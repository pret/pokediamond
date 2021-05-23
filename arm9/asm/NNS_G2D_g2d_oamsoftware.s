	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	; pltFmtTbl$8430
	.global UNK_020FF8D0
UNK_020FF8D0: ; 0x020FF8D0
	.byte 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00

	; static const in function
	; texSize_$8337
	.global UNK_020FF8D8
UNK_020FF8D8: ; 0x020FF8D8
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00

	; gxTexSizeSTbl
	.global UNK_020FF8F8
UNK_020FF8F8: ; 0x020FF8F8
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	; gxTexSizeTTbl
	.global UNK_020FF928
UNK_020FF928: ; 0x020FF928
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00

	.section .data

	; zOffsetStep_
	.global UNK_02106590
UNK_02106590: ; 0x02106590
	.byte 0x00, 0xF0, 0xFF, 0xFF

	.section .bss

	; bAutoZOffsetAdd_
	.global UNK_021CED08
UNK_021CED08: ; 0x021CED08
	.space 0x4

	; s_pUVFlipCorrectFunc
	.global UNK_021CED0C
UNK_021CED0C: ; 0x021CED0C
	.space 0x4

	; zOffset_
	.global UNK_021CED10
UNK_021CED10: ; 0x021CED10
	.space 0x4

	.section .text

	; NNS_G2dDrawOneOam3DDirectWithPosFast
	arm_func_start FUN_020B46B4
