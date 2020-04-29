    .include "asm/macros.inc"
    .include "global.inc"

    .text

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
