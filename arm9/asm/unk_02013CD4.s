    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02013CD4
FUN_02013CD4: ; 0x02013CD4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r1, #0x18
	bl FUN_02016998
	add r4, r0, #0x0
	bne _02013CE8
	bl ErrorHandling
_02013CE8:
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0xc]
	bl FUN_02013F68
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x4]
	ldr r0, [r5, #0x4]
	ldr r1, [r5, #0xc]
	bl FUN_02013F98
	str r0, [r4, #0x8]
	ldr r0, [r5, #0x4]
	str r0, [r4, #0xc]
	ldr r0, [r5, #0x8]
	ldr r1, [r5, #0xc]
	bl FUN_02013FC8
	str r0, [r4, #0x10]
	ldr r0, [r5, #0x8]
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02013D18
FUN_02013D18: ; 0x02013D18
	push {r4, lr}
	add r4, r0, #0x0
	bne _02013D22
	bl ErrorHandling
_02013D22:
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02013D2C
	bl ErrorHandling
_02013D2C:
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	bne _02013D36
	bl ErrorHandling
_02013D36:
	ldr r0, [r4, #0x10]
	cmp r0, #0x0
	bne _02013D40
	bl ErrorHandling
_02013D40:
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	ldr r0, [r4, #0x8]
	bl FUN_02016A18
	ldr r0, [r4, #0x10]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02013D5C
FUN_02013D5C: ; 0x02013D5C
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, _02013D90 ; =0x04000444
	mov r6, #0x0
	str r6, [r0, #0x0]
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	ble _02013D86
	add r4, r6, #0x0
_02013D6E:
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	ldr r1, [r0, #0x20]
	cmp r1, #0x0
	beq _02013D7C
	bl FUN_020140D8
_02013D7C:
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0x40
	cmp r6, r0
	blt _02013D6E
_02013D86:
	ldr r0, _02013D94 ; =0x04000448
	mov r1, #0x1
	str r1, [r0, #0x0]
	pop {r4-r6, pc}
	nop
_02013D90: .word 0x04000444
_02013D94: .word 0x04000448

	thumb_func_start FUN_02013D98
FUN_02013D98: ; 0x02013D98
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02014024
	add r4, r0, #0x0
	bne _02013DAA
	bl ErrorHandling
_02013DAA:
	ldr r0, [r5, #0x4]
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _02013DB6
	bl ErrorHandling
_02013DB6:
	ldr r0, [r5, #0x4]
	bl FUN_0201407C
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02013DC6
	bl ErrorHandling
_02013DC6:
	ldr r0, [r5, #0x4]
	ldr r1, [r4, #0x0]
	add r2, r4, #0x4
	bl FUN_020140A4
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02013DD4
FUN_02013DD4: ; 0x02013DD4
	push {r4, lr}
	ldr r1, _02013DE8 ; =0x021064BC
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r1, #0x0]
	blx r1
	add r0, r4, #0x0
	bl FUN_02013F50
	pop {r4, pc}
	.balign 4
_02013DE8: .word 0x021064BC

	thumb_func_start FUN_02013DEC
FUN_02013DEC: ; 0x02013DEC
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02013E12
	add r4, r6, #0x0
_02013DFA:
	ldr r1, [r5, #0x8]
	ldr r0, [r1, r4]
	cmp r0, #0x0
	beq _02013E08
	add r0, r1, r4
	bl FUN_02013DD4
_02013E08:
	ldr r0, [r5, #0xc]
	add r6, r6, #0x1
	add r4, #0x28
	cmp r6, r0
	blt _02013DFA
_02013E12:
	pop {r4-r6, pc}

	thumb_func_start FUN_02013E14
FUN_02013E14: ; 0x02013E14
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02014050
	add r4, r0, #0x0
	bne _02013E26
	bl ErrorHandling
_02013E26:
	ldr r0, [r5, #0x8]
	bl FUN_02014090
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02013E36
	bl ErrorHandling
_02013E36:
	ldr r0, [r5, #0x4]
	ldr r1, [r4, #0x0]
	add r2, r4, #0x4
	bl FUN_020140B4
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02013E44
FUN_02013E44: ; 0x02013E44
	push {r4, lr}
	ldr r1, _02013E58 ; =0x021064C4
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r1, #0x0]
	blx r1
	add r0, r4, #0x0
	bl FUN_02013F5C
	pop {r4, pc}
	.balign 4
_02013E58: .word 0x021064C4

	thumb_func_start FUN_02013E5C
FUN_02013E5C: ; 0x02013E5C
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x14]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02013E82
	add r4, r6, #0x0
_02013E6A:
	ldr r1, [r5, #0x10]
	ldr r0, [r1, r4]
	cmp r0, #0x0
	beq _02013E78
	add r0, r1, r4
	bl FUN_02013E44
_02013E78:
	ldr r0, [r5, #0x14]
	add r6, r6, #0x1
	add r4, #0x18
	cmp r6, r0
	blt _02013E6A
_02013E82:
	pop {r4-r6, pc}

	thumb_func_start FUN_02013E84
FUN_02013E84: ; 0x02013E84
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_02013FF8
	add r4, r0, #0x0
	bne _02013E96
	bl ErrorHandling
_02013E96:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02014218
	mov r0, #0x1
	str r0, [r4, #0x1c]
	str r0, [r4, #0x20]
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02013EA8
FUN_02013EA8: ; 0x02013EA8
	ldr r3, _02013EAC ; =FUN_02013F30
	bx r3
	.balign 4
_02013EAC: .word FUN_02013F30

	thumb_func_start FUN_02013EB0
FUN_02013EB0: ; 0x02013EB0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02013EBE
	bl ErrorHandling
_02013EBE:
	str r4, [r5, #0x20]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02013EC4
FUN_02013EC4: ; 0x02013EC4
	strh r1, [r0, #0x0]
	strh r2, [r0, #0x2]
	bx lr
	.balign 4

	thumb_func_start FUN_02013ECC
FUN_02013ECC: ; 0x02013ECC
	ldrh r1, [r0, #0x2]
	ldrh r0, [r0, #0x0]
	lsl r1, r1, #0x10
	orr r0, r1
	bx lr
	.balign 4

	thumb_func_start FUN_02013ED8
FUN_02013ED8: ; 0x02013ED8
	strh r1, [r0, #0x4]
	strh r2, [r0, #0x6]
	bx lr
	.balign 4

	thumb_func_start FUN_02013EE0
FUN_02013EE0: ; 0x02013EE0
	str r1, [r0, #0xc]
	str r2, [r0, #0x10]
	bx lr
	.balign 4

	thumb_func_start FUN_02013EE8
FUN_02013EE8: ; 0x02013EE8
	strh r1, [r0, #0x8]
	strh r2, [r0, #0xa]
	bx lr
	.balign 4

	thumb_func_start FUN_02013EF0
FUN_02013EF0: ; 0x02013EF0
	ldrh r1, [r0, #0xa]
	ldrh r0, [r0, #0x8]
	lsl r1, r1, #0x10
	orr r0, r1
	bx lr
	.balign 4

	thumb_func_start FUN_02013EFC
FUN_02013EFC: ; 0x02013EFC
	str r1, [r0, #0x14]
	bx lr

	thumb_func_start FUN_02013F00
FUN_02013F00: ; 0x02013F00
	ldr r0, [r0, #0x14]
	bx lr

	thumb_func_start FUN_02013F04
FUN_02013F04: ; 0x02013F04
	add r0, #0x3e
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02013F0C
FUN_02013F0C: ; 0x02013F0C
	strh r1, [r0, #0x3c]
	bx lr

	thumb_func_start FUN_02013F10
FUN_02013F10: ; 0x02013F10
	str r1, [r0, #0x24]
	bx lr

	thumb_func_start FUN_02013F14
FUN_02013F14: ; 0x02013F14
	str r1, [r0, #0x28]
	bx lr

	thumb_func_start FUN_02013F18
FUN_02013F18: ; 0x02013F18
	str r1, [r0, #0x2c]
	bx lr

	thumb_func_start FUN_02013F1C
FUN_02013F1C: ; 0x02013F1C
	str r1, [r0, #0x30]
	bx lr

	thumb_func_start FUN_02013F20
FUN_02013F20: ; 0x02013F20
	cmp r1, #0x0
	bne _02013F28
	str r2, [r0, #0x34]
	bx lr
_02013F28:
	str r2, [r0, #0x38]
	bx lr

	thumb_func_start FUN_02013F2C
FUN_02013F2C: ; 0x02013F2C
	str r1, [r0, #0x18]
	bx lr

	thumb_func_start FUN_02013F30
FUN_02013F30: ; 0x02013F30
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0x40
	bl memset
	add r0, r4, #0x0
	mov r1, #0x1f
	add r0, #0x3e
	strb r1, [r0, #0x0]
	ldr r0, _02013F4C ; =0x00007FFF
	strh r0, [r4, #0x3c]
	pop {r4, pc}
	nop
_02013F4C: .word 0x00007FFF

	thumb_func_start FUN_02013F50
FUN_02013F50: ; 0x02013F50
	ldr r3, _02013F58 ; =FUN_020B1A24
	mov r1, #0x0
	stmia r0!, {r1}
	bx r3
	.balign 4
_02013F58: .word FUN_020B1A24

	thumb_func_start FUN_02013F5C
FUN_02013F5C: ; 0x02013F5C
	ldr r3, _02013F64 ; =FUN_020B19DC
	mov r1, #0x0
	stmia r0!, {r1}
	bx r3
	.balign 4
_02013F64: .word FUN_020B19DC

	thumb_func_start FUN_02013F68
FUN_02013F68: ; 0x02013F68
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r0, r1, #0x0
	lsl r1, r6, #0x6
	bl FUN_02016998
	add r7, r0, #0x0
	bne _02013F7C
	bl ErrorHandling
_02013F7C:
	mov r4, #0x0
	cmp r6, #0x0
	ble _02013F92
	add r5, r7, #0x0
_02013F84:
	add r0, r5, #0x0
	bl FUN_02013F30
	add r4, r4, #0x1
	add r5, #0x40
	cmp r4, r6
	blt _02013F84
_02013F92:
	add r0, r7, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02013F98
FUN_02013F98: ; 0x02013F98
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x28
	mul r1, r6
	bl FUN_02016998
	add r7, r0, #0x0
	bne _02013FAE
	bl ErrorHandling
_02013FAE:
	mov r4, #0x0
	cmp r6, #0x0
	ble _02013FC4
	add r5, r7, #0x0
_02013FB6:
	add r0, r5, #0x0
	bl FUN_02013F50
	add r4, r4, #0x1
	add r5, #0x28
	cmp r4, r6
	blt _02013FB6
_02013FC4:
	add r0, r7, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02013FC8
FUN_02013FC8: ; 0x02013FC8
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x18
	mul r1, r6
	bl FUN_02016998
	add r7, r0, #0x0
	bne _02013FDE
	bl ErrorHandling
_02013FDE:
	mov r4, #0x0
	cmp r6, #0x0
	ble _02013FF4
	add r5, r7, #0x0
_02013FE6:
	add r0, r5, #0x0
	bl FUN_02013F5C
	add r4, r4, #0x1
	add r5, #0x18
	cmp r4, r6
	blt _02013FE6
_02013FF4:
	add r0, r7, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02013FF8
FUN_02013FF8: ; 0x02013FF8
	push {r3-r4}
	ldr r4, [r0, #0x4]
	mov r1, #0x0
	cmp r4, #0x0
	ble _0201401C
	ldr r3, [r0, #0x0]
	add r2, r3, #0x0
_02014006:
	ldr r0, [r2, #0x1c]
	cmp r0, #0x0
	bne _02014014
	lsl r0, r1, #0x6
	add r0, r3, r0
	pop {r3-r4}
	bx lr
_02014014:
	add r1, r1, #0x1
	add r2, #0x40
	cmp r1, r4
	blt _02014006
_0201401C:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_02014024
FUN_02014024: ; 0x02014024
	push {r3-r4}
	ldr r4, [r0, #0x4]
	mov r1, #0x0
	cmp r4, #0x0
	ble _0201404A
	ldr r3, [r0, #0x8]
	add r2, r3, #0x0
_02014032:
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	bne _02014042
	mov r0, #0x28
	mul r0, r1
	add r0, r3, r0
	pop {r3-r4}
	bx lr
_02014042:
	add r1, r1, #0x1
	add r2, #0x28
	cmp r1, r4
	blt _02014032
_0201404A:
	mov r0, #0x0
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02014050
FUN_02014050: ; 0x02014050
	push {r3-r4}
	ldr r4, [r0, #0x4]
	mov r1, #0x0
	cmp r4, #0x0
	ble _02014076
	ldr r3, [r0, #0x10]
	add r2, r3, #0x0
_0201405E:
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	bne _0201406E
	mov r0, #0x18
	mul r0, r1
	add r0, r3, r0
	pop {r3-r4}
	bx lr
_0201406E:
	add r1, r1, #0x1
	add r2, #0x18
	cmp r1, r4
	blt _0201405E
_02014076:
	mov r0, #0x0
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0201407C
FUN_0201407C: ; 0x0201407C
	push {r3, lr}
	ldr r3, _0201408C ; =0x021064B8
	mov r1, #0x0
	ldr r0, [r0, #0x10]
	ldr r3, [r3, #0x0]
	add r2, r1, #0x0
	blx r3
	pop {r3, pc}
	.balign 4
_0201408C: .word 0x021064B8

	thumb_func_start FUN_02014090
FUN_02014090: ; 0x02014090
	push {r3, lr}
	ldr r3, _020140A0 ; =0x021064C0
	mov r1, #0x0
	ldr r3, [r3, #0x0]
	lsl r0, r0, #0x5
	add r2, r1, #0x0
	blx r3
	pop {r3, pc}
	.balign 4
_020140A0: .word 0x021064C0

	thumb_func_start FUN_020140A4
FUN_020140A4: ; 0x020140A4
	push {r3, lr}
	lsl r1, r1, #0x10
	add r3, r2, #0x0
	lsr r1, r1, #0xd
	mov r2, #0x0
	bl FUN_020B1528
	pop {r3, pc}

	thumb_func_start FUN_020140B4
FUN_020140B4: ; 0x020140B4
	push {r3-r5, lr}
	add r3, r2, #0x0
	ldr r2, _020140D4 ; =0xFFFF0000
	add r5, r0, #0x0
	and r2, r1
	lsr r2, r2, #0x10
	lsl r1, r1, #0x10
	ldr r4, [r5, #0x8]
	lsl r2, r2, #0x3
	str r2, [r5, #0x8]
	lsr r1, r1, #0xd
	mov r2, #0x0
	bl FUN_020B1240
	str r4, [r5, #0x8]
	pop {r3-r5, pc}
	.balign 4
_020140D4: .word 0xFFFF0000

	thumb_func_start FUN_020140D8
FUN_020140D8: ; 0x020140D8
	push {r3-r7, lr}
	sub sp, #0x18
	ldr r7, _020141F8 ; =0x04000444
	mov r6, #0x0
	add r5, r0, #0x0
	str r6, [r7, #0x0]
	ldrh r1, [r5, #0x3c]
	ldr r0, _020141FC ; =0x7FFF8000
	orr r0, r1
	str r0, [r7, #0x7c]
	add r0, r7, #0x0
	ldr r1, _02014200 ; =0x00004210
	add r0, #0x80
	str r1, [r0, #0x0]
	ldr r3, [r5, #0x24]
	ldr r4, [r3, #0x8]
	ldr r2, [r3, #0x10]
	ldr r1, [r3, #0x4]
	ldr r0, [r3, #0x0]
	lsl r3, r2, #0x1d
	lsl r2, r1, #0x17
	lsl r1, r0, #0x14
	ldr r0, [r5, #0x28]
	lsl r4, r4, #0x1a
	lsr r0, r0, #0x3
	orr r4, r0
	mov r0, #0x1
	lsl r0, r0, #0x1e
	orr r0, r4
	orr r0, r1
	orr r0, r2
	orr r0, r3
	str r0, [r7, #0x64]
	ldr r0, [r5, #0x24]
	ldr r0, [r0, #0x8]
	cmp r0, #0x2
	bne _02014124
	mov r6, #0x1
_02014124:
	ldr r0, [r5, #0x30]
	ldr r1, [r5, #0x2c]
	lsl r0, r0, #0x5
	add r1, r1, r0
	mov r0, #0x4
	sub r0, r0, r6
	lsr r1, r0
	ldr r2, _02014204 ; =0x040004AC
	add r0, r5, #0x0
	str r1, [r2, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	sub r2, #0x8
	lsl r1, r0, #0x10
	mov r0, #0xc0
	orr r0, r1
	str r0, [r2, #0x0]
	ldr r0, [r5, #0x34]
	cmp r0, #0x0
	beq _02014156
	mov r0, #0x8
	ldrsh r0, [r5, r0]
	mov r7, #0x0
	str r0, [sp, #0x14]
	b _0201415E
_02014156:
	mov r0, #0x8
	ldrsh r7, [r5, r0]
	mov r0, #0x0
	str r0, [sp, #0x14]
_0201415E:
	ldr r0, [r5, #0x38]
	cmp r0, #0x0
	beq _0201416C
	mov r0, #0xa
	ldrsh r6, [r5, r0]
	mov r4, #0x0
	b _02014172
_0201416C:
	mov r0, #0xa
	ldrsh r4, [r5, r0]
	mov r6, #0x0
_02014172:
	ldr r0, [r5, #0x14]
	mov r1, #0x6
	lsl r2, r0, #0xc
	mov r0, #0x2
	ldrsh r0, [r5, r0]
	ldrsh r1, [r5, r1]
	mov r3, #0x4
	ldrsh r3, [r5, r3]
	add r0, r0, r1
	lsl r1, r0, #0xc
	mov r0, #0x0
	ldrsh r0, [r5, r0]
	add r0, r0, r3
	ldr r3, _02014208 ; =0x04000470
	lsl r0, r0, #0xc
	str r0, [r3, #0x0]
	str r1, [r3, #0x0]
	str r2, [r3, #0x0]
	ldr r0, [r5, #0x18]
	ldr r1, _0201420C ; =0x020FFA38
	asr r0, r0, #0x4
	lsl r2, r0, #0x1
	lsl r0, r2, #0x1
	add r2, r2, #0x1
	lsl r2, r2, #0x1
	ldrsh r0, [r1, r0]
	ldrsh r1, [r1, r2]
	bl G3_RotZ
	ldr r2, [r5, #0x10]
	ldr r0, [r5, #0xc]
	ldr r1, _02014210 ; =0x0400046C
	mov r3, #0x8
	str r0, [r1, #0x0]
	str r2, [r1, #0x0]
	lsr r0, r1, #0xe
	str r0, [r1, #0x0]
	mov r2, #0x4
	mov r0, #0x6
	ldrsh r2, [r5, r2]
	ldrsh r0, [r5, r0]
	neg r2, r2
	neg r0, r0
	lsl r2, r2, #0xc
	lsl r0, r0, #0xc
	str r2, [r1, #0x4]
	str r0, [r1, #0x4]
	mov r0, #0x0
	str r0, [r1, #0x4]
	mov r1, #0xa
	ldrsh r1, [r5, r1]
	add r2, r0, #0x0
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x14]
	str r1, [sp, #0x4]
	str r6, [sp, #0x8]
	str r7, [sp, #0xc]
	str r4, [sp, #0x10]
	ldrsh r3, [r5, r3]
	add r1, r0, #0x0
	bl FUN_020B0250
	ldr r0, _02014214 ; =0x04000448
	mov r1, #0x1
	str r1, [r0, #0x0]
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4
_020141F8: .word 0x04000444
_020141FC: .word 0x7FFF8000
_02014200: .word 0x00004210
_02014204: .word 0x040004AC
_02014208: .word 0x04000470
_0201420C: .word 0x020FFA38
_02014210: .word 0x0400046C
_02014214: .word 0x04000448

	thumb_func_start FUN_02014218
FUN_02014218: ; 0x02014218
	push {r3-r7, lr}
	add r5, r1, #0x0
	ldr r1, [r5, #0x4]
	add r7, r0, #0x0
	ldr r2, [r1, #0x10]
	mov r6, #0x8
	mov r0, #0x0
	cmp r2, #0x0
	ble _02014236
_0201422A:
	ldr r2, [r5, #0x4]
	add r0, r0, #0x1
	ldr r2, [r2, #0x10]
	lsl r6, r6, #0x1
	cmp r0, r2
	blt _0201422A
_02014236:
	ldr r1, [r1, #0x14]
	mov r4, #0x8
	mov r0, #0x0
	cmp r1, #0x0
	ble _0201424C
_02014240:
	ldr r1, [r5, #0x4]
	add r0, r0, #0x1
	ldr r1, [r1, #0x14]
	lsl r4, r4, #0x1
	cmp r0, r1
	blt _02014240
_0201424C:
	mov r1, #0xc
	mov r2, #0xe
	ldrsh r1, [r5, r1]
	ldrsh r2, [r5, r2]
	add r0, r7, #0x0
	bl FUN_02013EC4
	lsr r1, r6, #0x1f
	lsr r2, r4, #0x1f
	add r1, r6, r1
	add r2, r4, r2
	lsl r1, r1, #0xf
	lsl r2, r2, #0xf
	add r0, r7, #0x0
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_02013ED8
	mov r0, #0x1
	lsl r0, r0, #0xc
	str r0, [r7, #0xc]
	str r0, [r7, #0x10]
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_02013EE8
	ldr r1, [r5, #0x18]
	add r0, r7, #0x0
	bl FUN_02013EFC
	ldr r1, [r5, #0x14]
	add r0, r7, #0x0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_02013F04
	ldr r1, [r5, #0x4]
	add r0, r7, #0x0
	add r1, #0x10
	bl FUN_02013F10
	ldr r0, [r5, #0x4]
	mov r1, #0x0
	add r0, r0, #0x4
	bl FUN_020B1A14
	add r1, r0, #0x0
	add r0, r7, #0x0
	bl FUN_02013F14
	ldr r0, [r5, #0x8]
	mov r1, #0x0
	add r0, r0, #0x4
	bl FUN_020B19C4
	add r1, r0, #0x0
	add r0, r7, #0x0
	bl FUN_02013F18
	ldrh r1, [r5, #0x1c]
	add r0, r7, #0x0
	bl FUN_02013F1C
	mov r1, #0x0
	add r0, r7, #0x0
	add r2, r1, #0x0
	bl FUN_02013F20
	add r0, r7, #0x0
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_02013F20
	ldrh r1, [r5, #0x10]
	add r0, r7, #0x0
	bl FUN_02013F2C
	pop {r3-r7, pc}
	.balign 4
