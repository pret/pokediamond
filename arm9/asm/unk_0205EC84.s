    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0205EC84
FUN_0205EC84: ; 0x0205EC84
	ldr r3, _0205EC88 ; =FUN_020462E4
	bx r3
	.balign 4
_0205EC88: .word FUN_020462E4

	thumb_func_start FUN_0205EC8C
FUN_0205EC8C: ; 0x0205EC8C
	ldr r3, _0205EC90 ; =FUN_0204630C
	bx r3
	.balign 4
_0205EC90: .word FUN_0204630C

	thumb_func_start FUN_0205EC94
FUN_0205EC94: ; 0x0205EC94
	ldr r3, _0205EC98 ; =FUN_020462B8
	bx r3
	.balign 4
_0205EC98: .word FUN_020462B8

	thumb_func_start FUN_0205EC9C
FUN_0205EC9C: ; 0x0205EC9C
	push {r3, lr}
	cmp r1, #0x0
	beq _0205ECB6
	cmp r1, #0x1
	beq _0205ECAC
	cmp r1, #0x2
	beq _0205ECC0
	b _0205ECCA
_0205ECAC:
	lsl r1, r2, #0x10
	lsr r1, r1, #0x10
	bl FUN_0205EC84
	b _0205ECCE
_0205ECB6:
	lsl r1, r2, #0x10
	lsr r1, r1, #0x10
	bl FUN_0205EC8C
	b _0205ECCE
_0205ECC0:
	lsl r1, r2, #0x10
	lsr r1, r1, #0x10
	bl FUN_0205EC94
	pop {r3, pc}
_0205ECCA:
	bl ErrorHandling
_0205ECCE:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205ECD4
FUN_0205ECD4: ; 0x0205ECD4
	ldr r3, _0205ECDC ; =FUN_0205EC84
	mov r1, #0x96
	lsl r1, r1, #0x4
	bx r3
	.balign 4
_0205ECDC: .word FUN_0205EC84

	thumb_func_start FUN_0205ECE0
FUN_0205ECE0: ; 0x0205ECE0
	ldr r3, _0205ECE8 ; =FUN_0205EC94
	mov r1, #0x96
	lsl r1, r1, #0x4
	bx r3
	.balign 4
_0205ECE8: .word FUN_0205EC94

	thumb_func_start FUN_0205ECEC
FUN_0205ECEC: ; 0x0205ECEC
	ldr r3, _0205ECF4 ; =FUN_0205EC94
	ldr r1, _0205ECF8 ; =0x0000098D
	bx r3
	nop
_0205ECF4: .word FUN_0205EC94
_0205ECF8: .word 0x0000098D

	thumb_func_start FUN_0205ECFC
FUN_0205ECFC: ; 0x0205ECFC
	ldr r3, _0205ED04 ; =FUN_0205EC84
	ldr r1, _0205ED08 ; =0x00000964
	bx r3
	nop
_0205ED04: .word FUN_0205EC84
_0205ED08: .word 0x00000964

	thumb_func_start FUN_0205ED0C
FUN_0205ED0C: ; 0x0205ED0C
	ldr r3, _0205ED14 ; =FUN_0205EC94
	ldr r1, _0205ED18 ; =0x00000964
	bx r3
	nop
_0205ED14: .word FUN_0205EC94
_0205ED18: .word 0x00000964

	thumb_func_start FUN_0205ED1C
FUN_0205ED1C: ; 0x0205ED1C
	ldr r3, _0205ED24 ; =FUN_0205EC84
	ldr r1, _0205ED28 ; =0x00000961
	bx r3
	nop
_0205ED24: .word FUN_0205EC84
_0205ED28: .word 0x00000961

	thumb_func_start FUN_0205ED2C
FUN_0205ED2C: ; 0x0205ED2C
	ldr r3, _0205ED34 ; =FUN_0205EC8C
	ldr r1, _0205ED38 ; =0x00000961
	bx r3
	nop
