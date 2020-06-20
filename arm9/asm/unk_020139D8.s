    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020ED580
UNK_020ED580: ; 0x020ED580
	.byte 0xC0, 0x04, 0xF0, 0x04

	.global UNK_020ED584
UNK_020ED584: ; 0x020ED584
	.byte 0x4E, 0x02, 0xD2, 0x03

	.global UNK_020ED588
UNK_020ED588: ; 0x020ED588
	.byte 0xBB, 0x04, 0x00, 0x05

	.global UNK_020ED58C
UNK_020ED58C: ; 0x020ED58C
	.byte 0x41, 0x04, 0x99, 0x05

	.global UNK_020ED590
UNK_020ED590: ; 0x020ED590
	.byte 0x2C, 0x04, 0x9D, 0x05

	.global UNK_020ED594
UNK_020ED594: ; 0x020ED594
	.byte 0x7A, 0x04, 0x8D, 0x04

	.global UNK_020ED598
UNK_020ED598: ; 0x020ED598
	.byte 0xB6, 0x04, 0x05, 0x05

	.global UNK_020ED59C
UNK_020ED59C: ; 0x020ED59C
	.byte 0xFC, 0x04, 0x96, 0x05

	.global UNK_020ED5A0
UNK_020ED5A0: ; 0x020ED5A0
	.byte 0x8F, 0x04, 0x97, 0x04

	.global UNK_020ED5A4
UNK_020ED5A4: ; 0x020ED5A4
	.byte 0xB0, 0x04, 0xFF, 0x04

	.global UNK_020ED5A8
UNK_020ED5A8: ; 0x020ED5A8
	.byte 0xA7, 0x04, 0xE1, 0x04

	.global UNK_020ED5AC
UNK_020ED5AC: ; 0x020ED5AC
	.byte 0x79, 0x04, 0x98, 0x04, 0x9B, 0x04, 0x9C, 0x04

	.global UNK_020ED5B4
UNK_020ED5B4: ; 0x020ED5B4
	.byte 0x01

	.global UNK_020ED5B5
UNK_020ED5B5: ; 0x020ED5B5
	.byte 0x00, 0x02, 0x01, 0x03, 0x02, 0x04, 0x03, 0x05, 0x04, 0x07, 0x05

	.global UNK_020ED5C0
UNK_020ED5C0: ; 0x020ED5C0
	.byte 0x6A, 0x01, 0x4D, 0x02, 0x35, 0x02, 0x29, 0x02, 0x84, 0x01, 0x85, 0x01, 0x86, 0x01, 0x87, 0x01
	.byte 0x88, 0x01, 0x89, 0x01, 0x8A, 0x01

	.global UNK_020ED5D6
UNK_020ED5D6: ; 0x020ED5D6
	.byte 0xF0, 0x01, 0xD4, 0x01, 0x12, 0x00, 0x7C, 0x00, 0x26, 0x00, 0x26, 0x00, 0x6B, 0x00, 0x68, 0x00
	.byte 0x2F, 0x00, 0x20, 0x00, 0x17, 0x00

	.global UNK_020ED5EC
UNK_020ED5EC: ; 0x020ED5EC
	.word UNK_020ED58C
	.byte 2
	.word UNK_020ED580
	.byte 2
	.word UNK_020ED5A8
	.byte 2
	.word UNK_020ED5AC
	.byte 4
	.word UNK_020ED5A0
	.byte 2
	.word UNK_020ED59C
	.byte 2
	.word UNK_020ED588
	.byte 2
	.word UNK_020ED584
	.byte 2
	.word UNK_020ED590
	.byte 2
	.word UNK_020ED5A4
	.byte 2
	.word UNK_020ED598
	.byte 2
	.word UNK_020ED594
	.byte 2

	.text

	thumb_func_start FUN_020139D8
