    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020ECE88
UNK_020ECE88: ; 0x020ECE88
	.byte 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00

	.global UNK_020ECE98
UNK_020ECE98: ; 0x020ECE98
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00

	.global UNK_020ECEA8
UNK_020ECEA8: ; 0x020ECEA8
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020ECEC0
UNK_020ECEC0: ; 0x020ECEC0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xD5, 0x5C, 0x01, 0x00, 0xD5, 0x5C, 0x01, 0x00, 0xD5, 0x5C, 0x01, 0x00
	.byte 0xD5, 0x5C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_0200CABC
FUN_0200CABC: ; 0x0200CABC
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r3, #0x0
	str r2, [sp, #0x0]
	bne _0200CAE2
	mov r1, #0x0
	str r1, [sp, #0x4]
	ldr r0, [sp, #0x20]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	mov r0, #0x26
	add r2, r5, #0x0
	add r3, r4, #0x0
	bl FUN_0200687C
	add sp, #0x10
	pop {r3-r5, pc}
_0200CAE2:
	mov r0, #0x0
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x20]
	mov r1, #0x1
	str r0, [sp, #0xc]
	mov r0, #0x26
	add r2, r5, #0x0
	add r3, r4, #0x0
	bl FUN_0200687C
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_0200CAFC
FUN_0200CAFC: ; 0x0200CAFC
	mov r0, #0x18
	bx lr

	thumb_func_start FUN_0200CB00
FUN_0200CB00: ; 0x0200CB00
	push {r4-r6, lr}
	sub sp, #0x10
	add r6, r0, #0x0
	add r0, sp, #0x10
	ldrb r0, [r0, #0x10]
	add r5, r1, #0x0
	add r4, r3, #0x0
	cmp r0, #0x0
	beq _0200CB16
	mov r1, #0x1
	b _0200CB18
_0200CB16:
	mov r1, #0x0
_0200CB18:
	str r2, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x24]
	add r2, r6, #0x0
	str r0, [sp, #0xc]
	mov r0, #0x26
	add r3, r5, #0x0
	bl FUN_0200687C
	add r0, sp, #0x10
	ldrb r0, [r0, #0x10]
	cmp r0, #0x2
	bne _0200CB3A
	mov r1, #0x2d
	b _0200CB3C
_0200CB3A:
	mov r1, #0x18
_0200CB3C:
	cmp r5, #0x4
	bhs _0200CB56
	mov r0, #0x20
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	mov r2, #0x0
	str r0, [sp, #0x4]
	mov r0, #0x26
	lsl r3, r4, #0x5
	bl FUN_02006930
	add sp, #0x10
	pop {r4-r6, pc}
_0200CB56:
	mov r0, #0x20
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	mov r2, #0x4
	str r0, [sp, #0x4]
	mov r0, #0x26
	lsl r3, r4, #0x5
	bl FUN_02006930
	add sp, #0x10
	pop {r4-r6, pc}

	thumb_func_start FUN_0200CB6C
FUN_0200CB6C: ; 0x0200CB6C
	push {r4-r7, lr}
	sub sp, #0x24
	str r1, [sp, #0x14]
	str r2, [sp, #0x18]
	str r3, [sp, #0x1c]
	ldr r2, [sp, #0x1c]
	ldr r5, [sp, #0x40]
	sub r7, r2, #0x1
	ldr r2, [sp, #0x18]
	str r0, [sp, #0x10]
	sub r6, r2, #0x1
	lsl r2, r7, #0x18
	lsr r2, r2, #0x18
	str r2, [sp, #0x0]
	mov r2, #0x1
	str r2, [sp, #0x4]
	str r2, [sp, #0x8]
	lsl r3, r6, #0x18
	str r5, [sp, #0xc]
	add r2, sp, #0x28
	ldrh r2, [r2, #0x1c]
	lsr r3, r3, #0x18
	bl FUN_02018540
	add r1, sp, #0x28
	ldrh r4, [r1, #0x1c]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	ldrb r0, [r1, #0x10]
	add r2, r4, #0x1
	lsl r2, r2, #0x10
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	str r5, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	ldr r3, [sp, #0x18]
	lsr r2, r2, #0x10
	bl FUN_02018540
	add r0, sp, #0x28
	ldrb r1, [r0, #0x10]
	ldr r0, [sp, #0x18]
	add r2, r4, #0x2
	add r0, r0, r1
	str r0, [sp, #0x20]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r3, [sp, #0x20]
	str r5, [sp, #0xc]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x1c]
	add r2, r4, #0x3
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r0, sp, #0x28
	ldrb r0, [r0, #0x14]
	lsl r2, r2, #0x10
	lsl r3, r6, #0x18
	str r0, [sp, #0x8]
	str r5, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x1c]
	ldr r3, [sp, #0x20]
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r0, sp, #0x28
	ldrb r0, [r0, #0x14]
	add r2, r4, #0x5
	lsl r2, r2, #0x10
	str r0, [sp, #0x8]
	str r5, [sp, #0xc]
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	add r0, sp, #0x28
	ldrb r1, [r0, #0x14]
	ldr r0, [sp, #0x1c]
	add r2, r4, #0x6
	add r7, r0, r1
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	str r5, [sp, #0xc]
	lsl r2, r2, #0x10
	lsl r3, r6, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	add r0, sp, #0x28
	ldrb r0, [r0, #0x10]
	add r2, r4, #0x7
	lsl r2, r2, #0x10
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	str r5, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	ldr r3, [sp, #0x18]
	lsr r2, r2, #0x10
	bl FUN_02018540
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r3, [sp, #0x20]
	str r5, [sp, #0xc]
	add r4, #0x8
	lsl r2, r4, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0200CCA4
FUN_0200CCA4: ; 0x0200CCA4
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_0201AB08
	str r0, [sp, #0x10]
	add r0, r5, #0x0
	bl FUN_0201AB14
	str r0, [sp, #0x14]
	add r0, r5, #0x0
	bl FUN_0201AB18
	str r0, [sp, #0x18]
	add r0, r5, #0x0
	bl GetWindowWidth
	str r0, [sp, #0x1c]
	add r0, r5, #0x0
	bl GetWindowHeight
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x14]
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	str r7, [sp, #0x8]
	str r6, [sp, #0xc]
	ldr r0, [r5, #0x0]
	ldr r1, [sp, #0x10]
	ldr r3, [sp, #0x18]
	bl FUN_0200CB6C
	cmp r4, #0x0
	bne _0200CCF4
	add r0, r5, #0x0
	bl CopyWindowToVram
_0200CCF4:
	add sp, #0x20
	pop {r3-r7, pc}

	thumb_func_start FUN_0200CCF8
FUN_0200CCF8: ; 0x0200CCF8
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0201AB08
	str r0, [sp, #0x10]
	add r0, r5, #0x0
	bl FUN_0201AB14
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0201AB18
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl GetWindowWidth
	str r0, [sp, #0x14]
	add r0, r5, #0x0
	bl GetWindowHeight
	sub r1, r7, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x14]
	add r0, r0, #0x2
	add r1, r1, #0x2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r0, r0, #0x18
	str r1, [sp, #0x4]
	lsr r0, r0, #0x18
	sub r3, r6, #0x1
	lsl r3, r3, #0x18
	str r0, [sp, #0x8]
	mov r2, #0x0
	str r2, [sp, #0xc]
	ldr r0, [r5, #0x0]
	ldr r1, [sp, #0x10]
	lsr r3, r3, #0x18
	bl FUN_02018540
	cmp r4, #0x0
	bne _0200CD5A
	add r0, r5, #0x0
	bl FUN_02019570
_0200CD5A:
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200CD60
FUN_0200CD60: ; 0x0200CD60
	add r0, r0, #0x2
	bx lr

	thumb_func_start FUN_0200CD64
FUN_0200CD64: ; 0x0200CD64
	add r0, #0x19
	bx lr

	thumb_func_start FUN_0200CD68
FUN_0200CD68: ; 0x0200CD68
	push {r4-r7, lr}
	sub sp, #0x14
	str r0, [sp, #0x10]
	add r0, sp, #0x18
	ldrb r7, [r0, #0x10]
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r7, #0x0
	add r4, r3, #0x0
	bl FUN_0200CD60
	add r1, r0, #0x0
	str r6, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x2c]
	ldr r2, [sp, #0x10]
	str r0, [sp, #0xc]
	mov r0, #0x26
	add r3, r5, #0x0
	bl FUN_0200687C
	cmp r5, #0x4
	bhs _0200CDB8
	add r0, r7, #0x0
	bl FUN_0200CD64
	add r1, r0, #0x0
	mov r0, #0x20
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x2c]
	mov r2, #0x0
	str r0, [sp, #0x4]
	mov r0, #0x26
	lsl r3, r4, #0x5
	bl FUN_02006930
	add sp, #0x14
	pop {r4-r7, pc}
_0200CDB8:
	add r0, r7, #0x0
	bl FUN_0200CD64
	add r1, r0, #0x0
	mov r0, #0x20
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x2c]
	mov r2, #0x4
	str r0, [sp, #0x4]
	mov r0, #0x26
	lsl r3, r4, #0x5
	bl FUN_02006930
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0200CDD8
FUN_0200CDD8: ; 0x0200CDD8
	push {r3-r7, lr}
	sub sp, #0x30
	str r1, [sp, #0x10]
	str r2, [sp, #0x14]
	str r3, [sp, #0x18]
	ldr r2, [sp, #0x4c]
	add r7, r0, #0x0
	str r2, [sp, #0x4c]
	ldr r2, [sp, #0x18]
	ldr r5, [sp, #0x50]
	sub r6, r2, #0x1
	ldr r2, [sp, #0x14]
	sub r2, r2, #0x2
	str r2, [sp, #0x28]
	lsl r2, r6, #0x18
	lsr r2, r2, #0x18
	str r2, [sp, #0x0]
	mov r2, #0x1
	str r2, [sp, #0x4]
	str r2, [sp, #0x8]
	ldr r3, [sp, #0x28]
	str r5, [sp, #0xc]
	add r2, sp, #0x38
	lsl r3, r3, #0x18
	ldrh r2, [r2, #0x1c]
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x14]
	sub r0, r0, #0x1
	str r0, [sp, #0x24]
	add r0, sp, #0x38
	ldrh r4, [r0, #0x1c]
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r3, [sp, #0x24]
	str r5, [sp, #0xc]
	add r2, r4, #0x1
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r1, [sp, #0x10]
	add r0, r7, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	add r0, sp, #0x38
	ldrb r0, [r0, #0x10]
	add r2, r4, #0x2
	lsl r2, r2, #0x10
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	str r5, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r3, [sp, #0x14]
	add r0, r7, #0x0
	lsr r2, r2, #0x10
	bl FUN_02018540
	add r0, sp, #0x38
	ldrb r1, [r0, #0x10]
	ldr r0, [sp, #0x14]
	add r2, r4, #0x3
	add r0, r0, r1
	str r0, [sp, #0x2c]
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r3, [sp, #0x2c]
	str r5, [sp, #0xc]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r1, [sp, #0x10]
	add r0, r7, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x2c]
	add r2, r4, #0x4
	add r0, r0, #0x1
	str r0, [sp, #0x20]
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r3, [sp, #0x20]
	str r5, [sp, #0xc]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r1, [sp, #0x10]
	add r0, r7, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x2c]
	add r2, r4, #0x5
	add r0, r0, #0x2
	str r0, [sp, #0x1c]
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r3, [sp, #0x1c]
	str r5, [sp, #0xc]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r1, [sp, #0x10]
	add r0, r7, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x18]
	ldr r3, [sp, #0x28]
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x4c]
	add r2, r4, #0x6
	str r0, [sp, #0x8]
	str r5, [sp, #0xc]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r1, [sp, #0x10]
	add r0, r7, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x18]
	ldr r3, [sp, #0x24]
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x4c]
	add r2, r4, #0x7
	str r0, [sp, #0x8]
	str r5, [sp, #0xc]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r1, [sp, #0x10]
	add r0, r7, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x18]
	add r2, r4, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x4c]
	ldr r3, [sp, #0x2c]
	str r0, [sp, #0x8]
	str r5, [sp, #0xc]
	add r2, #0x9
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r1, [sp, #0x10]
	add r0, r7, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x18]
	add r2, r4, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x4c]
	ldr r3, [sp, #0x20]
	str r0, [sp, #0x8]
	str r5, [sp, #0xc]
	add r2, #0xa
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r1, [sp, #0x10]
	add r0, r7, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x18]
	add r2, r4, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x4c]
	ldr r3, [sp, #0x1c]
	str r0, [sp, #0x8]
	str r5, [sp, #0xc]
	add r2, #0xb
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r1, [sp, #0x10]
	add r0, r7, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	add r2, r4, #0x0
	ldr r3, [sp, #0x28]
	add r2, #0xc
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r1, [sp, #0x18]
	ldr r0, [sp, #0x4c]
	lsr r2, r2, #0x10
	add r6, r1, r0
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	str r5, [sp, #0xc]
	ldr r1, [sp, #0x10]
	add r0, r7, #0x0
	lsr r3, r3, #0x18
	bl FUN_02018540
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	add r2, r4, #0x0
	ldr r3, [sp, #0x24]
	str r5, [sp, #0xc]
	add r2, #0xd
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r1, [sp, #0x10]
	add r0, r7, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	add r0, sp, #0x38
	ldrb r0, [r0, #0x10]
	add r2, r4, #0x0
	add r2, #0xe
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	str r5, [sp, #0xc]
	lsl r2, r2, #0x10
	ldr r1, [sp, #0x10]
	ldr r3, [sp, #0x14]
	add r0, r7, #0x0
	lsr r2, r2, #0x10
	bl FUN_02018540
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	add r2, r4, #0x0
	ldr r3, [sp, #0x2c]
	str r5, [sp, #0xc]
	add r2, #0xf
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r1, [sp, #0x10]
	add r0, r7, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	add r2, r4, #0x0
	ldr r3, [sp, #0x20]
	str r5, [sp, #0xc]
	add r2, #0x10
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r1, [sp, #0x10]
	add r0, r7, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r3, [sp, #0x1c]
	str r5, [sp, #0xc]
	add r4, #0x11
	lsl r2, r4, #0x10
	lsl r3, r3, #0x18
	ldr r1, [sp, #0x10]
	add r0, r7, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200D06C
FUN_0200D06C: ; 0x0200D06C
	push {r4-r7, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_0201AB08
	str r0, [sp, #0x10]
	add r0, r5, #0x0
	bl FUN_0201AB14
	str r0, [sp, #0x14]
	add r0, r5, #0x0
	bl FUN_0201AB18
	str r0, [sp, #0x18]
	add r0, r5, #0x0
	bl GetWindowWidth
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl GetWindowHeight
	str r7, [sp, #0x0]
	str r0, [sp, #0x4]
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x0]
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0x14]
	ldr r3, [sp, #0x18]
	bl FUN_0200CDD8
	add sp, #0x1c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0200D0BC
FUN_0200D0BC: ; 0x0200D0BC
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r4, r1, #0x0
	add r1, r6, #0x0
	add r2, r3, #0x0
	add r5, r0, #0x0
	bl FUN_0200D06C
	cmp r4, #0x0
	bne _0200D0D6
	add r0, r5, #0x0
	bl CopyWindowToVram
_0200D0D6:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0200D18C
	pop {r4-r6, pc}

	thumb_func_start FUN_0200D0E0
FUN_0200D0E0: ; 0x0200D0E0
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0201AB08
	str r0, [sp, #0x10]
	add r0, r5, #0x0
	bl FUN_0201AB14
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0201AB18
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl GetWindowWidth
	str r0, [sp, #0x14]
	add r0, r5, #0x0
	bl GetWindowHeight
	sub r1, r7, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x14]
	add r0, r0, #0x2
	add r1, r1, #0x5
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r0, r0, #0x18
	str r1, [sp, #0x4]
	lsr r0, r0, #0x18
	sub r3, r6, #0x2
	lsl r3, r3, #0x18
	str r0, [sp, #0x8]
	mov r2, #0x0
	str r2, [sp, #0xc]
	ldr r0, [r5, #0x0]
	ldr r1, [sp, #0x10]
	lsr r3, r3, #0x18
	bl FUN_02018540
	cmp r4, #0x0
	bne _0200D142
	add r0, r5, #0x0
	bl FUN_02019570
_0200D142:
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200D148
FUN_0200D148: ; 0x0200D148
	push {r4-r5, lr}
	sub sp, #0x24
	add r5, r1, #0x0
	str r0, [sp, #0x1c]
	add r1, sp, #0x14
	strh r3, [r1, #0xc]
	add r4, r2, #0x0
	add r0, sp, #0x20
	ldrh r2, [r0, #0x10]
	add r3, r4, #0x0
	strh r2, [r1, #0xe]
	ldr r2, [sp, #0x34]
	str r2, [sp, #0x14]
	ldrh r2, [r0, #0x18]
	strh r2, [r1, #0x4]
	ldrh r2, [r0, #0x1c]
	strh r2, [r1, #0x6]
	ldrh r1, [r0, #0x20]
	add r2, r5, #0x0
	str r1, [sp, #0x0]
	ldrh r1, [r0, #0x24]
	str r1, [sp, #0x4]
	ldrh r1, [r0, #0x28]
	str r1, [sp, #0x8]
	ldrh r0, [r0, #0x2c]
	add r1, sp, #0x14
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	add r0, sp, #0x1c
	bl FUN_02018A60
	add sp, #0x24
	pop {r4-r5, pc}

	thumb_func_start FUN_0200D18C
FUN_0200D18C: ; 0x0200D18C
	push {r3-r7, lr}
	sub sp, #0x40
	str r1, [sp, #0x24]
	str r0, [sp, #0x20]
	ldr r0, [r0, #0x0]
	bl FUN_02016BB8
	add r6, r0, #0x0
	ldr r0, [sp, #0x20]
	bl FUN_0201AB08
	mov r1, #0x6
	str r0, [sp, #0x28]
	add r0, r6, #0x0
	lsl r1, r1, #0x6
	bl AllocFromHeap
	add r5, r0, #0x0
	ldr r0, [sp, #0x28]
	bl FUN_020187B0
	add r4, r0, #0x0
	str r6, [sp, #0x0]
	mov r0, #0x26
	mov r1, #0x16
	mov r2, #0x0
	add r3, sp, #0x3c
	bl FUN_02006BB0
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x3c]
	mov r7, #0x0
	ldr r0, [r0, #0x14]
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x24]
	add r0, #0xa
	lsl r0, r0, #0x5
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x24]
	add r0, #0xb
	lsl r0, r0, #0x5
	str r0, [sp, #0x38]
_0200D1E0:
	ldr r1, [sp, #0x34]
	lsl r6, r7, #0x7
	add r0, r5, r6
	add r1, r4, r1
	mov r2, #0x20
	bl memcpy
	add r0, r6, #0x0
	ldr r1, [sp, #0x38]
	add r0, #0x20
	add r0, r5, r0
	add r1, r4, r1
	mov r2, #0x20
	bl memcpy
	add r0, r6, #0x0
	ldr r1, [sp, #0x34]
	add r0, #0x40
	add r0, r5, r0
	add r1, r4, r1
	mov r2, #0x20
	bl memcpy
	ldr r1, [sp, #0x38]
	add r6, #0x60
	add r0, r5, r6
	add r1, r4, r1
	mov r2, #0x20
	bl memcpy
	add r0, r7, #0x1
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	cmp r7, #0x3
	blo _0200D1E0
	mov r1, #0x30
	str r1, [sp, #0x0]
	str r5, [sp, #0x4]
	mov r3, #0xc
	str r3, [sp, #0x8]
	str r1, [sp, #0xc]
	mov r0, #0x1
	str r0, [sp, #0x10]
	mov r2, #0x0
	str r2, [sp, #0x14]
	str r3, [sp, #0x18]
	str r1, [sp, #0x1c]
	ldr r0, [sp, #0x30]
	mov r1, #0x4
	bl FUN_0200D148
	ldr r0, [sp, #0x24]
	mov r3, #0x6
	add r0, #0x12
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x28]
	ldr r0, [r0, #0x0]
	add r2, r5, #0x0
	lsl r3, r3, #0x6
	bl FUN_02017E14
	ldr r0, [sp, #0x24]
	bl FUN_02002840
	ldr r0, [sp, #0x2c]
	bl FreeToHeap
	add r0, r5, #0x0
	bl FreeToHeap
	add sp, #0x40
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200D274
FUN_0200D274: ; 0x0200D274
	push {r4-r7, lr}
	sub sp, #0x14
	str r0, [sp, #0x4]
	str r1, [sp, #0x8]
	add r0, sp, #0x18
	ldrb r0, [r0, #0x10]
	add r7, r2, #0x0
	add r5, r3, #0x0
	bl FUN_0200CD60
	add r1, r0, #0x0
	ldr r0, [sp, #0x2c]
	mov r2, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x26
	add r3, sp, #0x10
	bl FUN_02006BB0
	str r0, [sp, #0xc]
	mov r1, #0x9
	ldr r0, [sp, #0x2c]
	lsl r1, r1, #0x6
	bl AllocFromHeap
	ldr r1, [sp, #0x10]
	mov r2, #0x9
	ldr r1, [r1, #0x14]
	lsl r2, r2, #0x6
	add r4, r0, #0x0
	bl memcpy
	mov r0, #0x9
	mov r3, #0x0
	lsl r0, r0, #0x6
	mov r1, #0xf
_0200D2BA:
	ldrb r2, [r4, r3]
	lsl r6, r2, #0x14
	and r2, r1
	lsl r2, r2, #0x18
	lsr r6, r6, #0x18
	lsr r2, r2, #0x18
	cmp r6, #0x0
	bne _0200D2CC
	add r6, r5, #0x0
_0200D2CC:
	cmp r2, #0x0
	bne _0200D2D2
	add r2, r5, #0x0
_0200D2D2:
	lsl r6, r6, #0x4
	orr r2, r6
	strb r2, [r4, r3]
	add r3, r3, #0x1
	cmp r3, r0
	blo _0200D2BA
	str r7, [sp, #0x0]
	mov r3, #0x9
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x8]
	add r2, r4, #0x0
	lsl r3, r3, #0x6
	bl FUN_02017E14
	ldr r0, [sp, #0xc]
	bl FreeToHeap
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0200D300
FUN_0200D300: ; 0x0200D300
	push {r4-r7, lr}
	sub sp, #0x1c
	str r0, [sp, #0x10]
	add r5, r2, #0x0
	mov r0, #0xf
	add r6, r1, #0x0
	add r7, r3, #0x0
	str r5, [sp, #0x0]
	lsl r0, r0, #0x6
	str r0, [sp, #0x4]
	mov r1, #0x0
	ldr r4, [sp, #0x38]
	str r1, [sp, #0x8]
	ldr r2, [sp, #0x10]
	mov r0, #0x24
	add r3, r6, #0x0
	str r4, [sp, #0xc]
	bl FUN_0200687C
	mov r0, #0x24 ; NARC_GRAPHIC_FIELD_BOARD
	mov r1, #0x1
	add r2, r4, #0x0
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0x18
	str r0, [sp, #0x14]
	bl FUN_020B0138
	add r2, sp, #0x20
	ldr r1, [sp, #0x18]
	ldrb r2, [r2, #0x10]
	lsl r3, r7, #0x15
	ldr r1, [r1, #0xc]
	lsl r2, r2, #0x5
	add r1, r1, r2
	add r0, r6, #0x0
	mov r2, #0x20
	lsr r3, r3, #0x10
	bl FUN_02017FB4
	ldr r1, [sp, #0x14]
	add r0, r4, #0x0
	bl FUN_02016A8C
	add r0, sp, #0x20
	ldrb r3, [r0, #0x10]
	cmp r3, #0x1
	bhi _0200D374
	ldrh r0, [r0, #0x14]
	add r5, #0x1e
	lsl r2, r5, #0x10
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x10]
	add r1, r6, #0x0
	lsr r2, r2, #0x10
	str r4, [sp, #0x4]
	bl FUN_0200D378
_0200D374:
	add sp, #0x1c
	pop {r4-r7, pc}

	thumb_func_start FUN_0200D378
FUN_0200D378: ; 0x0200D378
	push {r3-r5, lr}
	sub sp, #0x10
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r1, [sp, #0x20]
	cmp r3, #0x0
	bne _0200D38C
	add r1, #0x21
	lsl r0, r1, #0x10
	b _0200D390
_0200D38C:
	add r0, r1, #0x2
	lsl r0, r0, #0x10
_0200D390:
	lsr r1, r0, #0x10
	mov r0, #0x3
	str r2, [sp, #0x0]
	lsl r0, r0, #0x8
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x24]
	add r2, r5, #0x0
	str r0, [sp, #0xc]
	mov r0, #0x24
	add r3, r4, #0x0
	bl FUN_0200687C
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_0200D3B0
FUN_0200D3B0: ; 0x0200D3B0
	push {r3-r7, lr}
	sub sp, #0x40
	str r1, [sp, #0x14]
	str r2, [sp, #0x18]
	str r3, [sp, #0x1c]
	ldr r2, [sp, #0x1c]
	ldr r6, [sp, #0x5c]
	sub r7, r2, #0x1
	ldr r2, [sp, #0x18]
	ldr r5, [sp, #0x60]
	str r2, [sp, #0x34]
	sub r2, #0x9
	str r2, [sp, #0x34]
	lsl r2, r7, #0x18
	lsr r2, r2, #0x18
	str r2, [sp, #0x0]
	mov r2, #0x1
	str r2, [sp, #0x4]
	str r2, [sp, #0x8]
	ldr r3, [sp, #0x34]
	str r5, [sp, #0xc]
	add r2, sp, #0x48
	lsl r3, r3, #0x18
	ldrh r2, [r2, #0x1c]
	lsr r3, r3, #0x18
	str r0, [sp, #0x10]
	bl FUN_02018540
	ldr r0, [sp, #0x18]
	str r0, [sp, #0x30]
	sub r0, #0x8
	str r0, [sp, #0x30]
	add r0, sp, #0x48
	ldrh r4, [r0, #0x1c]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r3, [sp, #0x30]
	str r5, [sp, #0xc]
	add r2, r4, #0x1
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	add r0, sp, #0x48
	ldrb r0, [r0, #0x10]
	add r2, r4, #0x2
	lsl r2, r2, #0x10
	str r0, [sp, #0x3c]
	add r0, r0, #0x7
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x18]
	lsr r2, r2, #0x10
	sub r0, r0, #0x7
	str r0, [sp, #0x20]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	ldr r3, [sp, #0x20]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	str r5, [sp, #0xc]
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r3, r3, #0x18
	bl FUN_02018540
	add r2, r4, #0x3
	lsl r2, r2, #0x10
	ldr r1, [sp, #0x18]
	ldr r0, [sp, #0x3c]
	lsr r2, r2, #0x10
	add r0, r1, r0
	str r0, [sp, #0x38]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r3, [sp, #0x38]
	str r5, [sp, #0xc]
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x38]
	add r2, r4, #0x4
	add r0, r0, #0x1
	str r0, [sp, #0x2c]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r3, [sp, #0x2c]
	str r5, [sp, #0xc]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x38]
	add r0, r0, #0x2
	str r0, [sp, #0x28]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r3, [sp, #0x28]
	str r5, [sp, #0xc]
	add r2, r4, #0x5
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x1c]
	ldr r3, [sp, #0x34]
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r6, [sp, #0x8]
	str r5, [sp, #0xc]
	add r2, r4, #0x6
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x1c]
	ldr r3, [sp, #0x30]
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r6, [sp, #0x8]
	str r5, [sp, #0xc]
	add r2, r4, #0x7
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x1c]
	add r2, r4, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r6, [sp, #0x8]
	str r5, [sp, #0xc]
	ldr r3, [sp, #0x18]
	add r2, #0x8
	sub r3, r3, #0x1
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x1c]
	add r2, r4, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r6, [sp, #0x8]
	ldr r3, [sp, #0x38]
	str r5, [sp, #0xc]
	add r2, #0x9
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x1c]
	add r2, r4, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r6, [sp, #0x8]
	ldr r3, [sp, #0x2c]
	str r5, [sp, #0xc]
	add r2, #0xa
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x1c]
	add r2, r4, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r6, [sp, #0x8]
	ldr r3, [sp, #0x28]
	str r5, [sp, #0xc]
	add r2, #0xb
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x1c]
	add r2, r4, #0x0
	add r6, r0, r6
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r3, [sp, #0x34]
	str r5, [sp, #0xc]
	add r2, #0xc
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	add r2, r4, #0x0
	ldr r3, [sp, #0x30]
	str r5, [sp, #0xc]
	add r2, #0xd
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	add r2, r4, #0x0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	ldr r3, [sp, #0x20]
	str r5, [sp, #0xc]
	add r2, #0xe
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	add r2, r4, #0x0
	ldr r3, [sp, #0x38]
	str r5, [sp, #0xc]
	add r2, #0xf
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	add r2, r4, #0x0
	ldr r3, [sp, #0x2c]
	str r5, [sp, #0xc]
	add r2, #0x10
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r3, [sp, #0x28]
	str r5, [sp, #0xc]
	add r4, #0x11
	lsl r2, r4, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	add sp, #0x40
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200D678
FUN_0200D678: ; 0x0200D678
	push {r3-r7, lr}
	sub sp, #0x28
	str r1, [sp, #0x10]
	add r7, r0, #0x0
	str r2, [sp, #0x14]
	bl FUN_0201AB08
	str r0, [sp, #0x20]
	add r0, r7, #0x0
	bl FUN_0201AB14
	sub r0, r0, #0x7
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x18]
	add r0, r7, #0x0
	bl FUN_0201AB18
	str r0, [sp, #0x1c]
	mov r0, #0x0
	str r0, [sp, #0x24]
_0200D6A2:
	ldr r2, [sp, #0x24]
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x24]
	add r3, r2, #0x0
	add r0, r1, r0
	mov r1, #0x6
	mul r3, r1
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0x18
	mov r4, #0x0
	add r5, r1, r3
	lsr r6, r0, #0x18
_0200D6BA:
	str r6, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x14]
	ldr r3, [sp, #0x18]
	str r0, [sp, #0xc]
	add r2, r4, r5
	add r3, r3, r4
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [r7, #0x0]
	ldr r1, [sp, #0x20]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x6
	blo _0200D6BA
	ldr r0, [sp, #0x24]
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x24]
	cmp r0, #0x4
	blo _0200D6A2
	add sp, #0x28
	pop {r3-r7, pc}

	thumb_func_start FUN_0200D6F8
FUN_0200D6F8: ; 0x0200D6F8
	push {r3-r7, lr}
	sub sp, #0x28
	add r5, r0, #0x0
	str r1, [sp, #0x10]
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_0201AB08
	str r0, [sp, #0x14]
	add r0, sp, #0x30
	ldrb r0, [r0, #0x10]
	cmp r0, #0x1
	bhi _0200D756
	add r0, r5, #0x0
	bl FUN_0201AB14
	str r0, [sp, #0x18]
	add r0, r5, #0x0
	bl FUN_0201AB18
	str r0, [sp, #0x1c]
	add r0, r5, #0x0
	bl GetWindowWidth
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl GetWindowHeight
	str r7, [sp, #0x0]
	str r0, [sp, #0x4]
	str r6, [sp, #0x8]
	str r4, [sp, #0xc]
	ldr r0, [r5, #0x0]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x18]
	ldr r3, [sp, #0x1c]
	bl FUN_0200D3B0
	add r1, r4, #0x0
	add r1, #0x1e
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	add r2, r6, #0x0
	bl FUN_0200D678
	b _0200D788
_0200D756:
	add r0, r5, #0x0
	bl FUN_0201AB14
	str r0, [sp, #0x20]
	add r0, r5, #0x0
	bl FUN_0201AB18
	str r0, [sp, #0x24]
	add r0, r5, #0x0
	bl GetWindowWidth
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl GetWindowHeight
	str r7, [sp, #0x0]
	str r0, [sp, #0x4]
	str r6, [sp, #0x8]
	str r4, [sp, #0xc]
	ldr r0, [r5, #0x0]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x20]
	ldr r3, [sp, #0x24]
	bl FUN_0200CDD8
_0200D788:
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	bne _0200D794
	add r0, r5, #0x0
	bl CopyWindowToVram
_0200D794:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0200D18C
	add sp, #0x28
	pop {r3-r7, pc}

	thumb_func_start FUN_0200D7A0
FUN_0200D7A0: ; 0x0200D7A0
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	add r4, r1, #0x0
	str r2, [sp, #0x10]
	bl FUN_0201AB08
	str r0, [sp, #0x14]
	cmp r4, #0x1
	bhi _0200D7FE
	add r0, r5, #0x0
	bl FUN_0201AB14
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0201AB18
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl GetWindowWidth
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl GetWindowHeight
	sub r1, r7, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r0, r0, #0x2
	lsl r0, r0, #0x18
	sub r4, #0x9
	lsl r3, r4, #0x18
	add r6, #0xb
	str r1, [sp, #0x0]
	lsl r1, r6, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x4]
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	mov r2, #0x0
	str r2, [sp, #0xc]
	ldr r0, [r5, #0x0]
	ldr r1, [sp, #0x14]
	lsr r3, r3, #0x18
	bl FUN_02018540
	b _0200D846
_0200D7FE:
	add r0, r5, #0x0
	bl FUN_0201AB14
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0201AB18
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl GetWindowWidth
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl GetWindowHeight
	sub r1, r6, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x0]
	add r1, r7, #0x4
	lsl r1, r1, #0x18
	add r0, r0, #0x2
	lsr r1, r1, #0x18
	lsl r0, r0, #0x18
	str r1, [sp, #0x4]
	lsr r0, r0, #0x18
	sub r3, r4, #0x2
	lsl r3, r3, #0x18
	str r0, [sp, #0x8]
	mov r2, #0x0
	str r2, [sp, #0xc]
	ldr r0, [r5, #0x0]
	ldr r1, [sp, #0x14]
	lsr r3, r3, #0x18
	bl FUN_02018540
_0200D846:
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	bne _0200D852
	add r0, r5, #0x0
	bl FUN_02019570
_0200D852:
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200D858
FUN_0200D858: ; 0x0200D858
	push {r4-r7, lr}
	sub sp, #0x34
	str r0, [sp, #0x20]
	ldr r0, [r0, #0x0]
	str r1, [sp, #0x24]
	bl FUN_02016BB8
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x20]
	bl FUN_0201AB08
	bl FUN_020187B0
	add r5, r0, #0x0
	ldr r0, [sp, #0x28]
	ldr r1, _0200D970 ; =0x0000048C
	bl AllocFromHeap
	ldr r1, [sp, #0x24]
	add r4, r0, #0x0
	ldr r0, _0200D974 ; =0x00000404
	add r1, #0x12
	lsl r1, r1, #0x5
	add r0, r4, r0
	add r1, r5, r1
	mov r2, #0x80
	bl memcpy
	ldr r0, [sp, #0x28]
	mov r1, #0x80
	bl AllocFromHeap
	ldr r1, [sp, #0x24]
	mov r2, #0x20
	add r1, #0xa
	lsl r1, r1, #0x5
	str r1, [sp, #0x2c]
	add r1, r5, r1
	add r6, r0, #0x0
	bl memcpy
	ldr r0, [sp, #0x24]
	mov r2, #0x20
	add r0, #0xb
	lsl r7, r0, #0x5
	add r0, r6, #0x0
	add r0, #0x20
	add r1, r5, r7
	bl memcpy
	ldr r1, [sp, #0x2c]
	add r0, r6, #0x0
	add r0, #0x40
	add r1, r5, r1
	mov r2, #0x20
	bl memcpy
	add r0, r6, #0x0
	add r0, #0x60
	add r1, r5, r7
	mov r2, #0x20
	bl memcpy
	mov r5, #0x0
	add r7, r4, #0x4
_0200D8DA:
	lsl r0, r5, #0x7
	add r0, r7, r0
	add r1, r6, #0x0
	mov r2, #0x80
	bl memcpy
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x8
	blo _0200D8DA
	add r0, r6, #0x0
	bl FreeToHeap
	ldr r0, [sp, #0x28]
	mov r1, #0x17
	str r0, [sp, #0x0]
	mov r0, #0x26
	mov r2, #0x0
	add r3, sp, #0x30
	bl FUN_02006BB0
	mov r2, #0x80
	add r5, r0, #0x0
	str r2, [sp, #0x0]
	add r0, r4, #0x4
	str r0, [sp, #0x4]
	mov r3, #0x10
	str r3, [sp, #0x8]
	str r2, [sp, #0xc]
	mov r1, #0x0
	str r1, [sp, #0x10]
	str r1, [sp, #0x14]
	str r3, [sp, #0x18]
	str r2, [sp, #0x1c]
	ldr r0, [sp, #0x30]
	add r2, r1, #0x0
	ldr r0, [r0, #0x14]
	bl FUN_0200D148
	add r0, r5, #0x0
	bl FreeToHeap
	ldr r0, [sp, #0x20]
	ldr r1, _0200D978 ; =0x00000484
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x24]
	mov r2, #0x0
	strh r0, [r4, r1]
	add r0, r1, #0x2
	strb r2, [r4, r0]
	add r0, r1, #0x3
	ldrb r3, [r4, r0]
	mov r0, #0x7f
	bic r3, r0
	add r0, r1, #0x3
	strb r3, [r4, r0]
	add r0, r1, #0x4
	ldrb r3, [r4, r0]
	mov r0, #0x3
	bic r3, r0
	add r0, r1, #0x4
	strb r3, [r4, r0]
	ldr r0, _0200D97C ; =FUN_0200DB7C
	add r1, r4, #0x0
	bl FUN_0200CA60
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0200D980
	add r0, r4, #0x0
	add sp, #0x34
	pop {r4-r7, pc}
	nop
_0200D970: .word 0x0000048C
_0200D974: .word 0x00000404
_0200D978: .word 0x00000484
_0200D97C: .word FUN_0200DB7C

	thumb_func_start FUN_0200D980
FUN_0200D980: ; 0x0200D980
	push {r4-r7, lr}
	sub sp, #0x24
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r6, r1, #0x0
	bl FUN_0201AB08
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_0201AB14
	str r0, [sp, #0x18]
	ldr r0, [r5, #0x0]
	bl FUN_0201AB18
	str r0, [sp, #0x1c]
	ldr r0, [r5, #0x0]
	bl GetWindowWidth
	str r0, [sp, #0x20]
	cmp r6, #0x2
	bne _0200DA8A
	ldr r2, _0200DB78 ; =0x00000484
	add r1, r4, #0x0
	ldrh r0, [r5, r2]
	sub r2, #0x80
	add r2, r5, r2
	add r0, #0x12
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x0]
	mov r3, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02017E14
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	add r7, r0, #0x2
	ldr r0, [sp, #0x20]
	ldr r2, _0200DB78 ; =0x00000484
	add r6, r1, r0
	add r0, r6, #0x1
	str r0, [sp, #0x14]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldrh r2, [r5, r2]
	ldr r0, [r5, #0x0]
	ldr r3, [sp, #0x14]
	add r2, #0xa
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldr r2, _0200DB78 ; =0x00000484
	ldr r0, [r5, #0x0]
	ldrh r2, [r5, r2]
	add r6, r6, #0x2
	lsl r3, r6, #0x18
	add r2, #0xb
	lsl r2, r2, #0x10
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x1c]
	ldr r3, [sp, #0x14]
	add r7, r0, #0x3
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldr r2, _0200DB78 ; =0x00000484
	ldr r0, [r5, #0x0]
	ldrh r2, [r5, r2]
	lsl r3, r3, #0x18
	ldr r0, [r0, #0x0]
	add r2, #0xa
	lsl r2, r2, #0x10
	add r1, r4, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldr r2, _0200DB78 ; =0x00000484
	ldr r0, [r5, #0x0]
	ldrh r2, [r5, r2]
	lsl r3, r6, #0x18
	ldr r0, [r0, #0x0]
	add r2, #0xb
	lsl r2, r2, #0x10
	add r1, r4, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x0]
	bl FUN_02017CD0
	add sp, #0x24
	pop {r4-r7, pc}
_0200DA8A:
	ldr r3, _0200DB78 ; =0x00000484
	add r2, r5, #0x4
	ldrh r0, [r5, r3]
	add r3, r3, #0x3
	add r1, r4, #0x0
	add r0, #0x12
	str r0, [sp, #0x0]
	ldrb r3, [r5, r3]
	ldr r0, [r5, #0x0]
	lsl r3, r3, #0x19
	lsr r3, r3, #0x19
	lsl r3, r3, #0x7
	add r2, r2, r3
	ldr r0, [r0, #0x0]
	mov r3, #0x80
	bl FUN_02017E14
	cmp r6, #0x0
	beq _0200DB72
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	add r7, r0, #0x2
	ldr r0, [sp, #0x20]
	ldr r2, _0200DB78 ; =0x00000484
	add r6, r1, r0
	add r0, r6, #0x1
	str r0, [sp, #0x10]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldrh r2, [r5, r2]
	ldr r0, [r5, #0x0]
	ldr r3, [sp, #0x10]
	add r2, #0x12
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldr r2, _0200DB78 ; =0x00000484
	ldr r0, [r5, #0x0]
	ldrh r2, [r5, r2]
	add r6, r6, #0x2
	lsl r3, r6, #0x18
	add r2, #0x13
	lsl r2, r2, #0x10
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x1c]
	ldr r3, [sp, #0x10]
	add r7, r0, #0x3
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldr r2, _0200DB78 ; =0x00000484
	ldr r0, [r5, #0x0]
	ldrh r2, [r5, r2]
	lsl r3, r3, #0x18
	ldr r0, [r0, #0x0]
	add r2, #0x14
	lsl r2, r2, #0x10
	add r1, r4, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldr r2, _0200DB78 ; =0x00000484
	ldr r0, [r5, #0x0]
	ldrh r2, [r5, r2]
	lsl r3, r6, #0x18
	ldr r0, [r0, #0x0]
	add r2, #0x15
	lsl r2, r2, #0x10
	add r1, r4, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x0]
	bl FUN_02017CD0
_0200DB72:
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_0200DB78: .word 0x00000484

	thumb_func_start FUN_0200DB7C
FUN_0200DB7C: ; 0x0200DB7C
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, _0200DBE4 ; =0x00000488
	ldrb r2, [r1, r0]
	lsl r2, r2, #0x1e
	lsr r2, r2, #0x1e
	beq _0200DB9E
	cmp r2, #0x1
	bne _0200DB96
	add r0, r1, #0x0
	mov r1, #0x2
	bl FUN_0200D980
_0200DB96:
	add r0, r4, #0x0
	bl FUN_0200CAB4
	pop {r3-r5, pc}
_0200DB9E:
	sub r2, r0, #0x2
	ldrb r2, [r1, r2]
	add r3, r2, #0x1
	sub r2, r0, #0x2
	strb r3, [r1, r2]
	ldrb r2, [r1, r2]
	cmp r2, #0x10
	bne _0200DBE0
	mov r3, #0x0
	sub r2, r0, #0x2
	strb r3, [r1, r2]
	sub r2, r0, #0x1
	ldrb r2, [r1, r2]
	mov r4, #0x7f
	bic r2, r4
	sub r4, r0, #0x1
	ldrb r4, [r1, r4]
	sub r0, r0, #0x1
	lsl r4, r4, #0x19
	lsr r4, r4, #0x19
	add r5, r4, #0x1
	mov r4, #0x7
	and r4, r5
	lsl r4, r4, #0x18
	lsr r5, r4, #0x18
	mov r4, #0x7f
	and r4, r5
	orr r2, r4
	strb r2, [r1, r0]
	add r0, r1, #0x0
	add r1, r3, #0x0
	bl FUN_0200D980
_0200DBE0:
	pop {r3-r5, pc}
	nop
_0200DBE4: .word 0x00000488

	thumb_func_start FUN_0200DBE8
FUN_0200DBE8: ; 0x0200DBE8
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FreeToHeap
	add r0, r4, #0x0
	bl FUN_0200CAB4
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0200DBFC
FUN_0200DBFC: ; 0x0200DBFC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0200DC1C ; =FUN_0200DBE8
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_0200CA98
	ldr r1, _0200DC20 ; =0x00000488
	mov r0, #0x3
	ldrb r2, [r4, r1]
	bic r2, r0
	mov r0, #0x1
	orr r0, r2
	strb r0, [r4, r1]
	pop {r4, pc}
	nop
_0200DC1C: .word FUN_0200DBE8
_0200DC20: .word 0x00000488

	thumb_func_start FUN_0200DC24
FUN_0200DC24: ; 0x0200DC24
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0200DC44 ; =FUN_0200DBE8
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_0200CA98
	ldr r1, _0200DC48 ; =0x00000488
	mov r0, #0x3
	ldrb r2, [r4, r1]
	bic r2, r0
	mov r0, #0x2
	orr r0, r2
	strb r0, [r4, r1]
	pop {r4, pc}
	nop
_0200DC44: .word FUN_0200DBE8
_0200DC48: .word 0x00000488

	thumb_func_start FUN_0200DC4C
FUN_0200DC4C: ; 0x0200DC4C
	push {r4-r7, lr}
	sub sp, #0xc
	str r2, [sp, #0x4]
	ldr r5, [sp, #0x30]
	str r3, [sp, #0x8]
	add r6, r0, #0x0
	add r7, r1, #0x0
	str r5, [sp, #0x0]
	bl FUN_0200DD70
	add r4, r0, #0x0
	add r1, r5, #0x0
	bl FUN_0200DDAC
	add r0, r4, #0x0
	bl FUN_0200DDD8
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x8]
	add r0, r4, #0x0
	bl FUN_0200DE30
	add r2, sp, #0x10
	ldrh r1, [r2, #0x18]
	ldrb r2, [r2, #0x1c]
	add r0, r4, #0x0
	bl FUN_0200DE80
	add r2, sp, #0x10
	ldrb r1, [r2, #0x10]
	ldrh r2, [r2, #0x14]
	add r0, r4, #0x0
	bl FUN_0200DFD8
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_02017CD0
	ldr r0, _0200DCA0 ; =0x0000016F
	add r0, r4, r0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_0200DCA0: .word 0x0000016F

	thumb_func_start FUN_0200DCA4
FUN_0200DCA4: ; 0x0200DCA4
	push {r4-r7, lr}
	sub sp, #0xc
	str r2, [sp, #0x4]
	ldr r5, [sp, #0x2c]
	str r3, [sp, #0x8]
	add r6, r0, #0x0
	add r7, r1, #0x0
	str r5, [sp, #0x0]
	bl FUN_0200DD70
	add r4, r0, #0x0
	add r1, r5, #0x0
	bl FUN_0200DDAC
	add r0, r4, #0x0
	bl FUN_0200DDD8
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x8]
	add r0, r4, #0x0
	bl FUN_0200DE30
	ldr r1, [sp, #0x28]
	add r0, r4, #0x0
	bl FUN_0200DEC0
	add r2, sp, #0x10
	ldrb r1, [r2, #0x10]
	ldrh r2, [r2, #0x14]
	add r0, r4, #0x0
	bl FUN_0200DFD8
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_02017CD0
	ldr r0, _0200DCF4 ; =0x0000016F
	add r0, r4, r0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_0200DCF4: .word 0x0000016F

	thumb_func_start FUN_0200DCF8
FUN_0200DCF8: ; 0x0200DCF8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0200DD6C ; =0x0000016F
	add r4, r1, #0x0
	ldrb r1, [r4, r0]
	cmp r1, #0x1
	beq _0200DD10
	cmp r1, #0x2
	beq _0200DD2E
	cmp r1, #0x3
	beq _0200DD40
	b _0200DD54
_0200DD10:
	add r0, r4, #0x0
	bl FUN_0200E188
	mov r0, #0x59
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_0200C3DC
	add r0, r4, #0x0
	bl MOD05_021D99F8
	add r0, r5, #0x0
	bl FUN_0200621C
	pop {r3-r5, pc}
_0200DD2E:
	mov r1, #0x3
	strb r1, [r4, r0]
	sub r0, #0xb
	ldr r0, [r4, r0]
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	bl FUN_02020130
	b _0200DD54
_0200DD40:
	sub r0, #0xb
	ldr r0, [r4, r0]
	ldr r0, [r0, #0x0]
	bl FUN_0202022C
	cmp r0, #0x6
	bne _0200DD54
	ldr r0, _0200DD6C ; =0x0000016F
	mov r1, #0x0
	strb r1, [r4, r0]
_0200DD54:
	mov r0, #0x59
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	ldr r0, [r4, #0x0]
	bl FUN_0201FDEC
	pop {r3-r5, pc}
	.balign 4
_0200DD6C: .word 0x0000016F

	thumb_func_start FUN_0200DD70
FUN_0200DD70: ; 0x0200DD70
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r7, r3, #0x0
	mov r1, #0x17
	add r6, r2, #0x0
	ldr r0, _0200DDA4 ; =FUN_0200DCF8
	ldr r3, [sp, #0x18]
	lsl r1, r1, #0x4
	mov r2, #0x0
	bl FUN_020061E8
	bl FUN_0201B6C8
	ldr r1, _0200DDA8 ; =0x0000016F
	mov r2, #0x0
	strb r2, [r0, r1]
	sub r2, r1, #0x7
	str r5, [r0, r2]
	sub r2, r1, #0x3
	strb r4, [r0, r2]
	sub r2, r1, #0x2
	strb r6, [r0, r2]
	sub r1, r1, #0x1
	strb r7, [r0, r1]
	pop {r3-r7, pc}
	.balign 4
_0200DDA4: .word FUN_0200DCF8
_0200DDA8: .word 0x0000016F

	thumb_func_start FUN_0200DDAC
FUN_0200DDAC: ; 0x0200DDAC
	push {r4-r6, lr}
	sub sp, #0x18
	ldr r5, _0200DDD4 ; =UNK_020ECEA8
	add r4, sp, #0x0
	add r6, r0, #0x0
	add r3, r1, #0x0
	add r2, r4, #0x0
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	add r1, r2, #0x0
	add r0, r6, #0x0
	mov r2, #0x1
	bl MOD05_021D959C
	add sp, #0x18
	pop {r4-r6, pc}
	.balign 4
_0200DDD4: .word UNK_020ECEA8

	thumb_func_start FUN_0200DDD8
FUN_0200DDD8: ; 0x0200DDD8
	push {r3-r4, lr}
	sub sp, #0xc
	mov r1, #0x1
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, _0200DE2C ; =0x00015CD5
	mov r2, #0x31
	str r1, [sp, #0x8]
	mov r1, #0x26
	mov r3, #0x0
	add r4, r0, #0x0
	bl MOD05_021D967C
	ldr r0, _0200DE2C ; =0x00015CD5
	mov r1, #0x26
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r2, #0x2f
	mov r3, #0x0
	bl MOD05_021D96F4
	ldr r0, _0200DE2C ; =0x00015CD5
	mov r1, #0x26
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r2, #0x2e
	mov r3, #0x0
	bl MOD05_021D9708
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r0, _0200DE2C ; =0x00015CD5
	mov r1, #0x26
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r2, #0x30
	mov r3, #0x0
	bl MOD05_021D971C
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_0200DE2C: .word 0x00015CD5

	thumb_func_start FUN_0200DE30
FUN_0200DE30: ; 0x0200DE30
	push {r4-r7, lr}
	sub sp, #0x34
	ldr r5, _0200DE7C ; =UNK_020ECEC0
	add r6, r2, #0x0
	add r4, r0, #0x0
	add r7, r1, #0x0
	add r3, sp, #0x0
	mov r2, #0x6
_0200DE40:
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _0200DE40
	ldr r0, [r5, #0x0]
	str r0, [r3, #0x0]
	add r0, r7, #0x5
	lsl r1, r0, #0x3
	add r0, sp, #0x0
	strh r1, [r0, #0x0]
	add r1, r6, #0x5
	lsl r1, r1, #0x3
	strh r1, [r0, #0x2]
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl MOD05_021D9820
	mov r1, #0x59
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r0, [r4, #0x0]
	bl FUN_0201FDEC
	mov r0, #0x10
	mov r1, #0x1
	bl GX_EngineBToggleLayers
	add sp, #0x34
	pop {r4-r7, pc}
	nop
_0200DE7C: .word UNK_020ECEC0

	thumb_func_start FUN_0200DE80
FUN_0200DE80: ; 0x0200DE80
	push {r4-r7, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	ldr r0, _0200DEBC ; =0x00000162
	add r4, r1, #0x0
	ldrh r0, [r5, r0]
	add r6, r2, #0x0
	bl FUN_02006D98
	add r7, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	add r0, sp, #0xc
	add r1, r4, #0x0
	add r2, r6, #0x0
	mov r3, #0x2
	bl FUN_02068C00
	add r0, r5, #0x0
	add r1, sp, #0xc
	bl FUN_0200DEF4
	add r0, r7, #0x0
	bl FUN_020072E8
	add sp, #0x1c
	pop {r4-r7, pc}
	nop
_0200DEBC: .word 0x00000162

	thumb_func_start FUN_0200DEC0
FUN_0200DEC0: ; 0x0200DEC0
	push {r4-r6, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, _0200DEF0 ; =0x00000162
	add r4, r1, #0x0
	ldrh r0, [r5, r0]
	bl FUN_02006D98
	add r6, r0, #0x0
	add r0, sp, #0x0
	add r1, r4, #0x0
	mov r2, #0x2
	bl FUN_02068B68
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl FUN_0200DEF4
	add r0, r6, #0x0
	bl FUN_020072E8
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_0200DEF0: .word 0x00000162

	thumb_func_start FUN_0200DEF4
FUN_0200DEF4: ; 0x0200DEF4
	push {r3-r7, lr}
	sub sp, #0x28
	add r5, r0, #0x0
	ldr r0, _0200DFC8 ; =0x00000162
	add r6, r1, #0x0
	mov r1, #0x19
	ldrh r0, [r5, r0]
	lsl r1, r1, #0x8
	bl AllocFromHeap
	add r2, sp, #0x18
	ldr r3, _0200DFCC ; =UNK_020ECE98
	add r4, r0, #0x0
	add r7, r2, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	str r4, [sp, #0x0]
	ldr r2, _0200DFC8 ; =0x00000162
	ldrh r0, [r6, #0x0]
	ldrh r1, [r6, #0x2]
	ldrh r2, [r5, r2]
	add r3, r7, #0x0
	bl FUN_02012400
	ldr r3, _0200DFD0 ; =UNK_020ECE88
	add r2, sp, #0x8
	add r7, r2, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	mov r0, #0x32
	lsl r0, r0, #0x6
	add r0, r4, r0
	str r0, [sp, #0x0]
	ldr r2, _0200DFC8 ; =0x00000162
	ldrh r0, [r6, #0x0]
	ldrh r1, [r6, #0x2]
	ldrh r2, [r5, r2]
	add r3, r7, #0x0
	bl FUN_02012400
	mov r0, #0x13
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	ldr r1, _0200DFD4 ; =0x00015CD5
	bl FUN_020094F0
	bl FUN_02009C5C
	mov r1, #0x1
	str r0, [sp, #0x4]
	bl FUN_020B1A14
	mov r1, #0x19
	add r7, r0, #0x0
	add r0, r4, #0x0
	lsl r1, r1, #0x8
	bl DC_FlushRange
	mov r2, #0x19
	add r0, r4, #0x0
	add r1, r7, #0x0
	lsl r2, r2, #0x8
	bl GX_LoadOBJ
	add r0, r4, #0x0
	bl FreeToHeap
	ldr r2, _0200DFC8 ; =0x00000162
	ldrh r0, [r6, #0x0]
	ldrh r1, [r6, #0x4]
	ldrh r2, [r5, r2]
	bl FUN_02012470
	add r4, r0, #0x0
	mov r0, #0x4d
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldr r1, _0200DFD4 ; =0x00015CD5
	bl FUN_020094F0
	ldr r1, [sp, #0x4]
	bl FUN_02009E54
	mov r1, #0x1
	bl FUN_020B19C4
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x20
	bl DC_FlushRange
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x20
	bl GX_LoadOBJPltt
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x28
	pop {r3-r7, pc}
	nop
_0200DFC8: .word 0x00000162
_0200DFCC: .word UNK_020ECE98
_0200DFD0: .word UNK_020ECE88
_0200DFD4: .word 0x00015CD5

	thumb_func_start FUN_0200DFD8
FUN_0200DFD8: ; 0x0200DFD8
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r3, _0200E184 ; =0x0000016E
	add r5, r0, #0x0
	ldrb r0, [r5, r3]
	add r4, r1, #0x0
	sub r1, r3, #0x2
	sub r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	str r4, [sp, #0xc]
	sub r0, r3, #0x6
	sub r3, r3, #0x1
	ldrb r3, [r5, r3]
	ldrb r1, [r5, r1]
	ldr r0, [r5, r0]
	sub r3, r3, #0x1
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	add r6, r2, #0x0
	bl FUN_02018540
	ldr r3, _0200E184 ; =0x0000016E
	add r2, r6, #0x1
	ldrb r0, [r5, r3]
	sub r1, r3, #0x2
	lsl r2, r2, #0x10
	sub r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0xa
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	str r4, [sp, #0xc]
	sub r0, r3, #0x6
	sub r3, r3, #0x1
	ldrb r1, [r5, r1]
	ldrb r3, [r5, r3]
	ldr r0, [r5, r0]
	lsr r2, r2, #0x10
	bl FUN_02018540
	ldr r3, _0200E184 ; =0x0000016E
	add r2, r6, #0x2
	ldrb r0, [r5, r3]
	lsl r2, r2, #0x10
	sub r1, r3, #0x2
	sub r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	str r4, [sp, #0xc]
	sub r0, r3, #0x6
	sub r3, r3, #0x1
	ldrb r3, [r5, r3]
	ldrb r1, [r5, r1]
	ldr r0, [r5, r0]
	add r3, #0xa
	lsl r3, r3, #0x18
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r3, _0200E184 ; =0x0000016E
	add r2, r6, #0x4
	ldrb r0, [r5, r3]
	lsl r2, r2, #0x10
	sub r1, r3, #0x2
	str r0, [sp, #0x0]
	mov r0, #0xa
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	str r4, [sp, #0xc]
	sub r0, r3, #0x6
	sub r3, r3, #0x1
	ldrb r1, [r5, r1]
	ldrb r3, [r5, r3]
	ldr r0, [r5, r0]
	lsr r2, r2, #0x10
	bl FUN_02018540
	ldr r3, _0200E184 ; =0x0000016E
	add r2, r6, #0x3
	ldrb r0, [r5, r3]
	lsl r2, r2, #0x10
	sub r1, r3, #0x2
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r0, #0xa
	str r0, [sp, #0x8]
	str r4, [sp, #0xc]
	sub r0, r3, #0x6
	sub r3, r3, #0x1
	ldrb r3, [r5, r3]
	ldrb r1, [r5, r1]
	ldr r0, [r5, r0]
	sub r3, r3, #0x1
	lsl r3, r3, #0x18
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r3, _0200E184 ; =0x0000016E
	add r2, r6, #0x5
	ldrb r0, [r5, r3]
	lsl r2, r2, #0x10
	sub r1, r3, #0x2
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r0, #0xa
	str r0, [sp, #0x8]
	str r4, [sp, #0xc]
	sub r0, r3, #0x6
	sub r3, r3, #0x1
	ldrb r3, [r5, r3]
	ldrb r1, [r5, r1]
	ldr r0, [r5, r0]
	add r3, #0xa
	lsl r3, r3, #0x18
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r3, _0200E184 ; =0x0000016E
	add r2, r6, #0x6
	ldrb r0, [r5, r3]
	lsl r2, r2, #0x10
	sub r1, r3, #0x2
	add r0, #0xa
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	str r4, [sp, #0xc]
	sub r0, r3, #0x6
	sub r3, r3, #0x1
	ldrb r3, [r5, r3]
	ldrb r1, [r5, r1]
	ldr r0, [r5, r0]
	sub r3, r3, #0x1
	lsl r3, r3, #0x18
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r3, _0200E184 ; =0x0000016E
	add r2, r6, #0x7
	ldrb r0, [r5, r3]
	sub r1, r3, #0x2
	lsl r2, r2, #0x10
	add r0, #0xa
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0xa
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	str r4, [sp, #0xc]
	sub r0, r3, #0x6
	sub r3, r3, #0x1
	ldrb r1, [r5, r1]
	ldrb r3, [r5, r3]
	ldr r0, [r5, r0]
	lsr r2, r2, #0x10
	bl FUN_02018540
	ldr r3, _0200E184 ; =0x0000016E
	add r6, #0x8
	ldrb r0, [r5, r3]
	lsl r2, r6, #0x10
	sub r1, r3, #0x2
	add r0, #0xa
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	str r4, [sp, #0xc]
	sub r0, r3, #0x6
	sub r3, r3, #0x1
	ldrb r3, [r5, r3]
	ldrb r1, [r5, r1]
	ldr r0, [r5, r0]
	add r3, #0xa
	lsl r3, r3, #0x18
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	mov r1, #0x5a
	lsl r1, r1, #0x2
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldrb r1, [r5, r1]
	bl FUN_0201AC68
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_0200E184: .word 0x0000016E

	thumb_func_start FUN_0200E188
FUN_0200E188: ; 0x0200E188
	push {r4, lr}
	sub sp, #0x10
	ldr r3, _0200E1CC ; =0x0000016E
	add r4, r0, #0x0
	ldrb r0, [r4, r3]
	mov r2, #0x0
	sub r1, r3, #0x2
	sub r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0xc
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	str r2, [sp, #0xc]
	sub r0, r3, #0x6
	sub r3, r3, #0x1
	ldrb r3, [r4, r3]
	ldrb r1, [r4, r1]
	ldr r0, [r4, r0]
	sub r3, r3, #0x1
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FUN_02018540
	mov r1, #0x5a
	lsl r1, r1, #0x2
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldrb r1, [r4, r1]
	bl FUN_0201AC68
	add sp, #0x10
	pop {r4, pc}
	.balign 4
_0200E1CC: .word 0x0000016E
