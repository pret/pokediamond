    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start MI_Init
MI_Init: ; 0x020CE648
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, #0x3
	bl MI_SetWramBank
	mov r0, #0x0
	bl MI_StopDma
	add sp, sp, #0x4
	ldmfd sp!, {lr}
	bx lr

