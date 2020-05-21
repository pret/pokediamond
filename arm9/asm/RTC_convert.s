	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_02106A20
	.extern UNK_02106A1C

	.text

	arm_func_start RTC_GetDayOfWeek
RTC_GetDayOfWeek: ; 0x020D6248
	stmdb sp!, {r4-r6,lr}
	ldr r1, [r0, #0x4]
	ldr r2, [r0, #0x0]
	sub r3, r1, #0x2
	cmp r3, #0x1
	add lr, r2, #0x7d0
	ldr r4, _020D630C ; =0x51EB851F
	sublt lr, lr, #0x1
	ldr r12, [r0, #0x8]
	smull r0, r2, r4, lr
	addlt r3, r3, #0xc
	mov r1, #0x1a
	mul r0, r3, r1
	smull r1, r3, r4, lr
	ldr r5, _020D6310 ; =0x66666667
	sub r0, r0, #0x2
	smull r4, r1, r5, r0
	mov r4, lr, lsr #0x1f
	mov r2, r2, asr #0x5
	mov r3, r3, asr #0x5
	add r3, r4, r3
	ldr r5, _020D6314 ; =0x00000064
	add r2, r4, r2
	smull r2, r4, r5, r2
	sub r2, lr, r2
	mov r1, r1, asr #0x2
	mov r0, r0, lsr #0x1f
	add r1, r0, r1
	mov r4, r2, asr #0x1
	add r0, r12, r1
	add r1, r2, r4, lsr #0x1e
	add r2, r2, r0
	mov r6, r3, asr #0x1
	add r0, r3, r6, lsr #0x1e
	add r1, r2, r1, asr #0x2
	add r1, r1, r0, asr #0x2
	mov r0, #0x5
	mla r4, r3, r0, r1
	ldr r3, _020D6318 ; =0x92492493
	mov r1, r4, lsr #0x1f
	smull r2, r0, r3, r4
	add r0, r4, r0
	mov r0, r0, asr #0x2
	ldr r2, _020D631C ; =0x00000007
	add r0, r1, r0
	smull r0, r1, r2, r0
	sub r0, r4, r0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D630C: .word 0x51EB851F
_020D6310: .word 0x66666667
_020D6314: .word 0x00000064
_020D6318: .word 0x92492493
_020D631C: .word 0x00000007

	arm_func_start RTC_ConvertSecondToDateTime
RTC_ConvertSecondToDateTime: ; 0x020D6320
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r2
	mov r12, #0x0
	mov r4, r3
	subs r2, r5, r12
	sbcs r2, r4, r12
	mov r7, r0
	mov r6, r1
	movlt r5, r12
	movlt r4, r12
	blt _020D6364
	ldr r1, _020D63B0 ; =0xBC19137F
	subs r0, r1, r5
	sbcs r0, r12, r4
	movlt r5, r1
	movlt r4, r12
_020D6364:
	ldr r2, _020D63B4 ; =0x00015180
	mov r0, r5
	mov r1, r4
	mov r3, #0x0
	bl _ll_mod
	mov r1, r0
	mov r0, r6
	bl RTCi_ConvertSecondToTime
	ldr r2, _020D63B4 ; =0x00015180
	mov r0, r5
	mov r1, r4
	mov r3, #0x0
	bl _ll_sdiv
	mov r1, r0
	mov r0, r7
	bl RTC_ConvertDayToDate
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020D63B0: .word 0xBC19137F
_020D63B4: .word 0x00015180

	arm_func_start RTCi_ConvertSecondToTime
RTCi_ConvertSecondToTime: ; 0x020D63B8
	stmdb sp!, {r4-r6,lr}
	ldr r2, _020D6448 ; =0x0001517F
	cmp r1, #0x0
	movlt r1, #0x0
	cmp r1, r2
	ldr ip, _020D644C ; =0x88888889
	movgt r1, r2
	smull r2, r3, r12, r1
	smull r2, lr, r12, r1
	ldr r5, _020D6450 ; =0x91A2B3C5
	add r3, r1, r3
	smull r4, r2, r5, r1
	mov r5, r1, lsr #0x1f
	mov r3, r3, asr #0x5
	add r3, r5, r3
	smull r4, r6, r12, r3
	add lr, r1, lr
	mov lr, lr, asr #0x5
	add r6, r3, r6
	add r2, r1, r2
	ldr r4, _020D6454 ; =0x0000003C
	add lr, r5, lr
	smull r12, lr, r4, lr
	sub lr, r1, r12
	mov r2, r2, asr #0xb
	mov r6, r6, asr #0x5
	mov r1, r3, lsr #0x1f
	add r6, r1, r6
	smull r1, r12, r4, r6
	str lr, [r0, #0x8]
	sub r6, r3, r1
	str r6, [r0, #0x4]
	add r2, r5, r2
	str r2, [r0, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D6448: .word 0x0001517F
_020D644C: .word 0x88888889
_020D6450: .word 0x91A2B3C5
_020D6454: .word 0x0000003C

	arm_func_start RTC_ConvertDayToDate
RTC_ConvertDayToDate: ; 0x020D6458
	stmdb sp!, {r4,lr}
	ldr r2, _020D6560 ; =0x00008EAC
	cmp r1, #0x0
	movlt r1, #0x0
	cmp r1, r2
	movgt r1, r2
	ldr r3, _020D6564 ; =0x92492493
	add lr, r1, #0x6
	smull r2, r4, r3, lr
	add r4, lr, r4
	mov r4, r4, asr #0x2
	mov r2, lr, lsr #0x1f
	ldr ip, _020D6568 ; =0x00000007
	add r4, r2, r4
	smull r2, r3, r12, r4
	sub r4, lr, r2
	ldr r2, _020D656C ; =0x0000016D
	ldr r3, _020D6570 ; =0x0000016E
	str r4, [r0, #0xc]
	mov lr, #0x0
_020D64A8:
	ands r12, lr, #0x3
	moveq r12, r3
	movne r12, r2
	mov r4, r1
	subs r1, r1, r12
	movmi r1, r4
	bmi _020D64D0
	add lr, lr, #0x1
	cmp lr, #0x63
	blo _020D64A8
_020D64D0:
	ldr r2, _020D656C ; =0x0000016D
	str lr, [r0, #0x0]
	cmp r1, r2
	movgt r1, r2
	ands r2, lr, #0x3
	bne _020D6518
	cmp r1, #0x3c
	bge _020D6514
	cmp r1, #0x1f
	movlt r2, #0x1
	subge r1, r1, #0x1f
	movge r2, #0x2
	str r2, [r0, #0x4]
	add r1, r1, #0x1
	str r1, [r0, #0x8]
	ldmia sp!, {r4,lr}
	bx lr
_020D6514:
	sub r1, r1, #0x1
_020D6518:
	ldr r3, _020D6574 ; =UNK_02106A20
	mov r4, #0xb
_020D6520:
	ldr r2, [r3, r4, lsl #0x2]
	mov r12, r4, lsl #0x2
	cmp r1, r2
	blt _020D6550
	add r2, r4, #0x1
	str r2, [r0, #0x4]
	ldr r2, [r3, r12]
	sub r1, r1, r2
	add r1, r1, #0x1
	str r1, [r0, #0x8]
	ldmia sp!, {r4,lr}
	bx lr
_020D6550:
	subs r4, r4, #0x1
	bpl _020D6520
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D6560: .word 0x00008EAC
_020D6564: .word 0x92492493
_020D6568: .word 0x00000007
_020D656C: .word 0x0000016D
_020D6570: .word 0x0000016E
_020D6574: .word UNK_02106A20

	arm_func_start RTC_ConvertDateTimeToSecond
RTC_ConvertDateTimeToSecond: ; 0x020D6578
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	bl RTC_ConvertDateToDay
	mov r4, r0
	mvn r0, #0x0
	cmp r4, r0
	addeq sp, sp, #0x4
	moveq r1, r0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	mov r0, r5
	bl RTCi_ConvertTimeToSecond
	mvn r2, #0x0
	cmp r0, r2
	moveq r1, r2
	beq _020D65DC
	ldr r1, _020D65EC ; =0x00015180
	mov r2, #0x0
	umull r12, r3, r4, r1
	mla r3, r4, r2, r3
	mov r2, r4, asr #0x1f
	mla r3, r2, r1, r3
	adds r2, r0, r12
	adc r1, r3, r0, asr #0x1f
_020D65DC:
	mov r0, r2
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D65EC: .word 0x00015180

	arm_func_start RTCi_ConvertTimeToSecond
RTCi_ConvertTimeToSecond: ; 0x020D65F0
	ldr r3, [r0, #0x4]
	ldr r2, [r0, #0x0]
	mov r1, #0x3c
	mla r3, r2, r1, r3
	ldr r0, [r0, #0x8]
	mla r0, r3, r1, r0
	bx lr

	arm_func_start RTC_ConvertDateToDay
RTC_ConvertDateToDay: ; 0x020D660C
	ldr r3, [r0, #0x0]
	cmp r3, #0x64
	bhs _020D665C
	ldr r2, [r0, #0x4]
	cmp r2, #0x1
	blo _020D665C
	cmp r2, #0xc
	bhi _020D665C
	ldr r1, [r0, #0x8]
	cmp r1, #0x1
	blo _020D665C
	cmp r1, #0x1f
	bhi _020D665C
	ldr r0, [r0, #0xc]
	cmp r0, #0x7
	bge _020D665C
	cmp r2, #0x1
	blo _020D665C
	cmp r2, #0xc
	bls _020D6664
_020D665C:
	mvn r0, #0x0
	bx lr
_020D6664:
	ldr r0, _020D6698 ; =UNK_02106A1C
	sub r1, r1, #0x1
	ldr r0, [r0, r2, lsl #0x2]
	cmp r2, #0x3
	add r2, r1, r0
	blo _020D6684
	ands r0, r3, #0x3
	addeq r2, r2, #0x1
_020D6684:
	ldr r0, _020D669C ; =0x0000016D
	add r1, r3, #0x3
	mla r0, r3, r0, r2
	add r0, r0, r1, lsr #0x2
	bx lr
	.balign 4
_020D6698: .word UNK_02106A1C
_020D669C: .word 0x0000016D
