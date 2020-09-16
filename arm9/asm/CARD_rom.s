	.include "asm/macros.inc"
	.include "global.inc"

	.extern OSi_ThreadInfo
	.extern cardi_common

	.section .data

	.global UNK_02106A50
UNK_02106A50: ; 0x02106A50
	.word 0x027FFE00

	.section .bss

	.global UNK_021D5BE0
UNK_021D5BE0: ; 0x021D5BE0
	.space 0x20

	.global UNK_021D5C00
UNK_021D5C00: ; 0x021D5C00
	.space 0x220

    .text

	arm_func_start CARDi_GetRomAccessor
CARDi_GetRomAccessor: ; 0x020D7210
	ldr r0, _020D7218 ; =CARDi_ReadCard
	bx lr
	.balign 4
_020D7218: .word CARDi_ReadCard

	arm_func_start CARD_WaitRomAsync
CARD_WaitRomAsync: ; 0x020D721C
	ldr ip, _020D7224 ; =CARDi_WaitAsync
	bx r12
	.balign 4
_020D7224: .word CARDi_WaitAsync

	arm_func_start CARD_Init
CARD_Init: ; 0x020D7228
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr ip, _020D72A0 ; =cardi_common
	ldr r0, [r12, #0x114]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	mov r0, #0x1
	str r0, [r12, #0x114]
	mov r3, #0x0
	str r3, [r12, #0x24]
	ldr r0, [r12, #0x24]
	mvn r1, #0x0
	str r0, [r12, #0x20]
	ldr r2, [r12, #0x20]
	ldr r0, _020D72A4 ; =UNK_021D5BE0
	str r2, [r12, #0x1c]
	str r1, [r12, #0x28]
	str r3, [r12, #0x38]
	str r3, [r12, #0x3c]
	str r3, [r0, #0x0]
	bl CARDi_InitCommon
	bl CARDi_GetRomAccessor
	ldr r1, _020D72A8 ; =UNK_021D5C00
	str r0, [r1, #0x0]
	bl CARD_InitPulledOutCallback
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D72A0: .word cardi_common
_020D72A4: .word UNK_021D5BE0
_020D72A8: .word UNK_021D5C00

	arm_func_start CARDi_ReadRom
CARDi_ReadRom: ; 0x020D72AC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r6, _020D73C0 ; =cardi_common
	mov r10, r0
	mov r9, r1
	mov r8, r2
	mov r7, r3
	ldr fp, _020D73C4 ; =UNK_021D5C00
	bl CARD_CheckEnabled
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x114]
	mov r5, r0
	ands r0, r1, #0x4
	beq _020D72FC
	add r4, r6, #0x10c
_020D72E8:
	mov r0, r4
	bl OS_SleepThread
	ldr r0, [r6, #0x114]
	ands r0, r0, #0x4
	bne _020D72E8
_020D72FC:
	ldr r1, [r6, #0x114]
	ldr r0, [sp, #0x28]
	orr r1, r1, #0x4
	str r1, [r6, #0x114]
	ldr r1, [sp, #0x2c]
	str r0, [r6, #0x38]
	mov r0, r5
	str r1, [r6, #0x3c]
	bl OS_RestoreInterrupts
	ldr r0, _020D73C8 ; =UNK_021D5BE0
	str r10, [r6, #0x28]
	ldr r0, [r0, #0x0]
	cmp r10, #0x3
	add r0, r9, r0
	str r0, [r6, #0x1c]
	str r8, [r6, #0x20]
	str r7, [r6, #0x24]
	bhi _020D734C
	mov r0, r10
	bl MI_StopDma
_020D734C:
	mov r0, r11
	bl CARDi_TryReadCardDma
_020D7354: ; 0x020D7354
	cmp r0, #0x0
	beq _020D7380
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	bl CARD_WaitRomAsync
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D7380:
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	beq _020D73A0
	ldr r0, _020D73CC ; =CARDi_ReadRomSyncCore
	bl CARDi_SetTask
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D73A0:
	ldr r1, _020D73D0 ; =OSi_ThreadInfo
	mov r0, r6
	ldr r1, [r1, #0x4]
	str r1, [r6, #0x104]
	bl CARDi_ReadRomSyncCore
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020D73C0: .word cardi_common
_020D73C4: .word UNK_021D5C00
_020D73C8: .word UNK_021D5BE0
_020D73CC: .word CARDi_ReadRomSyncCore
_020D73D0: .word OSi_ThreadInfo

	arm_func_start CARDi_ReadRomSyncCore
CARDi_ReadRomSyncCore: ; 0x020D73D4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r4, _020D7478 ; =UNK_021D5C00
	mov r0, r4
	bl CARDi_ReadFromCache
_020D73E8: ; 0x020D73E8
	cmp r0, #0x0
	beq _020D73FC
	ldr r1, [r4, #0x0]
	mov r0, r4
	blx r1
_020D73FC:
	ldr r7, _020D747C ; =cardi_common
	bl CARDi_ReadRomIDCore
	bl CARDi_CheckPulledOutCore
_020D7408: ; 0x020D7408
	ldr r0, [r7, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
	ldr r6, [r7, #0x38]
	ldr r5, [r7, #0x3c]
	bl OS_DisableInterrupts
	ldr r1, [r7, #0x114]
	mov r4, r0
	bic r0, r1, #0x4c
	str r0, [r7, #0x114]
	add r0, r7, #0x10c
	bl OS_WakeupThread
	ldr r0, [r7, #0x114]
	ands r0, r0, #0x10
	beq _020D744C
	add r0, r7, #0x44
	bl OS_WakeupThreadDirect
_020D744C:
	mov r0, r4
	bl OS_RestoreInterrupts
_020D7454: ; 0x020D7454
	cmp r6, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r5
	blx r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020D7478: .word UNK_021D5C00
_020D747C: .word cardi_common

	arm_func_start CARDi_ReadRomIDCore
CARDi_ReadRomIDCore: ; 0x020D7480
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, #0xb8000000
	mov r1, #0x0
	bl CARDi_SetRomOp
	ldr r1, _020D74DC ; =UNK_02106A50
	mov r0, #0x2000
	ldr r1, [r1, #0x0]
	rsb r0, r0, #0x0
	ldr r2, [r1, #0x60]
	ldr r1, _020D74E0 ; =0x040001A4
	bic r2, r2, #0x7000000
	orr r2, r2, #0xa7000000
	and r0, r2, r0
	str r0, [r1, #0x0]
_020D74BC:
	ldr r0, [r1, #0x0]
	ands r0, r0, #0x800000
	beq _020D74BC
	ldr r0, _020D74E4 ; =0x04100010
	ldr r0, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D74DC: .word UNK_02106A50
_020D74E0: .word 0x040001A4
_020D74E4: .word 0x04100010

	arm_func_start CARDi_ReadCard
CARDi_ReadCard: ; 0x020D74E8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r10, r0
	ldr sb, _020D75DC ; =cardi_common
	add r7, r10, #0x20
	ldr r5, _020D75E0 ; =0x04100010
	ldr r6, _020D75E4 ; =0x040001A4
	mov r11, #0x0
	mov r0, #0x200
	rsb r4, r0, #0x0
_020D7510:
	ldr r0, [r9, #0x1c]
	and r1, r0, r4
	cmp r1, r0
	bne _020D7538
	ldr r8, [r9, #0x20]
	ands r0, r8, #0x3
	bne _020D7538
	ldr r0, [r9, #0x24]
	cmp r0, #0x200
	bhs _020D7540
_020D7538:
	mov r8, r7
	str r1, [r10, #0x8]
_020D7540:
	mov r0, r1, lsr #0x8
	orr r0, r0, #0xb7000000
	mov r1, r1, lsl #0x18
	bl CARDi_SetRomOp
	ldr r1, [r10, #0x4]
	mov r0, r11
	str r1, [r6, #0x0]
_020D755C:
	ldr r2, [r6, #0x0]
	ands r1, r2, #0x800000
	beq _020D7578
	ldr r1, [r5, #0x0]
	cmp r0, #0x200
	strcc r1, [r8, r0, lsl #0x2]
	addcc r0, r0, #0x1
_020D7578:
	ands r1, r2, #0x80000000
	bne _020D755C
	ldr r0, [r9, #0x20]
	cmp r8, r0
	bne _020D75C0
	ldr r2, [r9, #0x1c]
	ldr r1, [r9, #0x20]
	ldr r0, [r9, #0x24]
	add r2, r2, #0x200
	add r1, r1, #0x200
	subs r0, r0, #0x200
	str r2, [r9, #0x1c]
	str r1, [r9, #0x20]
	str r0, [r9, #0x24]
	bne _020D7510
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D75C0:
	mov r0, r10
	bl CARDi_ReadFromCache
_020D75C8: ; 0x020D75C8
	cmp r0, #0x0
	bne _020D7510
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020D75DC: .word cardi_common
_020D75E0: .word 0x04100010
_020D75E4: .word 0x040001A4

	arm_func_start CARDi_TryReadCardDma
CARDi_TryReadCardDma:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr fp, _020D7748 ; =cardi_common
	mov r7, #0x0
	ldr r9, [r11, #0x20]
	mov r10, r0
	mov r6, r7
	mov r5, r7
	mov r1, r7
	ands r4, r9, #0x1f
	ldr r8, [r11, #0x24]
	bne _020D7624
	ldr r0, [r11, #0x28]
	cmp r0, #0x3
	movls r1, #0x1
_020D7624:
	cmp r1, #0x0
	beq _020D7678
	bl OS_GetDTCMAddress
	ldr r1, _020D774C ; =0x01FF8000
	add r2, r9, r8
	cmp r2, r1
	mov r3, #0x1
	mov r1, #0x0
	bls _020D7650
	cmp r9, #0x2000000
	movcc r1, r3
_020D7650:
	cmp r1, #0x0
	bne _020D7670
	cmp r0, r2
	bhs _020D766C
	add r0, r0, #0x4000
	cmp r0, r9
	bhi _020D7670
_020D766C:
	mov r3, #0x0
_020D7670:
	cmp r3, #0x0
	moveq r5, #0x1
_020D7678:
	cmp r5, #0x0
	beq _020D7694
	ldr r1, [r11, #0x1c]
	ldr r0, _020D7750 ; =0x000001FF
	orr r1, r1, r8
	ands r0, r1, r0
	moveq r6, #0x1
_020D7694:
	cmp r6, #0x0
	beq _020D76A4
	cmp r8, #0x0
	movne r7, #0x1
_020D76A4:
	ldr r0, _020D7754 ; =UNK_02106A50
	cmp r7, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x60]
	bic r0, r0, #0x7000000
	orr r0, r0, #0xa1000000
	str r0, [r10, #0x4]
	beq _020D7738
	bl OS_DisableInterrupts
	mov r5, r0
	mov r0, r9
	mov r1, r8
	bl IC_InvalidateRange
_020D76D8: ; 0x020D76D8
	cmp r4, #0x0
	beq _020D7700
	sub r9, r9, r4
	mov r0, r9
	mov r1, #0x20
	bl DC_StoreRange
	add r0, r9, r8
	mov r1, #0x20
	bl DC_StoreRange
	add r8, r8, #0x20
_020D7700:
	mov r0, r9
	mov r1, r8
	bl DC_InvalidateRange
	bl DC_WaitWriteBufferEmpty
	ldr r1, _020D7758 ; =CARDi_OnReadCard
	mov r0, #0x80000
	bl OS_SetIrqFunction
	mov r0, #0x80000
	bl OS_ResetRequestIrqMask
	mov r0, #0x80000
	bl OS_EnableIrqMask
	mov r0, r5
	bl OS_RestoreInterrupts
	bl CARDi_SetCardDma
_020D7738:
	mov r0, r7
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020D7748: .word cardi_common
_020D774C: .word 0x01FF8000
_020D7750: .word 0x000001FF
_020D7754: .word UNK_02106A50
_020D7758: .word CARDi_OnReadCard

	arm_func_start CARDi_OnReadCard
CARDi_OnReadCard: ; 0x020D775C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r0, _020D7838 ; =cardi_common
	ldr r0, [r0, #0x28]
	bl MI_StopDma
	ldr r0, _020D7838 ; =cardi_common
	ldr r3, [r0, #0x1c]
	ldr r2, [r0, #0x20]
	ldr r1, [r0, #0x24]
	add r3, r3, #0x200
	add r2, r2, #0x200
	subs r1, r1, #0x200
	str r3, [r0, #0x1c]
	str r2, [r0, #0x20]
	str r1, [r0, #0x24]
	bne _020D7828
	mov r0, #0x80000
	bl OS_DisableIrqMask
	mov r0, #0x80000
	bl OS_ResetRequestIrqMask
	ldr r7, _020D7838 ; =cardi_common
	bl CARDi_ReadRomIDCore
	bl CARDi_CheckPulledOutCore
_020D77B8: ; 0x020D77B8
	ldr r0, [r7, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
	ldr r6, [r7, #0x38]
	ldr r5, [r7, #0x3c]
	bl OS_DisableInterrupts
	ldr r1, [r7, #0x114]
	mov r4, r0
	bic r0, r1, #0x4c
	str r0, [r7, #0x114]
	add r0, r7, #0x10c
	bl OS_WakeupThread
	ldr r0, [r7, #0x114]
	ands r0, r0, #0x10
	beq _020D77FC
	add r0, r7, #0x44
	bl OS_WakeupThreadDirect
_020D77FC:
	mov r0, r4
	bl OS_RestoreInterrupts
_020D7804: ; 0x020D7804
	cmp r6, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r5
	blx r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D7828:
	bl CARDi_SetCardDma
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020D7838: .word cardi_common

	arm_func_start CARDi_SetCardDma
CARDi_SetCardDma: ; 0x020D783C
	stmdb sp!, {r4,lr}
	ldr r4, _020D7884 ; =cardi_common
	ldr r1, _020D7888 ; =0x04100010
	ldr r0, [r4, #0x28]
	ldr r2, [r4, #0x20]
	mov r3, #0x200
	bl MIi_CardDmaCopy32
	ldr r1, [r4, #0x1c]
	mov r0, r1, lsr #0x8
	orr r0, r0, #0xb7000000
	mov r1, r1, lsl #0x18
	bl CARDi_SetRomOp
	ldr r0, _020D788C ; =UNK_021D5C00
	ldr r1, _020D7890 ; =0x040001A4
	ldr r0, [r0, #0x4]
	str r0, [r1, #0x0]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D7884: .word cardi_common
_020D7888: .word 0x04100010
_020D788C: .word UNK_021D5C00
_020D7890: .word 0x040001A4

	arm_func_start CARDi_SetRomOp
CARDi_SetRomOp: ; 0x020D7894
	ldr r3, _020D790C ; =0x040001A4
_020D7898:
	ldr r2, [r3, #0x0]
	ands r2, r2, #0x80000000
	bne _020D7898
	ldr r3, _020D7910 ; =0x040001A1
	mov r12, #0xc0
	ldr r2, _020D7914 ; =0x040001A8
	strb r12, [r3, #0x0]
	mov r12, r0, lsr #0x18
	ldr r3, _020D7918 ; =0x040001A9
	strb r12, [r2, #0x0]
	mov r12, r0, lsr #0x10
	ldr r2, _020D791C ; =0x040001AA
	strb r12, [r3, #0x0]
	mov r12, r0, lsr #0x8
	ldr r3, _020D7920 ; =0x040001AB
	strb r12, [r2, #0x0]
	ldr r2, _020D7924 ; =0x040001AC
	strb r0, [r3, #0x0]
	mov r3, r1, lsr #0x18
	ldr r0, _020D7928 ; =0x040001AD
	strb r3, [r2, #0x0]
	mov r3, r1, lsr #0x10
	ldr r2, _020D792C ; =0x040001AE
	strb r3, [r0, #0x0]
	mov r3, r1, lsr #0x8
	ldr r0, _020D7930 ; =0x040001AF
	strb r3, [r2, #0x0]
	strb r1, [r0, #0x0]
	bx lr
	.balign 4
_020D790C: .word 0x040001A4
_020D7910: .word 0x040001A1
_020D7914: .word 0x040001A8
_020D7918: .word 0x040001A9
_020D791C: .word 0x040001AA
_020D7920: .word 0x040001AB
_020D7924: .word 0x040001AC
_020D7928: .word 0x040001AD
_020D792C: .word 0x040001AE
_020D7930: .word 0x040001AF

	arm_func_start CARDi_ReadFromCache
CARDi_ReadFromCache:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r5, _020D79C8 ; =cardi_common
	mov r1, #0x200
	ldr r3, [r5, #0x1c]
	rsb r1, r1, #0x0
	ldr r2, [r0, #0x8]
	and r3, r3, r1
	cmp r3, r2
	bne _020D79AC
	ldr r2, [r5, #0x1c]
	ldr r1, [r5, #0x24]
	sub r3, r2, r3
	rsb r4, r3, #0x200
	cmp r4, r1
	movhi r4, r1
	add r0, r0, #0x20
	ldr r1, [r5, #0x20]
	mov r2, r4
	add r0, r0, r3
	bl MI_CpuCopy8
	ldr r0, [r5, #0x1c]
	add r0, r0, r4
	str r0, [r5, #0x1c]
	ldr r0, [r5, #0x20]
	add r0, r0, r4
	str r0, [r5, #0x20]
	ldr r0, [r5, #0x24]
	sub r0, r0, r4
	str r0, [r5, #0x24]
_020D79AC:
	ldr r0, [r5, #0x24]
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D79C8: .word cardi_common
