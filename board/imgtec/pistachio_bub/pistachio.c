/*
 * Copyright (C) 2015 Imagination Technologies
 * Author: Govindraj Raja <govindraj.raja@imgtec.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dwmmc.h>
#include <fdtdec.h>
#include <miiphy.h>
#include <malloc.h>
#include <netdev.h>
#include <serial.h>

#include <asm/addrspace.h>
#include <asm/io.h>
#include <asm/pistachio.h>
#include <asm/mipsregs.h>

#include "mfio.h"

DECLARE_GLOBAL_DATA_PTR;

phys_size_t initdram(int board_type)
{
#ifdef CONFIG_OF_CONTROL
	int node;
	fdt_addr_t addr;
        fdt_size_t size;

	node  = fdt_path_offset(gd->fdt_blob, "/memory");
	addr = fdtdec_get_addr_size(gd->fdt_blob, node, "reg", &size);
	if (addr == FDT_ADDR_T_NONE || size == 0) {
		printf("\n DRAM: Can't get mem size\n");
		return -1;
	}

	return (phys_size_t)size;
#else
	return CONFIG_SYS_MEM_SIZE;
#endif

}

int checkboard(void)
{
	return 0;
}

/*
 * Print CPU information
 */
int print_cpuinfo(void)
{
	printf("MIPS(interAptiv): IMG Pistachio %dMHz.\n", CONFIG_SYS_MHZ);
	return 0;
}

char *addr= "01:23:45:67:89:AB";
uchar enetaddr[6];

int board_eth_init(bd_t *bs)
{
	mfio_setup_ethernet();

	eth_parse_enetaddr(addr, enetaddr);
	eth_setenv_enetaddr("ethaddr", enetaddr);

#ifndef CONFIG_DM_ETH
	if (designware_initialize(PISTACHIO_ETHERNET,
			PHY_INTERFACE_MODE_RMII) >= 0)
		return 1;
#endif

	return 0;
}

int board_mmc_init(bd_t *bis)
{
	struct dwmci_host *host = NULL;

	mfio_setup_mmc();

	host = malloc(sizeof(struct dwmci_host));
	if (!host) {
		printf("dwmci_host malloc fail!\n");
		return 1;
	}

	memset(host, 0, sizeof(struct dwmci_host));
	host->name = "Synopsys Mobile storage";
	host->ioaddr = (void *)0x18142000;
	host->buswidth = 4;
	host->dev_index = 0;
	host->bus_hz = 200000000;

	add_dwmci(host, host->bus_hz, 25000000);

	return 0;
}

void _machine_restart(void)
{
}

int board_early_init_f(void)
{
	return 0;
}

int misc_init_r(void)
{
	return 0;
}

#ifndef DM_SERIAL
struct serial_device *default_serial_console(void)
{
	return &eserial2_device;
}
#endif
