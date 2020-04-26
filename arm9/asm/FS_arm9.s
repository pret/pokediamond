	.include "asm/macros.inc
	.include "global.inc"
	.section .text

	arm_func_start FSi_TranslateCommand
FSi_TranslateCommand:
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	ldr r0, [r8, #0xc]
	mov r7, r1
	mov r1, #0x1
	ldr r5, [r8, #0x8]
	mov r4, r1, lsl r7
	ands r0, r0, #0x4
	moveq r1, #0x0
	cmp r1, #0x0
	ldrne r0, [r5, #0x1c]
	orrne r0, r0, #0x200
	strne r0, [r5, #0x1c]
	ldreq r0, [r5, #0x1c]
	orreq r0, r0, #0x100
	streq r0, [r5, #0x1c]
	ldr r0, [r5, #0x58]
	ands r0, r0, r4
	beq _020CFFE4
	ldr r2, [r5, #0x54]
	mov r0, r8
	mov r1, r7
	blx r2
	mov r6, r0
	cmp r6, #0x8
	addls pc, pc, r6, lsl #0x2
	b _020CFFE8
_020CFFA0:
	b _020CFFC4
	b _020CFFC4
	b _020CFFE8
	b _020CFFE8
	b _020CFFC4
	b _020CFFE8
	b _020CFFE8
	b _020CFFE8
	b _020CFFCC
_020CFFC4:
	str r6, [r8, #0x14]
	b _020CFFE8
_020CFFCC:
	ldr r1, [r5, #0x58]
	mvn r0, r4
	and r0, r1, r0
	str r0, [r5, #0x58]
	mov r6, #0x7
	b _020CFFE8
_020CFFE4:
	mov r6, #0x7
_020CFFE8:
	cmp r6, #0x7
	bne _020D0004
	ldr r1, _020D00AC ; =0x02103F80
	mov r0, r8
	ldr r1, [r1, r7, lsl #0x2]
	blx r1
	mov r6, r0
_020D0004:
	cmp r6, #0x6
	bne _020D0060
	ldr r0, [r8, #0xc]
	ands r0, r0, #0x4
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020D00A0
	bl OS_DisableInterrupts
	ldr r1, [r5, #0x1c]
	mov r4, r0
	ands r0, r1, #0x200
	beq _020D0050
	add r6, r5, #0xc
_020D003C:
	mov r0, r6
	bl OS_SleepThread
	ldr r0, [r5, #0x1c]
	ands r0, r0, #0x200
	bne _020D003C
_020D0050:
	mov r0, r4
	ldr r6, [r8, #0x14]
	bl OS_RestoreInterrupts
	b _020D00A0
_020D0060:
	ldr r0, [r8, #0xc]
	ands r0, r0, #0x4
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	ldrne r0, [r5, #0x1c]
	bicne r0, r0, #0x200
	strne r0, [r5, #0x1c]
	strne r6, [r8, #0x14]
	bne _020D00A0
	ldr r1, [r5, #0x1c]
	mov r0, r8
	bic r2, r1, #0x100
	mov r1, r6
	str r2, [r5, #0x1c]
	bl FSi_ReleaseCommand
_020D00A0:
	mov r0, r6
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020D00AC: .word 0x02103F80

	arm_func_start FSi_ReleaseCommand
FSi_ReleaseCommand:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x0]
	mov r4, r0
	ldr r0, [r6, #0x4]
	cmp r1, #0x0
	strne r0, [r1, #0x4]
	cmp r0, #0x0
	strne r1, [r0, #0x0]
	mov r0, #0x0
	str r0, [r6, #0x0]
	ldr r1, [r6, #0x0]
	add r0, r6, #0x18
	str r1, [r6, #0x4]
	ldr r1, [r6, #0xc]
	bic r1, r1, #0x4f
	str r1, [r6, #0xc]
	str r5, [r6, #0x14]
	bl OS_WakeupThread
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r6,lr}
	bx lr

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


	arm_func_start FS_UnloadOverlay
FS_UnloadOverlay: ; 0x020D2040
	stmdb sp!, {lr}
	sub sp, sp, #0x2c
	mov r3, r0
	mov r2, r1
	add r0, sp, #0x0
	mov r1, r3
	bl FS_LoadOverlayInfo
_020D205C:
	cmp r0, #0x0
	beq _020D2074
	add r0, sp, #0x0
	bl FS_UnloadOverlayImage
	cmp r0, #0x0
	bne _020D2084
_020D2074:
	add sp, sp, #0x2c
	mov r0, #0x0
	ldmfd sp!, {lr}
	bx lr
_020D2084:
	mov r0, #0x1
	add sp, sp, #0x2c
	ldmfd sp!, {lr}
	bx lr

	arm_func_start FS_LoadOverlay
FS_LoadOverlay: ; 0x020D2094
	stmdb sp!, {lr}
	sub sp, sp, #0x2c
	mov r3, r0
	mov r2, r1
	add r0, sp, #0x0
	mov r1, r3
	bl FS_LoadOverlayInfo
_020D20B0:
	cmp r0, #0x0
	beq _020D20C8
	add r0, sp, #0x0
	bl FS_LoadOverlayImage
	cmp r0, #0x0
	bne _020D20D8
_020D20C8:
	add sp, sp, #0x2c
	mov r0, #0x0
	ldmfd sp!, {lr}
	bx lr
_020D20D8:
	add r0, sp, #0x0
	bl FS_StartOverlay
	mov r0, #0x1
	add sp, sp, #0x2c
	ldmfd sp!, {lr}
	bx lr

	arm_func_start FS_UnloadOverlayImage
FS_UnloadOverlayImage: ; 0x020D20F0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FS_EndOverlay
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FS_EndOverlay
FS_EndOverlay: ; 0x020D210C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r8, _020D220C ; =0x021D74C8
	mov r11, r0
	mov r9, #0x0
_020D2120:
	ldr r1, [r11, #0x8]
	ldr r0, [r11, #0xc]
	ldr r5, [r11, #0x4]
	add r0, r1, r0
	mov r7, r9
	mov r6, r9
	add r4, r5, r0
	bl OS_DisableInterrupts
	ldr lr, [r8, #0x0]
	mov r10, r9
	mov r12, lr
	cmp lr, #0x0
	beq _020D21C4
_020D2154:
	ldr r2, [r12, #0x8]
	ldr r3, [r12, #0x0]
	cmp r2, #0x0
	ldr r1, [r12, #0x4]
	bne _020D2178
	cmp r1, r5
	blo _020D2178
	cmp r1, r4
	blo _020D2188
_020D2178:
	cmp r2, r5
	blo _020D21B4
	cmp r2, r4
	bhs _020D21B4
_020D2188:
	cmp r6, #0x0
	strne r12, [r6, #0x0]
	moveq r7, r12
	cmp lr, r12
	streq r3, [r8, #0x0]
	moveq lr, r3
	str r9, [r12, #0x0]
	cmp r10, #0x0
	mov r6, r12
	strne r3, [r10, #0x0]
	b _020D21B8
_020D21B4:
	mov r10, r12
_020D21B8:
	mov r12, r3
	cmp r3, #0x0
	bne _020D2154
_020D21C4:
	bl OS_RestoreInterrupts
_020D21C8:
	cmp r7, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r11, lr}
	bxeq lr
_020D21D8:
	ldr r1, [r7, #0x4]
	ldr r4, [r7]
	cmp r1, #0x0
	beq _020D21F0
	ldr r0, [r7, #0x8]
	blx r1
_020D21F0:
	mov r7, r4
	cmp r4, #0x0
	bne _020D21D8
	b _020D2120
	add sp, sp, #0x4
	ldmia sp!, {r4-r11, lr}
	bx lr
_020D220C: .word 0x021D74C8

	arm_func_start FS_StartOverlay
FS_StartOverlay: ; 0x020D2210
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	bl FSi_GetOverlayBinarySize
	ldr r1, _020D2300 ; =0x027FFC40
	mov r4, r0
	ldrh r0, [r1, #0x0]
	cmp r0, #0x2
	bne _020D22A4
	ldrb r1, [r5, #0x1f]
	mov r0, #0x0
	ands r1, r1, #0x2
	beq _020D2280
	ldr r1, _020D2304 ; =0x02106F84
	ldr r3, _020D2308 ; =0x02106F84
	ldr r2, _020D230C ; =0x66666667
	sub r12, r1, r3
	smull r1, lr, r2, r12
	mov lr, lr, asr #0x3
	mov r1, r12, lsr #0x1f
	ldr r2, [r5, #0x0]
	add lr, r1, lr
	cmp r2, lr
	bhs _020D2280
	mov r0, #0x14
	mla r0, r2, r0, r3
	ldr r1, [r5, #0x4]
	mov r2, r4
	bl FSi_CompareDigest
_020D2280:
	cmp r0, #0x0
	bne _020D22A4
	ldr r0, [r5, #0x4]
	mov r2, r4
	mov r1, #0x0
	bl MI_CpuFill8
	bl OS_Terminate
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D22A4:
	ldrb r0, [r5, #0x1f]
	ands r0, r0, #0x1
	beq _020D22BC
	ldr r0, [r5, #0x4]
	add r0, r0, r4
	bl MIi_UncompressBackward
_020D22BC:
	ldr r0, [r5, #0x4]
	ldr r1, [r5, #0x8]
	bl DC_FlushRange
	ldr r6, [r5, #0x10]
	ldr r4, [r5, #0x14]
	cmp r6, r4
	ldmcsia sp!, {r4-r6,lr}
	bxcs lr
_020D22DC:
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	beq _020D22EC
	blx r0
_020D22EC:
	add r6, r6, #0x4
	cmp r6, r4
	blo _020D22DC
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D2300: .word 0x027FFC40
_020D2304: .word 0x02106F84
_020D2308: .word 0x02106F84
_020D230C: .word 0x66666667

	arm_func_start FSi_CompareDigest
FSi_CompareDigest:
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x58
	mov r4, r0
	mov r6, r1
	mov r5, r2
	add r0, sp, #0x4
	mov r1, #0x0
	mov r2, #0x14
	bl MI_CpuFill8
	ldr r0, _020D23AC ; =0x02106834
	ldr r1, _020D23B0 ; =0x02106838
	ldr r0, [r0, #0x0]
	ldr r2, [r1, #0x0]
	add r1, sp, #0x18
	bl MI_CpuCopy8
	ldr r3, _020D23B0 ; =0x02106838
	mov r1, r6
	ldr r12, [r3, #0x0]
	mov r2, r5
	add r0, sp, #0x4
	add r3, sp, #0x18
	str r12, [sp, #0x0]
	bl MATH_CalcHMACSHA1
	add r2, sp, #0x4
	mov r3, #0x0
_020D2374:
	ldr r1, [r2, #0x0]
	ldr r0, [r4, r3]
	cmp r1, r0
	bne _020D2394
	add r3, r3, #0x4
	cmp r3, #0x14
	add r2, r2, #0x4
	blo _020D2374
_020D2394:
	cmp r3, #0x14
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x58
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D23AC: .word 0x02106834
_020D23B0: .word 0x02106838

	arm_func_start FS_LoadOverlayImage
FS_LoadOverlayImage: ; 0x020D23B4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x54
	mov r5, r0
	add r0, sp, #0x8
	bl FS_InitFile
_020D23C8:
	add r0, sp, #0x0
	mov r1, r5
	bl FS_GetOverlayFileID
	add r1, sp, #0x0
	add r0, sp, #0x8
	ldmia r1, {r1, r2}
	bl FS_OpenFileFast
	cmp r0, #0x0
	addeq sp, sp, #0x54
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5, lr}
	bxeq lr
	mov r0, r5
	bl FSi_GetOverlayBinarySize
	mov r4, r0
	mov r0, r5
	bl FS_ClearOverlayImage
	ldr r1, [r5, #0x4]
	add r0, sp, #0x8
	mov r2, r4
	bl FS_ReadFile
	cmp r4, r0
	beq _020D243C
	add r0, sp, #0x8
	bl FS_CloseFile
	add sp, sp, #0x54
	mov r0, #0x0
	ldmia sp!, {r4-r5, lr}
	bx lr
_020D243C:
	add r0, sp, #0x8
	bl FS_CloseFile
	mov r0, #0x1
	add sp, sp, #0x54
	ldmia sp!, {r4-r5, lr}
	bx lr

	arm_func_start FS_LoadOverlayImageAsync
FS_LoadOverlayImageAsync: ; 0x020D2454
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r5, r1
	mov r6, r0
	mov r0, r5
	bl FS_InitFile
_020D246C:
	add r0, sp, #0x0
	mov r1, r6
	bl FS_GetOverlayFileID
	add r1, sp, #0x0
	mov r0, r5
	ldmia r1, {r1, r2}
	bl FS_OpenFileFast
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6, lr}
	bxeq lr
	mov r0, r6
	bl FSi_GetOverlayBinarySize
	mov r4, r0
	mov r0, r6
	bl FS_ClearOverlayImage
	ldr r1, [r6, #0x4]
	mov r0, r5
	mov r2, r4
	bl FS_ReadFileAsync
	cmp r4, r0
	addeq sp, sp, #0x8
	moveq r0, #0x1
	ldmeqia sp!, {r4-r6, lr}
	bxeq lr
	mov r0, r5
	bl FS_CloseFile
	mov r0, #0x0
	add sp, sp, #0x8
	ldmia sp!, {r4-r6, lr}
	bx lr

	arm_func_start FS_LoadOverlayInfo
FS_LoadOverlayInfo:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x64
	movs r4, r1
	mov r5, r0
	ldreq r0, _020D25EC ; =0x021D5404
	ldrne r0, _020D25F0 ; =0x021D540C
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	beq _020D25A8
	ldr r0, [r0, #0x4]
	mov r2, r2, lsl #0x5
	cmp r2, r0
	addcs sp, sp, #0x64
	movcs r0, #0x0
	ldmcsia sp!, {r4-r5,lr}
	bxcs lr
	add r0, r3, r2
	mov r1, r5
	mov r2, #0x20
	bl MI_CpuCopy8
	add r0, sp, #0x18
	str r4, [r5, #0x20]
	bl FS_InitFile
	add r0, sp, #0x10
	mov r1, r5
	bl FS_GetOverlayFileID
	add r1, sp, #0x10
	add r0, sp, #0x18
	ldmia r1, {r1-r2}
	bl FS_OpenFileFast
_020D2564:
	cmp r0, #0x0
	addeq sp, sp, #0x64
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r1, [sp, #0x3c]
	add r0, sp, #0x18
	str r1, [r5, #0x24]
	ldr r2, [sp, #0x40]
	ldr r1, [sp, #0x3c]
	sub r1, r2, r1
	str r1, [r5, #0x28]
	bl FS_CloseFile
	add sp, sp, #0x64
	mov r0, #0x1
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D25A8:
	ldr r1, _020D25F4 ; =0x027FFE50
	ldr ip, _020D25F8 ; =0x027FFE58
	ldr r0, [r1, #0x0]
	ldr r3, _020D25FC ; =0x021D5414
	str r0, [sp, #0x0]
	ldr r1, [r1, #0x4]
	mov r0, r5
	str r1, [sp, #0x4]
	ldr r5, [r12, #0x0]
	mov r1, r4
	str r5, [sp, #0x8]
	ldr r4, [r12, #0x4]
	str r4, [sp, #0xc]
	bl FSi_LoadOverlayInfoCore
	add sp, sp, #0x64
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D25EC: .word 0x021D5404
_020D25F0: .word 0x021D540C
_020D25F4: .word 0x027FFE50
_020D25F8: .word 0x027FFE58
_020D25FC: .word 0x021D5414

	arm_func_start FSi_LoadOverlayInfoCore
FSi_LoadOverlayInfoCore: ; 0x020D2600
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x54
	movs r9, r1
	ldreq r5, [sp, #0x74]
	ldreq r6, [sp, #0x70]
	ldrne r5, [sp, #0x7c]
	ldrne r6, [sp, #0x78]
	mov r7, r2, lsl #0x5
	cmp r7, r5
	mov r4, r0
	mov r8, r3
	addcs sp, sp, #0x54
	movcs r0, #0x0
	ldmcsia sp!, {r4-r9,lr}
	bxcs lr
	add r0, sp, #0xc
	bl FS_InitFile
	mvn r12, #0x0
	add r0, sp, #0xc
	mov r1, r8
	add r2, r6, r7
	add r3, r6, r5
	str r12, [sp, #0x0]
	bl FS_OpenFileDirect
_020D2660:
	cmp r0, #0
	addeq sp, sp, #0x54
	moveq r0, #0
	ldmeqia sp!, {r4-r9, lr}
	bxeq lr
	add r0, sp, #12
	mov r1, r4
	mov r2, #32
	bl FS_ReadFile
	cmp r0, #32
	beq _020D26A4
	add r0, sp, #12
	bl FS_CloseFile
	add sp, sp, #0x54
	mov r0, #0x0
	ldmia sp!, {r4-r9, lr}
	bx lr
_020D26A4:
	add r0, sp, #0xC
	bl FS_CloseFile
	add r0, sp, #0x4
	mov r1, r4
	str r9, [r4, #0x20]
	bl FS_GetOverlayFileID
	add r1, sp, #0x4
	add r0, sp, #0xC
	ldmia r1, {r1, r2}
	bl FS_OpenFileFast
	cmp r0, #0x0
	addeq sp, sp, #0x54
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9, lr}
	bxeq lr
	ldr r1, [sp, #0x30]
	add r0, sp, #0xC
	str r1, [r4, #0x24]
	ldr r2, [sp, #0x34]
	ldr r1, [sp, #0x30]
	sub r1, r2, r1
	str r1, [r4, #0x28]
	bl FS_CloseFile
	mov r0, #0x1
	add sp, sp, #0x54
	ldmia sp!, {r4-r9, lr}
	bx lr

	arm_func_start FS_GetOverlayFileID
FS_GetOverlayFileID: ; 0x020D2710
	sub sp, sp, #0x8
	ldr r2, _020D2734 ; =0x021D5414
	str r2, [sp, #0x0]
	ldr r1, [r1, #0x18]
	str r1, [sp, #0x4]
	str r2, [r0, #0x0]
	str r1, [r0, #0x4]
	add sp, sp, #0x8
	bx lr
	.balign 4
_020D2734: .word 0x021D5414

	arm_func_start FS_ClearOverlayImage
FS_ClearOverlayImage: ; 0x020D2738
	stmdb sp!, {r4-r6,lr}
	ldr r5, [r0, #0x8]
	ldr r1, [r0, #0xc]
	ldr r6, [r0, #0x4]
	add r4, r5, r1
	mov r0, r6
	mov r1, r4
	bl IC_InvalidateRange
	mov r0, r6
	mov r1, r4
	bl DC_InvalidateRange
	add r0, r6, r5
	sub r2, r4, r5
	mov r1, #0x0
	bl MI_CpuFill8
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FSi_GetOverlayBinarySize
FSi_GetOverlayBinarySize: ; 0x020D277C
	ldrb r1, [r0, #0x1f]
	ands r1, r1, #0x1
	ldrne r0, [r0, #0x1c]
	movne r0, r0, lsl #0x8
	movne r0, r0, lsr #0x8
	ldreq r0, [r0, #0x8]
	bx lr