_0205ED34: .word FUN_0205EC8C
_0205ED38: .word 0x00000961

	thumb_func_start FUN_0205ED3C
FUN_0205ED3C: ; 0x0205ED3C
	ldr r3, _0205ED44 ; =FUN_0205EC94
	ldr r1, _0205ED48 ; =0x00000961
	bx r3
	nop
_0205ED44: .word FUN_0205EC94
_0205ED48: .word 0x00000961

	thumb_func_start FUN_0205ED4C
FUN_0205ED4C: ; 0x0205ED4C
	ldr r3, _0205ED54 ; =FUN_0205EC84
	ldr r1, _0205ED58 ; =0x00000965
	bx r3
	nop
_0205ED54: .word FUN_0205EC84
_0205ED58: .word 0x00000965

	thumb_func_start FUN_0205ED5C
FUN_0205ED5C: ; 0x0205ED5C
	ldr r3, _0205ED64 ; =FUN_0205EC8C
	ldr r1, _0205ED68 ; =0x00000965
	bx r3
	nop
_0205ED64: .word FUN_0205EC8C
_0205ED68: .word 0x00000965

	thumb_func_start FUN_0205ED6C
FUN_0205ED6C: ; 0x0205ED6C
	ldr r3, _0205ED74 ; =FUN_0205EC94
	ldr r1, _0205ED78 ; =0x00000965
	bx r3
	nop
_0205ED74: .word FUN_0205EC94
_0205ED78: .word 0x00000965

	thumb_func_start FUN_0205ED7C
FUN_0205ED7C: ; 0x0205ED7C
	ldr r3, _0205ED84 ; =FUN_0205EC84
	ldr r1, _0205ED88 ; =0x0000096D
	bx r3
	nop
_0205ED84: .word FUN_0205EC84
_0205ED88: .word 0x0000096D

	thumb_func_start FUN_0205ED8C
FUN_0205ED8C: ; 0x0205ED8C
	ldr r3, _0205ED94 ; =FUN_0205EC8C
	ldr r1, _0205ED98 ; =0x0000096D
	bx r3
	nop
_0205ED94: .word FUN_0205EC8C
_0205ED98: .word 0x0000096D

	thumb_func_start FUN_0205ED9C
FUN_0205ED9C: ; 0x0205ED9C
	ldr r3, _0205EDA4 ; =FUN_0205EC94
	ldr r1, _0205EDA8 ; =0x0000096D
	bx r3
	nop
_0205EDA4: .word FUN_0205EC94
_0205EDA8: .word 0x0000096D

	thumb_func_start FUN_0205EDAC
FUN_0205EDAC: ; 0x0205EDAC
	ldr r3, _0205EDB4 ; =FUN_0205EC84
	ldr r1, _0205EDB8 ; =0x0000096E
	bx r3
	nop
_0205EDB4: .word FUN_0205EC84
_0205EDB8: .word 0x0000096E

	thumb_func_start FUN_0205EDBC
FUN_0205EDBC: ; 0x0205EDBC
	ldr r3, _0205EDC4 ; =FUN_0205EC84
	ldr r1, _0205EDC8 ; =0x0000096F
	bx r3
	nop
_0205EDC4: .word FUN_0205EC84
_0205EDC8: .word 0x0000096F

	thumb_func_start FUN_0205EDCC
FUN_0205EDCC: ; 0x0205EDCC
	ldr r3, _0205EDD4 ; =FUN_0205EC84
	mov r1, #0x97
	lsl r1, r1, #0x4
	bx r3
	.balign 4
_0205EDD4: .word FUN_0205EC84

	thumb_func_start FUN_0205EDD8
FUN_0205EDD8: ; 0x0205EDD8
	ldr r3, _0205EDE0 ; =FUN_0205EC84
	ldr r1, _0205EDE4 ; =0x00000971
	bx r3
	nop
_0205EDE0: .word FUN_0205EC84
_0205EDE4: .word 0x00000971

	thumb_func_start FUN_0205EDE8
