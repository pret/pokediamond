	.include "asm/macros.inc"
	.include "global.inc"

    .text

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
