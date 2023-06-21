	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start sub_020142EC
sub_020142EC: ; 0x020142EC
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	ldr r0, _02014394 ; =sub_020143DC
	mov r1, #0x50
	mov r2, #0x0
	bl sub_020061E8
	str r0, [sp, #0x4]
	bl sub_0201B6C8
	add r4, r0, #0x0
	cmp r5, #0x0
	beq _02014330
	cmp r6, #0x0
	bne _02014320
	add r0, r5, #0x0
	mov r1, #0x0
	bl PaletteData_GetUnfadedBuf
	str r0, [sp, #0x0]
	ldr r0, _02014398 ; =sub_020144E0
	str r0, [r4, #0x4]
	b _0201434A
_02014320:
	add r0, r5, #0x0
	mov r1, #0x1
	bl PaletteData_GetUnfadedBuf
	str r0, [sp, #0x0]
	ldr r0, _0201439C ; =sub_020144FC
	str r0, [r4, #0x4]
	b _0201434A
_02014330:
	cmp r6, #0x0
	bne _02014340
	bl sub_020222E8
	str r0, [sp, #0x0]
	ldr r0, _020143A0 ; =sub_020144B0
	str r0, [r4, #0x4]
	b _0201434A
_02014340:
	bl sub_020222F8
	str r0, [sp, #0x0]
	ldr r0, _020143A4 ; =sub_020144C8
	str r0, [r4, #0x4]
_0201434A:
	ldr r1, [sp, #0x0]
	lsl r0, r7, #0x5
	str r0, [sp, #0x8]
	add r0, r1, r0
	add r1, r4, #0x0
	add r1, #0xc
	mov r2, #0x20
	bl MIi_CpuCopy16
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x8]
	mov r2, #0x20
	add r0, r1, r0
	add r1, r4, #0x0
	add r1, #0x2c
	bl MIi_CpuCopy16
	ldr r0, [sp, #0x4]
	mov r1, #0x1
	str r0, [r4, #0x0]
	add r0, r4, #0x0
	str r5, [r4, #0x8]
	add r0, #0x4c
	strb r6, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x4d
	strb r7, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x4e
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x4f
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02014394: .word sub_020143DC
_02014398: .word sub_020144E0
_0201439C: .word sub_020144FC
_020143A0: .word sub_020144B0
_020143A4: .word sub_020144C8

	thumb_func_start sub_020143A8
sub_020143A8: ; 0x020143A8
	cmp r1, #0x0
	beq _020143B6
	cmp r1, #0x1
	beq _020143BE
	cmp r1, #0x2
	beq _020143C6
	bx lr
_020143B6:
	mov r1, #0x0
	add r0, #0x4e
	strb r1, [r0, #0x0]
	bx lr
_020143BE:
	mov r1, #0x2
	add r0, #0x4e
	strb r1, [r0, #0x0]
	bx lr
_020143C6:
	mov r1, #0x3
	add r0, #0x4e
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_020143D0
sub_020143D0: ; 0x020143D0
	ldr r3, _020143D8 ; =sub_0200621C
	ldr r0, [r0, #0x0]
	bx r3
	nop
_020143D8: .word sub_0200621C

	thumb_func_start sub_020143DC
sub_020143DC: ; 0x020143DC
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x4e
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	bhi _02014452
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020143F8: ; jump table (using 16-bit offset)
	.short _02014400 - _020143F8 - 2; case 0
	.short _02014410 - _020143F8 - 2; case 1
	.short _02014452 - _020143F8 - 2; case 2
	.short _02014444 - _020143F8 - 2; case 3
_02014400:
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x4f
	strb r1, [r0, #0x0]
	mov r0, #0x1
	add r4, #0x4e
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
_02014410:
	add r0, r4, #0x0
	bl sub_02014454
	cmp r0, #0x1
	bne _02014424
	add r1, r4, #0x0
	ldr r2, [r4, #0x4]
	add r0, r4, #0x0
	add r1, #0x2c
	blx r2
_02014424:
	add r0, r4, #0x0
	add r0, #0x4f
	ldrb r0, [r0, #0x0]
	add r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x4f
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x4f
	ldrb r0, [r0, #0x0]
	cmp r0, #0x20
	bne _02014452
	mov r0, #0x0
	add r4, #0x4f
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
_02014444:
	ldr r2, [r4, #0x4]
	add r0, r4, #0x0
	add r1, #0xc
	blx r2
	add r0, r5, #0x0
	bl sub_0200621C
_02014452:
	pop {r3-r5, pc}

	thumb_func_start sub_02014454
sub_02014454: ; 0x02014454
	push {r4-r5}
	add r1, r0, #0x0
	add r1, #0x4f
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02014482
	mov r1, #0x1e
	mov r4, #0x0
	mov r3, #0x1
	lsl r1, r1, #0xa
_02014468:
	add r2, r3, #0x0
	lsl r2, r4
	tst r2, r1
	beq _02014474
	ldrh r2, [r0, #0xc]
	strh r2, [r0, #0x2c]
_02014474:
	add r4, r4, #0x1
	add r0, r0, #0x2
	cmp r4, #0x10
	blo _02014468
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_02014482:
	cmp r1, #0x18
	bne _020144AA
	mov r1, #0x1e
	mov r5, #0x0
	add r4, r0, #0x0
	mov r3, #0x1
	lsl r1, r1, #0xa
_02014490:
	add r2, r3, #0x0
	lsl r2, r5
	tst r2, r1
	beq _0201449C
	ldrh r2, [r0, #0x2a]
	strh r2, [r4, #0x2c]
_0201449C:
	add r5, r5, #0x1
	add r4, r4, #0x2
	cmp r5, #0x10
	blo _02014490
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_020144AA:
	mov r0, #0x0
	pop {r4-r5}
	bx lr

	thumb_func_start sub_020144B0
sub_020144B0: ; 0x020144B0
	push {r3, lr}
	add r3, r0, #0x0
	add r3, #0x4d
	ldrb r3, [r3, #0x0]
	mov r0, #0x0
	mov r2, #0x20
	lsl r3, r3, #0x15
	lsr r3, r3, #0x10
	bl BG_LoadPlttData
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_020144C8
sub_020144C8: ; 0x020144C8
	push {r3, lr}
	add r3, r0, #0x0
	add r3, #0x4d
	ldrb r3, [r3, #0x0]
	mov r0, #0x4
	mov r2, #0x20
	lsl r3, r3, #0x15
	lsr r3, r3, #0x10
	bl BG_LoadPlttData
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_020144E0
sub_020144E0: ; 0x020144E0
	push {r3, lr}
	add r3, r0, #0x0
	mov r0, #0x20
	str r0, [sp, #0x0]
	ldr r0, [r3, #0x8]
	add r3, #0x4d
	ldrb r3, [r3, #0x0]
	mov r2, #0x0
	lsl r3, r3, #0x14
	lsr r3, r3, #0x10
	bl PaletteData_LoadPalette
	pop {r3, pc}
	.balign 4
