    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0206EB80
FUN_0206EB80: ; 0x0206EB80
	ldr r0, _0206EB84 ; =0x00000774
	bx lr
	.balign 4
_0206EB84: .word 0x00000774

	thumb_func_start FUN_0206EB88
FUN_0206EB88: ; 0x0206EB88
	push {r4, lr}
	ldr r1, _0206EB9C ; =0x00000774
	bl AllocFromHeap
	add r4, r0, #0x0
	bl FUN_0206EBA0
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_0206EB9C: .word 0x00000774

	thumb_func_start FUN_0206EBA0
FUN_0206EBA0: ; 0x0206EBA0
	ldr r3, _0206EBAC ; =MIi_CpuClear16
	add r1, r0, #0x0
	mov r0, #0x0
	ldr r2, _0206EBB0 ; =0x00000774
	bx r3
	nop
_0206EBAC: .word MIi_CpuClear16
_0206EBB0: .word 0x00000774

	thumb_func_start FUN_0206EBB4
FUN_0206EBB4: ; 0x0206EBB4
	ldr r3, _0206EBBC ; =MI_CpuCopy8
	ldr r2, _0206EBC0 ; =0x00000774
	bx r3
	nop
_0206EBBC: .word MI_CpuCopy8
_0206EBC0: .word 0x00000774

	thumb_func_start FUN_0206EBC4
FUN_0206EBC4: ; 0x0206EBC4
	mov r1, #0x77
	lsl r1, r1, #0x4
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start FUN_0206EBCC
FUN_0206EBCC: ; 0x0206EBCC
	mov r2, #0x77
	lsl r2, r2, #0x4
	str r1, [r0, r2]
	bx lr

	thumb_func_start FUN_0206EBD4
