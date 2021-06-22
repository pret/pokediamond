	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020EE668
UNK_020EE668: ; 0x020EE668
	.byte 0x00, 0x01, 0x02, 0x03

	.global UNK_020EE66C
UNK_020EE66C: ; 0x020EE66C
	.word FUN_020216EC, FUN_0202171C

	.global UNK_020EE674
UNK_020EE674: ; 0x020EE674
	.word FUN_0202173C, FUN_0202174C

	.text

	thumb_func_start FUN_02021590
FUN_02021590: ; 0x02021590
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r6, r1, #0x0
	ldr r0, [sp, #0x20]
	mov r1, #0x78
	add r7, r2, #0x0
	str r3, [sp, #0x4]
	bl AllocFromHeap
	add r4, r0, #0x0
	beq _020215C0
	ldr r1, [sp, #0x20]
	ldr r3, [sp, #0x4]
	str r1, [sp, #0x0]
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl FUN_02021600
	ldr r2, [sp, #0x20]
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_020216D4
_020215C0:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020215C8
FUN_020215C8: ; 0x020215C8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02021728
	add r0, r4, #0x0
	bl FUN_020216B8
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020215E0
FUN_020215E0: ; 0x020215E0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	add r6, r2, #0x0
	cmp r1, r4
	beq _020215FC
	bl FUN_02021728
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020216D4
_020215FC:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02021600
FUN_02021600: ; 0x02021600
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r0, r1, #0x0
	ldr r1, [sp, #0x18]
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl NARC_ctor
	str r0, [r5, #0x54]
	cmp r0, #0x0
	beq _020216A6
	add r1, r5, #0x0
	add r1, #0x5c
	str r1, [sp, #0x0]
	add r1, r4, #0x0
	mov r2, #0x0
	mov r3, #0x10
	bl NARC_ReadFromMember
	str r6, [r5, #0x6c]
	cmp r6, #0x0
	beq _02021638
	mov r0, #0x0
	str r0, [r5, #0x74]
	ldr r0, _020216AC ; =FUN_0202192C
	str r0, [r5, #0x70]
	b _02021660
_02021638:
	ldr r0, [r5, #0x60]
	cmp r0, #0x0
	bne _02021642
	bl GF_AssertFail
_02021642:
	ldr r0, [sp, #0x18]
	ldr r1, [r5, #0x64]
	bl AllocFromHeap
	str r0, [r5, #0x74]
	ldr r0, _020216B0 ; =FUN_02021924
	add r1, r4, #0x0
	str r0, [r5, #0x70]
	ldr r0, [r5, #0x74]
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x54]
	ldr r2, [r5, #0x60]
	ldr r3, [r5, #0x64]
	bl NARC_ReadFromMember
_02021660:
	add r0, r5, #0x0
	add r0, #0x6a
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bhi _02021674
	add r0, r5, #0x0
	add r0, #0x6b
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bls _02021678
_02021674:
	bl GF_AssertFail
_02021678:
	add r0, r5, #0x0
	add r0, #0x6a
	ldrb r0, [r0, #0x0]
	ldr r2, _020216B4 ; =UNK_020EE668
	sub r0, r0, #0x1
	lsl r3, r0, #0x1
	add r0, r5, #0x0
	add r0, #0x6b
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r2, r3
	ldrb r0, [r1, r0]
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	add r0, #0x6b
	ldrb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x6a
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x4
	mul r0, r1
	str r0, [r5, #0xc]
	str r4, [r5, #0x58]
_020216A6:
	add sp, #0x4
	pop {r3-r6, pc}
	nop
_020216AC: .word FUN_0202192C
_020216B0: .word FUN_02021924
_020216B4: .word UNK_020EE668

	thumb_func_start FUN_020216B8
FUN_020216B8: ; 0x020216B8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x74]
	cmp r0, #0x0
	beq _020216C6
	bl FreeToHeap
_020216C6:
	ldr r0, [r4, #0x54]
	cmp r0, #0x0
	beq _020216D0
	bl NARC_dtor
_020216D0:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020216D4
FUN_020216D4: ; 0x020216D4
	push {r3, lr}
	add r3, r1, #0x0
	add r1, r2, #0x0
	str r3, [r0, #0x0]
	ldr r2, _020216E8 ; =UNK_020EE66C
	lsl r3, r3, #0x2
	ldr r2, [r2, r3]
	blx r2
	pop {r3, pc}
	nop
_020216E8: .word UNK_020EE66C

	thumb_func_start FUN_020216EC
FUN_020216EC: ; 0x020216EC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0xc]
	ldr r0, [r5, #0x64]
	add r4, r2, #0x0
	mul r4, r0
	add r0, r1, #0x0
	add r1, r4, #0x0
	bl AllocFromHeap
	str r0, [r5, #0x10]
	ldr r0, _02021718 ; =FUN_02021774
	add r3, r4, #0x0
	str r0, [r5, #0x4]
	ldr r0, [r5, #0x10]
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	ldr r2, [r5, #0x5c]
	bl NARC_ReadFromMember
	pop {r3-r5, pc}
	.balign 4
_02021718: .word FUN_02021774

	thumb_func_start FUN_0202171C
FUN_0202171C: ; 0x0202171C
	ldr r1, _02021724 ; =FUN_0202181C
	str r1, [r0, #0x4]
	bx lr
	nop
_02021724: .word FUN_0202181C

	thumb_func_start FUN_02021728
FUN_02021728: ; 0x02021728
	push {r3, lr}
	ldr r1, [r0, #0x0]
	lsl r2, r1, #0x2
	ldr r1, _02021738 ; =UNK_020EE674
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	nop
_02021738: .word UNK_020EE674

	thumb_func_start FUN_0202173C
FUN_0202173C: ; 0x0202173C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x10]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x10]
	pop {r4, pc}

	thumb_func_start FUN_0202174C
FUN_0202174C: ; 0x0202174C
	bx lr
	.balign 4

	thumb_func_start FUN_02021750
FUN_02021750: ; 0x02021750
	push {r3, lr}
	ldr r3, [r0, #0x64]
	cmp r1, r3
	bhi _02021764
	sub r1, r1, #0x1
	lsl r1, r1, #0x10
	ldr r3, [r0, #0x4]
	lsr r1, r1, #0x10
	blx r3
	pop {r3, pc}
_02021764:
	add r0, r2, #0x0
	mov r1, #0x0
	add r0, #0x80
	strb r1, [r0, #0x0]
	add r2, #0x81
	strb r1, [r2, #0x0]
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02021774
FUN_02021774: ; 0x02021774
	push {r3-r7, lr}
	str r1, [sp, #0x0]
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	ldr r1, [r7, #0xc]
	add r5, r0, #0x0
	ldr r0, [r7, #0x8]
	add r6, r2, #0x0
	mul r5, r1
	ldr r4, [r7, #0x10]
	cmp r0, #0x3
	bhi _02021802
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02021798: ; jump table (using 16-bit offset)
	.short _020217A0 - _02021798 - 2; case 0
	.short _020217AA - _02021798 - 2; case 1
	.short _020217C0 - _02021798 - 2; case 2
	.short _020217D6 - _02021798 - 2; case 3
_020217A0:
	add r0, r4, r5
	add r1, r6, #0x0
	bl DecompressGlyphTile
	b _02021802
_020217AA:
	add r0, r4, r5
	add r1, r6, #0x0
	bl DecompressGlyphTile
	add r0, r4, r5
	add r1, r6, #0x0
	add r0, #0x10
	add r1, #0x40
	bl DecompressGlyphTile
	b _02021802
_020217C0:
	add r0, r4, r5
	add r1, r6, #0x0
	bl DecompressGlyphTile
	add r0, r4, r5
	add r1, r6, #0x0
	add r0, #0x10
	add r1, #0x20
	bl DecompressGlyphTile
	b _02021802
_020217D6:
	add r0, r4, r5
	add r1, r6, #0x0
	bl DecompressGlyphTile
	add r0, r4, r5
	add r1, r6, #0x0
	add r0, #0x10
	add r1, #0x20
	bl DecompressGlyphTile
	add r0, r4, r5
	add r1, r6, #0x0
	add r0, #0x20
	add r1, #0x40
	bl DecompressGlyphTile
	add r0, r4, r5
	add r1, r6, #0x0
	add r0, #0x30
	add r1, #0x60
	bl DecompressGlyphTile
_02021802:
	ldr r1, [sp, #0x0]
	ldr r2, [r7, #0x70]
	add r0, r7, #0x0
	blx r2
	add r1, r6, #0x0
	add r1, #0x80
	add r7, #0x69
	strb r0, [r1, #0x0]
	ldrb r0, [r7, #0x0]
	add r6, #0x81
	strb r0, [r6, #0x0]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202181C
FUN_0202181C: ; 0x0202181C
	push {r3-r7, lr}
	add r4, r0, #0x0
	ldr r6, [r4, #0xc]
	add r0, #0x14
	str r0, [sp, #0x0]
	add r7, r1, #0x0
	add r5, r2, #0x0
	add r2, r7, #0x0
	ldr r3, [r4, #0x5c]
	mul r2, r6
	add r2, r3, r2
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	add r3, r6, #0x0
	bl NARC_ReadFromMember
	ldr r0, [r4, #0x8]
	cmp r0, #0x3
	bhi _020218C0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0202184E: ; jump table (using 16-bit offset)
	.short _02021856 - _0202184E - 2; case 0
	.short _02021862 - _0202184E - 2; case 1
	.short _0202187A - _0202184E - 2; case 2
	.short _02021892 - _0202184E - 2; case 3
_02021856:
	add r0, r4, #0x0
	add r0, #0x14
	add r1, r5, #0x0
	bl DecompressGlyphTile
	b _020218C0
_02021862:
	add r0, r4, #0x0
	add r0, #0x14
	add r1, r5, #0x0
	bl DecompressGlyphTile
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r0, #0x24
	add r1, #0x40
	bl DecompressGlyphTile
	b _020218C0
_0202187A:
	add r0, r4, #0x0
	add r0, #0x14
	add r1, r5, #0x0
	bl DecompressGlyphTile
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r0, #0x24
	add r1, #0x20
	bl DecompressGlyphTile
	b _020218C0
_02021892:
	add r0, r4, #0x0
	add r0, #0x14
	add r1, r5, #0x0
	bl DecompressGlyphTile
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r0, #0x24
	add r1, #0x20
	bl DecompressGlyphTile
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r0, #0x34
	add r1, #0x40
	bl DecompressGlyphTile
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r0, #0x44
	add r1, #0x60
	bl DecompressGlyphTile
_020218C0:
	ldr r2, [r4, #0x70]
	add r0, r4, #0x0
	add r1, r7, #0x0
	blx r2
	add r1, r5, #0x0
	add r1, #0x80
	add r4, #0x69
	strb r0, [r1, #0x0]
	ldrb r0, [r4, #0x0]
	add r5, #0x81
	strb r0, [r5, #0x0]
	pop {r3-r7, pc}

	thumb_func_start FUN_020218D8
FUN_020218D8: ; 0x020218D8
	push {r3-r7, lr}
	add r4, r1, #0x0
	ldrh r1, [r4, #0x0]
	add r5, r0, #0x0
	ldr r0, _0202191C ; =0x0000FFFF
	add r7, r2, #0x0
	mov r6, #0x0
	cmp r1, r0
	beq _02021916
_020218EA:
	ldr r0, _02021920 ; =0x0000FFFE
	cmp r1, r0
	bne _02021900
	add r0, r4, #0x0
	bl MsgArray_SkipControlCode
	add r4, r0, #0x0
	ldrh r1, [r4, #0x0]
	ldr r0, _0202191C ; =0x0000FFFF
	cmp r1, r0
	beq _02021916
_02021900:
	ldr r2, [r5, #0x70]
	add r0, r5, #0x0
	sub r1, r1, #0x1
	blx r2
	add r4, r4, #0x2
	add r0, r7, r0
	add r6, r6, r0
	ldrh r1, [r4, #0x0]
	ldr r0, _0202191C ; =0x0000FFFF
	cmp r1, r0
	bne _020218EA
_02021916:
	sub r0, r6, r7
	pop {r3-r7, pc}
	nop
_0202191C: .word 0x0000FFFF
_02021920: .word 0x0000FFFE

	thumb_func_start FUN_02021924
FUN_02021924: ; 0x02021924
	ldr r0, [r0, #0x74]
	ldrb r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start FUN_0202192C
FUN_0202192C: ; 0x0202192C
	add r0, #0x68
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4
