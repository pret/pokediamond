	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start SND_UpdateSharedWork
SND_UpdateSharedWork: ; 0x037FF448
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r5, #0
	mov	r4, r5
	ldr	r0, _037FF4E4	; =SNDi_SharedWork
	ldr	r0, [r0]
	cmp	r0, #0
	beq	_037FF4D8
	mov	r7, r5
	mov	r6, #1
_037FF470:
	mov	r0, r7
	bl	SND_IsChannelActive
	cmp	r0, #0
	orrne	r0, r5, r6, lsl r7
	movne	r0, r0, lsl #16
	movne	r5, r0, lsr #16
	add	r7, r7, #1
	cmp	r7, #16
	blt	_037FF470
	mov	r0, #0
	bl	SND_IsCaptureActive
	cmp	r0, #0
	orrne	r0, r4, #1
	movne	r0, r0, lsl #16
	movne	r4, r0, lsr #16
	mov	r0, #1
	bl	SND_IsCaptureActive
	cmp	r0, #0
	orrne	r0, r4, #2
	movne	r0, r0, lsl #16
	movne	r4, r0, lsr #16
	ldr	r0, _037FF4E4	; =SNDi_SharedWork
	ldr	r1, [r0]
	strh	r5, [r1, #8]
	ldr	r0, [r0]
	strh	r4, [r0, #10]
_037FF4D8:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FF4E4:	.word	SNDi_SharedWork

	arm_func_start SND_SetPlayerGlobalVariable
SND_SetPlayerGlobalVariable: ; 0x037FF4E8
	ldr	r2, _037FF500	; =SNDi_SharedWork
	ldr	r2, [r2]
	add	r0, r2, r0, lsl #1
	add	r0, r0, #512	; 0x200
	strh	r1, [r0, #96]	; 0x60
	bx	lr
_037FF500:	.word	SNDi_SharedWork

	arm_func_start SND_SetPlayerLocalVariable
SND_SetPlayerLocalVariable: ; 0x037FF504
	ldr	r3, _037FF520	; =SNDi_SharedWork
	ldr	ip, [r3]
	mov	r3, #36	; 0x24
	mla	r3, r0, r3, ip
	add	r0, r3, r1, lsl #1
	strh	r2, [r0, #32]
	bx	lr
_037FF520:	.word	SNDi_SharedWork
