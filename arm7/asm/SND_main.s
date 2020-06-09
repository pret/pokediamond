	.include "asm/macros.inc"
	.include "global.inc"

    .section .bss

	.global _03807A30
_03807A30: ;0x03807A30
	.space 0x03807A34 - 0x03807A30

	.global _03807A34
_03807A34: ;0x03807A34
	.space 0x03807A54 - 0x03807A34

	.global _03807A54
_03807A54: ;0x03807A54
	.space 0x03807A74 - 0x03807A54

	.global _03807A74
_03807A74: ;0x03807A74
	.space 0x03807AA0 - 0x03807A74

	.global _03807AA0
_03807AA0: ;0x03807AA0
	.space 0x03807F44 - 0x03807AA0

	.global _03807F44
_03807F44: ;0x03807F44
	.space 0x03807F48 - 0x03807F44

    .section .text

	arm_func_start SndThread
SndThread: ; 0x037FC2B0
	stmdb	sp!, {r4, r5, r6, lr}
	bl	SND_InitIntervalTimer
	bl	SND_ExChannelInit
	bl	SND_SeqInit
	bl	SND_AlarmInit
	bl	SND_Enable
	mov	r0, #0
	mov	r1, r0
	mov	r2, r0
	mov	r3, r0
	bl	SND_SetOutputSelector
	mov	r0, #127	; 0x7f
	bl	SND_SetMasterVolume
	bl	SND_StartIntervalTimer
	mov	r4, #1
	mov	r5, #0
_037FC2F0:
	mov	r6, r5
	bl	SND_WaitForIntervalTimer
	cmp	r0, #1
	beq	_037FC308
	cmp	r0, #2
	b	_037FC30C
_037FC308:
	mov	r6, r4
_037FC30C:
	bl	SND_UpdateExChannel
	bl	SND_CommandProc
	mov	r0, r6
	bl	SND_SeqMain
	mov	r0, r6
	bl	SND_ExChannelMain
	bl	SND_UpdateSharedWork
	bl	SND_CalcRandom
	b	_037FC2F0
_037FC330:
	ldr	r0, _037FC344	; =_03807A54
	mov	r1, #1
	mov	r2, #0
	ldr	ip, _037FC348	; =OS_SendMessage
	bx	ip
_037FC344:	.word	_03807A54
_037FC348:	.word	OS_SendMessage

	arm_func_start SNDi_UnlockMutex
SNDi_UnlockMutex: ; 0x037FC34C
	bx	lr

	arm_func_start SNDi_LockMutex
SNDi_LockMutex: ; 0x037FC350
	bx	lr

	arm_func_start SND_SendWakeupMessage
SND_SendWakeupMessage: ; 0x037FC354
	ldr	r0, _037FC368	; =_03807A54
	mov	r1, #2
	mov	r2, #0
	ldr	ip, _037FC36C	; =OS_SendMessage
	bx	ip
_037FC368:	.word	_03807A54
_037FC36C:	.word	OS_SendMessage

	arm_func_start SND_WaitForIntervalTimer
SND_WaitForIntervalTimer: ; 0x037FC370
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037FC398	; =_03807A54
	add	r1, sp, #0
	mov	r2, #1
	bl	OS_ReceiveMessage
	ldr	r0, [sp]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FC398:	.word	_03807A54

	arm_func_start SND_StopIntervalTimer
SND_StopIntervalTimer: ; 0x037FC39C
	ldr	r0, _037FC3A8	; =_03807A74
	ldr	ip, _037FC3AC	; =OS_CancelAlarm
	bx	ip
_037FC3A8:	.word	_03807A74
_037FC3AC:	.word	OS_CancelAlarm

	arm_func_start SND_StartIntervalTimer
SND_StartIntervalTimer: ; 0x037FC3B0
	stmfd	sp!, {lr}
	sub	sp, sp, #12
	bl	OS_GetTick
	mov	ip, r0
	ldr	r0, _037FC3FC	; =_037FC330
	str	r0, [sp, #4]
	mov	r0, #0
	str	r0, [sp, #8]
	ldr	r3, _037FC400	; =0x00000AA8
	str	r0, [sp]
	ldr	r0, _037FC404	; =_03807A74
	mov	r2, #65536	; 0x10000
	adds	ip, ip, r2
	adc	r2, r1, #0
	mov	r1, ip
	bl	OS_SetPeriodicAlarm
	add	sp, sp, #12
	ldmia	sp!, {lr}
	bx	lr
_037FC3FC:	.word	_037FC330
_037FC400:	.word	0x00000AA8
_037FC404:	.word	_03807A74

	arm_func_start SND_InitIntervalTimer
SND_InitIntervalTimer: ; 0x037FC408
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037FC434	; =_03807A54
	ldr	r1, _037FC438	; =_03807A34
	mov	r2, #8
	bl	OS_InitMessageQueue
	ldr	r0, _037FC43C	; =_03807A74
	bl	OS_CreateAlarm
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FC434:	.word	_03807A54
_037FC438:	.word	_03807A34
_037FC43C:	.word	_03807A74

	arm_func_start SND_CreateThread
SND_CreateThread: ; 0x037FC440
	stmfd	sp!, {lr}
	sub	sp, sp, #12
	mov	r1, #1024	; 0x400
	str	r1, [sp]
	str	r0, [sp, #4]
	ldr	r0, _037FC47C	; =_03807AA0
	ldr	r1, _037FC480	; =SndThread
	mov	r2, #0
	ldr	r3, _037FC484	; =_03807F44
	bl	OS_CreateThread
	ldr	r0, _037FC47C	; =_03807AA0
	bl	OS_WakeupThreadDirect
	add	sp, sp, #12
	ldmia	sp!, {lr}
	bx	lr
_037FC47C:	.word	_03807AA0
_037FC480:	.word	SndThread
_037FC484:	.word	_03807F44

	arm_func_start SND_Init
SND_Init: ; 0x037FC488
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	ldr	r0, _037FC4BC	; =_03807A30
	ldr	r1, [r0]
	cmp	r1, #0
	bne	_037FC4B4
	mov	r1, #1
	str	r1, [r0]
	bl	SND_CommandInit
	mov	r0, r4
	bl	SND_CreateThread
_037FC4B4:
	ldmia	sp!, {r4, lr}
	bx	lr
_037FC4BC:	.word	_03807A30
