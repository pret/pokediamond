	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start WM_EndKeySharing
WM_EndKeySharing: ; 0x020DAD3C
	ldr ip, _020DAD44 ; =WM_EndDataSharing
	bx r12
	.balign 4
_020DAD44: .word WM_EndDataSharing

	arm_func_start WM_StartKeySharing
WM_StartKeySharing: ; 0x020DAD48
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020DAD70 ; =0x0000FFFF
	mov r12, #0x1
	mov r3, #0x2
	str r12, [sp, #0x0]
	bl WM_StartDataSharing
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DAD70: .word 0x0000FFFF
