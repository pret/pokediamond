	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

	arm_func_start PushCommand_impl
PushCommand_impl: ; 0x020CE66C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r0, #0x1
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl SND_AllocCommand
_020CE68C:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7, lr}
	bxeq lr
	str r7, [r0, #0x4]
	str r6, [r0, #0x8]
	str r5, [r0, #0xc]
	ldr r1, [sp, #0x18]
	str r4, [r0, #0x10]
	str r1, [r0, #0x14]
	bl SND_PushCommand
	add sp, sp, #0x4
	ldmia sp!, {r4-r7, lr}
	bx lr

	arm_func_start SNDi_SetTrackParam
SNDi_SetTrackParam: ; 0x020CE6C4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r12, [sp, #0x8]
	mov lr, r2
	str r3, [sp, #0x0]
	mov r2, r1
	orr r1, r0, r12, lsl #0x18
	mov r3, lr
	mov r0, #0x7
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020CE6F8
FUN_020CE6F8: ; 0x020CE6F8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r12, r2
	str r3, [sp, #0x0]
	mov r1, r0
	mov r2, lr
	mov r3, r12
	mov r0, #0x6
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_ResetMasterPan
SND_ResetMasterPan: ; 0x020CE72C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, #0x0
	mov r3, r2
	mov r0, #0x18
	mvn r1, #0x0
	str r2, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetMasterPan
SND_SetMasterPan: ; 0x020CE758
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, #0x0
	mov r1, r0
	mov r3, r2
	mov r0, #0x18
	str r2, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetOutputSelector
SND_SetOutputSelector: ; 0x020CE784
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r12, r2
	str r3, [sp, #0x0]
	mov r1, r0
	mov r2, lr
	mov r3, r12
	mov r0, #0x19
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_InvalidateWaveData
SND_InvalidateWaveData: ; 0x020CE7B8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r3, #0x0
	mov r1, r0
	mov r0, #0x20
	str r3, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_InvalidateBankData
SND_InvalidateBankData: ; 0x020CE7E4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r3, #0x0
	mov r1, r0
	mov r0, #0x1f
	str r3, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_InvalidateSeqData
SND_InvalidateSeqData: ; 0x020CE810
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r3, #0x0
	mov r1, r0
	mov r0, #0x1e
	str r3, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetupChannelPcm
SND_SetupChannelPcm: ; 0x020CE83C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r12, [sp, #0x18]
	mov r3, r3, lsl #0x1a
	orr r4, r3, r1, lsl #0x18
	ldr r5, [sp, #0x24]
	mov r3, r12, lsl #0x18
	ldr r1, [sp, #0x1c]
	ldr r12, [sp, #0x10]
	orr r4, r4, r5, lsl #0x10
	orr r4, r12, r4
	ldr lr, [sp, #0x20]
	orr r3, r3, r1, lsl #0x16
	ldr r12, [sp, #0x14]
	orr r1, r0, lr, lsl #0x10
	orr r3, r12, r3
	mov r0, #0xe
	str r4, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start SND_SetChannelPan
SND_SetChannelPan: ; 0x020CE894
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r3, #0x0
	mov r1, r0
	mov r0, #0x15
	str r3, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetChannelVolume
SND_SetChannelVolume: ; 0x020CE8C0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r3, r2
	mov r12, #0x0
	mov r1, r0
	mov r2, lr
	mov r0, #0x14
	str r12, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetChannelTimer
SND_SetChannelTimer: ; 0x020CE8F4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r3, #0x0
	mov r1, r0
	mov r0, #0x13
	str r3, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_UnlockChannel
SND_UnlockChannel: ; 0x020CE920
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r3, #0x0
	mov r1, r0
	mov r0, #0x1b
	str r3, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_LockChannel
SND_LockChannel: ; 0x020CE94C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r3, #0x0
	mov r1, r0
	mov r0, #0x1a
	str r3, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetupAlarm
SND_SetupAlarm: ; 0x020CE978
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r4, r2
	mov r5, r1
	ldr r2, [sp, #0x18]
	mov r6, r0
	mov r1, r3
	bl SNDi_SetAlarmHandler
_020CE998:
	str r0, [sp]
	mov r1, r6
	mov r2, r5
	mov r3, r4
	mov r0, #0x12
	bl PushCommand_impl
	add sp, sp, #0x8
	ldmia sp!, {r4-r6, lr}
	bx lr

	arm_func_start SND_SetupCapture
SND_SetupCapture: ; 0x020CE9BC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, r0, lsl #0x1f
	orr r0, r0, r1, lsl #0x1e
	ldr r12, [sp, #0x8]
	mov r1, r2
	orr r0, r0, r12, lsl #0x1d
	ldr r2, [sp, #0xc]
	mov lr, #0x0
	orr r0, r0, r2, lsl #0x1c
	ldr r12, [sp, #0x10]
	mov r2, r3
	orr r3, r0, r12, lsl #0x1b
	mov r0, #0x11
	str lr, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_StopTimer
SND_StopTimer: ; 0x020CEA08
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r7, r2
	mov r9, r0
	mov r8, r1
	mov r6, r3
	mov r4, r7
	mov r5, #0x0
	b _020CEA44
_020CEA2C:
	ands r0, r4, #0x1
	beq _020CEA3C
	mov r0, r5
	bl SNDi_IncAlarmId
_020CEA3C:
	add r5, r5, #0x1
	mov r4, r4, lsr #0x1
_020CEA44:
	cmp r5, #0x8
	bge _020CEA54
	cmp r4, #0x0
	bne _020CEA2C
_020CEA54:
	mov r1, r9
	mov r2, r8
	mov r3, r7
	mov r0, #0xd
	str r6, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start SND_StartTimer
SND_StartTimer: ; 0x020CEA78
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r12, r2
	str r3, [sp, #0x0]
	mov r1, r0
	mov r2, lr
	mov r3, r12
	mov r0, #0xc
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetTrackAllocatableChannel
SND_SetTrackAllocatableChannel: ; 0x020CEAAC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r3, r2
	mov r12, #0x0
	mov r1, r0
	mov r2, lr
	mov r0, #0x9
	str r12, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetTrackPan
SND_SetTrackPan: ; 0x020CEAE0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r3, r2
	mov r12, #0x1
	mov r2, #0x9
	str r12, [sp, #0x0]
	bl SNDi_SetTrackParam
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetTrackPitch
SND_SetTrackPitch: ; 0x020CEB08
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r3, r2
	mov r12, #0x2
	mov r2, #0xc
	str r12, [sp, #0x0]
	bl SNDi_SetTrackParam
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetPlayerChannelPriority
SND_SetPlayerChannelPriority: ; 0x020CEB30
	ldr ip, _020CEB44 ; =FUN_020CE6F8
	mov r2, r1
	mov r1, #0x4
	mov r3, #0x1
	bx r12
	.balign 4
_020CEB44: .word FUN_020CE6F8

	arm_func_start SND_SetPlayerVolume
SND_SetPlayerVolume: ; 0x020CEB48
	ldr ip, _020CEB5C ; =FUN_020CE6F8
	mov r2, r1
	mov r1, #0x6
	mov r3, #0x2
	bx r12
	.balign 4
_020CEB5C: .word FUN_020CE6F8

	arm_func_start SND_PauseSeq
SND_PauseSeq: ; 0x020CEB60
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r3, #0x0
	mov r1, r0
	mov r0, #0x4
	str r3, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_StartPreparedSeq
SND_StartPreparedSeq: ; 0x020CEB8C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, #0x0
	mov r1, r0
	mov r3, r2
	mov r0, #0x3
	str r2, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_PrepareSeq
SND_PrepareSeq: ; 0x020CEBB8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r12, r2
	str r3, [sp, #0x0]
	mov r1, r0
	mov r2, lr
	mov r3, r12
	mov r0, #0x2
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_StopSeq
SND_StopSeq: ; 0x020CEBEC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, #0x0
	mov r1, r0
	mov r3, r2
	mov r0, #0x1
	str r2, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SNDi_UnlockMutex
SNDi_UnlockMutex: ; 0x020CEC18
	ldr ip, _020CEC24 ; =OS_UnlockMutex
	ldr r0, _020CEC28 ; =0x021D3820
	bx r12
	.balign 4
_020CEC24: .word OS_UnlockMutex
_020CEC28: .word 0x021D3820

	arm_func_start SNDi_LockMutex
SNDi_LockMutex: ; 0x020CEC2C
	ldr ip, _020CEC38 ; =OS_LockMutex
	ldr r0, _020CEC3C ; =0x021D3820
	bx r12
	.balign 4
_020CEC38: .word OS_LockMutex
_020CEC3C: .word 0x021D3820

	arm_func_start SND_Init
SND_Init: ; 0x020CEC40
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020CEC84 ; =0x021D381C
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020CEC88 ; =0x021D3820
	mov r2, #0x1
	str r2, [r1, #0x0]
	bl OS_InitMutex
	bl SND_CommandInit
	bl SND_AlarmInit
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CEC84: .word 0x021D381C
_020CEC88: .word 0x021D3820

	arm_func_start IsCommandAvailable
IsCommandAvailable:
	stmdb sp!, {r4,lr}
	bl OS_IsRunOnEmulator
_020CEC94:
	cmp r0, #0x0
	moveq r0, #0x1
	ldmeqia sp!, {r4, lr}
	bxeq lr
	bl OS_DisableInterrupts
	ldr r1, _020CECD0
	mov r2, #0x10
	str r2, [r1]
	ldr r4, [r1]
	bl OS_RestoreInterrupts
	cmp r4, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	ldmia sp!, {r4, lr}
	bx lr
_020CECD0: .word 0x04FFF200

	arm_func_start AllocCommand
AllocCommand: ; 0x020CECD4
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020CED24 ; =0x021D3838
	ldr r4, [r1, #0x0]
	cmp r4, #0x0
	bne _020CECFC
	bl OS_RestoreInterrupts
_020CECF0:
	mov r0, #0x0
	ldmia sp!, {r4, lr}
	bx lr
_020CECFC:
	ldr r2, [r4, #0x0]
	str r2, [r1, #0x0]
	cmp r2, #0x0
	ldreq r1, _020CED28 ; =0x021D3848
	moveq r2, #0x0
	streq r2, [r1, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CED24: .word 0x021D3838
_020CED28: .word 0x021D3848

	arm_func_start RequestCommandProc
RequestCommandProc: ; 0x020CED2C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, #0x7
	mov r4, #0x0
_020CED3C:
	mov r0, r5
	mov r1, r4
	mov r2, r4
	bl PXI_SendWordByFifo
_020CED4C:
	cmp r0, #0
	blt _020CED3C
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start InitPXI
InitPXI: ; 0x020CED60
	stmdb sp!, {r4-r6,lr}
	ldr r1, _020CEDC8 ; =PxiFifoCallback
	mov r0, #0x7
	bl PXI_SetFifoRecvCallback
	bl IsCommandAvailable
_020CED74:
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6, lr}
	bxeq lr
	mov r0, #0x7
	mov r1, #0x1
	bl PXI_IsCallbackReady
	cmp r0, #0x0
	ldmneia sp!, {r4-r6, lr}
	bxne lr
	mov r6, #0x64
	mov r5, #0x7
	mov r4, #0x1
_020CEDA4:
	mov r0, r6
	bl OS_SpinWait
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
	cmp r0, #0x0
	beq _020CEDA4
	ldmia sp!, {r4-r6, lr}
	bx lr
_020CEDC8: .word PxiFifoCallback

	arm_func_start PxiFifoCallback
PxiFifoCallback: ; 0x020CEDCC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	bl OS_DisableInterrupts
	mov r4, r0
	mov r0, r5
	bl SNDi_CallAlarmHandler
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start SND_CountWaitingCommand
SND_CountWaitingCommand: ; 0x020CEDFC
	stmdb sp!, {r4,lr}
	bl SND_CountFreeCommand
	mov r4, r0
	bl SND_CountReservedCommand
	rsb r1, r4, #0x100
	sub r0, r1, r0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start SND_CountReservedCommand
SND_CountReservedCommand: ; 0x020CEE1C
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020CEE58 ; =0x021D3840
	mov r4, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020CEE48
_020CEE38:
	ldr r1, [r1, #0x0]
	add r4, r4, #0x1
	cmp r1, #0x0
	bne _020CEE38
_020CEE48:
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CEE58: .word 0x021D3840

	arm_func_start SND_CountFreeCommand
SND_CountFreeCommand: ; 0x020CEE5C
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020CEE98 ; =0x021D3838
	mov r4, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020CEE88
_020CEE78:
	ldr r1, [r1, #0x0]
	add r4, r4, #0x1
	cmp r1, #0x0
	bne _020CEE78
_020CEE88:
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CEE98: .word 0x021D3838

	arm_func_start SND_IsFinishedCommandTag
SND_IsFinishedCommandTag:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _020CEEEC ; =0x021D383C
	ldr r1, [r1, #0x0]
	cmp r4, r1
	bls _020CEECC
	sub r1, r4, r1
	cmp r1, #0x80000000
	movcc r4, #0x0
	movcs r4, #0x1
	b _020CEEDC
_020CEECC:
	sub r1, r1, r4
	cmp r1, #0x80000000
	movcc r4, #0x1
	movcs r4, #0x0
_020CEEDC:
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CEEEC: .word 0x021D383C

	arm_func_start SND_GetCurrentCommandTag
SND_GetCurrentCommandTag: ; 0x020CEEF0
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020CEF24 ; =0x021D3840
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	ldreq r1, _020CEF28 ; =0x021D383C
	ldreq r4, [r1, #0x0]
	ldrne r1, _020CEF2C ; =0x021D3858
	ldrne r4, [r1, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CEF24: .word 0x021D3840
_020CEF28: .word 0x021D383C
_020CEF2C: .word 0x021D3858

	arm_func_start SND_WaitForCommandProc
SND_WaitForCommandProc: ; 0x020CEF30
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl SND_IsFinishedCommandTag
_020CEF40:
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5, lr}
	bxne lr
	mov r4, #0x0
_020CEF54:
	mov r0, r4
	bl SND_RecvCommandReply
	cmp r0, #0x0
	bne _020CEF54
	mov r0, r5
	bl SND_IsFinishedCommandTag
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5, lr}
	bxne lr
	bl RequestCommandProc
	mov r0, r5
	bl SND_IsFinishedCommandTag
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5, lr}
	bxne lr
	mov r4, #0x1
_020CEF9C:
	mov r0, r4
	bl SND_RecvCommandReply
	mov r0, r5
	bl SND_IsFinishedCommandTag
	cmp r0, #0x0
	beq _020CEF9C
	add sp, sp, #0x4
	ldmia sp!, {r4-r5, lr}
	bx lr

	arm_func_start SND_FlushCommand
SND_FlushCommand: ; 0x020CEFC0
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020CF164 ; =0x021D3840
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020CEFF8
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r9,lr}
	bx lr
_020CEFF8:
	ldr r1, _020CF168 ; =0x021D3854
	ldr r1, [r1, #0x0]
	cmp r1, #0x8
	blt _020CF03C
	ands r1, r5, #0x1
	bne _020CF024
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r9,lr}
	bx lr
_020CF024:
	mov r0, #0x1
	bl SND_RecvCommandReply
	ldr r0, _020CF168 ; =0x021D3854
	ldr r0, [r0, #0x0]
	cmp r0, #0x8
	bge _020CF024
_020CF03C:
	ldr r0, _020CF16C ; =0x021D3B00
	mov r1, #0x1800
	bl DC_FlushRange
	ldr r1, _020CF164 ; =0x021D3840
	mov r0, #0x7
	ldr r1, [r1, #0x0]
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020CF05C:
	cmp r0, #0x0
	bge _020CF0E0
	ands r0, r5, #0x1
	bne _020CF084
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r9, lr}
	bx lr
_020CF084:
	ldr r1, _020CF164
	mov r0, #0x7
	ldr r1, [r1]
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	bge _020CF0E0
	ldr r6, _020CF164
	mov r9, #0x64
	mov r8, #0x7
	mov r7, #0x0
_020CF0B0:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r9
	bl OS_SpinWait
	bl OS_DisableInterrupts
	mov r4, r0
	mov r0, r8
	ldr r1, [r6]
	mov r2, r7
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	blt _020CF0B0
_020CF0E0:
	ands r0, r5, #0x2
	beq _020CF0EC
	bl RequestCommandProc
_020CF0EC:
	ldr r0, _020CF170
	ldr r1, _020CF164
	ldr r3, [r0]
	ldr r5, [r1]
	add r1, r3, #0x1
	ldr r2, _020CF174
	str r1, [r0]
	str r5, [r2, r3, lsl #2]
	cmp r1, #0x8
	movgt r1, #0x0
	ldr r2, _020CF168
	strgt r1, [r0]
	ldr r1, _020CF178
	ldr r3, [r2]
	ldr r0, [r1]
	add ip, r3, #0x1
	add r6, r0, #0x1
	ldr r5, _020CF164
	mov lr, #0x0
	ldr r3, _020CF17C
	mov r0, r4
	str lr, [r5]
	str lr, [r3]
	str ip, [r2]
	str r6, [r1]
	bl OS_RestoreInterrupts
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r9, lr}
	bx lr
_020CF164: .word 0x021D3840
_020CF168: .word 0x021D3854
_020CF16C: .word 0x021D3B00
_020CF170: .word 0x021D3850
_020CF174: .word 0x021D385C
_020CF178: .word 0x021D3858
_020CF17C: .word 0x021D3844

	arm_func_start SND_PushCommand
SND_PushCommand: ; 0x020CF180
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r2, _020CF1C0 ; =0x021D3844
	ldr r1, [r2, #0x0]
	cmp r1, #0x0
	ldreq r1, _020CF1C4 ; =0x021D3840
	streq r4, [r2, #0x0]
	streq r4, [r1, #0x0]
	strne r4, [r1, #0x0]
	strne r4, [r2, #0x0]
	mov r1, #0x0
	str r1, [r4, #0x0]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CF1C0: .word 0x021D3844
_020CF1C4: .word 0x021D3840

	arm_func_start SND_AllocCommand
SND_AllocCommand:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl IsCommandAvailable
_020CF1D4:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl AllocCommand
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	ands r0, r4, #0x1
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl SND_CountWaitingCommand
	cmp r0, #0x0
	ble _020CF238
	mov r4, #0x0
_020CF214:
	mov r0, r4
	bl SND_RecvCommandReply
	cmp r0, #0x0
	bne _020CF214
	bl AllocCommand
	cmp r0, #0x0
	beq _020CF240
	ldmia sp!, {r4,lr}
	bx lr
_020CF238:
	mov r0, #0x1
	bl SND_FlushCommand
_020CF240:
	bl RequestCommandProc
	mov r4, #0x1
_020CF248:
	mov r0, r4
	bl SND_RecvCommandReply
	bl AllocCommand
	cmp r0, #0x0
	beq _020CF248
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start SND_RecvCommandReply
SND_RecvCommandReply: ; 0x020CF264
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	mov r5, r0
	ands r0, r4, #0x1
	beq _020CF2C0
	bl SNDi_GetFinishedCommandTag
	ldr r4, _020CF380 ; =0x021D383C
	ldr r1, [r4, #0x0]
	cmp r1, r0
	bne _020CF2E8
	mov r6, #0x64
_020CF294:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r6
	bl OS_SpinWait
	bl OS_DisableInterrupts
	mov r5, r0
	bl SNDi_GetFinishedCommandTag
	ldr r1, [r4, #0x0]
	cmp r1, r0
	beq _020CF294
	b _020CF2E8
_020CF2C0:
	bl SNDi_GetFinishedCommandTag
	ldr r1, _020CF380 ; =0x021D383C
	ldr r1, [r1, #0x0]
	cmp r1, r0
	bne _020CF2E8
	mov r0, r5
	bl OS_RestoreInterrupts
_020CF2DC:
	mov r0, #0x0
	ldmia sp!, {r4-r6, lr}
	bx lr
_020CF2E8:
	ldr r0, _020CF384 ; =0x021D384C
	ldr r2, _020CF388 ; =0x021D385C
	ldr r3, [r0, #0x0]
	add r1, r3, #0x1
	ldr r4, [r2, r3, lsl #0x2]
	str r1, [r0, #0x0]
	cmp r1, #0x8
	movgt r1, #0x0
	strgt r1, [r0, #0x0]
	ldr r0, [r4, #0x0]
	mov r1, r4
	cmp r0, #0x0
	beq _020CF32C
_020CF31C:
	ldr r1, [r1, #0x0]
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	bne _020CF31C
_020CF32C:
	ldr r0, _020CF38C ; =0x021D3848
	ldr r3, _020CF390 ; =0x021D3854
	ldr r0, [r0, #0x0]
	ldr r2, _020CF380 ; =0x021D383C
	cmp r0, #0x0
	strne r4, [r0, #0x0]
	ldreq r0, _020CF394 ; =0x021D3838
	ldr lr, [r3, #0x0]
	streq r4, [r0, #0x0]
	ldr ip, _020CF38C ; =0x021D3848
	sub r6, lr, #0x1
	ldr r0, [r2, #0x0]
	str r1, [r12, #0x0]
	add lr, r0, #0x1
	mov r0, r5
	str r6, [r3, #0x0]
	str lr, [r2, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020CF380: .word 0x021D383C
_020CF384: .word 0x021D384C
_020CF388: .word 0x021D385C
_020CF38C: .word 0x021D3848
_020CF390: .word 0x021D3854
_020CF394: .word 0x021D3838

	arm_func_start SND_CommandInit
SND_CommandInit: ; 0x020CF398
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	bl InitPXI
	ldr r3, _020CF478 ; =0x021D3B00
	ldr r0, _020CF47C ; =0x021D3838
	mov r4, #0x0
	str r3, [r0, #0x0]
	mov r1, r3
	mov r0, #0x18
_020CF3BC:
	add r4, r4, #0x1
	mla r2, r4, r0, r1
	cmp r4, #0xff
	str r2, [r3], #0x18
	blt _020CF3BC
	ldr r7, _020CF480 ; =0x021D4B00
	mov r10, #0x0
	ldr r5, _020CF484 ; =0x021D3840
	ldr r4, _020CF488 ; =0x021D3844
	ldr lr, _020CF48C ; =0x021D3854
	ldr ip, _020CF490 ; =0x021D384C
	ldr r3, _020CF494 ; =0x021D3850
	ldr r1, _020CF498 ; =0x021D383C
	ldr sb, _020CF49C ; =0x021D52E8
	ldr r6, _020CF4A0 ; =0x021D3848
	ldr r2, _020CF4A4 ; =0x021D3858
	mov r8, #0x1
	ldr r0, _020CF4A8 ; =0x021D3880
	ldr fp, _020CF4AC ; =0x021D5360
	str r9, [r6, #0x0]
	str r10, [r7, #0x7e8]
	str r10, [r5, #0x0]
	str r10, [r4, #0x0]
	str r10, [lr, #0x0]
	str r10, [r12, #0x0]
	str r10, [r3, #0x0]
	str r8, [r2, #0x0]
	str r10, [r1, #0x0]
	str r0, [r11, #0x0]
	bl SNDi_InitSharedWork
	mov r0, r8
	bl SND_AllocCommand
_020CF43C:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r11, lr}
	bxeq lr
	mov r2, #0x1D
	mov r1, fp
	str r2, [r0, #0x4]
	ldr r1, [r1]
	str r1, [r0, #0x8]
	bl SND_PushCommand
	mov r0, r8
	bl SND_FlushCommand
	add sp, sp, #0x4
	ldmia sp!, {r4-r11, lr}
	bx lr
_020CF478: .word 0x021D3B00
_020CF47C: .word 0x021D3838
_020CF480: .word 0x021D4B00
_020CF484: .word 0x021D3840
_020CF488: .word 0x021D3844
_020CF48C: .word 0x021D3854
_020CF490: .word 0x021D384C
_020CF494: .word 0x021D3850
_020CF498: .word 0x021D383C
_020CF49C: .word 0x021D52E8
_020CF4A0: .word 0x021D3848
_020CF4A4: .word 0x021D3858
_020CF4A8: .word 0x021D3880
_020CF4AC: .word 0x021D5360

	arm_func_start SNDi_CallAlarmHandler
SNDi_CallAlarmHandler: ; 0x020CF4B0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, _020CF50C ; =0x021D5300
	and r2, r0, #0xff
	mov r1, #0xc
	mla r3, r2, r1, r3
	mov r1, r0, asr #0x8
	ldrb r0, [r3, #0x8]
	and r1, r1, #0xff
	cmp r1, r0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r0, [r3, #0x4]
	blx r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CF50C: .word 0x021D5300

	arm_func_start SNDi_SetAlarmHandler
SNDi_SetAlarmHandler:
	mov r3, #0xc
	mul r3, r0, r3
	ldr r0, _020CF53C ; =0x021D5300
	str r1, [r0, r3]
	add r1, r0, r3
	str r2, [r1, #0x4]
	ldrb r0, [r1, #0x8]
	add r0, r0, #0x1
	strb r0, [r1, #0x8]
	ldrb r0, [r1, #0x8]
	bx lr
	.balign 4
_020CF53C: .word 0x021D5300

	arm_func_start SNDi_IncAlarmId
SNDi_IncAlarmId: ; 0x020CF540
	ldr r2, _020CF55C ; =0x021D5300
	mov r1, #0xc
	mla r1, r0, r1, r2
	ldrb r0, [r1, #0x8]
	add r0, r0, #0x1
	strb r0, [r1, #0x8]
	bx lr
	.balign 4
_020CF55C: .word 0x021D5300

	arm_func_start SND_AlarmInit
SND_AlarmInit: ; 0x020CF560
	ldr r1, _020CF58C ; =0x021D5300
	mov r2, #0x0
	mov r0, r2
_020CF56C:
	str r0, [r1, #0x0]
	str r0, [r1, #0x4]
	add r2, r2, #0x1
	strb r0, [r1, #0x8]
	cmp r2, #0x8
	add r1, r1, #0xc
	blt _020CF56C
	bx lr
	.balign 4
_020CF58C: .word 0x021D5300

	arm_func_start SNDi_InitSharedWork
SNDi_InitSharedWork: ; 0x020CF590
	stmdb sp!, {r4,lr}
	mov r4, #0x0
	str r4, [r0, #0x4]
	strh r4, [r0, #0x8]
	strh r4, [r0, #0xa]
	mov r12, r0
	str r4, [r0, #0x0]
	mov r3, r4
	mvn r2, #0x0
_020CF5B4:
	mov lr, r3
	str r3, [r12, #0x40]
_020CF5BC:
	add r1, r12, lr, lsl #0x1
	add lr, lr, #0x1
	strh r2, [r1, #0x20]
	cmp lr, #0x10
	blt _020CF5BC
	add r4, r4, #0x1
	cmp r4, #0x10
	add r12, r12, #0x24
	blt _020CF5B4
	mov r3, #0x0
	mvn r2, #0x0
_020CF5E8:
	add r1, r0, r3, lsl #0x1
	add r1, r1, #0x200
	add r3, r3, #0x1
	strh r2, [r1, #0x60]
	cmp r3, #0x10
	blt _020CF5E8
	mov r1, #0x280
	bl DC_FlushRange
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start SNDi_GetFinishedCommandTag
SNDi_GetFinishedCommandTag: ; 0x020CF610
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020CF640 ; =0x021D5360
	mov r1, #0x4
	ldr r0, [r0, #0x0]
	bl DC_InvalidateRange
	ldr r0, _020CF640 ; =0x021D5360
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CF640: .word 0x021D5360

	arm_func_start SND_GetPlayerTickCounter
SND_GetPlayerTickCounter: ; 0x020CF644
	stmdb sp!, {r4,lr}
	mov r1, #0x24
	mul r4, r0, r1
	ldr r0, _020CF680 ; =0x021D5360
	mov r1, #0x4
	ldr r0, [r0, #0x0]
	add r0, r0, #0x40
	add r0, r0, r4
	bl DC_InvalidateRange
	ldr r0, _020CF680 ; =0x021D5360
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	ldr r0, [r0, #0x40]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CF680: .word 0x021D5360

	arm_func_start SND_GetChannelStatus
SND_GetChannelStatus: ; 0x020CF684
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020CF6B8 ; =0x021D5360
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	add r0, r0, #0x8
	bl DC_InvalidateRange
	ldr r0, _020CF6B8 ; =0x021D5360
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x8]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CF6B8: .word 0x021D5360

	arm_func_start SND_GetPlayerStatus
SND_GetPlayerStatus: ; 0x020CF6BC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020CF6F0 ; =0x021D5360
	mov r1, #0x4
	ldr r0, [r0, #0x0]
	add r0, r0, #0x4
	bl DC_InvalidateRange
	ldr r0, _020CF6F0 ; =0x021D5360
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CF6F0: .word 0x021D5360

	arm_func_start SND_CalcChannelVolume
SND_CalcChannelVolume: ; 0x020CF6F4
	ldr r1, _020CF75C ; =0xFFFFFD2D
	cmp r0, r1
	movlt r0, r1
	blt _020CF70C
	cmp r0, #0x0
	movgt r0, #0x0
_020CF70C:
	ldr r1, _020CF760 ; =0x000002D3
	ldr r2, _020CF764 ; =0x02103CAC
	add r3, r0, r1
	mvn r1, #0xef
	cmp r0, r1
	ldrb r2, [r2, r3]
	movlt r0, #0x3
	blt _020CF74C
	mvn r1, #0x77
	cmp r0, r1
	movlt r0, #0x2
	blt _020CF74C
	mvn r1, #0x3b
	cmp r0, r1
	movlt r0, #0x1
	movge r0, #0x0
_020CF74C:
	orr r0, r2, r0, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bx lr
	.balign 4
_020CF75C: .word 0xFFFFFD2D
_020CF760: .word 0x000002D3
_020CF764: .word 0x02103CAC

	arm_func_start SND_GetWaveDataAddress
SND_GetWaveDataAddress: ; 0x020CF768
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl SNDi_LockMutex
	add r0, r5, r4, lsl #0x2
	ldr r4, [r0, #0x3c]
	cmp r4, #0x0
	beq _020CF798
	cmp r4, #0x2000000
	addcc r4, r5, r4
	b _020CF79C
_020CF798:
	mov r4, #0x0
_020CF79C:
	bl SNDi_UnlockMutex
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start SND_SetWaveDataAddress
SND_SetWaveDataAddress: ; 0x020CF7B0
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl SNDi_LockMutex
	add r0, r6, #0x3c
	add r2, r6, r5, lsl #0x2
	add r0, r0, r5, lsl #0x2
	mov r1, #0x4
	str r4, [r2, #0x3c]
	bl DC_StoreRange
	bl SNDi_UnlockMutex
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start SND_GetWaveDataCount
SND_GetWaveDataCount: ; 0x020CF7E8
	ldr r0, [r0, #0x38]
	bx lr

	arm_func_start SND_GetNextInstData
SND_GetNextInstData: ; 0x020CF7F0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r4, [r2, #0x0]
	ldr r3, [r0, #0x38]
	cmp r4, r3
	bhs _020CF9B8
	mov r12, #0x0
_020CF80C:
	add r3, r0, r4, lsl #0x2
	ldr r4, [r3, #0x3c]
	strb r4, [r1, #0x0]
	ldrb r3, [r1, #0x0]
	cmp r3, #0x10
	bgt _020CF850
	cmp r3, #0x10
	bge _020CF8A8
	cmp r3, #0x5
	addls pc, pc, r3, lsl #0x2
	b _020CF998
_020CF838:
	b _020CF998
	b _020CF85C
	b _020CF85C
	b _020CF85C
	b _020CF85C
	b _020CF85C
_020CF850:
	cmp r3, #0x11
	beq _020CF924
	b _020CF998
_020CF85C:
	mov r3, r4, lsr #0x8
	add r5, r0, r4, lsr #0x8
	ldrh r4, [r0, r3]
	ldrh r3, [r5, #0x2]
	add sp, sp, #0x4
	mov r0, #0x1
	strh r4, [r1, #0x2]
	strh r3, [r1, #0x4]
	ldrh r4, [r5, #0x4]
	ldrh r3, [r5, #0x6]
	strh r4, [r1, #0x6]
	strh r3, [r1, #0x8]
	ldrh r3, [r5, #0x8]
	strh r3, [r1, #0xA]
	ldr r1, [r2]
	add r1, r1, #0x1
	str r1, [r2]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020CF8A8:
	add r5, r0, r4, lsr #0x8
	b _020CF904
_020CF8B0:
	mov r0, #0xc
	mla r12, lr, r0, r5
	ldrh r4, [r12, #0x2]
	ldrh r3, [r12, #0x4]
	add sp, sp, #0x4
	mov r0, #0x1
	strh r4, [r1, #0x0]
	strh r3, [r1, #0x2]
	ldrh r4, [r12, #0x6]
	ldrh r3, [r12, #0x8]
	strh r4, [r1, #0x4]
	strh r3, [r1, #0x6]
	ldrh r4, [r12, #0xa]
	ldrh r3, [r12, #0xc]
	strh r4, [r1, #0x8]
	strh r3, [r1, #0xa]
	ldr r1, [r2, #0x4]
	add r1, r1, #0x1
	str r1, [r2, #0x4]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020CF904:
	ldrb r4, [r5, #0x1]
	ldrb r3, [r5, #0x0]
	ldr lr, [r2, #0x4]
	sub r3, r4, r3
	add r3, r3, #0x1
	cmp lr, r3
	blo _020CF8B0
	b _020CF998
_020CF924:
	add r4, r0, r4, lsr #0x8
	b _020CF98C
_020CF92C:
	ldrb lr, [r4, r3]
	cmp lr, #0x0
	beq _020CF998
	mov r0, #0xc
	mla lr, r3, r0, r4
	ldrh r12, [lr, #0x8]
	ldrh r3, [lr, #0xa]
	add sp, sp, #0x4
	mov r0, #0x1
	strh r12, [r1, #0x0]
	strh r3, [r1, #0x2]
	ldrh r12, [lr, #0xc]
	ldrh r3, [lr, #0xe]
	strh r12, [r1, #0x4]
	strh r3, [r1, #0x6]
	ldrh r12, [lr, #0x10]
	ldrh r3, [lr, #0x12]
	strh r12, [r1, #0x8]
	strh r3, [r1, #0xa]
	ldr r1, [r2, #0x4]
	add r1, r1, #0x1
	str r1, [r2, #0x4]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020CF98C:
	ldr r3, [r2, #0x4]
	cmp r3, #0x8
	blo _020CF92C
_020CF998:
	ldr r3, [r2, #0x0]
	add r3, r3, #0x1
	str r3, [r2, #0x0]
	str r12, [r2, #0x4]
	ldr r4, [r2, #0x0]
	ldr r3, [r0, #0x38]
	cmp r4, r3
	blo _020CF80C
_020CF9B8:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start SND_GetFirstInstDataPos
SND_GetFirstInstDataPos: ; 0x020CF9C8
	sub sp, sp, #0x8
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	add sp, sp, #0x8
	bx lr

	arm_func_start SND_DestroyWaveArc
SND_DestroyWaveArc: ; 0x020CF9E8
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	bl SNDi_LockMutex
	ldr r0, [r4, #0x18]
	cmp r0, #0x0
	beq _020CFA28
	mov r5, #0x0
	mov r4, #0x8
_020CFA08:
	ldr r6, [r0, #0x4]
	mov r1, r4
	str r5, [r0, #0x0]
	str r5, [r0, #0x4]
	bl DC_StoreRange
	mov r0, r6
	cmp r6, #0x0
	bne _020CFA08
_020CFA28:
	bl SNDi_UnlockMutex
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start SND_DestroyBank
SND_DestroyBank: ; 0x020CFA34
	stmdb sp!, {r4-r8,lr}
	mov r7, r0
	bl SNDi_LockMutex
	add r5, r7, #0x18
	mov r6, #0x0
	mov r8, #0x8
	mov r4, #0x3c
_020CFA50:
	add r1, r7, r6, lsl #0x3
	ldr r0, [r1, #0x18]
	cmp r0, #0x0
	beq _020CFAB8
	ldr r3, [r0, #0x18]
	cmp r5, r3
	bne _020CFA80
	ldr r2, [r1, #0x1c]
	mov r1, r4
	str r2, [r0, #0x18]
	bl DC_StoreRange
	b _020CFAB8
_020CFA80:
	cmp r3, #0x0
	beq _020CFAA0
_020CFA88:
	ldr r0, [r3, #0x4]
	cmp r5, r0
	beq _020CFAA0
	mov r3, r0
	cmp r0, #0x0
	bne _020CFA88
_020CFAA0:
	add r0, r7, r6, lsl #0x3
	ldr r2, [r0, #0x1c]
	mov r0, r3
	mov r1, r8
	str r2, [r3, #0x4]
	bl DC_StoreRange
_020CFAB8:
	add r6, r6, #0x1
	cmp r6, #0x4
	add r5, r5, #0x8
	blt _020CFA50
	bl SNDi_UnlockMutex
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start SND_AssignWaveArc
SND_AssignWaveArc: ; 0x020CFAD4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl SNDi_LockMutex
	add r3, r6, r5, lsl #0x3
	ldr r2, [r3, #0x18]
	mov r12, r5, lsl #0x3
	cmp r2, #0x0
	beq _020CFB70
	cmp r4, r2
	bne _020CFB10
	bl SNDi_UnlockMutex
	ldmia sp!, {r4-r6,lr}
	bx lr
_020CFB10:
	add r1, r6, #0x18
	ldr r0, [r2, #0x18]
	add r12, r1, r12
	cmp r12, r0
	bne _020CFB3C
	ldr r0, [r3, #0x1c]
	mov r1, #0x3c
	str r0, [r2, #0x18]
	ldr r0, [r3, #0x18]
	bl DC_StoreRange
	b _020CFB70
_020CFB3C:
	cmp r0, #0x0
	beq _020CFB5C
_020CFB44:
	ldr r1, [r0, #0x4]
	cmp r12, r1
	beq _020CFB5C
	mov r0, r1
	cmp r1, #0x0
	bne _020CFB44
_020CFB5C:
	add r1, r6, r5, lsl #0x3
	ldr r2, [r1, #0x1c]
	mov r1, #0x8
	str r2, [r0, #0x4]
	bl DC_StoreRange
_020CFB70:
	add r0, r6, #0x18
	ldr r1, [r4, #0x18]
	add r0, r0, r5, lsl #0x3
	str r0, [r4, #0x18]
	add r0, r6, r5, lsl #0x3
	str r1, [r0, #0x1c]
	str r4, [r0, #0x18]
	bl SNDi_UnlockMutex
	mov r0, r6
	mov r1, #0x3c
	bl DC_StoreRange
	mov r0, r4
	mov r1, #0x3c
	bl DC_StoreRange
	ldmia sp!, {r4-r6,lr}
	bx lr
