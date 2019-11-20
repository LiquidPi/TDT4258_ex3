/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h> // for platform driver
#include <linux/ioport.h>// defines the interface of request_mem_region function
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <linux/fs.h>
#include <linux/uaccess.h>


#include "efm32gg.h"



#define GPIO_IF        0x114


		/*Variables decleration space*/
		
		struct resource *GPIO,*memory;
		int GPIO_IRQ_even, GPIO_IRQ_odd;
		unsigned long VA_GPIO ;
		struct cdev my_cdev;
		struct class *cl; // creating a class struct
		dev_t device_number;	//device number
		struct fasync_struct *async_queue;

		 long unsigned current_value;
		 long unsigned new_value;
		 long unsigned status = 0;
	
/*	static int my_fasync(int fd, struct file *filp, int mode){
    return fasync_helper(fd, filp, mode, &async_queue);
}*/



//	static irqreturn_t interrupt_handler(int irq, void *dev_id, struct pt_regs *regs){
	
	
	
	/*store the button status*/
	//status = ~ioread8(GPIO_PC_DIN); // read interrupt source
	
    //writel(status, VA_GPIO + GPIO_IFC); // clear interrupt
    
    //printk("interrupt!, %d \n", status);


	/*clear the interrupt*/
	//current_value = ioread32(GPIO_IFC);
	//new_value = current_value | ioread32(VA_GPIO + GPIO_IF);
	//iowrite32 (new_value, GPIO_IFC);
	
    //kill_fasync(&async_queue, SIGIO, POLL_IN);
    //return IRQ_HANDLED;
//}




/*user progtam opens the driver */
static int my_open (struct inode *inode, struct file *filp) {
		
		
		memory = request_mem_region(GPIO-> start, resource_size(GPIO),"gamedriver_mem");
		
		
		// Set GPIO PC to input
		new_value = 0x33333333;
		iowrite32(new_value, GPIO_PC_MODEL);

		
		// Enable internal pullup
		new_value = 0xFF;
		iowrite32(new_value, GPIO_PC_DOUT);
		// Enable interrupts for GPIO C when its state changes
		new_value = 0x22222222;
		iowrite32(new_value, GPIO_EXTIPSELL);

		// Set up the GPIO to interrupt when a bit changes from 1 to 0 (button pressed)
		new_value = 0xFF;
		iowrite32(new_value,  GPIO_EXTIFALL);

		// Set up interrupt generation
		//current_value = ioread32(VA_GPIO + GPIO_IEN);
		new_value = 0xFF; //current_value | 0xFF;
		iowrite32(new_value,  GPIO_IEN);

		// Clear interrupt flags to avoid interrupt on startup
		/*current_value = ioread32(VA_GPIO + GPIO_IF);
		new_value = current_value | ioread32(VA_GPIO + GPIO_IFC);
		iowrite32(new_value, VA_GPIO + GPIO_IFC);*/
		

	/*	int ret_even = request_irq ( GPIO_IRQ_even,interrupt_handler,0, "gamepad", &my_cdev);
		if (ret_even < 0){
		printk (KERN_ALERT "%s: request_irg failed with %d\n",
__func__, ret_even);
		}
		
		int ret_odd = request_irq ( GPIO_IRQ_odd,interrupt_handler,0, "gamepad", &my_cdev);
		if (ret_odd < 0){
		printk (KERN_ALERT "%s: request_irg failed with %d\n",
__func__, ret_odd);
		}*/
		//printk (" Device opened \n ");
		return 0;


}

/*user progtam closes the driver */
static int my_release (struct inode *inode, struct file *filp){


	//platform_device_release(struct device *dev)
	//free_irq(GPIO_IRQ,NULL);               causing an error, should be fixedd
	//printk (" Device closed \n ");
	return 0;
	/*
	// Release I/O port region
	release_region(GPIO_PA_BASE ,n);
	release_region(GPIO_PC_BASE ,n);
	release_region(CMU_HFCORECLKEN0 ,0x4);
	iowrite32(0x00, GPIO_IEN);
	printk(KERN_INFO "my_release has been executed!");
	return 0;
	*/
}

/*user progtam reads from the driver */
static ssize_t my_read (struct inode *flip, char __user *buff, size_t count, loff_t *offp) {
	
	int8_t data = ~ioread8(GPIO_PC_DIN);

	//copy_to_user (to Destination address, in user space buffer, from Source address, in kernel space data, n number of bytes to copy)
	copy_to_user(buff, &data, 1);

	
	//printk (" Device is being read %d  \n ",buff);
	return 0;
}

/*user progtam writes to the driver */
static ssize_t my_write (struct inode *flip, char __user *buff, size_t count, loff_t *offp){
	printk (" Device can't be written to!!! \n ");
	return 0;
};


	static struct file_operations my_fops = {
			.owner = THIS_MODULE,
			.read = my_read,
			.write = my_write,
			.open = my_open,
			.release = my_release
		};