FUN_0206EBD4: ; 0x0206EBD4
	push {r4-r6, lr}
	add r5, r2, #0x0
	add r4, r0, #0x0
	add r0, r1, #0x0
	ldr r2, [sp, #0x10]
	mov r1, #0x5
	add r6, r3, #0x0
	bl FUN_0206E7B8
	cmp r0, #0x7
	bhi _0206EC64
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0206EBF6: ; jump table (using 16-bit offset)
	.short _0206EC14 - _0206EBF6 - 2; case 0
	.short _0206EC28 - _0206EBF6 - 2; case 1
	.short _0206EC34 - _0206EBF6 - 2; case 2
	.short _0206EC58 - _0206EBF6 - 2; case 3
	.short _0206EC1C - _0206EBF6 - 2; case 4
	.short _0206EC4C - _0206EBF6 - 2; case 5
	.short _0206EC40 - _0206EBF6 - 2; case 6
	.short _0206EC06 - _0206EBF6 - 2; case 7
_0206EC06:
	mov r1, #0xa5
	lsl r1, r1, #0x2
	add r1, r4, r1
	str r1, [r5, #0x0]
	mov r1, #0x32
	str r1, [r6, #0x0]
	pop {r4-r6, pc}
_0206EC14:
	str r4, [r5, #0x0]
	mov r1, #0xa5
	str r1, [r6, #0x0]
	pop {r4-r6, pc}
_0206EC1C:
	ldr r1, _0206EC68 ; =0x000005BC
	add r1, r4, r1
	str r1, [r5, #0x0]
	mov r1, #0x40
	str r1, [r6, #0x0]
	pop {r4-r6, pc}
_0206EC28:
	ldr r1, _0206EC6C ; =0x0000051C
	add r1, r4, r1
	str r1, [r5, #0x0]
	mov r1, #0x28
	str r1, [r6, #0x0]
	pop {r4-r6, pc}
_0206EC34:
	ldr r1, _0206EC70 ; =0x000006BC
	add r1, r4, r1
	str r1, [r5, #0x0]
	mov r1, #0xf
	str r1, [r6, #0x0]
	pop {r4-r6, pc}
_0206EC40:
	ldr r1, _0206EC74 ; =0x000006F8
	add r1, r4, r1
	str r1, [r5, #0x0]
	mov r1, #0x1e
	str r1, [r6, #0x0]
	pop {r4-r6, pc}
_0206EC4C:
	ldr r1, _0206EC78 ; =0x000004EC
	add r1, r4, r1
	str r1, [r5, #0x0]
	mov r1, #0xc
	str r1, [r6, #0x0]
	pop {r4-r6, pc}
_0206EC58:
	mov r1, #0xd7
	lsl r1, r1, #0x2
	add r1, r4, r1
	str r1, [r5, #0x0]
	mov r1, #0x64
	str r1, [r6, #0x0]
_0206EC64:
	pop {r4-r6, pc}
	nop
_0206EC68: .word 0x000005BC
_0206EC6C: .word 0x0000051C
_0206EC70: .word 0x000006BC
_0206EC74: .word 0x000006F8
_0206EC78: .word 0x000004EC

	thumb_func_start FUN_0206EC7C
FUN_0206EC7C: ; 0x0206EC7C
	push {r4-r7}
	add r5, r1, #0x0
	mov r1, #0x0
	add r7, r0, #0x0
	add r4, r2, #0x0
	mov r12, r3
	mvn r1, r1
	mov r0, #0x0
	cmp r5, #0x0
	bls _0206ECCA
	add r2, r7, #0x0
	add r3, r1, #0x0
_0206EC94:
	ldrh r6, [r2, #0x0]
	cmp r4, r6
	bne _0206ECB2
	lsl r0, r0, #0x2
	add r0, r7, r0
	ldrh r2, [r0, #0x2]
	mov r1, r12
	add r2, r1, r2
	add r1, sp, #0x0
	ldrh r1, [r1, #0x10]
	cmp r2, r1
	ble _0206ECDC
	mov r0, #0x0
	pop {r4-r7}
	bx lr
_0206ECB2:
	cmp r1, r3
	bne _0206ECC2
	cmp r6, #0x0
	bne _0206ECC2
	ldrh r6, [r2, #0x2]
	cmp r6, #0x0
	bne _0206ECC2
	add r1, r0, #0x0
_0206ECC2:
	add r0, r0, #0x1
	add r2, r2, #0x4
	cmp r0, r5
	blo _0206EC94
_0206ECCA:
	mov r0, #0x0
	mvn r0, r0
	cmp r1, r0
	bne _0206ECD8
	mov r0, #0x0
	pop {r4-r7}
	bx lr
_0206ECD8:
	lsl r0, r1, #0x2
	add r0, r7, r0
_0206ECDC:
	pop {r4-r7}
	bx lr

	thumb_func_start FUN_0206ECE0
FUN_0206ECE0: ; 0x0206ECE0
	push {r4-r5, lr}
	sub sp, #0xc
	add r4, r2, #0x0
	str r3, [sp, #0x0]
	add r2, sp, #0x8
	add r3, sp, #0x4
	add r5, r1, #0x0
	bl FUN_0206EBD4
	cmp r0, #0x3
	bne _0206ED0A
	mov r0, #0x63
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x4]
	add r2, r5, #0x0
	add r3, r4, #0x0
	bl FUN_0206EC7C
	add sp, #0xc
	pop {r4-r5, pc}
_0206ED0A:
	ldr r0, _0206ED20 ; =0x000003E7
	add r2, r5, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x4]
	add r3, r4, #0x0
	bl FUN_0206EC7C
	add sp, #0xc
	pop {r4-r5, pc}
	nop
_0206ED20: .word 0x000003E7

	thumb_func_start FUN_0206ED24
FUN_0206ED24: ; 0x0206ED24
	push {r3, lr}
	bl FUN_0206ECE0
	cmp r0, #0x0
	beq _0206ED32
	mov r0, #0x1
	pop {r3, pc}
_0206ED32:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0206ED38
FUN_0206ED38: ; 0x0206ED38
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r0, #0x0
	add r5, r1, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_0206ECE0
	str r0, [sp, #0x8]
	cmp r0, #0x0
	bne _0206ED54
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_0206ED54:
	strh r5, [r0, #0x0]
	ldr r1, [sp, #0x8]
	add r2, sp, #0x8
	ldrh r0, [r1, #0x2]
	add r3, sp, #0x4
	add r0, r0, r4
	strh r0, [r1, #0x2]
	add r0, r7, #0x0
	add r1, r5, #0x0
	str r6, [sp, #0x0]
	bl FUN_0206EBD4
	sub r0, r0, #0x3
	cmp r0, #0x1
	bhi _0206ED7A
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x4]
	bl FUN_0206EF94
_0206ED7A:
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0206ED80
FUN_0206ED80: ; 0x0206ED80
	push {r3-r6}
	mov r5, #0x0
	cmp r1, #0x0
	bls _0206EDA8
	add r6, r0, #0x0
_0206ED8A:
	ldrh r4, [r6, #0x0]
	cmp r2, r4
	bne _0206EDA0
	lsl r1, r5, #0x2
	add r0, r0, r1
	ldrh r1, [r0, #0x2]
	cmp r1, r3
	bhs _0206EDAA
	mov r0, #0x0
	pop {r3-r6}
	bx lr
_0206EDA0:
	add r5, r5, #0x1
	add r6, r6, #0x4
	cmp r5, r1
	blo _0206ED8A
_0206EDA8:
	mov r0, #0x0
_0206EDAA:
	pop {r3-r6}
	bx lr
	.balign 4

	thumb_func_start FUN_0206EDB0
FUN_0206EDB0: ; 0x0206EDB0
	push {r4-r5, lr}
	sub sp, #0xc
	add r4, r2, #0x0
	str r3, [sp, #0x0]
	add r2, sp, #0x8
	add r3, sp, #0x4
	add r5, r1, #0x0
	bl FUN_0206EBD4
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x4]
	add r2, r5, #0x0
	add r3, r4, #0x0
	bl FUN_0206ED80
	add sp, #0xc
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_0206EDD4
FUN_0206EDD4: ; 0x0206EDD4
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	add r7, r1, #0x0
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl FUN_0206EDB0
	str r0, [sp, #0x8]
	cmp r0, #0x0
	bne _0206EDF0
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_0206EDF0:
	ldrh r1, [r0, #0x2]
	sub r1, r1, r5
	strh r1, [r0, #0x2]
	ldr r1, [sp, #0x8]
	ldrh r0, [r1, #0x2]
	cmp r0, #0x0
	bne _0206EE02
	mov r0, #0x0
	strh r0, [r1, #0x0]
_0206EE02:
	str r4, [sp, #0x0]
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r2, sp, #0x8
	add r3, sp, #0x4
	bl FUN_0206EBD4
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x4]
	bl FUN_0206EF48
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0206EE20
FUN_0206EE20: ; 0x0206EE20
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r3, #0x0
	bl FUN_0206ED80
	cmp r0, #0x0
	bne _0206EE34
	mov r0, #0x0
	pop {r4-r6, pc}
_0206EE34:
	ldrh r1, [r0, #0x2]
	sub r1, r1, r4
	strh r1, [r0, #0x2]
	ldrh r1, [r0, #0x2]
	cmp r1, #0x0
	bne _0206EE44
	mov r1, #0x0
	strh r1, [r0, #0x0]
_0206EE44:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0206EF48
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_0206EE50
FUN_0206EE50: ; 0x0206EE50
	push {r3, lr}
	bl FUN_0206EDB0
	cmp r0, #0x0
	beq _0206EE5E
	mov r0, #0x1
	pop {r3, pc}
_0206EE5E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0206EE64
FUN_0206EE64: ; 0x0206EE64
	cmp r1, #0x7
	bhi _0206EEC4
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0206EE74: ; jump table (using 16-bit offset)
	.short _0206EE8E - _0206EE74 - 2; case 0
	.short _0206EE9A - _0206EE74 - 2; case 1
	.short _0206EEA2 - _0206EE74 - 2; case 2
	.short _0206EEBA - _0206EE74 - 2; case 3
	.short _0206EE92 - _0206EE74 - 2; case 4
	.short _0206EEB2 - _0206EE74 - 2; case 5
	.short _0206EEAA - _0206EE74 - 2; case 6
	.short _0206EE84 - _0206EE74 - 2; case 7
_0206EE84:
	mov r1, #0xa5
	lsl r1, r1, #0x2
	add r0, r0, r1
	mov r2, #0x32
	b _0206EEC8
_0206EE8E:
	mov r2, #0xa5
	b _0206EEC8
_0206EE92:
	ldr r1, _0206EEE4 ; =0x000005BC
	mov r2, #0x40
	add r0, r0, r1
	b _0206EEC8
_0206EE9A:
	ldr r1, _0206EEE8 ; =0x0000051C
	mov r2, #0x28
	add r0, r0, r1
	b _0206EEC8
_0206EEA2:
	ldr r1, _0206EEEC ; =0x000006BC
	mov r2, #0xf
	add r0, r0, r1
	b _0206EEC8
_0206EEAA:
	ldr r1, _0206EEF0 ; =0x000006F8
	mov r2, #0x1e
	add r0, r0, r1
	b _0206EEC8
_0206EEB2:
	ldr r1, _0206EEF4 ; =0x000004EC
	mov r2, #0xc
	add r0, r0, r1
	b _0206EEC8
_0206EEBA:
	mov r1, #0xd7
	lsl r1, r1, #0x2
	add r0, r0, r1
	mov r2, #0x64
	b _0206EEC8
_0206EEC4:
	mov r0, #0x0
	bx lr
_0206EEC8:
	mov r3, #0x0
	cmp r2, #0x0
	bls _0206EEE0
_0206EECE:
	ldrh r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0206EED8
	mov r0, #0x1
	bx lr
_0206EED8:
	add r3, r3, #0x1
	add r0, r0, #0x4
	cmp r3, r2
	blo _0206EECE
_0206EEE0:
	mov r0, #0x0
	bx lr
	.balign 4
_0206EEE4: .word 0x000005BC
_0206EEE8: .word 0x0000051C
_0206EEEC: .word 0x000006BC
_0206EEF0: .word 0x000006F8
_0206EEF4: .word 0x000004EC

	thumb_func_start FUN_0206EEF8
FUN_0206EEF8: ; 0x0206EEF8
	push {r3, lr}
	add r3, r2, #0x0
	mov r2, #0x1
	bl FUN_0206EDB0
	cmp r0, #0x0
	bne _0206EF0A
	mov r0, #0x0
	pop {r3, pc}
_0206EF0A:
	ldrh r0, [r0, #0x2]
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0206EF10
FUN_0206EF10: ; 0x0206EF10
	push {r3, lr}
	mov r3, #0x1
	bl FUN_0206ED80
	cmp r0, #0x0
	bne _0206EF20
	mov r0, #0x0
	pop {r3, pc}
_0206EF20:
	ldrh r0, [r0, #0x2]
	pop {r3, pc}

	thumb_func_start FUN_0206EF24
FUN_0206EF24: ; 0x0206EF24
	push {r3}
	sub sp, #0x4
	ldrh r3, [r0, #0x0]
	add r2, sp, #0x0
	strh r3, [r2, #0x0]
	ldrh r3, [r0, #0x2]
	strh r3, [r2, #0x2]
	ldrh r3, [r1, #0x0]
	strh r3, [r0, #0x0]
	ldrh r3, [r1, #0x2]
	strh r3, [r0, #0x2]
	ldrh r0, [r2, #0x0]
	strh r0, [r1, #0x0]
	ldrh r0, [r2, #0x2]
	strh r0, [r1, #0x2]
	add sp, #0x4
	pop {r3}
	bx lr

	thumb_func_start FUN_0206EF48
FUN_0206EF48: ; 0x0206EF48
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	mov r0, #0x0
	add r7, r1, #0x0
	str r0, [sp, #0x4]
	sub r0, r7, #0x1
	str r0, [sp, #0x8]
	beq _0206EF8E
	ldr r4, [sp, #0x0]
_0206EF5C:
	ldr r0, [sp, #0x4]
	add r6, r0, #0x1
	cmp r6, r7
	bhs _0206EF80
	ldr r0, [sp, #0x0]
	lsl r1, r6, #0x2
	add r5, r0, r1
_0206EF6A:
	ldrh r0, [r4, #0x2]
	cmp r0, #0x0
	bne _0206EF78
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_0206EF24
_0206EF78:
	add r6, r6, #0x1
	add r5, r5, #0x4
	cmp r6, r7
	blo _0206EF6A
_0206EF80:
	ldr r0, [sp, #0x4]
	add r4, r4, #0x4
	add r1, r0, #0x1
	ldr r0, [sp, #0x8]
	str r1, [sp, #0x4]
	cmp r1, r0
	blo _0206EF5C
_0206EF8E:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0206EF94
FUN_0206EF94: ; 0x0206EF94
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	mov r0, #0x0
	add r7, r1, #0x0
	str r0, [sp, #0x4]
	sub r0, r7, #0x1
	str r0, [sp, #0x8]
	beq _0206EFE8
	ldr r4, [sp, #0x0]
_0206EFA8:
	ldr r0, [sp, #0x4]
	add r6, r0, #0x1
	cmp r6, r7
	bhs _0206EFDA
	ldr r0, [sp, #0x0]
	lsl r1, r6, #0x2
	add r5, r0, r1
_0206EFB6:
	ldrh r0, [r4, #0x2]
	cmp r0, #0x0
	beq _0206EFCA
	ldrh r0, [r5, #0x2]
	cmp r0, #0x0
	beq _0206EFD2
	ldrh r1, [r4, #0x0]
	ldrh r0, [r5, #0x0]
	cmp r1, r0
	bls _0206EFD2
_0206EFCA:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_0206EF24
_0206EFD2:
	add r6, r6, #0x1
	add r5, r5, #0x4
	cmp r6, r7
	blo _0206EFB6
_0206EFDA:
	ldr r0, [sp, #0x4]
	add r4, r4, #0x4
	add r1, r0, #0x1
	ldr r0, [sp, #0x8]
	str r1, [sp, #0x4]
	cmp r1, r0
	blo _0206EFA8
_0206EFE8:
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0206EFEC
FUN_0206EFEC: ; 0x0206EFEC
	push {r3-r7, lr}
	add r5, r0, #0x0
	lsl r0, r2, #0x18
	add r7, r1, #0x0
	lsr r0, r0, #0x18
	bl FUN_0206E2F0
	add r6, r0, #0x0
	ldrb r0, [r7, #0x0]
	mov r4, #0x0
	cmp r0, #0xff
	beq _0206F0BE
_0206F004:
	ldrb r0, [r7, r4]
	cmp r0, #0x7
	bhi _0206F0B6
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0206F016: ; jump table (using 16-bit offset)
	.short _0206F03A - _0206F016 - 2; case 0
	.short _0206F05C - _0206F016 - 2; case 1
	.short _0206F06E - _0206F016 - 2; case 2
	.short _0206F0A4 - _0206F016 - 2; case 3
	.short _0206F04A - _0206F016 - 2; case 4
	.short _0206F092 - _0206F016 - 2; case 5
	.short _0206F080 - _0206F016 - 2; case 6
	.short _0206F026 - _0206F016 - 2; case 7
_0206F026:
	mov r1, #0xa5
	lsl r1, r1, #0x2
	lsl r3, r4, #0x18
	add r0, r6, #0x0
	add r1, r5, r1
	mov r2, #0x7
	lsr r3, r3, #0x18
	bl FUN_0206E330
	b _0206F0B6
_0206F03A:
	lsl r3, r4, #0x18
	add r0, r6, #0x0
	add r1, r5, #0x0
	mov r2, #0x0
	lsr r3, r3, #0x18
	bl FUN_0206E330
	b _0206F0B6
_0206F04A:
	ldr r1, _0206F0C4 ; =0x000005BC
	lsl r3, r4, #0x18
	add r0, r6, #0x0
	add r1, r5, r1
	mov r2, #0x4
	lsr r3, r3, #0x18
	bl FUN_0206E330
	b _0206F0B6
_0206F05C:
	ldr r1, _0206F0C8 ; =0x0000051C
	lsl r3, r4, #0x18
	add r0, r6, #0x0
	add r1, r5, r1
	mov r2, #0x1
	lsr r3, r3, #0x18
	bl FUN_0206E330
	b _0206F0B6
_0206F06E:
	ldr r1, _0206F0CC ; =0x000006BC
	lsl r3, r4, #0x18
	add r0, r6, #0x0
	add r1, r5, r1
	mov r2, #0x2
	lsr r3, r3, #0x18
	bl FUN_0206E330
	b _0206F0B6
_0206F080:
	ldr r1, _0206F0D0 ; =0x000006F8
	lsl r3, r4, #0x18
	add r0, r6, #0x0
	add r1, r5, r1
	mov r2, #0x6
	lsr r3, r3, #0x18
	bl FUN_0206E330
	b _0206F0B6
_0206F092:
	ldr r1, _0206F0D4 ; =0x000004EC
	lsl r3, r4, #0x18
	add r0, r6, #0x0
	add r1, r5, r1
	mov r2, #0x5
	lsr r3, r3, #0x18
	bl FUN_0206E330
	b _0206F0B6
_0206F0A4:
	mov r1, #0xd7
	lsl r1, r1, #0x2
	lsl r3, r4, #0x18
	add r0, r6, #0x0
	add r1, r5, r1
	mov r2, #0x3
	lsr r3, r3, #0x18
	bl FUN_0206E330
_0206F0B6:
	add r4, r4, #0x1
	ldrb r0, [r7, r4]
	cmp r0, #0xff
	bne _0206F004
_0206F0BE:
	add r0, r6, #0x0
	pop {r3-r7, pc}
	nop
_0206F0C4: .word 0x000005BC
_0206F0C8: .word 0x0000051C
_0206F0CC: .word 0x000006BC
_0206F0D0: .word 0x000006F8
_0206F0D4: .word 0x000004EC

	thumb_func_start FUN_0206F0D8
FUN_0206F0D8: ; 0x0206F0D8
	cmp r1, #0x7
	bhi _0206F136
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0206F0E8: ; jump table (using 16-bit offset)
	.short _0206F102 - _0206F0E8 - 2; case 0
	.short _0206F10E - _0206F0E8 - 2; case 1
	.short _0206F116 - _0206F0E8 - 2; case 2
	.short _0206F12E - _0206F0E8 - 2; case 3
	.short _0206F106 - _0206F0E8 - 2; case 4
	.short _0206F126 - _0206F0E8 - 2; case 5
	.short _0206F11E - _0206F0E8 - 2; case 6
	.short _0206F0F8 - _0206F0E8 - 2; case 7
_0206F0F8:
	mov r1, #0xa5
	lsl r1, r1, #0x2
	add r0, r0, r1
	mov r3, #0x32
	b _0206F136
_0206F102:
	mov r3, #0xa5
	b _0206F136
_0206F106:
	ldr r1, _0206F144 ; =0x000005BC
	mov r3, #0x40
	add r0, r0, r1
	b _0206F136
_0206F10E:
	ldr r1, _0206F148 ; =0x0000051C
	mov r3, #0x28
	add r0, r0, r1
	b _0206F136
_0206F116:
	ldr r1, _0206F14C ; =0x000006BC
	mov r3, #0xf
	add r0, r0, r1
	b _0206F136
_0206F11E:
	ldr r1, _0206F150 ; =0x000006F8
	mov r3, #0x1e
	add r0, r0, r1
	b _0206F136
_0206F126:
	ldr r1, _0206F154 ; =0x000004EC
	mov r3, #0xc
	add r0, r0, r1
	b _0206F136
_0206F12E:
	mov r1, #0xd7
	lsl r1, r1, #0x2
	add r0, r0, r1
	mov r3, #0x64
_0206F136:
	cmp r2, r3
	blo _0206F13E
	mov r0, #0x0
	bx lr
_0206F13E:
	lsl r1, r2, #0x2
	add r0, r0, r1
	bx lr
	.balign 4
_0206F144: .word 0x000005BC
_0206F148: .word 0x0000051C
_0206F14C: .word 0x000006BC
_0206F150: .word 0x000006F8
_0206F154: .word 0x000004EC

	thumb_func_start FUN_0206F158
FUN_0206F158: ; 0x0206F158
	ldr r3, _0206F160 ; =FUN_02022610
	mov r1, #0x3
	bx r3
	nop
_0206F160: .word FUN_02022610

	thumb_func_start FUN_0206F164
FUN_0206F164: ; 0x0206F164
	push {r4, lr}
	mov r1, #0x24
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r4, #0x0
	mov r2, #0x24
	bl MIi_CpuClear16
	add r0, r4, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0206F17C
FUN_0206F17C: ; 0x0206F17C
	push {r3-r4}
	add r4, r0, r1
	ldrb r4, [r4, #0x8]
	strb r4, [r2, #0x0]
	ldrb r0, [r0, r1]
	strb r0, [r3, #0x0]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0206F18C
FUN_0206F18C: ; 0x0206F18C
	ldrh r0, [r0, #0x10]
	bx lr

	thumb_func_start FUN_0206F190
FUN_0206F190: ; 0x0206F190
	push {r3-r4}
	add r4, r0, r1
	strb r2, [r4, #0x8]
	strb r3, [r0, r1]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0206F19C
FUN_0206F19C: ; 0x0206F19C
	strh r1, [r0, #0x10]
	bx lr

	thumb_func_start FUN_0206F1A0
FUN_0206F1A0: ; 0x0206F1A0
	add r1, r0, r1
	ldrb r0, [r1, #0x19]
	strb r0, [r2, #0x0]
	ldrb r0, [r1, #0x14]
	strb r0, [r3, #0x0]
	bx lr

	thumb_func_start FUN_0206F1AC
FUN_0206F1AC: ; 0x0206F1AC
	ldrh r0, [r0, #0x1e]
	bx lr

	thumb_func_start FUN_0206F1B0
FUN_0206F1B0: ; 0x0206F1B0
	ldrh r0, [r0, #0x20]
	bx lr

	thumb_func_start FUN_0206F1B4
FUN_0206F1B4: ; 0x0206F1B4
	ldrh r0, [r0, #0x22]
	bx lr

	thumb_func_start FUN_0206F1B8
FUN_0206F1B8: ; 0x0206F1B8
	add r0, r0, r1
	strb r2, [r0, #0x19]
	strb r3, [r0, #0x14]
	bx lr

	thumb_func_start FUN_0206F1C0
FUN_0206F1C0: ; 0x0206F1C0
	push {r4-r6, lr}
	mov r4, #0x0
	add r5, r0, #0x0
	add r6, r4, #0x0
_0206F1C8:
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	add r3, r6, #0x0
	bl FUN_0206F1B8
	add r4, r4, #0x1
	cmp r4, #0x5
	blo _0206F1C8
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0206F1EC
	pop {r4-r6, pc}

	thumb_func_start FUN_0206F1E4
FUN_0206F1E4: ; 0x0206F1E4
	strh r1, [r0, #0x1e]
	strh r2, [r0, #0x20]
	bx lr
	.balign 4

	thumb_func_start FUN_0206F1EC
FUN_0206F1EC: ; 0x0206F1EC
	strh r1, [r0, #0x22]
	bx lr
