#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/clk.h>
#include <linux/pm_runtime.h>
#include <linux/completion.h>

#define OMAP_I2C_REV_REG        0x00
#define OMAP_I2C_IE_REG         0x04
#define OMAP_I2C_STAT_REG       0x08
#define OMAP_I2C_SYSS_REG       0x10
#define OMAP_I2C_BUF_REG        0x14
#define OMAP_I2C_CNT_REG        0x18
#define OMAP_I2C_DATA_REG       0x1C
#define OMAP_I2C_CON_REG        0x24
#define OMAP_I2C_OA_REG         0x28
#define OMAP_I2C_SA_REG         0x2C
#define OMAP_I2C_PSC_REG        0x30
#define OMAP_I2C_SCLL_REG       0x34
#define OMAP_I2C_SCLH_REG       0x38

#define OMAP_I2C_CON_EN         BIT(15)
#define OMAP_I2C_CON_MST        BIT(10)
#define OMAP_I2C_CON_TRX        BIT(9)
#define OMAP_I2C_CON_STP        BIT(1)
#define OMAP_I2C_CON_STT        BIT(0)

#define OMAP_I2C_STAT_ARDY      BIT(2)
#define OMAP_I2C_STAT_RRDY      BIT(3)
#define OMAP_I2C_STAT_XRDY      BIT(4)
#define OMAP_I2C_STAT_NACK      BIT(1)

struct custom_i2c_dev {
	void __iomem *base;
	struct device *dev;
	struct i2c_adapter adapter;
	struct clk *fclk;
	int irq;
	u32 speed;
	struct completion cmd_complete;
	u8 *buf;
	size_t buf_len;
	int cmd_err;
};

static inline u32 custom_i2c_read(struct custom_i2c_dev *dev, u32 reg)
{
	return readl(dev->base + reg);
}

static inline void custom_i2c_write(struct custom_i2c_dev *dev, u32 reg, u32 val)
{
	writel(val, dev->base + reg);
}

static int custom_i2c_wait_for_bb(struct custom_i2c_dev *dev)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(1000);
	u32 stat;

	while (time_before(jiffies, timeout)) {
		stat = custom_i2c_read(dev, OMAP_I2C_STAT_REG);
		if (!(stat & OMAP_I2C_STAT_ARDY))
			return 0;
		cpu_relax();
	}

	dev_err(dev->dev, "Timeout waiting for bus ready\n");
	return -ETIMEDOUT;
}

static irqreturn_t custom_i2c_isr(int irq, void *dev_id)
{
	struct custom_i2c_dev *dev = dev_id;
	u32 stat, err_flags = 0;

	stat = custom_i2c_read(dev, OMAP_I2C_STAT_REG);

	if (stat & OMAP_I2C_STAT_NACK) {
		err_flags |= OMAP_I2C_STAT_NACK;
		custom_i2c_write(dev, OMAP_I2C_CON_REG, OMAP_I2C_CON_STP);
	}

	if (stat & OMAP_I2C_STAT_ARDY)
		complete(&dev->cmd_complete);

	custom_i2c_write(dev, OMAP_I2C_STAT_REG, stat);

	if (err_flags) {
		dev->cmd_err |= err_flags;
		complete(&dev->cmd_complete);
	}

	return IRQ_HANDLED;
}

static int custom_i2c_xfer_msg(struct i2c_adapter *adap,
		struct i2c_msg *msg, int stop)
{
	struct custom_i2c_dev *dev = i2c_get_adapdata(adap);
	unsigned long timeout;
	u32 con;

	custom_i2c_write(dev, OMAP_I2C_SA_REG, msg->addr);
	custom_i2c_write(dev, OMAP_I2C_CNT_REG, msg->len);

	dev->buf = msg->buf;
	dev->buf_len = msg->len;
	dev->cmd_err = 0;

	reinit_completion(&dev->cmd_complete);

	con = OMAP_I2C_CON_EN | OMAP_I2C_CON_MST | OMAP_I2C_CON_STT;

	if (msg->flags & I2C_M_RD)
		con &= ~OMAP_I2C_CON_TRX;
	else
		con |= OMAP_I2C_CON_TRX;

	if (stop)
		con |= OMAP_I2C_CON_STP;

	custom_i2c_write(dev, OMAP_I2C_CON_REG, con);

	timeout = wait_for_completion_timeout(&dev->cmd_complete,
			msecs_to_jiffies(1000));
	if (!timeout) {
		dev_err(dev->dev, "Transfer timeout\n");
		return -ETIMEDOUT;
	}

	if (dev->cmd_err & OMAP_I2C_STAT_NACK) {
		dev_err(dev->dev, "No acknowledge from slave\n");
		return -EREMOTEIO;
	}

	return 0;
}

static int custom_i2c_xfer(struct i2c_adapter *adap,
		struct i2c_msg msgs[], int num)
{
	struct custom_i2c_dev *dev = i2c_get_adapdata(adap);
	int i, ret;