FUN_0205EDE8: ; 0x0205EDE8
	ldr r3, _0205EDF0 ; =FUN_0205EC84
	ldr r1, _0205EDF4 ; =0x00000972
	bx r3
	nop
_0205EDF0: .word FUN_0205EC84
_0205EDF4: .word 0x00000972

	thumb_func_start FUN_0205EDF8
FUN_0205EDF8: ; 0x0205EDF8
	ldr r3, _0205EE00 ; =FUN_0205EC84
	ldr r1, _0205EE04 ; =0x00000973
	bx r3
	nop
_0205EE00: .word FUN_0205EC84
_0205EE04: .word 0x00000973

	thumb_func_start FUN_0205EE08
FUN_0205EE08: ; 0x0205EE08
	push {r3, lr}
	cmp r1, #0x4
	bhi _0205EE4A
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0205EE1A: ; jump table (using 16-bit offset)
	.short _0205EE24 - _0205EE1A - 2; case 0
	.short _0205EE2C - _0205EE1A - 2; case 1
	.short _0205EE34 - _0205EE1A - 2; case 2
	.short _0205EE3C - _0205EE1A - 2; case 3
	.short _0205EE44 - _0205EE1A - 2; case 4
_0205EE24:
	ldr r1, _0205EE4C ; =0x00000968
	bl FUN_0205EC84
	pop {r3, pc}
_0205EE2C:
	ldr r1, _0205EE50 ; =0x00000969
	bl FUN_0205EC84
	pop {r3, pc}
_0205EE34:
	ldr r1, _0205EE54 ; =0x0000096A
	bl FUN_0205EC84
	pop {r3, pc}
_0205EE3C:
	ldr r1, _0205EE58 ; =0x0000096B
	bl FUN_0205EC84
	pop {r3, pc}
_0205EE44:
	ldr r1, _0205EE5C ; =0x0000096C
	bl FUN_0205EC84
_0205EE4A:
	pop {r3, pc}
	.balign 4
_0205EE4C: .word 0x00000968
_0205EE50: .word 0x00000969
_0205EE54: .word 0x0000096A
_0205EE58: .word 0x0000096B
_0205EE5C: .word 0x0000096C

	thumb_func_start FUN_0205EE60
FUN_0205EE60: ; 0x0205EE60
	push {r3, lr}
	cmp r1, #0x4
	bhi _0205EEA2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0205EE72: ; jump table (using 16-bit offset)
	.short _0205EE7C - _0205EE72 - 2; case 0
	.short _0205EE84 - _0205EE72 - 2; case 1
	.short _0205EE8C - _0205EE72 - 2; case 2
	.short _0205EE94 - _0205EE72 - 2; case 3
	.short _0205EE9C - _0205EE72 - 2; case 4
_0205EE7C:
	ldr r1, _0205EEA4 ; =0x00000968
	bl FUN_0205EC94
	pop {r3, pc}
_0205EE84:
	ldr r1, _0205EEA8 ; =0x00000969
	bl FUN_0205EC94
	pop {r3, pc}
_0205EE8C:
	ldr r1, _0205EEAC ; =0x0000096A
	bl FUN_0205EC94
	pop {r3, pc}
_0205EE94:
	ldr r1, _0205EEB0 ; =0x0000096B
	bl FUN_0205EC94
	pop {r3, pc}
_0205EE9C:
	ldr r1, _0205EEB4 ; =0x0000096C
	bl FUN_0205EC94
_0205EEA2:
	pop {r3, pc}
	.balign 4
_0205EEA4: .word 0x00000968
_0205EEA8: .word 0x00000969
_0205EEAC: .word 0x0000096A
_0205EEB0: .word 0x0000096B
_0205EEB4: .word 0x0000096C

	thumb_func_start FUN_0205EEB8
