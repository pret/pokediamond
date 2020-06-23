	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD69_0222D5C0
MOD69_0222D5C0: ; 0x0222D5C0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	mov r0, #3
	mov r1, #0x3f
	lsl r2, r0, #0x10
	bl FUN_0201681C
	ldr r1, _0222D70C ; =0x00001B60
	add r0, r5, #0
	mov r2, #0x3f
	bl FUN_02006268
	add r4, r0, #0
	add r0, r5, #0
	bl FUN_0200628C
	mov r2, #0x4e
	str r0, [r4, #0xc]
	mov r0, #0
	mov r1, #0x1a
	lsl r2, r2, #2
	mov r3, #0x3f
	bl NewMsgDataFromNarc
	ldr r1, _0222D710 ; =0x00001B5C
	str r0, [r4, r1]
	mov r0, #0x7d
	lsl r0, r0, #2
	mov r1, #0x3f
	bl String_ctor
	ldr r1, _0222D714 ; =0x00001B54
	str r0, [r4, r1]
	mov r0, #0x7d
	lsl r0, r0, #2
	mov r1, #0x3f
	bl String_ctor
	ldr r1, _0222D718 ; =0x00001B58
	str r0, [r4, r1]
	mov r0, #0x3f
	bl FUN_0200AA80
	ldr r1, _0222D71C ; =0x00001B50
	str r0, [r4, r1]
	mov r0, #0
	str r0, [r4, #4]
	ldr r0, [r4, #0xc]
	ldr r0, [r0, #4]
	bl GetPartyCount
	add r6, r0, #0
	mov r5, #0
	cmp r6, #0
	ble _0222D664
	mov r7, #0x7b
	lsl r7, r7, #2
_0222D63A:
	ldr r0, [r4, #0xc]
	add r1, r5, #0
	ldr r0, [r0, #4]
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222D65E
	ldr r0, [r4, #4]
	lsl r0, r0, #2
	add r0, r4, r0
	str r5, [r0, r7]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_0222D65E:
	add r5, r5, #1
	cmp r5, r6
	blt _0222D63A
_0222D664:
	add r0, r4, #0
	bl MOD69_0222DBAC
	add r0, r4, #0
	bl MOD69_0222DD54
	add r0, r4, #0
	bl MOD69_0222DE98
	ldr r0, _0222D720 ; =0x00001B3C
	mov r1, #0
	str r1, [r4, r0]
	add r0, r4, #0
	bl MOD69_0222EDCC
	ldr r1, _0222D724 ; =0x00001B38
	mov r2, #5
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	ldr r1, _0222D728 ; =0xFFFFF493
	lsl r2, r2, #0xe
	bl MOD69_0222EEBC
	ldr r0, _0222D724 ; =0x00001B38
	mov r2, #0xf
	ldr r0, [r4, r0]
	ldr r1, _0222D72C ; =0xFFFFF923
	lsl r2, r2, #0xe
	bl MOD69_0222EEBC
	ldr r0, _0222D724 ; =0x00001B38
	mov r2, #0xa
	ldr r0, [r4, r0]
	ldr r1, _0222D730 ; =0xFFFFFDB6
	lsl r2, r2, #0xe
	bl MOD69_0222EEBC
	ldr r0, _0222D724 ; =0x00001B38
	mov r2, #0x23
	ldr r0, [r4, r0]
	ldr r1, _0222D734 ; =0x0000024A
	lsl r2, r2, #0xe
	bl MOD69_0222EEBC
	ldr r0, _0222D724 ; =0x00001B38
	mov r2, #0x1e
	ldr r0, [r4, r0]
	ldr r1, _0222D738 ; =0x000006DD
	lsl r2, r2, #0xe
	bl MOD69_0222EEBC
	ldr r0, _0222D724 ; =0x00001B38
	mov r2, #0xa
	ldr r0, [r4, r0]
	ldr r1, _0222D73C ; =0x00000B6D
	lsl r2, r2, #0x10
	bl MOD69_0222EEBC
	add r0, r4, #0
	bl MOD69_0222F1B0
	ldr r1, _0222D720 ; =0x00001B3C
	ldr r2, _0222D740 ; =0x04000304
	str r0, [r4, r1]
	ldrh r1, [r2]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2]
	mov r0, #0
	str r0, [r4]
	ldr r0, _0222D744 ; =MOD69_0222DB2C
	add r1, r4, #0
	mov r2, #6
	bl MOD69_0222DBA4
	ldr r1, _0222D748 ; =0x00001B34
	mov r2, #1
	str r0, [r4, r1]
	ldr r1, _0222D74C ; =0x00000493
	mov r0, #8
	bl FUN_0200433C
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222D70C: .word 0x00001B60
_0222D710: .word 0x00001B5C
_0222D714: .word 0x00001B54
_0222D718: .word 0x00001B58
_0222D71C: .word 0x00001B50
_0222D720: .word 0x00001B3C
_0222D724: .word 0x00001B38
_0222D728: .word 0xFFFFF493
_0222D72C: .word 0xFFFFF923
_0222D730: .word 0xFFFFFDB6
_0222D734: .word 0x0000024A
_0222D738: .word 0x000006DD
_0222D73C: .word 0x00000B6D
_0222D740: .word 0x04000304
_0222D744: .word MOD69_0222DB2C
_0222D748: .word 0x00001B34
_0222D74C: .word 0x00000493

	thumb_func_start MOD69_0222D750
MOD69_0222D750: ; 0x0222D750
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r6, r0, #0
	cmp r1, #0
	beq _0222D762
	cmp r1, #1
	beq _0222D7C6
	b _0222D7D2
_0222D762:
	bl FUN_02006278
	add r4, r0, #0
	ldr r0, _0222D7D8 ; =0x00001B34
	ldr r0, [r4, r0]
	bl FUN_0200CAB4
	ldr r0, _0222D7DC ; =0x00001B3C
	ldr r0, [r4, r0]
	bl MOD69_0222F360
	ldr r0, _0222D7E0 ; =0x00001B38
	ldr r0, [r4, r0]
	bl MOD69_0222F150
	add r0, r4, #0
	bl MOD69_0222E1A0
	add r0, r4, #0
	bl MOD69_0222DE88
	add r0, r4, #0
	bl MOD69_0222DD18
	ldr r0, _0222D7E4 ; =0x00001B50
	ldr r0, [r4, r0]
	bl FUN_0200AB18
	ldr r0, _0222D7E8 ; =0x00001B54
	ldr r0, [r4, r0]
	bl String_dtor
	ldr r0, _0222D7EC ; =0x00001B58
	ldr r0, [r4, r0]
	bl String_dtor
	ldr r0, _0222D7F0 ; =0x00001B5C
	ldr r0, [r4, r0]
	bl DestroyMsgData
	add r0, r6, #0
	bl FUN_0200627C
	mov r0, #0x3f
	bl FUN_020168D0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0222D7D2
_0222D7C6:
	bl MOD69_0222F19C
	cmp r0, #0
	beq _0222D7D2
	mov r0, #1
	pop {r4, r5, r6, pc}
_0222D7D2:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_0222D7D8: .word 0x00001B34
_0222D7DC: .word 0x00001B3C
_0222D7E0: .word 0x00001B38
_0222D7E4: .word 0x00001B50
_0222D7E8: .word 0x00001B54
_0222D7EC: .word 0x00001B58
_0222D7F0: .word 0x00001B5C

	thumb_func_start MOD69_0222D7F4
MOD69_0222D7F4: ; 0x0222D7F4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	bl FUN_02006278
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #5
	bhs _0222D820
	lsl r2, r1, #2
	ldr r1, _0222D824 ; =0x0222F7D4
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _0222D81C
	mov r0, #0
	str r0, [r4]
	str r0, [r4, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
_0222D81C:
	mov r0, #0
	pop {r3, r4, r5, pc}
_0222D820:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222D824: .word MOD69_0222F7D4

	thumb_func_start MOD69_0222D828
MOD69_0222D828: ; 0x0222D828
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _0222D83A
	cmp r0, #1
	beq _0222D858
	b _0222D866
_0222D83A:
	mov r0, #0x10
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3f
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0222D866
_0222D858:
	bl FUN_0200E308
	cmp r0, #0
	beq _0222D866
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, pc}
_0222D866:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start MOD69_0222D86C
MOD69_0222D86C: ; 0x0222D86C
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _0222D87E
	cmp r0, #1
	beq _0222D8A6
	b _0222D8BC
_0222D87E:
	mov r0, #2
	str r0, [sp]
	mov r1, #0
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3f
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
	mov r0, #0
	mov r1, #0x1e
	bl FUN_020053CC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0222D8BC
_0222D8A6:
	bl FUN_0200E308
	cmp r0, #0
	beq _0222D8BC
	bl FUN_02005404
	cmp r0, #0
	bne _0222D8BC
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, pc}
_0222D8BC:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD69_0222D8C4
MOD69_0222D8C4: ; 0x0222D8C4
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #8]
	cmp r1, #0
	beq _0222D8D6
	sub r0, r1, #1
	str r0, [r4, #8]
	mov r0, #0
	pop {r4, pc}
_0222D8D6:
	ldr r1, [r4]
	cmp r1, #6
	bhi _0222D9CC
	add r2, r1, r1
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0222D8E8: ; jump table
	.short _0222D8F6 - _0222D8E8 - 2 ; case 0
	.short _0222D900 - _0222D8E8 - 2 ; case 1
	.short _0222D920 - _0222D8E8 - 2 ; case 2
	.short _0222D936 - _0222D8E8 - 2 ; case 3
	.short _0222D956 - _0222D8E8 - 2 ; case 4
	.short _0222D978 - _0222D8E8 - 2 ; case 5
	.short _0222D992 - _0222D8E8 - 2 ; case 6
_0222D8F6:
	ldr r0, _0222D9D0 ; =0x0222F960
	mov r2, #0
	str r2, [r0]
	add r0, r1, #1
	str r0, [r4]
_0222D900:
	ldr r1, _0222D9D0 ; =0x0222F960
	add r0, r4, #0
	ldr r1, [r1]
	mov r2, #0
	bl MOD69_0222E218
	ldr r1, _0222D9D0 ; =0x0222F960
	add r0, r4, #0
	ldr r1, [r1]
	mov r2, #1
	bl MOD69_0222E53C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0222D9CC
_0222D920:
	mov r1, #0
	bl MOD69_0222DB14
	cmp r0, #0
	beq _0222D9CC
	mov r0, #0x14
	str r0, [r4, #8]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0222D9CC
_0222D936:
	ldr r1, _0222D9D0 ; =0x0222F960
	mov r2, #1
	ldr r1, [r1]
	mov r3, #0
	bl MOD69_0222E6FC
	ldr r1, _0222D9D0 ; =0x0222F960
	add r0, r4, #0
	ldr r1, [r1]
	mov r2, #1
	bl MOD69_0222E804
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0222D9CC
_0222D956:
	mov r1, #0
	bl MOD69_0222DB14
	cmp r0, #0
	beq _0222D9CC
	add r0, r4, #0
	mov r1, #1
	bl MOD69_0222DB14
	cmp r0, #0
	beq _0222D9CC
	mov r0, #0x1e
	str r0, [r4, #8]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0222D9CC
_0222D978:
	mov r1, #0
	bl MOD69_0222EA84
	ldr r1, _0222D9D0 ; =0x0222F960
	add r0, r4, #0
	ldr r1, [r1]
	mov r2, #1
	bl MOD69_0222E590
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0222D9CC
_0222D992:
	mov r1, #0
	bl MOD69_0222DB14
	cmp r0, #0
	beq _0222D9CC
	ldr r0, _0222D9D0 ; =0x0222F960
	ldr r0, [r0]
	lsl r0, r0, #2
	add r1, r4, r0
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, _0222D9D0 ; =0x0222F960
	ldr r1, [r0]
	add r1, r1, #1
	str r1, [r0]
	ldr r0, [r4, #4]
	cmp r1, r0
	bge _0222D9C8
	mov r0, #0x1e
	str r0, [r4, #8]
	mov r0, #1
	str r0, [r4]
	b _0222D9CC
_0222D9C8:
	mov r0, #1
	pop {r4, pc}
_0222D9CC:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_0222D9D0: .word MOD69_0222F960

	thumb_func_start MOD69_0222D9D4
MOD69_0222D9D4: ; 0x0222D9D4
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r1, [r4, #8]
	cmp r1, #0
	beq _0222D9EA
	sub r0, r1, #1
	str r0, [r4, #8]
	add sp, #0x10
	mov r0, #0
	pop {r4, pc}
_0222D9EA:
	ldr r1, [r4]
	cmp r1, #8
	bhi _0222DAD4
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222D9FC: ; jump table
	.short _0222DA0E - _0222D9FC - 2 ; case 0
	.short _0222DA2E - _0222D9FC - 2 ; case 1
	.short _0222DA44 - _0222D9FC - 2 ; case 2
	.short _0222DA66 - _0222D9FC - 2 ; case 3
	.short _0222DA74 - _0222D9FC - 2 ; case 4
	.short _0222DA90 - _0222D9FC - 2 ; case 5
	.short _0222DA9E - _0222D9FC - 2 ; case 6
	.short _0222DAB4 - _0222D9FC - 2 ; case 7
	.short _0222DAC4 - _0222D9FC - 2 ; case 8
_0222DA0E:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	mov r0, #0x3f
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x10]
	mov r0, #0x69
	mov r3, #3
	bl FUN_020068C8
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0222DAD4
_0222DA2E:
	mov r1, #0
	bl MOD69_0222E2D8
	add r0, r4, #0
	mov r1, #1
	bl MOD69_0222E5F0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0222DAD4
_0222DA44:
	mov r1, #0
	bl MOD69_0222DB14
	cmp r0, #0
	beq _0222DAD4
	add r0, r4, #0
	mov r1, #1
	bl MOD69_0222DB14
	cmp r0, #0
	beq _0222DAD4
	mov r0, #0x14
	str r0, [r4, #8]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0222DAD4
_0222DA66:
	mov r1, #0
	bl MOD69_0222E644
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0222DAD4
_0222DA74:
	mov r1, #0
	bl MOD69_0222DB14
	cmp r0, #0
	beq _0222DAD4
	add r0, r4, #0
	bl MOD69_0222EB4C
	mov r0, #0x14
	str r0, [r4, #8]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0222DAD4
_0222DA90:
	mov r1, #0
	bl MOD69_0222EC60
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0222DAD4
_0222DA9E:
	mov r1, #0
	bl MOD69_0222DB14
	cmp r0, #0
	beq _0222DAD4
	mov r0, #0x14
	str r0, [r4, #8]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0222DAD4
_0222DAB4:
	ldr r0, _0222DADC ; =0x00001B3C
	ldr r0, [r4, r0]
	bl MOD69_0222F378
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0222DAD4
_0222DAC4:
	ldr r0, _0222DAE0 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0222DAD4
	add sp, #0x10
	mov r0, #1
	pop {r4, pc}
_0222DAD4:
	mov r0, #0
	add sp, #0x10
	pop {r4, pc}
	nop
_0222DADC: .word 0x00001B3C
_0222DAE0: .word 0x021C48B8

	thumb_func_start MOD69_0222DAE4
MOD69_0222DAE4: ; 0x0222DAE4
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4]
	cmp r1, #0
	beq _0222DAF4
	cmp r1, #1
	beq _0222DB02
	b _0222DB10
_0222DAF4:
	mov r1, #0
	bl MOD69_0222E6A0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0222DB10
_0222DB02:
	mov r1, #0
	bl MOD69_0222DB14
	cmp r0, #0
	beq _0222DB10
	mov r0, #1
	pop {r4, pc}
_0222DB10:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD69_0222DB14
MOD69_0222DB14: ; 0x0222DB14
	lsl r1, r1, #2
	add r1, r0, r1
	mov r0, #0x6d
	lsl r0, r0, #6
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _0222DB26
	mov r0, #1
	bx lr
_0222DB26:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD69_0222DB2C
MOD69_0222DB2C: ; 0x0222DB2C
	push {r4, lr}
	sub sp, #8
	ldr r0, _0222DB94 ; =0x04000600
	add r4, r1, #0
	ldr r1, [r0]
	mov r0, #2
	lsl r0, r0, #0x1a
	tst r0, r1
	bne _0222DB8E
	bl G3X_ResetMtxStack
	mov r1, #0
	mov r0, #0x11
	add r2, r1, #0
	bl FUN_020BB1C0
	ldr r0, _0222DB98 ; =0x00001B38
	ldr r0, [r4, r0]
	bl MOD69_0222F11C
	mov r2, #1
	mov r0, #0x12
	add r1, sp, #4
	str r2, [sp, #4]
	bl FUN_020BB1C0
	mov r1, #0
	mov r0, #0x11
	add r2, r1, #0
	bl FUN_020BB1C0
	ldr r0, _0222DB9C ; =0x00001B3C
	ldr r0, [r4, r0]
	bl MOD69_0222F63C
	mov r2, #1
	mov r0, #0x12
	add r1, sp, #0
	str r2, [sp]
	bl FUN_020BB1C0
	ldr r0, _0222DBA0 ; =0x04000540
	mov r1, #1
	str r1, [r0]
	ldr r0, [r4, #0x24]
	bl FUN_0201FDEC
	bl FUN_02009F80
_0222DB8E:
	add sp, #8
	pop {r4, pc}
	nop
_0222DB94: .word 0x04000600
_0222DB98: .word 0x00001B38
_0222DB9C: .word 0x00001B3C
_0222DBA0: .word 0x04000540

	thumb_func_start MOD69_0222DBA4
MOD69_0222DBA4: ; 0x0222DBA4
	ldr r3, _0222DBA8 ; =FUN_0200CA60
	bx r3
	.align 2, 0
_0222DBA8: .word FUN_0200CA60

	thumb_func_start MOD69_0222DBAC
MOD69_0222DBAC: ; 0x0222DBAC
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0x3f
	bl FUN_02016B94
	str r0, [r4, #0x10]
	ldr r0, _0222DCF4 ; =0x0222F8CC
	bl FUN_0201E66C
	ldr r2, _0222DCF8 ; =0x04000304
	ldr r0, _0222DCFC ; =0xFFFF7FFF
	ldrh r1, [r2]
	and r0, r1
	strh r0, [r2]
	ldr r0, _0222DD00 ; =0x0222F7C4
	bl FUN_02016BBC
	ldr r0, [r4, #0x10]
	ldr r2, _0222DD04 ; =0x0222F850
	mov r1, #1
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x10]
	ldr r2, _0222DD08 ; =0x0222F818
	mov r1, #2
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x10]
	ldr r2, _0222DD0C ; =0x0222F834
	mov r1, #3
	mov r3, #0
	bl FUN_02016C18
	mov r2, #0
	str r2, [sp]
	mov r1, #1
	ldr r0, [r4, #0x10]
	add r3, r1, #0
	bl FUN_02017F48
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	ldr r0, [r4, #0x10]
	mov r1, #1
	add r3, r2, #0
	bl FUN_02018540
	mov r3, #0
	add r1, r4, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r2, #1
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	ldr r0, [r4, #0x10]
	add r1, #0x14
	bl FUN_02019064
	add r0, r4, #0
	add r0, #0x14
	mov r1, #0
	bl FUN_02019620
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02019548
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02019270
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3f
	str r0, [sp, #0xc]
	mov r1, #3
	ldr r2, [r4, #0x10]
	mov r0, #0x69
	add r3, r1, #0
	bl FUN_0200687C
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3f
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x10]
	mov r0, #0x69
	mov r3, #3
	bl FUN_020068C8
	mov r0, #0x60
	str r0, [sp]
	mov r0, #0x3f
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x69
	mov r1, #4
	add r3, r2, #0
	bl FUN_02006930
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3f
	str r0, [sp, #0xc]
	mov r1, #2
	ldr r2, [r4, #0x10]
	mov r0, #0x69
	add r3, r1, #0
	bl FUN_020068C8
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_02017CD0
	ldr r0, _0222DD10 ; =0x04000040
	mov r1, #0
	strh r1, [r0]
	add r4, r0, #0
	strh r1, [r0, #4]
	add r4, #8
	ldrh r3, [r4]
	mov r2, #0x3f
	mov r1, #0x1b
	bic r3, r2
	orr r1, r3
	mov r3, #0x20
	orr r1, r3
	strh r1, [r4]
	add r0, #0xa
	ldrh r4, [r0]
	mov r1, #0x1f
	bic r4, r2
	orr r1, r4
	orr r1, r3
	strh r1, [r0]
	lsl r2, r3, #0x15
	ldr r1, [r2]
	ldr r0, _0222DD14 ; =0xFFFF1FFF
	and r1, r0
	lsl r0, r3, #8
	orr r0, r1
	str r0, [r2]
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_0222DCF4: .word MOD69_0222F8CC
_0222DCF8: .word 0x04000304
_0222DCFC: .word 0xFFFF7FFF
_0222DD00: .word MOD69_0222F7C4
_0222DD04: .word MOD69_0222F850
_0222DD08: .word MOD69_0222F818
_0222DD0C: .word MOD69_0222F834
_0222DD10: .word 0x04000040
_0222DD14: .word 0xFFFF1FFF

	thumb_func_start MOD69_0222DD18
MOD69_0222DD18: ; 0x0222DD18
	push {r4, lr}
	mov r2, #1
	lsl r2, r2, #0x1a
	add r4, r0, #0
	ldr r1, [r2]
	ldr r0, _0222DD50 ; =0xFFFF1FFF
	and r0, r1
	str r0, [r2]
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02019178
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #0x10]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #0x10]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #0x10]
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
_0222DD50: .word 0xFFFF1FFF

	thumb_func_start MOD69_0222DD54
MOD69_0222DD54: ; 0x0222DD54
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	bl FUN_020BB7F4
	bl G3X_InitMtxStack
	ldr r0, _0222DDE4 ; =0x04000060
	ldr r2, _0222DDE8 ; =0xFFFFCFFD
	ldrh r1, [r0]
	and r1, r2
	strh r1, [r0]
	ldrh r3, [r0]
	add r1, r2, #2
	and r3, r1
	mov r1, #0x10
	orr r1, r3
	strh r1, [r0]
	ldrh r3, [r0]
	ldr r1, _0222DDEC ; =0x0000CFFB
	and r1, r3
	strh r1, [r0]
	add r1, r2, #2
	ldrh r3, [r0]
	lsr r2, r2, #0x11
	and r3, r1
	mov r1, #8
	orr r1, r3
	strh r1, [r0]
	mov r0, #0
	add r1, r0, #0
	mov r3, #0x3f
	str r0, [sp]
	bl G3X_SetClearColor
	ldr r1, _0222DDF0 ; =0x04000540
	mov r0, #2
	str r0, [r1]
	ldr r0, _0222DDF4 ; =0xBFFF0000
	str r0, [r1, #0x40]
	mov r0, #1
	add r1, r0, #0
	bl FUN_020AEB70
	mov r0, #1
	lsl r0, r0, #0xe
	mov r1, #1
	bl FUN_020AEDF4
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	ldr r0, _0222DDF8 ; =0x04000008
	mov r1, #3
	ldrh r2, [r0]
	bic r2, r1
	mov r1, #2
	orr r1, r2
	strh r1, [r0]
	mov r1, #0
	add r0, #0x48
	mov r2, #0x18
	add r3, r1, #0
	str r1, [sp]
	bl G2x_SetBlendAlpha_
	add r0, r4, #0
	bl MOD69_0222DDFC
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0222DDE4: .word 0x04000060
_0222DDE8: .word 0xFFFFCFFD
_0222DDEC: .word 0x0000CFFB
_0222DDF0: .word 0x04000540
_0222DDF4: .word 0xBFFF0000
_0222DDF8: .word 0x04000008

	thumb_func_start MOD69_0222DDFC
MOD69_0222DDFC: ; 0x0222DDFC
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0
	mov r0, #0x3f
	bl FUN_0201EB64
	ldr r2, _0222DE80 ; =0x00001B1C
	ldr r3, _0222DE84 ; =0x00000FA4
	str r0, [r4, r2]
	mov r0, #0
	add r1, r2, #4
	str r0, [r4, r1]
	add r1, r2, #0
	add r1, #8
	str r0, [r4, r1]
	add r1, r2, #0
	add r1, #0xc
	str r0, [r4, r1]
	add r1, r2, #0
	add r1, #0x10
	strh r0, [r4, r1]
	add r1, r2, #0
	add r1, #0x12
	strh r0, [r4, r1]
	add r1, r2, #0
	add r1, #0x14
	strh r0, [r4, r1]
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4, r2]
	mov r1, #5
	str r0, [sp, #8]
	add r0, r2, #4
	add r2, #0x10
	add r0, r4, r0
	lsl r1, r1, #0xc
	add r2, r4, r2
	bl FUN_0201ECA8
	mov r1, #0
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #0x10]
	str r1, [sp, #0xc]
	str r1, [sp, #0x14]
	ldr r1, _0222DE80 ; =0x00001B1C
	add r0, sp, #0xc
	ldr r1, [r4, r1]
	bl FUN_0201EC58
	ldr r0, _0222DE80 ; =0x00001B1C
	ldr r0, [r4, r0]
	bl FUN_0201EB8C
	ldr r2, _0222DE80 ; =0x00001B1C
	mov r0, #1
	mov r1, #0x7d
	ldr r2, [r4, r2]
	lsl r0, r0, #0xc
	lsl r1, r1, #0xe
	bl FUN_0201EC94
	add sp, #0x18
	pop {r4, pc}
	nop
_0222DE80: .word 0x00001B1C
_0222DE84: .word 0x00000FA4

	thumb_func_start MOD69_0222DE88
MOD69_0222DE88: ; 0x0222DE88
	ldr r1, _0222DE90 ; =0x00001B1C
	ldr r3, _0222DE94 ; =FUN_0201EB70
	ldr r0, [r0, r1]
	bx r3
	.align 2, 0
_0222DE90: .word 0x00001B1C
_0222DE94: .word FUN_0201EB70

	thumb_func_start MOD69_0222DE98
MOD69_0222DE98: ; 0x0222DE98
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r0, #0
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r1, #0x80
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x3f
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	add r1, r4, #0
	mov r0, #0x40
	add r1, #0x28
	mov r2, #0x3f
	bl FUN_02008C9C
	str r0, [r4, #0x24]
	mov r0, #0x3f
	str r0, [sp]
	mov r0, #0x1b
	mov r1, #0x29
	mov r2, #0
	add r3, sp, #0x18
	bl FUN_02006C30
	mov r1, #0x5b
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0x3f
	str r0, [sp]
	mov r0, #0x1b
	mov r1, #0x2a
	mov r2, #0
	add r3, sp, #0x14
	bl FUN_02006C5C
	mov r1, #0x17
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r0, r4, #0
	bl MOD69_0222DF0C
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	add sp, #0x1c
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD69_0222DF0C
MOD69_0222DF0C: ; 0x0222DF0C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xd4
	mov r3, #0
	str r0, [sp, #0x14]
	str r1, [sp, #0xac]
	str r2, [sp, #0xb0]
	str r3, [sp, #0xa4]
	str r3, [sp, #0xb4]
	str r3, [sp, #0xb8]
	str r3, [sp, #0xbc]
	mov r1, #3
	add r0, sp, #0xc0
	strb r1, [r0]
	add r0, sp, #0x5c
	str r0, [sp, #0xa0]
	add r0, sp, #0x48
	str r0, [sp, #0xa8]
	ldr r0, [sp, #0x14]
	mov r1, #0x28
	ldr r0, [r0, #0x24]
	add r2, r3, #0
	str r0, [sp, #0x80]
	add r0, sp, #0xa0
	str r0, [sp, #0x84]
	mov r0, #1
	str r0, [sp, #0x98]
	mov r0, #0x3f
	str r3, [sp, #0x88]
	str r3, [sp, #0x8c]
	str r3, [sp, #0x90]
	str r0, [sp, #0x9c]
	str r0, [sp]
	mov r0, #0x1b
	add r3, sp, #0x44
	bl FUN_02006BB0
	str r0, [sp, #0x28]
	mov r0, #0x1b
	mov r1, #0x27
	add r2, sp, #0x40
	mov r3, #0x3f
	bl FUN_02006C08
	str r0, [sp, #0x24]
	mov r0, #0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x14]
	ldr r0, [r0, #4]
	cmp r0, #0
	bgt _0222DF72
	b _0222E0D4
_0222DF72:
	mov r0, #0x32
	lsl r0, r0, #6
	mov r1, #0x5d
	ldr r5, [sp, #0x14]
	str r0, [sp, #0x1c]
	ldr r7, [sp, #0x20]
	lsl r1, r1, #2
	add r0, r5, #0
	add r0, r0, r1
	str r0, [sp, #0x18]
	add r1, #0xa8
	add r0, r5, #0
	add r4, r0, r1
	ldr r0, [sp, #0x1c]
	add r6, r7, #0
	str r0, [sp, #0x38]
	str r0, [sp, #0x3c]
	str r0, [sp, #0x30]
	str r0, [sp, #0x34]
_0222DF98:
	add r0, sp, #0x5c
	bl FUN_020B1A24
	add r0, sp, #0x48
	bl FUN_020B19DC
	ldr r0, [sp, #0x44]
	add r1, r7, #0
	mov r2, #1
	add r3, sp, #0x5c
	bl FUN_020B1768
	ldr r0, [sp, #0x40]
	add r1, r6, #0
	mov r2, #1
	add r3, sp, #0x48
	bl FUN_020B1240
	ldr r0, [sp, #0x20]
	add r0, r0, #1
	str r0, [sp, #0x94]
	add r0, sp, #0x80
	bl FUN_0201FF84
	mov r1, #0x15
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [sp, #0x14]
	mov r1, #0x7b
	ldr r0, [r0, #0xc]
	lsl r1, r1, #2
	ldr r0, [r0, #4]
	ldr r1, [r5, r1]
	bl GetPartyMonByIndex
	str r0, [sp, #0x2c]
	ldr r1, [sp, #0x2c]
	add r0, sp, #0xc4
	mov r2, #2
	bl FUN_02068B68
	ldr r0, [sp, #0x2c]
	mov r1, #5
	mov r2, #0
	bl GetMonData
	mov r1, #0x81
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r1, #0
	ldr r0, [sp, #0x2c]
	add r2, r1, #0
	bl GetMonData
	str r4, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, sp, #0xc4
	str r0, [sp, #0x10]
	add r0, sp, #0xc4
	ldrh r0, [r0]
	ldrh r1, [r1, #2]
	ldr r3, _0222E198 ; =0x0222F86C
	mov r2, #0x3f
	bl FUN_02012530
	ldr r1, [sp, #0x30]
	add r0, r4, #0
	bl DC_FlushRange
	ldr r2, [sp, #0x34]
	add r0, r4, #0
	add r1, r7, #0
	bl GX_LoadOBJ
	mov r1, #0
	ldr r0, [sp, #0x2c]
	add r2, r1, #0
	bl GetMonData
	str r4, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, sp, #0xc4
	str r0, [sp, #0x10]
	add r0, sp, #0xc4
	ldrh r0, [r0]
	ldrh r1, [r1, #2]
	ldr r3, _0222E19C ; =0x0222F87C
	mov r2, #0x3f
	bl FUN_02012530
	ldr r1, [sp, #0x38]
	add r0, r4, #0
	bl DC_FlushRange
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x3c]
	add r0, r4, #0
	bl GX_LoadOBJ
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x3f
	str r0, [sp, #4]
	add r0, sp, #0xc4
	add r1, sp, #0xc4
	ldrh r0, [r0]
	ldrh r1, [r1, #4]
	mov r2, #1
	add r3, r6, #0
	bl FUN_02006930
	mov r1, #0x81
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	ldr r0, [sp, #0x18]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_02069010
	mov r0, #0x19
	lsl r0, r0, #8
	ldr r1, [sp, #0x1c]
	add r7, r7, r0
	add r0, r1, r0
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r6, #0x20
	add r0, #0x14
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	add r5, r5, #4
	add r0, r0, #1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x14]
	ldr r1, [r0, #4]
	ldr r0, [sp, #0x20]
	cmp r0, r1
	bge _0222E0D4
	b _0222DF98
_0222E0D4:
	add r0, sp, #0x5c
	bl FUN_020B1A24
	add r0, sp, #0x48
	bl FUN_020B19DC
	mov r1, #0x96
	ldr r0, [sp, #0x44]
	lsl r1, r1, #8
	mov r2, #1
	add r3, sp, #0x5c
	bl FUN_020B1768
	ldr r0, [sp, #0x40]
	mov r1, #0xc0
	mov r2, #1
	add r3, sp, #0x48
	bl FUN_020B1240
	ldr r0, [sp, #0x14]
	ldr r0, [r0, #0xc]
	ldr r0, [r0]
	bl FUN_020239CC
	cmp r0, #1
	bne _0222E10C
	mov r1, #1
	b _0222E10E
_0222E10C:
	mov r1, #0
_0222E10E:
	lsl r1, r1, #0x10
	add r0, sp, #0xc4
	lsr r1, r1, #0x10
	bl FUN_020690AC
	mov r1, #0x87
	ldr r0, [sp, #0x14]
	lsl r1, r1, #2
	add r0, r0, r1
	str r0, [sp]
	add r1, sp, #0xc4
	ldrh r0, [r1]
	ldrh r1, [r1, #2]
	ldr r3, _0222E198 ; =0x0222F86C
	mov r2, #0x3f
	bl FUN_02012400
	mov r1, #0x87
	ldr r0, [sp, #0x14]
	lsl r1, r1, #2
	add r0, r0, r1
	mov r1, #0x32
	lsl r1, r1, #6
	bl DC_FlushRange
	mov r1, #0x87
	mov r2, #0x32
	ldr r0, [sp, #0x14]
	lsl r1, r1, #2
	add r0, r0, r1
	mov r1, #0x96
	lsl r1, r1, #8
	lsl r2, r2, #6
	bl GX_LoadOBJ
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x3f
	str r0, [sp, #4]
	add r1, sp, #0xc4
	ldrh r0, [r1]
	ldrh r1, [r1, #4]
	mov r2, #1
	mov r3, #0xc0
	bl FUN_02006930
	mov r0, #0
	str r0, [sp, #0x94]
	add r0, sp, #0x80
	bl FUN_0201FF84
	mov r2, #0x5a
	ldr r1, [sp, #0x14]
	lsl r2, r2, #2
	str r0, [r1, r2]
	add r0, r1, #0
	ldr r0, [r0, r2]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [sp, #0x24]
	bl FreeToHeap
	ldr r0, [sp, #0x28]
	bl FreeToHeap
	add sp, #0xd4
	pop {r4, r5, r6, r7, pc}
	nop
_0222E198: .word MOD69_0222F86C
_0222E19C: .word MOD69_0222F87C

	thumb_func_start MOD69_0222E1A0
MOD69_0222E1A0: ; 0x0222E1A0
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6, #4]
	mov r4, #0
	cmp r0, #0
	ble _0222E1C2
	mov r7, #0x15
	add r5, r6, #0
	lsl r7, r7, #4
_0222E1B2:
	ldr r0, [r5, r7]
	bl FUN_0201FFC8
	ldr r0, [r6, #4]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blt _0222E1B2
_0222E1C2:
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	bl FreeToHeap
	mov r0, #0x5b
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FreeToHeap
	ldr r0, [r6, #0x24]
	bl FUN_0201FD58
	bl FUN_02009FA0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD69_0222E1E4
MOD69_0222E1E4: ; 0x0222E1E4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1, #4]
	mov r2, #0
	str r2, [r0]
	ldr r0, [r1]
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
	pop {r4, pc}

	thumb_func_start MOD69_0222E1FC
MOD69_0222E1FC: ; 0x0222E1FC
	str r1, [r0]
	str r2, [r0, #4]
	bx lr
	.align 2, 0

	thumb_func_start MOD69_0222E204
MOD69_0222E204: ; 0x0222E204
	ldr r3, _0222E210 ; =FUN_0200CA98
	add r1, r0, #0
	ldr r0, _0222E214 ; =MOD69_0222E1E4
	mov r2, #0
	bx r3
	nop
_0222E210: .word FUN_0200CA98
_0222E214: .word MOD69_0222E1E4

	thumb_func_start MOD69_0222E218
MOD69_0222E218: ; 0x0222E218
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x3f
	mov r1, #0x2c
	str r2, [sp]
	bl AllocFromHeap
	mov r1, #0x6d
	lsl r1, r1, #6
	add r4, r6, r1
	ldr r1, [sp]
	add r5, r0, #0
	lsl r1, r1, #2
	str r1, [sp, #4]
	ldr r2, [sp, #4]
	add r1, r5, #0
	add r2, r4, r2
	bl MOD69_0222E1FC
	lsl r0, r7, #2
	add r1, r6, r0
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	ldr r3, _0222E298 ; =0x0222F7A8
	str r0, [r5, #8]
	lsl r0, r7, #0x1f
	lsr r2, r0, #0x1c
	ldr r0, _0222E29C ; =0x0222F7A4
	ldr r6, [r0, r2]
	add r0, r5, #0
	ldr r2, [r3, r2]
	add r0, #0x18
	add r1, r6, #0
	mov r3, #0x1c
	bl MOD69_0222F680
	mov r0, #6
	add r1, r5, #0
	str r6, [r5, #0xc]
	lsl r0, r0, #0x10
	str r0, [r5, #0x10]
	mov r0, #0
	str r0, [r5, #0x14]
	ldr r0, [r5, #8]
	add r1, #0xc
	bl FUN_02020044
	ldr r0, [r5, #8]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, _0222E2A0 ; =MOD69_0222E2A4
	add r1, r5, #0
	mov r2, #0
	bl MOD69_0222DBA4
	ldr r1, [sp, #4]
	str r0, [r4, r1]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E298: .word MOD69_0222F7A8
_0222E29C: .word MOD69_0222F7A4
_0222E2A0: .word MOD69_0222E2A4

	thumb_func_start MOD69_0222E2A4
MOD69_0222E2A4: ; 0x0222E2A4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x18
	bl MOD69_0222F6A0
	str r0, [r4, #0xc]
	add r1, r4, #0
	ldr r0, [r4, #8]
	add r1, #0xc
	bl FUN_02020044
	add r0, r4, #0
	add r0, #0x18
	bl MOD69_0222F6C0
	cmp r0, #0
	beq _0222E2D6
	add r0, r4, #0
	bl MOD69_0222E204
	add r0, r5, #0
	bl FUN_0200CAB4
_0222E2D6:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD69_0222E2D8
MOD69_0222E2D8: ; 0x0222E2D8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x3f
	mov r1, #0x2c
	bl AllocFromHeap
	mov r1, #0x6d
	lsl r1, r1, #6
	add r5, r0, #0
	add r4, r6, r1
	lsl r7, r7, #2
	add r1, r5, #0
	add r2, r4, r7
	bl MOD69_0222E1FC
	mov r0, #0x5a
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	mov r1, #0x3a
	str r0, [r5, #8]
	add r0, r5, #0
	mov r2, #0x1a
	add r0, #0x18
	lsl r1, r1, #0xe
	lsl r2, r2, #0xe
	mov r3, #0x1c
	bl MOD69_0222F680
	mov r0, #2
	lsl r0, r0, #0x12
	str r0, [r5, #0xc]
	mov r0, #0x3a
	lsl r0, r0, #0xe
	str r0, [r5, #0x10]
	mov r0, #0
	str r0, [r5, #0x14]
	add r1, r5, #0
	ldr r0, [r5, #8]
	add r1, #0xc
	bl FUN_02020044
	ldr r0, [r5, #8]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, _0222E344 ; =MOD69_0222E348
	add r1, r5, #0
	mov r2, #0
	bl MOD69_0222DBA4
	str r0, [r4, r7]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E344: .word MOD69_0222E348

	thumb_func_start MOD69_0222E348
MOD69_0222E348: ; 0x0222E348
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x18
	bl MOD69_0222F6A0
	str r0, [r4, #0x10]
	add r1, r4, #0
	ldr r0, [r4, #8]
	add r1, #0xc
	bl FUN_02020044
	add r0, r4, #0
	add r0, #0x18
	bl MOD69_0222F6C0
	cmp r0, #0
	beq _0222E37A
	add r0, r4, #0
	bl MOD69_0222E204
	add r0, r5, #0
	bl FUN_0200CAB4
_0222E37A:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD69_0222E37C
MOD69_0222E37C: ; 0x0222E37C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #8
	bl MOD69_0222F6A0
	asr r0, r0, #0xc
	add r2, r0, #0
	add r2, #0x60
	cmp r0, #0
	bge _0222E396
	mov r0, #0
_0222E396:
	cmp r2, #0
	bge _0222E39C
	mov r2, #0
_0222E39C:
	cmp r0, #0xff
	ble _0222E3A4
	mov r2, #0
	add r0, r2, #0
_0222E3A4:
	cmp r2, #0xff
	ble _0222E3AA
	mov r2, #0xff
_0222E3AA:
	lsl r1, r0, #8
	mov r0, #0xff
	lsl r0, r0, #8
	and r1, r0
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	ldr r1, _0222E3DC ; =0x04000040
	strh r0, [r1]
	ldr r0, _0222E3E0 ; =0x000020A0
	strh r0, [r1, #4]
	add r0, r4, #0
	add r0, #8
	bl MOD69_0222F6C0
	cmp r0, #0
	beq _0222E3D8
	add r0, r4, #0
	bl MOD69_0222E204
	add r0, r5, #0
	bl FUN_0200CAB4
_0222E3D8:
	pop {r3, r4, r5, pc}
	nop
_0222E3DC: .word 0x04000040
_0222E3E0: .word 0x000020A0

	thumb_func_start MOD69_0222E3E4
MOD69_0222E3E4: ; 0x0222E3E4
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #8
	bl MOD69_0222F6A0
	asr r2, r0, #0xc
	ldr r0, [r4, #0x24]
	add r3, r2, r0
	cmp r2, #0
	bge _0222E3FE
	mov r2, #0
_0222E3FE:
	cmp r3, #0
	bge _0222E404
	mov r3, #0
_0222E404:
	cmp r2, #0xbf
	ble _0222E40C
	mov r3, #0
	add r2, r3, #0
_0222E40C:
	cmp r3, #0xbf
	ble _0222E412
	mov r3, #0xbf
_0222E412:
	ldr r0, [r4, #0x1c]
	ldr r6, [r4, #0x20]
	lsl r1, r0, #8
	mov r0, #0xff
	lsl r0, r0, #8
	lsl r6, r6, #0x18
	lsl r2, r2, #8
	and r1, r0
	lsr r6, r6, #0x18
	orr r6, r1
	ldr r1, _0222E450 ; =0x04000040
	and r2, r0
	lsl r0, r3, #0x18
	lsr r0, r0, #0x18
	strh r6, [r1]
	orr r0, r2
	strh r0, [r1, #4]
	add r0, r4, #0
	add r0, #8
	bl MOD69_0222F6C0
	cmp r0, #0
	beq _0222E44C
	add r0, r4, #0
	bl MOD69_0222E204
	add r0, r5, #0
	bl FUN_0200CAB4
_0222E44C:
	pop {r4, r5, r6, pc}
	nop
_0222E450: .word 0x04000040

	thumb_func_start MOD69_0222E454
MOD69_0222E454: ; 0x0222E454
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	add r0, #8
	bl MOD69_0222F6A0
	asr r4, r0, #0xc
	add r0, r5, #0
	add r0, #0x1c
	bl MOD69_0222F6A0
	asr r2, r0, #0xc
	cmp r4, #0
	bge _0222E474
	mov r4, #0
_0222E474:
	cmp r2, #0
	bge _0222E47A
	mov r2, #0
_0222E47A:
	cmp r4, #0xff
	ble _0222E482
	mov r2, #0
	add r4, r2, #0
_0222E482:
	cmp r2, #0xff
	ble _0222E488
	mov r2, #0xff
_0222E488:
	ldr r0, [r5, #0x30]
	mov r3, #0xff
	lsl r2, r2, #0x18
	ldr r1, [r5, #0x34]
	lsl r4, r4, #8
	lsl r3, r3, #8
	and r4, r3
	lsr r2, r2, #0x18
	lsl r0, r0, #8
	orr r4, r2
	ldr r2, _0222E4C4 ; =0x04000040
	and r3, r0
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	strh r4, [r2]
	orr r0, r3
	strh r0, [r2, #4]
	add r0, r5, #0
	add r0, #8
	bl MOD69_0222F6C0
	cmp r0, #0
	beq _0222E4C2
	add r0, r5, #0
	bl MOD69_0222E204
	add r0, r6, #0
	bl FUN_0200CAB4
_0222E4C2:
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222E4C4: .word 0x04000040

	thumb_func_start MOD69_0222E4C8
MOD69_0222E4C8: ; 0x0222E4C8
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	add r0, #8
	bl MOD69_0222F6A0
	asr r4, r0, #0xc
	add r0, r5, #0
	add r0, #0x1c
	bl MOD69_0222F6A0
	asr r2, r0, #0xc
	cmp r4, #0
	bge _0222E4E8
	mov r4, #0
_0222E4E8:
	cmp r2, #0
	bge _0222E4EE
	mov r2, #0
_0222E4EE:
	cmp r4, #0xbf
	ble _0222E4F6
	mov r2, #0
	add r4, r2, #0
_0222E4F6:
	cmp r2, #0xbf
	ble _0222E4FC
	mov r2, #0xbf
_0222E4FC:
	ldr r0, [r5, #0x30]
	ldr r3, [r5, #0x34]
	lsl r1, r0, #8
	mov r0, #0xff
	lsl r0, r0, #8
	lsl r3, r3, #0x18
	and r1, r0
	lsr r3, r3, #0x18
	orr r3, r1
	ldr r1, _0222E538 ; =0x04000040
	strh r3, [r1]
	lsl r3, r4, #8
	and r3, r0
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	orr r0, r3
	strh r0, [r1, #4]
	add r0, r5, #0
	add r0, #8
	bl MOD69_0222F6C0
	cmp r0, #0
	beq _0222E536
	add r0, r5, #0
	bl MOD69_0222E204
	add r0, r6, #0
	bl FUN_0200CAB4
_0222E536:
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222E538: .word 0x04000040

	thumb_func_start MOD69_0222E53C
MOD69_0222E53C: ; 0x0222E53C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r7, r1, #0
	mov r0, #0x3f
	mov r1, #0x1c
	add r6, r2, #0
	bl AllocFromHeap
	mov r1, #0x6d
	lsl r1, r1, #6
	add r5, r0, #0
	add r4, r4, r1
	lsl r6, r6, #2
	add r1, r5, #0
	add r2, r4, r6
	bl MOD69_0222E1FC
	lsl r0, r7, #0x1f
	lsr r2, r0, #0x1c
	ldr r1, _0222E584 ; =0x0222F7B4
	add r0, r5, #0
	ldr r3, _0222E588 ; =0x0222F7B8
	ldr r1, [r1, r2]
	ldr r2, [r3, r2]
	add r0, #8
	mov r3, #0x1c
	bl MOD69_0222F680
	ldr r0, _0222E58C ; =MOD69_0222E37C
	add r1, r5, #0
	mov r2, #1
	bl MOD69_0222DBA4
	str r0, [r4, r6]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E584: .word MOD69_0222F7B4
_0222E588: .word MOD69_0222F7B8
_0222E58C: .word MOD69_0222E37C

	thumb_func_start MOD69_0222E590
MOD69_0222E590: ; 0x0222E590
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r7, r1, #0
	mov r0, #0x3f
	mov r1, #0x28
	add r6, r2, #0
	bl AllocFromHeap
	mov r1, #0x6d
	lsl r1, r1, #6
	add r5, r0, #0
	add r4, r4, r1
	lsl r6, r6, #2
	add r1, r5, #0
	add r2, r4, r6
	bl MOD69_0222E1FC
	add r0, r5, #0
	mov r1, #2
	ldr r2, _0222E5E4 ; =0xFFF60000
	add r0, #8
	lsl r1, r1, #0x10
	mov r3, #0x1c
	bl MOD69_0222F680
	lsl r0, r7, #0x1f
	lsr r1, r0, #0x1d
	ldr r0, _0222E5E8 ; =0x0222F790
	mov r2, #1
	ldr r0, [r0, r1]
	add r1, r5, #0
	str r0, [r5, #0x1c]
	add r0, #0x60
	str r0, [r5, #0x20]
	mov r0, #0x80
	str r0, [r5, #0x24]
	ldr r0, _0222E5EC ; =MOD69_0222E3E4
	bl MOD69_0222DBA4
	str r0, [r4, r6]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E5E4: .word 0xFFF60000
_0222E5E8: .word MOD69_0222F790
_0222E5EC: .word MOD69_0222E3E4

	thumb_func_start MOD69_0222E5F0
MOD69_0222E5F0: ; 0x0222E5F0
	push {r4, r5, r6, lr}
	add r4, r0, #0
	add r6, r1, #0
	mov r0, #0x3f
	mov r1, #0x28
	bl AllocFromHeap
	mov r1, #0x6d
	lsl r1, r1, #6
	add r5, r0, #0
	add r4, r4, r1
	lsl r6, r6, #2
	add r1, r5, #0
	add r2, r4, r6
	bl MOD69_0222E1FC
	add r0, r5, #0
	mov r2, #6
	ldr r1, _0222E63C ; =0xFFF70000
	add r0, #8
	lsl r2, r2, #0xe
	mov r3, #0x1c
	bl MOD69_0222F680
	mov r0, #0x58
	str r0, [r5, #0x1c]
	mov r0, #0xa8
	str r0, [r5, #0x20]
	mov r0, #0x90
	str r0, [r5, #0x24]
	ldr r0, _0222E640 ; =MOD69_0222E3E4
	add r1, r5, #0
	mov r2, #1
	bl MOD69_0222DBA4
	str r0, [r4, r6]
	pop {r4, r5, r6, pc}
	nop
_0222E63C: .word 0xFFF70000
_0222E640: .word MOD69_0222E3E4

	thumb_func_start MOD69_0222E644
MOD69_0222E644: ; 0x0222E644
	push {r4, r5, r6, lr}
	add r4, r0, #0
	add r6, r1, #0
	mov r0, #0x3f
	mov r1, #0x38
	bl AllocFromHeap
	mov r1, #0x6d
	lsl r1, r1, #6
	add r5, r0, #0
	add r4, r4, r1
	lsl r6, r6, #2
	add r1, r5, #0
	add r2, r4, r6
	bl MOD69_0222E1FC
	add r0, r5, #0
	mov r1, #0x16
	add r0, #8
	lsl r1, r1, #0xe
	mov r2, #0
	mov r3, #0xc
	bl MOD69_0222F680
	add r0, r5, #0
	mov r1, #0x2a
	mov r2, #0xff
	add r0, #0x1c
	lsl r1, r1, #0xe
	lsl r2, r2, #0xc
	mov r3, #0xc
	bl MOD69_0222F680
	mov r0, #0x18
	str r0, [r5, #0x30]
	add r0, #0x90
	str r0, [r5, #0x34]
	ldr r0, _0222E69C ; =MOD69_0222E454
	add r1, r5, #0
	mov r2, #1
	bl MOD69_0222DBA4
	str r0, [r4, r6]
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222E69C: .word MOD69_0222E454

	thumb_func_start MOD69_0222E6A0
MOD69_0222E6A0: ; 0x0222E6A0
	push {r4, r5, r6, lr}
	add r4, r0, #0
	add r6, r1, #0
	mov r0, #0x3f
	mov r1, #0x38
	bl AllocFromHeap
	mov r1, #0x6d
	lsl r1, r1, #6
	add r5, r0, #0
	add r4, r4, r1
	lsl r6, r6, #2
	add r1, r5, #0
	add r2, r4, r6
	bl MOD69_0222E1FC
	mov r1, #6
	add r0, r5, #0
	lsl r1, r1, #0xe
	add r0, #8
	lsl r2, r1, #2
	mov r3, #0x18
	bl MOD69_0222F680
	add r0, r5, #0
	mov r1, #0x2a
	mov r2, #6
	add r0, #0x1c
	lsl r1, r1, #0xe
	lsl r2, r2, #0x10
	mov r3, #0x18
	bl MOD69_0222F680
	mov r0, #0
	str r0, [r5, #0x30]
	mov r0, #0xff
	str r0, [r5, #0x34]
	ldr r0, _0222E6F8 ; =MOD69_0222E4C8
	add r1, r5, #0
	mov r2, #1
	bl MOD69_0222DBA4
	str r0, [r4, r6]
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222E6F8: .word MOD69_0222E4C8

	thumb_func_start MOD69_0222E6FC
MOD69_0222E6FC: ; 0x0222E6FC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x3f
	mov r1, #0x74
	str r2, [sp]
	str r3, [sp, #4]
	bl AllocFromHeap
	mov r1, #0x6d
	lsl r1, r1, #6
	add r7, r5, r1
	ldr r1, [sp, #4]
	add r4, r0, #0
	lsl r1, r1, #2
	str r1, [sp, #0xc]
	ldr r2, [sp, #0xc]
	add r1, r4, #0
	add r2, r7, r2
	bl MOD69_0222E1FC
	lsl r0, r6, #2
	str r0, [sp, #8]
	add r1, r5, r0
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r1, [r1, r0]
	add r0, #0x24
	str r1, [r4, #8]
	add r1, r5, r0
	mov r0, #0x14
	mul r0, r6
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0x10
	str r1, [r4, #0xc]
	bl FUN_02008010
	ldr r0, [sp]
	str r0, [r4, #0x6c]
	ldr r0, [sp, #8]
	add r1, r5, r0
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	str r0, [r4, #0x70]
	ldr r0, [r4, #8]
	bl FUN_02020350
	add r3, r4, #0
	add r5, r0, #0
	add r3, #0x24
	mov r2, #4
_0222E768:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222E768
	ldr r0, [r5]
	add r5, r4, #0
	str r0, [r3]
	add r3, r4, #0
	add r5, #0x24
	add r3, #0x48
	mov r2, #4
_0222E77E:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222E77E
	ldr r0, [r5]
	str r0, [r3]
	add r0, r4, #0
	add r0, #0x48
	bl FUN_020B1A24
	mov r3, #0x19
	add r0, r4, #0
	lsl r3, r3, #8
	add r2, r6, #0
	mul r2, r3
	lsr r3, r3, #1
	add r0, #0x48
	mov r1, #1
	add r2, r2, r3
	bl FUN_020B1A1C
	ldr r0, _0222E7BC ; =MOD69_0222E7C0
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
	ldr r1, [sp, #0xc]
	str r0, [r7, r1]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E7BC: .word MOD69_0222E7C0

	thumb_func_start MOD69_0222E7C0
MOD69_0222E7C0: ; 0x0222E7C0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x6c]
	cmp r0, #0
	beq _0222E7DA
	ldr r0, [r4, #0x70]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02005578
	mov r0, #0
	str r0, [r4, #0x6c]
_0222E7DA:
	add r0, r4, #0
	add r0, #0x10
	bl FUN_02008030
	add r2, r0, #0
	bmi _0222E7F6
	mov r1, #0x24
	ldr r0, [r4, #8]
	add r4, #0x24
	mul r1, r2
	add r1, r4, r1
	bl FUN_02020334
	pop {r3, r4, r5, pc}
_0222E7F6:
	add r0, r4, #0
	bl MOD69_0222E204
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}

	thumb_func_start MOD69_0222E804
MOD69_0222E804: ; 0x0222E804
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r7, r1, #0
	mov r0, #0x3f
	mov r1, #0x38
	str r2, [sp]
	bl AllocFromHeap
	mov r1, #0x6d
	lsl r1, r1, #6
	add r6, r5, r1
	ldr r1, [sp]
	add r4, r0, #0
	lsl r1, r1, #2
	str r1, [sp, #4]
	ldr r2, [sp, #4]
	add r1, r4, #0
	add r2, r6, r2
	bl MOD69_0222E1FC
	str r5, [r4, #8]
	ldr r0, [r5, #0x10]
	ldr r1, _0222E894 ; =0x00001B50
	str r0, [r4, #0xc]
	add r0, r5, #0
	add r0, #0x14
	str r0, [r4, #0x10]
	ldr r0, [r5, r1]
	str r0, [r4, #0x14]
	add r0, r1, #4
	ldr r0, [r5, r0]
	str r0, [r4, #0x18]
	add r0, r1, #0
	add r0, #8
	ldr r0, [r5, r0]
	add r1, #0xc
	str r0, [r4, #0x1c]
	ldr r0, [r5, r1]
	str r0, [r4, #0x20]
	mov r0, #1
	tst r0, r7
	beq _0222E85E
	mov r0, #0
	b _0222E860
_0222E85E:
	mov r0, #0x78
_0222E860:
	lsl r1, r7, #2
	str r0, [r4, #0x2c]
	ldr r0, [r5, #0xc]
	add r2, r5, r1
	mov r1, #0x7b
	lsl r1, r1, #2
	ldr r0, [r0, #4]
	ldr r1, [r2, r1]
	bl GetPartyMonByIndex
	str r0, [r4, #0x24]
	ldr r0, [r5, #0xc]
	mov r2, #0
	ldr r0, [r0]
	add r1, r4, #0
	str r0, [r4, #0x28]
	str r2, [r4, #0x30]
	ldr r0, _0222E898 ; =MOD69_0222E9AC
	str r2, [r4, #0x34]
	bl FUN_0200CA44
	ldr r1, [sp, #4]
	str r0, [r6, r1]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E894: .word 0x00001B50
_0222E898: .word MOD69_0222E9AC

	thumb_func_start MOD69_0222E89C
MOD69_0222E89C: ; 0x0222E89C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x1c]
	add r4, r1, #0
	bl FUN_02021D5C
	mov r6, #0
	str r0, [sp, #0x10]
	cmp r0, #0
	ble _0222E8F2
_0222E8B2:
	ldr r0, [r5, #0x18]
	ldr r1, [r5, #0x1c]
	add r2, r6, #0
	bl FUN_02021D9C
	mov r0, #0
	ldr r1, [r5, #0x18]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0x88
	sub r0, r1, r0
	lsr r7, r0, #1
	str r4, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0222E8F8 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r3, [r5, #0x2c]
	ldr r0, [r5, #0x10]
	ldr r2, [r5, #0x18]
	add r3, r3, r7
	bl FUN_0201BDE0
	ldr r0, [sp, #0x10]
	add r6, r6, #1
	add r4, #0x10
	cmp r6, r0
	blt _0222E8B2
_0222E8F2:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0222E8F8: .word 0x00010200

	thumb_func_start MOD69_0222E8FC
MOD69_0222E8FC: ; 0x0222E8FC
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0x24]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl FUN_0200AC60
	ldr r0, [r4, #0x24]
	bl CalcMonLevel
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r0, [r4, #0x14]
	mov r3, #3
	bl FUN_0200AD38
	ldr r0, [r4, #0x24]
	bl GetMonGender
	cmp r0, #0
	beq _0222E93C
	cmp r0, #1
	beq _0222E948
	cmp r0, #2
	b _0222E954
_0222E93C:
	ldr r0, [r4, #0x20]
	ldr r2, [r4, #0x18]
	mov r1, #1
	bl ReadMsgDataIntoString
	b _0222E95E
_0222E948:
	ldr r0, [r4, #0x20]
	ldr r2, [r4, #0x18]
	mov r1, #2
	bl ReadMsgDataIntoString
	b _0222E95E
_0222E954:
	ldr r0, [r4, #0x20]
	ldr r2, [r4, #0x18]
	mov r1, #3
	bl ReadMsgDataIntoString
_0222E95E:
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #0x1c]
	ldr r2, [r4, #0x18]
	bl StringExpandPlaceholders
	add sp, #8
	pop {r4, pc}

	thumb_func_start MOD69_0222E96C
MOD69_0222E96C: ; 0x0222E96C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #8]
	ldr r1, [r5, #0x24]
	ldr r2, [r5, #0x28]
	bl MOD69_0222F6C4
	add r4, r0, #0
	beq _0222E982
	cmp r4, #1
	bne _0222E996
_0222E982:
	ldr r0, [r5, #0x24]
	mov r1, #0x98
	mov r2, #0
	bl GetMonData
	add r2, r0, #0
	ldr r0, [r5, #0x14]
	mov r1, #0
	bl FUN_0200AFF4
_0222E996:
	ldr r0, [r5, #0x20]
	ldr r2, [r5, #0x18]
	add r1, r4, #5
	bl ReadMsgDataIntoString
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x1c]
	ldr r2, [r5, #0x18]
	bl StringExpandPlaceholders
	pop {r3, r4, r5, pc}

	thumb_func_start MOD69_0222E9AC
MOD69_0222E9AC: ; 0x0222E9AC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x30]
	cmp r0, #0
	beq _0222E9BE
	sub r0, r0, #1
	str r0, [r4, #0x30]
	pop {r3, r4, r5, pc}
_0222E9BE:
	ldr r0, [r4, #0x34]
	cmp r0, #3
	bhi _0222EA82
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222E9D0: ; jump table
	.short _0222E9D8 - _0222E9D0 - 2 ; case 0
	.short _0222E9FC - _0222E9D0 - 2 ; case 1
	.short _0222EA2E - _0222E9D0 - 2 ; case 2
	.short _0222EA76 - _0222E9D0 - 2 ; case 3
_0222E9D8:
	ldr r0, [r4, #0x20]
	ldr r2, [r4, #0x1c]
	mov r1, #0
	bl ReadMsgDataIntoString
	add r0, r4, #0
	mov r1, #0x18
	bl MOD69_0222E89C
	ldr r0, [r4, #0x10]
	bl FUN_02019548
	mov r0, #0x14
	str r0, [r4, #0x30]
	ldr r0, [r4, #0x34]
	add r0, r0, #1
	str r0, [r4, #0x34]
	pop {r3, r4, r5, pc}
_0222E9FC:
	ldr r0, [r4, #0x24]
	ldr r2, [r4, #0x1c]
	mov r1, #0x76
	bl GetMonData
	add r0, r4, #0
	mov r1, #0x48
	bl MOD69_0222E89C
	add r0, r4, #0
	bl MOD69_0222E8FC
	add r0, r4, #0
	mov r1, #0x58
	bl MOD69_0222E89C
	ldr r0, [r4, #0x10]
	bl FUN_02019548
	mov r0, #0x14
	str r0, [r4, #0x30]
	ldr r0, [r4, #0x34]
	add r0, r0, #1
	str r0, [r4, #0x34]
	pop {r3, r4, r5, pc}
_0222EA2E:
	ldr r0, [r4, #0x24]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl FUN_0200AD18
	ldr r0, [r4, #0x20]
	ldr r2, [r4, #0x18]
	mov r1, #4
	bl ReadMsgDataIntoString
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #0x1c]
	ldr r2, [r4, #0x18]
	bl StringExpandPlaceholders
	add r0, r4, #0
	mov r1, #0x78
	bl MOD69_0222E89C
	add r0, r4, #0
	bl MOD69_0222E96C
	add r0, r4, #0
	mov r1, #0x88
	bl MOD69_0222E89C
	ldr r0, [r4, #0x10]
	bl FUN_02019548
	ldr r0, [r4, #0x34]
	add r0, r0, #1
	str r0, [r4, #0x34]
	pop {r3, r4, r5, pc}
_0222EA76:
	add r0, r4, #0
	bl MOD69_0222E204
	add r0, r5, #0
	bl FUN_0200CAB4
_0222EA82:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD69_0222EA84
MOD69_0222EA84: ; 0x0222EA84
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	mov r0, #0x3f
	mov r1, #0x30
	bl AllocFromHeap
	mov r1, #0x6d
	lsl r1, r1, #6
	add r4, r0, #0
	add r6, r5, r1
	lsl r7, r7, #2
	add r1, r4, #0
	add r2, r6, r7
	bl MOD69_0222E1FC
	ldr r0, [r5, #0x10]
	add r5, #0x14
	str r0, [r4, #0xc]
	add r0, r4, #0
	str r5, [r4, #0x10]
	mov r2, #1
	str r2, [r4, #0x2c]
	mov r1, #0
	add r0, #0x14
	lsl r2, r2, #0x14
	mov r3, #0x1c
	str r1, [r4, #0x28]
	bl MOD69_0222F680
	ldr r0, _0222EAD0 ; =MOD69_0222EAD4
	add r1, r4, #0
	mov r2, #0
	bl MOD69_0222DBA4
	str r0, [r6, r7]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222EAD0: .word MOD69_0222EAD4

	thumb_func_start MOD69_0222EAD4
MOD69_0222EAD4: ; 0x0222EAD4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x28]
	cmp r0, #0
	beq _0222EAEA
	cmp r0, #1
	beq _0222EB16
	cmp r0, #2
	beq _0222EB2C
	pop {r3, r4, r5, pc}
_0222EAEA:
	add r0, r4, #0
	add r0, #0x14
	bl MOD69_0222F6A0
	ldr r1, [r4, #0x2c]
	asr r3, r0, #0xc
	lsl r1, r1, #0x18
	ldr r0, [r4, #0xc]
	lsr r1, r1, #0x18
	mov r2, #3
	bl FUN_020179E0
	add r0, r4, #0
	add r0, #0x14
	bl MOD69_0222F6C0
	cmp r0, #0
	beq _0222EB48
	ldr r0, [r4, #0x28]
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r3, r4, r5, pc}
_0222EB16:
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl FUN_02019620
	ldr r0, [r4, #0x10]
	bl FUN_02019548
	ldr r0, [r4, #0x28]
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r3, r4, r5, pc}
_0222EB2C:
	ldr r1, [r4, #0x2c]
	ldr r0, [r4, #0xc]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	add r0, r4, #0
	bl MOD69_0222E204
	add r0, r5, #0
	bl FUN_0200CAB4
_0222EB48:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD69_0222EB4C
MOD69_0222EB4C: ; 0x0222EB4C
	push {r4, lr}
	sub sp, #0x10
	ldr r2, _0222EC50 ; =0x00001B5C
	add r4, r0, #0
	ldr r0, [r4, r2]
	sub r2, #8
	ldr r2, [r4, r2]
	mov r1, #0xc
	bl ReadMsgDataIntoString
	ldr r1, _0222EC54 ; =0x00001B54
	mov r0, #0
	ldr r1, [r4, r1]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #1
	lsl r1, r1, #8
	sub r0, r1, r0
	lsr r3, r0, #1
	mov r0, #4
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0222EC58 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r4, #0
	ldr r2, _0222EC54 ; =0x00001B54
	str r1, [sp, #0xc]
	ldr r2, [r4, r2]
	add r0, #0x14
	bl FUN_0201BDE0
	ldr r0, _0222EC5C ; =0x00001B50
	ldr r2, [r4, #0xc]
	ldr r0, [r4, r0]
	ldr r2, [r2]
	mov r1, #0
	bl FUN_0200ABC0
	ldr r0, [r4, #0xc]
	ldr r0, [r0]
	bl FUN_020239C0
	add r2, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r1, #1
	ldr r0, _0222EC5C ; =0x00001B50
	str r1, [sp, #4]
	ldr r0, [r4, r0]
	mov r3, #5
	bl FUN_0200AD38
	ldr r0, [r4, #0xc]
	ldr r0, [r0, #8]
	bl FUN_02029EBC
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _0222EC5C ; =0x00001B50
	mov r1, #2
	ldr r0, [r4, r0]
	mov r3, #3
	bl FUN_0200AD38
	ldr r0, [r4, #0xc]
	ldr r0, [r0, #8]
	bl FUN_02029EC0
	mov r3, #2
	add r2, r0, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _0222EC5C ; =0x00001B50
	mov r1, #3
	ldr r0, [r4, r0]
	bl FUN_0200AD38
	ldr r2, _0222EC50 ; =0x00001B5C
	mov r1, #0xd
	ldr r0, [r4, r2]
	sub r2, r2, #4
	ldr r2, [r4, r2]
	bl ReadMsgDataIntoString
	ldr r2, _0222EC5C ; =0x00001B50
	add r1, r2, #4
	ldr r0, [r4, r2]
	add r2, #8
	ldr r1, [r4, r1]
	ldr r2, [r4, r2]
	bl StringExpandPlaceholders
	ldr r1, _0222EC54 ; =0x00001B54
	mov r0, #0
	ldr r1, [r4, r1]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #1
	lsl r1, r1, #8
	sub r0, r1, r0
	lsr r3, r0, #1
	mov r0, #0xac
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0222EC58 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r4, #0
	ldr r2, _0222EC54 ; =0x00001B54
	str r1, [sp, #0xc]
	ldr r2, [r4, r2]
	add r0, #0x14
	bl FUN_0201BDE0
	add r4, #0x14
	add r0, r4, #0
	bl FUN_02019548
	add sp, #0x10
	pop {r4, pc}
	nop
_0222EC50: .word 0x00001B5C
_0222EC54: .word 0x00001B54
_0222EC58: .word 0x00010200
_0222EC5C: .word 0x00001B50

	thumb_func_start MOD69_0222EC60
MOD69_0222EC60: ; 0x0222EC60
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x3f
	mov r1, #0xdc
	bl AllocFromHeap
	mov r1, #0x6d
	lsl r1, r1, #6
	add r1, r5, r1
	str r1, [sp, #0xc]
	lsl r1, r6, #2
	str r1, [sp, #0x10]
	add r4, r0, #0
	ldr r3, [sp, #0xc]
	ldr r2, [sp, #0x10]
	add r1, r4, #0
	add r2, r3, r2
	bl MOD69_0222E1FC
	mov r0, #0x15
	lsl r0, r0, #4
	str r5, [r4, #0xc]
	add r0, r5, r0
	str r0, [r4, #8]
	mov r0, #0
	str r0, [r4, #0x10]
	str r0, [sp, #8]
	str r0, [r4, #0x18]
	ldr r0, [r5, #4]
	str r0, [r4, #0x14]
	cmp r0, #0
	ble _0222ECE8
	ldr r0, _0222ED24 ; =0x0222F8F4
	ldr r5, [sp, #8]
	str r0, [sp, #4]
	add r7, r4, #0
	add r6, r0, #0
_0222ECAE:
	ldr r3, [sp, #4]
	add r2, r7, #0
	ldmia r3!, {r0, r1}
	add r2, #0x94
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, r6, #0
	str r0, [r2]
	ldr r0, [r4, #8]
	ldr r0, [r0, r5]
	bl FUN_02020044
	ldr r0, [r4, #8]
	mov r1, #1
	ldr r0, [r0, r5]
	bl FUN_020200A0
	ldr r0, [sp, #4]
	ldr r1, [r4, #0x14]
	add r0, #0xc
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	add r7, #0xc
	add r0, r0, #1
	add r6, #0xc
	add r5, r5, #4
	str r0, [sp, #8]
	cmp r0, r1
	blt _0222ECAE
_0222ECE8:
	mov r0, #0
	add r7, r4, #0
	ldr r6, _0222ED28 ; =0x0222F7E8
	ldr r5, _0222ED24 ; =0x0222F8F4
	str r0, [sp]
	add r7, #0x1c
_0222ECF4:
	ldr r1, [r5]
	ldr r2, [r6]
	add r0, r7, #0
	mov r3, #8
	bl MOD69_0222F680
	ldr r0, [sp]
	add r6, r6, #4
	add r0, r0, #1
	add r5, #0xc
	add r7, #0x14
	str r0, [sp]
	cmp r0, #6
	blt _0222ECF4
	ldr r0, _0222ED2C ; =MOD69_0222ED30
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
	ldr r2, [sp, #0xc]
	ldr r1, [sp, #0x10]
	str r0, [r2, r1]
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0222ED24: .word MOD69_0222F8F4
_0222ED28: .word MOD69_0222F7E8
_0222ED2C: .word MOD69_0222ED30

	thumb_func_start MOD69_0222ED30
MOD69_0222ED30: ; 0x0222ED30
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r1, [r5, #0x10]
	mov r4, #0
	str r0, [sp]
	cmp r1, #0
	ble _0222ED84
	add r0, r5, #0
	str r0, [sp, #8]
	add r0, #0x1c
	add r7, r5, #0
	str r0, [sp, #8]
	str r5, [sp, #4]
	add r7, #0x94
	add r6, r4, #0
_0222ED50:
	ldr r0, [sp, #8]
	bl MOD69_0222F6A0
	ldr r1, [sp, #4]
	add r1, #0x94
	str r0, [r1]
	ldr r0, [r5, #0x14]
	cmp r4, r0
	bge _0222ED6C
	ldr r0, [r5, #8]
	add r1, r7, #0
	ldr r0, [r0, r6]
	bl FUN_02020044
_0222ED6C:
	ldr r0, [sp, #8]
	ldr r1, [r5, #0x10]
	add r0, #0x14
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	add r4, r4, #1
	add r0, #0xc
	str r0, [sp, #4]
	add r7, #0xc
	add r6, r6, #4
	cmp r4, r1
	blt _0222ED50
_0222ED84:
	ldr r0, [r5, #0x18]
	cmp r0, #0
	beq _0222ED92
	sub r0, r0, #1
	add sp, #0xc
	str r0, [r5, #0x18]
	pop {r4, r5, r6, r7, pc}
_0222ED92:
	cmp r1, #6
	bge _0222EDA4
	mov r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r5, #0x10]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r5, #0x10]
	pop {r4, r5, r6, r7, pc}
_0222EDA4:
	ldr r0, [r5, #0x14]
	add r2, r5, #0
	sub r1, r0, #1
	mov r0, #0x14
	add r2, #0x1c
	mul r0, r1
	add r0, r2, r0
	bl MOD69_0222F6C0
	cmp r0, #0
	beq _0222EDC6
	add r0, r5, #0
	bl MOD69_0222E204
	ldr r0, [sp]
	bl FUN_0200CAB4
_0222EDC6:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD69_0222EDCC
MOD69_0222EDCC: ; 0x0222EDCC
	push {r3, r4, r5, lr}
	ldr r1, _0222EE10 ; =0x00000844
	add r5, r0, #0
	mov r0, #0x3f
	bl AllocFromHeap
	add r4, r0, #0
	beq _0222EE0C
	ldr r0, _0222EE14 ; =0x0222F940
	mov r1, #1
	str r1, [r0]
	ldr r0, _0222EE18 ; =0x0222F960
	mov r1, #2
	str r1, [r0, #4]
	ldr r0, _0222EE1C ; =0x0000083C
	mov r1, #0
	str r1, [r4, r0]
	ldr r0, _0222EE20 ; =MOD69_0222EE80
	add r1, r4, #0
	mov r2, #5
	bl MOD69_0222DBA4
	ldr r1, _0222EE24 ; =0x00000838
	mov r2, #3
	str r0, [r4, r1]
	add r1, #8
	str r5, [r4, r1]
	ldr r0, _0222EE28 ; =MOD69_0222EE2C
	add r1, r4, #0
	bl MOD69_0222DBA4
	pop {r3, r4, r5, pc}
_0222EE0C:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222EE10: .word 0x00000844
_0222EE14: .word MOD69_0222F940
_0222EE18: .word MOD69_0222F960
_0222EE1C: .word 0x0000083C
_0222EE20: .word MOD69_0222EE80
_0222EE24: .word 0x00000838
_0222EE28: .word MOD69_0222EE2C

	thumb_func_start MOD69_0222EE2C
MOD69_0222EE2C: ; 0x0222EE2C
	push {r4, lr}
	add r4, r1, #0
	ldr r1, _0222EE70 ; =0x0222F940
	ldr r1, [r1]
	cmp r1, #0
	beq _0222EE60
	add r1, r4, #0
	mov r2, #2
	add r0, r4, #0
	add r1, #0x14
	lsl r2, r2, #0xa
	bl G3_BeginMakeDL
	ldr r1, _0222EE74 ; =0x00007FFF
	ldr r2, _0222EE78 ; =0x00004210
	add r0, r4, #0
	mov r3, #0
	bl G3B_MaterialColorDiffAmb
	mov r2, #0
	ldr r1, _0222EE78 ; =0x00004210
	add r0, r4, #0
	add r3, r2, #0
	bl G3B_MaterialColorSpecEmi
	pop {r4, pc}
_0222EE60:
	ldr r1, _0222EE7C ; =0x0222F960
	ldr r2, [r1, #4]
	sub r2, r2, #1
	str r2, [r1, #4]
	bl FUN_0200CAB4
	pop {r4, pc}
	nop
_0222EE70: .word MOD69_0222F940
_0222EE74: .word 0x00007FFF
_0222EE78: .word 0x00004210
_0222EE7C: .word MOD69_0222F960

	thumb_func_start MOD69_0222EE80
MOD69_0222EE80: ; 0x0222EE80
	push {r4, lr}
	add r4, r1, #0
	ldr r1, _0222EEB0 ; =0x0222F940
	ldr r1, [r1]
	cmp r1, #0
	beq _0222EEA2
	add r0, r4, #0
	bl G3_EndMakeDL
	ldr r1, _0222EEB4 ; =0x00000814
	str r0, [r4, r1]
	add r0, r4, #0
	ldr r1, [r4, r1]
	add r0, #0x14
	bl DC_FlushRange
	pop {r4, pc}
_0222EEA2:
	ldr r1, _0222EEB8 ; =0x0222F960
	ldr r2, [r1, #4]
	sub r2, r2, #1
	str r2, [r1, #4]
	bl FUN_0200CAB4
	pop {r4, pc}
	.align 2, 0
_0222EEB0: .word MOD69_0222F940
_0222EEB4: .word 0x00000814
_0222EEB8: .word MOD69_0222F960

	thumb_func_start MOD69_0222EEBC
MOD69_0222EEBC: ; 0x0222EEBC
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r2, #0
	bl FUN_0201B6C8
	ldr r1, _0222EEF8 ; =0x0000083C
	add r4, r0, #0
	ldr r3, [r4, r1]
	cmp r3, #8
	bge _0222EEF4
	add r1, r5, #0
	add r2, r6, #0
	bl MOD69_0222EF00
	ldr r2, _0222EEF8 ; =0x0000083C
	ldr r1, [r4, r2]
	lsl r1, r1, #2
	add r3, r4, r1
	add r1, r2, #0
	sub r1, #0x24
	str r0, [r3, r1]
	ldr r0, _0222EEFC ; =0x0222F960
	ldr r1, [r0, #4]
	add r1, r1, #1
	str r1, [r0, #4]
	ldr r0, [r4, r2]
	add r0, r0, #1
	str r0, [r4, r2]
_0222EEF4:
	pop {r4, r5, r6, pc}
	nop
_0222EEF8: .word 0x0000083C
_0222EEFC: .word MOD69_0222F960

	thumb_func_start MOD69_0222EF00
MOD69_0222EF00: ; 0x0222EF00
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r6, r0, #0
	ldr r1, _0222EF78 ; =0x00000838
	mov r0, #0x3f
	add r7, r2, #0
	add r4, r3, #0
	bl AllocFromHeap
	add r1, r0, #0
	beq _0222EF74
	ldr r0, _0222EF7C ; =0x00000818
	ldr r2, _0222EF80 ; =0x0222F88C
	str r6, [r1]
	lsl r3, r4, #2
	ldr r3, [r2, r3]
	add r2, r0, #0
	strh r5, [r1, r0]
	sub r2, #8
	str r3, [r1, r2]
	add r2, r0, #0
	mov r3, #0
	sub r2, #0x14
	str r3, [r1, r2]
	add r2, r0, #0
	sub r2, #0x10
	str r7, [r1, r2]
	ldr r2, _0222EF84 ; =0x0222F798
	lsl r6, r4, #1
	ldrsh r6, [r2, r6]
	add r2, r0, #0
	sub r2, #0xc
	str r6, [r1, r2]
	sub r2, r0, #4
	str r4, [r1, r2]
	add r4, r5, #0
	sub r4, #0x50
	add r2, r0, #2
	strh r4, [r1, r2]
	ldr r2, _0222EF88 ; =0xFFFFF000
	add r4, r0, #4
	strh r2, [r1, r4]
	add r4, r0, #6
	strh r3, [r1, r4]
	add r4, r0, #0
	add r5, #0x50
	add r4, #8
	strh r5, [r1, r4]
	add r4, r0, #0
	add r4, #0xa
	strh r2, [r1, r4]
	add r0, #0xc
	strh r3, [r1, r0]
	ldr r0, _0222EF8C ; =MOD69_0222EF90
	mov r2, #4
	bl MOD69_0222DBA4
	pop {r3, r4, r5, r6, r7, pc}
_0222EF74:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222EF78: .word 0x00000838
_0222EF7C: .word 0x00000818
_0222EF80: .word MOD69_0222F88C
_0222EF84: .word MOD69_0222F798
_0222EF88: .word 0xFFFFF000
_0222EF8C: .word MOD69_0222EF90

	thumb_func_start MOD69_0222EF90
MOD69_0222EF90: ; 0x0222EF90
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r1, _0222F0FC ; =0x0222F940
	ldr r1, [r1]
	cmp r1, #0
	bne _0222EFA0
	b _0222F0EC
_0222EFA0:
	ldr r0, _0222F100 ; =0x00000808
	add r1, r0, #4
	ldr r2, [r5, r0]
	ldr r1, [r5, r1]
	add r1, r2, r1
	str r1, [r5, r0]
	add r1, r0, #4
	ldr r1, [r5, r1]
	ldr r2, [r5, r0]
	cmp r1, #0
	ble _0222EFCE
	mov r1, #0xaa
	lsl r1, r1, #0xc
	cmp r2, r1
	blt _0222EFE4
	add r1, r0, #4
	ldr r2, [r5, r1]
	mov r1, #0
	mvn r1, r1
	mul r1, r2
	add r0, r0, #4
	str r1, [r5, r0]
	b _0222EFE4
_0222EFCE:
	mov r1, #0xa
	lsl r1, r1, #0xc
	cmp r2, r1
	bgt _0222EFE4
	add r1, r0, #4
	ldr r2, [r5, r1]
	mov r1, #0
	mvn r1, r1
	mul r1, r2
	add r0, r0, #4
	str r1, [r5, r0]
_0222EFE4:
	ldr r0, _0222F100 ; =0x00000808
	mov r2, #0xa
	ldr r0, [r5, r0]
	lsl r2, r2, #0xa
	asr r6, r0, #0xc
	add r0, r6, #0
	add r0, #0x5a
	lsl r1, r0, #2
	ldr r0, _0222F104 ; =0x020EDF50
	mov r3, #0
	ldr r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	ldr r4, _0222F108 ; =0x00000818
	mov r3, #0
	ldrsh r2, [r5, r4]
	sub r4, #0x18
	add r4, r0, r4
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r4, #0xc
	orr r1, r0
	add r4, r2, r1
	mov r2, #0xa
	ldr r0, _0222F104 ; =0x020EDF50
	lsl r1, r6, #2
	ldr r0, [r0, r1]
	lsl r2, r2, #0xa
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r6, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r6, #0xc
	orr r1, r0
	lsl r0, r2, #1
	mov r7, #9
	sub r6, r1, r0
	lsl r7, r7, #6
	add r0, r2, #0
	sub r1, r4, r7
	add r0, #0x26
	strh r1, [r5, r0]
	lsl r0, r6, #0x10
	add r1, r2, #0
	asr r0, r0, #0x10
	add r1, #0x28
	strh r0, [r5, r1]
	add r1, r2, #0
	add r1, #0x2a
	strh r3, [r5, r1]
	add r1, r2, #0
	add r4, r4, r7
	add r1, #0x2c
	strh r4, [r5, r1]
	add r1, r2, #0
	add r1, #0x2e
	strh r0, [r5, r1]
	add r0, r2, #0
	add r0, #0x30
	add r2, #0x14
	strh r3, [r5, r0]
	ldr r0, [r5, r2]
	add r1, r3, #0
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	str r3, [sp, #8]
	add r2, r3, #0
	ldr r0, [r5]
	mov r3, #2
	bl G3B_PolygonAttr
	ldr r0, [r5]
	mov r1, #1
	bl G3B_Begin
	mov r1, #0x81
	lsl r1, r1, #4
	ldr r1, [r5, r1]
	ldr r0, [r5]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl G3B_Color
	ldr r3, _0222F10C ; =0x0000081A
	ldr r0, [r5]
	add r2, r3, #2
	ldrsh r1, [r5, r3]
	add r3, r3, #4
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	bl G3B_Vtx
	mov r3, #0x82
	lsl r3, r3, #4
	add r2, r3, #2
	ldrsh r1, [r5, r3]
	add r3, r3, #4
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	ldr r0, [r5]
	bl G3B_Vtx
	ldr r3, _0222F110 ; =0x0000082C
	ldr r0, [r5]
	add r2, r3, #2
	ldrsh r1, [r5, r3]
	add r3, r3, #4
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	bl G3B_Vtx
	ldr r3, _0222F114 ; =0x00000826
	ldr r0, [r5]
	add r2, r3, #2
	ldrsh r1, [r5, r3]
	add r3, r3, #4
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	bl G3B_Vtx
	ldr r0, [r5]
	bl G3B_End
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0222F0EC:
	ldr r1, _0222F118 ; =0x0222F960
	ldr r2, [r1, #4]
	sub r2, r2, #1
	str r2, [r1, #4]
	bl FUN_0200CAB4
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0222F0FC: .word MOD69_0222F940
_0222F100: .word 0x00000808
_0222F104: .word 0x020EDF50
_0222F108: .word 0x00000818
_0222F10C: .word 0x0000081A
_0222F110: .word 0x0000082C
_0222F114: .word 0x00000826
_0222F118: .word MOD69_0222F960

	thumb_func_start MOD69_0222F11C
MOD69_0222F11C: ; 0x0222F11C
	push {r3, lr}
	cmp r0, #0
	beq _0222F142
	bl FUN_0201B6C8
	add r3, r0, #0
	ldr r0, _0222F144 ; =0x04000444
	mov r1, #0
	str r1, [r0]
	ldr r2, _0222F148 ; =0x00000814
	add r1, r3, #0
	ldr r2, [r3, r2]
	mov r0, #3
	add r1, #0x14
	bl MI_SendGXCommand
	ldr r0, _0222F14C ; =0x04000448
	mov r1, #1
	str r1, [r0]
_0222F142:
	pop {r3, pc}
	.align 2, 0
_0222F144: .word 0x04000444
_0222F148: .word 0x00000814
_0222F14C: .word 0x04000448

	thumb_func_start MOD69_0222F150
MOD69_0222F150: ; 0x0222F150
	push {r3, r4, r5, r6, r7, lr}
	ldr r1, _0222F190 ; =0x0222F940
	mov r2, #0
	str r2, [r1]
	cmp r0, #0
	beq _0222F18C
	bl FUN_0201B6C8
	add r6, r0, #0
	ldr r0, _0222F194 ; =0x0000083C
	mov r4, #0
	ldr r0, [r6, r0]
	cmp r0, #0
	ble _0222F186
	ldr r7, _0222F194 ; =0x0000083C
	add r5, r6, #0
_0222F170:
	ldr r0, _0222F198 ; =0x00000818
	ldr r0, [r5, r0]
	bl FUN_0201B6C8
	bl FreeToHeap
	ldr r0, [r6, r7]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blt _0222F170
_0222F186:
	add r0, r6, #0
	bl FreeToHeap
_0222F18C:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222F190: .word MOD69_0222F940
_0222F194: .word 0x0000083C
_0222F198: .word 0x00000818

	thumb_func_start MOD69_0222F19C
MOD69_0222F19C: ; 0x0222F19C
	ldr r0, _0222F1AC ; =0x0222F960
	ldr r0, [r0, #4]
	cmp r0, #0
	bne _0222F1A8
	mov r0, #1
	bx lr
_0222F1A8:
	mov r0, #0
	bx lr
	.align 2, 0
_0222F1AC: .word MOD69_0222F960

	thumb_func_start MOD69_0222F1B0
MOD69_0222F1B0: ; 0x0222F1B0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	ldr r1, _0222F344 ; =0x00008D64
	mov r0, #0x3f
	bl AllocFromHeap
	str r0, [sp, #0x28]
	bl LCRandom
	str r0, [sp, #0x20]
	ldr r0, _0222F348 ; =0x00003594
	bl SetLCRNGSeed
	mov r0, #0
	ldr r4, [sp, #0x28]
	str r0, [sp, #0x24]
	str r0, [sp, #0x1c]
	add r0, r4, #0
	str r0, [sp, #0x18]
	add r0, #0x34
	str r0, [sp, #0x18]
	add r0, r4, #0
	str r0, [sp, #0x14]
	add r0, #0x28
	str r0, [sp, #0x14]
	add r0, r4, #0
	str r0, [sp, #0x10]
	add r0, #0x2e
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	str r0, [sp, #0xc]
_0222F1EE:
	ldr r0, [sp, #0x1c]
	lsl r1, r0, #2
	ldr r0, _0222F34C ; =0x0222F8AC
	ldr r0, [r0, r1]
	str r0, [r4, #8]
	ldr r0, [sp, #0x1c]
	add r0, r0, #1
	str r0, [sp, #0x1c]
	cmp r0, #8
	blo _0222F206
	mov r0, #0
	str r0, [sp, #0x1c]
_0222F206:
	bl LCRandom
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x13
	sub r1, r1, r2
	mov r0, #0x13
	ror r1, r0
	mov r0, #1
	add r1, r2, r1
	lsl r0, r0, #0xc
	sub r0, r1, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #8]
	bl LCRandom
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x13
	sub r1, r1, r2
	mov r0, #0x13
	ror r1, r0
	mov r0, #1
	add r1, r2, r1
	lsl r0, r0, #0xc
	add r0, r1, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #4]
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	mov r0, #0x52
	lsl r0, r0, #2
	sub r0, r1, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	ldr r5, _0222F350 ; =0x0222F800
	str r0, [sp]
	mov r7, #0
	add r6, r4, #0
_0222F25C:
	mov r0, #0
	ldrsh r1, [r5, r0]
	ldr r0, [sp, #8]
	add r0, r0, r1
	strh r0, [r6, #0x10]
	mov r0, #2
	ldrsh r1, [r5, r0]
	ldr r0, [sp, #4]
	add r0, r0, r1
	strh r0, [r6, #0x12]
	mov r0, #4
	ldrsh r1, [r5, r0]
	ldr r0, [sp]
	add r0, r0, r1
	strh r0, [r6, #0x14]
	mov r0, #0
	strh r0, [r4, #0x28]
	strh r0, [r4, #0x2a]
	strh r0, [r4, #0x2c]
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r2, r0, #0x17
	sub r2, r2, r1
	mov r0, #0x17
	ror r2, r0
	mov r0, #2
	add r1, r1, r2
	lsl r0, r0, #8
	add r0, r1, r0
	strh r0, [r4, #0x2e]
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r2, r0, #0x17
	sub r2, r2, r1
	mov r0, #0x17
	ror r2, r0
	mov r0, #2
	add r1, r1, r2
	lsl r0, r0, #8
	add r0, r1, r0
	strh r0, [r4, #0x30]
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r2, r0, #0x17
	sub r2, r2, r1
	mov r0, #0x17
	ror r2, r0
	mov r0, #2
	add r1, r1, r2
	lsl r0, r0, #8
	add r0, r1, r0
	strh r0, [r4, #0x32]
	ldr r0, [sp, #0x18]
	bl MTX_Identity44_
	add r7, r7, #1
	add r5, r5, #6
	add r6, r6, #6
	cmp r7, #4
	blt _0222F25C
	bl LCRandom
	mov r1, #7
	and r0, r1
	sub r5, r0, #1
	cmp r0, #0
	beq _0222F2FA
_0222F2E8:
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0x14]
	bl VEC_Fx16Add
	add r0, r5, #0
	sub r5, r5, #1
	cmp r0, #0
	bne _0222F2E8
_0222F2FA:
	ldr r0, [sp, #0x18]
	add r4, #0x70
	add r0, #0x70
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	add r0, #0x70
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	add r0, #0x70
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xc]
	add r0, #0x70
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x24]
	add r0, r0, #1
	str r0, [sp, #0x24]
	cmp r0, #0x30
	bge _0222F320
	b _0222F1EE
_0222F320:
	ldr r0, [sp, #0x20]
	bl SetLCRNGSeed
	ldr r0, [sp, #0x28]
	mov r2, #0
	str r2, [r0]
	ldr r1, _0222F354 ; =0x00008D20
	str r2, [r0, #4]
	str r2, [r0, r1]
	ldr r0, _0222F358 ; =0x04000440
	mov r2, #2
	str r2, [r0]
	ldr r0, _0222F35C ; =MOD69_0222F388
	ldr r1, [sp, #0x28]
	bl FUN_0200CA44
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0222F344: .word 0x00008D64
_0222F348: .word 0x00003594
_0222F34C: .word MOD69_0222F8AC
_0222F350: .word MOD69_0222F800
_0222F354: .word 0x00008D20
_0222F358: .word 0x04000440
_0222F35C: .word MOD69_0222F388

	thumb_func_start MOD69_0222F360
MOD69_0222F360: ; 0x0222F360
	push {r4, lr}
	add r4, r0, #0
	beq _0222F374
	bl FUN_0201B6C8
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
_0222F374:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD69_0222F378
MOD69_0222F378: ; 0x0222F378
	push {r3, lr}
	cmp r0, #0
	beq _0222F386
	bl FUN_0201B6C8
	mov r1, #1
	str r1, [r0]
_0222F386:
	pop {r3, pc}

	thumb_func_start MOD69_0222F388
MOD69_0222F388: ; 0x0222F388
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x68
	add r7, r1, #0
	ldr r0, [r7]
	cmp r0, #0
	bne _0222F396
	b _0222F60C
_0222F396:
	ldr r1, _0222F610 ; =0x00001508
	mov r2, #0x1e
	add r0, r7, r1
	add r1, #0x14
	add r1, r7, r1
	lsl r2, r2, #0xa
	bl G3_BeginMakeDL
	mov r0, #0x3f
	str r0, [sp]
	mov r0, #0x1f
	str r0, [sp, #4]
	ldr r0, _0222F610 ; =0x00001508
	mov r1, #3
	mov r2, #0
	add r0, r7, r0
	add r3, r1, #0
	str r2, [sp, #8]
	bl G3B_PolygonAttr
	ldr r0, _0222F610 ; =0x00001508
	mov r2, #0
	ldr r1, _0222F614 ; =0x00005294
	add r0, r7, r0
	add r3, r2, #0
	bl G3B_MaterialColorDiffAmb
	mov r0, #0
	str r0, [sp, #0x1c]
	add r0, r7, #0
	str r0, [sp, #0x18]
	add r0, #0x28
	str r0, [sp, #0x18]
	add r0, r7, #0
	str r0, [sp, #0x14]
	add r0, #0x2e
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x18]
	add r5, r7, #0
	str r5, [sp, #0xc]
	add r5, #0x34
	add r4, r7, #0
	str r0, [sp, #0x10]
	str r5, [sp, #0xc]
_0222F3EE:
	mov r0, #0x24
	ldrsh r0, [r4, r0]
	sub r0, #0x55
	strh r0, [r4, #0x24]
	mov r0, #0x24
	ldrsh r1, [r4, r0]
	ldr r0, _0222F618 ; =0xFFFFF000
	cmp r1, r0
	bgt _0222F408
	mov r0, #2
	lsl r0, r0, #0xc
	add r0, r1, r0
	strh r0, [r4, #0x24]
_0222F408:
	mov r0, #0x24
	ldrsh r1, [r4, r0]
	ldr r0, _0222F61C ; =0x0000019A
	ldr r2, [sp, #0x18]
	sub r0, r1, r0
	strh r0, [r4, #0x12]
	mov r0, #0x12
	ldrsh r0, [r4, r0]
	ldr r1, [sp, #0x14]
	strh r0, [r4, #0x18]
	mov r0, #0x24
	ldrsh r0, [r4, r0]
	strh r0, [r4, #0x1e]
	ldr r0, [sp, #0x10]
	bl VEC_Fx16Add
	ldr r0, [sp, #0xc]
	bl MTX_Identity44_
	mov r0, #0x14
	ldrsh r0, [r4, r0]
	mov r2, #0x10
	mov r3, #0x12
	str r0, [sp]
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	bl MTX_TransApply44
	ldr r0, _0222F610 ; =0x00001508
	ldr r2, _0222F620 ; =0x00002D6B
	add r0, r7, r0
	mov r1, #0
	bl G3B_LightColor
	ldr r2, [r4, #8]
	ldr r0, _0222F610 ; =0x00001508
	lsl r2, r2, #0x10
	add r0, r7, r0
	mov r1, #1
	lsr r2, r2, #0x10
	bl G3B_LightColor
	mov r1, #0
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, _0222F624 ; =0x00000FFF
	strh r1, [r0, #2]
	ldr r1, _0222F628 ; =0xFFFFF001
	strh r1, [r0, #4]
	add r0, sp, #0x20
	add r1, r0, #0
	bl VEC_Fx16Normalize
	add r3, sp, #0x20
	add r1, sp, #0x20
	mov r0, #4
	ldrsh r0, [r1, r0]
	mov r1, #0
	add r2, r1, #0
	str r0, [sp]
	ldr r0, _0222F610 ; =0x00001508
	ldrsh r2, [r3, r2]
	add r6, r3, #0
	mov r3, #2
	ldrsh r3, [r6, r3]
	add r0, r7, r0
	bl G3B_LightVector
	mov r1, #0
	add r0, r6, #0
	strh r1, [r0]
	ldr r1, _0222F628 ; =0xFFFFF001
	strh r1, [r0, #2]
	lsr r1, r1, #0x14
	strh r1, [r0, #4]
	add r0, sp, #0x20
	add r1, r0, #0
	bl VEC_Fx16Normalize
	add r1, r6, #0
	mov r0, #4
	ldrsh r0, [r1, r0]
	add r3, r6, #0
	mov r2, #0
	str r0, [sp]
	ldrsh r2, [r3, r2]
	mov r3, #2
	ldr r0, _0222F610 ; =0x00001508
	ldrsh r3, [r6, r3]
	add r0, r7, r0
	mov r1, #1
	bl G3B_LightVector
	ldrh r0, [r4, #0x28]
	ldr r3, _0222F62C ; =0x020FFA38
	asr r0, r0, #4
	lsl r1, r0, #2
	ldr r0, _0222F62C ; =0x020FFA38
	add r2, r0, r1
	ldrsh r1, [r3, r1]
	mov r3, #2
	ldrsh r2, [r2, r3]
	add r0, sp, #0x28
	bl MTX_RotX44_
	ldr r2, [sp, #0xc]
	add r0, sp, #0x28
	add r1, r5, #0
	bl MTX_Concat44
	ldrh r0, [r4, #0x2a]
	ldr r3, _0222F62C ; =0x020FFA38
	asr r0, r0, #4
	lsl r1, r0, #2
	ldr r0, _0222F62C ; =0x020FFA38
	add r2, r0, r1
	ldrsh r1, [r3, r1]
	mov r3, #2
	ldrsh r2, [r2, r3]
	add r0, sp, #0x28
	bl MTX_RotY44_
	ldr r2, [sp, #0xc]
	add r0, sp, #0x28
	add r1, r5, #0
	bl MTX_Concat44
	ldrh r0, [r4, #0x2c]
	ldr r3, _0222F62C ; =0x020FFA38
	asr r0, r0, #4
	lsl r1, r0, #2
	ldr r0, _0222F62C ; =0x020FFA38
	add r2, r0, r1
	ldrsh r1, [r3, r1]
	mov r3, #2
	ldrsh r2, [r2, r3]
	add r0, sp, #0x28
	bl MTX_RotZ44_
	ldr r2, [sp, #0xc]
	add r0, sp, #0x28
	add r1, r5, #0
	bl MTX_Concat44
	ldr r2, [r4, #8]
	ldr r0, _0222F610 ; =0x00001508
	lsl r2, r2, #0x10
	ldr r1, _0222F630 ; =0x00007FFF
	add r0, r7, r0
	lsr r2, r2, #0x10
	mov r3, #0
	bl G3B_MaterialColorSpecEmi
	ldr r0, _0222F610 ; =0x00001508
	add r0, r7, r0
	bl G3B_PushMtx
	ldr r0, _0222F610 ; =0x00001508
	add r1, r5, #0
	add r0, r7, r0
	bl G3B_LoadMtx44
	ldr r0, _0222F610 ; =0x00001508
	mov r1, #1
	add r0, r7, r0
	bl G3B_Begin
	ldr r0, _0222F610 ; =0x00001508
	mov r1, #0
	ldr r3, _0222F628 ; =0xFFFFF001
	add r0, r7, r0
	add r2, r1, #0
	bl G3B_Normal
	mov r1, #0x9b
	ldr r0, _0222F610 ; =0x00001508
	mvn r1, r1
	add r2, r1, #0
	add r0, r7, r0
	sub r2, #0x31
	mov r3, #0
	bl G3B_Vtx
	ldr r0, _0222F610 ; =0x00001508
	mov r2, #0xcc
	add r0, r7, r0
	mov r1, #0x9c
	mvn r2, r2
	mov r3, #0
	bl G3B_Vtx
	ldr r0, _0222F610 ; =0x00001508
	mov r1, #0x9c
	add r0, r7, r0
	mov r2, #0xcd
	mov r3, #0
	bl G3B_Vtx
	ldr r0, _0222F610 ; =0x00001508
	mov r1, #0x9b
	add r0, r7, r0
	mvn r1, r1
	mov r2, #0xcd
	mov r3, #0
	bl G3B_Vtx
	ldr r0, _0222F610 ; =0x00001508
	add r0, r7, r0
	bl G3B_End
	ldr r0, _0222F610 ; =0x00001508
	mov r1, #1
	add r0, r7, r0
	bl G3B_PopMtx
	ldr r0, [sp, #0x18]
	add r4, #0x70
	add r0, #0x70
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	add r5, #0x70
	add r0, #0x70
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	add r0, #0x70
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xc]
	add r0, #0x70
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x1c]
	add r0, r0, #1
	str r0, [sp, #0x1c]
	cmp r0, #0x30
	bge _0222F5E2
	b _0222F3EE
_0222F5E2:
	ldr r0, _0222F610 ; =0x00001508
	add r0, r7, r0
	bl G3_EndMakeDL
	ldr r1, _0222F634 ; =0x00008D1C
	str r0, [r7, r1]
	ldr r0, _0222F638 ; =0x0000151C
	ldr r1, [r7, r1]
	add r0, r7, r0
	bl DC_FlushRange
	ldr r0, _0222F634 ; =0x00008D1C
	ldr r1, [r7, r0]
	mov r0, #0x1e
	lsl r0, r0, #0xa
	cmp r1, r0
	blo _0222F608
	bl ErrorHandling
_0222F608:
	mov r0, #1
	str r0, [r7, #4]
_0222F60C:
	add sp, #0x68
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222F610: .word 0x00001508
_0222F614: .word 0x00005294
_0222F618: .word 0xFFFFF000
_0222F61C: .word 0x0000019A
_0222F620: .word 0x00002D6B
_0222F624: .word 0x00000FFF
_0222F628: .word 0xFFFFF001
_0222F62C: .word 0x020FFA38
_0222F630: .word 0x00007FFF
_0222F634: .word 0x00008D1C
_0222F638: .word 0x0000151C

	thumb_func_start MOD69_0222F63C
MOD69_0222F63C: ; 0x0222F63C
	push {r4, lr}
	cmp r0, #0
	beq _0222F66C
	bl FUN_0201B6C8
	add r4, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _0222F66C
	ldr r0, _0222F670 ; =0x04000444
	mov r1, #0
	str r1, [r0]
	ldr r2, _0222F674 ; =0x00008D1C
	ldr r1, _0222F678 ; =0x0000151C
	ldr r2, [r4, r2]
	mov r0, #3
	add r1, r4, r1
	bl MI_SendGXCommand
	ldr r0, _0222F67C ; =0x04000448
	mov r1, #1
	str r1, [r0]
	mov r0, #0
	str r0, [r4, #4]
_0222F66C:
	pop {r4, pc}
	nop
_0222F670: .word 0x04000444
_0222F674: .word 0x00008D1C
_0222F678: .word 0x0000151C
_0222F67C: .word 0x04000448

	thumb_func_start MOD69_0222F680
MOD69_0222F680: ; 0x0222F680
	push {r3, r4, r5, lr}
	add r4, r0, #0
	str r1, [r4]
	add r5, r3, #0
	sub r0, r2, r1
	add r1, r5, #0
	str r2, [r4, #8]
	bl _s32_div_f
	str r0, [r4, #4]
	sub r0, r5, #1
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD69_0222F6A0
MOD69_0222F6A0: ; 0x0222F6A0
	ldr r1, [r0, #0xc]
	cmp r1, #0
	beq _0222F6B6
	sub r1, r1, #1
	str r1, [r0, #0xc]
	ldr r2, [r0]
	ldr r1, [r0, #4]
	add r1, r2, r1
	str r1, [r0]
	add r0, r1, #0
	bx lr
_0222F6B6:
	mov r1, #1
	str r1, [r0, #0x10]
	ldr r0, [r0, #8]
	bx lr
	.align 2, 0

	thumb_func_start MOD69_0222F6C0
MOD69_0222F6C0: ; 0x0222F6C0
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start MOD69_0222F6C4
MOD69_0222F6C4: ; 0x0222F6C4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r6, r2, #0
	bl AcquireMonLock
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0x79
	mov r2, #0
	bl GetMonData
	sub r1, r0, #1
	cmp r1, #2
	bhi _0222F6E8
	mov r5, #4
	b _0222F77A
_0222F6E8:
	sub r1, r0, #4
	cmp r1, #1
	bhi _0222F6F2
	mov r5, #3
	b _0222F77A
_0222F6F2:
	cmp r0, #0xf
	bne _0222F6FA
	mov r5, #5
	b _0222F77A
_0222F6FA:
	add r0, r4, #0
	mov r1, #0x6e
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _0222F70C
	mov r5, #6
	b _0222F77A
_0222F70C:
	add r0, r6, #0
	bl FUN_020239BC
	add r7, r0, #0
	add r0, r4, #0
	mov r1, #7
	mov r2, #0
	bl GetMonData
	cmp r7, r0
	beq _0222F726
	mov r5, #2
	b _0222F77A
_0222F726:
	ldr r1, _0222F788 ; =0x00001B54
	add r0, r6, #0
	ldr r1, [r5, r1]
	bl FUN_02023990
	ldr r2, _0222F78C ; =0x00001B58
	add r0, r4, #0
	ldr r2, [r5, r2]
	mov r1, #0x90
	bl GetMonData
	ldr r1, _0222F788 ; =0x00001B54
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl FUN_02021CE0
	cmp r0, #0
	beq _0222F750
	mov r5, #2
	b _0222F77A
_0222F750:
	add r0, r4, #0
	mov r1, #0x98
	mov r2, #0
	bl GetMonData
	mov r1, #0x7d
	lsl r1, r1, #4
	cmp r0, r1
	blo _0222F766
	mov r5, #6
	b _0222F77A
_0222F766:
	add r0, r4, #0
	mov r1, #0x92
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222F778
	mov r5, #0
	b _0222F77A
_0222F778:
	mov r5, #1
_0222F77A:
	ldr r1, [sp]
	add r0, r4, #0
	bl ReleaseMonLock
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222F788: .word 0x00001B54
_0222F78C: .word 0x00001B58

	.rodata
	.global MOD69_0222F790
MOD69_0222F790: ; 0x0222F790
	.byte 0x18, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00

	.global MOD69_0222F798
MOD69_0222F798: ; 0x0222F798
	.byte 0x00, 0x0C, 0x00, 0x0B, 0x00, 0x0A, 0x00, 0x0C, 0x00, 0x0B, 0x00, 0x0A

	.global MOD69_0222F7A4
MOD69_0222F7A4: ; 0x0222F7A4
	.byte 0x00, 0x00, 0x0C, 0x00

	.global MOD69_0222F7A8
MOD69_0222F7A8: ; 0x0222F7A8
	.byte 0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x80, 0x0B, 0x00

	.global MOD69_0222F7B4
MOD69_0222F7B4: ; 0x0222F7B4
	.byte 0x00, 0x00, 0xFA, 0xFF

	.global MOD69_0222F7B8
MOD69_0222F7B8: ; 0x0222F7B8
	.byte 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x80, 0x08, 0x00

	.global MOD69_0222F7C4
MOD69_0222F7C4: ; 0x0222F7C4
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD69_0222F7D4
MOD69_0222F7D4: ; 0x0222F7D4
	.byte 0x29, 0xD8, 0x22, 0x02, 0xC5, 0xD8, 0x22, 0x02, 0xD5, 0xD9, 0x22, 0x02, 0xE5, 0xDA, 0x22, 0x02
	.byte 0x6D, 0xD8, 0x22, 0x02

	.global MOD69_0222F7E8
MOD69_0222F7E8: ; 0x0222F7E8
	.byte 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x04, 0x00
	.byte 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x02, 0x00

	.global MOD69_0222F800
MOD69_0222F800: ; 0x0222F800
	.byte 0x64, 0xFF, 0x33, 0xFF, 0x00, 0x00, 0x9C, 0x00, 0x33, 0xFF, 0x00, 0x00, 0x9C, 0x00, 0xCD, 0x00
	.byte 0x00, 0x00, 0x64, 0xFF, 0xCD, 0x00, 0x00, 0x00

	.global MOD69_0222F818
MOD69_0222F818: ; 0x0222F818
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD69_0222F834
MOD69_0222F834: ; 0x0222F834
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x06, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD69_0222F850
MOD69_0222F850: ; 0x0222F850
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x1C, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD69_0222F86C
MOD69_0222F86C: ; 0x0222F86C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00

	.global MOD69_0222F87C
MOD69_0222F87C: ; 0x0222F87C
	.byte 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00

	.global MOD69_0222F88C
MOD69_0222F88C: ; 0x0222F88C
	.byte 0xFF, 0x33, 0x00, 0x00, 0xFF, 0x43, 0x00, 0x00, 0x9F, 0x23, 0x00, 0x00, 0xFF, 0x33, 0x00, 0x00
	.byte 0xFF, 0x43, 0x00, 0x00, 0x9F, 0x23, 0x00, 0x00, 0xFF, 0x33, 0x00, 0x00, 0xFF, 0x33, 0x00, 0x00

	.global MOD69_0222F8AC
MOD69_0222F8AC: ; 0x0222F8AC
	.byte 0x90, 0x57, 0x00, 0x00, 0x1F, 0x76, 0x00, 0x00, 0x08, 0x7D, 0x00, 0x00, 0xE6, 0x7F, 0x00, 0x00
	.byte 0xFF, 0x03, 0x00, 0x00, 0xE9, 0x03, 0x00, 0x00, 0x5F, 0x02, 0x00, 0x00, 0x16, 0x7C, 0x00, 0x00

	.global MOD69_0222F8CC
MOD69_0222F8CC: ; 0x0222F8CC
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global MOD69_0222F8F4
MOD69_0222F8F4: ; 0x0222F8F4
	.byte 0x00, 0x80, 0xFD, 0xFF, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x12, 0x00
	.byte 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFD, 0xFF, 0x00, 0x80, 0x05, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x12, 0x00, 0x00, 0x80, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x80, 0xFD, 0xFF, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x12, 0x00
	.byte 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00

	.data
	.global MOD69_0222F940
MOD69_0222F940: ; 0x0222F940
	.word 0x00000001

	.bss
	.global MOD69_0222F960
MOD69_0222F960: ; 0x0222F960
	.space 0x20

