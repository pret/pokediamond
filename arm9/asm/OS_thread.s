    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_021D349C
	.extern OSi_LauncherThread
	.extern OSi_SystemCallbackInSwitchThread

    .text

	arm_func_start OS_IsThreadAvailable
OS_IsThreadAvailable: ; 0x020CAED0
	ldr r0, _020CAEDC ; =OSi_IsThreadInitialized
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020CAEDC: .word OSi_IsThreadInitialized

	arm_func_start OS_SetThreadDestructor
OS_SetThreadDestructor:
	str r1, [r0, #0xb4]
	bx lr

	arm_func_start OS_EnableScheduler
OS_EnableScheduler: ; 0x020CAEE8
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020CAF1C ; =OSi_RescheduleCount
	mov r4, #0x0
	ldr r3, [r1, #0x0]
	cmp r3, #0x0
	subne r2, r3, #0x1
	movne r4, r3
	strne r2, [r1, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CAF1C: .word OSi_RescheduleCount

	arm_func_start OS_DisableScheduler
OS_DisableScheduler: ; 0x020CAF20
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r2, _020CAF54 ; =OSi_RescheduleCount
	mvn r1, #0x0
	ldr r3, [r2, #0x0]
	cmp r3, r1
	addcc r1, r3, #0x1
	movcc r4, r3
	strcc r1, [r2, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CAF54: .word OSi_RescheduleCount

	arm_func_start OSi_IdleThreadProc
OSi_IdleThreadProc: ; 0x020CAF58
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl OS_EnableInterrupts
_020CAF64:
	bl OS_Halt
	b _020CAF64

	arm_func_start OS_SetSwitchThreadCallback
OS_SetSwitchThreadCallback: ; 0x020CAF6C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020CAF9C ; =OSi_ThreadInfo
	ldr r4, [r1, #0xc]
	str r5, [r1, #0xc]
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CAF9C: .word OSi_ThreadInfo

	arm_func_start OSi_SleepAlarmCallback
OSi_SleepAlarmCallback: ; 0x020CAFA0
	ldr r2, [r0, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
	ldr ip, _020CAFBC ; =OS_WakeupThreadDirect
	mov r0, r2
	str r1, [r2, #0xb0]
	bx r12
	.balign 4
_020CAFBC: .word OS_WakeupThreadDirect

	arm_func_start OS_Sleep
OS_Sleep: ; 0x020CAFC0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x34
	mov r4, r0
	add r0, sp, #0x8
	bl OS_CreateAlarm
	ldr r0, _020CB060 ; =OSi_CurrentThreadPtr
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	str r0, [sp, #0x4]
	bl OS_DisableInterrupts
	ldr r1, _020CB064 ; =0x000082EA
	mov r2, #0x0
	umull r5, r3, r4, r1
	mla r3, r4, r2, r3
	mla r3, r2, r1, r3
	mov r1, r5, lsr #0x6
	mov r4, r0
	ldr r5, [sp, #0x4]
	add r0, sp, #0x8
	add r2, sp, #0x4
	str r0, [r5, #0xb0]
	str r2, [sp, #0x0]
	mov r2, r3, lsr #0x6
	orr r1, r1, r3, lsl #0x1a
	ldr r3, _020CB068 ; =OSi_SleepAlarmCallback
	bl OS_SetAlarm
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020CB04C
	mov r5, #0x0
_020CB038:
	mov r0, r5
	bl OS_SleepThread
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _020CB038
_020CB04C:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x34
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CB060: .word OSi_CurrentThreadPtr
_020CB064: .word 0x000082EA
_020CB068: .word OSi_SleepAlarmCallback

	arm_func_start OS_GetThreadPriority
OS_GetThreadPriority: ; 0x020CB06C
	ldr r0, [r0, #0x70]
	bx lr

	arm_func_start OS_SetThreadPriority
OS_SetThreadPriority: ; 0x020CB074
	stmdb sp!, {r4-r8,lr}
	ldr r2, _020CB120 ; =OSi_ThreadInfo
	mov r6, r0
	mov r5, r1
	ldr r8, [r2, #0x8]
	mov r7, #0x0
	bl OS_DisableInterrupts
	mov r4, r0
	b _020CB0A0
_020CB098:
	mov r7, r8
	ldr r8, [r8, #0x68]
_020CB0A0:
	cmp r8, #0x0
	beq _020CB0B0
	cmp r8, r6
	bne _020CB098
_020CB0B0:
	cmp r8, #0x0
	beq _020CB0C4
	ldr r0, _020CB124 ; =OSi_IdleThread
	cmp r8, r0
	bne _020CB0D8
_020CB0C4:
	mov r0, r4
	bl OS_RestoreInterrupts
_020CB0CC:
	mov r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CB0D8:
	ldr r0, [r8, #0x70]
	cmp r0, r5
	beq _020CB10C
	cmp r7, #0x0
	ldreq r1, [r6, #0x68]
	ldreq r0, _020CB120 ; =OSi_ThreadInfo
	streq r1, [r0, #0x8]
	ldrne r0, [r6, #0x68]
	strne r0, [r7, #0x68]
	mov r0, r6
	str r5, [r6, #0x70]
	bl OSi_InsertThreadToList
	bl OSi_RescheduleThread
_020CB10C:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020CB120: .word OSi_ThreadInfo
_020CB124: .word OSi_IdleThread

	arm_func_start OS_YieldThread
OS_YieldThread: ; 0x020CB128
	stmdb sp!, {r4-r8,lr}
	ldr r0, _020CB1E0 ; =OSi_ThreadInfo
	mov r7, #0x0
	mov r6, r7
	mov r5, r7
	ldr r8, [r0, #0x4]
	bl OS_DisableInterrupts
	ldr r1, _020CB1E0 ; =OSi_ThreadInfo
	mov r4, r0
	ldr r2, [r1, #0x8]
	mov r0, r7
	cmp r2, #0x0
	beq _020CB188
	ldr r1, [r8, #0x70]
_020CB160:
	cmp r2, r8
	moveq r7, r0
	ldr r0, [r2, #0x70]
	cmp r1, r0
	moveq r6, r2
	mov r0, r2
	ldr r2, [r2, #0x68]
	addeq r5, r5, #0x1
	cmp r2, #0x0
	bne _020CB160
_020CB188:
	cmp r5, #0x1
	ble _020CB198
	cmp r6, r8
	bne _020CB1A8
_020CB198:
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CB1A8:
	cmp r7, #0x0
	ldreq r1, [r8, #0x68]
	ldreq r0, _020CB1E0 ; =OSi_ThreadInfo
	streq r1, [r0, #0x8]
	ldrne r0, [r8, #0x68]
	strne r0, [r7, #0x68]
	ldr r0, [r6, #0x68]
	str r0, [r8, #0x68]
	str r8, [r6, #0x68]
	bl OSi_RescheduleThread
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020CB1E0: .word OSi_ThreadInfo

	arm_func_start OS_RescheduleThread
OS_RescheduleThread: ; 0x020CB1E4
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	mov r4, r0
	bl OSi_RescheduleThread
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start OS_SelectThread
OS_SelectThread: ; 0x020CB204
	ldr r0, _020CB22C ; =OSi_ThreadInfo
	ldr r0, [r0, #0x8]
	b _020CB214
_020CB210:
	ldr r0, [r0, #0x68]
_020CB214:
	cmp r0, #0x0
	bxeq lr
	ldr r1, [r0, #0x64]
	cmp r1, #0x1
	bne _020CB210
	bx lr
	.balign 4
_020CB22C: .word OSi_ThreadInfo

	arm_func_start OS_WakeupThreadDirect
OS_WakeupThreadDirect: ; 0x020CB230
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	mov r1, #0x1
	mov r4, r0
	str r1, [r5, #0x64]
	bl OSi_RescheduleThread
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start OS_WakeupThread
OS_WakeupThread: ; 0x020CB264
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, [r5, #0x0]
	mov r4, r0
	cmp r1, #0x0
	beq _020CB2D0
	cmp r1, #0x0
	beq _020CB2BC
	mov r7, #0x1
	mov r6, #0x0
_020CB294:
	mov r0, r5
	bl OSi_RemoveLinkFromQueue
	str r7, [r0, #0x64]
	str r6, [r0, #0x78]
	str r6, [r0, #0x80]
	ldr r1, [r0, #0x80]
	str r1, [r0, #0x7c]
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	bne _020CB294
_020CB2BC:
	mov r0, #0x0
	str r0, [r5, #0x4]
	ldr r0, [r5, #0x4]
	str r0, [r5, #0x0]
	bl OSi_RescheduleThread
_020CB2D0:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start OS_SleepThread
OS_SleepThread:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	bl OS_DisableInterrupts
	ldr r1, _020CB334 ; =OSi_CurrentThreadPtr
	mov r5, r0
	ldr r0, [r1, #0x0]
	cmp r6, #0x0
	ldr r4, [r0, #0x0]
	beq _020CB318
	mov r0, r6
	mov r1, r4
	str r6, [r4, #0x78]
	bl OSi_InsertLinkToQueue
_020CB318:
	mov r0, #0x0
	str r0, [r4, #0x64]
	bl OSi_RescheduleThread
	mov r0, r5
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020CB334: .word OSi_CurrentThreadPtr

	arm_func_start OS_IsThreadTerminated
OS_IsThreadTerminated: ; 0x020CB338
	ldr r0, [r0, #0x64]
	cmp r0, #0x2
	moveq r0, #0x1
	movne r0, #0x0
	bx lr

	arm_func_start OS_JoinThread
OS_JoinThread: ; 0x020CB34C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, [r5, #0x64]
	mov r4, r0
	cmp r1, #0x2
	beq _020CB374
	add r0, r5, #0x9c
	bl OS_SleepThread
_020CB374:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start OSi_CancelThreadAlarmForSleep
OSi_CancelThreadAlarmForSleep: ; 0x020CB388
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0xb0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	bl OS_CancelAlarm
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start OS_DestroyThread
OS_DestroyThread: ; 0x020CB3B4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020CB438 ; =OSi_ThreadInfo
	mov r4, r0
	ldr r0, [r1, #0x4]
	cmp r0, r5
	bne _020CB3DC
	bl OSi_ExitThread_Destroy
_020CB3DC:
	bl OS_DisableScheduler
	mov r0, r5
	bl OSi_UnlockAllMutex
	mov r0, r5
	bl OSi_CancelThreadAlarmForSleep
	ldr r0, [r5, #0x78]
	cmp r0, #0x0
	beq _020CB404
	mov r1, r5
	bl OSi_RemoveSpecifiedLinkFromQueue
_020CB404:
	mov r0, r5
	bl OSi_RemoveThreadFromList
	mov r1, #0x2
	add r0, r5, #0x9c
	str r1, [r5, #0x64]
	bl OS_WakeupThread
	bl OS_EnableScheduler
	mov r0, r4
	bl OS_RestoreInterrupts
	bl OS_RescheduleThread
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CB438: .word OSi_ThreadInfo

	arm_func_start OSi_ExitThread_Destroy
OSi_ExitThread_Destroy: ; 0x020CB43C
	stmdb sp!, {r4,lr}
	ldr r0, _020CB498 ; =OSi_CurrentThreadPtr
	ldr r0, [r0, #0x0]
	ldr r4, [r0, #0x0]
	bl OS_DisableScheduler
	mov r0, r4
	bl OSi_UnlockAllMutex
	ldr r0, [r4, #0x78]
	cmp r0, #0x0
	beq _020CB46C
	mov r1, r4
	bl OSi_RemoveSpecifiedLinkFromQueue
_020CB46C:
	mov r0, r4
	bl OSi_RemoveThreadFromList
	mov r1, #0x2
	add r0, r4, #0x9c
	str r1, [r4, #0x64]
	bl OS_WakeupThread
	bl OS_EnableScheduler
	bl OS_RescheduleThread
	bl OS_Terminate
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CB498: .word OSi_CurrentThreadPtr

	arm_func_start OSi_ExitThread_Destroy2
OSi_ExitThread_Destroy2: ; 0x020CB49C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020CB4DC ; =OSi_CurrentThreadPtr
	ldr r1, [r1, #0x0]
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0xb4]
	cmp r2, #0x0
	beq _020CB4CC
	mov r1, #0x0
	str r1, [r3, #0xb4]
	blx r2
	bl OS_DisableInterrupts
_020CB4CC:
	bl OSi_ExitThread_Destroy
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CB4DC: .word OSi_CurrentThreadPtr

	arm_func_start OSi_ExitThread_ArgSpecified
OSi_ExitThread_ArgSpecified: ; 0x020CB4E0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r2, _020CB548 ; =OSi_StackForDestructor
	mov r5, r0
	ldr r2, [r2, #0x0]
	mov r4, r1
	cmp r2, #0x0
	beq _020CB534
	ldr r1, _020CB54C ; =OSi_ExitThread_Destroy2
	bl OS_InitContext
	str r4, [r5, #0x4]
	ldr r1, [r5, #0x0]
	mov r0, r5
	orr r1, r1, #0x80
	str r1, [r5, #0x0]
	mov r1, #0x1
	str r1, [r5, #0x64]
	bl OS_LoadContext
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020CB534:
	mov r0, r4
	bl OSi_ExitThread_Destroy2
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CB548: .word OSi_StackForDestructor
_020CB54C: .word OSi_ExitThread_Destroy2

	arm_func_start OS_ExitThread
OS_ExitThread: ; 0x020CB550
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r0, _020CB578 ; =OSi_ThreadInfo
	mov r1, #0x0
	ldr r0, [r0, #0x4]
	bl OSi_ExitThread_ArgSpecified
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CB578: .word OSi_ThreadInfo

	arm_func_start OS_CreateThread
OS_CreateThread: ; 0x020CB57C
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r5, r1
	mov r7, r2
	mov r6, r3
	bl OS_DisableInterrupts
	mov r4, r0
	bl OSi_GetUnusedThreadId
	ldr r2, [sp, #0x1c]
	mov r1, #0x0
	str r2, [r8, #0x70]
	str r0, [r8, #0x6c]
	str r1, [r8, #0x64]
	str r1, [r8, #0x74]
	mov r0, r8
	bl OSi_InsertThreadToList
	mov r1, r5
	str r6, [r8, #0x94]
	ldr r0, [sp, #0x18]
	mov r12, #0x0
	sub r5, r6, r0
	sub r2, r6, #0x4
	str r5, [r8, #0x90]
	str r12, [r8, #0x98]
	ldr r3, _020CB678 ; =0xFDDB597D
	ldr r0, [r8, #0x94]
	ldr r6, _020CB67C ; =0x7BF9DD5B
	str r3, [r0, #-0x4]
	ldr r3, [r8, #0x90]
	mov r0, r8
	str r6, [r3, #0x0]
	str r12, [r8, #0xa0]
	ldr r3, [r8, #0xa0]
	str r3, [r8, #0x9c]
	bl OS_InitContext
	str r7, [r8, #0x4]
	add r1, r5, #0x4
	ldr r2, _020CB680 ; =OS_ExitThread
	mov r0, #0x0
	str r2, [r8, #0x3c]
	ldr r2, [sp, #0x18]
	sub r2, r2, #0x8
	bl MIi_CpuClear32
	mov r1, #0x0
	str r1, [r8, #0x84]
	str r1, [r8, #0x88]
	str r1, [r8, #0x8c]
	mov r0, r8
	bl OS_SetThreadDestructor
_020CB640:
	mov r0, #0x0
	str r0, [r8, #0x78]
	str r0, [r8, #0x80]
	ldr r2, [r8, #0x80]
	add r1, r8, #0xA4
	str r2, [r8, #0x7C]
	mov r2, #0xC
	bl MIi_CpuClear32
	mov r0, r4
	mov r1, #0x0
	str r1, [r8, #0xB0]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8, lr}
	bx lr
_020CB678: .word 0xFDDB597D
_020CB67C: .word 0x7BF9DD5B
_020CB680: .word OS_ExitThread

	arm_func_start OS_InitThread
OS_InitThread: ; 0x020CB684
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	ldr r3, _020CB7A4 ; =OSi_IsThreadInitialized
	ldr r0, [r3, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x8
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldr ip, _020CB7A8 ; =0x00000000
	ldr r1, _020CB7AC ; =OSi_LauncherThread
	mov lr, #0x0
	ldr r0, _020CB7B0 ; =OSi_ThreadInfo
	mov r6, #0x1
	mov r4, #0x10
	str r1, [r0, #0x8]
	str r1, [r0, #0x4]
	cmp r12, #0x0
	ldrle r0, _020CB7B4 ; =0x027E0080
	str r4, [r1, #0x70]
	suble r4, r0, r12
	str lr, [r1, #0x6c]
	str r6, [r1, #0x64]
	str lr, [r1, #0x68]
	str lr, [r1, #0x74]
	ldrgt r1, _020CB7B8 ; =0x027E0000
	ldrgt r0, _020CB7BC ; =0x00000400
	addgt r1, r1, #0x3f80
	subgt r0, r1, r0
	subgt r4, r0, r12
	ldr r1, _020CB7B8 ; =0x027E0000
	ldr r5, _020CB7C0 ; =UNK_021D349C
	ldr r2, _020CB7C4 ; =OSi_CurrentThreadPtr
	ldr r0, _020CB7BC ; =0x00000400
	str r5, [r2, #0x0]
	ldr r2, _020CB7AC ; =OSi_LauncherThread
	add r1, r1, #0x3f80
	str r6, [r3, #0x0]
	sub r3, r1, r0
	mov r0, #0x0
	ldr r1, _020CB7C8 ; =0xFDDB597D
	str r3, [r2, #0x94]
	str r4, [r2, #0x90]
	str r0, [r2, #0x98]
	str r1, [r3, #-0x4]
	ldr r3, [r2, #0x90]
	ldr ip, _020CB7CC ; =0x7BF9DD5B
	ldr r1, _020CB7B0 ; =OSi_ThreadInfo
	str r12, [r3, #0x0]
	ldr r3, _020CB7D0 ; =0x027FFFA0
	str r0, [r2, #0xa0]
	str r0, [r2, #0x9c]
	strh r0, [r1, #0x0]
	strh r0, [r1, #0x2]
	str r1, [r3, #0x0]
	bl OS_SetSwitchThreadCallback
	mov r2, #0xc8
	str r2, [sp, #0x0]
	mov r12, #0x1f
	ldr r0, _020CB7D4 ; =OSi_IdleThread
	ldr r1, _020CB7D8 ; =OSi_IdleThreadProc
	ldr r3, _020CB7DC ; =OSi_Initialized
	mov r2, #0x0
	str r12, [sp, #0x4]
	bl OS_CreateThread
	ldr r0, _020CB7D4 ; =OSi_IdleThread
	mov r2, #0x20
	mov r1, #0x1
	str r2, [r0, #0x70]
	str r1, [r0, #0x64]
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020CB7A4: .word OSi_IsThreadInitialized
_020CB7A8: .word SDK_SYS_STACKSIZE
_020CB7AC: .word OSi_LauncherThread
_020CB7B0: .word OSi_ThreadInfo
_020CB7B4: .word SDK_SECTION_ARENA_DTCM_START
_020CB7B8: .word SDK_AUTOLOAD_DTCM_START
_020CB7BC: .word SDK_IRQ_STACKSIZE
_020CB7C0: .word OSi_ThreadInfo+4
_020CB7C4: .word OSi_CurrentThreadPtr
_020CB7C8: .word 0xFDDB597D
_020CB7CC: .word 0x7BF9DD5B
_020CB7D0: .word 0x027FFFA0
_020CB7D4: .word OSi_IdleThread
_020CB7D8: .word OSi_IdleThreadProc
_020CB7DC: .word OSi_IdleThreadStack+0xc8

	arm_func_start OSi_RescheduleThread
OSi_RescheduleThread: ; 0x020CB7E0
	stmdb sp!, {r4-r6,lr}
	ldr r0, _020CB8BC ; =OSi_RescheduleCount
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldr r4, _020CB8C0 ; =OSi_ThreadInfo
	ldrh r0, [r4, #0x2]
	cmp r0, #0x0
	bne _020CB814
	bl OS_GetProcMode
	cmp r0, #0x12
	bne _020CB824
_020CB814:
	mov r0, #0x1
	strh r0, [r4, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
_020CB824:
	ldr r0, _020CB8C4 ; =OSi_CurrentThreadPtr
	ldr r0, [r0, #0x0]
	ldr r6, [r0, #0x0]
	bl OS_SelectThread
	mov r5, r0
	cmp r6, r5
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	cmp r5, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, [r6, #0x64]
	cmp r0, #0x2
	beq _020CB870
	mov r0, r6
	bl OS_SaveContext
_020CB864:
	cmp r0, #0x0
	ldmneia sp!, {r4-r6,lr}
	bxne lr
_020CB870:
	ldr r0, _020CB8C8 ; =OSi_SystemCallbackInSwitchThread
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _020CB88C
	mov r0, r6
	mov r1, r5
	blx r2
_020CB88C:
	ldr r2, [r4, #0xc]
	cmp r2, #0x0
	beq _020CB8A4
	mov r0, r6
	mov r1, r5
	blx r2
_020CB8A4:
	ldr r1, _020CB8C0 ; =OSi_ThreadInfo
	mov r0, r5
	str r5, [r1, #0x4]
	bl OS_LoadContext
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020CB8BC: .word OSi_RescheduleCount
_020CB8C0: .word OSi_ThreadInfo
_020CB8C4: .word OSi_CurrentThreadPtr
_020CB8C8: .word OSi_SystemCallbackInSwitchThread

	arm_func_start OSi_RemoveThreadFromList
OSi_RemoveThreadFromList: ; 0x020CB8CC
	ldr r1, _020CB910 ; =OSi_ThreadInfo
	mov r2, #0x0
	ldr r1, [r1, #0x8]
	b _020CB8E4
_020CB8DC:
	mov r2, r1
	ldr r1, [r1, #0x68]
_020CB8E4:
	cmp r1, #0x0
	beq _020CB8F4
	cmp r1, r0
	bne _020CB8DC
_020CB8F4:
	cmp r2, #0x0
	ldreq r1, [r0, #0x68]
	ldreq r0, _020CB910 ; =OSi_ThreadInfo
	streq r1, [r0, #0x8]
	ldrne r0, [r0, #0x68]
	strne r0, [r2, #0x68]
	bx lr
	.balign 4
_020CB910: .word OSi_ThreadInfo

	arm_func_start OSi_InsertThreadToList
OSi_InsertThreadToList: ; 0x020CB914
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020CB978 ; =OSi_ThreadInfo
	mov r12, #0x0
	ldr r3, [r1, #0x8]
	mov lr, r3
	b _020CB938
_020CB930:
	mov r12, lr
	ldr lr, [lr, #0x68]
_020CB938:
	cmp lr, #0x0
	beq _020CB950
	ldr r2, [lr, #0x70]
	ldr r1, [r0, #0x70]
	cmp r2, r1
	blo _020CB930
_020CB950:
	cmp r12, #0x0
	ldreq r1, _020CB978 ; =OSi_ThreadInfo
	streq r3, [r0, #0x68]
	streq r0, [r1, #0x8]
	ldrne r1, [r12, #0x68]
	strne r1, [r0, #0x68]
	strne r0, [r12, #0x68]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CB978: .word OSi_ThreadInfo

	arm_func_start OSi_RemoveMutexLinkFromQueue
OSi_RemoveMutexLinkFromQueue: ; 0x020CB97C
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _020CB9A4
	ldr r1, [r2, #0x10]
	str r1, [r0, #0x0]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x14]
	moveq r1, #0x0
	streq r1, [r0, #0x4]
_020CB9A4:
	mov r0, r2
	bx lr

	arm_func_start OSi_RemoveSpecifiedLinkFromQueue
OSi_RemoveSpecifiedLinkFromQueue: ; 0x020CB9AC
	ldr r2, [r0, #0x0]
	mov r12, r2
	cmp r2, #0x0
	beq _020CB9F8
_020CB9BC:
	cmp r12, r1
	ldr r3, [r12, #0x80]
	bne _020CB9EC
	cmp r2, r12
	ldr r2, [r12, #0x7c]
	streq r3, [r0, #0x0]
	strne r3, [r2, #0x80]
	ldr r1, [r0, #0x4]
	cmp r1, r12
	streq r2, [r0, #0x4]
	strne r2, [r3, #0x7c]
	b _020CB9F8
_020CB9EC:
	mov r12, r3
	cmp r3, #0x0
	bne _020CB9BC
_020CB9F8:
	mov r0, r12
	bx lr

	arm_func_start OSi_RemoveLinkFromQueue
OSi_RemoveLinkFromQueue: ; 0x020CBA00
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _020CBA2C
	ldr r1, [r2, #0x80]
	str r1, [r0, #0x0]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x7c]
	moveq r1, #0x0
	streq r1, [r0, #0x4]
	streq r1, [r2, #0x78]
_020CBA2C:
	mov r0, r2
	bx lr

	arm_func_start OSi_InsertLinkToQueue
OSi_InsertLinkToQueue:
	ldr r12, [r0, #0x0]
	b _020CBA48
_020CBA3C:
	cmp r12, r1
	bxeq lr
	ldr r12, [r12, #0x80]
_020CBA48:
	cmp r12, #0x0
	beq _020CBA60
	ldr r3, [r12, #0x70]
	ldr r2, [r1, #0x70]
	cmp r3, r2
	bls _020CBA3C
_020CBA60:
	cmp r12, #0x0
	bne _020CBA8C
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	streq r1, [r0, #0x0]
	strne r1, [r2, #0x80]
	str r2, [r1, #0x7c]
	mov r2, #0x0
	str r2, [r1, #0x80]
	str r1, [r0, #0x4]
	bx lr
_020CBA8C:
	ldr r2, [r12, #0x7c]
	cmp r2, #0x0
	streq r1, [r0, #0x0]
	strne r1, [r2, #0x80]
	str r2, [r1, #0x7c]
	str r12, [r1, #0x80]
	str r1, [r12, #0x7c]
	bx lr

	arm_func_start OSi_GetUnusedThreadId
OSi_GetUnusedThreadId: ; 0x020CBAAC
	ldr r1, _020CBAC0 ; =OSi_ThreadIdCount
	ldr r0, [r1, #0x0]
	add r0, r0, #0x1
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020CBAC0: .word OSi_ThreadIdCount
