	.include "asm/macros.inc"
	.include "global.inc"

    .section .bss

	.global OSi_StackForDestructor
OSi_StackForDestructor: ;0x03807784
	.space 0x03807788 - 0x03807784

	.global OSi_RescheduleCount
OSi_RescheduleCount: ;0x03807788
	.space 0x0380778C - 0x03807788

	.global _0380778C
_0380778C: ;0x0380778C
	.space 0x03807790 - 0x0380778C

	.global OSi_SystemCallbackInSwitchThread
OSi_SystemCallbackInSwitchThread: ;0x03807790
	.space 0x03807794 - 0x03807790

	.global OSi_CurrentThreadPtr
OSi_CurrentThreadPtr: ;0x03807794
	.space 0x03807798 - 0x03807794

	.global OSi_IsThreadInitialized
OSi_IsThreadInitialized: ;0x03807798
	.space 0x0380779C - 0x03807798

	.global OSi_ThreadInfo
OSi_ThreadInfo: ;0x0380779C
	.space 0x038077A0 - 0x0380779C

	.global _038077A0
_038077A0: ;0x038077A0
	.space 0x038077AC - 0x038077A0

	.global OSi_IdleThread
OSi_IdleThread: ;0x038077AC
	.space 0x03807850 - 0x038077AC

	.global OSi_LauncherThread
OSi_LauncherThread: ;0x03807850
	.space 0x038078F4 - 0x03807850

    .section .text

	arm_func_start OS_SetThreadDestructor
