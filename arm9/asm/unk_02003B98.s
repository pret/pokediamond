    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02003B98
FUN_02003B98: ; 0x02003B98
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	bl FUN_02003D30
	add r4, r0, #0x0
	bl FUN_020C01D0
	bl FUN_020040C8
	add r0, r4, #0x0
	bl FUN_02004064
	add r0, r4, #0x0
	ldr r1, _02003C00 ; =0x000BBC00
	add r0, #0x94
	bl FUN_020C2A94
	add r1, r4, #0x0
	add r1, #0x90
	str r0, [r1, #0x0]
	add r2, r4, #0x0
	add r2, #0x90
	ldr r1, _02003C04 ; =0x02104780
	ldr r2, [r2, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl FUN_020C26F8
	add r0, r4, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	bl FUN_020C39CC
	add r0, r4, #0x0
	bl FUN_02004088
	add r0, r4, #0x0
	bl FUN_020040A4
	ldr r0, _02003C08 ; =0x02107070
	mov r1, #0x0
	str r1, [r0, #0x4]
	ldr r0, _02003C0C ; =0x000BCD4C
	str r5, [r4, r0]
	ldrh r0, [r6, #0x0]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1e
	bl FUN_02004D60
	pop {r4-r6, pc}
	nop
_02003C00: .word 0x000BBC00
_02003C04: .word 0x02104780
_02003C08: .word 0x02107070
_02003C0C: .word 0x000BCD4C

	thumb_func_start FUN_02003C10
FUN_02003C10: ; 0x02003C10
	push {r4, lr}
	bl FUN_02003D30
	add r4, r0, #0x0
	bl FUN_02003D04
	cmp r0, #0x0
	bne _02003C30
	ldr r0, _02003C3C ; =0x000BCD00
	ldr r1, [r4, r0]
	cmp r1, #0x0
	ble _02003C2C
	sub r1, r1, #0x1
	str r1, [r4, r0]
_02003C2C:
	bl FUN_02003C40
_02003C30:
	bl FUN_02005CFC
	bl FUN_020C01A0
	pop {r4, pc}
	nop
_02003C3C: .word 0x000BCD00

	thumb_func_start FUN_02003C40
FUN_02003C40: ; 0x02003C40
	push {r4, lr}
	bl FUN_02003D30
	add r4, r0, #0x0
	ldr r0, _02003CDC ; =0x02107070
	ldr r0, [r0, #0x0]
	cmp r0, #0x6
	bhi _02003CD8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02003C5C: ; jump table (using 16-bit offset)
	.short _02003CD8 - _02003C5C - 2; case 0
	.short _02003C6A - _02003C5C - 2; case 1
	.short _02003CD8 - _02003C5C - 2; case 2
	.short _02003C72 - _02003C5C - 2; case 3
	.short _02003C82 - _02003C5C - 2; case 4
	.short _02003C92 - _02003C5C - 2; case 5
	.short _02003CB0 - _02003C5C - 2; case 6
_02003C6A:
	mov r0, #0x2
	bl FUN_02003CE8
	pop {r4, pc}
_02003C72:
	bl FUN_02005404
	cmp r0, #0x0
	bne _02003CD8
	mov r0, #0x2
	bl FUN_02003CE8
	pop {r4, pc}
_02003C82:
	bl FUN_02005404
	cmp r0, #0x0
	bne _02003CD8
	mov r0, #0x2
	bl FUN_02003CE8
	pop {r4, pc}
_02003C92:
	bl FUN_02005404
	cmp r0, #0x0
	bne _02003CD8
	bl FUN_02004D94
	cmp r0, #0x0
	bne _02003CD8
	bl FUN_020040DC
	ldr r0, _02003CE0 ; =0x000BCD0E
	ldrh r0, [r4, r0]
	bl FUN_0200521C
	pop {r4, pc}
_02003CB0:
	bl FUN_02005404
	cmp r0, #0x0
	bne _02003CD8
	bl FUN_02004D94
	cmp r0, #0x0
	bne _02003CD8
	bl FUN_020040DC
	ldr r0, _02003CE0 ; =0x000BCD0E
	ldrh r0, [r4, r0]
	bl FUN_0200521C
	ldr r1, _02003CE4 ; =0x000BCD08
	mov r0, #0x7f
	ldr r1, [r4, r1]
	mov r2, #0x0
	bl FUN_0200538C
_02003CD8:
	pop {r4, pc}
	nop
_02003CDC: .word 0x02107070
_02003CE0: .word 0x000BCD0E
_02003CE4: .word 0x000BCD08

	thumb_func_start FUN_02003CE8
FUN_02003CE8: ; 0x02003CE8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	ldr r1, _02003CFC ; =0x000BCCFC
	mov r2, #0x0
	strh r2, [r0, r1]
	ldr r0, _02003D00 ; =0x02107070
	str r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4
_02003CFC: .word 0x000BCCFC
_02003D00: .word 0x02107070

	thumb_func_start FUN_02003D04
FUN_02003D04: ; 0x02003D04
	push {r4, lr}
	bl FUN_02003D30
	add r4, r0, #0x0
	mov r0, #0x2
	bl FUN_020048BC
	cmp r0, #0x0
	beq _02003D1A
	mov r0, #0x1
	pop {r4, pc}
_02003D1A:
	ldr r0, _02003D2C ; =0x000BCD12
	ldrh r0, [r4, r0]
	cmp r0, #0x0
	beq _02003D26
	mov r0, #0x1
	pop {r4, pc}
_02003D26:
	mov r0, #0x0
	pop {r4, pc}
	nop
_02003D2C: .word 0x000BCD12

	thumb_func_start FUN_02003D30
FUN_02003D30: ; 0x02003D30
	ldr r0, _02003D34 ; =0x02107078
	bx lr
	.balign 4
_02003D34: .word 0x02107078

	thumb_func_start FUN_02003D38
FUN_02003D38: ; 0x02003D38
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	cmp r4, #0x27
	bls _02003D46
	b _02003E92
_02003D46:
	add r1, r4, r4
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02003D52: ; jump table (using 16-bit offset)
	.short _02003DA8 - _02003D52 - 2; case 0
	.short _02003DAE - _02003D52 - 2; case 1
	.short _02003DB4 - _02003D52 - 2; case 2
	.short _02003DBA - _02003D52 - 2; case 3
	.short _02003DC0 - _02003D52 - 2; case 4
	.short _02003DA2 - _02003D52 - 2; case 5
	.short _02003DC6 - _02003D52 - 2; case 6
	.short _02003DCC - _02003D52 - 2; case 7
	.short _02003DD2 - _02003D52 - 2; case 8
	.short _02003DD8 - _02003D52 - 2; case 9
	.short _02003DDE - _02003D52 - 2; case 10
	.short _02003DE4 - _02003D52 - 2; case 11
	.short _02003DEA - _02003D52 - 2; case 12
	.short _02003DF0 - _02003D52 - 2; case 13
	.short _02003DF6 - _02003D52 - 2; case 14
	.short _02003DFC - _02003D52 - 2; case 15
	.short _02003E02 - _02003D52 - 2; case 16
	.short _02003E08 - _02003D52 - 2; case 17
	.short _02003E0E - _02003D52 - 2; case 18
	.short _02003E14 - _02003D52 - 2; case 19
	.short _02003E1A - _02003D52 - 2; case 20
	.short _02003E20 - _02003D52 - 2; case 21
	.short _02003E26 - _02003D52 - 2; case 22
	.short _02003E2C - _02003D52 - 2; case 23
	.short _02003E32 - _02003D52 - 2; case 24
	.short _02003E38 - _02003D52 - 2; case 25
	.short _02003E3E - _02003D52 - 2; case 26
	.short _02003E44 - _02003D52 - 2; case 27
	.short _02003E4A - _02003D52 - 2; case 28
	.short _02003E50 - _02003D52 - 2; case 29
	.short _02003E56 - _02003D52 - 2; case 30
	.short _02003E5C - _02003D52 - 2; case 31
	.short _02003E62 - _02003D52 - 2; case 32
	.short _02003E68 - _02003D52 - 2; case 33
	.short _02003E6E - _02003D52 - 2; case 34
	.short _02003E74 - _02003D52 - 2; case 35
	.short _02003E7A - _02003D52 - 2; case 36
	.short _02003E80 - _02003D52 - 2; case 37
	.short _02003E86 - _02003D52 - 2; case 38
	.short _02003E8C - _02003D52 - 2; case 39
_02003DA2:
	ldr r1, _02003E9C ; =0x000BCCFE
	add r0, r0, r1
	pop {r4, pc}
_02003DA8:
	ldr r1, _02003EA0 ; =0x000BBCB8
	add r0, r0, r1
	pop {r4, pc}
_02003DAE:
	ldr r1, _02003EA4 ; =0x000BBCBC
	add r0, r0, r1
	pop {r4, pc}
_02003DB4:
	ldr r1, _02003EA8 ; =0x000BBCC0
	add r0, r0, r1
	pop {r4, pc}
_02003DBA:
	ldr r1, _02003EAC ; =0x000BBCE0
	add r0, r0, r1
	pop {r4, pc}
_02003DC0:
	ldr r1, _02003EB0 ; =0x000BCCE0
	add r0, r0, r1
	pop {r4, pc}
_02003DC6:
	ldr r1, _02003EB4 ; =0x000BCD00
	add r0, r0, r1
	pop {r4, pc}
_02003DCC:
	ldr r1, _02003EB8 ; =0x000BCD04
	add r0, r0, r1
	pop {r4, pc}
_02003DD2:
	ldr r1, _02003EBC ; =0x000BCD08
	add r0, r0, r1
	pop {r4, pc}
_02003DD8:
	ldr r1, _02003EC0 ; =0x000BCD0C
	add r0, r0, r1
	pop {r4, pc}
_02003DDE:
	ldr r1, _02003EC4 ; =0x000BCD0E
	add r0, r0, r1
	pop {r4, pc}
_02003DE4:
	ldr r1, _02003EC8 ; =0x000BCD10
	add r0, r0, r1
	pop {r4, pc}
_02003DEA:
	ldr r1, _02003ECC ; =0x000BCD11
	add r0, r0, r1
	pop {r4, pc}
_02003DF0:
	ldr r1, _02003ED0 ; =0x000BCD12
	add r0, r0, r1
	pop {r4, pc}
_02003DF6:
	ldr r1, _02003ED4 ; =0x000BCD14
	add r0, r0, r1
	pop {r4, pc}
_02003DFC:
	ldr r1, _02003ED8 ; =0x000BCD15
	add r0, r0, r1
	pop {r4, pc}
_02003E02:
	ldr r1, _02003EDC ; =0x000BCD16
	add r0, r0, r1
	pop {r4, pc}
_02003E08:
	ldr r1, _02003EE0 ; =0x000BCD17
	add r0, r0, r1
	pop {r4, pc}
_02003E0E:
	ldr r1, _02003EE4 ; =0x000BCD18
	add r0, r0, r1
	pop {r4, pc}
_02003E14:
	ldr r1, _02003EE8 ; =0x000BCD19
	add r0, r0, r1
	pop {r4, pc}
_02003E1A:
	ldr r1, _02003EEC ; =0x000BCD1A
	add r0, r0, r1
	pop {r4, pc}
_02003E20:
	ldr r1, _02003EF0 ; =0x000BCD1B
	add r0, r0, r1
	pop {r4, pc}
_02003E26:
	ldr r1, _02003EF4 ; =0x000BCD1C
	add r0, r0, r1
	pop {r4, pc}
_02003E2C:
	ldr r1, _02003EF8 ; =0x000BCD20
	add r0, r0, r1
	pop {r4, pc}
_02003E32:
	ldr r1, _02003EFC ; =0x000BCD24
	add r0, r0, r1
	pop {r4, pc}
_02003E38:
	ldr r1, _02003F00 ; =0x000BCD28
	add r0, r0, r1
	pop {r4, pc}
_02003E3E:
	ldr r1, _02003F04 ; =0x000BCD2C
	add r0, r0, r1
	pop {r4, pc}
_02003E44:
	ldr r1, _02003F08 ; =0x000BCD30
	add r0, r0, r1
	pop {r4, pc}
_02003E4A:
	ldr r1, _02003F0C ; =0x000BCD34
	add r0, r0, r1
	pop {r4, pc}
_02003E50:
	ldr r1, _02003F10 ; =0x000BCD38
	add r0, r0, r1
	pop {r4, pc}
_02003E56:
	ldr r1, _02003F14 ; =0x000BCD39
	add r0, r0, r1
	pop {r4, pc}
_02003E5C:
	ldr r1, _02003F18 ; =0x000BCD3A
	add r0, r0, r1
	pop {r4, pc}
_02003E62:
	ldr r1, _02003F1C ; =0x000BCD3C
	add r0, r0, r1
	pop {r4, pc}
_02003E68:
	ldr r1, _02003F20 ; =0x000BCD40
	add r0, r0, r1
	pop {r4, pc}
_02003E6E:
	ldr r1, _02003F24 ; =0x000BCD48
	add r0, r0, r1
	pop {r4, pc}
_02003E74:
	ldr r1, _02003F28 ; =0x000BCD4C
	add r0, r0, r1
	pop {r4, pc}
_02003E7A:
	ldr r1, _02003F2C ; =0x000BCD50
	add r0, r0, r1
	pop {r4, pc}
_02003E80:
	ldr r1, _02003F30 ; =0x000BCD54
	add r0, r0, r1
	pop {r4, pc}
_02003E86:
	ldr r1, _02003F34 ; =0x000BCD58
	add r0, r0, r1
	pop {r4, pc}
_02003E8C:
	ldr r1, _02003F38 ; =0x000BCD5C
	add r0, r0, r1
	pop {r4, pc}
_02003E92:
	bl ErrorHandling
	mov r0, #0x0
	pop {r4, pc}
	nop
_02003E9C: .word 0x000BCCFE
_02003EA0: .word 0x000BBCB8
_02003EA4: .word 0x000BBCBC
_02003EA8: .word 0x000BBCC0
_02003EAC: .word 0x000BBCE0
_02003EB0: .word 0x000BCCE0
_02003EB4: .word 0x000BCD00
_02003EB8: .word 0x000BCD04
_02003EBC: .word 0x000BCD08
_02003EC0: .word 0x000BCD0C
_02003EC4: .word 0x000BCD0E
_02003EC8: .word 0x000BCD10
_02003ECC: .word 0x000BCD11
_02003ED0: .word 0x000BCD12
_02003ED4: .word 0x000BCD14
_02003ED8: .word 0x000BCD15
_02003EDC: .word 0x000BCD16
_02003EE0: .word 0x000BCD17
_02003EE4: .word 0x000BCD18
_02003EE8: .word 0x000BCD19
_02003EEC: .word 0x000BCD1A
_02003EF0: .word 0x000BCD1B
_02003EF4: .word 0x000BCD1C
_02003EF8: .word 0x000BCD20
_02003EFC: .word 0x000BCD24
_02003F00: .word 0x000BCD28
_02003F04: .word 0x000BCD2C
_02003F08: .word 0x000BCD30
_02003F0C: .word 0x000BCD34
_02003F10: .word 0x000BCD38
_02003F14: .word 0x000BCD39
_02003F18: .word 0x000BCD3A
_02003F1C: .word 0x000BCD3C
_02003F20: .word 0x000BCD40
_02003F24: .word 0x000BCD48
_02003F28: .word 0x000BCD4C
_02003F2C: .word 0x000BCD50
_02003F30: .word 0x000BCD54
_02003F34: .word 0x000BCD58
_02003F38: .word 0x000BCD5C

	thumb_func_start FUN_02003F3C
FUN_02003F3C: ; 0x02003F3C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02003D30
	add r0, #0x90
	ldr r0, [r0, #0x0]
	bl FUN_020C290C
	add r4, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	bne _02003F5A
	bl ErrorHandling
_02003F5A:
	cmp r5, #0x0
	beq _02003F60
	str r4, [r5, #0x0]
_02003F60:
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02003F64
FUN_02003F64: ; 0x02003F64
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	add r0, #0x90
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	bl FUN_020C2828
	pop {r4, pc}

	thumb_func_start FUN_02003F78
FUN_02003F78: ; 0x02003F78
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	add r1, r0, #0x0
	add r1, #0x90
	ldr r1, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_020C36A8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02003F90
FUN_02003F90: ; 0x02003F90
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	add r1, r0, #0x0
	add r1, #0x90
	ldr r1, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_020C3674
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02003FA8
FUN_02003FA8: ; 0x02003FA8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02003D30
	add r2, r0, #0x0
	add r2, #0x90
	ldr r2, [r2, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020C35E0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02003FC4
FUN_02003FC4: ; 0x02003FC4
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	add r1, r0, #0x0
	add r1, #0x90
	ldr r1, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_020C360C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02003FDC
FUN_02003FDC: ; 0x02003FDC
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	add r1, r0, #0x0
	add r1, #0x90
	ldr r1, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_020C3640
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02003FF4
FUN_02003FF4: ; 0x02003FF4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02003D30
	add r4, r0, #0x0
	cmp r5, #0x9
	blt _02004008
	bl ErrorHandling
	mov r5, #0x0
_02004008:
	ldr r0, _02004014 ; =0x000BBC94
	add r1, r4, r0
	lsl r0, r5, #0x2
	add r0, r1, r0
	pop {r3-r5, pc}
	nop
_02004014: .word 0x000BBC94

	thumb_func_start FUN_02004018
FUN_02004018: ; 0x02004018
	push {r3, lr}
	cmp r0, #0x7
	bhi _0200405A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0200402A: ; jump table (using 16-bit offset)
	.short _0200403E - _0200402A - 2; case 0
	.short _0200403A - _0200402A - 2; case 1
	.short _02004042 - _0200402A - 2; case 2
	.short _02004046 - _0200402A - 2; case 3
	.short _0200404A - _0200402A - 2; case 4
	.short _0200404E - _0200402A - 2; case 5
	.short _02004052 - _0200402A - 2; case 6
	.short _02004056 - _0200402A - 2; case 7
_0200403A:
	mov r0, #0x0
	pop {r3, pc}
_0200403E:
	mov r0, #0x1
	pop {r3, pc}
_02004042:
	mov r0, #0x2
	pop {r3, pc}
_02004046:
	mov r0, #0x3
	pop {r3, pc}
_0200404A:
	mov r0, #0x4
	pop {r3, pc}
_0200404E:
	mov r0, #0x5
	pop {r3, pc}
_02004052:
	mov r0, #0x6
	pop {r3, pc}
_02004056:
	mov r0, #0x7
	pop {r3, pc}
_0200405A:
	bl ErrorHandling
	mov r0, #0x3
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02004064
FUN_02004064: ; 0x02004064
	push {r4, lr}
	ldr r2, _02004080 ; =0x000BCD60
	mov r1, #0x0
	add r4, r0, #0x0
	bl Call_FillMemWithValue
	ldr r0, _02004084 ; =0x000BCD1C
	mov r1, #0x0
_02004074:
	add r1, r1, #0x1
	str r1, [r4, r0]
	add r4, r4, #0x4
	cmp r1, #0x7
	blt _02004074
	pop {r4, pc}
	.balign 4
_02004080: .word 0x000BCD60
_02004084: .word 0x000BCD1C

	thumb_func_start FUN_02004088
FUN_02004088: ; 0x02004088
	push {r3-r5, lr}
	ldr r1, _020040A0 ; =0x000BBC94
	mov r4, #0x0
	add r5, r0, r1
_02004090:
	add r0, r5, #0x0
	bl FUN_020C0F80
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x9
	blt _02004090
	pop {r3-r5, pc}
	.balign 4
_020040A0: .word 0x000BBC94

	thumb_func_start FUN_020040A4
FUN_020040A4: ; 0x020040A4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _020040C0 ; =0x000BCD1C
	add r0, r4, r0
	bl FUN_02003F3C
	mov r0, #0x0
	bl FUN_02003F78
	ldr r0, _020040C4 ; =0x000BCD20
	add r0, r4, r0
	bl FUN_02003F3C
	pop {r4, pc}
	.balign 4
_020040C0: .word 0x000BCD1C
_020040C4: .word 0x000BCD20

	thumb_func_start FUN_020040C8
FUN_020040C8: ; 0x020040C8
	push {r3, lr}
	bl MIC_Init
	mov r0, #0x1
	bl PM_SetAmp
	mov r0, #0x2
	bl PM_SetAmpGain
	pop {r3, pc}

	thumb_func_start FUN_020040DC
FUN_020040DC: ; 0x020040DC
	push {r3, lr}
	mov r0, #0x7
	mov r1, #0x0
	bl FUN_020C1040
	mov r0, #0x7
	bl FUN_02003FF4
	bl FUN_020C0F68
	pop {r3, pc}
	.balign 4
