    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_Init
OS_Init: ; 0x020CC1B4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl OS_InitArena
	bl PXI_Init
	bl OS_InitLock
	bl OS_InitArenaEx
	bl OS_InitIrqTable
	bl OS_SetIrqStackChecker
	bl OS_InitException
	bl MI_Init
	bl OS_InitVAlarm
	bl OSi_InitVramExclusive
	bl OS_InitThread
	bl OS_InitReset
	bl CTRDG_Init
	bl CARD_Init
	bl PM_Init
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
