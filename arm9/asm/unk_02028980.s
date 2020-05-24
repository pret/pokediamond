	.include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020EE964
UNK_020EE964: ; 0x020EE964
	.byte 0xF6, 0x00, 0x00, 0x00, 0x2F, 0x00

	.global UNK_020EE96A
UNK_020EE96A: ; 0x020EE96A
	.byte 0x00, 0x00, 0x3B, 0x01, 0x00, 0x00, 0x43, 0x00, 0x01, 0x00, 0x3C, 0x01, 0x00, 0x00, 0x7A, 0x00
	.byte 0x03, 0x00, 0x3D, 0x01, 0x00, 0x00, 0x85, 0x00, 0x02, 0x00, 0x3E, 0x01, 0x00, 0x00, 0x58, 0x00
	.byte 0x04, 0x00, 0x3F, 0x01, 0x00, 0x00, 0xA7, 0x00, 0x06, 0x00, 0xFA, 0x00, 0x00, 0x00, 0x23, 0x00
	.byte 0x05, 0x00, 0x40, 0x01, 0x00, 0x00, 0x9A, 0x00, 0x07, 0x00

	.global UNK_020EE9A4
UNK_020EE9A4: ; 0x020EE9A4
	.byte 0x5A, 0x00, 0x00, 0x00

	.global UNK_020EE9A8
UNK_020EE9A8: ; 0x020EE9A8
	.byte 0x01, 0x00, 0x00, 0x00, 0x5B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x5D, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x5E, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x61, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x69, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x6A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6B, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6D, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_02028980
FUN_02028980: ; 0x02028980
	mov r0, #0x46
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_02028988
FUN_02028988: ; 0x02028988
	ldr r3, _02028990 ; =memset
	mov r1, #0x0
	mov r2, #0x70
	bx r3
	.balign 4
_02028990: .word memset

	thumb_func_start FUN_02028994
FUN_02028994: ; 0x02028994
	ldr r3, _020289A0 ; =memset
	mov r2, #0x46
	mov r1, #0x0
	lsl r2, r2, #0x4
	bx r3
	nop
_020289A0: .word memset

	thumb_func_start FUN_020289A4
FUN_020289A4: ; 0x020289A4
	ldr r3, _020289AC ; =FUN_02022610
	mov r1, #0x12
	bx r3
	nop
_020289AC: .word FUN_02022610

	thumb_func_start FUN_020289B0
