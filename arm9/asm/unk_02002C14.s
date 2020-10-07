    .include "asm/macros.inc"
    .include "global.inc"

	.section .bss

	.global UNK_02106FC8
UNK_02106FC8: ; 0x02106FC8
	.space 0x4

	.global UNK_02106FCC
UNK_02106FCC: ; 0x02106FCC
	.space 0xa4

	.section .rodata

	.global UNK_020ECB54
UNK_020ECB54: ; 0x020ECB54
	.short 0x0000, 0x0000
	.short 0x0001, 0x0000
	.short 0x0002, 0x0000
	.short 0x0003, 0x0000

	.global UNK_020ECB64
UNK_020ECB64: ; 0x020ECB64
	.byte 0x0B, 0x10, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x02
	.byte 0x0B, 0x10, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x02
	.byte 0x0B, 0x10, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x02
	.byte 0x0B, 0x10, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_02002C14
FUN_02002C14: ; 0x02002C14
	push {r4, lr}
	ldr r0, _02002C44 ; =UNK_02106FCC
	ldr r4, _02002C48 ; =UNK_02106FC8
	mov r1, #0x0
	str r0, [r4, #0x0]
	add r2, r1, #0x0
	add r0, r1, #0x0
_02002C22:
	ldr r3, [r4, #0x0]
	add r1, r1, #0x1
	add r3, r3, r2
	add r3, #0x84
	str r0, [r3, #0x0]
	ldr r3, [r4, #0x0]
	add r3, r3, r2
	add r3, #0x94
	add r2, r2, #0x4
	str r0, [r3, #0x0]
	cmp r1, #0x4
	blo _02002C22
	ldr r0, _02002C4C ; =UNK_020ECB64
	bl FUN_0201BCBC
	pop {r4, pc}
	nop
_02002C44: .word UNK_02106FCC
_02002C48: .word UNK_02106FC8
_02002C4C: .word UNK_020ECB64

	thumb_func_start FUN_02002C50
FUN_02002C50: ; 0x02002C50
	push {r3-r4, lr}
	sub sp, #0x4
	str r1, [sp, #0x0]
	lsl r4, r0, #0x2
	ldr r1, _02002C78 ; =UNK_020ECB54
	ldr r3, _02002C7C ; =UNK_020ECB54 + 2
	ldrh r1, [r1, r4]
	ldrh r3, [r3, r4]
	mov r0, #0xe
	mov r2, #0x1
	bl FUN_02021590
	ldr r1, _02002C80 ; =UNK_02106FC8
	ldr r1, [r1, #0x0]
	add r1, r1, r4
	add r1, #0x94
	str r0, [r1, #0x0]
	add sp, #0x4
	pop {r3-r4, pc}
	nop
_02002C78: .word UNK_020ECB54
_02002C7C: .word UNK_020ECB54 + 2
_02002C80: .word UNK_02106FC8

	thumb_func_start FUN_02002C84
FUN_02002C84: ; 0x02002C84
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	cmp r4, #0x4
	blt _02002C92
	bl ErrorHandling
_02002C92:
	ldr r0, _02002CBC ; =UNK_02106FC8
	lsl r4, r4, #0x2
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02002CA6
	bl ErrorHandling
_02002CA6:
	ldr r0, _02002CBC ; =UNK_02106FC8
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r2, r5, #0x0
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl FUN_020215E0
	pop {r3-r5, pc}
	nop
_02002CBC: .word UNK_02106FC8

	thumb_func_start FUN_02002CC0
FUN_02002CC0: ; 0x02002CC0
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x4
	blt _02002CCC
	bl ErrorHandling
_02002CCC:
	ldr r0, _02002CF4 ; =UNK_02106FC8
	lsl r4, r4, #0x2
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02002CE0
	bl ErrorHandling
_02002CE0:
	ldr r0, _02002CF4 ; =UNK_02106FC8
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	mov r2, #0x0
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl FUN_020215E0
	pop {r4, pc}
	.balign 4
_02002CF4: .word UNK_02106FC8

	thumb_func_start FUN_02002CF8
FUN_02002CF8: ; 0x02002CF8
	push {r3-r7, lr}
	add r4, r0, #0x0
	cmp r4, #0x4
	blt _02002D04
	bl ErrorHandling
_02002D04:
	ldr r0, _02002D8C ; =UNK_02106FC8
	lsl r6, r4, #0x2
	ldr r7, [r0, #0x0]
	add r0, r7, r6
	add r0, #0x84
	ldr r0, [r0, #0x0]
	mov r12, r0
	cmp r0, #0x0
	beq _02002D68
	ldr r2, _02002D90 ; =UNK_020ECB54
	mov r1, #0x0
	ldrh r0, [r2, r6]
	add r3, r7, #0x0
_02002D1E:
	cmp r1, r4
	beq _02002D3E
	ldrh r5, [r2, #0x0]
	cmp r5, r0
	bne _02002D3E
	add r5, r3, #0x0
	add r5, #0x94
	ldr r5, [r5, #0x0]
	cmp r5, #0x0
	beq _02002D3E
	lsl r0, r1, #0x2
	add r2, r7, r0
	add r2, #0x84
	mov r0, r12
	str r0, [r2, #0x0]
	b _02002D48
_02002D3E:
	add r1, r1, #0x1
	add r2, r2, #0x4
	add r3, r3, #0x4
	cmp r1, #0x4
	blo _02002D1E
_02002D48:
	cmp r1, #0x4
	bne _02002D68
	ldr r0, _02002D8C ; =UNK_02106FC8
	lsl r5, r4, #0x2
	ldr r0, [r0, #0x0]
	add r0, r0, r5
	add r0, #0x84
	ldr r0, [r0, #0x0]
	bl FreeToHeap
	ldr r0, _02002D8C ; =UNK_02106FC8
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, r5
	add r0, #0x84
	str r1, [r0, #0x0]
_02002D68:
	ldr r0, _02002D8C ; =UNK_02106FC8
	ldr r0, [r0, #0x0]
	add r0, r0, r6
	add r0, #0x94
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02002D88
	bl FUN_020215C8
	ldr r0, _02002D8C ; =UNK_02106FC8
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x2
	add r0, r1, r0
	add r0, #0x94
	str r2, [r0, #0x0]
_02002D88:
	pop {r3-r7, pc}
	nop
_02002D8C: .word UNK_02106FC8
_02002D90: .word UNK_020ECB54

	thumb_func_start FUN_02002D94
FUN_02002D94: ; 0x02002D94
	push {r3, lr}
	ldr r2, _02002DAC ; =UNK_02106FC8
	lsl r0, r0, #0x2
	ldr r2, [r2, #0x0]
	add r0, r2, r0
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl FUN_02021750
	ldr r0, _02002DAC ; =UNK_02106FC8
	ldr r0, [r0, #0x0]
	pop {r3, pc}
	.balign 4
_02002DAC: .word UNK_02106FC8

	thumb_func_start FontFunc
FontFunc: ; 0x02002DB0
	push {r4, lr}
	add r3, r1, #0x0
	add r3, #0x1c
	ldrb r2, [r3, #0x1]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x1f
	bne _02002DD8
	ldrb r2, [r3, #0x0]
	mov r4, #0xf
	lsl r0, r0, #0x18
	bic r2, r4
	lsr r4, r0, #0x18
	mov r0, #0xf
	and r0, r4
	orr r0, r2
	strb r0, [r3, #0x0]
	ldrb r2, [r3, #0x1]
	mov r0, #0x80
	orr r0, r2
	strb r0, [r3, #0x1]
_02002DD8:
	add r0, r1, #0x0
	bl RenderText
	pop {r4, pc}

	thumb_func_start FUN_02002DE0
FUN_02002DE0: ; 0x02002DE0
	push {r4-r6, lr}
	lsl r4, r0, #0x2
	ldr r0, _02002E10 ; =UNK_02106FC8
	add r5, r1, #0x0
	ldr r0, [r0, #0x0]
	add r6, r2, #0x0
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02002DFA
	bl ErrorHandling
_02002DFA:
	ldr r0, _02002E10 ; =UNK_02106FC8
	add r1, r5, #0x0
	ldr r0, [r0, #0x0]
	add r2, r6, #0x0
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl FUN_020218D8
	pop {r4-r6, pc}
	nop
_02002E10: .word UNK_02106FC8

	thumb_func_start FUN_02002E14
FUN_02002E14: ; 0x02002E14
	push {r4-r6, lr}
	lsl r4, r0, #0x2
	ldr r0, _02002E48 ; =UNK_02106FC8
	add r5, r1, #0x0
	ldr r0, [r0, #0x0]
	add r6, r2, #0x0
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02002E2E
	bl ErrorHandling
_02002E2E:
	add r0, r5, #0x0
	bl String_c_str
	add r1, r0, #0x0
	ldr r0, _02002E48 ; =UNK_02106FC8
	add r2, r6, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl FUN_020218D8
	pop {r4-r6, pc}
	.balign 4
_02002E48: .word UNK_02106FC8

	thumb_func_start FUN_02002E4C
FUN_02002E4C: ; 0x02002E4C
	mov r2, #0x0
	cmp r1, #0x7
	bhi _02002EAC
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02002E5E: ; jump table (using 16-bit offset)
	.short _02002E6E - _02002E5E - 2; case 0
	.short _02002E76 - _02002E5E - 2; case 1
	.short _02002E7E - _02002E5E - 2; case 2
	.short _02002E86 - _02002E5E - 2; case 3
	.short _02002E8E - _02002E5E - 2; case 4
	.short _02002E96 - _02002E5E - 2; case 5
	.short _02002E9E - _02002E5E - 2; case 6
	.short _02002EA6 - _02002E5E - 2; case 7
_02002E6E:
	lsl r1, r0, #0x3
	ldr r0, _02002EB0 ; =UNK_020ECB64
	ldrb r2, [r0, r1]
	b _02002EAC
_02002E76:
	lsl r1, r0, #0x3
	ldr r0, _02002EB4 ; =UNK_020ECB64 + 1
	ldrb r2, [r0, r1]
	b _02002EAC
_02002E7E:
	lsl r1, r0, #0x3
	ldr r0, _02002EB8 ; =UNK_020ECB64 + 2
	ldrb r2, [r0, r1]
	b _02002EAC
_02002E86:
	lsl r1, r0, #0x3
	ldr r0, _02002EBC ; =UNK_020ECB64 + 3
	ldrb r2, [r0, r1]
	b _02002EAC
_02002E8E:
	lsl r1, r0, #0x3
	ldr r0, _02002EC0 ; =UNK_020ECB64 + 4
	ldrb r2, [r0, r1]
	b _02002EAC
_02002E96:
	lsl r1, r0, #0x3
	ldr r0, _02002EC4 ; =UNK_020ECB64 + 5
	ldrb r2, [r0, r1]
	b _02002EAC
_02002E9E:
	lsl r1, r0, #0x3
	ldr r0, _02002EC8 ; =UNK_020ECB64 + 6
	ldrb r2, [r0, r1]
	b _02002EAC
_02002EA6:
	lsl r1, r0, #0x3
	ldr r0, _02002ECC ; =UNK_020ECB64 + 7
	ldrb r2, [r0, r1]
_02002EAC:
	add r0, r2, #0x0
	bx lr
	.balign 4
_02002EB0: .word UNK_020ECB64
_02002EB4: .word UNK_020ECB64 + 1
_02002EB8: .word UNK_020ECB64 + 2
_02002EBC: .word UNK_020ECB64 + 3
_02002EC0: .word UNK_020ECB64 + 4
_02002EC4: .word UNK_020ECB64 + 5
_02002EC8: .word UNK_020ECB64 + 6
_02002ECC: .word UNK_020ECB64 + 7

	thumb_func_start FUN_02002ED0
FUN_02002ED0: ; 0x02002ED0
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	mov r0, #0x20
	str r0, [sp, #0x0]
	add r3, r1, #0x0
	str r2, [sp, #0x4]
	mov r0, #0xe
	mov r1, #0x6
	add r2, r4, #0x0
	bl FUN_02006930
	add sp, #0x8
	pop {r4, pc}

	thumb_func_start FUN_02002EEC
FUN_02002EEC: ; 0x02002EEC
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	mov r0, #0x20
	str r0, [sp, #0x0]
	add r3, r1, #0x0
	str r2, [sp, #0x4]
	mov r0, #0xe
	mov r1, #0x7
	add r2, r4, #0x0
	bl FUN_02006930
	add sp, #0x8
	pop {r4, pc}
