	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start OS_Init
OS_Init: ; 0x037F9B84
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	bl	OS_InitArena
	bl	PXI_Init
	bl	OS_InitLock
	bl	OS_InitIrqTable
	bl	OS_InitTick
	bl	OS_InitAlarm
	bl	OS_InitThread
	bl	OS_InitReset
	bl	CTRDG_Init
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
