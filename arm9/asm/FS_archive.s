	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

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

	arm_func_start FS_LoadArchive
FS_LoadArchive: ; 0x020D0F78
	str r1, [r0, #0x28]
	str r3, [r0, #0x30]
	str r2, [r0, #0x3c]
	ldr r1, [r0, #0x3c]
	ldr r2, [sp, #0x4]
	str r1, [r0, #0x2c]
	str r2, [r0, #0x38]
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x8]
	str r1, [r0, #0x40]
	ldr r1, [r0, #0x40]
	cmp r2, #0x0
	str r1, [r0, #0x34]
	ldreq r2, _020D0FE8 ; =FSi_ReadMemCallback
	ldr r1, [sp, #0xc]
	str r2, [r0, #0x48]
	cmp r1, #0x0
	ldreq r1, _020D0FEC ; =FSi_WriteMemCallback
	str r1, [r0, #0x4c]
	ldr r2, [r0, #0x48]
	mov r1, #0x0
	str r2, [r0, #0x50]
	str r1, [r0, #0x44]
	ldr r1, [r0, #0x1c]
	orr r1, r1, #0x2
	str r1, [r0, #0x1c]
	mov r0, #0x1
	bx lr
	.balign 4
_020D0FE8: .word FSi_ReadMemCallback
_020D0FEC: .word FSi_WriteMemCallback

	arm_func_start FUN_020D0FF0
FUN_020D0FF0: ; 0x020D0FF0
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl OS_DisableInterrupts
	ldr r2, [r4, #0x4]
	mov r3, #0x0
	cmp r2, #0x0
	ldrne r1, [r4, #0x8]
	strne r1, [r2, #0x8]
	ldr r2, [r4, #0x8]
	cmp r2, #0x0
	ldrne r1, [r4, #0x4]
	strne r1, [r2, #0x4]
	str r3, [r4, #0x0]
	str r3, [r4, #0x8]
	ldr r1, [r4, #0x8]
	ldr r2, _020D1080 ; =0x021D53EC
	str r1, [r4, #0x4]
	ldr r1, [r4, #0x1c]
	bic r1, r1, #0x1
	str r1, [r4, #0x1c]
	ldr r1, [r2, #0x0]
	cmp r1, r4
	bne _020D1074
	ldr r1, _020D1084 ; =0x021D53E8
	str r3, [r2, #0x8]
	ldr r1, [r1, #0x0]
	strh r3, [r2, #0x6]
	str r1, [r2, #0x0]
	strh r3, [r2, #0x4]
_020D1074:
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D1080: .word 0x021D53EC
_020D1084: .word 0x021D53E8

	arm_func_start FS_RegisterArchiveName
FS_RegisterArchiveName: ; 0x020D1088
	stmdb sp!, {r4-r8,lr}
	mov r6, r1
	mov r5, r2
	mov r7, r0
	mov r8, #0x0
	bl OS_DisableInterrupts
	mov r4, r0
	mov r0, r6
	mov r1, r5
	bl FS_FindArchive
_020D10B0:
	cmp r0, #0x0
	bne _020D112C
	ldr r1, _020D1140
	ldr r2, [r1]
	cmp r2, #0x0
	bne _020D10E8
	ldr r0, _020D1144
	mov r2, r8
	str r7, [r1]
	str r7, [r0]
	str r2, [r0, #0x8]
	strh r2, [r0, #0x6]
	strh r2, [r0, #0x4]
	b _020D110C
_020D10E8:
	ldr r0, [r2, #0x4]
	cmp r0, #0x0
	beq _020D1104
_020D10F4:
	mov r2, r0
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	bne _020D10F4
_020D1104:
	str r7, [r2, #0x4]
	str r2, [r7, #0x8]
_020D110C:
	mov r0, r6
	mov r1, r5
	bl FSi_GetPackedName
	str r0, [r7]
	ldr r0, [r7, #0x1C]
	mov r8, #0x1
	orr r0, r0, #0x1
	str r0, [r7, #0x1C]
_020D112C:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020D1140: .word 0x021D53E8
_020D1144: .word 0x021D53EC

	arm_func_start FS_FindArchive
FS_FindArchive:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl FSi_GetPackedName
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020D1194 ; =0x021D53E8
	ldr r4, [r1, #0x0]
	b _020D116C
_020D1168:
	ldr r4, [r4, #0x4]
_020D116C:
	cmp r4, #0x0
	beq _020D1180
	ldr r1, [r4, #0x0]
	cmp r1, r5
	bne _020D1168
_020D1180:
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D1194: .word 0x021D53E8

	arm_func_start FS_InitArchive
FS_InitArchive: ; 0x020D1198
	stmdb sp!, {r4,lr}
	mov r1, #0x0
	mov r2, #0x5c
	mov r4, r0
	bl MI_CpuFill8
	mov r1, #0x0
	str r1, [r4, #0x10]
	ldr r0, [r4, #0x10]
	str r0, [r4, #0xc]
	str r1, [r4, #0x18]
	ldr r0, [r4, #0x18]
	str r0, [r4, #0x14]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FSi_SendCommand
FSi_SendCommand:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldr r6, [r7, #0x8]
	mov r2, #0x1
	str r1, [r7, #0x10]
	mov r0, #0x2
	str r0, [r7, #0x14]
	ldr r0, [r7, #0xc]
	mov r5, r2, lsl r1
	orr r0, r0, #0x1
	str r0, [r7, #0xc]
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x1c]
	mov r4, r0
	ands r0, r1, #0x80
	beq _020D1238
	mov r0, r7
	mov r1, #0x3
	bl FSi_ReleaseCommand
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D1238:
	ands r0, r5, #0x1fc
	ldrne r0, [r7, #0xc]
	add r2, r6, #0x20
	orrne r0, r0, #0x4
	strne r0, [r7, #0xc]
	ldr r1, [r7, #0x0]
	ldr r0, [r7, #0x4]
	cmp r1, #0x0
	strne r0, [r1, #0x4]
	cmp r0, #0x0
	strne r1, [r0, #0x0]
	ldr r0, [r2, #0x4]
	cmp r0, #0x0
	beq _020D1280
_020D1270:
	mov r2, r0
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	bne _020D1270
_020D1280:
	str r7, [r2, #0x4]
	str r2, [r7, #0x0]
	mov r1, #0x0
	str r1, [r7, #0x4]
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x8
	movne r1, #0x1
	cmp r1, #0x0
	bne _020D132C
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x10
	bne _020D132C
	ldr r1, [r6, #0x1c]
	mov r0, r4
	orr r1, r1, #0x10
	str r1, [r6, #0x1c]
	bl OS_RestoreInterrupts
	ldr r0, [r6, #0x58]
	ands r0, r0, #0x200
	beq _020D12E0
	ldr r2, [r6, #0x54]
	mov r0, r7
	mov r1, #0x9
	blx r2
_020D12E0:
	bl OS_DisableInterrupts
	ldr r1, [r7, #0xc]
	orr r1, r1, #0x40
	str r1, [r7, #0xc]
	ldr r1, [r7, #0xc]
	ands r1, r1, #0x4
	movne r1, #0x1
	moveq r1, #0x0
	cmp r1, #0x0
	bne _020D1324
	bl OS_RestoreInterrupts
	mov r0, r7
	bl FSi_ExecuteAsyncCommand
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D1324:
	bl OS_RestoreInterrupts
	b _020D1378
_020D132C:
	ldr r0, [r7, #0xc]
	ands r0, r0, #0x4
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	bne _020D135C
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D135C:
	add r0, r7, #0x18
	bl OS_SleepThread
	ldr r0, [r7, #0xc]
	ands r0, r0, #0x40
	beq _020D135C
	mov r0, r4
	bl OS_RestoreInterrupts
_020D1378:
	mov r0, r7
	bl FSi_ExecuteSyncCommand
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FSi_ExecuteSyncCommand
FSi_ExecuteSyncCommand: ; 0x020D138C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r1, [r4, #0x10]
	bl FSi_TranslateCommand
	mov r1, r0
	mov r0, r4
	bl FSi_ReleaseCommand
	ldr r0, [r4, #0x8]
	bl FSi_NextCommand
_020D13B0:
	cmp r0, #0x0
	beq _020D13BC
	bl FSi_ExecuteAsyncCommand
_020D13BC:
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FSi_ExecuteAsyncCommand
FSi_ExecuteAsyncCommand: ; 0x020D13D4
	stmdb sp!, {r4-r8,lr}
	movs r6, r0
	ldr r5, [r6, #0x8]
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r7, #0x0
	mov r8, #0x1
_020D13F0:
	bl OS_DisableInterrupts
	ldr r1, [r6, #0xc]
	mov r4, r0
	orr r0, r1, #0x40
	str r0, [r6, #0xc]
	ldr r0, [r6, #0xc]
	ands r0, r0, #0x4
	movne r0, r8
	moveq r0, r7
	cmp r0, #0x0
	beq _020D1434
	add r0, r6, #0x18
	bl OS_WakeupThread
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
_020D1434:
	ldr r1, [r6, #0xc]
	mov r0, r4
	orr r1, r1, #0x8
	str r1, [r6, #0xc]
	bl OS_RestoreInterrupts
	ldr r1, [r6, #0x10]
	mov r0, r6
	bl FSi_TranslateCommand
	cmp r0, #0x6
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r0, r5
	bl FSi_NextCommand
	movs r6, r0
	bne _020D13F0
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FSi_NextCommand
FSi_NextCommand:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4c
	mov r6, r0
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x1c]
	mov r5, r0
	ands r0, r1, #0x20
	beq _020D1500
	ldr r0, [r6, #0x1c]
	bic r0, r0, #0x20
	str r0, [r6, #0x1c]
	ldr r0, [r6, #0x24]
	cmp r0, #0x0
	beq _020D1500
	mov r8, #0x0
	mov r9, #0x1
	mov r7, #0x3
_020D14BC:
	ldr r1, [r0, #0xc]
	ldr r4, [r0, #0x4]
	ands r1, r1, #0x2
	movne r1, r9
	moveq r1, r8
	cmp r1, #0x0
	beq _020D14F4
	ldr r1, [r6, #0x24]
	cmp r1, r0
	mov r1, r7
	streq r4, [r6, #0x24]
	bl FSi_ReleaseCommand
_020D14EC:
	cmp r4, #0x0
	ldreq r4, [r6, #0x24]
_020D14F4:
	mov r0, r4
	cmp r4, #0x0
	bne _020D14BC
_020D1500:
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x40
	bne _020D15EC
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x8
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	bne _020D15EC
	ldr r4, [r6, #0x24]
	cmp r4, #0x0
	beq _020D15EC
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x10
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	moveq r7, #0x1
	movne r7, #0x0
	cmp r7, #0x0
	ldrne r0, [r6, #0x1c]
	orrne r0, r0, #0x10
	strne r0, [r6, #0x1c]
	mov r0, r5
	bl OS_RestoreInterrupts
_020D1564:
	cmp r7, #0x0
	beq _020D1588
	ldr r0, [r6, #0x58]
	ands r0, r0, #0x200
	beq _020D1588
	ldr r2, [r6, #0x54]
	mov r0, r4
	mov r1, #0x9
	blx r2
_020D1588:
	bl OS_DisableInterrupts
	ldr r1, [r4, #0xC]
	mov r5, r0
	orr r0, r1, #0x40
	str r0, [r4, #0xC]
	ldr r0, [r4, #0xC]
	ands r0, r0, #0x4
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020D15D4
	add r0, r4, #0x18
	bl OS_WakeupThread
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4c
	mov r0, #0x0
	ldmia sp!, {r4-r9, lr}
	bx lr
_020D15D4:
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4c
	mov r0, r4
	ldmia sp!, {r4-r9, lr}
	bx lr
_020D15EC:
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x10
	beq _020D162C
	ldr r0, [r6, #0x1c]
	bic r0, r0, #0x10
	str r0, [r6, #0x1c]
	ldr r0, [r6, #0x58]
	ands r0, r0, #0x400
	beq _020D162C
	add r0, sp, #0x0
	bl FS_InitFile
	str r6, [sp, #0x8]
	ldr r2, [r6, #0x54]
	add r0, sp, #0x0
	mov r1, #0xa
	blx r2
_020D162C:
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x40
	beq _020D1658
	ldr r1, [r6, #0x1c]
	add r0, r6, #0x14
	bic r1, r1, #0x40
	str r1, [r6, #0x1c]
	ldr r1, [r6, #0x1c]
	orr r1, r1, #0x8
	str r1, [r6, #0x1c]
	bl OS_WakeupThread
_020D1658:
	mov r0, r5
	bl OS_RestoreInterrupts
_020D1660:
	mov r0, #0x0
	add sp, sp, #0x4c
	ldmia sp!, {r4-r9, lr}
	bx lr

	arm_func_start FSi_ReadMemoryCore
FSi_ReadMemoryCore: ; 0x020D1670
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, r2
	mov r2, r3
	bl MI_CpuCopy8
_020D1684:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmfd sp!, {lr}
	bx lr

	arm_func_start FSi_WriteMemCallback
FSi_WriteMemCallback: ; 0x020D1694
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r12, [r0, #0x28]
	mov r0, r1
	add r1, r12, r2
	mov r2, r3
	bl MI_CpuCopy8
_020D16B0:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmfd sp!, {lr}
	bx lr

	arm_func_start FSi_ReadMemCallback
FSi_ReadMemCallback: ; 0x020D16C0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x28]
	add r0, r0, r2
	mov r2, r3
	bl MI_CpuCopy8
_020D16D8:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmfd sp!, {lr}
	bx lr

	arm_func_start FSi_GetPackedName
FSi_GetPackedName: ; 0x020D16E8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r1, #0x3
	mov lr, #0x0
	bgt _020D173C
	mov r12, lr
	cmp r1, #0x0
	ble _020D173C
	mov r3, lr
_020D170C:
	ldrb r2, [r0, r12]
	cmp r2, #0x0
	beq _020D173C
	sub r2, r2, #0x41
	cmp r2, #0x19
	addls r2, r2, #0x61
	addhi r2, r2, #0x41
	add r12, r12, #0x1
	orr lr, lr, r2, lsl r3
	cmp r12, r1
	add r3, r3, #0x8
	blt _020D170C
_020D173C:
	mov r0, lr
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
