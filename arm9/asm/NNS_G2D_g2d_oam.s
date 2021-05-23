	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	; NNSi_objSizeHTbl
	.global UNK_020FF894
UNK_020FF894: ; 0x020FF894
	.byte 0x08, 0x00, 0x10, 0x00, 0x20, 0x00, 0x40, 0x00, 0x08, 0x00, 0x08, 0x00, 0x10, 0x00, 0x20, 0x00
	.byte 0x10, 0x00, 0x20, 0x00, 0x20, 0x00, 0x40, 0x00

	; NNSi_objSizeWTbl
	.global UNK_020FF8AC
UNK_020FF8AC: ; 0x020FF8AC
	.byte 0x08, 0x00, 0x10, 0x00, 0x20, 0x00, 0x40, 0x00, 0x10, 0x00, 0x20, 0x00, 0x20, 0x00, 0x40, 0x00
	.byte 0x08, 0x00, 0x08, 0x00, 0x10, 0x00, 0x20, 0x00

	; static const in function
	.section .data

	; funcTbl$8497
	.global UNK_0210655C
UNK_0210655C: ; 0x0210655C
	.word FUN_020B1088
	.word FUN_020B1098
	.word 0
	.word 0
	.word 0

	.section .bss

	; numRegisterdInstance_
	.global UNK_021CCD9C
UNK_021CCD9C: ; 0x021CCD9C
	.space 0x4

	; oamCache_
	.global UNK_021CCDA0
UNK_021CCDA0: ; 0x021CCDA0
	.space 0x100

	; oamCache_ + 0x100
	.global UNK_021CCEA0
UNK_021CCEA0: ; 0x021CCEA0
	.space 0x400

	; oamCache_ + 0x500
	.global UNK_021CD2A0
UNK_021CD2A0: ; 0x021CD2A0
	.space 0x40

	; oamCache_ + 0x540
	.global UNK_021CD2E0
UNK_021CD2E0: ; 0x021CD2E0
	.space 0x100

	; oamCache_ + 0x640
	.global UNK_021CD3E0
UNK_021CD3E0: ; 0x021CD3E0
	.space 0x400

	; oamCache_ + 0xA40
	.global UNK_021CD7E0
UNK_021CD7E0: ; 0x021CD7E0
	.space 0x40

	; oamCache_ + 0xA80
	.global UNK_021CD820
UNK_021CD820: ; 0x021CD820
	.space 0x100

	; oamCache_ + 0xB80
	.global UNK_021CD920
UNK_021CD920: ; 0x021CD920
	.space 0x400

	; oamCache_ + 0xF80
	.global UNK_021CDD20
UNK_021CDD20: ; 0x021CDD20
	.space 0x40

	.section .text

	; _end
	arm_func_start FUN_020B0830
