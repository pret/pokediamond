	.include "asm/macros.inc"
	.include "global.inc"

	.section .text
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

	arm_func_start OS_IrqHandler
OS_IrqHandler: ; 0x037F853C
	stmfd	sp!, {lr}
	mov	ip, #67108864	; 0x4000000
	add	ip, ip, #528	; 0x210
	ldr	r1, [ip, #-8]
	cmp	r1, #0
	ldmeqfd	sp!, {pc}
	ldmia	ip, {r1, r2}
	ands	r1, r1, r2
	ldmeqfd	sp!, {pc}
	mov	r3, #1
	mov	r0, #0
_037F8568:
	ands	r2, r1, r3, lsl r0
	addeq	r0, r0, #1
	beq	_037F8568
	str	r2, [ip, #4]
	ldr	r1, _037F8588	; =OS_IRQTable
	ldr	r0, [r1, r0, lsl #2]
	ldr	lr, _037F858C	; =OS_IrqHandler_ThreadSwitch
	bx	r0
_037F8588:	.word	OS_IRQTable
_037F858C:	.word	OS_IrqHandler_ThreadSwitch

	arm_func_start OS_IrqHandler_ThreadSwitch
OS_IrqHandler_ThreadSwitch:
	ldr	ip, _037F86AC	; =OSi_IrqThreadQueue
	mov	r3, #0
	ldr	ip, [ip]
	mov	r2, #1
	cmp	ip, #0
	beq	_037F85E0
_037F85A8:
	str	r2, [ip, #72]	; 0x48
	str	r3, [ip, #92]	; 0x5c
	str	r3, [ip, #96]	; 0x60
	ldr	r0, [ip, #100]	; 0x64
	str	r3, [ip, #100]	; 0x64
	mov	ip, r0
	cmp	ip, #0
	bne	_037F85A8
	ldr	ip, _037F86AC	; =OSi_IrqThreadQueue
	str	r3, [ip]
	str	r3, [ip, #4]
	ldr	ip, _037F86B0	; =OSi_ThreadInfo
	mov	r1, #1
	strh	r1, [ip]
_037F85E0:
	ldr	ip, _037F86B0	; =OSi_ThreadInfo
	ldrh	r1, [ip]
	cmp	r1, #0
	ldreq	pc, [sp], #4		; (ldreq pc, [sp], #4)
	mov	r1, #0
	strh	r1, [ip]
	mov	r3, #210	; 0xd2
	msr	CPSR_c, r3
	add	r2, ip, #8
	ldr	r1, [r2]
_037F8608:
	cmp	r1, #0
	ldrneh	r0, [r1, #72]	; 0x48
	cmpne	r0, #1
	ldrne	r1, [r1, #76]	; 0x4c
	bne	_037F8608
	cmp	r1, #0
	bne	_037F8630
_037F8624:
	mov	r3, #146	; 0x92
	msr	CPSR_c, r3
	ldr pc, [sp], #4
_037F8630:
	ldr	r0, [ip, #4]
	cmp	r1, r0
	beq	_037F8624
	ldr	r3, [ip, #12]
	cmp	r3, #0
	beq	_037F8658

	arm_func_start FUN_037F8648
FUN_037F8648: ; 0x037F8648
	stmdb	sp!, {r0, r1, ip}
	mov	lr, pc
	bx	r3
	ldmia	sp!, {r0, r1, ip}
_037F8658:
	str	r1, [ip, #4]
	mrs	r2, SPSR
	str	r2, [r0, #0]!
	ldmib	sp!, {r2, r3}
	stmib	r0!, {r2, r3}
	ldmib	sp!, {r2, r3, ip, lr}
	stmib	r0!, {r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
	stmib	r0!, {lr}
	mov	r3, #211	; 0xd3
	msr	CPSR_c, r3
	stmib	r0!, {sp}
	ldr	sp, [r1, #68]	; 0x44
	mov	r3, #210	; 0xd2
	msr	CPSR_c, r3
	ldr	r2, [r1, #0]!
	msr	SPSR_fc, r2
	ldr	lr, [r1, #64]	; 0x40
	ldmib	r1!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
	nop			; (mov r0, r0)
	stmda	sp!, {r0, r1, r2, r3, ip, lr}
	ldmia	sp!, {pc}
_037F86AC:	.word	OSi_IrqThreadQueue
_037F86B0:	.word	OSi_ThreadInfo

	arm_func_start OSi_IrqVBlank
OSi_IrqVBlank: ; 0x037F86B4
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037F8700	; =OSi_IrqCallbackInfo
	ldr	r2, [r0, #96]	; 0x60
	ldr	r1, _037F8704	; =0x027FFC3C
	ldr	r0, [r1]
	add	r0, r0, #1
	str	r0, [r1]
	cmp	r2, #0
	beq	_037F86E4
	mov	lr, pc
	bx	r2
_037F86E4:
	ldr	r1, _037F8708	; =0x0380FFF8
	ldr	r0, [r1]
	orr	r0, r0, #1
	str	r0, [r1]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037F8700:	.word	OSi_IrqCallbackInfo
_037F8704:	.word	0x027FFC3C
_037F8708:	.word	0x0380FFF8

	arm_func_start OSi_IrqTimer3
OSi_IrqTimer3: ; 0x037F870C
	mov	r0, #7
	ldr	ip, _037F8718	; =OSi_IrqCallback
	bx	ip
_037F8718:	.word	OSi_IrqCallback

	arm_func_start OSi_IrqTimer2
OSi_IrqTimer2: ; 0x037F871C
	mov	r0, #6
	ldr	ip, _037F8728	; =OSi_IrqCallback
	bx	ip
_037F8728:	.word	OSi_IrqCallback

	arm_func_start OSi_IrqTimer1
OSi_IrqTimer1: ; 0x037F872C
	mov	r0, #5
	ldr	ip, _037F8738	; =OSi_IrqCallback
	bx	ip
_037F8738:	.word	OSi_IrqCallback

	arm_func_start OSi_IrqTimer0
OSi_IrqTimer0: ; 0x037F873C
	mov	r0, #4
	ldr	ip, _037F8748	; =OSi_IrqCallback
	bx	ip
_037F8748:	.word	OSi_IrqCallback

	arm_func_start OSi_IrqDma3
OSi_IrqDma3: ; 0x037F874C
	mov	r0, #3
	ldr	ip, _037F8758	; =OSi_IrqCallback
	bx	ip
_037F8758:	.word	OSi_IrqCallback

	arm_func_start OSi_IrqDma2
OSi_IrqDma2: ; 0x037F875C
	mov	r0, #2
	ldr	ip, _037F8768	; =OSi_IrqCallback
	bx	ip
_037F8768:	.word	OSi_IrqCallback

	arm_func_start OSi_IrqDma1
OSi_IrqDma1: ; 0x037F876C
	mov	r0, #1
	ldr	ip, _037F8778	; =OSi_IrqCallback
	bx	ip
_037F8778:	.word	OSi_IrqCallback

	arm_func_start OSi_IrqDma0
OSi_IrqDma0: ; 0x037F877C
	mov	r0, #0
	ldr	ip, _037F8788	; =OSi_IrqCallback
	bx	ip
_037F8788:	.word	OSi_IrqCallback

	arm_func_start OSi_IrqCallback
OSi_IrqCallback: ; 0x037F878C
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r3, #1
	mov	r2, r0, lsl #1
	ldr	r1, _037F880C	; =_038075E4
	ldrh	r1, [r1, r2]
	mov	r5, r3, lsl r1
	mov	r1, #12
	mul	r4, r0, r1
	ldr	r2, _037F8810	; =OSi_IrqCallbackInfo
	ldr	r1, [r2, r4]
	mov	r0, #0
	str	r0, [r2, r4]
	cmp	r1, #0
	beq	_037F87D8
	ldr	r0, _037F8814	; =_0380771C
	ldr	r0, [r0, r4]
	mov	lr, pc
	bx	r1
_037F87D8:
	ldr	r1, _037F8818	; =0x0380FFF8
	ldr	r0, [r1]
	orr	r0, r0, r5
	str	r0, [r1]
	ldr	r0, _037F881C	; =_03807718
	ldr	r0, [r0, r4]
	cmp	r0, #0
	bne	_037F8800
	mov	r0, r5
	bl	OS_DisableIrqMask
_037F8800:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037F880C:	.word	_038075E4
_037F8810:	.word	OSi_IrqCallbackInfo
_037F8814:	.word	_0380771C
_037F8818:	.word	0x0380FFF8
_037F881C:	.word	_03807718

	arm_func_start OS_IrqDummy
OS_IrqDummy: ; 0x037F8820
	bx	lr

	arm_func_start OS_ResetRequestIrqMask
OS_ResetRequestIrqMask: ; 0x037F8824
	ldr	ip, _037F8850	; =0x04000208
	ldrh	r3, [ip]
	mov	r1, #0
	strh	r1, [ip]
	ldr	r2, _037F8854	; =0x04000214
	ldr	r1, [r2]
	str	r0, [r2]
	ldrh	r0, [ip]
	strh	r3, [ip]
	mov	r0, r1
	bx	lr
_037F8850:	.word	0x04000208
_037F8854:	.word	0x04000214

	arm_func_start OS_DisableIrqMask
OS_DisableIrqMask: ; 0x037F8858
	ldr	ip, _037F888C	; =0x04000208
	ldrh	r3, [ip]
	mov	r1, #0
	strh	r1, [ip]
	ldr	r2, _037F8890	; =0x04000210
	ldr	r1, [r2]
	mvn	r0, r0
	and	r0, r1, r0
	str	r0, [r2]
	ldrh	r0, [ip]
	strh	r3, [ip]
	mov	r0, r1
	bx	lr
_037F888C:	.word	0x04000208
_037F8890:	.word	0x04000210

	arm_func_start OS_EnableIrqMask
OS_EnableIrqMask: ; 0x037F8894
	ldr	ip, _037F88C4	; =0x04000208
	ldrh	r3, [ip]
	mov	r1, #0
	strh	r1, [ip]
	ldr	r2, _037F88C8	; =0x04000210
	ldr	r1, [r2]
	orr	r0, r1, r0
	str	r0, [r2]
	ldrh	r0, [ip]
	strh	r3, [ip]
	mov	r0, r1
	bx	lr
_037F88C4:	.word	0x04000208
_037F88C8:	.word	0x04000210

	arm_func_start OS_SetIrqMask
OS_SetIrqMask: ; 0x037F88CC
	ldr	ip, _037F88F8	; =0x04000208
	ldrh	r3, [ip]
	mov	r1, #0
	strh	r1, [ip]
	ldr	r2, _037F88FC	; =0x04000210
	ldr	r1, [r2]
	str	r0, [r2]
	ldrh	r0, [ip]
	strh	r3, [ip]
	mov	r0, r1
	bx	lr
_037F88F8:	.word	0x04000208
_037F88FC:	.word	0x04000210

	arm_func_start OSi_EnterTimerCallback
OSi_EnterTimerCallback: ; 0x037F8900
	stmdb	sp!, {r4, lr}
	mov	r3, #12
	mul	r4, r0, r3
	ldr	r3, _037F8940	; =_03807744
	str	r1, [r3, r4]
	ldr	r1, _037F8944	; =_0380774C
	str	r2, [r1, r4]
	mov	r1, #1
	add	r0, r0, #3
	mov	r0, r1, lsl r0
	bl	OS_EnableIrqMask
	mov	r1, #1
	ldr	r0, _037F8948	; =_03807748
	str	r1, [r0, r4]
	ldmia	sp!, {r4, lr}
	bx	lr
_037F8940:	.word	_03807744
_037F8944:	.word	_0380774C
_037F8948:	.word	_03807748

	arm_func_start OS_SetIrqFunction
OS_SetIrqFunction: ; 0x037F894C
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r9, #0
	mov	r7, r9
	ldr	lr, _037F89E8	; =OS_IRQTable
	ldr	r4, _037F89EC	; =_03807774
	ldr	r6, _037F89F0	; =OSi_IrqCallbackInfo
	mov	ip, r9
	mov	r3, #1
	mov	r2, #12
_037F8974:
	ands	r5, r0, #1
	beq	_037F89CC
	mov	r8, r7
	cmp	r9, #8
	blt	_037F8998
	cmp	r9, #11
	suble	r5, r9, #8
	mlale	r8, r5, r2, r6
	ble	_037F89BC
_037F8998:
	cmp	r9, #3
	blt	_037F89B0
	cmp	r9, #6
	addle	r5, r9, #1
	mlale	r8, r5, r2, r6
	ble	_037F89BC
_037F89B0:
	cmp	r9, #0
	moveq	r8, r4
	strne	r1, [lr, r9, lsl #2]
_037F89BC:
	cmp	r8, #0
	strne	r1, [r8]
	strne	ip, [r8, #8]
	strne	r3, [r8, #4]
_037F89CC:
	mov	r0, r0, lsr #1
	add	r9, r9, #1
	cmp	r9, #25
	blt	_037F8974
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037F89E8:	.word	OS_IRQTable
_037F89EC:	.word	_03807774
_037F89F0:	.word	OSi_IrqCallbackInfo

	arm_func_start OS_InitIrqTable
OS_InitIrqTable: ; 0x037F89F4
	mov	r1, #0
	ldr	r0, _037F8A10	; =OSi_IrqThreadQueue
	str	r1, [r0, #4]
	str	r1, [r0]
	ldr	r0, _037F8A14	; =0x027FFC3C
	str	r1, [r0]
	bx	lr
_037F8A10:	.word	OSi_IrqThreadQueue
_037F8A14:	.word	0x027FFC3C

	arm_func_start OS_UnLockCartridge
OS_UnLockCartridge: ; 0x037F8A18
	ldr	r1, _037F8A20	; =OS_UnlockCartridge
	bx	r1
_037F8A20:	.word	OS_UnlockCartridge

	arm_func_start OS_GetLockID
OS_GetLockID: ; 0x037F8A24
	ldr	r3, _037F8AB4	; =0x027FFFB8
	ldr	r1, [r3]
	mov	r2, #0
	mov	r0, #-2147483648	; 0x80000000
_037F8A34:
	tst	r1, r0
	bne	_037F8A50
	add	r2, r2, #1
	cmp	r2, #32
	beq	_037F8A50
	mov	r0, r0, lsr #1
	b	_037F8A34
_037F8A50:
	cmp	r2, #32
	movne	r0, #128	; 0x80
	bne	_037F8A98
	add	r3, r3, #4
	ldr	r1, [r3]
	mov	r2, #0
	mov	r0, #-2147483648	; 0x80000000
_037F8A6C:
	tst	r1, r0
	bne	_037F8A88
	add	r2, r2, #1
	cmp	r2, #32
	beq	_037F8A88
	mov	r0, r0, lsr #1
	b	_037F8A6C
_037F8A88:
	cmp	r2, #32
	ldr	r0, _037F8AB8	; =0xFFFFFFFD
	bxeq	lr
	mov	r0, #160	; 0xa0
_037F8A98:
	add	r0, r0, r2
	mov	r1, #-2147483648	; 0x80000000
	mov	r1, r1, lsr r2
	ldr	r2, [r3]
	bic	r2, r2, r1
	str	r2, [r3]
	bx	lr
_037F8AB4:	.word	0x027FFFB8
_037F8AB8:	.word	0xFFFFFFFD

	arm_func_start OS_ReleaseLockID
OS_ReleaseLockID: ; 0x037F8ABC
	ldr	r3, _037F8AE8	; =0x027FFFB8
	cmp	r0, #160	; 0xa0
	addpl	r3, r3, #4
	subpl	r0, r0, #160	; 0xa0
	submi	r0, r0, #128	; 0x80
	mov	r1, #-2147483648	; 0x80000000
	mov	r1, r1, lsr r0
	ldr	r2, [r3]
	orr	r2, r2, r1
	str	r2, [r3]
	bx	lr
_037F8AE8:	.word	0x027FFFB8

	arm_func_start OS_ReadOwnerOfLockWord
OS_ReadOwnerOfLockWord: ; 0x037F8AEC
	ldrh	r0, [r0, #4]
	bx	lr
_037F8AF4:
	bx	lr
_037F8AF8:
	bx	lr

	arm_func_start OS_TryLockCartridge
OS_TryLockCartridge: ; 0x037F8AFC
	ldr	r1, _037F8B10	; =0x027FFFE8
	ldr	r2, _037F8B14	; =_037F8AF8
	mov	r3, #1
	ldr	ip, _037F8B18	; =FUN_037F8B5C
	bx	ip
_037F8B10:	.word	0x027FFFE8
_037F8B14:	.word	_037F8AF8
_037F8B18:	.word	FUN_037F8B5C

	arm_func_start OS_UnlockCartridge
OS_UnlockCartridge: ; 0x037F8B1C
	ldr	r1, _037F8B30	; =0x027FFFE8
	ldr	r2, _037F8B34	; =_037F8AF4
	mov	r3, #1
	ldr	ip, _037F8B38	; =FUN_037F8BE0
	bx	ip
_037F8B30:	.word	0x027FFFE8
_037F8B34:	.word	_037F8AF4
_037F8B38:	.word	FUN_037F8BE0

	arm_func_start OS_LockCartridge
OS_LockCartridge: ; 0x037F8B3C
	ldr	r1, _037F8B50	; =0x027FFFE8
	ldr	r2, _037F8B54	; =_037F8AF8
	mov	r3, #1
	ldr	ip, _037F8B58	; =FUN_037F8C6C
	bx	ip
_037F8B50:	.word	0x027FFFE8
_037F8B54:	.word	_037F8AF8
_037F8B58:	.word	FUN_037F8C6C

	arm_func_start FUN_037F8B5C
FUN_037F8B5C: ; 0x037F8B5C
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r9, r0
	mov	r8, r1
	mov	r7, r2
	movs	r6, r3
	beq	_037F8B84
	bl	OS_DisableInterrupts_IrqAndFiq
	mov	r5, r0
	b	_037F8B8C
_037F8B84:
	bl	OS_DisableInterrupts
	mov	r5, r0
_037F8B8C:
	mov	r0, r9
	mov	r1, r8
	bl	MI_SwapWord
	movs	r4, r0
	bne	_037F8BB4
	cmp	r7, #0
	beq	_037F8BB0
	mov	lr, pc
	bx	r7
_037F8BB0:
	strh	r9, [r8, #4]
_037F8BB4:
	cmp	r6, #0
	beq	_037F8BC8
	mov	r0, r5
	bl	OS_RestoreInterrupts_IrqAndFiq
	b	_037F8BD0
_037F8BC8:
	mov	r0, r5
	bl	OS_RestoreInterrupts
_037F8BD0:
	mov	r0, r4
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr

	arm_func_start FUN_037F8BE0
FUN_037F8BE0: ; 0x037F8BE0
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r1
	mov	r6, r2
	mov	r5, r3
	ldrh	r1, [r7, #4]
	cmp	r0, r1
	mvnne	r0, #1
	bne	_037F8C60
	cmp	r5, #0
	beq	_037F8C18
	bl	OS_DisableInterrupts_IrqAndFiq
	mov	r4, r0
	b	_037F8C20
_037F8C18:
	bl	OS_DisableInterrupts
	mov	r4, r0
_037F8C20:
	mov	r0, #0
	strh	r0, [r7, #4]
	cmp	r6, #0
	beq	_037F8C38
	mov	lr, pc
	bx	r6
_037F8C38:
	mov	r0, #0
	str	r0, [r7]
	cmp	r5, #0
	beq	_037F8C54
	mov	r0, r4
	bl	OS_RestoreInterrupts_IrqAndFiq
	b	_037F8C5C
_037F8C54:
	mov	r0, r4
	bl	OS_RestoreInterrupts
_037F8C5C:
	mov	r0, #0
_037F8C60:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr

	arm_func_start FUN_037F8C6C
FUN_037F8C6C: ; 0x037F8C6C
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r8, r0
	mov	r7, r1
	mov	r6, r2
	mov	r5, r3
	mov	r4, #1024	; 0x400
	b	_037F8C90
_037F8C88:
	mov	r0, r4
	bl	FUN_037F8CB4
_037F8C90:
	mov	r0, r8
	mov	r1, r7
	mov	r2, r6
	mov	r3, r5
	bl	FUN_037F8B5C
	cmp	r0, #0
	bgt	_037F8C88
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr

	arm_func_start FUN_037F8CB4
FUN_037F8CB4: ; 0x037F8CB4
	ldr	ip, _037F8CBC	; =SVC_WaitByLoop
	bx	ip
_037F8CBC:	.word	SVC_WaitByLoop

	arm_func_start OS_InitLock
OS_InitLock: ; 0x037F8CC0
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	ldr	r0, _037F8D38	; =_03807780
	ldr	r1, [r0]
	cmp	r1, #0
	bne	_037F8D2C
	mov	r1, #1
	str	r1, [r0]
	mov	r0, #0
	ldr	r4, _037F8D3C	; =0x027FFFF0
	strh	r0, [r4, #6]
	mov	r5, #1024	; 0x400
	b	_037F8CFC
_037F8CF4:
	mov	r0, r5
	bl	FUN_037F8CB4
_037F8CFC:
	ldrh	r0, [r4, #4]
	cmp	r0, #127	; 0x7f
	bne	_037F8CF4
	mvn	r1, #0
	ldr	r0, _037F8D40	; =0x027FFFB8
	str	r1, [r0]
	mov	r0, #65536	; 0x10000
	rsb	r1, r0, #0
	ldr	r0, _037F8D44	; =0x027FFFBC
	str	r1, [r0]
	mov	r0, #191	; 0xbf
	strh	r0, [r4, #6]
_037F8D2C:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037F8D38:	.word	_03807780
_037F8D3C:	.word	0x027FFFF0
_037F8D40:	.word	0x027FFFB8
_037F8D44:	.word	0x027FFFBC

	arm_func_start OS_SetThreadDestructor
OS_SetThreadDestructor: ; 0x037F8D48
	str	r1, [r0, #152]	; 0x98
	bx	lr

	arm_func_start OS_EnableScheduler
OS_EnableScheduler: ; 0x037F8D50
	stmdb	sp!, {r4, lr}
	bl	OS_DisableInterrupts
	mov	r4, #0
	ldr	r1, _037F8D84	; =OSi_RescheduleCount
	ldr	r3, [r1]
	cmp	r3, #0
	subne	r2, r3, #1
	strne	r2, [r1]
	movne	r4, r3
	bl	OS_RestoreInterrupts
	mov	r0, r4
	ldmia	sp!, {r4, lr}
	bx	lr
_037F8D84:	.word	OSi_RescheduleCount

	arm_func_start OS_DisableScheduler
OS_DisableScheduler: ; 0x037F8D88
	stmdb	sp!, {r4, lr}
	bl	OS_DisableInterrupts
	ldr	r2, _037F8DBC	; =OSi_RescheduleCount
	ldr	r3, [r2]
	mvn	r1, #0
	cmp	r3, r1
	addcc	r1, r3, #1
	strcc	r1, [r2]
	movcc	r4, r3
	bl	OS_RestoreInterrupts
	mov	r0, r4
	ldmia	sp!, {r4, lr}
	bx	lr
_037F8DBC:	.word	OSi_RescheduleCount

	arm_func_start OS_SetSwitchThreadCallback
OS_SetSwitchThreadCallback: ; 0x037F8DC0
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	bl	OS_DisableInterrupts
	ldr	r1, _037F8DF0	; =OSi_ThreadInfo
	ldr	r4, [r1, #12]
	str	r5, [r1, #12]
	bl	OS_RestoreInterrupts
	mov	r0, r4
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037F8DF0:	.word	OSi_ThreadInfo
_037F8DF4:
	ldr	r2, [r0]
	mov	r1, #0
	str	r1, [r0]
	str	r1, [r2, #148]	; 0x94
	mov	r0, r2
	ldr	ip, _037F8E10	; =OS_WakeupThreadDirect
	bx	ip
_037F8E10:	.word	OS_WakeupThreadDirect

	arm_func_start OS_Sleep
OS_Sleep: ; 0x037F8E14
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #52	; 0x34
	mov	r5, r0
	add	r0, sp, #8
	bl	OS_CreateAlarm
	ldr	r0, _037F8EAC	; =OSi_CurrentThreadPtr
	ldr	r0, [r0]
	ldr	r0, [r0]
	str	r0, [sp, #4]
	bl	OS_DisableInterrupts
	mov	r4, r0
	add	r0, sp, #8
	ldr	r1, [sp, #4]
	str	r0, [r1, #148]	; 0x94
	add	r1, sp, #4
	str	r1, [sp]
	mov	r2, #0
	ldr	r1, _037F8EB0	; =0x000082EA
	umull	ip, r3, r5, r1
	mla	r3, r5, r2, r3
	mla	r3, r2, r1, r3
	mov	r2, r3, lsr #6
	mov	r1, ip, lsr #6
	orr	r1, r1, r3, lsl #26
	ldr	r3, _037F8EB4	; =_037F8DF4
	bl	OS_SetAlarm
	mov	r5, #0
	b	_037F8E8C
_037F8E84:
	mov	r0, r5
	bl	OS_SleepThread
_037F8E8C:
	ldr	r0, [sp, #4]
	cmp	r0, #0
	bne	_037F8E84
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #52	; 0x34
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037F8EAC:	.word	OSi_CurrentThreadPtr
_037F8EB0:	.word	0x000082EA
_037F8EB4:	.word	_037F8DF4

	arm_func_start OS_SetThreadPriority
OS_SetThreadPriority: ; 0x037F8EB8
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r6, r0
	mov	r5, r1
	ldr	r0, _037F8F60	; =OSi_ThreadInfo
	ldr	r8, [r0, #8]
	mov	r7, #0
	bl	OS_DisableInterrupts
	mov	r4, r0
	b	_037F8EE4
_037F8EDC:
	mov	r7, r8
	ldr	r8, [r8, #76]	; 0x4c
_037F8EE4:
	cmp	r8, #0
	beq	_037F8EF4
	cmp	r8, r6
	bne	_037F8EDC
_037F8EF4:
	cmp	r8, #0
	beq	_037F8F08
	ldr	r0, _037F8F64	; =OSi_IdleThread
	cmp	r8, r0
	bne	_037F8F18
_037F8F08:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #0
	b	_037F8F58
_037F8F18:
	ldr	r0, [r8, #84]	; 0x54
	cmp	r0, r5
	beq	_037F8F4C
	cmp	r7, #0
	ldreq	r1, [r6, #76]	; 0x4c
	ldreq	r0, _037F8F60	; =OSi_ThreadInfo
	streq	r1, [r0, #8]
	ldrne	r0, [r6, #76]	; 0x4c
	strne	r0, [r7, #76]	; 0x4c
	str	r5, [r6, #84]	; 0x54
	mov	r0, r6
	bl	FUN_037F9584
	bl	FUN_037F945C
_037F8F4C:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #1
_037F8F58:
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037F8F60:	.word	OSi_ThreadInfo
_037F8F64:	.word	OSi_IdleThread

	arm_func_start OS_RescheduleThread
OS_RescheduleThread: ; 0x037F8F68
	stmdb	sp!, {r4, lr}
	bl	OS_DisableInterrupts
	mov	r4, r0
	bl	FUN_037F945C
	mov	r0, r4
	bl	OS_RestoreInterrupts
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start OS_SelectThread
OS_SelectThread: ; 0x037F8F88
	ldr	r0, _037F8FB0	; =OSi_ThreadInfo
	ldr	r0, [r0, #8]
	b	_037F8F98
_037F8F94:
	ldr	r0, [r0, #76]	; 0x4c
_037F8F98:
	cmp	r0, #0
	bxeq	lr
	ldr	r1, [r0, #72]	; 0x48
	cmp	r1, #1
	bne	_037F8F94
	bx	lr
_037F8FB0:	.word	OSi_ThreadInfo

	arm_func_start OS_WakeupThreadDirect
OS_WakeupThreadDirect: ; 0x037F8FB4
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	bl	OS_DisableInterrupts
	mov	r4, r0
	mov	r0, #1
	str	r0, [r5, #72]	; 0x48
	bl	FUN_037F945C
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start OS_WakeupThread
OS_WakeupThread: ; 0x037F8FE8
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r5, r0
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r0, [r5]
	cmp	r0, #0
	beq	_037F9050
	mov	r7, #1
	mov	r6, #0
	b	_037F9030
_037F9014:
	mov	r0, r5
	bl	FUN_037F967C
	str	r7, [r0, #72]	; 0x48
	str	r6, [r0, #92]	; 0x5c
	str	r6, [r0, #100]	; 0x64
	ldr	r1, [r0, #100]	; 0x64
	str	r1, [r0, #96]	; 0x60
_037F9030:
	ldr	r0, [r5]
	cmp	r0, #0
	bne	_037F9014
	mov	r0, #0
	str	r0, [r5, #4]
	ldr	r0, [r5, #4]
	str	r0, [r5]
	bl	FUN_037F945C
_037F9050:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr

	arm_func_start OS_SleepThread
OS_SleepThread: ; 0x037F9064
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	bl	OS_DisableInterrupts
	mov	r5, r0
	ldr	r0, _037F90B4	; =OSi_CurrentThreadPtr
	ldr	r0, [r0]
	ldr	r4, [r0]
	cmp	r6, #0
	beq	_037F9098
	str	r6, [r4, #92]	; 0x5c
	mov	r0, r6
	mov	r1, r4
	bl	FUN_037F96B0
_037F9098:
	mov	r0, #0
	str	r0, [r4, #72]	; 0x48
	bl	FUN_037F945C
	mov	r0, r5
	bl	OS_RestoreInterrupts
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr
_037F90B4:	.word	OSi_CurrentThreadPtr

	arm_func_start OS_IsThreadTerminated
OS_IsThreadTerminated: ; 0x037F90B8
	ldr	r0, [r0, #72]	; 0x48
	cmp	r0, #2
	moveq	r0, #1
	movne	r0, #0
	bx	lr

	arm_func_start OS_JoinThread
OS_JoinThread: ; 0x037F90CC
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r0, [r5, #72]	; 0x48
	cmp	r0, #2
	beq	_037F90F4
	add	r0, r5, #128	; 0x80
	bl	OS_SleepThread
_037F90F4:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start FUN_037F9108
FUN_037F9108: ; 0x037F9108
	stmdb	sp!, {r4, lr}
	ldr	r0, _037F9164	; =OSi_CurrentThreadPtr
	ldr	r0, [r0]
	ldr	r4, [r0]
	bl	OS_DisableScheduler
	mov	r0, r4
	bl	OSi_UnlockAllMutex
	ldr	r0, [r4, #92]	; 0x5c
	cmp	r0, #0
	beq	_037F9138
	mov	r1, r4
	bl	FUN_037F961C
_037F9138:
	mov	r0, r4
	bl	FUN_037F953C
	mov	r0, #2
	str	r0, [r4, #72]	; 0x48
	add	r0, r4, #128	; 0x80
	bl	OS_WakeupThread
	bl	OS_EnableScheduler
	bl	OS_RescheduleThread
	bl	FUN_037FB1F0
	ldmia	sp!, {r4, lr}
	bx	lr
_037F9164:	.word	OSi_CurrentThreadPtr

	arm_func_start FUN_037F9168
FUN_037F9168: ; 0x037F9168
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _037F91AC	; =OSi_CurrentThreadPtr
	ldr	r1, [r1]
	ldr	r3, [r1]
	ldr	r2, [r3, #152]	; 0x98
	cmp	r2, #0
	beq	_037F919C
	mov	r1, #0
	str	r1, [r3, #152]	; 0x98
	mov	lr, pc
	bx	r2
	bl	OS_DisableInterrupts
_037F919C:
	bl	FUN_037F9108
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037F91AC:	.word	OSi_CurrentThreadPtr

	arm_func_start FUN_037F91B0
FUN_037F91B0: ; 0x037F91B0
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, r1
	ldr	r1, _037F9210	; =OSi_StackForDestructor
	ldr	r2, [r1]
	cmp	r2, #0
	beq	_037F91FC
	ldr	r1, _037F9214	; =FUN_037F9168
	bl	OS_InitContext
	str	r4, [r5, #4]
	ldr	r0, [r5]
	orr	r0, r0, #128	; 0x80
	str	r0, [r5]
	mov	r0, #1
	str	r0, [r5, #72]	; 0x48
	mov	r0, r5
	bl	OS_LoadContext
	b	_037F9204
_037F91FC:
	mov	r0, r4
	bl	FUN_037F9168
_037F9204:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037F9210:	.word	OSi_StackForDestructor
_037F9214:	.word	FUN_037F9168

	arm_func_start OS_ExitThread
OS_ExitThread: ; 0x037F9218
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	bl	OS_DisableInterrupts
	ldr	r0, _037F9240	; =OSi_ThreadInfo
	ldr	r0, [r0, #4]
	mov	r1, #0
	bl	FUN_037F91B0
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037F9240:	.word	OSi_ThreadInfo

	arm_func_start OS_CreateThread
OS_CreateThread: ; 0x037F9244
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r9, r0
	mov	r8, r1
	mov	r7, r2
	mov	r6, r3
	bl	OS_DisableInterrupts
	mov	r4, r0
	bl	FUN_037F9728
	ldr	r1, [sp, #36]	; 0x24
	str	r1, [r9, #84]	; 0x54
	str	r0, [r9, #80]	; 0x50
	mov	r0, #0
	str	r0, [r9, #72]	; 0x48
	str	r0, [r9, #88]	; 0x58
	mov	r0, r9
	bl	FUN_037F9584
	str	r6, [r9, #120]	; 0x78
	ldr	r0, [sp, #32]
	sub	r5, r6, r0
	str	r5, [r9, #116]	; 0x74
	mov	r2, #0
	str	r2, [r9, #124]	; 0x7c
	ldr	r1, _037F9348	; =0xD73BFDF7
	ldr	r0, [r9, #120]	; 0x78
	str	r1, [r0, #-4]
	ldr	r1, _037F934C	; =0xFBDD37BB
	ldr	r0, [r9, #116]	; 0x74
	str	r1, [r0]
	str	r2, [r9, #132]	; 0x84
	ldr	r0, [r9, #132]	; 0x84
	str	r0, [r9, #128]	; 0x80
	mov	r0, r9
	mov	r1, r8
	sub	r2, r6, #4
	bl	OS_InitContext
	str	r7, [r9, #4]
	ldr	r0, _037F9350	; =OS_ExitThread
	str	r0, [r9, #60]	; 0x3c
	mov	r0, #0
	add	r1, r5, #4
	ldr	r2, [sp, #32]
	sub	r2, r2, #8
	bl	MIi_CpuClear32
	mov	r1, #0
	str	r1, [r9, #104]	; 0x68
	str	r1, [r9, #108]	; 0x6c
	str	r1, [r9, #112]	; 0x70
	mov	r0, r9
	bl	OS_SetThreadDestructor
	mov	r0, #0
	str	r0, [r9, #92]	; 0x5c
	str	r0, [r9, #100]	; 0x64
	ldr	r1, [r9, #100]	; 0x64
	str	r1, [r9, #96]	; 0x60
	add	r1, r9, #136	; 0x88
	mov	r2, #12
	bl	MIi_CpuClear32
	mov	r0, #0
	str	r0, [r9, #148]	; 0x94
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037F9348:	.word	0xD73BFDF7
_037F934C:	.word	0xFBDD37BB
_037F9350:	.word	OS_ExitThread

	arm_func_start OS_InitThread
OS_InitThread: ; 0x037F9354
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037F942C	; =OSi_IsThreadInitialized
	ldr	r1, [r0]
	cmp	r1, #0
	bne	_037F9420
	mov	r2, #1
	str	r2, [r0]
	ldr	r1, _037F9430	; =_038077A0
	ldr	r0, _037F9434	; =OSi_CurrentThreadPtr
	str	r1, [r0]
	mov	r0, #16
	ldr	r1, _037F9438	; =OSi_LauncherThread
	str	r0, [r1, #84]	; 0x54
	mov	r0, #0
	str	r0, [r1, #80]	; 0x50
	str	r2, [r1, #72]	; 0x48
	str	r0, [r1, #76]	; 0x4c
	str	r0, [r1, #88]	; 0x58
	ldr	r0, _037F943C	; =OSi_ThreadInfo
	str	r1, [r0, #8]
	str	r1, [r0, #4]
	ldr	r2, _037F9440	; =0x00000400
	cmp	r2, #0
	ldrle	r0, _037F9444	; =FUN_037F8000
	suble	r2, r0, r2
	ldrgt	r1, _037F9448	; =0x00000400
	ldrgt	r0, _037F944C	; =0x0380FF80
	subgt	r0, r0, r1
	subgt	r2, r0, r2
	ldr	r1, _037F9448	; =0x00000400
	ldr	r0, _037F944C	; =0x0380FF80
	sub	r3, r0, r1
	ldr	r1, _037F9438	; =OSi_LauncherThread
	str	r3, [r1, #120]	; 0x78
	str	r2, [r1, #116]	; 0x74
	mov	r0, #0
	str	r0, [r1, #124]	; 0x7c
	ldr	r2, _037F9450	; =0xD73BFDF7
	str	r2, [r3, #-4]
	ldr	r3, _037F9454	; =0xFBDD37BB
	ldr	r2, [r1, #116]	; 0x74
	str	r3, [r2]
	str	r0, [r1, #132]	; 0x84
	str	r0, [r1, #128]	; 0x80
	ldr	r1, _037F943C	; =OSi_ThreadInfo
	strh	r0, [r1]
	strh	r0, [r1, #2]
	ldr	r2, _037F9458	; =0x027FFFA4
	str	r1, [r2]
	bl	OS_SetSwitchThreadCallback
_037F9420:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037F942C:	.word	OSi_IsThreadInitialized
_037F9430:	.word	_038077A0
_037F9434:	.word	OSi_CurrentThreadPtr
_037F9438:	.word	OSi_LauncherThread
_037F943C:	.word	OSi_ThreadInfo
_037F9440:	.word	0x00000400
_037F9444:	.word	FUN_037F8000
_037F9448:	.word	0x00000400
_037F944C:	.word	0x0380FF80
_037F9450:	.word	0xD73BFDF7
_037F9454:	.word	0xFBDD37BB
_037F9458:	.word	0x027FFFA4

	arm_func_start FUN_037F945C
FUN_037F945C: ; 0x037F945C
	stmdb	sp!, {r4, r5, r6, lr}
	ldr	r0, _037F952C	; =OSi_RescheduleCount
	ldr	r0, [r0]
	cmp	r0, #0
	bne	_037F9524
	ldr	r4, _037F9530	; =OSi_ThreadInfo
	ldrh	r0, [r4, #2]
	cmp	r0, #0
	bne	_037F948C
	bl	OS_GetProcMode
	cmp	r0, #18
	bne	_037F9498
_037F948C:
	mov	r0, #1
	strh	r0, [r4]
	b	_037F9524
_037F9498:
	ldr	r0, _037F9534	; =OSi_CurrentThreadPtr
	ldr	r0, [r0]
	ldr	r6, [r0]
	bl	OS_SelectThread
	mov	r5, r0
	cmp	r6, r5
	beq	_037F9524
	cmp	r5, #0
	beq	_037F9524
	ldr	r0, [r6, #72]	; 0x48
	cmp	r0, #2
	beq	_037F94D8
	mov	r0, r6
	bl	OS_SaveContext
	cmp	r0, #0
	bne	_037F9524
_037F94D8:
	ldr	r0, _037F9538	; =OSi_SystemCallbackInSwitchThread
	ldr	r2, [r0]
	cmp	r2, #0
	beq	_037F94F8
	mov	r0, r6
	mov	r1, r5
	mov	lr, pc
	bx	r2
_037F94F8:
	ldr	r2, [r4, #12]
	cmp	r2, #0
	beq	_037F9514
	mov	r0, r6
	mov	r1, r5
	mov	lr, pc
	bx	r2
_037F9514:
	ldr	r0, _037F9530	; =OSi_ThreadInfo
	str	r5, [r0, #4]
	mov	r0, r5
	bl	OS_LoadContext
_037F9524:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr
_037F952C:	.word	OSi_RescheduleCount
_037F9530:	.word	OSi_ThreadInfo
_037F9534:	.word	OSi_CurrentThreadPtr
_037F9538:	.word	OSi_SystemCallbackInSwitchThread

	arm_func_start FUN_037F953C
FUN_037F953C: ; 0x037F953C
	ldr	r1, _037F9580	; =OSi_ThreadInfo
	ldr	r2, [r1, #8]
	mov	r1, #0
	b	_037F9554
_037F954C:
	mov	r1, r2
	ldr	r2, [r2, #76]	; 0x4c
_037F9554:
	cmp	r2, #0
	beq	_037F9564
	cmp	r2, r0
	bne	_037F954C
_037F9564:
	cmp	r1, #0
	ldreq	r1, [r0, #76]	; 0x4c
	ldreq	r0, _037F9580	; =OSi_ThreadInfo
	streq	r1, [r0, #8]
	ldrne	r0, [r0, #76]	; 0x4c
	strne	r0, [r1, #76]	; 0x4c
	bx	lr
_037F9580:	.word	OSi_ThreadInfo

	arm_func_start FUN_037F9584
FUN_037F9584: ; 0x037F9584
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _037F95E8	; =OSi_ThreadInfo
	ldr	r3, [r1, #8]
	mov	lr, r3
	mov	ip, #0
	b	_037F95A8
_037F95A0:
	mov	ip, lr
	ldr	lr, [lr, #76]	; 0x4c
_037F95A8:
	cmp	lr, #0
	beq	_037F95C0
	ldr	r2, [lr, #84]	; 0x54
	ldr	r1, [r0, #84]	; 0x54
	cmp	r2, r1
	bcc	_037F95A0
_037F95C0:
	cmp	ip, #0
	streq	r3, [r0, #76]	; 0x4c
	ldreq	r1, _037F95E8	; =OSi_ThreadInfo
	streq	r0, [r1, #8]
	ldrne	r1, [ip, #76]	; 0x4c
	strne	r1, [r0, #76]	; 0x4c
	strne	r0, [ip, #76]	; 0x4c
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037F95E8:	.word	OSi_ThreadInfo

	arm_func_start OSi_RemoveMutexLinkFromQueue
OSi_RemoveMutexLinkFromQueue: ; 0x037F95EC
	ldr	r2, [r0]
	cmp	r2, #0
	beq	_037F9614
	ldr	r1, [r2, #16]
	str	r1, [r0]
	cmp	r1, #0
	movne	r0, #0
	strne	r0, [r1, #20]
	moveq	r1, #0
	streq	r1, [r0, #4]
_037F9614:
	mov	r0, r2
	bx	lr

	arm_func_start FUN_037F961C
FUN_037F961C: ; 0x037F961C
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r2, [r0]
	mov	lr, r2
	b	_037F9664
_037F9630:
	ldr	ip, [lr, #100]	; 0x64
	cmp	lr, r1
	bne	_037F9660
	ldr	r3, [lr, #96]	; 0x60
	cmp	r2, lr
	streq	ip, [r0]
	strne	ip, [r3, #100]	; 0x64
	ldr	r1, [r0, #4]
	cmp	r1, lr
	streq	r3, [r0, #4]
	strne	r3, [ip, #96]	; 0x60
	b	_037F966C
_037F9660:
	mov	lr, ip
_037F9664:
	cmp	lr, #0
	bne	_037F9630
_037F966C:
	mov	r0, lr
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start FUN_037F967C
FUN_037F967C: ; 0x037F967C
	ldr	r2, [r0]
	cmp	r2, #0
	beq	_037F96A8
	ldr	r1, [r2, #100]	; 0x64
	str	r1, [r0]
	cmp	r1, #0
	movne	r0, #0
	strne	r0, [r1, #96]	; 0x60
	moveq	r1, #0
	streq	r1, [r0, #4]
	streq	r1, [r2, #92]	; 0x5c
_037F96A8:
	mov	r0, r2
	bx	lr

	arm_func_start FUN_037F96B0
FUN_037F96B0: ; 0x037F96B0
	ldr	ip, [r0]
	b	_037F96C4
_037F96B8:
	cmp	ip, r1
	bxeq	lr
	ldr	ip, [ip, #100]	; 0x64
_037F96C4:
	cmp	ip, #0
	beq	_037F96DC
	ldr	r3, [ip, #84]	; 0x54
	ldr	r2, [r1, #84]	; 0x54
	cmp	r3, r2
	bls	_037F96B8
_037F96DC:
	cmp	ip, #0
	bne	_037F9708
	ldr	r2, [r0, #4]
	cmp	r2, #0
	streq	r1, [r0]
	strne	r1, [r2, #100]	; 0x64
	str	r2, [r1, #96]	; 0x60
	mov	r2, #0
	str	r2, [r1, #100]	; 0x64
	str	r1, [r0, #4]
	bx	lr
_037F9708:
	ldr	r2, [ip, #96]	; 0x60
	cmp	r2, #0
	streq	r1, [r0]
	strne	r1, [r2, #100]	; 0x64
	str	r2, [r1, #96]	; 0x60
	str	ip, [r1, #100]	; 0x64
	str	r1, [ip, #96]	; 0x60
	bx	lr

	arm_func_start FUN_037F9728
FUN_037F9728: ; 0x037F9728
	ldr	r1, _037F973C	; =_0380778C
	ldr	r0, [r1]
	add	r0, r0, #1
	str	r0, [r1]
	bx	lr
_037F973C:	.word	_0380778C

	arm_func_start OS_InitContext
OS_InitContext: ; 0x037F9740
	add	r1, r1, #4
	str	r1, [r0, #64]	; 0x40
	str	r2, [r0, #68]	; 0x44
	sub	r2, r2, #64	; 0x40
	tst	r2, #4
	subne	r2, r2, #4
	str	r2, [r0, #56]	; 0x38
	ands	r1, r1, #1
	movne	r1, #63	; 0x3f
	moveq	r1, #31
	str	r1, [r0]
	mov	r1, #0
	str	r1, [r0, #4]
	str	r1, [r0, #8]
	str	r1, [r0, #12]
	str	r1, [r0, #16]
	str	r1, [r0, #20]
	str	r1, [r0, #24]
	str	r1, [r0, #28]
	str	r1, [r0, #32]
	str	r1, [r0, #36]	; 0x24
	str	r1, [r0, #40]	; 0x28
	str	r1, [r0, #44]	; 0x2c
	str	r1, [r0, #48]	; 0x30
	str	r1, [r0, #52]	; 0x34
	str	r1, [r0, #60]	; 0x3c
	bx	lr

	arm_func_start OS_SaveContext
OS_SaveContext: ; 0x037F97AC
	add	r1, r0, #0
	mrs	r2, CPSR
	str	r2, [r1], #4
	mov	r0, #211	; 0xd3
	msr	CPSR_c, r0
	str	sp, [r1, #64]	; 0x40
	msr	CPSR_c, r2
	mov	r0, #1
	stmia	r1, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}
	adr r0, OS_LoadContext
	str	r0, [r1, #60]	; 0x3c
	mov	r0, #0
	bx	lr

	arm_func_start OS_LoadContext
OS_LoadContext: ; 0x037F97E0
	mrs	r1, CPSR
	bic	r1, r1, #31
	orr	r1, r1, #211	; 0xd3
	msr	CPSR_c, r1
	ldr	r1, [r0], #4
	msr	SPSR_fsxc, r1
	ldr	sp, [r0, #64]	; 0x40
	ldr	lr, [r0, #60]	; 0x3c
	ldmia	r0, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
	nop			; (mov r0, r0)
	subs	pc, lr, #4

	arm_func_start OS_ReadMessage
OS_ReadMessage: ; 0x037F980C
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r6, r0
	mov	r5, r1
	mov	r7, r2
	bl	OS_DisableInterrupts
	mov	r4, r0
	and	r8, r7, #1
	add	r7, r6, #8
	b	_037F9850
_037F9830:
	cmp	r8, #0
	bne	_037F9848
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #0
	b	_037F987C
_037F9848:
	mov	r0, r7
	bl	OS_SleepThread
_037F9850:
	ldr	r0, [r6, #28]
	cmp	r0, #0
	beq	_037F9830
	cmp	r5, #0
	ldrne	r1, [r6, #16]
	ldrne	r0, [r6, #24]
	ldrne	r0, [r1, r0, lsl #2]
	strne	r0, [r5]
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #1
_037F987C:
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr

	arm_func_start OS_ReceiveMessage
OS_ReceiveMessage: ; 0x037F9884
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r6, r0
	mov	r5, r1
	mov	r7, r2
	bl	OS_DisableInterrupts
	mov	r4, r0
	and	r8, r7, #1
	add	r7, r6, #8
	b	_037F98C8
_037F98A8:
	cmp	r8, #0
	bne	_037F98C0
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #0
	b	_037F991C
_037F98C0:
	mov	r0, r7
	bl	OS_SleepThread
_037F98C8:
	ldr	r0, [r6, #28]
	cmp	r0, #0
	beq	_037F98A8
	cmp	r5, #0
	ldrne	r1, [r6, #16]
	ldrne	r0, [r6, #24]
	ldrne	r0, [r1, r0, lsl #2]
	strne	r0, [r5]
	ldr	r0, [r6, #24]
	add	r0, r0, #1
	ldr	r1, [r6, #20]
	bl	_s32_div_f
	str	r1, [r6, #24]
	ldr	r0, [r6, #28]
	sub	r0, r0, #1
	str	r0, [r6, #28]
	mov	r0, r6
	bl	OS_WakeupThread
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #1
_037F991C:
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr

	arm_func_start OS_SendMessage
OS_SendMessage: ; 0x037F9924
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r6, r0
	mov	r5, r1
	mov	r7, r2
	bl	OS_DisableInterrupts
	mov	r4, r0
	and	r7, r7, #1
	b	_037F9968
_037F9948:
	cmp	r7, #0
	bne	_037F9960
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #0
	b	_037F99AC
_037F9960:
	mov	r0, r6
	bl	OS_SleepThread
_037F9968:
	ldr	r2, [r6, #28]
	ldr	r1, [r6, #20]
	cmp	r1, r2
	ble	_037F9948
	ldr	r0, [r6, #24]
	add	r0, r0, r2
	bl	_s32_div_f
	ldr	r0, [r6, #16]
	str	r5, [r0, r1, lsl #2]
	ldr	r0, [r6, #28]
	add	r0, r0, #1
	str	r0, [r6, #28]
	add	r0, r6, #8
	bl	OS_WakeupThread
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #1
_037F99AC:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr

	arm_func_start OS_InitMessageQueue
OS_InitMessageQueue: ; 0x037F99B8
	mov	ip, #0
	str	ip, [r0, #4]
	ldr	r3, [r0, #4]
	str	r3, [r0]
	str	ip, [r0, #12]
	ldr	r3, [r0, #12]
	str	r3, [r0, #8]
	str	r1, [r0, #16]
	str	r2, [r0, #20]
	str	ip, [r0, #24]
	str	ip, [r0, #28]
	bx	lr

	arm_func_start OSi_DequeueItem
OSi_DequeueItem: ; 0x037F99E8
	ldr	r2, [r1, #16]
	ldr	r1, [r1, #20]
	cmp	r2, #0
	streq	r1, [r0, #112]	; 0x70
	strne	r1, [r2, #20]
	cmp	r1, #0
	streq	r2, [r0, #108]	; 0x6c
	strne	r2, [r1, #16]
	bx	lr

	arm_func_start OSi_EnqueueTail
OSi_EnqueueTail: ; 0x037F9A0C
	ldr	r2, [r0, #112]	; 0x70
	cmp	r2, #0
	streq	r1, [r0, #108]	; 0x6c
	strne	r1, [r2, #16]
	str	r2, [r1, #20]
	mov	r2, #0
	str	r2, [r1, #16]
	str	r1, [r0, #112]	; 0x70
	bx	lr

	arm_func_start OSi_UnlockAllMutex
OSi_UnlockAllMutex: ; 0x037F9A30
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	add	r5, r6, #108	; 0x6c
	mov	r4, #0
	b	_037F9A58
_037F9A44:
	mov	r0, r5
	bl	OSi_RemoveMutexLinkFromQueue
	str	r4, [r0, #12]
	str	r4, [r0, #8]
	bl	OS_WakeupThread
_037F9A58:
	ldr	r0, [r6, #108]	; 0x6c
	cmp	r0, #0
	bne	_037F9A44
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start OS_UnlockMutex
OS_UnlockMutex: ; 0x037F9A6C
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r0, _037F9AD8	; =OSi_ThreadInfo
	ldr	r0, [r0, #4]
	ldr	r1, [r5, #8]
	cmp	r1, r0
	bne	_037F9AC4
	ldr	r1, [r5, #12]
	sub	r1, r1, #1
	str	r1, [r5, #12]
	ldr	r1, [r5, #12]
	cmp	r1, #0
	bne	_037F9AC4
	mov	r1, r5
	bl	OSi_DequeueItem
	mov	r0, #0
	str	r0, [r5, #8]
	mov	r0, r5
	bl	OS_WakeupThread
_037F9AC4:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037F9AD8:	.word	OSi_ThreadInfo

	arm_func_start OS_LockMutex
OS_LockMutex: ; 0x037F9ADC
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r5, r0
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r0, _037F9B64	; =OSi_ThreadInfo
	ldr	r7, [r0, #4]
	mov	r6, #0
_037F9AFC:
	ldr	r0, [r5, #8]
	cmp	r0, #0
	bne	_037F9B28
	str	r7, [r5, #8]
	ldr	r0, [r5, #12]
	add	r0, r0, #1
	str	r0, [r5, #12]
	mov	r0, r7
	mov	r1, r5
	bl	OSi_EnqueueTail
	b	_037F9B50
_037F9B28:
	cmp	r0, r7
	ldreq	r0, [r5, #12]
	addeq	r0, r0, #1
	streq	r0, [r5, #12]
	beq	_037F9B50
	str	r5, [r7, #104]	; 0x68
	mov	r0, r5
	bl	OS_SleepThread
	str	r6, [r7, #104]	; 0x68
	b	_037F9AFC
_037F9B50:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037F9B64:	.word	OSi_ThreadInfo

	arm_func_start OS_InitMutex
OS_InitMutex: ; 0x037F9B68
	mov	r2, #0
	str	r2, [r0, #4]
	ldr	r1, [r0, #4]
	str	r1, [r0]
	str	r2, [r0, #8]
	str	r2, [r0, #12]
	bx	lr

	arm_func_start OS_Init
OS_Init: ; 0x037F9B84
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	bl	OS_InitArena
	bl	PXI_Init
	bl	OS_InitLock
	bl	OS_InitIrqTable
	bl	OS_InitTick
	bl	OS_InitAlarm
	bl	OS_InitThread
	bl	OS_InitReset
	bl	CTRDG_Init
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start OS_SetArenaLo
OS_SetArenaLo: ; 0x037F9BBC
	mov	r0, r0, lsl #2
	add	r0, r0, #40894464	; 0x2700000
	add	r0, r0, #1044480	; 0xff000
	str	r1, [r0, #3488]	; 0xda0
	bx	lr

	arm_func_start OS_SetArenaHi
OS_SetArenaHi: ; 0x037F9BD0
	mov	r0, r0, lsl #2
	add	r0, r0, #40894464	; 0x2700000
	add	r0, r0, #1044480	; 0xff000
	str	r1, [r0, #3524]	; 0xdc4
	bx	lr

	arm_func_start OS_GetInitArenaLo
OS_GetInitArenaLo: ; 0x037F9BE4
	cmp	r0, #1
	beq	_037F9C00
	cmp	r0, #7
	beq	_037F9C08
	cmp	r0, #8
	beq	_037F9C18
	b	_037F9C2C
_037F9C00:
	ldr	r0, _037F9C34	; =0x027FAFCC
	bx	lr
_037F9C08:
	ldr	r0, _037F9C38	; =0x0380B92C
	cmp	r0, #58720256	; 0x03800000
	movhi	r0, #58720256	; 0x03800000
	bx	lr
_037F9C18:
	mov	r0, #58720256	; 0x03800000
	ldr	r1, _037F9C38	; =0x0380B92C
	cmp	r1, #58720256	; 0x03800000
	movhi	r0, r1
	bx	lr
_037F9C2C:
	mov	r0, #0
	bx	lr
_037F9C34:	.word	0x027FAFCC
_037F9C38:	.word	0x0380B92C

	arm_func_start OS_GetInitArenaHi
OS_GetInitArenaHi: ; 0x037F9C3C
	cmp	r0, #1
	beq	_037F9C58
	cmp	r0, #7
	beq	_037F9C60
	cmp	r0, #8
	beq	_037F9C68
	b	_037F9CA0
_037F9C58:
	ldr	r0, _037F9CA8	; =0x027FF000
	bx	lr
_037F9C60:
	mov	r0, #58720256	; 0x03800000
	bx	lr
_037F9C68:
	ldr	r1, _037F9CAC	; =0x00000400
	ldr	r0, _037F9CB0	; =0x0380FF80
	sub	r2, r0, r1
	mov	r0, #58720256	; 0x03800000
	ldr	r1, _037F9CB4	; =0x0380B92C
	cmp	r1, #58720256	; 0x03800000
	movhi	r0, r1
	ldr	r1, _037F9CB8	; =0x00000400
	cmp	r1, #0
	bxeq	lr
	cmp	r1, #0
	sublt	r0, r0, r1
	subge	r0, r2, r1
	bx	lr
_037F9CA0:
	mov	r0, #0
	bx	lr
_037F9CA8:	.word	0x027FF000
_037F9CAC:	.word	0x00000400
_037F9CB0:	.word	0x0380FF80
_037F9CB4:	.word	0x0380B92C
_037F9CB8:	.word	0x00000400

	arm_func_start OS_GetArenaLo
OS_GetArenaLo: ; 0x037F9CBC
	mov	r0, r0, lsl #2
	add	r0, r0, #40894464	; 0x2700000
	add	r0, r0, #1044480	; 0xff000
	ldr	r0, [r0, #3488]	; 0xda0
	bx	lr

	arm_func_start OS_GetArenaHi
OS_GetArenaHi: ; 0x037F9CD0
	mov	r0, r0, lsl #2
	add	r0, r0, #40894464	; 0x2700000
	add	r0, r0, #1044480	; 0xff000
	ldr	r0, [r0, #3524]	; 0xdc4
	bx	lr

	arm_func_start OS_InitArena
OS_InitArena: ; 0x037F9CE4
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _037F9D84	; =_038078F4
	ldr	r0, [r1]
	cmp	r0, #0
	bne	_037F9D78
	mov	r0, #1
	str	r0, [r1]
	bl	OS_GetInitArenaHi
	mov	r1, r0
	mov	r0, #1
	bl	OS_SetArenaHi
	mov	r0, #1
	bl	OS_GetInitArenaLo
	mov	r1, r0
	mov	r0, #1
	bl	OS_SetArenaLo
	mov	r0, #7
	bl	OS_GetInitArenaHi
	mov	r1, r0
	mov	r0, #7
	bl	OS_SetArenaHi
	mov	r0, #7
	bl	OS_GetInitArenaLo
	mov	r1, r0
	mov	r0, #7
	bl	OS_SetArenaLo
	mov	r0, #8
	bl	OS_GetInitArenaHi
	mov	r1, r0
	mov	r0, #8
	bl	OS_SetArenaHi
	mov	r0, #8
	bl	OS_GetInitArenaLo
	mov	r1, r0
	mov	r0, #8
	bl	OS_SetArenaLo
_037F9D78:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037F9D84:	.word	_038078F4

	arm_func_start OS_CheckHeap
OS_CheckHeap: ; 0x037F9D88
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r8, r0
	mov	r7, r1
	mov	r6, #0
	mov	r5, r6
	mvn	r4, #0
	bl	OS_DisableInterrupts
	ldr	r1, _037F9F34	; =OSiHeapInfo
	ldr	ip, [r1, r8, lsl #2]
	mov	r1, r4
	cmp	r7, r1
	ldreq	r7, [ip]
	ldr	r2, [ip, #16]
	cmp	r2, #0
	beq	_037F9F24
	cmp	r7, #0
	blt	_037F9F24
	ldr	r1, [ip, #4]
	cmp	r7, r1
	bge	_037F9F24
	mov	r1, #12
	mul	r1, r7, r1
	add	r3, r2, r1
	ldr	r2, [r2, r1]
	cmp	r2, #0
	blt	_037F9F24
	ldr	r1, [r3, #8]
	cmp	r1, #0
	beq	_037F9E70
	ldr	r7, [r1]
	cmp	r7, #0
	bne	_037F9F24
	b	_037F9E70
_037F9E0C:
	ldr	r7, [ip, #8]
	cmp	r7, r1
	bhi	_037F9F24
	ldr	r7, [ip, #12]
	cmp	r1, r7
	bcs	_037F9F24
	ands	r7, r1, #31
	bne	_037F9F24
	ldr	lr, [r1, #4]
	cmp	lr, #0
	beq	_037F9E44
	ldr	r7, [lr]
	cmp	r7, r1
	bne	_037F9F24
_037F9E44:
	ldr	r7, [r1, #8]
	cmp	r7, #64	; 0x40
	bcc	_037F9F24
	ands	r1, r7, #31
	bne	_037F9F24
	add	r6, r6, r7
	cmp	r6, #0
	ble	_037F9F24
	cmp	r6, r2
	bgt	_037F9F24
	mov	r1, lr
_037F9E70:
	cmp	r1, #0
	bne	_037F9E0C
	ldr	r1, [r3, #4]
	cmp	r1, #0
	beq	_037F9F14
	ldr	r3, [r1]
	cmp	r3, #0
	bne	_037F9F24
	b	_037F9F14
_037F9E94:
	ldr	r3, [ip, #8]
	cmp	r3, r1
	bhi	_037F9F24
	ldr	r3, [ip, #12]
	cmp	r1, r3
	bcs	_037F9F24
	ands	r3, r1, #31
	bne	_037F9F24
	ldr	lr, [r1, #4]
	cmp	lr, #0
	beq	_037F9ECC
	ldr	r3, [lr]
	cmp	r3, r1
	bne	_037F9F24
_037F9ECC:
	ldr	r7, [r1, #8]
	cmp	r7, #64	; 0x40
	bcc	_037F9F24
	ands	r3, r7, #31
	bne	_037F9F24
	cmp	lr, #0
	beq	_037F9EF4
	add	r1, r1, r7
	cmp	r1, lr
	bcs	_037F9F24
_037F9EF4:
	add	r6, r6, r7
	sub	r1, r7, #32
	add	r5, r5, r1
	cmp	r6, #0
	ble	_037F9F24
	cmp	r6, r2
	bgt	_037F9F24
	mov	r1, lr
_037F9F14:
	cmp	r1, #0
	bne	_037F9E94
	cmp	r6, r2
	moveq	r4, r5
_037F9F24:
	bl	OS_RestoreInterrupts
	mov	r0, r4
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037F9F34:	.word	OSiHeapInfo

	arm_func_start OS_CreateHeap
OS_CreateHeap: ; 0x037F9F38
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r4, r0
	mov	r6, r1
	mov	r5, r2
	bl	OS_DisableInterrupts
	ldr	r1, _037F9FDC	; =OSiHeapInfo
	ldr	r7, [r1, r4, lsl #2]
	add	r1, r6, #31
	bic	r6, r1, #31
	bic	r5, r5, #31
	mov	r4, #0
	ldr	lr, [r7, #4]
	mov	r1, #12
	b	_037F9FC0
_037F9F74:
	ldr	r3, [r7, #16]
	mul	r2, r4, r1
	add	ip, r3, r2
	ldr	r2, [r3, r2]
	cmp	r2, #0
	bge	_037F9FBC
	sub	r1, r5, r6
	str	r1, [ip]
	mov	r2, #0
	str	r2, [r6]
	str	r2, [r6, #4]
	ldr	r1, [ip]
	str	r1, [r6, #8]
	str	r6, [ip, #4]
	str	r2, [ip, #8]
	bl	OS_RestoreInterrupts
	mov	r0, r4
	b	_037F9FD0
_037F9FBC:
	add	r4, r4, #1
_037F9FC0:
	cmp	r4, lr
	blt	_037F9F74
	bl	OS_RestoreInterrupts
	mvn	r0, #0
_037F9FD0:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037F9FDC:	.word	OSiHeapInfo

	arm_func_start OS_InitAlloc
OS_InitAlloc: ; 0x037F9FE0
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r7, r0
	mov	r5, r1
	mov	r4, r2
	mov	r6, r3
	bl	OS_DisableInterrupts
	ldr	r1, _037FA084	; =OSiHeapInfo
	str	r5, [r1, r7, lsl #2]
	mov	r2, #12
	mul	r1, r6, r2
	add	r3, r5, #20
	str	r3, [r5, #16]
	str	r6, [r5, #4]
	mov	r8, #0
	mvn	lr, #0
	mov	ip, r8
	b	_037FA044
_037FA024:
	ldr	r6, [r5, #16]
	mul	r3, r8, r2
	add	r7, r6, r3
	str	lr, [r6, r3]
	str	ip, [r7, #8]
	ldr	r3, [r7, #8]
	str	r3, [r7, #4]
	add	r8, r8, #1
_037FA044:
	ldr	r3, [r5, #4]
	cmp	r8, r3
	blt	_037FA024
	mvn	r2, #0
	str	r2, [r5]
	ldr	r2, [r5, #16]
	add	r1, r2, r1
	add	r1, r1, #31
	bic	r1, r1, #31
	str	r1, [r5, #8]
	bic	r1, r4, #31
	str	r1, [r5, #12]
	bl	OS_RestoreInterrupts
	ldr	r0, [r5, #8]
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FA084:	.word	OSiHeapInfo

	arm_func_start OS_SetCurrentHeap
OS_SetCurrentHeap: ; 0x037FA088
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r4, r0
	mov	r5, r1
	bl	OS_DisableInterrupts
	ldr	r1, _037FA0C0	; =OSiHeapInfo
	ldr	r1, [r1, r4, lsl #2]
	ldr	r4, [r1]
	str	r5, [r1]
	bl	OS_RestoreInterrupts
	mov	r0, r4
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FA0C0:	.word	OSiHeapInfo

	arm_func_start OS_FreeToHeap
OS_FreeToHeap: ; 0x037FA0C4
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r4, r1
	mov	r6, r2
	bl	OS_DisableInterrupts
	mov	r5, r0
	ldr	r0, _037FA134	; =OSiHeapInfo
	ldr	r0, [r0, r7, lsl #2]
	cmp	r4, #0
	ldrlt	r4, [r0]
	sub	r6, r6, #32
	ldr	r1, [r0, #16]
	mov	r0, #12
	mla	r7, r4, r0, r1
	ldr	r0, [r7, #8]
	mov	r1, r6
	bl	FUN_037FA304
	str	r0, [r7, #8]
	ldr	r0, [r7, #4]
	mov	r1, r6
	bl	FUN_037FA250
	str	r0, [r7, #4]
	mov	r0, r5
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FA134:	.word	OSiHeapInfo

	arm_func_start OS_AllocFromHeap
OS_AllocFromHeap: ; 0x037FA138
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r6, r0
	mov	r5, r1
	mov	r7, r2
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r1, _037FA24C	; =OSiHeapInfo
	ldr	r1, [r1, r6, lsl #2]
	cmp	r1, #0
	bne	_037FA170
	bl	OS_RestoreInterrupts
	mov	r0, #0
	b	_037FA240
_037FA170:
	cmp	r5, #0
	ldrlt	r5, [r1]
	ldr	r1, [r1, #16]
	mov	r0, #12
	mla	r6, r5, r0, r1
	add	r0, r7, #32
	add	r0, r0, #31
	bic	r7, r0, #31
	ldr	r0, [r6, #4]
	mov	r5, r0
	b	_037FA1AC
_037FA19C:
	ldr	r1, [r5, #8]
	cmp	r7, r1
	ble	_037FA1B4
	ldr	r5, [r5, #4]
_037FA1AC:
	cmp	r5, #0
	bne	_037FA19C
_037FA1B4:
	cmp	r5, #0
	bne	_037FA1CC
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #0
	b	_037FA240
_037FA1CC:
	ldr	r1, [r5, #8]
	sub	r1, r1, r7
	cmp	r1, #64	; 0x40
	bcs	_037FA1EC
	mov	r1, r5
	bl	FUN_037FA304
	str	r0, [r6, #4]
	b	_037FA224
_037FA1EC:
	str	r7, [r5, #8]
	add	r2, r5, r7
	str	r1, [r2, #8]
	ldr	r0, [r5]
	str	r0, [r5, r7]
	ldr	r0, [r5, #4]
	str	r0, [r2, #4]
	ldr	r0, [r2, #4]
	cmp	r0, #0
	strne	r2, [r0]
	ldr	r0, [r2]
	cmp	r0, #0
	strne	r2, [r0, #4]
	streq	r2, [r6, #4]
_037FA224:
	ldr	r0, [r6, #8]
	mov	r1, r5
	bl	FUN_037FA32C
	str	r0, [r6, #8]
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	r0, r5, #32
_037FA240:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FA24C:	.word	OSiHeapInfo

	arm_func_start FUN_037FA250
FUN_037FA250: ; 0x037FA250
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	ip, r0
	mov	lr, #0
	b	_037FA274
_037FA264:
	cmp	r1, ip
	bls	_037FA27C
	mov	lr, ip
	ldr	ip, [ip, #4]
_037FA274:
	cmp	ip, #0
	bne	_037FA264
_037FA27C:
	str	ip, [r1, #4]
	str	lr, [r1]
	cmp	ip, #0
	beq	_037FA2BC
	str	r1, [ip]
	ldr	r3, [r1, #8]
	add	r2, r1, r3
	cmp	r2, ip
	bne	_037FA2BC
	ldr	r2, [ip, #8]
	add	r2, r3, r2
	str	r2, [r1, #8]
	ldr	ip, [ip, #4]
	str	ip, [r1, #4]
	cmp	ip, #0
	strne	r1, [ip]
_037FA2BC:
	cmp	lr, #0
	beq	_037FA2F4
	str	r1, [lr, #4]
	ldr	r2, [lr, #8]
	add	r3, lr, r2
	cmp	r3, r1
	bne	_037FA2F8
	ldr	r1, [r1, #8]
	add	r1, r2, r1
	str	r1, [lr, #8]
	str	ip, [lr, #4]
	cmp	ip, #0
	strne	lr, [ip]
	b	_037FA2F8
_037FA2F4:
	mov	r0, r1
_037FA2F8:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start FUN_037FA304
FUN_037FA304: ; 0x037FA304
	ldr	r3, [r1, #4]
	cmp	r3, #0
	ldrne	r2, [r1]
	strne	r2, [r3]
	ldr	r2, [r1]
	cmp	r2, #0
	ldreq	r0, [r1, #4]
	ldrne	r1, [r1, #4]
	strne	r1, [r2, #4]
	bx	lr

	arm_func_start FUN_037FA32C
FUN_037FA32C: ; 0x037FA32C
	str	r0, [r1, #4]
	mov	r2, #0
	str	r2, [r1]
	cmp	r0, #0
	strne	r1, [r0]
	mov	r0, r1
	bx	lr

	arm_func_start OSi_SetTimerReserved
OSi_SetTimerReserved: ; 0x037FA348
	ldr	r1, _037FA360	; =_0380791C
	ldrh	r3, [r1]
	mov	r2, #1
	orr	r0, r3, r2, lsl r0
	strh	r0, [r1]
	bx	lr
_037FA360:	.word	_0380791C

	arm_func_start OS_GetTick
OS_GetTick: ; 0x037FA364
	stmfd	sp!, {lr}
	sub	sp, sp, #12
	bl	OS_DisableInterrupts
	ldr	r1, _037FA404	; =0x04000100
	ldrh	r1, [r1]
	strh	r1, [sp]
	ldr	r1, _037FA408	; =OSi_TickCounter
	ldr	ip, [r1]
	ldr	r3, [r1, #4]
	ldr	r2, _037FA40C	; =0x0000FFFF
	mvn	r1, #0
	and	r2, r3, r2
	and	r1, ip, r1
	str	r1, [sp, #4]
	str	r2, [sp, #8]
	ldr	r1, _037FA410	; =0x04000214
	ldr	r1, [r1]
	ands	r1, r1, #8
	beq	_037FA3D8
	ldrh	r1, [sp]
	ands	r1, r1, #32768	; 0x8000
	bne	_037FA3D8
	ldr	r3, [sp, #4]
	ldr	r2, [sp, #8]
	mov	r1, #1
	adds	r3, r3, r1
	adc	r1, r2, #0
	str	r3, [sp, #4]
	str	r1, [sp, #8]
_037FA3D8:
	bl	OS_RestoreInterrupts
	ldr	r2, [sp, #4]
	ldr	r0, [sp, #8]
	mov	r1, r0, lsl #16
	orr	r1, r1, r2, lsr #16
	ldrh	r0, [sp]
	orr	r1, r1, r0, asr #31
	orr	r0, r0, r2, lsl #16
	add	sp, sp, #12
	ldmia	sp!, {lr}
	bx	lr
_037FA404:	.word	0x04000100
_037FA408:	.word	OSi_TickCounter
_037FA40C:	.word	0x0000FFFF
_037FA410:	.word	0x04000214

	arm_func_start FUN_037FA414
FUN_037FA414: ; 0x037FA414
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _037FA488	; =OSi_TickCounter
	ldr	ip, [r1]
	ldr	r2, [r1, #4]
	mov	r3, #0
	mov	r0, #1
	adds	ip, ip, r0
	adc	r0, r2, #0
	str	ip, [r1]
	str	r0, [r1, #4]
	ldr	r0, _037FA48C	; =OSi_NeedResetTimer
	ldr	r1, [r0]
	cmp	r1, #0
	beq	_037FA46C
	ldr	r2, _037FA490	; =0x04000102
	strh	r3, [r2]
	ldr	r1, _037FA494	; =0x04000100
	strh	r3, [r1]
	mov	r1, #193	; 0xc1
	strh	r1, [r2]
	str	r3, [r0]
_037FA46C:
	mov	r0, #0
	ldr	r1, _037FA498	; =FUN_037FA414
	mov	r2, r0
	bl	OSi_EnterTimerCallback
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FA488:	.word	OSi_TickCounter
_037FA48C:	.word	OSi_NeedResetTimer
_037FA490:	.word	0x04000102
_037FA494:	.word	0x04000100
_037FA498:	.word	FUN_037FA414

	arm_func_start OS_IsTickAvailable
OS_IsTickAvailable: ; 0x037FA49C
	ldr	r0, _037FA4A8	; =_03807920
	ldrh	r0, [r0]
	bx	lr
_037FA4A8:	.word	_03807920

	arm_func_start OS_InitTick
OS_InitTick: ; 0x037FA4AC
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037FA528	; =_03807920
	ldrh	r1, [r0]
	cmp	r1, #0
	bne	_037FA51C
	mov	r1, #1
	strh	r1, [r0]
	mov	r0, #0
	bl	OSi_SetTimerReserved
	mov	r2, #0
	ldr	r0, _037FA52C	; =OSi_TickCounter
	str	r2, [r0]
	str	r2, [r0, #4]
	ldr	r1, _037FA530	; =0x04000102
	strh	r2, [r1]
	ldr	r0, _037FA534	; =0x04000100
	strh	r2, [r0]
	mov	r0, #193	; 0xc1
	strh	r0, [r1]
	mov	r0, #8
	ldr	r1, _037FA538	; =FUN_037FA414
	bl	OS_SetIrqFunction
	mov	r0, #8
	bl	OS_EnableIrqMask
	mov	r1, #0
	ldr	r0, _037FA53C	; =OSi_NeedResetTimer
	str	r1, [r0]
_037FA51C:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FA528:	.word	_03807920
_037FA52C:	.word	OSi_TickCounter
_037FA530:	.word	0x04000102
_037FA534:	.word	0x04000100
_037FA538:	.word	FUN_037FA414
_037FA53C:	.word	OSi_NeedResetTimer

	arm_func_start FUN_037FA540
FUN_037FA540: ; 0x037FA540
	stmdb	sp!, {r0, lr}
	bl	FUN_037FA550
	ldmia	sp!, {r0, lr}
	bx	lr

	arm_func_start FUN_037FA550
FUN_037FA550: ; 0x037FA550
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r1, #0
	ldr	r0, _037FA644	; =0x04000106
	strh	r1, [r0]
	mov	r0, #16
	bl	OS_DisableIrqMask
	ldr	r1, _037FA648	; =0x0380FFF8
	ldr	r0, [r1]
	orr	r0, r0, #16
	str	r0, [r1]
	bl	OS_GetTick
	ldr	r2, _037FA64C	; =_03807934
	ldr	r4, [r2]
	cmp	r4, #0
	beq	_037FA638
	ldr	ip, [r4, #12]
	ldr	r3, [r4, #16]
	cmp	r1, r3
	cmpeq	r0, ip
	bcs	_037FA5B0
	mov	r0, r4
	bl	FUN_037FA970
	b	_037FA638
_037FA5B0:
	ldr	r1, [r4, #24]
	str	r1, [r2]
	cmp	r1, #0
	moveq	r0, #0
	streq	r0, [r2, #4]
	movne	r0, #0
	strne	r0, [r1, #20]
	ldr	r5, [r4]
	ldr	r2, [r4, #28]
	ldr	r1, [r4, #32]
	mov	r0, #0
	cmp	r1, r0
	cmpeq	r2, r0
	streq	r0, [r4]
	cmp	r5, #0
	beq	_037FA5FC
	ldr	r0, [r4, #4]
	mov	lr, pc
	bx	r5
_037FA5FC:
	ldr	r2, [r4, #28]
	ldr	r0, [r4, #32]
	mov	r1, #0
	cmp	r0, r1
	cmpeq	r2, r1
	beq	_037FA624
	str	r5, [r4]
	mov	r0, r4
	mov	r2, r1
	bl	FUN_037FA7D0
_037FA624:
	ldr	r0, _037FA64C	; =_03807934
	ldr	r0, [r0]
	cmp	r0, #0
	beq	_037FA638
	bl	FUN_037FA970
_037FA638:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FA644:	.word	0x04000106
_037FA648:	.word	0x0380FFF8
_037FA64C:	.word	_03807934

	arm_func_start OS_CancelAlarm
OS_CancelAlarm: ; 0x037FA650
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r1, [r5]
	cmp	r1, #0
	bne	_037FA678
	bl	OS_RestoreInterrupts
	b	_037FA6D0
_037FA678:
	ldr	r0, [r5, #24]
	cmp	r0, #0
	ldreq	r2, [r5, #20]
	ldreq	r1, _037FA6DC	; =_03807934
	streq	r2, [r1, #4]
	ldrne	r1, [r5, #20]
	strne	r1, [r0, #20]
	ldr	r1, [r5, #20]
	cmp	r1, #0
	strne	r0, [r1, #24]
	bne	_037FA6B8
	ldr	r1, _037FA6DC	; =_03807934
	str	r0, [r1]
	cmp	r0, #0
	beq	_037FA6B8
	bl	FUN_037FA970
_037FA6B8:
	mov	r0, #0
	str	r0, [r5]
	str	r0, [r5, #28]
	str	r0, [r5, #32]
	mov	r0, r4
	bl	OS_RestoreInterrupts
_037FA6D0:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FA6DC:	.word	_03807934

	arm_func_start OS_SetPeriodicAlarm
OS_SetPeriodicAlarm: ; 0x037FA6E0
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	movs	r4, r0
	mov	r9, r1
	mov	r8, r2
	mov	r7, r3
	ldr	r6, [sp, #32]
	beq	_037FA70C
	ldr	r0, [r4]
	cmp	r0, #0
	beq	_037FA710
_037FA70C:
	bl	FUN_037FB1F0
_037FA710:
	bl	OS_DisableInterrupts
	mov	r5, r0
	str	r7, [r4, #28]
	str	r6, [r4, #32]
	str	r9, [r4, #36]	; 0x24
	str	r8, [r4, #40]	; 0x28
	ldr	r0, [sp, #36]	; 0x24
	str	r0, [r4]
	ldr	r0, [sp, #40]	; 0x28
	str	r0, [r4, #4]
	mov	r0, r4
	mov	r1, #0
	mov	r2, r1
	bl	FUN_037FA7D0
	mov	r0, r5
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr

	arm_func_start OS_SetAlarm
OS_SetAlarm: ; 0x037FA75C
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	movs	r7, r0
	mov	r6, r1
	mov	r5, r2
	mov	r8, r3
	beq	_037FA780
	ldr	r0, [r7]
	cmp	r0, #0
	beq	_037FA784
_037FA780:
	bl	FUN_037FB1F0
_037FA784:
	bl	OS_DisableInterrupts
	mov	r4, r0
	mov	r0, #0
	str	r0, [r7, #28]
	str	r0, [r7, #32]
	str	r8, [r7]
	ldr	r0, [sp, #24]
	str	r0, [r7, #4]
	bl	OS_GetTick
	mov	r2, r0
	mov	r0, r7
	adds	r3, r6, r2
	adc	r2, r5, r1
	mov	r1, r3
	bl	FUN_037FA7D0
	mov	r0, r4
	bl	OS_RestoreInterrupts
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr

	arm_func_start FUN_037FA7D0
FUN_037FA7D0: ; 0x037FA7D0
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r8, r0
	mov	r7, r1
	mov	r6, r2
	ldr	r2, [r8, #28]
	ldr	r1, [r8, #32]
	mov	r0, #0
	cmp	r1, r0
	cmpeq	r2, r0
	beq	_037FA84C
	bl	OS_GetTick
	ldr	r7, [r8, #36]	; 0x24
	ldr	r6, [r8, #40]	; 0x28
	cmp	r6, r1
	cmpeq	r7, r0
	bcs	_037FA84C
	ldr	r5, [r8, #28]
	ldr	r4, [r8, #32]
	subs	r0, r0, r7
	sbc	r1, r1, r6
	mov	r2, r5
	mov	r3, r4
	bl	_ll_udiv
	mov	r2, #1
	adds	r2, r0, r2
	adc	r0, r1, #0
	umull	r3, r1, r5, r2
	mla	r1, r5, r0, r1
	mla	r1, r4, r2, r1
	adds	r7, r7, r3
	adc	r6, r6, r1
_037FA84C:
	str	r7, [r8, #12]
	str	r6, [r8, #16]
	ldr	r0, _037FA8FC	; =_03807934
	ldr	r4, [r0]
	mov	r1, #0
	b	_037FA8B8
_037FA864:
	ldr	r2, [r4, #12]
	ldr	r0, [r4, #16]
	subs	r3, r7, r2
	sbc	r2, r6, r0
	subs	r0, r3, r1
	sbcs	r0, r2, r1
	bge	_037FA8B4
	ldr	r0, [r4, #20]
	str	r0, [r8, #20]
	str	r8, [r4, #20]
	str	r4, [r8, #24]
	ldr	r0, [r8, #20]
	cmp	r0, #0
	strne	r8, [r0, #24]
	bne	_037FA8F4
	ldr	r0, _037FA8FC	; =_03807934
	str	r8, [r0]
	mov	r0, r8
	bl	FUN_037FA970
	b	_037FA8F4
_037FA8B4:
	ldr	r4, [r4, #24]
_037FA8B8:
	cmp	r4, #0
	bne	_037FA864
	mov	r0, #0
	str	r0, [r8, #24]
	ldr	r0, _037FA8FC	; =_03807934
	ldr	r1, [r0, #4]
	str	r8, [r0, #4]
	str	r1, [r8, #20]
	cmp	r1, #0
	strne	r8, [r1, #24]
	bne	_037FA8F4
	str	r8, [r0, #4]
	str	r8, [r0]
	mov	r0, r8
	bl	FUN_037FA970
_037FA8F4:
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FA8FC:	.word	_03807934

	arm_func_start OS_CreateAlarm
OS_CreateAlarm: ; 0x037FA900
	mov	r1, #0
	str	r1, [r0]
	str	r1, [r0, #8]
	bx	lr

	arm_func_start OS_IsAlarmAvailable
OS_IsAlarmAvailable: ; 0x037FA910
	ldr	r0, _037FA91C	; =_03807930
	ldrh	r0, [r0]
	bx	lr
_037FA91C:	.word	_03807930

	arm_func_start OS_InitAlarm
OS_InitAlarm: ; 0x037FA920
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _037FA968	; =_03807930
	ldrh	r0, [r1]
	cmp	r0, #0
	bne	_037FA95C
	mov	r0, #1
	strh	r0, [r1]
	bl	OSi_SetTimerReserved
	mov	r1, #0
	ldr	r0, _037FA96C	; =_03807934
	str	r1, [r0]
	str	r1, [r0, #4]
	mov	r0, #16
	bl	OS_DisableIrqMask
_037FA95C:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FA968:	.word	_03807930
_037FA96C:	.word	_03807934

	arm_func_start FUN_037FA970
FUN_037FA970: ; 0x037FA970
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r4, r0
	bl	OS_GetTick
	mov	r2, #0
	ldr	r3, _037FA9FC	; =0x04000106
	strh	r2, [r3]
	ldr	ip, [r4, #12]
	ldr	r3, [r4, #16]
	subs	r5, ip, r0
	sbc	r4, r3, r1
	mov	r0, #1
	ldr	r1, _037FAA00	; =FUN_037FA540
	bl	OSi_EnterTimerCallback
	mov	r1, #0
	subs	r0, r5, r1
	sbcs	r0, r4, r1
	ldrlt	r1, _037FAA04	; =0x0000FFFE
	blt	_037FA9D4
	mov	r0, #65536	; 0x10000
	subs	r0, r5, r0
	sbcs	r0, r4, r1
	mvnlt	r0, r5
	movlt	r0, r0, lsl #16
	movlt	r1, r0, lsr #16
_037FA9D4:
	ldr	r0, _037FAA08	; =0x04000104
	strh	r1, [r0]
	mov	r1, #193	; 0xc1
	ldr	r0, _037FA9FC	; =0x04000106
	strh	r1, [r0]
	mov	r0, #16
	bl	OS_EnableIrqMask
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FA9FC:	.word	0x04000106
_037FAA00:	.word	FUN_037FA540
_037FAA04:	.word	0x0000FFFE
_037FAA08:	.word	0x04000104

	arm_func_start FUN_037FAA0C
FUN_037FAA0C: ; 0x037FAA0C
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	bl	OS_DisableInterrupts
	ldr	r1, _037FAA50	; =_03807940
	ldr	r1, [r1]
	cmp	r4, r1
	ldrlt	r1, _037FAA54	; =_03807944
	ldrlt	r2, [r1]
	addlt	r2, r2, #1
	strlt	r2, [r1]
	ldr	r1, _037FAA50	; =_03807940
	str	r4, [r1]
	bl	OS_RestoreInterrupts
	ldr	r0, _037FAA54	; =_03807944
	ldr	r0, [r0]
	ldmia	sp!, {r4, lr}
	bx	lr
_037FAA50:	.word	_03807940
_037FAA54:	.word	_03807944

	arm_func_start FUN_037FAA58
FUN_037FAA58: ; 0x037FAA58
	ldr	r3, [r0, #12]
	subs	r3, r1, r3
	ldrsh	r1, [r0, #16]
	sub	r2, r2, r1
	bmi	_037FAA7C
	cmp	r3, #0
	bne	_037FAA84
	cmp	r2, #0
	bge	_037FAA84
_037FAA7C:
	mov	r0, #0
	bx	lr
_037FAA84:
	cmp	r2, #0
	ldrlt	r1, _037FAAA4	; =0x00000107
	addlt	r2, r2, r1
	ldrsh	r0, [r0, #18]
	cmp	r2, r0
	movle	r0, #1
	movgt	r0, #2
	bx	lr
_037FAAA4:	.word	0x00000107

	arm_func_start FUN_037FAAA8
FUN_037FAAA8: ; 0x037FAAA8
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	r0, #4
	bl	OS_DisableIrqMask
	ldr	r2, _037FAC1C	; =0x04000004
	ldrh	r0, [r2]
	bic	r0, r0, #32
	strh	r0, [r2]
	ldr	r1, _037FAC20	; =0x0380FFF8
	ldr	r0, [r1]
	orr	r0, r0, #4
	str	r0, [r1]
	ldrh	r2, [r2]
	mov	r0, r2, asr #8
	and	r1, r0, #255	; 0xff
	mov	r0, r2, lsl #1
	and	r0, r0, #256	; 0x100
	orr	r0, r1, r0
	sub	r0, r0, #1
	bl	FUN_037FAA0C
	ldr	r9, _037FAC24	; =0x04000006
	mov	r6, #4
	ldr	r5, _037FAC1C	; =0x04000004
	mov	r4, #0
	ldr	fp, _037FAC28	; =_03807944
	b	_037FAC00
_037FAB10:
	ldrh	r8, [r9]
	mov	r0, r8
	bl	FUN_037FAA0C
	mov	r7, r0
	mov	r0, sl
	mov	r1, r7
	mov	r2, r8
	bl	FUN_037FAA58
	cmp	r0, #0
	beq	_037FAB4C
	cmp	r0, #1
	beq	_037FAB8C
	cmp	r0, #2
	beq	_037FABE4
	b	_037FAC00
_037FAB4C:
	mov	r0, sl
	bl	FUN_037FAD2C
	ldrh	r1, [r9]
	ldrsh	r0, [sl, #16]
	cmp	r0, r1
	bne	_037FAC10
	ldr	r0, [sl, #12]
	cmp	r0, r7
	bne	_037FAC10
	mov	r0, r6
	bl	OS_DisableIrqMask
	ldrh	r0, [r5]
	bic	r0, r0, #32
	strh	r0, [r5]
	mov	r0, r6
	bl	OS_ResetRequestIrqMask
_037FAB8C:
	ldr	r7, [sl]
	mov	r0, sl
	bl	FUN_037FAECC
	str	r4, [sl]
	cmp	r7, #0
	beq	_037FABB0
	ldr	r0, [sl, #4]
	mov	lr, pc
	bx	r7
_037FABB0:
	ldr	r0, [sl, #28]
	cmp	r0, #0
	beq	_037FAC00
	ldr	r0, [sl, #36]	; 0x24
	cmp	r0, #0
	bne	_037FAC00
	str	r7, [sl]
	ldr	r0, [fp]
	add	r0, r0, #1
	str	r0, [sl, #12]
	mov	r0, sl
	bl	FUN_037FAF04
	b	_037FAC00
_037FABE4:
	mov	r0, sl
	bl	FUN_037FAECC
	mov	r0, sl
	bl	FUN_037FAF04
	ldr	r0, [fp]
	add	r0, r0, #1
	str	r0, [sl, #12]
_037FAC00:
	ldr	r0, _037FAC2C	; =_03807948
	ldr	sl, [r0]
	cmp	sl, #0
	bne	_037FAB10
_037FAC10:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FAC1C:	.word	0x04000004
_037FAC20:	.word	0x0380FFF8
_037FAC24:	.word	0x04000006
_037FAC28:	.word	_03807944
_037FAC2C:	.word	_03807948

	arm_func_start OS_CancelVAlarms
OS_CancelVAlarms: ; 0x037FAC30
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	bl	OS_DisableInterrupts
	mov	r5, r0
	cmp	r7, #0
	bne	_037FAC50
	bl	FUN_037FB1F0
_037FAC50:
	ldr	r0, _037FACA8	; =_03807948
	ldr	r0, [r0]
	cmp	r0, #0
	ldrne	r6, [r0, #24]
	moveq	r6, #0
	mov	r4, #0
	b	_037FAC8C
_037FAC6C:
	ldr	r1, [r0, #8]
	cmp	r1, r7
	bne	_037FAC7C
	bl	OS_CancelVAlarm
_037FAC7C:
	mov	r0, r6
	cmp	r6, #0
	ldrne	r6, [r6, #24]
	moveq	r6, r4
_037FAC8C:
	cmp	r0, #0
	bne	_037FAC6C
	mov	r0, r5
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FACA8:	.word	_03807948

	arm_func_start OS_CancelVAlarm
OS_CancelVAlarm: ; 0x037FACAC
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	bl	OS_DisableInterrupts
	mov	r4, r0
	mov	r1, #1
	str	r1, [r5, #36]	; 0x24
	ldr	r1, [r5]
	cmp	r1, #0
	bne	_037FACDC
	bl	OS_RestoreInterrupts
	b	_037FACF4
_037FACDC:
	mov	r0, r5
	bl	FUN_037FAECC
	mov	r0, #0
	str	r0, [r5]
	mov	r0, r4
	bl	OS_RestoreInterrupts
_037FACF4:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start OS_SetVAlarmTag
OS_SetVAlarmTag: ; 0x037FAD00
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	movs	r4, r1
	bne	_037FAD18
	bl	FUN_037FB1F0
_037FAD18:
	cmp	r5, #0
	strne	r4, [r5, #8]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start FUN_037FAD2C
FUN_037FAD2C: ; 0x037FAD2C
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #4
	ldr	r1, _037FAD80	; =FUN_037FAAA8
	bl	OS_SetIrqFunction
	ldrsh	ip, [r4, #16]
	and	r3, ip, #256	; 0x100
	ldr	r1, _037FAD84	; =0x04000004
	ldrh	r0, [r1]
	and	r2, r0, #63	; 0x3f
	and	r0, ip, #255	; 0xff
	orr	r0, r2, r0, lsl #8
	orr	r0, r0, r3, asr #1
	strh	r0, [r1]
	ldrh	r0, [r1]
	orr	r0, r0, #32
	strh	r0, [r1]
	mov	r0, #4
	bl	OS_EnableIrqMask
	ldmia	sp!, {r4, lr}
	bx	lr
_037FAD80:	.word	FUN_037FAAA8
_037FAD84:	.word	0x04000004

	arm_func_start OS_SetPeriodicVAlarm
OS_SetPeriodicVAlarm: ; 0x037FAD88
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r8, r0
	mov	r7, r1
	mov	r6, r2
	mov	r5, r3
	bl	OS_DisableInterrupts
	mov	r4, r0
	cmp	r8, #0
	beq	_037FADBC
	ldr	r0, [r8]
	cmp	r0, #0
	beq	_037FADC0
_037FADBC:
	bl	FUN_037FB1F0
_037FADC0:
	ldr	r0, _037FAE1C	; =0x04000006
	ldrh	r9, [r0]
	mov	r0, r9
	bl	FUN_037FAA0C
	mov	r1, #1
	str	r1, [r8, #28]
	strh	r7, [r8, #16]
	cmp	r7, r9
	addle	r0, r0, #1
	str	r0, [r8, #12]
	strh	r6, [r8, #18]
	str	r5, [r8]
	ldr	r0, [sp, #32]
	str	r0, [r8, #4]
	mov	r0, #0
	str	r0, [r8, #36]	; 0x24
	mov	r0, r8
	bl	FUN_037FAF48
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037FAE1C:	.word	0x04000006

	arm_func_start OS_SetVAlarm
OS_SetVAlarm: ; 0x037FAE20
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r8, r0
	mov	r7, r1
	mov	r6, r2
	mov	r5, r3
	bl	OS_DisableInterrupts
	mov	r4, r0
	cmp	r8, #0
	beq	_037FAE54
	ldr	r0, [r8]
	cmp	r0, #0
	beq	_037FAE58
_037FAE54:
	bl	FUN_037FB1F0
_037FAE58:
	ldr	r0, _037FAEB4	; =0x04000006
	ldrh	r9, [r0]
	mov	r0, r9
	bl	FUN_037FAA0C
	mov	r1, #0
	str	r1, [r8, #28]
	strh	r7, [r8, #16]
	cmp	r7, r9
	addle	r0, r0, #1
	str	r0, [r8, #12]
	strh	r6, [r8, #18]
	str	r5, [r8]
	ldr	r0, [sp, #32]
	str	r0, [r8, #4]
	mov	r0, #0
	str	r0, [r8, #36]	; 0x24
	mov	r0, r8
	bl	FUN_037FAF48
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037FAEB4:	.word	0x04000006

	arm_func_start OS_CreateVAlarm
OS_CreateVAlarm: ; 0x037FAEB8
	mov	r1, #0
	str	r1, [r0]
	str	r1, [r0, #8]
	str	r1, [r0, #32]
	bx	lr

	arm_func_start FUN_037FAECC
FUN_037FAECC: ; 0x037FAECC
	cmp	r0, #0
	bxeq	lr
	ldr	r2, [r0, #20]
	ldr	r1, [r0, #24]
	cmp	r1, #0
	strne	r2, [r1, #20]
	ldreq	r0, _037FAF00	; =_03807948
	streq	r2, [r0, #4]
	cmp	r2, #0
	strne	r1, [r2, #24]
	ldreq	r0, _037FAF00	; =_03807948
	streq	r1, [r0]
	bx	lr
_037FAF00:	.word	_03807948

	arm_func_start FUN_037FAF04
FUN_037FAF04: ; 0x037FAF04
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _037FAF44	; =_03807948
	ldr	r3, [r1, #4]
	str	r3, [r0, #20]
	mov	r2, #0
	str	r2, [r0, #24]
	str	r0, [r1, #4]
	cmp	r3, #0
	strne	r0, [r3, #24]
	bne	_037FAF38
	str	r0, [r1]
	bl	FUN_037FAD2C
_037FAF38:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FAF44:	.word	_03807948

	arm_func_start FUN_037FAF48
FUN_037FAF48: ; 0x037FAF48
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _037FAFCC	; =_03807948
	ldr	r3, [r1]
	b	_037FAFB4
_037FAF5C:
	ldr	r2, [r0, #12]
	ldr	r1, [r3, #12]
	cmp	r1, r2
	bcc	_037FAFB0
	cmp	r1, r2
	bne	_037FAF84
	ldrsh	r2, [r3, #16]
	ldrsh	r1, [r0, #16]
	cmp	r2, r1
	ble	_037FAFB0
_037FAF84:
	ldr	r1, [r3, #20]
	str	r1, [r0, #20]
	str	r3, [r0, #24]
	str	r0, [r3, #20]
	cmp	r1, #0
	strne	r0, [r1, #24]
	bne	_037FAFC0
	ldr	r1, _037FAFCC	; =_03807948
	str	r0, [r1]
	bl	FUN_037FAD2C
	b	_037FAFC0
_037FAFB0:
	ldr	r3, [r3, #24]
_037FAFB4:
	cmp	r3, #0
	bne	_037FAF5C
	bl	FUN_037FAF04
_037FAFC0:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FAFCC:	.word	_03807948

	arm_func_start OS_IsVAlarmAvailable
OS_IsVAlarmAvailable: ; 0x037FAFD0
	ldr	r0, _037FAFDC	; =_0380793C
	ldrh	r0, [r0]
	bx	lr
_037FAFDC:	.word	_0380793C

	arm_func_start OS_InitVAlarm
OS_InitVAlarm: ; 0x037FAFE0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037FB038	; =_0380793C
	ldrh	r1, [r0]
	cmp	r1, #0
	bne	_037FB02C
	mov	r1, #1
	strh	r1, [r0]
	mov	r1, #0
	ldr	r0, _037FB03C	; =_03807948
	str	r1, [r0]
	str	r1, [r0, #4]
	mov	r0, #4
	bl	OS_DisableIrqMask
	mov	r1, #0
	ldr	r0, _037FB040	; =_03807944
	str	r1, [r0]
	ldr	r0, _037FB044	; =_03807940
	str	r1, [r0]
_037FB02C:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FB038:	.word	_0380793C
_037FB03C:	.word	_03807948
_037FB040:	.word	_03807944
_037FB044:	.word	_03807940

	arm_func_start OS_EnableInterrupts
OS_EnableInterrupts: ; 0x037FB048
	mrs	r0, CPSR
	bic	r1, r0, #128	; 0x80
	msr	CPSR_c, r1
	and	r0, r0, #128	; 0x80
	bx	lr

	arm_func_start OS_DisableInterrupts
OS_DisableInterrupts: ; 0x037FB05C
	mrs	r0, CPSR
	orr	r1, r0, #128	; 0x80
	msr	CPSR_c, r1
	and	r0, r0, #128	; 0x80
	bx	lr

	arm_func_start OS_RestoreInterrupts
OS_RestoreInterrupts: ; 0x037FB070
	mrs	r1, CPSR
	bic	r2, r1, #128	; 0x80
	orr	r2, r2, r0
	msr	CPSR_c, r2
	and	r0, r1, #128	; 0x80
	bx	lr

	arm_func_start OS_DisableInterrupts_IrqAndFiq
OS_DisableInterrupts_IrqAndFiq: ; 0x037FB088
	mrs	r0, CPSR
	orr	r1, r0, #192	; 0xc0
	msr	CPSR_c, r1
	and	r0, r0, #192	; 0xc0
	bx	lr

	arm_func_start OS_RestoreInterrupts_IrqAndFiq
OS_RestoreInterrupts_IrqAndFiq: ; 0x037FB09C
	mrs	r1, CPSR
	bic	r2, r1, #192	; 0xc0
	orr	r2, r2, r0
	msr	CPSR_c, r2
	and	r0, r1, #192	; 0xc0
	bx	lr

	arm_func_start OS_GetProcMode
OS_GetProcMode: ; 0x037FB0B4
	mrs	r0, CPSR
	and	r0, r0, #31
	bx	lr

	arm_func_start OS_SpinWait
OS_SpinWait: ; 0x037FB0C0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r1, #4
	bl	_s32_div_f
	bl	FUN_037F8CB4
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start OS_ResetSystem
OS_ResetSystem: ; 0x037FB0E0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #0
	bl	MI_StopDma
	mov	r0, #1
	bl	MI_StopDma
	mov	r0, #2
	bl	MI_StopDma
	mov	r0, #3
	bl	MI_StopDma
	mov	r0, #262144	; 0x40000
	bl	OS_SetIrqMask
	mvn	r0, #0
	bl	OS_ResetRequestIrqMask
	bl	SND_Shutdown
	mov	r0, #16
	bl	FUN_037FB134
	bl	FUN_038073EC
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start FUN_037FB134
FUN_037FB134: ; 0x037FB134
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0, lsl #8
	mov	r5, #12
	mov	r4, #0
_037FB144:
	mov	r0, r5
	mov	r1, r6
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	bne	_037FB144
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start FUN_037FB164
FUN_037FB164: ; 0x037FB164
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	and	r0, r1, #32512	; 0x7f00
	mov	r0, r0, lsl #8
	mov	r0, r0, lsr #16
	cmp	r0, #16
	moveq	r1, #1
	ldreq	r0, _037FB19C	; =_03807954
	streqh	r1, [r0]
	beq	_037FB190
	bl	FUN_037FB1F0
_037FB190:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FB19C:	.word	_03807954

	arm_func_start OS_IsResetOccurred
OS_IsResetOccurred: ; 0x037FB1A0
	ldr	r0, _037FB1AC	; =_03807954
	ldrh	r0, [r0]
	bx	lr
_037FB1AC:	.word	_03807954

	arm_func_start OS_InitReset
OS_InitReset: ; 0x037FB1B0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037FB1E8	; =_03807950
	ldrh	r1, [r0]
	cmp	r1, #0
	bne	_037FB1DC
	mov	r1, #1
	strh	r1, [r0]
	mov	r0, #12
	ldr	r1, _037FB1EC	; =FUN_037FB164
	bl	PXI_SetFifoRecvCallback
_037FB1DC:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FB1E8:	.word	_03807950
_037FB1EC:	.word	FUN_037FB164

	arm_func_start FUN_037FB1F0
FUN_037FB1F0: ; 0x037FB1F0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #0
	bl	CTRDG_VibPulseEdgeUpdate
_037FB200:
	bl	OS_DisableInterrupts
	bl	FUN_037F8530
	b	_037FB200

	arm_func_start MI_StopDma
MI_StopDma: ; 0x037FB20C
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	bl	OS_DisableInterrupts
	mov	r1, #6
	mul	r1, r4, r1
	add	r1, r1, #5
	mov	r1, r1, lsl #1
	add	r1, r1, #67108864	; 0x4000000
	ldrh	r2, [r1, #176]	; 0xb0
	bic	r2, r2, #12800	; 0x3200
	strh	r2, [r1, #176]	; 0xb0
	ldrh	r2, [r1, #176]	; 0xb0
	bic	r2, r2, #32768	; 0x8000
	strh	r2, [r1, #176]	; 0xb0
	ldrh	r2, [r1, #176]	; 0xb0
	ldrh	r1, [r1, #176]	; 0xb0
	cmp	r4, #0
	bne	_037FB27C
	mov	r1, #12
	mul	r3, r4, r1
	ldr	r1, _037FB288	; =0x040000B0
	add	r4, r3, r1
	mov	r2, #0
	add	r1, r3, #67108864	; 0x4000000
	str	r2, [r1, #176]	; 0xb0
	str	r2, [r4, #4]
	ldr	r1, _037FB28C	; =0x81400001
	str	r1, [r4, #8]
_037FB27C:
	bl	OS_RestoreInterrupts
	ldmia	sp!, {r4, lr}
	bx	lr
_037FB288:	.word	0x040000B0
_037FB28C:	.word	0x81400001

	arm_func_start MI_WaitDma
MI_WaitDma: ; 0x037FB290
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	bl	OS_DisableInterrupts
	mov	r1, #3
	mul	r1, r4, r1
	add	r2, r1, #2
	ldr	r1, _037FB2F8	; =0x040000B0
	add	r2, r1, r2, lsl #2
_037FB2B0:
	ldr	r1, [r2]
	ands	r1, r1, #-2147483648	; 0x80000000
	bne	_037FB2B0
	cmp	r4, #0
	bne	_037FB2EC
	mov	r1, #12
	mul	r3, r4, r1
	ldr	r1, _037FB2F8	; =0x040000B0
	add	r4, r3, r1
	mov	r2, #0
	add	r1, r3, #67108864	; 0x4000000
	str	r2, [r1, #176]	; 0xb0
	str	r2, [r4, #4]
	ldr	r1, _037FB2FC	; =0x81400001
	str	r1, [r4, #8]
_037FB2EC:
	bl	OS_RestoreInterrupts
	ldmia	sp!, {r4, lr}
	bx	lr
_037FB2F8:	.word	0x040000B0
_037FB2FC:	.word	0x81400001

	arm_func_start MIi_CpuClear16
MIi_CpuClear16: ; 0x037FB300
	mov	r3, #0
_037FB304:
	cmp	r3, r2
	strlth	r0, [r1, r3]
	addlt	r3, r3, #2
	blt	_037FB304
	bx	lr

	arm_func_start MIi_CpuCopy16
MIi_CpuCopy16: ; 0x037FB318
	mov	ip, #0
_037FB31C:
	cmp	ip, r2
	ldrlth	r3, [r0, ip]
	strlth	r3, [r1, ip]
	addlt	ip, ip, #2
	blt	_037FB31C
	bx	lr

	arm_func_start MIi_CpuClear32
MIi_CpuClear32: ; 0x037FB334
	add	ip, r1, r2
_037FB338:
	cmp	r1, ip
	stmltia	r1!, {r0}
	blt	_037FB338
	bx	lr

	arm_func_start MIi_CpuCopy32
MIi_CpuCopy32: ; 0x037FB348
	add	ip, r1, r2
_037FB34C:
	cmp	r1, ip
	ldmltia	r0!, {r2}
	stmltia	r1!, {r2}
	blt	_037FB34C
	bx	lr

	arm_func_start MIi_CpuClearFast
MIi_CpuClearFast: ; 0x037FB360
	stmdb	sp!, {r4, r5, r6, r7, r8, r9}
	add	r9, r1, r2
	mov	ip, r2, lsr #5
	add	ip, r1, ip, lsl #5
	mov	r2, r0
	mov	r3, r2
	mov	r4, r2
	mov	r5, r2
	mov	r6, r2
	mov	r7, r2
	mov	r8, r2
_037FB38C:
	cmp	r1, ip
	stmltia	r1!, {r0, r2, r3, r4, r5, r6, r7, r8}
	blt	_037FB38C
_037FB398:
	cmp	r1, r9
	stmltia	r1!, {r0}
	blt	_037FB398
	ldmia	sp!, {r4, r5, r6, r7, r8, r9}
	bx	lr

	arm_func_start MIi_CpuCopyFast
MIi_CpuCopyFast: ; 0x037FB3AC
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl}
	add	sl, r1, r2
	mov	ip, r2, lsr #5
	add	ip, r1, ip, lsl #5
_037FB3BC:
	cmp	r1, ip
	ldmltia	r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
	stmltia	r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
	blt	_037FB3BC
_037FB3CC:
	cmp	r1, sl
	ldmltia	r0!, {r2}
	stmltia	r1!, {r2}
	blt	_037FB3CC
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl}
	bx	lr

	arm_func_start MI_CpuFill8
MI_CpuFill8: ; 0x037FB3E4
	cmp	r2, #0
	bxeq	lr
	tst	r0, #1
	beq	_037FB410
	ldrh	ip, [r0, #-1]
	and	ip, ip, #255	; 0xff
	orr	r3, ip, r1, lsl #8
	strh	r3, [r0, #-1]
	add	r0, r0, #1
	subs	r2, r2, #1
	bxeq	lr
_037FB410:
	cmp	r2, #2
	bcc	_037FB458
	orr	r1, r1, r1, lsl #8
	tst	r0, #2
	beq	_037FB430
	strh	r1, [r0], #2
	subs	r2, r2, #2
	bxeq	lr
_037FB430:
	orr	r1, r1, r1, lsl #16
	bics	r3, r2, #3
	beq	_037FB450
	sub	r2, r2, r3
	add	ip, r3, r0
_037FB444:
	str	r1, [r0], #4
	cmp	r0, ip
	bcc	_037FB444
_037FB450:
	tst	r2, #2
	strneh	r1, [r0], #2
_037FB458:
	tst	r2, #1
	bxeq	lr
	ldrh	r3, [r0]
	and	r3, r3, #65280	; 0xff00
	and	r1, r1, #255	; 0xff
	orr	r1, r1, r3
	strh	r1, [r0]
	bx	lr

	arm_func_start MI_CpuCopy8
MI_CpuCopy8: ; 0x037FB478
	cmp	r2, #0
	bxeq	lr
	tst	r1, #1
	beq	_037FB4B8
	ldrh	ip, [r1, #-1]
	and	ip, ip, #255	; 0xff
	tst	r0, #1
	ldrneh	r3, [r0, #-1]
	movne	r3, r3, lsr #8
	ldreqh	r3, [r0]
	orr	r3, ip, r3, lsl #8
	strh	r3, [r1, #-1]
	add	r0, r0, #1
	add	r1, r1, #1
	subs	r2, r2, #1
	bxeq	lr
_037FB4B8:
	eor	ip, r1, r0
	tst	ip, #1
	beq	_037FB50C
	bic	r0, r0, #1
	ldrh	ip, [r0], #2
	mov	r3, ip, lsr #8
	subs	r2, r2, #2
	bcc	_037FB4F0
_037FB4D8:
	ldrh	ip, [r0], #2
	orr	ip, r3, ip, lsl #8
	strh	ip, [r1], #2
	mov	r3, ip, lsr #16
	subs	r2, r2, #2
	bcs	_037FB4D8
_037FB4F0:
	tst	r2, #1
	bxeq	lr
	ldrh	ip, [r1]
	and	ip, ip, #65280	; 0xff00
	orr	ip, ip, r3
	strh	ip, [r1]
	bx	lr
_037FB50C:
	tst	ip, #2
	beq	_037FB538
	bics	r3, r2, #1
	beq	_037FB584
	sub	r2, r2, r3
	add	ip, r3, r1
_037FB524:
	ldrh	r3, [r0], #2
	strh	r3, [r1], #2
	cmp	r1, ip
	bcc	_037FB524
	b	_037FB584
_037FB538:
	cmp	r2, #2
	bcc	_037FB584
	tst	r1, #2
	beq	_037FB558
	ldrh	r3, [r0], #2
	strh	r3, [r1], #2
	subs	r2, r2, #2
	bxeq	lr
_037FB558:
	bics	r3, r2, #3
	beq	_037FB578
	sub	r2, r2, r3
	add	ip, r3, r1
_037FB568:
	ldr	r3, [r0], #4
	str	r3, [r1], #4
	cmp	r1, ip
	bcc	_037FB568
_037FB578:
	tst	r2, #2
	ldrneh	r3, [r0], #2
	strneh	r3, [r1], #2
_037FB584:
	tst	r2, #1
	bxeq	lr
	ldrh	r2, [r1]
	ldrh	r0, [r0]
	and	r2, r2, #65280	; 0xff00
	and	r0, r0, #255	; 0xff
	orr	r0, r2, r0
	strh	r0, [r1]
	bx	lr

	arm_func_start MI_SwapWord
MI_SwapWord: ; 0x037FB5A8
	swp	r0, r0, [r1]
	bx	lr

	arm_func_start PXI_Init
PXI_Init: ; 0x037FB5B0
	ldr	ip, _037FB5B8	; =PXI_InitFifo
	bx	ip
_037FB5B8:	.word	PXI_InitFifo

	arm_func_start PXIi_HandlerRecvFifoNotEmpty
PXIi_HandlerRecvFifoNotEmpty: ; 0x037FB5BC
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	sub	sp, sp, #8
	ldr	sl, _037FB6D0	; =0x04000184
	ldr	r5, _037FB6D4	; =_0380795C
	mov	r7, #68157440	; 0x4100000
	mov	r6, #0
	mvn	r8, #3
	mvn	r9, #2
	ldr	r4, _037FB6D8	; =0x04000188
_037FB5E0:
	ldrh	r0, [sl]
	ands	r0, r0, #16384	; 0x4000
	ldrneh	r0, [sl]
	orrne	r0, r0, #49152	; 0xc000
	strneh	r0, [sl]
	movne	r1, r9
	bne	_037FB628
	bl	OS_DisableInterrupts
	ldrh	r1, [sl]
	ands	r1, r1, #256	; 0x100
	beq	_037FB618
	bl	OS_RestoreInterrupts
	mov	r1, r8
	b	_037FB628
_037FB618:
	ldr	r1, [r7]
	str	r1, [sp]
	bl	OS_RestoreInterrupts
	mov	r1, r6
_037FB628:
	cmp	r1, r8
	beq	_037FB6C4
	mvn	r0, #2
	cmp	r1, r0
	beq	_037FB5E0
	ldr	r2, [sp]
	mov	r0, r2, lsl #27
	movs	r0, r0, lsr #27
	beq	_037FB5E0
	ldr	r3, [r5, r0, lsl #2]
	cmp	r3, #0
	beq	_037FB670
	mov	r1, r2, lsr #6
	mov	r2, r2, lsl #26
	mov	r2, r2, lsr #31
	mov	lr, pc
	bx	r3
	b	_037FB5E0
_037FB670:
	mov	r0, r2, lsl #26
	movs	r0, r0, lsr #31
	bne	_037FB5E0
	orr	r0, r2, #32
	str	r0, [sp]
	ldrh	r0, [sl]
	ands	r0, r0, #16384	; 0x4000
	ldrneh	r0, [sl]
	orrne	r0, r0, #49152	; 0xc000
	strneh	r0, [sl]
	bne	_037FB5E0
	bl	OS_DisableInterrupts
	ldrh	r1, [sl]
	ands	r1, r1, #2
	beq	_037FB6B4
	bl	OS_RestoreInterrupts
	b	_037FB5E0
_037FB6B4:
	ldr	r1, [sp]
	str	r1, [r4]
	bl	OS_RestoreInterrupts
	b	_037FB5E0
_037FB6C4:
	add	sp, sp, #8
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	bx	lr
_037FB6D0:	.word	0x04000184
_037FB6D4:	.word	_0380795C
_037FB6D8:	.word	0x04000188

	arm_func_start PXI_SendWordByFifo
PXI_SendWordByFifo: ; 0x037FB6DC
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r3, [sp]
	bic	r3, r3, #31
	and	r0, r0, #31
	orr	r0, r3, r0
	str	r0, [sp]
	bic	r3, r0, #32
	and	r0, r2, #1
	orr	r0, r3, r0, lsl #5
	str	r0, [sp]
	and	r2, r0, #63	; 0x3f
	bic	r0, r1, #-67108864	; 0xfc000000
	orr	r0, r2, r0, lsl #6
	str	r0, [sp]
	ldr	r1, _037FB778	; =0x04000184
	ldrh	r0, [r1]
	ands	r0, r0, #16384	; 0x4000
	ldrneh	r0, [r1]
	orrne	r0, r0, #49152	; 0xc000
	strneh	r0, [r1]
	mvnne	r0, #0
	bne	_037FB76C
	bl	OS_DisableInterrupts
	ldr	r1, _037FB778	; =0x04000184
	ldrh	r1, [r1]
	ands	r1, r1, #2
	beq	_037FB758
	bl	OS_RestoreInterrupts
	mvn	r0, #1
	b	_037FB76C
_037FB758:
	ldr	r2, [sp]
	ldr	r1, _037FB77C	; =0x04000188
	str	r2, [r1]
	bl	OS_RestoreInterrupts
	mov	r0, #0
_037FB76C:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FB778:	.word	0x04000184
_037FB77C:	.word	0x04000188

	arm_func_start PXI_IsCallbackReady
PXI_IsCallbackReady: ; 0x037FB780
	mov	r3, #1
	mov	r2, r3, lsl r0
	ldr	r0, _037FB7A4	; =0x027FFC00
	add	r0, r0, r1, lsl #2
	ldr	r0, [r0, #904]	; 0x388
	ands	r0, r2, r0
	moveq	r3, #0
	mov	r0, r3
	bx	lr
_037FB7A4:	.word	0x027FFC00

	arm_func_start PXI_SetFifoRecvCallback
PXI_SetFifoRecvCallback: ; 0x037FB7A8
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r4, r0
	mov	r5, r1
	bl	OS_DisableInterrupts
	ldr	r1, _037FB80C	; =_0380795C
	str	r5, [r1, r4, lsl #2]
	cmp	r5, #0
	beq	_037FB7E4
	ldr	r3, _037FB810	; =0x027FFC00
	ldr	r2, [r3, #908]	; 0x38c
	mov	r1, #1
	orr	r1, r2, r1, lsl r4
	str	r1, [r3, #908]	; 0x38c
	b	_037FB7FC
_037FB7E4:
	ldr	r3, _037FB810	; =0x027FFC00
	ldr	r2, [r3, #908]	; 0x38c
	mov	r1, #1
	mvn	r1, r1, lsl r4
	and	r1, r2, r1
	str	r1, [r3, #908]	; 0x38c
_037FB7FC:
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FB80C:	.word	_0380795C
_037FB810:	.word	0x027FFC00

	arm_func_start PXI_InitFifo
PXI_InitFifo: ; 0x037FB814
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	bl	OS_DisableInterrupts
	mov	r5, r0
	ldr	r0, _037FB8D4	; =_03807958
	ldrh	r1, [r0]
	cmp	r1, #0
	bne	_037FB8C4
	mov	r1, #1
	strh	r1, [r0]
	mov	r2, #0
	ldr	r0, _037FB8D8	; =0x027FFC00
	str	r2, [r0, #908]	; 0x38c
	mov	r1, r2
	ldr	r0, _037FB8DC	; =_0380795C
_037FB84C:
	str	r1, [r0, r2, lsl #2]
	add	r2, r2, #1
	cmp	r2, #32
	blt	_037FB84C
	ldr	r1, _037FB8E0	; =0x0000C408
	ldr	r0, _037FB8E4	; =0x04000184
	strh	r1, [r0]
	mov	r0, #262144	; 0x40000
	bl	OS_ResetRequestIrqMask
	mov	r0, #262144	; 0x40000
	ldr	r1, _037FB8E8	; =PXIi_HandlerRecvFifoNotEmpty
	bl	OS_SetIrqFunction
	mov	r0, #262144	; 0x40000
	bl	OS_EnableIrqMask
	mov	r4, #8
	mov	r6, r4
	ldr	r8, _037FB8EC	; =0x04000180
	mov	r7, #1000	; 0x3e8
	b	_037FB8BC
_037FB898:
	mov	r0, r4, lsl #8
	strh	r0, [r8]
	mov	r0, r7
	bl	OS_SpinWait
	ldrh	r0, [r8]
	and	r0, r0, #15
	cmp	r0, r4
	movne	r4, r6
	sub	r4, r4, #1
_037FB8BC:
	cmp	r4, #0
	bge	_037FB898
_037FB8C4:
	mov	r0, r5
	bl	OS_RestoreInterrupts
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FB8D4:	.word	_03807958
_037FB8D8:	.word	0x027FFC00
_037FB8DC:	.word	_0380795C
_037FB8E0:	.word	0x0000C408
_037FB8E4:	.word	0x04000184
_037FB8E8:	.word	PXIi_HandlerRecvFifoNotEmpty
_037FB8EC:	.word	0x04000180

	arm_func_start EXIi_SelectRcnt
EXIi_SelectRcnt: ; 0x037FB8F0
	mov	r1, r0
	mov	r0, #49152	; 0xc000
	mov	r1, r1, lsl #16
	mov	r1, r1, lsr #16
	ldr	ip, _037FB908	; =EXIi_SetBitRcnt0L
	bx	ip
_037FB908:	.word	EXIi_SetBitRcnt0L

	arm_func_start EXIi_SetBitRcnt0L
EXIi_SetBitRcnt0L: ; 0x037FB90C
	mvn	r3, r0
	ldr	r2, _037FB928	; =0x04000134
	ldrh	r0, [r2]
	and	r0, r3, r0
	orr	r0, r1, r0
	strh	r0, [r2]
	bx	lr
_037FB928:	.word	0x04000134

	arm_func_start FUN_037FB92C
FUN_037FB92C: ; 0x037FB92C
	stmdb	sp!, {r4, lr}
	mov	r4, #0
	mov	r0, #32768	; 0x8000
	bl	EXIi_SelectRcnt
	ldr	r0, _037FB964	; =0x04000136
	ldrh	r1, [r0]
	ands	r0, r1, #128	; 0x80
	movne	r4, #32768	; 0x8000
	and	r0, r1, #11
	orr	r1, r4, r0, lsl #10
	ldr	r0, _037FB968	; =0x027FFFA8
	strh	r1, [r0]
	ldmia	sp!, {r4, lr}
	bx	lr
_037FB964:	.word	0x04000136
_037FB968:	.word	0x027FFFA8

	arm_func_start PAD_InitXYButton
PAD_InitXYButton: ; 0x037FB96C
	stmfd	sp!, {lr}
	sub	sp, sp, #12
	bl	OS_IsTickAvailable
	cmp	r0, #0
	beq	_037FB98C
	bl	OS_IsAlarmAvailable
	cmp	r0, #0
	bne	_037FB994
_037FB98C:
	mov	r0, #0
	b	_037FB9F0
_037FB994:
	ldr	r0, _037FB9FC	; =PADi_XYButtonAvailable
	ldr	r0, [r0]
	cmp	r0, #0
	movne	r0, #0
	bne	_037FB9F0
	ldr	r0, _037FBA00	; =_038079E0
	bl	OS_CreateAlarm
	bl	OS_GetTick
	mov	r2, r0
	ldr	r0, _037FBA04	; =FUN_037FB92C
	str	r0, [sp, #4]
	mov	r0, #0
	str	r0, [sp, #8]
	ldr	r3, _037FBA08	; =0x0000082E
	str	r0, [sp]
	ldr	r0, _037FBA00	; =_038079E0
	adds	ip, r2, r3
	adc	r2, r1, #0
	mov	r1, ip
	bl	OS_SetPeriodicAlarm
	mov	r0, #1
	ldr	r1, _037FB9FC	; =PADi_XYButtonAvailable
	str	r0, [r1]
_037FB9F0:
	add	sp, sp, #12
	ldmia	sp!, {lr}
	bx	lr
_037FB9FC:	.word	PADi_XYButtonAvailable
_037FBA00:	.word	_038079E0
_037FBA04:	.word	FUN_037FB92C
_037FBA08:	.word	0x0000082E

	arm_func_start SND_SetOutputSelector
SND_SetOutputSelector: ; 0x037FBA0C
	ldr	ip, _037FBA40	; =0x04000501
	ldrb	ip, [ip]
	ands	ip, ip, #128	; 0x80
	movne	ip, #1
	moveq	ip, #0
	mov	ip, ip, lsl #7
	orr	r3, ip, r3, lsl #5
	orr	r2, r3, r2, lsl #4
	orr	r1, r2, r1, lsl #2
	orr	r1, r0, r1
	ldr	r0, _037FBA40	; =0x04000501
	strb	r1, [r0]
	bx	lr
_037FBA40:	.word	0x04000501

	arm_func_start SND_SetMasterVolume
SND_SetMasterVolume: ; 0x037FBA44
	ldr	r1, _037FBA50	; =0x04000500
	strb	r0, [r1]
	bx	lr
_037FBA50:	.word	0x04000500

	arm_func_start SND_EndSleep
SND_EndSleep: ; 0x037FBA54
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _037FBA94	; =0x04000304
	ldrh	r0, [r1]
	orr	r0, r0, #1
	strh	r0, [r1]
	mov	r0, #1
	bl	PMi_SetControl
	mov	r0, #256	; 0x100
	bl	FUN_037FBA9C
	ldr	r0, _037FBA98	; =0x0007AB80
	bl	OS_SpinWait
	bl	SND_Enable
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FBA94:	.word	0x04000304
_037FBA98:	.word	0x0007AB80

	arm_func_start FUN_037FBA9C
FUN_037FBA9C: ; 0x037FBA9C
	ldr	ip, _037FBAA4	; =SVC_SoundBiasSet
	bx	ip
_037FBAA4:	.word	SVC_SoundBiasSet

	arm_func_start SND_BeginSleep
SND_BeginSleep: ; 0x037FBAA8
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	bl	SND_Disable
	mov	r0, #128	; 0x80
	bl	FUN_037FBAEC
	mov	r0, #262144	; 0x40000
	bl	OS_SpinWait
	mov	r0, #1
	bl	PMi_ResetControl
	ldr	r1, _037FBAE8	; =0x04000304
	ldrh	r0, [r1]
	bic	r0, r0, #1
	strh	r0, [r1]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FBAE8:	.word	0x04000304

	arm_func_start FUN_037FBAEC
FUN_037FBAEC: ; 0x037FBAEC
	ldr	ip, _037FBAF4	; =SVC_SoundBiasReset
	bx	ip
_037FBAF4:	.word	SVC_SoundBiasReset

	arm_func_start SND_Shutdown
SND_Shutdown: ; 0x037FBAF8
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	bl	SND_Disable
	mov	r5, #0
	mov	r4, #1
_037FBB0C:
	mov	r0, r5
	mov	r1, r4
	bl	SND_StopChannel
	add	r5, r5, #1
	cmp	r5, #16
	blt	_037FBB0C
	mov	r1, #0
	ldr	r0, _037FBB44	; =0x04000508
	strb	r1, [r0]
	ldr	r0, _037FBB48	; =0x04000509
	strb	r1, [r0]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FBB44:	.word	0x04000508
_037FBB48:	.word	0x04000509

	arm_func_start SND_Disable
SND_Disable: ; 0x037FBB4C
	ldr	r1, _037FBB60	; =0x04000501
	ldrb	r0, [r1]
	bic	r0, r0, #128	; 0x80
	strb	r0, [r1]
	bx	lr
_037FBB60:	.word	0x04000501

	arm_func_start SND_Enable
SND_Enable: ; 0x037FBB64
	ldr	r1, _037FBB78	; =0x04000501
	ldrb	r0, [r1]
	orr	r0, r0, #128	; 0x80
	strb	r0, [r1]
	bx	lr
_037FBB78:	.word	0x04000501

	arm_func_start CalcSurroundDecay
CalcSurroundDecay: ; 0x037FBB7C
	cmp	r1, #24
	bge	_037FBBAC
	ldr	r2, _037FBBE0	; =sSurroundDecay
	ldr	r3, [r2]
	ldr	r2, _037FBBE4	; =0x00007FFF
	sub	r2, r2, r3
	add	r1, r1, #40	; 0x28
	mul	r1, r3, r1
	add	r1, r1, r2, lsl #6
	mul	r1, r0, r1
	mov	r0, r1, asr #21
	bx	lr
_037FBBAC:
	cmp	r1, #104	; 0x68
	bxle	lr
	ldr	r2, _037FBBE0	; =sSurroundDecay
	ldr	ip, [r2]
	ldr	r2, _037FBBE4	; =0x00007FFF
	add	r3, ip, r2
	rsb	r2, ip, #0
	sub	r1, r1, #40	; 0x28
	mul	r1, r2, r1
	add	r1, r1, r3, lsl #6
	mul	r1, r0, r1
	mov	r0, r1, asr #21
	bx	lr
_037FBBE0:	.word	sSurroundDecay
_037FBBE4:	.word	0x00007FFF

	arm_func_start SNDi_SetSurroundDecay
SNDi_SetSurroundDecay: ; 0x037FBBE8
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	ldr	r1, _037FBC40	; =sSurroundDecay
	str	r0, [r1]
	mov	r4, #0
	ldr	r6, _037FBC44	; =sOrgVolume
	mov	r7, #1
	ldr	r5, _037FBC48	; =0x0000FFF5
_037FBC04:
	mov	r0, r7, lsl r4
	ands	r0, r0, r5
	beq	_037FBC2C
	mov	r8, r4, lsl #4
	add	r0, r8, #67108864	; 0x4000000
	ldrb	r1, [r0, #1026]	; 0x402
	ldrb	r0, [r6, r4]
	bl	CalcSurroundDecay
	add	r1, r8, #67108864	; 0x4000000
	strb	r0, [r1, #1024]	; 0x400
_037FBC2C:
	add	r4, r4, #1
	cmp	r4, #16
	blt	_037FBC04
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FBC40:	.word	sSurroundDecay
_037FBC44:	.word	sOrgVolume
_037FBC48:	.word	0x0000FFF5

	arm_func_start SND_GetChannelControl
SND_GetChannelControl: ; 0x037FBC4C
	mov	r0, r0, lsl #4
	add	r0, r0, #67108864	; 0x4000000
	ldr	r0, [r0, #1024]	; 0x400
	bx	lr

	arm_func_start SND_SetMasterPan
SND_SetMasterPan: ; 0x037FBC5C
	ldr	r1, _037FBCB8	; =sMasterPan
	str	r0, [r1]
	cmp	r0, #0
	blt	_037FBC90
	mov	r2, #0
	and	r1, r0, #255	; 0xff
_037FBC74:
	mov	r0, r2, lsl #4
	add	r0, r0, #67108864	; 0x4000000
	strb	r1, [r0, #1026]	; 0x402
	add	r2, r2, #1
	cmp	r2, #16
	blt	_037FBC74
	bx	lr
_037FBC90:
	mov	r3, #0
	ldr	r2, _037FBCBC	; =sOrgPan
_037FBC98:
	ldrb	r1, [r2, r3]
	mov	r0, r3, lsl #4
	add	r0, r0, #67108864	; 0x4000000
	strb	r1, [r0, #1026]	; 0x402
	add	r3, r3, #1
	cmp	r3, #16
	blt	_037FBC98
	bx	lr
_037FBCB8:	.word	sMasterPan
_037FBCBC:	.word	sOrgPan

	arm_func_start SND_IsChannelActive
SND_IsChannelActive: ; 0x037FBCC0
	mov	r0, r0, lsl #4
	add	r0, r0, #67108864	; 0x4000000
	ldrb	r0, [r0, #1027]	; 0x403
	ands	r0, r0, #128	; 0x80
	movne	r0, #1
	moveq	r0, #0
	bx	lr

	arm_func_start SND_SetChannelPan
SND_SetChannelPan: ; 0x037FBCDC
	stmdb	sp!, {r4, lr}
	ldr	r2, _037FBD44	; =sOrgPan
	strb	r1, [r2, r0]
	ldr	r2, _037FBD48	; =sMasterPan
	ldr	r2, [r2]
	cmp	r2, #0
	movge	r1, r2
	mov	r4, r0, lsl #4
	add	r2, r4, #67108864	; 0x4000000
	strb	r1, [r2, #1026]	; 0x402
	ldr	r2, _037FBD4C	; =sSurroundDecay
	ldr	r2, [r2]
	cmp	r2, #0
	ble	_037FBD3C
	mov	r2, #1
	mov	r3, r2, lsl r0
	ldr	r2, _037FBD50	; =0x0000FFF5
	ands	r2, r3, r2
	beq	_037FBD3C
	ldr	r2, _037FBD54	; =sOrgVolume
	ldrb	r0, [r2, r0]
	bl	CalcSurroundDecay
	add	r1, r4, #67108864	; 0x4000000
	strb	r0, [r1, #1024]	; 0x400
_037FBD3C:
	ldmia	sp!, {r4, lr}
	bx	lr
_037FBD44:	.word	sOrgPan
_037FBD48:	.word	sMasterPan
_037FBD4C:	.word	sSurroundDecay
_037FBD50:	.word	0x0000FFF5
_037FBD54:	.word	sOrgVolume

	arm_func_start SND_SetChannelTimer
SND_SetChannelTimer: ; 0x037FBD58
	rsb	r1, r1, #65536	; 0x10000
	mov	r0, r0, lsl #4
	add	r0, r0, #67108864	; 0x4000000
	add	r0, r0, #1024	; 0x400
	strh	r1, [r0, #8]
	bx	lr

	arm_func_start SND_SetChannelVolume
SND_SetChannelVolume: ; 0x037FBD70
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, r2
	ldr	r0, _037FBDE8	; =sOrgVolume
	strb	r1, [r0, r5]
	ldr	r0, _037FBDEC	; =sSurroundDecay
	ldr	r0, [r0]
	cmp	r0, #0
	ble	_037FBDC8
	mov	r0, #1
	mov	r2, r0, lsl r5
	ldr	r0, _037FBDF0	; =0x0000FFF5
	ands	r0, r2, r0
	beq	_037FBDC8
	mov	r0, r5, lsl #4
	add	r0, r0, #67108864	; 0x4000000
	ldrb	r2, [r0, #1026]	; 0x402
	mov	r0, r1
	mov	r1, r2
	bl	CalcSurroundDecay
	mov	r1, r0
_037FBDC8:
	orr	r1, r1, r4, lsl #8
	mov	r0, r5, lsl #4
	add	r0, r0, #67108864	; 0x4000000
	add	r0, r0, #1024	; 0x400
	strh	r1, [r0]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FBDE8:	.word	sOrgVolume
_037FBDEC:	.word	sSurroundDecay
_037FBDF0:	.word	0x0000FFF5

	arm_func_start SND_StopChannel
SND_StopChannel: ; 0x037FBDF4
	mov	r3, r0, lsl #4
	ldr	r2, _037FBE1C	; =0x04000400
	add	ip, r2, r0, lsl #4
	add	r0, r3, #67108864	; 0x4000000
	ldr	r0, [r0, #1024]	; 0x400
	bic	r2, r0, #-2147483648	; 0x80000000
	ands	r0, r1, #1
	orrne	r2, r2, #32768	; 0x8000
	str	r2, [ip]
	bx	lr
_037FBE1C:	.word	0x04000400

	arm_func_start SND_SetupChannelNoise
SND_SetupChannelNoise: ; 0x037FBE20
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r2
	mov	r6, r3
	ldr	r5, [sp, #24]
	mov	r4, r0, lsl #4
	ldr	r2, _037FBEBC	; =sOrgPan
	strb	r5, [r2, r0]
	ldr	r2, _037FBEC0	; =sMasterPan
	ldr	r2, [r2]
	cmp	r2, #0
	movge	r5, r2
	ldr	r2, _037FBEC4	; =sOrgVolume
	strb	r1, [r2, r0]
	ldr	r2, _037FBEC8	; =sSurroundDecay
	ldr	r2, [r2]
	cmp	r2, #0
	ble	_037FBE8C
	mov	r2, #1
	mov	r2, r2, lsl r0
	ldr	r0, _037FBECC	; =0x0000FFF5
	ands	r0, r2, r0
	beq	_037FBE8C
	mov	r0, r1
	mov	r1, r5
	bl	CalcSurroundDecay
	mov	r1, r0
_037FBE8C:
	mov	r0, r5, lsl #16
	orr	r0, r0, #1610612736	; 0x60000000
	orr	r0, r0, r7, lsl #8
	orr	r1, r1, r0
	add	r0, r4, #67108864	; 0x4000000
	str	r1, [r0, #1024]	; 0x400
	rsb	r1, r6, #65536	; 0x10000
	add	r0, r0, #1024	; 0x400
	strh	r1, [r0, #8]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FBEBC:	.word	sOrgPan
_037FBEC0:	.word	sMasterPan
_037FBEC4:	.word	sOrgVolume
_037FBEC8:	.word	sSurroundDecay
_037FBECC:	.word	0x0000FFF5

	arm_func_start SND_SetupChannelPsg
SND_SetupChannelPsg: ; 0x037FBED0
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r1
	mov	r6, r3
	ldr	r5, [sp, #28]
	mov	r4, r0, lsl #4
	ldr	r1, _037FBF74	; =sOrgPan
	strb	r5, [r1, r0]
	ldr	r1, _037FBF78	; =sMasterPan
	ldr	r1, [r1]
	cmp	r1, #0
	movge	r5, r1
	ldr	r1, _037FBF7C	; =sOrgVolume
	strb	r2, [r1, r0]
	ldr	r1, _037FBF80	; =sSurroundDecay
	ldr	r1, [r1]
	cmp	r1, #0
	ble	_037FBF3C
	mov	r1, #1
	mov	r1, r1, lsl r0
	ldr	r0, _037FBF84	; =0x0000FFF5
	ands	r0, r1, r0
	beq	_037FBF3C
	mov	r0, r2
	mov	r1, r5
	bl	CalcSurroundDecay
	mov	r2, r0
_037FBF3C:
	mov	r0, r7, lsl #24
	orr	r0, r0, #1610612736	; 0x60000000
	orr	r0, r0, r5, lsl #16
	orr	r0, r0, r6, lsl #8
	orr	r1, r2, r0
	add	r0, r4, #67108864	; 0x4000000
	str	r1, [r0, #1024]	; 0x400
	ldr	r1, [sp, #24]
	rsb	r1, r1, #65536	; 0x10000
	add	r0, r0, #1024	; 0x400
	strh	r1, [r0, #8]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FBF74:	.word	sOrgPan
_037FBF78:	.word	sMasterPan
_037FBF7C:	.word	sOrgVolume
_037FBF80:	.word	sSurroundDecay
_037FBF84:	.word	0x0000FFF5

	arm_func_start SND_SetupChannelPcm
SND_SetupChannelPcm: ; 0x037FBF88
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r8, r1
	mov	r7, r2
	mov	r6, r3
	ldr	r1, [sp, #32]
	ldr	r5, [sp, #44]	; 0x2c
	mov	r4, r0, lsl #4
	ldr	r2, _037FC044	; =sOrgPan
	strb	r5, [r2, r0]
	ldr	r2, _037FC048	; =sMasterPan
	ldr	r2, [r2]
	cmp	r2, #0
	movge	r5, r2
	ldr	r2, _037FC04C	; =sOrgVolume
	strb	r1, [r2, r0]
	ldr	r2, _037FC050	; =sSurroundDecay
	ldr	r2, [r2]
	cmp	r2, #0
	ble	_037FBFF8
	mov	r2, #1
	mov	r2, r2, lsl r0
	ldr	r0, _037FC054	; =0x0000FFF5
	ands	r0, r2, r0
	beq	_037FBFF8
	mov	r0, r1
	mov	r1, r5
	bl	CalcSurroundDecay
	mov	r1, r0
_037FBFF8:
	ldr	r2, [sp, #36]	; 0x24
	mov	r0, r7, lsl #29
	orr	r0, r0, r6, lsl #27
	orr	r0, r0, r5, lsl #16
	orr	r0, r0, r2, lsl #8
	orr	r0, r1, r0
	add	r1, r4, #67108864	; 0x4000000
	str	r0, [r1, #1024]	; 0x400
	ldr	r0, [sp, #40]	; 0x28
	rsb	r2, r0, #65536	; 0x10000
	add	r0, r1, #1024	; 0x400
	strh	r2, [r0, #8]
	ldr	r2, [sp, #24]
	strh	r2, [r0, #10]
	ldr	r0, [sp, #28]
	str	r0, [r1, #1036]	; 0x40c
	str	r8, [r1, #1028]	; 0x404
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FC044:	.word	sOrgPan
_037FC048:	.word	sMasterPan
_037FC04C:	.word	sOrgVolume
_037FC050:	.word	sSurroundDecay
_037FC054:	.word	0x0000FFF5

	arm_func_start SND_CalcRandom
SND_CalcRandom: ; 0x037FC058
	ldr	r2, _037FC080	; =_03807660
	ldr	r3, [r2]
	ldr	r0, _037FC084	; =0x0019660D
	ldr	r1, _037FC088	; =0x3C6EF35F
	mla	r0, r3, r0, r1
	str	r0, [r2]
	mov	r0, r0, lsr #16
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	bx	lr
_037FC080:	.word	_03807660
_037FC084:	.word	0x0019660D
_037FC088:	.word	0x3C6EF35F

	arm_func_start SND_SinIdx
SND_SinIdx: ; 0x037FC08C
	cmp	r0, #32
	ldrlt	r1, _037FC0F4	; =_03807170
	ldrltsb	r0, [r1, r0]
	bxlt	lr
	cmp	r0, #64	; 0x40
	rsblt	r1, r0, #64	; 0x40
	ldrlt	r0, _037FC0F4	; =_03807170
	ldrltsb	r0, [r0, r1]
	bxlt	lr
	cmp	r0, #96	; 0x60
	bge	_037FC0D4
	sub	r1, r0, #64	; 0x40
	ldr	r0, _037FC0F4	; =_03807170
	ldrsb	r0, [r0, r1]
	rsb	r0, r0, #0
	mov	r0, r0, lsl #24
	mov	r0, r0, asr #24
	bx	lr
_037FC0D4:
	sub	r0, r0, #96	; 0x60
	rsb	r1, r0, #32
	ldr	r0, _037FC0F4	; =_03807170
	ldrsb	r0, [r0, r1]
	rsb	r0, r0, #0
	mov	r0, r0, lsl #24
	mov	r0, r0, asr #24
	bx	lr
_037FC0F4:	.word	_03807170

	arm_func_start SND_CalcChannelVolume
SND_CalcChannelVolume: ; 0x037FC0F8
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	ldr	r0, _037FC168	; =0xFFFFFD2D
	cmp	r4, r0
	movlt	r4, r0
	blt	_037FC118
	cmp	r4, #0
	movgt	r4, #0
_037FC118:
	ldr	r0, _037FC16C	; =0x000002D3
	add	r0, r4, r0
	bl	FUN_037FC170
	mvn	r1, #239	; 0xef
	cmp	r4, r1
	movlt	r1, #3
	blt	_037FC154
	mvn	r1, #119	; 0x77
	cmp	r4, r1
	movlt	r1, #2
	blt	_037FC154
	mvn	r1, #59	; 0x3b
	cmp	r4, r1
	movlt	r1, #1
	movge	r1, #0
_037FC154:
	orr	r0, r0, r1, lsl #8
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	ldmia	sp!, {r4, lr}
	bx	lr
_037FC168:	.word	0xFFFFFD2D
_037FC16C:	.word	0x000002D3

	arm_func_start FUN_037FC170
FUN_037FC170: ; 0x037FC170
	ldr	ip, _037FC178	; =SVC_GetVolumeTable
	bx	ip
_037FC178:	.word	SVC_GetVolumeTable

	arm_func_start SND_CalcTimer
SND_CalcTimer: ; 0x037FC17C
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, #0
	rsb	r0, r1, #0
	b	_037FC19C
_037FC194:
	sub	r4, r4, #1
	add	r0, r0, #768	; 0x300
_037FC19C:
	cmp	r0, #0
	blt	_037FC194
	b	_037FC1B0
_037FC1A8:
	add	r4, r4, #1
	sub	r0, r0, #768	; 0x300
_037FC1B0:
	cmp	r0, #768	; 0x300
	bge	_037FC1A8
	bl	FUN_037FC2A4
	mov	r2, #0
	mov	r1, #65536	; 0x10000
	adds	lr, r0, r1
	adc	ip, r2, #0
	mov	r3, r5, asr #31
	umull	r1, r0, lr, r5
	mla	r0, lr, r3, r0
	mla	r0, ip, r5, r0
	sub	lr, r4, #16
	cmp	lr, #0
	bgt	_037FC208
	rsb	r2, lr, #0
	mov	r3, r0, lsr r2
	mov	r5, r1, lsr r2
	rsb	r1, r2, #32
	orr	r5, r5, r0, lsl r1
	sub	r1, r2, #32
	orr	r5, r5, r0, lsr r1
	b	_037FC264
_037FC208:
	cmp	lr, #32
	bge	_037FC25C
	mvn	r5, #0
	rsb	r4, lr, #32
	mov	ip, r5, lsl r4
	rsb	r3, r4, #32
	orr	ip, ip, r5, lsr r3
	sub	r3, r4, #32
	orr	ip, ip, r5, lsl r3
	and	r3, r0, ip
	and	r5, r1, r5, lsl r4
	cmp	r3, r2
	cmpeq	r5, r2
	ldrne	r0, _037FC2A0	; =0x0000FFFF
	bne	_037FC294
	mov	r5, r1, lsl lr
	mov	r3, r0, lsl lr
	orr	r3, r3, r1, lsr r4
	sub	r0, lr, #32
	orr	r3, r3, r1, lsl r0
	b	_037FC264
_037FC25C:
	ldr	r0, _037FC2A0	; =0x0000FFFF
	b	_037FC294
_037FC264:
	mov	r1, #0
	mov	r0, #16
	cmp	r3, r1
	cmpeq	r5, r0
	movcc	r5, r0
	bcc	_037FC28C
	ldr	r0, _037FC2A0	; =0x0000FFFF
	cmp	r3, r1
	cmpeq	r5, r0
	movhi	r5, r0
_037FC28C:
	mov	r0, r5, lsl #16
	mov	r0, r0, lsr #16
_037FC294:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FC2A0:	.word	0x0000FFFF

	arm_func_start FUN_037FC2A4
FUN_037FC2A4: ; 0x037FC2A4
	ldr	ip, _037FC2AC	; =SVC_GetPitchTable
	bx	ip
_037FC2AC:	.word	SVC_GetPitchTable

	arm_func_start FUN_037FC2B0
FUN_037FC2B0: ; 0x037FC2B0
	stmdb	sp!, {r4, r5, r6, lr}
	bl	SND_InitIntervalTimer
	bl	SND_ExChannelInit
	bl	SND_SeqInit
	bl	SND_AlarmInit
	bl	SND_Enable
	mov	r0, #0
	mov	r1, r0
	mov	r2, r0
	mov	r3, r0
	bl	SND_SetOutputSelector
	mov	r0, #127	; 0x7f
	bl	SND_SetMasterVolume
	bl	SND_StartIntervalTimer
	mov	r4, #1
	mov	r5, #0
_037FC2F0:
	mov	r6, r5
	bl	SND_WaitForIntervalTimer
	cmp	r0, #1
	beq	_037FC308
	cmp	r0, #2
	b	_037FC30C
_037FC308:
	mov	r6, r4
_037FC30C:
	bl	SND_UpdateExChannel
	bl	SND_CommandProc
	mov	r0, r6
	bl	SND_SeqMain
	mov	r0, r6
	bl	SND_ExChannelMain
	bl	SND_UpdateSharedWork
	bl	SND_CalcRandom
	b	_037FC2F0
_037FC330:
	ldr	r0, _037FC344	; =_03807A54
	mov	r1, #1
	mov	r2, #0
	ldr	ip, _037FC348	; =OS_SendMessage
	bx	ip
_037FC344:	.word	_03807A54
_037FC348:	.word	OS_SendMessage

	arm_func_start SNDi_UnlockMutex
SNDi_UnlockMutex: ; 0x037FC34C
	bx	lr

	arm_func_start SNDi_LockMutex
SNDi_LockMutex: ; 0x037FC350
	bx	lr

	arm_func_start SND_SendWakeupMessage
SND_SendWakeupMessage: ; 0x037FC354
	ldr	r0, _037FC368	; =_03807A54
	mov	r1, #2
	mov	r2, #0
	ldr	ip, _037FC36C	; =OS_SendMessage
	bx	ip
_037FC368:	.word	_03807A54
_037FC36C:	.word	OS_SendMessage

	arm_func_start SND_WaitForIntervalTimer
SND_WaitForIntervalTimer: ; 0x037FC370
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037FC398	; =_03807A54
	add	r1, sp, #0
	mov	r2, #1
	bl	OS_ReceiveMessage
	ldr	r0, [sp]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FC398:	.word	_03807A54

	arm_func_start SND_StopIntervalTimer
SND_StopIntervalTimer: ; 0x037FC39C
	ldr	r0, _037FC3A8	; =_03807A74
	ldr	ip, _037FC3AC	; =OS_CancelAlarm
	bx	ip
_037FC3A8:	.word	_03807A74
_037FC3AC:	.word	OS_CancelAlarm

	arm_func_start SND_StartIntervalTimer
SND_StartIntervalTimer: ; 0x037FC3B0
	stmfd	sp!, {lr}
	sub	sp, sp, #12
	bl	OS_GetTick
	mov	ip, r0
	ldr	r0, _037FC3FC	; =_037FC330
	str	r0, [sp, #4]
	mov	r0, #0
	str	r0, [sp, #8]
	ldr	r3, _037FC400	; =0x00000AA8
	str	r0, [sp]
	ldr	r0, _037FC404	; =_03807A74
	mov	r2, #65536	; 0x10000
	adds	ip, ip, r2
	adc	r2, r1, #0
	mov	r1, ip
	bl	OS_SetPeriodicAlarm
	add	sp, sp, #12
	ldmia	sp!, {lr}
	bx	lr
_037FC3FC:	.word	_037FC330
_037FC400:	.word	0x00000AA8
_037FC404:	.word	_03807A74

	arm_func_start SND_InitIntervalTimer
SND_InitIntervalTimer: ; 0x037FC408
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037FC434	; =_03807A54
	ldr	r1, _037FC438	; =_03807A34
	mov	r2, #8
	bl	OS_InitMessageQueue
	ldr	r0, _037FC43C	; =_03807A74
	bl	OS_CreateAlarm
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FC434:	.word	_03807A54
_037FC438:	.word	_03807A34
_037FC43C:	.word	_03807A74

	arm_func_start SND_CreateThread
SND_CreateThread: ; 0x037FC440
	stmfd	sp!, {lr}
	sub	sp, sp, #12
	mov	r1, #1024	; 0x400
	str	r1, [sp]
	str	r0, [sp, #4]
	ldr	r0, _037FC47C	; =_03807AA0
	ldr	r1, _037FC480	; =FUN_037FC2B0
	mov	r2, #0
	ldr	r3, _037FC484	; =_03807F44
	bl	OS_CreateThread
	ldr	r0, _037FC47C	; =_03807AA0
	bl	OS_WakeupThreadDirect
	add	sp, sp, #12
	ldmia	sp!, {lr}
	bx	lr
_037FC47C:	.word	_03807AA0
_037FC480:	.word	FUN_037FC2B0
_037FC484:	.word	_03807F44

	arm_func_start SND_Init
SND_Init: ; 0x037FC488
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	ldr	r0, _037FC4BC	; =_03807A30
	ldr	r1, [r0]
	cmp	r1, #0
	bne	_037FC4B4
	mov	r1, #1
	str	r1, [r0]
	bl	SND_CommandInit
	mov	r0, r4
	bl	SND_CreateThread
_037FC4B4:
	ldmia	sp!, {r4, lr}
	bx	lr
_037FC4BC:	.word	_03807A30

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

	arm_func_start FUN_037FC530
FUN_037FC530: ; 0x037FC530
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, r1
	add	r0, r6, #40	; 0x28
	bl	SND_GetLfoValue
	mov	r4, r0
	mov	ip, r0, asr #31
	mov	r3, #0
	cmp	ip, r3
	cmpeq	r0, r3
	beq	_037FC5B0
	ldrb	r1, [r6, #40]	; 0x28
	cmp	r1, #0
	beq	_037FC59C
	cmp	r1, #1
	beq	_037FC584
	cmp	r1, #2
	moveq	ip, ip, lsl #6
	orreq	ip, ip, r0, lsr #26
	moveq	r4, r0, lsl #6
	b	_037FC5A8
_037FC584:
	mov	r2, #60	; 0x3c
	umull	r4, r1, r0, r2
	mla	r1, r0, r3, r1
	mla	r1, ip, r2, r1
	mov	ip, r1
	b	_037FC5A8
_037FC59C:
	mov	ip, ip, lsl #6
	orr	ip, ip, r0, lsr #26
	mov	r4, r0, lsl #6
_037FC5A8:
	mov	r4, r4, lsr #14
	orr	r4, r4, ip, lsl #18
_037FC5B0:
	cmp	r5, #0
	beq	_037FC5C0
	add	r0, r6, #40	; 0x28
	bl	SND_UpdateLfo
_037FC5C0:
	mov	r0, r4
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start FUN_037FC5CC
FUN_037FC5CC: ; 0x037FC5CC
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r4, r0
	mov	r5, r1
	ldrsh	r3, [r4, #50]	; 0x32
	cmp	r3, #0
	moveq	r0, #0
	beq	_037FC630
	ldr	r0, [r4, #20]
	ldr	r2, [r4, #24]
	cmp	r0, r2
	movge	r0, #0
	bge	_037FC630
	sub	r0, r2, r0
	smull	r0, r1, r3, r0
	mov	r3, r2, asr #31
	bl	_ll_sdiv
	cmp	r5, #0
	beq	_037FC630
	ldrb	r1, [r4, #3]
	mov	r1, r1, lsl #29
	movs	r1, r1, lsr #31
	ldrne	r1, [r4, #20]
	addne	r1, r1, #1
	strne	r1, [r4, #20]
_037FC630:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start FUN_037FC63C
FUN_037FC63C: ; 0x037FC63C
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldrh	lr, [r0, #36]	; 0x24
	and	r2, lr, #255	; 0xff
	ldrh	ip, [r1, #36]	; 0x24
	and	r0, ip, #255	; 0xff
	mov	r2, r2, lsl #4
	mov	r3, r0, lsl #4
	ldr	r1, _037FC698	; =_03807294
	ldrb	r0, [r1, lr, asr #8]
	mov	r2, r2, asr r0
	ldrb	r0, [r1, ip, asr #8]
	mov	r0, r3, asr r0
	cmp	r2, r0
	beq	_037FC688
	cmp	r2, r0
	movlt	r0, #1
	mvnge	r0, #0
	b	_037FC68C
_037FC688:
	mov	r0, #0
_037FC68C:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FC698:	.word	_03807294

	arm_func_start FUN_037FC69C
FUN_037FC69C: ; 0x037FC69C
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	ldr	r0, _037FC6E4	; =0xFFFE9680
	str	r0, [r4, #16]
	mov	r0, #0
	strb	r0, [r4, #2]
	str	r1, [r4, #52]	; 0x34
	add	r0, r4, #40	; 0x28
	bl	SND_StartLfo
	ldrb	r0, [r4, #3]
	orr	r0, r0, #2
	strb	r0, [r4, #3]
	ldrb	r0, [r4, #3]
	bic	r0, r0, #1
	orr	r0, r0, #1
	strb	r0, [r4, #3]
	ldmia	sp!, {r4, lr}
	bx	lr
_037FC6E4:	.word	0xFFFE9680

	arm_func_start FUN_037FC6E8
FUN_037FC6E8: ; 0x037FC6E8
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	ip, #0
	str	ip, [r4, #80]	; 0x50
	str	r1, [r4, #72]	; 0x48
	str	r2, [r4, #76]	; 0x4c
	str	ip, [r4, #52]	; 0x34
	strb	r3, [r4, #34]	; 0x22
	mov	r1, #127	; 0x7f
	strh	r1, [r4, #36]	; 0x24
	ldrb	r2, [r4, #3]
	bic	r2, r2, #2
	strb	r2, [r4, #3]
	ldrb	r2, [r4, #3]
	orr	r2, r2, #4
	strb	r2, [r4, #3]
	mov	r2, #60	; 0x3c
	strb	r2, [r4, #8]
	strb	r2, [r4, #5]
	strb	r1, [r4, #9]
	strb	ip, [r4, #10]
	strh	ip, [r4, #12]
	strh	ip, [r4, #6]
	strh	ip, [r4, #14]
	strb	ip, [r4, #11]
	strb	r1, [r4, #4]
	strh	ip, [r4, #50]	; 0x32
	str	ip, [r4, #24]
	str	ip, [r4, #20]
	bl	SND_SetExChannelAttack
	mov	r0, r4
	mov	r1, #127	; 0x7f
	bl	SND_SetExChannelDecay
	mov	r0, r4
	mov	r1, #127	; 0x7f
	bl	SND_SetExChannelSustain
	mov	r0, r4
	mov	r1, #127	; 0x7f
	bl	SND_SetExChannelRelease
	add	r0, r4, #40	; 0x28
	bl	SND_InitLfoParam
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start FUN_037FC794
FUN_037FC794: ; 0x037FC794
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r1, r0
	cmp	r1, #127	; 0x7f
	ldreq	r0, _037FC7F0	; =0x0000FFFF
	beq	_037FC7E4
	cmp	r1, #126	; 0x7e
	moveq	r0, #15360	; 0x3c00
	beq	_037FC7E4
	cmp	r1, #50	; 0x32
	movlt	r0, r1, lsl #1
	addlt	r0, r0, #1
	movlt	r0, r0, lsl #16
	movlt	r0, r0, lsr #16
	blt	_037FC7E4
	mov	r0, #7680	; 0x1e00
	rsb	r1, r1, #126	; 0x7e
	bl	_s32_div_f
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
_037FC7E4:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FC7F0:	.word	0x0000FFFF

	arm_func_start SND_GetLfoValue
SND_GetLfoValue: ; 0x037FC7F4
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	ldrb	r0, [r4, #2]
	cmp	r0, #0
	moveq	r0, #0
	beq	_037FC83C
	ldrh	r1, [r4, #6]
	ldrh	r0, [r4, #4]
	cmp	r1, r0
	movcc	r0, #0
	bcc	_037FC83C
	ldrh	r0, [r4, #8]
	mov	r0, r0, lsr #8
	bl	SND_SinIdx
	ldrb	r2, [r4, #3]
	ldrb	r1, [r4, #2]
	mul	r0, r1, r0
	mul	r0, r2, r0
_037FC83C:
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start SND_UpdateLfo
SND_UpdateLfo: ; 0x037FC844
	ldrh	r2, [r0, #6]
	ldrh	r1, [r0, #4]
	cmp	r2, r1
	addcc	r1, r2, #1
	strcch	r1, [r0, #6]
	bxcc	lr
	ldrh	r2, [r0, #8]
	ldrb	r1, [r0, #1]
	mov	r3, r1, lsl #6
	add	r1, r2, r1, lsl #6
	mov	r2, r1, lsr #8
	b	_037FC878
_037FC874:
	sub	r2, r2, #128	; 0x80
_037FC878:
	cmp	r2, #128	; 0x80
	bcs	_037FC874
	ldrh	r1, [r0, #8]
	add	r1, r1, r3
	strh	r1, [r0, #8]
	ldrh	r1, [r0, #8]
	and	r1, r1, #255	; 0xff
	strh	r1, [r0, #8]
	ldrh	r1, [r0, #8]
	orr	r1, r1, r2, lsl #8
	strh	r1, [r0, #8]
	bx	lr

	arm_func_start SND_StartLfo
SND_StartLfo: ; 0x037FC8A8
	mov	r1, #0
	strh	r1, [r0, #8]
	strh	r1, [r0, #6]
	bx	lr

	arm_func_start SND_InitLfoParam
SND_InitLfoParam: ; 0x037FC8B8
	mov	r2, #0
	strb	r2, [r0]
	strb	r2, [r0, #2]
	mov	r1, #1
	strb	r1, [r0, #3]
	mov	r1, #16
	strb	r1, [r0, #1]
	strh	r2, [r0, #4]
	bx	lr

	arm_func_start SND_InvalidateWave
SND_InvalidateWave: ; 0x037FC8DC
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r5, #0
	mov	r9, r5
	ldr	r4, _037FC960	; =SNDi_Work
	mov	r8, #84	; 0x54
_037FC8FC:
	mla	r2, r5, r8, r4
	ldrb	r1, [r2, #3]
	mov	r0, r1, lsl #31
	movs	r0, r0, lsr #31
	beq	_037FC944
	ldrb	r0, [r2, #1]
	cmp	r0, #0
	bne	_037FC944
	ldr	r0, [r2, #68]	; 0x44
	cmp	r7, r0
	bhi	_037FC944
	cmp	r0, r6
	bhi	_037FC944
	bic	r0, r1, #2
	strb	r0, [r2, #3]
	mov	r0, r5
	mov	r1, r9
	bl	SND_StopChannel
_037FC944:
	add	r0, r5, #1
	and	r5, r0, #255	; 0xff
	cmp	r5, #16
	bcc	_037FC8FC
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037FC960:	.word	SNDi_Work

	arm_func_start SND_GetLockedChannel
SND_GetLockedChannel: ; 0x037FC964
	ands	r0, r0, #1
	ldrne	r0, _037FC97C	; =_03807F44
	ldrne	r0, [r0]
	ldreq	r0, _037FC980	; =_03807F48
	ldreq	r0, [r0]
	bx	lr
_037FC97C:	.word	_03807F44
_037FC980:	.word	_03807F48

	arm_func_start SND_UnlockChannel
SND_UnlockChannel: ; 0x037FC984
	ands	r1, r1, #1
	ldreq	r1, _037FC9B8	; =_03807F48
	ldreq	r2, [r1]
	mvneq	r0, r0
	andeq	r0, r2, r0
	streq	r0, [r1]
	bxeq	lr
	ldr	r1, _037FC9BC	; =_03807F44
	ldr	r2, [r1]
	mvn	r0, r0
	and	r0, r2, r0
	str	r0, [r1]
	bx	lr
_037FC9B8:	.word	_03807F48
_037FC9BC:	.word	_03807F44

	arm_func_start SND_LockChannel
SND_LockChannel: ; 0x037FC9C0
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	r9, r1
	mov	r7, sl
	mov	r6, #0
	mov	fp, r6
	str	r6, [sp]
	mov	r4, r6
	mov	r5, #1
	b	_037FCA6C
_037FC9EC:
	ands	r0, r7, #1
	beq	_037FCA64
	mov	r1, #84	; 0x54
	ldr	r0, _037FCAAC	; =SNDi_Work
	mla	r8, r6, r1, r0
	ldr	r0, _037FCAB0	; =_03807F48
	ldr	r1, [r0]
	mov	r0, r5, lsl r6
	ands	r0, r1, r0
	bne	_037FCA64
	ldr	r3, [r8, #72]	; 0x48
	cmp	r3, #0
	beq	_037FCA34
	mov	r0, r8
	mov	r1, fp
	ldr	r2, [r8, #76]	; 0x4c
	mov	lr, pc
	bx	r3
_037FCA34:
	mov	r0, r6
	ldr	r1, [sp]
	bl	SND_StopChannel
	strb	r4, [r8, #34]	; 0x22
	mov	r0, r8
	bl	SND_FreeExChannel
	ldrb	r0, [r8, #3]
	bic	r0, r0, #248	; 0xf8
	strb	r0, [r8, #3]
	ldrb	r0, [r8, #3]
	bic	r0, r0, #1
	strb	r0, [r8, #3]
_037FCA64:
	add	r6, r6, #1
	mov	r7, r7, lsr #1
_037FCA6C:
	cmp	r6, #16
	bge	_037FCA7C
	cmp	r7, #0
	bne	_037FC9EC
_037FCA7C:
	ands	r0, r9, #1
	ldrne	r0, _037FCAB4	; =_03807F44
	ldrne	r1, [r0]
	orrne	r1, r1, sl
	strne	r1, [r0]
	ldreq	r0, _037FCAB0	; =_03807F48
	ldreq	r1, [r0]
	orreq	r1, r1, sl
	streq	r1, [r0]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FCAAC:	.word	SNDi_Work
_037FCAB0:	.word	_03807F48
_037FCAB4:	.word	_03807F44

	arm_func_start SND_StopUnlockedChannel
SND_StopUnlockedChannel: ; 0x037FCAB8
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	r8, #0
	mov	r6, r8
	mov	r5, r8
	mov	r4, r8
	ldr	fp, _037FCB78	; =SNDi_Work
	mov	r7, #1
	b	_037FCB5C
_037FCAE0:
	ands	r0, sl, #1
	beq	_037FCB54
	mov	r0, #84	; 0x54
	mla	r9, r8, r0, fp
	ldr	r0, _037FCB7C	; =_03807F48
	ldr	r1, [r0]
	mov	r0, r7, lsl r8
	ands	r0, r1, r0
	bne	_037FCB54
	ldr	r3, [r9, #72]	; 0x48
	cmp	r3, #0
	beq	_037FCB24
	mov	r0, r9
	mov	r1, r6
	ldr	r2, [r9, #76]	; 0x4c
	mov	lr, pc
	bx	r3
_037FCB24:
	mov	r0, r8
	mov	r1, r5
	bl	SND_StopChannel
	strb	r4, [r9, #34]	; 0x22
	mov	r0, r9
	bl	SND_FreeExChannel
	ldrb	r0, [r9, #3]
	bic	r0, r0, #248	; 0xf8
	strb	r0, [r9, #3]
	ldrb	r0, [r9, #3]
	bic	r0, r0, #1
	strb	r0, [r9, #3]
_037FCB54:
	add	r8, r8, #1
	mov	sl, sl, lsr #1
_037FCB5C:
	cmp	r8, #16
	bge	_037FCB6C
	cmp	sl, #0
	bne	_037FCAE0
_037FCB6C:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FCB78:	.word	SNDi_Work
_037FCB7C:	.word	_03807F48

	arm_func_start SND_FreeExChannel
SND_FreeExChannel: ; 0x037FCB80
	cmp	r0, #0
	movne	r1, #0
	strne	r1, [r0, #72]	; 0x48
	strne	r1, [r0, #76]	; 0x4c
	bx	lr

	arm_func_start SND_AllocExChannel
SND_AllocExChannel: ; 0x037FCB94
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	r9, r1
	mov	fp, r3
	ldr	r0, _037FCCBC	; =_03807F48
	ldr	r0, [r0]
	mvn	r0, r0
	and	sl, sl, r0
	cmp	r2, #0
	ldreq	r0, _037FCCC0	; =_03807F44
	ldreq	r0, [r0]
	mvneq	r0, r0
	andeq	sl, sl, r0
	mov	r8, #0
	mov	r7, r8
	mov	r5, #1
	mov	r4, #84	; 0x54
_037FCBDC:
	ldr	r0, _037FCCC4	; =_03807298
	ldrb	r1, [r0, r7]
	mov	r0, r5, lsl r1
	ands	r0, sl, r0
	beq	_037FCC34
	ldr	r0, _037FCCC8	; =SNDi_Work
	mla	r6, r1, r4, r0
	cmp	r8, #0
	moveq	r8, r6
	beq	_037FCC34
	ldrb	r1, [r8, #34]	; 0x22
	ldrb	r0, [r6, #34]	; 0x22
	cmp	r0, r1
	bhi	_037FCC34
	cmp	r0, r1
	bne	_037FCC30
	mov	r0, r8
	mov	r1, r6
	bl	FUN_037FC63C
	cmp	r0, #0
	bge	_037FCC34
_037FCC30:
	mov	r8, r6
_037FCC34:
	add	r7, r7, #1
	cmp	r7, #16
	blt	_037FCBDC
	cmp	r8, #0
	moveq	r0, #0
	beq	_037FCCB0
	ldrb	r0, [r8, #34]	; 0x22
	cmp	r9, r0
	movlt	r0, #0
	blt	_037FCCB0
	ldr	r3, [r8, #72]	; 0x48
	cmp	r3, #0
	beq	_037FCC7C
	mov	r0, r8
	mov	r1, #0
	ldr	r2, [r8, #76]	; 0x4c
	mov	lr, pc
	bx	r3
_037FCC7C:
	ldrb	r0, [r8, #3]
	bic	r0, r0, #248	; 0xf8
	orr	r0, r0, #16
	strb	r0, [r8, #3]
	ldrb	r0, [r8, #3]
	bic	r0, r0, #1
	strb	r0, [r8, #3]
	mov	r0, r8
	mov	r1, fp
	ldr	r2, [sp, #40]	; 0x28
	mov	r3, r9
	bl	FUN_037FC6E8
	mov	r0, r8
_037FCCB0:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FCCBC:	.word	_03807F48
_037FCCC0:	.word	_03807F44
_037FCCC4:	.word	_03807298
_037FCCC8:	.word	SNDi_Work

	arm_func_start SND_IsExChannelActive
SND_IsExChannelActive: ; 0x037FCCCC
	ldrb	r0, [r0, #3]
	mov	r0, r0, lsl #31
	mov	r0, r0, lsr #31
	bx	lr

	arm_func_start SND_ReleaseExChannel
SND_ReleaseExChannel: ; 0x037FCCDC
	mov	r1, #3
	strb	r1, [r0, #2]
	bx	lr

	arm_func_start SND_SetExChannelRelease
SND_SetExChannelRelease: ; 0x037FCCE8
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, r1
	bl	FUN_037FC794
	strh	r0, [r4, #32]
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start SND_SetExChannelSustain
SND_SetExChannelSustain: ; 0x037FCD04
	strb	r1, [r0, #29]
	bx	lr

	arm_func_start SND_SetExChannelDecay
SND_SetExChannelDecay: ; 0x037FCD0C
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, r1
	bl	FUN_037FC794
	strh	r0, [r4, #30]
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start SND_SetExChannelAttack
SND_SetExChannelAttack: ; 0x037FCD28
	cmp	r1, #109	; 0x6d
	rsblt	r1, r1, #255	; 0xff
	strltb	r1, [r0, #28]
	rsbge	r2, r1, #127	; 0x7f
	ldrge	r1, _037FCD48	; =_038072A8
	ldrgeb	r1, [r1, r2]
	strgeb	r1, [r0, #28]
	bx	lr
_037FCD48:	.word	_038072A8

	arm_func_start SND_UpdateExChannelEnvelope
SND_UpdateExChannelEnvelope: ; 0x037FCD4C
	cmp	r1, #0
	beq	_037FCDF0
	ldrb	r1, [r0, #2]
	cmp	r1, #3
	addls	pc, pc, r1, lsl #2
	b	_037FCDF0
	b	_037FCD74
	b	_037FCDA4
	b	_037FCDF0
	b	_037FCDE0
_037FCD74:
	ldr	r1, [r0, #16]
	rsb	r2, r1, #0
	ldrb	r1, [r0, #28]
	mul	r1, r2, r1
	mov	r1, r1, asr #8
	rsb	r1, r1, #0
	str	r1, [r0, #16]
	ldr	r1, [r0, #16]
	cmp	r1, #0
	moveq	r1, #1
	streqb	r1, [r0, #2]
	b	_037FCDF0
_037FCDA4:
	ldrb	r1, [r0, #29]
	mov	r2, r1, lsl #1
	ldr	r1, _037FCDFC	; =SNDi_DecibelSquareTable
	ldrsh	r1, [r1, r2]
	mov	r3, r1, lsl #7
	ldr	r2, [r0, #16]
	ldrh	r1, [r0, #30]
	sub	r1, r2, r1
	str	r1, [r0, #16]
	ldr	r1, [r0, #16]
	cmp	r1, r3
	strle	r3, [r0, #16]
	movle	r1, #2
	strleb	r1, [r0, #2]
	b	_037FCDF0
_037FCDE0:
	ldr	r2, [r0, #16]
	ldrh	r1, [r0, #32]
	sub	r1, r2, r1
	str	r1, [r0, #16]
_037FCDF0:
	ldr	r0, [r0, #16]
	mov	r0, r0, asr #7
	bx	lr
_037FCDFC:	.word	SNDi_DecibelSquareTable

	arm_func_start SND_StartExChannelNoise
SND_StartExChannelNoise: ; 0x037FCE00
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldrb	r2, [r0]
	cmp	r2, #14
	movcc	r0, #0
	bcc	_037FCE3C
	cmp	r2, #15
	movhi	r0, #0
	bhi	_037FCE3C
	mov	r2, #2
	strb	r2, [r0, #1]
	ldr	r2, _037FCE48	; =0x00001F46
	strh	r2, [r0, #60]	; 0x3c
	bl	FUN_037FC69C
	mov	r0, #1
_037FCE3C:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FCE48:	.word	0x00001F46

	arm_func_start SND_StartExChannelPsg
SND_StartExChannelPsg: ; 0x037FCE4C
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldrb	r3, [r0]
	cmp	r3, #8
	movcc	r0, #0
	bcc	_037FCE90
	cmp	r3, #13
	movhi	r0, #0
	bhi	_037FCE90
	mov	r3, #1
	strb	r3, [r0, #1]
	str	r1, [r0, #68]	; 0x44
	ldr	r1, _037FCE9C	; =0x00001F46
	strh	r1, [r0, #60]	; 0x3c
	mov	r1, r2
	bl	FUN_037FC69C
	mov	r0, #1
_037FCE90:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FCE9C:	.word	0x00001F46

	arm_func_start SND_StartExChannelPcm
SND_StartExChannelPcm: ; 0x037FCEA0
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	lr, r2
	mov	r0, #0
	strb	r0, [r4, #1]
	add	ip, r4, #56	; 0x38
	ldmia	r1, {r0, r1, r2}
	stmia	ip, {r0, r1, r2}
	str	lr, [r4, #68]	; 0x44
	mov	r0, r4
	mov	r1, r3
	bl	FUN_037FC69C
	mov	r0, #1
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start SND_ExChannelMain
SND_ExChannelMain: ; 0x037FCEDC
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #28
	mov	r6, r0
	mov	r4, #0
	mov	fp, r4
	mov	r7, #1
	str	r4, [sp, #8]
	mov	r0, #127	; 0x7f
	str	r0, [sp, #20]
	str	r4, [sp, #16]
	str	r4, [sp, #12]
	str	r4, [sp, #4]
	str	r4, [sp]
_037FCF10:
	ldr	r8, [sp]
	mov	sl, r8
	mov	r9, r8
	mov	r1, #84	; 0x54
	ldr	r0, _037FD1E4	; =SNDi_Work
	mla	r5, r4, r1, r0
	ldrb	r1, [r5, #3]
	mov	r0, r1, lsl #31
	movs	r0, r0, lsr #31
	beq	_037FD1CC
	mov	r0, r1, lsl #30
	movs	r0, r0, lsr #31
	beq	_037FCF74
	bic	r0, r1, #248	; 0xf8
	mov	r1, r1, lsl #24
	mov	r1, r1, lsr #27
	orr	r1, r1, #1
	and	r1, r1, #255	; 0xff
	and	r1, r1, #31
	orr	r0, r0, r1, lsl #3
	strb	r0, [r5, #3]
	ldrb	r0, [r5, #3]
	bic	r0, r0, #2
	strb	r0, [r5, #3]
	b	_037FCFC0
_037FCF74:
	mov	r0, r4
	bl	SND_IsChannelActive
	cmp	r0, #0
	bne	_037FCFC0
	ldr	r3, [r5, #72]	; 0x48
	cmp	r3, #0
	streqb	fp, [r5, #34]	; 0x22
	beq	_037FCFA8
	mov	r0, r5
	mov	r1, r7
	ldr	r2, [r5, #76]	; 0x4c
	mov	lr, pc
	bx	r3
_037FCFA8:
	ldr	r0, [sp, #4]
	strh	r0, [r5, #36]	; 0x24
	ldrb	r0, [r5, #3]
	bic	r0, r0, #1
	strb	r0, [r5, #3]
	b	_037FD1CC
_037FCFC0:
	ldrb	r0, [r5, #9]
	mov	r1, r0, lsl #1
	ldr	r0, _037FD1E8	; =SNDi_DecibelSquareTable
	ldrsh	r0, [r0, r1]
	add	r8, r8, r0
	ldrb	r1, [r5, #8]
	ldrb	r0, [r5, #5]
	sub	r0, r1, r0
	add	sl, sl, r0, lsl #6
	mov	r0, r5
	mov	r1, r6
	bl	SND_UpdateExChannelEnvelope
	add	r8, r8, r0
	mov	r0, r5
	mov	r1, r6
	bl	FUN_037FC5CC
	add	r2, sl, r0
	ldrsh	r0, [r5, #12]
	add	r1, r8, r0
	ldrsh	r0, [r5, #6]
	add	r8, r1, r0
	ldrsh	r0, [r5, #14]
	add	sl, r2, r0
	mov	r0, r5
	mov	r1, r6
	bl	FUN_037FC530
	ldrb	r1, [r5, #40]	; 0x28
	cmp	r1, #0
	beq	_037FD05C
	cmp	r1, #1
	beq	_037FD048
	cmp	r1, #2
	addeq	r9, r9, r0
	b	_037FD060
_037FD048:
	mov	r1, #32768	; 0x8000
	rsb	r1, r1, #0
	cmp	r8, r1
	addgt	r8, r8, r0
	b	_037FD060
_037FD05C:
	add	sl, sl, r0
_037FD060:
	ldrsb	r0, [r5, #10]
	add	r9, r9, r0
	ldrb	r0, [r5, #4]
	cmp	r0, #127	; 0x7f
	mulne	r0, r9, r0
	addne	r0, r0, #64	; 0x40
	movne	r9, r0, asr #7
	ldrsb	r0, [r5, #11]
	add	r9, r9, r0
	ldrb	r0, [r5, #2]
	cmp	r0, #3
	bne	_037FD0EC
	ldr	r0, _037FD1EC	; =0xFFFFFD2D
	cmp	r8, r0
	bgt	_037FD0EC
	ldrb	r0, [r5, #3]
	bic	r0, r0, #248	; 0xf8
	orr	r0, r0, #16
	strb	r0, [r5, #3]
	ldr	r3, [r5, #72]	; 0x48
	cmp	r3, #0
	ldreq	r0, [sp, #8]
	streqb	r0, [r5, #34]	; 0x22
	beq	_037FD0D4
	mov	r0, r5
	mov	r1, r7
	ldr	r2, [r5, #76]	; 0x4c
	mov	lr, pc
	bx	r3
_037FD0D4:
	ldr	r0, [sp, #12]
	strh	r0, [r5, #36]	; 0x24
	ldrb	r0, [r5, #3]
	bic	r0, r0, #1
	strb	r0, [r5, #3]
	b	_037FD1CC
_037FD0EC:
	mov	r0, r8
	bl	SND_CalcChannelVolume
	mov	r8, r0
	ldrh	r0, [r5, #60]	; 0x3c
	mov	r1, sl
	bl	SND_CalcTimer
	ldrb	r1, [r5, #1]
	cmp	r1, #1
	ldreq	r1, _037FD1F0	; =0x0000FFFC
	andeq	r0, r0, r1
	moveq	r0, r0, lsl #16
	moveq	r0, r0, lsr #16
	adds	r9, r9, #64	; 0x40
	ldrmi	r9, [sp, #16]
	bmi	_037FD130
	cmp	r9, #127	; 0x7f
	ldrgt	r9, [sp, #20]
_037FD130:
	ldrh	r1, [r5, #36]	; 0x24
	cmp	r8, r1
	beq	_037FD164
	strh	r8, [r5, #36]	; 0x24
	ldrb	r2, [r5, #3]
	bic	r1, r2, #248	; 0xf8
	mov	r2, r2, lsl #24
	mov	r2, r2, lsr #27
	orr	r2, r2, #8
	and	r2, r2, #255	; 0xff
	and	r2, r2, #31
	orr	r1, r1, r2, lsl #3
	strb	r1, [r5, #3]
_037FD164:
	ldrh	r1, [r5, #38]	; 0x26
	cmp	r0, r1
	beq	_037FD198
	strh	r0, [r5, #38]	; 0x26
	ldrb	r0, [r5, #3]
	bic	r1, r0, #248	; 0xf8
	mov	r0, r0, lsl #24
	mov	r0, r0, lsr #27
	orr	r0, r0, #4
	and	r0, r0, #255	; 0xff
	and	r0, r0, #31
	orr	r0, r1, r0, lsl #3
	strb	r0, [r5, #3]
_037FD198:
	ldrb	r0, [r5, #35]	; 0x23
	cmp	r9, r0
	beq	_037FD1CC
	strb	r9, [r5, #35]	; 0x23
	ldrb	r0, [r5, #3]
	bic	r1, r0, #248	; 0xf8
	mov	r0, r0, lsl #24
	mov	r0, r0, lsr #27
	orr	r0, r0, #16
	and	r0, r0, #255	; 0xff
	and	r0, r0, #31
	orr	r0, r1, r0, lsl #3
	strb	r0, [r5, #3]
_037FD1CC:
	add	r4, r4, #1
	cmp	r4, #16
	blt	_037FCF10
	add	sp, sp, #28
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FD1E4:	.word	SNDi_Work
_037FD1E8:	.word	SNDi_DecibelSquareTable
_037FD1EC:	.word	0xFFFFFD2D
_037FD1F0:	.word	0x0000FFFC

	arm_func_start SND_UpdateExChannel
SND_UpdateExChannel: ; 0x037FD1F4
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	sub	sp, sp, #24
	mov	r8, #0
	mov	r4, #2
	mov	r5, #1
	mov	r6, r8
	ldr	r7, _037FD3DC	; =SNDi_Work
	mov	sl, #84	; 0x54
_037FD214:
	mla	r9, r8, sl, r7
	ldrb	r0, [r9, #3]
	mov	r0, r0, lsl #24
	movs	r0, r0, lsr #27
	beq	_037FD374
	ands	r0, r0, #2
	beq	_037FD23C
	mov	r0, r8
	mov	r1, r6
	bl	SND_StopChannel
_037FD23C:
	ldrb	r0, [r9, #3]
	mov	r0, r0, lsl #24
	mov	r1, r0, lsr #27
	ands	r0, r1, #1
	beq	_037FD318
	ldrb	r0, [r9, #1]
	cmp	r0, #0
	beq	_037FD270
	cmp	r0, #1
	beq	_037FD2C8
	cmp	r0, #2
	beq	_037FD2F4
	b	_037FD374
_037FD270:
	ldrb	r0, [r9, #57]	; 0x39
	cmp	r0, #0
	movne	r3, r5
	moveq	r3, r4
	ldrh	r1, [r9, #36]	; 0x24
	ldrh	r0, [r9, #62]	; 0x3e
	str	r0, [sp]
	ldr	r0, [r9, #64]	; 0x40
	str	r0, [sp, #4]
	and	r0, r1, #255	; 0xff
	str	r0, [sp, #8]
	mov	r0, r1, asr #8
	str	r0, [sp, #12]
	ldrh	r0, [r9, #38]	; 0x26
	str	r0, [sp, #16]
	ldrb	r0, [r9, #35]	; 0x23
	str	r0, [sp, #20]
	mov	r0, r8
	ldr	r1, [r9, #68]	; 0x44
	ldrb	r2, [r9, #56]	; 0x38
	bl	SND_SetupChannelPcm
	b	_037FD374
_037FD2C8:
	ldrh	r3, [r9, #36]	; 0x24
	ldrh	r0, [r9, #38]	; 0x26
	str	r0, [sp]
	ldrb	r0, [r9, #35]	; 0x23
	str	r0, [sp, #4]
	mov	r0, r8
	ldr	r1, [r9, #68]	; 0x44
	and	r2, r3, #255	; 0xff
	mov	r3, r3, asr #8
	bl	SND_SetupChannelPsg
	b	_037FD374
_037FD2F4:
	ldrh	r2, [r9, #36]	; 0x24
	ldrb	r0, [r9, #35]	; 0x23
	str	r0, [sp]
	mov	r0, r8
	and	r1, r2, #255	; 0xff
	mov	r2, r2, asr #8
	ldrh	r3, [r9, #38]	; 0x26
	bl	SND_SetupChannelNoise
	b	_037FD374
_037FD318:
	ands	r0, r1, #4
	beq	_037FD32C
	mov	r0, r8
	ldrh	r1, [r9, #38]	; 0x26
	bl	SND_SetChannelTimer
_037FD32C:
	ldrb	r0, [r9, #3]
	mov	r0, r0, lsl #24
	mov	r0, r0, lsr #27
	ands	r0, r0, #8
	beq	_037FD354
	ldrh	r2, [r9, #36]	; 0x24
	mov	r0, r8
	and	r1, r2, #255	; 0xff
	mov	r2, r2, asr #8
	bl	SND_SetChannelVolume
_037FD354:
	ldrb	r0, [r9, #3]
	mov	r0, r0, lsl #24
	mov	r0, r0, lsr #27
	ands	r0, r0, #16
	beq	_037FD374
	mov	r0, r8
	ldrb	r1, [r9, #35]	; 0x23
	bl	SND_SetChannelPan
_037FD374:
	add	r8, r8, #1
	cmp	r8, #16
	blt	_037FD214
	mov	r5, #0
	ldr	r3, _037FD3DC	; =SNDi_Work
	mov	r1, #84	; 0x54
_037FD38C:
	mla	r4, r5, r1, r3
	ldrb	r0, [r4, #3]
	mov	r0, r0, lsl #24
	movs	r0, r0, lsr #27
	beq	_037FD3C4
	ands	r0, r0, #1
	movne	r0, r5, lsl #4
	addne	r0, r0, #67108864	; 0x4000000
	ldrneb	r2, [r0, #1027]	; 0x403
	orrne	r2, r2, #128	; 0x80
	strneb	r2, [r0, #1027]	; 0x403
	ldrb	r0, [r4, #3]
	bic	r0, r0, #248	; 0xf8
	strb	r0, [r4, #3]
_037FD3C4:
	add	r5, r5, #1
	cmp	r5, #16
	blt	_037FD38C
	add	sp, sp, #24
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	bx	lr
_037FD3DC:	.word	SNDi_Work

	arm_func_start SND_ExChannelInit
SND_ExChannelInit: ; 0x037FD3E0
	mov	ip, #0
	ldr	r2, _037FD434	; =SNDi_Work
	mov	r0, #84	; 0x54
_037FD3EC:
	mul	r1, ip, r0
	add	r3, r2, r1
	strb	ip, [r2, r1]
	ldrb	r1, [r3, #3]
	bic	r1, r1, #248	; 0xf8
	strb	r1, [r3, #3]
	ldrb	r1, [r3, #3]
	bic	r1, r1, #1
	strb	r1, [r3, #3]
	add	ip, ip, #1
	cmp	ip, #16
	blt	_037FD3EC
	mov	r1, #0
	ldr	r0, _037FD438	; =_03807F48
	str	r1, [r0]
	ldr	r0, _037FD43C	; =_03807F44
	str	r1, [r0]
	bx	lr
_037FD434:	.word	SNDi_Work
_037FD438:	.word	_03807F48
_037FD43C:	.word	_03807F44

	arm_func_start FUN_037FD440
FUN_037FD440: ; 0x037FD440
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	cmp	r2, #3
	addls	pc, pc, r2, lsl #2
	b	_037FD4B8
	b	_037FD464
	b	_037FD474
	b	_037FD484
	b	_037FD49C
_037FD464:
	ldrb	r0, [r4]
	bic	r0, r0, #4
	strb	r0, [r4]
	b	_037FD4B8
_037FD474:
	ldrb	r0, [r4]
	orr	r0, r0, #4
	strb	r0, [r4]
	b	_037FD4B8
_037FD484:
	ldrb	r2, [r4]
	orr	r2, r2, #4
	strb	r2, [r4]
	mvn	r2, #0
	bl	FUN_037FE588
	b	_037FD4B8
_037FD49C:
	ldrb	r2, [r4]
	orr	r2, r2, #4
	strb	r2, [r4]
	mov	r2, #127	; 0x7f
	bl	FUN_037FE588
	mov	r0, r4
	bl	FUN_037FE54C
_037FD4B8:
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start FUN_037FD4C0
FUN_037FD4C0: ; 0x037FD4C0
	mov	r0, #0
	ldr	r3, _037FD500	; =_038086EC
	b	_037FD4F0
_037FD4CC:
	add	ip, r3, r0, lsl #6
	ldrb	r1, [r3, r0, lsl #6]
	mov	r2, r1, lsl #31
	movs	r2, r2, lsr #31
	biceq	r1, r1, #1
	orreq	r1, r1, #1
	streqb	r1, [ip]
	bxeq	lr
	add	r0, r0, #1
_037FD4F0:
	cmp	r0, #32
	blt	_037FD4CC
	mvn	r0, #0
	bx	lr
_037FD500:	.word	_038086EC

	arm_func_start FUN_037FD504
FUN_037FD504: ; 0x037FD504
	ldr	r2, _037FD544	; =SNDi_SharedWork
	ldr	r2, [r2]
	cmp	r2, #0
	moveq	r0, #0
	bxeq	lr
	cmp	r1, #16
	addge	r2, r2, #608	; 0x260
	subge	r0, r1, #16
	addge	r0, r2, r0, lsl #1
	bxge	lr
	add	r3, r2, #32
	ldrb	r2, [r0, #1]
	mov	r0, #36	; 0x24
	mla	r0, r2, r0, r3
	add	r0, r0, r1, lsl #1
	bx	lr
_037FD544:	.word	SNDi_SharedWork

	arm_func_start FUN_037FD548
FUN_037FD548: ; 0x037FD548
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r8, r0
	mov	r7, r1
	mov	r6, #0
	mov	r5, r6
	mov	r4, #1
_037FD560:
	mov	r0, r8
	mov	r1, r5
	bl	FUN_037FE460
	cmp	r0, #0
	beq	_037FD5A8
	ldr	r1, [r0, #40]	; 0x28
	cmp	r1, #0
	beq	_037FD5A8
	mov	r1, r8
	mov	r2, r5
	mov	r3, r7
	bl	FUN_037FD5C8
	cmp	r0, #0
	moveq	r6, r4
	beq	_037FD5A8
	mov	r0, r8
	mov	r1, r5
	bl	FUN_037FE3EC
_037FD5A8:
	add	r5, r5, #1
	cmp	r5, #16
	blt	_037FD560
	cmp	r6, #0
	moveq	r0, #1
	movne	r0, #0
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr

	arm_func_start FUN_037FD5C8
FUN_037FD5C8: ; 0x037FD5C8
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #52	; 0x34
	mov	r9, r0
	mov	r8, r1
	str	r3, [sp, #4]
	ldr	r2, [r9, #60]	; 0x3c
	b	_037FD61C
_037FD5E4:
	ldr	r0, [r2, #52]	; 0x34
	cmp	r0, #0
	subgt	r0, r0, #1
	strgt	r0, [r2, #52]	; 0x34
	ldrb	r0, [r2, #3]
	mov	r0, r0, lsl #29
	movs	r0, r0, lsr #31
	bne	_037FD618
	ldr	r1, [r2, #20]
	ldr	r0, [r2, #24]
	cmp	r1, r0
	addlt	r0, r1, #1
	strlt	r0, [r2, #20]
_037FD618:
	ldr	r2, [r2, #80]	; 0x50
_037FD61C:
	cmp	r2, #0
	bne	_037FD5E4
	ldrb	r1, [r9]
	mov	r0, r1, lsl #27
	movs	r0, r0, lsr #31
	beq	_037FD64C
	ldr	r0, [r9, #60]	; 0x3c
	cmp	r0, #0
	movne	r0, #0
	bne	_037FDF84
	bic	r0, r1, #16
	strb	r0, [r9]
_037FD64C:
	ldr	r0, [r9, #32]
	cmp	r0, #0
	ble	_037FD670
	sub	r0, r0, #1
	str	r0, [r9, #32]
	ldr	r0, [r9, #32]
	cmp	r0, #0
	movgt	r0, #0
	bgt	_037FDF84
_037FD670:
	ldr	r0, [r9, #40]	; 0x28
	bl	FUN_037FE9B8
	add	r0, r9, #40	; 0x28
	str	r0, [sp, #28]
	mov	r0, #2
	str	r0, [sp, #32]
	mov	r0, #127	; 0x7f
	str	r0, [sp, #36]	; 0x24
	mov	fp, #0
	mvn	r0, #0
	str	r0, [sp, #40]	; 0x28
	mov	sl, #1
	mov	r0, #3
	str	r0, [sp, #20]
	mov	r0, #4
	str	r0, [sp, #24]
	b	_037FDF64
_037FD6B4:
	mov	r4, fp
	mov	r6, sl
	ldr	r0, [r9, #40]	; 0x28
	bl	FUN_037FE968
	mov	r7, r0
	ldr	r0, [r9, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r9, #40]	; 0x28
	cmp	r7, #162	; 0xa2
	bne	_037FD700
	ldr	r0, [r9, #40]	; 0x28
	bl	FUN_037FE968
	mov	r7, r0
	ldr	r0, [r9, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r9, #40]	; 0x28
	ldrb	r0, [r9]
	mov	r0, r0, lsl #25
	mov	r6, r0, lsr #31
_037FD700:
	cmp	r7, #160	; 0xa0
	bne	_037FD72C
	ldr	r0, [r9, #40]	; 0x28
	bl	FUN_037FE968
	mov	r7, r0
	ldr	r0, [r9, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r9, #40]	; 0x28
	ldr	r0, [sp, #20]
	str	r0, [sp, #8]
	mov	r4, sl
_037FD72C:
	cmp	r7, #161	; 0xa1
	bne	_037FD758
	ldr	r0, [r9, #40]	; 0x28
	bl	FUN_037FE968
	mov	r7, r0
	ldr	r0, [r9, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r9, #40]	; 0x28
	ldr	r0, [sp, #24]
	str	r0, [sp, #8]
	mov	r4, sl
_037FD758:
	ands	r0, r7, #128	; 0x80
	bne	_037FD82C
	ldr	r0, [r9, #40]	; 0x28
	bl	FUN_037FE968
	str	r0, [sp, #12]
	ldr	r0, [sp, #28]
	ldr	r0, [r0]
	add	r1, r0, #1
	ldr	r0, [sp, #28]
	str	r1, [r0]
	cmp	r4, #0
	ldrne	r2, [sp, #8]
	ldreq	r2, [sp, #32]
	mov	r0, r9
	mov	r1, r8
	bl	FUN_037FE7B0
	mov	r5, r0
	ldrsb	r0, [r9, #19]
	add	r4, r7, r0
	cmp	r6, #0
	beq	_037FDF64
	cmp	r4, #0
	movlt	r4, fp
	blt	_037FD7C0
	cmp	r4, #127	; 0x7f
	ldrgt	r4, [sp, #36]	; 0x24
_037FD7C0:
	ldrb	r0, [r9]
	mov	r0, r0, lsl #29
	movs	r0, r0, lsr #31
	bne	_037FD800
	ldr	r0, [sp, #4]
	cmp	r0, #0
	beq	_037FD800
	cmp	r5, #0
	movgt	r0, r5
	ldrle	r0, [sp, #40]	; 0x28
	str	r0, [sp]
	mov	r0, r9
	mov	r1, r8
	mov	r2, r4
	ldr	r3, [sp, #12]
	bl	FUN_037FDF94
_037FD800:
	strb	r4, [r9, #20]
	ldrb	r0, [r9]
	mov	r0, r0, lsl #30
	movs	r0, r0, lsr #31
	beq	_037FDF64
	str	r5, [r9, #32]
	cmp	r5, #0
	ldreqb	r0, [r9]
	orreq	r0, r0, #16
	streqb	r0, [r9]
	b	_037FDF64
_037FD82C:
	and	r0, r7, #240	; 0xf0
	cmp	r0, #192	; 0xc0
	bgt	_037FD868
	cmp	r0, #192	; 0xc0
	bge	_037FD9B8
	cmp	r0, #144	; 0x90
	bgt	_037FD85C
	cmp	r0, #144	; 0x90
	bge	_037FD8D8
	cmp	r0, #128	; 0x80
	beq	_037FD890
	b	_037FDF64
_037FD85C:
	cmp	r0, #176	; 0xb0
	beq	_037FDC68
	b	_037FDF64
_037FD868:
	cmp	r0, #224	; 0xe0
	bgt	_037FD884
	cmp	r0, #224	; 0xe0
	bge	_037FDC14
	cmp	r0, #208	; 0xd0
	beq	_037FD9B8
	b	_037FDF64
_037FD884:
	cmp	r0, #240	; 0xf0
	beq	_037FDEC0
	b	_037FDF64
_037FD890:
	cmp	r4, #0
	ldrne	r2, [sp, #8]
	ldreq	r2, [sp, #32]
	mov	r0, r9
	mov	r1, r8
	bl	FUN_037FE7B0
	cmp	r6, #0
	beq	_037FDF64
	cmp	r7, #128	; 0x80
	beq	_037FD8C4
	cmp	r7, #129	; 0x81
	beq	_037FD8CC
	b	_037FDF64
_037FD8C4:
	str	r0, [r9, #32]
	b	_037FDF64
_037FD8CC:
	cmp	r0, #65536	; 0x10000
	strlth	r0, [r9, #2]
	b	_037FDF64
_037FD8D8:
	cmp	r7, #147	; 0x93
	beq	_037FD8F4
	cmp	r7, #148	; 0x94
	beq	_037FD958
	cmp	r7, #149	; 0x95
	beq	_037FD974
	b	_037FDF64
_037FD8F4:
	ldr	r0, [r9, #40]	; 0x28
	bl	FUN_037FE968
	mov	r4, r0
	ldr	r0, [r9, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r9, #40]	; 0x28
	mov	r0, r9
	bl	FUN_037FE8B8
	mov	r5, r0
	cmp	r6, #0
	beq	_037FDF64
	mov	r0, r8
	mov	r1, r4
	bl	FUN_037FE460
	movs	r4, r0
	beq	_037FDF64
	cmp	r4, r9
	beq	_037FDF64
	mov	r1, r8
	bl	FUN_037FE440
	mov	r0, r4
	ldr	r1, [r9, #36]	; 0x24
	mov	r2, r5
	bl	FUN_037FE6A8
	b	_037FDF64
_037FD958:
	mov	r0, r9
	bl	FUN_037FE8B8
	cmp	r6, #0
	ldrne	r1, [r9, #36]	; 0x24
	addne	r0, r1, r0
	strne	r0, [r9, #40]	; 0x28
	b	_037FDF64
_037FD974:
	mov	r0, r9
	bl	FUN_037FE8B8
	cmp	r6, #0
	beq	_037FDF64
	ldrb	r1, [r9, #59]	; 0x3b
	cmp	r1, #3
	bcs	_037FDF64
	ldr	r2, [r9, #40]	; 0x28
	add	r1, r9, r1, lsl #2
	str	r2, [r1, #44]	; 0x2c
	ldrb	r1, [r9, #59]	; 0x3b
	add	r1, r1, #1
	strb	r1, [r9, #59]	; 0x3b
	ldr	r1, [r9, #36]	; 0x24
	add	r0, r1, r0
	str	r0, [r9, #40]	; 0x28
	b	_037FDF64
_037FD9B8:
	cmp	r4, #0
	ldrne	r2, [sp, #8]
	moveq	r2, fp
	mov	r0, r9
	mov	r1, r8
	bl	FUN_037FE7B0
	strb	r0, [sp, #44]	; 0x2c
	cmp	r6, #0
	beq	_037FDF64
	sub	r0, r7, #192	; 0xc0
	cmp	r0, #23
	addls	pc, pc, r0, lsl #2
	b	_037FDF64
	b	_037FDBE4
	b	_037FDA4C
	b	_037FDA64
	b	_037FDBCC
	b	_037FDBD8
	b	_037FDA70
	b	_037FDA7C
	b	_037FDA88
	b	_037FDB48
	b	_037FDB90
	b	_037FDAB0
	b	_037FDABC
	b	_037FDAC8
	b	_037FDAD4
	b	_037FDBB0
	b	_037FDAA4
	b	_037FDAE0
	b	_037FDAEC
	b	_037FDAF8
	b	_037FDB04
	b	_037FDB10
	b	_037FDA58
	b	_037FDBF4
	b	_037FDB7C
_037FDA4C:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #4]
	b	_037FDF64
_037FDA58:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #5]
	b	_037FDF64
_037FDA64:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r8, #5]
	b	_037FDF64
_037FDA70:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #7]
	b	_037FDF64
_037FDA7C:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #18]
	b	_037FDF64
_037FDA88:
	ldrb	r0, [r9]
	bic	r1, r0, #2
	ldrb	r0, [sp, #44]	; 0x2c
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #1
	strb	r0, [r9]
	b	_037FDF64
_037FDAA4:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #21]
	b	_037FDF64
_037FDAB0:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #26]
	b	_037FDF64
_037FDABC:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #25]
	b	_037FDF64
_037FDAC8:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #24]
	b	_037FDF64
_037FDAD4:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #27]
	b	_037FDF64
_037FDAE0:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #14]
	b	_037FDF64
_037FDAEC:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #15]
	b	_037FDF64
_037FDAF8:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #16]
	b	_037FDF64
_037FDB04:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #17]
	b	_037FDF64
_037FDB10:
	ldrb	r0, [r9, #59]	; 0x3b
	cmp	r0, #3
	bcs	_037FDF64
	ldr	r1, [r9, #40]	; 0x28
	add	r0, r9, r0, lsl #2
	str	r1, [r0, #44]	; 0x2c
	ldrb	r1, [sp, #44]	; 0x2c
	ldrb	r0, [r9, #59]	; 0x3b
	add	r0, r9, r0
	strb	r1, [r0, #56]	; 0x38
	ldrb	r0, [r9, #59]	; 0x3b
	add	r0, r0, #1
	strb	r0, [r9, #59]	; 0x3b
	b	_037FDF64
_037FDB48:
	ldrb	r0, [r9]
	bic	r1, r0, #8
	ldrb	r0, [sp, #44]	; 0x2c
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #3
	strb	r0, [r9]
	mov	r0, r9
	mov	r1, r8
	ldr	r2, [sp, #40]	; 0x28
	bl	FUN_037FE588
	mov	r0, r9
	bl	FUN_037FE54C
	b	_037FDF64
_037FDB7C:
	mov	r0, r9
	mov	r1, r8
	ldrb	r2, [sp, #44]	; 0x2c
	bl	FUN_037FD440
	b	_037FDF64
_037FDB90:
	ldrb	r1, [sp, #44]	; 0x2c
	ldrsb	r0, [r9, #19]
	add	r0, r1, r0
	strb	r0, [r9, #20]
	ldrb	r0, [r9]
	orr	r0, r0, #32
	strb	r0, [r9]
	b	_037FDF64
_037FDBB0:
	ldrb	r0, [r9]
	bic	r1, r0, #32
	ldrb	r0, [sp, #44]	; 0x2c
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #5
	strb	r0, [r9]
	b	_037FDF64
_037FDBCC:
	ldrsb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #19]
	b	_037FDF64
_037FDBD8:
	ldrsb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #6]
	b	_037FDF64
_037FDBE4:
	ldrb	r0, [sp, #44]	; 0x2c
	sub	r0, r0, #64	; 0x40
	strb	r0, [r9, #8]
	b	_037FDF64
_037FDBF4:
	ldr	r0, _037FDF90	; =_03807F4C
	ldr	r0, [r0]
	cmp	r0, #0
	beq	_037FDF64
	mov	r0, r8
	ldrb	r1, [sp, #44]	; 0x2c
	bl	FUN_037FD504
	b	_037FDF64
_037FDC14:
	cmp	r4, #0
	ldrne	r2, [sp, #8]
	moveq	r2, sl
	mov	r0, r9
	mov	r1, r8
	bl	FUN_037FE7B0
	mov	r0, r0, lsl #16
	mov	r0, r0, asr #16
	cmp	r6, #0
	beq	_037FDF64
	cmp	r7, #224	; 0xe0
	beq	_037FDC60
	cmp	r7, #225	; 0xe1
	beq	_037FDC58
	cmp	r7, #227	; 0xe3
	streqh	r0, [r9, #22]
	b	_037FDF64
_037FDC58:
	strh	r0, [r8, #24]
	b	_037FDF64
_037FDC60:
	strh	r0, [r9, #28]
	b	_037FDF64
_037FDC68:
	ldr	r0, [r9, #40]	; 0x28
	bl	FUN_037FE968
	str	r0, [sp, #16]
	ldr	r0, [r9, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r9, #40]	; 0x28
	cmp	r4, #0
	ldrne	r2, [sp, #8]
	moveq	r2, sl
	mov	r0, r9
	mov	r1, r8
	bl	FUN_037FE7B0
	mov	r0, r0, lsl #16
	mov	r5, r0, asr #16
	mov	r0, r8
	ldr	r1, [sp, #16]
	bl	FUN_037FD504
	mov	r4, r0
	cmp	r6, #0
	beq	_037FDF64
	cmp	r4, #0
	beq	_037FDF64
	sub	r0, r7, #176	; 0xb0
	cmp	r0, #13
	addls	pc, pc, r0, lsl #2
	b	_037FDF64
	b	_037FDD08
	b	_037FDD10
	b	_037FDD20
	b	_037FDD30
	b	_037FDD40
	b	_037FDD5C
	b	_037FDD80
	b	_037FDF64
	b	_037FDDB8
	b	_037FDDE4
	b	_037FDE10
	b	_037FDE3C
	b	_037FDE68
	b	_037FDE94
_037FDD08:
	strh	r5, [r4]
	b	_037FDF64
_037FDD10:
	ldrsh	r0, [r4]
	add	r0, r0, r5
	strh	r0, [r4]
	b	_037FDF64
_037FDD20:
	ldrsh	r0, [r4]
	sub	r0, r0, r5
	strh	r0, [r4]
	b	_037FDF64
_037FDD30:
	ldrsh	r0, [r4]
	mul	r1, r0, r5
	strh	r1, [r4]
	b	_037FDF64
_037FDD40:
	cmp	r5, #0
	beq	_037FDF64
	ldrsh	r0, [r4]
	mov	r1, r5
	bl	_s32_div_f
	strh	r0, [r4]
	b	_037FDF64
_037FDD5C:
	cmp	r5, #0
	ldrgesh	r0, [r4]
	movge	r0, r0, lsl r5
	strgeh	r0, [r4]
	ldrltsh	r1, [r4]
	rsblt	r0, r5, #0
	movlt	r0, r1, asr r0
	strlth	r0, [r4]
	b	_037FDF64
_037FDD80:
	mov	r6, fp
	cmp	r5, #0
	movlt	r6, sl
	rsblt	r0, r5, #0
	movlt	r0, r0, lsl #16
	movlt	r5, r0, asr #16
	bl	SND_CalcRandom
	add	r1, r5, #1
	mul	r1, r0, r1
	mov	r0, r1, asr #16
	cmp	r6, #0
	rsbne	r0, r0, #0
	strh	r0, [r4]
	b	_037FDF64
_037FDDB8:
	ldrsh	r0, [r4]
	cmp	r0, r5
	moveq	r2, sl
	movne	r2, fp
	ldrb	r0, [r9]
	bic	r1, r0, #64	; 0x40
	and	r0, r2, #255	; 0xff
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #6
	strb	r0, [r9]
	b	_037FDF64
_037FDDE4:
	ldrsh	r0, [r4]
	cmp	r0, r5
	movge	r2, sl
	movlt	r2, fp
	ldrb	r0, [r9]
	bic	r1, r0, #64	; 0x40
	and	r0, r2, #255	; 0xff
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #6
	strb	r0, [r9]
	b	_037FDF64
_037FDE10:
	ldrsh	r0, [r4]
	cmp	r0, r5
	movgt	r2, sl
	movle	r2, fp
	ldrb	r0, [r9]
	bic	r1, r0, #64	; 0x40
	and	r0, r2, #255	; 0xff
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #6
	strb	r0, [r9]
	b	_037FDF64
_037FDE3C:
	ldrsh	r0, [r4]
	cmp	r0, r5
	movle	r2, sl
	movgt	r2, fp
	ldrb	r0, [r9]
	bic	r1, r0, #64	; 0x40
	and	r0, r2, #255	; 0xff
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #6
	strb	r0, [r9]
	b	_037FDF64
_037FDE68:
	ldrsh	r0, [r4]
	cmp	r0, r5
	movlt	r2, sl
	movge	r2, fp
	ldrb	r0, [r9]
	bic	r1, r0, #64	; 0x40
	and	r0, r2, #255	; 0xff
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #6
	strb	r0, [r9]
	b	_037FDF64
_037FDE94:
	ldrsh	r0, [r4]
	cmp	r0, r5
	movne	r2, sl
	moveq	r2, fp
	ldrb	r0, [r9]
	bic	r1, r0, #64	; 0x40
	and	r0, r2, #255	; 0xff
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #6
	strb	r0, [r9]
	b	_037FDF64
_037FDEC0:
	cmp	r6, #0
	beq	_037FDF64
	sub	r0, r7, #252	; 0xfc
	cmp	r0, #3
	addls	pc, pc, r0, lsl #2
	b	_037FDF64
	b	_037FDF10
	b	_037FDEE8
	b	_037FDF64
	b	_037FDF5C
_037FDEE8:
	ldrb	r0, [r9, #59]	; 0x3b
	cmp	r0, #0
	beq	_037FDF64
	sub	r0, r0, #1
	strb	r0, [r9, #59]	; 0x3b
	ldrb	r0, [r9, #59]	; 0x3b
	add	r0, r9, r0, lsl #2
	ldr	r0, [r0, #44]	; 0x2c
	str	r0, [r9, #40]	; 0x28
	b	_037FDF64
_037FDF10:
	ldrb	r0, [r9, #59]	; 0x3b
	cmp	r0, #0
	beq	_037FDF64
	sub	r1, r0, #1
	add	r2, r9, r1
	ldrb	r0, [r2, #56]	; 0x38
	cmp	r0, #0
	beq	_037FDF40
	sub	r0, r0, #1
	ands	r0, r0, #255	; 0xff
	streqb	r1, [r9, #59]	; 0x3b
	beq	_037FDF64
_037FDF40:
	strb	r0, [r2, #56]	; 0x38
	ldrb	r0, [r9, #59]	; 0x3b
	sub	r0, r0, #1
	add	r0, r9, r0, lsl #2
	ldr	r0, [r0, #44]	; 0x2c
	str	r0, [r9, #40]	; 0x28
	b	_037FDF64
_037FDF5C:
	mvn	r0, #0
	b	_037FDF84
_037FDF64:
	ldr	r0, [r9, #32]
	cmp	r0, #0
	bne	_037FDF80
	ldrb	r0, [r9]
	mov	r0, r0, lsl #27
	movs	r0, r0, lsr #31
	beq	_037FD6B4
_037FDF80:
	mov	r0, #0
_037FDF84:
	add	sp, sp, #52	; 0x34
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FDF90:	.word	_03807F4C

	arm_func_start FUN_037FDF94
FUN_037FDF94: ; 0x037FDF94
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	sub	sp, sp, #24
	mov	r8, r0
	mov	r7, r1
	mov	r6, r2
	mov	r5, r3
	mov	r4, #0
	ldrb	r0, [r8]
	mov	r0, r0, lsl #28
	movs	r0, r0, lsr #31
	beq	_037FDFD0
	ldr	r4, [r8, #60]	; 0x3c
	cmp	r4, #0
	strneb	r6, [r4, #8]
	strneb	r5, [r4, #9]
_037FDFD0:
	cmp	r4, #0
	bne	_037FE0C4
	ldr	r0, [r7, #32]
	ldrh	r1, [r8, #2]
	mov	r2, r6
	add	r3, sp, #8
	bl	SND_ReadInstData
	cmp	r0, #0
	beq	_037FE18C
	ldrb	r0, [sp, #8]
	cmp	r0, #4
	addls	pc, pc, r0, lsl #2
	b	_037FE030
	b	_037FE030
	b	_037FE018
	b	_037FE020
	b	_037FE028
	b	_037FE018
_037FE018:
	ldr	r1, _037FE198	; =0x0000FFFF
	b	_037FE034
_037FE020:
	mov	r1, #16128	; 0x3f00
	b	_037FE034
_037FE028:
	mov	r1, #49152	; 0xc000
	b	_037FE034
_037FE030:
	b	_037FE18C
_037FE034:
	ldrh	r0, [r8, #30]
	and	r0, r1, r0
	str	r8, [sp]
	ldrb	r2, [r7, #4]
	ldrb	r1, [r8, #18]
	add	r1, r2, r1
	ldrb	r2, [r8]
	mov	r2, r2, lsl #24
	mov	r2, r2, lsr #31
	ldr	r3, _037FE19C	; =FUN_037FE344
	bl	SND_AllocExChannel
	movs	r4, r0
	beq	_037FE18C
	ldrb	r0, [r8]
	mov	r0, r0, lsl #28
	movs	r0, r0, lsr #31
	mvnne	r3, #0
	ldreq	r3, [sp, #48]	; 0x30
	ldr	r0, [r7, #32]
	str	r0, [sp]
	add	r0, sp, #8
	str	r0, [sp, #4]
	mov	r0, r4
	mov	r1, r6
	mov	r2, r5
	bl	SND_NoteOn
	cmp	r0, #0
	bne	_037FE0B8
	mov	r0, #0
	strb	r0, [r4, #34]	; 0x22
	mov	r0, r4
	bl	SND_FreeExChannel
	b	_037FE18C
_037FE0B8:
	ldr	r0, [r8, #60]	; 0x3c
	str	r0, [r4, #80]	; 0x50
	str	r4, [r8, #60]	; 0x3c
_037FE0C4:
	ldrb	r1, [r8, #14]
	cmp	r1, #255	; 0xff
	beq	_037FE0D8
	mov	r0, r4
	bl	SND_SetExChannelAttack
_037FE0D8:
	ldrb	r1, [r8, #15]
	cmp	r1, #255	; 0xff
	beq	_037FE0EC
	mov	r0, r4
	bl	SND_SetExChannelDecay
_037FE0EC:
	ldrb	r1, [r8, #16]
	cmp	r1, #255	; 0xff
	beq	_037FE100
	mov	r0, r4
	bl	SND_SetExChannelSustain
_037FE100:
	ldrb	r1, [r8, #17]
	cmp	r1, #255	; 0xff
	beq	_037FE114
	mov	r0, r4
	bl	SND_SetExChannelRelease
_037FE114:
	ldrsh	r0, [r8, #22]
	strh	r0, [r4, #50]	; 0x32
	ldrb	r0, [r8]
	mov	r0, r0, lsl #26
	movs	r0, r0, lsr #31
	beq	_037FE144
	ldrsh	r1, [r4, #50]	; 0x32
	ldrb	r0, [r8, #20]
	sub	r0, r0, r6
	mov	r0, r0, lsl #22
	add	r0, r1, r0, asr #16
	strh	r0, [r4, #50]	; 0x32
_037FE144:
	ldrb	r0, [r8, #21]
	cmp	r0, #0
	bne	_037FE168
	ldr	r0, [sp, #48]	; 0x30
	str	r0, [r4, #24]
	ldrb	r0, [r4, #3]
	bic	r0, r0, #4
	strb	r0, [r4, #3]
	b	_037FE184
_037FE168:
	mul	r1, r0, r0
	ldrsh	r0, [r4, #50]	; 0x32
	cmp	r0, #0
	rsblt	r0, r0, #0
	mul	r0, r1, r0
	mov	r0, r0, asr #11
	str	r0, [r4, #24]
_037FE184:
	mov	r0, #0
	str	r0, [r4, #20]
_037FE18C:
	add	sp, sp, #24
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FE198:	.word	0x0000FFFF
_037FE19C:	.word	FUN_037FE344

	arm_func_start FUN_037FE1A0
FUN_037FE1A0: ; 0x037FE1A0
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, #0
	mov	r4, #1
_037FE1B0:
	mov	r0, r6
	mov	r1, r5
	bl	FUN_037FE460
	cmp	r0, #0
	beq	_037FE1D0
	mov	r1, r6
	mov	r2, r4
	bl	FUN_037FE1E4
_037FE1D0:
	add	r5, r5, #1
	cmp	r5, #16
	blt	_037FE1B0
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start FUN_037FE1E4
FUN_037FE1E4: ; 0x037FE1E4
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	fp, r2
	ldrb	r0, [r1, #5]
	mov	r0, r0, lsl #1
	ldr	r4, _037FE340	; =SNDi_DecibelSquareTable
	ldrsh	r3, [r4, r0]
	ldrb	r0, [sl, #4]
	mov	r0, r0, lsl #1
	ldrsh	r2, [r4, r0]
	ldrb	r0, [sl, #5]
	mov	r0, r0, lsl #1
	ldrsh	r0, [r4, r0]
	add	r0, r2, r0
	add	r3, r3, r0
	ldrsh	r2, [sl, #10]
	ldrsh	r0, [r1, #6]
	add	r2, r2, r0
	ldrsb	r4, [sl, #6]
	ldrb	r0, [sl, #7]
	mov	r0, r0, lsl #6
	mul	r1, r4, r0
	ldrsh	r0, [sl, #12]
	add	r0, r0, r1, asr #7
	ldrsb	r1, [sl, #8]
	ldrb	r4, [sl, #1]
	cmp	r4, #127	; 0x7f
	mulne	r4, r1, r4
	addne	r1, r4, #64	; 0x40
	movne	r1, r1, asr #7
	ldrsb	r4, [sl, #9]
	add	r1, r1, r4
	mov	r4, #32768	; 0x8000
	rsb	r4, r4, #0
	cmp	r3, r4
	movlt	r3, r4
	mov	r4, #32768	; 0x8000
	rsb	r4, r4, #0
	cmp	r2, r4
	movlt	r2, r4
	mvn	r4, #127	; 0x7f
	cmp	r1, r4
	movlt	r1, r4
	blt	_037FE2A0
	cmp	r1, #127	; 0x7f
	movgt	r1, #127	; 0x7f
_037FE2A0:
	ldr	r9, [sl, #60]	; 0x3c
	mov	r4, #1
	mov	r3, r3, lsl #16
	mov	r7, r3, asr #16
	mov	r0, r0, lsl #16
	mov	r6, r0, asr #16
	mov	r0, r1, lsl #24
	mov	r5, r0, asr #24
	mov	r0, r2, lsl #16
	mov	r8, r0, asr #16
	b	_037FE32C
_037FE2CC:
	strh	r8, [r9, #6]
	ldrb	r0, [r9, #2]
	cmp	r0, #3
	beq	_037FE328
	strh	r7, [r9, #12]
	strh	r6, [r9, #14]
	strb	r5, [r9, #11]
	ldrb	r0, [sl, #1]
	strb	r0, [r9, #4]
	ldrh	r0, [sl, #24]
	strh	r0, [r9, #40]	; 0x28
	ldrh	r0, [sl, #26]
	strh	r0, [r9, #42]	; 0x2a
	ldrh	r0, [sl, #28]
	strh	r0, [r9, #44]	; 0x2c
	ldr	r0, [r9, #52]	; 0x34
	cmp	r0, #0
	bne	_037FE328
	cmp	fp, #0
	beq	_037FE328
	strb	r4, [r9, #34]	; 0x22
	mov	r0, r9
	bl	SND_ReleaseExChannel
_037FE328:
	ldr	r9, [r9, #80]	; 0x50
_037FE32C:
	cmp	r9, #0
	bne	_037FE2CC
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FE340:	.word	SNDi_DecibelSquareTable

	arm_func_start FUN_037FE344
FUN_037FE344: ; 0x037FE344
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, r2
	cmp	r1, #1
	bne	_037FE368
	mov	r1, #0
	strb	r1, [r5, #34]	; 0x22
	bl	SND_FreeExChannel
_037FE368:
	ldr	r1, [r4, #60]	; 0x3c
	cmp	r1, r5
	ldreq	r0, [r5, #80]	; 0x50
	streq	r0, [r4, #60]	; 0x3c
	beq	_037FE3A0
	b	_037FE394
_037FE380:
	cmp	r0, r5
	ldreq	r0, [r5, #80]	; 0x50
	streq	r0, [r1, #80]	; 0x50
	beq	_037FE3A0
	mov	r1, r0
_037FE394:
	ldr	r0, [r1, #80]	; 0x50
	cmp	r0, #0
	bne	_037FE380
_037FE3A0:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start FUN_037FE3AC
FUN_037FE3AC: ; 0x037FE3AC
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, #0
_037FE3BC:
	mov	r0, r5
	mov	r1, r4
	bl	FUN_037FE3EC
	add	r4, r4, #1
	cmp	r4, #16
	blt	_037FE3BC
	ldrb	r0, [r5]
	bic	r0, r0, #1
	strb	r0, [r5]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start FUN_037FE3EC
FUN_037FE3EC: ; 0x037FE3EC
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, r1
	bl	FUN_037FE460
	cmp	r0, #0
	beq	_037FE430
	mov	r1, r5
	bl	FUN_037FE440
	add	r3, r5, #8
	ldr	r2, _037FE43C	; =_038086EC
	ldrb	r1, [r3, r4]
	ldrb	r0, [r2, r1, lsl #6]
	bic	r0, r0, #1
	strb	r0, [r2, r1, lsl #6]
	mov	r0, #255	; 0xff
	strb	r0, [r3, r4]
_037FE430:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FE43C:	.word	_038086EC

	arm_func_start FUN_037FE440
FUN_037FE440: ; 0x037FE440
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mvn	r2, #0
	bl	FUN_037FE588
	mov	r0, r4
	bl	FUN_037FE54C
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start FUN_037FE460
FUN_037FE460: ; 0x037FE460
	cmp	r1, #15
	movgt	r0, #0
	bxgt	lr
	add	r0, r0, r1
	ldrb	r1, [r0, #8]
	cmp	r1, #255	; 0xff
	moveq	r0, #0
	ldrne	r0, _037FE488	; =_038086EC
	addne	r0, r0, r1, lsl #6
	bx	lr
_037FE488:	.word	_038086EC

	arm_func_start FUN_037FE48C
FUN_037FE48C: ; 0x037FE48C
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r6, r0
	mov	r5, #0
	add	r1, r6, #28
	b	_037FE4B4
_037FE4A4:
	ldrh	r0, [r1]
	sub	r0, r0, #240	; 0xf0
	strh	r0, [r1]
	add	r5, r5, #1
_037FE4B4:
	ldrh	r0, [r6, #28]
	cmp	r0, #240	; 0xf0
	bcs	_037FE4A4
	mov	r4, #0
	mov	r7, #1
	b	_037FE4F0
_037FE4CC:
	mov	r0, r6
	mov	r1, r7
	bl	FUN_037FD548
	cmp	r0, #0
	beq	_037FE4EC
	mov	r0, r6
	bl	FUN_037FE3AC
	b	_037FE4F8
_037FE4EC:
	add	r4, r4, #1
_037FE4F0:
	cmp	r4, r5
	blt	_037FE4CC
_037FE4F8:
	ldr	r0, _037FE548	; =SNDi_SharedWork
	ldr	r0, [r0]
	cmp	r0, #0
	beq	_037FE524
	add	r3, r0, #64	; 0x40
	ldrb	r1, [r6, #1]
	mov	r0, #36	; 0x24
	mul	r2, r1, r0
	ldr	r0, [r3, r2]
	add	r0, r0, r4
	str	r0, [r3, r2]
_037FE524:
	ldrh	r2, [r6, #24]
	ldrh	r0, [r6, #26]
	mul	r1, r2, r0
	ldrh	r0, [r6, #28]
	add	r0, r0, r1, asr #8
	strh	r0, [r6, #28]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FE548:	.word	SNDi_SharedWork

	arm_func_start FUN_037FE54C
FUN_037FE54C: ; 0x037FE54C
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	ldr	r4, [r5, #60]	; 0x3c
	b	_037FE56C
_037FE560:
	mov	r0, r4
	bl	SND_FreeExChannel
	ldr	r4, [r4, #80]	; 0x50
_037FE56C:
	cmp	r4, #0
	bne	_037FE560
	mov	r0, #0
	str	r0, [r5, #60]	; 0x3c
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start FUN_037FE588
FUN_037FE588: ; 0x037FE588
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r4, r0
	mov	r7, r2
	mov	r2, #0
	bl	FUN_037FE1E4
	ldr	r6, [r4, #60]	; 0x3c
	and	r5, r7, #255	; 0xff
	mov	r4, #1
	b	_037FE5E4
_037FE5B0:
	mov	r0, r6
	bl	SND_IsExChannelActive
	cmp	r0, #0
	beq	_037FE5E0
	cmp	r7, #0
	blt	_037FE5D4
	mov	r0, r6
	mov	r1, r5
	bl	SND_SetExChannelRelease
_037FE5D4:
	strb	r4, [r6, #34]	; 0x22
	mov	r0, r6
	bl	SND_ReleaseExChannel
_037FE5E0:
	ldr	r6, [r6, #80]	; 0x50
_037FE5E4:
	cmp	r6, #0
	bne	_037FE5B0
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr

	arm_func_start FUN_037FE5F8
FUN_037FE5F8: ; 0x037FE5F8
	stmdb	sp!, {r4, lr}
	ldrb	r2, [r0]
	bic	r2, r2, #4
	strb	r2, [r0]
	str	r1, [r0, #32]
	mov	r1, #120	; 0x78
	strh	r1, [r0, #24]
	mov	r1, #256	; 0x100
	strh	r1, [r0, #26]
	mov	r1, #240	; 0xf0
	strh	r1, [r0, #28]
	mov	r1, #127	; 0x7f
	strb	r1, [r0, #5]
	mov	r3, #0
	strh	r3, [r0, #6]
	mov	r1, #64	; 0x40
	strb	r1, [r0, #4]
	mov	r2, #255	; 0xff
_037FE640:
	add	r1, r0, r3
	strb	r2, [r1, #8]
	add	r3, r3, #1
	cmp	r3, #16
	blt	_037FE640
	ldr	r2, _037FE6A4	; =SNDi_SharedWork
	ldr	r3, [r2]
	cmp	r3, #0
	beq	_037FE69C
	mov	r4, #0
	ldrb	ip, [r0, #1]
	mov	r1, #36	; 0x24
	mla	r3, ip, r1, r3
	str	r4, [r3, #64]	; 0x40
	mvn	lr, #0
_037FE67C:
	ldr	r3, [r2]
	ldrb	ip, [r0, #1]
	mla	r3, ip, r1, r3
	add	r3, r3, r4, lsl #1
	strh	lr, [r3, #32]
	add	r4, r4, #1
	cmp	r4, #16
	blt	_037FE67C
_037FE69C:
	ldmia	sp!, {r4, lr}
	bx	lr
_037FE6A4:	.word	SNDi_SharedWork

	arm_func_start FUN_037FE6A8
FUN_037FE6A8: ; 0x037FE6A8
	str	r1, [r0, #36]	; 0x24
	ldr	r1, [r0, #36]	; 0x24
	add	r1, r1, r2
	str	r1, [r0, #40]	; 0x28
	bx	lr

	arm_func_start FUN_037FE6BC
FUN_037FE6BC: ; 0x037FE6BC
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #0
	str	r0, [r4, #36]	; 0x24
	str	r0, [r4, #40]	; 0x28
	ldrb	r1, [r4]
	orr	r1, r1, #2
	strb	r1, [r4]
	ldrb	r1, [r4]
	bic	r1, r1, #4
	strb	r1, [r4]
	ldrb	r1, [r4]
	bic	r1, r1, #8
	strb	r1, [r4]
	ldrb	r1, [r4]
	bic	r1, r1, #16
	strb	r1, [r4]
	ldrb	r1, [r4]
	bic	r1, r1, #32
	strb	r1, [r4]
	ldrb	r1, [r4]
	orr	r1, r1, #64	; 0x40
	strb	r1, [r4]
	ldrb	r1, [r4]
	bic	r1, r1, #128	; 0x80
	strb	r1, [r4]
	strb	r0, [r4, #59]	; 0x3b
	strh	r0, [r4, #2]
	mov	r1, #64	; 0x40
	strb	r1, [r4, #18]
	mov	r2, #127	; 0x7f
	strb	r2, [r4, #4]
	strb	r2, [r4, #5]
	strh	r0, [r4, #10]
	strb	r0, [r4, #8]
	strb	r0, [r4, #9]
	strb	r0, [r4, #6]
	strh	r0, [r4, #12]
	mov	r1, #255	; 0xff
	strb	r1, [r4, #14]
	strb	r1, [r4, #15]
	strb	r1, [r4, #16]
	strb	r1, [r4, #17]
	strb	r2, [r4, #1]
	mov	r1, #2
	strb	r1, [r4, #7]
	mov	r1, #60	; 0x3c
	strb	r1, [r4, #20]
	strb	r0, [r4, #21]
	strh	r0, [r4, #22]
	strb	r0, [r4, #19]
	ldr	r0, _037FE7AC	; =0x0000FFFF
	strh	r0, [r4, #30]
	add	r0, r4, #24
	bl	SND_InitLfoParam
	mov	r0, #0
	str	r0, [r4, #32]
	str	r0, [r4, #60]	; 0x3c
	ldmia	sp!, {r4, lr}
	bx	lr
_037FE7AC:	.word	0x0000FFFF

	arm_func_start FUN_037FE7B0
FUN_037FE7B0: ; 0x037FE7B0
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r4, r0
	mov	r6, r1
	cmp	r2, #4
	addls	pc, pc, r2, lsl #2
	b	_037FE86C
	b	_037FE7DC
	b	_037FE7F8
	b	_037FE804
	b	_037FE83C
	b	_037FE810
_037FE7DC:
	ldr	r0, [r4, #40]	; 0x28
	bl	FUN_037FE968
	mov	r5, r0
	ldr	r0, [r4, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r4, #40]	; 0x28
	b	_037FE86C
_037FE7F8:
	bl	FUN_037FE918
	mov	r5, r0
	b	_037FE86C
_037FE804:
	bl	FUN_037FE878
	mov	r5, r0
	b	_037FE86C
_037FE810:
	ldr	r0, [r4, #40]	; 0x28
	bl	FUN_037FE968
	mov	r1, r0
	ldr	r0, [r4, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r4, #40]	; 0x28
	mov	r0, r6
	bl	FUN_037FD504
	cmp	r0, #0
	ldrnesh	r5, [r0]
	b	_037FE86C
_037FE83C:
	bl	FUN_037FE918
	mov	r5, r0, lsl #16
	mov	r0, r4
	bl	FUN_037FE918
	mov	r0, r0, lsl #16
	mov	r4, r0, asr #16
	bl	SND_CalcRandom
	sub	r1, r4, r5, asr #16
	add	r1, r1, #1
	mul	r1, r0, r1
	mov	r0, r1, asr #16
	add	r5, r0, r5, asr #16
_037FE86C:
	mov	r0, r5
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start FUN_037FE878
FUN_037FE878: ; 0x037FE878
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, #0
	add	r4, r6, #40	; 0x28
_037FE888:
	ldr	r0, [r6, #40]	; 0x28
	bl	FUN_037FE968
	ldr	r1, [r4]
	add	r1, r1, #1
	str	r1, [r4]
	and	r1, r0, #127	; 0x7f
	orr	r5, r1, r5, lsl #7
	ands	r0, r0, #128	; 0x80
	bne	_037FE888
	mov	r0, r5
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start FUN_037FE8B8
FUN_037FE8B8: ; 0x037FE8B8
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r4, r0
	ldr	r0, [r4, #40]	; 0x28
	bl	FUN_037FE968
	mov	r5, r0
	ldr	r0, [r4, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r4, #40]	; 0x28
	ldr	r0, [r4, #40]	; 0x28
	bl	FUN_037FE968
	ldr	r1, [r4, #40]	; 0x28
	add	r1, r1, #1
	str	r1, [r4, #40]	; 0x28
	orr	r5, r5, r0, lsl #8
	ldr	r0, [r4, #40]	; 0x28
	bl	FUN_037FE968
	ldr	r1, [r4, #40]	; 0x28
	add	r1, r1, #1
	str	r1, [r4, #40]	; 0x28
	orr	r0, r5, r0, lsl #16
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start FUN_037FE918
FUN_037FE918: ; 0x037FE918
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	ldr	r0, [r5, #40]	; 0x28
	bl	FUN_037FE968
	mov	r4, r0
	ldr	r0, [r5, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r5, #40]	; 0x28
	ldr	r0, [r5, #40]	; 0x28
	bl	FUN_037FE968
	ldr	r1, [r5, #40]	; 0x28
	add	r1, r1, #1
	str	r1, [r5, #40]	; 0x28
	orr	r0, r4, r0, lsl #8
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start FUN_037FE968
FUN_037FE968: ; 0x037FE968
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	ldr	r0, _037FE9B0	; =_03807F50
	ldr	r1, [r0]
	cmp	r4, r1
	bcc	_037FE98C
	ldr	r0, [r0, #4]
	cmp	r4, r0
	bcc	_037FE994
_037FE98C:
	mov	r0, r4
	bl	FUN_037FE9B8
_037FE994:
	ldr	r0, _037FE9B0	; =_03807F50
	ldr	r0, [r0]
	sub	r1, r4, r0
	ldr	r0, _037FE9B4	; =_03807F58
	ldrb	r0, [r0, r1]
	ldmia	sp!, {r4, lr}
	bx	lr
_037FE9B0:	.word	_03807F50
_037FE9B4:	.word	_03807F58

	arm_func_start FUN_037FE9B8
FUN_037FE9B8: ; 0x037FE9B8
	bic	r2, r0, #3
	ldr	r0, _037FE9F0	; =_03807F50
	str	r2, [r0]
	add	r1, r2, #16
	str	r1, [r0, #4]
	ldr	r1, [r2]
	str	r1, [r0, #8]
	ldr	r1, [r2, #4]
	str	r1, [r0, #12]
	ldr	r1, [r2, #8]
	str	r1, [r0, #16]
	ldr	r1, [r2, #12]
	str	r1, [r0, #20]
	bx	lr
_037FE9F0:	.word	_03807F50

	arm_func_start SNDi_SetTrackParam
SNDi_SetTrackParam: ; 0x037FE9F4
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r1
	mov	r9, r2
	mov	r8, r3
	ldr	r7, [sp, #40]	; 0x28
	ldr	r2, _037FEA94	; =_038084AC
	mov	r1, #36	; 0x24
	mla	fp, r0, r1, r2
	mov	r6, #0
	mov	r0, r8, lsl #16
	mov	r4, r0, lsr #16
	and	r5, r8, #255	; 0xff
	b	_037FEA78
_037FEA2C:
	ands	r0, sl, #1
	beq	_037FEA70
	mov	r0, fp
	mov	r1, r6
	bl	FUN_037FE460
	cmp	r0, #0
	beq	_037FEA70
	cmp	r7, #1
	beq	_037FEA64
	cmp	r7, #2
	beq	_037FEA6C
	cmp	r7, #4
	streq	r8, [r0, r9]
	b	_037FEA70
_037FEA64:
	strb	r5, [r0, r9]
	b	_037FEA70
_037FEA6C:
	strh	r4, [r0, r9]
_037FEA70:
	add	r6, r6, #1
	mov	sl, sl, lsr #1
_037FEA78:
	cmp	r6, #16
	bge	_037FEA88
	cmp	sl, #0
	bne	_037FEA2C
_037FEA88:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FEA94:	.word	_038084AC

	arm_func_start SNDi_SetPlayerParam
SNDi_SetPlayerParam: ; 0x037FEA98
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	lr, _037FEAE0	; =_038084AC
	mov	ip, #36	; 0x24
	mla	ip, r0, ip, lr
	cmp	r3, #1
	beq	_037FEAC8
	cmp	r3, #2
	beq	_037FEAD0
	cmp	r3, #4
	streq	r2, [ip, r1]
	b	_037FEAD4
_037FEAC8:
	strb	r2, [ip, r1]
	b	_037FEAD4
_037FEAD0:
	strh	r2, [ip, r1]
_037FEAD4:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FEAE0:	.word	_038084AC

	arm_func_start SND_InvalidateBank
SND_InvalidateBank: ; 0x037FEAE4
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r7, r0
	mov	r6, r1
	mov	r5, #0
	ldr	r4, _037FEB40	; =_038084AC
	mov	r8, #36	; 0x24
_037FEAFC:
	mul	r1, r5, r8
	add	r0, r4, r1
	ldrb	r1, [r4, r1]
	mov	r1, r1, lsl #31
	movs	r1, r1, lsr #31
	beq	_037FEB2C
	ldr	r1, [r0, #32]
	cmp	r7, r1
	bhi	_037FEB2C
	cmp	r1, r6
	bhi	_037FEB2C
	bl	FUN_037FE3AC
_037FEB2C:
	add	r5, r5, #1
	cmp	r5, #16
	blt	_037FEAFC
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FEB40:	.word	_038084AC

	arm_func_start SND_InvalidateSeq
SND_InvalidateSeq: ; 0x037FEB44
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	r9, r1
	mov	r7, #0
	mov	r5, r7
	ldr	fp, _037FEBDC	; =_038084AC
	mov	r4, #36	; 0x24
_037FEB64:
	mul	r0, r7, r4
	add	r8, fp, r0
	ldrb	r0, [fp, r0]
	mov	r0, r0, lsl #31
	movs	r0, r0, lsr #31
	beq	_037FEBC4
	mov	r6, r5
	b	_037FEBBC
_037FEB84:
	mov	r0, r8
	mov	r1, r6
	bl	FUN_037FE460
	cmp	r0, #0
	beq	_037FEBB8
	ldr	r0, [r0, #40]	; 0x28
	cmp	sl, r0
	bhi	_037FEBB8
	cmp	r0, r9
	bhi	_037FEBB8
	mov	r0, r8
	bl	FUN_037FE3AC
	b	_037FEBC4
_037FEBB8:
	add	r6, r6, #1
_037FEBBC:
	cmp	r6, #16
	blt	_037FEB84
_037FEBC4:
	add	r7, r7, #1
	cmp	r7, #16
	blt	_037FEB64
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FEBDC:	.word	_038084AC

	arm_func_start SND_SetTrackAllocatableChannel
SND_SetTrackAllocatableChannel: ; 0x037FEBE0
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r6, r1
	ldr	r3, _037FEC54	; =_038084AC
	mov	r1, #36	; 0x24
	mla	r5, r0, r1, r3
	mov	r4, #0
	mov	r0, r2, lsl #16
	mov	r7, r0, lsr #16
	b	_037FEC38
_037FEC08:
	ands	r0, r6, #1
	beq	_037FEC30
	mov	r0, r5
	mov	r1, r4
	bl	FUN_037FE460
	cmp	r0, #0
	strneh	r7, [r0, #30]
	ldrneb	r1, [r0]
	orrne	r1, r1, #128	; 0x80
	strneb	r1, [r0]
_037FEC30:
	add	r4, r4, #1
	mov	r6, r6, lsr #1
_037FEC38:
	cmp	r4, #16
	bge	_037FEC48
	cmp	r6, #0
	bne	_037FEC08
_037FEC48:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FEC54:	.word	_038084AC

	arm_func_start SND_SetTrackMute
SND_SetTrackMute: ; 0x037FEC58
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r1
	mov	r6, r2
	ldr	r2, _037FECC8	; =_038084AC
	mov	r1, #36	; 0x24
	mla	r5, r0, r1, r2
	mov	r4, #0
	b	_037FECAC
_037FEC7C:
	ands	r0, r7, #1
	beq	_037FECA4
	mov	r0, r5
	mov	r1, r4
	bl	FUN_037FE460
	cmp	r0, #0
	beq	_037FECA4
	mov	r1, r5
	mov	r2, r6
	bl	FUN_037FD440
_037FECA4:
	add	r4, r4, #1
	mov	r7, r7, lsr #1
_037FECAC:
	cmp	r4, #16
	bge	_037FECBC
	cmp	r7, #0
	bne	_037FEC7C
_037FECBC:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FECC8:	.word	_038084AC

	arm_func_start SND_SkipSeq
SND_SkipSeq: ; 0x037FECCC
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r6, r1
	ldr	r2, _037FED90	; =_038084AC
	mov	r1, #36	; 0x24
	mla	r5, r0, r1, r2
	mov	r8, #0
	mov	r4, #127	; 0x7f
_037FECE8:
	mov	r0, r5
	mov	r1, r8
	bl	FUN_037FE460
	movs	r7, r0
	beq	_037FED10
	mov	r1, r5
	mov	r2, r4
	bl	FUN_037FE588
	mov	r0, r7
	bl	FUN_037FE54C
_037FED10:
	add	r8, r8, #1
	cmp	r8, #16
	blt	_037FECE8
	bl	SND_StopIntervalTimer
	mov	r4, #0
	mov	r7, r4
	b	_037FED50
_037FED2C:
	mov	r0, r5
	mov	r1, r7
	bl	FUN_037FD548
	cmp	r0, #0
	beq	_037FED4C
	mov	r0, r5
	bl	FUN_037FE3AC
	b	_037FED58
_037FED4C:
	add	r4, r4, #1
_037FED50:
	cmp	r4, r6
	bcc	_037FED2C
_037FED58:
	bl	SND_StartIntervalTimer
	ldr	r0, _037FED94	; =SNDi_SharedWork
	ldr	r0, [r0]
	cmp	r0, #0
	beq	_037FED88
	add	r3, r0, #64	; 0x40
	ldrb	r1, [r5, #1]
	mov	r0, #36	; 0x24
	mul	r2, r1, r0
	ldr	r0, [r3, r2]
	add	r0, r0, r4
	str	r0, [r3, r2]
_037FED88:
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FED90:	.word	_038084AC
_037FED94:	.word	SNDi_SharedWork

	arm_func_start SND_PauseSeq
SND_PauseSeq: ; 0x037FED98
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	ldr	r5, _037FEE18	; =_038084AC
	mov	r2, #36	; 0x24
	mul	r3, r0, r2
	add	r4, r5, r3
	ldrb	r0, [r5, r3]
	bic	r2, r0, #4
	and	r0, r1, #255	; 0xff
	and	r0, r0, #1
	orr	r0, r2, r0, lsl #2
	strb	r0, [r5, r3]
	cmp	r1, #0
	beq	_037FEE0C
	mov	r7, #0
	mov	r5, #127	; 0x7f
_037FEDD8:
	mov	r0, r4
	mov	r1, r7
	bl	FUN_037FE460
	movs	r6, r0
	beq	_037FEE00
	mov	r1, r4
	mov	r2, r5
	bl	FUN_037FE588
	mov	r0, r6
	bl	FUN_037FE54C
_037FEE00:
	add	r7, r7, #1
	cmp	r7, #16
	blt	_037FEDD8
_037FEE0C:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FEE18:	.word	_038084AC

	arm_func_start SND_StopSeq
SND_StopSeq: ; 0x037FEE1C
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	ldr	r2, _037FEE70	; =_038084AC
	mov	r0, #36	; 0x24
	mul	r1, r4, r0
	add	r0, r2, r1
	ldrb	r1, [r2, r1]
	mov	r1, r1, lsl #31
	movs	r1, r1, lsr #31
	beq	_037FEE68
	bl	FUN_037FE3AC
	ldr	r0, _037FEE74	; =SNDi_SharedWork
	ldr	r2, [r0]
	cmp	r2, #0
	ldrne	r1, [r2, #4]
	movne	r0, #1
	mvnne	r0, r0, lsl r4
	andne	r0, r1, r0
	strne	r0, [r2, #4]
_037FEE68:
	ldmia	sp!, {r4, lr}
	bx	lr
_037FEE70:	.word	_038084AC
_037FEE74:	.word	SNDi_SharedWork

	arm_func_start SND_StartSeq
SND_StartSeq: ; 0x037FEE78
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	bl	SND_PrepareSeq
	mov	r0, r4
	bl	SND_StartPreparedSeq
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start SND_StartPreparedSeq
SND_StartPreparedSeq: ; 0x037FEE94
	ldr	r2, _037FEEB0	; =_038084AC
	mov	r1, #36	; 0x24
	mul	r1, r0, r1
	ldrb	r0, [r2, r1]
	orr	r0, r0, #2
	strb	r0, [r2, r1]
	bx	lr
_037FEEB0:	.word	_038084AC

	arm_func_start SND_PrepareSeq
SND_PrepareSeq: ; 0x037FEEB4
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r4, r0
	mov	r8, r1
	mov	r6, r2
	mov	r5, r3
	ldr	r1, _037FEFFC	; =_038084AC
	mov	r0, #36	; 0x24
	mul	r0, r4, r0
	add	r7, r1, r0
	ldrb	r0, [r1, r0]
	mov	r0, r0, lsl #31
	movs	r0, r0, lsr #31
	beq	_037FEEF4
	mov	r0, r7
	bl	FUN_037FE3AC
_037FEEF4:
	mov	r0, r7
	mov	r1, r5
	bl	FUN_037FE5F8
	bl	FUN_037FD4C0
	movs	r9, r0
	bmi	_037FEFF0
	ldr	r0, _037FF000	; =_038086EC
	add	r5, r0, r9, lsl #6
	mov	r0, r5
	bl	FUN_037FE6BC
	mov	r0, r5
	mov	r1, r8
	mov	r2, r6
	bl	FUN_037FE6A8
	strb	r9, [r7, #8]
	ldr	r0, [r5, #40]	; 0x28
	bl	FUN_037FE9B8
	ldr	r0, [r5, #40]	; 0x28
	bl	FUN_037FE968
	add	r2, r5, #40	; 0x28
	ldr	r1, [r5, #40]	; 0x28
	add	r1, r1, #1
	str	r1, [r5, #40]	; 0x28
	cmp	r0, #254	; 0xfe
	ldrne	r0, [r2]
	subne	r0, r0, #1
	strne	r0, [r2]
	bne	_037FEFB8
	mov	r0, r5
	bl	FUN_037FE918
	mov	r0, r0, lsl #15
	mov	r5, r0, lsr #16
	mov	r6, #1
	ldr	r8, _037FF000	; =_038086EC
	b	_037FEFB0
_037FEF80:
	ands	r0, r5, #1
	beq	_037FEFA4
	bl	FUN_037FD4C0
	movs	r9, r0
	bmi	_037FEFB8
	add	r0, r8, r9, lsl #6
	bl	FUN_037FE6BC
	add	r0, r7, r6
	strb	r9, [r0, #8]
_037FEFA4:
	add	r6, r6, #1
	mov	r0, r5, lsl #15
	mov	r5, r0, lsr #16
_037FEFB0:
	cmp	r5, #0
	bne	_037FEF80
_037FEFB8:
	ldrb	r0, [r7]
	bic	r0, r0, #1
	orr	r0, r0, #1
	strb	r0, [r7]
	ldrb	r0, [r7]
	bic	r0, r0, #2
	strb	r0, [r7]
	ldr	r0, _037FF004	; =SNDi_SharedWork
	ldr	r2, [r0]
	cmp	r2, #0
	ldrne	r1, [r2, #4]
	movne	r0, #1
	orrne	r0, r1, r0, lsl r4
	strne	r0, [r2, #4]
_037FEFF0:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037FEFFC:	.word	_038084AC
_037FF000:	.word	_038086EC
_037FF004:	.word	SNDi_SharedWork

	arm_func_start SND_SeqMain
SND_SeqMain: ; 0x037FF008
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	mov	r8, r0
	mov	r5, #0
	mov	r6, r5
	mov	sl, #1
	ldr	r4, _037FF0A0	; =_038084AC
	mov	r9, #36	; 0x24
_037FF024:
	mul	r0, r6, r9
	add	r7, r4, r0
	ldrb	r1, [r4, r0]
	mov	r0, r1, lsl #31
	movs	r0, r0, lsr #31
	beq	_037FF07C
	mov	r0, r1, lsl #30
	movs	r0, r0, lsr #31
	beq	_037FF06C
	cmp	r8, #0
	beq	_037FF064
	mov	r0, r1, lsl #29
	movs	r0, r0, lsr #31
	bne	_037FF064
	mov	r0, r7
	bl	FUN_037FE48C
_037FF064:
	mov	r0, r7
	bl	FUN_037FE1A0
_037FF06C:
	ldrb	r0, [r7]
	mov	r0, r0, lsl #31
	movs	r0, r0, lsr #31
	orrne	r5, r5, sl, lsl r6
_037FF07C:
	add	r6, r6, #1
	cmp	r6, #16
	blt	_037FF024
	ldr	r0, _037FF0A4	; =SNDi_SharedWork
	ldr	r0, [r0]
	cmp	r0, #0
	strne	r5, [r0, #4]
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	bx	lr
_037FF0A0:	.word	_038084AC
_037FF0A4:	.word	SNDi_SharedWork

	arm_func_start SND_SeqInit
SND_SeqInit: ; 0x037FF0A8
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	lr, #0
	ldr	r3, _037FF10C	; =_038084AC
	mov	r0, #36	; 0x24
_037FF0BC:
	mul	r2, lr, r0
	add	ip, r3, r2
	ldrb	r1, [r3, r2]
	bic	r1, r1, #1
	strb	r1, [r3, r2]
	strb	lr, [ip, #1]
	add	lr, lr, #1
	cmp	lr, #16
	blt	_037FF0BC
	mov	r2, #0
	ldr	r1, _037FF110	; =_038086EC
_037FF0E8:
	ldrb	r0, [r1, r2, lsl #6]
	bic	r0, r0, #1
	strb	r0, [r1, r2, lsl #6]
	add	r2, r2, #1
	cmp	r2, #32
	blt	_037FF0E8
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FF10C:	.word	_038084AC
_037FF110:	.word	_038086EC

	arm_func_start FUN_037FF114
FUN_037FF114: ; 0x037FF114
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	add	r0, r0, r1, lsl #3
	ldr	r0, [r0, #24]
	cmp	r0, #0
	moveq	r0, #0
	beq	_037FF148
	ldr	r1, [r0, #56]	; 0x38
	cmp	r2, r1
	movcs	r0, #0
	bcs	_037FF148
	mov	r1, r2
	bl	SND_GetWaveDataAddress
_037FF148:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start SND_NoteOn
SND_NoteOn: ; 0x037FF154
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r9, r0
	mov	r8, r1
	mov	r7, r2
	mov	r6, r3
	ldr	r5, [sp, #36]	; 0x24
	ldrb	r4, [r5, #10]
	cmp	r4, #255	; 0xff
	mvneq	r6, #0
	moveq	r4, #0
	ldrb	r0, [r5]
	cmp	r0, #4
	addls	pc, pc, r0, lsl #2
	b	_037FF210
	b	_037FF210
	b	_037FF1A4
	b	_037FF1EC
	b	_037FF200
	b	_037FF1A4
_037FF1A4:
	cmp	r0, #1
	ldrneh	r1, [r5, #4]
	ldrneh	r0, [r5, #2]
	orrne	r1, r0, r1, lsl #16
	bne	_037FF1CC
	ldr	r0, [sp, #32]
	ldrh	r1, [r5, #4]
	ldrh	r2, [r5, #2]
	bl	FUN_037FF114
	mov	r1, r0
_037FF1CC:
	cmp	r1, #0
	moveq	r0, #0
	beq	_037FF214
	mov	r0, r9
	add	r2, r1, #12
	mov	r3, r6
	bl	SND_StartExChannelPcm
	b	_037FF214
_037FF1EC:
	mov	r0, r9
	ldrh	r1, [r5, #2]
	mov	r2, r6
	bl	SND_StartExChannelPsg
	b	_037FF214
_037FF200:
	mov	r0, r9
	mov	r1, r6
	bl	SND_StartExChannelNoise
	b	_037FF214
_037FF210:
	mov	r0, #0
_037FF214:
	cmp	r0, #0
	moveq	r0, #0
	beq	_037FF270
	strb	r8, [r9, #8]
	ldrb	r0, [r5, #6]
	strb	r0, [r9, #5]
	strb	r7, [r9, #9]
	mov	r0, r9
	ldrb	r1, [r5, #7]
	bl	SND_SetExChannelAttack
	mov	r0, r9
	ldrb	r1, [r5, #8]
	bl	SND_SetExChannelDecay
	mov	r0, r9
	ldrb	r1, [r5, #9]
	bl	SND_SetExChannelSustain
	mov	r0, r9
	mov	r1, r4
	bl	SND_SetExChannelRelease
	ldrb	r0, [r5, #11]
	sub	r0, r0, #64	; 0x40
	strb	r0, [r9, #10]
	mov	r0, #1
_037FF270:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr

	arm_func_start SND_GetWaveDataAddress
SND_GetWaveDataAddress: ; 0x037FF27C
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, r1
	bl	SNDi_LockMutex
	add	r0, r5, r4, lsl #2
	ldr	r4, [r0, #60]	; 0x3c
	cmp	r4, #0
	beq	_037FF2AC
	cmp	r4, #33554432	; 0x2000000
	addcc	r4, r5, r4
	b	_037FF2B0
_037FF2AC:
	mov	r4, #0
_037FF2B0:
	bl	SNDi_UnlockMutex
	mov	r0, r4
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start SND_ReadInstData
SND_ReadInstData: ; 0x037FF2C4
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r6, r0
	movs	r7, r1
	mov	r5, r2
	mov	r4, r3
	movmi	r0, #0
	bmi	_037FF43C
	bl	SNDi_LockMutex
	ldr	r0, [r6, #56]	; 0x38
	cmp	r7, r0
	bcc	_037FF300
	bl	SNDi_UnlockMutex
	mov	r0, #0
	b	_037FF43C
_037FF300:
	add	r0, r6, r7, lsl #2
	ldr	r3, [r0, #60]	; 0x3c
	strb	r3, [r4]
	ldrb	r0, [r4]
	cmp	r0, #17
	addls	pc, pc, r0, lsl #2
	b	_037FF428
	b	_037FF428
	b	_037FF364
	b	_037FF364
	b	_037FF364
	b	_037FF364
	b	_037FF364
	b	_037FF428
	b	_037FF428
	b	_037FF428
	b	_037FF428
	b	_037FF428
	b	_037FF428
	b	_037FF428
	b	_037FF428
	b	_037FF428
	b	_037FF428
	b	_037FF384
	b	_037FF3D4
_037FF364:
	add	r3, r6, r3, lsr #8
	add	r2, r4, #2
	mov	r1, #5
_037FF370:
	ldrh	r0, [r3], #2
	strh	r0, [r2], #2
	subs	r1, r1, #1
	bne	_037FF370
	b	_037FF434
_037FF384:
	add	r2, r6, r3, lsr #8
	ldrb	r1, [r2, #1]
	ldrb	r0, [r6, r3, lsr #8]
	cmp	r5, r0
	blt	_037FF3A0
	cmp	r5, r1
	ble	_037FF3AC
_037FF3A0:
	bl	SNDi_UnlockMutex
	mov	r0, #0
	b	_037FF43C
_037FF3AC:
	sub	r1, r5, r0
	mov	r0, #12
	mla	r0, r1, r0, r2
	add	r2, r0, #2
	mov	r1, #6
_037FF3C0:
	ldrh	r0, [r2], #2
	strh	r0, [r4], #2
	subs	r1, r1, #1
	bne	_037FF3C0
	b	_037FF434
_037FF3D4:
	mov	r2, #0
	add	r1, r6, r3, lsr #8
	b	_037FF3F8
_037FF3E0:
	add	r2, r2, #1
	cmp	r2, #8
	blt	_037FF3F8
	bl	SNDi_UnlockMutex
	mov	r0, #0
	b	_037FF43C
_037FF3F8:
	ldrb	r0, [r1, r2]
	cmp	r5, r0
	bgt	_037FF3E0
	mov	r0, #12
	mla	r0, r2, r0, r1
	add	r2, r0, #8
	mov	r1, #6
_037FF414:
	ldrh	r0, [r2], #2
	strh	r0, [r4], #2
	subs	r1, r1, #1
	bne	_037FF414
	b	_037FF434
_037FF428:
	bl	SNDi_UnlockMutex
	mov	r0, #0
	b	_037FF43C
_037FF434:
	bl	SNDi_UnlockMutex
	mov	r0, #1
_037FF43C:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr

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

	arm_func_start FUN_037FF524
FUN_037FF524: ; 0x037FF524
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, #7
	mov	r4, #0
_037FF534:
	mov	r0, r5
	mov	r1, r6
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	blt	_037FF534
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start SND_StopAlarm
SND_StopAlarm: ; 0x037FF554
	stmdb	sp!, {r4, lr}
	ldr	r1, _037FF590	; =_03808EEC
	add	r4, r1, r0, lsl #6
	ldrb	r0, [r1, r0, lsl #6]
	cmp	r0, #0
	beq	_037FF588
	add	r0, r4, #20
	bl	OS_CancelAlarm
	ldrb	r0, [r4, #1]
	add	r0, r0, #1
	strb	r0, [r4, #1]
	mov	r0, #0
	strb	r0, [r4]
_037FF588:
	ldmia	sp!, {r4, lr}
	bx	lr
_037FF590:	.word	_03808EEC

	arm_func_start SND_StartAlarm
SND_StartAlarm: ; 0x037FF594
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #12
	mov	r4, r0
	ldr	r0, _037FF654	; =_03808EEC
	add	r5, r0, r4, lsl #6
	ldrb	r0, [r0, r4, lsl #6]
	cmp	r0, #0
	beq	_037FF5C4
	add	r0, r5, #20
	bl	OS_CancelAlarm
	mov	r0, #0
	strb	r0, [r5]
_037FF5C4:
	ldr	r9, [r5, #4]
	ldr	r8, [r5, #8]
	ldr	r7, [r5, #12]
	ldr	r6, [r5, #16]
	ldrb	r0, [r5, #1]
	orr	r4, r4, r0, lsl #8
	add	r0, r5, #20
	bl	OS_CreateAlarm
	mov	r0, #0
	cmp	r6, r0
	cmpeq	r7, r0
	bne	_037FF610
	str	r4, [sp]
	add	r0, r5, #20
	mov	r1, r9
	mov	r2, r8
	ldr	r3, _037FF658	; =FUN_037FF524
	bl	OS_SetAlarm
	b	_037FF640
_037FF610:
	bl	OS_GetTick
	mov	r2, r0
	ldr	r0, _037FF658	; =FUN_037FF524
	str	r0, [sp, #4]
	str	r4, [sp, #8]
	mov	r3, r7
	str	r6, [sp]
	add	r0, r5, #20
	adds	r4, r9, r2
	adc	r2, r8, r1
	mov	r1, r4
	bl	OS_SetPeriodicAlarm
_037FF640:
	mov	r0, #1
	strb	r0, [r5]
	add	sp, sp, #12
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037FF654:	.word	_03808EEC
_037FF658:	.word	FUN_037FF524

	arm_func_start SND_SetupAlarm
SND_SetupAlarm: ; 0x037FF65C
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r8, r1
	mov	r7, r2
	mov	r6, r3
	ldr	r5, [sp, #24]
	ldr	r1, _037FF6B4	; =_03808EEC
	add	r4, r1, r0, lsl #6
	ldrb	r0, [r1, r0, lsl #6]
	cmp	r0, #0
	beq	_037FF694
	add	r0, r4, #20
	bl	OS_CancelAlarm
	mov	r0, #0
	strb	r0, [r4]
_037FF694:
	str	r8, [r4, #4]
	str	r7, [r4, #8]
	str	r6, [r4, #12]
	str	r5, [r4, #16]
	ldr	r0, [sp, #28]
	strb	r0, [r4, #1]
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FF6B4:	.word	_03808EEC

	arm_func_start SND_AlarmInit
SND_AlarmInit: ; 0x037FF6B8
	mov	r3, #0
	mov	r2, r3
	ldr	r1, _037FF6E0	; =SNDi_Work
_037FF6C4:
	add	r0, r1, r3, lsl #6
	strb	r2, [r0, #3968]	; 0xf80
	strb	r2, [r0, #3969]	; 0xf81
	add	r3, r3, #1
	cmp	r3, #8
	blt	_037FF6C4
	bx	lr
_037FF6E0:	.word	SNDi_Work

	arm_func_start FUN_037FF6E4
FUN_037FF6E4: ; 0x037FF6E4
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	ldr	r0, _037FF74C	; =SNDi_Work
	mov	r1, r5
	mov	r2, #4480	; 0x1180
	bl	MIi_CpuCopy32
	ldr	r1, _037FF74C	; =SNDi_Work
	add	r0, r5, #4096	; 0x1000
	str	r1, [r0, #448]	; 0x1c0
	mov	r4, #0
_037FF710:
	mov	r0, r4
	bl	SND_GetChannelControl
	add	r1, r5, r4, lsl #2
	add	r1, r1, #4096	; 0x1000
	str	r0, [r1, #384]	; 0x180
	add	r4, r4, #1
	cmp	r4, #16
	blt	_037FF710
	mov	r0, #0
	bl	SND_GetLockedChannel
	add	r1, r5, #4096	; 0x1000
	str	r0, [r1, #452]	; 0x1c4
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FF74C:	.word	SNDi_Work

	arm_func_start FUN_037FF750
FUN_037FF750: ; 0x037FF750
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r9, r2
	mov	r5, r3
	bl	OS_DisableInterrupts
	mov	r4, r0
	mov	r8, #0
	b	_037FF790
_037FF778:
	ands	r0, r9, #1
	beq	_037FF788
	mov	r0, r8
	bl	SND_StopAlarm
_037FF788:
	add	r8, r8, #1
	mov	r9, r9, lsr #1
_037FF790:
	cmp	r8, #8
	bge	_037FF7A0
	cmp	r9, #0
	bne	_037FF778
_037FF7A0:
	mov	r8, #0
	b	_037FF7C4
_037FF7A8:
	ands	r0, r7, #1
	beq	_037FF7BC
	mov	r0, r8
	mov	r1, r5
	bl	SND_StopChannel
_037FF7BC:
	add	r8, r8, #1
	mov	r7, r7, lsr #1
_037FF7C4:
	cmp	r8, #16
	bge	_037FF7D4
	cmp	r7, #0
	bne	_037FF7A8
_037FF7D4:
	ands	r0, r6, #1
	movne	r1, #0
	ldrne	r0, _037FF80C	; =0x04000508
	strneb	r1, [r0]
	ands	r0, r6, #2
	movne	r1, #0
	ldrne	r0, _037FF810	; =0x04000509
	strneb	r1, [r0]
	mov	r0, r4
	bl	OS_RestoreInterrupts
	bl	SND_UpdateSharedWork
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037FF80C:	.word	0x04000508
_037FF810:	.word	0x04000509

	arm_func_start FUN_037FF814
FUN_037FF814: ; 0x037FF814
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r5, r2
	bl	OS_DisableInterrupts
	mov	r4, r0
	mov	r2, #0
	b	_037FF858
_037FF838:
	ands	r0, r7, #1
	movne	r0, r2, lsl #4
	addne	r0, r0, #67108864	; 0x4000000
	ldrneb	r1, [r0, #1027]	; 0x403
	orrne	r1, r1, #128	; 0x80
	strneb	r1, [r0, #1027]	; 0x403
	add	r2, r2, #1
	mov	r7, r7, lsr #1
_037FF858:
	cmp	r2, #16
	bge	_037FF868
	cmp	r7, #0
	bne	_037FF838
_037FF868:
	ands	r0, r6, #1
	beq	_037FF8A0
	ands	r0, r6, #2
	ldreq	r1, _037FF8FC	; =0x04000508
	ldreqb	r0, [r1]
	orreq	r0, r0, #128	; 0x80
	streqb	r0, [r1]
	beq	_037FF8B4
	ldr	r2, _037FF8FC	; =0x04000508
	ldrh	r1, [r2]
	ldr	r0, _037FF900	; =0x00008080
	orr	r0, r1, r0
	strh	r0, [r2]
	b	_037FF8B4
_037FF8A0:
	ands	r0, r6, #2
	ldrne	r1, _037FF904	; =0x04000509
	ldrneb	r0, [r1]
	orrne	r0, r0, #128	; 0x80
	strneb	r0, [r1]
_037FF8B4:
	mov	r6, #0
	b	_037FF8D4
_037FF8BC:
	ands	r0, r5, #1
	beq	_037FF8CC
	mov	r0, r6
	bl	SND_StartAlarm
_037FF8CC:
	add	r6, r6, #1
	mov	r5, r5, lsr #1
_037FF8D4:
	cmp	r6, #8
	bge	_037FF8E4
	cmp	r5, #0
	bne	_037FF8BC
_037FF8E4:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	bl	SND_UpdateSharedWork
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FF8FC:	.word	0x04000508
_037FF900:	.word	0x00008080
_037FF904:	.word	0x04000509

	arm_func_start FUN_037FF908
FUN_037FF908: ; 0x037FF908
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, r1
	mov	r4, #0
	b	_037FF938
_037FF91C:
	ands	r0, r6, #1
	beq	_037FF930
	mov	r0, r4
	mov	r1, r5
	bl	SND_SetChannelPan
_037FF930:
	add	r4, r4, #1
	mov	r6, r6, lsr #1
_037FF938:
	cmp	r4, #16
	bge	_037FF948
	cmp	r6, #0
	bne	_037FF91C
_037FF948:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start FUN_037FF950
FUN_037FF950: ; 0x037FF950
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r5, r2
	mov	r4, #0
	b	_037FF98C
_037FF96C:
	ands	r0, r7, #1
	beq	_037FF984
	mov	r0, r4
	mov	r1, r6
	mov	r2, r5
	bl	SND_SetChannelVolume
_037FF984:
	add	r4, r4, #1
	mov	r7, r7, lsr #1
_037FF98C:
	cmp	r4, #16
	bge	_037FF99C
	cmp	r7, #0
	bne	_037FF96C
_037FF99C:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr

	arm_func_start FUN_037FF9A8
FUN_037FF9A8: ; 0x037FF9A8
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, r1
	mov	r4, #0
	b	_037FF9D8
_037FF9BC:
	ands	r0, r6, #1
	beq	_037FF9D0
	mov	r0, r4
	mov	r1, r5
	bl	SND_SetChannelTimer
_037FF9D0:
	add	r4, r4, #1
	mov	r6, r6, lsr #1
_037FF9D8:
	cmp	r4, #16
	bge	_037FF9E8
	cmp	r6, #0
	bne	_037FF9BC
_037FF9E8:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start FUN_037FF9F0
FUN_037FF9F0: ; 0x037FF9F0
	mov	r0, #7
	ldr	r1, _037FFA00	; =FUN_037FFA08
	ldr	ip, _037FFA04	; =PXI_SetFifoRecvCallback
	bx	ip
_037FFA00:	.word	FUN_037FFA08
_037FFA04:	.word	PXI_SetFifoRecvCallback

	arm_func_start FUN_037FFA08
FUN_037FFA08: ; 0x037FFA08
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r1
	bl	OS_DisableInterrupts
	mov	r4, r0
	cmp	r5, #33554432	; 0x2000000
	bcc	_037FFA38
	ldr	r0, _037FFA58	; =_038090EC
	mov	r1, r5
	mov	r2, #0
	bl	OS_SendMessage
	b	_037FFA44
_037FFA38:
	cmp	r5, #0
	bne	_037FFA44
	bl	SND_SendWakeupMessage
_037FFA44:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FFA58:	.word	_038090EC

	arm_func_start SND_CommandProc
SND_CommandProc: ; 0x037FFA5C
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #52	; 0x34
	ldr	r7, _037FFEC4	; =SNDi_SharedWork
	ldr	r9, _037FFEC8	; =_038090EC
	add	r8, sp, #24
	mov	r4, #0
	ldr	r6, _037FFECC	; =0x0000FFFF
	ldr	r5, _037FFED0	; =0x003FFFFF
	b	_037FFEA0
_037FFA80:
	ldr	lr, [sp, #24]
	b	_037FFE88
_037FFA88:
	add	ip, sp, #28
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1}
	stmia	ip, {r0, r1}
	ldr	r0, [sp, #32]
	cmp	r0, #33	; 0x21
	addls	pc, pc, r0, lsl #2
	b	_037FFE84
	b	_037FFB34
	b	_037FFB4C
	b	_037FFB58
	b	_037FFB70
	b	_037FFB7C
	b	_037FFB8C
	b	_037FFB9C
	b	_037FFBB4
	b	_037FFBDC
	b	_037FFBF0
	b	_037FFC04
	b	_037FFC20
	b	_037FFC38
	b	_037FFC50
	b	_037FFD08
	b	_037FFD74
	b	_037FFDA8
	b	_037FFC68
	b	_037FFCB0
	b	_037FFCD4
	b	_037FFCE4
	b	_037FFCF8
	b	_037FFDD4
	b	_037FFDE0
	b	_037FFDEC
	b	_037FFDF8
	b	_037FFE10
	b	_037FFE20
	b	_037FFE30
	b	_037FFE70
	b	_037FFE40
	b	_037FFE50
	b	_037FFE60
	b	_037FFE7C
_037FFB34:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	ldr	r3, [sp, #48]	; 0x30
	bl	SND_StartSeq
	b	_037FFE84
_037FFB4C:
	ldr	r0, [sp, #36]	; 0x24
	bl	SND_StopSeq
	b	_037FFE84
_037FFB58:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	ldr	r3, [sp, #48]	; 0x30
	bl	SND_PrepareSeq
	b	_037FFE84
_037FFB70:
	ldr	r0, [sp, #36]	; 0x24
	bl	SND_StartPreparedSeq
	b	_037FFE84
_037FFB7C:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SND_PauseSeq
	b	_037FFE84
_037FFB8C:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SND_SkipSeq
	b	_037FFE84
_037FFB9C:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	ldr	r3, [sp, #48]	; 0x30
	bl	SNDi_SetPlayerParam
	b	_037FFE84
_037FFBB4:
	ldr	r1, [sp, #36]	; 0x24
	mov	r0, r1, lsr #24
	and	r0, r0, #255	; 0xff
	str	r0, [sp]
	bic	r0, r1, #-16777216	; 0xff000000
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	ldr	r3, [sp, #48]	; 0x30
	bl	SNDi_SetTrackParam
	b	_037FFE84
_037FFBDC:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	bl	SND_SetTrackMute
	b	_037FFE84
_037FFBF0:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	bl	SND_SetTrackAllocatableChannel
	b	_037FFE84
_037FFC04:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	mov	r2, r2, lsl #16
	mov	r2, r2, asr #16
	bl	SND_SetPlayerLocalVariable
	b	_037FFE84
_037FFC20:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	mov	r1, r1, lsl #16
	mov	r1, r1, asr #16
	bl	SND_SetPlayerGlobalVariable
	b	_037FFE84
_037FFC38:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	ldr	r3, [sp, #48]	; 0x30
	bl	FUN_037FF814
	b	_037FFE84
_037FFC50:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	ldr	r3, [sp, #48]	; 0x30
	bl	FUN_037FF750
	b	_037FFE84
_037FFC68:
	ldr	r1, [sp, #44]	; 0x2c
	mov	r0, r1, lsr #29
	and	r0, r0, #1
	str	r0, [sp]
	mov	r0, r1, lsr #28
	and	r0, r0, #1
	str	r0, [sp, #4]
	mov	r0, r1, lsr #27
	and	r0, r0, #1
	str	r0, [sp, #8]
	mov	r0, r1, lsr #31
	and	r0, r0, #1
	mov	r1, r1, lsr #30
	and	r1, r1, #1
	ldr	r2, [sp, #36]	; 0x24
	ldr	r3, [sp, #40]	; 0x28
	bl	SND_SetupCapture
	b	_037FFE84
_037FFCB0:
	ldr	r0, [sp, #48]	; 0x30
	str	r0, [sp, #4]
	ldr	r3, [sp, #44]	; 0x2c
	str	r4, [sp]
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	mov	r2, #0
	bl	SND_SetupAlarm
	b	_037FFE84
_037FFCD4:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	FUN_037FF9A8
	b	_037FFE84
_037FFCE4:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	bl	FUN_037FF950
	b	_037FFE84
_037FFCF8:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	FUN_037FF908
	b	_037FFE84
_037FFD08:
	ldr	r3, [sp, #48]	; 0x30
	ldr	r1, [sp, #36]	; 0x24
	ldr	r0, [sp, #44]	; 0x2c
	and	r2, r3, r6
	str	r2, [sp]
	and	r2, r0, r5
	str	r2, [sp, #4]
	mov	r2, r0, lsr #24
	and	r2, r2, #127	; 0x7f
	str	r2, [sp, #8]
	mov	r0, r0, lsr #22
	and	r0, r0, #3
	str	r0, [sp, #12]
	and	r0, r6, r1, lsr #16
	str	r0, [sp, #16]
	mov	r0, r3, lsr #16
	and	r0, r0, #127	; 0x7f
	str	r0, [sp, #20]
	and	r0, r1, r6
	ldr	r1, [sp, #40]	; 0x28
	bic	r1, r1, #-134217728	; 0xf8000000
	mov	r2, r3, lsr #24
	and	r2, r2, #3
	mov	r3, r3, lsr #26
	and	r3, r3, #3
	bl	SND_SetupChannelPcm
	b	_037FFE84
_037FFD74:
	ldr	r1, [sp, #44]	; 0x2c
	ldr	r3, [sp, #40]	; 0x28
	and	r0, r6, r1, lsr #8
	str	r0, [sp]
	and	r0, r1, #127	; 0x7f
	str	r0, [sp, #4]
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #48]	; 0x30
	and	r2, r3, #127	; 0x7f
	mov	r3, r3, lsr #8
	and	r3, r3, #3
	bl	SND_SetupChannelPsg
	b	_037FFE84
_037FFDA8:
	ldr	r3, [sp, #44]	; 0x2c
	ldr	r2, [sp, #40]	; 0x28
	and	r0, r3, #127	; 0x7f
	str	r0, [sp]
	ldr	r0, [sp, #36]	; 0x24
	and	r1, r2, #127	; 0x7f
	mov	r2, r2, lsr #8
	and	r2, r2, #3
	and	r3, r6, r3, lsr #8
	bl	SND_SetupChannelNoise
	b	_037FFE84
_037FFDD4:
	ldr	r0, [sp, #36]	; 0x24
	bl	SNDi_SetSurroundDecay
	b	_037FFE84
_037FFDE0:
	ldr	r0, [sp, #36]	; 0x24
	bl	SND_SetMasterVolume
	b	_037FFE84
_037FFDEC:
	ldr	r0, [sp, #36]	; 0x24
	bl	SND_SetMasterPan
	b	_037FFE84
_037FFDF8:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	ldr	r3, [sp, #48]	; 0x30
	bl	SND_SetOutputSelector
	b	_037FFE84
_037FFE10:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SND_LockChannel
	b	_037FFE84
_037FFE20:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SND_UnlockChannel
	b	_037FFE84
_037FFE30:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SND_StopUnlockedChannel
	b	_037FFE84
_037FFE40:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SND_InvalidateSeq
	b	_037FFE84
_037FFE50:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SND_InvalidateBank
	b	_037FFE84
_037FFE60:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SND_InvalidateWave
	b	_037FFE84
_037FFE70:
	ldr	r0, [sp, #36]	; 0x24
	str	r0, [r7]
	b	_037FFE84
_037FFE7C:
	ldr	r0, [sp, #36]	; 0x24
	bl	FUN_037FF6E4
_037FFE84:
	ldr	lr, [sp, #28]
_037FFE88:
	cmp	lr, #0
	bne	_037FFA88
	ldr	r1, [r7]
	ldr	r0, [r1]
	add	r0, r0, #1
	str	r0, [r1]
_037FFEA0:
	mov	r0, r9
	mov	r1, r8
	mov	r2, r4
	bl	OS_ReceiveMessage
	cmp	r0, #0
	bne	_037FFA80
	add	sp, sp, #52	; 0x34
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037FFEC4:	.word	SNDi_SharedWork
_037FFEC8:	.word	_038090EC
_037FFECC:	.word	0x0000FFFF
_037FFED0:	.word	0x003FFFFF

	arm_func_start SND_CommandInit
SND_CommandInit: ; 0x037FFED4
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037FFF08	; =_038090EC
	ldr	r1, _037FFF0C	; =_0380910C
	mov	r2, #8
	bl	OS_InitMessageQueue
	bl	FUN_037FF9F0
	mov	r1, #0
	ldr	r0, _037FFF10	; =SNDi_SharedWork
	str	r1, [r0]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FFF08:	.word	_038090EC
_037FFF0C:	.word	_0380910C
_037FFF10:	.word	SNDi_SharedWork

	arm_func_start FS_Init
FS_Init: ; 0x037FFF14
	ldr	ip, _037FFF1C	; =CARD_Init
	bx	ip
_037FFF1C:	.word	CARD_Init

	arm_func_start CARD_GetRomHeader
CARD_GetRomHeader: ; 0x037FFF20
	ldr	r0, _037FFF28	; =0x027FFA80
	bx	lr
_037FFF28:	.word	0x027FFA80

	arm_func_start CARD_SetThreadPriority
CARD_SetThreadPriority: ; 0x037FFF2C
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	ldr	r6, _037FFF70	; =cardi_common
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r5, [r6, #240]	; 0xf0
	str	r7, [r6, #240]	; 0xf0
	add	r0, r6, #72	; 0x48
	ldr	r1, [r6, #240]	; 0xf0
	bl	OS_SetThreadPriority
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, r5
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FFF70:	.word	cardi_common

	arm_func_start CARD_Enable
CARD_Enable: ; 0x037FFF74
	ldr	r1, _037FFF80	; =_0380912C
	str	r0, [r1]
	bx	lr
_037FFF80:	.word	_0380912C

	arm_func_start CARDi_InitCommon
CARDi_InitCommon: ; 0x037FFF84
	stmfd	sp!, {lr}
	sub	sp, sp, #12
	mvn	r1, #2
	ldr	r0, _0380001C	; =cardi_common
	str	r1, [r0, #12]
	mov	r2, #0
	str	r2, [r0, #16]
	str	r2, [r0, #28]
	str	r2, [r0]
	str	r2, [r0, #8]
	str	r2, [r0, #24]
	str	r2, [r0, #20]
	str	r2, [r0, #248]	; 0xf8
	str	r2, [r0, #244]	; 0xf4
	mov	r1, #4
	str	r1, [r0, #240]	; 0xf0
	mov	r1, #1024	; 0x400
	str	r1, [sp]
	ldr	r0, [r0, #240]	; 0xf0
	str	r0, [sp, #4]
	ldr	r0, _03800020	; =_03809188
	ldr	r1, _03800024	; =CARDi_TaskThread
	ldr	r3, _03800028	; =_03809760
	bl	OS_CreateThread
	ldr	r0, _03800020	; =_03809188
	bl	OS_WakeupThreadDirect
	mov	r0, #11
	ldr	r1, _0380002C	; =CARDi_OnFifoRecv
	bl	PXI_SetFifoRecvCallback
	ldr	r0, _03800030	; =0x027FFC40
	ldrh	r0, [r0]
_03800000:
	cmp	r0, #2
	beq	_03800010
	mov	r0, #1
	bl	CARD_Enable
_03800010:
	add	sp, sp, #12
	ldmia	sp!, {lr}
	bx	lr
_0380001C:	.word	cardi_common
_03800020:	.word	_03809188
_03800024:	.word	CARDi_TaskThread
_03800028:	.word	_03809760
_0380002C:	.word	CARDi_OnFifoRecv
_03800030:	.word	0x027FFC40

	arm_func_start CARDi_SetWriteProtectCore
CARDi_SetWriteProtectCore: ; 0x03800034
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	sub	sp, sp, #8
	mov	r4, r0
	bl	FUN_03800780
	cmp	r0, #0
	beq	_038000BC
	ldr	r0, _038000C8	; =cardi_common
	ldr	sl, [r0]
	mov	r9, #10
	mov	r0, #1
	strb	r0, [sp]
	strb	r4, [sp, #1]
	mov	r8, #2
	add	r7, sp, #0
	mov	r6, #0
	ldr	r5, _038000CC	; =_03800660
	mov	r4, #5
_03800078:
	bl	FUN_038005B4
	mov	r0, r8
	bl	FUN_038008B4
	mov	r0, r7
	mov	r1, r6
	mov	r2, r8
	mov	r3, r5
	bl	FUN_038006F0
	mov	r0, r4
	mov	r1, r6
	bl	FUN_03800830
	ldr	r0, [sl]
	cmp	r0, #4
	bne	_038000BC
	sub	r9, r9, #1
	cmp	r9, #0
	bgt	_03800078
_038000BC:
	add	sp, sp, #8
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	bx	lr
_038000C8:	.word	cardi_common
_038000CC:	.word	_03800660

	arm_func_start CARDi_EraseChipCore
CARDi_EraseChipCore: ; 0x038000D0
	stmdb	sp!, {r4, lr}
	bl	FUN_03800780
	cmp	r0, #0
	beq	_03800114
	ldr	r0, _0380011C	; =cardi_common
	ldr	r4, [r0]
	bl	FUN_038005B4
	mov	r0, #1
	bl	FUN_038008B4
	ldr	r0, _03800120	; =_038072BC
	mov	r1, #0
	mov	r2, #1
	ldr	r3, _03800124	; =_03800660
	bl	FUN_038006F0
	ldr	r0, [r4, #52]	; 0x34
	ldr	r1, [r4, #56]	; 0x38
	bl	FUN_03800830
_03800114:
	ldmia	sp!, {r4, lr}
	bx	lr
_0380011C:	.word	cardi_common
_03800120:	.word	_038072BC
_03800124:	.word	_03800660

	arm_func_start CARDi_EraseBackupSectorCore
CARDi_EraseBackupSectorCore: ; 0x03800128
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r7, r0
	mov	r6, r1
	ldr	r0, _038001B8	; =cardi_common
	ldr	r5, [r0]
	ldr	r4, [r5, #28]
	sub	r1, r4, #1
	orr	r0, r7, r6
	ands	r0, r1, r0
	movne	r0, #2
	strne	r0, [r5]
	bne	_038001B0
	bl	FUN_03800780
	cmp	r0, #0
	beq	_038001B0
	mov	r8, #216	; 0xd8
	b	_038001A8
_0380016C:
	bl	FUN_038005B4
	ldr	r0, [r5, #36]	; 0x24
	add	r0, r0, #1
	bl	FUN_038008B4
	mov	r0, r7
	mov	r1, r8
	bl	FUN_03800508
	ldr	r0, [r5, #60]	; 0x3c
	ldr	r1, [r5, #64]	; 0x40
	bl	FUN_03800830
	ldr	r0, [r5]
	cmp	r0, #0
	bne	_038001B0
	add	r7, r7, r4
	sub	r6, r6, r4
_038001A8:
	cmp	r6, #0
	bne	_0380016C
_038001B0:
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_038001B8:	.word	cardi_common

	arm_func_start CARDi_VerifyBackupCore
CARDi_VerifyBackupCore: ; 0x038001BC
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r5, r2
	bl	FUN_03800780
	cmp	r0, #0
	beq	_0380024C
	ldr	r0, _03800258	; =cardi_common
	ldr	r4, [r0]
	mov	r1, #1
	ldr	r0, _0380025C	; =_03809764
	str	r1, [r0, #12]
	ldr	r0, [r4, #36]	; 0x24
	add	r0, r0, #1
	add	r0, r0, r5
	bl	FUN_038008B4
	mov	r0, r7
	mov	r1, #3
	bl	FUN_03800508
	mov	r0, r6
	mov	r1, #0
	mov	r2, r5
	ldr	r3, _03800260	; =_038005F8
	bl	FUN_038006F0
	mov	r0, #0
	mov	r1, r0
	bl	FUN_03800830
	ldr	r0, [r4]
	cmp	r0, #0
	bne	_0380024C
	ldr	r0, _0380025C	; =_03809764
	ldr	r0, [r0, #12]
	cmp	r0, #0
	moveq	r0, #1
	streq	r0, [r4]
_0380024C:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_03800258:	.word	cardi_common
_0380025C:	.word	_03809764
_03800260:	.word	_038005F8

	arm_func_start CARDi_WriteBackupCore
CARDi_WriteBackupCore: ; 0x03800264
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	r9, r1
	mov	r8, r2
	bl	FUN_03800780
	cmp	r0, #0
	beq	_03800314
	ldr	r0, _03800320	; =cardi_common
	ldr	r7, [r0]
	ldr	r6, [r7, #32]
	sub	r4, r6, #1
	mov	fp, #10
	mov	r0, #0
	str	r0, [sp]
	b	_0380030C
_038002A4:
	and	r0, sl, r4
	sub	r5, r6, r0
	cmp	r5, r8
	movhi	r5, r8
	bl	FUN_038005B4
	ldr	r0, [r7, #36]	; 0x24
	add	r0, r0, #1
	add	r0, r0, r5
	bl	FUN_038008B4
	mov	r0, sl
	mov	r1, fp
	bl	FUN_03800508
	mov	r0, r9
	ldr	r1, [sp]
	mov	r2, r5
	ldr	r3, _03800324	; =_03800660
	bl	FUN_038006F0
	ldr	r0, [r7, #44]	; 0x2c
	ldr	r1, [r7, #48]	; 0x30
	bl	FUN_03800830
	ldr	r0, [r7]
	cmp	r0, #0
	bne	_03800314
	add	r9, r9, r5
	add	sl, sl, r5
	sub	r8, r8, r5
_0380030C:
	cmp	r8, #0
	bne	_038002A4
_03800314:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_03800320:	.word	cardi_common
_03800324:	.word	_03800660

	arm_func_start CARDi_ProgramBackupCore
CARDi_ProgramBackupCore: ; 0x03800328
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	r9, r1
	mov	r8, r2
	bl	FUN_03800780
	cmp	r0, #0
	beq	_038003D8
	ldr	r0, _038003E4	; =cardi_common
	ldr	r7, [r0]
	ldr	r6, [r7, #32]
	sub	r4, r6, #1
	mov	r0, #2
	str	r0, [sp]
	mov	fp, #0
	b	_038003D0
_03800368:
	and	r0, sl, r4
	sub	r5, r6, r0
	cmp	r5, r8
	movhi	r5, r8
	bl	FUN_038005B4
	ldr	r0, [r7, #36]	; 0x24
	add	r0, r0, #1
	add	r0, r0, r5
	bl	FUN_038008B4
	mov	r0, sl
	ldr	r1, [sp]
	bl	FUN_03800508
	mov	r0, r9
	mov	r1, fp
	mov	r2, r5
	ldr	r3, _038003E8	; =_03800660
	bl	FUN_038006F0
	ldr	r0, [r7, #40]	; 0x28
	mov	r1, fp
	bl	FUN_03800830
	ldr	r0, [r7]
	cmp	r0, #0
	bne	_038003D8
	add	r9, r9, r5
	add	sl, sl, r5
	sub	r8, r8, r5
_038003D0:
	cmp	r8, #0
	bne	_03800368
_038003D8:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_038003E4:	.word	cardi_common
_038003E8:	.word	_03800660

	arm_func_start CARDi_ReadBackupCore
CARDi_ReadBackupCore: ; 0x038003EC
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, r1
	mov	r4, r2
	bl	FUN_03800780
	cmp	r0, #0
	beq	_0380044C
	ldr	r0, _03800454	; =cardi_common
	ldr	r0, [r0]
	ldr	r0, [r0, #36]	; 0x24
	add	r0, r0, #1
	add	r0, r0, r4
	bl	FUN_038008B4
	mov	r0, r6
	mov	r1, #3
	bl	FUN_03800508
	mov	r0, #0
	mov	r1, r5
	mov	r2, r4
	ldr	r3, _03800458	; =_038006AC
	bl	FUN_038006F0
	mov	r0, #0
	mov	r1, r0
	bl	FUN_03800830
_0380044C:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr
_03800454:	.word	cardi_common
_03800458:	.word	_038006AC

	arm_func_start CARDi_InitStatusRegister
CARDi_InitStatusRegister: ; 0x0380045C
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	ldr	r0, _038004F8	; =cardi_common
	ldr	r0, [r0]
	ldrb	r4, [r0, #72]	; 0x48
	cmp	r4, #255	; 0xff
	beq	_038004EC
	ldr	r0, _038004FC	; =_03809760
	ldr	r0, [r0]
	cmp	r0, #0
	bne	_038004EC
	mov	r0, #5
	strb	r0, [sp]
	mov	r0, #2
	bl	FUN_038008B4
	add	r0, sp, #0
	mov	r1, #0
	mov	r2, #1
	ldr	r3, _03800500	; =_03800660
	bl	FUN_038006F0
	mov	r0, #0
	add	r1, sp, #1
	mov	r2, #1
	ldr	r3, _03800504	; =_038006AC
	bl	FUN_038006F0
	mov	r0, #0
	mov	r1, r0
	bl	FUN_03800830
	ldrb	r0, [sp, #1]
	cmp	r0, r4
	beq	_038004E0
	mov	r0, r4
	bl	CARDi_SetWriteProtectCore
_038004E0:
	mov	r1, #1
	ldr	r0, _038004FC	; =_03809760
	str	r1, [r0]
_038004EC:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_038004F8:	.word	cardi_common
_038004FC:	.word	_03809760
_03800500:	.word	_03800660
_03800504:	.word	_038006AC

	arm_func_start FUN_03800508
FUN_03800508: ; 0x03800508
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r2, _038005AC	; =cardi_common
	ldr	r2, [r2]
	ldr	r2, [r2, #36]	; 0x24
	cmp	r2, #1
	beq	_03800538
	cmp	r2, #2
	beq	_03800554
	cmp	r2, #3
	beq	_0380056C
	b	_0380058C
_03800538:
	and	r3, r0, #255	; 0xff
	mov	r0, r0, lsr #5
	and	r0, r0, #8
	orr	r0, r1, r0
	orr	r0, r0, r3, lsl #8
	str	r0, [sp]
	b	_0380058C
_03800554:
	and	r3, r0, #255	; 0xff
	and	r0, r0, #65280	; 0xff00
	orr	r0, r1, r0
	orr	r0, r0, r3, lsl #16
	str	r0, [sp]
	b	_0380058C
_0380056C:
	and	ip, r0, #255	; 0xff
	and	r3, r0, #65280	; 0xff00
	mov	r0, r0, lsr #8
	and	r0, r0, #65280	; 0xff00
	orr	r0, r1, r0
	orr	r0, r0, r3, lsl #8
	orr	r0, r0, ip, lsl #24
	str	r0, [sp]
_0380058C:
	add	r0, sp, #0
	mov	r1, #0
	add	r2, r2, #1
	ldr	r3, _038005B0	; =_03800660
	bl	FUN_038006F0
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_038005AC:	.word	cardi_common
_038005B0:	.word	_03800660

	arm_func_start FUN_038005B4
FUN_038005B4: ; 0x038005B4
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #1
	bl	FUN_038008B4
	ldr	r0, _038005F0	; =_038072C0
	mov	r1, #0
	mov	r2, #1
	ldr	r3, _038005F4	; =_03800660
	bl	FUN_038006F0
	mov	r0, #0
	mov	r1, r0
	bl	FUN_03800830
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_038005F0:	.word	_038072C0
_038005F4:	.word	_03800660
_038005F8:
	mov	r2, #0
	ldr	r1, _03800658	; =0x040001A2
	strh	r2, [r1]
	ldr	r2, _0380065C	; =0x040001A0
_03800608:
	ldrh	r1, [r2]
	ands	r1, r1, #128	; 0x80
	bne	_03800608
	ldr	r1, _03800658	; =0x040001A2
	ldrh	r1, [r1]
	and	r2, r1, #255	; 0xff
	ldr	r1, [r0, #4]
	ldrb	r1, [r1]
	cmp	r2, r1
	beq	_03800648
	mov	r1, #0
	str	r1, [r0, #12]
	ldr	r1, [r0]
	cmp	r1, #1
	movhi	r1, #1
	strhi	r1, [r0]
_03800648:
	ldr	r1, [r0, #4]
	add	r1, r1, #1
	str	r1, [r0, #4]
	bx	lr
_03800658:	.word	0x040001A2
_0380065C:	.word	0x040001A0
_03800660:
	sub	sp, sp, #8
	ldr	r1, [r0, #4]
	ldrb	r2, [r1]
	ldr	r1, _038006A4	; =0x040001A2
	strh	r2, [r1]
	ldr	r1, [r0, #4]
	add	r1, r1, #1
	str	r1, [r0, #4]
	ldr	r1, _038006A8	; =0x040001A0
_03800684:
	ldrh	r0, [r1]
	ands	r0, r0, #128	; 0x80
	bne	_03800684
	ldr	r0, _038006A4	; =0x040001A2
	ldrh	r0, [r0]
	strh	r0, [sp]
	add	sp, sp, #8
	bx	lr
_038006A4:	.word	0x040001A2
_038006A8:	.word	0x040001A0
_038006AC:
	mov	r2, #0
	ldr	r1, _038006E8	; =0x040001A2
	strh	r2, [r1]
	ldr	r2, _038006EC	; =0x040001A0
_038006BC:
	ldrh	r1, [r2]
	ands	r1, r1, #128	; 0x80
	bne	_038006BC
	ldr	r1, _038006E8	; =0x040001A2
	ldrh	r2, [r1]
	ldr	r1, [r0, #8]
	strb	r2, [r1]
	ldr	r1, [r0, #8]
	add	r1, r1, #1
	str	r1, [r0, #8]
	bx	lr
_038006E8:	.word	0x040001A2
_038006EC:	.word	0x040001A0

	arm_func_start FUN_038006F0
FUN_038006F0: ; 0x038006F0
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r7, r2
	mov	r6, r3
	ldr	r5, _03800774	; =_03809764
	str	r0, [r5, #4]
	str	r1, [r5, #8]
	ldr	r0, _03800778	; =0x0000A040
	ldr	r4, _0380077C	; =0x040001A0
	strh	r0, [r4]
	mov	r8, #40960	; 0xa000
	b	_03800750
_0380071C:
	ldr	r0, [r5]
	sub	r0, r0, #1
	str	r0, [r5]
	ldr	r0, [r5]
	cmp	r0, #0
	streqh	r8, [r4]
_03800734:
	ldrh	r0, [r4]
	ands	r0, r0, #128	; 0x80
	bne	_03800734
	mov	r0, r5
	mov	lr, pc
	bx	r6
	sub	r7, r7, #1
_03800750:
	cmp	r7, #0
	bne	_0380071C
	ldr	r0, [r5]
	cmp	r0, #0
	moveq	r1, #0
	ldreq	r0, _0380077C	; =0x040001A0
	streqh	r1, [r0]
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_03800774:	.word	_03809764
_03800778:	.word	0x0000A040
_0380077C:	.word	0x040001A0

	arm_func_start FUN_03800780
FUN_03800780: ; 0x03800780
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #0
	mov	r1, #50	; 0x32
	bl	FUN_03800830
	ldr	r0, _038007C0	; =cardi_common
	ldr	r1, [r0]
	ldr	r0, [r1]
	cmp	r0, #4
	moveq	r0, #6
	streq	r0, [r1]
	moveq	r0, #0
	movne	r0, #1
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_038007C0:	.word	cardi_common

	arm_func_start FUN_038007C4
FUN_038007C4: ; 0x038007C4
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #2
	bl	FUN_038008B4
	ldr	r0, _03800824	; =_038072C4
	mov	r1, #0
	mov	r2, #1
	ldr	r3, _03800828	; =_03800660
	bl	FUN_038006F0
	mov	r0, #0
	add	r1, sp, #0
	mov	r2, #1
	ldr	r3, _0380082C	; =_038006AC
	bl	FUN_038006F0
	mov	r0, #0
	mov	r1, r0
	bl	FUN_03800830
	ldrb	r0, [sp]
	ands	r0, r0, #1
	moveq	r0, #1
	movne	r0, #0
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03800824:	.word	_038072C4
_03800828:	.word	_03800660
_0380082C:	.word	_038006AC

	arm_func_start FUN_03800830
FUN_03800830: ; 0x03800830
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r5, r0
	mov	r4, r1
	adds	r1, r5, r4
	beq	_038008A8
	cmp	r5, #0
	beq	_03800850
	bl	OS_Sleep
_03800850:
	cmp	r4, #0
	beq	_03800890
	sub	r6, r4, r5
	mov	r4, #5
	b	_0380087C
_03800864:
	cmp	r6, #5
	movlt	r5, r6
	movge	r5, r4
	mov	r0, r5
	bl	OS_Sleep
	sub	r6, r6, r5
_0380087C:
	bl	FUN_038007C4
	cmp	r0, #0
	bne	_03800890
	cmp	r6, #0
	bgt	_03800864
_03800890:
	bl	FUN_038007C4
	cmp	r0, #0
	moveq	r1, #4
	ldreq	r0, _038008B0	; =cardi_common
	ldreq	r0, [r0]
	streq	r1, [r0]
_038008A8:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr
_038008B0:	.word	cardi_common

	arm_func_start FUN_038008B4
FUN_038008B4: ; 0x038008B4
	ldr	r1, _038008C0	; =_03809764
	str	r0, [r1]
	bx	lr
_038008C0:	.word	_03809764

	arm_func_start CARDi_GetRomAccessor
CARDi_GetRomAccessor: ; 0x038008C4
	ldr	r0, _038008CC	; =_03800A7C
	bx	lr
_038008CC:	.word	_03800A7C

	arm_func_start CARD_Init
CARD_Init: ; 0x038008D0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r2, _03800940	; =cardi_common
	ldr	r0, [r2, #252]	; 0xfc
	cmp	r0, #0
	bne	_03800934
	mov	r0, #1
	str	r0, [r2, #252]	; 0xfc
	mov	r1, #0
	str	r1, [r2, #40]	; 0x28
	ldr	r0, [r2, #40]	; 0x28
	str	r0, [r2, #36]	; 0x24
	ldr	r0, [r2, #36]	; 0x24
	str	r0, [r2, #32]
	mvn	r0, #0
	str	r0, [r2, #44]	; 0x2c
	str	r1, [r2, #60]	; 0x3c
	str	r1, [r2, #64]	; 0x40
	ldr	r0, _03800944	; =cardi_rom_base
	str	r1, [r0]
	bl	CARDi_InitCommon
	bl	CARDi_GetRomAccessor
	ldr	r1, _03800948	; =rom_stat
	str	r0, [r1]
	bl	CARD_InitPulledOutCallback
_03800934:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03800940:	.word	cardi_common
_03800944:	.word	cardi_rom_base
_03800948:	.word	rom_stat

	arm_func_start CARDi_ReadRomID
CARDi_ReadRomID: ; 0x0380094C
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	ldr	r5, _03800A10	; =cardi_common
	bl	OS_DisableInterrupts
	mov	r4, r0
	add	r6, r5, #244	; 0xf4
	b	_0380096C
_03800964:
	mov	r0, r6
	bl	OS_SleepThread
_0380096C:
	ldr	r0, [r5, #252]	; 0xfc
	ands	r0, r0, #4
	bne	_03800964
	ldr	r0, [r5, #252]	; 0xfc
	orr	r0, r0, #4
	str	r0, [r5, #252]	; 0xfc
	mov	r0, #0
	str	r0, [r5, #60]	; 0x3c
	str	r0, [r5, #64]	; 0x40
	mov	r0, r4
	bl	OS_RestoreInterrupts
	bl	CARDi_ReadRomIDCore
	mov	r8, r0
	ldr	r7, _03800A10	; =cardi_common
	mov	r1, #0
	ldr	r0, [r7]
	str	r1, [r0]
	ldr	r6, [r7, #60]	; 0x3c
	ldr	r5, [r7, #64]	; 0x40
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r0, [r7, #252]	; 0xfc
	bic	r0, r0, #76	; 0x4c
	str	r0, [r7, #252]	; 0xfc
	add	r0, r7, #244	; 0xf4
	bl	OS_WakeupThread
	ldr	r0, [r7, #252]	; 0xfc
	ands	r0, r0, #16
	beq	_038009E8
	add	r0, r7, #72	; 0x48
	bl	OS_WakeupThreadDirect
_038009E8:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	cmp	r6, #0
	beq	_03800A04
	mov	r0, r5
	mov	lr, pc
	bx	r6
_03800A04:
	mov	r0, r8
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_03800A10:	.word	cardi_common

	arm_func_start CARDi_ReadRomIDCore
CARDi_ReadRomIDCore: ; 0x03800A14
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #-1207959552	; 0xb8000000
	mov	r1, #0
	bl	FUN_03800A80
	ldr	r0, _03800A70	; =cardi_rom_header_addr
	ldr	r0, [r0]
	ldr	r0, [r0, #96]	; 0x60
	bic	r0, r0, #117440512	; 0x7000000
	orr	r1, r0, #-1493172224	; 0xa7000000
	mov	r0, #8192	; 0x2000
	rsb	r0, r0, #0
	and	r0, r1, r0
	ldr	r1, _03800A74	; =0x040001A4
	str	r0, [r1]
_03800A50:
	ldr	r0, [r1]
	ands	r0, r0, #8388608	; 0x800000
	beq	_03800A50
	ldr	r0, _03800A78	; =0x04100010
	ldr	r0, [r0]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03800A70:	.word	cardi_rom_header_addr
_03800A74:	.word	0x040001A4
_03800A78:	.word	0x04100010
_03800A7C:
	bx	lr

	arm_func_start FUN_03800A80
FUN_03800A80: ; 0x03800A80
	ldr	r3, _03800AF8	; =0x040001A4
_03800A84:
	ldr	r2, [r3]
	ands	r2, r2, #-2147483648	; 0x80000000
	bne	_03800A84
	mov	r3, #192	; 0xc0
	ldr	r2, _03800AFC	; =0x040001A1
	strb	r3, [r2]
	mov	r3, r0, lsr #24
	ldr	r2, _03800B00	; =0x040001A8
	strb	r3, [r2]
	mov	r3, r0, lsr #16
	ldr	r2, _03800B04	; =0x040001A9
	strb	r3, [r2]
	mov	r3, r0, lsr #8
	ldr	r2, _03800B08	; =0x040001AA
	strb	r3, [r2]
	ldr	r2, _03800B0C	; =0x040001AB
	strb	r0, [r2]
	mov	r2, r1, lsr #24
	ldr	r0, _03800B10	; =0x040001AC
	strb	r2, [r0]
	mov	r2, r1, lsr #16
	ldr	r0, _03800B14	; =0x040001AD
	strb	r2, [r0]
	mov	r2, r1, lsr #8
	ldr	r0, _03800B18	; =0x040001AE
	strb	r2, [r0]
	ldr	r0, _03800B1C	; =0x040001AF
	strb	r1, [r0]
	bx	lr
_03800AF8:	.word	0x040001A4
_03800AFC:	.word	0x040001A1
_03800B00:	.word	0x040001A8
_03800B04:	.word	0x040001A9
_03800B08:	.word	0x040001AA
_03800B0C:	.word	0x040001AB
_03800B10:	.word	0x040001AC
_03800B14:	.word	0x040001AD
_03800B18:	.word	0x040001AE
_03800B1C:	.word	0x040001AF

	arm_func_start CARDi_TaskThread
CARDi_TaskThread: ; 0x03800B20
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	ldr	r9, _03800D28	; =cardi_common
	add	r5, r9, #72	; 0x48
	mov	r8, #0
	add	r7, r9, #252	; 0xfc
	mov	r6, #1
	mov	r4, #3
	mov	fp, #11
_03800B44:
	mov	sl, r8
	bl	OS_DisableInterrupts
	str	r0, [sp]
_03800B50:
	ldr	r0, [r9, #252]	; 0xfc
	ands	r0, r0, #4
	bne	_03800B88
	ldr	r0, [r9, #252]	; 0xfc
	ands	r0, r0, #16
	beq	_03800B94
	ldr	r0, [r7]
	orr	r0, r0, #4
	str	r0, [r7]
	ldr	r0, [r7]
	bic	r0, r0, #16
	str	r0, [r7]
	mov	sl, r6
	b	_03800BA4
_03800B88:
	ldr	r0, [r9, #252]	; 0xfc
	ands	r0, r0, #8
	bne	_03800BA4
_03800B94:
	str	r5, [r9, #236]	; 0xec
	mov	r0, r8
	bl	OS_SleepThread
	b	_03800B50
_03800BA4:
	ldr	r0, [sp]
	bl	OS_RestoreInterrupts
	cmp	sl, #0
	beq	_03800D14
	ldr	r0, [r9]
	str	r8, [r0]
	ldr	r2, [r9]
	ldr	r1, [r2, #76]	; 0x4c
	ldr	r0, [r9, #4]
	mov	r0, r6, lsl r0
	ands	r0, r1, r0
	streq	r4, [r2]
	ldr	r0, [r9, #4]
	cmp	r0, #12
	addls	pc, pc, r0, lsl #2
	b	_03800CB8
	b	_03800CC0
	b	_03800CC0
	b	_03800C18
	b	_03800C20
	b	_03800C30
	b	_03800CB8
	b	_03800C3C
	b	_03800C54
	b	_03800C6C
	b	_03800C84
	b	_03800CB8
	b	_03800C9C
	b	_03800CB0
_03800C18:
	bl	CARDi_InitStatusRegister
	b	_03800CC0
_03800C20:
	bl	CARDi_ReadRomIDCore
	ldr	r1, [r9]
	str	r0, [r1, #8]
	b	_03800CC0
_03800C30:
	ldr	r0, [r9]
	str	r4, [r0]
	b	_03800CC0
_03800C3C:
	ldr	r2, [r9]
	ldr	r0, [r2, #12]
	ldr	r1, [r2, #16]
	ldr	r2, [r2, #20]
	bl	CARDi_ReadBackupCore
	b	_03800CC0
_03800C54:
	ldr	r2, [r9]
	ldr	r0, [r2, #16]
	ldr	r1, [r2, #12]
	ldr	r2, [r2, #20]
	bl	CARDi_WriteBackupCore
	b	_03800CC0
_03800C6C:
	ldr	r2, [r9]
	ldr	r0, [r2, #16]
	ldr	r1, [r2, #12]
	ldr	r2, [r2, #20]
	bl	CARDi_ProgramBackupCore
	b	_03800CC0
_03800C84:
	ldr	r2, [r9]
	ldr	r0, [r2, #16]
	ldr	r1, [r2, #12]
	ldr	r2, [r2, #20]
	bl	CARDi_VerifyBackupCore
	b	_03800CC0
_03800C9C:
	ldr	r1, [r9]
	ldr	r0, [r1, #16]
	ldr	r1, [r1, #20]
	bl	CARDi_EraseBackupSectorCore
	b	_03800CC0
_03800CB0:
	bl	CARDi_EraseChipCore
	b	_03800CC0
_03800CB8:
	ldr	r0, [r9]
	str	r4, [r0]
_03800CC0:
	mov	r0, fp
	mov	r1, r6
	mov	r2, r6
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	blt	_03800CC0
	bl	OS_DisableInterrupts
	mov	sl, r0
	ldr	r0, [r9, #252]	; 0xfc
	bic	r0, r0, #76	; 0x4c
	str	r0, [r9, #252]	; 0xfc
	add	r0, r9, #244	; 0xf4
	bl	OS_WakeupThread
	ldr	r0, [r9, #252]	; 0xfc
	ands	r0, r0, #16
	beq	_03800D08
	mov	r0, r5
	bl	OS_WakeupThreadDirect
_03800D08:
	mov	r0, sl
	bl	OS_RestoreInterrupts
	b	_03800B44
_03800D14:
	mov	r0, r9
	ldr	r1, [r9, #68]	; 0x44
	mov	lr, pc
	bx	r1
	b	_03800B44
_03800D28:	.word	cardi_common

	arm_func_start CARDi_OnFifoRecv
CARDi_OnFifoRecv: ; 0x03800D2C
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	cmp	r0, #11
	bne	_03800DFC
	cmp	r2, #0
	beq	_03800DFC
	ldr	r0, _03800E08	; =cardi_common
	ldr	r2, [r0, #8]
	cmp	r2, #0
	streq	r1, [r0, #4]
	ldr	r2, [r0, #4]
	cmp	r2, #12
	addls	pc, pc, r2, lsl #2
	b	_03800DC8
	b	_03800D98
	b	_03800DC8
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
_03800D98:
	ldr	r2, [r0, #8]
	cmp	r2, #0
	beq	_03800DC8
	cmp	r2, #1
	streq	r1, [r0]
	ldreq	r1, [r0, #252]	; 0xfc
	orreq	r1, r1, #16
	streq	r1, [r0, #252]	; 0xfc
	b	_03800DC8
_03800DBC:
	ldr	r1, [r0, #252]	; 0xfc
	orr	r1, r1, #16
	str	r1, [r0, #252]	; 0xfc
_03800DC8:
	ldr	r1, [r0, #252]	; 0xfc
	ands	r1, r1, #16
	ldreq	r1, [r0, #8]
	addeq	r1, r1, #1
	streq	r1, [r0, #8]
	beq	_03800DFC
	mov	r1, #0
	str	r1, [r0, #8]
	ldr	r1, [r0, #252]	; 0xfc
	ands	r1, r1, #4
	ldrne	r0, [r0, #236]	; 0xec
	addeq	r0, r0, #72	; 0x48
	bl	OS_WakeupThreadDirect
_03800DFC:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03800E08:	.word	cardi_common

	arm_func_start FUN_03800E0C
FUN_03800E0C: ; 0x03800E0C
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r5, #14
	mov	r4, #0
	b	_03800E30
_03800E28:
	mov	r0, r6
	bl	FUN_037F8CB4
_03800E30:
	mov	r0, r5
	mov	r1, r7
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	bne	_03800E28
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr

	arm_func_start FUN_03800E54
FUN_03800E54: ; 0x03800E54
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #0
	bl	CTRDG_VibPulseEdgeUpdate
	bl	SND_BeginSleep
	bl	WVR_Shutdown
	bl	FUN_037FB1F0
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
	bl	FUN_037FB1F0
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
	.balign 2, 0 ; Don't pad with nop