FUN_020139D8: ; 0x020139D8
	push {r3-r7, lr}
	mov r1, #0x30
	add r6, r0, #0x0
	bl AllocFromHeap
	ldr r4, _02013A0C ; =UNK_020ED5C0
	str r0, [sp, #0x0]
	mov r7, #0x0
	add r5, r0, #0x0
_020139EA:
	ldr r0, [sp, #0x0]
	mov r1, #0x1a
	str r6, [r0, #0x0]
	ldrh r2, [r4, #0x0]
	mov r0, #0x1
	add r3, r6, #0x0
	bl NewMsgDataFromNarc
	str r0, [r5, #0x4]
	add r7, r7, #0x1
	add r4, r4, #0x2
	add r5, r5, #0x4
	cmp r7, #0xb
	blt _020139EA
	ldr r0, [sp, #0x0]
	pop {r3-r7, pc}
	nop
_02013A0C: .word UNK_020ED5C0

	thumb_func_start FUN_02013A10
FUN_02013A10: ; 0x02013A10
	push {r4-r6, lr}
	add r6, r0, #0x0
	mov r4, #0x0
	add r5, r6, #0x0
_02013A18:
	ldr r0, [r5, #0x4]
	bl DestroyMsgData
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0xb
	blt _02013A18
	add r0, r6, #0x0
	bl FreeToHeap
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02013A30
FUN_02013A30: ; 0x02013A30
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r2, #0x0
	add r0, r1, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x0
	bl FUN_02013AEC
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x0]
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x4]
	add r2, r4, #0x0
	bl ReadMsgDataIntoString
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02013A58
FUN_02013A58: ; 0x02013A58
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	ldr r1, _02013A94 ; =0x0000FFFF
	cmp r0, r1
	beq _02013A88
	add r1, sp, #0x8
	add r2, sp, #0x4
	bl FUN_02013AEC
	ldr r0, [sp, #0x8]
	mov r3, #0x0
	lsl r1, r0, #0x1
	ldr r0, _02013A98 ; =UNK_020ED5C0
	ldrh r0, [r0, r1]
	str r0, [sp, #0x8]
	str r4, [sp, #0x0]
	ldr r1, [sp, #0x8]
	ldr r2, [sp, #0x4]
	mov r0, #0x1a
	bl ReadMsgData_NewNarc_ExistingString
	add sp, #0xc
	pop {r3-r4, pc}
_02013A88:
	add r0, r4, #0x0
	bl StringSetEmpty
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_02013A94: .word 0x0000FFFF
_02013A98: .word UNK_020ED5C0

	thumb_func_start FUN_02013A9C
FUN_02013A9C: ; 0x02013A9C
	push {r4-r5}
	ldr r4, _02013AE0 ; =UNK_020ED5C0
	mov r2, #0x0
_02013AA2:
	ldrh r3, [r4, #0x0]
	cmp r0, r3
	bne _02013AD0
	mov r4, #0x0
	add r3, r4, #0x0
	cmp r2, #0x0
	bls _02013AC6
	ldr r0, _02013AE4 ; =UNK_020ED5D6
_02013AB2:
	lsl r5, r4, #0x1
	ldrh r5, [r0, r5]
	add r4, r4, #0x1
	lsl r4, r4, #0x10
	add r3, r3, r5
	lsl r3, r3, #0x10
	lsr r4, r4, #0x10
	lsr r3, r3, #0x10
	cmp r4, r2
	blo _02013AB2
_02013AC6:
	add r0, r3, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r4-r5}
	bx lr
_02013AD0:
	add r2, r2, #0x1
	add r4, r4, #0x2
	cmp r2, #0xb
	blo _02013AA2
	ldr r0, _02013AE8 ; =0x0000FFFF
	pop {r4-r5}
	bx lr
	nop
_02013AE0: .word UNK_020ED5C0
_02013AE4: .word UNK_020ED5D6
_02013AE8: .word 0x0000FFFF

	thumb_func_start FUN_02013AEC
FUN_02013AEC: ; 0x02013AEC
	push {r3-r6}
	ldr r3, _02013B20 ; =0x00000FFF
	ldr r6, _02013B24 ; =UNK_020ED5D6
	and r3, r0
	mov r0, #0x0
	add r5, r0, #0x0
_02013AF8:
	ldrh r4, [r6, #0x0]
	add r0, r0, r4
	cmp r3, r0
	bhs _02013B12
	str r5, [r1, #0x0]
	ldr r1, _02013B24 ; =UNK_020ED5D6
	lsl r4, r5, #0x1
	ldrh r1, [r1, r4]
	sub r0, r0, r1
	sub r0, r3, r0
	str r0, [r2, #0x0]
	pop {r3-r6}
	bx lr
_02013B12:
	add r5, r5, #0x1
	add r6, r6, #0x2
	cmp r5, #0xb
	blo _02013AF8
	pop {r3-r6}
	bx lr
	nop
_02013B20: .word 0x00000FFF
_02013B24: .word UNK_020ED5D6

	thumb_func_start FUN_02013B28
FUN_02013B28: ; 0x02013B28
	mov r0, #0x8
	bx lr

	thumb_func_start FUN_02013B2C
FUN_02013B2C: ; 0x02013B2C
	push {r3, lr}
	mov r2, #0x0
	str r2, [r0, #0x0]
	ldr r3, _02013B54 ; =UNK_020ED5B4
	str r2, [r0, #0x4]
_02013B36:
	ldrb r1, [r3, #0x0]
	cmp r1, #0x2
	bne _02013B48
	ldr r1, _02013B58 ; =UNK_020ED5B5
	lsl r2, r2, #0x1
	ldrb r1, [r1, r2]
	bl FUN_02013C18
	pop {r3, pc}
_02013B48:
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, #0x6
	blo _02013B36
	pop {r3, pc}
	nop
_02013B54: .word UNK_020ED5B4
_02013B58: .word UNK_020ED5B5

	thumb_func_start FUN_02013B5C
FUN_02013B5C: ; 0x02013B5C
	ldr r3, _02013B64 ; =FUN_02022610
	mov r1, #0x22
	bx r3
	nop
_02013B64: .word FUN_02022610

	thumb_func_start FUN_02013B68
FUN_02013B68: ; 0x02013B68
	ldr r0, [r0, #0x4]
	add r2, r0, #0x0
	lsr r2, r1
	mov r0, #0x1
	and r0, r2
	bx lr

	thumb_func_start FUN_02013B74
FUN_02013B74: ; 0x02013B74
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r2, #0x0
	ldr r3, [r5, #0x4]
	add r4, r2, #0x0
	mov r0, #0x1
_02013B80:
	add r1, r3, #0x0
	lsr r1, r2
	tst r1, r0
	bne _02013B8A
	add r4, r4, #0x1
_02013B8A:
	add r2, r2, #0x1
	cmp r2, #0x20
	blo _02013B80
	cmp r4, #0x0
	beq _02013BC4
	bl LCRandom
	add r1, r4, #0x0
	bl _u32_div_f
	ldr r4, [r5, #0x4]
	mov r0, #0x0
	mov r2, #0x1
_02013BA4:
	add r3, r4, #0x0
	lsr r3, r0
	tst r3, r2
	bne _02013BBE
	cmp r1, #0x0
	bne _02013BBC
	mov r1, #0x1
	ldr r2, [r5, #0x4]
	lsl r1, r0
	orr r1, r2
	str r1, [r5, #0x4]
	pop {r3-r5, pc}
_02013BBC:
	sub r1, r1, #0x1
_02013BBE:
	add r0, r0, #0x1
	cmp r0, #0x20
	blo _02013BA4
_02013BC4:
	mov r0, #0x20
	pop {r3-r5, pc}

	thumb_func_start FUN_02013BC8
FUN_02013BC8: ; 0x02013BC8
	ldr r3, [r0, #0x4]
	mov r2, #0x0
	mov r0, #0x1
_02013BCE:
	add r1, r3, #0x0
	lsr r1, r2
	tst r1, r0
	bne _02013BDA
	mov r0, #0x0
	bx lr
_02013BDA:
	add r2, r2, #0x1
	cmp r2, #0x20
	blo _02013BCE
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_02013BE4
FUN_02013BE4: ; 0x02013BE4
	push {r3-r4}
	mov r3, #0x0
	ldr r4, _02013C08 ; =UNK_020ED5D6
	add r2, r3, #0x0
_02013BEC:
	ldrh r1, [r4, #0x0]
	add r2, r2, #0x1
	add r4, r4, #0x2
	add r1, r3, r1
	lsl r1, r1, #0x10
	lsr r3, r1, #0x10
	cmp r2, #0x9
	blt _02013BEC
	add r0, r3, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r3-r4}
	bx lr
	nop
_02013C08: .word UNK_020ED5D6

	thumb_func_start FUN_02013C0C
FUN_02013C0C: ; 0x02013C0C
	ldr r0, [r0, #0x0]
	add r2, r0, #0x0
	lsr r2, r1
	mov r0, #0x1
	and r0, r2
	bx lr

	thumb_func_start FUN_02013C18
FUN_02013C18: ; 0x02013C18
	mov r2, #0x1
	ldr r3, [r0, #0x0]
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02013C28
FUN_02013C28: ; 0x02013C28
	push {r4-r7}
	mov r3, #0x0
	ldr r5, _02013C64 ; =UNK_020ED5EC
	add r2, r3, #0x0
_02013C30:
	ldr r7, [r5, #0x4]
	add r4, r2, #0x0
	cmp r7, #0x0
	ble _02013C54
	ldr r6, [r5, #0x0]
_02013C3A:
	ldrh r1, [r6, #0x0]
	cmp r0, r1
	bne _02013C4C
	ldr r0, _02013C68 ; =UNK_020ED5EC + 4
	lsl r1, r3, #0x3
	ldr r0, [r0, r1]
	sub r0, r0, #0x1
	pop {r4-r7}
	bx lr
_02013C4C:
	add r4, r4, #0x1
	add r6, r6, #0x2
	cmp r4, r7
	blt _02013C3A
_02013C54:
	add r3, r3, #0x1
	add r5, #0x8
	cmp r3, #0xc
	blo _02013C30
	mov r0, #0x0
	pop {r4-r7}
	bx lr
	nop
_02013C64: .word UNK_020ED5EC
_02013C68: .word UNK_020ED5EC + 4

	thumb_func_start FUN_02013C6C
FUN_02013C6C: ; 0x02013C6C
	push {r3-r7, lr}
	ldr r3, _02013CC8 ; =UNK_020ED5EC
	add r6, r1, #0x0
	mov r7, #0x0
_02013C74:
	ldr r5, [r3, #0x4]
	mov r2, #0x0
	cmp r5, #0x0
	ble _02013CBC
	ldr r4, [r3, #0x0]
_02013C7E:
	ldrh r1, [r4, #0x0]
	cmp r0, r1
	bne _02013CB4
	ldr r2, _02013CCC ; =UNK_020ED5EC + 4
	lsl r1, r7, #0x3
	ldr r2, [r2, r1]
	mov r0, #0x0
	cmp r2, #0x0
	beq _02013CAC
	ldr r2, _02013CC8 ; =UNK_020ED5EC
	add r2, r2, r1
	ldr r2, [r2, #0x4]
_02013C96:
	cmp r6, #0x0
	bne _02013CA4
	ldr r2, _02013CC8 ; =UNK_020ED5EC
	lsl r0, r0, #0x1
	ldr r1, [r2, r1]
	ldrh r0, [r1, r0]
	pop {r3-r7, pc}
_02013CA4:
	sub r6, r6, #0x1
	add r0, r0, #0x1
	cmp r2, #0x0
	bne _02013C96
_02013CAC:
	bl ErrorHandling
	ldr r0, _02013CD0 ; =0x0000FFFF
	pop {r3-r7, pc}
_02013CB4:
	add r2, r2, #0x1
	add r4, r4, #0x2
	cmp r2, r5
	blt _02013C7E
_02013CBC:
	add r7, r7, #0x1
	add r3, #0x8
	cmp r7, #0xc
	blo _02013C74
	pop {r3-r7, pc}
	nop
_02013CC8: .word UNK_020ED5EC
_02013CCC: .word UNK_020ED5EC + 4
_02013CD0: .word 0x0000FFFF
