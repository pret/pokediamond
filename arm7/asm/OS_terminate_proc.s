	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start OS_Terminate
OS_Terminate: ; 0x037FB1F0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #0
	bl	CTRDG_VibPulseEdgeUpdate
_037FB200:
	bl	OS_DisableInterrupts
	bl	FUN_037F8530
	b	_037FB200
