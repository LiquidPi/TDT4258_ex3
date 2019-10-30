/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h> // for platform driver



	struct resource *res = platform_get_resource(dev , IORESOURCE_MEM, index);//returns the register base address
	
	int irq = platform_get_irq(dev , index);// returns the number of interrupt lines
	


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

		/*map the virtual address into the phu=ysical address(it isn't needed here but it's a good practice)*/
		GPIO = ioremap_nocache(GPIO->start, resource_size(GPIO));
		Timer = ioremap_nocache(Timer->start, resource_size(Timer));
		DAC = ioremap_nocache(DAC->start, resource_size(DAC));
		

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