FUN_0205EEB8: ; 0x0205EEB8
	push {r3, lr}
	mov r2, #0x0
	cmp r1, #0x5
	bhi _0205EF0A
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0205EECC: ; jump table (using 16-bit offset)
	.short _0205EF0A - _0205EECC - 2; case 0
	.short _0205EED8 - _0205EECC - 2; case 1
	.short _0205EEE2 - _0205EECC - 2; case 2
	.short _0205EEEE - _0205EECC - 2; case 3
	.short _0205EEF8 - _0205EECC - 2; case 4
	.short _0205EF02 - _0205EECC - 2; case 5
_0205EED8:
	ldr r1, _0205EF10 ; =0x0000097F
	bl FUN_0205EC94
	add r2, r0, #0x0
	b _0205EF0A
_0205EEE2:
	mov r1, #0x26
	lsl r1, r1, #0x6
	bl FUN_0205EC94
	add r2, r0, #0x0
	b _0205EF0A
_0205EEEE:
	ldr r1, _0205EF14 ; =0x00000981
	bl FUN_0205EC94
	add r2, r0, #0x0
	b _0205EF0A
_0205EEF8:
	ldr r1, _0205EF18 ; =0x00000982
	bl FUN_0205EC94
	add r2, r0, #0x0
	b _0205EF0A
_0205EF02:
	ldr r1, _0205EF1C ; =0x00000983
	bl FUN_0205EC94
	add r2, r0, #0x0
_0205EF0A:
	add r0, r2, #0x0
	pop {r3, pc}
	nop
_0205EF10: .word 0x0000097F
_0205EF14: .word 0x00000981
_0205EF18: .word 0x00000982
_0205EF1C: .word 0x00000983

	thumb_func_start FUN_0205EF20
FUN_0205EF20: ; 0x0205EF20
	push {r4-r6, lr}
	add r4, r1, #0x0
	ldr r1, _0205F0E4 ; =0x00000132
	add r6, r0, #0x0
	mov r5, #0x0
	cmp r4, r1
	bgt _0205EF7E
	blt _0205EF32
	b _0205F036
_0205EF32:
	cmp r4, #0xc9
	bgt _0205EF60
	blt _0205EF3A
	b _0205F084
_0205EF3A:
	cmp r4, #0x4b
	bgt _0205EF58
	add r1, r4, #0x0
	sub r1, #0x48
	bmi _0205EF5E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0205EF50: ; jump table (using 16-bit offset)
	.short _0205F06A - _0205EF50 - 2; case 0
	.short _0205F06A - _0205EF50 - 2; case 1
	.short _0205F06A - _0205EF50 - 2; case 2
	.short _0205F06A - _0205EF50 - 2; case 3
_0205EF58:
	cmp r4, #0xb9
	bne _0205EF5E
	b _0205F0D2
_0205EF5E:
	b _0205F0E0
_0205EF60:
	add r2, r1, #0x0
	sub r2, #0x32
	cmp r4, r2
	bgt _0205EF76
	sub r1, #0x32
	cmp r4, r1
	blt _0205EF70
	b _0205F09E
_0205EF70:
	cmp r4, #0xfb
	beq _0205F018
	b _0205F0E0
_0205EF76:
	sub r0, r1, #0x1
	cmp r4, r0
	beq _0205F036
	b _0205F0E0
_0205EF7E:
	add r2, r1, #0x0
	add r2, #0x5d
	cmp r4, r2
	bgt _0205EFC8
	add r2, r1, #0x0
	add r2, #0x5d
	cmp r4, r2
	blt _0205EF90
	b _0205F0B8
_0205EF90:
	add r2, r1, #0x1
	cmp r4, r2
	bgt _0205EF9E
	add r0, r2, #0x0
	cmp r4, r0
	beq _0205F036
	b _0205F0E0
