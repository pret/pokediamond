    .include "asm/macros.inc"
    .include "global.inc"

    .text

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
