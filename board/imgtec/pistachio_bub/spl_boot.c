/*
 * Startup Code for MIPS32 CPU-core SPL
 *
 * Copyright (c) 2015 Imagination Technologies
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/mipsregs.h>
#include <asm/mmu.h>
#include <common.h>
#include <linux/sizes.h>
#include <spl.h>

#include "ddr_init.h"
#include "lowlevel_init.h"

u32 spl_boot_device(void)
{
	return BOOT_DEVICE_SPI;
}

void spl_board_init(void)
{
	preloader_console_init();
	spl_image.flags = 0;
}

static void soc_mmu_init(void)
{
	/*
	 * Reserve 1MB before the location where U-Boot will be executed
	 * for the header. U-Boot will be loaded together with header
	 * in a way that places the beginning of the text segment at
	 * CONFIG_SYS_TEXT_BASE, having the header at lower addresses.
	 */
	u32 header_mem_reserved = 1 * 1024 * 1024;

	write_c0_wired(0);
	assert(!identity_map((u32)CONFIG_SYS_SOC_REG_BASE,
			     CONFIG_SYS_SOC_REG_SIZE, C0_ENTRYLO_UC));
	/*
	 * Map the u-boot code and data used before relocation
	 * The memory before CONFIG_SYS_TEXT_BASE -header_mem_reserved
         * is kept unmapped as NULL guard
	 */
	assert(!identity_map((u32)CONFIG_SYS_TEXT_BASE - header_mem_reserved,
			CONFIG_UBOOT_EARLY_MEM + header_mem_reserved,
			C0_ENTRYLO_WB));
}

u32 sb(void)
{
	soc_mmu_init();
	spl_lowlevel_init();
#if defined(CONFIG_DRAM_DDR2)
	init_ddr2();
#elif defined(CONFIG_DRAM_DDR3)
	init_ddr3();
#endif
	board_init_r(NULL, 0);
	spl_end();
	return 0;
}
