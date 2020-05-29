	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD42_02254840
MOD42_02254840: ; 0x02254840
	ldr r3, _02254848 ; =MOD20_02252978
	ldr r0, _0225484C ; =MOD42_02254854
	ldr r1, _02254850 ; =MOD42_02254A38
	bx r3
	.align 2, 0
_02254848: .word MOD20_02252978
_0225484C: .word MOD42_02254854
_02254850: .word MOD42_02254A38
	thumb_func_end MOD42_02254840

	thumb_func_start MOD42_02254854
MOD42_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x78
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD42_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD42_02254A04
	add r1, r4, #0
	mov r2, #1
	bl FUN_0200CA44
	cmp r0, #0
	beq _0225488C
	str r4, [r5]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0225488C:
	add r0, r4, #0
	bl FreeToHeap
_02254892:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254898: .word MOD42_02254A04
	thumb_func_end MOD42_02254854

	thumb_func_start MOD42_0225489C
MOD42_0225489C: ; 0x0225489C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r0, r1, #0
	str r1, [sp]
	str r2, [sp, #4]
	bl MOD20_02252C3C
	str r0, [r5, #0x60]
	add r0, r5, #0
	str r0, [sp, #8]
	add r0, #0x11
	add r7, r5, #0
	mov r6, #0
	add r4, r5, #0
	str r0, [sp, #8]
	add r7, #0x10
_022548BE:
	mov r0, #1
	strb r0, [r4, #0x13]
	strb r6, [r4, #0x12]
	ldr r0, [r5, #0x60]
	ldr r3, [sp, #8]
	add r1, r6, #0
	add r2, r7, #0
	bl FUN_0204C0A4
	ldrb r0, [r4, #0x10]
	add r7, r7, #4
	add r0, #0x10
	strb r0, [r4, #0x10]
	ldrb r0, [r4, #0x11]
	add r0, #0x10
	strb r0, [r4, #0x11]
	mov r0, #0
	strb r0, [r4, #0x13]
	add r0, r5, r6
	add r0, #0x70
	strb r6, [r0]
	ldr r0, [sp, #8]
	add r6, r6, #1
	add r0, r0, #4
	add r4, r4, #4
	str r0, [sp, #8]
	cmp r6, #6
	blt _022548BE
	mov r0, #0
	str r0, [r5, #0x28]
	str r0, [r5, #0x2c]
	str r0, [r5, #0xc]
	ldr r0, [sp]
	bl MOD20_02252C40
	bl FUN_020462AC
	add r7, r0, #0
	mov r4, #0
	add r6, r5, #0
_0225490E:
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_0205F524
	str r0, [r6, #0x30]
	add r4, r4, #1
	add r6, r6, #4
	cmp r4, #4
	blt _0225490E
	ldr r0, [sp]
	bl MOD20_02252C40
	bl FUN_0202A9B0
	str r0, [sp, #0xc]
	mov r4, #0
	add r7, r5, #0
	add r6, r5, #0
_02254932:
	lsl r1, r4, #0x18
	ldr r0, [sp, #0xc]
	lsr r1, r1, #0x18
	bl FUN_0202AAA0
	mov r1, #8
	str r0, [r7, #0x64]
	bl FUN_0202AAB8
	str r0, [r6, #0x40]
	add r1, r5, #0
	add r1, #0x76
	mov r0, #0
	add r4, r4, #1
	strb r0, [r1]
	add r7, r7, #4
	add r6, #8
	cmp r4, #3
	blt _02254932
	ldr r0, [sp]
	bl MOD20_02252C38
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl FUN_02034E30
	bl FUN_02034DCC
	add r6, r0, #0
	ldr r0, [r4, #0x1c]
	ldr r0, [r0]
	bl FUN_02034908
	cmp r0, #0
	beq _02254984
	ldr r0, [r4, #0x1c]
	ldr r0, [r0, #8]
	str r0, [r5, #4]
	ldr r0, [r4, #0x1c]
	ldr r0, [r0, #0xc]
	b _0225498A
_02254984:
	ldr r0, [r6, #8]
	str r0, [r5, #4]
	ldr r0, [r6, #0xc]
_0225498A:
	str r0, [r5, #8]
	ldr r1, [r5, #4]
	ldr r2, [sp, #4]
	asr r0, r1, #4
	lsr r0, r0, #0x1b
	add r0, r1, r0
	asr r0, r0, #5
	str r0, [r5, #4]
	ldr r1, [r5, #8]
	asr r0, r1, #4
	lsr r0, r0, #0x1b
	add r0, r1, r0
	asr r0, r0, #5
	str r0, [r5, #8]
	add r0, r5, #0
	add r0, #0x58
	add r1, r5, #4
	bl MOD42_02254CB4
	cmp r0, #0
	beq _022549C6
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	ldr r0, [sp]
	add sp, #0x10
	str r0, [r5, #0x5c]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_022549C6:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD42_0225489C

	thumb_func_start MOD42_022549CC
MOD42_022549CC: ; 0x022549CC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_022549D4:
	ldrb r2, [r5, #0x10]
	ldrb r3, [r5, #0x11]
	ldr r0, [r6, #0x60]
	sub r2, #0x10
	sub r3, #0x10
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	add r1, r4, #0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_0204C080
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _022549D4
	ldr r0, [r6, #0x58]
	bl MOD42_02254CF0
	add r0, r6, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD42_022549CC

	thumb_func_start MOD42_02254A04
MOD42_02254A04: ; 0x02254A04
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	cmp r1, #4
	bhs _02254A30
	lsl r2, r1, #2
	ldr r1, _02254A34 ; =0x022550CC
	add r0, r4, #0
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254A30
	add r0, r4, #0
	bl MOD42_022549CC
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x5c]
	bl MOD20_022529A0
_02254A30:
	pop {r3, r4, r5, pc}
	nop
_02254A34: .word 0x022550CC
	thumb_func_end MOD42_02254A04

	thumb_func_start MOD42_02254A38
MOD42_02254A38: ; 0x02254A38
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD42_02254A38

	thumb_func_start MOD42_02254A40
MOD42_02254A40: ; 0x02254A40
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _02254A48
	b _02254A4A
_02254A48:
	mov r1, #3
_02254A4A:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD42_02254A40

	thumb_func_start MOD42_02254A54
MOD42_02254A54: ; 0x02254A54
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A64
	cmp r0, #1
	beq _02254A74
	b _02254A8E
_02254A64:
	ldr r0, [r4, #0x58]
	mov r1, #0
	bl MOD42_02254EEC
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A8E
_02254A74:
	ldr r0, [r4, #0x58]
	mov r1, #0
	bl MOD42_02254F10
	cmp r0, #0
	beq _02254A8E
	ldr r0, [r4, #0x5c]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD42_02254A40
_02254A8E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD42_02254A54

	thumb_func_start MOD42_02254A94
MOD42_02254A94: ; 0x02254A94
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _02254AAC
	mov r1, #3
	bl MOD42_02254A40
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_02254AAC:
	bl MOD42_02254C04
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4, #0x2c]
	add r0, sp, #8
	add r1, sp, #4
	bl MOD20_02252BB8
	cmp r0, #0
	beq _02254B20
	ldr r5, [sp, #8]
	ldr r6, [sp, #4]
	mov r3, #0
_02254AC8:
	add r0, r4, r3
	add r0, #0x70
	ldrb r7, [r0]
	lsl r0, r7, #2
	add r2, r4, r0
	str r0, [sp]
	ldrb r0, [r2, #0x10]
	sub r1, r0, r5
	mov r0, #7
	mvn r0, r0
	cmp r1, r0
	blt _02254B1A
	cmp r1, #8
	bgt _02254B1A
	ldrb r0, [r2, #0x11]
	sub r1, r0, r6
	mov r0, #7
	mvn r0, r0
	cmp r1, r0
	blt _02254B1A
	cmp r1, #8
	bgt _02254B1A
	add r0, r4, #0
	add r1, r7, #0
	bl MOD42_02254BB4
	ldr r0, [sp]
	ldr r2, [sp, #8]
	add r1, r4, r0
	strb r2, [r1, #0x10]
	ldr r0, [sp, #4]
	strb r0, [r1, #0x11]
	mov r0, #1
	strb r0, [r1, #0x13]
	str r7, [r4, #0x28]
	str r0, [r4, #0x2c]
	add r0, r4, #0
	mov r1, #2
	bl MOD42_02254A40
	b _02254B20
_02254B1A:
	add r3, r3, #1
	cmp r3, #6
	blt _02254AC8
_02254B20:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD42_02254A94

	thumb_func_start MOD42_02254B28
MOD42_02254B28: ; 0x02254B28
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _02254B40
	mov r1, #3
	bl MOD42_02254A40
	add sp, #8
	mov r0, #0
	pop {r4, pc}
_02254B40:
	bl MOD42_02254C04
	str r0, [r4, #0xc]
	add r0, sp, #4
	add r1, sp, #0
	bl MOD20_02252B68
	cmp r0, #0
	beq _02254B68
	ldr r0, [r4, #0x28]
	ldr r1, [sp, #4]
	lsl r0, r0, #2
	add r0, r4, r0
	strb r1, [r0, #0x10]
	ldr r0, [r4, #0x28]
	ldr r1, [sp]
	lsl r0, r0, #2
	add r0, r4, r0
	strb r1, [r0, #0x11]
	b _02254B7A
_02254B68:
	ldr r0, [r4, #0x28]
	mov r1, #0
	lsl r0, r0, #2
	add r0, r4, r0
	strb r1, [r0, #0x13]
	add r0, r4, #0
	mov r1, #1
	bl MOD42_02254A40
_02254B7A:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	thumb_func_end MOD42_02254B28

	thumb_func_start MOD42_02254B80
MOD42_02254B80: ; 0x02254B80
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254B90
	cmp r0, #1
	beq _02254BA0
	b _02254BAE
_02254B90:
	ldr r0, [r4, #0x58]
	mov r1, #1
	bl MOD42_02254EEC
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254BAE
_02254BA0:
	ldr r0, [r4, #0x58]
	bl MOD42_02254F1C
	cmp r0, #0
	beq _02254BAE
	mov r0, #1
	pop {r4, pc}
_02254BAE:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD42_02254B80

	thumb_func_start MOD42_02254BB4
MOD42_02254BB4: ; 0x02254BB4
	push {r3, r4}
	add r2, r0, #0
	add r2, #0x70
	ldrb r2, [r2]
	cmp r2, r1
	beq _02254C00
	mov r4, #0
_02254BC2:
	add r2, r0, r4
	add r2, #0x70
	ldrb r2, [r2]
	cmp r1, r2
	beq _02254BD2
	add r4, r4, #1
	cmp r4, #6
	blt _02254BC2
_02254BD2:
	cmp r4, #0
	beq _02254BE6
_02254BD6:
	add r2, r0, r4
	add r2, #0x6f
	ldrb r3, [r2]
	add r2, r0, r4
	add r2, #0x70
	strb r3, [r2]
	sub r4, r4, #1
	bne _02254BD6
_02254BE6:
	add r2, r0, #0
	add r2, #0x70
	strb r1, [r2]
	mov r2, #0
_02254BEE:
	add r1, r0, r2
	add r1, #0x70
	ldrb r1, [r1]
	lsl r1, r1, #2
	add r1, r0, r1
	strb r2, [r1, #0x12]
	add r2, r2, #1
	cmp r2, #6
	blt _02254BEE
_02254C00:
	pop {r3, r4}
	bx lr
	thumb_func_end MOD42_02254BB4

	thumb_func_start MOD42_02254C04
MOD42_02254C04: ; 0x02254C04
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x5c]
	mov r7, #0
	bl MOD20_02252C30
	cmp r0, #0
	beq _02254CAE
	ldr r0, [r5, #0x5c]
	bl MOD20_02252C38
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl FUN_02034E30
	bl FUN_02034DCC
	add r6, r0, #0
	ldr r0, [r4, #0x1c]
	ldr r0, [r0]
	bl FUN_02034908
	cmp r0, #0
	beq _02254C3C
	ldr r1, [r4, #0x1c]
	ldr r0, [r1, #8]
	ldr r1, [r1, #0xc]
	b _02254C40
_02254C3C:
	ldr r0, [r6, #8]
	ldr r1, [r6, #0xc]
_02254C40:
	asr r2, r0, #4
	lsr r2, r2, #0x1b
	add r2, r0, r2
	asr r0, r2, #5
	asr r2, r1, #4
	lsr r2, r2, #0x1b
	add r2, r1, r2
	asr r1, r2, #5
	ldr r2, [r5, #4]
	cmp r0, r2
	bne _02254C5C
	ldr r2, [r5, #8]
	cmp r1, r2
	beq _02254C62
_02254C5C:
	str r0, [r5, #4]
	str r1, [r5, #8]
	mov r7, #1
_02254C62:
	add r0, r5, #0
	add r0, #0x76
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0x76
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0x76
	ldrb r0, [r0]
	cmp r0, #5
	blo _02254CAE
	mov r6, #0
	add r4, r5, #0
_02254C7E:
	ldr r0, [r5, #0x40]
	cmp r0, #0
	bne _02254C94
	ldr r0, [r4, #0x64]
	mov r1, #8
	bl FUN_0202AAB8
	str r0, [r5, #0x40]
	cmp r0, #0
	beq _02254C94
	mov r7, #1
_02254C94:
	cmp r0, #0
	beq _02254CA4
	ldr r0, [r4, #0x64]
	mov r1, #1
	bl FUN_0202AAB8
	str r0, [r5, #0x44]
	mov r7, #1
_02254CA4:
	add r6, r6, #1
	add r5, #8
	add r4, r4, #4
	cmp r6, #3
	blt _02254C7E
_02254CAE:
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD42_02254C04

	thumb_func_start MOD42_02254CB4
MOD42_02254CB4: ; 0x02254CB4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #8
	mov r1, #0x74
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254CEA
	add r0, #8
	mov r1, #4
	bl MOD20_022536F4
	str r5, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	bl MOD20_02252D24
	str r0, [r4, #0x20]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD42_02254D04
	str r4, [r6]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254CEA:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD42_02254CB4

	thumb_func_start MOD42_02254CF0
MOD42_02254CF0: ; 0x02254CF0
	push {r4, lr}
	add r4, r0, #0
	beq _02254D00
	bl MOD42_02254E7C
	add r0, r4, #0
	bl FreeToHeap
_02254D00:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD42_02254CF0

	thumb_func_start MOD42_02254D04
MOD42_02254D04: ; 0x02254D04
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	add r5, r0, #0
	add r7, r1, #0
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x78
	bl FUN_02006A34
	mov r0, #8
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x5c
	mov r1, #0xc
	mov r2, #0x76
	mov r3, #0x77
	bl MOD20_02253FBC
	mov r2, #0
	add r0, sp, #0x24
	strb r2, [r0, #0x12]
	mov r1, #2
	strb r1, [r0, #0x13]
	strb r2, [r0, #0x15]
	ldr r0, [r7]
	ldr r1, [r7, #4]
	add r2, sp, #0x28
	add r3, sp, #0x24
	bl MOD20_02254420
	ldr r0, [sp, #0x28]
	add r2, r5, #0
	lsl r0, r0, #0xc
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x24]
	mov r1, #1
	lsl r0, r0, #0xc
	str r0, [sp, #0x30]
	add r0, sp, #0x24
	strb r1, [r0, #0x14]
	mov r1, #0
	strh r1, [r0, #0x10]
	ldr r0, [r5, #0x20]
	add r1, sp, #0x2c
	add r2, #0x5c
	bl MOD20_02253E74
	str r0, [r5, #0x58]
	mov r1, #1
	add r0, sp, #0x24
	strb r1, [r0, #0x15]
	add r0, r5, #0
	str r0, [sp, #0x14]
	add r0, #0x5c
	mov r6, #0
	add r4, r7, #0
	str r5, [sp, #0xc]
	str r0, [sp, #0x14]
_02254D82:
	ldrb r0, [r4, #0xc]
	ldr r2, [sp, #0x14]
	lsl r0, r0, #0xc
	str r0, [sp, #0x2c]
	ldrb r0, [r4, #0xd]
	lsl r0, r0, #0xc
	str r0, [sp, #0x30]
	ldrb r0, [r4, #0xe]
	add r1, r0, #2
	add r0, sp, #0x24
	strb r1, [r0, #0x14]
	add r1, r6, #1
	strh r1, [r0, #0x10]
	ldr r0, [r5, #0x20]
	add r1, sp, #0x2c
	bl MOD20_02253E74
	ldr r1, [sp, #0xc]
	add r6, r6, #1
	str r0, [r1, #0x24]
	add r0, r1, #0
	add r0, r0, #4
	add r4, r4, #4
	str r0, [sp, #0xc]
	cmp r6, #6
	blt _02254D82
	add r0, r5, #0
	str r0, [sp, #0x18]
	add r0, #0x5c
	mov r6, #0
	add r4, r5, #0
	str r7, [sp, #0x10]
	str r0, [sp, #0x18]
_02254DC4:
	add r0, r6, #0
	add r1, sp, #0x28
	add r2, sp, #0x24
	bl MOD20_02254460
	ldr r0, [sp, #0x28]
	mov r1, #9
	lsl r0, r0, #0xc
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x18]
	lsl r0, r0, #0xc
	str r0, [sp, #0x30]
	add r0, sp, #0x24
	strb r1, [r0, #0x14]
	add r1, r6, #0
	add r1, #0xe
	strh r1, [r0, #0x10]
	ldr r0, [r5, #0x20]
	add r1, sp, #0x2c
	bl MOD20_02253E74
	str r0, [r4, #0x3c]
	ldr r0, [sp, #0x10]
	ldr r0, [r0, #0x2c]
	cmp r0, #0
	bne _02254E02
	ldr r0, [r4, #0x3c]
	mov r1, #1
	bl MOD20_02253F78
_02254E02:
	ldr r0, [sp, #0x10]
	add r6, r6, #1
	add r0, r0, #4
	add r4, r4, #4
	str r0, [sp, #0x10]
	cmp r6, #4
	blt _02254DC4
	add r0, r5, #0
	str r0, [sp, #0x20]
	add r0, #0x5c
	mov r6, #0
	add r4, r5, #0
	str r0, [sp, #0x20]
_02254E1C:
	ldr r0, [r7, #0x40]
	add r1, sp, #0x28
	add r2, sp, #0x24
	bl MOD20_02254488
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x28]
	mov r1, #8
	lsl r0, r0, #0xc
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x20]
	lsl r0, r0, #0xc
	str r0, [sp, #0x30]
	add r0, sp, #0x24
	strb r1, [r0, #0x14]
	mov r1, #0x12
	strh r1, [r0, #0x10]
	ldr r0, [r5, #0x20]
	add r1, sp, #0x2c
	bl MOD20_02253E74
	str r0, [r4, #0x4c]
	ldr r0, [r7, #0x3c]
	cmp r0, #0
	beq _02254E56
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	bne _02254E5E
_02254E56:
	ldr r0, [r4, #0x4c]
	mov r1, #1
	bl MOD20_02253F78
_02254E5E:
	add r6, r6, #1
	add r7, #8
	add r4, r4, #4
	cmp r6, #3
	blt _02254E1C
	ldr r0, _02254E78 ; =MOD42_02254FE8
	add r1, r5, #0
	mov r2, #3
	bl FUN_0200CA44
	str r0, [r5, #0x70]
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02254E78: .word MOD42_02254FE8
	thumb_func_end MOD42_02254D04

	thumb_func_start MOD42_02254E7C
MOD42_02254E7C: ; 0x02254E7C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x70]
	bl FUN_0200CAB4
	mov r6, #0
	add r4, r5, #0
	add r7, r6, #0
_02254E8C:
	ldr r1, [r4, #0x24]
	cmp r1, #0
	beq _02254E9A
	ldr r0, [r5, #0x20]
	bl MOD20_02253F14
	str r7, [r4, #0x24]
_02254E9A:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #6
	blt _02254E8C
	mov r6, #0
	add r4, r5, #0
	add r7, r6, #0
_02254EA8:
	ldr r1, [r4, #0x3c]
	cmp r1, #0
	beq _02254EB6
	ldr r0, [r5, #0x20]
	bl MOD20_02253F14
	str r7, [r4, #0x3c]
_02254EB6:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _02254EA8
	mov r6, #0
	add r4, r5, #0
	add r7, r6, #0
_02254EC4:
	ldr r1, [r4, #0x4c]
	cmp r1, #0
	beq _02254ED2
	ldr r0, [r5, #0x20]
	bl MOD20_02253F14
	str r7, [r4, #0x4c]
_02254ED2:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #3
	blt _02254EC4
	ldr r0, [r5, #0x20]
	ldr r1, [r5, #0x58]
	bl MOD20_02253F14
	add r5, #0x5c
	add r0, r5, #0
	bl MOD20_02254014
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD42_02254E7C

	thumb_func_start MOD42_02254EEC
MOD42_02254EEC: ; 0x02254EEC
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254F0C ; =0x022550F8
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254F0C: .word 0x022550F8
	thumb_func_end MOD42_02254EEC

	thumb_func_start MOD42_02254F10
MOD42_02254F10: ; 0x02254F10
	ldr r3, _02254F18 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254F18: .word MOD20_02253794
	thumb_func_end MOD42_02254F10

	thumb_func_start MOD42_02254F1C
MOD42_02254F1C: ; 0x02254F1C
	ldr r3, _02254F24 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254F24: .word MOD20_022537B8
	thumb_func_end MOD42_02254F1C

	thumb_func_start MOD42_02254F28
MOD42_02254F28: ; 0x02254F28
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD42_02254F28

	thumb_func_start MOD42_02254F3C
MOD42_02254F3C: ; 0x02254F3C
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254FC0 ; =0x022550DC
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x75
	mov r3, #6
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x73
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	ldr r0, [r5, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r1, _02254FC4 ; =0x04001000
	ldr r0, _02254FC8 ; =0xFFFFE0FF
	ldr r3, [r1]
	ldr r2, [r1]
	str r3, [sp, #0x10]
	and r0, r2
	lsl r2, r3, #0x13
	lsr r3, r2, #0x1b
	mov r2, #4
	orr r2, r3
	lsl r2, r2, #8
	orr r0, r2
	str r0, [r1]
	add r0, r4, #0
	bl MOD42_02254F28
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_02254FC0: .word 0x022550DC
_02254FC4: .word 0x04001000
_02254FC8: .word 0xFFFFE0FF
	thumb_func_end MOD42_02254F3C

	thumb_func_start MOD42_02254FCC
MOD42_02254FCC: ; 0x02254FCC
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r4, #0
	bl MOD42_02254F28
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD42_02254FCC

	thumb_func_start MOD42_02254FE8
MOD42_02254FE8: ; 0x02254FE8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r1, #0
	ldr r4, [r5]
	ldr r0, [r4, #0x28]
	cmp r0, #0
	beq _0225505E
	ldr r7, [r4, #0x24]
	lsl r6, r7, #2
	add r2, r4, r6
	ldrb r0, [r2, #0xf]
	cmp r0, #0
	beq _02255028
	add r0, r5, #0
	str r0, [sp, #4]
	add r0, #0x24
	str r0, [sp, #4]
	ldr r1, [sp, #4]
	add r0, r0, r6
	str r0, [sp]
	ldr r0, [r5, #0x20]
	ldr r1, [r1, r6]
	mov r2, #0
	bl MOD20_02253F80
	ldr r0, [sp, #4]
	add r7, #8
	ldr r0, [r0, r6]
	add r1, r7, #0
	bl MOD20_02253F28
	b _0225504C
_02255028:
	add r0, r5, #0
	str r0, [sp, #8]
	add r0, #0x24
	str r0, [sp, #8]
	ldr r1, [sp, #8]
	ldrb r2, [r2, #0xe]
	add r0, r0, r6
	str r0, [sp]
	ldr r0, [r5, #0x20]
	ldr r1, [r1, r6]
	add r2, r2, #2
	bl MOD20_02253F80
	ldr r0, [sp, #8]
	add r1, r7, #1
	ldr r0, [r0, r6]
	bl MOD20_02253F28
_0225504C:
	add r2, r4, r6
	ldrb r1, [r2, #0xc]
	ldr r0, [sp]
	ldrb r2, [r2, #0xd]
	ldr r0, [r0]
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	bl MOD20_02253F64
_0225505E:
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _022550C8
	ldr r0, [r4]
	ldr r1, [r4, #4]
	add r2, sp, #0x10
	add r3, sp, #0xc
	bl MOD20_02254420
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0xc]
	ldr r0, [r5, #0x58]
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	bl MOD20_02253F64
	mov r6, #0
	add r7, sp, #0x10
_02255082:
	ldr r0, [r4, #0x3c]
	cmp r0, #0
	beq _022550B6
	ldr r0, [r4, #0x40]
	add r1, r7, #0
	add r2, sp, #0xc
	bl MOD20_02254488
	cmp r0, #0
	ldr r0, [r5, #0x4c]
	beq _022550AE
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0xc]
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	bl MOD20_02253F64
	ldr r0, [r5, #0x4c]
	mov r1, #0
	bl MOD20_02253F78
	b _022550BE
_022550AE:
	mov r1, #1
	bl MOD20_02253F78
	b _022550BE
_022550B6:
	ldr r0, [r5, #0x4c]
	mov r1, #1
	bl MOD20_02253F78
_022550BE:
	add r6, r6, #1
	add r4, #8
	add r5, r5, #4
	cmp r6, #3
	blo _02255082
_022550C8:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD42_02254FE8

	.section .rodata
	; 0x022550CC
	.byte 0x55, 0x4A, 0x25, 0x02, 0x95, 0x4A, 0x25, 0x02, 0x29, 0x4B, 0x25, 0x02, 0x81, 0x4B, 0x25, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x3D, 0x4F, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xCD, 0x4F, 0x25, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	; .section .sinit
	.global SDK_OVERLAY.MODULE_42.SINIT_START
	.global SDK_OVERLAY.MODULE_42.SINIT_END
SDK_OVERLAY.MODULE_42.SINIT_START:
	.word MOD42_02254840
	.word 0
SDK_OVERLAY.MODULE_42.SINIT_END:
