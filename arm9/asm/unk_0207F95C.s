	.include "asm/macros.inc"
	.include "global.inc"

	.extern gMain
	.section .rodata

	.global UNK_020FB6F8
UNK_020FB6F8: ; 0x020FB6F8
	.byte 0x90, 0xB7, 0x50, 0x77, 0x90, 0xB7, 0x88, 0xAF, 0xFF, 0x00, 0x00, 0x00

	.global UNK_020FB704
UNK_020FB704: ; 0x020FB704
	.byte 0x03, 0x03, 0x0A, 0x12, 0x05, 0x03, 0x11, 0x12, 0xFF, 0xFF, 0xFF, 0xFF

	.global UNK_020FB710
UNK_020FB710: ; 0x020FB710
	.byte 0x48, 0x6F, 0x0C, 0x33, 0x78, 0x9F, 0x2C, 0x53, 0x90, 0xB7, 0x6C, 0x93, 0x78, 0x9F, 0xAC, 0xD3
	.byte 0x48, 0x6F, 0xCC, 0xF3, 0xFF, 0x00, 0x00, 0x00

	.global UNK_020FB728
UNK_020FB728: ; 0x020FB728
	.byte 0x00, 0x01, 0x02, 0x09, 0x01, 0x01, 0x06, 0x0F, 0x02, 0x02, 0x0E, 0x12, 0x03, 0x03, 0x16, 0x0F
	.byte 0x07, 0x04, 0x1A, 0x09, 0xFF, 0xFF, 0xFF, 0xFF

	.global UNK_020FB740
UNK_020FB740: ; 0x020FB740
	.byte 0x00, 0x01, 0x01, 0x04, 0x01, 0x01, 0x02, 0x0A, 0x02, 0x02, 0x05, 0x0F, 0x03, 0x03, 0x0A, 0x12
	.byte 0x04, 0x02, 0x11, 0x12, 0x05, 0x03, 0x16, 0x0F, 0x06, 0x04, 0x19, 0x0A, 0x07, 0x04, 0x1A, 0x04
	.byte 0xFF, 0xFF, 0xFF, 0xFF

	.global UNK_020FB764
UNK_020FB764: ; 0x020FB764
	.byte 0x20, 0x47, 0x08, 0x2F, 0x50, 0x77, 0x10, 0x37, 0x78, 0x9F, 0x28, 0x4F, 0x90, 0xB7, 0x50, 0x77
	.byte 0x90, 0xB7, 0x88, 0xAF, 0x78, 0x9F, 0xB0, 0xD7, 0x50, 0x77, 0xC8, 0xEF, 0x20, 0x47, 0xD0, 0xF7
	.byte 0xFF, 0x00, 0x00, 0x00

	.section .data

	.global UNK_0210613C
UNK_0210613C: ; 0x0210613C
	.word UNK_020FB764
	.word UNK_020FB710
	.word UNK_020FB6F8

	.global UNK_02106148
UNK_02106148: ; 0x02106148
	.word UNK_020FB740
	.word UNK_020FB728
	.word UNK_020FB704

	.text

	thumb_func_start FUN_0207F95C