_0205EF9E:
	add r1, r1, #0x2
	sub r1, r4, r1
	cmp r1, #0xa
	bhi _0205EFD6
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0205EFB2: ; jump table (using 16-bit offset)
	.short _0205F036 - _0205EFB2 - 2; case 0
	.short _0205F036 - _0205EFB2 - 2; case 1
	.short _0205F036 - _0205EFB2 - 2; case 2
	.short _0205F0E0 - _0205EFB2 - 2; case 3
	.short _0205EFFC - _0205EFB2 - 2; case 4
	.short _0205F0E0 - _0205EFB2 - 2; case 5
	.short _0205EFE0 - _0205EFB2 - 2; case 6
	.short _0205F0E0 - _0205EFB2 - 2; case 7
	.short _0205EFEE - _0205EFB2 - 2; case 8
	.short _0205F0E0 - _0205EFB2 - 2; case 9
	.short _0205F00A - _0205EFB2 - 2; case 10
_0205EFC8:
	ldr r0, _0205F0E8 ; =0x000001EE
	cmp r4, r0
	bgt _0205EFD8
	bge _0205F036
	sub r0, #0x48
	cmp r4, r0
	beq _0205F026
_0205EFD6:
	b _0205F0E0
_0205EFD8:
	add r0, r0, #0x3
	cmp r4, r0
	beq _0205F036
	b _0205F0E0
_0205EFE0:
	ldr r1, _0205F0EC ; =0x00000984
	bl FUN_0205EC94
	cmp r0, #0x1
	bne _0205F0E0
	ldr r5, _0205F0F0 ; =0x0000042E
	b _0205F0E0
_0205EFEE:
	ldr r1, _0205F0EC ; =0x00000984
	bl FUN_0205EC94
	cmp r0, #0x1
	bne _0205F0E0
	ldr r5, _0205F0F4 ; =0x00000429
	b _0205F0E0
_0205EFFC:
	ldr r1, _0205F0F8 ; =0x0000098E
	bl FUN_0205EC94
	cmp r0, #0x1
	bne _0205F0E0
	ldr r5, _0205F0F0 ; =0x0000042E
	b _0205F0E0
_0205F00A:
	ldr r1, _0205F0FC ; =0x0000098F
	bl FUN_0205EC94
	cmp r0, #0x1
	bne _0205F0E0
	ldr r5, _0205F0F0 ; =0x0000042E
	b _0205F0E0
_0205F018:
	ldr r1, _0205F100 ; =0x00000995
	bl FUN_0205EC94
	cmp r0, #0x1
	bne _0205F0E0
	ldr r5, _0205F104 ; =0x0000042D
	b _0205F0E0
_0205F026:
	ldr r1, _0205F108 ; =0x00000993
	add r0, r6, #0x0
	bl FUN_0205EC94
	cmp r0, #0x1
	bne _0205F0E0
	ldr r5, _0205F10C ; =0x0000044A
	b _0205F0E0
_0205F036:
	ldr r1, _0205F110 ; =0x00000985
	add r0, r6, #0x0
	bl FUN_0205EC94
	cmp r0, #0x1
	bne _0205F054
	bl IsNighttime
	cmp r0, #0x0
	bne _0205F050
	mov r5, #0xfe
	lsl r5, r5, #0x2
	b _0205F0E0
_0205F050:
	ldr r5, _0205F114 ; =0x00000415
	b _0205F0E0
_0205F054:
	ldr r0, _0205F118 ; =0x00000131
	cmp r4, r0
	bne _0205F0E0
	ldr r1, _0205F11C ; =0x00000986
	add r0, r6, #0x0
	bl FUN_0205EC94
	cmp r0, #0x1
	bne _0205F0E0
	ldr r5, _0205F120 ; =0x0000042B
	b _0205F0E0
_0205F06A:
	ldr r1, _0205F124 ; =0x00000987
	bl FUN_0205EC94
	cmp r0, #0x1
	bne _0205F0E0
	bl IsNighttime
	cmp r0, #0x0
	bne _0205F080
	ldr r5, _0205F128 ; =0x000003F5
	b _0205F0E0
_0205F080:
	ldr r5, _0205F12C ; =0x00000412
	b _0205F0E0
