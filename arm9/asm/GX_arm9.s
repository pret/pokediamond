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

	arm_func_start GX_InitGXState
GX_InitGXState: ; 0x020C5CAC
	ldr r0, _020C5D14 ; =0x021D33C4
	mov r3, #0x0
	ldr r2, _020C5D18 ; =0x04000240
	strh r3, [r0, #0x0]
	strh r3, [r0, #0x2]
	strh r3, [r0, #0x4]
	strh r3, [r0, #0x6]
	strh r3, [r0, #0x8]
	strh r3, [r0, #0xa]
	strh r3, [r0, #0xc]
	strh r3, [r0, #0xe]
	strh r3, [r0, #0x10]
	strh r3, [r0, #0x12]
	strh r3, [r0, #0x14]
	strh r3, [r0, #0x16]
	strh r3, [r0, #0x18]
	ldr r1, _020C5D1C ; =0x04000244
	str r3, [r2, #0x0]
	ldr r0, _020C5D20 ; =0x04000245
	strb r3, [r1, #0x0]
	ldr r1, _020C5D24 ; =0x04000246
	strb r3, [r0, #0x0]
	ldr r0, _020C5D28 ; =0x04000248
	strb r3, [r1, #0x0]
	strh r3, [r0, #0x0]
	bx lr
	.balign 4
_020C5D14: .word 0x021D33C4
_020C5D18: .word 0x04000240
_020C5D1C: .word 0x04000244
_020C5D20: .word 0x04000245
_020C5D24: .word 0x04000246
_020C5D28: .word 0x04000248

	arm_func_start GX_GetBankForSubOBJExtPltt
GX_GetBankForSubOBJExtPltt: ; 0x020C5D2C
	ldr r0, _020C5D38 ; =0x021D33C4
	ldrh r0, [r0, #0x18]
	bx lr
	.balign 4
_020C5D38: .word 0x021D33C4

	arm_func_start GX_GetBankForSubBGExtPltt
GX_GetBankForSubBGExtPltt: ; 0x020C5D3C
	ldr r0, _020C5D48 ; =0x021D33C4
	ldrh r0, [r0, #0x16]
	bx lr
	.balign 4
_020C5D48: .word 0x021D33C4

	arm_func_start GX_GetBankForSubOBJ
GX_GetBankForSubOBJ: ; 0x020C5D4C
	ldr r0, _020C5D58 ; =0x021D33C4
	ldrh r0, [r0, #0x14]
	bx lr
	.balign 4
_020C5D58: .word 0x021D33C4

	arm_func_start GX_GetBankForSubBGExtPltt_2
GX_GetBankForSubBGExtPltt_2: ; 0x020C5D5C
	ldr r0, _020C5D68 ; =0x021D33C4
	ldrh r0, [r0, #0x12]
	bx lr
	.balign 4
_020C5D68: .word 0x021D33C4

	arm_func_start GX_GetBankForLCDC
GX_GetBankForLCDC: ; 0x020C5D6C
	ldr r0, _020C5D78 ; =0x021D33C4
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4
_020C5D78: .word 0x021D33C4

	arm_func_start GX_GetBankForTexPltt
GX_GetBankForTexPltt: ; 0x020C5D7C
	ldr r0, _020C5D88 ; =0x021D33C4

	arm_func_start FUN_020C5D80
FUN_020C5D80: ; 0x020C5D80
	ldrh r0, [r0, #0xa]
	bx lr
	.balign 4
_020C5D88: .word 0x021D33C4

	arm_func_start FUN_020C5D8C
FUN_020C5D8C: ; 0x020C5D8C
	ldr r0, _020C5D98 ; =0x021D33C4
	ldrh r0, [r0, #0x8]
	bx lr
	.balign 4
_020C5D98: .word 0x021D33C4

	arm_func_start GX_GetBankForOBJExtPltt
GX_GetBankForOBJExtPltt: ; 0x020C5D9C
	ldr r0, _020C5DA8 ; =0x021D33C4
	ldrh r0, [r0, #0x10]
	bx lr
	.balign 4
_020C5DA8: .word 0x021D33C4

	arm_func_start GX_GetBankForBGExtPltt
GX_GetBankForBGExtPltt: ; 0x020C5DAC
	ldr r0, _020C5DB8 ; =0x021D33C4
	ldrh r0, [r0, #0xe]
	bx lr
	.balign 4
_020C5DB8: .word 0x021D33C4

	arm_func_start GX_GetBankForOBJ
GX_GetBankForOBJ: ; 0x020C5DBC
	ldr r0, _020C5DC8 ; =0x021D33C4
	ldrh r0, [r0, #0x4]
	bx lr
	.balign 4
_020C5DC8: .word 0x021D33C4

	arm_func_start GX_GetBankForBGExtPltt_2
GX_GetBankForBGExtPltt_2: ; 0x020C5DCC
	ldr r0, _020C5DD8 ; =0x021D33C4
	ldrh r0, [r0, #0x2]
	bx lr
	.balign 4
_020C5DD8: .word 0x021D33C4

	arm_func_start GX_DisableBankForSubOBJExtPltt
GX_DisableBankForSubOBJExtPltt: ; 0x020C5DDC
	ldr r2, _020C5DF8 ; =0x04001000
	ldr ip, _020C5DFC ; =FUN_020C5F28
	ldr r1, [r2, #0x0]
	ldr r0, _020C5E00 ; =0x021D33DC
	bic r1, r1, #0x80000000
	str r1, [r2, #0x0]
	bx r12
	.balign 4
_020C5DF8: .word 0x04001000
_020C5DFC: .word FUN_020C5F28
_020C5E00: .word 0x021D33DC

	arm_func_start FUN_020C5E04
FUN_020C5E04: ; 0x020C5E04
	ldr r2, _020C5E20 ; =0x04001000
	ldr ip, _020C5E24 ; =FUN_020C5F28
	ldr r1, [r2, #0x0]
	ldr r0, _020C5E28 ; =0x021D33DA
	bic r1, r1, #0x40000000
	str r1, [r2, #0x0]
	bx r12
	.balign 4
_020C5E20: .word 0x04001000
_020C5E24: .word FUN_020C5F28
_020C5E28: .word 0x021D33DA

	arm_func_start GX_DisableBankForSubOBJExtPltt_2
GX_DisableBankForSubOBJExtPltt_2: ; 0x020C5E2C
	ldr ip, _020C5E38 ; =FUN_020C5F28
	ldr r0, _020C5E3C ; =0x021D33D8
	bx r12
	.balign 4
_020C5E38: .word FUN_020C5F28
_020C5E3C: .word 0x021D33D8

	arm_func_start GX_DisableBankForSubBGExtPltt
GX_DisableBankForSubBGExtPltt: ; 0x020C5E40
	ldr ip, _020C5E4C ; =FUN_020C5F28
	ldr r0, _020C5E50 ; =0x021D33D6
	bx r12
	.balign 4
_020C5E4C: .word FUN_020C5F28
_020C5E50: .word 0x021D33D6

	arm_func_start GX_DisableBankForLCDC
GX_DisableBankForLCDC: ; 0x020C5E54
	ldr ip, _020C5E60 ; =FUN_020C5F28
	ldr r0, _020C5E64 ; =0x021D33C4
	bx r12
	.balign 4
_020C5E60: .word FUN_020C5F28
_020C5E64: .word 0x021D33C4

	arm_func_start GX_DisableBankForARM7
GX_DisableBankForARM7: ; 0x020C5E68
	ldr ip, _020C5E74 ; =FUN_020C5F28
	ldr r0, _020C5E78 ; =0x021D33CA
	bx r12
	.balign 4
_020C5E74: .word FUN_020C5F28
_020C5E78: .word 0x021D33CA

	arm_func_start GX_DisableBankForClearImage
GX_DisableBankForClearImage: ; 0x020C5E7C
	ldr ip, _020C5E88 ; =FUN_020C5F28
	ldr r0, _020C5E8C ; =0x021D33D0
	bx r12
	.balign 4
_020C5E88: .word FUN_020C5F28
_020C5E8C: .word 0x021D33D0

	arm_func_start GX_DisableBankForTexPltt
GX_DisableBankForTexPltt: ; 0x020C5E90
	ldr ip, _020C5E9C ; =FUN_020C5F28
	ldr r0, _020C5EA0 ; =0x021D33CE
	bx r12
	.balign 4
_020C5E9C: .word FUN_020C5F28
_020C5EA0: .word 0x021D33CE

	arm_func_start GX_DisableBankForTexPltt_2
GX_DisableBankForTexPltt_2: ; 0x020C5EA4
	ldr ip, _020C5EB0 ; =FUN_020C5F28
	ldr r0, _020C5EB4 ; =0x021D33CC
	bx r12
	.balign 4
_020C5EB0: .word FUN_020C5F28
_020C5EB4: .word 0x021D33CC

	arm_func_start GX_DisableBankForOBJExtPltt
GX_DisableBankForOBJExtPltt: ; 0x020C5EB8
	mov r2, #0x4000000
	ldr r1, [r2, #0x0]
	ldr ip, _020C5ED4 ; =FUN_020C5F28
	bic r1, r1, #0x80000000
	ldr r0, _020C5ED8 ; =0x021D33D4
	str r1, [r2, #0x0]
	bx r12
	.balign 4
_020C5ED4: .word FUN_020C5F28
_020C5ED8: .word 0x021D33D4

	arm_func_start GX_DisableBankForBGExtPltt
GX_DisableBankForBGExtPltt: ; 0x020C5EDC
	mov r2, #0x4000000
	ldr r1, [r2, #0x0]
	ldr ip, _020C5EF8 ; =FUN_020C5F28
	bic r1, r1, #0x40000000
	ldr r0, _020C5EFC ; =0x021D33D2
	str r1, [r2, #0x0]
	bx r12
	.balign 4
_020C5EF8: .word FUN_020C5F28
_020C5EFC: .word 0x021D33D2

	arm_func_start GX_DisableBankForOBJExtPltt_2
GX_DisableBankForOBJExtPltt_2: ; 0x020C5F00
	ldr ip, _020C5F0C ; =FUN_020C5F28
	ldr r0, _020C5F10 ; =0x021D33C8
	bx r12
	.balign 4
_020C5F0C: .word FUN_020C5F28
_020C5F10: .word 0x021D33C8

	arm_func_start disableBankForX_
disableBankForX_: ; 0x020C5F14
	ldr ip, _020C5F20 ; =FUN_020C5F28
	ldr r0, _020C5F24 ; =0x021D33C6
	bx r12
	.balign 4
_020C5F20: .word FUN_020C5F28
_020C5F24: .word 0x021D33C6

	arm_func_start FUN_020C5F28
FUN_020C5F28: ; 0x020C5F28
	stmdb sp!, {r4,lr}
	ldrh r4, [r0, #0x0]
	mov r1, #0x0
	strh r1, [r0, #0x0]
	ands r0, r4, #0x1
	ldrne r0, _020C5FE4 ; =0x04000240
	strneb r1, [r0, #0x0]
	ands r0, r4, #0x2
	ldrne r0, _020C5FE8 ; =0x04000241
	movne r1, #0x0
	strneb r1, [r0, #0x0]
	ands r0, r4, #0x4
	ldrne r0, _020C5FEC ; =0x04000242
	movne r1, #0x0
	strneb r1, [r0, #0x0]
	ands r0, r4, #0x8
	ldrne r0, _020C5FF0 ; =0x04000243
	movne r1, #0x0
	strneb r1, [r0, #0x0]
	ands r0, r4, #0x10
	ldrne r0, _020C5FF4 ; =0x04000244
	movne r1, #0x0
	strneb r1, [r0, #0x0]
	ands r0, r4, #0x20
	ldrne r0, _020C5FF8 ; =0x04000245
	movne r1, #0x0
	strneb r1, [r0, #0x0]
	ands r0, r4, #0x40
	ldrne r0, _020C5FFC ; =0x04000246
	movne r1, #0x0
	strneb r1, [r0, #0x0]
	ands r0, r4, #0x80
	ldrne r0, _020C6000 ; =0x04000248
	movne r1, #0x0
	strneb r1, [r0, #0x0]
	ands r0, r4, #0x100
	ldrne r0, _020C6004 ; =0x04000249
	movne r1, #0x0
	strneb r1, [r0, #0x0]
	ldr r1, _020C6008 ; =0x021D33BC
	mov r0, r4, lsl #0x10
	ldrh r1, [r1, #0x0]
	mov r0, r0, lsr #0x10
	bl OSi_UnlockVram
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C5FE4: .word 0x04000240
_020C5FE8: .word 0x04000241
_020C5FEC: .word 0x04000242
_020C5FF0: .word 0x04000243
_020C5FF4: .word 0x04000244
_020C5FF8: .word 0x04000245
_020C5FFC: .word 0x04000246
_020C6000: .word 0x04000248
_020C6004: .word 0x04000249
_020C6008: .word 0x021D33BC

	arm_func_start GX_ResetBankForSubOBJ
GX_ResetBankForSubOBJ: ; 0x020C600C
	ldr r2, _020C6028 ; =0x04001000
	ldr ip, _020C602C ; =FUN_020C6130
	ldr r1, [r2, #0x0]
	ldr r0, _020C6030 ; =0x021D33DC
	bic r1, r1, #0x80000000
	str r1, [r2, #0x0]
	bx r12
	.balign 4
_020C6028: .word 0x04001000
_020C602C: .word FUN_020C6130
_020C6030: .word 0x021D33DC

	arm_func_start FUN_020C6034
FUN_020C6034: ; 0x020C6034
	ldr r2, _020C6050 ; =0x04001000
	ldr ip, _020C6054 ; =FUN_020C6130
	ldr r1, [r2, #0x0]
	ldr r0, _020C6058 ; =0x021D33DA
	bic r1, r1, #0x40000000
	str r1, [r2, #0x0]
	bx r12
	.balign 4
_020C6050: .word 0x04001000
_020C6054: .word FUN_020C6130
_020C6058: .word 0x021D33DA

	arm_func_start FUN_020C605C
FUN_020C605C: ; 0x020C605C
	ldr ip, _020C6068 ; =FUN_020C6130
	ldr r0, _020C606C ; =0x021D33D8
	bx r12
	.balign 4
_020C6068: .word FUN_020C6130
_020C606C: .word 0x021D33D8

	arm_func_start GX_ResetBankForSubBG
GX_ResetBankForSubBG: ; 0x020C6070
	ldr ip, _020C607C ; =FUN_020C6130
	ldr r0, _020C6080 ; =0x021D33D6
	bx r12
	.balign 4
_020C607C: .word FUN_020C6130
_020C6080: .word 0x021D33D6

	arm_func_start GX_ResetBankForClearImage
GX_ResetBankForClearImage: ; 0x020C6084
	ldr ip, _020C6090 ; =FUN_020C6130
	ldr r0, _020C6094 ; =0x021D33D0
	bx r12
	.balign 4
_020C6090: .word FUN_020C6130
_020C6094: .word 0x021D33D0

	arm_func_start GX_ResetBankForTexPltt
GX_ResetBankForTexPltt: ; 0x020C6098
	ldr ip, _020C60A4 ; =FUN_020C6130
	ldr r0, _020C60A8 ; =0x021D33CE
	bx r12
	.balign 4
_020C60A4: .word FUN_020C6130
_020C60A8: .word 0x021D33CE

	arm_func_start GX_ResetBankForTex
GX_ResetBankForTex: ; 0x020C60AC
	ldr ip, _020C60B8 ; =FUN_020C6130
	ldr r0, _020C60BC ; =0x021D33CC
	bx r12
	.balign 4
_020C60B8: .word FUN_020C6130
_020C60BC: .word 0x021D33CC

	arm_func_start GX_ResetBankForOBJExtPltt
GX_ResetBankForOBJExtPltt: ; 0x020C60C0
	mov r2, #0x4000000
	ldr r1, [r2, #0x0]
	ldr ip, _020C60DC ; =FUN_020C6130
	bic r1, r1, #0x80000000
	ldr r0, _020C60E0 ; =0x021D33D4
	str r1, [r2, #0x0]
	bx r12
	.balign 4
_020C60DC: .word FUN_020C6130
_020C60E0: .word 0x021D33D4

	arm_func_start GX_ResetBankForBGExtPltt
GX_ResetBankForBGExtPltt: ; 0x020C60E4
	mov r2, #0x4000000
	ldr r1, [r2, #0x0]
	ldr ip, _020C6100 ; =FUN_020C6130
	bic r1, r1, #0x40000000
	ldr r0, _020C6104 ; =0x021D33D2
	str r1, [r2, #0x0]
	bx r12
	.balign 4
_020C6100: .word FUN_020C6130
_020C6104: .word 0x021D33D2

	arm_func_start GX_ResetBankForOBJ
GX_ResetBankForOBJ: ; 0x020C6108
	ldr ip, _020C6114 ; =FUN_020C6130
	ldr r0, _020C6118 ; =0x021D33C8
	bx r12
	.balign 4
_020C6114: .word FUN_020C6130
_020C6118: .word 0x021D33C8

	arm_func_start GX_ResetBankForBG
GX_ResetBankForBG: ; 0x020C611C
	ldr ip, _020C6128 ; =FUN_020C6130
	ldr r0, _020C612C ; =0x021D33C6
	bx r12
	.balign 4
_020C6128: .word FUN_020C6130
_020C612C: .word 0x021D33C6

	arm_func_start FUN_020C6130
FUN_020C6130: ; 0x020C6130
	stmdb sp!, {r4,lr}
	ldrh r4, [r0, #0x0]
	mov r2, #0x0
	ldr r1, _020C6164 ; =0x021D33C4
	strh r2, [r0, #0x0]
	ldrh r2, [r1, #0x0]
	mov r0, r4
	orr r2, r2, r4
	strh r2, [r1, #0x0]
	bl GX_VRAMCNT_SetLCDC_
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C6164: .word 0x021D33C4

	arm_func_start GX_SetBankForSubOBJExtPltt
GX_SetBankForSubOBJExtPltt: ; 0x020C6168
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020C61E8 ; =0x021D33C4
	mvn r12, r0
	ldrh r2, [r1, #0x18]
	ldrh r3, [r1, #0x0]
	cmp r0, #0x0
	strh r0, [r1, #0x18]
	orr r2, r3, r2
	and r2, r12, r2
	strh r2, [r1, #0x0]
	beq _020C61C0
	cmp r0, #0x100
	bne _020C61D0
	ldr r3, _020C61EC ; =0x04001000
	ldr r0, _020C61F0 ; =0x04000249
	ldr r2, [r3, #0x0]
	mov r1, #0x83
	orr r2, r2, #0x80000000
	str r2, [r3, #0x0]
	strb r1, [r0, #0x0]
	b _020C61D0
_020C61C0:
	ldr r1, _020C61EC ; =0x04001000
	ldr r0, [r1, #0x0]
	bic r0, r0, #0x80000000
	str r0, [r1, #0x0]
_020C61D0:
	ldr r0, _020C61E8 ; =0x021D33C4
	ldrh r0, [r0, #0x0]
	bl GX_VRAMCNT_SetLCDC_
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C61E8: .word 0x021D33C4
_020C61EC: .word 0x04001000
_020C61F0: .word 0x04000249

	arm_func_start GX_SetBankForSubBGExtPltt
GX_SetBankForSubBGExtPltt: ; 0x020C61F4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020C6274 ; =0x021D33C4
	mvn r12, r0
	ldrh r2, [r1, #0x16]
	ldrh r3, [r1, #0x0]
	cmp r0, #0x0
	strh r0, [r1, #0x16]
	orr r2, r3, r2
	and r2, r12, r2
	strh r2, [r1, #0x0]
	beq _020C624C
	cmp r0, #0x80
	bne _020C625C
	ldr r3, _020C6278 ; =0x04001000
	ldr r0, _020C627C ; =0x04000248
	ldr r2, [r3, #0x0]
	mov r1, #0x82
	orr r2, r2, #0x40000000
	str r2, [r3, #0x0]
	strb r1, [r0, #0x0]
	b _020C625C
_020C624C:
	ldr r1, _020C6278 ; =0x04001000
	ldr r0, [r1, #0x0]
	bic r0, r0, #0x40000000
	str r0, [r1, #0x0]
_020C625C:
	ldr r0, _020C6274 ; =0x021D33C4
	ldrh r0, [r0, #0x0]
	bl GX_VRAMCNT_SetLCDC_
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C6274: .word 0x021D33C4
_020C6278: .word 0x04001000
_020C627C: .word 0x04000248

	arm_func_start GX_SetBankForSubOBJ
GX_SetBankForSubOBJ: ; 0x020C6280
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020C62F0 ; =0x021D33C4
	mvn r12, r0
	ldrh r2, [r1, #0x14]
	ldrh r3, [r1, #0x0]
	cmp r0, #0x0
	strh r0, [r1, #0x14]
	orr r2, r3, r2
	and r2, r12, r2
	strh r2, [r1, #0x0]
	beq _020C62D8
	cmp r0, #0x8
	beq _020C62CC
	cmp r0, #0x100
	ldreq r0, _020C62F4 ; =0x04000249
	moveq r1, #0x82
	streqb r1, [r0, #0x0]
	b _020C62D8
_020C62CC:
	ldr r0, _020C62F8 ; =0x04000243
	mov r1, #0x84
	strb r1, [r0, #0x0]
_020C62D8:
	ldr r0, _020C62F0 ; =0x021D33C4
	ldrh r0, [r0, #0x0]
	bl GX_VRAMCNT_SetLCDC_
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C62F0: .word 0x021D33C4
_020C62F4: .word 0x04000249
_020C62F8: .word 0x04000243

	arm_func_start GX_SetBankForSubBG
GX_SetBankForSubBG: ; 0x020C62FC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020C6398 ; =0x021D33C4
	mvn r12, r0
	ldrh r2, [r1, #0x12]
	ldrh r3, [r1, #0x0]
	cmp r0, #0x80
	strh r0, [r1, #0x12]
	orr r2, r3, r2
	and r2, r12, r2
	strh r2, [r1, #0x0]
	bgt _020C6360
	cmp r0, #0x80
	bge _020C6374
	cmp r0, #0x4
	bgt _020C6380
	cmp r0, #0x0
	blt _020C6380
	cmp r0, #0x0
	beq _020C6380
	cmp r0, #0x4
	ldreq r0, _020C639C ; =0x04000242
	moveq r1, #0x84
	streqb r1, [r0, #0x0]
	b _020C6380
_020C6360:
	cmp r0, #0x180
	bne _020C6380
	ldr r0, _020C63A0 ; =0x04000249
	mov r1, #0x81
	strb r1, [r0, #0x0]
_020C6374:
	ldr r0, _020C63A4 ; =0x04000248
	mov r1, #0x81
	strb r1, [r0, #0x0]
_020C6380:
	ldr r0, _020C6398 ; =0x021D33C4
	ldrh r0, [r0, #0x0]
	bl GX_VRAMCNT_SetLCDC_
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C6398: .word 0x021D33C4
_020C639C: .word 0x04000242
_020C63A0: .word 0x04000249
_020C63A4: .word 0x04000248

	arm_func_start GX_SetBankForLCDC
GX_SetBankForLCDC: ; 0x020C63A8
	ldr r1, _020C63C0 ; =0x021D33C4
	ldr ip, _020C63C4 ; =GX_VRAMCNT_SetLCDC_
	ldrh r2, [r1, #0x0]
	orr r2, r2, r0
	strh r2, [r1, #0x0]
	bx r12
	.balign 4
_020C63C0: .word 0x021D33C4
_020C63C4: .word GX_VRAMCNT_SetLCDC_

	arm_func_start GX_SetBankForARM7
GX_SetBankForARM7: ; 0x020C63C8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020C6474 ; =0x021D33C4
	mvn r12, r0
	ldrh r2, [r1, #0x6]
	ldrh r3, [r1, #0x0]
	cmp r0, #0x8
	strh r0, [r1, #0x6]
	orr r2, r3, r2
	and r2, r12, r2
	strh r2, [r1, #0x0]
	bgt _020C642C
	cmp r0, #0x8
	bge _020C6450
	cmp r0, #0x4
	bgt _020C645C
	cmp r0, #0x0
	blt _020C645C
	cmp r0, #0x0
	beq _020C645C
	cmp r0, #0x4
	ldreq r0, _020C6478 ; =0x04000242
	moveq r1, #0x82
	streqb r1, [r0, #0x0]
	b _020C645C
_020C642C:
	cmp r0, #0xc
	bne _020C645C
	ldr r1, _020C647C ; =0x04000243
	mov r2, #0x8a
	strb r2, [r1, #0x0]
	ldr r0, _020C6478 ; =0x04000242
	mov r1, #0x82
	strb r1, [r0, #0x0]
	b _020C645C
_020C6450:
	ldr r0, _020C647C ; =0x04000243
	mov r1, #0x82
	strb r1, [r0, #0x0]
_020C645C:
	ldr r0, _020C6474 ; =0x021D33C4
	ldrh r0, [r0, #0x0]
	bl GX_VRAMCNT_SetLCDC_
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C6474: .word 0x021D33C4
_020C6478: .word 0x04000242
_020C647C: .word 0x04000243

	arm_func_start GX_SetBankForClearImage
GX_SetBankForClearImage: ; 0x020C6480
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020C65A8 ; =0x021D33C4
	mvn r12, r0
	ldrh r2, [r1, #0xc]
	ldrh r3, [r1, #0x0]
	cmp r0, #0xc
	strh r0, [r1, #0xc]
	orr r2, r3, r2
	and r2, r12, r2
	strh r2, [r1, #0x0]
	addls pc, pc, r0, lsl #0x2
	b _020C6590
_020C64B4: ; 0x020C64B4
	b _020C6540
_020C64B8: ; 0x020C64B8
	b _020C6554
_020C64BC: ; 0x020C64BC
	b _020C64F4
_020C64C0: ; 0x020C64C0
	b _020C64E8
_020C64C4: ; 0x020C64C4
	b _020C6574
_020C64C8: ; 0x020C64C8
	b _020C6590
_020C64CC: ; 0x020C64CC
	b _020C6590
_020C64D0: ; 0x020C64D0
	b _020C6590
_020C64D4: ; 0x020C64D4
	b _020C6520
_020C64D8: ; 0x020C64D8
	b _020C6590
_020C64DC: ; 0x020C64DC
	b _020C6590
_020C64E0: ; 0x020C64E0
	b _020C6590
_020C64E4: ; 0x020C64E4
	b _020C6514
_020C64E8:
	ldr r0, _020C65AC ; =0x04000240
	mov r1, #0x93
	strb r1, [r0, #0x0]
_020C64F4:
	ldr r0, _020C65B0 ; =0x04000241
	mov r2, #0x9b
	ldr r1, _020C65B4 ; =0x04000060
	strb r2, [r0, #0x0]
	ldrh r0, [r1, #0x0]
	orr r0, r0, #0x4000
	strh r0, [r1, #0x0]
	b _020C6590
_020C6514:
	ldr r0, _020C65B8 ; =0x04000242
	mov r1, #0x93
	strb r1, [r0, #0x0]
_020C6520:
	ldr r0, _020C65BC ; =0x04000243
	mov r2, #0x9b
	ldr r1, _020C65B4 ; =0x04000060
	strb r2, [r0, #0x0]
	ldrh r0, [r1, #0x0]
	orr r0, r0, #0x4000
	strh r0, [r1, #0x0]
	b _020C6590
_020C6540:
	ldr r1, _020C65B4 ; =0x04000060
	ldrh r0, [r1, #0x0]
	bic r0, r0, #0x4000
	strh r0, [r1, #0x0]
	b _020C6590
_020C6554:
	ldr r0, _020C65AC ; =0x04000240
	mov r2, #0x9b
	ldr r1, _020C65B4 ; =0x04000060
	strb r2, [r0, #0x0]
	ldrh r0, [r1, #0x0]
	orr r0, r0, #0x4000
	strh r0, [r1, #0x0]
	b _020C6590
_020C6574:
	ldr r0, _020C65B8 ; =0x04000242
	mov r2, #0x9b
	ldr r1, _020C65B4 ; =0x04000060
	strb r2, [r0, #0x0]
	ldrh r0, [r1, #0x0]
	orr r0, r0, #0x4000
	strh r0, [r1, #0x0]
_020C6590:
	ldr r0, _020C65A8 ; =0x021D33C4
	ldrh r0, [r0, #0x0]
	bl GX_VRAMCNT_SetLCDC_
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C65A8: .word 0x021D33C4
_020C65AC: .word 0x04000240
_020C65B0: .word 0x04000241
_020C65B4: .word 0x04000060
_020C65B8: .word 0x04000242
_020C65BC: .word 0x04000243

	arm_func_start GX_SetBankForTexPltt
GX_SetBankForTexPltt: ; 0x020C65C0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020C66A4 ; =0x021D33C4
	mvn r12, r0
	ldrh r2, [r1, #0xa]
	ldrh r3, [r1, #0x0]
	cmp r0, #0x30
	strh r0, [r1, #0xa]
	orr r2, r3, r2
	and r2, r12, r2
	strh r2, [r1, #0x0]
	bgt _020C661C
	cmp r0, #0x30
	bge _020C6674
	cmp r0, #0x10
	bgt _020C6610
	cmp r0, #0x10
	bge _020C6680
	cmp r0, #0x0
	b _020C668C
_020C6610:
	cmp r0, #0x20
	beq _020C6658
	b _020C668C
_020C661C:
	cmp r0, #0x60
	bgt _020C6640
	cmp r0, #0x60
	bge _020C664C
	cmp r0, #0x40
	ldreq r0, _020C66A8 ; =0x04000246
	moveq r1, #0x83
	streqb r1, [r0, #0x0]
	b _020C668C
_020C6640:
	cmp r0, #0x70
	beq _020C6668
	b _020C668C
_020C664C:
	ldr r0, _020C66A8 ; =0x04000246
	mov r1, #0x8b
	strb r1, [r0, #0x0]
_020C6658:
	ldr r0, _020C66AC ; =0x04000245
	mov r1, #0x83
	strb r1, [r0, #0x0]
	b _020C668C
_020C6668:
	ldr r0, _020C66A8 ; =0x04000246
	mov r1, #0x9b
	strb r1, [r0, #0x0]
_020C6674:
	ldr r0, _020C66AC ; =0x04000245
	mov r1, #0x93
	strb r1, [r0, #0x0]
_020C6680:
	ldr r0, _020C66B0 ; =0x04000244
	mov r1, #0x83
	strb r1, [r0, #0x0]
_020C668C:
	ldr r0, _020C66A4 ; =0x021D33C4
	ldrh r0, [r0, #0x0]
	bl GX_VRAMCNT_SetLCDC_
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C66A4: .word 0x021D33C4
_020C66A8: .word 0x04000246
_020C66AC: .word 0x04000245
_020C66B0: .word 0x04000244

	arm_func_start GX_SetBankForTex
GX_SetBankForTex: ; 0x020C66B4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020C689C ; =0x021D33C4
	mvn r12, r0
	ldrh r2, [r1, #0x8]
	ldrh r3, [r1, #0x0]
	cmp r0, #0x0
	strh r0, [r1, #0x8]
	orr r2, r3, r2
	and r2, r12, r2
	strh r2, [r1, #0x0]
	bne _020C66FC
	ldr r2, _020C68A0 ; =0x04000060
	ldr r0, _020C68A4 ; =0x0000CFFE
	ldrh r1, [r2, #0x0]
	and r0, r1, r0
	strh r0, [r2, #0x0]
	b _020C6884
_020C66FC:
	ldr r2, _020C68A0 ; =0x04000060
	cmp r0, #0xf
	ldrh r1, [r2, #0x0]
	bic r1, r1, #0x3000
	orr r1, r1, #0x1
	strh r1, [r2, #0x0]
	addls pc, pc, r0, lsl #0x2
	b _020C6884
_020C671C: ; 0x020C671C
	b _020C6884
_020C6720: ; 0x020C6720
	b _020C6878
_020C6724: ; 0x020C6724
	b _020C6844
_020C6728: ; 0x020C6728
	b _020C686C
_020C672C: ; 0x020C672C
	b _020C681C
_020C6730: ; 0x020C6730
	b _020C675C
_020C6734: ; 0x020C6734
	b _020C6838
_020C6738: ; 0x020C6738
	b _020C6860
_020C673C: ; 0x020C673C
	b _020C6800
_020C6740: ; 0x020C6740
	b _020C6778
_020C6744: ; 0x020C6744
	b _020C6794
_020C6748: ; 0x020C6748
	b _020C67B0
_020C674C: ; 0x020C674C
	b _020C6810
_020C6750: ; 0x020C6750
	b _020C67D8
_020C6754: ; 0x020C6754
	b _020C682C
_020C6758: ; 0x020C6758
	b _020C6854
_020C675C:
	ldr r1, _020C68A8 ; =0x04000240
	mov r2, #0x83
	ldr r0, _020C68AC ; =0x04000242
	strb r2, [r1, #0x0]
	mov r1, #0x8b
	strb r1, [r0, #0x0]
	b _020C6884
_020C6778:
	ldr r1, _020C68A8 ; =0x04000240
	mov r2, #0x83
	ldr r0, _020C68B0 ; =0x04000243
	strb r2, [r1, #0x0]
	mov r1, #0x8b
	strb r1, [r0, #0x0]
	b _020C6884
_020C6794:
	ldr r1, _020C68B4 ; =0x04000241
	mov r2, #0x83
	ldr r0, _020C68B0 ; =0x04000243
	strb r2, [r1, #0x0]
	mov r1, #0x8b
	strb r1, [r0, #0x0]
	b _020C6884
_020C67B0:
	ldr r0, _020C68A8 ; =0x04000240
	mov r2, #0x83
	ldr r1, _020C68B4 ; =0x04000241
	strb r2, [r0, #0x0]
	mov r2, #0x8b
	ldr r0, _020C68B0 ; =0x04000243
	strb r2, [r1, #0x0]
	mov r1, #0x93
	strb r1, [r0, #0x0]
	b _020C6884
_020C67D8:
	ldr r0, _020C68A8 ; =0x04000240
	mov r2, #0x83
	ldr r1, _020C68AC ; =0x04000242
	strb r2, [r0, #0x0]
	mov r2, #0x8b
	ldr r0, _020C68B0 ; =0x04000243
	strb r2, [r1, #0x0]
	mov r1, #0x93
	strb r1, [r0, #0x0]
	b _020C6884
_020C6800:
	ldr r0, _020C68B0 ; =0x04000243
	mov r1, #0x83
	strb r1, [r0, #0x0]
	b _020C6884
_020C6810:
	ldr r0, _020C68B0 ; =0x04000243
	mov r1, #0x8b
	strb r1, [r0, #0x0]
_020C681C:
	ldr r0, _020C68AC ; =0x04000242
	mov r1, #0x83
	strb r1, [r0, #0x0]
	b _020C6884
_020C682C:
	ldr r0, _020C68B0 ; =0x04000243
	mov r1, #0x93
	strb r1, [r0, #0x0]
_020C6838:
	ldr r0, _020C68AC ; =0x04000242
	mov r1, #0x8b
	strb r1, [r0, #0x0]
_020C6844:
	ldr r0, _020C68B4 ; =0x04000241
	mov r1, #0x83
	strb r1, [r0, #0x0]
	b _020C6884
_020C6854:
	ldr r0, _020C68B0 ; =0x04000243
	mov r1, #0x9b
	strb r1, [r0, #0x0]
_020C6860:
	ldr r0, _020C68AC ; =0x04000242
	mov r1, #0x93
	strb r1, [r0, #0x0]
_020C686C:
	ldr r0, _020C68B4 ; =0x04000241
	mov r1, #0x8b
	strb r1, [r0, #0x0]
_020C6878:
	ldr r0, _020C68A8 ; =0x04000240
	mov r1, #0x83
	strb r1, [r0, #0x0]
_020C6884:
	ldr r0, _020C689C ; =0x021D33C4
	ldrh r0, [r0, #0x0]
	bl GX_VRAMCNT_SetLCDC_
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C689C: .word 0x021D33C4
_020C68A0: .word 0x04000060
_020C68A4: .word 0x0000CFFE
_020C68A8: .word 0x04000240
_020C68AC: .word 0x04000242
_020C68B0: .word 0x04000243
_020C68B4: .word 0x04000241

	arm_func_start GX_SetBankForOBJExtPltt
GX_SetBankForOBJExtPltt: ; 0x020C68B8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020C6964 ; =0x021D33C4
	mvn r12, r0
	ldrh r2, [r1, #0x10]
	ldrh r3, [r1, #0x0]
	cmp r0, #0x0
	strh r0, [r1, #0x10]
	orr r2, r3, r2
	and r2, r12, r2
	strh r2, [r1, #0x0]
	beq _020C693C
	cmp r0, #0x20
	beq _020C68FC
	cmp r0, #0x40
	beq _020C691C
	b _020C694C
_020C68FC:
	mov r2, #0x4000000
	ldr r1, [r2, #0x0]
	ldr r0, _020C6968 ; =0x04000245
	orr r1, r1, #0x80000000
	str r1, [r2, #0x0]
	mov r1, #0x85
	strb r1, [r0, #0x0]
	b _020C694C
_020C691C:
	mov r2, #0x4000000
	ldr r1, [r2, #0x0]
	ldr r0, _020C696C ; =0x04000246
	orr r1, r1, #0x80000000
	str r1, [r2, #0x0]
	mov r1, #0x85
	strb r1, [r0, #0x0]
	b _020C694C
_020C693C:
	mov r1, #0x4000000
	ldr r0, [r1, #0x0]
	bic r0, r0, #0x80000000
	str r0, [r1, #0x0]
_020C694C:
	ldr r0, _020C6964 ; =0x021D33C4
	ldrh r0, [r0, #0x0]
	bl GX_VRAMCNT_SetLCDC_
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C6964: .word 0x021D33C4
_020C6968: .word 0x04000245
_020C696C: .word 0x04000246

	arm_func_start GX_SetBankForBGExtPltt
GX_SetBankForBGExtPltt: ; 0x020C6970
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020C6A74 ; =0x021D33C4
	mvn r12, r0
	ldrh r2, [r1, #0xe]
	ldrh r3, [r1, #0x0]
	cmp r0, #0x20
	strh r0, [r1, #0xe]
	orr r2, r3, r2
	and r2, r12, r2
	strh r2, [r1, #0x0]
	bgt _020C69D4
	cmp r0, #0x20
	bge _020C6A40
	cmp r0, #0x0
	bgt _020C69C8
	cmp r0, #0x0
	moveq r1, #0x4000000
	ldreq r0, [r1, #0x0]
	biceq r0, r0, #0x40000000
	streq r0, [r1, #0x0]
	b _020C6A5C
_020C69C8:
	cmp r0, #0x10
	beq _020C69F4
	b _020C6A5C
_020C69D4:
	cmp r0, #0x40
	bgt _020C69E8
	cmp r0, #0x40
	beq _020C6A14
	b _020C6A5C
_020C69E8:
	cmp r0, #0x60
	beq _020C6A34
	b _020C6A5C
_020C69F4:
	mov r2, #0x4000000
	ldr r1, [r2, #0x0]
	ldr r0, _020C6A78 ; =0x04000244
	orr r1, r1, #0x40000000
	str r1, [r2, #0x0]
	mov r1, #0x84
	strb r1, [r0, #0x0]
	b _020C6A5C
_020C6A14:
	mov r2, #0x4000000
	ldr r1, [r2, #0x0]
	ldr r0, _020C6A7C ; =0x04000246
	orr r1, r1, #0x40000000
	str r1, [r2, #0x0]
	mov r1, #0x8c
	strb r1, [r0, #0x0]
	b _020C6A5C
_020C6A34:
	ldr r0, _020C6A7C ; =0x04000246
	mov r1, #0x8c
	strb r1, [r0, #0x0]
_020C6A40:
	ldr r0, _020C6A80 ; =0x04000245
	mov r1, #0x84
	strb r1, [r0, #0x0]
	mov r1, #0x4000000
	ldr r0, [r1, #0x0]
	orr r0, r0, #0x40000000
	str r0, [r1, #0x0]
_020C6A5C:
	ldr r0, _020C6A74 ; =0x021D33C4
	ldrh r0, [r0, #0x0]
	bl GX_VRAMCNT_SetLCDC_
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C6A74: .word 0x021D33C4
_020C6A78: .word 0x04000244
_020C6A7C: .word 0x04000246
_020C6A80: .word 0x04000245

	arm_func_start GX_SetBankForOBJ
GX_SetBankForOBJ: ; 0x020C6A84
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020C6BD8 ; =0x021D33C4
	mvn r12, r0
	ldrh r2, [r1, #0x4]
	ldrh r3, [r1, #0x0]
	cmp r0, #0x30
	strh r0, [r1, #0x4]
	orr r2, r3, r2
	and r2, r12, r2
	strh r2, [r1, #0x0]
	bgt _020C6AF4
	cmp r0, #0x30
	bge _020C6B70
	cmp r0, #0x10
	bgt _020C6AE8
	cmp r0, #0x10
	bge _020C6B7C
	cmp r0, #0x3
	addls pc, pc, r0, lsl #0x2
	b _020C6BC0
_020C6AD8: ; 0x020C6AD8
	b _020C6BC0
_020C6ADC: ; 0x020C6ADC
	b _020C6B44
_020C6AE0: ; 0x020C6AE0
	b _020C6B54
_020C6AE4: ; 0x020C6AE4
	b _020C6B38
_020C6AE8:
	cmp r0, #0x20
	beq _020C6BB4
	b _020C6BC0
_020C6AF4:
	cmp r0, #0x50
	bgt _020C6B18
	cmp r0, #0x50
	bge _020C6B8C
	cmp r0, #0x40
	ldreq r0, _020C6BDC ; =0x04000246
	moveq r1, #0x82
	streqb r1, [r0, #0x0]
	b _020C6BC0
_020C6B18:
	cmp r0, #0x60
	bgt _020C6B2C
	cmp r0, #0x60
	beq _020C6BA8
	b _020C6BC0
_020C6B2C:
	cmp r0, #0x70
	beq _020C6B64
	b _020C6BC0
_020C6B38:
	ldr r0, _020C6BE0 ; =0x04000241
	mov r1, #0x8a
	strb r1, [r0, #0x0]
_020C6B44:
	ldr r0, _020C6BE4 ; =0x04000240
	mov r1, #0x82
	strb r1, [r0, #0x0]
	b _020C6BC0
_020C6B54:
	ldr r0, _020C6BE0 ; =0x04000241
	mov r1, #0x82
	strb r1, [r0, #0x0]
	b _020C6BC0
_020C6B64:
	ldr r0, _020C6BDC ; =0x04000246
	mov r1, #0x9a
	strb r1, [r0, #0x0]
_020C6B70:
	ldr r0, _020C6BE8 ; =0x04000245
	mov r1, #0x92
	strb r1, [r0, #0x0]
_020C6B7C:
	ldr r0, _020C6BEC ; =0x04000244
	mov r1, #0x82
	strb r1, [r0, #0x0]
	b _020C6BC0
_020C6B8C:
	ldr r1, _020C6BDC ; =0x04000246
	mov r2, #0x92
	ldr r0, _020C6BEC ; =0x04000244
	strb r2, [r1, #0x0]
	mov r1, #0x82
	strb r1, [r0, #0x0]
	b _020C6BC0
_020C6BA8:
	ldr r0, _020C6BDC ; =0x04000246
	mov r1, #0x8a
	strb r1, [r0, #0x0]
_020C6BB4:
	ldr r0, _020C6BE8 ; =0x04000245
	mov r1, #0x82
	strb r1, [r0, #0x0]
_020C6BC0:
	ldr r0, _020C6BD8 ; =0x021D33C4
	ldrh r0, [r0, #0x0]
	bl GX_VRAMCNT_SetLCDC_
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C6BD8: .word 0x021D33C4
_020C6BDC: .word 0x04000246
_020C6BE0: .word 0x04000241
_020C6BE4: .word 0x04000240
_020C6BE8: .word 0x04000245
_020C6BEC: .word 0x04000244

	arm_func_start GX_SetBankForBG
GX_SetBankForBG: ; 0x020C6BF0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020C6E88 ; =0x021D33C4
	mvn r12, r0
	ldrh r2, [r1, #0x2]
	ldrh r3, [r1, #0x0]
	cmp r0, #0x40
	strh r0, [r1, #0x2]
	orr r2, r3, r2
	and r2, r12, r2
	strh r2, [r1, #0x0]
	bgt _020C6CCC
	cmp r0, #0x40
	bge _020C6E64
	cmp r0, #0x20
	bgt _020C6CC0
	cmp r0, #0x0
	addge pc, pc, r0, lsl #0x2
	b _020C6E70
_020C6C3C: ; 0x020C6C3C
	b _020C6E70
_020C6C40: ; 0x020C6C40
	b _020C6D6C
_020C6C44: ; 0x020C6C44
	b _020C6D38
_020C6C48: ; 0x020C6C48
	b _020C6D60
_020C6C4C: ; 0x020C6C4C
	b _020C6D10
_020C6C50: ; 0x020C6C50
	b _020C6DB0
_020C6C54: ; 0x020C6C54
	b _020C6D2C
_020C6C58: ; 0x020C6C58
	b _020C6D54
_020C6C5C: ; 0x020C6C5C
	b _020C6CF4
_020C6C60: ; 0x020C6C60
	b _020C6DCC
_020C6C64: ; 0x020C6C64
	b _020C6DE8
_020C6C68: ; 0x020C6C68
	b _020C6D7C
_020C6C6C: ; 0x020C6C6C
	b _020C6D04
_020C6C70: ; 0x020C6C70
	b _020C6DA4
_020C6C74: ; 0x020C6C74
	b _020C6D20
_020C6C78: ; 0x020C6C78
	b _020C6D48
_020C6C7C: ; 0x020C6C7C
	b _020C6E1C
_020C6C80: ; 0x020C6C80
	b _020C6E70
_020C6C84: ; 0x020C6C84
	b _020C6E70
_020C6C88: ; 0x020C6C88
	b _020C6E70
_020C6C8C: ; 0x020C6C8C
	b _020C6E70
_020C6C90: ; 0x020C6C90
	b _020C6E70
_020C6C94: ; 0x020C6C94
	b _020C6E70
_020C6C98: ; 0x020C6C98
	b _020C6E70
_020C6C9C: ; 0x020C6C9C
	b _020C6E70
_020C6CA0: ; 0x020C6CA0
	b _020C6E70
_020C6CA4: ; 0x020C6CA4
	b _020C6E70
_020C6CA8: ; 0x020C6CA8
	b _020C6E70
_020C6CAC: ; 0x020C6CAC
	b _020C6E70
_020C6CB0: ; 0x020C6CB0
	b _020C6E70
_020C6CB4: ; 0x020C6CB4
	b _020C6E70
_020C6CB8: ; 0x020C6CB8
	b _020C6E70
_020C6CBC: ; 0x020C6CBC
	b _020C6E54
_020C6CC0:
	cmp r0, #0x30
	beq _020C6E10
	b _020C6E70
_020C6CCC:
	cmp r0, #0x60
	bgt _020C6CE8
	cmp r0, #0x60
	bge _020C6E48
	cmp r0, #0x50
	beq _020C6E2C
	b _020C6E70
_020C6CE8:
	cmp r0, #0x70
	beq _020C6E04
	b _020C6E70
_020C6CF4:
	ldr r0, _020C6E8C ; =0x04000243
	mov r1, #0x81
	strb r1, [r0, #0x0]
	b _020C6E70
_020C6D04:
	ldr r0, _020C6E8C ; =0x04000243
	mov r1, #0x89
	strb r1, [r0, #0x0]
_020C6D10:
	ldr r0, _020C6E90 ; =0x04000242
	mov r1, #0x81
	strb r1, [r0, #0x0]
	b _020C6E70
_020C6D20:
	ldr r0, _020C6E8C ; =0x04000243
	mov r1, #0x91
	strb r1, [r0, #0x0]
_020C6D2C:
	ldr r0, _020C6E90 ; =0x04000242
	mov r1, #0x89
	strb r1, [r0, #0x0]
_020C6D38:
	ldr r0, _020C6E94 ; =0x04000241
	mov r1, #0x81
	strb r1, [r0, #0x0]
	b _020C6E70
_020C6D48:
	ldr r0, _020C6E8C ; =0x04000243
	mov r1, #0x99
	strb r1, [r0, #0x0]
_020C6D54:
	ldr r0, _020C6E90 ; =0x04000242
	mov r1, #0x91
	strb r1, [r0, #0x0]
_020C6D60:
	ldr r0, _020C6E94 ; =0x04000241
	mov r1, #0x89
	strb r1, [r0, #0x0]
_020C6D6C:
	ldr r0, _020C6E98 ; =0x04000240
	mov r1, #0x81
	strb r1, [r0, #0x0]
	b _020C6E70
_020C6D7C:
	ldr r0, _020C6E98 ; =0x04000240
	mov r2, #0x81
	ldr r1, _020C6E94 ; =0x04000241
	strb r2, [r0, #0x0]
	mov r2, #0x89
	ldr r0, _020C6E8C ; =0x04000243
	strb r2, [r1, #0x0]
	mov r1, #0x91
	strb r1, [r0, #0x0]
	b _020C6E70
_020C6DA4:
	ldr r0, _020C6E8C ; =0x04000243
	mov r1, #0x91
	strb r1, [r0, #0x0]
_020C6DB0:
	ldr r1, _020C6E98 ; =0x04000240
	mov r2, #0x81
	ldr r0, _020C6E90 ; =0x04000242
	strb r2, [r1, #0x0]
	mov r1, #0x89
	strb r1, [r0, #0x0]
	b _020C6E70
_020C6DCC:
	ldr r1, _020C6E98 ; =0x04000240
	mov r2, #0x81
	ldr r0, _020C6E8C ; =0x04000243
	strb r2, [r1, #0x0]
	mov r1, #0x89
	strb r1, [r0, #0x0]
	b _020C6E70
_020C6DE8:
	ldr r1, _020C6E94 ; =0x04000241
	mov r2, #0x81
	ldr r0, _020C6E8C ; =0x04000243
	strb r2, [r1, #0x0]
	mov r1, #0x89
	strb r1, [r0, #0x0]
	b _020C6E70
_020C6E04:
	ldr r0, _020C6E9C ; =0x04000246
	mov r1, #0x99
	strb r1, [r0, #0x0]
_020C6E10:
	ldr r0, _020C6EA0 ; =0x04000245
	mov r1, #0x91
	strb r1, [r0, #0x0]
_020C6E1C:
	ldr r0, _020C6EA4 ; =0x04000244
	mov r1, #0x81
	strb r1, [r0, #0x0]
	b _020C6E70
_020C6E2C:
	ldr r1, _020C6E9C ; =0x04000246
	mov r2, #0x91
	ldr r0, _020C6EA4 ; =0x04000244
	strb r2, [r1, #0x0]
	mov r1, #0x81
	strb r1, [r0, #0x0]
	b _020C6E70
_020C6E48:
	ldr r0, _020C6E9C ; =0x04000246
	mov r1, #0x89
	strb r1, [r0, #0x0]
_020C6E54:
	ldr r0, _020C6EA0 ; =0x04000245
	mov r1, #0x81
	strb r1, [r0, #0x0]
	b _020C6E70
_020C6E64:
	ldr r0, _020C6E9C ; =0x04000246
	mov r1, #0x81
	strb r1, [r0, #0x0]
_020C6E70:
	ldr r0, _020C6E88 ; =0x021D33C4
	ldrh r0, [r0, #0x0]
	bl GX_VRAMCNT_SetLCDC_
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C6E88: .word 0x021D33C4
_020C6E8C: .word 0x04000243
_020C6E90: .word 0x04000242
_020C6E94: .word 0x04000241
_020C6E98: .word 0x04000240
_020C6E9C: .word 0x04000246
_020C6EA0: .word 0x04000245
_020C6EA4: .word 0x04000244

	arm_func_start GX_VRAMCNT_SetLCDC_
GX_VRAMCNT_SetLCDC_: ; 0x020C6EA8
	ands r1, r0, #0x1
	ldrne r1, _020C6F3C ; =0x04000240
	movne r2, #0x80
	strneb r2, [r1, #0x0]
	ands r1, r0, #0x2
	ldrne r1, _020C6F40 ; =0x04000241
	movne r2, #0x80
	strneb r2, [r1, #0x0]
	ands r1, r0, #0x4
	ldrne r1, _020C6F44 ; =0x04000242
	movne r2, #0x80
	strneb r2, [r1, #0x0]
	ands r1, r0, #0x8
	ldrne r1, _020C6F48 ; =0x04000243
	movne r2, #0x80
	strneb r2, [r1, #0x0]
	ands r1, r0, #0x10
	ldrne r1, _020C6F4C ; =0x04000244
	movne r2, #0x80
	strneb r2, [r1, #0x0]
	ands r1, r0, #0x20
	ldrne r1, _020C6F50 ; =0x04000245
	movne r2, #0x80
	strneb r2, [r1, #0x0]
	ands r1, r0, #0x40
	ldrne r1, _020C6F54 ; =0x04000246
	movne r2, #0x80
	strneb r2, [r1, #0x0]
	ands r1, r0, #0x80
	ldrne r1, _020C6F58 ; =0x04000248
	movne r2, #0x80
	strneb r2, [r1, #0x0]
	ands r0, r0, #0x100
	ldrne r0, _020C6F5C ; =0x04000249
	movne r1, #0x80
	strneb r1, [r0, #0x0]
	bx lr
	.balign 4
_020C6F3C: .word 0x04000240
_020C6F40: .word 0x04000241
_020C6F44: .word 0x04000242
_020C6F48: .word 0x04000243
_020C6F4C: .word 0x04000244
_020C6F50: .word 0x04000245
_020C6F54: .word 0x04000246
_020C6F58: .word 0x04000248
_020C6F5C: .word 0x04000249

	arm_func_start G2S_GetBG3CharPtr
G2S_GetBG3CharPtr: ; 0x020C6F60
	ldr r1, _020C6FA8 ; =0x04001000
	ldr r0, _020C6FAC ; =0x0400100E
	ldr r1, [r1, #0x0]
	ldrh r2, [r0, #0x0]
	and r0, r1, #0x7
	cmp r0, #0x3
	blt _020C6F8C
	cmp r0, #0x6
	bge _020C6FA0
	ands r0, r2, #0x80
	bne _020C6FA0
_020C6F8C:
	and r0, r2, #0x3c
	mov r0, r0, lsr #0x2
	mov r0, r0, lsl #0xe
	add r0, r0, #0x6200000
	bx lr
_020C6FA0:
	mov r0, #0x0
	bx lr
	.balign 4
_020C6FA8: .word 0x04001000
_020C6FAC: .word 0x0400100E

	arm_func_start G2_GetBG3CharPtr
G2_GetBG3CharPtr: ; 0x020C6FB0
	mov r0, #0x4000000
	ldr r1, [r0, #0x0]
	ldr r0, _020C700C ; =0x0400000E
	and r1, r1, #0x7
	cmp r1, #0x3
	ldrh r2, [r0, #0x0]
	blt _020C6FDC
	cmp r1, #0x6
	bge _020C7004
	ands r0, r2, #0x80
	bne _020C7004
_020C6FDC:
	mov r0, #0x4000000
	ldr r1, [r0, #0x0]
	and r0, r2, #0x3c
	and r1, r1, #0x7000000
	mov r1, r1, lsr #0x18
	mov r1, r1, lsl #0x10
	add r1, r1, #0x6000000
	mov r0, r0, lsr #0x2
	add r0, r1, r0, lsl #0xe
	bx lr
_020C7004:
	mov r0, #0x0
	bx lr
	.balign 4
_020C700C: .word 0x0400000E

	arm_func_start G2S_GetBG2CharPtr
G2S_GetBG2CharPtr: ; 0x020C7010
	ldr r1, _020C7050 ; =0x04001000
	ldr r0, _020C7054 ; =0x0400100C
	ldr r1, [r1, #0x0]
	ldrh r2, [r0, #0x0]
	and r0, r1, #0x7
	cmp r0, #0x5
	blt _020C7034
	ands r0, r2, #0x80
	bne _020C7048
_020C7034:
	and r0, r2, #0x3c
	mov r0, r0, lsr #0x2
	mov r0, r0, lsl #0xe
	add r0, r0, #0x6200000
	bx lr
_020C7048:
	mov r0, #0x0
	bx lr
	.balign 4
_020C7050: .word 0x04001000
_020C7054: .word 0x0400100C

	arm_func_start G2_GetBG2CharPtr
G2_GetBG2CharPtr: ; 0x020C7058
	mov r0, #0x4000000
	ldr r1, [r0, #0x0]
	ldr r0, _020C70AC ; =0x0400000C
	and r1, r1, #0x7
	cmp r1, #0x5
	ldrh r2, [r0, #0x0]
	blt _020C707C
	ands r0, r2, #0x80
	bne _020C70A4
_020C707C:
	mov r0, #0x4000000
	ldr r1, [r0, #0x0]
	and r0, r2, #0x3c
	and r1, r1, #0x7000000
	mov r1, r1, lsr #0x18
	mov r1, r1, lsl #0x10
	add r1, r1, #0x6000000
	mov r0, r0, lsr #0x2
	add r0, r1, r0, lsl #0xe
	bx lr
_020C70A4:
	mov r0, #0x0
	bx lr
	.balign 4
_020C70AC: .word 0x0400000C

	arm_func_start G2S_GetBG1CharPtr
G2S_GetBG1CharPtr: ; 0x020C70B0
	ldr r0, _020C70CC ; =0x0400100A
	ldrh r0, [r0, #0x0]
	and r0, r0, #0x3c
	mov r0, r0, asr #0x2
	mov r0, r0, lsl #0xe
	add r0, r0, #0x6200000
	bx lr
	.balign 4
_020C70CC: .word 0x0400100A

	arm_func_start G2_GetBG1CharPtr
G2_GetBG1CharPtr: ; 0x020C70D0
	ldr r1, _020C7100 ; =0x0400000A
	mov r0, #0x4000000
	ldrh r1, [r1, #0x0]
	ldr r0, [r0, #0x0]
	and r0, r0, #0x7000000
	mov r0, r0, lsr #0x18
	and r1, r1, #0x3c
	mov r0, r0, lsl #0x10
	mov r1, r1, asr #0x2
	add r0, r0, #0x6000000
	add r0, r0, r1, lsl #0xe
	bx lr
	.balign 4
_020C7100: .word 0x0400000A

	arm_func_start G2S_GetBG0CharPtr
G2S_GetBG0CharPtr: ; 0x020C7104
	ldr r0, _020C7120 ; =0x04001008
	ldrh r0, [r0, #0x0]
	and r0, r0, #0x3c
	mov r0, r0, asr #0x2
	mov r0, r0, lsl #0xe
	add r0, r0, #0x6200000
	bx lr
	.balign 4
_020C7120: .word 0x04001008

	arm_func_start G2_GetBG0CharPtr
G2_GetBG0CharPtr: ; 0x020C7124
	ldr r1, _020C7154 ; =0x04000008
	mov r0, #0x4000000
	ldrh r1, [r1, #0x0]
	ldr r0, [r0, #0x0]
	and r0, r0, #0x7000000
	mov r0, r0, lsr #0x18
	and r1, r1, #0x3c
	mov r0, r0, lsl #0x10
	mov r1, r1, asr #0x2
	add r0, r0, #0x6000000
	add r0, r0, r1, lsl #0xe
	bx lr
	.balign 4
_020C7154: .word 0x04000008

	arm_func_start G2S_GetBG3ScrPtr
G2S_GetBG3ScrPtr: ; 0x020C7158
	ldr r1, _020C71D0 ; =0x04001000
	ldr r0, _020C71D4 ; =0x0400100E
	ldr r1, [r1, #0x0]
	ldrh r2, [r0, #0x0]
	and r3, r1, #0x7
	cmp r3, #0x6
	and r0, r2, #0x1f00
	mov r1, r0, lsr #0x8
	addls pc, pc, r3, lsl #0x2
	b _020C71C8
_020C7180: ; 0x020C7180
	b _020C719C
_020C7184: ; 0x020C7184
	b _020C719C
_020C7188: ; 0x020C7188
	b _020C719C
_020C718C: ; 0x020C718C
	b _020C71A8
_020C7190: ; 0x020C7190
	b _020C71A8
_020C7194: ; 0x020C7194
	b _020C71A8
_020C7198: ; 0x020C7198
	b _020C71C0
_020C719C:
	mov r0, r1, lsl #0xb
	add r0, r0, #0x6200000
	bx lr
_020C71A8:
	ands r0, r2, #0x80
	movne r0, r1, lsl #0xe
	addne r0, r0, #0x6200000
	moveq r0, r1, lsl #0xb
	addeq r0, r0, #0x6200000
	bx lr
_020C71C0:
	mov r0, #0x0
	bx lr
_020C71C8:
	mov r0, #0x0
	bx lr
	.balign 4
_020C71D0: .word 0x04001000
_020C71D4: .word 0x0400100E

	arm_func_start G2_GetBG3ScrPtr
G2_GetBG3ScrPtr: ; 0x020C71D8
	ldr r0, _020C7260 ; =0x0400000E
	mov r2, #0x4000000
	ldr r1, [r2, #0x0]
	ldrh r3, [r0, #0x0]
	ldr r0, [r2, #0x0]
	and r12, r1, #0x7
	and r0, r0, #0x38000000
	mov r1, r0, lsr #0x1b
	and r0, r3, #0x1f00
	mov r2, r1, lsl #0x10
	cmp r12, #0x6
	mov r1, r0, lsr #0x8
	addls pc, pc, r12, lsl #0x2
	b _020C7258
_020C7210:
	b _020C722C
_020C7214:
	b _020C722C
_020C7218:
	b _020C722C
_020C721C:
	b _020C7238
_020C7220:
	b _020C7238
_020C7224:
	b _020C7238
_020C7228:
	b _020C7250
_020C722C:
	add r0, r2, #0x6000000
	add r0, r0, r1, lsl #0xb
	bx lr
_020C7238:
	ands r0, r3, #0x80
	movne r0, r1, lsl #0xe
	addne r0, r0, #0x6000000
	addeq r0, r2, #0x6000000
	addeq r0, r0, r1, lsl #0xb
	bx lr
_020C7250:
	mov r0, #0x0
	bx lr
_020C7258:
	mov r0, #0x0
	bx lr
	.balign 4
_020C7260: .word 0x0400000E

	arm_func_start G2S_GetBG2ScrPtr
G2S_GetBG2ScrPtr: ; 0x020C7264
	ldr r1, _020C72DC ; =0x04001000
	ldr r0, _020C72E0 ; =0x0400100C
	ldr r1, [r1, #0x0]
	ldrh r2, [r0, #0x0]
	and r3, r1, #0x7
	cmp r3, #0x6
	and r0, r2, #0x1f00
	mov r1, r0, lsr #0x8
	addls pc, pc, r3, lsl #0x2
	b _020C72D4
_020C728C: ; 0x020C728C
	b _020C72A8
_020C7290: ; 0x020C7290
	b _020C72A8
_020C7294: ; 0x020C7294
	b _020C72A8
_020C7298: ; 0x020C7298
	b _020C72A8
_020C729C: ; 0x020C729C
	b _020C72A8
_020C72A0: ; 0x020C72A0
	b _020C72B4
_020C72A4: ; 0x020C72A4
	b _020C72CC
_020C72A8:
	mov r0, r1, lsl #0xb
	add r0, r0, #0x6200000
	bx lr
_020C72B4:
	ands r0, r2, #0x80
	movne r0, r1, lsl #0xe
	addne r0, r0, #0x6200000
	moveq r0, r1, lsl #0xb
	addeq r0, r0, #0x6200000
	bx lr
_020C72CC:
	mov r0, #0x0
	bx lr
_020C72D4:
	mov r0, #0x0
	bx lr
	.balign 4
_020C72DC: .word 0x04001000
_020C72E0: .word 0x0400100C

	arm_func_start G2_GetBG2ScrPtr
G2_GetBG2ScrPtr: ; 0x020C72E4
	ldr r0, _020C736C ; =0x0400000C
	mov r2, #0x4000000
	ldr r1, [r2, #0x0]
	ldrh r3, [r0, #0x0]
	ldr r0, [r2, #0x0]
	and r12, r1, #0x7
	and r0, r0, #0x38000000
	mov r1, r0, lsr #0x1b
	and r0, r3, #0x1f00
	mov r2, r1, lsl #0x10
	cmp r12, #0x6
	mov r1, r0, lsr #0x8
	addls pc, pc, r12, lsl #0x2
	b _020C7364
_020C731C:
	b _020C7338
_020C7320:
	b _020C7338
_020C7324:
	b _020C7338
_020C7328:
	b _020C7338
_020C732C:
	b _020C7338
_020C7330:
	b _020C7344
_020C7334:
	b _020C735C
_020C7338:
	add r0, r2, #0x6000000
	add r0, r0, r1, lsl #0xb
	bx lr
_020C7344:
	ands r0, r3, #0x80
	movne r0, r1, lsl #0xe
	addne r0, r0, #0x6000000
	addeq r0, r2, #0x6000000
	addeq r0, r0, r1, lsl #0xb
	bx lr
_020C735C:
	mov r0, #0x6000000
	bx lr
_020C7364:
	mov r0, #0x0
	bx lr
	.balign 4
_020C736C: .word 0x0400000C

	arm_func_start G2S_GetBG1ScrPtr
G2S_GetBG1ScrPtr: ; 0x020C7370
	ldr r0, _020C738C ; =0x0400100A
	ldrh r0, [r0, #0x0]
	and r0, r0, #0x1f00
	mov r0, r0, asr #0x8
	mov r0, r0, lsl #0xb
	add r0, r0, #0x6200000
	bx lr
	.balign 4
_020C738C: .word 0x0400100A

	arm_func_start G2_GetBG1ScrPtr
G2_GetBG1ScrPtr: ; 0x020C7390
	ldr r1, _020C73C0 ; =0x0400000A
	mov r0, #0x4000000
	ldrh r1, [r1, #0x0]
	ldr r0, [r0, #0x0]
	and r0, r0, #0x38000000
	mov r0, r0, lsr #0x1b
	and r1, r1, #0x1f00
	mov r0, r0, lsl #0x10
	mov r1, r1, asr #0x8
	add r0, r0, #0x6000000
	add r0, r0, r1, lsl #0xb
	bx lr
	.balign 4
_020C73C0: .word 0x0400000A

	arm_func_start G2S_GetBG0ScrPtr
G2S_GetBG0ScrPtr: ; 0x020C73C4
	ldr r0, _020C73E0 ; =0x04001008
	ldrh r0, [r0, #0x0]
	and r0, r0, #0x1f00
	mov r0, r0, asr #0x8
	mov r0, r0, lsl #0xb
	add r0, r0, #0x6200000
	bx lr
	.balign 4
_020C73E0: .word 0x04001008

	arm_func_start G2_GetBG0ScrPtr
G2_GetBG0ScrPtr: ; 0x020C73E4
	ldr r1, _020C7414 ; =0x04000008
	mov r0, #0x4000000
	ldrh r1, [r1, #0x0]
	ldr r0, [r0, #0x0]
	and r0, r0, #0x38000000
	mov r0, r0, lsr #0x1b
	and r1, r1, #0x1f00
	mov r0, r0, lsl #0x10
	mov r1, r1, asr #0x8
	add r0, r0, #0x6000000
	add r0, r0, r1, lsl #0xb
	bx lr
	.balign 4
_020C7414: .word 0x04000008

	arm_func_start G2x_ChangeBlendBrightness_
G2x_ChangeBlendBrightness_: ; 0x020C7418
	cmp r1, #0x0
	ldrh r3, [r0, #0x0]
	bge _020C7444
	and r2, r3, #0xc0
	cmp r2, #0x80
	biceq r2, r3, #0xc0
	orreq r2, r2, #0xc0
	streqh r2, [r0, #0x0]
	rsb r1, r1, #0x0
	strh r1, [r0, #0x4]
	bx lr
_020C7444:
	and r2, r3, #0xc0
	cmp r2, #0xc0
	biceq r2, r3, #0xc0
	orreq r2, r2, #0x80
	streqh r2, [r0, #0x0]
	strh r1, [r0, #0x4]
	bx lr

	arm_func_start G2x_SetBlendBrightnessExt_
G2x_SetBlendBrightnessExt_: ; 0x020C7460
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr lr, [sp, #0x8]
	ldr r12, [sp, #0xc]
	orr r3, r3, lr, lsl #0x8
	cmp r12, #0x0
	orrge r1, r1, #0x80
	strh r3, [r0, #0x2]
	orrge r1, r1, r2, lsl #0x8
	strgeh r1, [r0, #0x0]
	strgeh r12, [r0, #0x4]
	addge sp, sp, #0x4
	ldmgeia sp!, {lr}
	bxge lr
	orr r1, r1, #0xc0
	orr r1, r1, r2, lsl #0x8
	strh r1, [r0, #0x0]
	rsb r1, r12, #0x0
	strh r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start G2x_SetBlendBrightness_
G2x_SetBlendBrightness_: ; 0x020C74B8
	cmp r2, #0x0
	orrlt r1, r1, #0xc0
	strlth r1, [r0, #0x0]
	rsblt r1, r2, #0x0
	strlth r1, [r0, #0x4]
	orrge r1, r1, #0x80
	strgeh r1, [r0, #0x0]
	strgeh r2, [r0, #0x4]
	bx lr

	arm_func_start G2x_SetBlendAlpha_
G2x_SetBlendAlpha_: ; 0x020C74DC
	ldr r12, [sp, #0x0]
	orr r1, r1, #0x40
	orr r2, r1, r2, lsl #0x8
	orr r1, r3, r12, lsl #0x8
	orr r1, r2, r1, lsl #0x10
	str r1, [r0, #0x0]
	bx lr

	arm_func_start G2x_SetBGyAffine_
G2x_SetBGyAffine_: ; 0x020C74F8
	stmdb sp!, {r4-r6,lr}
	ldr r5, [r1, #0x0]
	ldr r4, [r1, #0x4]
	mov r12, r5, lsl #0xc
	mov lr, r4, lsl #0xc
	mov r5, r12, asr #0x10
	mov r4, lr, asr #0x10
	mov r12, r5, lsl #0x10
	mov lr, r4, lsl #0x10
	mov r5, r12, lsr #0x10
	mov r4, lr, lsr #0x10
	orr r4, r5, r4, lsl #0x10
	str r4, [r0, #0x0]
	ldr r5, [r1, #0x8]
	ldr r4, [r1, #0xc]
	mov r12, r5, lsl #0xc
	mov lr, r4, lsl #0xc
	mov r5, r12, asr #0x10
	mov r4, lr, asr #0x10
	mov r12, r5, lsl #0x10
	mov lr, r4, lsl #0x10
	ldr r4, [sp, #0x14]
	ldr r6, [sp, #0x10]
	mov r12, r12, lsr #0x10
	mov r5, lr, lsr #0x10
	orr r5, r12, r5, lsl #0x10
	str r5, [r0, #0x4]
	ldr r12, [r1, #0x4]
	sub r5, r4, r3
	ldr r4, [r1, #0xc]
	mul lr, r12, r5
	mul r5, r4, r5
	ldr r12, [r1, #0x0]
	sub r6, r6, r2
	ldr r4, [r1, #0x8]
	mla r1, r12, r6, lr
	mla r5, r4, r6, r5
	add r1, r1, r2, lsl #0xc
	add r2, r5, r3, lsl #0xc
	mov r1, r1, asr #0x4
	str r1, [r0, #0x8]
	mov r1, r2, asr #0x4
	str r1, [r0, #0xc]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start G3B_End
G3B_End: ; 0x020C75AC
	ldr r1, [r0, #0x0]
	mov r2, #0x41
	str r2, [r1, #0x0]
	ldr r1, [r0, #0x4]
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start G3B_Begin
G3B_Begin: ; 0x020C75D0
	ldr r2, [r0, #0x0]
	mov r3, #0x40
	str r3, [r2, #0x0]
	ldr r2, [r0, #0x4]
	str r1, [r2, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start G3B_LightColor
G3B_LightColor: ; 0x020C7600
	ldr r3, [r0, #0x0]
	mov r12, #0x33
	str r12, [r3, #0x0]
	ldr r3, [r0, #0x4]
	orr r1, r2, r1, lsl #0x1e
	str r1, [r3, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start G3B_LightVector
G3B_LightVector: ; 0x020C7634
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr ip, _020C7694 ; =0x000003FF
	ldrsh r4, [sp, #0x10]
	ldr lr, [r0, #0x0]
	mov r5, #0x32
	str r5, [lr, #0x0]
	and lr, r12, r2, asr #0x3
	and r2, r12, r3, asr #0x3
	and r3, r12, r4, asr #0x3
	orr r2, lr, r2, lsl #0xa
	orr r3, r2, r3, lsl #0x14
	ldr r2, [r0, #0x4]
	orr r1, r3, r1, lsl #0x1e
	str r1, [r2, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020C7694: .word 0x000003FF

	arm_func_start G3B_MaterialColorSpecEmi
G3B_MaterialColorSpecEmi: ; 0x020C7698
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r12, [r0, #0x0]
	mov lr, #0x31
	cmp r3, #0x0
	movne r3, #0x1
	str lr, [r12, #0x0]
	orr r2, r1, r2, lsl #0x10
	moveq r3, #0x0
	ldr r1, [r0, #0x4]
	orr r2, r2, r3, lsl #0xf
	str r2, [r1, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start G3B_MaterialColorDiffAmb
G3B_MaterialColorDiffAmb: ; 0x020C76EC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r12, [r0, #0x0]
	mov lr, #0x30
	cmp r3, #0x0
	movne r3, #0x1
	str lr, [r12, #0x0]
	orr r2, r1, r2, lsl #0x10
	moveq r3, #0x0
	ldr r1, [r0, #0x4]
	orr r2, r2, r3, lsl #0xf
	str r2, [r1, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start G3B_PolygonAttr
G3B_PolygonAttr: ; 0x020C7740
	orr r1, r1, r2, lsl #0x4
	ldr r2, [r0, #0x0]
	mov r12, #0x29
	str r12, [r2, #0x0]
	ldr r2, [sp, #0x8]
	orr r1, r1, r3, lsl #0x6
	ldr r3, [sp, #0x0]
	orr r1, r2, r1
	ldr r12, [sp, #0x4]
	orr r2, r1, r3, lsl #0x18
	ldr r1, [r0, #0x4]
	orr r2, r2, r12, lsl #0x10
	str r2, [r1, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start G3B_Vtx
G3B_Vtx: ; 0x020C7790
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r12, [r0, #0x0]
	mov lr, #0x23
	str lr, [r12, #0x0]
	mov r1, r1, lsl #0x10
	mov r2, r2, lsl #0x10
	mov lr, r1, lsr #0x10
	mov r12, r2, lsr #0x10
	mov r1, r3, lsl #0x10
	ldr r2, [r0, #0x4]
	orr r3, lr, r12, lsl #0x10
	str r3, [r2, #0x0]
	ldr r2, [r0, #0x4]
	mov r1, r1, lsr #0x10
	str r1, [r2, #0x4]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x8
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start G3B_Normal
G3B_Normal: ; 0x020C77F4
	stmdb sp!, {r4,lr}
	ldr ip, _020C7844 ; =0x000003FF
	ldr lr, [r0, #0x0]
	mov r4, #0x21
	str r4, [lr, #0x0]
	and lr, r12, r1, asr #0x3
	and r1, r12, r2, asr #0x3
	and r3, r12, r3, asr #0x3
	orr r2, lr, r1, lsl #0xa
	ldr r1, [r0, #0x4]
	orr r2, r2, r3, lsl #0x14
	str r2, [r1, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C7844: .word 0x000003FF

	arm_func_start G3B_Color
G3B_Color: ; 0x020C7848
	ldr r2, [r0, #0x0]
	mov r3, #0x20
	str r3, [r2, #0x0]
	ldr r2, [r0, #0x4]
	str r1, [r2, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start G3B_LoadMtx44
G3B_LoadMtx44: ; 0x020C7878
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl G3BS_LoadMtx44
	ldr r0, [r4, #0x4]
	add r0, r0, #0x40
	str r0, [r4, #0x0]
	ldr r0, [r4, #0x0]
	add r0, r0, #0x4
	str r0, [r4, #0x4]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start G3B_PopMtx
G3B_PopMtx: ; 0x020C78A4
	ldr r2, [r0, #0x0]
	mov r3, #0x12
	str r3, [r2, #0x0]
	ldr r2, [r0, #0x4]
	str r1, [r2, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start G3B_PushMtx
G3B_PushMtx: ; 0x020C78D4
	ldr r1, [r0, #0x0]
	mov r2, #0x11
	str r2, [r1, #0x0]
	ldr r1, [r0, #0x4]
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start G3BS_LoadMtx44
G3BS_LoadMtx44: ; 0x020C78F8
	mov r3, r0
	ldr r0, [r3, #0x0]
	mov r2, #0x16
	str r2, [r0, #0x0]
	mov r0, r1
	ldr ip, _020C7918 ; =MI_Copy64B
	ldr r1, [r3, #0x4]
	bx r12
	.balign 4
_020C7918: .word MI_Copy64B

	arm_func_start G3_MultMtx33
G3_MultMtx33: ; 0x020C791C
	ldr r1, _020C7930 ; =0x04000400
	mov r2, #0x1a
	ldr ip, _020C7934 ; =MI_Copy36B
	str r2, [r1, #0x0]
	bx r12
	.balign 4
_020C7930: .word 0x04000400
_020C7934: .word MI_Copy36B

	arm_func_start G3_MultMtx43
G3_MultMtx43:
	ldr r1, _020C794C ; =0x04000400
	mov r2, #0x19
	ldr ip, _020C7950 ; =GX_SendFifo48B
	str r2, [r1, #0x0]
	bx r12
	.balign 4
_020C794C: .word 0x04000400
_020C7950: .word GX_SendFifo48B

	arm_func_start G3_LoadMtx43
G3_LoadMtx43: ; 0x020C7954
	ldr r1, _020C7968 ; =0x04000400
	mov r2, #0x17
	ldr ip, _020C796C ; =GX_SendFifo48B
	str r2, [r1, #0x0]
	bx r12
	.balign 4
_020C7968: .word 0x04000400
_020C796C: .word GX_SendFifo48B

	arm_func_start GXi_NopClearFifo128_
GXi_NopClearFifo128_: ; 0x020C7970
	mov r1, #0x0
	mov r2, #0x0
	mov r3, #0x0
	mov r12, #0x0
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	bx lr

	arm_func_start G3X_SetHOffset
G3X_SetHOffset: ; 0x020C7A04
	ldr r1, _020C7A10 ; =0x04000010
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020C7A10: .word 0x04000010

	arm_func_start G3X_GetBoxTestResult
G3X_GetBoxTestResult: ; 0x020C7A14
	ldr r2, _020C7A38 ; =0x04000600
	ldr r1, [r2, #0x0]
	ands r1, r1, #0x1
	ldreq r1, [r2, #0x0]
	mvnne r0, #0x0
	andeq r1, r1, #0x2
	streq r1, [r0, #0x0]
	moveq r0, #0x0
	bx lr
	.balign 4
_020C7A38: .word 0x04000600

	arm_func_start G3X_GetMtxStackLevelPJ
G3X_GetMtxStackLevelPJ:
	ldr r2, _020C7A64 ; =0x04000600
	ldr r1, [r2, #0x0]
	ands r1, r1, #0x4000
	ldreq r1, [r2, #0x0]
	mvnne r0, #0x0
	andeq r1, r1, #0x2000
	moveq r1, r1, lsr #0xd
	streq r1, [r0, #0x0]
	moveq r0, #0x0
	bx lr
	.balign 4
_020C7A64: .word 0x04000600

	arm_func_start G3X_GetMtxStackLevelPV
G3X_GetMtxStackLevelPV:
	ldr r2, _020C7A90 ; =0x04000600
	ldr r1, [r2, #0x0]
	ands r1, r1, #0x4000
	ldreq r1, [r2, #0x0]
	mvnne r0, #0x0
	andeq r1, r1, #0x1f00
	moveq r1, r1, lsr #0x8
	streq r1, [r0, #0x0]
	moveq r0, #0x0
	bx lr
	.balign 4
_020C7A90: .word 0x04000600

	arm_func_start G3X_InitTable
G3X_InitTable: ; 0x020C7A94
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r0, _020C7B2C ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C7AE4
	mov r2, #0x0
	str r2, [sp, #0x0]
	ldr r1, _020C7B30 ; =0x04000330
	mov r3, #0x10
	str r2, [sp, #0x4]
	bl MI_DmaFill32Async
	ldr r0, _020C7B2C ; =0x02106814
	ldr r1, _020C7B34 ; =0x04000360
	ldr r0, [r0, #0x0]
	mov r2, #0x0
	mov r3, #0x60
	bl MI_DmaFill32
	b _020C7B04
_020C7AE4:
	ldr r1, _020C7B30 ; =0x04000330
	mov r0, #0x0
	mov r2, #0x10
	bl MIi_CpuClear32
	ldr r1, _020C7B34 ; =0x04000360
	mov r0, #0x0
	mov r2, #0x60
	bl MIi_CpuClear32
_020C7B04:
	mov r2, #0x0
	ldr r0, _020C7B38 ; =0x040004D0
	mov r1, r2
_020C7B10:
	add r2, r2, #0x1
	str r1, [r0, #0x0]
	cmp r2, #0x20
	blt _020C7B10
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C7B2C: .word 0x02106814
_020C7B30: .word 0x04000330
_020C7B34: .word 0x04000360
_020C7B38: .word 0x040004D0

	arm_func_start G3X_SetClearColor
G3X_SetClearColor: ; 0x020C7B3C
	orr r0, r0, r1, lsl #0x10
	ldr r12, [sp, #0x0]
	orr r3, r0, r3, lsl #0x18
	cmp r12, #0x0
	ldr r1, _020C7B64 ; =0x04000350
	orrne r3, r3, #0x8000
	ldr r0, _020C7B68 ; =0x04000354
	str r3, [r1, #0x0]
	strh r2, [r0, #0x0]
	bx lr
	.balign 4
_020C7B64: .word 0x04000350
_020C7B68: .word 0x04000354

	arm_func_start G3X_SetFogTable
G3X_SetFogTable: ; 0x020C7B6C
	ldr ip, _020C7B78 ; =0x020CE2C4
	ldr r1, _020C7B7C ; =0x04000360
	bx r12
	.balign 4
_020C7B78: .word 0x020CE2C4
_020C7B7C: .word 0x04000360

	arm_func_start G3X_SetEdgeColorTable
G3X_SetEdgeColorTable: ; 0x020C7B80
	ldr ip, _020C7B90 ; =MIi_CpuCopy16
	ldr r1, _020C7B94 ; =0x04000330
	mov r2, #0x10
	bx r12
	.balign 4
_020C7B90: .word MIi_CpuCopy16
_020C7B94: .word 0x04000330

	arm_func_start G3X_GetVectorMtx
G3X_GetVectorMtx:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020C7BD8 ; =0x04000600
	mov r1, r0
	ldr r0, [r2, #0x0]
	ands r0, r0, #0x8000000
	addne sp, sp, #0x4
	mvnne r0, #0x0
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020C7BDC ; =0x04000680
	bl MI_Copy36B
_020C7BC8: ; 0x020C7BC8
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C7BD8: .word 0x04000600
_020C7BDC: .word 0x04000680

	arm_func_start G3X_GetClipMtx
G3X_GetClipMtx:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020C7C20 ; =0x04000600
	mov r1, r0
	ldr r0, [r2, #0x0]
	ands r0, r0, #0x8000000
	addne sp, sp, #0x4
	mvnne r0, #0x0
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020C7C24 ; =0x04000640
	bl MI_Copy64B
_020C7C10: ; 0x020C7C10
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C7C20: .word 0x04000600
_020C7C24: .word 0x04000640

	arm_func_start G3X_SetFog
G3X_SetFog: ; 0x020C7C28
	cmp r0, #0x0
	ldreq r2, _020C7C70 ; =0x04000060
	ldreq r0, _020C7C74 ; =0x0000CF7F
	ldreqh r1, [r2, #0x0]
	andeq r0, r1, r0
	streqh r0, [r2, #0x0]
	bxeq lr
	ldr r0, _020C7C78 ; =0x0400035C
	ldr ip, _020C7C70 ; =0x04000060
	strh r3, [r0, #0x0]
	mov r0, r2, lsl #0x8
	orr r0, r0, r1, lsl #0x6
	ldrh r3, [r12, #0x0]
	orr r0, r0, #0x80
	bic r1, r3, #0x3f40
	orr r0, r1, r0
	strh r0, [r12, #0x0]
	bx lr
	.balign 4
_020C7C70: .word 0x04000060
_020C7C74: .word 0x0000CF7F
_020C7C78: .word 0x0400035C

	arm_func_start G3X_ResetMtxStack_2
G3X_ResetMtxStack_2: ; 0x020C7C7C
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldr r1, _020C7D18 ; =0x04000600
	ldr r0, [r1, #0x0]
	orr r0, r0, #0x8000
	str r0, [r1, #0x0]
	add r4, sp, #0x0
_020C7C98:
	mov r0, r4
	bl G3X_GetMtxStackLevelPV
_020C7CA0: ; 0x020C7CA0
	cmp r0, #0x0
	bne _020C7C98
	add r4, sp, #0x4
_020C7CAC:
	mov r0, r4
	bl G3X_GetMtxStackLevelPJ
_020C7CB4: ; 0x020C7CB4
	cmp r0, #0x0
	bne _020C7CAC
	ldr r2, _020C7D1C ; =0x04000440
	mov r1, #0x3
	str r1, [r2, #0x0]
	ldr r0, _020C7D20 ; =0x04000454
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r2, #0x0]
	ldr r1, [sp, #0x4]
	cmp r1, #0x0
	ldrne r0, _020C7D24 ; =0x04000448
	strne r1, [r0, #0x0]
	ldr r0, _020C7D1C ; =0x04000440
	mov r1, #0x2
	str r1, [r0, #0x0]
	ldr r2, [sp, #0x0]
	ldr r1, _020C7D24 ; =0x04000448
	ldr r0, _020C7D20 ; =0x04000454
	str r2, [r1, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C7D18: .word 0x04000600
_020C7D1C: .word 0x04000440
_020C7D20: .word 0x04000454
_020C7D24: .word 0x04000448

	arm_func_start G3X_InitMtxStack
G3X_InitMtxStack: ; 0x020C7D28
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldr r1, _020C7DC8 ; =0x04000600
	ldr r0, [r1, #0x0]
	orr r0, r0, #0x8000
	str r0, [r1, #0x0]
	add r4, sp, #0x0
_020C7D44:
	mov r0, r4
	bl G3X_GetMtxStackLevelPV
_020C7D4C: ; 0x020C7D4C
	cmp r0, #0x0
	bne _020C7D44
	add r4, sp, #0x4
_020C7D58:
	mov r0, r4
	bl G3X_GetMtxStackLevelPJ
_020C7D60: ; 0x020C7D60
	cmp r0, #0x0
	bne _020C7D58
	ldr r2, _020C7DCC ; =0x04000440
	mov r1, #0x3
	str r1, [r2, #0x0]
	ldr r0, _020C7DD0 ; =0x04000454
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r2, #0x0]
	ldr r1, [sp, #0x4]
	ldr r2, _020C7DD0 ; =0x04000454
	cmp r1, #0x0
	ldrne r0, _020C7DD4 ; =0x04000448
	mov r3, #0x0
	strne r1, [r0, #0x0]
	ldr r0, _020C7DCC ; =0x04000440
	str r3, [r2, #0x0]
	mov r1, #0x2
	str r1, [r0, #0x0]
	ldr r1, [sp, #0x0]
	ldr r0, _020C7DD4 ; =0x04000448
	str r1, [r0, #0x0]
	str r3, [r2, #0x0]
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C7DC8: .word 0x04000600
_020C7DCC: .word 0x04000440
_020C7DD0: .word 0x04000454
_020C7DD4: .word 0x04000448

	arm_func_start G3X_ClearFifo
G3X_ClearFifo: ; 0x020C7DD8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C7E04 ; =0x04000400
	bl GXi_NopClearFifo128_
	ldr r1, _020C7E08 ; =0x04000600
_020C7DEC:
	ldr r0, [r1, #0x0]
	ands r0, r0, #0x8000000
	bne _020C7DEC
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C7E04: .word 0x04000400
_020C7E08: .word 0x04000600

	arm_func_start G3X_ResetMtxStack
G3X_ResetMtxStack: ; 0x020C7E0C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020C7E7C ; =0x04000600
_020C7E18:
	ldr r0, [r2, #0x0]
	ands r0, r0, #0x8000000
	bne _020C7E18
	ldr r0, [r2, #0x0]
	ldr r1, _020C7E80 ; =0x04000060
	orr r0, r0, #0x8000
	str r0, [r2, #0x0]
	ldrh r0, [r1, #0x0]
	orr r0, r0, #0x2000
	strh r0, [r1, #0x0]
	ldrh r0, [r1, #0x0]
	orr r0, r0, #0x1000
	strh r0, [r1, #0x0]
	bl G3X_ResetMtxStack_2
	ldr r2, _020C7E84 ; =0x001F0080
	ldr r0, _020C7E88 ; =0x040004A4
	ldr r1, _020C7E8C ; =0x040004A8
	str r2, [r0, #0x0]
	mov r2, #0x0
	ldr r0, _020C7E90 ; =0x040004AC
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C7E7C: .word 0x04000600
_020C7E80: .word 0x04000060
_020C7E84: .word 0x001F0080
_020C7E88: .word 0x040004A4
_020C7E8C: .word 0x040004A8
_020C7E90: .word 0x040004AC

	arm_func_start G3X_Init
G3X_Init: ; 0x020C7E94
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl G3X_ClearFifo
	ldr r0, _020C7FAC ; =0x04000504
	mov r1, #0x0
	str r1, [r0, #0x0]
	ldr r1, _020C7FB0 ; =0x04000600
_020C7EB0:
	ldr r0, [r1, #0x0]
	ands r0, r0, #0x8000000
	bne _020C7EB0
	ldr r0, _020C7FB4 ; =0x04000060
	mov r3, #0x0
	strh r3, [r0, #0x0]
	ldr r2, _020C7FB8 ; =0x04000010
	str r3, [r1, #0x0]
	str r3, [r2, #0x0]
	ldrh r12, [r0, #0x0]
	ldr r2, _020C7FBC ; =0xFFFFCFFD
	ldr r3, _020C7FC0 ; =0x0000CFFB
	orr r12, r12, #0x2000
	strh r12, [r0, #0x0]
	ldrh r12, [r0, #0x0]
	orr r12, r12, #0x1000
	strh r12, [r0, #0x0]
	ldrh r12, [r0, #0x0]
	and r2, r12, r2
	strh r2, [r0, #0x0]
	ldrh r2, [r0, #0x0]
	bic r2, r2, #0x3000
	orr r2, r2, #0x10
	strh r2, [r0, #0x0]
	ldrh r2, [r0, #0x0]
	and r2, r2, r3
	strh r2, [r0, #0x0]
	ldr r0, [r1, #0x0]
	orr r0, r0, #0x8000
	str r0, [r1, #0x0]
	ldr r0, [r1, #0x0]
	bic r0, r0, #0xc0000000
	orr r0, r0, #0x80000000
	str r0, [r1, #0x0]
	bl G3X_InitMtxStack
	ldr r0, _020C7FC4 ; =0x04000350
	mov r3, #0x0
	ldr r2, _020C7FC8 ; =0x00007FFF
	ldr r1, _020C7FCC ; =0x04000354
	str r3, [r0, #0x0]
	ldr r0, _020C7FD0 ; =0x04000356
	strh r2, [r1, #0x0]
	ldr r1, _020C7FD4 ; =0x04000358
	strh r3, [r0, #0x0]
	ldr r0, _020C7FD8 ; =0x0400035C
	str r3, [r1, #0x0]
	ldr r1, _020C7FDC ; =0x04000008
	strh r3, [r0, #0x0]
	ldrh r0, [r1, #0x0]
	bic r0, r0, #0x3
	strh r0, [r1, #0x0]
	bl G3X_InitTable
	ldr r2, _020C7FE0 ; =0x001F0080
	ldr r0, _020C7FE4 ; =0x040004A4
	ldr r1, _020C7FE8 ; =0x040004A8
	str r2, [r0, #0x0]
	mov r2, #0x0
	ldr r0, _020C7FEC ; =0x040004AC
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C7FAC: .word 0x04000504
_020C7FB0: .word 0x04000600
_020C7FB4: .word 0x04000060
_020C7FB8: .word 0x04000010
_020C7FBC: .word 0xFFFFCFFD
_020C7FC0: .word 0x0000CFFB
_020C7FC4: .word 0x04000350
_020C7FC8: .word 0x00007FFF
_020C7FCC: .word 0x04000354
_020C7FD0: .word 0x04000356
_020C7FD4: .word 0x04000358
_020C7FD8: .word 0x0400035C
_020C7FDC: .word 0x04000008
_020C7FE0: .word 0x001F0080
_020C7FE4: .word 0x040004A4
_020C7FE8: .word 0x040004A8
_020C7FEC: .word 0x040004AC

	arm_func_start G3_RotZ
G3_RotZ: ; 0x020C7FF0
	ldr r3, _020C8028 ; =0x04000468
	mov r2, #0x0
	str r1, [r3, #0x0]
	str r0, [r3, #0x0]
	str r2, [r3, #0x0]
	rsb r0, r0, #0x0
	str r0, [r3, #0x0]
	str r1, [r3, #0x0]
	str r2, [r3, #0x0]
	str r2, [r3, #0x0]
	str r2, [r3, #0x0]
	mov r0, #0x1000
	str r0, [r3, #0x0]
	bx lr
	.balign 4
_020C8028: .word 0x04000468

	arm_func_start G3_RotY
G3_RotY: ; 0x020C802C
	ldr ip, _020C8064 ; =0x04000468
	mov r3, #0x0
	str r1, [r12, #0x0]
	str r3, [r12, #0x0]
	rsb r2, r0, #0x0
	str r2, [r12, #0x0]
	str r3, [r12, #0x0]
	mov r2, #0x1000
	str r2, [r12, #0x0]
	str r3, [r12, #0x0]
	str r0, [r12, #0x0]
	str r3, [r12, #0x0]
	str r1, [r12, #0x0]
	bx lr
	.balign 4
_020C8064: .word 0x04000468

	arm_func_start G3_RotX
G3_RotX: ; 0x020C8068
	ldr r3, _020C80A0 ; =0x04000468
	mov r2, #0x1000
	str r2, [r3, #0x0]
	mov r2, #0x0
	str r2, [r3, #0x0]
	str r2, [r3, #0x0]
	str r2, [r3, #0x0]
	str r1, [r3, #0x0]
	str r0, [r3, #0x0]
	str r2, [r3, #0x0]
	rsb r0, r0, #0x0
	str r0, [r3, #0x0]
	str r1, [r3, #0x0]
	bx lr
	.balign 4
_020C80A0: .word 0x04000468

	arm_func_start G3i_LookAt_
G3i_LookAt_: ; 0x020C80A4
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x24
	mov r9, r0
	ldr r6, [r9, #0x0]
	ldr r5, [r2, #0x0]
	add r0, sp, #0x0
	sub r5, r6, r5
	str r5, [sp, #0x0]
	ldr r7, [r9, #0x4]
	ldr r6, [r2, #0x4]
	mov r5, r1
	sub r1, r7, r6
	str r1, [sp, #0x4]
	ldr r6, [r9, #0x8]
	ldr r2, [r2, #0x8]
	mov r1, r0
	sub r2, r6, r2
	mov r8, r3
	str r2, [sp, #0x8]
	ldr r7, [sp, #0x40]
	bl VEC_Normalize
	add r1, sp, #0x0
	add r2, sp, #0xc
	mov r0, r5
	bl VEC_CrossProduct
	add r0, sp, #0xc
	mov r1, r0
	bl VEC_Normalize
_020C8114: ; 0x020C8114
	add r0, sp, #0x0
	add r1, sp, #0xc
	add r2, sp, #0x18
	bl VEC_CrossProduct
_020C8124: ; 0x020C8124
	cmp r8, #0x0
	beq _020C8184
	ldr r0, _020C8234 ; =0x04000440
	mov r1, #0x2
	str r1, [r0, #0x0]
	ldr r0, [sp, #0xc]
	ldr r4, _020C8238 ; =0x0400045C
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x18]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x0]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x10]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x1c]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x4]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x14]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x20]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x8]
	str r0, [r4, #0x0]
_020C8184:
	add r1, sp, #0xc
	mov r0, r9
	bl VEC_DotProduct
	rsb r6, r0, #0x0
	add r1, sp, #0x18
	mov r0, r9
	bl VEC_DotProduct
	rsb r5, r0, #0x0
	add r1, sp, #0x0
	mov r0, r9
	bl VEC_DotProduct
_020C81B0: ; 0x020C81B0
	cmp r8, #0x0
	strne r6, [r4, #0x0]
	rsb r0, r0, #0x0
	strne r5, [r4, #0x0]
	strne r0, [r4, #0x0]
	cmp r7, #0x0
	addeq sp, sp, #0x24
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r1, [sp, #0xc]
	str r1, [r7, #0x0]
	ldr r1, [sp, #0x18]
	str r1, [r7, #0x4]
	ldr r1, [sp, #0x0]
	str r1, [r7, #0x8]
	ldr r1, [sp, #0x10]
	str r1, [r7, #0xc]
	ldr r1, [sp, #0x1c]
	str r1, [r7, #0x10]
	ldr r1, [sp, #0x4]
	str r1, [r7, #0x14]
	ldr r1, [sp, #0x14]
	str r1, [r7, #0x18]
	ldr r1, [sp, #0x20]
	str r1, [r7, #0x1c]
	ldr r1, [sp, #0x8]
	str r1, [r7, #0x20]
	str r6, [r7, #0x24]
	str r5, [r7, #0x28]
	str r0, [r7, #0x2c]
	add sp, sp, #0x24
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020C8234: .word 0x04000440
_020C8238: .word 0x0400045C

	arm_func_start G3i_OrthoW_
G3i_OrthoW_: ; 0x020C823C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x34
	str r2, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x8]
	mov r2, r3
	ldr r7, [sp, #0x64]
	sub r0, r2, r0
	str r3, [sp, #0xc]
	str r1, [sp, #0x4]
	ldr r8, [sp, #0x60]
	ldr r6, [sp, #0x68]
	bl FX_InvAsync
_020C8270: ; 0x020C8270
	cmp r7, #0x0
	ldrne r0, _020C8528 ; =0x04000440
	movne r1, #0x0
	ldrne r4, _020C852C ; =0x04000458
	strne r1, [r0, #0x0]
	cmp r6, #0x0
	beq _020C82B8
	mov r0, #0x0
	str r0, [r6, #0x4]
	str r0, [r6, #0x8]
	str r0, [r6, #0xc]
	str r0, [r6, #0x10]
	str r0, [r6, #0x18]
	str r0, [r6, #0x1c]
	str r0, [r6, #0x20]
	str r0, [r6, #0x24]
	str r0, [r6, #0x2c]
	str r8, [r6, #0x3c]
_020C82B8:
	bl FX_GetDivResultFx64c
	mov r5, r0
	str r1, [sp, #0x14]
	ldr sb, _020C8530 ; =0x04000290
	mov r3, #0x0
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x4]
	str r3, [r9, #0x0]
	mov r2, #0x1000
	sub r1, r1, r0
	ldr r0, _020C8534 ; =0x04000298
	str r2, [r9, #0x4]
	str r1, [r0, #0x0]
	cmp r8, #0x1000
	str r3, [r0, #0x4]
	beq _020C8318
	mov r9, r8, asr #0x1f
	umull r0, r1, r5, r8
	mla r1, r5, r9, r1
	ldr r5, [sp, #0x14]
	mla r1, r5, r8, r1
	bl _ll_sdiv
	mov r5, r0
	str r1, [sp, #0x14]
_020C8318:
	ldr r0, [sp, #0x14]
	mov r2, r5, lsl #0xd
	mov r1, r0, lsl #0xd
	mov r0, #0x80000000
	adds r0, r2, r0
	orr r1, r1, r5, lsr #0x13
	adc r1, r1, #0x0
	cmp r7, #0x0
	mov r0, #0x0
	strne r1, [r4, #0x0]
	strne r0, [r4, #0x0]
	strne r0, [r4, #0x0]
	strne r0, [r4, #0x0]
	strne r0, [r4, #0x0]
	cmp r6, #0x0
	strne r1, [r6, #0x0]
	bl FX_GetDivResultFx64c
	mov r11, r0
	str r1, [sp, #0x2c]
	ldr r0, _020C8530 ; =0x04000290
	mov r3, #0x0
	mov r2, #0x1000
	str r3, [r0, #0x0]
	str r2, [r0, #0x4]
	ldr r9, [sp, #0x58]
	ldr r1, [sp, #0x5c]
	ldr r0, _020C8534 ; =0x04000298
	sub r1, r9, r1
	str r1, [r0, #0x0]
	cmp r8, #0x1000
	str r3, [r0, #0x4]
	beq _020C83B8
	mov r9, r8, asr #0x1f
	umull r0, r1, r11, r8
	mla r1, r11, r9, r1
	ldr r9, [sp, #0x2c]
	mla r1, r9, r8, r1
	bl _ll_sdiv
	mov r11, r0
	str r1, [sp, #0x2c]
_020C83B8:
	ldr r0, [sp, #0x2c]
	mov r3, r11, lsl #0xd
	mov r2, r0, lsl #0xd
	mov r0, #0x80000000
	orr r2, r2, r11, lsr #0x13
	adds r0, r3, r0
	adc r0, r2, #0x0
	cmp r7, #0x0
	mov r1, #0x0
	strne r0, [r4, #0x0]
	strne r1, [r4, #0x0]
	strne r1, [r4, #0x0]
	strne r1, [r4, #0x0]
	strne r1, [r4, #0x0]
	cmp r6, #0x0
	strne r0, [r6, #0x14]
	bl FX_GetDivResultFx64c
	cmp r8, #0x1000
	beq _020C8428
	mov r9, r8, asr #0x1f
	mov r2, #0x1000
	mov r3, #0x0
	umull r12, r10, r0, r8
	mla r10, r0, r9, r10
	mov r0, r12
	mla r10, r1, r8, r10
	mov r1, r10
	bl _ll_sdiv
_020C8428:
	mov r9, r1, lsl #0xd
	mov r10, r0, lsl #0xd
	mov r2, #0x80000000
	orr r9, r9, r0, lsr #0x13
	adds r2, r10, r2
	adc r2, r9, #0x0
	cmp r7, #0x0
	mov r3, #0x0
	strne r2, [r4, #0x0]
	strne r3, [r4, #0x0]
	cmp r6, #0x0
	strne r2, [r6, #0x28]
	ldr r3, [sp, #0xc]
	ldr r2, [sp, #0x8]
	add r9, r3, r2
	rsb lr, r9, #0x0
	ldr r3, [sp, #0x0]
	ldr r2, [sp, #0x4]
	ldr r9, [sp, #0x5c]
	add r2, r3, r2
	ldr r3, [sp, #0x58]
	rsb r12, r2, #0x0
	add r3, r9, r3
	mov r9, r12, asr #0x1f
	str r9, [sp, #0x20]
	mov r9, r3, asr #0x1f
	str r9, [sp, #0x24]
	umull r10, r9, r5, lr
	mov r2, lr, asr #0x1f
	str r2, [sp, #0x1c]
	str r10, [sp, #0x18]
	ldr r10, [sp, #0x1c]
	mov r2, #0x80000000
	mla r9, r5, r10, r9
	ldr r5, [sp, #0x14]
	mla r9, r5, lr, r9
	ldr r5, [sp, #0x18]
	adds r5, r5, r2
	adc r10, r9, #0x0
	ldr r5, [sp, #0x20]
	umull lr, r9, r11, r12
	mla r9, r11, r5, r9
	ldr r5, [sp, #0x2c]
	mla r9, r5, r12, r9
	adds r5, lr, r2
	adc r5, r9, #0x0
	umull r11, r9, r0, r3
	adds r2, r11, r2
	ldr r2, [sp, #0x24]
	mla r9, r0, r2, r9
	mla r9, r1, r3, r9
	adc r0, r9, #0x0
	cmp r7, #0x0
	strne r10, [r4, #0x0]
	strne r5, [r4, #0x0]
	strne r0, [r4, #0x0]
	strne r8, [r4, #0x0]
	cmp r6, #0x0
	strne r10, [r6, #0x30]
	strne r5, [r6, #0x34]
	strne r0, [r6, #0x38]
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020C8528: .word 0x04000440
_020C852C: .word 0x04000458
_020C8530: .word 0x04000290
_020C8534: .word 0x04000298

	arm_func_start G3i_PerspectiveW_
G3i_PerspectiveW_: ; 0x020C8538
	stmdb sp!, {r4-r10,lr}
	mov r5, r0
	mov r0, r1
	mov r1, r5
	ldr r6, [sp, #0x24]
	mov r9, r2
	mov r8, r3
	ldr r5, [sp, #0x2c]
	bl FX_Div
	mov r7, r0
	cmp r6, #0x1000
	mulne r1, r7, r6
	movne r0, r1, asr #0xb
	addne r0, r1, r0, lsr #0x14
	movne r7, r0, asr #0xc
	ldr r0, [sp, #0x28]
	ldr r2, _020C8718 ; =0x04000290
	cmp r0, #0x0
	mov r3, #0x0
	str r3, [r2, #0x0]
	ldr r1, _020C871C ; =0x04000298
	str r7, [r2, #0x4]
	str r9, [r1, #0x0]
	ldrne r0, _020C8720 ; =0x04000440
	str r3, [r1, #0x4]
	ldrne r4, _020C8724 ; =0x04000458
	strne r3, [r0, #0x0]
	cmp r5, #0x0
	beq _020C85E4
	mov r1, #0x0
	str r1, [r5, #0x4]
	str r1, [r5, #0x8]
	str r1, [r5, #0xc]
	str r1, [r5, #0x10]
	str r1, [r5, #0x18]
	str r1, [r5, #0x1c]
	str r1, [r5, #0x20]
	str r1, [r5, #0x24]
	rsb r0, r6, #0x0
	str r0, [r5, #0x2c]
	str r1, [r5, #0x30]
	str r1, [r5, #0x34]
	str r1, [r5, #0x3c]
_020C85E4:
	bl FX_GetDivResult
	ldr r3, [sp, #0x20]
	ldr r1, [sp, #0x28]
	ldr sb, _020C8718 ; =0x04000290
	mov r12, #0x0
	str r12, [r9, #0x0]
	mov r10, #0x1000
	ldr r2, _020C871C ; =0x04000298
	str r10, [r9, #0x4]
	sub r3, r8, r3
	str r3, [r2, #0x0]
	str r12, [r2, #0x4]
	cmp r1, #0x0
	beq _020C8644
	str r0, [r4, #0x0]
	str r12, [r4, #0x0]
	str r12, [r4, #0x0]
	str r12, [r4, #0x0]
	str r12, [r4, #0x0]
	str r7, [r4, #0x0]
	str r12, [r4, #0x0]
	str r12, [r4, #0x0]
	str r12, [r4, #0x0]
	str r12, [r4, #0x0]
_020C8644:
	cmp r5, #0x0
	strne r0, [r5, #0x0]
	strne r7, [r5, #0x14]
	bl FX_GetDivResultFx64c
	cmp r6, #0x1000
	beq _020C8680
	mov r2, r6, asr #0x1f
	umull r7, r3, r0, r6
	mla r3, r0, r2, r3
	mla r3, r1, r6, r3
	mov r0, r7
	mov r1, r3
	mov r2, #0x1000
	mov r3, #0x0
	bl _ll_sdiv
_020C8680:
	ldr r3, [sp, #0x20]
	mov r10, r8, lsl #0x1
	add r12, r3, r8
	mov r2, r12, asr #0x1f
	umull r7, lr, r0, r12
	mla lr, r0, r2, lr
	mov r9, #0x80000000
	smull r3, r2, r10, r3
	mla lr, r1, r12, lr
	adds r7, r7, r9
	mov r8, #0x800
	adc r7, lr, #0x0
	adds r3, r3, r8
	adc r2, r2, #0x0
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	umull r10, r8, r0, r3
	mov r2, r3, asr #0x1f
	adds r9, r10, r9
	mla r8, r0, r2, r8
	mla r8, r1, r3, r8
	ldr r0, [sp, #0x28]
	adc r2, r8, #0x0
	cmp r0, #0x0
	mov r0, #0x0
	beq _020C8704
	str r7, [r4, #0x0]
	rsb r1, r6, #0x0
	str r1, [r4, #0x0]
	str r0, [r4, #0x0]
	str r0, [r4, #0x0]
	str r2, [r4, #0x0]
	str r0, [r4, #0x0]
_020C8704:
	cmp r5, #0x0
	strne r7, [r5, #0x28]
	strne r2, [r5, #0x38]
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_020C8718: .word 0x04000290
_020C871C: .word 0x04000298
_020C8720: .word 0x04000440
_020C8724: .word 0x04000458

	arm_func_start GXS_EndLoadOBJExtPltt
GXS_EndLoadOBJExtPltt: ; 0x020C8728
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C876C ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C8748
	bl MI_WaitDma
_020C8748:
	ldr r0, _020C8770 ; =0x021D33F8
	ldr r0, [r0, #0x0]
	bl GX_SetBankForSubOBJExtPltt
	ldr r0, _020C8770 ; =0x021D33F8
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C876C: .word 0x02106814
_020C8770: .word 0x021D33F8

	arm_func_start GXS_LoadOBJExtPltt
GXS_LoadOBJExtPltt: ; 0x020C8774
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	ldr r3, _020C87E0 ; =0x02106814
	mvn r12, #0x0
	ldr lr, [r3, #0x0]
	mov r5, r0
	mov r4, r1
	mov r3, r2
	cmp lr, r12
	beq _020C87C8
	ldr r2, _020C87E4 ; =0x068A0000
	mov r12, #0x0
	str r12, [sp, #0x0]
	mov r0, lr
	mov r1, r5
	add r2, r4, r2
	str r12, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
_020C87C8:
	ldr r1, _020C87E4 ; =0x068A0000
	add r1, r4, r1
	bl MIi_CpuCopy32
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020C87E0: .word 0x02106814
_020C87E4: .word 0x068A0000

	arm_func_start GXS_BeginLoadOBJExtPltt
GXS_BeginLoadOBJExtPltt: ; 0x020C87E8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl GX_ResetBankForSubOBJ
	ldr r1, _020C8808 ; =0x021D33F8
	str r0, [r1, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C8808: .word 0x021D33F8

	arm_func_start GXS_EndLoadBGExtPltt
GXS_EndLoadBGExtPltt: ; 0x020C880C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C8850 ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C882C
	bl MI_WaitDma
_020C882C:
	ldr r0, _020C8854 ; =0x021D33E0
	ldr r0, [r0, #0x0]
	bl GX_SetBankForSubBGExtPltt
	ldr r0, _020C8854 ; =0x021D33E0
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C8850: .word 0x02106814
_020C8854: .word 0x021D33E0

	arm_func_start GXS_LoadBGExtPltt
GXS_LoadBGExtPltt: ; 0x020C8858
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	ldr r3, _020C88C4 ; =0x02106814
	mvn r12, #0x0
	ldr lr, [r3, #0x0]
	mov r5, r0
	mov r4, r1
	mov r3, r2
	cmp lr, r12
	beq _020C88AC
	ldr r2, _020C88C8 ; =0x06898000
	mov r12, #0x0
	str r12, [sp, #0x0]
	mov r0, lr
	mov r1, r5
	add r2, r4, r2
	str r12, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
_020C88AC:
	ldr r1, _020C88C8 ; =0x06898000
	add r1, r4, r1
	bl MIi_CpuCopy32
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020C88C4: .word 0x02106814
_020C88C8: .word 0x06898000

	arm_func_start GXS_BeginLoadBGExtPltt
GXS_BeginLoadBGExtPltt: ; 0x020C88CC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020C6034
	ldr r1, _020C88EC ; =0x021D33E0
	str r0, [r1, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C88EC: .word 0x021D33E0

	arm_func_start GX_EndLoadOBJExtPltt
GX_EndLoadOBJExtPltt: ; 0x020C88F0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C893C ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C8910
	bl MI_WaitDma
_020C8910:
	ldr r0, _020C8940 ; =0x021D33E8
	ldr r0, [r0, #0x0]
	bl GX_SetBankForOBJExtPltt
	ldr r1, _020C8940 ; =0x021D33E8
	mov r2, #0x0
	ldr r0, _020C8944 ; =0x021D33E4
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C893C: .word 0x02106814
_020C8940: .word 0x021D33E8
_020C8944: .word 0x021D33E4

	arm_func_start GX_LoadOBJExtPltt
GX_LoadOBJExtPltt: ; 0x020C8948
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	ldr ip, _020C89B4 ; =0x021D33E4
	ldr r3, _020C89B8 ; =0x02106814
	ldr r4, [r12, #0x0]
	ldr lr, [r3, #0x0]
	mvn r12, #0x0
	mov r5, r0
	mov r3, r2
	cmp lr, r12
	add r4, r4, r1
	beq _020C89A0
	mov r12, #0x0
	str r12, [sp, #0x0]
	mov r0, lr
	mov r1, r5
	mov r2, r4
	str r12, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
_020C89A0:
	mov r1, r4
	bl MIi_CpuCopy32
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020C89B4: .word 0x021D33E4
_020C89B8: .word 0x02106814

	arm_func_start GX_BeginLoadOBJExtPltt
GX_BeginLoadOBJExtPltt: ; 0x020C89BC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl GX_ResetBankForOBJExtPltt
	ldr r1, _020C8A1C ; =0x021D33E8
	cmp r0, #0x0
	str r0, [r1, #0x0]
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	cmp r0, #0x20
	beq _020C8A04
	cmp r0, #0x40
	ldreq r1, _020C8A20 ; =0x06894000
	ldreq r0, _020C8A24 ; =0x021D33E4
	add sp, sp, #0x4
	streq r1, [r0, #0x0]
	ldmia sp!, {lr}
	bx lr
_020C8A04:
	ldr r1, _020C8A28 ; =0x06890000
	ldr r0, _020C8A24 ; =0x021D33E4
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C8A1C: .word 0x021D33E8
_020C8A20: .word 0x06894000
_020C8A24: .word 0x021D33E4
_020C8A28: .word 0x06890000

	arm_func_start GX_EndLoadBGExtPltt
GX_EndLoadBGExtPltt: ; 0x020C8A2C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C8A80 ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C8A4C
	bl MI_WaitDma
_020C8A4C:
	ldr r0, _020C8A84 ; =0x021D33F4
	ldr r0, [r0, #0x0]
	bl GX_SetBankForBGExtPltt
	ldr r2, _020C8A84 ; =0x021D33F4
	mov r3, #0x0
	ldr r1, _020C8A88 ; =0x021D33F0
	ldr r0, _020C8A8C ; =0x021D33EC
	str r3, [r2, #0x0]
	str r3, [r1, #0x0]
	str r3, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C8A80: .word 0x02106814
_020C8A84: .word 0x021D33F4
_020C8A88: .word 0x021D33F0
_020C8A8C: .word 0x021D33EC

	arm_func_start GX_LoadBGExtPltt
GX_LoadBGExtPltt: ; 0x020C8A90
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	ldr lr, _020C8B04 ; =0x021D33F0
	ldr ip, _020C8B08 ; =0x021D33EC
	ldr r3, _020C8B0C ; =0x02106814
	ldr lr, [lr, #0x0]
	ldr r4, [r12, #0x0]
	add r5, lr, r1
	ldr lr, [r3, #0x0]
	mvn r12, #0x0
	mov r1, r0
	mov r3, r2
	cmp lr, r12
	sub r4, r5, r4
	beq _020C8AF0
	mov r12, #0x0
	str r12, [sp, #0x0]
	mov r0, lr
	mov r2, r4
	str r12, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
_020C8AF0:
	mov r1, r4
	bl MIi_CpuCopy32
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020C8B04: .word 0x021D33F0
_020C8B08: .word 0x021D33EC
_020C8B0C: .word 0x02106814

	arm_func_start GX_BeginLoadBGExtPltt
GX_BeginLoadBGExtPltt: ; 0x020C8B10
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl GX_ResetBankForBGExtPltt
	ldr r1, _020C8BFC ; =0x021D33F4
	cmp r0, #0x20
	str r0, [r1, #0x0]
	bgt _020C8B60
	cmp r0, #0x20
	bge _020C8BD8
	cmp r0, #0x0
	bgt _020C8B4C
	add sp, sp, #0x4
	cmp r0, #0x0
	ldmia sp!, {lr}
	bx lr
_020C8B4C:
	cmp r0, #0x10
	beq _020C8B90
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020C8B60:
	cmp r0, #0x40
	bgt _020C8B7C
	cmp r0, #0x40
	beq _020C8BB4
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020C8B7C:
	cmp r0, #0x60
	beq _020C8BD8
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020C8B90:
	ldr r3, _020C8C00 ; =0x06880000
	ldr r1, _020C8C04 ; =0x021D33F0
	ldr r0, _020C8C08 ; =0x021D33EC
	mov r2, #0x0
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020C8BB4:
	ldr r3, _020C8C0C ; =0x06894000
	ldr r1, _020C8C04 ; =0x021D33F0
	ldr r0, _020C8C08 ; =0x021D33EC
	mov r2, #0x4000
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020C8BD8:
	ldr r3, _020C8C10 ; =0x06890000
	ldr r1, _020C8C04 ; =0x021D33F0
	ldr r0, _020C8C08 ; =0x021D33EC
	mov r2, #0x0
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C8BFC: .word 0x021D33F4
_020C8C00: .word 0x06880000
_020C8C04: .word 0x021D33F0
_020C8C08: .word 0x021D33EC
_020C8C0C: .word 0x06894000
_020C8C10: .word 0x06890000

	arm_func_start GXS_LoadBG3Char
GXS_LoadBG3Char: ; 0x020C8C14
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2S_GetBG3CharPtr
	ldr r1, _020C8C78 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8C60
	cmp r4, #0x30
	bls _020C8C60
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8C60:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8C78: .word 0x02106814

	arm_func_start GX_LoadBG3Char
GX_LoadBG3Char: ; 0x020C8C7C
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2_GetBG3CharPtr
	ldr r1, _020C8CE0 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8CC8
	cmp r4, #0x30
	bls _020C8CC8
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8CC8:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8CE0: .word 0x02106814

	arm_func_start GXS_LoadBG2Char
GXS_LoadBG2Char: ; 0x020C8CE4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2S_GetBG2CharPtr
	ldr r1, _020C8D48 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8D30
	cmp r4, #0x30
	bls _020C8D30
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8D30:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8D48: .word 0x02106814

	arm_func_start GX_LoadBG2Char
GX_LoadBG2Char: ; 0x020C8D4C
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2_GetBG2CharPtr
	ldr r1, _020C8DB0 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8D98
	cmp r4, #0x30
	bls _020C8D98
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8D98:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8DB0: .word 0x02106814

	arm_func_start GXS_LoadBG1Char
GXS_LoadBG1Char: ; 0x020C8DB4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2S_GetBG1CharPtr
	ldr r1, _020C8E18 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8E00
	cmp r4, #0x30
	bls _020C8E00
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8E00:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8E18: .word 0x02106814

	arm_func_start GX_LoadBG1Char
GX_LoadBG1Char: ; 0x020C8E1C
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2_GetBG1CharPtr
	ldr r1, _020C8E80 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8E68
	cmp r4, #0x30
	bls _020C8E68
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8E68:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8E80: .word 0x02106814

	arm_func_start GXS_LoadBG0Char
GXS_LoadBG0Char: ; 0x020C8E84
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2S_GetBG0CharPtr
	ldr r1, _020C8EE8 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8ED0
	cmp r4, #0x30
	bls _020C8ED0
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8ED0:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8EE8: .word 0x02106814

	arm_func_start GX_LoadBG0Char
GX_LoadBG0Char: ; 0x020C8EEC
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2_GetBG0CharPtr
	ldr r1, _020C8F50 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8F38
	cmp r4, #0x30
	bls _020C8F38
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8F38:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8F50: .word 0x02106814

	arm_func_start GXS_LoadBG3Scr
GXS_LoadBG3Scr: ; 0x020C8F54
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2S_GetBG3ScrPtr
	ldr r1, _020C8FB8 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8FA0
	cmp r4, #0x1c
	bls _020C8FA0
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8FA0:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8FB8: .word 0x02106814

	arm_func_start GX_LoadBG3Scr
GX_LoadBG3Scr: ; 0x020C8FBC
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2_GetBG3ScrPtr
	ldr r1, _020C9020 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C9008
	cmp r4, #0x1c
	bls _020C9008
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C9008:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C9020: .word 0x02106814

	arm_func_start GXS_LoadBG2Scr
GXS_LoadBG2Scr: ; 0x020C9024
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2S_GetBG2ScrPtr
	ldr r1, _020C9088 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C9070
	cmp r4, #0x1c
	bls _020C9070
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C9070:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C9088: .word 0x02106814

	arm_func_start GX_LoadBG2Scr
GX_LoadBG2Scr: ; 0x020C908C
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2_GetBG2ScrPtr
	ldr r1, _020C90F0 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C90D8
	cmp r4, #0x1c
	bls _020C90D8
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C90D8:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C90F0: .word 0x02106814

	arm_func_start GXS_LoadBG1Scr
GXS_LoadBG1Scr: ; 0x020C90F4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2S_GetBG1ScrPtr
	ldr r1, _020C9158 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C9140
	cmp r4, #0x1c
	bls _020C9140
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C9140:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C9158: .word 0x02106814

	arm_func_start GX_LoadBG1Scr
GX_LoadBG1Scr: ; 0x020C915C
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2_GetBG1ScrPtr
	ldr r1, _020C91C0 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C91A8
	cmp r4, #0x1c
	bls _020C91A8
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C91A8:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C91C0: .word 0x02106814

	arm_func_start GXS_LoadBG0Scr
GXS_LoadBG0Scr: ; 0x020C91C4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2S_GetBG0ScrPtr
	ldr r1, _020C9228 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C9210
	cmp r4, #0x1c
	bls _020C9210
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C9210:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C9228: .word 0x02106814

	arm_func_start GX_LoadBG0Scr
GX_LoadBG0Scr: ; 0x020C922C
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2_GetBG0ScrPtr
	ldr r1, _020C9290 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C9278
	cmp r4, #0x1c
	bls _020C9278
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C9278:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C9290: .word 0x02106814

	arm_func_start GXS_LoadOBJ
GXS_LoadOBJ: ; 0x020C9294
	stmdb sp!, {r4,lr}
	ldr r3, _020C92F0 ; =0x02106814
	mov r4, r0
	ldr r0, [r3, #0x0]
	mvn r12, #0x0
	mov lr, r1
	mov r3, r2
	cmp r0, r12
	mov r12, #0x6600000
	beq _020C92D8
	cmp r3, #0x30
	bls _020C92D8
	mov r1, r4
	add r2, r12, lr
	bl MI_DmaCopy32
	ldmia sp!, {r4,lr}
	bx lr
_020C92D8:
	mov r0, r4
	mov r2, r3
	add r1, r12, lr
	bl MIi_CpuCopy32
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C92F0: .word 0x02106814

	arm_func_start GX_LoadOBJ
GX_LoadOBJ: ; 0x020C92F4
	stmdb sp!, {r4,lr}
	ldr r3, _020C9350 ; =0x02106814
	mov r4, r0
	ldr r0, [r3, #0x0]
	mvn r12, #0x0
	mov lr, r1
	mov r3, r2
	cmp r0, r12
	mov r12, #0x6400000
	beq _020C9338
	cmp r3, #0x30
	bls _020C9338
	mov r1, r4
	add r2, r12, lr
	bl MI_DmaCopy32
	ldmia sp!, {r4,lr}
	bx lr
_020C9338:
	mov r0, r4
	mov r2, r3
	add r1, r12, lr
	bl MIi_CpuCopy32
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C9350: .word 0x02106814

	arm_func_start GXS_LoadOAM
GXS_LoadOAM: ; 0x020C9354
	stmdb sp!, {r4,lr}
	ldr r3, _020C93B4 ; =0x02106814
	mov r4, r0
	ldr r0, [r3, #0x0]
	mvn r12, #0x0
	mov lr, r1
	mov r3, r2
	cmp r0, r12
	beq _020C9398
	cmp r3, #0x30
	bls _020C9398
	ldr r2, _020C93B8 ; =0x07000400
	mov r1, r4
	add r2, lr, r2
	bl MI_DmaCopy32
	ldmia sp!, {r4,lr}
	bx lr
_020C9398:
	ldr r1, _020C93B8 ; =0x07000400
	mov r0, r4
	mov r2, r3
	add r1, lr, r1
	bl MIi_CpuCopy32
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C93B4: .word 0x02106814
_020C93B8: .word 0x07000400

	arm_func_start GX_LoadOAM
GX_LoadOAM: ; 0x020C93BC
	stmdb sp!, {r4,lr}
	ldr r3, _020C9414 ; =0x02106814
	mov r4, r0
	ldr r0, [r3, #0x0]
	mvn r12, #0x0
	mov lr, r1
	mov r3, r2
	cmp r0, r12
	beq _020C93FC
	cmp r3, #0x30
	bls _020C93FC
	mov r1, r4
	add r2, lr, #0x7000000
	bl MI_DmaCopy32
	ldmia sp!, {r4,lr}
	bx lr
_020C93FC:
	mov r0, r4
	mov r2, r3
	add r1, lr, #0x7000000
	bl MIi_CpuCopy32
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C9414: .word 0x02106814

	arm_func_start GXS_LoadOBJPltt
GXS_LoadOBJPltt: ; 0x020C9418
	stmdb sp!, {r4,lr}
	ldr r3, _020C9478 ; =0x02106814
	mov r4, r0
	ldr r0, [r3, #0x0]
	mvn r12, #0x0
	mov lr, r1
	mov r3, r2
	cmp r0, r12
	beq _020C945C
	cmp r3, #0x1c
	bls _020C945C
	ldr r2, _020C947C ; =0x05000600
	mov r1, r4
	add r2, lr, r2
	bl MI_DmaCopy16
	ldmia sp!, {r4,lr}
	bx lr
_020C945C:
	ldr r1, _020C947C ; =0x05000600
	mov r0, r4
	mov r2, r3
	add r1, lr, r1
	bl MIi_CpuCopy16
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C9478: .word 0x02106814
_020C947C: .word 0x05000600

	arm_func_start GX_LoadOBJPltt
GX_LoadOBJPltt: ; 0x020C9480
	stmdb sp!, {r4,lr}
	ldr r3, _020C94E0 ; =0x02106814
	mov r4, r0
	ldr r0, [r3, #0x0]
	mvn r12, #0x0
	mov lr, r1
	mov r3, r2
	cmp r0, r12
	beq _020C94C4
	cmp r3, #0x1c
	bls _020C94C4
	ldr r2, _020C94E4 ; =0x05000200
	mov r1, r4
	add r2, lr, r2
	bl MI_DmaCopy16
	ldmia sp!, {r4,lr}
	bx lr
_020C94C4:
	ldr r1, _020C94E4 ; =0x05000200
	mov r0, r4
	mov r2, r3
	add r1, lr, r1
	bl MIi_CpuCopy16
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C94E0: .word 0x02106814
_020C94E4: .word 0x05000200

	arm_func_start GXS_LoadBGPltt
GXS_LoadBGPltt: ; 0x020C94E8
	stmdb sp!, {r4,lr}
	ldr r3, _020C9548 ; =0x02106814
	mov r4, r0
	ldr r0, [r3, #0x0]
	mvn r12, #0x0
	mov lr, r1
	mov r3, r2
	cmp r0, r12
	beq _020C952C
	cmp r3, #0x1c
	bls _020C952C
	ldr r2, _020C954C ; =0x05000400
	mov r1, r4
	add r2, lr, r2
	bl MI_DmaCopy16
	ldmia sp!, {r4,lr}
	bx lr
_020C952C:
	ldr r1, _020C954C ; =0x05000400
	mov r0, r4
	mov r2, r3
	add r1, lr, r1
	bl MIi_CpuCopy16
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C9548: .word 0x02106814
_020C954C: .word 0x05000400

	arm_func_start GX_LoadBGPltt
GX_LoadBGPltt: ; 0x020C9550
	stmdb sp!, {r4,lr}
	ldr r3, _020C95A8 ; =0x02106814
	mov r4, r0
	ldr r0, [r3, #0x0]
	mvn r12, #0x0
	mov lr, r1
	mov r3, r2
	cmp r0, r12
	beq _020C9590
	cmp r3, #0x1c
	bls _020C9590
	mov r1, r4
	add r2, lr, #0x5000000
	bl MI_DmaCopy16
	ldmia sp!, {r4,lr}
	bx lr
_020C9590:
	mov r0, r4
	mov r2, r3
	add r1, lr, #0x5000000
	bl MIi_CpuCopy16
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C95A8: .word 0x02106814

	arm_func_start GX_EndLoadClearImage
GX_EndLoadClearImage: ; 0x020C95AC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C95F8 ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C95CC
	bl MI_WaitDma
_020C95CC:
	ldr r0, _020C95FC ; =0x021D33FC
	ldr r0, [r0, #0x0]
	bl GX_SetBankForClearImage
	ldr r1, _020C95FC ; =0x021D33FC
	mov r2, #0x0
	ldr r0, _020C9600 ; =0x021D340C
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C95F8: .word 0x02106814
_020C95FC: .word 0x021D33FC
_020C9600: .word 0x021D340C

	arm_func_start GX_LoadClearImageDepth
GX_LoadClearImageDepth: ; 0x020C9604
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldr r3, _020C9670 ; =0x021D340C
	ldr r2, _020C9674 ; =0x02106814
	ldr r12, [r3, #0x0]
	ldr lr, [r2, #0x0]
	mvn r2, #0x0
	mov r4, r0
	mov r3, r1
	cmp lr, r2
	add r2, r12, #0x20000
	beq _020C9658
	mov r12, #0x0
	str r12, [sp, #0x0]
	mov r0, lr
	mov r1, r4
	str r12, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020C9658:
	mov r1, r2
	mov r2, r3
	bl MIi_CpuCopy32
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C9670: .word 0x021D340C
_020C9674: .word 0x02106814

	arm_func_start GX_LoadClearImageColor
GX_LoadClearImageColor: ; 0x020C9678
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldr r2, _020C96E0 ; =0x02106814
	ldr ip, _020C96E4 ; =0x021D340C
	ldr lr, [r2, #0x0]
	mvn r2, #0x0
	mov r4, r0
	mov r3, r1
	cmp lr, r2
	ldr r2, [r12, #0x0]
	beq _020C96C8
	mov r12, #0x0
	str r12, [sp, #0x0]
	mov r0, lr
	mov r1, r4
	str r12, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020C96C8:
	mov r1, r2
	mov r2, r3
	bl MIi_CpuCopy32
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C96E0: .word 0x02106814
_020C96E4: .word 0x021D340C

	arm_func_start GX_BeginLoadClearImage
GX_BeginLoadClearImage: ; 0x020C96E8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl GX_ResetBankForClearImage
	ldr r1, _020C979C ; =0x021D33FC
	cmp r0, #0xc
	str r0, [r1, #0x0]
	addls pc, pc, r0, lsl #0x2
	b _020C9790
_020C9708:
	b _020C9790
_020C970C:
	b _020C976C
_020C9710:
	b _020C973C
_020C9714:
	b _020C973C
_020C9718:
	b _020C9784
_020C971C:
	b _020C9790
_020C9720:
	b _020C9790
_020C9724:
	b _020C9790
_020C9728:
	b _020C9754
_020C972C:
	b _020C9790
_020C9730:
	b _020C9790
_020C9734:
	b _020C9790
_020C9738:
	b _020C9754
_020C973C:
	ldr r0, _020C97A0 ; =0x021D340C
	mov r1, #0x6800000
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020C9754:
	ldr r1, _020C97A4 ; =0x06840000
	ldr r0, _020C97A0 ; =0x021D340C
	add sp, sp, #0x4
	str r1, [r0, #0x0]
	ldmia sp!, {lr}
	bx lr
_020C976C:
	ldr r1, _020C97A8 ; =0x067E0000
	ldr r0, _020C97A0 ; =0x021D340C
	add sp, sp, #0x4
	str r1, [r0, #0x0]
	ldmia sp!, {lr}
	bx lr
_020C9784:
	ldr r1, _020C97AC ; =0x06820000
	ldr r0, _020C97A0 ; =0x021D340C
	str r1, [r0, #0x0]
_020C9790:
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C979C: .word 0x021D33FC
_020C97A0: .word 0x021D340C
_020C97A4: .word 0x06840000
_020C97A8: .word 0x067E0000
_020C97AC: .word 0x06820000

	arm_func_start GX_EndLoadTexPltt
GX_EndLoadTexPltt: ; 0x020C97B0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C97FC ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C97D0
	bl MI_WaitDma
_020C97D0:
	ldr r0, _020C9800 ; =0x021D3408
	ldr r0, [r0, #0x0]
	bl GX_SetBankForTexPltt
	ldr r1, _020C9800 ; =0x021D3408
	mov r2, #0x0
	ldr r0, _020C9804 ; =0x021D3404
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C97FC: .word 0x02106814
_020C9800: .word 0x021D3408
_020C9804: .word 0x021D3404

	arm_func_start GX_LoadTexPltt
GX_LoadTexPltt: ; 0x020C9808
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	ldr ip, _020C9874 ; =0x021D3404
	ldr r3, _020C9878 ; =0x02106814
	ldr r4, [r12, #0x0]
	ldr lr, [r3, #0x0]
	mvn r12, #0x0
	mov r5, r0
	mov r3, r2
	cmp lr, r12
	add r4, r4, r1
	beq _020C9860
	mov r12, #0x0
	str r12, [sp, #0x0]
	mov r0, lr
	mov r1, r5
	mov r2, r4
	str r12, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
_020C9860:
	mov r1, r4
	bl MIi_CpuCopy32
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020C9874: .word 0x021D3404
_020C9878: .word 0x02106814

	arm_func_start GX_BeginLoadTexPltt
GX_BeginLoadTexPltt: ; 0x020C987C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl GX_ResetBankForTexPltt
	mov r3, r0, asr #0x4
	ldr r2, _020C98B8 ; =0x021D3408
	ldr r1, _020C98BC ; =0x02103B3C
	mov r3, r3, lsl #0x1
	ldrh r3, [r1, r3]
	ldr r1, _020C98C0 ; =0x021D3404
	str r0, [r2, #0x0]
	mov r0, r3, lsl #0xc
	str r0, [r1, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C98B8: .word 0x021D3408
_020C98BC: .word 0x02103B3C
_020C98C0: .word 0x021D3404

	arm_func_start GX_EndLoadTex
GX_EndLoadTex: ; 0x020C98C4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C9920 ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C98E4
	bl MI_WaitDma
_020C98E4:
	ldr r0, _020C9924 ; =0x021D3410
	ldr r0, [r0, #0x0]
	bl GX_SetBankForTex
	ldr r3, _020C9928 ; =0x021D3418
	mov r12, #0x0
	ldr r2, _020C992C ; =0x021D3414
	ldr r1, _020C9930 ; =0x021D3400
	ldr r0, _020C9924 ; =0x021D3410
	str r12, [r3, #0x0]
	str r12, [r2, #0x0]
	str r12, [r1, #0x0]
	str r12, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C9920: .word 0x02106814
_020C9924: .word 0x021D3410
_020C9928: .word 0x021D3418
_020C992C: .word 0x021D3414
_020C9930: .word 0x021D3400

	arm_func_start GX_LoadTex
GX_LoadTex: ; 0x020C9934
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	ldr r3, _020C9A88 ; =0x021D3414
	mov r7, r0
	ldr r5, [r3, #0x0]
	mov r6, r2
	cmp r5, #0x0
	ldreq r0, _020C9A8C ; =0x021D3400
	ldreq r0, [r0, #0x0]
	addeq r2, r0, r1
	beq _020C9A34
	ldr r0, _020C9A90 ; =0x021D3418
	add r2, r1, r6
	ldr r4, [r0, #0x0]
	cmp r2, r4
	ldrlo r0, _020C9A8C ; =0x021D3400
	ldrcc r0, [r0, #0x0]
	addcc r2, r0, r1
	blo _020C9A34
	cmp r1, r4
	addcs r0, r5, r1
	subcs r2, r0, r4
	bhs _020C9A34
	ldr r2, _020C9A8C ; =0x021D3400
	ldr r0, _020C9A94 ; =0x02106814
	ldr r3, [r2, #0x0]
	ldr r0, [r0, #0x0]
	mvn r2, #0x0
	cmp r0, r2
	sub r4, r4, r1
	add r2, r3, r1
	beq _020C99CC
	cmp r4, #0x30
	bls _020C99CC
	mov r1, r7
	mov r3, r4
	bl MI_DmaCopy32
	b _020C99DC
_020C99CC:
	mov r1, r2
	mov r0, r7
	mov r2, r4
	bl MIi_CpuCopy32
_020C99DC:
	ldr r0, _020C9A94 ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C9A18
	mov r12, #0x0
	str r12, [sp, #0x0]
	mov r2, r5
	add r1, r7, r4
	sub r3, r6, r4
	str r12, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
_020C9A18:
	mov r1, r5
	add r0, r7, r4
	sub r2, r6, r4
	bl MIi_CpuCopy32
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
_020C9A34:
	ldr r0, _020C9A94 ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C9A6C
	mov r4, #0x0
	str r4, [sp, #0x0]
	mov r1, r7
	mov r3, r6
	str r4, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
_020C9A6C:
	mov r1, r2
	mov r0, r7
	mov r2, r6
	bl MIi_CpuCopy32
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020C9A88: .word 0x021D3414
_020C9A8C: .word 0x021D3400
_020C9A90: .word 0x021D3418
_020C9A94: .word 0x02106814

	arm_func_start GX_BeginLoadTex
GX_BeginLoadTex: ; 0x020C9A98
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl GX_ResetBankForTex
	mov r1, #0x6
	mul r12, r0, r1
	ldr r3, _020C9AFC ; =0x02103B4C
	ldr r2, _020C9B00 ; =0x02103B4E
	ldr r1, _020C9B04 ; =0x02103B50
	ldrh r5, [r3, r12]
	ldrh r4, [r2, r12]
	ldrh lr, [r1, r12]
	ldr ip, _020C9B08 ; =0x021D3410
	ldr r3, _020C9B0C ; =0x021D3400
	mov r5, r5, lsl #0xc
	ldr r2, _020C9B10 ; =0x021D3414
	mov r4, r4, lsl #0xc
	ldr r1, _020C9B14 ; =0x021D3418
	mov lr, lr, lsl #0xc
	str r0, [r12, #0x0]
	str r5, [r3, #0x0]
	str r4, [r2, #0x0]
	str lr, [r1, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020C9AFC: .word 0x02103B4C
_020C9B00: .word 0x02103B4E
_020C9B04: .word 0x02103B50
_020C9B08: .word 0x021D3410
_020C9B0C: .word 0x021D3400
_020C9B10: .word 0x021D3414
_020C9B14: .word 0x021D3418

	arm_func_start G3_EndMakeDL
G3_EndMakeDL: ; 0x020C9B18
	ldr r3, [r0, #0x0]
	ldr r2, [r0, #0x8]
	cmp r2, r3
	moveq r0, #0x0
	bxeq lr
	and r1, r3, #0x3
	cmp r1, #0x3
	addls pc, pc, r1, lsl #0x2
	b _020C9B8C
_020C9B3C:
	b _020C9B4C
_020C9B40:
	b _020C9B54
_020C9B44:
	b _020C9B64
_020C9B48:
	b _020C9B78
_020C9B4C:
	sub r0, r3, r2
	bx lr
_020C9B54:
	add r1, r3, #0x1
	str r1, [r0, #0x0]
	mov r1, #0x0
	strb r1, [r3, #0x0]
_020C9B64:
	ldr r3, [r0, #0x0]
	mov r1, #0x0
	add r2, r3, #0x1
	str r2, [r0, #0x0]
	strb r1, [r3, #0x0]
_020C9B78:
	ldr r3, [r0, #0x0]
	mov r1, #0x0
	add r2, r3, #0x1
	str r2, [r0, #0x0]
	strb r1, [r3, #0x0]
_020C9B8C:
	ldr r1, [r0, #0x10]
	cmp r1, #0x0
	beq _020C9BB0
	ldr r3, [r0, #0x4]
	mov r1, #0x0
	add r2, r3, #0x4
	str r2, [r0, #0x4]
	str r1, [r3, #0x0]
	str r1, [r0, #0x10]
_020C9BB0:
	ldr r1, [r0, #0x4]
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	ldr r0, [r0, #0x8]
	sub r0, r1, r0
	bx lr

	arm_func_start G3_BeginMakeDL
G3_BeginMakeDL: ; 0x020C9BC8
	str r2, [r0, #0xc]
	str r1, [r0, #0x8]
	str r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	mov r1, #0x0
	str r1, [r0, #0x10]
	bx lr

	arm_func_start GX_SendFifo48B
GX_SendFifo48B: ; 0x020C9BE8
	ldmia r0!, {r2-r3,r12}
	stmia r1, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1, {r2-r3,r12}
	bx lr
