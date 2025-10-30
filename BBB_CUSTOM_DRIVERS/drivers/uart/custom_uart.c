#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/serial_core.h>
#include <linux/serial_8250.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/clk.h>
#include <linux/pm_runtime.h>
#include <linux/tty_flip.h>

#ifndef UART_LCR_8N1
#define UART_LCR_8N1 0x03
#endif

struct custom_uart_port {
	struct uart_port port;
	struct clk *fclk;
	void __iomem *membase;
};

static inline u32 custom_uart_read(struct custom_uart_port *up, u32 reg)
{
	u32 val = readl(up->membase + reg);
	pr_info("custom_uart: read 0x%x from reg 0x%x\n", val, reg);
	return val;
}

static inline void custom_uart_write(struct custom_uart_port *up, u32 reg, u32 val)
{
	writel(val, up->membase + reg);
	pr_info("custom_uart: wrote 0x%x to reg 0x%x\n", val, reg);
}

static void custom_uart_start_tx(struct uart_port *port)
{
}

static void custom_uart_stop_tx(struct uart_port *port)
{
}

static void custom_uart_stop_rx(struct uart_port *port)
{
	struct custom_uart_port *up = container_of(port, struct custom_uart_port, port);
	custom_uart_write(up, UART_IER, 0);
}

static void custom_uart_enable_ms(struct uart_port *port)
{
}

static void custom_uart_rx_chars(struct custom_uart_port *up)
{
	struct uart_port *port = &up->port;
	unsigned int lsr;
	unsigned char ch;

	lsr = custom_uart_read(up, UART_LSR);
	while (lsr & UART_LSR_DR) {
		ch = custom_uart_read(up, UART_RX);
		tty_insert_flip_char(&port->state->port, ch, TTY_NORMAL);
		lsr = custom_uart_read(up, UART_LSR);
	}
	tty_flip_buffer_push(&port->state->port);
}

static irqreturn_t custom_uart_irq(int irq, void *dev_id)
{
	struct custom_uart_port *up = dev_id;
	custom_uart_rx_chars(up);
	return IRQ_HANDLED;
}

static int custom_uart_startup(struct uart_port *port)
{
	struct custom_uart_port *up = container_of(port, struct custom_uart_port, port);
	int ret;

	pm_runtime_get_sync(port->dev);
	custom_uart_write(up, UART_FCR, 0x07);
	custom_uart_write(up, UART_IER, 0x01);
	ret = request_irq(port->irq, custom_uart_irq, IRQF_SHARED, "custom-uart", up);
	if (ret) {
		pr_err("custom_uart: IRQ request failed\n");
		return ret;
	}
	pr_info("custom_uart: startup done\n");
	return 0;
}

static void custom_uart_shutdown(struct uart_port *port)
{
	struct custom_uart_port *up = container_of(port, struct custom_uart_port, port);
	custom_uart_write(up, UART_IER, 0);
	free_irq(port->irq, up);
	pm_runtime_put_sync(port->dev);
	pr_info("custom_uart: shutdown done\n");
}

static void custom_uart_set_termios(struct uart_port *port,
		struct ktermios *termios,
		const struct ktermios *old)
{
	struct custom_uart_port *up = container_of(port, struct custom_uart_port, port);
	unsigned int baud, quot;
	unsigned char lcr = UART_LCR_8N1;

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk / 16);
	quot = uart_get_divisor(port, baud);

	custom_uart_write(up, UART_LCR, lcr | 0x80);
	custom_uart_write(up, UART_DLL, quot & 0xff);
	custom_uart_write(up, UART_IER, quot >> 8);
	custom_uart_write(up, UART_LCR, lcr);

	uart_update_timeout(port, termios->c_cflag, baud);
	pr_info("custom_uart: set_termios baud=%u\n", baud);
}

static const char *custom_uart_type(struct uart_port *port)
{
	return "CUSTOM_UART";
}

static void custom_uart_release_port(struct uart_port *port)
{
}

static int custom_uart_request_port(struct uart_port *port)
{
	return 0;
}