FUN_020B46B4: ; 0x020B46B4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x1c
	add r12, sp, #0x4
	mov r5, r1
	mov r4, r2
	mov r7, r3
	mov r6, r0
	ldr r1, [sp, #0x30]
	ldr r2, [sp, #0x34]
	ldr r3, [sp, #0x38]
	mov r0, r7
	str r12, [sp, #0x0]
	bl FUN_020B498C
	ldr r2, [r7, #0x0]
	and r1, r2, #0x300
	cmp r1, #0x100
	beq _020B4708
	cmp r1, #0x300
	beq _020B4708
	and r0, r2, #0x30000000
	orr r1, r1, r0
_020B4708:
	cmp r1, #0x300
	bne _020B478C
	ldr r0, _020B4914 ; =0xC000C000
	ldr r1, _020B4918 ; =UNK_021CED08
	and r0, r2, r0
	and r2, r0, #0xc0000000
	mov r12, r2, lsr #0x1e
	and r0, r0, #0xc000
	mov lr, r0, asr #0xe
	ldr r3, _020B491C ; =UNK_020FF8AC
	ldr r0, [r1, #0x0]
	ldr r2, _020B4920 ; =UNK_020FF894
	cmp r0, #0x0
	ldrne r0, _020B4924 ; =UNK_021CED10
	mov r12, r12, lsl #0x1
	add r1, r2, lr, lsl #0x3
	add r3, r3, lr, lsl #0x3
	ldrh r2, [r12, r3]
	ldrh r1, [r12, r1]
	ldrne r0, [r0, #0x0]
	mov r2, r2, asr #0x1
	addne r3, r0, r4, lsl #0xc
	mov r1, r1, asr #0x1
	add r0, r5, r1
	add r2, r6, r2
	ldr r1, _020B4928 ; =0x04000470
	mov r2, r2, lsl #0xc
	str r2, [r1, #0x0]
	mov r0, r0, lsl #0xc
	moveq r3, r4, lsl #0xc
	str r0, [r1, #0x0]
	str r3, [r1, #0x0]
	b _020B47C0
_020B478C:
	ldr r0, _020B4918 ; =UNK_021CED08
	ldr r1, _020B4928 ; =0x04000470
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldrne r0, _020B4924 ; =UNK_021CED10
	ldrne r0, [r0, #0x0]
	addne r2, r0, r4, lsl #0xc
	mov r0, r6, lsl #0xc
	str r0, [r1, #0x0]
	mov r0, r5, lsl #0xc
	moveq r2, r4, lsl #0xc
	str r0, [r1, #0x0]
	str r2, [r1, #0x0]
_020B47C0:
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	ldr r2, _020B492C ; =0x0400046C
	mov r0, r0, lsl #0xc
	str r0, [r2, #0x0]
	mov r0, r1, lsl #0xc
	str r0, [r2, #0x0]
	mov r1, #0x1000
	str r1, [r2, #0x0]
	ldr r0, _020B4930 ; =0x04000500
	mov r1, #0x1
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x10]
	mov r0, r0, lsl #0x8
	mov r1, r1, lsl #0x8
	mov r0, r0, asr #0x10
	mov r1, r1, asr #0x10
	mov r0, r0, lsl #0x10
	mov r1, r1, lsl #0x10
	mov r2, r0, lsr #0x10
	mov r0, r1, lsr #0x10
	orr r2, r2, r0, lsl #0x10
	ldr r1, _020B4934 ; =0x04000488
	ldr r0, _020B4938 ; =0x04000490
	str r2, [r1, #0x0]
	mov r2, #0x10000
	str r2, [r0, #0x0]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	mov r2, r2, lsl #0x8
	mov r3, r3, lsl #0x8
	mov r2, r2, asr #0x10
	mov r3, r3, asr #0x10
	mov r2, r2, lsl #0x10
	mov r3, r3, lsl #0x10
	mov r4, r2, lsr #0x10
	mov r2, r3, lsr #0x10
	orr r3, r4, r2, lsl #0x10
	ldr r2, _020B493C ; =0x00010040
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x8]
	mov r2, r2, lsl #0x8
	mov r3, r3, lsl #0x8
	mov r2, r2, asr #0x10
	mov r3, r3, asr #0x10
	mov r2, r2, lsl #0x10
	mov r3, r3, lsl #0x10
	mov r4, r2, lsr #0x10
	mov r2, r3, lsr #0x10
	orr r2, r4, r2, lsl #0x10
	str r2, [r1, #0x0]
	mov r2, #0x40
	str r2, [r0, #0x0]
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x8]
	mov r2, r2, lsl #0x8
	mov r3, r3, lsl #0x8
	mov r2, r2, asr #0x10
	mov r3, r3, asr #0x10
	mov r2, r2, lsl #0x10
	mov r3, r3, lsl #0x10
	mov r4, r2, lsr #0x10
	mov r2, r3, lsr #0x10
	orr r2, r4, r2, lsl #0x10
	str r2, [r1, #0x0]
	mov r2, #0x0
	str r2, [r0, #0x0]
	ldr r1, _020B4940 ; =0x04000504
	ldr r0, _020B4918 ; =UNK_021CED08
	str r2, [r1, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x1c
	ldmeqia sp!, {r4-r7,pc}
	ldr r1, _020B4924 ; =UNK_021CED10
	ldr r0, _020B4944 ; =UNK_02106590
	ldr r2, [r1, #0x0]
	ldr r0, [r0, #0x0]
	add r0, r2, r0
	str r0, [r1, #0x0]
	add sp, sp, #0x1c
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B4914: .word 0xC000C000
_020B4918: .word UNK_021CED08
_020B491C: .word UNK_020FF8AC
_020B4920: .word UNK_020FF894
_020B4924: .word UNK_021CED10
_020B4928: .word 0x04000470
_020B492C: .word 0x0400046C
_020B4930: .word 0x04000500
_020B4934: .word 0x04000488
_020B4938: .word 0x04000490
_020B493C: .word 0x00010040
_020B4940: .word 0x04000504
_020B4944: .word UNK_02106590
	arm_func_end FUN_020B46B4

	; NNSi_G2dGetOamSoftEmuAutoZOffsetStep
	arm_func_start FUN_020B4948
FUN_020B4948: ; 0x020B4948
	ldr r0, _020B4954 ; =UNK_02106590
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020B4954: .word UNK_02106590
	arm_func_end FUN_020B4948

	; NNSi_G2dSetOamSoftEmuAutoZOffsetStep
	arm_func_start FUN_020B4958
FUN_020B4958: ; 0x020B4958
	ldr r1, _020B4964 ; =UNK_02106590
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020B4964: .word UNK_02106590
	arm_func_end FUN_020B4958

	; NNSi_G2dResetOamSoftEmuAutoZOffset
	arm_func_start FUN_020B4968
FUN_020B4968: ; 0x020B4968
	ldr r0, _020B4978 ; =UNK_021CED10
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020B4978: .word UNK_021CED10
	arm_func_end FUN_020B4968

	; NNSi_G2dSetOamSoftEmuAutoZOffsetFlag
	arm_func_start FUN_020B497C
FUN_020B497C: ; 0x020B497C
	ldr r1, _020B4988 ; =UNK_021CED08
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020B4988: .word UNK_021CED08
	arm_func_end FUN_020B497C

	; CalcSpriteParams_
	arm_func_start FUN_020B498C
FUN_020B498C: ; 0x020B498C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0xc
	mov r6, r0
	ldr r4, [r6, #0x0]
	ldr r0, _020B4BCC ; =0xC000C000
	ldr r5, [r6, #0x4]
	and r4, r4, r0
	and r0, r4, #0xc0000000
	and r4, r4, #0xc000
	mov lr, r0, lsr #0x1e
	ldr r0, _020B4BD0 ; =UNK_020FF8AC
	mov r12, r4, asr #0xe
	ldr r8, _020B4BD4 ; =UNK_020FF894
	mov r4, lr, lsl #0x1
	add r0, r0, r12, lsl #0x3
	ldrh r9, [r4, r0]
	ldr r0, [sp, #0x28]
	mov r5, r5, lsl #0x16
	mov r5, r5, lsr #0x16
	mov r7, r5, lsl #0x10
	str r9, [r0, #0x10]
	add r5, r8, r12, lsl #0x3
	ldrh r8, [r4, r5]
	mov r5, r1
	mov r4, r3
	str r8, [r0, #0x14]
	ldr r1, [r5, #0x14]
	mov r7, r7, lsr #0x10
	cmp r1, #0x0
	bne _020B4A74
	ldr r1, [r5, #0x8]
	mov r2, r2, lsr #0x3
	orr r1, r2, r1, lsl #0x1a
	ldr r2, [r5, #0x0]
	orr r1, r1, #0x40000000
	ldr r3, [r5, #0x4]
	orr r1, r1, r2, lsl #0x14
	orr r2, r1, r3, lsl #0x17
	ldr r8, [r5, #0x10]
	ldr r1, _020B4BD8 ; =0x040004A8
	orr r2, r2, r8, lsl #0x1d
	str r2, [r1, #0x0]
	ldr r1, [r5, #0x8]
	ldr r2, [r5, #0x0]
	cmp r1, #0x4
	moveq r1, r7, lsl #0xf
	moveq r7, r1, lsr #0x10
	ldr r1, _020B4BDC ; =UNK_020FF8D8
	ldr r1, [r1, r2, lsl #0x2]
	sub r1, r1, #0x1
	and r1, r7, r1
	mov r1, r1, lsl #0xf
	str r1, [r0, #0x0]
	ldr r1, [r5, #0x0]
	mov r1, r7, asr r1
	mov r1, r1, lsl #0xf
	str r1, [r0, #0x4]
	b _020B4AE0
_020B4A74:
	and r1, r1, #0x700000
	mov r1, r1, asr #0x14
	mov r12, r12, lsl #0x10
	add r1, r1, #0x5
	ldr r3, [r5, #0x8]
	mov lr, lr, lsl #0x10
	ldr sb, _020B4BE0 ; =UNK_020FF8F8
	mov r12, r12, lsr #0x10
	ldr r8, _020B4BE4 ; =UNK_020FF928
	add r1, r2, r7, lsl r1
	mov r2, r3, lsl #0x1a
	orr r3, r2, r1, lsr #0x3
	mov r7, lr, lsr #0x10
	add r2, r9, r12, lsl #0x4
	add r1, r8, r12, lsl #0x4
	ldr r2, [r2, r7, lsl #0x2]
	orr r3, r3, #0x40000000
	ldr r1, [r1, r7, lsl #0x2]
	orr r2, r3, r2, lsl #0x14
	ldr r3, [r5, #0x10]
	orr r2, r2, r1, lsl #0x17
	ldr r1, _020B4BD8 ; =0x040004A8
	orr r2, r2, r3, lsl #0x1d
	str r2, [r1, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
_020B4AE0:
	ldr r2, [r0, #0x0]
	ldr r1, [r0, #0x10]
	add r1, r2, r1, lsl #0xc
	str r1, [r0, #0x8]
	ldr r2, [r0, #0x4]
	ldr r1, [r0, #0x14]
	add r1, r2, r1, lsl #0xc
	str r1, [r0, #0xc]
	ldr r1, [r6, #0x0]
	mov r2, r1, lsl #0x2
	mov r1, r1, lsl #0x3
	movs r3, r1, lsr #0x1f
	mov r12, r2, lsr #0x1f
	ldrne r2, [r0, #0x0]
	ldrne r1, [r0, #0x8]
	strne r1, [r0, #0x0]
	strne r2, [r0, #0x8]
	cmp r12, #0x0
	ldrne r2, [r0, #0x4]
	ldrne r1, [r0, #0xc]
	strne r1, [r0, #0x4]
	ldr r1, _020B4BE8 ; =UNK_021CED0C
	strne r2, [r0, #0xc]
	ldr r7, [r1, #0x0]
	cmp r7, #0x0
	beq _020B4B60
	str r3, [sp, #0x0]
	add r1, r0, #0x4
	add r2, r0, #0x8
	add r3, r0, #0xc
	str r12, [sp, #0x4]
	blx r7
_020B4B60:
	ldr r0, [r6, #0x4]
	ldr r1, [r6, #0x0]
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x1c
	mov r3, r1, lsl #0x12
	ldr r1, [r5, #0xc]
	mov r0, r0, lsl #0x10
	ldr r2, _020B4BEC ; =UNK_020FF8D0
	mov r3, r3, lsr #0x1f
	cmp r1, #0x0
	mov r0, r0, lsr #0x10
	ldr r1, [r2, r3, lsl #0x2]
	movne r0, r0, lsl #0x9
	bne _020B4BA4
	cmp r1, #0x4
	moveq r0, #0x0
	movne r0, r0, lsl #0x5
_020B4BA4:
	cmp r1, #0x2
	moveq r2, #0x1
	movne r2, #0x0
	add r1, r4, r0
	rsb r0, r2, #0x4
	mov r1, r1, lsr r0
	ldr r0, _020B4BF0 ; =0x040004AC
	str r1, [r0, #0x0]
	add sp, sp, #0xc
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020B4BCC: .word 0xC000C000
_020B4BD0: .word UNK_020FF8AC
_020B4BD4: .word UNK_020FF894
_020B4BD8: .word 0x040004A8
_020B4BDC: .word UNK_020FF8D8
_020B4BE0: .word UNK_020FF8F8
_020B4BE4: .word UNK_020FF928
_020B4BE8: .word UNK_021CED0C
_020B4BEC: .word UNK_020FF8D0
_020B4BF0: .word 0x040004AC
	arm_func_end FUN_020B498C

