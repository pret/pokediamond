	.include "asm/macros.inc"
	.include "global.inc"

    .section .bss

	.global _038090EC
_038090EC: ;0x038090EC
	.space 0x0380910C - 0x038090EC

	.global _0380910C
_0380910C: ;0x0380910C
	.space 0x0380912C - 0x0380910C

    .section .text

	arm_func_start ReadDriverInfo
ReadDriverInfo: ; 0x037FF6E4
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	ldr	r0, _037FF74C	; =SNDi_Work
	mov	r1, r5
	mov	r2, #4480	; 0x1180
	bl	MIi_CpuCopy32
	ldr	r1, _037FF74C	; =SNDi_Work
	add	r0, r5, #4096	; 0x1000
	str	r1, [r0, #448]	; 0x1c0
	mov	r4, #0
_037FF710:
	mov	r0, r4
	bl	SND_GetChannelControl
	add	r1, r5, r4, lsl #2
	add	r1, r1, #4096	; 0x1000
	str	r0, [r1, #384]	; 0x180
	add	r4, r4, #1
	cmp	r4, #16
	blt	_037FF710
	mov	r0, #0
	bl	SND_GetLockedChannel
	add	r1, r5, #4096	; 0x1000
	str	r0, [r1, #452]	; 0x1c4
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FF74C:	.word	SNDi_Work

	arm_func_start StopTimer
StopTimer: ; 0x037FF750
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r9, r2
	mov	r5, r3
	bl	OS_DisableInterrupts
	mov	r4, r0
	mov	r8, #0
	b	_037FF790
_037FF778:
	ands	r0, r9, #1
	beq	_037FF788
	mov	r0, r8
	bl	SND_StopAlarm
_037FF788:
	add	r8, r8, #1
	mov	r9, r9, lsr #1
_037FF790:
	cmp	r8, #8
	bge	_037FF7A0
	cmp	r9, #0
	bne	_037FF778
_037FF7A0:
	mov	r8, #0
	b	_037FF7C4
_037FF7A8:
	ands	r0, r7, #1
	beq	_037FF7BC
	mov	r0, r8
	mov	r1, r5
	bl	SND_StopChannel
_037FF7BC:
	add	r8, r8, #1
	mov	r7, r7, lsr #1
_037FF7C4:
	cmp	r8, #16
	bge	_037FF7D4
	cmp	r7, #0
	bne	_037FF7A8
_037FF7D4:
	ands	r0, r6, #1
	movne	r1, #0
	ldrne	r0, _037FF80C	; =0x04000508
	strneb	r1, [r0]
	ands	r0, r6, #2
	movne	r1, #0
	ldrne	r0, _037FF810	; =0x04000509
	strneb	r1, [r0]
	mov	r0, r4
	bl	OS_RestoreInterrupts
	bl	SND_UpdateSharedWork
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037FF80C:	.word	0x04000508
_037FF810:	.word	0x04000509

	arm_func_start StartTimer
StartTimer: ; 0x037FF814
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r5, r2
	bl	OS_DisableInterrupts
	mov	r4, r0
	mov	r2, #0
	b	_037FF858
_037FF838:
	ands	r0, r7, #1
	movne	r0, r2, lsl #4
	addne	r0, r0, #67108864	; 0x4000000
	ldrneb	r1, [r0, #1027]	; 0x403
	orrne	r1, r1, #128	; 0x80
	strneb	r1, [r0, #1027]	; 0x403
	add	r2, r2, #1
	mov	r7, r7, lsr #1
_037FF858:
	cmp	r2, #16
	bge	_037FF868
	cmp	r7, #0
	bne	_037FF838
_037FF868:
	ands	r0, r6, #1
	beq	_037FF8A0
	ands	r0, r6, #2
	ldreq	r1, _037FF8FC	; =0x04000508
	ldreqb	r0, [r1]
	orreq	r0, r0, #128	; 0x80
	streqb	r0, [r1]
	beq	_037FF8B4
	ldr	r2, _037FF8FC	; =0x04000508
	ldrh	r1, [r2]
	ldr	r0, _037FF900	; =0x00008080
	orr	r0, r1, r0
	strh	r0, [r2]
	b	_037FF8B4
_037FF8A0:
	ands	r0, r6, #2
	ldrne	r1, _037FF904	; =0x04000509
	ldrneb	r0, [r1]
	orrne	r0, r0, #128	; 0x80
	strneb	r0, [r1]
_037FF8B4:
	mov	r6, #0
	b	_037FF8D4
_037FF8BC:
	ands	r0, r5, #1
	beq	_037FF8CC
	mov	r0, r6
	bl	SND_StartAlarm
_037FF8CC:
	add	r6, r6, #1
	mov	r5, r5, lsr #1
_037FF8D4:
	cmp	r6, #8
	bge	_037FF8E4
	cmp	r5, #0
	bne	_037FF8BC
_037FF8E4:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	bl	SND_UpdateSharedWork
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FF8FC:	.word	0x04000508
_037FF900:	.word	0x00008080
_037FF904:	.word	0x04000509

	arm_func_start SetChannelPan
SetChannelPan: ; 0x037FF908
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, r1
	mov	r4, #0
	b	_037FF938
_037FF91C:
	ands	r0, r6, #1
	beq	_037FF930
	mov	r0, r4
	mov	r1, r5
	bl	SND_SetChannelPan
_037FF930:
	add	r4, r4, #1
	mov	r6, r6, lsr #1
_037FF938:
	cmp	r4, #16
	bge	_037FF948
	cmp	r6, #0
	bne	_037FF91C
_037FF948:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start SetChannelVolume
SetChannelVolume: ; 0x037FF950
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r5, r2
	mov	r4, #0
	b	_037FF98C
_037FF96C:
	ands	r0, r7, #1
	beq	_037FF984
	mov	r0, r4
	mov	r1, r6
	mov	r2, r5
	bl	SND_SetChannelVolume
_037FF984:
	add	r4, r4, #1
	mov	r7, r7, lsr #1
_037FF98C:
	cmp	r4, #16
	bge	_037FF99C
	cmp	r7, #0
	bne	_037FF96C
_037FF99C:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr

	arm_func_start SetChannelTimer
SetChannelTimer: ; 0x037FF9A8
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, r1
	mov	r4, #0
	b	_037FF9D8
_037FF9BC:
	ands	r0, r6, #1
	beq	_037FF9D0
	mov	r0, r4
	mov	r1, r5
	bl	SND_SetChannelTimer
_037FF9D0:
	add	r4, r4, #1
	mov	r6, r6, lsr #1
_037FF9D8:
	cmp	r4, #16
	bge	_037FF9E8
	cmp	r6, #0
	bne	_037FF9BC
_037FF9E8:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start InitPXI
InitPXI: ; 0x037FF9F0
	mov	r0, #7
	ldr	r1, _037FFA00	; =PxiFifoCallback
	ldr	ip, _037FFA04	; =PXI_SetFifoRecvCallback
	bx	ip
_037FFA00:	.word	PxiFifoCallback
_037FFA04:	.word	PXI_SetFifoRecvCallback

	arm_func_start PxiFifoCallback
PxiFifoCallback: ; 0x037FFA08
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r1
	bl	OS_DisableInterrupts
	mov	r4, r0
	cmp	r5, #33554432	; 0x2000000
	bcc	_037FFA38
	ldr	r0, _037FFA58	; =_038090EC
	mov	r1, r5
	mov	r2, #0
	bl	OS_SendMessage
	b	_037FFA44
_037FFA38:
	cmp	r5, #0
	bne	_037FFA44
	bl	SND_SendWakeupMessage
_037FFA44:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FFA58:	.word	_038090EC

	arm_func_start SND_CommandProc
SND_CommandProc: ; 0x037FFA5C
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #52	; 0x34
	ldr	r7, _037FFEC4	; =SNDi_SharedWork
	ldr	r9, _037FFEC8	; =_038090EC
	add	r8, sp, #24
	mov	r4, #0
	ldr	r6, _037FFECC	; =0x0000FFFF
	ldr	r5, _037FFED0	; =0x003FFFFF
	b	_037FFEA0
_037FFA80:
	ldr	lr, [sp, #24]
	b	_037FFE88
_037FFA88:
	add	ip, sp, #28
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1}
	stmia	ip, {r0, r1}
	ldr	r0, [sp, #32]
	cmp	r0, #33	; 0x21
	addls	pc, pc, r0, lsl #2
	b	_037FFE84
	b	_037FFB34
	b	_037FFB4C
	b	_037FFB58
	b	_037FFB70
	b	_037FFB7C
	b	_037FFB8C
	b	_037FFB9C
	b	_037FFBB4
	b	_037FFBDC
	b	_037FFBF0
	b	_037FFC04
	b	_037FFC20
	b	_037FFC38
	b	_037FFC50
	b	_037FFD08
	b	_037FFD74
	b	_037FFDA8
	b	_037FFC68
	b	_037FFCB0
	b	_037FFCD4
	b	_037FFCE4
	b	_037FFCF8
	b	_037FFDD4
	b	_037FFDE0
	b	_037FFDEC
	b	_037FFDF8
	b	_037FFE10
	b	_037FFE20
	b	_037FFE30
	b	_037FFE70
	b	_037FFE40
	b	_037FFE50
	b	_037FFE60
	b	_037FFE7C
_037FFB34:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	ldr	r3, [sp, #48]	; 0x30
	bl	SND_StartSeq
	b	_037FFE84
_037FFB4C:
	ldr	r0, [sp, #36]	; 0x24
	bl	SND_StopSeq
	b	_037FFE84
_037FFB58:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	ldr	r3, [sp, #48]	; 0x30
	bl	SND_PrepareSeq
	b	_037FFE84
_037FFB70:
	ldr	r0, [sp, #36]	; 0x24
	bl	SND_StartPreparedSeq
	b	_037FFE84
_037FFB7C:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SND_PauseSeq
	b	_037FFE84
_037FFB8C:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SND_SkipSeq
	b	_037FFE84
_037FFB9C:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	ldr	r3, [sp, #48]	; 0x30
	bl	SNDi_SetPlayerParam
	b	_037FFE84
_037FFBB4:
	ldr	r1, [sp, #36]	; 0x24
	mov	r0, r1, lsr #24
	and	r0, r0, #255	; 0xff
	str	r0, [sp]
	bic	r0, r1, #-16777216	; 0xff000000
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	ldr	r3, [sp, #48]	; 0x30
	bl	SNDi_SetTrackParam
	b	_037FFE84
_037FFBDC:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	bl	SND_SetTrackMute
	b	_037FFE84
_037FFBF0:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	bl	SND_SetTrackAllocatableChannel
	b	_037FFE84
_037FFC04:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	mov	r2, r2, lsl #16
	mov	r2, r2, asr #16
	bl	SND_SetPlayerLocalVariable
	b	_037FFE84
_037FFC20:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	mov	r1, r1, lsl #16
	mov	r1, r1, asr #16
	bl	SND_SetPlayerGlobalVariable
	b	_037FFE84
_037FFC38:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	ldr	r3, [sp, #48]	; 0x30
	bl	StartTimer
	b	_037FFE84
_037FFC50:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	ldr	r3, [sp, #48]	; 0x30
	bl	StopTimer
	b	_037FFE84
_037FFC68:
	ldr	r1, [sp, #44]	; 0x2c
	mov	r0, r1, lsr #29
	and	r0, r0, #1
	str	r0, [sp]
	mov	r0, r1, lsr #28
	and	r0, r0, #1
	str	r0, [sp, #4]
	mov	r0, r1, lsr #27
	and	r0, r0, #1
	str	r0, [sp, #8]
	mov	r0, r1, lsr #31
	and	r0, r0, #1
	mov	r1, r1, lsr #30
	and	r1, r1, #1
	ldr	r2, [sp, #36]	; 0x24
	ldr	r3, [sp, #40]	; 0x28
	bl	SND_SetupCapture
	b	_037FFE84
_037FFCB0:
	ldr	r0, [sp, #48]	; 0x30
	str	r0, [sp, #4]
	ldr	r3, [sp, #44]	; 0x2c
	str	r4, [sp]
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	mov	r2, #0
	bl	SND_SetupAlarm
	b	_037FFE84
_037FFCD4:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SetChannelTimer
	b	_037FFE84
_037FFCE4:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	bl	SetChannelVolume
	b	_037FFE84
_037FFCF8:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SetChannelPan
	b	_037FFE84
_037FFD08:
	ldr	r3, [sp, #48]	; 0x30
	ldr	r1, [sp, #36]	; 0x24
	ldr	r0, [sp, #44]	; 0x2c
	and	r2, r3, r6
	str	r2, [sp]
	and	r2, r0, r5
	str	r2, [sp, #4]
	mov	r2, r0, lsr #24
	and	r2, r2, #127	; 0x7f
	str	r2, [sp, #8]
	mov	r0, r0, lsr #22
	and	r0, r0, #3
	str	r0, [sp, #12]
	and	r0, r6, r1, lsr #16
	str	r0, [sp, #16]
	mov	r0, r3, lsr #16
	and	r0, r0, #127	; 0x7f
	str	r0, [sp, #20]
	and	r0, r1, r6
	ldr	r1, [sp, #40]	; 0x28
	bic	r1, r1, #-134217728	; 0xf8000000
	mov	r2, r3, lsr #24
	and	r2, r2, #3
	mov	r3, r3, lsr #26
	and	r3, r3, #3
	bl	SND_SetupChannelPcm
	b	_037FFE84
_037FFD74:
	ldr	r1, [sp, #44]	; 0x2c
	ldr	r3, [sp, #40]	; 0x28
	and	r0, r6, r1, lsr #8
	str	r0, [sp]
	and	r0, r1, #127	; 0x7f
	str	r0, [sp, #4]
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #48]	; 0x30
	and	r2, r3, #127	; 0x7f
	mov	r3, r3, lsr #8
	and	r3, r3, #3
	bl	SND_SetupChannelPsg
	b	_037FFE84
_037FFDA8:
	ldr	r3, [sp, #44]	; 0x2c
	ldr	r2, [sp, #40]	; 0x28
	and	r0, r3, #127	; 0x7f
	str	r0, [sp]
	ldr	r0, [sp, #36]	; 0x24
	and	r1, r2, #127	; 0x7f
	mov	r2, r2, lsr #8
	and	r2, r2, #3
	and	r3, r6, r3, lsr #8
	bl	SND_SetupChannelNoise
	b	_037FFE84
_037FFDD4:
	ldr	r0, [sp, #36]	; 0x24
	bl	SNDi_SetSurroundDecay
	b	_037FFE84
_037FFDE0:
	ldr	r0, [sp, #36]	; 0x24
	bl	SND_SetMasterVolume
	b	_037FFE84
_037FFDEC:
	ldr	r0, [sp, #36]	; 0x24
	bl	SND_SetMasterPan
	b	_037FFE84
_037FFDF8:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	ldr	r2, [sp, #44]	; 0x2c
	ldr	r3, [sp, #48]	; 0x30
	bl	SND_SetOutputSelector
	b	_037FFE84
_037FFE10:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SND_LockChannel
	b	_037FFE84
_037FFE20:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SND_UnlockChannel
	b	_037FFE84
_037FFE30:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SND_StopUnlockedChannel
	b	_037FFE84
_037FFE40:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SND_InvalidateSeq
	b	_037FFE84
_037FFE50:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SND_InvalidateBank
	b	_037FFE84
_037FFE60:
	ldr	r0, [sp, #36]	; 0x24
	ldr	r1, [sp, #40]	; 0x28
	bl	SND_InvalidateWave
	b	_037FFE84
_037FFE70:
	ldr	r0, [sp, #36]	; 0x24
	str	r0, [r7]
	b	_037FFE84
_037FFE7C:
	ldr	r0, [sp, #36]	; 0x24
	bl	ReadDriverInfo
_037FFE84:
	ldr	lr, [sp, #28]
_037FFE88:
	cmp	lr, #0
	bne	_037FFA88
	ldr	r1, [r7]
	ldr	r0, [r1]
	add	r0, r0, #1
	str	r0, [r1]
_037FFEA0:
	mov	r0, r9
	mov	r1, r8
	mov	r2, r4
	bl	OS_ReceiveMessage
	cmp	r0, #0
	bne	_037FFA80
	add	sp, sp, #52	; 0x34
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037FFEC4:	.word	SNDi_SharedWork
_037FFEC8:	.word	_038090EC
_037FFECC:	.word	0x0000FFFF
_037FFED0:	.word	0x003FFFFF

	arm_func_start SND_CommandInit
SND_CommandInit: ; 0x037FFED4
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037FFF08	; =_038090EC
	ldr	r1, _037FFF0C	; =_0380910C
	mov	r2, #8
	bl	OS_InitMessageQueue
	bl	InitPXI
	mov	r1, #0
	ldr	r0, _037FFF10	; =SNDi_SharedWork
	str	r1, [r0]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FFF08:	.word	_038090EC
_037FFF0C:	.word	_0380910C
_037FFF10:	.word	SNDi_SharedWork
