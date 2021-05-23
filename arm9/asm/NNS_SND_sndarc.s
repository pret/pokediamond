	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	; sCurrent
	.global UNK_021D28C0
UNK_021D28C0: ; 0x021D28C0
	.space 0x4

	.section .text

	; _end
	arm_func_start SDATi_SymbDtor
SDATi_SymbDtor: ; 0x020C209C
	mov r0, #0x0
	str r0, [r2, #0x88]
	bx lr

	; _end
	arm_func_start SDATi_FatDtor
SDATi_FatDtor: ; 0x020C20A8
	mov r0, #0x0
	str r0, [r2, #0x84]
	bx lr

	; _end
	arm_func_start SDATi_InfoDtor
SDATi_InfoDtor: ; 0x020C20B4
	mov r0, #0x0
	str r0, [r2, #0x8c]
	bx lr

	; NNS_SndArcSetFileAddress
	arm_func_start FUN_020C20C0
FUN_020C20C0: ; 0x020C20C0
	ldr r2, _020C20D8 ; =UNK_021D28C0
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x84]
	add r0, r2, r0, lsl #0x4
	str r1, [r0, #0x14]
	bx lr
	.balign 4
_020C20D8: .word UNK_021D28C0

	; NNS_SndArcGetFileAddress
	arm_func_start FUN_020C20DC
FUN_020C20DC: ; 0x020C20DC
	ldr r1, _020C2100 ; =UNK_021D28C0
	ldr r1, [r1, #0x0]
	ldr r2, [r1, #0x84]
	ldr r1, [r2, #0x8]
	cmp r0, r1
	movcs r0, #0x0
	addcc r0, r2, r0, lsl #0x4
	ldrcc r0, [r0, #0x14]
	bx lr
	.balign 4
_020C2100: .word UNK_021D28C0

	; NNS_SndArcReadFile
	arm_func_start FUN_020C2104
FUN_020C2104: ; 0x020C2104
	stmdb sp!, {r4-r6,lr}
	ldr r4, _020C2178 ; =UNK_021D28C0
	mov r5, r2
	ldr r4, [r4, #0x0]
	mov r6, r1
	ldr r2, [r4, #0x84]
	ldr r1, [r2, #0x8]
	cmp r0, r1
	mvncs r0, #0x0
	ldmcsia sp!, {r4-r6,pc}
	add r1, r2, #0xc
	add r1, r1, r0, lsl #0x4
	ldr r0, [r1, #0x4]
	ldr r1, [r1, #0x0]
	sub r0, r0, r3
	cmp r5, r0
	movhi r5, r0
	add r0, r4, #0x34
	add r1, r1, r3
	mov r2, #0x0
	bl FS_SeekFile
	cmp r0, #0x0
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	mov r1, r6
	mov r2, r5
	add r0, r4, #0x34
	bl FS_ReadFile
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C2178: .word UNK_021D28C0

	; NNS_SndArcGetFileSize
	arm_func_start FUN_020C217C
FUN_020C217C: ; 0x020C217C
	ldr r1, _020C21A0 ; =UNK_021D28C0
	ldr r1, [r1, #0x0]
	ldr r2, [r1, #0x84]
	ldr r1, [r2, #0x8]
	cmp r0, r1
	movcs r0, #0x0
	addcc r0, r2, r0, lsl #0x4
	ldrcc r0, [r0, #0x10]
	bx lr
	.balign 4
_020C21A0: .word UNK_021D28C0

	; NNS_SndArcGetGroupInfo
	arm_func_start FUN_020C21A4
FUN_020C21A4: ; 0x020C21A4
	ldr r1, _020C2204 ; =UNK_021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0x1c]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C2204: .word UNK_021D28C0

	; NNS_SndArcGetPlayerInfo
	arm_func_start FUN_020C2208
FUN_020C2208: ; 0x020C2208
	ldr r1, _020C2268 ; =UNK_021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0x18]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C2268: .word UNK_021D28C0

	; NNS_SndArcGetWaveArcInfo
	arm_func_start FUN_020C226C
FUN_020C226C: ; 0x020C226C
	ldr r1, _020C22CC ; =UNK_021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0x14]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C22CC: .word UNK_021D28C0

	; NNS_SndArcGetBankInfo
	arm_func_start FUN_020C22D0
FUN_020C22D0: ; 0x020C22D0
	ldr r1, _020C2330 ; =UNK_021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0x10]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C2330: .word UNK_021D28C0

	; NNS_SndArcGetSeqArcInfo
	arm_func_start FUN_020C2334
FUN_020C2334: ; 0x020C2334
	ldr r1, _020C2394 ; =UNK_021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0xc]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C2394: .word UNK_021D28C0

	; NNS_SndArcGetSeqInfo
	arm_func_start FUN_020C2398
FUN_020C2398: ; 0x020C2398
	ldr r1, _020C23F8 ; =UNK_021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0x8]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C23F8: .word UNK_021D28C0

	; _end
	arm_func_start FUN_020C23FC
FUN_020C23FC: ; 0x020C23FC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020C2398
	cmp r0, #0x0
	moveq r0, #0x0
	addne r0, r0, #0x4
	add sp, sp, #0x4
	ldmia sp!, {pc}

	; NNS_SndArcGetCurrent
	arm_func_start FUN_020C241C
FUN_020C241C: ; 0x020C241C
	ldr r0, _020C2428 ; =UNK_021D28C0
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020C2428: .word UNK_021D28C0

	; NNS_SndArcSetCurrent
	arm_func_start FUN_020C242C
FUN_020C242C: ; 0x020C242C
	ldr r1, _020C2440 ; =UNK_021D28C0
	ldr r2, [r1, #0x0]
	str r0, [r1, #0x0]
	mov r0, r2
	bx lr
	.balign 4
_020C2440: .word UNK_021D28C0

	; NNS_SndArcInitOnMemory
	arm_func_start FUN_020C2444
FUN_020C2444: ; 0x020C2444
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	mov r0, r4
	mov r1, r5
	mov r2, #0x30
	bl MIi_CpuCopy32
	ldr r0, [r5, #0x18]
	mov r12, #0x0
	cmp r0, #0x0
	moveq r0, #0x0
	addne r0, r4, r0
	str r0, [r5, #0x8c]
	ldr r0, [r5, #0x20]
	cmp r0, #0x0
	moveq r0, #0x0
	addne r0, r4, r0
	str r0, [r5, #0x84]
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	moveq r0, #0x0
	addne r0, r4, r0
	str r0, [r5, #0x88]
	ldr r2, [r5, #0x84]
	ldr r0, [r2, #0x8]
	cmp r0, #0x0
	bls _020C24F0
	mov r3, r12
	mov r1, r12
_020C24BC:
	add r2, r2, #0xc
	ldr r0, [r2, r3]
	add r2, r2, r3
	cmp r0, #0x0
	moveq r0, r1
	addne r0, r4, r0
	str r0, [r2, #0x8]
	ldr r2, [r5, #0x84]
	add r12, r12, #0x1
	ldr r0, [r2, #0x8]
	add r3, r3, #0x10
	cmp r12, r0
	blo _020C24BC
_020C24F0:
	mov r1, #0x0
	ldr r0, _020C2508 ; =UNK_021D28C0
	str r1, [r5, #0x30]
	str r5, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C2508: .word UNK_021D28C0

SDATi_ReadHeaders:
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r6, r0
	mov r5, r1
	mov r1, #0x0
	mov r4, r2
	mov r2, r1
	add r0, r6, #0x34
	bl FS_SeekFile
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	mov r1, r6
	add r0, r6, #0x34
	mov r2, #0x30
	bl FS_ReadFile
	cmp r0, #0x30
	addne sp, sp, #0x8
	movne r0, #0x0
	ldmneia sp!, {r4-r6,pc}
	cmp r5, #0x0
	beq _020C26E0
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r1, [r6, #0x1c]
	ldr r2, _020C26EC ; =SDATi_InfoDtor
	mov r0, r5
	mov r3, r6
	bl SDATi_AllocAndInitChunk
	str r0, [r6, #0x8c]
	ldr r0, [r6, #0x8c]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r1, [r6, #0x18]
	add r0, r6, #0x34
	mov r2, #0x0
	bl FS_SeekFile
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r1, [r6, #0x8c]
	ldr r2, [r6, #0x1c]
	add r0, r6, #0x34
	bl FS_ReadFile
	ldr r1, [r6, #0x1c]
	cmp r0, r1
	addne sp, sp, #0x8
	movne r0, #0x0
	ldmneia sp!, {r4-r6,pc}
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r1, [r6, #0x24]
	ldr r2, _020C26F0 ; =SDATi_FatDtor
	mov r0, r5
	mov r3, r6
	bl SDATi_AllocAndInitChunk
	str r0, [r6, #0x84]
	ldr r0, [r6, #0x84]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r1, [r6, #0x20]
	add r0, r6, #0x34
	mov r2, #0x0
	bl FS_SeekFile
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r1, [r6, #0x84]
	ldr r2, [r6, #0x24]
	add r0, r6, #0x34
	bl FS_ReadFile
	ldr r1, [r6, #0x24]
	cmp r0, r1
	addne sp, sp, #0x8
	movne r0, #0x0
	ldmneia sp!, {r4-r6,pc}
	cmp r4, #0x0
	beq _020C26E0
	ldr r1, [r6, #0x14]
	cmp r1, #0x0
	beq _020C26E0
	mov r4, #0x0
	ldr r2, _020C26F4 ; =SDATi_SymbDtor
	mov r0, r5
	mov r3, r6
	str r4, [sp, #0x0]
	bl SDATi_AllocAndInitChunk
	str r0, [r6, #0x88]
	ldr r0, [r6, #0x88]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, r4
	ldmeqia sp!, {r4-r6,pc}
	ldr r1, [r6, #0x10]
	add r0, r6, #0x34
	mov r2, r4
	bl FS_SeekFile
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, r4
	ldmeqia sp!, {r4-r6,pc}
	ldr r1, [r6, #0x88]
	ldr r2, [r6, #0x14]
	add r0, r6, #0x34
	bl FS_ReadFile
	ldr r1, [r6, #0x14]
	cmp r0, r1
	addne sp, sp, #0x8
	movne r0, r4
	ldmneia sp!, {r4-r6,pc}
_020C26E0:
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C26EC: .word SDATi_InfoDtor
_020C26F0: .word SDATi_FatDtor
_020C26F4: .word SDATi_SymbDtor

	; NNS_SndArcInit
	arm_func_start SDAT_Open
SDAT_Open: ; 0x020C26F8
	; r0: &sSoundDataBuffer
	; r1: char* filename
	; r2: (&sSoundDataBuffer)->unk_0090
	; r3: 0
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r12, #0x0
	str r12, [r6, #0x8c]
	str r12, [r6, #0x84]
	add r0, r6, #0x7c
	mov r5, r2
	mov r4, r3
	str r12, [r6, #0x88]
	bl FS_ConvertPathToFileID
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	add r0, r6, #0x34
	bl FS_InitFile
	add r1, r6, #0x7c
	add r0, r6, #0x34
	ldmia r1, {r1-r2}
	bl FS_OpenFileFast
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	mov r3, #0x1
	mov r0, r6
	mov r1, r5
	mov r2, r4
	str r3, [r6, #0x30]
	bl SDATi_ReadHeaders
	cmp r0, #0x0
	ldrne r0, _020C2770 ; =UNK_021D28C0
	strne r6, [r0, #0x0]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C2770: .word UNK_021D28C0

