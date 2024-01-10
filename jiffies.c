/*
 *
 * jiffies.c
 *
 * Kernel module that prints the current jiffies value
 * when cat /proc/jiffies is called
 *
 * jhak1@mcmaster.ca
 * 
 */
// For kernel programming
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
// For proc read
#include <linux/proc_fs.h>
// For jiffies
#include <linux/jiffies.h>
#include <asm/uaccess.h>

// Defines a constant buffer size for the string to be printed
#define BUFFER_SIZE 128
// Defines the name of the proc
#define PROC_NAME "jiffies"

/*
 * Function Prototypes
 * */

ssize_t proc_read(struct file *file, char __user *usr_buf,size_t count, loff_t *pos);

static struct proc_ops proc_ops ={
	.proc_read = proc_read,
};

/* This function is called when the module is loaded. */
int proc_init(void)
{
	/* created the /proc/jiffies entry */
	proc_create(PROC_NAME, 0666, NULL, &proc_ops);

	return 0;
}
/* This function is called when the module is removed. */
void proc_exit(void)
{
	/* removes the /proc/jiffies entry */
	remove_proc_entry(PROC_NAME, NULL);
}
/* This function is called each time /proc/jiffies is read */
ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count,loff_t *pos)
{
	// rv will store the number of characters printed
	int rv = 0;
	char buffer[BUFFER_SIZE];
	// completed is used as a boolean value to prevent repeated reads
	static int completed = 0;

	// If it is completed, set completed to 0 and return 0 to prevent repetition
	if(completed){
		completed = 0;
		return 0;
	}

	// Otherwise, set completed to 1 and print the jiffies
	completed = 1;

	// Store the number of characters printed in rv
	// sprintf returns the number of characters in buffer
	rv = sprintf(buffer, "jiffies: %lu\n", jiffies);

	/* copied kernel space buffer to user space usr_buf */
	copy_to_user(usr_buf, buffer, rv);

	// Returns rv
	return rv;
}

//Set the module entry and exit points
module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HELLO MODULE");
MODULE_AUTHOR("SGG");
