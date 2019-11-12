/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h> // for platform driver
#include <linux/ioport.h>// defines the interface of request_mem_region function


#define DRIVER_NAME "gamepad"




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



















/* a function to obtain one or more device numbers to work with for setting up the char device time
	the major number identifies the driver associated with the device.
	The minor number is used by the kernel to determine exactly which device is being referred to.
*/

static int register_chr_dev(void)
{
	int ret;

	//Dynamic Allocation of the device number is performed by the function call alloc chrdev region (). Firstminor is zero
	if ((ret = alloc_chrdev_region(&gp_dev_number, 0, 1, DRIVER_NAME)) < 0) {
		printk(KERN_ERR "ERROR %d: Failed alloc_chr_region %s\n", ret,
		       DRIVER_NAME);
	}
	gp_cdev_ptr = cdev_alloc();
	cdev_init(gp_cdev_ptr, &gp_fops);
	if ((ret = cdev_add(gp_cdev_ptr, gp_dev_number, 1)) < 0) {
		printk(KERN_ERR "ERROR %d: Failed to add cdev %s\n", ret,
		       DRIVER_NAME);
	}
	gp_cl = class_create(THIS_MODULE, DRIVER_NAME);
	device_create(gp_cl, NULL, gp_dev_number, NULL, DRIVER_NAME);

	return 0;
}




/*
 * my_prove - it's the function that will be called if there is a hardware match (linux platform drivers)
 *
 * if there is a hardware match this function will be called and then it'll request information from the kernel about the register base address, irq numbers..etc and then initialize everything, after this function the driver is ready for use
 * code from a running kernel
 */

static int my_probe (struct platform_device *dev)
{
		struct *GPIO, *Timer, *DAC;
		int GPIO_IRQ, DAC_IRQ, Timer_IRQ;

		/*get the base address of each of the registers*/
		GPIO   = platform_get_resource(dev, IORESOURCE_MEM, 0)
		Timer  = platform_get_resource(dev, IORESOURCE_MEM, 1)
		DAC    = platform_get_resource(dev, IORESOURCE_MEM, 2)

		/*virtual memory base addresses */
		unsigned long VA_GPIO = ioremap_nocache(GPIO->start, resource_size(GPIO))
		unsigned long VA_Timer = ioremap_nocache(Timer->start, resource_size(Timer))
		unsigned long VA_DAC = ioremap_nocache(DAC->start, resource_size(DAC))

		/*get the IRQ numbers*/
		GPIO_IRQ = platform_get_irq (dev,0);
		DAC_IRQ = platform_get_irq (dev,4);
		Timer_IRQ = platform_get_irq (dev,2);


		dev_t device_number;	//device number

		static struct file_operations my_fops = {
			.owner = THIS_MODULE,
			.read = my_read,
			.write = my_write,
			.open = my_open,
			.release = my_release
		};


		/*it was mentioned in the compendium that a cdev struct needs to be allocated and intialized
		* propably will have to add extra stuff to this struct
		*/
		struct cdex my_cdev;
		struct class *cl; // creating a class struct

		cl = class create (THIS_MODULE,"my"); //this function is necessery to make the driver visiable for user space

		/*allocation of device number*/

		if(alloc_chrdev_region(&device_number, 0, 1, dev->name)<0){
			printk(KERN_ALERT"Unable to access the I/O-port C memory region.\n");
			return -1;
		}


		cdev_init (&my_cdev, &my_fops);
		/* passing the cd structure to the kernel
		* number 1 represent the number of devices
		*/
		cdev_add (&my_cdev,device_number,1);

		device_create (cl,NULL,device_number,NULL,"my");//this function is necessery to make the driver visiable for user space

// Exercise 2 equivalent
		int long unsigned current_value;
		int long unsigned new_value;

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
		new_value = current_value | ioread32(VA_GPIO + GPIO_IF);
		iowrite32(new_value, VA_GPIO + GPIO_IFC);


		/*requesting access to the I/O pins by allocating the corresponding memory region, it will return NULL if the I/O aren't available
		*request_mem_region() will return NULL if the I/O isn't available
		*GPIO.start : is the first argument which is the starting address for the allocated memory
		*resource_size():returns the length of the memory needed by the I/O whcih is the second arrgument
		*dev -> name : is the third arrgument which is the name of the driver
		*/



		/*Test: turn on the LEDS 14,13 and 12*/
		*VA_GPIO = 2;
		*(VA_GPIO + 0x08) = 0x05550000; // PA_MODEH: this sets only PA14, PA13 and PA12 as outputs since the rest are being used by the OS
		*(VA_GPIO + 0x0c) = 0x7000; // PA_DOUT: setting the bits 14, 13 and 12 high

		/*end of the test*/

		return 0;

}



/*user progtam opens the driver */
static int my_open (struct inode *inode, struct file *filp) {

}

/*user progtam closes the driver */
static int my_release (struct inode *inode, struct file *filp){
	unsigned long n = 0x24;

	//platform_device_release(struct device *dev)

	// Release I/O port region
	release_region(GPIO_PA_BASE ,n);
	release_region(GPIO_PC_BASE ,n);
	release_region(CMU_HFCORECLKEN0 ,0x4);
	iowrite32(0x00, GPIO_IEN);
	printk(KERN_INFO "my_release has been executed!");
	return 0;

}

/*user progtam reads from the driver */
static ssize_t my_read (struct inode *flip, char __user *buff, size_t count, loff_t *offp) {
	uint32_t data = ioread32(GPIO_PC_DIN);
  copy_to_user(buff, &data, 1);
	return (ssize_t)1;
}

/*user progtam writes to the driver */
static ssize_t my_write (struct inode *flip, char __user *buff, size_t count, loff_t *offp);



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
	printk("Hello World, here is your module speaking\n");

	/*register with the kernel*/
	platform_driver_register (&my_driver);

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
	 printk("Short life for a small module...\n");

	 /*unregester from kernel*/
	 platofrm_driver_unregister(&my_driver);
}








module_init(template_init);
module_exit(template_cleanup);

MODULE_DESCRIPTION("Small module, demo only, not very useful.");
MODULE_LICENSE("GPL");