_0205F084:
	ldr r1, _0205F130 ; =0x00000988
	bl FUN_0205EC94
	cmp r0, #0x1
	bne _0205F0E0
	bl IsNighttime
	cmp r0, #0x0
	bne _0205F09A
	ldr r5, _0205F134 ; =0x000003FF
	b _0205F0E0
_0205F09A:
	ldr r5, _0205F138 ; =0x0000041C
	b _0205F0E0
_0205F09E:
	ldr r1, _0205F13C ; =0x00000989
	bl FUN_0205EC94
	cmp r0, #0x1
	bne _0205F0E0
	bl IsNighttime
	cmp r0, #0x0
	bne _0205F0B4
	ldr r5, _0205F140 ; =0x000003EE
	b _0205F0E0
_0205F0B4:
	ldr r5, _0205F144 ; =0x0000040B
	b _0205F0E0
_0205F0B8:
	ldr r1, _0205F148 ; =0x0000098A
	bl FUN_0205EC94
	cmp r0, #0x1
	bne _0205F0E0
	bl IsNighttime
	cmp r0, #0x0
	bne _0205F0CE
	ldr r5, _0205F140 ; =0x000003EE
	b _0205F0E0
_0205F0CE:
	ldr r5, _0205F144 ; =0x0000040B
	b _0205F0E0
_0205F0D2:
	ldr r1, _0205F14C ; =0x0000098B
	add r0, r6, #0x0
	bl FUN_0205EC94
	cmp r0, #0x1
	bne _0205F0E0
	ldr r5, _0205F150 ; =0x000003E9
_0205F0E0:
	add r0, r5, #0x0
	pop {r4-r6, pc}
	.balign 4
_0205F0E4: .word 0x00000132
_0205F0E8: .word 0x000001EE
_0205F0EC: .word 0x00000984
_0205F0F0: .word 0x0000042E
_0205F0F4: .word 0x00000429
_0205F0F8: .word 0x0000098E
_0205F0FC: .word 0x0000098F
_0205F100: .word 0x00000995
_0205F104: .word 0x0000042D
_0205F108: .word 0x00000993
_0205F10C: .word 0x0000044A
_0205F110: .word 0x00000985
_0205F114: .word 0x00000415
_0205F118: .word 0x00000131
_0205F11C: .word 0x00000986
_0205F120: .word 0x0000042B
_0205F124: .word 0x00000987
_0205F128: .word 0x000003F5
_0205F12C: .word 0x00000412
_0205F130: .word 0x00000988
_0205F134: .word 0x000003FF
_0205F138: .word 0x0000041C
_0205F13C: .word 0x00000989
_0205F140: .word 0x000003EE
_0205F144: .word 0x0000040B
_0205F148: .word 0x0000098A
_0205F14C: .word 0x0000098B
_0205F150: .word 0x000003E9

	thumb_func_start FUN_0205F154
FUN_0205F154: ; 0x0205F154
	ldr r3, _0205F15C ; =FUN_0205EC84
	ldr r1, _0205F160 ; =0x00000966
	bx r3
	nop
_0205F15C: .word FUN_0205EC84
_0205F160: .word 0x00000966

	thumb_func_start FUN_0205F164
FUN_0205F164: ; 0x0205F164
	ldr r3, _0205F16C ; =FUN_0205EC8C
	ldr r1, _0205F170 ; =0x00000966
	bx r3
	nop
_0205F16C: .word FUN_0205EC8C
_0205F170: .word 0x00000966

	thumb_func_start FUN_0205F174
FUN_0205F174: ; 0x0205F174
	ldr r3, _0205F17C ; =FUN_0205EC94
	ldr r1, _0205F180 ; =0x00000966
	bx r3
	nop
_0205F17C: .word FUN_0205EC94
_0205F180: .word 0x00000966

	thumb_func_start FUN_0205F184
FUN_0205F184: ; 0x0205F184
	ldr r3, _0205F18C ; =FUN_0205EC94
	ldr r1, _0205F190 ; =0x00000978
	bx r3
	nop
