    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020ECB98
UNK_020ECB98: ; 0x020ECB98
	.word FUN_020B1768
	.word FUN_020B1528

	.global UNK_020ECBA0
UNK_020ECBA0: ; 0x020ECBA0
	.word GX_LoadOBJ, GXS_LoadOBJ

	.global UNK_020ECBA8
UNK_020ECBA8: ; 0x020ECBA8
	.word FUN_020B1768, FUN_020B1528

	.global UNK_020ECBB0
UNK_020ECBB0: ; 0x020ECBB0
	.word GX_LoadBGPltt, GX_LoadOBJPltt, GX_LoadBGExtPltt, GX_LoadOBJExtPltt
	.word GXS_LoadBGPltt, GXS_LoadOBJPltt, GXS_LoadBGExtPltt, GXS_LoadOBJExtPltt

	.text

	thumb_func_start FUN_0200687C
FUN_0200687C: ; 0x0200687C
	push {r3-r7, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	mov r2, #0x0
	add r5, r3, #0x0
	str r2, [sp, #0x0]
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x2c]
	ldr r4, [sp, #0x24]
	bl UncompressFromNarc
	add r7, r0, #0x0
	beq _020068C2
	add r1, sp, #0x4
	bl FUN_020B0030
	cmp r0, #0x0
	beq _020068BC
	cmp r4, #0x0
	bne _020068A8
	ldr r0, [sp, #0x4]
	ldr r4, [r0, #0x10]
_020068A8:
	ldr r0, [sp, #0x20]
	lsl r1, r5, #0x18
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x4]
	add r0, r6, #0x0
	ldr r2, [r2, #0x14]
	lsr r1, r1, #0x18
	add r3, r4, #0x0
	bl FUN_02017E14
_020068BC:
	add r0, r7, #0x0
	bl FreeToHeap
_020068C2:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_020068C8
FUN_020068C8: ; 0x020068C8
	push {r3-r7, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	mov r2, #0x1
	add r5, r3, #0x0
	str r2, [sp, #0x0]
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x2c]
	ldr r4, [sp, #0x24]
	bl UncompressFromNarc
	add r7, r0, #0x0
	beq _0200692C
	add r1, sp, #0x4
	bl FUN_020B0180
	cmp r0, #0x0
	beq _02006926
	cmp r4, #0x0
	bne _020068F4
	ldr r0, [sp, #0x4]
	ldr r4, [r0, #0x8]
_020068F4:
	lsl r1, r5, #0x18
	add r0, r6, #0x0
	lsr r1, r1, #0x18
	bl FUN_0201886C
	cmp r0, #0x0
	beq _02006912
	ldr r2, [sp, #0x4]
	lsl r1, r5, #0x18
	add r0, r6, #0x0
	lsr r1, r1, #0x18
	add r2, #0xc
	add r3, r4, #0x0
	bl FUN_02017DFC
_02006912:
	ldr r0, [sp, #0x20]
	lsl r1, r5, #0x18
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x4]
	add r0, r6, #0x0
	lsr r1, r1, #0x18
	add r2, #0xc
	add r3, r4, #0x0
	bl FUN_02017CE8
_02006926:
	add r0, r7, #0x0
	bl FreeToHeap
_0200692C:
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02006930
FUN_02006930: ; 0x02006930
	push {lr}
	sub sp, #0xc
	str r3, [sp, #0x0]
	ldr r3, [sp, #0x10]
	str r3, [sp, #0x4]
	ldr r3, [sp, #0x14]
	str r3, [sp, #0x8]
	mov r3, #0x0
	bl FUN_02006948
	add sp, #0xc
	pop {pc}

	thumb_func_start FUN_02006948
FUN_02006948: ; 0x02006948
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r2, #0x0
	add r7, r3, #0x0
	mov r2, #0x1
	str r2, [sp, #0x0]
	ldr r3, [sp, #0x28]
	mov r2, #0x0
	ldr r6, [sp, #0x20]
	ldr r5, [sp, #0x24]
	bl UncompressFromNarc
	str r0, [sp, #0x4]
	cmp r0, #0x0
	beq _02006A2A
	add r1, sp, #0x8
	bl FUN_020B0138
	cmp r0, #0x0
	beq _02006A24
	ldr r0, [sp, #0x8]
	ldr r1, [r0, #0xc]
	add r1, r1, r7
	str r1, [r0, #0xc]
	cmp r5, #0x0
	bne _02006982
	ldr r0, [sp, #0x8]
	ldr r0, [r0, #0x8]
	sub r5, r0, r7
_02006982:
	ldr r0, [sp, #0x8]
	add r1, r5, #0x0
	ldr r0, [r0, #0xc]
	bl DC_FlushRange
	cmp r4, #0x7
	bhi _02006A14
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0200699C: ; jump table (using 16-bit offset)
	.short _02006A14 - _0200699C - 2; case 0
	.short _02006A14 - _0200699C - 2; case 1
	.short _020069AC - _0200699C - 2; case 2
	.short _020069E0 - _0200699C - 2; case 3
	.short _02006A14 - _0200699C - 2; case 4
	.short _02006A14 - _0200699C - 2; case 5
	.short _020069C6 - _0200699C - 2; case 6
	.short _020069FA - _0200699C - 2; case 7
_020069AC:
	bl GX_BeginLoadBGExtPltt
	ldr r0, [sp, #0x8]
	ldr r3, _02006A30 ; =UNK_020ECBB0
	lsl r4, r4, #0x2
	ldr r0, [r0, #0xc]
	ldr r3, [r3, r4]
	add r1, r6, #0x0
	add r2, r5, #0x0
	blx r3
	bl GX_EndLoadBGExtPltt
	b _02006A24
_020069C6:
	bl GXS_BeginLoadBGExtPltt
	ldr r0, [sp, #0x8]
	ldr r3, _02006A30 ; =UNK_020ECBB0
	lsl r4, r4, #0x2
	ldr r0, [r0, #0xc]
	ldr r3, [r3, r4]
	add r1, r6, #0x0
	add r2, r5, #0x0
	blx r3
	bl GXS_EndLoadBGExtPltt
	b _02006A24
_020069E0:
	bl GX_BeginLoadOBJExtPltt
	ldr r0, [sp, #0x8]
	ldr r3, _02006A30 ; =UNK_020ECBB0
	lsl r4, r4, #0x2
	ldr r0, [r0, #0xc]
	ldr r3, [r3, r4]
	add r1, r6, #0x0
	add r2, r5, #0x0
	blx r3
	bl GX_EndLoadOBJExtPltt
	b _02006A24
_020069FA:
	bl GXS_BeginLoadOBJExtPltt
	ldr r0, [sp, #0x8]
	ldr r3, _02006A30 ; =UNK_020ECBB0
	lsl r4, r4, #0x2
	ldr r0, [r0, #0xc]
	ldr r3, [r3, r4]
	add r1, r6, #0x0
	add r2, r5, #0x0
	blx r3
	bl GXS_EndLoadOBJExtPltt
	b _02006A24
_02006A14:
	ldr r0, [sp, #0x8]
	ldr r3, _02006A30 ; =UNK_020ECBB0
	lsl r4, r4, #0x2
	ldr r0, [r0, #0xc]
	ldr r3, [r3, r4]
	add r1, r6, #0x0
	add r2, r5, #0x0
	blx r3
_02006A24:
	ldr r0, [sp, #0x4]
	bl FreeToHeap
_02006A2A:
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02006A30: .word UNK_020ECBB0

	thumb_func_start FUN_02006A34
FUN_02006A34: ; 0x02006A34
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r2, #0x0
	mov r2, #0x1
	add r6, r3, #0x0
	str r2, [sp, #0x0]
	ldr r2, [sp, #0x24]
	ldr r3, [sp, #0x28]
	ldr r4, [sp, #0x20]
	bl UncompressFromNarc
	add r7, r0, #0x0
	beq _02006A80
	add r1, sp, #0x4
	bl FUN_020B0088
	cmp r0, #0x0
	beq _02006A7A
	cmp r4, #0x0
	bne _02006A60
	ldr r0, [sp, #0x4]
	ldr r4, [r0, #0x10]
_02006A60:
	ldr r0, [sp, #0x4]
	add r1, r4, #0x0
	ldr r0, [r0, #0x14]
	bl DC_FlushRange
	ldr r0, [sp, #0x4]
	ldr r3, _02006A88 ; =UNK_020ECBA0
	lsl r5, r5, #0x2
	ldr r0, [r0, #0x14]
	ldr r3, [r3, r5]
	add r1, r6, #0x0
	add r2, r4, #0x0
	blx r3
_02006A7A:
	add r0, r7, #0x0
	bl FreeToHeap
_02006A80:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02006A88: .word UNK_020ECBA0

	thumb_func_start FUN_02006A8C
FUN_02006A8C: ; 0x02006A8C
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r2, #0x0
	add r4, r3, #0x0
	mov r2, #0x1
	str r2, [sp, #0x0]
	ldr r3, [sp, #0x20]
	mov r2, #0x0
	bl UncompressFromNarc
	add r6, r0, #0x0
	beq _02006AE0
	add r1, sp, #0x4
	bl FUN_020B00F0
	add r7, r0, #0x0
	add r0, r6, #0x0
	add r1, sp, #0x8
	bl FUN_020B0138
	cmp r0, #0x0
	beq _02006ADA
	cmp r7, #0x0
	beq _02006ACE
	ldr r0, [sp, #0x24]
	add r2, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x4]
	add r3, r5, #0x0
	bl FUN_020B10E8
	b _02006ADA
_02006ACE:
	ldr r0, [sp, #0x8]
	ldr r3, [sp, #0x24]
	add r1, r4, #0x0
	add r2, r5, #0x0
	bl FUN_020B1240
_02006ADA:
	add r0, r6, #0x0
	bl FreeToHeap
_02006AE0:
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_02006AE4
FUN_02006AE4: ; 0x02006AE4
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r3, #0x0
	mov r3, #0x1
	str r3, [sp, #0x0]
	ldr r3, [sp, #0x24]
	bl UncompressFromNarc
	add r6, r0, #0x0
	ldr r4, _02006B30 ; =0x00000000
	beq _02006B28
	add r1, sp, #0x4
	bl FUN_020B0088
	cmp r0, #0x0
	beq _02006B22
	ldr r1, [sp, #0x18]
	cmp r1, #0x0
	beq _02006B0E
	ldr r0, [sp, #0x4]
	str r1, [r0, #0x10]
_02006B0E:
	ldr r4, _02006B34 ; =UNK_020ECBA8
	lsl r5, r5, #0x2
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x20]
	ldr r2, [sp, #0x1c]
	ldr r3, [sp, #0x28]
	ldr r4, [r4, r5]
	blx r4
	ldr r0, [sp, #0x4]
	ldr r4, [r0, #0x10]
_02006B22:
	add r0, r6, #0x0
	bl FreeToHeap
_02006B28:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_02006B30: .word 0x00000000
_02006B34: .word UNK_020ECBA8

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
	bl FUN_020B0088
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
	bl FUN_020B0030
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
	bl FUN_020B0180
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
	bl FUN_020B0138
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
	bl FUN_020AFEB8
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
	bl thunk_FUN_020afda0_2
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
