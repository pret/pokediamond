	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F7380
UNK_020F7380: ; 0x020F7380
	.word sub_0205EAB0, sub_0205EAE0

	.global UNK_020F7388
UNK_020F7388: ; 0x020F7388
	.word sub_0205E554, sub_0205E598

	.global UNK_020F7390
UNK_020F7390: ; 0x020F7390
	.word sub_0205E768, sub_0205E7A4

	.global UNK_020F7398
UNK_020F7398: ; 0x020F7398
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00, 0x00, 0x00

	.global UNK_020F73A4
UNK_020F73A4: ; 0x020F73A4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00, 0x00, 0x00

	.text

	thumb_func_start sub_0205E4EC
sub_0205E4EC: ; 0x0205E4EC
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x8
	bl sub_0205858C
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl sub_0205E5B4
	add r0, r4, #0x0
	mov r1, #0x0
	bl sub_02058544
	add r0, r4, #0x0
	bl MapObject_ClearSingleMovement
	add r0, r4, #0x0
	mov r1, #0x0
	bl MapObject_ClearFlag18
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0205E518
sub_0205E518: ; 0x0205E518
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl sub_020585B0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0205E5B4
	cmp r0, #0x0
	beq _0205E548
	add r0, r5, #0x0
	mov r1, #0x0
	bl MapObject_ClearFlag18
	ldr r6, _0205E54C ; =UNK_020F7388
