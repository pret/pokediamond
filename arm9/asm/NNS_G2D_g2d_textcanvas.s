	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNSi_G2dTextCanvasDrawTextRect
NNSi_G2dTextCanvasDrawTextRect: ; 0x020B7168
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	ldr r12, [sp, #0x28]
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	ands r0, r12, #0x100
	beq _020B71AC
	ldr r0, [r7, #0x4]
	ldr r1, [r7, #0xc]
	ldr r2, [sp, #0x2c]
	bl NNSi_G2dFontGetTextHeight
	ldr r1, [sp, #0x20]
	sub r0, r1, r0
	add r5, r5, r0
	b _020B71E4
_020B71AC:
	ands r0, r12, #0x80
	beq _020B71E4
	ldr r0, [r7, #0x4]
	ldr r1, [r7, #0xc]
	ldr r2, [sp, #0x2c]
	bl NNSi_G2dFontGetTextHeight
	ldr r2, [sp, #0x20]
	add r1, r0, #0x1
	add r0, r2, #0x1
	add r0, r0, r0, lsr #0x1f
	mov r2, r0, asr #0x1
	add r0, r1, r1, lsr #0x1f
	sub r0, r2, r0, asr #0x1
	add r5, r5, r0
_020B71E4:
	ldr r1, [sp, #0x24]
	ldr r0, [sp, #0x28]
	str r1, [sp, #0x0]
	ldr r12, [sp, #0x2c]
	str r0, [sp, #0x4]
	mov r0, r7
	mov r1, r6
	mov r2, r5
	mov r3, r4
	str r12, [sp, #0x8]
	bl NNSi_G2dTextCanvasDrawTextAlign
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,pc}
	arm_func_end NNSi_G2dTextCanvasDrawTextRect

	arm_func_start NNSi_G2dTextCanvasDrawText
NNSi_G2dTextCanvasDrawText: ; 0x020B7218
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x18
	ldr r4, [sp, #0x34]
	mov r8, r0
	str r4, [sp, #0x0]
	mov r7, r1
	mov r6, r2
	mov r5, r3
	ldr r4, [sp, #0x30]
	ldr r1, [r8, #0x4]
	ldr r2, [r8, #0x8]
	ldr r3, [r8, #0xc]
	add r0, sp, #0xc
	bl NNSi_G2dFontGetTextRect
	ands r0, r4, #0x10
	ldrne r0, [sp, #0xc]
	addne r0, r0, #0x1
	addne r0, r0, r0, lsr #0x1f
	subne r7, r7, r0, asr #0x1
	bne _020B7274
	ands r0, r4, #0x20
	ldrne r0, [sp, #0xc]
	subne r7, r7, r0
_020B7274:
	ands r0, r4, #0x2
	ldrne r0, [sp, #0x10]
	addne r0, r0, #0x1
	addne r0, r0, r0, lsr #0x1f
	subne r6, r6, r0, asr #0x1
	bne _020B7298
	ands r0, r4, #0x4
	ldrne r0, [sp, #0x10]
	subne r6, r6, r0
_020B7298:
	str r5, [sp, #0x0]
	ldr r0, [sp, #0x34]
	str r4, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r3, [sp, #0xc]
	mov r0, r8
	mov r1, r7
	mov r2, r6
	bl NNSi_G2dTextCanvasDrawTextAlign
	add sp, sp, #0x18
	ldmia sp!, {r4-r8,pc}
	arm_func_end NNSi_G2dTextCanvasDrawText

	arm_func_start NNSi_G2dTextCanvasDrawTextAlign
NNSi_G2dTextCanvasDrawTextAlign: ; 0x020B72C4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r10, r0
	ldr r4, [r10, #0x4]
	ldr r0, [sp, #0x40]
	ldr r4, [r4, #0x0]
	ldr r5, [r10, #0xc]
	ldrsb r4, [r4, #0x1]
	cmp r0, #0x0
	mov r9, r1
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x38]
	mov r8, r2
	str r0, [sp, #0x38]
	mov r7, r3
	add r6, r5, r4
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4-r11,pc}
	add r0, r7, #0x1
	ldr r1, [sp, #0x3c]
	add r0, r0, r0, lsr #0x1f
	mov r0, r0, asr #0x1
	and r5, r1, #0x800
	and r11, r1, #0x400
	str r0, [sp, #0x8]
	mov r4, #0x0
_020B732C:
	mov r1, r9
	cmp r5, #0x0
	beq _020B7358
	ldr r0, [r10, #0x4]
	ldr r1, [r10, #0x8]
	ldr r2, [sp, #0xc]
	mov r3, r4
	bl NNSi_G2dFontGetStringWidth
	sub r0, r7, r0
	add r1, r9, r0
	b _020B7388
_020B7358:
	cmp r11, #0x0
	beq _020B7388
	ldr r0, [r10, #0x4]
	ldr r1, [r10, #0x8]
	ldr r2, [sp, #0xc]
	mov r3, r4
	bl NNSi_G2dFontGetStringWidth
	add r0, r0, #0x1
	add r1, r0, r0, lsr #0x1f
	ldr r0, [sp, #0x8]
	sub r0, r0, r1, asr #0x1
	add r1, r9, r0
_020B7388:
	ldr r2, [sp, #0xc]
	add r3, sp, #0xc
	str r2, [sp, #0x0]
	str r3, [sp, #0x4]
	ldr r3, [sp, #0x38]
	mov r0, r10
	mov r2, r8
	bl NNSi_G2dTextCanvasDrawString
	ldr r0, [sp, #0xc]
	add r8, r8, r6
	cmp r0, #0x0
	bne _020B732C
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,pc}
	arm_func_end NNSi_G2dTextCanvasDrawTextAlign

	arm_func_start NNSi_G2dTextCanvasDrawString
NNSi_G2dTextCanvasDrawString: ; 0x020B73C0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r10, r0
	ldr r6, [r10, #0x8]
	ldr r5, [r10, #0x4]
	ldr r4, [sp, #0x30]
	add r0, sp, #0x8
	str r4, [sp, #0x8]
	ldr r4, [r5, #0x4]
	mov r9, r1
	mov r8, r2
	mov r7, r3
	blx r4
	cmp r0, #0x0
	beq _020B743C
	add r11, sp, #0x8
_020B7400:
	cmp r0, #0xa
	beq _020B743C
	str r7, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [r10, #0x0]
	mov r1, r5
	mov r2, r9
	mov r3, r8
	bl NNS_G2dCharCanvasDrawChar
	add r1, r9, r0
	mov r0, r11
	add r9, r1, r6
	blx r4
	cmp r0, #0x0
	bne _020B7400
_020B743C:
	ldr r1, [sp, #0x34]
	cmp r1, #0x0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r11,pc}
	cmp r0, #0xa
	ldreq r1, [sp, #0x8]
	ldr r0, [sp, #0x34]
	movne r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
	arm_func_end NNSi_G2dTextCanvasDrawString
