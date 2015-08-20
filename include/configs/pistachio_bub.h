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
#define PISTACHIO_BOARD_NAME		CONFIG_SYS_CONFIG_NAME
#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_DISPLAY_BOARDINFO

#define CONFIG_OF_LIBFDT

#define CONFIG_MISC_INIT_R

/*
 * CPU Configuration
 */
#define CONFIG_SYS_MHZ			546
#define CONFIG_SYS_MIPS_TIMER_FREQ	(CONFIG_SYS_MHZ * 1000000)

#define CONFIG_PHYS_TO_BUS

#define CONFIG_OF_LIBFDT

/*
 * Memory map
 */
#define CONFIG_SYS_GRAM_BASE		0x1A000000
#define CONFIG_SYS_GRAM_SIZE		0x00020000
#define CONFIG_SYS_SRAM_BASE		0x1B000000
#define CONFIG_SYS_SRAM_SIZE		0x00010000
#define CONFIG_SYS_SOC_REG_BASE		0x18100000
#define CONFIG_SYS_SOC_REG_SIZE		0x00440000

#define CONFIG_SYS_TEXT_BASE		0x00400000
#define CONFIG_SYS_MONITOR_BASE		CONFIG_SYS_TEXT_BASE

#define CONFIG_MEMSIZE_IN_BYTES

#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_MEM_SIZE		(128 * 1024 * 1024)

#define CONFIG_SYS_INIT_SP_OFFSET	0x400000

#define CONFIG_SYS_LOAD_ADDR		0x01000000
#define CONFIG_SYS_MEMTEST_START	0x00100000
#define CONFIG_SYS_MEMTEST_END		0x00800000

#define CONFIG_SYS_MALLOC_LEN		(4 * 1024 * 1024)
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

#ifdef CONFIG_SYS_NS16550_REG_SIZE
#undef CONFIG_SYS_NS16550_REG_SIZE
#define CONFIG_SYS_NS16550_REG_SIZE	-4
#endif

#define CONFIG_DW_SERIAL
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_CLK		(115200 * 16)

#ifndef DM_SERIAL
#define CONFIG_SYS_NS16550_COM1	(PISTACHIO_UART0)
#define CONFIG_SYS_NS16550_COM2	(PISTACHIO_UART1)
#define CONFIG_CONS_INDEX		2
#endif

/*
 * Ethernet configuration
 */
/* to use Pistachio specific configuration */
#define CONFIG_PISTACHIO_DW_MAC

#define CONFIG_PHYLIB
#define CONFIG_PHY_MICREL
#define CONFIG_MII
#define CONFIG_AUTONEG_TIMEOUT		(150 * CONFIG_SYS_HZ)
#define CONFIG_ETH_DESIGNWARE

#define	CONFIG_SYS_RX_ETH_BUFFER	16

/*
 * USB configuration
 */
#define CONFIG_USB_DWC2_REG_ADDR	(PISTACHIO_USB)
#define CONFIG_USB_DWC2

/* Default option is NAND_BOOT */
#define NAND_BOOT

#ifdef NAND_BOOT
/* SPFI */
#define CONFIG_IMGTEC_SPFI
#define CONFIG_SPI_FLASH
/* NOR support */
#define CONFIG_CMD_SF
#define CONFIG_SYS_SPI1_CS0_GPIO	0
#define CONFIG_SYS_SPI1_CS1_GPIO	58
#define CONFIG_SPI_FLASH_WINBOND
/* NAND support */
#define CONFIG_MTD_SPI_NAND
#define CONFIG_MTD_SPI_NAND_DEVICES
#define CONFIG_SPI_NAND_GD5F
#define CONFIG_SYS_NAND_SELF_INIT
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SF_DEFAULT_BUS		1
#define CONFIG_SYS_NAND_CS		1
#define CONFIG_SYS_NAND_USE_FLASH_BBT
#define CONFIG_CMD_NAND
/* NAND pattitions */
#define CONFIG_LZO
#define CONFIG_RBTREE
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define MTDIDS_DEFAULT                  "nand0=spi-nand"
#define MTDPARTS_DEFAULT                "mtdparts=spi-nand:-(rootfs)"
#endif

/* MMC - Sdhost */
#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_DWMMC
#define CONFIG_BOUNCE_BUFFER

#define HAVE_BLOCK_DEVICE
#define CONFIG_PARTITION_UUIDS
#define CONFIG_CMD_FAT
#define CONFIG_CMD_EXT3
#define CONFIG_CMD_EXT4
#define CONFIG_DOS_PARTITION
#define CONFIG_ISO_PARTITION
#define CONFIG_FS_EXT4
#define CONFIG_FS_FAT

#define CONFIG_SYS_NO_FLASH

#define CONFIG_ENV_IS_NOWHERE
#define CONFIG_ENV_SIZE                 0x20000

#define USB_BOOTCOMMAND							\
	"setenv verify n;"						\
	"usb start;"							\
	"ext4load usb $usbdev:$usbpart $fdtaddr $bootdir$usbfdtfile;"	\
	"ext4load usb $usbdev:$usbpart $loadaddr $bootdir$bootfile;"	\
	"bootm $loadaddr - $fdtaddr;"

#define NAND_BOOTCOMMAND						\
	"setenv verify n;"						\
        "mtdparts default;"						\
	"ubi part rootfs;"						\
	"ubifsmount ubi:rootfs;"					\
        "ubifsload $loadaddr $botdir$bootfile;"				\
	"ubifsload $fdtaddr $bootdir$nandfdtfile;"			\
	"bootm $loadaddr - $fdtaddr;"

#ifndef NAND_BOOT

#define CONFIG_BOOTCOMMAND	USB_BOOTCOMMAND

#else

#define CONFIG_BOOTCOMMAND	NAND_BOOTCOMMAND

#endif

#define CONFIG_EXTRA_ENV_SETTINGS 					\
	"fdtaddr=0x000F0000\0"						\
	"usbfdtfile="PISTACHIO_BOARD_NAME".dtb\0"			\
	"nandfdtfile="PISTACHIO_BOARD_NAME"_nand.dtb\0"			\
	"bootfile=uImage.bin\0"						\
	"loadaddr=0x00400000\0"						\
	"bootdir=/\0"							\
	"usbdev=0\0"							\
	"usbpart=0\0"							\
	"usbboot="USB_BOOTCOMMAND"\0"					\
	"nandboot="NAND_BOOTCOMMAND"\0"					\
	"\0"

#define CONFIG_BOOTDELAY    2

/*
 * Commands
 */
#include <config_cmd_default.h>

#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_LOADB
#undef CONFIG_CMD_LOADS
#undef CONFIG_CMD_NFS

#define CONFIG_CMD_ELF

#define CONFIG_CMD_DNS
#define CONFIG_BOOTP_DNS
#define CONFIG_BOOTP_DNS2
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_SEND_HOSTNAME

#define CONFIG_CMD_NFS
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING

#define CONFIG_CMD_MMC

#define CONFIG_SYS_LONGHELP		/* verbose help, undef to save memory */

#endif /* _PISTACHIO_CONFIG_H */
