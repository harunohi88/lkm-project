#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/slab.h>

static int buffer_size = 128;
module_param(buffer_size, int, 0644);
MODULE_PARM_DESC(buffer_size, "Kernel buffer size in bytes (16-1024)");

static char *init_message = "hello from kernel memory!";
module_param(init_message, charp, 0644);
MODULE_PARM_DESC(init_message, "initial message to store in kernel buffer");

static char *kernel_buffer;

static int __init memory_demo_init(void)
{
	size_t message_length;

	pr_info("init start\n");
	pr_info("requested buffer_size: %d, init_message: %s\n", buffer_size, init_message);

	if (buffer_size < 16 || buffer_size > 1024)
	{
		pr_err("buffer_size out of range (range: 16-1024)\n");
		return -EINVAL;
	}

	kernel_buffer = kmalloc(buffer_size, GFP_KERNEL);
	if (kernel_buffer == NULL)
	{
		pr_err("kmalloc failed for buffer_size: %d\n", buffer_size);
		return -ENOMEM;
	}

	memset(kernel_buffer, 0, buffer_size);

	message_length = strlen(init_message);
	if (message_length > buffer_size)
	{
		pr_err("init_message too long (length=%zu, buffer_size=%d)\n", message_length, buffer_size);
		kfree(kernel_buffer);
		kernel_buffer = NULL;
		return -EINVAL;
	}

	strscpy(kernel_buffer, init_message, buffer_size);

	pr_info("buffer allocated at %px\n", kernel_buffer);
	pr_info("stored message=\"%s\"\n", kernel_buffer);
	pr_info("init success\n");

	return 0;

}

static void __exit memory_demo_exit(void)
{
	pr_info("exit start\n");

	if (kernel_buffer)
	{
		pr_info("freeing buffer at %px with message=\"%s\"\n",\
				kernel_buffer, kernel_buffer);
		kfree(kernel_buffer);
		kernel_buffer = NULL;
	}

	pr_info("exit complete\n");
}

module_init(memory_demo_init);
module_exit(memory_demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Park Jinhyeok");
MODULE_DESCRIPTION("03_Memory: Kernel memory allocation and cleanup demo");
MODULE_VERSION("0.1");
