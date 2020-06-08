	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start SND_IsCaptureActive
SND_IsCaptureActive: ; 0x037FC4C0
	add	r0, r0, #67108864	; 0x4000000
	ldrb	r0, [r0, #1288]	; 0x508
	ands	r0, r0, #128	; 0x80
	movne	r0, #1
	moveq	r0, #0
	bx	lr

	arm_func_start SND_SetupCapture
SND_SetupCapture: ; 0x037FC4D8
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r4, r0, lsl #3
	ldr	ip, [sp, #16]
	cmp	ip, #0
	movne	r5, #0
	moveq	r5, #1
	ldr	lr, [sp, #24]
	ldr	ip, [sp, #20]
	mov	r1, r1, lsl #3
	orr	r1, r1, r5, lsl #2
	orr	r1, r1, ip, lsl #1
	orr	r1, lr, r1
	add	r0, r0, #67108864	; 0x4000000
	strb	r1, [r0, #1288]	; 0x508
	add	r0, r4, #67108864	; 0x4000000
	str	r2, [r0, #1296]	; 0x510
	add	r0, r0, #1280	; 0x500
	strh	r3, [r0, #20]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
