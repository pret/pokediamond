	.include "asm/macros.inc"
	.include "global.inc"

	.extern cardi_common
	.extern UNK_021D5560
	.extern UNK_021D555C
	.extern UNK_021D5BE0

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
	ldr r0, _020D6710 ; =cardi_common
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020D6710: .word cardi_common

;CARDi_TryWaitAsync?
	arm_func_start FUN_020D6714
FUN_020D6714: ; 0x020D6714
	ldr r0, _020D672C ; =cardi_common
	ldr r0, [r0, #0x114]
	ands r0, r0, #0x4
	moveq r0, #0x1
	movne r0, #0x0
	bx lr
	.balign 4
_020D672C: .word cardi_common

	arm_func_start CARDi_WaitAsync
CARDi_WaitAsync: ; 0x020D6730
	stmdb sp!, {r4-r6,lr}
	ldr r6, _020D6788 ; =cardi_common
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
_020D6788: .word cardi_common

	arm_func_start CARD_Enable
CARD_Enable: ; 0x020D678C
	ldr r1, _020D6798 ; =UNK_021D555C
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020D6798: .word UNK_021D555C

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
	ldr r0, _020D67D4 ; =UNK_021D555C
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020D67D4: .word UNK_021D555C

	arm_func_start CARDi_InitCommon
CARDi_InitCommon: ; 0x020D67D8
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldr r4, _020D68B8 ; =cardi_common
	ldr r1, _020D68BC ; =UNK_021D5560
	mvn r2, #0x2
	mov r0, #0x0
	str r2, [r4, #0x8]
	mov r2, #0x60
	str r0, [r4, #0xc]
	str r0, [r4, #0x18]
	str r1, [r4, #0x0]
	bl MIi_CpuClearFast
	ldr r0, _020D68BC ; =UNK_021D5560
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
	ldr r3, _020D68D0 ; =UNK_021D5BE0
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
_020D68B8: .word cardi_common
_020D68BC: .word UNK_021D5560
_020D68C0: .word 0x027FFC40
_020D68C4: .word 0x027FFE00
_020D68C8: .word 0x027FFA80
_020D68CC: .word CARDi_TaskThread
_020D68D0: .word UNK_021D5BE0
_020D68D4: .word CARDi_OnFifoRecv

	arm_func_start CARDi_UnlockResource
CARDi_UnlockResource: ; 0x020D68D8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r5, _020D6978 ; =cardi_common
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
_020D6978: .word cardi_common

	arm_func_start CARDi_LockResource
CARDi_LockResource: ; 0x020D697C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r5, _020D6A14 ; =cardi_common
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
_020D6A14: .word cardi_common

	arm_func_start CARDi_SetTask
CARDi_SetTask: ; 0x020D6A18
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r4, _020D6A5C ; =cardi_common
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
_020D6A5C: .word cardi_common
