/*
 * Copyright (C) 2015 Imagination Technologies
 * Author: Shraddha Chaudhari <shraddha.chaudhari@imgtec.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <asm/io.h>

#define PISTACHIO_SCRATCHPAD_BASE	0x18102120
#define NUM_OF_REG			8
#define REG_SIZE			4

static int do_scratchpad_read(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	ulong index;
	unsigned int val;

	if (argc < 2)
		return CMD_RET_USAGE;

	index = simple_strtoul(argv[1], NULL, 16);

	if(index >= NUM_OF_REG)
		return CMD_RET_USAGE;

	index *= REG_SIZE;

	val = readl(PISTACHIO_SCRATCHPAD_BASE + index);
	printf("0x%x\n",val);
	return 0;
}

static int do_scratchpad_write(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	ulong index, value;

	if (argc < 3)
		return CMD_RET_USAGE;

	index = simple_strtoul(argv[1], NULL, 16);
	value = simple_strtoul(argv[2], NULL, 16);

	if(index >= NUM_OF_REG)
		return CMD_RET_USAGE;

	index *= REG_SIZE;

	writel(value, PISTACHIO_SCRATCHPAD_BASE + index);

	return 0;
}

U_BOOT_CMD(
	scratchpad_read,	2,	0,	do_scratchpad_read,
	"display scratchpad register",
	"[0-7] "
);

U_BOOT_CMD(
	scratchpad_write,	3,	0,	do_scratchpad_write,
	"write scratchpad register",
	"[0-7] value"
);
