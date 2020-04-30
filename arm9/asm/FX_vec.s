	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start VEC_MultAdd
VEC_MultAdd: ; 0x020C50D4
	stmdb sp!, {r4,lr}
	ldr r4, [r1, #0x0]
	ldr lr, [r2, #0x0]
	smull r12, r4, r0, r4
	mov r12, r12, lsr #0xc
	orr r12, r12, r4, lsl #0x14
	add r4, lr, r12
	str r4, [r3, #0x0]
	ldr r12, [r1, #0x4]
	ldr r4, [r2, #0x4]
	smull lr, r12, r0, r12
	mov lr, lr, lsr #0xc
	orr lr, lr, r12, lsl #0x14
	add r4, r4, lr
	str r4, [r3, #0x4]
	ldr r1, [r1, #0x8]
	ldr r12, [r2, #0x8]
	smull r2, r1, r0, r1
	mov r0, r2, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	add r0, r12, r0
	str r0, [r3, #0x8]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start VEC_Fx16Normalize
VEC_Fx16Normalize: ; 0x020C5134
	stmdb sp!, {r4-r8,lr}
	ldrsh r4, [r0, #0x0]
	ldrsh r3, [r0, #0x2]
	ldrsh r2, [r0, #0x4]
	mul r8, r4, r4
	mul r7, r3, r3
	mul r6, r2, r2
	ldr r2, _020C526C ; =0x04000280
	mov r3, #0x2
	ldr r4, _020C5270 ; =0x04000290
	strh r3, [r2, #0x0]
	mov r2, #0x0
	str r2, [r4, #0x0]
	mov r5, #0x1000000
	mov r2, r8, asr #0x1f
	adds r3, r8, r7
	adc r2, r2, r7, asr #0x1f
	adds r7, r3, r6
	adc r6, r2, r6, asr #0x1f
	mov r3, r6, lsl #0x2
	ldr r2, _020C5274 ; =0x04000298
	str r5, [r4, #0x4]
	str r7, [r2, #0x0]
	ldr r5, _020C5278 ; =0x040002B0
	str r6, [r2, #0x4]
	mov r4, #0x1
	ldr r2, _020C527C ; =0x040002B8
	strh r4, [r5, #0x0]
	mov r4, r7, lsl #0x2
	str r4, [r2, #0x0]
	orr r3, r3, r7, lsr #0x1e
	str r3, [r2, #0x4]
_020C51B4:
	ldrh r2, [r5, #0x0]
	ands r2, r2, #0x8000
	bne _020C51B4
	ldr r2, _020C5280 ; =0x040002B4
	ldr r12, [r2, #0x0]
	ldr r3, _020C526C ; =0x04000280
_020C51CC:
	ldrh r2, [r3, #0x0]
	ands r2, r2, #0x8000
	bne _020C51CC
	ldr r7, _020C5284 ; =0x040002A0
	ldrsh r5, [r0, #0x0]
	ldr r6, [r7, #0x0]
	mov r4, r12, asr #0x1f
	umull r3, r2, r6, r12
	mla r2, r6, r4, r2
	ldr r8, [r7, #0x4]
	mov r4, r5, asr #0x1f
	umull r7, r6, r3, r5
	mov lr, #0x0
	mla r2, r8, r12, r2
	mla r6, r3, r4, r6
	mla r6, r2, r5, r6
	adds r4, r7, lr
	adc r4, r6, #0x1000
	mov r4, r4, asr #0xd
	strh r4, [r1, #0x0]
	ldrsh r5, [r0, #0x2]
	umull r6, r12, r3, r5
	mov r4, r5, asr #0x1f
	mla r12, r3, r4, r12
	mla r12, r2, r5, r12
	adds r4, r6, lr
	adc r4, r12, #0x1000
	mov r4, r4, asr #0xd
	strh r4, [r1, #0x2]
	ldrsh r12, [r0, #0x4]
	umull r5, r4, r3, r12
	mov r0, r12, asr #0x1f
	adds r5, r5, lr
	mla r4, r3, r0, r4
	mla r4, r2, r12, r4
	adc r0, r4, #0x1000
	mov r0, r0, asr #0xd
	strh r0, [r1, #0x4]
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020C526C: .word 0x04000280
_020C5270: .word 0x04000290
_020C5274: .word 0x04000298
_020C5278: .word 0x040002B0
_020C527C: .word 0x040002B8
_020C5280: .word 0x040002B4
_020C5284: .word 0x040002A0

	arm_func_start VEC_Normalize
VEC_Normalize:
	stmdb sp!, {r4-r8,lr}
	ldr r3, [r0, #0x4]
	ldr r4, [r0, #0x0]
	smull r2, r7, r3, r3
	smlal r2, r7, r4, r4
	ldr r4, [r0, #0x8]
	ldr r3, _020C53AC ; =0x04000280
	smlal r2, r7, r4, r4
	mov r6, #0x2
	mov r4, r7, lsl #0x2
	ldr r5, _020C53B0 ; =0x04000290
	strh r6, [r3, #0x0]
	mov r3, #0x0
	str r3, [r5, #0x0]
	mov r6, #0x1000000
	ldr r3, _020C53B4 ; =0x04000298
	str r6, [r5, #0x4]
	str r2, [r3, #0x0]
	ldr r6, _020C53B8 ; =0x040002B0
	str r7, [r3, #0x4]
	mov r5, #0x1
	ldr r3, _020C53BC ; =0x040002B8
	strh r5, [r6, #0x0]
	mov r5, r2, lsl #0x2
	str r5, [r3, #0x0]
	orr r4, r4, r2, lsr #0x1e
	str r4, [r3, #0x4]
_020C52F4:
	ldrh r2, [r6, #0x0]
	ands r2, r2, #0x8000
	bne _020C52F4
	ldr r2, _020C53C0 ; =0x040002B4
	ldr r12, [r2, #0x0]
	ldr r3, _020C53AC ; =0x04000280
_020C530C:
	ldrh r2, [r3, #0x0]
	ands r2, r2, #0x8000
	bne _020C530C
	ldr r7, _020C53C4 ; =0x040002A0
	ldr r5, [r0, #0x0]
	ldr r6, [r7, #0x0]
	mov r4, r12, asr #0x1f
	umull r3, r2, r6, r12
	mla r2, r6, r4, r2
	ldr r8, [r7, #0x4]
	mov r4, r5, asr #0x1f
	umull r7, r6, r3, r5
	mov lr, #0x0
	mla r2, r8, r12, r2
	mla r6, r3, r4, r6
	mla r6, r2, r5, r6
	adds r4, r7, lr
	adc r4, r6, #0x1000
	mov r4, r4, asr #0xd
	str r4, [r1, #0x0]
	ldr r5, [r0, #0x4]
	umull r6, r12, r3, r5
	mov r4, r5, asr #0x1f
	mla r12, r3, r4, r12
	mla r12, r2, r5, r12
	adds r4, r6, lr
	adc r4, r12, #0x1000
	mov r4, r4, asr #0xd
	str r4, [r1, #0x4]
	ldr r12, [r0, #0x8]
	umull r5, r4, r3, r12
	mov r0, r12, asr #0x1f
	adds r5, r5, lr
	mla r4, r3, r0, r4
	mla r4, r2, r12, r4
	adc r0, r4, #0x1000
	mov r0, r0, asr #0xd
	str r0, [r1, #0x8]
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020C53AC: .word 0x04000280
_020C53B0: .word 0x04000290
_020C53B4: .word 0x04000298
_020C53B8: .word 0x040002B0
_020C53BC: .word 0x040002B8
_020C53C0: .word 0x040002B4
_020C53C4: .word 0x040002A0

	arm_func_start VEC_Mag
VEC_Mag:
	ldr r2, [r0, #0x4]
	ldr r3, [r0, #0x0]
	smull r12, r1, r2, r2
	smlal r12, r1, r3, r3
	ldr r0, [r0, #0x8]
	ldr r3, _020C5424 ; =0x040002B0
	smlal r12, r1, r0, r0
	mov r2, #0x1
	mov r1, r1, lsl #0x2
	ldr r0, _020C5428 ; =0x040002B8
	strh r2, [r3, #0x0]
	mov r2, r12, lsl #0x2
	str r2, [r0, #0x0]
	orr r1, r1, r12, lsr #0x1e
	str r1, [r0, #0x4]
_020C5404:
	ldrh r0, [r3, #0x0]
	ands r0, r0, #0x8000
	bne _020C5404
	ldr r0, _020C542C ; =0x040002B4
	ldr r0, [r0, #0x0]
	add r0, r0, #0x1
	mov r0, r0, asr #0x1
	bx lr
	.balign 4
_020C5424: .word 0x040002B0
_020C5428: .word 0x040002B8
_020C542C: .word 0x040002B4

	arm_func_start VEC_Fx16CrossProduct
VEC_Fx16CrossProduct: ; 0x020C5430
	stmdb sp!, {r4-r6,lr}
	ldrsh r4, [r1, #0x4]
	ldrsh r12, [r0, #0x2]
	ldrsh lr, [r0, #0x0]
	ldrsh r3, [r1, #0x2]
	ldrsh r6, [r0, #0x4]
	ldrsh r1, [r1, #0x0]
	mul r5, r12, r4
	mul r0, r6, r3
	sub r0, r5, r0
	add r0, r0, #0x800
	mov r0, r0, asr #0xc
	mul r5, r6, r1
	mul r4, lr, r4
	sub r4, r5, r4
	add r4, r4, #0x800
	mul r3, lr, r3
	mul r1, r12, r1
	sub r1, r3, r1
	add r1, r1, #0x800
	strh r0, [r2, #0x0]
	mov r0, r4, asr #0xc
	strh r0, [r2, #0x2]
	mov r0, r1, asr #0xc
	strh r0, [r2, #0x4]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start VEC_CrossProduct
VEC_CrossProduct:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r12, [r1, #0x8]
	ldr r9, [r0, #0x4]
	ldr r3, [r0, #0x0]
	ldr r11, [r1, #0x4]
	ldr r0, [r0, #0x8]
	ldr r10, [r1, #0x0]
	smull r4, r7, r9, r12
	smull r1, r6, r0, r11
	subs r8, r4, r1
	smull r5, r4, r0, r10
	smull lr, r12, r3, r12
	smull r1, r0, r3, r11
	smull r10, r3, r9, r10
	sbc r6, r7, r6
	mov r9, #0x800
	adds r7, r8, r9
	adc r6, r6, #0x0
	subs r8, r5, lr
	sbc r5, r4, r12
	adds r8, r8, r9
	mov r4, r7, lsr #0xc
	adc r5, r5, #0x0
	subs r1, r1, r10
	orr r4, r4, r6, lsl #0x14
	mov r6, r8, lsr #0xc
	sbc r0, r0, r3
	adds r1, r1, r9
	str r4, [r2, #0x0]
	orr r6, r6, r5, lsl #0x14
	adc r0, r0, #0x0
	mov r1, r1, lsr #0xc
	str r6, [r2, #0x4]
	orr r1, r1, r0, lsl #0x14
	str r1, [r2, #0x8]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start VEC_Fx16DotProduct
VEC_Fx16DotProduct: ; 0x020C5538
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldrsh lr, [r0, #0x2]
	ldrsh r12, [r1, #0x2]
	ldrsh r3, [r0, #0x4]
	ldrsh r2, [r1, #0x4]
	ldrsh r5, [r0, #0x0]
	ldrsh r4, [r1, #0x0]
	smulbb r1, lr, r12
	smulbb r0, r3, r2
	smlabb r1, r5, r4, r1
	add r0, r0, #0x800
	adds r2, r1, r0
	mov r1, r1, asr #0x1f
	adc r1, r1, r0, asr #0x1f
	mov r0, r2, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start VEC_DotProduct
VEC_DotProduct:
	stmdb sp!, {r4,lr}
	ldr r3, [r0, #0x4]
	ldr r2, [r1, #0x4]
	ldr r12, [r0, #0x0]
	smull r4, lr, r3, r2
	ldr r2, [r1, #0x0]
	ldr r3, [r0, #0x8]
	smlal r4, lr, r12, r2
	ldr r1, [r1, #0x8]
	mov r0, #0x800
	smlal r4, lr, r3, r1
	adds r0, r4, r0
	adc r1, lr, #0x0
	mov r0, r0, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start VEC_Fx16Add
VEC_Fx16Add: ; 0x020C55CC
	ldrsh r12, [r0, #0x0]
	ldrsh r3, [r1, #0x0]
	add r3, r12, r3
	strh r3, [r2, #0x0]
	ldrsh r12, [r0, #0x2]
	ldrsh r3, [r1, #0x2]
	add r3, r12, r3
	strh r3, [r2, #0x2]
	ldrsh r3, [r0, #0x4]
	ldrsh r0, [r1, #0x4]
	add r0, r3, r0
	strh r0, [r2, #0x4]
	bx lr

	arm_func_start VEC_Subtract
VEC_Subtract: ; 0x020C5600
	ldr r12, [r0, #0x0]
	ldr r3, [r1, #0x0]
	sub r3, r12, r3
	str r3, [r2, #0x0]
	ldr r12, [r0, #0x4]
	ldr r3, [r1, #0x4]
	sub r3, r12, r3
	str r3, [r2, #0x4]
	ldr r3, [r0, #0x8]
	ldr r0, [r1, #0x8]
	sub r0, r3, r0
	str r0, [r2, #0x8]
	bx lr

	arm_func_start VEC_Add
VEC_Add: ; 0x020C5634
	ldr r12, [r0, #0x0]
	ldr r3, [r1, #0x0]
	add r3, r12, r3
	str r3, [r2, #0x0]
	ldr r12, [r0, #0x4]
	ldr r3, [r1, #0x4]
	add r3, r12, r3
	str r3, [r2, #0x4]
	ldr r3, [r0, #0x8]
	ldr r0, [r1, #0x8]
	add r0, r3, r0
	str r0, [r2, #0x8]
	bx lr