FUN_020B0830: ; 0x020B0830
	ldrh r3, [r0, #0x6]
	ldrh r2, [r0, #0x8]
	mov r12, #0x0
	add r1, r3, #0x1
	cmp r2, r1
	bgt _020B0854
	ldrh r0, [r0, #0x4]
	cmp r0, r3
	movls r12, #0x1
_020B0854:
	cmp r12, #0x0
	subne r0, r3, r2
	addne r0, r0, #0x1
	movne r0, r0, lsl #0x10
	movne r0, r0, lsr #0x10
	moveq r0, #0x0
	bx lr
	arm_func_end FUN_020B0830

	; _end
	arm_func_start FUN_020B0870
FUN_020B0870: ; 0x020B0870
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020B09B4
	mov r0, r4
	bl FUN_020B0888
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020B0870

	; NNS_G2dResetOamManagerBuffer
	arm_func_start FUN_020B0888
FUN_020B0888: ; 0x020B0888
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	ldr r0, [r5, #0x14]
	cmp r0, #0x0
	beq _020B0944
	ldrh r2, [r5, #0x6]
	ldrh r1, [r5, #0x8]
	mov r3, #0x0
	add r0, r2, #0x1
	cmp r1, r0
	bgt _020B08C0
	ldrh r0, [r5, #0x4]
	cmp r0, r2
	movls r3, #0x1
_020B08C0:
	cmp r3, #0x0
	moveq r4, #0x0
	beq _020B08E0
	ldrh r0, [r5, #0x4]
	sub r0, r2, r0
	add r0, r0, #0x1
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0xd
_020B08E0:
	ldr r2, [r5, #0x0]
	ldr r1, _020B09AC ; =UNK_021CCDA0
	mov r0, #0x540
	mla r1, r2, r0, r1
	ldrh r0, [r5, #0x4]
	add r2, r1, #0x100
	mov r1, r4
	add r6, r2, r0, lsl #0x3
	mov r0, r6
	bl DC_InvalidateRange
	ldr r0, _020B09B0 ; =GXi_DmaId
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020B0930
	mov r1, r6
	mov r3, r4
	mov r2, #0xc0
	bl MI_DmaFill32
	b _020B0998
_020B0930:
	mov r1, r6
	mov r2, r4
	mov r0, #0xc0
	bl MIi_CpuClear32
	b _020B0998
_020B0944:
	ldr r2, [r5, #0x0]
	ldr r1, _020B09AC ; =UNK_021CCDA0
	mov r0, #0x540
	mla r1, r2, r0, r1
	ldrh r2, [r5, #0x4]
	ldrh r0, [r5, #0x6]
	add r1, r1, #0x100
	add r3, r1, r2, lsl #0x3
	sub r0, r0, r2
	add r0, r0, #0x1
	mov r0, r0, lsl #0x10
	movs r2, r0, lsr #0x10
	mov r0, #0x0
	beq _020B0998
	mov r1, #0xc0
_020B0980:
	add r0, r0, #0x1
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	cmp r0, r2
	strh r1, [r3], #0x8
	blo _020B0980
_020B0998:
	ldrh r0, [r5, #0x4]
	strh r0, [r5, #0x8]
	ldrh r0, [r5, #0xa]
	strh r0, [r5, #0xe]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B09AC: .word UNK_021CCDA0
_020B09B0: .word GXi_DmaId
	arm_func_end FUN_020B0888

	; NNS_G2dApplyOamManagerToHW
	arm_func_start FUN_020B09B4
FUN_020B09B4: ; 0x020B09B4
	stmdb sp!, {r4-r10,lr}
	mov r7, r0
	ldr r0, [r7, #0x14]
	cmp r0, #0x0
	beq _020B0A48
	ldr r5, [r7, #0x0]
	ldr r1, _020B0BA8 ; =UNK_021CCDA0
	mov r0, #0x540
	mla r1, r5, r0, r1
	ldrh r2, [r7, #0x4]
	ldrh r0, [r7, #0x6]
	add r1, r1, #0x100
	add r4, r1, r2, lsl #0x3
	sub r0, r0, r2
	add r0, r0, #0x1
	mov r0, r0, lsl #0x13
	mov r6, r0, lsr #0x10
	mov r2, r2, lsl #0x13
	mov r0, r4
	mov r1, r6
	mov r7, r2, lsr #0x10
	bl DC_FlushRange
	cmp r5, #0x0
	beq _020B0A20
	cmp r5, #0x1
	beq _020B0A34
	ldmia sp!, {r4-r10,pc}
_020B0A20:
	mov r0, r4
	mov r1, r7
	mov r2, r6
	bl GX_LoadOAM
	ldmia sp!, {r4-r10,pc}
_020B0A34:
	mov r0, r4
	mov r1, r7
	mov r2, r6
	bl GXS_LoadOAM
	ldmia sp!, {r4-r10,pc}
_020B0A48:
	ldr r0, [r7, #0x0]
	ldr r2, _020B0BA8 ; =UNK_021CCDA0
	mov r1, #0x540
	mla r2, r0, r1, r2
	ldrh r5, [r7, #0x4]
	ldrh r1, [r7, #0x6]
	ldr r3, _020B0BAC ; =UNK_0210655C
	add r4, r2, #0x100
	sub r1, r1, r5
	add r1, r1, #0x1
	mov r1, r1, lsl #0x10
	mov r2, r5, lsl #0x13
	add r6, r4, r5, lsl #0x3
	movs r5, r1, lsr #0x10
	mov r4, r2, lsr #0x10
	ldr r9, [r3, r0, lsl #0x2]
	mov r10, #0x0
	beq _020B0AC8
	mov r8, #0x6
_020B0A94:
	mov r0, r6
	mov r1, r4
	mov r2, r8
	blx r9
	add r0, r10, #0x1
	add r2, r4, #0x8
	mov r1, r0, lsl #0x10
	mov r0, r2, lsl #0x10
	mov r10, r1, lsr #0x10
	cmp r10, r5
	mov r4, r0, lsr #0x10
	add r6, r6, #0x8
	blo _020B0A94
_020B0AC8:
	ldrh r2, [r7, #0xc]
	ldrh r1, [r7, #0xe]
	mov r3, #0x0
	add r0, r2, #0x1
	cmp r1, r0
	bgt _020B0AEC
	ldrh r0, [r7, #0xa]
	cmp r0, r2
	movls r3, #0x1
_020B0AEC:
	cmp r3, #0x0
	ldmeqia sp!, {r4-r10,pc}
	ldr r0, [r7, #0x0]
	ldr r2, _020B0BA8 ; =UNK_021CCDA0
	mov r1, #0x540
	mla r2, r0, r1, r2
	ldrh r5, [r7, #0xa]
	add r4, r2, #0x100
	ldrh r1, [r7, #0xc]
	mov r2, r5, lsl #0x15
	ldr r3, _020B0BAC ; =UNK_0210655C
	sub r1, r1, r5
	add r1, r1, #0x1
	mov r1, r1, lsl #0x10
	add r9, r4, r5, lsl #0x5
	ldr r5, [r3, r0, lsl #0x2]
	movs r8, r1, lsr #0x10
	mov r7, r2, lsr #0x10
	mov r6, #0x0
	ldmeqia sp!, {r4-r10,pc}
	mov r4, #0x2
_020B0B40:
	mov r2, r4
	add r0, r9, #0x6
	add r1, r7, #0x6
	blx r5
	mov r2, r4
	add r0, r9, #0xe
	add r1, r7, #0xe
	blx r5
	mov r2, r4
	add r0, r9, #0x16
	add r1, r7, #0x16
	blx r5
	add r0, r9, #0x1e
	add r1, r7, #0x1e
	mov r2, r4
	blx r5
	add r0, r7, #0x20
	mov r0, r0, lsl #0x10
	mov r7, r0, lsr #0x10
	add r9, r9, #0x20
	add r0, r6, #0x1
	mov r0, r0, lsl #0x10
	mov r6, r0, lsr #0x10
	cmp r6, r8
	blo _020B0B40
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020B0BA8: .word UNK_021CCDA0
_020B0BAC: .word UNK_0210655C
	arm_func_end FUN_020B09B4

	; NNS_G2dEntryOamManagerAffine
	arm_func_start FUN_020B0BB0
FUN_020B0BB0: ; 0x020B0BB0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r12, [r0, #0xc]
	ldrh r3, [r0, #0xe]
	mov lr, #0x0
	add r2, r12, #0x1
	cmp r3, r2
	bgt _020B0BDC
	ldrh r2, [r0, #0xa]
	cmp r2, r12
	movls lr, #0x1
_020B0BDC:
	cmp lr, #0x0
	subne r2, r12, r3
	addne r2, r2, #0x1
	movne r2, r2, lsl #0x10
	movne r2, r2, lsr #0x10
	moveq r2, #0x0
	cmp r2, #0x1
	movcs r2, #0x1
	movcc r2, #0x0
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldreq r0, _020B0C74 ; =0x0000FFFE
	ldmeqia sp!, {pc}
	ldr lr, [r0, #0x0]
	ldr r3, _020B0C78 ; =UNK_021CCDA0
	mov r2, #0x540
	mla r12, lr, r2, r3
	ldr r3, [r1, #0x0]
	ldrh r2, [r0, #0xe]
	add r12, r12, #0x100
	mov r3, r3, asr #0x4
	add r12, r12, r2, lsl #0x5
	strh r3, [r12, #0x6]
	ldr r3, [r1, #0x4]
	mov r3, r3, asr #0x4
	strh r3, [r12, #0xe]
	ldr r3, [r1, #0x8]
	mov r3, r3, asr #0x4
	strh r3, [r12, #0x16]
	ldr r1, [r1, #0xc]
	mov r1, r1, asr #0x4
	strh r1, [r12, #0x1e]
	ldrh r1, [r0, #0xe]
	add r1, r1, #0x1
	strh r1, [r0, #0xe]
	mov r0, r2
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B0C74: .word 0x0000FFFE
_020B0C78: .word UNK_021CCDA0
	arm_func_end FUN_020B0BB0

	; NNS_G2dEntryOamManagerOamWithAffineIdx
	arm_func_start FUN_020B0C7C
FUN_020B0C7C: ; 0x020B0C7C
	stmdb sp!, {r4,lr}
	ldrh r12, [r0, #0x6]
	ldrh r4, [r0, #0x8]
	mov lr, #0x0
	add r3, r12, #0x1
	cmp r4, r3
	bgt _020B0CA4
	ldrh r3, [r0, #0x4]
	cmp r3, r12
	movls lr, #0x1
_020B0CA4:
	cmp lr, #0x0
	subne r3, r12, r4
	addne r3, r3, #0x1
	movne r3, r3, lsl #0x10
	movne r3, r3, lsr #0x10
	moveq r3, #0x0
	cmp r3, #0x1
	movcs r3, #0x1
	movcc r3, #0x0
	cmp r3, #0x0
	beq _020B0D48
	ldr r4, [r0, #0x0]
	ldr ip, _020B0D50 ; =UNK_021CCDA0
	mov r3, #0x540
	mla r12, r4, r3, r12
	ldrh r3, [r0, #0x8]
	add r4, r12, #0x100
	ldrh r12, [r1, #0x0]
	mov lr, r3, lsl #0x3
	add r3, r4, r3, lsl #0x3
	strh r12, [r4, lr]
	ldrh lr, [r1, #0x2]
	ldr ip, _020B0D54 ; =0x0000FFFE
	strh lr, [r3, #0x2]
	ldrh r1, [r1, #0x4]
	cmp r2, r12
	strh r1, [r3, #0x4]
	beq _020B0D34
	ldr r1, [r3, #0x0]
	mov r12, r1, lsl #0x16
	mov r12, r12, lsr #0x1e
	ands r12, r12, #0x1
	bicne r12, r1, #0x3e000000
	andne r1, r2, #0x1f
	orrne r1, r12, r1, lsl #0x19
	strne r1, [r3, #0x0]
_020B0D34:
	ldrh r1, [r0, #0x8]
	add r1, r1, #0x1
	strh r1, [r0, #0x8]
	mov r0, #0x1
	ldmia sp!, {r4,pc}
_020B0D48:
	mov r0, #0x0
	ldmia sp!, {r4,pc}
	.balign 4
_020B0D50: .word UNK_021CCDA0
_020B0D54: .word 0x0000FFFE
	arm_func_end FUN_020B0C7C

	; NNS_G2dEntryOamManagerOam
	arm_func_start FUN_020B0D58
FUN_020B0D58: ; 0x020B0D58
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldrh lr, [r0, #0x6]
	ldrh r12, [r0, #0x8]
	mov r4, #0x0
	add r3, lr, #0x1
	cmp r12, r3
	bgt _020B0D84
	ldrh r3, [r0, #0x4]
	cmp r3, lr
	movls r4, #0x1
_020B0D84:
	cmp r4, #0x0
	subne r3, lr, r12
	addne r3, r3, #0x1
	movne r3, r3, lsl #0x10
	movne r3, r3, lsr #0x10
	moveq r3, #0x0
	cmp r3, r2
	movcs r3, #0x1
	movcc r3, #0x0
	cmp r3, #0x0
	beq _020B0E24
	ldr lr, [r0, #0x0]
	ldr ip, _020B0E30 ; =UNK_021CCDA0
	mov r3, #0x540
	mla r12, lr, r3, r12
	ldrh r3, [r0, #0x8]
	add r12, r12, #0x100
	cmp r2, #0x0
	add r4, r12, r3, lsl #0x3
	mov r5, #0x0
	ble _020B0E18
	add r3, r0, #0x8
_020B0DDC:
	ldrh lr, [r1, #0x0]
	mov r0, r5, lsl #0x3
	add r12, r4, r5, lsl #0x3
	strh lr, [r4, r0]
	ldrh r0, [r1, #0x2]
	add r5, r5, #0x1
	cmp r5, r2
	strh r0, [r12, #0x2]
	ldrh r0, [r1, #0x4]
	add r1, r1, #0x8
	strh r0, [r12, #0x4]
	ldrh r0, [r3, #0x0]
	add r0, r0, #0x1
	strh r0, [r3, #0x0]
	blt _020B0DDC
_020B0E18:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r5,pc}
_020B0E24:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B0E30: .word UNK_021CCDA0
	arm_func_end FUN_020B0D58

	; NNS_G2dGetNewOamManagerInstance
	arm_func_start FUN_020B0E34
FUN_020B0E34: ; 0x020B0E34
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r5, [sp, #0x1c]
	ldr r6, _020B0FB4 ; =UNK_021CCDA0
	mov r4, #0x540
	mla r4, r5, r4, r6
	mov lr, r1
	sub r1, r2, #0x1
	add r1, lr, r1
	mov r1, r1, lsl #0x10
	mov r12, r1, lsr #0x10
	add r7, r4, lr, lsl #0x1
	add r2, r4, r12, lsl #0x1
	mov r6, r0
	mov r5, r3
	cmp r7, r2
	mov r3, lr, lsl #0x1
	bhi _020B0E9C
	ldr r0, _020B0FB8 ; =0x0000FFFF
_020B0E80:
	ldrh r1, [r7, #0x0]
	cmp r1, r0
	movne r0, #0x0
	bne _020B0EA0
	add r7, r7, #0x2
	cmp r7, r2
	bls _020B0E80
_020B0E9C:
	mov r0, #0x1
_020B0EA0:
	cmp r0, #0x0
	beq _020B0EE0
	ldr r0, _020B0FBC ; =UNK_021CCD9C
	sub r2, r12, lr
	ldrh r7, [r0, #0x0]
	add r1, r4, r3
	mov r2, r2, lsl #0x1
	add r3, r7, #0x1
	strh r3, [r0, #0x0]
	strh r7, [r6, #0x10]
	strh lr, [r6, #0x4]
	strh r12, [r6, #0x6]
	strh lr, [r6, #0x8]
	ldrh r0, [r6, #0x10]
	bl MIi_CpuClear16
	b _020B0EEC
_020B0EE0:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020B0EEC:
	ldrh r0, [sp, #0x18]
	add r4, r4, #0x500
	cmp r0, #0x0
	bne _020B0F18
	mov r0, #0x20
	strh r0, [r6, #0xa]
	mov r0, #0x0
	strh r0, [r6, #0xc]
	ldrh r0, [r6, #0xa]
	strh r0, [r6, #0xe]
	b _020B0F98
_020B0F18:
	sub r0, r0, #0x1
	add r0, r5, r0
	mov r0, r0, lsl #0x10
	mov r12, r0, lsr #0x10
	add r7, r4, r5, lsl #0x1
	add r2, r4, r12, lsl #0x1
	cmp r7, r2
	mov r3, r5, lsl #0x1
	bhi _020B0F5C
	ldr r0, _020B0FB8 ; =0x0000FFFF
_020B0F40:
	ldrh r1, [r7, #0x0]
	cmp r1, r0
	movne r0, #0x0
	bne _020B0F60
	add r7, r7, #0x2
	cmp r7, r2
	bls _020B0F40
_020B0F5C:
	mov r0, #0x1
_020B0F60:
	cmp r0, #0x0
	beq _020B0F8C
	strh r5, [r6, #0xa]
	strh r12, [r6, #0xc]
	strh r5, [r6, #0xe]
	ldrh r0, [r6, #0x10]
	sub r2, r12, r5
	add r1, r4, r3
	mov r2, r2, lsl #0x1
	bl MIi_CpuClear16
	b _020B0F98
_020B0F8C:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020B0F98:
	mov r1, #0x0
	ldr r0, [sp, #0x1c]
	str r1, [r6, #0x14]
	str r0, [r6, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B0FB4: .word UNK_021CCDA0
_020B0FB8: .word 0x0000FFFF
_020B0FBC: .word UNK_021CCD9C
	arm_func_end FUN_020B0E34

	; NNS_G2dInitOamManagerModule
	arm_func_start FUN_020B0FC0
FUN_020B0FC0: ; 0x020B0FC0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020B1060 ; =UNK_021CCEA0
	mov r0, #0xc0
	mov r2, #0x400
	bl MIi_CpuClear16
	ldr r1, _020B1064 ; =UNK_021CD3E0
	mov r0, #0xc0
	mov r2, #0x400
	bl MIi_CpuClear16
	ldr r1, _020B1068 ; =UNK_021CD920
	mov r0, #0xc0
	mov r2, #0x400
	bl MIi_CpuClear16
	ldr r0, _020B106C ; =0x0000FFFF
	ldr r1, _020B1070 ; =UNK_021CCDA0
	mov r2, #0x100
	bl MIi_CpuClear16
	ldr r0, _020B106C ; =0x0000FFFF
	ldr r1, _020B1074 ; =UNK_021CD2E0
	mov r2, #0x100
	bl MIi_CpuClear16
	ldr r0, _020B106C ; =0x0000FFFF
	ldr r1, _020B1078 ; =UNK_021CD820
	mov r2, #0x100
	bl MIi_CpuClear16
	ldr r0, _020B106C ; =0x0000FFFF
	ldr r1, _020B107C ; =UNK_021CD2A0
	mov r2, #0x40
	bl MIi_CpuClear16
	ldr r0, _020B106C ; =0x0000FFFF
	ldr r1, _020B1080 ; =UNK_021CD7E0
	mov r2, #0x40
	bl MIi_CpuClear16
	ldr r0, _020B106C ; =0x0000FFFF
	ldr r1, _020B1084 ; =UNK_021CDD20
	mov r2, #0x40
	bl MIi_CpuClear16
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B1060: .word UNK_021CCEA0
_020B1064: .word UNK_021CD3E0
_020B1068: .word UNK_021CD920
_020B106C: .word 0x0000FFFF
_020B1070: .word UNK_021CCDA0
_020B1074: .word UNK_021CD2E0
_020B1078: .word UNK_021CD820
_020B107C: .word UNK_021CD2A0
_020B1080: .word UNK_021CD7E0
_020B1084: .word UNK_021CDD20
	arm_func_end FUN_020B0FC0

	; CpuLoadOAMMain_
	arm_func_start FUN_020B1088
FUN_020B1088: ; 0x020B1088
	ldr ip, _020B1094 ; =MIi_CpuCopy16
	add r1, r1, #0x7000000
	bx r12
	.balign 4
_020B1094: .word MIi_CpuCopy16
	arm_func_end FUN_020B1088

	; CpuLoadOAMSub_
	arm_func_start FUN_020B1098
FUN_020B1098: ; 0x020B1098
	ldr r3, _020B10A8 ; =0x07000400
	ldr ip, _020B10AC ; =MIi_CpuCopy16
	add r1, r1, r3
	bx r12
	.balign 4
_020B10A8: .word 0x07000400
_020B10AC: .word MIi_CpuCopy16
	arm_func_end FUN_020B1098

