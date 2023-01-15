	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start FUN_02055068
FUN_02055068: ; 0x02055068
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r0, #0x0
	add r5, r1, #0x0
	add r4, r2, #0x0
	str r3, [sp, #0x8]
	bl FUN_0205517C
	ldr r1, [sp, #0x20]
	ldr r2, [sp, #0x24]
	ldr r3, [sp, #0x28]
	add r6, r0, #0x0
	bl FUN_0205519C
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x24]
	bl FUN_020555A0
	add r2, r0, #0x0
	str r5, [sp, #0x0]
	ldr r3, [sp, #0x8]
	add r0, r6, #0x0
	add r1, r7, #0x0
	str r4, [sp, #0x4]
	bl FUN_02055208
	add r0, r6, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_020550A4
FUN_020550A4: ; 0x020550A4
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r7, r0, #0x0
	add r6, r2, #0x0
	bl FUN_0205517C
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020554C8
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	add r2, r6, #0x0
	add r3, r4, #0x0
	bl FUN_0205519C
	add r0, r7, #0x0
	bl FUN_020552E4
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	add r1, r6, #0x0
	bl FUN_020555A0
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058454
	mov r1, #0x9
	add r0, r4, #0x0
	lsl r1, r1, #0xa
	bl FUN_02058410
	mov r1, #0x6
	add r0, r4, #0x0
	lsl r1, r1, #0x6
	bl FUN_02058418
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02058AC8
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0205539C
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02055108
FUN_02055108: ; 0x02055108
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_020553A0
	add r4, r0, #0x0
	bne _02055118
	bl GF_AssertFail
_02055118:
	add r0, r4, #0x0
	bl FUN_02058578
	add r0, r5, #0x0
	bl MOD05_021EDBC8
	add r0, r5, #0x0
	bl FUN_020553C4
	cmp r0, #0x2
	bne _0205515C
	add r0, r5, #0x0
	bl FUN_02055320
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205532C
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl PlayerAvatar_GetFacingDirection
	add r3, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl MOD06_0224ABAC
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02055450
_0205515C:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02055160
FUN_02055160: ; 0x02055160
	ldr r3, _02055164 ; =FreeToHeap
	bx r3
	.balign 4
_02055164: .word FreeToHeap

	thumb_func_start FUN_02055168
FUN_02055168: ; 0x02055168
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020553A0
	bl FUN_02057654
	add r0, r4, #0x0
	bl FUN_02055160
	pop {r4, pc}

	thumb_func_start FUN_0205517C
FUN_0205517C: ; 0x0205517C
	push {r4, lr}
	mov r0, #0xb
	mov r1, #0x3c
	bl AllocFromHeap
	add r4, r0, #0x0
	bne _0205518E
	bl GF_AssertFail
_0205518E:
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x3c
	bl memset
	add r0, r4, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0205519C
FUN_0205519C: ; 0x0205519C
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r1, r3, #0x0
	add r6, r2, #0x0
	bl FUN_02055458
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0205536C
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02055374
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020553A8
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020553E4
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_020553DC
	add r0, r5, #0x0
	bl FUN_02055410
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	bl FUN_0205542C
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	bl FUN_02055434
	add r0, r5, #0x0
	mov r1, #0xff
	bl FUN_02055460
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_020556C8
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205574C
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02055208
FUN_02055208: ; 0x02055208
	push {r4-r5, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	add r0, r1, #0x0
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x1c]
	bl FUN_0205753C
	add r5, r0, #0x0
	bne _02055228
	bl GF_AssertFail
_02055228:
	add r0, r5, #0x0
	mov r1, #0xff
	bl FUN_02058444
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058484
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0205848C
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058494
	mov r1, #0x0
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_020584EC
	add r0, r5, #0x0
	mov r1, #0x0
	mov r2, #0x1
	bl FUN_020584EC
	add r0, r5, #0x0
	mov r1, #0x0
	mov r2, #0x2
	bl FUN_020584EC
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	bl FUN_02058534
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	bl FUN_0205853C
	mov r1, #0x9
	add r0, r5, #0x0
	lsl r1, r1, #0xa
	bl FUN_02058410
	mov r1, #0x6
	add r0, r5, #0x0
	lsl r1, r1, #0x6
	bl FUN_02058418
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02058AC8
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_0205539C
	add sp, #0xc
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_020552A4
FUN_020552A4: ; 0x020552A4
	push {r3-r7, lr}
	sub sp, #0x8
	mov r1, #0x0
	str r1, [sp, #0x4]
	str r1, [sp, #0x0]
	add r1, sp, #0x0
	add r2, sp, #0x4
	mov r3, #0x1
	add r5, r0, #0x0
	bl FUN_020580F4
	cmp r0, #0x0
	beq _020552DE
	add r4, sp, #0x0
	add r6, sp, #0x4
	mov r7, #0x1
_020552C4:
	ldr r0, [sp, #0x0]
	bl FUN_02058480
	cmp r0, #0x1
	beq _020552DE
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	add r3, r7, #0x0
	bl FUN_020580F4
	cmp r0, #0x0
	bne _020552C4
_020552DE:
	ldr r0, [sp, #0x0]
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_020552E4
FUN_020552E4: ; 0x020552E4
	push {r4, lr}
	bl FUN_020552A4
	add r4, r0, #0x0
	bne _020552F2
	bl GF_AssertFail
_020552F2:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start PlayerAvatar_GetFacingDirection
PlayerAvatar_GetFacingDirection: ; 0x020552F8
	push {r3, lr}
	bl FUN_020553A0
	bl FUN_020584C4
	pop {r3, pc}

	thumb_func_start FUN_02055304
FUN_02055304: ; 0x02055304
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_020553A0
	add r1, r4, #0x0
	bl FUN_020584AC
	pop {r4, pc}

	thumb_func_start FUN_02055314
FUN_02055314: ; 0x02055314
	push {r3, lr}
	bl FUN_020553A0
	bl FUN_020584D4
	pop {r3, pc}

	thumb_func_start FUN_02055320
FUN_02055320: ; 0x02055320
	push {r3, lr}
	bl FUN_020553A0
	bl FUN_02058B2C
	pop {r3, pc}

	thumb_func_start FUN_0205532C
FUN_0205532C: ; 0x0205532C
	push {r3, lr}
	bl FUN_020553A0
	bl FUN_02058B4C
	pop {r3, pc}

	thumb_func_start FUN_02055338
FUN_02055338: ; 0x02055338
	push {r3, lr}
	bl FUN_020553A0
	bl FUN_02058B14
	pop {r3, pc}

	thumb_func_start FUN_02055344
FUN_02055344: ; 0x02055344
	push {r3, lr}
	bl FUN_020553A0
	bl FUN_02058B24
	pop {r3, pc}

	thumb_func_start FUN_02055350
FUN_02055350: ; 0x02055350
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_020553A0
	add r1, r4, #0x0
	bl FUN_02058B5C
	pop {r4, pc}

	thumb_func_start FUN_02055360
FUN_02055360: ; 0x02055360
	push {r3, lr}
	bl FUN_020553A4
	bl FUN_02058B7C
	pop {r3, pc}

	thumb_func_start FUN_0205536C
FUN_0205536C: ; 0x0205536C
	str r1, [r0, #0x10]
	bx lr

	thumb_func_start FUN_02055370
FUN_02055370: ; 0x02055370
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start FUN_02055374
FUN_02055374: ; 0x02055374
	str r1, [r0, #0x14]
	bx lr

	thumb_func_start FUN_02055378
FUN_02055378: ; 0x02055378
	ldr r0, [r0, #0x14]
	bx lr

	thumb_func_start FUN_0205537C
FUN_0205537C: ; 0x0205537C
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_020553A0
	cmp r4, #0x1
	bne _02055392
	mov r1, #0x2
	lsl r1, r1, #0x8
	bl FUN_02058418
	pop {r4, pc}
_02055392:
	mov r1, #0x2
	lsl r1, r1, #0x8
	bl FUN_02058410
	pop {r4, pc}

	thumb_func_start FUN_0205539C
FUN_0205539C: ; 0x0205539C
	str r1, [r0, #0x2c]
	bx lr

	thumb_func_start FUN_020553A0
FUN_020553A0: ; 0x020553A0
	ldr r0, [r0, #0x2c]
	bx lr

	thumb_func_start FUN_020553A4
FUN_020553A4: ; 0x020553A4
	ldr r0, [r0, #0x2c]
	bx lr

	thumb_func_start FUN_020553A8
FUN_020553A8: ; 0x020553A8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x3
	blt _020553B6
	bl GF_AssertFail
_020553B6:
	add r0, r5, #0x0
	add r1, r4, #0x0
	str r4, [r5, #0x18]
	bl FUN_020554DC
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020553C4
FUN_020553C4: ; 0x020553C4
	push {r4, lr}
	add r4, r0, #0x0
	bne _020553CE
	bl GF_AssertFail
_020553CE:
	ldr r0, [r4, #0x18]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020553D4
FUN_020553D4: ; 0x020553D4
	ldr r2, [r0, #0x4]
	orr r1, r2
	str r1, [r0, #0x4]
	bx lr

	thumb_func_start FUN_020553DC
FUN_020553DC: ; 0x020553DC
	str r1, [r0, #0x4]
	bx lr

	thumb_func_start FUN_020553E0
FUN_020553E0: ; 0x020553E0
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_020553E4
FUN_020553E4: ; 0x020553E4
	str r1, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_020553E8
FUN_020553E8: ; 0x020553E8
	ldr r0, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_020553EC
FUN_020553EC: ; 0x020553EC
	ldr r2, [r0, #0x0]
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_020553F4
FUN_020553F4: ; 0x020553F4
	ldr r2, [r0, #0x0]
	mvn r1, r1
	and r1, r2
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02055400
FUN_02055400: ; 0x02055400
	ldr r0, [r0, #0x0]
	and r0, r1
	bx lr
	.balign 4

	thumb_func_start FUN_02055408
FUN_02055408: ; 0x02055408
	ldr r0, [r0, #0x20]
	bx lr

	thumb_func_start FUN_0205540C
FUN_0205540C: ; 0x0205540C
	str r1, [r0, #0x20]
	bx lr

	thumb_func_start FUN_02055410
FUN_02055410: ; 0x02055410
	ldr r3, _02055418 ; =FUN_020556F4
	mov r1, #0x0
	str r1, [r0, #0x20]
	bx r3
	.balign 4
_02055418: .word FUN_020556F4

	thumb_func_start FUN_0205541C
FUN_0205541C: ; 0x0205541C
	ldr r3, [r0, #0x20]
	add r1, r3, r1
	str r1, [r0, #0x20]
	cmp r1, r2
	ble _02055428
	str r2, [r0, #0x20]
_02055428:
	ldr r0, [r0, #0x20]
	bx lr

	thumb_func_start FUN_0205542C
FUN_0205542C: ; 0x0205542C
	str r1, [r0, #0x24]
	bx lr

	thumb_func_start FUN_02055430
FUN_02055430: ; 0x02055430
	ldr r0, [r0, #0x24]
	bx lr

	thumb_func_start FUN_02055434
FUN_02055434: ; 0x02055434
	str r1, [r0, #0x28]
	bx lr

	thumb_func_start FUN_02055438
FUN_02055438: ; 0x02055438
	ldr r0, [r0, #0x28]
	bx lr

	thumb_func_start FUN_0205543C
FUN_0205543C: ; 0x0205543C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl FUN_0205542C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02055434
	pop {r3-r5, pc}

	thumb_func_start FUN_02055450
FUN_02055450: ; 0x02055450
	str r1, [r0, #0x30]
	bx lr

	thumb_func_start FUN_02055454
FUN_02055454: ; 0x02055454
	ldr r0, [r0, #0x30]
	bx lr

	thumb_func_start FUN_02055458
FUN_02055458: ; 0x02055458
	str r1, [r0, #0x34]
	bx lr

	thumb_func_start FUN_0205545C
FUN_0205545C: ; 0x0205545C
	ldr r0, [r0, #0x34]
	bx lr

	thumb_func_start FUN_02055460
FUN_02055460: ; 0x02055460
	str r1, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02055464
FUN_02055464: ; 0x02055464
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02055468
FUN_02055468: ; 0x02055468
	mov r1, #0x0
	strh r1, [r0, #0x0]
	strh r1, [r0, #0x2]
	str r1, [r0, #0x4]
	bx lr
	.balign 4

	thumb_func_start FUN_02055474
FUN_02055474: ; 0x02055474
	cmp r0, #0x0
	beq _02055482
	ldrh r0, [r0, #0x2]
	cmp r0, #0x1
	bne _02055482
	mov r0, #0x1
	bx lr
_02055482:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02055488
FUN_02055488: ; 0x02055488
	cmp r1, #0x1
	bne _02055492
	mov r1, #0x1
	strh r1, [r0, #0x2]
	bx lr
_02055492:
	mov r1, #0x0
	strh r1, [r0, #0x2]
	bx lr

	thumb_func_start FUN_02055498
FUN_02055498: ; 0x02055498
	cmp r0, #0x0
	bne _020554A0
	mov r0, #0x0
	bx lr
_020554A0:
	ldrh r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_020554A4
FUN_020554A4: ; 0x020554A4
	cmp r0, #0x0
	beq _020554AA
	strh r1, [r0, #0x0]
_020554AA:
	bx lr

	thumb_func_start FUN_020554AC
FUN_020554AC: ; 0x020554AC
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_0205545C
	add r1, r4, #0x0
	bl FUN_020554A4
	pop {r4, pc}

	thumb_func_start FUN_020554BC
FUN_020554BC: ; 0x020554BC
	push {r3, lr}
	bl FUN_0205545C
	bl FUN_02055498
	pop {r3, pc}

	thumb_func_start FUN_020554C8
FUN_020554C8: ; 0x020554C8
	cmp r0, #0x0
	beq _020554D0
	ldr r0, [r0, #0x4]
	bx lr
_020554D0:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_020554D4
FUN_020554D4: ; 0x020554D4
	cmp r0, #0x0
	beq _020554DA
	str r1, [r0, #0x4]
_020554DA:
	bx lr

	thumb_func_start FUN_020554DC
FUN_020554DC: ; 0x020554DC
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_0205545C
	add r1, r4, #0x0
	bl FUN_020554D4
	pop {r4, pc}

	thumb_func_start FUN_020554EC
FUN_020554EC: ; 0x020554EC
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r5, r0, #0x0
	bl FUN_020553A0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02058DBC
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0205536C
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02055374
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02055514
FUN_02055514: ; 0x02055514
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r7, r2, #0x0
	add r5, r0, #0x0
	add r4, r3, #0x0
	bl FUN_020553A0
	add r1, r6, #0x0
	mov r2, #0x0
	add r3, r7, #0x0
	str r4, [sp, #0x0]
	bl FUN_02058E28
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0205536C
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02055374
	pop {r3-r7, pc}

	thumb_func_start FUN_02055540
FUN_02055540: ; 0x02055540
	push {r4-r5, lr}
	sub sp, #0xc
	add r5, r1, #0x0
	bl FUN_020553A0
	add r4, r0, #0x0
	add r1, sp, #0x0
	bl FUN_02058B5C
	add r0, r4, #0x0
	add r1, sp, #0x0
	str r5, [sp, #0x4]
	bl FUN_02058B6C
	add sp, #0xc
	pop {r4-r5, pc}

	thumb_func_start FUN_02055560
FUN_02055560: ; 0x02055560
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_020553A0
	cmp r4, #0x1
	bne _02055574
	mov r1, #0x0
	bl FUN_02058960
	pop {r4, pc}
_02055574:
	mov r1, #0x1
	bl FUN_02058960
	pop {r4, pc}

	thumb_func_start FUN_0205557C
FUN_0205557C: ; 0x0205557C
	push {r3-r5, lr}
	add r5, r1, #0x0
	bl FUN_020553A0
	add r4, r0, #0x0
	cmp r5, #0x1
	bne _02055598
	mov r1, #0x0
	bl FUN_02058960
	add r0, r4, #0x0
	bl FUN_02059D1C
	pop {r3-r5, pc}
_02055598:
	mov r1, #0x1
	bl FUN_02058960
	pop {r3-r5, pc}

	thumb_func_start FUN_020555A0
FUN_020555A0: ; 0x020555A0
	push {r3, lr}
	cmp r1, #0x0
	bne _020555F2
	cmp r0, #0x9
	bhi _0205563E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020555B6: ; jump table (using 16-bit offset)
	.short _020555CA - _020555B6 - 2; case 0
	.short _020555CE - _020555B6 - 2; case 1
	.short _020555D2 - _020555B6 - 2; case 2
	.short _020555D6 - _020555B6 - 2; case 3
	.short _020555DA - _020555B6 - 2; case 4
	.short _020555DE - _020555B6 - 2; case 5
	.short _020555E2 - _020555B6 - 2; case 6
	.short _020555E6 - _020555B6 - 2; case 7
	.short _020555EA - _020555B6 - 2; case 8
	.short _020555EE - _020555B6 - 2; case 9
_020555CA:
	mov r0, #0x0
	pop {r3, pc}
_020555CE:
	mov r0, #0x15
	pop {r3, pc}
_020555D2:
	mov r0, #0xb2
	pop {r3, pc}
_020555D6:
	mov r0, #0xb0
	pop {r3, pc}
_020555DA:
	mov r0, #0xb4
	pop {r3, pc}
_020555DE:
	mov r0, #0xba
	pop {r3, pc}
_020555E2:
	mov r0, #0xbc
	pop {r3, pc}
_020555E6:
	mov r0, #0xc4
	pop {r3, pc}
_020555EA:
	mov r0, #0xc6
	pop {r3, pc}
_020555EE:
	mov r0, #0xc8
	pop {r3, pc}
_020555F2:
	cmp r0, #0x9
	bhi _0205563E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02055602: ; jump table (using 16-bit offset)
	.short _02055616 - _02055602 - 2; case 0
	.short _0205561A - _02055602 - 2; case 1
	.short _0205561E - _02055602 - 2; case 2
	.short _02055622 - _02055602 - 2; case 3
	.short _02055626 - _02055602 - 2; case 4
	.short _0205562A - _02055602 - 2; case 5
	.short _0205562E - _02055602 - 2; case 6
	.short _02055632 - _02055602 - 2; case 7
	.short _02055636 - _02055602 - 2; case 8
	.short _0205563A - _02055602 - 2; case 9
_02055616:
	mov r0, #0x61
	pop {r3, pc}
_0205561A:
	mov r0, #0x62
	pop {r3, pc}
_0205561E:
	mov r0, #0xb3
	pop {r3, pc}
_02055622:
	mov r0, #0xb1
	pop {r3, pc}
_02055626:
	mov r0, #0xb5
	pop {r3, pc}
_0205562A:
	mov r0, #0xbb
	pop {r3, pc}
_0205562E:
	mov r0, #0xbd
	pop {r3, pc}
_02055632:
	mov r0, #0xc5
	pop {r3, pc}
_02055636:
	mov r0, #0xc7
	pop {r3, pc}
_0205563A:
	mov r0, #0xc9
	pop {r3, pc}
_0205563E:
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02055648
FUN_02055648: ; 0x02055648
	push {r3, lr}
	cmp r0, #0x9
	bhi _02055690
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0205565A: ; jump table (using 16-bit offset)
	.short _0205566E - _0205565A - 2; case 0
	.short _02055672 - _0205565A - 2; case 1
	.short _02055676 - _0205565A - 2; case 2
	.short _02055690 - _0205565A - 2; case 3
	.short _0205567A - _0205565A - 2; case 4
	.short _02055690 - _0205565A - 2; case 5
	.short _0205567E - _0205565A - 2; case 6
	.short _02055682 - _0205565A - 2; case 7
	.short _02055686 - _0205565A - 2; case 8
	.short _0205568A - _0205565A - 2; case 9
_0205566E:
	mov r0, #0x1
	pop {r3, pc}
_02055672:
	mov r0, #0x2
	pop {r3, pc}
_02055676:
	mov r0, #0x4
	pop {r3, pc}
_0205567A:
	mov r0, #0x10
	pop {r3, pc}
_0205567E:
	mov r0, #0x20
	pop {r3, pc}
_02055682:
	mov r0, #0x40
	pop {r3, pc}
_02055686:
	mov r0, #0x80
	pop {r3, pc}
_0205568A:
	mov r0, #0x1
	lsl r0, r0, #0x8
	pop {r3, pc}
_02055690:
	bl GF_AssertFail
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_02055698
FUN_02055698: ; 0x02055698
	ldr r0, [r0, #0x38]
	bx lr

	thumb_func_start FUN_0205569C
FUN_0205569C: ; 0x0205569C
	push {r3, lr}
	cmp r1, #0x1
	bne _020556AA
	mov r1, #0x1
	bl FUN_020553EC
	pop {r3, pc}
_020556AA:
	mov r1, #0x1
	bl FUN_020553F4
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020556B4
FUN_020556B4: ; 0x020556B4
	push {r3, lr}
	mov r1, #0x1
	bl FUN_02055400
	cmp r0, #0x0
	beq _020556C4
	mov r0, #0x1
	pop {r3, pc}
_020556C4:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_020556C8
FUN_020556C8: ; 0x020556C8
	push {r3, lr}
	cmp r1, #0x1
	bne _020556D6
	mov r1, #0x2
	bl FUN_020553EC
	pop {r3, pc}
_020556D6:
	mov r1, #0x2
	bl FUN_020553F4
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020556E0
FUN_020556E0: ; 0x020556E0
	push {r3, lr}
	mov r1, #0x2
	bl FUN_02055400
	cmp r0, #0x0
	beq _020556F0
	mov r0, #0x1
	pop {r3, pc}
_020556F0:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_020556F4
FUN_020556F4: ; 0x020556F4
	push {r3, lr}
	cmp r1, #0x1
	bne _02055702
	mov r1, #0x4
	bl FUN_020553EC
	pop {r3, pc}
_02055702:
	mov r1, #0x4
	bl FUN_020553F4
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205570C
FUN_0205570C: ; 0x0205570C
	push {r3, lr}
	mov r1, #0x4
	bl FUN_02055400
	cmp r0, #0x0
	beq _0205571C
	mov r0, #0x1
	pop {r3, pc}
_0205571C:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02055720
FUN_02055720: ; 0x02055720
	push {r3, lr}
	cmp r1, #0x1
	bne _0205572E
	mov r1, #0x8
	bl FUN_020553EC
	pop {r3, pc}
_0205572E:
	mov r1, #0x8
	bl FUN_020553F4
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02055738
FUN_02055738: ; 0x02055738
	push {r3, lr}
	mov r1, #0x8
	bl FUN_02055400
	cmp r0, #0x0
	beq _02055748
	mov r0, #0x1
	pop {r3, pc}
_02055748:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0205574C
FUN_0205574C: ; 0x0205574C
	push {r3, lr}
	cmp r1, #0x1
	bne _0205575A
	mov r1, #0x10
	bl FUN_020553EC
	pop {r3, pc}
_0205575A:
	mov r1, #0x10
	bl FUN_020553F4
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02055764
FUN_02055764: ; 0x02055764
	push {r3, lr}
	mov r1, #0x10
	bl FUN_02055400
	cmp r0, #0x0
	beq _02055774
	mov r0, #0x1
	pop {r3, pc}
_02055774:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02055778
FUN_02055778: ; 0x02055778
	push {r3, lr}
	cmp r1, #0x1
	bne _02055786
	mov r1, #0x20
	bl FUN_020553EC
	pop {r3, pc}
_02055786:
	mov r1, #0x20
	bl FUN_020553F4
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02055790
FUN_02055790: ; 0x02055790
	push {r3, lr}
	mov r1, #0x20
	bl FUN_02055400
	cmp r0, #0x0
	beq _020557A0
	mov r0, #0x1
	pop {r3, pc}
_020557A0:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_020557A4
FUN_020557A4: ; 0x020557A4
	ldr r3, _020557AC ; =FUN_020553EC
	mov r1, #0x40
	bx r3
	nop
_020557AC: .word FUN_020553EC

	thumb_func_start FUN_020557B0
FUN_020557B0: ; 0x020557B0
	ldr r3, _020557B8 ; =FUN_020553F4
	mov r1, #0x40
	bx r3
	nop
_020557B8: .word FUN_020553F4

	thumb_func_start FUN_020557BC
FUN_020557BC: ; 0x020557BC
	push {r3, lr}
	mov r1, #0x40
	bl FUN_02055400
	cmp r0, #0x0
	beq _020557CC
	mov r0, #0x1
	pop {r3, pc}
_020557CC:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_020557D0
FUN_020557D0: ; 0x020557D0
	push {r3, lr}
	cmp r1, #0x1
	bne _020557DE
	mov r1, #0x80
	bl FUN_020553EC
	pop {r3, pc}
_020557DE:
	mov r1, #0x80
	bl FUN_020553F4
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020557E8
FUN_020557E8: ; 0x020557E8
	ldr r3, _020557F0 ; =FUN_02055400
	mov r1, #0x80
	bx r3
	nop
_020557F0: .word FUN_02055400
