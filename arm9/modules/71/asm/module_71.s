	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD71_0222D5C0
MOD71_0222D5C0: ; 0x0222D5C0
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	bl FUN_02015F1C
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _0222D72C ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _0222D730 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	ldr r2, _0222D734 ; =0x000707D0
	mov r0, #3
	mov r1, #0x1a
	bl FUN_0201681C
	ldr r1, _0222D738 ; =0x000036B4
	add r0, r5, #0
	mov r2, #0x1a
	bl FUN_02006268
	add r4, r0, #0
	ldr r2, _0222D738 ; =0x000036B4
	mov r0, #0
	add r1, r4, #0
	bl MIi_CpuClearFast
	mov r0, #0x1a
	bl FUN_02016B94
	mov r1, #0x5d
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0xc
	mov r1, #0x16
	mov r2, #0x1a
	bl FUN_0200AA90
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0x1a
	bl FUN_0200AA80
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0x1a
	bl FUN_0200AA80
	mov r2, #6
	lsl r2, r2, #6
	str r0, [r4, r2]
	mov r1, #0x1a
	mov r0, #0
	sub r2, #0x44
	add r3, r1, #0
	bl NewMsgDataFromNarc
	mov r1, #0x61
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0
	str r0, [r4, #0x40]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD71_0222E76C
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	bl MOD71_0222E558
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD71_0222E578
	mov r0, #0x10
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x1a
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	add r0, r4, #0
	bl MOD71_0222E900
	ldr r0, _0222D73C ; =MOD71_0222E4DC
	add r1, r4, #0
	bl FUN_02015F10
	bl MOD71_0222EA38
	add r0, r4, #0
	bl MOD71_0222EA68
	add r0, r4, #0
	bl MOD71_0222EF90
	mov r0, #0x5d
	ldr r2, [r4, #8]
	lsl r0, r0, #2
	ldr r1, _0222D740 ; =0x00000438
	ldr r0, [r4, r0]
	ldr r2, [r2, #0x18]
	add r1, r4, r1
	bl MOD71_02230C48
	ldr r0, [r4, #8]
	add r1, r4, #0
	ldr r0, [r0]
	str r0, [r4]
	bl FUN_02083D10
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _0222D744 ; =0x000005A8
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0x14
	mov r2, #1
	bl MOD71_02230F40
	ldr r0, [r4]
	bl FUN_02083B84
	mov r0, #0
	mov r1, #1
	bl FUN_0201797C
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r1, #0x5d
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	mov r0, #0x1a
	bl FUN_020335F0
	bl FUN_02033E74
	bl IsNighttime
	cmp r0, #0
	bne _0222D71A
	ldr r1, _0222D748 ; =0x0000043D
	mov r0, #4
	mov r2, #1
	bl FUN_0200433C
	b _0222D724
_0222D71A:
	ldr r1, _0222D74C ; =0x0000043E
	mov r0, #4
	mov r2, #1
	bl FUN_0200433C
_0222D724:
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0222D72C: .word 0xFFFFE0FF
_0222D730: .word 0x04001000
_0222D734: .word 0x000707D0
_0222D738: .word 0x000036B4
_0222D73C: .word MOD71_0222E4DC
_0222D740: .word 0x00000438
_0222D744: .word 0x000005A8
_0222D748: .word 0x0000043D
_0222D74C: .word 0x0000043E
	thumb_func_end MOD71_0222D5C0

	thumb_func_start MOD71_0222D750
MOD71_0222D750: ; 0x0222D750
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldr r1, [sp, #0x10]
	add r4, r2, #0
	lsl r1, r1, #4
	add r1, #0x92
	mov r2, #2
	ldr r0, [r0, #0x14]
	add r6, r3, #0
	lsl r1, r1, #5
	lsl r2, r2, #8
	bl GX_LoadOBJ
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl FUN_0206B7BC
	add r1, r0, #0
	ldr r0, [sp, #0x14]
	add r1, #0xa
	bl FUN_020202A8
	pop {r4, r5, r6, pc}
	thumb_func_end MOD71_0222D750

	thumb_func_start MOD71_0222D780
MOD71_0222D780: ; 0x0222D780
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	bl FUN_02031190
	bl FUN_0202DFA4
	add r4, r0, #0
	bl FUN_02031190
	mov r1, #1
	eor r0, r1
	bl FUN_0202DFA4
	add r6, r0, #0
	add r0, r4, #0
	mov r1, #0x1a
	bl FUN_020239A0
	add r4, r0, #0
	add r0, r6, #0
	mov r1, #0x1a
	bl FUN_020239A0
	add r6, r0, #0
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x30
	bl NewString_ReadMsgData
	add r7, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0222D814 ; =0x00000438
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0xa
	mov r3, #0
	bl MOD71_02230EFC
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0222D818 ; =0x00000448
	add r1, r6, #0
	add r0, r5, r0
	mov r2, #0xa
	mov r3, #0
	bl MOD71_02230EFC
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0222D81C ; =0x00000498
	add r1, r7, #0
	add r0, r5, r0
	mov r2, #5
	mov r3, #0
	bl MOD71_02230EFC
	add r0, r7, #0
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	add r0, r4, #0
	bl String_dtor
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222D814: .word 0x00000438
_0222D818: .word 0x00000448
_0222D81C: .word 0x00000498
	thumb_func_end MOD71_0222D780

	thumb_func_start MOD71_0222D820
MOD71_0222D820: ; 0x0222D820
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	bl MOD71_0222E558
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD71_0222E578
	add r0, r4, #0
	bl MOD71_0222E900
	add r0, r4, #0
	bl MOD71_0222D93C
	add r0, r4, #0
	bl MOD71_0222D780
	ldr r0, [r4, #8]
	ldr r0, [r0, #0x18]
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r2, #0x5d
	str r0, [sp]
	mov r0, #0x1a
	lsl r2, r2, #2
	str r0, [sp, #4]
	ldr r0, [r4, r2]
	mov r1, #0
	add r2, #0x65
	mov r3, #0xa
	bl FUN_0200CD68
	mov r1, #0
	mov r2, #0x5d
	str r1, [sp]
	mov r0, #0x1a
	lsl r2, r2, #2
	str r0, [sp, #4]
	ldr r0, [r4, r2]
	add r2, #0x83
	mov r3, #0xb
	bl FUN_0200CB00
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _0222D92C ; =0x00000588
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0xf
	mov r2, #1
	bl MOD71_02230F40
	mov r0, #4
	mov r1, #1
	bl FUN_0201797C
	mov r0, #5
	mov r1, #1
	bl FUN_0201797C
	mov r0, #6
	mov r1, #1
	bl FUN_0201797C
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	mov r0, #0
	mov r1, #1
	bl FUN_0201797C
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201797C
	mov r0, #2
	mov r1, #1
	bl FUN_0201797C
	mov r0, #3
	mov r1, #1
	bl FUN_0201797C
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	bl MOD71_0222EA38
	add r0, r4, #0
	bl MOD71_0222EA68
	add r0, r4, #0
	bl MOD71_0222EF90
	ldr r0, _0222D930 ; =0x00002218
	mov r1, #0
	ldr r0, [r4, r0]
	add r2, r4, #0
	bl MOD71_0222DBEC
	ldr r0, _0222D934 ; =0x0000221C
	mov r1, #6
	ldr r0, [r4, r0]
	add r2, r4, #0
	bl MOD71_0222DBEC
	mov r0, #0xce
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0xcf
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, _0222D938 ; =MOD71_0222E4DC
	add r1, r4, #0
	bl FUN_02015F10
	add sp, #8
	pop {r4, pc}
	nop
_0222D92C: .word 0x00000588
_0222D930: .word 0x00002218
_0222D934: .word 0x0000221C
_0222D938: .word MOD71_0222E4DC
	thumb_func_end MOD71_0222D820

	thumb_func_start MOD71_0222D93C
MOD71_0222D93C: ; 0x0222D93C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5e
	ldr r1, _0222D9B8 ; =0x00002218
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	mov r2, #0
	bl MOD71_0222DB5C
	mov r0, #0x5e
	ldr r1, _0222D9BC ; =0x0000221C
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	mov r2, #6
	bl MOD71_0222DB5C
	mov r0, #0
	mov r2, #0x5e
	str r0, [sp]
	lsl r2, r2, #2
	ldr r3, _0222D9B8 ; =0x00002218
	ldr r0, _0222D9C0 ; =0x000004A8
	ldr r1, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	ldr r3, [r5, r3]
	add r0, r5, r0
	bl MOD71_0222DB94
	mov r0, #6
	mov r2, #0x5e
	str r0, [sp]
	lsl r2, r2, #2
	ldr r3, _0222D9BC ; =0x0000221C
	ldr r0, _0222D9C4 ; =0x00000508
	ldr r1, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	ldr r3, [r5, r3]
	add r0, r5, r0
	bl MOD71_0222DB94
	ldr r0, _0222D9B8 ; =0x00002218
	ldr r0, [r5, r0]
	bl GetPartyCount
	add r4, r0, #0
	ldr r0, _0222D9BC ; =0x0000221C
	ldr r0, [r5, r0]
	bl GetPartyCount
	add r2, r0, #0
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl MOD71_0222E8DC
	pop {r3, r4, r5, pc}
	nop
_0222D9B8: .word 0x00002218
_0222D9BC: .word 0x0000221C
_0222D9C0: .word 0x000004A8
_0222D9C4: .word 0x00000508
	thumb_func_end MOD71_0222D93C

	thumb_func_start MOD71_0222D9C8
MOD71_0222D9C8: ; 0x0222D9C8
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	bl FUN_02006278
	ldr r1, [r5]
	add r4, r0, #0
	mov r6, #0
	cmp r1, #0
	beq _0222D9E8
	cmp r1, #1
	beq _0222D9FC
	cmp r1, #2
	bne _0222D9E6
	b _0222DB28
_0222D9E6:
	b _0222DB32
_0222D9E8:
	bl FUN_0200E308
	cmp r0, #0
	beq _0222DA02
	mov r0, #1
	str r0, [r5]
	add r0, r4, #0
	bl MOD71_0222D780
	b _0222DB32
_0222D9FC:
	ldr r1, [r4, #0x48]
	cmp r1, #7
	bls _0222DA04
_0222DA02:
	b _0222DB32
_0222DA04:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222DA10: ; jump table
	.short _0222DA20 - _0222DA10 - 2 ; case 0
	.short _0222DA28 - _0222DA10 - 2 ; case 1
	.short _0222DA36 - _0222DA10 - 2 ; case 2
	.short _0222DA54 - _0222DA10 - 2 ; case 3
	.short _0222DA72 - _0222DA10 - 2 ; case 4
	.short _0222DAAE - _0222DA10 - 2 ; case 5
	.short _0222DAFE - _0222DA10 - 2 ; case 6
	.short _0222DB1A - _0222DA10 - 2 ; case 7
_0222DA20:
	bl MOD71_0222DD60
	str r0, [r4, #0x48]
	b _0222DB32
_0222DA28:
	bl MOD71_0222E2D4
	str r0, [r4, #0x48]
	add r0, r4, #0
	bl MOD71_0222F264
	b _0222DB32
_0222DA36:
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x1a
	str r0, [sp, #8]
	add r0, r6, #0
	add r1, r6, #0
	add r2, r6, #0
	add r3, r6, #0
	bl FUN_0200E1D0
	mov r0, #2
	str r0, [r5]
	b _0222DB32
_0222DA54:
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x1a
	str r0, [sp, #8]
	add r0, r6, #0
	add r1, r6, #0
	add r2, r6, #0
	add r3, r6, #0
	bl FUN_0200E1D0
	mov r0, #4
	str r0, [r4, #0x48]
	b _0222DB32
_0222DA72:
	bl FUN_0200E308
	cmp r0, #0
	beq _0222DB32
	add r0, r4, #0
	bl MOD71_0222E3D4
	add r0, r4, #0
	bl MOD71_0222E378
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD71_0222E848
	mov r0, #1
	str r0, [r4, #0x44]
	mov r0, #5
	str r0, [r4, #0x48]
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #6
	bl _s32_div_f
	add r1, r0, #0
	add r0, r4, #0
	bl MOD71_0222F59C
	b _0222DB32
_0222DAAE:
	ldr r0, [r4, #0x40]
	bl FUN_02006290
	cmp r0, #0
	beq _0222DB32
	ldr r0, [r4, #0x40]
	bl FUN_02006260
	add r0, r4, #0
	bl MOD71_0222D820
	add r0, r6, #0
	str r0, [r4, #0x44]
	add r0, r4, #0
	add r0, #0x20
	ldrb r2, [r0]
	ldr r1, [r4, #0x3c]
	mov r0, #6
	mul r0, r1
	add r1, r2, r0
	add r0, r4, #0
	add r0, #0x88
	str r1, [r0]
	add r0, r4, #0
	bl MOD71_0222E224
	add r0, r4, #0
	mov r1, #0xce
	add r0, #0x88
	lsl r1, r1, #2
	ldr r0, [r0]
	ldr r1, [r4, r1]
	add r2, r6, #0
	bl MOD71_0222F350
	bl FUN_02033E74
	mov r0, #6
	str r0, [r4, #0x48]
	b _0222DB32
_0222DAFE:
	mov r0, #8
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x1a
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r1, #0
	add r3, r6, #0
	bl FUN_0200E1D0
	mov r0, #7
	str r0, [r4, #0x48]
	b _0222DB32
_0222DB1A:
	bl FUN_0200E308
	cmp r0, #0
	beq _0222DB32
	mov r0, #1
	str r0, [r4, #0x48]
	b _0222DB32
_0222DB28:
	bl FUN_0200E308
	cmp r0, #0
	beq _0222DB32
	mov r6, #1
_0222DB32:
	ldr r0, [r4, #0x44]
	cmp r0, #0
	bne _0222DB48
	add r0, r4, #0
	bl MOD71_02230B3C
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201FDEC
_0222DB48:
	mov r1, #0x5d
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	mov r0, #0x1a
	bl FUN_020335F0
	add r0, r6, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD71_0222D9C8

	thumb_func_start MOD71_0222DB5C
MOD71_0222DB5C: ; 0x0222DB5C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	add r0, r5, #0
	add r6, r2, #0
	mov r4, #0
	bl GetPartyCount
	cmp r0, #0
	ble _0222DB92
_0222DB70:
	add r0, r5, #0
	add r1, r4, #0
	bl GetPartyMonByIndex
	bl FUN_020690E4
	add r2, r0, #0
	add r0, r7, #0
	add r1, r4, r6
	bl FUN_0200ACF8
	add r0, r5, #0
	add r4, r4, #1
	bl GetPartyCount
	cmp r4, r0
	blt _0222DB70
_0222DB92:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD71_0222DB5C

	thumb_func_start MOD71_0222DB94
MOD71_0222DB94: ; 0x0222DB94
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r0, r3, #0
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r6, [sp, #0x28]
	mov r4, #0
	bl GetPartyCount
	cmp r0, #0
	ble _0222DBE6
	add r7, r6, #1
_0222DBB0:
	ldr r0, [sp, #8]
	ldr r1, [sp, #0xc]
	add r2, r7, r4
	mov r3, #0x1a
	bl ReadMsgData_ExpandPlaceholders
	add r6, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #8
	mov r3, #0
	bl MOD71_02230EFC
	add r0, r6, #0
	bl String_dtor
	ldr r0, [sp, #0x10]
	add r5, #0x10
	add r4, r4, #1
	bl GetPartyCount
	cmp r4, r0
	blt _0222DBB0
_0222DBE6:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD71_0222DB94

	thumb_func_start MOD71_0222DBEC
MOD71_0222DBEC: ; 0x0222DBEC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	str r2, [sp, #0x20]
	mov r7, #0
	bl GetPartyCount
	cmp r0, #0
	bgt _0222DC02
	b _0222DD10
_0222DC02:
	mov r1, #0x1f
	ldr r0, [sp, #0x20]
	lsl r1, r1, #6
	add r0, r0, r1
	str r0, [sp, #0x1c]
_0222DC0C:
	ldr r0, [sp, #0xc]
	ldr r2, _0222DD50 ; =0x00000696
	add r0, r7, r0
	str r0, [sp, #0x10]
	lsl r0, r0, #2
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x10]
	lsl r1, r0, #4
	ldr r0, [sp, #0x20]
	add r4, r0, r1
	ldr r1, [sp, #0x18]
	ldrb r2, [r4, r2]
	add r5, r0, r1
	mov r0, #0x69
	ldr r1, _0222DD54 ; =0x00000695
	lsl r0, r0, #4
	ldrh r0, [r4, r0]
	ldrb r1, [r4, r1]
	bl FUN_0206B6D4
	add r1, r0, #0
	mov r0, #0x1a
	str r0, [sp]
	ldr r6, [sp, #0x1c]
	ldr r3, [sp, #0x18]
	mov r0, #0x13
	mov r2, #0
	add r3, r6, r3
	bl FUN_02006BB0
	mov r1, #0x79
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	add r0, #0x30
	ldr r0, [r5, r0]
	mov r1, #2
	ldr r0, [r0, #0x14]
	lsl r1, r1, #8
	bl DC_FlushRange
	ldr r0, [sp, #0x10]
	mov r1, #0x69
	str r0, [sp]
	mov r0, #0x37
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	ldr r2, _0222DD50 ; =0x00000696
	str r0, [sp, #4]
	ldr r3, _0222DD54 ; =0x00000695
	mov r0, #0x1f
	lsl r1, r1, #4
	lsl r0, r0, #6
	ldrh r1, [r4, r1]
	ldrb r2, [r4, r2]
	ldrb r3, [r4, r3]
	ldr r0, [r5, r0]
	bl MOD71_0222D750
	mov r0, #0x37
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, _0222DD58 ; =0x00000692
	ldrh r0, [r4, r0]
	cmp r0, #0
	bne _0222DCA4
	mov r0, #0x3a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	b _0222DCCC
_0222DCA4:
	ldr r0, [sp, #0x10]
	lsl r1, r0, #2
	ldr r0, [sp, #0x20]
	add r1, r0, r1
	mov r0, #0x3a
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	str r1, [sp, #0x14]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x3a
	ldr r1, [sp, #0x14]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	ldr r1, _0222DD58 ; =0x00000692
	ldrh r1, [r4, r1]
	add r1, r1, #2
	bl FUN_02020130
_0222DCCC:
	ldr r0, _0222DD5C ; =0x0000069C
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0222DCE2
	mov r0, #0x3d
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	b _0222DD02
_0222DCE2:
	ldr r0, [sp, #0x10]
	lsl r1, r0, #2
	ldr r0, [sp, #0x20]
	add r4, r0, r1
	mov r0, #0x3d
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x3d
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0x15
	bl FUN_02020130
_0222DD02:
	ldr r0, [sp, #8]
	add r7, r7, #1
	bl GetPartyCount
	cmp r7, r0
	bge _0222DD10
	b _0222DC0C
_0222DD10:
	cmp r7, #6
	bge _0222DD4C
	ldr r0, [sp, #0xc]
	mov r6, #0x3a
	lsl r1, r0, #2
	ldr r0, [sp, #0x20]
	lsl r6, r6, #4
	add r1, r0, r1
	lsl r0, r7, #2
	add r5, r6, #0
	add r4, r1, r0
	add r5, #0x30
_0222DD28:
	mov r0, #0x37
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r4, r6]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r4, r5]
	mov r1, #0
	bl FUN_020200A0
	add r7, r7, #1
	add r4, r4, #4
	cmp r7, #6
	blt _0222DD28
_0222DD4C:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0222DD50: .word 0x00000696
_0222DD54: .word 0x00000695
_0222DD58: .word 0x00000692
_0222DD5C: .word 0x0000069C
	thumb_func_end MOD71_0222DBEC

	thumb_func_start MOD71_0222DD60
MOD71_0222DD60: ; 0x0222DD60
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r0, #0
	bl MOD71_02230C1C
	ldr r0, [r4, #0x4c]
	cmp r0, #0x13
	bls _0222DD72
	b _0222E0E8
_0222DD72:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222DD7E: ; jump table
	.short _0222DDA6 - _0222DD7E - 2 ; case 0
	.short _0222DDC0 - _0222DD7E - 2 ; case 1
	.short _0222DE12 - _0222DD7E - 2 ; case 2
	.short _0222DE22 - _0222DD7E - 2 ; case 3
	.short _0222DE38 - _0222DD7E - 2 ; case 4
	.short _0222DE48 - _0222DD7E - 2 ; case 5
	.short _0222DE60 - _0222DD7E - 2 ; case 6
	.short _0222DE74 - _0222DD7E - 2 ; case 7
	.short _0222DE86 - _0222DD7E - 2 ; case 8
	.short _0222DEB2 - _0222DD7E - 2 ; case 9
	.short _0222DEC0 - _0222DD7E - 2 ; case 10
	.short _0222DECC - _0222DD7E - 2 ; case 11
	.short _0222DF58 - _0222DD7E - 2 ; case 12
	.short _0222DF74 - _0222DD7E - 2 ; case 13
	.short _0222DF80 - _0222DD7E - 2 ; case 14
	.short _0222DF92 - _0222DD7E - 2 ; case 15
	.short _0222DFD6 - _0222DD7E - 2 ; case 16
	.short _0222E010 - _0222DD7E - 2 ; case 17
	.short _0222E054 - _0222DD7E - 2 ; case 18
	.short _0222E094 - _0222DD7E - 2 ; case 19
_0222DDA6:
	mov r0, #0x50
	bl FUN_02031588
	mov r0, #2
	bl FUN_020166A8
	add r0, r4, #0
	bl MOD71_02230B88
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
	b _0222E0E8
_0222DDC0:
	mov r0, #0x50
	bl FUN_020315D8
	cmp r0, #0
	beq _0222DEB8
	ldr r0, [r4, #8]
	ldr r0, [r0, #0x34]
	cmp r0, #0
	bne _0222DDD6
	mov r0, #6
	b _0222DDD8
_0222DDD6:
	mov r0, #2
_0222DDD8:
	str r0, [r4, #0x4c]
	bl FUN_02031190
	cmp r0, #0
	bne _0222DE04
	bl LCRandom
	ldr r1, _0222E0F0 ; =0x00000445
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x3c
	blo _0222DDF8
	bl ErrorHandling
_0222DDF8:
	bl FUN_02031190
	mov r1, #0x1f
	add r2, r5, #3
	bl MOD71_0222F42C
_0222DE04:
	ldr r0, [r4, #4]
	bl MOD71_0222F4A8
	add r0, r4, #0
	bl MOD71_02230C08
	b _0222E0E8
_0222DE12:
	mov r1, #0x8b
	lsl r1, r1, #6
	ldr r1, [r4, r1]
	cmp r1, #0
	beq _0222DEB8
	add r0, r0, #1
	str r0, [r4, #0x4c]
	b _0222E0E8
_0222DE22:
	mov r0, #0x8b
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0222DEB8
	mov r0, #4
	str r0, [r4, #0x4c]
	b _0222E0E8
_0222DE38:
	ldr r0, _0222E0F4 ; =0x0000369C
	add r0, r4, r0
	bl FUN_020336C0
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
	b _0222E0E8
_0222DE48:
	ldr r2, _0222E0F4 ; =0x0000369C
	ldr r0, [r4, #4]
	mov r1, #2
	add r2, r4, r2
	bl FUN_020336C8
	cmp r0, #0
	beq _0222DEB8
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
	b _0222E0E8
_0222DE60:
	mov r0, #1
	bl FUN_02031400
	mov r0, #0x51
	bl FUN_02031588
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
	b _0222E0E8
_0222DE74:
	mov r0, #0x51
	bl FUN_020315D8
	cmp r0, #0
	beq _0222DEB8
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
	b _0222E0E8
_0222DE86:
	mov r0, #0
	str r0, [r4, #0x50]
	str r0, [r4, #0x54]
	str r0, [r4, #0x58]
	bl FUN_02031190
	cmp r0, #1
	bne _0222DEAA
	bl FUN_02031190
	ldr r1, _0222E0F8 ; =0x00002218
	ldr r2, [r4, #0x50]
	ldr r1, [r4, r1]
	bl MOD71_0222F480
	ldr r0, [r4, #0x50]
	add r0, r0, #1
	str r0, [r4, #0x50]
_0222DEAA:
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
	b _0222E0E8
_0222DEB2:
	ldr r0, [r4, #0x54]
	cmp r0, #0
	bne _0222DEBA
_0222DEB8:
	b _0222E0E8
_0222DEBA:
	mov r0, #0xa
	str r0, [r4, #0x4c]
	b _0222E0E8
_0222DEC0:
	add r0, r0, #1
	str r0, [r4, #0x4c]
	add r0, r4, #0
	bl MOD71_0222D93C
	b _0222E0E8
_0222DECC:
	mov r1, #0
	mov r0, #0x69
	add r2, r4, #0
	add r5, r1, #0
	lsl r0, r0, #4
_0222DED6:
	add r1, r1, #1
	strh r5, [r2, r0]
	add r2, #0x10
	cmp r1, #0xd
	blt _0222DED6
	ldr r0, _0222E0F8 ; =0x00002218
	ldr r0, [r4, r0]
	bl GetPartyCount
	cmp r0, #0
	ble _0222DF12
	mov r0, #0x69
	lsl r0, r0, #4
	ldr r7, _0222E0F8 ; =0x00002218
	add r6, r4, r0
_0222DEF4:
	ldr r0, _0222E0F8 ; =0x00002218
	add r1, r5, #0
	ldr r0, [r4, r0]
	bl GetPartyMonByIndex
	add r1, r6, #0
	bl MOD71_0222E118
	ldr r0, [r4, r7]
	add r6, #0x10
	add r5, r5, #1
	bl GetPartyCount
	cmp r5, r0
	blt _0222DEF4
_0222DF12:
	ldr r0, _0222E0FC ; =0x0000221C
	mov r5, #0
	ldr r0, [r4, r0]
	bl GetPartyCount
	cmp r0, #0
	ble _0222DF48
	mov r0, #0x69
	lsl r0, r0, #4
	ldr r7, _0222E0FC ; =0x0000221C
	add r6, r4, r0
_0222DF28:
	ldr r0, _0222E0FC ; =0x0000221C
	add r1, r5, #0
	ldr r0, [r4, r0]
	bl GetPartyMonByIndex
	add r1, r5, #6
	lsl r1, r1, #4
	add r1, r6, r1
	bl MOD71_0222E118
	ldr r0, [r4, r7]
	add r5, r5, #1
	bl GetPartyCount
	cmp r5, r0
	blt _0222DF28
_0222DF48:
	mov r0, #0x75
	mov r1, #1
	lsl r0, r0, #4
	strh r1, [r4, r0]
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
	b _0222E0E8
_0222DF58:
	bl FUN_02031190
	bl FUN_0202DFA4
	ldr r2, _0222E100 ; =0x00002224
	ldr r1, [r4, r2]
	add r2, r2, #4
	add r2, r4, r2
	bl MOD71_0222F4BC
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
	b _0222E0E8
_0222DF74:
	ldr r1, [r4, #0x54]
	cmp r1, #3
	bne _0222DFD4
	add r0, r0, #1
	str r0, [r4, #0x4c]
	b _0222E0E8
_0222DF80:
	ldr r0, [r4, #4]
	bl FUN_02029EF8
	bl MOD71_0222F528
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
	b _0222E0E8
_0222DF92:
	ldr r1, [r4, #0x54]
	cmp r1, #4
	bne _0222DFD4
	add r0, r0, #1
	str r0, [r4, #0x4c]
	mov r0, #0x10
	mov r1, #0
	bl FUN_0201E6E4
	ldr r0, _0222E0F8 ; =0x00002218
	mov r1, #0
	ldr r0, [r4, r0]
	add r2, r4, #0
	bl MOD71_0222DBEC
	ldr r0, _0222E0FC ; =0x0000221C
	mov r1, #6
	ldr r0, [r4, r0]
	add r2, r4, #0
	bl MOD71_0222DBEC
	mov r6, #0xce
	mov r5, #0
	mov r7, #1
	lsl r6, r6, #2
_0222DFC4:
	ldr r0, [r4, r6]
	add r1, r7, #0
	bl FUN_020200A0
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #2
	blt _0222DFC4
_0222DFD4:
	b _0222E0E8
_0222DFD6:
	mov r1, #0
	mov r0, #1
	add r2, r1, #0
	str r0, [sp]
	mov r0, #8
	sub r2, #0x10
	mov r3, #0x1e
	bl FUN_0200A208
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201797C
	mov r0, #2
	mov r1, #1
	bl FUN_0201797C
	mov r0, #3
	mov r1, #1
	bl FUN_0201797C
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
	b _0222E0E8
_0222E010:
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #0
	beq _0222E0E8
	ldr r0, _0222E0F8 ; =0x00002218
	mov r1, #0
	ldr r0, [r4, r0]
	bl GetPartyMonByIndex
	mov r2, #0x7f
	ldr r3, _0222E104 ; =0x000020F0
	lsl r2, r2, #4
	add r1, r0, #0
	mov r0, #0
	add r2, r4, r2
	add r3, r4, r3
	bl MOD71_0222EBFC
	ldr r1, _0222E108 ; =0x00002110
	ldr r2, _0222E0F8 ; =0x00002218
	str r0, [r4, r1]
	str r4, [sp]
	ldr r0, _0222E10C ; =0x00000438
	mov r1, #0
	ldr r2, [r4, r2]
	add r0, r4, r0
	add r3, r1, #0
	bl MOD71_0222ECD4
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
	b _0222E0E8
_0222E054:
	mov r1, #0
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #8
	sub r2, #0x10
	mov r3, #0x17
	bl FUN_0200A208
	mov r0, #4
	mov r1, #1
	bl FUN_0201797C
	mov r0, #5
	mov r1, #1
	bl FUN_0201797C
	mov r0, #6
	mov r1, #1
	bl FUN_0201797C
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
	add r0, r4, #0
	bl MOD71_02230BA8
	b _0222E0E8
_0222E094:
	mov r0, #2
	bl FUN_0200A344
	cmp r0, #0
	beq _0222E0E8
	ldr r0, _0222E110 ; =0x000005A8
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200D0E0
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _0222E114 ; =0x00000588
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0xf
	mov r2, #1
	bl MOD71_02230F40
	mov r0, #2
	bl FUN_020166B8
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0222E0E8:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E0F0: .word 0x00000445
_0222E0F4: .word 0x0000369C
_0222E0F8: .word 0x00002218
_0222E0FC: .word 0x0000221C
_0222E100: .word 0x00002224
_0222E104: .word 0x000020F0
_0222E108: .word 0x00002110
_0222E10C: .word 0x00000438
_0222E110: .word 0x000005A8
_0222E114: .word 0x00000588
	thumb_func_end MOD71_0222DD60

	thumb_func_start MOD71_0222E118
MOD71_0222E118: ; 0x0222E118
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl AcquireMonLock
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #0x9a
	mov r2, #0
	bl GetMonData
	strb r0, [r4, #4]
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	strh r0, [r4]
	add r0, r5, #0
	mov r1, #0x70
	mov r2, #0
	bl GetMonData
	strb r0, [r4, #6]
	add r0, r5, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	strb r0, [r4, #5]
	add r0, r5, #0
	mov r1, #0x6f
	mov r2, #0
	bl GetMonData
	strh r0, [r4, #8]
	add r0, r5, #0
	mov r1, #0xa1
	mov r2, #0
	bl GetMonData
	str r0, [r4, #0xc]
	add r0, r5, #0
	mov r1, #6
	mov r2, #0
	bl GetMonData
	add r6, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	bl ReleaseMonLock
	ldrh r0, [r4]
	cmp r0, #0
	beq _0222E18E
	mov r1, #0x1c ; BASE_FLIP
	bl GetMonBaseStat
	strh r0, [r4, #0xa]
_0222E18E:
	cmp r6, #0
	beq _0222E19E
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	bl ItemIdIsMail
	add r0, r0, #1
	strh r0, [r4, #2]
_0222E19E:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD71_0222E118

	thumb_func_start MOD71_0222E1A0
MOD71_0222E1A0: ; 0x0222E1A0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #6
	bl _s32_div_f
	ldr r0, _0222E20C ; =0x0000221C
	add r7, r1, #0
	ldr r0, [r5, r0]
	bl GetPartyMonByIndex
	add r6, r0, #0
	add r0, r4, #0
	mov r1, #6
	bl _s32_div_f
	add r1, r6, #0
	mov r2, #0x7f
	mov r6, #0x32
	add r3, r0, #0
	lsl r2, r2, #4
	lsl r6, r6, #6
	mul r6, r3
	add r2, r5, r2
	add r2, r2, r6
	ldr r6, _0222E210 ; =0x000020F0
	lsl r3, r3, #4
	add r6, r5, r6
	mov r0, #1
	add r3, r6, r3
	bl MOD71_0222EBFC
	ldr r1, _0222E214 ; =0x00002110
	ldr r2, _0222E20C ; =0x0000221C
	str r0, [r5, r1]
	str r5, [sp]
	ldr r0, _0222E218 ; =0x00000438
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	add r3, r7, #0
	bl MOD71_0222ECD4
	lsl r1, r4, #4
	add r2, r5, r1
	ldr r1, _0222E21C ; =0x00000694
	ldr r0, _0222E220 ; =0x0000040C
	ldrb r1, [r2, r1]
	ldr r0, [r5, r0]
	add r1, r1, #5
	bl FUN_02020130
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222E20C: .word 0x0000221C
_0222E210: .word 0x000020F0
_0222E214: .word 0x00002110
_0222E218: .word 0x00000438
_0222E21C: .word 0x00000694
_0222E220: .word 0x0000040C
	thumb_func_end MOD71_0222E1A0

	thumb_func_start MOD71_0222E224
MOD71_0222E224: ; 0x0222E224
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r1, r5, #0
	add r1, #0x88
	ldr r1, [r1]
	cmp r1, #0xc
	beq _0222E2B8
	cmp r1, #6
	bge _0222E29E
	ldr r0, _0222E2BC ; =0x00002218
	ldr r0, [r5, r0]
	bl GetPartyMonByIndex
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #6
	bl _s32_div_f
	mov r2, #0x7f
	add r3, r0, #0
	lsl r2, r2, #4
	add r1, r4, #0
	add r4, r5, r2
	mov r2, #0x32
	lsl r2, r2, #6
	mul r2, r3
	add r2, r4, r2
	ldr r4, _0222E2C0 ; =0x000020F0
	lsl r3, r3, #4
	add r4, r5, r4
	mov r0, #0
	add r3, r4, r3
	bl MOD71_0222EBFC
	ldr r1, _0222E2C4 ; =0x00002110
	add r3, r5, #0
	str r0, [r5, r1]
	ldr r0, _0222E2C8 ; =0x00000438
	ldr r2, _0222E2BC ; =0x00002218
	str r5, [sp]
	add r3, #0x88
	ldr r2, [r5, r2]
	ldr r3, [r3]
	add r0, r5, r0
	mov r1, #0
	bl MOD71_0222ECD4
	ldr r0, _0222E2C8 ; =0x00000438
	mov r1, #1
	add r0, r5, r0
	add r2, r5, #0
	bl MOD71_0222EF24
	ldr r0, _0222E2CC ; =0x0000040C
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	pop {r3, r4, r5, pc}
_0222E29E:
	bl MOD71_0222E1A0
	ldr r0, _0222E2C8 ; =0x00000438
	mov r1, #0
	add r0, r5, r0
	add r2, r5, #0
	bl MOD71_0222EF24
	ldr r0, _0222E2D0 ; =0x00000408
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020200A0
_0222E2B8:
	pop {r3, r4, r5, pc}
	nop
_0222E2BC: .word 0x00002218
_0222E2C0: .word 0x000020F0
_0222E2C4: .word 0x00002110
_0222E2C8: .word 0x00000438
_0222E2CC: .word 0x0000040C
_0222E2D0: .word 0x00000408
	thumb_func_end MOD71_0222E224

	thumb_func_start MOD71_0222E2D4
MOD71_0222E2D4: ; 0x0222E2D4
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222E374 ; =0x00002214
	add r4, r0, #0
	ldr r1, [r4, r1]
	cmp r1, #0
	beq _0222E2EA
	blx r1
	mov r1, #5
	lsl r1, r1, #6
	str r0, [r4, r1]
_0222E2EA:
	mov r0, #5
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	cmp r0, #3
	bhi _0222E314
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222E300: ; jump table
	.short _0222E314 - _0222E300 - 2 ; case 0
	.short _0222E314 - _0222E300 - 2 ; case 1
	.short _0222E308 - _0222E300 - 2 ; case 2
	.short _0222E30E - _0222E300 - 2 ; case 3
_0222E308:
	add sp, #4
	mov r0, #2
	pop {r3, r4, pc}
_0222E30E:
	add sp, #4
	mov r0, #3
	pop {r3, r4, pc}
_0222E314:
	mov r0, #0
	mov r2, #0xce
	str r0, [sp]
	mov r0, #0x53
	lsl r2, r2, #2
	mov r3, #0x69
	lsl r0, r0, #2
	add r1, r4, #0
	lsl r3, r3, #4
	ldr r2, [r4, r2]
	add r0, r4, r0
	add r1, #0x88
	add r3, r4, r3
	bl MOD71_0222F3DC
	cmp r0, #0
	beq _0222E33C
	add r0, r4, #0
	bl MOD71_0222E224
_0222E33C:
	mov r0, #1
	mov r2, #0xcf
	str r0, [sp]
	mov r0, #0x15
	lsl r2, r2, #2
	mov r3, #0x69
	lsl r0, r0, #4
	add r1, r4, #0
	lsl r3, r3, #4
	ldr r2, [r4, r2]
	add r0, r4, r0
	add r1, #0x8c
	add r3, r4, r3
	bl MOD71_0222F3DC
	add r0, r4, #0
	add r0, #0x90
	bl MOD71_0222F2D8
	add r0, r4, #0
	add r4, #0x88
	ldr r2, [r4]
	mov r1, #0x17
	bl MOD71_0222F440
	mov r0, #1
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0222E374: .word 0x00002214
	thumb_func_end MOD71_0222E2D4

	thumb_func_start MOD71_0222E378
MOD71_0222E378: ; 0x0222E378
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0x2d
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	mov r0, #0x2e
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	mov r0, #0xb5
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009E04
	mov r0, #0xb9
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009E04
	mov r7, #0xb
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #6
_0222E3AC:
	ldr r0, [r5, r7]
	bl FUN_02008E2C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0222E3AC
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_0201FD58
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD71_0222E378

	thumb_func_start MOD71_0222E3D4
MOD71_0222E3D4: ; 0x0222E3D4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, _0222E42C ; =0x00002218
	mov r4, #0
	ldr r0, [r6, r0]
	bl GetPartyCount
	cmp r0, #0
	ble _0222E402
	ldr r7, _0222E42C ; =0x00002218
	add r5, r6, #0
_0222E3EA:
	mov r0, #0x79
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FreeToHeap
	ldr r0, [r6, r7]
	add r5, r5, #4
	add r4, r4, #1
	bl GetPartyCount
	cmp r4, r0
	blt _0222E3EA
_0222E402:
	ldr r0, _0222E430 ; =0x0000221C
	mov r5, #0
	ldr r0, [r6, r0]
	bl GetPartyCount
	cmp r0, #0
	ble _0222E42A
	ldr r7, _0222E430 ; =0x0000221C
	add r4, r6, #0
_0222E414:
	ldr r0, _0222E434 ; =0x000007A8
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldr r0, [r6, r7]
	add r4, r4, #4
	add r5, r5, #1
	bl GetPartyCount
	cmp r5, r0
	blt _0222E414
_0222E42A:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222E42C: .word 0x00002218
_0222E430: .word 0x0000221C
_0222E434: .word 0x000007A8
	thumb_func_end MOD71_0222E3D4

	thumb_func_start MOD71_0222E438
MOD71_0222E438: ; 0x0222E438
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02006278
	add r4, r0, #0
	add r0, r5, #0
	bl FUN_0200628C
	ldr r1, [r4, #0x5c]
	str r1, [r0, #0x28]
	add r0, r4, #0
	bl MOD71_0222E3D4
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl String_dtor
	ldr r0, _0222E4D4 ; =0x0000221C
	ldr r0, [r4, r0]
	bl FreeToHeap
	add r0, r4, #0
	bl MOD71_0222E378
	ldr r0, _0222E4D8 ; =0x00000438
	add r0, r4, r0
	bl MOD71_02230E88
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD71_0222E848
	mov r1, #0x5d
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	mov r0, #0x1a
	bl FUN_02016A8C
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl DestroyMsgData
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	bl FUN_0200AB18
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200AB18
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200AB18
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl String_dtor
	add r0, r5, #0
	bl FUN_0200627C
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	mov r0, #0x1a
	bl FUN_020168D0
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_0222E4D4: .word 0x0000221C
_0222E4D8: .word 0x00000438
	thumb_func_end MOD71_0222E438

	thumb_func_start MOD71_0222E4DC
MOD71_0222E4DC: ; 0x0222E4DC
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0201AB60
	ldr r0, _0222E548 ; =0x00002110
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _0222E52E
	sub r4, r0, #1
	mov r0, #0x7f
	mov r2, #0x32
	lsl r0, r0, #4
	lsl r2, r2, #6
	add r1, r4, #0
	add r0, r5, r0
	mul r1, r2
	add r0, r0, r1
	bl GXS_LoadOBJ
	lsl r1, r4, #4
	mov r0, #0x20
	add r2, r5, r1
	str r0, [sp]
	mov r0, #0x1a
	add r3, r4, #2
	ldr r1, _0222E54C ; =0x000020F0
	str r0, [sp, #4]
	ldrh r0, [r2, r1]
	add r1, r1, #4
	ldrh r1, [r2, r1]
	mov r2, #5
	lsl r3, r3, #5
	bl FUN_02006930
	ldr r0, _0222E548 ; =0x00002110
	mov r1, #0
	str r1, [r5, r0]
_0222E52E:
	bl FUN_0201C30C
	bl FUN_02009F80
	ldr r3, _0222E550 ; =0x027E0000
	ldr r1, _0222E554 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_0222E548: .word 0x00002110
_0222E54C: .word 0x000020F0
_0222E550: .word 0x027E0000
_0222E554: .word 0x00003FF8
	thumb_func_end MOD71_0222E4DC

	thumb_func_start MOD71_0222E558
MOD71_0222E558: ; 0x0222E558
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _0222E574 ; =0x022311B0
	add r3, sp, #0
	mov r2, #5
_0222E562:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222E562
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_0222E574: .word MOD71_022311B0
	thumb_func_end MOD71_0222E558

	thumb_func_start MOD71_0222E578
MOD71_0222E578: ; 0x0222E578
	push {r4, r5, r6, r7, lr}
	sub sp, #0xd4
	ldr r4, _0222E748 ; =0x022310B4
	add r3, sp, #0xc4
	add r5, r0, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r4, _0222E74C ; =0x0223115C
	add r3, sp, #0xa8
	ldmia r4!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	mov r1, #0
	str r0, [r3]
	add r0, r5, #0
	add r3, r1, #0
	bl FUN_02016C18
	add r0, r5, #0
	mov r1, #0
	bl FUN_02018744
	ldr r4, _0222E750 ; =0x02231124
	add r3, sp, #0x8c
	ldmia r4!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	mov r1, #1
	str r0, [r3]
	add r0, r5, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r5, #0
	mov r1, #1
	bl FUN_02018744
	ldr r4, _0222E754 ; =0x02231178
	add r3, sp, #0x70
	ldmia r4!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	mov r1, #2
	str r0, [r3]
	add r0, r5, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r5, #0
	mov r1, #2
	bl FUN_02018744
	ldr r4, _0222E758 ; =0x02231194
	add r3, sp, #0x54
	ldmia r4!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	mov r1, #3
	str r0, [r3]
	add r0, r5, #0
	mov r3, #0
	bl FUN_02016C18
	ldr r4, _0222E75C ; =0x022310EC
	add r3, sp, #0x38
	ldmia r4!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	str r0, [r3]
	add r0, r5, #0
	mov r1, #4
	mov r3, #0
	bl FUN_02016C18
	add r0, r5, #0
	mov r1, #4
	bl FUN_02018744
	ldr r4, _0222E760 ; =0x02231108
	add r3, sp, #0x1c
	ldmia r4!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	mov r1, #5
	str r0, [r3]
	add r0, r5, #0
	mov r3, #0
	bl FUN_02016C18
	ldr r4, _0222E764 ; =0x02231140
	add r3, sp, #0
	ldmia r4!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	mov r1, #6
	str r0, [r3]
	add r0, r5, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x1a
	bl FUN_02017F18
	mov r0, #1
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x1a
	bl FUN_02017F18
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x1a
	bl FUN_02017F18
	mov r4, #0
	mov r6, #3
	add r7, r4, #0
_0222E6BC:
	lsl r1, r4, #0x18
	mov r2, #0
	add r0, r5, #0
	lsr r1, r1, #0x18
	add r3, r2, #0
	bl FUN_020179E0
	lsl r1, r4, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	add r2, r6, #0
	add r3, r7, #0
	bl FUN_020179E0
	add r1, r4, #4
	lsl r1, r1, #0x18
	mov r2, #0
	add r0, r5, #0
	lsr r1, r1, #0x18
	add r3, r2, #0
	bl FUN_020179E0
	add r1, r4, #4
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	add r4, r4, #1
	cmp r4, #4
	blt _0222E6BC
	mov r0, #0
	add r1, r0, #0
	bl FUN_0201797C
	mov r0, #1
	mov r1, #0
	bl FUN_0201797C
	mov r0, #2
	mov r1, #0
	bl FUN_0201797C
	mov r0, #3
	mov r1, #0
	bl FUN_0201797C
	mov r0, #4
	mov r1, #0
	bl FUN_0201797C
	mov r0, #5
	mov r1, #0
	bl FUN_0201797C
	mov r0, #6
	mov r1, #0
	bl FUN_0201797C
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _0222E768 ; =0xFFFF1FFF
	and r0, r1
	str r0, [r2]
	add sp, #0xd4
	pop {r4, r5, r6, r7, pc}
	nop
_0222E748: .word MOD71_022310B4
_0222E74C: .word MOD71_0223115C
_0222E750: .word MOD71_02231124
_0222E754: .word MOD71_02231178
_0222E758: .word MOD71_02231194
_0222E75C: .word MOD71_022310EC
_0222E760: .word MOD71_02231108
_0222E764: .word MOD71_02231140
_0222E768: .word 0xFFFF1FFF
	thumb_func_end MOD71_0222E578

	thumb_func_start MOD71_0222E76C
MOD71_0222E76C: ; 0x0222E76C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, r1, #0
	bl FUN_0200628C
	add r4, r0, #0
	mov r2, #6
	ldr r0, _0222E830 ; =0x00000668
	str r4, [r5, #8]
	mov r1, #4
	str r1, [r5, r0]
	mov r3, #0
	str r3, [r5, #0x44]
	sub r0, r0, #4
	str r3, [r5, r0]
	mov r0, #0x5b
	lsl r0, r0, #2
	str r2, [r5, r0]
	add r1, r0, #4
	str r2, [r5, r1]
	add r1, r5, #0
	add r1, #0x88
	str r3, [r1]
	add r1, r5, #0
	add r1, #0x8c
	str r2, [r1]
	sub r0, #0x2c
	str r3, [r5, r0]
	str r3, [r5, #0x48]
	ldr r0, _0222E834 ; =MOD71_0222F538
	ldr r1, _0222E838 ; =0x00002214
	str r3, [r5, #0x4c]
	str r0, [r5, r1]
	str r3, [r5, #0x60]
	str r3, [r5, #0x64]
	ldr r0, _0222E83C ; =0x00002110
	str r3, [r5, #0x5c]
	str r3, [r5, r0]
	ldr r0, _0222E840 ; =0x000036A0
	sub r6, r2, #7
	str r6, [r5, r0]
	add r2, r0, #4
	str r6, [r5, r2]
	add r2, r1, #0
	add r2, #0xac
	str r3, [r5, r2]
	add r2, r0, #0
	add r2, #0xc
	str r3, [r5, r2]
	add r0, #0x10
	str r3, [r5, r0]
	add r0, r1, #4
	ldr r2, [r4, #8]
	add r1, #0x10
	str r2, [r5, r0]
	ldr r0, [r4, #0xc]
	str r0, [r5, r1]
	ldr r0, [r4, #0x10]
	str r0, [r5, #4]
	bl FUN_0206B8A4
	add r1, r0, #0
	mov r0, #0x1a
	bl AllocFromHeap
	ldr r1, _0222E844 ; =0x0000221C
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	mov r1, #6
	bl FUN_0206B8CC
	bl FUN_0206B8A4
	add r2, r0, #0
	ldr r0, _0222E844 ; =0x0000221C
	mov r1, #0xff
	ldr r0, [r5, r0]
	bl memset
	ldr r0, [r4, #4]
	mov r1, #0x1a
	bl FUN_020239A0
	mov r1, #0x63
	lsl r1, r1, #2
	str r0, [r5, r1]
	sub r1, #8
	ldr r0, [r5, r1]
	mov r1, #0x28
	bl NewString_ReadMsgData
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [r5, r1]
	ldr r0, [r4, #0x14]
	bl FUN_02033778
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222E830: .word 0x00000668
_0222E834: .word MOD71_0222F538
_0222E838: .word 0x00002214
_0222E83C: .word 0x00002110
_0222E840: .word 0x000036A0
_0222E844: .word 0x0000221C
	thumb_func_end MOD71_0222E76C

	thumb_func_start MOD71_0222E848
MOD71_0222E848: ; 0x0222E848
	push {r4, lr}
	add r4, r0, #0
	mov r1, #6
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #5
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #4
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #3
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #2
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #0
	bl FUN_020178A0
	pop {r4, pc}
	thumb_func_end MOD71_0222E848

	thumb_func_start MOD71_0222E884
MOD71_0222E884: ; 0x0222E884
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r2, #0
	mov r2, #1
	add r4, r3, #0
	str r2, [sp]
	ldr r2, [sp, #0x20]
	ldr r3, [sp, #0x24]
	bl FUN_02006C98
	add r6, r0, #0
	beq _0222E8D6
	add r1, sp, #4
	bl FUN_020B0180
	cmp r0, #0
	beq _0222E8D0
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	bne _0222E8B2
	ldr r0, [sp, #4]
	ldr r0, [r0, #8]
	str r0, [sp, #0x1c]
_0222E8B2:
	lsl r1, r4, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	bl FUN_0201886C
	cmp r0, #0
	beq _0222E8D0
	ldr r2, [sp, #4]
	lsl r1, r4, #0x18
	ldr r3, [sp, #0x1c]
	add r0, r5, #0
	lsr r1, r1, #0x18
	add r2, #0xc
	bl FUN_02017DFC
_0222E8D0:
	add r0, r6, #0
	bl FreeToHeap
_0222E8D6:
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD71_0222E884

	thumb_func_start MOD71_0222E8DC
MOD71_0222E8DC: ; 0x0222E8DC
	push {r3, r4, lr}
	sub sp, #4
	mov r1, #2
	add r4, r0, #0
	bl FUN_0201886C
	add r2, r0, #0
	mov r0, #0
	mov r3, #6
	str r0, [sp]
	add r0, r4, #0
	mov r1, #2
	lsl r3, r3, #8
	bl FUN_02017CE8
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD71_0222E8DC

	thumb_func_start MOD71_0222E900
MOD71_0222E900: ; 0x0222E900
	push {r4, lr}
	sub sp, #0x10
	mov r1, #0x5d
	lsl r1, r1, #2
	ldr r4, [r0, r1]
	sub r1, #0x54
	str r1, [sp]
	mov r0, #0x1a
	mov r1, #0
	str r0, [sp, #4]
	mov r0, #0x36
	mov r2, #4
	add r3, r1, #0
	bl FUN_02006930
	mov r1, #0
	mov r0, #0x12
	lsl r0, r0, #4
	str r0, [sp]
	mov r0, #0x1a
	str r0, [sp, #4]
	mov r0, #0x36
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02006930
	mov r0, #0
	add r1, r0, #0
	bl FUN_02017FE4
	mov r0, #4
	mov r1, #0
	bl FUN_02017FE4
	mov r1, #0x1a
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x1a
	bl FUN_02002EEC
	mov r0, #0
	str r0, [sp]
	mov r0, #9
	lsl r0, r0, #0xa
	str r0, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	mov r0, #0x1a
	str r0, [sp, #0xc]
	mov r0, #0x36
	add r2, r4, #0
	mov r3, #2
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x1a
	str r0, [sp, #0xc]
	mov r0, #0x36
	mov r1, #3
	add r2, r4, #0
	mov r3, #2
	bl MOD71_0222E884
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x1a
	str r0, [sp, #0xc]
	mov r0, #0x36
	mov r1, #4
	add r2, r4, #0
	mov r3, #3
	bl FUN_020068C8
	mov r0, #0
	mov r1, #0x40
	mov r2, #0x1a
	bl FUN_02002EEC
	mov r0, #0
	mov r1, #0x60
	mov r2, #0x1a
	bl FUN_02002ED0
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	lsl r0, r0, #0xa
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x1a
	str r0, [sp, #0xc]
	mov r0, #0x36
	mov r1, #2
	add r2, r4, #0
	mov r3, #5
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x1a
	mov r1, #5
	str r0, [sp, #0xc]
	mov r0, #0x36
	add r2, r4, #0
	add r3, r1, #0
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x1a
	mov r1, #6
	str r0, [sp, #0xc]
	mov r0, #0x36
	add r2, r4, #0
	add r3, r1, #0
	bl FUN_020068C8
	mov r0, #4
	mov r1, #0x40
	mov r2, #0x1a
	bl FUN_02002EEC
	mov r0, #4
	mov r1, #0x60
	mov r2, #0x1a
	bl FUN_02002ED0
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD71_0222E900

	thumb_func_start MOD71_0222EA38
MOD71_0222EA38: ; 0x0222EA38
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _0222EA64 ; =0x022310C4
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_0201D040
	mov r0, #0x14
	mov r1, #0x1a
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_0222EA64: .word MOD71_022310C4
	thumb_func_end MOD71_0222EA38

	thumb_func_start MOD71_0222EA68
MOD71_0222EA68: ; 0x0222EA68
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r1, #0x7f
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x1a
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	mov r1, #0x66
	lsl r1, r1, #2
	mov r0, #0x2d
	add r1, r5, r1
	mov r2, #0x1a
	bl FUN_02008C9C
	mov r1, #0x65
	lsl r1, r1, #2
	mov r7, #0xb
	str r0, [r5, r1]
	mov r6, #0
	add r4, r5, #0
	lsl r7, r7, #6
_0222EAA6:
	mov r0, #2
	add r1, r6, #0
	mov r2, #0x1a
	bl FUN_02008DEC
	str r0, [r4, r7]
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _0222EAA6
	mov r0, #0
	str r0, [sp]
	mov r3, #1
	str r3, [sp, #4]
	mov r0, #0x1a
	str r0, [sp, #8]
	mov r0, #0xb
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #0x36
	mov r2, #7
	bl FUN_02008F34
	mov r1, #0x2d
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r2, #0
	str r2, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #9
	str r0, [sp, #8]
	mov r0, #0x1a
	sub r1, #0xc
	str r0, [sp, #0xc]
	ldr r0, [r5, r1]
	mov r1, #0x36
	add r3, r2, #0
	bl FUN_02008FEC
	mov r1, #0xb5
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x1a
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x36
	mov r2, #8
	mov r3, #1
	bl FUN_020090AC
	mov r1, #0xb6
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x1a
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x36
	mov r2, #9
	mov r3, #1
	bl FUN_020090AC
	mov r1, #0xb7
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r3, #1
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x1a
	sub r1, #0x1c
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x36
	mov r2, #0xa
	bl FUN_02008F34
	mov r1, #0x2e
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	mov r0, #0x1a
	mov r2, #0
	sub r1, #0x1c
	str r0, [sp, #0xc]
	ldr r0, [r5, r1]
	mov r1, #0x36
	add r3, r2, #0
	bl FUN_02008FEC
	mov r1, #0xb9
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r3, #1
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x1a
	sub r1, #0x1c
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x36
	mov r2, #0xb
	bl FUN_020090AC
	mov r1, #0xba
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r3, #1
	str r3, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x1a
	sub r1, #0x1c
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x36
	mov r2, #0xc
	bl FUN_020090AC
	mov r1, #0xbb
	lsl r1, r1, #2
	str r0, [r5, r1]
	sub r1, #0x1c
	ldr r0, [r5, r1]
	bl FUN_02009A50
	mov r0, #0x2e
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_02009A50
	mov r0, #0xb5
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009CF0
	mov r0, #0xb9
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009CF0
	bl FUN_0206B888
	mov r3, #0x80
	add r1, r0, #0
	str r3, [sp]
	mov r0, #0x1a
	str r0, [sp, #4]
	mov r0, #0x13
	mov r2, #1
	add r3, #0xc0
	bl FUN_02006930
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD71_0222EA68

	thumb_func_start MOD71_0222EBFC
MOD71_0222EBFC: ; 0x0222EBFC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	add r4, r2, #0
	add r0, r3, #0
	mov r2, #2
	add r6, r1, #0
	str r3, [sp, #0x20]
	bl FUN_02068B68
	mov r1, #0
	add r0, r6, #0
	add r2, r1, #0
	bl GetMonData
	add r7, r0, #0
	add r0, r6, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	mov r3, #0
	str r3, [sp]
	mov r1, #0xa
	str r1, [sp, #4]
	str r1, [sp, #8]
	str r4, [sp, #0xc]
	str r7, [sp, #0x10]
	str r3, [sp, #0x14]
	mov r1, #2
	str r1, [sp, #0x18]
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x20]
	ldrh r0, [r0]
	ldrh r1, [r1, #2]
	mov r2, #0x1a
	bl FUN_020124B4
	mov r1, #0x32
	add r0, r4, #0
	lsl r1, r1, #6
	bl DC_FlushRange
	add r0, r5, #1
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD71_0222EBFC

	thumb_func_start MOD71_0222EC5C
MOD71_0222EC5C: ; 0x0222EC5C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	mov r0, #0x14
	mov r1, #0x1a
	str r3, [sp, #8]
	bl String_ctor
	add r4, r0, #0
	add r0, r6, #0
	add r1, r7, #0
	bl GetPartyMonByIndex
	mov r1, #0x76
	add r2, r4, #0
	bl GetMonData
	add r0, r5, #0
	mov r1, #0
	bl FUN_02019620
	ldr r0, [sp, #0x20]
	ldr r2, [sp, #8]
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	mov r3, #0
	bl MOD71_02230EFC
	add r0, r4, #0
	bl String_dtor
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD71_0222EC5C

	thumb_func_start MOD71_0222ECA8
MOD71_0222ECA8: ; 0x0222ECA8
	push {r4, lr}
	ldrh r0, [r0]
	add r4, r3, #0
	cmp r0, #0x1d
	beq _0222ECB6
	cmp r0, #0x20
	bne _0222ECCE
_0222ECB6:
	add r0, r1, #0
	add r1, r2, #0
	bl GetPartyMonByIndex
	mov r1, #0x4d
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222ECCE
	mov r0, #2
	pop {r4, pc}
_0222ECCE:
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD71_0222ECA8

	thumb_func_start MOD71_0222ECD4
MOD71_0222ECD4: ; 0x0222ECD4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r6, r0, #0
	add r5, r1, #0
	add r0, r2, #0
	add r1, r3, #0
	str r2, [sp, #8]
	str r3, [sp, #0xc]
	ldr r4, [sp, #0x50]
	bl GetPartyMonByIndex
	mov r1, #2
	bl FUN_02068E14
	str r0, [sp, #0x10]
	mov r0, #1
	lsl r0, r0, #0xa
	add r7, r4, r0
	lsl r0, r5, #2
	str r0, [sp, #0x14]
	ldr r0, [r7, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0xc
	add r3, r5, #0
	mul r3, r0
	ldr r1, _0222EF10 ; =0x022311D8
	ldr r0, [sp, #0x14]
	ldr r2, _0222EF14 ; =0x022311DC
	ldr r1, [r1, r3]
	ldr r3, [r2, r3]
	ldr r2, [sp, #0x10]
	ldr r0, [r7, r0]
	add r2, r2, r3
	add r2, #0xc0
	bl MOD71_02230B70
	cmp r5, #0
	bne _0222ED36
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x14]
	lsl r1, r1, #4
	add r2, r4, r1
	ldr r1, _0222EF18 ; =0x0000069A
	ldr r0, [r7, r0]
	ldrh r1, [r2, r1]
	bl FUN_02020100
_0222ED36:
	ldr r1, [sp, #0xc]
	mov r0, #1
	lsl r1, r1, #4
	add r2, r4, r1
	ldr r1, _0222EF1C ; =0x00000694
	lsl r0, r0, #0xa
	add r7, r4, r0
	add r0, r5, #2
	ldrb r1, [r2, r1]
	lsl r0, r0, #2
	str r0, [sp, #0x18]
	ldr r0, [r7, r0]
	add r1, r1, #5
	bl FUN_02020130
	ldr r0, [sp, #0x18]
	mov r1, #1
	ldr r0, [r7, r0]
	bl FUN_020200A0
	mov r0, #6
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x1a
	lsl r0, r0, #4
	ldr r1, [sp, #8]
	ldr r2, [sp, #0xc]
	add r0, r6, r0
	mov r3, #9
	bl MOD71_0222EC5C
	mov r7, #0x69
	mov r0, #6
	add r1, r5, #0
	mul r1, r0
	ldr r0, [sp, #0xc]
	lsl r7, r7, #4
	add r0, r0, r1
	lsl r0, r0, #4
	str r0, [sp, #0x34]
	add r1, r4, r7
	ldr r3, [sp, #0x34]
	add r0, r1, r0
	add r3, r4, r3
	add r7, #8
	ldrh r3, [r3, r7]
	ldr r1, [sp, #8]
	ldr r2, [sp, #0xc]
	bl MOD71_0222ECA8
	ldr r1, _0222EF20 ; =0x00000695
	add r2, r4, r1
	ldr r1, [sp, #0x34]
	str r2, [sp, #0x1c]
	ldrb r1, [r2, r1]
	cmp r1, #0
	beq _0222EDAA
	mov r0, #2
_0222EDAA:
	cmp r0, #0
	beq _0222EDCA
	cmp r0, #1
	beq _0222EDF0
	cmp r0, #2
	bne _0222EE14
	add r0, r5, #4
	lsl r0, r0, #2
	add r1, r4, r0
	mov r0, #1
	lsl r0, r0, #0xa
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_020200A0
	b _0222EE14
_0222EDCA:
	mov r0, #1
	lsl r0, r0, #0xa
	add r0, r4, r0
	str r0, [sp, #0x20]
	add r0, r5, #4
	lsl r0, r0, #2
	ldr r1, [sp, #0x20]
	str r0, [sp, #0x24]
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #0x24]
	ldr r0, [r1, r0]
	mov r1, #0x17
	bl FUN_02020130
	b _0222EE14
_0222EDF0:
	mov r0, #1
	lsl r0, r0, #0xa
	add r0, r4, r0
	str r0, [sp, #0x28]
	add r0, r5, #4
	lsl r0, r0, #2
	ldr r1, [sp, #0x28]
	str r0, [sp, #0x2c]
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
	ldr r1, [sp, #0x28]
	ldr r0, [sp, #0x2c]
	ldr r0, [r1, r0]
	mov r1, #0x16
	bl FUN_02020130
_0222EE14:
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x34]
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _0222EE9A
	mov r0, #0xa
	mov r1, #0x1a
	bl String_ctor
	add r7, r0, #0
	add r0, r5, #0
	add r0, #0x1c
	lsl r0, r0, #4
	str r0, [sp, #0x30]
	add r0, r6, r0
	mov r1, #0
	bl FUN_02019620
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x27
	add r2, r7, #0
	bl ReadMsgDataIntoString
	mov r0, #6
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, [sp, #0x30]
	add r1, r7, #0
	add r0, r6, r0
	mov r2, #9
	mov r3, #0xff
	bl MOD71_02230EFC
	ldr r0, [sp, #8]
	ldr r1, [sp, #0xc]
	bl GetPartyMonByIndex
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	mov r0, #1
	str r0, [sp]
	add r0, r7, #0
	mov r2, #3
	mov r3, #0
	bl String16_FormatInteger
	mov r0, #0x1e
	str r0, [sp]
	ldr r0, [sp, #0x30]
	mov r3, #0
	add r0, r6, r0
	add r1, r7, #0
	mov r2, #9
	str r3, [sp, #4]
	bl MOD71_02230EFC
	add r0, r7, #0
	bl String_dtor
	b _0222EEA6
_0222EE9A:
	add r0, r5, #0
	add r0, #0x1c
	lsl r0, r0, #4
	add r0, r6, r0
	bl FUN_02019570
_0222EEA6:
	mov r0, #3
	str r0, [sp]
	mov r3, #0
	add r0, r5, #0
	mov r1, #0x19
	add r0, #0x1e
	lsl r0, r0, #4
	str r3, [sp, #4]
	lsl r1, r1, #4
	ldr r1, [r4, r1]
	add r0, r6, r0
	mov r2, #7
	bl MOD71_02230EFC
	ldr r0, [sp, #8]
	ldr r1, [sp, #0xc]
	bl GetPartyMonByIndex
	mov r1, #6
	mov r2, #0
	bl GetMonData
	add r5, #0x20
	lsl r0, r0, #0x10
	lsl r4, r5, #4
	lsr r7, r0, #0x10
	add r0, r6, r4
	mov r1, #0
	bl FUN_02019620
	mov r0, #0x14
	mov r1, #0x1a
	bl String_ctor
	add r1, r7, #0
	mov r2, #0x1a
	add r5, r0, #0
	bl GetItemNameIntoString
	mov r0, #3
	str r0, [sp]
	mov r3, #0
	add r0, r6, r4
	add r1, r5, #0
	mov r2, #9
	str r3, [sp, #4]
	bl MOD71_02230EFC
	add r0, r5, #0
	bl String_dtor
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222EF10: .word MOD71_022311D8
_0222EF14: .word MOD71_022311DC
_0222EF18: .word 0x0000069A
_0222EF1C: .word 0x00000694
_0222EF20: .word 0x00000695
	thumb_func_end MOD71_0222ECD4

	thumb_func_start MOD71_0222EF24
MOD71_0222EF24: ; 0x0222EF24
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	lsl r0, r4, #2
	add r1, r6, r0
	mov r0, #1
	lsl r0, r0, #0xa
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_020200A0
	add r0, r4, #2
	lsl r0, r0, #2
	add r1, r6, r0
	mov r0, #1
	lsl r0, r0, #0xa
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_020200A0
	add r0, r4, #4
	lsl r0, r0, #2
	add r1, r6, r0
	mov r0, #1
	lsl r0, r0, #0xa
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_020200A0
	add r0, r4, #0
	add r0, #0x1a
	lsl r0, r0, #4
	add r0, r5, r0
	bl FUN_02019570
	add r0, r4, #0
	add r0, #0x1c
	lsl r0, r0, #4
	add r0, r5, r0
	bl FUN_02019570
	add r0, r4, #0
	add r0, #0x1e
	lsl r0, r0, #4
	add r0, r5, r0
	bl FUN_02019570
	add r4, #0x20
	lsl r0, r4, #4
	add r0, r5, r0
	bl FUN_02019570
	pop {r4, r5, r6, pc}
	thumb_func_end MOD71_0222EF24

	thumb_func_start MOD71_0222EF90
MOD71_0222EF90: ; 0x0222EF90
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	mov r1, #0
	add r5, r0, #0
	str r1, [sp]
	sub r0, r1, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r2, #0xb
	str r1, [sp, #0xc]
	mov r0, #2
	lsl r2, r2, #6
	str r0, [sp, #0x10]
	ldr r0, [r5, r2]
	add r3, r1, #0
	str r0, [sp, #0x14]
	add r0, r2, #4
	ldr r0, [r5, r0]
	str r0, [sp, #0x18]
	add r0, r2, #0
	add r0, #8
	ldr r0, [r5, r0]
	str r0, [sp, #0x1c]
	add r0, r2, #0
	add r0, #0xc
	ldr r0, [r5, r0]
	add r2, #0x30
	str r0, [sp, #0x20]
	str r1, [sp, #0x24]
	add r0, r5, r2
	add r2, r1, #0
	str r1, [sp, #0x28]
	bl FUN_02008AA4
	mov r1, #1
	mov r3, #0xb
	str r1, [sp]
	sub r0, r1, #2
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	lsl r3, r3, #6
	ldr r2, [r5, r3]
	str r2, [sp, #0x14]
	add r2, r3, #4
	ldr r2, [r5, r2]
	str r2, [sp, #0x18]
	add r2, r3, #0
	add r2, #8
	ldr r2, [r5, r2]
	str r2, [sp, #0x1c]
	add r2, r3, #0
	add r2, #0xc
	ldr r2, [r5, r2]
	add r3, #0x54
	str r2, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	add r0, r5, r3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02008AA4
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #2
	str r0, [sp, #0x2c]
	mov r0, #0x2f
	lsl r0, r0, #4
	add r0, r5, r0
	str r0, [sp, #0x30]
	mov r0, #6
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	str r0, [sp, #0x38]
	lsr r0, r1, #5
	mov r7, #0
	str r1, [sp, #0x34]
	str r7, [sp, #0x3c]
	str r0, [sp, #0x40]
	str r0, [sp, #0x44]
	str r0, [sp, #0x48]
	add r0, sp, #0x2c
	strh r7, [r0, #0x20]
	mov r0, #1
	str r0, [sp, #0x54]
	mov r0, #0x1a
	ldr r6, _0222F218 ; =0x02231220
	str r7, [sp, #0x50]
	str r0, [sp, #0x58]
	add r4, r5, #0
_0222F04C:
	ldr r0, [r6]
	lsl r0, r0, #0xc
	str r0, [sp, #0x34]
	ldr r0, [r6, #4]
	lsl r0, r0, #0xc
	str r0, [sp, #0x38]
	add r0, sp, #0x2c
	bl FUN_0201FE94
	mov r1, #0xce
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200BC
	add r0, r4, #0
	mov r1, #0xce
	add r0, #0x88
	lsl r1, r1, #2
	ldr r0, [r0]
	ldr r1, [r4, r1]
	add r2, r7, #0
	bl MOD71_0222F350
	mov r0, #0xce
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x64
	bl FUN_02020310
	mov r0, #0xce
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
	add r7, r7, #1
	add r6, #8
	add r4, r4, #4
	cmp r7, #2
	blt _0222F04C
	ldr r6, _0222F218 ; =0x02231220
	mov r7, #0
	add r4, r5, #0
_0222F0A8:
	ldr r0, [r6]
	add r0, #0x10
	lsl r0, r0, #0xc
	str r0, [sp, #0x34]
	ldr r0, [r6, #4]
	sub r0, r0, #6
	lsl r0, r0, #0xc
	str r0, [sp, #0x38]
	add r0, sp, #0x2c
	bl FUN_0201FE94
	mov r1, #0x37
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x37
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, r7, #5
	bl FUN_02020130
	mov r0, #0x37
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #5
	bl FUN_02020310
	mov r0, #0x37
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
	add r7, r7, #1
	add r6, #8
	add r4, r4, #4
	cmp r7, #0xc
	blt _0222F0A8
	ldr r6, _0222F218 ; =0x02231220
	mov r7, #0
	add r4, r5, #0
_0222F102:
	ldr r0, [r6]
	add r0, #0x24
	lsl r0, r0, #0xc
	str r0, [sp, #0x34]
	ldr r0, [r6, #4]
	add r0, #0x10
	lsl r0, r0, #0xc
	str r0, [sp, #0x38]
	mov r0, #0
	str r0, [sp, #0x50]
	add r0, sp, #0x2c
	bl FUN_0201FE94
	mov r1, #0x3a
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	mov r1, #3
	bl FUN_02020310
	mov r0, #0x3a
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
	add r7, r7, #1
	add r6, #8
	add r4, r4, #4
	cmp r7, #0xc
	blt _0222F102
	ldr r6, _0222F218 ; =0x02231220
	mov r7, #0
	add r4, r5, #0
_0222F148:
	ldr r0, [r6]
	add r0, #0x2d
	lsl r0, r0, #0xc
	str r0, [sp, #0x34]
	ldr r0, [r6, #4]
	add r0, #0x10
	lsl r0, r0, #0xc
	str r0, [sp, #0x38]
	mov r0, #0
	str r0, [sp, #0x50]
	add r0, sp, #0x2c
	bl FUN_0201FE94
	mov r1, #0x3d
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	mov r1, #3
	bl FUN_02020310
	mov r0, #0x3d
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
	add r7, r7, #1
	add r6, #8
	add r4, r4, #4
	cmp r7, #0xc
	blt _0222F148
	mov r0, #6
	lsl r0, r0, #0x10
	str r0, [sp, #0x34]
	mov r0, #0x42
	lsl r0, r0, #0xc
	str r0, [sp, #0x38]
	add r0, sp, #0x2c
	bl FUN_0201FE94
	ldr r1, _0222F21C ; =0x00000418
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, _0222F21C ; =0x00000418
	mov r1, #0x14
	ldr r0, [r5, r0]
	bl FUN_02020130
	ldr r0, _0222F21C ; =0x00000418
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	mov r0, #0xc5
	lsl r0, r0, #2
	ldr r4, _0222F220 ; =0x022311D8
	mov r6, #0
	add r7, r5, r0
_0222F1C4:
	ldr r0, [r4]
	str r7, [sp, #0x30]
	lsl r0, r0, #0xc
	str r0, [sp, #0x34]
	ldr r0, [r4, #4]
	lsl r1, r0, #0xc
	mov r0, #3
	lsl r0, r0, #0x12
	add r0, r1, r0
	str r0, [sp, #0x38]
	mov r0, #2
	str r0, [sp, #0x54]
	add r0, sp, #0x2c
	bl FUN_0201FE94
	mov r1, #1
	lsl r1, r1, #0xa
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #1
	lsl r0, r0, #0xa
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200BC
	mov r0, #1
	lsl r0, r0, #0xa
	ldr r0, [r5, r0]
	ldr r1, [r4, #8]
	bl FUN_02020130
	add r6, r6, #1
	add r4, #0xc
	add r5, r5, #4
	cmp r6, #6
	blt _0222F1C4
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0222F218: .word MOD71_02231220
_0222F21C: .word 0x00000418
_0222F220: .word MOD71_022311D8
	thumb_func_end MOD71_0222EF90

	thumb_func_start MOD71_0222F224
MOD71_0222F224: ; 0x0222F224
	push {r3, r4}
	ldr r3, _0222F260 ; =gUnknown21C48B8
	mov r1, #0
	ldr r3, [r3, #0x4c]
	mov r4, #0x40
	add r2, r1, #0
	tst r4, r3
	beq _0222F238
	mov r2, #1
	add r1, r1, #1
_0222F238:
	mov r4, #0x80
	tst r4, r3
	beq _0222F242
	mov r2, #2
	add r1, r1, #1
_0222F242:
	mov r4, #0x20
	tst r4, r3
	beq _0222F24C
	mov r2, #3
	add r1, r1, #1
_0222F24C:
	mov r4, #0x10
	tst r3, r4
	beq _0222F256
	mov r2, #4
	add r1, r1, #1
_0222F256:
	cmp r1, #0
	beq _0222F25C
	str r2, [r0]
_0222F25C:
	pop {r3, r4}
	bx lr
	.align 2, 0
_0222F260: .word gUnknown21C48B8
	thumb_func_end MOD71_0222F224

	thumb_func_start MOD71_0222F264
MOD71_0222F264: ; 0x0222F264
	push {r4, r5, r6, lr}
	add r4, r0, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #6
	bge _0222F2CA
	ldr r0, _0222F2CC ; =0x022310AC
	bl FUN_02020988
	add r5, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	beq _0222F2CA
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	lsl r0, r0, #4
	add r2, r4, r0
	ldr r0, _0222F2D0 ; =0x00000695
	ldrb r1, [r2, r0]
	cmp r1, #0
	bne _0222F2CA
	sub r0, r0, #5
	ldrh r0, [r2, r0]
	ldr r1, _0222F2D4 ; =0x000001B9
	cmp r0, r1
	bne _0222F2AE
	ldr r0, [r4, #4]
	bl FUN_02029EF8
	mov r1, #0
	mov r2, #0x64
	add r3, r1, #0
	bl FUN_02005E90
	b _0222F2B2
_0222F2AE:
	bl FUN_02005578
_0222F2B2:
	mov r0, #1
	lsl r0, r0, #0xa
	add r4, r4, r0
	lsl r6, r5, #2
	ldr r0, [r4, r6]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [r4, r6]
	add r1, r5, #4
	bl FUN_02020130
_0222F2CA:
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222F2CC: .word MOD71_022310AC
_0222F2D0: .word 0x00000695
_0222F2D4: .word 0x000001B9
	thumb_func_end MOD71_0222F264

	thumb_func_start MOD71_0222F2D8
MOD71_0222F2D8: ; 0x0222F2D8
	push {r3, lr}
	ldrh r1, [r0]
	add r1, #0x14
	strh r1, [r0]
	ldrh r2, [r0]
	mov r1, #0x5a
	lsl r1, r1, #2
	cmp r2, r1
	bls _0222F2EE
	mov r1, #0
	strh r1, [r0]
_0222F2EE:
	ldrh r0, [r0]
	bl Sin_Wrap
	mov r1, #0xa
	mul r1, r0
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	add r0, #0xf
	lsl r1, r0, #5
	mov r0, #0x1d
	orr r1, r0
	add r0, sp, #0
	strh r1, [r0]
	add r0, sp, #0
	mov r1, #0x3a
	mov r2, #2
	bl GX_LoadOBJPltt
	pop {r3, pc}
	thumb_func_end MOD71_0222F2D8

	thumb_func_start MOD71_0222F318
MOD71_0222F318: ; 0x0222F318
	push {r3, r4, r5, r6}
	mov r5, #0x18
	mul r5, r0
	ldr r6, _0222F34C ; =0x02231288
	mov r0, #6
	mov r4, #0
	add r5, r6, r5
	mul r0, r1
	add r5, r5, r0
	add r3, r4, #0
	add r1, r5, #0
_0222F32E:
	ldrb r0, [r1]
	lsl r0, r0, #4
	ldrh r0, [r2, r0]
	cmp r0, #0
	beq _0222F33C
	ldrb r4, [r5, r3]
	b _0222F344
_0222F33C:
	add r3, r3, #1
	add r1, r1, #1
	cmp r3, #6
	blt _0222F32E
_0222F344:
	add r0, r4, #0
	pop {r3, r4, r5, r6}
	bx lr
	nop
_0222F34C: .word MOD71_02231288
	thumb_func_end MOD71_0222F318

	thumb_func_start MOD71_0222F350
MOD71_0222F350: ; 0x0222F350
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	cmp r5, #0xd
	blt _0222F362
	bl ErrorHandling
_0222F362:
	ldr r1, _0222F3C8 ; =0x02231220
	lsl r0, r5, #3
	ldr r1, [r1, r0]
	lsl r1, r1, #0xc
	str r1, [sp]
	ldr r1, _0222F3CC ; =0x02231224
	ldr r0, [r1, r0]
	add r1, sp, #0
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	cmp r5, #0xc
	bne _0222F394
	add r0, r6, #0
	bl FUN_02020044
	mov r1, #0xc
	add r2, r4, #0
	mul r2, r1
	ldr r1, _0222F3D0 ; =0x022310DC
	add r0, r6, #0
	ldr r1, [r1, r2]
	bl FUN_02020130
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0222F394:
	add r0, r6, #0
	bl FUN_02020044
	cmp r5, #6
	bge _0222F3B2
	mov r1, #0xc
	add r2, r4, #0
	mul r2, r1
	ldr r1, _0222F3D4 ; =0x022310D4
	add r0, r6, #0
	ldr r1, [r1, r2]
	bl FUN_02020130
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0222F3B2:
	mov r1, #0xc
	add r2, r4, #0
	mul r2, r1
	ldr r1, _0222F3D8 ; =0x022310D8
	add r0, r6, #0
	ldr r1, [r1, r2]
	bl FUN_02020130
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_0222F3C8: .word MOD71_02231220
_0222F3CC: .word MOD71_02231224
_0222F3D0: .word MOD71_022310DC
_0222F3D4: .word MOD71_022310D4
_0222F3D8: .word MOD71_022310D8
	thumb_func_end MOD71_0222F350

	thumb_func_start MOD71_0222F3DC
MOD71_0222F3DC: ; 0x0222F3DC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	str r2, [sp]
	ldr r0, [r5]
	add r4, r1, #0
	ldr r2, [sp, #0x18]
	sub r1, r0, #1
	mov r7, #0
	cmp r2, #0
	bne _0222F41C
	cmp r0, #0
	beq _0222F416
	ldr r0, [r4]
	add r2, r3, #0
	bl MOD71_0222F318
	ldr r1, [sp]
	ldr r2, [sp, #0x18]
	add r6, r0, #0
	bl MOD71_0222F350
	ldr r0, [r4]
	cmp r0, r6
	beq _0222F416
	ldr r0, _0222F428 ; =0x000005DC
	bl FUN_020054C8
	str r6, [r4]
	mov r7, #1
_0222F416:
	mov r0, #0
	str r0, [r5]
	b _0222F424
_0222F41C:
	ldr r0, [r4]
	ldr r1, [sp]
	bl MOD71_0222F350
_0222F424:
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222F428: .word 0x000005DC
	thumb_func_end MOD71_0222F3DC

	thumb_func_start MOD71_0222F42C
MOD71_0222F42C: ; 0x0222F42C
	push {r3, lr}
	add r0, sp, #0
	strb r2, [r0]
	add r0, r1, #0
	add r1, sp, #0
	mov r2, #1
	bl FUN_02030ADC
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD71_0222F42C

	thumb_func_start MOD71_0222F440
MOD71_0222F440: ; 0x0222F440
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _0222F470 ; =0x000036A0
	add r4, r1, #0
	ldr r1, [r5, r0]
	add r6, r2, #0
	cmp r6, r1
	bne _0222F458
	add r0, r0, #4
	ldr r0, [r5, r0]
	cmp r4, r0
	beq _0222F46C
_0222F458:
	bl FUN_02031190
	add r1, r4, #0
	add r2, r6, #0
	bl MOD71_0222F42C
	ldr r0, _0222F470 ; =0x000036A0
	str r6, [r5, r0]
	add r0, r0, #4
	str r4, [r5, r0]
_0222F46C:
	pop {r4, r5, r6, pc}
	nop
_0222F470: .word 0x000036A0
	thumb_func_end MOD71_0222F440

	thumb_func_start MOD71_0222F474
MOD71_0222F474: ; 0x0222F474
	mov r2, #0x59
	lsl r2, r2, #4
	mul r2, r1
	add r0, r0, r2
	bx lr
	.align 2, 0
	thumb_func_end MOD71_0222F474

	thumb_func_start MOD71_0222F480
MOD71_0222F480: ; 0x0222F480
	push {r3, r4, r5, lr}
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r5, r1, #0
	add r4, r2, #0
	bl FUN_02030E7C
	cmp r0, #0
	beq _0222F4A6
	add r0, r5, #0
	add r1, r4, #0
	bl MOD71_0222F474
	mov r2, #0x59
	add r1, r0, #0
	mov r0, #0x16
	lsl r2, r2, #4
	bl FUN_02030A78
_0222F4A6:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD71_0222F480

	thumb_func_start MOD71_0222F4A8
MOD71_0222F4A8: ; 0x0222F4A8
	push {r3, lr}
	bl FUN_0202A918
	add r1, r0, #0
	mov r0, #0x20
	mov r2, #0xe
	bl FUN_02030ADC
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD71_0222F4A8

	thumb_func_start MOD71_0222F4BC
MOD71_0222F4BC: ; 0x0222F4BC
	push {r4, r5, r6, lr}
	add r4, r2, #0
	add r6, r0, #0
	add r5, r1, #0
	bl FUN_0202398C
	add r1, r0, #0
	add r0, r4, #0
	bl CopyU16StringArray
	add r0, r6, #0
	bl FUN_020239BC
	str r0, [r4, #0x10]
	add r0, r6, #0
	bl FUN_02023A70
	strb r0, [r4, #0x14]
	add r0, r6, #0
	bl FUN_02023A68
	strb r0, [r4, #0x15]
	add r0, r6, #0
	bl FUN_020239CC
	strb r0, [r4, #0x16]
	mov r0, #0
	add r1, r4, #0
_0222F4F4:
	ldr r2, [r5, #0x10]
	str r2, [r1, #0x18]
	ldrb r3, [r5, #0x15]
	add r2, r4, r0
	add r2, #0x58
	strb r3, [r2]
	add r2, r4, r0
	ldrb r3, [r5, #0x14]
	add r2, #0x68
	add r1, r1, #4
	strb r3, [r2]
	add r2, r4, r0
	ldrb r3, [r5, #0x16]
	add r2, #0x78
	add r0, r0, #1
	add r5, #0x88
	strb r3, [r2]
	cmp r0, #0x10
	blt _0222F4F4
	mov r0, #0x1c
	add r1, r4, #0
	mov r2, #0x88
	bl FUN_02030A78
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD71_0222F4BC

	thumb_func_start MOD71_0222F528
MOD71_0222F528: ; 0x0222F528
	ldr r3, _0222F534 ; =FUN_02030A78
	mov r2, #0xfa
	add r1, r0, #0
	mov r0, #0x1d
	lsl r2, r2, #2
	bx r3
	.align 2, 0
_0222F534: .word FUN_02030A78
	thumb_func_end MOD71_0222F528

	thumb_func_start MOD71_0222F538
MOD71_0222F538: ; 0x0222F538
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x53
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD71_0222F224
	ldr r0, _0222F588 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _0222F584
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0222F584
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #0xc
	bne _0222F56C
	ldr r1, _0222F58C ; =MOD71_0222F674
	ldr r0, _0222F590 ; =0x00002214
	str r1, [r4, r0]
	b _0222F584
_0222F56C:
	cmp r0, #6
	bge _0222F578
	ldr r1, _0222F594 ; =MOD71_0222FDD8
	ldr r0, _0222F590 ; =0x00002214
	str r1, [r4, r0]
	b _0222F584
_0222F578:
	blt _0222F584
	cmp r0, #0xc
	bge _0222F584
	ldr r1, _0222F598 ; =MOD71_02230810
	ldr r0, _0222F590 ; =0x00002214
	str r1, [r4, r0]
_0222F584:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_0222F588: .word gUnknown21C48B8
_0222F58C: .word MOD71_0222F674
_0222F590: .word 0x00002214
_0222F594: .word MOD71_0222FDD8
_0222F598: .word MOD71_02230810
	thumb_func_end MOD71_0222F538

	thumb_func_start MOD71_0222F59C
MOD71_0222F59C: ; 0x0222F59C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bne _0222F5CC
	ldr r0, _0222F660 ; =0x00002218
	ldr r0, [r5, r0]
	str r0, [r5, #0xc]
	ldr r0, [r5, #8]
	ldr r0, [r0, #8]
	bl GetPartyCount
	strb r0, [r5, #0x1f]
	mov r0, #0
	str r0, [r5, #0x34]
	bl FUN_02031190
	bl FUN_0202DFA4
	add r1, r0, #0
	add r0, r5, #0
	add r0, #0xc
	bl FUN_0207C2A4
	b _0222F606
_0222F5CC:
	ldr r0, _0222F664 ; =0x0000221C
	ldr r1, [r5, r0]
	str r1, [r5, #0xc]
	ldr r0, [r5, r0]
	bl GetPartyCount
	strb r0, [r5, #0x1f]
	bl FUN_02031190
	mov r2, #1
	ldr r1, _0222F668 ; =0x00002E14
	eor r2, r0
	mov r0, #0xfb
	lsl r0, r0, #2
	add r1, r5, r1
	mul r0, r2
	add r0, r1, r0
	str r0, [r5, #0x34]
	bl FUN_02031190
	mov r1, #1
	eor r0, r1
	bl FUN_0202DFA4
	add r1, r0, #0
	add r0, r5, #0
	add r0, #0xc
	bl FUN_0207C2A4
_0222F606:
	mov r0, #1
	strb r0, [r5, #0x1d]
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #6
	bl _s32_div_f
	add r0, r5, #0
	add r0, #0x20
	strb r1, [r0]
	mov r0, #1
	strb r0, [r5, #0x1e]
	mov r0, #0
	strh r0, [r5, #0x24]
	ldr r0, [r5, #8]
	ldr r0, [r0, #0x10]
	bl FUN_02079C70
	str r0, [r5, #0x38]
	ldr r0, [r5, #8]
	ldr r0, [r0, #0x30]
	str r0, [r5, #0x28]
	ldr r0, [r5, #8]
	ldr r0, [r0, #0x18]
	str r0, [r5, #0x10]
	ldr r0, [r5, #8]
	ldr r0, [r0, #0x10]
	bl FUN_0202A918
	str r0, [r5, #0x2c]
	add r0, r5, #0
	ldr r1, _0222F66C ; =0x022313C0
	add r0, #0xc
	bl FUN_0207B000
	add r1, r5, #0
	ldr r0, _0222F670 ; =UNK_020FA6E8
	add r1, #0xc
	mov r2, #0x1a
	bl FUN_02006234
	str r0, [r5, #0x40]
	str r4, [r5, #0x3c]
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222F660: .word 0x00002218
_0222F664: .word 0x0000221C
_0222F668: .word 0x00002E14
_0222F66C: .word MOD71_022313C0
_0222F670: .word UNK_020FA6E8
	thumb_func_end MOD71_0222F59C

	thumb_func_start MOD71_0222F674
MOD71_0222F674: ; 0x0222F674
	push {r4, lr}
	sub sp, #0x10
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _0222F6BC ; =0x000005A8
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0x19
	mov r2, #1
	bl MOD71_02230F40
	ldr r1, _0222F6C0 ; =MOD71_0222F6C8
	ldr r0, _0222F6C4 ; =0x00002214
	str r1, [r4, r0]
	mov r0, #0
	add sp, #0x10
	pop {r4, pc}
	nop
_0222F6BC: .word 0x000005A8
_0222F6C0: .word MOD71_0222F6C8
_0222F6C4: .word 0x00002214
	thumb_func_end MOD71_0222F674

	thumb_func_start MOD71_0222F6C8
MOD71_0222F6C8: ; 0x0222F6C8
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0x5d
	ldr r2, _0222F778 ; =0x00000658
	lsl r0, r0, #2
	add r1, r4, r2
	add r2, #0xc
	ldr r0, [r4, r0]
	add r2, r4, r2
	bl MOD71_02230FB0
	cmp r0, #0
	beq _0222F6EE
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _0222F738
	b _0222F772
_0222F6EE:
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _0222F77C ; =0x000005A8
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0x1c
	mov r2, #1
	bl MOD71_02230F40
	add r0, r4, #0
	mov r1, #0x18
	mov r2, #1
	bl MOD71_0222F440
	ldr r1, _0222F780 ; =MOD71_0222FD9C
	ldr r0, _0222F784 ; =0x00002214
	str r1, [r4, r0]
	mov r0, #0
	str r0, [r4, #0x5c]
	b _0222F772
_0222F738:
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _0222F788 ; =0x00000588
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0xf
	mov r2, #1
	bl MOD71_02230F40
	ldr r1, _0222F78C ; =MOD71_0222F538
	ldr r0, _0222F784 ; =0x00002214
	str r1, [r4, r0]
_0222F772:
	mov r0, #0
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_0222F778: .word 0x00000658
_0222F77C: .word 0x000005A8
_0222F780: .word MOD71_0222FD9C
_0222F784: .word 0x00002214
_0222F788: .word 0x00000588
_0222F78C: .word MOD71_0222F538
	thumb_func_end MOD71_0222F6C8

	thumb_func_start MOD71_0222F790
MOD71_0222F790: ; 0x0222F790
	push {r4, lr}
	sub sp, #0x10
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _0222F7D8 ; =0x000005A8
	ldr r1, [r4, #0x68]
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r2, #1
	bl MOD71_02230F40
	ldr r1, _0222F7DC ; =MOD71_0222F7E4
	ldr r0, _0222F7E0 ; =0x00002214
	str r1, [r4, r0]
	mov r0, #0
	add sp, #0x10
	pop {r4, pc}
	nop
_0222F7D8: .word 0x000005A8
_0222F7DC: .word MOD71_0222F7E4
_0222F7E0: .word 0x00002214
	thumb_func_end MOD71_0222F790

	thumb_func_start MOD71_0222F7E4
MOD71_0222F7E4: ; 0x0222F7E4
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, _0222F83C ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _0222F834
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _0222F840 ; =0x00000588
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0xf
	mov r2, #1
	bl MOD71_02230F40
	ldr r1, _0222F844 ; =MOD71_0222F538
	ldr r0, _0222F848 ; =0x00002214
	str r1, [r4, r0]
	add r0, r4, #0
	bl MOD71_02230390
_0222F834:
	mov r0, #0
	add sp, #0x10
	pop {r4, pc}
	nop
_0222F83C: .word gUnknown21C48B8
_0222F840: .word 0x00000588
_0222F844: .word MOD71_0222F538
_0222F848: .word 0x00002214
	thumb_func_end MOD71_0222F7E4

	thumb_func_start MOD71_0222F84C
MOD71_0222F84C: ; 0x0222F84C
	push {r3, r4, lr}
	sub sp, #4
	ldr r4, _0222F86C ; =0x00003674
	add r3, r0, #0
	ldr r0, [r3, r4]
	add r4, r4, #4
	str r0, [sp]
	ldr r0, _0222F870 ; =0x000005A8
	mov r2, #1
	add r0, r3, r0
	ldr r3, [r3, r4]
	bl MOD71_02230F40
	add sp, #4
	pop {r3, r4, pc}
	nop
_0222F86C: .word 0x00003674
_0222F870: .word 0x000005A8
	thumb_func_end MOD71_0222F84C

	thumb_func_start MOD71_0222F874
MOD71_0222F874: ; 0x0222F874
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x5d
	ldr r2, _0222F8B4 ; =0x00000658
	lsl r0, r0, #2
	add r1, r4, r2
	add r2, #0xc
	ldr r0, [r4, r0]
	add r2, r4, r2
	bl MOD71_02230FB0
	cmp r0, #0
	beq _0222F898
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _0222F8A0
	b _0222F8AE
_0222F898:
	ldr r1, _0222F8B8 ; =MOD71_0222FBF0
	ldr r0, _0222F8BC ; =0x00002214
	str r1, [r4, r0]
	b _0222F8AE
_0222F8A0:
	add r0, r4, #0
	mov r1, #0x22
	bl MOD71_0222F84C
	ldr r1, _0222F8C0 ; =MOD71_0222FADC
	ldr r0, _0222F8BC ; =0x00002214
	str r1, [r4, r0]
_0222F8AE:
	mov r0, #0
	pop {r4, pc}
	nop
_0222F8B4: .word 0x00000658
_0222F8B8: .word MOD71_0222FBF0
_0222F8BC: .word 0x00002214
_0222F8C0: .word MOD71_0222FADC
	thumb_func_end MOD71_0222F874

	thumb_func_start MOD71_0222F8C4
MOD71_0222F8C4: ; 0x0222F8C4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #0x5d
	ldr r2, _0222F938 ; =0x00000658
	lsl r0, r0, #2
	add r1, r4, r2
	add r2, #0xc
	ldr r0, [r4, r0]
	add r2, r4, r2
	bl MOD71_02230FB0
	cmp r0, #0
	beq _0222F8EA
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _0222F910
	b _0222F932
_0222F8EA:
	ldr r1, _0222F93C ; =0x00003694
	ldr r0, [r4, r1]
	sub r1, #0x24
	ldr r1, [r4, r1]
	bl FUN_02028468
	mov r0, #0
	str r0, [sp]
	ldr r1, _0222F940 ; =0x0000366C
	ldr r0, [r4, #4]
	ldr r1, [r4, r1]
	mov r2, #0x1f
	mov r3, #0x1a
	bl FUN_02033A70
	ldr r1, _0222F944 ; =MOD71_0222FBF0
	ldr r0, _0222F948 ; =0x00002214
	str r1, [r4, r0]
	b _0222F932
_0222F910:
	ldr r0, _0222F940 ; =0x0000366C
	ldr r0, [r4, r0]
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, _0222F94C ; =0x00003674
	mov r1, #0
	ldr r0, [r4, r0]
	bl FUN_0200ABC0
	add r0, r4, #0
	mov r1, #0x23
	bl MOD71_0222F84C
	ldr r1, _0222F950 ; =MOD71_0222F874
	ldr r0, _0222F948 ; =0x00002214
	str r1, [r4, r0]
_0222F932:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0222F938: .word 0x00000658
_0222F93C: .word 0x00003694
_0222F940: .word 0x0000366C
_0222F944: .word MOD71_0222FBF0
_0222F948: .word 0x00002214
_0222F94C: .word 0x00003674
_0222F950: .word MOD71_0222F874
	thumb_func_end MOD71_0222F8C4

	thumb_func_start MOD71_0222F954
MOD71_0222F954: ; 0x0222F954
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0xda
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	bl FUN_02001204
	add r4, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _0222F976
	add r0, r0, #1
	cmp r4, r0
	bne _0222F9A0
	mov r0, #0
	pop {r4, r5, r6, pc}
_0222F976:
	ldr r0, _0222FA10 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _0222FA14 ; =0x0000366C
	ldr r0, [r5, r0]
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, _0222FA18 ; =0x00003674
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_0200ABC0
	add r0, r5, #0
	mov r1, #0x23
	bl MOD71_0222F84C
	ldr r1, _0222FA1C ; =MOD71_0222F874
	ldr r0, _0222FA20 ; =0x00002214
	str r1, [r5, r0]
	b _0222F9E4
_0222F9A0:
	ldr r0, _0222FA10 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _0222FA24 ; =0x00003670
	str r4, [r5, r0]
	mov r0, #0x1a
	bl FUN_02023928
	add r6, r0, #0
	ldr r0, _0222FA28 ; =0x00003694
	add r1, r4, #0
	ldr r0, [r5, r0]
	bl FUN_020283A4
	add r1, r0, #0
	add r0, r6, #0
	bl FUN_0202395C
	ldr r0, _0222FA18 ; =0x00003674
	mov r1, #0
	ldr r0, [r5, r0]
	add r2, r6, #0
	bl FUN_0200ABC0
	add r0, r6, #0
	bl FreeToHeap
	add r0, r5, #0
	mov r1, #0x24
	bl MOD71_0222F84C
	ldr r1, _0222FA2C ; =MOD71_0222F8C4
	ldr r0, _0222FA20 ; =0x00002214
	str r1, [r5, r0]
_0222F9E4:
	ldr r0, _0222FA30 ; =0x00003684
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	ldr r0, _0222FA30 ; =0x00003684
	add r0, r5, r0
	bl FUN_02019178
	mov r0, #0xda
	lsl r0, r0, #6
	mov r1, #0
	ldr r0, [r5, r0]
	add r2, r1, #0
	bl FUN_02001300
	ldr r0, _0222FA34 ; =0x0000367C
	ldr r0, [r5, r0]
	bl FUN_02012870
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222FA10: .word 0x000005DC
_0222FA14: .word 0x0000366C
_0222FA18: .word 0x00003674
_0222FA1C: .word MOD71_0222F874
_0222FA20: .word 0x00002214
_0222FA24: .word 0x00003670
_0222FA28: .word 0x00003694
_0222FA2C: .word MOD71_0222F8C4
_0222FA30: .word 0x00003684
_0222FA34: .word 0x0000367C
	thumb_func_end MOD71_0222F954

	thumb_func_start MOD71_0222FA38
MOD71_0222FA38: ; 0x0222FA38
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _0222FACC ; =0x00003694
	ldr r0, [r5, r0]
	bl FUN_02028448
	str r0, [sp]
	add r0, r0, #1
	mov r1, #0x1a
	bl FUN_02012838
	ldr r1, _0222FAD0 ; =0x0000367C
	str r0, [r5, r1]
	mov r0, #0x64
	mov r1, #0x1a
	bl String_ctor
	ldr r7, _0222FACC ; =0x00003694
	add r6, r0, #0
	mov r4, #0
_0222FA60:
	ldr r0, [r5, r7]
	add r1, r4, #0
	bl FUN_0202842C
	cmp r0, #0
	beq _0222FA8A
	ldr r0, _0222FACC ; =0x00003694
	add r1, r4, #0
	ldr r0, [r5, r0]
	bl FUN_020283A4
	add r1, r0, #0
	add r0, r6, #0
	bl FUN_02021E28
	ldr r0, _0222FAD0 ; =0x0000367C
	add r1, r6, #0
	ldr r0, [r5, r0]
	add r2, r4, #0
	bl FUN_020128A0
_0222FA8A:
	add r4, r4, #1
	cmp r4, #0x20
	blt _0222FA60
	ldr r1, _0222FAD0 ; =0x0000367C
	mov r2, #0xb
	ldr r0, [r5, r1]
	sub r1, r1, #4
	add r3, r2, #0
	ldr r1, [r5, r1]
	sub r3, #0xd
	bl FUN_02012880
	add r0, r6, #0
	bl String_dtor
	ldr r2, _0222FAD0 ; =0x0000367C
	mov r3, #0x5d
	lsl r3, r3, #2
	ldr r0, [r5, r2]
	add r2, #8
	ldr r1, [sp]
	ldr r3, [r5, r3]
	add r2, r5, r2
	bl MOD71_02231018
	mov r1, #0xda
	lsl r1, r1, #6
	str r0, [r5, r1]
	ldr r1, _0222FAD4 ; =MOD71_0222F954
	ldr r0, _0222FAD8 ; =0x00002214
	str r1, [r5, r0]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222FACC: .word 0x00003694
_0222FAD0: .word 0x0000367C
_0222FAD4: .word MOD71_0222F954
_0222FAD8: .word 0x00002214
	thumb_func_end MOD71_0222FA38

	thumb_func_start MOD71_0222FADC
MOD71_0222FADC: ; 0x0222FADC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x5d
	ldr r2, _0222FB30 ; =0x00000658
	lsl r0, r0, #2
	add r1, r4, r2
	add r2, #0xc
	ldr r0, [r4, r0]
	add r2, r4, r2
	bl MOD71_02230FB0
	cmp r0, #0
	beq _0222FB00
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _0222FB08
	b _0222FB2A
_0222FB00:
	ldr r1, _0222FB34 ; =MOD71_0222FA38
	ldr r0, _0222FB38 ; =0x00002214
	str r1, [r4, r0]
	b _0222FB2A
_0222FB08:
	ldr r0, _0222FB3C ; =0x0000366C
	ldr r0, [r4, r0]
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, _0222FB40 ; =0x00003674
	mov r1, #0
	ldr r0, [r4, r0]
	bl FUN_0200ABC0
	add r0, r4, #0
	mov r1, #0x23
	bl MOD71_0222F84C
	ldr r1, _0222FB44 ; =MOD71_0222F874
	ldr r0, _0222FB38 ; =0x00002214
	str r1, [r4, r0]
_0222FB2A:
	mov r0, #0
	pop {r4, pc}
	nop
_0222FB30: .word 0x00000658
_0222FB34: .word MOD71_0222FA38
_0222FB38: .word 0x00002214
_0222FB3C: .word 0x0000366C
_0222FB40: .word 0x00003674
_0222FB44: .word MOD71_0222F874
	thumb_func_end MOD71_0222FADC

	thumb_func_start MOD71_0222FB48
MOD71_0222FB48: ; 0x0222FB48
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	mov r0, #0x5d
	ldr r2, _0222FBC4 ; =0x00000658
	lsl r0, r0, #2
	add r1, r5, r2
	add r2, #0xc
	ldr r0, [r5, r0]
	add r2, r5, r2
	bl MOD71_02230FB0
	cmp r0, #0
	beq _0222FB6E
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _0222FBB6
	b _0222FBBC
_0222FB6E:
	ldr r1, _0222FBC8 ; =MOD71_0222FBF0
	ldr r0, _0222FBCC ; =0x00002214
	ldr r6, _0222FBD0 ; =0x00003694
	str r1, [r5, r0]
	mov r4, #0
_0222FB78:
	ldr r0, [r5, r6]
	add r1, r4, #0
	bl FUN_0202842C
	cmp r0, #0
	bne _0222FB98
	mov r0, #0
	str r0, [sp]
	ldr r1, _0222FBD4 ; =0x0000366C
	ldr r0, [r5, #4]
	ldr r1, [r5, r1]
	add r2, r4, #0
	mov r3, #0x1a
	bl FUN_02033A70
	b _0222FB9E
_0222FB98:
	add r4, r4, #1
	cmp r4, #0x20
	blt _0222FB78
_0222FB9E:
	cmp r4, #0x20
	bne _0222FBBC
	add r0, r5, #0
	mov r1, #0x22
	bl MOD71_0222F84C
	ldr r1, _0222FBD8 ; =MOD71_0222FADC
	ldr r0, _0222FBCC ; =0x00002214
	add sp, #4
	str r1, [r5, r0]
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_0222FBB6:
	ldr r1, _0222FBC8 ; =MOD71_0222FBF0
	ldr r0, _0222FBCC ; =0x00002214
	str r1, [r5, r0]
_0222FBBC:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_0222FBC4: .word 0x00000658
_0222FBC8: .word MOD71_0222FBF0
_0222FBCC: .word 0x00002214
_0222FBD0: .word 0x00003694
_0222FBD4: .word 0x0000366C
_0222FBD8: .word MOD71_0222FADC
	thumb_func_end MOD71_0222FB48

	thumb_func_start MOD71_0222FBDC
MOD71_0222FBDC: ; 0x0222FBDC
	push {r3, lr}
	mov r0, #0x13
	bl FUN_020315D8
	cmp r0, #0
	beq _0222FBEC
	mov r0, #2
	pop {r3, pc}
_0222FBEC:
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD71_0222FBDC

	thumb_func_start MOD71_0222FBF0
MOD71_0222FBF0: ; 0x0222FBF0
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r1, #0
	ldr r0, _0222FCE4 ; =0x0000366C
	mvn r1, r1
	str r1, [r6, r0]
	mov r4, #0
	bl FUN_02030F20
	cmp r0, #0
	ble _0222FC2C
	ldr r7, _0222FCE8 ; =0x000035EC
	add r5, r6, #0
_0222FC0A:
	ldr r0, [r5, r7]
	cmp r0, #2
	bne _0222FC20
	ldr r0, _0222FCE4 ; =0x0000366C
	lsl r1, r4, #2
	str r4, [r6, r0]
	mov r2, #0
	add r1, r6, r1
	sub r0, #0x80
	str r2, [r1, r0]
	b _0222FC2C
_0222FC20:
	add r5, r5, #4
	add r4, r4, #1
	bl FUN_02030F20
	cmp r4, r0
	blt _0222FC0A
_0222FC2C:
	ldr r0, _0222FCE4 ; =0x0000366C
	mov r1, #0
	ldr r2, [r6, r0]
	mvn r1, r1
	cmp r2, r1
	bne _0222FC70
	add r0, #0xc
	ldr r0, [r6, r0]
	bl DestroyMsgData
	ldr r0, _0222FCEC ; =0x00003674
	ldr r0, [r6, r0]
	bl FUN_0200AB18
	mov r0, #0x13
	bl FUN_02031588
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r6, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _0222FCF0 ; =0x000005A8
	ldr r3, [r6, r3]
	add r0, r6, r0
	mov r1, #0x1c
	mov r2, #1
	bl MOD71_02230F40
	ldr r1, _0222FCF4 ; =MOD71_0222FBDC
	ldr r0, _0222FCF8 ; =0x00002214
	str r1, [r6, r0]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0222FC70:
	ldr r0, [r6, #4]
	bl FUN_0206F158
	ldr r1, _0222FCFC ; =0x000001B5
	mov r2, #1
	mov r3, #0x1a
	bl FUN_0206EE50
	cmp r0, #1
	bne _0222FCAA
	ldr r0, _0222FCE4 ; =0x0000366C
	ldr r0, [r6, r0]
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, _0222FCEC ; =0x00003674
	mov r1, #0
	ldr r0, [r6, r0]
	bl FUN_0200ABC0
	add r0, r6, #0
	mov r1, #0x21
	bl MOD71_0222F84C
	ldr r1, _0222FD00 ; =MOD71_0222FB48
	ldr r0, _0222FCF8 ; =0x00002214
	str r1, [r6, r0]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0222FCAA:
	ldr r0, [r6, #4]
	bl FUN_020286EC
	add r5, r0, #0
	mov r4, #0
_0222FCB4:
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0202842C
	cmp r0, #0
	bne _0222FCD4
	mov r0, #0
	str r0, [sp]
	ldr r1, _0222FCE4 ; =0x0000366C
	ldr r0, [r6, #4]
	ldr r1, [r6, r1]
	add r2, r4, #0
	mov r3, #0x1a
	bl FUN_02033A70
	b _0222FCDA
_0222FCD4:
	add r4, r4, #1
	cmp r4, #0x20
	blt _0222FCB4
_0222FCDA:
	ldr r1, _0222FD04 ; =MOD71_0222FBF0
	ldr r0, _0222FCF8 ; =0x00002214
	str r1, [r6, r0]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222FCE4: .word 0x0000366C
_0222FCE8: .word 0x000035EC
_0222FCEC: .word 0x00003674
_0222FCF0: .word 0x000005A8
_0222FCF4: .word MOD71_0222FBDC
_0222FCF8: .word 0x00002214
_0222FCFC: .word 0x000001B5
_0222FD00: .word MOD71_0222FB48
_0222FD04: .word MOD71_0222FBF0
	thumb_func_end MOD71_0222FBF0

	thumb_func_start MOD71_0222FD08
MOD71_0222FD08: ; 0x0222FD08
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r1, _0222FD78 ; =0x000035EC
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0x1a
	bl FUN_020339B4
	cmp r0, #0
	bne _0222FD48
	mov r0, #0x13
	bl FUN_02031588
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _0222FD7C ; =0x000005A8
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0x1c
	mov r2, #1
	bl MOD71_02230F40
	ldr r1, _0222FD80 ; =MOD71_0222FBDC
	ldr r0, _0222FD84 ; =0x00002214
	add sp, #4
	str r1, [r4, r0]
	mov r0, #0
	pop {r3, r4, pc}
_0222FD48:
	mov r0, #0x1a
	bl FUN_0200AA80
	ldr r1, _0222FD88 ; =0x00003674
	ldr r2, _0222FD8C ; =0x00000251
	str r0, [r4, r1]
	mov r1, #0x1a
	mov r0, #0
	add r3, r1, #0
	bl NewMsgDataFromNarc
	ldr r1, _0222FD90 ; =0x00003678
	str r0, [r4, r1]
	ldr r0, [r4, #4]
	bl FUN_020286EC
	ldr r1, _0222FD94 ; =0x00003694
	str r0, [r4, r1]
	ldr r1, _0222FD98 ; =MOD71_0222FBF0
	ldr r0, _0222FD84 ; =0x00002214
	str r1, [r4, r0]
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0222FD78: .word 0x000035EC
_0222FD7C: .word 0x000005A8
_0222FD80: .word MOD71_0222FBDC
_0222FD84: .word 0x00002214
_0222FD88: .word 0x00003674
_0222FD8C: .word 0x00000251
_0222FD90: .word 0x00003678
_0222FD94: .word 0x00003694
_0222FD98: .word MOD71_0222FBF0
	thumb_func_end MOD71_0222FD08

	thumb_func_start MOD71_0222FD9C
MOD71_0222FD9C: ; 0x0222FD9C
	ldr r2, [r0, #0x60]
	cmp r2, #0
	beq _0222FDC8
	ldr r1, [r0, #0x64]
	cmp r1, #0
	beq _0222FDC8
	cmp r2, #1
	bne _0222FDB8
	cmp r1, #1
	bne _0222FDB8
	ldr r2, _0222FDCC ; =MOD71_0222FD08
	ldr r1, _0222FDD0 ; =0x00002214
	str r2, [r0, r1]
	b _0222FDBE
_0222FDB8:
	ldr r2, _0222FDD4 ; =MOD71_0222F790
	ldr r1, _0222FDD0 ; =0x00002214
	str r2, [r0, r1]
_0222FDBE:
	mov r1, #0
	str r1, [r0, #0x60]
	str r1, [r0, #0x64]
	mov r1, #0x1d
	str r1, [r0, #0x68]
_0222FDC8:
	mov r0, #0
	bx lr
	.align 2, 0
_0222FDCC: .word MOD71_0222FD08
_0222FDD0: .word 0x00002214
_0222FDD4: .word MOD71_0222F790
	thumb_func_end MOD71_0222FD9C

	thumb_func_start MOD71_0222FDD8
MOD71_0222FDD8: ; 0x0222FDD8
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r0, #0
	mov r0, #0
	add r1, sp, #0x10
	strb r0, [r1, #8]
	mov r0, #1
	strb r0, [r1, #9]
	mov r0, #3
	strb r0, [r1, #0xa]
	ldrb r2, [r1, #0xb]
	mov r0, #0xf
	bic r2, r0
	strb r2, [r1, #0xb]
	ldrb r2, [r1, #0xb]
	mov r0, #0x30
	bic r2, r0
	strb r2, [r1, #0xb]
	ldrb r2, [r1, #0xb]
	mov r0, #0xc0
	bic r2, r0
	strb r2, [r1, #0xb]
	ldr r0, _0222FED0 ; =0x00002218
	add r1, r4, #0
	add r1, #0x88
	ldr r0, [r4, r0]
	ldr r1, [r1]
	bl GetPartyMonByIndex
	bl FUN_020690E4
	add r2, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200ACF8
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5f
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #8
	str r0, [sp]
	ldr r0, _0222FED4 ; =0x00000598
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0x10
	mov r2, #1
	bl MOD71_02230F40
	mov r0, #3
	mov r1, #0x1a
	bl FUN_02012838
	ldr r1, _0222FED8 ; =0x0000065C
	mov r2, #0x11
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #0x61
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	mov r3, #0
	bl FUN_02012880
	ldr r0, _0222FED8 ; =0x0000065C
	mov r1, #0x61
	lsl r1, r1, #2
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	mov r2, #0x12
	mov r3, #1
	bl FUN_02012880
	ldr r0, _0222FED8 ; =0x0000065C
	mov r1, #0x61
	lsl r1, r1, #2
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	mov r2, #0x13
	mov r3, #2
	bl FUN_02012880
	ldr r0, _0222FED8 ; =0x0000065C
	ldr r1, [r4, r0]
	str r1, [sp, #0x10]
	sub r0, #0xa4
	add r0, r4, r0
	str r0, [sp, #0x14]
	bl MOD71_02231004
	mov r0, #0x1a
	str r0, [sp]
	mov r0, #2
	mov r2, #0
	str r0, [sp, #4]
	add r0, sp, #0x10
	mov r1, #8
	add r3, r2, #0
	bl FUN_02001C14
	mov r1, #0x66
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r1, _0222FEDC ; =MOD71_0222FEE4
	ldr r0, _0222FEE0 ; =0x00002214
	str r1, [r4, r0]
	mov r0, #0
	add sp, #0x1c
	pop {r3, r4, pc}
	nop
_0222FED0: .word 0x00002218
_0222FED4: .word 0x00000598
_0222FED8: .word 0x0000065C
_0222FEDC: .word MOD71_0222FEE4
_0222FEE0: .word 0x00002214
	thumb_func_end MOD71_0222FDD8

	thumb_func_start MOD71_0222FEE4
MOD71_0222FEE4: ; 0x0222FEE4
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0x66
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_02001C78
	cmp r0, #2
	bhi _0222FF06
	cmp r0, #0
	beq _0222FF10
	cmp r0, #1
	beq _0222FF64
	cmp r0, #2
	beq _0222FFB4
	b _02230002
_0222FF06:
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _0222FFB4
	b _02230002
_0222FF10:
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _02230008 ; =0x00000588
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0xf
	mov r2, #1
	bl MOD71_02230F40
	mov r0, #0x66
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02001C5C
	ldr r0, _0223000C ; =0x0000065C
	ldr r0, [r4, r0]
	bl FUN_02012870
	ldr r1, _02230010 ; =MOD71_0222F538
	ldr r0, _02230014 ; =0x00002214
	add sp, #0x10
	str r1, [r4, r0]
	mov r0, #3
	pop {r4, pc}
_0222FF64:
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _02230018 ; =0x000005A8
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0x14
	mov r2, #1
	bl MOD71_02230F40
	mov r0, #0x66
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02001C5C
	ldr r0, _0223000C ; =0x0000065C
	ldr r0, [r4, r0]
	bl FUN_02012870
	ldr r1, _0223001C ; =MOD71_02230020
	ldr r0, _02230014 ; =0x00002214
	str r1, [r4, r0]
	b _02230002
_0222FFB4:
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _02230008 ; =0x00000588
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0xf
	mov r2, #1
	bl MOD71_02230F40
	mov r0, #0x66
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02001C5C
	ldr r0, _0223000C ; =0x0000065C
	ldr r0, [r4, r0]
	bl FUN_02012870
	ldr r1, _02230010 ; =MOD71_0222F538
	ldr r0, _02230014 ; =0x00002214
	str r1, [r4, r0]
_02230002:
	mov r0, #0
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_02230008: .word 0x00000588
_0223000C: .word 0x0000065C
_02230010: .word MOD71_0222F538
_02230014: .word 0x00002214
_02230018: .word 0x000005A8
_0223001C: .word MOD71_02230020
	thumb_func_end MOD71_0222FEE4

	thumb_func_start MOD71_02230020
MOD71_02230020: ; 0x02230020
	push {r4, lr}
	sub sp, #0x10
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _02230070 ; =0x000005A8
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0x14
	mov r2, #1
	bl MOD71_02230F40
	add r0, r4, #0
	mov r1, #0x18
	mov r2, #2
	bl MOD71_0222F440
	ldr r1, _02230074 ; =MOD71_0223007C
	ldr r0, _02230078 ; =0x00002214
	str r1, [r4, r0]
	mov r0, #0
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_02230070: .word 0x000005A8
_02230074: .word MOD71_0223007C
_02230078: .word 0x00002214
	thumb_func_end MOD71_02230020

	thumb_func_start MOD71_0223007C
MOD71_0223007C: ; 0x0223007C
	ldr r2, [r0, #0x60]
	cmp r2, #0
	beq _022300A8
	ldr r1, [r0, #0x64]
	cmp r1, #0
	beq _022300A8
	cmp r2, #2
	bne _02230098
	cmp r1, #2
	bne _02230098
	ldr r2, _022300AC ; =MOD71_022300B8
	ldr r1, _022300B0 ; =0x00002214
	str r2, [r0, r1]
	b _0223009E
_02230098:
	ldr r2, _022300B4 ; =MOD71_0222F790
	ldr r1, _022300B0 ; =0x00002214
	str r2, [r0, r1]
_0223009E:
	mov r1, #0x18
	str r1, [r0, #0x68]
	mov r1, #0
	str r1, [r0, #0x60]
	str r1, [r0, #0x64]
_022300A8:
	mov r0, #0
	bx lr
	.align 2, 0
_022300AC: .word MOD71_022300B8
_022300B0: .word 0x00002214
_022300B4: .word MOD71_0222F790
	thumb_func_end MOD71_0223007C

	thumb_func_start MOD71_022300B8
MOD71_022300B8: ; 0x022300B8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r0, #0
	ldr r0, _022301D8 ; =0x00000438
	mov r6, #0
	add r0, r7, r0
	add r4, r7, #0
	add r5, r7, #0
	str r0, [sp, #4]
_022300CA:
	add r0, r7, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r6, r0
	beq _02230108
	mov r0, #0x37
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, _022301DC ; =0x00000692
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _022300F4
	mov r0, #0x3a
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
_022300F4:
	ldr r0, _022301E0 ; =0x0000069C
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _02230108
	mov r0, #0x3d
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
_02230108:
	add r0, r6, #7
	lsl r1, r0, #4
	ldr r0, [sp, #4]
	add r0, r0, r1
	bl FUN_0201958C
	add r0, r7, #0
	add r0, #0x8c
	ldr r0, [r0]
	sub r0, r0, #6
	cmp r6, r0
	beq _02230154
	mov r0, #0xe2
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, _022301E4 ; =0x000006F2
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _02230140
	mov r0, #0xee
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
_02230140:
	ldr r0, _022301E8 ; =0x000006FC
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _02230154
	mov r0, #0xfa
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
_02230154:
	add r0, r6, #0
	add r0, #0xd
	lsl r1, r0, #4
	ldr r0, [sp, #4]
	add r0, r0, r1
	bl FUN_0201958C
	add r6, r6, #1
	add r4, r4, #4
	add r5, #0x10
	cmp r6, #6
	blt _022300CA
	mov r0, #0xce
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0xcf
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	mov r1, #0
	bl FUN_020200A0
	add r0, r7, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r3, #0x30
	lsl r2, r0, #3
	ldr r1, _022301EC ; =0x02231220
	ldr r0, _022301F0 ; =0x000022C4
	ldr r1, [r1, r2]
	ldr r4, _022301F4 ; =0x02231224
	add r0, r7, r0
	ldr r2, [r4, r2]
	add r1, #0x10
	sub r2, r2, #6
	str r3, [sp]
	bl MOD71_02230204
	add r0, r7, #0
	add r0, #0x8c
	ldr r0, [r0]
	ldr r1, _022301EC ; =0x02231220
	lsl r2, r0, #3
	mov r0, #0x30
	str r0, [sp]
	ldr r0, _022301F8 ; =0x000022DC
	ldr r1, [r1, r2]
	add r3, r4, #0
	ldr r2, [r3, r2]
	add r0, r7, r0
	add r1, #0x10
	sub r2, r2, #6
	mov r3, #0xb0
	bl MOD71_02230204
	ldr r1, _022301FC ; =0x000022BC
	mov r0, #0
	str r0, [r7, r1]
	ldr r2, _02230200 ; =MOD71_0223029C
	sub r1, #0xa8
	str r2, [r7, r1]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022301D8: .word 0x00000438
_022301DC: .word 0x00000692
_022301E0: .word 0x0000069C
_022301E4: .word 0x000006F2
_022301E8: .word 0x000006FC
_022301EC: .word MOD71_02231220
_022301F0: .word 0x000022C4
_022301F4: .word MOD71_02231224
_022301F8: .word 0x000022DC
_022301FC: .word 0x000022BC
_02230200: .word MOD71_0223029C
	thumb_func_end MOD71_022300B8

	thumb_func_start MOD71_02230204
MOD71_02230204: ; 0x02230204
	lsl r1, r1, #0xc
	str r1, [r0]
	lsl r1, r2, #0xc
	str r1, [r0, #4]
	lsl r1, r3, #0xc
	str r1, [r0, #0xc]
	ldr r1, [sp]
	lsl r1, r1, #0xc
	str r1, [r0, #0x10]
	bx lr
	thumb_func_end MOD71_02230204

	thumb_func_start MOD71_02230218
MOD71_02230218: ; 0x02230218
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	ldr r7, [sp, #0x48]
	str r0, [sp]
	ldr r4, [r7]
	ldr r0, [r7, #0xc]
	str r1, [sp, #4]
	add r6, r3, #0
	sub r0, r0, r4
	mov r1, #0x14
	str r2, [sp, #8]
	ldr r5, [sp, #0x4c]
	bl _s32_div_f
	mul r0, r6
	add r0, r4, r0
	str r0, [sp, #0x24]
	ldr r4, [r7, #4]
	ldr r0, [r7, #0x10]
	mov r1, #0x14
	sub r0, r0, r4
	bl _s32_div_f
	mul r0, r6
	add r0, r4, r0
	str r0, [sp, #0x28]
	ldr r0, [sp]
	add r1, sp, #0x24
	bl FUN_02020044
	ldrh r0, [r5, #2]
	cmp r0, #0
	beq _02230276
	mov r0, #5
	ldr r1, [sp, #0x24]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x18]
	mov r0, #0x16
	ldr r1, [sp, #0x28]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x1c]
	ldr r0, [sp, #4]
	add r1, sp, #0x18
	bl FUN_02020044
_02230276:
	ldr r0, [r5, #0xc]
	cmp r0, #0
	beq _02230298
	mov r0, #7
	ldr r1, [sp, #0x24]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0xc]
	mov r0, #0x16
	ldr r1, [sp, #0x28]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x10]
	ldr r0, [sp, #8]
	add r1, sp, #0xc
	bl FUN_02020044
_02230298:
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD71_02230218

	thumb_func_start MOD71_0223029C
MOD71_0223029C: ; 0x0223029C
	push {r3, r4, r5, lr}
	sub sp, #8
	ldr r3, _02230370 ; =0x000022BC
	add r4, r0, #0
	ldr r0, [r4, r3]
	add r2, r3, #0
	add r0, r0, #1
	str r0, [r4, r3]
	add r0, r4, #0
	add r0, #0x88
	ldr r1, [r0]
	add r2, #8
	add r2, r4, r2
	lsl r0, r1, #2
	str r2, [sp]
	mov r2, #0x69
	lsl r2, r2, #4
	add r2, r4, r2
	lsl r1, r1, #4
	add r1, r2, r1
	mov r2, #0x37
	str r1, [sp, #4]
	lsl r2, r2, #4
	add r5, r4, r0
	add r1, r2, #0
	ldr r0, [r5, r2]
	add r1, #0x30
	add r2, #0x60
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	ldr r3, [r4, r3]
	bl MOD71_02230218
	add r0, r4, #0
	add r0, #0x8c
	ldr r3, _02230374 ; =0x000022DC
	ldr r5, [r0]
	add r1, r4, r3
	str r1, [sp]
	mov r1, #0x69
	lsl r1, r1, #4
	add r2, r4, r1
	lsl r1, r5, #4
	add r1, r2, r1
	mov r2, #0x37
	lsl r0, r5, #2
	lsl r2, r2, #4
	str r1, [sp, #4]
	add r5, r4, r0
	add r1, r2, #0
	ldr r0, [r5, r2]
	add r1, #0x30
	add r2, #0x60
	sub r3, #0x20
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	ldr r3, [r4, r3]
	bl MOD71_02230218
	ldr r1, _02230370 ; =0x000022BC
	ldr r0, [r4, r1]
	cmp r0, #0x15
	bne _02230368
	mov r0, #1
	add r2, r4, #0
	str r0, [sp]
	ldr r0, _02230378 ; =0x00000568
	sub r1, #0xa4
	add r2, #0x88
	ldr r1, [r4, r1]
	ldr r2, [r2]
	add r0, r4, r0
	mov r3, #8
	bl MOD71_0222EC5C
	mov r0, #1
	add r2, r4, #0
	str r0, [sp]
	ldr r1, _0223037C ; =0x0000221C
	add r2, #0x8c
	ldr r0, _02230380 ; =0x00000578
	ldr r2, [r2]
	ldr r1, [r4, r1]
	add r0, r4, r0
	sub r2, r2, #6
	mov r3, #8
	bl MOD71_0222EC5C
	add r1, r4, #0
	add r1, #0x8c
	ldr r1, [r1]
	add r0, r4, #0
	bl MOD71_0222E1A0
	ldr r1, _02230384 ; =MOD71_022304AC
	ldr r0, _02230388 ; =0x00002214
	str r1, [r4, r0]
	ldr r0, _0223038C ; =0x00000418
	mov r1, #1
	ldr r0, [r4, r0]
	bl FUN_020200A0
_02230368:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_02230370: .word 0x000022BC
_02230374: .word 0x000022DC
_02230378: .word 0x00000568
_0223037C: .word 0x0000221C
_02230380: .word 0x00000578
_02230384: .word MOD71_022304AC
_02230388: .word 0x00002214
_0223038C: .word 0x00000418
	thumb_func_end MOD71_0223029C

	thumb_func_start MOD71_02230390
MOD71_02230390: ; 0x02230390
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	ldr r1, _0223048C ; =0x00000568
	str r0, [sp]
	add r0, r0, r1
	bl FUN_0201958C
	ldr r1, _02230490 ; =0x00000578
	ldr r0, [sp]
	add r0, r0, r1
	bl FUN_0201958C
	ldr r6, [sp]
	ldr r1, _02230494 ; =0x00000438
	add r0, r6, #0
	add r0, r0, r1
	ldr r4, _02230498 ; =0x02231220
	mov r7, #0
	add r5, r6, #0
	str r0, [sp, #4]
_022303B8:
	mov r0, #0x69
	lsl r0, r0, #4
	ldrh r0, [r6, r0]
	cmp r0, #0
	beq _02230438
	mov r0, #0x37
	lsl r0, r0, #4
	ldr r1, [r4]
	ldr r2, [r4, #4]
	ldr r0, [r5, r0]
	add r1, #0x10
	sub r2, r2, #6
	bl MOD71_02230B70
	mov r0, #0x37
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, _0223049C ; =0x00000692
	ldrh r0, [r6, r0]
	cmp r0, #0
	beq _02230406
	mov r0, #0x3a
	lsl r0, r0, #4
	ldr r1, [r4]
	ldr r2, [r4, #4]
	ldr r0, [r5, r0]
	add r1, #0x24
	add r2, #0x10
	bl MOD71_02230B70
	mov r0, #0x3a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
_02230406:
	ldr r0, _022304A0 ; =0x0000069C
	ldr r0, [r6, r0]
	cmp r0, #0
	beq _0223042C
	mov r0, #0x3d
	lsl r0, r0, #4
	ldr r1, [r4]
	ldr r2, [r4, #4]
	ldr r0, [r5, r0]
	add r1, #0x2c
	add r2, #0x10
	bl MOD71_02230B70
	mov r0, #0x3d
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
_0223042C:
	add r0, r7, #7
	lsl r1, r0, #4
	ldr r0, [sp, #4]
	add r0, r0, r1
	bl FUN_02019220
_02230438:
	add r7, r7, #1
	add r6, #0x10
	add r4, #8
	add r5, r5, #4
	cmp r7, #0xc
	blt _022303B8
	mov r1, #0xce
	ldr r0, [sp]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r1, #1
	bl FUN_020200A0
	mov r1, #0xcf
	ldr r0, [sp]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r1, #1
	bl FUN_020200A0
	ldr r1, _02230494 ; =0x00000438
	ldr r0, [sp]
	ldr r2, [sp]
	add r0, r0, r1
	mov r1, #1
	bl MOD71_0222EF24
	ldr r1, _022304A4 ; =0x0000040C
	ldr r0, [sp]
	ldr r0, [r0, r1]
	mov r1, #0
	bl FUN_020200A0
	ldr r1, _022304A8 ; =0x00000418
	ldr r0, [sp]
	ldr r0, [r0, r1]
	mov r1, #0
	bl FUN_020200A0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223048C: .word 0x00000568
_02230490: .word 0x00000578
_02230494: .word 0x00000438
_02230498: .word MOD71_02231220
_0223049C: .word 0x00000692
_022304A0: .word 0x0000069C
_022304A4: .word 0x0000040C
_022304A8: .word 0x00000418
	thumb_func_end MOD71_02230390

	thumb_func_start MOD71_022304AC
MOD71_022304AC: ; 0x022304AC
	push {r4, lr}
	sub sp, #0x10
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	ldr r0, _02230534 ; =0x00002218
	add r1, r4, #0
	add r1, #0x88
	ldr r0, [r4, r0]
	ldr r1, [r1]
	bl GetPartyMonByIndex
	bl FUN_020690E4
	add r2, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200ACF8
	add r1, r4, #0
	ldr r0, _02230538 ; =0x0000221C
	add r1, #0x8c
	ldr r1, [r1]
	ldr r0, [r4, r0]
	sub r1, r1, #6
	bl GetPartyMonByIndex
	bl FUN_020690E4
	add r2, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_0200ACF8
	mov r3, #0x5f
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #8
	str r0, [sp]
	ldr r0, _0223053C ; =0x000005A8
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0x15
	mov r2, #1
	bl MOD71_02230F40
	ldr r1, _02230540 ; =MOD71_02230548
	ldr r0, _02230544 ; =0x00002214
	str r1, [r4, r0]
	mov r0, #0
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_02230534: .word 0x00002218
_02230538: .word 0x0000221C
_0223053C: .word 0x000005A8
_02230540: .word MOD71_02230548
_02230544: .word 0x00002214
	thumb_func_end MOD71_022304AC

	thumb_func_start MOD71_02230548
MOD71_02230548: ; 0x02230548
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0x5d
	ldr r2, _02230638 ; =0x00000658
	lsl r0, r0, #2
	add r1, r4, r2
	add r2, #0xc
	ldr r0, [r4, r0]
	add r2, r4, r2
	bl MOD71_02230FB0
	cmp r0, #0
	beq _0223056E
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _022305EE
	b _02230632
_0223056E:
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	lsl r0, r0, #4
	add r1, r4, r0
	ldr r0, _0223063C ; =0x0000069C
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _022305E6
	add r0, r4, #0
	bl MOD71_02230BC4
	cmp r0, #0
	beq _022305D4
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _02230640 ; =0x000005A8
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0x14
	mov r2, #1
	bl MOD71_02230F40
	ldr r1, _02230644 ; =MOD71_02230770
	ldr r0, _02230648 ; =0x00002214
	mov r2, #3
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #0x18
	bl MOD71_0222F440
	mov r0, #1
	str r0, [r4, #0x5c]
	b _02230632
_022305D4:
	ldr r1, _02230644 ; =MOD71_02230770
	ldr r0, _02230648 ; =0x00002214
	mov r2, #4
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #0x18
	bl MOD71_0222F440
	b _02230632
_022305E6:
	ldr r1, _0223064C ; =MOD71_02230650
	ldr r0, _02230648 ; =0x00002214
	str r1, [r4, r0]
	b _02230632
_022305EE:
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _02230640 ; =0x000005A8
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0x14
	mov r2, #1
	bl MOD71_02230F40
	ldr r1, _02230644 ; =MOD71_02230770
	ldr r0, _02230648 ; =0x00002214
	mov r2, #4
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #0x18
	bl MOD71_0222F440
_02230632:
	mov r0, #0
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_02230638: .word 0x00000658
_0223063C: .word 0x0000069C
_02230640: .word 0x000005A8
_02230644: .word MOD71_02230770
_02230648: .word 0x00002214
_0223064C: .word MOD71_02230650
	thumb_func_end MOD71_02230548

	thumb_func_start MOD71_02230650
MOD71_02230650: ; 0x02230650
	push {r4, lr}
	sub sp, #0x10
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5f
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #8
	str r0, [sp]
	ldr r0, _02230698 ; =0x000005A8
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0x24
	mov r2, #1
	bl MOD71_02230F40
	ldr r1, _0223069C ; =MOD71_022306A4
	ldr r0, _022306A0 ; =0x00002214
	str r1, [r4, r0]
	mov r0, #0
	add sp, #0x10
	pop {r4, pc}
	nop
_02230698: .word 0x000005A8
_0223069C: .word MOD71_022306A4
_022306A0: .word 0x00002214
	thumb_func_end MOD71_02230650

	thumb_func_start MOD71_022306A4
MOD71_022306A4: ; 0x022306A4
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0x5d
	ldr r2, _02230760 ; =0x00000658
	lsl r0, r0, #2
	add r1, r4, r2
	add r2, #0xc
	ldr r0, [r4, r0]
	add r2, r4, r2
	bl MOD71_02230FB0
	cmp r0, #0
	beq _022306CA
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _02230714
	b _02230758
_022306CA:
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _02230764 ; =0x000005A8
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0x14
	mov r2, #1
	bl MOD71_02230F40
	ldr r1, _02230768 ; =MOD71_02230770
	ldr r0, _0223076C ; =0x00002214
	mov r2, #3
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #0x18
	bl MOD71_0222F440
	mov r0, #1
	str r0, [r4, #0x5c]
	b _02230758
_02230714:
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _02230764 ; =0x000005A8
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0x14
	mov r2, #1
	bl MOD71_02230F40
	ldr r1, _02230768 ; =MOD71_02230770
	ldr r0, _0223076C ; =0x00002214
	mov r2, #4
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #0x18
	bl MOD71_0222F440
_02230758:
	mov r0, #0
	add sp, #0x10
	pop {r4, pc}
	nop
_02230760: .word 0x00000658
_02230764: .word 0x000005A8
_02230768: .word MOD71_02230770
_0223076C: .word 0x00002214
	thumb_func_end MOD71_022306A4

	thumb_func_start MOD71_02230770
MOD71_02230770: ; 0x02230770
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x60]
	cmp r1, #0
	beq _022307B8
	ldr r0, [r4, #0x64]
	cmp r0, #0
	beq _022307B8
	cmp r1, #3
	bne _02230798
	cmp r0, #3
	bne _02230798
	ldr r0, _022307BC ; =0x00003698
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	ldr r1, _022307C0 ; =MOD71_022307CC
	ldr r0, _022307C4 ; =0x00002214
	str r1, [r4, r0]
	b _0223079E
_02230798:
	ldr r1, _022307C8 ; =MOD71_0222F790
	ldr r0, _022307C4 ; =0x00002214
	str r1, [r4, r0]
_0223079E:
	mov r0, #0
	str r0, [r4, #0x60]
	str r0, [r4, #0x64]
	add r0, r4, #0
	bl MOD71_02230BC4
	cmp r0, #0
	beq _022307B4
	mov r0, #0x18
	str r0, [r4, #0x68]
	b _022307B8
_022307B4:
	mov r0, #0x22
	str r0, [r4, #0x68]
_022307B8:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_022307BC: .word 0x00003698
_022307C0: .word MOD71_022307CC
_022307C4: .word 0x00002214
_022307C8: .word MOD71_0222F790
	thumb_func_end MOD71_02230770

	thumb_func_start MOD71_022307CC
MOD71_022307CC: ; 0x022307CC
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_0202E288
	ldr r0, [r4, #8]
	add r3, r4, #0
	add r2, r4, #0
	ldr r1, _02230804 ; =0x00002218
	str r0, [sp]
	add r3, #0x8c
	ldr r0, [r4, r1]
	add r1, r1, #4
	add r2, #0x88
	ldr r3, [r3]
	ldr r1, [r4, r1]
	ldr r2, [r2]
	sub r3, r3, #6
	bl MOD71_022309E8
	ldr r1, _02230808 ; =MOD71_0222F790
	ldr r0, _0223080C ; =0x00002214
	str r1, [r4, r0]
	mov r0, #2
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_02230804: .word 0x00002218
_02230808: .word MOD71_0222F790
_0223080C: .word 0x00002214
	thumb_func_end MOD71_022307CC

	thumb_func_start MOD71_02230810
MOD71_02230810: ; 0x02230810
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r0, #0
	mov r0, #0
	add r1, sp, #0x10
	strb r0, [r1, #8]
	mov r0, #1
	strb r0, [r1, #9]
	mov r0, #2
	strb r0, [r1, #0xa]
	ldrb r2, [r1, #0xb]
	mov r0, #0xf
	bic r2, r0
	strb r2, [r1, #0xb]
	ldrb r2, [r1, #0xb]
	mov r0, #0x30
	bic r2, r0
	strb r2, [r1, #0xb]
	ldrb r2, [r1, #0xb]
	mov r0, #0xc0
	bic r2, r0
	strb r2, [r1, #0xb]
	add r1, r4, #0
	ldr r0, _022308F8 ; =0x0000221C
	add r1, #0x88
	ldr r1, [r1]
	ldr r0, [r4, r0]
	sub r1, r1, #6
	bl GetPartyMonByIndex
	bl FUN_020690E4
	add r2, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200ACF8
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5f
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #8
	str r0, [sp]
	ldr r0, _022308FC ; =0x00000598
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0x10
	mov r2, #1
	bl MOD71_02230F40
	mov r0, #2
	mov r1, #0x1a
	bl FUN_02012838
	ldr r1, _02230900 ; =0x0000065C
	mov r2, #0x11
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #0x61
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	mov r3, #0
	bl FUN_02012880
	ldr r0, _02230900 ; =0x0000065C
	mov r1, #0x61
	lsl r1, r1, #2
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	mov r2, #0x13
	mov r3, #1
	bl FUN_02012880
	ldr r0, _02230900 ; =0x0000065C
	ldr r1, [r4, r0]
	sub r0, #0x94
	add r0, r4, r0
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	bl MOD71_02231004
	mov r0, #0x1a
	str r0, [sp]
	mov r0, #2
	mov r2, #0
	str r0, [sp, #4]
	add r0, sp, #0x10
	mov r1, #8
	add r3, r2, #0
	bl FUN_02001C14
	mov r1, #0x66
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r1, _02230904 ; =MOD71_0223090C
	ldr r0, _02230908 ; =0x00002214
	str r1, [r4, r0]
	mov r0, #0
	add sp, #0x1c
	pop {r3, r4, pc}
	nop
_022308F8: .word 0x0000221C
_022308FC: .word 0x00000598
_02230900: .word 0x0000065C
_02230904: .word MOD71_0223090C
_02230908: .word 0x00002214
	thumb_func_end MOD71_02230810

	thumb_func_start MOD71_0223090C
MOD71_0223090C: ; 0x0223090C
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0x66
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_02001C78
	cmp r0, #0
	beq _0223092E
	cmp r0, #1
	beq _02230982
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _02230982
	b _022309D0
_0223092E:
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _022309D8 ; =0x00000588
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0xf
	mov r2, #1
	bl MOD71_02230F40
	ldr r1, _022309DC ; =MOD71_0222F538
	ldr r0, _022309E0 ; =0x00002214
	str r1, [r4, r0]
	mov r0, #0x66
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02001C5C
	ldr r0, _022309E4 ; =0x0000065C
	ldr r0, [r4, r0]
	bl FUN_02012870
	add sp, #0x10
	mov r0, #3
	pop {r4, pc}
_02230982:
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x5d
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r3, #0x5e
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	add r3, #0xc
	str r0, [sp]
	ldr r0, _022309D8 ; =0x00000588
	ldr r3, [r4, r3]
	add r0, r4, r0
	mov r1, #0xf
	mov r2, #1
	bl MOD71_02230F40
	mov r0, #0x66
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02001C5C
	ldr r0, _022309E4 ; =0x0000065C
	ldr r0, [r4, r0]
	bl FUN_02012870
	ldr r1, _022309DC ; =MOD71_0222F538
	ldr r0, _022309E0 ; =0x00002214
	str r1, [r4, r0]
_022309D0:
	mov r0, #0
	add sp, #0x10
	pop {r4, pc}
	nop
_022309D8: .word 0x00000588
_022309DC: .word MOD71_0222F538
_022309E0: .word 0x00002214
_022309E4: .word 0x0000065C
	thumb_func_end MOD71_0223090C

	thumb_func_start MOD71_022309E8
MOD71_022309E8: ; 0x022309E8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r0, [sp, #4]
	mov r0, #0x1a
	str r1, [sp, #8]
	add r6, r2, #0
	str r3, [sp, #0xc]
	ldr r5, [sp, #0x28]
	bl AllocMonZeroed
	add r7, r0, #0
	mov r0, #0x1a
	bl AllocMonZeroed
	add r4, r0, #0
	ldr r0, [sp, #4]
	add r1, r6, #0
	bl GetPartyMonByIndex
	add r1, r7, #0
	bl FUN_02069B88
	ldr r0, [sp, #8]
	ldr r1, [sp, #0xc]
	bl GetPartyMonByIndex
	add r1, r4, #0
	bl FUN_02069B88
	add r0, r4, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _02230A40
	mov r1, #0x46
	add r0, sp, #0x10
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #9
	add r2, sp, #0x10
	bl SetMonData
_02230A40:
	bl FUN_02031190
	bl FUN_0202DFA4
	add r1, r0, #0
	mov r0, #0xb
	str r0, [sp]
	add r0, r4, #0
	mov r2, #5
	mov r3, #0
	bl FUN_0208089C
	add r0, r4, #0
	bl FUN_0206AA84
	ldr r1, [r5, #0x3c]
	add r0, r7, #0
	bl FUN_02069B88
	ldr r1, [r5, #0x40]
	add r0, r4, #0
	bl FUN_02069B88
	bl FUN_02031190
	mov r1, #1
	eor r0, r1
	bl FUN_0202DFA4
	ldr r1, [r5, #0x38]
	bl FUN_0202393C
	ldr r0, [sp, #4]
	ldr r1, _02230AE0 ; =0x000001B9
	str r6, [r5, #0x2c]
	bl PartyHasMon
	cmp r0, #0
	bne _02230A98
	ldr r0, [r5, #0x10]
	bl FUN_02029EF8
	bl FUN_02029F08
_02230A98:
	ldr r0, [r5, #0x10]
	add r1, r4, #0
	bl FUN_0202C144
	ldr r0, [sp, #4]
	add r1, r6, #0
	bl GetPartyMonByIndex
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_02069B88
	ldr r0, [sp, #8]
	ldr r1, [sp, #0xc]
	bl GetPartyMonByIndex
	add r1, r0, #0
	add r0, r7, #0
	bl FUN_02069B88
	ldr r0, [r5, #0x1c]
	add r1, r4, #0
	bl MOD71_02230AE4
	ldr r0, [r5, #0x20]
	mov r1, #0x13
	bl FUN_0202A0E8
	add r0, r7, #0
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02230AE0: .word 0x000001B9
	thumb_func_end MOD71_022309E8

	thumb_func_start MOD71_02230AE4
MOD71_02230AE4: ; 0x02230AE4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r6, r0, #0
	add r4, r1, #0
	bl FUN_02031190
	mov r1, #1
	eor r0, r1
	bl FUN_0202DFA4
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #0x74
	add r2, sp, #4
	bl GetMonData
	add r0, r5, #0
	bl FUN_0202398C
	add r7, r0, #0
	add r0, r5, #0
	bl FUN_020239CC
	add r5, r0, #0
	add r0, r4, #0
	bl GetMonGender
	add r3, r0, #0
	mov r0, #0x1a
	lsl r1, r5, #0x18
	str r0, [sp]
	add r0, r7, #0
	lsr r1, r1, #0x18
	add r2, sp, #4
	bl FUN_0202945C
	add r1, r0, #0
	add r0, r6, #0
	mov r2, #4
	bl FUN_02028AD4
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD71_02230AE4

	thumb_func_start MOD71_02230B3C
MOD71_02230B3C: ; 0x02230B3C
	push {r4, lr}
	ldr r3, _02230B6C ; =0x000022B8
	add r4, r0, #0
	ldr r0, [r4, r3]
	mov r1, #6
	add r0, r0, #2
	str r0, [r4, r3]
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r3, [r4, r3]
	mov r2, #0
	bl FUN_020179E0
	mov r0, #0x5d
	ldr r3, _02230B6C ; =0x000022B8
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r3, [r4, r3]
	mov r1, #3
	mov r2, #0
	bl FUN_020179E0
	pop {r4, pc}
	.align 2, 0
_02230B6C: .word 0x000022B8
	thumb_func_end MOD71_02230B3C

	thumb_func_start MOD71_02230B70
MOD71_02230B70: ; 0x02230B70
	push {lr}
	sub sp, #0xc
	lsl r1, r1, #0xc
	str r1, [sp]
	lsl r1, r2, #0xc
	str r1, [sp, #4]
	add r1, sp, #0
	bl FUN_02020044
	add sp, #0xc
	pop {pc}
	.align 2, 0
	thumb_func_end MOD71_02230B70

	thumb_func_start MOD71_02230B88
MOD71_02230B88: ; 0x02230B88
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02230B9C ; =0x000005A8
	ldr r1, _02230BA0 ; =0x000001D9
	add r0, r4, r0
	bl FUN_0200D858
	ldr r1, _02230BA4 ; =0x000036A8
	str r0, [r4, r1]
	pop {r4, pc}
	.align 2, 0
_02230B9C: .word 0x000005A8
_02230BA0: .word 0x000001D9
_02230BA4: .word 0x000036A8
	thumb_func_end MOD71_02230B88

	thumb_func_start MOD71_02230BA8
MOD71_02230BA8: ; 0x02230BA8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02230BC0 ; =0x000036A8
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02230BBE
	bl FUN_0200DBFC
	ldr r0, _02230BC0 ; =0x000036A8
	mov r1, #0
	str r1, [r4, r0]
_02230BBE:
	pop {r4, pc}
	.align 2, 0
_02230BC0: .word 0x000036A8
	thumb_func_end MOD71_02230BA8

	thumb_func_start MOD71_02230BC4
MOD71_02230BC4: ; 0x02230BC4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _02230C00 ; =0x00002218
	mov r4, #0
	ldr r0, [r5, r0]
	bl GetPartyCount
	add r3, r4, #0
	cmp r0, #0
	ble _02230BF0
	add r1, r5, #0
	add r1, #0x88
	ldr r6, [r1]
	ldr r1, _02230C04 ; =0x00000695
_02230BE0:
	cmp r3, r6
	beq _02230BE8
	ldrb r2, [r5, r1]
	add r4, r4, r2
_02230BE8:
	add r3, r3, #1
	add r5, #0x10
	cmp r3, r0
	blt _02230BE0
_02230BF0:
	sub r0, r0, #1
	cmp r4, r0
	bne _02230BFA
	mov r0, #0
	pop {r4, r5, r6, pc}
_02230BFA:
	mov r0, #1
	pop {r4, r5, r6, pc}
	nop
_02230C00: .word 0x00002218
_02230C04: .word 0x00000695
	thumb_func_end MOD71_02230BC4

	thumb_func_start MOD71_02230C08
MOD71_02230C08: ; 0x02230C08
	ldr r1, _02230C18 ; =0x000036AC
	mov r2, #1
	str r2, [r0, r1]
	mov r2, #0
	add r1, r1, #4
	str r2, [r0, r1]
	bx lr
	nop
_02230C18: .word 0x000036AC
	thumb_func_end MOD71_02230C08

	thumb_func_start MOD71_02230C1C
MOD71_02230C1C: ; 0x02230C1C
	push {r3, lr}
	ldr r2, _02230C40 ; =0x000036AC
	ldr r1, [r0, r2]
	cmp r1, #0
	beq _02230C3E
	add r1, r2, #4
	ldr r1, [r0, r1]
	add r3, r1, #1
	add r1, r2, #4
	str r3, [r0, r1]
	ldr r1, [r0, r1]
	ldr r0, _02230C44 ; =0x00000708
	cmp r1, r0
	ble _02230C3E
	mov r0, #4
	bl FUN_020336A0
_02230C3E:
	pop {r3, pc}
	.align 2, 0
_02230C40: .word 0x000036AC
_02230C44: .word 0x00000708
	thumb_func_end MOD71_02230C1C

	thumb_func_start MOD71_02230C48
MOD71_02230C48: ; 0x02230C48
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r2, #0
	mov r2, #1
	str r2, [sp]
	mov r3, #0xa
	str r3, [sp, #4]
	mov r3, #2
	str r3, [sp, #8]
	mov r6, #8
	str r6, [sp, #0xc]
	add r5, r1, #0
	str r0, [sp, #0x14]
	str r2, [sp, #0x10]
	bl FUN_02019064
	add r0, r5, #0
	mov r1, #0
	bl FUN_02019620
	mov r2, #1
	add r1, r5, #0
	str r2, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	add r0, r6, #0
	str r0, [sp, #0xc]
	mov r0, #0x15
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	add r1, #0x10
	mov r3, #0x14
	bl FUN_02019064
	add r0, r5, #0
	add r0, #0x10
	mov r1, #0
	bl FUN_02019620
	mov r0, #0x15
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	add r0, r6, #0
	str r0, [sp, #0xc]
	mov r0, #0x29
	str r0, [sp, #0x10]
	add r1, r5, #0
	ldr r0, [sp, #0x14]
	add r1, #0x60
	mov r2, #1
	mov r3, #0x1a
	bl FUN_02019064
	add r0, r5, #0
	add r0, #0x60
	mov r1, #0
	bl FUN_02019620
	add r0, r4, #0
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x1a
	str r0, [sp, #4]
	ldr r0, [sp, #0x14]
	ldr r2, _02230E78 ; =0x000001D9
	mov r1, #0
	mov r3, #0xa
	bl FUN_0200CD68
	mov r1, #0
	str r1, [sp]
	mov r0, #0x1a
	str r0, [sp, #4]
	ldr r0, [sp, #0x14]
	ldr r2, _02230E7C ; =0x000001F7
	mov r3, #0xb
	bl FUN_0200CB00
	mov r1, #0x15
	str r1, [sp]
	mov r0, #0x14
	str r0, [sp, #4]
	mov r3, #2
	lsl r1, r1, #4
	str r3, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	add r1, r5, r1
	mov r2, #0
	bl FUN_02019064
	mov r0, #0x15
	lsl r0, r0, #4
	add r0, r5, r0
	mov r1, #0
	bl FUN_02019620
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0xe
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x28
	mov r1, #0x16
	str r0, [sp, #0x10]
	lsl r1, r1, #4
	ldr r0, [sp, #0x14]
	add r1, r5, r1
	mov r2, #0
	mov r3, #2
	bl FUN_02019064
	mov r0, #0x16
	lsl r0, r0, #4
	add r0, r5, r0
	mov r1, #0
	bl FUN_02019620
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x38
	mov r1, #0x17
	str r0, [sp, #0x10]
	lsl r1, r1, #4
	ldr r0, [sp, #0x14]
	add r1, r5, r1
	mov r2, #0
	mov r3, #2
	bl FUN_02019064
	mov r0, #0x17
	lsl r0, r0, #4
	add r0, r5, r0
	mov r1, #0
	bl FUN_02019620
	mov r0, #0x11
	str r0, [sp]
	mov r0, #0xb
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r1, #0xa4
	str r1, [sp, #0x10]
	add r1, #0xdc
	ldr r0, [sp, #0x14]
	add r1, r5, r1
	mov r2, #0
	mov r3, #0x14
	bl FUN_02019064
	mov r0, #6
	lsl r0, r0, #6
	add r0, r5, r0
	mov r1, #0
	bl FUN_02019620
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0xb
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r1, #0xe6
	str r1, [sp, #0x10]
	add r1, #0xaa
	ldr r0, [sp, #0x14]
	add r1, r5, r1
	mov r2, #0
	mov r3, #0x14
	bl FUN_02019064
	mov r0, #0x19
	lsl r0, r0, #4
	add r0, r5, r0
	mov r1, #0
	bl FUN_02019620
	ldr r4, _02230E80 ; =0x022313F4
	mov r7, #0
	mov r6, #0x33
_02230DE2:
	add r0, r7, #7
	lsl r0, r0, #4
	str r0, [sp, #0x18]
	ldrh r0, [r4, #2]
	ldr r1, [sp, #0x18]
	mov r2, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldrh r3, [r4]
	ldr r0, [sp, #0x14]
	add r1, r5, r1
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FUN_02019064
	ldr r0, [sp, #0x18]
	mov r1, #0
	add r0, r5, r0
	bl FUN_02019620
	add r7, r7, #1
	add r6, #0x10
	add r4, r4, #4
	cmp r7, #0xe
	blt _02230DE2
	ldr r4, _02230E84 ; =0x0223142C
	mov r6, #0
_02230E2C:
	add r0, r6, #0
	add r0, #0x1a
	lsl r7, r0, #4
	ldrh r0, [r4, #2]
	add r1, r5, r7
	mov r2, #4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldrh r0, [r4, #4]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	ldrh r0, [r4, #6]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldrh r0, [r4, #8]
	str r0, [sp, #0x10]
	ldrh r3, [r4]
	ldr r0, [sp, #0x14]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FUN_02019064
	add r0, r5, r7
	mov r1, #0
	bl FUN_02019620
	add r6, r6, #1
	add r4, #0xa
	cmp r6, #8
	blt _02230E2C
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_02230E78: .word 0x000001D9
_02230E7C: .word 0x000001F7
_02230E80: .word MOD71_022313F4
_02230E84: .word MOD71_0223142C
	thumb_func_end MOD71_02230C48

	thumb_func_start MOD71_02230E88
MOD71_02230E88: ; 0x02230E88
	push {r3, r4, r5, lr}
	add r4, r0, #0
	mov r5, #0
_02230E8E:
	add r0, r5, #7
	lsl r0, r0, #4
	add r0, r4, r0
	bl FUN_02019178
	add r5, r5, #1
	cmp r5, #0xe
	blt _02230E8E
	mov r5, #0
_02230EA0:
	add r0, r5, #0
	add r0, #0x1a
	lsl r0, r0, #4
	add r0, r4, r0
	bl FUN_02019178
	add r5, r5, #1
	cmp r5, #8
	blt _02230EA0
	add r0, r4, #0
	bl FUN_02019178
	add r0, r4, #0
	add r0, #0x10
	bl FUN_02019178
	add r0, r4, #0
	add r0, #0x60
	bl FUN_02019178
	mov r0, #0x15
	lsl r0, r0, #4
	add r0, r4, r0
	bl FUN_02019178
	mov r0, #0x16
	lsl r0, r0, #4
	add r0, r4, r0
	bl FUN_02019178
	mov r0, #0x17
	lsl r0, r0, #4
	add r0, r4, r0
	bl FUN_02019178
	mov r0, #6
	lsl r0, r0, #6
	add r0, r4, r0
	bl FUN_02019178
	mov r0, #0x19
	lsl r0, r0, #4
	add r0, r4, r0
	bl FUN_02019178
	pop {r3, r4, r5, pc}
	thumb_func_end MOD71_02230E88

	thumb_func_start MOD71_02230EFC
MOD71_02230EFC: ; 0x02230EFC
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r3, #0
	ldr r3, [sp, #0x20]
	add r5, r0, #0
	add r6, r1, #0
	cmp r3, #1
	bne _02230F20
	mov r0, #0
	add r2, r0, #0
	bl FUN_02002E14
	ldrb r1, [r5, #7]
	lsl r1, r1, #3
	sub r1, r1, r0
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r3, r0, #1
_02230F20:
	ldr r0, [sp, #0x24]
	mov r1, #0
	str r0, [sp]
	ldr r0, _02230F3C ; =0x000B0C00
	str r4, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, #0
	add r2, r6, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_02230F3C: .word 0x000B0C00
	thumb_func_end MOD71_02230EFC

	thumb_func_start MOD71_02230F40
MOD71_02230F40: ; 0x02230F40
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	add r1, r3, #0
	ldr r0, [sp, #0x20]
	add r2, r6, #0
	mov r3, #0x1a
	bl ReadMsgData_ExpandPlaceholders
	add r6, r0, #0
	cmp r4, #1
	bne _02230F6A
	ldr r2, _02230FA4 ; =0x000001D9
	add r0, r5, #0
	mov r1, #0
	mov r3, #0xa
	bl FUN_0200D0BC
	b _02230F76
_02230F6A:
	ldr r2, _02230FA8 ; =0x000001F7
	add r0, r5, #0
	mov r1, #0
	mov r3, #0xb
	bl FUN_0200CCA4
_02230F76:
	add r0, r5, #0
	mov r1, #0xf
	bl FUN_02019620
	mov r3, #0
	str r3, [sp]
	ldr r0, _02230FAC ; =0x0001020F
	str r3, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	str r3, [sp, #0xc]
	bl FUN_0201BDE0
	add r4, r0, #0
	add r0, r6, #0
	bl String_dtor
	add r0, r4, #0
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_02230FA4: .word 0x000001D9
_02230FA8: .word 0x000001F7
_02230FAC: .word 0x0001020F
	thumb_func_end MOD71_02230F40

	thumb_func_start MOD71_02230FB0
MOD71_02230FB0: ; 0x02230FB0
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r2, #0
	add r5, r1, #0
	mov r6, #0
	ldr r1, [r4]
	mvn r6, r6
	cmp r1, #0
	beq _02230FC8
	cmp r1, #1
	beq _02230FE0
	b _02230FF6
_02230FC8:
	mov r1, #0x1a
	str r1, [sp]
	ldr r1, _02230FFC ; =0x022313CC
	ldr r2, _02231000 ; =0x000001F7
	mov r3, #0xb
	bl FUN_02002198
	str r0, [r5]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02230FF6
_02230FE0:
	ldr r0, [r5]
	mov r1, #0x1a
	bl FUN_020021AC
	add r6, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r6, r0
	beq _02230FF6
	mov r0, #0
	str r0, [r4]
_02230FF6:
	add r0, r6, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02230FFC: .word MOD71_022313CC
_02231000: .word 0x000001F7
	thumb_func_end MOD71_02230FB0

	thumb_func_start MOD71_02231004
MOD71_02231004: ; 0x02231004
	push {r3, lr}
	ldr r2, _02231014 ; =0x000001F7
	mov r1, #0
	mov r3, #0xb
	bl FUN_0200CCA4
	pop {r3, pc}
	nop
_02231014: .word 0x000001F7
	thumb_func_end MOD71_02231004

	thumb_func_start MOD71_02231018
MOD71_02231018: ; 0x02231018
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r0, #0xc
	str r0, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _02231088 ; =0x0000014D
	add r4, r2, #0
	add r6, r1, #0
	str r0, [sp, #0x10]
	add r0, r3, #0
	add r1, r4, #0
	mov r2, #0
	mov r3, #0x13
	bl FUN_02019064
	ldr r2, _0223108C ; =0x000001F7
	add r0, r4, #0
	mov r1, #0
	mov r3, #0xb
	bl FUN_0200CCA4
	ldr r3, _02231090 ; =0x022313D4
	add r2, sp, #0x14
	add r7, r2, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r1, r6, #1
	add r0, sp, #0x14
	strh r1, [r0, #0x10]
	mov r1, #5
	strh r1, [r0, #0x12]
	ldr r0, _02231094 ; =MOD71_02231098
	mov r1, #0
	str r0, [sp, #0x18]
	add r0, r7, #0
	add r2, r1, #0
	mov r3, #0x1a
	str r5, [sp, #0x14]
	str r4, [sp, #0x20]
	bl FUN_020010A8
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	nop
_02231088: .word 0x0000014D
_0223108C: .word 0x000001F7
_02231090: .word MOD71_022313D4
_02231094: .word MOD71_02231098
	thumb_func_end MOD71_02231018

	thumb_func_start MOD71_02231098
MOD71_02231098: ; 0x02231098
	push {r3, lr}
	cmp r2, #0
	bne _022310A4
	ldr r0, _022310A8 ; =0x000005DC
	bl FUN_020054C8
_022310A4:
	pop {r3, pc}
	nop
_022310A8: .word 0x000005DC
	thumb_func_end MOD71_02231098

	.rodata
	.global MOD71_022310AC
MOD71_022310AC: ; 0x022310AC
	.byte 0x38, 0x88, 0x18, 0x68, 0xFF, 0x00, 0x00, 0x00

	.global MOD71_022310B4
MOD71_022310B4: ; 0x022310B4
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD71_022310C4
MOD71_022310C4: ; 0x022310C4
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00

	.global MOD71_022310D4
MOD71_022310D4: ; 0x022310D4
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD71_022310D8
MOD71_022310D8: ; 0x022310D8
	.byte 0x01, 0x00, 0x00, 0x00

	.global MOD71_022310DC
MOD71_022310DC: ; 0x022310DC
	.byte 0x02, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00

	.global MOD71_022310EC
MOD71_022310EC: ; 0x022310EC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD71_02231108
MOD71_02231108: ; 0x02231108
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD71_02231124
MOD71_02231124: ; 0x02231124
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD71_02231140
MOD71_02231140: ; 0x02231140
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1B, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD71_0223115C
MOD71_0223115C: ; 0x0223115C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD71_02231178
MOD71_02231178: ; 0x02231178
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1C, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD71_02231194
MOD71_02231194: ; 0x02231194
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1D, 0x04, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD71_022311B0
MOD71_022311B0: ; 0x022311B0
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD71_022311D8
MOD71_022311D8: ; 0x022311D8
	.byte 0x3F, 0x00, 0x00, 0x00

	.global MOD71_022311DC
MOD71_022311DC: ; 0x022311DC
	.byte 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x90, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0xE3, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.byte 0x16, 0x00, 0x00, 0x00

	.global MOD71_02231220
MOD71_02231220: ; 0x02231220
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD71_02231224
MOD71_02231224: ; 0x02231224
	.byte 0x20, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x48, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x70, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x48, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x70, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0xA0, 0x00, 0x00, 0x00

	.global MOD71_02231288
MOD71_02231288: ; 0x02231288
	.byte 0x04, 0x02, 0x0C, 0x0C, 0x00, 0x00, 0x02, 0x04, 0x0C, 0x0C, 0x00, 0x00, 0x07, 0x06, 0x01, 0x00
	.byte 0x00, 0x00, 0x01, 0x06, 0x07, 0x00, 0x00, 0x00, 0x05, 0x03, 0x0C, 0x0C, 0x00, 0x00, 0x03, 0x05
	.byte 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x07, 0x06, 0x01, 0x00, 0x00, 0x06, 0x07, 0x00, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x08, 0x07, 0x06
	.byte 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x05, 0x01
	.byte 0x01, 0x01, 0x00, 0x00, 0x02, 0x09, 0x08, 0x07, 0x00, 0x00, 0x08, 0x09, 0x06, 0x06, 0x00, 0x00
	.byte 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x0A, 0x09, 0x08
	.byte 0x07, 0x06, 0x05, 0x03, 0x01, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x01, 0x01
	.byte 0x01, 0x01, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x0A, 0x08, 0x06, 0x00, 0x00, 0x00
	.byte 0x0A, 0x08, 0x0C, 0x00, 0x00, 0x00, 0x08, 0x0A, 0x0C, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x07, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x0C
	.byte 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x06, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x01, 0x00
	.byte 0x00, 0x00, 0x09, 0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x0C
	.byte 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x03, 0x02
	.byte 0x01, 0x00, 0x0B, 0x09, 0x07, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x0B, 0x09, 0x07, 0x06, 0x00, 0x00, 0x07, 0x06, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD71_022313C0
MOD71_022313C0: ; 0x022313C0
	.byte 0x00, 0x01, 0x02, 0x04, 0x03, 0x05, 0x06, 0x07, 0x08, 0x00, 0x00, 0x00

	.global MOD71_022313CC
MOD71_022313CC: ; 0x022313CC
	.byte 0x00, 0x19, 0x0D, 0x06, 0x04, 0x03, 0x12, 0x01

	.global MOD71_022313D4
MOD71_022313D4: ; 0x022313D4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x20, 0x00, 0x20, 0x00, 0x00, 0x08, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD71_022313F4
MOD71_022313F4: ; 0x022313F4
	.byte 0x00, 0x00, 0x07, 0x00, 0x08, 0x00, 0x07, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x08, 0x00, 0x0C, 0x00
	.byte 0x00, 0x00, 0x11, 0x00, 0x08, 0x00, 0x11, 0x00, 0x10, 0x00, 0x07, 0x00, 0x18, 0x00, 0x07, 0x00
	.byte 0x10, 0x00, 0x0C, 0x00, 0x18, 0x00, 0x0C, 0x00, 0x10, 0x00, 0x11, 0x00, 0x18, 0x00, 0x11, 0x00
	.byte 0x04, 0x00, 0x0A, 0x00, 0x14, 0x00, 0x0A, 0x00

	.global MOD71_0223142C
MOD71_0223142C: ; 0x0223142C
	.byte 0x04, 0x00, 0x01, 0x00, 0x09, 0x00, 0x02, 0x00, 0x01, 0x00, 0x14, 0x00, 0x01, 0x00, 0x09, 0x00
	.byte 0x02, 0x00, 0x13, 0x00, 0x04, 0x00, 0x03, 0x00, 0x08, 0x00, 0x02, 0x00, 0x25, 0x00, 0x14, 0x00
	.byte 0x03, 0x00, 0x08, 0x00, 0x02, 0x00, 0x35, 0x00, 0x02, 0x00, 0x13, 0x00, 0x07, 0x00, 0x02, 0x00
	.byte 0x45, 0x00, 0x12, 0x00, 0x13, 0x00, 0x07, 0x00, 0x02, 0x00, 0x53, 0x00, 0x02, 0x00, 0x15, 0x00
	.byte 0x0C, 0x00, 0x02, 0x00, 0x61, 0x00, 0x12, 0x00, 0x15, 0x00, 0x0C, 0x00, 0x02, 0x00, 0x79, 0x00

	.data
	.bss
