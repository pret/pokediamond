	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

	.extern FSi_GetPackedName
	.extern FSi_ReadMemCallback
	.extern FSi_WriteMemCallback
	.extern FSi_ReadMemoryCore
	.extern FSi_NextCommand
	.extern FSi_ExecuteAsyncCommand
	.extern FSi_ExecuteSyncCommand
	.extern FSi_SendCommand
	.extern FS_InitArchive
	.extern FS_FindArchive
	.extern FS_RegisterArchiveName
	.extern FS_ReleaseArchiveName
	.extern FS_LoadArchive

	arm_func_start FS_NotifyArchiveAsyncEnd
FS_NotifyArchiveAsyncEnd: ; 0x020D0B40
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	ldr r0, [r4, #0x1c]
	mov r6, r1
	ands r0, r0, #0x100
	beq _020D0B8C
	ldr r2, [r4, #0x1c]
	ldr r0, [r4, #0x24]
	bic r2, r2, #0x100
	str r2, [r4, #0x1c]
	bl FSi_ReleaseCommand
	mov r0, r4
	bl FSi_NextCommand
_020D0B74:
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	bl FSi_ExecuteAsyncCommand
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D0B8C:
	ldr r5, [r4, #0x24]
	bl OS_DisableInterrupts
	str r6, [r5, #0x14]
	ldr r1, [r4, #0x1c]
	mov r5, r0
	bic r1, r1, #0x200
	add r0, r4, #0xc
	str r1, [r4, #0x1c]
	bl OS_WakeupThread
	mov r0, r5
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FS_SetArchiveProc
FS_SetArchiveProc: ; 0x020D0BC0
	cmp r2, #0x0
	moveq r1, #0x0
	beq _020D0BD4
	cmp r1, #0x0
	moveq r2, #0x0
_020D0BD4:
	str r1, [r0, #0x54]
	str r2, [r0, #0x58]
	bx lr

	arm_func_start FS_ResumeArchive
FS_ResumeArchive:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r0
	mov r6, #0x0
	bl OS_DisableInterrupts
	ldr r1, [r4, #0x1c]
	mov r5, r0
	ands r0, r1, #0x8
	movne r0, #0x1
	moveq r0, r6
	cmp r0, #0x0
	moveq r7, #0x1
	movne r7, #0x0
	cmp r7, #0x0
	bne _020D0C34
	ldr r1, [r4, #0x1c]
	mov r0, r4
	bic r1, r1, #0x8
	str r1, [r4, #0x1c]
	bl FSi_NextCommand
	mov r6, r0
_020D0C34:
	mov r0, r5
	bl OS_RestoreInterrupts
_020D0C3C:
	cmp r6, #0x0
	beq _020D0C4C
	mov r0, r6
	bl FSi_ExecuteAsyncCommand
_020D0C4C:
	mov r0, r7
	add sp, sp, #0x4
	ldmia sp!, {r4-r7, lr}
	bx lr

	arm_func_start FS_SuspendArchive
FS_SuspendArchive: ; 0x020D0C5C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x1c]
	mov r4, r0
	ands r0, r1, #0x8
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	moveq r5, #0x1
	movne r5, #0x0
	cmp r5, #0x0
	beq _020D0CD4
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x10
	beq _020D0CC8
	ldr r0, [r6, #0x1c]
	orr r0, r0, #0x40
	str r0, [r6, #0x1c]
	add r7, r6, #0x14
_020D0CB0:
	mov r0, r7
	bl OS_SleepThread
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x40
	bne _020D0CB0
	b _020D0CD4
_020D0CC8:
	ldr r0, [r6, #0x1c]
	orr r0, r0, #0x8
	str r0, [r6, #0x1c]
_020D0CD4:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FS_UnloadArchiveTables
FS_UnloadArchiveTables: ; 0x020D0CEC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, [r5, #0x1c]
	mov r4, #0x0
	ands r0, r0, #0x2
	movne r0, #0x1
	moveq r0, r4
	cmp r0, #0x0
	beq _020D0D74
	mov r0, r5
	bl FS_SuspendArchive
	ldr r1, [r5, #0x1c]
	ands r1, r1, #0x4
	movne r1, #0x1
	moveq r1, #0x0
	cmp r1, #0x0
	beq _020D0D64
	ldr r2, [r5, #0x1c]
	mov r1, #0x0
	bic r2, r2, #0x4
	str r2, [r5, #0x1c]
	ldr r4, [r5, #0x44]
	str r1, [r5, #0x44]
	ldr r1, [r5, #0x3c]
	str r1, [r5, #0x2c]
	ldr r1, [r5, #0x40]
	str r1, [r5, #0x34]
	ldr r1, [r5, #0x48]
	str r1, [r5, #0x50]
_020D0D64:
	cmp r0, #0x0
	beq _020D0D74
	mov r0, r5
	bl FS_ResumeArchive
_020D0D74:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020D0D84
FUN_020D0D84: ; 0x020D0D84
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4c
	mov r7, r0
	ldr r3, [r7, #0x30]
	ldr r0, [r7, #0x38]
	mov r6, r1
	add r0, r3, r0
	add r0, r0, #0x20
	add r0, r0, #0x1f
	bic r5, r0, #0x1f
	cmp r5, r2
	bhi _020D0E9C
	add r1, r6, #0x1f
	add r0, sp, #0x4
	bic r4, r1, #0x1f
	bl FS_InitFile
	ldr r2, [r7, #0x2c]
	mvn r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, [r7, #0x30]
	add r0, sp, #0x4
	mov r1, r7
	add r3, r2, r3
	bl FS_OpenFileDirect
_020D0DE4:
	cmp r0, #0x0
	beq _020D0E1C
	ldr r2, [r7, #0x30]
	add r0, sp, #0x4
	mov r1, r4
	bl FS_ReadFile
	cmp r0, #0x0
	bge _020D0E14
	ldr r2, [r7, #0x30]
	mov r0, r4
	mov r1, #0x0
	bl MI_CpuFill8
_020D0E14:
	add r0, sp, #0x4
	bl FS_CloseFile
_020D0E1C:
	str r4, [r7, #0x2C]
	ldr ip, [r7, #0x30]
	ldr r2, [r7, #0x34]
	mvn r0, #0x0
	str r0, [sp]
	ldr r3, [r7, #0x38]
	add r0, sp, #0x4
	mov r1, r7
	add r3, r2, r3
	add r4, r4, ip
	bl FS_OpenFileDirect
	cmp r0, #0x0
	beq _020D0E80
	ldr r2, [r7, #0x38]
	add r0, sp, #0x4
	mov r1, r4
	bl FS_ReadFile
	cmp r0, #0x0
	bge _020D0E78
	ldr r2, [r7, #0x38]
	mov r0, r4
	mov r1, #0x0
	bl MI_CpuFill8
_020D0E78:
	add r0, sp, #0x4
	bl FS_CloseFile
_020D0E80:
	str r4, [r7, #0x34]
	ldr r0, _020D0EAC
	str r6, [r7, #0x44]
	str r0, [r7, #0x50]
	ldr r0, [r7, #0x1C]
	orr r0, r0, #0x4
	str r0, [r7, #0x1C]
_020D0E9C:
	mov r0, r5
	add sp, sp, #0x4C
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D0EAC:
	.word FSi_ReadMemoryCore

	arm_func_start FUN_020D0EB0
FUN_020D0EB0: ; 0x020D0EB0
	stmdb sp!, {r4-r8,lr}
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, [r5, #0x1c]
	mov r4, r0
	ands r0, r1, #0x2
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020D0F64
	mov r0, r5
	ldr r1, [r5, #0x1c]
	bl FS_SuspendArchive
	ldr r1, [r5, #0x1c]
	mov r7, r0
	orr r0, r1, #0x80
	str r0, [r5, #0x1c]
	ldr r0, [r5, #0x24]
	cmp r0, #0x0
	beq _020D0F1C
	mov r6, #0x3
_020D0F04:
	ldr r8, [r0, #0x4]
	mov r1, r6
	bl FSi_ReleaseCommand
	mov r0, r8
	cmp r8, #0x0
	bne _020D0F04
_020D0F1C:
	mov r0, #0x0
	str r0, [r5, #0x24]
	cmp r7, #0x0
	beq _020D0F34
	mov r0, r5
	bl FS_ResumeArchive
_020D0F34:
	mov r0, #0x0
	str r0, [r5, #0x28]
	str r0, [r5, #0x2c]
	str r0, [r5, #0x30]
	str r0, [r5, #0x34]
	str r0, [r5, #0x38]
	str r0, [r5, #0x40]
	ldr r0, [r5, #0x40]
	str r0, [r5, #0x3c]
	ldr r0, [r5, #0x1c]
	bic r0, r0, #0xa2
	str r0, [r5, #0x1c]
_020D0F64:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r8,lr}
	bx lr