_0205F18C: .word FUN_0205EC94
_0205F190: .word 0x00000978

	thumb_func_start FUN_0205F194
FUN_0205F194: ; 0x0205F194
	ldr r3, _0205F19C ; =FUN_0205EC94
	ldr r1, _0205F1A0 ; =0x00000992
	bx r3
	nop
_0205F19C: .word FUN_0205EC94
_0205F1A0: .word 0x00000992

	thumb_func_start FUN_0205F1A4
FUN_0205F1A4: ; 0x0205F1A4
	ldr r3, _0205F1AC ; =FUN_0205EC94
	ldr r1, _0205F1B0 ; =0x0000097D
	bx r3
	nop
_0205F1AC: .word FUN_0205EC94
_0205F1B0: .word 0x0000097D

	thumb_func_start FUN_0205F1B4
FUN_0205F1B4: ; 0x0205F1B4
	ldr r3, _0205F1BC ; =FUN_0205EC94
	ldr r1, _0205F1C0 ; =0x0000097E
	bx r3
	nop
_0205F1BC: .word FUN_0205EC94
_0205F1C0: .word 0x0000097E

	thumb_func_start FUN_0205F1C4
FUN_0205F1C4: ; 0x0205F1C4
	ldr r3, _0205F1CC ; =FUN_0205EC84
	ldr r1, _0205F1D0 ; =0x0000097C
	bx r3
	nop
_0205F1CC: .word FUN_0205EC84
_0205F1D0: .word 0x0000097C

	thumb_func_start FUN_0205F1D4
FUN_0205F1D4: ; 0x0205F1D4
	ldr r3, _0205F1DC ; =FUN_0205EC8C
	ldr r1, _0205F1E0 ; =0x0000097C
	bx r3
	nop
_0205F1DC: .word FUN_0205EC8C
_0205F1E0: .word 0x0000097C

	thumb_func_start FUN_0205F1E4
FUN_0205F1E4: ; 0x0205F1E4
	ldr r3, _0205F1EC ; =FUN_0205EC94
	ldr r1, _0205F1F0 ; =0x0000097C
	bx r3
	nop
_0205F1EC: .word FUN_0205EC94
_0205F1F0: .word 0x0000097C

	thumb_func_start FUN_0205F1F4
FUN_0205F1F4: ; 0x0205F1F4
	ldr r3, _0205F1FC ; =FUN_0205EC84
	ldr r1, _0205F200 ; =0x00000967
	bx r3
	nop
_0205F1FC: .word FUN_0205EC84
_0205F200: .word 0x00000967

	thumb_func_start FUN_0205F204
FUN_0205F204: ; 0x0205F204
	ldr r3, _0205F20C ; =FUN_0205EC8C
	ldr r1, _0205F210 ; =0x00000967
	bx r3
	nop
_0205F20C: .word FUN_0205EC8C
_0205F210: .word 0x00000967

	thumb_func_start FUN_0205F214
FUN_0205F214: ; 0x0205F214
	ldr r3, _0205F21C ; =FUN_0205EC94
	ldr r1, _0205F220 ; =0x00000967
	bx r3
	nop
_0205F21C: .word FUN_0205EC94
_0205F220: .word 0x00000967

	thumb_func_start FUN_0205F224
FUN_0205F224: ; 0x0205F224
	ldr r3, _0205F22C ; =FUN_0205EC84
	ldr r1, _0205F230 ; =0x00000979
	bx r3
	nop
_0205F22C: .word FUN_0205EC84
_0205F230: .word 0x00000979

	thumb_func_start FUN_0205F234
FUN_0205F234: ; 0x0205F234
	ldr r3, _0205F23C ; =FUN_0205EC8C
	ldr r1, _0205F240 ; =0x00000979
	bx r3
	nop
_0205F23C: .word FUN_0205EC8C
_0205F240: .word 0x00000979

	thumb_func_start FUN_0205F244
FUN_0205F244: ; 0x0205F244
	ldr r3, _0205F24C ; =FUN_0205EC94
	ldr r1, _0205F250 ; =0x00000979
	bx r3
	nop
