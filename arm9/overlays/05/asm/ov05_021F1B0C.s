	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021F1B0C
ov05_021F1B0C: ; 0x021F1B0C
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl ov05_021F1C34
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, sp, #0
	bl sub_02058BB4
	add sp, #0xc
	pop {r3, r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021F1B2C
ov05_021F1B2C: ; 0x021F1B2C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl sub_02058628
	ldr r4, [r0]
	add r0, r5, #0
	bl ov05_021F2E28
	cmp r0, #1
	beq _021F1B54
	cmp r4, #0
	beq _021F1B54
	add r0, r5, #0
	bl ov05_021F1C48
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl sub_0201F854
_021F1B54:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021F1B58
ov05_021F1B58: ; 0x021F1B58
	ldr r3, _021F1B5C ; =ov05_021F1CA4
	bx r3
	.balign 4, 0
_021F1B5C: .word ov05_021F1CA4

	thumb_func_start ov05_021F1B60
ov05_021F1B60: ; 0x021F1B60
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl sub_02058628
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021F1B76
	add r1, r4, #4
	bl ov05_021F20D8
_021F1B76:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F2060
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0x14
	bl MapObject_SetFlagsBits
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021F1B8C
ov05_021F1B8C: ; 0x021F1B8C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl sub_02058628
	add r4, r0, #0
	add r0, r5, #0
	bl ov05_021F2E28
	cmp r0, #1
	beq _021F1BCC
	ldr r0, [r4]
	cmp r0, #0
	bne _021F1BAE
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F1FC8
_021F1BAE:
	ldr r0, [r4]
	cmp r0, #0
	beq _021F1BCC
	add r1, r4, #4
	bl ov05_021F20F8
	ldr r1, [r4]
	add r0, r5, #0
	bl ov05_021F2F48
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0x14
	bl sub_02058418
_021F1BCC:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021F1BD0
ov05_021F1BD0: ; 0x021F1BD0
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl ov05_021F1C34
	mov r1, #0
	mov r0, #6
	lsl r0, r0, #0xe
	str r0, [sp, #4]
	str r1, [sp]
	str r1, [sp, #8]
	add r0, r4, #0
	add r1, sp, #0
	bl sub_02058BB4
	add sp, #0xc
	pop {r3, r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021F1BF4
ov05_021F1BF4: ; 0x021F1BF4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl sub_02058628
	ldr r4, [r0]
	add r0, r5, #0
	bl ov05_021F2E28
	cmp r0, #1
	beq _021F1C12
	cmp r4, #0
	beq _021F1C12
	add r0, r5, #0
	bl ov05_021F1C48
_021F1C12:
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021F1C14
ov05_021F1C14: ; 0x021F1C14
	ldr r3, _021F1C18 ; =ov05_021F1CA4
	bx r3
	.balign 4, 0
_021F1C18: .word ov05_021F1CA4

	thumb_func_start ov05_021F1C1C
ov05_021F1C1C: ; 0x021F1C1C
	ldr r3, _021F1C20 ; =sub_02058628
	bx r3
	.balign 4, 0
_021F1C20: .word sub_02058628

	thumb_func_start ov05_021F1C24
ov05_021F1C24: ; 0x021F1C24
	push {r3, lr}
	bl sub_02058628
	bl ov05_021F1C30
	pop {r3, pc}

	thumb_func_start ov05_021F1C30
ov05_021F1C30: ; 0x021F1C30
	ldr r0, [r0]
	bx lr

	thumb_func_start ov05_021F1C34
ov05_021F1C34: ; 0x021F1C34
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0x10
	bl sub_02058604
	add r1, r0, #0
	add r0, r4, #0
	bl ov05_021F1FC8
	pop {r4, pc}

	thumb_func_start ov05_021F1C48
ov05_021F1C48: ; 0x021F1C48
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl sub_02058628
	ldr r4, [r0]
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F2F48
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F1C64
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021F1C64
ov05_021F1C64: ; 0x021F1C64
	push {r4, r5, r6, lr}
	mov r4, #1
	add r6, r1, #0
	lsl r1, r4, #9
	add r5, r0, #0
	bl MapObject_TestFlagsBits
	cmp r0, #1
	bne _021F1C78
	mov r4, #0
_021F1C78:
	mov r1, #1
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl MapObject_TestFlagsBits
	cmp r0, #1
	bne _021F1C96
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl MapObject_TestFlagsBits
	cmp r0, #0
	bne _021F1C96
	mov r4, #0
_021F1C96:
	lsl r1, r4, #0x18
	add r0, r6, #0
	lsr r1, r1, #0x18
	bl sub_0201F80C
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021F1CA4
ov05_021F1CA4: ; 0x021F1CA4
	push {r4, lr}
	add r4, r0, #0
	bl sub_02058628
	add r1, r0, #0
	add r0, r4, #0
	bl ov05_021F2060
	pop {r4, pc}
	.balign 4, 0
