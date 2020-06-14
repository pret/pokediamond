    .include "asm/macros.inc"
    .include "global.inc"
    .include "constants/species.h"

	.extern gGameVersion
	.extern sItemOdds
    .extern sLegendaryMonsList
    .extern UNK_020F7F16

	.text

	thumb_func_start FUN_02069818
FUN_02069818: ; 0x02069818
	push {r3-r7, lr}
	sub sp, #0x10
	add r7, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0x0
	mov r1, #0x2c
	str r2, [sp, #0x0]
	str r0, [sp, #0x8]
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r7, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	add r0, r7, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0xc]
	add r0, r7, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0xc]
	add r2, r4, #0x0
	bl LoadWotbl_HandleAlternateForme
	ldr r0, [r5, #0x0]
	lsl r0, r0, #0x1
	ldrh r2, [r4, r0]
	ldr r0, _020698D8 ; =0x0000FFFF
	cmp r2, r0
	bne _0206987A
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0206987A:
	mov r0, #0xfe
	lsl r0, r0, #0x8
	add r3, r2, #0x0
	and r3, r0
	lsl r6, r6, #0x9
	cmp r6, r3
	beq _020698AC
	ldr r1, _020698D8 ; =0x0000FFFF
_0206988A:
	ldr r2, [r5, #0x0]
	add r2, r2, #0x1
	str r2, [r5, #0x0]
	lsl r2, r2, #0x1
	ldrh r2, [r4, r2]
	cmp r2, r1
	bne _020698A4
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_020698A4:
	add r3, r2, #0x0
	and r3, r0
	cmp r6, r3
	bne _0206988A
_020698AC:
	cmp r6, r3
	bne _020698CC
	ldr r0, _020698DC ; =0x000001FF
	add r1, r2, #0x0
	and r1, r0
	ldr r0, [sp, #0x0]
	strh r1, [r0, #0x0]
	ldr r0, [r5, #0x0]
	ldr r1, [sp, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	ldrh r1, [r1, #0x0]
	add r0, r7, #0x0
	bl FUN_02069698
	str r0, [sp, #0x8]
_020698CC:
	add r0, r4, #0x0
	bl FreeToHeap
	ldr r0, [sp, #0x8]
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_020698D8: .word 0x0000FFFF
_020698DC: .word 0x000001FF

	thumb_func_start FUN_020698E0
FUN_020698E0: ; 0x020698E0
	ldr r3, _020698E4 ; =FUN_020698E8
	bx r3
	.balign 4
_020698E4: .word FUN_020698E8

	thumb_func_start FUN_020698E8
FUN_020698E8: ; 0x020698E8
	push {r4-r6, lr}
	sub sp, #0x8
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r1, #0x36
	mov r2, #0x0
	add r5, r0, #0x0
	bl GetBoxMonData
	add r1, sp, #0x0
	strh r0, [r1, #0x4]
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x3a
	mov r2, #0x0
	bl GetBoxMonData
	add r1, sp, #0x0
	strb r0, [r1, #0x2]
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x3e
	mov r2, #0x0
	bl GetBoxMonData
	add r1, sp, #0x0
	strb r0, [r1, #0x0]
	add r1, r6, #0x0
	add r0, r5, #0x0
	add r1, #0x36
	mov r2, #0x0
	bl GetBoxMonData
	add r1, sp, #0x0
	strh r0, [r1, #0x6]
	add r1, r6, #0x0
	add r0, r5, #0x0
	add r1, #0x3a
	mov r2, #0x0
	bl GetBoxMonData
	add r1, sp, #0x0
	strb r0, [r1, #0x3]
	add r1, r6, #0x0
	add r0, r5, #0x0
	add r1, #0x3e
	mov r2, #0x0
	bl GetBoxMonData
	add r1, sp, #0x0
	strb r0, [r1, #0x1]
	add r1, r4, #0x0
	add r2, sp, #0x4
	add r0, r5, #0x0
	add r1, #0x36
	add r2, #0x2
	bl SetBoxMonData
	add r1, r4, #0x0
	add r2, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x3a
	add r2, #0x3
	bl SetBoxMonData
	add r4, #0x3e
	add r2, sp, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, #0x1
	bl SetBoxMonData
	add r1, r6, #0x0
	add r0, r5, #0x0
	add r1, #0x36
	add r2, sp, #0x4
	bl SetBoxMonData
	add r1, r6, #0x0
	add r2, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x3a
	add r2, #0x2
	bl SetBoxMonData
	add r6, #0x3e
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, sp, #0x0
	bl SetBoxMonData
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020699A4
FUN_020699A4: ; 0x020699A4
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x3
	bhs _02069A0A
	mov r7, #0x0
	add r6, sp, #0x0
_020699B2:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x37
	add r2, r7, #0x0
	bl GetMonData
	add r1, r4, #0x0
	strh r0, [r6, #0x2]
	add r0, r5, #0x0
	add r1, #0x3b
	mov r2, #0x0
	bl GetMonData
	add r1, r4, #0x0
	strb r0, [r6, #0x1]
	add r0, r5, #0x0
	add r1, #0x3f
	mov r2, #0x0
	bl GetMonData
	add r1, r4, #0x0
	add r2, sp, #0x0
	strb r0, [r6, #0x0]
	add r0, r5, #0x0
	add r1, #0x36
	add r2, #0x2
	bl SetMonData
	add r1, r4, #0x0
	add r2, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x3a
	add r2, #0x1
	bl SetMonData
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x3e
	add r2, sp, #0x0
	bl SetMonData
	add r4, r4, #0x1
	cmp r4, #0x3
	blo _020699B2
_02069A0A:
	mov r1, #0x0
	add r0, sp, #0x0
	strh r1, [r0, #0x2]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x0]
	add r2, sp, #0x0
	add r0, r5, #0x0
	mov r1, #0x39
	add r2, #0x2
	bl SetMonData
	add r2, sp, #0x0
	add r0, r5, #0x0
	mov r1, #0x3d
	add r2, #0x1
	bl SetMonData
	add r0, r5, #0x0
	mov r1, #0x41
	add r2, sp, #0x0
	bl SetMonData
	pop {r3-r7, pc}

	thumb_func_start MonHasMove
MonHasMove: ; 0x02069A38
	push {r3-r7, lr}
	mov r4, #0x0
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r7, r4, #0x0
_02069A42:
	add r1, r4, #0x0
	add r0, r6, #0x0
	add r1, #0x36
	add r2, r7, #0x0
	bl GetMonData
	cmp r5, r0
	beq _02069A58
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _02069A42
_02069A58:
	cmp r4, #0x4
	beq _02069A60
	mov r0, #0x1
	pop {r3-r7, pc}
_02069A60:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02069A64
FUN_02069A64: ; 0x02069A64
	push {r4-r5, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r3, r4, #0x0
	mov r2, #0x11
_02069A74:
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02069A74
	ldrh r1, [r4, #0x4]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1f
	beq _02069A8E
	mov r0, #0x1
	bic r1, r0
	mov r0, #0x1
	orr r0, r1
	strh r0, [r4, #0x4]
_02069A8E:
	add r0, r4, #0x0
	mov r1, #0x9f
	add r2, sp, #0x0
	bl SetMonData
	add r0, r4, #0x0
	mov r1, #0xa2
	add r2, sp, #0x0
	bl SetMonData
	add r0, r4, #0x0
	mov r1, #0xa3
	add r2, sp, #0x0
	bl SetMonData
	mov r0, #0x0
	bl CreateNewSealsObject
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0xa9
	add r2, r5, #0x0
	bl SetMonData
	add r0, r5, #0x0
	bl FreeToHeap
	add r0, r4, #0x0
	mov r1, #0xa1
	add r2, sp, #0x0
	bl SetMonData
	mov r0, #0x0
	add r1, sp, #0x4
	mov r2, #0x18
	bl MIi_CpuClearFast
	add r0, r4, #0x0
	mov r1, #0xaa
	add r2, sp, #0x4
	bl SetMonData
	add r0, r4, #0x0
	bl CalcMonLevelAndStats
	add sp, #0x1c
	pop {r4-r5, pc}

	thumb_func_start FUN_02069AEC
FUN_02069AEC: ; 0x02069AEC
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	bl FUN_0206B9AC
	add r7, r0, #0x0
	mov r6, #0x1
	mov r5, #0x0
	cmp r7, #0x0
	ble _02069B3C
_02069AFE:
	ldr r0, [sp, #0x0]
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02069B36
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _02069B36
	add r0, r4, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, r6
	bls _02069B36
	add r6, r0, #0x0
_02069B36:
	add r5, r5, #0x1
	cmp r5, r7
	blt _02069AFE
_02069B3C:
	add r0, r6, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02069B40
FUN_02069B40: ; 0x02069B40
	push {r3, lr}
	sub sp, #0x8
	add r3, r0, #0x0
	mov r0, #0x2
	str r0, [sp, #0x0]
	add r0, sp, #0x4
	mov r1, #0x6d ; NARC_POKETOOL_POKEZUKAN
	mov r2, #0x0
	lsl r3, r3, #0x1
	bl ReadFromNarcMemberByIdPair
	add r0, sp, #0x4
	ldrh r0, [r0, #0x0]
	add sp, #0x8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02069B60
FUN_02069B60: ; 0x02069B60
	push {r3, lr}
	sub sp, #0x8
	add r3, r0, #0x0
	mov r2, #0x0
	add r0, sp, #0x4
	strh r2, [r0, #0x0]
	cmp r3, #0x97
	bhi _02069B7E
	mov r0, #0x2
	str r0, [sp, #0x0]
	add r0, sp, #0x4
	mov r1, #0x91 ; NARC_POKETOOL_SHINZUKAN
	lsl r3, r3, #0x1
	bl ReadFromNarcMemberByIdPair
_02069B7E:
	add r0, sp, #0x4
	ldrh r0, [r0, #0x0]
	add sp, #0x8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02069B88
FUN_02069B88: ; 0x02069B88
	push {r3-r4}
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r2, #0x1d
_02069B90:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02069B90
	ldr r0, [r4, #0x0]
	str r0, [r3, #0x0]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02069BA0
FUN_02069BA0: ; 0x02069BA0
	push {r3-r4}
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r2, #0x11
_02069BA8:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02069BA8
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02069BB4
FUN_02069BB4: ; 0x02069BB4
	push {r3-r4}
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r2, #0x11
_02069BBC:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02069BBC
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02069BC8
FUN_02069BC8: ; 0x02069BC8
	ldr r3, _02069BCC ; =FUN_02069BD0
	bx r3
	.balign 4
_02069BCC: .word FUN_02069BD0

	thumb_func_start FUN_02069BD0
FUN_02069BD0: ; 0x02069BD0
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x0
	add r2, r1, #0x0
	bl GetBoxMonData
	add r1, r4, #0x0
	bl FUN_02069BE4
	pop {r4, pc}

	thumb_func_start FUN_02069BE4
FUN_02069BE4: ; 0x02069BE4
	push {r4, lr}
	add r4, r1, #0x0
	bl GetNatureFromPersonality
	lsl r1, r0, #0x2
	add r1, r0, r1
	ldr r0, _02069BF8 ; =UNK_020F7F16
	add r0, r0, r1
	ldrsb r0, [r4, r0]
	pop {r4, pc}
	.balign 4
_02069BF8: .word UNK_020F7F16

	thumb_func_start FUN_02069BFC
FUN_02069BFC: ; 0x02069BFC
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r7, r1, #0x0
	mov r0, #0x0
	mov r1, #0x2c
	add r5, r2, #0x0
	bl AllocFromHeap
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl LoadWotbl_HandleAlternateForme
	ldrh r1, [r6, #0x0]
	ldr r0, _02069C44 ; =0x0000FFFF
	mov r4, #0x0
	cmp r1, r0
	beq _02069C3A
	ldr r1, _02069C48 ; =0x000001FF
	ldr r2, _02069C44 ; =0x0000FFFF
	add r0, r6, #0x0
_02069C28:
	ldrh r3, [r0, #0x0]
	add r0, r0, #0x2
	add r4, r4, #0x1
	and r3, r1
	strh r3, [r5, #0x0]
	ldrh r3, [r0, #0x0]
	add r5, r5, #0x2
	cmp r3, r2
	bne _02069C28
_02069C3A:
	add r0, r6, #0x0
	bl FreeToHeap
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4
_02069C44: .word 0x0000FFFF
_02069C48: .word 0x000001FF

	thumb_func_start FUN_02069C4C
FUN_02069C4C: ; 0x02069C4C
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_0206B9AC
	add r6, r0, #0x0
	bl rand_LC
	mov r1, #0x1
	lsl r1, r1, #0xe
	cmp r0, r1
	beq _02069C70
	lsl r1, r1, #0x1
	cmp r0, r1
	beq _02069C70
	mov r1, #0x3
	lsl r1, r1, #0xe
	cmp r0, r1
	bne _02069CF2
_02069C70:
	bl rand_LC
	add r1, r6, #0x0
	bl _s32_div_f
	add r0, r5, #0x0
	add r7, r1, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02069C70
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _02069C70
	add r0, r7, #0x0
	bl MaskOfFlagNo
	add r1, r0, #0x0
	lsl r1, r1, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_02069CF4
	cmp r0, #0x0
	bne _02069CF2
	add r5, sp, #0x0
	mov r6, #0x7
_02069CB8:
	bl rand_LC
	strb r0, [r5, #0x0]
	ldrb r2, [r5, #0x0]
	add r1, r2, #0x0
	and r1, r6
	beq _02069CB8
	mov r0, #0xf0
	tst r0, r2
	beq _02069CD0
	add r0, sp, #0x0
	strb r1, [r0, #0x0]
_02069CD0:
	add r1, sp, #0x0
	ldrb r2, [r1, #0x0]
	lsl r0, r2, #0x4
	orr r0, r2
	strb r0, [r1, #0x0]
	ldrb r2, [r1, #0x0]
	mov r0, #0xf3
	and r0, r2
	strb r0, [r1, #0x0]
	ldrb r0, [r1, #0x0]
	add r2, sp, #0x0
	add r0, r0, #0x1
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	mov r1, #0x99
	bl SetMonData
_02069CF2:
	pop {r3-r7, pc}

	thumb_func_start FUN_02069CF4
FUN_02069CF4: ; 0x02069CF4
	push {r3-r7, lr}
	mov r6, #0x0
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	mov r4, #0x1
	add r7, r6, #0x0
	cmp r5, #0x0
	beq _02069D32
_02069D04:
	mov r0, #0x1
	tst r0, r5
	beq _02069D26
	ldr r0, [sp, #0x0]
	add r1, r6, #0x0
	bl FUN_0206B9B0
	mov r1, #0x99
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02069D26
	add r0, r7, #0x0
	orr r0, r4
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
_02069D26:
	lsl r0, r5, #0x17
	add r6, r6, #0x1
	lsl r4, r4, #0x1
	lsr r5, r0, #0x18
	bne _02069D04
	b _02069D4A
_02069D32:
	add r1, r6, #0x0
	bl FUN_0206B9B0
	mov r1, #0x99
	add r2, r6, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02069D4A
	add r0, r7, #0x1
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
_02069D4A:
	add r0, r7, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02069D50
FUN_02069D50: ; 0x02069D50
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	add r5, r1, #0x0
	bl FUN_0206B9AC
	mov r6, #0x0
	str r0, [sp, #0x4]
	cmp r0, #0x0
	ble _02069DC2
	add r4, sp, #0x8
_02069D66:
	ldr r0, [sp, #0x0]
	add r1, r6, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	add r7, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02069DBA
	add r0, r7, #0x0
	mov r1, #0x99
	mov r2, #0x0
	bl GetMonData
	strb r0, [r4, #0x0]
	ldrb r1, [r4, #0x0]
	mov r0, #0xf
	and r0, r1
	beq _02069DBA
	cmp r0, r5
	blt _02069D98
	cmp r5, #0x4
	ble _02069DA2
_02069D98:
	ldrb r1, [r4, #0x0]
	mov r0, #0xf0
	and r0, r1
	strb r0, [r4, #0x0]
	b _02069DA6
_02069DA2:
	sub r0, r1, r5
	strb r0, [r4, #0x0]
_02069DA6:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02069DB0
	mov r0, #0x10
	strb r0, [r4, #0x0]
_02069DB0:
	add r0, r7, #0x0
	mov r1, #0x99
	add r2, sp, #0x8
	bl SetMonData
_02069DBA:
	ldr r0, [sp, #0x4]
	add r6, r6, #0x1
	cmp r6, r0
	blt _02069D66
_02069DC2:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02069DC8
FUN_02069DC8: ; 0x02069DC8
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl FUN_0206B9AC
	add r7, r0, #0x0
	bl rand_LC
	mov r1, #0x3
	bl _s32_div_f
	cmp r1, #0x0
	bne _02069E70
	mov r4, #0x0
	cmp r7, #0x0
	ble _02069E70
	sub r0, r7, #0x1
	str r0, [sp, #0x0]
_02069DEC:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	add r6, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02069E6A
	add r0, r6, #0x0
	mov r1, #0x99
	mov r2, #0x0
	bl GetMonData
	add r1, sp, #0x4
	strb r0, [r1, #0x0]
	add r0, r1, #0x0
	ldrb r1, [r0, #0x0]
	mov r0, #0xf
	tst r0, r1
	beq _02069E6A
	cmp r4, #0x0
	beq _02069E40
	add r0, r5, #0x0
	sub r1, r4, #0x1
	bl FUN_0206B9B0
	mov r1, #0x99
	mov r2, #0x0
	add r6, r0, #0x0
	bl GetMonData
	mov r1, #0xf0
	tst r0, r1
	bne _02069E40
	add r0, r6, #0x0
	mov r1, #0x99
	add r2, sp, #0x4
	bl SetMonData
_02069E40:
	ldr r0, [sp, #0x0]
	cmp r4, r0
	bge _02069E6A
	add r0, r5, #0x0
	add r1, r4, #0x1
	bl FUN_0206B9B0
	mov r1, #0x99
	mov r2, #0x0
	add r6, r0, #0x0
	bl GetMonData
	mov r1, #0xf0
	tst r0, r1
	bne _02069E6A
	add r0, r6, #0x0
	mov r1, #0x99
	add r2, sp, #0x4
	bl SetMonData
	add r4, r4, #0x1
_02069E6A:
	add r4, r4, #0x1
	cmp r4, r7
	blt _02069DEC
_02069E70:
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02069E74
FUN_02069E74: ; 0x02069E74
	ldr r3, _02069E78 ; =FUN_02069E7C
	bx r3
	.balign 4
_02069E78: .word FUN_02069E7C

	thumb_func_start FUN_02069E7C
FUN_02069E7C: ; 0x02069E7C
	push {r3, lr}
	mov r1, #0x99
	mov r2, #0x0
	bl GetBoxMonData
	mov r1, #0xf
	tst r0, r1
	beq _02069E90
	mov r0, #0x1
	pop {r3, pc}
_02069E90:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02069E94
FUN_02069E94: ; 0x02069E94
	ldr r3, _02069E98 ; =FUN_02069E9C
	bx r3
	.balign 4
_02069E98: .word FUN_02069E9C

	thumb_func_start FUN_02069E9C
FUN_02069E9C: ; 0x02069E9C
	push {r3, lr}
	mov r1, #0x99
	mov r2, #0x0
	bl GetBoxMonData
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r0, #0xf
	tst r0, r1
	beq _02069EB4
	mov r0, #0x0
	pop {r3, pc}
_02069EB4:
	mov r0, #0xf0
	tst r0, r1
	beq _02069EBE
	mov r0, #0x1
	pop {r3, pc}
_02069EBE:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02069EC4
FUN_02069EC4: ; 0x02069EC4
	ldr r3, _02069EC8 ; =FUN_02069ECC
	bx r3
	.balign 4
_02069EC8: .word FUN_02069ECC

	thumb_func_start FUN_02069ECC
FUN_02069ECC: ; 0x02069ECC
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetBoxMonData
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xa
	mov r2, #0x0
	bl GetBoxMonData
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x6
	mov r2, #0x0
	bl GetBoxMonData
	ldr r1, _02069F20 ; =SPECIES_ARCEUS
	cmp r4, r1
	bne _02069F1C
	cmp r6, #0x79
	bne _02069F1C
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_0206E7B8
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl GetArceusTypeByPlate
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r1, #0x70
	add r2, sp, #0x0
	bl SetBoxMonData
_02069F1C:
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_02069F20: .word SPECIES_ARCEUS

	thumb_func_start GetArceusTypeByPlate
GetArceusTypeByPlate: ; 0x02069F24
	sub r0, #0x7d
	cmp r0, #0xf
	bhi _02069F96
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02069F36: ; jump table (using 16-bit offset)
	.short _02069F56 - _02069F36 - 2; case 0
	.short _02069F5A - _02069F36 - 2; case 1
	.short _02069F5E - _02069F36 - 2; case 2
	.short _02069F62 - _02069F36 - 2; case 3
	.short _02069F66 - _02069F36 - 2; case 4
	.short _02069F6A - _02069F36 - 2; case 5
	.short _02069F6E - _02069F36 - 2; case 6
	.short _02069F72 - _02069F36 - 2; case 7
	.short _02069F76 - _02069F36 - 2; case 8
	.short _02069F7A - _02069F36 - 2; case 9
	.short _02069F7E - _02069F36 - 2; case 10
	.short _02069F82 - _02069F36 - 2; case 11
	.short _02069F86 - _02069F36 - 2; case 12
	.short _02069F8A - _02069F36 - 2; case 13
	.short _02069F8E - _02069F36 - 2; case 14
	.short _02069F92 - _02069F36 - 2; case 15
_02069F56:
	mov r0, #0xa
	bx lr
_02069F5A:
	mov r0, #0xb
	bx lr
_02069F5E:
	mov r0, #0xd
	bx lr
_02069F62:
	mov r0, #0xc
	bx lr
_02069F66:
	mov r0, #0xf
	bx lr
_02069F6A:
	mov r0, #0x1
	bx lr
_02069F6E:
	mov r0, #0x3
	bx lr
_02069F72:
	mov r0, #0x4
	bx lr
_02069F76:
	mov r0, #0x2
	bx lr
_02069F7A:
	mov r0, #0xe
	bx lr
_02069F7E:
	mov r0, #0x6
	bx lr
_02069F82:
	mov r0, #0x5
	bx lr
_02069F86:
	mov r0, #0x7
	bx lr
_02069F8A:
	mov r0, #0x10
	bx lr
_02069F8E:
	mov r0, #0x11
	bx lr
_02069F92:
	mov r0, #0x8
	bx lr
_02069F96:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start LoadWotbl_HandleAlternateForme
LoadWotbl_HandleAlternateForme: ; 0x02069F9C
	push {r4, lr}
	add r4, r2, #0x0
	bl ResolveMonForme
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x21 ; NARC_POKETOOL_PERSONAL_WOTBL
	bl ReadWholeNarcMemberByIdPair
	pop {r4, pc}

	thumb_func_start FUN_02069FB0
FUN_02069FB0: ; 0x02069FB0
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, _0206A010 ; =0x000001B9
	add r4, r2, #0x0
	add r5, r1, #0x0
	add r6, r3, #0x0
	cmp r4, r0
	bne _02069FFC
	add r0, r5, #0x0
	bl FUN_02005F14
	cmp r0, #0x0
	bne _02069FE2
	mov r0, #0x1
	bl FUN_02005E80
	ldr r0, [sp, #0x20]
	ldr r3, [sp, #0x18]
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020056AC
	pop {r3-r7, pc}
_02069FE2:
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	beq _02069FEE
	mov r0, #0x1
	bl FUN_02005E80
_02069FEE:
	ldr r2, [sp, #0x18]
	add r0, r7, #0x0
	mov r1, #0x0
	add r3, r6, #0x0
	bl FUN_02005E90
	pop {r3-r7, pc}
_02069FFC:
	ldr r0, [sp, #0x20]
	ldr r3, [sp, #0x18]
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020056AC
	pop {r3-r7, pc}
	nop
_0206A010: .word 0x000001B9

	thumb_func_start FUN_0206A014
FUN_0206A014: ; 0x0206A014
	push {r3-r6, lr}
	sub sp, #0xc
	ldr r6, [sp, #0x20]
	add r5, r0, #0x0
	str r6, [sp, #0x0]
	ldr r6, [sp, #0x24]
	add r4, r2, #0x0
	str r6, [sp, #0x4]
	bl FUN_0206A054
	cmp r4, #0xe
	bne _0206A050
	add r0, r5, #0x0
	mov r1, #0xa3
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0xa2
	add r2, sp, #0x8
	bl SetMonData
	mov r0, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x9f
	add r2, sp, #0x8
	bl SetMonData
_0206A050:
	add sp, #0xc
	pop {r3-r6, pc}

	thumb_func_start FUN_0206A054
FUN_0206A054: ; 0x0206A054
	push {r0-r3}
	push {r3-r4, lr}
	sub sp, #0x4
	ldr r2, [sp, #0x24]
	add r4, r0, #0x0
	str r2, [sp, #0x0]
	mov r2, #0x0
	bl FUN_020808AC
	ldr r2, _0206A090 ; =gGameVersion
	add r0, r4, #0x0
	mov r1, #0x79
	bl SetBoxMonData
	add r0, r4, #0x0
	mov r1, #0x9a
	add r2, sp, #0x18
	bl SetBoxMonData
	add r0, r4, #0x0
	mov r1, #0x9d
	add r2, sp, #0x20
	bl SetBoxMonData
	add sp, #0x4
	pop {r3-r4}
	pop {r3}
	add sp, #0x10
	bx r3
	nop
_0206A090: .word gGameVersion

	thumb_func_start FUN_0206A094
FUN_0206A094: ; 0x0206A094
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	mov r0, #0x81
	add r7, r2, #0x0
	tst r0, r1
	bne _0206A12E
	bl rand_LC
	mov r1, #0x64
	bl _s32_div_f
	add r4, r1, #0x0
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r0, r5, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	mov r2, #0x10
	bl GetMonBaseStat_HandleFormeConversion
	add r1, sp, #0x4
	strh r0, [r1, #0x2]
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	mov r2, #0x11
	bl GetMonBaseStat_HandleFormeConversion
	add r1, sp, #0x4
	strh r0, [r1, #0x0]
	ldrh r2, [r1, #0x2]
	ldrh r0, [r1, #0x0]
	cmp r2, r0
	bne _0206A104
	cmp r2, #0x0
	beq _0206A104
	add r2, sp, #0x4
	add r0, r5, #0x0
	mov r1, #0x6
	add r2, #0x2
	bl SetMonData
	add sp, #0x8
	pop {r3-r7, pc}
_0206A104:
	ldr r0, _0206A134 ; =sItemOdds
	lsl r1, r7, #0x2
	ldrh r0, [r0, r1]
	cmp r4, r0
	blo _0206A12E
	ldr r0, _0206A138 ; =sItemOdds + 2
	ldrh r0, [r0, r1]
	cmp r4, r0
	add r2, sp, #0x4
	bhs _0206A126
	add r0, r5, #0x0
	mov r1, #0x6
	add r2, #0x2
	bl SetMonData
	add sp, #0x8
	pop {r3-r7, pc}
_0206A126:
	add r0, r5, #0x0
	mov r1, #0x6
	bl SetMonData
_0206A12E:
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0206A134: .word sItemOdds
_0206A138: .word sItemOdds + 2

	thumb_func_start FUN_0206A13C
FUN_0206A13C: ; 0x0206A13C
	ldr r3, _0206A140 ; =FUN_0206A144
	bx r3
	.balign 4
_0206A140: .word FUN_0206A144

	thumb_func_start FUN_0206A144
FUN_0206A144: ; 0x0206A144
	push {r4-r6, lr}
	add r6, r1, #0x0
	mov r1, #0xad
	mov r2, #0x0
	add r5, r0, #0x0
	bl GetBoxMonData
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r5, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl GetBoxMonData
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0206A16C
	pop {r4-r6, pc}

	thumb_func_start FUN_0206A16C
FUN_0206A16C: ; 0x0206A16C
	push {r4, lr}
	ldr r3, _0206A1C0 ; =SPECIES_EGG
	cmp r0, r3
	bne _0206A178
	mov r0, #0x0
	pop {r4, pc}
_0206A178:
	cmp r2, #0x20
	bhs _0206A186
	mov r3, #0x1
	add r4, r3, #0x0
	lsl r4, r2
	mov r2, #0x1d
	b _0206A1B0
_0206A186:
	cmp r2, #0x40
	bhs _0206A196
	mov r3, #0x1
	sub r2, #0x20
	add r4, r3, #0x0
	lsl r4, r2
	mov r2, #0x1e
	b _0206A1B0
_0206A196:
	cmp r2, #0x60
	bhs _0206A1A6
	mov r3, #0x1
	sub r2, #0x40
	add r4, r3, #0x0
	lsl r4, r2
	mov r2, #0x1f
	b _0206A1B0
_0206A1A6:
	mov r3, #0x1
	sub r2, #0x60
	add r4, r3, #0x0
	lsl r4, r2
	mov r2, #0x20
_0206A1B0:
	bl GetMonBaseStat_HandleFormeConversion
	tst r0, r4
	beq _0206A1BC
	mov r0, #0x1
	pop {r4, pc}
_0206A1BC:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_0206A1C0: .word SPECIES_EGG

	thumb_func_start FUN_0206A1C4
FUN_0206A1C4: ; 0x0206A1C4
	ldr r3, _0206A1C8 ; =FUN_0206A1CC
	bx r3
	.balign 4
_0206A1C8: .word FUN_0206A1CC

	thumb_func_start FUN_0206A1CC
FUN_0206A1CC: ; 0x0206A1CC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl AcquireBoxMonLock
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetBoxMonData
	mov r1, #0x0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl GetBoxMonData
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x18
	bl GetMonBaseStat
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0x19
	bl GetMonBaseStat
	str r0, [sp, #0x0]
	cmp r0, #0x0
	beq _0206A226
	mov r0, #0x1
	tst r0, r6
	beq _0206A21A
	add r0, r5, #0x0
	mov r1, #0xa
	add r2, sp, #0x0
	bl SetBoxMonData
	b _0206A230
_0206A21A:
	add r0, r5, #0x0
	mov r1, #0xa
	add r2, sp, #0x4
	bl SetBoxMonData
	b _0206A230
_0206A226:
	add r0, r5, #0x0
	mov r1, #0xa
	add r2, sp, #0x4
	bl SetBoxMonData
_0206A230:
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl ReleaseBoxMonLock
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_0206A23C
FUN_0206A23C: ; 0x0206A23C
	push {r4-r7, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	mov r0, #0x0
	str r1, [sp, #0x0]
	bl AllocMonZeroed
	str r0, [sp, #0x4]
	ldr r1, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02069B88
	ldr r0, [sp, #0x4]
	ldr r1, [r5, #0x0]
	mov r2, #0x0
	bl GetSubstruct
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	ldr r1, [r5, #0x0]
	mov r2, #0x1
	bl GetSubstruct
	add r6, r0, #0x0
	ldr r0, [sp, #0x4]
	ldr r1, [r5, #0x0]
	mov r2, #0x2
	bl GetSubstruct
	add r7, r0, #0x0
	ldr r0, [sp, #0x4]
	ldr r1, [r5, #0x0]
	mov r2, #0x3
	bl GetSubstruct
	str r0, [sp, #0x8]
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	mov r2, #0x0
	bl GetSubstruct
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	mov r2, #0x1
	bl GetSubstruct
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	mov r2, #0x2
	bl GetSubstruct
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	mov r2, #0x3
	bl GetSubstruct
	ldr r2, [sp, #0x4]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x4]
	ldrh r2, [r2, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl MonDecryptSegment
	add r0, r5, #0x0
	ldr r2, [r5, #0x0]
	add r0, #0x88
	mov r1, #0x64
	bl MonDecryptSegment
	add r0, r5, #0x0
	ldrh r2, [r5, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl MonDecryptSegment
	ldr r0, [sp, #0x0]
	str r0, [r5, #0x0]
	ldr r2, [sp, #0xc]
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0xc]
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0xc]
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0xc]
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0xc]
	ldr r2, [sp, #0x10]
	ldmia r6!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0x10]
	ldmia r6!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0x10]
	ldmia r6!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0x10]
	ldmia r6!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0x10]
	ldr r2, [sp, #0x14]
	ldmia r7!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0x14]
	ldmia r7!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0x14]
	ldmia r7!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0x14]
	ldmia r7!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0x14]
	mov r0, #0x10
_0206A32E:
	ldr r1, [sp, #0x8]
	ldrh r2, [r1, #0x0]
	add r1, r1, #0x2
	str r1, [sp, #0x8]
	ldr r1, [sp, #0x18]
	strh r2, [r1, #0x0]
	add r1, r1, #0x2
	str r1, [sp, #0x18]
	sub r0, r0, #0x1
	bne _0206A32E
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl CalcMonChecksum
	strh r0, [r5, #0x6]
	add r0, r5, #0x0
	ldrh r2, [r5, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl MonEncryptSegment
	add r0, r5, #0x0
	ldr r2, [r5, #0x0]
	add r0, #0x88
	mov r1, #0x64
	bl MonEncryptSegment
	ldr r0, [sp, #0x4]
	bl FreeToHeap
	add sp, #0x1c
	pop {r4-r7, pc}

	thumb_func_start LoadMonPersonal
LoadMonPersonal: ; 0x0206A370
	ldr r3, _0206A37C ; =ReadWholeNarcMemberByIdPair
	add r2, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x2 ; NARC_POKETOOL_PERSONAL_PERSONAL
	bx r3
	nop
_0206A37C: .word ReadWholeNarcMemberByIdPair

	thumb_func_start LoadMonBaseStats_HandleAlternateForme
LoadMonBaseStats_HandleAlternateForme: ; 0x0206A380
	push {r4, lr}
	add r4, r2, #0x0
	bl ResolveMonForme
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x2 ; NARC_POKETOOL_PERSONAL_PERSONAL
	bl ReadWholeNarcMemberByIdPair
	pop {r4, pc}

	thumb_func_start LoadMonEvolutionTable
LoadMonEvolutionTable: ; 0x0206A394
	ldr r3, _0206A3A0 ; =ReadWholeNarcMemberByIdPair
	add r2, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x22 ; NARC_POKETOOL_PERSONAL_EVO
	bx r3
	nop
_0206A3A0: .word ReadWholeNarcMemberByIdPair

	thumb_func_start MonEncryptSegment
MonEncryptSegment: ; 0x0206A3A4
	push {r0-r3}
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r4, #0x0
	lsr r6, r1, #0x1
	beq _0206A3C6
	add r7, sp, #0x20
_0206A3B2:
	add r0, r7, #0x0
	bl MonEncryptionLCRNG
	ldrh r1, [r5, #0x0]
	add r4, r4, #0x1
	eor r0, r1
	strh r0, [r5, #0x0]
	add r5, r5, #0x2
	cmp r4, r6
	blo _0206A3B2
_0206A3C6:
	pop {r3-r7}
	pop {r3}
	add sp, #0x10
	bx r3
	.balign 4

	thumb_func_start MonDecryptSegment
MonDecryptSegment: ; 0x0206A3D0
	ldr r3, _0206A3D4 ; =MonEncryptSegment
	bx r3
	.balign 4
_0206A3D4: .word MonEncryptSegment

	thumb_func_start MonEncryptionLCRNG
MonEncryptionLCRNG: ; 0x0206A3D8
	ldr r2, [r0, #0x0]
	ldr r1, _0206A3F0 ; =0x41C64E6D
	add r3, r2, #0x0
	mul r3, r1
	ldr r1, _0206A3F4 ; =0x00006073
	add r1, r3, r1
	str r1, [r0, #0x0]
	lsr r0, r1, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr
	nop
_0206A3F0: .word 0x41C64E6D
_0206A3F4: .word 0x00006073

	thumb_func_start CalcMonChecksum
CalcMonChecksum: ; 0x0206A3F8
	push {r3-r4}
	mov r3, #0x0
	add r2, r3, #0x0
	lsr r4, r1, #0x1
	beq _0206A412
_0206A402:
	ldrh r1, [r0, #0x0]
	add r2, r2, #0x1
	add r0, r0, #0x2
	add r1, r3, r1
	lsl r1, r1, #0x10
	lsr r3, r1, #0x10
	cmp r2, r4
	blo _0206A402
_0206A412:
	add r0, r3, #0x0
	pop {r3-r4}
	bx lr

	thumb_func_start GetSubstruct
GetSubstruct: ; 0x0206A418
	push {r3, lr}
	mov r3, #0x3e
	lsl r3, r3, #0xc
	and r3, r1
	lsr r3, r3, #0xd
	cmp r3, #0x1f
	bhi _0206A478
	add r3, r3, r3
	add r3, pc
	ldrh r3, [r3, #0x6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_0206A432: ; jump table (using 16-bit offset)
	.short _0206A472 - _0206A432 - 2; case 0
	.short _0206A4A4 - _0206A432 - 2; case 1
	.short _0206A4D4 - _0206A432 - 2; case 2
	.short _0206A504 - _0206A432 - 2; case 3
	.short _0206A534 - _0206A432 - 2; case 4
	.short _0206A564 - _0206A432 - 2; case 5
	.short _0206A594 - _0206A432 - 2; case 6
	.short _0206A5C6 - _0206A432 - 2; case 7
	.short _0206A5F6 - _0206A432 - 2; case 8
	.short _0206A626 - _0206A432 - 2; case 9
	.short _0206A656 - _0206A432 - 2; case 10
	.short _0206A686 - _0206A432 - 2; case 11
	.short _0206A6B6 - _0206A432 - 2; case 12
	.short _0206A6E8 - _0206A432 - 2; case 13
	.short _0206A718 - _0206A432 - 2; case 14
	.short _0206A748 - _0206A432 - 2; case 15
	.short _0206A778 - _0206A432 - 2; case 16
	.short _0206A7A8 - _0206A432 - 2; case 17
	.short _0206A7D8 - _0206A432 - 2; case 18
	.short _0206A80A - _0206A432 - 2; case 19
	.short _0206A83A - _0206A432 - 2; case 20
	.short _0206A86A - _0206A432 - 2; case 21
	.short _0206A89A - _0206A432 - 2; case 22
	.short _0206A8CA - _0206A432 - 2; case 23
	.short _0206A472 - _0206A432 - 2; case 24
	.short _0206A4A4 - _0206A432 - 2; case 25
	.short _0206A4D4 - _0206A432 - 2; case 26
	.short _0206A504 - _0206A432 - 2; case 27
	.short _0206A534 - _0206A432 - 2; case 28
	.short _0206A564 - _0206A432 - 2; case 29
	.short _0206A594 - _0206A432 - 2; case 30
	.short _0206A5C6 - _0206A432 - 2; case 31
_0206A472:
	add r0, #0x8
	cmp r2, #0x3
	bls _0206A47A
_0206A478:
	b _0206A8F8
_0206A47A:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A486: ; jump table (using 16-bit offset)
	.short _0206A48E - _0206A486 - 2; case 0
	.short _0206A492 - _0206A486 - 2; case 1
	.short _0206A498 - _0206A486 - 2; case 2
	.short _0206A49E - _0206A486 - 2; case 3
_0206A48E:
	add r1, r0, #0x0
	b _0206A8F8
_0206A492:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A498:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A49E:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A4A4:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A59A
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A4B6: ; jump table (using 16-bit offset)
	.short _0206A4BE - _0206A4B6 - 2; case 0
	.short _0206A4C2 - _0206A4B6 - 2; case 1
	.short _0206A4C8 - _0206A4B6 - 2; case 2
	.short _0206A4CE - _0206A4B6 - 2; case 3
_0206A4BE:
	add r1, r0, #0x0
	b _0206A8F8
_0206A4C2:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A4C8:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A4CE:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A4D4:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A59A
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A4E6: ; jump table (using 16-bit offset)
	.short _0206A4EE - _0206A4E6 - 2; case 0
	.short _0206A4F2 - _0206A4E6 - 2; case 1
	.short _0206A4F8 - _0206A4E6 - 2; case 2
	.short _0206A4FE - _0206A4E6 - 2; case 3
_0206A4EE:
	add r1, r0, #0x0
	b _0206A8F8
_0206A4F2:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A4F8:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A4FE:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A504:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A59A
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A516: ; jump table (using 16-bit offset)
	.short _0206A51E - _0206A516 - 2; case 0
	.short _0206A522 - _0206A516 - 2; case 1
	.short _0206A528 - _0206A516 - 2; case 2
	.short _0206A52E - _0206A516 - 2; case 3
_0206A51E:
	add r1, r0, #0x0
	b _0206A8F8
_0206A522:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A528:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A52E:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A534:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A59A
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A546: ; jump table (using 16-bit offset)
	.short _0206A54E - _0206A546 - 2; case 0
	.short _0206A552 - _0206A546 - 2; case 1
	.short _0206A558 - _0206A546 - 2; case 2
	.short _0206A55E - _0206A546 - 2; case 3
_0206A54E:
	add r1, r0, #0x0
	b _0206A8F8
_0206A552:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A558:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A55E:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A564:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A59A
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A576: ; jump table (using 16-bit offset)
	.short _0206A57E - _0206A576 - 2; case 0
	.short _0206A582 - _0206A576 - 2; case 1
	.short _0206A588 - _0206A576 - 2; case 2
	.short _0206A58E - _0206A576 - 2; case 3
_0206A57E:
	add r1, r0, #0x0
	b _0206A8F8
_0206A582:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A588:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A58E:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A594:
	add r0, #0x8
	cmp r2, #0x3
	bls _0206A59C
_0206A59A:
	b _0206A8F8
_0206A59C:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A5A8: ; jump table (using 16-bit offset)
	.short _0206A5B0 - _0206A5A8 - 2; case 0
	.short _0206A5B6 - _0206A5A8 - 2; case 1
	.short _0206A5BA - _0206A5A8 - 2; case 2
	.short _0206A5C0 - _0206A5A8 - 2; case 3
_0206A5B0:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A5B6:
	add r1, r0, #0x0
	b _0206A8F8
_0206A5BA:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A5C0:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A5C6:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A6BC
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A5D8: ; jump table (using 16-bit offset)
	.short _0206A5E0 - _0206A5D8 - 2; case 0
	.short _0206A5E6 - _0206A5D8 - 2; case 1
	.short _0206A5EA - _0206A5D8 - 2; case 2
	.short _0206A5F0 - _0206A5D8 - 2; case 3
_0206A5E0:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A5E6:
	add r1, r0, #0x0
	b _0206A8F8
_0206A5EA:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A5F0:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A5F6:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A6BC
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A608: ; jump table (using 16-bit offset)
	.short _0206A610 - _0206A608 - 2; case 0
	.short _0206A616 - _0206A608 - 2; case 1
	.short _0206A61A - _0206A608 - 2; case 2
	.short _0206A620 - _0206A608 - 2; case 3
_0206A610:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A616:
	add r1, r0, #0x0
	b _0206A8F8
_0206A61A:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A620:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A626:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A6BC
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A638: ; jump table (using 16-bit offset)
	.short _0206A640 - _0206A638 - 2; case 0
	.short _0206A646 - _0206A638 - 2; case 1
	.short _0206A64A - _0206A638 - 2; case 2
	.short _0206A650 - _0206A638 - 2; case 3
_0206A640:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A646:
	add r1, r0, #0x0
	b _0206A8F8
_0206A64A:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A650:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A656:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A6BC
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A668: ; jump table (using 16-bit offset)
	.short _0206A670 - _0206A668 - 2; case 0
	.short _0206A676 - _0206A668 - 2; case 1
	.short _0206A67A - _0206A668 - 2; case 2
	.short _0206A680 - _0206A668 - 2; case 3
_0206A670:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A676:
	add r1, r0, #0x0
	b _0206A8F8
_0206A67A:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A680:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A686:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A6BC
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A698: ; jump table (using 16-bit offset)
	.short _0206A6A0 - _0206A698 - 2; case 0
	.short _0206A6A6 - _0206A698 - 2; case 1
	.short _0206A6AA - _0206A698 - 2; case 2
	.short _0206A6B0 - _0206A698 - 2; case 3
_0206A6A0:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A6A6:
	add r1, r0, #0x0
	b _0206A8F8
_0206A6AA:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A6B0:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A6B6:
	add r0, #0x8
	cmp r2, #0x3
	bls _0206A6BE
_0206A6BC:
	b _0206A8F8
_0206A6BE:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A6CA: ; jump table (using 16-bit offset)
	.short _0206A6D2 - _0206A6CA - 2; case 0
	.short _0206A6D8 - _0206A6CA - 2; case 1
	.short _0206A6DE - _0206A6CA - 2; case 2
	.short _0206A6E2 - _0206A6CA - 2; case 3
_0206A6D2:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A6D8:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A6DE:
	add r1, r0, #0x0
	b _0206A8F8
_0206A6E2:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A6E8:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A7DE
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A6FA: ; jump table (using 16-bit offset)
	.short _0206A702 - _0206A6FA - 2; case 0
	.short _0206A708 - _0206A6FA - 2; case 1
	.short _0206A70E - _0206A6FA - 2; case 2
	.short _0206A712 - _0206A6FA - 2; case 3
_0206A702:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A708:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A70E:
	add r1, r0, #0x0
	b _0206A8F8
_0206A712:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A718:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A7DE
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A72A: ; jump table (using 16-bit offset)
	.short _0206A732 - _0206A72A - 2; case 0
	.short _0206A738 - _0206A72A - 2; case 1
	.short _0206A73E - _0206A72A - 2; case 2
	.short _0206A742 - _0206A72A - 2; case 3
_0206A732:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A738:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A73E:
	add r1, r0, #0x0
	b _0206A8F8
_0206A742:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A748:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A7DE
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A75A: ; jump table (using 16-bit offset)
	.short _0206A762 - _0206A75A - 2; case 0
	.short _0206A768 - _0206A75A - 2; case 1
	.short _0206A76E - _0206A75A - 2; case 2
	.short _0206A772 - _0206A75A - 2; case 3
_0206A762:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A768:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A76E:
	add r1, r0, #0x0
	b _0206A8F8
_0206A772:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A778:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A7DE
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A78A: ; jump table (using 16-bit offset)
	.short _0206A792 - _0206A78A - 2; case 0
	.short _0206A798 - _0206A78A - 2; case 1
	.short _0206A79E - _0206A78A - 2; case 2
	.short _0206A7A2 - _0206A78A - 2; case 3
_0206A792:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A798:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A79E:
	add r1, r0, #0x0
	b _0206A8F8
_0206A7A2:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A7A8:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A7DE
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A7BA: ; jump table (using 16-bit offset)
	.short _0206A7C2 - _0206A7BA - 2; case 0
	.short _0206A7C8 - _0206A7BA - 2; case 1
	.short _0206A7CE - _0206A7BA - 2; case 2
	.short _0206A7D2 - _0206A7BA - 2; case 3
_0206A7C2:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A7C8:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A7CE:
	add r1, r0, #0x0
	b _0206A8F8
_0206A7D2:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A7D8:
	add r0, #0x8
	cmp r2, #0x3
	bls _0206A7E0
_0206A7DE:
	b _0206A8F8
_0206A7E0:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A7EC: ; jump table (using 16-bit offset)
	.short _0206A7F4 - _0206A7EC - 2; case 0
	.short _0206A7FA - _0206A7EC - 2; case 1
	.short _0206A800 - _0206A7EC - 2; case 2
	.short _0206A806 - _0206A7EC - 2; case 3
_0206A7F4:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A7FA:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A800:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A806:
	add r1, r0, #0x0
	b _0206A8F8
_0206A80A:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A8F8
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A81C: ; jump table (using 16-bit offset)
	.short _0206A824 - _0206A81C - 2; case 0
	.short _0206A82A - _0206A81C - 2; case 1
	.short _0206A830 - _0206A81C - 2; case 2
	.short _0206A836 - _0206A81C - 2; case 3
_0206A824:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A82A:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A830:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A836:
	add r1, r0, #0x0
	b _0206A8F8
_0206A83A:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A8F8
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A84C: ; jump table (using 16-bit offset)
	.short _0206A854 - _0206A84C - 2; case 0
	.short _0206A85A - _0206A84C - 2; case 1
	.short _0206A860 - _0206A84C - 2; case 2
	.short _0206A866 - _0206A84C - 2; case 3
_0206A854:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A85A:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A860:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A866:
	add r1, r0, #0x0
	b _0206A8F8
_0206A86A:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A8F8
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A87C: ; jump table (using 16-bit offset)
	.short _0206A884 - _0206A87C - 2; case 0
	.short _0206A88A - _0206A87C - 2; case 1
	.short _0206A890 - _0206A87C - 2; case 2
	.short _0206A896 - _0206A87C - 2; case 3
_0206A884:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A88A:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A890:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A896:
	add r1, r0, #0x0
	b _0206A8F8
_0206A89A:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A8F8
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A8AC: ; jump table (using 16-bit offset)
	.short _0206A8B4 - _0206A8AC - 2; case 0
	.short _0206A8BA - _0206A8AC - 2; case 1
	.short _0206A8C0 - _0206A8AC - 2; case 2
	.short _0206A8C6 - _0206A8AC - 2; case 3
_0206A8B4:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A8BA:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A8C0:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A8C6:
	add r1, r0, #0x0
	b _0206A8F8
_0206A8CA:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A8F8
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A8DC: ; jump table (using 16-bit offset)
	.short _0206A8E4 - _0206A8DC - 2; case 0
	.short _0206A8EA - _0206A8DC - 2; case 1
	.short _0206A8F0 - _0206A8DC - 2; case 2
	.short _0206A8F6 - _0206A8DC - 2; case 3
_0206A8E4:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A8EA:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A8F0:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A8F6:
	add r1, r0, #0x0
_0206A8F8:
	add r0, r1, #0x0
	pop {r3, pc}

	thumb_func_start ResolveMonForme
ResolveMonForme: ; 0x0206A8FC
	ldr r3, _0206A928 ; =SPECIES_DEOXYS
	cmp r0, r3
	beq _0206A90C
	add r2, r3, #0x0
	add r2, #SPECIES_WORMADAM-SPECIES_DEOXYS
	cmp r0, r2
	beq _0206A91A
	bx lr
_0206A90C:
	cmp r1, #0x0
	beq _0206A926
	cmp r1, #0x3
	bgt _0206A926
	add r3, #SPECIES_DEOXYS_ATK-SPECIES_DEOXYS-1
	add r0, r1, r3
	bx lr
_0206A91A:
	cmp r1, #0x0
	beq _0206A926
	cmp r1, #0x2
	bgt _0206A926
	add r3, #SPECIES_WORMADAM_SANDY-SPECIES_DEOXYS-1
	add r0, r1, r3
_0206A926:
	bx lr
	.balign 4
_0206A928: .word SPECIES_DEOXYS

	thumb_func_start MaskOfFlagNo
MaskOfFlagNo: ; 0x0206A92C
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r4, #0x1
	cmp r5, #0x20
	blt _0206A93A
	bl ErrorHandling
_0206A93A:
	mov r0, #0x0
	cmp r5, #0x0
	ble _0206A948
_0206A940:
	add r0, r0, #0x1
	lsl r4, r4, #0x1
	cmp r0, r5
	blt _0206A940
_0206A948:
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start LowestFlagNo
LowestFlagNo: ; 0x0206A94C
	mov r3, #0x1
	mov r2, #0x0
_0206A950:
	add r1, r0, #0x0
	tst r1, r3
	bne _0206A95E
	add r2, r2, #0x1
	lsl r3, r3, #0x1
	cmp r2, #0x20
	blt _0206A950
_0206A95E:
	add r0, r2, #0x0
	bx lr
	.balign 4

	thumb_func_start IsPokemonLegendaryOrMythical
IsPokemonLegendaryOrMythical: ; 0x0206A964
	ldr r3, _0206A980 ; =sLegendaryMonsList
	mov r2, #0x0
_0206A968:
	ldrh r1, [r3, #0x0]
	cmp r0, r1
	bne _0206A972
	mov r0, #0x1
	bx lr
_0206A972:
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, #0x12
	blo _0206A968
	mov r0, #0x0
	bx lr
	nop
_0206A980: .word sLegendaryMonsList

	thumb_func_start GetLegendaryMon
GetLegendaryMon: ; 0x0206A984
	cmp r0, #0x12
	blo _0206A98A
	mov r0, #0x0
_0206A98A:
	lsl r1, r0, #0x1
	ldr r0, _0206A994 ; =sLegendaryMonsList
	ldrh r0, [r0, r1]
	bx lr
	nop
_0206A994: .word sLegendaryMonsList

	thumb_func_start FUN_0206A998
FUN_0206A998: ; 0x0206A998
	push {r3, lr}
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl IsPokemonLegendaryOrMythical
	pop {r3, pc}

	thumb_func_start FUN_0206A9AC
FUN_0206A9AC: ; 0x0206A9AC
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r6, r2, #0x0
	bl FUN_020239BC
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl GetBoxMonData
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl FUN_020239CC
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x9c
	mov r2, #0x0
	bl GetBoxMonData
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_020239A0
	add r7, r0, #0x0
	mov r0, #0x8
	add r1, r6, #0x0
	bl FUN_020219F4
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x90
	add r2, r6, #0x0
	mov r4, #0x0
	bl GetBoxMonData
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x4]
	cmp r1, r0
	bne _0206AA1C
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	cmp r1, r0
	bne _0206AA1C
	add r0, r7, #0x0
	add r1, r6, #0x0
	bl FUN_02021CE0
	cmp r0, #0x0
	bne _0206AA1C
	mov r4, #0x1
_0206AA1C:
	add r0, r6, #0x0
	bl FUN_02021A20
	add r0, r7, #0x0
	bl FUN_02021A20
	add r0, r4, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0206AA30
FUN_0206AA30: ; 0x0206AA30
	push {r3, lr}
	cmp r0, #0x3f
	bgt _0206AA48
	bge _0206AA6C
	cmp r0, #0x1
	bgt _0206AA74
	cmp r0, #0x0
	blt _0206AA74
	beq _0206AA82
	cmp r0, #0x1
	beq _0206AA82
	b _0206AA74
_0206AA48:
	cmp r0, #0x5a
	bgt _0206AA50
	beq _0206AA70
	b _0206AA74
_0206AA50:
	add r1, r0, #0x0
	sub r1, #0x5b
	cmp r1, #0x3
	bhi _0206AA74
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0206AA64: ; jump table (using 16-bit offset)
	.short _0206AA70 - _0206AA64 - 2; case 0
	.short _0206AA70 - _0206AA64 - 2; case 1
	.short _0206AA70 - _0206AA64 - 2; case 2
	.short _0206AA70 - _0206AA64 - 2; case 3
_0206AA6C:
	mov r0, #0x2
	pop {r3, pc}
_0206AA70:
	sub r0, #0x57
	pop {r3, pc}
_0206AA74:
	bl FUN_0206AE00
	cmp r0, #0x1
	bne _0206AA80
	mov r0, #0x1
	pop {r3, pc}
_0206AA80:
	mov r0, #0x0
_0206AA82:
	pop {r3, pc}

	thumb_func_start FUN_0206AA84
FUN_0206AA84: ; 0x0206AA84
	push {r3-r4, lr}
	sub sp, #0x1c
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, sp, #0x0
	strb r0, [r1, #0x0]
	add r1, sp, #0x0
	add r1, #0x1
	mov r2, #0x18
	bl MIi_CpuClearFast
	add r0, r4, #0x0
	mov r1, #0xa1
	add r2, sp, #0x0
	bl SetMonData
	add r2, sp, #0x0
	add r0, r4, #0x0
	mov r1, #0xaa
	add r2, #0x1
	bl SetMonData
	add sp, #0x1c
	pop {r3-r4, pc}

	thumb_func_start FUN_0206AAB4
FUN_0206AAB4: ; 0x0206AAB4
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl AcquireBoxMonLock
	mov r4, #0x0
	str r0, [sp, #0x0]
	add r7, r4, #0x0
	add r6, sp, #0x4
_0206AAC6:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x36
	add r2, r7, #0x0
	bl GetBoxMonData
	cmp r0, #0x0
	beq _0206AAF0
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x42
	mov r2, #0x0
	bl GetBoxMonData
	add r1, r4, #0x0
	strb r0, [r6, #0x0]
	add r0, r5, #0x0
	add r1, #0x3a
	add r2, sp, #0x4
	bl SetBoxMonData
_0206AAF0:
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _0206AAC6
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	bl ReleaseBoxMonLock
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
