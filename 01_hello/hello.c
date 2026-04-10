#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/kernel.h>
#include <linux/module.h>

static int __init hello_init(void)
{
	pr_info("module loaded\n");
	pr_warn("this is a traning module\n");
	pr_err("this is a error test\n");
	
	return 0;
}

static void __exit hello_exit(void)
{
	pr_info("module unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Park Jinhyeok");
MODULE_DESCRIPTION("01_hello: basic linux kernel module");
MODULE_VERSION("0.1");
