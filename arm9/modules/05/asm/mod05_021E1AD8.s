	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021E1AD8
MOD05_021E1AD8: ; 0x021E1AD8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	ldr r1, [sp, #0x2c]
	add r4, r0, #0
	add r5, r2, #0
	add r7, r3, #0
	cmp r1, #0
	bne _021E1B06
	ldr r2, _021E1BF0 ; =0x00000141
	mov r0, #1
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	add r1, r6, #0
	add r1, #0x8c
	str r0, [r1]
	add r0, r6, #0
	add r0, #0x97
	ldrb r1, [r0]
	mov r0, #2
	orr r1, r0
	b _021E1B16
_021E1B06:
	add r0, r6, #0
	add r0, #0x8c
	str r1, [r0]
	add r0, r6, #0
	add r0, #0x97
	ldrb r1, [r0]
	mov r0, #2
	bic r1, r0
_021E1B16:
	add r0, r6, #0
	add r0, #0x97
	strb r1, [r0]
	add r0, r6, #0
	ldr r1, [sp, #0x24]
	add r0, #0x90
	str r1, [r0]
	add r0, r6, #0
	ldr r1, [sp, #0x20]
	str r4, [r6]
	add r0, #0xa0
	str r1, [r0]
	add r0, r6, #0
	add r0, #0x97
	add r2, sp, #8
	ldrb r0, [r0]
	mov r1, #1
	ldrb r3, [r2, #0x14]
	bic r0, r1
	mov r1, #1
	and r1, r3
	orr r1, r0
	add r0, r6, #0
	add r0, #0x97
	strb r1, [r0]
	add r1, r6, #0
	ldrb r0, [r2, #0x10]
	add r1, #0x96
	mov r3, #3
	strb r0, [r1]
	add r1, r6, #0
	add r1, #0x97
	ldrb r2, [r1]
	mov r1, #0x40
	bic r2, r1
	add r1, r6, #0
	add r1, #0x97
	strb r2, [r1]
	add r1, r6, #0
	add r1, #0x97
	ldrb r2, [r1]
	mov r1, #0x80
	bic r2, r1
	add r1, r6, #0
	add r1, #0x97
	strb r2, [r1]
	add r1, r6, #0
	add r1, #0x98
	strb r5, [r1]
	add r1, r6, #0
	add r1, #0x99
	add r2, r6, #0
	strb r7, [r1]
	mov r1, #0
	add r2, #0x9b
	strb r1, [r2]
	ldr r2, [sp, #0x28]
	str r2, [r6, #0x18]
	add r2, r6, #0
	add r2, #0x94
	strb r3, [r2]
	mov r2, #0xb5
	lsl r2, r2, #2
	strh r0, [r6, r2]
	add r2, r6, #0
	add r3, r1, #0
_021E1B9A:
	add r0, r2, #0
	add r0, #0xb4
	str r3, [r0]
	add r0, r2, #0
	add r0, #0xb8
	add r1, r1, #1
	add r2, #8
	str r3, [r0]
	cmp r1, #0x1c
	blt _021E1B9A
	mov r7, #0xa7
	add r1, r6, #0
	add r2, r6, #0
	mov r5, #0
	mov r0, #0xff
	lsl r7, r7, #2
_021E1BBA:
	mov r4, #0x6f
	lsl r4, r4, #2
	str r5, [r1, r4]
	add r4, r4, #4
	str r5, [r1, r4]
	strh r0, [r2, r7]
	add r3, r3, #1
	add r1, #8
	add r2, r2, #2
	cmp r3, #0x1c
	blt _021E1BBA
	add r4, r6, #0
	mov r7, #0x50
_021E1BD4:
	add r0, r7, #0
	mov r1, #4
	bl String_ctor
	str r0, [r4, #0x1c]
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #0x1c
	blt _021E1BD4
	add r6, #0xa0
	ldr r1, _021E1BF4 ; =0x0000EEEE
	ldr r0, [r6]
	strh r1, [r0]
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E1BF0: .word 0x00000141
_021E1BF4: .word 0x0000EEEE

	thumb_func_start MOD05_021E1BF8
MOD05_021E1BF8: ; 0x021E1BF8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r7, r1, #0
	mov r1, #0xb6
	add r6, r0, #0
	mov r0, #4
	lsl r1, r1, #2
	str r2, [sp, #0x18]
	add r5, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	bne _021E1C18
	add sp, #0x1c
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021E1C18:
	mov r2, #0xb6
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	str r5, [sp]
	add r0, sp, #0x20
	ldrb r0, [r0, #0x10]
	add r1, r4, #0
	add r2, r7, #0
	str r0, [sp, #4]
	ldr r0, [sp, #0x34]
	str r0, [sp, #8]
	ldr r0, [sp, #0x38]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x3c]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x40]
	str r0, [sp, #0x14]
	ldr r3, [sp, #0x18]
	add r0, r6, #0
	bl MOD05_021E1AD8
	add r0, r4, #0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021E1C4C
MOD05_021E1C4C: ; 0x021E1C4C
	ldr r3, _021E1C50 ; =MOD05_021E1D38
	bx r3
	.balign 4, 0
_021E1C50: .word MOD05_021E1D38

	thumb_func_start MOD05_021E1C54
MOD05_021E1C54: ; 0x021E1C54
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	bl MOD05_021E1DA8
	mov r1, #7
	tst r1, r0
	bne _021E1C68
	lsr r0, r0, #3
	b _021E1C6C
_021E1C68:
	lsr r0, r0, #3
	add r0, r0, #1
_021E1C6C:
	add r1, r4, #0
	add r1, #0x97
	ldrb r1, [r1]
	lsl r1, r1, #0x19
	lsr r1, r1, #0x1f
	beq _021E1C86
	add r1, r4, #0
	add r1, #0x98
	ldrb r1, [r1]
	sub r2, r1, r0
	add r1, r4, #0
	add r1, #0x98
	strb r2, [r1]
_021E1C86:
	add r1, r4, #0
	add r1, #0x97
	ldrb r1, [r1]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1f
	beq _021E1CA8
	add r1, r4, #0
	add r1, #0x99
	ldrb r2, [r1]
	add r1, r4, #0
	add r1, #0x9b
	ldrb r1, [r1]
	lsl r1, r1, #1
	sub r2, r2, r1
	add r1, r4, #0
	add r1, #0x99
	strb r2, [r1]
_021E1CA8:
	add r1, r4, #0
	add r1, #0x99
	ldrb r1, [r1]
	lsl r0, r0, #0x18
	add r3, r4, #0
	str r1, [sp]
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x9b
	ldrb r0, [r0]
	add r1, r4, #0
	add r3, #0x98
	lsl r0, r0, #0x19
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x3d
	str r0, [sp, #0x10]
	ldr r0, [r4]
	ldrb r3, [r3]
	ldr r0, [r0, #8]
	add r1, #8
	mov r2, #3
	bl AddWindowParameterized
	mov r0, #0
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r4]
	ldr r2, _021E1D30 ; =0x000003D9
	ldr r0, [r0, #8]
	mov r1, #3
	mov r3, #0xb
	bl FUN_0200CB00
	add r0, r4, #0
	ldr r2, _021E1D30 ; =0x000003D9
	add r0, #8
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	add r0, r4, #0
	bl MOD05_021E1DE4
	add r1, r4, #0
	add r1, #0x96
	add r0, r4, #0
	ldrb r1, [r1]
	add r0, #0xa4
	mov r2, #4
	bl FUN_02001C34
	add r1, r4, #0
	add r1, #0xb0
	str r0, [r1]
	ldr r0, _021E1D34 ; =MOD05_021E1E58
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
	str r0, [r4, #4]
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_021E1D30: .word 0x000003D9
_021E1D34: .word MOD05_021E1E58

	thumb_func_start MOD05_021E1D38
MOD05_021E1D38: ; 0x021E1D38
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	mov r0, #0x50
	mov r1, #4
	add r6, r2, #0
	bl String_ctor
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	add r1, r7, #0
	add r2, r4, #0
	bl ReadMsgDataIntoString
	add r1, r5, #0
	add r1, #0x9b
	ldrb r1, [r1]
	add r0, r5, #0
	add r0, #0x90
	lsl r1, r1, #2
	add r1, r5, r1
	ldr r0, [r0]
	ldr r1, [r1, #0x1c]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r5, #0
	add r0, #0x9b
	ldrb r2, [r0]
	lsl r0, r2, #2
	add r0, r5, r0
	ldr r1, [r0, #0x1c]
	lsl r0, r2, #3
	add r0, r5, r0
	add r0, #0xb4
	str r1, [r0]
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	add r0, #0x9b
	ldrb r0, [r0]
	lsl r0, r0, #3
	add r0, r5, r0
	add r0, #0xb8
	str r6, [r0]
	add r0, r5, #0
	add r0, #0x9b
	ldrb r0, [r0]
	add r5, #0x9b
	add r0, r0, #1
	strb r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E1DA8
MOD05_021E1DA8: ; 0x021E1DA8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r0, #0x9b
	ldrb r0, [r0]
	mov r6, #0
	add r4, r6, #0
	cmp r0, #0
	ble _021E1DDE
	add r5, r7, #0
_021E1DBA:
	add r0, r5, #0
	add r0, #0xb4
	ldr r1, [r0]
	cmp r1, #0
	beq _021E1DDE
	mov r0, #0
	bl FUN_02002F9C
	cmp r6, r0
	bhs _021E1DD0
	add r6, r0, #0
_021E1DD0:
	add r0, r7, #0
	add r0, #0x9b
	ldrb r0, [r0]
	add r4, r4, #1
	add r5, #8
	cmp r4, r0
	blt _021E1DBA
_021E1DDE:
	add r6, #0xc
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021E1DE4
MOD05_021E1DE4: ; 0x021E1DE4
	add r2, r0, #0
	add r1, r0, #0
	add r2, #0xb4
	add r1, #0xa4
	str r2, [r1]
	add r2, r0, #0
	add r1, r0, #0
	add r2, #8
	add r1, #0xa8
	str r2, [r1]
	add r1, r0, #0
	mov r2, #0
	add r1, #0xac
	strb r2, [r1]
	add r1, r0, #0
	mov r2, #1
	add r1, #0xad
	strb r2, [r1]
	add r1, r0, #0
	add r1, #0x9b
	ldrb r2, [r1]
	add r1, r0, #0
	add r1, #0xae
	strb r2, [r1]
	add r2, r0, #0
	add r2, #0xaf
	ldrb r3, [r2]
	mov r2, #0xf
	add r1, r0, #0
	bic r3, r2
	add r2, r0, #0
	add r2, #0xaf
	strb r3, [r2]
	add r2, r0, #0
	add r2, #0xaf
	ldrb r3, [r2]
	mov r2, #0x30
	add r1, #0xaf
	bic r3, r2
	add r2, r0, #0
	add r2, #0xaf
	strb r3, [r2]
	add r0, #0x9b
	ldrb r0, [r0]
	ldrb r2, [r1]
	cmp r0, #4
	blo _021E1E4E
	mov r0, #0xc0
	bic r2, r0
	mov r0, #0x40
	orr r0, r2
	strb r0, [r1]
	bx lr
_021E1E4E:
	mov r0, #0xc0
	bic r2, r0
	strb r2, [r1]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021E1E58
MOD05_021E1E58: ; 0x021E1E58
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	add r0, #0x94
	ldrb r0, [r0]
	cmp r0, #0
	beq _021E1E74
	add r0, r4, #0
	add r0, #0x94
	ldrb r0, [r0]
	add r4, #0x94
	sub r0, r0, #1
	strb r0, [r4]
	pop {r4, pc}
_021E1E74:
	bl FUN_0200E308
	cmp r0, #0
	beq _021E1EC4
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	bl FUN_02001C78
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _021E1E96
	add r1, r1, #1
	cmp r0, r1
	beq _021E1EC4
	b _021E1EB6
_021E1E96:
	add r0, r4, #0
	add r0, #0x97
	ldrb r0, [r0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _021E1EC4
	add r0, r4, #0
	add r0, #0xa0
	ldr r1, _021E1EC8 ; =0x0000FFFE
	ldr r0, [r0]
	strh r1, [r0]
	add r0, r4, #0
	bl MOD05_021E1ECC
	pop {r4, pc}
_021E1EB6:
	add r1, r4, #0
	add r1, #0xa0
	ldr r1, [r1]
	strh r0, [r1]
	add r0, r4, #0
	bl MOD05_021E1ECC
_021E1EC4:
	pop {r4, pc}
	nop
_021E1EC8: .word 0x0000FFFE

	thumb_func_start MOD05_021E1ECC
MOD05_021E1ECC: ; 0x021E1ECC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, _021E1F30 ; =0x000005DC
	bl FUN_020054C8
	add r0, r6, #0
	add r0, #0xb0
	ldr r0, [r0]
	mov r1, #0
	bl FUN_02001C5C
	add r0, r6, #0
	add r0, #0xa8
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0200CCF8
	add r0, r6, #0
	add r0, #0xa8
	ldr r0, [r0]
	bl RemoveWindow
	mov r4, #0
	add r5, r6, #0
_021E1EFC:
	ldr r0, [r5, #0x1c]
	bl String_dtor
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x1c
	blt _021E1EFC
	add r0, r6, #0
	add r0, #0x97
	ldrb r0, [r0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _021E1F22
	add r0, r6, #0
	add r0, #0x8c
	ldr r0, [r0]
	bl DestroyMsgData
_021E1F22:
	ldr r0, [r6, #4]
	bl FUN_0200CAB4
	add r0, r6, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021E1F30: .word 0x000005DC

	thumb_func_start MOD05_021E1F34
MOD05_021E1F34: ; 0x021E1F34
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, sp, #0x10
	ldrb r4, [r4, #0x10]
	str r4, [sp]
	ldr r4, [sp, #0x24]
	str r4, [sp, #4]
	ldr r4, [sp, #0x28]
	str r4, [sp, #8]
	ldr r4, [sp, #0x2c]
	str r4, [sp, #0xc]
	ldr r4, [sp, #0x30]
	str r4, [sp, #0x10]
	bl MOD05_021E1BF8
	add sp, #0x14
	pop {r3, r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E1F58
MOD05_021E1F58: ; 0x021E1F58
	push {r3, lr}
	bl MOD05_021E2094
	pop {r3, pc}

	thumb_func_start MOD05_021E1F60
MOD05_021E1F60: ; 0x021E1F60
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	bl MOD05_021E2134
	mov r1, #7
	tst r1, r0
	bne _021E1F74
	lsr r0, r0, #3
	b _021E1F78
_021E1F74:
	lsr r0, r0, #3
	add r0, r0, #1
_021E1F78:
	add r1, r4, #0
	add r1, #0x97
	ldrb r1, [r1]
	lsl r1, r1, #0x19
	lsr r1, r1, #0x1f
	beq _021E1F92
	add r1, r4, #0
	add r1, #0x98
	ldrb r1, [r1]
	sub r2, r1, r0
	add r1, r4, #0
	add r1, #0x98
	strb r2, [r1]
_021E1F92:
	add r1, r4, #0
	add r1, #0x97
	ldrb r1, [r1]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1f
	beq _021E1FC8
	add r1, r4, #0
	add r1, #0x9b
	ldrb r3, [r1]
	cmp r3, #8
	bls _021E1FB8
	add r1, r4, #0
	add r1, #0x99
	ldrb r2, [r1]
	add r1, r4, #0
	add r1, #0x99
	sub r2, #0x10
	strb r2, [r1]
	b _021E1FC8
_021E1FB8:
	add r1, r4, #0
	add r1, #0x99
	ldrb r2, [r1]
	lsl r1, r3, #1
	sub r2, r2, r1
	add r1, r4, #0
	add r1, #0x99
	strb r2, [r1]
_021E1FC8:
	add r1, r4, #0
	add r1, #0x9b
	ldrb r2, [r1]
	cmp r2, #8
	bls _021E2002
	add r1, r4, #0
	add r1, #0x99
	ldrb r1, [r1]
	lsl r0, r0, #0x18
	add r3, r4, #0
	str r1, [sp]
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	mov r0, #0x10
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x3d
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r3, #0x98
	add r1, r4, #0
	ldrb r3, [r3]
	ldr r0, [r0, #8]
	add r1, #8
	mov r2, #3
	bl AddWindowParameterized
	b _021E2032
_021E2002:
	add r1, r4, #0
	add r1, #0x99
	ldrb r1, [r1]
	lsl r0, r0, #0x18
	add r3, r4, #0
	str r1, [sp]
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	lsl r0, r2, #0x19
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x3d
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r3, #0x98
	add r1, r4, #0
	ldrb r3, [r3]
	ldr r0, [r0, #8]
	add r1, #8
	mov r2, #3
	bl AddWindowParameterized
_021E2032:
	mov r0, #0
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r4]
	ldr r2, _021E208C ; =0x000003D9
	ldr r0, [r0, #8]
	mov r1, #3
	mov r3, #0xb
	bl FUN_0200CB00
	add r0, r4, #0
	ldr r2, _021E208C ; =0x000003D9
	add r0, #8
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	add r0, r4, #0
	bl MOD05_021E2170
	add r2, r4, #0
	add r2, #0x96
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r2, [r2]
	add r0, r4, r0
	mov r1, #0
	mov r3, #4
	bl ListMenuInit
	mov r1, #0x6d
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD05_021E2434
	ldr r0, _021E2090 ; =MOD05_021E229C
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
	str r0, [r4, #4]
	add sp, #0x14
	pop {r3, r4, pc}
	.balign 4, 0
_021E208C: .word 0x000003D9
_021E2090: .word MOD05_021E229C

	thumb_func_start MOD05_021E2094
MOD05_021E2094: ; 0x021E2094
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	str r1, [sp]
	mov r0, #0x50
	mov r1, #4
	add r7, r2, #0
	add r4, r3, #0
	bl String_ctor
	add r6, r0, #0
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	ldr r1, [sp]
	add r2, r6, #0
	bl ReadMsgDataIntoString
	add r1, r5, #0
	add r1, #0x9b
	ldrb r1, [r1]
	add r0, r5, #0
	add r0, #0x90
	lsl r1, r1, #2
	add r1, r5, r1
	ldr r0, [r0]
	ldr r1, [r1, #0x1c]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r5, #0
	add r0, #0x9b
	ldrb r1, [r0]
	lsl r0, r1, #2
	add r0, r5, r0
	lsl r1, r1, #3
	add r2, r5, r1
	mov r1, #0x6f
	ldr r0, [r0, #0x1c]
	lsl r1, r1, #2
	str r0, [r2, r1]
	add r0, r6, #0
	bl String_dtor
	cmp r4, #0xfa
	bne _021E2104
	add r0, r5, #0
	add r0, #0x9b
	ldrb r0, [r0]
	mov r2, #2
	mvn r2, r2
	lsl r0, r0, #3
	add r1, r5, r0
	mov r0, #7
	lsl r0, r0, #6
	str r2, [r1, r0]
	b _021E2114
_021E2104:
	add r0, r5, #0
	add r0, #0x9b
	ldrb r0, [r0]
	lsl r0, r0, #3
	add r1, r5, r0
	mov r0, #7
	lsl r0, r0, #6
	str r4, [r1, r0]
_021E2114:
	add r0, r5, #0
	add r0, #0x9b
	ldrb r0, [r0]
	lsl r0, r0, #1
	add r1, r5, r0
	mov r0, #0xa7
	lsl r0, r0, #2
	strh r7, [r1, r0]
	add r0, r5, #0
	add r0, #0x9b
	ldrb r0, [r0]
	add r5, #0x9b
	add r0, r0, #1
	strb r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E2134
MOD05_021E2134: ; 0x021E2134
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r0, #0x9b
	ldrb r0, [r0]
	mov r6, #0
	add r4, r6, #0
	cmp r0, #0
	ble _021E216A
	add r5, r7, #0
_021E2146:
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	cmp r1, #0
	beq _021E216A
	mov r0, #0
	bl FUN_02002F9C
	cmp r6, r0
	bhs _021E215C
	add r6, r0, #0
_021E215C:
	add r0, r7, #0
	add r0, #0x9b
	ldrb r0, [r0]
	add r4, r4, #1
	add r5, #8
	cmp r4, r0
	blt _021E2146
_021E216A:
	add r6, #0xc
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021E2170
MOD05_021E2170: ; 0x021E2170
	push {r4, r5}
	mov r3, #0x6f
	lsl r3, r3, #2
	add r1, r3, #0
	add r2, r0, r3
	sub r1, #0x28
	str r2, [r0, r1]
	add r1, r3, #0
	mov r2, #0
	sub r1, #0x24
	str r2, [r0, r1]
	add r1, r3, #0
	ldr r2, _021E2268 ; =MOD05_021E2278
	sub r1, #0x20
	str r2, [r0, r1]
	add r2, r0, #0
	add r1, r3, #0
	add r2, #8
	sub r1, #0x1c
	str r2, [r0, r1]
	add r1, r0, #0
	add r1, #0x9b
	ldrb r2, [r1]
	add r1, r3, #0
	sub r1, #0x18
	strh r2, [r0, r1]
	add r1, r3, #0
	mov r2, #8
	sub r1, #0x16
	strh r2, [r0, r1]
	add r1, r3, #0
	mov r2, #1
	sub r1, #0x14
	strb r2, [r0, r1]
	add r1, r3, #0
	mov r4, #0xc
	sub r1, #0x13
	strb r4, [r0, r1]
	add r1, r3, #0
	mov r4, #2
	sub r1, #0x12
	strb r4, [r0, r1]
	add r1, r3, #0
	sub r1, #0x11
	ldrb r4, [r0, r1]
	mov r1, #0xf
	bic r4, r1
	orr r4, r2
	add r2, r3, #0
	sub r2, #0x11
	strb r4, [r0, r2]
	add r2, r3, #0
	sub r2, #0x11
	ldrb r5, [r0, r2]
	mov r2, #0xf0
	mov r4, #0x10
	bic r5, r2
	orr r5, r4
	add r4, r3, #0
	sub r4, #0x11
	strb r5, [r0, r4]
	add r4, r3, #0
	sub r4, #0x10
	ldrb r4, [r0, r4]
	bic r4, r1
	mov r1, #0xf
	orr r4, r1
	add r1, r3, #0
	sub r1, #0x10
	strb r4, [r0, r1]
	add r1, r3, #0
	sub r1, #0x10
	ldrb r4, [r0, r1]
	mov r1, #0x20
	bic r4, r2
	add r2, r4, #0
	orr r2, r1
	add r1, r3, #0
	sub r1, #0x10
	strb r2, [r0, r1]
	add r1, r3, #0
	sub r1, #0xe
	ldrh r2, [r0, r1]
	mov r1, #7
	bic r2, r1
	add r1, r3, #0
	sub r1, #0xe
	strh r2, [r0, r1]
	add r1, r3, #0
	sub r1, #0xe
	ldrh r2, [r0, r1]
	mov r1, #0x78
	bic r2, r1
	add r1, r3, #0
	sub r1, #0xe
	strh r2, [r0, r1]
	add r1, r3, #0
	sub r1, #0xe
	ldrh r2, [r0, r1]
	ldr r1, _021E226C ; =0xFFFFFE7F
	and r2, r1
	mov r1, #0x80
	orr r2, r1
	add r1, r3, #0
	sub r1, #0xe
	strh r2, [r0, r1]
	add r1, r3, #0
	sub r1, #0xe
	ldrh r2, [r0, r1]
	ldr r1, _021E2270 ; =0xFFFF81FF
	and r2, r1
	add r1, r3, #0
	sub r1, #0xe
	strh r2, [r0, r1]
	add r1, r3, #0
	sub r1, #0xe
	ldrh r2, [r0, r1]
	ldr r1, _021E2274 ; =0xFFFF7FFF
	sub r3, #0xe
	and r1, r2
	strh r1, [r0, r3]
	pop {r4, r5}
	bx lr
	nop
_021E2268: .word MOD05_021E2278
_021E226C: .word 0xFFFFFE7F
_021E2270: .word 0xFFFF81FF
_021E2274: .word 0xFFFF7FFF

	thumb_func_start MOD05_021E2278
MOD05_021E2278: ; 0x021E2278
	push {r3, lr}
	mov r2, #2
	mvn r2, r2
	cmp r1, r2
	bne _021E228E
	mov r1, #3
	mov r2, #0xf
	mov r3, #4
	bl ListMenuOverrideSetColors
	pop {r3, pc}
_021E228E:
	mov r1, #1
	mov r2, #0xf
	mov r3, #2
	bl ListMenuOverrideSetColors
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E229C
MOD05_021E229C: ; 0x021E229C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r0, r5, #0
	add r0, #0x94
	ldrb r0, [r0]
	cmp r0, #0
	beq _021E22B8
	add r0, r5, #0
	add r0, #0x94
	ldrb r0, [r0]
	add r5, #0x94
	sub r0, r0, #1
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_021E22B8:
	bl FUN_0200E308
	cmp r0, #0
	beq _021E235A
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	mov r0, #0x6d
	mov r1, #0xb5
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldrh r6, [r5, r1]
	ldr r0, [r5, r0]
	add r1, r5, r1
	bl ListMenuGetCurrentItemArrayId
	mov r0, #0xb5
	lsl r0, r0, #2
	ldrh r0, [r5, r0]
	cmp r6, r0
	beq _021E22EE
	ldr r0, _021E235C ; =0x000005DC
	bl FUN_020054C8
_021E22EE:
	ldr r0, _021E2360 ; =gMain
	mov r1, #0x40
	ldr r0, [r0, #0x4c]
	tst r1, r0
	bne _021E230A
	mov r1, #0x80
	tst r1, r0
	bne _021E230A
	mov r1, #0x20
	tst r1, r0
	bne _021E230A
	mov r1, #0x10
	tst r0, r1
	beq _021E2310
_021E230A:
	add r0, r5, #0
	bl MOD05_021E2434
_021E2310:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _021E2320
	add r0, r0, #1
	cmp r4, r0
	beq _021E235A
	b _021E2346
_021E2320:
	add r0, r5, #0
	add r0, #0x97
	ldrb r0, [r0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _021E235A
	ldr r0, _021E235C ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	add r0, #0xa0
	ldr r1, _021E2364 ; =0x0000FFFE
	ldr r0, [r0]
	strh r1, [r0]
	add r0, r5, #0
	bl MOD05_021E2368
	pop {r4, r5, r6, pc}
_021E2346:
	ldr r0, _021E235C ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	strh r4, [r0]
	add r0, r5, #0
	bl MOD05_021E2368
_021E235A:
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021E235C: .word 0x000005DC
_021E2360: .word gMain
_021E2364: .word 0x0000FFFE

	thumb_func_start MOD05_021E2368
MOD05_021E2368: ; 0x021E2368
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, _021E23CC ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x6d
	lsl r0, r0, #2
	mov r1, #0
	ldr r0, [r6, r0]
	add r2, r1, #0
	bl DestroyListMenu
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	mov r1, #0
	bl FUN_0200CCF8
	add r0, r6, #0
	add r0, #8
	bl RemoveWindow
	mov r4, #0
	add r5, r6, #0
_021E2398:
	ldr r0, [r5, #0x1c]
	bl String_dtor
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x1c
	blt _021E2398
	add r0, r6, #0
	add r0, #0x97
	ldrb r0, [r0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _021E23BE
	add r0, r6, #0
	add r0, #0x8c
	ldr r0, [r0]
	bl DestroyMsgData
_021E23BE:
	ldr r0, [r6, #4]
	bl FUN_0200CAB4
	add r0, r6, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021E23CC: .word 0x000005DC

	thumb_func_start MOD05_021E23D0
MOD05_021E23D0: ; 0x021E23D0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	str r1, [sp, #0xc]
	mov r0, #0x50
	mov r1, #4
	add r7, r2, #0
	bl String_ctor
	add r4, r0, #0
	mov r0, #0x50
	mov r1, #4
	bl String_ctor
	add r6, r0, #0
	ldr r0, [r5, #0x18]
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	ldr r1, [sp, #0xc]
	add r2, r4, #0
	bl ReadMsgDataIntoString
	add r0, r5, #0
	add r0, #0x90
	ldr r0, [r0]
	add r1, r6, #0
	add r2, r4, #0
	bl StringExpandPlaceholders
	mov r3, #0
	str r3, [sp]
	str r7, [sp, #4]
	str r3, [sp, #8]
	ldr r0, [r5, #0x18]
	mov r1, #1
	add r2, r6, #0
	bl AddTextPrinterParameterized
	add r0, r4, #0
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021E2434
MOD05_021E2434: ; 0x021E2434
	push {r4, lr}
	mov r1, #0x6d
	add r4, r0, #0
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	add r1, r1, #6
	add r1, r4, r1
	bl ListMenuGetCurrentItemArrayId
	ldr r0, _021E2460 ; =0x000001BA
	ldrh r1, [r4, r0]
	add r0, #0xe2
	lsl r1, r1, #1
	add r1, r4, r1
	ldrh r1, [r1, r0]
	cmp r1, #0xff
	beq _021E245E
	add r0, r4, #0
	mov r2, #0
	bl MOD05_021E23D0
_021E245E:
	pop {r4, pc}
	.balign 4, 0
_021E2460: .word 0x000001BA

	thumb_func_start MOD05_021E2464
MOD05_021E2464: ; 0x021E2464
	push {r4, r5, lr}
	sub sp, #0x14
	mov r4, #0
	str r4, [sp]
	str r3, [sp, #4]
	ldr r3, [sp, #0x20]
	str r3, [sp, #8]
	str r4, [sp, #0xc]
	add r3, r4, #0
	str r4, [sp, #0x10]
	bl MOD05_021E1BF8
	add r5, r0, #0
	add r0, r4, #0
	add r1, r0, #0
	bl GetFontAttribute
	lsl r1, r0, #3
	mov r0, #7
	tst r0, r1
	bne _021E2492
	lsr r4, r1, #3
	b _021E2496
_021E2492:
	lsr r0, r1, #3
	add r4, r0, #1
_021E2496:
	add r0, r5, #0
	add r0, #0x99
	ldrb r0, [r0]
	add r3, r5, #0
	add r1, r5, #0
	str r0, [sp]
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0xdd
	str r0, [sp, #0x10]
	ldr r0, [r5]
	add r3, #0x98
	ldrb r3, [r3]
	ldr r0, [r0, #8]
	add r1, #8
	mov r2, #3
	bl AddWindowParameterized
	mov r0, #0
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r5]
	ldr r2, _021E2538 ; =0x000003D9
	ldr r0, [r0, #8]
	mov r1, #3
	mov r3, #0xb
	bl FUN_0200CB00
	add r0, r5, #0
	ldr r2, _021E2538 ; =0x000003D9
	add r0, #8
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	lsl r0, r4, #0x13
	lsr r0, r0, #0x10
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0
	add r0, #8
	mov r1, #0xf
	add r3, r2, #0
	bl FillWindowPixelRect
	mov r2, #0
	add r0, r5, #0
	mov r1, #0xf
	add r3, r2, #0
	bl MOD05_021E2540
	mov r1, #0x10
	add r0, r5, #0
	mov r2, #0x20
	add r3, r1, #0
	bl MOD05_021E2540
	add r0, r5, #0
	add r1, r5, #0
	add r0, #8
	add r1, #0xa8
	str r0, [r1]
	bl CopyWindowToVram
	ldr r0, _021E253C ; =MOD05_021E25A4
	add r1, r5, #0
	mov r2, #0
	bl FUN_0200CA44
	str r0, [r5, #4]
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_021E2538: .word 0x000003D9
_021E253C: .word MOD05_021E25A4

	thumb_func_start MOD05_021E2540
MOD05_021E2540: ; 0x021E2540
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r1, [sp, #0xc]
	add r5, r0, #0
	mov r0, #0x50
	mov r1, #4
	str r2, [sp, #0x10]
	add r7, r3, #0
	bl String_ctor
	add r4, r0, #0
	mov r0, #0x50
	mov r1, #4
	bl String_ctor
	add r6, r0, #0
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	ldr r1, [sp, #0xc]
	add r2, r4, #0
	bl ReadMsgDataIntoString
	add r0, r5, #0
	add r0, #0x90
	ldr r0, [r0]
	add r1, r6, #0
	add r2, r4, #0
	bl StringExpandPlaceholders
	str r7, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	add r5, #8
	ldr r3, [sp, #0x10]
	add r0, r5, #0
	add r2, r6, #0
	bl AddTextPrinterParameterized
	add r0, r4, #0
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E25A4
MOD05_021E25A4: ; 0x021E25A4
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r0, r6, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldrh r1, [r0]
	ldr r0, _021E2604 ; =0x0000FFFF
	cmp r1, r0
	bne _021E2602
	add r0, r6, #0
	add r0, #0xa8
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0200CCF8
	add r0, r6, #0
	add r0, #0xa8
	ldr r0, [r0]
	bl RemoveWindow
	mov r4, #0
	add r5, r6, #0
_021E25D0:
	ldr r0, [r5, #0x1c]
	bl String_dtor
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x1c
	blt _021E25D0
	add r0, r6, #0
	add r0, #0x97
	ldrb r0, [r0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _021E25F6
	add r0, r6, #0
	add r0, #0x8c
	ldr r0, [r0]
	bl DestroyMsgData
_021E25F6:
	ldr r0, [r6, #4]
	bl FUN_0200CAB4
	add r0, r6, #0
	bl FreeToHeap
_021E2602:
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021E2604: .word 0x0000FFFF

	thumb_func_start MOD05_021E2608
MOD05_021E2608: ; 0x021E2608
	cmp r0, #0x89
	bgt _021E2646
	bge _021E269E
	cmp r0, #0x68
	bgt _021E2638
	bge _021E2682
	cmp r0, #0xe
	bgt _021E2632
	add r1, r0, #0
	sub r1, #0xb
	bmi _021E26C2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E262A: ; jump table
	.short _021E26B2 - _021E262A - 2 ; case 0
	.short _021E26B6 - _021E262A - 2 ; case 1
	.short _021E26BA - _021E262A - 2 ; case 2
	.short _021E26BE - _021E262A - 2 ; case 3
_021E2632:
	cmp r0, #0x67
	beq _021E267E
	b _021E26C2
_021E2638:
	cmp r0, #0x70
	bgt _021E2640
	beq _021E268E
	b _021E26C2
_021E2640:
	cmp r0, #0x71
	beq _021E2692
	b _021E26C2
_021E2646:
	cmp r0, #0x96
	bgt _021E2668
	cmp r0, #0x8c
	blt _021E265A
	beq _021E26AA
	cmp r0, #0x8d
	beq _021E26AE
	cmp r0, #0x96
	beq _021E268A
	b _021E26C2
_021E265A:
	cmp r0, #0x8a
	bgt _021E2662
	beq _021E26A2
	b _021E26C2
_021E2662:
	cmp r0, #0x8b
	beq _021E26A6
	b _021E26C2
_021E2668:
	ldr r1, _021E26C8 ; =0x000001CD
	cmp r0, r1
	bgt _021E2676
	bge _021E2696
	cmp r0, #0xa4
	beq _021E2686
	b _021E26C2
_021E2676:
	add r1, r1, #1
	cmp r0, r1
	beq _021E269A
	b _021E26C2
_021E267E:
	mov r0, #1
	bx lr
_021E2682:
	mov r0, #0
	bx lr
_021E2686:
	mov r0, #0
	bx lr
_021E268A:
	mov r0, #1
	bx lr
_021E268E:
	mov r0, #1
	bx lr
_021E2692:
	mov r0, #0
	bx lr
_021E2696:
	mov r0, #1
	bx lr
_021E269A:
	mov r0, #0
	bx lr
_021E269E:
	mov r0, #4
	bx lr
_021E26A2:
	mov r0, #3
	bx lr
_021E26A6:
	mov r0, #2
	bx lr
_021E26AA:
	mov r0, #1
	bx lr
_021E26AE:
	mov r0, #0
	bx lr
_021E26B2:
	mov r0, #3
	bx lr
_021E26B6:
	mov r0, #2
	bx lr
_021E26BA:
	mov r0, #1
	bx lr
_021E26BE:
	mov r0, #0
	bx lr
_021E26C2:
	mov r0, #1
	bx lr
	nop
_021E26C8: .word 0x000001CD

	thumb_func_start MOD05_021E26CC
MOD05_021E26CC: ; 0x021E26CC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r6, r1, #0
	bl MOD05_021E1DA8
	mov r1, #7
	tst r1, r0
	bne _021E26E2
	lsr r7, r0, #3
	b _021E26E6
_021E26E2:
	lsr r0, r0, #3
	add r7, r0, #1
_021E26E6:
	add r0, r5, #0
	add r0, #0x9b
	ldrb r0, [r0]
	add r1, r6, #0
	str r0, [sp, #0x14]
	bl _s32_div_f
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, [sp, #0x14]
	add r1, r6, #0
	bl _s32_div_f
	cmp r1, #0
	beq _021E270A
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_021E270A:
	add r0, r5, #0
	add r0, #0x99
	ldrb r0, [r0]
	add r3, r5, #0
	add r1, r5, #0
	str r0, [sp]
	add r0, r7, #0
	mul r0, r6
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	lsl r0, r4, #0x19
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x3d
	str r0, [sp, #0x10]
	ldr r0, [r5]
	add r3, #0x98
	ldrb r3, [r3]
	ldr r0, [r0, #8]
	add r1, #8
	mov r2, #3
	bl AddWindowParameterized
	mov r0, #0
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r5]
	ldr r2, _021E2794 ; =0x000003D9
	ldr r0, [r0, #8]
	mov r1, #3
	mov r3, #0xb
	bl FUN_0200CB00
	add r0, r5, #0
	ldr r2, _021E2794 ; =0x000003D9
	add r0, #8
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD05_021E279C
	add r1, r5, #0
	add r1, #0x96
	add r0, r5, #0
	ldrb r1, [r1]
	add r0, #0xa4
	mov r2, #4
	bl FUN_02001C34
	add r1, r5, #0
	add r1, #0xb0
	str r0, [r1]
	ldr r0, _021E2798 ; =MOD05_021E1E58
	add r1, r5, #0
	mov r2, #0
	bl FUN_0200CA44
	str r0, [r5, #4]
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E2794: .word 0x000003D9
_021E2798: .word MOD05_021E1E58

	thumb_func_start MOD05_021E279C
MOD05_021E279C: ; 0x021E279C
	push {r3, r4}
	add r4, r0, #0
	add r3, r0, #0
	add r4, #0xb4
	add r3, #0xa4
	str r4, [r3]
	add r4, r0, #0
	add r3, r0, #0
	add r4, #8
	add r3, #0xa8
	str r4, [r3]
	add r3, r0, #0
	mov r4, #0
	add r3, #0xac
	strb r4, [r3]
	add r3, r0, #0
	add r3, #0xad
	strb r1, [r3]
	add r1, r0, #0
	add r1, #0xae
	strb r2, [r1]
	add r1, r0, #0
	add r1, #0xaf
	ldrb r2, [r1]
	mov r1, #0xf
	bic r2, r1
	add r1, r0, #0
	add r1, #0xaf
	strb r2, [r1]
	add r1, r0, #0
	add r1, #0xaf
	ldrb r2, [r1]
	mov r1, #0x30
	add r0, #0xaf
	bic r2, r1
	strb r2, [r0]
	pop {r3, r4}
	bx lr

	thumb_func_start MOD05_021E27E8
MOD05_021E27E8: ; 0x021E27E8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r7, r1, #0
	add r6, r2, #0
	mov r0, #4
	mov r1, #1
	bl AllocWindows
	add r4, r0, #0
	str r6, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, [r5, #8]
	add r1, r4, #0
	mov r2, #3
	add r3, r7, #0
	bl AddWindowParameterized
	mov r0, #0
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r5, #8]
	ldr r2, _021E2888 ; =0x000003D9
	mov r1, #3
	mov r3, #0xb
	bl FUN_0200CB00
	ldr r2, _021E2888 ; =0x000003D9
	add r0, r4, #0
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	add r0, r4, #0
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r2, #0x7a
	mov r0, #0
	mov r1, #0x1a
	lsl r2, r2, #2
	mov r3, #4
	bl NewMsgDataFromNarc
	mov r1, #0x12
	add r7, r0, #0
	bl NewString_ReadMsgData
	mov r1, #0
	add r6, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	add r0, r4, #0
	add r2, r6, #0
	add r3, r1, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r7, #0
	bl DestroyMsgData
	add r0, r6, #0
	bl String_dtor
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021E28A0
	add r0, r4, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021E2888: .word 0x000003D9

	thumb_func_start MOD05_021E288C
MOD05_021E288C: ; 0x021E288C
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	bl FUN_0200CCF8
	add r0, r4, #0
	mov r1, #1
	bl WindowArray_dtor
	pop {r4, pc}

	thumb_func_start MOD05_021E28A0
MOD05_021E28A0: ; 0x021E28A0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r0, #0
	add r5, r1, #0
	mov r0, #0x50
	str r0, [sp]
	mov r3, #0x10
	add r0, r5, #0
	mov r1, #0xf
	mov r2, #0
	str r3, [sp, #4]
	bl FillWindowPixelRect
	mov r2, #0x7a
	mov r0, #0
	mov r1, #0x1a
	lsl r2, r2, #2
	mov r3, #4
	bl NewMsgDataFromNarc
	str r0, [sp, #0xc]
	mov r0, #4
	bl ScrStrBufs_new
	add r6, r0, #0
	mov r0, #0x10
	mov r1, #4
	bl String_ctor
	add r4, r0, #0
	ldr r0, [sp, #0xc]
	mov r1, #0x13
	bl NewString_ReadMsgData
	str r0, [sp, #0x10]
	ldr r0, [r7, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	bl PlayerProfile_GetMoney
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r6, #0
	mov r1, #0
	mov r3, #6
	bl BufferIntegerAsString
	ldr r2, [sp, #0x10]
	add r0, r6, #0
	add r1, r4, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r4, #0
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0x50
	sub r3, r1, r0
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	add r0, r5, #0
	add r2, r4, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x10]
	bl String_dtor
	add r0, r4, #0
	bl String_dtor
	add r0, r6, #0
	bl ScrStrBufs_delete
	ldr r0, [sp, #0xc]
	bl DestroyMsgData
	add r0, r5, #0
	bl ScheduleWindowCopyToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021E2950
MOD05_021E2950: ; 0x021E2950
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r7, r1, #0
	add r6, r2, #0
	mov r0, #4
	mov r1, #1
	bl AllocWindows
	add r4, r0, #0
	str r6, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x29
	str r0, [sp, #0x10]
	ldr r0, [r5, #8]
	add r1, r4, #0
	mov r2, #3
	add r3, r7, #0
	bl AddWindowParameterized
	mov r0, #0
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r5, #8]
	ldr r2, _021E29B0 ; =0x000003D9
	mov r1, #3
	mov r3, #0xb
	bl FUN_0200CB00
	ldr r2, _021E29B0 ; =0x000003D9
	add r0, r4, #0
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021E29C8
	add r0, r4, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021E29B0: .word 0x000003D9

	thumb_func_start MOD05_021E29B4
MOD05_021E29B4: ; 0x021E29B4
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	bl FUN_0200CCF8
	add r0, r4, #0
	mov r1, #1
	bl WindowArray_dtor
	pop {r4, pc}

	thumb_func_start MOD05_021E29C8
MOD05_021E29C8: ; 0x021E29C8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	str r1, [sp, #0xc]
	add r0, r1, #0
	mov r1, #0xf
	bl FillWindowPixelBuffer
	ldr r2, _021E2A6C ; =0x00000141
	mov r0, #0
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	add r7, r0, #0
	mov r0, #4
	bl ScrStrBufs_new
	add r5, r0, #0
	mov r0, #0x10
	mov r1, #4
	bl String_ctor
	add r4, r0, #0
	add r0, r7, #0
	mov r1, #0xc5
	bl NewString_ReadMsgData
	str r0, [sp, #0x10]
	ldr r0, [r6, #0xc]
	bl Sav2_PlayerData_GetCoinsAddr
	bl CheckCoins
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #0
	mov r3, #5
	bl BufferIntegerAsString
	ldr r2, [sp, #0x10]
	add r0, r5, #0
	add r1, r4, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r4, #0
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0x50
	sub r3, r1, r0
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0xc]
	add r2, r4, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x10]
	bl String_dtor
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	bl ScrStrBufs_delete
	add r0, r7, #0
	bl DestroyMsgData
	ldr r0, [sp, #0xc]
	bl ScheduleWindowCopyToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021E2A6C: .word 0x00000141

	thumb_func_start MOD05_021E2A70
MOD05_021E2A70: ; 0x021E2A70
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r7, r1, #0
	add r6, r2, #0
	mov r0, #4
	mov r1, #1
	bl AllocWindows
	add r4, r0, #0
	str r6, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x29
	str r0, [sp, #0x10]
	ldr r0, [r5, #8]
	add r1, r4, #0
	mov r2, #3
	add r3, r7, #0
	bl AddWindowParameterized
	mov r0, #0
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r5, #8]
	ldr r2, _021E2AD0 ; =0x000003D9
	mov r1, #3
	mov r3, #0xb
	bl FUN_0200CB00
	ldr r2, _021E2AD0 ; =0x000003D9
	add r0, r4, #0
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021E2AD4
	add r0, r4, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021E2AD0: .word 0x000003D9

	thumb_func_start MOD05_021E2AD4
MOD05_021E2AD4: ; 0x021E2AD4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	str r1, [sp, #0xc]
	add r0, r1, #0
	mov r1, #0xf
	bl FillWindowPixelBuffer
	ldr r2, _021E2B7C ; =0x00000141
	mov r0, #0
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	add r7, r0, #0
	mov r0, #4
	bl ScrStrBufs_new
	add r5, r0, #0
	mov r0, #0x10
	mov r1, #4
	bl String_ctor
	add r4, r0, #0
	add r0, r7, #0
	mov r1, #0xe6
	bl NewString_ReadMsgData
	str r0, [sp, #0x10]
	ldr r0, [r6, #0xc]
	bl FUN_0202A8D8
	mov r1, #0
	add r2, r1, #0
	bl FUN_0202A3B4
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #0
	mov r3, #5
	bl BufferIntegerAsString
	ldr r2, [sp, #0x10]
	add r0, r5, #0
	add r1, r4, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r4, #0
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0x50
	sub r3, r1, r0
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0xc]
	add r2, r4, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x10]
	bl String_dtor
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	bl ScrStrBufs_delete
	add r0, r7, #0
	bl DestroyMsgData
	ldr r0, [sp, #0xc]
	bl ScheduleWindowCopyToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021E2B7C: .word 0x00000141
