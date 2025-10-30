/*custom SPI Controller Driver for BeagleBone Black (Kernel 6.x)
	 * Fixed for kernel 6.12.32
	 *  */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/spi/spi.h>
#include <linux/of.h>
#include <linux/io.h>
#include <linux/clk.h>
#include <linux/pm_runtime.h>

	 struct custom_spi {
		     struct spi_controller *ctlr;
		         void __iomem *base;
			     struct clk *clk;
	 };

static int custom_spi_transfer_one_message(struct spi_controller *ctlr, 
		                                           struct spi_message *msg)
{
	    struct spi_transfer *xfer;
	        
	        pr_info("custom_spi: transfer start\n");
		    
		    list_for_each_entry(xfer, &msg->transfers, transfer_list) {
			            pr_info("custom_spi: len=%u speed=%u\n", xfer->len, xfer->speed_hz);
				            
				            if (xfer->tx_buf)
						                pr_info("custom_spi: TX buffer available\n");
					            if (xfer->rx_buf)
							                pr_info("custom_spi: RX buffer available\n");
						        }
		        
		        msg->status = 0;
			    msg->actual_length = 0;
			        
			        list_for_each_entry(xfer, &msg->transfers, transfer_list) {
					        msg->actual_length += xfer->len;
						    }
				    
				    spi_finalize_current_message(ctlr);
				        
				        pr_info("custom_spi: transfer complete\n");
					    return 0;
}

static int custom_spi_setup(struct spi_device *spi_dev)
{
	    pr_info("custom_spi: setup for chip select %u\n", (unsigned int)spi_dev->chip_select);
	        return 0;
}

static int custom_spi_probe(struct platform_device *pdev)
{
	    struct spi_controller *ctlr;
	        struct custom_spi *spi;
		    int ret;
		        
		        pr_info("custom_spi: probe start\n");
			    
			    /* In kernel 6.12, spi_alloc_master returns spi_controller */
			    ctlr = (struct spi_controller *)spi_alloc_master(&pdev->dev, sizeof(*spi));
			        if (!ctlr) {
					        pr_err("custom_spi: failed to allocate SPI controller\n");
						        return -ENOMEM;
							    }
				    
				    /* Get driver data */
				    spi = spi_controller_get_devdata(ctlr);
				        spi->ctlr = ctlr;
					    
					    platform_set_drvdata(pdev, spi);
					        
					        /* Configure SPI controller */
					        ctlr->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
						    ctlr->bits_per_word_mask = SPI_BPW_MASK(8);
						        ctlr->num_chipselect = 4;
							    ctlr->setup = custom_spi_setup;
							        ctlr->transfer_one_message = custom_spi_transfer_one_message;
								    ctlr->dev.of_node = pdev->dev.of_node;
								        
								        /* Enable runtime PM */
								        pm_runtime_enable(&pdev->dev);
									    
									    pr_info("custom_spi: registering SPI controller\n");
									        
									        /* Register SPI controller */
									        ret = devm_spi_register_controller(&pdev->dev, ctlr);
										    if (ret) {
											            pr_err("custom_spi: registration failed: %d\n", ret);
												            pm_runtime_disable(&pdev->dev);
													            spi_controller_put(ctlr);
														            return ret;
															        }
										        
										        pr_info("custom_spi: probe done successfully\n");
											    return 0;
}

static void custom_spi_remove(struct platform_device *pdev)
{
	    pr_info("custom_spi: remove called\n");
	        pm_runtime_disable(&pdev->dev);
		    pr_info("custom_spi: remove done\n");
}

static const struct of_device_id custom_spi_dt_ids[] = {
	    { .compatible = "custom,spi" },
	        { }
};
MODULE_DEVICE_TABLE(of, custom_spi_dt_ids);

static struct platform_driver custom_spi_driver = {
	    .probe = custom_spi_probe,
	        .remove_new = custom_spi_remove,
		    .driver = {
			            .name = "custom_spi",
				            .of_match_table = custom_spi_dt_ids,
					        },
};

module_platform_driver(custom_spi_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pujith");
MODULE_DESCRIPTION("Custom SPI Controller Driver for BBB (Kernel 6.12)");
