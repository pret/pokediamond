	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global _0380A038
_0380A038: ;0x0380A038
	.space 0x0380A03C - 0x0380A038

	.global _0380A03C
_0380A03C: ;0x0380A03C
	.space 0x0380A05C - 0x0380A03C

	.global _0380A05C
_0380A05C: ;0x0380A05C
	.space 0x0380A06C - 0x0380A05C

	.global _0380A06C
_0380A06C: ;0x0380A06C
	.space 0x0380A13C - 0x0380A06C

	.global _0380A13C
_0380A13C: ;0x0380A13C
	.space 0x0380A210 - 0x0380A13C

	.section .text

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
