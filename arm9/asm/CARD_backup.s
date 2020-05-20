	.include "asm/macros.inc"
	.include "global.inc"

    .text

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

	.extern _SDK_NintendoBackup

	arm_func_start CARD_IdentifyBackup
CARD_IdentifyBackup: ; 0x020D6DC4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, _020D6F00 ; =_SDK_NintendoBackup
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
	bl CARDi_IdentifyBackupCore
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
_020D6F00: .word _SDK_NintendoBackup
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
	ldr r0, _020D7008 ; =_SDK_NintendoBackup
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
_020D7008: .word _SDK_NintendoBackup
_020D700C: .word CARDi_RequestStreamCommandCore
_020D7010: .word 0x021D3498

	arm_func_start CARDi_RequestStreamCommandCore
CARDi_RequestStreamCommandCore:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r9, r0
	ldr r8, [r9, #0x2c]
	ldr r0, _020D720C ; =_SDK_NintendoBackup
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
_020D720C: .word _SDK_NintendoBackup