FUN_020289B0: ; 0x020289B0
	push {r3-r7, lr}
	sub sp, #0x10
	add r7, r0, #0x0
	cmp r1, #0x1
	beq _020289C0
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_020289C0:
	add r0, sp, #0x0
	bl FUN_020126B4
	ldr r0, [r7, #0x0]
	lsl r1, r0, #0x15
	lsr r3, r1, #0x1c
	beq _02028A18
	lsl r1, r0, #0x19
	lsr r2, r1, #0x19
	ldr r1, [sp, #0x0]
	cmp r2, r1
	bne _020289F2
	ldr r1, [sp, #0x4]
	cmp r3, r1
	bne _020289F2
	lsl r1, r0, #0xd
	lsr r2, r1, #0x1b
	ldr r1, [sp, #0x8]
	cmp r2, r1
	bne _020289F2
	lsl r0, r0, #0x12
	lsr r1, r0, #0x1d
	ldr r0, [sp, #0xc]
	cmp r1, r0
	beq _02028A18
_020289F2:
	mov r0, #0x3f
	lsl r0, r0, #0x4
	mov r5, #0x9
	add r6, r7, r0
_020289FA:
	add r4, r6, #0x0
	sub r4, #0x70
	add r3, r6, #0x0
	mov r2, #0xe
_02028A02:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02028A02
	sub r5, r5, #0x1
	sub r6, #0x70
	cmp r5, #0x1
	bge _020289FA
	add r0, r7, #0x0
	bl FUN_02028988
_02028A18:
	add r0, r7, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02028A20
FUN_02028A20: ; 0x02028A20
	push {r4, lr}
	sub sp, #0x20
	add r4, r0, #0x0
	cmp r1, #0x1
	beq _02028A30
	add sp, #0x20
	mov r0, #0x0
	pop {r4, pc}
_02028A30:
	add r0, sp, #0x0
	bl FUN_020126B4
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x19
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x15
	lsr r0, r0, #0x1c
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0xd
	lsr r0, r0, #0x1b
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x12
	lsr r0, r0, #0x1d
	str r0, [sp, #0x1c]
	add r0, sp, #0x0
	bl FUN_02012710
	add r4, r0, #0x0
	add r0, sp, #0x10
	bl FUN_02012710
	ldr r2, [sp, #0x4]
	sub r0, r4, r0
	cmp r2, #0xc
	bne _02028A7E
	ldr r1, [sp, #0x8]
	cmp r1, #0x1f
	bne _02028A7E
	ldr r1, [sp, #0x14]
	cmp r1, #0x1
	bne _02028A7E
	ldr r1, [sp, #0x18]
	cmp r1, #0x1
	beq _02028A94
_02028A7E:
	cmp r2, #0x1
	bne _02028AAC
	ldr r1, [sp, #0x8]
	cmp r1, #0x1
	bne _02028AAC
	ldr r1, [sp, #0x14]
	cmp r1, #0xc
	bne _02028AAC
	ldr r1, [sp, #0x18]
	cmp r1, #0x1f
	bne _02028AAC
_02028A94:
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x10]
	sub r1, r1, r0
	cmp r1, #0x2
	bge _02028AA6
	mov r0, #0x1
	mvn r0, r0
	cmp r1, r0
	bgt _02028ACC
_02028AA6:
	add sp, #0x20
	mov r0, #0x1
	pop {r4, pc}
_02028AAC:
	mov r1, #0x1
	mvn r1, r1
	cmp r0, r1
	ble _02028AB8
	cmp r0, #0x2
	blt _02028ABE
_02028AB8:
	add sp, #0x20
	mov r0, #0x1
	pop {r4, pc}
_02028ABE:
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x10]
	cmp r1, r0
	beq _02028ACC
	add sp, #0x20
	mov r0, #0x1
	pop {r4, pc}
_02028ACC:
	mov r0, #0x0
	add sp, #0x20
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02028AD4
FUN_02028AD4: ; 0x02028AD4
	push {r4, lr}
	add r4, r1, #0x0
	cmp r0, #0x0
	beq _02028B12
	cmp r2, #0x4
	bhi _02028B12
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02028AEC: ; jump table (using 16-bit offset)
	.short _02028AF6 - _02028AEC - 2; case 0
	.short _02028AFC - _02028AEC - 2; case 1
	.short _02028B02 - _02028AEC - 2; case 2
	.short _02028B08 - _02028AEC - 2; case 3
	.short _02028B0E - _02028AEC - 2; case 4
_02028AF6:
	bl FUN_02028B1C
	b _02028B12
_02028AFC:
	bl FUN_02028B5C
	b _02028B12
_02028B02:
	bl FUN_02028BF0
	b _02028B12
_02028B08:
	bl FUN_02028BFC
	b _02028B12
_02028B0E:
	bl FUN_02028C08
_02028B12:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02028B1C
FUN_02028B1C: ; 0x02028B1C
	push {r4-r5}
	ldr r3, [r0, #0x0]
	lsl r2, r3, #0x19
	lsr r5, r2, #0x19
	ldr r2, [r1, #0x0]
	lsl r4, r2, #0x19
	lsr r4, r4, #0x19
	cmp r5, r4
	bne _02028B52
	lsl r4, r3, #0x15
	lsr r5, r4, #0x1c
	lsl r4, r2, #0x15
	lsr r4, r4, #0x1c
	cmp r5, r4
	bne _02028B52
	lsl r4, r3, #0xd
	lsr r5, r4, #0x1b
	lsl r4, r2, #0xd
	lsr r4, r4, #0x1b
	cmp r5, r4
	bne _02028B52
	lsl r3, r3, #0x12
	lsl r2, r2, #0x12
	lsr r3, r3, #0x1d
	lsr r2, r2, #0x1d
	cmp r3, r2
	beq _02028B56
_02028B52:
	ldr r1, [r1, #0x0]
	str r1, [r0, #0x0]
_02028B56:
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_02028B5C
FUN_02028B5C: ; 0x02028B5C
	push {r3, lr}
	ldrb r2, [r1, #0x0]
	cmp r2, #0x23
	bhi _02028BEE
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02028B70: ; jump table (using 16-bit offset)
	.short _02028BEE - _02028B70 - 2; case 0
	.short _02028BB8 - _02028B70 - 2; case 1
	.short _02028BB8 - _02028B70 - 2; case 2
	.short _02028BB8 - _02028B70 - 2; case 3
	.short _02028BB8 - _02028B70 - 2; case 4
	.short _02028BB8 - _02028B70 - 2; case 5
	.short _02028BB8 - _02028B70 - 2; case 6
	.short _02028BB8 - _02028B70 - 2; case 7
	.short _02028BB8 - _02028B70 - 2; case 8
	.short _02028BC0 - _02028B70 - 2; case 9
	.short _02028BC0 - _02028B70 - 2; case 10
	.short _02028BC8 - _02028B70 - 2; case 11
	.short _02028BD0 - _02028B70 - 2; case 12
	.short _02028BD8 - _02028B70 - 2; case 13
	.short _02028BD8 - _02028B70 - 2; case 14
	.short _02028BD8 - _02028B70 - 2; case 15
	.short _02028BB8 - _02028B70 - 2; case 16
	.short _02028BB8 - _02028B70 - 2; case 17
	.short _02028BE0 - _02028B70 - 2; case 18
	.short _02028BE8 - _02028B70 - 2; case 19
	.short _02028BE8 - _02028B70 - 2; case 20
	.short _02028BE8 - _02028B70 - 2; case 21
	.short _02028BE8 - _02028B70 - 2; case 22
	.short _02028BE8 - _02028B70 - 2; case 23
	.short _02028BE8 - _02028B70 - 2; case 24
	.short _02028BE8 - _02028B70 - 2; case 25
	.short _02028BE8 - _02028B70 - 2; case 26
	.short _02028BE8 - _02028B70 - 2; case 27
	.short _02028BE8 - _02028B70 - 2; case 28
	.short _02028BE8 - _02028B70 - 2; case 29
	.short _02028BE8 - _02028B70 - 2; case 30
	.short _02028BEE - _02028B70 - 2; case 31
	.short _02028BE8 - _02028B70 - 2; case 32
	.short _02028BE8 - _02028B70 - 2; case 33
	.short _02028BB8 - _02028B70 - 2; case 34
	.short _02028BB8 - _02028B70 - 2; case 35
_02028BB8:
	add r0, r0, #0x4
	bl FUN_02028CE8
	pop {r3, pc}
_02028BC0:
	add r0, r0, #0x4
	bl FUN_02028D98
	pop {r3, pc}
_02028BC8:
	add r0, r0, #0x4
	bl FUN_02028D44
	pop {r3, pc}
_02028BD0:
	add r0, r0, #0x4
	bl FUN_02028D24
	pop {r3, pc}
_02028BD8:
	add r0, r0, #0x4
	bl FUN_02028DFC
	pop {r3, pc}
_02028BE0:
	add r0, r0, #0x4
	bl FUN_02028E44
	pop {r3, pc}
_02028BE8:
	add r0, r0, #0x4
	bl FUN_02028E8C
_02028BEE:
	pop {r3, pc}

	thumb_func_start FUN_02028BF0
FUN_02028BF0: ; 0x02028BF0
	ldrh r2, [r1, #0x0]
	strh r2, [r0, #0x14]
	ldrh r1, [r1, #0x2]
	strh r1, [r0, #0x16]
	bx lr
	.balign 4

	thumb_func_start FUN_02028BFC
FUN_02028BFC: ; 0x02028BFC
	ldrh r2, [r1, #0x0]
	strh r2, [r0, #0x18]
	ldrh r1, [r1, #0x2]
	strh r1, [r0, #0x1a]
	bx lr
	.balign 4

	thumb_func_start FUN_02028C08
FUN_02028C08: ; 0x02028C08
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	bl FUN_02028CA8
	ldrb r1, [r4, #0x0]
	cmp r1, #0x10
	bhi _02028C6E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02028C24: ; jump table (using 16-bit offset)
	.short _02028C6E - _02028C24 - 2; case 0
	.short _02028C46 - _02028C24 - 2; case 1
	.short _02028C46 - _02028C24 - 2; case 2
	.short _02028C46 - _02028C24 - 2; case 3
	.short _02028C46 - _02028C24 - 2; case 4
	.short _02028C46 - _02028C24 - 2; case 5
	.short _02028C4E - _02028C24 - 2; case 6
	.short _02028C56 - _02028C24 - 2; case 7
	.short _02028C5E - _02028C24 - 2; case 8
	.short _02028C56 - _02028C24 - 2; case 9
	.short _02028C5E - _02028C24 - 2; case 10
	.short _02028C46 - _02028C24 - 2; case 11
	.short _02028C5E - _02028C24 - 2; case 12
	.short _02028C68 - _02028C24 - 2; case 13
	.short _02028C5E - _02028C24 - 2; case 14
	.short _02028C56 - _02028C24 - 2; case 15
	.short _02028C5E - _02028C24 - 2; case 16
_02028C46:
	add r1, r4, #0x0
	bl FUN_02028ED4
	pop {r3-r5, pc}
_02028C4E:
	add r1, r4, #0x0
	bl FUN_02028F10
	pop {r3-r5, pc}
_02028C56:
	add r1, r4, #0x0
	bl FUN_02028F2C
	pop {r3-r5, pc}
_02028C5E:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02028F60
	pop {r3-r5, pc}
_02028C68:
	add r1, r4, #0x0
	bl FUN_02028F94
_02028C6E:
	pop {r3-r5, pc}

	thumb_func_start FUN_02028C70
FUN_02028C70: ; 0x02028C70
	push {r3-r4}
	mov r3, #0x0
	add r4, r0, #0x0
	mov r1, #0x3f
_02028C78:
	ldr r2, [r4, #0x0]
	tst r2, r1
	bne _02028C86
	lsl r1, r3, #0x2
	add r0, r0, r1
	pop {r3-r4}
	bx lr
_02028C86:
	add r3, r3, #0x1
	add r4, r4, #0x4
	cmp r3, #0x4
	blo _02028C78
	mov r3, #0x0
	add r2, r0, #0x0
_02028C92:
	ldr r1, [r2, #0x4]
	add r3, r3, #0x1
	stmia r2!, {r1}
	cmp r3, #0x3
	blo _02028C92
	lsl r2, r3, #0x2
	mov r1, #0x0
	str r1, [r0, r2]
	add r0, r0, r2
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02028CA8
FUN_02028CA8: ; 0x02028CA8
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	add r2, r4, #0x0
_02028CB0:
	ldrb r0, [r2, #0x1c]
	cmp r0, #0x0
	bne _02028CC0
	mov r0, #0x2a
	add r4, #0x1c
	mul r0, r1
	add r0, r4, r0
	pop {r4, pc}
_02028CC0:
	add r1, r1, #0x1
	add r2, #0x2a
	cmp r1, #0x2
	blo _02028CB0
	add r0, r4, #0x0
	add r1, r4, #0x0
	add r0, #0x1c
	add r1, #0x46
	mov r2, #0x2a
	bl memcpy
	add r4, #0x46
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x2a
	bl memset
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02028CE8
FUN_02028CE8: ; 0x02028CE8
	push {r4, lr}
	add r4, r1, #0x0
	mov r2, #0x0
	add r3, r0, #0x0
_02028CF0:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	beq _02028CFE
	add r2, r2, #0x1
	add r3, r3, #0x4
	cmp r2, #0x4
	blo _02028CF0
_02028CFE:
	cmp r2, #0x0
	beq _02028D14
	lsl r2, r2, #0x2
	add r2, r0, r2
	sub r2, r2, #0x4
	ldr r3, [r2, #0x0]
	mov r2, #0x3f
	ldrb r1, [r4, #0x0]
	and r2, r3
	cmp r1, r2
	beq _02028D20
_02028D14:
	bl FUN_02028C70
	ldrb r2, [r4, #0x0]
	mov r1, #0x3f
	and r1, r2
	str r1, [r0, #0x0]
_02028D20:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02028D24
FUN_02028D24: ; 0x02028D24
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02028C70
	ldrb r2, [r4, #0x0]
	mov r1, #0x3f
	and r1, r2
	ldrh r2, [r4, #0x2]
	lsl r3, r2, #0x10
	ldrh r2, [r4, #0x4]
	lsl r2, r2, #0x16
	lsr r2, r2, #0x10
	orr r2, r3
	orr r1, r2
	str r1, [r0, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02028D44
FUN_02028D44: ; 0x02028D44
	push {r3-r5, lr}
	add r4, r1, #0x0
	mov r2, #0x0
	mov r3, #0x3f
_02028D4C:
	lsl r1, r2, #0x2
	ldr r5, [r0, r1]
	and r5, r3
	cmp r5, #0xb
	bne _02028D72
	mov r3, #0x0
	str r3, [r0, r1]
	cmp r2, #0x3
	bhs _02028D7C
_02028D5E:
	lsl r3, r2, #0x2
	add r1, r0, r3
	ldr r1, [r1, #0x4]
	str r1, [r0, r3]
	add r1, r2, #0x1
	lsl r1, r1, #0x10
	lsr r2, r1, #0x10
	cmp r2, #0x3
	blo _02028D5E
	b _02028D7C
_02028D72:
	add r1, r2, #0x1
	lsl r1, r1, #0x10
	lsr r2, r1, #0x10
	cmp r2, #0x4
	blo _02028D4C
_02028D7C:
	bl FUN_02028C70
	ldrb r2, [r4, #0x0]
	mov r1, #0x3f
	and r1, r2
	ldrh r2, [r4, #0x2]
	lsl r3, r2, #0x10
	ldrh r2, [r4, #0x4]
	lsl r2, r2, #0x16
	lsr r2, r2, #0x10
	orr r2, r3
	orr r1, r2
	str r1, [r0, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02028D98
FUN_02028D98: ; 0x02028D98
	push {r4-r6, lr}
	add r4, r1, #0x0
	mov r6, #0x0
	mov r1, #0x3f
_02028DA0:
	lsl r5, r6, #0x2
	ldr r3, [r0, r5]
	add r2, r3, #0x0
	and r2, r1
	cmp r2, #0x9
	bne _02028DD4
	lsr r3, r3, #0x10
	lsl r3, r3, #0x10
	ldrh r2, [r4, #0x2]
	lsr r3, r3, #0x10
	cmp r2, r3
	bne _02028DD4
	mov r1, #0x0
	str r1, [r0, r5]
	cmp r6, #0x3
	bhs _02028DDE
_02028DC0:
	lsl r2, r6, #0x2
	add r1, r0, r2
	ldr r1, [r1, #0x4]
	str r1, [r0, r2]
	add r1, r6, #0x1
	lsl r1, r1, #0x10
	lsr r6, r1, #0x10
	cmp r6, #0x3
	blo _02028DC0
	b _02028DDE
_02028DD4:
	add r2, r6, #0x1
	lsl r2, r2, #0x10
	lsr r6, r2, #0x10
	cmp r6, #0x4
	blo _02028DA0
_02028DDE:
	bl FUN_02028C70
	ldrb r2, [r4, #0x0]
	mov r1, #0x3f
	and r1, r2
	ldrh r2, [r4, #0x2]
	lsl r3, r2, #0x10
	ldrh r2, [r4, #0x4]
	lsl r2, r2, #0x16
	lsr r2, r2, #0x10
	orr r2, r3
	orr r1, r2
	str r1, [r0, #0x0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02028DFC
FUN_02028DFC: ; 0x02028DFC
	push {r4, lr}
	add r4, r1, #0x0
	mov r2, #0x0
	add r3, r0, #0x0
_02028E04:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	beq _02028E12
	add r2, r2, #0x1
	add r3, r3, #0x4
	cmp r2, #0x4
	blo _02028E04
_02028E12:
	cmp r2, #0x0
	beq _02028E30
	lsl r1, r2, #0x2
	add r1, r0, r1
	sub r1, r1, #0x4
	ldr r3, [r1, #0x0]
	mov r1, #0x3f
	ldrb r2, [r4, #0x0]
	and r1, r3
	cmp r2, r1
	bne _02028E30
	ldrh r2, [r4, #0x2]
	lsr r1, r3, #0x10
	cmp r2, r1
	beq _02028E42
_02028E30:
	bl FUN_02028C70
	ldrh r1, [r4, #0x2]
	ldrb r2, [r4, #0x0]
	lsl r3, r1, #0x10
	mov r1, #0x3f
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x0]
_02028E42:
	pop {r4, pc}

	thumb_func_start FUN_02028E44
FUN_02028E44: ; 0x02028E44
	push {r4, lr}
	add r4, r1, #0x0
	mov r2, #0x0
	add r3, r0, #0x0
_02028E4C:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	beq _02028E5A
	add r2, r2, #0x1
	add r3, r3, #0x4
	cmp r2, #0x4
	blo _02028E4C
_02028E5A:
	cmp r2, #0x0
	beq _02028E78
	lsl r1, r2, #0x2
	add r1, r0, r1
	sub r1, r1, #0x4
	ldr r3, [r1, #0x0]
	mov r1, #0x3f
	ldrb r2, [r4, #0x0]
	and r1, r3
	cmp r2, r1
	bne _02028E78
	ldrh r2, [r4, #0x6]
	lsr r1, r3, #0x10
	cmp r2, r1
	beq _02028E8A
_02028E78:
	bl FUN_02028C70
	ldrh r1, [r4, #0x6]
	ldrb r2, [r4, #0x0]
	lsl r3, r1, #0x10
	mov r1, #0x3f
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x0]
_02028E8A:
	pop {r4, pc}

	thumb_func_start FUN_02028E8C
FUN_02028E8C: ; 0x02028E8C
	push {r4, lr}
	add r4, r1, #0x0
	mov r2, #0x0
	add r3, r0, #0x0
_02028E94:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	beq _02028EA2
	add r2, r2, #0x1
	add r3, r3, #0x4
	cmp r2, #0x4
	blo _02028E94
_02028EA2:
	cmp r2, #0x0
	beq _02028EC0
	lsl r1, r2, #0x2
	add r1, r0, r1
	sub r1, r1, #0x4
	ldr r3, [r1, #0x0]
	mov r1, #0x3f
	ldrb r2, [r4, #0x0]
	and r1, r3
	cmp r2, r1
	bne _02028EC0
	ldrh r2, [r4, #0x2]
	lsr r1, r3, #0x10
	cmp r2, r1
	beq _02028ED2
_02028EC0:
	bl FUN_02028C70
	ldrh r1, [r4, #0x2]
	ldrb r2, [r4, #0x0]
	lsl r3, r1, #0x10
	mov r1, #0x3f
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x0]
_02028ED2:
	pop {r4, pc}

	thumb_func_start FUN_02028ED4
FUN_02028ED4: ; 0x02028ED4
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldrb r0, [r4, #0x0]
	strb r0, [r5, #0x0]
	ldrb r3, [r4, #0x1]
	lsl r1, r3, #0x1c
	lsr r2, r1, #0x1a
	lsl r1, r3, #0x1b
	lsr r1, r1, #0x1f
	lsl r0, r3, #0x1a
	lsl r1, r1, #0x1
	orr r1, r2
	lsr r0, r0, #0x1f
	orr r0, r1
	strb r0, [r5, #0x1]
	add r0, r4, #0x2
	add r1, r5, #0x2
	mov r2, #0x8
	bl FUN_020292D4
	add r4, #0x12
	add r5, #0x12
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x8
	bl FUN_020292D4
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02028F10
FUN_02028F10: ; 0x02028F10
	add r2, r0, #0x0
	ldrb r0, [r1, #0x0]
	ldr r3, _02028F28 ; =FUN_020292D4
	strb r0, [r2, #0x0]
	ldrb r0, [r1, #0x1]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	strb r0, [r2, #0x1]
	add r0, r1, #0x2
	add r1, r2, #0x2
	mov r2, #0x8
	bx r3
	.balign 4
_02028F28: .word FUN_020292D4

	thumb_func_start FUN_02028F2C
FUN_02028F2C: ; 0x02028F2C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldrb r0, [r4, #0x0]
	mov r2, #0x8
	strb r0, [r5, #0x0]
	ldrb r0, [r4, #0x1]
	lsl r1, r0, #0x1b
	lsr r1, r1, #0x1f
	lsl r0, r0, #0x18
	lsl r1, r1, #0x2
	lsr r0, r0, #0x1e
	orr r0, r1
	strb r0, [r5, #0x1]
	add r0, r4, #0x2
	add r1, r5, #0x2
	bl FUN_020292D4
	add r4, #0x22
	add r5, #0x12
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0xc
	bl FUN_020292D4
	pop {r3-r5, pc}

	thumb_func_start FUN_02028F60
FUN_02028F60: ; 0x02028F60
	push {r4, lr}
	add r4, r1, #0x0
	mov r3, #0x0
	add r2, r0, #0x0
_02028F68:
	ldrb r1, [r2, #0x1c]
	cmp r1, #0x0
	beq _02028F76
	add r3, r3, #0x1
	add r2, #0x2a
	cmp r3, #0x2
	blo _02028F68
_02028F76:
	cmp r3, #0x0
	beq _02028F8A
	mov r1, #0x2a
	mul r1, r3
	add r1, r0, r1
	sub r1, #0xe
	ldrb r2, [r4, #0x0]
	ldrb r1, [r1, #0x0]
	cmp r2, r1
	beq _02028F92
_02028F8A:
	bl FUN_02028CA8
	ldrb r1, [r4, #0x0]
	strb r1, [r0, #0x0]
_02028F92:
	pop {r4, pc}

	thumb_func_start FUN_02028F94
FUN_02028F94: ; 0x02028F94
	ldrb r2, [r1, #0x0]
	strb r2, [r0, #0x0]
	ldrb r1, [r1, #0x1]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	strb r1, [r0, #0x1]
	bx lr
	.balign 4

	thumb_func_start FUN_02028FA4
FUN_02028FA4: ; 0x02028FA4
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x4
	bl FUN_02016998
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl FUN_020126B4
	ldr r2, [r4, #0x0]
	mov r0, #0x7f
	bic r2, r0
	ldr r1, [sp, #0x0]
	mov r0, #0x7f
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	str r1, [r4, #0x0]
	add r2, r1, #0x0
	ldr r1, [sp, #0x4]
	ldr r0, _02029008 ; =0xFFFFF87F
	lsl r1, r1, #0x1c
	and r2, r0
	lsr r1, r1, #0x15
	orr r2, r1
	ldr r1, _0202900C ; =0xFFF83FFF
	str r2, [r4, #0x0]
	and r2, r1
	ldr r1, [sp, #0x8]
	lsr r0, r0, #0xd
	lsl r1, r1, #0x1b
	lsr r1, r1, #0xd
	orr r2, r1
	ldr r1, _02029010 ; =0xFFFFC7FF
	str r2, [r4, #0x0]
	and r2, r1
	ldr r1, [sp, #0xc]
	lsl r1, r1, #0x1d
	lsr r1, r1, #0x12
	orr r1, r2
	and r1, r0
	lsl r0, r5, #0x13
	orr r0, r1
	str r0, [r4, #0x0]
	add r0, r4, #0x0
	add sp, #0x10
	pop {r3-r5, pc}
	nop
_02029008: .word 0xFFFFF87F
_0202900C: .word 0xFFF83FFF
_02029010: .word 0xFFFFC7FF

	thumb_func_start FUN_02029014
FUN_02029014: ; 0x02029014
	push {r3, lr}
	mov r1, #0x8
	bl FUN_02016998
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	strb r1, [r0, #0x4]
	strb r1, [r0, #0x5]
	strb r1, [r0, #0x6]
	strb r1, [r0, #0x7]
	pop {r3, pc}

	thumb_func_start FUN_02029030
FUN_02029030: ; 0x02029030
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x1
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_0202903C
FUN_0202903C: ; 0x0202903C
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x2
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029048
FUN_02029048: ; 0x02029048
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x3
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029054
FUN_02029054: ; 0x02029054
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x4
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029060
FUN_02029060: ; 0x02029060
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x5
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_0202906C
FUN_0202906C: ; 0x0202906C
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x6
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029078
FUN_02029078: ; 0x02029078
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x7
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029084
FUN_02029084: ; 0x02029084
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x8
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029090
FUN_02029090: ; 0x02029090
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02029014
	mov r1, #0x9
	strb r1, [r0, #0x0]
	strh r4, [r0, #0x2]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020290A4
FUN_020290A4: ; 0x020290A4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r2, #0x0
	add r4, r1, #0x0
	bl FUN_02029014
	mov r1, #0xa
	strb r1, [r0, #0x0]
	strh r5, [r0, #0x2]
	strh r4, [r0, #0x4]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020290BC
FUN_020290BC: ; 0x020290BC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02029014
	mov r1, #0xb
	strb r1, [r0, #0x0]
	strh r4, [r0, #0x4]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020290D0
FUN_020290D0: ; 0x020290D0
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02029014
	mov r1, #0xc
	strb r1, [r0, #0x0]
	strh r4, [r0, #0x4]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020290E4
FUN_020290E4: ; 0x020290E4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02029014
	mov r1, #0xd
	strb r1, [r0, #0x0]
	strh r4, [r0, #0x2]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020290F8
FUN_020290F8: ; 0x020290F8
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02029014
	mov r1, #0xe
	strb r1, [r0, #0x0]
	strh r4, [r0, #0x2]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202910C
FUN_0202910C: ; 0x0202910C
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02029014
	mov r1, #0xf
	strb r1, [r0, #0x0]
	strh r4, [r0, #0x2]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02029120
FUN_02029120: ; 0x02029120
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x10
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_0202912C
FUN_0202912C: ; 0x0202912C
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x11
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029138
FUN_02029138: ; 0x02029138
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02029014
	mov r1, #0x12
	strb r1, [r0, #0x0]
	strh r4, [r0, #0x6]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202914C
FUN_0202914C: ; 0x0202914C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r2, #0x0
	add r4, r1, #0x0
	bl FUN_02029014
	add r5, #0x13
	strb r5, [r0, #0x0]
	strh r4, [r0, #0x2]
	pop {r3-r5, pc}

	thumb_func_start FUN_02029160
FUN_02029160: ; 0x02029160
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x22
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_0202916C
FUN_0202916C: ; 0x0202916C
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x23
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029178
FUN_02029178: ; 0x02029178
	push {r3, lr}
	mov r1, #0x4
	bl FUN_02016998
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	pop {r3, pc}

	thumb_func_start FUN_0202918C
FUN_0202918C: ; 0x0202918C
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x18]
	add r5, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_02029178
	add r4, r0, #0x0
	mov r0, #0x1
	strb r0, [r4, #0x0]
	strh r5, [r4, #0x2]
	ldrb r1, [r4, #0x1]
	mov r0, #0xc0
	bic r1, r0
	lsl r0, r6, #0x1e
	lsr r0, r0, #0x18
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0x3c
	bic r1, r0
	lsl r0, r7, #0x1c
	lsr r0, r0, #0x1a
	orr r0, r1
	strb r0, [r4, #0x1]
	ldr r0, [sp, #0x0]
	bl FUN_02029EC0
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	beq _020291DA
	cmp r0, #0x2
	beq _020291DA
	cmp r0, #0x4
	bne _020291E4
_020291DA:
	ldrb r1, [r4, #0x1]
	mov r0, #0x3
	bic r1, r0
	strb r1, [r4, #0x1]
	b _02029206
_020291E4:
	cmp r0, #0x1
	beq _020291EC
	cmp r0, #0x3
	bne _020291FA
_020291EC:
	ldrb r1, [r4, #0x1]
	mov r0, #0x3
	bic r1, r0
	mov r0, #0x1
	orr r0, r1
	strb r0, [r4, #0x1]
	b _02029206
_020291FA:
	ldrb r1, [r4, #0x1]
	mov r0, #0x3
	bic r1, r0
	mov r0, #0x2
	orr r0, r1
	strb r0, [r4, #0x1]
_02029206:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202920C
FUN_0202920C: ; 0x0202920C
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x18]
	add r5, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_02029178
	add r4, r0, #0x0
	mov r0, #0x2
	strb r0, [r4, #0x0]
	strh r5, [r4, #0x2]
	ldrb r1, [r4, #0x1]
	mov r0, #0xc0
	bic r1, r0
	lsl r0, r6, #0x1e
	lsr r0, r0, #0x18
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0x3c
	bic r1, r0
	lsl r0, r7, #0x1c
	lsr r0, r0, #0x1a
	orr r0, r1
	strb r0, [r4, #0x1]
	ldr r0, [sp, #0x0]
	bl FUN_02029EC0
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x1
	beq _0202925C
	cmp r0, #0x3
	beq _0202925C
	cmp r0, #0x5
	bne _02029266
_0202925C:
	ldrb r1, [r4, #0x1]
	mov r0, #0x3
	bic r1, r0
	strb r1, [r4, #0x1]
	b _02029288
_02029266:
	cmp r0, #0x2
	beq _0202926E
	cmp r0, #0x4
	bne _0202927C
_0202926E:
	ldrb r1, [r4, #0x1]
	mov r0, #0x3
	bic r1, r0
	mov r0, #0x1
	orr r0, r1
	strb r0, [r4, #0x1]
	b _02029288
_0202927C:
	ldrb r1, [r4, #0x1]
	mov r0, #0x3
	bic r1, r0
	mov r0, #0x2
	orr r0, r1
	strb r0, [r4, #0x1]
_02029288:
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0202928C
FUN_0202928C: ; 0x0202928C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r0, r2, #0x0
	mov r1, #0x4
	bl FUN_02016998
	ldrh r2, [r0, #0x0]
	mov r1, #0x1
	bic r2, r1
	mov r1, #0x1
	orr r1, r2
	strh r1, [r0, #0x0]
	strh r5, [r0, #0x2]
	ldrh r2, [r0, #0x0]
	ldr r1, _020292B8 ; =0xFFFF0001
	and r2, r1
	lsl r1, r4, #0x11
	lsr r1, r1, #0x10
	orr r1, r2
	strh r1, [r0, #0x0]
	pop {r3-r5, pc}
	.balign 4
_020292B8: .word 0xFFFF0001

	thumb_func_start FUN_020292BC
FUN_020292BC: ; 0x020292BC
	push {r4, lr}
	mov r1, #0x3a
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x3a
	add r4, r0, #0x0
	bl memset
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020292D4
FUN_020292D4: ; 0x020292D4
	push {r4-r5}
	mov r4, #0x0
	cmp r2, #0x0
	bls _020292EA
	ldr r3, _02029308 ; =0x0000FFFF
	add r5, r1, #0x0
_020292E0:
	add r4, r4, #0x1
	strh r3, [r5, #0x0]
	add r5, r5, #0x2
	cmp r4, r2
	blo _020292E0
_020292EA:
	mov r5, #0x0
	cmp r2, #0x0
	bls _02029304
	ldr r3, _02029308 ; =0x0000FFFF
_020292F2:
	ldrh r4, [r0, #0x0]
	cmp r4, r3
	beq _02029304
	add r5, r5, #0x1
	strh r4, [r1, #0x0]
	add r0, r0, #0x2
	add r1, r1, #0x2
	cmp r5, r2
	blo _020292F2
_02029304:
	pop {r4-r5}
	bx lr
	.balign 4
_02029308: .word 0x0000FFFF

	thumb_func_start FUN_0202930C
FUN_0202930C: ; 0x0202930C
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, r3, #0x0
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_020292BC
	add r4, r0, #0x0
	mov r0, #0x1
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	mov r1, #0xf
	mov r2, #0x8
	bic r0, r1
	mov r1, #0xf
	and r1, r6
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0x10
	bic r1, r0
	lsl r0, r5, #0x1f
	lsr r0, r0, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r7, #0x0
	add r1, r4, #0x2
	bl FUN_020292D4
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202934C
FUN_0202934C: ; 0x0202934C
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, r3, #0x0
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_020292BC
	add r4, r0, #0x0
	mov r0, #0x2
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	mov r1, #0xf
	mov r2, #0x8
	bic r0, r1
	mov r1, #0xf
	and r1, r6
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0x10
	bic r1, r0
	lsl r0, r5, #0x1f
	lsr r0, r0, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r7, #0x0
	add r1, r4, #0x2
	bl FUN_020292D4
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202938C
FUN_0202938C: ; 0x0202938C
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, [sp, #0x1c]
	str r1, [sp, #0x0]
	add r5, r2, #0x0
	add r6, r3, #0x0
	bl FUN_020292BC
	add r4, r0, #0x0
	mov r0, #0x3
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	mov r1, #0xf
	bic r0, r1
	add r1, sp, #0x8
	ldrb r2, [r1, #0x10]
	mov r1, #0xf
	and r1, r2
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r0, [r4, #0x1]
	mov r1, #0x10
	mov r2, #0x8
	bic r0, r1
	lsl r1, r5, #0x1f
	lsr r1, r1, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0x20
	bic r1, r0
	lsl r0, r6, #0x1f
	lsr r0, r0, #0x1a
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r7, #0x0
	add r1, r4, #0x2
	bl FUN_020292D4
	add r1, r4, #0x0
	ldr r0, [sp, #0x0]
	add r1, #0x12
	mov r2, #0x8
	bl FUN_020292D4
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020293EC
FUN_020293EC: ; 0x020293EC
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, r3, #0x0
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_020292BC
	add r4, r0, #0x0
	mov r0, #0x4
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	mov r1, #0xf
	mov r2, #0x8
	bic r0, r1
	mov r1, #0xf
	and r1, r6
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0x10
	bic r1, r0
	lsl r0, r5, #0x1f
	lsr r0, r0, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r7, #0x0
	add r1, r4, #0x2
	bl FUN_020292D4
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202942C
FUN_0202942C: ; 0x0202942C
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r0, r2, #0x0
	add r5, r1, #0x0
	bl FUN_020292BC
	add r4, r0, #0x0
	mov r0, #0x6
	strb r0, [r4, #0x0]
	ldrb r1, [r4, #0x1]
	mov r0, #0x10
	mov r2, #0x8
	bic r1, r0
	lsl r0, r5, #0x1f
	lsr r0, r0, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r6, #0x0
	add r1, r4, #0x2
	bl FUN_020292D4
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0202945C
FUN_0202945C: ; 0x0202945C
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, [sp, #0x18]
	add r5, r1, #0x0
	str r2, [sp, #0x0]
	add r6, r3, #0x0
	bl FUN_020292BC
	add r4, r0, #0x0
	mov r0, #0x7
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	mov r1, #0x10
	mov r2, #0x8
	bic r0, r1
	lsl r1, r5, #0x1f
	lsr r1, r1, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0xc0
	bic r1, r0
	lsl r0, r6, #0x1e
	lsr r0, r0, #0x18
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r7, #0x0
	add r1, r4, #0x2
	bl FUN_020292D4
	add r1, r4, #0x0
	ldr r0, [sp, #0x0]
	add r1, #0x22
	mov r2, #0xc
	bl FUN_020292D4
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_020294A8
FUN_020294A8: ; 0x020294A8
	push {r3, lr}
	bl FUN_020292BC
	mov r1, #0x8
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_020294B4
FUN_020294B4: ; 0x020294B4
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, r3, #0x0
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_020292BC
	add r4, r0, #0x0
	mov r0, #0xb
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	mov r1, #0xf
	mov r2, #0x8
	bic r0, r1
	mov r1, #0xf
	and r1, r6
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0x10
	bic r1, r0
	lsl r0, r5, #0x1f
	lsr r0, r0, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r7, #0x0
	add r1, r4, #0x2
	bl FUN_020292D4
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020294F4
FUN_020294F4: ; 0x020294F4
	push {r3, lr}
	bl FUN_020292BC
	mov r1, #0xc
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029500
FUN_02029500: ; 0x02029500
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_020292BC
	mov r1, #0xd
	strb r1, [r0, #0x0]
	ldrb r2, [r0, #0x1]
	mov r1, #0xf
	bic r2, r1
	mov r1, #0xf
	and r1, r4
	orr r1, r2
	strb r1, [r0, #0x1]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02029520
FUN_02029520: ; 0x02029520
	push {r3, lr}
	bl FUN_020292BC
	mov r1, #0xe
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_0202952C
FUN_0202952C: ; 0x0202952C
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, [sp, #0x18]
	add r5, r1, #0x0
	str r2, [sp, #0x0]
	add r6, r3, #0x0
	bl FUN_020292BC
	add r4, r0, #0x0
	mov r0, #0xf
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	mov r1, #0x10
	mov r2, #0x8
	bic r0, r1
	lsl r1, r5, #0x1f
	lsr r1, r1, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0xc0
	bic r1, r0
	lsl r0, r6, #0x1e
	lsr r0, r0, #0x18
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r7, #0x0
	add r1, r4, #0x2
	bl FUN_020292D4
	add r1, r4, #0x0
	ldr r0, [sp, #0x0]
	add r1, #0x22
	mov r2, #0xc
	bl FUN_020292D4
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02029578
FUN_02029578: ; 0x02029578
	push {r3, lr}
	bl FUN_020292BC
	mov r1, #0x10
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029584
FUN_02029584: ; 0x02029584
	push {r3, lr}
	cmp r2, #0x4
	bhi _020295DA
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02029596: ; jump table (using 16-bit offset)
	.short _020295A0 - _02029596 - 2; case 0
	.short _020295AC - _02029596 - 2; case 1
	.short _020295B8 - _02029596 - 2; case 2
	.short _020295C4 - _02029596 - 2; case 3
	.short _020295D0 - _02029596 - 2; case 4
_020295A0:
	mov r2, #0x70
	mul r2, r3
	add r0, r0, r2
	bl FUN_020295DC
	pop {r3, pc}
_020295AC:
	mov r2, #0x70
	mul r2, r3
	add r0, r0, r2
	bl FUN_020295E4
	pop {r3, pc}
_020295B8:
	mov r2, #0x70
	mul r2, r3
	add r0, r0, r2
	bl FUN_02029690
	pop {r3, pc}
_020295C4:
	mov r2, #0x70
	mul r2, r3
	add r0, r0, r2
	bl FUN_0202969C
	pop {r3, pc}
_020295D0:
	mov r2, #0x70
	mul r2, r3
	add r0, r0, r2
	bl FUN_020296A8
_020295DA:
	pop {r3, pc}

	thumb_func_start FUN_020295DC
FUN_020295DC: ; 0x020295DC
	ldr r0, [r0, #0x0]
	str r0, [r1, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_020295E4
FUN_020295E4: ; 0x020295E4
	push {r3-r7, lr}
	mov r6, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r7, r6, #0x0
_020295EE:
	strb r7, [r4, #0x0]
	strb r7, [r4, #0x1]
	strb r7, [r4, #0x2]
	strb r7, [r4, #0x3]
	strb r7, [r4, #0x4]
	strb r7, [r4, #0x5]
	strb r7, [r4, #0x6]
	strb r7, [r4, #0x7]
	ldr r0, [r5, #0x4]
	mov r1, #0x3f
	and r1, r0
	cmp r1, #0x23
	bhi _02029682
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02029614: ; jump table (using 16-bit offset)
	.short _02029682 - _02029614 - 2; case 0
	.short _0202965C - _02029614 - 2; case 1
	.short _0202965C - _02029614 - 2; case 2
	.short _0202965C - _02029614 - 2; case 3
	.short _0202965C - _02029614 - 2; case 4
	.short _0202965C - _02029614 - 2; case 5
	.short _0202965C - _02029614 - 2; case 6
	.short _0202965C - _02029614 - 2; case 7
	.short _0202965C - _02029614 - 2; case 8
	.short _02029664 - _02029614 - 2; case 9
	.short _02029664 - _02029614 - 2; case 10
	.short _02029664 - _02029614 - 2; case 11
	.short _02029664 - _02029614 - 2; case 12
	.short _0202966C - _02029614 - 2; case 13
	.short _0202966C - _02029614 - 2; case 14
	.short _0202966C - _02029614 - 2; case 15
	.short _0202965C - _02029614 - 2; case 16
	.short _0202965C - _02029614 - 2; case 17
	.short _02029674 - _02029614 - 2; case 18
	.short _0202967C - _02029614 - 2; case 19
	.short _0202967C - _02029614 - 2; case 20
	.short _0202967C - _02029614 - 2; case 21
	.short _0202967C - _02029614 - 2; case 22
	.short _0202967C - _02029614 - 2; case 23
	.short _0202967C - _02029614 - 2; case 24
	.short _0202967C - _02029614 - 2; case 25
	.short _0202967C - _02029614 - 2; case 26
	.short _0202967C - _02029614 - 2; case 27
	.short _0202967C - _02029614 - 2; case 28
	.short _0202967C - _02029614 - 2; case 29
	.short _0202967C - _02029614 - 2; case 30
	.short _02029682 - _02029614 - 2; case 31
	.short _0202967C - _02029614 - 2; case 32
	.short _0202967C - _02029614 - 2; case 33
	.short _0202965C - _02029614 - 2; case 34
	.short _0202965C - _02029614 - 2; case 35
_0202965C:
	add r1, r4, #0x0
	bl FUN_02029730
	b _02029682
_02029664:
	add r1, r4, #0x0
	bl FUN_02029738
	b _02029682
_0202966C:
	add r1, r4, #0x0
	bl FUN_02029750
	b _02029682
_02029674:
	add r1, r4, #0x0
	bl FUN_0202975C
	b _02029682
_0202967C:
	add r1, r4, #0x0
	bl FUN_02029768
_02029682:
	add r6, r6, #0x1
	add r4, #0x8
	add r5, r5, #0x4
	cmp r6, #0x4
	blo _020295EE
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02029690
FUN_02029690: ; 0x02029690
	ldrh r2, [r0, #0x14]
	strh r2, [r1, #0x0]
	ldrh r0, [r0, #0x16]
	strh r0, [r1, #0x2]
	bx lr
	.balign 4

	thumb_func_start FUN_0202969C
FUN_0202969C: ; 0x0202969C
	ldrh r2, [r0, #0x18]
	strh r2, [r1, #0x0]
	ldrh r0, [r0, #0x1a]
	strh r0, [r1, #0x2]
	bx lr
	.balign 4

	thumb_func_start FUN_020296A8
FUN_020296A8: ; 0x020296A8
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r5, r6, #0x0
	add r4, r1, #0x0
	mov r7, #0x0
	add r5, #0x1c
_020296B4:
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x3a
	bl memset
	ldrb r0, [r6, #0x1c]
	cmp r0, #0x10
	bhi _02029722
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020296D0: ; jump table (using 16-bit offset)
	.short _02029722 - _020296D0 - 2; case 0
	.short _020296F2 - _020296D0 - 2; case 1
	.short _020296F2 - _020296D0 - 2; case 2
	.short _020296F2 - _020296D0 - 2; case 3
	.short _020296F2 - _020296D0 - 2; case 4
	.short _020296F2 - _020296D0 - 2; case 5
	.short _020296FC - _020296D0 - 2; case 6
	.short _02029706 - _020296D0 - 2; case 7
	.short _02029710 - _020296D0 - 2; case 8
	.short _02029706 - _020296D0 - 2; case 9
	.short _02029710 - _020296D0 - 2; case 10
	.short _020296F2 - _020296D0 - 2; case 11
	.short _02029710 - _020296D0 - 2; case 12
	.short _0202971A - _020296D0 - 2; case 13
	.short _02029710 - _020296D0 - 2; case 14
	.short _02029706 - _020296D0 - 2; case 15
	.short _02029710 - _020296D0 - 2; case 16
_020296F2:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02029774
	b _02029722
_020296FC:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020297E4
	b _02029722
_02029706:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02029808
	b _02029722
_02029710:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02029860
	b _02029722
_0202971A:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02029868
_02029722:
	add r7, r7, #0x1
	add r4, #0x3a
	add r6, #0x2a
	add r5, #0x2a
	cmp r7, #0x2
	blo _020296B4
	pop {r3-r7, pc}

	thumb_func_start FUN_02029730
FUN_02029730: ; 0x02029730
	mov r2, #0x3f
	and r0, r2
	strb r0, [r1, #0x0]
	bx lr

	thumb_func_start FUN_02029738
FUN_02029738: ; 0x02029738
	mov r2, #0x3f
	and r2, r0
	strb r2, [r1, #0x0]
	lsr r3, r0, #0x6
	ldr r2, _0202974C ; =0x000003FF
	lsr r0, r0, #0x10
	and r2, r3
	strh r2, [r1, #0x4]
	strh r0, [r1, #0x2]
	bx lr
	.balign 4
_0202974C: .word 0x000003FF

	thumb_func_start FUN_02029750
FUN_02029750: ; 0x02029750
	mov r2, #0x3f
	and r2, r0
	strb r2, [r1, #0x0]
	lsr r0, r0, #0x10
	strh r0, [r1, #0x2]
	bx lr

	thumb_func_start FUN_0202975C
FUN_0202975C: ; 0x0202975C
	mov r2, #0x3f
	and r2, r0
	strb r2, [r1, #0x0]
	lsr r0, r0, #0x10
	strh r0, [r1, #0x6]
	bx lr

	thumb_func_start FUN_02029768
FUN_02029768: ; 0x02029768
	mov r2, #0x3f
	and r2, r0
	strb r2, [r1, #0x0]
	lsr r0, r0, #0x10
	strh r0, [r1, #0x2]
	bx lr

	thumb_func_start FUN_02029774
FUN_02029774: ; 0x02029774
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldrb r0, [r5, #0x0]
	add r4, r1, #0x0
	mov r1, #0xf
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	bic r0, r1
	ldrb r1, [r5, #0x1]
	asr r2, r1, #0x2
	mov r1, #0x1f
	and r1, r2
	lsl r1, r1, #0x18
	lsr r2, r1, #0x18
	mov r1, #0xf
	and r1, r2
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r0, [r4, #0x1]
	mov r1, #0x10
	mov r2, #0x1
	bic r0, r1
	ldrb r1, [r5, #0x1]
	asr r1, r1, #0x1
	and r1, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r0, [r4, #0x1]
	mov r1, #0x20
	bic r0, r1
	ldrb r1, [r5, #0x1]
	and r1, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1a
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r5, #0x2
	add r1, r4, #0x2
	mov r2, #0x8
	bl FUN_020292D4
	add r5, #0x12
	add r4, #0x12
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x8
	bl FUN_020292D4
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020297E4
FUN_020297E4: ; 0x020297E4
	ldrb r2, [r0, #0x0]
	strb r2, [r1, #0x0]
	ldrb r3, [r1, #0x1]
	mov r2, #0x10
	bic r3, r2
	ldrb r2, [r0, #0x1]
	add r0, r0, #0x2
	lsl r2, r2, #0x1f
	lsr r2, r2, #0x1b
	orr r2, r3
	strb r2, [r1, #0x1]
	ldr r3, _02029804 ; =FUN_020292D4
	add r1, r1, #0x2
	mov r2, #0x8
	bx r3
	nop
_02029804: .word FUN_020292D4

	thumb_func_start FUN_02029808
FUN_02029808: ; 0x02029808
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldrb r0, [r5, #0x0]
	add r4, r1, #0x0
	mov r1, #0x10
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	bic r0, r1
	ldrb r1, [r5, #0x1]
	asr r2, r1, #0x2
	mov r1, #0x1
	and r1, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r0, [r4, #0x1]
	mov r1, #0xc0
	ldrb r2, [r5, #0x1]
	bic r0, r1
	mov r1, #0x3
	and r1, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1e
	lsr r1, r1, #0x18
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r5, #0x2
	add r1, r4, #0x2
	mov r2, #0x8
	bl FUN_020292D4
	add r5, #0x12
	add r4, #0x22
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0xc
	bl FUN_020292D4
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02029860
FUN_02029860: ; 0x02029860
	ldrb r0, [r0, #0x0]
	strb r0, [r1, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02029868
FUN_02029868: ; 0x02029868
	ldrb r2, [r0, #0x0]
	strb r2, [r1, #0x0]
	ldrb r3, [r1, #0x1]
	mov r2, #0xf
	bic r3, r2
	ldrb r2, [r0, #0x1]
	mov r0, #0xf
	and r0, r2
	orr r0, r3
	strb r0, [r1, #0x1]
	bx lr
	.balign 4

	thumb_func_start FUN_02029880
FUN_02029880: ; 0x02029880
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r0, #0x0
	mov r0, #0x0
	add r4, r3, #0x0
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	str r1, [sp, #0x0]
	add r5, r2, #0x0
	ldr r6, [sp, #0x20]
	bl FUN_02034930
	cmp r0, #0x1
	bne _020298BA
	add r0, r5, #0x0
	bl FUN_02034964
	cmp r0, #0x1
	bne _02029942
	add r0, r4, #0x0
	bl FUN_02034824
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r1, r6, #0x0
	bl FUN_020290F8
	str r0, [sp, #0x4]
	b _02029942
_020298BA:
	add r0, r4, #0x0
	bl FUN_02034944
	cmp r0, #0x1
	bne _0202991A
	add r0, r5, #0x0
	bl FUN_02034964
	cmp r0, #0x1
	bne _02029942
	ldr r0, _02029958 ; =0x0000019E
	cmp r4, r0
	bne _020298DE
	add r0, r6, #0x0
	bl FUN_02029030
	str r0, [sp, #0x4]
	b _02029942
_020298DE:
	add r0, #0x8
	cmp r4, r0
	bne _020298EE
	add r0, r6, #0x0
	bl FUN_0202903C
	str r0, [sp, #0x4]
	b _02029942
_020298EE:
	add r0, r4, #0x0
	bl FUN_02034824
	add r7, r0, #0x0
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	ldr r5, _0202995C ; =UNK_020EE9A4
	mov r4, #0x0
	str r0, [sp, #0x8]
_02029900:
	ldr r0, [r5, #0x0]
	cmp r7, r0
	bne _02029910
	ldr r0, [sp, #0x8]
	add r1, r6, #0x0
	bl FUN_0202910C
	str r0, [sp, #0x4]
_02029910:
	add r4, r4, #0x1
	add r5, #0x8
	cmp r4, #0x1b
	blo _02029900
	b _02029942
_0202991A:
	add r0, r4, #0x0
	bl FUN_02034964
	cmp r0, #0x1
	bne _02029942
	add r0, r5, #0x0
	bl FUN_02034944
	cmp r0, #0x1
	bne _02029942
	add r0, r7, #0x0
	add r1, r5, #0x0
	bl FUN_02029988
	cmp r0, #0xff
	beq _02029942
	add r1, r6, #0x0
	bl FUN_02029090
	str r0, [sp, #0x4]
_02029942:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _02029952
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	mov r2, #0x1
	bl FUN_02028AD4
_02029952:
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02029958: .word 0x0000019E
_0202995C: .word UNK_020EE9A4

	thumb_func_start FUN_02029960
FUN_02029960: ; 0x02029960
	ldr r3, _02029980 ; =UNK_020EE9A4
	mov r2, #0x0
_02029964:
	ldr r1, [r3, #0x0]
	cmp r0, r1
	bne _02029972
	ldr r0, _02029984 ; =UNK_020EE9A8
	lsl r1, r2, #0x3
	ldr r0, [r0, r1]
	bx lr
_02029972:
	add r2, r2, #0x1
	add r3, #0x8
	cmp r2, #0x1b
	blo _02029964
	mov r0, #0x0
	bx lr
	nop
_02029980: .word UNK_020EE9A4
_02029984: .word UNK_020EE9A8

	thumb_func_start FUN_02029988
FUN_02029988: ; 0x02029988
	push {r3-r5, lr}
	ldr r2, _020299B8 ; =UNK_020EE964
	mov r4, #0x0
_0202998E:
	lsl r3, r4, #0x3
	add r5, r2, r3
	ldrh r5, [r5, #0x4]
	cmp r1, r5
	bne _020299A8
	ldr r1, _020299BC ; =UNK_020EE96A
	ldrh r1, [r1, r3]
	bl FUN_020239D0
	cmp r0, #0x0
	bne _020299B2
	add r0, r4, #0x0
	pop {r3-r5, pc}
_020299A8:
	add r3, r4, #0x1
	lsl r3, r3, #0x18
	lsr r4, r3, #0x18
	cmp r4, #0x8
	blo _0202998E
_020299B2:
	mov r0, #0xff
	pop {r3-r5, pc}
	nop
_020299B8: .word UNK_020EE964
_020299BC: .word UNK_020EE96A

	thumb_func_start FUN_020299C0
FUN_020299C0: ; 0x020299C0
	push {r4, lr}
	add r4, r0, #0x0
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	add r1, r2, #0x0
	bl FUN_020290E4
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0x1
	bl FUN_02028AD4
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020299DC
FUN_020299DC: ; 0x020299DC
	push {r3-r7, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r7, r1, #0x0
	add r6, r3, #0x0
	bl FUN_02029A48
	cmp r0, #0x8
	bhs _02029A04
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020290A4
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x1
	bl FUN_02028AD4
	pop {r3-r7, pc}
_02029A04:
	bne _02029A1A
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_020290BC
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x1
	bl FUN_02028AD4
	pop {r3-r7, pc}
_02029A1A:
	cmp r0, #0x9
	bne _02029A32
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_020290D0
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x1
	bl FUN_02028AD4
	pop {r3-r7, pc}
_02029A32:
	add r0, r7, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0202928C
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x3
	bl FUN_02028AD4
	pop {r3-r7, pc}

	thumb_func_start FUN_02029A48
FUN_02029A48: ; 0x02029A48
	ldr r2, _02029A7C ; =UNK_020EE964
	mov r3, #0x0
_02029A4C:
	lsl r1, r3, #0x3
	ldr r1, [r2, r1]
	cmp r0, r1
	bne _02029A58
	add r0, r3, #0x0
	bx lr
_02029A58:
	add r1, r3, #0x1
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r3, #0x8
	blo _02029A4C
	ldr r1, _02029A80 ; =0x00000105
	sub r2, r0, r1
	cmp r2, #0x3
	bhi _02029A6E
	mov r0, #0x8
	bx lr
_02029A6E:
	add r1, r1, #0x6
	cmp r0, r1
	bne _02029A78
	mov r0, #0x9
	bx lr
_02029A78:
	mov r0, #0xa
	bx lr
	.balign 4
_02029A7C: .word UNK_020EE964
_02029A80: .word 0x00000105
