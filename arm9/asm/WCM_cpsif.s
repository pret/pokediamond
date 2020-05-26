	.include "asm/macros.inc"
	.include "global.inc"

	.bss

	.global wcmCpsifw
wcmCpsifw: ; 0x021CA870
	.space 0x2C

	.text

	arm_func_start WcmCpsifUnlockMutexInIRQ
WcmCpsifUnlockMutexInIRQ: ; 0x020A8534
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x8]
	ldr r1, _020A858C ; =OS_IrqHandler
	cmp r2, r1
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r1, [r0, #0xc]
	sub r1, r1, #0x1
	str r1, [r0, #0xc]
	ldr r1, [r0, #0xc]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	mov r1, #0x0
	str r1, [r0, #0x8]
	bl OS_WakeupThread
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A858C: .word OS_IrqHandler

	arm_func_start WcmCpsifTryLockMutexInIRQ
WcmCpsifTryLockMutexInIRQ: ; 0x020A8590
	ldr r2, [r0, #0x8]
	cmp r2, #0x0
	bne _020A85B8
	ldr r1, _020A85D8 ; =OS_IrqHandler
	str r1, [r0, #0x8]
	ldr r1, [r0, #0xc]
	add r1, r1, #0x1
	str r1, [r0, #0xc]
	mov r0, #0x1
	bx lr
_020A85B8:
	ldr r1, _020A85D8 ; =OS_IrqHandler
	cmp r2, r1
	ldreq r1, [r0, #0xc]
	addeq r1, r1, #0x1
	streq r1, [r0, #0xc]
	moveq r0, #0x1
	movne r0, #0x0
	bx lr
	.balign 4
_020A85D8: .word OS_IrqHandler

	arm_func_start WcmCpsifKACallback
WcmCpsifKACallback: ; 0x020A85DC
	ldr ip, _020A85E8 ; =WcmCpsifUnlockMutexInIRQ
	ldr r0, _020A85EC ; =wcmCpsifw+0xC
	bx r12
	.balign 4
_020A85E8: .word WcmCpsifUnlockMutexInIRQ
_020A85EC: .word wcmCpsifw+0xC

	arm_func_start WcmCpsifWmCallback
WcmCpsifWmCallback: ; 0x020A85F0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r1, [r0, #0x0]
	cmp r1, #0x12
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldrh r2, [r0, #0x2]
	ldr r1, _020A863C ; =wcmCpsifw
	str r2, [r1, #0x24]
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	bne _020A8628
	bl WCMi_ResetKeepAliveAlarm
_020A8628:
	ldr r0, _020A8640 ; =wcmCpsifw+0x4
	bl OS_WakeupThread
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A863C: .word wcmCpsifw
_020A8640: .word wcmCpsifw+0x4

	arm_func_start WCM_SendDCFData
WCM_SendDCFData: ; 0x020A8644
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	mov r6, r2
	bl OS_DisableInterrupts
	mov r5, r0
	bl WCMi_GetSystemWork
	cmp r0, #0x0
	bne _020A867C
	mov r0, r5
	bl OS_RestoreInterrupts
	mvn r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A867C:
	ldr r0, _020A87AC ; =wcmCpsifw+0xC
	bl OS_LockMutex
	bl WCMi_GetSystemWork
	movs r4, r0
	bne _020A86AC
	ldr r0, _020A87AC ; =wcmCpsifw+0xC
	bl OS_UnlockMutex
	mov r0, r5
	bl OS_RestoreInterrupts
	mvn r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A86AC:
	add r0, r4, #0x2000
	ldr r1, [r0, #0x260]
	cmp r1, #0x9
	bne _020A86C8
	ldrb r0, [r0, #0x26b]
	cmp r0, #0x1
	bne _020A86E4
_020A86C8:
	ldr r0, _020A87AC ; =wcmCpsifw+0xC
	bl OS_UnlockMutex
	mov r0, r5
	bl OS_RestoreInterrupts
	mvn r0, #0x3
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A86E4:
	mov r0, r7
	mov r2, r6
	add r1, r4, #0xf00
	bl MI_CpuCopy8
	mov r3, r6, lsl #0x10
	ldr r0, _020A87B0 ; =WcmCpsifWmCallback
	mov r1, r8
	add r2, r4, #0xf00
	mov r3, r3, lsr #0x10
	bl WM_SetDCFData
	cmp r0, #0x8
	addls pc, pc, r0, lsl #0x2
	b _020A873C
_020A8718: ; jump table
	b _020A873C ; case 0
	b _020A873C ; case 1
	b _020A8758 ; case 2
	b _020A873C ; case 3
	b _020A873C ; case 4
	b _020A873C ; case 5
	b _020A873C ; case 6
	b _020A873C ; case 7
	b _020A873C ; case 8
_020A873C:
	ldr r0, _020A87AC ; =wcmCpsifw+0xC
	bl OS_UnlockMutex
	mov r0, r5
	bl OS_RestoreInterrupts
	mvn r0, #0x4
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A8758:
	ldr r0, _020A87B4 ; =wcmCpsifw+0x4
	bl OS_SleepThread
	ldr r0, _020A87B8 ; =wcmCpsifw
	ldr r0, [r0, #0x24]
	cmp r0, #0x0
	beq _020A8790
	cmp r0, #0x1
	ldr r0, _020A87AC ; =wcmCpsifw+0xC
	bl OS_UnlockMutex
	mov r0, r5
	bl OS_RestoreInterrupts
	mvn r0, #0x4
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A8790:
	ldr r0, _020A87AC ; =wcmCpsifw+0xC
	bl OS_UnlockMutex
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r6
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020A87AC: .word wcmCpsifw+0xC
_020A87B0: .word WcmCpsifWmCallback
_020A87B4: .word wcmCpsifw+0x4
_020A87B8: .word wcmCpsifw

	arm_func_start WCM_SetRecvDCFCallback
WCM_SetRecvDCFCallback: ; 0x020A87BC
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _020A87DC ; =wcmCpsifw
	str r4, [r1, #0x28]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A87DC: .word wcmCpsifw

	arm_func_start WCM_GetApEssid
WCM_GetApEssid: ; 0x020A87E0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, #0x0
	mov r4, r0
	mov r6, r7
	bl WCMi_GetSystemWork
	mov r5, r0
	bl OS_DisableInterrupts
	cmp r5, #0x0
	beq _020A8830
	add r1, r5, #0x2000
	ldr r2, [r1, #0x260]
	cmp r2, #0x9
	bne _020A8830
	ldrb r1, [r1, #0x26b]
	cmp r1, #0x0
	addeq r2, r5, #0x2100
	ldreq r1, _020A884C ; =0x0000214C
	ldreqh r6, [r2, #0x4a]
	addeq r7, r5, r1
_020A8830:
	bl OS_RestoreInterrupts
	cmp r4, #0x0
	strneh r6, [r4, #0x0]
	mov r0, r7
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020A884C: .word 0x0000214C

	arm_func_start WCM_GetApMacAddress
WCM_GetApMacAddress:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, #0x0
	bl WCMi_GetSystemWork
	mov r4, r0
	bl OS_DisableInterrupts
	cmp r4, #0x0
	beq _020A8890
	add r1, r4, #0x2000
	ldr r2, [r1, #0x260]
	cmp r2, #0x9
	bne _020A8890
	ldrb r1, [r1, #0x26b]
	cmp r1, #0x0
	ldreq r1, _020A88A4 ; =0x00002144
	addeq r5, r4, r1
_020A8890:
	bl OS_RestoreInterrupts
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A88A4: .word 0x00002144

	arm_func_start WCMi_CpsifSendNullPacket
WCMi_CpsifSendNullPacket: ; 0x020A88A8
	stmdb sp!, {r4,lr}
	bl WCMi_GetSystemWork
	movs r4, r0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	add r0, r4, #0x2000
	ldr r1, [r0, #0x260]
	cmp r1, #0x9
	ldmneia sp!, {r4,lr}
	bxne lr
	ldrb r0, [r0, #0x26b]
	cmp r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, _020A8928 ; =wcmCpsifw+0xC
	bl WcmCpsifTryLockMutexInIRQ
	cmp r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r1, _020A892C ; =0x00002144
	ldr r0, _020A8930 ; =WcmCpsifKACallback
	add r1, r4, r1
	add r2, r4, #0xf00
	mov r3, #0x0
	bl WM_SetDCFData
	cmp r0, #0x2
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, _020A8928 ; =wcmCpsifw+0xC
	bl WcmCpsifUnlockMutexInIRQ
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A8928: .word wcmCpsifw+0xC
_020A892C: .word 0x00002144
_020A8930: .word WcmCpsifKACallback

	arm_func_start WCMi_CpsifRecvCallback
WCMi_CpsifRecvCallback: ; 0x020A8934
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020A8978 ; =wcmCpsifw
	mov r2, r0
	ldr r12, [r1, #0x28]
	cmp r12, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldrh r3, [r2, #0x6]
	add r0, r2, #0x1e
	add r1, r2, #0x18
	add r2, r2, #0x2c
	blx r12
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A8978: .word wcmCpsifw

	arm_func_start WCMi_InitCpsif
WCMi_InitCpsif: ; 0x020A897C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020A89C8 ; =wcmCpsifw
	ldrb r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020A89CC ; =wcmCpsifw+0xC
	mov r2, #0x0
	mov r3, #0x1
	strb r3, [r1, #0x0]
	str r2, [r1, #0x24]
	str r2, [r1, #0x8]
	str r2, [r1, #0x4]
	bl OS_InitMutex
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A89C8: .word wcmCpsifw
_020A89CC: .word wcmCpsifw+0xC
