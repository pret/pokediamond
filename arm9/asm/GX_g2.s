    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start G2x_ChangeBlendBrightness_
G2x_ChangeBlendBrightness_: ; 0x020C7418
	cmp r1, #0x0
	ldrh r3, [r0, #0x0]
	bge _020C7444
	and r2, r3, #0xc0
	cmp r2, #0x80
	biceq r2, r3, #0xc0
	orreq r2, r2, #0xc0
	streqh r2, [r0, #0x0]
	rsb r1, r1, #0x0
	strh r1, [r0, #0x4]
	bx lr
_020C7444:
	and r2, r3, #0xc0
	cmp r2, #0xc0
	biceq r2, r3, #0xc0
	orreq r2, r2, #0x80
	streqh r2, [r0, #0x0]
	strh r1, [r0, #0x4]
	bx lr

	arm_func_start G2x_SetBlendBrightnessExt_
G2x_SetBlendBrightnessExt_: ; 0x020C7460
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr lr, [sp, #0x8]
	ldr r12, [sp, #0xc]
	orr r3, r3, lr, lsl #0x8
	cmp r12, #0x0
	orrge r1, r1, #0x80
	strh r3, [r0, #0x2]
	orrge r1, r1, r2, lsl #0x8
	strgeh r1, [r0, #0x0]
	strgeh r12, [r0, #0x4]
	addge sp, sp, #0x4
	ldmgeia sp!, {lr}
	bxge lr
	orr r1, r1, #0xc0
	orr r1, r1, r2, lsl #0x8
	strh r1, [r0, #0x0]
	rsb r1, r12, #0x0
	strh r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start G2x_SetBlendBrightness_
G2x_SetBlendBrightness_: ; 0x020C74B8
	cmp r2, #0x0
	orrlt r1, r1, #0xc0
	strlth r1, [r0, #0x0]
	rsblt r1, r2, #0x0
	strlth r1, [r0, #0x4]
	orrge r1, r1, #0x80
	strgeh r1, [r0, #0x0]
	strgeh r2, [r0, #0x4]
	bx lr

	arm_func_start G2x_SetBlendAlpha_
G2x_SetBlendAlpha_: ; 0x020C74DC
	ldr r12, [sp, #0x0]
	orr r1, r1, #0x40
	orr r2, r1, r2, lsl #0x8
	orr r1, r3, r12, lsl #0x8
	orr r1, r2, r1, lsl #0x10
	str r1, [r0, #0x0]
	bx lr

	arm_func_start G2x_SetBGyAffine_
G2x_SetBGyAffine_: ; 0x020C74F8
	stmdb sp!, {r4-r6,lr}
	ldr r5, [r1, #0x0]
	ldr r4, [r1, #0x4]
	mov r12, r5, lsl #0xc
	mov lr, r4, lsl #0xc
	mov r5, r12, asr #0x10
	mov r4, lr, asr #0x10
	mov r12, r5, lsl #0x10
	mov lr, r4, lsl #0x10
	mov r5, r12, lsr #0x10
	mov r4, lr, lsr #0x10
	orr r4, r5, r4, lsl #0x10
	str r4, [r0, #0x0]
	ldr r5, [r1, #0x8]
	ldr r4, [r1, #0xc]
	mov r12, r5, lsl #0xc
	mov lr, r4, lsl #0xc
	mov r5, r12, asr #0x10
	mov r4, lr, asr #0x10
	mov r12, r5, lsl #0x10
	mov lr, r4, lsl #0x10
	ldr r4, [sp, #0x14]
	ldr r6, [sp, #0x10]
	mov r12, r12, lsr #0x10
	mov r5, lr, lsr #0x10
	orr r5, r12, r5, lsl #0x10
	str r5, [r0, #0x4]
	ldr r12, [r1, #0x4]
	sub r5, r4, r3
	ldr r4, [r1, #0xc]
	mul lr, r12, r5
	mul r5, r4, r5
	ldr r12, [r1, #0x0]
	sub r6, r6, r2
	ldr r4, [r1, #0x8]
	mla r1, r12, r6, lr
	mla r5, r4, r6, r5
	add r1, r1, r2, lsl #0xc
	add r2, r5, r3, lsl #0xc
	mov r1, r1, asr #0x4
	str r1, [r0, #0x8]
	mov r1, r2, asr #0x4
	str r1, [r0, #0xc]
	ldmia sp!, {r4-r6,lr}
	bx lr
