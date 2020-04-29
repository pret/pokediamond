	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start GXx_SetMasterBrightness_
GXx_SetMasterBrightness_: ; 0x020C5978
	cmp r1, #0x0
	moveq r1, #0x0
	streqh r1, [r0, #0x0]
	bxeq lr
	cmp r1, #0x0
	orrgt r1, r1, #0x4000
	strgth r1, [r0, #0x0]
	rsble r1, r1, #0x0
	orrle r1, r1, #0x8000
	strleh r1, [r0, #0x0]
	bx lr

	arm_func_start GXS_SetGraphicsMode
GXS_SetGraphicsMode: ; 0x020C59A4
	ldr r2, _020C59BC ; =0x04001000
	ldr r1, [r2, #0x0]
	bic r1, r1, #0x7
	orr r0, r1, r0
	str r0, [r2, #0x0]
	bx lr
	.balign 4
_020C59BC: .word 0x04001000

	arm_func_start GX_SetGraphicsMode
GX_SetGraphicsMode: ; 0x020C59C0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, _020C5A28 ; =0x02106810
	mov lr, #0x4000000
	ldrh r12, [r3, #0x0]
	ldr lr, [lr, #0x0]
	ldr r3, _020C5A2C ; =0x021D33C0
	cmp r12, #0x0
	strh r0, [r3, #0x0]
	ldr r3, _020C5A30 ; =0xFFF0FFF0
	moveq r0, #0x0
	and r3, lr, r3
	orr r0, r3, r0, lsl #0x10
	orr r0, r1, r0
	orr r1, r0, r2, lsl #0x3
	mov r12, #0x4000000
	ldr r0, _020C5A2C ; =0x021D33C0
	str r1, [r12, #0x0]
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	ldreq r0, _020C5A28 ; =0x02106810
	moveq r1, #0x0
	streqh r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C5A28: .word 0x02106810
_020C5A2C: .word 0x021D33C0
_020C5A30: .word 0xFFF0FFF0

	arm_func_start GX_DispOn
GX_DispOn: ; 0x020C5A34
	ldr r0, _020C5A78 ; =0x021D33C0
	ldr r1, _020C5A7C ; =0x02106810
	ldrh r2, [r0, #0x0]
	mov r0, #0x1
	strh r0, [r1, #0x0]
	cmp r2, #0x0
	moveq r1, #0x4000000
	ldreq r0, [r1, #0x0]
	orreq r0, r0, #0x10000
	streq r0, [r1, #0x0]
	bxeq lr
	mov r1, #0x4000000
	ldr r0, [r1, #0x0]
	bic r0, r0, #0x30000
	orr r0, r0, r2, lsl #0x10
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020C5A78: .word 0x021D33C0
_020C5A7C: .word 0x02106810

	arm_func_start GX_DispOff
GX_DispOff: ; 0x020C5A80
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, #0x4000000
	ldr r12, [lr, #0x0]
	ldr r1, _020C5AC0 ; =0x02106810
	and r2, r12, #0x30000
	mov r3, #0x0
	ldr r0, _020C5AC4 ; =0x021D33C0
	mov r2, r2, lsr #0x10
	strh r3, [r1, #0x0]
	strh r2, [r0, #0x0]
	bic r0, r12, #0x30000
	str r0, [lr, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C5AC0: .word 0x02106810
_020C5AC4: .word 0x021D33C0

	arm_func_start GX_VBlankIntr
GX_VBlankIntr: ; 0x020C5AC8
	ldr r2, _020C5AF4 ; =0x04000004
	cmp r0, #0x0
	ldrh r0, [r2, #0x0]
	ldrneh r1, [r2, #0x0]
	and r0, r0, #0x8
	orrne r1, r1, #0x8
	strneh r1, [r2, #0x0]
	ldreqh r1, [r2, #0x0]
	biceq r1, r1, #0x8
	streqh r1, [r2, #0x0]
	bx lr
	.balign 4
_020C5AF4: .word 0x04000004

	arm_func_start GX_HBlankIntr
GX_HBlankIntr: ; 0x020C5AF8
	ldr r2, _020C5B24 ; =0x04000004
	cmp r0, #0x0
	ldrh r0, [r2, #0x0]
	ldrneh r1, [r2, #0x0]
	and r0, r0, #0x10
	orrne r1, r1, #0x10
	strneh r1, [r2, #0x0]
	ldreqh r1, [r2, #0x0]
	biceq r1, r1, #0x10
	streqh r1, [r2, #0x0]
	bx lr
	.balign 4
_020C5B24: .word 0x04000004

	arm_func_start GX_Init
GX_Init: ; 0x020C5B28
	stmdb sp!, {r4-r6,lr}
	ldr r3, _020C5C68 ; =0x04000304
	ldr r0, _020C5C6C ; =0xFFFFFDF1
	ldrh r2, [r3, #0x0]
	ldr r1, _020C5C70 ; =0x0000020E
	orr r2, r2, #0x8000
	strh r2, [r3, #0x0]
	ldrh r2, [r3, #0x0]
	and r0, r2, r0
	orr r0, r0, r1
	strh r0, [r3, #0x0]
	ldrh r0, [r3, #0x0]
	orr r0, r0, #0x1
	strh r0, [r3, #0x0]
	bl GX_InitGXState
	ldr r5, _020C5C74 ; =0x021D33BC
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	bne _020C5B9C
	mvn r4, #0x2
_020C5B78:
	bl OS_GetLockID
	mov r6, r0
	cmp r6, r4
	bne _020C5B8C
	bl OS_Terminate
_020C5B8C:
	strh r6, [r5, #0x0]
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	beq _020C5B78
_020C5B9C:
	ldr r0, _020C5C78 ; =0x04000004
	mov r2, #0x0
	strh r2, [r0, #0x0]
	mov r1, #0x4000000
	ldr r0, _020C5C7C ; =0x02106814
	str r2, [r1, #0x0]
	ldr r0, [r0, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C5BF4
	ldr r1, _020C5C80 ; =0x04000008
	mov r3, #0x60
	bl MI_DmaFill32
	ldr r1, _020C5C84 ; =0x0400006C
	mov r2, #0x0
	ldr r0, _020C5C7C ; =0x02106814
	strh r2, [r1, #0x0]
	ldr r0, [r0, #0x0]
	ldr r1, _020C5C88 ; =0x04001000
	mov r3, #0x70
	bl MI_DmaFill32
	b _020C5C1C
_020C5BF4:
	ldr r1, _020C5C80 ; =0x04000008
	mov r0, r2
	mov r2, #0x60
	bl MIi_CpuClear32
	ldr r3, _020C5C84 ; =0x0400006C
	mov r0, #0x0
	ldr r1, _020C5C88 ; =0x04001000
	mov r2, #0x70
	strh r0, [r3, #0x0]
	bl MIi_CpuClear32
_020C5C1C:
	ldr r1, _020C5C8C ; =0x04000020
	mov r2, #0x100
	ldr r0, _020C5C90 ; =0x04000026
	strh r2, [r1, #0x0]
	ldr r1, _020C5C94 ; =0x04000030
	strh r2, [r0, #0x0]
	ldr r0, _020C5C98 ; =0x04000036
	strh r2, [r1, #0x0]
	ldr r1, _020C5C9C ; =0x04001020
	strh r2, [r0, #0x0]
	ldr r0, _020C5CA0 ; =0x04001026
	strh r2, [r1, #0x0]
	ldr r1, _020C5CA4 ; =0x04001030
	strh r2, [r0, #0x0]
	ldr r0, _020C5CA8 ; =0x04001036
	strh r2, [r1, #0x0]
	strh r2, [r0, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C5C68: .word 0x04000304
_020C5C6C: .word 0xFFFFFDF1
_020C5C70: .word 0x0000020E
_020C5C74: .word 0x021D33BC
_020C5C78: .word 0x04000004
_020C5C7C: .word 0x02106814
_020C5C80: .word 0x04000008
_020C5C84: .word 0x0400006C
_020C5C88: .word 0x04001000
_020C5C8C: .word 0x04000020
_020C5C90: .word 0x04000026
_020C5C94: .word 0x04000030
_020C5C98: .word 0x04000036
_020C5C9C: .word 0x04001020
_020C5CA0: .word 0x04001026
_020C5CA4: .word 0x04001030
_020C5CA8: .word 0x04001036
