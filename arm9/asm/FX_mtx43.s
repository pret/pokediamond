	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start MTX_Identity43_
MTX_Identity43_: ; 0x020C426C
	mov r2, #0x1000
	mov r3, #0x0
	stmia r0!, {r2-r3}
	mov r1, #0x0
	stmia r0!, {r1,r3}
	stmia r0!, {r2-r3}
	stmia r0!, {r1,r3}
	stmia r0!, {r2-r3}
	stmia r0!, {r1,r3}
	bx lr

	arm_func_start MTX_Copy43To44_
MTX_Copy43To44_: ; 0x020C4294
	stmdb sp!, {r4}
	mov r12, #0x0
	ldmia r0!, {r2-r4}
	stmia r1!, {r2-r4,r12}
	ldmia r0!, {r2-r4}
	stmia r1!, {r2-r4,r12}
	ldmia r0!, {r2-r4}
	stmia r1!, {r2-r4,r12}
	mov r12, #0x1000
	ldmia r0!, {r2-r4}
	stmia r1!, {r2-r4,r12}
	ldmia sp!, {r4}
	bx lr

	thumb_func_start MTX_Scale43_
MTX_Scale43_: ; 0x020C42C8
	stmia r0!, {r1}
	mov r1, #0x0
	str r3, [r0, #0x1c]
	mov r3, #0x0
	stmia r0!, {r1,r3}
	stmia r0!, {r1-r3}
	mov r2, #0x0
	stmia r0!, {r1,r3}
	add r0, #0x4
	stmia r0!, {r1-r3}
	bx lr
	.balign 4

	thumb_func_start MTX_RotX43_
MTX_RotX43_: ; 0x020C42E0
	str r1, [r0, #0x14]
	neg r1, r1
	str r1, [r0, #0x1c]
	mov r1, #0x1
	lsl r1, r1, #0xc
	stmia r0!, {r1}
	mov r3, #0x0
	mov r1, #0x0
	stmia r0!, {r1,r3}
	stmia r0!, {r1-r2}
	str r1, [r0, #0x4]
	add r0, #0xc
	stmia r0!, {r2-r3}
	stmia r0!, {r1,r3}
	bx lr
	.balign 4

	thumb_func_start MTX_RotY43_
MTX_RotY43_: ; 0x020C4300
	str r1, [r0, #0x18]
	mov r3, #0x0
	stmia r0!, {r2-r3}
	neg r1, r1
	stmia r0!, {r1,r3}
	mov r1, #0x1
	lsl r1, r1, #0xc
	stmia r0!, {r1,r3}
	add r0, #0x4
	mov r1, #0x0
	stmia r0!, {r1-r3}
	stmia r0!, {r1,r3}
	bx lr
	.balign 4

	arm_func_start MTX_MultVec43
MTX_MultVec43: ; 0x020C431C
	stmdb sp!, {r4-r6,lr}
	ldr r12, [r0, #0x4]
	ldr r4, [r1, #0xc]
	ldr r3, [r0, #0x0]
	smull r6, r5, r12, r4
	ldr r4, [r1, #0x0]
	ldr r0, [r0, #0x8]
	smlal r6, r5, r3, r4
	ldr r4, [r1, #0x18]
	smlal r6, r5, r0, r4
	mov r4, r6, lsr #0xc
	orr r4, r4, r5, lsl #0x14
	str r4, [r2, #0x0]
	ldr r5, [r2, #0x0]
	ldr r4, [r1, #0x24]
	add r4, r5, r4
	str r4, [r2, #0x0]
	ldr r4, [r1, #0x10]
	ldr r5, [r1, #0x4]
	smull r6, lr, r12, r4
	smlal r6, lr, r3, r5
	ldr r4, [r1, #0x1c]
	smlal r6, lr, r0, r4
	mov r4, r6, lsr #0xc
	orr r4, r4, lr, lsl #0x14
	str r4, [r2, #0x4]
	ldr r5, [r2, #0x4]
	ldr r4, [r1, #0x28]
	add r4, r5, r4
	str r4, [r2, #0x4]
	ldr lr, [r1, #0x14]
	ldr r4, [r1, #0x8]
	smull r5, lr, r12, lr
	smlal r5, lr, r3, r4
	ldr r3, [r1, #0x20]
	smlal r5, lr, r0, r3
	mov r0, r5, lsr #0xc
	orr r0, r0, lr, lsl #0x14
	str r0, [r2, #0x8]
	ldr r3, [r2, #0x8]
	ldr r0, [r1, #0x2c]
	add r0, r3, r0
	str r0, [r2, #0x8]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start MTX_Concat43
MTX_Concat43: ; 0x020C43D0
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x30
	ldr r5, [r0, #0x4]
	ldr r3, [r1, #0xc]
	mov r12, r2
	smull r8, r7, r5, r3
	ldr r6, [r0, #0x0]
	ldr r3, [r1, #0x0]
	cmp r12, r1
	smlal r8, r7, r6, r3
	ldr r4, [r0, #0x8]
	ldr r3, [r1, #0x18]
	addeq r2, sp, #0x0
	smlal r8, r7, r4, r3
	mov r3, r8, lsr #0xc
	orr r3, r3, r7, lsl #0x14
	str r3, [r2, #0x0]
	ldr r3, [r1, #0x10]
	ldr r7, [r1, #0x4]
	smull r9, r8, r5, r3
	smlal r9, r8, r6, r7
	ldr r3, [r1, #0x1c]
	add lr, sp, #0x0
	smlal r9, r8, r4, r3
	mov r3, r9, lsr #0xc
	orr r3, r3, r8, lsl #0x14
	str r3, [r2, #0x4]
	ldr r3, [r1, #0x14]
	ldr r7, [r1, #0x8]
	smull r9, r8, r5, r3
	smlal r9, r8, r6, r7
	ldr r6, [r1, #0x20]
	smlal r9, r8, r4, r6
	mov r4, r9, lsr #0xc
	orr r4, r4, r8, lsl #0x14
	str r4, [r2, #0x8]
	ldr r4, [r0, #0x10]
	ldr r5, [r0, #0xc]
	smull r9, r8, r4, r3
	smlal r9, r8, r5, r7
	ldr r3, [r0, #0x14]
	smlal r9, r8, r3, r6
	mov r6, r9, lsr #0xc
	orr r6, r6, r8, lsl #0x14
	str r6, [r2, #0x14]
	ldr r6, [r1, #0x10]
	ldr r7, [r1, #0x4]
	smull r9, r8, r4, r6
	smlal r9, r8, r5, r7
	ldr r6, [r1, #0x1c]
	smlal r9, r8, r3, r6
	mov r6, r9, lsr #0xc
	orr r6, r6, r8, lsl #0x14
	str r6, [r2, #0x10]
	ldr r7, [r1, #0xc]
	ldr r8, [r1, #0x0]
	smull r10, r9, r4, r7
	smlal r10, r9, r5, r8
	ldr r6, [r1, #0x18]
	smlal r10, r9, r3, r6
	mov r3, r10, lsr #0xc
	orr r3, r3, r9, lsl #0x14
	str r3, [r2, #0xc]
	ldr r4, [r0, #0x1c]
	ldr r5, [r0, #0x18]
	smull r9, r7, r4, r7
	smlal r9, r7, r5, r8
	ldr r3, [r0, #0x20]
	smlal r9, r7, r3, r6
	mov r6, r9, lsr #0xc
	orr r6, r6, r7, lsl #0x14
	str r6, [r2, #0x18]
	ldr r6, [r1, #0x10]
	ldr r7, [r1, #0x4]
	smull r9, r6, r4, r6
	smlal r9, r6, r5, r7
	ldr r8, [r1, #0x1c]
	smlal r9, r6, r3, r8
	mov r7, r9, lsr #0xc
	orr r7, r7, r6, lsl #0x14
	str r7, [r2, #0x1c]
	ldr r7, [r1, #0x14]
	ldr r6, [r1, #0x8]
	smull r9, r8, r4, r7
	smlal r9, r8, r5, r6
	ldr r5, [r1, #0x20]
	smlal r9, r8, r3, r5
	mov r3, r9, lsr #0xc
	orr r3, r3, r8, lsl #0x14
	str r3, [r2, #0x20]
	ldr r4, [r0, #0x28]
	ldr r3, [r0, #0x24]
	smull r8, r7, r4, r7
	smlal r8, r7, r3, r6
	ldr r0, [r0, #0x2c]
	ldr r6, [r1, #0x2c]
	smlal r8, r7, r0, r5
	mov r5, r8, lsr #0xc
	orr r5, r5, r7, lsl #0x14
	adds r5, r6, r5
	str r5, [r2, #0x2c]
	ldr r5, [r1, #0x10]
	ldr r6, [r1, #0x4]
	smull r8, r5, r4, r5
	smlal r8, r5, r3, r6
	ldr r7, [r1, #0x1c]
	ldr r9, [r1, #0x28]
	smlal r8, r5, r0, r7
	mov r6, r8, lsr #0xc
	orr r6, r6, r5, lsl #0x14
	adds r5, r9, r6
	str r5, [r2, #0x28]
	ldr r8, [r1, #0x24]
	ldr r6, [r1, #0x18]
	ldr r5, [r1, #0x0]
	ldr r1, [r1, #0xc]
	smull r7, r1, r4, r1
	smlal r7, r1, r3, r5
	smlal r7, r1, r0, r6
	mov r0, r7, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	adds r0, r8, r0
	cmp r2, lr
	str r0, [r2, #0x24]
	addne sp, sp, #0x30
	ldmneia sp!, {r4-r10,lr}
	bxne lr
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldmia lr, {r0-r3}
	stmia r12, {r0-r3}
	add sp, sp, #0x30
	ldmia sp!, {r4-r10,lr}
	bx lr

	arm_func_start MTX_Inverse43
MTX_Inverse43: ; 0x020C45F0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x5c
	mov r10, r0
	ldr r11, [r10, #0x14]
	cmp r10, r1
	addeq r9, sp, #0x2c
	ldr r3, [r10, #0x18]
	ldr r2, [r10, #0xc]
	ldr r8, [r10, #0x20]
	str r1, [sp, #0x0]
	movne r9, r1
	smull r7, r5, r2, r8
	smull r6, r1, r11, r3
	ldr r4, [r10, #0x1c]
	subs r12, r7, r6
	ldr r0, [r10, #0x10]
	smull r6, lr, r11, r4
	sbc r11, r5, r1
	smull r5, r4, r2, r4
	mov r1, #0x800
	smull r8, r7, r0, r8
	smull r3, r2, r0, r3
	adds r12, r12, r1
	adc r0, r11, #0x0
	subs r8, r8, r6
	sbc r6, r7, lr
	adds r7, r8, r1
	adc r11, r6, #0x0
	mov r7, r7, lsr #0xc
	mov r8, r12, lsr #0xc
	orr r7, r7, r11, lsl #0x14
	orr r8, r8, r0, lsl #0x14
	subs r0, r5, r3
	sbc r12, r4, r2
	ldr r6, [r10, #0x4]
	ldr r11, [r10, #0x0]
	smull r3, r2, r6, r8
	adds r0, r0, r1
	smull r5, r4, r11, r7
	adc r11, r12, #0x0
	mov r6, r0, lsr #0xc
	subs r3, r5, r3
	ldr r0, [r10, #0x8]
	orr r6, r6, r11, lsl #0x14
	sbc r2, r4, r2
	smlal r3, r2, r0, r6
	adds r0, r3, r1
	mov r1, r8, asr #0x1f
	str r1, [sp, #0x4]
	mov r1, r7, asr #0x1f
	str r1, [sp, #0x8]
	mov r1, r6, asr #0x1f
	adc r2, r2, #0x0
	mov r0, r0, lsr #0xc
	orrs r0, r0, r2, lsl #0x14
	str r1, [sp, #0xc]
	addeq sp, sp, #0x5c
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	bl FX_InvAsync
	ldr r1, [r10, #0x8]
	ldr r2, [r10, #0x1c]
	ldr r11, [r10, #0x10]
	smull r0, r4, r2, r1
	smull r3, r2, r11, r1
	ldr r5, [r10, #0x18]
	str r2, [sp, #0x18]
	str r3, [sp, #0x14]
	smull r3, r2, r5, r1
	str r2, [sp, #0x20]
	ldr r2, [r10, #0x20]
	ldr lr, [r10, #0x4]
	str r2, [sp, #0x10]
	ldr r5, [sp, #0x10]
	str r3, [sp, #0x1c]
	smull r12, r5, lr, r5
	subs r0, r12, r0
	ldr r2, [r10, #0xc]
	sbc r4, r5, r4
	smull r1, r5, r2, r1
	str r5, [sp, #0x28]
	mov r5, r0, lsr #0xc
	ldr r11, [r10, #0x14]
	orr r5, r5, r4, lsl #0x14
	smull r4, r2, lr, r11
	ldr r0, [sp, #0x14]
	ldr r3, [r10, #0x0]
	subs r4, r4, r0
	ldr r0, [sp, #0x18]
	mov r4, r4, lsr #0xc
	sbc r0, r2, r0
	orr r4, r4, r0, lsl #0x14
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x1c]
	smull r12, r0, r3, r0
	subs r2, r12, r2
	ldr r12, [sp, #0x20]
	sbc r0, r0, r12
	smull r12, r11, r3, r11
	ldr r3, [sp, #0x28]
	subs r1, r12, r1
	sbc r3, r11, r3
	mov r11, r2, lsr #0xc
	orr r11, r11, r0, lsl #0x14
	mov r0, r1, lsr #0xc
	str r0, [sp, #0x24]
	orr r0, r0, r3, lsl #0x14
	str r0, [sp, #0x24]
	bl FX_GetDivResult
	smull r2, r1, r0, r5
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	rsb lr, r2, #0x0
	smull r2, r1, r0, r4
	mov r4, r2, lsr #0xc
	orr r4, r4, r1, lsl #0x14
	smull r2, r1, r0, r11
	mov r3, r2, lsr #0xc
	orr r3, r3, r1, lsl #0x14
	ldr r1, [sp, #0x24]
	umull r11, r5, r0, r7
	smull r2, r1, r0, r1
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	ldr r1, [sp, #0x8]
	mov r12, r0, asr #0x1f
	mla r5, r0, r1, r5
	mla r5, r12, r7, r5
	mov r1, r11, lsr #0xc
	orr r1, r1, r5, lsl #0x14
	str r1, [r9, #0x0]
	str lr, [r9, #0x4]
	str r4, [r9, #0x8]
	ldr r1, [sp, #0x4]
	umull r5, r4, r0, r8
	mla r4, r0, r1, r4
	mla r4, r12, r8, r4
	mov r1, r5, lsr #0xc
	orr r1, r1, r4, lsl #0x14
	rsb r1, r1, #0x0
	str r1, [r9, #0xc]
	ldr r1, [sp, #0xc]
	rsb r2, r2, #0x0
	str r3, [r9, #0x10]
	str r2, [r9, #0x14]
	umull r3, r2, r0, r6
	mla r2, r0, r1, r2
	mla r2, r12, r6, r2
	mov r1, r3, lsr #0xc
	orr r1, r1, r2, lsl #0x14
	str r1, [r9, #0x18]
	ldr r3, [r10, #0x0]
	ldr r1, [r10, #0x1c]
	ldr r2, [r10, #0x18]
	smull r5, r4, r3, r1
	ldr r1, [r10, #0x4]
	smull r3, r1, r2, r1
	subs r2, r5, r3
	sbc r1, r4, r1
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	smull r2, r1, r0, r2
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	rsb r1, r2, #0x0
	str r1, [r9, #0x1c]
	ldr r3, [r10, #0x0]
	ldr r1, [r10, #0x10]
	ldr r2, [r10, #0xc]
	smull r5, r4, r3, r1
	ldr r1, [r10, #0x4]
	smull r3, r1, r2, r1
	subs r2, r5, r3
	sbc r1, r4, r1
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	smull r2, r1, r0, r2
	mov r0, r2, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	str r0, [r9, #0x20]
	add r0, sp, #0x2c
	ldr r2, [r9, #0xc]
	ldr r1, [r10, #0x28]
	ldr r4, [r9, #0x0]
	smull r7, r1, r2, r1
	ldr r3, [r10, #0x24]
	ldr r6, [r9, #0x18]
	smlal r7, r1, r4, r3
	ldr r5, [r10, #0x2c]
	cmp r9, r0
	smlal r7, r1, r6, r5
	mov r2, r7, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	rsb r1, r2, #0x0
	str r1, [r9, #0x24]
	ldr r2, [r9, #0x10]
	ldr r1, [r10, #0x28]
	ldr r4, [r9, #0x4]
	smull r7, r1, r2, r1
	ldr r3, [r10, #0x24]
	ldr r6, [r9, #0x1c]
	smlal r7, r1, r4, r3
	ldr r5, [r10, #0x2c]
	smlal r7, r1, r6, r5
	mov r2, r7, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	rsb r1, r2, #0x0
	str r1, [r9, #0x28]
	ldr r1, [r10, #0x28]
	ldr r2, [r9, #0x14]
	ldr r4, [r9, #0x8]
	smull r7, r1, r2, r1
	ldr r3, [r10, #0x24]
	ldr r6, [r9, #0x20]
	smlal r7, r1, r4, r3
	ldr r5, [r10, #0x2c]
	smlal r7, r1, r6, r5
	mov r2, r7, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	rsb r1, r2, #0x0
	str r1, [r9, #0x2c]
	bne _020C4974
	ldr r1, [sp, #0x0]
	bl MI_Copy48B
_020C4974:
	mov r0, #0x0
	add sp, sp, #0x5c
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start MTX_ScaleApply43
MTX_ScaleApply43: ; 0x020C4984
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r12, [sp, #0x10]
	mov r5, r0
	str r12, [sp, #0x0]
	mov r4, r1
	bl MTX_ScaleApply33
	ldr r0, [r5, #0x24]
	str r0, [r4, #0x24]
	ldr r0, [r5, #0x28]
	str r0, [r4, #0x28]
	ldr r0, [r5, #0x2c]
	str r0, [r4, #0x2c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
