	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

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