/*
 * my_prove - it's the function that will be called if there is a hardware match (linux platform drivers)
 *
 * if there is a hardware match this function will be called and then it'll request information from the kernel about the register base address, irq numbers..etc and then initialize everything, after this function the driver is ready for use
 * code from a running kernel
 */

static int my_probe (struct platform_device *dev)
{
		
		/*allocation of device number*/

		if(alloc_chrdev_region(&device_number, 0, 1, "gamepad")<0){
			printk(KERN_ALERT"Unable to access the I/O-port C memory region.\n");
			return -1;
		}

		cl = class_create (THIS_MODULE,"gamepad"); //this function is necessery to make the driver visiable for user space
		device_create (cl,NULL,device_number,NULL,"gamepad");//this function is necessery to make the driver visiable for user space


		cdev_init (&my_cdev, &my_fops);
		/* passing the cd structure to the kernel
		* number 1 represent the number of devices
		*/
		cdev_add (&my_cdev,device_number,1);
		
		

		
		/*get the base address of each of the registers*/
		GPIO   = platform_get_resource(dev, IORESOURCE_MEM, 0);

		/*virtual memory base addresses */
		 VA_GPIO = ioremap_nocache(GPIO->start, resource_size(GPIO));

		/*get the IRQ numbers*/
		GPIO_IRQ_even = platform_get_irq (dev,0);
		GPIO_IRQ_odd  = platform_get_irq (dev,1);


		

		
		
		

// Exercise 2 equivalent

/*
		// Enable buttons
		// Set GPIO PC to input
		new_value = 0x33333333;
		iowrite32(new_value, VA_GPIO + GPIO_PC_MODEL);

		// Enable internal pullup
		new_value = 0xFF;
		iowrite32(new_value, VA_GPIO + GPIO_PC_DOUT);

		// Enable interrupts for GPIO C when its state changes
		new_value = 0x22222222;
		iowrite32(new_value, VA_GPIO + GPIO_EXTIPSELL);

		// Set up the GPIO to interrupt when a bit changes from 1 to 0 (button pressed)
		new_value = 0xFF;
		iowrite32(new_value, VA_GPIO + GPIO_EXTIFALL);

		// Set up interrupt generation
		current_value = ioread32(VA_GPIO + GPIO_IEN);
		new_value = current_value | 0xFF;
		iowrite32(new_value, VA_GPIO + GPIO_IEN);

		// Clear interrupt flags to avoid interrupt on startup
		current_value = ioread32(VA_GPIO + GPIO_IFC);
		new_value = current_value | ioread32(VA_GPIO + GPIO_IFC);
		iowrite32(new_value, VA_GPIO + GPIO_IFC);
*/

		/*requesting access to the I/O pins by allocating the corresponding memory region, it will return NULL if the I/O aren't available
		*request_mem_region() will return NULL if the I/O isn't available
		*GPIO.start : is the first argument which is the starting address for the allocated memory
		*resource_size():returns the length of the memory needed by the I/O whcih is the second arrgument
		*dev -> name : is the third arrgument which is the name of the driver
		*/

		return 0;

}

/*
 * my_remove - function to be called when the driver is being deactivated
 *
 *
 * code from a running kernel
 */

static int my_remove (struct platform_device *dev){

		return 0;
}


static const struct of_device_id my_of_match[] = {
		{	.compatible = "tdt4258",	},
		{	},
};
MODULE_DEVICE_TABLE(of,	my_of_match);

/* This struct define my_driver which is what the __int will register when the driver is loaded to the kernel
*
*/
static struct platform_driver my_driver = {
		.probe	=	my_probe,
		.remove	=	my_remove,
		.driver	=	{
					.name	=	"my",
					.owner	=	THIS_MODULE,
					.of_match_table	=	my_of_match,
		},
};


/*********************************************/

/*
 * template_init - function to insert this module into kernel space
 *
 * This is the first of two exported functions to handle inserting this
 * code into a running kernel
 *
 * Returns 0 if successfull, otherwise -1
 * To make this driver a linux platform driver the initial function will only register the device, and if there is a mathc later the kernel will call "my_probe" function
 */

static int __init template_init(void)
{
	

	/*register with the kernel*/
	platform_driver_register (&my_driver);
	
    printk("Hello World, here is your module speaking\n");
	return 0;
}

/*
 * template_cleanup - function to cleanup this module from kernel space
 *
 * This is the second of two exported functions to handle cleanup this
 * code from a running kernel
 */

static void __exit template_cleanup(void)
{

    cdev_del(&my_cdev);

	 /*unregester from kernel*/
	 platform_driver_unregister(&my_driver);
	 printk("Short life for a small module...\n");
}








module_init(template_init);

module_exit(template_cleanup);

MODULE_DESCRIPTION("Small module, demo only, not very useful.");
MODULE_LICENSE("GPL");
