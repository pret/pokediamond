	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start FUN_037F8000
FUN_037F8000: ; 0x037F8000
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037F8028	; =PMi_Initialized
	ldr	r0, [r0]
	cmp	r0, #0
	beq	_037F801C
	bl	PM_SelfBlinkProc
_037F801C:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037F8028:	.word	PMi_Initialized

	arm_func_start FUN_037F802C
FUN_037F802C: ; 0x037F802C
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	r8, #0
	bl	FUN_037F81E8
	cmp	r0, #0
	beq	_037F80F8
	bl	FUN_037F81C4
	mov	r7, r0
	mov	r9, r8
	mov	r4, #1
	mov	fp, #138	; 0x8a
	mov	r5, #112	; 0x70
_037F8060:
	add	r6, sl, r9, lsl #8
	ldr	r0, _037F81B4	; =0x0000FFFF
	mov	r1, r6
	mov	r2, r5
	bl	FUN_037F81B8
	mov	r2, r6
	ldrh	r1, [r2, #114]	; 0x72
	cmp	r0, r1
	bne	_037F80E0
	ldrh	r0, [r2, #112]	; 0x70
	cmp	r0, #128	; 0x80
	bcs	_037F80E0
	ldr	r0, _037F81B4	; =0x0000FFFF
	add	r1, r6, #116	; 0x74
	mov	r2, fp
	bl	FUN_037F81B8
	mov	r3, r6
	ldrh	r1, [r3, #254]	; 0xfe
	cmp	r0, r1
	bne	_037F80E0
	ldrh	r2, [r3, #118]	; 0x76
	ldrb	r0, [r3, #117]	; 0x75
	mov	r1, r4, lsl r0
	ands	r1, r1, r2
	beq	_037F80E0
	ands	r1, r7, r2
	ldrneh	r1, [r6, #100]	; 0x64
	bicne	r1, r1, #7
	andne	r0, r0, #7
	orrne	r0, r1, r0
	strneh	r0, [r6, #100]	; 0x64
	orr	r8, r8, r4, lsl r9
_037F80E0:
	add	r0, r9, #1
	mov	r0, r0, lsl #16
	mov	r9, r0, lsr #16
	cmp	r9, #2
	bcc	_037F8060
	b	_037F8158
_037F80F8:
	bl	FUN_037F81C4
	cmp	r0, #0
	movne	r0, #3
	bne	_037F81A8
	mov	r7, r8
	mov	r4, #1
	ldr	r6, _037F81B4	; =0x0000FFFF
	mov	r5, #112	; 0x70
_037F8118:
	mov	r0, r6
	add	r1, sl, r7, lsl #8
	mov	r2, r5
	bl	FUN_037F81B8
	add	r2, sl, r7, lsl #8
	ldrh	r1, [r2, #114]	; 0x72
	cmp	r0, r1
	bne	_037F8144
	ldrh	r0, [r2, #112]	; 0x70
	cmp	r0, #128	; 0x80
	orrcc	r8, r8, r4, lsl r7
_037F8144:
	add	r0, r7, #1
	mov	r0, r0, lsl #16
	mov	r7, r0, lsr #16
	cmp	r7, #2
	bcc	_037F8118
_037F8158:
	cmp	r8, #1
	beq	_037F8174
	cmp	r8, #2
	beq	_037F8174
	cmp	r8, #3
	beq	_037F817C
	b	_037F81A4
_037F8174:
	mov	r0, r8
	b	_037F81A8
_037F817C:
	ldrh	r0, [sl, #112]	; 0x70
	add	r0, r0, #1
	and	r0, r0, #127	; 0x7f
	and	r1, r0, #255	; 0xff
	add	r0, sl, #256	; 0x100
	ldrh	r0, [r0, #112]	; 0x70
	cmp	r1, r0
	moveq	r0, #2
	movne	r0, #1
	b	_037F81A8
_037F81A4:
	mov	r0, #0
_037F81A8:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037F81B4:	.word	0x0000FFFF

	arm_func_start FUN_037F81B8
FUN_037F81B8: ; 0x037F81B8
	ldr	ip, _037F81C0	; =SVC_GetCRC16
	bx	ip
_037F81C0:	.word	SVC_GetCRC16

	arm_func_start FUN_037F81C4
FUN_037F81C4: ; 0x037F81C4
	mov	r0, #0
	ldr	r1, _037F81E4	; =0x027FFE1D
	ldrb	r1, [r1]
	cmp	r1, #128	; 0x80
	orreq	r0, r0, #64	; 0x40
	moveq	r0, r0, lsl #16
	moveq	r0, r0, lsr #16
	bx	lr
_037F81E4:	.word	0x027FFE1D

	arm_func_start FUN_037F81E8
FUN_037F81E8: ; 0x037F81E8
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #29
	mov	r1, #1
	add	r2, sp, #0
	bl	NVRAM_ReadDataBytes
	ldrb	r0, [sp]
	cmp	r0, #255	; 0xff
	moveq	r0, #0
	beq	_037F821C
	ands	r0, r0, #64	; 0x40
	movne	r0, #1
	moveq	r0, #0
_037F821C:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start FUN_037F8228
FUN_037F8228: ; 0x037F8228
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #528	; 0x210
	mov	r0, #32
	mov	r1, #2
	add	r2, sp, #4
	bl	NVRAM_ReadDataBytes
	ldr	r0, [sp, #4]
	mov	r0, r0, lsl #3
	str	r0, [sp, #4]
	mov	r1, #256	; 0x100
	add	r2, sp, #16
	bl	NVRAM_ReadDataBytes
	ldr	r0, [sp, #4]
	add	r0, r0, #256	; 0x100
	mov	r1, #256	; 0x100
	add	r2, sp, #272	; 0x110
	bl	NVRAM_ReadDataBytes
	add	r0, sp, #16
	bl	FUN_037F802C
	cmp	r0, #3
	blt	_037F8290
	mvn	r0, #0
	ldr	r1, _037F83A4	; =0x027FFC80
	mov	r2, #116	; 0x74
	bl	MIi_CpuClear32
	b	_037F834C
_037F8290:
	cmp	r0, #0
	beq	_037F833C
	mov	r2, r0, lsl #8
	ldr	r1, _037F83A8	; =0xFFFFFF2A
	add	r1, sp, r1
	ldrb	r1, [r1, r0, lsl #8]
	cmp	r1, #10
	bcs	_037F82DC
	mov	ip, #10
	mov	r3, #0
	add	r1, sp, #16
	add	r2, r1, r2
	b	_037F82D0
_037F82C4:
	add	r1, r2, ip, lsl #1
	strh	r3, [r1, #-252]	; 0xffffff04
	sub	ip, ip, #1
_037F82D0:
	ldrb	r1, [r2, #-230]	; 0xffffff1a
	cmp	ip, r1
	bgt	_037F82C4
_037F82DC:
	mov	r2, r0, lsl #8
	ldr	r1, _037F83AC	; =0xFFFFFF60
	add	r1, sp, r1
	ldrb	r1, [r1, r0, lsl #8]
	cmp	r1, #26
	bcs	_037F8320
	mov	ip, #26
	mov	r3, #0
	add	r1, sp, #16
	add	r2, r1, r2
	b	_037F8314
_037F8308:
	add	r1, r2, ip, lsl #1
	strh	r3, [r1, #-230]	; 0xffffff1a
	sub	ip, ip, #1
_037F8314:
	ldrb	r1, [r2, #-176]	; 0xffffff50
	cmp	ip, r1
	bgt	_037F8308
_037F8320:
	add	r1, sp, #16
	sub	r0, r0, #1
	add	r0, r1, r0, lsl #8
	ldr	r1, _037F83A4	; =0x027FFC80
	mov	r2, #116	; 0x74
	bl	MIi_CpuCopy32
	b	_037F834C
_037F833C:
	mov	r0, #0
	ldr	r1, _037F83A4	; =0x027FFC80
	mov	r2, #116	; 0x74
	bl	MIi_CpuClear32
_037F834C:
	mov	r0, #54	; 0x36
	mov	r1, #6
	add	r2, sp, #8
	bl	NVRAM_ReadDataBytes
	ldr	r0, _037F83A4	; =0x027FFC80
	add	r4, r0, #116	; 0x74
	add	r0, sp, #8
	mov	r1, r4
	mov	r2, #6
	bl	MI_CpuCopy8
	mov	r0, #60	; 0x3c
	mov	r1, #2
	add	r2, sp, #0
	bl	NVRAM_ReadDataBytes
	ldrh	r0, [sp]
	mov	r0, r0, lsl #15
	mov	r0, r0, lsr #16
	bl	WMSP_GetAllowedChannel
	strh	r0, [r4, #6]
	add	sp, sp, #528	; 0x210
	ldmia	sp!, {r4, lr}
	bx	lr
_037F83A4:	.word	0x027FFC80
_037F83A8:	.word	0xFFFFFF2A
_037F83AC:	.word	0xFFFFFF60

	arm_func_start FUN_037F83B0
FUN_037F83B0: ; 0x037F83B0
	stmdb	sp!, {r4, lr}
	mov	r0, #8
	bl	OS_GetArenaHi
	mov	r4, r0
	mov	r0, #8
	bl	OS_GetArenaLo
	mov	r1, r0
	mov	r0, #8
	mov	r2, r4
	mov	r3, #1
	bl	OS_InitAlloc
	mov	r4, r0
	mov	r0, #8
	bl	OS_GetArenaHi
	mov	r2, r0
	mov	r0, r4
	mov	r1, #0
	sub	r2, r2, r4
	bl	MI_CpuFill8
	mov	r0, #8
	mov	r1, r4
	bl	OS_SetArenaLo
	mov	r0, #8
	bl	OS_GetArenaHi
	mov	r4, r0
	mov	r0, #8
	bl	OS_GetArenaLo
	mov	r1, r0
	mov	r0, #8
	mov	r2, r4
	bl	OS_CreateHeap
	movs	r4, r0
	bpl	_037F8438
	bl	FUN_037FB1F0
_037F8438:
	mov	r0, #8
	mov	r1, r4
	bl	OS_SetCurrentHeap
	mov	r0, #8
	mov	r1, r4
	bl	OS_CheckHeap
	cmp	r0, #8448	; 0x2100
	bcs	_037F845C
	bl	FUN_037FB1F0
_037F845C:
	mov	r0, r4
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start NitroSpMain
NitroSpMain: ; 0x037F8468
	stmdb	sp!, {r4, lr}
	bl	WVR_ShelterExtWram
	bl	OS_Init
	bl	OS_InitThread
	bl	FUN_037F8228
	bl	PXI_Init
	bl	FUN_037F83B0
	mov	r4, r0
	mov	r0, #6
	bl	SND_Init
	bl	PAD_InitXYButton
	mov	r0, #1
	ldr	r1, _037F8524	; =FUN_037F8000
	bl	OS_SetIrqFunction
	mov	r0, #1
	bl	OS_EnableIrqMask
	ldr	r1, _037F8528	; =0x04000004
	ldrh	r0, [r1]
	ldrh	r0, [r1]
	orr	r0, r0, #8
	strh	r0, [r1]
	ldr	r1, _037F852C	; =0x04000208
	ldrh	r0, [r1]
	mov	r0, #1
	strh	r0, [r1]
	bl	OS_EnableInterrupts
	mvn	r0, #0
	bl	FS_Init
	mov	r0, #15
	bl	CARD_SetThreadPriority
	mov	r0, #12
	bl	RTC_Init
	mov	r0, r4
	bl	WVR_Init
	mov	r0, #2
	bl	SPI_Init
	mov	r4, #0
_037F84FC:
	bl	FUN_037F8530
	bl	OS_IsResetOccurred
	cmp	r0, #0
	beq	_037F8518
	mov	r0, r4
	bl	CTRDG_VibPulseEdgeUpdate
	bl	OS_ResetSystem
_037F8518:
	bl	CTRDG_CheckPullOut_Polling
	bl	CARD_CheckPullOut_Polling
	b	_037F84FC
_037F8524:	.word	FUN_037F8000
_037F8528:	.word	0x04000004
_037F852C:	.word	0x04000208

	arm_func_start FUN_037F8530
FUN_037F8530: ; 0x037F8530
	ldr	ip, _037F8538	; =SVC_Halt
	bx	ip
_037F8538:	.word	SVC_Halt
