#ifndef ESCALATION_H
#define ESCALATION_H

#include <linux/cred.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE > KERNEL_VERSION(3,4,0)
#define V(x) x.val
#else
#define V(x) x
#endif

int privilege_escalation(void);

#endif