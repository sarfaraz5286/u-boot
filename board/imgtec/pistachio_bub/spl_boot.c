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
	write_c0_wired(0);
	/* Map SOC registers only; DRAM will be mapped later */
	assert(!identity_map((u32)CONFIG_SYS_SOC_REG_BASE,
			     CONFIG_SYS_SOC_REG_SIZE, C0_ENTRYLO_UC));
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
