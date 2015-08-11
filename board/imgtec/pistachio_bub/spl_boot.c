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

#include "lowlevel_init.h"

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
	spl_end();
	return 0;
}