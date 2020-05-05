	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

	arm_func_start FSi_CloseFileCommand
FSi_CloseFileCommand: ; 0x020D0114
	mov r0, #0x0
	bx lr

	arm_func_start FSi_OpenFileDirectCommand
FSi_OpenFileDirectCommand: ; 0x020D011C
	ldr r1, [r0, #0x30]
	str r1, [r0, #0x24]
	ldr r1, [r0, #0x30]
	str r1, [r0, #0x2c]
	ldr r1, [r0, #0x34]
	str r1, [r0, #0x28]
	ldr r1, [r0, #0x38]
	str r1, [r0, #0x20]
	mov r0, #0x0
	bx lr

	arm_func_start FSi_OpenFileFastCommand
FSi_OpenFileFastCommand: ; 0x020D0144
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x14
	mov r5, r0
	ldr r1, [r5, #0x8]
	ldr r4, [r5, #0x34]
	ldr r0, [r1, #0x30]
	mov r2, r4, lsl #0x3
	cmp r2, r0
	addcs sp, sp, #0x14
	movcs r0, #0x1
	ldmcsia sp!, {r4-r5,lr}
	bxcs lr
	str r1, [sp, #0x8]
	ldr r1, [r1, #0x2c]
	add r0, sp, #0x8
	add r3, r1, r2
	add r1, sp, #0x0
	mov r2, #0x8
	str r3, [sp, #0xc]
	bl FSi_ReadTable
_020D0194:
	cmp r0, #0
	addne sp, sp, #0x14
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r1, [sp]
	mov r0, r5
	str r1, [r5, #0x30]
	ldr r2, [sp, #0x4]
	mov r1, #7
	str r2, [r5, #0x34]
	str r4, [r5, #0x38]
	bl FSi_TranslateCommand
	add sp, sp, #0x14
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FSi_GetPathCommand
FSi_GetPathCommand: ; 0x020D01D0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xe4
	mov r4, r0
	ldr r1, [r4, #0x8]
	add r0, sp, #0x98
	add r11, r4, #0x30
	str r1, [sp, #0x0]
	bl FS_InitFile
	ldr r0, [r4, #0x8]
	str r0, [sp, #0xa0]
	ldr r0, [r4, #0xc]
	ands r0, r0, #0x20
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	ldrneh r5, [r4, #0x24]
	movne r4, #0x10000
	bne _020D02BC
	ldrh r0, [r11, #0x8]
	ldr r4, [r4, #0x20]
	cmp r0, #0x0
	ldrneh r5, [r11, #0xa]
	bne _020D02BC
	mov r10, #0x0
	mov r9, r10
	mov r5, #0x10000
	add r8, sp, #0x98
	mov r6, #0x3
	mov r7, #0x1
_020D0244:
	mov r0, r8
	mov r1, r10
	bl FSi_SeekDirDirect
	add r2, sp, #0x4
	cmp r10, #0x0
	mov r0, r8
	mov r1, r6
	ldreq r9, [sp, #0xc4]
	str r2, [sp, #0xc8]
	str r7, [sp, #0xcc]
	bl FSi_TranslateCommand
_020D0270:
	cmp r0, #0x0
	bne _020D02A8
_020D0278:
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	bne _020D0294
	ldr r0, [sp, #0x8]
	cmp r0, r4
	ldreqh r5, [sp, #0xbc]
	beq _020D02A8
_020D0294:
	mov r0, r8
	mov r1, r6
	bl FSi_TranslateCommand
	cmp r0, #0x0
	beq _020D0278
_020D02A8:
	cmp r5, #0x10000
	bne _020D02BC
	add sl, sl, #0x1
	cmp sl, r9
	bcc _020D0244
_020D02BC:
	cmp r5, #0x10000
	moveq r0, #0x0
	streqh r0, [r11, #0x8]
	addeq sp, sp, #0xe4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldrh r0, [r11, #0x8]
	cmp r0, #0x0
	bne _020D03B8
	ldr r0, [sp, #0x0]
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0xff
	addls r9, r1, #0x1
	bls _020D0308
	cmp r0, #0xff00
	addls r9, r1, #0x2
	addhi r9, r1, #0x3
_020D0308:
	cmp r4, #0x10000
	ldrne r0, [sp, #0x14]
	add r9, r9, #0x2
	addne r9, r9, r0
	mov r10, r5
	cmp r5, #0x0
	beq _020D03AC
	add r0, sp, #0x98
	mov r1, r5
	bl FSi_SeekDirDirect
	add r8, sp, #0x98
	mov r6, #0x3
	mov r7, #0x1
_020D033C:
	ldr r1, [sp, #0xc4]
	mov r0, r8
	bl FSi_SeekDirDirect
	add r2, sp, #0x4
	mov r0, r8
	mov r1, r6
	str r2, [sp, #0xc8]
	str r7, [sp, #0xcc]
	bl FSi_TranslateCommand
_020D0360:
	cmp r0, #0x0
	bne _020D03A0
_020D0368:
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	beq _020D038C
	ldrh r0, [sp, #0x8]
	cmp r0, sl
	ldreq r0, [sp, #0x14]
	addeq r0, r0, #0x1
	addeq r9, r9, r0
	beq _020D03A0
_020D038C:
	mov r0, r8
	mov r1, r6
	bl FSi_TranslateCommand
	cmp r0, #0x0
	beq _020D0368
_020D03A0:
	ldrh sl, [sp, #0xbc]
	cmp sl, #0x0
	bne _020D033C
_020D03AC:
	add r0, r9, #0x1
	strh r0, [r11, #0x8]
	strh r5, [r11, #0xa]
_020D03B8:
	ldr r7, [r11, #0x0]
	cmp r7, #0x0
	addeq sp, sp, #0xe4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldrh r6, [r11, #0x8]
	ldr r0, [r11, #0x4]
	cmp r0, r6
	addcc sp, sp, #0xe4
	movcc r0, #0x1
	ldmccia sp!, {r4-r11,lr}
	bxcc lr
	ldr r0, [sp, #0x0]
	mov r9, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0xff
	movls r8, #0x1
	bls _020D0410
	cmp r0, #0xff00
	movls r8, #0x2
	movhi r8, #0x3
_020D0410:
	ldr r0, [sp, #0x0]
	mov r1, r7
	mov r2, r8
	bl MI_CpuCopy8
	add r1, r9, r8
	ldr r0, _020D058C ; =0x0210682C
	add r1, r7, r1
	mov r2, #0x2
	bl MI_CpuCopy8
	add r0, sp, #0x98
	mov r1, r5
	bl FSi_SeekDirDirect
	cmp r4, #0x10000
	beq _020D04C4
	add r3, sp, #0x4
	mov r2, #0x0
	add r0, sp, #0x98
	mov r1, #0x3
	str r3, [sp, #0xc8]
	str r2, [sp, #0xcc]
	bl FSi_TranslateCommand
_020D0464:
	cmp r0, #0x0
	bne _020D04A0
	add r9, sp, #0x98
	mov r8, #0x3
_020D0474:
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	bne _020D048C
	ldr r0, [sp, #0x8]
	cmp r0, r4
	beq _020D04A0
_020D048C:
	mov r0, r9
	mov r1, r8
	bl FSi_TranslateCommand
	cmp r0, #0x0
	beq _020D0474
_020D04A0:
	ldr r0, [sp, #0x14]
	add r1, r7, r6
	add r4, r0, #0x1
	add r0, sp, #0x18
	mov r2, r4
	sub r1, r1, r4
	bl MI_CpuCopy8
	sub r6, r6, r4
	b _020D04D4
_020D04C4:
	add r0, r7, r6
	mov r1, #0x0
	strb r1, [r0, #-0x1]
	sub r6, r6, #0x1
_020D04D4:
	cmp r5, #0x0
	beq _020D057C
	add r10, sp, #0x98
	add r11, sp, #0x4
	mov r4, #0x3
	mov r9, #0x0
	mov r8, #0x2f
_020D04F0:
	ldr r1, [sp, #0xc4]
	mov r0, r10
	bl FSi_SeekDirDirect
	add r2, r7, r6
	mov r0, r10
	mov r1, r4
	str r11, [sp, #0xc8]
	str r9, [sp, #0xcc]
	strb r8, [r2, #-0x1]
	sub r6, r6, #0x1
	bl FSi_TranslateCommand
_020D051C:
	cmp r0, #0x0
	bne _020D0570
_020D0524:
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	beq _020D055C
	ldrh r0, [sp, #0x8]
	cmp r0, r5
	bne _020D055C
	ldr r5, [sp, #0x14]
	add r1, r7, r6
	add r0, sp, #0x18
	mov r2, r5
	sub r1, r1, r5
	bl MI_CpuCopy8
	sub r6, r6, r5
	b _020D0570
_020D055C:
	mov r0, sl
	mov r1, r4
	bl FSi_TranslateCommand
	cmp r0, #0x0
	beq _020D0524
_020D0570:
	ldrh r5, [sp, #0xbc]
	cmp r5, #0x0
	bne _020D04F0
_020D057C:
	mov r0, #0x0
	add sp, sp, #0xe4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020D058C: .word 0x0210682C

	arm_func_start FSi_FindPathCommand
FSi_FindPathCommand: ; 0x020D0590
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x9c
	mov r10, r0
	ldr r2, [r10, #0x40]
	ldr r9, [r10, #0x3c]
	mov r1, #0x2
	str r2, [sp, #0x0]
	bl FSi_TranslateCommand
	ldrb r1, [r9, #0x0]
	cmp r1, #0x0
	beq _020D0780
	mov r0, #0x2
	add r11, sp, #0x1c
	mov r4, #0x3
	mov r5, #0x1
	mov r6, #0x0
	str r0, [sp, #0x4]
_020D05D4:
	mov r7, r6
	b _020D05E0
_020D05DC:
	add r7, r7, #0x1
_020D05E0:
	ldrb r8, [r9, r7]
	mov r0, r6
	cmp r8, #0x0
	beq _020D0600
	cmp r8, #0x2f
	beq _020D0600
	cmp r8, #0x5c
	movne r0, r5
_020D0600:
	cmp r0, #0x0
	bne _020D05DC
	cmp r8, #0x0
	bne _020D061C
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _020D0620
_020D061C:
	mov r8, r5
_020D0620:
	cmp r7, #0x0
	addeq sp, sp, #0x9c
	moveq r0, #0x1
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	cmp r1, #0x2e
	bne _020D068C
	cmp r7, #0x1
	addeq r9, r9, #0x1
	beq _020D0764
	ldrb r0, [r9, #0x1]
	cmp r7, #0x2
	moveq r1, r5
	movne r1, r6
	cmp r0, #0x2e
	moveq r0, r5
	movne r0, r6
	ands r0, r1, r0
	beq _020D068C
	ldrh r0, [r10, #0x24]
	cmp r0, #0x0
	beq _020D0684
	ldr r1, [r10, #0x2c]
	mov r0, r10
	bl FSi_SeekDirDirect
_020D0684:
	add r9, r9, #0x2
	b _020D0764
_020D068C:
	cmp r7, #0x7f
	addgt sp, sp, #0x9c
	movgt r0, #0x1
	ldmgtia sp!, {r4-r11,lr}
	bxgt lr
	add r0, sp, #0x8
	str r0, [r10, #0x30]
	str r6, [r10, #0x34]
_020D06AC:
	mov r0, r10
	mov r1, r4
	bl FSi_TranslateCommand
_020D06B8:
	cmp r0, #0x0
	addne sp, sp, #0x9c
	movne r0, #0x1
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	ldr r0, [sp, #0x14]
	cmp r8, r0
	bne _020D06AC
	ldr r0, [sp, #0x18]
	cmp r7, r0
	bne _020D06AC
	mov r0, r9
	mov r1, fp
	mov r2, r7
	bl FSi_StrNICmp
	cmp r0, #0x0
	bne _020D06AC
	cmp r8, #0x0
	beq _020D0728
	add r0, sp, #0x8
	add r3, sl, #0x30
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	ldr r1, [sp, #0x4]
	mov r0, sl
	add r9, r9, r7
	bl FSi_TranslateCommand
	b _020D0764
_020D0728:
	ldr r0, [sp]
	cmp r0, #0x0
	addne sp, sp, #0x9c
	movne r0, #0x1
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	ldr r3, [sl, #0x44]
	ldr r2, [sp, #0x8]
	ldr r1, [sp, #0xC]
	add sp, sp, #0x9c
	str r2, [r3]
	str r1, [r3, #0x4]
	mov r0, #0x0
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D0764:
	ldrb r0, [r9, #0x0]
	cmp r0, #0x0
	movne r0, r5
	moveq r0, r6
	ldrb r1, [r9, r0]!
	cmp r1, #0x0
	bne _020D05D4
_020D0780:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	moveq r0, #0x1
	addne r0, r10, #0x20
	ldrne r3, [r10, #0x44]
	ldmneia r0, {r0-r2}
	stmneia r3, {r0-r2}
	movne r0, #0x0
	add sp, sp, #0x9c
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FSi_ReadDirCommand
FSi_ReadDirCommand: ; 0x020D07AC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r5, r0
	ldr r4, [r5, #0x30]
	ldr r1, [r5, #0x8]
	add r0, sp, #0x4
	str r1, [sp, #0x4]
	ldr r3, [r5, #0x28]
	add r1, sp, #0x0
	mov r2, #0x1
	str r3, [sp, #0x8]
	bl FSi_ReadTable
_020D07DC:
	cmp r0, #0x0
	addne sp, sp, #0xC
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldrb r1, [sp]
	and r2, r1, #0x7F
	mov r1, r1, asr #0x7
	str r2, [r4, #0x10]
	and r1, r1, #0x1
	str r1, [r4, #0xC]
	ldr r2, [r4, #0x10]
	cmp r2, #0x0
	addeq sp, sp, #0xC
	moveq r0, #0x1
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r1, [r5, #0x34]
	cmp r1, #0x0
	bne _020D0858
	add r0, sp, #0x4
	add r1, r4, #0x14
	bl FSi_ReadTable
	cmp r0, #0x0
	addne sp, sp, #0xC
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r1, [r4, #0x10]
	mov r2, #0x0
	add r1, r4, r1
	strb r2, [r1, #0x14]
	b _020D0864
_020D0858:
	ldr r1, [sp, #0x8]
	add r1, r1, r2
	str r1, [sp, #0x8]
_020D0864:
	ldr r1, [r4, #0xC]
	cmp r1, #0x0
	beq _020D08B8
	add r0, sp, #0x4
	add r1, sp, #0x2
	mov r2, #0x2
	bl FSi_ReadTable
	cmp r0, #0x0
	addne sp, sp, #0xC
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r2, [r5, #0x8]
	ldr r1, _020D08E8
	str r2, [r4]
	ldrh r3, [sp, #0x2]
	mov r2, #0x0
	and r1, r3, r1
	strh r1, [r4, #0x4]
	strh r2, [r4, #0x6]
	str r2, [r4, #0x8]
	b _020D08D4
_020D08B8:
	ldr r1, [r5, #0x8]
	str r1, [r4]
	ldrh r1, [r5, #0x26]
	str r1, [r4, #0x4]
	ldrh r1, [r5, #0x26]
	add r1, r1, #0x1
	strh r1, [r5, #0x26]
_020D08D4:
	ldr r1, [sp, #0x8]
	str r1, [r5, #0x28]
	add sp, sp, #0xC
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D08E8: .word 0x00000FFF

	arm_func_start FSi_SeekDirCommand
FSi_SeekDirCommand: ; 0x020D08EC
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x10
	mov r6, r0
	ldr r5, [r6, #0x8]
	add r4, r6, #0x30
	str r5, [sp, #0x8]
	ldrh r1, [r4, #0x4]
	ldr r2, [r5, #0x34]
	add r0, sp, #0x8
	add r3, r2, r1, lsl #0x3
	add r1, sp, #0x0
	mov r2, #0x8
	str r3, [sp, #0xc]
	bl FSi_ReadTable
	movs r3, r0
	bne _020D0978
	add r12, r6, #0x20
	ldmia r4, {r0-r2}
	stmia r12, {r0-r2}
	ldrh r0, [r4, #0x6]
	cmp r0, #0x0
	bne _020D0968
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	bne _020D0968
	ldrh r0, [sp, #0x4]
	strh r0, [r6, #0x26]
	ldr r1, [r5, #0x34]
	ldr r0, [sp, #0x0]
	add r0, r1, r0
	str r0, [r6, #0x28]
_020D0968:
	ldrh r1, [sp, #0x6]
	ldr r0, _020D0988 ; =0x00000FFF
	and r0, r1, r0
	str r0, [r6, #0x2c]
_020D0978:
	mov r0, r3
	add sp, sp, #0x10
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D0988: .word 0x00000FFF

	arm_func_start FSi_WriteFileCommand
FSi_WriteFileCommand: ; 0x020D098C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x2c]
	ldr r3, [r0, #0x38]
	ldr lr, [r0, #0x8]
	ldr r1, [r0, #0x30]
	add r12, r2, r3
	str r12, [r0, #0x2c]
	ldr r12, [lr, #0x4c]
	mov r0, lr
	blx r12
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FSi_ReadFileCommand
FSi_ReadFileCommand: ; 0x020D09C4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x2c]
	ldr r3, [r0, #0x38]
	ldr lr, [r0, #0x8]
	ldr r1, [r0, #0x30]
	add r12, r2, r3
	str r12, [r0, #0x2c]
	ldr r12, [lr, #0x48]
	mov r0, lr
	blx r12
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FSi_SeekDirDirect
FSi_SeekDirDirect: ; 0x020D09FC
	ldr r3, [r0, #0xc]
	mov r2, #0x0
	orr r3, r3, #0x4
	str r3, [r0, #0xc]
	ldr r3, [r0, #0x8]
	ldr ip, _020D0A2C ; =FSi_TranslateCommand
	str r3, [r0, #0x30]
	str r2, [r0, #0x38]
	strh r2, [r0, #0x36]
	strh r1, [r0, #0x34]
	mov r1, #0x2
	bx r12
	.balign 4
_020D0A2C: .word FSi_TranslateCommand

	arm_func_start FSi_ReadTable
FSi_ReadTable:
	stmdb sp!, {r4-r8,lr}
	mov r7, r0
	ldr r5, [r7, #0x0]
	mov r6, r2
	ldr r2, [r5, #0x1c]
	mov r0, r5
	orr r2, r2, #0x200
	str r2, [r5, #0x1c]
	ldr r2, [r7, #0x4]
	ldr r4, [r5, #0x50]
	mov r3, r6
	blx r4
	cmp r0, #0x0
	beq _020D0A7C
	cmp r0, #0x1
	beq _020D0A7C
	cmp r0, #0x6
	beq _020D0A8C
	b _020D0AC8
_020D0A7C:
	ldr r1, [r5, #0x1c]
	bic r1, r1, #0x200
	str r1, [r5, #0x1c]
	b _020D0AC8
_020D0A8C:
	bl OS_DisableInterrupts
	ldr r1, [r5, #0x1c]
	mov r4, r0
	ands r0, r1, #0x200
	beq _020D0AB8
	add r8, r5, #0xc
_020D0AA4:
	mov r0, r8
	bl OS_SleepThread
	ldr r0, [r5, #0x1c]
	ands r0, r0, #0x200
	bne _020D0AA4
_020D0AB8:
	mov r0, r4
	bl OS_RestoreInterrupts
	ldr r0, [r5, #0x24]
	ldr r0, [r0, #0x14]
_020D0AC8:
	ldr r1, [r7, #0x4]
	add r1, r1, r6
	str r1, [r7, #0x4]
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FSi_StrNICmp
FSi_StrNICmp: ; 0x020D0ADC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	mov lr, #0x0
	bls _020D0B30
_020D0AF0:
	ldrb r12, [r0, lr]
	ldrb r3, [r1, lr]
	sub r12, r12, #0x41
	cmp r12, #0x19
	sub r3, r3, #0x41
	addls r12, r12, #0x20
	cmp r3, #0x19
	addls r3, r3, #0x20
	cmp r12, r3
	addne sp, sp, #0x4
	subne r0, r12, r3
	ldmneia sp!, {lr}
	bxne lr
	add lr, lr, #0x1
	cmp lr, r2
	blo _020D0AF0
_020D0B30:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
