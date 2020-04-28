	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MTX_Identity22_
MTX_Identity22_: ; 0x020C3E8C
	mov r1, #0x0
	mov r2, #0x1000
	mov r3, #0x0
	stmia r0!, {r2-r3}
	stmia r0!, {r1-r2}
	bx lr

	thumb_func_start MTX_Rot22_
MTX_Rot22_: ; 0x020C3EA4
	str r2, [r0, #0x0]
	str r1, [r0, #0x4]
	neg r1, r1
	str r1, [r0, #0x8]
	str r2, [r0, #0xc]
	bx lr

	arm_func_start MTX_ScaleApply22
MTX_ScaleApply22: ; 0x020C3EB0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r12, [r0, #0x0]
	smull lr, r12, r2, r12
	mov lr, lr, lsr #0xc
	orr lr, lr, r12, lsl #0x14
	str lr, [r1, #0x0]
	ldr r12, [r0, #0x4]
	smull lr, r12, r2, r12
	mov r2, lr, lsr #0xc
	orr r2, r2, r12, lsl #0x14
	str r2, [r1, #0x4]
	ldr r2, [r0, #0x8]
	smull r12, r2, r3, r2
	mov r12, r12, lsr #0xc
	orr r12, r12, r2, lsl #0x14
	str r12, [r1, #0x8]
	ldr r0, [r0, #0xc]
	smull r2, r0, r3, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [r1, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start MTX_Identity33_
MTX_Identity33_: ; 0x020C3F14
	mov r2, #0x1000
	str r2, [r0, #0x20]
	mov r3, #0x0
	stmia r0!, {r2-r3}
	mov r1, #0x0
	stmia r0!, {r1,r3}
	stmia r0!, {r2-r3}
	stmia r0!, {r1,r3}
	bx lr

	thumb_func_start MTX_RotX33_
MTX_RotX33_: ; 0x020C3F38
	mov r3, #0x1
	lsl r3, r3, #0xc
	str r3, [r0, #0x0]
	mov r3, #0x0
	str r3, [r0, #0x4]
	str r3, [r0, #0x8]
	str r3, [r0, #0xc]
	str r2, [r0, #0x10]
	str r1, [r0, #0x14]
	str r3, [r0, #0x18]
	neg r1, r1
	str r1, [r0, #0x1c]
	str r2, [r0, #0x20]
	bx lr

	thumb_func_start MTX_RotY33_
MTX_RotY33_: ; 0x020C3F54
	str r2, [r0, #0x0]
	str r2, [r0, #0x20]
	mov r3, #0x0
	str r3, [r0, #0x4]
	str r3, [r0, #0xc]
	str r3, [r0, #0x14]
	str r3, [r0, #0x1c]
	neg r2, r1
	mov r3, #0x1
	lsl r3, r3, #0xc
	str r1, [r0, #0x18]
	str r2, [r0, #0x8]
	str r3, [r0, #0x10]
	bx lr

	thumb_func_start MTX_RotZ33_
MTX_RotZ33_: ; 0x020C3F70
	stmia r0!, {r2}
	mov r3, #0x0
	stmia r0!, {r1,r3}
	neg r1, r1
	stmia r0!, {r1-r2}
	mov r1, #0x1
	lsl r1, r1, #0xc
	str r3, [r0, #0x0]
	str r3, [r0, #0x4]
	str r3, [r0, #0x8]
	str r1, [r0, #0xc]
	bx lr

	arm_func_start MTX_MultVec33
MTX_MultVec33: ; 0x020C3F88
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
	ldr r4, [r1, #0x10]
	ldr r5, [r1, #0x4]
	smull r6, lr, r12, r4
	smlal r6, lr, r3, r5
	ldr r4, [r1, #0x1c]
	smlal r6, lr, r0, r4
	mov r4, r6, lsr #0xc
	orr r4, r4, lr, lsl #0x14
	str r4, [r2, #0x4]
	ldr lr, [r1, #0x14]
	ldr r4, [r1, #0x8]
	smull r5, lr, r12, lr
	smlal r5, lr, r3, r4
	ldr r1, [r1, #0x20]
	smlal r5, lr, r0, r1
	mov r0, r5, lsr #0xc
	orr r0, r0, lr, lsl #0x14
	str r0, [r2, #0x8]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start MTX_Concat33
MTX_Concat33: ; 0x020C400C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x24
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
	cmp r2, lr
	smlal r9, r8, r4, r6
	mov r4, r9, lsr #0xc
	orr r4, r4, r8, lsl #0x14
	str r4, [r2, #0x8]
	ldr r4, [r0, #0x10]
	ldr r5, [r0, #0xc]
	smull r9, r8, r4, r3
	smlal r9, r8, r5, r7
	ldr r3, [r0, #0x14]
	addne sp, sp, #0x24
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
	ldr r6, [r1, #0x0]
	smull r9, r8, r4, r7
	smlal r9, r8, r5, r6
	ldr r5, [r1, #0x18]
	smlal r9, r8, r3, r5
	mov r3, r9, lsr #0xc
	orr r3, r3, r8, lsl #0x14
	str r3, [r2, #0xc]
	ldr r4, [r0, #0x1c]
	ldr r3, [r0, #0x18]
	smull r8, r7, r4, r7
	smlal r8, r7, r3, r6
	ldr r0, [r0, #0x20]
	smlal r8, r7, r0, r5
	mov r5, r8, lsr #0xc
	orr r5, r5, r7, lsl #0x14
	str r5, [r2, #0x18]
	ldr r5, [r1, #0x10]
	ldr r6, [r1, #0x4]
	smull r8, r5, r4, r5
	smlal r8, r5, r3, r6
	ldr r7, [r1, #0x1c]
	smlal r8, r5, r0, r7
	mov r6, r8, lsr #0xc
	orr r6, r6, r5, lsl #0x14
	str r6, [r2, #0x1c]
	ldr r6, [r1, #0x20]
	ldr r5, [r1, #0x8]
	ldr r1, [r1, #0x14]
	smull r7, r1, r4, r1
	smlal r7, r1, r3, r5
	smlal r7, r1, r0, r6
	mov r0, r7, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	str r0, [r2, #0x20]
	ldmneia sp!, {r4-r9,lr}
	bxne lr
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldr r0, [lr, #0x0]
	str r0, [r12, #0x0]
	add sp, sp, #0x24
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start MTX_ScaleApply33
MTX_ScaleApply33: ; 0x020C41A8
	stmdb sp!, {r4,lr}
	ldr r4, [r0, #0x0]
	ldr r12, [sp, #0x8]
	smull lr, r4, r2, r4
	mov lr, lr, lsr #0xc
	orr lr, lr, r4, lsl #0x14
	str lr, [r1, #0x0]
	ldr r4, [r0, #0x4]
	smull lr, r4, r2, r4
	mov lr, lr, lsr #0xc
	orr lr, lr, r4, lsl #0x14
	str lr, [r1, #0x4]
	ldr lr, [r0, #0x8]
	smull r4, lr, r2, lr
	mov r2, r4, lsr #0xc
	orr r2, r2, lr, lsl #0x14
	str r2, [r1, #0x8]
	ldr r2, [r0, #0xc]
	smull lr, r2, r3, r2
	mov lr, lr, lsr #0xc
	orr lr, lr, r2, lsl #0x14
	str lr, [r1, #0xc]
	ldr r2, [r0, #0x10]
	smull lr, r2, r3, r2
	mov lr, lr, lsr #0xc
	orr lr, lr, r2, lsl #0x14
	str lr, [r1, #0x10]
	ldr r2, [r0, #0x14]
	smull lr, r2, r3, r2
	mov r3, lr, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	str r3, [r1, #0x14]
	ldr r2, [r0, #0x18]
	smull r3, r2, r12, r2
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	str r3, [r1, #0x18]
	ldr r2, [r0, #0x1c]
	smull r3, r2, r12, r2
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	str r3, [r1, #0x1c]
	ldr r0, [r0, #0x20]
	smull r2, r0, r12, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [r1, #0x20]
	ldmia sp!, {r4,lr}
	bx lr

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

	arm_func_start MTX_Identity44_
MTX_Identity44_: ; 0x020C49C4
	mov r2, #0x1000
	mov r3, #0x0
	stmia r0!, {r2-r3}
	mov r1, #0x0
	stmia r0!, {r1,r3}
	stmia r0!, {r1-r3}
	stmia r0!, {r1,r3}
	stmia r0!, {r1-r3}
	stmia r0!, {r1,r3}
	stmia r0!, {r1-r2}
	bx lr

	arm_func_start MTX_Copy44To43_
MTX_Copy44To43_:
	ldmia r0!, {r2-r3,r12}
	add r0, r0, #0x4
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	add r0, r0, #0x4
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	add r0, r0, #0x4
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	add r0, r0, #0x4
	stmia r1!, {r2-r3,r12}
	bx lr

	thumb_func_start MTX_RotX44_
MTX_RotX44_: ; 0x020C4A24
	str r2, [r0, #0x14]
	str r2, [r0, #0x28]
	str r1, [r0, #0x18]
	neg r1, r1
	str r1, [r0, #0x24]
	mov r1, #0x1
	mov r2, #0x0
	lsl r1, r1, #0xc
	mov r3, #0x0
	stmia r0!, {r1-r3}
	stmia r0!, {r2-r3}
	add r0, #0x8
	stmia r0!, {r2-r3}
	add r0, #0x8
	stmia r0!, {r2-r3}
	stmia r0!, {r2-r3}
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start MTX_RotY44_
MTX_RotY44_: ; 0x020C4A48
	str r2, [r0, #0x0]
	str r2, [r0, #0x28]
	str r1, [r0, #0x20]
	neg r1, r1
	str r1, [r0, #0x8]
	mov r3, #0x1
	mov r1, #0x0
	lsl r3, r3, #0xc
	mov r2, #0x0
	str r2, [r0, #0x4]
	add r0, #0xc
	stmia r0!, {r1-r3}
	stmia r0!, {r1-r2}
	str r2, [r0, #0x4]
	add r0, #0xc
	stmia r0!, {r1-r2}
	stmia r0!, {r1-r3}
	bx lr

	thumb_func_start MTX_RotZ44_
MTX_RotZ44_: ; 0x020C4A6C
	str r2, [r0, #0x0]
	str r2, [r0, #0x14]
	str r1, [r0, #0x4]
	neg r1, r1
	str r1, [r0, #0x10]
	mov r3, #0x1
	mov r1, #0x0
	lsl r3, r3, #0xc
	mov r2, #0x0
	add r0, #0x8
	stmia r0!, {r1-r2}
	add r0, #0x8
	stmia r0!, {r1-r2}
	stmia r0!, {r1-r3}
	stmia r0!, {r1-r2}
	stmia r0!, {r1-r3}
	bx lr
	.balign 4

	arm_func_start MTX_Concat44
MTX_Concat44: ; 0x020C4A90
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x44
	ldr r5, [r0, #0x4]
	ldr r3, [r1, #0x10]
	mov r12, r2
	smull r6, r4, r5, r3
	ldr r9, [r0, #0x0]
	ldr r3, [r1, #0x0]
	cmp r12, r1
	smlal r6, r4, r9, r3
	ldr r10, [r0, #0x8]
	ldr r3, [r1, #0x20]
	ldr r8, [r0, #0xc]
	smlal r6, r4, r10, r3
	ldr r3, [r1, #0x30]
	addeq r2, sp, #0x0
	smlal r6, r4, r8, r3
	mov r3, r6, lsr #0xc
	orr r3, r3, r4, lsl #0x14
	str r3, [r2, #0x0]
	ldr r3, [r1, #0x14]
	ldr r4, [r1, #0x4]
	smull r7, r6, r5, r3
	smlal r7, r6, r9, r4
	ldr r3, [r1, #0x24]
	ldr r4, [r1, #0x34]
	smlal r7, r6, r10, r3
	smlal r7, r6, r8, r4
	mov r3, r7, lsr #0xc
	orr r3, r3, r6, lsl #0x14
	str r3, [r2, #0x4]
	ldr r3, [r1, #0x1c]
	ldr r4, [r1, #0xc]
	smull r7, r6, r5, r3
	smlal r7, r6, r9, r4
	ldr r3, [r1, #0x2c]
	ldr r4, [r1, #0x3c]
	smlal r7, r6, r10, r3
	smlal r7, r6, r8, r4
	mov r3, r7, lsr #0xc
	orr r3, r3, r6, lsl #0x14
	str r3, [r2, #0xc]
	ldr r6, [r1, #0x18]
	ldr r7, [r1, #0x8]
	smull r4, r3, r5, r6
	smlal r4, r3, r9, r7
	ldr r9, [r1, #0x28]
	ldr r5, [r1, #0x38]
	smlal r4, r3, r10, r9
	smlal r4, r3, r8, r5
	mov r4, r4, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x8]
	ldr r8, [r0, #0x14]
	ldr r10, [r0, #0x10]
	smull r4, r3, r8, r6
	smlal r4, r3, r10, r7
	ldr r7, [r0, #0x18]
	ldr r6, [r0, #0x1c]
	smlal r4, r3, r7, r9
	smlal r4, r3, r6, r5
	mov r4, r4, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x18]
	ldr r3, [r1, #0x14]
	ldr r4, [r1, #0x4]
	smull r11, r3, r8, r3
	smlal r11, r3, r10, r4
	ldr r5, [r1, #0x24]
	ldr r9, [r1, #0x34]
	smlal r11, r3, r7, r5
	smlal r11, r3, r6, r9
	mov r4, r11, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x14]
	ldr r3, [r1, #0x1c]
	ldr r4, [r1, #0xc]
	smull r11, r3, r8, r3
	smlal r11, r3, r10, r4
	ldr r5, [r1, #0x2c]
	ldr r9, [r1, #0x3c]
	smlal r11, r3, r7, r5
	smlal r11, r3, r6, r9
	mov r4, r11, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x1c]
	ldr r9, [r1, #0x10]
	ldr r11, [r1, #0x0]
	smull r4, r3, r8, r9
	smlal r4, r3, r10, r11
	ldr r5, [r1, #0x20]
	ldr r8, [r1, #0x30]
	smlal r4, r3, r7, r5
	smlal r4, r3, r6, r8
	mov r4, r4, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x10]
	ldr r6, [r0, #0x24]
	ldr r7, [r0, #0x20]
	smull r4, r3, r6, r9
	smlal r4, r3, r7, r11
	ldr r10, [r0, #0x28]
	add lr, sp, #0x0
	smlal r4, r3, r10, r5
	ldr r5, [r0, #0x2c]
	cmp r2, lr
	smlal r4, r3, r5, r8
	mov r4, r4, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x20]
	ldr r3, [r1, #0x14]
	ldr r4, [r1, #0x4]
	smull r11, r3, r6, r3
	smlal r11, r3, r7, r4
	ldr r8, [r1, #0x24]
	ldr r9, [r1, #0x34]
	smlal r11, r3, r10, r8
	smlal r11, r3, r5, r9
	mov r4, r11, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x24]
	ldr r3, [r1, #0x1c]
	ldr r4, [r1, #0xc]
	smull r11, r3, r6, r3
	smlal r11, r3, r7, r4
	ldr r8, [r1, #0x2c]
	ldr r9, [r1, #0x3c]
	smlal r11, r3, r10, r8
	smlal r11, r3, r5, r9
	mov r4, r11, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x2c]
	ldr r9, [r1, #0x18]
	ldr r8, [r1, #0x8]
	smull r4, r3, r6, r9
	smlal r4, r3, r7, r8
	ldr r7, [r1, #0x28]
	ldr r6, [r1, #0x38]
	smlal r4, r3, r10, r7
	smlal r4, r3, r5, r6
	mov r4, r4, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x28]
	ldr r5, [r0, #0x34]
	ldr r4, [r0, #0x30]
	smull r10, r9, r5, r9
	ldr r3, [r0, #0x38]
	smlal r10, r9, r4, r8
	smlal r10, r9, r3, r7
	ldr r0, [r0, #0x3c]
	addne sp, sp, #0x44
	smlal r10, r9, r0, r6
	mov r6, r10, lsr #0xc
	orr r6, r6, r9, lsl #0x14
	str r6, [r2, #0x38]
	ldr r6, [r1, #0x14]
	ldr r7, [r1, #0x4]
	smull r10, r6, r5, r6
	smlal r10, r6, r4, r7
	ldr r8, [r1, #0x24]
	ldr r9, [r1, #0x34]
	smlal r10, r6, r3, r8
	smlal r10, r6, r0, r9
	mov r7, r10, lsr #0xc
	orr r7, r7, r6, lsl #0x14
	str r7, [r2, #0x34]
	ldr r6, [r1, #0x10]
	ldr r7, [r1, #0x0]
	smull r10, r6, r5, r6
	smlal r10, r6, r4, r7
	ldr r8, [r1, #0x20]
	ldr r9, [r1, #0x30]
	smlal r10, r6, r3, r8
	smlal r10, r6, r0, r9
	mov r7, r10, lsr #0xc
	orr r7, r7, r6, lsl #0x14
	str r7, [r2, #0x30]
	ldr r8, [r1, #0x3c]
	ldr r7, [r1, #0x2c]
	ldr r6, [r1, #0xc]
	ldr r1, [r1, #0x1c]
	smull r9, r1, r5, r1
	smlal r9, r1, r4, r6
	smlal r9, r1, r3, r7
	smlal r9, r1, r0, r8
	mov r0, r9, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	str r0, [r2, #0x3c]
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldmia lr, {r0-r3}
	stmia r12, {r0-r3}
	add sp, sp, #0x44
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start MTX_TransApply44
MTX_TransApply44: ; 0x020C4DB4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	cmp r7, r6
	beq _020C4DD8
	bl MI_Copy48B
_020C4DD8:
	ldr r0, [r7, #0x10]
	ldr r1, [r7, #0x0]
	smull r3, r2, r4, r0
	smlal r3, r2, r5, r1
	ldr r0, [sp, #0x18]
	ldr r1, [r7, #0x20]
	ldr r12, [r7, #0x30]
	smlal r3, r2, r0, r1
	mov r1, r3, lsr #0xc
	orr r1, r1, r2, lsl #0x14
	add r1, r12, r1
	str r1, [r6, #0x30]
	ldr r1, [r7, #0x14]
	ldr r2, [r7, #0x4]
	smull r12, r3, r4, r1
	smlal r12, r3, r5, r2
	ldr r1, [r7, #0x24]
	ldr r2, [r7, #0x34]
	smlal r12, r3, r0, r1
	mov r1, r12, lsr #0xc
	orr r1, r1, r3, lsl #0x14
	add r1, r2, r1
	str r1, [r6, #0x34]
	ldr r1, [r7, #0x18]
	ldr r2, [r7, #0x8]
	smull r12, r3, r4, r1
	smlal r12, r3, r5, r2
	ldr r1, [r7, #0x28]
	ldr r2, [r7, #0x38]
	smlal r12, r3, r0, r1
	mov r1, r12, lsr #0xc
	orr r1, r1, r3, lsl #0x14
	add r1, r2, r1
	str r1, [r6, #0x38]
	ldr r1, [r7, #0x1c]
	ldr r2, [r7, #0xc]
	smull r12, r3, r4, r1
	smlal r12, r3, r5, r2
	ldr r1, [r7, #0x2c]
	ldr r2, [r7, #0x3c]
	smlal r12, r3, r0, r1
	mov r0, r12, lsr #0xc
	orr r0, r0, r3, lsl #0x14
	add r0, r2, r0
	str r0, [r6, #0x3c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

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

	arm_func_start FX_GetSqerResult
FX_GetSqerResult: ; 0x020C4F80
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
	bl FX_GetSqerResult
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

	arm_func_start FX_Atan2
FX_Atan2: ; 0x020C5668
	stmdb sp!, {r4,lr}
	cmp r0, #0x0
	ble _020C5704
	cmp r1, #0x0
	ble _020C56B4
	cmp r1, r0
	movgt r3, r0
	movgt r4, #0x0
	movgt r0, #0x1
	bgt _020C57C8
	cmp r1, r0
	movlt r3, r1
	movlt r1, r0
	movlt r4, #0x4000
	movlt r0, #0x0
	blt _020C57C8
	mov r0, #0x2000
	ldmia sp!, {r4,lr}
	bx lr
_020C56B4:
	cmp r1, #0x0
	bge _020C56F8
	rsb r1, r1, #0x0
	cmp r1, r0
	movlt r3, r1
	movlt r1, r0
	movlt r4, #0x4000
	movlt r0, #0x1
	blt _020C57C8
	cmp r1, r0
	movgt r3, r0
	movgt r4, #0x8000
	movgt r0, #0x0
	bgt _020C57C8
	mov r0, #0x6000
	ldmia sp!, {r4,lr}
	bx lr
_020C56F8:
	mov r0, #0x4000
	ldmia sp!, {r4,lr}
	bx lr
_020C5704:
	cmp r0, #0x0
	bge _020C57B4
	cmp r1, #0x0
	rsb r2, r0, #0x0
	bge _020C5760
	rsb r1, r1, #0x0
	cmp r1, r2
	movgt r0, #0x8000
	rsbgt r4, r0, #0x0
	movgt r3, r2
	movgt r0, #0x1
	bgt _020C57C8
	cmp r1, r2
	bge _020C5754
	mov r0, #0x4000
	mov r3, r1
	mov r1, r2
	rsb r4, r0, #0x0
	mov r0, #0x0
	b _020C57C8
_020C5754:
	mov r0, #0xa000
	ldmia sp!, {r4,lr}
	bx lr
_020C5760:
	cmp r1, #0x0
	ble _020C57A8
	cmp r1, r2
	bge _020C5788
	mov r0, #0x4000
	mov r3, r1
	mov r1, r2
	rsb r4, r0, #0x0
	mov r0, #0x1
	b _020C57C8
_020C5788:
	cmp r1, r2
	movgt r4, #0x0
	movgt r3, r2
	movgt r0, r4
	bgt _020C57C8
	mov r0, #0xe000
	ldmia sp!, {r4,lr}
	bx lr
_020C57A8:
	mov r0, #0xc000
	ldmia sp!, {r4,lr}
	bx lr
_020C57B4:
	cmp r1, #0x0
	movge r0, #0x0
	movlt r0, #0x8000
	ldmia sp!, {r4,lr}
	bx lr
_020C57C8:
	cmp r1, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	cmp r0, #0x0
	beq _020C580C
	mov r0, r3
	bl FX_Div
	mov r1, r0, asr #0x5
	ldr r0, _020C5838 ; =FX_AtanTable_
	mov r1, r1, lsl #0x1
	ldrsh r0, [r0, r1]
	add r0, r4, r0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {r4,lr}
	bx lr
_020C580C:
	mov r0, r3
	bl FX_Div
	mov r1, r0, asr #0x5
	ldr r0, _020C5838 ; =FX_AtanTable_
	mov r1, r1, lsl #0x1
	ldrsh r0, [r0, r1]
	sub r0, r4, r0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C5838: .word FX_AtanTable_

	arm_func_start FX_Atan
FX_Atan: ; 0x020C583C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	blt _020C58A4
	cmp r0, #0x1000
	ble _020C5880
	bl FX_Inv
	mov r1, r0, asr #0x5
	ldr r0, _020C5924 ; =FX_AtanTable_
	mov r1, r1, lsl #0x1
	ldrsh r0, [r0, r1]
	add sp, sp, #0x4
	rsb r0, r0, #0x4000
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {lr}
	bx lr
_020C5880:
	cmp r0, #0x1000
	movlt r1, r0, asr #0x5
	ldrlt r0, _020C5924 ; =FX_AtanTable_
	movlt r1, r1, lsl #0x1
	ldrlth r0, [r0, r1]
	add sp, sp, #0x4
	movge r0, #0x2000
	ldmia sp!, {lr}
	bx lr
_020C58A4:
	mov r1, #0x1000
	rsb r1, r1, #0x0
	cmp r0, r1
	bge _020C58E4
	rsb r0, r0, #0x0
	bl FX_Inv
	mov r1, r0, asr #0x5
	ldr r0, _020C5924 ; =FX_AtanTable_
	mov r1, r1, lsl #0x1
	ldrsh r0, [r0, r1]
	add sp, sp, #0x4
	sub r0, r0, #0x4000
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {lr}
	bx lr
_020C58E4:
	cmp r0, r1
	addle sp, sp, #0x4
	movle r0, #0xe000
	ldmleia sp!, {lr}
	bxle lr
	rsb r0, r0, #0x0
	mov r1, r0, asr #0x5
	ldr r0, _020C5924 ; =FX_AtanTable_
	mov r1, r1, lsl #0x1
	ldrsh r0, [r0, r1]
	rsb r0, r0, #0x0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C5924: .word FX_AtanTable_

	arm_func_start FX_Modf
FX_Modf: ; 0x020C5928
	cmp r0, #0x0
	blt _020C5948
	ldr r2, _020C596C ; =0x7FFFF000
	ldr r3, _020C5970 ; =0x00000FFF
	and r2, r0, r2
	str r2, [r1, #0x0]
	and r0, r0, r3
	bx lr
_020C5948:
	ldr r2, _020C596C ; =0x7FFFF000
	rsb r3, r0, #0x0
	ldr r0, _020C5970 ; =0x00000FFF
	and r2, r3, r2
	rsb r2, r2, #0x0
	and r0, r3, r0
	str r2, [r1, #0x0]
	rsb r0, r0, #0x0
	bx lr
	.balign 4
_020C596C: .word 0x7FFFF000
_020C5970: .word 0x00000FFF

	arm_func_start FX_Init
FX_Init: ; 0x020C5974
	bx lr

