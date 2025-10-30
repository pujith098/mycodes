#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0xadfaa6f6, "__platform_driver_register" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x92997ed8, "_printk" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xa26af585, "__pm_runtime_disable" },
	{ 0x755a2154, "spi_finalize_current_message" },
	{ 0xd25a1eff, "__spi_alloc_controller" },
	{ 0x411e9a6e, "pm_runtime_enable" },
	{ 0xf322c130, "devm_spi_register_controller" },
	{ 0x7bce0087, "put_device" },
	{ 0x3992149a, "platform_driver_unregister" },
	{ 0x31916f86, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Ccustom,spi");
MODULE_ALIAS("of:N*T*Ccustom,spiC*");
