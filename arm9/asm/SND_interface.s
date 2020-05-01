	.include "asm/macros.inc"
	.include "global.inc"

    .text

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
