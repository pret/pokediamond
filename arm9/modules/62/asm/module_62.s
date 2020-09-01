	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD62_0222D5D0
MOD62_0222D5D0: ; 0x0222D5D0
	add r3, r2, #0
	sub r3, #0xa
	strb r3, [r0]
	add r3, r1, #0
	sub r3, #0xa
	strb r3, [r0, #2]
	add r2, #0xa
	strb r2, [r0, #1]
	add r1, #0xa
	strb r1, [r0, #3]
	bx lr
	.align 2, 0
	thumb_func_end MOD62_0222D5D0

	thumb_func_start MOD62_0222D5E8
MOD62_0222D5E8: ; 0x0222D5E8
	mov r1, #0
	strb r1, [r0]
	strb r1, [r0, #2]
	mov r1, #0xc0
	strb r1, [r0, #1]
	mov r1, #0xff
	strb r1, [r0, #3]
	bx lr
	thumb_func_end MOD62_0222D5E8

	thumb_func_start MOD62_0222D5F8
MOD62_0222D5F8: ; 0x0222D5F8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	beq _0222D64C
	cmp r2, #1
	bne _0222D628
	ldr r3, _0222D650 ; =gMain + 0x40
	mov r1, #0x1c
	mov r2, #0x1e
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, r4, #0
	bl FUN_0200C714
	add r1, sp, #0
	add r0, r4, #0
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	add r0, r5, #0
	bl MOD62_0222D5E8
	pop {r3, r4, r5, pc}
_0222D628:
	add r1, sp, #0
	add r0, r4, #0
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	add r3, sp, #0
	mov r1, #2
	mov r2, #0
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, r5, #0
	lsl r1, r1, #0x18
	lsl r2, r2, #0x18
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl MOD62_0222D5D0
_0222D64C:
	pop {r3, r4, r5, pc}
	nop
_0222D650: .word gMain + 0x40
	thumb_func_end MOD62_0222D5F8

	thumb_func_start MOD62_0222D654
MOD62_0222D654: ; 0x0222D654
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	add r7, r4, #0
	mov r6, #0xcb
	add r5, r0, #0
	sub r7, #0x38
	lsl r6, r6, #2
_0222D662:
	ldr r0, [r5, r6]
	cmp r0, #0
	beq _0222D670
	add r1, r7, #0
	mov r2, #0x10
	bl FUN_0200C82C
_0222D670:
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #8
	blt _0222D662
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD62_0222D654

	thumb_func_start MOD62_0222D67C
MOD62_0222D67C: ; 0x0222D67C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r0, #0xf1
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	mov r6, #0
	lsl r0, r0, #3
	add r0, r7, r0
	ldr r4, [r0, #8]
	add r5, r7, #0
_0222D690:
	ldrb r1, [r4]
	cmp r1, #0
	beq _0222D6CE
	mov r0, #0xca
	lsl r0, r0, #2
	strb r1, [r5, r0]
	ldrb r1, [r4, #1]
	add r0, r0, #1
	strb r1, [r5, r0]
	ldrb r1, [r4, #2]
	ldr r0, _0222D6E8 ; =0x0000032A
	strb r1, [r5, r0]
	lsl r1, r6, #0x18
	add r0, r7, #0
	lsr r1, r1, #0x18
	bl MOD62_0222D9A0
	mov r0, #0x33
	mov r1, #0xcb
	lsl r0, r0, #4
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	mov r2, #0
	bl MOD62_0222D5F8
	mov r0, #0xc9
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r5, r0]
	b _0222D6DA
_0222D6CE:
	mov r0, #0xc9
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
	add r0, r0, #4
	strb r1, [r5, r0]
_0222D6DA:
	add r6, r6, #1
	add r4, r4, #3
	add r5, #0x10
	cmp r6, #8
	blt _0222D690
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222D6E8: .word 0x0000032A
	thumb_func_end MOD62_0222D67C

	thumb_func_start MOD62_0222D6EC
MOD62_0222D6EC: ; 0x0222D6EC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r0, #0
	mov r0, #0xc9
	mov r4, #0
	add r3, r6, #0
	lsl r0, r0, #2
_0222D6FA:
	ldr r2, [r3, r0]
	cmp r2, #1
	beq _0222D75C
	add r0, r6, r1
	mov r1, #0x42
	lsl r1, r1, #4
	ldrb r3, [r0, r1]
	lsl r5, r4, #4
	add r0, r1, #0
	add r2, r6, r5
	sub r0, #0xf8
	strb r3, [r2, r0]
	add r0, r1, #0
	sub r0, #0xf7
	add r7, r6, r0
	mov r0, #0xbe
	sub r1, #0xf6
	strb r0, [r7, r5]
	add r0, r6, r1
	mov r1, #0x46
	strb r1, [r0, r5]
	str r0, [sp]
	add r0, sp, #8
	add r1, sp, #4
	bl FUN_02020AB0
	ldr r0, [sp, #8]
	strb r0, [r7, r5]
	ldr r1, [sp, #4]
	ldr r0, [sp]
	strb r1, [r0, r5]
	lsl r1, r4, #0x18
	add r0, r6, #0
	lsr r1, r1, #0x18
	bl MOD62_0222D9A0
	lsl r1, r4, #0x18
	add r0, r6, #0
	lsr r1, r1, #0x18
	bl MOD62_0222D788
	mov r0, #0xc9
	mov r2, #1
	add r1, r6, r5
	lsl r0, r0, #2
	str r2, [r1, r0]
	add sp, #0xc
	add r0, r4, #0
	pop {r4, r5, r6, r7, pc}
_0222D75C:
	add r4, r4, #1
	add r3, #0x10
	cmp r4, #8
	blt _0222D6FA
	mov r0, #0xff
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD62_0222D6EC

	thumb_func_start MOD62_0222D76C
MOD62_0222D76C: ; 0x0222D76C
	mov r1, #0xc9
	mov r3, #0
	lsl r1, r1, #2
_0222D772:
	ldr r2, [r0, r1]
	cmp r2, #1
	beq _0222D77C
	mov r0, #1
	bx lr
_0222D77C:
	add r3, r3, #1
	add r0, #0x10
	cmp r3, #8
	blt _0222D772
	mov r0, #0
	bx lr
	thumb_func_end MOD62_0222D76C

	thumb_func_start MOD62_0222D788
MOD62_0222D788: ; 0x0222D788
	push {r3, r4, r5, r6, r7, lr}
	mov r7, #0xc9
	add r5, r0, #0
	add r6, r1, #0
	mov r4, #0
	lsl r7, r7, #2
_0222D794:
	ldr r0, [r5, r7]
	cmp r0, #1
	bne _0222D7D4
	cmp r4, r6
	bne _0222D7AC
	mov r0, #0xcb
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_0200C6C4
	b _0222D7D4
_0222D7AC:
	mov r0, #0xcb
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0200C6D8
	add r1, r0, #0
	bne _0222D7C8
	mov r0, #0xcb
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r1, #1
	bl FUN_0200C6C4
	b _0222D7D4
_0222D7C8:
	mov r0, #0xcb
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r1, #2
	bl FUN_0200C6C4
_0222D7D4:
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #8
	blt _0222D794
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD62_0222D788

	thumb_func_start MOD62_0222D7E0
MOD62_0222D7E0: ; 0x0222D7E0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r7, r1, #0
	add r1, r0, #0
	add r1, #0xdc
	ldr r4, [r1]
	add r1, r0, #0
	add r1, #0xe0
	ldr r5, [r1]
	mov r1, #0x5b
	str r1, [sp]
	add r1, #0xca
	str r1, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	mov r1, #1
	str r1, [sp, #0xc]
	mov r1, #2
	str r1, [sp, #0x10]
	ldr r1, _0222D864 ; =0x0000532D
	add r6, r2, #0
	str r1, [sp, #0x14]
	add r0, #0xe8
	ldr r0, [r0]
	mov r1, #3
	add r2, r4, #0
	add r3, r5, #0
	bl FUN_0200C0DC
	add r0, r7, #0
	bl FUN_02085FAC
	add r3, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _0222D868 ; =0x00004E20
	add r1, r5, #0
	add r0, r6, r0
	str r0, [sp, #8]
	add r0, r4, #0
	mov r2, #0x5b
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _0222D86C ; =0x0000564D
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x5b
	mov r3, #0x5d
	bl FUN_0200C124
	mov r3, #1
	ldr r0, _0222D870 ; =0x000059D9
	str r3, [sp]
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #0x5b
	bl FUN_0200C13C
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222D864: .word 0x0000532D
_0222D868: .word 0x00004E20
_0222D86C: .word 0x0000564D
_0222D870: .word 0x000059D9
	thumb_func_end MOD62_0222D7E0

	thumb_func_start MOD62_0222D874
MOD62_0222D874: ; 0x0222D874
	push {r4, r5, r6, r7, lr}
	sub sp, #0x74
	mov r1, #0x26
	lsl r1, r1, #4
	str r0, [sp]
	ldr r0, [r0, r1]
	cmp r0, #0
	bne _0222D886
	b _0222D994
_0222D886:
	ldr r0, [sp]
	mov r7, #0
	str r7, [r0, r1]
	add r4, sp, #0x54
	add r5, sp, #0x34
	add r6, r0, #0
_0222D892:
	mov r0, #0xff
	str r0, [r4]
	str r0, [r5]
	mov r0, #0xcb
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	cmp r0, #0
	beq _0222D8AA
	bl FUN_0200C6D8
	str r0, [r4]
	str r7, [r5]
_0222D8AA:
	add r7, r7, #1
	add r4, r4, #4
	add r5, r5, #4
	add r6, #0x10
	cmp r7, #8
	blt _0222D892
	mov r0, #0
	mov ip, r0
_0222D8BA:
	mov r0, ip
	mov r3, #7
	cmp r0, #7
	bge _0222D8EA
	add r4, sp, #0x70
	add r5, sp, #0x50
_0222D8C6:
	sub r7, r4, #4
	ldr r2, [r4]
	ldr r0, [r7]
	cmp r0, r2
	blt _0222D8DE
	ldr r1, [r5]
	sub r6, r5, #4
	str r0, [r4]
	ldr r0, [r6]
	str r0, [r5]
	str r2, [r7]
	str r1, [r6]
_0222D8DE:
	sub r3, r3, #1
	mov r0, ip
	sub r4, r4, #4
	sub r5, r5, #4
	cmp r3, r0
	bgt _0222D8C6
_0222D8EA:
	mov r0, ip
	add r0, r0, #1
	mov ip, r0
	cmp r0, #7
	blt _0222D8BA
	mov r3, #0xca
	lsl r3, r3, #2
	ldr r0, [sp]
	mov r2, #0
	add r1, sp, #0x1c
	add r4, r3, #1
	add r5, r3, #2
_0222D902:
	ldrb r6, [r0, r3]
	add r2, r2, #1
	strb r6, [r1]
	ldrb r6, [r0, r4]
	strb r6, [r1, #1]
	ldrb r6, [r0, r5]
	add r0, #0x10
	strb r6, [r1, #2]
	add r1, r1, #3
	cmp r2, #8
	blt _0222D902
	add r3, sp, #0x1c
	add r2, sp, #4
	mov r1, #0x18
_0222D91E:
	ldrb r0, [r3]
	add r3, r3, #1
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _0222D91E
	ldr r5, [sp]
	mov r6, #0
	add r4, sp, #0x34
	add r7, sp, #4
_0222D932:
	ldr r1, [r4]
	cmp r1, #0xff
	bne _0222D94A
	mov r0, #0xca
	mov r1, #0
	lsl r0, r0, #2
	strb r1, [r5, r0]
	add r0, r0, #1
	strb r1, [r5, r0]
	ldr r0, _0222D998 ; =0x0000032A
	strb r1, [r5, r0]
	b _0222D98A
_0222D94A:
	lsl r0, r1, #1
	add r0, r1, r0
	ldrb r1, [r7, r0]
	mov r0, #0xca
	lsl r0, r0, #2
	strb r1, [r5, r0]
	ldr r1, [r4]
	lsl r0, r1, #1
	add r0, r1, r0
	add r0, r7, r0
	ldrb r1, [r0, #1]
	ldr r0, _0222D99C ; =0x00000329
	strb r1, [r5, r0]
	ldr r1, [r4]
	lsl r0, r1, #1
	add r0, r1, r0
	add r0, r7, r0
	ldrb r1, [r0, #2]
	ldr r0, _0222D998 ; =0x0000032A
	strb r1, [r5, r0]
	ldr r0, [r4]
	lsl r1, r0, #4
	ldr r0, [sp]
	add r1, r0, r1
	mov r0, #0xcb
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0222D98A
	add r1, r6, #0
	bl FUN_0200C6C4
_0222D98A:
	add r6, r6, #1
	add r4, r4, #4
	add r5, #0x10
	cmp r6, #8
	blt _0222D932
_0222D994:
	add sp, #0x74
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0222D998: .word 0x0000032A
_0222D99C: .word 0x00000329
	thumb_func_end MOD62_0222D874

	thumb_func_start MOD62_0222D9A0
MOD62_0222D9A0: ; 0x0222D9A0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r1, #0
	add r1, r0, #0
	add r1, #0xdc
	ldr r7, [r1]
	add r1, r0, #0
	add r1, #0xe0
	ldr r6, [r1]
	mov r1, #0xc9
	lsl r1, r1, #2
	add r2, r0, r1
	lsl r1, r5, #4
	add r4, r2, r1
	ldr r1, [r2, r1]
	cmp r1, #1
	bne _0222D9CC
	bl ErrorHandling
	add sp, #0x34
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0222D9CC:
	ldrb r1, [r4, #4]
	add r2, r5, #0
	bl MOD62_0222D7E0
	ldrb r1, [r4, #5]
	add r0, sp, #0
	strh r1, [r0]
	ldrb r1, [r4, #6]
	strh r1, [r0, #2]
	mov r1, #0
	strh r1, [r0, #4]
	strh r1, [r0, #6]
	mov r0, #2
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x2c]
	sub r0, r0, #2
	str r1, [sp, #0xc]
	str r1, [sp, #0x30]
	str r1, [sp, #8]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	ldrb r0, [r4, #4]
	bl FUN_02085FAC
	ldr r0, _0222DA28 ; =0x00004E20
	add r1, r6, #0
	add r0, r5, r0
	str r0, [sp, #0x14]
	ldr r0, _0222DA2C ; =0x0000532D
	add r2, sp, #0
	str r0, [sp, #0x18]
	ldr r0, _0222DA30 ; =0x0000564D
	str r0, [sp, #0x1c]
	ldr r0, _0222DA34 ; =0x000059D9
	str r0, [sp, #0x20]
	add r0, r7, #0
	bl FUN_0200C154
	str r0, [r4, #8]
	bl FUN_0200C5A8
	mov r0, #1
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	nop
_0222DA28: .word 0x00004E20
_0222DA2C: .word 0x0000532D
_0222DA30: .word 0x0000564D
_0222DA34: .word 0x000059D9
	thumb_func_end MOD62_0222D9A0

	thumb_func_start MOD62_0222DA38
MOD62_0222DA38: ; 0x0222DA38
	push {r3, r4, r5, r6, r7, lr}
	add r5, r2, #0
	add r6, r1, #0
	mov r1, #0xc9
	add r4, r0, #0
	lsl r7, r5, #4
	add r3, r4, r7
	lsl r1, r1, #2
	ldr r2, [r3, r1]
	cmp r2, #0
	bne _0222DA52
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0222DA52:
	cmp r6, #3
	bhi _0222DAE2
	add r2, r6, r6
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0222DA62: ; jump table
	.short _0222DA6A - _0222DA62 - 2 ; case 0
	.short _0222DAAA - _0222DA62 - 2 ; case 1
	.short _0222DA80 - _0222DA62 - 2 ; case 2
	.short _0222DAAA - _0222DA62 - 2 ; case 3
_0222DA6A:
	add r1, r4, #0
	add r1, #0xd4
	ldr r1, [r1]
	cmp r1, #0xff
	bne _0222DAE6
	add r4, #0xd4
	add r1, r5, #0
	str r5, [r4]
	bl MOD62_0222D788
	b _0222DAE6
_0222DA80:
	add r0, #0xd4
	ldr r0, [r0]
	cmp r0, r5
	bne _0222DAE6
	add r0, r1, #0
	add r0, #0xc
	add r1, #8
	ldr r0, [r3, r0]
	ldr r1, [r3, r1]
	mov r2, #1
	bl MOD62_0222D5F8
	add r0, r4, #0
	add r1, r5, #0
	bl MOD62_0222DBCC
	add r0, r4, #0
	add r1, r5, #0
	bl MOD62_0222DC48
	b _0222DAE6
_0222DAAA:
	add r1, r4, #0
	add r1, #0xd4
	ldr r1, [r1]
	cmp r1, #0xff
	bne _0222DAE6
	add r1, r5, #0
	bl MOD62_0222DB38
	mov r1, #0x33
	add r2, r4, r7
	lsl r1, r1, #4
	add r6, r0, #0
	ldr r0, [r2, r1]
	sub r1, r1, #4
	ldr r1, [r2, r1]
	mov r2, #0
	bl MOD62_0222D5F8
	cmp r6, #0
	bne _0222DADA
	add r0, r4, #0
	add r1, r5, #0
	bl MOD62_0222DB78
_0222DADA:
	mov r0, #0xff
	add r4, #0xd4
	str r0, [r4]
	b _0222DAE6
_0222DAE2:
	bl ErrorHandling
_0222DAE6:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD62_0222DA38

	thumb_func_start MOD62_0222DAEC
MOD62_0222DAEC: ; 0x0222DAEC
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r7, #0xc9
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_0222DAF8:
	ldr r0, [r5, r7]
	cmp r0, #1
	bne _0222DB06
	add r0, r6, #0
	add r1, r4, #0
	bl MOD62_0222DB78
_0222DB06:
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #8
	blt _0222DAF8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD62_0222DAEC

	thumb_func_start MOD62_0222DB10
MOD62_0222DB10: ; 0x0222DB10
	push {r3, r4, r5, r6, r7, lr}
	mov r7, #0xc9
	add r5, r0, #0
	add r6, r1, #0
	mov r4, #0
	lsl r7, r7, #2
_0222DB1C:
	ldr r0, [r5, r7]
	cmp r0, #1
	bne _0222DB2E
	mov r0, #0xcb
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl FUN_0200C644
_0222DB2E:
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #8
	blt _0222DB1C
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD62_0222DB10

	thumb_func_start MOD62_0222DB38
MOD62_0222DB38: ; 0x0222DB38
	push {r3, lr}
	lsl r1, r1, #4
	add r2, r0, r1
	mov r0, #0xc9
	lsl r0, r0, #2
	ldr r1, [r2, r0]
	cmp r1, #0
	bne _0222DB4C
	mov r0, #1
	pop {r3, pc}
_0222DB4C:
	add r0, #8
	ldr r0, [r2, r0]
	add r1, sp, #0
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	add r2, sp, #0
	mov r0, #2
	mov r1, #0
	ldrsh r0, [r2, r0]
	ldrsh r1, [r2, r1]
	mov r2, #0xbe
	mov r3, #0x46
	bl MOD08_0222A02C
	cmp r0, #0x3c
	bgt _0222DB74
	mov r0, #1
	pop {r3, pc}
_0222DB74:
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD62_0222DB38

	thumb_func_start MOD62_0222DB78
MOD62_0222DB78: ; 0x0222DB78
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0xca
	add r7, r1, #0
	lsl r0, r0, #2
	lsl r4, r7, #4
	add r6, r5, r0
	ldrb r0, [r6, r4]
	bl FUN_02085FAC
	add r0, r5, #0
	add r0, #0xe0
	ldr r1, _0222DBC8 ; =0x00004E20
	ldr r0, [r0]
	add r1, r7, r1
	bl FUN_0200C358
	mov r0, #0xcb
	lsl r0, r0, #2
	add r7, r5, r0
	ldr r0, [r7, r4]
	bl FUN_0200C3DC
	mov r1, #0
	mov r2, #0xc9
	lsl r2, r2, #2
	str r1, [r7, r4]
	add r3, r5, r4
	str r1, [r3, r2]
	strb r1, [r6, r4]
	add r0, r2, #5
	strb r1, [r3, r0]
	add r0, r2, #6
	add r2, #0xc
	strb r1, [r3, r0]
	ldr r0, [r3, r2]
	add r2, r1, #0
	bl MOD62_0222D5D0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222DBC8: .word 0x00004E20
	thumb_func_end MOD62_0222DB78

	thumb_func_start MOD62_0222DBCC
MOD62_0222DBCC: ; 0x0222DBCC
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r5, r1, #0
	bl MOD62_0222DB38
	cmp r0, #0
	bne _0222DBEC
	lsl r0, r5, #4
	add r1, r4, r0
	mov r0, #0xcb
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_0200C90C
	pop {r3, r4, r5, pc}
_0222DBEC:
	lsl r0, r5, #4
	add r1, r4, r0
	mov r0, #0xcb
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_0200C90C
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD62_0222DBCC

	thumb_func_start MOD62_0222DC00
MOD62_0222DC00: ; 0x0222DC00
	push {r4, r5, r6, r7}
	mov r2, #0xf1
	lsl r2, r2, #2
	ldr r2, [r0, r2]
	ldr r4, _0222DC44 ; =0x00000329
	lsl r2, r2, #3
	add r2, r0, r2
	ldr r2, [r2, #8]
	mov r1, #0
	add r3, r4, #1
	sub r5, r4, #1
_0222DC16:
	ldrb r7, [r0, r5]
	ldrb r6, [r2]
	cmp r7, r6
	bne _0222DC2E
	ldrb r7, [r0, r4]
	ldrb r6, [r2, #1]
	cmp r7, r6
	bne _0222DC2E
	ldrb r7, [r0, r3]
	ldrb r6, [r2, #2]
	cmp r7, r6
	beq _0222DC34
_0222DC2E:
	mov r0, #1
	pop {r4, r5, r6, r7}
	bx lr
_0222DC34:
	add r1, r1, #1
	add r2, r2, #3
	add r0, #0x10
	cmp r1, #8
	blt _0222DC16
	mov r0, #0
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
_0222DC44: .word 0x00000329
	thumb_func_end MOD62_0222DC00

	thumb_func_start MOD62_0222DC48
MOD62_0222DC48: ; 0x0222DC48
	push {r3, r4, r5, lr}
	add r5, r0, #0
	lsl r4, r1, #4
	mov r0, #0xcb
	add r1, r5, r4
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, sp, #0
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	add r2, sp, #0
	mov r0, #2
	ldrsh r1, [r2, r0]
	ldr r0, _0222DC78 ; =0x00000329
	add r3, r5, r4
	strb r1, [r3, r0]
	mov r1, #0
	ldrsh r1, [r2, r1]
	add r0, r0, #1
	strb r1, [r3, r0]
	pop {r3, r4, r5, pc}
	nop
_0222DC78: .word 0x00000329
	thumb_func_end MOD62_0222DC48

	thumb_func_start MOD62_0222DC7C
MOD62_0222DC7C: ; 0x0222DC7C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	mov r3, #0xca
	add r7, r0, #0
	lsl r3, r3, #2
	mov r0, #0
	add r1, r7, #0
	add r2, sp, #0
	add r4, r3, #1
	add r5, r3, #2
_0222DC90:
	ldrb r6, [r1, r3]
	add r0, r0, #1
	strb r6, [r2]
	ldrb r6, [r1, r4]
	strb r6, [r2, #1]
	ldrb r6, [r1, r5]
	add r1, #0x10
	strb r6, [r2, #2]
	add r2, r2, #3
	cmp r0, #8
	blt _0222DC90
	ldr r0, [r7]
	mov r2, #0xf1
	lsl r2, r2, #2
	ldr r0, [r0, #0x20]
	ldr r2, [r7, r2]
	add r1, sp, #0
	bl FUN_02029CA4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD62_0222DC7C

	thumb_func_start MOD62_0222DCBC
MOD62_0222DCBC: ; 0x0222DCBC
	push {r3, r4, r5, r6}
	mov r3, #0xca
	lsl r3, r3, #2
	mov r2, #0
	add r4, r3, #1
	add r5, r3, #2
_0222DCC8:
	ldrb r6, [r1, r3]
	add r2, r2, #1
	strb r6, [r0]
	ldrb r6, [r1, r4]
	strb r6, [r0, #1]
	ldrb r6, [r1, r5]
	add r1, #0x10
	strb r6, [r0, #2]
	add r0, r0, #3
	cmp r2, #8
	blt _0222DCC8
	pop {r3, r4, r5, r6}
	bx lr
	.align 2, 0
	thumb_func_end MOD62_0222DCBC

	thumb_func_start MOD62_0222DCE4
MOD62_0222DCE4: ; 0x0222DCE4
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	add r0, r1, #0
	add r1, sp, #0
	add r4, r2, #0
	add r1, #2
	add r2, sp, #0
	add r6, r3, #0
	bl FUN_0200C7A0
	add r1, sp, #0
	mov r0, #0
	ldrsh r2, [r1, r0]
	sub r2, r2, r6
	strb r2, [r5]
	ldrsh r0, [r1, r0]
	add r0, r0, r6
	strb r0, [r5, #1]
	mov r0, #2
	ldrsh r2, [r1, r0]
	sub r2, r2, r4
	strb r2, [r5, #2]
	ldrsh r0, [r1, r0]
	add r0, r0, r4
	strb r0, [r5, #3]
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD62_0222DCE4

	thumb_func_start MOD62_0222DD1C
MOD62_0222DD1C: ; 0x0222DD1C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #2
	mov r1, #0x35
	bl FUN_02011744
	mov r1, #0x8d
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #2
	mov r1, #0x35
	bl FUN_02002C50
	pop {r4, pc}
	thumb_func_end MOD62_0222DD1C

	thumb_func_start MOD62_0222DD38
MOD62_0222DD38: ; 0x0222DD38
	push {r4, lr}
	add r4, r0, #0
	mov r0, #2
	bl FUN_02002CF8
	mov r0, #0x8e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02011870
	mov r0, #9
	lsl r0, r0, #6
	add r0, r4, r0
	bl FUN_0201D5E8
	mov r0, #0x8f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02011870
	mov r0, #0x93
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_0201D5E8
	mov r0, #0x8d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_020117BC
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD62_0222DD38

	thumb_func_start MOD62_0222DD78
MOD62_0222DD78: ; 0x0222DD78
	push {r3, lr}
	sub sp, #0x18
	add r3, r0, #0
	mov r0, #0xe
	str r0, [sp]
	mov r0, #7
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, _0222DDB0 ; =0x00007530
	add r2, r3, #0
	str r0, [sp, #0x14]
	add r0, r3, #0
	add r0, #0xe8
	add r2, #0xdc
	add r3, #0xe0
	ldr r0, [r0]
	ldr r2, [r2]
	ldr r3, [r3]
	mov r1, #3
	bl FUN_0200C0DC
	add sp, #0x18
	pop {r3, pc}
	.align 2, 0
_0222DDB0: .word 0x00007530
	thumb_func_end MOD62_0222DD78

	thumb_func_start MOD62_0222DDB4
MOD62_0222DDB4: ; 0x0222DDB4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	bl MOD62_0222DD78
	mov r1, #0
	add r0, r4, #0
	mov r2, #0x4e
	mov r3, #0xa5
	str r1, [sp]
	bl MOD62_0222DE00
	mov r0, #0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xac
	mov r3, #0xa5
	bl MOD62_0222DE00
	add sp, #4
	pop {r3, r4, pc}
	thumb_func_end MOD62_0222DDB4

	thumb_func_start MOD62_0222DDE0
MOD62_0222DDE0: ; 0x0222DDE0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x8e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	bl FUN_020119D0
	mov r0, #0x8f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_020119D0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD62_0222DDE0

	thumb_func_start MOD62_0222DE00
MOD62_0222DE00: ; 0x0222DE00
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	add r5, r0, #0
	add r4, r1, #0
	str r2, [sp, #0x10]
	add r7, r3, #0
	mov r0, #0
	mov r1, #0x1a
	mov r2, #8
	mov r3, #0x35
	bl NewMsgDataFromNarc
	add r1, r4, #5
	str r0, [sp, #0x14]
	bl NewString_ReadMsgData
	str r0, [sp, #0x18]
	add r0, sp, #0x1c
	bl FUN_0201901C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xe4
	ldr r0, [r0]
	add r1, sp, #0x1c
	mov r2, #0xa
	mov r3, #2
	bl FUN_020190EC
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0222DEF0 ; =0x000F0D02
	ldr r2, [sp, #0x18]
	str r0, [sp, #8]
	add r0, sp, #0x1c
	mov r1, #2
	str r3, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, sp, #0x1c
	mov r1, #2
	mov r2, #0x35
	bl FUN_02011898
	mov r3, #9
	lsl r3, r3, #6
	mov r1, #0xc
	add r6, r4, #0
	mul r6, r1
	add r3, r5, r3
	mov r1, #1
	mov r2, #2
	add r3, r3, r6
	bl FUN_0201D568
	mov r0, #0x8d
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	str r0, [sp, #0x2c]
	add r0, sp, #0x1c
	str r0, [sp, #0x30]
	add r0, r5, #0
	add r0, #0xe0
	ldr r0, [r0]
	bl FUN_0200CA40
	str r0, [sp, #0x34]
	add r0, r5, #0
	add r0, #0xe0
	ldr r0, [r0]
	ldr r1, _0222DEF4 ; =0x00007530
	bl FUN_0200C334
	str r0, [sp, #0x38]
	mov r0, #0
	mov r1, #0x91
	str r0, [sp, #0x3c]
	add r0, r5, r6
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	str r0, [sp, #0x40]
	ldr r0, [sp, #0x10]
	add r7, #0xc0
	str r0, [sp, #0x44]
	mov r0, #1
	str r0, [sp, #0x4c]
	mov r0, #0x28
	str r0, [sp, #0x50]
	mov r0, #2
	str r0, [sp, #0x54]
	mov r0, #0x35
	sub r1, #0xc
	str r0, [sp, #0x58]
	str r7, [sp, #0x48]
	add r5, r5, r1
	lsl r4, r4, #2
	add r0, sp, #0x2c
	bl FUN_020117E8
	str r0, [r5, r4]
	ldr r0, [r5, r4]
	ldr r1, [sp, #0x70]
	bl FUN_02011AC0
	ldr r0, [sp, #0x18]
	bl String_dtor
	ldr r0, [sp, #0x14]
	bl DestroyMsgData
	add r0, sp, #0x1c
	bl FUN_02019178
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	nop
_0222DEF0: .word 0x000F0D02
_0222DEF4: .word 0x00007530
	thumb_func_end MOD62_0222DE00

	thumb_func_start MOD62_0222DEF8
MOD62_0222DEF8: ; 0x0222DEF8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r6, #0
	add r5, r0, #0
	mov r0, #0x42
	add r3, r1, #0
	add r7, r6, #0
	add r2, r6, #0
	add r4, r6, #0
	lsl r0, r0, #4
_0222DF0C:
	add r1, r5, r2
	add r2, r2, #1
	strb r4, [r1, r0]
	cmp r2, #8
	blt _0222DF0C
	lsl r0, r3, #3
	str r0, [sp, #4]
	add r0, r5, #0
	str r0, [sp]
	add r0, #0x68
	str r0, [sp]
_0222DF22:
	ldr r0, [sp]
	add r1, r4, #0
	bl FUN_02029CF8
	add r1, r5, r4
	add r1, #0x80
	ldrb r1, [r1]
	cmp r1, #0
	bne _0222DF38
	cmp r0, #1
	bne _0222DF50
_0222DF38:
	ldr r0, [sp, #4]
	add r7, r7, #1
	cmp r7, r0
	ble _0222DF50
	mov r0, #0x42
	add r1, r5, r6
	add r2, r4, #1
	lsl r0, r0, #4
	add r6, r6, #1
	strb r2, [r1, r0]
	cmp r6, #8
	bge _0222DF56
_0222DF50:
	add r4, r4, #1
	cmp r4, #0x51
	blt _0222DF22
_0222DF56:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD62_0222DEF8

	thumb_func_start MOD62_0222DF5C
MOD62_0222DF5C: ; 0x0222DF5C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r7, r0, #0
	add r0, #0xdc
	ldr r6, [r0]
	add r0, r7, #0
	add r0, #0xe0
	ldr r5, [r0]
	add r0, r7, #0
	add r0, #0xe8
	ldr r0, [r0]
	mov r4, #0
	str r0, [sp, #0x18]
_0222DF76:
	mov r0, #0x42
	add r1, r7, r4
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	bl FUN_02085FAC
	add r3, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _0222DFF4 ; =0x000061A8
	add r1, r5, #0
	add r0, r4, r0
	str r0, [sp, #8]
	add r0, r6, #0
	mov r2, #0x5b
	bl FUN_0200C00C
	add r4, r4, #1
	cmp r4, #8
	blt _0222DF76
	mov r0, #0x5b
	str r0, [sp]
	add r0, #0xca
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, _0222DFF8 ; =0x000066B4
	mov r1, #3
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x18]
	add r2, r6, #0
	add r3, r5, #0
	bl FUN_0200C0DC
	mov r0, #1
	str r0, [sp]
	ldr r0, _0222DFFC ; =0x00006A2C
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r6, #0
	mov r2, #0x5b
	mov r3, #0xb4
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0222E000 ; =0x00006DB8
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r6, #0
	mov r2, #0x5b
	mov r3, #0x58
	bl FUN_0200C13C
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_0222DFF4: .word 0x000061A8
_0222DFF8: .word 0x000066B4
_0222DFFC: .word 0x00006A2C
_0222E000: .word 0x00006DB8
	thumb_func_end MOD62_0222DF5C

	thumb_func_start MOD62_0222E004
MOD62_0222E004: ; 0x0222E004
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x58
	add r5, r0, #0
	add r0, #0xdc
	ldr r0, [r0]
	mov r4, #0
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xe0
	ldr r7, [r0]
	add r0, sp, #4
	strh r4, [r0, #0x20]
	strh r4, [r0, #0x22]
	strh r4, [r0, #0x24]
	strh r4, [r0, #0x26]
	mov r0, #0x3c
	str r0, [sp, #0x2c]
	mov r0, #2
	str r0, [sp, #0x34]
	mov r0, #1
	str r0, [sp, #0x50]
	sub r0, r0, #2
	str r0, [sp, #0x48]
	str r0, [sp, #0x4c]
	ldr r0, _0222E0B4 ; =0x000066B4
	str r4, [sp, #0x54]
	str r0, [sp, #0x3c]
	ldr r0, _0222E0B8 ; =0x00006A2C
	str r4, [sp, #0x30]
	str r0, [sp, #0x40]
	ldr r0, _0222E0BC ; =0x00006DB8
	str r0, [sp, #0x44]
	mov r0, #0xf9
	lsl r0, r0, #2
	add r6, r5, r0
_0222E04A:
	ldr r0, _0222E0C0 ; =0x000061A8
	add r1, r7, #0
	add r0, r4, r0
	str r0, [sp, #0x38]
	ldr r0, [sp]
	add r2, sp, #0x24
	bl FUN_0200C154
	add r4, r4, #1
	stmia r6!, {r0}
	cmp r4, #8
	blt _0222E04A
	ldr r3, _0222E0C4 ; =MOD62_02231158
	add r2, sp, #4
	mov r1, #0x10
_0222E068:
	ldrh r0, [r3]
	add r3, r3, #2
	strh r0, [r2]
	add r2, r2, #2
	sub r1, r1, #1
	bne _0222E068
	mov r7, #0xf9
	mov r6, #0
	add r4, sp, #4
	lsl r7, r7, #2
_0222E07C:
	mov r2, #2
	ldrsh r2, [r4, r2]
	mov r0, #0xf9
	mov r1, #0
	lsl r0, r0, #2
	sub r2, r2, #1
	lsl r2, r2, #0x10
	ldrsh r1, [r4, r1]
	ldr r0, [r5, r0]
	asr r2, r2, #0x10
	bl FUN_0200C714
	mov r0, #0xf9
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0200C5A8
	ldr r0, [r5, r7]
	mov r1, #0
	bl FUN_0200C61C
	add r6, r6, #1
	add r4, r4, #4
	add r5, r5, #4
	cmp r6, #8
	blt _0222E07C
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222E0B4: .word 0x000066B4
_0222E0B8: .word 0x00006A2C
_0222E0BC: .word 0x00006DB8
_0222E0C0: .word 0x000061A8
_0222E0C4: .word MOD62_02231158
	thumb_func_end MOD62_0222E004

	thumb_func_start MOD62_0222E0C8
MOD62_0222E0C8: ; 0x0222E0C8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r7, #0xf9
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_0222E0D4:
	add r0, r6, #0
	add r0, #0xe0
	ldr r1, _0222E0F4 ; =0x000061A8
	ldr r0, [r0]
	add r1, r4, r1
	bl FUN_0200C358
	ldr r0, [r5, r7]
	bl FUN_0200C3DC
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #8
	blt _0222E0D4
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E0F4: .word 0x000061A8
	thumb_func_end MOD62_0222E0C8

	thumb_func_start MOD62_0222E0F8
MOD62_0222E0F8: ; 0x0222E0F8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r1, #0
	mov r4, #0
	str r0, [sp]
	str r4, [sp, #4]
	add r5, r7, #0
	add r6, r7, #0
_0222E108:
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	cmp r1, #0
	beq _0222E120
	add r0, r6, #0
	bl MOD08_02217F08
	cmp r0, #1
	bne _0222E120
	mov r0, #1
	str r0, [sp, #4]
_0222E120:
	add r4, r4, #1
	add r5, r5, #4
	add r6, #0x24
	cmp r4, #8
	blt _0222E108
	mov r0, #0x12
	lsl r0, r0, #4
	add r0, r7, r0
	bl MOD08_02217ECC
	cmp r0, #1
	bne _0222E160
	mov r3, #0x59
	mov r0, #1
	lsl r3, r3, #2
	str r0, [sp, #4]
	ldr r0, [r7, r3]
	sub r3, #0x44
	ldrsh r3, [r7, r3]
	mov r1, #5
	mov r2, #0
	bl FUN_020179E0
	mov r3, #0x59
	lsl r3, r3, #2
	ldr r0, [r7, r3]
	sub r3, #0x42
	ldrsh r3, [r7, r3]
	mov r1, #5
	mov r2, #3
	bl FUN_020179E0
_0222E160:
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _0222E17C
	mov r0, #0x5b
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	mov r1, #0
	str r1, [r0]
	add r0, r7, #0
	bl FreeToHeap
	ldr r0, [sp]
	bl FUN_0200CAB4
_0222E17C:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD62_0222E0F8

	thumb_func_start MOD62_0222E180
MOD62_0222E180: ; 0x0222E180
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	str r1, [sp, #0xc]
	mov r1, #0x17
	str r0, [sp, #8]
	mov r0, #0x35
	lsl r1, r1, #4
	str r2, [sp, #0x10]
	bl AllocFromHeap
	str r0, [sp, #0x1c]
	ldr r0, [sp, #8]
	mov r1, #0x59
	add r0, #0xe4
	ldr r2, [r0]
	ldr r0, [sp, #0x1c]
	lsl r1, r1, #2
	str r2, [r0, r1]
	add r4, r0, #0
	add r5, r0, #0
	ldr r0, [sp, #0xc]
	mov r1, #0x38
	lsl r0, r0, #4
	neg r0, r0
	str r0, [sp, #0x18]
	ldr r0, [sp, #0xc]
	ldr r6, [sp, #8]
	mul r1, r0
	ldr r0, [sp, #0x10]
	mov r7, #0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r1, [sp, #0x14]
	str r0, [sp, #0x20]
_0222E1C4:
	mov r0, #0xc9
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	cmp r0, #0
	bne _0222E1D8
	mov r0, #0x51
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _0222E22E
_0222E1D8:
	mov r0, #0xcb
	lsl r0, r0, #2
	ldr r1, [r6, r0]
	mov r0, #0x51
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r1, sp, #0x24
	ldr r0, [r4, r0]
	add r1, #2
	add r2, sp, #0x24
	bl FUN_0200C7A0
	add r1, sp, #0x24
	mov r0, #0
	ldrsh r3, [r1, r0]
	mov r0, #2
	ldrsh r1, [r1, r0]
	ldr r0, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r0, r3, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	ldr r0, [sp, #0x20]
	add r2, r1, r2
	lsl r2, r2, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	asr r2, r2, #0x10
	bl MOD08_02217E80
	mov r1, #0x51
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	add r0, r5, #0
	bl MOD08_02217F08
	mov r1, #0x51
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	add r0, r5, #0
	bl MOD08_02217F08
_0222E22E:
	add r7, r7, #1
	add r6, #0x10
	add r4, r4, #4
	add r5, #0x24
	cmp r7, #8
	blt _0222E1C4
	mov r1, #0x59
	ldr r0, [sp, #0x1c]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r1, #5
	bl FUN_02017B48
	add r4, r0, #0
	mov r1, #0x59
	ldr r0, [sp, #0x1c]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r1, #5
	bl FUN_02017B54
	add r3, r0, #0
	ldr r0, [sp, #0xc]
	mov r5, #0x37
	lsl r0, r0, #4
	add r0, r3, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	ldr r0, [sp, #0x10]
	mov r1, #0x12
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	lsl r3, r3, #0x10
	ldr r2, [sp, #0xc]
	mvn r5, r5
	mul r5, r2
	add r2, r4, r5
	lsl r2, r2, #0x10
	ldr r0, [sp, #0x1c]
	lsl r1, r1, #4
	add r0, r0, r1
	lsl r1, r4, #0x10
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	asr r3, r3, #0x10
	bl MOD08_02217E80
	mov r2, #0x96
	lsl r2, r2, #2
	ldr r0, [sp, #8]
	add r1, r2, #0
	add r3, r0, r2
	ldr r0, [sp, #0x1c]
	sub r1, #0xec
	str r3, [r0, r1]
	sub r2, #0xec
	ldr r0, [r0, r2]
	mov r3, #1
	str r3, [r0]
	ldr r0, _0222E2B8 ; =MOD62_0222E0F8
	ldr r1, [sp, #0x1c]
	lsl r2, r3, #0xc
	bl FUN_0200CA44
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E2B8: .word MOD62_0222E0F8
	thumb_func_end MOD62_0222E180

	thumb_func_start MOD62_0222E2BC
MOD62_0222E2BC: ; 0x0222E2BC
	push {r3, lr}
	sub sp, #8
	mov r2, #2
	mov r1, #0
	ldr r0, _0222E2D8 ; =MOD62_0222E2DC
	str r2, [sp]
	str r0, [sp, #4]
	mov r0, #0x35
	add r3, r1, #0
	bl FUN_02022318
	add sp, #8
	pop {r3, pc}
	nop
_0222E2D8: .word MOD62_0222E2DC
	thumb_func_end MOD62_0222E2BC

	thumb_func_start MOD62_0222E2DC
MOD62_0222E2DC: ; 0x0222E2DC
	push {r3, lr}
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	ldr r0, _0222E348 ; =0x04000008
	mov r1, #3
	ldrh r2, [r0]
	bic r2, r1
	mov r1, #1
	orr r1, r2
	strh r1, [r0]
	add r0, #0x58
	ldrh r2, [r0]
	ldr r1, _0222E34C ; =0xFFFFCFFD
	and r2, r1
	strh r2, [r0]
	add r2, r1, #2
	ldrh r3, [r0]
	add r1, r1, #2
	and r3, r2
	mov r2, #0x10
	orr r2, r3
	strh r2, [r0]
	ldrh r3, [r0]
	ldr r2, _0222E350 ; =0x0000CFFB
	and r3, r2
	strh r3, [r0]
	ldrh r3, [r0]
	sub r2, #0x1c
	and r3, r1
	mov r1, #8
	orr r1, r3
	strh r1, [r0]
	ldrh r1, [r0]
	and r1, r2
	strh r1, [r0]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl G3X_SetFog
	mov r0, #0
	ldr r2, _0222E354 ; =0x00007FFF
	add r1, r0, #0
	mov r3, #0x3f
	str r0, [sp]
	bl G3X_SetClearColor
	ldr r1, _0222E358 ; =0xBFFF0000
	ldr r0, _0222E35C ; =0x04000580
	str r1, [r0]
	pop {r3, pc}
	.align 2, 0
_0222E348: .word 0x04000008
_0222E34C: .word 0xFFFFCFFD
_0222E350: .word 0x0000CFFB
_0222E354: .word 0x00007FFF
_0222E358: .word 0xBFFF0000
_0222E35C: .word 0x04000580
	thumb_func_end MOD62_0222E2DC

	thumb_func_start MOD62_0222E360
MOD62_0222E360: ; 0x0222E360
	push {r3, r4, r5, lr}
	ldr r3, _0222E398 ; =UNK_021064B8
	mov r0, #2
	mov r1, #0
	ldr r3, [r3]
	lsl r0, r0, #0xe
	add r2, r1, #0
	blx r3
	ldr r3, _0222E39C ; =UNK_021064C0
	mov r1, #0
	add r4, r0, #0
	ldr r3, [r3]
	mov r0, #0x80
	add r2, r1, #0
	blx r3
	add r5, r0, #0
	cmp r4, #0
	bne _0222E388
	bl ErrorHandling
_0222E388:
	cmp r5, #0
	bne _0222E390
	bl ErrorHandling
_0222E390:
	bl FUN_02012CC8
	pop {r3, r4, r5, pc}
	nop
_0222E398: .word UNK_021064B8
_0222E39C: .word UNK_021064C0
	thumb_func_end MOD62_0222E360

	thumb_func_start MOD62_0222E3A0
MOD62_0222E3A0: ; 0x0222E3A0
	push {r3, lr}
	bl FUN_020222AC
	bl FUN_02013364
	cmp r0, #0
	ble _0222E3B6
	bl FUN_020222AC
	bl FUN_020B02C8
_0222E3B6:
	bl FUN_02013388
	mov r0, #1
	mov r1, #0
	bl FUN_020222B4
	pop {r3, pc}
	thumb_func_end MOD62_0222E3A0

	thumb_func_start MOD62_0222E3C4
MOD62_0222E3C4: ; 0x0222E3C4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	str r1, [sp, #0x18]
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x58]
	add r0, r3, #0
	add r6, r2, #0
	str r3, [sp, #0x1c]
	bl MOD62_0222F89C
	cmp r0, #3
	bhi _0222E442
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222E3E8: ; jump table
	.short _0222E3F0 - _0222E3E8 - 2 ; case 0
	.short _0222E402 - _0222E3E8 - 2 ; case 1
	.short _0222E418 - _0222E3E8 - 2 ; case 2
	.short _0222E42E - _0222E3E8 - 2 ; case 3
_0222E3F0:
	mov r0, #0
	str r0, [sp, #0x24]
	mov r0, #4
	str r0, [sp, #0x28]
	mov r0, #1
	mov r5, #0xd
	mov r4, #6
	str r0, [sp, #0x2c]
	b _0222E442
_0222E402:
	mov r0, #2
	str r0, [sp, #0x24]
	mov r0, #0
	str r0, [sp, #0x28]
	mov r0, #4
	str r0, [sp, #0x2c]
	mov r0, #1
	mov r5, #0xb
	mov r4, #8
	str r0, [sp, #0x30]
	b _0222E442
_0222E418:
	mov r0, #3
	str r0, [sp, #0x24]
	mov r0, #0
	str r0, [sp, #0x28]
	mov r0, #4
	str r0, [sp, #0x2c]
	mov r0, #1
	mov r5, #0xb
	mov r4, #8
	str r0, [sp, #0x30]
	b _0222E442
_0222E42E:
	mov r0, #2
	str r0, [sp, #0x24]
	mov r0, #0
	str r0, [sp, #0x28]
	mov r0, #4
	str r0, [sp, #0x2c]
	mov r0, #1
	mov r5, #0xb
	mov r4, #8
	str r0, [sp, #0x30]
_0222E442:
	lsr r0, r4, #0x1f
	add r0, r4, r0
	asr r7, r0, #1
	ldr r0, [sp, #0x18]
	bl FUN_0201901C
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #9
	str r0, [sp, #4]
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xe
	str r0, [sp, #0xc]
	mov r0, #0xa6
	str r0, [sp, #0x10]
	lsl r2, r6, #0x18
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	lsr r2, r2, #0x18
	mov r3, #0x15
	bl FUN_02019064
	add r0, r7, #0
	mov r1, #0x35
	bl ListMenu_ctor
	mov r2, #0x67
	ldr r1, [sp, #0x1c]
	lsl r2, r2, #2
	str r0, [r1, r2]
	mov r0, #0
	mov r1, #0x1a
	mov r2, #8
	mov r3, #0x35
	bl NewMsgDataFromNarc
	mov r6, #0
	str r0, [sp, #0x20]
	cmp r7, #0
	ble _0222E4D0
	add r5, sp, #0x24
_0222E49A:
	ldr r1, [r5]
	ldr r0, [sp, #0x20]
	lsl r2, r1, #3
	ldr r1, _0222E538 ; =MOD62_02231358
	ldr r1, [r1, r2]
	bl NewString_ReadMsgData
	ldr r2, [r5]
	add r4, r0, #0
	lsl r3, r2, #3
	ldr r2, _0222E538 ; =MOD62_02231358
	mov r0, #0x67
	add r2, r2, r3
	ldr r1, [sp, #0x1c]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r2, [r2, #4]
	add r1, r4, #0
	bl ListMenu_AddItem
	add r0, r4, #0
	bl String_dtor
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, r7
	blt _0222E49A
_0222E4D0:
	ldr r0, [sp, #0x20]
	bl DestroyMsgData
	mov r1, #0x67
	ldr r0, [sp, #0x1c]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r1, #0
	str r0, [sp, #0x34]
	add r0, sp, #0x24
	strb r1, [r0, #0x18]
	ldr r1, [sp, #0x18]
	mov r2, #0xf
	str r1, [sp, #0x38]
	mov r1, #1
	strb r1, [r0, #0x19]
	strb r7, [r0, #0x1a]
	ldrb r3, [r0, #0x1b]
	bic r3, r2
	strb r3, [r0, #0x1b]
	ldrb r3, [r0, #0x1b]
	mov r2, #0x30
	bic r3, r2
	strb r3, [r0, #0x1b]
	ldrb r3, [r0, #0x1b]
	mov r2, #0xc0
	bic r3, r2
	mov r2, #0x40
	orr r2, r3
	strb r2, [r0, #0x1b]
	ldr r0, [sp, #0x18]
	mov r2, #0x1f
	mov r3, #0xd
	bl FUN_0200CCA4
	mov r0, #0x35
	str r0, [sp]
	mov r0, #2
	mov r2, #0
	str r0, [sp, #4]
	add r0, sp, #0x34
	mov r1, #8
	add r3, r2, #0
	bl FUN_02001C14
	mov r2, #0x1a
	ldr r1, [sp, #0x1c]
	lsl r2, r2, #4
	str r0, [r1, r2]
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E538: .word MOD62_02231358
	thumb_func_end MOD62_0222E3C4

	thumb_func_start MOD62_0222E53C
MOD62_0222E53C: ; 0x0222E53C
	push {r4, r5}
	lsr r5, r0, #0x1f
	lsl r4, r0, #0x1e
	sub r4, r4, r5
	mov r3, #0x1e
	ror r4, r3
	add r4, r5, r4
	mov r3, #0x38
	mul r3, r4
	add r3, #0x28
	strh r3, [r1]
	asr r1, r0, #2
	mov r0, #0x35
	mul r0, r1
	add r0, #0x1b
	strh r0, [r2]
	pop {r4, r5}
	bx lr
	thumb_func_end MOD62_0222E53C

	thumb_func_start MOD62_0222E560
MOD62_0222E560: ; 0x0222E560
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r1, r0, #0
	add r1, #0xdc
	ldr r4, [r1]
	add r1, r0, #0
	add r1, #0xe0
	add r0, #0xe8
	ldr r5, [r1]
	ldr r6, [r0]
	bl FUN_0206B888
	mov r1, #0x13
	str r1, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	mov r0, #0xfa
	lsl r0, r0, #6
	str r0, [sp, #0x14]
	add r0, r6, #0
	mov r1, #2
	add r2, r4, #0
	add r3, r5, #0
	bl FUN_0200C0DC
	bl FUN_0206B894
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _0222E5D0 ; =0x00004268
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x13
	bl FUN_0200C124
	bl FUN_0206B8A0
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _0222E5D4 ; =0x00004650
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x13
	bl FUN_0200C13C
	add sp, #0x18
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222E5D0: .word 0x00004268
_0222E5D4: .word 0x00004650
	thumb_func_end MOD62_0222E560

	thumb_func_start MOD62_0222E5D8
MOD62_0222E5D8: ; 0x0222E5D8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x4c
	add r5, r0, #0
	ldr r1, [r5]
	mov r6, #0
	ldr r0, [r1]
	cmp r0, #0
	ble _0222E6C6
	str r6, [sp, #0xc]
	add r4, r5, #0
_0222E5EC:
	ldr r0, [sp, #0xc]
	add r0, r1, r0
	ldr r7, [r0, #4]
	add r0, r7, #0
	bl FUN_0206B6C8
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _0222E6CC ; =0x00003A98
	add r1, r5, #0
	add r0, r6, r0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xdc
	add r1, #0xe0
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x13
	bl FUN_0200C978
	mov r1, #0
	add r0, sp, #0x18
	strh r1, [r0]
	strh r1, [r0, #2]
	strh r1, [r0, #4]
	strh r1, [r0, #6]
	mov r0, #0xa
	str r0, [sp, #0x20]
	add r0, r1, #0
	str r0, [sp, #0x24]
	mov r0, #1
	str r0, [sp, #0x28]
	mov r0, #2
	str r0, [sp, #0x44]
	add r0, r1, #0
	str r0, [sp, #0x48]
	ldr r0, _0222E6CC ; =0x00003A98
	add r2, sp, #0x18
	add r0, r6, r0
	str r0, [sp, #0x2c]
	mov r0, #0xfa
	lsl r0, r0, #6
	str r0, [sp, #0x30]
	ldr r0, _0222E6D0 ; =0x00004268
	str r0, [sp, #0x34]
	ldr r0, _0222E6D4 ; =0x00004650
	str r0, [sp, #0x38]
	sub r0, r1, #1
	str r0, [sp, #0x3c]
	sub r0, r1, #1
	str r0, [sp, #0x40]
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xdc
	add r1, #0xe0
	ldr r0, [r0]
	ldr r1, [r1]
	bl FUN_0200C154
	mov r1, #0xbf
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r7, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0x10]
	add r0, r7, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0x14]
	add r0, r7, #0
	mov r1, #0x70
	mov r2, #0
	bl GetMonData
	add r1, r0, #0
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x14]
	bl FUN_0206B7BC
	add r1, r0, #0
	mov r0, #0xbf
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r0, [r0]
	bl FUN_020202DC
	mov r0, #0xbf
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_0200C5C0
	ldr r0, [sp, #0xc]
	ldr r1, [r5]
	add r0, r0, #4
	str r0, [sp, #0xc]
	ldr r0, [r1]
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, r0
	blt _0222E5EC
_0222E6C6:
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
	nop
_0222E6CC: .word 0x00003A98
_0222E6D0: .word 0x00004268
_0222E6D4: .word 0x00004650
	thumb_func_end MOD62_0222E5D8

	thumb_func_start MOD62_0222E6D8
MOD62_0222E6D8: ; 0x0222E6D8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6]
	mov r4, #0
	ldr r0, [r0]
	cmp r0, #0
	ble _0222E700
	mov r7, #0xbf
	add r5, r6, #0
	lsl r7, r7, #2
_0222E6EC:
	ldr r0, [r5, r7]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r6]
	add r4, r4, #1
	ldr r0, [r0]
	add r5, r5, #4
	cmp r4, r0
	blt _0222E6EC
_0222E700:
	mov r5, #0
	add r4, r6, #0
_0222E704:
	ldr r7, [r4, #4]
	cmp r7, #0xff
	beq _0222E748
	add r1, sp, #0
	add r0, r5, #0
	add r1, #2
	add r2, sp, #0
	bl MOD62_0222E53C
	add r2, sp, #0
	mov r1, #2
	ldrsh r1, [r2, r1]
	add r3, r2, #0
	mov r2, #0
	ldrsh r2, [r3, r2]
	lsl r0, r7, #2
	add r7, r6, r0
	mov r0, #0xbf
	lsl r0, r0, #2
	sub r1, #0x10
	add r2, #0xc
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r7, r0]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	mov r0, #0xbf
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	mov r1, #1
	bl FUN_0200C644
_0222E748:
	add r5, r5, #1
	add r4, #8
	cmp r5, #0xc
	blt _0222E704
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD62_0222E6D8

	thumb_func_start MOD62_0222E754
MOD62_0222E754: ; 0x0222E754
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6]
	mov r4, #0
	ldr r0, [r0]
	cmp r0, #0
	ble _0222E77A
	mov r7, #0xbf
	add r5, r6, #0
	lsl r7, r7, #2
_0222E768:
	ldr r0, [r5, r7]
	bl FUN_0200C5A8
	ldr r0, [r6]
	add r4, r4, #1
	ldr r0, [r0]
	add r5, r5, #4
	cmp r4, r0
	blt _0222E768
_0222E77A:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD62_0222E754

	thumb_func_start MOD62_0222E77C
MOD62_0222E77C: ; 0x0222E77C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6]
	mov r4, #0
	ldr r0, [r0]
	cmp r0, #0
	ble _0222E7A2
	mov r7, #0xbf
	add r5, r6, #0
	lsl r7, r7, #2
_0222E790:
	ldr r0, [r5, r7]
	bl FUN_0200C3DC
	ldr r0, [r6]
	add r4, r4, #1
	ldr r0, [r0]
	add r5, r5, #4
	cmp r4, r0
	blt _0222E790
_0222E7A2:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD62_0222E77C

	thumb_func_start MOD62_0222E7A4
MOD62_0222E7A4: ; 0x0222E7A4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r6, #0
	add r4, r7, #0
	add r5, r7, #0
_0222E7AE:
	ldr r0, [r4, #8]
	bl MOD62_0222F870
	mov r1, #0x9a
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0x99
	ldr r1, [r4, #4]
	lsl r0, r0, #2
	str r1, [r5, r0]
	add r0, r0, #4
	ldr r0, [r5, r0]
	cmp r0, #0
	bne _0222E7DC
	mov r0, #0x99
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0xff
	beq _0222E7DC
	add r0, r7, #0
	add r1, r6, #0
	bl MOD62_02230D38
_0222E7DC:
	add r6, r6, #1
	add r4, #8
	add r5, #0xc
	cmp r6, #0xc
	blt _0222E7AE
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD62_0222E7A4

	thumb_func_start MOD62_0222E7E8
MOD62_0222E7E8: ; 0x0222E7E8
	push {r3, r4, r5, r6, lr}
	sub sp, #0x4c
	add r4, r0, #0
	mov r0, #0x35
	bl FUN_0200BB14
	add r2, sp, #0x2c
	ldr r5, _0222E868 ; =MOD62_02231138
	str r0, [r4, #8]
	ldmia r5!, {r0, r1}
	add r3, r2, #0
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	ldr r6, _0222E86C ; =MOD62_0223110C
	stmia r2!, {r0, r1}
	add r5, sp, #0x18
	ldmia r6!, {r0, r1}
	add r2, r5, #0
	stmia r5!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	add r1, r3, #0
	str r0, [r5]
	ldr r0, [r4, #8]
	mov r3, #0x20
	bl FUN_0200BB6C
	ldr r3, _0222E870 ; =MOD62_02231120
	add r2, sp, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r4, #8]
	bl FUN_0200BB34
	str r0, [r4, #0xc]
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	mov r2, #0x80
	bl FUN_0200BBF0
	cmp r0, #0
	bne _0222E852
	bl ErrorHandling
_0222E852:
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	add r2, sp, #0
	bl FUN_0200BF60
	cmp r0, #0
	bne _0222E864
	bl ErrorHandling
_0222E864:
	add sp, #0x4c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0222E868: .word MOD62_02231138
_0222E86C: .word MOD62_0223110C
_0222E870: .word MOD62_02231120
	thumb_func_end MOD62_0222E7E8

	thumb_func_start MOD62_0222E874
MOD62_0222E874: ; 0x0222E874
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	bl FUN_0200C398
	ldr r0, [r4, #8]
	bl FUN_0200BD04
	pop {r4, pc}
	thumb_func_end MOD62_0222E874

	thumb_func_start MOD62_0222E888
MOD62_0222E888: ; 0x0222E888
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _0222E8EC ; =0x0000AFC8
	add r1, r4, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0xdc
	add r1, #0xe0
	mov r2, #0x5b
	add r3, r2, #0
	ldr r0, [r0]
	ldr r1, [r1]
	add r3, #0xae
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _0222E8F0 ; =0x0000B798
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0xdc
	add r1, #0xe0
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x5b
	mov r3, #0xad
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0222E8F4 ; =0x0000BB80
	mov r2, #0x5b
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0xdc
	add r4, #0xe0
	ldr r0, [r0]
	ldr r1, [r4]
	mov r3, #0x51
	bl FUN_0200C13C
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_0222E8EC: .word 0x0000AFC8
_0222E8F0: .word 0x0000B798
_0222E8F4: .word 0x0000BB80
	thumb_func_end MOD62_0222E888

	thumb_func_start MOD62_0222E8F8
MOD62_0222E8F8: ; 0x0222E8F8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x64
	ldr r4, _0222E97C ; =MOD62_02231178
	add r6, r0, #0
	add r3, sp, #0
	mov r2, #6
_0222E904:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222E904
	mov r7, #0
	add r4, sp, #0
	add r5, r6, #0
_0222E912:
	ldr r1, [r4]
	add r0, sp, #0
	strh r1, [r0, #0x30]
	ldr r1, [r4, #4]
	add r2, sp, #0x30
	strh r1, [r0, #0x32]
	mov r1, #0
	strh r1, [r0, #0x34]
	strh r1, [r0, #0x36]
	mov r0, #0x28
	str r0, [sp, #0x38]
	mov r0, #2
	str r0, [sp, #0x3c]
	str r0, [sp, #0x40]
	mov r0, #1
	str r0, [sp, #0x5c]
	add r0, r1, #0
	str r0, [sp, #0x60]
	ldr r0, _0222E980 ; =0x0000AFC8
	str r0, [sp, #0x44]
	ldr r0, _0222E984 ; =0x000066B2
	str r0, [sp, #0x48]
	ldr r0, _0222E988 ; =0x0000B798
	str r0, [sp, #0x4c]
	ldr r0, _0222E98C ; =0x0000BB80
	str r0, [sp, #0x50]
	sub r0, r1, #1
	str r0, [sp, #0x54]
	sub r0, r1, #1
	str r0, [sp, #0x58]
	add r0, r6, #0
	add r1, r6, #0
	add r0, #0xdc
	add r1, #0xe0
	ldr r0, [r0]
	ldr r1, [r1]
	bl FUN_0200C154
	mov r1, #0xc5
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	ldr r1, [r4, #8]
	bl FUN_0200C8D0
	add r7, r7, #1
	add r4, #0xc
	add r5, r5, #4
	cmp r7, #4
	blt _0222E912
	add sp, #0x64
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0222E97C: .word MOD62_02231178
_0222E980: .word 0x0000AFC8
_0222E984: .word 0x000066B2
_0222E988: .word 0x0000B798
_0222E98C: .word 0x0000BB80
	thumb_func_end MOD62_0222E8F8

	thumb_func_start MOD62_0222E990
MOD62_0222E990: ; 0x0222E990
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, #0xd8
	ldr r0, [r0]
	cmp r0, #0
	beq _0222E9B0
	mov r6, #0xc5
	mov r4, #0
	lsl r6, r6, #2
_0222E9A2:
	ldr r0, [r5, r6]
	bl FUN_0200C5A8
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0222E9A2
_0222E9B0:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD62_0222E990

	thumb_func_start MOD62_0222E9B4
MOD62_0222E9B4: ; 0x0222E9B4
	push {r3, r4, r5, r6, r7, lr}
	mov r7, #0xc5
	add r5, r0, #0
	add r6, r1, #0
	mov r4, #0
	lsl r7, r7, #2
_0222E9C0:
	ldr r0, [r5, r7]
	add r1, r6, #0
	bl FUN_0200C644
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0222E9C0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD62_0222E9B4

	thumb_func_start MOD62_0222E9D4
MOD62_0222E9D4: ; 0x0222E9D4
	push {r4, r5, r6, lr}
	mov r6, #0xc5
	add r5, r0, #0
	mov r4, #0
	lsl r6, r6, #2
_0222E9DE:
	ldr r0, [r5, r6]
	bl FUN_0200C3DC
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0222E9DE
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD62_0222E9D4

	thumb_func_start MOD62_0222E9F0
MOD62_0222E9F0: ; 0x0222E9F0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	mov r6, #1
	str r6, [sp]
	ldr r6, [sp, #0x3c]
	add r7, r2, #0
	str r6, [sp, #4]
	ldr r6, _0222EA68 ; =0x00002AF8
	add r2, r3, #0
	add r2, r2, r6
	str r2, [sp, #8]
	mov r2, #0x5b
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200C00C
	mov r0, #0x5b
	str r0, [sp]
	ldr r0, [sp, #0x30]
	mov r1, #0
	str r0, [sp, #4]
	str r1, [sp, #8]
	ldr r1, [sp, #0x44]
	add r2, r5, #0
	str r1, [sp, #0xc]
	ldr r1, [sp, #0x3c]
	add r3, r4, #0
	str r1, [sp, #0x10]
	add r1, r6, #0
	add r0, r0, r1
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x40]
	add r0, r7, #0
	bl FUN_0200C0DC
	mov r0, #1
	str r0, [sp]
	ldr r3, [sp, #0x34]
	add r0, r6, #0
	add r0, r3, r0
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x5b
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r3, [sp, #0x38]
	add r0, r6, #0
	add r0, r3, r0
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x5b
	bl FUN_0200C13C
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222EA68: .word 0x00002AF8
	thumb_func_end MOD62_0222E9F0

	thumb_func_start MOD62_0222EA6C
MOD62_0222EA6C: ; 0x0222EA6C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x54
	add r5, r0, #0
	ldr r0, _0222EC14 ; =0x0000011E
	add r2, r5, #0
	str r0, [sp]
	mov r0, #0xae
	str r0, [sp, #4]
	mov r3, #0x52
	str r3, [sp, #8]
	mov r1, #1
	str r1, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	str r1, [sp, #0x14]
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xdc
	add r1, #0xe0
	add r2, #0xe8
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, [r2]
	add r3, #0xb8
	bl MOD62_0222E9F0
	ldr r0, _0222EC18 ; =0x00000123
	add r2, r5, #0
	str r0, [sp]
	mov r0, #0xb3
	str r0, [sp, #4]
	mov r3, #0x57
	str r3, [sp, #8]
	mov r1, #1
	str r1, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	str r1, [sp, #0x14]
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xdc
	add r1, #0xe0
	add r2, #0xe8
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, [r2]
	add r3, #0xbc
	bl MOD62_0222E9F0
	mov r6, #0
	add r4, r5, #0
	add r7, sp, #0x18
_0222EAD4:
	mov r0, #0
	strh r0, [r7, #8]
	strh r0, [r7, #0xa]
	strh r0, [r7, #0xc]
	mov r0, #0x9a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r5, #0
	strh r0, [r7, #0xe]
	mov r0, #0x28
	sub r0, r0, r6
	str r0, [sp, #0x28]
	mov r0, #0
	str r0, [sp, #0x2c]
	mov r0, #1
	str r0, [sp, #0x30]
	mov r0, #2
	str r0, [sp, #0x4c]
	mov r0, #0
	str r0, [sp, #0x50]
	ldr r0, _0222EC1C ; =0x00002C02
	add r1, #0xe0
	str r0, [sp, #0x34]
	add r0, #0x14
	str r0, [sp, #0x38]
	ldr r0, _0222EC20 ; =0x00002BA6
	add r2, sp, #0x20
	str r0, [sp, #0x3c]
	sub r0, #0x5c
	str r0, [sp, #0x40]
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x44]
	str r0, [sp, #0x48]
	add r0, r5, #0
	add r0, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	bl FUN_0200C154
	mov r1, #0x9b
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r1, sp, #0x1c
	add r0, r6, #0
	add r1, #2
	add r2, sp, #0x1c
	bl MOD62_0222E53C
	mov r0, #0x9b
	mov r1, #6
	mov r2, #4
	lsl r0, r0, #2
	ldrsh r1, [r7, r1]
	ldrsh r2, [r7, r2]
	ldr r0, [r4, r0]
	bl FUN_0200C714
	add r6, r6, #1
	add r4, #0xc
	cmp r6, #0xc
	blt _0222EAD4
	mov r1, #0
	add r0, sp, #0x18
	strh r1, [r0, #8]
	strh r1, [r0, #0xa]
	strh r1, [r0, #0xc]
	strh r1, [r0, #0xe]
	mov r0, #0x14
	str r0, [sp, #0x28]
	mov r0, #1
	str r1, [sp, #0x2c]
	str r1, [sp, #0x50]
	ldr r1, _0222EC24 ; =0x00002C0B
	str r0, [sp, #0x30]
	add r0, r1, #0
	add r0, #0x10
	str r0, [sp, #0x38]
	add r0, r1, #0
	mov r2, #2
	sub r0, #0x60
	str r1, [sp, #0x34]
	str r0, [sp, #0x3c]
	sub r0, r2, #3
	sub r1, #0xbc
	str r1, [sp, #0x40]
	add r1, r5, #0
	str r2, [sp, #0x4c]
	str r0, [sp, #0x44]
	str r0, [sp, #0x48]
	add r0, r5, #0
	add r0, #0xdc
	add r1, #0xe0
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, sp, #0x20
	bl FUN_0200C154
	mov r1, #0xbd
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xdc
	add r1, #0xe0
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, sp, #0x20
	bl FUN_0200C154
	mov r1, #0xbe
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r1, #0xcc
	ldr r0, [r5, r1]
	add r1, sp, #0x18
	add r1, #2
	add r2, sp, #0x18
	bl MOD62_0222E53C
	mov r0, #0xbd
	lsl r0, r0, #2
	add r3, sp, #0x18
	mov r1, #2
	mov r2, #0
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldr r0, [r5, r0]
	bl FUN_0200C714
	mov r0, #0xbe
	lsl r0, r0, #2
	add r3, sp, #0x18
	mov r1, #2
	mov r2, #0
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldr r0, [r5, r0]
	bl FUN_0200C714
	mov r0, #0xbe
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x19
	bl FUN_0200C6C4
	mov r0, #0xbd
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_0200C5C0
	mov r0, #0xbe
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_0200C5C0
	add sp, #0x54
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0222EC14: .word 0x0000011E
_0222EC18: .word 0x00000123
_0222EC1C: .word 0x00002C02
_0222EC20: .word 0x00002BA6
_0222EC24: .word 0x00002C0B
	thumb_func_end MOD62_0222EA6C

	thumb_func_start MOD62_0222EC28
MOD62_0222EC28: ; 0x0222EC28
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl MOD62_0222E7A4
	add r0, r5, #0
	bl MOD62_0222E6D8
	mov r7, #0x9a
	lsl r7, r7, #2
	mov r4, #0
	add r6, r7, #4
_0222EC3E:
	ldr r0, [r5, r6]
	cmp r0, #0
	beq _0222EC4A
	ldr r1, [r5, r7]
	bl FUN_0200C5C0
_0222EC4A:
	add r4, r4, #1
	add r5, #0xc
	cmp r4, #0xc
	blt _0222EC3E
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD62_0222EC28

	thumb_func_start MOD62_0222EC54
MOD62_0222EC54: ; 0x0222EC54
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r5, r0, #0
	lsl r6, r1, #3
	add r0, r5, r6
	ldr r0, [r0, #4]
	lsl r4, r2, #3
	str r1, [sp]
	add r1, r5, r4
	ldr r7, [r1, #4]
	cmp r0, #0xff
	beq _0222EC80
	add r1, r2, #1
	str r1, [sp, #0xc]
	ldr r1, [r5]
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, #4]
	mov r1, #0xa1
	add r2, sp, #0xc
	bl SetMonData
_0222EC80:
	cmp r7, #0xff
	beq _0222EC9A
	ldr r0, [sp]
	add r2, sp, #8
	add r0, r0, #1
	str r0, [sp, #8]
	ldr r1, [r5]
	lsl r0, r7, #2
	add r0, r1, r0
	ldr r0, [r0, #4]
	mov r1, #0xa1
	bl SetMonData
_0222EC9A:
	add r2, r5, #4
	ldr r1, [r2, r6]
	ldr r0, [r2, r4]
	add r7, r5, #0
	str r0, [r2, r6]
	str r1, [r2, r4]
	add r7, #8
	ldr r0, [r7, r6]
	add r1, sp, #0x10
	bl FUN_02029C74
	add r0, r5, #0
	str r0, [sp, #4]
	add r0, #8
	str r0, [sp, #4]
	ldr r0, [r0, r4]
	ldr r1, [r7, r6]
	bl FUN_02029C74
	ldr r1, [sp, #4]
	add r0, sp, #0x10
	ldr r1, [r1, r4]
	bl FUN_02029C74
	add r0, r5, #0
	bl MOD62_0222EC28
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD62_0222EC54

	thumb_func_start MOD62_0222ECD4
MOD62_0222ECD4: ; 0x0222ECD4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r6, #0x9b
	mov r4, #0
	add r5, r7, #0
	lsl r6, r6, #2
_0222ECE0:
	ldr r0, [r5, r6]
	bl FUN_0200C5A8
	add r4, r4, #1
	add r5, #0xc
	cmp r4, #0xc
	blt _0222ECE0
	mov r0, #0xbd
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	bl FUN_0200C5A8
	mov r0, #0xbe
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	bl FUN_0200C5A8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD62_0222ECD4

	thumb_func_start MOD62_0222ED04
MOD62_0222ED04: ; 0x0222ED04
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r6, #0x9b
	mov r4, #0
	add r5, r7, #0
	lsl r6, r6, #2
_0222ED10:
	ldr r0, [r5, r6]
	bl FUN_0200C3DC
	add r4, r4, #1
	add r5, #0xc
	cmp r4, #0xc
	blt _0222ED10
	mov r0, #0xbd
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	bl FUN_0200C3DC
	mov r0, #0xbe
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	bl FUN_0200C3DC
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD62_0222ED04

	thumb_func_start MOD62_0222ED34
MOD62_0222ED34: ; 0x0222ED34
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r6, r2, #0
	add r4, r1, #0
	lsl r1, r6, #0x18
	lsr r1, r1, #0x18
	str r1, [sp]
	mov r1, #0x35
	str r1, [sp, #4]
	mov r1, #1
	add r2, r1, #0
	mov r3, #0xf
	add r5, r0, #0
	bl FUN_0200CD68
	add r0, r6, #0
	bl FUN_0200CD64
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xc0
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x26
	mov r3, #0x35
	bl FUN_020030E8
	mov r0, #0
	str r0, [sp]
	mov r0, #0x35
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #1
	mov r2, #0x1f
	mov r3, #0xd
	bl FUN_0200CB00
	bl FUN_0200CAFC
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xd0
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x26
	mov r3, #0x35
	bl FUN_020030E8
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xe0
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0xe
	mov r2, #7
	mov r3, #0x35
	bl FUN_020030E8
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD62_0222ED34

	thumb_func_start MOD62_0222EDBC
MOD62_0222EDBC: ; 0x0222EDBC
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r6, r2, #0
	add r4, r1, #0
	lsl r1, r6, #0x18
	lsr r1, r1, #0x18
	str r1, [sp]
	mov r1, #0x35
	str r1, [sp, #4]
	mov r1, #4
	mov r2, #1
	mov r3, #0xf
	add r5, r0, #0
	bl FUN_0200CD68
	add r0, r6, #0
	bl FUN_0200CD64
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xc0
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x26
	mov r3, #0x35
	bl FUN_020030E8
	mov r0, #0
	str r0, [sp]
	mov r0, #0x35
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #4
	mov r2, #0x1f
	mov r3, #0xd
	bl FUN_0200CB00
	bl FUN_0200CAFC
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xd0
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x26
	mov r3, #0x35
	bl FUN_020030E8
	mov r0, #1
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xe0
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0xe
	mov r2, #7
	mov r3, #0x35
	bl FUN_020030E8
	mov r0, #1
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x30
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0xe
	mov r2, #7
	mov r3, #0x35
	bl FUN_020030E8
	mov r0, #1
	str r0, [sp]
	mov r0, #0x20
	mov r1, #0x5b
	str r0, [sp, #4]
	mov r0, #0xb0
	add r2, r1, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r2, #0xcb
	mov r3, #0x35
	bl FUN_020030E8
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD62_0222EDBC

	thumb_func_start MOD62_0222EE78
MOD62_0222EE78: ; 0x0222EE78
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r1, _0222EEDC ; =0x0000FFFF
	add r4, r0, #0
	cmp r5, r1
	bne _0222EE96
	mov r1, #0xf
	bl FUN_02019620
	add r0, r4, #0
	bl FUN_020191D0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0222EE96:
	mov r0, #0
	mov r1, #0x1a
	mov r2, #8
	mov r3, #0x35
	bl NewMsgDataFromNarc
	add r1, r5, #0
	add r6, r0, #0
	bl NewString_ReadMsgData
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #0xf
	bl FUN_02019620
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	add r0, r4, #0
	add r2, r5, #0
	add r3, r1, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r4, #0
	bl FUN_020191D0
	add r0, r5, #0
	bl String_dtor
	add r0, r6, #0
	bl DestroyMsgData
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0222EEDC: .word 0x0000FFFF
	thumb_func_end MOD62_0222EE78

	thumb_func_start MOD62_0222EEE0
MOD62_0222EEE0: ; 0x0222EEE0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r1, #0
	add r7, r0, #0
	add r0, r5, #0
	add r4, r2, #0
	add r6, r3, #0
	bl FUN_0201901C
	ldr r0, [sp, #0x28]
	lsl r2, r4, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [sp, #0x2c]
	lsl r3, r6, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	ldr r0, [sp, #0x30]
	add r1, r5, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xe
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x34]
	lsr r2, r2, #0x18
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	add r0, r7, #0
	lsr r3, r3, #0x18
	bl FUN_02019064
	mov r1, #1
	add r0, r5, #0
	add r2, r1, #0
	mov r3, #0xc
	bl FUN_0200D0BC
	add r0, r5, #0
	mov r1, #0xf
	bl FUN_02019620
	add r0, r5, #0
	bl FUN_020191D0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD62_0222EEE0

	thumb_func_start MOD62_0222EF44
MOD62_0222EF44: ; 0x0222EF44
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r1, #0
	add r7, r0, #0
	add r0, r5, #0
	add r4, r2, #0
	add r6, r3, #0
	bl FUN_0201901C
	ldr r0, [sp, #0x28]
	lsl r2, r4, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [sp, #0x2c]
	lsl r3, r6, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	ldr r0, [sp, #0x30]
	add r1, r5, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	ldr r0, [sp, #0x38]
	lsr r2, r2, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x34]
	lsr r3, r3, #0x18
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	add r0, r7, #0
	bl FUN_02019064
	add r0, r5, #0
	mov r1, #0xf
	bl FUN_02019620
	add r0, r5, #0
	bl FUN_020191D0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD62_0222EF44

	thumb_func_start MOD62_0222EFA0
MOD62_0222EFA0: ; 0x0222EFA0
	push {r3, r4, lr}
	sub sp, #0x14
	mov r1, #2
	add r4, r0, #0
	str r1, [sp]
	mov r0, #4
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0x94
	str r1, [sp, #0xc]
	mov r0, #0xb
	str r0, [sp, #0x10]
	add r0, r4, #0
	add r0, #0xe4
	add r1, #0x88
	ldr r0, [r0]
	add r1, r4, r1
	mov r2, #6
	mov r3, #3
	bl MOD62_0222EF44
	mov r1, #2
	str r1, [sp]
	mov r0, #4
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0x9c
	str r1, [sp, #0xc]
	mov r0, #0xb
	str r0, [sp, #0x10]
	add r0, r4, #0
	add r0, #0xe4
	add r1, #0x90
	ldr r0, [r0]
	add r1, r4, r1
	mov r2, #6
	mov r3, #0xa
	bl MOD62_0222EF44
	mov r0, #5
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r1, #0xa4
	str r1, [sp, #0xc]
	mov r0, #0xb
	str r0, [sp, #0x10]
	add r0, r4, #0
	add r0, #0xe4
	add r1, #0x98
	ldr r0, [r0]
	add r1, r4, r1
	mov r2, #6
	mov r3, #3
	bl MOD62_0222EF44
	mov r0, #5
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r1, #0xac
	str r1, [sp, #0xc]
	mov r0, #0xb
	str r0, [sp, #0x10]
	add r0, r4, #0
	add r0, #0xe4
	add r1, #0xa0
	ldr r0, [r0]
	add r1, r4, r1
	mov r2, #6
	mov r3, #0xa
	bl MOD62_0222EF44
	mov r0, #8
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r1, #0xb4
	str r1, [sp, #0xc]
	mov r0, #0xb
	str r0, [sp, #0x10]
	add r0, r4, #0
	add r0, #0xe4
	add r1, #0xa8
	ldr r0, [r0]
	add r1, r4, r1
	mov r2, #6
	mov r3, #3
	bl MOD62_0222EF44
	mov r0, #8
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r1, #0xbc
	str r1, [sp, #0xc]
	mov r0, #0xb
	str r0, [sp, #0x10]
	add r0, r4, #0
	add r0, #0xe4
	add r1, #0xb0
	ldr r0, [r0]
	add r1, r4, r1
	mov r2, #6
	mov r3, #0xa
	bl MOD62_0222EF44
	mov r2, #0xb
	str r2, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r1, #0xc4
	str r1, [sp, #0xc]
	add r0, r4, #0
	str r2, [sp, #0x10]
	add r0, #0xe4
	add r1, #0xb8
	ldr r0, [r0]
	add r1, r4, r1
	mov r2, #6
	mov r3, #3
	bl MOD62_0222EF44
	mov r2, #0xb
	str r2, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r1, #0xcc
	str r1, [sp, #0xc]
	add r0, r4, #0
	str r2, [sp, #0x10]
	add r0, #0xe4
	add r1, #0xc0
	ldr r0, [r0]
	add r1, r4, r1
	mov r2, #6
	mov r3, #0xa
	bl MOD62_0222EF44
	add sp, #0x14
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD62_0222EFA0

	thumb_func_start MOD62_0222F0D4
MOD62_0222F0D4: ; 0x0222F0D4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r0, #0
	add r5, r7, #0
	add r5, #0xec
	mov r6, #3
	add r5, #0x30
_0222F0E2:
	ldr r0, _0222F160 ; =0x0000041D
	add r1, r7, r6
	ldrb r0, [r1, r0]
	str r0, [sp, #0x10]
	cmp r0, #0
	bne _0222F0FE
	add r0, r5, #0
	mov r1, #0xee
	bl FUN_02019620
	add r0, r5, #0
	bl FUN_020191D0
	b _0222F152
_0222F0FE:
	add r0, r5, #0
	mov r1, #0
	bl FUN_02019620
	mov r0, #0x64
	mov r1, #0x35
	bl String_ctor
	ldr r1, [sp, #0x10]
	add r4, r0, #0
	ldr r0, [r7, #0x64]
	sub r1, r1, #1
	bl FUN_02029CF4
	add r1, r0, #0
	mov r0, #1
	str r0, [sp]
	add r0, r4, #0
	mov r2, #3
	mov r3, #1
	bl String16_FormatInteger
	mov r0, #0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0222F164 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r2, r4, #0
	mov r3, #7
	bl AddTextPrinterParameterized2
	add r0, r5, #0
	bl FUN_020191D0
	add r0, r4, #0
	bl String_dtor
_0222F152:
	add r6, r6, #1
	add r5, #0x10
	cmp r6, #0xb
	blt _0222F0E2
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0222F160: .word 0x0000041D
_0222F164: .word 0x00010200
	thumb_func_end MOD62_0222F0D4

	thumb_func_start MOD62_0222F168
MOD62_0222F168: ; 0x0222F168
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	add r0, r1, #3
	lsl r4, r0, #4
	mov r0, #0x42
	add r1, r6, r1
	lsl r0, r0, #4
	add r5, r6, #0
	ldrb r7, [r1, r0]
	add r5, #0xec
	cmp r7, #0
	bne _0222F194
	add r0, r5, r4
	mov r1, #0xee
	bl FUN_02019620
	add r0, r5, r4
	bl FUN_020191D0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_0222F194:
	add r0, r5, r4
	mov r1, #0
	bl FUN_02019620
	mov r0, #0x64
	mov r1, #0x35
	bl String_ctor
	str r0, [sp, #0x10]
	ldr r0, [r6, #0x64]
	sub r1, r7, #1
	bl FUN_02029CF4
	add r1, r0, #0
	mov r3, #1
	ldr r0, [sp, #0x10]
	mov r2, #3
	str r3, [sp]
	bl String16_FormatInteger
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0222F1E4 ; =0x00010200
	ldr r2, [sp, #0x10]
	str r0, [sp, #8]
	add r0, r5, r4
	mov r3, #7
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r5, r4
	bl FUN_020191D0
	ldr r0, [sp, #0x10]
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0222F1E4: .word 0x00010200
	thumb_func_end MOD62_0222F168

	thumb_func_start MOD62_0222F1E8
MOD62_0222F1E8: ; 0x0222F1E8
	push {r3, r4, r5, lr}
	add r0, #0xec
	add r5, r0, #0
	mov r4, #3
	add r5, #0x30
_0222F1F2:
	add r0, r5, #0
	bl FUN_02019570
	add r0, r5, #0
	bl FUN_02019178
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #0xb
	blt _0222F1F2
	pop {r3, r4, r5, pc}
	thumb_func_end MOD62_0222F1E8

	thumb_func_start MOD62_0222F208
MOD62_0222F208: ; 0x0222F208
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r1, _0222F26C ; =0x0000FFFF
	add r4, r0, #0
	cmp r5, r1
	bne _0222F226
	mov r1, #0xf
	bl FUN_02019620
	add r0, r4, #0
	bl FUN_020191D0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0222F226:
	mov r0, #0
	mov r1, #0x1a
	mov r2, #0xa
	mov r3, #0x35
	bl NewMsgDataFromNarc
	add r1, r5, #0
	add r6, r0, #0
	bl NewString_ReadMsgData
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #0xf
	bl FUN_02019620
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	add r0, r4, #0
	add r2, r5, #0
	add r3, r1, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r4, #0
	bl FUN_020191D0
	add r0, r5, #0
	bl String_dtor
	add r0, r6, #0
	bl DestroyMsgData
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0222F26C: .word 0x0000FFFF
	thumb_func_end MOD62_0222F208

	thumb_func_start MOD62_0222F270
MOD62_0222F270: ; 0x0222F270
	push {r3, lr}
	bl FUN_0201E788
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	pop {r3, pc}
	thumb_func_end MOD62_0222F270

	thumb_func_start MOD62_0222F288
MOD62_0222F288: ; 0x0222F288
	push {lr}
	sub sp, #0xc
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x35
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	add sp, #0xc
	pop {pc}
	.align 2, 0
	thumb_func_end MOD62_0222F288

	thumb_func_start MOD62_0222F2A8
MOD62_0222F2A8: ; 0x0222F2A8
	push {lr}
	sub sp, #0xc
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x35
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	add sp, #0xc
	pop {pc}
	thumb_func_end MOD62_0222F2A8

	thumb_func_start MOD62_0222F2C8
MOD62_0222F2C8: ; 0x0222F2C8
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x35
	add r2, r4, #0
	str r0, [sp, #0xc]
	mov r0, #0x5b
	add r2, #0xe4
	add r1, r0, #0
	ldr r2, [r2]
	add r1, #0xb1
	mov r3, #2
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x35
	add r2, r4, #0
	str r0, [sp, #0xc]
	mov r0, #0x5b
	add r2, #0xe4
	add r1, r0, #0
	ldr r2, [r2]
	add r1, #0xc1
	mov r3, #2
	bl FUN_020068C8
	mov r1, #0
	str r1, [sp]
	mov r0, #0x40
	str r0, [sp, #4]
	add r0, r4, #0
	str r1, [sp, #8]
	add r0, #0xe8
	mov r1, #0x5b
	add r2, r1, #0
	ldr r0, [r0]
	add r2, #0xc5
	mov r3, #0x35
	bl FUN_020030E8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x35
	add r2, r4, #0
	str r0, [sp, #0xc]
	mov r0, #0x5b
	add r2, #0xe4
	add r1, r0, #0
	ldr r2, [r2]
	add r1, #0xb2
	mov r3, #3
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x35
	str r0, [sp, #0xc]
	mov r0, #0x5b
	add r4, #0xe4
	add r1, r0, #0
	ldr r2, [r4]
	add r1, #0xc2
	mov r3, #3
	bl FUN_020068C8
	add sp, #0x10
	pop {r4, pc}
	thumb_func_end MOD62_0222F2C8

	thumb_func_start MOD62_0222F36C
MOD62_0222F36C: ; 0x0222F36C
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x35
	add r2, r4, #0
	str r0, [sp, #0xc]
	mov r0, #0x5b
	add r2, #0xe4
	add r1, r0, #0
	ldr r2, [r2]
	add r1, #0xb0
	mov r3, #5
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x35
	add r2, r4, #0
	str r0, [sp, #0xc]
	mov r0, #0x5b
	add r2, #0xe4
	add r1, r0, #0
	ldr r2, [r2]
	add r1, #0xc0
	mov r3, #5
	bl FUN_020068C8
	mov r0, #1
	str r0, [sp]
	mov r0, #0x40
	str r0, [sp, #4]
	mov r0, #0
	mov r1, #0x5b
	add r2, r1, #0
	add r4, #0xe8
	str r0, [sp, #8]
	ldr r0, [r4]
	add r2, #0xc4
	mov r3, #0x35
	bl FUN_020030E8
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD62_0222F36C

	thumb_func_start MOD62_0222F3D4
MOD62_0222F3D4: ; 0x0222F3D4
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x35
	add r2, r4, #0
	str r0, [sp, #0xc]
	mov r0, #0x5b
	add r2, #0xe4
	add r1, r0, #0
	ldr r2, [r2]
	add r1, #0xb0
	mov r3, #7
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x35
	add r2, r4, #0
	str r0, [sp, #0xc]
	mov r0, #0x5b
	add r2, #0xe4
	add r1, r0, #0
	ldr r2, [r2]
	add r1, #0xbf
	mov r3, #7
	bl FUN_020068C8
	mov r0, #1
	str r0, [sp]
	mov r0, #0x40
	str r0, [sp, #4]
	mov r0, #0
	mov r1, #0x5b
	add r2, r1, #0
	add r4, #0xe8
	str r0, [sp, #8]
	ldr r0, [r4]
	add r2, #0xc4
	mov r3, #0x35
	bl FUN_020030E8
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD62_0222F3D4

	thumb_func_start MOD62_0222F43C
MOD62_0222F43C: ; 0x0222F43C
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r1, r0, #0
	add r1, #0xdc
	ldr r4, [r1]
	add r1, r0, #0
	add r1, #0xe0
	ldr r5, [r1]
	mov r1, #0x5b
	str r1, [sp]
	add r1, #0xc7
	str r1, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	mov r1, #3
	str r1, [sp, #0xc]
	mov r2, #2
	str r2, [sp, #0x10]
	ldr r2, _0222F57C ; =0x000066B2
	add r0, #0xe8
	str r2, [sp, #0x14]
	ldr r0, [r0]
	add r2, r4, #0
	add r3, r5, #0
	bl FUN_0200C0DC
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _0222F580 ; =0x000062B9
	mov r2, #0x5b
	add r3, r2, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, r5, #0
	add r3, #0xb6
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _0222F584 ; =0x00006A29
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x5b
	mov r3, #0xb1
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0222F588 ; =0x00006DB5
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x5b
	mov r3, #0x55
	bl FUN_0200C13C
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _0222F58C ; =0x000062BA
	mov r2, #0x5b
	add r3, r2, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, r5, #0
	add r3, #0xb7
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _0222F590 ; =0x00006A2A
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x5b
	mov r3, #0xb2
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0222F594 ; =0x00006DB6
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x5b
	mov r3, #0x56
	bl FUN_0200C13C
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _0222F598 ; =0x000062B6
	mov r2, #0x5b
	add r3, r2, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, r5, #0
	add r3, #0xb3
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _0222F59C ; =0x00006A27
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x5b
	mov r3, #0xaf
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0222F5A0 ; =0x00006DB3
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x5b
	mov r3, #0x53
	bl FUN_0200C13C
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _0222F5A4 ; =0x000089C8
	mov r2, #0x5b
	add r3, r2, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, r5, #0
	add r3, #0xb5
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _0222F5A8 ; =0x00006A28
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x5b
	mov r3, #0xb0
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0222F5AC ; =0x00006DB4
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x5b
	mov r3, #0x54
	bl FUN_0200C13C
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222F57C: .word 0x000066B2
_0222F580: .word 0x000062B9
_0222F584: .word 0x00006A29
_0222F588: .word 0x00006DB5
_0222F58C: .word 0x000062BA
_0222F590: .word 0x00006A2A
_0222F594: .word 0x00006DB6
_0222F598: .word 0x000062B6
_0222F59C: .word 0x00006A27
_0222F5A0: .word 0x00006DB3
_0222F5A4: .word 0x000089C8
_0222F5A8: .word 0x00006A28
_0222F5AC: .word 0x00006DB4
	thumb_func_end MOD62_0222F43C

	thumb_func_start MOD62_0222F5B0
MOD62_0222F5B0: ; 0x0222F5B0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0xa0
	add r7, r0, #0
	add r0, #0xdc
	ldr r6, [r0]
	add r0, r7, #0
	add r0, #0xe0
	ldr r5, [r0]
	mov r0, #0xf9
	lsl r0, r0, #2
	add r4, r7, r0
	mov r1, #0
	add r2, sp, #0x6c
	strh r1, [r2]
	strh r1, [r2, #2]
	strh r1, [r2, #4]
	strh r1, [r2, #6]
	mov r0, #0x3c
	str r0, [sp, #0x74]
	mov r0, #2
	str r0, [sp, #0x7c]
	mov r0, #1
	str r1, [sp, #0x9c]
	sub r1, r0, #2
	str r0, [sp, #0x98]
	str r0, [sp, #0x78]
	ldr r0, _0222F6FC ; =0x000062B9
	str r1, [sp, #0x90]
	str r0, [sp, #0x80]
	ldr r0, _0222F700 ; =0x000066B2
	str r1, [sp, #0x94]
	str r0, [sp, #0x84]
	ldr r0, _0222F704 ; =0x00006A29
	add r1, r5, #0
	str r0, [sp, #0x88]
	ldr r0, _0222F708 ; =0x00006DB5
	str r0, [sp, #0x8c]
	add r0, r6, #0
	bl FUN_0200C154
	str r0, [r4, #0x20]
	ldr r0, _0222F70C ; =0x000062BA
	add r1, r5, #0
	str r0, [sp, #0x80]
	ldr r0, _0222F700 ; =0x000066B2
	add r2, sp, #0x6c
	str r0, [sp, #0x84]
	ldr r0, _0222F710 ; =0x00006A2A
	str r0, [sp, #0x88]
	ldr r0, _0222F714 ; =0x00006DB6
	str r0, [sp, #0x8c]
	add r0, r6, #0
	bl FUN_0200C154
	str r0, [r4, #0x24]
	mov r0, #1
	str r0, [sp, #0x98]
	str r0, [sp, #0x78]
	ldr r0, _0222F718 ; =0x000089C8
	add r1, r5, #0
	str r0, [sp, #0x80]
	ldr r0, _0222F700 ; =0x000066B2
	add r2, sp, #0x6c
	str r0, [sp, #0x84]
	ldr r0, _0222F71C ; =0x00006A28
	str r0, [sp, #0x88]
	ldr r0, _0222F720 ; =0x00006DB4
	str r0, [sp, #0x8c]
	add r0, r6, #0
	bl FUN_0200C154
	str r0, [r4, #0x28]
	mov r0, #1
	str r0, [sp, #0x98]
	mov r0, #0
	str r0, [sp, #0x78]
	ldr r0, _0222F724 ; =0x000062B6
	add r1, r5, #0
	str r0, [sp, #0x80]
	ldr r0, _0222F700 ; =0x000066B2
	add r2, sp, #0x6c
	str r0, [sp, #0x84]
	ldr r0, _0222F728 ; =0x00006A27
	str r0, [sp, #0x88]
	ldr r0, _0222F72C ; =0x00006DB3
	str r0, [sp, #0x8c]
	add r0, r6, #0
	bl FUN_0200C154
	str r0, [r4, #0x2c]
	add r0, r6, #0
	add r1, r5, #0
	add r2, sp, #0x6c
	bl FUN_0200C154
	ldr r3, _0222F730 ; =MOD62_022311A8
	str r0, [r4, #0x30]
	add r2, sp, #0x38
	mov r1, #0x1a
_0222F676:
	ldrh r0, [r3]
	add r3, r3, #2
	strh r0, [r2]
	add r2, r2, #2
	sub r1, r1, #1
	bne _0222F676
	ldr r3, _0222F734 ; =MOD62_022311DC
	add r2, sp, #4
	mov r1, #0x1a
_0222F688:
	ldrh r0, [r3]
	add r3, r3, #2
	strh r0, [r2]
	add r2, r2, #2
	sub r1, r1, #1
	bne _0222F688
	mov r0, #8
	str r0, [sp]
	mov r0, #0x1d
	add r4, r7, #0
	lsl r0, r0, #4
	add r7, r7, r0
	add r6, sp, #0x58
	add r4, #0x20
	add r5, sp, #0x24
	add r7, #0x20
_0222F6A8:
	mov r0, #0xf9
	mov r1, #0
	mov r2, #2
	lsl r0, r0, #2
	ldrsh r1, [r6, r1]
	ldrsh r2, [r6, r2]
	ldr r0, [r4, r0]
	bl FUN_0200C714
	mov r0, #0xf9
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200C5A8
	mov r0, #0xf9
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200C61C
	mov r1, #0xf9
	mov r2, #0
	mov r3, #2
	lsl r1, r1, #2
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	ldr r1, [r4, r1]
	add r0, r7, #0
	bl MOD62_0222DCE4
	ldr r0, [sp]
	add r6, r6, #4
	add r0, r0, #1
	add r4, r4, #4
	add r5, r5, #4
	add r7, r7, #4
	str r0, [sp]
	cmp r0, #0xd
	blt _0222F6A8
	add sp, #0xa0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222F6FC: .word 0x000062B9
_0222F700: .word 0x000066B2
_0222F704: .word 0x00006A29
_0222F708: .word 0x00006DB5
_0222F70C: .word 0x000062BA
_0222F710: .word 0x00006A2A
_0222F714: .word 0x00006DB6
_0222F718: .word 0x000089C8
_0222F71C: .word 0x00006A28
_0222F720: .word 0x00006DB4
_0222F724: .word 0x000062B6
_0222F728: .word 0x00006A27
_0222F72C: .word 0x00006DB3
_0222F730: .word MOD62_022311A8
_0222F734: .word MOD62_022311DC
	thumb_func_end MOD62_0222F5B0

	thumb_func_start MOD62_0222F738
MOD62_0222F738: ; 0x0222F738
	push {r3, r4, r5, r6, r7, lr}
	mov r7, #0xf9
	add r5, r0, #0
	add r6, r1, #0
	mov r4, #0
	lsl r7, r7, #2
_0222F744:
	ldr r0, [r5, r7]
	add r1, r6, #0
	bl FUN_0200C644
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xd
	blt _0222F744
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD62_0222F738

	thumb_func_start MOD62_0222F758
MOD62_0222F758: ; 0x0222F758
	bx lr
	.align 2, 0
	thumb_func_end MOD62_0222F758

	thumb_func_start MOD62_0222F75C
MOD62_0222F75C: ; 0x0222F75C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r6, #0xf9
	mov r4, #8
	add r5, #0x20
	lsl r6, r6, #2
_0222F768:
	ldr r0, [r5, r6]
	bl FUN_0200C3DC
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xd
	blt _0222F768
	pop {r4, r5, r6, pc}
	thumb_func_end MOD62_0222F75C

	thumb_func_start MOD62_0222F778
MOD62_0222F778: ; 0x0222F778
	add r1, r0, #0
	mov r0, #0xf1
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r3, _0222F78C ; =FUN_02029C74
	lsl r0, r0, #3
	add r0, r1, r0
	ldr r0, [r0, #8]
	add r1, #0x68
	bx r3
	.align 2, 0
_0222F78C: .word FUN_02029C74
	thumb_func_end MOD62_0222F778

	thumb_func_start MOD62_0222F790
MOD62_0222F790: ; 0x0222F790
	mov r1, #0xf1
	add r2, r0, #0
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	ldr r3, _0222F7A4 ; =FUN_02029C74
	lsl r1, r1, #3
	add r1, r2, r1
	add r0, #0x68
	ldr r1, [r1, #8]
	bx r3
	.align 2, 0
_0222F7A4: .word FUN_02029C74
	thumb_func_end MOD62_0222F790

	thumb_func_start MOD62_0222F7A8
MOD62_0222F7A8: ; 0x0222F7A8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_0222F7AE:
	ldr r0, [r5, #0x64]
	add r1, r4, #0
	bl FUN_02029CF4
	add r1, r5, r4
	add r1, #0x80
	add r4, r4, #1
	strb r0, [r1]
	cmp r4, #0x51
	blt _0222F7AE
	pop {r3, r4, r5, pc}
	thumb_func_end MOD62_0222F7A8

	thumb_func_start MOD62_0222F7C4
MOD62_0222F7C4: ; 0x0222F7C4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_0222F7CA:
	add r2, r5, r4
	add r2, #0x80
	ldrb r2, [r2]
	ldr r0, [r5, #0x64]
	add r1, r4, #0
	bl FUN_02029D40
	add r4, r4, #1
	cmp r4, #0x51
	blt _0222F7CA
	pop {r3, r4, r5, pc}
	thumb_func_end MOD62_0222F7C4

	thumb_func_start MOD62_0222F7E0
MOD62_0222F7E0: ; 0x0222F7E0
	push {r3, lr}
	mov r0, #7
	str r0, [sp]
	ldr r0, _0222F804 ; =0x04000050
	mov r1, #0
	mov r2, #6
	mov r3, #0xb
	bl G2x_SetBlendAlpha_
	mov r0, #8
	str r0, [sp]
	ldr r0, _0222F808 ; =0x04001050
	mov r1, #0
	mov r2, #0xe
	mov r3, #7
	bl G2x_SetBlendAlpha_
	pop {r3, pc}
	.align 2, 0
_0222F804: .word 0x04000050
_0222F808: .word 0x04001050
	thumb_func_end MOD62_0222F7E0

	thumb_func_start MOD62_0222F80C
MOD62_0222F80C: ; 0x0222F80C
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0xf1
	add r5, r0, #0
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	lsl r0, r0, #3
	add r0, r5, r0
	ldr r0, [r0, #4]
	cmp r0, #0xff
	beq _0222F832
	ldr r2, [r5]
	lsl r0, r0, #2
	add r0, r2, r0
	add r1, #0x64
	ldr r0, [r0, #4]
	ldr r1, [r5, r1]
	bl CopyPokemonToPokemon
	pop {r3, r4, r5, r6, r7, pc}
_0222F832:
	ldr r1, [r5]
	mov r6, #0
	ldr r0, [r1]
	cmp r0, #0
	ble _0222F868
	add r4, r6, #0
_0222F83E:
	add r0, r1, r4
	ldr r7, [r0, #4]
	mov r1, #0x4c
	add r0, r7, #0
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222F85C
	ldr r1, _0222F86C ; =0x00000428
	add r0, r7, #0
	ldr r1, [r5, r1]
	bl CopyPokemonToPokemon
	pop {r3, r4, r5, r6, r7, pc}
_0222F85C:
	ldr r1, [r5]
	add r6, r6, #1
	ldr r0, [r1]
	add r4, r4, #4
	cmp r6, r0
	blt _0222F83E
_0222F868:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222F86C: .word 0x00000428
	thumb_func_end MOD62_0222F80C

	thumb_func_start MOD62_0222F870
MOD62_0222F870: ; 0x0222F870
	push {r3, r4, r5, r6, r7, lr}
	mov r7, #0
	add r6, r0, #0
	add r5, r7, #0
	add r4, r7, #0
_0222F87A:
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_02029CC8
	bl FUN_02029CE0
	cmp r0, #0
	beq _0222F88C
	add r5, r5, #1
_0222F88C:
	add r4, r4, #1
	cmp r4, #8
	blt _0222F87A
	cmp r5, #0
	beq _0222F898
	mov r7, #1
_0222F898:
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD62_0222F870

	thumb_func_start MOD62_0222F89C
MOD62_0222F89C: ; 0x0222F89C
	mov r2, #0xc
	mul r2, r1
	add r1, r0, r2
	mov r0, #0x99
	lsl r0, r0, #2
	ldr r2, [r1, r0]
	add r0, r0, #4
	ldr r0, [r1, r0]
	cmp r2, #0xff
	bne _0222F8B8
	cmp r0, #0
	bne _0222F8B8
	mov r0, #0
	bx lr
_0222F8B8:
	cmp r2, #0xff
	bne _0222F8C4
	cmp r0, #1
	bne _0222F8C4
	mov r0, #1
	bx lr
_0222F8C4:
	cmp r2, #0xff
	beq _0222F8D0
	cmp r0, #1
	bne _0222F8D0
	mov r0, #2
	bx lr
_0222F8D0:
	mov r0, #3
	bx lr
	thumb_func_end MOD62_0222F89C

	thumb_func_start MOD62_0222F8D4
MOD62_0222F8D4: ; 0x0222F8D4
	push {r3, r4}
	cmp r2, #0xff
	bne _0222F8E6
	mov r2, #0xf6
	lsl r2, r2, #2
	ldr r4, [r0, r2]
	sub r2, r2, #4
	str r4, [r0, r2]
	b _0222F8EC
_0222F8E6:
	mov r4, #0xf5
	lsl r4, r4, #2
	str r2, [r0, r4]
_0222F8EC:
	mov r2, #0xf3
	lsl r2, r2, #2
	str r1, [r0, r2]
	add r1, r2, #0
	add r1, #0xc
	str r3, [r0, r1]
	mov r1, #0
	add r2, #0x10
	str r1, [r0, r2]
	pop {r3, r4}
	bx lr
	.align 2, 0
	thumb_func_end MOD62_0222F8D4

	thumb_func_start MOD62_0222F904
MOD62_0222F904: ; 0x0222F904
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xfc
	mov r1, #1
	bl FUN_0200CCF8
	add r0, r4, #0
	add r0, #0xfc
	bl FUN_02019570
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02001C5C
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ListMenu_dtor
	add r4, #0xfc
	add r0, r4, #0
	bl FUN_02019178
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD62_0222F904

	thumb_func_start MOD62_0222F93C
MOD62_0222F93C: ; 0x0222F93C
	push {r3, lr}
	mov r1, #1
	mov r2, #0
	mov r3, #3
	bl MOD62_0222F8D4
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD62_0222F93C

	thumb_func_start MOD62_0222F94C
MOD62_0222F94C: ; 0x0222F94C
	push {r4, lr}
	add r4, r0, #0
	bl MOD62_0222D874
	add r0, r4, #0
	bl MOD62_0222DC7C
	add r0, r4, #0
	bl MOD62_0222EC28
	mov r2, #0
	add r0, r4, #0
	mov r1, #2
	add r3, r2, #0
	bl MOD62_0222F8D4
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD62_0222F94C

	thumb_func_start MOD62_0222F970
MOD62_0222F970: ; 0x0222F970
	push {r3, lr}
	mov r1, #3
	mov r2, #0
	add r3, r1, #0
	bl MOD62_0222F8D4
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD62_0222F970

	thumb_func_start MOD62_0222F980
MOD62_0222F980: ; 0x0222F980
	push {r3, lr}
	mov r1, #4
	mov r2, #0
	mov r3, #3
	bl MOD62_0222F8D4
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD62_0222F980

	thumb_func_start MOD62_0222F990
MOD62_0222F990: ; 0x0222F990
	push {r3, r4, r5, lr}
	mov r1, #0xf3
	add r4, r0, #0
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	lsl r2, r1, #2
	ldr r1, _0222F9B0 ; =MOD62_02231220
	ldr r1, [r1, r2]
	blx r1
	add r4, #0xe0
	add r5, r0, #0
	ldr r0, [r4]
	bl FUN_0200BC1C
	add r0, r5, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222F9B0: .word MOD62_02231220
	thumb_func_end MOD62_0222F990

	thumb_func_start MOD62_0222F9B4
MOD62_0222F9B4: ; 0x0222F9B4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222FA3C ; =gMain
	mov r1, #0x10
	ldr r0, [r0, #0x4c]
	tst r1, r0
	beq _0222F9D2
	ldr r0, [r4]
	mov r1, #0xc
	add r0, r0, #1
	str r0, [r4]
	bl _s32_div_f
	str r1, [r4]
	b _0222FA38
_0222F9D2:
	mov r1, #0x20
	tst r1, r0
	beq _0222F9EA
	ldr r0, [r4]
	cmp r0, #0
	ble _0222F9E4
	sub r0, r0, #1
	str r0, [r4]
	b _0222FA38
_0222F9E4:
	mov r0, #0xb
	str r0, [r4]
	b _0222FA38
_0222F9EA:
	mov r1, #0x40
	tst r1, r0
	beq _0222FA0E
	ldr r1, [r4]
	asr r0, r1, #1
	lsr r0, r0, #0x1e
	add r0, r1, r0
	asr r0, r0, #2
	beq _0222FA0A
	sub r0, r1, #4
	mov r1, #0xc
	str r0, [r4]
	bl _s32_div_f
	str r1, [r4]
	b _0222FA38
_0222FA0A:
	mov r0, #0
	pop {r4, pc}
_0222FA0E:
	mov r1, #0x80
	tst r0, r1
	beq _0222FA34
	ldr r1, [r4]
	asr r0, r1, #1
	lsr r0, r0, #0x1e
	add r0, r1, r0
	asr r0, r0, #2
	cmp r0, #2
	beq _0222FA30
	add r0, r1, #4
	mov r1, #0xc
	str r0, [r4]
	bl _s32_div_f
	str r1, [r4]
	b _0222FA38
_0222FA30:
	mov r0, #0
	pop {r4, pc}
_0222FA34:
	mov r0, #0
	pop {r4, pc}
_0222FA38:
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_0222FA3C: .word gMain
	thumb_func_end MOD62_0222F9B4

	thumb_func_start MOD62_0222FA40
MOD62_0222FA40: ; 0x0222FA40
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	mov r4, #0
	str r2, [sp]
	cmp r1, #0
	bne _0222FA50
	mov r4, #1
_0222FA50:
	mov r0, #0xf1
	lsl r0, r0, #2
	lsl r6, r1, #2
	add r7, r5, r0
	add r1, sp, #4
	ldr r0, [r7, r6]
	add r1, #2
	add r2, sp, #4
	bl MOD62_0222E53C
	mov r0, #0xbd
	add r1, r5, r6
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r3, sp, #4
	mov r1, #2
	mov r2, #0
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	bl FUN_0200C714
	ldr r0, [sp]
	cmp r0, #1
	bne _0222FAAE
	mov r0, #0xf1
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, [r7, r6]
	lsl r4, r4, #2
	str r0, [r1, r4]
	ldr r0, [r1, r4]
	add r1, sp, #4
	add r1, #2
	add r2, sp, #4
	bl MOD62_0222E53C
	mov r0, #0xbd
	add r1, r5, r4
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r3, sp, #4
	mov r1, #2
	mov r2, #0
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	bl FUN_0200C714
_0222FAAE:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD62_0222FA40

	thumb_func_start MOD62_0222FAB4
MOD62_0222FAB4: ; 0x0222FAB4
	push {r4, r5, r6, lr}
	sub sp, #0x10
	mov r1, #0xf5
	add r4, r0, #0
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	cmp r1, #6
	bls _0222FAC6
	b _0222FD4C
_0222FAC6:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222FAD2: ; jump table
	.short _0222FAE0 - _0222FAD2 - 2 ; case 0
	.short _0222FBBC - _0222FAD2 - 2 ; case 1
	.short _0222FBCC - _0222FAD2 - 2 ; case 2
	.short _0222FBE0 - _0222FAD2 - 2 ; case 3
	.short _0222FCA2 - _0222FAD2 - 2 ; case 4
	.short _0222FD00 - _0222FAD2 - 2 ; case 5
	.short _0222FD10 - _0222FAD2 - 2 ; case 6
_0222FAE0:
	bl MOD62_0222E560
	add r0, r4, #0
	bl MOD62_0222E5D8
	add r0, r4, #0
	bl MOD62_0222E6D8
	add r0, r4, #0
	bl MOD62_0222F2C8
	add r0, r4, #0
	bl MOD62_0222F36C
	add r0, r4, #0
	bl MOD62_0222F3D4
	add r0, r4, #0
	bl MOD62_0222E7A4
	add r0, r4, #0
	bl MOD62_0222EA6C
	mov r0, #0x15
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r3, #2
	add r1, r4, #0
	str r3, [sp, #8]
	mov r0, #0x28
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0xe4
	ldr r0, [r0]
	add r1, #0xec
	mov r2, #1
	bl MOD62_0222EEE0
	add r0, r4, #0
	bl MOD62_0222D67C
	add r0, r4, #0
	mov r1, #1
	bl MOD62_0222DB10
	add r0, r4, #0
	bl MOD62_0222D654
	add r0, r4, #0
	bl MOD62_0222F43C
	add r0, r4, #0
	bl MOD62_0222F5B0
	add r0, r4, #0
	bl MOD62_0222E888
	add r0, r4, #0
	bl MOD62_0222E8F8
	add r0, r4, #0
	bl MOD62_0222F778
	add r0, r4, #0
	bl MOD62_0222F7A8
	ldr r1, _0222FD60 ; =0x00000418
	add r0, r4, #0
	ldr r1, [r4, r1]
	bl MOD62_0222DEF8
	add r0, r4, #0
	bl MOD62_0222DF5C
	add r0, r4, #0
	bl MOD62_0222E004
	add r0, r4, #0
	mov r1, #0
	bl MOD62_0222F738
	add r0, r4, #0
	mov r1, #0
	bl MOD62_0222E9B4
	add r0, r4, #0
	bl MOD62_0222DDB4
	add r0, r4, #0
	mov r1, #0
	bl MOD62_0222DDE0
	add r0, r4, #0
	add r0, #0xec
	mov r1, #7
	bl MOD62_0222EE78
	bl MOD62_0222F270
	add r0, r4, #0
	mov r1, #0
	bl MOD62_022300DC
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _0222FD4C
_0222FBBC:
	bl MOD62_0222F288
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _0222FD4C
_0222FBCC:
	bl FUN_0200E308
	cmp r0, #1
	beq _0222FBD6
	b _0222FD4C
_0222FBD6:
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
_0222FBE0:
	bl FUN_02020AA4
	cmp r0, #1
	bne _0222FBF0
	add r0, r4, #0
	bl MOD62_0222F93C
	b _0222FD4C
_0222FBF0:
	mov r0, #0xf1
	lsl r0, r0, #2
	ldr r6, [r4, r0]
	add r0, r4, r0
	bl MOD62_0222F9B4
	mov r1, #0xf1
	lsl r1, r1, #2
	ldr r5, [r4, r1]
	cmp r0, #1
	str r6, [r4, r1]
	bne _0222FC4C
	add r0, r4, #0
	bl MOD62_0222D874
	add r0, r4, #0
	bl MOD62_0222DC7C
	add r0, r4, #0
	bl MOD62_0222EC28
	mov r0, #0xf1
	lsl r0, r0, #2
	str r5, [r4, r0]
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	bl MOD62_0222FA40
	add r0, r4, #0
	bl MOD62_0222DAEC
	add r0, r4, #0
	bl MOD62_0222D67C
	add r0, r4, #0
	mov r1, #1
	bl MOD62_0222DB10
	add r0, r4, #0
	bl MOD62_0222D654
	ldr r0, _0222FD64 ; =0x000005DC
	bl FUN_020054C8
	b _0222FD4C
_0222FC4C:
	ldr r0, _0222FD68 ; =gMain
	ldr r2, [r0, #0x48]
	mov r0, #1
	tst r0, r2
	beq _0222FC8E
	add r0, r1, #0
	add r0, #0x10
	ldr r0, [r4, r0]
	add r1, #0x10
	add r0, r0, #1
	str r0, [r4, r1]
	add r0, r4, #0
	add r0, #0xec
	mov r1, #8
	bl MOD62_0222EE78
	mov r0, #0xf1
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r4, #0
	str r0, [sp]
	add r0, r4, #0
	add r0, #0xe4
	ldr r0, [r0]
	add r1, #0xfc
	mov r2, #1
	add r3, r4, #0
	bl MOD62_0222E3C4
	ldr r0, _0222FD64 ; =0x000005DC
	bl FUN_020054C8
	b _0222FD4C
_0222FC8E:
	mov r0, #2
	tst r0, r2
	beq _0222FD4C
	mov r0, #5
	add r1, #0x10
	str r0, [r4, r1]
	ldr r0, _0222FD6C ; =0x000005DD
	bl FUN_020054C8
	b _0222FD4C
_0222FCA2:
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_02001C78
	add r1, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r1, r0
	beq _0222FCBE
	add r0, r0, #1
	cmp r1, r0
	beq _0222FD4C
	b _0222FCD8
_0222FCBE:
	add r0, r4, #0
	bl MOD62_0222F904
	add r0, r4, #0
	add r0, #0xec
	mov r1, #7
	bl MOD62_0222EE78
	mov r0, #0xf5
	mov r1, #3
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _0222FD4C
_0222FCD8:
	cmp r1, #0
	beq _0222FD4C
	add r0, r4, #0
	blx r1
	cmp r0, #1
	beq _0222FCEC
	add r0, r4, #0
	bl MOD62_0222F904
	b _0222FD4C
_0222FCEC:
	add r0, r4, #0
	add r0, #0xec
	mov r1, #7
	bl MOD62_0222EE78
	mov r0, #0xf5
	mov r1, #3
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _0222FD4C
_0222FD00:
	bl MOD62_0222F2A8
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _0222FD4C
_0222FD10:
	bl FUN_0200E308
	cmp r0, #1
	bne _0222FD4C
	add r0, r4, #0
	add r0, #0xec
	bl FUN_02019178
	add r0, r4, #0
	bl MOD62_0222ED04
	add r0, r4, #0
	bl MOD62_0222E77C
	add r0, r4, #0
	bl MOD62_0222F75C
	add r0, r4, #0
	bl MOD62_0222E9D4
	add r0, r4, #0
	bl MOD62_0222E0C8
	ldr r0, [r4]
	mov r1, #0
	bl FUN_02085D9C
	add sp, #0x10
	mov r0, #0
	pop {r4, r5, r6, pc}
_0222FD4C:
	add r0, r4, #0
	bl MOD62_0222E754
	add r0, r4, #0
	bl MOD62_0222ECD4
	mov r0, #1
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_0222FD60: .word 0x00000418
_0222FD64: .word 0x000005DC
_0222FD68: .word gMain
_0222FD6C: .word 0x000005DD
	thumb_func_end MOD62_0222FAB4

	thumb_func_start MOD62_0222FD70
MOD62_0222FD70: ; 0x0222FD70
	push {r3, lr}
	cmp r1, #3
	bhi _0222FDA2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222FD82: ; jump table
	.short _0222FD8A - _0222FD82 - 2 ; case 0
	.short _0222FD9A - _0222FD82 - 2 ; case 1
	.short _0222FD92 - _0222FD82 - 2 ; case 2
	.short _0222FD9A - _0222FD82 - 2 ; case 3
_0222FD8A:
	mov r1, #1
	bl FUN_0200C61C
	pop {r3, pc}
_0222FD92:
	mov r1, #2
	bl FUN_0200C61C
	pop {r3, pc}
_0222FD9A:
	mov r1, #0
	bl FUN_0200C61C
	pop {r3, pc}
_0222FDA2:
	bl ErrorHandling
	pop {r3, pc}
	thumb_func_end MOD62_0222FD70

	thumb_func_start MOD62_0222FDA8
MOD62_0222FDA8: ; 0x0222FDA8
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	cmp r5, #0
	beq _0222FDCC
	add r1, sp, #4
	add r2, sp, #0
	bl FUN_020119A4
	ldr r1, [sp, #4]
	ldr r2, [sp]
	add r0, r5, #0
	add r1, r1, r4
	add r2, r2, r6
	bl FUN_020118C4
_0222FDCC:
	add sp, #8
	pop {r4, r5, r6, pc}
	thumb_func_end MOD62_0222FDA8

	thumb_func_start MOD62_0222FDD0
MOD62_0222FDD0: ; 0x0222FDD0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #3
	beq _0222FDE2
	cmp r0, #6
	beq _0222FDFC
	b _0222FE1C
_0222FDE2:
	mov r1, #0
	ldr r0, [r4, #8]
	sub r2, r1, #1
	bl MOD62_0222FDA8
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_0200C61C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_0222FDFC:
	ldr r0, [r4, #8]
	mov r1, #0
	mov r2, #2
	bl MOD62_0222FDA8
	ldr r0, [r4, #4]
	mov r1, #0
	bl FUN_0200C61C
	add r0, r5, #0
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
_0222FE1C:
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD62_0222FDD0

	thumb_func_start MOD62_0222FE24
MOD62_0222FE24: ; 0x0222FE24
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #0x35
	mov r1, #0xc
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #1
	str r0, [r4]
	mov r1, #0
	str r6, [r4, #4]
	add r0, r5, #0
	sub r2, r1, #1
	str r5, [r4, #8]
	bl MOD62_0222FDA8
	mov r2, #0xfa
	ldr r0, _0222FE54 ; =MOD62_0222FDD0
	add r1, r4, #0
	lsl r2, r2, #2
	bl FUN_0200CA44
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222FE54: .word MOD62_0222FDD0
	thumb_func_end MOD62_0222FE24

	thumb_func_start MOD62_0222FE58
MOD62_0222FE58: ; 0x0222FE58
	push {r4, r5, r6, lr}
	add r4, r2, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0xd8
	ldr r0, [r0]
	add r6, r1, #0
	cmp r0, #0
	bne _0222FE6C
	b _022300A8
_0222FE6C:
	cmp r5, #0x14
	bls _0222FE72
	b _022300A4
_0222FE72:
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222FE7E: ; jump table
	.short _0222FFE6 - _0222FE7E - 2 ; case 0
	.short _0222FFE6 - _0222FE7E - 2 ; case 1
	.short _0222FFE6 - _0222FE7E - 2 ; case 2
	.short _0222FFE6 - _0222FE7E - 2 ; case 3
	.short _0222FFE6 - _0222FE7E - 2 ; case 4
	.short _0222FFE6 - _0222FE7E - 2 ; case 5
	.short _0222FFE6 - _0222FE7E - 2 ; case 6
	.short _0222FFE6 - _0222FE7E - 2 ; case 7
	.short _0222FEA8 - _0222FE7E - 2 ; case 8
	.short _0222FEF2 - _0222FE7E - 2 ; case 9
	.short _0222FF40 - _0222FE7E - 2 ; case 10
	.short _0222FF6E - _0222FE7E - 2 ; case 11
	.short _0222FFAC - _0222FE7E - 2 ; case 12
	.short _02230074 - _0222FE7E - 2 ; case 13
	.short _02230074 - _0222FE7E - 2 ; case 14
	.short _02230074 - _0222FE7E - 2 ; case 15
	.short _02230074 - _0222FE7E - 2 ; case 16
	.short _02230074 - _0222FE7E - 2 ; case 17
	.short _02230074 - _0222FE7E - 2 ; case 18
	.short _02230074 - _0222FE7E - 2 ; case 19
	.short _02230074 - _0222FE7E - 2 ; case 20
_0222FEA8:
	cmp r6, #0
	bne _0222FEE6
	ldr r1, _022300AC ; =0x00000418
	ldr r0, [r4, r1]
	cmp r0, #0
	ble _0222FEB6
	b _0222FEBA
_0222FEB6:
	add r0, r1, #4
	ldr r0, [r4, r0]
_0222FEBA:
	sub r0, r0, #1
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD62_0222E0C8
	ldr r1, _022300AC ; =0x00000418
	add r0, r4, #0
	ldr r1, [r4, r1]
	bl MOD62_0222DEF8
	add r0, r4, #0
	bl MOD62_0222DF5C
	add r0, r4, #0
	bl MOD62_0222E004
	add r0, r4, #0
	bl MOD62_0222F0D4
	ldr r0, _022300B0 ; =0x000006C5
	bl FUN_020054C8
_0222FEE6:
	ldr r0, _022300B4 ; =0x00000404
	add r1, r6, #0
	ldr r0, [r4, r0]
	bl MOD62_0222FD70
	pop {r4, r5, r6, pc}
_0222FEF2:
	cmp r6, #0
	bne _0222FF34
	ldr r1, _022300AC ; =0x00000418
	ldr r0, [r4, r1]
	add r0, r0, #1
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	bl _s32_div_f
	ldr r0, _022300AC ; =0x00000418
	str r1, [r4, r0]
	add r0, r4, #0
	bl MOD62_0222E0C8
	ldr r1, _022300AC ; =0x00000418
	add r0, r4, #0
	ldr r1, [r4, r1]
	bl MOD62_0222DEF8
	add r0, r4, #0
	bl MOD62_0222DF5C
	add r0, r4, #0
	bl MOD62_0222E004
	add r0, r4, #0
	bl MOD62_0222F0D4
	ldr r0, _022300B0 ; =0x000006C5
	bl FUN_020054C8
_0222FF34:
	ldr r0, _022300B8 ; =0x00000408
	add r1, r6, #0
	ldr r0, [r4, r0]
	bl MOD62_0222FD70
	pop {r4, r5, r6, pc}
_0222FF40:
	cmp r6, #0
	bne _0222FF62
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #5
	beq _0222FF58
	mov r1, #5
	str r1, [r4, r0]
	ldr r0, _022300BC ; =0x000005DD
	bl FUN_020054C8
_0222FF58:
	ldr r0, _022300C0 ; =0x0000040C
	mov r1, #0
	ldr r0, [r4, r0]
	bl MOD62_0222FE24
_0222FF62:
	ldr r0, _022300C0 ; =0x0000040C
	add r1, r6, #0
	ldr r0, [r4, r0]
	bl MOD62_0222FD70
	pop {r4, r5, r6, pc}
_0222FF6E:
	cmp r6, #0
	bne _0222FF9E
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #6
	beq _0222FF8E
	mov r1, #6
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #0
	bl MOD62_022300DC
	ldr r0, _022300C4 ; =0x000005E2
	bl FUN_020054C8
_0222FF8E:
	mov r0, #0x41
	mov r1, #0x8e
	lsl r0, r0, #4
	lsl r1, r1, #2
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	bl MOD62_0222FE24
_0222FF9E:
	mov r0, #0x41
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, r6, #0
	bl MOD62_0222FD70
	pop {r4, r5, r6, pc}
_0222FFAC:
	cmp r6, #0
	bne _0222FFDA
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #7
	beq _0222FFCC
	mov r1, #7
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #0
	bl MOD62_022300DC
	ldr r0, _022300BC ; =0x000005DD
	bl FUN_020054C8
_0222FFCC:
	ldr r0, _022300C8 ; =0x00000414
	mov r1, #0x8f
	lsl r1, r1, #2
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	bl MOD62_0222FE24
_0222FFDA:
	ldr r0, _022300C8 ; =0x00000414
	add r1, r6, #0
	ldr r0, [r4, r0]
	bl MOD62_0222FD70
	pop {r4, r5, r6, pc}
_0222FFE6:
	cmp r6, #0
	bne _022300A8
	add r0, r4, #0
	bl MOD62_0222D76C
	cmp r0, #0
	bne _02230006
	ldr r0, _022300CC ; =0x000005F2
	bl FUN_020054C8
	add r4, #0xec
	add r0, r4, #0
	mov r1, #0xf
	bl MOD62_0222EE78
	pop {r4, r5, r6, pc}
_02230006:
	mov r0, #0x42
	lsl r0, r0, #4
	add r6, r4, r0
	ldrb r1, [r6, r5]
	cmp r1, #0
	beq _0223005C
	ldr r0, [r4, #0x64]
	sub r1, r1, #1
	bl FUN_02029CF4
	cmp r0, #0
	beq _0223005C
	lsl r1, r5, #0x18
	add r0, r4, #0
	lsr r1, r1, #0x18
	bl MOD62_0222D6EC
	add r1, r4, #0
	add r1, #0xd4
	str r0, [r1]
	ldrb r0, [r6, r5]
	bl FUN_02085FD0
	add r1, r0, #0
	add r0, r4, #0
	add r0, #0xec
	bl MOD62_0222F208
	ldr r0, [r4]
	mov r2, #0
	ldrb r1, [r6, r5]
	ldr r0, [r0, #0x20]
	mvn r2, r2
	bl FUN_02029D44
	add r0, r4, #0
	add r1, r5, #0
	bl MOD62_0222F168
	ldr r0, _022300D0 ; =0x000005EB
	bl FUN_020054C8
	pop {r4, r5, r6, pc}
_0223005C:
	ldrb r0, [r6, r5]
	cmp r0, #0
	beq _022300A8
	ldr r0, _022300CC ; =0x000005F2
	bl FUN_020054C8
	add r4, #0xec
	add r0, r4, #0
	mov r1, #0x10
	bl MOD62_0222EE78
	pop {r4, r5, r6, pc}
_02230074:
	cmp r6, #0
	bne _022300A8
	sub r5, #0xd
	lsl r2, r5, #0x18
	add r0, r4, #0
	lsr r2, r2, #0x18
	bl MOD62_0222DA38
	lsl r0, r5, #4
	add r1, r4, r0
	mov r0, #0xca
	lsl r0, r0, #2
	ldrb r0, [r1, r0]
	bl FUN_02085FD0
	add r4, #0xec
	add r1, r0, #0
	add r0, r4, #0
	bl MOD62_0222F208
	ldr r0, _022300D0 ; =0x000005EB
	bl FUN_020054C8
	pop {r4, r5, r6, pc}
_022300A4:
	bl ErrorHandling
_022300A8:
	pop {r4, r5, r6, pc}
	nop
_022300AC: .word 0x00000418
_022300B0: .word 0x000006C5
_022300B4: .word 0x00000404
_022300B8: .word 0x00000408
_022300BC: .word 0x000005DD
_022300C0: .word 0x0000040C
_022300C4: .word 0x000005E2
_022300C8: .word 0x00000414
_022300CC: .word 0x000005F2
_022300D0: .word 0x000005EB
	thumb_func_end MOD62_0222FE58

	thumb_func_start MOD62_022300D4
MOD62_022300D4: ; 0x022300D4
	mov r1, #0x96
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr
	thumb_func_end MOD62_022300D4

	thumb_func_start MOD62_022300DC
MOD62_022300DC: ; 0x022300DC
	add r0, #0xd8
	str r1, [r0]
	bx lr
	.align 2, 0
	thumb_func_end MOD62_022300DC

	thumb_func_start MOD62_022300E4
MOD62_022300E4: ; 0x022300E4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r0, [sp, #4]
	add r1, sp, #0x10
	mov r0, #0
	strb r0, [r1]
	strb r0, [r1, #1]
	strb r0, [r1, #2]
	mov r7, #0x1d
	lsl r7, r7, #4
	strb r0, [r1, #3]
	ldr r1, _022301A0 ; =MOD62_02231260
	ldr r2, [sp, #4]
	add r3, r7, #1
	add r4, r7, #2
	add r5, r7, #3
_02230104:
	ldrb r6, [r1]
	add r0, r0, #1
	strb r6, [r2, r7]
	ldrb r6, [r1, #1]
	strb r6, [r2, r3]
	ldrb r6, [r1, #2]
	strb r6, [r2, r4]
	ldrb r6, [r1, #3]
	add r1, r1, #4
	strb r6, [r2, r5]
	add r2, r2, #4
	cmp r0, #0xd
	blt _02230104
	cmp r0, #0x15
	bge _0223017E
	mov r3, #0x1d
	ldr r2, [sp, #4]
	lsl r3, r3, #4
	add r2, r2, r3
	lsl r4, r0, #2
	ldr r1, [sp, #4]
	ldr r3, [sp, #4]
	add r1, r1, r4
	add r2, r2, r4
	lsl r4, r0, #4
	add r5, sp, #0xc
	add r3, r3, r4
	ldrb r4, [r5, #4]
	strb r4, [r5]
	ldrb r4, [r5, #5]
	strb r4, [r5, #1]
	ldrb r4, [r5, #6]
	strb r4, [r5, #2]
	ldrb r4, [r5, #7]
	strb r4, [r5, #3]
	ldrb r4, [r5, #2]
	ldrb r6, [r5]
	ldrb r7, [r5, #1]
	str r4, [sp, #8]
	ldrb r4, [r5, #3]
	mov ip, r4
_02230156:
	mov r4, #0x1d
	lsl r4, r4, #4
	strb r6, [r1, r4]
	add r4, r4, #1
	strb r7, [r1, r4]
	ldr r5, _022301A4 ; =0x000001D2
	ldr r4, [sp, #8]
	add r0, r0, #1
	strb r4, [r1, r5]
	add r5, r5, #1
	mov r4, ip
	strb r4, [r1, r5]
	mov r4, #0x26
	lsl r4, r4, #4
	str r2, [r3, r4]
	add r1, r1, #4
	add r2, r2, #4
	add r3, #0x10
	cmp r0, #0x15
	blt _02230156
_0223017E:
	mov r0, #0x35
	str r0, [sp]
	mov r1, #0x1d
	ldr r0, [sp, #4]
	lsl r1, r1, #4
	add r0, r0, r1
	ldr r2, _022301A8 ; =MOD62_0222FE58
	ldr r3, [sp, #4]
	mov r1, #0x15
	bl FUN_020220C4
	mov r2, #0x73
	ldr r1, [sp, #4]
	lsl r2, r2, #2
	str r0, [r1, r2]
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022301A0: .word MOD62_02231260
_022301A4: .word 0x000001D2
_022301A8: .word MOD62_0222FE58
	thumb_func_end MOD62_022300E4

	thumb_func_start MOD62_022301AC
MOD62_022301AC: ; 0x022301AC
	push {r3, r4, r5, r6, lr}
	sub sp, #0x34
	ldr r1, _02230214 ; =0x00000428
	add r5, r0, #0
	ldr r1, [r5, r1]
	add r0, sp, #0x24
	mov r2, #2
	bl FUN_02068B68
	ldr r0, _02230214 ; =0x00000428
	mov r1, #5
	ldr r0, [r5, r0]
	mov r2, #0
	bl GetMonData
	add r4, r0, #0
	ldr r0, _02230214 ; =0x00000428
	mov r1, #2
	ldr r0, [r5, r0]
	bl FUN_02068E14
	add r6, r0, #0
	mov r0, #0x6b
	lsl r0, r0, #2
	lsl r1, r4, #0x10
	str r6, [r5, r0]
	add r0, sp, #0x10
	lsr r1, r1, #0x10
	bl FUN_02069010
	ldr r0, _02230218 ; =0xFFFFFD80
	add r6, #0x30
	str r0, [sp]
	mov r1, #0
	str r1, [sp, #4]
	add r0, sp, #0x10
	str r0, [sp, #8]
	mov r0, #0x69
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, sp, #0x24
	mov r2, #0xc0
	add r3, r6, #0
	bl FUN_020073A0
	mov r1, #0x6a
	lsl r1, r1, #2
	str r0, [r5, r1]
	add sp, #0x34
	pop {r3, r4, r5, r6, pc}
	nop
_02230214: .word 0x00000428
_02230218: .word 0xFFFFFD80
	thumb_func_end MOD62_022301AC

	thumb_func_start MOD62_0223021C
MOD62_0223021C: ; 0x0223021C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, _02230268 ; =0x00000428
	mov r1, #5
	ldr r0, [r5, r0]
	mov r2, #0
	bl GetMonData
	add r4, r0, #0
	ldr r0, _02230268 ; =0x00000428
	ldr r0, [r5, r0]
	bl GetMonNature
	add r6, r0, #0
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_02007314
	mov r1, #0x97
	lsl r2, r4, #0x10
	str r6, [sp]
	mov r0, #0
	str r0, [sp, #4]
	lsl r1, r1, #2
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	sub r1, #0xb4
	ldr r1, [r5, r1]
	lsr r2, r2, #0x10
	mov r3, #2
	bl FUN_02069038
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_02230268: .word 0x00000428
	thumb_func_end MOD62_0223021C

	thumb_func_start MOD62_0223026C
MOD62_0223026C: ; 0x0223026C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xc
	mov r2, #0
	bl FUN_02007558
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xd
	mov r2, #0
	bl FUN_02007558
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD62_0223026C

	thumb_func_start MOD62_02230290
MOD62_02230290: ; 0x02230290
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xc
	bl FUN_0200782C
	mov r1, #1
	lsl r1, r1, #8
	cmp r0, r1
	bne _022302AC
	mov r0, #0
	pop {r4, pc}
_022302AC:
	add r1, #0xa8
	ldr r0, [r4, r1]
	mov r1, #0xc
	bl FUN_0200782C
	mov r2, #1
	lsl r2, r2, #8
	cmp r0, r2
	blt _022302DE
	add r0, r2, #0
	add r0, #0xa8
	ldr r0, [r4, r0]
	mov r1, #0xc
	bl FUN_02007558
	mov r0, #0x6a
	lsl r0, r0, #2
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r4, r0]
	add r2, #0xf3
	bl FUN_02007558
	mov r0, #0
	pop {r4, pc}
_022302DE:
	add r2, #0xa8
	ldr r0, [r4, r2]
	mov r1, #0xc
	mov r2, #0x20
	bl FUN_020079E0
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xd
	mov r2, #0x20
	bl FUN_020079E0
	mov r1, #0x6a
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	bl FUN_02007F34
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD62_02230290

	thumb_func_start MOD62_0223030C
MOD62_0223030C: ; 0x0223030C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xc
	bl FUN_0200782C
	cmp r0, #0
	bne _02230324
	mov r0, #0
	pop {r4, pc}
_02230324:
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xc
	bl FUN_0200782C
	cmp r0, #0
	bgt _02230354
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xc
	mov r2, #0
	bl FUN_02007558
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xd
	mov r2, #0
	bl FUN_02007558
	mov r0, #0
	pop {r4, pc}
_02230354:
	mov r0, #0x6a
	lsl r0, r0, #2
	mov r1, #0xc
	add r2, r1, #0
	ldr r0, [r4, r0]
	sub r2, #0x2c
	bl FUN_020079E0
	mov r0, #0x6a
	lsl r0, r0, #2
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r4, r0]
	sub r2, #0x2d
	bl FUN_020079E0
	mov r1, #0x6a
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	bl FUN_02007F34
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD62_0223030C

	thumb_func_start MOD62_02230388
MOD62_02230388: ; 0x02230388
	add r2, r1, #0
	mov r1, #0x6a
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	ldr r3, _02230398 ; =FUN_02007558
	mov r1, #6
	bx r3
	nop
_02230398: .word FUN_02007558
	thumb_func_end MOD62_02230388

	thumb_func_start MOD62_0223039C
MOD62_0223039C: ; 0x0223039C
	mov r1, #0x6a
	lsl r1, r1, #2
	ldr r3, _022303A8 ; =FUN_02007534
	ldr r0, [r0, r1]
	bx r3
	nop
_022303A8: .word FUN_02007534
	thumb_func_end MOD62_0223039C

	thumb_func_start MOD62_022303AC
MOD62_022303AC: ; 0x022303AC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xa4
	mov r1, #0xf5
	add r4, r0, #0
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	cmp r2, #0xa
	bhi _0223042C
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_022303C8: ; jump table
	.short _022303DE - _022303C8 - 2 ; case 0
	.short _02230424 - _022303C8 - 2 ; case 1
	.short _0223049A - _022303C8 - 2 ; case 2
	.short _022304D2 - _022303C8 - 2 ; case 3
	.short _02230BDA - _022303C8 - 2 ; case 4
	.short _022304F2 - _022303C8 - 2 ; case 5
	.short _02230846 - _022303C8 - 2 ; case 6
	.short _022308B2 - _022303C8 - 2 ; case 7
	.short _02230AD4 - _022303C8 - 2 ; case 8
	.short _02230B00 - _022303C8 - 2 ; case 9
	.short _02230B96 - _022303C8 - 2 ; case 10
_022303DE:
	mov r1, #0
	bl MOD62_022300DC
	add r0, r4, #0
	ldr r1, _0223071C ; =0x0000FFFF
	add r0, #0xec
	bl MOD62_0222EE78
	add r0, r4, #0
	bl MOD62_0222EFA0
	add r0, r4, #0
	bl MOD62_0222F0D4
	add r0, r4, #0
	mov r1, #1
	mov r2, #4
	bl MOD62_0222E180
	add r0, r4, #0
	bl MOD62_0222F778
	add r0, r4, #0
	bl MOD62_0222F7A8
	mov r0, #0x26
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
_02230424:
	bl MOD62_022300D4
	cmp r0, #1
	bne _0223042E
_0223042C:
	b _02230BDA
_0223042E:
	mov r3, #0
	str r3, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r4, #0
	str r3, [sp, #8]
	add r0, #0xe8
	ldr r0, [r0]
	mov r1, #1
	mov r2, #3
	bl FUN_02003210
	mov r3, #0
	str r3, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r4, #0
	str r3, [sp, #8]
	add r0, #0xe8
	ldr r0, [r0]
	ldr r2, _0223071C ; =0x0000FFFF
	mov r1, #4
	bl FUN_02003210
	mov r0, #0x10
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #4
	mov r1, #1
	bl FUN_0201E74C
	mov r0, #7
	mov r1, #1
	bl FUN_020178BC
	add r0, r4, #0
	mov r1, #1
	bl MOD62_0222F738
	add r0, r4, #0
	mov r1, #1
	bl MOD62_0222E9B4
	add r0, r4, #0
	mov r1, #1
	bl MOD62_0222DDE0
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
_0223049A:
	add r0, #0xe8
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	bne _02230598
	mov r0, #3
	mov r1, #1
	bl FUN_020178BC
	mov r0, #0x10
	str r0, [sp]
	mov r3, #0
	str r3, [sp, #4]
	add r0, r4, #0
	str r3, [sp, #8]
	add r0, #0xe8
	ldr r0, [r0]
	mov r1, #1
	mov r2, #2
	bl FUN_02003210
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
_022304D2:
	add r0, #0xe8
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	bne _02230598
	add r0, r4, #0
	mov r1, #1
	bl MOD62_022300DC
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
_022304F2:
	add r2, r1, #0
	add r2, #8
	ldr r2, [r4, r2]
	cmp r2, #7
	bls _022304FE
	b _0223080C
_022304FE:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0223050A: ; jump table
	.short _0223051A - _0223050A - 2 ; case 0
	.short _0223058C - _0223050A - 2 ; case 1
	.short _022305E2 - _0223050A - 2 ; case 2
	.short _02230646 - _0223050A - 2 ; case 3
	.short _02230692 - _0223050A - 2 ; case 4
	.short _022306D6 - _0223050A - 2 ; case 5
	.short _0223072C - _0223050A - 2 ; case 6
	.short _022307A0 - _0223050A - 2 ; case 7
_0223051A:
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r3, #0
	str r3, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	add r0, r4, #0
	str r3, [sp, #8]
	add r0, #0xe8
	ldr r0, [r0]
	ldr r2, _02230720 ; =0x0000080B
	mov r1, #2
	bl FUN_02003210
	mov r3, #0
	str r3, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	add r0, r4, #0
	str r3, [sp, #8]
	add r0, #0xe8
	ldr r0, [r0]
	ldr r2, _0223071C ; =0x0000FFFF
	mov r1, #8
	bl FUN_02003210
	add r0, r4, #0
	mov r1, #0
	bl MOD62_022300DC
	mov r0, #0x3e
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	add r0, r4, #0
	bl MOD62_0222F80C
	add r0, r4, #0
	bl MOD62_022301AC
	add r0, r4, #0
	mov r1, #1
	bl MOD62_02230388
	add r0, r4, #0
	add r0, #0xec
	mov r1, #0xd
	bl MOD62_0222EE78
	mov r0, #0xf7
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
_0223058C:
	add r0, #0xe8
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	beq _0223059A
_02230598:
	b _02230BDA
_0223059A:
	mov r0, #0x35
	str r0, [sp, #0x80]
	mov r1, #1
	mov r2, #0
	mov r0, #0xff
	str r0, [sp, #0x88]
	add r0, r4, #0
	str r1, [sp, #0x7c]
	str r1, [sp, #0x94]
	str r2, [sp, #0x84]
	str r2, [sp, #0x90]
	add r0, #0xdc
	ldr r0, [r0]
	mov r1, #0x9a
	str r0, [sp, #0x98]
	add r0, r4, #0
	add r0, #0xe8
	ldr r0, [r0]
	str r0, [sp, #0x9c]
	ldr r0, _02230724 ; =0x00000428
	ldr r0, [r4, r0]
	bl GetMonData
	str r0, [sp, #0x8c]
	add r0, sp, #0x7c
	bl MOD08_02229918
	mov r1, #0x8b
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0xf7
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
_022305E2:
	add r2, sp, #0x58
	mov r0, #0
	str r0, [r2]
	str r0, [r2, #4]
	str r0, [r2, #8]
	mov r0, #1
	str r0, [sp, #0x58]
	add r0, r1, #0
	add r0, #0x54
	ldr r0, [r4, r0]
	sub r1, #0x10
	str r0, [sp, #0x60]
	ldr r0, [r4, r1]
	add r1, r4, #0
	add r0, r0, #1
	str r0, [sp, #0x18]
	add r0, sp, #0x64
	bl MOD62_0222DCBC
	ldr r0, _02230724 ; =0x00000428
	mov r1, #0xa1
	ldr r0, [r4, r0]
	add r2, sp, #0x18
	bl SetMonData
	ldr r0, _02230724 ; =0x00000428
	mov r1, #0xaa
	ldr r0, [r4, r0]
	add r2, sp, #0x64
	bl SetMonData
	mov r0, #0x35
	add r1, sp, #0x58
	bl MOD08_02228218
	mov r1, #0x8a
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	bl MOD08_02228524
	mov r0, #0xf7
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	mov r1, #0
	add r0, r0, #4
	str r1, [r4, r0]
	b _02230BDA
_02230646:
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD08_02228570
	cmp r0, #1
	bne _02230702
	mov r0, #0x8b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD08_02229A00
	cmp r0, #1
	bne _02230702
	add r0, r4, #0
	bl MOD62_02230290
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD08_022285A4
	add r0, r4, #0
	mov r1, #0
	bl MOD62_02230388
	add r0, r4, #0
	bl MOD62_0223026C
	ldr r0, _02230728 ; =0x000006C6
	bl FUN_020054C8
	mov r0, #0xf7
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
_02230692:
	bl MOD62_02230290
	add r5, r0, #0
	mov r0, #0x8b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD08_022299E8
	cmp r0, #0
	bne _02230702
	cmp r5, #0
	bne _02230702
	mov r0, #0x8b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD08_02229A2C
	mov r0, #0x10
	mov r1, #0
	bl FUN_0201E6E4
	add r0, r4, #0
	bl MOD62_0223021C
	mov r0, #0x3e
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	sub r1, r0, #4
	ldr r1, [r4, r1]
	sub r0, r0, #4
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
_022306D6:
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD08_022285B4
	cmp r0, #0
	bne _02230702
	mov r0, #0x97
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02014D7C
	cmp r0, #1
	bne _02230702
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02007390
	cmp r0, #0
	beq _02230704
_02230702:
	b _02230BDA
_02230704:
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD08_02228618
	mov r0, #0xf7
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
	nop
_0223071C: .word 0x0000FFFF
_02230720: .word 0x0000080B
_02230724: .word 0x00000428
_02230728: .word 0x000006C6
_0223072C:
	add r0, r1, #0
	add r0, #0xc
	ldr r0, [r4, r0]
	add r2, r0, #1
	add r0, r1, #0
	add r0, #0xc
	str r2, [r4, r0]
	add r0, r1, #0
	add r0, #0xc
	ldr r0, [r4, r0]
	cmp r0, #0x1e
	blt _0223081A
	add r0, r1, #0
	mov r2, #0
	add r0, #0xc
	str r2, [r4, r0]
	mov r0, #0x35
	mov r3, #1
	str r0, [sp, #0x34]
	mov r0, #5
	str r0, [sp, #0x38]
	mov r0, #0xff
	str r0, [sp, #0x3c]
	add r0, r4, #0
	str r3, [sp, #0x30]
	str r2, [sp, #0x44]
	str r3, [sp, #0x48]
	add r0, #0xdc
	ldr r0, [r0]
	add r1, #0x54
	str r0, [sp, #0x4c]
	add r0, r4, #0
	add r0, #0xe8
	ldr r0, [r0]
	str r0, [sp, #0x50]
	ldr r0, [r4, r1]
	mov r1, #0x9a
	bl GetMonData
	str r0, [sp, #0x40]
	add r0, sp, #0x30
	bl MOD08_02229918
	mov r1, #0x8b
	lsl r1, r1, #2
	str r0, [r4, r1]
	bl MOD62_0222F7E0
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0xf7
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
_022307A0:
	bl MOD62_0223030C
	add r5, r0, #0
	mov r0, #0x8b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD08_022299E8
	cmp r0, #0
	bne _0223081A
	cmp r5, #0
	bne _0223081A
	mov r0, #0xa
	str r0, [sp]
	mov r3, #0
	str r3, [sp, #4]
	add r0, r4, #0
	str r3, [sp, #8]
	add r0, #0xe8
	ldr r0, [r0]
	ldr r2, _02230B38 ; =0x0000080B
	mov r1, #2
	bl FUN_02003210
	mov r0, #0xa
	str r0, [sp]
	mov r3, #0
	str r3, [sp, #4]
	add r0, r4, #0
	str r3, [sp, #8]
	add r0, #0xe8
	ldr r0, [r0]
	ldr r2, _02230B3C ; =0x0000FFFF
	mov r1, #8
	bl FUN_02003210
	add r0, r4, #0
	mov r1, #1
	bl MOD62_02230388
	add r0, r4, #0
	bl MOD62_0223039C
	mov r0, #0x8b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD08_02229A2C
	mov r0, #0xf7
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
_0223080C:
	add r0, r4, #0
	add r0, #0xe8
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	beq _0223081C
_0223081A:
	b _02230BDA
_0223081C:
	mov r0, #0x10
	mov r1, #0
	bl FUN_0201E6E4
	add r0, r4, #0
	mov r1, #1
	bl MOD62_022300DC
	mov r0, #0xf7
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r1, #4
	sub r0, #8
	str r1, [r4, r0]
	add r0, r4, #0
	ldr r1, _02230B3C ; =0x0000FFFF
	add r0, #0xec
	bl MOD62_0222EE78
	b _02230BDA
_02230846:
	add r0, #0xec
	mov r1, #0xc
	bl MOD62_0222EE78
	add r0, r4, #0
	bl MOD62_0222DC00
	cmp r0, #1
	bne _02230860
	mov r0, #0x26
	mov r1, #1
	lsl r0, r0, #4
	str r1, [r4, r0]
_02230860:
	add r0, r4, #0
	bl MOD62_0222DC7C
	add r0, r4, #0
	bl MOD62_0222EC28
	ldr r0, [r4]
	ldr r0, [r0, #0x28]
	bl FUN_02029FC8
	mov r1, #6
	bl FUN_0202A170
	mov r0, #0xf1
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	mov r0, #0xc
	mul r0, r1
	add r2, r4, r0
	mov r0, #0x99
	lsl r0, r0, #2
	ldr r0, [r2, r0]
	cmp r0, #0xff
	beq _022308A8
	ldr r2, [r4]
	lsl r0, r0, #2
	add r0, r2, r0
	ldr r5, [r0, #4]
	ldr r0, [r2, #0x20]
	bl FUN_02029C8C
	add r2, r0, #0
	add r0, r5, #0
	mov r1, #0xaa
	bl SetMonData
_022308A8:
	mov r0, #0xf5
	mov r1, #8
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _02230BDA
_022308B2:
	add r1, #8
	ldr r1, [r4, r1]
	cmp r1, #5
	bhi _0223093C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022308C6: ; jump table
	.short _022308D2 - _022308C6 - 2 ; case 0
	.short _02230930 - _022308C6 - 2 ; case 1
	.short _022309B4 - _022308C6 - 2 ; case 2
	.short _022309C6 - _022308C6 - 2 ; case 3
	.short _02230A2E - _022308C6 - 2 ; case 4
	.short _02230A6A - _022308C6 - 2 ; case 5
_022308D2:
	bl MOD62_0222DC00
	cmp r0, #0
	bne _022308E4
	mov r0, #0xf5
	mov r1, #8
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _02230BDA
_022308E4:
	mov r3, #0
	str r3, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	add r0, r4, #0
	str r3, [sp, #8]
	add r0, #0xe8
	ldr r0, [r0]
	ldr r2, _02230B38 ; =0x0000080B
	mov r1, #2
	bl FUN_02003210
	mov r3, #0
	str r3, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	add r0, r4, #0
	str r3, [sp, #8]
	add r0, #0xe8
	ldr r0, [r0]
	ldr r2, _02230B3C ; =0x0000FFFF
	mov r1, #8
	bl FUN_02003210
	add r0, r4, #0
	mov r1, #0
	bl MOD62_022300DC
	mov r0, #1
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #0xf7
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
_02230930:
	add r0, #0xe8
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	beq _0223093E
_0223093C:
	b _02230BDA
_0223093E:
	add r0, r4, #0
	add r0, #0xe8
	ldr r0, [r0]
	mov r1, #0
	bl FUN_020038F0
	mov r0, #1
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r2, #4
	add r0, r4, #0
	str r2, [sp, #8]
	mov r1, #0x28
	str r1, [sp, #0xc]
	add r0, #0xe4
	add r1, #0xe4
	ldr r0, [r0]
	add r1, r4, r1
	mov r3, #2
	bl MOD62_0222EEE0
	add r0, r4, #0
	add r0, #0xe4
	ldr r0, [r0]
	mov r1, #0x19
	str r0, [sp, #0x1c]
	mov r0, #4
	str r0, [sp, #0x20]
	mov r0, #0xd4
	str r0, [sp, #0x24]
	mov r0, #5
	str r0, [sp, #0x28]
	add r0, sp, #0x10
	strb r1, [r0, #0x1c]
	mov r1, #6
	strb r1, [r0, #0x1d]
	mov r0, #0x35
	bl FUN_02014590
	mov r1, #0x89
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	add r1, sp, #0x1c
	bl FUN_020145C8
	mov r0, #0x43
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0xe
	bl MOD62_0222EE78
	mov r0, #0xf7
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
_022309B4:
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E74C
	mov r0, #0xf7
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
_022309C6:
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201466C
	cmp r0, #0
	beq _02230A76
	cmp r0, #1
	beq _022309DC
	cmp r0, #2
	bne _02230A76
_022309DC:
	mov r1, #0x3e
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r4, #0
	add r0, #0xe8
	ldr r0, [r0]
	mov r1, #1
	bl FUN_020038F0
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_020146C4
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_020145A8
	mov r0, #0x43
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #1
	bl FUN_0200D0E0
	mov r0, #0x43
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019570
	mov r0, #0x43
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019178
	mov r0, #0xf7
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
_02230A2E:
	mov r0, #0xa
	str r0, [sp]
	mov r3, #0
	str r3, [sp, #4]
	add r0, r4, #0
	str r3, [sp, #8]
	add r0, #0xe8
	ldr r0, [r0]
	ldr r2, _02230B38 ; =0x0000080B
	mov r1, #2
	bl FUN_02003210
	mov r0, #0xa
	str r0, [sp]
	mov r3, #0
	str r3, [sp, #4]
	add r0, r4, #0
	str r3, [sp, #8]
	add r0, #0xe8
	ldr r0, [r0]
	ldr r2, _02230B3C ; =0x0000FFFF
	mov r1, #8
	bl FUN_02003210
	mov r0, #0xf7
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
_02230A6A:
	add r0, #0xe8
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	beq _02230A78
_02230A76:
	b _02230BDA
_02230A78:
	mov r0, #0x3e
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _02230AC2
	cmp r1, #1
	beq _02230A8C
	cmp r1, #2
	beq _02230ABC
	b _02230AC2
_02230A8C:
	add r0, r4, #0
	bl MOD62_0222F790
	add r0, r4, #0
	bl MOD62_0222F7C4
	add r0, r4, #0
	bl MOD62_0222F0D4
	add r0, r4, #0
	bl MOD62_0222DAEC
	add r0, r4, #0
	bl MOD62_0222D67C
	add r0, r4, #0
	mov r1, #1
	bl MOD62_0222DB10
	mov r0, #0xf5
	mov r1, #6
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _02230AC2
_02230ABC:
	mov r1, #4
	sub r0, #0xc
	str r1, [r4, r0]
_02230AC2:
	add r0, r4, #0
	mov r1, #1
	bl MOD62_022300DC
	mov r0, #0xf7
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _02230BDA
_02230AD4:
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r3, #0
	str r3, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r4, #0
	str r3, [sp, #8]
	add r0, #0xe8
	ldr r0, [r0]
	mov r1, #1
	mov r2, #2
	bl FUN_02003210
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
_02230B00:
	add r0, #0xe8
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	bne _02230BDA
	mov r0, #0x10
	str r0, [sp]
	mov r3, #0
	str r3, [sp, #4]
	add r0, r4, #0
	mov r1, #1
	str r3, [sp, #8]
	add r0, #0xe8
	ldr r0, [r0]
	add r2, r1, #0
	bl FUN_02003210
	mov r0, #0x10
	str r0, [sp]
	mov r3, #0
	str r3, [sp, #4]
	add r0, r4, #0
	str r3, [sp, #8]
	add r0, #0xe8
	ldr r0, [r0]
	ldr r2, _02230B3C ; =0x0000FFFF
	b _02230B40
	.align 2, 0
_02230B38: .word 0x0000080B
_02230B3C: .word 0x0000FFFF
_02230B40:
	mov r1, #4
	bl FUN_02003210
	mov r0, #3
	add r1, r0, #0
	bl FUN_020178BC
	mov r0, #7
	mov r1, #3
	bl FUN_020178BC
	mov r0, #4
	mov r1, #0
	bl FUN_0201E74C
	add r0, r4, #0
	mov r1, #0
	bl MOD62_0222F738
	add r0, r4, #0
	mov r1, #0
	bl MOD62_0222E9B4
	add r0, r4, #0
	mov r1, #0
	bl MOD62_0222DDE0
	mov r1, #0
	add r0, r4, #0
	mvn r1, r1
	mov r2, #4
	bl MOD62_0222E180
	add r0, r4, #0
	mov r1, #0
	bl MOD62_022300DC
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230BDA
_02230B96:
	add r0, #0xe8
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	bne _02230BDA
	add r0, r4, #0
	bl MOD62_022300D4
	cmp r0, #1
	beq _02230BDA
	mov r0, #0xbe
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200C644
	mov r1, #0
	add r0, r4, #0
	mov r2, #0xff
	add r3, r1, #0
	bl MOD62_0222F8D4
	add r0, r4, #0
	add r0, #0xec
	mov r1, #7
	bl MOD62_0222EE78
	add r0, r4, #0
	bl MOD62_0222F1E8
	add sp, #0xa4
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02230BDA:
	add r0, r4, #0
	add r0, #0xd4
	ldr r5, [r0]
	cmp r5, #0xff
	bne _02230BF0
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02022144
	b _02230C98
_02230BF0:
	add r0, sp, #0x14
	add r1, sp, #0x10
	bl FUN_02020AB0
	cmp r0, #0
	beq _02230C3E
	lsl r6, r5, #4
	mov r0, #0xca
	add r1, r4, r6
	lsl r0, r0, #2
	ldrb r0, [r1, r0]
	bl FUN_02085FD0
	add r1, r0, #0
	add r0, r4, #0
	add r0, #0xec
	bl MOD62_0222F208
	mov r0, #0xcb
	ldr r2, [sp, #0x10]
	add r1, r4, r6
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r1, [sp, #0x14]
	lsl r2, r2, #0x10
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	add r0, r4, #0
	add r1, r5, #0
	bl MOD62_0222DBCC
	add r0, r4, #0
	add r1, r5, #0
	bl MOD62_0222DC48
	b _02230C98
_02230C3E:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD62_0222DB38
	lsl r6, r5, #4
	mov r2, #0x33
	add r1, r4, r6
	lsl r2, r2, #4
	add r7, r0, #0
	ldr r0, [r1, r2]
	sub r2, r2, #4
	ldr r1, [r1, r2]
	mov r2, #0
	bl MOD62_0222D5F8
	cmp r7, #0
	bne _02230C80
	mov r1, #0xca
	ldr r0, [r4]
	add r2, r4, r6
	lsl r1, r1, #2
	ldrb r1, [r2, r1]
	ldr r0, [r0, #0x20]
	mov r2, #1
	bl FUN_02029D84
	add r0, r4, #0
	bl MOD62_0222F0D4
	add r0, r4, #0
	add r1, r5, #0
	bl MOD62_0222DB78
_02230C80:
	ldr r0, _02230CB8 ; =0x000005EA
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0xff
	add r0, #0xd4
	str r1, [r0]
	add r0, r4, #0
	ldr r1, _02230CBC ; =0x0000FFFF
	add r0, #0xec
	bl MOD62_0222F208
_02230C98:
	add r0, r4, #0
	bl MOD62_0222F758
	add r0, r4, #0
	bl MOD62_0222E990
	add r0, r4, #0
	bl MOD62_0222E754
	add r0, r4, #0
	bl MOD62_0222ECD4
	mov r0, #1
	add sp, #0xa4
	pop {r4, r5, r6, r7, pc}
	nop
_02230CB8: .word 0x000005EA
_02230CBC: .word 0x0000FFFF
	thumb_func_end MOD62_022303AC

	thumb_func_start MOD62_02230CC0
MOD62_02230CC0: ; 0x02230CC0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _02230CD8
	cmp r1, #1
	beq _02230CDC
	cmp r1, #2
	beq _02230CEC
	b _02230D26
_02230CD8:
	add r1, r1, #1
	str r1, [r4, r0]
_02230CDC:
	bl MOD62_0222F2A8
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230D26
_02230CEC:
	bl FUN_0200E308
	cmp r0, #1
	bne _02230D26
	add r0, r4, #0
	add r0, #0xec
	bl FUN_02019178
	add r0, r4, #0
	bl MOD62_0222ED04
	add r0, r4, #0
	bl MOD62_0222E77C
	add r0, r4, #0
	bl MOD62_0222F75C
	add r0, r4, #0
	bl MOD62_0222E9D4
	add r0, r4, #0
	bl MOD62_0222E0C8
	ldr r0, [r4]
	mov r1, #1
	bl FUN_02085D9C
	mov r0, #0
	pop {r4, pc}
_02230D26:
	add r0, r4, #0
	bl MOD62_0222E754
	add r0, r4, #0
	bl MOD62_0222ECD4
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD62_02230CC0

	thumb_func_start MOD62_02230D38
MOD62_02230D38: ; 0x02230D38
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	mov r0, #0
	add r4, r5, #4
	lsl r6, r1, #3
	str r0, [sp]
	ldr r0, [r4, r6]
	cmp r0, #0xff
	beq _02230D5C
	ldr r1, [r5]
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, #4]
	mov r1, #0xa1
	add r2, sp, #0
	bl SetMonData
_02230D5C:
	mov r0, #0xff
	str r0, [r4, r6]
	add r0, r5, #0
	bl MOD62_0222EC28
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD62_02230D38

	thumb_func_start MOD62_02230D6C
MOD62_02230D6C: ; 0x02230D6C
	push {r4, lr}
	mov r2, #0xf5
	add r4, r0, #0
	lsl r2, r2, #2
	ldr r1, [r4, r2]
	cmp r1, #0
	beq _02230D84
	cmp r1, #1
	beq _02230DA2
	cmp r1, #2
	beq _02230DB2
	b _02230DC6
_02230D84:
	sub r2, #0x10
	ldr r1, [r4, r2]
	bl MOD62_02230D38
	add r0, r4, #0
	add r0, #0xec
	mov r1, #9
	bl MOD62_0222EE78
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	b _02230DC6
_02230DA2:
	ldr r0, _02230DD8 ; =gMain
	ldr r3, [r0, #0x48]
	ldr r0, _02230DDC ; =0x00000CF3
	tst r0, r3
	beq _02230DC6
	add r0, r1, #1
	str r0, [r4, r2]
	b _02230DC6
_02230DB2:
	mov r1, #0
	mov r2, #0xff
	add r3, r1, #0
	bl MOD62_0222F8D4
	add r0, r4, #0
	add r0, #0xec
	mov r1, #7
	bl MOD62_0222EE78
_02230DC6:
	add r0, r4, #0
	bl MOD62_0222E754
	add r0, r4, #0
	bl MOD62_0222ECD4
	mov r0, #1
	pop {r4, pc}
	nop
_02230DD8: .word gMain
_02230DDC: .word 0x00000CF3
	thumb_func_end MOD62_02230D6C

	thumb_func_start MOD62_02230DE0
MOD62_02230DE0: ; 0x02230DE0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #3
	bls _02230DF0
	b _02230F18
_02230DF0:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02230DFC: ; jump table
	.short _02230E04 - _02230DFC - 2 ; case 0
	.short _02230E46 - _02230DFC - 2 ; case 1
	.short _02230ED0 - _02230DFC - 2 ; case 2
	.short _02230EE0 - _02230DFC - 2 ; case 3
_02230E04:
	sub r0, #0xe0
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl FUN_0200C6C4
	mov r0, #0xbe
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x14
	bl FUN_0200C6C4
	mov r0, #0xbd
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_0200C5C0
	add r0, r4, #0
	add r0, #0xec
	mov r1, #0xa
	bl MOD62_0222EE78
	mov r0, #0xbe
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_0200C644
	mov r0, #0xf5
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
_02230E46:
	mov r0, #0xf2
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD62_0222F9B4
	cmp r0, #1
	bne _02230E66
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD62_0222FA40
	ldr r0, _02230F28 ; =0x000005DC
	bl FUN_020054C8
	b _02230F18
_02230E66:
	ldr r0, _02230F2C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _02230EA4
	mov r2, #0xf1
	lsl r2, r2, #2
	ldr r1, [r4, r2]
	add r2, r2, #4
	ldr r2, [r4, r2]
	add r0, r4, #0
	bl MOD62_0222EC54
	mov r1, #1
	add r0, r4, #0
	add r2, r1, #0
	bl MOD62_0222FA40
	add r0, r4, #0
	add r0, #0xec
	mov r1, #0xb
	bl MOD62_0222EE78
	mov r0, #0xf5
	mov r1, #2
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, _02230F28 ; =0x000005DC
	bl FUN_020054C8
	b _02230F18
_02230EA4:
	mov r0, #2
	tst r0, r1
	beq _02230F18
	mov r0, #0xbe
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200C644
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	bl MOD62_0222FA40
	mov r0, #0xf5
	mov r1, #3
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, _02230F30 ; =0x000005DD
	bl FUN_020054C8
	b _02230F18
_02230ED0:
	ldr r1, _02230F2C ; =gMain
	ldr r2, [r1, #0x48]
	ldr r1, _02230F34 ; =0x00000CF3
	tst r1, r2
	beq _02230F18
	mov r1, #3
	str r1, [r4, r0]
	b _02230F18
_02230EE0:
	sub r0, #0xe0
	ldr r0, [r4, r0]
	mov r1, #0x14
	bl FUN_0200C6C4
	mov r0, #0xbe
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x19
	bl FUN_0200C6C4
	mov r1, #0
	add r0, r4, #0
	mov r2, #0xff
	add r3, r1, #0
	bl MOD62_0222F8D4
	mov r0, #0xbd
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200C5C0
	add r0, r4, #0
	add r0, #0xec
	mov r1, #7
	bl MOD62_0222EE78
_02230F18:
	add r0, r4, #0
	bl MOD62_0222E754
	add r0, r4, #0
	bl MOD62_0222ECD4
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_02230F28: .word 0x000005DC
_02230F2C: .word gMain
_02230F30: .word 0x000005DD
_02230F34: .word 0x00000CF3
	thumb_func_end MOD62_02230DE0

	thumb_func_start MOD62_02230F38
MOD62_02230F38: ; 0x02230F38
	mov r0, #0
	bx lr
	thumb_func_end MOD62_02230F38

	thumb_func_start MOD62_02230F3C
MOD62_02230F3C: ; 0x02230F3C
	push {r3, lr}
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _02230F68 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _02230F6C ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	pop {r3, pc}
	.align 2, 0
_02230F68: .word 0xFFFFE0FF
_02230F6C: .word 0x04001000
	thumb_func_end MOD62_02230F3C

	thumb_func_start MOD62_02230F70
MOD62_02230F70: ; 0x02230F70
	push {r3, lr}
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	pop {r3, pc}
	thumb_func_end MOD62_02230F70

	thumb_func_start MOD62_02230F80
MOD62_02230F80: ; 0x02230F80
	push {r4, r5, lr}
	sub sp, #0xfc
	add r4, r0, #0
	bl FUN_0201E6D8
	ldr r5, _022310B8 ; =MOD62_02231238
	add r3, sp, #0x10
	mov r2, #5
_02230F90:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02230F90
	add r0, sp, #0x10
	bl FUN_0201E66C
	mov r1, #6
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x18
	lsl r2, r2, #0x12
	bl MIi_CpuClear32
	mov r1, #0x62
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x14
	lsl r2, r2, #0x10
	bl MIi_CpuClear32
	mov r1, #0x19
	mov r2, #1
	mov r0, #0
	lsl r1, r1, #0x16
	lsl r2, r2, #0x12
	bl MIi_CpuClear32
	mov r1, #0x66
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x14
	lsl r2, r2, #0x10
	bl MIi_CpuClear32
	ldr r5, _022310BC ; =MOD62_02231210
	add r3, sp, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _022310C0 ; =MOD62_02231294
	add r3, sp, #0xa8
	mov r2, #0xa
_02230FF0:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02230FF0
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	add r2, sp, #0xa8
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #2
	add r2, sp, #0xc4
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #3
	add r2, sp, #0xe0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018744
	add r0, r4, #0
	mov r1, #2
	bl FUN_02018744
	add r0, r4, #0
	mov r1, #3
	bl FUN_02018744
	ldr r1, _022310C4 ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #1
	orr r2, r0
	strh r2, [r1]
	add r1, r0, #0
	bl FUN_0201E6E4
	ldr r5, _022310C8 ; =MOD62_022312E8
	add r3, sp, #0x38
	mov r2, #0xe
_02231052:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02231052
	add r0, r4, #0
	mov r1, #4
	add r2, sp, #0x38
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #5
	add r2, sp, #0x54
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #6
	add r2, sp, #0x70
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #7
	add r2, sp, #0x8c
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	add r0, r4, #0
	mov r1, #5
	bl FUN_02018744
	add r0, r4, #0
	mov r1, #6
	bl FUN_02018744
	add r0, r4, #0
	mov r1, #7
	bl FUN_02018744
	mov r0, #4
	mov r1, #0
	bl FUN_0201E74C
	add sp, #0xfc
	pop {r4, r5, pc}
	nop
_022310B8: .word MOD62_02231238
_022310BC: .word MOD62_02231210
_022310C0: .word MOD62_02231294
_022310C4: .word 0x04000008
_022310C8: .word MOD62_022312E8
	thumb_func_end MOD62_02230F80

	thumb_func_start MOD62_022310CC
MOD62_022310CC: ; 0x022310CC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x69
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_020081C4
	bl FUN_0201C30C
	bl FUN_0200BC30
	add r0, r4, #0
	add r0, #0xe8
	ldr r0, [r0]
	bl FUN_0200372C
	add r4, #0xe4
	ldr r0, [r4]
	bl FUN_0201AB60
	ldr r3, _02231104 ; =0x027E0000
	ldr r1, _02231108 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	nop
_02231104: .word 0x027E0000
_02231108: .word 0x00003FF8
	thumb_func_end MOD62_022310CC

	.section .rodata

	.global MOD62_0223110C
MOD62_0223110C: ; 0x0223110C
	.byte 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x00, 0x10, 0x00, 0x10, 0x00
	.byte 0x10, 0x00, 0x00, 0x00

	.global MOD62_02231120
MOD62_02231120: ; 0x02231120
	.byte 0x60, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00
	.byte 0x40, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD62_02231138
MOD62_02231138: ; 0x02231138
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00

	.global MOD62_02231158
MOD62_02231158: ; 0x02231158
	.byte 0x13, 0x00, 0x17, 0x00
	.byte 0x4B, 0x00, 0x17, 0x00, 0x13, 0x00, 0x2F, 0x00, 0x4B, 0x00, 0x2F, 0x00, 0x13, 0x00, 0x47, 0x00
	.byte 0x4B, 0x00, 0x47, 0x00, 0x13, 0x00, 0x5F, 0x00, 0x4B, 0x00, 0x5F, 0x00

	.global MOD62_02231178
MOD62_02231178: ; 0x02231178
	.byte 0x88, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xF0, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global MOD62_022311A8
MOD62_022311A8: ; 0x022311A8
	.byte 0x14, 0x00, 0x17, 0x00
	.byte 0x14, 0x00, 0x2F, 0x00, 0x14, 0x00, 0x47, 0x00, 0x14, 0x00, 0x5F, 0x00, 0x4C, 0x00, 0x17, 0x00
	.byte 0x4C, 0x00, 0x2F, 0x00, 0x4C, 0x00, 0x47, 0x00, 0x4C, 0x00, 0x5F, 0x00, 0x1B, 0x00, 0x7C, 0x00
	.byte 0x43, 0x00, 0x7C, 0x00, 0x20, 0x00, 0xAB, 0x00, 0x68, 0x00, 0xAB, 0x00, 0xC0, 0x00, 0xAB, 0x00

	.global MOD62_022311DC
MOD62_022311DC: ; 0x022311DC
	.byte 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00
	.byte 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00
	.byte 0x0D, 0x00, 0x0A, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x10, 0x00, 0x0C, 0x00, 0x1C, 0x00, 0x0C, 0x00
	.byte 0x1C, 0x00, 0x0C, 0x00

	.global MOD62_02231210
MOD62_02231210: ; 0x02231210
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00

	.global MOD62_02231220
MOD62_02231220: ; 0x02231220
	.word MOD62_0222FAB4, MOD62_022303AC, MOD62_02230CC0, MOD62_02230D6C
	.word MOD62_02230DE0, MOD62_02230F38

	.global MOD62_02231238
MOD62_02231238: ; 0x02231238
	.byte 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x60, 0x00, 0x00, 0x00

	.global MOD62_02231260
MOD62_02231260: ; 0x02231260
	.byte 0x10, 0x20, 0x08, 0x18, 0x10, 0x20, 0x40, 0x50, 0x28, 0x38, 0x08, 0x18
	.byte 0x28, 0x38, 0x40, 0x50, 0x40, 0x50, 0x08, 0x18, 0x40, 0x50, 0x40, 0x50, 0x58, 0x68, 0x08, 0x18
	.byte 0x58, 0x68, 0x40, 0x50, 0x68, 0x80, 0x08, 0x30, 0x68, 0x80, 0x38, 0x60, 0xA8, 0xBC, 0x12, 0x4D
	.byte 0xA8, 0xBC, 0x61, 0x9C, 0xA8, 0xBC, 0xB2, 0xED

	.global MOD62_02231294
MOD62_02231294: ; 0x02231294
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x06, 0x04, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD62_022312E8
MOD62_022312E8: ; 0x022312E8
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0D, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x01, 0x00, 0x02, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0C, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0F, 0x01, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD62_02231358
MOD62_02231358: ; 0x02231358
	.word 0x00, MOD62_0222F93C
	.word 0x01, MOD62_0222F904
	.word 0x02, MOD62_0222F94C
	.word 0x03, MOD62_0222F970
	.word 0x04, MOD62_0222F980
