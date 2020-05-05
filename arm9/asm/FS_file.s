	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

	arm_func_start FS_ChangeDir
FS_ChangeDir: ; 0x020D174C
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x58
	mov r4, r0
	add r0, sp, #0xc
	bl FS_InitFile
	add r0, sp, #0xc
	add r3, sp, #0x0
	mov r1, r4
	mov r2, #0x0
	bl FSi_FindPath
_020D1774:
	cmp r0, #0x0
	moveq r0, #0x0
	addne r0, sp, #0x0
	ldrne r3, _020D179C
	ldmneia r0, {r0, r1, r2}
	stmneia r3, {r0, r1, r2}
	movne r0, #0x1
	add sp, sp, #0x58
	ldmia sp!, {r4, lr}
	bx lr
_020D179C: .word 0x021D53EC

	arm_func_start FS_SeekFile
FS_SeekFile: ; 0x020D17A0
	cmp r2, #0x0
	beq _020D17BC
	cmp r2, #0x1
	beq _020D17C8
	cmp r2, #0x2
	beq _020D17D4
	b _020D17E0
_020D17BC:
	ldr r2, [r0, #0x24]
	add r1, r1, r2
	b _020D17E8
_020D17C8:
	ldr r2, [r0, #0x2c]
	add r1, r1, r2
	b _020D17E8
_020D17D4:
	ldr r2, [r0, #0x28]
	add r1, r1, r2
	b _020D17E8
_020D17E0:
	mov r0, #0x0
	bx lr
_020D17E8:
	ldr r2, [r0, #0x24]
	cmp r1, r2
	movlt r1, r2
	ldr r2, [r0, #0x28]
	cmp r1, r2
	movgt r1, r2
	str r1, [r0, #0x2c]
	mov r0, #0x1
	bx lr

	arm_func_start FS_ReadFile
FS_ReadFile: ; 0x020D180C
	ldr ip, _020D1818 ; =FUN_020D1AAC
	mov r3, #0x0
	bx r12
	.balign 4
_020D1818: .word FUN_020D1AAC

	arm_func_start FS_ReadFileAsync
FS_ReadFileAsync: ; 0x020D181C
	ldr ip, _020D1828 ; =FUN_020D1AAC
	mov r3, #0x1
	bx r12
	.balign 4
_020D1828: .word FUN_020D1AAC

	arm_func_start FS_WaitAsync
FS_WaitAsync: ; 0x020D182C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r5, #0x0
	bl OS_DisableInterrupts
	ldr r1, [r6, #0xc]
	mov r4, r0
	ands r0, r1, #0x1
	movne r0, #0x1
	moveq r0, r5
	cmp r0, #0x0
	beq _020D18BC
	ldr r0, [r6, #0xc]
	ands r0, r0, #0x44
	moveq r5, #0x1
	movne r5, #0x0
	cmp r5, #0x0
	beq _020D189C
	ldr r0, [r6, #0xc]
	orr r0, r0, #0x4
	str r0, [r6, #0xc]
	add r7, r6, #0x18
_020D1884:
	mov r0, r7
	bl OS_SleepThread
	ldr r0, [r6, #0xc]
	ands r0, r0, #0x40
	beq _020D1884
	b _020D18BC
_020D189C:
	add r0, r6, #0x18
	bl OS_SleepThread
	ldr r0, [r6, #0xc]
	ands r0, r0, #0x1
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	bne _020D189C
_020D18BC:
	mov r0, r4
	bl OS_RestoreInterrupts
_020D18C4:
	cmp r5, #0x0
	beq _020D18E0
	mov r0, r6
	bl FSi_ExecuteSyncCommand
	add sp, sp, #4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D18E0:
	ldr r0, [r6, #0x14]
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FS_CloseFile
FS_CloseFile: ; 0x020D18FC
	stmdb sp!, {r4,lr}
	mov r1, #0x8
	mov r4, r0
	bl FSi_SendCommand
_020D190C:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, #0x0
	str r0, [r4, #0x8]
	mov r0, #0xE
	str r0, [r4, #0x10]
	ldr r1, [r4, #0xC]
	mov r0, #0x1
	bic r1, r1, #0x30
	str r1, [r4, #0xC]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FS_OpenFile
FS_OpenFile: ; 0x020D1944
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	mov r4, r0
	add r0, sp, #0x0
	bl FS_ConvertPathToFileID
_020D1958:
	cmp r0, #0x0
	beq _020D1984
	add r1, sp, #0x0
	mov r0, r4
	ldmia r1, {r1, r2}
	bl FS_OpenFileFast
	cmp r0, #0x0
	addne sp, sp, #0x8
	movne r0, #0x1
	ldmneia sp!, {r4, lr}
	bxne lr
_020D1984:
	mov r0, #0x0
	add sp, sp, #0x8
	ldmia sp!, {r4, lr}
	bx lr

	arm_func_start FS_OpenFileFast
FS_OpenFileFast:
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4,lr}
	ldr r1, [sp, #0xc]
	mov r4, r0
	cmp r1, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	addeq sp, sp, #0x10
	bxeq lr
	str r1, [r4, #0x8]
	ldr r3, [sp, #0xc]
	ldr r2, [sp, #0x10]
	mov r1, #0x6
	str r3, [r4, #0x30]
	str r2, [r4, #0x34]
	bl FSi_SendCommand
_020D19D4:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4, lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r1, [r4, #0xC]
	mov r0, #0x1
	orr r1, r1, #0x10
	str r1, [r4, #0xC]
	ldr r1, [r4, #0xC]
	bic r1, r1, #0x20
	str r1, [r4, #0xC]
	ldmia sp!, {r4, lr}
	add sp, sp, #0x10
	bx lr

	arm_func_start FS_OpenFileDirect
FS_OpenFileDirect:
	stmdb sp!, {r4,lr}
	mov r4, r0
	str r1, [r4, #0x8]
	ldr r12, [sp, #0x8]
	mov r1, #0x7
	str r12, [r4, #0x38]
	str r2, [r4, #0x30]
	str r3, [r4, #0x34]
	bl FSi_SendCommand
_020D1A34:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4, lr}
	bxeq lr
	ldr r1, [r4, #0xC]
	mov r0, #0x1
	orr r1, r1, #0x10
	str r1, [r4, #0xC]
	ldr r1, [r4, #0xC]
	bic r1, r1, #0x20
	str r1, [r4, #0xC]
	ldmia sp!, {r4, lr}
	bx lr

	arm_func_start FS_ConvertPathToFileID
FS_ConvertPathToFileID:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4c
	mov r5, r0
	add r0, sp, #0x0
	mov r4, r1
	bl FS_InitFile
_020D1A80:
	add r0, sp, #0x0
	mov r1, r4
	mov r2, r5
	mov r3, #0x0
	bl FSi_FindPath
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4C
	ldmia sp!, {r4-r5, lr}
	bx lr

	arm_func_start FUN_020D1AAC
FUN_020D1AAC: ; 0x020D1AAC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldr r4, [r7, #0x2c]
	ldr r0, [r7, #0x28]
	mov r6, r2
	str r1, [r7, #0x30]
	sub r0, r0, r4
	cmp r6, r0
	movgt r6, r0
	cmp r6, #0x0
	movlt r6, #0x0
	str r2, [r7, #0x34]
	mov r5, r3
	str r6, [r7, #0x38]
	cmp r5, #0x0
	ldreq r0, [r7, #0xc]
	mov r1, #0x0
	orreq r0, r0, #0x4
	streq r0, [r7, #0xc]
	mov r0, r7
	bl FSi_SendCommand
_020D1B04:
	cmp r5, #0x0
	bne _020D1B24
	mov r0, r7
	bl FS_WaitAsync
	cmp r0, #0x0
	ldrne r0, [r7, #0x2C]
	subne r6, r0, r4
	mvneq r6, #0x0
_020D1B24:
	mov r0, r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r7, lr}
	bx lr

	arm_func_start FSi_FindPath
FSi_FindPath:
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	mov r7, r1
	ldrb r1, [r7, #0x0]
	mov r8, r0
	mov r6, r2
	mov r5, r3
	cmp r1, #0x2f
	beq _020D1B60
	cmp r1, #0x5c
	bne _020D1B84
_020D1B60:
	ldr r0, _020D1C90 ; =0x021D53EC
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	strh r1, [sp, #0x4]
	str r0, [sp, #0x0]
	str r1, [sp, #0x8]
	strh r1, [sp, #0x6]
	add r7, r7, #0x1
	b _020D1C40
_020D1B84:
	ldr r0, _020D1C90 ; =0x021D53EC
	add r3, sp, #0x0
	ldmia r0, {r0-r2}
	stmia r3, {r0-r2}
	mov r4, #0x0
_020D1B98:
	ldrb r0, [r7, r4]
	cmp r0, #0x0
	beq _020D1C40
	cmp r0, #0x2f
	beq _020D1C40
	cmp r0, #0x5c
	beq _020D1C40
	cmp r0, #0x3a
	bne _020D1C34
	mov r0, r7
	mov r1, r4
	bl FS_FindArchive
_020D1BC8:
	cmp r0, #0x0
	addeq sp, sp, #0x10
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r1, [r0, #0x1C]
	ands r1, r1, #0x2
	movne r1, #0x1
	moveq r1, #0x0
	cmp r1, #0x0
	addeq sp, sp, #0x10
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r1, #0x0
	str r0, [sp]
	str r1, [sp, #0x8]
	strh r1, [sp, #0x6]
	strh r1, [sp, #0x4]
	add r0, r4, #0x1
	ldrb r0, [r7, r0]!
	cmp r0, #0x2f
	beq _020D1C2C
	cmp r0, #0x5c
	bne _020D1C40
_020D1C2C:
	add r7, r7, #0x1
	b _020D1C40
_020D1C34:
	add r4, r4, #0x1
	cmp r4, #0x3
	ble _020D1B98
_020D1C40:
	ldr r1, [sp, #0x0]
	add r0, sp, #0x0
	str r1, [r8, #0x8]
	str r7, [r8, #0x3c]
	add r3, r8, #0x30
	ldmia r0, {r0-r2}
	stmia r3, {r0-r2}
	cmp r5, #0x0
	movne r0, #0x1
	strne r0, [r8, #0x40]
	strne r5, [r8, #0x44]
	moveq r0, #0x0
	streq r0, [r8, #0x40]
	mov r0, r8
	mov r1, #0x4
	streq r6, [r8, #0x44]
	bl FSi_SendCommand
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020D1C90: .word 0x021D53EC

	arm_func_start FS_InitFile
FS_InitFile:
	mov r3, #0x0
	str r3, [r0, #0x0]
	ldr r2, [r0, #0x0]
	mov r1, #0xe
	str r2, [r0, #0x4]
	str r3, [r0, #0x1c]
	ldr r2, [r0, #0x1c]
	str r2, [r0, #0x18]
	str r3, [r0, #0x8]
	str r1, [r0, #0x10]
	str r3, [r0, #0xc]
	bx lr

	arm_func_start FS_IsAvailable
FS_IsAvailable: ; 0x020D1CC4
	ldr r0, _020D1CD0 ; =0x021D53F8
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020D1CD0: .word 0x021D53F8

	arm_func_start FS_Init
FS_Init: ; 0x020D1CD4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020D1D0C ; =0x021D53F8
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	mov r2, #0x1
	str r2, [r1, #0x0]
	bl FSi_InitRom
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D1D0C: .word 0x021D53F8