_0205E538:
	ldrb r2, [r4, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	ldr r2, [r6, r2]
	blx r2
	cmp r0, #0x1
	beq _0205E538
_0205E548:
	pop {r4-r6, pc}
	nop
_0205E54C: .word UNK_020F7388

	thumb_func_start sub_0205E550
sub_0205E550: ; 0x0205E550
	bx lr
	.balign 4

	thumb_func_start sub_0205E554
sub_0205E554: ; 0x0205E554
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl MapObject_ClearSingleMovement
	add r0, r5, #0x0
	bl MapObject_ClearFlag3
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0205E608
	cmp r0, #0x1
	bne _0205E592
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0205E63C
	add r0, r5, #0x0
	bl sub_0205E698
	cmp r0, #0x1
	bne _0205E592
	add r0, r5, #0x0
	bl MapObject_SetSingleMovement
	ldrb r0, [r4, #0x0]
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
_0205E592:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0205E598
sub_0205E598: ; 0x0205E598
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl sub_0205B080
	cmp r0, #0x1
	bne _0205E5B0
	add r0, r5, #0x0
	bl MapObject_ClearSingleMovement
	mov r0, #0x0
	strb r0, [r4, #0x0]
_0205E5B0:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start sub_0205E5B4
sub_0205E5B4: ; 0x0205E5B4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl MapObject_GetManager
	bl sub_020552A4
	cmp r0, #0x0
	bne _0205E5CC
	mov r0, #0x0
	strb r0, [r4, #0x1]
	pop {r3-r5, pc}
_0205E5CC:
	ldrb r0, [r4, #0x1]
	cmp r0, #0x0
	bne _0205E5DA
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0205E5E0
_0205E5DA:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0205E5E0
sub_0205E5E0: ; 0x0205E5E0
	push {r3-r5, lr}
	add r5, r1, #0x0
	bl MapObject_GetFieldSystem
	bl sub_02055698
	mov r1, #0x1
	add r4, r0, #0x0
	strb r1, [r5, #0x1]
	bl GetPlayerXCoord
	strh r0, [r5, #0x2]
	add r0, r4, #0x0
	bl GetPlayerYCoord
	strh r0, [r5, #0x4]
	mov r0, #0xff
	strh r0, [r5, #0x6]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0205E608
sub_0205E608: ; 0x0205E608
	push {r4-r6, lr}
	add r5, r1, #0x0
	bl MapObject_GetFieldSystem
	bl sub_02055698
	add r6, r0, #0x0
	beq _0205E638
	bl GetPlayerXCoord
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl GetPlayerYCoord
	mov r1, #0x2
	ldrsh r1, [r5, r1]
	cmp r4, r1
	bne _0205E634
	mov r1, #0x4
	ldrsh r1, [r5, r1]
	cmp r0, r1
	beq _0205E638
_0205E634:
	mov r0, #0x1
	pop {r4-r6, pc}
_0205E638:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start sub_0205E63C
sub_0205E63C: ; 0x0205E63C
	push {r3-r5, lr}
	add r5, r1, #0x0
	bl MapObject_GetFieldSystem
	bl sub_02055698
	add r4, r0, #0x0
	bl GetPlayerXCoord
	strh r0, [r5, #0x2]
	add r0, r4, #0x0
	bl GetPlayerYCoord
	strh r0, [r5, #0x4]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0205E65C
sub_0205E65C: ; 0x0205E65C
	push {r3, lr}
	bl MapObject_GetFieldSystem
	bl sub_02055698
	bl sub_02055464
	add r1, r0, #0x0
	sub r1, #0x58
	cmp r1, #0x3
	bhi _0205E694
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0205E67E: ; jump table (using 16-bit offset)
	.short _0205E686 - _0205E67E - 2; case 0
	.short _0205E68A - _0205E67E - 2; case 1
	.short _0205E68E - _0205E67E - 2; case 2
	.short _0205E692 - _0205E67E - 2; case 3
_0205E686:
	mov r0, #0x10
	pop {r3, pc}
_0205E68A:
	mov r0, #0x11
	pop {r3, pc}
_0205E68E:
	mov r0, #0x12
	pop {r3, pc}
_0205E692:
	mov r0, #0x13
_0205E694:
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_0205E698
sub_0205E698: ; 0x0205E698
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl MapObject_GetFieldSystem
	bl sub_02055698
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_GetCurrentX
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl MapObject_GetCurrentZ
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl sub_02055338
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl sub_02055344
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	cmp r0, r6
	bne _0205E6D2
	cmp r7, r4
	beq _0205E6FA
_0205E6D2:
	add r0, r5, #0x0
	bl sub_0205E65C
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x0]
	add r1, r7, #0x0
	add r2, r6, #0x0
	add r3, r4, #0x0
	bl sub_02059E80
	ldr r1, [sp, #0x4]
	bl sub_0205AFDC
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl sub_0205AE0C
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_0205E6FA:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start sub_0205E700
sub_0205E700: ; 0x0205E700
	push {r3-r5, lr}
	mov r1, #0xc
	add r5, r0, #0x0
	bl sub_0205858C
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0205E854
	add r0, r5, #0x0
	mov r1, #0x0
	bl sub_02058544
	add r0, r5, #0x0
	bl MapObject_ClearSingleMovement
	mov r0, #0x0
	strb r0, [r4, #0x1]
	pop {r3-r5, pc}

	thumb_func_start sub_0205E728
sub_0205E728: ; 0x0205E728
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl sub_020585B0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0205E854
	cmp r0, #0x0
	beq _0205E750
	ldr r6, _0205E754 ; =UNK_020F7390
_0205E740:
	ldrb r2, [r4, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	ldr r2, [r6, r2]
	blx r2
	cmp r0, #0x1
	beq _0205E740
_0205E750:
	pop {r4-r6, pc}
	nop
_0205E754: .word UNK_020F7390

	thumb_func_start sub_0205E758
sub_0205E758: ; 0x0205E758
	bx lr
	.balign 4

	thumb_func_start sub_0205E75C
sub_0205E75C: ; 0x0205E75C
	push {r3, lr}
	bl sub_020585B0
	mov r1, #0x0
	strb r1, [r0, #0x1]
	pop {r3, pc}

	thumb_func_start sub_0205E768
sub_0205E768: ; 0x0205E768
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl MapObject_ClearSingleMovement
	add r0, r5, #0x0
	bl MapObject_ClearFlag3
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0205E8F4
	cmp r0, #0x1
	bne _0205E7A0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0205E940
	cmp r0, #0x1
	bne _0205E7A0
	add r0, r5, #0x0
	bl MapObject_SetSingleMovement
	ldrb r0, [r4, #0x0]
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
_0205E7A0:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start sub_0205E7A4
sub_0205E7A4: ; 0x0205E7A4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl sub_0205B080
	cmp r0, #0x0
	bne _0205E7B6
	mov r0, #0x0
	pop {r3-r5, pc}
_0205E7B6:
	add r0, r5, #0x0
	bl MapObject_ClearSingleMovement
	mov r0, #0x0
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0205E7C4
sub_0205E7C4: ; 0x0205E7C4
	push {r4-r7, lr}
	sub sp, #0xc
	mov r1, #0x0
	add r4, r0, #0x0
	str r1, [sp, #0x8]
	bl MapObject_GetType
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl MapObject_GetMapID
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl sub_0205C9E8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl MapObject_GetManager
	ldr r1, [sp, #0x0]
	add r7, r0, #0x0
	cmp r1, #0x8
	bhi _0205E84C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0205E7FE: ; jump table (using 16-bit offset)
	.short _0205E84C - _0205E7FE - 2; case 0
	.short _0205E810 - _0205E7FE - 2; case 1
	.short _0205E810 - _0205E7FE - 2; case 2
	.short _0205E810 - _0205E7FE - 2; case 3
	.short _0205E810 - _0205E7FE - 2; case 4
	.short _0205E810 - _0205E7FE - 2; case 5
	.short _0205E810 - _0205E7FE - 2; case 6
	.short _0205E810 - _0205E7FE - 2; case 7
	.short _0205E810 - _0205E7FE - 2; case 8
_0205E810:
	add r1, sp, #0x4
	add r2, sp, #0x8
	mov r3, #0x1
	bl MapObjectManager_GetNextObjectWithFlagFromIndex
	cmp r0, #0x1
	bne _0205E84C
_0205E81E:
	ldr r0, [sp, #0x4]
	cmp r4, r0
	beq _0205E83C
	bl MapObject_GetMapID
	cmp r6, r0
	bne _0205E83C
	ldr r0, [sp, #0x4]
	bl sub_0205C9E8
	cmp r5, r0
	bne _0205E83C
	ldr r0, [sp, #0x4]
	add sp, #0xc
	pop {r4-r7, pc}
_0205E83C:
	add r0, r7, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x8
	mov r3, #0x1
	bl MapObjectManager_GetNextObjectWithFlagFromIndex
	cmp r0, #0x1
	beq _0205E81E
_0205E84C:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start sub_0205E854
sub_0205E854: ; 0x0205E854
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	bl MapObject_GetManager
	add r4, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl MapObject_GetMapID
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl sub_0205C9E8
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x8
	mov r3, #0x1
	bl MapObjectManager_GetNextObjectWithFlagFromIndex
	cmp r0, #0x1
	bne _0205E8C6
_0205E886:
	ldr r0, [sp, #0x4]
	cmp r5, r0
	beq _0205E8B6
	bl MapObject_GetMapID
	cmp r7, r0
	bne _0205E8B6
	ldr r0, [sp, #0x4]
	bl sub_0205C9E8
	cmp r6, r0
	bne _0205E8B6
	ldr r0, [sp, #0x0]
	ldrb r0, [r0, #0x1]
	cmp r0, #0x0
	bne _0205E8B0
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	add r0, r5, #0x0
	bl sub_0205E8D0
_0205E8B0:
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_0205E8B6:
	add r0, r4, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x8
	mov r3, #0x1
	bl MapObjectManager_GetNextObjectWithFlagFromIndex
	cmp r0, #0x1
	beq _0205E886
_0205E8C6:
	ldr r1, [sp, #0x0]
	mov r0, #0x0
	strb r0, [r1, #0x1]
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start sub_0205E8D0
sub_0205E8D0: ; 0x0205E8D0
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r0, #0x1
	add r4, r2, #0x0
	strb r0, [r5, #0x1]
	add r0, r4, #0x0
	bl MapObject_GetCurrentX
	strh r0, [r5, #0x2]
	add r0, r4, #0x0
	bl MapObject_GetCurrentZ
	strh r0, [r5, #0x4]
	mov r0, #0xff
	strh r0, [r5, #0x6]
	str r4, [r5, #0x8]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0205E8F4
sub_0205E8F4: ; 0x0205E8F4
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r5, [r1, #0x8]
	bl MapObject_GetCurrentX
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl MapObject_GetCurrentZ
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_GetPreviousX
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_GetPreviousZ
	cmp r4, r7
	bne _0205E91E
	cmp r6, r0
	beq _0205E93A
_0205E91E:
	add r0, r5, #0x0
	bl MapObject_CheckSingleMovement
	cmp r0, #0x1
	beq _0205E936
	mov r1, #0x61
	add r0, r5, #0x0
	lsl r1, r1, #0x6
	bl MapObject_GetFlagsBitsMask
	cmp r0, #0x0
	bne _0205E93A
_0205E936:
	mov r0, #0x1
	pop {r3-r7, pc}
_0205E93A:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_0205E940
sub_0205E940: ; 0x0205E940
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	add r5, r1, #0x0
	bl MapObject_GetCurrentX
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	bl MapObject_GetCurrentZ
	add r6, r0, #0x0
	ldr r0, [r5, #0x8]
	bl MapObject_GetCurrentX
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x8]
	bl MapObject_GetCurrentZ
	add r7, r0, #0x0
	ldr r0, [r5, #0x8]
	bl MapObject_GetPreviousX
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x8]
	bl MapObject_GetPreviousZ
	add r3, r0, #0x0
	ldr r0, [sp, #0x8]
	cmp r4, r0
	bne _0205E986
	cmp r6, r7
	bne _0205E986
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_0205E986:
	ldr r2, [sp, #0x4]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl sub_02059E80
	add r5, r0, #0x0
	bl sub_02059BF4
	add r4, r4, r0
	add r0, r5, #0x0
	bl sub_02059C00
	add r1, r6, r0
	ldr r0, [sp, #0x8]
	cmp r4, r0
	bne _0205E9AA
	cmp r1, r7
	beq _0205E9C0
_0205E9AA:
	add r0, r5, #0x0
	mov r1, #0xc
	bl sub_0205AFDC
	add r1, r0, #0x0
	ldr r0, [sp, #0x0]
	bl sub_0205AE0C
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_0205E9C0:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start sub_0205E9C8
sub_0205E9C8: ; 0x0205E9C8
	push {r4-r5, lr}
	sub sp, #0xc
	add r5, r1, #0x0
	add r4, r0, #0x0
	mov r1, #0x8
	bl sub_0205858C
	strb r5, [r0, #0x1]
	add r0, r4, #0x0
	mov r1, #0x0
	bl sub_02058544
	add r0, r4, #0x0
	bl MapObject_ClearSingleMovement
	mov r1, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0x14
	bl MapObject_SetFlagsBits
	ldr r5, _0205EA0C ; =UNK_020F7398
	add r3, sp, #0x0
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	add r1, r2, #0x0
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	bl sub_02058B94
	add sp, #0xc
	pop {r4-r5, pc}
	nop
_0205EA0C: .word UNK_020F7398

	thumb_func_start sub_0205EA10
sub_0205EA10: ; 0x0205EA10
	ldr r3, _0205EA18 ; =sub_0205E9C8
	mov r1, #0x0
	bx r3
	nop
_0205EA18: .word sub_0205E9C8

	thumb_func_start sub_0205EA1C
sub_0205EA1C: ; 0x0205EA1C
	ldr r3, _0205EA24 ; =sub_0205E9C8
	mov r1, #0x1
	bx r3
	nop
_0205EA24: .word sub_0205E9C8

	thumb_func_start sub_0205EA28
sub_0205EA28: ; 0x0205EA28
	ldr r3, _0205EA30 ; =sub_0205E9C8
	mov r1, #0x2
	bx r3
	nop
_0205EA30: .word sub_0205E9C8

	thumb_func_start sub_0205EA34
sub_0205EA34: ; 0x0205EA34
	ldr r3, _0205EA3C ; =sub_0205E9C8
	mov r1, #0x3
	bx r3
	nop
_0205EA3C: .word sub_0205E9C8

	thumb_func_start sub_0205EA40
sub_0205EA40: ; 0x0205EA40
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl sub_020585B0
	ldr r6, _0205EA60 ; =UNK_020F7380
	add r4, r0, #0x0
_0205EA4C:
	ldrb r2, [r4, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	ldr r2, [r6, r2]
	blx r2
	cmp r0, #0x1
	beq _0205EA4C
	pop {r4-r6, pc}
	nop
_0205EA60: .word UNK_020F7380

	thumb_func_start sub_0205EA64
sub_0205EA64: ; 0x0205EA64
	push {r3, lr}
	bl sub_0205EB20
	cmp r0, #0x0
	beq _0205EA72
	bl ov05_021E4DE4
_0205EA72:
	pop {r3, pc}

	thumb_func_start sub_0205EA74
sub_0205EA74: ; 0x0205EA74
	push {r4-r5, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	bl sub_020585B0
	add r5, r0, #0x0
	mov r1, #0x0
	strb r1, [r5, #0x0]
	add r0, r4, #0x0
	bl sub_0205EB14
	ldrb r0, [r5, #0x2]
	cmp r0, #0x0
	bne _0205EAA6
	ldr r5, _0205EAAC ; =UNK_020F73A4
	add r3, sp, #0x0
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	add r1, r2, #0x0
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	bl sub_02058B94
_0205EAA6:
	add sp, #0xc
	pop {r4-r5, pc}
	nop
_0205EAAC: .word UNK_020F73A4

	thumb_func_start sub_0205EAB0
sub_0205EAB0: ; 0x0205EAB0
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldrb r1, [r4, #0x2]
	add r5, r0, #0x0
	cmp r1, #0x0
	bne _0205EACA
	ldrb r1, [r4, #0x1]
	bl ov06_0224CECC
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl sub_0205EB14
_0205EACA:
	add r0, r5, #0x0
	bl MapObject_ClearSingleMovement
	add r0, r5, #0x0
	bl MapObject_ClearFlag3
	ldrb r0, [r4, #0x0]
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start sub_0205EAE0
sub_0205EAE0: ; 0x0205EAE0
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldrb r1, [r4, #0x2]
	add r5, r0, #0x0
	cmp r1, #0x0
	bne _0205EB0E
	bl sub_0205EB20
	cmp r0, #0x0
	bne _0205EB0E
	add r0, r5, #0x0
	bl sub_02058934
	cmp r0, #0x1
	bne _0205EB0E
	ldrb r1, [r4, #0x1]
	add r0, r5, #0x0
	bl ov06_0224CECC
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl sub_0205EB14
_0205EB0E:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0205EB14
sub_0205EB14: ; 0x0205EB14
	push {r4, lr}
	add r4, r1, #0x0
	bl sub_020585B0
	str r4, [r0, #0x4]
	pop {r4, pc}

	thumb_func_start sub_0205EB20
sub_0205EB20: ; 0x0205EB20
	push {r3, lr}
	bl sub_020585B0
	ldr r0, [r0, #0x4]
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_0205EB2C
sub_0205EB2C: ; 0x0205EB2C
	push {r3, lr}
	bl sub_020585B0
	mov r1, #0x1
	strb r1, [r0, #0x2]
	pop {r3, pc}
