	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start FUN_03801150
FUN_03801150: ;@ 0x03801150
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	cmp	r2, #0
	bne	_038011B4
	sub	r0, r0, #4
	cmp	r0, #5
	addls	pc, pc, r0, lsl #2
	b	_038011B4
	b	_038011AC
	b	_038011B4
	b	_03801188
	b	_038011B4
	b	_038011A0
	b	_03801194
_03801188:
	mov	r0, r1
	bl	TP_AnalyzeCommand
	b	_038011B4
_03801194:
	mov	r0, r1
	bl	MIC_AnalyzeCommand
	b	_038011B4
_038011A0:
	mov	r0, r1
	bl	PM_AnalyzeCommand
	b	_038011B4
_038011AC:
	mov	r0, r1
	bl	NVRAM_AnalyzeCommand
_038011B4:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start FUN_038011C0
FUN_038011C0: ;@ 0x038011C0
	stmdb	sp!, {r4, r5, r6, lr}
	sub	sp, sp, #8
	ldr	r6, _03801228	;@ =_03809C5C
	add	r5, sp, #0
	mov	r4, #1
_038011D4:
	mov	r0, r6
	mov	r1, r5
	mov	r2, r4
	bl	OS_ReceiveMessage
	ldr	r0, [sp]
	ldr	r1, [r0]
	cmp	r1, #3
	addls	pc, pc, r1, lsl #2
	b	_038011D4
	b	_03801208
	b	_03801220
	b	_03801210
	b	_03801218
_03801208:
	bl	TP_ExecuteProcess
	b	_038011D4
_03801210:
	bl	MIC_ExecuteProcess
	b	_038011D4
_03801218:
	bl	PM_ExecuteProcess
	b	_038011D4
_03801220:
	bl	NVRAM_ExecuteProcess
	b	_038011D4
_03801228:	.word	_03809C5C

	arm_func_start SPIi_CheckEntry
SPIi_CheckEntry: ;@ 0x0380122C
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _03801250	;@ =_03809C5C
	add	r1, sp, #0
	mov	r2, #0
	bl	OS_ReadMessage
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03801250:	.word	_03809C5C

	arm_func_start SPIi_SetEntry