OS_SetThreadDestructor: ; 0x037F8D48
	str	r1, [r0, #152]	; 0x98
	bx	lr

	arm_func_start OS_EnableScheduler
OS_EnableScheduler: ; 0x037F8D50
	stmdb	sp!, {r4, lr}
	bl	OS_DisableInterrupts
	mov	r4, #0
	ldr	r1, _037F8D84	; =OSi_RescheduleCount
	ldr	r3, [r1]
	cmp	r3, #0
	subne	r2, r3, #1
	strne	r2, [r1]
	movne	r4, r3
	bl	OS_RestoreInterrupts
	mov	r0, r4
	ldmia	sp!, {r4, lr}
	bx	lr
_037F8D84:	.word	OSi_RescheduleCount

	arm_func_start OS_DisableScheduler
OS_DisableScheduler: ; 0x037F8D88
	stmdb	sp!, {r4, lr}
	bl	OS_DisableInterrupts
	ldr	r2, _037F8DBC	; =OSi_RescheduleCount
	ldr	r3, [r2]
	mvn	r1, #0
	cmp	r3, r1
	addcc	r1, r3, #1
	strcc	r1, [r2]
	movcc	r4, r3
	bl	OS_RestoreInterrupts
	mov	r0, r4
	ldmia	sp!, {r4, lr}
	bx	lr
_037F8DBC:	.word	OSi_RescheduleCount

	arm_func_start OS_SetSwitchThreadCallback
OS_SetSwitchThreadCallback: ; 0x037F8DC0
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	bl	OS_DisableInterrupts
	ldr	r1, _037F8DF0	; =OSi_ThreadInfo
	ldr	r4, [r1, #12]
	str	r5, [r1, #12]
	bl	OS_RestoreInterrupts
	mov	r0, r4
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037F8DF0:	.word	OSi_ThreadInfo
_037F8DF4:
	ldr	r2, [r0]
	mov	r1, #0
	str	r1, [r0]
	str	r1, [r2, #148]	; 0x94
	mov	r0, r2
	ldr	ip, _037F8E10	; =OS_WakeupThreadDirect
	bx	ip
_037F8E10:	.word	OS_WakeupThreadDirect

	arm_func_start OS_Sleep
OS_Sleep: ; 0x037F8E14
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #52	; 0x34
	mov	r5, r0
	add	r0, sp, #8
	bl	OS_CreateAlarm
	ldr	r0, _037F8EAC	; =OSi_CurrentThreadPtr
	ldr	r0, [r0]
	ldr	r0, [r0]
	str	r0, [sp, #4]
	bl	OS_DisableInterrupts
	mov	r4, r0
	add	r0, sp, #8
	ldr	r1, [sp, #4]
	str	r0, [r1, #148]	; 0x94
	add	r1, sp, #4
	str	r1, [sp]
	mov	r2, #0
	ldr	r1, _037F8EB0	; =0x000082EA
	umull	ip, r3, r5, r1
	mla	r3, r5, r2, r3
	mla	r3, r2, r1, r3
	mov	r2, r3, lsr #6
	mov	r1, ip, lsr #6
	orr	r1, r1, r3, lsl #26
	ldr	r3, _037F8EB4	; =_037F8DF4
	bl	OS_SetAlarm
	mov	r5, #0
	b	_037F8E8C
_037F8E84:
	mov	r0, r5
	bl	OS_SleepThread
_037F8E8C:
	ldr	r0, [sp, #4]
	cmp	r0, #0
	bne	_037F8E84
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #52	; 0x34
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037F8EAC:	.word	OSi_CurrentThreadPtr
_037F8EB0:	.word	0x000082EA
_037F8EB4:	.word	_037F8DF4

	arm_func_start OS_SetThreadPriority
OS_SetThreadPriority: ; 0x037F8EB8
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r6, r0
	mov	r5, r1
	ldr	r0, _037F8F60	; =OSi_ThreadInfo
	ldr	r8, [r0, #8]
	mov	r7, #0
	bl	OS_DisableInterrupts
	mov	r4, r0
	b	_037F8EE4
_037F8EDC:
	mov	r7, r8
	ldr	r8, [r8, #76]	; 0x4c
_037F8EE4:
	cmp	r8, #0
	beq	_037F8EF4
	cmp	r8, r6
	bne	_037F8EDC
_037F8EF4:
	cmp	r8, #0
	beq	_037F8F08
	ldr	r0, _037F8F64	; =OSi_IdleThread
	cmp	r8, r0
	bne	_037F8F18
_037F8F08:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #0
	b	_037F8F58
_037F8F18:
	ldr	r0, [r8, #84]	; 0x54
	cmp	r0, r5
	beq	_037F8F4C
	cmp	r7, #0
	ldreq	r1, [r6, #76]	; 0x4c
	ldreq	r0, _037F8F60	; =OSi_ThreadInfo
	streq	r1, [r0, #8]
	ldrne	r0, [r6, #76]	; 0x4c
	strne	r0, [r7, #76]	; 0x4c
	str	r5, [r6, #84]	; 0x54
	mov	r0, r6
	bl	OSi_InsertThreadToList
	bl	OSi_RescheduleThread
_037F8F4C:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #1
_037F8F58:
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037F8F60:	.word	OSi_ThreadInfo
_037F8F64:	.word	OSi_IdleThread

	arm_func_start OS_RescheduleThread
OS_RescheduleThread: ; 0x037F8F68
	stmdb	sp!, {r4, lr}
	bl	OS_DisableInterrupts
	mov	r4, r0
	bl	OSi_RescheduleThread
	mov	r0, r4
	bl	OS_RestoreInterrupts
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start OS_SelectThread
OS_SelectThread: ; 0x037F8F88
	ldr	r0, _037F8FB0	; =OSi_ThreadInfo
	ldr	r0, [r0, #8]
	b	_037F8F98
_037F8F94:
	ldr	r0, [r0, #76]	; 0x4c
_037F8F98:
	cmp	r0, #0
	bxeq	lr
	ldr	r1, [r0, #72]	; 0x48
	cmp	r1, #1
	bne	_037F8F94
	bx	lr
_037F8FB0:	.word	OSi_ThreadInfo

	arm_func_start OS_WakeupThreadDirect
OS_WakeupThreadDirect: ; 0x037F8FB4
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	bl	OS_DisableInterrupts
	mov	r4, r0
	mov	r0, #1
	str	r0, [r5, #72]	; 0x48
	bl	OSi_RescheduleThread
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start OS_WakeupThread
OS_WakeupThread: ; 0x037F8FE8
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r5, r0
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r0, [r5]
	cmp	r0, #0
	beq	_037F9050
	mov	r7, #1
	mov	r6, #0
	b	_037F9030
_037F9014:
	mov	r0, r5
	bl	OSi_RemoveLinkFromQueue
	str	r7, [r0, #72]	; 0x48
	str	r6, [r0, #92]	; 0x5c
	str	r6, [r0, #100]	; 0x64
	ldr	r1, [r0, #100]	; 0x64
	str	r1, [r0, #96]	; 0x60
_037F9030:
	ldr	r0, [r5]
	cmp	r0, #0
	bne	_037F9014
	mov	r0, #0
	str	r0, [r5, #4]
	ldr	r0, [r5, #4]
	str	r0, [r5]
	bl	OSi_RescheduleThread
_037F9050:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr

	arm_func_start OS_SleepThread
OS_SleepThread: ; 0x037F9064
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	bl	OS_DisableInterrupts
	mov	r5, r0
	ldr	r0, _037F90B4	; =OSi_CurrentThreadPtr
	ldr	r0, [r0]
	ldr	r4, [r0]
	cmp	r6, #0
	beq	_037F9098
	str	r6, [r4, #92]	; 0x5c
	mov	r0, r6
	mov	r1, r4
	bl	OSi_InsertLinkToQueue
_037F9098:
	mov	r0, #0
	str	r0, [r4, #72]	; 0x48
	bl	OSi_RescheduleThread
	mov	r0, r5
	bl	OS_RestoreInterrupts
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr
_037F90B4:	.word	OSi_CurrentThreadPtr

	arm_func_start OS_IsThreadTerminated
OS_IsThreadTerminated: ; 0x037F90B8
	ldr	r0, [r0, #72]	; 0x48
	cmp	r0, #2
	moveq	r0, #1
	movne	r0, #0
	bx	lr

	arm_func_start OS_JoinThread
OS_JoinThread: ; 0x037F90CC
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r0, [r5, #72]	; 0x48
	cmp	r0, #2
	beq	_037F90F4
	add	r0, r5, #128	; 0x80
	bl	OS_SleepThread
_037F90F4:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start OSi_ExitThread_Destroy
OSi_ExitThread_Destroy: ; 0x037F9108
	stmdb	sp!, {r4, lr}
	ldr	r0, _037F9164	; =OSi_CurrentThreadPtr
	ldr	r0, [r0]
	ldr	r4, [r0]
	bl	OS_DisableScheduler
	mov	r0, r4
	bl	OSi_UnlockAllMutex
	ldr	r0, [r4, #92]	; 0x5c
	cmp	r0, #0
	beq	_037F9138
	mov	r1, r4
	bl	OSi_RemoveSpecifiedLinkFromQueue
_037F9138:
	mov	r0, r4
	bl	OSi_RemoveThreadFromList
	mov	r0, #2
	str	r0, [r4, #72]	; 0x48
	add	r0, r4, #128	; 0x80
	bl	OS_WakeupThread
	bl	OS_EnableScheduler
	bl	OS_RescheduleThread
	bl	OS_Terminate
	ldmia	sp!, {r4, lr}
	bx	lr
_037F9164:	.word	OSi_CurrentThreadPtr

	arm_func_start OSi_ExitThread
OSi_ExitThread: ; 0x037F9168
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _037F91AC	; =OSi_CurrentThreadPtr
	ldr	r1, [r1]
	ldr	r3, [r1]
	ldr	r2, [r3, #152]	; 0x98
	cmp	r2, #0
	beq	_037F919C
	mov	r1, #0
	str	r1, [r3, #152]	; 0x98
	mov	lr, pc
	bx	r2
	bl	OS_DisableInterrupts
_037F919C:
	bl	OSi_ExitThread_Destroy
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037F91AC:	.word	OSi_CurrentThreadPtr

	arm_func_start OSi_ExitThread_ArgSpecified
OSi_ExitThread_ArgSpecified: ; 0x037F91B0
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, r1
	ldr	r1, _037F9210	; =OSi_StackForDestructor
	ldr	r2, [r1]
	cmp	r2, #0
	beq	_037F91FC
	ldr	r1, _037F9214	; =OSi_ExitThread
	bl	OS_InitContext
	str	r4, [r5, #4]
	ldr	r0, [r5]
	orr	r0, r0, #128	; 0x80
	str	r0, [r5]
	mov	r0, #1
	str	r0, [r5, #72]	; 0x48
	mov	r0, r5
	bl	OS_LoadContext
	b	_037F9204
_037F91FC:
	mov	r0, r4
	bl	OSi_ExitThread
_037F9204:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037F9210:	.word	OSi_StackForDestructor
_037F9214:	.word	OSi_ExitThread

	arm_func_start OS_ExitThread
OS_ExitThread: ; 0x037F9218
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	bl	OS_DisableInterrupts
	ldr	r0, _037F9240	; =OSi_ThreadInfo
	ldr	r0, [r0, #4]
	mov	r1, #0
	bl	OSi_ExitThread_ArgSpecified
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037F9240:	.word	OSi_ThreadInfo

	arm_func_start OS_CreateThread
OS_CreateThread: ; 0x037F9244
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r9, r0
	mov	r8, r1
	mov	r7, r2
	mov	r6, r3
	bl	OS_DisableInterrupts
	mov	r4, r0
	bl	OSi_GetUnusedThreadId
	ldr	r1, [sp, #36]	; 0x24
	str	r1, [r9, #84]	; 0x54
	str	r0, [r9, #80]	; 0x50
	mov	r0, #0
	str	r0, [r9, #72]	; 0x48
	str	r0, [r9, #88]	; 0x58
	mov	r0, r9
	bl	OSi_InsertThreadToList
	str	r6, [r9, #120]	; 0x78
	ldr	r0, [sp, #32]
	sub	r5, r6, r0
	str	r5, [r9, #116]	; 0x74
	mov	r2, #0
	str	r2, [r9, #124]	; 0x7c
	ldr	r1, _037F9348	; =0xD73BFDF7
	ldr	r0, [r9, #120]	; 0x78
	str	r1, [r0, #-4]
	ldr	r1, _037F934C	; =0xFBDD37BB
	ldr	r0, [r9, #116]	; 0x74
	str	r1, [r0]
	str	r2, [r9, #132]	; 0x84
	ldr	r0, [r9, #132]	; 0x84
	str	r0, [r9, #128]	; 0x80
	mov	r0, r9
	mov	r1, r8
	sub	r2, r6, #4
	bl	OS_InitContext
	str	r7, [r9, #4]
	ldr	r0, _037F9350	; =OS_ExitThread
	str	r0, [r9, #60]	; 0x3c
	mov	r0, #0
	add	r1, r5, #4
	ldr	r2, [sp, #32]
	sub	r2, r2, #8
	bl	MIi_CpuClear32
	mov	r1, #0
	str	r1, [r9, #104]	; 0x68
	str	r1, [r9, #108]	; 0x6c
	str	r1, [r9, #112]	; 0x70
	mov	r0, r9
	bl	OS_SetThreadDestructor
	mov	r0, #0
	str	r0, [r9, #92]	; 0x5c
	str	r0, [r9, #100]	; 0x64
	ldr	r1, [r9, #100]	; 0x64
	str	r1, [r9, #96]	; 0x60
	add	r1, r9, #136	; 0x88
	mov	r2, #12
	bl	MIi_CpuClear32
	mov	r0, #0
	str	r0, [r9, #148]	; 0x94
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037F9348:	.word	0xD73BFDF7
_037F934C:	.word	0xFBDD37BB
_037F9350:	.word	OS_ExitThread

	arm_func_start OS_InitThread
OS_InitThread: ; 0x037F9354
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037F942C	; =OSi_IsThreadInitialized
	ldr	r1, [r0]
	cmp	r1, #0
	bne	_037F9420
	mov	r2, #1
	str	r2, [r0]
	ldr	r1, _037F9430	; =_038077A0
	ldr	r0, _037F9434	; =OSi_CurrentThreadPtr
	str	r1, [r0]
	mov	r0, #16
	ldr	r1, _037F9438	; =OSi_LauncherThread
	str	r0, [r1, #84]	; 0x54
	mov	r0, #0
	str	r0, [r1, #80]	; 0x50
	str	r2, [r1, #72]	; 0x48
	str	r0, [r1, #76]	; 0x4c
	str	r0, [r1, #88]	; 0x58
	ldr	r0, _037F943C	; =OSi_ThreadInfo
	str	r1, [r0, #8]
	str	r1, [r0, #4]
	ldr	r2, _037F9440	; =0x00000400
	cmp	r2, #0
	ldrle	r0, _037F9444	; =FUN_037F8000
	suble	r2, r0, r2
	ldrgt	r1, _037F9448	; =0x00000400
	ldrgt	r0, _037F944C	; =0x0380FF80
	subgt	r0, r0, r1
	subgt	r2, r0, r2
	ldr	r1, _037F9448	; =0x00000400
	ldr	r0, _037F944C	; =0x0380FF80
	sub	r3, r0, r1
	ldr	r1, _037F9438	; =OSi_LauncherThread
	str	r3, [r1, #120]	; 0x78
	str	r2, [r1, #116]	; 0x74
	mov	r0, #0
	str	r0, [r1, #124]	; 0x7c
	ldr	r2, _037F9450	; =0xD73BFDF7
	str	r2, [r3, #-4]
	ldr	r3, _037F9454	; =0xFBDD37BB
	ldr	r2, [r1, #116]	; 0x74
	str	r3, [r2]
	str	r0, [r1, #132]	; 0x84
	str	r0, [r1, #128]	; 0x80
	ldr	r1, _037F943C	; =OSi_ThreadInfo
	strh	r0, [r1]
	strh	r0, [r1, #2]
	ldr	r2, _037F9458	; =0x027FFFA4
	str	r1, [r2]
	bl	OS_SetSwitchThreadCallback
_037F9420:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037F942C:	.word	OSi_IsThreadInitialized
_037F9430:	.word	_038077A0
_037F9434:	.word	OSi_CurrentThreadPtr
_037F9438:	.word	OSi_LauncherThread
_037F943C:	.word	OSi_ThreadInfo
_037F9440:	.word	0x00000400
_037F9444:	.word	FUN_037F8000
_037F9448:	.word	0x00000400
_037F944C:	.word	0x0380FF80
_037F9450:	.word	0xD73BFDF7
_037F9454:	.word	0xFBDD37BB
_037F9458:	.word	0x027FFFA4

	arm_func_start OSi_RescheduleThread
OSi_RescheduleThread: ; 0x037F945C
	stmdb	sp!, {r4, r5, r6, lr}
	ldr	r0, _037F952C	; =OSi_RescheduleCount
	ldr	r0, [r0]
	cmp	r0, #0
	bne	_037F9524
	ldr	r4, _037F9530	; =OSi_ThreadInfo
	ldrh	r0, [r4, #2]
	cmp	r0, #0
	bne	_037F948C
	bl	OS_GetProcMode
	cmp	r0, #18
	bne	_037F9498
_037F948C:
	mov	r0, #1
	strh	r0, [r4]
	b	_037F9524
_037F9498:
	ldr	r0, _037F9534	; =OSi_CurrentThreadPtr
	ldr	r0, [r0]
	ldr	r6, [r0]
	bl	OS_SelectThread
	mov	r5, r0
	cmp	r6, r5
	beq	_037F9524
	cmp	r5, #0
	beq	_037F9524
	ldr	r0, [r6, #72]	; 0x48
	cmp	r0, #2
	beq	_037F94D8
	mov	r0, r6
	bl	OS_SaveContext
	cmp	r0, #0
	bne	_037F9524
_037F94D8:
	ldr	r0, _037F9538	; =OSi_SystemCallbackInSwitchThread
	ldr	r2, [r0]
	cmp	r2, #0
	beq	_037F94F8
	mov	r0, r6
	mov	r1, r5
	mov	lr, pc
	bx	r2
_037F94F8:
	ldr	r2, [r4, #12]
	cmp	r2, #0
	beq	_037F9514
	mov	r0, r6
	mov	r1, r5
	mov	lr, pc
	bx	r2
_037F9514:
	ldr	r0, _037F9530	; =OSi_ThreadInfo
	str	r5, [r0, #4]
	mov	r0, r5
	bl	OS_LoadContext
_037F9524:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr
_037F952C:	.word	OSi_RescheduleCount
_037F9530:	.word	OSi_ThreadInfo
_037F9534:	.word	OSi_CurrentThreadPtr
_037F9538:	.word	OSi_SystemCallbackInSwitchThread

	arm_func_start OSi_RemoveThreadFromList
OSi_RemoveThreadFromList: ; 0x037F953C
	ldr	r1, _037F9580	; =OSi_ThreadInfo
	ldr	r2, [r1, #8]
	mov	r1, #0
	b	_037F9554
_037F954C:
	mov	r1, r2
	ldr	r2, [r2, #76]	; 0x4c
_037F9554:
	cmp	r2, #0
	beq	_037F9564
	cmp	r2, r0
	bne	_037F954C
_037F9564:
	cmp	r1, #0
	ldreq	r1, [r0, #76]	; 0x4c
	ldreq	r0, _037F9580	; =OSi_ThreadInfo
	streq	r1, [r0, #8]
	ldrne	r0, [r0, #76]	; 0x4c
	strne	r0, [r1, #76]	; 0x4c
	bx	lr
_037F9580:	.word	OSi_ThreadInfo

	arm_func_start OSi_InsertThreadToList
OSi_InsertThreadToList: ; 0x037F9584
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _037F95E8	; =OSi_ThreadInfo
	ldr	r3, [r1, #8]
	mov	lr, r3
	mov	ip, #0
	b	_037F95A8
_037F95A0:
	mov	ip, lr
	ldr	lr, [lr, #76]	; 0x4c
_037F95A8:
	cmp	lr, #0
	beq	_037F95C0
	ldr	r2, [lr, #84]	; 0x54
	ldr	r1, [r0, #84]	; 0x54
	cmp	r2, r1
	bcc	_037F95A0
_037F95C0:
	cmp	ip, #0
	streq	r3, [r0, #76]	; 0x4c
	ldreq	r1, _037F95E8	; =OSi_ThreadInfo
	streq	r0, [r1, #8]
	ldrne	r1, [ip, #76]	; 0x4c
	strne	r1, [r0, #76]	; 0x4c
	strne	r0, [ip, #76]	; 0x4c
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037F95E8:	.word	OSi_ThreadInfo

	arm_func_start OSi_RemoveMutexLinkFromQueue
OSi_RemoveMutexLinkFromQueue: ; 0x037F95EC
	ldr	r2, [r0]
	cmp	r2, #0
	beq	_037F9614
	ldr	r1, [r2, #16]
	str	r1, [r0]
	cmp	r1, #0
	movne	r0, #0
	strne	r0, [r1, #20]
	moveq	r1, #0
	streq	r1, [r0, #4]
_037F9614:
	mov	r0, r2
	bx	lr

	arm_func_start OSi_RemoveSpecifiedLinkFromQueue
OSi_RemoveSpecifiedLinkFromQueue: ; 0x037F961C
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r2, [r0]
	mov	lr, r2
	b	_037F9664
_037F9630:
	ldr	ip, [lr, #100]	; 0x64
	cmp	lr, r1
	bne	_037F9660
	ldr	r3, [lr, #96]	; 0x60
	cmp	r2, lr
	streq	ip, [r0]
	strne	ip, [r3, #100]	; 0x64
	ldr	r1, [r0, #4]
	cmp	r1, lr
	streq	r3, [r0, #4]
	strne	r3, [ip, #96]	; 0x60
	b	_037F966C
_037F9660:
	mov	lr, ip
_037F9664:
	cmp	lr, #0
	bne	_037F9630
_037F966C:
	mov	r0, lr
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start OSi_RemoveLinkFromQueue
OSi_RemoveLinkFromQueue: ; 0x037F967C
	ldr	r2, [r0]
	cmp	r2, #0
	beq	_037F96A8
	ldr	r1, [r2, #100]	; 0x64
	str	r1, [r0]
	cmp	r1, #0
	movne	r0, #0
	strne	r0, [r1, #96]	; 0x60
	moveq	r1, #0
	streq	r1, [r0, #4]
	streq	r1, [r2, #92]	; 0x5c
_037F96A8:
	mov	r0, r2
	bx	lr

	arm_func_start OSi_InsertLinkToQueue
OSi_InsertLinkToQueue: ; 0x037F96B0
	ldr	ip, [r0]
	b	_037F96C4
_037F96B8:
	cmp	ip, r1
	bxeq	lr
	ldr	ip, [ip, #100]	; 0x64
_037F96C4:
	cmp	ip, #0
	beq	_037F96DC
	ldr	r3, [ip, #84]	; 0x54
	ldr	r2, [r1, #84]	; 0x54
	cmp	r3, r2
	bls	_037F96B8
_037F96DC:
	cmp	ip, #0
	bne	_037F9708
	ldr	r2, [r0, #4]
	cmp	r2, #0
	streq	r1, [r0]
	strne	r1, [r2, #100]	; 0x64
	str	r2, [r1, #96]	; 0x60
	mov	r2, #0
	str	r2, [r1, #100]	; 0x64
	str	r1, [r0, #4]
	bx	lr
_037F9708:
	ldr	r2, [ip, #96]	; 0x60
	cmp	r2, #0
	streq	r1, [r0]
	strne	r1, [r2, #100]	; 0x64
	str	r2, [r1, #96]	; 0x60
	str	ip, [r1, #100]	; 0x64
	str	r1, [ip, #96]	; 0x60
	bx	lr

	arm_func_start OSi_GetUnusedThreadId
OSi_GetUnusedThreadId: ; 0x037F9728
	ldr	r1, _037F973C	; =_0380778C
	ldr	r0, [r1]
	add	r0, r0, #1
	str	r0, [r1]
	bx	lr
_037F973C:	.word	_0380778C
