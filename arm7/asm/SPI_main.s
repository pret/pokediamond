	.include "asm/macros.inc"
	.include "global.inc"

    .section .bss

	.global _038099AC
_038099AC: ;0x038099AC
	.space 0x038099B0 - 0x038099AC

	.global _038099B0
_038099B0: ;0x038099B0
	.space 0x038099B8 - 0x038099B0

	.global _038099B8
_038099B8: ;0x038099B8
	.space 0x03809C5C - 0x038099B8

	.global _03809C5C
_03809C5C: ;0x03809C5C
	.space 0x03809C7C - 0x03809C5C

	.global _03809C7C
_03809C7C: ;0x03809C7C
	.space 0x03809CBC - 0x03809C7C

	.global _03809CBC
_03809CBC: ;0x03809CBC
	.space 0x03809CC0 - 0x03809CBC

	.global _03809CC0
_03809CC0: ;0x03809CC0
	.space 0x03809E40 - 0x03809CC0

	.global _03809E40
_03809E40: ;0x03809E40
	.space 0x03809E4C - 0x03809E40

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
