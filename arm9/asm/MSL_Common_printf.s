	.include "asm/macros.inc"
	.include "global.inc"

    .data

	.global UNK_02106DA0
UNK_02106DA0: ; 0x02106DA0
	.byte 0x30, 0x78, 0x30, 0x70, 0x30, 0x00, 0x00, 0x00
	.size UNK_02106DA0,.-UNK_02106DA0

	.global UNK_02106DA8
UNK_02106DA8: ; 0x02106DA8
	.asciz "-INF"
	.size UNK_02106DA8,.-UNK_02106DA8

	.balign 4, 0
	.global UNK_02106DB0
UNK_02106DB0: ; 0x02106DB0
	.asciz "-inf"
	.size UNK_02106DB0,.-UNK_02106DB0

	.balign 4, 0
	.global UNK_02106DB8
UNK_02106DB8: ; 0x02106DB8
	.asciz "INF"
	.size UNK_02106DB8,.-UNK_02106DB8

	.balign 4, 0
	.global UNK_02106DBC
UNK_02106DBC: ; 0x02106DBC
	.asciz "inf"
	.size UNK_02106DBC,.-UNK_02106DBC

	.balign 4, 0
	.global UNK_02106DC0
UNK_02106DC0: ; 0x02106DC0
	.asciz "-NAN"
	.size UNK_02106DC0,.-UNK_02106DC0

	.balign 4, 0
	.global UNK_02106DC8
UNK_02106DC8: ; 0x02106DC8
	.asciz "-nan"
	.size UNK_02106DC8,.-UNK_02106DC8

	.balign 4, 0
	.global UNK_02106DD0
UNK_02106DD0: ; 0x02106DD0
	.asciz "NAN"
	.size UNK_02106DD0,.-UNK_02106DD0

	.balign 4, 0
	.global UNK_02106DD4
UNK_02106DD4: ; 0x02106DD4
	.asciz "nan"
	.size UNK_02106DD4,.-UNK_02106DD4

	.balign 4, 0
	.global UNK_02106DD8
UNK_02106DD8: ; 0x02106DD8
	.byte 0x00, 0x00, 0x00, 0x00
	.size UNK_02106DD8,.-UNK_02106DD8

	.global UNK_02106DDC
UNK_02106DDC: ; 0x02106DDC
	.byte 0x00, 0x00, 0x00, 0x00
	.size UNK_02106DDC,.-UNK_02106DDC

    .text

	arm_func_start parse_format
