/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h> // for platform driver
#include <linux/ioport.h>// defines the interface of request_mem_region function



	


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

		/*get the IRQ numbers*/
		GPIO_IRQ = platform_get_irq (dev,0); 
		DAC_IRQ = platform_get_irq (dev,4); 
		Timer_IRQ = platform_get_irq (dev,2); 
		
		/*requesting access to the I/O pins by allocating the corresponding memory region, it will return NULL if the I/O aren't available 
		*request_mem_region() will return NULL if the I/O isn't available
		*GPIO.start : is the first argument which is the starting address for the allocated memory
		*resource_size():returns the length of the memory needed by the I/O whcih is the second arrgument
		*dev -> name : is the third arrgument which is the name of the driver
		*/
		
		
		
		if(request_mem_region(GPIO->start,resource_size(GPIO), dev ->name)){
			/*This remaps the pyhiscal address into a virtual address*/
			unsigned long VA_GPIO = ioremap_nocache(GPIO->start, resource_size(GPIO))
		
		
		/*Test: turn on the LEDS 14,13 and 12*/
		*VA_GPIO = 2;
		*(VA_GPIO + 0x08) = 0x05550000; // PA_MODEH: this sets only PA14, PA13 and PA12 as outputs since the rest are being used by the OS
		*(VA_GPIO + 0x0c) = 0x7000; // PA_DOUT: setting the bits 14, 13 and 12 high
		
		/*end of the test*/
		
		


		
		
		
		
		
		
		
		/*release the allocated memory region after it has been used*/
		release_mem_region(GPIO->start,resource_size(GPIO));
		}




		return 0;
}

/*user progtam opens the driver */
static int mu_open (struct inode *inode, struct file *filp);

/*user progtam closes the driver */
static int mu_release (struct inode *inode, struct file *filp);

/*user progtam reads from the driver */
static ssize_t my_read (struct inode *flip, char __user *buff, size_t count, loff_t *offp);

/*user progtam writes to the driver */
static ssize_t my_write (struct inode *flip, char __user *buff, size_t count, loff_t *offp);


static struct file_operations my_fops = {
	.owner = THIS_MODULE,
	.read = my_read,
	.write = my_write,
	.opem = my_open,
	.release = my_release
};


/*it was mentioned in the compendium that a cdev struct needs to be allocated and intialized*/
struct cdex my_cdev;

cdev_init (&my_cdev, &my_fops);



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