static void custom_uart_config_port(struct uart_port *port, int flags)
{
	if (flags & UART_CONFIG_TYPE)
		port->type = PORT_16550A;
}

static int custom_uart_verify_port(struct uart_port *port, struct serial_struct *ser)
{
	return 0;
}

static const struct uart_ops custom_uart_ops = {
	.start_tx     = custom_uart_start_tx,
	.stop_tx      = custom_uart_stop_tx,
	.stop_rx      = custom_uart_stop_rx,
	.enable_ms    = custom_uart_enable_ms,
	.startup      = custom_uart_startup,
	.shutdown     = custom_uart_shutdown,
	.set_termios  = custom_uart_set_termios,
	.type         = custom_uart_type,
	.release_port = custom_uart_release_port,
	.request_port = custom_uart_request_port,
	.config_port  = custom_uart_config_port,
	.verify_port  = custom_uart_verify_port,
};

static struct uart_driver custom_uart_driver = {
	.owner        = THIS_MODULE,
	.driver_name  = "custom-uart",
	.dev_name     = "ttyC",
	.major        = 0,
	.minor        = 0,
	.nr           = 1,
};

static int custom_uart_probe(struct platform_device *pdev)
{
	struct custom_uart_port *up;
	struct resource *mem;
	int ret;

	pr_info("custom_uart: probe start\n");

	up = devm_kzalloc(&pdev->dev, sizeof(*up), GFP_KERNEL);
	if (!up)
		return -ENOMEM;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	up->membase = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(up->membase))
		return PTR_ERR(up->membase);

	up->port.irq = platform_get_irq(pdev, 0);
	if (up->port.irq < 0)
		return up->port.irq;

	up->fclk = devm_clk_get(&pdev->dev, "fck");
	if (IS_ERR(up->fclk))
		return PTR_ERR(up->fclk);

	up->port.dev = &pdev->dev;
	up->port.type = PORT_16550A;
	up->port.iotype = UPIO_MEM;
	up->port.mapbase = mem->start;
	up->port.membase = up->membase;
	up->port.fifosize = 64;
	up->port.ops = &custom_uart_ops;
	up->port.flags = UPF_BOOT_AUTOCONF;
	up->port.uartclk = clk_get_rate(up->fclk);

	pm_runtime_enable(&pdev->dev);
	pm_runtime_get_sync(&pdev->dev);

	ret = uart_add_one_port(&custom_uart_driver, &up->port);
	if (ret) {
		pm_runtime_put_sync(&pdev->dev);
		pm_runtime_disable(&pdev->dev);
		return ret;
	}

	platform_set_drvdata(pdev, up);
	pr_info("custom_uart: probe done at 0x%lx\n", (unsigned long)mem->start);
	return 0;
}

static void custom_uart_remove(struct platform_device *pdev)
{
	struct custom_uart_port *up = platform_get_drvdata(pdev);
	uart_remove_one_port(&custom_uart_driver, &up->port);
	pm_runtime_disable(&pdev->dev);
	pr_info("custom_uart: removed\n");
}

static const struct of_device_id custom_uart_of_match[] = {
	{ .compatible = "custom,omap-uart", },
	{ },
};
MODULE_DEVICE_TABLE(of, custom_uart_of_match);

static struct platform_driver custom_uart_platform_driver = {
	.probe = custom_uart_probe,
	.remove = custom_uart_remove,
	.driver = {
		.name = "custom-uart",
		.of_match_table = custom_uart_of_match,
	},
};

static int __init custom_uart_init(void)
{
	int ret;

	ret = uart_register_driver(&custom_uart_driver);
	if (ret)
		return ret;

	ret = platform_driver_register(&custom_uart_platform_driver);
	if (ret)
		uart_unregister_driver(&custom_uart_driver);

	return ret;
}

static void __exit custom_uart_exit(void)
{
	platform_driver_unregister(&custom_uart_platform_driver);
	uart_unregister_driver(&custom_uart_driver);
}

module_init(custom_uart_init);
module_exit(custom_uart_exit);

MODULE_AUTHOR("Pujit");
MODULE_DESCRIPTION("Custom UART Driver for BBB");
MODULE_LICENSE("GPL");

