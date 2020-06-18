	.include "asm/macros.inc"
	.include "global.inc"

    .section .data

	.global _03807668
_03807668:
	.word	0xFFFFFFFF

	.global _0380766C
_0380766C:
	.word	0x00000001

    .section .bss

	.global _038099A0
_038099A0: ;0x038099A0
	.space 0x038099A4 - 0x038099A0

	.global _038099A4
_038099A4: ;0x038099A4
	.space 0x038099A8 - 0x038099A4

	.global _038099A8
_038099A8: ;0x038099A8
	.space 0x038099AC - 0x038099A8

	.section .text

	arm_func_start FUN_03800E54
FUN_03800E54: ; 0x03800E54
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #0
	bl	CTRDG_VibPulseEdgeUpdate
	bl	SND_BeginSleep
	bl	WVR_Shutdown
	bl	OS_Terminate
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start CARD_CheckPullOut_Polling
CARD_CheckPullOut_Polling: ; 0x03800E7C
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _03800F50	; =_038099A0
	ldr	r0, [r0]
	cmp	r0, #0
	bne	_03800F44
	ldr	r0, _03800F54	; =0x027FFC40
	ldrh	r0, [r0]
	cmp	r0, #2
	beq	_03800F44
	ldr	r1, _03800F58	; =_03807668
	ldr	r3, [r1]
	mvn	r0, #0
	cmp	r3, r0
	ldreq	r0, _03800F5C	; =0x027FFC3C
	ldreq	r0, [r0]
	addeq	r0, r0, #10
	streq	r0, [r1]
	beq	_03800F44
	ldr	r2, _03800F5C	; =0x027FFC3C
	ldr	r0, [r2]
	cmp	r0, r3
	bcc	_03800F44
	ldr	r0, [r2]
	add	r0, r0, #10
	str	r0, [r1]
	bl	CARD_IsPulledOut
	cmp	r0, #0
	beq	_03800F1C
	mov	r1, #1
	ldr	r0, _03800F50	; =_038099A0
	str	r1, [r0]
	bl	CARD_GetRomHeader
	ldr	r0, [r0, #12]
	cmp	r0, #0
	bne	_03800F1C
	ldr	r0, _03800F60	; =_0380766C
	ldr	r0, [r0]
	cmp	r0, #0
	bne	_03800F44
_03800F1C:
	mov	r1, #0
	ldr	r0, _03800F60	; =_0380766C
	str	r1, [r0]
	ldr	r0, _03800F50	; =_038099A0
	ldr	r0, [r0]
	cmp	r0, #0
	beq	_03800F44
	mov	r0, #17
	mov	r1, #100	; 0x64
	bl	FUN_03800E0C
_03800F44:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03800F50:	.word	_038099A0
_03800F54:	.word	0x027FFC40
_03800F58:	.word	_03807668
_03800F5C:	.word	0x027FFC3C
_03800F60:	.word	_0380766C

	arm_func_start CARD_IsCardIreqLo
CARD_IsCardIreqLo: ; 0x03800F64
	mov	r2, #1
	mov	r0, r2
	ldr	r1, _03800F88	; =0x04000214
	ldr	r1, [r1]
	ands	r1, r1, #1048576	; 0x100000
	movne	r0, #0
	ldrne	r1, _03800F8C	; =_038099A8
	strne	r2, [r1]
	bx	lr
_03800F88:	.word	0x04000214
_03800F8C:	.word	_038099A8

	arm_func_start CARD_CompareCardID
CARD_CompareCardID: ; 0x03800F90
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _03800FE8	; =0x027FFC10
	ldrh	r0, [r0]
	cmp	r0, #0
	ldreq	r0, _03800FEC	; =0x027FF800
	ldrne	r0, _03800FF0	; =0x027FFC00
	ldr	r0, [r0]
	str	r0, [sp]
	bl	CARDi_ReadRomID
	ldr	r1, [sp]
	cmp	r0, r1
	moveq	r0, #1
	movne	r0, #0
	cmp	r0, #0
	moveq	r2, #1
	movne	r2, #0
	ldr	r1, _03800FF4	; =_038099A8
	str	r2, [r1]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03800FE8:	.word	0x027FFC10
_03800FEC:	.word	0x027FF800
_03800FF0:	.word	0x027FFC00
_03800FF4:	.word	_038099A8

	arm_func_start CARD_IsPulledOut
CARD_IsPulledOut: ; 0x03800FF8
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _03801040	; =_038099A8
	ldr	r0, [r0]
	cmp	r0, #0
	bne	_0380102C
	ldr	r0, _03801044	; =0x027FFC1F
	ldrb	r0, [r0]
	ands	r0, r0, #1
	beq	_03801028
	bl	CARD_CompareCardID
	b	_0380102C
_03801028:
	bl	CARD_IsCardIreqLo
_0380102C:
	ldr	r0, _03801040	; =_038099A8
	ldr	r0, [r0]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03801040:	.word	_038099A8
_03801044:	.word	0x027FFC1F

	arm_func_start FUN_03801048
FUN_03801048: ; 0x03801048
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	and	r0, r1, #63	; 0x3f
	cmp	r0, #1
	bne	_03801064
	bl	FUN_03800E54
	b	_03801068
_03801064:
	bl	OS_Terminate
_03801068:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start CARD_InitPulledOutCallback
CARD_InitPulledOutCallback: ; 0x03801074
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	ldr	r0, _038010CC	; =_038099A4
	ldr	r1, [r0]
	cmp	r1, #0
	bne	_038010C0
	mov	r1, #1
	str	r1, [r0]
	bl	PXI_Init
	mov	r5, #14
	mov	r4, #0
_038010A0:
	mov	r0, r5
	mov	r1, r4
	bl	PXI_IsCallbackReady
	cmp	r0, #0
	beq	_038010A0
	mov	r0, #14
	ldr	r1, _038010D0	; =FUN_03801048
	bl	PXI_SetFifoRecvCallback
_038010C0:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_038010CC:	.word	_038099A4
_038010D0:	.word	FUN_03801048
