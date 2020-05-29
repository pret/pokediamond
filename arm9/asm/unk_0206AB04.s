    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0206AB04
FUN_0206AB04: ; 0x0206AB04
	push {r3, lr}
	mov r1, #0x75
	lsl r1, r1, #0x6
	mov r2, #0x0
	str r1, [sp, #0x0]
	mov r1, #0x9
	add r3, r2, #0x0
	bl ReadFromNarcMemberByIdPair
	pop {r3, pc}

	thumb_func_start FUN_0206AB18
FUN_0206AB18: ; 0x0206AB18
	push {r4, lr}
	sub sp, #0x10
	add r4, r1, #0x0
	add r1, sp, #0x0
	bl FUN_0206ABB4
	add r0, sp, #0x0
	add r1, r4, #0x0
	bl FUN_0206AB58
	add sp, #0x10
	pop {r4, pc}

	thumb_func_start FUN_0206AB30
FUN_0206AB30: ; 0x0206AB30
	push {r3-r5, lr}
	add r5, r1, #0x0
	cmp r5, #0x3
	bls _0206AB3A
	mov r5, #0x3
_0206AB3A:
	mov r1, #0x5
	bl FUN_0206AB18
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	mov r0, #0x14
	mul r0, r4
	mul r0, r5
	mov r1, #0x64
	bl _s32_div_f
	add r0, r4, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3-r5, pc}

	thumb_func_start FUN_0206AB58
FUN_0206AB58: ; 0x0206AB58
	cmp r1, #0xb
	bhi _0206ABB0
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0206AB68: ; jump table (using 16-bit offset)
	.short _0206AB80 - _0206AB68 - 2; case 0
	.short _0206AB84 - _0206AB68 - 2; case 1
	.short _0206AB88 - _0206AB68 - 2; case 2
	.short _0206AB8C - _0206AB68 - 2; case 3
	.short _0206AB90 - _0206AB68 - 2; case 4
	.short _0206AB94 - _0206AB68 - 2; case 5
	.short _0206AB98 - _0206AB68 - 2; case 6
	.short _0206AB9C - _0206AB68 - 2; case 7
	.short _0206ABA0 - _0206AB68 - 2; case 8
	.short _0206ABA6 - _0206AB68 - 2; case 9
	.short _0206ABAA - _0206AB68 - 2; case 10
	.short _0206ABAE - _0206AB68 - 2; case 11
_0206AB80:
	ldrh r0, [r0, #0x0]
	bx lr
_0206AB84:
	ldrb r0, [r0, #0x2]
	bx lr
_0206AB88:
	ldrb r0, [r0, #0x3]
	bx lr
_0206AB8C:
	ldrb r0, [r0, #0x4]
	bx lr
_0206AB90:
	ldrb r0, [r0, #0x5]
	bx lr
_0206AB94:
	ldrb r0, [r0, #0x6]
	bx lr
_0206AB98:
	ldrb r0, [r0, #0x7]
	bx lr
_0206AB9C:
	ldrh r0, [r0, #0x8]
	bx lr
_0206ABA0:
	mov r1, #0xa
	ldrsb r0, [r0, r1]
	bx lr
_0206ABA6:
	ldrb r0, [r0, #0xb]
	bx lr
_0206ABAA:
	ldrb r0, [r0, #0xc]
	bx lr
_0206ABAE:
	ldrb r0, [r0, #0xd]
_0206ABB0:
	bx lr
	.balign 4

	thumb_func_start FUN_0206ABB4
FUN_0206ABB4: ; 0x0206ABB4
	ldr r3, _0206ABC0 ; =ReadWholeNarcMemberByIdPair
	add r2, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x9
	bx r3
	nop
_0206ABC0: .word ReadWholeNarcMemberByIdPair
