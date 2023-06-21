	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start sub_03805A48
sub_03805A48: ;@ 0x03805A48
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

	arm_func_start sub_03805AAC
sub_03805AAC: ;@ 0x03805AAC
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

	arm_func_start sub_03805BC4
sub_03805BC4: ;@ 0x03805BC4
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
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
	bl	sub_03805A48
	mov	r0, r4, lsl #16
	movs	r0, r0, lsr #16
	bne	_03806198
	add	r0, sp, #4
	bl	sub_03805BC4
	b	_038061A0
_03806198:
	add	r0, sp, #4
	bl	sub_03805AAC
_038061A0:
	mov	r0, #6
	mov	r1, #16
	add	r2, sp, #4
	mov	r3, #3
	bl	sub_03805A48
	mov	r0, #134	;@ 0x86
	mov	r1, #80	;@ 0x50
	add	r2, sp, #4
	mov	r3, #3
	bl	sub_03805A48
	mov	r0, r5, lsl #16
	movs	r0, r0, lsr #16
	bne	_038061E0
	add	r0, sp, #4
	bl	sub_03805BC4
	b	_038061E8
_038061E0:
	add	r0, sp, #4
	bl	sub_03805AAC
_038061E8:
	mov	r0, #6
	mov	r1, #80	;@ 0x50
	add	r2, sp, #4
	mov	r3, #3
	bl	sub_03805A48
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
	bl	sub_03805A48
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