SPIi_SetEntry: ;@ 0x03801254
	stmdb	sp!, {r0, r1, r2, r3}
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r5, r0
	mov	r4, r1
	ldrh	r0, [sp, #24]
	cmp	r0, #4
	movhi	r0, #0
	bhi	_0380130C
	bl	OS_DisableInterrupts
	ldr	r2, _03801318	;@ =_038099B0
	ldr	r3, [r2, #1164]	;@ 0x48c
	mov	r1, #24
	mul	ip, r3, r1
	ldr	r3, _0380131C	;@ =_03809CBC
	str	r5, [r3, ip]
	ldr	r3, [r2, #1164]	;@ 0x48c
	mul	r5, r3, r1
	ldr	r3, _03801320	;@ =_03809CC0
	str	r4, [r3, r5]
	add	r3, sp, #24
	bic	r3, r3, #3
	add	r6, r3, #4
	mov	lr, #0
	ldrh	ip, [sp, #24]
	b	_038012D4
_038012B8:
	add	r6, r6, #4
	ldr	r5, [r6, #-4]
	ldr	r4, [r2, #1164]	;@ 0x48c
	mla	r3, r4, r1, r2
	add	r3, r3, lr, lsl #2
	str	r5, [r3, #788]	;@ 0x314
	add	lr, lr, #1
_038012D4:
	cmp	lr, ip
	blt	_038012B8
	ldr	r1, _03801318	;@ =_038099B0
	ldr	r4, [r1, #1164]	;@ 0x48c
	add	r2, r4, #1
	and	r2, r2, #15
	str	r2, [r1, #1164]	;@ 0x48c
	bl	OS_RestoreInterrupts
	ldr	r0, _03801324	;@ =_03809C5C
	ldr	r2, _0380131C	;@ =_03809CBC
	mov	r1, #24
	mla	r1, r4, r1, r2
	mov	r2, #0
	bl	OS_SendMessage
_0380130C:
	ldmia	sp!, {r4, r5, r6, lr}
	add	sp, sp, #16
	bx	lr
_03801318:	.word	_038099B0
_0380131C:	.word	_03809CBC
_03801320:	.word	_03809CC0
_03801324:	.word	_03809C5C

	arm_func_start SPIi_ReleaseException
SPIi_ReleaseException: ;@ 0x03801328
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _03801364	;@ =_038099B0
	ldr	r2, [r1, #4]
	cmp	r2, r0
	bne	_03801358
	mov	r0, #5
	str	r0, [r1, #4]
	mov	r0, #0
	str	r0, [r1]
	ldr	r0, _03801368	;@ =_03809E40
	bl	OS_WakeupThread
_03801358:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03801364:	.word	_038099B0
_03801368:	.word	_03809E40

	arm_func_start SPIi_GetException
SPIi_GetException: ;@ 0x0380136C
	mov	r2, #1
	ldr	r1, _03801380	;@ =_038099B0
	str	r2, [r1]
	str	r0, [r1, #4]
	bx	lr
_03801380:	.word	_038099B0

	arm_func_start SPIi_CheckException
SPIi_CheckException: ;@ 0x03801384
	ldr	r0, _0380139C	;@ =_038099B0
	ldr	r0, [r0]
	cmp	r0, #0
	moveq	r0, #1
	movne	r0, #0
	bx	lr
_0380139C:	.word	_038099B0

	arm_func_start SPIi_ReturnResult
SPIi_ReturnResult: ;@ 0x038013A0
	stmdb	sp!, {r4, r5, r6, lr}
	and	r2, r0, #112	;@ 0x70
	cmp	r2, #48	;@ 0x30
	bgt	_038013E0
	cmp	r2, #48	;@ 0x30
	bge	_03801434
	cmp	r2, #16
	bgt	_038013D4
	cmp	r2, #16
	bge	_0380141C
	cmp	r2, #0
	beq	_0380141C
	b	_03801438
_038013D4:
	cmp	r2, #32
	beq	_03801434
	b	_03801438
_038013E0:
	cmp	r2, #80	;@ 0x50
	bgt	_038013FC
	cmp	r2, #80	;@ 0x50
	bge	_03801424
	cmp	r2, #64	;@ 0x40
	beq	_03801424
	b	_03801438
_038013FC:
	cmp	r2, #96	;@ 0x60
	bgt	_03801410
	cmp	r2, #96	;@ 0x60
	beq	_0380142C
	b	_03801438
_03801410:
	cmp	r2, #112	;@ 0x70
	beq	_0380142C
	b	_03801438
_0380141C:
	mov	r4, #6
	b	_03801438
_03801424:
	mov	r4, #9
	b	_03801438
_0380142C:
	mov	r4, #8
	b	_03801438
_03801434:
	mov	r4, #4
_03801438:
	and	r0, r0, #255	;@ 0xff
	orr	r0, r0, #128	;@ 0x80
	mov	r0, r0, lsl #8
	orr	r2, r0, #50331648	;@ 0x3000000
	and	r0, r1, #255	;@ 0xff
	orr	r6, r2, r0
	mov	r5, #0
_03801454:
	mov	r0, r4
	mov	r1, r6
	mov	r2, r5
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	blt	_03801454
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start SPI_Unlock
SPI_Unlock: ;@ 0x03801474
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _038014D8	;@ =_038099B0
	ldr	r2, [r1]
	cmp	r2, #0
	beq	_038014CC
	ldr	r2, [r1, #4]
	cmp	r2, #4
	bne	_038014CC
	ldr	r1, [r1, #1176]	;@ 0x498
	cmp	r1, r0
	bne	_038014CC
	bl	OS_DisableInterrupts
	mov	r2, #5
	ldr	r1, _038014D8	;@ =_038099B0
	str	r2, [r1, #4]
	mov	r2, #0
	str	r2, [r1]
	str	r2, [r1, #1176]	;@ 0x498
	bl	OS_RestoreInterrupts
	ldr	r0, _038014DC	;@ =_03809E40
	bl	OS_WakeupThread
_038014CC:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_038014D8:	.word	_038099B0
_038014DC:	.word	_03809E40

	arm_func_start SPI_Lock
SPI_Lock: ;@ 0x038014E0
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	ldr	r5, _0380153C	;@ =_03809E40
	ldr	r4, _03801540	;@ =_038099B0
_038014F4:
	bl	OS_DisableInterrupts
	mov	r6, r0
	ldr	r1, [r4]
	cmp	r1, #0
	beq	_03801518
	bl	OS_RestoreInterrupts
	mov	r0, r5
	bl	OS_SleepThread
	b	_038014F4
_03801518:
	mov	r0, #4
	bl	SPIi_GetException
	ldr	r0, _03801540	;@ =_038099B0
	str	r7, [r0, #1176]	;@ 0x498
	mov	r0, r6
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_0380153C:	.word	_03809E40
_03801540:	.word	_038099B0

	arm_func_start SPI_Init
SPI_Init: ;@ 0x03801544
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	sub	sp, sp, #8
	mov	r4, r0
	ldr	r0, _03801640	;@ =_038099AC
	ldrh	r1, [r0]
	cmp	r1, #0
	bne	_03801634
	mov	r1, #1
	strh	r1, [r0]
	mov	r1, #0
	ldr	r0, _03801644	;@ =_038099B0
	str	r1, [r0]
	mov	r1, #5
	str	r1, [r0, #4]
	bl	TP_Init
	bl	NVRAM_Init
	bl	MIC_Init
	bl	PM_Init
	bl	PXI_Init
	mov	r0, #6
	ldr	r1, _03801648	;@ =FUN_03801150
	bl	PXI_SetFifoRecvCallback
	mov	r0, #9
	ldr	r1, _03801648	;@ =FUN_03801150
	bl	PXI_SetFifoRecvCallback
	mov	r0, #8
	ldr	r1, _03801648	;@ =FUN_03801150
	bl	PXI_SetFifoRecvCallback
	mov	r0, #4
	ldr	r1, _03801648	;@ =FUN_03801150
	bl	PXI_SetFifoRecvCallback
	ldr	r0, _0380164C	;@ =_03809C5C
	ldr	r1, _03801650	;@ =_03809C7C
	mov	r2, #16
	bl	OS_InitMessageQueue
	mov	r8, #0
	ldr	r7, _03801654	;@ =_03809CBC
	mov	r6, r8
	mov	r5, #24
_038015E0:
	mla	r0, r8, r5, r7
	mov	r1, r6
	mov	r2, r5
	bl	MI_CpuFill8
	add	r8, r8, #1
	cmp	r8, #16
	blt	_038015E0
	mov	r2, #0
	ldr	r0, _03801644	;@ =_038099B0
	str	r2, [r0, #1164]	;@ 0x48c
	str	r2, [r0, #1172]	;@ 0x494
	str	r2, [r0, #1168]	;@ 0x490
	mov	r0, #512	;@ 0x200
	str	r0, [sp]
	str	r4, [sp, #4]
	ldr	r0, _03801658	;@ =_038099B8
	ldr	r1, _0380165C	;@ =FUN_038011C0
	ldr	r3, _0380164C	;@ =_03809C5C
	bl	OS_CreateThread
	ldr	r0, _03801658	;@ =_038099B8
	bl	OS_WakeupThreadDirect
_03801634:
	add	sp, sp, #8
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_03801640:	.word	_038099AC
_03801644:	.word	_038099B0
_03801648:	.word	FUN_03801150
_0380164C:	.word	_03809C5C
_03801650:	.word	_03809C7C
_03801654:	.word	_03809CBC
_03801658:	.word	_038099B8
_0380165C:	.word	FUN_038011C0

	arm_func_start FUN_03801660
FUN_03801660: ;@ 0x03801660
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	cmp	r0, #0
	bne	_03801680
	mov	r0, #3
	mov	r1, #2
	bl	SPIi_ReturnResult
	b	_03801698
_03801680:
	ldr	r1, _038016A4	;@ =_03809E54
	str	r0, [r1, #36]	;@ 0x24
	str	r0, [r1, #40]	;@ 0x28
	mov	r0, #3
	mov	r1, #0
	bl	SPIi_ReturnResult
_03801698:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_038016A4:	.word	_03809E54

	arm_func_start FUN_038016A8
FUN_038016A8: ;@ 0x038016A8
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	mov	r4, r0
	mov	r0, #0
	mov	r1, #16
	mov	r2, #1
	mov	r3, r4
	bl	SPIi_SetEntry
	cmp	r0, #0
	bne	_0380170C
	ldr	r0, [sp]
	bic	r0, r0, #100663296	;@ 0x6000000
	orr	r0, r0, #100663296	;@ 0x6000000
	str	r0, [sp]
	ldrh	r1, [sp]
	ldr	r0, _03801718	;@ =0x027FFFAA
	strh	r1, [r0]
	ldrh	r1, [sp, #2]
	ldr	r0, _0380171C	;@ =0x027FFFAC
	strh	r1, [r0]
	mov	r0, #16
	and	r1, r4, #255	;@ 0xff
	mov	r1, r1, lsl #16
	mov	r1, r1, lsr #16
	bl	SPIi_ReturnResult
_0380170C:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_03801718:	.word	0x027FFFAA
_0380171C:	.word	0x027FFFAC

	arm_func_start TP_ExecuteProcess
TP_ExecuteProcess: ;@ 0x03801720
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	sub	sp, sp, #16
	mov	sl, r0
	ldr	r1, [sl, #4]
	cmp	r1, #2
	bhi	_03801754
	cmp	r1, #0
	beq	_0380176C
	cmp	r1, #1
	beq	_03801834
	cmp	r1, #2
	beq	_038018E0
	b	_0380192C
_03801754:
	cmp	r1, #16
	bne	_0380192C
	ldr	r0, _03801938	;@ =_03809E54
	ldr	r0, [r0, #32]
	cmp	r0, #2
	bne	_0380192C
_0380176C:
	bl	OS_DisableInterrupts
	mov	r4, r0
	mov	r0, #0
	bl	SPIi_CheckException
	cmp	r0, #0
	bne	_038017A4
	mov	r0, r4
	bl	OS_RestoreInterrupts
	ldr	r0, [sl, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #4
	bl	SPIi_ReturnResult
	b	_0380192C
_038017A4:
	mov	r0, #0
	bl	SPIi_GetException
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	r0, sp, #8
	ldr	r1, _03801938	;@ =_03809E54
	ldr	r1, [r1, #36]	;@ 0x24
	add	r2, sp, #4
	bl	TP_ExecSampling
	add	r0, sp, #8
	ldrh	r1, [sp, #4]
	bl	FUN_03801954
	ldrh	r1, [sp, #8]
	ldr	r0, _0380193C	;@ =0x027FFFAA
	strh	r1, [r0]
	ldrh	r1, [sp, #10]
	ldr	r0, _03801940	;@ =0x027FFFAC
	strh	r1, [r0]
	ldr	r0, [sl, #4]
	cmp	r0, #0
	bne	_0380180C
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #0
	bl	SPIi_ReturnResult
	b	_03801828
_0380180C:
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	ldr	r1, [sl, #8]
	and	r1, r1, #255	;@ 0xff
	mov	r1, r1, lsl #16
	mov	r1, r1, lsr #16
	bl	SPIi_ReturnResult
_03801828:
	mov	r0, #0
	bl	SPIi_ReleaseException
	b	_0380192C
_03801834:
	ldr	r7, _03801938	;@ =_03809E54
	ldr	r0, [r7, #32]
	cmp	r0, #1
	bne	_038018CC
	mov	r9, #0
	ldr	r8, _03801944	;@ =0x00000107
	ldr	r6, _03801948	;@ =_03809E80
	mov	r5, #10
	ldr	r4, _0380194C	;@ =FUN_038016A8
	b	_0380189C
_0380185C:
	mul	r0, r9, r8
	bl	_u32_div_f
	ldr	r1, [sl, #12]
	add	r0, r1, r0
	mov	r1, r8
	bl	_u32_div_f
	add	r2, r7, r9, lsl #1
	strh	r1, [r2, #204]	;@ 0xcc
	str	r9, [sp]
	mov	r0, #40	;@ 0x28
	mla	r0, r9, r0, r6
	ldrsh	r1, [r2, #204]	;@ 0xcc
	mov	r2, r5
	mov	r3, r4
	bl	OS_SetPeriodicVAlarm
	add	r9, r9, #1
_0380189C:
	ldr	r1, [sl, #8]
	cmp	r9, r1
	bcc	_0380185C
	ldr	r0, [sl, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #0
	bl	SPIi_ReturnResult
	mov	r1, #2
	ldr	r0, _03801938	;@ =_03809E54
	str	r1, [r0, #32]
	b	_0380192C
_038018CC:
	mov	r0, r1, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
	b	_0380192C
_038018E0:
	ldr	r0, _03801938	;@ =_03809E54
	ldr	r0, [r0, #32]
	cmp	r0, #3
	bne	_0380191C
	ldr	r0, _03801950	;@ =0x54505641
	bl	OS_CancelVAlarms
	ldr	r0, [sl, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #0
	bl	SPIi_ReturnResult
	mov	r1, #0
	ldr	r0, _03801938	;@ =_03809E54
	str	r1, [r0, #32]
	b	_0380192C
_0380191C:
	mov	r0, r1, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
_0380192C:
	add	sp, sp, #16
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	bx	lr
_03801938:	.word	_03809E54
_0380193C:	.word	0x027FFFAA
_03801940:	.word	0x027FFFAC
_03801944:	.word	0x00000107
_03801948:	.word	_03809E80
_0380194C:	.word	FUN_038016A8
_03801950:	.word	0x54505641

	arm_func_start FUN_03801954
FUN_03801954: ;@ 0x03801954
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, [r0]
	mov	r2, r0, lsl #7
	movs	r2, r2, lsr #31
	bne	_03801984
	mov	r1, #0
	ldr	r0, _03801A3C	;@ =_03809E50
	strb	r1, [r0]
	ldr	r0, _03801A40	;@ =_03809E4C
	strb	r1, [r0]
	b	_03801A30
_03801984:
	mov	r0, r0, lsl #5
	movs	r0, r0, lsr #30
	beq	_038019D4
	mov	r2, #0
	ldr	r0, _03801A40	;@ =_03809E4C
	strb	r2, [r0]
	ldr	r0, _03801A3C	;@ =_03809E50
	ldrb	r1, [r0]
	add	r1, r1, #1
	strb	r1, [r0]
	ldrb	r1, [r0]
	cmp	r1, #4
	bcc	_03801A30
	strb	r2, [r0]
	ldr	r0, _03801A44	;@ =_03809E54
	ldr	r1, [r0, #36]	;@ 0x24
	cmp	r1, #35	;@ 0x23
	addlt	r1, r1, #1
	strlt	r1, [r0, #36]	;@ 0x24
	b	_03801A30
_038019D4:
	mov	lr, #0
	ldr	r3, _03801A3C	;@ =_03809E50
	strb	lr, [r3]
	ldr	r2, _03801A44	;@ =_03809E54
	ldr	ip, [r2, #36]	;@ 0x24
	cmp	r1, ip, asr #1
	ldrge	r0, _03801A40	;@ =_03809E4C
	strgeb	lr, [r0]
	bge	_03801A30
	ldr	r0, _03801A40	;@ =_03809E4C
	ldrb	r1, [r0]
	add	r1, r1, #1
	strb	r1, [r0]
	ldrb	r1, [r0]
	cmp	r1, #4
	bcc	_03801A30
	strb	lr, [r0]
	ldr	r0, [r2, #40]	;@ 0x28
	cmp	ip, r0
	subgt	r0, ip, #1
	strgt	r0, [r2, #36]	;@ 0x24
	movgt	r0, #3
	strgtb	r0, [r3]
_03801A30:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03801A3C:	.word	_03809E50
_03801A40:	.word	_03809E4C
_03801A44:	.word	_03809E54

	arm_func_start TP_AnalyzeCommand
TP_AnalyzeCommand: ;@ 0x03801A48
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	ands	r1, r0, #33554432	;@ 0x2000000
	beq	_03801A78
	mov	r4, #0
	mov	r3, r4
	ldr	r1, _03801C00	;@ =_03809E54
_03801A64:
	mov	r2, r4, lsl #1
	strh	r3, [r1, r2]
	add	r4, r4, #1
	cmp	r4, #16
	blt	_03801A64
_03801A78:
	and	r1, r0, #983040	;@ 0xf0000
	mov	r1, r1, lsr #16
	mov	r1, r1, lsl #1
	ldr	r2, _03801C00	;@ =_03809E54
	strh	r0, [r2, r1]
	ands	r0, r0, #16777216	;@ 0x1000000
	beq	_03801BF4
	ldrh	r1, [r2]
	and	r0, r1, #65280	;@ 0xff00
	mov	r0, r0, lsl #8
	mov	r4, r0, lsr #16
	cmp	r4, #3
	addls	pc, pc, r4, lsl #2
	b	_03801BE8
	b	_03801AD4
	b	_03801AFC
	b	_03801B98
	b	_03801AC0
_03801AC0:
	and	r0, r1, #255	;@ 0xff
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	bl	FUN_03801660
	b	_03801BF4
_03801AD4:
	mov	r0, #0
	mov	r1, r4
	mov	r2, r0
	bl	SPIi_SetEntry
	cmp	r0, #0
	bne	_03801BF4
	mov	r0, r4
	mov	r1, #4
	bl	SPIi_ReturnResult
	b	_03801BF4
_03801AFC:
	ldr	r0, [r2, #32]
	cmp	r0, #0
	beq	_03801B18
	mov	r0, r4
	mov	r1, #3
	bl	SPIi_ReturnResult
	b	_03801BF4
_03801B18:
	and	r0, r1, #255	;@ 0xff
	mov	r0, r0, lsl #16
	movs	r3, r0, lsr #16
	beq	_03801B30
	cmp	r3, #4
	bls	_03801B40
_03801B30:
	mov	r0, r4
	mov	r1, #2
	bl	SPIi_ReturnResult
	b	_03801BF4
_03801B40:
	ldrh	r1, [r2, #2]
	ldr	r0, _03801C04	;@ =0x00000107
	cmp	r1, r0
	bcc	_03801B60
	mov	r0, r4
	mov	r1, #2
	bl	SPIi_ReturnResult
	b	_03801BF4
_03801B60:
	str	r1, [sp]
	mov	r0, #0
	mov	r1, r4
	mov	r2, #2
	bl	SPIi_SetEntry
	cmp	r0, #0
	movne	r1, #1
	ldrne	r0, _03801C00	;@ =_03809E54
	strne	r1, [r0, #32]
	bne	_03801BF4
	mov	r0, r4
	mov	r1, #4
	bl	SPIi_ReturnResult
	b	_03801BF4
_03801B98:
	ldr	r0, [r2, #32]
	cmp	r0, #2
	beq	_03801BB4
	mov	r0, r4
	mov	r1, #3
	bl	SPIi_ReturnResult
	b	_03801BF4
_03801BB4:
	mov	r0, #0
	mov	r1, r4
	mov	r2, r0
	bl	SPIi_SetEntry
	cmp	r0, #0
	movne	r1, #3
	ldrne	r0, _03801C00	;@ =_03809E54
	strne	r1, [r0, #32]
	bne	_03801BF4
	mov	r0, r4
	mov	r1, #4
	bl	SPIi_ReturnResult
	b	_03801BF4
_03801BE8:
	mov	r0, r4
	mov	r1, #1
	bl	SPIi_ReturnResult
_03801BF4:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_03801C00:	.word	_03809E54
_03801C04:	.word	0x00000107

	arm_func_start TP_Init
TP_Init: ;@ 0x03801C08
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r3, #0
	ldr	r0, _03801CFC	;@ =_03809E54
	str	r3, [r0, #32]
	mov	r1, #20
	str	r1, [r0, #36]	;@ 0x24
	str	r1, [r0, #40]	;@ 0x28
	mov	r2, r3
_03801C28:
	mov	r1, r3, lsl #1
	strh	r2, [r0, r1]
	add	r3, r3, #1
	cmp	r3, #16
	blt	_03801C28
	bl	OS_IsVAlarmAvailable
	cmp	r0, #0
	bne	_03801C4C
	bl	OS_InitVAlarm
_03801C4C:
	mov	r7, #0
	ldr	r6, _03801D00	;@ =_03809E80
	ldr	r5, _03801D04	;@ =0x54505641
	mov	r4, #40	;@ 0x28
_03801C5C:
	mla	r8, r7, r4, r6
	mov	r0, r8
	bl	OS_CreateVAlarm
	mov	r0, r8
	mov	r1, r5
	bl	OS_SetVAlarmTag
	add	r7, r7, #1
	cmp	r7, #4
	blt	_03801C5C
	ldr	r1, _03801D08	;@ =0x040001C0
_03801C84:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03801C84
	ldr	r0, _03801D0C	;@ =0x00008A01
	strh	r0, [r1]
	mov	r1, #132	;@ 0x84
	ldr	r0, _03801D10	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _03801D08	;@ =0x040001C0
_03801CA8:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03801CA8
	mov	r1, #0
	ldr	r0, _03801D10	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _03801D08	;@ =0x040001C0
_03801CC4:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03801CC4
	ldr	r0, _03801D14	;@ =0x00008201
	strh	r0, [r1]
	mov	r1, #0
	ldr	r0, _03801D10	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _03801D08	;@ =0x040001C0
_03801CE8:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03801CE8
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_03801CFC:	.word	_03809E54
_03801D00:	.word	_03809E80
_03801D04:	.word	0x54505641
_03801D08:	.word	0x040001C0
_03801D0C:	.word	0x00008A01
_03801D10:	.word	0x040001C2
_03801D14:	.word	0x00008201

	arm_func_start TP_ExecSampling
TP_ExecSampling: ;@ 0x03801D18
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #12
	mov	r7, r0
	movs	r6, r1
	mov	r5, r2
	mov	r0, #0
	strh	r0, [r5]
	rsbmi	r6, r6, #0
	bl	FUN_03802160
	movs	r4, r0
	bne	_03801D94
	ldr	r1, [r7]
	mov	r0, #4096	;@ 0x1000
	rsb	r0, r0, #0
	and	r0, r1, r0
	str	r0, [r7]
	ldr	r1, [r7]
	ldr	r0, _03801F4C	;@ =0xFF000FFF
	and	r0, r1, r0
	str	r0, [r7]
	ldr	r0, [r7]
	bic	r0, r0, #16777216	;@ 0x1000000
	str	r0, [r7]
	ldr	r0, [r7]
	bic	r0, r0, #100663296	;@ 0x6000000
	orr	r0, r0, #100663296	;@ 0x6000000
	str	r0, [r7]
	mov	r1, #0
	ldr	r0, _03801F50	;@ =_03809F28
	strh	r1, [r0]
	b	_03801F40
_03801D94:
	add	r0, sp, #0
	mov	r1, r6
	mov	r2, #0
	add	r3, sp, #2
	bl	FUN_03801F68
	ldr	r1, [r7]
	bic	r1, r1, #100663296	;@ 0x6000000
	and	r0, r0, #3
	orr	r0, r1, r0, lsl #25
	str	r0, [r7]
	ldr	r1, [r7]
	mov	r0, #4096	;@ 0x1000
	rsb	r0, r0, #0
	and	r2, r1, r0
	ldrh	r1, [sp]
	ldr	r0, _03801F54	;@ =0x00000FFF
	and	r0, r1, r0
	orr	r0, r2, r0
	str	r0, [r7]
	add	r0, sp, #0
	mov	r1, r6
	mov	r2, #1
	add	r3, sp, #4
	bl	FUN_03801F68
	cmp	r0, #2
	bne	_03801E1C
	ldr	r0, [r7]
	bic	r1, r0, #100663296	;@ 0x6000000
	mov	r0, r0, lsl #5
	mov	r0, r0, lsr #30
	orr	r0, r0, #2
	and	r0, r0, #3
	orr	r0, r1, r0, lsl #25
	str	r0, [r7]
_03801E1C:
	ldr	r1, [r7]
	ldr	r0, _03801F4C	;@ =0xFF000FFF
	and	r2, r1, r0
	ldrh	r1, [sp]
	ldr	r0, _03801F54	;@ =0x00000FFF
	and	r0, r1, r0
	orr	r0, r2, r0, lsl #12
	str	r0, [r7]
	ldr	r0, _03801F58	;@ =0x00008A01
	ldr	r3, _03801F5C	;@ =0x040001C0
	strh	r0, [r3]
	mov	r6, #0
	mov	r2, r6
	ldr	r1, _03801F60	;@ =0x040001C2
_03801E54:
	strh	r2, [r1]
_03801E58:
	ldrh	r0, [r3]
	ands	r0, r0, #128	;@ 0x80
	bne	_03801E58
	add	r6, r6, #1
	cmp	r6, #12
	blt	_03801E54
	ldr	r0, _03801F64	;@ =0x00008201
	strh	r0, [r3]
	mov	r1, #0
	ldr	r0, _03801F60	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _03801F5C	;@ =0x040001C0
_03801E88:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03801E88
	cmp	r4, #2
	ldreq	r0, [r7]
	biceq	r0, r0, #100663296	;@ 0x6000000
	orreq	r0, r0, #100663296	;@ 0x6000000
	streq	r0, [r7]
	bl	FUN_03802160
	cmp	r0, #0
	beq	_03801F20
	cmp	r0, #1
	beq	_03801EF0
	cmp	r0, #2
	bne	_03801F3C
	ldr	r0, [r7]
	orr	r0, r0, #16777216	;@ 0x1000000
	str	r0, [r7]
	ldr	r0, [r7]
	bic	r0, r0, #100663296	;@ 0x6000000
	orr	r0, r0, #100663296	;@ 0x6000000
	str	r0, [r7]
	mov	r1, #0
	ldr	r0, _03801F50	;@ =_03809F28
	strh	r1, [r0]
	b	_03801F40
_03801EF0:
	ldr	r0, [r7]
	orr	r0, r0, #16777216	;@ 0x1000000
	str	r0, [r7]
	mov	r1, #1
	ldr	r0, _03801F50	;@ =_03809F28
	strh	r1, [r0]
	ldrh	r0, [sp, #4]
	ldrh	r1, [sp, #2]
	cmp	r1, r0
	movcc	r1, r0
	strh	r1, [r5]
	b	_03801F40
_03801F20:
	ldr	r0, [r7]
	bic	r0, r0, #16777216	;@ 0x1000000
	str	r0, [r7]
	mov	r1, #0
	ldr	r0, _03801F50	;@ =_03809F28
	strh	r1, [r0]
	b	_03801F40
_03801F3C:
	bl	OS_Terminate
_03801F40:
	add	sp, sp, #12
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_03801F4C:	.word	0xFF000FFF
_03801F50:	.word	_03809F28
_03801F54:	.word	0x00000FFF
_03801F58:	.word	0x00008A01
_03801F5C:	.word	0x040001C0
_03801F60:	.word	0x040001C2
_03801F64:	.word	0x00008201

	arm_func_start FUN_03801F68
FUN_03801F68: ;@ 0x03801F68
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	sub	sp, sp, #24
	cmp	r2, #0
	moveq	r5, #209	;@ 0xd1
	moveq	r6, #1
	movne	r5, #145	;@ 0x91
	movne	r6, #2
_03801F84:
	ldr	r4, _0380214C	;@ =0x040001C0
	ldrh	r2, [r4]
	ands	r2, r2, #128	;@ 0x80
	bne	_03801F84
	ldr	r2, _03802150	;@ =0x00008A01
	strh	r2, [r4]
	and	r5, r5, #255	;@ 0xff
	ldr	r2, _03802154	;@ =0x040001C2
	strh	r5, [r2]
_03801FA8:
	ldrh	r2, [r4]
	ands	r2, r2, #128	;@ 0x80
	bne	_03801FA8
	mov	r7, #0
	ldr	ip, _0380214C	;@ =0x040001C0
	ldr	lr, _03802154	;@ =0x040001C2
	add	r2, sp, #0
	mov	r4, r7
	ldr	r9, _03802158	;@ =0x00007FF8
_03801FCC:
	strh	r4, [lr]
_03801FD0:
	ldrh	r8, [ip]
	ands	r8, r8, #128	;@ 0x80
	bne	_03801FD0
	ldrh	r8, [lr]
	and	r8, r8, #255	;@ 0xff
	mov	r8, r8, lsl #16
	mov	r8, r8, lsr #8
	str	r8, [r2, r7, lsl #2]
	strh	r5, [lr]
_03801FF4:
	ldrh	r8, [ip]
	ands	r8, r8, #128	;@ 0x80
	bne	_03801FF4
	ldrh	r8, [lr]
	and	r8, r8, #255	;@ 0xff
	mov	r8, r8, lsl #16
	ldr	sl, [r2, r7, lsl #2]
	orr	r8, sl, r8, lsr #16
	str	r8, [r2, r7, lsl #2]
	ldr	r8, [r2, r7, lsl #2]
	and	r8, r8, r9
	mov	r8, r8, asr #3
	str	r8, [r2, r7, lsl #2]
	add	r7, r7, #1
	cmp	r7, #5
	blt	_03801FCC
	ldr	r2, _0380215C	;@ =0x00008201
	strh	r2, [ip]
	mov	r2, #0
	strh	r2, [lr]
	ldr	r4, _0380214C	;@ =0x040001C0
_03802048:
	ldrh	r2, [r4]
	ands	r2, r2, #128	;@ 0x80
	bne	_03802048
	mov	r8, #0
	mov	r7, r8
	add	r5, sp, #0
_03802060:
	add	r9, r7, #1
	ldr	r4, [r5, r7, lsl #2]
	b	_03802084
_0380206C:
	ldr	r2, [r5, r9, lsl #2]
	subs	r2, r4, r2
	rsbmi	r2, r2, #0
	cmp	r2, r8
	movgt	r8, r2
	add	r9, r9, #1
_03802084:
	cmp	r9, #5
	blt	_0380206C
	add	r7, r7, #1
	cmp	r7, #4
	blt	_03802060
	strh	r8, [r3]
	mov	r4, #0
	add	r2, sp, #0
	b	_0380211C
_038020A8:
	add	r3, r4, #1
	ldr	r7, [r2, r4, lsl #2]
	b	_03802110
_038020B4:
	ldr	r8, [r2, r3, lsl #2]
	subs	r5, r7, r8
	rsbmi	r5, r5, #0
	cmp	r5, r1
	bgt	_0380210C
	add	r9, r3, #1
	b	_03802104
_038020D0:
	ldr	r5, [r2, r9, lsl #2]
	subs	sl, r7, r5
	rsbmi	sl, sl, #0
	cmp	sl, r1
	bgt	_03802100
	add	r1, r8, r7, lsl #1
	add	r1, r5, r1
	mov	r1, r1, asr #2
	bic	r1, r1, #7
	strh	r1, [r0]
	mov	r0, #0
	b	_03802140
_03802100:
	add	r9, r9, #1
_03802104:
	cmp	r9, #5
	blt	_038020D0
_0380210C:
	add	r3, r3, #1
_03802110:
	cmp	r3, #4
	blt	_038020B4
	add	r4, r4, #1
_0380211C:
	cmp	r4, #3
	blt	_038020A8
	ldr	r2, [sp]
	ldr	r1, [sp, #16]
	add	r1, r2, r1
	mov	r1, r1, asr #1
	bic	r1, r1, #7
	strh	r1, [r0]
	mov	r0, r6
_03802140:
	add	sp, sp, #24
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	bx	lr
_0380214C:	.word	0x040001C0
_03802150:	.word	0x00008A01
_03802154:	.word	0x040001C2
_03802158:	.word	0x00007FF8
_0380215C:	.word	0x00008201

	arm_func_start FUN_03802160
FUN_03802160: ;@ 0x03802160
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	ldr	r1, _038022A4	;@ =0x040001C0
_03802174:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03802174
	ldr	r0, _038022A8	;@ =0x00008A01
	strh	r0, [r1]
	mov	r1, #132	;@ 0x84
	ldr	r0, _038022AC	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _038022A4	;@ =0x040001C0
_03802198:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03802198
	mov	r1, #0
	ldr	r0, _038022AC	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _038022A4	;@ =0x040001C0
_038021B4:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038021B4
	ldr	r0, _038022B0	;@ =0x00008201
	strh	r0, [r1]
	mov	r1, #0
	ldr	r0, _038022AC	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _038022A4	;@ =0x040001C0
_038021D8:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038021D8
	ldr	r0, _038022B4	;@ =_03809F28
	ldrh	r0, [r0]
	cmp	r0, #0
	bne	_0380220C
	ldr	r0, _038022B8	;@ =0x04000136
	ldrh	r0, [r0]
	ands	r0, r0, #64	;@ 0x40
	moveq	r0, #1
	movne	r0, #0
	b	_03802298
_0380220C:
	ldr	r0, _038022B8	;@ =0x04000136
	ldrh	r0, [r0]
	ands	r0, r0, #64	;@ 0x40
	moveq	r0, #1
	beq	_03802298
	ldr	r0, _038022A8	;@ =0x00008A01
	strh	r0, [r1]
	mov	r1, #132	;@ 0x84
	ldr	r0, _038022AC	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _038022A4	;@ =0x040001C0
_03802238:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03802238
	mov	r1, #0
	ldr	r0, _038022AC	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _038022A4	;@ =0x040001C0
_03802254:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03802254
	ldr	r0, _038022B0	;@ =0x00008201
	strh	r0, [r1]
	mov	r1, #0
	ldr	r0, _038022AC	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _038022A4	;@ =0x040001C0
_03802278:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03802278
	ldr	r0, _038022B8	;@ =0x04000136
	ldrh	r0, [r0]
	ands	r0, r0, #64	;@ 0x40
	movne	r0, #0
	moveq	r0, #2
_03802298:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_038022A4:	.word	0x040001C0
_038022A8:	.word	0x00008A01
_038022AC:	.word	0x040001C2
_038022B0:	.word	0x00008201
_038022B4:	.word	_03809F28
_038022B8:	.word	0x04000136

	arm_func_start PM_ExecuteProcess
PM_ExecuteProcess: ;@ 0x038022BC
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r4, r0
	bl	OS_DisableInterrupts
	mov	r5, r0
	mov	r0, #3
	bl	SPIi_CheckException
	cmp	r0, #0
	bne	_03802300
	mov	r0, r5
	bl	OS_RestoreInterrupts
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #4
	bl	SPIi_ReturnResult
	b	_0380242C
_03802300:
	mov	r0, #3
	bl	SPIi_GetException
	mov	r0, r5
	bl	OS_RestoreInterrupts
	ldr	r1, [r4, #4]
	sub	r0, r1, #97	;@ 0x61
	cmp	r0, #5
	addls	pc, pc, r0, lsl #2
	b	_03802414
	b	_0380233C
	b	_03802414
	b	_038023E0
	b	_03802368
	b	_038023A4
	b	_03802408
_0380233C:
	mov	r1, #1
	ldr	r0, _03802438	;@ =PMi_Work
	str	r1, [r0, #32]
	ldr	r1, [r4, #8]
	ldr	r0, _0380243C	;@ =PMi_TriggerBL
	strh	r1, [r0]
	ldr	r1, [r4, #12]
	ldr	r0, _03802440	;@ =PMi_KeyPattern
	strh	r1, [r0]
	bl	PMi_DoSleep
	b	_03802424
_03802368:
	mov	r1, #4
	ldr	r0, _03802438	;@ =PMi_Work
	str	r1, [r0, #32]
	ldr	r2, [r4, #8]
	str	r2, [r0, #40]	;@ 0x28
	ldr	r1, [r4, #12]
	str	r1, [r0, #36]	;@ 0x24
	mov	r0, r2, lsl #16
	mov	r0, r0, lsr #16
	and	r1, r1, #255	;@ 0xff
	bl	PMi_SetRegister
	mov	r0, #100	;@ 0x64
	mov	r1, #0
	bl	SPIi_ReturnResult
	b	_03802424
_038023A4:
	mov	r1, #3
	ldr	r0, _03802438	;@ =PMi_Work
	str	r1, [r0, #32]
	ldr	r1, [r4, #8]
	str	r1, [r0, #40]	;@ 0x28
	mov	r0, r1, lsl #16
	mov	r4, r0, lsr #16
	mov	r0, r4
	bl	PMi_GetRegister
	mov	r1, r0
	add	r0, r4, #112	;@ 0x70
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	bl	SPIi_ReturnResult
	b	_03802424
_038023E0:
	mov	r0, #2
	ldr	r1, _03802438	;@ =PMi_Work
	str	r0, [r1, #32]
	ldr	r0, [r4, #8]
	str	r0, [r1, #36]	;@ 0x24
	bl	PMi_SwitchUtilityProc
	mov	r0, #99	;@ 0x63
	mov	r1, #0
	bl	SPIi_ReturnResult
	b	_03802424
_03802408:
	ldr	r0, [r4, #8]
	bl	PMi_SetLED
	b	_03802424
_03802414:
	mov	r0, r1, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #1
	bl	SPIi_ReturnResult
_03802424:
	mov	r0, #3
	bl	SPIi_ReleaseException
_0380242C:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_03802438:	.word	PMi_Work
_0380243C:	.word	PMi_TriggerBL
_03802440:	.word	PMi_KeyPattern

	arm_func_start PM_AnalyzeCommand
PM_AnalyzeCommand: ;@ 0x03802444
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	ands	r1, r0, #33554432	;@ 0x2000000
	beq	_03802474
	mov	r4, #0
	mov	r3, r4
	ldr	r1, _03802610	;@ =PMi_Work
_03802460:
	mov	r2, r4, lsl #1
	strh	r3, [r1, r2]
	add	r4, r4, #1
	cmp	r4, #16
	blt	_03802460
_03802474:
	and	r1, r0, #983040	;@ 0xf0000
	mov	r1, r1, lsr #16
	mov	r1, r1, lsl #1
	ldr	ip, _03802610	;@ =PMi_Work
	strh	r0, [ip, r1]
	ands	r0, r0, #16777216	;@ 0x1000000
	beq	_03802604
	ldrh	r3, [ip]
	and	r0, r3, #65280	;@ 0xff00
	mov	r0, r0, lsl #8
	mov	r4, r0, lsr #16
	sub	r0, r4, #96	;@ 0x60
	cmp	r0, #7
	addls	pc, pc, r0, lsl #2
	b	_038025F8
	b	_038024D0
	b	_038024E0
	b	_038025F8
	b	_03802588
	b	_0380251C
	b	_03802558
	b	_038025C4
	b	_038025DC
_038024D0:
	mov	r0, #96	;@ 0x60
	mov	r1, #0
	bl	SPIi_ReturnResult
	b	_03802604
_038024E0:
	ldrh	r1, [ip, #2]
	ldr	r0, _03802614	;@ =0x0000FFFF
	and	r0, r1, r0
	str	r0, [sp]
	mov	r0, #3
	mov	r1, r4
	mov	r2, #2
	and	r3, r3, #255	;@ 0xff
	bl	SPIi_SetEntry
	cmp	r0, #0
	bne	_03802604
	mov	r0, r4
	mov	r1, #4
	bl	SPIi_ReturnResult
	b	_03802604
_0380251C:
	ldrh	r1, [ip, #2]
	ldr	r0, _03802614	;@ =0x0000FFFF
	and	r0, r1, r0
	str	r0, [sp]
	mov	r0, #3
	mov	r1, r4
	mov	r2, #2
	and	r3, r3, #255	;@ 0xff
	bl	SPIi_SetEntry
	cmp	r0, #0
	bne	_03802604
	mov	r0, r4
	mov	r1, #4
	bl	SPIi_ReturnResult
	b	_03802604
_03802558:
	mov	r0, #3
	mov	r1, r4
	mov	r2, #1
	ldr	ip, _03802614	;@ =0x0000FFFF
	and	r3, r3, ip
	bl	SPIi_SetEntry
	cmp	r0, #0
	bne	_03802604
	mov	r0, r4
	mov	r1, #4
	bl	SPIi_ReturnResult
	b	_03802604
_03802588:
	mov	r0, #3
	mov	r1, r4
	mov	r2, #1
	and	lr, r3, #255	;@ 0xff
	ldrh	ip, [ip, #2]
	ldr	r3, _03802614	;@ =0x0000FFFF
	and	r3, ip, r3
	orr	r3, r3, lr, lsl #16
	bl	SPIi_SetEntry
	cmp	r0, #0
	bne	_03802604
	mov	r0, r4
	mov	r1, #4
	bl	SPIi_ReturnResult
	b	_03802604
_038025C4:
	and	r0, r3, #255	;@ 0xff
	bl	PM_SetLEDPattern
	mov	r0, #102	;@ 0x66
	mov	r1, #0
	bl	SPIi_ReturnResult
	b	_03802604
_038025DC:
	bl	PM_GetLEDPattern
	mov	r1, r0
	mov	r0, #103	;@ 0x67
	mov	r1, r1, lsl #16
	mov	r1, r1, lsr #16
	bl	SPIi_ReturnResult
	b	_03802604
_038025F8:
	mov	r0, r4
	mov	r1, #1
	bl	SPIi_ReturnResult
_03802604:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_03802610:	.word	PMi_Work
_03802614:	.word	0x0000FFFF

	arm_func_start PM_Init
PM_Init: ;@ 0x03802618
	mov	r1, #1
	ldr	r0, _0380264C	;@ =PMi_Initialized
	str	r1, [r0]
	mov	r3, #0
	ldr	r0, _03802650	;@ =PMi_Work
	str	r3, [r0, #32]
	mov	r2, r3
_03802634:
	mov	r1, r3, lsl #1
	strh	r2, [r0, r1]
	add	r3, r3, #1
	cmp	r3, #16
	blt	_03802634
	bx	lr
_0380264C:	.word	PMi_Initialized
_03802650:	.word	PMi_Work

	arm_func_start PMi_SendPxiCommand
PMi_SendPxiCommand: ;@ 0x03802654
	ldr	r3, _03802678	;@ =0x0000FFFF
	and	r3, r2, r3
	and	r0, r0, #62914560	;@ 0x3c00000
	mov	r2, r0, lsl #22
	and	r0, r1, #4128768	;@ 0x3f0000
	orr	r0, r2, r0, lsl #16
	orr	r0, r3, r0
	ldr	ip, _0380267C	;@ =PMi_SendPxiData
	bx	ip
_03802678:	.word	0x0000FFFF
_0380267C:	.word	PMi_SendPxiData

	arm_func_start PMi_SendPxiData
PMi_SendPxiData: ;@ 0x03802680
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, #8
	mov	r4, #0
_03802690:
	mov	r0, r5
	mov	r1, r6
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	bne	_03802690
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start PMi_ResetControl
PMi_ResetControl: ;@ 0x038026B0
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #0
	bl	PMi_GetRegister
	mvn	r1, r4
	and	r0, r0, r1
	and	r1, r0, #255	;@ 0xff
	mov	r0, #0
	bl	PMi_SetRegister
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start PMi_SetControl
PMi_SetControl: ;@ 0x038026DC
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #0
	bl	PMi_GetRegister
	orr	r1, r0, r4
	mov	r0, #0
	bl	PMi_SetRegister
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start PMi_GetRegister
PMi_GetRegister: ;@ 0x03802700
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	ldr	r1, _0380278C	;@ =0x040001C0
_0380270C:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_0380270C
	bl	FUN_03802808
	mov	r0, #1
	bl	FUN_03802820
	orr	r0, r4, #128	;@ 0x80
	and	r0, r0, #255	;@ 0xff
	and	r1, r0, #255	;@ 0xff
	ldr	r0, _03802790	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _0380278C	;@ =0x040001C0
_0380273C:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_0380273C
	mov	r0, #0
	bl	FUN_03802820
	mov	r1, #0
	ldr	r0, _03802790	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _0380278C	;@ =0x040001C0
_03802760:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03802760
	ldr	r0, _03802790	;@ =0x040001C2
	ldrh	r0, [r0]
	and	r0, r0, #255	;@ 0xff
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	and	r0, r0, #255	;@ 0xff
	ldmia	sp!, {r4, lr}
	bx	lr
_0380278C:	.word	0x040001C0
_03802790:	.word	0x040001C2

	arm_func_start PMi_SetRegister
PMi_SetRegister: ;@ 0x03802794
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, r1
	ldr	r1, _03802800	;@ =0x040001C0
_038027A8:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038027A8
	bl	FUN_03802808
	mov	r0, #1
	bl	FUN_03802820
	and	r0, r5, #255	;@ 0xff
	and	r1, r0, #255	;@ 0xff
	ldr	r0, _03802804	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _03802800	;@ =0x040001C0
_038027D4:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038027D4
	mov	r0, #0
	bl	FUN_03802820
	and	r1, r4, #255	;@ 0xff
	ldr	r0, _03802804	;@ =0x040001C2
	strh	r1, [r0]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_03802800:	.word	0x040001C0
_03802804:	.word	0x040001C2

	arm_func_start FUN_03802808
FUN_03802808: ;@ 0x03802808
	ldr	r1, _03802818	;@ =0x00008202
	ldr	r0, _0380281C	;@ =0x040001C0
	strh	r1, [r0]
	bx	lr
_03802818:	.word	0x00008202
_0380281C:	.word	0x040001C0

	arm_func_start FUN_03802820
FUN_03802820: ;@ 0x03802820
	ldr	r1, _03802834	;@ =0x00008002
	orr	r1, r1, r0, lsl #11
	ldr	r0, _03802838	;@ =0x040001C0
	strh	r1, [r0]
	bx	lr
_03802834:	.word	0x00008002
_03802838:	.word	0x040001C0

	arm_func_start PMi_SetLED
PMi_SetLED: ;@ 0x0380283C
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	cmp	r4, #1
	beq	_03802860
	cmp	r4, #2
	beq	_03802878
	cmp	r4, #3
	beq	_0380286C
	b	_0380288C
_03802860:
	mov	r0, #16
	bl	PMi_ResetControl
	b	_03802890
_0380286C:
	mov	r0, #48	;@ 0x30
	bl	PMi_SetControl
	b	_03802890
_03802878:
	mov	r0, #32
	bl	PMi_ResetControl
	mov	r0, #16
	bl	PMi_SetControl
	b	_03802890
_0380288C:
	bl	OS_Terminate
_03802890:
	ldr	r0, _038028A0	;@ =PMi_LEDStatus
	str	r4, [r0]
	ldmia	sp!, {r4, lr}
	bx	lr
_038028A0:	.word	PMi_LEDStatus

	arm_func_start PMi_SwitchUtilityProc
PMi_SwitchUtilityProc: ;@ 0x038028A4
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	cmp	r0, #15
	addls	pc, pc, r0, lsl #2
	b	_038029C4
	b	_038029C4
	b	_038028F8
	b	_0380290C
	b	_03802920
	b	_03802934
	b	_03802940
	b	_0380294C
	b	_03802958
	b	_03802964
	b	_03802970
	b	_0380297C
	b	_03802988
	b	_03802994
	b	_038029A0
	b	_038029B8
	b	_038029AC
_038028F8:
	mov	r0, #1
	bl	PM_SetLEDPattern
	mov	r0, #1
	bl	PMi_SetLED
	b	_038029C4
_0380290C:
	mov	r0, #3
	bl	PM_SetLEDPattern
	mov	r0, #3
	bl	PMi_SetLED
	b	_038029C4
_03802920:
	mov	r0, #2
	bl	PM_SetLEDPattern
	mov	r0, #2
	bl	PMi_SetLED
	b	_038029C4
_03802934:
	mov	r0, #4
	bl	PMi_SetControl
	b	_038029C4
_03802940:
	mov	r0, #4
	bl	PMi_ResetControl
	b	_038029C4
_0380294C:
	mov	r0, #8
	bl	PMi_SetControl
	b	_038029C4
_03802958:
	mov	r0, #8
	bl	PMi_ResetControl
	b	_038029C4
_03802964:
	mov	r0, #12
	bl	PMi_SetControl
	b	_038029C4
_03802970:
	mov	r0, #12
	bl	PMi_ResetControl
	b	_038029C4
_0380297C:
	mov	r0, #1
	bl	PMi_SetControl
	b	_038029C4
_03802988:
	mov	r0, #1
	bl	PMi_ResetControl
	b	_038029C4
_03802994:
	mov	r0, #2
	bl	PMi_ResetControl
	b	_038029C4
_038029A0:
	mov	r0, #2
	bl	PMi_SetControl
	b	_038029C4
_038029AC:
	mov	r0, #64	;@ 0x40
	bl	PMi_ResetControl
	b	_038029C4
_038029B8:
	bl	SND_BeginSleep
	mov	r0, #64	;@ 0x40
	bl	PMi_SetControl
_038029C4:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start PMi_DoSleep
PMi_DoSleep: ;@ 0x038029D0
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r5, #0
	ldr	r0, _03802B94	;@ =0x04000208
	ldrh	r4, [r0]
	strh	r5, [r0]
	bl	OS_DisableInterrupts
	mov	r9, r0
	mvn	r0, #-33554432	;@ 0xfe000000
	bl	OS_DisableIrqMask
	mov	r8, r0
	mov	r0, r5
	bl	PMi_GetRegister
	mov	r7, r0
	mov	r0, #2
	bl	PM_SetLEDPattern
	mov	r0, #2
	bl	PMi_SetLED
	mov	r0, #2
	bl	PMi_SetLED
	bl	SND_BeginSleep
	mov	r0, #1
	bl	PMi_ResetControl
	ldr	r0, _03802B98	;@ =PMi_TriggerBL
	ldrh	r0, [r0]
	ands	r0, r0, #1
	beq	_03802A58
	ldr	r0, _03802B9C	;@ =PMi_KeyPattern
	ldrh	r0, [r0]
	orr	r1, r0, #16384	;@ 0x4000
	ldr	r0, _03802BA0	;@ =0x04000132
	strh	r1, [r0]
	mov	r0, #4096	;@ 0x1000
	bl	OS_EnableIrqMask
_03802A58:
	ldr	r0, _03802B98	;@ =PMi_TriggerBL
	ldrh	r0, [r0]
	ands	r0, r0, #4
	beq	_03802A70
	mov	r0, #4194304	;@ 0x400000
	bl	OS_EnableIrqMask
_03802A70:
	ldr	r0, _03802B98	;@ =PMi_TriggerBL
	ldrh	r0, [r0]
	ands	r0, r0, #2
	beq	_03802AB4
	ldr	r0, _03802BA4	;@ =0x04000134
	ldrh	r6, [r0]
	mov	r5, #1
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	mov	r0, #64	;@ 0x40
	mov	r1, #0
	bl	EXIi_SetBitRcnt0L
	mov	r0, #256	;@ 0x100
	mov	r1, r0
	bl	EXIi_SetBitRcnt0L
	mov	r0, #128	;@ 0x80
	bl	OS_EnableIrqMask
_03802AB4:
	ldr	r0, _03802B98	;@ =PMi_TriggerBL
	ldrh	r0, [r0]
	ands	r0, r0, #8
	beq	_03802ACC
	mov	r0, #1048576	;@ 0x100000
	bl	OS_EnableIrqMask
_03802ACC:
	ldr	r0, _03802B98	;@ =PMi_TriggerBL
	ldrh	r0, [r0]
	ands	r0, r0, #16
	beq	_03802AE4
	mov	r0, #8192	;@ 0x2000
	bl	OS_EnableIrqMask
_03802AE4:
	mov	r0, r9
	bl	OS_RestoreInterrupts
	ldr	r1, _03802B94	;@ =0x04000208
	ldrh	r0, [r1]
	mov	r0, #1
	strh	r0, [r1]
	bl	FUN_03802BAC
	mov	r0, #0
	mov	r1, r7
	bl	PMi_SetRegister
	ldr	r0, _03802B98	;@ =PMi_TriggerBL
	ldrh	r1, [r0]
	ands	r0, r1, #32
	movne	r0, #6
	moveq	r0, #7
	ands	r1, r1, #64	;@ 0x40
	movne	r7, #4
	moveq	r7, #5
	bl	PMi_SwitchUtilityProc
	mov	r0, r7
	bl	PMi_SwitchUtilityProc
	cmp	r5, #0
	ldrne	r0, _03802BA4	;@ =0x04000134
	strneh	r6, [r0]
	mov	r0, #1
	bl	PMi_SetControl
	bl	SND_EndSleep
	mov	r1, #0
	ldr	r0, _03802BA8	;@ =PMi_Work
	str	r1, [r0, #32]
	mov	r0, #98	;@ 0x62
	mov	r2, r1
	bl	PMi_SendPxiCommand
	bl	OS_DisableInterrupts
	mov	r0, r8
	bl	OS_SetIrqMask
	mov	r0, r9
	bl	OS_RestoreInterrupts
	ldr	r1, _03802B94	;@ =0x04000208
	ldrh	r0, [r1]
	strh	r4, [r1]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_03802B94:	.word	0x04000208
_03802B98:	.word	PMi_TriggerBL
_03802B9C:	.word	PMi_KeyPattern
_03802BA0:	.word	0x04000132
_03802BA4:	.word	0x04000134
_03802BA8:	.word	PMi_Work

	arm_func_start FUN_03802BAC
FUN_03802BAC: ;@ 0x03802BAC
	ldr	ip, _03802BB4	;@ =SVC_Stop
	bx	ip
_03802BB4:	.word	SVC_Stop

	arm_func_start PM_GetLEDPattern
PM_GetLEDPattern: ;@ 0x03802BB8
	ldr	r0, _03802BC4	;@ =PMi_BlinkPatternNo
	ldr	r0, [r0]
	bx	lr
_03802BC4:	.word	PMi_BlinkPatternNo

	arm_func_start PM_SetLEDPattern
PM_SetLEDPattern: ;@ 0x03802BC8
	cmp	r0, #15
	ldrle	r1, _03802BE4	;@ =PMi_BlinkPatternNo
	strle	r0, [r1]
	movle	r1, #0
	ldrle	r0, _03802BE8	;@ =_03809F64
	strle	r1, [r0]
	bx	lr
_03802BE4:	.word	PMi_BlinkPatternNo
_03802BE8:	.word	_03809F64

	arm_func_start PM_SelfBlinkProc
PM_SelfBlinkProc: ;@ 0x03802BEC
	stmdb	sp!, {r4, r5, r6, lr}
	ldr	r0, _03802D04	;@ =PMi_BlinkPatternNo
	ldr	r3, [r0]
	cmp	r3, #0
	bne	_03802C28
	mov	r0, #3
	mov	r1, #102	;@ 0x66
	mov	r2, #1
	mov	r3, r2
	bl	SPIi_SetEntry
	cmp	r0, #0
	beq	_03802CFC
	mov	r0, #1
	bl	PM_SetLEDPattern
	b	_03802CFC
_03802C28:
	cmp	r3, #4
	bge	_03802C54
	ldr	r0, _03802D08	;@ =PMi_LEDStatus
	ldr	r0, [r0]
	cmp	r3, r0
	beq	_03802CFC
	mov	r0, #3
	mov	r1, #102	;@ 0x66
	mov	r2, #1
	bl	SPIi_SetEntry
	b	_03802CFC
_03802C54:
	ldr	r6, _03802D0C	;@ =PMi_BlinkPatternData
	sub	r1, r3, #4
	mov	r0, #12
	mul	r5, r1, r0
	add	r4, r6, r5
	ldr	r0, _03802D10	;@ =_03809F64
	ldr	r0, [r0]
	ldrh	r1, [r4, #10]
	bl	_u32_div_f
	ldr	r5, [r6, r5]
	ldr	lr, [r4, #4]
	mov	r3, #0
	mov	r2, #-2147483648	;@ 0x80000000
	mov	ip, r3, lsr r0
	rsb	r1, r0, #32
	orr	ip, ip, r2, lsl r1
	sub	r1, r0, #32
	orr	ip, ip, r2, lsr r1
	and	r0, lr, r2, lsr r0
	and	r1, r5, ip
	cmp	r0, r3
	cmpeq	r1, r3
	movne	r3, #1
	moveq	r3, #2
	ldr	r0, _03802D10	;@ =_03809F64
	ldr	r1, [r0]
	add	ip, r1, #1
	str	ip, [r0]
	ldrh	r2, [r4, #8]
	ldrh	r1, [r4, #10]
	mul	r1, r2, r1
	cmp	ip, r1
	movcs	r1, #0
	strcs	r1, [r0]
	ldr	r0, _03802D08	;@ =PMi_LEDStatus
	ldr	r0, [r0]
	cmp	r3, r0
	beq	_03802CFC
	mov	r0, #3
	mov	r1, #102	;@ 0x66
	mov	r2, #1
	bl	SPIi_SetEntry
_03802CFC:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr
_03802D04:	.word	PMi_BlinkPatternNo
_03802D08:	.word	PMi_LEDStatus
_03802D0C:	.word	PMi_BlinkPatternData
_03802D10:	.word	_03809F64

	arm_func_start FUN_03802D14
FUN_03802D14: ;@ 0x03802D14
	stmdb	sp!, {r4, r5, r6, r7, lr}
	ldr	r4, _03802E6C	;@ =_03809F6C
	ldrh	r5, [r4, #38]	;@ 0x26
	and	r0, r5, #4
	cmp	r0, #4
	ldrh	r6, [r4, #56]	;@ 0x38
	ldrneh	r7, [r4, #58]	;@ 0x3a
	ldreq	r7, _03802E70	;@ =0x0000FFFF
	bl	SPIi_CheckEntry
	cmp	r0, #0
	bne	_03802D80
	mov	r0, #2
	bl	SPIi_CheckException
	cmp	r0, #0
	beq	_03802D80
	and	r0, r5, #1
	cmp	r0, #1
	bne	_03802D70
	bl	MIC_ExecSampling12
	tst	r5, #2
	moveq	r7, r0
	eorne	r7, r0, #32768	;@ 0x8000
	b	_03802D80
_03802D70:
	bl	MIC_ExecSampling8
	tst	r5, #2
	moveq	r7, r0
	eorne	r7, r0, #128	;@ 0x80
_03802D80:
	and	r0, r5, #1
	ldr	r3, _03802E74	;@ =0x027FFC00
	ldr	r1, [r4, #44]	;@ 0x2c
	cmp	r0, #1
	bne	_03802DB0
	ldr	r2, [r4, #40]	;@ 0x28
	strh	r7, [r2, r1]!
	str	r2, [r3, #912]	;@ 0x390
	add	r3, r3, #916	;@ 0x394
	strh	r7, [r3]
	add	r1, r1, #2
	b	_03802DE8
_03802DB0:
	and	r7, r7, #255	;@ 0xff
	tst	r1, #1
	bne	_03802DC8
	mov	r6, r7
	add	r1, r1, #1
	b	_03802DE8
_03802DC8:
	orr	r0, r6, r7, lsl #8
	ldr	r2, [r4, #40]	;@ 0x28
	sub	r1, r1, #1
	strh	r0, [r2, r1]!
	str	r2, [r3, #912]	;@ 0x390
	add	r3, r3, #916	;@ 0x394
	strh	r0, [r3]
	add	r1, r1, #2
_03802DE8:
	strh	r6, [r4, #56]	;@ 0x38
	strh	r7, [r4, #58]	;@ 0x3a
	ldr	r0, [r4, #48]	;@ 0x30
	cmp	r1, r0
	movcs	r1, #0
	str	r1, [r4, #44]	;@ 0x2c
	bcc	_03802E64
	ldrh	r0, [r4, #36]	;@ 0x24
	and	r0, r0, #16
	cmp	r0, #16
	bne	_03802E24
	mov	r0, #81	;@ 0x51
	mov	r1, #0
	bl	SPIi_ReturnResult
	b	_03802E64
_03802E24:
	mov	r0, #2
	mov	r1, #66	;@ 0x42
	mov	r2, #0
	bl	SPIi_SetEntry
	cmp	r0, #0
	bne	_03802E4C
	mov	r0, #81	;@ 0x51
	mov	r1, #4
	bl	SPIi_ReturnResult
	b	_03802E64
_03802E4C:
	mov	r0, #4
	str	r0, [r4, #32]
	ldr	r1, _03802E78	;@ =0x0400010E
	ldrh	r0, [r1]
	bic	r0, r0, #128	;@ 0x80
	strh	r0, [r1]
_03802E64:
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_03802E6C:	.word	_03809F6C
_03802E70:	.word	0x0000FFFF
_03802E74:	.word	0x027FFC00
_03802E78:	.word	0x0400010E

	arm_func_start FUN_03802E7C
FUN_03802E7C: ;@ 0x03802E7C
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	bl	FUN_03802D14
	ldr	r1, _03802EB0	;@ =0x0380FFF8
	ldr	r0, [r1]
	orr	r0, r0, #64	;@ 0x40
	str	r0, [r1]
	mov	r1, #64	;@ 0x40
	ldr	r0, _03802EB4	;@ =0x04000214
	str	r1, [r0]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03802EB0:	.word	0x0380FFF8
_03802EB4:	.word	0x04000214

	arm_func_start MIC_ExecuteProcess
MIC_ExecuteProcess: ;@ 0x03802EB8
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	ldr	r2, [r5, #4]
	cmp	r2, #64	;@ 0x40
	beq	_03802EE4
	cmp	r2, #65	;@ 0x41
	beq	_03802FB0
	cmp	r2, #66	;@ 0x42
	beq	_0380304C
	b	_038030F0
_03802EE4:
	bl	OS_DisableInterrupts
	mov	r4, r0
	mov	r0, #2
	bl	SPIi_CheckException
	cmp	r0, #0
	bne	_03802F1C
	mov	r0, r4
	bl	OS_RestoreInterrupts
	ldr	r0, [r5, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #4
	bl	SPIi_ReturnResult
	b	_038030F0
_03802F1C:
	mov	r0, #2
	bl	SPIi_GetException
	mov	r0, r4
	bl	OS_RestoreInterrupts
	ldr	r0, [r5, #8]
	and	r0, r0, #1
	cmp	r0, #1
	bne	_03802F68
	bl	MIC_ExecSampling12
	ldr	r1, [r5, #8]
	ands	r1, r1, #2
	eorne	r0, r0, #32768	;@ 0x8000
	movne	r0, r0, lsl #16
	movne	r0, r0, lsr #16
	ldr	r1, _038030FC	;@ =0x027FFF94
	strh	r0, [r1]
	ldr	r0, _03803100	;@ =0x027FFF90
	str	r1, [r0]
	b	_03802F90
_03802F68:
	bl	MIC_ExecSampling8
	ldr	r1, [r5, #8]
	ands	r1, r1, #2
	eorne	r0, r0, #128	;@ 0x80
	movne	r0, r0, lsl #16
	movne	r0, r0, lsr #16
	ldr	r1, _038030FC	;@ =0x027FFF94
	strh	r0, [r1]
	ldr	r0, _03803100	;@ =0x027FFF90
	str	r1, [r0]
_03802F90:
	ldr	r0, [r5, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #0
	bl	SPIi_ReturnResult
	mov	r0, #2
	bl	SPIi_ReleaseException
	b	_038030F0
_03802FB0:
	ldr	r0, _03803104	;@ =_03809F6C
	ldr	r1, [r0, #32]
	cmp	r1, #1
	bne	_03803038
	mov	r1, #0
	strh	r1, [r0, #58]	;@ 0x3a
	strh	r1, [r0, #56]	;@ 0x38
	bl	OS_DisableInterrupts
	mov	r4, r0
	mov	r0, #64	;@ 0x40
	bl	OS_EnableIrqMask
	mov	r0, #64	;@ 0x40
	ldr	r1, _03803108	;@ =FUN_03802E7C
	bl	MIC_SetIrqFunction
	bl	MIC_EnableMultipleInterrupt
	ldr	r0, _03803104	;@ =_03809F6C
	ldrh	r2, [r0, #52]	;@ 0x34
	ldr	r1, _0380310C	;@ =0x0400010C
	strh	r2, [r1]
	ldrh	r0, [r0, #54]	;@ 0x36
	orr	r1, r0, #192	;@ 0xc0
	ldr	r0, _03803110	;@ =0x0400010E
	strh	r1, [r0]
	mov	r0, r4
	bl	OS_RestoreInterrupts
	ldr	r0, [r5, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #0
	bl	SPIi_ReturnResult
	mov	r1, #2
	ldr	r0, _03803104	;@ =_03809F6C
	str	r1, [r0, #32]
	b	_038030F0
_03803038:
	mov	r0, r2, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
	b	_038030F0
_0380304C:
	ldr	r0, _03803104	;@ =_03809F6C
	ldr	r1, [r0, #32]
	sub	r0, r1, #3
	cmp	r0, #1
	bhi	_038030CC
	ldr	r1, _03803110	;@ =0x0400010E
	ldrh	r0, [r1]
	bic	r0, r0, #128	;@ 0x80
	strh	r0, [r1]
	bl	OS_DisableInterrupts
	mov	r4, r0
	mov	r0, #64	;@ 0x40
	mov	r1, #0
	bl	MIC_SetIrqFunction
	bl	MIC_DisableMultipleInterrupt
	mov	r0, r4
	bl	OS_RestoreInterrupts
	ldr	r0, _03803104	;@ =_03809F6C
	ldr	r0, [r0, #32]
	cmp	r0, #3
	bne	_038030B0
	mov	r0, #66	;@ 0x42
	mov	r1, #0
	bl	SPIi_ReturnResult
	b	_038030BC
_038030B0:
	mov	r0, #81	;@ 0x51
	mov	r1, #0
	bl	SPIi_ReturnResult
_038030BC:
	mov	r1, #0
	ldr	r0, _03803104	;@ =_03809F6C
	str	r1, [r0, #32]
	b	_038030F0
_038030CC:
	cmp	r1, #3
	bne	_038030E4
	mov	r0, #66	;@ 0x42
	mov	r1, #3
	bl	SPIi_ReturnResult
	b	_038030F0
_038030E4:
	mov	r0, #81	;@ 0x51
	mov	r1, #3
	bl	SPIi_ReturnResult
_038030F0:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_038030FC:	.word	0x027FFF94
_03803100:	.word	0x027FFF90
_03803104:	.word	_03809F6C
_03803108:	.word	FUN_03802E7C
_0380310C:	.word	0x0400010C
_03803110:	.word	0x0400010E

	arm_func_start FUN_03803114
FUN_03803114: ;@ 0x03803114
	cmp	r0, #65536	;@ 0x10000
	bcs	_03803138
	mov	r2, #0
	ldr	r1, _038031B4	;@ =_03809F6C
	strh	r2, [r1, #54]	;@ 0x36
	rsb	r0, r0, #65536	;@ 0x10000
	strh	r0, [r1, #52]	;@ 0x34
	mov	r0, #1
	bx	lr
_03803138:
	cmp	r0, #4194304	;@ 0x400000
	bcs	_03803160
	mov	r2, #1
	ldr	r1, _038031B4	;@ =_03809F6C
	strh	r2, [r1, #54]	;@ 0x36
	mov	r0, r0, lsr #6
	rsb	r0, r0, #65536	;@ 0x10000
	strh	r0, [r1, #52]	;@ 0x34
	mov	r0, r2
	bx	lr
_03803160:
	cmp	r0, #16777216	;@ 0x1000000
	bcs	_03803188
	mov	r2, #2
	ldr	r1, _038031B4	;@ =_03809F6C
	strh	r2, [r1, #54]	;@ 0x36
	mov	r0, r0, lsr #8
	rsb	r0, r0, #65536	;@ 0x10000
	strh	r0, [r1, #52]	;@ 0x34
	mov	r0, #1
	bx	lr
_03803188:
	cmp	r0, #67108864	;@ 0x4000000
	movcs	r0, #0
	bxcs	lr
	mov	r2, #3
	ldr	r1, _038031B4	;@ =_03809F6C
	strh	r2, [r1, #54]	;@ 0x36
	mov	r0, r0, lsr #10
	rsb	r0, r0, #65536	;@ 0x10000
	strh	r0, [r1, #52]	;@ 0x34
	mov	r0, #1
	bx	lr
_038031B4:	.word	_03809F6C

	arm_func_start MIC_AnalyzeCommand
MIC_AnalyzeCommand: ;@ 0x038031B8
	stmdb	sp!, {r4, lr}
	ands	r1, r0, #33554432	;@ 0x2000000
	beq	_038031E4
	mov	r4, #0
	mov	r3, r4
	ldr	r1, _03803478	;@ =_03809F6C
_038031D0:
	mov	r2, r4, lsl #1
	strh	r3, [r1, r2]
	add	r4, r4, #1
	cmp	r4, #16
	blt	_038031D0
_038031E4:
	and	r1, r0, #983040	;@ 0xf0000
	mov	r1, r1, lsr #16
	mov	r2, r1, lsl #1
	ldr	r1, _03803478	;@ =_03809F6C
	strh	r0, [r1, r2]
	ands	r0, r0, #16777216	;@ 0x1000000
	beq	_03803470
	ldrh	r3, [r1]
	and	r0, r3, #65280	;@ 0xff00
	mov	r0, r0, lsl #8
	mov	r4, r0, lsr #16
	sub	r0, r4, #64	;@ 0x40
	cmp	r0, #3
	addls	pc, pc, r0, lsl #2
	b	_03803464
	b	_03803230
	b	_03803270
	b	_03803378
	b	_038033DC
_03803230:
	mov	r0, #2
	mov	r1, r4
	mov	r2, #1
	and	r3, r3, #255	;@ 0xff
	bl	SPIi_SetEntry
	cmp	r0, #0
	bne	_03803258
	mov	r0, r4
	mov	r1, #4
	bl	SPIi_ReturnResult
_03803258:
	mov	r1, #0
	ldr	r0, _0380347C	;@ =0x027FFF94
	strh	r1, [r0]
	ldr	r0, _03803480	;@ =0x027FFF90
	str	r1, [r0]
	b	_03803470
_03803270:
	ldr	r0, [r1, #32]
	cmp	r0, #0
	beq	_0380328C
	mov	r0, r4
	mov	r1, #3
	bl	SPIi_ReturnResult
	b	_03803470
_0380328C:
	and	r0, r3, #255	;@ 0xff
	strh	r0, [r1, #36]	;@ 0x24
	ldrh	r2, [r1, #2]
	ldrh	r0, [r1, #4]
	orr	r3, r0, r2, lsl #16
	cmp	r3, #33554432	;@ 0x2000000
	bcc	_038032B0
	cmp	r3, #37748736	;@ 0x2400000
	bcc	_038032C0
_038032B0:
	mov	r0, r4
	mov	r1, #2
	bl	SPIi_ReturnResult
	b	_03803470
_038032C0:
	str	r3, [r1, #40]	;@ 0x28
	ldrh	r2, [r1, #6]
	ldrh	r0, [r1, #8]
	orr	r2, r0, r2, lsl #16
	add	r0, r3, r2
	cmp	r0, #37748736	;@ 0x2400000
	bls	_038032EC
	mov	r0, r4
	mov	r1, #2
	bl	SPIi_ReturnResult
	b	_03803470
_038032EC:
	str	r2, [r1, #48]	;@ 0x30
	ldrh	r2, [r1, #10]
	ldrh	r0, [r1, #12]
	orr	r0, r0, r2, lsl #16
	bl	FUN_03803114
	cmp	r0, #0
	bne	_03803318
	mov	r0, r4
	mov	r1, #2
	bl	SPIi_ReturnResult
	b	_03803470
_03803318:
	mov	r2, #0
	ldr	r0, _03803478	;@ =_03809F6C
	str	r2, [r0, #44]	;@ 0x2c
	ldrh	r1, [r0, #36]	;@ 0x24
	and	r1, r1, #7
	strh	r1, [r0, #38]	;@ 0x26
	mov	r0, #2
	mov	r1, r4
	bl	SPIi_SetEntry
	cmp	r0, #0
	bne	_03803354
	mov	r0, r4
	mov	r1, #4
	bl	SPIi_ReturnResult
	b	_03803470
_03803354:
	mov	r1, #0
	ldr	r0, _0380347C	;@ =0x027FFF94
	strh	r1, [r0]
	ldr	r0, _03803480	;@ =0x027FFF90
	str	r1, [r0]
	mov	r1, #1
	ldr	r0, _03803478	;@ =_03809F6C
	str	r1, [r0, #32]
	b	_03803470
_03803378:
	ldr	r0, [r1, #32]
	cmp	r0, #2
	beq	_03803394
	mov	r0, r4
	mov	r1, #3
	bl	SPIi_ReturnResult
	b	_03803470
_03803394:
	mov	r0, #2
	mov	r1, r4
	mov	r2, #0
	bl	SPIi_SetEntry
	cmp	r0, #0
	bne	_038033BC
	mov	r0, r4
	mov	r1, #4
	bl	SPIi_ReturnResult
	b	_03803470
_038033BC:
	mov	r1, #3
	ldr	r0, _03803478	;@ =_03809F6C
	str	r1, [r0, #32]
	ldr	r1, _03803484	;@ =0x0400010E
	ldrh	r0, [r1]
	bic	r0, r0, #128	;@ 0x80
	strh	r0, [r1]
	b	_03803470
_038033DC:
	ldr	r0, [r1, #32]
	cmp	r0, #2
	beq	_038033F8
	mov	r0, r4
	mov	r1, #3
	bl	SPIi_ReturnResult
	b	_03803470
_038033F8:
	ldrh	r2, [r1, #2]
	ldrh	r0, [r1, #4]
	orr	r0, r0, r2, lsl #16
	bl	FUN_03803114
	cmp	r0, #0
	bne	_03803420
	mov	r0, r4
	mov	r1, #2
	bl	SPIi_ReturnResult
	b	_03803470
_03803420:
	bl	OS_DisableInterrupts
	ldr	ip, _03803484	;@ =0x0400010E
	ldrh	r1, [ip]
	bic	r1, r1, #128	;@ 0x80
	strh	r1, [ip]
	ldr	r1, _03803478	;@ =_03809F6C
	ldrh	r3, [r1, #52]	;@ 0x34
	ldr	r2, _03803488	;@ =0x0400010C
	strh	r3, [r2]
	ldrh	r1, [r1, #54]	;@ 0x36
	orr	r1, r1, #192	;@ 0xc0
	strh	r1, [ip]
	bl	OS_RestoreInterrupts
	mov	r0, r4
	mov	r1, #0
	bl	SPIi_ReturnResult
	b	_03803470
_03803464:
	mov	r0, r4
	mov	r1, #1
	bl	SPIi_ReturnResult
_03803470:
	ldmia	sp!, {r4, lr}
	bx	lr
_03803478:	.word	_03809F6C
_0380347C:	.word	0x027FFF94
_03803480:	.word	0x027FFF90
_03803484:	.word	0x0400010E
_03803488:	.word	0x0400010C

	arm_func_start MIC_Init
MIC_Init: ;@ 0x0380348C
	mov	r3, #0
	ldr	r0, _038034C4	;@ =_03809F6C
	str	r3, [r0, #32]
	mov	r2, r3
_0380349C:
	mov	r1, r3, lsl #1
	strh	r2, [r0, r1]
	add	r3, r3, #1
	cmp	r3, #16
	blt	_0380349C
	ldr	r1, _038034C8	;@ =0x0400010E
	ldrh	r0, [r1]
	bic	r0, r0, #128	;@ 0x80
	strh	r0, [r1]
	bx	lr
_038034C4:	.word	_03809F6C
_038034C8:	.word	0x0400010E

	arm_func_start MIC_ExecSampling12
MIC_ExecSampling12: ;@ 0x038034CC
	ldr	r1, _03803580	;@ =0x040001C0
_038034D0:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038034D0
	ldr	r0, _03803584	;@ =0x00008A01
	strh	r0, [r1]
	mov	r1, #228	;@ 0xe4
	ldr	r0, _03803588	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _03803580	;@ =0x040001C0
_038034F4:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038034F4
	mov	r1, #0
	ldr	r0, _03803588	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r2, _03803580	;@ =0x040001C0
_03803510:
	ldrh	r0, [r2]
	ands	r0, r0, #128	;@ 0x80
	bne	_03803510
	ldr	r1, _03803588	;@ =0x040001C2
	ldrh	r0, [r1]
	and	r0, r0, #255	;@ 0xff
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r0, r0, lsl #24
	mov	r3, r0, lsr #16
	ldr	r0, _0380358C	;@ =0x00008201
	strh	r0, [r2]
	mov	r0, #0
	strh	r0, [r1]
	ldr	r1, _03803580	;@ =0x040001C0
_0380354C:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_0380354C
	ldr	r0, _03803588	;@ =0x040001C2
	ldrh	r0, [r0]
	and	r0, r0, #255	;@ 0xff
	mov	r0, r0, lsl #16
	orr	r1, r3, r0, lsr #16
	ldr	r0, _03803590	;@ =0x00007FF8
	and	r0, r1, r0
	mov	r0, r0, lsl #17
	mov	r0, r0, lsr #16
	bx	lr
_03803580:	.word	0x040001C0
_03803584:	.word	0x00008A01
_03803588:	.word	0x040001C2
_0380358C:	.word	0x00008201
_03803590:	.word	0x00007FF8

	arm_func_start MIC_ExecSampling8
MIC_ExecSampling8: ;@ 0x03803594
	ldr	r1, _03803648	;@ =0x040001C0
_03803598:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03803598
	ldr	r0, _0380364C	;@ =0x00008A01
	strh	r0, [r1]
	mov	r1, #236	;@ 0xec
	ldr	r0, _03803650	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _03803648	;@ =0x040001C0
_038035BC:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038035BC
	mov	r1, #0
	ldr	r0, _03803650	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r2, _03803648	;@ =0x040001C0
_038035D8:
	ldrh	r0, [r2]
	ands	r0, r0, #128	;@ 0x80
	bne	_038035D8
	ldr	r1, _03803650	;@ =0x040001C2
	ldrh	r0, [r1]
	and	r0, r0, #255	;@ 0xff
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r0, r0, lsl #24
	mov	r3, r0, lsr #16
	ldr	r0, _03803654	;@ =0x00008201
	strh	r0, [r2]
	mov	r0, #0
	strh	r0, [r1]
	ldr	r1, _03803648	;@ =0x040001C0
_03803614:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03803614
	ldr	r0, _03803650	;@ =0x040001C2
	ldrh	r0, [r0]
	and	r0, r0, #255	;@ 0xff
	mov	r0, r0, lsl #16
	orr	r1, r3, r0, lsr #16
	ldr	r0, _03803658	;@ =0x00007F80
	and	r0, r1, r0
	mov	r0, r0, lsl #9
	mov	r0, r0, lsr #16
	bx	lr
_03803648:	.word	0x040001C0
_0380364C:	.word	0x00008A01
_03803650:	.word	0x040001C2
_03803654:	.word	0x00008201
_03803658:	.word	0x00007F80
_0380365C:
	mov	ip, #67108864	;@ 0x4000000
	add	r1, ip, #520	;@ 0x208
	ldrh	r0, [r1]
	tst	r0, r0
	bxeq	lr
	ldr	r3, [ip, #528]	;@ 0x210
	ldr	r1, [ip, #532]	;@ 0x214
	ands	r2, r1, r3
	bxeq	lr
	ldr	r0, _038037C8	;@ =0x01DF3FFF
	tst	r2, r0
	streq	r2, [ip, #532]	;@ 0x214
	bxeq	lr
	stmfd	sp!, {lr}
	mrs	r0, SPSR
	stmfd	sp!, {r0}
	stmdb	sp, {sp, lr}^
	sub	sp, sp, #8
	mov	r0, #159	;@ 0x9f
	msr	CPSR_c, r0
	ldr	r1, _038037CC	;@ =OSi_ThreadInfo
	ldrh	r0, [r1, #2]
	add	r0, r0, #1
	strh	r0, [r1, #2]
	ldr	r1, _038037D0	;@ =_03809FA8
	cmp	r0, #1
	moveq	r0, sp
	ldreq	sp, [r1, #4]
	streq	r0, [r1, #4]
	stmfd	sp!, {r3}
	ldr	r1, _038037D4	;@ =_038072C8
	ldr	r0, [r1]
	tst	r0, r2
	strne	r0, [ip, #532]	;@ 0x214
	ldrne	r0, [r1, #4]
	ldrne	r3, _038037D8	;@ =OS_IRQTable
	ldrne	r0, [r3, r0, lsl #2]
	bne	_03803738
	mov	r3, #1
_038036F8:
	ldr	r0, [r1, r3, lsl #3]
	tst	r0, r2
	addeq	r3, r3, #1
	beq	_038036F8
	str	r0, [ip, #532]	;@ 0x214
	add	r0, r1, r3, lsl #3
	ldr	r2, [r0, #4]
	ldr	r3, _038037D8	;@ =OS_IRQTable
	ldr	r0, [r3, r2, lsl #2]
	ldr	r2, _038037CC	;@ =OSi_ThreadInfo
	ldrh	r3, [r2, #2]
	cmp	r3, #1
	ldreq	r2, [r1]
	streq	r2, [ip, #528]	;@ 0x210
	moveq	r2, #31
	msreq	CPSR_c, r2
_03803738:
	ldr	r1, [ip, #528]	;@ 0x210
	stmfd	sp!, {r1}
	adr lr, _03803748
	bx	r0
_03803748:
	mov	r0, #159	;@ 0x9f
	msr	CPSR_c, r0
	mov	ip, #67108864	;@ 0x4000000
	ldmia	sp!, {r0}
	ldr	r1, [ip, #528]	;@ 0x210
	eor	r2, r0, r1
	and	r1, r2, r1
	and	r0, r2, r0
	ldmia	sp!, {r3}
	orr	r3, r3, r1
	bic	r3, r3, r0
	str	r3, [ip, #528]	;@ 0x210
	ldr	r2, _038037CC	;@ =OSi_ThreadInfo
	ldr	r3, _038037D0	;@ =_03809FA8
	ldrh	r0, [r2, #2]
	subs	r1, r0, #1
	strh	r1, [r2, #2]
	moveq	r0, sp
	ldreq	sp, [r3, #4]
	streq	r0, [r3, #4]
	mov	r0, #146	;@ 0x92
	msr	CPSR_c, r0
	ldmia	sp, {sp, lr}^
	nop			;@ (mov r0, r0)
	add	sp, sp, #8
	ldmia	sp!, {r0}
	msr	SPSR_fc, r0
	tst	r1, r1
	ldreq	r0, _038037DC	;@ =OS_IrqHandler_ThreadSwitch
	addeq	lr, pc, #0
	bxeq	r0
	ldmia	sp!, {pc}
_038037C8:	.word	0x01DF3FFF
_038037CC:	.word	OSi_ThreadInfo
_038037D0:	.word	_03809FA8
_038037D4:	.word	_038072C8
_038037D8:	.word	OS_IRQTable
_038037DC:	.word	OS_IrqHandler_ThreadSwitch

	arm_func_start MIC_DisableMultipleInterrupt
MIC_DisableMultipleInterrupt: ;@ 0x038037E0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _03803820	;@ =0x0380FFFC
	ldr	r1, [r0]
	ldr	r0, _03803824	;@ =_0380365C
	cmp	r1, r0
	bne	_03803814
	bl	OS_DisableInterrupts
	ldr	r1, _03803828	;@ =_03809FA8
	ldr	r2, [r1, #12]
	ldr	r1, _03803820	;@ =0x0380FFFC
	str	r2, [r1]
	bl	OS_RestoreInterrupts
_03803814:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03803820:	.word	0x0380FFFC
_03803824:	.word	_0380365C
_03803828:	.word	_03809FA8

	arm_func_start MIC_EnableMultipleInterrupt
MIC_EnableMultipleInterrupt: ;@ 0x0380382C
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _03803888	;@ =0x0380FFFC
	ldr	r2, [r0]
	ldr	r0, _0380388C	;@ =_0380365C
	cmp	r2, r0
	beq	_0380387C
	mov	r1, #0
	ldr	r0, _03803890	;@ =_03809FA8
	str	r1, [r0]
	ldr	r1, _03803894	;@ =0x0380FE80
	str	r1, [r0, #4]
	mov	r1, #64	;@ 0x40
	str	r1, [r0, #8]
	str	r2, [r0, #12]
	bl	OS_DisableInterrupts
	ldr	r2, _0380388C	;@ =_0380365C
	ldr	r1, _03803888	;@ =0x0380FFFC
	str	r2, [r1]
	bl	OS_RestoreInterrupts
_0380387C:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03803888:	.word	0x0380FFFC
_0380388C:	.word	_0380365C
_03803890:	.word	_03809FA8
_03803894:	.word	0x0380FE80

	arm_func_start MIC_SetIrqFunction
MIC_SetIrqFunction: ;@ 0x03803898
	mov	ip, #0
	ldr	r2, _038038BC	;@ =OS_IRQTable
_038038A0:
	ands	r3, r0, #1
	strne	r1, [r2, ip, lsl #2]
	mov	r0, r0, lsr #1
	add	ip, ip, #1
	cmp	ip, #25
	blt	_038038A0
	bx	lr
_038038BC:	.word	OS_IRQTable

	arm_func_start CTRDGi_SendtoPxi
CTRDGi_SendtoPxi: ;@ 0x038038C0
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, #1
	mov	r5, #13
	mov	r4, #0
	b	_038038E4
_038038DC:
	mov	r0, r6
	bl	FUN_037F8CB4
_038038E4:
	mov	r0, r5
	mov	r1, r7
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	bne	_038038DC
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr

	arm_func_start CTRDGi_UnlockByProcessor
CTRDGi_UnlockByProcessor: ;@ 0x03803908
	stmdb	sp!, {r4, lr}
	mov	r4, r1
	ldr	r1, [r4]
	cmp	r1, #0
	bne	_03803920
	bl	OS_UnLockCartridge
_03803920:
	ldr	r0, [r4, #4]
	bl	OS_RestoreInterrupts
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start CTRDGi_LockByProcessor
CTRDGi_LockByProcessor: ;@ 0x03803930
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, r1
	bl	OS_DisableInterrupts
	str	r0, [r4, #4]
	ldr	r0, _0380398C	;@ =0x027FFFE8
	bl	OS_ReadOwnerOfLockWord
	and	r0, r0, #128	;@ 0x80
	str	r0, [r4]
	ldr	r0, [r4]
	cmp	r0, #0
	bne	_03803974
	mov	r0, r5
	bl	OS_TryLockCartridge
	cmp	r0, #0
	bne	_0380397C
_03803974:
	mov	r0, #1
	b	_03803980
_0380397C:
	mov	r0, #0
_03803980:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_0380398C:	.word	0x027FFFE8

	arm_func_start CTRDGi_RestoreAccessCycle
CTRDGi_RestoreAccessCycle: ;@ 0x03803990
	ldr	r3, [r0]
	ldr	r2, _038039C0	;@ =0x04000204
	ldrh	r1, [r2]
	bic	r1, r1, #12
	orr	r1, r1, r3, lsl #2
	strh	r1, [r2]
	ldr	r1, [r0, #4]
	ldrh	r0, [r2]
	bic	r0, r0, #16
	orr	r0, r0, r1, lsl #4
	strh	r0, [r2]
	bx	lr
_038039C0:	.word	0x04000204

	arm_func_start CTRDGi_ChangeLatestAccessCycle
CTRDGi_ChangeLatestAccessCycle: ;@ 0x038039C4
	ldr	r2, _03803A08	;@ =0x04000204
	ldrh	r1, [r2]
	and	r1, r1, #12
	mov	r1, r1, asr #2
	str	r1, [r0]
	ldrh	r1, [r2]
	and	r1, r1, #16
	mov	r1, r1, asr #4
	str	r1, [r0, #4]
	ldrh	r0, [r2]
	bic	r0, r0, #12
	orr	r0, r0, #12
	strh	r0, [r2]
	ldrh	r0, [r2]
	bic	r0, r0, #16
	strh	r0, [r2]
	bx	lr
_03803A08:	.word	0x04000204

	arm_func_start CTRDG_IsExisting
CTRDG_IsExisting: ;@ 0x03803A0C
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #16
	mov	r4, #1
	ldr	r2, _03803B20	;@ =0x027FFC30
	ldrh	r1, [r2]
	ldr	r0, _03803B24	;@ =0x0000FFFF
	cmp	r1, r0
	moveq	r0, #0
	beq	_03803B14
	ldrb	r0, [r2, #5]
	mov	r0, r0, lsl #30
	mov	r0, r0, lsr #31
	cmp	r0, #1
	moveq	r0, #0
	beq	_03803B14
	ldr	r0, _03803B28	;@ =CTRDGi_Work
	ldrh	r0, [r0, #2]
	add	r1, sp, #0
	bl	CTRDGi_LockByProcessor
	cmp	r0, #0
	bne	_03803A70
	ldr	r0, [sp, #4]
	bl	OS_RestoreInterrupts
	mov	r0, r4
	b	_03803B14
_03803A70:
	add	r0, sp, #8
	bl	CTRDGi_ChangeLatestAccessCycle
	mov	r2, #134217728	;@ 0x8000000
	ldrb	r3, [r2, #178]	;@ 0xb2
	cmp	r3, #150	;@ 0x96
	bne	_03803A9C
	ldr	r0, _03803B20	;@ =0x027FFC30
	ldrh	r1, [r0]
	ldrh	r0, [r2, #190]	;@ 0xbe
	cmp	r1, r0
	bne	_03803AE4
_03803A9C:
	cmp	r3, #150	;@ 0x96
	beq	_03803ABC
	ldr	r0, _03803B20	;@ =0x027FFC30
	ldrh	r1, [r0]
	ldr	r0, _03803B2C	;@ =0x0801FFFE
	ldrh	r0, [r0]
	cmp	r1, r0
	bne	_03803AE4
_03803ABC:
	ldr	r2, _03803B20	;@ =0x027FFC30
	ldr	r1, [r2, #8]
	mov	r0, #134217728	;@ 0x8000000
	ldr	r0, [r0, #172]	;@ 0xac
	cmp	r1, r0
	beq	_03803AF8
	ldrb	r0, [r2, #5]
	mov	r0, r0, lsl #31
	movs	r0, r0, lsr #31
	beq	_03803AF8
_03803AE4:
	ldr	r1, _03803B20	;@ =0x027FFC30
	ldrb	r0, [r1, #5]
	orr	r0, r0, #2
	strb	r0, [r1, #5]
	mov	r4, #0
_03803AF8:
	add	r0, sp, #8
	bl	CTRDGi_RestoreAccessCycle
	ldr	r0, _03803B28	;@ =CTRDGi_Work
	ldrh	r0, [r0, #2]
	add	r1, sp, #0
	bl	CTRDGi_UnlockByProcessor
	mov	r0, r4
_03803B14:
	add	sp, sp, #16
	ldmia	sp!, {r4, lr}
	bx	lr
_03803B20:	.word	0x027FFC30
_03803B24:	.word	0x0000FFFF
_03803B28:	.word	CTRDGi_Work
_03803B2C:	.word	0x0801FFFE

	arm_func_start CTRDG_IsPulledOut
CTRDG_IsPulledOut: ;@ 0x03803B30
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r2, _03803B80	;@ =0x027FFC30
	ldrh	r1, [r2]
	ldr	r0, _03803B84	;@ =0x0000FFFF
	cmp	r1, r0
	moveq	r0, #0
	beq	_03803B74
	ldrb	r0, [r2, #5]
	mov	r0, r0, lsl #30
	movs	r0, r0, lsr #31
	bne	_03803B64
	bl	CTRDG_IsExisting
_03803B64:
	ldr	r0, _03803B80	;@ =0x027FFC30
	ldrb	r0, [r0, #5]
	mov	r0, r0, lsl #30
	mov	r0, r0, lsr #31
_03803B74:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03803B80:	.word	0x027FFC30
_03803B84:	.word	0x0000FFFF

	arm_func_start CTRDGi_InitCommon
CTRDGi_InitCommon: ;@ 0x03803B88
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #0
	str	r0, [sp]
	add	r0, sp, #0
	ldr	r1, _03803BC0	;@ =CTRDGi_Work
	ldr	r2, _03803BC4	;@ =0x05000001
	bl	FUN_03803BC8
	bl	OS_GetLockID
	ldr	r1, _03803BC0	;@ =CTRDGi_Work
	strh	r0, [r1, #2]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03803BC0:	.word	CTRDGi_Work
_03803BC4:	.word	0x05000001

	arm_func_start FUN_03803BC8
FUN_03803BC8: ;@ 0x03803BC8
	ldr	ip, _03803BD0	;@ =SVC_CpuSet
	bx	ip
_03803BD0:	.word	SVC_CpuSet

	arm_func_start FUN_03803BD4
FUN_03803BD4: ;@ 0x03803BD4
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	and	r0, r1, #63	;@ 0x3f
	cmp	r0, #3
	bne	_03803C40
	ldr	r0, _03803C50	;@ =0x01FFFFC0
	and	r0, r1, r0
	mov	r2, r0, lsr #6
	ldr	r1, _03803C54	;@ =0x04000204
	ldrh	r0, [r1]
	bic	r0, r0, #96	;@ 0x60
	orr	r0, r0, r2, lsl #5
	strh	r0, [r1]
	mov	r7, #1
	mov	r6, #17
	mov	r5, #18
	mov	r4, #0
	b	_03803C24
_03803C1C:
	mov	r0, r7
	bl	FUN_037F8CB4
_03803C24:
	mov	r0, r6
	mov	r1, r5
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	bne	_03803C1C
	b	_03803C44
_03803C40:
	bl	OS_Terminate
_03803C44:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_03803C50:	.word	0x01FFFFC0
_03803C54:	.word	0x04000204

	arm_func_start FUN_03803C58
FUN_03803C58: ;@ 0x03803C58
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

	arm_func_start CTRDG_CheckPullOut_Polling
CTRDG_CheckPullOut_Polling: ;@ 0x03803C80
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	ldr	r1, _03803D80	;@ =_03807708
	ldr	r3, [r1]
	mvn	r0, #0
	cmp	r3, r0
	ldreq	r0, _03803D84	;@ =0x027FFC3C
	ldreq	r0, [r0]
	addeq	r0, r0, #10
	streq	r0, [r1]
	beq	_03803D74
	ldr	r0, _03803D88	;@ =_03809FCC
	ldr	r0, [r0]
	cmp	r0, #0
	bne	_03803D74
	ldr	r0, _03803D8C	;@ =_03809FC8
	ldr	r0, [r0]
	cmp	r0, #0
	bne	_03803D74
	ldr	r2, _03803D84	;@ =0x027FFC3C
	ldr	r0, [r2]
	cmp	r0, r3
	bcc	_03803D74
	ldr	r0, [r2]
	add	r0, r0, #10
	str	r0, [r1]
	bl	CTRDG_IsPulledOut
	ldr	r1, _03803D8C	;@ =_03809FC8
	str	r0, [r1]
	bl	CTRDG_IsExisting
	cmp	r0, #0
	bne	_03803D28
	ldr	r0, _03803D90	;@ =_03807704
	ldr	r0, [r0]
	cmp	r0, #0
	movne	r1, #1
	ldrne	r0, _03803D88	;@ =_03809FCC
	strne	r1, [r0]
	bne	_03803D74
	mov	r1, #1
	ldr	r0, _03803D8C	;@ =_03809FC8
	str	r1, [r0]
_03803D28:
	mov	r7, #0
	ldr	r0, _03803D90	;@ =_03807704
	str	r7, [r0]
	ldr	r0, _03803D8C	;@ =_03809FC8
	ldr	r0, [r0]
	cmp	r0, #0
	beq	_03803D74
	mov	r6, #100	;@ 0x64
	mov	r5, #13
	mov	r4, #17
	b	_03803D5C
_03803D54:
	mov	r0, r6
	bl	OS_Sleep
_03803D5C:
	mov	r0, r5
	mov	r1, r4
	mov	r2, r7
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	bne	_03803D54
_03803D74:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_03803D80:	.word	_03807708
_03803D84:	.word	0x027FFC3C
_03803D88:	.word	_03809FCC
_03803D8C:	.word	_03809FC8
_03803D90:	.word	_03807704

	arm_func_start FUN_03803D94
FUN_03803D94: ;@ 0x03803D94
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r7, r0
	mov	r0, #134217728	;@ 0x8000000
	add	r6, r0, #4
	mov	r4, #1
	bl	OS_GetLockID
	mov	r0, r0, lsl #16
	mov	r5, r0, lsr #16
	mov	r0, r5
	bl	OS_LockCartridge
	mov	r1, #0
	ldr	r0, _03803E3C	;@ =0x0000FFFF
	eor	r2, r0, #3
	mov	r2, r2, lsl #16
	mov	lr, r2, lsr #16
	eor	r2, r0, #132	;@ 0x84
	mov	r2, r2, lsl #16
	mov	r8, r2, lsr #16
	b	_03803E18
_03803DE0:
	mov	ip, r0
	cmp	r1, #76	;@ 0x4c
	moveq	ip, r8
	beq	_03803DF8
	cmp	r1, #77	;@ 0x4d
	moveq	ip, lr
_03803DF8:
	mov	r3, r1, lsl #1
	ldrh	r2, [r7, r3]
	and	ip, ip, r2
	ldrh	r2, [r6, r3]
	cmp	ip, r2
	movne	r4, #0
	bne	_03803E20
	add	r1, r1, #1
_03803E18:
	cmp	r1, #78	;@ 0x4e
	blt	_03803DE0
_03803E20:
	mov	r0, r5
	bl	OS_UnLockCartridge
	mov	r0, r5
	bl	OS_ReleaseLockID
	mov	r0, r4
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_03803E3C:	.word	0x0000FFFF

	arm_func_start FUN_03803E40
FUN_03803E40: ;@ 0x03803E40
	ldr	r1, _03803E54	;@ =current_vib
	str	r0, [r1]
	ldr	r1, _03803E58	;@ =0x08001000
	strh	r0, [r1]
	bx	lr
_03803E54:	.word	current_vib
_03803E58:	.word	0x08001000

	arm_func_start CTRDG_VibPulseEdgeUpdate
CTRDG_VibPulseEdgeUpdate: ;@ 0x03803E5C
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	movs	r5, r0
	beq	_03803E9C
	ldr	r0, [r5]
	cmp	r0, #0
	bne	_03803E9C
	ldr	r0, [r5, #68]	;@ 0x44
	add	r0, r0, #1
	str	r0, [r5, #68]	;@ 0x44
	ldr	r1, [r5, #64]	;@ 0x40
	cmp	r1, #0
	beq	_03803E9C
	ldr	r0, [r5, #68]	;@ 0x44
	cmp	r0, r1
	movhi	r5, #0
_03803E9C:
	cmp	r5, #0
	beq	_03803EB0
	ldr	r0, [r5, #60]	;@ 0x3c
	cmp	r0, #0
	bne	_03803F48
_03803EB0:
	bl	OS_DisableInterrupts
	mov	r9, r0
	ldr	r0, _03804068	;@ =current_vib
	ldr	r0, [r0]
	cmp	r0, #2
	bne	_03803F34
	mov	r8, #0
	ldr	r7, _0380406C	;@ =0x027FFFE8
	ldr	r4, _03804070	;@ =_03809FBC
	ldr	fp, _03804074	;@ =0x000080E8
	mov	r6, r8
	mov	r5, #1
	b	_03803F2C
_03803EE4:
	mov	r0, r7
	bl	OS_ReadOwnerOfLockWord
	ands	sl, r0, #128	;@ 0x80
	bne	_03803F04
	ldrh	r0, [r4]
	bl	OS_TryLockCartridge
	cmp	r0, #0
	bne	_03803F24
_03803F04:
	mov	r0, r6
	bl	FUN_03803E40
	mov	r8, r5
	cmp	sl, #0
	bne	_03803F2C
	ldrh	r0, [r4]
	bl	OS_UnlockCartridge
	b	_03803F2C
_03803F24:
	mov	r0, fp
	bl	OS_SpinWait
_03803F2C:
	cmp	r8, #0
	beq	_03803EE4
_03803F34:
	ldr	r0, _03804078	;@ =_03809FEC
	bl	OS_CancelAlarm
	mov	r0, r9
	bl	OS_RestoreInterrupts
	b	_0380405C
_03803F48:
	cmp	r5, #0
	beq	_0380405C
	ldr	r0, _0380406C	;@ =0x027FFFE8
	bl	OS_ReadOwnerOfLockWord
	ands	r4, r0, #128	;@ 0x80
	bne	_03803F74
	ldr	r0, _03804070	;@ =_03809FBC
	ldrh	r0, [r0]
	bl	OS_TryLockCartridge
	cmp	r0, #0
	bne	_03804044
_03803F74:
	ldr	r1, [r5]
	ldr	r0, [r5, #4]
	cmp	r1, r0
	bne	_03803FB0
	mov	r0, #0
	bl	FUN_03803E40
	str	r5, [sp]
	ldr	r0, _03804078	;@ =_03809FEC
	ldr	r1, [r5, #8]
	mov	r2, #0
	ldr	r3, _0380407C	;@ =CTRDG_VibPulseEdgeUpdate
	bl	OS_SetAlarm
	mov	r0, #0
	str	r0, [r5]
	b	_0380402C
_03803FB0:
	ands	r0, r1, #1
	beq	_03803FF4
	mov	r0, #0
	bl	FUN_03803E40
	str	r5, [sp]
	ldr	r0, _03804078	;@ =_03809FEC
	ldr	r1, [r5]
	mov	r1, r1, lsr #1
	add	r1, r5, r1, lsl #2
	ldr	r1, [r1, #36]	;@ 0x24
	mov	r2, #0
	ldr	r3, _0380407C	;@ =CTRDG_VibPulseEdgeUpdate
	bl	OS_SetAlarm
	ldr	r0, [r5]
	add	r0, r0, #1
	str	r0, [r5]
	b	_0380402C
_03803FF4:
	mov	r0, #2
	bl	FUN_03803E40
	str	r5, [sp]
	ldr	r0, _03804078	;@ =_03809FEC
	ldr	r1, [r5]
	mov	r1, r1, lsr #1
	add	r1, r5, r1, lsl #2
	ldr	r1, [r1, #12]
	mov	r2, #0
	ldr	r3, _0380407C	;@ =CTRDG_VibPulseEdgeUpdate
	bl	OS_SetAlarm
	ldr	r0, [r5]
	add	r0, r0, #1
	str	r0, [r5]
_0380402C:
	cmp	r4, #0
	bne	_0380405C
	ldr	r0, _03804070	;@ =_03809FBC
	ldrh	r0, [r0]
	bl	OS_UnlockCartridge
	b	_0380405C
_03804044:
	str	r5, [sp]
	ldr	r0, _03804078	;@ =_03809FEC
	ldr	r1, _03804080	;@ =0x0000020B
	mov	r2, #0
	ldr	r3, _0380407C	;@ =CTRDG_VibPulseEdgeUpdate
	bl	OS_SetAlarm
_0380405C:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_03804068:	.word	current_vib
_0380406C:	.word	0x027FFFE8
_03804070:	.word	_03809FBC
_03804074:	.word	0x000080E8
_03804078:	.word	_03809FEC
_0380407C:	.word	CTRDG_VibPulseEdgeUpdate
_03804080:	.word	0x0000020B
_03804084:
	mov	r0, r1
	ldr	ip, _03804090	;@ =CTRDG_VibPulseEdgeUpdate
	bx	ip
_03804090:	.word	CTRDG_VibPulseEdgeUpdate

	arm_func_start FUN_03804094
FUN_03804094: ;@ 0x03804094
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	and	r0, r1, #63	;@ 0x3f
	cmp	r0, #2
	bne	_038040B0
	bl	FUN_03803C58
	b	_038040B4
_038040B0:
	bl	OS_Terminate
_038040B4:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start FUN_038040C0
FUN_038040C0: ;@ 0x038040C0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	and	r0, r1, #63	;@ 0x3f
	cmp	r0, #1
	ldreq	r0, _038040F4	;@ =_03809FD4
	streq	r1, [r0]
	moveq	r1, #1
	streq	r1, [r0, #16]
	beq	_038040E8
	bl	OS_Terminate
_038040E8:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_038040F4:	.word	_03809FD4

	arm_func_start CTRDGi_InitModuleInfo
CTRDGi_InitModuleInfo: ;@ 0x038040F8
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	ldr	r0, _038041C8	;@ =_03809FC4
	ldr	r1, [r0]
	cmp	r1, #0
	bne	_038041BC
	mov	r1, #1
	str	r1, [r0]
	ldr	r0, _038041CC	;@ =0x04000300
	ldrh	r0, [r0]
	ands	r0, r0, #1
	beq	_038041BC
	mov	r0, #262144	;@ 0x40000
	bl	OS_SetIrqMask
	mov	r5, r0
	ldr	r1, _038041D0	;@ =0x04000208
	ldrh	r4, [r1]
	mov	r0, #1
	strh	r0, [r1]
	mov	r7, #256	;@ 0x100
	ldr	r6, _038041D4	;@ =_03809FD4
	b	_03804158
_03804150:
	mov	r0, r7
	bl	FUN_037F8CB4
_03804158:
	ldr	r0, [r6, #16]
	cmp	r0, #1
	bne	_03804150
	ldr	r1, [r6]
	ldr	r0, _038041D8	;@ =0x01FFFFC0
	and	r0, r1, r0
	mov	r0, r0, lsr #6
	mov	r0, r0, lsl #5
	add	r0, r0, #33554432	;@ 0x2000000
	add	r0, r0, #4
	bl	FUN_03803D94
	ldr	r2, _038041DC	;@ =0x027FFC30
	ldrb	r1, [r2, #5]
	bic	r1, r1, #1
	and	r0, r0, #255	;@ 0xff
	and	r0, r0, #1
	orr	r0, r1, r0
	strb	r0, [r2, #5]
	mov	r0, #1
	bl	CTRDGi_SendtoPxi
	ldr	r1, _038041D0	;@ =0x04000208
	ldrh	r0, [r1]
	strh	r4, [r1]
	mov	r0, r5
	bl	OS_SetIrqMask
_038041BC:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_038041C8:	.word	_03809FC4
_038041CC:	.word	0x04000300
_038041D0:	.word	0x04000208
_038041D4:	.word	_03809FD4
_038041D8:	.word	0x01FFFFC0
_038041DC:	.word	0x027FFC30

	arm_func_start CTRDG_Init
CTRDG_Init: ;@ 0x038041E0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	bl	OS_InitTick
	bl	OS_InitAlarm
	ldr	r0, _03804270	;@ =_03809FEC
	bl	OS_CreateAlarm
	ldr	r0, _03804274	;@ =_03809FD0
	ldr	r1, [r0]
	cmp	r1, #0
	bne	_03804264
	mov	r1, #1
	str	r1, [r0]
	bl	CTRDGi_InitCommon
	bl	OS_GetLockID
	mvn	r1, #2
	cmp	r0, r1
	beq	_03804264
	ldr	r1, _03804278	;@ =_03809FBC
	strh	r0, [r1]
	bl	PXI_Init
	mov	r0, #13
	ldr	r1, _0380427C	;@ =FUN_038040C0
	bl	PXI_SetFifoRecvCallback
	bl	CTRDGi_InitModuleInfo
	mov	r0, #13
	ldr	r1, _03804280	;@ =FUN_03804094
	bl	PXI_SetFifoRecvCallback
	mov	r0, #16
	ldr	r1, _03804284	;@ =_03804084
	bl	PXI_SetFifoRecvCallback
	mov	r0, #17
	ldr	r1, _03804288	;@ =FUN_03803BD4
	bl	PXI_SetFifoRecvCallback
_03804264:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03804270:	.word	_03809FEC
_03804274:	.word	_03809FD0
_03804278:	.word	_03809FBC
_0380427C:	.word	FUN_038040C0
_03804280:	.word	FUN_03804094
_03804284:	.word	_03804084
_03804288:	.word	FUN_03803BD4

	arm_func_start FUN_0380428C
FUN_0380428C: ;@ 0x0380428C
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	add	r0, sp, #0
	bl	NVRAM_ReadStatusRegister
	ldrh	r1, [sp]
	ands	r0, r1, #1
	movne	r0, #0
	bne	_038042B8
	ands	r0, r1, #2
	movne	r0, #1
	moveq	r0, #0
_038042B8:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start FUN_038042C4
FUN_038042C4: ;@ 0x038042C4
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	add	r0, sp, #0
	bl	NVRAM_ReadStatusRegister
	ldrh	r0, [sp]
	ands	r0, r0, #1
	moveq	r0, #1
	movne	r0, #0
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start NVRAM_ExecuteProcess
NVRAM_ExecuteProcess: ;@ 0x038042F0
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r4, r0
	bl	OS_DisableInterrupts
	mov	r5, r0
	mov	r0, #1
	bl	SPIi_CheckException
	cmp	r0, #0
	bne	_03804334
	mov	r0, r5
	bl	OS_RestoreInterrupts
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #4
	bl	SPIi_ReturnResult
	b	_038045C0
_03804334:
	mov	r0, #1
	bl	SPIi_GetException
	mov	r0, r5
	bl	OS_RestoreInterrupts
	ldr	r0, [r4, #4]
	sub	r0, r0, #32
	cmp	r0, #13
	addls	pc, pc, r0, lsl #2
	b	_03804584
	b	_03804390
	b	_03804398
	b	_038043A0
	b	_038043AC
	b	_038043EC
	b	_0380442C
	b	_03804474
	b	_038044BC
	b	_038044F4
	b	_0380452C
	b	_03804534
	b	_0380453C
	b	_03804570
	b	_0380457C
_03804390:
	bl	NVRAM_WriteEnable
	b	_038045A4
_03804398:
	bl	NVRAM_WriteDisable
	b	_038045A4
_038043A0:
	ldr	r0, [r4, #16]
	bl	NVRAM_ReadStatusRegister
	b	_038045A4
_038043AC:
	bl	FUN_038042C4
	cmp	r0, #0
	bne	_038043D8
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
	mov	r0, #1
	bl	SPIi_ReleaseException
	b	_038045C0
_038043D8:
	ldr	r0, [r4, #8]
	ldr	r1, [r4, #12]
	ldr	r2, [r4, #16]
	bl	NVRAM_ReadDataBytes
	b	_038045A4
_038043EC:
	bl	FUN_038042C4
	cmp	r0, #0
	bne	_03804418
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
	mov	r0, #1
	bl	SPIi_ReleaseException
	b	_038045C0
_03804418:
	ldr	r0, [r4, #8]
	ldr	r1, [r4, #12]
	ldr	r2, [r4, #16]
	bl	NVRAM_ReadDataBytesAtHigherSpeed
	b	_038045A4
_0380442C:
	bl	FUN_0380428C
	cmp	r0, #0
	bne	_03804458
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
	mov	r0, #1
	bl	SPIi_ReleaseException
	b	_038045C0
_03804458:
	ldr	r0, [r4, #8]
	ldr	r1, [r4, #12]
	mov	r1, r1, lsl #16
	mov	r1, r1, lsr #16
	ldr	r2, [r4, #16]
	bl	NVRAM_PageWrite
	b	_038045A4
_03804474:
	bl	FUN_0380428C
	cmp	r0, #0
	bne	_038044A0
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
	mov	r0, #1
	bl	SPIi_ReleaseException
	b	_038045C0
_038044A0:
	ldr	r0, [r4, #8]
	ldr	r1, [r4, #12]
	mov	r1, r1, lsl #16
	mov	r1, r1, lsr #16
	ldr	r2, [r4, #16]
	bl	NVRAM_PageProgram
	b	_038045A4
_038044BC:
	bl	FUN_0380428C
	cmp	r0, #0
	bne	_038044E8
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
	mov	r0, #1
	bl	SPIi_ReleaseException
	b	_038045C0
_038044E8:
	ldr	r0, [r4, #8]
	bl	NVRAM_PageErase
	b	_038045A4
_038044F4:
	bl	FUN_0380428C
	cmp	r0, #0
	bne	_03804520
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
	mov	r0, #1
	bl	SPIi_ReleaseException
	b	_038045C0
_03804520:
	ldr	r0, [r4, #8]
	bl	NVRAM_SectorErase
	b	_038045A4
_0380452C:
	bl	NVRAM_DeepPowerDown
	b	_038045A4
_03804534:
	bl	NVRAM_ReleaseFromDeepPowerDown
	b	_038045A4
_0380453C:
	bl	FUN_0380428C
	cmp	r0, #0
	bne	_03804568
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
	mov	r0, #1
	bl	SPIi_ReleaseException
	b	_038045C0
_03804568:
	bl	NVRAM_ChipErase
	b	_038045A4
_03804570:
	ldr	r0, [r4, #16]
	bl	NVRAM_ReadSiliconId
	b	_038045A4
_0380457C:
	bl	NVRAM_SoftwareReset
	b	_038045A4
_03804584:
	mov	r0, #1
	bl	SPIi_ReleaseException
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #1
	bl	SPIi_ReturnResult
	b	_038045C0
_038045A4:
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #0
	bl	SPIi_ReturnResult
	mov	r0, #1
	bl	SPIi_ReleaseException
_038045C0:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start NVRAM_AnalyzeCommand
NVRAM_AnalyzeCommand: ;@ 0x038045CC
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #12
	ands	r1, r0, #33554432	;@ 0x2000000
	beq	_038045FC
	mov	r5, #0
	mov	lr, r5
	ldr	r1, _0380476C	;@ =_0380A018
_038045E8:
	mov	r4, r5, lsl #1
	strh	lr, [r1, r4]
	add	r5, r5, #1
	cmp	r5, #16
	blt	_038045E8
_038045FC:
	and	r1, r0, #983040	;@ 0xf0000
	mov	r1, r1, lsr #16
	mov	r4, r1, lsl #1
	ldr	r1, _0380476C	;@ =_0380A018
	strh	r0, [r1, r4]
	ands	r0, r0, #16777216	;@ 0x1000000
	beq	_03804760
	ldrh	r0, [r1]
	and	r4, r0, #65280	;@ 0xff00
	mov	r4, r4, lsl #8
	mov	r4, r4, lsr #16
	sub	lr, r4, #34	;@ 0x22
	cmp	lr, #10
	addls	pc, pc, lr, lsl #2
	b	_03804734
	b	_03804664
	b	_038046A0
	b	_038046A0
	b	_038046E8
	b	_038046E8
	b	_03804728
	b	_03804728
	b	_03804734
	b	_03804734
	b	_03804734
	b	_03804664
_03804664:
	ldrh	ip, [r1, #4]
	and	lr, ip, #65280	;@ 0xff00
	and	r0, r0, #255	;@ 0xff
	mov	ip, r0, lsl #24
	ldrh	r0, [r1, #2]
	orr	r0, ip, r0, lsl #8
	orr	ip, r0, lr, lsr #8
	cmp	ip, #33554432	;@ 0x2000000
	bcc	_03804690
	cmp	ip, #41943040	;@ 0x2800000
	bcc	_03804734
_03804690:
	mov	r0, r4
	mov	r1, #2
	bl	SPIi_ReturnResult
	b	_03804760
_038046A0:
	ldrh	r3, [r1, #8]
	ldrh	r2, [r1, #10]
	orr	ip, r2, r3, lsl #16
	cmp	ip, #33554432	;@ 0x2000000
	bcc	_038046BC
	cmp	ip, #41943040	;@ 0x2800000
	bcc	_038046CC
_038046BC:
	mov	r0, r4
	mov	r1, #2
	bl	SPIi_ReturnResult
	b	_03804760
_038046CC:
	and	r2, r0, #255	;@ 0xff
	ldrh	r0, [r1, #2]
	orr	r3, r0, r2, lsl #16
	ldrh	r2, [r1, #4]
	ldrh	r0, [r1, #6]
	orr	r2, r0, r2, lsl #16
	b	_03804734
_038046E8:
	ldrh	r3, [r1, #6]
	ldrh	r2, [r1, #8]
	orr	ip, r2, r3, lsl #16
	cmp	ip, #33554432	;@ 0x2000000
	bcc	_03804704
	cmp	ip, #41943040	;@ 0x2800000
	bcc	_03804714
_03804704:
	mov	r0, r4
	mov	r1, #2
	bl	SPIi_ReturnResult
	b	_03804760
_03804714:
	and	r2, r0, #255	;@ 0xff
	ldrh	r0, [r1, #2]
	orr	r3, r0, r2, lsl #16
	ldrh	r2, [r1, #4]
	b	_03804734
_03804728:
	and	r3, r0, #255	;@ 0xff
	ldrh	r0, [r1, #2]
	orr	r3, r0, r3, lsl #16
_03804734:
	str	r2, [sp]
	str	ip, [sp, #4]
	mov	r0, #1
	mov	r1, r4
	mov	r2, #3
	bl	SPIi_SetEntry
	cmp	r0, #0
	bne	_03804760
	mov	r0, r4
	mov	r1, #4
	bl	SPIi_ReturnResult
_03804760:
	add	sp, sp, #12
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_0380476C:	.word	_0380A018

	arm_func_start NVRAM_Init
NVRAM_Init: ;@ 0x03804770
	mov	r3, #0
	mov	r2, r3
	ldr	r0, _03804794	;@ =_0380A018
_0380477C:
	mov	r1, r3, lsl #1
	strh	r2, [r0, r1]
	add	r3, r3, #1
	cmp	r3, #16
	blt	_0380477C
	bx	lr
_03804794:	.word	_0380A018

	arm_func_start NVRAM_SoftwareReset
NVRAM_SoftwareReset: ;@ 0x03804798
	ldr	r1, _038047D0	;@ =0x040001C0
_0380479C:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_0380479C
	mov	r0, #33024	;@ 0x8100
	strh	r0, [r1]
	mov	r1, #255	;@ 0xff
	ldr	r0, _038047D4	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _038047D0	;@ =0x040001C0
_038047C0:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038047C0
	bx	lr
_038047D0:	.word	0x040001C0
_038047D4:	.word	0x040001C2

	arm_func_start NVRAM_ReadSiliconId
NVRAM_ReadSiliconId: ;@ 0x038047D8
	ldr	r2, _0380486C	;@ =0x040001C0
_038047DC:
	ldrh	r1, [r2]
	ands	r1, r1, #128	;@ 0x80
	bne	_038047DC
	mov	r1, #35072	;@ 0x8900
	strh	r1, [r2]
	mov	r2, #159	;@ 0x9f
	ldr	r1, _03804870	;@ =0x040001C2
	strh	r2, [r1]
	ldr	r2, _0380486C	;@ =0x040001C0
_03804800:
	ldrh	r1, [r2]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804800
	mov	r2, #0
	ldr	r1, _03804870	;@ =0x040001C2
	strh	r2, [r1]
	ldr	r3, _0380486C	;@ =0x040001C0
_0380481C:
	ldrh	r1, [r3]
	ands	r1, r1, #128	;@ 0x80
	bne	_0380481C
	ldr	r2, _03804870	;@ =0x040001C2
	ldrh	r1, [r2]
	and	r1, r1, #255	;@ 0xff
	strb	r1, [r0]
	mov	r1, #33024	;@ 0x8100
	strh	r1, [r3]
	mov	r1, #0
	strh	r1, [r2]
	ldr	r2, _0380486C	;@ =0x040001C0
_0380484C:
	ldrh	r1, [r2]
	ands	r1, r1, #128	;@ 0x80
	bne	_0380484C
	ldr	r1, _03804870	;@ =0x040001C2
	ldrh	r1, [r1]
	and	r1, r1, #255	;@ 0xff
	strb	r1, [r0, #1]
	bx	lr
_0380486C:	.word	0x040001C0
_03804870:	.word	0x040001C2

	arm_func_start NVRAM_ChipErase
NVRAM_ChipErase: ;@ 0x03804874
	ldr	r1, _038048AC	;@ =0x040001C0
_03804878:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804878
	mov	r0, #33024	;@ 0x8100
	strh	r0, [r1]
	mov	r1, #199	;@ 0xc7
	ldr	r0, _038048B0	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _038048AC	;@ =0x040001C0
_0380489C:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_0380489C
	bx	lr
_038048AC:	.word	0x040001C0
_038048B0:	.word	0x040001C2

	arm_func_start NVRAM_ReleaseFromDeepPowerDown
NVRAM_ReleaseFromDeepPowerDown: ;@ 0x038048B4
	ldr	r1, _038048EC	;@ =0x040001C0
_038048B8:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038048B8
	mov	r0, #33024	;@ 0x8100
	strh	r0, [r1]
	mov	r1, #171	;@ 0xab
	ldr	r0, _038048F0	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _038048EC	;@ =0x040001C0
_038048DC:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038048DC
	bx	lr
_038048EC:	.word	0x040001C0
_038048F0:	.word	0x040001C2

	arm_func_start NVRAM_DeepPowerDown
NVRAM_DeepPowerDown: ;@ 0x038048F4
	ldr	r1, _0380492C	;@ =0x040001C0
_038048F8:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038048F8
	mov	r0, #33024	;@ 0x8100
	strh	r0, [r1]
	mov	r1, #185	;@ 0xb9
	ldr	r0, _03804930	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _0380492C	;@ =0x040001C0
_0380491C:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_0380491C
	bx	lr
_0380492C:	.word	0x040001C0
_03804930:	.word	0x040001C2

	arm_func_start NVRAM_SectorErase
NVRAM_SectorErase: ;@ 0x03804934
	and	r1, r0, #16711680	;@ 0xff0000
	mov	r1, r1, lsr #16
	mov	r1, r1, lsl #16
	mov	r2, r1, lsr #16
	and	r1, r0, #65280	;@ 0xff00
	mov	r1, r1, lsl #8
	mov	r1, r1, lsr #16
	and	r0, r0, #255	;@ 0xff
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	ldr	ip, _038049F0	;@ =0x040001C0
_03804960:
	ldrh	r3, [ip]
	ands	r3, r3, #128	;@ 0x80
	bne	_03804960
	mov	r3, #35072	;@ 0x8900
	strh	r3, [ip]
	mov	ip, #216	;@ 0xd8
	ldr	r3, _038049F4	;@ =0x040001C2
	strh	ip, [r3]
	ldr	ip, _038049F0	;@ =0x040001C0
_03804984:
	ldrh	r3, [ip]
	ands	r3, r3, #128	;@ 0x80
	bne	_03804984
	and	r3, r2, #255	;@ 0xff
	ldr	r2, _038049F4	;@ =0x040001C2
	strh	r3, [r2]
	ldr	r3, _038049F0	;@ =0x040001C0
_038049A0:
	ldrh	r2, [r3]
	ands	r2, r2, #128	;@ 0x80
	bne	_038049A0
	and	r2, r1, #255	;@ 0xff
	ldr	r1, _038049F4	;@ =0x040001C2
	strh	r2, [r1]
	ldr	r2, _038049F0	;@ =0x040001C0
_038049BC:
	ldrh	r1, [r2]
	ands	r1, r1, #128	;@ 0x80
	bne	_038049BC
	mov	r1, #33024	;@ 0x8100
	strh	r1, [r2]
	and	r1, r0, #255	;@ 0xff
	ldr	r0, _038049F4	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _038049F0	;@ =0x040001C0
_038049E0:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038049E0
	bx	lr
_038049F0:	.word	0x040001C0
_038049F4:	.word	0x040001C2

	arm_func_start NVRAM_PageErase
NVRAM_PageErase: ;@ 0x038049F8
	and	r1, r0, #16711680	;@ 0xff0000
	mov	r1, r1, lsr #16
	mov	r1, r1, lsl #16
	mov	r2, r1, lsr #16
	and	r1, r0, #65280	;@ 0xff00
	mov	r1, r1, lsl #8
	mov	r1, r1, lsr #16
	and	r0, r0, #255	;@ 0xff
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	ldr	ip, _03804AB4	;@ =0x040001C0
_03804A24:
	ldrh	r3, [ip]
	ands	r3, r3, #128	;@ 0x80
	bne	_03804A24
	mov	r3, #35072	;@ 0x8900
	strh	r3, [ip]
	mov	ip, #219	;@ 0xdb
	ldr	r3, _03804AB8	;@ =0x040001C2
	strh	ip, [r3]
	ldr	ip, _03804AB4	;@ =0x040001C0
_03804A48:
	ldrh	r3, [ip]
	ands	r3, r3, #128	;@ 0x80
	bne	_03804A48
	and	r3, r2, #255	;@ 0xff
	ldr	r2, _03804AB8	;@ =0x040001C2
	strh	r3, [r2]
	ldr	r3, _03804AB4	;@ =0x040001C0
_03804A64:
	ldrh	r2, [r3]
	ands	r2, r2, #128	;@ 0x80
	bne	_03804A64
	and	r2, r1, #255	;@ 0xff
	ldr	r1, _03804AB8	;@ =0x040001C2
	strh	r2, [r1]
	ldr	r2, _03804AB4	;@ =0x040001C0
_03804A80:
	ldrh	r1, [r2]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804A80
	mov	r1, #33024	;@ 0x8100
	strh	r1, [r2]
	and	r1, r0, #255	;@ 0xff
	ldr	r0, _03804AB8	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _03804AB4	;@ =0x040001C0
_03804AA4:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804AA4
	bx	lr
_03804AB4:	.word	0x040001C0
_03804AB8:	.word	0x040001C2

	arm_func_start NVRAM_PageProgram
NVRAM_PageProgram: ;@ 0x03804ABC
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	cmp	r1, #1
	bcc	_03804BD4
	add	r3, r0, r1
	sub	r3, r3, #1
	mov	r3, r3, lsr #8
	cmp	r3, r0, lsr #8
	andhi	r1, r0, #255	;@ 0xff
	rsbhi	r1, r1, #256	;@ 0x100
	movhi	r1, r1, lsl #16
	movhi	r1, r1, lsr #16
	and	r3, r0, #16711680	;@ 0xff0000
	mov	r3, r3, lsr #16
	strh	r3, [sp]
	and	r3, r0, #65280	;@ 0xff00
	mov	r3, r3, lsr #8
	strh	r3, [sp, #2]
	and	r0, r0, #255	;@ 0xff
	strh	r0, [sp, #4]
	ldr	r3, _03804BE0	;@ =0x040001C0
_03804B10:
	ldrh	r0, [r3]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804B10
	mov	r0, #35072	;@ 0x8900
	strh	r0, [r3]
	mov	r0, #2
	ldr	lr, _03804BE4	;@ =0x040001C2
	strh	r0, [lr]
	mov	r4, #0
	add	r3, sp, #0
	ldr	ip, _03804BE0	;@ =0x040001C0
_03804B3C:
	ldrh	r0, [ip]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804B3C
	mov	r0, r4, lsl #1
	ldrh	r0, [r3, r0]
	and	r0, r0, #255	;@ 0xff
	strh	r0, [lr]
	add	r4, r4, #1
	cmp	r4, #3
	blt	_03804B3C
	mov	ip, #0
	sub	lr, r1, #1
	ldr	r3, _03804BE0	;@ =0x040001C0
	ldr	r0, _03804BE4	;@ =0x040001C2
	b	_03804B94
_03804B78:
	ldrh	r1, [r3]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804B78
	ldrb	r1, [r2, ip]
	and	r1, r1, #255	;@ 0xff
	strh	r1, [r0]
	add	ip, ip, #1
_03804B94:
	cmp	ip, lr
	blt	_03804B78
	ldr	r1, _03804BE0	;@ =0x040001C0
_03804BA0:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804BA0
	mov	r0, #33024	;@ 0x8100
	strh	r0, [r1]
	ldrb	r0, [r2, ip]
	and	r1, r0, #255	;@ 0xff
	ldr	r0, _03804BE4	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _03804BE0	;@ =0x040001C0
_03804BC8:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804BC8
_03804BD4:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_03804BE0:	.word	0x040001C0
_03804BE4:	.word	0x040001C2

	arm_func_start NVRAM_PageWrite
NVRAM_PageWrite: ;@ 0x03804BE8
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	cmp	r1, #1
	bcc	_03804D00
	add	r3, r0, r1
	sub	r3, r3, #1
	mov	r3, r3, lsr #8
	cmp	r3, r0, lsr #8
	andhi	r1, r0, #255	;@ 0xff
	rsbhi	r1, r1, #256	;@ 0x100
	movhi	r1, r1, lsl #16
	movhi	r1, r1, lsr #16
	and	r3, r0, #16711680	;@ 0xff0000
	mov	r3, r3, lsr #16
	strh	r3, [sp]
	and	r3, r0, #65280	;@ 0xff00
	mov	r3, r3, lsr #8
	strh	r3, [sp, #2]
	and	r0, r0, #255	;@ 0xff
	strh	r0, [sp, #4]
	ldr	r3, _03804D0C	;@ =0x040001C0
_03804C3C:
	ldrh	r0, [r3]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804C3C
	mov	r0, #35072	;@ 0x8900
	strh	r0, [r3]
	mov	r0, #10
	ldr	lr, _03804D10	;@ =0x040001C2
	strh	r0, [lr]
	mov	r4, #0
	add	r3, sp, #0
	ldr	ip, _03804D0C	;@ =0x040001C0
_03804C68:
	ldrh	r0, [ip]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804C68
	mov	r0, r4, lsl #1
	ldrh	r0, [r3, r0]
	and	r0, r0, #255	;@ 0xff
	strh	r0, [lr]
	add	r4, r4, #1
	cmp	r4, #3
	blt	_03804C68
	mov	ip, #0
	sub	lr, r1, #1
	ldr	r3, _03804D0C	;@ =0x040001C0
	ldr	r0, _03804D10	;@ =0x040001C2
	b	_03804CC0
_03804CA4:
	ldrh	r1, [r3]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804CA4
	ldrb	r1, [r2, ip]
	and	r1, r1, #255	;@ 0xff
	strh	r1, [r0]
	add	ip, ip, #1
_03804CC0:
	cmp	ip, lr
	blt	_03804CA4
	ldr	r1, _03804D0C	;@ =0x040001C0
_03804CCC:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804CCC
	mov	r0, #33024	;@ 0x8100
	strh	r0, [r1]
	ldrb	r0, [r2, ip]
	and	r1, r0, #255	;@ 0xff
	ldr	r0, _03804D10	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _03804D0C	;@ =0x040001C0
_03804CF4:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804CF4
_03804D00:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_03804D0C:	.word	0x040001C0
_03804D10:	.word	0x040001C2

	arm_func_start NVRAM_ReadDataBytesAtHigherSpeed
NVRAM_ReadDataBytesAtHigherSpeed: ;@ 0x03804D14
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	cmp	r1, #1
	bcc	_03804E3C
	and	r3, r0, #16711680	;@ 0xff0000
	mov	r3, r3, lsr #16
	strh	r3, [sp]
	and	r3, r0, #65280	;@ 0xff00
	mov	r3, r3, lsr #8
	strh	r3, [sp, #2]
	and	r0, r0, #255	;@ 0xff
	strh	r0, [sp, #4]
	ldr	r3, _03804E48	;@ =0x040001C0
_03804D48:
	ldrh	r0, [r3]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804D48
	mov	r0, #35072	;@ 0x8900
	strh	r0, [r3]
	mov	r0, #11
	ldr	ip, _03804E4C	;@ =0x040001C2
	strh	r0, [ip]
	mov	lr, #0
	add	r3, sp, #0
	ldr	r4, _03804E48	;@ =0x040001C0
_03804D74:
	ldrh	r0, [r4]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804D74
	mov	r0, lr, lsl #1
	ldrh	r0, [r3, r0]
	and	r0, r0, #255	;@ 0xff
	strh	r0, [ip]
	add	lr, lr, #1
	cmp	lr, #3
	blt	_03804D74
	ldr	r3, _03804E48	;@ =0x040001C0
_03804DA0:
	ldrh	r0, [r3]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804DA0
	mov	r3, #0
	ldr	r0, _03804E4C	;@ =0x040001C2
	strh	r3, [r0]
	ldr	r3, _03804E48	;@ =0x040001C0
_03804DBC:
	ldrh	r0, [r3]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804DBC
	mov	r0, #0
	ldr	ip, _03804E48	;@ =0x040001C0
	mov	r4, r0
	ldr	lr, _03804E4C	;@ =0x040001C2
	sub	r1, r1, #1
	b	_03804E00
_03804DE0:
	strh	r4, [lr]
_03804DE4:
	ldrh	r3, [ip]
	ands	r3, r3, #128	;@ 0x80
	bne	_03804DE4
	ldrh	r3, [lr]
	and	r3, r3, #255	;@ 0xff
	strb	r3, [r2, r0]
	add	r0, r0, #1
_03804E00:
	cmp	r0, r1
	bcc	_03804DE0
	mov	r1, #33024	;@ 0x8100
	ldr	ip, _03804E48	;@ =0x040001C0
	strh	r1, [ip]
	mov	r3, #0
	ldr	r1, _03804E4C	;@ =0x040001C2
	strh	r3, [r1]
_03804E20:
	ldrh	r1, [ip]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804E20
	ldr	r1, _03804E4C	;@ =0x040001C2
	ldrh	r1, [r1]
	and	r1, r1, #255	;@ 0xff
	strb	r1, [r2, r0]
_03804E3C:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_03804E48:	.word	0x040001C0
_03804E4C:	.word	0x040001C2

	arm_func_start NVRAM_ReadDataBytes
NVRAM_ReadDataBytes: ;@ 0x03804E50
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	cmp	r1, #1
	bcc	_03804F5C
	and	r3, r0, #16711680	;@ 0xff0000
	mov	r3, r3, lsr #16
	strh	r3, [sp]
	and	r3, r0, #65280	;@ 0xff00
	mov	r3, r3, lsr #8
	strh	r3, [sp, #2]
	and	r0, r0, #255	;@ 0xff
	strh	r0, [sp, #4]
	ldr	r3, _03804F68	;@ =0x040001C0
_03804E84:
	ldrh	r0, [r3]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804E84
	mov	r0, #35072	;@ 0x8900
	strh	r0, [r3]
	mov	r0, #3
	ldr	ip, _03804F6C	;@ =0x040001C2
	strh	r0, [ip]
	mov	lr, #0
	add	r3, sp, #0
	ldr	r4, _03804F68	;@ =0x040001C0
_03804EB0:
	ldrh	r0, [r4]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804EB0
	mov	r0, lr, lsl #1
	ldrh	r0, [r3, r0]
	and	r0, r0, #255	;@ 0xff
	strh	r0, [ip]
	add	lr, lr, #1
	cmp	lr, #3
	blt	_03804EB0
	ldr	r3, _03804F68	;@ =0x040001C0
_03804EDC:
	ldrh	r0, [r3]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804EDC
	mov	r0, #0
	ldr	ip, _03804F68	;@ =0x040001C0
	mov	r4, r0
	ldr	lr, _03804F6C	;@ =0x040001C2
	sub	r1, r1, #1
	b	_03804F20
_03804F00:
	strh	r4, [lr]
_03804F04:
	ldrh	r3, [ip]
	ands	r3, r3, #128	;@ 0x80
	bne	_03804F04
	ldrh	r3, [lr]
	and	r3, r3, #255	;@ 0xff
	strb	r3, [r2, r0]
	add	r0, r0, #1
_03804F20:
	cmp	r0, r1
	bcc	_03804F00
	mov	r1, #33024	;@ 0x8100
	ldr	ip, _03804F68	;@ =0x040001C0
	strh	r1, [ip]
	mov	r3, #0
	ldr	r1, _03804F6C	;@ =0x040001C2
	strh	r3, [r1]
_03804F40:
	ldrh	r1, [ip]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804F40
	ldr	r1, _03804F6C	;@ =0x040001C2
	ldrh	r1, [r1]
	and	r1, r1, #255	;@ 0xff
	strb	r1, [r2, r0]
_03804F5C:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_03804F68:	.word	0x040001C0
_03804F6C:	.word	0x040001C2

	arm_func_start NVRAM_ReadStatusRegister
NVRAM_ReadStatusRegister: ;@ 0x03804F70
	ldr	r2, _03804FDC	;@ =0x040001C0
_03804F74:
	ldrh	r1, [r2]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804F74
	mov	r1, #35072	;@ 0x8900
	strh	r1, [r2]
	mov	r2, #5
	ldr	r1, _03804FE0	;@ =0x040001C2
	strh	r2, [r1]
	ldr	r2, _03804FDC	;@ =0x040001C0
_03804F98:
	ldrh	r1, [r2]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804F98
	mov	r1, #33024	;@ 0x8100
	strh	r1, [r2]
	mov	r2, #0
	ldr	r1, _03804FE0	;@ =0x040001C2
	strh	r2, [r1]
	ldr	r2, _03804FDC	;@ =0x040001C0
_03804FBC:
	ldrh	r1, [r2]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804FBC
	ldr	r1, _03804FE0	;@ =0x040001C2
	ldrh	r1, [r1]
	and	r1, r1, #255	;@ 0xff
	strb	r1, [r0]
	bx	lr
_03804FDC:	.word	0x040001C0
_03804FE0:	.word	0x040001C2

	arm_func_start NVRAM_WriteDisable
NVRAM_WriteDisable: ;@ 0x03804FE4
	ldr	r1, _0380501C	;@ =0x040001C0
_03804FE8:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804FE8
	mov	r0, #33024	;@ 0x8100
	strh	r0, [r1]
	mov	r1, #4
	ldr	r0, _03805020	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _0380501C	;@ =0x040001C0
_0380500C:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_0380500C
	bx	lr
_0380501C:	.word	0x040001C0
_03805020:	.word	0x040001C2

	arm_func_start NVRAM_WriteEnable
NVRAM_WriteEnable: ;@ 0x03805024
	ldr	r1, _0380505C	;@ =0x040001C0
_03805028:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03805028
	mov	r0, #33024	;@ 0x8100
	strh	r0, [r1]
	mov	r1, #6
	ldr	r0, _03805060	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _0380505C	;@ =0x040001C0
_0380504C:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_0380504C
	bx	lr
_0380505C:	.word	0x040001C0
_03805060:	.word	0x040001C2

	arm_func_start FUN_03805064
FUN_03805064: ;@ 0x03805064
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	lr, #0
	mov	r2, lr
	b	_03805094
_03805078:
	mov	r1, r2, lsl #2
	mov	r1, r0, lsr r1
	and	r1, r1, #15
	cmp	r1, #10
	movcs	r0, #0
	bcs	_038050D0
	add	r2, r2, #1
_03805094:
	cmp	r2, #8
	blt	_03805078
	mov	r3, #0
	mov	ip, #1
	mov	r2, #10
_038050A8:
	mov	r1, r3, lsl #2
	mov	r1, r0, lsr r1
	and	r1, r1, #15
	mla	lr, ip, r1, lr
	add	r3, r3, #1
	mul	r1, ip, r2
	mov	ip, r1
	cmp	r3, #8
	blt	_038050A8
	mov	r0, lr
_038050D0:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start FUN_038050DC
FUN_038050DC: ;@ 0x038050DC
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r8, r0
	mov	r7, r1
	mov	r6, r2
	sub	r0, r7, #1
	cmp	r0, #1
	subls	r8, r8, #1
	addls	r7, r7, #12
	mov	r0, r8
	mov	r1, #400	;@ 0x190
	bl	_u32_div_f
	mov	r5, r0
	mov	r0, r8
	mov	r1, #100	;@ 0x64
	bl	_u32_div_f
	mov	r4, r0
	mov	r0, #13
	mul	r0, r7, r0
	add	r0, r0, #8
	mov	r1, #5
	bl	_u32_div_f
	add	r1, r8, r8, lsr #2
	sub	r1, r1, r4
	add	r1, r5, r1
	add	r0, r1, r0
	add	r0, r6, r0
	mov	r1, #7
	bl	_u32_div_f
	mov	r0, r1
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr

	arm_func_start FUN_03805158
FUN_03805158: ;@ 0x03805158
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	add	r0, sp, #0
	bl	RTC_ReadStatus1
	add	r0, sp, #2
	bl	RTC_ReadStatus2
	ldrh	r0, [sp]
	mov	r1, r0, lsl #24
	movs	r1, r1, lsr #31
	bne	_0380519C
	mov	r0, r0, lsl #25
	movs	r0, r0, lsr #31
	bne	_0380519C
	ldrh	r0, [sp, #2]
	mov	r0, r0, lsl #24
	movs	r0, r0, lsr #31
	beq	_038051B4
_0380519C:
	ldrh	r0, [sp]
	bic	r0, r0, #1
	orr	r0, r0, #1
	strh	r0, [sp]
	add	r0, sp, #0
	bl	RTC_WriteStatus1
_038051B4:
	ldrh	r0, [sp]
	mov	r1, r0, lsl #27
	movs	r1, r1, lsr #31
	bne	_038051D0
	mov	r0, r0, lsl #26
	movs	r0, r0, lsr #31
	beq	_038051F0
_038051D0:
	ldrh	r0, [sp, #2]
	bic	r0, r0, #15
	strh	r0, [sp, #2]
	ldrh	r0, [sp, #2]
	bic	r0, r0, #64	;@ 0x40
	strh	r0, [sp, #2]
	add	r0, sp, #2
	bl	RTC_WriteStatus2
_038051F0:
	ldr	r0, _03805288	;@ =0x027FFDE8
	bl	RTC_ReadDateTime
	ldr	r0, _03805288	;@ =0x027FFDE8
	ldrb	r0, [r0]
	bl	FUN_03805064
	mov	r4, r0
	ldr	r0, _03805288	;@ =0x027FFDE8
	ldr	r0, [r0]
	mov	r0, r0, lsl #19
	mov	r0, r0, lsr #27
	bl	FUN_03805064
	mov	r5, r0
	ldr	r0, _03805288	;@ =0x027FFDE8
	ldr	r0, [r0]
	mov	r0, r0, lsl #10
	mov	r0, r0, lsr #26
	bl	FUN_03805064
	mov	r2, r0
	add	r0, r4, #2000	;@ 0x7d0
	mov	r1, r5
	bl	FUN_038050DC
	ldr	r2, _03805288	;@ =0x027FFDE8
	ldr	r1, [r2]
	mov	r3, r1, lsl #5
	mov	r3, r3, lsr #29
	cmp	r3, r0
	beq	_03805274
	bic	r1, r1, #117440512	;@ 0x7000000
	and	r0, r0, #7
	orr	r0, r1, r0, lsl #24
	str	r0, [r2]
	mov	r0, r2
	bl	RTC_WriteDateTime
_03805274:
	mov	r0, #1
	bl	RTC_SetHourFormat
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_03805288:	.word	0x027FFDE8

	arm_func_start FUN_0380528C
FUN_0380528C: ;@ 0x0380528C
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	add	r0, sp, #0
	bl	RTC_ReadStatus1
	ldrh	r0, [sp]
	mov	r1, r0, lsl #27
	movs	r1, r1, lsr #31
	bne	_038052B8
	mov	r0, r0, lsl #26
	movs	r0, r0, lsr #31
	beq	_03805310
_038052B8:
	add	r0, sp, #2
	bl	RTC_ReadStatus2
	mov	r4, #0
	ldrh	r0, [sp]
	mov	r0, r0, lsl #27
	movs	r0, r0, lsr #31
	orrne	r4, r4, #1
	ldrneh	r0, [sp, #2]
	bicne	r0, r0, #15
	strneh	r0, [sp, #2]
	ldrh	r0, [sp]
	mov	r0, r0, lsl #26
	movs	r0, r0, lsr #31
	orrne	r4, r4, #2
	ldrneh	r0, [sp, #2]
	bicne	r0, r0, #64	;@ 0x40
	strneh	r0, [sp, #2]
	add	r0, sp, #2
	bl	RTC_WriteStatus2
	mov	r0, #48	;@ 0x30
	mov	r1, r4
	bl	FUN_038057D8
_03805310:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start FUN_0380531C
FUN_0380531C: ;@ 0x0380531C
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #76	;@ 0x4c
	ldr	r6, _038057CC	;@ =0x027FFDE8
	add	r5, r6, #4
	mov	r7, #0
	ldr	r9, _038057D0	;@ =_0380A03C
	mov	r8, #1
	mov	r0, #16
	str	r0, [sp]
	mov	r0, #17
	str	r0, [sp, #4]
	mov	r0, #18
	str	r0, [sp, #8]
	mov	sl, #19
	mov	r4, #2
	mov	fp, #20
	mov	r0, #21
	str	r0, [sp, #12]
	mov	r0, #22
	str	r0, [sp, #16]
	mov	r0, #23
	str	r0, [sp, #20]
	mov	r0, #24
	str	r0, [sp, #24]
	mov	r0, #25
	str	r0, [sp, #28]
	mov	r0, #32
	str	r0, [sp, #32]
	mov	r0, #33	;@ 0x21
	str	r0, [sp, #36]	;@ 0x24
	mov	r0, #34	;@ 0x22
	str	r0, [sp, #40]	;@ 0x28
	mov	r0, #35	;@ 0x23
	str	r0, [sp, #44]	;@ 0x2c
	mov	r0, #36	;@ 0x24
	str	r0, [sp, #48]	;@ 0x30
	mov	r0, #37	;@ 0x25
	str	r0, [sp, #52]	;@ 0x34
	mov	r0, #38	;@ 0x26
	str	r0, [sp, #56]	;@ 0x38
	mov	r0, #39	;@ 0x27
	str	r0, [sp, #60]	;@ 0x3c
	mov	r0, #40	;@ 0x28
	str	r0, [sp, #64]	;@ 0x40
	mov	r0, #41	;@ 0x29
	str	r0, [sp, #68]	;@ 0x44
_038053D4:
	mov	r0, r9
	add	r1, sp, #72	;@ 0x48
	mov	r2, r8
	bl	OS_ReceiveMessage
	ldr	r0, _038057D4	;@ =_0380A13C
	ldrh	r0, [r0, #216]	;@ 0xd8
	cmp	r0, #41	;@ 0x29
	addls	pc, pc, r0, lsl #2
	b	_038057BC
	b	_038054A0
	b	_038054B8
	b	_038057BC
	b	_038057BC
	b	_038057BC
	b	_038057BC
	b	_038057BC
	b	_038057BC
	b	_038057BC
	b	_038057BC
	b	_038057BC
	b	_038057BC
	b	_038057BC
	b	_038057BC
	b	_038057BC
	b	_038057BC
	b	_038054DC
	b	_038054F8
	b	_03805514
	b	_03805530
	b	_03805568
	b	_038055A0
	b	_038055D8
	b	_038055F4
	b	_03805610
	b	_0380562C
	b	_038057BC
	b	_038057BC
	b	_038057BC
	b	_038057BC
	b	_038057BC
	b	_038057BC
	b	_03805648
	b	_03805664
	b	_03805688
	b	_038056A4
	b	_038056DC
	b	_03805714
	b	_0380574C
	b	_03805768
	b	_03805784
	b	_038057A0
_038054A0:
	bl	RTC_Reset
	str	r7, [r9, #468]	;@ 0x1d4
	mov	r0, r7
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_038054B8:
	ldrh	r0, [r6]
	mov	r0, r0, lsl #30
	mov	r0, r0, lsr #31
	bl	RTC_SetHourFormat
	str	r7, [r9, #468]	;@ 0x1d4
	mov	r0, r8
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_038054DC:
	mov	r0, r6
	bl	RTC_ReadDateTime
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp]
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_038054F8:
	mov	r0, r6
	bl	RTC_ReadDate
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #4]
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_03805514:
	add	r0, r6, #4
	bl	RTC_ReadTime
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #8]
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_03805530:
	mov	r0, r5
	bl	RTC_ReadPulse
	cmp	r0, #0
	bne	_03805554
	str	r7, [r9, #468]	;@ 0x1d4
	mov	r0, sl
	mov	r1, r4
	bl	FUN_038057D8
	b	_038053D4
_03805554:
	str	r7, [r9, #468]	;@ 0x1d4
	mov	r0, sl
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_03805568:
	mov	r0, r5
	bl	RTC_ReadAlarm1
	cmp	r0, #0
	bne	_0380558C
	str	r7, [r9, #468]	;@ 0x1d4
	mov	r0, fp
	mov	r1, r4
	bl	FUN_038057D8
	b	_038053D4
_0380558C:
	str	r7, [r9, #468]	;@ 0x1d4
	mov	r0, fp
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_038055A0:
	mov	r0, r5
	bl	RTC_ReadAlarm2
	cmp	r0, #0
	bne	_038055C4
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #12]
	mov	r1, r4
	bl	FUN_038057D8
	b	_038053D4
_038055C4:
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #12]
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_038055D8:
	mov	r0, r6
	bl	RTC_ReadStatus1
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #16]
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_038055F4:
	add	r0, r6, #2
	bl	RTC_ReadStatus2
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #20]
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_03805610:
	add	r0, r6, #4
	bl	RTC_ReadAdjust
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #24]
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_0380562C:
	add	r0, r6, #4
	bl	RTC_ReadFree
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #28]
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_03805648:
	mov	r0, r6
	bl	RTC_WriteDateTime
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #32]
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_03805664:
	add	r0, r6, #4
	bl	RTC_ReadTime
	mov	r0, r6
	bl	RTC_WriteDateTime
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #36]	;@ 0x24
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_03805688:
	add	r0, r6, #4
	bl	RTC_WriteTime
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #40]	;@ 0x28
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_038056A4:
	mov	r0, r5
	bl	RTC_WritePulse
	cmp	r0, #0
	bne	_038056C8
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #44]	;@ 0x2c
	mov	r1, r4
	bl	FUN_038057D8
	b	_038053D4
_038056C8:
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #44]	;@ 0x2c
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_038056DC:
	mov	r0, r5
	bl	RTC_WriteAlarm1
	cmp	r0, #0
	bne	_03805700
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #48]	;@ 0x30
	mov	r1, r4
	bl	FUN_038057D8
	b	_038053D4
_03805700:
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #48]	;@ 0x30
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_03805714:
	mov	r0, r5
	bl	RTC_WriteAlarm2
	cmp	r0, #0
	bne	_03805738
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #52]	;@ 0x34
	mov	r1, r4
	bl	FUN_038057D8
	b	_038053D4
_03805738:
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #52]	;@ 0x34
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_0380574C:
	mov	r0, r6
	bl	RTC_WriteStatus1
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #56]	;@ 0x38
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_03805768:
	add	r0, r6, #2
	bl	RTC_WriteStatus2
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #60]	;@ 0x3c
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_03805784:
	add	r0, r6, #4
	bl	RTC_WriteAdjust
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #64]	;@ 0x40
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_038057A0:
	add	r0, r6, #4
	bl	RTC_WriteFree
	str	r7, [r9, #468]	;@ 0x1d4
	ldr	r0, [sp, #68]	;@ 0x44
	mov	r1, r7
	bl	FUN_038057D8
	b	_038053D4
_038057BC:
	str	r7, [r9, #468]	;@ 0x1d4
	mov	r1, r8
	bl	FUN_038057D8
	b	_038053D4
_038057CC:	.word	0x027FFDE8
_038057D0:	.word	_0380A03C
_038057D4:	.word	_0380A13C

	arm_func_start FUN_038057D8
FUN_038057D8: ;@ 0x038057D8
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r0, r0, lsl #8
	and	r0, r0, #32512	;@ 0x7f00
	orr	r2, r0, #32768	;@ 0x8000
	and	r0, r1, #255	;@ 0xff
	orr	r6, r2, r0
	mov	r5, #5
	mov	r4, #0
_038057F8:
	mov	r0, r5
	mov	r1, r6
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	blt	_038057F8
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start FUN_03805818
FUN_03805818: ;@ 0x03805818
	stmdb	sp!, {r4, lr}
	cmp	r2, #0
	bne	_03805944
	and	r0, r1, #32512	;@ 0x7f00
	mov	r0, r0, lsl #8
	mov	r4, r0, lsr #16
	cmp	r4, #41	;@ 0x29
	addls	pc, pc, r4, lsl #2
	b	_03805938
	b	_038058E4
	b	_038058E4
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_038058E4
	b	_038058E4
	b	_038058E4
	b	_038058E4
	b	_038058E4
	b	_038058E4
	b	_038058E4
	b	_038058E4
	b	_038058E4
	b	_038058E4
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_03805938
	b	_038058E4
	b	_038058E4
	b	_038058E4
	b	_038058E4
	b	_038058E4
	b	_038058E4
	b	_038058E4
_038058E4:
	ldr	r0, _0380594C	;@ =_0380A03C
	ldr	r1, [r0, #468]	;@ 0x1d4
	cmp	r1, #0
	beq	_03805904
	mov	r0, r4
	mov	r1, #3
	bl	FUN_038057D8
	b	_03805944
_03805904:
	mov	r1, #1
	str	r1, [r0, #468]	;@ 0x1d4
	ldr	r1, _03805950	;@ =_0380A13C
	strh	r4, [r1, #216]	;@ 0xd8
	mov	r1, #0
	mov	r2, r1
	bl	OS_SendMessage
	cmp	r0, #0
	bne	_03805944
	mov	r0, r4
	mov	r1, #4
	bl	FUN_038057D8
	b	_03805944
_03805938:
	mov	r0, r4
	mov	r1, #1
	bl	FUN_038057D8
_03805944:
	ldmia	sp!, {r4, lr}
	bx	lr
_0380594C:	.word	_0380A03C
_03805950:	.word	_0380A13C

	arm_func_start RTC_Init
RTC_Init: ;@ 0x03805954
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	mov	r4, r0
	ldr	r0, _03805A28	;@ =_0380A038
	ldrh	r1, [r0]
	cmp	r1, #0
	bne	_03805A1C
	mov	r1, #1
	strh	r1, [r0]
	ldr	r0, _03805A2C	;@ =_0380A03C
	str	r1, [r0, #468]	;@ 0x1d4
	bl	FUN_03805158
	mov	r1, #0
	ldr	r0, _03805A2C	;@ =_0380A03C
	str	r1, [r0, #468]	;@ 0x1d4
	bl	PXI_Init
	mov	r0, #5
	ldr	r1, _03805A30	;@ =FUN_03805818
	bl	PXI_SetFifoRecvCallback
	ldr	r0, _03805A2C	;@ =_0380A03C
	ldr	r1, _03805A34	;@ =_0380A05C
	mov	r2, #4
	bl	OS_InitMessageQueue
	mov	r0, #256	;@ 0x100
	str	r0, [sp]
	str	r4, [sp, #4]
	ldr	r0, _03805A38	;@ =_0380A06C
	ldr	r1, _03805A3C	;@ =FUN_0380531C
	mov	r2, #0
	ldr	r3, _03805A40	;@ =_0380A210
	bl	OS_CreateThread
	ldr	r0, _03805A38	;@ =_0380A06C
	bl	OS_WakeupThreadDirect
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	mov	r0, #64	;@ 0x40
	mov	r1, #0
	bl	EXIi_SetBitRcnt0L
	mov	r0, #256	;@ 0x100
	mov	r1, r0
	bl	EXIi_SetBitRcnt0L
	bl	OS_DisableInterrupts
	mov	r4, r0
	mov	r0, #128	;@ 0x80
	ldr	r1, _03805A44	;@ =FUN_0380528C
	bl	OS_SetIrqFunction
	mov	r0, #128	;@ 0x80
	bl	OS_EnableIrqMask
	mov	r0, r4
	bl	OS_RestoreInterrupts
_03805A1C:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_03805A28:	.word	_0380A038
_03805A2C:	.word	_0380A03C
_03805A30:	.word	FUN_03805818
_03805A34:	.word	_0380A05C
_03805A38:	.word	_0380A06C
_03805A3C:	.word	FUN_0380531C
_03805A40:	.word	_0380A210
_03805A44:	.word	FUN_0380528C

	arm_func_start FUN_03805A48
FUN_03805A48: ;@ 0x03805A48
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r5, r2
	mov	r4, r3
	bl	RTCi_GpioStart
	mov	r0, r7
	mov	r1, r6
	bl	RTCi_GpioSendCommand
	cmp	r7, #6
	beq	_03805A90
	cmp	r7, #134	;@ 0x86
	bne	_03805A9C
	mov	r0, r5
	mov	r1, r4
	bl	RTCi_GpioReceiveData
	b	_03805A9C
_03805A90:
	mov	r0, r5
	mov	r1, r4
	bl	RTCi_GpioSendData
_03805A9C:
	bl	RTCi_GpioEnd
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr

	arm_func_start FUN_03805AAC
FUN_03805AAC: ;@ 0x03805AAC
	ldr	r2, [r0]
	mov	r1, r2, lsl #18
	mov	r3, r1, lsr #26
	cmp	r3, #35	;@ 0x23
	addls	pc, pc, r3, lsl #2
	b	_03805BA8
	b	_03805B54
	b	_03805B54
	b	_03805B54
	b	_03805B54
	b	_03805B54
	b	_03805B54
	b	_03805B54
	b	_03805B54
	b	_03805B78
	b	_03805B78
	b	_03805BA8
	b	_03805BA8
	b	_03805BA8
	b	_03805BA8
	b	_03805BA8
	b	_03805BA8
	b	_03805B54
	b	_03805B54
	b	_03805B9C
	b	_03805B9C
	b	_03805B9C
	b	_03805B9C
	b	_03805B9C
	b	_03805B9C
	b	_03805B9C
	b	_03805B9C
	b	_03805BA8
	b	_03805BA8
	b	_03805BA8
	b	_03805BA8
	b	_03805BA8
	b	_03805BA8
	b	_03805B9C
	b	_03805B9C
	b	_03805B9C
	b	_03805B9C
_03805B54:
	mov	r1, r2, lsl #17
	movs	r1, r1, lsr #31
	bxeq	lr
	bic	r2, r2, #16128	;@ 0x3f00
	add	r1, r3, #18
	and	r1, r1, #63	;@ 0x3f
	orr	r1, r2, r1, lsl #8
	str	r1, [r0]
	bx	lr
_03805B78:
	mov	r1, r2, lsl #17
	movs	r1, r1, lsr #31
	bxeq	lr
	bic	r2, r2, #16128	;@ 0x3f00
	add	r1, r3, #24
	and	r1, r1, #63	;@ 0x3f
	orr	r1, r2, r1, lsl #8
	str	r1, [r0]
	bx	lr
_03805B9C:
	orr	r1, r2, #16384	;@ 0x4000
	str	r1, [r0]
	bx	lr
_03805BA8:
	ldr	r1, [r0]
	bic	r1, r1, #16384	;@ 0x4000
	str	r1, [r0]
	ldr	r1, [r0]
	bic	r1, r1, #16128	;@ 0x3f00
	str	r1, [r0]
	bx	lr

	arm_func_start FUN_03805BC4
FUN_03805BC4: ;@ 0x03805BC4
	ldr	r1, [r0]
	mov	r2, r1, lsl #18
	mov	r2, r2, lsr #26
	cmp	r2, #35	;@ 0x23
	addls	pc, pc, r2, lsl #2
	b	_03805CD0
	b	_03805C6C
	b	_03805C6C
	b	_03805C6C
	b	_03805C6C
	b	_03805C6C
	b	_03805C6C
	b	_03805C6C
	b	_03805C6C
	b	_03805C6C
	b	_03805C6C
	b	_03805CD0
	b	_03805CD0
	b	_03805CD0
	b	_03805CD0
	b	_03805CD0
	b	_03805CD0
	b	_03805C6C
	b	_03805C6C
	b	_03805C78
	b	_03805C78
	b	_03805C78
	b	_03805C78
	b	_03805C78
	b	_03805C78
	b	_03805C78
	b	_03805C78
	b	_03805CD0
	b	_03805CD0
	b	_03805CD0
	b	_03805CD0
	b	_03805CD0
	b	_03805CD0
	b	_03805CA4
	b	_03805CA4
	b	_03805C78
	b	_03805C78
_03805C6C:
	bic	r1, r1, #16384	;@ 0x4000
	str	r1, [r0]
	bx	lr
_03805C78:
	orr	r1, r1, #16384	;@ 0x4000
	str	r1, [r0]
	ldr	r1, [r0]
	bic	r2, r1, #16128	;@ 0x3f00
	mov	r1, r1, lsl #18
	mov	r1, r1, lsr #26
	sub	r1, r1, #18
	and	r1, r1, #63	;@ 0x3f
	orr	r1, r2, r1, lsl #8
	str	r1, [r0]
	bx	lr
_03805CA4:
	orr	r1, r1, #16384	;@ 0x4000
	str	r1, [r0]
	ldr	r1, [r0]
	bic	r2, r1, #16128	;@ 0x3f00
	mov	r1, r1, lsl #18
	mov	r1, r1, lsr #26
	sub	r1, r1, #24
	and	r1, r1, #63	;@ 0x3f
	orr	r1, r2, r1, lsl #8
	str	r1, [r0]
	bx	lr
_03805CD0:
	ldr	r1, [r0]
	bic	r1, r1, #16384	;@ 0x4000
	str	r1, [r0]
	ldr	r1, [r0]
	bic	r1, r1, #16128	;@ 0x3f00
	str	r1, [r0]
	bx	lr

	arm_func_start RTC_WriteFree
RTC_WriteFree: ;@ 0x03805CEC
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	mov	r0, #6
	mov	r1, #112	;@ 0x70
	mov	r2, r4
	mov	r3, #1
	bl	FUN_03805A48
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_ReadFree
RTC_ReadFree: ;@ 0x03805D18
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	mov	r0, #134	;@ 0x86
	mov	r1, #112	;@ 0x70
	mov	r2, r4
	mov	r3, #1
	bl	FUN_03805A48
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_WriteAdjust
RTC_WriteAdjust: ;@ 0x03805D44
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	mov	r0, #6
	mov	r1, #48	;@ 0x30
	mov	r2, r4
	mov	r3, #1
	bl	FUN_03805A48
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_ReadAdjust
RTC_ReadAdjust: ;@ 0x03805D70
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	mov	r0, #134	;@ 0x86
	mov	r1, #48	;@ 0x30
	mov	r2, r4
	mov	r3, #1
	bl	FUN_03805A48
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_WriteStatus2
RTC_WriteStatus2: ;@ 0x03805D9C
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	mov	r0, #6
	mov	r1, #64	;@ 0x40
	mov	r2, r4
	mov	r3, #1
	bl	FUN_03805A48
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_ReadStatus2
RTC_ReadStatus2: ;@ 0x03805DC8
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	mov	r0, #134	;@ 0x86
	mov	r1, #64	;@ 0x40
	mov	r2, r4
	mov	r3, #1
	bl	FUN_03805A48
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_WriteStatus1
RTC_WriteStatus1: ;@ 0x03805DF4
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	mov	r0, #6
	mov	r1, #0
	mov	r2, r4
	mov	r3, #1
	bl	FUN_03805A48
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_ReadStatus1
RTC_ReadStatus1: ;@ 0x03805E20
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	mov	r0, #134	;@ 0x86
	mov	r1, #0
	mov	r2, r4
	mov	r3, #1
	bl	FUN_03805A48
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_WriteAlarm2
RTC_WriteAlarm2: ;@ 0x03805E4C
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	mov	r4, r0
	add	r0, sp, #0
	bl	RTC_ReadStatus2
	ldrh	r0, [sp]
	mov	r0, r0, lsl #25
	movs	r0, r0, lsr #31
	moveq	r0, #0
	beq	_03805E8C
	mov	r0, #6
	mov	r1, #80	;@ 0x50
	mov	r2, r4
	mov	r3, #3
	bl	FUN_03805A48
	mov	r0, #1
_03805E8C:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_ReadAlarm2
RTC_ReadAlarm2: ;@ 0x03805E98
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	mov	r4, r0
	add	r0, sp, #0
	bl	RTC_ReadStatus2
	ldrh	r0, [sp]
	mov	r0, r0, lsl #25
	movs	r0, r0, lsr #31
	moveq	r0, #0
	beq	_03805ED8
	mov	r0, #134	;@ 0x86
	mov	r1, #80	;@ 0x50
	mov	r2, r4
	mov	r3, #3
	bl	FUN_03805A48
	mov	r0, #1
_03805ED8:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_WriteAlarm1
RTC_WriteAlarm1: ;@ 0x03805EE4
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	mov	r4, r0
	add	r0, sp, #0
	bl	RTC_ReadStatus2
	ldrh	r0, [sp]
	mov	r0, r0, lsl #28
	mov	r0, r0, lsr #28
	cmp	r0, #4
	movne	r0, #0
	bne	_03805F28
	mov	r0, #6
	mov	r1, #16
	mov	r2, r4
	mov	r3, #3
	bl	FUN_03805A48
	mov	r0, #1
_03805F28:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_ReadAlarm1
RTC_ReadAlarm1: ;@ 0x03805F34
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	mov	r4, r0
	add	r0, sp, #0
	bl	RTC_ReadStatus2
	ldrh	r0, [sp]
	mov	r0, r0, lsl #28
	mov	r0, r0, lsr #28
	cmp	r0, #4
	movne	r0, #0
	bne	_03805F78
	mov	r0, #134	;@ 0x86
	mov	r1, #16
	mov	r2, r4
	mov	r3, #3
	bl	FUN_03805A48
	mov	r0, #1
_03805F78:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_WritePulse
RTC_WritePulse: ;@ 0x03805F84
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	mov	r4, r0
	add	r0, sp, #0
	bl	RTC_ReadStatus2
	ldrh	r0, [sp]
	mov	r0, r0, lsl #28
	mov	r0, r0, lsr #28
	and	r0, r0, #11
	cmp	r0, #1
	movne	r0, #0
	bne	_03805FCC
	mov	r0, #6
	mov	r1, #16
	mov	r2, r4
	mov	r3, #1
	bl	FUN_03805A48
	mov	r0, #1
_03805FCC:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_ReadPulse
RTC_ReadPulse: ;@ 0x03805FD8
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	mov	r4, r0
	add	r0, sp, #0
	bl	RTC_ReadStatus2
	ldrh	r0, [sp]
	mov	r0, r0, lsl #28
	mov	r0, r0, lsr #28
	and	r0, r0, #11
	cmp	r0, #1
	movne	r0, #0
	bne	_03806020
	mov	r0, #134	;@ 0x86
	mov	r1, #16
	mov	r2, r4
	mov	r3, #1
	bl	FUN_03805A48
	mov	r0, #1
_03806020:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_WriteTime
RTC_WriteTime: ;@ 0x0380602C
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	mov	r0, #6
	mov	r1, #96	;@ 0x60
	mov	r2, r4
	mov	r3, #3
	bl	FUN_03805A48
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_ReadTime
RTC_ReadTime: ;@ 0x03806058
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	mov	r0, #134	;@ 0x86
	mov	r1, #96	;@ 0x60
	mov	r2, r4
	mov	r3, #3
	bl	FUN_03805A48
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_ReadDate
RTC_ReadDate: ;@ 0x03806084
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	mov	r0, #134	;@ 0x86
	mov	r1, #32
	mov	r2, r4
	mov	r3, #4
	bl	FUN_03805A48
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_WriteDateTime
RTC_WriteDateTime: ;@ 0x038060B0
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	mov	r0, #6
	mov	r1, #32
	mov	r2, r4
	mov	r3, #7
	bl	FUN_03805A48
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_ReadDateTime
RTC_ReadDateTime: ;@ 0x038060DC
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	mov	r0, #134	;@ 0x86
	mov	r1, #32
	mov	r2, r4
	mov	r3, #7
	bl	FUN_03805A48
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start RTC_SetHourFormat
RTC_SetHourFormat: ;@ 0x03806108
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #12
	mov	r4, r0
	and	r5, r4, #1
	mov	r0, r5, lsl #16
	mov	r0, r0, lsr #16
	cmp	r0, #1
	bne	_038061FC
	add	r0, sp, #0
	bl	RTC_ReadStatus1
	ldrh	r1, [sp]
	mov	r0, r1, lsl #30
	mov	r2, r0, lsr #31
	mov	r0, r5, lsl #16
	cmp	r2, r0, lsr #16
	beq	_038061FC
	and	r4, r4, #1
	bic	r1, r1, #2
	mov	r0, r4, lsl #16
	mov	r0, r0, lsr #16
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #1
	strh	r0, [sp]
	add	r0, sp, #0
	bl	RTC_WriteStatus1
	mov	r0, #134	;@ 0x86
	mov	r1, #16
	add	r2, sp, #4
	mov	r3, #3
	bl	FUN_03805A48
	mov	r0, r4, lsl #16
	movs	r0, r0, lsr #16
	bne	_03806198
	add	r0, sp, #4
	bl	FUN_03805BC4
	b	_038061A0
_03806198:
	add	r0, sp, #4
	bl	FUN_03805AAC
_038061A0:
	mov	r0, #6
	mov	r1, #16
	add	r2, sp, #4
	mov	r3, #3
	bl	FUN_03805A48
	mov	r0, #134	;@ 0x86
	mov	r1, #80	;@ 0x50
	add	r2, sp, #4
	mov	r3, #3
	bl	FUN_03805A48
	mov	r0, r5, lsl #16
	movs	r0, r0, lsr #16
	bne	_038061E0
	add	r0, sp, #4
	bl	FUN_03805BC4
	b	_038061E8
_038061E0:
	add	r0, sp, #4
	bl	FUN_03805AAC
_038061E8:
	mov	r0, #6
	mov	r1, #80	;@ 0x50
	add	r2, sp, #4
	mov	r3, #3
	bl	FUN_03805A48
_038061FC:
	add	sp, sp, #12
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start RTC_Reset
RTC_Reset: ;@ 0x03806208
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	ldrh	r0, [sp]
	bic	r0, r0, #1
	orr	r0, r0, #1
	strh	r0, [sp]
	mov	r0, #6
	mov	r1, #0
	add	r2, sp, #0
	mov	r3, #1
	bl	FUN_03805A48
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start RTCi_GpioStart
RTCi_GpioStart: ;@ 0x03806248
	mov	ip, #67108864	;@ 0x4000000
	add	ip, ip, #312	;@ 0x138
	ldrh	r0, [ip]
	bic	r0, r0, #119	;@ 0x77
	orr	r0, r0, #114	;@ 0x72
	strh	r0, [ip]
	mov	r3, #2
_03806264:
	subs	r3, r3, #1
	bne	_03806264
	bic	r0, r0, #4
	orr	r0, r0, #4
	strh	r0, [ip]
	mov	r3, #2
_0380627C:
	subs	r3, r3, #1
	bne	_0380627C
	bx	lr

	arm_func_start RTCi_GpioEnd
RTCi_GpioEnd: ;@ 0x03806288
	mov	ip, #67108864	;@ 0x4000000
	add	ip, ip, #312	;@ 0x138
	mov	r3, #2
_03806294:
	subs	r3, r3, #1
	bne	_03806294
	ldrh	r0, [ip]
	bic	r0, r0, #4
	orr	r0, r0, #0
	strh	r0, [ip]
	mov	r3, #2
_038062B0:
	subs	r3, r3, #1
	bne	_038062B0
	bx	lr

	arm_func_start RTCi_GpioSendCommand
RTCi_GpioSendCommand: ;@ 0x038062BC
	mov	ip, #67108864	;@ 0x4000000
	add	ip, ip, #312	;@ 0x138
	orr	r1, r0, r1
	ldrh	r0, [ip]
	bic	r0, r0, #119	;@ 0x77
	orr	r0, r0, #116	;@ 0x74
	mov	r2, #0
_038062D8:
	bic	r0, r0, #3
	orr	r0, r0, #0
	mov	r3, #1
	tst	r3, r1, lsr r2
	movne	r3, #1
	moveq	r3, #0
	orr	r0, r0, r3
	strh	r0, [ip]
	mov	r3, #9
_038062FC:
	subs	r3, r3, #1
	bne	_038062FC
	bic	r0, r0, #2
	orr	r0, r0, #2
	strh	r0, [ip]
	mov	r3, #9
_03806314:
	subs	r3, r3, #1
	bne	_03806314
	add	r2, r2, #1
	cmp	r2, #8
	bne	_038062D8
	bx	lr

	arm_func_start RTCi_GpioSendData
RTCi_GpioSendData: ;@ 0x0380632C
	mov	ip, #67108864	;@ 0x4000000
	add	ip, ip, #312	;@ 0x138
_03806334:
	stmdb	sp!, {r0, r1}
	tst	r0, #1
	ldreqh	r1, [r0]
	ldrneh	r1, [r0, #-1]
	movne	r1, r1, lsr #8
	ldrh	r0, [ip]
	bic	r0, r0, #119	;@ 0x77
	orr	r0, r0, #116	;@ 0x74
	mov	r2, #0
_03806358:
	bic	r0, r0, #3
	orr	r0, r0, #0
	mov	r3, #1
	tst	r3, r1, lsr r2
	movne	r3, #1
	moveq	r3, #0
	orr	r0, r0, r3
	strh	r0, [ip]
	mov	r3, #9
_0380637C:
	subs	r3, r3, #1
	bne	_0380637C
	bic	r0, r0, #2
	orr	r0, r0, #2
	strh	r0, [ip]
	mov	r3, #9
_03806394:
	subs	r3, r3, #1
	bne	_03806394
	add	r2, r2, #1
	cmp	r2, #8
	bne	_03806358
	ldmia	sp!, {r0, r1}
	add	r0, r0, #1
	subs	r1, r1, #1
	bne	_03806334
	bx	lr

	arm_func_start RTCi_GpioReceiveData
RTCi_GpioReceiveData: ;@ 0x038063BC
	mov	ip, #67108864	;@ 0x4000000
	add	ip, ip, #312	;@ 0x138
_038063C4:
	stmdb	sp!, {r0, r1}
	ldrh	r0, [ip]
	bic	r0, r0, #119	;@ 0x77
	orr	r0, r0, #100	;@ 0x64
	mov	r2, #0
	mov	r1, #0
_038063DC:
	bic	r0, r0, #3
	orr	r0, r0, #0
	strh	r0, [ip]
	mov	r3, #9
_038063EC:
	subs	r3, r3, #1
	bne	_038063EC
	ldrh	r0, [ip]
	and	r3, r0, #1
	cmp	r3, #1
	moveq	r3, #128	;@ 0x80
	movne	r3, #0
	orr	r2, r3, r2, lsr #1
	bic	r0, r0, #2
	orr	r0, r0, #2
	strh	r0, [ip]
	mov	r3, #9
_0380641C:
	subs	r3, r3, #1
	bne	_0380641C
	add	r1, r1, #1
	cmp	r1, #8
	bne	_038063DC
	ldmia	sp!, {r0, r1}
	tst	r0, #1
	beq	_03806454
	ldrh	r3, [r0, #-1]
	bic	r3, r3, #65280	;@ 0xff00
	mov	r2, r2, lsl #8
	orr	r3, r2, r3
	strh	r3, [r0, #-1]
	b	_03806464
_03806454:
	ldrh	r3, [r0]
	bic	r3, r3, #255	;@ 0xff
	orr	r3, r3, r2
	strh	r3, [r0]
_03806464:
	add	r0, r0, #1
	subs	r1, r1, #1
	bne	_038063C4
	bx	lr

	arm_func_start FUN_03806474
FUN_03806474: ;@ 0x03806474
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	ldr	r4, _0380665C	;@ =wmspW
	ldr	r0, _03806660	;@ =_0601A960
	ldr	r0, [r0, #1356]	;@ 0x54c
	cmp	r0, #0
	beq	_038064B0
	add	r0, r4, #4096	;@ 0x1000
	ldr	r0, [r0, #1356]	;@ 0x54c
	ldr	r0, [r0]
	ldrh	r0, [r0]
	cmp	r0, #0
	beq	_038064B0
	bl	FUN_03806668
	bl	FUN_03806670
_038064B0:
	add	r0, r4, #136	;@ 0x88
	add	r1, sp, #0
	mov	r2, #0
	bl	OS_ReceiveMessage
	cmp	r0, #0
	beq	_03806520
	add	r0, r4, #4096	;@ 0x1000
	ldr	r0, [r0, #1356]	;@ 0x54c
	cmp	r0, #0
	beq	_038064B0
	bl	WMSP_GetBuffer4Callback2Wm9
	mov	r5, r0
	mov	r0, #0
	mov	r1, r5
	mov	r2, #256	;@ 0x100
	bl	MIi_CpuClear32
	ldr	r0, [sp]
	ldrh	r0, [r0]
	strh	r0, [r5]
	mov	r0, #4
	strh	r0, [r5, #2]
	mov	r0, r5
	bl	WMSP_ReturnResult2Wm9
	ldr	r1, [sp]
	ldrh	r0, [r1]
	orr	r0, r0, #32768	;@ 0x8000
	strh	r0, [r1]
	b	_038064B0
_03806520:
	bl	FUN_03806678
	bl	FUN_038068BC
	cmp	r0, #0
	beq	_03806548
	add	r0, r4, #136	;@ 0x88
	mov	r1, #0
	mov	r2, #1
	bl	OS_SendMessage
	bl	FUN_03806678
	bl	OS_JoinThread
_03806548:
	add	r0, r4, #136	;@ 0x88
	add	r1, sp, #0
	mov	r2, #0
	bl	OS_ReceiveMessage
	mov	r6, r0
	add	r0, r4, #88	;@ 0x58
	add	r1, sp, #0
	mov	r2, #0
	bl	OS_ReceiveMessage
	mov	r5, r0
	mov	r0, r4
	add	r1, sp, #0
	mov	r2, #0
	bl	OS_ReceiveMessage
	orr	r1, r6, r5
	orrs	r0, r0, r1
	beq	_03806590
	bl	OS_Terminate
_03806590:
	bl	FUN_03806680
	add	r7, r4, #40	;@ 0x28
	add	r6, sp, #0
	mov	r5, #0
_038065A0:
	mov	r0, r7
	mov	r1, r6
	mov	r2, r5
	bl	OS_ReceiveMessage
	cmp	r0, #0
	bne	_038065A0
	bl	FUN_03806688
	bl	FUN_038068BC
	cmp	r0, #0
	beq	_038065E0
	add	r0, r4, #40	;@ 0x28
	mov	r1, #0
	mov	r2, #1
	bl	OS_SendMessage
	bl	FUN_03806688
	bl	OS_JoinThread
_038065E0:
	mov	r0, #1
	bl	PM_SetLEDPattern
	mov	r0, #1
	bl	PMi_SetLED
	add	r0, r4, #4096	;@ 0x1000
	ldr	r0, [r0, #1356]	;@ 0x54c
	cmp	r0, #0
	beq	_03806614
	ldr	r1, [r0]
	ldrh	r0, [r1]
	cmp	r0, #0
	movne	r0, #0
	strneh	r0, [r1]
_03806614:
	bl	FUN_03806970
	mov	r6, #15
	mov	r5, #131072	;@ 0x20000
	mov	r4, #0
_03806624:
	mov	r0, r6
	mov	r1, r5
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	blt	_03806624
	bl	OS_DisableInterrupts
	mov	r1, #1
	ldr	r0, _03806664	;@ =_0380A3F0
	strb	r1, [r0]
	bl	OS_ExitThread
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_0380665C:	.word	wmspW
_03806660:	.word	_0601A960
_03806664:	.word	_0380A3F0

	arm_func_start FUN_03806668
FUN_03806668: ;@ 0x03806668
	ldr	pc, _0380666C	;@ =WMSP_CancelVAlarm
_0380666C:	.word	WMSP_CancelVAlarm

	arm_func_start FUN_03806670
FUN_03806670: ;@ 0x03806670
	ldr	pc, _03806674	;@ =WMSP_CancelAllAlarms
_03806674:	.word	WMSP_CancelAllAlarms

	arm_func_start FUN_03806678
FUN_03806678: ;@ 0x03806678
	ldr	pc, _0380667C	;@ =WMSP_GetRequestThread
_0380667C:	.word	WMSP_GetRequestThread

	arm_func_start FUN_03806680
FUN_03806680: ;@ 0x03806680
	ldr	pc, _03806684	;@ =WL_Terminate
_03806684:	.word	WL_Terminate

	arm_func_start FUN_03806688
FUN_03806688: ;@ 0x03806688
	ldr	pc, _0380668C	;@ =WMSP_GetIndicateThread
_0380668C:	.word	WMSP_GetIndicateThread

	arm_func_start FUN_03806690
FUN_03806690: ;@ 0x03806690
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r0, _03806738	;@ =_0380A400
	bl	FUN_038068BC
	cmp	r0, #0
	beq	_038066C0
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #0
	b	_0380672C
_038066C0:
	ldr	r0, _0380673C	;@ =_0380A3F0
	ldrb	r1, [r0]
	cmp	r1, #3
	beq	_038066E0
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #0
	b	_0380672C
_038066E0:
	mov	r1, #4
	strb	r1, [r0]
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #10
	ldr	r1, _03806740	;@ =FUN_03806920
	bl	PXI_SetFifoRecvCallback
	mov	r0, #1024	;@ 0x400
	str	r0, [sp]
	mov	r0, #2
	str	r0, [sp, #4]
	ldr	r0, _03806738	;@ =_0380A400
	ldr	r1, _03806744	;@ =FUN_03806474
	mov	r2, #0
	ldr	r3, _03806748	;@ =_0380AA64
	bl	OS_CreateThread
	ldr	r0, _03806738	;@ =_0380A400
	bl	OS_WakeupThreadDirect
	mov	r0, #1
_0380672C:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_03806738:	.word	_0380A400
_0380673C:	.word	_0380A3F0
_03806740:	.word	FUN_03806920
_03806744:	.word	FUN_03806474
_03806748:	.word	_0380AA64

	arm_func_start FUN_0380674C
FUN_0380674C: ;@ 0x0380674C
	stmdb	sp!, {r4, r5, r6, lr}
	bl	FUN_038069B0
	ldr	r0, _038067A0	;@ =_0380A3F8
	ldr	r0, [r0]
	bl	FUN_038069EC
	mov	r6, #15
	mov	r5, #65536	;@ 0x10000
	mov	r4, #0
_0380676C:
	mov	r0, r6
	mov	r1, r5
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	blt	_0380676C
	bl	OS_DisableInterrupts
	mov	r1, #3
	ldr	r0, _038067A4	;@ =_0380A3F0
	strb	r1, [r0]
	bl	OS_ExitThread
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr
_038067A0:	.word	_0380A3F8
_038067A4:	.word	_0380A3F0

	arm_func_start FUN_038067A8
FUN_038067A8: ;@ 0x038067A8
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r0, _03806844	;@ =_0380A400
	bl	FUN_038068BC
	cmp	r0, #0
	beq	_038067D8
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #0
	b	_03806838
_038067D8:
	ldr	r0, _03806848	;@ =_0380A3F0
	ldrb	r1, [r0]
	cmp	r1, #1
	beq	_038067F8
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #0
	b	_03806838
_038067F8:
	mov	r1, #2
	strb	r1, [r0]
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #1024	;@ 0x400
	str	r0, [sp]
	mov	r0, #10
	str	r0, [sp, #4]
	ldr	r0, _03806844	;@ =_0380A400
	ldr	r1, _0380684C	;@ =FUN_0380674C
	mov	r2, #0
	ldr	r3, _03806850	;@ =_0380AA64
	bl	OS_CreateThread
	ldr	r0, _03806844	;@ =_0380A400
	bl	OS_WakeupThreadDirect
	mov	r0, #1
_03806838:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_03806844:	.word	_0380A400
_03806848:	.word	_0380A3F0
_0380684C:	.word	FUN_0380674C
_03806850:	.word	_0380AA64

	arm_func_start FUN_03806854
FUN_03806854: ;@ 0x03806854
	stmdb	sp!, {r4, lr}
	mov	r4, r1
	cmp	r4, #65536	;@ 0x10000
	beq	_03806870
	cmp	r4, #131072	;@ 0x20000
	beq	_03806884
	b	_03806898
_03806870:
	bl	FUN_038067A8
	cmp	r0, #0
	bne	_038068B4
	orr	r4, r4, #5
	b	_0380689C
_03806884:
	bl	FUN_03806690
	cmp	r0, #0
	bne	_038068B4
	orr	r4, r4, #5
	b	_0380689C
_03806898:
	orr	r4, r4, #7
_0380689C:
	mov	r0, #15
	mov	r1, r4
	mov	r2, #0
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	blt	_0380689C
_038068B4:
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start FUN_038068BC
FUN_038068BC: ;@ 0x038068BC
	cmp	r0, #0
	moveq	r0, #0
	bxeq	lr
	ldr	r1, _0380691C	;@ =OSi_ThreadInfo
	ldr	r1, [r1, #8]
	b	_0380690C
_038068D4:
	cmp	r1, r0
	bne	_03806908
	ldr	r0, [r0, #72]	;@ 0x48
	cmp	r0, #0
	beq	_038068F8
	cmp	r0, #1
	beq	_038068F8
	cmp	r0, #2
	b	_03806900
_038068F8:
	mov	r0, #1
	bx	lr
_03806900:
	mov	r0, #0
	bx	lr
_03806908:
	ldr	r1, [r1, #76]	;@ 0x4c
_0380690C:
	cmp	r1, #0
	bne	_038068D4
	mov	r0, #0
	bx	lr
_0380691C:	.word	OSi_ThreadInfo

	arm_func_start FUN_03806920
FUN_03806920: ;@ 0x03806920
	stmdb	sp!, {r4, r5, r6, lr}
	movs	r6, r1
	ldrh	r4, [r6]
	beq	_03806968
	mov	r0, #0
	mov	r2, #256	;@ 0x100
	bl	MIi_CpuClear32
	strh	r4, [r6]
	mov	r0, #4
	strh	r0, [r6, #2]
	mov	r5, #10
	mov	r4, #0
_03806950:
	mov	r0, r5
	mov	r1, r6
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	blt	_03806950
_03806968:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start FUN_03806970
FUN_03806970: ;@ 0x03806970
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _038069A8	;@ =_0380A3F4
	ldr	r0, [r0]
	cmp	r0, #0
	beq	_0380699C
	mov	r0, #0
	mov	r1, #100663296	;@ 0x6000000
	ldr	r2, _038069AC	;@ =_0380A3FC
	ldr	r2, [r2]
	bl	MIi_CpuClearFast
_0380699C:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_038069A8:	.word	_0380A3F4
_038069AC:	.word	_0380A3FC

	arm_func_start FUN_038069B0
FUN_038069B0: ;@ 0x038069B0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _038069E4	;@ =_0380A3F4
	ldr	r0, [r0]
	cmp	r0, #0
	beq	_038069D8
	mov	r1, #100663296	;@ 0x6000000
	ldr	r2, _038069E8	;@ =_0380A3FC
	ldr	r2, [r2]
	bl	MIi_CpuCopyFast
_038069D8:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_038069E4:	.word	_0380A3F4
_038069E8:	.word	_0380A3FC

	arm_func_start FUN_038069EC
FUN_038069EC: ;@ 0x038069EC
	stmfd	sp!, {lr}
	sub	sp, sp, #84	;@ 0x54
	ldr	r1, _03806A84	;@ =_0380B064
	str	r1, [sp]
	ldr	r1, _03806A88	;@ =_0380B064
	str	r1, [sp, #4]
	mov	r1, #1536	;@ 0x600
	str	r1, [sp, #8]
	mov	r3, #4
	str	r3, [sp, #12]
	mov	r1, #0
	str	r1, [sp, #32]
	mov	r2, #8
	str	r2, [sp, #36]	;@ 0x24
	str	r0, [sp, #40]	;@ 0x28
	ldr	r0, _03806A8C	;@ =_0380A4A4
	str	r0, [sp, #44]	;@ 0x2c
	mov	r0, #448	;@ 0x1c0
	str	r0, [sp, #48]	;@ 0x30
	mov	r1, #3
	str	r1, [sp, #52]	;@ 0x34
	mov	r0, #64	;@ 0x40
	str	r0, [sp, #28]
	str	r1, [sp, #60]	;@ 0x3c
	str	r3, [sp, #76]	;@ 0x4c
	mov	r0, #5
	str	r0, [sp, #68]	;@ 0x44
	mov	r0, #7
	str	r0, [sp, #56]	;@ 0x38
	str	r2, [sp, #72]	;@ 0x48
	mov	r0, #9
	str	r0, [sp, #64]	;@ 0x40
	add	r0, sp, #0
	add	r1, sp, #52	;@ 0x34
	bl	FUN_03806A90
	add	sp, sp, #84	;@ 0x54
	ldmia	sp!, {lr}
	bx	lr
_03806A84:	.word	_0380B064
_03806A88:	.word	_0380B064
_03806A8C:	.word	_0380A4A4

	arm_func_start FUN_03806A90
FUN_03806A90: ;@ 0x03806A90
	ldr	pc, _03806A94	;@ =WM_sp_init
_03806A94:	.word	WM_sp_init

	arm_func_start WVR_Shutdown
WVR_Shutdown: ;@ 0x03806A98
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _03806ACC	;@ =0x04000304
	ldrh	r0, [r1]
	bic	r0, r0, #2
	strh	r0, [r1]
	mov	r0, #1
	bl	PM_SetLEDPattern
	mov	r0, #1
	bl	PMi_SetLED
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03806ACC:	.word	0x04000304

	arm_func_start WVR_Init
WVR_Init: ;@ 0x03806AD0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _03806B20	;@ =_0380A3F8
	str	r0, [r1]
	mov	r1, #1
	ldr	r0, _03806B24	;@ =_0380A3F0
	strb	r1, [r0]
	ldr	r0, _03806B28	;@ =_0380A400
	mov	r1, #0
	mov	r2, #164	;@ 0xa4
	bl	MI_CpuFill8
	mov	r0, #15
	ldr	r1, _03806B2C	;@ =FUN_03806854
	bl	PXI_SetFifoRecvCallback
	mov	r0, #10
	ldr	r1, _03806B30	;@ =FUN_03806920
	bl	PXI_SetFifoRecvCallback
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03806B20:	.word	_0380A3F8
_03806B24:	.word	_0380A3F0
_03806B28:	.word	_0380A400
_03806B2C:	.word	FUN_03806854
_03806B30:	.word	FUN_03806920

	arm_func_start MATH_CountPopulation
MATH_CountPopulation: ; 0x03806B34
	ldr	r1, _03806B6C	;@ =0x55555555
	and	r1, r1, r0, lsr #1
	sub	r2, r0, r1
	ldr	r0, _03806B70	;@ =0x33333333
	and	r1, r2, r0
	and	r0, r0, r2, lsr #2
	add	r0, r1, r0
	add	r1, r0, r0, lsr #4
	ldr	r0, _03806B74	;@ =0x0F0F0F0F
	and	r0, r1, r0
	add	r0, r0, r0, lsr #8
	add	r0, r0, r0, lsr #16
	and	r0, r0, #255	;@ 0xff
	bx	lr
_03806B6C:	.word	0x55555555
_03806B70:	.word	0x33333333
_03806B74:	.word	0x0F0F0F0F

	arm_func_start _ll_udiv
_ll_udiv: ;@ 0x03806B78
	stmdb	sp!, {r4, r5, r6, r7, fp, ip, lr}
	mov	r4, #0
	b	_03806B8C

	arm_func_start _ull_mod
_ull_mod: ;@ 0x03806B84
	stmdb	sp!, {r4, r5, r6, r7, fp, ip, lr}
	mov	r4, #1
_03806B8C:
	orrs	r5, r3, r2
	bne	_03806B9C
	ldmia	sp!, {r4, r5, r6, r7, fp, ip, lr}
	bx	lr
_03806B9C:
	orrs	r5, r1, r3
	bne	_03806C44
	mov	r1, r2
	bl	_u32_div_not_0_f
	cmp	r4, #0
	movne	r0, r1
	mov	r1, #0
	ldmia	sp!, {r4, r5, r6, r7, fp, ip, lr}
	bx	lr

	arm_func_start _ll_mod
_ll_mod: ;@ 0x03806BC0
	stmdb	sp!, {r4, r5, r6, r7, fp, ip, lr}
	mov	r4, r1
	orr	r4, r4, #1
	b	_03806BE0

	arm_func_start _ll_sdiv
_ll_sdiv: ;@ 0x03806BD0
	stmdb	sp!, {r4, r5, r6, r7, fp, ip, lr}
	eor	r4, r1, r3
	mov	r4, r4, asr #1
	mov	r4, r4, lsl #1
_03806BE0:
	orrs	r5, r3, r2
	bne	_03806BF0
	ldmia	sp!, {r4, r5, r6, r7, fp, ip, lr}
	bx	lr
_03806BF0:
	mov	r5, r0, lsr #31
	add	r5, r5, r1
	mov	r6, r2, lsr #31
	add	r6, r6, r3
	orrs	r6, r5, r6
	bne	_03806C24
	mov	r1, r2
	bl	_s32_div_f
	ands	r4, r4, #1
	movne	r0, r1
	mov	r1, r0, asr #31
	ldmia	sp!, {r4, r5, r6, r7, fp, ip, lr}
	bx	lr
_03806C24:
	cmp	r1, #0
	bge	_03806C34
	rsbs	r0, r0, #0
	rsc	r1, r1, #0
_03806C34:
	cmp	r3, #0
	bge	_03806C44
	rsbs	r2, r2, #0
	rsc	r3, r3, #0
_03806C44:
	orrs	r5, r1, r0
	beq	_03806D68
	mov	r5, #0
	mov	r6, #1
	cmp	r3, #0
	bmi	_03806C70
_03806C5C:
	add	r5, r5, #1
	adds	r2, r2, r2
	adcs	r3, r3, r3
	bpl	_03806C5C
	add	r6, r6, r5
_03806C70:
	cmp	r1, #0
	blt	_03806C90
_03806C78:
	cmp	r6, #1
	beq	_03806C90
	sub	r6, r6, #1
	adds	r0, r0, r0
	adcs	r1, r1, r1
	bpl	_03806C78
_03806C90:
	mov	r7, #0
	mov	ip, #0
	mov	fp, #0
	b	_03806CB8
_03806CA0:
	orr	ip, ip, #1
	subs	r6, r6, #1
	beq	_03806D10
	adds	r0, r0, r0
	adcs	r1, r1, r1
	adcs	r7, r7, r7
_03806CB8:
	subs	r0, r0, r2
	sbcs	r1, r1, r3
	sbcs	r7, r7, #0
	adds	ip, ip, ip
	adc	fp, fp, fp
	cmp	r7, #0
	bge	_03806CA0
_03806CD4:
	subs	r6, r6, #1
	beq	_03806D08
	adds	r0, r0, r0
	adcs	r1, r1, r1
	adc	r7, r7, r7
	adds	r0, r0, r2
	adcs	r1, r1, r3
	adc	r7, r7, #0
	adds	ip, ip, ip
	adc	fp, fp, fp
	cmp	r7, #0
	bge	_03806CA0
	b	_03806CD4
_03806D08:
	adds	r0, r0, r2
	adc	r1, r1, r3
_03806D10:
	ands	r7, r4, #1
	moveq	r0, ip
	moveq	r1, fp
	beq	_03806D48
	subs	r7, r5, #32
	movge	r0, r1, lsr r7
	bge	_03806D6C
	rsb	r7, r5, #32
	mov	r0, r0, lsr r5
	orr	r0, r0, r1, lsl r7
	mov	r1, r1, lsr r5
	b	_03806D48
	mov	r0, r1, lsr r7
	mov	r1, #0
_03806D48:
	cmp	r4, #0
	blt	_03806D58
	ldmia	sp!, {r4, r5, r6, r7, fp, ip, lr}
	bx	lr
_03806D58:
	rsbs	r0, r0, #0
	rsc	r1, r1, #0
	ldmia	sp!, {r4, r5, r6, r7, fp, ip, lr}
	bx	lr
_03806D68:
	mov	r0, #0
_03806D6C:
	mov	r1, #0
	cmp	r4, #0
	blt	_03806D58
	ldmia	sp!, {r4, r5, r6, r7, fp, ip, lr}
	bx	lr

	arm_func_start _s32_div_f
_s32_div_f: ;@ 0x03806D80
	eor	ip, r0, r1
	and	ip, ip, #-2147483648	;@ 0x80000000
	cmp	r0, #0
	rsblt	r0, r0, #0
	addlt	ip, ip, #1
	cmp	r1, #0
	rsblt	r1, r1, #0
	beq	_03806F78
	cmp	r0, r1
	movcc	r1, r0
	movcc	r0, #0
	bcc	_03806F78
	mov	r2, #28
	mov	r3, r0, lsr #4
	cmp	r1, r3, lsr #12
	suble	r2, r2, #16
	movle	r3, r3, lsr #16
	cmp	r1, r3, lsr #4
	suble	r2, r2, #8
	movle	r3, r3, lsr #8
	cmp	r1, r3
	suble	r2, r2, #4
	movle	r3, r3, lsr #4
	mov	r0, r0, lsl r2
	rsb	r1, r1, #0
	adds	r0, r0, r0
	add	r2, r2, r2, lsl #1
	add	pc, pc, r2, lsl #2
	nop			;@ (mov r0, r0)
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	mov	r1, r3
_03806F78:
	ands	r3, ip, #-2147483648	;@ 0x80000000
	rsbne	r0, r0, #0
	ands	r3, ip, #1
	rsbne	r1, r1, #0
	bx	lr

	arm_func_start _u32_div_f
_u32_div_f: ;@ 0x03806F8C
	cmp	r1, #0
	bxeq	lr

	arm_func_start _u32_div_not_0_f
_u32_div_not_0_f: ;@ 0x03806F94
	cmp	r0, r1
	movcc	r1, r0
	movcc	r0, #0
	bxcc	lr
	mov	r2, #28
	mov	r3, r0, lsr #4
	cmp	r1, r3, lsr #12
	suble	r2, r2, #16
	movle	r3, r3, lsr #16
	cmp	r1, r3, lsr #4
	suble	r2, r2, #8
	movle	r3, r3, lsr #8
	cmp	r1, r3
	suble	r2, r2, #4
	movle	r3, r3, lsr #4
	mov	r0, r0, lsl r2
	rsb	r1, r1, #0
	adds	r0, r0, r0
	add	r2, r2, r2, lsl #1
	add	pc, pc, r2, lsl #2
	nop			;@ (mov r0, r0)
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	adcs	r3, r1, r3, lsl #1
	subcc	r3, r3, r1
	adcs	r0, r0, r0
	mov	r1, r3
	bx	lr

	.global _03807170
_03807170:
	.byte	0
	.byte	6
	.byte	12
	.byte	19
	.byte	25
	.byte	31
	.byte	37
	.byte	43
	.byte	49
	.byte	54
	.byte	60
	.byte	65
	.byte	71
	.byte	76
	.byte	81
	.byte	85
	.byte	90
	.byte	94
	.byte	98
	.byte	102
	.byte	106
	.byte	109
	.byte	112
	.byte	115
	.byte	117
	.byte	120
	.byte	122
	.byte	123
	.byte	125
	.byte	126
	.byte	126
	.byte	127
	.byte	127
	.byte	0
	.byte	0
	.byte	0

	.global SNDi_DecibelSquareTable
SNDi_DecibelSquareTable:
	.short	-32768
	.short	-722
	.short	-721
	.short	-651
	.short	-601
	.short	-562
	.short	-530
	.short	-503
	.short	-480
	.short	-460
	.short	-442
	.short	-425
	.short	-410
	.short	-396
	.short	-383
	.short	-371
	.short	-360
	.short	-349
	.short	-339
	.short	-330
	.short	-321
	.short	-313
	.short	-305
	.short	-297
	.short	-289
	.short	-282
	.short	-276
	.short	-269
	.short	-263
	.short	-257
	.short	-251
	.short	-245
	.short	-239
	.short	-234
	.short	-229
	.short	-224
	.short	-219
	.short	-214
	.short	-210
	.short	-205
	.short	-201
	.short	-196
	.short	-192
	.short	-188
	.short	-184
	.short	-180
	.short	-176
	.short	-173
	.short	-169
	.short	-165
	.short	-162
	.short	-158
	.short	-155
	.short	-152
	.short	-149
	.short	-145
	.short	-142
	.short	-139
	.short	-136
	.short	-133
	.short	-130
	.short	-127
	.short	-125
	.short	-122
	.short	-119
	.short	-116
	.short	-114
	.short	-111
	.short	-109
	.short	-106
	.short	-103
	.short	-101
	.short	-99
	.short	-96
	.short	-94
	.short	-91
	.short	-89
	.short	-87
	.short	-85
	.short	-82
	.short	-80
	.short	-78
	.short	-76
	.short	-74
	.short	-72
	.short	-70
	.short	-68
	.short	-66
	.short	-64
	.short	-62
	.short	-60
	.short	-58
	.short	-56
	.short	-54
	.short	-52
	.short	-50
	.short	-49
	.short	-47
	.short	-45
	.short	-43
	.short	-42
	.short	-40
	.short	-38
	.short	-36
	.short	-35
	.short	-33
	.short	-31
	.short	-30
	.short	-28
	.short	-27
	.short	-25
	.short	-23
	.short	-22
	.short	-20
	.short	-19
	.short	-17
	.short	-16
	.short	-14
	.short	-13
	.short	-11
	.short	-10
	.short	-8
	.short	-7
	.short	-6
	.short	-4
	.short	-3
	.short	-1
	.short	0

	.global _03807294
_03807294:
	.byte	0
	.byte	1
	.byte	2
	.byte	4

	.global _03807298
_03807298:
	.byte	4
	.byte	5
	.byte	6
	.byte	7
	.byte	2
	.byte	0
	.byte	3
	.byte	1
	.byte	8
	.byte	9
	.byte	10
	.byte	11
	.byte	14
	.byte	12
	.byte	15
	.byte	13

	.global _038072A8
_038072A8:
	.byte	0
	.byte	1
	.byte	5
	.byte	14
	.byte	26
	.byte	38
	.byte	51
	.byte	63
	.byte	73
	.byte	84
	.byte	92
	.byte	100
	.byte	109
	.byte	116
	.byte	123
	.byte	127
	.byte	132
	.byte	137
	.byte	143
	.byte	0

	.global _038072BC
_038072BC:
	.word	0x000000C7

	.global _038072C0
_038072C0:
	.word	0x00000006

	.global _038072C4
_038072C4:
	.word	0x00000005

	.global _038072C8
_038072C8:
	.word	0x00000040
	.word	0x00000006
	.word	0x01000000
	.word	0x00000018
	.word	0x00080000
	.word	0x00000013
	.word	0x00100000
	.word	0x00000014
	.word	0x00040000
	.word	0x00000012
	.word	0x00000008
	.word	0x00000003
	.word	0x00000010
	.word	0x00000004
	.word	0x00000020
	.word	0x00000005
	.word	0x00000100
	.word	0x00000008
	.word	0x00000200
	.word	0x00000009
	.word	0x00000400
	.word	0x0000000A
	.word	0x00000800
	.word	0x0000000B
	.word	0x00001000
	.word	0x0000000C
	.word	0x00002000
	.word	0x0000000D
	.word	0x00000002
	.word	0x00000001
	.word	0x00000004
	.word	0x00000002
	.word	0x00000001
	.word	0x00000000
	.word	0x00010000
	.word	0x00000010
	.word	0x00400000
	.word	0x00000016
	.word	0x00000080
	.word	0x00000007
	.word	0x00020000
	.word	0x00000011
	.word	0x00800000
	.word	0x00000017

	arm_func_start FUN_03807378
FUN_03807378: ;@ 0x03807378
	mov	ip, #67108864	;@ 0x4000000
	str	ip, [ip, #520]	;@ 0x208
	ldr	r1, _038073E0	;@ =0x0380FFFC
	mov	r0, #0
	str	r0, [r1]
	ldr	r1, _038073E4	;@ =0x04000180
	mov	r0, #256	;@ 0x100
	strh	r0, [r1]
_03807398:
	ldrh	r0, [r1]
	and	r0, r0, #15
	cmp	r0, #1
	bne	_03807398
	ldr	r1, _038073E4	;@ =0x04000180
	mov	r0, #0
	strh	r0, [r1]
_038073B4:
	ldrh	r0, [r1]
	cmp	r0, #1
	beq	_038073B4
	ldr	r3, _038073E8	;@ =0x027FFE00
	ldr	ip, [r3, #52]	;@ 0x34
	mov	lr, ip
	mov	r0, #0
	mov	r1, #0
	mov	r2, #0
	mov	r3, #0
	bx	ip
_038073E0:	.word	0x0380FFFC
_038073E4:	.word	0x04000180
_038073E8:	.word	0x027FFE00

	arm_func_start FUN_038073EC
FUN_038073EC: ;@ 0x038073EC
	mov	r1, #0
	ldr	r0, _03807400	;@ =0x04000208
	strh	r1, [r0]
	ldr	ip, _03807404	;@ =FUN_03807378
	bx	ip
_03807400:	.word	0x04000208
_03807404:	.word	FUN_03807378

	arm_func_start WMSP_GetAllowedChannel
WMSP_GetAllowedChannel: ;@ 0x03807408
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	ldr	r1, _03807530	;@ =0x00001FFF
	and	r0, r0, r1
	mov	r0, r0, lsl #16
	movs	r6, r0, lsr #16
	moveq	r0, #0
	beq	_03807524
	mov	r9, #0
	mov	r0, #1
	b	_03807444
_03807434:
	mov	r1, r0, lsl r9
	ands	r1, r6, r1
	bne	_0380744C
	add	r9, r9, #1
_03807444:
	cmp	r9, #16
	blt	_03807434
_0380744C:
	mov	sl, #15
	mov	r0, #1
	b	_03807468
_03807458:
	mov	r1, r0, lsl sl
	ands	r1, r6, r1
	bne	_03807470
	sub	sl, sl, #1
_03807468:
	cmp	sl, #0
	bne	_03807458
_03807470:
	sub	r5, sl, r9
	cmp	r5, #5
	movlt	r0, #1
	movlt	r0, r0, lsl r9
	movlt	r0, r0, lsl #16
	movlt	r0, r0, lsr #16
	blt	_03807524
	add	r0, sl, r9
	mov	r1, #2
	bl	_s32_div_f
	mov	r8, r0
	mov	r7, #0
	mov	fp, #2
	mov	r4, #1
	b	_038074D4
_038074AC:
	mov	r0, r7
	mov	r1, fp
	bl	_s32_div_f
	mov	r0, r1, lsl #1
	sub	r0, r0, #1
	mla	r8, r7, r0, r8
	mov	r0, r4, lsl r8
	ands	r0, r6, r0
	bne	_038074DC
	add	r7, r7, #1
_038074D4:
	cmp	r7, r5
	blt	_038074AC
_038074DC:
	sub	r0, sl, r8
	cmp	r0, #5
	blt	_038074F4
	sub	r0, r8, r9
	cmp	r0, #5
	bge	_0380750C
_038074F4:
	mov	r0, #1
	mov	r1, r0, lsl r9
	orr	r0, r1, r0, lsl sl
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	b	_03807524
_0380750C:
	mov	r1, #1
	mov	r0, r1, lsl sl
	orr	r0, r0, r1, lsl r8
	orr	r0, r0, r1, lsl r9
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
_03807524:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_03807530:	.word	0x00001FFF

	arm_func_start WMSP_GetBuffer4Callback2Wm9
WMSP_GetBuffer4Callback2Wm9: ;@ 0x03807534
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	ldr	r0, _03807584	;@ =_0601AE88
	bl	OS_LockMutex
	mov	r5, #256	;@ 0x100
	ldr	r4, _03807588	;@ =0x027FFF96
	b	_03807558
_03807550:
	mov	r0, r5
	bl	FUN_037F8CB4
_03807558:
	ldrh	r0, [r4]
	ands	r1, r0, #1
	bne	_03807550
	orr	r0, r0, #1
	strh	r0, [r4]
	ldr	r0, _0380758C	;@ =_0601A960
	ldr	r0, [r0, #1356]	;@ 0x54c
	ldr	r0, [r0, #8]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_03807584:	.word	_0601AE88
_03807588:	.word	0x027FFF96
_0380758C:	.word	_0601A960

	arm_func_start WMSP_ReturnResult2Wm9
WMSP_ReturnResult2Wm9: ;@ 0x03807590
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, #256	;@ 0x100
	mov	r5, #10
	mov	r4, #0
	b	_038075B4
_038075AC:
	mov	r0, r6
	bl	FUN_037F8CB4
_038075B4:
	mov	r0, r5
	mov	r1, r7
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	blt	_038075AC
	ldr	r0, _038075E0	;@ =_0601AE88
	bl	OS_UnlockMutex
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_038075E0:	.word	_0601AE88
	.balign 2, 0 ; Don't pad with nop
