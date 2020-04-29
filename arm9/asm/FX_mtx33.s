	.include "asm/macros.inc"
	.include "global.inc"

	.text

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