	pm_runtime_get_sync(dev->dev);

	ret = custom_i2c_wait_for_bb(dev);
	if (ret < 0)
		goto out;

	for (i = 0; i < num; i++) {
		ret = custom_i2c_xfer_msg(adap, &msgs[i], (i == (num - 1)));
		if (ret < 0)
			goto out;
	}

	ret = num;

out:
	pm_runtime_put_sync(dev->dev);
	return ret;
}

static u32 custom_i2c_func(struct i2c_adapter *adap)
{
	return I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
}

static const struct i2c_algorithm custom_i2c_algo = {
	.master_xfer = custom_i2c_xfer,
	.functionality = custom_i2c_func,
};

static int custom_i2c_init_hw(struct custom_i2c_dev *dev)
{
	u32 psc, scll, sclh;
	unsigned long fclk_rate;

	custom_i2c_write(dev, OMAP_I2C_CON_REG, 0);

	fclk_rate = clk_get_rate(dev->fclk);

	if (dev->speed > 100000) {
		psc = fclk_rate / 12000000 - 1;
		scll = 7;
		sclh = 5;
	} else {
		psc = fclk_rate / 12000000 - 1;
		scll = 13;
		sclh = 15;
	}

	custom_i2c_write(dev, OMAP_I2C_PSC_REG, psc);
	custom_i2c_write(dev, OMAP_I2C_SCLL_REG, scll);
	custom_i2c_write(dev, OMAP_I2C_SCLH_REG, sclh);

	custom_i2c_write(dev, OMAP_I2C_CON_REG, OMAP_I2C_CON_EN);

	custom_i2c_write(dev, OMAP_I2C_IE_REG,
			OMAP_I2C_STAT_ARDY | OMAP_I2C_STAT_NACK |
			OMAP_I2C_STAT_RRDY | OMAP_I2C_STAT_XRDY);

	return 0;
}

static int custom_i2c_probe(struct platform_device *pdev)
{
	struct custom_i2c_dev *dev;
	struct resource *mem;
	int ret;

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dev->base = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(dev->base))
		return PTR_ERR(dev->base);

	dev->irq = platform_get_irq(pdev, 0);
	if (dev->irq < 0)
		return dev->irq;

	dev->dev = &pdev->dev;

	of_property_read_u32(pdev->dev.of_node, "clock-frequency", &dev->speed);
	if (!dev->speed)
		dev->speed = 100000;

	dev->fclk = devm_clk_get(&pdev->dev, "fck");
	if (IS_ERR(dev->fclk))
		return PTR_ERR(dev->fclk);

	pm_runtime_enable(dev->dev);
	pm_runtime_get_sync(dev->dev);

	init_completion(&dev->cmd_complete);

	ret = custom_i2c_init_hw(dev);
	if (ret)
		goto err_pm;

	ret = devm_request_irq(&pdev->dev, dev->irq, custom_i2c_isr,
			IRQF_SHARED, dev_name(&pdev->dev), dev);
	if (ret)
		goto err_pm;

	i2c_set_adapdata(&dev->adapter, dev);
	dev->adapter.owner = THIS_MODULE;
	dev->adapter.class = I2C_CLASS_DEPRECATED;
	strncpy(dev->adapter.name, "Custom I2C adapter", sizeof(dev->adapter.name));
	dev->adapter.name[sizeof(dev->adapter.name)-1] = '\0';
	dev->adapter.algo = &custom_i2c_algo;
	dev->adapter.dev.parent = &pdev->dev;
	dev->adapter.dev.of_node = pdev->dev.of_node;
	dev->adapter.nr = pdev->id;

	ret = i2c_add_numbered_adapter(&dev->adapter);
	if (ret)
		goto err_pm;

	platform_set_drvdata(pdev, dev);

	pm_runtime_put_sync(dev->dev);

	return 0;

err_pm:
	pm_runtime_put_sync(dev->dev);
	pm_runtime_disable(dev->dev);
	return ret;
}

static void custom_i2c_remove(struct platform_device *pdev)
{
	struct custom_i2c_dev *dev = platform_get_drvdata(pdev);

	i2c_del_adapter(&dev->adapter);
	pm_runtime_disable(dev->dev);

}

static const struct of_device_id custom_i2c_of_match[] = {
	{ .compatible = "custom,omap-i2c", },
	{ },
};
MODULE_DEVICE_TABLE(of, custom_i2c_of_match);

static struct platform_driver custom_i2c_driver = {
	.probe = custom_i2c_probe,
	.remove = custom_i2c_remove,
	.driver = {
		.name = "custom-i2c",
		.of_match_table = custom_i2c_of_match,
	},
};

module_platform_driver(custom_i2c_driver);

MODULE_AUTHOR("Pujit");
MODULE_DESCRIPTION("Custom I2C Master Driver for BBB");
MODULE_LICENSE("GPL");

