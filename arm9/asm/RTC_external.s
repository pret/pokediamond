	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global UNK_021D5534
UNK_021D5534: ; 0x021D5534
	.space 0x4

	.global UNK_021D5538
UNK_021D5538: ; 0x021D5538
	.space 0x24

	.text

	arm_func_start RtcWaitBusy
RtcWaitBusy: ; 0x020D5914
	ldr ip, _020D5928 ; =UNK_021D5538
_020D5918:
	ldr r0, [r12, #0x0]
	cmp r0, #0x1
	beq _020D5918
	bx lr
	.balign 4
_020D5928: .word UNK_021D5538

	arm_func_start RtcGetResultCallback
RtcGetResultCallback: ; 0x020D592C
	ldr r1, _020D5938 ; =UNK_021D5538
	str r0, [r1, #0x20]
	bx lr
	.balign 4
_020D5938: .word UNK_021D5538

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
	ldr r0, _020D5F30 ; =UNK_021D5538
	ldr r2, _020D5F30 ; =UNK_021D5538
	ldr r1, [r0, #0x18]
	ldr r4, [r2, #0x4]
	cmp r1, #0x0
	movne r1, #0x0
	strne r1, [r0, #0x18]
	ldr r0, _020D5F30 ; =UNK_021D5538
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
	ldr r0, _020D5F30 ; =UNK_021D5538
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
	ldr r0, _020D5F30 ; =UNK_021D5538
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
	ldr r1, _020D5F30 ; =UNK_021D5538
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
	ldreq r0, _020D5F30 ; =UNK_021D5538
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
	ldreq r0, _020D5F30 ; =UNK_021D5538
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
	ldreq r0, _020D5F30 ; =UNK_021D5538
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
	ldreq r0, _020D5F30 ; =UNK_021D5538
	moveq r5, #0x3
	streq r1, [r0, #0x18]
	b _020D5ED0
_020D5E6C:
	str r5, [r0, #0x18]
	b _020D5ED0
_020D5E74:
	ldr r0, _020D5F30 ; =UNK_021D5538
	mov r1, #0x0
	str r1, [r0, #0x18]
	mov r5, #0x4
	b _020D5ED0
_020D5E88:
	ldr r0, _020D5F30 ; =UNK_021D5538
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
	ldr r0, _020D5F30 ; =UNK_021D5538
	ldr r1, [r0, #0x18]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r2, _020D5F30 ; =UNK_021D5538
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
_020D5F30: .word UNK_021D5538
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
	ldr r1, _020D5FCC ; =UNK_021D5538
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
	ldr r0, _020D5FCC ; =UNK_021D5538
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
_020D5FCC: .word UNK_021D5538

	arm_func_start RTC_GetTime
RTC_GetTime: ; 0x020D5FD0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020D600C ; =RtcGetResultCallback
	mov r2, #0x0
	bl RTC_GetTimeAsync
	ldr r1, _020D6010 ; =UNK_021D5538
	cmp r0, #0x0
	str r0, [r1, #0x20]
	bne _020D5FF8
	bl RtcWaitBusy
_020D5FF8:
	ldr r0, _020D6010 ; =UNK_021D5538
	ldr r0, [r0, #0x20]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D600C: .word RtcGetResultCallback
_020D6010: .word UNK_021D5538

	arm_func_start RTC_GetTimeAsync
RTC_GetTimeAsync: ; 0x020D6014
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl OS_DisableInterrupts
	ldr r1, _020D608C ; =UNK_021D5538
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
	ldr r0, _020D608C ; =UNK_021D5538
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
_020D608C: .word UNK_021D5538

	arm_func_start RTC_GetDate
RTC_GetDate: ; 0x020D6090
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020D60CC ; =RtcGetResultCallback
	mov r2, #0x0
	bl RTC_GetDateAsync
	ldr r1, _020D60D0 ; =UNK_021D5538
	cmp r0, #0x0
	str r0, [r1, #0x20]
	bne _020D60B8
	bl RtcWaitBusy
_020D60B8:
	ldr r0, _020D60D0 ; =UNK_021D5538
	ldr r0, [r0, #0x20]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D60CC: .word RtcGetResultCallback
_020D60D0: .word UNK_021D5538

	arm_func_start RTC_GetDateAsync
RTC_GetDateAsync: ; 0x020D60D4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl OS_DisableInterrupts
	ldr r1, _020D6148 ; =UNK_021D5538
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
	ldr r0, _020D6148 ; =UNK_021D5538
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
_020D6148: .word UNK_021D5538

	arm_func_start RTC_Init
RTC_Init: ; 0x020D614C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _020D61C8 ; =UNK_021D5534
	ldrh r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r0, _020D61CC ; =UNK_021D5538
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
_020D61C8: .word UNK_021D5534
_020D61CC: .word UNK_021D5538
_020D61D0: .word RtcCommonCallback
