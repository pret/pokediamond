	.include "asm/macros.inc"
	.include "global.inc"

    .section .bss

	.global _03809F6C
_03809F6C: ;0x03809F6C
	.space 0x03809FA8 - 0x03809F6C

	.global _03809FA8
_03809FA8: ;0x03809FA8
	.space 0x03809FB8 - 0x03809FA8

    .section .text

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
