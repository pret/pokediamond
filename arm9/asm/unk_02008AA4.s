    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02008AA4
FUN_02008AA4: ; 0x02008AA4
	push {r3-r7, lr}
	sub sp, #0x18
	mov r4, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x44]
	add r6, r1, #0x0
	str r2, [sp, #0x0]
	str r3, [sp, #0x4]
	str r4, [sp, #0xc]
	cmp r0, #0x0
	bne _02008AC2
	bl ErrorHandling
_02008AC2:
	ldr r0, [sp, #0x48]
	cmp r0, #0x0
	bne _02008ACC
	bl ErrorHandling
_02008ACC:
	ldr r0, [sp, #0x50]
	cmp r0, #0x0
	bne _02008AD6
	bl ErrorHandling
_02008AD6:
	ldr r0, [sp, #0x4c]
	cmp r0, #0x0
	bne _02008AE0
	bl ErrorHandling
_02008AE0:
	cmp r5, #0x0
	bne _02008AE8
	bl ErrorHandling
_02008AE8:
	ldr r0, [sp, #0x44]
	add r1, r6, #0x0
	bl FUN_020094F0
	add r7, r0, #0x0
	bne _02008AF8
	bl ErrorHandling
_02008AF8:
	ldr r0, [sp, #0x48]
	ldr r1, [sp, #0x0]
	bl FUN_020094F0
	str r0, [sp, #0x14]
	cmp r0, #0x0
	bne _02008B0A
	bl ErrorHandling
_02008B0A:
	ldr r0, [sp, #0x4c]
	ldr r1, [sp, #0x4]
	bl FUN_020094F0
	str r0, [sp, #0x10]
	cmp r0, #0x0
	bne _02008B1C
	bl ErrorHandling
_02008B1C:
	ldr r0, [sp, #0x50]
	cmp r0, #0x0
	beq _02008B3A
	mov r2, #0x0
	ldr r1, [sp, #0x30]
	mvn r2, r2
	cmp r1, r2
	beq _02008B3A
	bl FUN_020094F0
	str r0, [sp, #0xc]
	cmp r0, #0x0
	bne _02008B3A
	bl ErrorHandling
_02008B3A:
	ldr r0, [sp, #0x54]
	cmp r0, #0x0
	beq _02008B62
	mov r2, #0x0
	ldr r1, [sp, #0x34]
	mvn r2, r2
	cmp r1, r2
	beq _02008B50
	bl FUN_020094F0
	add r4, r0, #0x0
_02008B50:
	mov r0, #0x0
	ldr r1, [sp, #0x38]
	mvn r0, r0
	cmp r1, r0
	beq _02008B62
	ldr r0, [sp, #0x58]
	bl FUN_020094F0
	str r0, [sp, #0x8]
_02008B62:
	ldr r0, [sp, #0x3c]
	cmp r0, #0x0
	beq _02008B82
	ldr r1, [sp, #0x10]
	add r0, r7, #0x0
	bl FUN_02009C80
	add r6, r0, #0x0
	bne _02008B78
	bl ErrorHandling
_02008B78:
	add r0, r7, #0x0
	bl FUN_02009544
	str r0, [r5, #0x4]
	b _02008B94
_02008B82:
	add r0, r7, #0x0
	bl FUN_02009C5C
	add r6, r0, #0x0
	bne _02008B90
	bl ErrorHandling
_02008B90:
	mov r0, #0x0
	str r0, [r5, #0x4]
_02008B94:
	ldr r0, [sp, #0x14]
	add r1, r6, #0x0
	bl FUN_02009E54
	str r0, [r5, #0x8]
	ldr r0, [sp, #0x10]
	str r6, [r5, #0x0]
	bl FUN_02009574
	str r0, [r5, #0xc]
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	beq _02008BB4
	bl FUN_0200958C
	b _02008BB6
_02008BB4:
	mov r0, #0x0
_02008BB6:
	str r0, [r5, #0x10]
	cmp r4, #0x0
	beq _02008BCC
	add r0, r4, #0x0
	bl FUN_020095A4
	str r0, [r5, #0x14]
	ldr r0, [sp, #0x8]
	bl FUN_020095BC
	b _02008BD0
_02008BCC:
	mov r0, #0x0
	str r0, [r5, #0x14]
_02008BD0:
	str r0, [r5, #0x18]
	ldr r0, [sp, #0x3c]
	str r0, [r5, #0x1c]
	ldr r0, [sp, #0x40]
	add r5, #0x20
	strb r0, [r5, #0x0]
	add sp, #0x18
	pop {r3-r7, pc}

	thumb_func_start FUN_02008BE0
FUN_02008BE0: ; 0x02008BE0
	push {r4-r7, lr}
	sub sp, #0x34
	add r5, r0, #0x0
	ldr r0, [sp, #0x48]
	add r7, r1, #0x0
	str r0, [sp, #0x48]
	ldr r0, [sp, #0x4c]
	mov r4, #0x0
	str r0, [sp, #0x4c]
	ldr r0, [sp, #0x50]
	ldr r1, [r5, #0x0]
	str r0, [sp, #0x50]
	ldr r0, [sp, #0x54]
	str r2, [sp, #0x2c]
	str r0, [sp, #0x54]
	sub r0, r4, #0x2
	str r3, [sp, #0x30]
	cmp r1, r0
	beq _02008C14
	add r2, r5, #0x0
	sub r0, r4, #0x2
_02008C0A:
	add r2, #0x20
	ldr r1, [r2, #0x0]
	add r4, r4, #0x1
	cmp r1, r0
	bne _02008C0A
_02008C14:
	add r0, r7, #0x0
	mov r1, #0x8
	bl FUN_02016998
	mov r1, #0x24
	add r6, r0, #0x0
	add r0, r7, #0x0
	mul r1, r4
	bl FUN_02016998
	str r0, [r6, #0x0]
	mov r7, #0x0
	str r4, [r6, #0x4]
	cmp r4, #0x0
	ble _02008C7A
	add r4, r7, #0x0
_02008C34:
	ldr r0, [r5, #0xc]
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x10]
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x14]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x1c]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x2c]
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x30]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x4c]
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x50]
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x54]
	str r0, [sp, #0x28]
	ldr r0, [r6, #0x0]
	ldr r1, [r5, #0x0]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	add r0, r0, r4
	bl FUN_02008AA4
	ldr r0, [r6, #0x4]
	add r7, r7, #0x1
	add r5, #0x20
	add r4, #0x24
	cmp r7, r0
	blt _02008C34
_02008C7A:
	add r0, r6, #0x0
	add sp, #0x34
	pop {r4-r7, pc}

	thumb_func_start FUN_02008C80
FUN_02008C80: ; 0x02008C80
	push {r4, lr}
	add r4, r0, #0x0
	bne _02008C8A
	bl ErrorHandling
_02008C8A:
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02008C94
	bl FUN_02016A18
_02008C94:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}

	thumb_func_start FUN_02008C9C
FUN_02008C9C: ; 0x02008C9C
	push {r3-r6, lr}
	sub sp, #0x1c
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r1, _02008D00 ; =0xFFFFF000
	add r0, r4, #0x0
	add r6, r2, #0x0
	bl FUN_0202134C
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r0, #0xff
	lsl r0, r0, #0xc
	str r0, [sp, #0x8]
	mov r0, #0x3
	lsl r0, r0, #0x12
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	add r0, #0x98
	add r1, sp, #0x0
	mov r2, #0x1
	add r3, r4, #0x0
	bl FUN_02009FD8
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0xff
	mov r1, #0x3
	lsl r1, r1, #0x12
	lsl r0, r0, #0xc
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	str r1, [sp, #0x4]
	str r1, [sp, #0xc]
	add r0, #0xe0
	add r1, sp, #0x0
	mov r2, #0x2
	add r3, r4, #0x0
	bl FUN_02009FD8
	add r0, sp, #0x10
	str r5, [sp, #0x10]
	str r4, [sp, #0x14]
	str r6, [sp, #0x18]
	bl FUN_0201FCB0
	add sp, #0x1c
	pop {r3-r6, pc}
	nop
_02008D00: .word 0xFFFFF000

	thumb_func_start FUN_02008D04
FUN_02008D04: ; 0x02008D04
	push {r3, lr}
	sub sp, #0x10
	str r1, [sp, #0x0]
	mov r1, #0xff
	lsl r1, r1, #0xc
	str r1, [sp, #0x8]
	mov r1, #0x3
	lsl r1, r1, #0x12
	str r1, [sp, #0xc]
	add r0, #0x98
	add r1, sp, #0x0
	str r2, [sp, #0x4]
	bl FUN_02021390
	add sp, #0x10
	pop {r3, pc}

	thumb_func_start FUN_02008D24
FUN_02008D24: ; 0x02008D24
	push {r3, lr}
	sub sp, #0x10
	str r1, [sp, #0x0]
	mov r1, #0xff
	lsl r1, r1, #0xc
	str r1, [sp, #0x8]
	mov r1, #0x3
	lsl r1, r1, #0x12
	str r1, [sp, #0xc]
	add r0, #0xe0
	add r1, sp, #0x0
	str r2, [sp, #0x4]
	bl FUN_02021390
	add sp, #0x10
	pop {r3, pc}

	thumb_func_start FUN_02008D44
FUN_02008D44: ; 0x02008D44
	push {r4, lr}
	add r4, r0, #0x0
	cmp r1, #0x10
	beq _02008D5A
	ldr r2, _02008DCC ; =0x00100010
	cmp r1, r2
	beq _02008D8A
	ldr r0, _02008DD0 ; =0x00200010
	cmp r1, r0
	beq _02008D98
	b _02008DC4
_02008D5A:
	bl GX_GetBankForOBJ
	cmp r0, #0x40
	beq _02008D6A
	bl GX_GetBankForOBJ
	cmp r0, #0x20
	bne _02008D7A
_02008D6A:
	mov r0, #0x3e
	mov r1, #0x2
	lsl r0, r0, #0x8
	lsl r1, r1, #0x8
	add r2, r4, #0x0
	bl FUN_0201D194
	pop {r4, pc}
_02008D7A:
	mov r0, #0x7e
	mov r1, #0x2
	lsl r0, r0, #0x8
	lsl r1, r1, #0x8
	add r2, r4, #0x0
	bl FUN_0201D194
	pop {r4, pc}
_02008D8A:
	mov r0, #0xfe
	lsr r1, r2, #0xb
	lsl r0, r0, #0x8
	add r2, r4, #0x0
	bl FUN_0201D194
	pop {r4, pc}
_02008D98:
	bl GX_GetBankForOBJ
	cmp r0, #0x30
	beq _02008DA8
	bl GX_GetBankForOBJ
	cmp r0, #0x50
	bne _02008DB6
_02008DA8:
	mov r1, #0x2
	ldr r0, _02008DD4 ; =0x00013E00
	lsl r1, r1, #0x8
	add r2, r4, #0x0
	bl FUN_0201D194
	pop {r4, pc}
_02008DB6:
	mov r1, #0x2
	ldr r0, _02008DD8 ; =0x0001FE00
	lsl r1, r1, #0x8
	add r2, r4, #0x0
	bl FUN_0201D194
	pop {r4, pc}
_02008DC4:
	bl ErrorHandling
	pop {r4, pc}
	nop
_02008DCC: .word 0x00100010
_02008DD0: .word 0x00200010
_02008DD4: .word 0x00013E00
_02008DD8: .word 0x0001FE00

	thumb_func_start FUN_02008DDC
FUN_02008DDC: ; 0x02008DDC
	ldr r3, _02008DE8 ; =FUN_0201E068
	add r1, r0, #0x0
	mov r0, #0x3
	lsl r0, r0, #0xe
	bx r3
	nop
_02008DE8: .word FUN_0201E068
