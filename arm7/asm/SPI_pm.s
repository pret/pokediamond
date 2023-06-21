	.include "asm/macros.inc"
	.include "global.inc"

    .section .data

	.global PMi_LEDStatus
PMi_LEDStatus:
	.word	0x00000001

	.global PMi_BlinkPatternData
PMi_BlinkPatternData:
	.word	0x00000000
	.word	0xAA000000
	.word	0x00010008
	.word	0x00000000
	.word	0xCC000000
	.word	0x00010008
	.word	0x00000000
	.word	0xE3800000
	.word	0x0001000C
	.word	0x00000000
	.word	0xF0F00000
	.word	0x00010010
	.word	0x00000000
	.word	0xF83E0000
	.word	0x00010014
	.word	0x00000000
	.word	0xFC000000
	.word	0x0001000C
	.word	0x00000000
	.word	0xFF000000
	.word	0x00010010
	.word	0x00000000
	.word	0xFFC00000
	.word	0x00010014
	.word	0x00000000
	.word	0xFF000000
	.word	0x00010020
	.word	0x00000000
	.word	0xFF00FF00
	.word	0x00010020
	.word	0x00000000
	.word	0xFFFFFF00
	.word	0x00010020
	.word	0x00000000
	.word	0xC3000000
	.word	0x00020028

    .section .bss

	.global PMi_KeyPattern
PMi_KeyPattern: ;0x03809F2C
	.space 0x03809F30 - 0x03809F2C

	.global PMi_TriggerBL
PMi_TriggerBL: ;0x03809F30
	.space 0x03809F34 - 0x03809F30

	.global PMi_Initialized
PMi_Initialized: ;0x03809F34
	.space 0x03809F38 - 0x03809F34

	.global PMi_Work
PMi_Work: ;0x03809F38
	.space 0x03809F64 - 0x03809F38

	.global _03809F64
_03809F64: ;0x03809F64
	.space 0x03809F68 - 0x03809F64

	.global PMi_BlinkPatternNo
PMi_BlinkPatternNo: ;0x03809F68
	.space 0x03809F6C - 0x03809F68

    .section .text

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
	bl	sub_03802808
	mov	r0, #1
	bl	sub_03802820
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
	bl	sub_03802820
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
	bl	sub_03802808
	mov	r0, #1
	bl	sub_03802820
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
	bl	sub_03802820
	and	r1, r4, #255	;@ 0xff
	ldr	r0, _03802804	;@ =0x040001C2
	strh	r1, [r0]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_03802800:	.word	0x040001C0
_03802804:	.word	0x040001C2

	arm_func_start sub_03802808
sub_03802808: ;@ 0x03802808
	ldr	r1, _03802818	;@ =0x00008202
	ldr	r0, _0380281C	;@ =0x040001C0
	strh	r1, [r0]
	bx	lr
_03802818:	.word	0x00008202
_0380281C:	.word	0x040001C0

	arm_func_start sub_03802820
sub_03802820: ;@ 0x03802820
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
	bl	sub_03802BAC
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

	arm_func_start sub_03802BAC
sub_03802BAC: ;@ 0x03802BAC
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
