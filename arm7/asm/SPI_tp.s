	.include "asm/macros.inc"
	.include "global.inc"

    .section .bss

	.global _03809E4C
_03809E4C: ;0x03809E4C
	.space 0x03809E50 - 0x03809E4C

	.global _03809E50
_03809E50: ;0x03809E50
	.space 0x03809E54 - 0x03809E50

	.global _03809E54
_03809E54: ;0x03809E54
	.space 0x03809E80 - 0x03809E54

	.global _03809E80
_03809E80: ;0x03809E80
	.space 0x03809F28 - 0x03809E80

	.global _03809F28
_03809F28: ;0x03809F28
	.space 0x03809F2C - 0x03809F28

    .section .text

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
