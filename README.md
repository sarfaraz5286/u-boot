# Using u-boot on Creator (Ci40) Marduk platform

### How to build/cross-compile for Ci40:

	$ export CROSS_COMPILE=/path/to/mips-toolchain/mips-toolchain-prefix
	$ make pistachio_marduk_defconfig
	$ make

This will generate u-boot-pistachio-nor.img

Note: Using OpenWrt's toolchain toolchain-mipsel_mips32_gcc-5.2.0_musl-1.1.11 will require [this patch](http://lists.denx.de/pipermail/u-boot/2015-July/217911.html) to be applied.

### How to flash on Ci40:

1. [Load OpenWrt](https://github.com/IMGCreator/openwrt/blob/master-pistachio/README.md)

2. Erase and write u-boot image on bootloader partition of Ci40

		$ flashcp -v u-boot-pistachio-nor.img /dev/mtd0

	Note: flashcp needs to be manually selected in OpneWrt menuconfig

		Base system -> busybox -> Cutomize busybox options -> Miscellaneous Utilities -> flashcp

3. Reboot

		$ reboot

_Please be aware that you may brick the board if you flashed a wrong bootloader. Only way to re-cover back the board is to use Dedi-prog SF100 programmer to flash the pre-built bootloader again._
