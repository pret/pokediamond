	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start CARD_UnlockBackup
CARD_UnlockBackup: ; 0x020D66A0
	ldr ip, _020D66AC ; =CARDi_UnlockResource
	mov r1, #0x2
	bx r12
	.balign 4
_020D66AC: .word CARDi_UnlockResource

	arm_func_start CARD_LockBackup
CARD_LockBackup: ; 0x020D66B0
	ldr ip, _020D66BC ; =CARDi_LockResource
	mov r1, #0x2
	bx r12
	.balign 4
_020D66BC: .word CARDi_LockResource

	arm_func_start CARD_UnlockRom
CARD_UnlockRom: ; 0x020D66C0
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_UnlockCard
	mov r0, r4
	mov r1, #0x1
	bl CARDi_UnlockResource
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start CARD_LockRom
CARD_LockRom: ; 0x020D66E0
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r1, #0x1
	bl CARDi_LockResource
	mov r0, r4
	bl OS_TryLockCard
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start CARD_GetResultCode
CARD_GetResultCode: ; 0x020D6700
	ldr r0, _020D6710 ; =0x021D55C0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020D6710: .word 0x021D55C0

	arm_func_start FUN_020D6714
FUN_020D6714: ; 0x020D6714
	ldr r0, _020D672C ; =0x021D55C0
	ldr r0, [r0, #0x114]
	ands r0, r0, #0x4
	moveq r0, #0x1
	movne r0, #0x0
	bx lr
	.balign 4
_020D672C: .word 0x021D55C0

	arm_func_start CARDi_WaitAsync
CARDi_WaitAsync: ; 0x020D6730
	stmdb sp!, {r4-r6,lr}
	ldr r6, _020D6788 ; =0x021D55C0
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x114]
	mov r5, r0
	ands r0, r1, #0x4
	beq _020D6764
	add r4, r6, #0x10c
