	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNSi_G2dFontGetTextRect
NNSi_G2dFontGetTextRect: ; 0x020B5ABC
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0xc
	add r5, sp, #0x0
	mov r4, #0x0
	str r4, [r5, #0x0]
	str r4, [r5, #0x4]
	mov r8, r2
	ldr r2, [sp, #0x28]
	mov r5, r0
	mov r9, r1
	mov r4, r3
	cmp r2, #0x0
	mov r7, #0x1
	beq _020B5B24
	add r6, sp, #0x28
_020B5AF8:
	mov r0, r9
	mov r1, r8
	mov r3, r6
	bl NNSi_G2dFontGetStringWidth
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x28]
	cmp r0, r1
	strgt r0, [sp, #0x0]
	add r7, r7, #0x1
	cmp r2, #0x0
	bne _020B5AF8
_020B5B24:
	ldr r0, [r9, #0x0]
	sub r2, r7, #0x1
	ldrsb r1, [r0, #0x1]
	ldr r0, [sp, #0x0]
	add r1, r4, r1
	mul r1, r2, r1
	sub r1, r1, r4
	str r1, [sp, #0x4]
	str r0, [r5, #0x0]
	str r1, [r5, #0x4]
	add sp, sp, #0xc
	ldmia sp!, {r4-r9,pc}
	arm_func_end NNSi_G2dFontGetTextRect

	arm_func_start NNSi_G2dFontGetTextHeight
NNSi_G2dFontGetTextHeight: ; 0x020B5B54
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	str r2, [sp, #0x0]
	add r3, sp, #0x4
	mov r2, #0x0
	str r2, [r3, #0x0]
	mov r8, r0
	str r2, [r3, #0x4]
	ldr r7, [r8, #0x4]
	add r0, sp, #0x0
	mov r5, r1
	mov r4, #0x1
	blx r7
	cmp r0, #0x0
	beq _020B5BAC
	add r6, sp, #0x0
_020B5B94:
	cmp r0, #0xa
	mov r0, r6
	addeq r4, r4, #0x1
	blx r7
	cmp r0, #0x0
	bne _020B5B94
_020B5BAC:
	ldr r0, [r8, #0x0]
	ldrsb r0, [r0, #0x1]
	add r0, r5, r0
	mul r0, r4, r0
	sub r0, r0, r5
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}
	arm_func_end NNSi_G2dFontGetTextHeight

	arm_func_start NNSi_G2dFontGetStringWidth
NNSi_G2dFontGetStringWidth: ; 0x020B5BC8
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x8
	mov r8, r0
	str r2, [sp, #0x0]
	ldr r4, [r8, #0x4]
	add r0, sp, #0x0
	mov r7, r1
	mov r6, r3
	mov r5, #0x0
	blx r4
	movs r1, r0
	beq _020B5C58
	ldr sb, _020B5C84 ; =0x0000FFFF
	add r10, sp, #0x0
_020B5C00:
	cmp r1, #0xa
	beq _020B5C58
	mov r0, r8
	bl NNS_G2dFontFindGlyphIndex
	mov r1, r0
	cmp r1, r9
	ldreq r0, [r8, #0x0]
	ldreqh r1, [r0, #0x2]
	mov r0, r8
	bl NNS_G2dFontGetCharWidthsFromIndex
	ldrh r1, [r8, #0x8]
	cmp r1, #0x0
	ldrnesb r1, [r0, #0x0]
	ldrneb r0, [r0, #0x1]
	addne r0, r1, r0
	ldreqsb r0, [r0, #0x2]
	add r1, r7, r0
	mov r0, r10
	add r5, r5, r1
	blx r4
	movs r1, r0
	bne _020B5C00
_020B5C58:
	cmp r6, #0x0
	beq _020B5C70
	cmp r1, #0xa
	ldreq r0, [sp, #0x0]
	movne r0, #0x0
	str r0, [r6, #0x0]
_020B5C70:
	cmp r5, #0x0
	subgt r5, r5, r7
	mov r0, r5
	add sp, sp, #0x8
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020B5C84: .word 0x0000FFFF
	arm_func_end NNSi_G2dFontGetStringWidth

	arm_func_start NNS_G2dFontGetCharWidthsFromIndex
NNS_G2dFontGetCharWidthsFromIndex: ; 0x020B5C88
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [r0, #0x0]
	ldr lr, [r3, #0xc]
	cmp lr, #0x0
	beq _020B5CD8
_020B5CA0:
	ldrh r12, [lr, #0x0]
	cmp r12, r1
	bhi _020B5CCC
	ldrh r2, [lr, #0x2]
	cmp r1, r2
	ldrlsh r2, [r0, #0xa]
	addls r3, lr, #0x8
	subls r0, r1, r12
	mlals r0, r2, r0, r3
	addls sp, sp, #0x4
	ldmlsia sp!, {pc}
_020B5CCC:
	ldr lr, [lr, #0x4]
	cmp lr, #0x0
	bne _020B5CA0
_020B5CD8:
	add r0, r3, #0x4
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNS_G2dFontGetCharWidthsFromIndex

	arm_func_start NNS_G2dFontFindGlyphIndex
NNS_G2dFontFindGlyphIndex: ; 0x020B5CE4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	beq _020B5D2C
_020B5CFC:
	ldrh r2, [r0, #0x0]
	cmp r2, r1
	bhi _020B5D20
	ldrh r2, [r0, #0x2]
	cmp r1, r2
	bhi _020B5D20
	bl GetGlyphIndex
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020B5D20:
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	bne _020B5CFC
_020B5D2C:
	ldr r0, _020B5D38 ; =0x0000FFFF
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B5D38: .word 0x0000FFFF
	arm_func_end NNS_G2dFontFindGlyphIndex

	arm_func_start NNS_G2dFontInitUTF16
NNS_G2dFontInitUTF16: ; 0x020B5D3C
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, r1
	mov r1, r4
	bl NNSi_G2dGetUnpackedFont
	sub r0, r0, #0x1
	strh r0, [r4, #0x8]
	ldrh r0, [r4, #0x8]
	cmp r0, #0x0
	movne r1, #0x2
	moveq r1, #0x3
	ldr r0, _020B5D78 ; =NNSi_G2dSplitCharUTF16
	strh r1, [r4, #0xa]
	str r0, [r4, #0x4]
	ldmia sp!, {r4,pc}
	.balign 4
_020B5D78: .word NNSi_G2dSplitCharUTF16
	arm_func_end NNS_G2dFontInitUTF16

	arm_func_start GetGlyphIndex
GetGlyphIndex: ; 0x020B5D7C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r3, [r0, #0x4]
	ldr r2, _020B5E4C ; =0x0000FFFF
	cmp r3, #0x0
	beq _020B5DA8
	cmp r3, #0x1
	beq _020B5DC4
	cmp r3, #0x2
	beq _020B5DD8
	b _020B5E40
_020B5DA8:
	ldrh r2, [r0, #0x0]
	ldrh r3, [r0, #0xc]
	sub r0, r1, r2
	add r0, r3, r0
	mov r0, r0, lsl #0x10
	mov r2, r0, lsr #0x10
	b _020B5E40
_020B5DC4:
	ldrh r2, [r0, #0x0]
	sub r1, r1, r2
	add r0, r0, r1, lsl #0x1
	ldrh r2, [r0, #0xc]
	b _020B5E40
_020B5DD8:
	ldrh r3, [r0, #0xc]
	add r0, r0, #0xc
	add r0, r0, #0x2
	sub r3, r3, #0x1
	add lr, r0, r3, lsl #0x2
	cmp r0, lr
	bhi _020B5E40
_020B5DF4:
	sub r12, lr, r0
	mov r3, r12, asr #0x1
	add r3, r12, r3, lsr #0x1e
	mov r3, r3, asr #0x2
	add r3, r3, r3, lsr #0x1f
	mov r12, r3, asr #0x1
	mov r3, r12, lsl #0x2
	ldrh r3, [r0, r3]
	add r12, r0, r12, lsl #0x2
	cmp r3, r1
	addcc r0, r12, #0x4
	blo _020B5E38
	cmp r1, r3
	subcc lr, r12, #0x4
	blo _020B5E38
	ldrh r2, [r12, #0x2]
	b _020B5E40
_020B5E38:
	cmp r0, lr
	bls _020B5DF4
_020B5E40:
	mov r0, r2
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B5E4C: .word 0x0000FFFF
	arm_func_end GetGlyphIndex
