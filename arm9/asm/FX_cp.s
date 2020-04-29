	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start FX_ModS32
FX_ModS32: ; 0x020C4E98
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr ip, _020C4EE0 ; =0x04000280
	mov lr, #0x0
	ldr r3, _020C4EE4 ; =0x04000290
	strh lr, [r12, #0x0]
	ldr r2, _020C4EE8 ; =0x04000298
	str r0, [r3, #0x0]
	str r1, [r2, #0x0]
	str lr, [r2, #0x4]
_020C4EC0:
	ldrh r0, [r12, #0x0]
	ands r0, r0, #0x8000
	bne _020C4EC0
	ldr r0, _020C4EEC ; =0x040002A8
	ldr r0, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C4EE0: .word 0x04000280
_020C4EE4: .word 0x04000290
_020C4EE8: .word 0x04000298
_020C4EEC: .word 0x040002A8

	arm_func_start FX_DivS32
FX_DivS32: ; 0x020C4EF0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr ip, _020C4F38 ; =0x04000280
	mov lr, #0x0
	ldr r3, _020C4F3C ; =0x04000290
	strh lr, [r12, #0x0]
	ldr r2, _020C4F40 ; =0x04000298
	str r0, [r3, #0x0]
	str r1, [r2, #0x0]
	str lr, [r2, #0x4]
_020C4F18:
	ldrh r0, [r12, #0x0]
	ands r0, r0, #0x8000
	bne _020C4F18
	ldr r0, _020C4F44 ; =0x040002A0
	ldr r0, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C4F38: .word 0x04000280
_020C4F3C: .word 0x04000290
_020C4F40: .word 0x04000298
_020C4F44: .word 0x040002A0

	arm_func_start FX_DivAsync
FX_DivAsync: ; 0x020C4F48
	ldr r2, _020C4F74 ; =0x04000280
	mov r12, #0x1
	ldr r3, _020C4F78 ; =0x04000290
	strh r12, [r2, #0x0]
	mov r12, #0x0
	str r12, [r3, #0x0]
	ldr r2, _020C4F7C ; =0x04000298
	str r0, [r3, #0x4]
	str r1, [r2, #0x0]
	str r12, [r2, #0x4]
	bx lr
	.balign 4
_020C4F74: .word 0x04000280
_020C4F78: .word 0x04000290
_020C4F7C: .word 0x04000298

	arm_func_start FX_GetSqrtResult
FX_GetSqrtResult: ; 0x020C4F80
	ldr r1, _020C4FA4 ; =0x040002B0
_020C4F84:
	ldrh r0, [r1, #0x0]
	ands r0, r0, #0x8000
	bne _020C4F84
	ldr r0, _020C4FA8 ; =0x040002B4
	ldr r0, [r0, #0x0]
	add r0, r0, #0x200
	mov r0, r0, lsr #0xa
	bx lr
	.balign 4
_020C4FA4: .word 0x040002B0
_020C4FA8: .word 0x040002B4

	arm_func_start FX_InvAsync
FX_InvAsync:
	ldr r1, _020C4FDC ; =0x04000280
	mov r3, #0x1
	ldr r2, _020C4FE0 ; =0x04000290
	strh r3, [r1, #0x0]
	mov r12, #0x0
	str r12, [r2, #0x0]
	mov r3, #0x1000
	ldr r1, _020C4FE4 ; =0x04000298
	str r3, [r2, #0x4]
	str r0, [r1, #0x0]
	str r12, [r1, #0x4]
	bx lr
	.balign 4
_020C4FDC: .word 0x04000280
_020C4FE0: .word 0x04000290
_020C4FE4: .word 0x04000298

	arm_func_start FX_GetDivResult
FX_GetDivResult: ; 0x020C4FE8
	ldr r1, _020C501C ; =0x04000280
_020C4FEC:
	ldrh r0, [r1, #0x0]
	ands r0, r0, #0x8000
	bne _020C4FEC
	ldr r1, _020C5020 ; =0x040002A0
	mov r0, #0x80000
	ldr r2, [r1, #0x0]
	ldr r1, [r1, #0x4]
	adds r0, r2, r0
	adc r1, r1, #0x0
	mov r0, r0, lsr #0x14
	orr r0, r0, r1, lsl #0xc
	bx lr
	.balign 4
_020C501C: .word 0x04000280
_020C5020: .word 0x040002A0

	arm_func_start FX_GetDivResultFx64c
FX_GetDivResultFx64c: ; 0x020C5024
	ldr r1, _020C5044 ; =0x04000280
_020C5028:
	ldrh r0, [r1, #0x0]
	ands r0, r0, #0x8000
	bne _020C5028
	ldr r1, _020C5048 ; =0x040002A0
	ldr r0, [r1, #0x0]
	ldr r1, [r1, #0x4]
	bx lr
	.balign 4
_020C5044: .word 0x04000280
_020C5048: .word 0x040002A0

	arm_func_start FX_Sqrt
FX_Sqrt: ; 0x020C504C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	addle sp, sp, #0x4
	movle r0, #0x0
	ldmleia sp!, {lr}
	bxle lr
	ldr r2, _020C5094 ; =0x040002B0
	mov r3, #0x1
	strh r3, [r2, #0x0]
	ldr r1, _020C5098 ; =0x040002B8
	mov r2, #0x0
	str r2, [r1, #0x0]
	str r0, [r1, #0x4]
	bl FX_GetSqrtResult
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C5094: .word 0x040002B0
_020C5098: .word 0x040002B8

	arm_func_start FX_Inv
FX_Inv: ; 0x020C509C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FX_InvAsync
	bl FX_GetDivResult
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FX_Div
FX_Div: ; 0x020C50B8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FX_DivAsync
	bl FX_GetDivResult
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
