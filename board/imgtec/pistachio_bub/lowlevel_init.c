/*
 * Low level initialization code for MIPS32 CPU-core SPL
 *
 * Copyright (c) 2015 Imagination Technologies
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include "clocks.h"
#include "lowlevel_init.h"
#include "mfio.h"

void spl_end(void) {
	/* for debugging purposes */
	while(1)
	{
	}
}


void spl_lowlevel_init(void) {
	int ret;

	/*
	 * System PLL divided by 2 -> 350 MHz
	 * The same frequency will be the input frequency for the SPFI block
	 */
	system_clk_setup(1);

	/*
	 * MIPS CPU dividers: division by 1 -> 546 MHz
	 * This is set up as we cannot make any assumption about
	 * the values set or not by the boot ROM code
	 */
	mips_clk_setup(0, 0);

	/* Setup system PLL at 700 MHz */
	ret = sys_pll_setup(2, 1, 13, 350);
	if (ret != CLOCKS_OK)
		return;

	/* Setup MIPS PLL at 546 MHz */
	ret = mips_pll_setup(2, 1, 1, 21);
	if (ret != CLOCKS_OK)
		return;

	/* Setup SPIM1 MFIOs */
	mfio_setup_spim1();

	/*
	 * Setup UART1 clock and MFIOs
	 * System PLL divided by 5 divided by 76 -> 1.8421 Mhz
	 */
	uart1_clk_setup(4, 75);
	mfio_setup_uart1();
	eth_clk_setup(0, 6);
	rom_clk_setup(1);
	usb_clk_setup(6, 2, 7);
}
