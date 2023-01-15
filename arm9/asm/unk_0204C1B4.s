	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F4878
UNK_020F4878: ; 0x020F4878
	.word FUN_0204C6D4, FUN_0204C7A0, FUN_0204C824, FUN_0204C89C
	.word FUN_0204C7A0, FUN_0204C93C, FUN_0204C7A0

	.global UNK_020F4894
UNK_020F4894: ; 0x020F4894
	.word FUN_0204C468, FUN_0204C4A4, FUN_0204C528, FUN_0204C5A0
	.word FUN_0204C644, FUN_0204C68C, FUN_0204C468

	.global UNK_020F48B0
UNK_020F48B0: ; 0x020F48B0
	.word 0x00000000, 0x00000000, FUN_0204C984, FUN_0204C9EC
	.word 0x00000000, 0x00000000, 0x00000000

	.text

	thumb_func_start FUN_0204C1B4
FUN_0204C1B4: ; 0x0204C1B4
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r5, r1, #0x0
	ldr r0, [sp, #0x24]
	mov r1, #0x20
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl AllocFromHeap
	add r2, r0, #0x0
	str r5, [r2, #0x4]
	str r4, [r2, #0x8]
	str r6, [r2, #0xc]
	add r0, sp, #0x8
	ldrh r0, [r0, #0x10]
	ldr r1, _0204C1F0 ; =FUN_0204C1F4
	strh r0, [r2, #0x10]
	ldr r0, [sp, #0x1c]
	str r0, [r2, #0x14]
	ldr r0, [sp, #0x20]
	str r0, [r2, #0x18]
	ldr r0, [sp, #0x24]
	str r0, [r2, #0x1c]
	mov r0, #0x0
	str r0, [r2, #0x0]
	add r0, r7, #0x0
	bl FUN_0204640C
	pop {r3-r7, pc}
	nop
_0204C1F0: .word FUN_0204C1F4

	thumb_func_start FUN_0204C1F4
FUN_0204C1F4: ; 0x0204C1F4
	push {r4-r5, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0204C214
	cmp r0, #0x1
	beq _0204C23C
	b _0204C258
_0204C214:
	ldr r0, [r5, #0x4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	ldr r0, [r4, #0x14]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x1c]
	str r0, [sp, #0x8]
	ldrh r3, [r4, #0x10]
	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0xc]
	bl FUN_0200E1D0
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204C258
_0204C23C:
	bl FUN_0200E308
	cmp r0, #0x0
	beq _0204C258
	ldr r0, [r5, #0x4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r5, pc}
_0204C258:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_0204C260
FUN_0204C260: ; 0x0204C260
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0xb
	mov r1, #0x24
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl AllocFromHeapAtEnd
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	str r0, [r2, #0x4]
	str r5, [r2, #0x8]
	str r4, [r2, #0xc]
	ldr r0, [sp, #0x18]
	str r6, [r2, #0x10]
	str r0, [r2, #0x14]
	ldr r0, [sp, #0x1c]
	ldr r1, _0204C298 ; =FUN_0204C380
	str r0, [r2, #0x18]
	ldr r0, [sp, #0x20]
	str r0, [r2, #0x20]
	add r0, r7, #0x0
	bl FUN_020463CC
	pop {r3-r7, pc}
	nop
_0204C298: .word FUN_0204C380

	thumb_func_start FUN_0204C29C
FUN_0204C29C: ; 0x0204C29C
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0xb
	mov r1, #0x24
	str r2, [sp, #0x0]
	str r3, [sp, #0x4]
	bl AllocFromHeapAtEnd
	add r6, r0, #0x0
	mov r4, #0x0
	str r4, [r6, #0x0]
	str r4, [r6, #0x4]
	ldr r0, [sp, #0x0]
	str r5, [r6, #0x8]
	str r0, [r6, #0xc]
	ldr r0, [sp, #0x4]
	str r0, [r6, #0x10]
	ldr r0, [sp, #0x20]
	str r0, [r6, #0x14]
	ldr r0, [sp, #0x24]
	str r0, [r6, #0x18]
	ldr r0, [r7, #0x1c]
	ldr r0, [r0, #0x0]
	str r0, [sp, #0x8]
	bl MapHeader_IsCave
	cmp r0, #0x0
	beq _0204C308
	add r0, r5, #0x0
	bl MapHeader_IsCave
	cmp r0, #0x0
	beq _0204C2E6
	mov r4, #0x6
	b _0204C36A
_0204C2E6:
	add r0, r5, #0x0
	bl MapHeader_IsOutdoor
	cmp r0, #0x0
	beq _0204C2F4
	mov r4, #0x5
	b _0204C36A
_0204C2F4:
	add r0, r5, #0x0
	bl MapHeader_IsBuilding
	cmp r0, #0x0
	beq _0204C302
	mov r4, #0x6
	b _0204C36A
_0204C302:
	bl GF_AssertFail
	b _0204C36A
_0204C308:
	ldr r0, [sp, #0x8]
	bl MapHeader_IsOutdoor
	cmp r0, #0x0
	beq _0204C334
	add r0, r5, #0x0
	bl MapHeader_IsCave
	cmp r0, #0x0
	beq _0204C320
	mov r4, #0x4
	b _0204C36A
_0204C320:
	add r0, r5, #0x0
	bl MapHeader_IsBuilding
	cmp r0, #0x0
	beq _0204C32E
	mov r4, #0x6
	b _0204C36A
_0204C32E:
	bl GF_AssertFail
	b _0204C36A
_0204C334:
	ldr r0, [sp, #0x8]
	bl MapHeader_IsBuilding
	cmp r0, #0x0
	beq _0204C366
	add r0, r5, #0x0
	bl MapHeader_IsOutdoor
	cmp r0, #0x0
	bne _0204C36A
	add r0, r5, #0x0
	bl MapHeader_IsBuilding
	cmp r0, #0x0
	beq _0204C356
	mov r4, #0x6
	b _0204C36A
_0204C356:
	add r0, r5, #0x0
	bl MapHeader_IsCave
	cmp r0, #0x0
	bne _0204C36A
	bl GF_AssertFail
	b _0204C36A
_0204C366:
	bl GF_AssertFail
_0204C36A:
	ldr r1, _0204C37C ; =FUN_0204C380
	add r0, r7, #0x0
	add r2, r6, #0x0
	str r4, [r6, #0x20]
	bl FUN_020463CC
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_0204C37C: .word FUN_0204C380

	thumb_func_start FUN_0204C380
FUN_0204C380: ; 0x0204C380
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	add r6, r4, #0x0
	ldr r1, [r4, #0x0]
	add r6, #0x8
	cmp r1, #0x6
	bhi _0204C458
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0204C3A8: ; jump table (using 16-bit offset)
	.short _0204C3B6 - _0204C3A8 - 2; case 0
	.short _0204C3DA - _0204C3A8 - 2; case 1
	.short _0204C3E8 - _0204C3A8 - 2; case 2
	.short _0204C3F8 - _0204C3A8 - 2; case 3
	.short _0204C406 - _0204C3A8 - 2; case 4
	.short _0204C41E - _0204C3A8 - 2; case 5
	.short _0204C450 - _0204C3A8 - 2; case 6
_0204C3B6:
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r1, [r6, #0x0]
	add r0, r7, #0x0
	bl FUN_0204AD60
	ldr r1, [r4, #0x20]
	add r0, r5, #0x0
	lsl r2, r1, #0x2
	ldr r1, _0204C45C ; =UNK_020F4894
	ldr r1, [r1, r2]
	add r2, r4, #0x0
	bl FUN_0204640C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204C458
_0204C3DA:
	add r0, r5, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204C458
_0204C3E8:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02049160
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204C458
_0204C3F8:
	add r0, r5, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204C458
_0204C406:
	ldr r0, [r4, #0x20]
	lsl r1, r0, #0x2
	ldr r0, _0204C460 ; =UNK_020F48B0
	ldr r1, [r0, r1]
	cmp r1, #0x0
	beq _0204C416
	add r0, r7, #0x0
	blx r1
_0204C416:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204C458
_0204C41E:
	bl FUN_02005404
	cmp r0, #0x0
	bne _0204C458
	ldr r1, [r6, #0x0]
	add r0, r7, #0x0
	bl FUN_0204AD8C
	add r0, r7, #0x0
	bl MOD05_021E331C
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r1, [r4, #0x20]
	add r0, r5, #0x0
	lsl r2, r1, #0x2
	ldr r1, _0204C464 ; =UNK_020F4878
	ldr r1, [r1, r2]
	add r2, r4, #0x0
	bl FUN_0204640C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204C458
_0204C450:
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r7, pc}
_0204C458:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0204C45C: .word UNK_020F4894
_0204C460: .word UNK_020F48B0
_0204C464: .word UNK_020F4878

	thumb_func_start FUN_0204C468
FUN_0204C468: ; 0x0204C468
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _0204C484
	cmp r0, #0x1
	beq _0204C498
	b _0204C49C
_0204C484:
	ldr r0, _0204C4A0 ; =0x00000603
	bl PlaySE
	add r0, r5, #0x0
	bl FUN_0204AFC8
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C49C
_0204C498:
	mov r0, #0x1
	pop {r3-r5, pc}
_0204C49C:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0204C4A0: .word 0x00000603

	thumb_func_start FUN_0204C4A4
FUN_0204C4A4: ; 0x0204C4A4
	push {r4-r6, lr}
	add r6, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x3
	bhi _0204C522
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0204C4C8: ; jump table (using 16-bit offset)
	.short _0204C4D0 - _0204C4C8 - 2; case 0
	.short _0204C4F6 - _0204C4C8 - 2; case 1
	.short _0204C510 - _0204C4C8 - 2; case 2
	.short _0204C51E - _0204C4C8 - 2; case 3
_0204C4D0:
	bl MOD05_021DA5B8
	str r0, [r4, #0x1c]
	ldr r0, [r5, #0x38]
	bl FUN_02055320
	add r6, r0, #0x0
	ldr r0, [r5, #0x38]
	bl FUN_0205532C
	add r1, r0, #0x0
	ldr r2, [r4, #0x1c]
	add r0, r6, #0x0
	bl MOD05_021DA5D0
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C522
_0204C4F6:
	ldr r1, [r4, #0x1c]
	add r0, r5, #0x0
	bl MOD05_021DA5D8
	cmp r0, #0x0
	beq _0204C522
	ldr r0, [r4, #0x1c]
	bl MOD05_021DA5C8
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C522
_0204C510:
	add r0, r6, #0x0
	bl FUN_0204AFC8
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C522
_0204C51E:
	mov r0, #0x1
	pop {r4-r6, pc}
_0204C522:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0204C528
FUN_0204C528: ; 0x0204C528
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _0204C54A
	cmp r0, #0x1
	beq _0204C570
	cmp r0, #0x2
	beq _0204C598
	b _0204C59C
_0204C54A:
	bl MOD05_021DA5B8
	str r0, [r4, #0x1c]
	ldr r0, [r5, #0x38]
	bl FUN_02055320
	add r6, r0, #0x0
	ldr r0, [r5, #0x38]
	bl FUN_0205532C
	add r1, r0, #0x0
	ldr r2, [r4, #0x1c]
	add r0, r6, #0x0
	bl MOD05_021DA5D0
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C59C
_0204C570:
	ldr r0, [r5, #0x38]
	ldr r6, [r4, #0x1c]
	bl PlayerAvatar_GetFacingDirection
	add r2, r0, #0x0
	lsl r2, r2, #0x18
	add r0, r5, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	bl MOD05_021DAC70
	cmp r0, #0x0
	beq _0204C59C
	ldr r0, [r4, #0x1c]
	bl MOD05_021DA5C8
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C59C
_0204C598:
	mov r0, #0x1
	pop {r4-r6, pc}
_0204C59C:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0204C5A0
FUN_0204C5A0: ; 0x0204C5A0
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x3
	bhi _0204C63C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0204C5C4: ; jump table (using 16-bit offset)
	.short _0204C5CC - _0204C5C4 - 2; case 0
	.short _0204C5FE - _0204C5C4 - 2; case 1
	.short _0204C61C - _0204C5C4 - 2; case 2
	.short _0204C630 - _0204C5C4 - 2; case 3
_0204C5CC:
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetFacingDirection
	add r6, r0, #0x0
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	cmp r6, #0x2
	bne _0204C5E6
	mov r1, #0xa
	bl FUN_0205ADDC
	b _0204C5F6
_0204C5E6:
	cmp r6, #0x3
	bne _0204C5F2
	mov r1, #0xb
	bl FUN_0205ADDC
	b _0204C5F6
_0204C5F2:
	bl GF_AssertFail
_0204C5F6:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C63C
_0204C5FE:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r5, r0, #0x0
	bl FUN_0205AE28
	cmp r0, #0x1
	bne _0204C63C
	add r0, r5, #0x0
	bl FUN_0205AE50
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C63C
_0204C61C:
	ldr r0, _0204C640 ; =0x00000603
	bl PlaySE
	mov r0, #0x0
	bl MOD05_021D7CA4
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C63C
_0204C630:
	bl FUN_0200E308
	cmp r0, #0x0
	beq _0204C63C
	mov r0, #0x1
	pop {r4-r6, pc}
_0204C63C:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_0204C640: .word 0x00000603

	thumb_func_start FUN_0204C644
FUN_0204C644: ; 0x0204C644
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r6, #0x38]
	bl FUN_020553A0
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _0204C668
	cmp r0, #0x1
	beq _0204C67E
	b _0204C682
_0204C668:
	bl MOD05_021DB030
	add r2, r0, #0x0
	ldr r1, _0204C688 ; =MOD05_021DB1D0
	add r0, r5, #0x0
	bl FUN_0204640C
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C682
_0204C67E:
	mov r0, #0x1
	pop {r4-r6, pc}
_0204C682:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_0204C688: .word MOD05_021DB1D0

	thumb_func_start FUN_0204C68C
FUN_0204C68C: ; 0x0204C68C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r6, #0x38]
	bl FUN_020553A0
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _0204C6B0
	cmp r0, #0x1
	beq _0204C6C6
	b _0204C6CA
_0204C6B0:
	bl MOD05_021DB030
	add r2, r0, #0x0
	ldr r1, _0204C6D0 ; =MOD05_021DB144
	add r0, r5, #0x0
	bl FUN_0204640C
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C6CA
_0204C6C6:
	mov r0, #0x1
	pop {r4-r6, pc}
_0204C6CA:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_0204C6D0: .word MOD05_021DB144

	thumb_func_start FUN_0204C6D4
FUN_0204C6D4: ; 0x0204C6D4
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl FUN_02046528
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	ldr r0, [r5, #0x4]
	cmp r0, #0x3
	bhi _0204C798
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0204C6F8: ; jump table (using 16-bit offset)
	.short _0204C700 - _0204C6F8 - 2; case 0
	.short _0204C74A - _0204C6F8 - 2; case 1
	.short _0204C770 - _0204C6F8 - 2; case 2
	.short _0204C794 - _0204C6F8 - 2; case 3
_0204C700:
	ldr r0, [r4, #0x38]
	bl FUN_020553A0
	add r7, r0, #0x0
	ldr r0, [r4, #0x38]
	bl FUN_02055320
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x38]
	bl FUN_0205532C
	add r2, r0, #0x0
	ldr r1, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_0204A6E0
	bl FUN_020547B0
	cmp r0, #0x0
	beq _0204C736
	add r0, r7, #0x0
	mov r1, #0x1
	bl FUN_0205889C
	mov r0, #0x1
	str r0, [r5, #0x4]
	b _0204C798
_0204C736:
	bl MOD05_021DB030
	add r2, r0, #0x0
	ldr r1, _0204C79C ; =MOD05_021DB250
	add r0, r6, #0x0
	bl FUN_0204640C
	mov r0, #0x3
	str r0, [r5, #0x4]
	b _0204C798
_0204C74A:
	bl MOD05_021DA5B8
	str r0, [r5, #0x1c]
	ldr r0, [r4, #0x38]
	bl FUN_02055320
	add r6, r0, #0x0
	ldr r0, [r4, #0x38]
	bl FUN_0205532C
	add r1, r0, #0x0
	ldr r2, [r5, #0x1c]
	add r0, r6, #0x0
	bl MOD05_021DA5D0
	ldr r0, [r5, #0x4]
	add r0, r0, #0x1
	str r0, [r5, #0x4]
	b _0204C798
_0204C770:
	ldr r5, [r5, #0x1c]
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl MOD05_021DA7B4
	cmp r0, #0x0
	beq _0204C798
	add r0, r5, #0x0
	bl MOD05_021DA5C8
	ldr r0, [r4, #0x38]
	bl FUN_020553A0
	mov r1, #0x0
	bl FUN_0205889C
	mov r0, #0x1
	pop {r3-r7, pc}
_0204C794:
	mov r0, #0x1
	pop {r3-r7, pc}
_0204C798:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0204C79C: .word MOD05_021DB250

	thumb_func_start FUN_0204C7A0
FUN_0204C7A0: ; 0x0204C7A0
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _0204C7BE
	cmp r0, #0x1
	beq _0204C814
	b _0204C818
_0204C7BE:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r7, r0, #0x0
	ldr r0, [r5, #0x38]
	bl FUN_02055320
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x38]
	bl FUN_0205532C
	add r2, r0, #0x0
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_0204A6E0
	bl FUN_020547B0
	cmp r0, #0x0
	beq _0204C7FE
	add r0, r7, #0x0
	mov r1, #0x1
	bl FUN_0205889C
	mov r0, #0x1
	str r0, [r4, #0x4]
	ldr r1, _0204C81C ; =FUN_0204C6D4
	add r0, r6, #0x0
	add r2, r4, #0x0
	bl FUN_020463EC
	b _0204C818
_0204C7FE:
	bl MOD05_021DB030
	add r2, r0, #0x0
	ldr r1, _0204C820 ; =MOD05_021DB380
	add r0, r6, #0x0
	bl FUN_0204640C
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C818
_0204C814:
	mov r0, #0x1
	pop {r3-r7, pc}
_0204C818:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0204C81C: .word FUN_0204C6D4
_0204C820: .word MOD05_021DB380

	thumb_func_start FUN_0204C824
FUN_0204C824: ; 0x0204C824
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _0204C846
	cmp r0, #0x1
	beq _0204C86C
	cmp r0, #0x2
	beq _0204C894
	b _0204C898
_0204C846:
	bl MOD05_021DA5B8
	str r0, [r4, #0x1c]
	ldr r0, [r5, #0x38]
	bl FUN_02055320
	add r6, r0, #0x0
	ldr r0, [r5, #0x38]
	bl FUN_0205532C
	add r1, r0, #0x0
	ldr r2, [r4, #0x1c]
	add r0, r6, #0x0
	bl MOD05_021DA5D0
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C898
_0204C86C:
	ldr r0, [r5, #0x38]
	ldr r6, [r4, #0x1c]
	bl PlayerAvatar_GetFacingDirection
	add r2, r0, #0x0
	lsl r2, r2, #0x18
	add r0, r5, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	bl MOD05_021DAAA4
	cmp r0, #0x0
	beq _0204C898
	ldr r0, [r4, #0x1c]
	bl MOD05_021DA5C8
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C898
_0204C894:
	mov r0, #0x1
	pop {r4-r6, pc}
_0204C898:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0204C89C
FUN_0204C89C: ; 0x0204C89C
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x3
	bhi _0204C936
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0204C8C0: ; jump table (using 16-bit offset)
	.short _0204C8C8 - _0204C8C0 - 2; case 0
	.short _0204C904 - _0204C8C0 - 2; case 1
	.short _0204C922 - _0204C8C0 - 2; case 2
	.short _0204C932 - _0204C8C0 - 2; case 3
_0204C8C8:
	mov r0, #0x1
	bl MOD05_021D7CA4
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r6, r0, #0x0
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetFacingDirection
	cmp r0, #0x2
	bne _0204C8EA
	add r0, r6, #0x0
	mov r1, #0xa
	bl FUN_0205ADDC
	b _0204C8FC
_0204C8EA:
	cmp r0, #0x3
	bne _0204C8F8
	add r0, r6, #0x0
	mov r1, #0xb
	bl FUN_0205ADDC
	b _0204C8FC
_0204C8F8:
	bl GF_AssertFail
_0204C8FC:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C936
_0204C904:
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r5, r0, #0x0
	bl FUN_0205AE28
	cmp r0, #0x1
	bne _0204C936
	add r0, r5, #0x0
	bl FUN_0205AE50
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C936
_0204C922:
	bl FUN_0200E308
	cmp r0, #0x0
	beq _0204C936
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C936
_0204C932:
	mov r0, #0x1
	pop {r4-r6, pc}
_0204C936:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0204C93C
FUN_0204C93C: ; 0x0204C93C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r6, #0x38]
	bl FUN_020553A0
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _0204C960
	cmp r0, #0x1
	beq _0204C976
	b _0204C97A
_0204C960:
	bl MOD05_021DB030
	add r2, r0, #0x0
	ldr r1, _0204C980 ; =MOD05_021DB040
	add r0, r5, #0x0
	bl FUN_0204640C
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0204C97A
_0204C976:
	mov r0, #0x1
	pop {r4-r6, pc}
_0204C97A:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_0204C980: .word MOD05_021DB040

	thumb_func_start FUN_0204C984
FUN_0204C984: ; 0x0204C984
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetFacingDirection
	add r4, r0, #0x0
	ldr r0, [r5, #0x38]
	add r1, sp, #0x4
	bl FUN_02055350
	cmp r4, #0x3
	bne _0204C9AA
	mov r0, #0x1
	ldr r1, [sp, #0x4]
	lsl r0, r0, #0x10
	sub r0, r1, r0
	str r0, [sp, #0x4]
	b _0204C9B4
_0204C9AA:
	mov r0, #0x1
	ldr r1, [sp, #0x4]
	lsl r0, r0, #0x10
	add r0, r1, r0
	str r0, [sp, #0x4]
_0204C9B4:
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x8]
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0xc]
	add r0, r5, #0x0
	bl FUN_0204A708
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x38]
	add r1, sp, #0x4
	add r2, r4, #0x0
	bl FUN_020554EC
	ldr r0, [r5, #0x38]
	bl FUN_02055360
	ldr r1, [r5, #0x20]
	bl Camera_SetLookAtTargetAndRecalcPos
	ldr r0, [r5, #0x38]
	bl FUN_02055360
	ldr r1, [r5, #0x20]
	bl Camera_SetFixedTarget
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_0204C9EC
FUN_0204C9EC: ; 0x0204C9EC
	push {r4-r6, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetFacingDirection
	add r4, r0, #0x0
	ldr r0, [r5, #0x38]
	add r1, sp, #0x4
	bl FUN_02055350
	ldr r0, [r5, #0x38]
	bl FUN_02055320
	add r6, r0, #0x0
	ldr r0, [r5, #0x38]
	bl FUN_0205532C
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0204A6E0
	add r6, r0, #0x0
	bl FUN_020548D8
	cmp r0, #0x0
	beq _0204CA32
	mov r0, #0x1
	ldr r1, [sp, #0x4]
	lsl r0, r0, #0x10
	add r0, r1, r0
	str r0, [sp, #0x4]
	mov r4, #0x2
	b _0204CA48
_0204CA32:
	add r0, r6, #0x0
	bl FUN_020548E4
	cmp r0, #0x0
	beq _0204CA48
	mov r0, #0x1
	ldr r1, [sp, #0x4]
	lsl r0, r0, #0x10
	sub r0, r1, r0
	str r0, [sp, #0x4]
	mov r4, #0x3
_0204CA48:
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x8]
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0xc]
	add r0, r5, #0x0
	bl FUN_0204A708
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x38]
	add r1, sp, #0x4
	add r2, r4, #0x0
	bl FUN_020554EC
	ldr r0, [r5, #0x38]
	bl FUN_02055360
	ldr r1, [r5, #0x20]
	bl Camera_SetLookAtTargetAndRecalcPos
	ldr r0, [r5, #0x38]
	bl FUN_02055360
	ldr r1, [r5, #0x20]
	bl Camera_SetFixedTarget
	add sp, #0x10
	pop {r4-r6, pc}
