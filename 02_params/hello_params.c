#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>

static char *name = "world";
module_param(name, charp, 0644);
MODULE_PARM_DESC(name, "Name to print in kernel log");

static int repeat = 1;
module_param(repeat, int, 0644);
MODULE_PARM_DESC(repeat, "Number of greeting messages (1~10)");

static int __init hello_params_init(void)
{
	int i;

	pr_info("init start\n");
	pr_info("received params name=\"%s\", repeat=%d\n", name, repeat);

	if (repeat < 1 || repeat > 10)
	{
		pr_err("Invalid repeat=%d (allowed range: 1~10)\n", repeat);
		return -EINVAL;
	}

	i = 0;
	while (i < repeat)
	{
		++i;
		pr_info("[%d/%d] hello, %s\n", i, repeat, name);
	}

	pr_info("init success\n");

	return 0;
}

static void __exit hello_params_exit(void)
{
	pr_info("exit, good bye %s\n.", name);
}

module_init(hello_params_init);
module_exit(hello_params_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Park Jinhyeok");
MODULE_DESCRIPTION("02_Params: Linux kernel module with module parameters");
MODULE_VERSION("0.1");