FUN_0207F95C: ; 0x0207F95C
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r1, [r0, #0x12]
	cmp r1, #0x3
	bhi _0207F9AC
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0207F978: ; jump table (using 16-bit offset)
	.short _0207F980 - _0207F978 - 2; case 0
	.short _0207F980 - _0207F978 - 2; case 1
	.short _0207F9AC - _0207F978 - 2; case 2
	.short _0207F9AC - _0207F978 - 2; case 3
_0207F980:
	ldr r0, [r0, #0x2c]
	ldr r1, _0207F9C4 ; =0x0000068F
	cmp r0, #0x0
	beq _0207F992
	ldrb r2, [r4, r1]
	mov r0, #0xf
	bic r2, r0
	strb r2, [r4, r1]
	b _0207F9BA
_0207F992:
	ldrb r2, [r4, r1]
	mov r0, #0xf
	bic r2, r0
	mov r0, #0x1
	orr r0, r2
	strb r0, [r4, r1]
	mov r1, #0x4
	ldr r0, [r4, #0x0]
	mov r2, #0x0
	add r3, r1, #0x0
	bl FUN_0201AEE4
	b _0207F9BA
_0207F9AC:
	ldr r1, _0207F9C4 ; =0x0000068F
	mov r0, #0xf
	ldrb r2, [r4, r1]
	bic r2, r0
	mov r0, #0xf
	orr r0, r2
	strb r0, [r4, r1]
_0207F9BA:
	add r0, r4, #0x0
	bl FUN_0207FA38
	pop {r4, pc}
	nop
_0207F9C4: .word 0x0000068F

	thumb_func_start FUN_0207F9C8
FUN_0207F9C8: ; 0x0207F9C8
	push {r3-r7, lr}
	ldr r0, [r0, #0x0]
	add r4, r1, #0x0
	mov r1, #0x4
	add r5, r2, #0x0
	bl GetBgTilemapBuffer
	add r7, r0, #0x0
	lsl r0, r5, #0x2
	add r1, r5, r0
	ldrb r2, [r4, #0x0]
	mov r0, #0x1
	mov r3, #0x0
	add r5, r2, #0x0
	and r5, r0
	mov r0, #0xf
	mul r0, r5
	lsr r5, r2, #0x1
	mov r2, #0x96
	mul r2, r5
	add r0, r0, r2
	add r0, r1, r0
	add r0, #0x1e
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r12, r0
_0207F9FC:
	mov r0, #0x1e
	add r1, r3, #0x0
	mul r1, r0
	mov r0, r12
	mov r2, #0x0
	add r5, r0, r1
_0207FA08:
	ldrb r0, [r4, #0x1]
	ldrb r6, [r4, #0x3]
	lsl r1, r0, #0xc
	add r0, r2, r5
	add r1, r1, r0
	add r6, r3, r6
	lsl r6, r6, #0x5
	ldrb r0, [r4, #0x2]
	add r6, r2, r6
	add r0, r0, r6
	lsl r0, r0, #0x1
	strh r1, [r7, r0]
	add r0, r2, #0x1
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	cmp r2, #0x5
	blo _0207FA08
	add r0, r3, #0x1
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	cmp r3, #0x5
	blo _0207F9FC
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0207FA38
FUN_0207FA38: ; 0x0207FA38
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, _0207FA78 ; =0x0000068F
	ldrb r0, [r6, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r0, #0xf
	beq _0207FA74
	lsl r1, r0, #0x2
	ldr r0, _0207FA7C ; =UNK_02106148
	mov r5, #0x0
	ldr r4, [r0, r1]
	add r7, r5, #0x0
_0207FA52:
	lsl r1, r5, #0x2
	ldrb r0, [r4, r1]
	cmp r0, #0xff
	beq _0207FA6C
	add r0, r6, #0x0
	add r1, r4, r1
	add r2, r7, #0x0
	bl FUN_0207F9C8
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	b _0207FA52
_0207FA6C:
	ldr r0, [r6, #0x0]
	mov r1, #0x4
	bl FUN_0201AC68
_0207FA74:
	pop {r3-r7, pc}
	nop
_0207FA78: .word 0x0000068F
_0207FA7C: .word UNK_02106148

	thumb_func_start FUN_0207FA80
FUN_0207FA80: ; 0x0207FA80
	push {r3, lr}
	bl FUN_0207FA98
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _0207FA94
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}
_0207FA94:
	mov r0, #0xff
	pop {r3, pc}

	thumb_func_start FUN_0207FA98
FUN_0207FA98: ; 0x0207FA98
	push {r3, lr}
	ldr r1, _0207FAB8 ; =0x0000068F
	ldrb r0, [r0, r1]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r0, #0xf
	bne _0207FAAC
	mov r0, #0x0
	mvn r0, r0
	pop {r3, pc}
_0207FAAC:
	lsl r1, r0, #0x2
	ldr r0, _0207FABC ; =UNK_0210613C
	ldr r0, [r0, r1]
	bl FUN_02020988
	pop {r3, pc}
	.balign 4
_0207FAB8: .word 0x0000068F
_0207FABC: .word UNK_0210613C

	thumb_func_start FUN_0207FAC0
FUN_0207FAC0: ; 0x0207FAC0
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, _0207FB18 ; =0x0000068F
	ldrb r0, [r5, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r0, #0xf
	bne _0207FADA
	mov r0, #0x0
	add sp, #0x8
	mvn r0, r0
	pop {r3-r5, pc}
_0207FADA:
	lsl r1, r0, #0x2
	ldr r0, _0207FB1C ; =UNK_0210613C
	ldr r0, [r0, r1]
	bl FUN_02020968
	add r4, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	beq _0207FB12
	ldr r1, _0207FB20 ; =0x0000FFFE
	add r0, sp, #0x4
	strh r1, [r0, #0x0]
	add r0, sp, #0x4
	str r0, [sp, #0x0]
	ldr r3, _0207FB24 ; =gMain + 0x40
	ldr r0, [r5, #0x0]
	ldrh r2, [r3, #0x1c]
	ldrh r3, [r3, #0x1e]
	mov r1, #0x4
	bl FUN_0201AFBC
	cmp r0, #0x0
	bne _0207FB12
	mov r0, #0x0
	add sp, #0x8
	mvn r0, r0
	pop {r3-r5, pc}
_0207FB12:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_0207FB18: .word 0x0000068F
_0207FB1C: .word UNK_0210613C
_0207FB20: .word 0x0000FFFE
_0207FB24: .word gMain + 0x40

	thumb_func_start FUN_0207FB28
FUN_0207FB28: ; 0x0207FB28
	push {r4-r6, lr}
	ldr r1, _0207FBF4 ; =0x0000068F
	add r5, r0, #0x0
	ldrb r2, [r5, r1]
	lsl r2, r2, #0x1c
	lsr r3, r2, #0x1a
	ldr r2, _0207FBF8 ; =UNK_02106148
	ldr r4, [r2, r3]
	add r2, r1, #0x6
	ldrb r2, [r5, r2]
	cmp r2, #0x0
	beq _0207FB4A
	cmp r2, #0x1
	beq _0207FB84
	cmp r2, #0x2
	beq _0207FB8C
	b _0207FBEE
_0207FB4A:
	sub r1, #0xab
	add r0, r1, #0x0
	bl FUN_020054C8
	add r0, r5, #0x0
	bl FUN_0207FA38
	ldr r1, _0207FBFC ; =0x00000696
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	mov r2, #0x2
	lsl r1, r1, #0x2
	add r1, r4, r1
	bl FUN_0207F9C8
	ldr r0, [r5, #0x0]
	mov r1, #0x4
	bl FUN_0201AC68
	add r0, r5, #0x0
	bl FUN_0207CEDC
	ldr r0, _0207FC00 ; =0x00000694
	mov r1, #0x0
	strb r1, [r5, r0]
	mov r1, #0x1
	add r0, r0, #0x1
	strb r1, [r5, r0]
	b _0207FBEE
_0207FB84:
	mov r2, #0x2
	add r0, r1, #0x6
	strb r2, [r5, r0]
	b _0207FBEE
_0207FB8C:
	add r2, r1, #0x5
	ldrb r2, [r5, r2]
	cmp r2, #0x3
	beq _0207FBA0
	add r0, r1, #0x5
	ldrb r0, [r5, r0]
	add r2, r0, #0x1
	add r0, r1, #0x5
	strb r2, [r5, r0]
	b _0207FBEE
_0207FBA0:
	bl FUN_0207CF58
	ldr r0, _0207FBFC ; =0x00000696
	ldrb r6, [r5, r0]
	add r0, r5, #0x0
	bl FUN_0207FAC0
	cmp r6, r0
	beq _0207FBEE
	mov r0, #0x2a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	lsl r0, r0, #0x3
	lsr r0, r0, #0x1f
	beq _0207FBD6
	lsl r1, r6, #0x2
	ldrb r0, [r4, r1]
	cmp r0, #0x1
	beq _0207FBD6
	cmp r0, #0x7
	beq _0207FBD6
	add r0, r5, #0x0
	add r1, r4, r1
	mov r2, #0x0
	bl FUN_0207F9C8
	b _0207FBE2
_0207FBD6:
	lsl r1, r6, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	mov r2, #0x1
	bl FUN_0207F9C8
_0207FBE2:
	ldr r0, [r5, #0x0]
	mov r1, #0x4
	bl FUN_0201AC68
	mov r0, #0x1
	pop {r4-r6, pc}
_0207FBEE:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_0207FBF4: .word 0x0000068F
_0207FBF8: .word UNK_02106148
_0207FBFC: .word 0x00000696
_0207FC00: .word 0x00000694

	thumb_func_start FUN_0207FC04
FUN_0207FC04: ; 0x0207FC04
	push {r4-r5}
	ldr r4, _0207FC38 ; =0x0000068F
	ldrb r3, [r0, r4]
	lsl r3, r3, #0x1c
	lsr r5, r3, #0x1a
	ldr r3, _0207FC3C ; =UNK_02106148
	ldr r3, [r3, r5]
	add r5, r4, #0x7
	ldrb r5, [r0, r5]
	lsl r5, r5, #0x2
	add r5, r3, r5
	ldrb r5, [r5, #0x2]
	lsl r5, r5, #0x3
	add r5, #0x14
	strh r5, [r1, #0x0]
	add r1, r4, #0x7
	ldrb r0, [r0, r1]
	lsl r0, r0, #0x2
	add r0, r3, r0
	ldrb r0, [r0, #0x3]
	lsl r0, r0, #0x3
	add r0, #0x14
	strh r0, [r2, #0x0]
	pop {r4-r5}
	bx lr
	nop
_0207FC38: .word 0x0000068F
_0207FC3C: .word UNK_02106148

	thumb_func_start FUN_0207FC40
FUN_0207FC40: ; 0x0207FC40
	ldr r2, _0207FC54 ; =0x0000068F
	ldrb r0, [r0, r2]
	lsl r0, r0, #0x1c
	lsr r2, r0, #0x1a
	ldr r0, _0207FC58 ; =UNK_02106148
	ldr r2, [r0, r2]
	lsl r0, r1, #0x2
	ldrb r0, [r2, r0]
	bx lr
	nop
_0207FC54: .word 0x0000068F
_0207FC58: .word UNK_02106148
