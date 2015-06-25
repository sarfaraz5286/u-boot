/*
 * Copyright (C) 2015 Imagination Technologies
 * Author: Govindraj Raja <govindraj.raja@imgtec.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _PISTACHIO_CONFIG_H
#define _PISTACHIO_CONFIG_H

#include <asm/addrspace.h>
#include <asm/pistachio.h>

/*
 * System configuration
 */

#define CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_DISPLAY_CPUINFO

#define CONFIG_PISTACHIO
#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_DISPLAY_BOARDINFO

#define CONFIG_MISC_INIT_R

/*
 * CPU Configuration
 */
#define CONFIG_SYS_MHZ			546
#define CONFIG_SYS_MIPS_TIMER_FREQ	(CONFIG_SYS_MHZ * 1000000)

#define CONFIG_SYS_CACHELINE_SIZE	32
#define CONFIG_PHYS_TO_BUS

#define CONFIG_OF_LIBFDT

/*
 * Memory map
 */
#define CONFIG_SYS_TEXT_BASE		0x80000000
#define CONFIG_SYS_MONITOR_BASE		CONFIG_SYS_TEXT_BASE

#define CONFIG_MEMSIZE_IN_BYTES

#define CONFIG_SYS_SDRAM_BASE		0x80000000
#define CONFIG_SYS_MEM_SIZE		(128 * 1024 * 1024)

#define CONFIG_SYS_INIT_SP_OFFSET	0x400000

#define CONFIG_SYS_LOAD_ADDR		0x81000000
#define CONFIG_SYS_MEMTEST_START	0x80100000
#define CONFIG_SYS_MEMTEST_END		0x80800000

#define CONFIG_SYS_MALLOC_LEN		(128 * 1024)
#define CONFIG_SYS_BOOTPARAMS_LEN	(128 * 1024)
#define CONFIG_SYS_BOOTM_LEN		(64 * 1024 * 1024)

/*
 * Console configuration
 */
#define CONFIG_SYS_PROMPT		"pistachio # "

#define CONFIG_SYS_CBSIZE		256
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					 sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		16

#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_AUTO_COMPLETE
#define CONFIG_CMDLINE_EDITING

/*
 * Serial driver
 */
#define CONFIG_BAUDRATE			115200

#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	-4
#define CONFIG_SYS_NS16550_CLK		(115200 * 16)
#define CONFIG_SYS_NS16550_COM1		CKSEG1ADDR(PISTACHIO_UART0)
#define CONFIG_SYS_NS16550_COM2		CKSEG1ADDR(PISTACHIO_UART1)
#define CONFIG_CONS_INDEX		2


/*
 * Ethernet configuration
 */
#define CONFIG_PHYLIB
#define CONFIG_ETH_DESIGNWARE

/*
 * USB configuration
 */
#define CONFIG_USB_DWC2_REG_ADDR	CKSEG1ADDR(PISTACHIO_USB)
#define CONFIG_USB_DWC2

/* USB Storage */
#define CONFIG_USB_DEVICE
#define CONFIG_USB_STORAGE
#define CONFIG_USB_GADGET


#define CONFIG_SYS_NO_FLASH

#define CONFIG_ENV_IS_NOWHERE
#define CONFIG_ENV_SIZE                 0x20000

#define CONFIG_EXTRA_ENV_SETTINGS 					\
	"fdtaddr=0x800F0000\0"						\
	"fdtfile=pistachio_bub.dtb\0"					\
	"bootfile=uImage.bin\0"						\
	"loadaddr=0x80400000\0"						\
	"bootdir=/\0"							\
	"usbdev=0\0"							\
	"usbpart=0\0"							\
	"usbboot=usb start;"						\
	"ext4load usb $usbdev:$usbpart $fdtaddr $bootdir$fdtfile;"	\
	"ext4load usb $usbdev:$usbpart $loadaddr $bootdir$bootfile;"	\
	"\0"								\

#define CONFIG_BOOTCOMMAND		\
	"setenv verify n;"		\
	"run usbboot;"			\
	"bootm $loadaddr - $fdtaddr;"	\

#define CONFIG_BOOTDELAY    0
/*
 * Commands
 */
#include <config_cmd_default.h>

#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_LOADB
#undef CONFIG_CMD_LOADS
#undef CONFIG_CMD_NFS


#define CONFIG_CMD_USB

#define CONFIG_CMD_DHCP
#define CONFIG_CMD_ELF
#define CONFIG_CMD_PING

#define CONFIG_CMD_NET

#define CONFIG_CMD_NFS
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING

#define CONFIG_CMD_FAT
#define CONFIG_CMD_EXT3
#define CONFIG_CMD_EXT4
#define CONFIG_DOS_PARTITION

#define CONFIG_SYS_LONGHELP		/* verbose help, undef to save memory */

#endif /* _PISTACHIO_CONFIG_H */
