	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

	arm_func_start FS_TryLoadTable
FS_TryLoadTable: ; 0x020D1D10
	ldr ip, _020D1D28 ; =FUN_020D0D84
	mov r3, r0
	mov r2, r1
	ldr r0, _020D1D2C ; =0x021D5414
	mov r1, r3
	bx r12
	.balign 4
_020D1D28: .word FUN_020D0D84
_020D1D2C: .word 0x021D5414

	arm_func_start FS_SetDefaultDMA
FS_SetDefaultDMA: ; 0x020D1D30
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	bl OS_DisableInterrupts
	mov r5, r0
	ldr r1, _020D1D7C ; =0x021D5400
	ldr r0, _020D1D80 ; =0x021D5414
	ldr r4, [r1, #0x0]
	bl FS_SuspendArchive
	ldr r1, _020D1D7C ; =0x021D5400
	cmp r0, #0x0
	str r6, [r1, #0x0]
	beq _020D1D68
	ldr r0, _020D1D80 ; =0x021D5414
	bl FS_ResumeArchive
_020D1D68:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D1D7C: .word 0x021D5400
_020D1D80: .word 0x021D5414

	arm_func_start FSi_InitRom
FSi_InitRom: ; 0x020D1D84
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x14
	ldr r1, _020D1EE8 ; =0x021D5400
	str r0, [r1, #0x0]
	bl OS_GetLockID
	ldr r3, _020D1EEC ; =0x021D53FC
	ldr r2, _020D1EF0 ; =0x021D5404
	mov r12, #0x0
	ldr r1, _020D1EF4 ; =0x021D540C
	str r0, [r3, #0x0]
	str r12, [r2, #0x0]
	str r12, [r2, #0x4]
	str r12, [r1, #0x0]
	str r12, [r1, #0x4]
	bl CARD_Init
	ldr r0, _020D1EF8 ; =0x021D5414
	bl FS_InitArchive
	ldr r0, _020D1EF8 ; =0x021D5414
	ldr r1, _020D1EFC ; =0x02106830
	mov r2, #0x3
	bl FS_RegisterArchiveName
	ldr r0, _020D1F00 ; =0x027FFC40
	ldrh r0, [r0, #0x0]
	cmp r0, #0x2
	bne _020D1E4C
	ldr ip, _020D1EF0 ; =0x021D5404
	mvn r2, #0x0
	ldr r3, _020D1EF4 ; =0x021D540C
	mov lr, #0x0
	ldr r0, _020D1EF8 ; =0x021D5414
	ldr r1, _020D1F04 ; =FSi_EmptyArchiveProc
	str r2, [r12, #0x0]
	str lr, [r12, #0x4]
	str r2, [r3, #0x0]
	str lr, [r3, #0x4]
	bl FS_SetArchiveProc
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, _020D1F08 ; =FSi_ReadDummyCallback
	str r1, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr ip, _020D1F0C ; =FSi_WriteDummyCallback
	ldr r0, _020D1EF8 ; =0x021D5414
	mov r2, r1
	mov r3, r1
	str r12, [sp, #0xc]
	bl FS_LoadArchive
	add sp, sp, #0x14
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D1E4C:
	ldr r5, _020D1F10 ; =0x027FFE40
	ldr r0, _020D1EF8 ; =0x021D5414
	ldr r1, _020D1F14 ; =FSi_RomArchiveProc
	ldr r2, _020D1F18 ; =0x00000602
	ldr r4, _020D1F1C ; =0x027FFE48
	bl FS_SetArchiveProc
	ldr r1, [r5, #0x0]
	mvn r0, #0x0
	cmp r1, r0
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	cmp r1, #0x0
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r2, [r4, #0x0]
	cmp r2, r0
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	cmp r2, #0x0
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	str r1, [sp, #0x0]
	ldr r0, [r5, #0x4]
	ldr r1, _020D1F20 ; =FSi_ReadRomCallback
	str r0, [sp, #0x4]
	ldr r0, _020D1F0C ; =FSi_WriteDummyCallback
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r3, [r4, #0x4]
	ldr r0, _020D1EF8 ; =0x021D5414
	mov r1, #0x0
	bl FS_LoadArchive
	add sp, sp, #0x14
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D1EE8: .word 0x021D5400
_020D1EEC: .word 0x021D53FC
_020D1EF0: .word 0x021D5404
_020D1EF4: .word 0x021D540C
_020D1EF8: .word 0x021D5414
_020D1EFC: .word 0x02106830
_020D1F00: .word 0x027FFC40
_020D1F04: .word FSi_EmptyArchiveProc
_020D1F08: .word FSi_ReadDummyCallback
_020D1F0C: .word FSi_WriteDummyCallback
_020D1F10: .word 0x027FFE40
_020D1F14: .word FSi_RomArchiveProc
_020D1F18: .word 0x00000602
_020D1F1C: .word 0x027FFE48
_020D1F20: .word FSi_ReadRomCallback

	arm_func_start FSi_EmptyArchiveProc
FSi_EmptyArchiveProc: ; 0x020D1F24
	mov r0, #0x4
	bx lr

	arm_func_start FSi_ReadDummyCallback
FSi_ReadDummyCallback: ; 0x020D1F2C
	mov r0, #0x1
	bx lr

	arm_func_start FSi_RomArchiveProc
FSi_RomArchiveProc: ; 0x020D1F34
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r1, #0x1
	beq _020D1FA0
	cmp r1, #0x9
	beq _020D1F58
	cmp r1, #0xa
	beq _020D1F7C
	b _020D1FB0
_020D1F58:
	ldr r0, _020D1FC0 ; =0x021D53FC
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl CARD_LockRom
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {lr}
	bx lr
_020D1F7C:
	ldr r0, _020D1FC0 ; =0x021D53FC
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl CARD_UnlockRom
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {lr}
	bx lr
_020D1FA0:
	add sp, sp, #0x4
	mov r0, #0x4
	ldmia sp!, {lr}
	bx lr
_020D1FB0:
	mov r0, #0x8
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D1FC0: .word 0x021D53FC

	arm_func_start FSi_WriteDummyCallback
FSi_WriteDummyCallback: ; 0x020D1FC4
	mov r0, #0x1
	bx lr

	arm_func_start FSi_ReadRomCallback
FSi_ReadRomCallback: ; 0x020D1FCC
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr ip, _020D2010 ; =FSi_OnRomReadDone
	mov lr, r1
	str r12, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r1, #0x1
	ldr r0, _020D2014 ; =0x021D5400
	str r1, [sp, #0x8]
	mov r1, r2
	ldr r0, [r0, #0x0]
	mov r2, lr
	bl CARDi_ReadRom
	mov r0, #0x6
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D2010: .word FSi_OnRomReadDone
_020D2014: .word 0x021D5400

	arm_func_start FSi_OnRomReadDone
FSi_OnRomReadDone: ; 0x020D2018
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl CARD_IsPulledOut
_020D2024:
	cmp r0, #0x0
	movne r1, #0x5
	moveq r1, #0x0
	mov r0, r4
	bl FS_NotifyArchiveAsyncEnd
	ldmia sp!, {r4,lr}
	bx lr
