#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manoj Patil <patilmanoj9528@gmail.com>");
MODULE_DESCRIPTION("Basic read loadable kernel module");

static struct proc_dir_entry *custom_proc_node;

static ssize_t read_fun(struct file *file_pointer,
                        char __user *user_space_buffers,
                        size_t count,
                        loff_t *offset) {
    char msg[] = "hello from kernel!\n";
    size_t len = strlen(msg);
    int result;

    printk("read_fun\n");

    if (*offset >= len)
        return 0;

    result = copy_to_user(user_space_buffers, msg, len);
    if (result != 0)
        return -EFAULT;

    *offset += len;
    return len;
}

static struct proc_ops driver_proc_ops = {
    .proc_read = read_fun,
};

static int my_module_init(void) {
    printk("my_module_init: entry\n");

    custom_proc_node = proc_create("my_driver",
                                   0,
                                   NULL,
                                   &driver_proc_ops);

    printk("my_module_init: exit\n");
    return 0;
}

static void my_module_exit(void) {
    printk("my_module_exit: entry\n");

    proc_remove(custom_proc_node);

    printk("my_module_exit: exit\n");
}

module_init(my_module_init);
module_exit(my_module_exit);
