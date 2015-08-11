/*
 * Startup Code for MIPS32 CPU-core SPL
 *
 * Copyright (c) 2015 Imagination Technologies
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm-offsets.h>
#include <config.h>
#include <asm/asm.h>
#include <asm/mipsregs.h>
#include <asm/regdef.h>

#define CONFIG_SYS_INIT_SP_ADDR (CONFIG_SYS_SRAM_BASE + \
				CONFIG_SYS_SRAM_SIZE)

/* Prevent assembler from "optimizing" this code. */
.set	noreorder
.section ".text._start", "ax", %progbits
.globl _start

_start:
	.align	PTRLOG
	bal	1f
	nop
	PTR	_gp
1:
	PTR_L	gp, 0(ra)

	/* Init cause register */
	mtc0	zero, CP0_CAUSE

	/* Init timer registers */
	mtc0	zero, CP0_COUNT
	mtc0	zero, CP0_COMPARE

	/* Initialize bss */
	la	t0, __bss_start
	move	k0, t0
	sw	zero, (t0)
	la	t1, __bss_end - 4
	blt	t1, t0, stack
	nop
clear_bss:
	addiu	t0, 4
	sw	zero, (t0)
	bne	t0, t1, clear_bss
	nop
stack:
	/* Set up temporary stack */
	PTR_LI	t0, -4
	PTR_LI	t1, CONFIG_SYS_INIT_SP_ADDR
	# Force 4 byte alignment
	and	sp, t1, t0
	move	fp, sp

	/* Branch to sb */
	PTR_LA	t9, sb
	jr	t9
	move	ra, zero
	/* Hopefully it does not return */
5:	nop
	b	5b
	nop

