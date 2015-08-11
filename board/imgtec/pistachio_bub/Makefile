#
# Copyright (C) 2015 Imagination Technologies
#
# SPDX-License-Identifier:	GPL-2.0+
#

obj-y				= mfio.o
obj-y				+= pistachio.o
obj-$(CONFIG_SPL_BUILD)		+= clocks.o
ifdef CONFIG_DRAM_DDR2
obj-$(CONFIG_SPL_BUILD)		+= ddr2_init.o
endif
ifdef CONFIG_DRAM_DDR3
obj-$(CONFIG_SPL_BUILD)		+= ddr3_init.o
endif
obj-$(CONFIG_SPL_BUILD)		+= lowlevel_init.o
obj-$(CONFIG_SPL_BUILD)		+= spl_boot.o
