	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start RtcWaitBusy
RtcWaitBusy: ; 0x020D5914
	ldr ip, _020D5928 ; =0x021D5538
_020D5918:
	ldr r0, [r12, #0x0]
	cmp r0, #0x1
	beq _020D5918
	bx lr
	.balign 4
_020D5928: .word 0x021D5538

	arm_func_start RtcGetResultCallback
RtcGetResultCallback: ; 0x020D592C
	ldr r1, _020D5938 ; =0x021D5538
	str r0, [r1, #0x20]
	bx lr
	.balign 4
_020D5938: .word 0x021D5538

	arm_func_start RtcBCD2HEX
RtcBCD2HEX: ; 0x020D593C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, #0x0
	mov r3, r5
	mov r2, r5
_020D5950:
	mov r1, r0, lsr r2
	and r1, r1, #0xf
	cmp r1, #0xa
	addcs sp, sp, #0x4
	movcs r0, #0x0
	ldmcsia sp!, {r4-r5,lr}
	bxcs lr
	add r3, r3, #0x1
	cmp r3, #0x8
	add r2, r2, #0x4
	blt _020D5950
	mov r12, #0x0
	mov lr, r12
	mov r4, #0x1
	mov r2, #0xa
_020D598C:
	mov r1, r0, lsr lr
	and r3, r1, #0xf
	mul r1, r4, r2
	mla r5, r4, r3, r5
	add r12, r12, #0x1
	mov r4, r1
	cmp r12, #0x8
	add lr, lr, #0x4
	blt _020D598C
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start RtcCommonCallback
RtcCommonCallback: ; 0x020D59C0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	beq _020D5A30
	ldr r0, _020D5F30 ; =0x021D5538
	ldr r2, _020D5F30 ; =0x021D5538
	ldr r1, [r0, #0x18]
	ldr r4, [r2, #0x4]
	cmp r1, #0x0
	movne r1, #0x0
	strne r1, [r0, #0x18]
	ldr r0, _020D5F30 ; =0x021D5538
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	movne r1, #0x0
	strne r1, [r0, #0x0]
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r1, [r2, #0x10]
	mov r3, #0x0
	mov r0, #0x6
	str r3, [r2, #0x4]
	blx r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D5A30:
	and r0, r1, #0x7f00
	mov r0, r0, lsr #0x8
	and r0, r0, #0xff
	cmp r0, #0x30
	and r2, r1, #0xff
	bne _020D5A70
	ldr r0, _020D5F30 ; =0x021D5538
	ldr r0, [r0, #0x1c]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	blx r0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D5A70:
	cmp r2, #0x0
	bne _020D5E88
	ldr r0, _020D5F30 ; =0x021D5538
	mov r5, #0x0
	ldr r1, [r0, #0x14]
	cmp r1, #0xf
	addls pc, pc, r1, lsl #0x2
	b _020D5E74
_020D5A90:
	b _020D5AD0
_020D5A94:
	b _020D5B24
_020D5A98:
	b _020D5B74
_020D5A9C:
	b _020D5ED0
_020D5AA0:
	b _020D5ED0
_020D5AA4:
	b _020D5ED0
_020D5AA8:
	b _020D5C1C
_020D5AAC:
	b _020D5C4C
_020D5AB0:
	b _020D5C70
_020D5AB4:
	b _020D5D14
_020D5AB8:
	b _020D5DC8
_020D5ABC:
	b _020D5ED0
_020D5AC0:
	b _020D5ED0
_020D5AC4:
	b _020D5ED0
_020D5AC8:
	b _020D5ED0
_020D5ACC:
	b _020D5ED0
_020D5AD0:
	ldr r1, _020D5F34 ; =0x027FFDE8
	ldr r4, [r0, #0x8]
	ldrb r0, [r1, #0x0]
	bl RtcBCD2HEX
	ldr r1, _020D5F34 ; =0x027FFDE8
	str r0, [r4, #0x0]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsl #0x13
	mov r0, r0, lsr #0x1b
	bl RtcBCD2HEX
	ldr r1, _020D5F34 ; =0x027FFDE8
	str r0, [r4, #0x4]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsl #0xa
	mov r0, r0, lsr #0x1a
	bl RtcBCD2HEX
	str r0, [r4, #0x8]
	mov r0, r4
	bl RTC_GetDayOfWeek
	str r0, [r4, #0xc]
	b _020D5ED0
_020D5B24:
	ldr r1, _020D5F38 ; =0x027FFDEC
	ldr r4, [r0, #0x8]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsl #0x1a
	mov r0, r0, lsr #0x1a
	bl RtcBCD2HEX
	ldr r1, _020D5F38 ; =0x027FFDEC
	str r0, [r4, #0x0]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsl #0x11
	mov r0, r0, lsr #0x19
	bl RtcBCD2HEX
	ldr r1, _020D5F38 ; =0x027FFDEC
	str r0, [r4, #0x4]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsl #0x9
	mov r0, r0, lsr #0x19
	bl RtcBCD2HEX
	str r0, [r4, #0x8]
	b _020D5ED0
_020D5B74:
	ldr r1, _020D5F34 ; =0x027FFDE8
	ldr r4, [r0, #0x8]
	ldr r0, [r1, #0x0]
	and r0, r0, #0xff
	bl RtcBCD2HEX
	ldr r1, _020D5F34 ; =0x027FFDE8
	str r0, [r4, #0x0]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsl #0x13
	mov r0, r0, lsr #0x1b
	bl RtcBCD2HEX
	ldr r1, _020D5F34 ; =0x027FFDE8
	str r0, [r4, #0x4]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsl #0xa
	mov r0, r0, lsr #0x1a
	bl RtcBCD2HEX
	str r0, [r4, #0x8]
	mov r0, r4
	bl RTC_GetDayOfWeek
	ldr r1, _020D5F38 ; =0x027FFDEC
	str r0, [r4, #0xc]
	ldr r0, [r1, #0x0]
	ldr r1, _020D5F30 ; =0x021D5538
	mov r0, r0, lsl #0x1a
	mov r0, r0, lsr #0x1a
	ldr r4, [r1, #0xc]
	bl RtcBCD2HEX
	ldr r1, _020D5F38 ; =0x027FFDEC
	str r0, [r4, #0x0]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsl #0x11
	mov r0, r0, lsr #0x19
	bl RtcBCD2HEX
	ldr r1, _020D5F38 ; =0x027FFDEC
	str r0, [r4, #0x4]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsl #0x9
	mov r0, r0, lsr #0x19
	bl RtcBCD2HEX
	str r0, [r4, #0x8]
	b _020D5ED0
_020D5C1C:
	ldr r1, _020D5F3C ; =0x027FFDEA
	ldr r2, [r0, #0x8]
	ldrh r0, [r1, #0x0]
	mov r0, r0, lsl #0x1c
	mov r0, r0, lsr #0x1c
	cmp r0, #0x4
	bne _020D5C44
	mov r0, #0x1
	str r0, [r2, #0x0]
	b _020D5ED0
_020D5C44:
	str r5, [r2, #0x0]
	b _020D5ED0
_020D5C4C:
	ldr r1, _020D5F3C ; =0x027FFDEA
	ldr r2, [r0, #0x8]
	ldrh r0, [r1, #0x0]
	mov r0, r0, lsl #0x19
	movs r0, r0, lsr #0x1f
	movne r0, #0x1
	strne r0, [r2, #0x0]
	streq r5, [r2, #0x0]
	b _020D5ED0
_020D5C70:
	ldr r1, _020D5F38 ; =0x027FFDEC
	ldr r4, [r0, #0x8]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsl #0x1d
	mov r0, r0, lsr #0x1d
	str r0, [r4, #0x0]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsl #0x12
	mov r0, r0, lsr #0x1a
	bl RtcBCD2HEX
	ldr r1, _020D5F38 ; =0x027FFDEC
	str r0, [r4, #0x4]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsl #0x9
	mov r0, r0, lsr #0x19
	bl RtcBCD2HEX
	str r0, [r4, #0x8]
	mov r1, r5
	ldr r0, _020D5F38 ; =0x027FFDEC
	str r1, [r4, #0xc]
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x18
	movs r0, r0, lsr #0x1f
	ldrne r0, [r4, #0xc]
	addne r0, r0, #0x1
	strne r0, [r4, #0xc]
	ldr r0, _020D5F38 ; =0x027FFDEC
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x10
	movs r0, r0, lsr #0x1f
	ldrne r0, [r4, #0xc]
	addne r0, r0, #0x2
	strne r0, [r4, #0xc]
	ldr r0, _020D5F38 ; =0x027FFDEC
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x8
	movs r0, r0, lsr #0x1f
	ldrne r0, [r4, #0xc]
	addne r0, r0, #0x4
	strne r0, [r4, #0xc]
	b _020D5ED0
_020D5D14:
	ldr r3, [r0, #0x18]
	cmp r3, #0x0
	bne _020D5DC0
	ldr r1, [r0, #0x8]
	ldr r1, [r1, #0x0]
	cmp r1, #0x1
	bne _020D5D7C
	ldr r2, _020D5F3C ; =0x027FFDEA
	ldrh r1, [r2, #0x0]
	mov r1, r1, lsl #0x1c
	mov r1, r1, lsr #0x1c
	cmp r1, #0x4
	beq _020D5ED0
	add r1, r3, #0x1
	str r1, [r0, #0x18]
	ldrh r0, [r2, #0x0]
	bic r0, r0, #0xf
	orr r0, r0, #0x4
	strh r0, [r2, #0x0]
	bl RTCi_WriteRawStatus2Async
_020D5D64: ; 0x020D5D64
	cmp r0, #0x0
	moveq r1, r5
	ldreq r0, _020D5F30 ; =0x021D5538
	moveq r5, #0x3
	streq r1, [r0, #0x18]
	b _020D5ED0
_020D5D7C:
	ldr r2, _020D5F3C ; =0x027FFDEA
	ldrh r1, [r2, #0x0]
	mov r1, r1, lsl #0x1c
	movs r1, r1, lsr #0x1c
	beq _020D5ED0
	add r1, r3, #0x1
	str r1, [r0, #0x18]
	ldrh r0, [r2, #0x0]
	bic r0, r0, #0xf
	strh r0, [r2, #0x0]
	bl RTCi_WriteRawStatus2Async
_020D5DA8: ; 0x020D5DA8
	cmp r0, #0x0
	moveq r1, r5
	ldreq r0, _020D5F30 ; =0x021D5538
	moveq r5, #0x3
	streq r1, [r0, #0x18]
	b _020D5ED0
_020D5DC0:
	str r5, [r0, #0x18]
	b _020D5ED0
_020D5DC8:
	ldr r3, [r0, #0x18]
	cmp r3, #0x0
	bne _020D5E6C
	ldr r1, [r0, #0x8]
	ldr r1, [r1, #0x0]
	cmp r1, #0x1
	bne _020D5E28
	ldr r2, _020D5F3C ; =0x027FFDEA
	ldrh r1, [r2, #0x0]
	mov r1, r1, lsl #0x19
	movs r1, r1, lsr #0x1f
	bne _020D5ED0
	add r1, r3, #0x1
	str r1, [r0, #0x18]
	ldrh r0, [r2, #0x0]
	orr r0, r0, #0x40
	strh r0, [r2, #0x0]
	bl RTCi_WriteRawStatus2Async
_020D5E10: ; 0x020D5E10
	cmp r0, #0x0
	moveq r1, r5
	ldreq r0, _020D5F30 ; =0x021D5538
	moveq r5, #0x3
	streq r1, [r0, #0x18]
	b _020D5ED0
_020D5E28:
	ldr r2, _020D5F3C ; =0x027FFDEA
	ldrh r1, [r2, #0x0]
	mov r1, r1, lsl #0x19
	movs r1, r1, lsr #0x1f
	beq _020D5ED0
	add r1, r3, #0x1
	str r1, [r0, #0x18]
	ldrh r0, [r2, #0x0]
	bic r0, r0, #0x40
	strh r0, [r2, #0x0]
	bl RTCi_WriteRawStatus2Async
_020D5E54: ; 0x020D5E54
	cmp r0, #0x0
	moveq r1, r5
	ldreq r0, _020D5F30 ; =0x021D5538
	moveq r5, #0x3
	streq r1, [r0, #0x18]
	b _020D5ED0
_020D5E6C:
	str r5, [r0, #0x18]
	b _020D5ED0
_020D5E74:
	ldr r0, _020D5F30 ; =0x021D5538
	mov r1, #0x0
	str r1, [r0, #0x18]
	mov r5, #0x4
	b _020D5ED0
_020D5E88:
	ldr r0, _020D5F30 ; =0x021D5538
	mov r1, #0x0
	str r1, [r0, #0x18]
	cmp r2, #0x4
	addls pc, pc, r2, lsl #0x2
	b _020D5ECC
_020D5EA0:
	b _020D5ECC
_020D5EA4:
	b _020D5EB4
_020D5EA8:
	b _020D5EBC
_020D5EAC:
	b _020D5EC4
_020D5EB0:
	b _020D5ECC
_020D5EB4:
	mov r5, #0x4
	b _020D5ED0
_020D5EBC:
	mov r5, #0x5
	b _020D5ED0
_020D5EC4:
	mov r5, #0x1
	b _020D5ED0
_020D5ECC:
	mov r5, #0x6
_020D5ED0:
	ldr r0, _020D5F30 ; =0x021D5538
	ldr r1, [r0, #0x18]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r2, _020D5F30 ; =0x021D5538
	ldr r1, [r0, #0x0]
	ldr r4, [r2, #0x4]
	cmp r1, #0x0
	movne r1, #0x0
	strne r1, [r0, #0x0]
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r1, [r2, #0x10]
	mov r3, #0x0
	mov r0, r5
	str r3, [r2, #0x4]
	blx r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D5F30: .word 0x021D5538
_020D5F34: .word 0x027FFDE8
_020D5F38: .word 0x027FFDEC
_020D5F3C: .word 0x027FFDEA

	arm_func_start RTC_GetDateTimeAsync
RTC_GetDateTimeAsync: ; 0x020D5F40
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl OS_DisableInterrupts
	ldr r1, _020D5FCC ; =0x021D5538
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	beq _020D5F80
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D5F80:
	mov r2, #0x1
	str r2, [r1, #0x0]
	bl OS_RestoreInterrupts
	ldr r0, _020D5FCC ; =0x021D5538
	mov r2, #0x2
	mov r1, #0x0
	str r2, [r0, #0x14]
	str r1, [r0, #0x18]
	str r7, [r0, #0x8]
	str r6, [r0, #0xc]
	str r5, [r0, #0x4]
	str r4, [r0, #0x10]
	bl RTCi_ReadRawDateTimeAsync
_020D5FB4: ; 0x020D5FB4
	cmp r0, #0x0
	movne r0, #0x0
	moveq r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020D5FCC: .word 0x021D5538

	arm_func_start RTC_GetTime
RTC_GetTime: ; 0x020D5FD0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020D600C ; =RtcGetResultCallback
	mov r2, #0x0
	bl RTC_GetTimeAsync
	ldr r1, _020D6010 ; =0x021D5538
	cmp r0, #0x0
	str r0, [r1, #0x20]
	bne _020D5FF8
	bl RtcWaitBusy
_020D5FF8:
	ldr r0, _020D6010 ; =0x021D5538
	ldr r0, [r0, #0x20]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D600C: .word RtcGetResultCallback
_020D6010: .word 0x021D5538

	arm_func_start RTC_GetTimeAsync
RTC_GetTimeAsync: ; 0x020D6014
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl OS_DisableInterrupts
	ldr r1, _020D608C ; =0x021D5538
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	beq _020D6048
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D6048:
	mov r2, #0x1
	str r2, [r1, #0x0]
	bl OS_RestoreInterrupts
	ldr r0, _020D608C ; =0x021D5538
	mov r2, #0x1
	mov r1, #0x0
	str r2, [r0, #0x14]
	str r1, [r0, #0x18]
	str r6, [r0, #0x8]
	str r5, [r0, #0x4]
	str r4, [r0, #0x10]
	bl RTCi_ReadRawTimeAsync
_020D6078: ; 0x020D6078
	cmp r0, #0x0
	movne r0, #0x0
	moveq r0, #0x3
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D608C: .word 0x021D5538

	arm_func_start RTC_GetDate
RTC_GetDate: ; 0x020D6090
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020D60CC ; =RtcGetResultCallback
	mov r2, #0x0
	bl RTC_GetDateAsync
	ldr r1, _020D60D0 ; =0x021D5538
	cmp r0, #0x0
	str r0, [r1, #0x20]
	bne _020D60B8
	bl RtcWaitBusy
_020D60B8:
	ldr r0, _020D60D0 ; =0x021D5538
	ldr r0, [r0, #0x20]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D60CC: .word RtcGetResultCallback
_020D60D0: .word 0x021D5538

	arm_func_start RTC_GetDateAsync
RTC_GetDateAsync: ; 0x020D60D4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl OS_DisableInterrupts
	ldr r1, _020D6148 ; =0x021D5538
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	beq _020D6108
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D6108:
	mov r2, #0x1
	str r2, [r1, #0x0]
	bl OS_RestoreInterrupts
	ldr r0, _020D6148 ; =0x021D5538
	mov r1, #0x0
	str r1, [r0, #0x14]
	str r1, [r0, #0x18]
	str r6, [r0, #0x8]
	str r5, [r0, #0x4]
	str r4, [r0, #0x10]
	bl RTCi_ReadRawDateAsync
_020D6134: ; 0x020D6134
	cmp r0, #0x0
	movne r0, #0x0
	moveq r0, #0x3
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D6148: .word 0x021D5538

	arm_func_start RTC_Init
RTC_Init: ; 0x020D614C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _020D61C8 ; =0x021D5534
	ldrh r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r0, _020D61CC ; =0x021D5538
	mov r2, #0x0
	mov r3, #0x1
	strh r3, [r1, #0x0]
	str r2, [r0, #0x0]
	str r2, [r0, #0x4]
	str r2, [r0, #0x1c]
	str r2, [r0, #0x8]
	str r2, [r0, #0xc]
	bl PXI_Init
	mov r5, #0x5
	mov r4, #0x1
_020D619C:
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
_020D61A8: ; 0x020D61A8
	cmp r0, #0x0
	beq _020D619C
	ldr r1, _020D61D0 ; =RtcCommonCallback
	mov r0, #0x5
	bl PXI_SetFifoRecvCallback
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D61C8: .word 0x021D5534
_020D61CC: .word 0x021D5538
_020D61D0: .word RtcCommonCallback

	arm_func_start FUN_020D61D4
FUN_020D61D4: ; 0x020D61D4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, r0, lsl #0x8
	and r1, r0, #0x7f00
	mov r0, #0x5
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020D61F0: ; 0x020D61F0
	cmp r0, #0x0
	movge r0, #0x1
	movlt r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start RTCi_WriteRawStatus2Async
RTCi_WriteRawStatus2Async:
	ldr ip, _020D6214 ; =FUN_020D61D4
	mov r0, #0x27
	bx r12
	.balign 4
_020D6214: .word FUN_020D61D4

	arm_func_start RTCi_ReadRawTimeAsync
RTCi_ReadRawTimeAsync:
	ldr ip, _020D6224 ; =FUN_020D61D4
	mov r0, #0x12
	bx r12
	.balign 4
_020D6224: .word FUN_020D61D4

	arm_func_start RTCi_ReadRawDateAsync
RTCi_ReadRawDateAsync:
	ldr ip, _020D6234 ; =FUN_020D61D4
	mov r0, #0x11
	bx r12
	.balign 4
_020D6234: .word FUN_020D61D4

	arm_func_start RTCi_ReadRawDateTimeAsync
RTCi_ReadRawDateTimeAsync:
	ldr ip, _020D6244 ; =FUN_020D61D4
	mov r0, #0x10
	bx r12
	.balign 4
_020D6244: .word FUN_020D61D4

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
	ldr r3, _020D6574 ; =0x02106A20
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
_020D6574: .word 0x02106A20

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
	ldr r0, _020D6698 ; =0x02106A1C
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
_020D6698: .word 0x02106A1C
_020D669C: .word 0x0000016D
