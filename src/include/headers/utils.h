#ifndef INCLUDE_H
#define INCLUDE_H

#include <linux/printk.h>

#define DEBUG_ENABLED 1

#define debug(str, ...) 					\
if (DEBUG_ENABLED) {			 			\
	pr_info("[ ROOTKIT_POC ] [ %s ] " str "\n", 		\
		__func__, ##__VA_ARGS__); 			\
}

#define alert(str, ...) 					\
if (DEBUG_ENABLED) { 						\
	pr_warn("[ ROOTKIT_POC ] [ %s ] " str "\n", 		\
		__func__, ##__VA_ARGS__); 			\
}

#endif