parse_format: ; 0x020DF600
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	ldrsb r3, [r0, #0x1]
	mov r4, #0x0
	mov r5, #0x1
	mov lr, r2
	strb r5, [sp, #0x0]
	strb r4, [sp, #0x1]
	strb r4, [sp, #0x2]
	strb r4, [sp, #0x3]
	strb r4, [sp, #0x4]
	str r4, [sp, #0x8]
	str r4, [sp, #0xc]
	cmp r3, #0x25
	add r12, r0, #0x1
	bne _020DF65C
	add r0, sp, #0x0
	strb r3, [sp, #0x5]
	ldmia r0, {r0-r3}
	stmia lr, {r0-r3}
	add sp, sp, #0x10
	add r0, r12, #0x1
	ldmia sp!, {r4-r8,pc}
_020DF65C:
	mov r2, #0x2
	mov r0, r4
	mov r5, r2
	mov r6, r4
	mov r7, #0x1
_020DF670:
	mov r8, r7
	cmp r3, #0x2b
	bgt _020DF6A0
	bge _020DF6C8
	cmp r3, #0x23
	bgt _020DF6F8
	cmp r3, #0x20
	blt _020DF6F8
	beq _020DF6D0
	cmp r3, #0x23
	beq _020DF6E0
	b _020DF6F8
_020DF6A0:
	cmp r3, #0x30
	bgt _020DF6F8
	cmp r3, #0x2d
	blt _020DF6F8
	beq _020DF6C0
	cmp r3, #0x30
	beq _020DF6E8
	b _020DF6F8
_020DF6C0:
	strb r6, [sp, #0x0]
	b _020DF6FC
_020DF6C8:
	strb r7, [sp, #0x1]
	b _020DF6FC
_020DF6D0:
	ldrb r4, [sp, #0x1]
	cmp r4, #0x1
	strneb r5, [sp, #0x1]
	b _020DF6FC
_020DF6E0:
	strb r7, [sp, #0x3]
	b _020DF6FC
_020DF6E8:
	ldrb r4, [sp, #0x0]
	cmp r4, #0x0
	strneb r2, [sp, #0x0]
	b _020DF6FC
_020DF6F8:
	mov r8, r0
_020DF6FC:
	cmp r8, #0x0
	ldrnesb r3, [r12, #0x1]!
	bne _020DF670
	cmp r3, #0x2a
	bne _020DF744
	ldr r0, [r1, #0x0]
	add r0, r0, #0x4
	str r0, [r1, #0x0]
	ldr r0, [r0, #-0x4]
	str r0, [sp, #0x8]
	cmp r0, #0x0
	bge _020DF73C
	rsb r0, r0, #0x0
	mov r2, #0x0
	strb r2, [sp, #0x0]
	str r0, [sp, #0x8]
_020DF73C:
	ldrsb r3, [r12, #0x1]!
	b _020DF794
_020DF744:
	ldr r4, _020DFB88 ; =__msl_digit
	mov r5, #0x0
	mov r0, #0xa
	b _020DF768
_020DF754:
	ldr r2, [sp, #0x8]
	sub r3, r3, #0x30
	mla r6, r2, r0, r3
	ldrsb r3, [r12, #0x1]!
	str r6, [sp, #0x8]
_020DF768:
	cmp r3, #0x0
	blt _020DF778
	cmp r3, #0x80
	blt _020DF780
_020DF778:
	mov r2, r5
	b _020DF78C
_020DF780:
	mov r2, r3, lsl #0x1
	ldrh r2, [r4, r2]
	and r2, r2, #0x8
_020DF78C:
	cmp r2, #0x0
	bne _020DF754
_020DF794:
	ldr r2, [sp, #0x8]
	ldr r0, _020DFB8C ; =0x000001FD
	cmp r2, r0
	ble _020DF7C4
	mov r1, #0xff
	add r0, sp, #0x0
	strb r1, [sp, #0x5]
	ldmia r0, {r0-r3}
	stmia lr, {r0-r3}
	add sp, sp, #0x10
	add r0, r12, #0x1
	ldmia sp!, {r4-r8,pc}
_020DF7C4:
	cmp r3, #0x2e
	bne _020DF858
	ldrsb r3, [r12, #0x1]!
	mov r0, #0x1
	strb r0, [sp, #0x2]
	cmp r3, #0x2a
	bne _020DF808
	ldr r0, [r1, #0x0]
	add r0, r0, #0x4
	str r0, [r1, #0x0]
	ldr r0, [r0, #-0x4]
	ldrsb r3, [r12, #0x1]!
	str r0, [sp, #0xc]
	cmp r0, #0x0
	movlt r0, #0x0
	strltb r0, [sp, #0x2]
	b _020DF858
_020DF808:
	ldr r2, _020DFB88 ; =__msl_digit
	mov r4, #0x0
	mov r0, #0xa
	b _020DF82C
_020DF818:
	ldr r1, [sp, #0xc]
	sub r3, r3, #0x30
	mla r5, r1, r0, r3
	ldrsb r3, [r12, #0x1]!
	str r5, [sp, #0xc]
_020DF82C:
	cmp r3, #0x0
	blt _020DF83C
	cmp r3, #0x80
	blt _020DF844
_020DF83C:
	mov r1, r4
	b _020DF850
_020DF844:
	mov r1, r3, lsl #0x1
	ldrh r1, [r2, r1]
	and r1, r1, #0x8
_020DF850:
	cmp r1, #0x0
	bne _020DF818
_020DF858:
	cmp r3, #0x6c
	mov r0, #0x1
	bgt _020DF890
	cmp r3, #0x68
	blt _020DF884
	beq _020DF8AC
	cmp r3, #0x6a
	beq _020DF8F8
	cmp r3, #0x6c
	beq _020DF8C8
	b _020DF91C
_020DF884:
	cmp r3, #0x4c
	beq _020DF8EC
	b _020DF91C
_020DF890:
	cmp r3, #0x74
	bgt _020DF8A0
	beq _020DF904
	b _020DF91C
_020DF8A0:
	cmp r3, #0x7a
	beq _020DF910
	b _020DF91C
_020DF8AC:
	ldrsb r1, [r12, #0x1]
	mov r2, #0x2
	strb r2, [sp, #0x4]
	cmp r1, #0x68
	streqb r0, [sp, #0x4]
	ldreqsb r3, [r12, #0x1]!
	b _020DF920
_020DF8C8:
	ldrsb r1, [r12, #0x1]
	mov r2, #0x3
	strb r2, [sp, #0x4]
	cmp r1, #0x6c
	bne _020DF920
	mov r1, #0x4
	strb r1, [sp, #0x4]
	ldrsb r3, [r12, #0x1]!
	b _020DF920
_020DF8EC:
	mov r1, #0x9
	strb r1, [sp, #0x4]
	b _020DF920
_020DF8F8:
	mov r1, #0x6
	strb r1, [sp, #0x4]
	b _020DF920
_020DF904:
	mov r1, #0x8
	strb r1, [sp, #0x4]
	b _020DF920
_020DF910:
	mov r1, #0x7
	strb r1, [sp, #0x4]
	b _020DF920
_020DF91C:
	mov r0, #0x0
_020DF920:
	cmp r0, #0x0
	ldrnesb r3, [r12, #0x1]!
	strb r3, [sp, #0x5]
	cmp r3, #0x61
	bgt _020DF974
	bge _020DFA5C
	cmp r3, #0x47
	bgt _020DF968
	subs r0, r3, #0x41
	addpl pc, pc, r0, lsl #0x2
	b _020DFB68
	b _020DFA5C ; case 65
	b _020DFB68 ; case 66
	b _020DFB68 ; case 67
	b _020DFB68 ; case 68
	b _020DFAA4 ; case 69
	b _020DFA24 ; case 70
	b _020DFA94 ; case 71
_020DF968:
	cmp r3, #0x58
	beq _020DF9E8
	b _020DFB68
_020DF974:
	cmp r3, #0x63
	bgt _020DF984
	beq _020DFB04
	b _020DFB68
_020DF984:
	sub r0, r3, #0x64
	cmp r0, #0x14
	addls pc, pc, r0, lsl #0x2
	b _020DFB68
	b _020DF9E8 ; case 100
	b _020DFAA4 ; case 101
	b _020DFA24 ; case 102
	b _020DFA94 ; case 103
	b _020DFB68 ; case 104
	b _020DF9E8 ; case 105
	b _020DFB68 ; case 106
	b _020DFB68 ; case 107
	b _020DFB68 ; case 108
	b _020DFB68 ; case 109
	b _020DFB54 ; case 110
	b _020DF9E8 ; case 111
	b _020DFAE0 ; case 112
	b _020DFB68 ; case 113
	b _020DFB68 ; case 114
	b _020DFB30 ; case 115
	b _020DFB68 ; case 116
	b _020DF9E8 ; case 117
	b _020DFB68 ; case 118
	b _020DFB68 ; case 119
	b _020DF9E8 ; case 120
_020DF9E8:
	ldrb r0, [sp, #0x4]
	cmp r0, #0x9
	moveq r0, #0xff
	streqb r0, [sp, #0x5]
	beq _020DFB70
	ldrb r0, [sp, #0x2]
	cmp r0, #0x0
	moveq r0, #0x1
	streq r0, [sp, #0xc]
	beq _020DFB70
	ldrb r0, [sp, #0x0]
	cmp r0, #0x2
	moveq r0, #0x1
	streqb r0, [sp, #0x0]
	b _020DFB70
_020DFA24:
	ldrb r0, [sp, #0x4]
	cmp r0, #0x2
	cmpne r0, #0x6
	cmpne r0, #0x7
	cmpne r0, #0x8
	cmpne r0, #0x4
	moveq r0, #0xff
	streqb r0, [sp, #0x5]
	beq _020DFB70
	ldrb r0, [sp, #0x2]
	cmp r0, #0x0
	moveq r0, #0x6
	streq r0, [sp, #0xc]
	b _020DFB70
_020DFA5C:
	ldrb r0, [sp, #0x2]
	cmp r0, #0x0
	moveq r0, #0xd
	streq r0, [sp, #0xc]
	ldrb r0, [sp, #0x4]
	cmp r0, #0x2
	cmpne r0, #0x6
	cmpne r0, #0x7
	cmpne r0, #0x8
	cmpne r0, #0x4
	cmpne r0, #0x1
	moveq r0, #0xff
	streqb r0, [sp, #0x5]
	b _020DFB70
_020DFA94:
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	moveq r0, #0x1
	streq r0, [sp, #0xc]
_020DFAA4:
	ldrb r0, [sp, #0x4]
	cmp r0, #0x2
	cmpne r0, #0x6
	cmpne r0, #0x7
	cmpne r0, #0x8
	cmpne r0, #0x4
	cmpne r0, #0x1
	moveq r0, #0xff
	streqb r0, [sp, #0x5]
	beq _020DFB70
	ldrb r0, [sp, #0x2]
	cmp r0, #0x0
	moveq r0, #0x6
	streq r0, [sp, #0xc]
	b _020DFB70
_020DFAE0:
	mov r3, #0x78
	mov r2, #0x1
	mov r1, #0x3
	mov r0, #0x8
	strb r3, [sp, #0x5]
	strb r2, [sp, #0x3]
	strb r1, [sp, #0x4]
	str r0, [sp, #0xc]
	b _020DFB70
_020DFB04:
	ldrb r1, [sp, #0x4]
	cmp r1, #0x3
	moveq r0, #0x5
	streqb r0, [sp, #0x4]
	beq _020DFB70
	ldrb r0, [sp, #0x2]
	cmp r0, #0x0
	cmpeq r1, #0x0
	movne r0, #0xff
	strneb r0, [sp, #0x5]
	b _020DFB70
_020DFB30:
	ldrb r0, [sp, #0x4]
	cmp r0, #0x3
	moveq r0, #0x5
	streqb r0, [sp, #0x4]
	beq _020DFB70
	cmp r0, #0x0
	movne r0, #0xff
	strneb r0, [sp, #0x5]
	b _020DFB70
_020DFB54:
	ldrb r0, [sp, #0x4]
	cmp r0, #0x9
	moveq r0, #0xff
	streqb r0, [sp, #0x5]
	b _020DFB70
_020DFB68:
	mov r0, #0xff
	strb r0, [sp, #0x5]
_020DFB70:
	add r0, sp, #0x0
	ldmia r0, {r0-r3}
	stmia lr, {r0-r3}
	add r0, r12, #0x1
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020DFB88: .word __msl_digit
_020DFB8C: .word 0x000001FD
    arm_func_end parse_format

	arm_func_start long2str
long2str: ; 0x020DFB90
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3-r11,lr}
	sub sp, sp, #0x10
	movs r10, r0
	mov r0, #0x0
	mov r5, r1
	str r0, [sp, #0xc]
	ldr r7, [sp, #0x4c]
	mov r6, r0
	strb r0, [r5, #-0x1]!
	ldrb r0, [sp, #0x43]
	str r1, [sp, #0x0]
	ldrb r8, [sp, #0x45]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x48]
	ldrb r11, [sp, #0x41]
	str r0, [sp, #0x8]
	cmpeq r7, #0x0
	bne _020DFC04
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020DFBF0
	cmp r8, #0x6f
	beq _020DFC04
_020DFBF0:
	add sp, sp, #0x10
	mov r0, r5
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020DFC04:
	cmp r8, #0x69
	bgt _020DFC2C
	bge _020DFC60
	cmp r8, #0x58
	bgt _020DFC20
	beq _020DFC8C
	b _020DFC94
_020DFC20:
	cmp r8, #0x64
	beq _020DFC60
	b _020DFC94
_020DFC2C:
	cmp r8, #0x6f
	bgt _020DFC40
	moveq r4, #0x8
	moveq r11, #0x0
	b _020DFC94
_020DFC40:
	cmp r8, #0x78
	bgt _020DFC94
	cmp r8, #0x75
	blt _020DFC94
	beq _020DFC80
	cmp r8, #0x78
	beq _020DFC8C
	b _020DFC94
_020DFC60:
	cmp r10, #0x0
	mov r4, #0xa
	bge _020DFC94
	mov r0, #0x1
	cmp r10, #0x80000000
	rsbne r10, r10, #0x0
	str r0, [sp, #0xc]
	b _020DFC94
_020DFC80:
	mov r4, #0xa
	mov r11, #0x0
	b _020DFC94
_020DFC8C:
	mov r4, #0x10
	mov r11, #0x0
_020DFC94:
	mov r0, r10
	mov r1, r4
	bl _u32_div_f
	mov r9, r1
	mov r0, r10
	mov r1, r4
	bl _u32_div_f
	cmp r9, #0xa
	mov r10, r0
	addlt r9, r9, #0x30
	blt _020DFCCC
	cmp r8, #0x78
	addeq r9, r9, #0x57
	addne r9, r9, #0x37
_020DFCCC:
	cmp r10, #0x0
	strb r9, [r5, #-0x1]!
	add r6, r6, #0x1
	bne _020DFC94
	cmp r4, #0x8
	bne _020DFD00
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ldrnesb r0, [r5, #0x0]
	cmpne r0, #0x30
	movne r0, #0x30
	strneb r0, [r5, #-0x1]!
	addne r6, r6, #0x1
_020DFD00:
	ldrb r0, [sp, #0x40]
	cmp r0, #0x2
	bne _020DFD34
	ldr r0, [sp, #0xc]
	ldr r7, [sp, #0x8]
	cmp r0, #0x0
	cmpeq r11, #0x0
	subne r7, r7, #0x1
	cmp r4, #0x10
	bne _020DFD34
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	subne r7, r7, #0x2
_020DFD34:
	ldr r0, [sp, #0x0]
	sub r1, r0, r5
	ldr r0, _020DFDD8 ; =0x000001FD
	add r1, r7, r1
	cmp r1, r0
	addgt sp, sp, #0x10
	movgt r0, #0x0
	ldmgtia sp!, {r3-r11,lr}
	addgt sp, sp, #0x10
	bxgt lr
	cmp r6, r7
	bge _020DFD78
	mov r0, #0x30
_020DFD68:
	add r6, r6, #0x1
	cmp r6, r7
	strb r0, [r5, #-0x1]!
	blt _020DFD68
_020DFD78:
	cmp r4, #0x10
	bne _020DFD94
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	movne r0, #0x30
	strneb r8, [r5, #-0x1]
	strneb r0, [r5, #-0x2]!
_020DFD94:
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	movne r0, #0x2d
	strneb r0, [r5, #-0x1]!
	bne _020DFDC4
	cmp r11, #0x1
	moveq r0, #0x2b
	streqb r0, [r5, #-0x1]!
	beq _020DFDC4
	cmp r11, #0x2
	moveq r0, #0x20
	streqb r0, [r5, #-0x1]!
_020DFDC4:
	mov r0, r5
	add sp, sp, #0x10
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020DFDD8: .word 0x000001FD
    arm_func_end long2str

	arm_func_start longlong2str
longlong2str: ; 0x020DFDDC
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3-r11,lr}
	sub sp, sp, #0x18
	mov r9, r1
	mov r1, #0x0
	mov r10, r0
	mov r6, r2
	mov r0, r1
	strb r0, [r6, #-0x1]!
	ldr r0, [sp, #0x58]
	cmp r9, #0x0
	str r0, [sp, #0x10]
	ldrb r0, [sp, #0x4f]
	cmpeq r10, #0x0
	str r2, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x54]
	str r1, [sp, #0x14]
	str r0, [sp, #0x8]
	ldrb r0, [sp, #0x4d]
	mov r7, r1
	ldrb r8, [sp, #0x51]
	str r0, [sp, #0xc]
	ldreq r0, [sp, #0x10]
	cmpeq r0, #0x0
	bne _020DFE6C
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020DFE58
	cmp r8, #0x6f
	beq _020DFE6C
_020DFE58:
	add sp, sp, #0x18
	mov r0, r6
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020DFE6C:
	cmp r8, #0x69
	bgt _020DFE94
	bge _020DFEC4
	cmp r8, #0x58
	bgt _020DFE88
	beq _020DFF18
	b _020DFF24
_020DFE88:
	cmp r8, #0x64
	beq _020DFEC4
	b _020DFF24
_020DFE94:
	cmp r8, #0x6f
	bgt _020DFEA4
	beq _020DFEF8
	b _020DFF24
_020DFEA4:
	cmp r8, #0x78
	bgt _020DFF24
	cmp r8, #0x75
	blt _020DFF24
	beq _020DFF08
	cmp r8, #0x78
	beq _020DFF18
	b _020DFF24
_020DFEC4:
	subs r0, r10, #0x0
	sbcs r0, r9, #0x0
	mov r11, #0xa
	mov r5, #0x0
	bge _020DFF24
	cmp r9, #0x80000000
	cmpeq r10, r5
	beq _020DFEEC
	rsbs r10, r10, #0x0
	rsc r9, r9, #0x0
_020DFEEC:
	mov r0, #0x1
	str r0, [sp, #0x14]
	b _020DFF24
_020DFEF8:
	mov r5, #0x0
	str r5, [sp, #0xc]
	mov r11, #0x8
	b _020DFF24
_020DFF08:
	mov r5, #0x0
	str r5, [sp, #0xc]
	mov r11, #0xa
	b _020DFF24
_020DFF18:
	mov r5, #0x0
	str r5, [sp, #0xc]
	mov r11, #0x10
_020DFF24:
	mov r0, r10
	mov r1, r9
	mov r2, r11
	mov r3, r5
	bl _ull_mod
	mov r4, r0
	mov r0, r10
	mov r1, r9
	mov r2, r11
	mov r3, r5
	bl _ll_udiv
	mov r10, r0
	cmp r4, #0xa
	mov r9, r1
	addlt r0, r4, #0x30
	blt _020DFF70
	cmp r8, #0x78
	addeq r0, r4, #0x57
	addne r0, r4, #0x37
_020DFF70:
	strb r0, [r6, #-0x1]!
	mov r0, #0x0
	cmp r9, r0
	cmpeq r10, r0
	add r7, r7, #0x1
	bne _020DFF24
	cmp r5, #0x0
	cmpeq r11, #0x8
	bne _020DFFB0
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ldrnesb r0, [r6, #0x0]
	cmpne r0, #0x30
	movne r0, #0x30
	strneb r0, [r6, #-0x1]!
	addne r7, r7, #0x1
_020DFFB0:
	ldrb r0, [sp, #0x4c]
	cmp r0, #0x2
	bne _020E0000
	ldr r0, [sp, #0x8]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	cmp r0, #0x0
	ldreq r0, [sp, #0xc]
	cmpeq r0, #0x0
	ldrne r0, [sp, #0x10]
	subne r0, r0, #0x1
	strne r0, [sp, #0x10]
	cmp r5, #0x0
	cmpeq r11, #0x10
	bne _020E0000
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ldrne r0, [sp, #0x10]
	subne r0, r0, #0x2
	strne r0, [sp, #0x10]
_020E0000:
	ldr r0, [sp, #0x0]
	ldr r1, _020E00B8 ; =0x000001FD
	sub r2, r0, r6
	ldr r0, [sp, #0x10]
	add r0, r0, r2
	cmp r0, r1
	addgt sp, sp, #0x18
	movgt r0, #0x0
	ldmgtia sp!, {r3-r11,lr}
	addgt sp, sp, #0x10
	bxgt lr
	ldr r0, [sp, #0x10]
	cmp r7, r0
	bge _020E0050
	mov r1, #0x30
_020E003C:
	ldr r0, [sp, #0x10]
	add r7, r7, #0x1
	cmp r7, r0
	strb r1, [r6, #-0x1]!
	blt _020E003C
_020E0050:
	cmp r5, #0x0
	cmpeq r11, #0x10
	bne _020E0070
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	movne r0, #0x30
	strneb r8, [r6, #-0x1]
	strneb r0, [r6, #-0x2]!
_020E0070:
	ldr r0, [sp, #0x14]
	cmp r0, #0x0
	movne r0, #0x2d
	strneb r0, [r6, #-0x1]!
	bne _020E00A4
	ldr r0, [sp, #0xc]
	cmp r0, #0x1
	moveq r0, #0x2b
	streqb r0, [r6, #-0x1]!
	beq _020E00A4
	cmp r0, #0x2
	moveq r0, #0x20
	streqb r0, [r6, #-0x1]!
_020E00A4:
	mov r0, r6
	add sp, sp, #0x18
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E00B8: .word 0x000001FD
    arm_func_end longlong2str

	arm_func_start double2hex
double2hex: ; 0x020E00BC
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3-r10,lr}
	sub sp, sp, #0x44
	ldr r7, [sp, #0x80]
	ldr r0, _020E056C ; =0x000001FD
	mov r8, r2
	cmp r7, r0
	ldrb r6, [sp, #0x79]
	ldrb r5, [sp, #0x77]
	ldrb r4, [sp, #0x75]
	ldr r1, [sp, #0x68]
	ldr r2, [sp, #0x6c]
	addgt sp, sp, #0x44
	movgt r0, #0x0
	ldmgtia sp!, {r3-r10,lr}
	addgt sp, sp, #0x10
	bxgt lr
	mov r10, #0x0
	mov r9, #0x20
	add r0, sp, #0x8
	add r3, sp, #0xc
	strb r10, [sp, #0x8]
	strh r9, [sp, #0xa]
	bl __num2dec_internal2
	ldr r0, [sp, #0x68]
	ldr r1, [sp, #0x6c]
	bl fabs
	mov r2, r0
	mov r0, r10
	mov r3, r1
	mov r1, r0
	bl _deq
	bne _020E0188
	ldr r3, _020E0570 ; =UNK_02106DA0
	sub r0, r8, #0x6
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	add sp, sp, #0x44
	strb r2, [r8, #-0x6]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldrb r2, [r3, #0x4]
	ldrb r1, [r3, #0x5]
	strb r2, [r0, #0x4]
	strb r1, [r0, #0x5]
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
_020E0188:
	ldrb r0, [sp, #0x11]
	cmp r0, #0x49
	bne _020E0298
	ldrsb r0, [sp, #0xc]
	cmp r0, #0x0
	beq _020E0224
	cmp r6, #0x41
	sub r0, r8, #0x5
	bne _020E01E8
	ldr r3, _020E0574 ; =UNK_02106DA8
	add sp, sp, #0x44
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	strb r2, [r0, #0x0]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldrb r1, [r3, #0x4]
	strb r1, [r0, #0x4]
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
_020E01E8:
	ldr r3, _020E0578 ; =UNK_02106DB0
	add sp, sp, #0x44
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	strb r2, [r0, #0x0]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldrb r1, [r3, #0x4]
	strb r1, [r0, #0x4]
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
_020E0224:
	cmp r6, #0x41
	sub r0, r8, #0x4
	bne _020E0264
	ldr r3, _020E057C ; =UNK_02106DB8
	add sp, sp, #0x44
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	strb r2, [r0, #0x0]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
_020E0264:
	ldr r3, _020E0580 ; =UNK_02106DBC
	add sp, sp, #0x44
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	strb r2, [r0, #0x0]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
_020E0298:
	cmp r0, #0x4e
	bne _020E03A4
	ldrsb r0, [sp, #0xc]
	cmp r0, #0x0
	beq _020E0330
	cmp r6, #0x41
	sub r0, r8, #0x5
	bne _020E02F4
	ldr r3, _020E0584 ; =UNK_02106DC0
	add sp, sp, #0x44
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	strb r2, [r0, #0x0]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldrb r1, [r3, #0x4]
	strb r1, [r0, #0x4]
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
_020E02F4:
	ldr r3, _020E0588 ; =UNK_02106DC8
	add sp, sp, #0x44
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	strb r2, [r0, #0x0]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldrb r1, [r3, #0x4]
	strb r1, [r0, #0x4]
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
_020E0330:
	cmp r6, #0x41
	sub r0, r8, #0x4
	bne _020E0370
	ldr r3, _020E058C ; =UNK_02106DD0
	add sp, sp, #0x44
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	strb r2, [r0, #0x0]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
_020E0370:
	ldr r3, _020E0590 ; =UNK_02106DD4
	add sp, sp, #0x44
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	strb r2, [r0, #0x0]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
_020E03A4:
	mov r3, r10
	mov r1, #0x1
	mov r0, #0x64
	add r9, sp, #0x68
	strb r1, [sp, #0x34]
	strb r1, [sp, #0x35]
	strb r3, [sp, #0x36]
	strb r3, [sp, #0x37]
	strb r3, [sp, #0x38]
	str r3, [sp, #0x3c]
	str r1, [sp, #0x40]
	strb r0, [sp, #0x39]
_020E03D4:
	rsb r1, r3, #0x7
	ldrsb r2, [r9, r3]
	ldrsb r0, [r9, r1]
	strb r0, [r9, r3]
	add r3, r3, #0x1
	strb r2, [r9, r1]
	cmp r3, #0x4
	blt _020E03D4
	ldrb r0, [sp, #0x69]
	ldrb r1, [sp, #0x68]
	ldr sb, _020E0594 ; =0x000007FF
	mov r0, r0, lsl #0x11
	orr r1, r0, r1, lsl #0x19
	add r0, sp, #0x34
	and lr, r9, r1, lsr #0x15
	sub r12, sp, #0x8
	ldmia r0, {r0-r3}
	stmia r12, {r0-r3}
	rsb r0, r9, #0x400
	mov r1, r8
	add r0, lr, r0
	ldmia r12, {r2-r3}
	bl long2str
	cmp r6, #0x61
	moveq r1, #0x70
	movne r1, #0x50
	strb r1, [r0, #-0x1]!
	mov r1, r7, lsl #0x2
	mov lr, r7
	cmp r7, #0x1
	add r8, r1, #0xb
	add r12, sp, #0x68
	blt _020E04E4
	mov r9, #0x30
_020E045C:
	cmp r8, #0x40
	bge _020E04CC
	ldrb r1, [r12, r8, asr #0x3]
	and r2, r8, #0x7
	rsb r3, r2, #0x7
	mov r2, r1, asr r3
	sub r10, r8, #0x4
	bic r1, r8, #0x7
	bic r10, r10, #0x7
	cmp r1, r10
	add r10, r12, r8, asr #0x3
	and r1, r2, #0xff
	beq _020E04A0
	ldrb r2, [r10, #-0x1]
	mov r2, r2, lsl #0x8
	orr r1, r1, r2, asr r3
	and r1, r1, #0xff
_020E04A0:
	and r1, r1, #0xf
	cmp r1, #0xa
	addcc r1, r1, #0x30
	andcc r1, r1, #0xff
	blo _020E04D0
	cmp r6, #0x61
	addeq r1, r1, #0x57
	andeq r1, r1, #0xff
	addne r1, r1, #0x37
	andne r1, r1, #0xff
	b _020E04D0
_020E04CC:
	mov r1, r9
_020E04D0:
	sub lr, lr, #0x1
	cmp lr, #0x1
	strb r1, [r0, #-0x1]!
	sub r8, r8, #0x4
	bge _020E045C
_020E04E4:
	cmp r7, #0x0
	cmpeq r5, #0x0
	movne r1, #0x2e
	strneb r1, [r0, #-0x1]!
	mov r1, #0x31
	strb r1, [r0, #-0x1]
	cmp r6, #0x61
	moveq r1, #0x78
	movne r1, #0x58
	strb r1, [r0, #-0x2]!
	mov r1, #0x30
	strb r1, [r0, #-0x1]!
	ldrsb r1, [sp, #0xc]
	cmp r1, #0x0
	movne r1, #0x2d
	strneb r1, [r0, #-0x1]!
	addne sp, sp, #0x44
	ldmneia sp!, {r3-r10,lr}
	addne sp, sp, #0x10
	bxne lr
	cmp r4, #0x1
	moveq r1, #0x2b
	streqb r1, [r0, #-0x1]!
	addeq sp, sp, #0x44
	ldmeqia sp!, {r3-r10,lr}
	addeq sp, sp, #0x10
	bxeq lr
	cmp r4, #0x2
	moveq r1, #0x20
	streqb r1, [r0, #-0x1]!
	add sp, sp, #0x44
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E056C: .word 0x000001FD
_020E0570: .word UNK_02106DA0
_020E0574: .word UNK_02106DA8
_020E0578: .word UNK_02106DB0
_020E057C: .word UNK_02106DB8
_020E0580: .word UNK_02106DBC
_020E0584: .word UNK_02106DC0
_020E0588: .word UNK_02106DC8
_020E058C: .word UNK_02106DD0
_020E0590: .word UNK_02106DD4
_020E0594: .word 0x000007FF
    arm_func_end double2hex

	arm_func_start round_decimal
round_decimal: ; 0x020E0598
	stmdb sp!, {r4,lr}
	cmp r1, #0x0
	bge _020E05C0
_020E05A4:
	mov r1, #0x0
	strh r1, [r0, #0x2]
	mov r1, #0x1
	strb r1, [r0, #0x4]
	mov r1, #0x30
	strb r1, [r0, #0x5]
	ldmia sp!, {r4,pc}
_020E05C0:
	ldrb lr, [r0, #0x4]
	cmp r1, lr
	ldmgeia sp!, {r4,pc}
	add r12, r0, #0x5
	add r2, r12, r1
	add r2, r2, #0x1
	ldrsb r3, [r2, #-0x1]!
	sub r3, r3, #0x30
	mov r3, r3, lsl #0x18
	mov r3, r3, asr #0x18
	cmp r3, #0x5
	bne _020E0620
	add r12, r12, lr
_020E05F4:
	sub r12, r12, #0x1
	cmp r12, r2
	bls _020E060C
	ldrsb r3, [r12, #0x0]
	cmp r3, #0x30
	beq _020E05F4
_020E060C:
	cmp r12, r2
	ldreqsb r3, [r2, #-0x1]
	andeq r4, r3, #0x1
	movne r4, #0x1
	b _020E0628
_020E0620:
	movgt r4, #0x1
	movle r4, #0x0
_020E0628:
	cmp r1, #0x0
	beq _020E0684
	mov r12, #0x0
	mov lr, #0x1
_020E0638:
	ldrsb r3, [r2, #-0x1]!
	sub r3, r3, #0x30
	add r3, r3, r4
	mov r3, r3, lsl #0x18
	mov r3, r3, asr #0x18
	cmp r3, #0x9
	movgt r4, lr
	movle r4, r12
	cmp r4, #0x0
	bne _020E0668
	cmp r3, #0x0
	bne _020E0670
_020E0668:
	sub r1, r1, #0x1
	b _020E067C
_020E0670:
	add r3, r3, #0x30
	strb r3, [r2, #0x0]
	b _020E0684
_020E067C:
	cmp r1, #0x0
	bne _020E0638
_020E0684:
	cmp r4, #0x0
	beq _020E06AC
	ldrsh r3, [r0, #0x2]
	mov r2, #0x1
	mov r1, #0x31
	add r3, r3, #0x1
	strh r3, [r0, #0x2]
	strb r2, [r0, #0x4]
	strb r1, [r0, #0x5]
	ldmia sp!, {r4,pc}
_020E06AC:
	cmp r1, #0x0
	beq _020E05A4
	strb r1, [r0, #0x4]
	ldmia sp!, {r4,pc}
    arm_func_end round_decimal

	arm_func_start float2str
float2str: ; 0x020E06BC
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x2c
	ldr r7, [sp, #0x68]
	ldr r3, _020E0DF4 ; =0x000001FD
	ldrb r6, [sp, #0x61]
	ldrb r5, [sp, #0x5f]
	ldrb r4, [sp, #0x5d]
	cmp r7, r3
	mov r10, r0
	mov r8, r1
	mov r9, r2
	addgt sp, sp, #0x2c
	movgt r0, #0x0
	ldmgtia sp!, {r4-r11,lr}
	addgt sp, sp, #0x10
	bxgt lr
	mov r12, #0x0
	mov r11, #0x20
	add r0, sp, #0x0
	add r3, sp, #0x4
	mov r1, r10
	mov r2, r8
	strb r12, [sp, #0x0]
	strh r11, [sp, #0x2]
	bl __num2dec_internal2
	ldrb r0, [sp, #0x8]
	add r1, sp, #0x9
	add r0, r1, r0
	b _020E074C
_020E0734:
	ldrb r2, [sp, #0x8]
	ldrsh r1, [sp, #0x6]
	sub r2, r2, #0x1
	add r1, r1, #0x1
	strb r2, [sp, #0x8]
	strh r1, [sp, #0x6]
_020E074C:
	ldrb r1, [sp, #0x8]
	cmp r1, #0x1
	bls _020E0764
	ldrsb r1, [r0, #-0x1]!
	cmp r1, #0x30
	beq _020E0734
_020E0764:
	ldrb r0, [sp, #0x9]
	cmp r0, #0x30
	beq _020E0784
	cmp r0, #0x49
	beq _020E0790
	cmp r0, #0x4e
	beq _020E08F0
	b _020E0A44
_020E0784:
	mov r0, #0x0
	strh r0, [sp, #0x6]
	b _020E0A44
_020E0790:
	mov r2, #0x0
	mov r0, r10
	mov r1, r8
	mov r3, r2
	bl _dls
	bhs _020E0854
	cmp r6, #0x0
	sub r0, r9, #0x5
	blt _020E07BC
	cmp r6, #0x80
	blt _020E07C4
_020E07BC:
	mov r1, #0x0
	b _020E07D4
_020E07C4:
	ldr r1, _020E0DF8 ; =__msl_digit
	mov r2, r6, lsl #0x1
	ldrh r1, [r1, r2]
	and r1, r1, #0x200
_020E07D4:
	cmp r1, #0x0
	beq _020E0818
	ldr r3, _020E0DFC ; =UNK_02106DA8
	add sp, sp, #0x2c
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	strb r2, [r0, #0x0]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldrb r1, [r3, #0x4]
	strb r1, [r0, #0x4]
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E0818:
	ldr r3, _020E0E00 ; =UNK_02106DB0
	add sp, sp, #0x2c
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	strb r2, [r0, #0x0]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldrb r1, [r3, #0x4]
	strb r1, [r0, #0x4]
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E0854:
	cmp r6, #0x0
	sub r0, r9, #0x4
	blt _020E0868
	cmp r6, #0x80
	blt _020E0870
_020E0868:
	mov r1, #0x0
	b _020E0880
_020E0870:
	ldr r1, _020E0DF8 ; =__msl_digit
	mov r2, r6, lsl #0x1
	ldrh r1, [r1, r2]
	and r1, r1, #0x200
_020E0880:
	cmp r1, #0x0
	beq _020E08BC
	ldr r3, _020E0E04 ; =UNK_02106DB8
	add sp, sp, #0x2c
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	strb r2, [r0, #0x0]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E08BC:
	ldr r3, _020E0E08 ; =UNK_02106DBC
	add sp, sp, #0x2c
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	strb r2, [r0, #0x0]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E08F0:
	ldrsb r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020E09A8
	cmp r6, #0x0
	sub r0, r9, #0x5
	blt _020E0910
	cmp r6, #0x80
	blt _020E0918
_020E0910:
	mov r1, #0x0
	b _020E0928
_020E0918:
	ldr r1, _020E0DF8 ; =__msl_digit
	mov r2, r6, lsl #0x1
	ldrh r1, [r1, r2]
	and r1, r1, #0x200
_020E0928:
	cmp r1, #0x0
	beq _020E096C
	ldr r3, _020E0E0C ; =UNK_02106DC0
	add sp, sp, #0x2c
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	strb r2, [r0, #0x0]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldrb r1, [r3, #0x4]
	strb r1, [r0, #0x4]
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E096C:
	ldr r3, _020E0E10 ; =UNK_02106DC8
	add sp, sp, #0x2c
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	strb r2, [r0, #0x0]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldrb r1, [r3, #0x4]
	strb r1, [r0, #0x4]
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E09A8:
	cmp r6, #0x0
	sub r0, r9, #0x4
	blt _020E09BC
	cmp r6, #0x80
	blt _020E09C4
_020E09BC:
	mov r1, #0x0
	b _020E09D4
_020E09C4:
	ldr r1, _020E0DF8 ; =__msl_digit
	mov r2, r6, lsl #0x1
	ldrh r1, [r1, r2]
	and r1, r1, #0x200
_020E09D4:
	cmp r1, #0x0
	beq _020E0A10
	ldr r3, _020E0E14 ; =UNK_02106DD0
	add sp, sp, #0x2c
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	strb r2, [r0, #0x0]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E0A10:
	ldr r3, _020E0E18 ; =UNK_02106DD4
	add sp, sp, #0x2c
	ldrb r2, [r3, #0x0]
	ldrb r1, [r3, #0x1]
	strb r2, [r0, #0x0]
	strb r1, [r0, #0x1]
	ldrb r2, [r3, #0x2]
	ldrb r1, [r3, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E0A44:
	ldrb r0, [sp, #0x8]
	ldrsh r1, [sp, #0x6]
	sub r8, r9, #0x1
	sub r0, r0, #0x1
	add r0, r1, r0
	strh r0, [sp, #0x6]
	mov r0, #0x0
	strb r0, [r8, #0x0]
	cmp r6, #0x65
	bgt _020E0A98
	bge _020E0B24
	cmp r6, #0x47
	bgt _020E0DE0
	cmp r6, #0x45
	blt _020E0DE0
	beq _020E0B24
	cmp r6, #0x46
	beq _020E0C6C
	cmp r6, #0x47
	beq _020E0AB0
	b _020E0DE0
_020E0A98:
	cmp r6, #0x66
	bgt _020E0AA8
	beq _020E0C6C
	b _020E0DE0
_020E0AA8:
	cmp r6, #0x67
	bne _020E0DE0
_020E0AB0:
	ldrb r0, [sp, #0x8]
	cmp r0, r7
	ble _020E0AC8
	add r0, sp, #0x4
	mov r1, r7
	bl round_decimal
_020E0AC8:
	ldrsh r2, [sp, #0x6]
	mvn r0, #0x3
	cmp r2, r0
	blt _020E0AE0
	cmp r2, r7
	blt _020E0B00
_020E0AE0:
	cmp r5, #0x0
	ldreqb r0, [sp, #0x8]
	subne r7, r7, #0x1
	subeq r7, r0, #0x1
	cmp r6, #0x67
	moveq r6, #0x65
	movne r6, #0x45
	b _020E0B24
_020E0B00:
	cmp r5, #0x0
	addne r0, r2, #0x1
	subne r7, r7, r0
	bne _020E0C6C
	ldrb r1, [sp, #0x8]
	add r0, r2, #0x1
	subs r7, r1, r0
	movmi r7, #0x0
	b _020E0C6C
_020E0B24:
	ldrb r0, [sp, #0x8]
	add r1, r7, #0x1
	cmp r0, r1
	ble _020E0B3C
	add r0, sp, #0x4
	bl round_decimal
_020E0B3C:
	ldrsh lr, [sp, #0x6]
	mov r11, #0x2b
	mov r10, #0x0
	cmp lr, #0x0
	rsblt lr, lr, #0x0
	movlt r11, #0x2d
	ldr r3, _020E0E1C ; =0x66666667
	mov r0, #0xa
	b _020E0B90
_020E0B60:
	mov r1, lr, lsr #0x1f
	smull r2, r12, r3, lr
	add r12, r1, r12, asr #0x2
	smull r1, r2, r0, r12
	sub r12, lr, r1
	add r1, r12, #0x30
	strb r1, [r8, #-0x1]!
	mov r2, lr
	smull r1, lr, r3, r2
	mov r1, r2, lsr #0x1f
	add lr, r1, lr, asr #0x2
	add r10, r10, #0x1
_020E0B90:
	cmp lr, #0x0
	bne _020E0B60
	cmp r10, #0x2
	blt _020E0B60
	strb r11, [r8, #-0x1]
	strb r6, [r8, #-0x2]!
	sub r1, r9, r8
	ldr r0, _020E0DF4 ; =0x000001FD
	add r1, r7, r1
	cmp r1, r0
	addgt sp, sp, #0x2c
	movgt r0, #0x0
	ldmgtia sp!, {r4-r11,lr}
	addgt sp, sp, #0x10
	bxgt lr
	ldrb r1, [sp, #0x8]
	add r0, r7, #0x1
	cmp r1, r0
	bge _020E0BFC
	add r0, r7, #0x2
	sub r0, r0, r1
	subs r1, r0, #0x1
	beq _020E0BFC
	mov r0, #0x30
_020E0BF0:
	strb r0, [r8, #-0x1]!
	subs r1, r1, #0x1
	bne _020E0BF0
_020E0BFC:
	ldrb r1, [sp, #0x8]
	add r0, sp, #0x9
	add r2, r0, r1
	subs r1, r1, #0x1
	beq _020E0C20
_020E0C10:
	ldrsb r0, [r2, #-0x1]!
	subs r1, r1, #0x1
	strb r0, [r8, #-0x1]!
	bne _020E0C10
_020E0C20:
	cmp r7, #0x0
	cmpeq r5, #0x0
	movne r0, #0x2e
	strneb r0, [r8, #-0x1]!
	ldrb r0, [sp, #0x9]
	strb r0, [r8, #-0x1]!
	ldrsb r0, [sp, #0x4]
	cmp r0, #0x0
	movne r0, #0x2d
	strneb r0, [r8, #-0x1]!
	bne _020E0DE0
	cmp r4, #0x1
	moveq r0, #0x2b
	streqb r0, [r8, #-0x1]!
	beq _020E0DE0
	cmp r4, #0x2
	moveq r0, #0x20
	streqb r0, [r8, #-0x1]!
	b _020E0DE0
_020E0C6C:
	ldrsh r3, [sp, #0x6]
	ldrb r2, [sp, #0x8]
	sub r0, r2, r3
	subs r1, r0, #0x1
	movmi r1, #0x0
	cmp r1, r7
	ble _020E0CAC
	sub r1, r1, r7
	add r0, sp, #0x4
	sub r1, r2, r1
	bl round_decimal
	ldrsh r3, [sp, #0x6]
	ldrb r2, [sp, #0x8]
	sub r0, r2, r3
	subs r1, r0, #0x1
	movmi r1, #0x0
_020E0CAC:
	adds r0, r3, #0x1
	movmi r0, #0x0
	ldr r3, _020E0DF4 ; =0x000001FD
	add r6, r0, r1
	cmp r6, r3
	addgt sp, sp, #0x2c
	movgt r0, #0x0
	ldmgtia sp!, {r4-r11,lr}
	addgt sp, sp, #0x10
	bxgt lr
	add r3, sp, #0x9
	sub r6, r7, r1
	cmp r6, #0x0
	add r2, r3, r2
	mov r9, #0x0
	ble _020E0D00
	mov r3, #0x30
_020E0CF0:
	add r9, r9, #0x1
	cmp r9, r6
	strb r3, [r8, #-0x1]!
	blt _020E0CF0
_020E0D00:
	mov r6, #0x0
	b _020E0D14
_020E0D08:
	ldrsb r3, [r2, #-0x1]!
	add r6, r6, #0x1
	strb r3, [r8, #-0x1]!
_020E0D14:
	cmp r6, r1
	ldrltb r3, [sp, #0x8]
	cmplt r6, r3
	blt _020E0D08
	cmp r6, r1
	bge _020E0D40
	mov r3, #0x30
_020E0D30:
	add r6, r6, #0x1
	cmp r6, r1
	strb r3, [r8, #-0x1]!
	blt _020E0D30
_020E0D40:
	cmp r7, #0x0
	cmpeq r5, #0x0
	movne r1, #0x2e
	strneb r1, [r8, #-0x1]!
	cmp r0, #0x0
	beq _020E0DA8
	ldrb r1, [sp, #0x8]
	mov r5, #0x0
	sub r1, r0, r1
	cmp r1, #0x0
	ble _020E0D88
	mov r3, #0x30
_020E0D70:
	strb r3, [r8, #-0x1]!
	ldrb r1, [sp, #0x8]
	add r5, r5, #0x1
	sub r1, r0, r1
	cmp r5, r1
	blt _020E0D70
_020E0D88:
	cmp r5, r0
	bge _020E0DB0
_020E0D90:
	ldrsb r1, [r2, #-0x1]!
	add r5, r5, #0x1
	cmp r5, r0
	strb r1, [r8, #-0x1]!
	blt _020E0D90
	b _020E0DB0
_020E0DA8:
	mov r0, #0x30
	strb r0, [r8, #-0x1]!
_020E0DB0:
	ldrsb r0, [sp, #0x4]
	cmp r0, #0x0
	movne r0, #0x2d
	strneb r0, [r8, #-0x1]!
	bne _020E0DE0
	cmp r4, #0x1
	moveq r0, #0x2b
	streqb r0, [r8, #-0x1]!
	beq _020E0DE0
	cmp r4, #0x2
	moveq r0, #0x20
	streqb r0, [r8, #-0x1]!
_020E0DE0:
	mov r0, r8
	add sp, sp, #0x2c
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E0DF4: .word 0x000001FD
_020E0DF8: .word __msl_digit
_020E0DFC: .word UNK_02106DA8
_020E0E00: .word UNK_02106DB0
_020E0E04: .word UNK_02106DB8
_020E0E08: .word UNK_02106DBC
_020E0E0C: .word UNK_02106DC0
_020E0E10: .word UNK_02106DC8
_020E0E14: .word UNK_02106DD0
_020E0E18: .word UNK_02106DD4
_020E0E1C: .word 0x66666667
    arm_func_end float2str

	arm_func_start __pformatter
__pformatter:
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x22c
	mov r3, #0x20
	mov r11, r2
	strb r3, [sp, #0x19]
	ldrsb r2, [r11, #0x0]
	mov r9, r0
	mov r8, r1
	cmp r2, #0x0
	mov r10, #0x0
	beq _020E1628
_020E0E50:
	mov r0, r11
	mov r1, #0x25
	bl strchr
	str r0, [sp, #0xc]
	cmp r0, #0x0
	bne _020E0EA4
	mov r0, r11
	bl strlen
	movs r2, r0
	add r10, r10, r2
	beq _020E1628
	mov r0, r8
	mov r1, r11
	blx r9
	cmp r0, #0x0
	bne _020E1628
	add sp, sp, #0x22c
	mvn r0, #0x0
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E0EA4:
	subs r2, r0, r11
	add r10, r10, r2
	beq _020E0ED4
	mov r0, r8
	mov r1, r11
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x22c
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
_020E0ED4:
	ldr r0, [sp, #0xc]
	add r1, sp, #0x25c
	add r2, sp, #0x1c
	bl parse_format
	ldrb r1, [sp, #0x21]
	mov r11, r0
	cmp r1, #0x61
	bgt _020E0F40
	bge _020E12A4
	cmp r1, #0x47
	bgt _020E0F34
	subs r0, r1, #0x41
	addpl pc, pc, r0, lsl #0x2
	b _020E0F28
	b _020E12A4 ; case 65
	b _020E148C ; case 66
	b _020E148C ; case 67
	b _020E148C ; case 68
	b _020E123C ; case 69
	b _020E123C ; case 70
	b _020E123C ; case 71
_020E0F28:
	cmp r1, #0x25
	beq _020E1478
	b _020E148C
_020E0F34:
	cmp r1, #0x58
	beq _020E1100
	b _020E148C
_020E0F40:
	cmp r1, #0x75
	bgt _020E0FA8
	subs r0, r1, #0x64
	addpl pc, pc, r0, lsl #0x2
	b _020E0F9C
	b _020E0FC0 ; case 100
	b _020E123C ; case 101
	b _020E123C ; case 102
	b _020E123C ; case 103
	b _020E148C ; case 104
	b _020E0FC0 ; case 105
	b _020E148C ; case 106
	b _020E148C ; case 107
	b _020E148C ; case 108
	b _020E148C ; case 109
	b _020E13CC ; case 110
	b _020E1100 ; case 111
	b _020E148C ; case 112
	b _020E148C ; case 113
	b _020E148C ; case 114
	b _020E130C ; case 115
	b _020E148C ; case 116
	b _020E1100 ; case 117
_020E0F9C:
	cmp r1, #0x63
	beq _020E1458
	b _020E148C
_020E0FA8:
	cmp r1, #0x78
	bgt _020E0FB8
	beq _020E1100
	b _020E148C
_020E0FB8:
	cmp r1, #0xff
	b _020E148C
_020E0FC0:
	ldrb r0, [sp, #0x20]
	cmp r0, #0x3
	bne _020E0FE0
	ldr r1, [sp, #0x25c]
	add r1, r1, #0x4
	str r1, [sp, #0x25c]
	ldr r5, [r1, #-0x4]
	b _020E1078
_020E0FE0:
	cmp r0, #0x4
	bne _020E1008
	ldr r1, [sp, #0x25c]
	add r2, r1, #0x8
	str r2, [sp, #0x25c]
	ldr r1, [r2, #-0x8]
	str r1, [sp, #0x10]
	ldr r1, [r2, #-0x4]
	str r1, [sp, #0x14]
	b _020E1078
_020E1008:
	cmp r0, #0x6
	bne _020E1030
	ldr r1, [sp, #0x25c]
	add r2, r1, #0x8
	str r2, [sp, #0x25c]
	ldr r1, [r2, #-0x8]
	str r1, [sp, #0x10]
	ldr r1, [r2, #-0x4]
	str r1, [sp, #0x14]
	b _020E1078
_020E1030:
	cmp r0, #0x7
	bne _020E104C
	ldr r1, [sp, #0x25c]
	add r1, r1, #0x4
	str r1, [sp, #0x25c]
	ldr r5, [r1, #-0x4]
	b _020E1078
_020E104C:
	cmp r0, #0x8
	bne _020E1068
	ldr r1, [sp, #0x25c]
	add r1, r1, #0x4
	str r1, [sp, #0x25c]
	ldr r5, [r1, #-0x4]
	b _020E1078
_020E1068:
	ldr r1, [sp, #0x25c]
	add r1, r1, #0x4
	str r1, [sp, #0x25c]
	ldr r5, [r1, #-0x4]
_020E1078:
	cmp r0, #0x2
	moveq r1, r5, lsl #0x10
	moveq r5, r1, asr #0x10
	cmp r0, #0x1
	moveq r1, r5, lsl #0x18
	moveq r5, r1, asr #0x18
	cmp r0, #0x4
	cmpne r0, #0x6
	add r0, sp, #0x1c
	bne _020E10CC
	sub r4, sp, #0x4
	ldmia r0, {r0-r3}
	stmia r4, {r0-r3}
	ldr r3, [r4, #0x0]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r2, sp, #0x22c
	bl longlong2str
	movs r7, r0
	beq _020E148C
	b _020E10F0
_020E10CC:
	sub r4, sp, #0x8
	ldmia r0, {r0-r3}
	stmia r4, {r0-r3}
	add r1, sp, #0x22c
	mov r0, r5
	ldmia r4, {r2-r3}
	bl long2str
	movs r7, r0
	beq _020E148C
_020E10F0:
	add r0, sp, #0x200
	add r0, r0, #0x2b
	sub r6, r0, r7
	b _020E14D8
_020E1100:
	ldrb r0, [sp, #0x20]
	cmp r0, #0x3
	bne _020E1120
	ldr r1, [sp, #0x25c]
	add r1, r1, #0x4
	str r1, [sp, #0x25c]
	ldr r5, [r1, #-0x4]
	b _020E11B8
_020E1120:
	cmp r0, #0x4
	bne _020E1148
	ldr r1, [sp, #0x25c]
	add r2, r1, #0x8
	str r2, [sp, #0x25c]
	ldr r1, [r2, #-0x8]
	str r1, [sp, #0x10]
	ldr r1, [r2, #-0x4]
	str r1, [sp, #0x14]
	b _020E11B8
_020E1148:
	cmp r0, #0x6
	bne _020E1170
	ldr r1, [sp, #0x25c]
	add r2, r1, #0x8
	str r2, [sp, #0x25c]
	ldr r1, [r2, #-0x8]
	str r1, [sp, #0x10]
	ldr r1, [r2, #-0x4]
	str r1, [sp, #0x14]
	b _020E11B8
_020E1170:
	cmp r0, #0x7
	bne _020E118C
	ldr r1, [sp, #0x25c]
	add r1, r1, #0x4
	str r1, [sp, #0x25c]
	ldr r5, [r1, #-0x4]
	b _020E11B8
_020E118C:
	cmp r0, #0x8
	bne _020E11A8
	ldr r1, [sp, #0x25c]
	add r1, r1, #0x4
	str r1, [sp, #0x25c]
	ldr r5, [r1, #-0x4]
	b _020E11B8
_020E11A8:
	ldr r1, [sp, #0x25c]
	add r1, r1, #0x4
	str r1, [sp, #0x25c]
	ldr r5, [r1, #-0x4]
_020E11B8:
	cmp r0, #0x2
	moveq r1, r5, lsl #0x10
	moveq r5, r1, lsr #0x10
	cmp r0, #0x1
	andeq r5, r5, #0xff
	cmp r0, #0x4
	cmpne r0, #0x6
	add r0, sp, #0x1c
	bne _020E1208
	sub r4, sp, #0x4
	ldmia r0, {r0-r3}
	stmia r4, {r0-r3}
	ldr r3, [r4, #0x0]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r2, sp, #0x22c
	bl longlong2str
	movs r7, r0
	beq _020E148C
	b _020E122C
_020E1208:
	sub r4, sp, #0x8
	ldmia r0, {r0-r3}
	stmia r4, {r0-r3}
	add r1, sp, #0x22c
	mov r0, r5
	ldmia r4, {r2-r3}
	bl long2str
	movs r7, r0
	beq _020E148C
_020E122C:
	add r0, sp, #0x200
	add r0, r0, #0x2b
	sub r6, r0, r7
	b _020E14D8
_020E123C:
	ldrb r0, [sp, #0x20]
	cmp r0, #0x9
	ldrne r0, [sp, #0x25c]
	addne r0, r0, #0x8
	strne r0, [sp, #0x25c]
	bne _020E1260
	ldr r0, [sp, #0x25c]
	add r0, r0, #0x8
	str r0, [sp, #0x25c]
_020E1260:
	ldr r7, [r0, #-0x8]
	ldr r6, [r0, #-0x4]
	add r0, sp, #0x1c
	sub r4, sp, #0x4
	ldmia r0, {r0-r3}
	stmia r4, {r0-r3}
	ldr r3, [r4, #0x0]
	mov r0, r7
	mov r1, r6
	add r2, sp, #0x22c
	bl float2str
	movs r7, r0
	beq _020E148C
	add r0, sp, #0x200
	add r0, r0, #0x2b
	sub r6, r0, r7
	b _020E14D8
_020E12A4:
	ldrb r0, [sp, #0x20]
	cmp r0, #0x9
	ldrne r0, [sp, #0x25c]
	addne r0, r0, #0x8
	strne r0, [sp, #0x25c]
	bne _020E12C8
	ldr r0, [sp, #0x25c]
	add r0, r0, #0x8
	str r0, [sp, #0x25c]
_020E12C8:
	ldr r7, [r0, #-0x8]
	ldr r6, [r0, #-0x4]
	add r0, sp, #0x1c
	sub r4, sp, #0x4
	ldmia r0, {r0-r3}
	stmia r4, {r0-r3}
	ldr r3, [r4, #0x0]
	mov r0, r7
	mov r1, r6
	add r2, sp, #0x22c
	bl double2hex
	movs r7, r0
	beq _020E148C
	add r0, sp, #0x200
	add r0, r0, #0x2b
	sub r6, r0, r7
	b _020E14D8
_020E130C:
	ldrb r0, [sp, #0x20]
	cmp r0, #0x5
	bne _020E134C
	ldr r0, [sp, #0x25c]
	mov r2, #0x200
	add r0, r0, #0x4
	str r0, [sp, #0x25c]
	ldr r1, [r0, #-0x4]
	add r0, sp, #0x2c
	cmp r1, #0x0
	ldreq r1, _020E163C ; =UNK_02106DD8
	bl wcstombs
	cmp r0, #0x0
	blt _020E148C
	add r7, sp, #0x2c
	b _020E135C
_020E134C:
	ldr r0, [sp, #0x25c]
	add r0, r0, #0x4
	str r0, [sp, #0x25c]
	ldr r7, [r0, #-0x4]
_020E135C:
	ldrb r0, [sp, #0x1f]
	cmp r7, #0x0
	ldreq r7, _020E1640 ; =UNK_02106DDC
	cmp r0, #0x0
	beq _020E1390
	ldrb r0, [sp, #0x1e]
	ldrb r6, [r7], #0x1
	cmp r0, #0x0
	beq _020E14D8
	ldr r0, [sp, #0x28]
	cmp r6, r0
	movgt r6, r0
	b _020E14D8
_020E1390:
	ldrb r0, [sp, #0x1e]
	cmp r0, #0x0
	beq _020E13BC
	ldr r6, [sp, #0x28]
	mov r0, r7
	mov r2, r6
	mov r1, #0x0
	bl memchr
	cmp r0, #0x0
	subne r6, r0, r7
	b _020E14D8
_020E13BC:
	mov r0, r7
	bl strlen
	mov r6, r0
	b _020E14D8
_020E13CC:
	ldr r1, [sp, #0x25c]
	ldrb r0, [sp, #0x20]
	add r1, r1, #0x4
	str r1, [sp, #0x25c]
	ldr r1, [r1, #-0x4]
	cmp r0, #0x8
	addls pc, pc, r0, lsl #0x2
	b _020E161C
	b _020E1410 ; case 0
	b _020E161C ; case 1
	b _020E1418 ; case 2
	b _020E1420 ; case 3
	b _020E1448 ; case 4
	b _020E161C ; case 5
	b _020E1428 ; case 6
	b _020E1438 ; case 7
	b _020E1440 ; case 8
_020E1410:
	str r10, [r1, #0x0]
	b _020E161C
_020E1418:
	strh r10, [r1, #0x0]
	b _020E161C
_020E1420:
	str r10, [r1, #0x0]
	b _020E161C
_020E1428:
	str r10, [r1, #0x0]
	mov r0, r10, asr #0x1f
	str r0, [r1, #0x4]
	b _020E161C
_020E1438:
	str r10, [r1, #0x0]
	b _020E161C
_020E1440:
	str r10, [r1, #0x0]
	b _020E161C
_020E1448:
	str r10, [r1, #0x0]
	mov r0, r10, asr #0x1f
	str r0, [r1, #0x4]
	b _020E161C
_020E1458:
	ldr r0, [sp, #0x25c]
	add r7, sp, #0x2c
	add r0, r0, #0x4
	str r0, [sp, #0x25c]
	ldr r0, [r0, #-0x4]
	mov r6, #0x1
	strb r0, [sp, #0x2c]
	b _020E14D8
_020E1478:
	mov r0, #0x25
	strb r0, [sp, #0x2c]
	add r7, sp, #0x2c
	mov r6, #0x1
	b _020E14D8
_020E148C:
	ldr r0, [sp, #0xc]
	bl strlen
	movs r4, r0
	beq _020E14C4
	ldr r1, [sp, #0xc]
	mov r0, r8
	mov r2, r4
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x22c
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
_020E14C4:
	add sp, sp, #0x22c
	add r0, r10, r4
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E14D8:
	ldrb r0, [sp, #0x1c]
	mov r4, r6
	cmp r0, #0x0
	beq _020E158C
	cmp r0, #0x2
	moveq r0, #0x30
	movne r0, #0x20
	strb r0, [sp, #0x19]
	ldrsb r0, [r7, #0x0]
	cmp r0, #0x2b
	cmpne r0, #0x2d
	cmpne r0, #0x20
	bne _020E1548
	ldrsb r0, [sp, #0x19]
	cmp r0, #0x30
	bne _020E1548
	mov r0, r8
	mov r1, r7
	mov r2, #0x1
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x22c
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
	add r7, r7, #0x1
	sub r6, r6, #0x1
_020E1548:
	ldr r0, [sp, #0x24]
	cmp r4, r0
	bge _020E158C
_020E1554:
	mov r0, r8
	add r1, sp, #0x19
	mov r2, #0x1
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x22c
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r0, [sp, #0x24]
	add r4, r4, #0x1
	cmp r4, r0
	blt _020E1554
_020E158C:
	cmp r6, #0x0
	beq _020E15BC
	mov r0, r8
	mov r1, r7
	mov r2, r6
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x22c
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
_020E15BC:
	ldrb r0, [sp, #0x1c]
	cmp r0, #0x0
	bne _020E1618
	ldr r0, [sp, #0x24]
	cmp r4, r0
	bge _020E1618
	mov r6, #0x20
	add r7, sp, #0x18
_020E15DC:
	mov r0, r8
	mov r1, r7
	mov r2, #0x1
	strb r6, [sp, #0x18]
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x22c
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r0, [sp, #0x24]
	add r4, r4, #0x1
	cmp r4, r0
	blt _020E15DC
_020E1618:
	add r10, r10, r4
_020E161C:
	ldrsb r0, [r11, #0x0]
	cmp r0, #0x0
	bne _020E0E50
_020E1628:
	mov r0, r10
	add sp, sp, #0x22c
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E163C: .word UNK_02106DD8
_020E1640: .word UNK_02106DDC
    arm_func_end __pformatter

	arm_func_start __FileWrite
__FileWrite: ; 0x020E1644
	stmdb sp!, {r3-r5,lr}
	mov r5, r0
	mov r0, r1
	mov r3, r5
	mov r1, #0x1
	mov r4, r2
	bl __fwrite
	cmp r4, r0
	movne r5, #0x0
	mov r0, r5
	ldmia sp!, {r3-r5,pc}
    arm_func_end __FileWrite

	arm_func_start __StringWrite
__StringWrite: ; 0x020E1670
	stmdb sp!, {r3-r5,lr}
	mov r4, r0
	ldr r3, [r4, #0x8]
	mov r5, r2
	ldr r2, [r4, #0x4]
	add r0, r3, r5
	cmp r0, r2
	ldr r0, [r4, #0x0]
	subhi r5, r2, r3
	mov r2, r5
	add r0, r0, r3
	bl memcpy
	ldr r1, [r4, #0x8]
	mov r0, #0x1
	add r1, r1, r5
	str r1, [r4, #0x8]
	ldmia sp!, {r3-r5,pc}
    arm_func_end __StringWrite

	arm_func_start printf
printf: ; 0x020E16B4
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4,lr}
	ldr r0, _020E17B4 ; =__files + 0x4C
	mvn r1, #0x0
	bl fwide
	cmp r0, #0x0
	mvnge r0, #0x0
	ldmgeia sp!, {r4,lr}
	addge sp, sp, #0x10
	bxge lr
	ldr r0, _020E17B8 ; =__cs + 0x48
	bl OS_TryLockMutex
	cmp r0, #0x0
	bne _020E1710
	ldr r0, _020E17BC ; =OSi_ThreadInfo
	ldr r1, _020E17C0 ; =__cs_id
	ldr r2, [r0, #0x4]
	ldr r0, _020E17C4 ; =__cs_ref
	ldr r3, [r2, #0x6c]
	mov r2, #0x1
	str r3, [r1, #0xc]
	str r2, [r0, #0xc]
	b _020E1768
_020E1710:
	ldr r0, _020E17BC ; =OSi_ThreadInfo
	ldr r1, _020E17C0 ; =__cs_id
	ldr r0, [r0, #0x4]
	ldr r1, [r1, #0xc]
	ldr r0, [r0, #0x6c]
	cmp r1, r0
	bne _020E1740
	ldr r0, _020E17C4 ; =__cs_ref
	ldr r1, [r0, #0xc]
	add r1, r1, #0x1
	str r1, [r0, #0xc]
	b _020E1768
_020E1740:
	ldr r0, _020E17B8 ; =__cs + 0x48
	bl OS_LockMutex
	ldr r0, _020E17BC ; =OSi_ThreadInfo
	ldr r1, _020E17C0 ; =__cs_id
	ldr r2, [r0, #0x4]
	ldr r0, _020E17C4 ; =__cs_ref
	ldr r3, [r2, #0x6c]
	mov r2, #0x1
	str r3, [r1, #0xc]
	str r2, [r0, #0xc]
_020E1768:
	add r0, sp, #0x8
	bic r3, r0, #0x3
	ldr r2, [sp, #0x8]
	ldr r0, _020E17C8 ; =__FileWrite
	ldr r1, _020E17B4 ; =__files + 0x4C
	add r3, r3, #0x4
	bl __pformatter
	ldr r1, _020E17C4 ; =__cs_ref
	mov r4, r0
	ldr r0, [r1, #0xc]
	subs r0, r0, #0x1
	str r0, [r1, #0xc]
	bne _020E17A4
	ldr r0, _020E17B8 ; =__cs + 0x48
	bl OS_UnlockMutex
_020E17A4:
	mov r0, r4
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E17B4: .word __files + 0x4C
_020E17B8: .word __cs + 0x48
_020E17BC: .word OSi_ThreadInfo
_020E17C0: .word __cs_id
_020E17C4: .word __cs_ref
_020E17C8: .word __FileWrite
    arm_func_end printf

	arm_func_start vsnprintf
vsnprintf: ; 0x020E17CC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r5, r0
	mov r4, r1
	mov r12, #0x0
	ldr r0, _020E1830 ; =__StringWrite
	add r1, sp, #0x0
	str r5, [sp, #0x0]
	str r4, [sp, #0x4]
	str r12, [sp, #0x8]
	bl __pformatter
	cmp r5, #0x0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r5,pc}
	cmp r0, r4
	movcc r1, #0x0
	addcc sp, sp, #0xc
	strccb r1, [r5, r0]
	ldmccia sp!, {r4-r5,pc}
	cmp r4, #0x0
	addne r1, r5, r4
	movne r2, #0x0
	strneb r2, [r1, #-0x1]
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020E1830: .word __StringWrite
    arm_func_end vsnprintf

	arm_func_start snprintf
snprintf: ; 0x020E1834
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3,lr}
	add r3, sp, #0x10
	bic r3, r3, #0x3
	ldr r2, [sp, #0x10]
	add r3, r3, #0x4
	bl vsnprintf
	ldmia sp!, {r3,lr}
	add sp, sp, #0x10
	bx lr
    arm_func_end snprintf

	arm_func_start sprintf
sprintf: ; 0x020E185C
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3,lr}
	add r1, sp, #0xc
	bic r1, r1, #0x3
	add r3, r1, #0x4
	ldr r2, [sp, #0xc]
	mvn r1, #0x0
	bl vsnprintf
	ldmia sp!, {r3,lr}
	add sp, sp, #0x10
	bx lr
    arm_func_end sprintf

    .section .exceptix,4

	.word long2str
	.short 589
	.word 0x0090FF20
	.word longlong2str
	.short 737
	.word 0x00A0FF20
	.word double2hex
	.short 1245
	.word 0x00F07F20
	.word float2str
	.short 1893
	.word 0x00C0FF20
	.word __pformatter
	.short 2084
	.word UNK_020EC710
	.word __FileWrite
	.short 45
	.word 0x00200300
	.word __StringWrite
	.short 69
	.word 0x00200300
	.word printf
	.short 281
	.word 0x00300120
	.word vsnprintf
	.short 105
	.word 0x00300300
	.word snprintf
	.short 41
	.word 0x00300020
	.word sprintf
	.short 45
	.word 0x00300020

    .section .exception,8

UNK_020EC710: ; 0x020EC710
	.byte 0x20, 0xFF, 0x09, 0x60
	.balign 8
