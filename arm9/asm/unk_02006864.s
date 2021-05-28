    .include "asm/macros.inc"
    .include "global.inc"

    .extern UNK_020ECB98
    .extern UNK_020ECBA0
    .extern UNK_020ECBA8

	.text

	thumb_func_start FUN_02006B38
FUN_02006B38: ; 0x02006B38
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r3, #0x0
	mov r3, #0x1
	str r3, [sp, #0x0]
	ldr r3, [sp, #0x24]
	bl UncompressFromNarc
	add r4, r0, #0x0
	beq _02006B9E
	add r1, sp, #0x4
	bl NNS_G2dGetUnpackedCharacterData
	cmp r0, #0x0
	beq _02006B98
	ldr r1, [sp, #0x18]
	cmp r1, #0x0
	beq _02006B60
	ldr r0, [sp, #0x4]
	str r1, [r0, #0x10]
_02006B60:
	ldr r0, [sp, #0x1c]
	cmp r0, #0x1
	beq _02006B6C
	cmp r0, #0x2
	beq _02006B7C
	b _02006B88
_02006B6C:
	mov r0, #0x1
	lsl r0, r0, #0x1a
	ldr r1, [r0, #0x0]
	ldr r0, _02006BA4 ; =0x00300010
	and r1, r0
	ldr r0, [sp, #0x4]
	str r1, [r0, #0x8]
	b _02006B88
_02006B7C:
	ldr r0, _02006BA8 ; =0x04001000
	ldr r1, [r0, #0x0]
	ldr r0, _02006BA4 ; =0x00300010
	and r1, r0
	ldr r0, [sp, #0x4]
	str r1, [r0, #0x8]
_02006B88:
	lsl r6, r5, #0x2
	ldr r5, _02006BAC ; =UNK_020ECB98
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x20]
	ldr r2, [sp, #0x1c]
	ldr r3, [sp, #0x28]
	ldr r5, [r5, r6]
	blx r5
_02006B98:
	add r0, r4, #0x0
	bl FreeToHeap
_02006B9E:
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_02006BA4: .word 0x00300010
_02006BA8: .word 0x04001000
_02006BAC: .word UNK_020ECB98

	thumb_func_start FUN_02006BB0
FUN_02006BB0: ; 0x02006BB0
	push {r3-r5, lr}
	add r4, r3, #0x0
	mov r3, #0x0
	str r3, [sp, #0x0]
	ldr r3, [sp, #0x10]
	bl UncompressFromNarc
	add r5, r0, #0x0
	beq _02006BD6
	add r1, r4, #0x0
	bl NNS_G2dGetUnpackedBGCharacterData
	cmp r0, #0x0
	bne _02006BD6
	add r0, r5, #0x0
	bl FreeToHeap
	mov r0, #0x0
	pop {r3-r5, pc}
_02006BD6:
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02006BDC
FUN_02006BDC: ; 0x02006BDC
	push {r3-r5, lr}
	add r4, r3, #0x0
	mov r3, #0x0
	str r3, [sp, #0x0]
	ldr r3, [sp, #0x10]
	bl UncompressFromNarc
	add r5, r0, #0x0
	beq _02006C02
	add r1, r4, #0x0
	bl NNS_G2dGetUnpackedScreenData
	cmp r0, #0x0
	bne _02006C02
	add r0, r5, #0x0
	bl FreeToHeap
	mov r0, #0x0
	pop {r3-r5, pc}
_02006C02:
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02006C08
FUN_02006C08: ; 0x02006C08
	push {r3-r5, lr}
	add r5, r2, #0x0
	mov r2, #0x0
	str r2, [sp, #0x0]
	bl UncompressFromNarc
	add r4, r0, #0x0
	beq _02006C2C
	add r1, r5, #0x0
	bl NNS_G2dGetUnpackedPaletteData
	cmp r0, #0x0
	bne _02006C2C
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x0
	pop {r3-r5, pc}
_02006C2C:
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02006C30
FUN_02006C30: ; 0x02006C30
	push {r3-r5, lr}
	add r4, r3, #0x0
	mov r3, #0x0
	str r3, [sp, #0x0]
	ldr r3, [sp, #0x10]
	bl UncompressFromNarc
	add r5, r0, #0x0
	beq _02006C56
	add r1, r4, #0x0
	bl NNS_G2dGetUnpackedCellBank
	cmp r0, #0x0
	bne _02006C56
	add r0, r5, #0x0
	bl FreeToHeap
	mov r0, #0x0
	pop {r3-r5, pc}
_02006C56:
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02006C5C
FUN_02006C5C: ; 0x02006C5C
	push {r3-r5, lr}
	add r4, r3, #0x0
	mov r3, #0x0
	str r3, [sp, #0x0]
	ldr r3, [sp, #0x10]
	bl UncompressFromNarc
	add r5, r0, #0x0
	beq _02006C82
	add r1, r4, #0x0
	bl NNS_G2dGetUnpackedAnimBank
	cmp r0, #0x0
	bne _02006C82
	add r0, r5, #0x0
	bl FreeToHeap
	mov r0, #0x0
	pop {r3-r5, pc}
_02006C82:
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02006C88
FUN_02006C88: ; 0x02006C88
	push {r3, lr}
	add r3, r2, #0x0
	mov r2, #0x0
	str r2, [sp, #0x0]
	mov r2, #0x1
	bl UncompressFromNarc
	pop {r3, pc}

	thumb_func_start UncompressFromNarc
UncompressFromNarc: ; 0x02006C98
	; void * UncompressFromNarc(NarcId narcId, s32 memberNo, BOOL isCompressed, u32 heap_id, BOOL allocAtEnd)
	push {r3-r7, lr}
	add r5, r2, #0x0
	add r7, r0, #0x0
	add r6, r3, #0x0
	str r1, [sp, #0x0]
	cmp r5, #0x0
	bne _02006CAC
	ldr r2, [sp, #0x18]
	cmp r2, #0x1
	bne _02006CC0
_02006CAC:
	ldr r1, [sp, #0x0]
	add r0, r7, #0x0
	bl GetNarcMemberSizeByIdPair
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	b _02006CCE
_02006CC0:
	bl GetNarcMemberSizeByIdPair
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
_02006CCE:
	cmp r4, #0x0
	beq _02006D12
	ldr r2, [sp, #0x0]
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl ReadWholeNarcMemberByIdPair
	cmp r5, #0x0
	beq _02006D12
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	bne _02006CF2
	ldr r1, [r4, #0x0]
	add r0, r6, #0x0
	lsr r1, r1, #0x8
	bl AllocFromHeap
	b _02006CFC
_02006CF2:
	ldr r1, [r4, #0x0]
	add r0, r6, #0x0
	lsr r1, r1, #0x8
	bl AllocFromHeapAtEnd
_02006CFC:
	add r5, r0, #0x0
	cmp r5, #0x0
	beq _02006D10
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl MI_UncompressLZ8
	add r0, r4, #0x0
	bl FreeToHeap
_02006D10:
	add r4, r5, #0x0
_02006D12:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02006D18
FUN_02006D18: ; 0x02006D18
	push {r3-r7, lr}
	sub sp, #0x8
	ldr r5, [sp, #0x24]
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl GetNarcMemberSizeByIdPair
	str r0, [r5, #0x0]
	cmp r6, #0x0
	bne _02006D36
	ldr r0, [sp, #0x20]
	cmp r0, #0x1
	bne _02006D42
_02006D36:
	ldr r1, [r5, #0x0]
	add r0, r7, #0x0
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	b _02006D4C
_02006D42:
	ldr r1, [r5, #0x0]
	add r0, r7, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
_02006D4C:
	cmp r4, #0x0
	beq _02006D92
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	add r0, r4, #0x0
	bl ReadWholeNarcMemberByIdPair
	cmp r6, #0x0
	beq _02006D92
	ldr r0, [r4, #0x0]
	lsr r0, r0, #0x8
	str r0, [r5, #0x0]
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	bne _02006D74
	ldr r1, [r5, #0x0]
	add r0, r7, #0x0
	bl AllocFromHeap
	b _02006D7C
_02006D74:
	ldr r1, [r5, #0x0]
	add r0, r7, #0x0
	bl AllocFromHeapAtEnd
_02006D7C:
	add r5, r0, #0x0
	cmp r5, #0x0
	beq _02006D90
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl MI_UncompressLZ8
	add r0, r4, #0x0
	bl FreeToHeap
_02006D90:
	add r4, r5, #0x0
_02006D92:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