_0205F24C: .word FUN_0205EC94
_0205F250: .word 0x00000979

	thumb_func_start FUN_0205F254
FUN_0205F254: ; 0x0205F254
	ldr r3, _0205F25C ; =FUN_0205EC8C
	ldr r1, _0205F260 ; =0x00000994
	bx r3
	nop
_0205F25C: .word FUN_0205EC8C
_0205F260: .word 0x00000994

	thumb_func_start FUN_0205F264
FUN_0205F264: ; 0x0205F264
	ldr r3, _0205F26C ; =FUN_0205EC9C
	ldr r2, _0205F270 ; =0x00000962
	bx r3
	nop
_0205F26C: .word FUN_0205EC9C
_0205F270: .word 0x00000962

	thumb_func_start FUN_0205F274
FUN_0205F274: ; 0x0205F274
	ldr r3, _0205F27C ; =FUN_0205EC84
	ldr r1, _0205F280 ; =0x0000097A
	bx r3
	nop
_0205F27C: .word FUN_0205EC84
_0205F280: .word 0x0000097A

	thumb_func_start FUN_0205F284
FUN_0205F284: ; 0x0205F284
	ldr r3, _0205F28C ; =FUN_0205EC8C
	ldr r1, _0205F290 ; =0x0000097A
	bx r3
	nop
_0205F28C: .word FUN_0205EC8C
_0205F290: .word 0x0000097A

	thumb_func_start FUN_0205F294
FUN_0205F294: ; 0x0205F294
	ldr r3, _0205F29C ; =FUN_0205EC94
	ldr r1, _0205F2A0 ; =0x0000097A
	bx r3
	nop
_0205F29C: .word FUN_0205EC94
_0205F2A0: .word 0x0000097A

	thumb_func_start FUN_0205F2A4
FUN_0205F2A4: ; 0x0205F2A4
	ldr r3, _0205F2AC ; =FUN_0205EC84
	ldr r1, _0205F2B0 ; =0x0000097B
	bx r3
	nop
_0205F2AC: .word FUN_0205EC84
_0205F2B0: .word 0x0000097B

	thumb_func_start FUN_0205F2B4
FUN_0205F2B4: ; 0x0205F2B4
	ldr r3, _0205F2BC ; =FUN_0205EC8C
	ldr r1, _0205F2C0 ; =0x0000097B
	bx r3
	nop
_0205F2BC: .word FUN_0205EC8C
_0205F2C0: .word 0x0000097B

	thumb_func_start FUN_0205F2C4
FUN_0205F2C4: ; 0x0205F2C4
	ldr r3, _0205F2CC ; =FUN_0205EC94
	ldr r1, _0205F2D0 ; =0x0000097B
	bx r3
	nop
_0205F2CC: .word FUN_0205EC94
_0205F2D0: .word 0x0000097B

	thumb_func_start FUN_0205F2D4
FUN_0205F2D4: ; 0x0205F2D4
	ldr r3, _0205F2DC ; =FUN_0205EC9C
	ldr r2, _0205F2E0 ; =0x00000963
	bx r3
	nop
_0205F2DC: .word FUN_0205EC9C
_0205F2E0: .word 0x00000963

	thumb_func_start FUN_0205F2E4
FUN_0205F2E4: ; 0x0205F2E4
	push {r4-r6, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	cmp r4, #0x45
	blo _0205F2F4
	bl ErrorHandling
_0205F2F4:
	mov r2, #0x9b
	lsl r2, r2, #0x4
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, r2
	bl FUN_0205EC9C
	pop {r4-r6, pc}

	thumb_func_start FUN_0205F304
FUN_0205F304: ; 0x0205F304
	ldr r3, _0205F30C ; =FUN_0205EC84
	ldr r1, _0205F310 ; =0x0000098C
	bx r3
	nop
_0205F30C: .word FUN_0205EC84
_0205F310: .word 0x0000098C