_020D6750:
	mov r0, r4
	bl OS_SleepThread
	ldr r0, [r6, #0x114]
	ands r0, r0, #0x4
	bne _020D6750
_020D6764:
	mov r0, r5
	bl OS_RestoreInterrupts
_020D676C: ; 0x020D676C
	ldr r0, [r6, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D6788: .word 0x021D55C0

	arm_func_start CARD_Enable
CARD_Enable: ; 0x020D678C
	ldr r1, _020D6798 ; =0x021D555C
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020D6798: .word 0x021D555C

	arm_func_start CARD_CheckEnabled
CARD_CheckEnabled: ; 0x020D679C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl CARD_IsEnabled
_020D67A8: ; 0x020D67A8
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	bl OS_Terminate
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start CARD_IsEnabled
CARD_IsEnabled:
	ldr r0, _020D67D4 ; =0x021D555C
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020D67D4: .word 0x021D555C

	arm_func_start CARDi_InitCommon
CARDi_InitCommon: ; 0x020D67D8
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldr r4, _020D68B8 ; =0x021D55C0
	ldr r1, _020D68BC ; =0x021D5560
	mvn r2, #0x2
	mov r0, #0x0
	str r2, [r4, #0x8]
	mov r2, #0x60
	str r0, [r4, #0xc]
	str r0, [r4, #0x18]
	str r1, [r4, #0x0]
	bl MIi_CpuClearFast
	ldr r0, _020D68BC ; =0x021D5560
	mov r1, #0x60
	bl DC_FlushRange
	ldr r0, _020D68C0 ; =0x027FFC40
	ldrh r0, [r0, #0x0]
	cmp r0, #0x2
	beq _020D6834
	ldr r0, _020D68C4 ; =0x027FFE00
	ldr r1, _020D68C8 ; =0x027FFA80
	mov r2, #0x160
	bl MI_CpuCopy8
_020D6834:
	mov r2, #0x0
	str r2, [r4, #0x14]
	ldr r0, [r4, #0x14]
	mov r1, #0x4
	str r0, [r4, #0x10]
	str r2, [r4, #0x110]
	ldr r3, [r4, #0x110]
	mov r0, #0x400
	str r3, [r4, #0x10c]
	str r1, [r4, #0x108]
	str r0, [sp, #0x0]
	ldr r12, [r4, #0x108]
	ldr r1, _020D68CC ; =CARDi_TaskThread
	ldr r3, _020D68D0 ; =0x021D5BE0
	add r0, r4, #0x44
	str r12, [sp, #0x4]
	bl OS_CreateThread
	add r0, r4, #0x44
	bl OS_WakeupThreadDirect
	ldr r1, _020D68D4 ; =CARDi_OnFifoRecv
	mov r0, #0xb
	bl PXI_SetFifoRecvCallback
	ldr r0, _020D68C0 ; =0x027FFC40
	ldrh r0, [r0, #0x0]
	cmp r0, #0x2
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, #0x1
	bl CARD_Enable
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D68B8: .word 0x021D55C0
_020D68BC: .word 0x021D5560
_020D68C0: .word 0x027FFC40
_020D68C4: .word 0x027FFE00
_020D68C8: .word 0x027FFA80
_020D68CC: .word CARDi_TaskThread
_020D68D0: .word 0x021D5BE0
_020D68D4: .word CARDi_OnFifoRecv

	arm_func_start CARDi_UnlockResource
CARDi_UnlockResource: ; 0x020D68D8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r5, _020D6978 ; =0x021D55C0
	mov r7, r0
	mov r6, r1
	bl OS_DisableInterrupts
	mov r1, r5
	mov r4, r0
	ldr r0, [r1, #0x8]
	cmp r0, r7
	bne _020D6910
	ldr r0, [r5, #0xc]
	cmp r0, #0x0
	bne _020D6918
_020D6910:
	bl OS_Terminate
	b _020D6958
_020D6918:
	ldr r0, [r5, #0x18]
	cmp r0, r6
	beq _020D6928
	bl OS_Terminate
_020D6928:
	ldr r0, [r5, #0xc]
	sub r0, r0, #0x1
	str r0, [r5, #0xc]
	ldr r0, [r5, #0xc]
	cmp r0, #0x0
	bne _020D6958
	mvn r0, #0x2
	str r0, [r5, #0x8]
	mov r1, #0x0
	add r0, r5, #0x10
	str r1, [r5, #0x18]
	bl OS_WakeupThread
_020D6958:
	ldr r1, [r5, #0x0]
	mov r2, #0x0
	mov r0, r4
	str r2, [r1, #0x0]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020D6978: .word 0x021D55C0

	arm_func_start CARDi_LockResource
CARDi_LockResource: ; 0x020D697C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r5, _020D6A14 ; =0x021D55C0
	mov r7, r0
	mov r6, r1
	bl OS_DisableInterrupts
	ldr r1, [r5, #0x8]
	mov r4, r0
	cmp r1, r7
	bne _020D69B8
	ldr r0, [r5, #0x18]
	cmp r0, r6
	beq _020D69E8
	bl OS_Terminate
	b _020D69E8
_020D69B8:
	ldr r0, [r5, #0x8]
	mvn r8, #0x2
	cmp r0, r8
	beq _020D69E0
	add r9, r5, #0x10
_020D69CC:
	mov r0, r9
	bl OS_SleepThread
	ldr r0, [r5, #0x8]
	cmp r0, r8
	bne _020D69CC
_020D69E0:
	str r7, [r5, #0x8]
	str r6, [r5, #0x18]
_020D69E8:
	ldr r1, [r5, #0xc]
	mov r0, r4
	add r1, r1, #0x1
	str r1, [r5, #0xc]
	ldr r1, [r5, #0x0]
	mov r2, #0x0
	str r2, [r1, #0x0]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020D6A14: .word 0x021D55C0

	arm_func_start CARDi_SetTask
CARDi_SetTask: ; 0x020D6A18
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r4, _020D6A5C ; =0x021D55C0
	mov r5, r0
	ldr r1, [r4, #0x108]
	add r0, r4, #0x44
	bl OS_SetThreadPriority
	add r0, r4, #0x44
	str r0, [r4, #0x104]
	str r5, [r4, #0x40]
	ldr r1, [r4, #0x114]
	orr r1, r1, #0x8
	str r1, [r4, #0x114]
	bl OS_WakeupThreadDirect
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D6A5C: .word 0x021D55C0

	arm_func_start FUN_020D6A60
FUN_020D6A60: ; 0x020D6A60
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _020D6D60 ; =0x021D55C0
	mov r5, r0
	ldr r4, [r1, #0x0]
	mov r1, #0x0
	add r0, r4, #0x18
	mov r2, #0x48
	bl MI_CpuFill8
_020D6A84: ; 0x020D6A84
	cmp r5, #0x0
	str r5, [r4, #0x4]
	mov r0, #0x3f
	addeq sp, sp, #0x4
	str r0, [r4, #0x4c]
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	mov r0, r5, asr #0x8
	and r0, r0, #0xff
	mov r2, #0x1
	mov r3, r2, lsl r0
	and r1, r5, #0xff
	str r3, [r4, #0x18]
	mov r0, #0xff
	strb r0, [r4, #0x48]
	cmp r1, #0x1
	bne _020D6B80
	cmp r3, #0x200
	beq _020D6AE4
	cmp r3, #0x2000
	beq _020D6B04
	cmp r3, #0x10000
	beq _020D6B28
	b _020D6D38
_020D6AE4:
	mov r0, #0x10
	str r0, [r4, #0x20]
	str r2, [r4, #0x24]
	mov r0, #0x5
	str r0, [r4, #0x28]
	mov r0, #0xf0
	strb r0, [r4, #0x48]
	b _020D6B48
_020D6B04:
	mov r0, #0x20
	str r0, [r4, #0x20]
	mov r0, #0x2
	str r0, [r4, #0x24]
	mov r0, #0x5
	str r0, [r4, #0x28]
	mov r0, #0x0
	strb r0, [r4, #0x48]
	b _020D6B48
_020D6B28:
	mov r0, #0x80
	str r0, [r4, #0x20]
	mov r0, #0x2
	str r0, [r4, #0x24]
	mov r0, #0xa
	str r0, [r4, #0x28]
	mov r0, #0x0
	strb r0, [r4, #0x48]
_020D6B48:
	ldr r0, [r4, #0x20]
	add sp, sp, #0x4
	str r0, [r4, #0x1c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x40
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x100
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x200
	str r0, [r4, #0x4c]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D6B80:
	cmp r1, #0x2
	bne _020D6CD8
	cmp r3, #0x100000
	bhi _020D6BB8
	cmp r3, #0x100000
	bhs _020D6BD8
	cmp r3, #0x40000
	bhi _020D6BAC
	cmp r3, #0x40000
	beq _020D6BD8
	b _020D6D38
_020D6BAC:
	cmp r3, #0x80000
	beq _020D6BD8
	b _020D6D38
_020D6BB8:
	cmp r3, #0x200000
	bhi _020D6BCC
	cmp r3, #0x200000
	beq _020D6C10
	b _020D6D38
_020D6BCC:
	cmp r3, #0x800000
	beq _020D6C48
	b _020D6D38
_020D6BD8:
	mov r0, #0x19
	str r0, [r4, #0x2c]
	mov r1, #0x12c
	str r1, [r4, #0x30]
	ldr r0, _020D6D64 ; =0x00001388
	str r1, [r4, #0x44]
	str r0, [r4, #0x3c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x80
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x400
	str r0, [r4, #0x4c]
	b _020D6C7C
_020D6C10:
	mov r1, #0x3e8
	ldr r0, _020D6D68 ; =0x00000BB8
	str r1, [r4, #0x3c]
	ldr r1, _020D6D6C ; =0x00004268
	str r0, [r4, #0x40]
	ldr r0, _020D6D70 ; =0x00009C40
	str r1, [r4, #0x34]
	str r0, [r4, #0x38]
	mov r0, #0x0
	strb r0, [r4, #0x48]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x1000
	str r0, [r4, #0x4c]
	b _020D6C7C
_020D6C48:
	mov r1, #0x3e8
	ldr r0, _020D6D68 ; =0x00000BB8
	str r1, [r4, #0x3c]
	ldr r1, _020D6D74 ; =0x000109A0
	str r0, [r4, #0x40]
	ldr r0, _020D6D78 ; =0x00027100
	str r1, [r4, #0x34]
	str r0, [r4, #0x38]
	mov r0, #0x0
	strb r0, [r4, #0x48]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x1000
	str r0, [r4, #0x4c]
_020D6C7C:
	mov r0, #0x10000
	str r0, [r4, #0x1c]
	mov r0, #0x100
	str r0, [r4, #0x20]
	mov r0, #0x3
	str r0, [r4, #0x24]
	mov r0, #0x5
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x4c]
	add sp, sp, #0x4
	orr r0, r0, #0x40
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x100
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x200
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x800
	str r0, [r4, #0x4c]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D6CD8:
	cmp r1, #0x3
	bne _020D6D38
	cmp r3, #0x2000
	beq _020D6CF0
	cmp r3, #0x8000
	bne _020D6D38
_020D6CF0:
	str r3, [r4, #0x20]
	str r3, [r4, #0x1c]
	mov r0, #0x2
	str r0, [r4, #0x24]
	mov r0, #0x0
	strb r0, [r4, #0x48]
	ldr r0, [r4, #0x4c]
	add sp, sp, #0x4
	orr r0, r0, #0x40
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x100
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x200
	str r0, [r4, #0x4c]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D6D38:
	mov r1, #0x0
	str r1, [r4, #0x4]
	str r1, [r4, #0x18]
	ldr r0, _020D6D60 ; =0x021D55C0
	mov r1, #0x3
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D6D60: .word 0x021D55C0
_020D6D64: .word 0x00001388
_020D6D68: .word 0x00000BB8
_020D6D6C: .word 0x00004268
_020D6D70: .word 0x00009C40
_020D6D74: .word 0x000109A0
_020D6D78: .word 0x00027100

	arm_func_start CARD_CancelBackupAsync
CARD_CancelBackupAsync: ; 0x020D6D7C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r1, _020D6DA8 ; =0x021D55C0
	ldr r2, [r1, #0x114]
	orr r2, r2, #0x40
	str r2, [r1, #0x114]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D6DA8: .word 0x021D55C0

	arm_func_start CARD_TryWaitBackupAsync
CARD_TryWaitBackupAsync: ; 0x020D6DAC
	ldr ip, _020D6DB4 ; =FUN_020D6714
	bx r12
	.balign 4
_020D6DB4: .word FUN_020D6714

	arm_func_start CARD_WaitBackupAsync
CARD_WaitBackupAsync: ; 0x020D6DB8
	ldr ip, _020D6DC0 ; =CARDi_WaitAsync
	bx r12
	.balign 4
_020D6DC0: .word CARDi_WaitAsync

	arm_func_start CARD_IdentifyBackup
CARD_IdentifyBackup: ; 0x020D6DC4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, _020D6F00 ; =0x02000C3C
	ldr r7, _020D6F04 ; =0x021D55C0
	bl OSi_ReferSymbol
_020D6DDC: ; 0x020D6DDC
	cmp r5, #0x0
	bne _020D6DE8
	bl OS_Terminate
_020D6DE8:
	bl CARD_CheckEnabled
	bl OS_DisableInterrupts
	ldr r1, [r7, #0x114]
	mov r4, r0
	ands r0, r1, #0x4
	beq _020D6E18
	add r6, r7, #0x10c
_020D6E04:
	mov r0, r6
	bl OS_SleepThread
	ldr r0, [r7, #0x114]
	ands r0, r0, #0x4
	bne _020D6E04
_020D6E18:
	ldr r0, [r7, #0x114]
	mov r1, #0x0
	orr r0, r0, #0x4
	str r0, [r7, #0x114]
	str r1, [r7, #0x38]
	mov r0, r4
	str r1, [r7, #0x3c]
	bl OS_RestoreInterrupts
	mov r0, r5
	bl FUN_020D6A60
	ldr r0, _020D6F08 ; =0x021D3498
	ldr r1, _020D6F04 ; =0x021D55C0
	ldr r2, [r0, #0x4]
	mov r0, r7
	str r2, [r1, #0x104]
	mov r1, #0x2
	mov r2, #0x1
	bl CARDi_Request
_020D6E60: ; 0x020D6E60
	ldr r0, [r7, #0x0]
	mov r1, #0x0
	str r1, [r0, #0xc]
	ldr r0, [r7, #0x0]
	add r1, r7, #0x120
	str r1, [r0, #0x10]
	ldr r1, [r7, #0x0]
	mov r2, #0x1
	mov r0, r7
	str r2, [r1, #0x14]
	mov r1, #0x6
	bl CARDi_Request
	ldr r6, [r7, #0x38]
	ldr r5, [r7, #0x3c]
	bl OS_DisableInterrupts
	mov r4, r0
	ldr r1, [r7, #0x114]
	add r0, r7, #0x10c
	bic r1, r1, #0x4c
	str r1, [r7, #0x114]
	bl OS_WakeupThread
	ldr r0, [r7, #0x114]
	ands r0, r0, #0x10
	beq _020D6EC8
	add r0, r7, #0x44
	bl OS_WakeupThreadDirect
_020D6EC8:
	mov r0, r4
	bl OS_RestoreInterrupts
_020D6ED0: ; 0x020D6ED0
	cmp r6, #0x0
	beq _020D6EE0
	mov r0, r5
	blx r6
_020D6EE0:
	ldr r0, [r7, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020D6F00: .word 0x02000C3C
_020D6F04: .word 0x021D55C0
_020D6F08: .word 0x021D3498

	arm_func_start CARD_GetBackupSectorSize
CARD_GetBackupSectorSize: ; 0x020D6F0C
	ldr r0, _020D6F1C ; =0x021D55C0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x1c]
	bx lr
	.balign 4
_020D6F1C: .word 0x021D55C0

	arm_func_start CARDi_RequestStreamCommand
CARDi_RequestStreamCommand: ; 0x020D6F20
	stmdb sp!, {r4-r10,lr}
	mov r10, r0
	ldr r6, _020D7004 ; =0x021D55C0
	ldr r0, _020D7008 ; =0x02000C3C
	mov r9, r1
	mov r8, r2
	mov r7, r3
	bl OSi_ReferSymbol
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x114]
	mov r5, r0
	ands r0, r1, #0x4
	beq _020D6F6C
	add r4, r6, #0x10c
_020D6F58:
	mov r0, r4
	bl OS_SleepThread
	ldr r0, [r6, #0x114]
	ands r0, r0, #0x4
	bne _020D6F58
_020D6F6C:
	ldr r0, [r6, #0x114]
	ldr r1, [sp, #0x20]
	orr r0, r0, #0x4
	str r0, [r6, #0x114]
	str r7, [r6, #0x38]
	mov r0, r5
	str r1, [r6, #0x3c]
	bl OS_RestoreInterrupts
	str r10, [r6, #0x1c]
	str r9, [r6, #0x20]
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0x28]
	str r8, [r6, #0x24]
	ldr r2, [sp, #0x2c]
	str r1, [r6, #0x2c]
	ldr r1, [sp, #0x30]
	str r2, [r6, #0x30]
	str r1, [r6, #0x34]
	cmp r0, #0x0
	beq _020D6FD0
	ldr r0, _020D700C ; =CARDi_RequestStreamCommandCore
	bl CARDi_SetTask
	mov r0, #0x1
	ldmia sp!, {r4-r10,lr}
	bx lr
_020D6FD0:
	ldr r0, _020D7010 ; =0x021D3498
	ldr r1, _020D7004 ; =0x021D55C0
	ldr r2, [r0, #0x4]
	mov r0, r6
	str r2, [r1, #0x104]
	bl CARDi_RequestStreamCommandCore
_020D6FE8: ; 0x020D6FE8
	ldr r0, [r6, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_020D7004: .word 0x021D55C0
_020D7008: .word 0x02000C3C
_020D700C: .word CARDi_RequestStreamCommandCore
_020D7010: .word 0x021D3498

	arm_func_start CARDi_RequestStreamCommandCore
CARDi_RequestStreamCommandCore:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r9, r0
	ldr r8, [r9, #0x2c]
	ldr r0, _020D720C ; =0x02000C3C
	ldr r7, [r9, #0x34]
	ldr r10, [r9, #0x30]
	mov r6, #0x100
	bl OSi_ReferSymbol
	cmp r8, #0xb
	bne _020D7048
	bl CARD_GetBackupSectorSize
	mov r6, r0
_020D7048:
	mov r0, #0x1
	add r4, r9, #0x120
	mov r11, #0x9
	str r0, [sp, #0x0]
_020D7058:
	ldr r5, [r9, #0x24]
	ldr r0, [r9, #0x0]
	cmp r6, r5
	movcc r5, r6
	str r5, [r0, #0x14]
	ldr r0, [r9, #0x114]
	ands r0, r0, #0x40
	beq _020D7094
	ldr r0, [r9, #0x114]
	mov r1, #0x7
	bic r0, r0, #0x40
	str r0, [r9, #0x114]
	ldr r0, [r9, #0x0]
	str r1, [r0, #0x0]
	b _020D71A8
_020D7094:
	cmp r7, #0x3
	addls pc, pc, r7, lsl #0x2
	b _020D7124
_020D70A0:
	b _020D70B0
_020D70A4:
	b _020D70D4
_020D70A8:
	b _020D70D4
_020D70AC:
	b _020D710C
_020D70B0:
	mov r1, r5
	add r0, r9, #0x120
	bl DC_InvalidateRange
	ldr r1, [r9, #0x1c]
	ldr r0, [r9, #0x0]
	str r1, [r0, #0xc]
	ldr r0, [r9, #0x0]
	str r4, [r0, #0x10]
	b _020D7124
_020D70D4:
	ldr r0, [r9, #0x1c]
	mov r1, r4
	mov r2, r5
	bl MI_CpuCopy8
	mov r1, r5
	add r0, r9, #0x120
	bl DC_FlushRange
	bl DC_WaitWriteBufferEmpty
_020D70F4: ; 0x020D70F4
	ldr r0, [r9, #0x0]
	str r4, [r0, #0xc]
	ldr r1, [r9, #0x20]
	ldr r0, [r9, #0x0]
	str r1, [r0, #0x10]
	b _020D7124
_020D710C:
	ldr r1, [r9, #0x1c]
	ldr r0, [r9, #0x0]
	str r1, [r0, #0xc]
	ldr r1, [r9, #0x20]
	ldr r0, [r9, #0x0]
	str r1, [r0, #0x10]
_020D7124:
	mov r0, r9
	mov r1, r8
	mov r2, r10
	bl CARDi_Request
_020D7134: ; 0x020D7134
	cmp r0, #0x0
	beq _020D71A8
	cmp r7, #0x2
	bne _020D7160
	ldr r2, [sp, #0x0]
	mov r0, r9
	mov r1, r11
	bl CARDi_Request
_020D7154: ; 0x020D7154
	cmp r0, #0x0
	bne _020D7178
	b _020D71A8
_020D7160:
	cmp r7, #0x0
	bne _020D7178
	ldr r1, [r9, #0x20]
	mov r2, r5
	add r0, r9, #0x120
	bl MI_CpuCopy8
_020D7178:
	ldr r0, [r9, #0x1c]
	add r0, r0, r5
	str r0, [r9, #0x1c]
	ldr r0, [r9, #0x20]
	add r0, r0, r5
	str r0, [r9, #0x20]
	ldr r0, [r9, #0x24]
	sub r0, r0, r5
	str r0, [r9, #0x24]
	ldr r0, [r9, #0x24]
	cmp r0, #0x0
	bne _020D7058
_020D71A8:
	ldr r6, [r9, #0x38]
	ldr r5, [r9, #0x3c]
	bl OS_DisableInterrupts
	ldr r1, [r9, #0x114]
	mov r4, r0
	bic r0, r1, #0x4c
	str r0, [r9, #0x114]
	add r0, r9, #0x10c
	bl OS_WakeupThread
	ldr r0, [r9, #0x114]
	ands r0, r0, #0x10
	beq _020D71E0
	add r0, r9, #0x44
	bl OS_WakeupThreadDirect
_020D71E0:
	mov r0, r4
	bl OS_RestoreInterrupts
_020D71E8: ; 0x020D71E8
	cmp r6, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	mov r0, r5
	blx r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020D720C: .word 0x02000C3C

	arm_func_start CARDi_GetRomAccessor
CARDi_GetRomAccessor: ; 0x020D7210
	ldr r0, _020D7218 ; =CARDi_ReadCard
	bx lr
	.balign 4
_020D7218: .word CARDi_ReadCard

	arm_func_start CARD_WaitRomAsync
CARD_WaitRomAsync: ; 0x020D721C
	ldr ip, _020D7224 ; =CARDi_WaitAsync
	bx r12
	.balign 4
_020D7224: .word CARDi_WaitAsync

	arm_func_start CARD_Init
CARD_Init: ; 0x020D7228
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr ip, _020D72A0 ; =0x021D55C0
	ldr r0, [r12, #0x114]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	mov r0, #0x1
	str r0, [r12, #0x114]
	mov r3, #0x0
	str r3, [r12, #0x24]
	ldr r0, [r12, #0x24]
	mvn r1, #0x0
	str r0, [r12, #0x20]
	ldr r2, [r12, #0x20]
	ldr r0, _020D72A4 ; =0x021D5BE0
	str r2, [r12, #0x1c]
	str r1, [r12, #0x28]
	str r3, [r12, #0x38]
	str r3, [r12, #0x3c]
	str r3, [r0, #0x0]
	bl CARDi_InitCommon
	bl CARDi_GetRomAccessor
	ldr r1, _020D72A8 ; =0x021D5C00
	str r0, [r1, #0x0]
	bl CARD_InitPulledOutCallback
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D72A0: .word 0x021D55C0
_020D72A4: .word 0x021D5BE0
_020D72A8: .word 0x021D5C00

	arm_func_start CARDi_ReadRom
CARDi_ReadRom: ; 0x020D72AC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r6, _020D73C0 ; =0x021D55C0
	mov r10, r0
	mov r9, r1
	mov r8, r2
	mov r7, r3
	ldr fp, _020D73C4 ; =0x021D5C00
	bl CARD_CheckEnabled
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x114]
	mov r5, r0
	ands r0, r1, #0x4
	beq _020D72FC
	add r4, r6, #0x10c
_020D72E8:
	mov r0, r4
	bl OS_SleepThread
	ldr r0, [r6, #0x114]
	ands r0, r0, #0x4
	bne _020D72E8
_020D72FC:
	ldr r1, [r6, #0x114]
	ldr r0, [sp, #0x28]
	orr r1, r1, #0x4
	str r1, [r6, #0x114]
	ldr r1, [sp, #0x2c]
	str r0, [r6, #0x38]
	mov r0, r5
	str r1, [r6, #0x3c]
	bl OS_RestoreInterrupts
	ldr r0, _020D73C8 ; =0x021D5BE0
	str r10, [r6, #0x28]
	ldr r0, [r0, #0x0]
	cmp r10, #0x3
	add r0, r9, r0
	str r0, [r6, #0x1c]
	str r8, [r6, #0x20]
	str r7, [r6, #0x24]
	bhi _020D734C
	mov r0, r10
	bl MI_StopDma
_020D734C:
	mov r0, r11
	bl CARDi_TryReadCardDma
_020D7354: ; 0x020D7354
	cmp r0, #0x0
	beq _020D7380
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	bl CARD_WaitRomAsync
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D7380:
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	beq _020D73A0
	ldr r0, _020D73CC ; =CARDi_ReadRomSyncCore
	bl CARDi_SetTask
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D73A0:
	ldr r1, _020D73D0 ; =0x021D3498
	mov r0, r6
	ldr r1, [r1, #0x4]
	str r1, [r6, #0x104]
	bl CARDi_ReadRomSyncCore
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020D73C0: .word 0x021D55C0
_020D73C4: .word 0x021D5C00
_020D73C8: .word 0x021D5BE0
_020D73CC: .word CARDi_ReadRomSyncCore
_020D73D0: .word 0x021D3498

	arm_func_start CARDi_ReadRomSyncCore
CARDi_ReadRomSyncCore: ; 0x020D73D4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r4, _020D7478 ; =0x021D5C00
	mov r0, r4
	bl CARDi_ReadFromCache
_020D73E8: ; 0x020D73E8
	cmp r0, #0x0
	beq _020D73FC
	ldr r1, [r4, #0x0]
	mov r0, r4
	blx r1
_020D73FC:
	ldr r7, _020D747C ; =0x021D55C0
	bl CARDi_ReadRomIDCore
	bl CARDi_CheckPulledOutCore
_020D7408: ; 0x020D7408
	ldr r0, [r7, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
	ldr r6, [r7, #0x38]
	ldr r5, [r7, #0x3c]
	bl OS_DisableInterrupts
	ldr r1, [r7, #0x114]
	mov r4, r0
	bic r0, r1, #0x4c
	str r0, [r7, #0x114]
	add r0, r7, #0x10c
	bl OS_WakeupThread
	ldr r0, [r7, #0x114]
	ands r0, r0, #0x10
	beq _020D744C
	add r0, r7, #0x44
	bl OS_WakeupThreadDirect
_020D744C:
	mov r0, r4
	bl OS_RestoreInterrupts
_020D7454: ; 0x020D7454
	cmp r6, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r5
	blx r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020D7478: .word 0x021D5C00
_020D747C: .word 0x021D55C0

	arm_func_start CARDi_ReadRomIDCore
CARDi_ReadRomIDCore: ; 0x020D7480
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, #0xb8000000
	mov r1, #0x0
	bl CARDi_SetRomOp
	ldr r1, _020D74DC ; =0x02106A50
	mov r0, #0x2000
	ldr r1, [r1, #0x0]
	rsb r0, r0, #0x0
	ldr r2, [r1, #0x60]
	ldr r1, _020D74E0 ; =0x040001A4
	bic r2, r2, #0x7000000
	orr r2, r2, #0xa7000000
	and r0, r2, r0
	str r0, [r1, #0x0]
_020D74BC:
	ldr r0, [r1, #0x0]
	ands r0, r0, #0x800000
	beq _020D74BC
	ldr r0, _020D74E4 ; =0x04100010
	ldr r0, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D74DC: .word 0x02106A50
_020D74E0: .word 0x040001A4
_020D74E4: .word 0x04100010

	arm_func_start CARDi_ReadCard
CARDi_ReadCard: ; 0x020D74E8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r10, r0
	ldr sb, _020D75DC ; =0x021D55C0
	add r7, r10, #0x20
	ldr r5, _020D75E0 ; =0x04100010
	ldr r6, _020D75E4 ; =0x040001A4
	mov r11, #0x0
	mov r0, #0x200
	rsb r4, r0, #0x0
_020D7510:
	ldr r0, [r9, #0x1c]
	and r1, r0, r4
	cmp r1, r0
	bne _020D7538
	ldr r8, [r9, #0x20]
	ands r0, r8, #0x3
	bne _020D7538
	ldr r0, [r9, #0x24]
	cmp r0, #0x200
	bhs _020D7540
_020D7538:
	mov r8, r7
	str r1, [r10, #0x8]
_020D7540:
	mov r0, r1, lsr #0x8
	orr r0, r0, #0xb7000000
	mov r1, r1, lsl #0x18
	bl CARDi_SetRomOp
	ldr r1, [r10, #0x4]
	mov r0, r11
	str r1, [r6, #0x0]
_020D755C:
	ldr r2, [r6, #0x0]
	ands r1, r2, #0x800000
	beq _020D7578
	ldr r1, [r5, #0x0]
	cmp r0, #0x200
	strcc r1, [r8, r0, lsl #0x2]
	addcc r0, r0, #0x1
_020D7578:
	ands r1, r2, #0x80000000
	bne _020D755C
	ldr r0, [r9, #0x20]
	cmp r8, r0
	bne _020D75C0
	ldr r2, [r9, #0x1c]
	ldr r1, [r9, #0x20]
	ldr r0, [r9, #0x24]
	add r2, r2, #0x200
	add r1, r1, #0x200
	subs r0, r0, #0x200
	str r2, [r9, #0x1c]
	str r1, [r9, #0x20]
	str r0, [r9, #0x24]
	bne _020D7510
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D75C0:
	mov r0, r10
	bl CARDi_ReadFromCache
_020D75C8: ; 0x020D75C8
	cmp r0, #0x0
	bne _020D7510
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020D75DC: .word 0x021D55C0
_020D75E0: .word 0x04100010
_020D75E4: .word 0x040001A4

	arm_func_start CARDi_TryReadCardDma
CARDi_TryReadCardDma:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr fp, _020D7748 ; =0x021D55C0
	mov r7, #0x0
	ldr r9, [r11, #0x20]
	mov r10, r0
	mov r6, r7
	mov r5, r7
	mov r1, r7
	ands r4, r9, #0x1f
	ldr r8, [r11, #0x24]
	bne _020D7624
	ldr r0, [r11, #0x28]
	cmp r0, #0x3
	movls r1, #0x1
_020D7624:
	cmp r1, #0x0
	beq _020D7678
	bl OS_GetDTCMAddress
	ldr r1, _020D774C ; =0x01FF8000
	add r2, r9, r8
	cmp r2, r1
	mov r3, #0x1
	mov r1, #0x0
	bls _020D7650
	cmp r9, #0x2000000
	movcc r1, r3
_020D7650:
	cmp r1, #0x0
	bne _020D7670
	cmp r0, r2
	bhs _020D766C
	add r0, r0, #0x4000
	cmp r0, r9
	bhi _020D7670
_020D766C:
	mov r3, #0x0
_020D7670:
	cmp r3, #0x0
	moveq r5, #0x1
_020D7678:
	cmp r5, #0x0
	beq _020D7694
	ldr r1, [r11, #0x1c]
	ldr r0, _020D7750 ; =0x000001FF
	orr r1, r1, r8
	ands r0, r1, r0
	moveq r6, #0x1
_020D7694:
	cmp r6, #0x0
	beq _020D76A4
	cmp r8, #0x0
	movne r7, #0x1
_020D76A4:
	ldr r0, _020D7754 ; =0x02106A50
	cmp r7, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x60]
	bic r0, r0, #0x7000000
	orr r0, r0, #0xa1000000
	str r0, [r10, #0x4]
	beq _020D7738
	bl OS_DisableInterrupts
	mov r5, r0
	mov r0, r9
	mov r1, r8
	bl IC_InvalidateRange
_020D76D8: ; 0x020D76D8
	cmp r4, #0x0
	beq _020D7700
	sub r9, r9, r4
	mov r0, r9
	mov r1, #0x20
	bl DC_StoreRange
	add r0, r9, r8
	mov r1, #0x20
	bl DC_StoreRange
	add r8, r8, #0x20
_020D7700:
	mov r0, r9
	mov r1, r8
	bl DC_InvalidateRange
	bl DC_WaitWriteBufferEmpty
	ldr r1, _020D7758 ; =CARDi_OnReadCard
	mov r0, #0x80000
	bl OS_SetIrqFunction
	mov r0, #0x80000
	bl OS_ResetRequestIrqMask
	mov r0, #0x80000
	bl OS_EnableIrqMask
	mov r0, r5
	bl OS_RestoreInterrupts
	bl CARDi_SetCardDma
_020D7738:
	mov r0, r7
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020D7748: .word cardi_common
_020D774C: .word 0x01FF8000
_020D7750: .word 0x000001FF
_020D7754: .word 0x02106A50
_020D7758: .word CARDi_OnReadCard

	arm_func_start CARDi_OnReadCard
CARDi_OnReadCard: ; 0x020D775C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r0, _020D7838 ; =0x021D55C0
	ldr r0, [r0, #0x28]
	bl MI_StopDma
	ldr r0, _020D7838 ; =0x021D55C0
	ldr r3, [r0, #0x1c]
	ldr r2, [r0, #0x20]
	ldr r1, [r0, #0x24]
	add r3, r3, #0x200
	add r2, r2, #0x200
	subs r1, r1, #0x200
	str r3, [r0, #0x1c]
	str r2, [r0, #0x20]
	str r1, [r0, #0x24]
	bne _020D7828
	mov r0, #0x80000
	bl OS_DisableIrqMask
	mov r0, #0x80000
	bl OS_ResetRequestIrqMask
	ldr r7, _020D7838 ; =0x021D55C0
	bl CARDi_ReadRomIDCore
	bl CARDi_CheckPulledOutCore
_020D77B8: ; 0x020D77B8
	ldr r0, [r7, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
	ldr r6, [r7, #0x38]
	ldr r5, [r7, #0x3c]
	bl OS_DisableInterrupts
	ldr r1, [r7, #0x114]
	mov r4, r0
	bic r0, r1, #0x4c
	str r0, [r7, #0x114]
	add r0, r7, #0x10c
	bl OS_WakeupThread
	ldr r0, [r7, #0x114]
	ands r0, r0, #0x10
	beq _020D77FC
	add r0, r7, #0x44
	bl OS_WakeupThreadDirect
_020D77FC:
	mov r0, r4
	bl OS_RestoreInterrupts
_020D7804: ; 0x020D7804
	cmp r6, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r5
	blx r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D7828:
	bl CARDi_SetCardDma
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020D7838: .word 0x021D55C0

	arm_func_start CARDi_SetCardDma
CARDi_SetCardDma: ; 0x020D783C
	stmdb sp!, {r4,lr}
	ldr r4, _020D7884 ; =0x021D55C0
	ldr r1, _020D7888 ; =0x04100010
	ldr r0, [r4, #0x28]
	ldr r2, [r4, #0x20]
	mov r3, #0x200
	bl MIi_CardDmaCopy32
	ldr r1, [r4, #0x1c]
	mov r0, r1, lsr #0x8
	orr r0, r0, #0xb7000000
	mov r1, r1, lsl #0x18
	bl CARDi_SetRomOp
	ldr r0, _020D788C ; =0x021D5C00
	ldr r1, _020D7890 ; =0x040001A4
	ldr r0, [r0, #0x4]
	str r0, [r1, #0x0]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D7884: .word 0x021D55C0
_020D7888: .word 0x04100010
_020D788C: .word 0x021D5C00
_020D7890: .word 0x040001A4

	arm_func_start CARDi_SetRomOp
CARDi_SetRomOp: ; 0x020D7894
	ldr r3, _020D790C ; =0x040001A4
_020D7898:
	ldr r2, [r3, #0x0]
	ands r2, r2, #0x80000000
	bne _020D7898
	ldr r3, _020D7910 ; =0x040001A1
	mov r12, #0xc0
	ldr r2, _020D7914 ; =0x040001A8
	strb r12, [r3, #0x0]
	mov r12, r0, lsr #0x18
	ldr r3, _020D7918 ; =0x040001A9
	strb r12, [r2, #0x0]
	mov r12, r0, lsr #0x10
	ldr r2, _020D791C ; =0x040001AA
	strb r12, [r3, #0x0]
	mov r12, r0, lsr #0x8
	ldr r3, _020D7920 ; =0x040001AB
	strb r12, [r2, #0x0]
	ldr r2, _020D7924 ; =0x040001AC
	strb r0, [r3, #0x0]
	mov r3, r1, lsr #0x18
	ldr r0, _020D7928 ; =0x040001AD
	strb r3, [r2, #0x0]
	mov r3, r1, lsr #0x10
	ldr r2, _020D792C ; =0x040001AE
	strb r3, [r0, #0x0]
	mov r3, r1, lsr #0x8
	ldr r0, _020D7930 ; =0x040001AF
	strb r3, [r2, #0x0]
	strb r1, [r0, #0x0]
	bx lr
	.balign 4
_020D790C: .word 0x040001A4
_020D7910: .word 0x040001A1
_020D7914: .word 0x040001A8
_020D7918: .word 0x040001A9
_020D791C: .word 0x040001AA
_020D7920: .word 0x040001AB
_020D7924: .word 0x040001AC
_020D7928: .word 0x040001AD
_020D792C: .word 0x040001AE
_020D7930: .word 0x040001AF

	arm_func_start CARDi_ReadFromCache
CARDi_ReadFromCache:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r5, _020D79C8 ; =0x021D55C0
	mov r1, #0x200
	ldr r3, [r5, #0x1c]
	rsb r1, r1, #0x0
	ldr r2, [r0, #0x8]
	and r3, r3, r1
	cmp r3, r2
	bne _020D79AC
	ldr r2, [r5, #0x1c]
	ldr r1, [r5, #0x24]
	sub r3, r2, r3
	rsb r4, r3, #0x200
	cmp r4, r1
	movhi r4, r1
	add r0, r0, #0x20
	ldr r1, [r5, #0x20]
	mov r2, r4
	add r0, r0, r3
	bl MI_CpuCopy8
	ldr r0, [r5, #0x1c]
	add r0, r0, r4
	str r0, [r5, #0x1c]
	ldr r0, [r5, #0x20]
	add r0, r0, r4
	str r0, [r5, #0x20]
	ldr r0, [r5, #0x24]
	sub r0, r0, r4
	str r0, [r5, #0x24]
_020D79AC:
	ldr r0, [r5, #0x24]
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D79C8: .word 0x021D55C0

	arm_func_start CARDi_Request
CARDi_Request:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r6, r0
	ldr r0, [r6, #0x114]
	mov r5, r1
	mov r4, r2
	ands r0, r0, #0x2
	bne _020D7A44
	ldr r1, [r6, #0x114]
	mov r0, #0xb
	orr r2, r1, #0x2
	mov r1, #0x1
	str r2, [r6, #0x114]
	bl PXI_IsCallbackReady
_020D7A04: ; 0x020D7A04
	cmp r0, #0x0
	bne _020D7A34
	mov r9, #0x64
	mov r8, #0xb
	mov r7, #0x1
_020D7A18:
	mov r0, r9
	bl OS_SpinWait
	mov r0, r8
	mov r1, r7
	bl PXI_IsCallbackReady
_020D7A2C: ; 0x020D7A2C
	cmp r0, #0x0
	beq _020D7A18
_020D7A34:
	mov r0, r6
	mov r1, #0x0
	mov r2, #0x1
	bl CARDi_Request
_020D7A44:
	ldr r0, [r6, #0x0]
	mov r1, #0x60
	bl DC_FlushRange
	bl DC_WaitWriteBufferEmpty
	mov r9, #0xb
	mov r8, #0x1
	mov r7, #0x0
	mov r11, #0x60
_020D7A64:
	str r5, [r6, #0x4]
	ldr r0, [r6, #0x114]
	orr r0, r0, #0x20
	str r0, [r6, #0x114]
_020D7A74:
	mov r0, r9
	mov r1, r5
	mov r2, r8
	bl PXI_SendWordByFifo
_020D7A84: ; 0x020D7A84
	cmp r0, #0x0
	blt _020D7A74
	cmp r5, #0x0
	bne _020D7AB0
	ldr r10, [r6, #0x0]
_020D7A98:
	mov r0, r9
	mov r1, r10
	mov r2, r8
	bl PXI_SendWordByFifo
_020D7AA8: ; 0x020D7AA8
	cmp r0, #0x0
	blt _020D7A98
_020D7AB0:
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x114]
	mov r10, r0
	ands r0, r1, #0x20
	beq _020D7AD8
_020D7AC4:
	mov r0, r7
	bl OS_SleepThread
	ldr r0, [r6, #0x114]
	ands r0, r0, #0x20
	bne _020D7AC4
_020D7AD8:
	mov r0, r10
	bl OS_RestoreInterrupts
_020D7AE0: ; 0x020D7AE0
	ldr r0, [r6, #0x0]
	mov r1, r11
	bl DC_InvalidateRange
_020D7AEC: ; 0x020D7AEC
	ldr r0, [r6, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x4
	bne _020D7B08
	sub r4, r4, #0x1
	cmp r4, #0x0
	bgt _020D7A64
_020D7B08:
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start CARDi_TaskThread
CARDi_TaskThread: ; 0x020D7B20
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r5, _020D7B78 ; =0x021D55C0
	mov r6, #0x0
	add r7, r5, #0x44
_020D7B34:
	bl OS_DisableInterrupts
	ldr r1, [r5, #0x114]
	mov r4, r0
	ands r0, r1, #0x8
	bne _020D7B60
_020D7B48:
	mov r0, r6
	str r7, [r5, #0x104]
	bl OS_SleepThread
	ldr r0, [r5, #0x114]
	ands r0, r0, #0x8
	beq _020D7B48
_020D7B60:
	mov r0, r4
	bl OS_RestoreInterrupts
	ldr r1, [r5, #0x40]
	mov r0, r5
	blx r1
	b _020D7B34
	.balign 4
_020D7B78: .word 0x021D55C0

	arm_func_start CARDi_OnFifoRecv
CARDi_OnFifoRecv: ; 0x020D7B7C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0xb
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r1, _020D7BC8 ; =0x021D55C0
	ldr r0, [r1, #0x114]
	bic r0, r0, #0x20
	str r0, [r1, #0x114]
	ldr r0, [r1, #0x104]
	bl OS_WakeupThreadDirect
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D7BC8: .word 0x021D55C0

	arm_func_start CARDi_SendtoPxi
CARDi_SendtoPxi: ; 0x020D7BCC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r1, r7
	mov r0, #0xe
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020D7BEC: ; 0x020D7BEC
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r5, #0xe
	mov r4, #0x0
_020D7C04:
	mov r0, r6
	blx FUN_020005F2
	mov r0, r5
	mov r1, r7
	mov r2, r4
	bl PXI_SendWordByFifo
_020D7C1C: ; 0x020D7C1C
	cmp r0, #0x0
	bne _020D7C04
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start CARDi_CheckPulledOutCore
CARDi_CheckPulledOutCore:
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldr r1, _020D7C94 ; =0x027FFC10
	ldrh r1, [r1, #0x0]
	cmp r1, #0x0
	ldreq r1, _020D7C98 ; =0x027FF800
	ldrne r1, _020D7C9C ; =0x027FFC00
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x0]
	cmp r0, r1
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl OS_DisableInterrupts
	mov r4, r0
	mov r0, #0xe
	mov r1, #0x11
	mov r2, #0x0
	bl CARDi_PulledOutCallback
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D7C94: .word 0x027FFC10
_020D7C98: .word 0x027FF800
_020D7C9C: .word 0x027FFC00

	arm_func_start CARD_TerminateForPulledOut
CARD_TerminateForPulledOut: ; 0x020D7CA0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020D7D10 ; =0x027FFFA8
	mov r5, #0x1
	ldrh r0, [r0, #0x0]
	and r0, r0, #0x8000
	movs r0, r0, asr #0xf
	beq _020D7CEC
	bl PM_ForceToPowerOff
	cmp r0, #0x4
	bne _020D7CE4
	ldr r4, _020D7D14 ; =0x000A3A47
_020D7CD0:
	mov r0, r4
	bl OS_SpinWait
	bl PM_ForceToPowerOff
	cmp r0, #0x4
	beq _020D7CD0
_020D7CE4:
	cmp r0, #0x0
	moveq r5, #0x0
_020D7CEC:
	cmp r5, #0x0
	beq _020D7D00
	mov r0, #0x1
	mov r1, r0
	bl CARDi_SendtoPxi
_020D7D00:
	bl OS_Terminate
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D7D10: .word 0x027FFFA8
_020D7D14: .word 0x000A3A47

	arm_func_start CARD_IsPulledOut
CARD_IsPulledOut: ; 0x020D7D18
	ldr r0, _020D7D24 ; =0x021D5E20
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020D7D24: .word 0x021D5E20

	arm_func_start CARDi_PulledOutCallback
CARDi_PulledOutCallback: ; 0x020D7D28
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	and r0, r1, #0x3f
	cmp r0, #0x11
	bne _020D7D90
	ldr r2, _020D7DA0 ; =0x021D5E20
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r1, _020D7DA4 ; =0x021D5E24
	mov r0, #0x1
	ldr r1, [r1, #0x0]
	str r0, [r2, #0x0]
	cmp r1, #0x0
	beq _020D7D70
	blx r1
_020D7D70:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	bl CARD_TerminateForPulledOut
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020D7D90:
	bl OS_Terminate
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D7DA0: .word 0x021D5E20
_020D7DA4: .word 0x021D5E24

	arm_func_start CARD_InitPulledOutCallback
CARD_InitPulledOutCallback: ; 0x020D7DA8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl PXI_Init
	ldr r1, _020D7DD8 ; =CARDi_PulledOutCallback
	mov r0, #0xe
	bl PXI_SetFifoRecvCallback
	ldr r0, _020D7DDC ; =0x021D5E24
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D7DD8: .word CARDi_PulledOutCallback
_020D7DDC: .word 0x021D5E24
