    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02005CFC
FUN_02005CFC: ; 0x02005CFC
	push {r3, lr}
	mov r0, #0x1d
	bl FUN_02003D38
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _02005D1C
	mov r0, #0xe
	bl FUN_02004ABC
	cmp r0, #0x0
	bne _02005D1C
	bl FUN_02005DFC
	mov r0, #0x1
	pop {r3, pc}
_02005D1C:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02005D20
FUN_02005D20: ; 0x02005D20
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x1e
	bl FUN_02003D38
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02029F04
	cmp r0, #0x0
	bne _02005D3A
	mov r0, #0x0
	pop {r3-r5, pc}
_02005D3A:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x1
	beq _02005D44
	mov r0, #0x1
	pop {r3-r5, pc}
_02005D44:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02005D48
FUN_02005D48: ; 0x02005D48
	push {r3-r7, lr}
	sub sp, #0x30
	add r6, r0, #0x0
	add r5, r2, #0x0
	add r7, r3, #0x0
	bl FUN_02004DB4
	str r0, [sp, #0x0]
	mov r0, #0x1d
	bl FUN_02003D38
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	bl FUN_02005D20
	cmp r0, #0x0
	bne _02005D70
	add sp, #0x30
	mov r0, #0x0
	pop {r3-r7, pc}
_02005D70:
	mov r0, #0x0
	bl FUN_02005614
	bl FUN_02005DFC
	mov r0, #0xe
	bl FUN_02004984
	bl LCRandom
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x13
	sub r1, r1, r2
	mov r0, #0x13
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r6, #0x0
	bl FUN_02029F10
	add r1, r0, #0x0
	ldr r0, [sp, #0x0]
	bl FUN_02029F14
	mov r0, #0xe
	bl FUN_02004930
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0xc]
	bl FUN_02004DB4
	str r0, [sp, #0x10]
	mov r0, #0x0
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	mov r0, #0x7d
	lsl r0, r0, #0x4
	str r0, [sp, #0x1c]
	str r0, [sp, #0x20]
	mov r0, #0x2
	lsl r0, r0, #0xe
	add r0, r4, r0
	str r0, [sp, #0x28]
	lsr r0, r7, #0x1f
	add r0, r7, r0
	asr r0, r0, #0x1
	add r0, #0x40
	str r0, [sp, #0x2c]
	add r0, sp, #0x8
	mov r1, #0xe
	str r5, [sp, #0x24]
	bl FUN_02004A6C
	add r4, r0, #0x0
	mov r0, #0xe
	add r1, r5, #0x0
	bl FUN_02004AF8
	ldr r0, [sp, #0x4]
	mov r1, #0x1
	strb r1, [r0, #0x0]
	mov r0, #0x0
	bl FUN_02005E80
	add r0, r4, #0x0
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02005DFC
FUN_02005DFC: ; 0x02005DFC
	push {r3-r5, lr}
	mov r0, #0xf
	bl FUN_02003D38
	add r5, r0, #0x0
	mov r0, #0x1d
	bl FUN_02003D38
	add r4, r0, #0x0
	ldrb r0, [r5, #0x0]
	cmp r0, #0x1
	bne _02005E20
	mov r0, #0xe
	bl FUN_02004C3C
	mov r0, #0xe
	bl FUN_02004A04
_02005E20:
	mov r0, #0x0
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02005E28
FUN_02005E28: ; 0x02005E28
	push {lr}
	sub sp, #0x1c
	mov r0, #0x2
	str r0, [sp, #0x0]
	bl FUN_02004DB4
	mov r1, #0x7d
	str r0, [sp, #0x4]
	lsl r1, r1, #0x4
	mov r0, #0x1f
	str r1, [sp, #0x8]
	tst r0, r1
	beq _02005E48
	mov r0, #0x1f
	bic r1, r0
	str r1, [sp, #0x8]
_02005E48:
	ldr r0, _02005E60 ; =0x00004174
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	add r0, sp, #0x0
	bl FUN_02004914
	add sp, #0x1c
	pop {pc}
	nop
_02005E60: .word 0x00004174

	thumb_func_start FUN_02005E64
FUN_02005E64: ; 0x02005E64
	ldr r3, _02005E68 ; =FUN_0200491C
	bx r3
	.balign 4
_02005E68: .word FUN_0200491C

	thumb_func_start FUN_02005E6C
FUN_02005E6C: ; 0x02005E6C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02004DB4
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02029F4C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02005E80
FUN_02005E80: ; 0x02005E80
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x1e
	bl FUN_02003D38
	strb r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02005E90
FUN_02005E90: ; 0x02005E90
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x23
	add r7, r1, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02003D38
	cmp r5, #0x0
	bne _02005EB2
	ldr r0, [r0, #0x0]
	add r1, r7, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl FUN_02005D48
	b _02005EBE
_02005EB2:
	add r0, r5, #0x0
	add r1, r7, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl FUN_02005D48
_02005EBE:
	cmp r0, #0x0
	bne _02005ED8
	mov r0, #0x1
	bl FUN_02005E80
	mov r0, #0xb
	str r0, [sp, #0x0]
	ldr r1, _02005EDC ; =0x000001B9
	mov r0, #0x0
	add r2, r6, #0x0
	add r3, r4, #0x0
	bl FUN_020056AC
_02005ED8:
	pop {r3-r7, pc}
	nop
_02005EDC: .word 0x000001B9

	thumb_func_start FUN_02005EE0
FUN_02005EE0: ; 0x02005EE0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02029F04
	cmp r0, #0x0
	bne _02005EF0
	mov r0, #0x0
	pop {r4, pc}
_02005EF0:
	add r0, r4, #0x0
	bl FUN_02029F10
	mov r1, #0xf
	ldrsb r0, [r0, r1]
	sub r1, #0x2d
	cmp r0, r1
	bge _02005F04
	mov r0, #0x1
	pop {r4, pc}
_02005F04:
	cmp r0, #0x1e
	blt _02005F10
	cmp r0, #0x80
	bge _02005F10
	mov r0, #0x2
	pop {r4, pc}
_02005F10:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02005F14
FUN_02005F14: ; 0x02005F14
	cmp r0, #0xb
	bgt _02005F2E
	bge _02005F32
	cmp r0, #0x5
	bgt _02005F36
	cmp r0, #0x0
	blt _02005F36
	beq _02005F32
	cmp r0, #0x1
	beq _02005F32
	cmp r0, #0x5
	beq _02005F32
	b _02005F36
_02005F2E:
	cmp r0, #0xc
	bne _02005F36
_02005F32:
	mov r0, #0x1
	bx lr
_02005F36:
	mov r0, #0x0
	bx lr
	.balign 4
