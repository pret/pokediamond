	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD08_02211E60
MOD08_02211E60: ; 0x02211E60
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _02211E70
	lsl r1, r0, #2
	ldr r0, _02211E74 ; =0x0222A9E4
	ldr r0, [r0, r1]
	bx lr
_02211E70:
	ldr r0, _02211E78 ; =0x0222A780
	bx lr
	.align 2, 0
_02211E74: .word MOD8_0222A9E4
_02211E78: .word MOD8_0222A780

	thumb_func_start MOD08_02211E7C
MOD08_02211E7C: ; 0x02211E7C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, r1, #0
	add r4, r3, #0
	bl MOD08_02211E60
	ldr r3, [sp, #0x10]
	add r1, r0, #0
	mov r0, #0x20
	lsl r3, r3, #0x14
	str r0, [sp]
	add r0, r5, #0
	add r2, r4, #0
	lsr r3, r3, #0x10
	bl FUN_02003054
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02211EA0
MOD08_02211EA0: ; 0x02211EA0
	add r1, r0, #0
	add r1, #0x8d
	ldrb r1, [r1]
	cmp r1, #0
	bne _02211EB2
	ldr r1, _02211EC0 ; =MOD08_02211EC4
	add r0, #0xbc
	str r1, [r0]
	bx lr
_02211EB2:
	add r1, r0, #0
	add r1, #0x8d
	ldrb r1, [r1]
	add r0, #0x8d
	sub r1, r1, #1
	strb r1, [r0]
	bx lr
	.align 2, 0
_02211EC0: .word MOD08_02211EC4

	thumb_func_start MOD08_02211EC4
MOD08_02211EC4: ; 0x02211EC4
	push {r4, lr}
	add r4, r0, #0
_02211EC8:
	ldr r0, [r4, #0x18]
	ldr r0, [r0]
	bl MOD08_0221533C
	add r1, r0, #0
	add r0, r4, #0
	blx r1
	add r0, r4, #0
	add r0, #0x8d
	ldrb r0, [r0]
	cmp r0, #0
	bne _02211EE6
	ldr r0, [r4, #0x10]
	cmp r0, #1
	beq _02211EC8
_02211EE6:
	pop {r4, pc}

	thumb_func_start MOD08_02211EE8
MOD08_02211EE8: ; 0x02211EE8
	push {r3, r4, r5, lr}
	add r5, r2, #0
	add r4, r3, #0
	cmp r0, #1
	beq _02211EF8
	cmp r0, #2
	beq _02211F06
	b _02211F14
_02211EF8:
	add r0, r1, #0
	add r0, #0x8e
	ldrh r0, [r0]
	add r1, #0x8e
	add r0, r0, #1
	strh r0, [r1]
	b _02211F18
_02211F06:
	add r0, r1, #0
	add r0, #0x90
	ldrh r0, [r0]
	add r1, #0x90
	add r0, r0, #1
	strh r0, [r1]
	b _02211F18
_02211F14:
	bl ErrorHandling
_02211F18:
	ldr r2, [sp, #0x10]
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02211F24
MOD08_02211F24: ; 0x02211F24
	push {r4, lr}
	add r4, r2, #0
	cmp r0, #1
	beq _02211F32
	cmp r0, #2
	beq _02211F40
	b _02211F4E
_02211F32:
	add r0, r1, #0
	add r0, #0x8e
	ldrh r0, [r0]
	add r1, #0x8e
	sub r0, r0, #1
	strh r0, [r1]
	b _02211F52
_02211F40:
	add r0, r1, #0
	add r0, #0x90
	ldrh r0, [r0]
	add r1, #0x90
	sub r0, r0, #1
	strh r0, [r1]
	b _02211F52
_02211F4E:
	bl ErrorHandling
_02211F52:
	add r0, r4, #0
	bl FUN_0200CAB4
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02211F5C
MOD08_02211F5C: ; 0x02211F5C
	push {r3, r4, r5, lr}
	mov r1, #0x69
	lsl r1, r1, #2
	add r5, r0, #0
	bl AllocFromHeap
	add r4, r0, #0
	bne _02211F78
	cmp r4, #0
	bne _02211F74
	bl ErrorHandling
_02211F74:
	mov r0, #0
	pop {r3, r4, r5, pc}
_02211F78:
	mov r2, #0x69
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	mov r1, #0x47
	str r5, [r4]
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4]
	lsl r1, r1, #2
	bl AllocFromHeap
	add r1, r4, #0
	add r1, #0xc0
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	cmp r0, #0
	bne _02211FAC
	bne _02211FA8
	bl ErrorHandling
_02211FA8:
	mov r0, #0
	pop {r3, r4, r5, pc}
_02211FAC:
	mov r2, #0x47
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	mov r1, #0
	str r1, [r4, #0xc]
	str r1, [r4, #0x18]
	add r2, r4, #0
	add r3, r1, #0
_02211FC0:
	add r0, r2, #0
	add r0, #0xcc
	add r1, r1, #1
	add r2, r2, #4
	str r3, [r0]
	cmp r1, #4
	blt _02211FC0
	mov r0, #0x59
	add r2, r4, #0
	mov r1, #0
	lsl r0, r0, #2
_02211FD6:
	add r3, r3, #1
	str r1, [r2, r0]
	add r2, r2, #4
	cmp r3, #5
	blt _02211FD6
	mov r0, #0x5e
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #1
	str r0, [r4, #0xc]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02211FF0
MOD08_02211FF0: ; 0x02211FF0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	cmp r5, #0
	bne _02211FFE
	bl ErrorHandling
_02211FFE:
	str r4, [r5, #8]
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02212004
MOD08_02212004: ; 0x02212004
	push {r4, lr}
	add r4, r0, #0
	bne _0221200E
	bl ErrorHandling
_0221200E:
	ldr r0, [r4, #8]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02212014
MOD08_02212014: ; 0x02212014
	push {r4, lr}
	add r4, r0, #0
	bne _0221201E
	bl ErrorHandling
_0221201E:
	ldr r0, [r4]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02212024
MOD08_02212024: ; 0x02212024
	push {r4, lr}
	add r4, r0, #0
	bl MOD08_022123CC
	cmp r0, #0
	bne _02212034
	mov r0, #0
	pop {r4, pc}
_02212034:
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD08_02212048
MOD08_02212048: ; 0x02212048
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	add r4, r0, #0
	add r5, r1, #0
	str r2, [sp]
	str r3, [sp, #4]
	bl MOD08_0221268C
	add r0, r4, #0
	bl MOD08_022123CC
	cmp r0, #0
	bne _02212068
	add sp, #0x3c
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_02212068:
	mov r3, #0
	mov r2, #1
	add r1, r3, #0
_0221206E:
	add r0, r4, r3
	add r0, #0x6c
	strb r2, [r0]
	add r0, r4, r3
	add r0, #0x7c
	add r3, r3, #1
	strb r1, [r0]
	cmp r3, #0x10
	blt _0221206E
	add r3, r4, #0
	mov r0, #0
_02212084:
	add r2, r3, #0
	add r2, #0x94
	add r1, r1, #1
	add r3, r3, #4
	str r0, [r2]
	cmp r1, #0xa
	blt _02212084
	add r3, r4, #0
	mov r2, #0
_02212096:
	str r2, [r3, #0x30]
	add r1, r3, #0
	str r2, [r3, #0x28]
	add r1, #0x2c
	strb r2, [r1]
	add r1, r3, #0
	add r1, #0x2d
	add r0, r0, #1
	add r3, #0xc
	strb r2, [r1]
	cmp r0, #3
	blt _02212096
	add r0, r4, #0
	add r0, #0xc0
	ldrb r1, [r5]
	ldr r0, [r0]
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0xc0
	ldrb r1, [r5, #1]
	ldr r0, [r0]
	strb r1, [r0, #1]
	add r0, r4, #0
	add r0, #0xc0
	ldrh r1, [r5, #2]
	ldr r0, [r0]
	strh r1, [r0, #2]
	add r0, r4, #0
	add r0, #0xc0
	ldr r1, [r5, #4]
	ldr r0, [r0]
	str r1, [r0, #4]
	add r0, r4, #0
	add r0, #0xc0
	ldrh r1, [r5, #8]
	ldr r0, [r0]
	strh r1, [r0, #8]
	add r0, r4, #0
	add r0, #0xc0
	ldrh r1, [r5, #0xc]
	ldr r0, [r0]
	strh r1, [r0, #0xa]
	add r0, r4, #0
	add r0, #0xc0
	ldr r1, [r5, #0x10]
	ldr r0, [r0]
	str r1, [r0, #0xc]
	add r0, r4, #0
	add r0, #0xc0
	ldrh r1, [r5, #0xa]
	ldr r0, [r0]
	strh r1, [r0, #0x10]
	add r0, r4, #0
	add r0, #0xc0
	ldr r1, [r5, #0x54]
	ldr r0, [r0]
	strh r1, [r0, #0x12]
	add r0, r4, #0
	add r0, #0xc0
	ldrh r1, [r5, #0x14]
	ldr r0, [r0]
	strh r1, [r0, #0x14]
	add r0, r4, #0
	add r0, #0xc0
	ldrh r1, [r5, #0x16]
	ldr r0, [r0]
	strh r1, [r0, #0x16]
	ldrh r0, [r5, #0xe]
	lsl r0, r0, #0x1e
	lsr r2, r0, #0x1f
	add r0, r4, #0
	add r0, #0xc0
	ldr r1, [r0]
	mov r0, #0x46
	lsl r0, r0, #2
	str r2, [r1, r0]
	ldr r0, [sp, #4]
	ldr r1, [r0]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r0, #0xac
	str r1, [r0]
	ldr r0, [sp, #4]
	ldr r0, [r0]
	cmp r0, #0
	bne _02212148
	bl ErrorHandling
_02212148:
	ldr r0, [sp, #4]
	mov r5, #0
	ldr r1, [r0, #4]
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	ldr r0, [sp, #4]
	ldr r2, [sp, #4]
	ldr r1, [r0, #8]
	add r0, r4, #0
	add r0, #0xc8
	str r1, [r0]
	ldr r0, [sp, #4]
	add r3, r5, #0
	ldr r1, [r0, #0x30]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r7, r5, #0
	add r0, #0xd4
	str r1, [r0]
	add r0, r2, #0
	mov ip, r0
_02212176:
	add r1, r4, #0
	add r1, #0xc0
	ldr r1, [r1]
	ldr r0, [r2, #0xc]
	add r1, r1, r3
	add r1, #0xb0
	str r0, [r1]
	ldr r0, [sp, #4]
	add r1, r0, r5
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldrb r6, [r1, #0x1c]
	add r0, r0, r5
	add r0, #0xc0
	strb r6, [r0]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r6, [r2, #0x20]
	add r0, r0, r3
	add r0, #0xc4
	str r6, [r0]
	mov r0, ip
	ldrh r6, [r0, #0x34]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r0, r0, r7
	add r0, #0xd8
	strh r6, [r0]
	add r0, r1, #0
	add r0, #0x3c
	ldrb r6, [r0]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r7, r7, #2
	add r0, r0, r5
	add r0, #0xe0
	strb r6, [r0]
	add r0, r1, #0
	add r0, #0x40
	ldrb r6, [r0]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r1, #0x44
	add r0, r0, r5
	add r0, #0xe4
	strb r6, [r0]
	ldrb r0, [r1]
	add r1, r4, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r1, r1, r5
	add r1, #0xe8
	strb r0, [r1]
	add r1, r4, #0
	add r1, #0xc0
	ldr r1, [r1]
	ldr r0, [r2, #0x48]
	add r1, r1, r3
	add r1, #0xec
	str r0, [r1]
	add r1, r4, #0
	add r1, #0xc0
	ldr r1, [r1]
	ldr r0, [r2, #0x58]
	add r1, r1, r3
	add r1, #0xfc
	str r0, [r1]
	mov r0, ip
	add r0, r0, #2
	add r5, r5, #1
	add r2, r2, #4
	add r3, r3, #4
	mov ip, r0
	cmp r5, #4
	blt _02212176
	ldr r5, [sp, #4]
	mov r2, #0x61
	lsl r2, r2, #2
	add r5, #0x6c
	add r3, r4, r2
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [sp, #4]
	add r0, #0x84
	ldr r3, [r0]
	add r0, r4, #0
	add r0, #0xc0
	ldr r1, [r0]
	add r0, r2, #0
	sub r0, #0x78
	str r3, [r1, r0]
	ldr r0, [sp, #4]
	add r0, #0x8c
	ldr r3, [r0]
	add r0, r4, #0
	add r0, #0xc0
	ldr r1, [r0]
	add r0, r2, #0
	sub r0, #0x70
	str r3, [r1, r0]
	ldr r0, [sp, #4]
	add r0, #0x88
	ldr r3, [r0]
	add r0, r4, #0
	add r0, #0xc0
	ldr r1, [r0]
	add r0, r2, #0
	sub r0, #0x74
	str r3, [r1, r0]
	ldr r0, [sp]
	sub r2, #0x62
	cmp r0, r2
	bne _02212296
	ldr r5, _0221236C ; =0x0222AB18
	add r3, sp, #8
	mov r2, #6
_02212270:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02212270
	ldr r0, [r5]
	str r0, [r3]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldrh r0, [r0, #0x12]
	cmp r0, #0xc
	blo _0221228E
	mov r0, #0xa1
	str r0, [sp]
	b _02212296
_0221228E:
	lsl r1, r0, #2
	add r0, sp, #8
	ldr r0, [r0, r1]
	str r0, [sp]
_02212296:
	ldr r0, [sp]
	cmp r0, #0
	beq _022122A2
	ldr r1, _02212370 ; =0x000001D3
	cmp r0, r1
	ble _022122A6
_022122A2:
	mov r0, #1
	str r0, [sp]
_022122A6:
	ldr r0, [sp, #4]
	ldr r0, [r0, #0x68]
	str r0, [r4, #4]
	ldr r1, [sp]
	ldr r2, [r4]
	bl AllocAndReadWholeNarcMemberByIdPair
	str r0, [r4, #0x14]
	cmp r0, #0
	bne _022122C6
	bne _022122C0
	bl ErrorHandling
_022122C0:
	add sp, #0x3c
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_022122C6:
	str r0, [r4, #0x18]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #0
	bl FUN_02018884
	mov r1, #0x1a
	lsl r1, r1, #4
	strb r0, [r4, r1]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #1
	bl FUN_02018884
	ldr r1, _02212374 ; =0x000001A1
	strb r0, [r4, r1]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #2
	bl FUN_02018884
	ldr r1, _02212378 ; =0x000001A2
	strb r0, [r4, r1]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #3
	bl FUN_02018884
	ldr r1, _0221237C ; =0x000001A3
	mov r3, #0
	strb r0, [r4, r1]
	add r2, r4, #0
	add r1, r3, #0
_02212310:
	add r0, r2, #0
	add r0, #0xdc
	add r3, r3, #1
	add r2, r2, #4
	str r1, [r0]
	cmp r3, #0xa
	blt _02212310
	mov r2, #0x4f
	lsl r2, r2, #2
	add r3, r2, #0
	add r5, r4, #0
	mov r0, #0
	add r3, #0x14
_0221232A:
	str r0, [r5, r2]
	str r0, [r5, r3]
	add r1, r1, #1
	add r5, r5, #4
	cmp r1, #5
	blt _0221232A
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r4, r1]
	add r1, r4, #0
	ldr r2, _02212380 ; =MOD08_02211EC4
	add r1, #0xbc
	str r2, [r1]
	add r1, r4, #0
	add r1, #0x8d
	strb r0, [r1]
	add r0, r4, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _0221235C
	mov r0, #0x67
	mov r1, #7
	lsl r0, r0, #2
	b _02212362
_0221235C:
	mov r1, #0xff
	add r0, r1, #0
	add r0, #0x9d
_02212362:
	str r1, [r4, r0]
	mov r0, #1
	str r0, [r4, #0x10]
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0221236C: .word MOD8_0222AB18
_02212370: .word 0x000001D3
_02212374: .word 0x000001A1
_02212378: .word 0x000001A2
_0221237C: .word 0x000001A3
_02212380: .word MOD08_02211EC4

	thumb_func_start MOD08_02212384
MOD08_02212384: ; 0x02212384
	push {r4, lr}
	add r4, r0, #0
	bl MOD08_022123CC
	cmp r0, #0
	bne _02212394
	mov r0, #0
	pop {r4, pc}
_02212394:
	add r0, r4, #0
	add r4, #0xbc
	ldr r1, [r4]
	blx r1
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD08_022123A0
MOD08_022123A0: ; 0x022123A0
	ldr r0, [r0, #0x10]
	cmp r0, #1
	bne _022123AA
	mov r0, #1
	bx lr
_022123AA:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD08_022123B0
MOD08_022123B0: ; 0x022123B0
	push {r3, lr}
	ldr r0, [r0, #0x14]
	cmp r0, #0
	bne _022123C2
	bne _022123BE
	bl ErrorHandling
_022123BE:
	mov r0, #0
	pop {r3, pc}
_022123C2:
	bl FreeToHeap
	mov r0, #1
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD08_022123CC
MOD08_022123CC: ; 0x022123CC
	cmp r0, #0
	bne _022123D4
	mov r0, #0
	bx lr
_022123D4:
	ldr r0, [r0, #0xc]
	cmp r0, #1
	bne _022123DE
	mov r0, #1
	bx lr
_022123DE:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD08_022123E4
MOD08_022123E4: ; 0x022123E4
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r6, r0, #0
	add r5, r1, #0
	add r4, r2, #0
	str r3, [sp]
	mov r0, #1
	add r1, r6, #0
	add r2, r5, #0
	add r3, r4, #0
	bl MOD08_02211EE8
	add sp, #4
	pop {r3, r4, r5, r6, pc}

	thumb_func_start MOD08_02212400
MOD08_02212400: ; 0x02212400
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _02212418 ; =0x0000044C
	add r4, r1, #0
	add r3, r2, #0
	str r0, [sp]
	mov r0, #1
	add r1, r5, #0
	add r2, r4, #0
	bl MOD08_02211EE8
	pop {r3, r4, r5, pc}
	.align 2, 0
_02212418: .word 0x0000044C

	thumb_func_start MOD08_0221241C
MOD08_0221241C: ; 0x0221241C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r6, r0, #0
	add r5, r1, #0
	add r4, r2, #0
	str r3, [sp]
	mov r0, #2
	add r1, r6, #0
	add r2, r5, #0
	add r3, r4, #0
	bl MOD08_02211EE8
	add sp, #4
	pop {r3, r4, r5, r6, pc}

	thumb_func_start MOD08_02212438
MOD08_02212438: ; 0x02212438
	add r3, r0, #0
	add r2, r1, #0
	add r1, r3, #0
	ldr r3, _02212444 ; =MOD08_02211F24
	mov r0, #1
	bx r3
	.align 2, 0
_02212444: .word MOD08_02211F24

	thumb_func_start MOD08_02212448
MOD08_02212448: ; 0x02212448
	add r3, r0, #0
	add r2, r1, #0
	add r1, r3, #0
	ldr r3, _02212454 ; =MOD08_02211F24
	mov r0, #2
	bx r3
	.align 2, 0
_02212454: .word MOD08_02211F24

	thumb_func_start MOD08_02212458
MOD08_02212458: ; 0x02212458
	add r0, #0xc0
	ldr r0, [r0]
	ldrh r0, [r0, #0x14]
	bx lr

	thumb_func_start MOD08_02212460
MOD08_02212460: ; 0x02212460
	add r0, #0xc0
	ldr r0, [r0]
	ldrh r0, [r0, #0x16]
	bx lr

	thumb_func_start MOD08_02212468
MOD08_02212468: ; 0x02212468
	add r0, #0xc0
	ldr r1, [r0]
	ldr r0, [r1, #0x18]
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, #0x1c]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02212478
MOD08_02212478: ; 0x02212478
	add r0, #0xc0
	ldr r2, [r0]
	lsl r0, r1, #2
	add r0, r2, r0
	ldr r0, [r0, #0x1c]
	bx lr

	thumb_func_start MOD08_02212484
MOD08_02212484: ; 0x02212484
	add r0, #0xc0
	ldr r2, [r0]
	lsl r0, r1, #2
	add r0, r2, r0
	ldr r0, [r0, #0x5c]
	bx lr

	thumb_func_start MOD08_02212490
MOD08_02212490: ; 0x02212490
	add r0, #0xc4
	ldr r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02212498
MOD08_02212498: ; 0x02212498
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	cmp r5, #0xa
	blt _022124A6
	bl ErrorHandling
_022124A6:
	lsl r0, r5, #2
	add r0, r4, r0
	add r0, #0x94
	ldr r0, [r0]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_022124B0
MOD08_022124B0: ; 0x022124B0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	cmp r4, #0xa
	blt _022124BE
	bl ErrorHandling
_022124BE:
	cmp r5, #0
	bne _022124C6
	bl ErrorHandling
_022124C6:
	add r5, #0xdc
	lsl r4, r4, #2
	ldr r0, [r5, r4]
	cmp r0, #0
	bne _022124D4
	bl ErrorHandling
_022124D4:
	ldr r0, [r5, r4]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_022124D8
MOD08_022124D8: ; 0x022124D8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	cmp r4, #5
	blt _022124E6
	bl ErrorHandling
_022124E6:
	cmp r5, #0
	bne _022124EE
	bl ErrorHandling
_022124EE:
	mov r0, #0x4f
	lsl r0, r0, #2
	add r5, r5, r0
	lsl r4, r4, #2
	ldr r0, [r5, r4]
	cmp r0, #0
	bne _02212500
	bl ErrorHandling
_02212500:
	ldr r0, [r5, r4]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02212504
MOD08_02212504: ; 0x02212504
	push {r4, lr}
	add r4, r0, #0
	bne _0221250E
	bl ErrorHandling
_0221250E:
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02212518
MOD08_02212518: ; 0x02212518
	add r0, #0xcc
	ldr r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02212520
MOD08_02212520: ; 0x02212520
	add r0, #0xc0
	ldr r0, [r0]
	add r0, #0xac
	ldr r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_0221252C
MOD08_0221252C: ; 0x0221252C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	mov r1, #0x3c
	bl AllocFromHeap
	add r4, r0, #0
	bne _02212544
	bl ErrorHandling
	mov r0, #0
	pop {r3, r4, r5, pc}
_02212544:
	mov r1, #0
	mov r2, #0x3c
	bl memset
	add r0, r5, #0
	add r0, #0x90
	ldrh r0, [r0]
	add r5, #0x90
	add r0, r0, #1
	strh r0, [r5]
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_0221255C
MOD08_0221255C: ; 0x0221255C
	ldr r3, _02212568 ; =FUN_0200CA44
	str r0, [r1, #0x38]
	ldr r0, _0221256C ; =MOD08_02212574
	ldr r2, _02212570 ; =0x0000044C
	bx r3
	nop
_02212568: .word FUN_0200CA44
_0221256C: .word MOD08_02212574
_02212570: .word 0x0000044C

	thumb_func_start MOD08_02212574
MOD08_02212574: ; 0x02212574
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _022125B0 ; =0x0222AAC4
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	bne _022125AE
	ldr r0, [r4, #0x38]
	add r1, r0, #0
	add r1, #0x90
	ldrh r1, [r1]
	cmp r1, #0
	beq _022125A2
	add r1, r0, #0
	add r1, #0x90
	ldrh r1, [r1]
	add r0, #0x90
	sub r1, r1, #1
	strh r1, [r0]
_022125A2:
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_022125AE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022125B0: .word MOD8_0222AAC4

	thumb_func_start MOD08_022125B4
MOD08_022125B4: ; 0x022125B4
	mov r0, #0
	bx lr

	thumb_func_start MOD08_022125B8
MOD08_022125B8: ; 0x022125B8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldrb r1, [r5, #4]
	add r0, r1, #1
	strb r0, [r5, #4]
	ldrb r0, [r5, #3]
	cmp r1, r0
	bhs _022125CC
	mov r0, #1
	pop {r3, r4, r5, pc}
_022125CC:
	mov r0, #0
	strb r0, [r5, #4]
	ldr r2, [r5, #0x14]
	ldr r1, [r5, #0x10]
	mov r4, #1
	add r1, r2, r1
	str r1, [r5, #0x14]
	ldr r1, [r5, #0x10]
	cmp r1, #0
	bne _022125E4
	add r4, r0, #0
	b _022125FC
_022125E4:
	ldr r2, [r5, #0xc]
	ldr r1, [r5, #8]
	cmp r1, r2
	ldr r1, [r5, #0x14]
	bge _022125F6
	cmp r1, r2
	blt _022125FC
	add r4, r0, #0
	b _022125FC
_022125F6:
	cmp r1, r2
	bgt _022125FC
	add r4, r0, #0
_022125FC:
	ldr r0, [r5, #0x14]
	bl FUN_0200554C
	ldrh r0, [r5, #0x1a]
	bl FUN_02005508
	cmp r0, #0
	bne _0221260E
	mov r4, #0
_0221260E:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02212614
MOD08_02212614: ; 0x02212614
	ldr r3, _02212618 ; =MOD08_022125B8
	bx r3
	.align 2, 0
_02212618: .word MOD08_022125B8

	thumb_func_start MOD08_0221261C
MOD08_0221261C: ; 0x0221261C
	ldr r3, _02212620 ; =MOD08_022125B8
	bx r3
	.align 2, 0
_02212620: .word MOD08_022125B8

	thumb_func_start MOD08_02212624
MOD08_02212624: ; 0x02212624
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldrb r1, [r5, #4]
	add r0, r1, #1
	strb r0, [r5, #4]
	ldrb r0, [r5, #3]
	cmp r1, r0
	bhs _02212638
	mov r0, #1
	pop {r3, r4, r5, pc}
_02212638:
	mov r0, #0
	strb r0, [r5, #4]
	ldrb r0, [r5, #0x18]
	mov r4, #1
	sub r0, r0, #1
	strb r0, [r5, #0x18]
	ldrh r0, [r5, #0x1a]
	bl FUN_020054C8
	ldrh r0, [r5, #0x1a]
	ldr r1, _02212660 ; =0x0000FFFF
	ldr r2, [r5, #0x14]
	bl FUN_02005530
	ldrb r0, [r5, #0x18]
	cmp r0, #0
	bne _0221265C
	mov r4, #0
_0221265C:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02212660: .word 0x0000FFFF

	thumb_func_start MOD08_02212664
MOD08_02212664: ; 0x02212664
	push {r4, lr}
	add r4, r0, #0
	ldrb r2, [r4, #3]
	mov r0, #1
	sub r1, r2, #1
	strb r1, [r4, #3]
	cmp r2, #0
	bne _02212686
	ldrh r0, [r4, #0x1a]
	bl FUN_020054C8
	ldrh r0, [r4, #0x1a]
	ldr r1, _02212688 ; =0x0000FFFF
	ldr r2, [r4, #0x14]
	bl FUN_02005530
	mov r0, #0
_02212686:
	pop {r4, pc}
	.align 2, 0
_02212688: .word 0x0000FFFF

	thumb_func_start MOD08_0221268C
MOD08_0221268C: ; 0x0221268C
	push {r3, lr}
	ldr r0, _022126A0 ; =0x04000050
	mov r3, #8
	mov r1, #0
	mov r2, #0x3f
	str r3, [sp]
	bl G2x_SetBlendAlpha_
	pop {r3, pc}
	nop
_022126A0: .word 0x04000050

	thumb_func_start MOD08_022126A4
MOD08_022126A4: ; 0x022126A4
	push {r3, r4}
	add r2, r0, #0
	mov r1, #1
	add r2, #0x8d
	strb r1, [r2]
	ldr r3, _022126D8 ; =gMain
	lsl r2, r1, #9
	ldr r4, [r3, #0x44]
	tst r2, r4
	beq _022126D4
	add r2, r1, #0
	add r2, #0xff
	tst r2, r4
	beq _022126D4
	ldr r2, [r3, #0x48]
	lsl r1, r1, #0xa
	tst r1, r2
	beq _022126D4
	ldr r1, [r0, #0x18]
	add r1, r1, #4
	str r1, [r0, #0x18]
	mov r1, #0
	add r0, #0x8d
	strb r1, [r0]
_022126D4:
	pop {r3, r4}
	bx lr
	.align 2, 0
_022126D8: .word gMain

	thumb_func_start MOD08_022126DC
MOD08_022126DC: ; 0x022126DC
	ldr r1, [r0, #0x18]
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r2, [r1]
	add r1, r0, #0
	add r1, #0x8d
	strb r2, [r1]
	ldr r1, [r0, #0x18]
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r1, _022126F8 ; =MOD08_02211EA0
	add r0, #0xbc
	str r1, [r0]
	bx lr
	.align 2, 0
_022126F8: .word MOD08_02211EA0

	thumb_func_start MOD08_022126FC
MOD08_022126FC: ; 0x022126FC
	add r1, r0, #0
	add r1, #0x8e
	ldrh r1, [r1]
	cmp r1, #0
	bne _02212714
	ldr r1, [r0, #0x18]
	add r1, r1, #4
	str r1, [r0, #0x18]
	mov r1, #0
	add r0, #0x8d
	strb r1, [r0]
	bx lr
_02212714:
	mov r1, #1
	add r0, #0x8d
	strb r1, [r0]
	bx lr

	thumb_func_start MOD08_0221271C
MOD08_0221271C: ; 0x0221271C
	ldr r1, [r0, #0x18]
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r3, [r1]
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r2, [r1]
	add r1, r1, #4
	str r1, [r0, #0x18]
	cmp r3, #0xa
	bhs _0221273A
	lsl r1, r3, #2
	add r0, r0, r1
	add r0, #0x94
	str r2, [r0]
_0221273A:
	bx lr

	thumb_func_start MOD08_0221273C
MOD08_0221273C: ; 0x0221273C
	ldr r1, [r0, #0x18]
	mov r3, #0
	add r1, r1, #4
	str r1, [r0, #0x18]
	add r2, r3, #0
_02212746:
	add r1, r0, #0
	add r1, #0x94
	add r3, r3, #1
	add r0, r0, #4
	str r2, [r1]
	cmp r3, #0xa
	blt _02212746
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02212758
MOD08_02212758: ; 0x02212758
	cmp r1, #5
	bhi _022127A4
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02212768: ; jump table
	.short _02212774 - _02212768 - 2 ; case 0
	.short _0221277C - _02212768 - 2 ; case 1
	.short _02212784 - _02212768 - 2 ; case 2
	.short _0221278C - _02212768 - 2 ; case 3
	.short _02212794 - _02212768 - 2 ; case 4
	.short _0221279C - _02212768 - 2 ; case 5
_02212774:
	add r0, #0xc0
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bx lr
_0221277C:
	add r0, #0xc0
	ldr r0, [r0]
	ldrh r0, [r0, #8]
	bx lr
_02212784:
	add r0, #0xc0
	ldr r0, [r0]
	ldrh r0, [r0, #0xa]
	bx lr
_0221278C:
	add r0, #0xc0
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bx lr
_02212794:
	add r0, #0xc0
	ldr r0, [r0]
	ldrh r0, [r0, #0x10]
	bx lr
_0221279C:
	add r0, #0xc0
	ldr r0, [r0]
	ldrh r0, [r0, #0x12]
	bx lr
_022127A4:
	mov r0, #0
	bx lr

	thumb_func_start MOD08_022127A8
MOD08_022127A8: ; 0x022127A8
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	add r3, r0, #0
	add r0, r1, #0
	str r2, [sp]
	add r6, r4, #0
	add r5, r0, #0
	mov ip, r4
	add r7, r0, #0
_022127BA:
	add r1, r3, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r1, r1, r6
	add r1, #0xb0
	ldr r1, [r1]
	str r1, [r5, #8]
	add r1, r3, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r1, r1, r6
	add r1, #0xc4
	ldr r1, [r1]
	str r1, [r5, #0x18]
	add r1, r3, #0
	add r1, #0xc0
	ldr r2, [r1]
	mov r1, ip
	add r1, r2, r1
	add r1, #0xd8
	ldrh r1, [r1]
	add r2, r0, r4
	add r2, #0x30
	strh r1, [r7, #0x28]
	add r1, r3, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r7, r7, #2
	add r1, r1, r4
	add r1, #0xe0
	ldrb r1, [r1]
	strb r1, [r2]
	add r1, r3, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r2, r0, r4
	add r1, r1, r4
	add r1, #0xe4
	ldrb r1, [r1]
	add r2, #0x34
	strb r1, [r2]
	add r1, r3, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r2, r0, r4
	add r1, r1, r4
	add r1, #0xe8
	ldrb r1, [r1]
	add r2, #0x38
	strb r1, [r2]
	add r1, r3, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r2, r0, r4
	add r1, r1, r6
	add r1, #0xec
	ldr r1, [r1]
	add r2, #0x4c
	str r1, [r5, #0x3c]
	add r1, r3, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r6, r6, #4
	add r1, r1, r4
	add r1, #0xc0
	ldrb r1, [r1]
	add r4, r4, #1
	add r5, r5, #4
	strb r1, [r2]
	mov r1, ip
	add r1, r1, #2
	mov ip, r1
	cmp r4, #4
	blt _022127BA
	ldr r1, [sp]
	cmp r1, #3
	bhi _022128B8
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02212860: ; jump table
	.short _02212868 - _02212860 - 2 ; case 0
	.short _0221287C - _02212860 - 2 ; case 1
	.short _02212890 - _02212860 - 2 ; case 2
	.short _022128A4 - _02212860 - 2 ; case 3
_02212868:
	add r1, r3, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r3, #0xc0
	ldrh r1, [r1, #0x14]
	str r1, [r0]
	ldr r1, [r3]
	ldrh r1, [r1, #0x16]
	str r1, [r0, #4]
	pop {r3, r4, r5, r6, r7, pc}
_0221287C:
	add r1, r3, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r3, #0xc0
	ldrh r1, [r1, #0x14]
	str r1, [r0]
	ldr r1, [r3]
	ldrh r1, [r1, #0x14]
	str r1, [r0, #4]
	pop {r3, r4, r5, r6, r7, pc}
_02212890:
	add r1, r3, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r3, #0xc0
	ldrh r1, [r1, #0x14]
	str r1, [r0]
	ldr r1, [r3]
	ldrh r1, [r1, #0x14]
	str r1, [r0, #4]
	pop {r3, r4, r5, r6, r7, pc}
_022128A4:
	add r1, r3, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r3, #0xc0
	ldrh r1, [r1, #0x14]
	str r1, [r0]
	ldr r1, [r3]
	ldrh r1, [r1, #0x14]
	str r1, [r0, #4]
	pop {r3, r4, r5, r6, r7, pc}
_022128B8:
	bl ErrorHandling
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_022128C0
MOD08_022128C0: ; 0x022128C0
	push {r3, r4, r5, lr}
	sub sp, #0x50
	add r5, r0, #0
	ldr r1, [r5, #0x18]
	add r1, r1, #4
	str r1, [r5, #0x18]
	ldr r4, [r1]
	add r1, r1, #4
	str r1, [r5, #0x18]
	add r1, sp, #0
	add r2, r4, #0
	bl MOD08_022127A8
	cmp r4, #2
	add r0, sp, #0
	bne _022128EA
	ldr r1, [r5]
	bl MOD08_0222A568
	add sp, #0x50
	pop {r3, r4, r5, pc}
_022128EA:
	cmp r4, #3
	bne _022128F8
	ldr r1, [r5]
	bl MOD08_0222A2A4
	add sp, #0x50
	pop {r3, r4, r5, pc}
_022128F8:
	ldr r1, [r5]
	bl MOD08_0222A294
	add sp, #0x50
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02212904
MOD08_02212904: ; 0x02212904
	push {r4, lr}
	sub sp, #0x50
	add r4, r0, #0
	ldr r1, [r4, #0x18]
	add r1, r1, #4
	str r1, [r4, #0x18]
	ldr r2, [r1]
	add r1, r1, #4
	str r1, [r4, #0x18]
	add r1, sp, #0
	bl MOD08_022127A8
	ldr r1, [r4]
	add r0, sp, #0
	bl MOD08_0222A494
	add sp, #0x50
	pop {r4, pc}

	thumb_func_start MOD08_02212928
MOD08_02212928: ; 0x02212928
	ldr r1, [r0, #0x18]
	mov r2, #0
	add r1, r1, #4
	str r1, [r0, #0x18]
	add r3, r0, #0
_02212932:
	ldr r1, [r3, #0x30]
	cmp r1, #1
	beq _0221295E
	mov r1, #0xc
	mul r1, r2
	mov r2, #1
	add r1, r0, r1
	str r2, [r1, #0x30]
	add r2, r1, #0
	mov r3, #0
	add r2, #0x2c
	strb r3, [r2]
	ldr r2, [r0, #0x18]
	ldr r3, [r2]
	add r2, r1, #0
	add r2, #0x2d
	strb r3, [r2]
	ldr r2, [r0, #0x18]
	add r2, r2, #4
	str r2, [r0, #0x18]
	str r2, [r1, #0x28]
	bx lr
_0221295E:
	add r2, r2, #1
	add r3, #0xc
	cmp r2, #3
	blt _02212932
	bx lr

	thumb_func_start MOD08_02212968
MOD08_02212968: ; 0x02212968
	push {r3, r4}
	ldr r1, [r0, #0x18]
	add r3, r0, #0
	add r1, r1, #4
	add r3, #0x18
	str r1, [r0, #0x18]
	mov r2, #2
_02212976:
	ldr r1, [r3, #0x30]
	cmp r1, #0
	beq _022129AA
	add r4, r2, #0
	mov r1, #0xc
	add r2, r0, #0
	mul r4, r1
	add r2, #0x2c
	ldrb r1, [r2, r4]
	add r1, r1, #1
	strb r1, [r2, r4]
	ldrb r3, [r2, r4]
	add r2, r0, r4
	add r1, r2, #0
	add r1, #0x2d
	ldrb r1, [r1]
	cmp r3, r1
	bne _022129A2
	mov r0, #0
	str r0, [r2, #0x30]
	pop {r3, r4}
	bx lr
_022129A2:
	ldr r1, [r2, #0x28]
	str r1, [r0, #0x18]
	pop {r3, r4}
	bx lr
_022129AA:
	sub r3, #0xc
	sub r2, r2, #1
	bpl _02212976
	pop {r3, r4}
	bx lr

	thumb_func_start MOD08_022129B4
MOD08_022129B4: ; 0x022129B4
	push {r3, r4, r5, r6, r7, lr}
	ldr r1, _02212BB0 ; =0x0000017E
	add r5, r0, #0
	ldrb r0, [r5, r1]
	mov r6, #0
	cmp r0, #1
	bhs _022129D2
	add r0, r5, #0
	mov r2, #1
	add r0, #0x8d
	strb r2, [r0]
	ldrb r0, [r5, r1]
	add r0, r0, #1
	strb r0, [r5, r1]
	pop {r3, r4, r5, r6, r7, pc}
_022129D2:
	add r7, r6, #0
	add r4, r6, #0
_022129D6:
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r0, r0, r4
	ldr r0, [r0, #0x1c]
	cmp r0, #0
	beq _022129EA
	bl FUN_020133C8
	add r6, r6, r0
_022129EA:
	add r7, r7, #1
	add r4, r4, #4
	cmp r7, #0x10
	blt _022129D6
	cmp r6, #0
	bne _02212A0A
	add r0, r5, #0
	add r0, #0x8e
	ldrh r0, [r0]
	cmp r0, #0
	bne _02212A0A
	add r0, r5, #0
	add r0, #0x90
	ldrh r0, [r0]
	cmp r0, #0
	beq _02212A1A
_02212A0A:
	add r0, r5, #0
	mov r1, #1
	add r0, #0x8d
	strb r1, [r0]
	ldr r0, _02212BB4 ; =0x0000017D
	mov r1, #0
	strb r1, [r5, r0]
	pop {r3, r4, r5, r6, r7, pc}
_02212A1A:
	bl FUN_02005514
	cmp r0, #0
	beq _02212A44
	ldr r0, _02212BB4 ; =0x0000017D
	ldrb r1, [r5, r0]
	add r1, r1, #1
	strb r1, [r5, r0]
	ldrb r1, [r5, r0]
	cmp r1, #0x5a
	bls _02212A3C
	mov r1, #0
	strb r1, [r5, r0]
	add r0, r5, #0
	add r0, #0x8d
	strb r1, [r0]
	b _02212A44
_02212A3C:
	mov r0, #1
	add r5, #0x8d
	strb r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_02212A44:
	ldr r0, _02212BB4 ; =0x0000017D
	mov r1, #0
	strb r1, [r5, r0]
	add r0, r0, #1
	strb r1, [r5, r0]
	add r0, r5, #0
	add r2, r1, #0
_02212A52:
	add r1, r1, #1
	str r2, [r0, #0x1c]
	add r0, r0, #4
	cmp r1, #3
	blt _02212A52
	add r1, r5, #0
	mov r4, #0
_02212A60:
	add r0, r1, #0
	str r4, [r1, #0x28]
	add r0, #0x2c
	strb r4, [r0]
	add r0, r1, #0
	add r0, #0x2d
	strb r4, [r0]
	str r4, [r1, #0x30]
	add r2, r2, #1
	add r1, #0xc
	cmp r2, #3
	blt _02212A60
	add r7, r5, #0
	mov r6, #0
_02212A7C:
	add r0, r7, #0
	add r0, #0xcc
	ldr r1, [r0]
	cmp r1, #0
	beq _02212A94
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r0, #0xac
	ldr r0, [r0]
	bl FUN_0200C398
_02212A94:
	add r0, r7, #0
	add r0, #0xcc
	add r4, r4, #1
	add r7, r7, #4
	str r6, [r0]
	cmp r4, #4
	blt _02212A7C
_02212AA2:
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02213454
	add r6, r6, #1
	cmp r6, #5
	blt _02212AA2
	mov r6, #0
	add r4, r6, #0
	add r7, r6, #0
_02212AB6:
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r0, r0, r4
	ldr r0, [r0, #0x1c]
	cmp r0, #0
	beq _02212AD2
	bl MOD08_02215B40
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r0, r0, r4
	str r7, [r0, #0x1c]
_02212AD2:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #0x10
	blt _02212AB6
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	cmp r1, #0
	beq _02212AE8
	mov r1, #0
	str r1, [r5, r0]
_02212AE8:
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #0
	bne _02212B3C
	bl MOD11_02231678
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02215588
	add r4, r0, #0
	add r0, r5, #0
	bl MOD08_02212014
	add r3, r0, #0
	lsl r0, r4, #0x18
	mov r1, #1
	lsr r0, r0, #0x18
	lsl r1, r1, #0xe
	mov r2, #0
	bl FUN_02017F18
	add r0, r5, #0
	bl MOD08_02212490
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02215588
	add r1, r0, #0
	lsl r1, r1, #0x18
	add r0, r4, #0
	lsr r1, r1, #0x18
	bl FUN_02018744
	mov r0, #2
	mov r1, #1
	bl FUN_0201797C
	b _02212B40
_02212B3C:
	bl MOD12_02233560
_02212B40:
	mov r1, #0x1a
	lsl r1, r1, #4
	ldrb r1, [r5, r1]
	mov r0, #0
	bl FUN_020178BC
	ldr r1, _02212BB8 ; =0x000001A1
	mov r0, #1
	ldrb r1, [r5, r1]
	bl FUN_020178BC
	ldr r1, _02212BBC ; =0x000001A2
	mov r0, #2
	ldrb r1, [r5, r1]
	bl FUN_020178BC
	ldr r1, _02212BC0 ; =0x000001A3
	mov r0, #3
	ldrb r1, [r5, r1]
	bl FUN_020178BC
	add r0, r5, #0
	add r0, #0xc4
	mov r2, #0
	ldr r0, [r0]
	mov r1, #2
	add r3, r2, #0
	bl FUN_020179E0
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #2
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	add r0, r5, #0
	add r0, #0xc4
	mov r2, #0
	ldr r0, [r0]
	mov r1, #3
	add r3, r2, #0
	bl FUN_020179E0
	add r0, r5, #0
	add r0, #0xc4
	mov r1, #3
	ldr r0, [r0]
	add r2, r1, #0
	mov r3, #0
	bl FUN_020179E0
	mov r0, #0
	str r0, [r5, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02212BB0: .word 0x0000017E
_02212BB4: .word 0x0000017D
_02212BB8: .word 0x000001A1
_02212BBC: .word 0x000001A2
_02212BC0: .word 0x000001A3

	thumb_func_start MOD08_02212BC4
MOD08_02212BC4: ; 0x02212BC4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r4, [r0]
	add r1, r0, #4
	str r1, [r5, #0x18]
	ldr r0, [r1]
	str r0, [sp]
	add r0, r1, #4
	str r0, [r5, #0x18]
	ldr r7, [r0]
	add r0, r0, #4
	str r0, [r5, #0x18]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	str r4, [r0, #0x18]
	add r0, r5, r4
	add r0, #0x7c
	ldrb r0, [r0]
	cmp r0, #0
	beq _02212C22
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	lsl r6, r4, #2
	add r0, r0, r6
	ldr r0, [r0, #0x1c]
	add r1, sp, #4
	bl FUN_020133EC
	mov r0, #0
	ldr r1, [sp, #8]
	mvn r0, r0
	mul r0, r1
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r1, sp, #4
	add r0, r0, r6
	ldr r0, [r0, #0x1c]
	bl FUN_020133FC
_02212C22:
	add r0, r5, #0
	add r0, #0xc0
	add r1, r5, r4
	add r1, #0x6c
	ldr r0, [r0]
	lsl r6, r4, #2
	add r0, r0, r6
	ldrb r1, [r1]
	ldr r0, [r0, #0x1c]
	bl FUN_02013440
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, [sp]
	add r0, r0, r6
	ldr r0, [r0, #0x1c]
	add r2, r7, #0
	add r3, r5, #0
	bl MOD08_02215B2C
	add r5, #0xc0
	ldr r1, [r5]
	str r0, [r1, #0x5c]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02212C58
MOD08_02212C58: ; 0x02212C58
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r4, [r0]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r7, [r0]
	add r1, r0, #4
	str r1, [r5, #0x18]
	ldr r0, [r1]
	add r1, r1, #4
	str r1, [r5, #0x18]
	str r0, [sp, #4]
	ldr r0, [r1]
	str r0, [sp]
	add r0, r1, #4
	str r0, [r5, #0x18]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	str r4, [r0, #0x18]
	add r0, r5, r4
	add r0, #0x7c
	ldrb r0, [r0]
	cmp r0, #0
	beq _02212CBE
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	lsl r6, r4, #2
	add r0, r0, r6
	ldr r0, [r0, #0x1c]
	add r1, sp, #8
	bl FUN_020133EC
	mov r0, #0
	ldr r1, [sp, #0xc]
	mvn r0, r0
	mul r0, r1
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r1, sp, #8
	add r0, r0, r6
	ldr r0, [r0, #0x1c]
	bl FUN_020133FC
_02212CBE:
	add r0, r5, #0
	add r0, #0xc0
	add r1, r5, r4
	add r1, #0x6c
	ldr r0, [r0]
	lsl r6, r4, #2
	add r0, r0, r6
	ldrb r1, [r1]
	ldr r0, [r0, #0x1c]
	bl FUN_02013440
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, [sp, #4]
	add r0, r0, r6
	ldr r0, [r0, #0x1c]
	ldr r2, [sp]
	add r3, r5, #0
	bl MOD08_02215B2C
	add r5, #0xc0
	ldr r2, [r5]
	lsl r1, r7, #2
	add r1, r2, r1
	str r0, [r1, #0x5c]
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02212CF8
MOD08_02212CF8: ; 0x02212CF8
	push {r4, r5, r6, lr}
	sub sp, #0x90
	ldr r5, _02212D4C ; =0x0222AB4C
	add r4, r0, #0
	add r3, sp, #0
	mov r2, #0x12
_02212D04:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02212D04
	add r0, r4, #0
	bl MOD08_02212458
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02212460
	add r6, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	bl MOD08_02227468
	mov r1, #0x18
	add r3, r5, #0
	mul r3, r1
	add r2, sp, #0
	lsl r1, r0, #2
	add r0, r2, r3
	ldr r4, [r1, r0]
	cmp r4, #0xff
	bne _02212D44
	bl ErrorHandling
_02212D44:
	sub r0, r4, #1
	add sp, #0x90
	pop {r4, r5, r6, pc}
	nop
_02212D4C: .word MOD8_0222AB4C

	thumb_func_start MOD08_02212D50
MOD08_02212D50: ; 0x02212D50
	push {r4, r5, r6, lr}
	sub sp, #0x90
	ldr r5, _02212DA4 ; =0x0222ABDC
	add r4, r0, #0
	add r3, sp, #0
	mov r2, #0x12
_02212D5C:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02212D5C
	add r0, r4, #0
	bl MOD08_02212458
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02212460
	add r6, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	bl MOD08_02227468
	mov r1, #0x18
	add r3, r5, #0
	mul r3, r1
	add r2, sp, #0
	lsl r1, r0, #2
	add r0, r2, r3
	ldr r4, [r1, r0]
	cmp r4, #0xff
	bne _02212D9C
	bl ErrorHandling
_02212D9C:
	add r0, r4, #0
	add sp, #0x90
	pop {r4, r5, r6, pc}
	nop
_02212DA4: .word MOD8_0222ABDC

	thumb_func_start MOD08_02212DA8
MOD08_02212DA8: ; 0x02212DA8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r5, r0, #0
	ldr r1, [r5, #0x18]
	add r0, #0x18
	add r1, r1, #4
	str r1, [r5, #0x18]
	ldr r4, [r1]
	add r1, r1, #4
	str r1, [r5, #0x18]
	mov r1, #0
	add r2, sp, #0x10
_02212DC0:
	ldr r3, [r5, #0x18]
	add r1, r1, #1
	ldr r3, [r3]
	str r3, [r2]
	ldr r3, [r0]
	add r2, r2, #4
	add r3, r3, #4
	str r3, [r0]
	cmp r1, #6
	blt _02212DC0
	ldr r1, [r5, #0x18]
	ldr r1, [r1]
	str r1, [sp]
	ldr r1, [r0]
	add r1, r1, #4
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	str r4, [r0, #0x18]
	add r0, r5, r4
	add r0, #0x7c
	ldrb r0, [r0]
	cmp r0, #0
	beq _02212E1E
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	lsl r6, r4, #2
	add r0, r0, r6
	ldr r0, [r0, #0x1c]
	add r1, sp, #4
	bl FUN_020133EC
	mov r0, #0
	ldr r1, [sp, #8]
	mvn r0, r0
	mul r0, r1
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r1, sp, #4
	add r0, r0, r6
	ldr r0, [r0, #0x1c]
	bl FUN_020133FC
_02212E1E:
	add r0, r5, #0
	bl MOD08_02212CF8
	add r7, r0, #0
	add r0, r5, #0
	add r0, #0xc0
	add r1, r5, r4
	add r1, #0x6c
	ldr r0, [r0]
	lsl r6, r4, #2
	add r0, r0, r6
	ldrb r1, [r1]
	ldr r0, [r0, #0x1c]
	bl FUN_02013440
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	lsl r2, r7, #2
	add r0, r0, r6
	add r1, sp, #0x10
	ldr r1, [r1, r2]
	ldr r0, [r0, #0x1c]
	ldr r2, [sp]
	add r3, r5, #0
	bl MOD08_02215B2C
	add r5, #0xc0
	ldr r1, [r5]
	str r0, [r1, #0x5c]
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02212E60
MOD08_02212E60: ; 0x02212E60
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	ldr r1, [r5, #0x18]
	add r0, #0x18
	add r1, r1, #4
	str r1, [r5, #0x18]
	ldr r4, [r1]
	add r1, r1, #4
	str r1, [r5, #0x18]
	mov r1, #0
	add r2, sp, #0x10
_02212E78:
	ldr r3, [r5, #0x18]
	add r1, r1, #1
	ldr r3, [r3]
	str r3, [r2]
	ldr r3, [r0]
	add r2, r2, #4
	add r3, r3, #4
	str r3, [r0]
	cmp r1, #4
	blt _02212E78
	ldr r1, [r5, #0x18]
	ldr r1, [r1]
	str r1, [sp]
	ldr r1, [r0]
	add r1, r1, #4
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	str r4, [r0, #0x18]
	add r0, r5, r4
	add r0, #0x7c
	ldrb r0, [r0]
	cmp r0, #0
	beq _02212ED6
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	lsl r6, r4, #2
	add r0, r0, r6
	ldr r0, [r0, #0x1c]
	add r1, sp, #4
	bl FUN_020133EC
	mov r0, #0
	ldr r1, [sp, #8]
	mvn r0, r0
	mul r0, r1
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r1, sp, #4
	add r0, r0, r6
	ldr r0, [r0, #0x1c]
	bl FUN_020133FC
_02212ED6:
	add r0, r5, #0
	bl MOD08_02212D50
	add r7, r0, #0
	add r0, r5, #0
	add r0, #0xc0
	add r1, r5, r4
	add r1, #0x6c
	ldr r0, [r0]
	lsl r6, r4, #2
	add r0, r0, r6
	ldrb r1, [r1]
	ldr r0, [r0, #0x1c]
	bl FUN_02013440
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	lsl r2, r7, #2
	add r0, r0, r6
	add r1, sp, #0x10
	ldr r1, [r1, r2]
	ldr r0, [r0, #0x1c]
	ldr r2, [sp]
	add r3, r5, #0
	bl MOD08_02215B2C
	add r5, #0xc0
	ldr r1, [r5]
	str r0, [r1, #0x5c]
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02212F18
MOD08_02212F18: ; 0x02212F18
	push {r3, r4, r5, r6, r7, lr}
	mov r6, #0
	add r5, r0, #0
	add r7, r6, #0
	add r4, r6, #0
_02212F22:
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r0, r0, r4
	ldr r0, [r0, #0x1c]
	cmp r0, #0
	beq _02212F36
	bl FUN_020133C8
	add r6, r6, r0
_02212F36:
	add r7, r7, #1
	add r4, r4, #4
	cmp r7, #0x10
	blt _02212F22
	cmp r6, #0
	bne _02212F50
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	mov r0, #0
	add r5, #0x8d
	strb r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_02212F50:
	mov r0, #1
	add r5, #0x8d
	strb r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02212F58
MOD08_02212F58: ; 0x02212F58
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r1, [r0]
	add r0, r0, #4
	str r0, [r5, #0x18]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	lsl r4, r1, #2
	add r0, r0, r4
	ldr r0, [r0, #0x1c]
	cmp r0, #0
	beq _02212F7C
	bl ErrorHandling
_02212F7C:
	ldr r0, [r5, #0x18]
	mov r2, #0
	ldr r1, [r0]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r5]
	bl MOD08_02215AA4
	add r1, r5, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r1, r1, r4
	str r0, [r1, #0x1c]
	add r0, r5, #0
	mov r1, #2
	add r0, #0x8d
	strb r1, [r0]
	ldr r0, _02212FA8 ; =MOD08_02211EA0
	add r5, #0xbc
	str r0, [r5]
	pop {r3, r4, r5, pc}
	nop
_02212FA8: .word MOD08_02211EA0

	thumb_func_start MOD08_02212FAC
MOD08_02212FAC: ; 0x02212FAC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r1, [r0]
	add r0, r0, #4
	add r0, r0, #4
	str r0, [r5, #0x18]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	lsl r4, r1, #2
	add r0, r0, r4
	ldr r0, [r0, #0x1c]
	cmp r0, #0
	beq _02212FD2
	bl ErrorHandling
_02212FD2:
	ldr r0, [r5, #0x18]
	mov r1, #0x64
	ldr r2, [r0]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r5]
	mov r3, #0
	bl MOD08_02215ACC
	add r1, r5, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r1, r1, r4
	str r0, [r1, #0x1c]
	add r0, r5, #0
	mov r1, #2
	add r0, #0x8d
	strb r1, [r0]
	ldr r0, _02213000 ; =MOD08_02211EA0
	add r5, #0xbc
	str r0, [r5]
	pop {r3, r4, r5, pc}
	nop
_02213000: .word MOD08_02211EA0

	thumb_func_start MOD08_02213004
MOD08_02213004: ; 0x02213004
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r1, [r0]
	add r0, r0, #4
	str r0, [r5, #0x18]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	lsl r4, r1, #2
	add r0, r0, r4
	ldr r0, [r0, #0x1c]
	bl MOD08_02215B40
	add r5, #0xc0
	ldr r0, [r5]
	mov r1, #0
	add r0, r0, r4
	str r1, [r0, #0x1c]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02213030
MOD08_02213030: ; 0x02213030
	ldr r1, [r0, #0x18]
	mov r3, #0
	add r1, r1, #4
	str r1, [r0, #0x18]
	add r2, r0, #0
_0221303A:
	ldr r1, [r2, #0x1c]
	cmp r1, #0
	bne _02213056
	ldr r1, [r0, #0x18]
	add r2, r1, #4
	lsl r1, r3, #2
	add r1, r0, r1
	str r2, [r1, #0x1c]
	ldr r2, [r0, #0x18]
	ldr r1, [r2]
	lsl r1, r1, #2
	add r1, r2, r1
	str r1, [r0, #0x18]
	bx lr
_02213056:
	add r3, r3, #1
	add r2, r2, #4
	cmp r3, #3
	blt _0221303A
	bx lr

	thumb_func_start MOD08_02213060
MOD08_02213060: ; 0x02213060
	ldr r1, [r0, #0x18]
	add r3, r0, #0
	add r1, r1, #4
	str r1, [r0, #0x18]
	mov r2, #2
	add r3, #8
_0221306C:
	ldr r1, [r3, #0x1c]
	cmp r1, #0
	beq _02213082
	add r3, r0, #0
	add r3, #0x1c
	lsl r2, r2, #2
	ldr r1, [r3, r2]
	str r1, [r0, #0x18]
	mov r0, #0
	str r0, [r3, r2]
	bx lr
_02213082:
	sub r3, r3, #4
	sub r2, r2, #1
	bpl _0221306C
	bx lr
	.align 2, 0

	thumb_func_start MOD08_0221308C
MOD08_0221308C: ; 0x0221308C
	push {r3, r4}
	ldr r2, [r0, #0x18]
	add r1, r0, #0
	add r2, r2, #4
	str r2, [r0, #0x18]
	ldr r4, [r2]
	add r2, r2, #4
	str r2, [r0, #0x18]
	ldr r3, [r2]
	add r2, r2, #4
	str r2, [r0, #0x18]
	lsl r2, r4, #2
	add r2, r0, r2
	add r2, #0x94
	ldr r2, [r2]
	add r1, #0x18
	cmp r3, r2
	bne _022130BA
	ldr r1, [r0, #0x18]
	ldr r1, [r1]
	str r1, [r0, #0x18]
	pop {r3, r4}
	bx lr
_022130BA:
	ldr r0, [r1]
	add r0, r0, #4
	str r0, [r1]
	pop {r3, r4}
	bx lr

	thumb_func_start MOD08_022130C4
MOD08_022130C4: ; 0x022130C4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	add r0, r0, #4
	str r0, [r4, #0x18]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	bl MOD08_02215350
	cmp r0, #0
	ldr r0, [r4, #0x18]
	beq _022130E4
	ldr r0, [r0]
	str r0, [r4, #0x18]
	pop {r4, pc}
_022130E4:
	add r0, r0, #4
	str r0, [r4, #0x18]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_022130EC
MOD08_022130EC: ; 0x022130EC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	add r1, r0, #4
	str r1, [r4, #0x18]
	ldr r0, [r1]
	add r1, r1, #4
	str r1, [r4, #0x18]
	bl MOD08_02218C48
	add r7, r0, #0
	ldr r0, [r4, #0x18]
	add r2, r4, #0
	ldr r5, [r0]
	add r0, r0, #4
	add r2, #0x18
	mov r3, #0
	str r0, [r4, #0x18]
	cmp r5, #0
	bls _0221312E
	add r6, r4, #0
_02213116:
	ldr r0, [r4, #0x18]
	add r3, r3, #1
	ldr r1, [r0]
	add r0, r6, #0
	add r0, #0x94
	str r1, [r0]
	ldr r0, [r2]
	add r6, r6, #4
	add r0, r0, #4
	str r0, [r2]
	cmp r3, r5
	blo _02213116
_0221312E:
	cmp r3, #0xa
	bge _02213146
	lsl r0, r3, #2
	add r2, r4, r0
	mov r1, #0
_02213138:
	add r0, r2, #0
	add r0, #0x94
	add r3, r3, #1
	add r2, r2, #4
	str r1, [r0]
	cmp r3, #0xa
	blt _02213138
_02213146:
	add r0, r4, #0
	blx r7
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_0221314C
MOD08_0221314C: ; 0x0221314C
	ldr r2, [r0, #0x18]
	add r1, r0, #0
	add r2, r2, #4
	str r2, [r0, #0x18]
	add r2, r0, #0
	add r2, #0xc0
	ldr r2, [r2]
	add r1, #0x18
	ldrh r3, [r2, #0x10]
	mov r2, #1
	tst r2, r3
	beq _0221316A
	ldr r2, [r1]
	add r2, r2, #4
	str r2, [r1]
_0221316A:
	ldr r2, [r0, #0x18]
	ldr r1, [r2]
	lsl r1, r1, #2
	add r1, r2, r1
	str r1, [r0, #0x18]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02213178
MOD08_02213178: ; 0x02213178
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x18]
	add r1, r1, #4
	str r1, [r4, #0x18]
	ldr r2, [r1]
	add r1, r1, #4
	str r1, [r4, #0x18]
	cmp r2, #0
	bne _0221319A
	add r1, r4, #0
	add r1, #0xc0
	ldr r1, [r1]
	ldrh r1, [r1, #0x14]
	bl MOD08_02227470
	b _022131A6
_0221319A:
	add r1, r4, #0
	add r1, #0xc0
	ldr r1, [r1]
	ldrh r1, [r1, #0x16]
	bl MOD08_02227470
_022131A6:
	cmp r0, #4
	bne _022131B0
	ldr r0, [r4, #0x18]
	add r0, r0, #4
	str r0, [r4, #0x18]
_022131B0:
	ldr r1, [r4, #0x18]
	ldr r0, [r1]
	lsl r0, r0, #2
	add r0, r1, r0
	str r0, [r4, #0x18]
	pop {r4, pc}

	thumb_func_start MOD08_022131BC
MOD08_022131BC: ; 0x022131BC
	push {r4, r5}
	sub sp, #0x10
	ldr r5, _02213214 ; =0x0222AA3C
	add r2, sp, #0
	add r4, r0, #0
	add r3, r2, #0
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r1, [r4, #0x18]
	add r0, r4, #0
	add r1, r1, #4
	str r1, [r4, #0x18]
	add r1, r4, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r0, #0x18
	ldr r1, [r1, #0xc]
	cmp r1, #0
	beq _02213202
	ldr r2, [r0]
	add r2, r2, #4
	str r2, [r0]
	mov r2, #0
_022131EE:
	ldr r5, [r3]
	tst r5, r1
	bne _02213202
	ldr r5, [r0]
	add r2, r2, #1
	add r5, r5, #4
	add r3, r3, #4
	str r5, [r0]
	cmp r2, #4
	blo _022131EE
_02213202:
	ldr r1, [r4, #0x18]
	ldr r0, [r1]
	lsl r0, r0, #2
	add r0, r1, r0
	str r0, [r4, #0x18]
	add sp, #0x10
	pop {r4, r5}
	bx lr
	nop
_02213214: .word MOD8_0222AA3C

	thumb_func_start MOD08_02213218
MOD08_02213218: ; 0x02213218
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x18]
	add r1, r1, #4
	str r1, [r4, #0x18]
	bl MOD08_02212004
	cmp r0, #1
	bne _02213236
	ldr r1, [r4, #0x18]
	ldr r0, [r1]
	lsl r0, r0, #2
	add r0, r1, r0
	str r0, [r4, #0x18]
	pop {r4, pc}
_02213236:
	ldr r0, [r4, #0x18]
	add r0, r0, #4
	str r0, [r4, #0x18]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02213240
MOD08_02213240: ; 0x02213240
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r1, [r5, #0x18]
	add r1, r1, #4
	str r1, [r5, #0x18]
	add r1, r5, #0
	add r1, #0xc0
	ldr r1, [r1]
	ldrh r1, [r1, #0x14]
	bl MOD08_02227470
	add r1, r5, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r4, r0, #0
	ldrh r1, [r1, #0x16]
	add r0, r5, #0
	bl MOD08_02227470
	cmp r4, r0
	bne _02213276
	ldr r1, [r5, #0x18]
	ldr r0, [r1]
	lsl r0, r0, #2
	add r0, r1, r0
	str r0, [r5, #0x18]
	pop {r3, r4, r5, pc}
_02213276:
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02213280
MOD08_02213280: ; 0x02213280
	ldr r2, [r0, #0x18]
	add r1, r0, #0
	add r2, r2, #4
	str r2, [r0, #0x18]
	ldr r3, [r2]
	add r2, r2, #4
	str r2, [r0, #0x18]
	add r2, r0, #0
	add r2, #0xc0
	ldr r2, [r2]
	add r1, #0x18
	ldrh r2, [r2, #0x10]
	cmp r3, r2
	bne _022132AA
	ldr r0, [r0, #0x18]
	ldr r2, [r1]
	ldr r0, [r0]
	lsl r0, r0, #2
	add r0, r2, r0
	str r0, [r1]
	bx lr
_022132AA:
	ldr r0, [r1]
	add r0, r0, #4
	str r0, [r1]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_022132B4
MOD08_022132B4: ; 0x022132B4
	ldr r1, [r0, #0x18]
	add r2, r1, #4
	str r2, [r0, #0x18]
	ldr r1, [r2]
	lsl r1, r1, #2
	add r1, r2, r1
	str r1, [r0, #0x18]
	bx lr

	thumb_func_start MOD08_022132C4
MOD08_022132C4: ; 0x022132C4
	push {r4, r5, r6, lr}
	add r4, r0, #0
	cmp r1, #7
	bhi _022133A2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022132D8: ; jump table
	.short _022132E8 - _022132D8 - 2 ; case 0
	.short _022132F0 - _022132D8 - 2 ; case 1
	.short _022132F8 - _022132D8 - 2 ; case 2
	.short _02213306 - _022132D8 - 2 ; case 3
	.short _02213314 - _022132D8 - 2 ; case 4
	.short _0221333A - _022132D8 - 2 ; case 5
	.short _02213360 - _022132D8 - 2 ; case 6
	.short _02213382 - _022132D8 - 2 ; case 7
_022132E8:
	add r4, #0xc0
	ldr r0, [r4]
	ldrh r6, [r0, #0x14]
	b _022133A2
_022132F0:
	add r4, #0xc0
	ldr r0, [r4]
	ldrh r6, [r0, #0x16]
	b _022133A2
_022132F8:
	add r4, #0xc0
	ldr r1, [r4]
	ldrh r1, [r1, #0x14]
	bl MOD08_022274C0
	add r6, r0, #0
	b _022133A2
_02213306:
	add r4, #0xc0
	ldr r1, [r4]
	ldrh r1, [r1, #0x16]
	bl MOD08_022274C0
	add r6, r0, #0
	b _022133A2
_02213314:
	mov r6, #0xff
	mov r5, #0
_02213318:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02215490
	cmp r0, #0
	beq _02213328
	cmp r0, #2
	bne _0221332C
_02213328:
	add r6, r5, #0
	b _02213332
_0221332C:
	add r5, r5, #1
	cmp r5, #4
	blt _02213318
_02213332:
	cmp r6, #0xff
	bne _022133A2
	mov r6, #0
	b _022133A2
_0221333A:
	mov r6, #0xff
	mov r5, #0
_0221333E:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02215490
	cmp r0, #1
	beq _0221334E
	cmp r0, #3
	bne _02213352
_0221334E:
	add r6, r5, #0
	b _02213358
_02213352:
	add r5, r5, #1
	cmp r5, #4
	blt _0221333E
_02213358:
	cmp r6, #0xff
	bne _022133A2
	mov r6, #0
	b _022133A2
_02213360:
	mov r6, #0xff
	mov r5, #0
_02213364:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02215490
	cmp r0, #4
	bne _02213374
	add r6, r5, #0
	b _0221337A
_02213374:
	add r5, r5, #1
	cmp r5, #4
	blt _02213364
_0221337A:
	cmp r6, #0xff
	bne _022133A2
	mov r6, #0
	b _022133A2
_02213382:
	mov r6, #0xff
	mov r5, #0
_02213386:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02215490
	cmp r0, #5
	bne _02213396
	add r6, r5, #0
	b _0221339C
_02213396:
	add r5, r5, #1
	cmp r5, #4
	blt _02213386
_0221339C:
	cmp r6, #0xff
	bne _022133A2
	mov r6, #0
_022133A2:
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_022133A8
MOD08_022133A8: ; 0x022133A8
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldrb r0, [r5, #5]
	cmp r0, #0
	beq _022133C4
	ldrb r0, [r5, #4]
	add r0, r0, #1
	strb r0, [r5, #4]
	ldrb r1, [r5, #4]
	ldrb r0, [r5, #5]
	cmp r1, r0
	bne _022133F2
	mov r0, #0
	strb r0, [r5, #4]
_022133C4:
	ldr r0, [r5, #8]
	mov r1, #0
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	ldr r0, [r5, #8]
	mov r1, #1
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	ldr r0, [r5, #8]
	mov r1, #0x29
	bl FUN_0200782C
	sub r0, r4, r0
	lsl r0, r0, #0x10
	asr r2, r0, #0x10
	ldr r0, [r5]
	add r1, r6, #0
	bl FUN_0200C714
_022133F2:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_022133F4
MOD08_022133F4: ; 0x022133F4
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldrb r0, [r5, #5]
	cmp r0, #0
	beq _02213410
	ldrb r0, [r5, #4]
	add r0, r0, #1
	strb r0, [r5, #4]
	ldrb r1, [r5, #4]
	ldrb r0, [r5, #5]
	cmp r1, r0
	bne _02213452
	mov r0, #0
	strb r0, [r5, #4]
_02213410:
	ldr r0, [r5, #8]
	mov r1, #0
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	ldr r0, [r5, #8]
	mov r1, #1
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	ldr r0, [r5, #8]
	mov r1, #0x29
	bl FUN_0200782C
	sub r0, r4, r0
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	sub r6, #0x28
	ldr r0, [r5]
	mov r1, #2
	mov r2, #0
	neg r3, r6
	bl FUN_020179E0
	sub r4, #0x28
	ldr r0, [r5]
	mov r1, #2
	mov r2, #3
	neg r3, r4
	bl FUN_020179E0
_02213452:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_02213454
MOD08_02213454: ; 0x02213454
	push {r3, r4, r5, lr}
	add r4, r0, #0
	cmp r1, #4
	bne _02213480
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0221349E
	ldr r0, [r0, #0xc]
	bl FUN_0200CAB4
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FreeToHeap
	mov r0, #0x5e
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	pop {r3, r4, r5, pc}
_02213480:
	mov r0, #0x59
	lsl r0, r0, #2
	lsl r5, r1, #2
	add r4, r4, r0
	ldr r0, [r4, r5]
	cmp r0, #0
	beq _0221349E
	ldr r0, [r0, #0xc]
	bl FUN_0200CAB4
	ldr r0, [r4, r5]
	bl FreeToHeap
	mov r0, #0
	str r0, [r4, r5]
_0221349E:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_022134A0
MOD08_022134A0: ; 0x022134A0
	bx lr
	.align 2, 0

	thumb_func_start MOD08_022134A4
MOD08_022134A4: ; 0x022134A4
	bx lr
	.align 2, 0

	thumb_func_start MOD08_022134A8
MOD08_022134A8: ; 0x022134A8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	ldr r1, [r5, #0x18]
	add r2, r1, #4
	str r2, [r5, #0x18]
	ldr r1, [r2]
	add r2, r2, #4
	str r2, [r5, #0x18]
	ldr r4, [r2]
	add r2, r2, #4
	str r2, [r5, #0x18]
	bl MOD08_022132C4
	add r6, r0, #0
	add r0, r5, #0
	add r0, #0xc0
	ldr r1, [r0]
	lsl r0, r6, #2
	add r0, r1, r0
	add r0, #0xb0
	ldr r1, [r0]
	ldr r0, [r1, #4]
	str r0, [sp, #0x14]
	ldr r0, [r1, #8]
	str r0, [sp, #0x10]
	ldr r0, [r1]
	str r0, [sp, #0x18]
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _022134FE
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_022154A8
	bl MOD08_0222A6C8
	cmp r0, #1
	bne _022134FE
	mov r7, #0xc9
	b _02213500
_022134FE:
	mov r7, #0xc8
_02213500:
	mov r0, #2
	bl FUN_020187B0
	mov r2, #0x19
	mov r1, #0
	lsl r2, r2, #8
	bl MI_CpuFill8
	mov r0, #2
	mov r1, #0
	bl FUN_0201797C
	mov r0, #0
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xc4
	mov r3, #0x32
	ldr r0, [r0]
	ldr r2, [sp, #0x18]
	mov r1, #2
	lsl r3, r3, #6
	bl FUN_02017E14
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0x80
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xc8
	ldr r0, [r0]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	ldr r3, [r5]
	bl FUN_020030E8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5]
	add r2, r5, #0
	str r0, [sp, #0xc]
	add r2, #0xc4
	ldr r2, [r2]
	mov r0, #7
	add r1, r7, #0
	mov r3, #2
	bl FUN_020068C8
	cmp r4, #1
	bne _022135AC
	ldr r0, [r5]
	mov r1, #0x10
	bl AllocFromHeap
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r5, #0
	add r0, #0xc4
	ldr r2, [r0]
	ldr r0, [r5, r1]
	add r1, r6, #0
	str r2, [r0]
	add r0, r5, #0
	bl MOD08_022154D4
	mov r1, #0x5e
	lsl r1, r1, #2
	ldr r2, [r5, r1]
	str r0, [r2, #8]
	ldr r0, [r5, r1]
	mov r2, #0
	strb r2, [r0, #4]
	ldr r0, [r5, r1]
	strb r2, [r0, #5]
	ldr r0, _02213628 ; =MOD08_022133F4
	ldr r1, [r5, r1]
	ldr r2, _0221362C ; =0x00001001
	bl FUN_0200CA44
	mov r1, #0x5e
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	str r0, [r1, #0xc]
_022135AC:
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_022154D4
	mov r1, #0
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r7, r0, #0x10
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_022154D4
	mov r1, #1
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_022154D4
	mov r1, #0x29
	bl FUN_0200782C
	sub r0, r4, r0
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	add r0, r5, #0
	add r0, #0xc4
	sub r7, #0x28
	ldr r0, [r0]
	mov r1, #2
	mov r2, #0
	neg r3, r7
	bl FUN_020179E0
	add r0, r5, #0
	add r0, #0xc4
	sub r4, #0x28
	ldr r0, [r0]
	mov r1, #2
	mov r2, #3
	neg r3, r4
	bl FUN_020179E0
	mov r0, #2
	mov r1, #1
	bl FUN_0201797C
	add r0, r5, #0
	bl MOD08_02215574
	add r1, r0, #0
	lsl r1, r1, #0x18
	mov r0, #2
	lsr r1, r1, #0x18
	bl FUN_020178BC
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_02213628: .word MOD08_022133F4
_0221362C: .word 0x00001001

	thumb_func_start MOD08_02213630
MOD08_02213630: ; 0x02213630
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	add r0, r0, #4
	add r0, r0, #4
	str r0, [r4, #0x18]
	mov r0, #2
	bl FUN_020187B0
	mov r2, #0x19
	mov r1, #0
	lsl r2, r2, #8
	bl MI_CpuFill8
	add r0, r4, #0
	mov r1, #4
	bl MOD08_02213454
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02213658
MOD08_02213658: ; 0x02213658
	push {r4, lr}
	sub sp, #0x18
	ldr r3, _022136CC ; =0x0222AA7C
	add r2, sp, #0
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r4, #0x18]
	add r0, r0, #4
	str r0, [r4, #0x18]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r0, #0xac
	ldr r0, [r0]
	bl FUN_0200BB34
	mov r1, #0x4e
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, [r4, r1]
	add r0, #0xac
	ldr r0, [r0]
	mov r2, #5
	bl FUN_0200BBF0
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r0, #0xac
	ldr r0, [r0]
	bl FUN_0200BB68
	mov r2, #0x11
	mov r1, #0
	lsl r2, r2, #0x10
	bl FUN_02008D24
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	mov r1, #0x4e
	add r0, #0xac
	lsl r1, r1, #2
	ldr r0, [r0]
	ldr r1, [r4, r1]
	add r2, sp, #0
	bl FUN_0200BF60
	add sp, #0x18
	pop {r4, pc}
	.align 2, 0
_022136CC: .word MOD8_0222AA7C

	thumb_func_start MOD08_022136D0
MOD08_022136D0: ; 0x022136D0
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r0, [r5, #0x18]
	ldr r1, _0221377C ; =0x00004E21
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r2, [r0]
	add r0, r0, #4
	str r0, [r5, #0x18]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r4, r2, r1
	ldrh r3, [r0, #0x14]
	lsr r2, r1, #2
	add r0, #0xac
	mul r2, r3
	add r4, r4, r2
	mov r2, #0
	str r2, [sp]
	mov r2, #1
	str r2, [sp, #4]
	str r4, [sp, #8]
	lsr r1, r1, #6
	ldr r0, [r0]
	ldr r1, [r5, r1]
	mov r2, #0x1b
	mov r3, #0x28
	bl FUN_0200C00C
	mov r0, #0x1b
	str r0, [sp]
	mov r3, #0x27
	str r3, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	add r2, r5, #0
	add r0, r5, #0
	str r4, [sp, #0x14]
	add r2, #0xc0
	ldr r2, [r2]
	add r0, #0xc8
	add r2, #0xac
	lsl r3, r3, #3
	ldr r0, [r0]
	ldr r2, [r2]
	ldr r3, [r5, r3]
	mov r1, #2
	bl FUN_0200C0DC
	mov r0, #0
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0x4e
	str r4, [sp, #4]
	add r0, #0xc0
	ldr r0, [r0]
	lsl r1, r1, #2
	add r0, #0xac
	ldr r0, [r0]
	ldr r1, [r5, r1]
	mov r2, #0x1b
	mov r3, #0x29
	bl FUN_0200C124
	mov r0, #0
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0x4e
	str r4, [sp, #4]
	add r0, #0xc0
	ldr r0, [r0]
	lsl r1, r1, #2
	add r0, #0xac
	ldr r0, [r0]
	ldr r1, [r5, r1]
	mov r2, #0x1b
	mov r3, #0x2a
	bl FUN_0200C13C
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221377C: .word 0x00004E21

	thumb_func_start MOD08_02213780
MOD08_02213780: ; 0x02213780
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x70
	add r4, r0, #0
	ldr r1, [r4, #0x18]
	ldr r6, _02213994 ; =0x00004E21
	add r2, r1, #4
	str r2, [r4, #0x18]
	ldr r1, [r2]
	add r2, r2, #4
	str r2, [r4, #0x18]
	mov ip, r1
	ldr r1, [r2]
	add r2, r2, #4
	str r2, [r4, #0x18]
	str r1, [sp, #0x10]
	ldr r1, [r2]
	add r2, r2, #4
	str r2, [r4, #0x18]
	str r1, [sp, #0xc]
	ldr r1, [r2]
	add r2, r2, #4
	str r2, [r4, #0x18]
	add r2, r4, #0
	add r2, #0xc0
	ldr r2, [r2]
	add r1, r1, r6
	ldrh r3, [r2, #0x14]
	lsr r2, r6, #2
	mul r2, r3
	add r2, r1, r2
	str r2, [sp, #0x58]
	add r2, r4, #0
	add r2, #0xc0
	ldr r2, [r2]
	ldrh r3, [r2, #0x14]
	lsr r2, r6, #2
	mul r2, r3
	add r2, r1, r2
	str r2, [sp, #0x5c]
	add r2, r4, #0
	add r2, #0xc0
	ldr r2, [r2]
	ldrh r3, [r2, #0x14]
	lsr r2, r6, #2
	mul r2, r3
	add r2, r1, r2
	str r2, [sp, #0x60]
	add r2, r4, #0
	add r2, #0xc0
	ldr r2, [r2]
	lsr r3, r6, #2
	ldrh r2, [r2, #0x14]
	mul r3, r2
	add r1, r1, r3
	str r1, [sp, #0x64]
	mov r1, #0
	str r1, [sp, #0x68]
	str r1, [sp, #0x6c]
	mov r1, ip
	bl MOD08_022132C4
	str r0, [sp, #0x1c]
	add r0, r4, #0
	add r0, #0xc0
	ldr r1, [r0]
	ldr r0, [sp, #0x1c]
	lsl r0, r0, #2
	add r0, r1, r0
	add r0, #0xb0
	ldr r1, [r0]
	ldr r0, [r1, #4]
	str r0, [sp, #0x18]
	ldr r0, [r1, #8]
	str r0, [sp, #0x14]
	ldr r0, [r1]
	ldr r1, [sp, #0x1c]
	str r0, [sp, #0x20]
	add r0, r4, #0
	bl MOD08_022154D4
	add r6, r0, #0
	beq _02213848
	mov r1, #0
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r7, r0, #0x10
	add r0, r6, #0
	mov r1, #1
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r5, r0, #0x10
	add r0, r6, #0
	mov r1, #0x29
	bl FUN_0200782C
	sub r0, r5, r0
	lsl r0, r0, #0x10
	asr r5, r0, #0x10
_02213848:
	add r0, sp, #0x24
	strh r7, [r0]
	strh r5, [r0, #2]
	mov r1, #0
	strh r1, [r0, #4]
	strh r1, [r0, #6]
	mov r0, #0x64
	str r0, [sp, #0x2c]
	mov r0, #1
	str r1, [sp, #0x30]
	str r0, [sp, #0x34]
	str r0, [sp, #0x50]
	str r1, [sp, #0x54]
	add r2, sp, #0x58
	add r3, sp, #0x24
_02213866:
	ldr r0, [r2]
	add r1, r1, #1
	str r0, [r3, #0x14]
	add r2, r2, #4
	add r3, r3, #4
	cmp r1, #6
	blt _02213866
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	mov r1, #0x4e
	add r0, #0xac
	lsl r1, r1, #2
	ldr r0, [r0]
	ldr r1, [r4, r1]
	add r2, sp, #0x24
	bl FUN_0200C154
	add r7, r0, #0
	cmp r6, #0
	bne _02213898
	mov r1, #0
	bl FUN_0200C644
	b _022138AC
_02213898:
	add r0, r6, #0
	mov r1, #6
	bl FUN_0200782C
	cmp r0, #1
	bne _022138AC
	add r0, r7, #0
	mov r1, #0
	bl FUN_0200C644
_022138AC:
	add r0, r4, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _022138CE
	ldr r1, [sp, #0x1c]
	add r0, r4, #0
	bl MOD08_022154A8
	bl MOD08_0222A6C8
	cmp r0, #1
	bne _022138CE
	add r0, r7, #0
	mov r1, #1
	bl FUN_0200C8D0
_022138CE:
	ldr r1, [sp, #0x1c]
	add r0, r4, #0
	bl MOD08_022154D4
	cmp r0, #0
	beq _022138F0
	ldr r0, [r7]
	bl FUN_02020350
	add r1, r0, #0
	mov r3, #0x32
	ldr r1, [r1, #4]
	ldr r2, [sp, #0x20]
	mov r0, #0x13
	lsl r3, r3, #6
	bl FUN_0201C2C8
_022138F0:
	ldr r1, [sp, #0x1c]
	add r0, r4, #0
	bl MOD08_022154D4
	cmp r0, #0
	beq _02213926
	ldr r0, [r7]
	bl FUN_02020354
	mov r1, #1
	bl FUN_0201E28C
	mov r1, #2
	str r1, [sp]
	mov r1, #0x20
	lsl r0, r0, #0x14
	str r1, [sp, #4]
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0xc8
	ldr r0, [r0]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	ldr r3, [r4]
	bl FUN_020030E8
_02213926:
	ldr r0, [sp, #0xc]
	lsl r5, r0, #2
	mov r0, #0x4f
	lsl r0, r0, #2
	add r6, r4, r0
	ldr r0, [r6, r5]
	cmp r0, #0
	beq _0221393A
	bl ErrorHandling
_0221393A:
	mov r0, #0x15
	str r7, [r6, r5]
	mov r2, #1
	add r1, r4, r5
	lsl r0, r0, #4
	str r2, [r1, r0]
	ldr r0, [sp, #0x10]
	cmp r0, #1
	bne _02213990
	ldr r1, [sp, #0x1c]
	add r0, r4, #0
	bl MOD08_022154D4
	cmp r0, #0
	beq _02213990
	mov r0, #0x59
	lsl r0, r0, #2
	add r6, r4, r0
	ldr r0, [r4]
	mov r1, #0x10
	bl AllocFromHeap
	str r0, [r6, r5]
	ldr r0, [r6, r5]
	ldr r1, [sp, #0x1c]
	str r7, [r0]
	add r0, r4, #0
	bl MOD08_022154D4
	ldr r1, [r6, r5]
	ldr r2, _02213998 ; =0x00001001
	str r0, [r1, #8]
	ldr r0, [r6, r5]
	mov r1, #0
	strb r1, [r0, #4]
	ldr r0, [r6, r5]
	strb r1, [r0, #5]
	ldr r0, _0221399C ; =MOD08_022133A8
	ldr r1, [r6, r5]
	bl FUN_0200CA44
	ldr r1, [r6, r5]
	str r0, [r1, #0xc]
_02213990:
	add sp, #0x70
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02213994: .word 0x00004E21
_02213998: .word 0x00001001
_0221399C: .word MOD08_022133A8

	thumb_func_start MOD08_022139A0
MOD08_022139A0: ; 0x022139A0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	add r0, r0, #4
	str r0, [r4, #0x18]
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _022139C2
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r0, #0xac
	ldr r0, [r0]
	bl FUN_0200C398
_022139C2:
	mov r0, #0x4e
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	pop {r4, pc}

	thumb_func_start MOD08_022139CC
MOD08_022139CC: ; 0x022139CC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r1, [r0]
	add r0, r0, #4
	str r0, [r5, #0x18]
	mov r0, #0x4f
	lsl r0, r0, #2
	lsl r4, r1, #2
	add r6, r5, r0
	ldr r0, [r6, r4]
	cmp r0, #0
	beq _022139EE
	bl FUN_0200C3DC
_022139EE:
	mov r0, #0x15
	mov r2, #0
	add r1, r5, r4
	lsl r0, r0, #4
	str r2, [r1, r0]
	str r2, [r6, r4]
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_022139FC
MOD08_022139FC: ; 0x022139FC
	push {r3, lr}
	ldr r2, [r1, #0xc]
	cmp r2, #0
	bne _02213A0A
	bl FUN_0200CAB4
	pop {r3, pc}
_02213A0A:
	mov r0, #0x4e
	ldr r2, [r1]
	lsl r0, r0, #2
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _02213A1C
	ldr r0, [r1, #4]
	bl FUN_0200BC1C
_02213A1C:
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD08_02213A20
MOD08_02213A20: ; 0x02213A20
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, [r5, #0x18]
	add r6, r5, #0
	add r1, r0, #4
	str r1, [r5, #0x18]
	ldr r0, [r1]
	add r6, #0x54
	str r0, [sp]
	add r0, r1, #4
	str r0, [r5, #0x18]
	ldr r2, [r0]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r1, [r0]
	add r0, r0, #4
	str r0, [r5, #0x18]
	add r0, r5, #0
	lsl r4, r2, #4
	str r0, [sp, #8]
	add r0, #0x4c
	lsl r1, r1, #2
	str r0, [sp, #8]
	str r5, [r0, r4]
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r3, [r5, r0]
	add r2, r5, r4
	str r3, [r2, #0x50]
	add r1, r5, r1
	add r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #0
	str r0, [r6, r4]
	mov r0, #1
	str r0, [r2, #0x58]
	ldr r0, [r6, r4]
	bl FUN_0200C644
	add r0, r5, #0
	bl MOD08_0221553C
	cmp r0, #1
	beq _02213A7C
	b _02213BCA
_02213A7C:
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_02227468
	str r0, [sp, #4]
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_02227468
	add r7, r0, #0
	ldr r1, [sp]
	add r0, r5, #0
	bl MOD08_022132C4
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022154D4
	cmp r0, #0
	beq _02213AB8
	mov r1, #6
	bl FUN_0200782C
	b _02213ABA
_02213AB8:
	mov r0, #0
_02213ABA:
	cmp r0, #1
	ldr r0, [r6, r4]
	bne _02213AC8
	mov r1, #0
	bl FUN_0200C644
	b _02213ACE
_02213AC8:
	mov r1, #1
	bl FUN_0200C644
_02213ACE:
	ldr r0, [sp]
	cmp r0, #3
	bhi _02213BBC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02213AE0: ; jump table
	.short _02213AE8 - _02213AE0 - 2 ; case 0
	.short _02213B36 - _02213AE0 - 2 ; case 1
	.short _02213B0E - _02213AE0 - 2 ; case 2
	.short _02213B7A - _02213AE0 - 2 ; case 3
_02213AE8:
	ldr r0, [sp, #4]
	sub r0, r0, #3
	cmp r0, #1
	bhi _02213AFA
	ldr r0, [r6, r4]
	mov r1, #1
	bl FUN_0200C6C4
	b _02213BBC
_02213AFA:
	add r5, #0x54
	ldr r0, [r5, r4]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r5, r4]
	mov r1, #0xff
	bl FUN_0200C6C4
	b _02213BBC
_02213B0E:
	ldr r0, [sp, #4]
	cmp r0, #5
	beq _02213B18
	cmp r0, #2
	bne _02213B22
_02213B18:
	ldr r0, [r6, r4]
	mov r1, #1
	bl FUN_0200C6C4
	b _02213BBC
_02213B22:
	add r5, #0x54
	ldr r0, [r5, r4]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r5, r4]
	mov r1, #0xff
	bl FUN_0200C6C4
	b _02213BBC
_02213B36:
	cmp r7, #5
	bhi _02213BBC
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02213B46: ; jump table
	.short _02213BBC - _02213B46 - 2 ; case 0
	.short _02213BBC - _02213B46 - 2 ; case 1
	.short _02213B52 - _02213B46 - 2 ; case 2
	.short _02213B5C - _02213B46 - 2 ; case 3
	.short _02213B66 - _02213B46 - 2 ; case 4
	.short _02213B70 - _02213B46 - 2 ; case 5
_02213B52:
	ldr r0, [r6, r4]
	mov r1, #0xff
	bl FUN_0200C6C4
	b _02213BBC
_02213B5C:
	ldr r0, [r6, r4]
	mov r1, #1
	bl FUN_0200C6C4
	b _02213BBC
_02213B66:
	ldr r0, [r6, r4]
	mov r1, #1
	bl FUN_0200C6C4
	b _02213BBC
_02213B70:
	ldr r0, [r6, r4]
	mov r1, #0xff
	bl FUN_0200C6C4
	b _02213BBC
_02213B7A:
	cmp r7, #5
	bhi _02213BBC
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02213B8A: ; jump table
	.short _02213BBC - _02213B8A - 2 ; case 0
	.short _02213BBC - _02213B8A - 2 ; case 1
	.short _02213B96 - _02213B8A - 2 ; case 2
	.short _02213BA0 - _02213B8A - 2 ; case 3
	.short _02213BAA - _02213B8A - 2 ; case 4
	.short _02213BB4 - _02213B8A - 2 ; case 5
_02213B96:
	ldr r0, [r6, r4]
	mov r1, #1
	bl FUN_0200C6C4
	b _02213BBC
_02213BA0:
	ldr r0, [r6, r4]
	mov r1, #0xff
	bl FUN_0200C6C4
	b _02213BBC
_02213BAA:
	ldr r0, [r6, r4]
	mov r1, #0xff
	bl FUN_0200C6C4
	b _02213BBC
_02213BB4:
	ldr r0, [r6, r4]
	mov r1, #1
	bl FUN_0200C6C4
_02213BBC:
	ldr r1, [sp, #8]
	mov r2, #1
	ldr r0, _02213BD0 ; =MOD08_022139FC
	add r1, r1, r4
	lsl r2, r2, #0xc
	bl FUN_0200CA44
_02213BCA:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02213BD0: .word MOD08_022139FC

	thumb_func_start MOD08_02213BD4
MOD08_02213BD4: ; 0x02213BD4
	ldr r1, [r0, #0x18]
	mov r2, #0
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r3, [r1]
	add r1, r1, #4
	str r1, [r0, #0x18]
	lsl r1, r3, #4
	add r0, r0, r1
	str r2, [r0, #0x58]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02213BEC
MOD08_02213BEC: ; 0x02213BEC
	ldr r1, [r0, #0x18]
	ldr r3, _02213BFC ; =MOD08_02213454
	add r2, r1, #4
	str r2, [r0, #0x18]
	ldr r1, [r2]
	add r2, r2, #4
	str r2, [r0, #0x18]
	bx r3
	.align 2, 0
_02213BFC: .word MOD08_02213454

	thumb_func_start MOD08_02213C00
MOD08_02213C00: ; 0x02213C00
	ldr r1, [r0, #0x18]
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r3, [r1]
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r2, [r1]
	add r1, r1, #4
	str r1, [r0, #0x18]
	add r0, r0, r3
	add r0, #0x6c
	strb r2, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02213C1C
MOD08_02213C1C: ; 0x02213C1C
	ldr r1, [r0, #0x18]
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r3, [r1]
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r2, [r1]
	add r1, r1, #4
	str r1, [r0, #0x18]
	add r0, r0, r3
	add r0, #0x7c
	strb r2, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02213C38
MOD08_02213C38: ; 0x02213C38
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02213C3C
MOD08_02213C3C: ; 0x02213C3C
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02213C40
MOD08_02213C40: ; 0x02213C40
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r5, r0, #0
	ldrh r1, [r1, #0x14]
	add r0, r4, #0
	add r6, r2, #0
	bl MOD08_02227470
	add r7, r0, #0
	add r0, r4, #0
	add r4, #0xc0
	ldr r1, [r4]
	ldrh r1, [r1, #0x16]
	bl MOD08_02227470
	lsl r1, r6, #2
	add r1, r5, r1
	ldr r1, [r1, #0x1c]
	cmp r1, #2
	bne _02213C84
	cmp r7, r0
	bne _02213C7C
	cmp r0, #3
	beq _02213C78
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02213C78:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02213C7C:
	cmp r0, #3
	bne _02213C90
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02213C84:
	cmp r1, #0
	beq _02213C90
	cmp r0, #3
	bne _02213C90
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02213C90:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02213C94
MOD08_02213C94: ; 0x02213C94
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r0, #0
	add r5, r1, #0
	add r0, r3, #0
	mov r1, #0
	add r4, r2, #0
	str r3, [sp, #0x10]
	bl MOD08_022156AC
	add r1, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, [r5]
	add r2, r5, #0
	str r0, [sp, #0xc]
	add r2, #0xc4
	ldr r2, [r2]
	mov r0, #7
	add r3, r4, #0
	bl FUN_0200687C
	ldr r0, [sp, #0x10]
	mov r1, #1
	bl MOD08_022156AC
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x90
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xc8
	ldr r0, [r0]
	ldr r3, [r5]
	mov r1, #7
	bl FUN_020030E8
	add r0, r5, #0
	add r0, #0xc4
	lsl r1, r4, #0x18
	ldr r0, [r0]
	lsr r1, r1, #0x18
	bl FUN_02018744
	add r0, r5, #0
	mov r6, #2
	bl MOD08_02212004
	cmp r0, #1
	bne _02213D08
	mov r6, #4
	b _02213D18
_02213D08:
	add r0, r7, #0
	add r1, r5, #0
	mov r2, #7
	bl MOD08_02213C40
	cmp r0, #1
	bne _02213D18
	mov r6, #3
_02213D18:
	ldr r0, [sp, #0x10]
	add r1, r6, #0
	bl MOD08_022156AC
	add r1, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, [r5]
	add r5, #0xc4
	str r0, [sp, #0xc]
	ldr r2, [r5]
	mov r0, #7
	add r3, r4, #0
	bl FUN_020068C8
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02213D40
MOD08_02213D40: ; 0x02213D40
	lsl r0, r0, #0x10
	and r0, r1
	cmp r1, r0
	bne _02213D4C
	mov r0, #1
	bx lr
_02213D4C:
	mov r0, #0
	bx lr

	thumb_func_start MOD08_02213D50
MOD08_02213D50: ; 0x02213D50
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	ldr r3, _02213DA0 ; =0x0222AA2C
	add r2, sp, #0
	add r5, r0, #0
	add r4, r2, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r7, _02213DA4 ; =0x0222AADC
	mov r6, #0
_02213D68:
	ldr r0, [r5, #0x18]
	ldr r1, [r4]
	bl MOD08_02213D40
	cmp r0, #0
	beq _02213D92
	ldr r0, [r4]
	mov r1, #0
	lsr r2, r0, #0x10
	cmp r2, #2
	blt _02213D8A
_02213D7E:
	lsr r0, r2, #0x1f
	add r0, r2, r0
	asr r2, r0, #1
	add r1, r1, #1
	cmp r2, #2
	bge _02213D7E
_02213D8A:
	lsl r1, r1, #2
	ldr r1, [r7, r1]
	add r0, r5, #0
	blx r1
_02213D92:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blo _02213D68
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02213DA0: .word MOD8_0222AA2C
_02213DA4: .word MOD8_0222AADC

	thumb_func_start MOD08_02213DA8
MOD08_02213DA8: ; 0x02213DA8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	mov r1, #0x4c
	bl AllocFromHeap
	add r4, r0, #0
	bne _02213DC0
	bl ErrorHandling
	mov r0, #0
	pop {r3, r4, r5, pc}
_02213DC0:
	mov r1, #0
	mov r2, #0x4c
	bl memset
	mov r0, #0
	str r0, [r4]
	strb r0, [r4, #5]
	str r5, [r4, #0x48]
	strb r0, [r4, #9]
	mov r0, #0x1f
	strb r0, [r4, #0xa]
	mov r0, #0x1d
	strb r0, [r4, #0xb]
	mov r0, #2
	strb r0, [r4, #0xc]
	add r0, r5, #0
	mov r1, #5
	bl MOD08_02212498
	cmp r0, #1
	bne _02213DFA
	mov r0, #0
	strb r0, [r4, #9]
	mov r0, #0x1f
	strb r0, [r4, #0xa]
	mov r0, #0xf
	strb r0, [r4, #0xb]
	mov r0, #7
	strb r0, [r4, #0xc]
_02213DFA:
	add r0, r5, #0
	mov r1, #5
	bl MOD08_02212498
	cmp r0, #2
	bne _02213E16
	mov r0, #7
	strb r0, [r4, #9]
	mov r0, #0xf
	strb r0, [r4, #0xa]
	mov r0, #0x1d
	strb r0, [r4, #0xb]
	mov r0, #2
	strb r0, [r4, #0xc]
_02213E16:
	mov r1, #0
	add r2, r5, #0
	add r3, r4, #0
_02213E1C:
	add r0, r2, #0
	add r0, #0x94
	ldr r0, [r0]
	add r1, r1, #1
	str r0, [r3, #0x1c]
	add r2, r2, #4
	add r3, r3, #4
	cmp r1, #0xa
	blt _02213E1C
	mov r0, #0x5f
	mov r1, #1
	lsl r0, r0, #2
	strb r1, [r5, r0]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02213E3C
MOD08_02213E3C: ; 0x02213E3C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldrb r0, [r5, #5]
	cmp r0, #0
	beq _02213E50
	cmp r0, #1
	beq _02213E8E
	cmp r0, #2
	beq _02213EE0
	b _02213F2A
_02213E50:
	ldr r0, [r5, #0x48]
	mov r1, #2
	bl MOD08_0221477C
	ldr r0, [r5, #0x48]
	mov r1, #2
	bl MOD08_02215600
	add r4, r0, #0
	ldr r0, [r5, #0x48]
	mov r1, #1
	bl MOD08_02215600
	lsl r1, r4, #0x18
	mov r0, #3
	lsr r1, r1, #0x18
	bl FUN_020178BC
	lsl r1, r4, #0x18
	mov r0, #2
	lsr r1, r1, #0x18
	bl FUN_020178BC
	mov r0, #2
	mov r1, #1
	bl FUN_0201797C
	ldrb r0, [r5, #5]
	add r0, r0, #1
	strb r0, [r5, #5]
	b _02213F2E
_02213E8E:
	ldr r0, [r5, #0x48]
	mov r1, #3
	add r0, #0xc4
	ldr r0, [r0]
	mov r2, #2
	add r3, r1, #0
	bl FUN_020170F4
	ldr r0, [r5, #0x48]
	bl MOD08_02212004
	cmp r0, #1
	beq _02213EB8
	ldr r0, [r5, #0x48]
	mov r2, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #3
	add r3, r2, #0
	bl FUN_020170F4
_02213EB8:
	ldr r1, [r5, #0x48]
	ldr r3, [r5, #0x10]
	add r0, r5, #0
	mov r2, #3
	bl MOD08_02213C94
	ldrb r0, [r5, #9]
	mov r1, #4
	mov r2, #8
	str r0, [sp]
	ldrb r3, [r5, #0xa]
	ldr r0, _02213F34 ; =0x04000050
	bl G2x_SetBlendAlpha_
	add r0, r5, #0
	bl MOD08_02213D50
	ldrb r0, [r5, #5]
	add r0, r0, #1
	strb r0, [r5, #5]
_02213EE0:
	ldrb r1, [r5, #9]
	ldrb r0, [r5, #0xb]
	mov r2, #0
	cmp r1, r0
	bhs _02213EF0
	add r0, r1, #2
	strb r0, [r5, #9]
	b _02213EF2
_02213EF0:
	add r2, r2, #1
_02213EF2:
	ldrb r1, [r5, #0xa]
	ldrb r0, [r5, #0xc]
	cmp r1, r0
	bls _02213F00
	sub r0, r1, #2
	strb r0, [r5, #0xa]
	b _02213F02
_02213F00:
	add r2, r2, #1
_02213F02:
	cmp r2, #2
	bne _02213F14
	ldrb r0, [r5, #0xb]
	strb r0, [r5, #9]
	ldrb r0, [r5, #0xc]
	strb r0, [r5, #0xa]
	ldrb r0, [r5, #5]
	add r0, r0, #1
	strb r0, [r5, #5]
_02213F14:
	ldrb r0, [r5, #9]
	ldrb r1, [r5, #0xa]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _02213F38 ; =0x04000052
	strh r1, [r0]
	ldrb r0, [r5, #5]
	cmp r0, #2
	beq _02213F2E
	mov r0, #0
	pop {r3, r4, r5, pc}
_02213F2A:
	mov r0, #0
	pop {r3, r4, r5, pc}
_02213F2E:
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_02213F34: .word 0x04000050
_02213F38: .word 0x04000052

	thumb_func_start MOD08_02213F3C
MOD08_02213F3C: ; 0x02213F3C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r1, #0
	ldrb r0, [r4, #5]
	cmp r0, #4
	bls _02213F4A
	b _0221411C
_02213F4A:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02213F56: ; jump table
	.short _02213F60 - _02213F56 - 2 ; case 0
	.short _02213F6E - _02213F56 - 2 ; case 1
	.short _02213FB0 - _02213F56 - 2 ; case 2
	.short _02213FF6 - _02213F56 - 2 ; case 3
	.short _022140F8 - _02213F56 - 2 ; case 4
_02213F60:
	mov r0, #2
	mov r1, #1
	bl FUN_0201797C
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
_02213F6E:
	ldr r0, [r4, #0x48]
	mov r1, #2
	bl MOD08_02215600
	add r5, r0, #0
	ldr r0, [r4, #0x48]
	mov r1, #1
	bl MOD08_02215600
	lsl r1, r5, #0x18
	mov r0, #3
	lsr r1, r1, #0x18
	bl FUN_020178BC
	lsl r1, r5, #0x18
	mov r0, #2
	lsr r1, r1, #0x18
	bl FUN_020178BC
	ldrb r0, [r4, #0xa]
	mov r1, #4
	mov r2, #8
	str r0, [sp]
	ldrb r3, [r4, #9]
	ldr r0, _02214128 ; =0x04000050
	bl G2x_SetBlendAlpha_
	add r0, r4, #0
	bl MOD08_02213D50
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
_02213FB0:
	ldrb r1, [r4, #9]
	ldrb r0, [r4, #0xb]
	mov r2, #0
	cmp r1, r0
	bhs _02213FC0
	add r0, r1, #2
	strb r0, [r4, #9]
	b _02213FC2
_02213FC0:
	add r2, r2, #1
_02213FC2:
	ldrb r1, [r4, #0xa]
	ldrb r0, [r4, #0xc]
	cmp r1, r0
	bls _02213FD0
	sub r0, r1, #2
	strb r0, [r4, #0xa]
	b _02213FD2
_02213FD0:
	add r2, r2, #1
_02213FD2:
	cmp r2, #2
	bne _02213FE8
	ldrb r0, [r4, #0xb]
	add r0, r0, #2
	strb r0, [r4, #9]
	ldrb r0, [r4, #0xc]
	sub r0, r0, #2
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
_02213FE8:
	ldrb r0, [r4, #0xa]
	ldrb r1, [r4, #9]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0221412C ; =0x04000052
	strh r1, [r0]
	b _02214122
_02213FF6:
	add r0, r4, #0
	add r0, #0x44
	ldrh r0, [r0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _0221400A
	ldr r0, [r4, #0x48]
	bl MOD08_02214524
_0221400A:
	add r0, r4, #0
	add r0, #0x44
	ldrh r0, [r0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _0221401E
	ldr r0, [r4, #0x48]
	bl MOD08_02214524
_0221401E:
	ldr r0, [r4, #0x48]
	mov r2, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #3
	add r3, r2, #0
	bl FUN_020179E0
	ldr r0, [r4, #0x48]
	mov r1, #3
	add r0, #0xc4
	ldr r0, [r0]
	add r2, r1, #0
	mov r3, #0
	bl FUN_020179E0
	ldr r0, [r4, #0x48]
	mov r1, #3
	add r0, #0xc4
	ldr r0, [r0]
	mov r2, #2
	mov r3, #4
	bl FUN_020170F4
	ldr r0, [r4, #0x48]
	bl MOD08_02212004
	cmp r0, #0
	bne _02214078
	ldr r0, [r4, #0x48]
	mov r1, #3
	add r0, #0xc4
	ldr r0, [r0]
	mov r2, #0
	mov r3, #1
	bl FUN_020170F4
	ldr r0, [r4, #0x48]
	mov r1, #3
	bl MOD08_02215638
	ldr r0, [r4, #0x48]
	bl MOD08_02215660
	b _022140CC
_02214078:
	ldr r2, [r4, #0x48]
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, [r2]
	mov r1, #0x61
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	ldr r0, [r2, r1]
	add r1, r1, #4
	ldr r1, [r2, r1]
	add r2, #0xc4
	ldr r2, [r2]
	mov r3, #3
	bl FUN_0200687C
	mov r2, #0x66
	lsl r2, r2, #2
	add r1, r2, #0
	ldr r3, [r4, #0x48]
	mov r0, #0
	str r0, [sp]
	ldr r0, [r3, r2]
	sub r1, #0x14
	lsl r0, r0, #5
	str r0, [sp, #4]
	sub r0, r2, #4
	ldr r0, [r3, r0]
	sub r2, #0xc
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	add r0, r3, #0
	add r0, #0xc8
	ldr r0, [r0]
	ldr r1, [r3, r1]
	ldr r2, [r3, r2]
	ldr r3, [r3]
	bl FUN_020030E8
_022140CC:
	ldr r2, [r4, #0x48]
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, [r2]
	mov r1, #0x61
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	ldr r0, [r2, r1]
	add r1, #0xc
	ldr r1, [r2, r1]
	add r2, #0xc4
	ldr r2, [r2]
	mov r3, #3
	bl FUN_020068C8
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
	b _02214122
_022140F8:
	ldr r0, [r4, #0x48]
	bl MOD08_02212004
	cmp r0, #0
	bne _02214108
	bl MOD11_02231678
	b _0221410C
_02214108:
	bl MOD12_02233560
_0221410C:
	ldr r0, [r4, #0x48]
	mov r1, #2
	bl MOD08_02214850
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
	b _02214122
_0221411C:
	add sp, #0x10
	mov r0, #0
	pop {r3, r4, r5, pc}
_02214122:
	mov r0, #1
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_02214128: .word 0x04000050
_0221412C: .word 0x04000052

	thumb_func_start MOD08_02214130
MOD08_02214130: ; 0x02214130
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldrb r0, [r4, #5]
	cmp r0, #0
	beq _02214142
	cmp r0, #1
	beq _022141BE
	b _0221423A
_02214142:
	ldrb r0, [r4, #0xd]
	ldr r2, [r4, #0x48]
	cmp r0, #0
	bne _02214180
	mov r3, #0
	str r3, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	mov r5, #0x67
	add r0, r2, #0
	str r3, [sp, #8]
	lsl r5, r5, #2
	ldr r2, [r2, r5]
	add r0, #0xc8
	lsl r2, r2, #0x10
	ldr r0, [r0]
	mov r1, #1
	lsr r2, r2, #0x10
	bl FUN_02003210
	mov r1, #0
	str r1, [sp]
	ldr r0, [r4, #0x48]
	add r2, r5, #0
	add r0, #0xc8
	ldr r0, [r0]
	add r2, #0x64
	mov r3, #0x10
	bl FUN_02003A64
	b _022141B8
_02214180:
	mov r3, #0
	str r3, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	ldr r0, _02214254 ; =0x0000FFFF
	mov r5, #0x67
	str r0, [sp, #8]
	add r0, r2, #0
	lsl r5, r5, #2
	ldr r2, [r2, r5]
	add r0, #0xc8
	lsl r2, r2, #0x10
	ldr r0, [r0]
	mov r1, #1
	lsr r2, r2, #0x10
	bl FUN_02003210
	ldr r0, _02214254 ; =0x0000FFFF
	add r2, r5, #0
	str r0, [sp]
	ldr r0, [r4, #0x48]
	mov r1, #0
	add r0, #0xc8
	ldr r0, [r0]
	add r2, #0x64
	mov r3, #0x10
	bl FUN_02003A64
_022141B8:
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
_022141BE:
	ldr r0, [r4, #0x48]
	add r0, #0xc8
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	bne _0221424E
	ldr r0, [r4, #0x48]
	mov r2, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #3
	add r3, r2, #0
	bl FUN_020170F4
	ldr r1, [r4, #0x48]
	ldr r3, [r4, #0x10]
	add r0, r4, #0
	mov r2, #3
	bl MOD08_02213C94
	ldrb r0, [r4, #0xd]
	cmp r0, #0
	bne _02214208
	mov r0, #0x10
	str r0, [sp]
	mov r3, #0
	str r3, [sp, #4]
	str r3, [sp, #8]
	ldr r0, [r4, #0x48]
	mov r1, #1
	add r0, #0xc8
	ldr r0, [r0]
	lsl r2, r1, #9
	bl FUN_02003210
	b _02214222
_02214208:
	mov r0, #0x10
	str r0, [sp]
	mov r3, #0
	ldr r0, _02214254 ; =0x0000FFFF
	str r3, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4, #0x48]
	mov r1, #1
	add r0, #0xc8
	ldr r0, [r0]
	lsl r2, r1, #9
	bl FUN_02003210
_02214222:
	add r0, r4, #0
	bl MOD08_02213D50
	mov r0, #0x5f
	ldr r1, [r4, #0x48]
	mov r2, #2
	lsl r0, r0, #2
	strb r2, [r1, r0]
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
	b _0221424E
_0221423A:
	ldr r0, [r4, #0x48]
	add r0, #0xc8
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	bne _0221424E
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, pc}
_0221424E:
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02214254: .word 0x0000FFFF

	thumb_func_start MOD08_02214258
MOD08_02214258: ; 0x02214258
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r1, #0
	ldrb r0, [r4, #5]
	cmp r0, #3
	bls _02214266
	b _02214462
_02214266:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02214272: ; jump table
	.short _0221427A - _02214272 - 2 ; case 0
	.short _02214286 - _02214272 - 2 ; case 1
	.short _02214300 - _02214272 - 2 ; case 2
	.short _022143F0 - _02214272 - 2 ; case 3
_0221427A:
	add r0, r4, #0
	bl MOD08_02213D50
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
_02214286:
	ldrb r0, [r4, #0xd]
	cmp r0, #0
	bne _022142C2
	mov r3, #0
	str r3, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	str r3, [sp, #8]
	ldr r0, [r4, #0x48]
	mov r1, #1
	add r0, #0xc8
	ldr r0, [r0]
	lsl r2, r1, #9
	bl FUN_02003210
	ldr r3, [r4, #0x48]
	mov r1, #0
	mov r2, #0x67
	add r0, r3, #0
	str r1, [sp]
	lsl r2, r2, #2
	ldr r2, [r3, r2]
	add r0, #0xc8
	lsl r2, r2, #0x10
	ldr r0, [r0]
	lsr r2, r2, #0x10
	mov r3, #0x10
	bl FUN_02003A64
	b _022142FA
_022142C2:
	mov r3, #0
	str r3, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	ldr r0, _0221448C ; =0x0000FFFF
	mov r1, #1
	str r0, [sp, #8]
	ldr r0, [r4, #0x48]
	lsl r2, r1, #9
	add r0, #0xc8
	ldr r0, [r0]
	bl FUN_02003210
	mov r2, #0x67
	ldr r3, [r4, #0x48]
	ldr r0, _0221448C ; =0x0000FFFF
	lsl r2, r2, #2
	str r0, [sp]
	add r0, r3, #0
	ldr r2, [r3, r2]
	add r0, #0xc8
	lsl r2, r2, #0x10
	ldr r0, [r0]
	mov r1, #0
	lsr r2, r2, #0x10
	mov r3, #0x10
	bl FUN_02003A64
_022142FA:
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
_02214300:
	ldr r0, [r4, #0x48]
	add r0, #0xc8
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	beq _02214310
	b _02214486
_02214310:
	add r0, r4, #0
	add r0, #0x44
	ldrh r0, [r0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _02214324
	ldr r0, [r4, #0x48]
	bl MOD08_02214524
_02214324:
	add r0, r4, #0
	add r0, #0x44
	ldrh r0, [r0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _02214338
	ldr r0, [r4, #0x48]
	bl MOD08_02214524
_02214338:
	mov r0, #3
	mov r1, #0
	bl FUN_0201797C
	ldr r0, [r4, #0x48]
	bl MOD08_02212004
	cmp r0, #0
	bne _0221436A
	ldr r0, [r4, #0x48]
	mov r1, #3
	add r0, #0xc4
	ldr r0, [r0]
	mov r2, #0
	mov r3, #1
	bl FUN_020170F4
	ldr r0, [r4, #0x48]
	mov r1, #3
	bl MOD08_02215638
	ldr r0, [r4, #0x48]
	bl MOD08_02215660
	b _022143BE
_0221436A:
	ldr r2, [r4, #0x48]
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, [r2]
	mov r1, #0x61
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	ldr r0, [r2, r1]
	add r1, r1, #4
	ldr r1, [r2, r1]
	add r2, #0xc4
	ldr r2, [r2]
	mov r3, #3
	bl FUN_0200687C
	mov r2, #0x66
	lsl r2, r2, #2
	add r1, r2, #0
	ldr r3, [r4, #0x48]
	mov r0, #0
	str r0, [sp]
	ldr r0, [r3, r2]
	sub r1, #0x14
	lsl r0, r0, #5
	str r0, [sp, #4]
	sub r0, r2, #4
	ldr r0, [r3, r0]
	sub r2, #0xc
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	add r0, r3, #0
	add r0, #0xc8
	ldr r0, [r0]
	ldr r1, [r3, r1]
	ldr r2, [r3, r2]
	ldr r3, [r3]
	bl FUN_020030E8
_022143BE:
	ldr r2, [r4, #0x48]
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, [r2]
	mov r1, #0x61
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	ldr r0, [r2, r1]
	add r1, #0xc
	ldr r1, [r2, r1]
	add r2, #0xc4
	ldr r2, [r2]
	mov r3, #3
	bl FUN_020068C8
	mov r0, #3
	mov r1, #1
	bl FUN_0201797C
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
_022143F0:
	ldr r0, [r4, #0x48]
	mov r2, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #3
	add r3, r2, #0
	bl FUN_020179E0
	ldr r0, [r4, #0x48]
	mov r1, #3
	add r0, #0xc4
	ldr r0, [r0]
	add r2, r1, #0
	mov r3, #0
	bl FUN_020179E0
	ldrb r0, [r4, #0xd]
	ldr r2, [r4, #0x48]
	cmp r0, #0
	bne _0221443A
	mov r0, #0x10
	str r0, [sp]
	mov r3, #0
	str r3, [sp, #4]
	mov r5, #0x67
	add r0, r2, #0
	str r3, [sp, #8]
	lsl r5, r5, #2
	ldr r2, [r2, r5]
	add r0, #0xc8
	lsl r2, r2, #0x10
	ldr r0, [r0]
	mov r1, #1
	lsr r2, r2, #0x10
	bl FUN_02003210
	b _0221445C
_0221443A:
	mov r0, #0x10
	str r0, [sp]
	mov r3, #0
	mov r5, #0x67
	ldr r0, _0221448C ; =0x0000FFFF
	str r3, [sp, #4]
	str r0, [sp, #8]
	add r0, r2, #0
	lsl r5, r5, #2
	ldr r2, [r2, r5]
	add r0, #0xc8
	lsl r2, r2, #0x10
	ldr r0, [r0]
	mov r1, #1
	lsr r2, r2, #0x10
	bl FUN_02003210
_0221445C:
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
_02214462:
	ldr r0, [r4, #0x48]
	add r0, #0xc8
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	bne _02214486
	mov r0, #0x5f
	ldr r1, [r4, #0x48]
	mov r2, #2
	lsl r0, r0, #2
	strb r2, [r1, r0]
	ldrb r0, [r4, #5]
	add sp, #0x10
	add r0, r0, #1
	strb r0, [r4, #5]
	mov r0, #0
	pop {r3, r4, r5, pc}
_02214486:
	mov r0, #1
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221448C: .word 0x0000FFFF

	thumb_func_start MOD08_02214490
MOD08_02214490: ; 0x02214490
	push {r3, lr}
	add r0, r1, #0
	bl MOD08_02213D50
	mov r0, #0
	pop {r3, pc}

	thumb_func_start MOD08_0221449C
MOD08_0221449C: ; 0x0221449C
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD08_02213D50
	add r0, r4, #0
	add r0, #0x44
	ldrh r0, [r0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _022144BA
	ldr r0, [r4, #0x48]
	bl MOD08_02214524
_022144BA:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_022144C0
MOD08_022144C0: ; 0x022144C0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x18]
	cmp r0, #1
	bne _022144DA
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
_022144DA:
	mov r3, #4
	mov r1, #8
	ldrsh r2, [r4, r3]
	ldrsh r0, [r4, r1]
	add r0, r2, r0
	strh r0, [r4, #4]
	mov r0, #6
	ldrsh r2, [r4, r0]
	mov r0, #0xa
	ldrsh r0, [r4, r0]
	add r0, r2, r0
	strh r0, [r4, #6]
	ldrsh r0, [r4, r1]
	cmp r0, #0
	beq _02214508
	ldr r1, [r4, #0xc]
	ldrsh r3, [r4, r3]
	lsl r1, r1, #0x18
	ldr r0, [r4]
	lsr r1, r1, #0x18
	mov r2, #0
	bl FUN_020179E0
_02214508:
	mov r0, #0xa
	ldrsh r0, [r4, r0]
	cmp r0, #0
	beq _02214522
	ldr r1, [r4, #0xc]
	mov r3, #6
	lsl r1, r1, #0x18
	ldrsh r3, [r4, r3]
	ldr r0, [r4]
	lsr r1, r1, #0x18
	mov r2, #3
	bl FUN_020179E0
_02214522:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02214524
MOD08_02214524: ; 0x02214524
	push {r4, lr}
	add r4, r0, #0
	bne _0221452E
	bl ErrorHandling
_0221452E:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _0221453C
	mov r0, #1
	str r0, [r1, #0x18]
_0221453C:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02214540
MOD08_02214540: ; 0x02214540
	mov r1, #0x67
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MOD08_02214548
MOD08_02214548: ; 0x02214548
	mov r0, #0
	bx lr

	thumb_func_start MOD08_0221454C
MOD08_0221454C: ; 0x0221454C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x48]
	mov r1, #0x20
	ldr r0, [r0]
	bl AllocFromHeap
	add r4, r0, #0
	ldr r0, [r5, #0x48]
	mov r2, #6
	add r0, #0xc4
	ldr r0, [r0]
	str r0, [r4]
	ldr r0, [r5, #0x48]
	add r0, #0x9c
	ldr r0, [r0]
	strh r0, [r4, #4]
	ldr r0, [r5, #0x48]
	add r0, #0xa0
	ldr r0, [r0]
	strh r0, [r4, #6]
	ldr r0, [r5, #0x48]
	add r0, #0x94
	ldr r0, [r0]
	strh r0, [r4, #8]
	ldr r0, [r5, #0x48]
	add r0, #0x98
	ldr r0, [r0]
	strh r0, [r4, #0xa]
	mov r0, #3
	str r0, [r4, #0xc]
	str r0, [r4, #0x10]
	ldr r1, [r5, #0x48]
	add r0, r5, #0
	bl MOD08_02213C40
	cmp r0, #1
	bne _022145C0
	mov r0, #8
	ldrsh r1, [r4, r0]
	sub r0, #9
	mul r0, r1
	strh r0, [r4, #8]
	mov r0, #0xa
	ldrsh r1, [r4, r0]
	sub r0, #0xb
	mul r0, r1
	strh r0, [r4, #0xa]
	mov r0, #4
	ldrsh r1, [r4, r0]
	sub r0, r0, #5
	mul r0, r1
	strh r0, [r4, #4]
	mov r0, #6
	ldrsh r1, [r4, r0]
	sub r0, r0, #7
	mul r0, r1
	strh r0, [r4, #6]
_022145C0:
	mov r0, #1
	str r0, [r4, #0x14]
	mov r1, #0
	str r1, [r4, #0x18]
	mov r1, #6
	ldr r2, [r5, #0x48]
	lsl r1, r1, #6
	str r4, [r2, r1]
	add r1, r5, #0
	add r1, #0x44
	ldrh r2, [r1]
	mov r1, #1
	add r5, #0x44
	bic r2, r1
	orr r0, r2
	strh r0, [r5]
	ldr r0, _022145F0 ; =MOD08_022144C0
	ldr r2, _022145F4 ; =0x00001001
	add r1, r4, #0
	bl FUN_0200CA44
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_022145F0: .word MOD08_022144C0
_022145F4: .word 0x00001001

	thumb_func_start MOD08_022145F8
MOD08_022145F8: ; 0x022145F8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	ldr r4, [r0, #0x48]
	str r0, [sp]
	ldr r0, [r4]
	mov r1, #0x20
	bl AllocFromHeap
	add r6, r0, #0
	ldr r0, [r4]
	mov r1, #0xc4
	bl AllocFromHeap
	str r0, [r6, #0x1c]
	mov r0, #6
	lsl r0, r0, #6
	str r6, [r4, r0]
	ldr r0, [sp]
	mov r1, #2
	add r0, #0x44
	ldrh r0, [r0]
	add r2, r0, #0
	ldr r0, [sp]
	orr r2, r1
	add r0, #0x44
	strh r2, [r0]
	mov r0, #0
	str r0, [r6, #0x18]
	add r0, r4, #0
	bl MOD08_022155C4
	bl MOD08_022189A0
	add r5, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl MOD08_02218998
	add r1, r0, #0
	ldr r2, [r4]
	add r0, r5, #0
	bl MOD08_022187F4
	mov r4, #0
	ldr r1, [r6, #0x1c]
	ldr r7, _022146C8 ; =0x0222AAF8
	add r1, #0xc0
	str r0, [r1]
	str r4, [sp, #4]
	add r5, r4, #0
_0221465C:
	ldr r0, [r6, #0x1c]
	strh r4, [r0, r5]
	ldr r0, [r6, #0x1c]
	add r1, r0, r5
	ldrsh r0, [r0, r5]
	add r0, #8
	strh r0, [r1, #2]
	mov r0, #0
	ldrsh r1, [r7, r0]
	ldr r0, [r6, #0x1c]
	add r0, r0, r5
	strh r1, [r0, #4]
	ldr r0, [r6, #0x1c]
	add r1, r0, r5
	mov r0, #0
	strh r0, [r1, #6]
	add r1, r0, #0
	bl MOD08_02218998
	ldr r1, [r6, #0x1c]
	mov r2, #6
	add r1, r1, r5
	str r0, [r1, #8]
	ldr r0, [sp]
	add r1, r0, #0
	ldr r1, [r1, #0x48]
	bl MOD08_02213C40
	cmp r0, #1
	bne _022146A6
	ldr r0, [r6, #0x1c]
	mov r1, #4
	add r0, r0, r5
	ldrsh r2, [r0, r1]
	sub r1, r1, #5
	mul r1, r2
	strh r1, [r0, #4]
_022146A6:
	ldr r0, [sp, #4]
	add r4, #8
	add r0, r0, #1
	add r5, #0xc
	add r7, r7, #2
	str r0, [sp, #4]
	cmp r0, #0x10
	blt _0221465C
	mov r2, #1
	ldr r0, _022146CC ; =MOD08_022146E4
	add r1, r6, #0
	lsl r2, r2, #0xc
	bl FUN_0200CA44
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022146C8: .word MOD8_0222AAF8
_022146CC: .word MOD08_022146E4

	thumb_func_start MOD08_022146D0
MOD08_022146D0: ; 0x022146D0
	add r1, r0, #0
	add r1, #0x44
	ldrh r2, [r1]
	mov r1, #2
	add r0, #0x44
	orr r1, r2
	strh r1, [r0]
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD08_022146E4
MOD08_022146E4: ; 0x022146E4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5, #0x18]
	ldr r4, [r5, #0x1c]
	cmp r0, #1
	bne _02214712
	add r4, #0xc0
	ldr r0, [r4]
	bl MOD08_02218870
	ldr r0, [r5, #0x1c]
	bl FreeToHeap
	add r0, r5, #0
	bl FreeToHeap
	add r0, r6, #0
	bl FUN_0200CAB4
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02214712:
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	bl MOD08_02218894
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
_02214722:
	mov r0, #6
	ldrsh r1, [r4, r0]
	mov r0, #4
	ldrsh r0, [r4, r0]
	add r0, r1, r0
	strh r0, [r4, #6]
	mov r0, #0
	ldrsh r6, [r4, r0]
	mov r0, #2
	ldrsh r0, [r4, r0]
	cmp r6, r0
	bge _0221476A
	ldr r0, [sp]
	lsl r1, r6, #2
	add r5, r0, r1
	mov r7, #2
_02214742:
	ldr r1, [r4, #8]
	mov r2, #6
	lsl r0, r1, #0x10
	asr r1, r1, #0x10
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	lsl r1, r1, #0x10
	ldrsh r2, [r4, r2]
	asr r0, r0, #0x10
	lsr r1, r1, #0x10
	add r0, r0, r2
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl MOD08_02218998
	stmia r5!, {r0}
	ldrsh r0, [r4, r7]
	add r6, r6, #1
	cmp r6, r0
	blt _02214742
_0221476A:
	ldr r0, [sp, #4]
	add r4, #0xc
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #0x10
	blt _02214722
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_0221477C
MOD08_0221477C: ; 0x0221477C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r1, #0
	mov r1, #2
	add r5, r0, #0
	bl MOD08_02215600
	add r1, r0, #0
	lsl r0, r4, #0x18
	lsl r1, r1, #0x18
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	bl FUN_020178BC
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	mov r1, #0
	bl FUN_0201797C
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _022147C0
	add r0, r5, #0
	add r0, #0xc4
	lsl r1, r4, #0x18
	ldr r0, [r0]
	lsr r1, r1, #0x18
	mov r2, #2
	mov r3, #4
	bl FUN_020170F4
	b _022147E4
_022147C0:
	add r0, r5, #0
	add r0, #0xc4
	lsl r1, r4, #0x18
	ldr r0, [r0]
	lsr r1, r1, #0x18
	mov r2, #0
	mov r3, #1
	bl FUN_020170F4
	add r0, r5, #0
	add r0, #0xc4
	lsl r1, r4, #0x18
	ldr r0, [r0]
	lsr r1, r1, #0x18
	mov r2, #2
	mov r3, #4
	bl FUN_020170F4
_022147E4:
	add r0, r5, #0
	add r0, #0xc4
	lsl r1, r4, #0x18
	ldr r0, [r0]
	lsr r1, r1, #0x18
	bl FUN_02018744
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _02214822
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, [r5]
	mov r1, #0x61
	add r2, r5, #0
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	ldr r0, [r5, r1]
	add r1, r1, #4
	add r2, #0xc4
	ldr r1, [r5, r1]
	ldr r2, [r2]
	add r3, r4, #0
	bl FUN_0200687C
	b _0221482A
_02214822:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02215638
_0221482A:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, [r5]
	mov r1, #0x61
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	ldr r0, [r5, r1]
	add r1, #0xc
	ldr r1, [r5, r1]
	add r5, #0xc4
	ldr r2, [r5]
	add r3, r4, #0
	bl FUN_020068C8
	add sp, #0x10
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02214850
MOD08_02214850: ; 0x02214850
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #1
	add r5, r0, #0
	bl MOD08_02215600
	add r1, r0, #0
	lsl r0, r4, #0x18
	lsl r1, r1, #0x18
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	bl FUN_020178BC
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _02214888
	add r0, r5, #0
	add r0, #0xc4
	lsl r1, r4, #0x18
	ldr r0, [r0]
	lsr r1, r1, #0x18
	mov r2, #2
	mov r3, #3
	bl FUN_020170F4
	b _022148AC
_02214888:
	add r0, r5, #0
	add r0, #0xc4
	lsl r1, r4, #0x18
	mov r2, #0
	ldr r0, [r0]
	lsr r1, r1, #0x18
	add r3, r2, #0
	bl FUN_020170F4
	add r0, r5, #0
	add r0, #0xc4
	lsl r1, r4, #0x18
	ldr r0, [r0]
	lsr r1, r1, #0x18
	mov r2, #2
	mov r3, #3
	bl FUN_020170F4
_022148AC:
	add r5, #0xc4
	lsl r1, r4, #0x18
	ldr r0, [r5]
	lsr r1, r1, #0x18
	bl FUN_02018744
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_022148BC
MOD08_022148BC: ; 0x022148BC
	add r1, r0, #0
	add r1, #0x44
	ldrh r2, [r1]
	mov r1, #1
	add r0, #0x44
	bic r2, r1
	mov r1, #1
	orr r1, r2
	strh r1, [r0]
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD08_022148D4
MOD08_022148D4: ; 0x022148D4
	push {r3, lr}
	ldr r0, [r0, #0x48]
	bl MOD08_02214524
	mov r0, #0
	pop {r3, pc}

	thumb_func_start MOD08_022148E0
MOD08_022148E0: ; 0x022148E0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r2, [r4, #0x14]
	add r5, r0, #0
	lsl r3, r2, #2
	ldr r2, _0221490C ; =0x0222AA64
	ldr r2, [r2, r3]
	blx r2
	cmp r0, #0
	bne _0221490A
	mov r0, #0x5f
	ldr r1, [r4, #0x48]
	mov r2, #0
	lsl r0, r0, #2
	strb r2, [r1, r0]
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_0221490A:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221490C: .word MOD8_0222AA64

	thumb_func_start MOD08_02214910
MOD08_02214910: ; 0x02214910
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD08_02213DA8
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	strb r0, [r4, #0xd]
	ldr r0, [r5, #0x18]
	ldr r2, _02214954 ; =0x0000044C
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	str r0, [r4, #0x10]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r1, [r0]
	add r0, r0, #4
	str r0, [r5, #0x18]
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	str r0, [r4, #0x14]
	ldr r0, _02214958 ; =0xFFFF0000
	and r0, r1
	lsr r0, r0, #0x10
	str r0, [r4, #0x18]
	ldr r0, _0221495C ; =MOD08_022148E0
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, pc}
	.align 2, 0
_02214954: .word 0x0000044C
_02214958: .word 0xFFFF0000
_0221495C: .word MOD08_022148E0

	thumb_func_start MOD08_02214960
MOD08_02214960: ; 0x02214960
	ldr r1, [r0, #0x18]
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r3, [r1]
	add r2, r1, #4
	str r2, [r0, #0x18]
	ldr r1, [r2]
	add r2, r2, #4
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	str r2, [r0, #0x18]
	cmp r3, #3
	bhi _022149B4
	add r2, r3, r3
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02214986: ; jump table
	.short _0221498E - _02214986 - 2 ; case 0
	.short _02214998 - _02214986 - 2 ; case 1
	.short _022149A2 - _02214986 - 2 ; case 2
	.short _022149AC - _02214986 - 2 ; case 3
_0221498E:
	mov r2, #6
	lsl r2, r2, #6
	ldr r0, [r0, r2]
	strh r1, [r0, #8]
	bx lr
_02214998:
	mov r2, #6
	lsl r2, r2, #6
	ldr r0, [r0, r2]
	strh r1, [r0, #0xa]
	bx lr
_022149A2:
	mov r2, #6
	lsl r2, r2, #6
	ldr r0, [r0, r2]
	strh r1, [r0, #4]
	bx lr
_022149AC:
	mov r2, #6
	lsl r2, r2, #6
	ldr r0, [r0, r2]
	strh r1, [r0, #4]
_022149B4:
	bx lr
	.align 2, 0

	thumb_func_start MOD08_022149B8
MOD08_022149B8: ; 0x022149B8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD08_02213DA8
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	strb r0, [r4, #0xd]
	ldr r0, [r5, #0x18]
	ldr r2, _02214A00 ; =0x0000044C
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	str r0, [r4, #0x10]
	ldr r0, [r5, #0x18]
	add r1, r0, #4
	str r1, [r5, #0x18]
	ldr r0, [r1]
	add r1, r1, #4
	str r1, [r5, #0x18]
	lsl r1, r0, #0x10
	lsr r1, r1, #0x10
	add r1, r1, #3
	str r1, [r4, #0x14]
	ldr r1, _02214A04 ; =0xFFFF0000
	and r0, r1
	lsr r0, r0, #0x10
	str r0, [r4, #0x18]
	ldr r0, _02214A08 ; =MOD08_022148E0
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, pc}
	nop
_02214A00: .word 0x0000044C
_02214A04: .word 0xFFFF0000
_02214A08: .word MOD08_022148E0

	thumb_func_start MOD08_02214A0C
MOD08_02214A0C: ; 0x02214A0C
	mov r1, #0x5f
	lsl r1, r1, #2
	ldrb r1, [r0, r1]
	cmp r1, #2
	bne _02214A24
	ldr r1, [r0, #0x18]
	add r1, r1, #4
	str r1, [r0, #0x18]
	mov r1, #0
	add r0, #0x8d
	strb r1, [r0]
	bx lr
_02214A24:
	mov r1, #1
	add r0, #0x8d
	strb r1, [r0]
	bx lr

	thumb_func_start MOD08_02214A2C
MOD08_02214A2C: ; 0x02214A2C
	mov r1, #0x5f
	lsl r1, r1, #2
	ldrb r1, [r0, r1]
	cmp r1, #0
	bne _02214A44
	ldr r1, [r0, #0x18]
	add r1, r1, #4
	str r1, [r0, #0x18]
	mov r1, #0
	add r0, #0x8d
	strb r1, [r0]
	bx lr
_02214A44:
	mov r1, #1
	add r0, #0x8d
	strb r1, [r0]
	bx lr

	thumb_func_start MOD08_02214A4C
MOD08_02214A4C: ; 0x02214A4C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5, #0x18]
	mov r1, #0
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r4, [r0]
	add r0, r0, #4
	str r0, [r5, #0x18]
	add r0, r4, #0
	bl MOD08_022156AC
	add r1, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, [r5]
	add r2, r5, #0
	str r0, [sp, #0xc]
	add r2, #0xc4
	ldr r2, [r2]
	mov r0, #7
	mov r3, #3
	bl FUN_0200687C
	add r0, r4, #0
	mov r1, #1
	bl MOD08_022156AC
	mov r2, #0
	str r2, [sp]
	add r1, r0, #0
	ldr r0, [r5]
	add r3, r2, #0
	str r0, [sp, #4]
	mov r0, #7
	bl FUN_02006930
	add r0, r4, #0
	mov r1, #2
	bl MOD08_022156AC
	add r1, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, [r5]
	add r5, #0xc4
	str r0, [sp, #0xc]
	ldr r2, [r5]
	mov r0, #7
	mov r3, #3
	bl FUN_020068C8
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02214AC8
MOD08_02214AC8: ; 0x02214AC8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl MOD08_02213DA8
	add r4, r0, #0
	ldr r0, [r5, #0x18]
	add r1, r0, #4
	str r1, [r5, #0x18]
	ldr r0, [r1]
	str r0, [sp]
	add r0, r1, #4
	str r0, [r5, #0x18]
	ldr r7, [r0]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r6, [r0]
	add r0, r0, #4
	str r0, [r5, #0x18]
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _02214AFA
	str r6, [r4, #0x10]
	b _02214B12
_02214AFA:
	add r0, r5, #0
	add r5, #0xc0
	ldr r1, [r5]
	ldrh r1, [r1, #0x16]
	bl MOD08_02227470
	cmp r0, #3
	bne _02214B0E
	str r7, [r4, #0x10]
	b _02214B12
_02214B0E:
	ldr r0, [sp]
	str r0, [r4, #0x10]
_02214B12:
	ldr r0, _02214B20 ; =MOD08_022148E0
	ldr r2, _02214B24 ; =0x0000044C
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02214B20: .word MOD08_022148E0
_02214B24: .word 0x0000044C

	thumb_func_start MOD08_02214B28
MOD08_02214B28: ; 0x02214B28
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02214B2C
MOD08_02214B2C: ; 0x02214B2C
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02214B30
MOD08_02214B30: ; 0x02214B30
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02214B34
MOD08_02214B34: ; 0x02214B34
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02214B38
MOD08_02214B38: ; 0x02214B38
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02214B3C
MOD08_02214B3C: ; 0x02214B3C
	ldr r1, [r0, #0x18]
	ldr r3, _02214B50 ; =FUN_020054C8
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r2, [r1]
	add r1, r1, #4
	str r1, [r0, #0x18]
	lsl r0, r2, #0x10
	lsr r0, r0, #0x10
	bx r3
	.align 2, 0
_02214B50: .word FUN_020054C8

	thumb_func_start MOD08_02214B54
MOD08_02214B54: ; 0x02214B54
	ldr r1, [r0, #0x18]
	ldr r3, _02214B6C ; =FUN_020054F0
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r2, [r1]
	add r1, r1, #4
	str r1, [r0, #0x18]
	lsl r0, r2, #0x10
	lsr r0, r0, #0x10
	mov r1, #0
	bx r3
	nop
_02214B6C: .word FUN_020054F0

	thumb_func_start MOD08_02214B70
MOD08_02214B70: ; 0x02214B70
	push {r3, r4, r5, lr}
	ldr r1, [r0, #0x18]
	add r2, r1, #4
	str r2, [r0, #0x18]
	ldr r1, [r2]
	lsl r1, r1, #0x10
	lsr r4, r1, #0x10
	add r1, r2, #4
	str r1, [r0, #0x18]
	ldr r2, [r1]
	add r1, r1, #4
	str r1, [r0, #0x18]
	lsl r1, r2, #0x18
	asr r1, r1, #0x18
	bl MOD08_02215354
	add r5, r0, #0
	add r0, r4, #0
	bl FUN_020054C8
	ldr r1, _02214BA4 ; =0x0000FFFF
	add r0, r4, #0
	add r2, r5, #0
	bl FUN_02005530
	pop {r3, r4, r5, pc}
	.align 2, 0
_02214BA4: .word 0x0000FFFF

	thumb_func_start MOD08_02214BA8
MOD08_02214BA8: ; 0x02214BA8
	push {r3, lr}
	ldr r1, [r0, #0x18]
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r2, [r1]
	add r1, r1, #4
	str r1, [r0, #0x18]
	lsl r1, r2, #0x18
	asr r1, r1, #0x18
	bl MOD08_02215354
	bl FUN_0200554C
	pop {r3, pc}

	thumb_func_start MOD08_02214BC4
MOD08_02214BC4: ; 0x02214BC4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD08_0221252C
	mov r1, #0
	mov r2, #0x3c
	add r4, r0, #0
	bl memset
	mov r0, #1
	strb r0, [r4]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	strh r0, [r4, #0x1a]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	str r0, [r4, #8]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	str r0, [r4, #0xc]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	str r0, [r4, #0x10]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	strb r0, [r4, #3]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r1, [r4, #8]
	add r0, r5, #0
	lsl r1, r1, #0x18
	asr r1, r1, #0x18
	bl MOD08_02215354
	str r0, [r4, #8]
	ldr r1, [r4, #0xc]
	add r0, r5, #0
	lsl r1, r1, #0x18
	asr r1, r1, #0x18
	bl MOD08_02215354
	str r0, [r4, #0xc]
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x10]
	lsl r0, r0, #0x18
	lsl r1, r1, #0x18
	lsl r2, r2, #0x18
	asr r0, r0, #0x18
	asr r1, r1, #0x18
	asr r2, r2, #0x18
	bl MOD08_0221540C
	str r0, [r4, #0x10]
	ldrh r0, [r4, #0x1a]
	bl FUN_020054C8
	ldrh r0, [r4, #0x1a]
	ldr r1, _02214C60 ; =0x0000FFFF
	ldr r2, [r4, #8]
	bl FUN_02005530
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_0221255C
	pop {r3, r4, r5, pc}
	.align 2, 0
_02214C60: .word 0x0000FFFF

	thumb_func_start MOD08_02214C64
MOD08_02214C64: ; 0x02214C64
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD08_0221252C
	mov r1, #0
	mov r2, #0x3c
	add r4, r0, #0
	bl memset
	mov r0, #2
	strb r0, [r4]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	strh r0, [r4, #0x1a]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [r4, #8]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [r4, #0xc]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [r4, #0x10]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	strb r0, [r4, #3]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldrh r0, [r4, #0x1a]
	bl FUN_020054C8
	ldrh r0, [r4, #0x1a]
	ldr r1, _02214CD8 ; =0x0000FFFF
	ldr r2, [r4, #8]
	bl FUN_02005530
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_0221255C
	pop {r3, r4, r5, pc}
	.align 2, 0
_02214CD8: .word 0x0000FFFF

	thumb_func_start MOD08_02214CDC
MOD08_02214CDC: ; 0x02214CDC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD08_0221252C
	mov r1, #0
	mov r2, #0x3c
	add r4, r0, #0
	bl memset
	mov r0, #1
	strb r0, [r4]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	strh r0, [r4, #0x1a]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [r4, #8]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [r4, #0xc]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [r4, #0x10]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	strb r0, [r4, #3]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r1, [r4, #8]
	add r0, r5, #0
	lsl r1, r1, #0x18
	asr r1, r1, #0x18
	bl MOD08_02215354
	str r0, [r4, #8]
	ldr r1, [r4, #0xc]
	add r0, r5, #0
	lsl r1, r1, #0x18
	asr r1, r1, #0x18
	bl MOD08_02215354
	str r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	add r0, r5, #0
	lsl r1, r1, #0x18
	asr r1, r1, #0x18
	bl MOD08_02215354
	str r0, [r4, #0x10]
	ldrh r0, [r4, #0x1a]
	bl FUN_020054C8
	ldrh r0, [r4, #0x1a]
	ldr r1, _02214D7C ; =0x0000FFFF
	ldr r2, [r4, #8]
	bl FUN_02005530
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_0221255C
	pop {r3, r4, r5, pc}
	nop
_02214D7C: .word 0x0000FFFF

	thumb_func_start MOD08_02214D80
MOD08_02214D80: ; 0x02214D80
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD08_0221252C
	mov r1, #0
	mov r2, #0x3c
	add r4, r0, #0
	bl memset
	mov r0, #4
	strb r0, [r4]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	strh r0, [r4, #0x1a]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [r4, #0x14]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	strb r0, [r4, #3]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	strb r0, [r4, #0x18]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldrb r0, [r4, #3]
	strb r0, [r4, #4]
	ldr r1, [r4, #0x14]
	add r0, r5, #0
	lsl r1, r1, #0x18
	asr r1, r1, #0x18
	bl MOD08_02215354
	str r0, [r4, #0x14]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_0221255C
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02214DE4
MOD08_02214DE4: ; 0x02214DE4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD08_0221252C
	mov r1, #0
	mov r2, #0x3c
	add r4, r0, #0
	bl memset
	mov r0, #5
	strb r0, [r4]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	strh r0, [r4, #0x1a]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [r4, #0x14]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r0, [r0]
	strb r0, [r4, #3]
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r1, [r4, #0x14]
	add r0, r5, #0
	lsl r1, r1, #0x18
	asr r1, r1, #0x18
	bl MOD08_02215354
	str r0, [r4, #0x14]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_0221255C
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02214E3C
MOD08_02214E3C: ; 0x02214E3C
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02214E40
MOD08_02214E40: ; 0x02214E40
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x90
	ldrh r0, [r0]
	cmp r0, #0
	beq _02214E5C
	add r0, r4, #0
	mov r1, #1
	add r0, #0x8d
	strb r1, [r0]
	ldr r0, _02214E94 ; =0x0000017D
	mov r1, #0
	strb r1, [r4, r0]
	pop {r4, pc}
_02214E5C:
	bl FUN_02005514
	cmp r0, #0
	beq _02214E80
	ldr r0, _02214E94 ; =0x0000017D
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	ldrb r1, [r4, r0]
	cmp r1, #0x5a
	bls _02214E78
	mov r1, #0
	strb r1, [r4, r0]
	pop {r4, pc}
_02214E78:
	mov r0, #1
	add r4, #0x8d
	strb r0, [r4]
	pop {r4, pc}
_02214E80:
	add r0, r4, #0
	mov r1, #0
	add r0, #0x8d
	strb r1, [r0]
	ldr r0, _02214E94 ; =0x0000017D
	strb r1, [r4, r0]
	ldr r0, [r4, #0x18]
	add r0, r0, #4
	str r0, [r4, #0x18]
	pop {r4, pc}
	.align 2, 0
_02214E94: .word 0x0000017D

	thumb_func_start MOD08_02214E98
MOD08_02214E98: ; 0x02214E98
	push {r3, lr}
	ldr r1, [r0, #0x18]
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r3, [r1]
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r2, [r1]
	add r1, r1, #4
	str r1, [r0, #0x18]
	lsl r0, r2, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	lsl r3, r3, #0x10
	ldr r0, _02214EC4 ; =0x04001050
	mov r1, #1
	mov r2, #2
	lsr r3, r3, #0x10
	bl G2x_SetBlendAlpha_
	pop {r3, pc}
	nop
_02214EC4: .word 0x04001050

	thumb_func_start MOD08_02214EC8
MOD08_02214EC8: ; 0x02214EC8
	ldr r3, _02214ECC ; =MOD08_0221268C
	bx r3
	.align 2, 0
_02214ECC: .word MOD08_0221268C

	thumb_func_start MOD08_02214ED0
MOD08_02214ED0: ; 0x02214ED0
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02214ED4
MOD08_02214ED4: ; 0x02214ED4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r0, [r5, #0x18]
	add r6, r5, #0
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r1, [r0]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r7, [r0]
	add r0, r0, #4
	lsl r4, r1, #2
	add r6, #0xcc
	str r0, [r5, #0x18]
	ldr r0, [r6, r4]
	cmp r0, #0
	beq _02214EFC
	bl ErrorHandling
_02214EFC:
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r0, #0xac
	ldr r0, [r0]
	bl FUN_0200BB34
	str r0, [r6, r4]
	ldr r0, [r6, r4]
	cmp r0, #0
	bne _02214F16
	bl ErrorHandling
_02214F16:
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, [r6, r4]
	add r0, #0xac
	ldr r0, [r0]
	add r2, r7, #0
	bl FUN_0200BBF0
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r0, #0xac
	ldr r0, [r0]
	bl FUN_0200BB68
	mov r2, #0x11
	mov r1, #0
	lsl r2, r2, #0x10
	bl FUN_02008D24
	add r0, r5, #0
	mov r1, #0
	add r2, sp, #0
	add r0, #0x18
_02214F48:
	ldr r3, [r5, #0x18]
	add r1, r1, #1
	ldr r3, [r3]
	str r3, [r2]
	ldr r3, [r0]
	add r2, r2, #4
	add r3, r3, #4
	str r3, [r0]
	cmp r1, #6
	blt _02214F48
	add r5, #0xc0
	ldr r0, [r5]
	ldr r1, [r6, r4]
	add r0, #0xac
	ldr r0, [r0]
	add r2, sp, #0
	bl FUN_0200BF60
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02214F70
MOD08_02214F70: ; 0x02214F70
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	ldr r0, [r2, #0x18]
	add r0, r0, #4
	str r0, [r2, #0x18]
	ldr r1, [r0]
	add r0, r0, #4
	str r0, [r2, #0x18]
	ldr r3, [r0]
	add r0, r0, #4
	str r0, [r2, #0x18]
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02214FB0 ; =0x00001388
	lsl r1, r1, #2
	add r0, r3, r0
	str r0, [sp, #8]
	add r0, r2, #0
	add r1, r2, r1
	add r0, #0xc0
	ldr r0, [r0]
	add r1, #0xcc
	add r0, #0xac
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x15
	bl FUN_0200C00C
	add sp, #0xc
	pop {pc}
	.align 2, 0
_02214FB0: .word 0x00001388

	thumb_func_start MOD08_02214FB4
MOD08_02214FB4: ; 0x02214FB4
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	add r0, r0, #4
	str r0, [r4, #0x18]
	ldr r3, [r0]
	add r0, r0, #4
	str r0, [r4, #0x18]
	ldr r1, [r0]
	add r2, r0, #4
	str r2, [r4, #0x18]
	ldr r0, [r2]
	add r2, r2, #4
	str r2, [r4, #0x18]
	mov r2, #0x16
	str r2, [sp]
	str r1, [sp, #4]
	mov r2, #0
	str r2, [sp, #8]
	mov r2, #1
	str r2, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, _0221500C ; =0x00001388
	add r2, r4, #0
	add r0, r1, r0
	str r0, [sp, #0x14]
	add r2, #0xc0
	ldr r2, [r2]
	lsl r3, r3, #2
	add r0, r4, #0
	add r3, r4, r3
	add r0, #0xc8
	add r2, #0xac
	add r3, #0xcc
	ldr r0, [r0]
	ldr r2, [r2]
	ldr r3, [r3]
	mov r1, #2
	bl FUN_0200C0DC
	add sp, #0x18
	pop {r4, pc}
	nop
_0221500C: .word 0x00001388

	thumb_func_start MOD08_02215010
MOD08_02215010: ; 0x02215010
	push {r3, lr}
	sub sp, #8
	add r2, r0, #0
	ldr r0, [r2, #0x18]
	add r0, r0, #4
	str r0, [r2, #0x18]
	ldr r1, [r0]
	add r0, r0, #4
	str r0, [r2, #0x18]
	ldr r3, [r0]
	add r0, r0, #4
	str r0, [r2, #0x18]
	mov r0, #1
	str r0, [sp]
	ldr r0, _02215050 ; =0x00001388
	lsl r1, r1, #2
	add r0, r3, r0
	str r0, [sp, #4]
	add r0, r2, #0
	add r1, r2, r1
	add r0, #0xc0
	ldr r0, [r0]
	add r1, #0xcc
	add r0, #0xac
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x17
	bl FUN_0200C124
	add sp, #8
	pop {r3, pc}
	nop
_02215050: .word 0x00001388

	thumb_func_start MOD08_02215054
MOD08_02215054: ; 0x02215054
	push {r3, lr}
	sub sp, #8
	add r2, r0, #0
	ldr r0, [r2, #0x18]
	add r0, r0, #4
	str r0, [r2, #0x18]
	ldr r1, [r0]
	add r0, r0, #4
	str r0, [r2, #0x18]
	ldr r3, [r0]
	add r0, r0, #4
	str r0, [r2, #0x18]
	mov r0, #1
	str r0, [sp]
	ldr r0, _02215094 ; =0x00001388
	lsl r1, r1, #2
	add r0, r3, r0
	str r0, [sp, #4]
	add r0, r2, #0
	add r1, r2, r1
	add r0, #0xc0
	ldr r0, [r0]
	add r1, #0xcc
	add r0, #0xac
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x18
	bl FUN_0200C13C
	add sp, #8
	pop {r3, pc}
	nop
_02215094: .word 0x00001388

	thumb_func_start MOD08_02215098
MOD08_02215098: ; 0x02215098
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r4, r0, #0
	ldr r1, [r4, #0x18]
	add r1, r1, #4
	str r1, [r4, #0x18]
	ldr r5, [r1]
	add r2, r1, #4
	str r2, [r4, #0x18]
	ldr r1, [r2]
	str r1, [sp]
	add r1, r2, #4
	str r1, [r4, #0x18]
	bl MOD08_02212460
	add r6, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	mov r2, #0
	bl MOD08_02217B98
	add r1, sp, #0xc
	strh r0, [r1]
	add r0, r4, #0
	add r1, r6, #0
	mov r2, #1
	bl MOD08_02217B98
	add r2, sp, #0xc
	strh r0, [r2, #2]
	mov r1, #0
	strh r1, [r2, #4]
	strh r1, [r2, #6]
	mov r0, #0x64
	str r0, [sp, #0x14]
	mov r0, #1
	str r0, [sp, #0x1c]
	str r0, [sp, #0x38]
	add r0, r4, #0
	ldr r3, _022151A0 ; =0x00001388
	str r1, [sp, #0x18]
	str r1, [sp, #0x3c]
	add r2, sp, #0xc
	add r0, #0x18
_022150F0:
	ldr r6, [r4, #0x18]
	add r1, r1, #1
	ldr r6, [r6]
	add r6, r6, r3
	str r6, [r2, #0x14]
	ldr r6, [r0]
	add r2, r2, #4
	add r6, r6, #4
	str r6, [r0]
	cmp r1, #6
	blt _022150F0
	mov r0, #0x41
	lsl r0, r0, #2
	add r3, sp, #0xc
	add r2, r4, r0
	mov r6, #6
_02215110:
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	sub r6, r6, #1
	bne _02215110
	ldr r0, [r3]
	lsl r7, r5, #2
	str r0, [r2]
	add r0, r4, #0
	str r0, [sp, #8]
	add r0, #0xcc
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, [sp, #8]
	add r0, #0xac
	ldr r0, [r0]
	ldr r1, [r1, r7]
	add r2, sp, #0xc
	bl FUN_0200C154
	str r0, [sp, #4]
	ldr r0, [r4, #0x18]
	add r2, r4, #0
	ldr r3, [r0]
	add r0, r0, #4
	add r2, #0x18
	mov r6, #0
	str r0, [r4, #0x18]
	cmp r3, #0
	ble _02215168
	add r5, r4, #0
_02215150:
	ldr r0, [r4, #0x18]
	add r6, r6, #1
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0x94
	str r1, [r0]
	ldr r0, [r2]
	add r5, r5, #4
	add r0, r0, #4
	str r0, [r2]
	cmp r6, r3
	blt _02215150
_02215168:
	cmp r6, #0xa
	bge _02215180
	lsl r0, r6, #2
	add r2, r4, r0
	mov r1, #0
_02215172:
	add r0, r2, #0
	add r0, #0x94
	add r6, r6, #1
	add r2, r2, #4
	str r1, [r0]
	cmp r6, #0xa
	blt _02215172
_02215180:
	ldr r0, [sp]
	bl MOD08_02218C5C
	add r5, r0, #0
	add r0, r4, #0
	add r4, #0xc0
	ldr r1, [r4]
	ldr r2, [sp, #8]
	add r1, #0xac
	ldr r1, [r1]
	ldr r2, [r2, r7]
	ldr r3, [sp, #4]
	blx r5
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022151A0: .word 0x00001388

	thumb_func_start MOD08_022151A4
MOD08_022151A4: ; 0x022151A4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r0, #0
	ldr r1, [r5, #0x18]
	add r1, r1, #4
	str r1, [r5, #0x18]
	ldr r4, [r1]
	add r1, r1, #4
	str r1, [r5, #0x18]
	ldr r7, [r1]
	add r1, r1, #4
	str r1, [r5, #0x18]
	bl MOD08_02212460
	add r6, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0
	bl MOD08_02217B98
	add r1, sp, #0
	strh r0, [r1]
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #1
	bl MOD08_02217B98
	add r2, sp, #0
	strh r0, [r2, #2]
	mov r1, #0
	strh r1, [r2, #4]
	strh r1, [r2, #6]
	mov r0, #0x64
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0x10]
	str r0, [sp, #0x2c]
	add r0, r5, #0
	ldr r3, _02215254 ; =0x00001388
	str r1, [sp, #0xc]
	str r1, [sp, #0x30]
	add r2, sp, #0
	add r0, #0x18
_022151FA:
	ldr r6, [r5, #0x18]
	add r1, r1, #1
	ldr r6, [r6]
	add r6, r6, r3
	str r6, [r2, #0x14]
	ldr r6, [r0]
	add r2, r2, #4
	add r6, r6, #4
	str r6, [r0]
	cmp r1, #6
	blt _022151FA
	mov r0, #0x41
	lsl r0, r0, #2
	add r6, sp, #0
	add r3, r5, r0
	mov r2, #6
_0221521A:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0221521A
	ldr r0, [r6]
	lsl r1, r4, #2
	str r0, [r3]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r1, r5, r1
	add r0, #0xac
	add r1, #0xcc
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, sp, #0
	bl FUN_0200C154
	add r5, #0xdc
	lsl r4, r7, #2
	add r6, r0, #0
	ldr r0, [r5, r4]
	cmp r0, #0
	beq _0221524E
	bl ErrorHandling
_0221524E:
	str r6, [r5, r4]
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02215254: .word 0x00001388

	thumb_func_start MOD08_02215258
MOD08_02215258: ; 0x02215258
	push {r3, r4, r5, lr}
	ldr r1, [r0, #0x18]
	add r5, r0, #0
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r2, [r1]
	add r1, r1, #4
	add r5, #0xcc
	lsl r4, r2, #2
	str r1, [r0, #0x18]
	ldr r1, [r5, r4]
	cmp r1, #0
	beq _0221527E
	add r0, #0xc0
	ldr r0, [r0]
	add r0, #0xac
	ldr r0, [r0]
	bl FUN_0200C398
_0221527E:
	mov r0, #0
	str r0, [r5, r4]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02215284
MOD08_02215284: ; 0x02215284
	ldr r1, [r0, #0x18]
	add r1, r1, #4
	str r1, [r0, #0x18]
	ldr r3, [r1]
	add r2, r1, #4
	str r2, [r0, #0x18]
	ldr r1, [r2]
	add r2, r2, #4
	str r2, [r0, #0x18]
	lsl r2, r3, #2
	add r2, r0, r2
	mov r0, #0x4f
	lsl r0, r0, #2
	ldr r3, _022152A4 ; =FUN_0200C644
	ldr r0, [r2, r0]
	bx r3
	.align 2, 0
_022152A4: .word FUN_0200C644

	thumb_func_start MOD08_022152A8
MOD08_022152A8: ; 0x022152A8
	ldr r3, _022152AC ; =ErrorHandling
	bx r3
	.align 2, 0
_022152AC: .word ErrorHandling

	thumb_func_start MOD08_022152B0
MOD08_022152B0: ; 0x022152B0
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r1, [r5, #0x18]
	add r1, r1, #4
	str r1, [r5, #0x18]
	ldr r4, [r1]
	add r1, r1, #4
	str r1, [r5, #0x18]
	ldr r1, [r1]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	lsl r1, r1, #0x18
	asr r1, r1, #0x18
	bl MOD08_02215354
	add r3, r0, #0
	ldr r0, [r5, #0x18]
	add r0, r0, #4
	str r0, [r5, #0x18]
	ldr r1, [r0]
	add r0, r0, #4
	str r0, [r5, #0x18]
	add r0, r5, #0
	add r0, #0xc0
	ldr r2, [r0]
	mov r0, #0x46
	lsl r0, r0, #2
	str r1, [sp]
	ldr r1, [r2, r0]
	sub r0, #0xc
	str r1, [sp, #4]
	ldr r1, [r5]
	str r1, [sp, #8]
	add r1, r4, #0
	ldrh r4, [r2, #0x14]
	ldr r0, [r2, r0]
	lsl r4, r4, #1
	add r2, r2, r4
	add r2, #0xd8
	ldrh r2, [r2]
	bl FUN_02069FB0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_0221530C
MOD08_0221530C: ; 0x0221530C
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02005670
	cmp r0, #0
	bne _02215330
	ldr r0, [r4, #0x18]
	add r1, r0, #4
	str r1, [r4, #0x18]
	ldr r0, [r1]
	add r1, r1, #4
	str r1, [r4, #0x18]
	mov r1, #0
	add r4, #0x8d
	strb r1, [r4]
	bl FUN_02005614
	pop {r4, pc}
_02215330:
	mov r0, #1
	add r4, #0x8d
	strb r0, [r4]
	pop {r4, pc}

	thumb_func_start MOD08_02215338
MOD08_02215338: ; 0x02215338
	bx lr
	.align 2, 0

	thumb_func_start MOD08_0221533C
MOD08_0221533C: ; 0x0221533C
	cmp r0, #0x55
	bls _02215344
	mov r0, #0
	bx lr
_02215344:
	lsl r1, r0, #2
	ldr r0, _0221534C ; =0x0222AC6C
	ldr r0, [r0, r1]
	bx lr
	.align 2, 0
_0221534C: .word MOD8_0222AC6C

	thumb_func_start MOD08_02215350
MOD08_02215350: ; 0x02215350
	ldrb r0, [r0, #1]
	bx lr

	thumb_func_start MOD08_02215354
MOD08_02215354: ; 0x02215354
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD08_02212458
	add r7, r0, #0
	add r0, r5, #0
	bl MOD08_02212460
	add r6, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	bl MOD08_02227470
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02227470
	add r0, r5, #0
	add r1, r7, #0
	bl MOD08_02227470
	cmp r0, #3
	bne _02215390
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02227470
	cmp r0, #4
	beq _022153F6
_02215390:
	add r0, r5, #0
	add r1, r7, #0
	bl MOD08_02227470
	cmp r0, #4
	bne _022153B0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02227470
	cmp r0, #3
	bne _022153B0
	mov r0, #0
	mvn r0, r0
	mul r4, r0
	b _022153F6
_022153B0:
	add r0, r5, #0
	add r1, r7, #0
	bl MOD08_02227470
	cmp r0, #3
	bne _022153D4
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02227470
	cmp r0, #3
	bne _022153D4
	cmp r4, #0
	ble _022153F6
	mov r0, #0
	mvn r0, r0
	mul r4, r0
	b _022153F6
_022153D4:
	add r0, r5, #0
	add r1, r7, #0
	bl MOD08_02227470
	cmp r0, #4
	bne _022153F6
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02227470
	cmp r0, #4
	bne _022153F6
	cmp r4, #0
	bge _022153F6
	mov r0, #0
	mvn r0, r0
	mul r4, r0
_022153F6:
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _02215406
	mov r0, #0
	mvn r0, r0
	mul r4, r0
_02215406:
	lsl r0, r4, #0x18
	asr r0, r0, #0x18
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_0221540C
MOD08_0221540C: ; 0x0221540C
	push {r3, lr}
	cmp r0, r1
	bge _0221541E
	add r0, r2, #0
	bl abs
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	pop {r3, pc}
_0221541E:
	cmp r0, r1
	ble _02215430
	add r0, r2, #0
	bl abs
	neg r0, r0
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	pop {r3, pc}
_02215430:
	mov r0, #0
	pop {r3, pc}

	thumb_func_start MOD08_02215434
MOD08_02215434: ; 0x02215434
	push {r3, r4, r5, lr}
	ldr r4, [r0, #0x18]
	add r3, r0, #0
	add r4, r4, #4
	str r4, [r0, #0x18]
	ldr r5, [r4]
	add r4, r4, #4
	add r3, #0x18
	str r4, [r0, #0x18]
	cmp r5, r2
	beq _02215456
	cmp r5, r2
	beq _02215452
	bl ErrorHandling
_02215452:
	mov r0, #0
	pop {r3, r4, r5, pc}
_02215456:
	mov r4, #0
	cmp r2, #0
	ble _02215470
_0221545C:
	ldr r5, [r0, #0x18]
	add r4, r4, #1
	ldr r5, [r5]
	str r5, [r1]
	ldr r5, [r3]
	add r1, r1, #4
	add r5, r5, #4
	str r5, [r3]
	cmp r4, r2
	blt _0221545C
_02215470:
	mov r0, #1
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02215474
MOD08_02215474: ; 0x02215474
	push {r3, r4}
	add r4, r0, #0
	mov r0, #0x41
	lsl r0, r0, #2
	add r3, r1, r0
	mov r2, #6
_02215480:
	ldmia r3!, {r0, r1}
	stmia r4!, {r0, r1}
	sub r2, r2, #1
	bne _02215480
	ldr r0, [r3]
	str r0, [r4]
	pop {r3, r4}
	bx lr

	thumb_func_start MOD08_02215490
MOD08_02215490: ; 0x02215490
	add r0, #0xc0
	ldr r0, [r0]
	add r0, r0, r1
	add r0, #0xc0
	ldrb r0, [r0]
	bx lr

	thumb_func_start MOD08_0221549C
MOD08_0221549C: ; 0x0221549C
	add r0, #0xc0
	ldr r0, [r0]
	add r0, r0, r1
	add r0, #0xe0
	ldrb r0, [r0]
	bx lr

	thumb_func_start MOD08_022154A8
MOD08_022154A8: ; 0x022154A8
	add r0, #0xc0
	ldr r2, [r0]
	lsl r0, r1, #1
	add r0, r2, r0
	add r0, #0xd8
	ldrh r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_022154B8
MOD08_022154B8: ; 0x022154B8
	add r0, #0xc0
	ldr r0, [r0]
	add r0, r0, r1
	add r0, #0xe8
	ldrb r0, [r0]
	bx lr

	thumb_func_start MOD08_022154C4
MOD08_022154C4: ; 0x022154C4
	add r0, #0xc0
	ldr r2, [r0]
	lsl r0, r1, #2
	add r0, r2, r0
	add r0, #0xec
	ldr r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_022154D4
MOD08_022154D4: ; 0x022154D4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0xc0
	ldr r0, [r0]
	lsl r4, r1, #2
	add r0, r0, r4
	add r0, #0xc4
	ldr r0, [r0]
	cmp r0, #0
	bne _022154EC
	mov r0, #0
	pop {r3, r4, r5, pc}
_022154EC:
	bl FUN_02008268
	cmp r0, #0
	beq _02215500
	add r5, #0xc0
	ldr r0, [r5]
	add r0, r0, r4
	add r0, #0xc4
	ldr r0, [r0]
	pop {r3, r4, r5, pc}
_02215500:
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02215504
MOD08_02215504: ; 0x02215504
	add r0, #0xc8
	ldr r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_0221550C
MOD08_0221550C: ; 0x0221550C
	add r0, #0xc0
	ldr r2, [r0]
	lsl r0, r1, #2
	add r0, r2, r0
	add r0, #0xb0
	ldr r0, [r0]
	ldr r0, [r0, #8]
	bx lr

	thumb_func_start MOD08_0221551C
MOD08_0221551C: ; 0x0221551C
	add r0, #0xc0
	ldr r2, [r0]
	lsl r0, r1, #2
	add r0, r2, r0
	add r0, #0xb0
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bx lr

	thumb_func_start MOD08_0221552C
MOD08_0221552C: ; 0x0221552C
	add r0, #0xc0
	ldr r2, [r0]
	lsl r0, r1, #2
	add r0, r2, r0
	add r0, #0xb0
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start MOD08_0221553C
MOD08_0221553C: ; 0x0221553C
	add r0, #0xc0
	ldr r0, [r0]
	add r0, #0xd4
	ldr r1, [r0]
	mov r0, #2
	tst r0, r1
	beq _0221554E
	mov r0, #1
	bx lr
_0221554E:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02215554
MOD08_02215554: ; 0x02215554
	add r0, #0xc0
	ldr r2, [r0]
	lsl r0, r1, #2
	add r0, r2, r0
	add r0, #0xfc
	ldr r1, [r0]
	ldr r0, _02215570 ; =0x200400C0
	tst r0, r1
	beq _0221556A
	mov r0, #1
	bx lr
_0221556A:
	mov r0, #0
	bx lr
	nop
_02215570: .word 0x200400C0

	thumb_func_start MOD08_02215574
MOD08_02215574: ; 0x02215574
	push {r3, lr}
	bl MOD08_02212004
	cmp r0, #1
	bne _02215582
	mov r0, #2
	pop {r3, pc}
_02215582:
	mov r0, #1
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD08_02215588
MOD08_02215588: ; 0x02215588
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r3, _022155C0 ; =0x0222AAAC
	add r2, sp, #0
	add r5, r0, #0
	add r4, r1, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _022155B4
	add r0, sp, #0xc
	lsl r1, r4, #2
	add sp, #0x18
	ldr r0, [r0, r1]
	pop {r3, r4, r5, pc}
_022155B4:
	lsl r1, r4, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_022155C0: .word MOD8_0222AAAC

	thumb_func_start MOD08_022155C4
MOD08_022155C4: ; 0x022155C4
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r3, _022155FC ; =0x0222AA94
	add r2, sp, #0
	add r5, r0, #0
	add r4, r1, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _022155F0
	add r0, sp, #0xc
	lsl r1, r4, #2
	add sp, #0x18
	ldr r0, [r0, r1]
	pop {r3, r4, r5, pc}
_022155F0:
	lsl r1, r4, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_022155FC: .word MOD8_0222AA94

	thumb_func_start MOD08_02215600
MOD08_02215600: ; 0x02215600
	push {r3, lr}
	cmp r1, #3
	bhi _02215636
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02215612: ; jump table
	.short _0221561A - _02215612 - 2 ; case 0
	.short _02215622 - _02215612 - 2 ; case 1
	.short _0221562A - _02215612 - 2 ; case 2
	.short _02215632 - _02215612 - 2 ; case 3
_0221561A:
	bl MOD08_02212004
	mov r0, #0
	pop {r3, pc}
_02215622:
	bl MOD08_02212004
	mov r0, #1
	pop {r3, pc}
_0221562A:
	bl MOD08_02212004
	mov r0, #3
	pop {r3, pc}
_02215632:
	bl MOD08_02215574
_02215636:
	pop {r3, pc}

	thumb_func_start MOD08_02215638
MOD08_02215638: ; 0x02215638
	push {r3, lr}
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	add r0, r2, #0
	add r2, #0xc0
	ldr r3, [r2]
	mov r2, #0x11
	add r0, #0xc4
	lsl r2, r2, #4
	lsl r1, r1, #0x18
	ldr r2, [r3, r2]
	mov r3, #1
	ldr r0, [r0]
	lsr r1, r1, #0x18
	lsl r3, r3, #0x10
	bl FUN_02017E14
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD08_02215660
MOD08_02215660: ; 0x02215660
	push {r3, lr}
	mov r2, #2
	add r1, r0, #0
	lsl r2, r2, #8
	str r2, [sp]
	add r1, #0xc0
	add r0, #0xc8
	ldr r1, [r1]
	sub r2, #0xec
	ldr r1, [r1, r2]
	mov r2, #0
	ldr r0, [r0]
	add r3, r2, #0
	bl FUN_02003054
	pop {r3, pc}

	thumb_func_start MOD08_02215680
MOD08_02215680: ; 0x02215680
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD08_022132C4
	add r4, r0, #0
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _022156A8
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_022154A8
	bl MOD08_0222A6C8
	cmp r0, #1
	bne _022156A8
	mov r0, #1
	pop {r3, r4, r5, pc}
_022156A8:
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_022156AC
MOD08_022156AC: ; 0x022156AC
	mov r2, #0x14
	mul r2, r0
	ldr r0, _022156BC ; =0x0222ADC0
	lsl r1, r1, #2
	add r0, r0, r2
	ldr r0, [r1, r0]
	bx lr
	nop
_022156BC: .word MOD8_0222ADC0

	thumb_func_start MOD08_022156C0
MOD08_022156C0: ; 0x022156C0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x90
	ldr r3, _02215900 ; =0x0222AA4C
	add r6, r2, #0
	add r2, sp, #0x78
	add r7, r0, #0
	add r5, r1, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r5, #0
	mov r1, #0x58
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	str r6, [r4, #4]
	add r0, r7, #0
	bl MOD11_02230078
	str r0, [r4, #8]
	add r0, r7, #0
	bl MOD11_02230080
	str r0, [r4, #0xc]
	add r0, r7, #0
	bl MOD11_022300CC
	str r0, [r4, #0x10]
	mov r6, #0
	add r5, r4, #0
_02215704:
	mov r0, #0
	str r0, [r5, #0x24]
	add r0, r7, #0
	add r1, r6, #0
	bl MOD11_022312D0
	str r0, [r5, #0x34]
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #4
	blt _02215704
	add r1, r4, #0
	add r0, r7, #0
	add r1, #0x44
	bl MOD11_02231504
	add r1, r4, #0
	add r0, r7, #0
	add r1, #0x48
	bl MOD11_02231534
	mov r6, #0
	add r7, r6, #0
_02215732:
	ldr r0, [r4, #4]
	cmp r6, r0
	beq _0221573C
	cmp r0, #0xff
	bne _0221579E
_0221573C:
	ldr r1, _02215904 ; =0x0000D903
	str r7, [sp]
	add r2, r6, r1
	ldr r1, _02215908 ; =0x00001388
	mov r3, #0x28
	mul r1, r0
	mov r0, #1
	add r5, r2, r1
	str r0, [sp, #4]
	str r5, [sp, #8]
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	mov r2, #0x1b
	bl FUN_0200C00C
	mov r0, #0x1b
	str r0, [sp]
	mov r0, #0x27
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r5, [sp, #0x14]
	ldr r0, [r4, #0x10]
	ldr r2, [r4, #8]
	ldr r3, [r4, #0xc]
	mov r1, #2
	bl FUN_0200C0DC
	mov r0, #0
	str r0, [sp]
	str r5, [sp, #4]
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	mov r2, #0x1b
	mov r3, #0x29
	bl FUN_0200C124
	mov r0, #0
	str r0, [sp]
	str r5, [sp, #4]
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	mov r2, #0x1b
	mov r3, #0x2a
	bl FUN_0200C13C
_0221579E:
	add r6, r6, #1
	cmp r6, #4
	blt _02215732
	mov r0, #0
	str r0, [sp, #0x24]
	add r7, r4, #0
_022157AA:
	ldr r1, [r4, #4]
	ldr r0, [sp, #0x24]
	cmp r0, r1
	beq _022157B8
	cmp r1, #0xff
	beq _022157B8
	b _022158EC
_022157B8:
	ldr r2, _02215904 ; =0x0000D903
	ldr r0, [sp, #0x24]
	add r3, r1, #0
	add r0, r0, r2
	ldr r2, _02215908 ; =0x00001388
	mul r3, r2
	add r1, r0, r3
	str r1, [r7, #0x14]
	ldr r1, [r4, #4]
	add r3, r1, #0
	mul r3, r2
	add r1, r0, r3
	str r1, [sp, #0x60]
	ldr r1, [r4, #4]
	add r3, r1, #0
	mul r3, r2
	add r1, r0, r3
	str r1, [sp, #0x64]
	ldr r1, [r4, #4]
	add r3, r1, #0
	mul r3, r2
	add r1, r0, r3
	str r1, [sp, #0x68]
	ldr r1, [r4, #4]
	mul r2, r1
	mov r1, #0
	add r0, r0, r2
	str r0, [sp, #0x6c]
	str r1, [sp, #0x70]
	str r1, [sp, #0x74]
	ldr r2, [r7, #0x34]
	ldr r5, [r7, #0x48]
	ldr r0, [r2, #4]
	cmp r5, #0
	str r0, [sp, #0x20]
	ldr r0, [r2, #8]
	str r0, [sp, #0x1c]
	ldr r0, [r2]
	str r0, [sp, #0x18]
	beq _022158EC
	add r0, r5, #0
	bl FUN_0200782C
	str r0, [sp, #0x28]
	add r0, r5, #0
	mov r1, #1
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	add r0, r5, #0
	mov r1, #0x29
	bl FUN_0200782C
	sub r2, r6, r0
	ldr r0, [sp, #0x28]
	add r1, sp, #0x2c
	strh r0, [r1]
	strh r2, [r1, #2]
	mov r0, #0
	strh r0, [r1, #4]
	strh r0, [r1, #6]
	ldr r1, [sp, #0x24]
	add r3, sp, #0x2c
	add r1, r4, r1
	add r1, #0x44
	ldrb r1, [r1]
	lsl r2, r1, #2
	add r1, sp, #0x78
	ldr r1, [r1, r2]
	str r0, [sp, #0x38]
	str r1, [sp, #0x34]
	mov r1, #1
	str r1, [sp, #0x3c]
	str r1, [sp, #0x58]
	str r0, [sp, #0x5c]
	add r2, sp, #0x60
_02215852:
	ldr r1, [r2]
	add r0, r0, #1
	str r1, [r3, #0x14]
	add r2, r2, #4
	add r3, r3, #4
	cmp r0, #6
	blt _02215852
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	add r2, sp, #0x2c
	bl FUN_0200C154
	add r6, r0, #0
	bl FUN_0200C5A8
	str r6, [r7, #0x24]
	cmp r5, #0
	bne _02215880
	add r0, r6, #0
	mov r1, #0
	bl FUN_0200C644
	b _022158A8
_02215880:
	add r0, r5, #0
	bl FUN_02008268
	cmp r0, #0
	bne _02215894
	add r0, r6, #0
	mov r1, #0
	bl FUN_0200C644
	b _022158A8
_02215894:
	add r0, r5, #0
	mov r1, #6
	bl FUN_0200782C
	cmp r0, #1
	bne _022158A8
	add r0, r6, #0
	mov r1, #0
	bl FUN_0200C644
_022158A8:
	cmp r5, #0
	beq _022158C2
	ldr r0, [r6]
	bl FUN_02020350
	add r1, r0, #0
	mov r3, #0x32
	ldr r1, [r1, #4]
	ldr r2, [sp, #0x18]
	mov r0, #0x13
	lsl r3, r3, #6
	bl FUN_0201C2C8
_022158C2:
	cmp r5, #0
	beq _022158EC
	ldr r0, [r6]
	bl FUN_02020354
	mov r1, #1
	bl FUN_0201E28C
	mov r1, #2
	str r1, [sp]
	mov r1, #0x20
	lsl r0, r0, #0x14
	str r1, [sp, #4]
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	ldr r0, [r4, #0x10]
	ldr r1, [sp, #0x20]
	ldr r2, [sp, #0x1c]
	ldr r3, [r4]
	bl FUN_020030E8
_022158EC:
	ldr r0, [sp, #0x24]
	add r7, r7, #4
	add r0, r0, #1
	str r0, [sp, #0x24]
	cmp r0, #4
	bge _022158FA
	b _022157AA
_022158FA:
	add r0, r4, #0
	add sp, #0x90
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02215900: .word MOD8_0222AA4C
_02215904: .word 0x0000D903
_02215908: .word 0x00001388

	thumb_func_start MOD08_0221590C
MOD08_0221590C: ; 0x0221590C
	ldr r3, _02215914 ; =MOD08_022156C0
	mov r2, #0xff
	bx r3
	nop
_02215914: .word MOD08_022156C0

	thumb_func_start MOD08_02215918
MOD08_02215918: ; 0x02215918
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r6, #0
	add r4, r5, #0
_02215920:
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _0221593C
	ldr r0, [r5, #0xc]
	ldr r1, [r4, #0x14]
	bl FUN_0200C358
	ldr r0, [r5, #0xc]
	ldr r1, [r4, #0x14]
	bl FUN_0200C368
	ldr r0, [r4, #0x24]
	bl FUN_0200C3DC
_0221593C:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _02215920
	add r0, r5, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_0221594C
MOD08_0221594C: ; 0x0221594C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r4, #0
	add r5, r6, #0
_02215956:
	cmp r4, r7
	bne _02215976
	ldr r0, [r5, #0x24]
	cmp r0, #0
	beq _02215976
	ldr r0, [r6, #0xc]
	ldr r1, [r5, #0x14]
	bl FUN_0200C358
	ldr r0, [r6, #0xc]
	ldr r1, [r5, #0x14]
	bl FUN_0200C368
	ldr r0, [r5, #0x24]
	bl FUN_0200C3DC
_02215976:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _02215956
	add r0, r6, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02215988
MOD08_02215988: ; 0x02215988
	push {r4, lr}
	add r4, r0, #0
	bne _02215992
	bl ErrorHandling
_02215992:
	ldr r0, [r4, #4]
	add r0, r4, r0
	add r0, #0x44
	ldrb r0, [r0]
	pop {r4, pc}

	thumb_func_start MOD08_0221599C
MOD08_0221599C: ; 0x0221599C
	push {r4, lr}
	sub sp, #8
	mov r1, #0x12
	lsl r1, r1, #0xa
	add r4, r0, #0
	bl AllocFromHeap
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r3, #0x12
	ldr r0, _022159DC ; =MOD08_02215A68
	ldr r1, _022159E0 ; =MOD08_02215A84
	lsl r3, r3, #0xa
	str r4, [sp, #4]
	bl FUN_02012CDC
	add r4, r0, #0
	bl FUN_0201343C
	add r2, r0, #0
	beq _022159D4
	mov r0, #1
	mov r1, #0xe1
	lsl r0, r0, #0xc
	lsl r1, r1, #0xe
	bl FUN_0201EC94
_022159D4:
	add r0, r4, #0
	add sp, #8
	pop {r4, pc}
	nop
_022159DC: .word MOD08_02215A68
_022159E0: .word MOD08_02215A84

	thumb_func_start MOD08_022159E4
MOD08_022159E4: ; 0x022159E4
	push {r4, lr}
	sub sp, #8
	mov r1, #0x42
	lsl r1, r1, #8
	add r4, r0, #0
	bl AllocFromHeap
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r3, #0x42
	ldr r0, _02215A24 ; =MOD08_02215A68
	ldr r1, _02215A28 ; =MOD08_02215A84
	lsl r3, r3, #8
	str r4, [sp, #4]
	bl FUN_02012CDC
	add r4, r0, #0
	bl FUN_0201343C
	add r2, r0, #0
	beq _02215A1C
	mov r0, #1
	mov r1, #0xe1
	lsl r0, r0, #0xc
	lsl r1, r1, #0xe
	bl FUN_0201EC94
_02215A1C:
	add r0, r4, #0
	add sp, #8
	pop {r4, pc}
	nop
_02215A24: .word MOD08_02215A68
_02215A28: .word MOD08_02215A84

	thumb_func_start MOD08_02215A2C
MOD08_02215A2C: ; 0x02215A2C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_020133E8
	add r4, r0, #0
	add r0, r5, #0
	bl FUN_02012DE4
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02215A44
MOD08_02215A44: ; 0x02215A44
	push {r3, lr}
	bl FUN_020222AC
	bl FUN_02013348
	cmp r0, #0
	beq _02215A66
	bl FUN_02013364
	cmp r0, #0
	ble _02215A62
	bl FUN_020222AC
	bl NNS_G2dSetupSoftwareSpriteCamera
_02215A62:
	bl FUN_02013388
_02215A66:
	pop {r3, pc}

	thumb_func_start MOD08_02215A68
MOD08_02215A68: ; 0x02215A68
	push {r4, lr}
	ldr r3, _02215A80 ; =NNS_GfdDefaultFuncAllocTexVram
	mov r2, #0
	ldr r3, [r3]
	blx r3
	add r4, r0, #0
	bl FUN_0201327C
	lsl r0, r4, #0x10
	lsr r0, r0, #0xd
	pop {r4, pc}
	nop
_02215A80: .word NNS_GfdDefaultFuncAllocTexVram

	thumb_func_start MOD08_02215A84
MOD08_02215A84: ; 0x02215A84
	push {r4, lr}
	ldr r3, _02215A9C ; =NNS_GfdDefaultFuncAllocPlttVram
	mov r2, #0
	ldr r3, [r3]
	blx r3
	add r4, r0, #0
	bl FUN_020132BC
	lsl r0, r4, #0x10
	lsr r0, r0, #0xd
	pop {r4, pc}
	nop
_02215A9C: .word NNS_GfdDefaultFuncAllocPlttVram

	thumb_func_start MOD08_02215AA0
MOD08_02215AA0: ; 0x02215AA0
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02215AA4
MOD08_02215AA4: ; 0x02215AA4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	bl MOD08_0221599C
	add r4, r0, #0
	mov r0, #0x1d
	add r1, r6, #0
	add r2, r5, #0
	bl FUN_0201318C
	add r1, r0, #0
	add r0, r4, #0
	mov r2, #0xa
	add r3, r7, #0
	bl FUN_02013194
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02215ACC
MOD08_02215ACC: ; 0x02215ACC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	str r3, [sp]
	bl MOD08_0221599C
	add r4, r0, #0
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	bl FUN_0201318C
	add r1, r0, #0
	ldr r3, [sp]
	add r0, r4, #0
	mov r2, #0xa
	bl FUN_02013194
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02215AF8
MOD08_02215AF8: ; 0x02215AF8
	ldr r3, _02215AFC ; =NARC_AllocAndReadWholeMember
	bx r3
	.align 2, 0
_02215AFC: .word NARC_AllocAndReadWholeMember

	thumb_func_start MOD08_02215B00
MOD08_02215B00: ; 0x02215B00
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r7, r2, #0
	add r0, r5, #0
	str r3, [sp]
	bl MOD08_022159E4
	add r4, r0, #0
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	bl MOD08_02215AF8
	add r1, r0, #0
	ldr r3, [sp]
	add r0, r4, #0
	mov r2, #0xa
	bl FUN_02013194
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02215B2C
MOD08_02215B2C: ; 0x02215B2C
	push {r4, lr}
	lsl r4, r2, #2
	ldr r2, _02215B3C ; =0x0222B248
	ldr r2, [r2, r4]
	bl FUN_020133AC
	pop {r4, pc}
	nop
_02215B3C: .word MOD8_0222B248

	thumb_func_start MOD08_02215B40
MOD08_02215B40: ; 0x02215B40
	ldr r3, _02215B44 ; =MOD08_02215A2C
	bx r3
	.align 2, 0
_02215B44: .word MOD08_02215A2C

	thumb_func_start MOD08_02215B48
MOD08_02215B48: ; 0x02215B48
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r2, #0
	mov r4, #1
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r6, #0
	add r1, r7, #0
	bl MOD08_02227468
	cmp r5, #5
	bhi _02215B84
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02215B6E: ; jump table
	.short _02215B84 - _02215B6E - 2 ; case 0
	.short _02215B7A - _02215B6E - 2 ; case 1
	.short _02215B84 - _02215B6E - 2 ; case 2
	.short _02215B7E - _02215B6E - 2 ; case 3
	.short _02215B84 - _02215B6E - 2 ; case 4
	.short _02215B82 - _02215B6E - 2 ; case 5
_02215B7A:
	sub r4, r4, #2
	b _02215B84
_02215B7E:
	sub r4, r4, #2
	b _02215B84
_02215B82:
	sub r4, r4, #2
_02215B84:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02215B88
MOD08_02215B88: ; 0x02215B88
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02215B8C
MOD08_02215B8C: ; 0x02215B8C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r0, #0
	bl FUN_0201341C
	add r4, r0, #0
	bl MOD08_02212458
	add r0, r4, #0
	bl MOD08_02212460
	add r0, r4, #0
	bl MOD08_02212468
	add r6, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl MOD08_02227470
	cmp r0, #3
	bne _02215BC2
	add r0, r4, #0
	mov r1, #1
	add r2, sp, #0x28
	bl MOD08_0222771C
	b _02215BFA
_02215BC2:
	add r0, r4, #0
	mov r1, #1
	bl MOD08_02227468
	str r0, [sp]
	bl MOD08_02227524
	str r0, [sp, #4]
	add r0, r6, #0
	bl FUN_02013448
	add r7, r0, #0
	add r0, r4, #0
	bl MOD08_02212004
	add r4, r0, #0
	ldr r0, [sp, #4]
	add r1, sp, #0x28
	add r2, r4, #0
	add r3, r7, #0
	bl MOD08_0222765C
	ldr r0, [sp]
	add r1, sp, #0x1c
	add r2, r4, #0
	add r3, r7, #0
	bl MOD08_0222765C
_02215BFA:
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #0x28]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	add r0, r1, r0
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #0x2c]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r1, r0
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #0x30]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	add r0, r1, r0
	str r0, [r5, #0x30]
	mov r0, #1
	add r1, sp, #0x10
	bl MOD08_02227974
	add r0, r6, #0
	bl FUN_0201343C
	add r4, r0, #0
	add r0, sp, #8
	add r1, r4, #0
	bl FUN_0201F014
	add r0, sp, #8
	add r1, r4, #0
	bl FUN_0201EF90
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02215C44
MOD08_02215C44: ; 0x02215C44
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	bl FUN_0201341C
	add r4, r0, #0
	bl MOD08_02212460
	add r6, r0, #0
	add r0, r4, #0
	bl MOD08_02212468
	add r7, r0, #0
	add r0, r4, #0
	mov r1, #0
	add r2, sp, #0xc
	bl MOD08_0222771C
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	add r0, r1, r0
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #0x10]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r1, r0
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #0x14]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	add r0, r1, r0
	str r0, [r5, #0x30]
	add r0, r6, #0
	add r1, sp, #0
	bl MOD08_02227974
	add r0, r7, #0
	add r1, sp, #0
	bl FUN_020133FC
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02215CA0
MOD08_02215CA0: ; 0x02215CA0
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl FUN_0201341C
	add r5, r0, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r5, #0
	add r2, sp, #0
	bl MOD08_0222771C
	ldr r0, [r4, #0x20]
	ldr r1, [sp]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	add r0, r1, r0
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x20]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r1, r0
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x20]
	ldr r1, [sp, #8]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	add r0, r1, r0
	str r0, [r4, #0x30]
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02215CE4
MOD08_02215CE4: ; 0x02215CE4
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl FUN_0201341C
	add r5, r0, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	add r2, sp, #0
	bl MOD08_0222771C
	ldr r0, [r4, #0x20]
	ldr r1, [sp]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	add r0, r1, r0
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x20]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r1, r0
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x20]
	ldr r1, [sp, #8]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	add r0, r1, r0
	str r0, [r4, #0x30]
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02215D28
MOD08_02215D28: ; 0x02215D28
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	bl FUN_0201341C
	add r4, r0, #0
	bl MOD08_02212458
	add r6, r0, #0
	add r0, r4, #0
	bl MOD08_02212460
	add r0, r4, #0
	add r1, r6, #0
	add r2, sp, #0
	bl MOD08_0222771C
	ldr r0, [r5, #0x20]
	ldr r1, [sp]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	add r0, r1, r0
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r1, r0
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #8]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	add r0, r1, r0
	str r0, [r5, #0x30]
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_02215D74
MOD08_02215D74: ; 0x02215D74
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	bl FUN_0201341C
	add r6, r0, #0
	bl MOD08_02212468
	bl FUN_02013448
	add r7, r0, #0
	add r0, r6, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_02227470
	cmp r0, #3
	beq _02215DA0
	mov r4, #1
	b _02215DA2
_02215DA0:
	mov r4, #0
_02215DA2:
	add r0, r6, #0
	bl MOD08_02212004
	add r2, r0, #0
	add r0, r4, #0
	add r1, sp, #0
	add r3, r7, #0
	bl MOD08_0222765C
	ldr r0, [r5, #0x20]
	ldr r1, [sp]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	add r0, r1, r0
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r1, r0
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #8]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	add r0, r1, r0
	str r0, [r5, #0x30]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02215DDC
MOD08_02215DDC: ; 0x02215DDC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	bl FUN_0201341C
	add r6, r0, #0
	bl MOD08_02212468
	bl FUN_02013448
	add r7, r0, #0
	add r0, r6, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_02227470
	cmp r0, #3
	beq _02215E08
	mov r4, #1
	b _02215E0A
_02215E08:
	mov r4, #0
_02215E0A:
	add r0, r6, #0
	bl MOD08_02212004
	add r2, r0, #0
	add r0, r4, #0
	add r1, sp, #0
	add r3, r7, #0
	bl MOD08_0222765C
	ldr r0, [r5, #0x20]
	ldr r1, [sp]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	add r0, r1, r0
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r1, r0
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #8]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	add r0, r1, r0
	str r0, [r5, #0x30]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02215E44
MOD08_02215E44: ; 0x02215E44
	push {r4, r5, r6, r7, lr}
	sub sp, #0x9c
	add r5, r0, #0
	add r1, sp, #0
	mov r0, #0
	strh r0, [r1]
	strh r0, [r1, #2]
	strh r0, [r1, #4]
	strh r0, [r1, #6]
	strh r0, [r1, #8]
	strh r0, [r1, #0xa]
	ldr r3, _02215EE4 ; =0x0222B2A4
	add r2, sp, #0x54
	mov r1, #0x24
_02215E60:
	ldrh r0, [r3]
	add r3, r3, #2
	strh r0, [r2]
	add r2, r2, #2
	sub r1, r1, #1
	bne _02215E60
	ldr r3, _02215EE8 ; =0x0222B2EC
	add r2, sp, #0xc
	mov r1, #0x24
_02215E72:
	ldrh r0, [r3]
	add r3, r3, #2
	strh r0, [r2]
	add r2, r2, #2
	sub r1, r1, #1
	bne _02215E72
	bl FUN_0201341C
	add r4, r0, #0
	bl MOD08_02212458
	add r6, r0, #0
	add r0, r4, #0
	bl MOD08_02212460
	add r7, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	bl MOD08_02227468
	add r6, r0, #0
	add r0, r4, #0
	add r1, r7, #0
	bl MOD08_02227468
	lsl r2, r0, #1
	mov r0, #0xc
	add r1, r6, #0
	mul r1, r0
	add r0, sp, #0x54
	add r0, r0, r1
	ldrsh r4, [r2, r0]
	mov r3, #0xac
	add r0, r4, #0
	ldr r4, [r5, #0x20]
	mul r0, r3
	ldr r4, [r4]
	ldr r4, [r4, #4]
	add r0, r0, r4
	str r0, [r5, #0x28]
	add r0, sp, #0xc
	add r0, r0, r1
	ldrsh r0, [r2, r0]
	add r1, r0, #0
	ldr r0, [r5, #0x20]
	mul r1, r3
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r1, r0
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x20]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x30]
	add sp, #0x9c
	pop {r4, r5, r6, r7, pc}
	nop
_02215EE4: .word MOD8_0222B2A4
_02215EE8: .word MOD8_0222B2EC

	thumb_func_start MOD08_02215EEC
MOD08_02215EEC: ; 0x02215EEC
	push {r3, r4}
	add r3, r2, #0
	add r3, #8
	cmp r0, #7
	bhi _02215F7C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02215F02: ; jump table
	.short _02215F7C - _02215F02 - 2 ; case 0
	.short _02215F12 - _02215F02 - 2 ; case 1
	.short _02215F1C - _02215F02 - 2 ; case 2
	.short _02215F26 - _02215F02 - 2 ; case 3
	.short _02215F30 - _02215F02 - 2 ; case 4
	.short _02215F42 - _02215F02 - 2 ; case 5
	.short _02215F54 - _02215F02 - 2 ; case 6
	.short _02215F66 - _02215F02 - 2 ; case 7
_02215F12:
	ldr r0, [r2]
	mul r1, r0
	str r1, [r2]
	pop {r3, r4}
	bx lr
_02215F1C:
	ldr r0, [r2, #4]
	mul r1, r0
	str r1, [r2, #4]
	pop {r3, r4}
	bx lr
_02215F26:
	ldr r0, [r3]
	mul r1, r0
	str r1, [r3]
	pop {r3, r4}
	bx lr
_02215F30:
	ldr r0, [r2]
	add r3, r0, #0
	mul r3, r1
	str r3, [r2]
	ldr r0, [r2, #4]
	mul r1, r0
	str r1, [r2, #4]
	pop {r3, r4}
	bx lr
_02215F42:
	ldr r0, [r2]
	add r4, r0, #0
	mul r4, r1
	str r4, [r2]
	ldr r0, [r3]
	mul r1, r0
	str r1, [r3]
	pop {r3, r4}
	bx lr
_02215F54:
	ldr r0, [r2, #4]
	add r4, r0, #0
	mul r4, r1
	str r4, [r2, #4]
	ldr r0, [r3]
	mul r1, r0
	str r1, [r3]
	pop {r3, r4}
	bx lr
_02215F66:
	ldr r0, [r2]
	add r4, r0, #0
	mul r4, r1
	str r4, [r2]
	ldr r0, [r2, #4]
	add r4, r0, #0
	mul r4, r1
	str r4, [r2, #4]
	ldr r0, [r3]
	mul r1, r0
	str r1, [r3]
_02215F7C:
	pop {r3, r4}
	bx lr

	thumb_func_start MOD08_02215F80
MOD08_02215F80: ; 0x02215F80
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r6, r2, #0
	add r5, r1, #0
	add r1, r3, #0
	add r7, sp, #0x10
	mov r2, #0
	str r2, [r7]
	ldr r3, [sp, #0x30]
	str r2, [r7, #4]
	ldr r4, [sp, #0x38]
	str r2, [r7, #8]
	cmp r3, #5
	bhi _0221602A
	add r3, r3, r3
	add r3, pc
	ldrh r3, [r3, #6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_02215FA8: ; jump table
	.short _0221602A - _02215FA8 - 2 ; case 0
	.short _02215FB4 - _02215FA8 - 2 ; case 1
	.short _02215FDA - _02215FA8 - 2 ; case 2
	.short _02215FEE - _02215FA8 - 2 ; case 3
	.short _02215FF6 - _02215FA8 - 2 ; case 4
	.short _02216000 - _02215FA8 - 2 ; case 5
_02215FB4:
	add r0, r5, #0
	add r1, r7, #0
	bl FUN_02013628
	add r1, sp, #0x20
	mov r0, #0x14
	ldrsb r0, [r1, r0]
	ldr r1, [sp, #0x10]
	add r2, r1, #0
	mul r2, r0
	ldr r1, [sp, #0x14]
	str r2, [sp, #0x10]
	add r2, r1, #0
	mul r2, r0
	ldr r1, [sp, #0x18]
	str r2, [sp, #0x14]
	mul r0, r1
	str r0, [sp, #0x18]
	b _0221602A
_02215FDA:
	str r2, [sp, #0x10]
	add r1, sp, #0x20
	mov r0, #0x14
	ldrsb r1, [r1, r0]
	mov r0, #0x32
	lsl r0, r0, #6
	mul r0, r1
	str r0, [sp, #0x14]
	str r2, [sp, #0x18]
	b _0221602A
_02215FEE:
	add r2, r7, #0
	bl MOD08_0222771C
	b _0221602A
_02215FF6:
	add r1, r6, #0
	add r2, r7, #0
	bl MOD08_0222771C
	b _0221602A
_02216000:
	add r1, sp, #0
	str r2, [r1]
	str r2, [r1, #4]
	str r2, [r1, #8]
	str r2, [r1, #0xc]
	mov r2, #4
	bl MOD08_02215434
	ldr r0, [sp]
	add r2, sp, #0x20
	str r0, [sp, #0x10]
	ldr r0, [sp, #4]
	mov r1, #0x14
	str r0, [sp, #0x14]
	ldr r0, [sp, #8]
	str r0, [sp, #0x18]
	ldrsb r1, [r2, r1]
	ldr r0, [sp, #0xc]
	add r2, r7, #0
	bl MOD08_02215EEC
_0221602A:
	ldr r1, [sp, #0x10]
	ldr r0, [r4]
	sub r0, r1, r0
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	ldr r0, [r4, #4]
	sub r0, r1, r0
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	ldr r0, [r4, #8]
	sub r0, r1, r0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, sp, #0x10
	bl FUN_02013610
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02216050
MOD08_02216050: ; 0x02216050
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r6, r2, #0
	add r5, r1, #0
	add r1, r3, #0
	add r7, sp, #0x10
	mov r2, #0
	str r2, [r7]
	ldr r3, [sp, #0x30]
	str r2, [r7, #4]
	ldr r4, [sp, #0x38]
	str r2, [r7, #8]
	cmp r3, #5
	bhi _022160FA
	add r3, r3, r3
	add r3, pc
	ldrh r3, [r3, #6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_02216078: ; jump table
	.short _022160FA - _02216078 - 2 ; case 0
	.short _02216084 - _02216078 - 2 ; case 1
	.short _022160AA - _02216078 - 2 ; case 2
	.short _022160BE - _02216078 - 2 ; case 3
	.short _022160C6 - _02216078 - 2 ; case 4
	.short _022160D0 - _02216078 - 2 ; case 5
_02216084:
	add r0, r5, #0
	add r1, r7, #0
	bl FUN_02013548
	add r1, sp, #0x20
	mov r0, #0x14
	ldrsb r0, [r1, r0]
	ldr r1, [sp, #0x10]
	add r2, r1, #0
	mul r2, r0
	ldr r1, [sp, #0x14]
	str r2, [sp, #0x10]
	add r2, r1, #0
	mul r2, r0
	ldr r1, [sp, #0x18]
	str r2, [sp, #0x14]
	mul r0, r1
	str r0, [sp, #0x18]
	b _022160FA
_022160AA:
	str r2, [sp, #0x10]
	add r1, sp, #0x20
	mov r0, #0x14
	ldrsb r1, [r1, r0]
	mov r0, #0x32
	lsl r0, r0, #6
	mul r0, r1
	str r0, [sp, #0x14]
	str r2, [sp, #0x18]
	b _022160FA
_022160BE:
	add r2, r7, #0
	bl MOD08_0222771C
	b _022160FA
_022160C6:
	add r1, r6, #0
	add r2, r7, #0
	bl MOD08_0222771C
	b _022160FA
_022160D0:
	add r1, sp, #0
	str r2, [r1]
	str r2, [r1, #4]
	str r2, [r1, #8]
	str r2, [r1, #0xc]
	mov r2, #4
	bl MOD08_02215434
	ldr r0, [sp]
	add r2, sp, #0x20
	str r0, [sp, #0x10]
	ldr r0, [sp, #4]
	mov r1, #0x14
	str r0, [sp, #0x14]
	ldr r0, [sp, #8]
	str r0, [sp, #0x18]
	ldrsb r1, [r2, r1]
	ldr r0, [sp, #0xc]
	add r2, r7, #0
	bl MOD08_02215EEC
_022160FA:
	ldr r1, [sp, #0x10]
	ldr r0, [r4]
	sub r0, r1, r0
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	ldr r0, [r4, #4]
	sub r0, r1, r0
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	ldr r0, [r4, #8]
	sub r0, r1, r0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, sp, #0x10
	bl FUN_02013530
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02216120
MOD08_02216120: ; 0x02216120
	push {r4, r5, r6, r7, lr}
	sub sp, #0x94
	add r6, r0, #0
	add r7, r2, #0
	add r4, r1, #0
	str r3, [sp, #0xc]
	bl MOD08_02212468
	add r0, r6, #0
	add r1, r7, #0
	bl MOD08_02227468
	str r0, [sp, #0x10]
	ldr r1, [sp, #0xc]
	add r0, r6, #0
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r6, #0
	add r1, sp, #0x7c
	mov r2, #3
	bl MOD08_02215434
	add r0, r6, #0
	add r1, sp, #0x70
	mov r2, #3
	bl MOD08_02215434
	add r0, r6, #0
	add r1, sp, #0x58
	mov r2, #3
	bl MOD08_02215434
	add r0, r6, #0
	add r1, sp, #0x64
	mov r2, #3
	bl MOD08_02215434
	add r0, r6, #0
	add r1, sp, #0x40
	mov r2, #3
	bl MOD08_02215434
	add r0, r6, #0
	add r1, sp, #0x34
	mov r2, #3
	bl MOD08_02215434
	add r0, r6, #0
	add r1, sp, #0x4c
	mov r2, #3
	bl MOD08_02215434
	ldr r0, [sp, #0x10]
	cmp r0, #5
	bhi _022161A8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221619C: ; jump table
	.short _022161A8 - _0221619C - 2 ; case 0
	.short _022161B8 - _0221619C - 2 ; case 1
	.short _022161CE - _0221619C - 2 ; case 2
	.short _02216202 - _0221619C - 2 ; case 3
	.short _0221624C - _0221619C - 2 ; case 4
	.short _02216280 - _0221619C - 2 ; case 5
_022161A8:
	ldr r1, [sp, #0x7c]
	add r0, sp, #0x14
	strh r1, [r0]
	ldr r1, [sp, #0x80]
	strh r1, [r0, #2]
	ldr r1, [sp, #0x84]
	strh r1, [r0, #4]
	b _022162C8
_022161B8:
	ldr r0, [sp, #0x7c]
	neg r1, r0
	add r0, sp, #0x14
	strh r1, [r0]
	ldr r1, [sp, #0x80]
	neg r1, r1
	strh r1, [r0, #2]
	ldr r1, [sp, #0x84]
	neg r1, r1
	strh r1, [r0, #4]
	b _022162C8
_022161CE:
	cmp r5, #3
	add r0, sp, #0x14
	bne _022161E2
	ldr r1, [sp, #0x70]
	strh r1, [r0]
	ldr r1, [sp, #0x74]
	strh r1, [r0, #2]
	ldr r1, [sp, #0x78]
	strh r1, [r0, #4]
	b _022162C8
_022161E2:
	cmp r5, #5
	bne _022161F4
	ldr r1, [sp, #0x58]
	strh r1, [r0]
	ldr r1, [sp, #0x5c]
	strh r1, [r0, #2]
	ldr r1, [sp, #0x60]
	strh r1, [r0, #4]
	b _022162C8
_022161F4:
	ldr r1, [sp, #0x64]
	strh r1, [r0]
	ldr r1, [sp, #0x68]
	strh r1, [r0, #2]
	ldr r1, [sp, #0x6c]
	strh r1, [r0, #4]
	b _022162C8
_02216202:
	cmp r5, #2
	bne _0221621C
	ldr r0, [sp, #0x70]
	neg r1, r0
	add r0, sp, #0x14
	strh r1, [r0]
	ldr r1, [sp, #0x74]
	neg r1, r1
	strh r1, [r0, #2]
	ldr r1, [sp, #0x78]
	neg r1, r1
	strh r1, [r0, #4]
	b _022162C8
_0221621C:
	cmp r5, #5
	bne _02216236
	ldr r0, [sp, #0x64]
	neg r1, r0
	add r0, sp, #0x14
	strh r1, [r0]
	ldr r1, [sp, #0x68]
	neg r1, r1
	strh r1, [r0, #2]
	ldr r1, [sp, #0x6c]
	neg r1, r1
	strh r1, [r0, #4]
	b _022162C8
_02216236:
	ldr r0, [sp, #0x40]
	neg r1, r0
	add r0, sp, #0x14
	strh r1, [r0]
	ldr r1, [sp, #0x44]
	neg r1, r1
	strh r1, [r0, #2]
	ldr r1, [sp, #0x48]
	neg r1, r1
	strh r1, [r0, #4]
	b _022162C8
_0221624C:
	cmp r5, #3
	add r0, sp, #0x14
	bne _02216260
	ldr r1, [sp, #0x40]
	strh r1, [r0]
	ldr r1, [sp, #0x44]
	strh r1, [r0, #2]
	ldr r1, [sp, #0x48]
	strh r1, [r0, #4]
	b _022162C8
_02216260:
	cmp r5, #5
	bne _02216272
	ldr r1, [sp, #0x34]
	strh r1, [r0]
	ldr r1, [sp, #0x38]
	strh r1, [r0, #2]
	ldr r1, [sp, #0x3c]
	strh r1, [r0, #4]
	b _022162C8
_02216272:
	ldr r1, [sp, #0x4c]
	strh r1, [r0]
	ldr r1, [sp, #0x50]
	strh r1, [r0, #2]
	ldr r1, [sp, #0x54]
	strh r1, [r0, #4]
	b _022162C8
_02216280:
	cmp r5, #3
	bne _0221629A
	ldr r0, [sp, #0x4c]
	neg r1, r0
	add r0, sp, #0x14
	strh r1, [r0]
	ldr r1, [sp, #0x50]
	neg r1, r1
	strh r1, [r0, #2]
	ldr r1, [sp, #0x54]
	neg r1, r1
	strh r1, [r0, #4]
	b _022162C8
_0221629A:
	cmp r5, #2
	bne _022162B4
	ldr r0, [sp, #0x58]
	neg r1, r0
	add r0, sp, #0x14
	strh r1, [r0]
	ldr r1, [sp, #0x5c]
	neg r1, r1
	strh r1, [r0, #2]
	ldr r1, [sp, #0x60]
	neg r1, r1
	strh r1, [r0, #4]
	b _022162C8
_022162B4:
	ldr r0, [sp, #0x34]
	neg r1, r0
	add r0, sp, #0x14
	strh r1, [r0]
	ldr r1, [sp, #0x38]
	neg r1, r1
	strh r1, [r0, #2]
	ldr r1, [sp, #0x3c]
	neg r1, r1
	strh r1, [r0, #4]
_022162C8:
	ldr r2, [sp, #0xc]
	add r0, r6, #0
	add r1, r7, #0
	bl MOD08_02215B48
	add r5, r0, #0
	add r1, sp, #0x28
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	add r0, r6, #0
	mov r2, #3
	bl MOD08_02215434
	add r0, r6, #0
	add r1, r7, #0
	add r2, sp, #0x1c
	bl MOD08_0222771C
	ldr r0, [sp, #0x28]
	cmp r0, #0
	bne _02216334
	ldr r0, [sp, #0x2c]
	cmp r0, #0
	bne _02216334
	ldr r0, [sp, #0x30]
	cmp r0, #0
	bne _02216334
	add r3, sp, #0x1c
	ldmia r3!, {r0, r1}
	add r2, sp, #0x88
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r1, [r4, #0x20]
	ldr r0, [sp, #0x1c]
	ldr r1, [r1]
	ldr r1, [r1, #4]
	add r0, r0, r1
	str r0, [r4, #0x28]
	ldr r1, [r4, #0x20]
	ldr r0, [sp, #0x20]
	ldr r1, [r1]
	ldr r1, [r1, #8]
	add r0, r0, r1
	str r0, [r4, #0x2c]
	ldr r1, [r4, #0x20]
	ldr r0, [sp, #0x24]
	ldr r1, [r1]
	ldr r1, [r1, #0xc]
	add r0, r0, r1
	str r0, [r4, #0x30]
	b _02216388
_02216334:
	ldr r2, [sp, #0x28]
	ldr r1, [sp, #0x2c]
	ldr r0, [sp, #0x30]
	str r2, [sp, #0x88]
	str r1, [sp, #0x8c]
	str r0, [sp, #0x90]
	cmp r2, #0
	bne _0221634E
	mov r0, #0x32
	lsl r0, r0, #6
	cmp r1, r0
	bne _0221634E
	mov r5, #1
_0221634E:
	ldr r1, [sp, #0x88]
	add r0, r1, #0
	ldr r1, [sp, #0x8c]
	mul r0, r5
	add r2, r1, #0
	mul r2, r5
	ldr r1, [sp, #0x24]
	str r2, [sp, #0x8c]
	add r2, r1, #0
	mul r2, r5
	str r0, [sp, #0x88]
	str r2, [sp, #0x90]
	ldr r1, [r4, #0x20]
	ldr r1, [r1]
	ldr r1, [r1, #4]
	add r0, r0, r1
	str r0, [r4, #0x28]
	ldr r1, [r4, #0x20]
	ldr r0, [sp, #0x8c]
	ldr r1, [r1]
	ldr r1, [r1, #8]
	add r0, r0, r1
	str r0, [r4, #0x2c]
	ldr r1, [r4, #0x20]
	ldr r0, [sp, #0x90]
	ldr r1, [r1]
	ldr r1, [r1, #0xc]
	add r0, r0, r1
	str r0, [r4, #0x30]
_02216388:
	ldr r0, [sp, #0xa8]
	cmp r0, #0
	beq _022163C6
	cmp r0, #1
	beq _02216398
	cmp r0, #2
	beq _022163B0
	b _022163C6
_02216398:
	ldr r0, [sp, #0xac]
	ldr r3, [sp, #0xc]
	str r0, [sp]
	str r5, [sp, #4]
	add r0, sp, #0x88
	str r0, [sp, #8]
	add r0, r6, #0
	add r1, r4, #0
	add r2, r7, #0
	bl MOD08_02215F80
	b _022163C6
_022163B0:
	ldr r0, [sp, #0xac]
	ldr r3, [sp, #0xc]
	str r0, [sp]
	str r5, [sp, #4]
	add r0, sp, #0x88
	str r0, [sp, #8]
	add r0, r6, #0
	add r1, r4, #0
	add r2, r7, #0
	bl MOD08_02216050
_022163C6:
	add r1, sp, #0x14
	ldrh r2, [r1]
	add r0, r4, #0
	add r0, #0x50
	strh r2, [r0]
	add r0, r4, #0
	ldrh r2, [r1, #2]
	add r0, #0x52
	add r4, #0x54
	strh r2, [r0]
	ldrh r0, [r1, #4]
	strh r0, [r4]
	add sp, #0x94
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_022163E4
MOD08_022163E4: ; 0x022163E4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r0, #0
	add r5, r1, #0
	add r4, r2, #0
	bl FUN_0201341C
	add r6, r0, #0
	bl MOD08_02212458
	str r0, [sp, #8]
	add r0, r6, #0
	bl MOD08_02212460
	add r3, r0, #0
	str r5, [sp]
	ldr r2, [sp, #8]
	add r0, r6, #0
	add r1, r7, #0
	str r4, [sp, #4]
	bl MOD08_02216120
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02216414
MOD08_02216414: ; 0x02216414
	ldr r3, _0221641C ; =MOD08_022163E4
	mov r1, #0
	add r2, r1, #0
	bx r3
	.align 2, 0
_0221641C: .word MOD08_022163E4

	thumb_func_start MOD08_02216420
MOD08_02216420: ; 0x02216420
	ldr r3, _02216428 ; =MOD08_022163E4
	mov r1, #1
	add r2, r1, #0
	bx r3
	.align 2, 0
_02216428: .word MOD08_022163E4

	thumb_func_start MOD08_0221642C
MOD08_0221642C: ; 0x0221642C
	ldr r3, _02216434 ; =MOD08_022163E4
	mov r1, #1
	mov r2, #2
	bx r3
	.align 2, 0
_02216434: .word MOD08_022163E4

	thumb_func_start MOD08_02216438
MOD08_02216438: ; 0x02216438
	ldr r3, _02216440 ; =MOD08_022163E4
	mov r1, #1
	mov r2, #3
	bx r3
	.align 2, 0
_02216440: .word MOD08_022163E4

	thumb_func_start MOD08_02216444
MOD08_02216444: ; 0x02216444
	ldr r3, _0221644C ; =MOD08_022163E4
	mov r1, #1
	mov r2, #4
	bx r3
	.align 2, 0
_0221644C: .word MOD08_022163E4

	thumb_func_start MOD08_02216450
MOD08_02216450: ; 0x02216450
	ldr r3, _02216458 ; =MOD08_022163E4
	mov r1, #1
	mov r2, #5
	bx r3
	.align 2, 0
_02216458: .word MOD08_022163E4

	thumb_func_start MOD08_0221645C
MOD08_0221645C: ; 0x0221645C
	ldr r3, _02216464 ; =MOD08_022163E4
	mov r1, #2
	mov r2, #1
	bx r3
	.align 2, 0
_02216464: .word MOD08_022163E4

	thumb_func_start MOD08_02216468
MOD08_02216468: ; 0x02216468
	ldr r3, _02216470 ; =MOD08_022163E4
	mov r1, #2
	add r2, r1, #0
	bx r3
	.align 2, 0
_02216470: .word MOD08_022163E4

	thumb_func_start MOD08_02216474
MOD08_02216474: ; 0x02216474
	ldr r3, _0221647C ; =MOD08_022163E4
	mov r1, #2
	mov r2, #3
	bx r3
	.align 2, 0
_0221647C: .word MOD08_022163E4

	thumb_func_start MOD08_02216480
MOD08_02216480: ; 0x02216480
	ldr r3, _02216488 ; =MOD08_022163E4
	mov r1, #2
	mov r2, #4
	bx r3
	.align 2, 0
_02216488: .word MOD08_022163E4

	thumb_func_start MOD08_0221648C
MOD08_0221648C: ; 0x0221648C
	ldr r3, _02216494 ; =MOD08_022163E4
	mov r1, #2
	mov r2, #5
	bx r3
	.align 2, 0
_02216494: .word MOD08_022163E4

	thumb_func_start MOD08_02216498
MOD08_02216498: ; 0x02216498
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	bl FUN_0201341C
	add r4, r0, #0
	bl MOD08_02212458
	add r6, r0, #0
	add r0, r4, #0
	bl MOD08_02212460
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r5, #0
	add r3, r6, #0
	bl MOD08_02216120
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_022164C8
MOD08_022164C8: ; 0x022164C8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r2, [r4, #0x14]
	add r5, r0, #0
	cmp r2, #0
	beq _022164D8
	bl MOD08_0221658C
_022164D8:
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _022164E6
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_022168C0
_022164E6:
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _022164F4
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02217124
_022164F4:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02217158
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _0221650A
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02217168
_0221650A:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_0221650C
MOD08_0221650C: ; 0x0221650C
	push {r3, r4, r5, r6, r7, lr}
	ldr r4, [r1]
	add r6, r2, #0
	add r0, r4, #0
	bl MOD08_02212468
	bl FUN_02013448
	add r7, r0, #0
	add r0, r4, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r4, #0
	bl MOD08_02227470
	cmp r0, #3
	beq _02216534
	mov r5, #1
	b _02216536
_02216534:
	mov r5, #0
_02216536:
	add r0, r4, #0
	bl MOD08_02212004
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	add r3, r7, #0
	bl MOD08_0222765C
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_0221654C
MOD08_0221654C: ; 0x0221654C
	push {r3, r4, r5, r6, r7, lr}
	ldr r4, [r1]
	add r6, r2, #0
	add r0, r4, #0
	bl MOD08_02212468
	bl FUN_02013448
	add r7, r0, #0
	add r0, r4, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r4, #0
	bl MOD08_02227470
	cmp r0, #3
	beq _02216574
	mov r5, #1
	b _02216576
_02216574:
	mov r5, #0
_02216576:
	add r0, r4, #0
	bl MOD08_02212004
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	add r3, r7, #0
	bl MOD08_0222765C
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_0221658C
MOD08_0221658C: ; 0x0221658C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xbc
	add r4, r1, #0
	ldr r2, [r4, #0x14]
	add r5, r0, #0
	cmp r2, #0x64
	bgt _022165F4
	blt _0221659E
	b _02216768
_0221659E:
	cmp r2, #0x22
	bhi _022165FA
	add r3, r2, r2
	add r3, pc
	ldrh r3, [r3, #6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_022165AE: ; jump table
	.short _02216872 - _022165AE - 2 ; case 0
	.short _022165FC - _022165AE - 2 ; case 1
	.short _02216608 - _022165AE - 2 ; case 2
	.short _02216704 - _022165AE - 2 ; case 3
	.short _02216740 - _022165AE - 2 ; case 4
	.short _02216754 - _022165AE - 2 ; case 5
	.short _02216614 - _022165AE - 2 ; case 6
	.short _02216620 - _022165AE - 2 ; case 7
	.short _022166EC - _022165AE - 2 ; case 8
	.short _022166F8 - _022165AE - 2 ; case 9
	.short _0221662C - _022165AE - 2 ; case 10
	.short _02216638 - _022165AE - 2 ; case 11
	.short _02216794 - _022165AE - 2 ; case 12
	.short _022167A4 - _022165AE - 2 ; case 13
	.short _02216644 - _022165AE - 2 ; case 14
	.short _02216650 - _022165AE - 2 ; case 15
	.short _0221665C - _022165AE - 2 ; case 16
	.short _02216668 - _022165AE - 2 ; case 17
	.short _02216674 - _022165AE - 2 ; case 18
	.short _02216680 - _022165AE - 2 ; case 19
	.short _0221668C - _022165AE - 2 ; case 20
	.short _02216698 - _022165AE - 2 ; case 21
	.short _022166A4 - _022165AE - 2 ; case 22
	.short _022166B0 - _022165AE - 2 ; case 23
	.short _022166BC - _022165AE - 2 ; case 24
	.short _022166C8 - _022165AE - 2 ; case 25
	.short _022166D4 - _022165AE - 2 ; case 26
	.short _022166E0 - _022165AE - 2 ; case 27
	.short _022167B4 - _022165AE - 2 ; case 28
	.short _02216872 - _022165AE - 2 ; case 29
	.short _02216804 - _022165AE - 2 ; case 30
	.short _022167DA - _022165AE - 2 ; case 31
	.short _0221683C - _022165AE - 2 ; case 32
	.short _022167C0 - _022165AE - 2 ; case 33
	.short _022167CE - _022165AE - 2 ; case 34
_022165F4:
	cmp r2, #0x65
	bne _022165FA
	b _0221677E
_022165FA:
	b _02216872
_022165FC:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	add r2, sp, #0xb0
	bl MOD08_0222771C
	b _02216872
_02216608:
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	add r2, sp, #0xb0
	bl MOD08_0222771C
	b _02216872
_02216614:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	add r2, sp, #0xb0
	bl MOD08_0222774C
	b _02216872
_02216620:
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	add r2, sp, #0xb0
	bl MOD08_0222774C
	b _02216872
_0221662C:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	add r2, sp, #0xb0
	bl MOD08_0222777C
	b _02216872
_02216638:
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	add r2, sp, #0xb0
	bl MOD08_0222777C
	b _02216872
_02216644:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	add r2, sp, #0xb0
	bl MOD08_022277AC
	b _02216872
_02216650:
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	add r2, sp, #0xb0
	bl MOD08_022277AC
	b _02216872
_0221665C:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	add r2, sp, #0xb0
	bl MOD08_022277DC
	b _02216872
_02216668:
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	add r2, sp, #0xb0
	bl MOD08_022277DC
	b _02216872
_02216674:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	add r2, sp, #0xb0
	bl MOD08_0222780C
	b _02216872
_02216680:
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	add r2, sp, #0xb0
	bl MOD08_0222780C
	b _02216872
_0221668C:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	add r2, sp, #0xb0
	bl MOD08_0222783C
	b _02216872
_02216698:
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	add r2, sp, #0xb0
	bl MOD08_0222783C
	b _02216872
_022166A4:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	add r2, sp, #0xb0
	bl MOD08_0222786C
	b _02216872
_022166B0:
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	add r2, sp, #0xb0
	bl MOD08_0222786C
	b _02216872
_022166BC:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	add r2, sp, #0xb0
	bl MOD08_0222789C
	b _02216872
_022166C8:
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	add r2, sp, #0xb0
	bl MOD08_0222789C
	b _02216872
_022166D4:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	add r2, sp, #0xb0
	bl MOD08_022278CC
	b _02216872
_022166E0:
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	add r2, sp, #0xb0
	bl MOD08_022278CC
	b _02216872
_022166EC:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	add r2, sp, #0xb0
	bl MOD08_0222792C
	b _02216872
_022166F8:
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	add r2, sp, #0xb0
	bl MOD08_0222792C
	b _02216872
_02216704:
	ldr r0, [r4]
	add r1, sp, #0xa0
	mov r2, #4
	bl MOD08_02215434
	add r0, r4, #0
	bl MOD08_0221727C
	strb r0, [r4, #8]
	ldr r0, [sp, #0xa4]
	str r0, [sp, #0xb0]
	ldr r0, [sp, #0xa8]
	str r0, [sp, #0xb4]
	ldr r0, [sp, #0xac]
	str r0, [sp, #0xb8]
	ldr r0, [sp, #0xa0]
	cmp r0, #1
	bne _0221672C
	mov r0, #1
	strb r0, [r4, #8]
_0221672C:
	mov r0, #8
	ldrsb r1, [r4, r0]
	ldr r2, [sp, #0xb0]
	mul r1, r2
	str r1, [sp, #0xb0]
	ldrsb r0, [r4, r0]
	ldr r1, [sp, #0xb4]
	mul r0, r1
	str r0, [sp, #0xb4]
	b _02216872
_02216740:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	add r2, sp, #0xb0
	bl MOD08_0222771C
	add r0, r4, #0
	add r1, sp, #0xb0
	bl MOD08_0221734C
	b _02216872
_02216754:
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	add r2, sp, #0xb0
	bl MOD08_0222771C
	add r0, r4, #0
	add r1, sp, #0xb0
	bl MOD08_0221734C
	b _02216872
_02216768:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	add r2, sp, #0xb0
	bl MOD08_0222771C
	ldr r1, [r4, #0x24]
	add r0, r4, #0
	add r2, sp, #0xb0
	bl MOD08_022172C0
	b _02216872
_0221677E:
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	add r2, sp, #0xb0
	bl MOD08_0222771C
	ldr r1, [r4, #0x28]
	add r0, r4, #0
	add r2, sp, #0xb0
	bl MOD08_022172C0
	b _02216872
_02216794:
	add r2, sp, #0xb0
	bl MOD08_0221654C
	add r0, r4, #0
	add r1, sp, #0xb0
	bl MOD08_0221734C
	b _02216872
_022167A4:
	add r2, sp, #0xb0
	bl MOD08_0221650C
	add r0, r4, #0
	add r1, sp, #0xb0
	bl MOD08_0221734C
	b _02216872
_022167B4:
	ldr r0, _022168A8 ; =0x00002CE0
	str r0, [sp, #0xb0]
	mov r0, #0
	str r0, [sp, #0xb4]
	str r0, [sp, #0xb8]
	b _02216872
_022167C0:
	ldr r0, _022168AC ; =0xFFFFEC78
	str r0, [sp, #0xb0]
	ldr r0, _022168B0 ; =0xFFFFE890
	str r0, [sp, #0xb4]
	mov r0, #0
	str r0, [sp, #0xb8]
	b _02216872
_022167CE:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	add r2, sp, #0xb0
	bl MOD08_0222771C
	b _02216872
_022167DA:
	ldr r6, _022168B4 ; =0x0222B344
	add r3, sp, #0x70
	mov r2, #6
_022167E0:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _022167E0
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	bl MOD08_02227468
	lsl r1, r0, #3
	add r0, sp, #0x70
	ldr r0, [r0, r1]
	str r0, [sp, #0xb0]
	add r0, sp, #0x74
	ldr r0, [r0, r1]
	str r0, [sp, #0xb4]
	mov r0, #0
	str r0, [sp, #0xb8]
	b _02216872
_02216804:
	ldr r6, _022168B8 ; =0x0222B3DC
	add r3, sp, #0x38
	mov r2, #7
_0221680A:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0221680A
	ldr r0, [r4]
	bl MOD08_02212004
	cmp r0, #1
	bne _02216820
	mov r0, #6
	b _02216828
_02216820:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	bl MOD08_02227468
_02216828:
	lsl r1, r0, #3
	add r0, sp, #0x38
	ldr r0, [r0, r1]
	str r0, [sp, #0xb0]
	add r0, sp, #0x3c
	ldr r0, [r0, r1]
	str r0, [sp, #0xb4]
	mov r0, #0
	str r0, [sp, #0xb8]
	b _02216872
_0221683C:
	ldr r6, _022168BC ; =0x0222B3A4
	add r3, sp, #0
	mov r2, #7
_02216842:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02216842
	ldr r0, [r4]
	bl MOD08_02212004
	cmp r0, #1
	bne _02216858
	mov r0, #6
	b _02216860
_02216858:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	bl MOD08_02227468
_02216860:
	lsl r1, r0, #3
	add r0, sp, #0
	ldr r0, [r0, r1]
	str r0, [sp, #0xb0]
	add r0, sp, #4
	ldr r0, [r0, r1]
	str r0, [sp, #0xb4]
	mov r0, #0
	str r0, [sp, #0xb8]
_02216872:
	add r2, sp, #0xb0
	ldmia r2!, {r0, r1}
	add r4, #0x2c
	stmia r4!, {r0, r1}
	ldr r0, [r2]
	str r0, [r4]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #0xb0]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	add r0, r1, r0
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #0xb4]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r1, r0
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #0xb8]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	add r0, r1, r0
	str r0, [r5, #0x30]
	add sp, #0xbc
	pop {r3, r4, r5, r6, pc}
	nop
_022168A8: .word 0x00002CE0
_022168AC: .word 0xFFFFEC78
_022168B0: .word 0xFFFFE890
_022168B4: .word MOD8_0222B344
_022168B8: .word MOD8_0222B3DC
_022168BC: .word MOD8_0222B3A4

	thumb_func_start MOD08_022168C0
MOD08_022168C0: ; 0x022168C0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x148
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r1]
	ldr r1, [r1, #0x24]
	bl MOD08_02227468
	str r0, [sp, #0x18]
	ldr r0, [sp, #4]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r1, [r1, #0x28]
	bl MOD08_02227468
	str r0, [sp, #0x14]
	ldr r0, [sp, #4]
	ldr r0, [r0, #0x18]
	cmp r0, #0x1a
	bls _022168EC
	bl _022170F2
_022168EC:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022168F8: ; jump table
	.short _0221692E - _022168F8 - 2 ; case 0
	.short _0221693A - _022168F8 - 2 ; case 1
	.short _0221693A - _022168F8 - 2 ; case 2
	.short _02217024 - _022168F8 - 2 ; case 3
	.short _022169A2 - _022168F8 - 2 ; case 4
	.short _02216A5C - _022168F8 - 2 ; case 5
	.short _02216D90 - _022168F8 - 2 ; case 6
	.short _02216D90 - _022168F8 - 2 ; case 7
	.short _02216B16 - _022168F8 - 2 ; case 8
	.short _02216B16 - _022168F8 - 2 ; case 9
	.short _02216B7E - _022168F8 - 2 ; case 10
	.short _02216B7E - _022168F8 - 2 ; case 11
	.short _02216BCC - _022168F8 - 2 ; case 12
	.short _02216BCC - _022168F8 - 2 ; case 13
	.short _02216C14 - _022168F8 - 2 ; case 14
	.short _02216C14 - _022168F8 - 2 ; case 15
	.short _02216C5C - _022168F8 - 2 ; case 16
	.short _02216C5C - _022168F8 - 2 ; case 17
	.short _02216D00 - _022168F8 - 2 ; case 18
	.short _02216D00 - _022168F8 - 2 ; case 19
	.short _02216D48 - _022168F8 - 2 ; case 20
	.short _02216D48 - _022168F8 - 2 ; case 21
	.short _02217038 - _022168F8 - 2 ; case 22
	.short _022170F2 - _022168F8 - 2 ; case 23
	.short _022170C4 - _022168F8 - 2 ; case 24
	.short _02217080 - _022168F8 - 2 ; case 25
	.short _02217092 - _022168F8 - 2 ; case 26
_0221692E:
	mov r1, #0
	add r0, sp, #0x20
	strh r1, [r0]
	strh r1, [r0, #2]
	strh r1, [r0, #4]
	b _022170F2
_0221693A:
	ldr r0, [sp, #4]
	ldr r0, [r0]
	bl MOD08_02212004
	cmp r0, #1
	bne _02216974
	ldr r0, [sp, #4]
	ldr r0, [r0, #0x10]
	cmp r0, #2
	add r0, sp, #0x20
	bne _02216962
	ldr r1, _02216CA4 ; =0xFFFFF2F8
	strh r1, [r0]
	mov r1, #0x73
	lsl r1, r1, #4
	strh r1, [r0, #2]
	mov r1, #0x2e
	lsl r1, r1, #4
	strh r1, [r0, #4]
	b _022170F2
_02216962:
	mov r1, #0x92
	lsl r1, r1, #4
	strh r1, [r0]
	ldr r1, _02216CA8 ; =0xFFFFFA60
	strh r1, [r0, #2]
	mov r1, #0x2e
	lsl r1, r1, #4
	strh r1, [r0, #4]
	b _022170F2
_02216974:
	ldr r0, [sp, #0x14]
	mov r1, #0xc
	mul r1, r0
	ldr r2, [sp, #0x18]
	mov r0, #0x48
	mul r0, r2
	ldr r2, _02216CAC ; =0x0222BB44
	add r2, r2, r0
	ldr r3, [r1, r2]
	add r2, sp, #0x20
	strh r3, [r2]
	ldr r3, _02216CB0 ; =0x0222BB48
	add r3, r3, r0
	ldr r3, [r1, r3]
	strh r3, [r2, #2]
	ldr r3, _02216CB4 ; =0x0222BB4C
	add r0, r3, r0
	ldr r1, [r1, r0]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	strh r0, [r2, #4]
	b _022170F2
_022169A2:
	ldr r0, [sp, #4]
	ldr r0, [r0]
	bl MOD08_02212004
	cmp r0, #1
	bne _022169DE
	ldr r0, [sp, #0x14]
	mov r1, #0xc
	mul r1, r0
	ldr r2, [sp, #0x18]
	mov r0, #0x48
	mul r0, r2
	ldr r2, _02216CAC ; =0x0222BB44
	add r2, r2, r0
	ldr r2, [r1, r2]
	neg r3, r2
	add r2, sp, #0x20
	strh r3, [r2]
	ldr r3, _02216CB0 ; =0x0222BB48
	add r3, r3, r0
	ldr r3, [r1, r3]
	strh r3, [r2, #2]
	ldr r3, _02216CB4 ; =0x0222BB4C
	add r0, r3, r0
	ldr r1, [r1, r0]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	strh r0, [r2, #4]
	b _022170F2
_022169DE:
	ldr r0, [sp, #4]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r1, [r1, #0x24]
	bl MOD08_02227470
	add r4, r0, #0
	ldr r0, [sp, #4]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r1, [r1, #0x28]
	bl MOD08_02227470
	cmp r4, r0
	bne _02216A2A
	ldr r0, [sp, #0x14]
	mov r1, #0xc
	mul r1, r0
	ldr r2, [sp, #0x18]
	mov r0, #0x48
	mul r0, r2
	ldr r2, _02216CAC ; =0x0222BB44
	add r2, r2, r0
	ldr r3, [r1, r2]
	add r2, sp, #0x20
	strh r3, [r2]
	ldr r3, _02216CB0 ; =0x0222BB48
	add r3, r3, r0
	ldr r3, [r1, r3]
	strh r3, [r2, #2]
	ldr r3, _02216CB4 ; =0x0222BB4C
	add r0, r3, r0
	ldr r1, [r1, r0]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	strh r0, [r2, #4]
	b _022170F2
_02216A2A:
	ldr r0, [sp, #4]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r1, [r1, #0x24]
	bl MOD08_02227470
	cmp r0, #3
	add r0, sp, #0x20
	bne _02216A4E
	mov r1, #0x3b
	lsl r1, r1, #6
	strh r1, [r0]
	mov r1, #0x21
	lsl r1, r1, #6
	strh r1, [r0, #2]
	ldr r1, _02216CB8 ; =0x000005FC
	strh r1, [r0, #4]
	b _022170F2
_02216A4E:
	ldr r1, _02216CBC ; =0xFFFFEF7C
	strh r1, [r0]
	ldr r1, _02216CC0 ; =0xFFFFF558
	strh r1, [r0, #2]
	ldr r1, _02216CB8 ; =0x000005FC
	strh r1, [r0, #4]
	b _022170F2
_02216A5C:
	ldr r0, [sp, #4]
	ldr r0, [r0]
	bl MOD08_02212004
	cmp r0, #1
	bne _02216A98
	ldr r0, [sp, #0x14]
	mov r1, #0xc
	mul r1, r0
	ldr r2, [sp, #0x18]
	mov r0, #0x48
	mul r0, r2
	ldr r2, _02216CAC ; =0x0222BB44
	add r2, r2, r0
	ldr r2, [r1, r2]
	neg r3, r2
	add r2, sp, #0x20
	strh r3, [r2]
	ldr r3, _02216CB0 ; =0x0222BB48
	add r3, r3, r0
	ldr r3, [r1, r3]
	strh r3, [r2, #2]
	ldr r3, _02216CB4 ; =0x0222BB4C
	add r0, r3, r0
	ldr r1, [r1, r0]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	strh r0, [r2, #4]
	b _022170F2
_02216A98:
	ldr r0, [sp, #4]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r1, [r1, #0x24]
	bl MOD08_02227470
	add r4, r0, #0
	ldr r0, [sp, #4]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r1, [r1, #0x28]
	bl MOD08_02227470
	cmp r4, r0
	bne _02216AE4
	ldr r0, [sp, #0x14]
	mov r1, #0xc
	mul r1, r0
	ldr r2, [sp, #0x18]
	mov r0, #0x48
	mul r0, r2
	ldr r2, _02216CAC ; =0x0222BB44
	add r2, r2, r0
	ldr r3, [r1, r2]
	add r2, sp, #0x20
	strh r3, [r2]
	ldr r3, _02216CB0 ; =0x0222BB48
	add r3, r3, r0
	ldr r3, [r1, r3]
	strh r3, [r2, #2]
	ldr r3, _02216CB4 ; =0x0222BB4C
	add r0, r3, r0
	ldr r1, [r1, r0]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	strh r0, [r2, #4]
	b _022170F2
_02216AE4:
	ldr r0, [sp, #4]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r1, [r1, #0x24]
	bl MOD08_02227470
	cmp r0, #3
	add r0, sp, #0x20
	bne _02216B08
	mov r1, #0x3b
	lsl r1, r1, #6
	strh r1, [r0]
	mov r1, #0x21
	lsl r1, r1, #6
	strh r1, [r0, #2]
	ldr r1, _02216CB8 ; =0x000005FC
	strh r1, [r0, #4]
	b _022170F2
_02216B08:
	ldr r1, _02216CBC ; =0xFFFFEF7C
	strh r1, [r0]
	ldr r1, _02216CC0 ; =0xFFFFF558
	strh r1, [r0, #2]
	ldr r1, _02216CB8 ; =0x000005FC
	strh r1, [r0, #4]
	b _022170F2
_02216B16:
	ldr r0, [sp, #4]
	ldr r0, [r0]
	bl MOD08_02212004
	cmp r0, #1
	bne _02216B50
	ldr r0, [sp, #4]
	ldr r0, [r0, #0x10]
	cmp r0, #2
	add r0, sp, #0x20
	bne _02216B3E
	ldr r1, _02216CC4 ; =0xFFFFF6E0
	strh r1, [r0]
	mov r1, #0x5a
	lsl r1, r1, #4
	strh r1, [r0, #2]
	mov r1, #0x2e
	lsl r1, r1, #4
	strh r1, [r0, #4]
	b _022170F2
_02216B3E:
	mov r1, #0x92
	lsl r1, r1, #4
	strh r1, [r0]
	ldr r1, _02216CA8 ; =0xFFFFFA60
	strh r1, [r0, #2]
	mov r1, #0x2e
	lsl r1, r1, #4
	strh r1, [r0, #4]
	b _022170F2
_02216B50:
	ldr r0, [sp, #0x14]
	mov r1, #0xc
	mul r1, r0
	ldr r2, [sp, #0x18]
	mov r0, #0x48
	mul r0, r2
	ldr r2, _02216CC8 ; =0x0222B484
	add r2, r2, r0
	ldr r3, [r1, r2]
	add r2, sp, #0x20
	strh r3, [r2]
	ldr r3, _02216CCC ; =0x0222B488
	add r3, r3, r0
	ldr r3, [r1, r3]
	strh r3, [r2, #2]
	ldr r3, _02216CD0 ; =0x0222B48C
	add r0, r3, r0
	ldr r1, [r1, r0]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	strh r0, [r2, #4]
	b _022170F2
_02216B7E:
	ldr r0, [sp, #4]
	ldr r0, [r0]
	bl MOD08_02212004
	cmp r0, #1
	bne _02216B9E
	ldr r1, _02216CC4 ; =0xFFFFF6E0
	add r0, sp, #0x20
	strh r1, [r0]
	mov r1, #0x5a
	lsl r1, r1, #4
	strh r1, [r0, #2]
	mov r1, #0x2e
	lsl r1, r1, #4
	strh r1, [r0, #4]
	b _022170F2
_02216B9E:
	ldr r0, [sp, #0x14]
	mov r1, #0xc
	mul r1, r0
	ldr r2, [sp, #0x18]
	mov r0, #0x48
	mul r0, r2
	ldr r2, _02216CD4 ; =0x0222B634
	add r2, r2, r0
	ldr r3, [r1, r2]
	add r2, sp, #0x20
	strh r3, [r2]
	ldr r3, _02216CCC ; =0x0222B488
	add r3, r3, r0
	ldr r3, [r1, r3]
	strh r3, [r2, #2]
	ldr r3, _02216CD0 ; =0x0222B48C
	add r0, r3, r0
	ldr r1, [r1, r0]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	strh r0, [r2, #4]
	b _022170F2
_02216BCC:
	ldr r0, [sp, #4]
	ldr r0, [r0]
	bl MOD08_02212004
	cmp r0, #1
	bne _02216BEC
	ldr r1, _02216CD8 ; =0xFFFFF488
	add r0, sp, #0x20
	strh r1, [r0]
	mov r1, #0x5a
	lsl r1, r1, #4
	strh r1, [r0, #2]
	mov r1, #0x2e
	lsl r1, r1, #4
	strh r1, [r0, #4]
	b _022170F2
_02216BEC:
	ldr r0, [sp, #0x14]
	mov r1, #0xc
	mul r1, r0
	ldr r2, [sp, #0x18]
	mov r0, #0x48
	mul r0, r2
	ldr r2, _02216CDC ; =0x0222B994
	add r2, r2, r0
	ldr r3, [r1, r2]
	add r2, sp, #0x20
	strh r3, [r2]
	ldr r3, _02216CE0 ; =0x0222B998
	add r3, r3, r0
	ldr r3, [r1, r3]
	strh r3, [r2, #2]
	ldr r3, _02216CE4 ; =0x0222B99C
	add r0, r3, r0
	ldr r0, [r1, r0]
	strh r0, [r2, #4]
	b _022170F2
_02216C14:
	ldr r0, [sp, #4]
	ldr r0, [r0]
	bl MOD08_02212004
	cmp r0, #1
	bne _02216C34
	ldr r1, _02216CC4 ; =0xFFFFF6E0
	add r0, sp, #0x20
	strh r1, [r0]
	mov r1, #0x5a
	lsl r1, r1, #4
	strh r1, [r0, #2]
	mov r1, #0x2e
	lsl r1, r1, #4
	strh r1, [r0, #4]
	b _022170F2
_02216C34:
	ldr r0, [sp, #0x14]
	mov r1, #0xc
	mul r1, r0
	ldr r2, [sp, #0x18]
	mov r0, #0x48
	mul r0, r2
	ldr r2, _02216CE8 ; =0x0222BCF4
	add r2, r2, r0
	ldr r3, [r1, r2]
	add r2, sp, #0x20
	strh r3, [r2]
	ldr r3, _02216CEC ; =0x0222BCF8
	add r3, r3, r0
	ldr r3, [r1, r3]
	strh r3, [r2, #2]
	ldr r3, _02216CF0 ; =0x0222BCFC
	add r0, r3, r0
	ldr r0, [r1, r0]
	strh r0, [r2, #4]
	b _022170F2
_02216C5C:
	ldr r0, [sp, #4]
	ldr r0, [r0]
	bl MOD08_02212004
	cmp r0, #1
	bne _02216C7C
	ldr r1, _02216CC4 ; =0xFFFFF6E0
	add r0, sp, #0x20
	strh r1, [r0]
	mov r1, #0x5a
	lsl r1, r1, #4
	strh r1, [r0, #2]
	mov r1, #0x2e
	lsl r1, r1, #4
	strh r1, [r0, #4]
	b _022170F2
_02216C7C:
	ldr r0, [sp, #0x14]
	mov r1, #0xc
	mul r1, r0
	ldr r2, [sp, #0x18]
	mov r0, #0x48
	mul r0, r2
	ldr r2, _02216CF4 ; =0x0222B7E4
	add r2, r2, r0
	ldr r3, [r1, r2]
	add r2, sp, #0x20
	strh r3, [r2]
	ldr r3, _02216CF8 ; =0x0222B7E8
	add r3, r3, r0
	ldr r3, [r1, r3]
	strh r3, [r2, #2]
	ldr r3, _02216CFC ; =0x0222B7EC
	add r0, r3, r0
	ldr r0, [r1, r0]
	strh r0, [r2, #4]
	b _022170F2
	.align 2, 0
_02216CA4: .word 0xFFFFF2F8
_02216CA8: .word 0xFFFFFA60
_02216CAC: .word MOD8_0222BB44
_02216CB0: .word MOD8_0222BB48
_02216CB4: .word MOD8_0222BB4C
_02216CB8: .word 0x000005FC
_02216CBC: .word 0xFFFFEF7C
_02216CC0: .word 0xFFFFF558
_02216CC4: .word 0xFFFFF6E0
_02216CC8: .word MOD8_0222B484
_02216CCC: .word MOD8_0222B488
_02216CD0: .word MOD8_0222B48C
_02216CD4: .word MOD8_0222B634
_02216CD8: .word 0xFFFFF488
_02216CDC: .word MOD8_0222B994
_02216CE0: .word MOD8_0222B998
_02216CE4: .word MOD8_0222B99C
_02216CE8: .word MOD8_0222BCF4
_02216CEC: .word MOD8_0222BCF8
_02216CF0: .word MOD8_0222BCFC
_02216CF4: .word MOD8_0222B7E4
_02216CF8: .word MOD8_0222B7E8
_02216CFC: .word MOD8_0222B7EC
_02216D00:
	ldr r0, [sp, #4]
	ldr r0, [r0]
	bl MOD08_02212004
	cmp r0, #1
	bne _02216D20
	ldr r1, _02217044 ; =0xFFFFF6E0
	add r0, sp, #0x20
	strh r1, [r0]
	mov r1, #0x5a
	lsl r1, r1, #4
	strh r1, [r0, #2]
	mov r1, #0x2e
	lsl r1, r1, #4
	strh r1, [r0, #4]
	b _022170F2
_02216D20:
	ldr r0, [sp, #0x14]
	mov r1, #0xc
	mul r1, r0
	ldr r2, [sp, #0x18]
	mov r0, #0x48
	mul r0, r2
	ldr r2, _02217048 ; =0x0222BEA4
	add r2, r2, r0
	ldr r3, [r1, r2]
	add r2, sp, #0x20
	strh r3, [r2]
	ldr r3, _0221704C ; =0x0222BEA8
	add r3, r3, r0
	ldr r3, [r1, r3]
	strh r3, [r2, #2]
	ldr r3, _02217050 ; =0x0222BEAC
	add r0, r3, r0
	ldr r0, [r1, r0]
	strh r0, [r2, #4]
	b _022170F2
_02216D48:
	ldr r0, [sp, #4]
	ldr r0, [r0]
	bl MOD08_02212004
	cmp r0, #1
	bne _02216D68
	ldr r1, _02217054 ; =0xFFFFEF10
	add r0, sp, #0x20
	strh r1, [r0]
	mov r1, #0x5a
	lsl r1, r1, #4
	strh r1, [r0, #2]
	mov r1, #0x2e
	lsl r1, r1, #4
	strh r1, [r0, #4]
	b _022170F2
_02216D68:
	ldr r0, [sp, #0x14]
	mov r1, #0xc
	mul r1, r0
	ldr r2, [sp, #0x18]
	mov r0, #0x48
	mul r0, r2
	ldr r2, _02217058 ; =0x0222C054
	add r2, r2, r0
	ldr r3, [r1, r2]
	add r2, sp, #0x20
	strh r3, [r2]
	ldr r3, _0221705C ; =0x0222C058
	add r3, r3, r0
	ldr r3, [r1, r3]
	strh r3, [r2, #2]
	ldr r3, _02217060 ; =0x0222C05C
	add r0, r3, r0
	ldr r0, [r1, r0]
	strh r0, [r2, #4]
	b _022170F2
_02216D90:
	ldr r4, _02217064 ; =0x0222B414
	add r3, sp, #0xd8
	mov r2, #0xe
_02216D96:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02216D96
	ldr r3, _02217068 ; =0x0222B334
	add r2, sp, #0x58
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r1, sp, #0xc8
	mov r0, #0
	str r1, [sp, #0xc]
	add r1, sp, #0xb8
	mov ip, r0
	str r1, [sp, #0x1c]
	add r0, sp, #0xd8
	add r7, sp, #0xa8
	add r6, sp, #0x98
	add r5, sp, #0x88
	add r1, sp, #0x78
	add r2, sp, #0x68
_02216DC2:
	ldr r4, [r0]
	ldr r3, [sp, #0xc]
	str r4, [r3]
	ldr r4, [r0, #0x10]
	ldr r3, [sp, #0x1c]
	str r4, [r3]
	ldr r3, [r0, #0x20]
	stmia r7!, {r3}
	ldr r3, [r0, #0x30]
	stmia r6!, {r3}
	ldr r3, [r0, #0x40]
	stmia r5!, {r3}
	ldr r3, [r0, #0x50]
	stmia r1!, {r3}
	ldr r3, [r0, #0x60]
	add r0, r0, #4
	stmia r2!, {r3}
	ldr r3, [sp, #0xc]
	add r3, r3, #4
	str r3, [sp, #0xc]
	ldr r3, [sp, #0x1c]
	add r3, r3, #4
	str r3, [sp, #0x1c]
	mov r3, ip
	add r3, r3, #1
	mov ip, r3
	cmp r3, #4
	blt _02216DC2
	ldr r0, [sp, #4]
	ldr r0, [r0]
	bl MOD08_02212004
	cmp r0, #1
	bne _02216E3E
	mov r0, #0
	str r0, [sp, #8]
	add r0, sp, #0x58
	str r0, [sp, #0x10]
	add r7, sp, #0xc8
	add r6, sp, #0xb8
	add r0, sp, #0xa8
	add r1, sp, #0x98
	add r2, sp, #0x88
	add r3, sp, #0x78
	add r4, sp, #0x68
_02216E1C:
	ldr r5, [sp, #0x10]
	ldr r5, [r5]
	stmia r7!, {r5}
	stmia r6!, {r5}
	stmia r0!, {r5}
	stmia r1!, {r5}
	stmia r2!, {r5}
	stmia r3!, {r5}
	stmia r4!, {r5}
	ldr r5, [sp, #0x10]
	add r5, r5, #4
	str r5, [sp, #0x10]
	ldr r5, [sp, #8]
	add r5, r5, #1
	str r5, [sp, #8]
	cmp r5, #4
	blt _02216E1C
_02216E3E:
	ldr r0, [sp, #0x18]
	cmp r0, #5
	bhi _02216E5C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02216E50: ; jump table
	.short _02216E5C - _02216E50 - 2 ; case 0
	.short _02216E6C - _02216E50 - 2 ; case 1
	.short _02216E98 - _02216E50 - 2 ; case 2
	.short _02216ED0 - _02216E50 - 2 ; case 3
	.short _02216F5E - _02216E50 - 2 ; case 4
	.short _02216F96 - _02216E50 - 2 ; case 5
_02216E5C:
	ldr r1, [sp, #0xc8]
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0xcc]
	strh r1, [r0, #2]
	ldr r1, [sp, #0xd0]
	strh r1, [r0, #4]
	b _022170F2
_02216E6C:
	ldr r0, [sp, #0xd4]
	cmp r0, #1
	bne _02216E82
	ldr r1, [sp, #0xc8]
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0xcc]
	strh r1, [r0, #2]
	ldr r1, [sp, #0xd0]
	strh r1, [r0, #4]
	b _022170F2
_02216E82:
	ldr r0, [sp, #0xc8]
	neg r1, r0
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0xcc]
	neg r1, r1
	strh r1, [r0, #2]
	ldr r1, [sp, #0xd0]
	neg r1, r1
	strh r1, [r0, #4]
	b _022170F2
_02216E98:
	ldr r0, [sp, #0x14]
	cmp r0, #3
	bne _02216EAE
	ldr r1, [sp, #0xb8]
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0xbc]
	strh r1, [r0, #2]
	ldr r1, [sp, #0xc0]
	strh r1, [r0, #4]
	b _022170F2
_02216EAE:
	cmp r0, #5
	add r0, sp, #0x20
	bne _02216EC2
	ldr r1, [sp, #0x98]
	strh r1, [r0]
	ldr r1, [sp, #0x9c]
	strh r1, [r0, #2]
	ldr r1, [sp, #0xa0]
	strh r1, [r0, #4]
	b _022170F2
_02216EC2:
	ldr r1, [sp, #0xa8]
	strh r1, [r0]
	ldr r1, [sp, #0xac]
	strh r1, [r0, #2]
	ldr r1, [sp, #0xb0]
	strh r1, [r0, #4]
	b _022170F2
_02216ED0:
	ldr r0, [sp, #0x14]
	cmp r0, #2
	bne _02216F02
	ldr r0, [sp, #0xc4]
	cmp r0, #1
	bne _02216EEC
	ldr r1, [sp, #0xb8]
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0xbc]
	strh r1, [r0, #2]
	ldr r1, [sp, #0xc0]
	strh r1, [r0, #4]
	b _022170F2
_02216EEC:
	ldr r0, [sp, #0xb8]
	neg r1, r0
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0xbc]
	neg r1, r1
	strh r1, [r0, #2]
	ldr r1, [sp, #0xc0]
	neg r1, r1
	strh r1, [r0, #4]
	b _022170F2
_02216F02:
	cmp r0, #5
	bne _02216F32
	ldr r0, [sp, #0xb4]
	cmp r0, #1
	bne _02216F22
	ldr r0, [sp, #0x88]
	neg r1, r0
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0x8c]
	neg r1, r1
	strh r1, [r0, #2]
	ldr r1, [sp, #0x90]
	neg r1, r1
	strh r1, [r0, #4]
	b _022170F2
_02216F22:
	ldr r1, [sp, #0x88]
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0x8c]
	strh r1, [r0, #2]
	ldr r1, [sp, #0x90]
	strh r1, [r0, #4]
	b _022170F2
_02216F32:
	ldr r0, [sp, #0x84]
	cmp r0, #1
	bne _02216F48
	ldr r1, [sp, #0x78]
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0x7c]
	strh r1, [r0, #2]
	ldr r1, [sp, #0x80]
	strh r1, [r0, #4]
	b _022170F2
_02216F48:
	ldr r0, [sp, #0x78]
	neg r1, r0
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0x7c]
	neg r1, r1
	strh r1, [r0, #2]
	ldr r1, [sp, #0x80]
	neg r1, r1
	strh r1, [r0, #4]
	b _022170F2
_02216F5E:
	ldr r0, [sp, #0x14]
	cmp r0, #3
	bne _02216F74
	ldr r1, [sp, #0x78]
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0x7c]
	strh r1, [r0, #2]
	ldr r1, [sp, #0x80]
	strh r1, [r0, #4]
	b _022170F2
_02216F74:
	cmp r0, #5
	add r0, sp, #0x20
	bne _02216F88
	ldr r1, [sp, #0x68]
	strh r1, [r0]
	ldr r1, [sp, #0x6c]
	strh r1, [r0, #2]
	ldr r1, [sp, #0x70]
	strh r1, [r0, #4]
	b _022170F2
_02216F88:
	ldr r1, [sp, #0x88]
	strh r1, [r0]
	ldr r1, [sp, #0x8c]
	strh r1, [r0, #2]
	ldr r1, [sp, #0x90]
	strh r1, [r0, #4]
	b _022170F2
_02216F96:
	ldr r0, [sp, #0x14]
	cmp r0, #3
	bne _02216FC8
	ldr r0, [sp, #0xc4]
	cmp r0, #1
	bne _02216FB2
	ldr r1, [sp, #0x88]
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0x8c]
	strh r1, [r0, #2]
	ldr r1, [sp, #0x90]
	strh r1, [r0, #4]
	b _022170F2
_02216FB2:
	ldr r0, [sp, #0x88]
	neg r1, r0
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0x8c]
	neg r1, r1
	strh r1, [r0, #2]
	ldr r1, [sp, #0x90]
	neg r1, r1
	strh r1, [r0, #4]
	b _022170F2
_02216FC8:
	cmp r0, #2
	bne _02216FF8
	ldr r0, [sp, #0xc4]
	cmp r0, #1
	bne _02216FE2
	ldr r1, [sp, #0x98]
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0x9c]
	strh r1, [r0, #2]
	ldr r1, [sp, #0xa0]
	strh r1, [r0, #4]
	b _022170F2
_02216FE2:
	ldr r0, [sp, #0x98]
	neg r1, r0
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0x9c]
	neg r1, r1
	strh r1, [r0, #2]
	ldr r1, [sp, #0xa0]
	neg r1, r1
	strh r1, [r0, #4]
	b _022170F2
_02216FF8:
	ldr r0, [sp, #0xc4]
	cmp r0, #1
	bne _0221700E
	ldr r1, [sp, #0x68]
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0x6c]
	strh r1, [r0, #2]
	ldr r1, [sp, #0x70]
	strh r1, [r0, #4]
	b _022170F2
_0221700E:
	ldr r0, [sp, #0x68]
	neg r1, r0
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, [sp, #0x6c]
	neg r1, r1
	strh r1, [r0, #2]
	ldr r1, [sp, #0x70]
	neg r1, r1
	strh r1, [r0, #4]
	b _022170F2
_02217024:
	ldr r1, _0221706C ; =0xFFFFFCE0
	add r0, sp, #0x20
	strh r1, [r0]
	mov r1, #0x4b
	lsl r1, r1, #4
	strh r1, [r0, #2]
	mov r1, #0x7d
	lsl r1, r1, #2
	strh r1, [r0, #4]
	b _022170F2
_02217038:
	ldr r1, _02217070 ; =0xFFFFF2AE
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r1, _02217074 ; =0xFFFFF5AC
	b _02217078
	nop
_02217044: .word 0xFFFFF6E0
_02217048: .word MOD8_0222BEA4
_0221704C: .word MOD8_0222BEA8
_02217050: .word MOD8_0222BEAC
_02217054: .word 0xFFFFEF10
_02217058: .word MOD8_0222C054
_0221705C: .word MOD8_0222C058
_02217060: .word MOD8_0222C05C
_02217064: .word MOD8_0222B414
_02217068: .word MOD8_0222B334
_0221706C: .word 0xFFFFFCE0
_02217070: .word 0xFFFFF2AE
_02217074: .word 0xFFFFF5AC
_02217078:
	strh r1, [r0, #2]
	mov r1, #0
	strh r1, [r0, #4]
	b _022170F2
_02217080:
	ldr r1, _02217114 ; =0xFFFFF290
	add r0, sp, #0x20
	strh r1, [r0]
	mov r1, #0x7a
	lsl r1, r1, #4
	strh r1, [r0, #2]
	mov r1, #0
	strh r1, [r0, #4]
	b _022170F2
_02217092:
	ldr r0, [sp, #4]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r1, [r1, #0x24]
	bl MOD08_02227470
	cmp r0, #3
	add r0, sp, #0x20
	bne _022170B6
	mov r1, #0x3b
	lsl r1, r1, #6
	strh r1, [r0]
	mov r1, #0x21
	lsl r1, r1, #6
	strh r1, [r0, #2]
	mov r1, #0
	strh r1, [r0, #4]
	b _022170F2
_022170B6:
	ldr r1, _02217118 ; =0xFFFFE890
	strh r1, [r0]
	ldr r1, _0221711C ; =0xFFFFF768
	strh r1, [r0, #2]
	mov r1, #0
	strh r1, [r0, #4]
	b _022170F2
_022170C4:
	ldr r4, _02217120 ; =0x0222B374
	add r3, sp, #0x28
	mov r2, #6
_022170CA:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _022170CA
	ldr r0, [sp, #4]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r1, [r1, #0x24]
	bl MOD08_02227468
	lsl r2, r0, #3
	add r0, sp, #0x28
	ldr r1, [r0, r2]
	add r0, sp, #0x20
	strh r1, [r0]
	add r1, sp, #0x2c
	ldr r1, [r1, r2]
	strh r1, [r0, #2]
	mov r1, #0
	strh r1, [r0, #4]
_022170F2:
	add r1, sp, #0x20
	ldr r0, [sp]
	ldrh r2, [r1]
	add r0, #0x50
	strh r2, [r0]
	ldr r0, [sp]
	ldrh r2, [r1, #2]
	add r0, #0x52
	strh r2, [r0]
	ldr r0, [sp]
	ldrh r1, [r1, #4]
	add r0, #0x54
	str r0, [sp]
	strh r1, [r0]
	add sp, #0x148
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02217114: .word 0xFFFFF290
_02217118: .word 0xFFFFE890
_0221711C: .word 0xFFFFF768
_02217120: .word MOD8_0222B374

	thumb_func_start MOD08_02217124
MOD08_02217124: ; 0x02217124
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	bl MOD08_022178CC
	add r6, r0, #0
	mov r4, #0
	cmp r6, #0
	ble _02217154
_02217136:
	add r0, r4, #0
	bl MOD08_022178A4
	ldr r1, [r5, #0x1c]
	and r1, r0
	cmp r0, r1
	bne _0221714E
	add r0, r4, #0
	add r1, r7, #0
	add r2, r5, #0
	bl MOD08_0221788C
_0221714E:
	add r4, r4, #1
	cmp r4, r6
	blt _02217136
_02217154:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02217158
MOD08_02217158: ; 0x02217158
	add r3, r0, #0
	add r2, r1, #0
	add r1, r3, #0
	ldr r3, _02217164 ; =MOD08_02217B04
	ldr r0, [r2, #0x20]
	bx r3
	.align 2, 0
_02217164: .word MOD08_02217B04

	thumb_func_start MOD08_02217168
MOD08_02217168: ; 0x02217168
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	bl MOD08_02227468
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	bl MOD08_02227468
	ldr r1, [r4, #0xc]
	cmp r1, #3
	bhi _022171B0
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02217190: ; jump table
	.short _022171B0 - _02217190 - 2 ; case 0
	.short _02217198 - _02217190 - 2 ; case 1
	.short _022171A6 - _02217190 - 2 ; case 2
	.short _022171B0 - _02217190 - 2 ; case 3
_02217198:
	cmp r0, #0
	bne _022171A2
	mov r5, #1
	lsl r5, r5, #8
	b _022171B0
_022171A2:
	ldr r5, _022171C4 ; =0xFFFFEC00
	b _022171B0
_022171A6:
	cmp r0, #0
	bne _022171AE
	mov r5, #0
	b _022171B0
_022171AE:
	ldr r5, _022171C8 ; =0xFFFFEB00
_022171B0:
	ldr r0, [r4, #4]
	bl FUN_02013448
	ldr r0, [r6, #0x20]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	add r0, r5, r0
	str r0, [r6, #0x30]
	pop {r4, r5, r6, pc}
	nop
_022171C4: .word 0xFFFFEC00
_022171C8: .word 0xFFFFEB00

	thumb_func_start MOD08_022171CC
MOD08_022171CC: ; 0x022171CC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl FUN_0201341C
	add r5, r0, #0
	bl MOD08_02212014
	mov r1, #0x38
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	add r0, r5, #0
	bl MOD08_02212468
	str r0, [r4, #4]
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0xc
	mov r2, #6
	bl MOD08_02215434
	ldr r0, [r4, #0x10]
	cmp r0, #4
	bhi _02217214
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221720A: ; jump table
	.short _02217214 - _0221720A - 2 ; case 0
	.short _02217226 - _0221720A - 2 ; case 1
	.short _02217238 - _0221720A - 2 ; case 2
	.short _0221724A - _0221720A - 2 ; case 3
	.short _0221725C - _0221720A - 2 ; case 4
_02217214:
	ldr r0, [r4]
	bl MOD08_02212458
	str r0, [r4, #0x24]
	ldr r0, [r4]
	bl MOD08_02212460
	str r0, [r4, #0x28]
	b _0221726C
_02217226:
	ldr r0, [r4]
	bl MOD08_02212460
	str r0, [r4, #0x24]
	ldr r0, [r4]
	bl MOD08_02212458
	str r0, [r4, #0x28]
	b _0221726C
_02217238:
	ldr r0, [r4]
	bl MOD08_02212458
	str r0, [r4, #0x24]
	ldr r0, [r4]
	bl MOD08_02212460
	str r0, [r4, #0x28]
	b _0221726C
_0221724A:
	ldr r0, [r4]
	bl MOD08_02212460
	str r0, [r4, #0x24]
	ldr r0, [r4]
	bl MOD08_02212458
	str r0, [r4, #0x28]
	b _0221726C
_0221725C:
	ldr r0, [r4]
	bl MOD08_02212458
	str r0, [r4, #0x24]
	ldr r0, [r4]
	bl MOD08_02212460
	str r0, [r4, #0x28]
_0221726C:
	add r0, r6, #0
	add r1, r4, #0
	bl MOD08_022164C8
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_0221727C
MOD08_0221727C: ; 0x0221727C
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, [r6]
	ldr r1, [r6, #0x24]
	mov r4, #1
	bl MOD08_02227468
	add r5, r0, #0
	ldr r0, [r6]
	ldr r1, [r6, #0x28]
	bl MOD08_02227468
	cmp r5, #5
	bhi _022172BA
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022172A4: ; jump table
	.short _022172BA - _022172A4 - 2 ; case 0
	.short _022172B0 - _022172A4 - 2 ; case 1
	.short _022172BA - _022172A4 - 2 ; case 2
	.short _022172B4 - _022172A4 - 2 ; case 3
	.short _022172BA - _022172A4 - 2 ; case 4
	.short _022172B8 - _022172A4 - 2 ; case 5
_022172B0:
	sub r4, r4, #2
	b _022172BA
_022172B4:
	sub r4, r4, #2
	b _022172BA
_022172B8:
	sub r4, r4, #2
_022172BA:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_022172C0
MOD08_022172C0: ; 0x022172C0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r5, r0, #0
	add r0, sp, #0x20
	mov r4, #0
	str r4, [r0]
	str r4, [r0, #4]
	add r6, r1, #0
	add r7, r2, #0
	str r4, [r0, #8]
_022172D4:
	ldr r0, [r5]
	add r1, r6, #0
	bl MOD08_02227468
	cmp r4, r0
	ldr r0, [r5]
	bne _022172EC
	add r1, sp, #0x10
	mov r2, #4
	bl MOD08_02215434
	b _022172F4
_022172EC:
	add r1, sp, #0
	mov r2, #4
	bl MOD08_02215434
_022172F4:
	add r4, r4, #1
	cmp r4, #6
	blt _022172D4
	add r0, r5, #0
	bl MOD08_0221727C
	strb r0, [r5, #8]
	ldr r0, [sp, #0x14]
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x18]
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x1c]
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x10]
	cmp r0, #1
	bne _02217318
	mov r0, #1
	strb r0, [r5, #8]
_02217318:
	mov r1, #8
	ldrsb r0, [r5, r1]
	ldr r2, [sp, #0x20]
	ldr r3, [sp, #0x24]
	mul r0, r2
	str r0, [sp, #0x20]
	ldrsb r2, [r5, r1]
	mul r2, r3
	str r2, [sp, #0x24]
	ldrsb r1, [r5, r1]
	ldr r2, [sp, #0x28]
	mul r1, r2
	str r1, [sp, #0x28]
	ldr r1, [r7]
	add r0, r1, r0
	str r0, [r7]
	ldr r1, [r7, #4]
	ldr r0, [sp, #0x24]
	add r0, r1, r0
	str r0, [r7, #4]
	ldr r1, [r7, #8]
	ldr r0, [sp, #0x28]
	add r0, r1, r0
	str r0, [r7, #8]
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD08_0221734C
MOD08_0221734C: ; 0x0221734C
	push {r4, r5, lr}
	sub sp, #0x1c
	add r5, r0, #0
	add r4, r1, #0
	add r1, sp, #0
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	ldr r0, [r5]
	add r1, sp, #0xc
	mov r2, #4
	bl MOD08_02215434
	add r0, r5, #0
	bl MOD08_0221727C
	strb r0, [r5, #8]
	ldr r0, [sp, #0x10]
	str r0, [sp]
	ldr r0, [sp, #0x14]
	str r0, [sp, #4]
	ldr r0, [sp, #0x18]
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	cmp r0, #1
	bne _02217386
	mov r0, #1
	strb r0, [r5, #8]
_02217386:
	mov r1, #8
	ldrsb r0, [r5, r1]
	ldr r2, [sp]
	ldr r3, [sp, #4]
	mul r0, r2
	str r0, [sp]
	ldrsb r2, [r5, r1]
	mul r2, r3
	str r2, [sp, #4]
	ldrsb r1, [r5, r1]
	ldr r2, [sp, #8]
	mul r1, r2
	str r1, [sp, #8]
	ldr r1, [r4]
	add r0, r1, r0
	str r0, [r4]
	ldr r1, [r4, #4]
	ldr r0, [sp, #4]
	add r0, r1, r0
	str r0, [r4, #4]
	ldr r1, [r4, #8]
	ldr r0, [sp, #8]
	add r0, r1, r0
	str r0, [r4, #8]
	add sp, #0x1c
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_022173BC
MOD08_022173BC: ; 0x022173BC
	ldr r3, _022173C4 ; =MOD08_02215434
	ldr r0, [r0]
	mov r2, #5
	bx r3
	.align 2, 0
_022173C4: .word MOD08_02215434

	thumb_func_start MOD08_022173C8
MOD08_022173C8: ; 0x022173C8
	mov r0, #1
	bx lr

	thumb_func_start MOD08_022173CC
MOD08_022173CC: ; 0x022173CC
	push {r4, r5, lr}
	sub sp, #0x1c
	add r5, r0, #0
	add r4, r1, #0
	add r1, sp, #0
	mov r0, #0
	strh r0, [r1]
	strh r0, [r1, #2]
	strh r0, [r1, #4]
	add r0, r4, #0
	add r1, sp, #8
	bl MOD08_022173BC
	add r0, r4, #0
	bl MOD08_0221727C
	strb r0, [r4, #8]
	ldr r0, [sp, #0xc]
	cmp r0, #1
	bne _022173F8
	mov r0, #1
	strb r0, [r4, #8]
_022173F8:
	ldr r0, [sp, #8]
	cmp r0, #3
	bgt _02217416
	cmp r0, #0
	blt _02217482
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0221740E: ; jump table
	.short _0221741A - _0221740E - 2 ; case 0
	.short _02217446 - _0221740E - 2 ; case 1
	.short _02217482 - _0221740E - 2 ; case 2
	.short _02217482 - _0221740E - 2 ; case 3
_02217416:
	cmp r0, #0xff
	b _02217482
_0221741A:
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_02013514
	add r2, sp, #0
	mov r0, #0
	mov r1, #8
	ldrsh r3, [r2, r0]
	ldrsb r0, [r4, r1]
	mul r0, r3
	strh r0, [r2]
	mov r0, #2
	ldrsh r3, [r2, r0]
	ldrsb r0, [r4, r1]
	mul r0, r3
	strh r0, [r2, #2]
	mov r0, #4
	ldrsh r3, [r2, r0]
	ldrsb r0, [r4, r1]
	mul r0, r3
	strh r0, [r2, #4]
	b _02217482
_02217446:
	ldr r0, [sp, #0x10]
	add r2, sp, #0
	strh r0, [r2]
	ldr r0, [sp, #0x14]
	mov r1, #8
	strh r0, [r2, #2]
	ldr r0, [sp, #0x18]
	strh r0, [r2, #4]
	mov r0, #0
	ldrsh r3, [r2, r0]
	ldrsb r0, [r4, r1]
	mul r0, r3
	strh r0, [r2]
	mov r0, #2
	ldrsh r3, [r2, r0]
	ldrsb r0, [r4, r1]
	mul r0, r3
	strh r0, [r2, #2]
	mov r0, #4
	ldrsh r3, [r2, r0]
	ldrsb r0, [r4, r1]
	add r1, sp, #0
	mul r0, r3
	strh r0, [r2, #4]
	add r0, r5, #0
	bl FUN_02013514
	add sp, #0x1c
	mov r0, #1
	pop {r4, r5, pc}
_02217482:
	add r1, sp, #0
	mov r0, #0
	ldrsh r2, [r1, r0]
	ldr r0, [r4, #0x2c]
	sub r0, r2, r0
	strh r0, [r1]
	mov r0, #2
	ldrsh r2, [r1, r0]
	ldr r0, [r4, #0x30]
	sub r0, r2, r0
	strh r0, [r1, #2]
	mov r0, #4
	ldrsh r2, [r1, r0]
	ldr r0, [r4, #0x34]
	sub r0, r2, r0
	strh r0, [r1, #4]
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_02013514
	mov r0, #1
	add sp, #0x1c
	pop {r4, r5, pc}

	thumb_func_start MOD08_022174B0
MOD08_022174B0: ; 0x022174B0
	mov r0, #1
	bx lr

	thumb_func_start MOD08_022174B4
MOD08_022174B4: ; 0x022174B4
	mov r0, #1
	bx lr

	thumb_func_start MOD08_022174B8
MOD08_022174B8: ; 0x022174B8
	push {r4, r5, r6, lr}
	sub sp, #0x20
	add r5, r0, #0
	add r4, r1, #0
	add r1, sp, #0
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	add r0, r4, #0
	add r1, sp, #0xc
	bl MOD08_022173BC
	add r0, r4, #0
	bl MOD08_0221727C
	strb r0, [r4, #8]
	ldr r0, [sp, #0x10]
	cmp r0, #1
	bne _022174E4
	mov r0, #1
	strb r0, [r4, #8]
_022174E4:
	ldr r0, [sp, #0xc]
	cmp r0, #3
	bgt _02217502
	cmp r0, #0
	blt _02217562
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022174FA: ; jump table
	.short _02217506 - _022174FA - 2 ; case 0
	.short _0221752A - _022174FA - 2 ; case 1
	.short _0221754C - _022174FA - 2 ; case 2
	.short _02217558 - _022174FA - 2 ; case 3
_02217502:
	cmp r0, #0xff
	b _02217562
_02217506:
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_02013548
	mov r0, #8
	ldrsb r1, [r4, r0]
	ldr r2, [sp]
	mul r1, r2
	str r1, [sp]
	ldrsb r1, [r4, r0]
	ldr r2, [sp, #4]
	mul r1, r2
	str r1, [sp, #4]
	ldrsb r0, [r4, r0]
	ldr r1, [sp, #8]
	mul r0, r1
	str r0, [sp, #8]
	b _02217562
_0221752A:
	ldr r2, [sp, #0x14]
	ldr r1, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	str r2, [sp]
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #8
	ldrsb r6, [r4, r3]
	mul r6, r2
	str r6, [sp]
	ldrsb r2, [r4, r3]
	mul r2, r1
	str r2, [sp, #4]
	ldrsb r1, [r4, r3]
	mul r1, r0
	str r1, [sp, #8]
	b _02217562
_0221754C:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	add r2, sp, #0
	bl MOD08_0222771C
	b _02217562
_02217558:
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	add r2, sp, #0
	bl MOD08_0222771C
_02217562:
	ldr r1, [sp]
	ldr r0, [r4, #0x2c]
	sub r0, r1, r0
	str r0, [sp]
	ldr r1, [sp, #4]
	ldr r0, [r4, #0x30]
	sub r0, r1, r0
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_02013530
	mov r0, #1
	add sp, #0x20
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_02217580
MOD08_02217580: ; 0x02217580
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r4, r1, #0
	mov r1, #0
	add r0, sp, #0
	strh r1, [r0]
	add r0, r4, #0
	add r1, sp, #4
	bl MOD08_022173BC
	add r0, r4, #0
	bl MOD08_0221727C
	strb r0, [r4, #8]
	ldr r0, [sp, #8]
	cmp r0, #1
	bne _022175A8
	mov r0, #1
	strb r0, [r4, #8]
_022175A8:
	ldr r0, [sp, #4]
	cmp r0, #3
	bgt _022175C6
	cmp r0, #0
	blt _022175F4
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022175BE: ; jump table
	.short _022175CA - _022175BE - 2 ; case 0
	.short _022175E2 - _022175BE - 2 ; case 1
	.short _022175F4 - _022175BE - 2 ; case 2
	.short _022175F4 - _022175BE - 2 ; case 3
_022175C6:
	cmp r0, #0xff
	b _022175F4
_022175CA:
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_02013594
	add r1, sp, #0
	mov r0, #0
	ldrsh r2, [r1, r0]
	mov r0, #8
	ldrsb r0, [r4, r0]
	mul r0, r2
	strh r0, [r1]
	b _022175F4
_022175E2:
	ldr r0, [sp, #0xc]
	add r1, sp, #0
	strh r0, [r1]
	mov r0, #0
	ldrsh r2, [r1, r0]
	mov r0, #8
	ldrsb r0, [r4, r0]
	mul r0, r2
	strh r0, [r1]
_022175F4:
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_0201357C
	mov r0, #1
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02217604
MOD08_02217604: ; 0x02217604
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r4, r1, #0
	mov r1, #0
	add r0, sp, #0
	strh r1, [r0]
	add r0, r4, #0
	add r1, sp, #4
	bl MOD08_022173BC
	add r0, r4, #0
	bl MOD08_0221727C
	strb r0, [r4, #8]
	ldr r0, [sp, #8]
	cmp r0, #1
	bne _0221762C
	mov r0, #1
	strb r0, [r4, #8]
_0221762C:
	ldr r0, [sp, #4]
	cmp r0, #3
	bgt _0221764A
	cmp r0, #0
	blt _02217674
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02217642: ; jump table
	.short _0221764E - _02217642 - 2 ; case 0
	.short _02217664 - _02217642 - 2 ; case 1
	.short _02217674 - _02217642 - 2 ; case 2
	.short _02217674 - _02217642 - 2 ; case 3
_0221764A:
	cmp r0, #0xff
	b _02217674
_0221764E:
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_020135C4
	add r1, sp, #0
	mov r0, #8
	ldrh r2, [r1]
	ldrsb r0, [r4, r0]
	mul r0, r2
	strh r0, [r1]
	b _02217674
_02217664:
	ldr r0, [sp, #0xc]
	add r1, sp, #0
	strh r0, [r1]
	mov r0, #8
	ldrh r2, [r1]
	ldrsb r0, [r4, r0]
	mul r0, r2
	strh r0, [r1]
_02217674:
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_020135B0
	mov r0, #1
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02217684
MOD08_02217684: ; 0x02217684
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r4, r1, #0
	mov r1, #0
	add r0, sp, #0
	strh r1, [r0]
	add r0, r4, #0
	add r1, sp, #4
	bl MOD08_022173BC
	add r0, r4, #0
	bl MOD08_0221727C
	strb r0, [r4, #8]
	ldr r0, [sp, #8]
	cmp r0, #1
	bne _022176AC
	mov r0, #1
	strb r0, [r4, #8]
_022176AC:
	ldr r1, [sp, #4]
	cmp r1, #3
	bgt _022176CA
	cmp r1, #0
	blt _022176DE
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022176C2: ; jump table
	.short _022176CE - _022176C2 - 2 ; case 0
	.short _022176D8 - _022176C2 - 2 ; case 1
	.short _022176DE - _022176C2 - 2 ; case 2
	.short _022176DE - _022176C2 - 2 ; case 3
_022176CA:
	cmp r1, #0xff
	b _022176DE
_022176CE:
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_020135F4
	b _022176DE
_022176D8:
	ldr r1, [sp, #0xc]
	add r0, sp, #0
	strh r1, [r0]
_022176DE:
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_020135E0
	mov r0, #1
	add sp, #0x18
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_022176EC
MOD08_022176EC: ; 0x022176EC
	mov r0, #1
	bx lr

	thumb_func_start MOD08_022176F0
MOD08_022176F0: ; 0x022176F0
	mov r0, #1
	bx lr

	thumb_func_start MOD08_022176F4
MOD08_022176F4: ; 0x022176F4
	mov r0, #1
	bx lr

	thumb_func_start MOD08_022176F8
MOD08_022176F8: ; 0x022176F8
	mov r0, #1
	bx lr

	thumb_func_start MOD08_022176FC
MOD08_022176FC: ; 0x022176FC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r7, r0, #0
	add r4, r1, #0
	add r1, sp, #0
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	add r0, r4, #0
	add r1, sp, #0xc
	bl MOD08_022173BC
	add r0, r4, #0
	bl MOD08_0221727C
	strb r0, [r4, #8]
	ldr r0, [sp, #0x10]
	cmp r0, #1
	bne _02217728
	mov r0, #1
	strb r0, [r4, #8]
_02217728:
	ldr r0, [sp, #0xc]
	cmp r0, #4
	bgt _02217748
	cmp r0, #0
	blt _022177E2
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0221773E: ; jump table
	.short _0221774C - _0221773E - 2 ; case 0
	.short _02217770 - _0221773E - 2 ; case 1
	.short _022177CC - _0221773E - 2 ; case 2
	.short _022177D8 - _0221773E - 2 ; case 3
	.short _02217792 - _0221773E - 2 ; case 4
_02217748:
	cmp r0, #0xff
	b _022177E2
_0221774C:
	add r0, r7, #0
	add r1, sp, #0
	bl FUN_02013628
	mov r0, #8
	ldrsb r1, [r4, r0]
	ldr r2, [sp]
	mul r1, r2
	str r1, [sp]
	ldrsb r1, [r4, r0]
	ldr r2, [sp, #4]
	mul r1, r2
	str r1, [sp, #4]
	ldrsb r0, [r4, r0]
	ldr r1, [sp, #8]
	mul r0, r1
	str r0, [sp, #8]
	b _022177E2
_02217770:
	ldr r2, [sp, #0x14]
	ldr r1, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	str r2, [sp]
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #8
	ldrsb r5, [r4, r3]
	mul r5, r2
	str r5, [sp]
	ldrsb r2, [r4, r3]
	mul r2, r1
	str r2, [sp, #4]
	ldrsb r1, [r4, r3]
	mul r1, r0
	str r1, [sp, #8]
	b _022177E2
_02217792:
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	add r2, sp, #0
	bl MOD08_0222771C
	ldr r1, [sp]
	ldr r5, [sp, #0x14]
	add r0, r1, #0
	ldr r6, [sp, #0x18]
	mul r0, r5
	add r1, r6, #0
	bl _s32_div_f
	ldr r1, [sp, #4]
	str r0, [sp]
	add r0, r1, #0
	mul r0, r5
	add r1, r6, #0
	bl _s32_div_f
	ldr r1, [sp, #8]
	str r0, [sp, #4]
	add r0, r1, #0
	mul r0, r5
	add r1, r6, #0
	bl _s32_div_f
	str r0, [sp, #8]
	b _022177E2
_022177CC:
	ldr r0, [r4]
	ldr r1, [r4, #0x24]
	add r2, sp, #0
	bl MOD08_0222771C
	b _022177E2
_022177D8:
	ldr r0, [r4]
	ldr r1, [r4, #0x28]
	add r2, sp, #0
	bl MOD08_0222771C
_022177E2:
	ldr r1, [sp]
	ldr r0, [r4, #0x2c]
	sub r0, r1, r0
	str r0, [sp]
	ldr r1, [sp, #4]
	ldr r0, [r4, #0x30]
	sub r0, r1, r0
	str r0, [sp, #4]
	ldr r1, [sp, #8]
	ldr r0, [r4, #0x34]
	sub r0, r1, r0
	str r0, [sp, #8]
	add r0, r7, #0
	add r1, sp, #0
	bl FUN_02013610
	mov r0, #1
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02217808
MOD08_02217808: ; 0x02217808
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r4, r1, #0
	mov r1, #0
	add r0, sp, #0
	strh r1, [r0]
	add r0, r4, #0
	add r1, sp, #4
	bl MOD08_022173BC
	add r0, r4, #0
	bl MOD08_0221727C
	strb r0, [r4, #8]
	ldr r0, [sp, #8]
	cmp r0, #1
	bne _02217830
	mov r0, #1
	strb r0, [r4, #8]
_02217830:
	ldr r0, [sp, #4]
	cmp r0, #3
	bgt _0221784E
	cmp r0, #0
	blt _0221787C
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02217846: ; jump table
	.short _02217852 - _02217846 - 2 ; case 0
	.short _0221786A - _02217846 - 2 ; case 1
	.short _0221787C - _02217846 - 2 ; case 2
	.short _0221787C - _02217846 - 2 ; case 3
_0221784E:
	cmp r0, #0xff
	b _0221787C
_02217852:
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_02013674
	add r1, sp, #0
	mov r0, #0
	ldrsh r2, [r1, r0]
	mov r0, #8
	ldrsb r0, [r4, r0]
	mul r0, r2
	strh r0, [r1]
	b _0221787C
_0221786A:
	ldr r0, [sp, #0xc]
	add r1, sp, #0
	strh r0, [r1]
	mov r0, #0
	ldrsh r2, [r1, r0]
	mov r0, #8
	ldrsb r0, [r4, r0]
	mul r0, r2
	strh r0, [r1]
_0221787C:
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_0201365C
	mov r0, #1
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_0221788C
MOD08_0221788C: ; 0x0221788C
	push {r3, lr}
	add r3, r0, #0
	add r0, r1, #0
	add r1, r2, #0
	ldr r2, _022178A0 ; =0x0222C204
	lsl r3, r3, #2
	ldr r2, [r2, r3]
	blx r2
	pop {r3, pc}
	nop
_022178A0: .word MOD8_0222C204

	thumb_func_start MOD08_022178A4
MOD08_022178A4: ; 0x022178A4
	push {r3, r4, r5}
	sub sp, #0x3c
	ldr r4, _022178C8 ; =0x0222C23C
	add r5, r0, #0
	add r3, sp, #0
	mov r2, #7
_022178B0:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _022178B0
	ldr r0, [r4]
	lsl r1, r5, #2
	str r0, [r3]
	add r0, sp, #0
	ldr r0, [r0, r1]
	add sp, #0x3c
	pop {r3, r4, r5}
	bx lr
	.align 2, 0
_022178C8: .word MOD8_0222C23C

	thumb_func_start MOD08_022178CC
MOD08_022178CC: ; 0x022178CC
	push {r4, r5, r6, lr}
	mov r4, #0
	ldr r6, _022178F4 ; =0x0000FEFE
	add r5, r4, #0
_022178D4:
	add r0, r4, #0
	bl MOD08_022178A4
	add r4, r4, #1
	cmp r0, r6
	beq _022178E6
	add r5, r5, #1
	cmp r5, #0xff
	blt _022178D4
_022178E6:
	cmp r5, #0xff
	blt _022178EE
	mov r0, #0
	pop {r4, r5, r6, pc}
_022178EE:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	nop
_022178F4: .word 0x0000FEFE

	thumb_func_start MOD08_022178F8
MOD08_022178F8: ; 0x022178F8
	ldr r3, _02217900 ; =MOD08_02215434
	ldr r0, [r0]
	mov r2, #4
	bx r3
	.align 2, 0
_02217900: .word MOD08_02215434

	thumb_func_start MOD08_02217904
MOD08_02217904: ; 0x02217904
	push {r3, lr}
	sub sp, #8
	add r2, sp, #0
	mov r0, #0
	strh r0, [r2]
	strh r0, [r2, #2]
	strh r0, [r2, #4]
	strh r0, [r2, #6]
	ldr r0, [r1, #4]
	bl FUN_0201343C
	add r1, r0, #0
	add r0, sp, #0
	bl FUN_0201EF90
	mov r0, #1
	add sp, #8
	pop {r3, pc}

	thumb_func_start MOD08_02217928
MOD08_02217928: ; 0x02217928
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	ldr r1, _02217960 ; =0x0222C278
	add r0, sp, #0
	ldrh r2, [r1, #0x20]
	strh r2, [r0]
	ldrh r2, [r1, #0x22]
	strh r2, [r0, #2]
	ldrh r2, [r1, #0x24]
	ldrh r1, [r1, #0x26]
	strh r2, [r0, #4]
	strh r1, [r0, #6]
	ldr r0, [r4, #4]
	bl FUN_0201343C
	add r5, r0, #0
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_02013440
	add r0, sp, #0
	add r1, r5, #0
	bl FUN_0201EF90
	mov r0, #1
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_02217960: .word MOD8_0222C278

	thumb_func_start MOD08_02217964
MOD08_02217964: ; 0x02217964
	push {r4, lr}
	sub sp, #0x18
	add r4, r1, #0
	add r1, sp, #0
	mov r0, #0
	strh r0, [r1]
	strh r0, [r1, #2]
	strh r0, [r1, #4]
	strh r0, [r1, #6]
	add r0, r4, #0
	add r1, sp, #8
	bl MOD08_022178F8
	ldr r1, [sp, #0xc]
	add r0, sp, #0
	strh r1, [r0]
	ldr r1, [sp, #0x10]
	strh r1, [r0, #2]
	ldr r1, [sp, #0x14]
	strh r1, [r0, #4]
	ldr r0, [r4, #4]
	bl FUN_0201343C
	add r1, r0, #0
	add r0, sp, #0
	bl FUN_0201EF90
	mov r0, #1
	add sp, #0x18
	pop {r4, pc}

	thumb_func_start MOD08_022179A0
MOD08_022179A0: ; 0x022179A0
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	ldr r1, _022179D8 ; =0x0222C278
	add r0, sp, #0
	ldrh r2, [r1, #0x18]
	strh r2, [r0]
	ldrh r2, [r1, #0x1a]
	strh r2, [r0, #2]
	ldrh r2, [r1, #0x1c]
	ldrh r1, [r1, #0x1e]
	strh r2, [r0, #4]
	strh r1, [r0, #6]
	ldr r0, [r4, #4]
	bl FUN_0201343C
	add r5, r0, #0
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_02013440
	add r0, sp, #0
	add r1, r5, #0
	bl FUN_0201EF90
	mov r0, #1
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_022179D8: .word MOD8_0222C278

	thumb_func_start MOD08_022179DC
MOD08_022179DC: ; 0x022179DC
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r1, #0
	ldr r1, _02217A38 ; =0x0222C278
	add r0, sp, #0
	ldrh r2, [r1, #0x10]
	strh r2, [r0, #8]
	ldrh r2, [r1, #0x12]
	strh r2, [r0, #0xa]
	ldrh r2, [r1, #0x14]
	strh r2, [r0, #0xc]
	ldrh r2, [r1, #0x16]
	strh r2, [r0, #0xe]
	ldrh r2, [r1, #0x28]
	strh r2, [r0]
	ldrh r2, [r1, #0x2a]
	strh r2, [r0, #2]
	ldrh r2, [r1, #0x2c]
	strh r2, [r0, #4]
	ldrh r1, [r1, #0x2e]
	strh r1, [r0, #6]
	ldr r0, [r4, #4]
	bl FUN_0201343C
	add r5, r0, #0
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_02013440
	ldr r0, [r4]
	bl MOD08_02212004
	cmp r0, #1
	bne _02217A2A
	add r0, sp, #8
	add r1, r5, #0
	bl FUN_0201EF90
	b _02217A32
_02217A2A:
	add r0, sp, #0
	add r1, r5, #0
	bl FUN_0201EF90
_02217A32:
	mov r0, #1
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_02217A38: .word MOD8_0222C278

	thumb_func_start MOD08_02217A3C
MOD08_02217A3C: ; 0x02217A3C
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	ldr r1, _02217A74 ; =0x0222C278
	add r0, sp, #0
	ldrh r2, [r1]
	strh r2, [r0]
	ldrh r2, [r1, #2]
	strh r2, [r0, #2]
	ldrh r2, [r1, #4]
	ldrh r1, [r1, #6]
	strh r2, [r0, #4]
	strh r1, [r0, #6]
	ldr r0, [r4, #4]
	bl FUN_0201343C
	add r5, r0, #0
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_02013440
	add r0, sp, #0
	add r1, r5, #0
	bl FUN_0201EF90
	mov r0, #1
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_02217A74: .word MOD8_0222C278

	thumb_func_start MOD08_02217A78
MOD08_02217A78: ; 0x02217A78
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	ldr r1, _02217AB0 ; =0x0222C278
	add r0, sp, #0
	ldrh r2, [r1, #8]
	strh r2, [r0]
	ldrh r2, [r1, #0xa]
	strh r2, [r0, #2]
	ldrh r2, [r1, #0xc]
	ldrh r1, [r1, #0xe]
	strh r2, [r0, #4]
	strh r1, [r0, #6]
	ldr r0, [r4, #4]
	bl FUN_0201343C
	add r5, r0, #0
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_02013440
	add r0, sp, #0
	add r1, r5, #0
	bl FUN_0201EF90
	mov r0, #1
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_02217AB0: .word MOD8_0222C278

	thumb_func_start MOD08_02217AB4
MOD08_02217AB4: ; 0x02217AB4
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r0, [r5, #4]
	bl FUN_0201343C
	add r4, r0, #0
	ldr r0, [r5]
	ldr r1, [r5, #0x24]
	add r2, sp, #0
	bl MOD08_022278FC
	add r0, sp, #0
	add r1, r4, #0
	bl FUN_0201F04C
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02217ADC
MOD08_02217ADC: ; 0x02217ADC
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r0, [r5, #4]
	bl FUN_0201343C
	add r4, r0, #0
	ldr r0, [r5]
	ldr r1, [r5, #0x28]
	add r2, sp, #0
	bl MOD08_022278FC
	add r0, sp, #0
	add r1, r4, #0
	bl FUN_0201F04C
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02217B04
MOD08_02217B04: ; 0x02217B04
	push {r3, lr}
	add r3, r0, #0
	add r0, r1, #0
	add r1, r2, #0
	ldr r2, _02217B18 ; =0x0222C2A8
	lsl r3, r3, #2
	ldr r2, [r2, r3]
	blx r2
	pop {r3, pc}
	nop
_02217B18: .word MOD8_0222C2A8

	thumb_func_start MOD08_02217B1C
MOD08_02217B1C: ; 0x02217B1C
	push {r3, r4, r5, r6}
	cmp r2, #0
	beq _02217B32
	mov r4, #0x18
	add r6, r0, #0
	mul r6, r4
	ldr r4, _02217B48 ; =0x0222C2CC
	lsl r5, r1, #2
	add r4, r4, r6
	ldrsh r4, [r5, r4]
	strh r4, [r2]
_02217B32:
	cmp r3, #0
	beq _02217B44
	mov r2, #0x18
	mul r2, r0
	ldr r0, _02217B4C ; =0x0222C2CE
	lsl r1, r1, #2
	add r0, r0, r2
	ldrsh r0, [r1, r0]
	strh r0, [r3]
_02217B44:
	pop {r3, r4, r5, r6}
	bx lr
	.align 2, 0
_02217B48: .word MOD8_0222C2CC
_02217B4C: .word MOD8_0222C2CE

	thumb_func_start MOD08_02217B50
MOD08_02217B50: ; 0x02217B50
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	add r4, r2, #0
	add r6, r3, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _02217B70
	mov r0, #0
	add r1, r5, #2
	add r2, r4, #0
	add r3, r6, #0
	bl MOD08_02217B1C
	pop {r3, r4, r5, r6, r7, pc}
_02217B70:
	add r0, r7, #0
	bl MOD08_0221553C
	cmp r0, #1
	bne _02217B88
	mov r0, #1
	sub r1, r5, #2
	add r2, r4, #0
	add r3, r6, #0
	bl MOD08_02217B1C
	pop {r3, r4, r5, r6, r7, pc}
_02217B88:
	mov r0, #0
	add r1, r5, #0
	add r2, r4, #0
	add r3, r6, #0
	bl MOD08_02217B1C
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02217B98
MOD08_02217B98: ; 0x02217B98
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r6, r2, #0
	bl MOD08_02227468
	add r4, r0, #0
	add r0, r7, #0
	bl MOD08_0221553C
	cmp r0, #1
	bne _02217BB2
	mov r5, #1
	b _02217BB4
_02217BB2:
	mov r5, #0
_02217BB4:
	add r0, r7, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _02217BC0
	add r4, r4, #2
_02217BC0:
	cmp r6, #3
	bhi _02217BF8
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02217BD0: ; jump table
	.short _02217BD8 - _02217BD0 - 2 ; case 0
	.short _02217BE8 - _02217BD0 - 2 ; case 1
	.short _02217BD8 - _02217BD0 - 2 ; case 2
	.short _02217BE8 - _02217BD0 - 2 ; case 3
_02217BD8:
	mov r0, #0x18
	add r2, r5, #0
	mul r2, r0
	ldr r0, _02217C00 ; =0x0222C2CC
	lsl r1, r4, #2
	add r0, r0, r2
	ldrsh r0, [r1, r0]
	pop {r3, r4, r5, r6, r7, pc}
_02217BE8:
	mov r0, #0x18
	add r2, r5, #0
	mul r2, r0
	ldr r0, _02217C04 ; =0x0222C2CE
	lsl r1, r4, #2
	add r0, r0, r2
	ldrsh r0, [r1, r0]
	pop {r3, r4, r5, r6, r7, pc}
_02217BF8:
	bl ErrorHandling
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02217C00: .word MOD8_0222C2CC
_02217C04: .word MOD8_0222C2CE

	thumb_func_start MOD08_02217C08
MOD08_02217C08: ; 0x02217C08
	push {r3, lr}
	ldr r0, [r0]
	bl FUN_02020354
	mov r1, #1
	bl FUN_0201E28C
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}

	thumb_func_start MOD08_02217C1C
MOD08_02217C1C: ; 0x02217C1C
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r5, #1
	bl MOD08_02227470
	add r4, r0, #0
	add r0, r6, #0
	bl MOD08_02212004
	cmp r0, #0
	beq _02217C3A
	cmp r4, #3
	bne _02217C40
	sub r5, r5, #2
	b _02217C40
_02217C3A:
	cmp r4, #4
	bne _02217C40
	sub r5, r5, #2
_02217C40:
	add r0, r5, #0
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_02217C44
MOD08_02217C44: ; 0x02217C44
	push {r4, lr}
	mov r4, #1
	bl MOD08_02227470
	cmp r0, #4
	bne _02217C52
	sub r4, r4, #2
_02217C52:
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02217C58
MOD08_02217C58: ; 0x02217C58
	ldr r3, _02217C60 ; =FX_Div
	sub r0, r1, r0
	lsl r1, r2, #0xc
	bx r3
	.align 2, 0
_02217C60: .word FX_Div

	thumb_func_start MOD08_02217C64
MOD08_02217C64: ; 0x02217C64
	push {r3, lr}
	sub r0, r1, r0
	add r1, r2, #0
	bl FX_Div
	add r1, sp, #0
	str r0, [sp]
	bl FX_Modf
	cmp r0, #0
	beq _02217C84
	mov r0, #1
	ldr r1, [sp]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp]
_02217C84:
	ldr r0, [sp]
	cmp r0, #0
	bge _02217C8C
	neg r0, r0
_02217C8C:
	str r0, [sp]
	asr r0, r0, #0xc
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD08_02217C94
MOD08_02217C94: ; 0x02217C94
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #0
	ldrsh r1, [r4, r1]
	add r1, r2, r1
	mov r2, #2
	ldrsh r2, [r4, r2]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add r2, r3, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	pop {r4, pc}

	thumb_func_start MOD08_02217CB4
MOD08_02217CB4: ; 0x02217CB4
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	add r1, sp, #4
	add r2, sp, #0
	bl MOD08_0221825C
	ldr r1, [sp, #4]
	ldr r2, [sp]
	add r0, r4, #0
	bl FUN_0200C884
	add sp, #8
	pop {r4, pc}

	thumb_func_start MOD08_02217CD0
MOD08_02217CD0: ; 0x02217CD0
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	mov r1, #0
	add r6, r3, #0
	ldrsh r3, [r5, r1]
	add r0, r4, #0
	add r2, r2, r3
	bl FUN_02007558
	mov r2, #2
	ldrsh r2, [r5, r2]
	add r0, r4, #0
	mov r1, #1
	add r2, r6, r2
	bl FUN_02007558
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_02217CF4
MOD08_02217CF4: ; 0x02217CF4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r2, #0
	add r4, r1, #0
	ldrsh r2, [r5, r2]
	add r0, r4, #0
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #2
	ldrsh r2, [r5, r2]
	add r0, r4, #0
	mov r1, #0xd
	bl FUN_02007558
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02217D14
MOD08_02217D14: ; 0x02217D14
	push {r3, r4, r5, lr}
	add r4, r3, #0
	add r5, r0, #0
	ldr r3, [sp, #0x1c]
	ldr r0, [sp, #0x14]
	str r3, [r5, #4]
	str r1, [r5, #8]
	str r0, [r5, #0xc]
	ldr r0, [sp, #0x18]
	str r4, [r5, #0x10]
	str r0, [r5, #0x14]
	sub r0, r2, r1
	add r1, r3, #0
	bl _s32_div_f
	str r0, [r5, #0x18]
	add r0, sp, #0
	ldrh r0, [r0, #0x10]
	ldr r1, [sp, #0x1c]
	sub r0, r0, r4
	bl _s32_div_f
	str r0, [r5, #0x1c]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02217D44
MOD08_02217D44: ; 0x02217D44
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r7, r2, #0
	str r3, [sp]
	cmp r5, #0
	bne _02217D56
	bl ErrorHandling
_02217D56:
	cmp r4, r7
	bls _02217D62
	add r0, sp, #8
	ldrh r1, [r0, #0x1c]
	neg r1, r1
	strh r1, [r0, #0x1c]
_02217D62:
	add r1, sp, #8
	mov r0, #0x1c
	ldrsh r6, [r1, r0]
	lsl r0, r4, #0xc
	lsl r1, r7, #0xc
	lsl r2, r6, #0xc
	bl MOD08_02217C64
	str r0, [r5, #4]
	ldr r0, [sp, #0x1c]
	str r4, [r5, #8]
	str r0, [r5, #0xc]
	ldr r0, [sp]
	str r0, [r5, #0x10]
	ldr r0, [sp, #0x20]
	str r0, [r5, #0x14]
	str r6, [r5, #0x18]
	add r0, sp, #8
	ldrh r1, [r0, #0x10]
	ldr r0, [sp]
	sub r0, r1, r0
	ldr r1, [r5, #4]
	bl _s32_div_f
	str r0, [r5, #0x1c]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02217D98
MOD08_02217D98: ; 0x02217D98
	push {r4, lr}
	add r4, r0, #0
	bne _02217DA2
	bl ErrorHandling
_02217DA2:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _02217E26
	ldr r1, [r4, #8]
	ldr r0, [r4, #0x18]
	add r0, r1, r0
	str r0, [r4, #8]
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x1c]
	add r0, r1, r0
	str r0, [r4, #0x10]
	ldr r0, [r4, #8]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [r4, #8]
	ldr r0, [r4, #0x10]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [r4, #0x10]
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	ldr r0, [r4, #8]
	ldr r2, [r4, #0xc]
	asr r0, r0, #4
	lsl r1, r0, #2
	ldr r0, _02217E2C ; =FX_SinCosTable_
	asr r3, r2, #0x1f
	ldrsh r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	asr r0, r1, #0xc
	strh r0, [r4]
	ldr r0, [r4, #0x10]
	ldr r2, [r4, #0x14]
	asr r0, r0, #4
	lsl r0, r0, #1
	add r0, r0, #1
	lsl r1, r0, #1
	ldr r0, _02217E2C ; =FX_SinCosTable_
	asr r3, r2, #0x1f
	ldrsh r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	asr r0, r1, #0xc
	strh r0, [r4, #2]
	mov r0, #1
	pop {r4, pc}
_02217E26:
	mov r0, #0
	pop {r4, pc}
	nop
_02217E2C: .word FX_SinCosTable_

	thumb_func_start MOD08_02217E30
MOD08_02217E30: ; 0x02217E30
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl MOD08_02217D98
	cmp r0, #0
	beq _02217E52
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	add r3, r6, #0
	bl MOD08_02217C94
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02217E52:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02217E58
MOD08_02217E58: ; 0x02217E58
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl MOD08_02217D98
	cmp r0, #0
	beq _02217E7A
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	add r3, r6, #0
	bl MOD08_02217CD0
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02217E7A:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02217E80
MOD08_02217E80: ; 0x02217E80
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r4, r1, #0
	add r6, r3, #0
	str r2, [sp]
	cmp r5, #0
	bne _02217E94
	bl ErrorHandling
_02217E94:
	strh r4, [r5]
	strh r6, [r5, #2]
	add r0, sp, #0x10
	ldrh r7, [r0, #0x14]
	lsl r0, r4, #0xc
	str r0, [sp, #4]
	str r7, [r5, #4]
	ldr r1, [sp]
	add r2, r7, #0
	lsl r1, r1, #0xc
	bl MOD08_02217C58
	str r0, [r5, #8]
	lsl r4, r6, #0xc
	add r2, sp, #0x10
	mov r1, #0x10
	ldrsh r1, [r2, r1]
	add r0, r4, #0
	add r2, r7, #0
	lsl r1, r1, #0xc
	bl MOD08_02217C58
	str r0, [r5, #0xc]
	ldr r0, [sp, #4]
	str r0, [r5, #0x10]
	str r4, [r5, #0x14]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02217ECC
MOD08_02217ECC: ; 0x02217ECC
	push {r4, lr}
	add r4, r0, #0
	bne _02217ED6
	bl ErrorHandling
_02217ED6:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _02217F02
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #8]
	add r0, r1, r0
	str r0, [r4, #0x10]
	ldr r1, [r4, #0x14]
	ldr r0, [r4, #0xc]
	add r0, r1, r0
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x10]
	asr r0, r0, #0xc
	strh r0, [r4]
	ldr r0, [r4, #0x14]
	asr r0, r0, #0xc
	strh r0, [r4, #2]
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	mov r0, #1
	pop {r4, pc}
_02217F02:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02217F08
MOD08_02217F08: ; 0x02217F08
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD08_02217ECC
	cmp r0, #0
	beq _02217F26
	mov r2, #0
	add r0, r5, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD08_02217C94
	mov r0, #1
	pop {r3, r4, r5, pc}
_02217F26:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02217F2C
MOD08_02217F2C: ; 0x02217F2C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD08_02217ECC
	cmp r0, #0
	beq _02217F4A
	mov r2, #0
	add r0, r5, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD08_02217CD0
	mov r0, #1
	pop {r3, r4, r5, pc}
_02217F4A:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02217F50
MOD08_02217F50: ; 0x02217F50
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r4, sp, #0x10
	mov r1, #0x14
	ldrsh r1, [r4, r1]
	str r1, [sp]
	ldrh r1, [r4, #0x18]
	str r1, [sp, #4]
	add r1, r2, #0
	add r2, r3, #0
	mov r3, #0x10
	ldrsh r3, [r4, r3]
	bl MOD08_02217E80
	mov r1, #0
	strh r1, [r5]
	ldr r0, _02217F94 ; =0x0000BFFF
	strh r1, [r5, #2]
	str r0, [sp]
	ldr r0, [sp, #0x2c]
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r4, #0
	ldrh r0, [r0, #0x18]
	ldr r3, _02217F98 ; =0x00003FFF
	add r2, r1, #0
	str r0, [sp, #0xc]
	add r0, r5, #0
	bl MOD08_02217D14
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_02217F94: .word 0x0000BFFF
_02217F98: .word 0x00003FFF

	thumb_func_start MOD08_02217F9C
MOD08_02217F9C: ; 0x02217F9C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	cmp r5, #0
	bne _02217FAA
	bl ErrorHandling
_02217FAA:
	cmp r4, #0
	bne _02217FB2
	bl ErrorHandling
_02217FB2:
	add r0, r5, #0
	bl MOD08_02217ECC
	add r6, r0, #0
	add r0, r4, #0
	bl MOD08_02217D98
	mov r2, #0
	ldrsh r3, [r5, r2]
	ldrsh r1, [r4, r2]
	add r1, r3, r1
	strh r1, [r5]
	mov r1, #2
	ldrsh r3, [r5, r1]
	ldrsh r1, [r4, r1]
	add r1, r3, r1
	strh r1, [r5, #2]
	cmp r6, r0
	bne _02217FE0
	cmp r6, #0
	bne _02217FE0
	add r0, r2, #0
	pop {r4, r5, r6, pc}
_02217FE0:
	mov r0, #1
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_02217FE4
MOD08_02217FE4: ; 0x02217FE4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r2, #0
	bl MOD08_02217F9C
	cmp r0, #0
	beq _02218002
	mov r2, #0
	add r0, r5, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD08_02217C94
	mov r0, #1
	pop {r3, r4, r5, pc}
_02218002:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02218008
MOD08_02218008: ; 0x02218008
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	add r4, r3, #0
	cmp r5, #0
	bne _0221801A
	bl ErrorHandling
_0221801A:
	str r6, [r5]
	lsl r0, r6, #0xc
	lsl r1, r7, #0xc
	add r2, r4, #0
	str r4, [r5, #4]
	bl MOD08_02217C58
	asr r0, r0, #0xc
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02218030
MOD08_02218030: ; 0x02218030
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	add r4, r3, #0
	cmp r5, #0
	bne _02218042
	bl ErrorHandling
_02218042:
	str r6, [r5]
	lsl r6, r6, #0xc
	add r0, r6, #0
	lsl r1, r7, #0xc
	add r2, r4, #0
	str r4, [r5, #4]
	bl MOD08_02217C58
	str r0, [r5, #8]
	str r6, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02218058
MOD08_02218058: ; 0x02218058
	push {r4, lr}
	add r4, r0, #0
	bne _02218062
	bl ErrorHandling
_02218062:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _0221807A
	ldr r1, [r4]
	ldr r0, [r4, #8]
	add r0, r1, r0
	str r0, [r4]
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	mov r0, #1
	pop {r4, pc}
_0221807A:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02218080
MOD08_02218080: ; 0x02218080
	push {r4, lr}
	add r4, r0, #0
	bne _0221808A
	bl ErrorHandling
_0221808A:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _022180A6
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #8]
	add r0, r1, r0
	str r0, [r4, #0xc]
	asr r0, r0, #0xc
	str r0, [r4]
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	mov r0, #1
	pop {r4, pc}
_022180A6:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_022180AC
MOD08_022180AC: ; 0x022180AC
	push {r3, r4, r5, lr}
	ldr r4, [sp, #0x10]
	add r5, r0, #0
	str r4, [r5, #4]
	str r1, [r5, #8]
	sub r0, r2, r1
	add r1, r4, #0
	str r3, [r5, #0xc]
	bl _u32_div_f
	str r0, [r5, #0x10]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_022180C4
MOD08_022180C4: ; 0x022180C4
	push {r4, lr}
	add r4, r0, #0
	bne _022180CE
	bl ErrorHandling
_022180CE:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _02218116
	ldr r1, [r4, #8]
	ldr r0, [r4, #0x10]
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	ldr r0, [r4, #8]
	ldr r2, [r4, #0xc]
	asr r0, r0, #4
	lsl r0, r0, #1
	add r0, r0, #1
	lsl r1, r0, #1
	ldr r0, _0221811C ; =FX_SinCosTable_
	asr r3, r2, #0x1f
	ldrsh r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	asr r0, r1, #0xc
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_02218116:
	mov r0, #0
	pop {r4, pc}
	nop
_0221811C: .word FX_SinCosTable_

	thumb_func_start MOD08_02218120
MOD08_02218120: ; 0x02218120
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	cmp r4, #0
	bne _02218132
	bl ErrorHandling
_02218132:
	ldr r0, [sp, #0x18]
	add r1, r6, #0
	str r0, [r4, #4]
	lsl r0, r5, #8
	bl _s32_div_f
	add r5, r0, #0
	lsl r0, r7, #8
	add r1, r6, #0
	bl _s32_div_f
	add r1, r0, #0
	ldr r2, [sp, #0x18]
	lsl r0, r5, #0xc
	lsl r1, r1, #0xc
	bl MOD08_02217C58
	str r0, [r4, #8]
	lsl r0, r5, #0x10
	asr r0, r0, #0x10
	strh r0, [r4]
	strh r0, [r4, #2]
	mov r0, #0
	ldrsh r0, [r4, r0]
	lsl r0, r0, #0xc
	str r0, [r4, #0x10]
	mov r0, #2
	ldrsh r0, [r4, r0]
	lsl r0, r0, #0xc
	str r0, [r4, #0x14]
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02218170
MOD08_02218170: ; 0x02218170
	push {r4, lr}
	add r4, r0, #0
	bne _0221817A
	bl ErrorHandling
_0221817A:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _022181A4
	sub r0, r0, #1
	str r0, [r4, #4]
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #8]
	add r0, r1, r0
	str r0, [r4, #0x10]
	ldr r1, [r4, #0x14]
	ldr r0, [r4, #8]
	add r0, r1, r0
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x10]
	asr r0, r0, #0xc
	strh r0, [r4]
	ldr r0, [r4, #0x14]
	asr r0, r0, #0xc
	strh r0, [r4, #2]
	mov r0, #1
	pop {r4, pc}
_022181A4:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD08_022181A8
MOD08_022181A8: ; 0x022181A8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	str r3, [sp]
	cmp r5, #0
	bne _022181BA
	bl ErrorHandling
_022181BA:
	ldr r0, [sp, #0x20]
	add r1, sp, #8
	str r0, [r5, #4]
	mov r0, #0x14
	ldrsh r4, [r1, r0]
	lsl r0, r6, #8
	add r1, r4, #0
	bl _s32_div_f
	add r6, r0, #0
	lsl r0, r7, #8
	add r1, r4, #0
	bl _s32_div_f
	add r1, r0, #0
	ldr r2, [sp, #0x20]
	lsl r0, r6, #0xc
	lsl r1, r1, #0xc
	bl MOD08_02217C58
	str r0, [r5, #8]
	ldr r0, [sp]
	add r1, r4, #0
	lsl r0, r0, #8
	bl _s32_div_f
	add r7, r0, #0
	add r1, sp, #8
	mov r0, #0x10
	ldrsh r0, [r1, r0]
	add r1, r4, #0
	lsl r0, r0, #8
	bl _s32_div_f
	add r1, r0, #0
	ldr r2, [sp, #0x20]
	lsl r0, r7, #0xc
	lsl r1, r1, #0xc
	bl MOD08_02217C58
	str r0, [r5, #0xc]
	strh r6, [r5]
	strh r7, [r5, #2]
	mov r0, #0
	ldrsh r0, [r5, r0]
	lsl r0, r0, #0xc
	str r0, [r5, #0x10]
	mov r0, #2
	ldrsh r0, [r5, r0]
	lsl r0, r0, #0xc
	str r0, [r5, #0x14]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02218224
MOD08_02218224: ; 0x02218224
	push {r4, lr}
	add r4, r0, #0
	bne _0221822E
	bl ErrorHandling
_0221822E:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _02218258
	sub r0, r0, #1
	str r0, [r4, #4]
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #8]
	add r0, r1, r0
	str r0, [r4, #0x10]
	ldr r1, [r4, #0x14]
	ldr r0, [r4, #0xc]
	add r0, r1, r0
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x10]
	asr r0, r0, #0xc
	strh r0, [r4]
	ldr r0, [r4, #0x14]
	asr r0, r0, #0xc
	strh r0, [r4, #2]
	mov r0, #1
	pop {r4, pc}
_02218258:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD08_0221825C
MOD08_0221825C: ; 0x0221825C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0
	ldrsh r0, [r5, r0]
	add r4, r1, #0
	add r6, r2, #0
	bl _fflt
	ldr r1, _02218288 ; =0x43800000
	bl _fdiv
	str r0, [r4]
	mov r0, #2
	ldrsh r0, [r5, r0]
	bl _fflt
	ldr r1, _02218288 ; =0x43800000
	bl _fdiv
	str r0, [r6]
	pop {r4, r5, r6, pc}
	nop
_02218288: .word 0x43800000

	thumb_func_start MOD08_0221828C
MOD08_0221828C: ; 0x0221828C
	push {r3, r4, lr}
	sub sp, #4
	lsl r1, r1, #1
	mov r0, #0x50
	sub r0, r0, r1
	lsl r4, r0, #0xc
	asr r1, r4, #0x1f
	add r0, r4, #0
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r0, r0, r2
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	lsl r1, r2, #9
	bl FX_Div
	sub r0, r4, r0
	add r1, sp, #0
	bl FX_Modf
	cmp r0, #0
	beq _022182CA
	mov r1, #2
	lsl r1, r1, #0xa
	add r0, r0, r1
_022182CA:
	ldr r1, [sp]
	add r0, r1, r0
	asr r1, r0, #0xc
	lsr r0, r1, #0x1f
	add r0, r1, r0
	lsl r0, r0, #0xf
	asr r0, r0, #0x10
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD08_022182DC
MOD08_022182DC: ; 0x022182DC
	push {r4, r5, r6, lr}
	add r6, r2, #0
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	add r2, r3, #0
	bl MOD08_0221828C
	add r2, r0, #0
	ldr r0, [sp, #0x10]
	cmp r0, #1
	bne _02218306
	mov r0, #0
	mvn r0, r0
	mul r0, r2
	lsl r0, r0, #0x10
	asr r2, r0, #0x10
	sub r0, r4, r6
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
_02218306:
	add r0, r5, #0
	mov r1, #1
	add r2, r4, r2
	bl FUN_02007558
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_02218314
MOD08_02218314: ; 0x02218314
	push {r3, r4, r5, r6, r7, lr}
	add r7, r2, #0
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	add r2, r3, #0
	bl MOD08_0221828C
	add r4, r0, #0
	ldr r0, [sp, #0x18]
	cmp r0, #1
	bne _0221833E
	mov r0, #0
	mvn r0, r0
	mul r0, r4
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	sub r0, r5, r7
	lsl r0, r0, #0x10
	asr r5, r0, #0x10
_0221833E:
	add r1, sp, #0
	add r0, r6, #0
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	add r2, sp, #0
	mov r1, #2
	ldrsh r1, [r2, r1]
	add r2, r5, r4
	lsl r2, r2, #0x10
	add r0, r6, #0
	asr r2, r2, #0x10
	bl FUN_0200C714
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02218360
MOD08_02218360: ; 0x02218360
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD08_02218170
	cmp r0, #0
	beq _0221837A
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02217CB4
	mov r0, #1
	pop {r3, r4, r5, pc}
_0221837A:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02218380
MOD08_02218380: ; 0x02218380
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD08_02218170
	cmp r0, #0
	beq _0221839A
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02217CF4
	mov r0, #1
	pop {r3, r4, r5, pc}
_0221839A:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_022183A0
MOD08_022183A0: ; 0x022183A0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD08_02218224
	cmp r0, #0
	beq _022183BA
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02217CF4
	mov r0, #1
	pop {r3, r4, r5, pc}
_022183BA:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_022183C0
MOD08_022183C0: ; 0x022183C0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	add r7, r3, #0
	cmp r5, #0
	bne _022183D2
	bl ErrorHandling
_022183D2:
	str r7, [r5, #4]
	ldr r0, [sp, #0x18]
	str r7, [r5, #8]
	str r0, [r5, #0xc]
	mov r1, #0
	str r1, [r5, #0x10]
	str r6, [r5, #0x14]
	str r4, [r5, #0x18]
	neg r0, r6
	str r0, [r5, #0x1c]
	neg r0, r4
	str r0, [r5, #0x20]
	strh r1, [r5]
	strh r1, [r5, #2]
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_022183F0
MOD08_022183F0: ; 0x022183F0
	push {r4, lr}
	add r4, r0, #0
	bne _022183FA
	bl ErrorHandling
_022183FA:
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _0221844E
	ldr r0, [r4, #4]
	add r1, r0, #1
	str r1, [r4, #4]
	ldr r0, [r4, #8]
	cmp r1, r0
	blt _0221844A
	mov r2, #0
	str r2, [r4, #4]
	ldrsh r0, [r4, r2]
	ldr r1, [r4, #0x1c]
	str r0, [r4, #0x1c]
	cmp r1, #0
	bne _0221841E
	strh r2, [r4]
	b _02218422
_0221841E:
	neg r0, r1
	strh r0, [r4]
_02218422:
	mov r0, #2
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #0x20]
	str r0, [r4, #0x20]
	cmp r1, #0
	bne _02218432
	mov r0, #0
	b _02218434
_02218432:
	neg r0, r1
_02218434:
	strh r0, [r4, #2]
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	cmp r0, #4
	blt _0221844A
	mov r0, #0
	str r0, [r4, #0x10]
	ldr r0, [r4, #0xc]
	sub r0, r0, #1
	str r0, [r4, #0xc]
_0221844A:
	mov r0, #1
	pop {r4, pc}
_0221844E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02218454
MOD08_02218454: ; 0x02218454
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl MOD08_022183F0
	cmp r0, #0
	beq _02218476
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	add r3, r6, #0
	bl MOD08_02217CD0
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02218476:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_0221847C
MOD08_0221847C: ; 0x0221847C
	push {r3, r4, r5, r6, r7, lr}
	mov ip, r1
	str r0, [sp]
	strh r3, [r0]
	add r0, sp, #8
	mov r1, #0x10
	ldrsh r3, [r0, r1]
	ldr r1, [sp]
	mov r6, #0
	strh r3, [r1, #2]
	add r1, #0x94
	str r2, [r1]
	ldr r1, [sp]
	ldrh r2, [r0, #0x14]
	add r1, #0xa8
	strh r2, [r1]
	ldr r1, [sp]
	add r1, #0xaa
	strh r6, [r1]
	ldr r1, [sp]
	ldrb r7, [r0, #0x18]
	add r1, #0xac
	strb r7, [r1]
	ldr r1, [sp]
	add r1, #0xad
	strb r6, [r1]
	ldrb r1, [r0, #0x1c]
	ldr r0, [sp]
	add r0, #0xae
	strb r1, [r0]
	cmp r7, #0
	ble _022184D8
	ldr r5, [sp]
_022184BE:
	mov r4, ip
	add r3, r5, #4
	mov r2, #4
_022184C4:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _022184C4
	ldr r0, [r4]
	add r6, r6, #1
	str r0, [r3]
	add r5, #0x24
	cmp r6, r7
	blt _022184BE
_022184D8:
	ldr r0, [sp]
	ldr r1, [sp, #0x28]
	add r0, #0x98
	str r1, [r0]
	ldr r0, [sp]
	ldr r1, [sp, #0x2c]
	add r0, #0x9c
	str r1, [r0]
	ldr r0, [sp]
	ldr r1, [sp, #0x30]
	add r0, #0xa0
	str r1, [r0]
	ldr r0, [sp]
	ldr r1, [sp, #0x34]
	add r0, #0xa4
	str r1, [r0]
	ldr r0, [sp]
	mov r5, #0
	add r0, #0xac
	ldrb r0, [r0]
	cmp r0, #0
	ble _02218522
	ldr r4, [sp]
	add r6, r5, #0
_02218508:
	add r0, r4, #0
	add r0, #0x98
	ldr r0, [r0]
	add r1, r6, #0
	bl FUN_0200C644
	ldr r0, [sp]
	add r5, r5, #1
	add r0, #0xac
	ldrb r0, [r0]
	add r4, r4, #4
	cmp r5, r0
	blt _02218508
_02218522:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02218524
MOD08_02218524: ; 0x02218524
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	mov r0, #0
	add r2, sp, #0x10
	mov r1, #1
_02218530:
	add r0, r0, #1
	stmia r2!, {r1}
	cmp r0, #4
	blt _02218530
	add r0, r5, #0
	add r0, #0xa8
	ldrh r2, [r0]
	add r0, r5, #0
	add r0, #0xaa
	ldrh r0, [r0]
	cmp r2, r0
	bhi _02218570
	add r0, r5, #0
	add r0, #0xad
	ldrb r0, [r0]
	lsl r0, r0, #2
	add r0, r5, r0
	add r0, #0x98
	ldr r0, [r0]
	bl FUN_0200C644
	add r0, r5, #0
	add r0, #0xad
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0xad
	strb r1, [r0]
	add r0, r5, #0
	mov r1, #0
	add r0, #0xaa
	strh r1, [r0]
_02218570:
	add r0, r5, #0
	add r0, #0xad
	ldrb r1, [r0]
	add r0, r5, #0
	add r0, #0xac
	ldrb r0, [r0]
	cmp r1, r0
	bhs _0221858E
	add r0, r5, #0
	add r0, #0xaa
	ldrh r0, [r0]
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0xaa
	strh r1, [r0]
_0221858E:
	mov r0, #0
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xad
	ldrb r0, [r0]
	cmp r0, #0
	ble _0221862E
	add r0, sp, #0x10
	add r7, r5, #4
	str r0, [sp, #4]
	add r6, r5, #0
	add r4, r5, #0
_022185A6:
	add r1, r5, #0
	add r1, #0x94
	ldr r1, [r1]
	add r0, r7, #0
	blx r1
	ldr r1, [sp, #4]
	cmp r0, #0
	str r0, [r1]
	beq _02218604
	add r0, r5, #0
	add r0, #0xae
	ldrb r0, [r0]
	cmp r0, #0
	bne _022185EA
	mov r1, #0
	mov r2, #4
	ldrsh r1, [r5, r1]
	ldrsh r2, [r6, r2]
	add r0, r4, #0
	add r0, #0x98
	add r1, r1, r2
	mov r2, #2
	ldrsh r3, [r5, r2]
	mov r2, #6
	ldrsh r2, [r6, r2]
	lsl r1, r1, #0x10
	ldr r0, [r0]
	add r2, r3, r2
	lsl r2, r2, #0x10
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	b _02218610
_022185EA:
	add r0, r7, #0
	add r1, sp, #0xc
	add r2, sp, #8
	bl MOD08_0221825C
	add r0, r4, #0
	add r0, #0x98
	ldr r0, [r0]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #8]
	bl FUN_0200C884
	b _02218610
_02218604:
	add r0, r4, #0
	add r0, #0x98
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0200C644
_02218610:
	ldr r0, [sp, #4]
	add r7, #0x24
	add r0, r0, #4
	str r0, [sp, #4]
	ldr r0, [sp]
	add r6, #0x24
	add r0, r0, #1
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xad
	ldrb r1, [r0]
	ldr r0, [sp]
	add r4, r4, #4
	cmp r0, r1
	blt _022185A6
_0221862E:
	add r5, #0xac
	ldrb r2, [r5]
	mov r3, #0
	cmp r2, #0
	ble _0221864E
	add r1, sp, #0x10
_0221863A:
	ldr r0, [r1]
	cmp r0, #1
	bne _02218646
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02218646:
	add r3, r3, #1
	add r1, r1, #4
	cmp r3, r2
	blt _0221863A
_0221864E:
	mov r0, #0
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02218654
MOD08_02218654: ; 0x02218654
	push {r3, r4, r5, lr}
	sub sp, #0x10
	ldr r3, _02218684 ; =0x0000FFFF
	add r4, r1, #0
	mov r1, #2
	str r3, [sp]
	lsl r1, r1, #0x10
	str r1, [sp, #4]
	ldr r1, _02218688 ; =0xFFFF8000
	add r5, r0, #0
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	mov r1, #0
	add r2, r3, #0
	add r3, r1, #0
	bl MOD08_02217D14
	ldr r0, [r5, #4]
	add r1, r0, #0
	mul r1, r4
	str r1, [r5, #4]
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_02218684: .word 0x0000FFFF
_02218688: .word 0xFFFF8000

	thumb_func_start MOD08_0221868C
MOD08_0221868C: ; 0x0221868C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02217ECC
	cmp r0, #0
	bne _022186A8
	mov r0, #1
	str r0, [r4, #0x24]
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
_022186A8:
	mov r0, #0
	ldrsh r1, [r4, r0]
	cmp r1, #0
	bge _022186B2
	strh r0, [r4]
_022186B2:
	mov r0, #2
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bge _022186BE
	mov r0, #0
	strh r0, [r4, #2]
_022186BE:
	mov r0, #0
	ldrsh r1, [r4, r0]
	mov r0, #2
	ldrsh r0, [r4, r0]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _022186D0 ; =0x04000052
	strh r1, [r0]
	pop {r3, r4, r5, pc}
	.align 2, 0
_022186D0: .word 0x04000052

	thumb_func_start MOD08_022186D4
MOD08_022186D4: ; 0x022186D4
	push {r4, r5, r6, lr}
	sub sp, #8
	add r6, sp, #8
	mov r5, #0x10
	ldrsh r5, [r6, r5]
	add r4, r0, #0
	str r5, [sp]
	ldr r5, [sp, #0x1c]
	lsl r5, r5, #0x10
	lsr r5, r5, #0x10
	str r5, [sp, #4]
	bl MOD08_02217E80
	mov r2, #0
	ldr r0, _02218700 ; =MOD08_0221868C
	add r1, r4, #0
	str r2, [r4, #0x24]
	bl FUN_0200CA44
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_02218700: .word MOD08_0221868C

	thumb_func_start MOD08_02218704
MOD08_02218704: ; 0x02218704
	ldr r0, [r0, #0x24]
	bx lr

	thumb_func_start MOD08_02218708
MOD08_02218708: ; 0x02218708
	push {r3, lr}
	ldr r0, [r1, #8]
	cmp r0, #0
	beq _0221871C
	mov r0, #1
	str r0, [r1, #0xc]
	ldr r0, [r1, #0x18]
	ldr r1, [r1, #0x10]
	blx r1
	pop {r3, pc}
_0221871C:
	bl FUN_020129C8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD08_02218724
MOD08_02218724: ; 0x02218724
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _0221873E
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _0221873E
	ldr r0, [r4, #0x18]
	ldr r1, [r4, #0x14]
	blx r1
	mov r0, #0
	str r0, [r4, #0xc]
_0221873E:
	pop {r4, pc}

	thumb_func_start MOD08_02218740
MOD08_02218740: ; 0x02218740
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	cmp r5, #0
	bne _02218752
	bl ErrorHandling
_02218752:
	mov r0, #1
	str r0, [r5, #8]
	mov r2, #0
	str r2, [r5, #0xc]
	str r4, [r5, #0x18]
	str r6, [r5, #0x10]
	ldr r0, _02218778 ; =MOD08_02218708
	str r7, [r5, #0x14]
	add r1, r5, #0
	bl FUN_0200CA98
	str r0, [r5, #4]
	ldr r0, _0221877C ; =MOD08_02218724
	add r1, r5, #0
	mov r2, #0
	bl FUN_0200CA60
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02218778: .word MOD08_02218708
_0221877C: .word MOD08_02218724

	thumb_func_start MOD08_02218780
MOD08_02218780: ; 0x02218780
	push {r4, lr}
	add r4, r0, #0
	bne _0221878A
	bl ErrorHandling
_0221878A:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _02218794
	bl FUN_0200CAB4
_02218794:
	ldr r0, [r4]
	cmp r0, #0
	beq _0221879E
	bl FUN_0200CAB4
_0221879E:
	bl FUN_020129C8
	pop {r4, pc}

	thumb_func_start MOD08_022187A4
MOD08_022187A4: ; 0x022187A4
	push {r4, lr}
	add r4, r0, #0
	bne _022187AE
	bl ErrorHandling
_022187AE:
	mov r0, #0
	str r0, [r4, #8]
	pop {r4, pc}

	thumb_func_start MOD08_022187B4
MOD08_022187B4: ; 0x022187B4
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x1c]
	bl FUN_0201299C
	add r5, r0, #0
	bl FUN_020129C8
	mov r1, #0x62
	lsl r1, r1, #4
	ldr r1, [r4, r1]
	add r0, r5, #0
	mov r2, #4
	mov r3, #1
	bl FUN_020129D8
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_022187D8
MOD08_022187D8: ; 0x022187D8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x1c]
	bl FUN_020129B4
	add r0, r4, #0
	bl MOD08_022187B4
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_022187EC
MOD08_022187EC: ; 0x022187EC
	ldr r3, _022187F0 ; =MOD08_022187B4
	bx r3
	.align 2, 0
_022187F0: .word MOD08_022187B4

	thumb_func_start MOD08_022187F4
MOD08_022187F4: ; 0x022187F4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r7, r2, #0
	add r5, r0, #0
	ldr r1, _02218864 ; =0x00000624
	add r0, r7, #0
	bl AllocFromHeap
	ldr r2, _02218864 ; =0x00000624
	mov r1, #0
	add r4, r0, #0
	bl memset
	cmp r4, #0
	bne _02218816
	bl ErrorHandling
_02218816:
	mov r2, #0x32
	add r1, r4, #0
	lsl r2, r2, #4
	add r0, r7, #0
	add r1, #0x20
	add r2, r4, r2
	bl FUN_02012944
	str r0, [r4, #0x1c]
	cmp r0, #0
	bne _02218830
	bl ErrorHandling
_02218830:
	mov r0, #0x62
	lsl r0, r0, #4
	add r1, r4, #0
	mov r2, #3
	str r5, [r4, r0]
	add r0, r6, #0
	add r1, #0x20
	lsl r2, r2, #8
	bl MIi_CpuClear32
	mov r2, #0x32
	lsl r2, r2, #4
	add r1, r4, r2
	add r0, r6, #0
	sub r2, #0x20
	bl MIi_CpuClear32
	ldr r2, _02218868 ; =MOD08_022187D8
	ldr r3, _0221886C ; =MOD08_022187EC
	add r0, r4, #0
	add r1, r4, #0
	bl MOD08_02218740
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02218864: .word 0x00000624
_02218868: .word MOD08_022187D8
_0221886C: .word MOD08_022187EC

	thumb_func_start MOD08_02218870
MOD08_02218870: ; 0x02218870
	push {r4, lr}
	add r4, r0, #0
	bne _0221887A
	bl ErrorHandling
_0221887A:
	add r0, r4, #0
	bl MOD08_02218780
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _0221888A
	bl FUN_02012974
_0221888A:
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02218894
MOD08_02218894: ; 0x02218894
	push {r4, lr}
	add r4, r0, #0
	bne _0221889E
	bl ErrorHandling
_0221889E:
	ldr r0, [r4, #0x1c]
	bl FUN_02012988
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_022188A8
MOD08_022188A8: ; 0x022188A8
	push {r4, lr}
	add r4, r0, #0
	bne _022188B2
	bl ErrorHandling
_022188B2:
	add r0, r4, #0
	bl MOD08_022187A4
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_022188BC
MOD08_022188BC: ; 0x022188BC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x1c]
	bl FUN_02012B30
	ldr r0, [r4, #0x1c]
	bl FUN_02012B68
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_022188D0
MOD08_022188D0: ; 0x022188D0
	ldr r3, _022188D8 ; =FUN_02012B68
	ldr r0, [r0, #0x1c]
	bx r3
	nop
_022188D8: .word FUN_02012B68

	thumb_func_start MOD08_022188DC
MOD08_022188DC: ; 0x022188DC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r7, r0, #0
	str r1, [sp, #0x14]
	ldr r0, [sp, #0x40]
	mov r1, #0x20
	str r2, [sp, #0x18]
	add r5, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	bne _022188F8
	bl ErrorHandling
_022188F8:
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x20
	bl memset
	ldr r0, [sp, #0x34]
	bl MOD08_022189A0
	add r6, r0, #0
	ldr r0, [sp, #0x40]
	bl FUN_02012A00
	str r0, [r4, #0x1c]
	str r5, [sp]
	add r1, sp, #0x20
	mov r0, #0x10
	ldrsh r0, [r1, r0]
	add r1, r7, #0
	str r0, [sp, #4]
	ldr r0, [sp, #0x3c]
	str r6, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x38]
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x1c]
	ldr r2, [sp, #0x14]
	ldr r3, [sp, #0x18]
	bl FUN_02012A30
	ldr r2, _02218944 ; =MOD08_022188BC
	ldr r3, _02218948 ; =MOD08_022188D0
	add r0, r4, #0
	add r1, r4, #0
	bl MOD08_02218740
	add r0, r4, #0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02218944: .word MOD08_022188BC
_02218948: .word MOD08_022188D0

	thumb_func_start MOD08_0221894C
MOD08_0221894C: ; 0x0221894C
	push {r4, lr}
	add r4, r0, #0
	bne _02218956
	bl ErrorHandling
_02218956:
	add r0, r4, #0
	bl MOD08_02218780
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _02218966
	bl FUN_02012B00
_02218966:
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02218970
MOD08_02218970: ; 0x02218970
	push {r4, lr}
	add r4, r0, #0
	bne _0221897A
	bl ErrorHandling
_0221897A:
	ldr r0, [r4, #0x1c]
	bl FUN_02012B20
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02218984
MOD08_02218984: ; 0x02218984
	push {r4, lr}
	add r4, r0, #0
	bne _0221898E
	bl ErrorHandling
_0221898E:
	add r0, r4, #0
	bl MOD08_022187A4
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02218998
MOD08_02218998: ; 0x02218998
	lsl r1, r1, #0x10
	orr r0, r1
	bx lr
	.align 2, 0

	thumb_func_start MOD08_022189A0
MOD08_022189A0: ; 0x022189A0
	cmp r0, #3
	bhi _022189C6
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022189B0: ; jump table
	.short _022189B8 - _022189B0 - 2 ; case 0
	.short _022189BC - _022189B0 - 2 ; case 1
	.short _022189C0 - _022189B0 - 2 ; case 2
	.short _022189C4 - _022189B0 - 2 ; case 3
_022189B8:
	ldr r0, _022189C8 ; =0x04000010
	bx lr
_022189BC:
	ldr r0, _022189CC ; =0x04000014
	bx lr
_022189C0:
	ldr r0, _022189D0 ; =0x04000018
	bx lr
_022189C4:
	ldr r0, _022189D4 ; =0x0400001C
_022189C6:
	bx lr
	.align 2, 0
_022189C8: .word 0x04000010
_022189CC: .word 0x04000014
_022189D0: .word 0x04000018
_022189D4: .word 0x0400001C

	thumb_func_start MOD08_022189D8
MOD08_022189D8: ; 0x022189D8
	add r2, r0, r2
	lsr r0, r2, #0x1f
	add r0, r2, r0
	asr r2, r0, #1
	ldr r0, [sp]
	add r1, r1, r3
	strh r2, [r0]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r1, r0, #1
	ldr r0, [sp, #4]
	strh r1, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_022189F4
MOD08_022189F4: ; 0x022189F4
	push {r3, lr}
	sub r1, r1, r3
	neg r1, r1
	sub r0, r0, r2
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	asr r1, r1, #0x10
	add r2, r1, #0
	asr r0, r0, #0x10
	mul r2, r1
	add r1, r0, #0
	mul r1, r0
	add r0, r2, r1
	lsl r0, r0, #0xc
	bl FX_Sqrt
	ldr r1, [sp, #8]
	str r0, [r1]
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD08_02218A1C
MOD08_02218A1C: ; 0x02218A1C
	push {r4, r5, r6, lr}
	add r6, r0, #0
	sub r0, r1, r3
	neg r0, r0
	lsl r0, r0, #0x10
	sub r1, r6, r2
	asr r4, r0, #0x10
	lsl r1, r1, #0x10
	ldr r5, [sp, #0x10]
	lsl r0, r4, #0xc
	asr r1, r1, #4
	bl FX_Atan2
	strh r0, [r5]
	ldrh r1, [r5]
	cmp r1, #0
	beq _02218A4C
	cmp r4, #0
	bge _02218A4C
	ldr r0, _02218A50 ; =0x00007FFF
	sub r1, r1, r0
	ldr r0, _02218A54 ; =0x0000FFFF
	mul r0, r1
	strh r0, [r5]
_02218A4C:
	pop {r4, r5, r6, pc}
	nop
_02218A50: .word 0x00007FFF
_02218A54: .word 0x0000FFFF

	thumb_func_start MOD08_02218A58
MOD08_02218A58: ; 0x02218A58
	cmp r2, #0
	ldr r3, [r0]
	bge _02218A70
	add r2, r3, r2
	cmp r2, r1
	ble _02218A6A
	str r2, [r0]
	mov r0, #0
	bx lr
_02218A6A:
	str r1, [r0]
	mov r0, #1
	bx lr
_02218A70:
	add r2, r3, r2
	cmp r2, r1
	bge _02218A7C
	str r2, [r0]
	mov r0, #0
	bx lr
_02218A7C:
	str r1, [r0]
	mov r0, #1
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02218A84
MOD08_02218A84: ; 0x02218A84
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _02218AF4
	mov r0, #0x17
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #0x17]
	ldrsb r1, [r4, r0]
	mov r0, #0x16
	ldrsb r0, [r4, r0]
	cmp r1, r0
	blt _02218AF4
	mov r0, #0
	strb r0, [r4, #0x17]
	ldrb r0, [r4, #0x14]
	str r0, [sp]
	ldrh r0, [r4, #0x10]
	str r0, [sp, #4]
	ldrh r2, [r4, #0xc]
	ldrh r3, [r4, #0xe]
	ldr r0, [r4, #0x18]
	ldr r1, [r4, #8]
	bl FUN_020039E8
	ldrb r3, [r4, #0x13]
	ldrb r1, [r4, #0x14]
	cmp r1, r3
	bne _02218ACA
	mov r0, #0
	add sp, #8
	str r0, [r4]
	pop {r4, pc}
_02218ACA:
	mov r0, #0x15
	ldrsb r2, [r4, r0]
	add r1, r1, r2
	lsl r0, r1, #0x18
	asr r0, r0, #0x18
	cmp r2, #0
	ble _02218AE8
	cmp r0, r3
	ble _02218AE2
	add sp, #8
	strb r3, [r4, #0x14]
	pop {r4, pc}
_02218AE2:
	add sp, #8
	strb r1, [r4, #0x14]
	pop {r4, pc}
_02218AE8:
	cmp r0, r3
	bge _02218AF2
	add sp, #8
	strb r3, [r4, #0x14]
	pop {r4, pc}
_02218AF2:
	strb r1, [r4, #0x14]
_02218AF4:
	add sp, #8
	pop {r4, pc}

	thumb_func_start MOD08_02218AF8
MOD08_02218AF8: ; 0x02218AF8
	push {r4, lr}
	add r4, r0, #0
	bne _02218B02
	bl ErrorHandling
_02218B02:
	ldr r0, [r4]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02218B08
MOD08_02218B08: ; 0x02218B08
	push {r4, lr}
	add r4, r0, #0
	bne _02218B12
	bl ErrorHandling
_02218B12:
	ldr r0, [r4, #4]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD08_02218B20
MOD08_02218B20: ; 0x02218B20
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r0, r1, #0
	mov r1, #0x1c
	add r6, r2, #0
	add r7, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	bne _02218B38
	bl ErrorHandling
_02218B38:
	str r5, [r4, #0x18]
	str r6, [r4, #8]
	strh r7, [r4, #0xc]
	add r1, sp, #8
	ldrh r0, [r1, #0x10]
	strh r0, [r4, #0xe]
	ldrh r0, [r1, #0x24]
	strh r0, [r4, #0x10]
	ldrb r2, [r1, #0x1c]
	add r0, sp, #0x28
	ldrb r0, [r0]
	strb r2, [r4, #0x12]
	strb r0, [r4, #0x13]
	strb r2, [r4, #0x14]
	mov r0, #0x14
	ldrsb r0, [r1, r0]
	strb r0, [r4, #0x16]
	strb r0, [r4, #0x17]
	ldrb r2, [r4, #0x12]
	ldrb r0, [r4, #0x13]
	cmp r2, r0
	bhs _02218B6A
	mov r0, #0x18
	ldrsb r0, [r1, r0]
	b _02218B70
_02218B6A:
	mov r0, #0x18
	ldrsb r0, [r1, r0]
	neg r0, r0
_02218B70:
	strb r0, [r4, #0x15]
	mov r0, #1
	str r0, [r4]
	ldr r0, _02218B88 ; =MOD08_02218A84
	ldr r2, [sp, #0x30]
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #4]
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02218B88: .word MOD08_02218A84

	thumb_func_start MOD08_02218B8C
MOD08_02218B8C: ; 0x02218B8C
	push {r4, r5, r6, r7}
	mov r7, #0
	cmp r1, #0
	ble _02218BCE
	mov r2, #0x97
_02218B96:
	ldrh r6, [r0]
	mov r3, #0x1f
	add r7, r7, #1
	asr r4, r6, #0xa
	and r4, r3
	add r5, r4, #0
	mov r3, #0x1d
	mul r5, r3
	mov r3, #0x1f
	and r3, r6
	mov r4, #0x4c
	mul r4, r3
	asr r6, r6, #5
	mov r3, #0x1f
	and r3, r6
	add r6, r3, #0
	mul r6, r2
	add r3, r4, r6
	add r3, r5, r3
	asr r5, r3, #8
	lsl r4, r5, #0xa
	lsl r3, r5, #5
	orr r3, r4
	orr r3, r5
	strh r3, [r0]
	add r0, r0, #2
	cmp r7, r1
	blt _02218B96
_02218BCE:
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02218BD4
MOD08_02218BD4: ; 0x02218BD4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD08_02215504
	mov r1, #0
	bl FUN_02003204
	add r4, r0, #0
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _02218BF8
	add r0, r4, #0
	mov r1, #0x30
	bl MOD08_02218B8C
	pop {r3, r4, r5, pc}
_02218BF8:
	add r0, r4, #0
	mov r1, #0x80
	bl MOD08_02218B8C
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02218C04
MOD08_02218C04: ; 0x02218C04
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	bl MOD08_02215504
	add r4, r0, #0
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _02218C30
	mov r1, #0
	str r1, [sp]
	mov r0, #0x60
	str r0, [sp, #4]
	add r0, r4, #0
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020031B8
	add sp, #8
	pop {r3, r4, r5, pc}
_02218C30:
	mov r1, #0
	mov r0, #1
	str r1, [sp]
	lsl r0, r0, #8
	str r0, [sp, #4]
	add r0, r4, #0
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020031B8
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02218C48
MOD08_02218C48: ; 0x02218C48
	cmp r0, #0x54
	blo _02218C50
	mov r0, #0
	bx lr
_02218C50:
	lsl r1, r0, #2
	ldr r0, _02218C58 ; =0x0222C384
	ldr r0, [r0, r1]
	bx lr
	.align 2, 0
_02218C58: .word MOD8_0222C384

	thumb_func_start MOD08_02218C5C
MOD08_02218C5C: ; 0x02218C5C
	cmp r0, #0x21
	blo _02218C64
	mov r0, #0
	bx lr
_02218C64:
	lsl r1, r0, #2
	ldr r0, _02218C6C ; =0x0222C300
	ldr r0, [r0, r1]
	bx lr
	.align 2, 0
_02218C6C: .word MOD8_0222C300

	thumb_func_start MOD08_02218C70
MOD08_02218C70: ; 0x02218C70
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02218C74
MOD08_02218C74: ; 0x02218C74
	push {r4, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _02218C86
	cmp r0, #1
	beq _02218C8C
	pop {r4, pc}
_02218C86:
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, pc}
_02218C8C:
	ldr r0, [r4, #4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD08_02218C9C
MOD08_02218C9C: ; 0x02218C9C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #5
	mov r1, #8
	bl AllocFromHeap
	add r2, r0, #0
	mov r0, #0
	strb r0, [r2]
	mov r3, #1
	ldr r1, _02218CC0 ; =MOD08_02218C74
	add r0, r4, #0
	lsl r3, r3, #0xc
	str r4, [r2, #4]
	bl MOD08_022123E4
	pop {r4, pc}
	nop
_02218CC0: .word MOD08_02218C74

	thumb_func_start MOD08_02218CC4
MOD08_02218CC4: ; 0x02218CC4
	push {r4, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _02218CD6
	cmp r0, #1
	beq _02218CDC
	pop {r4, pc}
_02218CD6:
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, pc}
_02218CDC:
	ldr r0, [r4, #4]
	add r1, r2, #0
	bl MOD08_02212448
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD08_02218CEC
MOD08_02218CEC: ; 0x02218CEC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #5
	mov r1, #8
	bl AllocFromHeap
	add r2, r0, #0
	mov r0, #0
	strb r0, [r2]
	mov r3, #1
	ldr r1, _02218D10 ; =MOD08_02218CC4
	add r0, r4, #0
	lsl r3, r3, #0xc
	str r4, [r2, #4]
	bl MOD08_0221241C
	pop {r4, pc}
	nop
_02218D10: .word MOD08_02218CC4

	thumb_func_start MOD08_02218D14
MOD08_02218D14: ; 0x02218D14
	push {r4, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	cmp r1, #0
	beq _02218D24
	cmp r1, #1
	beq _02218D2A
	pop {r4, pc}
_02218D24:
	add r0, r1, #1
	strb r0, [r4]
	pop {r4, pc}
_02218D2A:
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02218D38
MOD08_02218D38: ; 0x02218D38
	push {r4, lr}
	add r4, r0, #0
	mov r0, #5
	mov r1, #8
	bl AllocFromHeap
	add r1, r0, #0
	mov r0, #0
	strb r0, [r1]
	mov r2, #1
	ldr r0, _02218D58 ; =MOD08_02218D14
	lsl r2, r2, #0xc
	str r4, [r1, #4]
	bl FUN_0200CA44
	pop {r4, pc}
	.align 2, 0
_02218D58: .word MOD08_02218D14

	thumb_func_start MOD08_02218D5C
MOD08_02218D5C: ; 0x02218D5C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	ldrb r0, [r5]
	cmp r0, #0
	beq _02218D6E
	cmp r0, #1
	beq _02218DB4
	pop {r4, r5, r6, pc}
_02218D6E:
	ldr r0, [r5, #0x14]
	ldr r0, [r0]
	bl FUN_0200C59C
	ldr r0, [r5, #0x18]
	ldr r0, [r0]
	bl FUN_0200C59C
	ldr r0, [r5, #0x1c]
	ldr r0, [r0]
	bl FUN_0200C59C
	ldr r0, [r5, #0x14]
	mov r1, #1
	ldr r0, [r0]
	mov r2, #0
	bl FUN_0200C7FC
	ldr r0, [r5, #0x18]
	mov r1, #0
	ldr r0, [r0]
	mvn r1, r1
	mov r2, #0
	bl FUN_0200C7FC
	ldr r0, [r5, #0x1c]
	mov r1, #1
	ldr r0, [r0]
	add r2, r1, #0
	bl FUN_0200C7FC
	ldr r0, [r5, #0xc]
	bl FUN_0200BC1C
	pop {r4, r5, r6, pc}
_02218DB4:
	ldr r0, [r5, #0x10]
	ldr r4, [r5, #4]
	bl FUN_0200C3DC
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	add r1, r6, #0
	bl MOD08_02212438
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_02218DCC
MOD08_02218DCC: ; 0x02218DCC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r6, r1, #0
	mov r1, #0x73
	str r0, [sp]
	mov r0, #5
	lsl r1, r1, #2
	add r7, r2, #0
	add r5, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	bne _02218DEA
	bl ErrorHandling
_02218DEA:
	mov r0, #0
	strb r0, [r4]
	str r6, [r4, #8]
	str r7, [r4, #0xc]
	ldr r0, [sp]
	str r5, [r4, #0x10]
	str r0, [r4, #4]
	ldr r1, [sp]
	add r0, sp, #4
	bl MOD08_02215474
	str r5, [r4, #0x14]
	mov r6, #1
	add r5, r4, #4
	add r7, sp, #4
_02218E08:
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	add r2, r7, #0
	bl FUN_0200C154
	str r0, [r5, #0x14]
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #3
	blt _02218E08
	mov r3, #1
	ldr r0, [sp]
	ldr r1, _02218E30 ; =MOD08_02218D5C
	add r2, r4, #0
	lsl r3, r3, #0xc
	bl MOD08_022123E4
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02218E30: .word MOD08_02218D5C

	thumb_func_start MOD08_02218E34
MOD08_02218E34: ; 0x02218E34
	push {r4, lr}
	mov r1, #0xc
	add r2, r1, #0
	add r2, #0xf4
	add r4, r0, #0
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf3
	bl FUN_02007558
	pop {r4, pc}

	thumb_func_start MOD08_02218E50
MOD08_02218E50: ; 0x02218E50
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r2, r0, #0
	ldrb r0, [r5, #4]
	cmp r0, #0
	beq _02218E62
	cmp r0, #1
	beq _02218E84
	b _02218F4E
_02218E62:
	mov r0, #0x26
	ldrsh r0, [r5, r0]
	mov r1, #0x20
	mov r2, #0x22
	str r0, [sp]
	mov r3, #0x24
	add r0, r5, #0
	ldrsh r1, [r5, r1]
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	add r0, #0x7c
	bl MOD08_022183C0
	ldrb r0, [r5, #4]
	add r0, r0, #1
	strb r0, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
_02218E84:
	add r0, r5, #0
	add r0, #0x7c
	bl MOD08_022183F0
	cmp r0, #0
	bne _02218E98
	ldrb r0, [r5, #4]
	add r0, r0, #1
	strb r0, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
_02218E98:
	ldr r2, [r5, #0x28]
	mov r1, #1
	lsl r1, r1, #8
	add r0, r2, #0
	and r0, r1
	cmp r0, r1
	bne _02218EE4
	ldr r0, [r5]
	mov r6, #0
	cmp r0, #0
	ble _02218F32
	add r4, r5, #0
	mov r7, #0x32
_02218EB2:
	ldr r0, [r4, #0x34]
	cmp r0, #0
	beq _02218ED8
	mov r2, #0x7c
	mov r3, #0x30
	ldrsh r2, [r5, r2]
	ldrsh r3, [r4, r3]
	mov r1, #0
	add r2, r2, r3
	bl FUN_02007558
	mov r2, #0x7e
	ldrsh r3, [r5, r2]
	ldrsh r2, [r4, r7]
	ldr r0, [r4, #0x34]
	mov r1, #1
	add r2, r3, r2
	bl FUN_02007558
_02218ED8:
	ldr r0, [r5]
	add r6, r6, #1
	add r4, #0x14
	cmp r6, r0
	blt _02218EB2
	b _02218F32
_02218EE4:
	lsl r0, r1, #1
	and r2, r0
	cmp r2, r0
	bne _02218F32
	ldr r0, [r5]
	mov r6, #0
	cmp r0, #0
	ble _02218F2C
	add r4, r5, #0
	mov r7, #0x32
_02218EF8:
	ldr r0, [r4, #0x38]
	cmp r0, #0
	beq _02218F22
	mov r1, #0x7c
	mov r2, #0x30
	ldrsh r1, [r5, r1]
	ldrsh r2, [r4, r2]
	add r1, r1, r2
	mov r2, #0x7e
	ldrsh r3, [r5, r2]
	ldrsh r2, [r4, r7]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add r2, r3, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	ldr r0, [r4, #0x38]
	bl FUN_0200C5A8
_02218F22:
	ldr r0, [r5]
	add r6, r6, #1
	add r4, #0x14
	cmp r6, r0
	blt _02218EF8
_02218F2C:
	ldr r0, [r5, #0x10]
	bl FUN_0200BC1C
_02218F32:
	mov r0, #1
	ldr r1, [r5, #0x28]
	lsl r0, r0, #0xa
	and r1, r0
	cmp r1, r0
	bne _02218F5C
	mov r3, #0x7c
	ldrsh r3, [r5, r3]
	ldr r0, [r5, #0x18]
	mov r1, #3
	mov r2, #0
	bl FUN_020179E0
	pop {r3, r4, r5, r6, r7, pc}
_02218F4E:
	ldr r0, [r5, #8]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r5, #0
	bl FreeToHeap
_02218F5C:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02218F60
MOD08_02218F60: ; 0x02218F60
	push {r3, r4, r5, lr}
	mov r1, #0xa0
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #4
	bl MOD08_02227B70
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	strh r0, [r4, #0x20]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	strh r0, [r4, #0x22]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	strh r0, [r4, #0x24]
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	strh r0, [r4, #0x26]
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	mov r2, #1
	lsl r2, r2, #8
	str r0, [r4, #0x28]
	add r1, r0, #0
	and r0, r2
	cmp r0, r2
	bne _02218FC0
	add r2, r4, #0
	add r0, r5, #0
	add r2, #0x2c
	add r3, r4, #0
	bl MOD08_02227BAC
	b _02218FD6
_02218FC0:
	lsl r0, r2, #1
	add r3, r1, #0
	and r3, r0
	cmp r3, r0
	bne _02218FD6
	add r2, r4, #0
	add r0, r5, #0
	add r2, #0x2c
	add r3, r4, #0
	bl MOD08_02227F88
_02218FD6:
	ldr r0, [r4, #8]
	ldr r1, _02218FE4 ; =MOD08_02218E50
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, pc}
	nop
_02218FE4: .word MOD08_02218E50

	thumb_func_start MOD08_02218FE8
MOD08_02218FE8: ; 0x02218FE8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x1c]
	cmp r0, #3
	bhi _022190B2
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02219000: ; jump table
	.short _02219008 - _02219000 - 2 ; case 0
	.short _02219026 - _02219000 - 2 ; case 1
	.short _02219068 - _02219000 - 2 ; case 2
	.short _02219074 - _02219000 - 2 ; case 3
_02219008:
	ldrh r0, [r4, #0x18]
	mov r1, #4
	mov r2, #0x39
	str r0, [sp]
	ldrh r3, [r4, #0x16]
	ldr r0, _02219154 ; =0x04000050
	bl G2x_SetBlendAlpha_
	mov r0, #2
	mov r1, #1
	bl FUN_0201797C
	ldrb r0, [r4, #0x1c]
	add r0, r0, #1
	strb r0, [r4, #0x1c]
_02219026:
	ldrh r1, [r4, #8]
	ldrh r2, [r4, #0x16]
	mov r0, #0
	sub r1, r1, #2
	cmp r2, r1
	bge _02219038
	add r1, r2, #2
	strh r1, [r4, #0x16]
	b _0221903A
_02219038:
	add r0, r0, #1
_0221903A:
	ldrh r1, [r4, #0x18]
	cmp r1, #9
	bls _02219046
	sub r1, r1, #2
	strh r1, [r4, #0x18]
	b _02219048
_02219046:
	add r0, r0, #1
_02219048:
	cmp r0, #2
	bne _0221905A
	ldrh r0, [r4, #8]
	strh r0, [r4, #0x16]
	mov r0, #7
	strh r0, [r4, #0x18]
	ldrb r0, [r4, #0x1c]
	add r0, r0, #1
	strb r0, [r4, #0x1c]
_0221905A:
	ldrh r0, [r4, #0x18]
	ldrh r1, [r4, #0x16]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _02219158 ; =0x04000052
	strh r1, [r0]
	b _022190CA
_02219068:
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _022190CA
	add r0, r0, #1
	strb r0, [r4, #0x1c]
	b _022190CA
_02219074:
	ldrh r0, [r4, #0x16]
	mov r1, #0
	cmp r0, #2
	bls _02219082
	sub r0, r0, #2
	strh r0, [r4, #0x16]
	b _02219084
_02219082:
	add r1, r1, #1
_02219084:
	ldrh r0, [r4, #0x18]
	cmp r0, #0x1d
	bhs _02219090
	add r0, r0, #2
	strh r0, [r4, #0x18]
	b _02219092
_02219090:
	add r1, r1, #1
_02219092:
	cmp r1, #2
	bne _022190A4
	mov r0, #0
	strh r0, [r4, #0x16]
	mov r0, #0x1f
	strh r0, [r4, #0x18]
	ldrb r0, [r4, #0x1c]
	add r0, r0, #1
	strb r0, [r4, #0x1c]
_022190A4:
	ldrh r0, [r4, #0x18]
	ldrh r1, [r4, #0x16]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _02219158 ; =0x04000052
	strh r1, [r0]
	b _022190CA
_022190B2:
	mov r0, #2
	mov r1, #0
	bl FUN_0201797C
	ldr r0, [r4, #0x20]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
_022190CA:
	mov r1, #0x10
	ldrsh r3, [r4, r1]
	cmp r3, #0
	ble _022190DC
	mov r0, #0xc
	ldrsh r2, [r4, r0]
	lsl r0, r1, #5
	cmp r2, r0
	bge _022190EA
_022190DC:
	cmp r3, #0
	bge _022190EE
	mov r0, #0xc
	ldrsh r1, [r4, r0]
	ldr r0, _0221915C ; =0xFFFFFE64
	cmp r1, r0
	bgt _022190EE
_022190EA:
	mov r0, #1
	str r0, [r4, #4]
_022190EE:
	mov r0, #0xa
	ldrsh r1, [r4, r0]
	mov r0, #0xe
	ldrsh r0, [r4, r0]
	add r0, r1, r0
	strh r0, [r4, #0xa]
	mov r0, #0xc
	ldrsh r2, [r4, r0]
	mov r0, #0x10
	ldrsh r1, [r4, r0]
	add r1, r2, r1
	strh r1, [r4, #0xc]
	ldrh r2, [r4, #0x12]
	ldrh r1, [r4, #0x14]
	cmp r2, r1
	bhs _02219132
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bge _02219118
	add r0, r0, #1
	b _0221911A
_02219118:
	mov r0, #0
_0221911A:
	strh r0, [r4, #0x10]
	mov r0, #0xe
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bge _02219128
	add r0, r0, #1
	b _0221912A
_02219128:
	mov r0, #0
_0221912A:
	strh r0, [r4, #0xe]
	mov r0, #0
	strh r0, [r4, #0x14]
	b _02219136
_02219132:
	add r0, r1, #1
	strh r0, [r4, #0x14]
_02219136:
	mov r3, #0xa
	ldrsh r3, [r4, r3]
	ldr r0, [r4, #0x30]
	mov r1, #2
	mov r2, #0
	bl FUN_020179E0
	mov r3, #0xc
	ldrsh r3, [r4, r3]
	ldr r0, [r4, #0x30]
	mov r1, #2
	mov r2, #3
	bl FUN_020179E0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02219154: .word 0x04000050
_02219158: .word 0x04000052
_0221915C: .word 0xFFFFFE64

	thumb_func_start MOD08_02219160
MOD08_02219160: ; 0x02219160
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r1, #0xb8
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x1c
	bl MOD08_02227B70
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	strh r0, [r4, #0xa]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	strh r0, [r4, #0xc]
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	strh r0, [r4, #0xe]
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	strh r0, [r4, #0x10]
	add r0, r5, #0
	mov r1, #5
	bl MOD08_02212498
	str r0, [r4]
	add r0, r5, #0
	mov r1, #6
	bl MOD08_02212498
	strh r0, [r4, #8]
	add r0, r5, #0
	mov r1, #7
	bl MOD08_02212498
	strh r0, [r4, #0x12]
	mov r0, #0
	strh r0, [r4, #0x14]
	ldr r0, [r4]
	cmp r0, #0
	beq _0221920C
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_02227470
	cmp r0, #4
	bne _0221920C
	mov r0, #0xa
	ldrsh r1, [r4, r0]
	sub r0, #0xb
	mul r0, r1
	strh r0, [r4, #0xa]
	mov r1, #0xc
	add r0, r1, #0
	ldrsh r2, [r4, r1]
	sub r0, #0xd
	mul r0, r2
	strh r0, [r4, #0xc]
	mov r0, #0xe
	ldrsh r2, [r4, r0]
	sub r0, #0xf
	mul r0, r2
	strh r0, [r4, #0xe]
	mov r0, #0x10
	ldrsh r2, [r4, r0]
	sub r0, #0x11
	mul r0, r2
	strh r0, [r4, #0x10]
	ldrsh r0, [r4, r1]
	sub r0, #0x54
	strh r0, [r4, #0xc]
	b _02219214
_0221920C:
	mov r0, #0xc
	ldrsh r0, [r4, r0]
	add r0, #0x54
	strh r0, [r4, #0xc]
_02219214:
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _02219228
	mov r0, #0xe
	ldrsh r1, [r4, r0]
	sub r0, #0xf
	mul r0, r1
	strh r0, [r4, #0xe]
_02219228:
	mov r1, #0
	strh r1, [r4, #0x16]
	mov r0, #0x1f
	strh r0, [r4, #0x18]
	mov r0, #2
	str r1, [r4, #4]
	bl FUN_0201797C
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	mov r1, #0
	add r7, r0, #0
	bl MOD08_022156AC
	add r6, r0, #0
	add r0, r5, #0
	bl MOD08_02212014
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x30]
	mov r0, #7
	add r1, r6, #0
	mov r3, #2
	bl FUN_0200687C
	add r0, r7, #0
	mov r1, #1
	bl MOD08_022156AC
	add r6, r0, #0
	add r0, r5, #0
	bl MOD08_02212014
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x90
	str r0, [sp, #8]
	ldr r0, [r4, #0x34]
	mov r1, #7
	add r2, r6, #0
	bl FUN_020030E8
	ldr r0, [r4, #0x30]
	mov r1, #2
	bl FUN_02018744
	add r0, r5, #0
	mov r6, #2
	bl MOD08_02212004
	cmp r0, #1
	bne _022192A8
	mov r6, #4
	b _022192BC
_022192A8:
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_02227470
	cmp r0, #4
	bne _022192BC
	mov r6, #3
_022192BC:
	add r0, r7, #0
	add r1, r6, #0
	bl MOD08_022156AC
	add r6, r0, #0
	add r0, r5, #0
	bl MOD08_02212014
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x30]
	mov r0, #7
	add r1, r6, #0
	mov r3, #2
	bl FUN_020068C8
	mov r3, #0xa
	ldrsh r3, [r4, r3]
	ldr r0, [r4, #0x30]
	mov r1, #2
	mov r2, #0
	bl FUN_020179E0
	mov r3, #0xc
	ldrsh r3, [r4, r3]
	ldr r0, [r4, #0x30]
	mov r1, #2
	mov r2, #3
	bl FUN_020179E0
	ldr r0, [r4, #0x20]
	ldr r1, _02219310 ; =MOD08_02218FE8
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02219310: .word MOD08_02218FE8

	thumb_func_start MOD08_02219314
MOD08_02219314: ; 0x02219314
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x1c]
	cmp r0, #3
	bhi _022193DA
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0221932C: ; jump table
	.short _02219334 - _0221932C - 2 ; case 0
	.short _02219352 - _0221932C - 2 ; case 1
	.short _02219390 - _0221932C - 2 ; case 2
	.short _0221939C - _0221932C - 2 ; case 3
_02219334:
	ldrh r0, [r4, #0x18]
	mov r1, #4
	mov r2, #0x39
	str r0, [sp]
	ldrh r3, [r4, #0x16]
	ldr r0, _0221947C ; =0x04000050
	bl G2x_SetBlendAlpha_
	mov r0, #2
	mov r1, #1
	bl FUN_0201797C
	ldrb r0, [r4, #0x1c]
	add r0, r0, #1
	strb r0, [r4, #0x1c]
_02219352:
	ldrh r0, [r4, #0x16]
	mov r1, #0
	cmp r0, #0x10
	bhs _02219360
	add r0, r0, #2
	strh r0, [r4, #0x16]
	b _02219362
_02219360:
	add r1, r1, #1
_02219362:
	ldrh r0, [r4, #0x18]
	cmp r0, #4
	bls _0221936E
	sub r0, r0, #2
	strh r0, [r4, #0x18]
	b _02219370
_0221936E:
	add r1, r1, #1
_02219370:
	cmp r1, #2
	bne _02219382
	mov r0, #0x10
	strh r0, [r4, #0x16]
	mov r0, #4
	strh r0, [r4, #0x18]
	ldrb r0, [r4, #0x1c]
	add r0, r0, #1
	strb r0, [r4, #0x1c]
_02219382:
	ldrh r0, [r4, #0x18]
	ldrh r1, [r4, #0x16]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _02219480 ; =0x04000052
	strh r1, [r0]
	b _022193F2
_02219390:
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _022193F2
	add r0, r0, #1
	strb r0, [r4, #0x1c]
	b _022193F2
_0221939C:
	ldrh r0, [r4, #0x16]
	mov r1, #0
	cmp r0, #2
	bls _022193AA
	sub r0, r0, #2
	strh r0, [r4, #0x16]
	b _022193AC
_022193AA:
	add r1, r1, #1
_022193AC:
	ldrh r0, [r4, #0x18]
	cmp r0, #0x10
	bhs _022193B8
	add r0, r0, #2
	strh r0, [r4, #0x18]
	b _022193BA
_022193B8:
	add r1, r1, #1
_022193BA:
	cmp r1, #2
	bne _022193CC
	mov r0, #0
	strh r0, [r4, #0x16]
	mov r0, #0x1f
	strh r0, [r4, #0x18]
	ldrb r0, [r4, #0x1c]
	add r0, r0, #1
	strb r0, [r4, #0x1c]
_022193CC:
	ldrh r0, [r4, #0x18]
	ldrh r1, [r4, #0x16]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _02219480 ; =0x04000052
	strh r1, [r0]
	b _022193F2
_022193DA:
	mov r0, #2
	mov r1, #0
	bl FUN_0201797C
	ldr r0, [r4, #0x20]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
_022193F2:
	mov r1, #0x10
	ldrsh r3, [r4, r1]
	cmp r3, #0
	ble _02219404
	mov r0, #0xc
	ldrsh r2, [r4, r0]
	lsl r0, r1, #5
	cmp r2, r0
	bge _02219412
_02219404:
	cmp r3, #0
	bge _02219416
	mov r0, #0xc
	ldrsh r1, [r4, r0]
	ldr r0, _02219484 ; =0xFFFFFE64
	cmp r1, r0
	bgt _02219416
_02219412:
	mov r0, #1
	str r0, [r4, #4]
_02219416:
	mov r0, #0xa
	ldrsh r1, [r4, r0]
	mov r0, #0xe
	ldrsh r0, [r4, r0]
	add r0, r1, r0
	strh r0, [r4, #0xa]
	mov r0, #0xc
	ldrsh r2, [r4, r0]
	mov r0, #0x10
	ldrsh r1, [r4, r0]
	add r1, r2, r1
	strh r1, [r4, #0xc]
	ldrh r2, [r4, #0x12]
	ldrh r1, [r4, #0x14]
	cmp r2, r1
	bhs _0221945A
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bge _02219440
	add r0, r0, #1
	b _02219442
_02219440:
	mov r0, #0
_02219442:
	strh r0, [r4, #0x10]
	mov r0, #0xe
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bge _02219450
	add r0, r0, #1
	b _02219452
_02219450:
	mov r0, #0
_02219452:
	strh r0, [r4, #0xe]
	mov r0, #0
	strh r0, [r4, #0x14]
	b _0221945E
_0221945A:
	add r0, r1, #1
	strh r0, [r4, #0x14]
_0221945E:
	mov r3, #0xa
	ldrsh r3, [r4, r3]
	ldr r0, [r4, #0x30]
	mov r1, #2
	mov r2, #0
	bl FUN_020179E0
	mov r3, #0xc
	ldrsh r3, [r4, r3]
	ldr r0, [r4, #0x30]
	mov r1, #2
	mov r2, #3
	bl FUN_020179E0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221947C: .word 0x04000050
_02219480: .word 0x04000052
_02219484: .word 0xFFFFFE64

	thumb_func_start MOD08_02219488
MOD08_02219488: ; 0x02219488
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r1, #0xb8
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x1c
	bl MOD08_02227B70
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	strh r0, [r4, #0xa]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	strh r0, [r4, #0xc]
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	strh r0, [r4, #0xe]
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	strh r0, [r4, #0x10]
	add r0, r5, #0
	mov r1, #5
	bl MOD08_02212498
	str r0, [r4]
	add r0, r5, #0
	mov r1, #6
	bl MOD08_02212498
	strh r0, [r4, #8]
	add r0, r5, #0
	mov r1, #7
	bl MOD08_02212498
	strh r0, [r4, #0x12]
	mov r0, #0
	strh r0, [r4, #0x14]
	ldr r0, [r4]
	cmp r0, #0
	beq _02219534
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_02227470
	cmp r0, #4
	bne _02219534
	mov r0, #0xa
	ldrsh r1, [r4, r0]
	sub r0, #0xb
	mul r0, r1
	strh r0, [r4, #0xa]
	mov r1, #0xc
	add r0, r1, #0
	ldrsh r2, [r4, r1]
	sub r0, #0xd
	mul r0, r2
	strh r0, [r4, #0xc]
	mov r0, #0xe
	ldrsh r2, [r4, r0]
	sub r0, #0xf
	mul r0, r2
	strh r0, [r4, #0xe]
	mov r0, #0x10
	ldrsh r2, [r4, r0]
	sub r0, #0x11
	mul r0, r2
	strh r0, [r4, #0x10]
	ldrsh r0, [r4, r1]
	sub r0, #0x54
	strh r0, [r4, #0xc]
	b _0221953C
_02219534:
	mov r0, #0xc
	ldrsh r0, [r4, r0]
	add r0, #0x54
	strh r0, [r4, #0xc]
_0221953C:
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _02219550
	mov r0, #0xe
	ldrsh r1, [r4, r0]
	sub r0, #0xf
	mul r0, r1
	strh r0, [r4, #0xe]
_02219550:
	mov r0, #4
	strh r0, [r4, #0x16]
	mov r0, #0x10
	strh r0, [r4, #0x18]
	mov r1, #0
	strh r1, [r4, #0x16]
	strh r0, [r4, #0x18]
	mov r0, #2
	str r1, [r4, #4]
	bl FUN_0201797C
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	mov r1, #0
	add r7, r0, #0
	bl MOD08_022156AC
	add r6, r0, #0
	add r0, r5, #0
	bl MOD08_02212014
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x30]
	mov r0, #7
	add r1, r6, #0
	mov r3, #2
	bl FUN_0200687C
	add r0, r7, #0
	mov r1, #1
	bl MOD08_022156AC
	add r6, r0, #0
	add r0, r5, #0
	bl MOD08_02212014
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x90
	str r0, [sp, #8]
	ldr r0, [r4, #0x34]
	mov r1, #7
	add r2, r6, #0
	bl FUN_020030E8
	ldr r0, [r4, #0x30]
	mov r1, #2
	bl FUN_02018744
	add r0, r5, #0
	mov r6, #2
	bl MOD08_02212004
	cmp r0, #1
	bne _022195D6
	mov r6, #4
	b _022195EA
_022195D6:
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_02227470
	cmp r0, #4
	bne _022195EA
	mov r6, #3
_022195EA:
	add r0, r7, #0
	add r1, r6, #0
	bl MOD08_022156AC
	add r6, r0, #0
	add r0, r5, #0
	bl MOD08_02212014
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x30]
	mov r0, #7
	add r1, r6, #0
	mov r3, #2
	bl FUN_020068C8
	mov r3, #0xa
	ldrsh r3, [r4, r3]
	ldr r0, [r4, #0x30]
	mov r1, #2
	mov r2, #0
	bl FUN_020179E0
	mov r3, #0xc
	ldrsh r3, [r4, r3]
	ldr r0, [r4, #0x30]
	mov r1, #2
	mov r2, #3
	bl FUN_020179E0
	ldr r0, [r4, #0x20]
	ldr r1, _0221963C ; =MOD08_02219314
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0221963C: .word MOD08_02219314

	thumb_func_start MOD08_02219640
MOD08_02219640: ; 0x02219640
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _02219656
	cmp r0, #1
	beq _02219656
	cmp r0, #2
	beq _02219688
	pop {r3, r4, r5, pc}
_02219656:
	add r0, r4, #0
	add r0, #0xc
	bl MOD08_02218058
	cmp r0, #1
	bne _02219672
	ldr r2, [r4, #0xc]
	ldr r0, [r4, #8]
	lsl r2, r2, #0x10
	mov r1, #9
	lsr r2, r2, #0x10
	bl FUN_02007558
	pop {r3, r4, r5, pc}
_02219672:
	add r0, r4, #0
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x20]
	ldr r3, [r4, #0x24]
	add r0, #0xc
	bl MOD08_02218008
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_02219688:
	ldr r0, [r4, #8]
	mov r1, #0xa
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4, #8]
	mov r1, #0xb
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4, #8]
	mov r1, #9
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4, #4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_022196B8
MOD08_022196B8: ; 0x022196B8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl MOD08_02212014
	mov r1, #0x2c
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4]
	str r5, [r4, #4]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	str r0, [r4, #0x24]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	str r0, [r4, #0x20]
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	add r7, r0, #0
	beq _022196F2
	cmp r7, #2
	bne _022196FC
_022196F2:
	ldr r0, [r4, #4]
	bl MOD08_02212460
	str r0, [sp]
	b _02219704
_022196FC:
	ldr r0, [r4, #4]
	bl MOD08_02212458
	str r0, [sp]
_02219704:
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	add r2, r0, #0
	add r0, r4, #0
	ldr r1, [r4, #0x20]
	ldr r3, [r4, #0x24]
	add r0, #0xc
	bl MOD08_02218008
	ldr r1, [sp]
	add r0, r5, #0
	bl MOD08_02217C1C
	add r6, r0, #0
	ldr r0, [r4, #0x14]
	add r1, r0, #0
	mul r1, r6
	str r1, [r4, #0x14]
	cmp r7, #2
	bne _02219736
	mov r0, #0
	mvn r0, r0
	mul r6, r0
_02219736:
	ldr r0, [r4, #4]
	ldr r1, [sp]
	bl MOD08_022154D4
	str r0, [r4, #8]
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	cmp r0, #1
	bne _02219760
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	strh r0, [r4, #0x28]
	add r0, r5, #0
	mov r1, #5
	bl MOD08_02212498
	b _02219768
_02219760:
	mov r0, #0x28
	add r1, r6, #0
	mul r1, r0
	strh r1, [r4, #0x28]
_02219768:
	strh r0, [r4, #0x2a]
	mov r2, #0x28
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #8]
	mov r1, #0xa
	bl FUN_02007558
	mov r2, #0x2a
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #8]
	mov r1, #0xb
	bl FUN_02007558
	ldr r0, [r4, #4]
	ldr r1, _02219790 ; =MOD08_02219640
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02219790: .word MOD08_02219640

	thumb_func_start MOD08_02219794
MOD08_02219794: ; 0x02219794
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #0x2c
	mov r2, #0x2e
	add r5, r0, #0
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r3, [r4, #0x28]
	add r0, r4, #4
	bl MOD08_02217E58
	cmp r0, #0
	bne _022197E0
	mov r2, #0x2c
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl FUN_02007558
	mov r2, #0x2e
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x28]
	mov r1, #1
	sub r2, #8
	bl FUN_02007558
	ldr r0, [r4, #0x28]
	mov r1, #9
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_022197E0:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_022197E4
MOD08_022197E4: ; 0x022197E4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	bl MOD08_02212014
	mov r1, #0x30
	bl AllocFromHeap
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #0
	str r5, [r4]
	bl MOD08_02212498
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	add r2, r0, #0
	add r0, r4, #4
	add r1, r6, #0
	bl MOD08_02218654
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	cmp r0, #8
	bgt _0221982E
	cmp r0, #2
	blt _022198A0
	beq _02219834
	cmp r0, #4
	beq _02219850
	cmp r0, #8
	beq _02219874
	b _022198A0
_0221982E:
	cmp r0, #0x10
	beq _02219886
	b _022198A0
_02219834:
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	str r0, [r4, #0x28]
	mov r0, #0
	ldr r1, [r4, #0x10]
	mvn r0, r0
	mul r0, r1
	str r0, [r4, #0x10]
	b _022198A4
_02219850:
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022274C0
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	str r0, [r4, #0x28]
	mov r0, #0
	ldr r1, [r4, #0x10]
	mvn r0, r0
	mul r0, r1
	str r0, [r4, #0x10]
	b _022198A4
_02219874:
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	str r0, [r4, #0x28]
	b _022198A4
_02219886:
	ldr r0, [r4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022274C0
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	str r0, [r4, #0x28]
	b _022198A4
_022198A0:
	bl ErrorHandling
_022198A4:
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #0x2c]
	ldr r0, [r4, #0x28]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #0x2e]
	mov r0, #0x2e
	ldrsh r0, [r4, r0]
	ldr r1, _022198CC ; =MOD08_02219794
	add r2, r4, #0
	add r0, #8
	strh r0, [r4, #0x2e]
	ldr r0, [r4]
	bl MOD08_02212400
	pop {r4, r5, r6, pc}
	.align 2, 0
_022198CC: .word MOD08_02219794

	thumb_func_start MOD08_022198D0
MOD08_022198D0: ; 0x022198D0
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	ldr r0, [r5, #0x14]
	add r4, r1, #0
	mov r1, #1
	add r6, r2, #0
	bl FUN_0200C644
	ldr r0, [r5, #0x14]
	add r1, r4, #0
	add r2, r6, #0
	bl FUN_0200C714
	mov r0, #0
	str r0, [r5, #0x40]
	mov r0, #4
	mov r1, #0xa
	add r5, #0x18
	str r0, [sp]
	add r0, r5, #0
	add r2, r1, #0
	mov r3, #0xe
	bl MOD08_02218120
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_02219908
MOD08_02219908: ; 0x02219908
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r1, [r4, #0x14]
	add r0, #0x18
	bl MOD08_02218360
	cmp r0, #0
	bne _02219944
	ldr r0, [r4, #0x40]
	cmp r0, #0
	beq _0221992E
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl FUN_0200C644
	add sp, #4
	mov r0, #1
	pop {r3, r4, pc}
_0221992E:
	mov r0, #1
	str r0, [r4, #0x40]
	mov r0, #2
	add r4, #0x18
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0xe
	mov r2, #0xa
	mov r3, #0xc
	bl MOD08_02218120
_02219944:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD08_0221994C
MOD08_0221994C: ; 0x0221994C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x48]
	mov r5, #0
	cmp r1, #4
	bhi _022199E4
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02219964: ; jump table
	.short _0221996E - _02219964 - 2 ; case 0
	.short _02219994 - _02219964 - 2 ; case 1
	.short _022199A4 - _02219964 - 2 ; case 2
	.short _022199D2 - _02219964 - 2 ; case 3
	.short _022199E2 - _02219964 - 2 ; case 4
_0221996E:
	mov r1, #0x4c
	ldrsh r3, [r4, r1]
	ldr r2, [r4, #0x3c]
	mov r1, #0x18
	mul r1, r2
	mov r2, #0x4e
	ldrsh r2, [r4, r2]
	add r1, r3, r1
	lsl r1, r1, #0x10
	sub r2, #0x10
	lsl r2, r2, #0x10
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl MOD08_022198D0
	ldr r0, [r4, #0x48]
	add r0, r0, #1
	str r0, [r4, #0x48]
	b _022199E4
_02219994:
	bl MOD08_02219908
	cmp r0, #0
	beq _022199E4
	ldr r0, [r4, #0x48]
	add r0, r0, #1
	str r0, [r4, #0x48]
	b _022199E4
_022199A4:
	ldr r1, [r4, #0x44]
	sub r1, r1, #1
	str r1, [r4, #0x44]
	bpl _022199E4
	ldr r1, [r4, #0x48]
	add r1, r1, #1
	str r1, [r4, #0x48]
	mov r1, #0x4c
	ldrsh r3, [r4, r1]
	ldr r2, [r4, #0x3c]
	mov r1, #0x18
	mul r1, r2
	mov r2, #0x4e
	ldrsh r2, [r4, r2]
	sub r1, r3, r1
	lsl r1, r1, #0x10
	sub r2, #0x18
	lsl r2, r2, #0x10
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl MOD08_022198D0
	b _022199E4
_022199D2:
	bl MOD08_02219908
	cmp r0, #0
	beq _022199E4
	ldr r0, [r4, #0x48]
	add r0, r0, #1
	str r0, [r4, #0x48]
	b _022199E4
_022199E2:
	mov r5, #1
_022199E4:
	add r0, r5, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_022199E8
MOD08_022199E8: ; 0x022199E8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _022199FA
	cmp r0, #1
	beq _02219A0C
	b _02219A22
_022199FA:
	add r0, r4, #0
	bl MOD08_0221994C
	cmp r0, #0
	beq _02219A22
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02219A22
_02219A0C:
	ldr r0, [r4, #0x14]
	bl FUN_0200C3DC
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
_02219A22:
	ldr r0, [r4, #8]
	bl FUN_0200BC1C
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02219A2C
MOD08_02219A2C: ; 0x02219A2C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	mov r1, #0x50
	add r5, r0, #0
	str r2, [sp]
	add r6, r3, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4]
	ldr r0, [sp]
	str r7, [r4, #4]
	str r0, [r4, #8]
	str r6, [r4, #0x14]
	add r0, r6, #0
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl FUN_0200C6B0
	ldr r0, [r4, #0x14]
	mov r1, #2
	bl FUN_0200C840
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl FUN_0200C644
	mov r0, #4
	str r0, [r4, #0x44]
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02217C1C
	str r0, [r4, #0x3c]
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	mov r1, #0
	add r5, r0, #0
	bl FUN_0200782C
	add r1, r4, #0
	add r1, #0x4c
	strh r0, [r1]
	add r0, r5, #0
	mov r1, #1
	bl FUN_0200782C
	add r1, r4, #0
	add r1, #0x4e
	strh r0, [r1]
	ldr r0, [r4]
	ldr r1, _02219AB4 ; =MOD08_022199E8
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02219AB4: .word MOD08_022199E8

	thumb_func_start MOD08_02219AB8
MOD08_02219AB8: ; 0x02219AB8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	bl FUN_020038E4
	cmp r0, #0
	bne _02219AD6
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
_02219AD6:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02219AD8
MOD08_02219AD8: ; 0x02219AD8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	mov r1, #8
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4]
	add r0, r5, #0
	bl MOD08_02215504
	str r0, [r4, #4]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	cmp r0, #0
	beq _02219B06
	cmp r0, #1
	beq _02219B12
	cmp r0, #2
	beq _02219B18
	b _02219B1E
_02219B06:
	add r0, r5, #0
	bl MOD08_02214540
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	b _02219B22
_02219B12:
	mov r6, #1
	lsl r6, r6, #8
	b _02219B22
_02219B18:
	mov r6, #2
	lsl r6, r6, #8
	b _02219B22
_02219B1E:
	bl ErrorHandling
_02219B22:
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	str r0, [sp, #0xc]
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	str r0, [sp, #0x10]
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	ldr r1, [sp, #0xc]
	lsl r0, r0, #0x10
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp]
	ldr r1, [sp, #0x10]
	lsl r3, r7, #0x18
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #4]
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	mov r1, #1
	add r2, r6, #0
	asr r3, r3, #0x18
	bl FUN_02003210
	ldr r0, [r4]
	ldr r1, _02219B7C ; =MOD08_02219AB8
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_02219B7C: .word MOD08_02219AB8

	thumb_func_start MOD08_02219B80
MOD08_02219B80: ; 0x02219B80
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #5
	bhi _02219C28
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02219B98: ; jump table
	.short _02219BA4 - _02219B98 - 2 ; case 0
	.short _02219BBC - _02219B98 - 2 ; case 1
	.short _02219BCE - _02219B98 - 2 ; case 2
	.short _02219BE0 - _02219B98 - 2 ; case 3
	.short _02219BF8 - _02219B98 - 2 ; case 4
	.short _02219C1A - _02219B98 - 2 ; case 5
_02219BA4:
	ldr r0, [r4, #0x14]
	mov r1, #0
	str r0, [sp]
	ldr r0, [r4, #4]
	ldr r2, [r4, #0x18]
	ldr r3, [r4, #0x10]
	bl FUN_02007E68
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
_02219BBC:
	ldr r0, [r4, #4]
	bl FUN_02007F20
	cmp r0, #0
	bne _02219C28
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
_02219BCE:
	ldr r1, [r4, #0x1c]
	cmp r1, #0
	bne _02219BDA
	add r0, r0, #1
	str r0, [r4, #8]
	b _02219BE0
_02219BDA:
	sub r0, r1, #1
	str r0, [r4, #0x1c]
	pop {r3, r4, r5, pc}
_02219BE0:
	ldr r0, [r4, #0x14]
	mov r2, #0
	str r0, [sp]
	ldr r0, [r4, #4]
	ldr r1, [r4, #0x18]
	ldr r3, [r4, #0x10]
	bl FUN_02007E68
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
_02219BF8:
	ldr r0, [r4, #4]
	bl FUN_02007F20
	cmp r0, #0
	bne _02219C28
	ldr r0, [r4, #0xc]
	sub r0, r0, #1
	str r0, [r4, #0xc]
	cmp r0, #0
	bgt _02219C14
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
_02219C14:
	mov r0, #0
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
_02219C1A:
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
_02219C28:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02219C2C
MOD08_02219C2C: ; 0x02219C2C
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0x20
	add r4, r0, #0
	bl MOD08_02228064
	add r6, r0, #0
	str r4, [r6]
	mov r1, #0
	add r0, r4, #0
	str r1, [r6, #4]
	bl MOD08_02212498
	ldr r2, _02219DF4 ; =0x00000802
	cmp r0, r2
	bgt _02219C66
	bge _02219CEC
	cmp r0, #8
	bgt _02219C60
	cmp r0, #2
	blt _02219C5E
	beq _02219C7E
	cmp r0, #4
	beq _02219C90
	cmp r0, #8
	beq _02219CB6
_02219C5E:
	b _02219DA4
_02219C60:
	cmp r0, #0x10
	beq _02219CC8
	b _02219DA4
_02219C66:
	add r1, r2, #6
	cmp r0, r1
	bgt _02219C76
	bge _02219D48
	add r1, r2, #2
	cmp r0, r1
	beq _02219D1C
	b _02219DA4
_02219C76:
	add r2, #0xe
	cmp r0, r2
	beq _02219D78
	b _02219DA4
_02219C7E:
	add r0, r4, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r6]
	bl MOD08_022154D4
	str r0, [r6, #4]
	b _02219DA8
_02219C90:
	add r0, r4, #0
	bl MOD08_0221553C
	cmp r0, #1
	beq _02219C9C
	b _02219DA8
_02219C9C:
	ldr r0, [r6]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r6]
	bl MOD08_022274C0
	add r1, r0, #0
	ldr r0, [r6]
	bl MOD08_022154D4
	str r0, [r6, #4]
	b _02219DA8
_02219CB6:
	add r0, r4, #0
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r6]
	bl MOD08_022154D4
	str r0, [r6, #4]
	b _02219DA8
_02219CC8:
	add r0, r4, #0
	bl MOD08_0221553C
	cmp r0, #1
	bne _02219DA8
	ldr r0, [r6]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r6]
	bl MOD08_022274C0
	add r1, r0, #0
	ldr r0, [r6]
	bl MOD08_022154D4
	str r0, [r6, #4]
	b _02219DA8
_02219CEC:
	mov r7, #0xff
	mov r5, #0
_02219CF0:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02215490
	cmp r0, #0
	beq _02219D00
	cmp r0, #2
	bne _02219D04
_02219D00:
	add r7, r5, #0
	b _02219D0A
_02219D04:
	add r5, r5, #1
	cmp r5, #4
	blt _02219CF0
_02219D0A:
	cmp r7, #0xff
	bne _02219D10
	mov r7, #0
_02219D10:
	ldr r0, [r6]
	add r1, r7, #0
	bl MOD08_022154D4
	str r0, [r6, #4]
	b _02219DA8
_02219D1C:
	mov r7, #0xff
	mov r5, #0
_02219D20:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02215490
	cmp r0, #4
	bne _02219D30
	add r7, r5, #0
	b _02219D36
_02219D30:
	add r5, r5, #1
	cmp r5, #4
	blt _02219D20
_02219D36:
	cmp r7, #0xff
	bne _02219D3C
	mov r7, #0
_02219D3C:
	ldr r0, [r6]
	add r1, r7, #0
	bl MOD08_022154D4
	str r0, [r6, #4]
	b _02219DA8
_02219D48:
	mov r7, #0xff
	mov r5, #0
_02219D4C:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02215490
	cmp r0, #1
	beq _02219D5C
	cmp r0, #3
	bne _02219D60
_02219D5C:
	add r7, r5, #0
	b _02219D66
_02219D60:
	add r5, r5, #1
	cmp r5, #4
	blt _02219D4C
_02219D66:
	cmp r7, #0xff
	bne _02219D6C
	mov r7, #0
_02219D6C:
	ldr r0, [r6]
	add r1, r7, #0
	bl MOD08_022154D4
	str r0, [r6, #4]
	b _02219DA8
_02219D78:
	mov r7, #0xff
	mov r5, #0
_02219D7C:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02215490
	cmp r0, #5
	bne _02219D8C
	add r7, r5, #0
	b _02219D92
_02219D8C:
	add r5, r5, #1
	cmp r5, #4
	blt _02219D7C
_02219D92:
	cmp r7, #0xff
	bne _02219D98
	mov r7, #0
_02219D98:
	ldr r0, [r6]
	add r1, r7, #0
	bl MOD08_022154D4
	str r0, [r6, #4]
	b _02219DA8
_02219DA4:
	bl ErrorHandling
_02219DA8:
	ldr r0, [r6, #4]
	cmp r0, #0
	bne _02219DB6
	add r0, r6, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
_02219DB6:
	add r0, r4, #0
	mov r1, #1
	bl MOD08_02212498
	str r0, [r6, #0x10]
	add r0, r4, #0
	mov r1, #2
	bl MOD08_02212498
	str r0, [r6, #0xc]
	add r0, r4, #0
	mov r1, #3
	bl MOD08_02212498
	str r0, [r6, #0x14]
	add r0, r4, #0
	mov r1, #4
	bl MOD08_02212498
	str r0, [r6, #0x18]
	add r0, r4, #0
	mov r1, #5
	bl MOD08_02212498
	str r0, [r6, #0x1c]
	ldr r0, [r6]
	ldr r1, _02219DF8 ; =MOD08_02219B80
	add r2, r6, #0
	bl MOD08_02212400
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02219DF4: .word 0x00000802
_02219DF8: .word MOD08_02219B80

	thumb_func_start MOD08_02219DFC
MOD08_02219DFC: ; 0x02219DFC
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #4
	bls _02219E0C
	b _02219F60
_02219E0C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02219E18: ; jump table
	.short _02219E22 - _02219E18 - 2 ; case 0
	.short _02219E70 - _02219E18 - 2 ; case 1
	.short _02219EC2 - _02219E18 - 2 ; case 2
	.short _02219EEC - _02219E18 - 2 ; case 3
	.short _02219F4E - _02219E18 - 2 ; case 4
_02219E22:
	ldr r0, [r4, #0x4c]
	asr r0, r0, #0x10
	str r0, [sp]
	ldr r1, [r4, #0x3c]
	ldr r2, [r4, #0x44]
	ldr r3, [r4, #0x40]
	add r0, r4, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	add r0, #0x14
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	asr r3, r3, #0x10
	bl MOD08_02218120
	add r0, r4, #0
	add r0, #0x14
	add r1, sp, #8
	add r2, sp, #4
	bl MOD08_0221825C
	ldr r0, [r4, #0x50]
	cmp r0, #1
	bne _02219E5E
	ldr r1, [sp, #8]
	mov r0, #0
	bl _fsub
	str r0, [sp, #8]
_02219E5E:
	ldr r0, [r4, #0x10]
	ldr r1, [sp, #8]
	ldr r2, [sp, #4]
	bl FUN_0200C884
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02219F60
_02219E70:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02218170
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x14
	add r1, sp, #8
	add r2, sp, #4
	bl MOD08_0221825C
	ldr r0, [r4, #0x50]
	cmp r0, #1
	bne _02219E96
	ldr r1, [sp, #8]
	mov r0, #0
	bl _fsub
	str r0, [sp, #8]
_02219E96:
	ldr r0, [r4, #0x10]
	ldr r1, [sp, #8]
	ldr r2, [sp, #4]
	bl FUN_0200C884
	cmp r5, #0
	beq _02219EBA
	mov r0, #0
	str r0, [sp]
	mov r1, #0xc
	mov r2, #0xe
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	ldr r3, [r4, #0x28]
	bl MOD08_02218314
	b _02219F60
_02219EBA:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02219F60
_02219EC2:
	ldr r0, [r4, #0x4c]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	ldr r1, [r4, #0x40]
	ldr r2, [r4, #0x44]
	ldr r3, [r4, #0x3c]
	add r0, r4, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	add r0, #0x14
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	asr r3, r3, #0x10
	bl MOD08_02218120
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02219F60
_02219EEC:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02218170
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x14
	add r1, sp, #8
	add r2, sp, #4
	bl MOD08_0221825C
	ldr r0, [r4, #0x50]
	cmp r0, #1
	bne _02219F12
	ldr r1, [sp, #8]
	mov r0, #0
	bl _fsub
	str r0, [sp, #8]
_02219F12:
	ldr r0, [r4, #0x10]
	ldr r1, [sp, #8]
	ldr r2, [sp, #4]
	bl FUN_0200C884
	cmp r5, #0
	beq _02219F36
	mov r0, #0
	str r0, [sp]
	mov r1, #0xc
	mov r2, #0xe
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	ldr r3, [r4, #0x28]
	bl MOD08_02218314
	b _02219F60
_02219F36:
	ldr r0, [r4, #0x48]
	sub r0, r0, #1
	str r0, [r4, #0x48]
	cmp r0, #0
	bgt _02219F48
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02219F60
_02219F48:
	mov r0, #0
	str r0, [r4, #8]
	b _02219F60
_02219F4E:
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
	add sp, #0xc
	pop {r4, r5, pc}
_02219F60:
	ldr r0, [r4, #4]
	bl FUN_0200BC1C
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02219F6C
MOD08_02219F6C: ; 0x02219F6C
	push {r4, r5, r6, lr}
	mov r1, #0x54
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4]
	add r0, r5, #0
	bl MOD08_02212504
	str r0, [r4, #4]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	cmp r0, #0
	bne _02219FAE
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	add r6, r0, #0
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_0221552C
	b _02219FCC
_02219FAE:
	ldr r0, [r4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	add r6, r0, #0
	ldr r0, [r4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_0221552C
_02219FCC:
	strh r0, [r4, #0xe]
	add r0, r6, #0
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #0xc]
	add r0, r6, #0
	mov r1, #0x29
	bl FUN_0200782C
	mov r1, #0xc
	ldrsh r1, [r4, r1]
	sub r0, r1, r0
	strh r0, [r4, #0xc]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	str r0, [r4, #0x38]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	str r0, [r4, #0x3c]
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	str r0, [r4, #0x40]
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	str r0, [r4, #0x44]
	add r0, r5, #0
	mov r1, #5
	bl MOD08_02212498
	str r0, [r4, #0x48]
	add r0, r5, #0
	mov r1, #6
	bl MOD08_02212498
	str r0, [r4, #0x4c]
	add r0, r5, #0
	mov r1, #7
	bl MOD08_02212498
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022124D8
	str r0, [r4, #0x10]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200C6B0
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r4, #0x10]
	mov r1, #2
	bl FUN_0200C840
	ldr r1, [r4, #0x38]
	mov r2, #0x10
	ldr r0, [r4]
	sub r2, r2, r1
	bl MOD08_02227994
	ldr r0, [r4]
	ldr r1, _0221A08C ; =MOD08_02219DFC
	add r2, r4, #0
	bl MOD08_02212400
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	cmp r0, #0
	beq _0221A07A
	mov r1, #1
	b _0221A07C
_0221A07A:
	mov r1, #0
_0221A07C:
	ldr r0, [r4]
	bl MOD08_02215680
	cmp r0, #1
	bne _0221A08A
	mov r0, #1
	str r0, [r4, #0x50]
_0221A08A:
	pop {r4, r5, r6, pc}
	.align 2, 0
_0221A08C: .word MOD08_02219DFC

	thumb_func_start MOD08_0221A090
MOD08_0221A090: ; 0x0221A090
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #5
	bls _0221A0A0
	b _0221A1DC
_0221A0A0:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0221A0AC: ; jump table
	.short _0221A0B8 - _0221A0AC - 2 ; case 0
	.short _0221A0FC - _0221A0AC - 2 ; case 1
	.short _0221A12C - _0221A0AC - 2 ; case 2
	.short _0221A140 - _0221A0AC - 2 ; case 3
	.short _0221A186 - _0221A0AC - 2 ; case 4
	.short _0221A1C8 - _0221A0AC - 2 ; case 5
_0221A0B8:
	ldr r0, [r4, #0x40]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	ldr r0, [r4, #0x44]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #4]
	ldr r0, [r4, #0x4c]
	asr r0, r0, #0x10
	str r0, [sp, #8]
	ldr r1, [r4, #0x34]
	ldr r2, [r4, #0x38]
	ldr r3, [r4, #0x3c]
	add r0, r4, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	add r0, #0x10
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	asr r3, r3, #0x10
	bl MOD08_022181A8
	add r0, r4, #0
	ldr r1, [r4, #0xc]
	add r0, #0x10
	bl MOD08_02218380
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, pc}
_0221A0FC:
	add r0, r4, #0
	ldr r1, [r4, #0xc]
	add r0, #0x10
	bl MOD08_022183A0
	cmp r0, #0
	beq _0221A122
	mov r0, #0
	str r0, [sp]
	mov r1, #8
	mov r2, #0xa
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	ldr r3, [r4, #0x24]
	bl MOD08_022182DC
	add sp, #0xc
	pop {r4, r5, pc}
_0221A122:
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, pc}
_0221A12C:
	ldr r1, [r4, #0x50]
	cmp r1, #0
	bne _0221A138
	add r0, r0, #1
	str r0, [r4, #4]
	b _0221A140
_0221A138:
	sub r0, r1, #1
	add sp, #0xc
	str r0, [r4, #0x50]
	pop {r4, r5, pc}
_0221A140:
	ldr r0, [r4, #0x3c]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	ldr r0, [r4, #0x44]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #4]
	ldr r0, [r4, #0x4c]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	ldr r1, [r4, #0x38]
	ldr r2, [r4, #0x34]
	ldr r3, [r4, #0x40]
	add r0, r4, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	add r0, #0x10
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	asr r3, r3, #0x10
	bl MOD08_022181A8
	add r0, r4, #0
	ldr r1, [r4, #0xc]
	add r0, #0x10
	bl MOD08_022183A0
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, pc}
_0221A186:
	add r0, r4, #0
	ldr r1, [r4, #0xc]
	add r0, #0x10
	bl MOD08_022183A0
	cmp r0, #0
	beq _0221A1AC
	mov r0, #0
	str r0, [sp]
	mov r1, #8
	mov r2, #0xa
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	ldr r3, [r4, #0x24]
	bl MOD08_022182DC
	add sp, #0xc
	pop {r4, r5, pc}
_0221A1AC:
	ldr r0, [r4, #0x48]
	sub r0, r0, #1
	str r0, [r4, #0x48]
	cmp r0, #0
	bgt _0221A1C0
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, pc}
_0221A1C0:
	mov r0, #0
	add sp, #0xc
	str r0, [r4, #4]
	pop {r4, r5, pc}
_0221A1C8:
	ldr r0, [r4, #0xc]
	bl MOD08_02218E34
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
_0221A1DC:
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start MOD08_0221A1E0
MOD08_0221A1E0: ; 0x0221A1E0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x54
	add r5, r0, #0
	mov r1, #0x54
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #0
	str r5, [r4]
	bl MOD08_02212498
	ldr r2, _0221A3E4 ; =0x00000802
	cmp r0, r2
	bgt _0221A224
	bge _0221A290
	mov r2, #0x42
	lsl r2, r2, #2
	cmp r0, r2
	bgt _0221A21C
	sub r1, r2, #6
	cmp r0, r1
	blt _0221A21A
	beq _0221A23C
	sub r1, r2, #4
	cmp r0, r1
	beq _0221A23C
	cmp r0, r2
	beq _0221A266
_0221A21A:
	b _0221A346
_0221A21C:
	add r2, #8
	cmp r0, r2
	beq _0221A266
	b _0221A346
_0221A224:
	add r1, r2, #6
	cmp r0, r1
	bgt _0221A234
	bge _0221A2EC
	add r1, r2, #2
	cmp r0, r1
	beq _0221A2C0
	b _0221A346
_0221A234:
	add r2, #0xe
	cmp r0, r2
	beq _0221A31C
	b _0221A346
_0221A23C:
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_0221552C
	strh r0, [r4, #0xa]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	add r1, r0, #0
	ldr r0, [r4]
	add r2, sp, #4
	add r3, sp, #0
	bl MOD08_02227BAC
	ldr r0, [sp, #0xc]
	str r0, [r4, #0xc]
	b _0221A346
_0221A266:
	ldr r0, [r4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_0221552C
	strh r0, [r4, #0xa]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	add r1, r0, #0
	ldr r0, [r4]
	add r2, sp, #4
	add r3, sp, #0
	bl MOD08_02227BAC
	ldr r0, [sp, #0xc]
	str r0, [r4, #0xc]
	b _0221A346
_0221A290:
	mov r7, #0xff
	mov r6, #0
_0221A294:
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02215490
	cmp r0, #0
	beq _0221A2A4
	cmp r0, #2
	bne _0221A2A8
_0221A2A4:
	add r7, r6, #0
	b _0221A2AE
_0221A2A8:
	add r6, r6, #1
	cmp r6, #4
	blt _0221A294
_0221A2AE:
	cmp r7, #0xff
	bne _0221A2B4
	mov r7, #0
_0221A2B4:
	ldr r0, [r4]
	add r1, r7, #0
	bl MOD08_022154D4
	str r0, [r4, #0xc]
	b _0221A346
_0221A2C0:
	mov r7, #0xff
	mov r6, #0
_0221A2C4:
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02215490
	cmp r0, #4
	bne _0221A2D4
	add r7, r6, #0
	b _0221A2DA
_0221A2D4:
	add r6, r6, #1
	cmp r6, #4
	blt _0221A2C4
_0221A2DA:
	cmp r7, #0xff
	bne _0221A2E0
	mov r7, #0
_0221A2E0:
	ldr r0, [r4]
	add r1, r7, #0
	bl MOD08_022154D4
	str r0, [r4, #0xc]
	b _0221A346
_0221A2EC:
	mov r7, #0xff
	mov r6, #0
_0221A2F0:
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02215490
	cmp r0, #1
	beq _0221A300
	cmp r0, #3
	bne _0221A304
_0221A300:
	add r7, r6, #0
	b _0221A30A
_0221A304:
	add r6, r6, #1
	cmp r6, #4
	blt _0221A2F0
_0221A30A:
	cmp r7, #0xff
	bne _0221A310
	mov r7, #0
_0221A310:
	ldr r0, [r4]
	add r1, r7, #0
	bl MOD08_022154D4
	str r0, [r4, #0xc]
	b _0221A346
_0221A31C:
	mov r7, #0xff
	mov r6, #0
_0221A320:
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02215490
	cmp r0, #5
	bne _0221A330
	add r7, r6, #0
	b _0221A336
_0221A330:
	add r6, r6, #1
	cmp r6, #4
	blt _0221A320
_0221A336:
	cmp r7, #0xff
	bne _0221A33C
	mov r7, #0
_0221A33C:
	ldr r0, [r4]
	add r1, r7, #0
	bl MOD08_022154D4
	str r0, [r4, #0xc]
_0221A346:
	ldr r0, [r4, #0xc]
	cmp r0, #0
	bne _0221A356
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x54
	pop {r4, r5, r6, r7, pc}
_0221A356:
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #8]
	ldr r0, [r4, #0xc]
	mov r1, #0x29
	bl FUN_0200782C
	strh r0, [r4, #0xa]
	mov r0, #0xa
	ldrsh r0, [r4, r0]
	mov r1, #1
	add r0, #0x10
	strh r0, [r4, #0xa]
	add r0, r5, #0
	bl MOD08_02212498
	str r0, [r4, #0x34]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	str r0, [r4, #0x38]
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	str r0, [r4, #0x3c]
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	str r0, [r4, #0x40]
	add r0, r5, #0
	mov r1, #5
	bl MOD08_02212498
	str r0, [r4, #0x44]
	add r0, r5, #0
	mov r1, #6
	bl MOD08_02212498
	str r0, [r4, #0x48]
	add r0, r5, #0
	mov r1, #7
	bl MOD08_02212498
	str r0, [r4, #0x4c]
	add r0, r5, #0
	mov r1, #6
	bl MOD08_02212498
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [r4, #0x48]
	add r0, r5, #0
	mov r1, #6
	bl MOD08_02212498
	asr r0, r0, #0x10
	str r0, [r4, #0x50]
	ldr r0, [r4]
	ldr r1, _0221A3E8 ; =MOD08_0221A090
	add r2, r4, #0
	bl MOD08_02212400
	add r1, r4, #0
	bl MOD08_0221A090
	add sp, #0x54
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0221A3E4: .word 0x00000802
_0221A3E8: .word MOD08_0221A090

	thumb_func_start MOD08_0221A3EC
MOD08_0221A3EC: ; 0x0221A3EC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #8
	bl MOD08_02218704
	cmp r0, #0
	beq _0221A40E
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
	pop {r3, r4, r5, pc}
_0221A40E:
	ldr r0, [r4, #4]
	bl FUN_0200BC1C
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_0221A418
MOD08_0221A418: ; 0x0221A418
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r1, #0x30
	add r7, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r7, [r4]
	add r0, r7, #0
	bl MOD08_02212504
	str r0, [r4, #4]
	add r0, r7, #0
	mov r1, #0
	bl MOD08_02212498
	add r6, r0, #0
	mov r5, #0
_0221A43C:
	mov r0, #1
	lsl r0, r5
	tst r0, r6
	beq _0221A452
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_022124D8
	mov r1, #1
	bl FUN_0200C90C
_0221A452:
	add r5, r5, #1
	cmp r5, #4
	blt _0221A43C
	add r0, r7, #0
	mov r1, #1
	bl MOD08_02212498
	add r5, r0, #0
	add r0, r7, #0
	mov r1, #3
	bl MOD08_02212498
	str r0, [sp, #8]
	ldr r0, [r4]
	ldr r2, [sp, #8]
	add r1, r5, #0
	bl MOD08_02227994
	add r0, r7, #0
	mov r1, #2
	bl MOD08_02212498
	add r6, r0, #0
	add r0, r7, #0
	mov r1, #4
	bl MOD08_02212498
	str r0, [sp, #0xc]
	add r0, r7, #0
	mov r1, #5
	bl MOD08_02212498
	ldr r1, [sp, #0xc]
	ldr r3, [sp, #8]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	str r1, [sp]
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r1, r5, #0x10
	lsl r2, r6, #0x10
	lsl r3, r3, #0x10
	add r0, #8
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	asr r3, r3, #0x10
	bl MOD08_022186D4
	ldr r0, [r4]
	ldr r1, _0221A4C0 ; =MOD08_0221A3EC
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0221A4C0: .word MOD08_0221A3EC

	thumb_func_start MOD08_0221A4C4
MOD08_0221A4C4: ; 0x0221A4C4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r6, r0, #0
	mov r1, #1
	bl MOD08_02212498
	add r5, r0, #0
	add r0, r6, #0
	mov r1, #0
	bl MOD08_02212498
	add r1, r0, #0
	add r0, r6, #0
	add r2, sp, #4
	add r3, sp, #0
	bl MOD08_02227BAC
	ldr r0, [sp]
	mov r4, #0
	cmp r0, #0
	ble _0221A512
	mov r7, #6
_0221A4F0:
	ldr r1, [sp, #0x14]
	add r0, r6, #0
	bl MOD08_02215554
	cmp r0, #1
	bne _0221A500
	cmp r5, #0
	beq _0221A50A
_0221A500:
	ldr r0, [sp, #0xc]
	add r1, r7, #0
	add r2, r5, #0
	bl FUN_02007558
_0221A50A:
	ldr r0, [sp]
	add r4, r4, #1
	cmp r4, r0
	blt _0221A4F0
_0221A512:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_0221A518
MOD08_0221A518: ; 0x0221A518
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r1, [r4, #4]
	ldr r0, [r4, #8]
	cmp r1, r0
	blt _0221A566
	ldr r0, [r4]
	cmp r0, #0
	ldr r0, [r4, #0x14]
	bne _0221A546
	mov r1, #6
	mov r2, #0
	bl FUN_02007558
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r4, #0x3c]
	add r1, r5, #0
	bl MOD08_02212438
	pop {r3, r4, r5, pc}
_0221A546:
	mov r1, #6
	bl FUN_0200782C
	add r3, r0, #0
	mov r2, #1
	ldr r0, [r4, #0x14]
	mov r1, #6
	eor r2, r3
	bl FUN_02007558
	ldr r0, [r4]
	sub r0, r0, #1
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_0221A566:
	add r0, r1, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_0221A56C
MOD08_0221A56C: ; 0x0221A56C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r1, #0x40
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #0
	str r5, [r4, #0x3c]
	bl MOD08_02212498
	lsl r0, r0, #1
	str r0, [r4]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	add r1, r4, #0
	str r0, [r4, #8]
	add r0, r5, #0
	add r1, #0x20
	bl MOD08_02227B70
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022154D4
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x3c]
	ldr r1, _0221A5B8 ; =MOD08_0221A518
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, pc}
	nop
_0221A5B8: .word MOD08_0221A518

	thumb_func_start MOD08_0221A5BC
MOD08_0221A5BC: ; 0x0221A5BC
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0x24
	ldrb r0, [r0]
	cmp r0, #0
	beq _0221A5D4
	cmp r0, #1
	beq _0221A608
	b _0221A632
_0221A5D4:
	mov r0, #0x16
	ldrsh r3, [r4, r0]
	mov r0, #0x14
	ldrsh r1, [r4, r0]
	mov r2, #0xc
	str r3, [sp]
	ldr r0, [r4, #8]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	ldrsh r2, [r4, r2]
	add r0, r4, #0
	add r0, #0x40
	add r2, r1, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD08_02217E80
	add r0, r4, #0
	add r0, #0x24
	ldrb r0, [r0]
	add r4, #0x24
	add sp, #8
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, pc}
_0221A608:
	add r0, r4, #0
	add r0, #0x40
	bl MOD08_02217ECC
	cmp r0, #0
	bne _0221A622
	add r0, r4, #0
	add r0, #0x24
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x24
	strb r1, [r0]
_0221A622:
	mov r2, #0x40
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x18]
	mov r1, #0
	bl FUN_02007558
	add sp, #8
	pop {r4, pc}
_0221A632:
	ldr r0, [r4, #0x64]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #8
	pop {r4, pc}

	thumb_func_start MOD08_0221A644
MOD08_0221A644: ; 0x0221A644
	push {r4, r5, r6, lr}
	mov r1, #0x68
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4, #0x64]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	str r0, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	strh r0, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	mov r6, #0xff
	add r1, r6, #0
	add r1, #9
	cmp r0, r1
	bgt _0221A690
	add r1, r6, #3
	cmp r0, r1
	blt _0221A6E6
	beq _0221A69A
	add r1, r6, #5
	cmp r0, r1
	beq _0221A6A4
	add r1, r6, #0
	add r1, #9
	cmp r0, r1
	beq _0221A6C0
	b _0221A6E6
_0221A690:
	add r1, r6, #0
	add r1, #0x11
	cmp r0, r1
	beq _0221A6CA
	b _0221A6E6
_0221A69A:
	add r0, r5, #0
	bl MOD08_02212458
	add r6, r0, #0
	b _0221A6EA
_0221A6A4:
	add r0, r5, #0
	bl MOD08_0221553C
	cmp r0, #1
	bne _0221A6EA
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022274C0
	add r6, r0, #0
	b _0221A6EA
_0221A6C0:
	add r0, r5, #0
	bl MOD08_02212460
	add r6, r0, #0
	b _0221A6EA
_0221A6CA:
	add r0, r5, #0
	bl MOD08_0221553C
	cmp r0, #1
	bne _0221A6EA
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022274C0
	add r6, r0, #0
	b _0221A6EA
_0221A6E6:
	bl ErrorHandling
_0221A6EA:
	cmp r6, #0xff
	bne _0221A6F6
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
_0221A6F6:
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x24
	bl MOD08_02227B70
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_022154D4
	add r1, r4, #0
	add r1, #0x14
	str r0, [r4, #0x18]
	bl MOD08_02227B2C
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02217C1C
	cmp r0, #0
	bgt _0221A728
	mov r0, #0xc
	ldrsh r1, [r4, r0]
	sub r0, #0xd
	mul r0, r1
	strh r0, [r4, #0xc]
_0221A728:
	ldr r0, [r4, #0x64]
	ldr r1, _0221A734 ; =MOD08_0221A5BC
	add r2, r4, #0
	bl MOD08_02212400
	pop {r4, r5, r6, pc}
	.align 2, 0
_0221A734: .word MOD08_0221A5BC

	thumb_func_start MOD08_0221A738
MOD08_0221A738: ; 0x0221A738
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #0
	beq _0221A750
	cmp r0, #1
	beq _0221A792
	b _0221A7BC
_0221A750:
	ldr r0, [r4, #0x14]
	cmp r0, #0
	bne _0221A760
	mov r0, #0xff
	add r4, #0x20
	add sp, #8
	strb r0, [r4]
	pop {r4, pc}
_0221A760:
	mov r0, #0x12
	ldrsh r3, [r4, r0]
	mov r0, #0x10
	ldrsh r1, [r4, r0]
	mov r2, #0x64
	str r3, [sp]
	ldr r0, [r4, #8]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	ldrsh r2, [r4, r2]
	add r0, r4, #0
	add r0, #0x3c
	add r2, r1, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD08_02217E80
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x20
	strb r1, [r0]
_0221A792:
	add r0, r4, #0
	add r0, #0x3c
	bl MOD08_02217ECC
	cmp r0, #0
	bne _0221A7AC
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x20
	strb r1, [r0]
_0221A7AC:
	mov r2, #0x3c
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl FUN_02007558
	add sp, #8
	pop {r4, pc}
_0221A7BC:
	ldr r0, [r4, #0x60]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #8
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_0221A7D0
MOD08_0221A7D0: ; 0x0221A7D0
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0x68
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4, #0x60]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	str r0, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	add r1, r4, #0
	add r1, #0x64
	strh r0, [r1]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	add r1, r4, #0
	add r7, r0, #0
	add r0, r5, #0
	add r1, #0x20
	bl MOD08_02227B70
	mov r6, #0xff
	add r0, r6, #0
	add r0, #9
	cmp r7, r0
	bgt _0221A82C
	add r0, r6, #3
	cmp r7, r0
	blt _0221A882
	beq _0221A836
	add r0, r6, #5
	cmp r7, r0
	beq _0221A840
	add r0, r6, #0
	add r0, #9
	cmp r7, r0
	beq _0221A85C
	b _0221A882
_0221A82C:
	add r0, r6, #0
	add r0, #0x11
	cmp r7, r0
	beq _0221A866
	b _0221A882
_0221A836:
	add r0, r5, #0
	bl MOD08_02212458
	add r6, r0, #0
	b _0221A886
_0221A840:
	add r0, r5, #0
	bl MOD08_0221553C
	cmp r0, #1
	bne _0221A886
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022274C0
	add r6, r0, #0
	b _0221A886
_0221A85C:
	add r0, r5, #0
	bl MOD08_02212460
	add r6, r0, #0
	b _0221A886
_0221A866:
	add r0, r5, #0
	bl MOD08_0221553C
	cmp r0, #1
	bne _0221A886
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022274C0
	add r6, r0, #0
	b _0221A886
_0221A882:
	bl ErrorHandling
_0221A886:
	cmp r6, #0xff
	bne _0221A892
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
_0221A892:
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_022154D4
	add r1, r4, #0
	add r1, #0x10
	str r0, [r4, #0x14]
	bl MOD08_02227B2C
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02217C1C
	cmp r0, #0
	bgt _0221A8C0
	mov r0, #0x64
	ldrsh r1, [r4, r0]
	sub r0, #0x65
	add r2, r1, #0
	mul r2, r0
	add r0, r4, #0
	add r0, #0x64
	strh r2, [r0]
_0221A8C0:
	add r0, r5, #0
	bl MOD08_02212004
	ldr r0, [r4, #0x60]
	ldr r1, _0221A8D8 ; =MOD08_0221A738
	add r2, r4, #0
	bl MOD08_02212400
	add r1, r4, #0
	bl MOD08_0221A738
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0221A8D8: .word MOD08_0221A738

	thumb_func_start MOD08_0221A8DC
MOD08_0221A8DC: ; 0x0221A8DC
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bls _0221A8EC
	b _0221AA6A
_0221A8EC:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221A8F8: ; jump table
	.short _0221A900 - _0221A8F8 - 2 ; case 0
	.short _0221A962 - _0221A8F8 - 2 ; case 1
	.short _0221A9AC - _0221A8F8 - 2 ; case 2
	.short _0221A9FA - _0221A8F8 - 2 ; case 3
_0221A900:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02218170
	cmp r0, #1
	bne _0221A958
	add r0, r4, #0
	add r0, #0x38
	bl MOD08_022183F0
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x16
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #0xd
	bl FUN_02007558
	mov r2, #0x38
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl FUN_020079E0
	mov r0, #2
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0x28]
	bl MOD08_0221828C
	mov r2, #2
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #1
	add r2, r2, r3
	bl FUN_02007558
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0221A958:
	ldrb r0, [r4]
	add sp, #4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0221A962:
	ldrb r0, [r4, #9]
	add r0, r0, #1
	strb r0, [r4, #9]
	ldrb r1, [r4, #9]
	ldrb r0, [r4, #0xa]
	cmp r1, r0
	bhi _0221A972
	b _0221AA78
_0221A972:
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl MOD08_02212498
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl MOD08_02212498
	add r6, r0, #0
	ldr r0, [r4, #0xc]
	mov r1, #3
	bl MOD08_02212498
	str r0, [sp]
	add r0, r4, #0
	lsl r1, r5, #0x10
	lsl r3, r6, #0x10
	add r0, #0x14
	asr r1, r1, #0x10
	mov r2, #0x64
	asr r3, r3, #0x10
	bl MOD08_02218120
	ldrb r0, [r4]
	add sp, #4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0221A9AC:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02218170
	cmp r0, #1
	bne _0221A9F0
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x16
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #0xd
	bl FUN_02007558
	mov r0, #2
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0x28]
	bl MOD08_0221828C
	mov r2, #2
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #1
	add r2, r2, r3
	bl FUN_02007558
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0221A9F0:
	ldrb r0, [r4]
	add sp, #4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0221A9FA:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02218170
	cmp r0, #1
	ldr r0, [r4, #0x10]
	bne _0221AA3E
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x16
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #0xd
	bl FUN_02007558
	mov r0, #2
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0x28]
	bl MOD08_0221828C
	mov r2, #2
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #1
	add r2, r2, r3
	bl FUN_02007558
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0221AA3E:
	mov r1, #0xc
	add r2, r1, #0
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r4, #0x10]
	add r2, #0xf3
	bl FUN_02007558
	mov r2, #2
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_02007558
	ldrb r0, [r4]
	add sp, #4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0221AA6A:
	ldr r0, [r4, #0xc]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_0221AA78:
	add sp, #4
	pop {r3, r4, r5, r6, pc}

	thumb_func_start MOD08_0221AA7C
MOD08_0221AA7C: ; 0x0221AA7C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	bl MOD08_02212014
	mov r1, #0x5c
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4, #8]
	strb r0, [r4]
	str r5, [r4, #0xc]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #0xc]
	bl MOD08_022154D4
	str r0, [r4, #0x10]
	mov r0, #0
	strb r0, [r4, #9]
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #2]
	ldr r0, [r4, #0xc]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #0xc]
	bl MOD08_0221552C
	str r0, [r4, #4]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0x64
	lsl r3, r6, #0x10
	add r0, #0x14
	add r2, r1, #0
	asr r3, r3, #0x10
	bl MOD08_02218120
	mov r0, #0xa
	str r0, [sp]
	add r0, r4, #0
	mov r2, #0
	add r0, #0x38
	mov r1, #2
	add r3, r2, #0
	bl MOD08_022183C0
	ldr r0, [r4, #0xc]
	ldr r1, _0221AB14 ; =MOD08_0221A8DC
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_0221AB14: .word MOD08_0221A8DC

	thumb_func_start MOD08_0221AB18
MOD08_0221AB18: ; 0x0221AB18
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bls _0221AB28
	b _0221ACA8
_0221AB28:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221AB34: ; jump table
	.short _0221AB3C - _0221AB34 - 2 ; case 0
	.short _0221AB9E - _0221AB34 - 2 ; case 1
	.short _0221ABEA - _0221AB34 - 2 ; case 2
	.short _0221AC38 - _0221AB34 - 2 ; case 3
_0221AB3C:
	add r0, r4, #0
	add r0, #0x20
	bl MOD08_02218224
	cmp r0, #1
	bne _0221AB94
	add r0, r4, #0
	add r0, #0x44
	bl MOD08_022183F0
	mov r2, #0x20
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x1c]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x22
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x1c]
	mov r1, #0xd
	bl FUN_02007558
	mov r2, #0x44
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x1c]
	mov r1, #0
	bl FUN_020079E0
	mov r0, #2
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0x34]
	bl MOD08_0221828C
	mov r2, #2
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x1c]
	mov r1, #1
	add r2, r2, r3
	bl FUN_02007558
	add sp, #0xc
	pop {r3, r4, pc}
_0221AB94:
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, pc}
_0221AB9E:
	ldrb r0, [r4, #9]
	add r0, r0, #1
	strb r0, [r4, #9]
	ldrb r1, [r4, #9]
	ldrb r0, [r4, #0xa]
	cmp r1, r0
	bhi _0221ABAE
	b _0221ACB6
_0221ABAE:
	ldr r3, [r4, #0x10]
	ldr r2, [r4, #0xc]
	lsl r0, r3, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	asr r1, r2, #0x10
	mov r0, #0x64
	str r0, [sp, #4]
	ldr r0, [r4, #0x14]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	asr r3, r3, #0x10
	str r0, [sp, #8]
	add r0, r4, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	add r0, #0x20
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	asr r3, r3, #0x10
	bl MOD08_022181A8
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, pc}
_0221ABEA:
	add r0, r4, #0
	add r0, #0x20
	bl MOD08_02218224
	cmp r0, #1
	bne _0221AC2E
	mov r2, #0x20
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x1c]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x22
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x1c]
	mov r1, #0xd
	bl FUN_02007558
	mov r0, #2
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0x34]
	bl MOD08_0221828C
	mov r2, #2
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x1c]
	mov r1, #1
	add r2, r2, r3
	bl FUN_02007558
	add sp, #0xc
	pop {r3, r4, pc}
_0221AC2E:
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, pc}
_0221AC38:
	add r0, r4, #0
	add r0, #0x20
	bl MOD08_02218224
	cmp r0, #1
	ldr r0, [r4, #0x1c]
	bne _0221AC7C
	mov r2, #0x20
	ldrsh r2, [r4, r2]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x22
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x1c]
	mov r1, #0xd
	bl FUN_02007558
	mov r0, #2
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0x34]
	bl MOD08_0221828C
	mov r2, #2
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x1c]
	mov r1, #1
	add r2, r2, r3
	bl FUN_02007558
	add sp, #0xc
	pop {r3, r4, pc}
_0221AC7C:
	mov r1, #0xc
	add r2, r1, #0
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r4, #0x1c]
	add r2, #0xf3
	bl FUN_02007558
	mov r2, #2
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x1c]
	mov r1, #1
	bl FUN_02007558
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, pc}
_0221ACA8:
	ldr r0, [r4, #0x18]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_0221ACB6:
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD08_0221ACBC
MOD08_0221ACBC: ; 0x0221ACBC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	bl MOD08_02212014
	mov r1, #0x68
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4, #8]
	strb r0, [r4]
	str r5, [r4, #0x18]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #0x18]
	bl MOD08_022154D4
	str r0, [r4, #0x1c]
	mov r0, #0
	strb r0, [r4, #9]
	add r0, r5, #0
	mov r1, #6
	bl MOD08_02212498
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x18]
	mov r1, #3
	bl MOD08_02212498
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x18]
	mov r1, #4
	bl MOD08_02212498
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x18]
	mov r1, #5
	bl MOD08_02212498
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x18]
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	mov r2, #0
	add r3, r4, #2
	bl MOD08_02217B50
	ldr r0, [r4, #0x18]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #0x18]
	bl MOD08_0221552C
	str r0, [r4, #4]
	mov r1, #2
	ldrsh r1, [r4, r1]
	add r0, r1, r0
	strh r0, [r4, #2]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	asr r0, r0, #0x10
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #0x10]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x10
	asr r7, r0, #0x10
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	asr r0, r0, #0x10
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #0xc]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	str r6, [sp]
	mov r1, #0x64
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r4, #0
	ldr r1, [sp, #0x10]
	ldr r3, [sp, #0xc]
	add r0, #0x20
	add r2, r7, #0
	bl MOD08_022181A8
	mov r0, #0xa
	str r0, [sp]
	add r0, r4, #0
	mov r2, #0
	add r0, #0x44
	mov r1, #2
	add r3, r2, #0
	bl MOD08_022183C0
	ldr r0, [r4, #0x18]
	ldr r1, _0221ADBC ; =MOD08_0221AB18
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0221ADBC: .word MOD08_0221AB18

	thumb_func_start MOD08_0221ADC0
MOD08_0221ADC0: ; 0x0221ADC0
	push {r3, r4, r5, lr}
	mov r2, #1
	lsl r2, r2, #0x1a
	add r5, r0, #0
	add r4, r1, #0
	ldr r1, [r2]
	ldr r0, _0221ADEC ; =0xFFFF1FFF
	and r0, r1
	str r0, [r2]
	ldr r0, [r4, #8]
	mov r1, #2
	bl MOD08_02214850
	ldr r0, [r4, #8]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
	nop
_0221ADEC: .word 0xFFFF1FFF

	thumb_func_start MOD08_0221ADF0
MOD08_0221ADF0: ; 0x0221ADF0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r1, #0x28
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	add r0, r5, #0
	add r1, r4, #4
	bl MOD08_02227B70
	ldr r0, [r4, #8]
	mov r1, #2
	bl MOD08_0221477C
	ldr r0, [r4, #8]
	mov r1, #0
	bl MOD08_022124D8
	str r0, [r4, #0x24]
	mov r1, #2
	bl FUN_0200C90C
	ldr r0, [r4, #0x24]
	mov r1, #2
	bl FUN_0200C840
	ldr r1, _0221AE70 ; =0x3F99999A
	ldr r0, [r4, #0x24]
	add r2, r1, #0
	bl FUN_0200C884
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r2, [r0]
	ldr r1, _0221AE74 ; =0xFFFF1FFF
	and r2, r1
	lsr r1, r0, #0xb
	orr r1, r2
	str r1, [r0]
	add r0, #0x4a
	ldrh r2, [r0]
	mov r1, #0x3f
	bic r2, r1
	mov r1, #0x1b
	orr r1, r2
	strh r1, [r0]
	ldrh r2, [r0]
	ldr r1, _0221AE78 ; =0xFFFFC0FF
	and r2, r1
	mov r1, #7
	lsl r1, r1, #8
	orr r1, r2
	strh r1, [r0]
	ldr r0, [r4, #8]
	ldr r1, _0221AE7C ; =MOD08_0221ADC0
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, pc}
	nop
_0221AE70: .word 0x3F99999A
_0221AE74: .word 0xFFFF1FFF
_0221AE78: .word 0xFFFFC0FF
_0221AE7C: .word MOD08_0221ADC0

	thumb_func_start MOD08_0221AE80
MOD08_0221AE80: ; 0x0221AE80
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #0
	beq _0221AE98
	cmp r0, #1
	beq _0221AED4
	b _0221AF0A
_0221AE98:
	mov r0, #0x12
	ldrsh r3, [r4, r0]
	mov r0, #0x10
	ldrsh r1, [r4, r0]
	mov r0, #0x66
	ldrsh r0, [r4, r0]
	mov r2, #0x64
	add r0, r3, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	ldr r0, [r4, #8]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	ldrsh r2, [r4, r2]
	add r0, r4, #0
	add r0, #0x3c
	add r2, r1, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD08_02217E80
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x20
	strb r1, [r0]
_0221AED4:
	add r0, r4, #0
	add r0, #0x3c
	bl MOD08_02217ECC
	cmp r0, #0
	bne _0221AEEE
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x20
	strb r1, [r0]
_0221AEEE:
	mov r2, #0x3c
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl FUN_02007558
	mov r2, #0x3e
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl FUN_02007558
	add sp, #8
	pop {r4, pc}
_0221AF0A:
	ldr r0, [r4, #0x60]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #8
	pop {r4, pc}

	thumb_func_start MOD08_0221AF1C
MOD08_0221AF1C: ; 0x0221AF1C
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0x68
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4, #0x60]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	str r0, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	add r1, r4, #0
	add r1, #0x64
	strh r0, [r1]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	add r1, r4, #0
	add r1, #0x66
	strh r0, [r1]
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	add r1, r4, #0
	add r7, r0, #0
	add r0, r5, #0
	add r1, #0x20
	bl MOD08_02227B70
	mov r6, #0xff
	add r0, r6, #0
	add r0, #9
	cmp r7, r0
	bgt _0221AF86
	add r0, r6, #3
	cmp r7, r0
	blt _0221AFDC
	beq _0221AF90
	add r0, r6, #5
	cmp r7, r0
	beq _0221AF9A
	add r0, r6, #0
	add r0, #9
	cmp r7, r0
	beq _0221AFB6
	b _0221AFDC
_0221AF86:
	add r0, r6, #0
	add r0, #0x11
	cmp r7, r0
	beq _0221AFC0
	b _0221AFDC
_0221AF90:
	add r0, r5, #0
	bl MOD08_02212458
	add r6, r0, #0
	b _0221AFE0
_0221AF9A:
	add r0, r5, #0
	bl MOD08_0221553C
	cmp r0, #1
	bne _0221AFE0
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022274C0
	add r6, r0, #0
	b _0221AFE0
_0221AFB6:
	add r0, r5, #0
	bl MOD08_02212460
	add r6, r0, #0
	b _0221AFE0
_0221AFC0:
	add r0, r5, #0
	bl MOD08_0221553C
	cmp r0, #1
	bne _0221AFE0
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022274C0
	add r6, r0, #0
	b _0221AFE0
_0221AFDC:
	bl ErrorHandling
_0221AFE0:
	cmp r6, #0xff
	bne _0221AFEC
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
_0221AFEC:
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_022154D4
	str r0, [r4, #0x14]
	cmp r0, #0
	bne _0221B002
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
_0221B002:
	add r1, r4, #0
	add r1, #0x10
	bl MOD08_02227B2C
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02217C1C
	cmp r0, #0
	bgt _0221B036
	mov r0, #0x64
	ldrsh r1, [r4, r0]
	sub r0, #0x65
	add r2, r1, #0
	mul r2, r0
	add r0, r4, #0
	add r0, #0x64
	strh r2, [r0]
	mov r0, #0x66
	ldrsh r1, [r4, r0]
	sub r0, #0x67
	add r2, r1, #0
	mul r2, r0
	add r0, r4, #0
	add r0, #0x66
	strh r2, [r0]
_0221B036:
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _0221B050
	mov r0, #0x66
	ldrsh r1, [r4, r0]
	sub r0, #0x67
	add r2, r1, #0
	mul r2, r0
	add r0, r4, #0
	add r0, #0x66
	strh r2, [r0]
_0221B050:
	ldr r0, [r4, #0x60]
	ldr r1, _0221B064 ; =MOD08_0221AE80
	add r2, r4, #0
	bl MOD08_02212400
	add r1, r4, #0
	bl MOD08_0221AE80
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221B064: .word MOD08_0221AE80

	thumb_func_start MOD08_0221B068
MOD08_0221B068: ; 0x0221B068
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #0x20
	mov r2, #0x22
	add r5, r0, #0
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r3, [r4, #0x24]
	add r0, #0x30
	bl MOD08_02217E58
	cmp r0, #0
	bne _0221B0AC
	mov r2, #0x20
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl FUN_02007558
	mov r2, #0x22
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x24]
	mov r1, #1
	sub r2, #8
	bl FUN_02007558
	ldr r0, [r4, #4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_0221B0AC:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_0221B0B0
MOD08_0221B0B0: ; 0x0221B0B0
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	mov r1, #0x54
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02227B70
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	add r2, r4, #0
	add r1, r0, #0
	add r0, r5, #0
	add r2, #0x1c
	add r3, sp, #0
	bl MOD08_02227BAC
	mov r0, #0x22
	ldrsh r0, [r4, r0]
	mov r1, #1
	add r0, #8
	strh r0, [r4, #0x22]
	add r0, r5, #0
	bl MOD08_02212498
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0x30
	add r1, r6, #0
	bl MOD08_02218654
	ldr r1, [r4, #0x3c]
	add r2, r4, #0
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	str r0, [r4, #0x3c]
	ldr r1, [r4, #0x44]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	str r0, [r4, #0x44]
	ldr r0, [r4, #4]
	ldr r1, _0221B124 ; =MOD08_0221B068
	bl MOD08_02212400
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0221B124: .word MOD08_0221B068

	thumb_func_start MOD08_0221B128
MOD08_0221B128: ; 0x0221B128
	push {r4, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	bne _0221B160
	add r0, r4, #0
	add r0, #0x30
	bl MOD08_02217ECC
	cmp r0, #0
	bne _0221B146
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221B146:
	mov r2, #0x30
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl FUN_02007558
	mov r2, #0x32
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl FUN_02007558
	pop {r4, pc}
_0221B160:
	ldr r0, [r4, #4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD08_0221B170
MOD08_0221B170: ; 0x0221B170
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r1, #0x5c
	add r6, r0, #0
	bl MOD08_02228064
	add r5, r0, #0
	add r0, r6, #0
	add r1, r5, #0
	bl MOD08_02227B70
	add r0, r6, #0
	mov r1, #0
	bl MOD08_02212498
	add r4, r0, #0
	add r0, r6, #0
	mov r1, #1
	bl MOD08_02212498
	add r7, r0, #0
	cmp r4, #8
	bgt _0221B1AE
	cmp r4, #2
	blt _0221B1EC
	beq _0221B1B4
	cmp r4, #4
	beq _0221B1BE
	cmp r4, #8
	beq _0221B1D0
	b _0221B1EC
_0221B1AE:
	cmp r4, #0x10
	beq _0221B1DA
	b _0221B1EC
_0221B1B4:
	add r0, r6, #0
	bl MOD08_02212458
	str r0, [sp, #8]
	b _0221B1F0
_0221B1BE:
	add r0, r6, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_022274C0
	str r0, [sp, #8]
	b _0221B1F0
_0221B1D0:
	add r0, r6, #0
	bl MOD08_02212460
	str r0, [sp, #8]
	b _0221B1F0
_0221B1DA:
	add r0, r6, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_022274C0
	str r0, [sp, #8]
	b _0221B1F0
_0221B1EC:
	bl ErrorHandling
_0221B1F0:
	add r2, r5, #0
	ldr r1, [sp, #8]
	add r0, r6, #0
	add r2, #0x54
	bl MOD08_022275C0
	add r2, r5, #0
	add r0, r6, #0
	add r1, r4, #0
	add r2, #0x1c
	add r3, sp, #0xc
	bl MOD08_02227BAC
	add r0, r5, #0
	mov r1, #0
	add r0, #0x58
	strh r1, [r0]
	add r0, r5, #0
	add r0, #0x5a
	strh r1, [r0]
	ldr r0, [r5, #4]
	ldr r1, [sp, #8]
	bl MOD08_02227470
	cmp r0, #3
	bne _0221B22A
	mov r1, #0x4f
	mvn r1, r1
	b _0221B22E
_0221B22A:
	mov r1, #0x15
	lsl r1, r1, #4
_0221B22E:
	add r0, r5, #0
	add r0, #0x58
	strh r1, [r0]
	mov r0, #0x22
	ldrsh r3, [r5, r0]
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	str r3, [sp]
	str r0, [sp, #4]
	mov r1, #0x20
	mov r2, #0x58
	add r0, r5, #0
	ldrsh r1, [r5, r1]
	ldrsh r2, [r5, r2]
	add r0, #0x30
	bl MOD08_02217E80
	ldr r0, [r5, #4]
	ldr r1, _0221B260 ; =MOD08_0221B128
	add r2, r5, #0
	bl MOD08_02212400
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221B260: .word MOD08_0221B128

	thumb_func_start MOD08_0221B264
MOD08_0221B264: ; 0x0221B264
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	mov r1, #0x5c
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02227B70
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	str r0, [sp, #0xc]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	add r7, r0, #0
	cmp r6, #8
	bgt _0221B2AC
	cmp r6, #2
	blt _0221B2EA
	beq _0221B2B2
	cmp r6, #4
	beq _0221B2BC
	cmp r6, #8
	beq _0221B2CE
	b _0221B2EA
_0221B2AC:
	cmp r6, #0x10
	beq _0221B2D8
	b _0221B2EA
_0221B2B2:
	add r0, r5, #0
	bl MOD08_02212458
	str r0, [sp, #8]
	b _0221B2EE
_0221B2BC:
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022274C0
	str r0, [sp, #8]
	b _0221B2EE
_0221B2CE:
	add r0, r5, #0
	bl MOD08_02212460
	str r0, [sp, #8]
	b _0221B2EE
_0221B2D8:
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022274C0
	str r0, [sp, #8]
	b _0221B2EE
_0221B2EA:
	bl ErrorHandling
_0221B2EE:
	add r2, r4, #0
	ldr r1, [sp, #8]
	add r0, r5, #0
	add r2, #0x54
	bl MOD08_022275C0
	add r2, r4, #0
	add r0, r5, #0
	add r1, r6, #0
	add r2, #0x1c
	add r3, sp, #0x10
	bl MOD08_02227BAC
	add r0, r4, #0
	mov r1, #0
	add r0, #0x58
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0x5a
	strh r1, [r0]
	ldr r0, [r4, #4]
	ldr r1, [sp, #8]
	bl MOD08_02227470
	cmp r0, #3
	bne _0221B328
	mov r1, #0x4f
	mvn r1, r1
	b _0221B32C
_0221B328:
	mov r1, #0x15
	lsl r1, r1, #4
_0221B32C:
	add r0, r4, #0
	add r0, #0x58
	strh r1, [r0]
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bne _0221B356
	mov r0, #0x22
	ldrsh r3, [r4, r0]
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	str r3, [sp]
	str r0, [sp, #4]
	mov r1, #0x20
	mov r2, #0x58
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	add r0, #0x30
	bl MOD08_02217E80
	b _0221B37A
_0221B356:
	ldr r1, [sp, #8]
	add r0, r5, #0
	mov r2, #0
	bl MOD08_02217B98
	add r2, r0, #0
	mov r0, #0x22
	ldrsh r3, [r4, r0]
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	str r3, [sp]
	str r0, [sp, #4]
	mov r1, #0x58
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	add r0, #0x30
	bl MOD08_02217E80
_0221B37A:
	ldr r0, [r4, #4]
	ldr r1, _0221B388 ; =MOD08_0221B128
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0221B388: .word MOD08_0221B128

	thumb_func_start MOD08_0221B38C
MOD08_0221B38C: ; 0x0221B38C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	mov r1, #0
	add r5, r0, #0
	bl MOD08_02212498
	add r4, r0, #0
	cmp r4, #8
	bgt _0221B3AE
	cmp r4, #2
	blt _0221B3EC
	beq _0221B3B4
	cmp r4, #4
	beq _0221B3BE
	cmp r4, #8
	beq _0221B3D0
	b _0221B3EC
_0221B3AE:
	cmp r4, #0x10
	beq _0221B3DA
	b _0221B3EC
_0221B3B4:
	add r0, r5, #0
	bl MOD08_02212458
	add r6, r0, #0
	b _0221B3F0
_0221B3BE:
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022274C0
	add r6, r0, #0
	b _0221B3F0
_0221B3D0:
	add r0, r5, #0
	bl MOD08_02212460
	add r6, r0, #0
	b _0221B3F0
_0221B3DA:
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022274C0
	add r6, r0, #0
	b _0221B3F0
_0221B3EC:
	bl ErrorHandling
_0221B3F0:
	add r0, r5, #0
	add r1, r6, #0
	add r2, sp, #0
	bl MOD08_022275C0
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #8
	add r3, sp, #4
	bl MOD08_02227BAC
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_0221552C
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	mov r1, #0
	add r2, sp, #0
	ldrsh r2, [r2, r1]
	ldr r0, [sp, #0x10]
	bl FUN_02007558
	add r3, sp, #0
	mov r2, #2
	ldrsh r2, [r3, r2]
	ldr r0, [sp, #0x10]
	mov r1, #1
	add r2, r2, r4
	bl FUN_02007558
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_0221B434
MOD08_0221B434: ; 0x0221B434
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x30]
	bl MOD08_02218AF8
	cmp r0, #0
	bne _0221B458
	ldr r0, [r4, #0x30]
	bl MOD08_02218B08
	ldr r0, [r4, #4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_0221B458:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_0221B45C
MOD08_0221B45C: ; 0x0221B45C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	mov r1, #0x34
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02227B70
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	str r0, [sp, #0x1c]
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	str r0, [sp, #0x20]
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	str r0, [sp, #0x24]
	add r0, r5, #0
	mov r1, #5
	bl MOD08_02212498
	add r2, r4, #0
	str r0, [sp, #0x28]
	add r0, r5, #0
	add r1, r7, #0
	add r2, #0x1c
	add r3, sp, #0x2c
	bl MOD08_02227F88
	ldr r0, [r4, #0x28]
	ldr r0, [r0]
	bl FUN_02020354
	mov r1, #1
	bl FUN_0201E28C
	add r7, r0, #0
	add r0, r5, #0
	bl MOD08_02212014
	add r1, r0, #0
	mov r0, #0x10
	str r0, [sp]
	lsl r0, r6, #0x18
	asr r0, r0, #0x18
	str r0, [sp, #4]
	ldr r0, [sp, #0x1c]
	lsl r3, r7, #0x14
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [sp, #8]
	ldr r0, [sp, #0x20]
	mov r2, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x24]
	lsr r3, r3, #0x10
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x28]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x14]
	ldr r0, _0221B520 ; =0x0000044C
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x18]
	bl MOD08_02218B20
	str r0, [r4, #0x30]
	ldr r0, [r4, #4]
	ldr r1, _0221B524 ; =MOD08_0221B434
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221B520: .word 0x0000044C
_0221B524: .word MOD08_0221B434

	thumb_func_start MOD08_0221B528
MOD08_0221B528: ; 0x0221B528
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	bne _0221B59C
	ldr r0, [r4, #0x4c]
	add r1, r0, #1
	str r1, [r4, #0x4c]
	ldr r0, [r4, #0x44]
	cmp r1, r0
	blt _0221B5B0
	mov r1, #0
	str r1, [r4, #0x4c]
	ldr r0, [r4, #0x48]
	cmp r0, #0
	ldr r0, [r4, #0x54]
	bne _0221B560
	cmp r0, #0
	bge _0221B552
	str r1, [r4, #0x54]
_0221B552:
	ldr r0, [r4, #0x54]
	cmp r0, #0
	bne _0221B574
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221B574
_0221B560:
	cmp r0, #0x50
	ble _0221B568
	mov r0, #0x50
	str r0, [r4, #0x54]
_0221B568:
	ldr r0, [r4, #0x54]
	cmp r0, #0x50
	bne _0221B574
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221B574:
	ldr r0, [r4, #0x24]
	ldr r2, [r4, #0x54]
	mov r1, #0x12
	bl FUN_02007558
	ldr r0, [r4, #0x24]
	ldr r2, [r4, #0x50]
	mov r1, #1
	bl FUN_02007558
	mov r0, #0x42
	ldrsh r1, [r4, r0]
	ldr r2, [r4, #0x50]
	sub r1, r2, r1
	str r1, [r4, #0x50]
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #0x54]
	add r0, r1, r0
	str r0, [r4, #0x54]
	pop {r3, r4, r5, pc}
_0221B59C:
	ldr r0, [r4, #0x24]
	bl MOD08_02218E34
	ldr r0, [r4, #4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_0221B5B0:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_0221B5B4
MOD08_0221B5B4: ; 0x0221B5B4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r1, #0x58
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02227B70
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	add r6, r0, #0
	add r2, r4, #0
	add r0, r5, #0
	add r1, r6, #0
	add r2, #0x1c
	add r3, sp, #4
	bl MOD08_02227BAC
	cmp r6, #8
	bgt _0221B5F6
	cmp r6, #2
	blt _0221B634
	beq _0221B5FC
	cmp r6, #4
	beq _0221B606
	cmp r6, #8
	beq _0221B618
	b _0221B634
_0221B5F6:
	cmp r6, #0x10
	beq _0221B622
	b _0221B634
_0221B5FC:
	add r0, r5, #0
	bl MOD08_02212458
	add r7, r0, #0
	b _0221B638
_0221B606:
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022274C0
	add r7, r0, #0
	b _0221B638
_0221B618:
	add r0, r5, #0
	bl MOD08_02212460
	add r7, r0, #0
	b _0221B638
_0221B622:
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022274C0
	add r7, r0, #0
	b _0221B638
_0221B634:
	bl ErrorHandling
_0221B638:
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	str r0, [r4, #0x48]
	cmp r0, #0
	ldr r0, [r4, #0x24]
	bne _0221B68C
	mov r1, #1
	bl FUN_0200782C
	str r0, [r4, #0x50]
	ldr r0, [r4, #0x24]
	mov r1, #0x12
	bl FUN_0200782C
	mov r1, #0x50
	sub r0, r1, r0
	str r0, [r4, #0x54]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	add r1, r4, #0
	add r1, #0x40
	strh r0, [r1]
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	add r1, r4, #0
	add r1, #0x42
	strh r0, [r1]
	mov r0, #0x42
	ldrsh r1, [r4, r0]
	sub r0, #0x43
	add r2, r1, #0
	mul r2, r0
	add r0, r4, #0
	add r0, #0x42
	strh r2, [r0]
	b _0221B6BA
_0221B68C:
	mov r1, #1
	bl FUN_0200782C
	str r0, [r4, #0x50]
	ldr r0, [r4, #0x24]
	mov r1, #0x12
	bl FUN_0200782C
	str r0, [r4, #0x54]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	add r1, r4, #0
	add r1, #0x40
	strh r0, [r1]
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	add r1, r4, #0
	add r1, #0x42
	strh r0, [r1]
_0221B6BA:
	mov r0, #0
	str r0, [r4, #0x30]
	str r0, [r4, #0x34]
	mov r0, #0x50
	str r0, [r4, #0x38]
	add r0, r5, #0
	add r1, r7, #0
	bl MOD08_0221552C
	mov r1, #0x50
	sub r0, r1, r0
	str r0, [r4, #0x3c]
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	str r0, [r4, #0x44]
	mov r0, #0
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x3c]
	str r0, [sp]
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x30]
	ldr r2, [r4, #0x34]
	ldr r3, [r4, #0x38]
	bl FUN_02007E40
	ldr r0, [r4, #4]
	ldr r1, _0221B700 ; =MOD08_0221B528
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221B700: .word MOD08_0221B528

	thumb_func_start MOD08_0221B704
MOD08_0221B704: ; 0x0221B704
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
	cmp r1, #8
	bgt _0221B71E
	cmp r1, #2
	blt _0221B754
	beq _0221B724
	cmp r1, #4
	beq _0221B72C
	cmp r1, #8
	beq _0221B73C
	b _0221B754
_0221B71E:
	cmp r1, #0x10
	beq _0221B744
	b _0221B754
_0221B724:
	bl MOD08_02212458
	add r4, r0, #0
	b _0221B758
_0221B72C:
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022274C0
	add r4, r0, #0
	b _0221B758
_0221B73C:
	bl MOD08_02212460
	add r4, r0, #0
	b _0221B758
_0221B744:
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022274C0
	add r4, r0, #0
	b _0221B758
_0221B754:
	bl ErrorHandling
_0221B758:
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_0221B75C
MOD08_0221B75C: ; 0x0221B75C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _0221B76E
	cmp r0, #1
	beq _0221B7B4
	pop {r3, r4, r5, pc}
_0221B76E:
	ldr r0, [r4, #0x24]
	add r1, r0, #1
	str r1, [r4, #0x24]
	ldr r0, [r4, #0x20]
	cmp r1, r0
	blt _0221B7E6
	mov r0, #0
	str r0, [r4, #0x24]
	mov r0, #0x1c
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #0x44]
	add r2, r1, r0
	str r2, [r4, #0x44]
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl FUN_02007558
	mov r0, #0x1c
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #0x3c]
	sub r1, r1, r0
	str r1, [r4, #0x3c]
	ldr r0, [r4, #0x40]
	cmp r1, r0
	ble _0221B7A8
	str r0, [r4, #0x3c]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221B7A8:
	ldr r0, [r4, #0x30]
	ldr r2, [r4, #0x3c]
	mov r1, #0x12
	bl FUN_02007558
	pop {r3, r4, r5, pc}
_0221B7B4:
	ldr r0, [r4, #0x30]
	mov r1, #0xe
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4, #0x30]
	ldr r2, [r4, #0x48]
	mov r1, #1
	bl FUN_02007558
	ldr r0, [r4, #0x30]
	ldr r2, [r4, #0x40]
	mov r1, #0x12
	bl FUN_02007558
	ldr r0, [r4, #0x30]
	bl MOD08_02218E34
	ldr r0, [r4, #4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_0221B7E6:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_0221B7E8
MOD08_0221B7E8: ; 0x0221B7E8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _0221B7FA
	cmp r0, #1
	beq _0221B83E
	pop {r3, r4, r5, pc}
_0221B7FA:
	ldr r0, [r4, #0x24]
	add r1, r0, #1
	str r1, [r4, #0x24]
	ldr r0, [r4, #0x20]
	cmp r1, r0
	blt _0221B870
	mov r0, #0
	str r0, [r4, #0x24]
	mov r0, #0x1c
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #0x44]
	add r2, r1, r0
	str r2, [r4, #0x44]
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl FUN_02007558
	mov r0, #0x1c
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #0x3c]
	sub r0, r1, r0
	str r0, [r4, #0x3c]
	bpl _0221B832
	mov r0, #0
	str r0, [r4, #0x3c]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221B832:
	ldr r0, [r4, #0x30]
	ldr r2, [r4, #0x3c]
	mov r1, #0x12
	bl FUN_02007558
	pop {r3, r4, r5, pc}
_0221B83E:
	ldr r0, [r4, #0x30]
	mov r1, #0xe
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4, #0x30]
	ldr r2, [r4, #0x48]
	mov r1, #1
	bl FUN_02007558
	ldr r0, [r4, #0x30]
	ldr r2, [r4, #0x40]
	mov r1, #0x12
	bl FUN_02007558
	ldr r0, [r4, #0x30]
	bl MOD08_02218E34
	ldr r0, [r4, #4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_0221B870:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_0221B874
MOD08_0221B874: ; 0x0221B874
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _0221B886
	cmp r0, #1
	beq _0221B8C8
	pop {r3, r4, r5, pc}
_0221B886:
	ldr r0, [r4, #0x24]
	add r1, r0, #1
	str r1, [r4, #0x24]
	ldr r0, [r4, #0x20]
	cmp r1, r0
	blt _0221B8E6
	mov r0, #0
	str r0, [r4, #0x24]
	mov r1, #0x1c
	ldrsh r2, [r4, r1]
	ldr r3, [r4, #0x3c]
	sub r2, r3, r2
	str r2, [r4, #0x3c]
	ldrsh r1, [r4, r1]
	ldr r2, [r4, #0x40]
	add r1, r2, r1
	str r1, [r4, #0x40]
	ldr r1, [r4, #0x3c]
	cmp r1, #0
	bge _0221B8B6
	str r0, [r4, #0x3c]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221B8B6:
	ldr r0, [r4, #0x40]
	mov r1, #0
	str r0, [sp]
	ldr r0, [r4, #0x30]
	ldr r2, [r4, #0x3c]
	mov r3, #0x50
	bl FUN_02007E40
	pop {r3, r4, r5, pc}
_0221B8C8:
	ldr r0, [r4, #0x30]
	mov r1, #0xe
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4, #0x30]
	bl MOD08_02218E34
	ldr r0, [r4, #4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_0221B8E6:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_0221B8E8
MOD08_0221B8E8: ; 0x0221B8E8
	push {r4, r5, r6, lr}
	sub sp, #8
	mov r1, #0x50
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02227B70
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	strh r0, [r4, #0x1c]
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	str r0, [r4, #0x20]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	add r6, r0, #0
	add r2, r4, #0
	add r0, r5, #0
	add r1, r6, #0
	add r2, #0x28
	add r3, sp, #4
	bl MOD08_02227BAC
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_0221B704
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #5
	bl MOD08_02212498
	cmp r0, #0
	beq _0221B96A
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_0221552C
	mov r3, #0x50
	sub r0, r3, r0
	str r0, [r4, #0x3c]
	mov r1, #0
	str r1, [r4, #0x40]
	str r1, [sp]
	ldr r0, [r4, #0x30]
	ldr r2, [r4, #0x3c]
	bl FUN_02007E40
	ldr r0, [r4, #4]
	ldr r1, _0221B9DC ; =MOD08_0221B874
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #8
	pop {r4, r5, r6, pc}
_0221B96A:
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl FUN_0200782C
	str r0, [r4, #0x44]
	str r0, [r4, #0x48]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_0221552C
	mov r3, #0x50
	sub r0, r3, r0
	str r0, [r4, #0x3c]
	str r0, [r4, #0x40]
	mov r0, #0x1c
	ldrsh r0, [r4, r0]
	cmp r0, #0
	ble _0221B9AA
	ldr r0, [r4, #0x3c]
	mov r1, #0
	str r0, [sp]
	ldr r0, [r4, #0x30]
	add r2, r1, #0
	bl FUN_02007E40
	ldr r0, [r4, #4]
	ldr r1, _0221B9E0 ; =MOD08_0221B7E8
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #8
	pop {r4, r5, r6, pc}
_0221B9AA:
	mov r0, #0
	str r0, [r4, #0x3c]
	ldr r1, [r4, #0x44]
	ldr r0, [r4, #0x40]
	add r2, r1, r0
	str r2, [r4, #0x44]
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl FUN_02007558
	ldr r0, [r4, #0x3c]
	mov r1, #0
	str r0, [sp]
	ldr r0, [r4, #0x30]
	add r2, r1, #0
	mov r3, #0x50
	bl FUN_02007E40
	ldr r0, [r4, #4]
	ldr r1, _0221B9E4 ; =MOD08_0221B75C
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_0221B9DC: .word MOD08_0221B874
_0221B9E0: .word MOD08_0221B7E8
_0221B9E4: .word MOD08_0221B75C

	thumb_func_start MOD08_0221B9E8
MOD08_0221B9E8: ; 0x0221B9E8
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _0221B9FC
	cmp r0, #1
	beq _0221BA1C
	b _0221BAAC
_0221B9FC:
	ldr r0, [r4, #0x10]
	str r0, [sp]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	add r0, r4, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r3, [r4, #0xc]
	add r0, #0xd4
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl MOD08_022183C0
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221BA1C:
	add r0, r4, #0
	add r0, #0xd4
	bl MOD08_022183F0
	cmp r0, #0
	bne _0221BA70
	ldrb r1, [r4, #1]
	ldr r0, [r4, #0x18]
	cmp r1, r0
	ldrb r0, [r4]
	blt _0221BA36
	add r0, r0, #1
	b _0221BA38
_0221BA36:
	sub r0, r0, #1
_0221BA38:
	strb r0, [r4]
	ldr r0, [r4, #0x20]
	cmp r0, #0
	beq _0221BA50
	ldr r1, [r4, #0x1c]
	mov r2, #0
	lsl r1, r1, #0x18
	ldr r0, [r4, #0x28]
	lsr r1, r1, #0x18
	add r3, r2, #0
	bl FUN_020179E0
_0221BA50:
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _0221BA66
	ldr r1, [r4, #0x1c]
	ldr r0, [r4, #0x28]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
_0221BA66:
	ldrb r0, [r4, #1]
	add sp, #4
	add r0, r0, #1
	strb r0, [r4, #1]
	pop {r3, r4, pc}
_0221BA70:
	mov r3, #0xd4
	ldrsh r0, [r4, r3]
	cmp r0, #0
	beq _0221BA8C
	mov r0, #1
	str r0, [r4, #0x20]
	ldr r1, [r4, #0x1c]
	ldrsh r3, [r4, r3]
	lsl r1, r1, #0x18
	ldr r0, [r4, #0x28]
	lsr r1, r1, #0x18
	mov r2, #0
	bl FUN_020179E0
_0221BA8C:
	mov r3, #0xd6
	ldrsh r0, [r4, r3]
	cmp r0, #0
	beq _0221BABA
	mov r0, #1
	str r0, [r4, #0x24]
	ldr r1, [r4, #0x1c]
	ldrsh r3, [r4, r3]
	lsl r1, r1, #0x18
	ldr r0, [r4, #0x28]
	lsr r1, r1, #0x18
	mov r2, #3
	bl FUN_020179E0
	add sp, #4
	pop {r3, r4, pc}
_0221BAAC:
	ldr r0, [r4, #0x2c]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_0221BABA:
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD08_0221BAC0
MOD08_0221BAC0: ; 0x0221BAC0
	push {r3, r4, r5, lr}
	mov r1, #0xf8
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4]
	strb r0, [r4, #1]
	str r5, [r4, #0x2c]
	add r0, r5, #0
	bl MOD08_02212504
	str r0, [r4, #0x30]
	ldr r0, [r4, #0x2c]
	bl MOD08_02212490
	str r0, [r4, #0x28]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	str r0, [r4, #4]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	str r0, [r4, #8]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	str r0, [r4, #0xc]
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	str r0, [r4, #0x10]
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	str r0, [r4, #0x18]
	add r0, r5, #0
	mov r1, #5
	bl MOD08_02212498
	cmp r0, #0
	bne _0221BB26
	mov r0, #3
	b _0221BB28
_0221BB26:
	mov r0, #2
_0221BB28:
	str r0, [r4, #0x1c]
	ldr r0, [r4, #0x2c]
	ldr r1, _0221BB38 ; =MOD08_0221B9E8
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, pc}
	nop
_0221BB38: .word MOD08_0221B9E8

	thumb_func_start MOD08_0221BB3C
MOD08_0221BB3C: ; 0x0221BB3C
	push {r4, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldr r0, [r4, #0x2c]
	ldr r3, [r4, #0x24]
	cmp r3, r0
	beq _0221BB50
	ldr r1, [r4, #0x28]
	cmp r1, r0
	bne _0221BB60
_0221BB50:
	ldr r0, [r4, #4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
_0221BB60:
	mov r1, #0x20
	ldrsh r2, [r4, r1]
	cmp r2, #0
	bge _0221BB82
	add r2, r3, r2
	cmp r2, #0
	ble _0221BB7A
	str r2, [r4, #0x24]
	ldrsh r0, [r4, r1]
	ldr r2, [r4, #0x28]
	add r0, r2, r0
	str r0, [r4, #0x28]
	b _0221BB9A
_0221BB7A:
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x2c]
	str r0, [r4, #0x28]
	b _0221BB9A
_0221BB82:
	add r2, r3, r2
	cmp r2, #0xf
	bge _0221BB94
	str r2, [r4, #0x24]
	ldrsh r0, [r4, r1]
	ldr r2, [r4, #0x28]
	add r0, r2, r0
	str r0, [r4, #0x28]
	b _0221BB9A
_0221BB94:
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x2c]
	str r0, [r4, #0x28]
_0221BB9A:
	ldr r0, [r4, #0x1c]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x24]
	lsl r0, r0, #4
	orr r1, r0
	ldr r0, _0221BBB4 ; =0x0400004D
	strb r1, [r0]
	ldr r0, [r4, #0xc]
	bl FUN_0200BC1C
	pop {r4, pc}
	.align 2, 0
_0221BBB4: .word 0x0400004D

	thumb_func_start MOD08_0221BBB8
MOD08_0221BBB8: ; 0x0221BBB8
	push {r3, r4, r5, lr}
	mov r1, #0x30
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02227B70
	ldr r0, [r4, #4]
	mov r1, #1
	bl MOD08_02212498
	strh r0, [r4, #0x20]
	ldr r0, [r4, #4]
	mov r1, #2
	bl MOD08_02212498
	str r0, [r4, #0x24]
	ldr r0, [r4, #4]
	mov r1, #3
	bl MOD08_02212498
	str r0, [r4, #0x28]
	ldr r0, [r4, #4]
	mov r1, #0
	bl MOD08_02212498
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_022124D8
	mov r1, #1
	str r0, [r4, #0x1c]
	bl FUN_0200C644
	mov r0, #0x20
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bge _0221BC0E
	mov r0, #0
	b _0221BC10
_0221BC0E:
	mov r0, #0xf
_0221BC10:
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x1c]
	mov r1, #1
	bl FUN_0200C8F8
	ldr r0, [r4, #4]
	ldr r1, _0221BC2C ; =MOD08_0221BB3C
	add r2, r4, #0
	bl MOD08_02212400
	add r1, r4, #0
	bl MOD08_0221BB3C
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221BC2C: .word MOD08_0221BB3C

	thumb_func_start MOD08_0221BC30
MOD08_0221BC30: ; 0x0221BC30
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	mov r1, #0
	bl MOD08_02212498
	str r0, [r4]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	strh r0, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	strh r0, [r4, #0xe]
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	strh r0, [r4, #4]
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	strh r0, [r4, #6]
	add r0, r5, #0
	mov r1, #5
	bl MOD08_02212498
	str r0, [r4, #8]
	add r0, r5, #0
	mov r1, #6
	bl MOD08_02212498
	str r0, [r4, #0x10]
	add r0, r5, #0
	mov r1, #8
	bl MOD08_02212498
	str r0, [r4, #0x30]
	add r0, r5, #0
	mov r1, #7
	bl MOD08_02212498
	ldr r2, _0221BCFC ; =0xFFFF0000
	mov r1, #0
	and r2, r0
	lsl r0, r0, #0x10
	str r1, [r4, #0x1c]
	lsr r2, r2, #0x10
	str r2, [r4, #0x20]
	lsr r0, r0, #0x10
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x20]
	cmp r0, #0
	bne _0221BCA6
	str r1, [r4, #0x20]
_0221BCA6:
	ldr r0, [r4, #0x24]
	cmp r0, #0
	bne _0221BCB0
	mov r0, #0xff
	str r0, [r4, #0x24]
_0221BCB0:
	ldr r1, [r4]
	add r0, r5, #0
	bl MOD08_02212484
	str r0, [r4, #0x38]
	add r0, r5, #0
	bl MOD08_02212468
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x10]
	cmp r0, #0
	bne _0221BCDA
	add r0, r5, #0
	bl MOD08_02212458
	str r0, [r4, #0x14]
	add r0, r5, #0
	bl MOD08_02212460
	str r0, [r4, #0x18]
	b _0221BCEE
_0221BCDA:
	cmp r0, #1
	bne _0221BCEE
	add r0, r5, #0
	bl MOD08_02212460
	str r0, [r4, #0x14]
	add r0, r5, #0
	bl MOD08_02212458
	str r0, [r4, #0x18]
_0221BCEE:
	ldr r0, [r4, #0x38]
	cmp r0, #0
	bne _0221BCF8
	bl ErrorHandling
_0221BCF8:
	pop {r3, r4, r5, pc}
	nop
_0221BCFC: .word 0xFFFF0000

	thumb_func_start MOD08_0221BD00
MOD08_0221BD00: ; 0x0221BD00
	ldr r0, [r0, #8]
	mov r1, #0
	cmp r0, #0
	beq _0221BD12
_0221BD08:
	ldrh r2, [r0, #0x26]
	ldrh r3, [r0, #0x24]
	ldr r0, [r0]
	cmp r0, #0
	bne _0221BD08
_0221BD12:
	cmp r2, r3
	beq _0221BD18
	mov r1, #1
_0221BD18:
	add r0, r1, #0
	bx lr

	thumb_func_start MOD08_0221BD1C
MOD08_0221BD1C: ; 0x0221BD1C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	bl MOD08_0221BD00
	add r4, r0, #0
	mov r0, #4
	ldrsh r0, [r5, r0]
	ldr r1, [r5, #0x28]
	cmp r1, r0
	bge _0221BD3A
	add r0, r1, #1
	str r0, [r5, #0x28]
	pop {r4, r5, r6, pc}
_0221BD3A:
	add r0, r5, #0
	add r0, #0xa8
	bl MOD08_02217ECC
	cmp r0, #0
	bne _0221BD62
	cmp r4, #0
	bne _0221BD62
	ldr r0, [r5, #0x34]
	ldr r1, [r5, #0x38]
	bl FUN_020133DC
	ldr r0, [r5, #0x40]
	add r1, r6, #0
	bl MOD08_02212438
	add r0, r5, #0
	bl MOD08_02228094
	pop {r4, r5, r6, pc}
_0221BD62:
	ldr r1, [r5, #0x1c]
	ldr r0, [r5, #0x20]
	cmp r0, r1
	bgt _0221BD70
	ldr r0, [r5, #0x24]
	cmp r0, r1
	bge _0221BD76
_0221BD70:
	ldr r0, [r5, #0x24]
	cmp r0, #0xff
	bne _0221BDD4
_0221BD76:
	mov r0, #0xa8
	ldrsh r2, [r5, r0]
	ldr r1, [r5, #0x38]
	mov r3, #0xac
	add r0, r2, #0
	ldr r2, [r1, #0x20]
	mul r0, r3
	ldr r2, [r2]
	ldr r2, [r2, #4]
	add r0, r0, r2
	str r0, [r1, #0x28]
	mov r0, #0xaa
	ldrsh r4, [r5, r0]
	ldr r2, [r5, #0x38]
	add r1, r4, #0
	mul r1, r3
	ldr r3, [r2, #0x20]
	ldr r3, [r3]
	ldr r3, [r3, #8]
	add r1, r1, r3
	str r1, [r2, #0x2c]
	ldr r1, [r5, #0x30]
	cmp r1, #0
	beq _0221BDD4
	mov r1, #6
	ldrsh r1, [r5, r1]
	add r0, #0xbe
	bl _s32_div_f
	ldr r1, [r5, #0x2c]
	add r0, r1, r0
	str r0, [r5, #0x2c]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl Sin_Wrap
	mov r1, #0xaa
	ldrsh r2, [r5, r1]
	mov r1, #0xac
	mul r1, r2
	add r2, r1, r0
	ldr r1, [r5, #0x38]
	ldr r0, [r1, #0x20]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r2, r0
	str r0, [r1, #0x2c]
_0221BDD4:
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_0221BDD8
MOD08_0221BDD8: ; 0x0221BDD8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	mov r1, #0x41
	lsl r1, r1, #2
	add r6, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x3c
	bl MOD08_02227B70
	add r0, r6, #0
	add r1, r4, #0
	bl MOD08_0221BC30
	add r0, r6, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_02217C1C
	add r5, r0, #0
	ldr r1, [r4, #0x14]
	add r0, r6, #0
	add r2, sp, #0x18
	bl MOD08_0222771C
	ldr r1, [r4, #0x18]
	add r0, r6, #0
	add r2, sp, #0xc
	bl MOD08_0222771C
	ldr r0, [sp, #0x18]
	mov r1, #0xac
	bl _s32_div_f
	add r6, r0, #0
	ldr r0, [sp, #0xc]
	mov r1, #0xac
	bl _s32_div_f
	add r7, r0, #0
	ldr r0, [sp, #0x1c]
	mov r1, #0xac
	bl _s32_div_f
	str r0, [sp, #8]
	ldr r0, [sp, #0x10]
	mov r1, #0xac
	bl _s32_div_f
	mov r1, #0xe
	ldrsh r1, [r4, r1]
	add r2, r1, #0
	mul r2, r5
	add r0, r0, r2
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	ldrh r0, [r4, #6]
	lsl r1, r6, #0x10
	mov r2, #0xc
	str r0, [sp, #4]
	ldrsh r2, [r4, r2]
	add r0, r4, #0
	add r0, #0xa8
	add r3, r2, #0
	mul r3, r5
	add r2, r7, r3
	ldr r3, [sp, #8]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	asr r3, r3, #0x10
	bl MOD08_02217E80
	cmp r5, #0
	ldr r2, _0221BEFC ; =0x00005C71
	ble _0221BE90
	ldr r1, _0221BF00 ; =0x00000E38
	add r0, r4, #0
	add r0, #0xf0
	mul r1, r5
	mul r2, r5
	mov r3, #0xa
	bl MOD08_02218008
	b _0221BEA0
_0221BE90:
	ldr r1, _0221BF04 ; =0x00003FFF
	add r0, r4, #0
	add r0, #0xf0
	mul r1, r5
	mul r2, r5
	mov r3, #0xa
	bl MOD08_02218008
_0221BEA0:
	ldr r0, [r4, #0x20]
	mov r5, #0
	cmp r0, #0
	ble _0221BEBA
	add r6, r4, #0
	add r6, #0xa8
_0221BEAC:
	add r0, r6, #0
	bl MOD08_02217ECC
	ldr r0, [r4, #0x20]
	add r5, r5, #1
	cmp r5, r0
	blt _0221BEAC
_0221BEBA:
	ldr r0, [r4, #0x24]
	cmp r0, #0xff
	beq _0221BEC4
	add r0, r0, #1
	str r0, [r4, #0x1c]
_0221BEC4:
	mov r0, #0xa8
	ldrsh r3, [r4, r0]
	ldr r1, [r4, #0x38]
	mov r2, #0xac
	add r0, r3, #0
	ldr r3, [r1, #0x20]
	mul r0, r2
	ldr r3, [r3]
	ldr r3, [r3, #4]
	add r0, r0, r3
	str r0, [r1, #0x28]
	mov r1, #0xaa
	ldrsh r1, [r4, r1]
	ldr r0, [r4, #0x38]
	mul r2, r1
	ldr r1, [r0, #0x20]
	ldr r1, [r1]
	ldr r1, [r1, #8]
	add r1, r2, r1
	str r1, [r0, #0x2c]
	ldr r0, [r4, #0x40]
	ldr r1, _0221BF08 ; =MOD08_0221BD1C
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_0221BEFC: .word 0x00005C71
_0221BF00: .word 0x00000E38
_0221BF04: .word 0x00003FFF
_0221BF08: .word MOD08_0221BD1C

	thumb_func_start MOD08_0221BF0C
MOD08_0221BF0C: ; 0x0221BF0C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	mov r1, #0x41
	lsl r1, r1, #2
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x3c
	bl MOD08_02227B70
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	str r0, [r4]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	str r0, [r4, #0x10]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	strh r0, [r4, #6]
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	strh r0, [r4, #4]
	mov r0, #0
	str r0, [r4, #0x28]
	add r0, r5, #0
	mov r1, #5
	bl MOD08_02212498
	ldr r2, _0221C098 ; =0xFFFF0000
	mov r1, #0
	and r2, r0
	lsl r0, r0, #0x10
	str r1, [r4, #0x1c]
	lsr r2, r2, #0x10
	str r2, [r4, #0x20]
	lsr r0, r0, #0x10
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x20]
	cmp r0, #0
	bne _0221BF7E
	str r1, [r4, #0x20]
_0221BF7E:
	ldr r0, [r4, #0x24]
	cmp r0, #0
	bne _0221BF88
	mov r0, #0xff
	str r0, [r4, #0x24]
_0221BF88:
	ldr r1, [r4]
	add r0, r5, #0
	bl MOD08_02212484
	str r0, [r4, #0x38]
	add r0, r5, #0
	bl MOD08_02212468
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x10]
	cmp r0, #0
	bne _0221BFB0
	add r0, r5, #0
	bl MOD08_02212458
	str r0, [r4, #0x14]
	add r0, r5, #0
	bl MOD08_02212458
	b _0221BFBE
_0221BFB0:
	add r0, r5, #0
	bl MOD08_02212460
	str r0, [r4, #0x14]
	add r0, r5, #0
	bl MOD08_02212460
_0221BFBE:
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x38]
	cmp r0, #0
	bne _0221BFCA
	bl ErrorHandling
_0221BFCA:
	ldr r1, [r4, #0x14]
	add r0, r5, #0
	add r2, sp, #0x14
	bl MOD08_0222771C
	ldr r1, [r4, #0x18]
	add r0, r5, #0
	add r2, sp, #8
	bl MOD08_0222771C
	cmp r6, #0
	bne _0221BFEE
	add r0, sp, #0x14
	bl MOD08_0222795C
	ldr r0, [sp, #8]
	str r0, [sp, #0x14]
	b _0221BFF8
_0221BFEE:
	add r0, sp, #8
	bl MOD08_0222795C
	ldr r0, [sp, #0x14]
	str r0, [sp, #8]
_0221BFF8:
	ldr r0, [sp, #0x14]
	mov r1, #0xac
	bl _s32_div_f
	add r5, r0, #0
	ldr r0, [sp, #8]
	mov r1, #0xac
	bl _s32_div_f
	add r6, r0, #0
	ldr r0, [sp, #0x18]
	mov r1, #0xac
	bl _s32_div_f
	add r7, r0, #0
	ldr r0, [sp, #0xc]
	mov r1, #0xac
	bl _s32_div_f
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	ldrh r0, [r4, #6]
	lsl r1, r5, #0x10
	lsl r2, r6, #0x10
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r3, r7, #0x10
	add r0, #0xa8
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	asr r3, r3, #0x10
	bl MOD08_02217E80
	ldr r0, [r4, #0x20]
	mov r5, #0
	cmp r0, #0
	ble _0221C056
	add r6, r4, #0
	add r6, #0xa8
_0221C048:
	add r0, r6, #0
	bl MOD08_02217ECC
	ldr r0, [r4, #0x20]
	add r5, r5, #1
	cmp r5, r0
	blt _0221C048
_0221C056:
	ldr r0, [r4, #0x24]
	cmp r0, #0xff
	beq _0221C060
	add r0, r0, #1
	str r0, [r4, #0x1c]
_0221C060:
	mov r0, #0xa8
	ldrsh r3, [r4, r0]
	ldr r1, [r4, #0x38]
	mov r2, #0xac
	add r0, r3, #0
	ldr r3, [r1, #0x20]
	mul r0, r2
	ldr r3, [r3]
	ldr r3, [r3, #4]
	add r0, r0, r3
	str r0, [r1, #0x28]
	mov r1, #0xaa
	ldrsh r1, [r4, r1]
	ldr r0, [r4, #0x38]
	mul r2, r1
	ldr r1, [r0, #0x20]
	ldr r1, [r1]
	ldr r1, [r1, #8]
	add r1, r2, r1
	str r1, [r0, #0x2c]
	ldr r0, [r4, #0x40]
	ldr r1, _0221C09C ; =MOD08_0221BD1C
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221C098: .word 0xFFFF0000
_0221C09C: .word MOD08_0221BD1C

	thumb_func_start MOD08_0221C0A0
MOD08_0221C0A0: ; 0x0221C0A0
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	bl MOD08_0221BD00
	add r4, r0, #0
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xa8
	add r1, #0xcc
	bl MOD08_02217F9C
	cmp r0, #0
	bne _0221C0DA
	cmp r4, #0
	bne _0221C0DA
	ldr r0, [r5, #0x34]
	ldr r1, [r5, #0x38]
	bl FUN_020133DC
	ldr r0, [r5, #0x40]
	add r1, r6, #0
	bl MOD08_02212438
	add r0, r5, #0
	bl MOD08_02228094
	pop {r4, r5, r6, pc}
_0221C0DA:
	mov r1, #0xa8
	ldrsh r1, [r5, r1]
	ldr r0, [r5, #0x38]
	mov r2, #0xac
	add r3, r1, #0
	ldr r1, [r0, #0x20]
	mul r3, r2
	ldr r1, [r1]
	ldr r1, [r1, #4]
	add r1, r3, r1
	str r1, [r0, #0x28]
	mov r1, #0xaa
	ldrsh r1, [r5, r1]
	ldr r0, [r5, #0x38]
	mul r2, r1
	ldr r1, [r0, #0x20]
	ldr r1, [r1]
	ldr r1, [r1, #8]
	add r1, r2, r1
	str r1, [r0, #0x2c]
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_0221C104
MOD08_0221C104: ; 0x0221C104
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	mov r1, #0x41
	lsl r1, r1, #2
	add r6, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x3c
	bl MOD08_02227B70
	add r0, r6, #0
	add r1, r4, #0
	bl MOD08_0221BC30
	add r0, r6, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_02217C1C
	add r5, r0, #0
	ldr r1, [r4, #0x14]
	add r0, r6, #0
	add r2, sp, #0x20
	bl MOD08_0222771C
	ldr r1, [r4, #0x18]
	add r0, r6, #0
	add r2, sp, #0x14
	bl MOD08_0222771C
	ldr r0, [sp, #0x20]
	mov r1, #0xac
	bl _s32_div_f
	add r6, r0, #0
	ldr r0, [sp, #0x14]
	mov r1, #0xac
	bl _s32_div_f
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x24]
	mov r1, #0xac
	bl _s32_div_f
	add r7, r0, #0
	ldr r0, [sp, #0x18]
	mov r1, #0xac
	bl _s32_div_f
	lsl r1, r7, #0x10
	asr r1, r1, #0x10
	str r1, [sp]
	mov r1, #0xe
	ldrsh r1, [r4, r1]
	mov r3, #0xc
	add r2, r1, #0
	mul r2, r5
	add r0, r0, r2
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #4]
	ldrh r0, [r4, #6]
	lsl r2, r6, #0x10
	add r1, r4, #0
	str r0, [sp, #8]
	ldr r0, [r4, #8]
	add r1, #0xcc
	lsl r0, r0, #0xc
	neg r0, r0
	str r0, [sp, #0xc]
	ldrsh r6, [r4, r3]
	add r0, r4, #0
	add r0, #0xa8
	add r3, r6, #0
	ldr r6, [sp, #0x10]
	mul r3, r5
	add r3, r6, r3
	lsl r3, r3, #0x10
	asr r2, r2, #0x10
	asr r3, r3, #0x10
	bl MOD08_02217F50
	cmp r5, #0
	ldr r2, _0221C23C ; =0x00005C71
	ble _0221C1CA
	ldr r1, _0221C240 ; =0x00000E38
	add r0, r4, #0
	add r0, #0xf0
	mul r1, r5
	mul r2, r5
	mov r3, #0xa
	bl MOD08_02218008
	b _0221C1DA
_0221C1CA:
	ldr r1, _0221C244 ; =0x00003FFF
	add r0, r4, #0
	add r0, #0xf0
	mul r1, r5
	mul r2, r5
	mov r3, #0xa
	bl MOD08_02218008
_0221C1DA:
	ldr r0, [r4, #0x20]
	mov r5, #0
	cmp r0, #0
	ble _0221C1FA
	add r6, r4, #0
	add r7, r4, #0
	add r6, #0xa8
	add r7, #0xcc
_0221C1EA:
	add r0, r6, #0
	add r1, r7, #0
	bl MOD08_02217F9C
	ldr r0, [r4, #0x20]
	add r5, r5, #1
	cmp r5, r0
	blt _0221C1EA
_0221C1FA:
	ldr r0, [r4, #0x24]
	cmp r0, #0xff
	beq _0221C204
	add r0, r0, #1
	str r0, [r4, #0x1c]
_0221C204:
	mov r0, #0xa8
	ldrsh r3, [r4, r0]
	ldr r1, [r4, #0x38]
	mov r2, #0xac
	add r0, r3, #0
	ldr r3, [r1, #0x20]
	mul r0, r2
	ldr r3, [r3]
	ldr r3, [r3, #4]
	add r0, r0, r3
	str r0, [r1, #0x28]
	mov r1, #0xaa
	ldrsh r1, [r4, r1]
	ldr r0, [r4, #0x38]
	mul r2, r1
	ldr r1, [r0, #0x20]
	ldr r1, [r1]
	ldr r1, [r1, #8]
	add r1, r2, r1
	str r1, [r0, #0x2c]
	ldr r0, [r4, #0x40]
	ldr r1, _0221C248 ; =MOD08_0221C0A0
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_0221C23C: .word 0x00005C71
_0221C240: .word 0x00000E38
_0221C244: .word 0x00003FFF
_0221C248: .word MOD08_0221C0A0

	thumb_func_start MOD08_0221C24C
MOD08_0221C24C: ; 0x0221C24C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	bl MOD08_0221BD00
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0x58
	bl MOD08_02217D98
	cmp r0, #0
	bne _0221C282
	cmp r4, #0
	bne _0221C282
	ldr r0, [r5, #0x34]
	ldr r1, [r5, #0x38]
	bl FUN_020133DC
	ldr r0, [r5, #0x40]
	add r1, r6, #0
	bl MOD08_02212438
	add r0, r5, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
_0221C282:
	add r0, r5, #0
	add r0, #0x8c
	ldr r2, [r0]
	mov r0, #0x5a
	ldrsh r0, [r5, r0]
	mov r3, #0xac
	add r1, r0, #0
	mul r1, r3
	add r1, r2, r1
	add r2, r5, #0
	add r2, #0x88
	ldr r4, [r2]
	mov r2, #0x58
	ldrsh r2, [r5, r2]
	ldr r0, [r5, #0x38]
	mul r3, r2
	ldr r2, [r0, #0x20]
	add r3, r4, r3
	ldr r2, [r2]
	ldr r2, [r2, #4]
	add r2, r3, r2
	str r2, [r0, #0x28]
	ldr r2, [r5, #0x38]
	ldr r0, [r2, #0x20]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r1, r0
	str r0, [r2, #0x2c]
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_0221C2BC
MOD08_0221C2BC: ; 0x0221C2BC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r1, #0x94
	add r4, r0, #0
	bl MOD08_02228064
	add r5, r0, #0
	add r1, r5, #0
	add r0, r4, #0
	add r1, #0x3c
	bl MOD08_02227B70
	add r0, r4, #0
	mov r1, #0
	bl MOD08_02212498
	str r0, [r5]
	add r0, r4, #0
	mov r1, #1
	bl MOD08_02212498
	str r0, [r5, #4]
	add r0, r4, #0
	mov r1, #2
	bl MOD08_02212498
	str r0, [r5, #0xc]
	add r0, r4, #0
	mov r1, #3
	bl MOD08_02212498
	str r0, [r5, #8]
	add r0, r4, #0
	mov r1, #4
	bl MOD08_02212498
	str r0, [r5, #0x10]
	add r0, r4, #0
	mov r1, #5
	bl MOD08_02212498
	str r0, [r5, #0x14]
	add r0, r4, #0
	mov r1, #6
	bl MOD08_02212498
	str r0, [r5, #0x18]
	add r0, r4, #0
	mov r1, #7
	bl MOD08_02212498
	str r0, [r5, #0x1c]
	add r0, r4, #0
	mov r1, #8
	bl MOD08_02212498
	str r0, [r5, #0x20]
	cmp r0, #0
	bne _0221C33A
	add r0, r4, #0
	bl MOD08_02212458
	b _0221C340
_0221C33A:
	add r0, r4, #0
	bl MOD08_02212460
_0221C340:
	str r0, [r5, #0x24]
	add r2, r5, #0
	ldr r1, [r5, #0x24]
	add r0, r4, #0
	add r2, #0x88
	bl MOD08_0222771C
	ldr r1, [r5]
	add r0, r4, #0
	bl MOD08_02212484
	str r0, [r5, #0x38]
	add r0, r4, #0
	mov r1, #9
	bl MOD08_02212498
	add r1, r0, #0
	add r0, r4, #0
	bl MOD08_02212478
	str r0, [r5, #0x34]
	ldr r1, [r5, #4]
	ldr r0, _0221C420 ; =0x0000FFFF
	mul r0, r1
	mov r1, #0x5a
	lsl r1, r1, #2
	bl _s32_div_f
	add r4, r0, #0
	ldr r1, [r5, #0xc]
	ldr r0, _0221C420 ; =0x0000FFFF
	mul r0, r1
	mov r1, #0x5a
	lsl r1, r1, #2
	bl _s32_div_f
	add r6, r0, #0
	ldr r1, [r5, #8]
	ldr r0, _0221C420 ; =0x0000FFFF
	mul r0, r1
	mov r1, #0x5a
	lsl r1, r1, #2
	bl _s32_div_f
	add r7, r0, #0
	ldr r1, [r5, #0x10]
	ldr r0, _0221C420 ; =0x0000FFFF
	mul r0, r1
	mov r1, #0x5a
	lsl r1, r1, #2
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	ldr r0, [r5, #0x14]
	lsl r1, r4, #0x10
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r0, [r5, #0x18]
	lsl r2, r6, #0x10
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r0, [r5, #0x1c]
	lsl r3, r7, #0x10
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r0, #0x58
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl MOD08_02217D14
	add r0, r5, #0
	add r0, #0x58
	bl MOD08_02217D98
	add r0, r5, #0
	add r0, #0x8c
	ldr r2, [r0]
	mov r0, #0x5a
	ldrsh r0, [r5, r0]
	mov r3, #0x58
	mov r4, #0xac
	add r1, r0, #0
	add r0, r5, #0
	mul r1, r4
	ldrsh r3, [r5, r3]
	add r0, #0x88
	add r2, r2, r1
	ldr r1, [r5, #0x38]
	ldr r0, [r0]
	mul r4, r3
	add r3, r0, r4
	ldr r0, [r1, #0x20]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	add r0, r3, r0
	str r0, [r1, #0x28]
	ldr r1, [r5, #0x38]
	ldr r0, [r1, #0x20]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r2, r0
	str r0, [r1, #0x2c]
	ldr r0, [r5, #0x40]
	ldr r1, _0221C424 ; =MOD08_0221C24C
	add r2, r5, #0
	bl MOD08_02212400
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0221C420: .word 0x0000FFFF
_0221C424: .word MOD08_0221C24C

	thumb_func_start MOD08_0221C428
MOD08_0221C428: ; 0x0221C428
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x1c]
	bl FUN_0200C608
	cmp r0, #0
	ldr r0, [r4, #0x1c]
	bne _0221C44E
	bl FUN_0200C3DC
	ldr r0, [r4, #4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
_0221C44E:
	bl FUN_0200C5A8
	ldr r0, [r4, #0x10]
	bl FUN_0200BC1C
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_0221C45C
MOD08_0221C45C: ; 0x0221C45C
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0x20
	add r5, r0, #0
	add r4, r3, #0
	bl MOD08_02228064
	add r7, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	bl MOD08_02227B70
	add r0, r5, #0
	mov r1, #0
	str r4, [r7, #0x1c]
	bl MOD08_02212498
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	lsl r0, r0, #0x10
	asr r2, r0, #0x10
	add r0, r4, #0
	add r1, r6, #0
	bl FUN_0200C82C
	ldr r0, [r7, #4]
	ldr r1, _0221C4A0 ; =MOD08_0221C428
	add r2, r7, #0
	bl MOD08_02212400
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0221C4A0: .word MOD08_0221C428

	thumb_func_start MOD08_0221C4A4
MOD08_0221C4A4: ; 0x0221C4A4
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldrb r0, [r5]
	cmp r0, #0
	beq _0221C4B6
	cmp r0, #1
	beq _0221C534
	b _0221C59E
_0221C4B6:
	ldr r1, [r5, #0x34]
	ldr r0, _0221C5C4 ; =0x0222C4D4
	lsl r2, r1, #1
	ldrsh r4, [r0, r2]
	add r0, r1, #1
	str r0, [r5, #0x34]
	cmp r4, #0xff
	beq _0221C506
	cmp r4, #0
	bne _0221C4FA
	ldr r0, [r5, #0x1c]
	bl FUN_0200C6A4
	add r6, r0, #0
	ldr r0, [r5, #4]
	bl MOD08_02215574
	cmp r6, r0
	ldr r0, [r5, #4]
	bne _0221C4EE
	mov r1, #2
	bl MOD08_02215600
	add r1, r0, #0
	ldr r0, [r5, #0x1c]
	bl FUN_0200C6B0
	b _0221C4FA
_0221C4EE:
	bl MOD08_02215574
	add r1, r0, #0
	ldr r0, [r5, #0x1c]
	bl FUN_0200C6B0
_0221C4FA:
	ldr r0, [r5, #0x1c]
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200C82C
	b _0221C5B4
_0221C506:
	ldr r0, [r5, #0x1c]
	mov r1, #2
	bl FUN_0200C840
	add r0, r5, #0
	ldr r2, _0221C5C8 ; =0x00001FFF
	add r0, #0x20
	mov r1, #0
	mov r3, #8
	bl MOD08_02218008
	mov r1, #7
	ldr r0, [r5, #0x1c]
	mvn r1, r1
	mov r2, #0x10
	bl FUN_0200C8DC
	mov r0, #0
	str r0, [r5, #0x34]
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
	b _0221C5B4
_0221C534:
	add r0, r5, #0
	add r0, #0x20
	bl MOD08_02218058
	cmp r0, #1
	bne _0221C54E
	ldr r1, [r5, #0x20]
	ldr r0, [r5, #0x1c]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_0200C898
	b _0221C5B4
_0221C54E:
	ldr r0, [r5, #0x34]
	cmp r0, #3
	ble _0221C55C
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
	b _0221C5B4
_0221C55C:
	add r0, r0, #1
	str r0, [r5, #0x34]
	cmp r0, #1
	beq _0221C56E
	cmp r0, #2
	beq _0221C57E
	cmp r0, #3
	beq _0221C58E
	b _0221C5B4
_0221C56E:
	add r0, r5, #0
	ldr r1, _0221C5C8 ; =0x00001FFF
	ldr r2, _0221C5CC ; =0xFFFFE001
	add r0, #0x20
	mov r3, #8
	bl MOD08_02218008
	b _0221C5B4
_0221C57E:
	ldr r1, _0221C5CC ; =0xFFFFE001
	add r0, r5, #0
	add r0, #0x20
	lsr r2, r1, #0x13
	mov r3, #8
	bl MOD08_02218008
	b _0221C5B4
_0221C58E:
	add r0, r5, #0
	ldr r1, _0221C5C8 ; =0x00001FFF
	add r0, #0x20
	mov r2, #0
	mov r3, #8
	bl MOD08_02218008
	b _0221C5B4
_0221C59E:
	ldr r0, [r5, #0x1c]
	bl FUN_0200C3DC
	ldr r0, [r5, #4]
	add r1, r4, #0
	bl MOD08_02212438
	add r0, r5, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
_0221C5B4:
	ldr r0, [r5, #0x1c]
	bl FUN_0200C5A8
	ldr r0, [r5, #0x10]
	bl FUN_0200BC1C
	pop {r4, r5, r6, pc}
	nop
_0221C5C4: .word MOD8_0222C4D4
_0221C5C8: .word 0x00001FFF
_0221C5CC: .word 0xFFFFE001

	thumb_func_start MOD08_0221C5D0
MOD08_0221C5D0: ; 0x0221C5D0
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0x38
	add r5, r0, #0
	add r6, r3, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02227B70
	str r6, [r4, #0x1c]
	mov r0, #0
	str r0, [r4, #0x34]
	add r0, r5, #0
	bl MOD08_02212460
	add r7, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #0
	bl MOD08_02217B98
	add r6, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #1
	bl MOD08_02217B98
	add r2, r0, #0
	ldr r0, [r4, #0x1c]
	add r1, r6, #0
	bl FUN_0200C714
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_02227470
	cmp r0, #4
	ldr r0, [r4, #0x1c]
	bne _0221C630
	mov r1, #1
	bl FUN_0200C5C0
	b _0221C636
_0221C630:
	mov r1, #0
	bl FUN_0200C5C0
_0221C636:
	ldr r0, [r4, #4]
	bl MOD08_02215574
	add r1, r0, #0
	ldr r0, [r4, #0x1c]
	bl FUN_0200C6B0
	ldr r0, [r4, #0x1c]
	mov r1, #0
	mov r2, #0xc
	bl FUN_0200C82C
	ldr r0, [r4, #4]
	ldr r1, _0221C65C ; =MOD08_0221C4A4
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221C65C: .word MOD08_0221C4A4

	thumb_func_start MOD08_0221C660
MOD08_0221C660: ; 0x0221C660
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x1c]
	bl FUN_0200C608
	cmp r0, #0
	ldr r0, [r4, #0x1c]
	bne _0221C686
	bl FUN_0200C3DC
	ldr r0, [r4, #4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
_0221C686:
	bl FUN_0200C5A8
	ldr r0, [r4, #0x10]
	bl FUN_0200BC1C
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_0221C694
MOD08_0221C694: ; 0x0221C694
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0x38
	add r5, r0, #0
	add r6, r3, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02227B70
	add r0, r5, #0
	str r6, [r4, #0x1c]
	bl MOD08_02212460
	add r7, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #0
	bl MOD08_02217B98
	add r6, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #1
	bl MOD08_02217B98
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _0221C6DC
	mov r6, #0x48
	mov r2, #0x20
	mov r5, #0
	b _0221C6F2
_0221C6DC:
	ldr r0, [r4, #4]
	add r1, r7, #0
	bl MOD08_02227470
	cmp r0, #3
	bne _0221C6EE
	mov r2, #0x7e
	mov r5, #1
	b _0221C6F2
_0221C6EE:
	mov r2, #0x20
	mov r5, #0
_0221C6F2:
	ldr r0, [r4, #0x1c]
	add r1, r6, #0
	bl FUN_0200C714
	ldr r0, [r4, #0x1c]
	add r1, r5, #0
	bl FUN_0200C5C0
	ldr r0, [r4, #4]
	mov r1, #2
	bl MOD08_02215600
	add r1, r0, #0
	ldr r0, [r4, #0x1c]
	bl FUN_0200C6B0
	ldr r0, [r4, #4]
	ldr r1, _0221C720 ; =MOD08_0221C660
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221C720: .word MOD08_0221C660

	thumb_func_start MOD08_0221C724
MOD08_0221C724: ; 0x0221C724
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bhi _0221C816
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221C73E: ; jump table
	.short _0221C746 - _0221C73E - 2 ; case 0
	.short _0221C76C - _0221C73E - 2 ; case 1
	.short _0221C784 - _0221C73E - 2 ; case 2
	.short _0221C7C0 - _0221C73E - 2 ; case 3
_0221C746:
	mov r0, #0xa0
	str r0, [sp]
	mov r3, #0x70
	mov r0, #1
	str r3, [sp, #4]
	mov r2, #0x15
	str r2, [sp, #8]
	lsl r0, r0, #0x12
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0x24
	add r1, #0x48
	sub r2, #0x33
	bl MOD08_02217F50
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221C82E
_0221C76C:
	add r0, r4, #0
	ldr r2, [r4, #0x1c]
	add r0, #0x24
	add r1, #0x48
	bl MOD08_02217FE4
	cmp r0, #0
	bne _0221C82E
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221C82E
_0221C784:
	ldr r0, [r4, #0x1c]
	bl FUN_0200C608
	cmp r0, #0
	bne _0221C82E
	ldr r0, [r4, #0x1c]
	mov r1, #1
	bl FUN_0200C90C
	add r0, r4, #0
	add r2, r4, #0
	mov r1, #0x10
	add r0, #0x20
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0x21
	strb r1, [r0]
	add r1, r4, #0
	add r1, #0x20
	add r2, #0x21
	ldrb r1, [r1]
	ldrb r2, [r2]
	ldr r0, [r4, #4]
	bl MOD08_02227994
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221C82E
_0221C7C0:
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #0
	beq _0221C7D8
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0x20
	strb r1, [r0]
_0221C7D8:
	add r0, r4, #0
	add r0, #0x21
	ldrb r0, [r0]
	cmp r0, #0x10
	bhs _0221C7F0
	add r0, r4, #0
	add r0, #0x21
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x21
	strb r1, [r0]
_0221C7F0:
	add r0, r4, #0
	add r0, #0x20
	ldrb r1, [r0]
	add r0, r4, #0
	add r0, #0x21
	ldrb r0, [r0]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0221C840 ; =0x04000052
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #0
	bne _0221C82E
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221C82E
_0221C816:
	ldr r0, [r4, #0x1c]
	bl FUN_0200C3DC
	ldr r0, [r4, #4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x10
	pop {r3, r4, r5, pc}
_0221C82E:
	ldr r0, [r4, #0x1c]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x10]
	bl FUN_0200BC1C
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_0221C840: .word 0x04000052

	thumb_func_start MOD08_0221C844
MOD08_0221C844: ; 0x0221C844
	push {r4, r5, r6, lr}
	mov r1, #0x6c
	add r6, r0, #0
	add r5, r3, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r6, #0
	add r1, r4, #0
	bl MOD08_02227B70
	mov r1, #0x1d
	str r5, [r4, #0x1c]
	add r0, r5, #0
	mvn r1, r1
	mov r2, #0xa0
	bl FUN_0200C714
	ldr r0, [r4, #4]
	mov r1, #2
	bl MOD08_02215600
	add r1, r0, #0
	ldr r0, [r4, #0x1c]
	bl FUN_0200C6B0
	ldr r0, [r4, #4]
	ldr r1, _0221C884 ; =MOD08_0221C724
	add r2, r4, #0
	bl MOD08_02212400
	pop {r4, r5, r6, pc}
	.align 2, 0
_0221C884: .word MOD08_0221C724

	thumb_func_start MOD08_0221C888
MOD08_0221C888: ; 0x0221C888
	push {r4, lr}
	mov r1, #0
	add r4, r0, #0
	bl MOD08_02212498
	cmp r0, #0
	beq _0221C89E
	add r0, r4, #0
	bl MOD08_02218BD4
	pop {r4, pc}
_0221C89E:
	add r0, r4, #0
	bl MOD08_02218C04
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_0221C8A8
MOD08_0221C8A8: ; 0x0221C8A8
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r0, #0
	ldrb r0, [r4]
	cmp r0, #0x18
	bls _0221C8B6
	b _0221CAAA
_0221C8B6:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0221C8C2: ; jump table
	.short _0221C8F4 - _0221C8C2 - 2 ; case 0
	.short _0221CAAA - _0221C8C2 - 2 ; case 1
	.short _0221CAAA - _0221C8C2 - 2 ; case 2
	.short _0221CAAA - _0221C8C2 - 2 ; case 3
	.short _0221CAAA - _0221C8C2 - 2 ; case 4
	.short _0221C9A0 - _0221C8C2 - 2 ; case 5
	.short _0221C9A0 - _0221C8C2 - 2 ; case 6
	.short _0221C9CA - _0221C8C2 - 2 ; case 7
	.short _0221CAAA - _0221C8C2 - 2 ; case 8
	.short _0221CAAA - _0221C8C2 - 2 ; case 9
	.short _0221C9E4 - _0221C8C2 - 2 ; case 10
	.short _0221C9E4 - _0221C8C2 - 2 ; case 11
	.short _0221CA0E - _0221C8C2 - 2 ; case 12
	.short _0221CAAA - _0221C8C2 - 2 ; case 13
	.short _0221CAAA - _0221C8C2 - 2 ; case 14
	.short _0221CA26 - _0221C8C2 - 2 ; case 15
	.short _0221CA26 - _0221C8C2 - 2 ; case 16
	.short _0221CA50 - _0221C8C2 - 2 ; case 17
	.short _0221CAAA - _0221C8C2 - 2 ; case 18
	.short _0221CAAA - _0221C8C2 - 2 ; case 19
	.short _0221CAAA - _0221C8C2 - 2 ; case 20
	.short _0221CAAA - _0221C8C2 - 2 ; case 21
	.short _0221CA68 - _0221C8C2 - 2 ; case 22
	.short _0221CA68 - _0221C8C2 - 2 ; case 23
	.short _0221CA92 - _0221C8C2 - 2 ; case 24
_0221C8F4:
	ldr r0, [r4, #0x34]
	ldr r1, _0221CAF0 ; =0xFFFF1FFF
	cmp r0, #0
	bne _0221C94E
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r2, [r0]
	add r5, r0, #0
	and r2, r1
	lsr r1, r0, #0xd
	orr r1, r2
	str r1, [r0]
	add r5, #0x48
	ldrh r3, [r5]
	mov r2, #0x3f
	mov r1, #0xf
	bic r3, r2
	orr r1, r3
	mov r3, #0x20
	orr r1, r3
	strh r1, [r5]
	add r5, r0, #0
	add r5, #0x4a
	ldrh r6, [r5]
	mov r1, #0x1f
	bic r6, r2
	orr r1, r6
	orr r1, r3
	strh r1, [r5]
	add r1, r0, #0
	mov r2, #0x80
	add r1, #0x40
	strh r2, [r1]
	ldr r1, _0221CAF4 ; =0x0000A0C0
	add r0, #0x44
	strh r1, [r0]
	bl LCRandom
	mov r1, #5
	bl _s32_div_f
	add r1, #0x23
	add sp, #4
	str r1, [r4, #0x3c]
	pop {r3, r4, r5, r6, pc}
_0221C94E:
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r2, [r0]
	add r5, r0, #0
	and r2, r1
	lsr r1, r0, #0xd
	orr r1, r2
	str r1, [r0]
	add r5, #0x48
	ldrh r3, [r5]
	mov r2, #0x3f
	mov r1, #0xf
	bic r3, r2
	orr r1, r3
	mov r3, #0x20
	orr r1, r3
	strh r1, [r5]
	add r5, r0, #0
	add r5, #0x4a
	ldrh r6, [r5]
	mov r1, #0x1f
	bic r6, r2
	orr r1, r6
	orr r1, r3
	strh r1, [r5]
	add r1, r0, #0
	lsl r2, r3, #0xa
	add r1, #0x40
	strh r2, [r1]
	ldr r1, _0221CAF8 ; =0x000056C0
	add r0, #0x44
	strh r1, [r0]
	bl LCRandom
	mov r1, #5
	bl _s32_div_f
	add r1, #0x23
	add sp, #4
	str r1, [r4, #0x3c]
	pop {r3, r4, r5, r6, pc}
_0221C9A0:
	bl LCRandom
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	beq _0221C9D0
	ldr r0, [r4, #0x38]
	cmp r0, #0
	bne _0221C9D0
	add r0, r0, #1
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x1c]
	mov r1, #0
	mov r2, #4
	bl FUN_0200C82C
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0221C9CA:
	ldr r0, [r4, #0x38]
	cmp r0, #1
	bne _0221C9D2
_0221C9D0:
	b _0221CAEC
_0221C9D2:
	add r0, r0, #1
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x1c]
	mov r1, #0
	mov r2, #4
	bl FUN_0200C82C
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0221C9E4:
	bl LCRandom
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	beq _0221CAEC
	ldr r0, [r4, #0x38]
	cmp r0, #1
	bne _0221CAEC
	add r0, r0, #1
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x1c]
	mov r1, #0
	mov r2, #4
	bl FUN_0200C82C
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0221CA0E:
	ldr r0, [r4, #0x38]
	cmp r0, #2
	beq _0221CAEC
	add r0, r0, #1
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x1c]
	mov r1, #0
	mov r2, #4
	bl FUN_0200C82C
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0221CA26:
	bl LCRandom
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	beq _0221CAEC
	ldr r0, [r4, #0x38]
	cmp r0, #2
	bne _0221CAEC
	add r0, r0, #1
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x1c]
	mov r1, #0
	mov r2, #4
	bl FUN_0200C82C
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0221CA50:
	ldr r0, [r4, #0x38]
	cmp r0, #3
	beq _0221CAEC
	add r0, r0, #1
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x1c]
	mov r1, #0
	mov r2, #4
	bl FUN_0200C82C
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0221CA68:
	bl LCRandom
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	beq _0221CAEC
	ldr r0, [r4, #0x38]
	cmp r0, #3
	bne _0221CAEC
	add r0, r0, #1
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x1c]
	mov r1, #0
	mov r2, #8
	bl FUN_0200C82C
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0221CA92:
	ldr r0, [r4, #0x38]
	cmp r0, #4
	beq _0221CAEC
	add r0, r0, #1
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x1c]
	mov r1, #0
	mov r2, #8
	bl FUN_0200C82C
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0221CAAA:
	ldr r1, [r4, #0x3c]
	cmp r0, r1
	ble _0221CAEC
	ldr r0, [r4, #0x38]
	cmp r0, #0x14
	ldr r0, [r4, #0x1c]
	bge _0221CAE6
	mov r1, #0
	mov r2, #4
	bl FUN_0200C82C
	add r1, sp, #0
	ldr r0, [r4, #0x1c]
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	add r0, sp, #0
	mov r1, #0
	ldrsh r0, [r0, r1]
	cmp r0, #0x82
	ble _0221CADC
	ldr r0, [r4, #0x1c]
	bl FUN_0200C644
_0221CADC:
	ldr r0, [r4, #0x38]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0x38]
	pop {r3, r4, r5, r6, pc}
_0221CAE6:
	mov r1, #0
	bl FUN_0200C644
_0221CAEC:
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0221CAF0: .word 0xFFFF1FFF
_0221CAF4: .word 0x0000A0C0
_0221CAF8: .word 0x000056C0

	thumb_func_start MOD08_0221CAFC
MOD08_0221CAFC: ; 0x0221CAFC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x30]
	cmp r0, #0
	beq _0221CB0E
	add r0, r4, #0
	bl MOD08_0221C8A8
_0221CB0E:
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	ldrb r1, [r4]
	ldr r0, [r4, #0x24]
	cmp r1, r0
	blt _0221CB66
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r2, [r0]
	ldr r1, _0221CB74 ; =0xFFFF1FFF
	and r1, r2
	add r2, r0, #0
	str r1, [r0]
	add r2, #0x48
	ldrh r3, [r2]
	mov r1, #0x3f
	bic r3, r1
	strh r3, [r2]
	add r2, r0, #0
	add r2, #0x4a
	ldrh r3, [r2]
	bic r3, r1
	strh r3, [r2]
	add r2, r0, #0
	mov r1, #0
	add r2, #0x40
	strh r1, [r2]
	add r0, #0x44
	strh r1, [r0]
	ldr r0, [r4, #0x1c]
	bl FUN_0200C644
	ldr r0, [r4, #0xc]
	bl FUN_0200BC1C
	ldr r0, [r4, #4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
_0221CB66:
	ldr r0, [r4, #0x1c]
	bl FUN_0200C5A8
	ldr r0, [r4, #0xc]
	bl FUN_0200BC1C
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221CB74: .word 0xFFFF1FFF

	thumb_func_start MOD08_0221CB78
MOD08_0221CB78: ; 0x0221CB78
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0x40
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02227B70
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	str r0, [r4, #0x20]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	str r0, [r4, #0x24]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	str r0, [r4, #0x28]
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	str r0, [r4, #0x2c]
	add r0, r5, #0
	mov r1, #5
	bl MOD08_02212498
	str r0, [r4, #0x30]
	add r0, r5, #0
	mov r1, #6
	bl MOD08_02212498
	str r0, [r4, #0x34]
	ldr r0, [r4, #4]
	ldr r1, [r4, #0x20]
	bl MOD08_022124D8
	str r0, [r4, #0x1c]
	mov r0, #0
	str r0, [r4, #0x38]
	ldr r1, [r4, #0x28]
	cmp r1, #0xff
	beq _0221CBEA
	add r0, r5, #0
	bl MOD08_02215600
	add r1, r0, #0
	ldr r0, [r4, #0x1c]
	bl FUN_0200C6B0
_0221CBEA:
	ldr r1, [r4, #0x2c]
	cmp r1, #0xff
	beq _0221CBF6
	ldr r0, [r4, #0x1c]
	bl FUN_0200C6C4
_0221CBF6:
	add r0, r5, #0
	bl MOD08_0221553C
	cmp r0, #1
	beq _0221CC28
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	cmp r0, #2
	beq _0221CC18
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	cmp r0, #3
	bne _0221CC28
_0221CC18:
	ldr r0, [r4, #0x1c]
	mov r1, #0
	bl FUN_0200C644
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
_0221CC28:
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	add r7, r0, #0
	add r0, r5, #0
	bl MOD08_02212458
	add r6, r0, #0
	add r0, r5, #0
	bl MOD08_02212460
	str r0, [sp]
	ldr r0, [r4, #0x2c]
	cmp r0, #0xff
	beq _0221CC76
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02227468
	add r6, r0, #0
	ldr r1, [sp]
	add r0, r5, #0
	bl MOD08_02227468
	cmp r7, #3
	bhi _0221CC76
	add r1, r7, r7
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0221CC6A: ; jump table
	.short _0221CC72 - _0221CC6A - 2 ; case 0
	.short _0221CCFC - _0221CC6A - 2 ; case 1
	.short _0221CCB8 - _0221CC6A - 2 ; case 2
	.short _0221CD40 - _0221CC6A - 2 ; case 3
_0221CC72:
	cmp r6, #5
	bls _0221CC78
_0221CC76:
	b _0221CD82
_0221CC78:
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221CC84: ; jump table
	.short _0221CD82 - _0221CC84 - 2 ; case 0
	.short _0221CD82 - _0221CC84 - 2 ; case 1
	.short _0221CC90 - _0221CC84 - 2 ; case 2
	.short _0221CC9A - _0221CC84 - 2 ; case 3
	.short _0221CCA4 - _0221CC84 - 2 ; case 4
	.short _0221CCAE - _0221CC84 - 2 ; case 5
_0221CC90:
	ldr r0, [r4, #0x1c]
	mov r1, #0x14
	bl FUN_0200C6C4
	b _0221CD82
_0221CC9A:
	ldr r0, [r4, #0x1c]
	mov r1, #0xa
	bl FUN_0200C6C4
	b _0221CD82
_0221CCA4:
	ldr r0, [r4, #0x1c]
	mov r1, #0xa
	bl FUN_0200C6C4
	b _0221CD82
_0221CCAE:
	ldr r0, [r4, #0x1c]
	mov r1, #0x14
	bl FUN_0200C6C4
	b _0221CD82
_0221CCB8:
	cmp r6, #5
	bhi _0221CD82
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221CCC8: ; jump table
	.short _0221CD82 - _0221CCC8 - 2 ; case 0
	.short _0221CD82 - _0221CCC8 - 2 ; case 1
	.short _0221CCD4 - _0221CCC8 - 2 ; case 2
	.short _0221CCDE - _0221CCC8 - 2 ; case 3
	.short _0221CCE8 - _0221CCC8 - 2 ; case 4
	.short _0221CCF2 - _0221CCC8 - 2 ; case 5
_0221CCD4:
	ldr r0, [r4, #0x1c]
	mov r1, #0xa
	bl FUN_0200C6C4
	b _0221CD82
_0221CCDE:
	ldr r0, [r4, #0x1c]
	mov r1, #0x14
	bl FUN_0200C6C4
	b _0221CD82
_0221CCE8:
	ldr r0, [r4, #0x1c]
	mov r1, #0x14
	bl FUN_0200C6C4
	b _0221CD82
_0221CCF2:
	ldr r0, [r4, #0x1c]
	mov r1, #0xa
	bl FUN_0200C6C4
	b _0221CD82
_0221CCFC:
	cmp r0, #5
	bhi _0221CD82
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221CD0C: ; jump table
	.short _0221CD82 - _0221CD0C - 2 ; case 0
	.short _0221CD82 - _0221CD0C - 2 ; case 1
	.short _0221CD18 - _0221CD0C - 2 ; case 2
	.short _0221CD22 - _0221CD0C - 2 ; case 3
	.short _0221CD2C - _0221CD0C - 2 ; case 4
	.short _0221CD36 - _0221CD0C - 2 ; case 5
_0221CD18:
	ldr r0, [r4, #0x1c]
	mov r1, #0x14
	bl FUN_0200C6C4
	b _0221CD82
_0221CD22:
	ldr r0, [r4, #0x1c]
	mov r1, #0xa
	bl FUN_0200C6C4
	b _0221CD82
_0221CD2C:
	ldr r0, [r4, #0x1c]
	mov r1, #0xa
	bl FUN_0200C6C4
	b _0221CD82
_0221CD36:
	ldr r0, [r4, #0x1c]
	mov r1, #0x14
	bl FUN_0200C6C4
	b _0221CD82
_0221CD40:
	cmp r0, #5
	bhi _0221CD82
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221CD50: ; jump table
	.short _0221CD82 - _0221CD50 - 2 ; case 0
	.short _0221CD82 - _0221CD50 - 2 ; case 1
	.short _0221CD5C - _0221CD50 - 2 ; case 2
	.short _0221CD66 - _0221CD50 - 2 ; case 3
	.short _0221CD70 - _0221CD50 - 2 ; case 4
	.short _0221CD7A - _0221CD50 - 2 ; case 5
_0221CD5C:
	ldr r0, [r4, #0x1c]
	mov r1, #0xa
	bl FUN_0200C6C4
	b _0221CD82
_0221CD66:
	ldr r0, [r4, #0x1c]
	mov r1, #0x14
	bl FUN_0200C6C4
	b _0221CD82
_0221CD70:
	ldr r0, [r4, #0x1c]
	mov r1, #0x14
	bl FUN_0200C6C4
	b _0221CD82
_0221CD7A:
	ldr r0, [r4, #0x1c]
	mov r1, #0xa
	bl FUN_0200C6C4
_0221CD82:
	ldr r0, [r4, #4]
	ldr r1, _0221CD90 ; =MOD08_0221CAFC
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221CD90: .word MOD08_0221CAFC

	thumb_func_start MOD08_0221CD94
MOD08_0221CD94: ; 0x0221CD94
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r2, r0, #0
	ldr r0, [r6, #0x2c]
	cmp r0, #0
	bne _0221CDB0
	ldr r0, [r6, #4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r6, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
_0221CDB0:
	sub r0, r0, #1
	str r0, [r6, #0x2c]
	mov r4, #0
	add r5, r6, #0
_0221CDB8:
	ldr r0, [r5, #0x1c]
	cmp r0, #0
	beq _0221CDC2
	bl FUN_0200C5A8
_0221CDC2:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0221CDB8
	ldr r0, [r6, #0xc]
	bl FUN_0200BC1C
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_0221CDD4
MOD08_0221CDD4: ; 0x0221CDD4
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0x34
	add r4, r0, #0
	bl MOD08_02228064
	add r7, r0, #0
	add r0, r4, #0
	add r1, r7, #0
	bl MOD08_02227B70
	add r0, r4, #0
	mov r1, #0
	bl MOD08_02212498
	cmp r0, #0
	bne _0221CDF8
	mov r0, #3
	b _0221CE00
_0221CDF8:
	add r0, r4, #0
	mov r1, #0
	bl MOD08_02212498
_0221CE00:
	ldr r5, _0221CE38 ; =MOD8_0222D5A0
	str r0, [r7, #0x2c]
	mov r6, #0
	add r4, r7, #0
_0221CE08:
	ldr r0, [r7, #4]
	add r1, r6, #0
	bl MOD08_022124D8
	str r0, [r4, #0x1c]
	cmp r0, #0
	beq _0221CE1C
	ldr r1, [r5]
	bl FUN_0200C6C4
_0221CE1C:
	add r6, r6, #1
	add r4, r4, #4
	add r5, r5, #4
	cmp r6, #4
	blt _0221CE08
	ldr r0, [r7, #4]
	ldr r1, _0221CE3C ; =MOD08_0221CD94
	add r2, r7, #0
	bl MOD08_02212400
	add r1, r7, #0
	bl MOD08_0221CD94
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0221CE38: .word MOD8_0222D5A0
_0221CE3C: .word MOD08_0221CD94

	thumb_func_start MOD08_0221CE40
MOD08_0221CE40: ; 0x0221CE40
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r5, r1, #0
	add r4, r0, #0
	ldrb r0, [r5, #8]
	cmp r0, #0
	beq _0221CE54
	cmp r0, #1
	beq _0221CE9A
	b _0221CEB2
_0221CE54:
	mov r0, #0
	str r0, [r5]
	ldr r0, [r5, #0xc]
	mov r1, #2
	bl MOD08_022155C4
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl MOD08_02218998
	add r6, r0, #0
	ldr r0, [r5, #0xc]
	bl MOD08_02212014
	mov r1, #0xc8
	str r1, [sp]
	mov r3, #2
	str r4, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	str r6, [sp, #0xc]
	str r0, [sp, #0x10]
	add r0, r1, #0
	mov r1, #0xa0
	mov r2, #0xb6
	lsl r3, r3, #0x10
	bl MOD08_022188DC
	str r0, [r5, #0x24]
	ldrb r0, [r5, #8]
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r5, #8]
	pop {r3, r4, r5, r6, pc}
_0221CE9A:
	ldr r0, [r5]
	add r1, r0, #1
	str r1, [r5]
	ldr r0, [r5, #4]
	cmp r1, r0
	blt _0221CEC0
	ldr r0, [r5, #0x24]
	bl MOD08_0221894C
	ldrb r0, [r5, #8]
	add r0, r0, #1
	strb r0, [r5, #8]
_0221CEB2:
	ldr r0, [r5, #0xc]
	add r1, r4, #0
	bl MOD08_02212438
	add r0, r5, #0
	bl FreeToHeap
_0221CEC0:
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}

	thumb_func_start MOD08_0221CEC4
MOD08_0221CEC4: ; 0x0221CEC4
	push {r3, r4, r5, lr}
	mov r1, #0x28
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r1, r4, #0
	add r0, r5, #0
	add r1, #8
	bl MOD08_02227B70
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	str r0, [r4, #4]
	ldr r0, [r4, #0xc]
	ldr r1, _0221CEF0 ; =MOD08_0221CE40
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221CEF0: .word MOD08_0221CE40

	thumb_func_start MOD08_0221CEF4
MOD08_0221CEF4: ; 0x0221CEF4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r1, #0
	str r0, [sp, #0xc]
	ldrb r0, [r4]
	cmp r0, #3
	bls _0221CF04
	b _0221D076
_0221CF04:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221CF10: ; jump table
	.short _0221CF18 - _0221CF10 - 2 ; case 0
	.short _0221CFCA - _0221CF10 - 2 ; case 1
	.short _0221CFE8 - _0221CF10 - 2 ; case 2
	.short _0221D042 - _0221CF10 - 2 ; case 3
_0221CF18:
	ldrb r0, [r4, #4]
	mov r7, #0
	add r1, r7, #0
	add r0, r0, #1
	strb r0, [r4, #4]
	ldr r0, [r4, #8]
	bl MOD08_02212498
	cmp r0, #0
	ble _0221CF8E
	ldr r6, _0221D0E4 ; =0x0222C536
	add r5, r4, #0
_0221CF30:
	add r1, sp, #0x10
	ldr r0, [r5, #0x14]
	add r1, #2
	add r2, sp, #0x10
	bl FUN_0200C7A0
	ldrb r1, [r4, #4]
	ldrb r0, [r6]
	cmp r1, r0
	blo _0221CF74
	add r0, r4, r7
	ldrb r1, [r0, #1]
	add r1, r1, #1
	strb r1, [r0, #1]
	ldrb r2, [r0, #1]
	ldrb r1, [r6, #1]
	cmp r2, r1
	blo _0221CF7C
	mov r1, #0
	strb r1, [r0, #1]
	ldr r0, [r5, #0x14]
	bl FUN_0200C658
	cmp r0, #1
	ldr r0, [r5, #0x14]
	bne _0221CF6C
	mov r1, #0
	bl FUN_0200C644
	b _0221CF7C
_0221CF6C:
	mov r1, #1
	bl FUN_0200C644
	b _0221CF7C
_0221CF74:
	ldr r0, [r5, #0x14]
	mov r1, #0
	bl FUN_0200C644
_0221CF7C:
	ldr r0, [r4, #8]
	mov r1, #0
	add r5, r5, #4
	add r6, r6, #2
	add r7, r7, #1
	bl MOD08_02212498
	cmp r7, r0
	blt _0221CF30
_0221CF8E:
	ldrb r0, [r4, #4]
	cmp r0, #0x2d
	blo _0221D02C
	mov r5, #0
	ldr r0, [r4, #8]
	add r1, r5, #0
	bl MOD08_02212498
	cmp r0, #0
	ble _0221CFBE
	add r6, r4, #0
	mov r7, #1
_0221CFA6:
	ldr r0, [r6, #0x14]
	add r1, r7, #0
	bl FUN_0200C644
	ldr r0, [r4, #8]
	mov r1, #0
	add r6, r6, #4
	add r5, r5, #1
	bl MOD08_02212498
	cmp r5, r0
	blt _0221CFA6
_0221CFBE:
	mov r0, #0
	strb r0, [r4, #4]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221D0B0
_0221CFCA:
	mov r1, #0x64
	str r1, [sp]
	str r1, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x20
	mov r2, #0x3c
	add r3, r1, #0
	bl MOD08_022181A8
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221D0B0
_0221CFE8:
	add r0, r4, #0
	add r0, #0x20
	bl MOD08_02218224
	cmp r0, #1
	bne _0221D02E
	mov r5, #0
	ldr r0, [r4, #8]
	add r1, r5, #0
	bl MOD08_02212498
	cmp r0, #0
	ble _0221D0B0
	add r7, r4, #0
	add r6, r4, #0
	add r7, #0x20
_0221D008:
	add r0, r7, #0
	add r1, sp, #0x18
	add r2, sp, #0x14
	bl MOD08_0221825C
	ldr r0, [r6, #0x14]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	bl FUN_0200C884
	ldr r0, [r4, #8]
	mov r1, #0
	add r6, r6, #4
	add r5, r5, #1
	bl MOD08_02212498
	cmp r5, r0
	blt _0221D008
_0221D02C:
	b _0221D0B0
_0221D02E:
	ldrb r0, [r4, #4]
	add r0, r0, #1
	strb r0, [r4, #4]
	ldrb r0, [r4, #4]
	cmp r0, #0x2d
	blo _0221D0B0
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221D0B0
_0221D042:
	ldrb r0, [r4, #5]
	cmp r0, #0
	beq _0221D04C
	sub r0, r0, #1
	strb r0, [r4, #5]
_0221D04C:
	ldrb r0, [r4, #6]
	cmp r0, #0xf
	bhs _0221D056
	add r0, r0, #1
	strb r0, [r4, #6]
_0221D056:
	ldrb r0, [r4, #5]
	cmp r0, #0
	bne _0221D068
	ldrb r0, [r4, #6]
	cmp r0, #0xf
	bne _0221D068
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221D068:
	ldrb r0, [r4, #6]
	ldrb r1, [r4, #5]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0221D0E8 ; =0x04000052
	strh r1, [r0]
	b _0221D0B0
_0221D076:
	mov r5, #0
	ldr r0, [r4, #8]
	add r1, r5, #0
	bl MOD08_02212498
	cmp r0, #0
	ble _0221D09E
	add r6, r4, #0
	add r7, r5, #0
_0221D088:
	ldr r0, [r6, #0x14]
	bl FUN_0200C3DC
	ldr r0, [r4, #8]
	add r1, r7, #0
	add r6, r6, #4
	add r5, r5, #1
	bl MOD08_02212498
	cmp r5, r0
	blt _0221D088
_0221D09E:
	ldr r0, [r4, #8]
	ldr r1, [sp, #0xc]
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
_0221D0B0:
	mov r5, #0
	ldr r0, [r4, #8]
	add r1, r5, #0
	bl MOD08_02212498
	cmp r0, #0
	ble _0221D0DA
	add r6, r4, #0
	add r7, r5, #0
_0221D0C2:
	ldr r0, [r6, #0x14]
	ldr r0, [r0]
	bl FUN_0200C59C
	ldr r0, [r4, #8]
	add r1, r7, #0
	add r6, r6, #4
	add r5, r5, #1
	bl MOD08_02212498
	cmp r5, r0
	blt _0221D0C2
_0221D0DA:
	ldr r0, [r4, #0x10]
	bl FUN_0200BC1C
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0221D0E4: .word MOD8_0222C536
_0221D0E8: .word 0x04000052

	thumb_func_start MOD08_0221D0EC
MOD08_0221D0EC: ; 0x0221D0EC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	str r0, [sp]
	add r5, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl MOD08_02212014
	mov r1, #0x44
	bl AllocFromHeap
	add r4, r0, #0
	bne _0221D10A
	bl ErrorHandling
_0221D10A:
	mov r0, #0
	strb r0, [r4, #4]
	strb r0, [r4]
	str r5, [r4, #0xc]
	ldr r0, [sp]
	str r6, [r4, #0x10]
	str r0, [r4, #8]
	ldr r1, [sp]
	add r0, sp, #8
	bl MOD08_02215474
	mov r1, #0
	mvn r1, r1
	ldr r0, [r4, #8]
	add r2, r1, #0
	bl MOD08_02227994
	mov r0, #0xf
	strb r0, [r4, #5]
	mov r0, #0
	strb r0, [r4, #6]
	ldrb r0, [r4, #6]
	ldrb r1, [r4, #5]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0221D21C ; =0x04000052
	strh r1, [r0]
	ldr r0, [sp]
	str r7, [r4, #0x14]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [sp]
	bl MOD08_02227470
	cmp r0, #3
	bne _0221D166
	ldr r0, [sp]
	bl MOD08_02212004
	add r1, r0, #0
	mov r0, #0
	add r2, sp, #4
	bl MOD08_02227564
	b _0221D176
_0221D166:
	ldr r0, [sp]
	bl MOD08_02212004
	add r1, r0, #0
	mov r0, #1
	add r2, sp, #4
	bl MOD08_02227564
_0221D176:
	ldr r0, [r4, #8]
	mov r1, #0
	mov r6, #1
	bl MOD08_02212498
	cmp r0, #1
	ble _0221D1B0
	add r5, r4, #4
	add r7, sp, #4
_0221D188:
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	add r2, sp, #8
	bl FUN_0200C154
	str r0, [r5, #0x14]
	mov r1, #0
	mov r2, #2
	ldrsh r1, [r7, r1]
	ldrsh r2, [r7, r2]
	bl FUN_0200C714
	ldr r0, [r4, #8]
	mov r1, #0
	add r5, r5, #4
	add r6, r6, #1
	bl MOD08_02212498
	cmp r6, r0
	blt _0221D188
_0221D1B0:
	add r3, sp, #4
	mov r1, #0
	mov r2, #2
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldr r0, [r4, #0x14]
	bl FUN_0200C714
	mov r6, #0
	ldr r0, [r4, #8]
	add r1, r6, #0
	bl MOD08_02212498
	cmp r0, #0
	ble _0221D20A
	add r5, r4, #0
	add r7, r6, #0
_0221D1D2:
	add r1, r4, r6
	mov r0, #0
	strb r0, [r1, #1]
	ldr r0, [r5, #0x14]
	mov r1, #2
	bl FUN_0200C840
	mov r2, #0x20
	sub r2, r2, r7
	lsl r2, r2, #0x10
	ldr r0, [r5, #0x14]
	mov r1, #0
	asr r2, r2, #0x10
	bl FUN_0200C82C
	ldr r0, [r5, #0x14]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r4, #8]
	mov r1, #0
	add r5, r5, #4
	add r7, r7, #4
	add r6, r6, #1
	bl MOD08_02212498
	cmp r6, r0
	blt _0221D1D2
_0221D20A:
	mov r3, #1
	ldr r0, [sp]
	ldr r1, _0221D220 ; =MOD08_0221CEF4
	add r2, r4, #0
	lsl r3, r3, #0xc
	bl MOD08_022123E4
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0221D21C: .word 0x04000052
_0221D220: .word MOD08_0221CEF4

	thumb_func_start MOD08_0221D224
MOD08_0221D224: ; 0x0221D224
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #5
	bls _0221D234
	b _0221D404
_0221D234:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221D240: ; jump table
	.short _0221D24C - _0221D240 - 2 ; case 0
	.short _0221D2AE - _0221D240 - 2 ; case 1
	.short _0221D2C8 - _0221D240 - 2 ; case 2
	.short _0221D2EC - _0221D240 - 2 ; case 3
	.short _0221D346 - _0221D240 - 2 ; case 4
	.short _0221D394 - _0221D240 - 2 ; case 5
_0221D24C:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02218170
	cmp r0, #1
	bne _0221D2A4
	add r0, r4, #0
	add r0, #0x38
	bl MOD08_022183F0
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x16
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #0xd
	bl FUN_02007558
	mov r2, #0x38
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl FUN_020079E0
	mov r0, #2
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0x28]
	bl MOD08_0221828C
	mov r2, #2
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #1
	add r2, r2, r3
	bl FUN_02007558
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0221D2A4:
	ldrb r0, [r4]
	add sp, #4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0221D2AE:
	mov r0, #0x1f
	str r0, [sp]
	mov r1, #0
	ldr r0, [r4, #0x10]
	mov r2, #0xa
	add r3, r1, #0
	bl FUN_02007E68
	ldrb r0, [r4]
	add sp, #4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0221D2C8:
	ldr r0, [r4, #0x10]
	bl FUN_02007F20
	cmp r0, #0
	bne _0221D2F6
	mov r0, #0x1f
	str r0, [sp]
	mov r2, #0
	ldr r0, [r4, #0x10]
	mov r1, #0xa
	add r3, r2, #0
	bl FUN_02007E68
	ldrb r0, [r4]
	add sp, #4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0221D2EC:
	ldr r0, [r4, #0x10]
	bl FUN_02007F20
	cmp r0, #0
	beq _0221D2F8
_0221D2F6:
	b _0221D412
_0221D2F8:
	ldrb r0, [r4, #8]
	add r0, r0, #1
	strb r0, [r4, #8]
	ldrb r0, [r4, #8]
	cmp r0, #3
	blo _0221D33E
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl MOD08_02212498
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl MOD08_02212498
	add r6, r0, #0
	ldr r0, [r4, #0xc]
	mov r1, #3
	bl MOD08_02212498
	str r0, [sp]
	add r0, r4, #0
	lsl r1, r5, #0x10
	lsl r3, r6, #0x10
	add r0, #0x14
	asr r1, r1, #0x10
	mov r2, #0x64
	asr r3, r3, #0x10
	bl MOD08_02218120
	ldrb r0, [r4]
	add sp, #4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0221D33E:
	mov r0, #1
	add sp, #4
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0221D346:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02218170
	cmp r0, #1
	bne _0221D38A
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x16
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #0xd
	bl FUN_02007558
	mov r0, #2
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0x28]
	bl MOD08_0221828C
	mov r2, #2
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #1
	add r2, r2, r3
	bl FUN_02007558
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0221D38A:
	ldrb r0, [r4]
	add sp, #4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0221D394:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02218170
	cmp r0, #1
	ldr r0, [r4, #0x10]
	bne _0221D3D8
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x16
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #0xd
	bl FUN_02007558
	mov r0, #2
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0x28]
	bl MOD08_0221828C
	mov r2, #2
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #1
	add r2, r2, r3
	bl FUN_02007558
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0221D3D8:
	mov r1, #0xc
	add r2, r1, #0
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r4, #0x10]
	add r2, #0xf3
	bl FUN_02007558
	mov r2, #2
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_02007558
	ldrb r0, [r4]
	add sp, #4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0221D404:
	ldr r0, [r4, #0xc]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_0221D412:
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_0221D418
MOD08_0221D418: ; 0x0221D418
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	bl MOD08_02212014
	mov r1, #0x5c
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4, #8]
	strb r0, [r4]
	str r5, [r4, #0xc]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #0xc]
	bl MOD08_022154D4
	str r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #2]
	ldr r0, [r4, #0xc]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #0xc]
	bl MOD08_0221552C
	str r0, [r4, #4]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0x64
	lsl r3, r6, #0x10
	add r0, #0x14
	add r2, r1, #0
	asr r3, r3, #0x10
	bl MOD08_02218120
	mov r0, #0xa
	str r0, [sp]
	add r0, r4, #0
	mov r2, #0
	add r0, #0x38
	mov r1, #2
	add r3, r2, #0
	bl MOD08_022183C0
	ldr r0, [r4, #0xc]
	ldr r1, _0221D4A0 ; =MOD08_0221D224
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_0221D4A0: .word MOD08_0221D224

	thumb_func_start MOD08_0221D4A4
MOD08_0221D4A4: ; 0x0221D4A4
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #4
	bls _0221D4B4
	b _0221D6CC
_0221D4B4:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221D4C0: ; jump table
	.short _0221D4CA - _0221D4C0 - 2 ; case 0
	.short _0221D530 - _0221D4C0 - 2 ; case 1
	.short _0221D594 - _0221D4C0 - 2 ; case 2
	.short _0221D5F8 - _0221D4C0 - 2 ; case 3
	.short _0221D65C - _0221D4C0 - 2 ; case 4
_0221D4CA:
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_02218224
	cmp r0, #1
	bne _0221D50E
	mov r2, #0x10
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x12
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xd
	bl FUN_02007558
	mov r0, #2
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0x24]
	bl MOD08_0221828C
	mov r2, #2
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #1
	add r2, r2, r3
	bl FUN_02007558
	add sp, #0xc
	pop {r3, r4, pc}
_0221D50E:
	mov r1, #0x96
	str r1, [sp]
	mov r0, #0x64
	str r0, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	add r0, r4, #0
	mov r2, #0x32
	add r0, #0x10
	add r3, r2, #0
	bl MOD08_022181A8
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, pc}
_0221D530:
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_02218224
	cmp r0, #1
	bne _0221D574
	mov r2, #0x10
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x12
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xd
	bl FUN_02007558
	mov r0, #2
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0x24]
	bl MOD08_0221828C
	mov r2, #2
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #1
	add r2, r2, r3
	bl FUN_02007558
	add sp, #0xc
	pop {r3, r4, pc}
_0221D574:
	mov r2, #0x64
	str r2, [sp]
	str r2, [sp, #4]
	mov r0, #5
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x10
	mov r1, #0x32
	mov r3, #0x96
	bl MOD08_022181A8
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, pc}
_0221D594:
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_02218224
	cmp r0, #1
	bne _0221D5D8
	mov r2, #0x10
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x12
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xd
	bl FUN_02007558
	mov r0, #2
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0x24]
	bl MOD08_0221828C
	mov r2, #2
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #1
	add r2, r2, r3
	bl FUN_02007558
	add sp, #0xc
	pop {r3, r4, pc}
_0221D5D8:
	mov r2, #0x96
	mov r1, #0x64
	str r2, [sp]
	str r1, [sp, #4]
	mov r0, #5
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x10
	add r3, r1, #0
	bl MOD08_022181A8
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, pc}
_0221D5F8:
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_02218224
	cmp r0, #1
	bne _0221D63C
	mov r2, #0x10
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x12
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xd
	bl FUN_02007558
	mov r0, #2
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0x24]
	bl MOD08_0221828C
	mov r2, #2
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #1
	add r2, r2, r3
	bl FUN_02007558
	add sp, #0xc
	pop {r3, r4, pc}
_0221D63C:
	mov r2, #0x64
	str r2, [sp]
	str r2, [sp, #4]
	mov r0, #5
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x96
	add r0, #0x10
	add r3, r1, #0
	bl MOD08_022181A8
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, pc}
_0221D65C:
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_02218224
	cmp r0, #1
	ldr r0, [r4, #0xc]
	bne _0221D6A0
	mov r2, #0x10
	ldrsh r2, [r4, r2]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x12
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xd
	bl FUN_02007558
	mov r0, #2
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0x24]
	bl MOD08_0221828C
	mov r2, #2
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #1
	add r2, r2, r3
	bl FUN_02007558
	add sp, #0xc
	pop {r3, r4, pc}
_0221D6A0:
	mov r1, #0xc
	add r2, r1, #0
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r4, #0xc]
	add r2, #0xf3
	bl FUN_02007558
	mov r2, #2
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_02007558
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, pc}
_0221D6CC:
	ldr r0, [r4, #8]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD08_0221D6E0
MOD08_0221D6E0: ; 0x0221D6E0
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	bl MOD08_02212014
	mov r1, #0x58
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4]
	str r5, [r4, #8]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #8]
	bl MOD08_022154D4
	str r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #2]
	ldr r0, [r4, #8]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #8]
	bl MOD08_0221552C
	str r0, [r4, #4]
	mov r0, #0x32
	str r0, [sp]
	mov r1, #0x64
	str r1, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x10
	mov r2, #0x96
	add r3, r1, #0
	bl MOD08_022181A8
	ldr r0, [r4, #8]
	ldr r1, _0221D748 ; =MOD08_0221D4A4
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0221D748: .word MOD08_0221D4A4

	thumb_func_start MOD08_0221D74C
MOD08_0221D74C: ; 0x0221D74C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r1, #0
	add r2, r0, #0
	ldrb r0, [r5, #1]
	cmp r0, #0
	beq _0221D766
	cmp r0, #1
	beq _0221D84C
	cmp r0, #2
	bne _0221D764
	b _0221D8AE
_0221D764:
	b _0221D8E2
_0221D766:
	ldrb r3, [r5]
	mov r0, #0x1f
	lsr r2, r3, #0x1f
	lsl r1, r3, #0x1f
	sub r1, r1, r2
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #1
	add r1, r3, #1
	str r0, [sp, #0xc]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	str r0, [sp, #8]
	ldr r1, [sp, #0xc]
	mov r0, #6
	mul r0, r1
	ldr r1, _0221D900 ; =0x0222C59A
	ldrsh r2, [r1, r0]
	ldr r1, [sp, #8]
	sub r7, r2, r1
	mov r1, #0xa
	ldrsh r3, [r5, r1]
	ldr r1, _0221D904 ; =0x0222C598
	ldrsh r6, [r1, r0]
	mov r1, #8
	ldrsh r2, [r5, r1]
	ldr r1, _0221D908 ; =0x0222C596
	ldrsh r4, [r1, r0]
	lsl r0, r7, #0x10
	str r3, [sp]
	add r1, r2, r4
	lsr r0, r0, #0x10
	add r2, r2, r6
	str r0, [sp, #4]
	add r0, r5, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, #0x28
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl MOD08_02217E80
	mov r0, #0xa
	ldrsh r3, [r5, r0]
	mov r0, #8
	ldrsh r2, [r5, r0]
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	sub r1, r2, r4
	str r3, [sp]
	sub r2, r2, r6
	str r0, [sp, #4]
	add r0, r5, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, #0x4c
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl MOD08_02217E80
	ldr r0, [sp, #0xc]
	add r1, r0, #1
	mov r0, #6
	mul r0, r1
	ldr r1, _0221D900 ; =0x0222C59A
	ldrsh r2, [r1, r0]
	ldr r1, [sp, #8]
	sub r7, r2, r1
	mov r1, #0xa
	ldrsh r3, [r5, r1]
	ldr r1, _0221D904 ; =0x0222C598
	ldrsh r6, [r1, r0]
	mov r1, #8
	ldrsh r2, [r5, r1]
	ldr r1, _0221D908 ; =0x0222C596
	ldrsh r4, [r1, r0]
	lsl r0, r7, #0x10
	str r3, [sp]
	add r1, r2, r4
	lsr r0, r0, #0x10
	add r2, r2, r6
	str r0, [sp, #4]
	add r0, r5, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, #0x70
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl MOD08_02217E80
	mov r0, #0xa
	ldrsh r3, [r5, r0]
	mov r0, #8
	ldrsh r2, [r5, r0]
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	sub r1, r2, r4
	str r3, [sp]
	sub r2, r2, r6
	str r0, [sp, #4]
	add r0, r5, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, #0x94
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl MOD08_02217E80
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
	ldrb r0, [r5, #1]
	add r0, r0, #1
	strb r0, [r5, #1]
_0221D84C:
	mov r0, #0
	add r7, r5, #0
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	add r7, #0x28
	add r6, r5, #0
	add r4, r5, #0
_0221D85A:
	add r0, r7, #0
	bl MOD08_02217ECC
	cmp r0, #0
	bne _0221D870
	ldr r0, [sp, #0x10]
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x10]
	b _0221D87E
_0221D870:
	mov r1, #0x28
	mov r2, #0x2a
	ldrsh r1, [r6, r1]
	ldrsh r2, [r6, r2]
	ldr r0, [r4, #0x18]
	bl FUN_0200C714
_0221D87E:
	ldr r0, [r4, #0x18]
	bl FUN_0200C5A8
	ldr r0, [sp, #0x14]
	add r7, #0x24
	add r0, r0, #1
	add r6, #0x24
	add r4, r4, #4
	str r0, [sp, #0x14]
	cmp r0, #4
	blt _0221D85A
	ldr r0, [sp, #0x10]
	cmp r0, #4
	bne _0221D8F4
	ldrb r0, [r5]
	cmp r0, #9
	bne _0221D8A8
	ldrb r0, [r5, #1]
	add r0, r0, #1
	strb r0, [r5, #1]
	b _0221D8F4
_0221D8A8:
	mov r0, #0
	strb r0, [r5, #1]
	b _0221D8F4
_0221D8AE:
	ldrb r0, [r5, #4]
	cmp r0, #0
	beq _0221D8B8
	sub r0, r0, #1
	strb r0, [r5, #4]
_0221D8B8:
	ldrb r0, [r5, #5]
	cmp r0, #0xf
	bhs _0221D8C2
	add r0, r0, #1
	strb r0, [r5, #5]
_0221D8C2:
	ldrb r0, [r5, #4]
	cmp r0, #0
	bne _0221D8D4
	ldrb r0, [r5, #5]
	cmp r0, #0xf
	bne _0221D8D4
	ldrb r0, [r5, #1]
	add r0, r0, #1
	strb r0, [r5, #1]
_0221D8D4:
	ldrb r0, [r5, #5]
	ldrb r1, [r5, #4]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0221D90C ; =0x04000052
	strh r1, [r0]
	b _0221D8F4
_0221D8E2:
	ldr r0, [r5, #0xc]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r5, #0
	bl FreeToHeap
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0221D8F4:
	ldr r0, [r5, #0x14]
	bl FUN_0200BC1C
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221D900: .word MOD8_0222C59A
_0221D904: .word MOD8_0222C598
_0221D908: .word MOD8_0222C596
_0221D90C: .word 0x04000052

	thumb_func_start MOD08_0221D910
MOD08_0221D910: ; 0x0221D910
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	str r0, [sp, #0x18]
	bl MOD08_02212014
	mov r1, #0xb8
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4, #1]
	strb r0, [r4]
	ldr r0, [sp, #0x18]
	str r0, [r4, #0xc]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #0xc]
	bl MOD08_022154D4
	str r0, [r4, #0x10]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #8]
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #0xa]
	ldr r0, [r4, #0x10]
	mov r1, #0x29
	bl FUN_0200782C
	mov r1, #0xa
	ldrsh r1, [r4, r1]
	sub r0, r1, r0
	strh r0, [r4, #0xa]
	ldr r0, [r4, #0xc]
	bl MOD08_02212504
	str r0, [r4, #0x14]
	mov r0, #8
	strb r0, [r4, #4]
	mov r1, #6
	strb r1, [r4, #5]
	sub r1, r1, #7
	ldr r0, [r4, #0xc]
	add r2, r1, #0
	bl MOD08_02227994
	ldrb r0, [r4, #5]
	ldrb r1, [r4, #4]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0221DB90 ; =0x04000052
	strh r1, [r0]
	ldr r0, [r4, #0xc]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #0xc]
	bl MOD08_0221550C
	str r0, [sp, #0x20]
	ldr r0, [r4, #0xc]
	bl MOD08_02215574
	add r7, r0, #0
	ldr r0, [r4, #0xc]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #0xc]
	bl MOD08_0221551C
	str r0, [sp, #0x1c]
	mov r6, #0
	add r5, r4, #0
_0221D9AE:
	ldr r0, [r4, #0xc]
	add r1, r6, #0
	bl MOD08_022124D8
	mov r1, #1
	str r0, [r5, #0x18]
	bl FUN_0200C90C
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #4
	blt _0221D9AE
	ldr r0, [r4, #0xc]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #0xc]
	bl MOD08_02227470
	cmp r0, #3
	ldr r0, [r4, #0x18]
	bne _0221DA9E
	mov r1, #0xa
	bl FUN_0200C6C4
	ldr r0, [r4, #0x1c]
	mov r1, #0xa
	bl FUN_0200C6C4
	ldr r0, [r4, #0x20]
	mov r1, #0x14
	bl FUN_0200C6C4
	ldr r0, [r4, #0x24]
	mov r1, #0x14
	bl FUN_0200C6C4
	ldr r0, [r4, #0x18]
	add r1, r7, #0
	bl FUN_0200C6B0
	ldr r0, [r4, #0x1c]
	add r1, r7, #0
	bl FUN_0200C6B0
	ldr r0, [r4, #0x20]
	add r1, r7, #0
	bl FUN_0200C6B0
	ldr r0, [r4, #0x24]
	add r1, r7, #0
	bl FUN_0200C6B0
	ldr r0, [r4, #0x18]
	ldr r0, [r0]
	bl FUN_02020354
	mov r1, #1
	bl FUN_0201E28C
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	ldr r0, [r4, #0xc]
	bl MOD08_02215504
	add r6, r0, #0
	ldr r0, [sp, #0x18]
	bl MOD08_02212014
	add r3, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	lsl r0, r5, #0x14
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x20]
	add r0, r6, #0
	bl FUN_02003B40
	ldr r0, [r4, #0x20]
	ldr r0, [r0]
	bl FUN_02020354
	mov r1, #1
	bl FUN_0201E28C
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	ldr r0, [r4, #0xc]
	bl MOD08_02215504
	add r6, r0, #0
	ldr r0, [sp, #0x18]
	bl MOD08_02212014
	add r3, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	lsl r0, r5, #0x14
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	mov r0, #0xc4
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x20]
	add r0, r6, #0
	bl FUN_02003B40
	b _0221DB80
_0221DA9E:
	mov r1, #0x14
	bl FUN_0200C6C4
	ldr r0, [r4, #0x1c]
	mov r1, #0x14
	bl FUN_0200C6C4
	ldr r0, [r4, #0x20]
	mov r1, #0xa
	bl FUN_0200C6C4
	ldr r0, [r4, #0x24]
	mov r1, #0xa
	bl FUN_0200C6C4
	ldr r0, [r4, #0x18]
	add r1, r7, #1
	bl FUN_0200C6B0
	ldr r0, [r4, #0x1c]
	add r1, r7, #1
	bl FUN_0200C6B0
	ldr r0, [r4, #0x20]
	add r1, r7, #1
	bl FUN_0200C6B0
	ldr r0, [r4, #0x24]
	add r1, r7, #1
	bl FUN_0200C6B0
	ldr r0, [r4, #0x18]
	add r1, r7, #0
	bl FUN_0200C6B0
	ldr r0, [r4, #0x1c]
	add r1, r7, #0
	bl FUN_0200C6B0
	ldr r0, [r4, #0x20]
	add r1, r7, #0
	bl FUN_0200C6B0
	ldr r0, [r4, #0x24]
	add r1, r7, #0
	bl FUN_0200C6B0
	ldr r0, [r4, #0x18]
	ldr r0, [r0]
	bl FUN_02020354
	mov r1, #1
	bl FUN_0201E28C
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	ldr r0, [r4, #0xc]
	bl MOD08_02215504
	add r6, r0, #0
	ldr r0, [sp, #0x18]
	bl MOD08_02212014
	add r3, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	lsl r0, r5, #0x14
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	mov r0, #0xc4
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x20]
	add r0, r6, #0
	bl FUN_02003B40
	ldr r0, [r4, #0x20]
	ldr r0, [r0]
	bl FUN_02020354
	mov r1, #1
	bl FUN_0201E28C
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	ldr r0, [r4, #0xc]
	bl MOD08_02215504
	add r6, r0, #0
	ldr r0, [sp, #0x18]
	bl MOD08_02212014
	add r3, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	lsl r0, r5, #0x14
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x20]
	add r0, r6, #0
	bl FUN_02003B40
_0221DB80:
	ldr r0, [r4, #0xc]
	ldr r1, _0221DB94 ; =MOD08_0221D74C
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_0221DB90: .word 0x04000052
_0221DB94: .word MOD08_0221D74C

	thumb_func_start MOD08_0221DB98
MOD08_0221DB98: ; 0x0221DB98
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _0221DBAA
	cmp r0, #1
	beq _0221DC04
	b _0221DC44
_0221DBAA:
	ldrb r1, [r4, #2]
	ldr r5, _0221DC54 ; =0x0222C531
	mov r2, #0x64
	lsl r0, r1, #1
	add r3, r1, r0
	ldr r0, _0221DC58 ; =0x0222C532
	ldr r1, _0221DC5C ; =0x0222C530
	ldrb r0, [r0, r3]
	ldrb r1, [r1, r3]
	ldrb r3, [r5, r3]
	str r0, [sp]
	add r0, r4, #0
	add r0, #0xc
	bl MOD08_02218120
	ldrb r0, [r4, #2]
	cmp r0, #0
	ldr r0, _0221DC60 ; =0x00007FFF
	bne _0221DBE0
	str r0, [sp]
	mov r1, #0
	ldr r0, [r4, #8]
	mov r2, #6
	add r3, r1, #0
	bl FUN_02007E68
	b _0221DBEE
_0221DBE0:
	str r0, [sp]
	mov r2, #0
	ldr r0, [r4, #8]
	mov r1, #6
	add r3, r2, #0
	bl FUN_02007E68
_0221DBEE:
	ldrb r1, [r4, #2]
	mov r0, #1
	eor r0, r1
	strb r0, [r4, #2]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_0221DC04:
	add r0, r4, #0
	add r0, #0xc
	bl MOD08_02218170
	cmp r0, #0
	bne _0221DC2C
	ldr r0, [r4, #8]
	bl FUN_02007F20
	cmp r0, #0
	bne _0221DC2C
	ldrb r0, [r4, #1]
	cmp r0, #4
	ldrb r0, [r4]
	bhs _0221DC28
	sub r0, r0, #1
	strb r0, [r4]
	b _0221DC2C
_0221DC28:
	add r0, r0, #1
	strb r0, [r4]
_0221DC2C:
	mov r1, #0xc
	ldrsh r2, [r4, r1]
	ldr r0, [r4, #8]
	bl FUN_02007558
	mov r2, #0xe
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #8]
	mov r1, #0xd
	bl FUN_02007558
	pop {r3, r4, r5, pc}
_0221DC44:
	ldr r0, [r4, #4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221DC54: .word MOD8_0222C531
_0221DC58: .word MOD8_0222C532
_0221DC5C: .word MOD8_0222C530
_0221DC60: .word 0x00007FFF

	thumb_func_start MOD08_0221DC64
MOD08_0221DC64: ; 0x0221DC64
	push {r3, r4, r5, lr}
	mov r1, #0x30
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4]
	strb r0, [r4, #2]
	strb r0, [r4, #1]
	str r5, [r4, #4]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_022154D4
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	ldr r1, _0221DC98 ; =MOD08_0221DB98
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, pc}
	nop
_0221DC98: .word MOD08_0221DB98

	thumb_func_start MOD08_0221DC9C
MOD08_0221DC9C: ; 0x0221DC9C
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _0221DCB0
	cmp r0, #1
	beq _0221DCEA
	b _0221DD42
_0221DCB0:
	ldrb r1, [r4, #1]
	ldr r2, _0221DD54 ; =0x0222C578
	ldr r5, _0221DD58 ; =0x0222C579
	lsl r0, r1, #2
	add r3, r1, r0
	ldr r0, _0221DD5C ; =0x0222C57A
	ldr r1, _0221DD60 ; =0x0222C577
	ldrb r0, [r0, r3]
	ldrb r1, [r1, r3]
	ldrb r2, [r2, r3]
	str r0, [sp]
	mov r0, #0x64
	str r0, [sp, #4]
	ldr r0, _0221DD64 ; =0x0222C57B
	ldrb r0, [r0, r3]
	ldrb r3, [r5, r3]
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_022181A8
	ldrb r0, [r4, #1]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #1]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, pc}
_0221DCEA:
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_02218224
	cmp r0, #0
	bne _0221DD08
	ldrb r0, [r4, #1]
	cmp r0, #3
	ldrb r0, [r4]
	bhs _0221DD04
	sub r0, r0, #1
	strb r0, [r4]
	b _0221DD08
_0221DD04:
	add r0, r0, #1
	strb r0, [r4]
_0221DD08:
	mov r2, #0x10
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x12
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xd
	bl FUN_02007558
	mov r0, #2
	mov r1, #4
	ldrsh r0, [r4, r0]
	ldrsh r1, [r4, r1]
	ldr r2, [r4, #0x24]
	bl MOD08_0221828C
	mov r2, #2
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #1
	add r2, r2, r3
	bl FUN_02007558
	add sp, #0xc
	pop {r4, r5, pc}
_0221DD42:
	ldr r0, [r4, #8]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_0221DD54: .word MOD8_0222C578
_0221DD58: .word MOD8_0222C579
_0221DD5C: .word MOD8_0222C57A
_0221DD60: .word MOD8_0222C577
_0221DD64: .word MOD8_0222C57B

	thumb_func_start MOD08_0221DD68
MOD08_0221DD68: ; 0x0221DD68
	push {r3, r4, r5, lr}
	mov r1, #0x34
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4]
	strb r0, [r4, #1]
	str r5, [r4, #8]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #8]
	bl MOD08_022154D4
	str r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #2]
	ldr r0, [r4, #8]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #8]
	bl MOD08_0221552C
	strh r0, [r4, #4]
	ldr r0, [r4, #8]
	ldr r1, _0221DDB0 ; =MOD08_0221DC9C
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221DDB0: .word MOD08_0221DC9C

	thumb_func_start MOD08_0221DDB4
MOD08_0221DDB4: ; 0x0221DDB4
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #5
	bls _0221DDC4
	b _0221DF24
_0221DDC4:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221DDD0: ; jump table
	.short _0221DDDC - _0221DDD0 - 2 ; case 0
	.short _0221DE16 - _0221DDD0 - 2 ; case 1
	.short _0221DE58 - _0221DDD0 - 2 ; case 2
	.short _0221DE82 - _0221DDD0 - 2 ; case 3
	.short _0221DEA4 - _0221DDD0 - 2 ; case 4
	.short _0221DEE2 - _0221DDD0 - 2 ; case 5
_0221DDDC:
	ldrb r1, [r4, #1]
	ldr r2, _0221DF64 ; =0x0222C550
	ldr r5, _0221DF68 ; =0x0222C551
	lsl r0, r1, #2
	add r3, r1, r0
	ldr r0, _0221DF6C ; =0x0222C552
	ldr r1, _0221DF70 ; =0x0222C54F
	ldrb r0, [r0, r3]
	ldrb r1, [r1, r3]
	ldrb r2, [r2, r3]
	str r0, [sp]
	mov r0, #0x64
	str r0, [sp, #4]
	ldr r0, _0221DF74 ; =0x0222C553
	ldrb r0, [r0, r3]
	ldrb r3, [r5, r3]
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_022181A8
	ldrb r0, [r4, #1]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #1]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, pc}
_0221DE16:
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_02218224
	cmp r0, #0
	bne _0221DE28
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221DE28:
	mov r2, #0x10
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x12
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xd
	bl FUN_02007558
	mov r0, #0
	str r0, [sp]
	mov r1, #2
	mov r2, #6
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	ldr r3, [r4, #0x24]
	bl MOD08_022182DC
	add sp, #0xc
	pop {r4, r5, pc}
_0221DE58:
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0200782C
	mov r1, #0
	add r3, r0, #0
	lsl r3, r3, #0x10
	str r1, [sp]
	mov r0, #5
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x10
	add r2, r1, #0
	asr r3, r3, #0x10
	bl MOD08_02217E80
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, pc}
_0221DE82:
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_02217ECC
	cmp r0, #0
	bne _0221DE94
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221DE94:
	mov r2, #0x12
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_02007558
	add sp, #0xc
	pop {r4, r5, pc}
_0221DEA4:
	ldrb r1, [r4, #1]
	ldr r2, _0221DF64 ; =0x0222C550
	ldr r5, _0221DF68 ; =0x0222C551
	lsl r0, r1, #2
	add r3, r1, r0
	ldr r0, _0221DF6C ; =0x0222C552
	ldr r1, _0221DF70 ; =0x0222C54F
	ldrb r0, [r0, r3]
	ldrb r1, [r1, r3]
	ldrb r2, [r2, r3]
	str r0, [sp]
	mov r0, #0x64
	str r0, [sp, #4]
	ldr r0, _0221DF74 ; =0x0222C553
	ldrb r0, [r0, r3]
	ldrb r3, [r5, r3]
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_022181A8
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #2]
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, pc}
_0221DEE2:
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_02218224
	cmp r0, #0
	bne _0221DEF4
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221DEF4:
	mov r2, #0x10
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x12
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xd
	bl FUN_02007558
	mov r0, #1
	str r0, [sp]
	mov r1, #2
	mov r2, #6
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	ldr r3, [r4, #0x24]
	bl MOD08_022182DC
	add sp, #0xc
	pop {r4, r5, pc}
_0221DF24:
	mov r2, #4
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_02007558
	ldr r0, [r4, #0xc]
	mov r1, #6
	mov r2, #1
	bl FUN_02007558
	mov r1, #0xc
	add r2, r1, #0
	ldr r0, [r4, #0xc]
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r4, #0xc]
	add r2, #0xf3
	bl FUN_02007558
	ldr r0, [r4, #8]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_0221DF64: .word MOD8_0222C550
_0221DF68: .word MOD8_0222C551
_0221DF6C: .word MOD8_0222C552
_0221DF70: .word MOD8_0222C54F
_0221DF74: .word MOD8_0222C553

	thumb_func_start MOD08_0221DF78
MOD08_0221DF78: ; 0x0221DF78
	push {r3, r4, r5, lr}
	mov r1, #0x34
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4]
	strb r0, [r4, #1]
	str r5, [r4, #8]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #8]
	bl MOD08_022154D4
	str r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #2]
	mov r0, #2
	ldrsh r0, [r4, r0]
	strh r0, [r4, #4]
	ldr r0, [r4, #8]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #8]
	bl MOD08_0221552C
	strh r0, [r4, #6]
	ldr r0, [r4, #8]
	ldr r1, _0221DFC8 ; =MOD08_0221DDB4
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, pc}
	nop
_0221DFC8: .word MOD08_0221DDB4

	thumb_func_start MOD08_0221DFCC
MOD08_0221DFCC: ; 0x0221DFCC
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #4
	bhi _0221E0B6
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221DFE6: ; jump table
	.short _0221DFF0 - _0221DFE6 - 2 ; case 0
	.short _0221E02A - _0221DFE6 - 2 ; case 1
	.short _0221E048 - _0221DFE6 - 2 ; case 2
	.short _0221E05E - _0221DFE6 - 2 ; case 3
	.short _0221E098 - _0221DFE6 - 2 ; case 4
_0221DFF0:
	ldr r0, [r4, #8]
	bl MOD08_02214540
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	ldr r0, _0221E0C8 ; =0x00007FFF
	mov r1, #1
	str r0, [sp, #8]
	lsl r2, r2, #0x10
	ldr r0, [r4, #4]
	lsr r2, r2, #0x10
	sub r3, r1, #3
	bl FUN_02003210
	mov r1, #0
	str r1, [sp]
	ldr r0, [r4, #0x10]
	mov r2, #0x10
	add r3, r1, #0
	bl FUN_02007E68
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, pc}
_0221E02A:
	ldr r0, [r4, #4]
	bl FUN_020038E4
	cmp r0, #0
	bne _0221E0C4
	ldr r0, [r4, #0x10]
	bl FUN_02007F20
	cmp r0, #0
	bne _0221E0C4
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, pc}
_0221E048:
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	ldrb r0, [r4, #1]
	cmp r0, #5
	bls _0221E0C4
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, pc}
_0221E05E:
	ldr r0, [r4, #8]
	bl MOD08_02214540
	add r2, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0221E0C8 ; =0x00007FFF
	mov r1, #1
	str r0, [sp, #8]
	lsl r2, r2, #0x10
	ldr r0, [r4, #4]
	lsr r2, r2, #0x10
	sub r3, r1, #3
	bl FUN_02003210
	mov r2, #0
	str r2, [sp]
	ldr r0, [r4, #0x10]
	mov r1, #0x10
	add r3, r2, #0
	bl FUN_02007E68
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, pc}
_0221E098:
	ldr r0, [r4, #4]
	bl FUN_020038E4
	cmp r0, #0
	bne _0221E0C4
	ldr r0, [r4, #0x10]
	bl FUN_02007F20
	cmp r0, #0
	bne _0221E0C4
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, pc}
_0221E0B6:
	ldr r0, [r4, #8]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_0221E0C4:
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_0221E0C8: .word 0x00007FFF

	thumb_func_start MOD08_0221E0CC
MOD08_0221E0CC: ; 0x0221E0CC
	push {r3, r4, r5, lr}
	mov r1, #0x14
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4, #8]
	add r0, r5, #0
	bl MOD08_02215504
	str r0, [r4, #4]
	ldr r0, [r4, #8]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #8]
	bl MOD08_022154D4
	str r0, [r4, #0x10]
	ldr r0, [r4, #8]
	ldr r1, _0221E100 ; =MOD08_0221DFCC
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, pc}
	nop
_0221E100: .word MOD08_0221DFCC

	thumb_func_start MOD08_0221E104
MOD08_0221E104: ; 0x0221E104
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _0221E118
	cmp r0, #1
	beq _0221E184
	b _0221E1F8
_0221E118:
	ldrb r1, [r4, #1]
	ldr r2, _0221E20C ; =0x0222C55A
	ldr r5, _0221E210 ; =0x0222C55B
	lsl r0, r1, #2
	add r3, r1, r0
	ldr r0, _0221E214 ; =0x0222C55C
	ldr r1, _0221E218 ; =0x0222C559
	ldrb r0, [r0, r3]
	ldrb r1, [r1, r3]
	ldrb r2, [r2, r3]
	str r0, [sp]
	mov r0, #0x64
	str r0, [sp, #4]
	ldr r0, _0221E21C ; =0x0222C55D
	ldrb r0, [r0, r3]
	ldrb r3, [r5, r3]
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_022181A8
	ldrb r1, [r4, #1]
	ldr r6, _0221E220 ; =0x0222C53C
	lsl r0, r1, #1
	add r5, r1, r0
	mov r0, #4
	ldrsh r3, [r4, r0]
	ldr r0, _0221E224 ; =0x0222C53D
	mov r1, #0
	ldrb r0, [r0, r5]
	add r2, r1, #0
	add r0, r3, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	ldr r0, _0221E228 ; =0x0222C53E
	ldrb r0, [r0, r5]
	ldrb r5, [r6, r5]
	str r0, [sp, #4]
	add r3, r3, r5
	add r0, r4, #0
	lsl r3, r3, #0x10
	add r0, #0x34
	asr r3, r3, #0x10
	bl MOD08_02217E80
	ldrb r0, [r4, #1]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #1]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0221E184:
	add r0, r4, #0
	add r0, #0x10
	mov r5, #0
	bl MOD08_02218224
	cmp r0, #0
	bne _0221E194
	add r5, r5, #1
_0221E194:
	add r0, r4, #0
	add r0, #0x34
	bl MOD08_02217ECC
	cmp r0, #0
	bne _0221E1A2
	add r5, r5, #1
_0221E1A2:
	cmp r5, #2
	blt _0221E1C8
	ldrb r0, [r4, #1]
	cmp r0, #3
	blo _0221E1C4
	ldrb r0, [r4, #2]
	add r0, r0, #1
	strb r0, [r4, #2]
	mov r0, #0
	strb r0, [r4, #1]
	ldrb r0, [r4, #2]
	cmp r0, #3
	blo _0221E1C8
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221E1C8
_0221E1C4:
	mov r0, #0
	strb r0, [r4]
_0221E1C8:
	mov r2, #0x10
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0x12
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0xd
	bl FUN_02007558
	mov r0, #0
	str r0, [sp]
	mov r1, #0x36
	mov r2, #6
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	ldr r3, [r4, #0x24]
	bl MOD08_022182DC
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0221E1F8:
	ldr r0, [r4, #8]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_0221E20C: .word MOD8_0222C55A
_0221E210: .word MOD8_0222C55B
_0221E214: .word MOD8_0222C55C
_0221E218: .word MOD8_0222C559
_0221E21C: .word MOD8_0222C55D
_0221E220: .word MOD8_0222C53C
_0221E224: .word MOD8_0222C53D
_0221E228: .word MOD8_0222C53E

	thumb_func_start MOD08_0221E22C
MOD08_0221E22C: ; 0x0221E22C
	push {r3, r4, r5, lr}
	mov r1, #0x58
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4]
	strb r0, [r4, #1]
	str r5, [r4, #8]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #8]
	bl MOD08_022154D4
	str r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #4]
	ldr r0, [r4, #8]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #8]
	bl MOD08_0221552C
	strh r0, [r4, #6]
	ldr r0, [r4, #8]
	ldr r1, _0221E274 ; =MOD08_0221E104
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221E274: .word MOD08_0221E104

	thumb_func_start MOD08_0221E278
MOD08_0221E278: ; 0x0221E278
	push {r4, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _0221E28E
	cmp r0, #1
	beq _0221E2A6
	cmp r0, #2
	beq _0221E2C6
	b _0221E308
_0221E28E:
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	ldrb r0, [r4, #1]
	cmp r0, #0xa
	blo _0221E324
	mov r0, #0
	strb r0, [r4, #1]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221E324
_0221E2A6:
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0200C644
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200C644
	ldr r0, [r4, #0x10]
	mov r1, #2
	bl FUN_0200C90C
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221E324
_0221E2C6:
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	ldrb r0, [r4, #1]
	cmp r0, #0xa
	blo _0221E324
	ldr r0, _0221E338 ; =0x0400004A
	mov r1, #0x3f
	ldrh r2, [r0]
	bic r2, r1
	mov r1, #0x1f
	orr r2, r1
	strh r2, [r0]
	ldrh r3, [r0]
	ldr r2, _0221E33C ; =0xFFFFC0FF
	lsl r1, r1, #8
	and r2, r3
	orr r1, r2
	strh r1, [r0]
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl FUN_0200C644
	mov r0, #0
	strb r0, [r4, #1]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221E324
_0221E308:
	mov r3, #1
	lsl r3, r3, #0x1a
	ldr r1, [r3]
	ldr r0, _0221E340 ; =0xFFFF1FFF
	and r0, r1
	str r0, [r3]
	ldr r0, [r4, #4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
_0221E324:
	ldr r0, [r4, #0xc]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x10]
	bl FUN_0200C5A8
	ldr r0, [r4, #8]
	bl FUN_0200BC1C
	pop {r4, pc}
	.align 2, 0
_0221E338: .word 0x0400004A
_0221E33C: .word 0xFFFFC0FF
_0221E340: .word 0xFFFF1FFF

	thumb_func_start MOD08_0221E344
MOD08_0221E344: ; 0x0221E344
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	mov r1, #0x14
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4, #4]
	add r0, r5, #0
	bl MOD08_02212504
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	mov r1, #0
	bl MOD08_022124D8
	str r0, [r4, #0xc]
	ldr r0, [r4, #4]
	mov r1, #1
	bl MOD08_022124D8
	str r0, [r4, #0x10]
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r2, [r0]
	ldr r1, _0221E41C ; =0xFFFF1FFF
	and r2, r1
	lsr r1, r0, #0xb
	orr r1, r2
	str r1, [r0]
	add r0, #0x4a
	ldrh r2, [r0]
	mov r1, #0x3f
	bic r2, r1
	mov r1, #0x1f
	orr r1, r2
	strh r1, [r0]
	ldrh r2, [r0]
	ldr r1, _0221E420 ; =0xFFFFC0FF
	and r2, r1
	mov r1, #0x12
	lsl r1, r1, #8
	orr r1, r2
	strh r1, [r0]
	ldr r0, [r4, #4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_0221550C
	add r7, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_0221551C
	str r0, [sp, #0x18]
	ldr r0, [r4, #0xc]
	ldr r0, [r0]
	bl FUN_02020354
	mov r1, #1
	bl FUN_0201E28C
	add r6, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_02215504
	str r0, [sp, #0x1c]
	add r0, r5, #0
	bl MOD08_02212014
	add r3, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r1, #0x20
	lsl r0, r6, #0x14
	str r1, [sp, #4]
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	add r1, #0xe0
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	str r1, [sp, #0x14]
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	add r2, r7, #0
	bl FUN_02003B40
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #4]
	ldr r1, _0221E424 ; =MOD08_0221E278
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221E41C: .word 0xFFFF1FFF
_0221E420: .word 0xFFFFC0FF
_0221E424: .word MOD08_0221E278

	thumb_func_start MOD08_0221E428
MOD08_0221E428: ; 0x0221E428
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bls _0221E438
	b _0221E61A
_0221E438:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221E444: ; jump table
	.short _0221E44C - _0221E444 - 2 ; case 0
	.short _0221E45E - _0221E444 - 2 ; case 1
	.short _0221E576 - _0221E444 - 2 ; case 2
	.short _0221E5AE - _0221E444 - 2 ; case 3
_0221E44C:
	ldr r0, [r4, #0xc]
	mov r1, #0xe
	mov r2, #1
	bl FUN_02007558
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221E636
_0221E45E:
	mov r0, #0
	add r6, r4, #0
	ldr r7, _0221E640 ; =0x0222C52C
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	add r5, r4, #0
	add r6, #0x20
_0221E46C:
	ldrb r0, [r5, #0x18]
	cmp r0, #0
	beq _0221E478
	cmp r0, #1
	beq _0221E4A6
	b _0221E4F4
_0221E478:
	ldrb r0, [r5, #0x19]
	add r0, r0, #1
	strb r0, [r5, #0x19]
	ldrb r1, [r5, #0x19]
	ldrb r0, [r7]
	cmp r1, r0
	blo _0221E4FA
	mov r0, #5
	str r0, [sp]
	mov r0, #0x64
	str r0, [sp, #4]
	mov r0, #5
	mov r1, #0x64
	str r0, [sp, #8]
	add r0, r6, #0
	mov r2, #5
	add r3, r1, #0
	bl MOD08_022181A8
	ldrb r0, [r5, #0x18]
	add r0, r0, #1
	strb r0, [r5, #0x18]
	b _0221E4FA
_0221E4A6:
	add r0, r6, #0
	bl MOD08_02218224
	cmp r0, #0
	bne _0221E4B8
	ldrb r0, [r5, #0x18]
	add r0, r0, #1
	strb r0, [r5, #0x18]
	b _0221E4FA
_0221E4B8:
	add r0, r6, #0
	add r1, sp, #0x28
	add r2, sp, #0x24
	bl MOD08_0221825C
	mov r0, #8
	ldrsb r0, [r4, r0]
	bl _fflt
	add r1, r0, #0
	ldr r0, [sp, #0x28]
	bl _fmul
	add r1, r0, #0
	ldr r0, [r5, #0x1c]
	ldr r2, [sp, #0x24]
	bl FUN_0200C884
	mov r0, #0
	str r0, [sp]
	mov r1, #2
	ldr r2, [r4, #4]
	ldrsh r1, [r4, r1]
	lsl r2, r2, #0x10
	ldr r0, [r5, #0x1c]
	ldr r3, [r5, #0x34]
	asr r2, r2, #0x10
	bl MOD08_02218314
	b _0221E4FA
_0221E4F4:
	ldr r0, [sp, #0x10]
	add r0, r0, #1
	str r0, [sp, #0x10]
_0221E4FA:
	ldr r0, [r5, #0x1c]
	bl FUN_0200C5A8
	ldr r0, [sp, #0x14]
	add r5, #0x2c
	add r0, r0, #1
	add r7, r7, #1
	add r6, #0x2c
	str r0, [sp, #0x14]
	cmp r0, #3
	blt _0221E46C
	ldr r0, [sp, #0x10]
	cmp r0, #3
	bge _0221E518
	b _0221E636
_0221E518:
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	ldrb r0, [r4, #1]
	cmp r0, #3
	bhs _0221E56E
	mov r6, #0
	add r5, r4, #0
	add r7, r6, #0
_0221E52A:
	add r1, sp, #0x18
	ldr r0, [r5, #0x1c]
	add r1, #2
	add r2, sp, #0x18
	bl FUN_0200C7A0
	add r2, sp, #0x18
	mov r1, #2
	ldrsh r1, [r2, r1]
	mov r2, #2
	ldrsh r2, [r4, r2]
	ldr r0, [r5, #0x1c]
	bl FUN_0200C714
	mov r0, #8
	ldrsb r0, [r4, r0]
	bl _fflt
	add r1, r0, #0
	mov r2, #0xfe
	ldr r0, [r5, #0x1c]
	lsl r2, r2, #0x16
	bl FUN_0200C884
	strb r7, [r5, #0x18]
	strb r7, [r5, #0x19]
	add r6, r6, #1
	add r5, #0x2c
	cmp r6, #3
	blt _0221E52A
	ldrb r0, [r4]
	sub r0, r0, #1
	strb r0, [r4]
	b _0221E636
_0221E56E:
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221E636
_0221E576:
	add r5, r4, #0
	mov r7, #0
	add r6, r4, #0
	add r5, #0x20
_0221E57E:
	ldr r0, [r6, #0x1c]
	mov r1, #0
	bl FUN_0200C90C
	mov r0, #0x64
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #5
	mov r1, #5
	str r0, [sp, #8]
	add r0, r5, #0
	mov r2, #0x64
	add r3, r1, #0
	bl MOD08_022181A8
	add r7, r7, #1
	add r6, #0x2c
	add r5, #0x2c
	cmp r7, #3
	blt _0221E57E
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221E636
_0221E5AE:
	mov r7, #0
	add r6, r4, #0
	str r7, [sp, #0xc]
	add r6, #0x20
	add r5, r4, #0
_0221E5B8:
	add r0, r6, #0
	bl MOD08_02218224
	cmp r0, #0
	bne _0221E5C6
	add r7, r7, #1
	b _0221E600
_0221E5C6:
	add r0, r6, #0
	add r1, sp, #0x20
	add r2, sp, #0x1c
	bl MOD08_0221825C
	mov r0, #8
	ldrsb r0, [r4, r0]
	bl _fflt
	add r1, r0, #0
	ldr r0, [sp, #0x20]
	bl _fmul
	add r1, r0, #0
	ldr r0, [r5, #0x1c]
	ldr r2, [sp, #0x1c]
	bl FUN_0200C884
	mov r0, #0
	str r0, [sp]
	mov r1, #2
	ldr r2, [r4, #4]
	ldrsh r1, [r4, r1]
	lsl r2, r2, #0x10
	ldr r0, [r5, #0x1c]
	ldr r3, [r5, #0x34]
	asr r2, r2, #0x10
	bl MOD08_02218314
_0221E600:
	ldr r0, [sp, #0xc]
	add r6, #0x2c
	add r0, r0, #1
	add r5, #0x2c
	str r0, [sp, #0xc]
	cmp r0, #3
	blt _0221E5B8
	cmp r7, #3
	blt _0221E636
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221E636
_0221E61A:
	ldr r0, [r4, #0xc]
	mov r1, #0xe
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4, #0x10]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
_0221E636:
	ldr r0, [r4, #0x14]
	bl FUN_0200BC1C
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0221E640: .word MOD8_0222C52C

	thumb_func_start MOD08_0221E644
MOD08_0221E644: ; 0x0221E644
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0x9c
	str r0, [sp]
	bl MOD08_02228064
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4]
	strb r0, [r4, #1]
	ldr r0, [sp]
	str r0, [r4, #0x10]
	bl MOD08_02212504
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x10]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #0x10]
	bl MOD08_022154D4
	str r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #2]
	ldr r0, [r4, #0xc]
	mov r1, #0x29
	bl FUN_0200782C
	mov r1, #2
	ldrsh r1, [r4, r1]
	sub r0, r1, r0
	strh r0, [r4, #2]
	ldr r0, [r4, #0x10]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #0x10]
	bl MOD08_0221552C
	mov r1, #0
	str r0, [r4, #4]
	mvn r1, r1
	ldr r0, [r4, #0x10]
	add r2, r1, #0
	bl MOD08_02227994
	mov r6, #0
	ldr r1, _0221E720 ; =0x0000060C
	ldr r0, _0221E724 ; =0x04000052
	add r5, r4, #0
	strh r1, [r0]
	add r7, r6, #0
_0221E6B0:
	strb r7, [r5, #0x18]
	strb r7, [r5, #0x19]
	ldr r0, [r4, #0x10]
	add r1, r6, #0
	bl MOD08_022124D8
	str r0, [r5, #0x1c]
	mov r1, #2
	bl FUN_0200C840
	ldr r0, [r5, #0x1c]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r5, #0x1c]
	add r1, r6, #1
	bl FUN_0200C6C4
	add r6, r6, #1
	add r5, #0x2c
	cmp r6, #3
	blt _0221E6B0
	ldr r0, [sp]
	mov r1, #0
	bl MOD08_02215680
	cmp r0, #1
	bne _0221E6EE
	mov r0, #0
	mvn r0, r0
	b _0221E6F0
_0221E6EE:
	mov r0, #1
_0221E6F0:
	strb r0, [r4, #8]
	mov r6, #0
	add r5, r4, #0
	mov r7, #8
_0221E6F8:
	ldrsb r0, [r4, r7]
	bl _fflt
	add r1, r0, #0
	mov r2, #0xfe
	ldr r0, [r5, #0x1c]
	lsl r2, r2, #0x16
	bl FUN_0200C884
	add r6, r6, #1
	add r5, #0x2c
	cmp r6, #3
	blt _0221E6F8
	ldr r0, [r4, #0x10]
	ldr r1, _0221E728 ; =MOD08_0221E428
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221E720: .word 0x0000060C
_0221E724: .word 0x04000052
_0221E728: .word MOD08_0221E428

	thumb_func_start MOD08_0221E72C
MOD08_0221E72C: ; 0x0221E72C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bls _0221E73C
	b _0221E866
_0221E73C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221E748: ; jump table
	.short _0221E750 - _0221E748 - 2 ; case 0
	.short _0221E782 - _0221E748 - 2 ; case 1
	.short _0221E796 - _0221E748 - 2 ; case 2
	.short _0221E7F2 - _0221E748 - 2 ; case 3
_0221E750:
	ldr r0, [r4, #0xc]
	bl MOD08_02215504
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	bl MOD08_02214540
	add r2, r0, #0
	mov r1, #0
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r1, #1
	add r0, r5, #0
	lsr r2, r2, #0x10
	add r3, r1, #0
	bl FUN_02003210
	ldrb r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0221E782:
	ldr r0, [r4, #0xc]
	bl MOD08_02215504
	bl FUN_020038E4
	cmp r0, #0
	bne _0221E874
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221E796:
	mov r0, #5
	str r0, [sp]
	ldrb r1, [r4, #1]
	add r0, r4, #0
	add r0, #0xb4
	lsl r2, r1, #1
	ldr r1, _0221E878 ; =0x0222C586
	ldrsh r1, [r1, r2]
	mov r2, #0
	add r3, r2, #0
	bl MOD08_022183C0
	ldrb r0, [r4, #2]
	cmp r0, #0
	ldr r0, [r4, #0xc]
	bne _0221E7C8
	bl MOD08_02215504
	mov r1, #0
	mov r2, #0xff
	mov r3, #0xa
	str r1, [sp]
	bl FUN_02003A64
	b _0221E7DA
_0221E7C8:
	bl MOD08_02215504
	ldr r1, _0221E87C ; =0x00007FFF
	mov r2, #0xff
	str r1, [sp]
	mov r1, #0
	mov r3, #0xa
	bl FUN_02003A64
_0221E7DA:
	mov r0, #3
	strb r0, [r4, #3]
	ldrb r1, [r4, #2]
	mov r0, #1
	eor r0, r1
	strb r0, [r4, #2]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221E7F2:
	add r0, r4, #0
	add r0, #0xb4
	bl MOD08_022183F0
	cmp r0, #0
	bne _0221E810
	ldrb r0, [r4, #1]
	cmp r0, #8
	ldrb r0, [r4]
	blo _0221E80C
	add r0, r0, #1
	strb r0, [r4]
	b _0221E810
_0221E80C:
	sub r0, r0, #1
	strb r0, [r4]
_0221E810:
	ldrb r0, [r4, #3]
	cmp r0, #0
	beq _0221E832
	sub r0, r0, #1
	strb r0, [r4, #3]
	ldrb r0, [r4, #3]
	cmp r0, #0
	bne _0221E832
	ldr r0, [r4, #0xc]
	bl MOD08_02215504
	mov r1, #0
	mov r2, #0xff
	add r3, r1, #0
	str r1, [sp]
	bl FUN_02003A64
_0221E832:
	mov r6, #0
	add r5, r4, #0
	mov r7, #0x14
_0221E838:
	ldr r0, [r5, #0x1c]
	cmp r0, #0
	beq _0221E84C
	mov r2, #0xb4
	ldrsh r3, [r4, r2]
	ldrsh r2, [r5, r7]
	mov r1, #0
	add r2, r3, r2
	bl FUN_02007558
_0221E84C:
	add r6, r6, #1
	add r5, #0x14
	cmp r6, #4
	blt _0221E838
	mov r3, #0xb4
	ldrsh r3, [r4, r3]
	ldr r0, [r4, #8]
	mov r1, #3
	mov r2, #0
	bl FUN_020179E0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0221E866:
	ldr r0, [r4, #0xc]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_0221E874:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0221E878: .word MOD8_0222C586
_0221E87C: .word 0x00007FFF

	thumb_func_start MOD08_0221E880
MOD08_0221E880: ; 0x0221E880
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0xd8
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4]
	strb r0, [r4, #1]
	str r5, [r4, #0xc]
	add r0, r5, #0
	bl MOD08_02212504
	str r0, [r4, #0x10]
	ldr r0, [r4, #0xc]
	bl MOD08_02212490
	str r0, [r4, #8]
	ldr r0, [r4, #0xc]
	bl MOD08_0221553C
	cmp r0, #1
	bne _0221E8B2
	mov r1, #0x40
	b _0221E8B4
_0221E8B2:
	mov r1, #0xa
_0221E8B4:
	add r2, r4, #0
	add r0, r5, #0
	add r2, #0x14
	add r3, r4, #4
	bl MOD08_02227BAC
	ldr r0, [r4, #4]
	mov r6, #0
	cmp r0, #0
	ble _0221E8EA
	add r5, r4, #0
	add r7, r6, #0
_0221E8CC:
	ldr r0, [r5, #0x1c]
	add r1, r7, #0
	bl FUN_0200782C
	strh r0, [r5, #0x14]
	ldr r0, [r5, #0x1c]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r5, #0x16]
	ldr r0, [r4, #4]
	add r6, r6, #1
	add r5, #0x14
	cmp r6, r0
	blt _0221E8CC
_0221E8EA:
	ldr r0, [r4, #0xc]
	ldr r1, _0221E8F8 ; =MOD08_0221E72C
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221E8F8: .word MOD08_0221E72C

	thumb_func_start MOD08_0221E8FC
MOD08_0221E8FC: ; 0x0221E8FC
	push {r4, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	bne _0221E946
	add r0, r4, #0
	add r0, #0x40
	bl MOD08_02217ECC
	cmp r0, #0
	bne _0221E91A
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221E91A:
	add r0, r4, #0
	add r0, #0x1c
	bl MOD08_022183F0
	add r0, r4, #0
	add r0, #0x64
	bl MOD08_02218704
	mov r1, #0x40
	mov r2, #0x42
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x18]
	bl FUN_0200C714
	ldr r0, [r4, #0x18]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x10]
	bl FUN_0200BC1C
	pop {r4, pc}
_0221E946:
	ldr r0, [r4, #0xc]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_0221E958
MOD08_0221E958: ; 0x0221E958
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r1, #0x8c
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4]
	strb r0, [r4, #1]
	str r5, [r4, #0xc]
	add r0, r5, #0
	bl MOD08_02212504
	str r0, [r4, #0x10]
	ldr r0, [r4, #0xc]
	bl MOD08_02212490
	str r0, [r4, #8]
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl MOD08_022124D8
	str r0, [r4, #0x18]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	cmp r0, #0
	ldr r0, [r4, #0xc]
	bne _0221E99C
	bl MOD08_02212460
	b _0221E9A0
_0221E99C:
	bl MOD08_02212458
_0221E9A0:
	add r6, r0, #0
	ldr r0, [r4, #0xc]
	add r1, r6, #0
	bl MOD08_022154D4
	str r0, [r4, #0x14]
	add r1, r4, #4
	bl MOD08_02227B2C
	ldr r0, [r4, #0x14]
	mov r1, #0x29
	bl FUN_0200782C
	mov r1, #6
	ldrsh r1, [r4, r1]
	sub r0, r1, r0
	strh r0, [r4, #6]
	ldr r0, [r4, #0xc]
	add r1, r6, #0
	bl MOD08_02217C1C
	add r7, r0, #0
	ldr r0, [r4, #0xc]
	add r1, r6, #0
	bl MOD08_02217C44
	add r6, r0, #0
	mov r0, #6
	ldrsh r3, [r4, r0]
	mov r0, #4
	ldrsh r1, [r4, r0]
	mov r2, #0x14
	add r0, r6, #0
	mul r0, r2
	add r0, r3, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	str r2, [sp, #4]
	sub r2, #0x28
	mul r2, r7
	add r2, r1, r2
	add r0, r4, #0
	lsl r2, r2, #0x10
	add r0, #0x40
	asr r2, r2, #0x10
	bl MOD08_02217E80
	add r0, r5, #0
	mov r1, #2
	bl MOD08_022155C4
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl MOD08_022155C4
	mov r5, #1
	add r3, r5, #0
	lsl r3, r6
	add r1, r0, #0
	add r6, r3, #0
	mov r2, #0x20
	add r3, r5, #0
	orr r6, r2
	lsl r3, r1
	add r1, r6, #0
	orr r1, r3
	sub r2, #0x21
	ldr r0, [r4, #0xc]
	orr r1, r5
	add r3, r2, #0
	bl MOD08_022279D0
	mov r1, #0x1f
	mov r2, #0
	str r1, [sp]
	mov r0, #0xf
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x64
	add r3, r2, #0
	bl MOD08_022186D4
	ldr r0, [r4, #0x18]
	add r1, r5, #0
	bl FUN_0200C90C
	ldr r0, [r4, #0xc]
	ldr r1, _0221EA60 ; =MOD08_0221E8FC
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221EA60: .word MOD08_0221E8FC

	thumb_func_start MOD08_0221EA64
MOD08_0221EA64: ; 0x0221EA64
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _0221EA76
	cmp r0, #1
	beq _0221EAB6
	b _0221EAE6
_0221EA76:
	ldrb r0, [r4, #1]
	cmp r0, #0
	ldrb r0, [r4, #2]
	bne _0221EA88
	lsl r3, r0, #3
	ldr r0, _0221EB00 ; =0x0222C5B0
	ldr r2, [r0, r3]
	neg r1, r2
	b _0221EA90
_0221EA88:
	lsl r3, r0, #3
	ldr r0, _0221EB00 ; =0x0222C5B0
	ldr r1, [r0, r3]
	neg r2, r1
_0221EA90:
	ldr r5, _0221EB04 ; =0x0222C5B4
	add r0, r4, #0
	ldr r3, [r5, r3]
	add r0, #0x5c
	bl MOD08_02218008
	ldrb r0, [r4, #1]
	cmp r0, #1
	bne _0221EAA8
	ldrb r0, [r4, #2]
	add r0, r0, #1
	strb r0, [r4, #2]
_0221EAA8:
	ldrb r1, [r4, #1]
	mov r0, #1
	eor r0, r1
	strb r0, [r4, #1]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221EAB6:
	add r0, r4, #0
	add r0, #0x5c
	bl MOD08_02218058
	cmp r0, #1
	bne _0221EAD2
	ldr r2, [r4, #0x5c]
	ldr r0, [r4, #0x28]
	lsl r2, r2, #0x10
	mov r1, #9
	lsr r2, r2, #0x10
	bl FUN_02007558
	pop {r3, r4, r5, pc}
_0221EAD2:
	ldrb r0, [r4, #2]
	cmp r0, #5
	ldrb r0, [r4]
	blo _0221EAE0
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_0221EAE0:
	sub r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_0221EAE6:
	ldr r0, [r4, #0x28]
	mov r1, #9
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4, #4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221EB00: .word MOD8_0222C5B0
_0221EB04: .word MOD8_0222C5B4

	thumb_func_start MOD08_0221EB08
MOD08_0221EB08: ; 0x0221EB08
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _0221EB1C
	cmp r0, #1
	beq _0221EB40
	b _0221EB6A
_0221EB1C:
	mov r0, #0x22
	ldrsh r0, [r4, r0]
	mov r1, #0x1c
	mov r2, #0x1e
	str r0, [sp]
	mov r3, #0x20
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	add r0, #0x38
	bl MOD08_022183C0
	ldrb r0, [r4]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, pc}
_0221EB40:
	ldr r0, [r4, #0x2c]
	add r1, sp, #4
	bl MOD08_02227B2C
	add r0, r4, #0
	add r3, sp, #4
	mov r1, #0
	mov r2, #2
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldr r3, [r4, #0x2c]
	add r0, #0x38
	bl MOD08_02218454
	cmp r0, #0
	bne _0221EB78
	ldrb r0, [r4]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, pc}
_0221EB6A:
	ldr r0, [r4, #4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_0221EB78:
	add sp, #8
	pop {r4, pc}

	thumb_func_start MOD08_0221EB7C
MOD08_0221EB7C: ; 0x0221EB7C
	push {r4, r5, r6, lr}
	mov r1, #0x70
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02227B70
	ldr r0, [r4, #4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_022154D4
	str r0, [r4, #0x28]
	ldr r0, [r4, #4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_022154D4
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x28]
	mov r1, #0xb
	mov r2, #0x64
	bl FUN_02007558
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	strh r0, [r4, #0x1c]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_02212498
	strh r0, [r4, #0x1e]
	add r0, r5, #0
	mov r1, #3
	bl MOD08_02212498
	strh r0, [r4, #0x20]
	add r0, r5, #0
	mov r1, #4
	bl MOD08_02212498
	strh r0, [r4, #0x22]
	add r0, r5, #0
	mov r1, #5
	bl MOD08_02212498
	str r0, [r4, #0x24]
	cmp r6, #0
	ldr r0, [r4, #4]
	bne _0221EC06
	ldr r1, _0221EC10 ; =MOD08_0221EA64
	add r2, r4, #0
	bl MOD08_02212400
	pop {r4, r5, r6, pc}
_0221EC06:
	ldr r1, _0221EC14 ; =MOD08_0221EB08
	add r2, r4, #0
	bl MOD08_02212400
	pop {r4, r5, r6, pc}
	.align 2, 0
_0221EC10: .word MOD08_0221EA64
_0221EC14: .word MOD08_0221EB08

	thumb_func_start MOD08_0221EC18
MOD08_0221EC18: ; 0x0221EC18
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r2, r0, #0
	ldrb r0, [r5]
	cmp r0, #0
	beq _0221EC2A
	cmp r0, #1
	beq _0221EC4C
	b _0221ECA0
_0221EC2A:
	ldr r2, [r5, #0x48]
	mov r0, #0xa
	add r1, r2, #2
	str r0, [sp]
	add r0, r5, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, #0x4c
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	mov r3, #0
	bl MOD08_022183C0
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_0221EC4C:
	add r0, r5, #0
	add r0, #0x4c
	bl MOD08_022183F0
	cmp r0, #0
	bne _0221EC60
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_0221EC60:
	mov r6, #0
	add r4, r5, #0
	mov r7, #0x28
_0221EC66:
	ldr r0, [r4, #0x38]
	cmp r0, #0
	beq _0221EC7A
	mov r2, #0x4c
	ldrsh r3, [r5, r2]
	ldrsh r2, [r4, r7]
	mov r1, #0
	add r2, r3, r2
	bl FUN_02007558
_0221EC7A:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _0221EC66
	mov r3, #0x4c
	ldrsh r3, [r5, r3]
	ldr r0, [r5, #0x14]
	mov r1, #3
	mov r2, #0
	bl FUN_020179E0
	mov r3, #0x4e
	mov r1, #3
	ldrsh r3, [r5, r3]
	ldr r0, [r5, #0x14]
	add r2, r1, #0
	bl FUN_020179E0
	pop {r3, r4, r5, r6, r7, pc}
_0221ECA0:
	ldr r0, [r5, #4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r5, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_0221ECB0
MOD08_0221ECB0: ; 0x0221ECB0
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0x70
	add r4, r0, #0
	bl MOD08_02228064
	add r7, r0, #0
	add r0, r4, #0
	add r1, r7, #0
	bl MOD08_02227B70
	ldr r0, [r7, #4]
	mov r1, #1
	bl MOD08_02212758
	cmp r0, #0x46
	bgt _0221ECE0
	bge _0221ED02
	cmp r0, #0x1e
	bgt _0221ECDA
	beq _0221ED0E
	b _0221ED14
_0221ECDA:
	cmp r0, #0x32
	beq _0221ED08
	b _0221ED14
_0221ECE0:
	cmp r0, #0x6e
	bgt _0221ECEC
	bge _0221ECF6
	cmp r0, #0x5a
	beq _0221ECFC
	b _0221ED14
_0221ECEC:
	cmp r0, #0x96
	bne _0221ED14
	mov r0, #6
	str r0, [r7, #0x48]
	b _0221ED18
_0221ECF6:
	mov r0, #5
	str r0, [r7, #0x48]
	b _0221ED18
_0221ECFC:
	mov r0, #4
	str r0, [r7, #0x48]
	b _0221ED18
_0221ED02:
	mov r0, #3
	str r0, [r7, #0x48]
	b _0221ED18
_0221ED08:
	mov r0, #2
	str r0, [r7, #0x48]
	b _0221ED18
_0221ED0E:
	mov r0, #1
	str r0, [r7, #0x48]
	b _0221ED18
_0221ED14:
	mov r0, #0
	str r0, [r7, #0x48]
_0221ED18:
	add r5, r7, #0
	mov r6, #0
	add r4, r7, #0
	add r5, #0x28
_0221ED20:
	ldr r0, [r7, #4]
	add r1, r6, #0
	bl MOD08_022154D4
	str r0, [r4, #0x38]
	cmp r0, #0
	beq _0221ED34
	add r1, r5, #0
	bl MOD08_02227B2C
_0221ED34:
	add r6, r6, #1
	add r4, r4, #4
	add r5, r5, #4
	cmp r6, #4
	blt _0221ED20
	ldr r0, [r7, #4]
	ldr r1, _0221ED4C ; =MOD08_0221EC18
	add r2, r7, #0
	bl MOD08_02212400
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221ED4C: .word MOD08_0221EC18

	thumb_func_start MOD08_0221ED50
MOD08_0221ED50: ; 0x0221ED50
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _0221ED64
	cmp r0, #1
	beq _0221ED92
	b _0221EE00
_0221ED64:
	mov r0, #0xa
	str r0, [sp]
	add r0, r4, #0
	mov r2, #0
	add r0, #0x40
	mov r1, #0x14
	add r3, r2, #0
	bl MOD08_022183C0
	mov r0, #0xa
	str r0, [sp]
	add r0, r4, #0
	mov r2, #0
	add r0, #0x64
	mov r1, #2
	add r3, r2, #0
	bl MOD08_022183C0
	ldrb r0, [r4]
	add sp, #4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, pc}
_0221ED92:
	add r0, r4, #0
	add r0, #0x40
	bl MOD08_022183F0
	cmp r0, #0
	bne _0221EDA6
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221EDF6
_0221EDA6:
	mov r1, #0x2c
	ldrsh r2, [r4, r1]
	mov r1, #0x40
	ldrsh r1, [r4, r1]
	ldr r0, [r4, #0x38]
	add r1, r2, r1
	mov r2, #0x2e
	ldrsh r3, [r4, r2]
	mov r2, #0x42
	ldrsh r2, [r4, r2]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add r2, r3, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	mov r1, #0x40
	ldrsh r2, [r4, r1]
	mov r1, #0x2c
	ldrsh r1, [r4, r1]
	ldr r0, [r4, #0x3c]
	sub r1, r2, r1
	mov r2, #0x2e
	ldrsh r3, [r4, r2]
	mov r2, #0x42
	ldrsh r2, [r4, r2]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add r2, r3, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	ldr r0, [r4, #0x38]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x3c]
	bl FUN_0200C5A8
_0221EDF6:
	ldr r0, [r4, #0xc]
	bl FUN_0200BC1C
	add sp, #4
	pop {r3, r4, pc}
_0221EE00:
	ldr r0, [r4, #4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD08_0221EE14
MOD08_0221EE14: ; 0x0221EE14
	push {r3, r4, r5, lr}
	mov r1, #0x88
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02227B70
	ldr r0, [r4, #4]
	mov r1, #0
	bl MOD08_022124D8
	str r0, [r4, #0x38]
	ldr r0, [r4, #4]
	mov r1, #1
	bl MOD08_022124D8
	str r0, [r4, #0x3c]
	ldr r0, [r4, #4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_022154D4
	str r0, [r4, #0x30]
	ldr r0, [r4, #4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_022154D4
	str r0, [r4, #0x34]
	add r1, r4, #0
	ldr r0, [r4, #0x30]
	add r1, #0x28
	bl MOD08_02227B2C
	add r1, r4, #0
	ldr r0, [r4, #0x34]
	add r1, #0x2c
	bl MOD08_02227B2C
	ldr r0, [r4, #4]
	ldr r1, _0221EE7C ; =MOD08_0221ED50
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221EE7C: .word MOD08_0221ED50

	thumb_func_start MOD08_0221EE80
MOD08_0221EE80: ; 0x0221EE80
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	ldr r2, [r4, #0x38]
	add r0, #0x8c
	add r1, #0xb0
	bl MOD08_02217FE4
	cmp r0, #0
	bne _0221EEAC
	ldr r0, [r4, #0x38]
	bl FUN_0200C3DC
	ldr r0, [r4, #0x14]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl MOD08_02228094
	pop {r3, r4, r5, pc}
_0221EEAC:
	add r0, r4, #0
	add r0, #0xd4
	bl MOD08_02218058
	cmp r0, #1
	bne _0221EEC8
	add r1, r4, #0
	add r1, #0xd4
	ldr r1, [r1]
	ldr r0, [r4, #0x38]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_0200C898
_0221EEC8:
	ldr r0, [r4, #0x38]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x20]
	bl FUN_0200BC1C
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_0221EED8
MOD08_0221EED8: ; 0x0221EED8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r1, #0xe8
	add r6, r0, #0
	add r7, r3, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x10
	bl MOD08_02227B70
	add r0, r6, #0
	mov r1, #0
	bl MOD08_02212498
	strh r0, [r4, #0xc]
	add r0, r6, #0
	mov r1, #1
	bl MOD08_02212498
	strh r0, [r4, #0xe]
	add r0, r6, #0
	mov r1, #2
	bl MOD08_02212498
	str r0, [r4, #4]
	add r0, r6, #0
	mov r1, #3
	bl MOD08_02212498
	str r0, [r4, #8]
	add r0, r6, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_02217C1C
	add r5, r0, #0
	add r0, r7, #0
	mov r1, #2
	str r7, [r4, #0x38]
	bl FUN_0200C840
	add r0, r6, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_022154D4
	str r0, [r4, #0x44]
	add r0, r6, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_022154D4
	str r0, [r4, #0x58]
	add r1, r4, #0
	ldr r0, [r4, #0x44]
	add r1, #0x40
	bl MOD08_02227B2C
	add r1, r4, #0
	ldr r0, [r4, #0x58]
	add r1, #0x54
	bl MOD08_02227B2C
	mov r0, #0x42
	ldrsh r0, [r4, r0]
	mov r3, #0x54
	str r0, [sp]
	mov r0, #0x56
	ldrsh r2, [r4, r0]
	mov r0, #0xe
	ldrsh r0, [r4, r0]
	add r1, r0, #0
	mul r1, r5
	add r0, r2, r1
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #4]
	ldr r0, [r4, #4]
	add r1, r4, #0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	ldr r0, [r4, #8]
	mov r2, #0x40
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	ldrsh r3, [r4, r3]
	add r0, r4, #0
	ldrsh r2, [r4, r2]
	mov ip, r3
	mov r3, #0xc
	ldrsh r3, [r4, r3]
	add r0, #0x8c
	add r1, #0xb0
	add r7, r3, #0
	mul r7, r5
	mov r3, ip
	add r3, r3, r7
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	bl MOD08_02217F50
	add r0, r6, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_02215490
	cmp r0, #4
	bne _0221EFE0
	add r0, r6, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_02215490
	cmp r0, #2
	bne _0221EFE0
	mov r0, #0
	mvn r0, r0
	mul r5, r0
_0221EFE0:
	add r0, r6, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_02215490
	cmp r0, #5
	bne _0221F00A
	add r0, r6, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_02215490
	cmp r0, #3
	bne _0221F00A
	mov r0, #0
	mvn r0, r0
	mul r5, r0
_0221F00A:
	cmp r5, #0
	ldr r2, _0221F064 ; =0x00005C71
	ble _0221F022
	ldr r1, _0221F068 ; =0x00000E38
	add r0, r4, #0
	add r0, #0xd4
	mul r1, r5
	mul r2, r5
	mov r3, #0xa
	bl MOD08_02218008
	b _0221F032
_0221F022:
	ldr r1, _0221F06C ; =0x00003FFF
	add r0, r4, #0
	add r0, #0xd4
	mul r1, r5
	mul r2, r5
	mov r3, #0xa
	bl MOD08_02218008
_0221F032:
	add r1, r4, #0
	add r1, #0xd4
	ldr r1, [r1]
	ldr r0, [r4, #0x38]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_0200C898
	add r0, r4, #0
	add r1, r4, #0
	ldr r2, [r4, #0x38]
	add r0, #0x8c
	add r1, #0xb0
	bl MOD08_02217FE4
	ldr r0, [r4, #0x38]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x14]
	ldr r1, _0221F070 ; =MOD08_0221EE80
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0221F064: .word 0x00005C71
_0221F068: .word 0x00000E38
_0221F06C: .word 0x00003FFF
_0221F070: .word MOD08_0221EE80

	thumb_func_start MOD08_0221F074
MOD08_0221F074: ; 0x0221F074
	push {r4, r5, lr}
	sub sp, #0x1c
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x18]
	cmp r0, #3
	bls _0221F084
	b _0221F1F0
_0221F084:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221F090: ; jump table
	.short _0221F098 - _0221F090 - 2 ; case 0
	.short _0221F0C8 - _0221F090 - 2 ; case 1
	.short _0221F168 - _0221F090 - 2 ; case 2
	.short _0221F17A - _0221F090 - 2 ; case 3
_0221F098:
	mov r0, #0x12
	ldrsh r2, [r4, r0]
	mov r0, #0x96
	mov r3, #0x3c
	str r0, [sp]
	mov r1, #0x64
	str r1, [sp, #4]
	mov r0, #0xc
	mul r1, r2
	mul r3, r2
	lsl r2, r3, #0x10
	str r0, [sp, #8]
	add r0, r4, #0
	lsl r1, r1, #0x10
	add r0, #0x9c
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	mov r3, #5
	bl MOD08_022181A8
	ldrb r0, [r4, #0x18]
	add r0, r0, #1
	strb r0, [r4, #0x18]
	b _0221F20E
_0221F0C8:
	add r0, r4, #0
	add r0, #0x9c
	bl MOD08_02218224
	cmp r0, #0
	bne _0221F106
	mov r0, #0x12
	ldrsh r2, [r4, r0]
	mov r0, #0xa
	mov r1, #0x3c
	str r0, [sp]
	mov r0, #0x64
	str r0, [sp, #4]
	mov r0, #0xc
	mul r1, r2
	str r0, [sp, #8]
	add r0, r4, #0
	lsl r1, r1, #0x10
	mov r3, #0x96
	add r5, r2, #0
	mul r5, r3
	lsl r2, r5, #0x10
	add r0, #0x9c
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl MOD08_022181A8
	ldrb r0, [r4, #0x18]
	add r0, r0, #1
	strb r0, [r4, #0x18]
	b _0221F20E
_0221F106:
	add r0, r4, #0
	add r0, #0x9c
	add r1, sp, #0x18
	add r2, sp, #0x14
	bl MOD08_0221825C
	ldr r0, [r4, #0x40]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	bl FUN_0200C884
	mov r0, #0x16
	add r2, r4, #0
	add r2, #0xb0
	ldrsh r0, [r4, r0]
	ldr r2, [r2]
	mov r1, #0x10
	bl MOD08_0221828C
	mov r2, #0x16
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	mov r1, #0x14
	ldrsh r1, [r4, r1]
	add r2, r2, r3
	lsl r2, r2, #0x10
	ldr r0, [r4, #0x40]
	asr r2, r2, #0x10
	bl FUN_0200C714
	ldrb r1, [r4, #0xc]
	ldrb r0, [r4, #0x10]
	cmp r1, r0
	bhs _0221F14E
	add r0, r1, #1
	strb r0, [r4, #0xc]
_0221F14E:
	ldrb r1, [r4, #0xd]
	ldrb r0, [r4, #0x11]
	cmp r1, r0
	bls _0221F15A
	sub r0, r1, #1
	strb r0, [r4, #0xd]
_0221F15A:
	ldrb r0, [r4, #0xd]
	ldrb r1, [r4, #0xc]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0221F220 ; =0x04000052
	strh r1, [r0]
	b _0221F20E
_0221F168:
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	cmp r0, #4
	blt _0221F20E
	ldrb r0, [r4, #0x18]
	add r0, r0, #1
	strb r0, [r4, #0x18]
	b _0221F20E
_0221F17A:
	add r0, r4, #0
	add r0, #0x9c
	bl MOD08_02218224
	cmp r0, #0
	bne _0221F18E
	ldrb r0, [r4, #0x18]
	add r0, r0, #1
	strb r0, [r4, #0x18]
	b _0221F20E
_0221F18E:
	add r0, r4, #0
	add r0, #0x9c
	add r1, sp, #0x10
	add r2, sp, #0xc
	bl MOD08_0221825C
	ldr r0, [r4, #0x40]
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0xc]
	bl FUN_0200C884
	mov r0, #0x16
	add r2, r4, #0
	add r2, #0xb0
	ldrsh r0, [r4, r0]
	ldr r2, [r2]
	mov r1, #0x10
	bl MOD08_0221828C
	mov r2, #0x16
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	mov r1, #0x14
	ldrsh r1, [r4, r1]
	add r2, r2, r3
	lsl r2, r2, #0x10
	ldr r0, [r4, #0x40]
	asr r2, r2, #0x10
	bl FUN_0200C714
	ldrb r1, [r4, #0xc]
	ldrb r0, [r4, #0xe]
	cmp r1, r0
	bls _0221F1D6
	sub r0, r1, #1
	strb r0, [r4, #0xc]
_0221F1D6:
	ldrb r1, [r4, #0xd]
	ldrb r0, [r4, #0xf]
	cmp r1, r0
	bhs _0221F1E2
	add r0, r1, #1
	strb r0, [r4, #0xd]
_0221F1E2:
	ldrb r0, [r4, #0xd]
	ldrb r1, [r4, #0xc]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0221F220 ; =0x04000052
	strh r1, [r0]
	b _0221F20E
_0221F1F0:
	ldr r0, [r4, #0x44]
	bl FUN_0200C3DC
	ldr r0, [r4, #0x48]
	bl FUN_0200C3DC
	ldr r0, [r4, #0x1c]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl MOD08_02228094
	add sp, #0x1c
	pop {r4, r5, pc}
_0221F20E:
	ldr r0, [r4, #0x40]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x28]
	bl FUN_0200BC1C
	add sp, #0x1c
	pop {r4, r5, pc}
	nop
_0221F220: .word 0x04000052

	thumb_func_start MOD08_0221F224
MOD08_0221F224: ; 0x0221F224
	push {r4, r5, lr}
	sub sp, #0x14
	mov r1, #0xd4
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x18
	bl MOD08_02227B70
	add r0, r5, #0
	mov r1, #0
	bl MOD08_022124B0
	str r0, [r4, #0x44]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_022124B0
	mov r1, #0
	str r0, [r4, #0x48]
	mvn r1, r1
	ldr r0, [r4, #0x1c]
	add r2, r1, #0
	bl MOD08_02227994
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	mov r1, #0
	strb r1, [r4, #0xc]
	mov r0, #0x1f
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	strb r0, [r4, #0xf]
	strb r0, [r4, #0x10]
	mov r0, #4
	strb r0, [r4, #0x11]
	add r0, r5, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _0221F2B4
	ldr r0, [r4, #0x44]
	mov r1, #0
	str r0, [r4, #0x40]
	ldr r0, [r4, #0x48]
	bl FUN_0200C644
	ldr r0, [r4, #0x40]
	mov r1, #0
	bl FUN_0200C5C0
	mov r0, #0xb3
	strh r0, [r4, #0x14]
	mov r0, #0x78
	strh r0, [r4, #0x16]
	add r0, r5, #0
	bl MOD08_02215574
	add r1, r0, #0
	ldr r0, [r4, #0x40]
	add r1, r1, #1
	bl FUN_0200C6B0
	mov r0, #0
	mvn r0, r0
	strh r0, [r4, #0x12]
	b _0221F314
_0221F2B4:
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_02227470
	cmp r0, #4
	bne _0221F2E4
	ldr r0, [r4, #0x48]
	mov r1, #0
	str r0, [r4, #0x40]
	ldr r0, [r4, #0x44]
	bl FUN_0200C644
	ldr r0, [r4, #0x40]
	mov r1, #1
	bl FUN_0200C5C0
	mov r0, #0x90
	strh r0, [r4, #0x14]
	mov r0, #0x40
	strh r0, [r4, #0x16]
	b _0221F310
_0221F2E4:
	ldr r0, [r4, #0x44]
	mov r1, #0
	str r0, [r4, #0x40]
	ldr r0, [r4, #0x48]
	bl FUN_0200C644
	ldr r0, [r4, #0x40]
	mov r1, #0
	bl FUN_0200C5C0
	mov r0, #0x4c
	strh r0, [r4, #0x14]
	mov r0, #0x78
	strh r0, [r4, #0x16]
	add r0, r5, #0
	bl MOD08_02215574
	add r1, r0, #0
	ldr r0, [r4, #0x40]
	add r1, r1, #1
	bl FUN_0200C6B0
_0221F310:
	mov r0, #1
	strh r0, [r4, #0x12]
_0221F314:
	mov r1, #0x14
	mov r2, #0x16
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x40]
	bl FUN_0200C714
	ldr r0, [r4, #0x40]
	mov r1, #2
	bl FUN_0200C840
	ldr r0, [r4, #0x40]
	mov r1, #1
	bl FUN_0200C90C
	mov r0, #0x12
	ldrsh r0, [r4, r0]
	mov r3, #0x64
	add r1, r0, #0
	mov r0, #5
	str r0, [sp]
	mul r1, r3
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	str r3, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x9c
	add r2, r1, #0
	bl MOD08_022181A8
	add r0, r4, #0
	add r0, #0x9c
	bl MOD08_02218224
	add r0, r4, #0
	add r0, #0x9c
	add r1, sp, #0x10
	add r2, sp, #0xc
	bl MOD08_0221825C
	ldr r0, [r4, #0x40]
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0xc]
	bl FUN_0200C884
	mov r0, #0x16
	add r2, r4, #0
	add r2, #0xb0
	ldrsh r0, [r4, r0]
	ldr r2, [r2]
	mov r1, #0x10
	bl MOD08_0221828C
	mov r2, #0x16
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	mov r1, #0x14
	ldrsh r1, [r4, r1]
	add r2, r2, r3
	lsl r2, r2, #0x10
	ldr r0, [r4, #0x40]
	asr r2, r2, #0x10
	bl FUN_0200C714
	ldr r0, [r4, #0x1c]
	ldr r1, _0221F3A8 ; =MOD08_0221F074
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_0221F3A8: .word MOD08_0221F074

	thumb_func_start MOD08_0221F3AC
MOD08_0221F3AC: ; 0x0221F3AC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	add r4, r1, #0
	str r0, [sp, #0x10]
	ldrb r0, [r4]
	cmp r0, #8
	bls _0221F3BC
	b _0221F710
_0221F3BC:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221F3C8: ; jump table
	.short _0221F3DA - _0221F3C8 - 2 ; case 0
	.short _0221F412 - _0221F3C8 - 2 ; case 1
	.short _0221F46C - _0221F3C8 - 2 ; case 2
	.short _0221F486 - _0221F3C8 - 2 ; case 3
	.short _0221F4BA - _0221F3C8 - 2 ; case 4
	.short _0221F53E - _0221F3C8 - 2 ; case 5
	.short _0221F5D0 - _0221F3C8 - 2 ; case 6
	.short _0221F66E - _0221F3C8 - 2 ; case 7
	.short _0221F6B6 - _0221F3C8 - 2 ; case 8
_0221F3DA:
	ldrb r1, [r4, #0xc]
	ldr r2, _0221F6F4 ; =0x0222C569
	ldr r5, _0221F6F8 ; =0x0222C56A
	lsl r0, r1, #2
	add r3, r1, r0
	ldr r0, _0221F6FC ; =0x0222C56B
	ldr r1, _0221F700 ; =0x0222C568
	ldrb r0, [r0, r3]
	ldrb r1, [r1, r3]
	ldrb r2, [r2, r3]
	str r0, [sp]
	mov r0, #0x64
	str r0, [sp, #4]
	ldr r0, _0221F704 ; =0x0222C56C
	ldrb r0, [r0, r3]
	ldrb r3, [r5, r3]
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0xcc
	bl MOD08_022181A8
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221F74A
_0221F412:
	add r0, r4, #0
	add r0, #0xcc
	bl MOD08_02218224
	cmp r0, #1
	bne _0221F458
	mov r2, #0xcc
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x1c]
	mov r1, #0xc
	bl FUN_02007558
	mov r2, #0xce
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x1c]
	mov r1, #0xd
	bl FUN_02007558
	mov r0, #0x20
	add r2, r4, #0
	add r2, #0xe0
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #0x24]
	ldr r2, [r2]
	bl MOD08_0221828C
	mov r2, #0x20
	add r3, r0, #0
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x1c]
	mov r1, #1
	add r2, r2, r3
	bl FUN_02007558
	b _0221F74A
_0221F458:
	ldrb r0, [r4, #0xc]
	cmp r0, #3
	ldrb r0, [r4]
	blo _0221F466
	add r0, r0, #1
	strb r0, [r4]
	b _0221F74A
_0221F466:
	sub r0, r0, #1
	strb r0, [r4]
	b _0221F74A
_0221F46C:
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	ldrb r0, [r4, #1]
	cmp r0, #0xf
	blo _0221F54A
	mov r0, #0
	strb r0, [r4, #1]
	strb r0, [r4, #0xc]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221F74A
_0221F486:
	add r1, sp, #0x2c
	ldr r0, [r4, #0x30]
	add r1, #2
	add r2, sp, #0x2c
	bl FUN_0200C7A0
	add r1, sp, #0x14
	mov r0, #0x18
	ldrsh r0, [r1, r0]
	cmp r0, #0x68
	bgt _0221F4B2
	ldr r0, [r4, #0x30]
	mov r1, #0
	mov r2, #2
	bl FUN_0200C82C
	ldr r0, [r4, #0x7c]
	mov r1, #0
	mov r2, #2
	bl FUN_0200C82C
	b _0221F74A
_0221F4B2:
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221F74A
_0221F4BA:
	add r1, sp, #0x28
	ldr r0, [r4, #0x30]
	add r1, #2
	add r2, sp, #0x28
	bl FUN_0200C7A0
	add r1, sp, #0x14
	mov r0, #0x14
	ldrsh r0, [r1, r0]
	cmp r0, #0x68
	bgt _0221F4E6
	ldr r0, [r4, #0x30]
	mov r1, #0
	mov r2, #2
	bl FUN_0200C82C
	ldr r0, [r4, #0x7c]
	mov r1, #0
	mov r2, #2
	bl FUN_0200C82C
	b _0221F4F2
_0221F4E6:
	ldr r0, _0221F708 ; =0x04000052
	mov r1, #0x10
	strh r1, [r0]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221F4F2:
	ldrb r0, [r4, #1]
	mov r1, #0x10
	add r2, r1, #0
	add r0, r0, #1
	strb r0, [r4, #1]
	add r0, r4, #4
	bl MOD08_02218A58
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	add r0, #8
	sub r2, #0x10
	bl MOD08_02218A58
	ldr r0, [r4, #8]
	ldr r1, [r4, #4]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0221F708 ; =0x04000052
	strh r1, [r0]
	ldrb r0, [r4, #1]
	cmp r0, #0xa
	bne _0221F52C
	ldr r0, [r4, #0x30]
	mov r1, #0
	mov r2, #0x10
	bl FUN_0200C82C
_0221F52C:
	ldrb r0, [r4, #1]
	cmp r0, #0xc
	bne _0221F54A
	ldr r0, [r4, #0x7c]
	mov r1, #0
	mov r2, #0x10
	bl FUN_0200C82C
	b _0221F74A
_0221F53E:
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	ldrb r0, [r4, #1]
	cmp r0, #0xf
	bhs _0221F54C
_0221F54A:
	b _0221F74A
_0221F54C:
	mov r0, #0
	strb r0, [r4, #1]
	add r1, sp, #0x24
	ldr r0, [r4, #0x30]
	add r1, #2
	add r2, sp, #0x24
	bl FUN_0200C7A0
	add r1, sp, #0x20
	ldr r0, [r4, #0x7c]
	add r1, #2
	add r2, sp, #0x20
	bl FUN_0200C7A0
	add r0, r4, #0
	add r0, #0xc8
	str r0, [sp]
	add r0, r4, #0
	add r0, #0xca
	str r0, [sp, #4]
	add r3, sp, #0x14
	mov r0, #0x12
	mov r1, #0x10
	mov r2, #0xe
	mov r5, #0xc
	ldrsh r0, [r3, r0]
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldrsh r3, [r3, r5]
	bl MOD08_022189D8
	add r0, r4, #0
	add r0, #0x2c
	str r0, [sp]
	mov r3, #0xca
	add r2, sp, #0x14
	mov r0, #0x12
	mov r1, #0x10
	ldrsh r0, [r2, r0]
	ldrsh r1, [r2, r1]
	mov r2, #0xc8
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	bl MOD08_022189F4
	add r0, r4, #0
	add r0, #0x28
	str r0, [sp]
	mov r3, #0xca
	add r2, sp, #0x14
	mov r0, #0x12
	mov r1, #0x10
	ldrsh r0, [r2, r0]
	ldrsh r1, [r2, r1]
	mov r2, #0xc8
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	bl MOD08_02218A1C
	mov r0, #0xa
	lsl r0, r0, #0xe
	str r0, [r4, #0x2c]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221F74A
_0221F5D0:
	ldr r3, _0221F70C ; =0x0222C545
	add r2, sp, #0x30
	mov r1, #0xa
_0221F5D6:
	ldrb r0, [r3]
	add r3, r3, #1
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _0221F5D6
	add r1, sp, #0x1c
	ldr r0, [r4, #0x30]
	add r1, #2
	add r2, sp, #0x1c
	bl FUN_0200C7A0
	add r1, sp, #0x18
	ldr r0, [r4, #0x7c]
	add r1, #2
	add r2, sp, #0x18
	bl FUN_0200C7A0
	add r3, sp, #0x14
	mov r0, #8
	ldrsh r0, [r3, r0]
	mov r2, #0xa
	str r0, [sp]
	mov r0, #4
	ldrsh r0, [r3, r0]
	str r0, [sp, #4]
	str r2, [sp, #8]
	ldrb r1, [r4, #0xc]
	ldr r0, [r4, #0x2c]
	lsl r5, r1, #1
	add r1, sp, #0x30
	ldrsb r1, [r1, r5]
	mov r5, #6
	mul r1, r0
	str r1, [sp, #0xc]
	ldrsh r2, [r3, r2]
	add r0, r4, #0
	add r1, r4, #0
	ldrsh r3, [r3, r5]
	add r0, #0x34
	add r1, #0x58
	bl MOD08_02217F50
	add r3, sp, #0x14
	mov r0, #4
	ldrsh r0, [r3, r0]
	mov r5, #0xa
	str r0, [sp]
	mov r0, #8
	ldrsh r0, [r3, r0]
	str r0, [sp, #4]
	str r5, [sp, #8]
	ldrb r1, [r4, #0xc]
	ldr r0, [r4, #0x2c]
	lsl r2, r1, #1
	add r1, sp, #0x30
	add r1, #1
	ldrsb r1, [r1, r2]
	mov r2, #6
	mul r1, r0
	str r1, [sp, #0xc]
	ldrsh r2, [r3, r2]
	add r0, r4, #0
	add r1, r4, #0
	ldrsh r3, [r3, r5]
	add r0, #0x80
	add r1, #0xa4
	bl MOD08_02217F50
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221F74A
_0221F66E:
	add r0, r4, #0
	ldr r2, [r4, #0x30]
	add r0, #0x34
	add r1, #0x58
	mov r5, #0
	bl MOD08_02217FE4
	cmp r0, #0
	bne _0221F686
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
_0221F686:
	add r0, r4, #0
	add r1, r4, #0
	ldr r2, [r4, #0x7c]
	add r0, #0x80
	add r1, #0xa4
	bl MOD08_02217FE4
	cmp r0, #0
	bne _0221F69E
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
_0221F69E:
	cmp r5, #2
	bne _0221F74A
	ldrb r0, [r4, #0xc]
	cmp r0, #5
	ldrb r0, [r4]
	bne _0221F6B0
	add r0, r0, #1
	strb r0, [r4]
	b _0221F74A
_0221F6B0:
	sub r0, r0, #1
	strb r0, [r4]
	b _0221F74A
_0221F6B6:
	mov r5, #0
	add r0, r4, #4
	add r1, r5, #0
	sub r2, r5, #2
	bl MOD08_02218A58
	cmp r0, #1
	bne _0221F6C8
	add r5, r5, #1
_0221F6C8:
	add r0, r4, #0
	add r0, #8
	mov r1, #0x10
	mov r2, #2
	bl MOD08_02218A58
	cmp r0, #1
	bne _0221F6DA
	add r5, r5, #1
_0221F6DA:
	ldr r0, [r4, #8]
	ldr r1, [r4, #4]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0221F708 ; =0x04000052
	cmp r5, #2
	strh r1, [r0]
	bne _0221F74A
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221F74A
	nop
_0221F6F4: .word MOD8_0222C569
_0221F6F8: .word MOD8_0222C56A
_0221F6FC: .word MOD8_0222C56B
_0221F700: .word MOD8_0222C568
_0221F704: .word MOD8_0222C56C
_0221F708: .word 0x04000052
_0221F70C: .word MOD8_0222C545
_0221F710:
	mov r6, #0
	ldr r0, [r4, #0x10]
	add r1, r6, #0
	bl MOD08_02212498
	cmp r0, #0
	ble _0221F738
	add r5, r4, #0
	add r7, r6, #0
_0221F722:
	ldr r0, [r5, #0x30]
	bl FUN_0200C3DC
	ldr r0, [r4, #0x10]
	add r1, r7, #0
	add r5, #0x4c
	add r6, r6, #1
	bl MOD08_02212498
	cmp r6, r0
	blt _0221F722
_0221F738:
	ldr r0, [r4, #0x10]
	ldr r1, [sp, #0x10]
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
_0221F74A:
	mov r6, #0
	ldr r0, [r4, #0x10]
	add r1, r6, #0
	bl MOD08_02212498
	cmp r0, #0
	ble _0221F7B6
	add r5, r4, #0
	add r7, sp, #0x14
_0221F75C:
	add r1, sp, #0x14
	ldr r0, [r5, #0x30]
	add r1, #2
	add r2, sp, #0x14
	bl FUN_0200C7A0
	mov r0, #0
	ldrsh r0, [r7, r0]
	cmp r0, #0x50
	bge _0221F780
	ldr r0, [r4, #0x10]
	bl MOD08_02215574
	add r1, r0, #0
	ldr r0, [r5, #0x30]
	bl FUN_0200C6B0
	b _0221F7A6
_0221F780:
	mov r0, #2
	ldrsh r0, [r7, r0]
	cmp r0, #0x80
	ldr r0, [r4, #0x10]
	ble _0221F798
	bl MOD08_02215574
	add r1, r0, #0
	ldr r0, [r5, #0x30]
	bl FUN_0200C6B0
	b _0221F7A6
_0221F798:
	bl MOD08_02215574
	add r1, r0, #0
	ldr r0, [r5, #0x30]
	add r1, r1, #1
	bl FUN_0200C6B0
_0221F7A6:
	ldr r0, [r4, #0x10]
	mov r1, #0
	add r5, #0x4c
	add r6, r6, #1
	bl MOD08_02212498
	cmp r6, r0
	blt _0221F75C
_0221F7B6:
	ldrb r0, [r4]
	cmp r0, #4
	blo _0221F7EA
	mov r5, #0
	ldr r0, [r4, #0x10]
	add r1, r5, #0
	bl MOD08_02212498
	cmp r0, #0
	ble _0221F7E4
	add r6, r4, #0
	add r7, r5, #0
_0221F7CE:
	ldr r0, [r6, #0x30]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x10]
	add r1, r7, #0
	add r6, #0x4c
	add r5, r5, #1
	bl MOD08_02212498
	cmp r5, r0
	blt _0221F7CE
_0221F7E4:
	ldr r0, [r4, #0x18]
	bl FUN_0200BC1C
_0221F7EA:
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_0221F7F0
MOD08_0221F7F0: ; 0x0221F7F0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r5, r1, #0
	mov r1, #0xf0
	str r0, [sp]
	add r6, r2, #0
	add r7, r3, #0
	bl MOD08_02228064
	add r4, r0, #0
	mov r1, #0
	strb r1, [r4]
	ldr r0, [sp]
	strb r1, [r4, #1]
	str r0, [r4, #0x10]
	str r6, [r4, #0x18]
	str r5, [r4, #0x14]
	str r1, [r4, #4]
	mov r0, #0x10
	str r0, [r4, #8]
	ldr r0, [r4, #0x10]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #0x10]
	bl MOD08_022154D4
	str r0, [r4, #0x1c]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #0x20]
	ldr r0, [r4, #0x10]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #0x10]
	bl MOD08_0221552C
	str r0, [r4, #0x24]
	ldr r0, [sp]
	mov r1, #2
	bl MOD08_022155C4
	add r5, r0, #0
	ldr r0, [sp]
	mov r1, #1
	bl MOD08_022155C4
	mov r2, #1
	add r1, r2, #0
	add r3, r0, #0
	lsl r1, r5
	add r5, r2, #0
	lsl r5, r3
	orr r1, r5
	orr r1, r2
	sub r2, r2, #2
	ldr r0, [r4, #0x10]
	add r3, r2, #0
	bl MOD08_022279D0
	ldr r0, [r4, #8]
	ldr r1, [r4, #4]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0221F92C ; =0x04000052
	strh r1, [r0]
	ldr r1, [sp]
	add r0, sp, #4
	bl MOD08_02215474
	str r7, [r4, #0x30]
	ldr r0, [r4, #0x10]
	mov r1, #0
	mov r6, #1
	bl MOD08_02212498
	cmp r0, #1
	ble _0221F8B2
	add r5, r4, #0
	add r5, #0x4c
	add r7, sp, #4
_0221F896:
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #0x18]
	add r2, r7, #0
	bl FUN_0200C154
	str r0, [r5, #0x30]
	ldr r0, [r4, #0x10]
	mov r1, #0
	add r5, #0x4c
	add r6, r6, #1
	bl MOD08_02212498
	cmp r6, r0
	blt _0221F896
_0221F8B2:
	mov r6, #0
	ldr r0, [r4, #0x10]
	add r1, r6, #0
	bl MOD08_02212498
	cmp r0, #0
	ble _0221F8EC
	add r5, r4, #0
	mov r7, #1
_0221F8C4:
	ldr r0, [r5, #0x30]
	add r1, r7, #0
	bl FUN_0200C90C
	ldr r0, [r4, #0x10]
	bl MOD08_02215574
	add r1, r0, #0
	ldr r0, [r5, #0x30]
	add r1, r1, #1
	bl FUN_0200C6B0
	ldr r0, [r4, #0x10]
	mov r1, #0
	add r5, #0x4c
	add r6, r6, #1
	bl MOD08_02212498
	cmp r6, r0
	blt _0221F8C4
_0221F8EC:
	ldr r0, [sp]
	bl MOD08_02212004
	cmp r0, #1
	ldr r0, [r4, #0x30]
	bne _0221F90C
	mov r1, #0xa0
	mov r2, #0x2c
	bl FUN_0200C714
	ldr r0, [r4, #0x7c]
	mov r1, #0x50
	mov r2, #0x1d
	bl FUN_0200C714
	b _0221F91E
_0221F90C:
	mov r1, #0x64
	mov r2, #0x2c
	bl FUN_0200C714
	ldr r0, [r4, #0x7c]
	mov r1, #0xb4
	mov r2, #0x1d
	bl FUN_0200C714
_0221F91E:
	ldr r0, [r4, #0x10]
	ldr r1, _0221F930 ; =MOD08_0221F3AC
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0221F92C: .word 0x04000052
_0221F930: .word MOD08_0221F3AC

	thumb_func_start MOD08_0221F934
MOD08_0221F934: ; 0x0221F934
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	ldrb r0, [r5]
	cmp r0, #0
	beq _0221F946
	cmp r0, #1
	beq _0221F9BA
	b _0221F9EE
_0221F946:
	ldrb r0, [r5, #6]
	cmp r0, #0xf
	bhs _0221F950
	add r0, r0, #1
	strb r0, [r5, #6]
_0221F950:
	ldrb r0, [r5, #7]
	cmp r0, #0
	beq _0221F95A
	sub r0, r0, #1
	strb r0, [r5, #7]
_0221F95A:
	ldrb r0, [r5, #7]
	ldrb r1, [r5, #6]
	mov r6, #0
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0221FA3C ; =0x04000052
	strh r1, [r0]
	ldrb r0, [r5, #4]
	add r0, r0, #1
	strb r0, [r5, #4]
	ldrb r0, [r5, #5]
	cmp r0, #0
	ble _0221F9AC
	ldr r4, _0221FA40 ; =0x0222C5DC
	add r7, r5, #0
_0221F978:
	add r1, sp, #0
	ldr r0, [r7, #0x14]
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	ldrb r1, [r5, #4]
	ldrb r0, [r4]
	cmp r1, r0
	blo _0221F9A0
	add r0, r5, r6
	ldrb r1, [r0, #1]
	add r1, r1, #1
	strb r1, [r0, #1]
	ldrb r2, [r0, #1]
	ldrb r1, [r4, #1]
	cmp r2, r1
	blo _0221F9A0
	mov r1, #0
	strb r1, [r0, #1]
_0221F9A0:
	ldrb r0, [r5, #5]
	add r6, r6, #1
	add r7, r7, #4
	add r4, r4, #2
	cmp r6, r0
	blt _0221F978
_0221F9AC:
	ldrb r0, [r5, #4]
	cmp r0, #0x2d
	blo _0221FA18
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
	b _0221FA18
_0221F9BA:
	ldrb r0, [r5, #6]
	cmp r0, #0
	beq _0221F9C4
	sub r0, r0, #1
	strb r0, [r5, #6]
_0221F9C4:
	ldrb r0, [r5, #7]
	cmp r0, #0xf
	bhs _0221F9CE
	add r0, r0, #1
	strb r0, [r5, #7]
_0221F9CE:
	ldrb r0, [r5, #6]
	cmp r0, #0
	bne _0221F9E0
	ldrb r0, [r5, #7]
	cmp r0, #0xf
	bne _0221F9E0
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
_0221F9E0:
	ldrb r0, [r5, #7]
	ldrb r1, [r5, #6]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0221FA3C ; =0x04000052
	strh r1, [r0]
	b _0221FA18
_0221F9EE:
	ldrb r0, [r5, #5]
	mov r6, #0
	cmp r0, #0
	ble _0221FA08
	add r4, r5, #0
_0221F9F8:
	ldr r0, [r4, #0x14]
	bl FUN_0200C3DC
	ldrb r0, [r5, #5]
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, r0
	blt _0221F9F8
_0221FA08:
	ldr r0, [r5, #8]
	add r1, r7, #0
	bl MOD08_02212438
	add r0, r5, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
_0221FA18:
	ldrb r0, [r5, #5]
	mov r6, #0
	cmp r0, #0
	ble _0221FA34
	add r4, r5, #0
_0221FA22:
	ldr r0, [r4, #0x14]
	ldr r0, [r0]
	bl FUN_0200C59C
	ldrb r0, [r5, #5]
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, r0
	blt _0221FA22
_0221FA34:
	ldr r0, [r5, #0x10]
	bl FUN_0200BC1C
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0221FA3C: .word 0x04000052
_0221FA40: .word MOD8_0222C5DC

	thumb_func_start MOD08_0221FA44
MOD08_0221FA44: ; 0x0221FA44
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r7, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	str r3, [sp]
	bl MOD08_02212014
	mov r1, #0x44
	bl AllocFromHeap
	add r4, r0, #0
	bne _0221FA62
	bl ErrorHandling
_0221FA62:
	mov r0, #0
	strb r0, [r4, #4]
	strb r0, [r4]
	str r5, [r4, #0xc]
	str r6, [r4, #0x10]
	add r0, sp, #4
	add r1, r7, #0
	str r7, [r4, #8]
	bl MOD08_02215474
	mov r1, #0
	mvn r1, r1
	ldr r0, [r4, #8]
	add r2, r1, #0
	bl MOD08_02227994
	ldr r0, [r4, #8]
	mov r1, #0
	bl MOD08_02212498
	strb r0, [r4, #5]
	mov r0, #0
	strb r0, [r4, #6]
	mov r0, #0xf
	strb r0, [r4, #7]
	ldrb r0, [r4, #7]
	ldrb r1, [r4, #6]
	mov r6, #1
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0221FBA8 ; =0x04000052
	strh r1, [r0]
	ldr r0, [sp]
	str r0, [r4, #0x14]
	ldrb r0, [r4, #5]
	cmp r0, #1
	ble _0221FAC4
	add r5, r4, #4
_0221FAAE:
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	add r2, sp, #4
	bl FUN_0200C154
	str r0, [r5, #0x14]
	ldrb r0, [r4, #5]
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, r0
	blt _0221FAAE
_0221FAC4:
	add r0, r7, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r7, #0
	bl MOD08_02227470
	cmp r0, #3
	bne _0221FB18
	add r0, r7, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r7, #0
	bl MOD08_02227470
	cmp r0, #3
	bne _0221FB04
	add r0, r7, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r7, #0
	bl MOD08_02227470
	cmp r0, #3
	bne _0221FB04
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl FUN_0200C5C0
	b _0221FB0C
_0221FB04:
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl FUN_0200C5C0
_0221FB0C:
	ldr r0, [r4, #0x14]
	mov r1, #0x80
	mov r2, #0x50
	bl FUN_0200C714
	b _0221FB58
_0221FB18:
	add r0, r7, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r7, #0
	bl MOD08_02227470
	cmp r0, #4
	bne _0221FB46
	add r0, r7, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r7, #0
	bl MOD08_02227470
	cmp r0, #4
	bne _0221FB46
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl FUN_0200C5C0
	b _0221FB4E
_0221FB46:
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl FUN_0200C5C0
_0221FB4E:
	ldr r0, [r4, #0x14]
	mov r1, #0x80
	mov r2, #0x50
	bl FUN_0200C714
_0221FB58:
	ldrb r0, [r4, #5]
	mov r6, #0
	cmp r0, #0
	ble _0221FB98
	add r5, r4, #0
_0221FB62:
	add r1, r4, r6
	mov r0, #0
	strb r0, [r1, #1]
	ldr r0, [r5, #0x14]
	mov r1, #2
	bl FUN_0200C840
	ldr r0, [r5, #0x14]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r4, #8]
	bl MOD08_02212004
	cmp r0, #1
	bne _0221FB8E
	mov r2, #0xfe
	ldr r0, [r5, #0x14]
	ldr r1, _0221FBAC ; =0xBF800000
	lsl r2, r2, #0x16
	bl FUN_0200C884
_0221FB8E:
	ldrb r0, [r4, #5]
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, r0
	blt _0221FB62
_0221FB98:
	ldr r1, _0221FBB0 ; =MOD08_0221F934
	ldr r3, _0221FBB4 ; =0x0000044C
	add r0, r7, #0
	add r2, r4, #0
	bl MOD08_022123E4
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0221FBA8: .word 0x04000052
_0221FBAC: .word 0xBF800000
_0221FBB0: .word MOD08_0221F934
_0221FBB4: .word 0x0000044C

	thumb_func_start MOD08_0221FBB8
MOD08_0221FBB8: ; 0x0221FBB8
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r7, r0, #0
	ldrb r0, [r4]
	mov r6, #0
	cmp r0, #3
	bls _0221FBCA
	b _0221FD70
_0221FBCA:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221FBD6: ; jump table
	.short _0221FBDE - _0221FBD6 - 2 ; case 0
	.short _0221FC12 - _0221FBD6 - 2 ; case 1
	.short _0221FCEA - _0221FBD6 - 2 ; case 2
	.short _0221FD36 - _0221FBD6 - 2 ; case 3
_0221FBDE:
	ldrb r0, [r4, #9]
	cmp r0, #0xf
	bhs _0221FBE8
	add r0, r0, #1
	strb r0, [r4, #9]
_0221FBE8:
	ldrb r0, [r4, #0xa]
	cmp r0, #0
	beq _0221FBF2
	sub r0, r0, #1
	strb r0, [r4, #0xa]
_0221FBF2:
	ldrb r0, [r4, #9]
	cmp r0, #0xf
	bne _0221FC04
	ldrb r0, [r4, #0xa]
	cmp r0, #0
	bne _0221FC04
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221FC04:
	ldrb r0, [r4, #0xa]
	ldrb r1, [r4, #9]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0221FDCC ; =0x04000052
	strh r1, [r0]
	b _0221FD9C
_0221FC12:
	ldr r0, [r4, #0x30]
	cmp r0, #3
	bhi _0221FC78
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221FC24: ; jump table
	.short _0221FC2C - _0221FC24 - 2 ; case 0
	.short _0221FC46 - _0221FC24 - 2 ; case 1
	.short _0221FC60 - _0221FC24 - 2 ; case 2
	.short _0221FC60 - _0221FC24 - 2 ; case 3
_0221FC2C:
	ldr r0, [r4, #0x18]
	mov r1, #1
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x24]
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x34]
	bl FUN_0200C644
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl FUN_0200C644
	b _0221FC78
_0221FC46:
	ldr r0, [r4, #0x1c]
	mov r1, #1
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x20]
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x34]
	bl FUN_0200C644
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl FUN_0200C644
	b _0221FC78
_0221FC60:
	ldr r0, [r4, #0x28]
	mov r1, #1
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x2c]
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x34]
	bl FUN_0200C644
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl FUN_0200C644
_0221FC78:
	add r1, sp, #8
	ldr r0, [r4, #0x34]
	add r1, #2
	add r2, sp, #8
	bl FUN_0200C7A0
	ldr r1, [r4, #0x30]
	ldr r0, _0221FDD0 ; =0x0222C614
	lsl r2, r1, #3
	ldrsh r0, [r0, r2]
	ldr r5, _0221FDD4 ; =0x0222C612
	add r3, sp, #8
	str r0, [sp]
	ldr r0, _0221FDD8 ; =0x0222C5D8
	ldrsh r2, [r5, r2]
	ldrb r0, [r0, r1]
	mov r1, #2
	mov r5, #0
	str r0, [sp, #4]
	ldrsh r1, [r3, r1]
	add r0, r4, #0
	ldrsh r3, [r3, r5]
	add r0, #0x3c
	bl MOD08_02217E80
	add r1, sp, #8
	ldr r0, [r4, #0x38]
	add r1, #2
	add r2, sp, #8
	bl FUN_0200C7A0
	ldr r1, [r4, #0x30]
	ldr r0, _0221FDDC ; =0x0222C618
	lsl r2, r1, #3
	ldrsh r0, [r0, r2]
	ldr r5, _0221FDE0 ; =0x0222C616
	add r3, sp, #8
	str r0, [sp]
	ldr r0, _0221FDD8 ; =0x0222C5D8
	ldrsh r2, [r5, r2]
	ldrb r0, [r0, r1]
	mov r1, #2
	mov r5, #0
	str r0, [sp, #4]
	ldrsh r1, [r3, r1]
	add r0, r4, #0
	ldrsh r3, [r3, r5]
	add r0, #0x60
	bl MOD08_02217E80
	ldr r0, [r4, #0x30]
	add r0, r0, #1
	str r0, [r4, #0x30]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221FD9C
_0221FCEA:
	add r0, r4, #0
	ldr r1, [r4, #0x34]
	add r0, #0x3c
	add r5, r6, #0
	bl MOD08_02217F08
	cmp r0, #0
	bne _0221FCFC
	add r5, r5, #1
_0221FCFC:
	add r0, r4, #0
	ldr r1, [r4, #0x38]
	add r0, #0x60
	bl MOD08_02217F08
	cmp r0, #0
	bne _0221FD0C
	add r5, r5, #1
_0221FD0C:
	cmp r5, #2
	blt _0221FD9C
	ldr r0, [r4, #0x30]
	cmp r0, #3
	bgt _0221FD2E
	ldr r0, [r4, #0x34]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0x38]
	mov r1, #0
	bl FUN_0200C644
	ldrb r0, [r4]
	sub r0, r0, #1
	strb r0, [r4]
	b _0221FD9C
_0221FD2E:
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0221FD9C
_0221FD36:
	ldrb r0, [r4, #9]
	cmp r0, #0
	beq _0221FD40
	sub r0, r0, #1
	strb r0, [r4, #9]
_0221FD40:
	ldrb r0, [r4, #0xa]
	cmp r0, #0xf
	bhs _0221FD4A
	add r0, r0, #1
	strb r0, [r4, #0xa]
_0221FD4A:
	ldrb r1, [r4, #0xa]
	cmp r1, #7
	blo _0221FD52
	mov r6, #1
_0221FD52:
	ldrb r0, [r4, #9]
	cmp r0, #0
	bne _0221FD62
	cmp r1, #0xf
	bne _0221FD62
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_0221FD62:
	ldrb r0, [r4, #0xa]
	ldrb r1, [r4, #9]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0221FDCC ; =0x04000052
	strh r1, [r0]
	b _0221FD9C
_0221FD70:
	ldrb r0, [r4, #8]
	mov r6, #0
	cmp r0, #0
	ble _0221FD8A
	add r5, r4, #0
_0221FD7A:
	ldr r0, [r5, #0x18]
	bl FUN_0200C3DC
	ldrb r0, [r4, #8]
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, r0
	blt _0221FD7A
_0221FD8A:
	ldr r0, [r4, #0xc]
	add r1, r7, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0221FD9C:
	ldrb r0, [r4]
	cmp r0, #3
	bhs _0221FDC2
	cmp r6, #0
	bne _0221FDC2
	ldrb r0, [r4, #8]
	mov r6, #0
	cmp r0, #0
	ble _0221FDC2
	add r5, r4, #0
_0221FDB0:
	ldr r0, [r5, #0x18]
	ldr r0, [r0]
	bl FUN_0200C59C
	ldrb r0, [r4, #8]
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, r0
	blt _0221FDB0
_0221FDC2:
	ldr r0, [r4, #0x14]
	bl FUN_0200BC1C
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0221FDCC: .word 0x04000052
_0221FDD0: .word MOD8_0222C614
_0221FDD4: .word MOD8_0222C612
_0221FDD8: .word MOD8_0222C5D8
_0221FDDC: .word MOD8_0222C618
_0221FDE0: .word MOD8_0222C616

	thumb_func_start MOD08_0221FDE4
MOD08_0221FDE4: ; 0x0221FDE4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	str r0, [sp]
	add r5, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl MOD08_02212014
	mov r1, #0x84
	bl AllocFromHeap
	add r4, r0, #0
	bne _0221FE02
	bl ErrorHandling
_0221FE02:
	mov r0, #0
	strb r0, [r4, #7]
	strb r0, [r4]
	str r5, [r4, #0x10]
	str r6, [r4, #0x14]
	str r0, [r4, #0x30]
	ldr r0, [sp]
	ldr r1, [sp]
	str r0, [r4, #0xc]
	add r0, sp, #4
	bl MOD08_02215474
	mov r1, #0
	mvn r1, r1
	ldr r0, [r4, #0xc]
	add r2, r1, #0
	bl MOD08_02227994
	mov r1, #0
	strb r1, [r4, #9]
	mov r0, #0xf
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0xa]
	ldrb r2, [r4, #9]
	lsl r0, r0, #8
	orr r2, r0
	ldr r0, _0221FF0C ; =0x04000052
	strh r2, [r0]
	ldr r0, [r4, #0xc]
	bl MOD08_02212498
	strb r0, [r4, #8]
	str r7, [r4, #0x18]
	ldrb r0, [r4, #8]
	mov r6, #1
	cmp r0, #1
	ble _0221FE66
	add r5, r4, #4
	add r7, sp, #4
_0221FE50:
	ldr r0, [r4, #0x10]
	ldr r1, [r4, #0x14]
	add r2, r7, #0
	bl FUN_0200C154
	str r0, [r5, #0x18]
	ldrb r0, [r4, #8]
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, r0
	blt _0221FE50
_0221FE66:
	ldr r0, [r4, #0x18]
	mov r1, #0
	bl FUN_0200C5C0
	ldr r0, [r4, #0x1c]
	mov r1, #0
	bl FUN_0200C5C0
	ldr r0, [r4, #0x20]
	mov r1, #1
	bl FUN_0200C5C0
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl FUN_0200C5C0
	ldr r0, [r4, #0x28]
	mov r1, #2
	bl FUN_0200C5C0
	ldr r0, [r4, #0x2c]
	mov r1, #3
	bl FUN_0200C5C0
	ldr r0, [r4, #0x18]
	mov r1, #1
	bl FUN_0200C8D0
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl FUN_0200C8D0
	ldrb r0, [r4, #8]
	mov r7, #0
	cmp r0, #0
	ble _0221FEDC
	ldr r6, _0221FF10 ; =0x0222C5FA
	add r5, r4, #0
_0221FEB2:
	ldr r0, [r5, #0x18]
	mov r1, #1
	bl FUN_0200C5E0
	mov r1, #0
	mov r2, #2
	ldrsh r1, [r6, r1]
	ldrsh r2, [r6, r2]
	ldr r0, [r5, #0x18]
	bl FUN_0200C714
	ldr r0, [r5, #0x18]
	mov r1, #1
	bl FUN_0200C90C
	ldrb r0, [r4, #8]
	add r7, r7, #1
	add r5, r5, #4
	add r6, r6, #4
	cmp r7, r0
	blt _0221FEB2
_0221FEDC:
	ldr r0, [r4, #0x1c]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0x20]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0x2c]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [sp]
	ldr r1, _0221FF14 ; =MOD08_0221FBB8
	ldr r3, _0221FF18 ; =0x0000044C
	add r2, r4, #0
	bl MOD08_022123E4
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0221FF0C: .word 0x04000052
_0221FF10: .word MOD8_0222C5FA
_0221FF14: .word MOD08_0221FBB8
_0221FF18: .word 0x0000044C

	thumb_func_start MOD08_0221FF1C
MOD08_0221FF1C: ; 0x0221FF1C
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0xc]
	cmp r0, #7
	bls _0221FF2C
	b _02220084
_0221FF2C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221FF38: ; jump table
	.short _0221FF48 - _0221FF38 - 2 ; case 0
	.short _0221FF5C - _0221FF38 - 2 ; case 1
	.short _0221FF7E - _0221FF38 - 2 ; case 2
	.short _0221FFAC - _0221FF38 - 2 ; case 3
	.short _0221FFDA - _0221FF38 - 2 ; case 4
	.short _0221FFF8 - _0221FF38 - 2 ; case 5
	.short _02220020 - _0221FF38 - 2 ; case 6
	.short _02220068 - _0221FF38 - 2 ; case 7
_0221FF48:
	ldrb r0, [r4, #0xe]
	sub r0, r0, #1
	strb r0, [r4, #0xe]
	ldrb r0, [r4, #0xe]
	cmp r0, #0xa
	bhi _0221FF68
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	b _02220092
_0221FF5C:
	ldrb r0, [r4, #0xd]
	add r0, r0, #1
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xd]
	cmp r0, #3
	bhs _0221FF6A
_0221FF68:
	b _02220092
_0221FF6A:
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200C644
	mov r0, #0
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	b _02220092
_0221FF7E:
	ldrb r0, [r4, #0xd]
	add r0, r0, #1
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xd]
	cmp r0, #3
	bhi _0221FFA0
	ldr r0, [r4, #0x38]
	ldr r1, _0222009C ; =0x3DCCCCCD
	bl _fadd
	str r0, [r4, #0x38]
	ldr r1, [r4, #0x38]
	ldr r0, [r4, #0x10]
	add r2, r1, #0
	bl FUN_0200C884
	b _02220092
_0221FFA0:
	mov r0, #0
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	b _02220092
_0221FFAC:
	ldrb r0, [r4, #0xd]
	add r0, r0, #1
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xd]
	cmp r0, #3
	bhi _0221FFCE
	ldr r0, [r4, #0x38]
	ldr r1, _0222009C ; =0x3DCCCCCD
	bl _fsub
	str r0, [r4, #0x38]
	ldr r1, [r4, #0x38]
	ldr r0, [r4, #0x10]
	add r2, r1, #0
	bl FUN_0200C884
	b _02220092
_0221FFCE:
	mov r0, #0
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	b _02220092
_0221FFDA:
	ldrb r0, [r4, #0xe]
	sub r0, r0, #1
	strb r0, [r4, #0xe]
	ldrb r0, [r4, #0xe]
	cmp r0, #0xa
	bhi _02220092
	ldr r0, [r4, #0x3c]
	mov r1, #1
	str r1, [r0]
	mov r0, #0
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	b _02220092
_0221FFF8:
	ldrb r0, [r4, #0xd]
	add r0, r0, #1
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xd]
	cmp r0, #0x1e
	bls _02220010
	mov r0, #0
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	b _02220092
_02220010:
	ldr r0, [r4, #0x3c]
	ldr r0, [r0]
	cmp r0, #2
	bne _02220092
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	b _02220092
_02220020:
	bl LCRandom
	mov r1, #0xa
	bl _s32_div_f
	add r5, r1, #0
	add r2, sp, #8
	ldr r0, [r4, #0x10]
	add r1, sp, #8
	add r2, #2
	add r5, #0xa
	bl FUN_0200C7A0
	ldrb r0, [r4, #0xf]
	add r3, sp, #8
	mov r1, #0
	lsl r2, r0, #2
	ldr r0, _022200A0 ; =0x0222C5E4
	ldrsh r0, [r0, r2]
	str r0, [sp]
	lsl r0, r5, #0x10
	ldr r5, _022200A4 ; =0x0222C5E2
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	ldrsh r2, [r5, r2]
	add r0, r4, #0
	mov r5, #2
	ldrsh r1, [r3, r1]
	ldrsh r3, [r3, r5]
	add r0, #0x14
	bl MOD08_02217E80
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	b _02220092
_02220068:
	add r0, r4, #0
	ldr r1, [r4, #0x10]
	add r0, #0x14
	bl MOD08_02217F08
	cmp r0, #0
	bne _02220092
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl FUN_0200C644
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02220084:
	ldr r0, [r4, #0x3c]
	mov r1, #3
	str r1, [r0]
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
_02220092:
	ldr r0, [r4, #0x10]
	bl FUN_0200C5A8
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_0222009C: .word 0x3DCCCCCD
_022200A0: .word MOD8_0222C5E4
_022200A4: .word MOD8_0222C5E2

	thumb_func_start MOD08_022200A8
MOD08_022200A8: ; 0x022200A8
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bhi _02220164
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022200C0: ; jump table
	.short _022200C8 - _022200C0 - 2 ; case 0
	.short _022200F4 - _022200C0 - 2 ; case 1
	.short _02220116 - _022200C0 - 2 ; case 2
	.short _02220142 - _022200C0 - 2 ; case 3
_022200C8:
	ldrb r6, [r4, #2]
	mov r3, #1
	mov r2, #0
	cmp r6, #0
	ble _022200E8
	ldr r0, _0222017C ; =0x00000514
	add r5, r4, #0
_022200D6:
	ldr r1, [r5, r0]
	cmp r1, #1
	beq _022200E0
	mov r3, #0
	b _022200E8
_022200E0:
	add r2, r2, #1
	add r5, r5, #4
	cmp r2, r6
	blt _022200D6
_022200E8:
	cmp r3, #1
	bne _02220174
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _02220174
_022200F4:
	ldrb r0, [r4, #2]
	mov r5, #0
	cmp r0, #0
	ble _0222010E
	ldr r0, _0222017C ; =0x00000514
	add r3, r4, #0
	mov r2, #2
_02220102:
	str r2, [r3, r0]
	ldrb r1, [r4, #2]
	add r5, r5, #1
	add r3, r3, #4
	cmp r5, r1
	blt _02220102
_0222010E:
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _02220174
_02220116:
	ldrb r5, [r4, #2]
	mov r2, #1
	mov r6, #0
	cmp r5, #0
	ble _02220136
	ldr r0, _0222017C ; =0x00000514
	add r3, r4, #0
_02220124:
	ldr r1, [r3, r0]
	cmp r1, #3
	beq _0222012E
	mov r2, #0
	b _02220136
_0222012E:
	add r6, r6, #1
	add r3, r3, #4
	cmp r6, r5
	blt _02220124
_02220136:
	cmp r2, #1
	bne _02220174
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _02220174
_02220142:
	ldrb r0, [r4, #2]
	mov r6, #0
	cmp r0, #0
	ble _0222015C
	add r5, r4, #0
_0222014C:
	ldr r0, [r5, #0x24]
	bl FUN_0200C3DC
	ldrb r0, [r4, #2]
	add r6, r6, #1
	add r5, #0x40
	cmp r6, r0
	blt _0222014C
_0222015C:
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _02220174
_02220164:
	ldr r0, [r4, #8]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
_02220174:
	ldr r0, [r4, #0x10]
	bl FUN_0200BC1C
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222017C: .word 0x00000514

	thumb_func_start MOD08_02220180
MOD08_02220180: ; 0x02220180
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x50
	str r0, [sp]
	add r5, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl MOD08_02212014
	ldr r1, _022202E8 ; =0x00000564
	bl AllocFromHeap
	add r4, r0, #0
	bne _0222019E
	bl ErrorHandling
_0222019E:
	mov r0, #0
	strb r0, [r4, #1]
	strb r0, [r4]
	str r5, [r4, #0xc]
	ldr r0, [sp]
	str r6, [r4, #0x10]
	str r0, [r4, #8]
	ldr r1, [sp]
	add r0, sp, #0x1c
	bl MOD08_02215474
	mov r1, #0
	mvn r1, r1
	ldr r0, [r4, #8]
	add r2, r1, #0
	bl MOD08_02227994
	ldr r0, [r4, #8]
	mov r1, #0
	bl MOD08_02212498
	strb r0, [r4, #2]
	mov r0, #0xc
	strb r0, [r4, #2]
	mov r0, #0
	str r7, [r4, #0x24]
	str r0, [sp, #4]
	str r0, [sp, #0x14]
	ldrb r0, [r4, #2]
	cmp r0, #0
	ble _022202D8
	ldr r0, _022202EC ; =0x00000514
	add r5, r4, #0
	add r0, r4, r0
	str r0, [sp, #0xc]
	add r0, r4, #0
	str r0, [sp, #8]
	add r0, #0x14
	str r0, [sp, #8]
_022201EC:
	ldr r0, [sp, #0x14]
	cmp r0, #0
	beq _022201FE
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	add r2, sp, #0x1c
	bl FUN_0200C154
	str r0, [r5, #0x24]
_022201FE:
	add r1, r5, #0
	ldr r6, [r5, #0x24]
	add r1, #0x20
	mov r0, #0
	strb r0, [r1]
	add r1, r5, #0
	add r1, #0x21
	strb r0, [r1]
	bl LCRandom
	mov r1, #0xa
	bl _s32_div_f
	ldr r0, [sp, #0x14]
	add r1, #0xa
	add r1, r0, r1
	add r0, r5, #0
	add r0, #0x22
	strb r1, [r0]
	bl LCRandom
	mov r1, #6
	bl _s32_div_f
	add r0, r5, #0
	add r0, #0x23
	strb r1, [r0]
	mov r0, #0xfe
	lsl r0, r0, #0x16
	str r0, [r5, #0x4c]
	ldr r0, [r4, #8]
	ldr r1, _022202F0 ; =0x0222C632
	str r0, [r5, #0x14]
	ldr r0, [r4, #0xc]
	str r0, [r5, #0x18]
	ldr r0, [r4, #0x10]
	str r0, [r5, #0x1c]
	ldr r0, [sp, #0xc]
	str r0, [r5, #0x50]
	ldr r0, [sp, #4]
	lsl r0, r0, #3
	str r0, [sp, #0x18]
	add r7, r1, r0
	bl LCRandom
	mov r1, #6
	ldrsh r1, [r7, r1]
	bl _s32_div_f
	mov r0, #2
	ldrsh r0, [r7, r0]
	add r0, r0, r1
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #0x10]
	bl LCRandom
	mov r1, #4
	ldrsh r1, [r7, r1]
	bl _s32_div_f
	ldr r2, _022202F0 ; =0x0222C632
	ldr r0, [sp, #0x18]
	ldrsh r0, [r2, r0]
	add r0, r0, r1
	lsl r0, r0, #0x10
	asr r2, r0, #0x10
	ldr r1, [sp, #0x10]
	add r0, r6, #0
	bl FUN_0200C714
	add r0, r6, #0
	mov r1, #2
	bl FUN_0200C840
	ldr r1, [r5, #0x4c]
	add r0, r6, #0
	add r2, r1, #0
	bl FUN_0200C884
	add r0, r6, #0
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [sp]
	ldr r1, _022202F4 ; =MOD08_0221FF1C
	ldr r2, [sp, #8]
	ldr r3, _022202F8 ; =0x0000044B
	bl MOD08_022123E4
	ldr r0, [sp, #4]
	mov r1, #6
	add r0, r0, #1
	bl _s32_div_f
	ldr r0, [sp, #0xc]
	str r1, [sp, #4]
	add r0, r0, #4
	str r0, [sp, #0xc]
	ldr r0, [sp, #8]
	ldrb r1, [r4, #2]
	add r0, #0x40
	str r0, [sp, #8]
	ldr r0, [sp, #0x14]
	add r5, #0x40
	add r0, r0, #1
	str r0, [sp, #0x14]
	cmp r0, r1
	blt _022201EC
_022202D8:
	ldr r0, [sp]
	ldr r1, _022202FC ; =MOD08_022200A8
	ldr r3, _02220300 ; =0x0000044D
	add r2, r4, #0
	bl MOD08_022123E4
	add sp, #0x50
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022202E8: .word 0x00000564
_022202EC: .word 0x00000514
_022202F0: .word MOD8_0222C632
_022202F4: .word MOD08_0221FF1C
_022202F8: .word 0x0000044B
_022202FC: .word MOD08_022200A8
_02220300: .word 0x0000044D

	thumb_func_start MOD08_02220304
MOD08_02220304: ; 0x02220304
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #4]
	cmp r0, #3
	bhi _022203EA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222031E: ; jump table
	.short _02220326 - _0222031E - 2 ; case 0
	.short _02220344 - _0222031E - 2 ; case 1
	.short _02220396 - _0222031E - 2 ; case 2
	.short _022203C0 - _0222031E - 2 ; case 3
_02220326:
	ldr r0, [r4, #8]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #8]
	bl MOD08_022154D4
	mov r1, #6
	mov r2, #1
	bl FUN_02007558
	ldrb r0, [r4, #4]
	add r0, r0, #1
	strb r0, [r4, #4]
	b _02220410
_02220344:
	add r0, r4, #0
	add r0, #0x2c
	bl MOD08_02218704
	cmp r0, #0
	beq _02220410
	mov r0, #0
	str r0, [r4]
	ldr r0, [r4, #8]
	mov r1, #1
	bl MOD08_022155C4
	add r5, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl MOD08_02218998
	add r6, r0, #0
	ldr r0, [r4, #8]
	bl MOD08_02212014
	mov r1, #0xc8
	str r1, [sp]
	mov r3, #3
	str r5, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	str r6, [sp, #0xc]
	str r0, [sp, #0x10]
	add r0, r1, #0
	mov r1, #0xa0
	add r2, r1, #0
	add r2, #0xcc
	lsl r3, r3, #0xe
	bl MOD08_022188DC
	str r0, [r4, #0x28]
	ldrb r0, [r4, #4]
	add r0, r0, #1
	strb r0, [r4, #4]
	b _02220410
_02220396:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	cmp r0, #0x78
	blt _02220410
	ldr r0, [r4, #0x28]
	bl MOD08_0221894C
	mov r1, #2
	mov r2, #0x10
	str r1, [sp]
	add r0, r4, #0
	str r2, [sp, #4]
	add r0, #0x2c
	add r3, r2, #0
	bl MOD08_022186D4
	ldrb r0, [r4, #4]
	add r0, r0, #1
	strb r0, [r4, #4]
	b _02220410
_022203C0:
	add r0, r4, #0
	add r0, #0x2c
	bl MOD08_02218704
	cmp r0, #0
	beq _02220410
	ldr r0, [r4, #8]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #8]
	bl MOD08_022154D4
	mov r1, #6
	mov r2, #0
	bl FUN_02007558
	ldrb r0, [r4, #4]
	add r0, r0, #1
	strb r0, [r4, #4]
	b _02220410
_022203EA:
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _02220428 ; =0xFFFF1FFF
	and r0, r1
	str r0, [r2]
	ldr r0, [r4, #8]
	mov r1, #2
	bl MOD08_02214850
	ldr r0, [r4, #8]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
_02220410:
	ldr r0, [r4, #0x24]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x20]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x10]
	bl FUN_0200BC1C
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	nop
_02220428: .word 0xFFFF1FFF

	thumb_func_start MOD08_0222042C
MOD08_0222042C: ; 0x0222042C
	push {r3, r4, r5, lr}
	sub sp, #8
	mov r1, #0x54
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #4
	bl MOD08_02227B70
	ldr r0, [r4, #8]
	mov r1, #0
	bl MOD08_022124D8
	mov r1, #2
	str r0, [r4, #0x20]
	bl FUN_0200C90C
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r2, [r0]
	ldr r1, _022204C0 ; =0xFFFF1FFF
	and r2, r1
	lsr r1, r0, #0xb
	orr r1, r2
	str r1, [r0]
	add r0, #0x4a
	ldrh r2, [r0]
	mov r1, #0x3f
	bic r2, r1
	mov r1, #0x1b
	orr r1, r2
	strh r1, [r0]
	ldrh r2, [r0]
	ldr r1, _022204C4 ; =0xFFFFC0FF
	and r2, r1
	mov r1, #0x17
	lsl r1, r1, #8
	orr r1, r2
	strh r1, [r0]
	ldr r0, [r4, #8]
	mov r1, #1
	bl MOD08_022124D8
	mov r1, #1
	str r0, [r4, #0x24]
	bl FUN_0200C90C
	mov r1, #0x10
	str r1, [sp]
	add r0, r4, #0
	mov r2, #2
	str r1, [sp, #4]
	add r0, #0x2c
	add r3, r2, #0
	bl MOD08_022186D4
	ldr r0, [r4, #8]
	mov r1, #2
	bl MOD08_0221477C
	mov r0, #2
	mov r1, #1
	bl FUN_0201797C
	ldr r0, [r4, #8]
	ldr r1, _022204C8 ; =MOD08_02220304
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_022204C0: .word 0xFFFF1FFF
_022204C4: .word 0xFFFFC0FF
_022204C8: .word MOD08_02220304

	thumb_func_start MOD08_022204CC
MOD08_022204CC: ; 0x022204CC
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0200C658
	cmp r0, #1
	bne _022204DE
	add r0, r4, #0
	bl FUN_0200C5A8
_022204DE:
	pop {r4, pc}

	thumb_func_start MOD08_022204E0
MOD08_022204E0: ; 0x022204E0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r1, [sp, #4]
	str r0, [sp]
	ldr r0, [sp, #4]
	mov r1, #0x1c
	ldrsh r0, [r0, r1]
	cmp r0, #0
	bgt _02220504
	ldr r0, [sp, #4]
	ldr r0, [r0, #0x30]
	bl MOD08_022204CC
	ldr r0, [sp, #4]
	ldr r0, [r0, #0x34]
	bl MOD08_022204CC
	b _0222050A
_02220504:
	sub r1, r0, #1
	ldr r0, [sp, #4]
	strh r1, [r0, #0x1c]
_0222050A:
	ldr r0, [sp, #4]
	ldr r0, [r0, #0x28]
	bl MOD08_022204CC
	ldr r0, [sp, #4]
	ldr r0, [r0, #0x2c]
	bl MOD08_022204CC
	ldr r4, [sp, #4]
	mov r6, #0
	add r7, r6, #0
	add r5, r4, #0
_02220522:
	mov r0, #0x1e
	ldrsh r0, [r4, r0]
	add r0, r0, #1
	strh r0, [r4, #0x1e]
	mov r0, #0x1e
	ldrsh r0, [r4, r0]
	cmp r0, #0x28
	blt _0222053C
	ldr r0, [r5, #0x28]
	mov r1, #0
	bl FUN_0200C644
	add r6, r6, #1
_0222053C:
	add r7, r7, #1
	add r4, r4, #2
	add r5, r5, #4
	cmp r7, #4
	blt _02220522
	cmp r6, #4
	bne _02220570
	ldr r4, [sp, #4]
	mov r5, #0
_0222054E:
	ldr r0, [r4, #0x28]
	bl FUN_0200C3DC
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #4
	blt _0222054E
	ldr r0, [sp, #4]
	ldr r1, [sp]
	ldr r0, [r0, #4]
	bl MOD08_02212438
	ldr r0, [sp, #4]
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02220570:
	ldr r0, [sp, #4]
	ldr r0, [r0, #0x10]
	bl FUN_0200BC1C
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_0222057C
MOD08_0222057C: ; 0x0222057C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	mov r1, #0x38
	add r5, r0, #0
	add r4, r3, #0
	bl MOD08_02228064
	add r6, r0, #0
	mov r0, #0xa
	strh r0, [r6, #0x1c]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02227B70
	ldr r1, [r6, #4]
	add r0, sp, #0
	bl MOD08_02215474
	str r4, [r6, #0x28]
	mov r0, #0
	strh r0, [r6, #0x1e]
	mov r7, #1
	add r4, r6, #2
	add r5, r6, #4
_022205AC:
	mov r0, #0
	strh r0, [r4, #0x1e]
	ldr r0, [r6, #8]
	ldr r1, [r6, #0x10]
	add r2, sp, #0
	bl FUN_0200C154
	str r0, [r5, #0x28]
	add r7, r7, #1
	add r4, r4, #2
	add r5, r5, #4
	cmp r7, #4
	blt _022205AC
	ldr r0, [r6, #0x28]
	mov r1, #1
	bl FUN_0200C8D0
	ldr r0, [r6, #0x2c]
	mov r1, #1
	bl FUN_0200C8D0
	mov r1, #0x1f
	ldr r0, [r6, #0x28]
	mvn r1, r1
	mov r2, #0
	bl FUN_0200C82C
	mov r1, #0x1f
	ldr r0, [r6, #0x2c]
	mvn r1, r1
	mov r2, #0x20
	bl FUN_0200C82C
	ldr r0, [r6, #0x30]
	mov r1, #0x20
	mov r2, #0
	bl FUN_0200C82C
	mov r1, #0x20
	ldr r0, [r6, #0x34]
	add r2, r1, #0
	bl FUN_0200C82C
	ldr r0, [r6, #4]
	ldr r1, _02220610 ; =MOD08_022204E0
	add r2, r6, #0
	bl MOD08_02212400
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02220610: .word MOD08_022204E0

	thumb_func_start MOD08_02220614
MOD08_02220614: ; 0x02220614
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r1, #0
	mov r4, #0
	str r0, [sp, #0x1c]
	str r4, [sp, #0x20]
	add r6, r5, #0
	add r7, r5, #0
_02220624:
	mov r0, #0x22
	ldrsh r0, [r6, r0]
	add r0, r0, #1
	strh r0, [r6, #0x22]
	mov r0, #0x22
	ldrsh r0, [r6, r0]
	cmp r0, #0x14
	blt _02220676
	ldr r0, [r7, #0x2c]
	bl MOD08_022204CC
	mov r0, #0x22
	ldrsh r0, [r5, r0]
	cmp r0, #0x6e
	bne _02220676
	mov r1, #0
	mvn r1, r1
	ldr r0, [r5, #4]
	add r2, r1, #0
	bl MOD08_02227994
	ldr r0, [r5, #0x2c]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r5, #0x30]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r5, #0x34]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r5, #0x38]
	mov r1, #1
	bl FUN_0200C90C
	mov r0, #0xf
	str r0, [r5, #0x54]
	mov r0, #0
	str r0, [r5, #0x58]
_02220676:
	add r4, r4, #1
	add r6, r6, #2
	add r7, r7, #4
	cmp r4, #4
	blt _02220624
	mov r0, #0x22
	ldrsh r0, [r5, r0]
	cmp r0, #0x32
	bne _022206BA
	ldr r0, [r5, #4]
	bl MOD08_02212014
	add r1, r0, #0
	mov r0, #0x10
	str r0, [sp]
	sub r0, #0x12
	str r0, [sp, #4]
	mov r2, #2
	str r2, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #0xe
	str r0, [sp, #0x10]
	ldr r0, _02220894 ; =0x0000FFFF
	str r0, [sp, #0x14]
	ldr r0, _02220898 ; =0x000003EA
	str r0, [sp, #0x18]
	ldr r3, [r5, #0x1c]
	ldr r0, [r5, #0x18]
	lsl r3, r3, #0x14
	lsr r3, r3, #0x10
	bl MOD08_02218B20
	str r0, [r5, #0x3c]
_022206BA:
	mov r0, #0x22
	ldrsh r0, [r5, r0]
	cmp r0, #0x3c
	bne _022206F4
	ldr r0, [r5, #4]
	bl MOD08_02212014
	add r1, r0, #0
	mov r0, #0x10
	str r0, [sp]
	sub r0, #0x12
	str r0, [sp, #4]
	mov r2, #2
	str r2, [sp, #8]
	mov r0, #0xe
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, _02220894 ; =0x0000FFFF
	str r0, [sp, #0x14]
	ldr r0, _02220898 ; =0x000003EA
	str r0, [sp, #0x18]
	ldr r3, [r5, #0x1c]
	ldr r0, [r5, #0x18]
	lsl r3, r3, #0x14
	lsr r3, r3, #0x10
	bl MOD08_02218B20
	str r0, [r5, #0x40]
_022206F4:
	mov r0, #0x22
	ldrsh r0, [r5, r0]
	cmp r0, #0x46
	bne _0222072E
	ldr r0, [r5, #4]
	bl MOD08_02212014
	add r1, r0, #0
	mov r0, #0x10
	str r0, [sp]
	sub r0, #0x12
	str r0, [sp, #4]
	mov r2, #2
	str r2, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #0xe
	str r0, [sp, #0x10]
	ldr r0, _02220894 ; =0x0000FFFF
	str r0, [sp, #0x14]
	ldr r0, _02220898 ; =0x000003EA
	str r0, [sp, #0x18]
	ldr r3, [r5, #0x1c]
	ldr r0, [r5, #0x18]
	lsl r3, r3, #0x14
	lsr r3, r3, #0x10
	bl MOD08_02218B20
	str r0, [r5, #0x44]
_0222072E:
	mov r0, #0x22
	ldrsh r0, [r5, r0]
	cmp r0, #0x50
	bne _02220768
	ldr r0, [r5, #4]
	bl MOD08_02212014
	add r1, r0, #0
	mov r0, #0x10
	str r0, [sp]
	sub r0, #0x12
	str r0, [sp, #4]
	mov r2, #2
	str r2, [sp, #8]
	mov r0, #0xe
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, _02220894 ; =0x0000FFFF
	str r0, [sp, #0x14]
	ldr r0, _02220898 ; =0x000003EA
	str r0, [sp, #0x18]
	ldr r3, [r5, #0x1c]
	ldr r0, [r5, #0x18]
	lsl r3, r3, #0x14
	lsr r3, r3, #0x10
	bl MOD08_02218B20
	str r0, [r5, #0x48]
_02220768:
	mov r0, #0x22
	ldrsh r0, [r5, r0]
	cmp r0, #0x5a
	bne _022207A2
	ldr r0, [r5, #4]
	bl MOD08_02212014
	add r1, r0, #0
	mov r0, #0x10
	str r0, [sp]
	sub r0, #0x12
	str r0, [sp, #4]
	mov r2, #2
	str r2, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #0xe
	str r0, [sp, #0x10]
	ldr r0, _02220894 ; =0x0000FFFF
	str r0, [sp, #0x14]
	ldr r0, _02220898 ; =0x000003EA
	str r0, [sp, #0x18]
	ldr r3, [r5, #0x1c]
	ldr r0, [r5, #0x18]
	lsl r3, r3, #0x14
	lsr r3, r3, #0x10
	bl MOD08_02218B20
	str r0, [r5, #0x4c]
_022207A2:
	mov r0, #0x22
	ldrsh r0, [r5, r0]
	cmp r0, #0x64
	bne _022207DC
	ldr r0, [r5, #4]
	bl MOD08_02212014
	add r1, r0, #0
	mov r0, #0x10
	str r0, [sp]
	sub r0, #0x12
	str r0, [sp, #4]
	mov r2, #2
	str r2, [sp, #8]
	mov r0, #0xe
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, _02220894 ; =0x0000FFFF
	str r0, [sp, #0x14]
	ldr r0, _02220898 ; =0x000003EA
	str r0, [sp, #0x18]
	ldr r3, [r5, #0x1c]
	ldr r0, [r5, #0x18]
	lsl r3, r3, #0x14
	lsr r3, r3, #0x10
	bl MOD08_02218B20
	str r0, [r5, #0x50]
_022207DC:
	mov r1, #0x22
	ldrsh r0, [r5, r1]
	cmp r0, #0x6e
	bne _02220816
	sub r1, #0x23
	ldr r0, [r5, #4]
	add r2, r1, #0
	bl MOD08_02227994
	ldr r0, [r5, #0x2c]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r5, #0x30]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r5, #0x34]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r5, #0x38]
	mov r1, #1
	bl FUN_0200C90C
	mov r0, #0xf
	str r0, [r5, #0x54]
	mov r0, #0
	str r0, [r5, #0x58]
_02220816:
	mov r0, #0x22
	ldrsh r0, [r5, r0]
	cmp r0, #0x6e
	blt _0222084E
	ldr r0, [r5, #0x54]
	cmp r0, #0
	ble _02220828
	sub r0, r0, #1
	str r0, [r5, #0x54]
_02220828:
	ldr r0, [r5, #0x58]
	cmp r0, #0xf
	bge _02220832
	add r0, r0, #1
	str r0, [r5, #0x58]
_02220832:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x54]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0222089C ; =0x04000052
	strh r1, [r0]
	ldr r0, [r5, #0x54]
	cmp r0, #0
	bne _0222084E
	ldr r0, [r5, #0x58]
	cmp r0, #0xf
	bne _0222084E
	mov r0, #4
	str r0, [sp, #0x20]
_0222084E:
	ldr r0, [sp, #0x20]
	cmp r0, #4
	bne _0222088A
	mov r6, #0
	add r4, r5, #0
_02220858:
	ldr r0, [r4, #0x2c]
	bl FUN_0200C3DC
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _02220858
	mov r6, #0
	add r4, r5, #0
_0222086A:
	ldr r0, [r4, #0x3c]
	bl MOD08_02218B08
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #6
	blt _0222086A
	ldr r0, [r5, #4]
	ldr r1, [sp, #0x1c]
	bl MOD08_02212438
	add r0, r5, #0
	bl FreeToHeap
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
_0222088A:
	ldr r0, [r5, #0x10]
	bl FUN_0200BC1C
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02220894: .word 0x0000FFFF
_02220898: .word 0x000003EA
_0222089C: .word 0x04000052

	thumb_func_start MOD08_022208A0
MOD08_022208A0: ; 0x022208A0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	mov r1, #0x5c
	str r0, [sp]
	add r5, r3, #0
	bl MOD08_02228064
	add r4, r0, #0
	mov r0, #0xa
	strh r0, [r4, #0x20]
	ldr r0, [sp]
	add r1, r4, #0
	bl MOD08_02227B70
	ldr r1, [r4, #4]
	add r0, sp, #0xc
	bl MOD08_02215474
	str r5, [r4, #0x2c]
	mov r0, #0
	strh r0, [r4, #0x22]
	mov r0, #1
	str r0, [sp, #8]
	mov r7, #5
	add r6, r4, #2
	add r5, r4, #4
_022208D4:
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r2, r0, #0x1e
	sub r2, r2, r1
	mov r0, #0x1e
	ror r2, r0
	add r0, r1, r2
	add r0, r7, r0
	strh r0, [r6, #0x22]
	ldr r0, [r4, #8]
	ldr r1, [r4, #0x10]
	add r2, sp, #0xc
	bl FUN_0200C154
	str r0, [r5, #0x2c]
	ldr r0, [sp, #8]
	add r7, r7, #5
	add r0, r0, #1
	add r6, r6, #2
	add r5, r5, #4
	str r0, [sp, #8]
	cmp r0, #4
	blt _022208D4
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl FUN_0200C8D0
	ldr r0, [r4, #0x34]
	mov r1, #1
	bl FUN_0200C8D0
	ldr r0, [sp]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [sp]
	bl MOD08_022154D4
	mov r1, #0
	add r5, r0, #0
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #1
	bl FUN_0200782C
	add r0, r5, #0
	mov r1, #0x29
	bl FUN_0200782C
	ldr r0, [sp]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [sp]
	bl MOD08_02227470
	cmp r0, #3
	bne _02220956
	mov r7, #0x8c
	b _02220958
_02220956:
	mov r7, #0x54
_02220958:
	mov r6, #0
	add r5, r4, #0
_0222095C:
	ldr r0, [r5, #0x2c]
	ldr r1, [sp, #4]
	add r2, r7, #0
	bl FUN_0200C714
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #4
	blt _0222095C
	ldr r0, [sp]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [sp]
	bl MOD08_02227470
	cmp r0, #3
	ldr r0, [r4, #0x2c]
	bne _022209A2
	mov r1, #0xa
	bl FUN_0200C6C4
	ldr r0, [r4, #0x34]
	mov r1, #0xa
	bl FUN_0200C6C4
	ldr r0, [r4, #0x30]
	mov r1, #0x12
	bl FUN_0200C6C4
	ldr r0, [r4, #0x38]
	mov r1, #0x12
	bl FUN_0200C6C4
	b _022209C0
_022209A2:
	mov r1, #0x12
	bl FUN_0200C6C4
	ldr r0, [r4, #0x34]
	mov r1, #0x12
	bl FUN_0200C6C4
	ldr r0, [r4, #0x30]
	mov r1, #0xa
	bl FUN_0200C6C4
	ldr r0, [r4, #0x38]
	mov r1, #0xa
	bl FUN_0200C6C4
_022209C0:
	mov r1, #0x1f
	ldr r0, [r4, #0x2c]
	mvn r1, r1
	mov r2, #0
	bl FUN_0200C82C
	mov r1, #0x27
	ldr r0, [r4, #0x38]
	mvn r1, r1
	mov r2, #4
	bl FUN_0200C82C
	ldr r0, [r4, #0x34]
	mov r1, #0x20
	mov r2, #0
	bl FUN_0200C82C
	ldr r0, [r4, #0x30]
	mov r1, #0x28
	mov r2, #4
	bl FUN_0200C82C
	ldr r0, [r4, #0x2c]
	bl FUN_0200C68C
	str r0, [r4, #0x1c]
	ldr r0, [r4, #4]
	ldr r1, _02220A04 ; =MOD08_02220614
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02220A04: .word MOD08_02220614

	thumb_func_start MOD08_02220A08
MOD08_02220A08: ; 0x02220A08
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	bne _02220A8E
	add r0, r4, #0
	add r0, #0x60
	bl MOD08_02218224
	cmp r0, #0
	bne _02220A4C
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0x3c]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0x3c]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl MOD08_02228094
	add sp, #0xc
	pop {r4, r5, pc}
_02220A4C:
	add r0, r4, #0
	add r0, #0x60
	add r1, sp, #8
	add r2, sp, #4
	bl MOD08_0221825C
	ldr r0, [r4, #0x28]
	ldr r1, [sp, #8]
	ldr r2, [sp, #4]
	bl FUN_0200C884
	mov r0, #0
	str r0, [sp]
	mov r1, #0x58
	mov r2, #0x5a
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x28]
	ldr r3, [r4, #0x74]
	bl MOD08_02218314
	ldr r0, [r4, #0x28]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x3c]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x50]
	bl FUN_0200C5A8
	ldr r0, [r4, #0xc]
	bl FUN_0200BC1C
_02220A8E:
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02220A94
MOD08_02220A94: ; 0x02220A94
	push {r4, r5, lr}
	sub sp, #0xc
	mov r1, #0x84
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02227B70
	ldr r0, [r4, #4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_022154D4
	mov r1, #1
	str r0, [r4, #0x24]
	bl FUN_0200782C
	add r1, r4, #0
	add r1, #0x58
	strh r0, [r1]
	mov r0, #0x58
	ldrsh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0x5c
	strh r1, [r0]
	ldr r0, [r4, #4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_0221552C
	add r1, r4, #0
	add r1, #0x5a
	strh r0, [r1]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_022124D8
	str r0, [r4, #0x28]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_022124D8
	str r0, [r4, #0x3c]
	add r0, r5, #0
	mov r1, #2
	bl MOD08_022124D8
	str r0, [r4, #0x50]
	ldr r0, [r4, #0x28]
	mov r1, #2
	bl FUN_0200C840
	add r0, r5, #0
	bl MOD08_02215574
	add r1, r0, #0
	ldr r0, [r4, #0x28]
	bl FUN_0200C6B0
	add r0, r5, #0
	bl MOD08_02215574
	add r1, r0, #0
	ldr r0, [r4, #0x3c]
	bl FUN_0200C6B0
	add r0, r5, #0
	bl MOD08_02215574
	add r1, r0, #0
	ldr r0, [r4, #0x50]
	bl FUN_0200C6B0
	ldr r0, [r4, #4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_02215490
	sub r0, r0, #3
	cmp r0, #1
	ldr r0, [r4, #0x28]
	bhi _02220B62
	mov r1, #0x1e
	bl FUN_0200C6C4
	ldr r0, [r4, #0x3c]
	mov r1, #0x32
	bl FUN_0200C6C4
	ldr r0, [r4, #0x50]
	mov r1, #0x46
	bl FUN_0200C6C4
	b _02220B78
_02220B62:
	mov r1, #0x3c
	bl FUN_0200C6C4
	ldr r0, [r4, #0x3c]
	mov r1, #0x46
	bl FUN_0200C6C4
	ldr r0, [r4, #0x50]
	mov r1, #0x32
	bl FUN_0200C6C4
_02220B78:
	mov r2, #0x14
	mov r1, #0x64
	str r2, [sp]
	str r1, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x60
	add r3, r1, #0
	bl MOD08_022181A8
	ldr r0, [r4, #4]
	ldr r1, _02220B9C ; =MOD08_02220A08
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02220B9C: .word MOD08_02220A08

	thumb_func_start MOD08_02220BA0
MOD08_02220BA0: ; 0x02220BA0
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r2, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _02220BB4
	cmp r0, #1
	beq _02220CB2
	b _02220D00
_02220BB4:
	add r0, r4, #0
	add r0, #0xa0
	ldrb r0, [r0]
	cmp r0, #0
	bne _02220C2E
	mov r0, #0x22
	ldrsh r3, [r4, r0]
	mov r0, #0x20
	ldrsh r1, [r4, r0]
	mov r0, #3
	add r2, r1, #0
	str r3, [sp]
	add r2, #0x30
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r2, r2, #0x10
	add r0, #0x34
	asr r2, r2, #0x10
	bl MOD08_02217E80
	mov r0, #0x22
	ldrsh r1, [r4, r0]
	mov r0, #0xa4
	ldrsh r0, [r4, r0]
	add r2, r1, r0
	mov r0, #0x20
	ldrsh r1, [r4, r0]
	lsl r0, r2, #0x10
	asr r3, r0, #0x10
	add r2, r1, #0
	add r2, #0x30
	lsl r2, r2, #0x10
	str r3, [sp]
	mov r0, #6
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x58
	asr r2, r2, #0x10
	bl MOD08_02217E80
	mov r0, #0x22
	ldrsh r1, [r4, r0]
	mov r0, #0xa4
	ldrsh r0, [r4, r0]
	add r2, r1, r0
	mov r0, #0x20
	ldrsh r1, [r4, r0]
	lsl r0, r2, #0x10
	asr r3, r0, #0x10
	add r2, r1, #0
	add r2, #0x30
	lsl r2, r2, #0x10
	str r3, [sp]
	mov r0, #8
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x7c
	asr r2, r2, #0x10
	bl MOD08_02217E80
	b _02220C9C
_02220C2E:
	mov r0, #0x22
	ldrsh r3, [r4, r0]
	mov r0, #0x20
	ldrsh r2, [r4, r0]
	mov r0, #3
	add r1, r2, #0
	str r3, [sp]
	add r1, #0x30
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r1, r1, #0x10
	add r0, #0x34
	asr r1, r1, #0x10
	bl MOD08_02217E80
	mov r0, #0x22
	ldrsh r1, [r4, r0]
	mov r0, #0xa4
	ldrsh r0, [r4, r0]
	add r1, r1, r0
	mov r0, #0x20
	ldrsh r2, [r4, r0]
	lsl r0, r1, #0x10
	asr r3, r0, #0x10
	add r1, r2, #0
	add r1, #0x30
	lsl r1, r1, #0x10
	str r3, [sp]
	mov r0, #6
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x58
	asr r1, r1, #0x10
	bl MOD08_02217E80
	mov r0, #0x22
	ldrsh r1, [r4, r0]
	mov r0, #0xa4
	ldrsh r0, [r4, r0]
	add r1, r1, r0
	mov r0, #0x20
	ldrsh r2, [r4, r0]
	lsl r0, r1, #0x10
	asr r3, r0, #0x10
	add r1, r2, #0
	add r1, #0x30
	lsl r1, r1, #0x10
	str r3, [sp]
	mov r0, #9
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x7c
	asr r1, r1, #0x10
	bl MOD08_02217E80
_02220C9C:
	add r0, r4, #0
	add r0, #0xa0
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xa0
	strb r1, [r0]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _02220D12
_02220CB2:
	add r0, r4, #0
	ldr r1, [r4, #0x28]
	add r0, #0x58
	mov r5, #0
	bl MOD08_02217F08
	cmp r0, #0
	bne _02220CC4
	add r5, r5, #1
_02220CC4:
	add r0, r4, #0
	ldr r1, [r4, #0x24]
	add r0, #0x34
	bl MOD08_02217F2C
	cmp r0, #0
	bne _02220CD4
	add r5, r5, #1
_02220CD4:
	add r0, r4, #0
	ldr r1, [r4, #0x30]
	add r0, #0x7c
	bl MOD08_02217F08
	cmp r0, #0
	bne _02220CE4
	add r5, r5, #1
_02220CE4:
	cmp r5, #3
	blt _02220D12
	add r0, r4, #0
	add r0, #0xa0
	ldrb r0, [r0]
	cmp r0, #1
	ldrb r0, [r4]
	bne _02220CFA
	sub r0, r0, #1
	strb r0, [r4]
	b _02220D12
_02220CFA:
	add r0, r0, #1
	strb r0, [r4]
	b _02220D12
_02220D00:
	ldr r0, [r4, #4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl MOD08_02228094
	add sp, #8
	pop {r3, r4, r5, pc}
_02220D12:
	ldr r0, [r4, #0x28]
	bl FUN_0200C5A8
	ldr r0, [r4, #0xc]
	bl FUN_0200BC1C
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02220D24
MOD08_02220D24: ; 0x02220D24
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	mov r1, #0xa8
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02227B70
	add r0, r4, #0
	mov r1, #0
	add r0, #0xa1
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #8
	add r0, #0xa2
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0xa3
	strb r1, [r0]
	sub r1, #9
	ldr r0, [r4, #4]
	add r2, r1, #0
	bl MOD08_02227994
	add r0, r4, #0
	add r0, #0xa2
	ldrb r1, [r0]
	add r0, r4, #0
	add r0, #0xa3
	ldrb r0, [r0]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _02220E94 ; =0x04000052
	strh r1, [r0]
	ldr r0, [r4, #4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_022154D4
	str r0, [r4, #0x24]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #0x20]
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #0x22]
	ldr r0, [r4, #4]
	mov r1, #0
	bl MOD08_022124D8
	str r0, [r4, #0x28]
	ldr r0, [r4, #4]
	mov r1, #1
	bl MOD08_022124D8
	str r0, [r4, #0x30]
	ldr r0, [r4, #0x24]
	mov r1, #0x29
	bl FUN_0200782C
	neg r1, r0
	add r0, r4, #0
	add r0, #0xa4
	strh r1, [r0]
	ldr r0, [r4, #4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_0221550C
	add r7, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_0221551C
	str r0, [sp, #0x18]
	ldr r0, [r4, #4]
	ldr r5, [r4, #0x28]
	bl MOD08_02215574
	add r1, r0, #0
	add r0, r5, #0
	add r1, r1, #1
	bl FUN_0200C6B0
	ldr r0, [r5]
	bl FUN_02020354
	mov r1, #1
	bl FUN_0201E28C
	add r6, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_02215504
	str r0, [sp, #0x1c]
	ldr r0, [r4, #4]
	bl MOD08_02212014
	add r3, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	lsl r0, r6, #0x14
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	mov r0, #0xc4
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	add r2, r7, #0
	bl FUN_02003B40
	add r0, r5, #0
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r4, #4]
	ldr r5, [r4, #0x30]
	bl MOD08_02215574
	add r1, r0, #0
	add r0, r5, #0
	add r1, r1, #1
	bl FUN_0200C6B0
	ldr r0, [r5]
	bl FUN_02020354
	mov r1, #1
	bl FUN_0201E28C
	add r6, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_02215504
	str r0, [sp, #0x20]
	ldr r0, [r4, #4]
	bl MOD08_02212014
	add r3, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	lsl r0, r6, #0x14
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	mov r0, #0xc4
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x18]
	add r2, r7, #0
	bl FUN_02003B40
	add r0, r5, #0
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r4, #4]
	ldr r1, _02220E98 ; =MOD08_02220BA0
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_02220E94: .word 0x04000052
_02220E98: .word MOD08_02220BA0

	thumb_func_start MOD08_02220E9C
MOD08_02220E9C: ; 0x02220E9C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r6, #0
	str r0, [sp]
	str r1, [sp, #4]
	add r7, r6, #0
	add r4, r1, #0
	add r5, r1, #0
_02220EAC:
	mov r0, #0x1e
	ldrsh r0, [r4, r0]
	add r0, r0, #1
	strh r0, [r4, #0x1e]
	mov r0, #0x1e
	ldrsh r0, [r4, r0]
	cmp r0, #0x20
	blt _02220ED4
	ldr r0, [r5, #0x30]
	bl MOD08_022204CC
	mov r0, #0x1e
	ldrsh r0, [r4, r0]
	cmp r0, #0xa0
	blt _02220ED4
	ldr r0, [r5, #0x30]
	mov r1, #0
	bl FUN_0200C644
	add r6, r6, #1
_02220ED4:
	add r7, r7, #1
	add r4, r4, #2
	add r5, r5, #4
	cmp r7, #8
	blt _02220EAC
	cmp r6, #8
	bne _02220F08
	ldr r4, [sp, #4]
	mov r5, #0
_02220EE6:
	ldr r0, [r4, #0x30]
	bl FUN_0200C3DC
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #8
	blt _02220EE6
	ldr r0, [sp, #4]
	ldr r1, [sp]
	ldr r0, [r0, #4]
	bl MOD08_02212438
	ldr r0, [sp, #4]
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02220F08:
	ldr r0, [sp, #4]
	ldr r0, [r0, #0x10]
	bl FUN_0200BC1C
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02220F14
MOD08_02220F14: ; 0x02220F14
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x58
	mov r1, #0x74
	add r6, r0, #0
	add r5, r3, #0
	bl MOD08_02228064
	add r4, r0, #0
	mov r0, #0xa
	strh r0, [r4, #0x1c]
	add r0, r6, #0
	add r1, r4, #0
	bl MOD08_02227B70
	ldr r1, [r4, #4]
	add r0, sp, #0x24
	bl MOD08_02215474
	str r5, [r4, #0x30]
	mov r6, #1
	add r5, r4, #4
	mov r7, #0x1f
_02220F40:
	ldr r0, [r4, #8]
	ldr r1, [r4, #0x10]
	add r2, sp, #0x24
	bl FUN_0200C154
	str r0, [r5, #0x30]
	lsr r1, r6, #0x1f
	lsl r0, r6, #0x1f
	sub r0, r0, r1
	ror r0, r7
	add r0, r1, r0
	beq _02220F60
	ldr r0, [r5, #0x30]
	mov r1, #1
	bl FUN_0200C8D0
_02220F60:
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #8
	blt _02220F40
	ldr r0, [r4, #4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_022154D4
	mov r1, #0
	add r5, r0, #0
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r7, r0, #0x10
	add r0, r5, #0
	mov r1, #1
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r5, r0, #0x10
	ldr r0, [r4, #4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_022154D4
	mov r1, #0
	str r0, [sp, #0x1c]
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	ldr r0, [sp, #0x1c]
	mov r1, #1
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	mov r0, #0x14
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x50
	add r1, r7, #0
	add r2, r6, #0
	add r3, r5, #0
	bl MOD08_02217E80
	mov r7, #0
	ldr r0, [r4, #4]
	add r6, r7, #0
	str r7, [sp, #0x14]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_02227470
	cmp r0, #4
	bne _02220FE4
	mov r0, #1
	str r0, [sp, #0x14]
_02220FE4:
	add r0, r4, #0
	str r0, [sp, #0x20]
	add r0, #0x50
	add r5, r4, #0
	str r0, [sp, #0x20]
_02220FEE:
	ldr r0, [sp, #0x20]
	bl MOD08_02217ECC
	str r0, [sp, #0x18]
	lsr r2, r7, #0x1f
	lsl r1, r7, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	beq _02221026
	ldr r0, [sp, #0x14]
	cmp r0, #0
	bne _02221022
	cmp r6, #8
	bge _02221026
	mov r1, #0x50
	mov r2, #0x52
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r5, #0x30]
	bl FUN_0200C714
	add r5, r5, #4
	add r6, r6, #1
	b _02221026
_02221022:
	mov r0, #0
	str r0, [sp, #0x14]
_02221026:
	ldr r0, [sp, #0x18]
	add r7, r7, #1
	cmp r0, #1
	beq _02220FEE
	ldr r0, [r4, #4]
	mov r1, #1
	bl MOD08_02215600
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	mov r1, #2
	bl MOD08_02215600
	add r7, r0, #0
	mov r6, #0
	str r4, [sp, #0xc]
	add r5, r4, #0
_02221048:
	mov r0, #8
	sub r0, r0, r6
	str r0, [sp, #8]
	lsl r1, r0, #2
	ldr r0, [sp, #0xc]
	strh r1, [r0, #0x1e]
	ldr r0, [r4, #4]
	bl MOD08_02212004
	cmp r0, #0
	bne _022210A4
	ldr r0, [r4, #4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_02227470
	cmp r0, #3
	bne _02221086
	cmp r6, #4
	ldr r0, [r5, #0x30]
	bge _0222107E
	add r1, r7, #0
	bl FUN_0200C6B0
	b _0222109A
_0222107E:
	ldr r1, [sp, #0x10]
	bl FUN_0200C6B0
	b _0222109A
_02221086:
	cmp r6, #4
	ldr r0, [r5, #0x30]
	blt _02221094
	add r1, r7, #0
	bl FUN_0200C6B0
	b _0222109A
_02221094:
	ldr r1, [sp, #0x10]
	bl FUN_0200C6B0
_0222109A:
	ldr r0, [r5, #0x30]
	ldr r1, [sp, #8]
	bl FUN_0200C6C4
	b _022210B4
_022210A4:
	ldr r0, [r5, #0x30]
	add r1, r6, #0
	bl FUN_0200C6C4
	ldr r0, [r5, #0x30]
	add r1, r7, #0
	bl FUN_0200C6B0
_022210B4:
	ldr r0, [sp, #0xc]
	add r6, r6, #1
	add r0, r0, #2
	add r5, r5, #4
	str r0, [sp, #0xc]
	cmp r6, #8
	blt _02221048
	ldr r0, [r4, #4]
	ldr r1, _022210D0 ; =MOD08_02220E9C
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022210D0: .word MOD08_02220E9C

	thumb_func_start MOD08_022210D4
MOD08_022210D4: ; 0x022210D4
	push {r4, r5, lr}
	sub sp, #0x1c
	add r5, r1, #0
	add r4, r0, #0
	ldrb r0, [r5]
	cmp r0, #0
	beq _022210EA
	cmp r0, #1
	beq _02221178
	cmp r0, #2
	b _022211D6
_022210EA:
	ldr r0, [r5, #0x28]
	cmp r0, #0xe
	ble _02221140
	ldr r0, [r5, #0x30]
	ldr r1, _0222121C ; =0x3E4CCCCD
	bl _fsub
	str r0, [r5, #0x30]
	ldr r0, [r5, #0x2c]
	ldr r1, _0222121C ; =0x3E4CCCCD
	bl _fadd
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x30]
	bl _f2d
	ldr r2, _02221220 ; =0x9999999A
	ldr r3, _02221224 ; =0x3FC99999
	bl _dleq
	bhi _02221124
	ldrb r0, [r5]
	mov r1, #0
	add r0, r0, #1
	strb r0, [r5]
	ldr r0, [r5, #0x1c]
	bl FUN_0200C644
	b _022211FE
_02221124:
	mov r0, #0x36
	ldrsb r0, [r5, r0]
	bl _fflt
	add r1, r0, #0
	ldr r0, [r5, #0x2c]
	bl _fmul
	add r1, r0, #0
	ldr r0, [r5, #0x1c]
	ldr r2, [r5, #0x30]
	bl FUN_0200C884
	b _022211FE
_02221140:
	add r0, r5, #0
	add r0, #0x34
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0x34
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0x35
	ldrb r0, [r0]
	sub r1, r0, #1
	add r0, r5, #0
	add r0, #0x35
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0x34
	ldrb r1, [r0]
	add r0, r5, #0
	add r0, #0x35
	ldrb r0, [r0]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _02221228 ; =0x04000052
	strh r1, [r0]
	ldr r0, [r5, #0x28]
	add r0, r0, #1
	str r0, [r5, #0x28]
	b _022211FE
_02221178:
	ldr r0, [r5, #0x3c]
	bl MOD08_02218AF8
	cmp r0, #0
	bne _022211FE
	ldr r0, [r5, #0x38]
	bl MOD08_02218B08
	ldr r0, [r5, #0x3c]
	bl MOD08_02218B08
	ldr r0, [r5, #0x24]
	ldr r0, [r0]
	bl FUN_02020354
	mov r1, #1
	bl FUN_0201E28C
	add r4, r0, #0
	ldr r0, [r5, #4]
	bl MOD08_02212014
	add r1, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r2, #0
	lsl r3, r4, #0x14
	str r2, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	str r2, [sp, #0x10]
	ldr r0, _0222122C ; =0x0000FFFF
	mov r2, #2
	str r0, [sp, #0x14]
	ldr r0, _02221230 ; =0x0000044C
	lsr r3, r3, #0x10
	str r0, [sp, #0x18]
	ldr r0, [r5, #0x18]
	bl MOD08_02218B20
	str r0, [r5, #0x3c]
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
	b _022211FE
_022211D6:
	ldr r0, [r5, #0x3c]
	bl MOD08_02218AF8
	cmp r0, #0
	bne _022211FE
	ldr r0, [r5, #0x20]
	bl FUN_0200C5A8
	ldr r0, [r5, #0x3c]
	bl MOD08_02218B08
	ldr r0, [r5, #4]
	add r1, r4, #0
	bl MOD08_02212438
	add r0, r5, #0
	bl FreeToHeap
	add sp, #0x1c
	pop {r4, r5, pc}
_022211FE:
	ldr r0, [r5, #0x1c]
	bl FUN_0200C5A8
	ldr r0, [r5, #0x20]
	bl FUN_0200C5A8
	ldr r0, [r5, #0x24]
	bl FUN_0200C5A8
	ldr r0, [r5, #0xc]
	bl FUN_0200BC1C
	add sp, #0x1c
	pop {r4, r5, pc}
	nop
_0222121C: .word 0x3E4CCCCD
_02221220: .word 0x9999999A
_02221224: .word 0x3FC99999
_02221228: .word 0x04000052
_0222122C: .word 0x0000FFFF
_02221230: .word 0x0000044C

	thumb_func_start MOD08_02221234
MOD08_02221234: ; 0x02221234
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	mov r1, #0x40
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02227B70
	ldr r0, [r4, #4]
	mov r1, #0
	bl MOD08_022124D8
	str r0, [r4, #0x1c]
	ldr r0, [r4, #4]
	mov r1, #1
	bl MOD08_022124D8
	str r0, [r4, #0x20]
	ldr r0, [r4, #4]
	mov r1, #2
	bl MOD08_022124D8
	str r0, [r4, #0x24]
	mov r6, #0
	str r6, [r4, #0x28]
	add r0, r5, #0
	sub r6, #0x20
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_02217C1C
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	mul r0, r6
	add r6, r0, #0
	mov r0, #0xfe
	lsl r0, r0, #0x16
	str r0, [r4, #0x2c]
	str r0, [r4, #0x30]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02215680
	cmp r0, #1
	bne _0222129E
	mov r1, #0
	mvn r1, r1
	b _022212A0
_0222129E:
	mov r1, #1
_022212A0:
	add r0, r4, #0
	add r0, #0x36
	strb r1, [r0]
	add r1, sp, #0x24
	ldr r0, [r4, #0x20]
	add r1, #2
	add r2, sp, #0x24
	bl FUN_0200C7A0
	add r2, sp, #0x24
	mov r1, #2
	ldrsh r1, [r2, r1]
	mov r3, #0
	ldrsh r2, [r2, r3]
	add r1, r1, r6
	lsl r1, r1, #0x10
	ldr r0, [r4, #0x1c]
	asr r1, r1, #0x10
	bl FUN_0200C714
	ldr r0, [r4, #0x1c]
	mov r1, #2
	bl FUN_0200C840
	mov r0, #0x36
	ldrsb r0, [r4, r0]
	bl _fflt
	add r1, r0, #0
	ldr r0, [r4, #0x2c]
	bl _fmul
	add r1, r0, #0
	ldr r0, [r4, #0x1c]
	ldr r2, [r4, #0x30]
	bl FUN_0200C884
	ldr r0, [r4, #0x1c]
	ldr r0, [r0]
	bl FUN_02020354
	mov r1, #1
	bl FUN_0201E28C
	add r6, r0, #0
	add r0, r5, #0
	bl MOD08_02212014
	add r1, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r2, #0
	lsl r3, r6, #0x14
	str r2, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	mov r0, #0xf
	str r0, [sp, #0x10]
	ldr r0, _0222147C ; =0x0000FFFF
	mov r2, #2
	str r0, [sp, #0x14]
	ldr r0, _02221480 ; =0x0000044C
	lsr r3, r3, #0x10
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x18]
	bl MOD08_02218B20
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x24]
	ldr r0, [r0]
	bl FUN_02020354
	mov r1, #1
	bl FUN_0201E28C
	add r6, r0, #0
	add r0, r5, #0
	bl MOD08_02212014
	add r1, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r2, #0
	lsl r3, r6, #0x14
	str r2, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	mov r0, #0xf
	str r0, [sp, #0x10]
	ldr r0, _0222147C ; =0x0000FFFF
	mov r2, #2
	str r0, [sp, #0x14]
	ldr r0, _02221480 ; =0x0000044C
	lsr r3, r3, #0x10
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x18]
	bl MOD08_02218B20
	str r0, [r4, #0x3c]
	ldr r0, [r4, #4]
	bl MOD08_02212458
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldr r0, [r4, #4]
	add r1, r6, #0
	bl MOD08_02227468
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	ldr r0, [r4, #4]
	bl MOD08_02212004
	add r1, r0, #0
	add r0, r5, #0
	add r2, sp, #0x2c
	bl MOD08_02227564
	add r2, sp, #0x28
	ldr r0, [r4, #0x1c]
	add r1, sp, #0x28
	add r2, #2
	bl FUN_0200C7A0
	ldr r0, [r4, #4]
	add r1, r6, #0
	bl MOD08_02227470
	cmp r0, #3
	bne _022213BC
	ldr r0, [r4, #0x1c]
	mov r1, #1
	mov r5, #0
	bl FUN_0200C6B0
	ldr r0, [r4, #0x1c]
	add r1, r5, #0
	bl FUN_0200C6C4
	b _022213CE
_022213BC:
	ldr r0, [r4, #0x1c]
	mov r1, #2
	bl FUN_0200C6B0
	ldr r0, [r4, #0x1c]
	mov r1, #0
	bl FUN_0200C6C4
	mov r5, #2
_022213CE:
	ldr r0, [r4, #4]
	bl MOD08_02212460
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldr r0, [r4, #4]
	add r1, r6, #0
	bl MOD08_022154A8
	add r7, r0, #0
	ldr r0, [r4, #4]
	add r1, r6, #0
	bl MOD08_0221549C
	str r0, [sp, #0x1c]
	ldr r0, [r4, #4]
	add r1, r6, #0
	bl MOD08_022154B8
	str r0, [sp, #0x20]
	ldr r0, [r4, #4]
	add r1, r6, #0
	bl MOD08_022154C4
	ldr r1, [sp, #0x1c]
	ldr r3, [sp, #0x20]
	str r0, [sp]
	lsl r0, r7, #0x10
	lsl r1, r1, #0x18
	lsl r2, r5, #0x18
	lsl r3, r3, #0x18
	lsr r0, r0, #0x10
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02068E88
	add r2, r0, #0
	add r5, sp, #0x24
	mov r3, #0xa
	ldrsh r3, [r5, r3]
	mov r1, #4
	ldrsh r1, [r5, r1]
	add r2, r3, r2
	lsl r2, r2, #0x10
	ldr r0, [r4, #0x1c]
	asr r2, r2, #0x10
	bl FUN_0200C714
	ldr r0, [r4, #0x1c]
	mov r1, #1
	bl FUN_0200C644
	add r0, r4, #0
	mov r1, #0
	add r0, #0x34
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #0xf
	add r0, #0x35
	strb r1, [r0]
	sub r1, #0x10
	ldr r0, [r4, #4]
	add r2, r1, #0
	bl MOD08_02227994
	add r0, r4, #0
	add r0, #0x34
	ldrb r1, [r0]
	add r0, r4, #0
	add r0, #0x35
	ldrb r0, [r0]
	add r2, r4, #0
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _02221484 ; =0x04000052
	strh r1, [r0]
	ldr r0, [r4, #4]
	ldr r1, _02221488 ; =MOD08_022210D4
	bl MOD08_02212400
	add r1, r4, #0
	bl MOD08_022210D4
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222147C: .word 0x0000FFFF
_02221480: .word 0x0000044C
_02221484: .word 0x04000052
_02221488: .word MOD08_022210D4

	thumb_func_start MOD08_0222148C
MOD08_0222148C: ; 0x0222148C
	push {r3, r4, r5, lr}
	sub sp, #0x58
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _022214A0
	cmp r0, #1
	beq _022214E6
	b _02221560
_022214A0:
	ldr r0, [r4, #0x68]
	mov r1, #0x20
	lsl r0, r0, #2
	add r2, r4, r0
	ldr r0, [r2, #0x78]
	lsl r0, r0, #0x10
	asr r3, r0, #0x10
	str r3, [sp]
	mov r0, #0xf
	str r0, [sp, #4]
	ldr r2, [r2, #0x6c]
	add r0, r4, #0
	lsl r2, r2, #0x10
	ldrsh r1, [r4, r1]
	add r0, #0x30
	asr r2, r2, #0x10
	bl MOD08_02217E80
	ldr r2, [r4, #0x68]
	ldr r0, [r4, #0x24]
	lsl r2, r2, #2
	add r2, r4, r2
	add r2, #0x84
	ldr r2, [r2]
	mov r1, #2
	bl FUN_02007558
	ldr r0, [r4, #0x24]
	mov r1, #0x2c
	mov r2, #1
	bl FUN_02007558
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_022214E6:
	add r0, r4, #0
	add r0, #0x30
	bl MOD08_02217ECC
	cmp r0, #0
	bne _02221544
	ldr r0, [r4, #0x68]
	add r0, r0, #1
	str r0, [r4, #0x68]
	cmp r0, #2
	ble _02221504
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _0222153A
_02221504:
	ldr r0, [r4, #0x58]
	cmp r0, #0
	bne _02221536
	ldr r0, [r4, #4]
	add r1, sp, #8
	mov r2, #3
	bl MOD08_022127A8
	ldr r0, [r4, #0x68]
	cmp r0, #2
	ldr r0, [r4, #4]
	bne _0222152A
	bl MOD08_02212014
	add r1, r0, #0
	add r0, sp, #8
	bl MOD08_0222A494
	b _02221536
_0222152A:
	bl MOD08_02212014
	add r1, r0, #0
	add r0, sp, #8
	bl MOD08_0222A2A4
_02221536:
	mov r0, #0
	strb r0, [r4]
_0222153A:
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #0x20]
_02221544:
	mov r2, #0x30
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl FUN_02007558
	mov r2, #0x32
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl FUN_02007558
	add sp, #0x58
	pop {r3, r4, r5, pc}
_02221560:
	ldr r0, [r4, #0x24]
	mov r1, #0x2c
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4, #4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x58
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_0222157C
MOD08_0222157C: ; 0x0222157C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	mov r1, #0x90
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02227B70
	ldr r0, [r4, #4]
	bl MOD08_02212458
	add r6, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_02212458
	add r1, r0, #0
	add r2, r4, #0
	ldr r0, [r4, #4]
	add r2, #0x5c
	bl MOD08_022275C0
	ldr r0, [r4, #4]
	bl MOD08_02212460
	add r1, r0, #0
	add r2, r4, #0
	ldr r0, [r4, #4]
	add r2, #0x60
	bl MOD08_022275C0
	ldr r0, [r4, #4]
	add r1, r6, #0
	bl MOD08_02227470
	cmp r0, #3
	bne _022215CE
	mov r1, #1
	b _022215D2
_022215CE:
	mov r1, #0
	mvn r1, r1
_022215D2:
	add r0, r4, #0
	add r0, #0x54
	strh r1, [r0]
	ldr r0, [r4, #4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_02227470
	add r6, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_02227470
	cmp r6, r0
	bne _022215FE
	mov r0, #1
	b _02221600
_022215FE:
	mov r0, #0
_02221600:
	str r0, [r4, #0x58]
	mov r1, #0
	add r0, r5, #0
	str r1, [r4, #0x68]
	bl MOD08_02212498
	add r2, r4, #0
	add r1, r0, #0
	add r0, r5, #0
	add r2, #0x1c
	add r3, sp, #0
	bl MOD08_02227BAC
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl FUN_0200782C
	mov r1, #0x5e
	ldrsh r2, [r4, r1]
	mov r3, #0x54
	sub r0, r0, r2
	ldrsh r2, [r4, r3]
	cmp r2, #0
	ble _02221672
	add r2, r3, #0
	add r2, #0xfb
	str r2, [r4, #0x6c]
	sub r3, #0xa4
	str r3, [r4, #0x70]
	mov r2, #0x5c
	ldrsh r2, [r4, r2]
	str r2, [r4, #0x74]
	ldrsh r2, [r4, r1]
	add r2, r2, r0
	str r2, [r4, #0x78]
	mov r2, #0x62
	ldrsh r2, [r4, r2]
	add r2, r2, r0
	str r2, [r4, #0x7c]
	ldrsh r1, [r4, r1]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	mov r1, #0xa
	add r0, #0x84
	str r1, [r0]
	add r0, r4, #0
	ldr r1, _022216C8 ; =0xFFFFFD76
	add r0, #0x88
	str r1, [r0]
	ldr r0, [r4, #0x24]
	mov r1, #2
	bl FUN_0200782C
	b _022216B2
_02221672:
	add r2, r3, #0
	sub r2, #0xa4
	str r2, [r4, #0x6c]
	add r3, #0xfb
	str r3, [r4, #0x70]
	mov r2, #0x5c
	ldrsh r2, [r4, r2]
	str r2, [r4, #0x74]
	ldrsh r2, [r4, r1]
	add r2, r2, r0
	str r2, [r4, #0x78]
	mov r2, #0x62
	ldrsh r2, [r4, r2]
	add r2, r2, r0
	str r2, [r4, #0x7c]
	ldrsh r1, [r4, r1]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	ldr r1, _022216C8 ; =0xFFFFFD76
	add r0, #0x84
	str r1, [r0]
	add r0, r4, #0
	mov r1, #0xa
	add r0, #0x88
	str r1, [r0]
	ldr r0, [r4, #0x24]
	mov r1, #2
	bl FUN_0200782C
_022216B2:
	add r1, r4, #0
	add r1, #0x8c
	str r0, [r1]
	ldr r0, [r4, #4]
	ldr r1, _022216CC ; =MOD08_0222148C
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_022216C8: .word 0xFFFFFD76
_022216CC: .word MOD08_0222148C

	thumb_func_start MOD08_022216D0
MOD08_022216D0: ; 0x022216D0
	push {r3, r4, lr}
	sub sp, #4
	add r4, r2, #0
	ldr r2, [sp, #0x10]
	str r2, [sp]
	mov r2, #0x50
	sub r2, r2, r3
	add r3, r4, #0
	bl FUN_02007E40
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD08_022216E8
MOD08_022216E8: ; 0x022216E8
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r1, #0
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #3
	bls _022216FC
	b _0222181E
_022216FC:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02221708: ; jump table
	.short _02221710 - _02221708 - 2 ; case 0
	.short _0222176C - _02221708 - 2 ; case 1
	.short _022217AE - _02221708 - 2 ; case 2
	.short _02221804 - _02221708 - 2 ; case 3
_02221710:
	ldr r2, [r4, #0x10]
	add r2, #0x4f
	str r2, [r4, #0x10]
	cmp r2, #0x50
	blt _02221738
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	add sp, #4
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x20
	strb r1, [r0]
	ldr r1, [r4, #0x14]
	mov r0, #1
	eor r0, r1
	str r0, [r4, #0x14]
	mov r0, #0
	str r0, [r4, #0x10]
	pop {r3, r4, r5, r6, pc}
_02221738:
	ldr r0, [r4, #0x14]
	cmp r0, #0
	bne _02221754
	mov r0, #2
	str r0, [sp]
	ldr r3, [r4]
	ldr r0, [r4, #0x1c]
	add r3, r3, #2
	mov r1, #0
	lsl r3, r3, #1
	bl MOD08_022216D0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_02221754:
	mov r0, #2
	str r0, [sp]
	ldr r3, [r4]
	mov r1, #0x50
	add r3, r3, #2
	ldr r0, [r4, #0x1c]
	sub r1, r1, r2
	lsl r3, r3, #1
	bl MOD08_022216D0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0222176C:
	ldr r0, [r4, #4]
	mov r3, #0xff
	sub r0, r0, #1
	str r0, [r4, #4]
	ldr r0, [r4, #0xc]
	lsl r3, r3, #8
	add r2, r0, #1
	str r2, [r4, #0xc]
	ldr r6, [r4, #8]
	ldr r1, [r4, #4]
	lsl r0, r6, #8
	add r5, r0, #0
	add r6, #0x50
	lsl r0, r6, #0x18
	and r5, r3
	lsr r0, r0, #0x18
	lsl r1, r1, #8
	orr r5, r0
	ldr r0, _02221868 ; =0x04000040
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	strh r5, [r0]
	orr r1, r3
	strh r1, [r0, #4]
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r4, #0x20
	add sp, #4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_022217AE:
	ldr r0, [r4, #4]
	mov r3, #0xff
	sub r0, r0, #1
	str r0, [r4, #4]
	ldr r0, [r4, #0xc]
	lsl r3, r3, #8
	add r2, r0, #1
	str r2, [r4, #0xc]
	ldr r6, [r4, #8]
	ldr r1, [r4, #4]
	lsl r0, r6, #8
	add r5, r0, #0
	add r6, #0x50
	lsl r0, r6, #0x18
	and r5, r3
	lsr r0, r0, #0x18
	lsl r1, r1, #8
	orr r5, r0
	ldr r0, _02221868 ; =0x04000040
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	strh r5, [r0]
	orr r1, r3
	strh r1, [r0, #4]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	cmp r0, #0x26
	ble _022217FA
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r4, #0x20
	add sp, #4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_022217FA:
	mov r0, #0
	add r4, #0x20
	add sp, #4
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_02221804:
	ldr r0, [r4, #0x1c]
	mov r1, #0xe
	mov r2, #0
	bl FUN_02007558
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r4, #0x20
	add sp, #4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0222181E:
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r3, [r0]
	ldr r1, _0222186C ; =0xFFFF1FFF
	and r1, r3
	add r3, r0, #0
	str r1, [r0]
	add r3, #0x48
	ldrh r5, [r3]
	mov r1, #0x3f
	bic r5, r1
	strh r5, [r3]
	add r3, r0, #0
	add r3, #0x4a
	ldrh r5, [r3]
	bic r5, r1
	add r1, r0, #0
	strh r5, [r3]
	mov r3, #0
	add r1, #0x40
	strh r3, [r1]
	add r0, #0x44
	strh r3, [r0]
	ldr r0, [r4, #0x24]
	add r1, r2, #0
	bl MOD08_02212438
	ldr r0, [r4, #0x1c]
	ldr r2, [r4, #0x18]
	mov r1, #0x17
	bl FUN_02007558
	add r0, r4, #0
	bl FreeToHeap
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02221868: .word 0x04000040
_0222186C: .word 0xFFFF1FFF

	thumb_func_start MOD08_02221870
MOD08_02221870: ; 0x02221870
	push {r4, r5, r6, lr}
	mov r1, #0x50
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x20
	bl MOD08_02227B70
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_022154D4
	str r0, [r4, #0x1c]
	mov r0, #0
	str r0, [r4]
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_02227468
	cmp r0, #3
	beq _022218B0
	cmp r0, #4
	bne _022218C4
_022218B0:
	add r0, r5, #0
	bl MOD08_02215574
	add r1, r0, #0
	sub r1, r1, #1
	lsl r1, r1, #0x18
	mov r0, #2
	lsr r1, r1, #0x18
	bl FUN_020178BC
_022218C4:
	ldr r0, [r4, #0x1c]
	mov r1, #0
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	ldr r0, [r4, #0x1c]
	mov r1, #1
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r5, r0, #0x10
	ldr r0, [r4, #0x1c]
	mov r1, #0x29
	bl FUN_0200782C
	sub r0, r5, r0
	lsl r0, r0, #0x10
	asr r5, r0, #0x10
	ldr r0, [r4, #0x1c]
	mov r1, #0x17
	bl FUN_0200782C
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x1c]
	mov r1, #0x17
	mov r2, #8
	bl FUN_02007558
	sub r6, #0x28
	str r6, [r4, #8]
	add r5, #0x28
	mov r6, #1
	lsl r6, r6, #0x1a
	add r3, r6, #0
	str r5, [r4, #4]
	mov r1, #0
	str r1, [r4, #0x10]
	ldr r0, [r4, #4]
	add r3, #0x48
	str r0, [r4, #0xc]
	str r1, [r4, #0x14]
	ldr r1, [r6]
	ldr r0, _0222197C ; =0xFFFF1FFF
	and r1, r0
	lsr r0, r6, #0xd
	orr r0, r1
	str r0, [r6]
	ldrh r2, [r3]
	mov r1, #0x3f
	mov r0, #0x1f
	bic r2, r1
	orr r0, r2
	mov r2, #0x20
	orr r0, r2
	strh r0, [r3]
	add r3, r6, #0
	add r3, #0x4a
	ldrh r5, [r3]
	mov r0, #0x1b
	bic r5, r1
	orr r0, r5
	orr r0, r2
	strh r0, [r3]
	ldr r2, [r4, #8]
	mov r0, #0xff
	lsl r1, r2, #8
	add r2, #0x50
	lsl r0, r0, #8
	lsl r2, r2, #0x18
	and r1, r0
	lsr r2, r2, #0x18
	orr r2, r1
	add r1, r6, #0
	ldr r5, [r4, #0xc]
	ldr r3, [r4, #4]
	add r1, #0x40
	strh r2, [r1]
	lsl r1, r3, #8
	and r1, r0
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	add r6, #0x44
	strh r0, [r6]
	ldr r0, [r4, #0x24]
	ldr r1, _02221980 ; =MOD08_022216E8
	add r2, r4, #0
	bl MOD08_02212400
	pop {r4, r5, r6, pc}
	nop
_0222197C: .word 0xFFFF1FFF
_02221980: .word MOD08_022216E8

	thumb_func_start MOD08_02221984
MOD08_02221984: ; 0x02221984
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	mov r1, #0xe8
	mov r2, #0xea
	add r5, r0, #0
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r3, [r4, #8]
	add r0, #0xc
	bl MOD08_02217E58
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x38
	bl MOD08_02218524
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	bl FUN_0200BC1C
	mov r1, #0
	add r2, sp, #0
_022219B8:
	ldr r0, [r2]
	cmp r0, #1
	beq _022219EE
	add r1, r1, #1
	add r2, r2, #4
	cmp r1, #3
	blt _022219B8
	mov r2, #0xe8
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #8]
	mov r1, #0
	bl FUN_02007558
	mov r2, #0xea
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #8]
	mov r1, #1
	sub r2, #8
	bl FUN_02007558
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_022219EE:
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_022219F4
MOD08_022219F4: ; 0x022219F4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	add r5, r0, #0
	bl MOD08_02212014
	mov r1, #0xf0
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	add r0, r5, #0
	bl MOD08_02212504
	str r0, [r4, #4]
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	mov r1, #0
	str r0, [r4, #8]
	bl FUN_0200782C
	add r1, r4, #0
	add r1, #0xe8
	strh r0, [r1]
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_0200782C
	add r1, r4, #0
	add r1, #0xea
	strh r0, [r1]
	ldr r0, [r4, #8]
	mov r1, #0x29
	bl FUN_0200782C
	add r1, r4, #0
	add r1, #0xec
	strh r0, [r1]
	mov r0, #0xea
	ldrsh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xea
	add r1, #8
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0xc
	mov r1, #1
	mov r2, #8
	bl MOD08_02218654
	add r0, sp, #0x20
	mov r1, #1
	mov r2, #0xa
	bl MOD08_02218654
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02217C1C
	ldr r1, [r4, #0x18]
	mov r6, #0
	add r2, r1, #0
	mul r2, r0
	str r2, [r4, #0x18]
	ldr r1, [sp, #0x2c]
	add r5, r4, #0
	mul r0, r1
	str r0, [sp, #0x2c]
	mov r7, #0x64
_02221A8C:
	ldr r0, [r4]
	add r1, r6, #0
	bl MOD08_022124D8
	str r0, [r5, #0x30]
	add r1, r7, #0
	bl FUN_0200C6C4
	ldr r0, [r5, #0x30]
	mov r1, #1
	bl FUN_0200C6B0
	ldr r0, [r5, #0x30]
	mov r1, #1
	bl FUN_0200C90C
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _02221A8C
	mov r0, #0xea
	ldrsh r1, [r4, r0]
	mov r0, #0xec
	ldrsh r0, [r4, r0]
	mov r3, #0xe8
	ldr r2, _02221B04 ; =MOD08_02217D98
	sub r0, r1, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4, #0x30]
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x34]
	str r0, [sp, #0x14]
	str r1, [sp, #0x18]
	str r1, [sp, #0x1c]
	add r0, r4, #0
	ldrsh r3, [r4, r3]
	add r0, #0x38
	add r1, sp, #0x20
	bl MOD08_0221847C
	mov r1, #0
	mvn r1, r1
	ldr r0, [r4]
	add r2, r1, #0
	bl MOD08_02227994
	ldr r0, [r4]
	ldr r1, _02221B08 ; =MOD08_02221984
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02221B04: .word MOD08_02217D98
_02221B08: .word MOD08_02221984

	thumb_func_start MOD08_02221B0C
MOD08_02221B0C: ; 0x02221B0C
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #6
	bls _02221B1C
	b _02221C62
_02221B1C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02221B28: ; jump table
	.short _02221B36 - _02221B28 - 2 ; case 0
	.short _02221B78 - _02221B28 - 2 ; case 1
	.short _02221BAE - _02221B28 - 2 ; case 2
	.short _02221BC6 - _02221B28 - 2 ; case 3
	.short _02221BF6 - _02221B28 - 2 ; case 4
	.short _02221C0E - _02221B28 - 2 ; case 5
	.short _02221C32 - _02221B28 - 2 ; case 6
_02221B36:
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_02217ECC
	cmp r0, #0
	beq _02221B58
	mov r2, #0x48
	mov r3, #0x4a
	add r0, r4, #0
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	ldr r1, [r4, #0xc]
	add r0, #0x10
	bl MOD08_02217CD0
	add sp, #8
	pop {r3, r4, r5, pc}
_02221B58:
	mov r2, #0
	str r2, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r1, #0x10
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	add r0, #0x10
	add r3, r2, #0
	bl MOD08_02217E80
	ldr r0, [r4, #4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_02221B78:
	add r0, r4, #0
	add r0, #0x34
	bl MOD08_02218058
	cmp r0, #0
	beq _02221B92
	ldr r0, [r4, #0xc]
	ldr r2, [r4, #0x34]
	mov r1, #9
	bl FUN_02007558
	add sp, #8
	pop {r3, r4, r5, pc}
_02221B92:
	add r0, r4, #0
	ldr r1, [r4, #0x34]
	add r0, #0x34
	mov r2, #0
	mov r3, #4
	bl MOD08_02218008
	ldr r0, [r4, #4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #2
	strh r0, [r4, #8]
	pop {r3, r4, r5, pc}
_02221BAE:
	mov r0, #8
	ldrsh r1, [r4, r0]
	sub r1, r1, #1
	strh r1, [r4, #8]
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bge _02221C62
	ldr r0, [r4, #4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_02221BC6:
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_02217ECC
	cmp r0, #0
	beq _02221BE8
	mov r2, #0x48
	mov r3, #0x4a
	add r0, r4, #0
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	ldr r1, [r4, #0xc]
	add r0, #0x10
	bl MOD08_02217CD0
	add sp, #8
	pop {r3, r4, r5, pc}
_02221BE8:
	ldr r0, [r4, #4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0x20
	strh r0, [r4, #8]
	pop {r3, r4, r5, pc}
_02221BF6:
	mov r0, #8
	ldrsh r1, [r4, r0]
	sub r1, r1, #1
	strh r1, [r4, #8]
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bge _02221C62
	ldr r0, [r4, #4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_02221C0E:
	add r0, r4, #0
	add r0, #0x34
	bl MOD08_02218058
	cmp r0, #0
	beq _02221C28
	ldr r0, [r4, #0xc]
	ldr r2, [r4, #0x34]
	mov r1, #9
	bl FUN_02007558
	add sp, #8
	pop {r3, r4, r5, pc}
_02221C28:
	ldr r0, [r4, #4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_02221C32:
	mov r2, #0x48
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl FUN_02007558
	mov r2, #0x4a
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_02007558
	ldr r0, [r4, #0xc]
	mov r1, #9
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_02221C62:
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02221C68
MOD08_02221C68: ; 0x02221C68
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	bl MOD08_02212014
	mov r1, #0xf0
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	mov r0, #0
	str r0, [r4, #4]
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	mov r1, #0
	str r0, [r4, #0xc]
	bl FUN_0200782C
	add r1, r4, #0
	add r1, #0x48
	strh r0, [r1]
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0200782C
	add r1, r4, #0
	add r1, #0x4a
	strh r0, [r1]
	mov r1, #0
	add r0, r4, #0
	str r1, [sp]
	mov r2, #3
	str r2, [sp, #4]
	add r0, #0x10
	sub r2, #0x23
	add r3, r1, #0
	bl MOD08_02217E80
	add r0, r4, #0
	ldr r2, _02221D78 ; =0x00000E38
	add r0, #0x34
	mov r1, #0
	mov r3, #8
	bl MOD08_02218008
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02217C1C
	ldr r1, [r4, #0x18]
	add r2, r1, #0
	mul r2, r0
	str r2, [r4, #0x18]
	ldr r1, [r4, #0x3c]
	mul r0, r1
	str r0, [r4, #0x3c]
	ldr r0, [r4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02217C1C
	add r7, r0, #0
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_02227470
	add r6, r0, #0
	ldr r0, [r4]
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_02227470
	cmp r6, #3
	bne _02221D36
	cmp r0, #3
	bne _02221D36
	mov r1, #0xa
	add r2, r1, #0
	ldr r0, [r4, #0xc]
	sub r2, #0x32
	bl FUN_02007558
	ldr r0, [r4, #0xc]
	mov r1, #0xb
	mov r2, #0x28
	bl FUN_02007558
	b _02221D6A
_02221D36:
	cmp r6, #4
	bne _02221D54
	cmp r0, #4
	bne _02221D54
	ldr r0, [r4, #0xc]
	mov r1, #0xa
	mov r2, #0x28
	bl FUN_02007558
	ldr r0, [r4, #0xc]
	mov r1, #0xb
	mov r2, #0x28
	bl FUN_02007558
	b _02221D6A
_02221D54:
	mov r2, #0x28
	ldr r0, [r4, #0xc]
	mov r1, #0xa
	mul r2, r7
	bl FUN_02007558
	ldr r0, [r4, #0xc]
	mov r1, #0xb
	mov r2, #0x28
	bl FUN_02007558
_02221D6A:
	ldr r0, [r4]
	ldr r1, _02221D7C ; =MOD08_02221B0C
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02221D78: .word 0x00000E38
_02221D7C: .word MOD08_02221B0C

	thumb_func_start MOD08_02221D80
MOD08_02221D80: ; 0x02221D80
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, r1, #0
	add r1, r2, #0
	add r2, r3, #0
	ldr r4, [sp, #0x10]
	bl FUN_0200C154
	str r0, [r5]
	add r6, r4, #4
	add r3, r5, #4
	mov r2, #4
_02221D98:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02221D98
	ldr r0, [r6]
	add r2, r5, #0
	str r0, [r3]
	add r3, r4, #0
	add r3, #0x28
	ldmia r3!, {r0, r1}
	add r2, #0x28
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	mov r0, #0x3c
	ldrsh r0, [r4, r0]
	strh r0, [r5, #0x3c]
	mov r0, #0x3e
	ldrsh r0, [r4, r0]
	strh r0, [r5, #0x3e]
	mov r0, #0x40
	ldrsh r1, [r4, r0]
	add r0, r5, #0
	add r0, #0x40
	strh r1, [r0]
	ldr r0, [r4, #0x44]
	mov r1, #0
	str r0, [r5, #0x44]
	str r1, [r5, #0x48]
	ldr r0, [r5]
	bl FUN_0200C644
	ldr r0, [r5]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r5]
	mov r1, #1
	bl FUN_0200C6B0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_02221DF0
MOD08_02221DF0: ; 0x02221DF0
	ldr r3, _02221DF8 ; =FUN_0200C3DC
	ldr r0, [r0]
	bx r3
	nop
_02221DF8: .word FUN_0200C3DC

	thumb_func_start MOD08_02221DFC
MOD08_02221DFC: ; 0x02221DFC
	ldr r3, _02221E04 ; =FUN_0200C644
	ldr r0, [r0]
	bx r3
	nop
_02221E04: .word FUN_0200C644

	thumb_func_start MOD08_02221E08
MOD08_02221E08: ; 0x02221E08
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, [r4, #0x48]
	cmp r0, #0
	bne _02221E1A
	add sp, #0x10
	mov r0, #1
	pop {r4, pc}
_02221E1A:
	ldr r0, [r4, #0x44]
	cmp r0, #0
	beq _02221E2A
	cmp r0, #1
	beq _02221E2A
	cmp r0, #2
	beq _02221EAC
	b _02221EB2
_02221E2A:
	add r0, r4, #4
	bl MOD08_02217D98
	cmp r0, #0
	beq _02221E6A
	add r0, r4, #0
	add r0, #0x28
	bl MOD08_022180C4
	mov r0, #0x3c
	ldrsh r1, [r4, r0]
	ldr r0, [r4, #0x28]
	add r0, r1, r0
	str r0, [r4, #0x1c]
	mov r1, #0x3e
	ldrsh r2, [r4, r1]
	mov r1, #4
	ldrsh r1, [r4, r1]
	ldr r0, [r4]
	add r1, r2, r1
	mov r2, #0x40
	ldrsh r3, [r4, r2]
	mov r2, #6
	ldrsh r2, [r4, r2]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add r2, r3, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	b _02221EB2
_02221E6A:
	ldr r0, [r4, #0x44]
	cmp r0, #1
	bge _02221EA4
	cmp r0, #0
	bne _02221E92
	ldr r1, [r4, #0xc]
	ldr r2, _02221EB8 ; =0x00007FFF
	lsl r1, r1, #0x10
	str r2, [sp]
	ldr r0, [r4, #0x10]
	lsr r1, r1, #0x10
	str r0, [sp, #4]
	ldr r0, [r4, #0x18]
	add r3, r1, #0
	str r0, [sp, #8]
	ldr r0, _02221EBC ; =0x0000071C
	str r0, [sp, #0xc]
	add r0, r4, #4
	bl MOD08_02217D44
_02221E92:
	ldr r0, [r4, #8]
	ldr r2, _02221EC0 ; =0x0000FFFF
	str r0, [sp]
	add r0, r4, #0
	ldr r3, _02221EC4 ; =0xFFFFF000
	add r0, #0x28
	mov r1, #0
	bl MOD08_022180AC
_02221EA4:
	ldr r0, [r4, #0x44]
	add r0, r0, #1
	str r0, [r4, #0x44]
	b _02221EB2
_02221EAC:
	add sp, #0x10
	mov r0, #0
	pop {r4, pc}
_02221EB2:
	mov r0, #1
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_02221EB8: .word 0x00007FFF
_02221EBC: .word 0x0000071C
_02221EC0: .word 0x0000FFFF
_02221EC4: .word 0xFFFFF000

	thumb_func_start MOD08_02221EC8
MOD08_02221EC8: ; 0x02221EC8
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r7, r0, #0
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	cmp r0, #6
	bhi _02221F3C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02221EE4: ; jump table
	.short _02221EF2 - _02221EE4 - 2 ; case 0
	.short _02221F0A - _02221EE4 - 2 ; case 1
	.short _02221F56 - _02221EE4 - 2 ; case 2
	.short _02221F6C - _02221EE4 - 2 ; case 3
	.short _0222200C - _02221EE4 - 2 ; case 4
	.short _02222036 - _02221EE4 - 2 ; case 5
	.short _02222076 - _02221EE4 - 2 ; case 6
_02221EF2:
	add r0, r4, #0
	add r0, #0xc
	bl MOD08_02221E08
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xf0
	str r1, [r0]
	b _022220A0
_02221F0A:
	add r0, r4, #0
	add r0, #0xfc
	ldr r1, [r0]
	add r0, r4, #0
	add r1, #0xa
	add r0, #0xfc
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #0xa
	bl _s32_div_f
	mov r1, #0x1f
	sub r1, r1, r0
	lsl r1, r1, #8
	orr r1, r0
	ldr r0, _022220A8 ; =0x04000052
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0xfc
	ldr r1, [r0]
	ldr r0, _022220AC ; =0x00000136
	cmp r1, r0
	bge _02221F3E
_02221F3C:
	b _022220A0
_02221F3E:
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl FUN_0200C90C
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xf0
	str r1, [r0]
	b _022220A0
_02221F56:
	ldr r1, _022220B0 ; =0x0000FFFF
	ldr r0, _022220A8 ; =0x04000052
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xf0
	str r1, [r0]
	b _022220A0
_02221F6C:
	add r0, r4, #0
	add r0, #0xf4
	ldr r0, [r0]
	cmp r0, #0
	bgt _02221FB0
	add r0, r4, #0
	add r0, #0xf8
	ldr r0, [r0]
	mov r2, #0x4c
	add r3, r0, #0
	mul r3, r2
	add r0, r4, r3
	mov r1, #1
	add r0, #0xa0
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xf8
	ldr r0, [r0]
	mul r2, r0
	add r0, r4, r2
	ldr r0, [r0, #0x58]
	bl FUN_0200C644
	add r0, r4, #0
	add r0, #0xf8
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xf8
	str r1, [r0]
	add r0, r4, #0
	mov r1, #8
	add r0, #0xf4
	str r1, [r0]
_02221FB0:
	add r0, r4, #0
	add r0, #0xf8
	ldr r0, [r0]
	cmp r0, #2
	bge _02221FC8
	add r0, r4, #0
	add r0, #0xf4
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xf4
	str r1, [r0]
_02221FC8:
	add r0, r4, #0
	add r0, #0xc
	bl MOD08_02221E08
	add r5, r4, #0
	add r6, r0, #0
	mov r7, #0
	add r5, #0x58
_02221FD8:
	add r0, r5, #0
	bl MOD08_02221E08
	str r0, [sp]
	cmp r0, #0
	bne _02221FEC
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02221DFC
_02221FEC:
	ldr r0, [sp]
	add r7, r7, #1
	orr r6, r0
	add r5, #0x4c
	cmp r7, #2
	blt _02221FD8
	cmp r6, #0
	bne _022220A0
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xf0
	str r1, [r0]
	b _022220A0
_0222200C:
	ldr r0, [r4, #0xc]
	bl FUN_0200C5A8
	ldr r0, [r4, #0xc]
	ldr r0, [r0]
	bl FUN_02020388
	cmp r0, #0
	bne _022220A0
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0200C90C
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xf0
	str r1, [r0]
	b _022220A0
_02222036:
	add r0, r4, #0
	add r0, #0xfc
	ldr r1, [r0]
	add r0, r4, #0
	sub r1, #0xa
	add r0, #0xfc
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #0xa
	bl _s32_div_f
	mov r1, #0x1f
	sub r1, r1, r0
	lsl r1, r1, #8
	orr r1, r0
	ldr r0, _022220A8 ; =0x04000052
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	cmp r0, #0
	bgt _022220A0
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xf0
	str r1, [r0]
	b _022220A0
_02222076:
	add r5, r4, #0
	mov r6, #0
	add r5, #0x58
_0222207C:
	add r0, r5, #0
	bl MOD08_02221DF0
	add r6, r6, #1
	add r5, #0x4c
	cmp r6, #2
	blt _0222207C
	ldr r0, [r4, #0xc]
	bl FUN_0200C3DC
	ldr r0, [r4]
	add r1, r7, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
_022220A0:
	ldr r0, [r4, #8]
	bl FUN_0200BC1C
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022220A8: .word 0x04000052
_022220AC: .word 0x00000136
_022220B0: .word 0x0000FFFF

	thumb_func_start MOD08_022220B4
MOD08_022220B4: ; 0x022220B4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x48
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	str r3, [sp, #0x10]
	bl MOD08_02212014
	mov r1, #1
	lsl r1, r1, #8
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	str r6, [r4, #4]
	str r7, [r4, #8]
	mov r1, #8
	add r0, #0xf4
	str r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xf8
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xf0
	str r1, [r0]
	add r0, r5, #0
	bl MOD08_02212458
	add r6, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02217C1C
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0x11
	str r1, [r4, #0xc]
	mov r1, #0
	str r1, [r4, #0x50]
	ldr r2, _022221EC ; =0x0000BFFF
	neg r0, r0
	str r2, [sp]
	str r0, [sp, #4]
	ldr r1, _022221F0 ; =0xFFFF8000
	ldr r0, _022221F4 ; =0x0000071C
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	add r0, r4, #0
	lsr r1, r1, #0x12
	add r0, #0x10
	add r3, r1, #0
	bl MOD08_02217D44
	ldr r0, [r4, #0x14]
	ldr r2, _022221F8 ; =0x0000FFFF
	str r0, [sp]
	add r0, r4, #0
	ldr r3, _022221FC ; =0xFFFFF000
	add r0, #0x34
	mov r1, #0
	bl MOD08_022180AC
	add r0, r4, #0
	ldr r1, [r4, #0x28]
	add r0, #0x48
	strh r1, [r0]
	mov r0, #1
	str r0, [r4, #0x54]
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0
	bl MOD08_02217B98
	add r1, r4, #0
	add r1, #0x4a
	strh r0, [r1]
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #1
	bl MOD08_02217B98
	add r1, r4, #0
	add r1, #0x4c
	strh r0, [r1]
	mov r1, #0x4a
	mov r2, #0x4c
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	bl FUN_0200C714
	ldr r0, [r4, #0xc]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0200C6B0
	ldr r1, [r4]
	add r0, sp, #0x14
	bl MOD08_02215474
	mov r0, #0x4a
	ldrsh r0, [r4, r0]
	add r1, sp, #0x14
	add r5, r4, #0
	strh r0, [r1]
	mov r0, #0x4c
	ldrsh r0, [r4, r0]
	add r7, r4, #0
	mov r6, #0
	strh r0, [r1, #2]
	add r5, #0x58
	add r7, #0xc
_0222219A:
	str r7, [sp]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	add r0, r5, #0
	add r3, sp, #0x14
	bl MOD08_02221D80
	add r6, r6, #1
	add r5, #0x4c
	cmp r6, #2
	blt _0222219A
	add r0, r4, #0
	mov r1, #0
	add r0, #0xfc
	str r1, [r0]
	ldr r0, [r4]
	mov r2, #0x1f
	bl MOD08_02227994
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0200C90C
	mov r6, #0
	add r5, r4, #0
	mov r7, #1
_022221CE:
	ldr r0, [r5, #0x58]
	add r1, r7, #0
	bl FUN_0200C90C
	add r6, r6, #1
	add r5, #0x4c
	cmp r6, #2
	blt _022221CE
	ldr r0, [r4]
	ldr r1, _02222200 ; =MOD08_02221EC8
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x48
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022221EC: .word 0x0000BFFF
_022221F0: .word 0xFFFF8000
_022221F4: .word 0x0000071C
_022221F8: .word 0x0000FFFF
_022221FC: .word 0xFFFFF000
_02222200: .word MOD08_02221EC8

	thumb_func_start MOD08_02222204
MOD08_02222204: ; 0x02222204
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r2, #0x60
	ldrsh r3, [r4, r2]
	mov r2, #0x10
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x5c]
	mov r1, #0
	add r2, r3, r2
	bl FUN_02007558
	mov r2, #0x62
	ldrsh r3, [r4, r2]
	mov r2, #0x12
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x5c]
	mov r1, #1
	add r2, r3, r2
	bl FUN_02007558
	mov r1, #0x60
	ldrsh r2, [r4, r1]
	mov r1, #0x10
	ldrsh r1, [r4, r1]
	ldr r0, [r4, #0x58]
	add r1, r2, r1
	mov r2, #0x62
	ldrsh r3, [r4, r2]
	mov r2, #0x12
	ldrsh r2, [r4, r2]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add r3, r3, r2
	mov r2, #0x66
	ldrsh r2, [r4, r2]
	sub r2, r3, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	add r0, r4, #0
	add r0, #0x34
	add r1, sp, #4
	add r2, sp, #0
	bl MOD08_0221825C
	mov r0, #0x64
	ldrsh r0, [r4, r0]
	bl _fflt
	add r1, r0, #0
	ldr r0, _02222298 ; =0x3DCCCCCD
	bl _fmul
	add r1, r0, #0
	ldr r0, [sp, #4]
	bl _fadd
	add r1, r0, #0
	str r1, [sp, #4]
	ldr r0, [r4, #0x58]
	ldr r2, [sp]
	bl FUN_0200C884
	mov r0, #0x64
	ldrsh r1, [r4, r0]
	sub r0, #0x65
	add r4, #0x64
	mul r0, r1
	strh r0, [r4]
	add sp, #8
	pop {r4, pc}
	nop
_02222298: .word 0x3DCCCCCD

	thumb_func_start MOD08_0222229C
MOD08_0222229C: ; 0x0222229C
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r2, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _022222B4
	cmp r0, #1
	beq _022222EE
	cmp r0, #2
	beq _0222232A
	b _0222233C
_022222B4:
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_022183F0
	add r0, r4, #0
	add r0, #0x34
	bl MOD08_02218224
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02222204
	cmp r5, #0
	bne _0222233C
	mov r2, #0xa
	str r2, [sp]
	str r2, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x34
	mov r1, #0xc
	mov r3, #0xf
	bl MOD08_022181A8
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _0222233C
_022222EE:
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_022183F0
	add r0, r4, #0
	add r0, #0x34
	bl MOD08_02218224
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02222204
	cmp r5, #0
	bne _0222233C
	mov r2, #0x60
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x5c]
	mov r1, #0
	bl FUN_02007558
	mov r2, #0x62
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x5c]
	mov r1, #1
	bl FUN_02007558
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _0222233C
_0222232A:
	ldr r0, [r4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0xc
	pop {r4, r5, pc}
_0222233C:
	ldr r0, [r4, #4]
	bl FUN_0200BC1C
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02222348
MOD08_02222348: ; 0x02222348
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	bl MOD08_02212014
	mov r1, #0x68
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	add r0, r5, #0
	bl MOD08_02212504
	str r0, [r4, #4]
	mov r0, #0
	str r0, [r4, #8]
	str r0, [r4, #0xc]
	ldr r0, [r4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	mov r1, #0
	str r0, [r4, #0x5c]
	bl FUN_0200782C
	add r1, r4, #0
	add r1, #0x60
	strh r0, [r1]
	ldr r0, [r4, #0x5c]
	mov r1, #1
	bl FUN_0200782C
	add r1, r4, #0
	add r1, #0x62
	strh r0, [r1]
	ldr r0, [r4, #0x5c]
	mov r1, #0x29
	bl FUN_0200782C
	add r1, r4, #0
	add r1, #0x66
	strh r0, [r1]
	mov r0, #6
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x10
	mov r1, #2
	mov r2, #0
	mov r3, #1
	bl MOD08_022183C0
	ldr r0, [r4]
	mov r1, #0
	bl MOD08_022124D8
	str r0, [r4, #0x58]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r4, #0x58]
	mov r1, #2
	bl FUN_0200C840
	ldr r0, [r4, #0x58]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r4, #0x58]
	mov r1, #1
	bl FUN_0200C6B0
	mov r0, #0xf
	str r0, [sp]
	mov r1, #0xa
	str r1, [sp, #4]
	mov r0, #7
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x34
	mov r2, #0xc
	add r3, r1, #0
	bl MOD08_022181A8
	add r0, r4, #0
	mov r1, #1
	add r0, #0x64
	strh r1, [r0]
	ldr r0, [r4]
	mov r1, #0x1c
	mov r2, #0xf
	bl MOD08_02227994
	ldr r0, [r4]
	ldr r1, _02222414 ; =MOD08_0222229C
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02222414: .word MOD08_0222229C

	thumb_func_start MOD08_02222418
MOD08_02222418: ; 0x02222418
	mov r2, #0x12
	ldrsh r2, [r0, r2]
	mov r3, #0x10
	ldrsh r0, [r0, r3]
	neg r2, r2
	lsl r2, r2, #0x10
	neg r0, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	orr r0, r2
	mov r2, #3
	ldr r3, _02222434 ; =MIi_CpuClear32
	lsl r2, r2, #8
	bx r3
	.align 2, 0
_02222434: .word MIi_CpuClear32

	thumb_func_start MOD08_02222438
MOD08_02222438: ; 0x02222438
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5, #0x18]
	bl MOD08_02218970
	str r0, [sp, #0xc]
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	bl MOD08_02222418
	add r0, r5, #0
	add r0, #0x1c
	bl MOD08_02217ECC
	str r0, [sp, #8]
	mov r0, #0x14
	ldrsh r4, [r5, r0]
	mov r0, #0x16
	ldrsh r0, [r5, r0]
	cmp r4, r0
	bgt _022224D8
	ldr r1, [sp, #0xc]
	lsl r2, r4, #2
	add r1, r1, r2
	str r1, [sp]
_0222246C:
	ldr r1, [sp]
	sub r0, r0, r4
	ldr r2, [r1]
	lsl r1, r2, #0x10
	asr r1, r1, #0x10
	str r1, [sp, #4]
	lsr r1, r2, #0x10
	lsl r1, r1, #0x10
	asr r7, r1, #0x10
	mov r1, #0x1e
	ldrsh r1, [r5, r1]
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	sub r0, r7, r0
	lsl r0, r0, #0x10
	asr r7, r0, #0x10
	mov r0, #0x1c
	ldrsh r1, [r5, r0]
	mov r0, #0x14
	ldrsh r0, [r5, r0]
	add r0, #0x28
	sub r0, r0, r4
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	ldr r1, [sp, #4]
	sub r0, r1, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #4]
	sub r6, r4, #1
	bpl _022224B4
	add r6, #0xc0
_022224B4:
	ldr r0, [sp, #4]
	lsl r1, r7, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsr r1, r1, #0x10
	bl MOD08_02218998
	ldr r1, [sp, #0xc]
	lsl r2, r6, #2
	str r0, [r1, r2]
	ldr r0, [sp]
	add r4, r4, #1
	add r0, r0, #4
	str r0, [sp]
	mov r0, #0x16
	ldrsh r0, [r5, r0]
	cmp r4, r0
	ble _0222246C
_022224D8:
	ldr r0, [sp, #8]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_022224E0
MOD08_022224E0: ; 0x022224E0
	push {r4, r5, r6, lr}
	sub sp, #8
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #4
	bhi _02222548
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022224FA: ; jump table
	.short _02222504 - _022224FA - 2 ; case 0
	.short _02222536 - _022224FA - 2 ; case 1
	.short _0222255E - _022224FA - 2 ; case 2
	.short _022225AE - _022224FA - 2 ; case 3
	.short _022225CE - _022224FA - 2 ; case 4
_02222504:
	add r0, r4, #0
	bl MOD08_02222438
	cmp r0, #0
	bne _02222548
	ldr r0, [r4, #4]
	mov r1, #0x1f
	add r0, r0, #1
	str r0, [r4, #4]
	ldr r0, [r4]
	mov r2, #0
	bl MOD08_02227A00
	mov r1, #0x1f
	mov r2, #0
	str r1, [sp]
	mov r0, #0x10
	add r4, #0x40
	str r0, [sp, #4]
	add r0, r4, #0
	add r3, r2, #0
	bl MOD08_022186D4
	add sp, #8
	pop {r4, r5, r6, pc}
_02222536:
	add r0, r4, #0
	bl MOD08_02222438
	add r0, r4, #0
	add r0, #0x40
	bl MOD08_02218704
	cmp r0, #0
	bne _0222254A
_02222548:
	b _02222650
_0222254A:
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	ldr r0, [r4, #0x18]
	bl MOD08_02218984
	mov r0, #0
	add sp, #8
	str r0, [r4, #8]
	pop {r4, r5, r6, pc}
_0222255E:
	ldr r0, [r4]
	bl MOD08_02212490
	mov r3, #0x10
	ldrsh r3, [r4, r3]
	mov r1, #2
	mov r2, #0
	neg r3, r3
	bl FUN_020179E0
	ldr r0, [r4]
	bl MOD08_02212490
	mov r3, #0x12
	ldrsh r3, [r4, r3]
	mov r1, #2
	mov r2, #3
	neg r3, r3
	bl FUN_020179E0
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #8
	ble _02222650
	mov r1, #0
	str r1, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x1f
	add r0, #0x40
	add r3, r2, #0
	bl MOD08_022186D4
	ldr r0, [r4, #4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, r6, pc}
_022225AE:
	add r0, r4, #0
	add r0, #0x40
	bl MOD08_02218704
	cmp r0, #0
	beq _02222650
	ldr r0, [r4, #0xc]
	mov r1, #6
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4, #4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, r6, pc}
_022225CE:
	ldr r0, [r4, #0x18]
	bl MOD08_0221894C
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_02215588
	add r5, r0, #0
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_02215600
	add r1, r0, #0
	lsl r0, r5, #0x18
	lsl r1, r1, #0x18
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	bl FUN_020178BC
	ldr r0, [r4]
	bl MOD08_02215574
	add r1, r0, #0
	lsl r1, r1, #0x18
	mov r0, #0
	lsr r1, r1, #0x18
	bl FUN_020178BC
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_02215588
	add r5, r0, #0
	ldr r0, [r4]
	bl MOD08_02212014
	add r3, r0, #0
	lsl r0, r5, #0x18
	mov r1, #1
	lsr r0, r0, #0x18
	lsl r1, r1, #0xe
	mov r2, #0
	bl FUN_02017F18
	ldr r0, [r4]
	bl MOD08_02212490
	add r5, r0, #0
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_02215588
	add r1, r0, #0
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	bl FUN_02018744
	ldr r0, [r4]
	add r1, r6, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_02222650:
	add sp, #8
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_02222654
MOD08_02222654: ; 0x02222654
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	bl MOD08_02212014
	mov r1, #0x68
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x68
	add r4, r0, #0
	bl memset
	ldr r1, _022227BC ; =MOD08_022224E0
	str r5, [r4]
	add r0, r5, #0
	add r2, r4, #0
	bl MOD08_02212400
	str r0, [sp, #0x14]
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	str r0, [r4, #0xc]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #0x10]
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #0x12]
	ldr r0, [r4, #0xc]
	mov r1, #0x29
	bl FUN_0200782C
	mov r1, #0x12
	ldrsh r2, [r4, r1]
	sub r0, r2, r0
	strh r0, [r4, #0x12]
	mov r0, #0x10
	ldrsh r0, [r4, r0]
	mov r2, #1
	sub r0, #0x28
	strh r0, [r4, #0x10]
	ldrsh r0, [r4, r1]
	mov r1, #6
	sub r0, #0x28
	strh r0, [r4, #0x12]
	ldr r0, [r4, #0xc]
	bl FUN_02007558
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02217C1C
	add r6, r0, #0
	mov r0, #0x12
	ldrsh r1, [r4, r0]
	sub r1, #8
	strh r1, [r4, #0x14]
	ldrsh r0, [r4, r0]
	add r0, #0x58
	strh r0, [r4, #0x16]
	mov r0, #0x14
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bge _022226F0
	mov r0, #0
	strh r0, [r4, #0x14]
_022226F0:
	mov r0, #0x16
	ldrsh r0, [r4, r0]
	cmp r0, #0xc0
	ble _022226FC
	mov r0, #0xc0
	strh r0, [r4, #0x16]
_022226FC:
	add r0, r5, #0
	mov r1, #1
	bl MOD08_022155C4
	add r7, r0, #0
	ldr r0, [sp, #0x14]
	bl FUN_0201B6CC
	str r0, [sp, #0x18]
	ldrh r0, [r4, #0x10]
	ldrh r1, [r4, #0x12]
	bl MOD08_02218998
	str r0, [sp, #0x1c]
	add r0, r5, #0
	bl MOD08_02212014
	mov r1, #0x50
	str r1, [sp]
	ldr r1, [sp, #0x18]
	str r7, [sp, #4]
	add r1, r1, #1
	str r1, [sp, #8]
	ldr r1, [sp, #0x1c]
	ldr r2, _022227C0 ; =0x0000038E
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #0x14
	mov r1, #0x16
	ldrsh r0, [r4, r0]
	ldrsh r1, [r4, r1]
	lsl r3, r6, #0xf
	lsl r0, r0, #0x18
	lsl r1, r1, #0x18
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	bl MOD08_022188DC
	str r0, [r4, #0x18]
	mov r0, #0x28
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	add r0, #0x1c
	mov r2, #0x50
	add r3, r1, #0
	bl MOD08_02217E80
	ldr r0, [r4, #0x24]
	add r1, r0, #0
	mul r1, r6
	str r1, [r4, #0x24]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02227468
	sub r0, r0, #3
	cmp r0, #1
	bhi _022227AE
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_02215588
	add r5, r0, #0
	ldr r0, [r4]
	bl MOD08_02215574
	add r1, r0, #0
	lsl r0, r5, #0x18
	lsl r1, r1, #0x18
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	bl FUN_020178BC
	ldr r0, [r4]
	bl MOD08_02215574
	add r1, r0, #0
	add r1, r1, #1
	lsl r1, r1, #0x18
	mov r0, #0
	lsr r1, r1, #0x18
	bl FUN_020178BC
_022227AE:
	ldr r0, [sp, #0x14]
	add r1, r4, #0
	bl MOD08_022224E0
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022227BC: .word MOD08_022224E0
_022227C0: .word 0x0000038E

	thumb_func_start MOD08_022227C4
MOD08_022227C4: ; 0x022227C4
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r2, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #3
	bhi _02222874
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022227DE: ; jump table
	.short _022227E6 - _022227DE - 2 ; case 0
	.short _0222280C - _022227DE - 2 ; case 1
	.short _0222281E - _022227DE - 2 ; case 2
	.short _02222862 - _022227DE - 2 ; case 3
_022227E6:
	add r0, r4, #0
	add r0, #0x38
	bl MOD08_02218080
	ldr r2, [r4, #0x38]
	mov r1, #0x1f
	sub r1, r1, r2
	lsl r1, r1, #8
	orr r2, r1
	ldr r1, _02222880 ; =0x04000052
	cmp r0, #0
	strh r2, [r1]
	bne _02222874
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #0
	str r0, [r4, #0xc]
	b _02222874
_0222280C:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	cmp r0, #0x20
	ble _02222874
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02222874
_0222281E:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02218170
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x14
	add r1, sp, #4
	add r2, sp, #0
	bl MOD08_0221825C
	ldr r0, [r4, #0x4c]
	cmp r0, #1
	bne _02222844
	ldr r1, [sp, #4]
	mov r0, #0
	bl _fsub
	str r0, [sp, #4]
_02222844:
	ldr r0, [r4, #0x10]
	ldr r1, [sp, #4]
	ldr r2, [sp]
	bl FUN_0200C884
	cmp r5, #0
	bne _02222874
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02222874
_02222862:
	ldr r0, [r4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, pc}
_02222874:
	ldr r0, [r4, #4]
	bl FUN_0200BC1C
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_02222880: .word 0x04000052

	thumb_func_start MOD08_02222884
MOD08_02222884: ; 0x02222884
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r2, r0, #0
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _022228A0
	cmp r0, #1
	beq _02222928
	cmp r0, #2
	bne _0222289C
	b _022229B4
_0222289C:
	add sp, #0xc
	pop {r4, r5, pc}
_022228A0:
	add r0, r5, #0
	add r0, #0x14
	bl MOD08_022183F0
	mov r2, #0x38
	mov r3, #0x3a
	add r0, r5, #0
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	ldr r1, [r5, #8]
	add r0, #0x14
	bl MOD08_02217CD0
	ldr r0, [r5, #0x10]
	cmp r0, #1
	bne _022228DA
	mov r3, #0x3a
	ldrsh r4, [r5, r3]
	ldr r3, [r5, #0x3c]
	mov r2, #0x38
	sub r3, r4, r3
	add r0, r5, #0
	lsl r3, r3, #0x10
	ldrsh r2, [r5, r2]
	ldr r1, [r5, #0xc]
	add r0, #0x14
	asr r3, r3, #0x10
	bl MOD08_02217C94
_022228DA:
	ldr r0, [r5, #8]
	bl FUN_02007F20
	cmp r0, #0
	bne _022229C2
	mov r2, #0
	str r2, [sp]
	ldr r0, [r5, #8]
	mov r1, #0x10
	add r3, r2, #0
	bl FUN_02007E68
	ldr r0, [r5, #0x10]
	cmp r0, #1
	bne _0222291E
	ldr r0, [r5, #0xc]
	bl MOD08_02217C08
	mov r1, #1
	add r4, r1, #0
	lsl r4, r0
	ldr r0, [r5]
	bl MOD08_02215504
	mov r1, #0x10
	str r1, [sp]
	mov r3, #0
	lsl r2, r4, #0x10
	str r3, [sp, #4]
	mov r1, #4
	lsr r2, r2, #0x10
	str r3, [sp, #8]
	bl FUN_02003210
_0222291E:
	ldr r0, [r5, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r5, #4]
	pop {r4, r5, pc}
_02222928:
	add r0, r5, #0
	add r0, #0x14
	bl MOD08_022183F0
	mov r2, #0x38
	mov r3, #0x3a
	add r0, r5, #0
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	ldr r1, [r5, #8]
	add r0, #0x14
	bl MOD08_02217CD0
	ldr r0, [r5, #0x10]
	cmp r0, #1
	bne _02222962
	mov r3, #0x3a
	ldrsh r4, [r5, r3]
	ldr r3, [r5, #0x3c]
	mov r2, #0x38
	sub r3, r4, r3
	add r0, r5, #0
	lsl r3, r3, #0x10
	ldrsh r2, [r5, r2]
	ldr r1, [r5, #0xc]
	add r0, #0x14
	asr r3, r3, #0x10
	bl MOD08_02217C94
_02222962:
	ldr r0, [r5, #8]
	bl FUN_02007F20
	cmp r0, #0
	bne _022229C2
	mov r2, #0x38
	ldrsh r2, [r5, r2]
	ldr r0, [r5, #8]
	mov r1, #0
	bl FUN_02007558
	mov r2, #0x3a
	ldrsh r2, [r5, r2]
	ldr r0, [r5, #8]
	mov r1, #1
	bl FUN_02007558
	ldr r0, [r5, #0x10]
	cmp r0, #1
	bne _022229AA
	ldr r0, [r5, #8]
	mov r1, #6
	mov r2, #0
	bl FUN_02007558
	mov r2, #0x3a
	ldrsh r3, [r5, r2]
	ldr r2, [r5, #0x3c]
	mov r1, #0x38
	sub r2, r3, r2
	lsl r2, r2, #0x10
	ldrsh r1, [r5, r1]
	ldr r0, [r5, #0xc]
	asr r2, r2, #0x10
	bl FUN_0200C714
_022229AA:
	ldr r0, [r5, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r5, #4]
	pop {r4, r5, pc}
_022229B4:
	ldr r0, [r5]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r5, #0
	bl FreeToHeap
_022229C2:
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_022229C8
MOD08_022229C8: ; 0x022229C8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD08_02212014
	mov r1, #0x50
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x50
	bl memset
	str r5, [r4]
	add r0, r5, #0
	bl MOD08_02212504
	str r0, [r4, #4]
	add r0, r5, #0
	bl MOD08_02212004
	str r0, [r4, #0x4c]
	ldr r0, [r4]
	mov r1, #0
	bl MOD08_022124D8
	str r0, [r4, #0x10]
	mov r0, #8
	str r0, [sp]
	add r0, r4, #0
	mov r2, #0xa
	add r0, #0x14
	mov r1, #0xe
	add r3, r2, #0
	bl MOD08_02218120
	add r0, r4, #0
	add r0, #0x38
	mov r1, #0
	mov r2, #0x10
	mov r3, #8
	bl MOD08_02218030
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r4]
	mov r1, #0
	mov r2, #0x1f
	bl MOD08_02227994
	ldr r0, [r4, #0x10]
	mov r1, #2
	bl FUN_0200C840
	ldr r0, [r4, #0x4c]
	cmp r0, #1
	ldr r0, [r4, #0x10]
	bne _02222A48
	ldr r1, _02222A6C ; =0xBFB33333
	ldr r2, _02222A70 ; =0x3FB33333
	bl FUN_0200C884
	b _02222A50
_02222A48:
	ldr r1, _02222A70 ; =0x3FB33333
	add r2, r1, #0
	bl FUN_0200C884
_02222A50:
	ldr r0, [r4, #0x10]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200C6B0
	ldr r0, [r4]
	ldr r1, _02222A74 ; =MOD08_022227C4
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, pc}
	.align 2, 0
_02222A6C: .word 0xBFB33333
_02222A70: .word 0x3FB33333
_02222A74: .word MOD08_022227C4

	thumb_func_start MOD08_02222A78
MOD08_02222A78: ; 0x02222A78
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	bl MOD08_02212014
	mov r1, #0x40
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x40
	bl memset
	str r5, [r4]
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	str r0, [r4, #8]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #0x38]
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #0x3a]
	ldr r0, [r4, #8]
	mov r1, #0x29
	bl FUN_0200782C
	str r0, [r4, #0x3c]
	mov r1, #4
	add r0, r4, #0
	str r1, [sp]
	add r0, #0x14
	mov r2, #0
	mov r3, #1
	bl MOD08_022183C0
	ldr r0, [r4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02217C1C
	mov r1, #0x14
	ldrsh r1, [r4, r1]
	mov r2, #0x10
	add r0, r1, r0
	mov r1, #0
	strh r0, [r4, #0x14]
	str r1, [sp]
	ldr r0, [r4, #8]
	add r3, r1, #0
	bl FUN_02007E68
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_022124D8
	str r0, [r4, #0xc]
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02227468
	add r5, r0, #0
	ldr r0, [r4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02227468
	cmp r5, #2
	bne _02222B24
	cmp r0, #4
	beq _02222B2C
_02222B24:
	cmp r5, #5
	bne _02222B5E
	cmp r0, #3
	bne _02222B5E
_02222B2C:
	ldr r0, [r4, #0xc]
	bl MOD08_02217C08
	mov r1, #1
	add r5, r1, #0
	lsl r5, r0
	ldr r0, [r4]
	bl MOD08_02215504
	mov r3, #0
	lsl r2, r5, #0x10
	str r3, [sp]
	mov r1, #0x10
	str r1, [sp, #4]
	mov r1, #4
	lsr r2, r2, #0x10
	str r3, [sp, #8]
	bl FUN_02003210
	mov r2, #1
	str r2, [r4, #0x10]
	ldr r0, [r4, #8]
	mov r1, #6
	bl FUN_02007558
_02222B5E:
	ldr r0, [r4]
	ldr r1, _02222B6C ; =MOD08_02222884
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02222B6C: .word MOD08_02222884

	thumb_func_start MOD08_02222B70
MOD08_02222B70: ; 0x02222B70
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #8]
	mov r5, #0
	cmp r0, #3
	bhi _02222BEC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02222B8A: ; jump table
	.short _02222B92 - _02222B8A - 2 ; case 0
	.short _02222BAA - _02222B8A - 2 ; case 1
	.short _02222BD0 - _02222B8A - 2 ; case 2
	.short _02222BEA - _02222B8A - 2 ; case 3
_02222B92:
	add r0, r4, #0
	add r0, #0x1c
	bl MOD08_02218704
	cmp r0, #1
	bne _02222BEC
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #0x20
	str r0, [r4, #0x44]
	b _02222BEC
_02222BAA:
	ldr r0, [r4, #0x44]
	sub r0, r0, #1
	str r0, [r4, #0x44]
	bpl _02222BEC
	ldr r0, [r4, #8]
	mov r1, #8
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0x18
	add r4, #0x1c
	str r0, [sp, #4]
	add r0, r4, #0
	add r2, r5, #0
	add r3, r1, #0
	bl MOD08_022186D4
	b _02222BEC
_02222BD0:
	add r0, r4, #0
	add r0, #0x1c
	bl MOD08_02218704
	cmp r0, #1
	bne _02222BEC
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #0x14]
	bl MOD08_0221894C
	b _02222BEC
_02222BEA:
	mov r5, #1
_02222BEC:
	add r0, r5, #0
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02222BF4
MOD08_02222BF4: ; 0x02222BF4
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _02222C0A
	cmp r0, #1
	beq _02222C2C
	cmp r0, #2
	beq _02222C3E
	pop {r4, r5, r6, pc}
_02222C0A:
	ldr r0, [r4, #0x48]
	bl FUN_0200C658
	cmp r0, #1
	bne _02222C1E
	ldr r0, [r4, #0x10]
	mov r1, #6
	mov r2, #1
	bl FUN_02007558
_02222C1E:
	add r0, r4, #0
	bl MOD08_02222B70
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, r6, pc}
_02222C2C:
	add r0, r4, #0
	bl MOD08_02222B70
	cmp r0, #0
	beq _02222CC4
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, r6, pc}
_02222C3E:
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_02215588
	add r5, r0, #0
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_02215600
	add r1, r0, #0
	lsl r0, r5, #0x18
	lsl r1, r1, #0x18
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	bl FUN_020178BC
	ldr r0, [r4]
	bl MOD08_02215574
	add r1, r0, #0
	lsl r1, r1, #0x18
	mov r0, #0
	lsr r1, r1, #0x18
	bl FUN_020178BC
	ldr r0, [r4, #0x10]
	mov r1, #6
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_02215588
	add r5, r0, #0
	ldr r0, [r4]
	bl MOD08_02212014
	add r3, r0, #0
	lsl r0, r5, #0x18
	mov r1, #1
	lsr r0, r0, #0x18
	lsl r1, r1, #0xe
	mov r2, #0
	bl FUN_02017F18
	ldr r0, [r4]
	bl MOD08_02212490
	add r5, r0, #0
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_02215588
	add r1, r0, #0
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	bl FUN_02018744
	ldr r0, [r4]
	add r1, r6, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_02222CC4:
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_02222CC8
MOD08_02222CC8: ; 0x02222CC8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	mov r1, #0x4c
	add r7, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r7, [r4]
	add r0, r7, #0
	bl MOD08_02215504
	str r0, [r4, #0x18]
	ldr r0, [r4]
	mov r1, #0
	mov r2, #0x10
	bl MOD08_02227A00
	mov r2, #8
	str r2, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x1c
	mov r1, #0
	mov r3, #0x10
	bl MOD08_022186D4
	ldr r0, [r4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	mov r1, #0
	str r0, [r4, #0x10]
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r5, r0, #0x10
	ldr r0, [r4, #0x10]
	mov r1, #0x29
	bl FUN_0200782C
	sub r0, r5, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	sub r0, #0x28
	lsl r0, r0, #0x10
	asr r5, r0, #0x10
	ldr r0, [r4]
	mov r1, #0
	bl MOD08_022124D8
	str r0, [r4, #0x48]
	ldr r0, [r4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02227468
	cmp r0, #5
	beq _02222D58
	cmp r0, #2
	bne _02222D6A
_02222D58:
	ldr r0, [r4, #0x48]
	mov r1, #1
	bl FUN_0200C644
	ldr r0, [r4, #0x48]
	mov r1, #2
	bl FUN_0200C6B0
	b _02222DA6
_02222D6A:
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_02215588
	str r0, [sp, #0x14]
	ldr r0, [r4]
	bl MOD08_02215574
	add r1, r0, #0
	ldr r0, [sp, #0x14]
	lsl r1, r1, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	bl FUN_020178BC
	ldr r0, [r4]
	bl MOD08_02215574
	add r1, r0, #0
	add r1, r1, #1
	lsl r1, r1, #0x18
	mov r0, #0
	lsr r1, r1, #0x18
	bl FUN_020178BC
	ldr r0, [r4, #0x48]
	mov r1, #0
	bl FUN_0200C644
_02222DA6:
	add r0, r7, #0
	mov r1, #1
	bl MOD08_022155C4
	neg r1, r5
	lsl r1, r1, #0x10
	sub r6, #0x28
	str r0, [sp, #0x18]
	lsl r0, r6, #0x10
	asr r0, r0, #0x10
	neg r0, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsr r1, r1, #0x10
	bl MOD08_02218998
	add r6, r0, #0
	add r0, r7, #0
	bl MOD08_02212014
	mov r1, #0x64
	str r1, [sp]
	ldr r1, [sp, #0x18]
	mov r3, #5
	str r1, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	str r6, [sp, #0xc]
	str r0, [sp, #0x10]
	lsl r0, r5, #0x18
	add r5, #0x50
	lsl r1, r5, #0x18
	ldr r2, _02222E14 ; =0x0000038E
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	lsl r3, r3, #0xc
	bl MOD08_022188DC
	mov r2, #1
	str r0, [r4, #0x14]
	mov r1, #0
	str r1, [sp]
	ldr r0, [r4, #0x18]
	lsl r2, r2, #8
	mov r3, #8
	bl FUN_02003A64
	ldr r0, [r4]
	ldr r1, _02222E18 ; =MOD08_02222BF4
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_02222E14: .word 0x0000038E
_02222E18: .word MOD08_02222BF4

	thumb_func_start MOD08_02222E1C
MOD08_02222E1C: ; 0x02222E1C
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #3
	bhi _02222F1E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02222E36: ; jump table
	.short _02222E3E - _02222E36 - 2 ; case 0
	.short _02222E8E - _02222E36 - 2 ; case 1
	.short _02222ECC - _02222E36 - 2 ; case 2
	.short _02222F06 - _02222E36 - 2 ; case 3
_02222E3E:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02218170
	cmp r0, #1
	bne _02222E70
	add r0, r4, #0
	add r0, #0x14
	add r1, sp, #8
	add r2, sp, #4
	bl MOD08_0221825C
	ldr r0, [r4, #0x54]
	bl _fflt
	add r1, r0, #0
	ldr r0, [sp, #8]
	bl _fmul
	add r1, r0, #0
	ldr r0, [r4, #0x10]
	ldr r2, [sp, #4]
	bl FUN_0200C884
	b _02222F1E
_02222E70:
	ldr r0, [r4, #0xc]
	mov r1, #0xa
	add r0, r0, #1
	str r0, [r4, #0xc]
	mov r0, #5
	str r0, [r4, #0x4c]
	mov r0, #8
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x14
	add r2, r1, #0
	mov r3, #1
	bl MOD08_02218120
	b _02222F1E
_02222E8E:
	add r0, r4, #0
	add r0, #0x38
	bl MOD08_02218058
	ldr r1, [r4, #0x38]
	add r5, r0, #0
	lsl r1, r1, #0x10
	ldr r0, [r4, #0x10]
	lsr r1, r1, #0x10
	bl FUN_0200C898
	cmp r5, #0
	bne _02222F1E
	ldr r0, [r4, #0x4c]
	cmp r0, #0
	ble _02222EC4
	sub r0, r0, #1
	str r0, [r4, #0x4c]
	add r0, r4, #0
	ldr r1, [r4, #0x38]
	ldr r2, [r4, #0x50]
	add r0, #0x38
	mov r3, #4
	str r1, [r4, #0x50]
	bl MOD08_02218008
	b _02222F1E
_02222EC4:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02222F1E
_02222ECC:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02218170
	cmp r0, #1
	bne _02222EFE
	add r0, r4, #0
	add r0, #0x14
	add r1, sp, #8
	add r2, sp, #4
	bl MOD08_0221825C
	ldr r0, [r4, #0x54]
	bl _fflt
	add r1, r0, #0
	ldr r0, [sp, #8]
	bl _fmul
	add r1, r0, #0
	ldr r0, [r4, #0x10]
	ldr r2, [sp, #4]
	bl FUN_0200C884
	b _02222F1E
_02222EFE:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02222F1E
_02222F06:
	ldr r0, [r4, #0x10]
	bl FUN_0200C3DC
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0xc
	pop {r4, r5, pc}
_02222F1E:
	ldr r0, [r4, #8]
	bl FUN_0200BC1C
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start MOD08_02222F28
MOD08_02222F28: ; 0x02222F28
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r1, #0
	mov r1, #0x58
	add r5, r0, #0
	add r7, r2, #0
	str r3, [sp, #4]
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4]
	str r6, [r4, #4]
	str r7, [r4, #8]
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02217C1C
	add r7, r0, #0
	ldr r0, [r4]
	mov r1, #0
	bl MOD08_02215680
	cmp r0, #1
	bne _02222F68
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #0x54]
	neg r6, r7
	b _02222F6E
_02222F68:
	mov r0, #1
	str r0, [r4, #0x54]
	add r6, r7, #0
_02222F6E:
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	mov r2, #0
	bl MOD08_02217B98
	str r0, [sp, #8]
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	mov r2, #1
	bl MOD08_02217B98
	str r0, [sp, #0xc]
	ldr r0, [sp, #4]
	mov r1, #2
	str r0, [r4, #0x10]
	bl FUN_0200C840
	mov r1, #0xfe
	lsl r1, r1, #0x16
	ldr r0, [r4, #0x10]
	add r2, r1, #0
	bl FUN_0200C884
	ldr r0, [r4, #0x10]
	ldr r1, [sp, #8]
	ldr r2, [sp, #0xc]
	bl FUN_0200C714
	mov r1, #0x28
	mul r1, r7
	lsl r1, r1, #0x10
	ldr r0, [r4, #0x10]
	asr r1, r1, #0x10
	mov r2, #0
	bl FUN_0200C82C
	ldr r0, [r4, #0x10]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200C6B0
	mov r1, #0xb
	mvn r1, r1
	mul r1, r6
	lsl r1, r1, #0x10
	ldr r0, [r4, #0x10]
	asr r1, r1, #0x10
	mov r2, #0xc
	bl FUN_0200C8DC
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	bl MOD08_02227470
	cmp r0, #4
	ldr r0, [r4, #0x10]
	bne _02223000
	mov r1, #1
	bl FUN_0200C5C0
	b _02223006
_02223000:
	mov r1, #0
	bl FUN_0200C5C0
_02223006:
	mov r0, #8
	str r0, [sp]
	add r0, r4, #0
	mov r2, #0xa
	add r0, #0x14
	mov r1, #1
	add r3, r2, #0
	bl MOD08_02218120
	cmp r6, #0
	blt _0222302E
	add r0, r4, #0
	ldr r1, _02223050 ; =0x0000FF48
	ldr r2, _02223054 ; =0x0000E38D
	add r0, #0x38
	mov r3, #4
	bl MOD08_02218008
	ldr r0, _02223050 ; =0x0000FF48
	b _0222303E
_0222302E:
	add r0, r4, #0
	ldr r2, _02223058 ; =0x00001C71
	add r0, #0x38
	mov r1, #0
	mov r3, #4
	bl MOD08_02218008
	mov r0, #0
_0222303E:
	str r0, [r4, #0x50]
	ldr r0, [r4]
	ldr r1, _0222305C ; =MOD08_02222E1C
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02223050: .word 0x0000FF48
_02223054: .word 0x0000E38D
_02223058: .word 0x00001C71
_0222305C: .word MOD08_02222E1C

	thumb_func_start MOD08_02223060
MOD08_02223060: ; 0x02223060
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	str r1, [r5]
	add r6, r3, #0
	mov r3, #8
	mov r1, #0xa
	add r4, r2, #0
	add r0, r5, #4
	add r2, r1, #0
	str r3, [sp]
	bl MOD08_02218120
	mov r0, #3
	str r0, [r5, #0x2c]
	mov r0, #8
	str r0, [r5, #0x30]
	mov r0, #0xa
	str r0, [r5, #0x34]
	ldr r0, [sp, #0x18]
	add r1, r4, #0
	str r0, [r5, #0x28]
	ldr r0, [r5]
	add r2, r6, #0
	bl FUN_0200C714
	ldr r0, [r5]
	add r1, r4, #0
	add r2, r6, #0
	bl FUN_0200C714
	ldr r0, [r5]
	mov r1, #2
	bl FUN_0200C840
	ldr r0, [r5]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r5]
	mov r1, #1
	bl FUN_0200C6B0
	ldr r0, [sp, #0x18]
	cmp r0, #0
	beq _022230C8
	mov r2, #0xfe
	ldr r0, [r5]
	ldr r1, _022230D4 ; =0xBF800000
	lsl r2, r2, #0x16
	bl FUN_0200C884
_022230C8:
	ldr r0, [r5]
	mov r1, #0
	bl FUN_0200C644
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_022230D4: .word 0xBF800000

	thumb_func_start MOD08_022230D8
MOD08_022230D8: ; 0x022230D8
	ldr r3, _022230E0 ; =FUN_0200C3DC
	ldr r0, [r0]
	bx r3
	nop
_022230E0: .word FUN_0200C3DC

	thumb_func_start MOD08_022230E4
MOD08_022230E4: ; 0x022230E4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #1
	bl FUN_0200C644
	ldr r0, [r4]
	mov r1, #1
	bl FUN_0200C5E0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_022230FC
MOD08_022230FC: ; 0x022230FC
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r0, r4, #4
	bl MOD08_02218170
	cmp r0, #1
	bne _02223140
	add r0, r4, #4
	add r1, sp, #8
	add r2, sp, #4
	bl MOD08_0221825C
	ldr r0, [r4, #0x28]
	cmp r0, #0
	beq _02223132
	ldr r1, [sp, #8]
	mov r0, #0
	bl _fsub
	add r1, r0, #0
	mov r2, #0xfe
	ldr r0, [r4]
	lsl r2, r2, #0x16
	bl FUN_0200C884
	b _02223172
_02223132:
	mov r2, #0xfe
	ldr r0, [r4]
	ldr r1, [sp, #8]
	lsl r2, r2, #0x16
	bl FUN_0200C884
	b _02223172
_02223140:
	ldr r0, [r4, #0x2c]
	cmp r0, #0
	ble _0222316C
	sub r0, r0, #1
	str r0, [r4, #0x2c]
	mov r0, #8
	str r0, [sp]
	ldr r1, [r4, #0x30]
	ldr r3, [r4, #0x34]
	lsl r1, r1, #0x10
	lsl r3, r3, #0x10
	add r0, r4, #4
	asr r1, r1, #0x10
	mov r2, #0xa
	asr r3, r3, #0x10
	bl MOD08_02218120
	ldr r1, [r4, #0x30]
	ldr r0, [r4, #0x34]
	str r0, [r4, #0x30]
	str r1, [r4, #0x34]
	b _02223172
_0222316C:
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_02223172:
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start MOD08_02223178
MOD08_02223178: ; 0x02223178
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r7, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #3
	bhi _02223244
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02223190: ; jump table
	.short _02223198 - _02223190 - 2 ; case 0
	.short _022231CA - _02223190 - 2 ; case 1
	.short _022231E8 - _02223190 - 2 ; case 2
	.short _02223208 - _02223190 - 2 ; case 3
_02223198:
	ldr r0, [r4, #0x10]
	cmp r0, #4
	blt _022231C2
	mov r0, #0
	str r0, [r4, #0x10]
	ldr r1, [r4, #0x14]
	add r2, r4, #0
	mov r0, #0x38
	add r2, #0x44
	mul r0, r1
	add r0, r2, r0
	bl MOD08_022230E4
	ldr r0, [r4, #0x14]
	add r0, r0, #1
	str r0, [r4, #0x14]
	cmp r0, #4
	blt _022231C2
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
_022231C2:
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	b _02223244
_022231CA:
	mov r1, #0x1c
	mov r2, #0x1e
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r3, [r4, #0x18]
	add r0, #0x20
	bl MOD08_02218454
	cmp r0, #0
	bne _02223244
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02223244
_022231E8:
	add r5, r4, #0
	mov r6, #0
	add r5, #0x44
_022231EE:
	add r0, r5, #0
	bl MOD08_022230FC
	add r6, r6, #1
	add r5, #0x38
	cmp r6, #4
	blt _022231EE
	cmp r0, #0
	bne _02223244
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02223244
_02223208:
	mov r2, #0x1c
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x18]
	mov r1, #0
	bl FUN_02007558
	mov r2, #0x1e
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x18]
	mov r1, #1
	bl FUN_02007558
	add r5, r4, #0
	mov r6, #0
	add r5, #0x44
_02223226:
	add r0, r5, #0
	bl MOD08_022230D8
	add r6, r6, #1
	add r5, #0x38
	cmp r6, #4
	blt _02223226
	ldr r0, [r4]
	add r1, r7, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
_02223244:
	ldr r0, [r4, #8]
	bl FUN_0200BC1C
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_0222324C
MOD08_0222324C: ; 0x0222324C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x48
	str r1, [sp, #4]
	mov r1, #0x4a
	lsl r1, r1, #2
	add r4, r0, #0
	str r2, [sp, #8]
	str r3, [sp, #0xc]
	bl MOD08_02228064
	add r7, r0, #0
	ldr r0, [sp, #4]
	str r4, [r7]
	str r0, [r7, #4]
	ldr r0, [sp, #8]
	str r0, [r7, #8]
	add r0, r4, #0
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r7]
	bl MOD08_022154D4
	str r0, [r7, #0x18]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r7, #0x1c]
	ldr r0, [r7, #0x18]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r7, #0x1e]
	add r0, r7, #0
	mov r3, #1
	add r0, #0x20
	mov r1, #4
	mov r2, #0
	str r3, [sp]
	bl MOD08_022183C0
	mov r0, #0x1e
	ldrsh r4, [r7, r0]
	ldr r1, [r7]
	add r0, sp, #0x14
	add r4, #0x10
	mov r5, #0
	bl MOD08_02215474
	add r0, r5, #0
	add r6, r7, #0
	str r0, [sp, #0x10]
	add r6, #0x44
_022232B6:
	ldr r0, [sp, #0x10]
	cmp r0, #0
	bne _022232D0
	str r5, [sp]
	mov r2, #0x1c
	lsl r3, r4, #0x10
	ldrsh r2, [r7, r2]
	ldr r1, [sp, #0xc]
	add r0, r6, #0
	asr r3, r3, #0x10
	bl MOD08_02223060
	b _022232EC
_022232D0:
	ldr r0, [sp, #4]
	ldr r1, [sp, #8]
	add r2, sp, #0x14
	bl FUN_0200C154
	lsl r3, r4, #0x10
	add r1, r0, #0
	str r5, [sp]
	mov r2, #0x1c
	ldrsh r2, [r7, r2]
	add r0, r6, #0
	asr r3, r3, #0x10
	bl MOD08_02223060
_022232EC:
	mov r0, #1
	eor r5, r0
	ldr r0, [sp, #0x10]
	sub r4, #0xa
	add r0, r0, #1
	add r6, #0x38
	str r0, [sp, #0x10]
	cmp r0, #4
	blt _022232B6
	ldr r0, [r7]
	ldr r1, _0222330C ; =MOD08_02223178
	add r2, r7, #0
	bl MOD08_02212400
	add sp, #0x48
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222330C: .word MOD08_02223178

	thumb_func_start MOD08_02223310
MOD08_02223310: ; 0x02223310
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #6
	bls _02223320
	b _022234D2
_02223320:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222332C: ; jump table
	.short _0222333A - _0222332C - 2 ; case 0
	.short _0222337C - _0222332C - 2 ; case 1
	.short _022233DC - _0222332C - 2 ; case 2
	.short _0222341C - _0222332C - 2 ; case 3
	.short _0222343C - _0222332C - 2 ; case 4
	.short _0222347A - _0222332C - 2 ; case 5
	.short _022234BA - _0222332C - 2 ; case 6
_0222333A:
	add r0, r4, #0
	add r0, #0x18
	bl MOD08_02217ECC
	cmp r0, #0
	beq _0222335C
	mov r2, #0x14
	mov r3, #0x16
	add r0, r4, #0
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	ldr r1, [r4, #0x10]
	add r0, #0x18
	bl MOD08_02217CD0
	add sp, #0x10
	pop {r3, r4, r5, pc}
_0222335C:
	mov r2, #0
	str r2, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r1, #0x18
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	add r0, #0x18
	add r3, r2, #0
	bl MOD08_02217E80
	ldr r0, [r4, #0xc]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0222337C:
	add r0, r4, #0
	add r0, #0x18
	bl MOD08_02217ECC
	cmp r0, #0
	beq _0222339E
	mov r2, #0x14
	mov r3, #0x16
	add r0, r4, #0
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	ldr r1, [r4, #0x10]
	add r0, #0x18
	bl MOD08_02217CD0
	add sp, #0x10
	pop {r3, r4, r5, pc}
_0222339E:
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl FUN_02007558
	mov r2, #0x16
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_02007558
	mov r1, #0
	str r1, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r2, [r4, #0x3c]
	add r0, r4, #0
	lsl r2, r2, #5
	neg r2, r2
	lsl r2, r2, #0x10
	add r0, #0x18
	asr r2, r2, #0x10
	add r3, r1, #0
	bl MOD08_02217E80
	ldr r0, [r4, #0xc]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_022233DC:
	add r0, r4, #0
	ldr r2, [r4, #0x48]
	add r0, #0x4c
	add r1, #0x70
	bl MOD08_02217FE4
	cmp r0, #0
	bne _022234D2
	mov r0, #0x46
	ldrsh r0, [r4, r0]
	add r1, r4, #0
	mov r2, #0x44
	str r0, [sp]
	mov r0, #0x16
	ldrsh r0, [r4, r0]
	mov r3, #0x14
	add r1, #0x70
	str r0, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	ldr r0, _022234DC ; =0xFFFE0000
	str r0, [sp, #0xc]
	add r0, r4, #0
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	add r0, #0x4c
	bl MOD08_02217F50
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _022234D2
_0222341C:
	add r0, r4, #0
	ldr r2, [r4, #0x48]
	add r0, #0x4c
	add r1, #0x70
	bl MOD08_02217FE4
	cmp r0, #0
	bne _022234D2
	ldr r0, [r4, #0x48]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _022234D2
_0222343C:
	add r0, r4, #0
	add r0, #0x18
	bl MOD08_02217ECC
	cmp r0, #0
	beq _0222345C
	mov r2, #0x14
	mov r3, #0x16
	add r0, r4, #0
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	ldr r1, [r4, #0x10]
	add r0, #0x18
	bl MOD08_02217CD0
	b _022234D2
_0222345C:
	mov r2, #0
	str r2, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r1, #0x18
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	add r0, #0x18
	add r3, r2, #0
	bl MOD08_02217E80
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _022234D2
_0222347A:
	add r0, r4, #0
	add r0, #0x18
	bl MOD08_02217ECC
	cmp r0, #0
	beq _0222349A
	mov r2, #0x14
	mov r3, #0x16
	add r0, r4, #0
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	ldr r1, [r4, #0x10]
	add r0, #0x18
	bl MOD08_02217CD0
	b _022234D2
_0222349A:
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl FUN_02007558
	mov r2, #0x16
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_02007558
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _022234D2
_022234BA:
	ldr r0, [r4, #0x48]
	bl FUN_0200C3DC
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x10
	pop {r3, r4, r5, pc}
_022234D2:
	ldr r0, [r4, #8]
	bl FUN_0200BC1C
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_022234DC: .word 0xFFFE0000

	thumb_func_start MOD08_022234E0
MOD08_022234E0: ; 0x022234E0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r1, #0
	mov r1, #0x94
	add r5, r0, #0
	str r2, [sp, #0x10]
	add r6, r3, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4]
	ldr r0, [sp, #0x10]
	str r7, [r4, #4]
	str r0, [r4, #8]
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02217C1C
	str r0, [r4, #0x3c]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	str r0, [r4, #0x10]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #0x14]
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #0x16]
	mov r1, #0
	str r1, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r2, [r4, #0x3c]
	add r0, r4, #0
	lsl r2, r2, #4
	neg r2, r2
	lsl r2, r2, #0x10
	add r0, #0x18
	asr r2, r2, #0x10
	add r3, r1, #0
	bl MOD08_02217E80
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	mov r1, #0
	str r0, [r4, #0x40]
	bl FUN_0200782C
	add r1, r4, #0
	add r1, #0x44
	strh r0, [r1]
	ldr r0, [r4, #0x40]
	mov r1, #1
	bl FUN_0200782C
	add r1, r4, #0
	add r1, #0x46
	strh r0, [r1]
	add r0, r6, #0
	mov r1, #1
	str r6, [r4, #0x48]
	bl FUN_0200C5E0
	ldr r0, [r4, #0x48]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r4, #0x48]
	mov r1, #1
	bl FUN_0200C6B0
	mov r0, #0x16
	ldrsh r0, [r4, r0]
	add r1, r4, #0
	mov r2, #0x14
	str r0, [sp]
	mov r0, #0x46
	ldrsh r0, [r4, r0]
	mov r3, #0x44
	add r1, #0x70
	str r0, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	mov r0, #2
	lsl r0, r0, #0x10
	str r0, [sp, #0xc]
	add r0, r4, #0
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	add r0, #0x4c
	bl MOD08_02217F50
	ldr r0, [r4]
	ldr r1, _022235C8 ; =MOD08_02223310
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_022235C8: .word MOD08_02223310

	thumb_func_start MOD08_022235CC
MOD08_022235CC: ; 0x022235CC
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	add r2, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #3
	bhi _02223676
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022235E6: ; jump table
	.short _022235EE - _022235E6 - 2 ; case 0
	.short _0222361A - _022235E6 - 2 ; case 1
	.short _0222363E - _022235E6 - 2 ; case 2
	.short _02223664 - _022235E6 - 2 ; case 3
_022235EE:
	mov r2, #0x1a
	ldrsh r3, [r4, r2]
	mov r2, #0x68
	ldrsh r2, [r4, r2]
	mov r1, #0x18
	ldrsh r1, [r4, r1]
	sub r2, r3, r2
	add r0, r4, #0
	lsl r2, r2, #0x10
	ldr r3, [r4, #0x14]
	add r0, #0x1c
	asr r2, r2, #0x10
	bl MOD08_02217E30
	cmp r0, #0
	bne _02223676
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #0x10
	str r0, [r4, #0xc]
	b _02223676
_0222361A:
	ldr r0, [r4, #0xc]
	sub r0, r0, #1
	str r0, [r4, #0xc]
	bpl _02223676
	ldr r0, [r4, #8]
	mov r2, #0x10
	add r0, r0, #1
	str r0, [r4, #8]
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x40
	add r3, r2, #0
	bl MOD08_022186D4
	b _02223676
_0222363E:
	add r0, r4, #0
	add r0, #0x40
	bl MOD08_02218704
	cmp r0, #0
	beq _02223676
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl FUN_0200C644
	ldr r0, [r4, #0x10]
	mov r1, #6
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02223676
_02223664:
	ldr r0, [r4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #8
	pop {r4, pc}
_02223676:
	ldr r0, [r4, #4]
	bl FUN_0200BC1C
	add sp, #8
	pop {r4, pc}

	thumb_func_start MOD08_02223680
MOD08_02223680: ; 0x02223680
	push {r4, r5, r6, lr}
	sub sp, #8
	mov r1, #0x6c
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4]
	add r0, r5, #0
	bl MOD08_02212504
	str r0, [r4, #4]
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02217C1C
	add r6, r0, #0
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	str r0, [r4, #0x10]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #0x18]
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #0x1a]
	ldr r0, [r4, #0x10]
	mov r1, #0x29
	bl FUN_0200782C
	add r1, r4, #0
	add r1, #0x68
	strh r0, [r1]
	mov r0, #0x1a
	ldrsh r0, [r4, r0]
	mov r1, #0
	add r0, #8
	strh r0, [r4, #0x1a]
	ldr r0, [r4]
	bl MOD08_022124D8
	str r0, [r4, #0x14]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r4, #0x10]
	mov r1, #6
	mov r2, #1
	bl FUN_02007558
	add r0, r4, #0
	add r0, #0x1c
	mov r1, #2
	mov r2, #0x10
	bl MOD08_02218654
	ldr r0, [r4]
	mov r1, #0x10
	mov r2, #0
	bl MOD08_02227994
	mov r1, #0x10
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0
	add r0, #0x40
	add r3, r2, #0
	bl MOD08_022186D4
	ldr r0, [r4, #0x28]
	add r2, r4, #0
	add r1, r0, #0
	mul r1, r6
	str r1, [r4, #0x28]
	ldr r0, [r4]
	ldr r1, _02223740 ; =MOD08_022235CC
	bl MOD08_02212400
	ldr r0, [r4, #4]
	bl FUN_0200BC1C
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_02223740: .word MOD08_022235CC

	thumb_func_start MOD08_02223744
MOD08_02223744: ; 0x02223744
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x38]
	mov r4, #0
	cmp r0, #0
	beq _0222375A
	cmp r0, #1
	beq _0222378E
	cmp r0, #2
	beq _022237BA
	b _022237BC
_0222375A:
	add r0, r5, #0
	add r0, #0x14
	bl MOD08_02218170
	cmp r0, #0
	beq _02223774
	mov r2, #0x16
	ldrsh r2, [r5, r2]
	ldr r0, [r5, #0x10]
	mov r1, #0xd
	bl FUN_02007558
	b _022237BC
_02223774:
	ldr r0, [r5, #0x38]
	mov r2, #0xa
	add r0, r0, #1
	str r0, [r5, #0x38]
	mov r0, #0xc
	add r5, #0x14
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0xf
	add r3, r2, #0
	bl MOD08_02218120
	b _022237BC
_0222378E:
	add r0, r5, #0
	add r0, #0x14
	bl MOD08_02218170
	cmp r0, #0
	ldr r0, [r5, #0x10]
	beq _022237A8
	mov r2, #0x16
	ldrsh r2, [r5, r2]
	mov r1, #0xd
	bl FUN_02007558
	b _022237BC
_022237A8:
	mov r1, #0xd
	add r2, r1, #0
	add r2, #0xf3
	bl FUN_02007558
	ldr r0, [r5, #0x38]
	add r0, r0, #1
	str r0, [r5, #0x38]
	b _022237BC
_022237BA:
	mov r4, #1
_022237BC:
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_022237C0
MOD08_022237C0: ; 0x022237C0
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5, #0x40]
	mov r4, #0
	cmp r0, #0
	beq _022237D8
	cmp r0, #1
	beq _0222381E
	cmp r0, #2
	beq _0222383A
	b _0222383C
_022237D8:
	add r0, r5, #0
	ldr r1, [r5, #0x3c]
	add r0, #0x44
	bl MOD08_02218360
	add r0, r5, #0
	add r0, #0x68
	bl MOD08_02217ECC
	cmp r0, #0
	beq _02223802
	mov r2, #0xb4
	mov r3, #0xb6
	add r0, r5, #0
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	ldr r1, [r5, #0x3c]
	add r0, #0x68
	bl MOD08_02217C94
	b _0222383C
_02223802:
	ldr r0, [r5, #0x40]
	mov r1, #0x10
	add r0, r0, #1
	str r0, [r5, #0x40]
	str r1, [sp]
	mov r0, #8
	add r5, #0x8c
	str r0, [sp, #4]
	add r0, r5, #0
	add r2, r4, #0
	mov r3, #0xe
	bl MOD08_022186D4
	b _0222383C
_0222381E:
	add r0, r5, #0
	add r0, #0x8c
	bl MOD08_02218704
	cmp r0, #0
	beq _0222383C
	ldr r0, [r5, #0x3c]
	add r1, r4, #0
	bl FUN_0200C644
	ldr r0, [r5, #0x40]
	add r0, r0, #1
	str r0, [r5, #0x40]
	b _0222383C
_0222383A:
	mov r4, #1
_0222383C:
	add r0, r4, #0
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02223844
MOD08_02223844: ; 0x02223844
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _02223856
	cmp r0, #1
	beq _0222386E
	b _02223884
_02223856:
	add r0, r4, #0
	bl MOD08_02223744
	add r0, r4, #0
	bl MOD08_022237C0
	cmp r0, #0
	beq _02223884
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02223884
_0222386E:
	ldr r0, [r4, #0x3c]
	bl FUN_0200C3DC
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
_02223884:
	ldr r0, [r4, #8]
	bl FUN_0200BC1C
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_0222388C
MOD08_0222388C: ; 0x0222388C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	mov r1, #0xb8
	add r6, r0, #0
	add r7, r2, #0
	str r3, [sp, #8]
	bl MOD08_02228064
	add r4, r0, #0
	str r6, [r4]
	str r5, [r4, #4]
	str r7, [r4, #8]
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02217C1C
	str r0, [sp, #0xc]
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02217C44
	add r5, r0, #0
	add r0, r6, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	mov r1, #0
	str r0, [r4, #0x10]
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r7, r0, #0x10
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	mov r0, #0xc
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0xa
	add r0, #0x14
	add r2, r1, #0
	mov r3, #0xf
	bl MOD08_02218120
	ldr r0, [sp, #8]
	mov r1, #1
	str r0, [r4, #0x3c]
	bl FUN_0200C5E0
	ldr r0, [r4, #0x3c]
	mov r1, #2
	bl FUN_0200C840
	ldr r0, [r4, #0x3c]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r4, #0x3c]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r4, #0x3c]
	mov r1, #1
	bl FUN_0200C6B0
	ldr r0, [sp, #0xc]
	lsl r0, r0, #5
	add r1, r7, r0
	add r0, r4, #0
	add r0, #0xb4
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0xb6
	strh r6, [r0]
	cmp r5, #0
	bge _02223942
	mov r1, #7
	b _02223944
_02223942:
	mov r1, #0x17
_02223944:
	mvn r1, r1
	add r0, r1, #0
	mul r0, r5
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	mov r1, #0
	mov r0, #0x20
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x68
	add r2, r1, #0
	add r3, r1, #0
	bl MOD08_02217E80
	mov r0, #0x20
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x44
	mov r1, #5
	mov r2, #0xa
	mov r3, #0xc
	bl MOD08_02218120
	mov r0, #0x1a
	str r0, [sp]
	ldr r0, _02223994 ; =0x04000050
	mov r1, #0
	mov r2, #0x3f
	mov r3, #0x1f
	bl G2x_SetBlendAlpha_
	ldr r0, [r4]
	ldr r1, _02223998 ; =MOD08_02223844
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02223994: .word 0x04000050
_02223998: .word MOD08_02223844

	thumb_func_start MOD08_0222399C
MOD08_0222399C: ; 0x0222399C
	push {r3, lr}
	sub sp, #8
	ldr r1, [r0, #0x68]
	cmp r1, #5
	bhi _02223A50
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022239B2: ; jump table
	.short _022239BE - _022239B2 - 2 ; case 0
	.short _022239D4 - _022239B2 - 2 ; case 1
	.short _022239EE - _022239B2 - 2 ; case 2
	.short _02223A08 - _022239B2 - 2 ; case 3
	.short _02223A22 - _022239B2 - 2 ; case 4
	.short _02223A38 - _022239B2 - 2 ; case 5
_022239BE:
	mov r2, #0x28
	str r2, [sp]
	mov r1, #8
	str r1, [sp, #4]
	mov r1, #0
	add r0, #0x18
	add r3, r1, #0
	bl MOD08_02217E80
	add sp, #8
	pop {r3, pc}
_022239D4:
	mov r1, #0x4f
	mvn r1, r1
	str r1, [sp]
	mov r1, #8
	str r1, [sp, #4]
	mov r1, #0
	add r0, #0x18
	add r2, r1, #0
	add r3, r1, #0
	bl MOD08_02217E80
	add sp, #8
	pop {r3, pc}
_022239EE:
	mov r1, #0x50
	str r1, [sp]
	mov r1, #8
	str r1, [sp, #4]
	mov r1, #0
	add r2, r1, #0
	add r0, #0x18
	sub r2, #0x50
	add r3, r1, #0
	bl MOD08_02217E80
	add sp, #8
	pop {r3, pc}
_02223A08:
	mov r1, #0x4f
	mvn r1, r1
	str r1, [sp]
	mov r1, #8
	str r1, [sp, #4]
	mov r1, #0
	add r0, #0x18
	add r2, r1, #0
	add r3, r1, #0
	bl MOD08_02217E80
	add sp, #8
	pop {r3, pc}
_02223A22:
	mov r2, #0x50
	str r2, [sp]
	mov r1, #8
	str r1, [sp, #4]
	mov r1, #0
	add r0, #0x18
	add r3, r1, #0
	bl MOD08_02217E80
	add sp, #8
	pop {r3, pc}
_02223A38:
	mov r2, #0x27
	mvn r2, r2
	str r2, [sp]
	mov r1, #8
	str r1, [sp, #4]
	mov r1, #0
	add r0, #0x18
	add r3, r1, #0
	bl MOD08_02217E80
	add sp, #8
	pop {r3, pc}
_02223A50:
	bl ErrorHandling
	add sp, #8
	pop {r3, pc}

	thumb_func_start MOD08_02223A58
MOD08_02223A58: ; 0x02223A58
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #4
	bls _02223A68
	b _02223B7C
_02223A68:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02223A74: ; jump table
	.short _02223A7E - _02223A74 - 2 ; case 0
	.short _02223A9A - _02223A74 - 2 ; case 1
	.short _02223B1C - _02223A74 - 2 ; case 2
	.short _02223B52 - _02223A74 - 2 ; case 3
	.short _02223B64 - _02223A74 - 2 ; case 4
_02223A7E:
	ldr r0, [r4, #0x6c]
	add r0, r0, #1
	str r0, [r4, #0x6c]
	cmp r0, #4
	ble _02223B7C
	add r0, r4, #0
	bl MOD08_0222399C
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4, #0x6c]
	b _02223B7C
_02223A9A:
	add r0, r4, #0
	add r0, #0x18
	bl MOD08_02217ECC
	cmp r0, #0
	beq _02223ABA
	mov r2, #0x64
	mov r3, #0x66
	add r0, r4, #0
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	ldr r1, [r4, #0x14]
	add r0, #0x18
	bl MOD08_02217C94
	b _02223B7C
_02223ABA:
	ldr r0, [r4, #0x68]
	add r0, r0, #1
	str r0, [r4, #0x68]
	cmp r0, #6
	bge _02223AEA
	mov r0, #0
	str r0, [r4, #0xc]
	mov r0, #0x64
	ldrsh r1, [r4, r0]
	mov r0, #0x18
	ldrsh r0, [r4, r0]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0x64
	strh r1, [r0]
	mov r0, #0x66
	ldrsh r1, [r4, r0]
	mov r0, #0x1a
	ldrsh r0, [r4, r0]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0x66
	strh r1, [r0]
	b _02223B7C
_02223AEA:
	ldr r0, [r4, #0xc]
	mov r1, #1
	add r0, r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x14]
	bl FUN_0200C90C
	mov r1, #0x10
	add r0, r4, #0
	mov r2, #0
	str r1, [sp]
	add r0, #0x3c
	add r3, r2, #0
	str r1, [sp, #4]
	bl MOD08_022186D4
	ldr r0, _02223B88 ; =0x00007FFF
	mov r1, #0
	str r0, [sp]
	ldr r0, [r4, #0x10]
	mov r2, #0xa
	add r3, r1, #0
	bl FUN_02007E68
	b _02223B7C
_02223B1C:
	add r0, r4, #0
	add r0, #0x3c
	bl MOD08_02218704
	cmp r0, #0
	beq _02223B30
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl FUN_0200C644
_02223B30:
	ldr r0, [r4, #0x10]
	bl FUN_02007F20
	cmp r0, #0
	bne _02223B7C
	ldr r0, [r4, #0xc]
	mov r2, #0
	add r0, r0, #1
	str r0, [r4, #0xc]
	ldr r0, _02223B88 ; =0x00007FFF
	mov r1, #0xa
	str r0, [sp]
	ldr r0, [r4, #0x10]
	add r3, r2, #0
	bl FUN_02007E68
	b _02223B7C
_02223B52:
	ldr r0, [r4, #0x10]
	bl FUN_02007F20
	cmp r0, #0
	bne _02223B7C
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02223B7C
_02223B64:
	ldr r0, [r4, #0x14]
	bl FUN_0200C3DC
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, pc}
_02223B7C:
	ldr r0, [r4, #8]
	bl FUN_0200BC1C
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_02223B88: .word 0x00007FFF

	thumb_func_start MOD08_02223B8C
MOD08_02223B8C: ; 0x02223B8C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	mov r1, #0x70
	add r5, r0, #0
	str r2, [sp]
	add r6, r3, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4]
	ldr r0, [sp]
	str r7, [r4, #4]
	str r0, [r4, #8]
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	str r0, [r4, #0x10]
	str r6, [r4, #0x14]
	add r0, r6, #0
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl FUN_0200C6B0
	add r1, r4, #0
	add r2, r4, #0
	ldr r0, [r4, #0x14]
	add r1, #0x64
	add r2, #0x66
	bl FUN_0200C7A0
	ldr r0, [r4]
	ldr r1, _02223BE4 ; =MOD08_02223A58
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02223BE4: .word MOD08_02223A58

	thumb_func_start MOD08_02223BE8
MOD08_02223BE8: ; 0x02223BE8
	push {r3, lr}
	sub sp, #8
	ldr r1, [r0, #0x50]
	cmp r1, #3
	bhi _02223C6A
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02223BFE: ; jump table
	.short _02223C06 - _02223BFE - 2 ; case 0
	.short _02223C1C - _02223BFE - 2 ; case 1
	.short _02223C36 - _02223BFE - 2 ; case 2
	.short _02223C50 - _02223BFE - 2 ; case 3
_02223C06:
	mov r2, #0x50
	str r2, [sp]
	mov r1, #4
	str r1, [sp, #4]
	mov r1, #0
	add r0, #0x28
	add r3, r1, #0
	bl MOD08_02217E80
	add sp, #8
	pop {r3, pc}
_02223C1C:
	mov r1, #0x4f
	mvn r1, r1
	str r1, [sp]
	mov r1, #4
	str r1, [sp, #4]
	mov r1, #0
	add r0, #0x28
	add r2, r1, #0
	add r3, r1, #0
	bl MOD08_02217E80
	add sp, #8
	pop {r3, pc}
_02223C36:
	mov r1, #0x50
	str r1, [sp]
	mov r1, #4
	str r1, [sp, #4]
	mov r1, #0
	add r2, r1, #0
	add r0, #0x28
	sub r2, #0x50
	add r3, r1, #0
	bl MOD08_02217E80
	add sp, #8
	pop {r3, pc}
_02223C50:
	mov r1, #0x27
	mvn r1, r1
	str r1, [sp]
	mov r1, #4
	str r1, [sp, #4]
	mov r1, #0
	add r0, #0x28
	mov r2, #0x28
	add r3, r1, #0
	bl MOD08_02217E80
	add sp, #8
	pop {r3, pc}
_02223C6A:
	bl ErrorHandling
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD08_02223C74
MOD08_02223C74: ; 0x02223C74
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #6
	bhi _02223D7E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02223C8E: ; jump table
	.short _02223C9C - _02223C8E - 2 ; case 0
	.short _02223CB8 - _02223C8E - 2 ; case 1
	.short _02223D24 - _02223C8E - 2 ; case 2
	.short _02223D80 - _02223C8E - 2 ; case 3
	.short _02223DE2 - _02223C8E - 2 ; case 4
	.short _02223E02 - _02223C8E - 2 ; case 5
	.short _02223E30 - _02223C8E - 2 ; case 6
_02223C9C:
	ldr r0, [r4, #0x54]
	add r0, r0, #1
	str r0, [r4, #0x54]
	cmp r0, #1
	ble _02223D7E
	add r0, r4, #0
	bl MOD08_02223BE8
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4, #0x54]
	b _02223E48
_02223CB8:
	add r0, r4, #0
	add r0, #0x28
	bl MOD08_02217ECC
	cmp r0, #0
	beq _02223CD8
	mov r2, #0x4c
	mov r3, #0x4e
	add r0, r4, #0
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	ldr r1, [r4, #0x24]
	add r0, #0x28
	bl MOD08_02217C94
	b _02223E48
_02223CD8:
	ldr r0, [r4, #0x50]
	add r0, r0, #1
	str r0, [r4, #0x50]
	cmp r0, #4
	bge _02223D08
	mov r0, #0
	str r0, [r4, #0xc]
	mov r0, #0x4c
	ldrsh r1, [r4, r0]
	mov r0, #0x28
	ldrsh r0, [r4, r0]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0x4c
	strh r1, [r0]
	mov r0, #0x4e
	ldrsh r1, [r4, r0]
	mov r0, #0x2a
	ldrsh r0, [r4, r0]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0x4e
	strh r1, [r0]
	b _02223E48
_02223D08:
	ldr r0, [r4, #0xc]
	mov r1, #1
	add r0, r0, #1
	str r0, [r4, #0xc]
	mov r0, #8
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x24]
	bl FUN_0200C5C0
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl FUN_0200C5E0
	b _02223E48
_02223D24:
	ldr r0, [r4, #0x54]
	sub r0, r0, #1
	str r0, [r4, #0x54]
	bpl _02223D7E
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4]
	bl MOD08_02215504
	add r5, r0, #0
	ldr r0, [r4]
	bl MOD08_02214540
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	ldr r0, _02223E54 ; =0x0000FFFF
	mov r1, #1
	lsl r2, r2, #0x10
	add r3, r1, #0
	str r0, [sp, #8]
	add r0, r5, #0
	lsr r2, r2, #0x10
	sub r3, #9
	bl FUN_02003210
	ldr r7, _02223E54 ; =0x0000FFFF
	mov r6, #0
	add r5, r4, #0
_02223D64:
	ldr r0, [r5, #0x14]
	cmp r0, #0
	beq _02223D76
	mov r1, #0xe
	mov r2, #0x10
	mov r3, #0
	str r7, [sp]
	bl FUN_02007E68
_02223D76:
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #4
	blt _02223D64
_02223D7E:
	b _02223E48
_02223D80:
	ldr r0, [r4]
	bl MOD08_02215504
	bl FUN_020038E4
	cmp r0, #0
	bne _02223E48
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4]
	bl MOD08_02215504
	add r5, r0, #0
	ldr r0, [r4]
	bl MOD08_02214540
	add r2, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _02223E54 ; =0x0000FFFF
	mov r1, #1
	lsl r2, r2, #0x10
	add r3, r1, #0
	str r0, [sp, #8]
	add r0, r5, #0
	lsr r2, r2, #0x10
	sub r3, #9
	bl FUN_02003210
	ldr r7, _02223E54 ; =0x0000FFFF
	mov r6, #0
	add r5, r4, #0
_02223DC6:
	ldr r0, [r5, #0x14]
	cmp r0, #0
	beq _02223DD8
	mov r2, #0
	mov r1, #2
	add r3, r2, #0
	str r7, [sp]
	bl FUN_02007E68
_02223DD8:
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #4
	blt _02223DC6
	b _02223E48
_02223DE2:
	ldr r0, [r4]
	bl MOD08_02215504
	bl FUN_020038E4
	cmp r0, #0
	bne _02223E48
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	mov r0, #4
	str r0, [r4, #0x54]
	str r0, [r4, #0x50]
	mov r0, #0
	str r0, [r4, #0x58]
	b _02223E48
_02223E02:
	ldr r0, [r4, #0x54]
	sub r0, r0, #1
	str r0, [r4, #0x54]
	bpl _02223E48
	mov r0, #4
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x50]
	sub r0, r0, #1
	str r0, [r4, #0x50]
	bpl _02223E1E
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02223E48
_02223E1E:
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x58]
	bl FUN_0200C644
	ldr r1, [r4, #0x58]
	mov r0, #1
	eor r0, r1
	str r0, [r4, #0x58]
	b _02223E48
_02223E30:
	ldr r0, [r4, #0x24]
	bl FUN_0200C3DC
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_02223E48:
	ldr r0, [r4, #8]
	bl FUN_0200BC1C
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02223E54: .word 0x0000FFFF

	thumb_func_start MOD08_02223E58
MOD08_02223E58: ; 0x02223E58
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	mov r1, #0x5c
	add r5, r0, #0
	str r2, [sp, #4]
	add r7, r3, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4]
	ldr r0, [sp, #4]
	str r6, [r4, #4]
	str r0, [r4, #8]
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	str r0, [r4, #0x10]
	mov r6, #0
	add r5, r4, #0
_02223E88:
	ldr r0, [r4]
	add r1, r6, #0
	bl MOD08_022154D4
	str r0, [r5, #0x14]
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #4
	blt _02223E88
	str r7, [r4, #0x24]
	add r0, r7, #0
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl FUN_0200C6B0
	add r1, r4, #0
	add r2, r4, #0
	ldr r0, [r4, #0x24]
	add r1, #0x4c
	add r2, #0x4e
	bl FUN_0200C7A0
	mov r1, #0x4c
	ldrsh r2, [r4, r1]
	add r0, r4, #0
	add r0, #0x4c
	sub r2, #0x28
	strh r2, [r0]
	mov r2, #0x4e
	ldrsh r3, [r4, r2]
	add r0, r4, #0
	add r0, #0x4e
	sub r3, #0x28
	strh r3, [r0]
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x24]
	bl FUN_0200C714
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl FUN_0200C90C
	mov r0, #0xf
	mvn r0, r0
	str r0, [r4, #0x54]
	mov r0, #0x1a
	str r0, [sp]
	ldr r0, _02223F08 ; =0x04000050
	mov r1, #0
	mov r2, #0x3f
	mov r3, #0x1f
	bl G2x_SetBlendAlpha_
	ldr r0, [r4]
	ldr r1, _02223F0C ; =MOD08_02223C74
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02223F08: .word 0x04000050
_02223F0C: .word MOD08_02223C74

	thumb_func_start MOD08_02223F10
MOD08_02223F10: ; 0x02223F10
	push {r3, r4, r5, lr}
	ldr r2, _02223F50 ; =0x00000AAA
	add r4, r0, #0
	add r5, r1, #0
	add r0, #0x10
	mov r1, #0
	mov r3, #3
	bl MOD08_02218030
	cmp r5, #0
	beq _02223F3C
	mov r0, #0
	ldr r1, [r4, #0x18]
	mvn r0, r0
	mul r0, r1
	str r0, [r4, #0x18]
	ldr r0, [r4, #8]
	mov r1, #0xa
	mov r2, #0x10
	bl FUN_02007558
	b _02223F48
_02223F3C:
	mov r1, #0xa
	add r2, r1, #0
	ldr r0, [r4, #8]
	sub r2, #0x1a
	bl FUN_02007558
_02223F48:
	mov r0, #0
	str r0, [r4, #0x4c]
	str r0, [r4, #0x50]
	pop {r3, r4, r5, pc}
	.align 2, 0
_02223F50: .word 0x00000AAA

	thumb_func_start MOD08_02223F54
MOD08_02223F54: ; 0x02223F54
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0x4c]
	mov r5, #0
	cmp r0, #3
	bhi _0222405E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02223F6E: ; jump table
	.short _02223F76 - _02223F6E - 2 ; case 0
	.short _02223FB6 - _02223F6E - 2 ; case 1
	.short _02224012 - _02223F6E - 2 ; case 2
	.short _0222405C - _02223F6E - 2 ; case 3
_02223F76:
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_02218080
	ldr r0, [r4, #8]
	ldr r2, [r4, #0x10]
	mov r1, #9
	bl FUN_02007558
	ldr r0, [r4, #0x50]
	sub r0, r0, #1
	str r0, [r4, #0x50]
	bpl _0222405E
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
	mov r0, #0xe
	ldrsh r3, [r4, r0]
	mov r0, #0xc
	ldrsh r1, [r4, r0]
	add r0, r3, #2
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	mov r0, #2
	add r4, #0x24
	str r0, [sp, #4]
	add r0, r4, #0
	add r2, r1, #0
	bl MOD08_02217E80
	b _0222405E
_02223FB6:
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_02218080
	cmp r0, #0
	beq _02223FCC
	ldr r0, [r4, #8]
	ldr r2, [r4, #0x10]
	mov r1, #9
	bl FUN_02007558
_02223FCC:
	add r0, r4, #0
	ldr r1, [r4, #8]
	add r0, #0x24
	bl MOD08_02217F2C
	cmp r0, #0
	bne _0222405E
	ldr r0, [r4, #0x4c]
	mov r2, #0
	add r0, r0, #1
	str r0, [r4, #0x4c]
	ldr r1, [r4, #0x10]
	add r0, r4, #0
	lsl r1, r1, #0x10
	add r0, #0x10
	asr r1, r1, #0x10
	mov r3, #3
	bl MOD08_02218030
	mov r0, #0xe
	ldrsh r3, [r4, r0]
	mov r0, #0xc
	ldrsh r1, [r4, r0]
	mov r0, #2
	add r4, #0x24
	str r3, [sp]
	add r3, r3, #2
	lsl r3, r3, #0x10
	str r0, [sp, #4]
	add r0, r4, #0
	add r2, r1, #0
	asr r3, r3, #0x10
	bl MOD08_02217E80
	b _0222405E
_02224012:
	add r0, r4, #0
	ldr r1, [r4, #8]
	add r0, #0x24
	bl MOD08_02217F2C
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_02218080
	cmp r0, #0
	ldr r0, [r4, #8]
	beq _02224034
	ldr r2, [r4, #0x10]
	mov r1, #9
	bl FUN_02007558
	b _0222405E
_02224034:
	mov r2, #0xc
	ldrsh r2, [r4, r2]
	add r1, r5, #0
	bl FUN_02007558
	mov r2, #0xe
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_02007558
	ldr r0, [r4, #8]
	mov r1, #9
	add r2, r5, #0
	bl FUN_02007558
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
	b _0222405E
_0222405C:
	mov r5, #1
_0222405E:
	add r0, r5, #0
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02224064
MOD08_02224064: ; 0x02224064
	push {r4, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _02224076
	cmp r0, #1
	beq _022240A8
	pop {r4, pc}
_02224076:
	add r0, r4, #0
	bl MOD08_02223F54
	cmp r0, #0
	beq _022240B6
	ldr r0, [r4, #0x48]
	add r0, r0, #1
	str r0, [r4, #0x48]
	cmp r0, #4
	bge _022240A0
	ldr r1, [r4, #0x54]
	mov r0, #1
	eor r1, r0
	add r0, r4, #0
	str r1, [r4, #0x54]
	bl MOD08_02223F10
	add r0, r4, #0
	bl MOD08_02223F54
	pop {r4, pc}
_022240A0:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_022240A8:
	ldr r0, [r4, #4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_022240B6:
	pop {r4, pc}

	thumb_func_start MOD08_022240B8
MOD08_022240B8: ; 0x022240B8
	push {r4, r5, r6, lr}
	mov r1, #0x58
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4, #4]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_02217C1C
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #0
	bl MOD08_02212498
	cmp r0, #0
	bne _02224104
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_022154D4
	str r0, [r4, #8]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #0xc]
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_0200782C
	b _02224124
_02224104:
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_022154D4
	str r0, [r4, #8]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #0xc]
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_0200782C
_02224124:
	strh r0, [r4, #0xe]
	ldr r0, [r4, #8]
	mov r1, #0xb
	mov r2, #0x32
	bl FUN_02007558
	cmp r6, #1
	bne _02224138
	mov r0, #0
	b _0222413A
_02224138:
	mov r0, #1
_0222413A:
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x54]
	add r0, r4, #0
	bl MOD08_02223F10
	ldr r0, [r4, #4]
	ldr r1, _02224150 ; =MOD08_02224064
	add r2, r4, #0
	bl MOD08_02212400
	pop {r4, r5, r6, pc}
	.align 2, 0
_02224150: .word MOD08_02224064

	thumb_func_start MOD08_02224154
MOD08_02224154: ; 0x02224154
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x38]
	mov r5, #0
	cmp r0, #3
	bhi _02224210
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222416C: ; jump table
	.short _02224174 - _0222416C - 2 ; case 0
	.short _022241A4 - _0222416C - 2 ; case 1
	.short _022241C6 - _0222416C - 2 ; case 2
	.short _022241F6 - _0222416C - 2 ; case 3
_02224174:
	add r0, r4, #0
	ldr r1, [r4, #0xc]
	add r0, #0x10
	bl MOD08_02218380
	cmp r0, #0
	beq _0222419C
	add r0, r5, #0
	str r0, [sp]
	ldr r1, [r4, #0x3c]
	ldr r2, [r4, #0x40]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r4, #0xc]
	ldr r3, [r4, #0x24]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl MOD08_022182DC
	b _02224210
_0222419C:
	ldr r0, [r4, #0x38]
	add r0, r0, #1
	str r0, [r4, #0x38]
	b _02224210
_022241A4:
	ldr r0, [r4, #0x34]
	sub r0, r0, #1
	str r0, [r4, #0x34]
	bpl _02224210
	ldr r0, [r4, #0x38]
	mov r2, #0xa
	add r0, r0, #1
	str r0, [r4, #0x38]
	mov r0, #8
	add r4, #0x10
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0xf
	add r3, r2, #0
	bl MOD08_02218120
	b _02224210
_022241C6:
	add r0, r4, #0
	ldr r1, [r4, #0xc]
	add r0, #0x10
	bl MOD08_02218380
	cmp r0, #0
	beq _022241EE
	add r0, r5, #0
	str r0, [sp]
	ldr r1, [r4, #0x3c]
	ldr r2, [r4, #0x40]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r4, #0xc]
	ldr r3, [r4, #0x24]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl MOD08_022182DC
	b _02224210
_022241EE:
	ldr r0, [r4, #0x38]
	add r0, r0, #1
	str r0, [r4, #0x38]
	b _02224210
_022241F6:
	mov r1, #0xc
	add r2, r1, #0
	ldr r0, [r4, #0xc]
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r4, #0xc]
	add r2, #0xf3
	bl FUN_02007558
	mov r5, #1
_02224210:
	add r0, r5, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02224214
MOD08_02224214: ; 0x02224214
	push {r4, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _0222422A
	cmp r0, #1
	beq _02224240
	cmp r0, #2
	beq _02224250
	pop {r4, pc}
_0222422A:
	add r0, r4, #0
	bl MOD08_02224154
	cmp r0, #0
	beq _0222425E
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0x10
	str r0, [r4, #8]
	pop {r4, pc}
_02224240:
	ldr r0, [r4, #8]
	sub r0, r0, #1
	str r0, [r4, #8]
	bpl _0222425E
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, pc}
_02224250:
	ldr r0, [r4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_0222425E:
	pop {r4, pc}

	thumb_func_start MOD08_02224260
MOD08_02224260: ; 0x02224260
	push {r3, r4, r5, lr}
	mov r1, #0x44
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	str r0, [r4, #0xc]
	mov r0, #8
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0xa
	add r0, #0x10
	add r2, r1, #0
	mov r3, #0xf
	bl MOD08_02218120
	mov r0, #4
	str r0, [r4, #0x34]
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_0221552C
	str r0, [r4, #0x40]
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0200782C
	str r0, [r4, #0x3c]
	ldr r0, [r4]
	ldr r1, _022242BC ; =MOD08_02224214
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, pc}
	nop
_022242BC: .word MOD08_02224214

	thumb_func_start MOD08_022242C0
MOD08_022242C0: ; 0x022242C0
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5, #0x74]
	mov r1, #0x64
	bl _s32_div_f
	add r4, r0, #0
	ldr r0, [r5, #0x78]
	mov r1, #0x64
	bl _s32_div_f
	add r6, r0, #0
	ldr r0, [r5, #0x70]
	mov r1, #0x64
	bl _s32_div_f
	str r0, [sp]
	add r0, r5, #0
	lsl r1, r4, #0x10
	lsl r3, r6, #0x10
	add r0, #0x18
	asr r1, r1, #0x10
	mov r2, #0xa
	asr r3, r3, #0x10
	bl MOD08_02218120
	ldr r0, [r5]
	mov r1, #0x10
	mov r2, #0
	bl MOD08_02227994
	ldr r0, [r5, #0x70]
	mov r1, #0x64
	bl _s32_div_f
	mov r1, #6
	str r1, [sp]
	lsl r0, r0, #1
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x3c
	mov r1, #0x10
	mov r2, #0xa
	mov r3, #0
	bl MOD08_022186D4
	mov r0, #0
	str r0, [r5, #0x64]
	str r0, [r5, #0x68]
	add sp, #8
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_02224328
MOD08_02224328: ; 0x02224328
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x64]
	mov r5, #0
	cmp r0, #3
	bhi _022243FC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02224340: ; jump table
	.short _02224348 - _02224340 - 2 ; case 0
	.short _0222438E - _02224340 - 2 ; case 1
	.short _022243E4 - _02224340 - 2 ; case 2
	.short _022243FA - _02224340 - 2 ; case 3
_02224348:
	add r0, r4, #0
	ldr r1, [r4, #0x14]
	add r0, #0x18
	bl MOD08_02218360
	cmp r0, #0
	bne _022243FC
	ldr r0, [r4, #0x78]
	mov r1, #0x64
	bl _s32_div_f
	add r6, r0, #0
	ldr r0, [r4, #0x74]
	mov r1, #0x64
	bl _s32_div_f
	add r7, r0, #0
	ldr r0, [r4, #0x70]
	mov r1, #0x64
	bl _s32_div_f
	str r0, [sp]
	add r0, r4, #0
	lsl r1, r6, #0x10
	lsl r3, r7, #0x10
	add r0, #0x18
	asr r1, r1, #0x10
	mov r2, #0xa
	asr r3, r3, #0x10
	bl MOD08_02218120
	ldr r0, [r4, #0x64]
	add r0, r0, #1
	str r0, [r4, #0x64]
	b _022243FC
_0222438E:
	add r0, r4, #0
	ldr r1, [r4, #0x14]
	add r0, #0x18
	bl MOD08_02218360
	cmp r0, #0
	bne _022243FC
	ldr r0, [r4, #0x68]
	add r0, r0, #1
	str r0, [r4, #0x68]
	cmp r0, #2
	bge _022243DC
	add r0, r5, #0
	str r0, [r4, #0x64]
	ldr r0, [r4, #0x74]
	mov r1, #0x64
	bl _s32_div_f
	add r6, r0, #0
	ldr r0, [r4, #0x78]
	mov r1, #0x64
	bl _s32_div_f
	add r7, r0, #0
	ldr r0, [r4, #0x70]
	mov r1, #0x64
	bl _s32_div_f
	lsl r1, r6, #0x10
	lsl r3, r7, #0x10
	add r4, #0x18
	str r0, [sp]
	add r0, r4, #0
	asr r1, r1, #0x10
	mov r2, #0xa
	asr r3, r3, #0x10
	bl MOD08_02218120
	b _022243FC
_022243DC:
	ldr r0, [r4, #0x64]
	add r0, r0, #1
	str r0, [r4, #0x64]
	b _022243FC
_022243E4:
	add r0, r4, #0
	add r0, #0x3c
	bl MOD08_02218704
	cmp r0, #0
	beq _022243FC
	ldr r0, [r4, #0x64]
	mov r5, #1
	add r0, r0, #1
	str r0, [r4, #0x64]
	b _022243FC
_022243FA:
	mov r5, #1
_022243FC:
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02224400
MOD08_02224400: ; 0x02224400
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r1, [r5, #0x7c]
	mov r4, #0
	cmp r1, #0
	beq _02224416
	cmp r1, #1
	beq _02224428
	cmp r1, #2
	beq _02224472
	b _02224474
_02224416:
	bl MOD08_022242C0
	add r0, r5, #0
	bl MOD08_02224328
	ldr r0, [r5, #0x7c]
	add r0, r0, #1
	str r0, [r5, #0x7c]
	b _02224474
_02224428:
	bl MOD08_02224328
	cmp r0, #0
	beq _02224474
	ldr r0, [r5, #0x6c]
	sub r0, r0, #1
	str r0, [r5, #0x6c]
	bmi _02224468
	ldr r0, [r5, #0x70]
	mov r1, #3
	bl _s32_div_f
	ldr r1, [r5, #0x70]
	sub r0, r1, r0
	str r0, [r5, #0x70]
	ldr r0, [r5, #0x74]
	mov r1, #3
	bl _s32_div_f
	ldr r1, [r5, #0x74]
	sub r0, r1, r0
	str r0, [r5, #0x74]
	ldr r0, [r5, #0x78]
	mov r1, #3
	bl _s32_div_f
	ldr r1, [r5, #0x78]
	sub r0, r1, r0
	str r0, [r5, #0x78]
	add r0, r4, #0
	str r0, [r5, #0x7c]
	b _02224474
_02224468:
	ldr r0, [r5, #0x7c]
	mov r4, #1
	add r0, r0, #1
	str r0, [r5, #0x7c]
	b _02224474
_02224472:
	mov r4, #1
_02224474:
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02224478
MOD08_02224478: ; 0x02224478
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #4
	bls _02224488
	b _022245A8
_02224488:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02224494: ; jump table
	.short _0222449E - _02224494 - 2 ; case 0
	.short _022244E4 - _02224494 - 2 ; case 1
	.short _02224544 - _02224494 - 2 ; case 2
	.short _02224574 - _02224494 - 2 ; case 3
	.short _02224590 - _02224494 - 2 ; case 4
_0222449E:
	add r0, r4, #0
	bl MOD08_02224400
	cmp r0, #0
	beq _022245A8
	ldr r0, [r4, #0xc]
	mov r1, #0
	add r0, r0, #1
	str r0, [r4, #0xc]
	mov r0, #0x1e
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x14]
	bl FUN_0200C5C0
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl FUN_0200C5E0
	mov r1, #0xfe
	lsl r1, r1, #0x16
	ldr r0, [r4, #0x14]
	add r2, r1, #0
	bl FUN_0200C884
	mov r1, #0
	mov r2, #0x10
	str r1, [sp]
	mov r0, #4
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x3c
	add r3, r2, #0
	bl MOD08_022186D4
	b _022245A8
_022244E4:
	ldr r0, [r4, #0x10]
	cmp r0, #0
	bne _02224502
	mov r0, #1
	str r0, [sp]
	mov r0, #8
	mov r1, #0x10
	mov r2, #0
	mov r3, #0xd
	bl FUN_0200A208
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #0x10]
	b _02224508
_02224502:
	ble _02224508
	sub r0, r0, #1
	str r0, [r4, #0x10]
_02224508:
	mov r0, #0
	ldr r1, [r4, #0x10]
	mvn r0, r0
	cmp r1, r0
	bne _02224532
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #0
	beq _02224532
	mov r0, #1
	str r0, [sp]
	mov r0, #8
	mov r1, #0
	mov r2, #0x10
	mov r3, #0xd
	bl FUN_0200A208
	mov r0, #1
	mvn r0, r0
	str r0, [r4, #0x10]
_02224532:
	ldr r0, [r4, #0x14]
	bl FUN_0200C608
	cmp r0, #0
	bne _022245A8
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _022245A8
_02224544:
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #0
	beq _022245A8
	ldr r0, [r4, #0xc]
	mov r1, #0x10
	add r0, r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4]
	mov r2, #0
	bl MOD08_02227994
	mov r1, #0x10
	mov r2, #0
	str r1, [sp]
	mov r0, #8
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x3c
	add r3, r2, #0
	bl MOD08_022186D4
	b _022245A8
_02224574:
	add r0, r4, #0
	add r0, #0x3c
	bl MOD08_02218704
	cmp r0, #0
	beq _022245A8
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _022245A8
_02224590:
	ldr r0, [r4, #0x14]
	bl FUN_0200C3DC
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, pc}
_022245A8:
	ldr r0, [r4, #8]
	bl FUN_0200BC1C
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_022245B4
MOD08_022245B4: ; 0x022245B4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	mov r1, #0x80
	add r6, r0, #0
	str r2, [sp]
	add r5, r3, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r6, [r4]
	ldr r0, [sp]
	str r7, [r4, #4]
	str r0, [r4, #8]
	str r5, [r4, #0x14]
	add r0, r5, #0
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl FUN_0200C6B0
	ldr r0, [r4, #0x14]
	mov r1, #2
	bl FUN_0200C840
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r4, #0x14]
	mov r1, #4
	bl FUN_0200C61C
	mov r0, #3
	str r0, [r4, #0x6c]
	mov r0, #0x19
	lsl r0, r0, #4
	str r0, [r4, #0x70]
	ldr r0, _02224618 ; =0x000005DC
	ldr r1, _0222461C ; =MOD08_02224478
	str r0, [r4, #0x74]
	mov r0, #0xfa
	lsl r0, r0, #2
	str r0, [r4, #0x78]
	ldr r0, [r4]
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02224618: .word 0x000005DC
_0222461C: .word MOD08_02224478

	thumb_func_start MOD08_02224620
MOD08_02224620: ; 0x02224620
	push {r3, lr}
	sub sp, #8
	ldr r1, [r0, #0x34]
	cmp r1, #3
	bhi _02224668
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02224636: ; jump table
	.short _0222463E - _02224636 - 2 ; case 0
	.short _02224656 - _02224636 - 2 ; case 1
	.short _0222463E - _02224636 - 2 ; case 2
	.short _02224656 - _02224636 - 2 ; case 3
_0222463E:
	mov r1, #0x20
	str r1, [sp]
	mov r1, #6
	str r1, [sp, #4]
	mov r1, #0
	add r0, #0x10
	add r2, r1, #0
	add r3, r1, #0
	bl MOD08_02217E80
	add sp, #8
	pop {r3, pc}
_02224656:
	mov r1, #0
	str r1, [sp]
	mov r2, #6
	str r2, [sp, #4]
	add r0, #0x10
	add r2, r1, #0
	mov r3, #0x20
	bl MOD08_02217E80
_02224668:
	add sp, #8
	pop {r3, pc}

	thumb_func_start MOD08_0222466C
MOD08_0222466C: ; 0x0222466C
	push {r4, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _02224682
	cmp r0, #1
	beq _02224690
	cmp r0, #2
	beq _022246C8
	pop {r4, pc}
_02224682:
	add r0, r4, #0
	bl MOD08_02224620
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_02224690:
	add r0, r4, #0
	add r0, #0x10
	bl MOD08_02217ECC
	cmp r0, #0
	beq _022246B0
	mov r2, #0xc
	mov r3, #0xe
	add r0, r4, #0
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	ldr r1, [r4, #8]
	add r0, #0x10
	bl MOD08_02217CD0
	pop {r4, pc}
_022246B0:
	ldr r0, [r4, #0x34]
	add r0, r0, #1
	str r0, [r4, #0x34]
	cmp r0, #4
	bge _022246C0
	mov r0, #0
	str r0, [r4]
	pop {r4, pc}
_022246C0:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_022246C8:
	ldr r0, [r4, #4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD08_022246D8
MOD08_022246D8: ; 0x022246D8
	push {r3, r4, r5, lr}
	mov r1, #0x38
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4, #4]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_022154D4
	str r0, [r4, #8]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #0xc]
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #0xe]
	mov r0, #0
	str r0, [r4, #0x34]
	ldr r0, [r4, #4]
	ldr r1, _02224718 ; =MOD08_0222466C
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, pc}
	.align 2, 0
_02224718: .word MOD08_0222466C

	thumb_func_start MOD08_0222471C
MOD08_0222471C: ; 0x0222471C
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	add r2, r0, #0
	ldr r0, [r4]
	cmp r0, #6
	bhi _0222477E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02224736: ; jump table
	.short _02224744 - _02224736 - 2 ; case 0
	.short _02224762 - _02224736 - 2 ; case 1
	.short _022247DA - _02224736 - 2 ; case 2
	.short _0222481E - _02224736 - 2 ; case 3
	.short _0222485C - _02224736 - 2 ; case 4
	.short _022248A4 - _02224736 - 2 ; case 5
	.short _022248D4 - _02224736 - 2 ; case 6
_02224744:
	add r0, r4, #0
	add r0, #0x14
	mov r1, #1
	mov r2, #0x40
	bl MOD08_02218654
	ldr r1, [r4, #0x20]
	ldr r0, [r4, #8]
	add sp, #8
	mul r0, r1
	str r0, [r4, #0x20]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_02224762:
	mov r2, #0x12
	ldrsh r2, [r4, r2]
	mov r1, #0x10
	add r0, r4, #0
	add r2, #8
	lsl r2, r2, #0x10
	ldrsh r1, [r4, r1]
	ldr r3, [r4, #0xc]
	add r0, #0x14
	asr r2, r2, #0x10
	bl MOD08_02217E58
	cmp r0, #0
	beq _02224780
_0222477E:
	b _022248E2
_02224780:
	mov r2, #0x10
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl FUN_02007558
	mov r2, #0x12
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_02007558
	mov r0, #0x10
	ldrsh r1, [r4, r0]
	mov r3, #0
	mov r0, #2
	add r2, r1, #0
	str r3, [sp]
	add r2, #0x20
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r2, r2, #0x10
	add r0, #0x14
	asr r2, r2, #0x10
	bl MOD08_02217E80
	ldr r1, [r4, #0x1c]
	ldr r0, [r4, #8]
	mul r0, r1
	str r0, [r4, #0x1c]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02217ECC
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl FUN_02007558
	add sp, #8
	pop {r4, pc}
_022247DA:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02217ECC
	cmp r0, #0
	beq _022247F6
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl FUN_02007558
	add sp, #8
	pop {r4, pc}
_022247F6:
	mov r0, #0x3c
	ldrsh r1, [r4, r0]
	mov r3, #0
	mov r0, #2
	str r3, [sp]
	str r0, [sp, #4]
	ldr r2, [r4, #8]
	add r0, r4, #0
	lsl r2, r2, #5
	add r2, r1, r2
	lsl r2, r2, #0x10
	add r0, #0x40
	asr r2, r2, #0x10
	bl MOD08_02217E80
	ldr r0, [r4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_0222481E:
	add r0, r4, #0
	add r0, #0x40
	bl MOD08_02217ECC
	cmp r0, #0
	beq _0222483A
	mov r2, #0x40
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x38]
	mov r1, #0
	bl FUN_02007558
	add sp, #8
	pop {r4, pc}
_0222483A:
	mov r3, #0
	str r3, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r1, #0x14
	mov r2, #0x10
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	add r0, #0x14
	bl MOD08_02217E80
	ldr r0, [r4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_0222485C:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02217ECC
	cmp r0, #0
	ldr r0, [r4, #0xc]
	beq _02224878
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	mov r1, #0
	bl FUN_02007558
	add sp, #8
	pop {r4, pc}
_02224878:
	mov r2, #0x10
	ldrsh r2, [r4, r2]
	mov r1, #0
	bl FUN_02007558
	mov r3, #0
	str r3, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r1, #0x40
	mov r2, #0x3c
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	add r0, #0x40
	bl MOD08_02217E80
	ldr r0, [r4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_022248A4:
	add r0, r4, #0
	add r0, #0x40
	bl MOD08_02217ECC
	cmp r0, #0
	ldr r0, [r4, #0x38]
	beq _022248C0
	mov r2, #0x40
	ldrsh r2, [r4, r2]
	mov r1, #0
	bl FUN_02007558
	add sp, #8
	pop {r4, pc}
_022248C0:
	mov r2, #0x3c
	ldrsh r2, [r4, r2]
	mov r1, #0
	bl FUN_02007558
	ldr r0, [r4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_022248D4:
	ldr r0, [r4, #4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_022248E2:
	add sp, #8
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_022248E8
MOD08_022248E8: ; 0x022248E8
	push {r3, r4, r5, lr}
	mov r1, #0x64
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4, #4]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_02217C1C
	str r0, [r4, #8]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_022154D4
	str r0, [r4, #0xc]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #0x10]
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #0x12]
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD08_022154D4
	str r0, [r4, #0x38]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #0x3c]
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #0x3e]
	ldr r0, [r4, #4]
	ldr r1, _02224958 ; =MOD08_0222471C
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, pc}
	nop
_02224958: .word MOD08_0222471C

	thumb_func_start MOD08_0222495C
MOD08_0222495C: ; 0x0222495C
	push {lr}
	sub sp, #0xc
	mov r1, #0
	str r1, [r0, #0x40]
	mov r1, #8
	str r1, [sp]
	mov r1, #0xa
	str r1, [sp, #4]
	mov r2, #2
	str r2, [sp, #8]
	add r0, #0x1c
	mov r2, #9
	add r3, r1, #0
	bl MOD08_022181A8
	add sp, #0xc
	pop {pc}
	.align 2, 0

	thumb_func_start MOD08_02224980
MOD08_02224980: ; 0x02224980
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	mov r5, #0
	cmp r0, #3
	bhi _02224A72
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222499A: ; jump table
	.short _022249A2 - _0222499A - 2 ; case 0
	.short _022249E8 - _0222499A - 2 ; case 1
	.short _02224A2A - _0222499A - 2 ; case 2
	.short _02224A70 - _0222499A - 2 ; case 3
_022249A2:
	add r0, r4, #0
	ldr r1, [r4, #0x18]
	add r0, #0x1c
	bl MOD08_022183A0
	cmp r0, #0
	beq _022249C6
	add r0, r5, #0
	str r0, [sp]
	mov r1, #0x44
	mov r2, #0x46
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x18]
	ldr r3, [r4, #0x30]
	bl MOD08_022182DC
	b _02224A72
_022249C6:
	ldr r0, [r4, #0x40]
	mov r1, #9
	add r0, r0, #1
	str r0, [r4, #0x40]
	mov r0, #0xf
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #2
	add r4, #0x1c
	str r0, [sp, #8]
	add r0, r4, #0
	mov r2, #0xb
	mov r3, #8
	bl MOD08_022181A8
	b _02224A72
_022249E8:
	add r0, r4, #0
	ldr r1, [r4, #0x18]
	add r0, #0x1c
	bl MOD08_022183A0
	cmp r0, #0
	beq _02224A0C
	add r0, r5, #0
	str r0, [sp]
	mov r1, #0x44
	mov r2, #0x46
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x18]
	ldr r3, [r4, #0x30]
	bl MOD08_022182DC
	b _02224A72
_02224A0C:
	ldr r0, [r4, #0x40]
	mov r2, #0xa
	add r0, r0, #1
	str r0, [r4, #0x40]
	str r2, [sp]
	str r2, [sp, #4]
	mov r0, #2
	add r4, #0x1c
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0xb
	mov r3, #0xf
	bl MOD08_022181A8
	b _02224A72
_02224A2A:
	add r0, r4, #0
	ldr r1, [r4, #0x18]
	add r0, #0x1c
	bl MOD08_022183A0
	cmp r0, #0
	beq _02224A4E
	add r0, r5, #0
	str r0, [sp]
	mov r1, #0x44
	mov r2, #0x46
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x18]
	ldr r3, [r4, #0x30]
	bl MOD08_022182DC
	b _02224A72
_02224A4E:
	mov r1, #0xc
	add r2, r1, #0
	ldr r0, [r4, #0x18]
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r4, #0x18]
	add r2, #0xf3
	bl FUN_02007558
	ldr r0, [r4, #0x40]
	mov r5, #1
	add r0, r0, #1
	str r0, [r4, #0x40]
	b _02224A72
_02224A70:
	mov r5, #1
_02224A72:
	add r0, r5, #0
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start MOD08_02224A78
MOD08_02224A78: ; 0x02224A78
	push {r3, r4, r5, lr}
	add r4, r2, #0
	mov r2, #0
	str r2, [r1]
	add r5, r0, #0
	mov r1, #0x64
	bl FUN_0200C6C4
	add r0, r5, #0
	mov r1, #1
	bl FUN_0200C6B0
	add r0, r5, #0
	mov r1, #1
	bl FUN_0200C644
	add r0, r5, #0
	mov r1, #1
	bl FUN_0200C5E0
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0200C5F4
	add r0, r5, #0
	mov r1, #0
	bl FUN_0200C5C0
	add r0, r5, #0
	mov r1, #0
	bl FUN_0200C61C
	mov r1, #0x37
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl FUN_0200C5B4
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02224AC4
MOD08_02224AC4: ; 0x02224AC4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	mov r4, #0
	cmp r1, #0
	beq _02224AD6
	cmp r1, #1
	beq _02224AE8
	b _02224AEC
_02224AD6:
	bl FUN_0200C608
	cmp r0, #0
	bne _02224AEE
	ldr r0, [r5]
	mov r4, #1
	add r0, r0, #1
	str r0, [r5]
	b _02224AEE
_02224AE8:
	mov r4, #1
	b _02224AEE
_02224AEC:
	mov r4, #1
_02224AEE:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02224AF4
MOD08_02224AF4: ; 0x02224AF4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r7, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #5
	bls _02224B02
	b _02224C14
_02224B02:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02224B0E: ; jump table
	.short _02224B1A - _02224B0E - 2 ; case 0
	.short _02224B3E - _02224B0E - 2 ; case 1
	.short _02224B76 - _02224B0E - 2 ; case 2
	.short _02224BA6 - _02224B0E - 2 ; case 3
	.short _02224BCC - _02224B0E - 2 ; case 4
	.short _02224BF2 - _02224B0E - 2 ; case 5
_02224B1A:
	add r0, r4, #0
	bl MOD08_0222495C
	ldr r0, [r4, #0x10]
	add r1, r4, #0
	lsl r2, r0, #2
	add r0, r4, r2
	add r1, #0x60
	add r1, r1, r2
	mov r2, #2
	ldr r0, [r0, #0x48]
	lsl r2, r2, #0xc
	bl MOD08_02224A78
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02224C14
_02224B3E:
	add r0, r4, #0
	bl MOD08_02224980
	add r5, r0, #0
	ldr r0, [r4, #0x10]
	add r1, r4, #0
	lsl r2, r0, #2
	add r0, r4, r2
	add r1, #0x60
	ldr r0, [r0, #0x48]
	add r1, r1, r2
	bl MOD08_02224AC4
	cmp r5, r0
	bne _02224C14
	cmp r5, #1
	bne _02224C14
	ldr r0, [r4, #0x10]
	mov r1, #1
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #0x48]
	bl FUN_0200C5C0
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02224C14
_02224B76:
	ldr r0, [r4, #0x10]
	add r2, r4, #0
	add r2, #0x78
	lsl r1, r0, #2
	ldr r0, [r2, r1]
	sub r0, r0, #1
	str r0, [r2, r1]
	ldr r1, [r4, #0x10]
	lsl r0, r1, #2
	add r0, r4, r0
	ldr r0, [r0, #0x78]
	cmp r0, #0
	bge _02224C14
	add r0, r1, #1
	str r0, [r4, #0x10]
	cmp r0, #6
	bge _02224B9E
	mov r0, #0
	str r0, [r4, #0xc]
	b _02224C14
_02224B9E:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02224C14
_02224BA6:
	add r6, r4, #0
	mov r7, #0
	add r6, #0x60
	add r5, r4, #0
_02224BAE:
	mov r2, #2
	ldr r0, [r5, #0x48]
	add r1, r6, #0
	lsl r2, r2, #0xc
	bl MOD08_02224A78
	add r7, r7, #1
	add r6, r6, #4
	add r5, r5, #4
	cmp r7, #6
	blt _02224BAE
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02224C14
_02224BCC:
	add r6, r4, #0
	mov r7, #0
	add r6, #0x60
	add r5, r4, #0
_02224BD4:
	ldr r0, [r5, #0x48]
	add r1, r6, #0
	bl MOD08_02224AC4
	add r7, r7, #1
	add r6, r6, #4
	add r5, r5, #4
	cmp r7, #6
	blt _02224BD4
	cmp r0, #1
	bne _02224C14
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02224C14
_02224BF2:
	mov r6, #0
	add r5, r4, #0
_02224BF6:
	ldr r0, [r5, #0x48]
	bl FUN_0200C3DC
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #6
	blt _02224BF6
	ldr r0, [r4]
	add r1, r7, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
_02224C14:
	ldr r0, [r4, #8]
	bl FUN_0200BC1C
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02224C1C
MOD08_02224C1C: ; 0x02224C1C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x50
	str r1, [sp]
	mov r1, #0x90
	add r4, r0, #0
	str r2, [sp, #4]
	str r3, [sp, #8]
	bl MOD08_02228064
	ldr r1, [sp]
	str r4, [r0]
	str r1, [r0, #4]
	ldr r1, [sp, #4]
	str r0, [sp, #0x14]
	str r1, [r0, #8]
	ldr r0, [r0]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	bl MOD08_022154D4
	ldr r1, [sp, #0x14]
	str r0, [r1, #0x18]
	mov r1, #0
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r7, r0, #0x10
	ldr r0, [sp, #0x14]
	mov r1, #1
	ldr r0, [r0, #0x18]
	bl FUN_0200782C
	ldr r1, [sp, #0x14]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r1, #0x44
	str r0, [sp, #0xc]
	strh r0, [r1]
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	bl MOD08_0221552C
	ldr r1, [sp, #0x14]
	add r1, #0x46
	strh r0, [r1]
	ldr r1, [sp, #0x14]
	add r0, sp, #0x1c
	ldr r1, [r1]
	bl MOD08_02215474
	ldr r5, [sp, #0x14]
	mov r4, #0
_02224C94:
	cmp r4, #0
	bne _02224C9C
	ldr r0, [sp, #8]
	b _02224CA6
_02224C9C:
	ldr r0, [sp]
	ldr r1, [sp, #4]
	add r2, sp, #0x1c
	bl FUN_0200C154
_02224CA6:
	str r0, [r5, #0x48]
	ldr r0, [r5, #0x48]
	mov r1, #0
	bl FUN_0200C644
	lsr r0, r4, #0x1f
	add r0, r4, r0
	asr r1, r0, #1
	ldr r0, _02224D6C ; =0x00001555
	mov r2, #3
	mul r0, r1
	asr r0, r0, #4
	lsl r0, r0, #2
	ldr r1, _02224D70 ; =FX_SinCosTable_
	str r0, [sp, #0x18]
	add r1, r1, r0
	mov r0, #2
	ldrsh r0, [r1, r0]
	lsl r2, r2, #0x10
	mov r3, #0
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #2
	lsl r2, r2, #0xa
	add r2, r0, r2
	ldr r0, _02224D74 ; =0x00000000
	adc r1, r0
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	lsl r0, r1, #4
	asr r6, r0, #0x10
	mov r2, #3
	ldr r1, _02224D70 ; =FX_SinCosTable_
	ldr r0, [sp, #0x18]
	lsl r2, r2, #0x10
	ldrsh r0, [r1, r0]
	mov r3, #0
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #2
	lsl r2, r2, #0xa
	add r0, r0, r2
	ldr r2, _02224D74 ; =0x00000000
	adc r1, r2
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	lsl r0, r0, #4
	asr r0, r0, #0x10
	str r0, [sp, #0x10]
	lsr r2, r4, #0x1f
	lsl r1, r4, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	bne _02224D2E
	add r0, r7, r6
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	ldr r0, [r5, #0x48]
	mov r1, #1
	bl FUN_0200C8D0
	b _02224D34
_02224D2E:
	sub r0, r7, r6
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
_02224D34:
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	sub r0, r1, r0
	lsl r0, r0, #0x10
	asr r2, r0, #0x10
	ldr r0, [r5, #0x48]
	add r1, r6, #0
	bl FUN_0200C714
	cmp r4, #2
	bge _02224D4E
	mov r0, #8
	b _02224D50
_02224D4E:
	mov r0, #0
_02224D50:
	add r4, r4, #1
	str r0, [r5, #0x78]
	add r5, r5, #4
	cmp r4, #6
	blt _02224C94
	ldr r0, [sp, #0x14]
	ldr r1, _02224D78 ; =MOD08_02224AF4
	ldr r0, [r0]
	ldr r2, [sp, #0x14]
	bl MOD08_02212400
	add sp, #0x50
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02224D6C: .word 0x00001555
_02224D70: .word FX_SinCosTable_
_02224D74: .word 0x00000000
_02224D78: .word MOD08_02224AF4

	thumb_func_start MOD08_02224D7C
MOD08_02224D7C: ; 0x02224D7C
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #5
	bhi _02224DBC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02224D96: ; jump table
	.short _02224DA2 - _02224D96 - 2 ; case 0
	.short _02224DB2 - _02224D96 - 2 ; case 1
	.short _02224E12 - _02224D96 - 2 ; case 2
	.short _02224E6E - _02224D96 - 2 ; case 3
	.short _02224E9E - _02224D96 - 2 ; case 4
	.short _02224EC2 - _02224D96 - 2 ; case 5
_02224DA2:
	ldr r0, [r4, #0x5c]
	mov r1, #1
	bl FUN_0200C5E0
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02224EDA
_02224DB2:
	ldr r0, [r4, #0x5c]
	bl FUN_0200C608
	cmp r0, #0
	beq _02224DBE
_02224DBC:
	b _02224EDA
_02224DBE:
	ldr r0, [r4, #0x5c]
	mov r1, #0
	bl FUN_0200C5E0
	ldr r0, [r4, #0xc]
	mov r1, #0xa
	add r0, r0, #1
	str r0, [r4, #0xc]
	mov r0, #8
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x14
	add r2, r1, #0
	mov r3, #0
	bl MOD08_02218120
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl FUN_0200782C
	add r5, r0, #0
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200782C
	add r3, r0, #0
	mov r0, #0x8a
	ldrsh r0, [r4, r0]
	lsl r1, r5, #0x10
	lsl r3, r3, #0x10
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r2, #0x88
	add r0, r4, #0
	ldrsh r2, [r4, r2]
	add r0, #0x38
	asr r1, r1, #0x10
	asr r3, r3, #0x10
	bl MOD08_02217E80
	b _02224EDA
_02224E12:
	add r0, r4, #0
	ldr r1, [r4, #0x10]
	add r0, #0x38
	bl MOD08_02217F2C
	add r0, r4, #0
	ldr r1, [r4, #0x10]
	add r0, #0x14
	bl MOD08_02218380
	cmp r0, #0
	bne _02224EDA
	ldr r0, [r4, #0x10]
	mov r1, #6
	mov r2, #1
	bl FUN_02007558
	mov r1, #0xc
	add r2, r1, #0
	ldr r0, [r4, #0x10]
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r4, #0x10]
	add r2, #0xf3
	bl FUN_02007558
	ldr r0, [r4, #0x5c]
	mov r1, #1
	bl FUN_0200C5C0
	mov r1, #1
	ldr r0, [r4, #0x5c]
	lsl r1, r1, #0xc
	bl FUN_0200C5F4
	ldr r0, [r4, #0x5c]
	mov r1, #1
	bl FUN_0200C5E0
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02224EDA
_02224E6E:
	ldr r0, [r4, #0x5c]
	bl FUN_0200C608
	cmp r0, #0
	bne _02224EDA
	ldr r0, [r4, #0x5c]
	mov r1, #0
	bl FUN_0200C5E0
	ldr r0, [r4, #0xc]
	mov r1, #0
	add r0, r0, #1
	str r0, [r4, #0xc]
	str r1, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r3, #0x8a
	add r0, r4, #0
	ldrsh r3, [r4, r3]
	add r0, #0x60
	add r2, r1, #0
	bl MOD08_02217E80
	b _02224EDA
_02224E9E:
	add r0, r4, #0
	add r0, #0x60
	bl MOD08_02217ECC
	cmp r0, #0
	beq _02224EBA
	mov r1, #0x88
	mov r2, #0x62
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x5c]
	bl FUN_0200C714
	b _02224EDA
_02224EBA:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02224EDA
_02224EC2:
	ldr r0, [r4, #0x5c]
	bl FUN_0200C3DC
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, pc}
_02224EDA:
	ldr r0, [r4, #8]
	bl FUN_0200BC1C
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02224EE4
MOD08_02224EE4: ; 0x02224EE4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	mov r1, #0x8c
	add r5, r0, #0
	str r2, [sp]
	add r6, r3, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4]
	ldr r0, [sp]
	str r7, [r4, #4]
	str r0, [r4, #8]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	mov r1, #6
	mov r2, #0
	str r0, [r4, #0x10]
	bl FUN_02007558
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	mov r2, #0
	bl MOD08_02217B98
	add r1, r4, #0
	add r1, #0x88
	strh r0, [r1]
	add r0, r5, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r5, #0
	mov r2, #1
	bl MOD08_02217B98
	add r1, r4, #0
	add r1, #0x8a
	strh r0, [r1]
	str r6, [r4, #0x5c]
	add r0, r6, #0
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r4, #0x5c]
	mov r1, #1
	bl FUN_0200C6B0
	mov r1, #0x88
	mov r2, #0x8a
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x5c]
	bl FUN_0200C714
	ldr r0, [r4]
	ldr r1, _02224F70 ; =MOD08_02224D7C
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02224F70: .word MOD08_02224D7C

	thumb_func_start MOD08_02224F74
MOD08_02224F74: ; 0x02224F74
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	add r0, r1, #0
	bl MOD08_02217C08
	mov r1, #1
	add r2, r1, #0
	lsl r2, r0
	mov r0, #0
	lsl r2, r2, #0x10
	add r4, #0xc4
	str r0, [sp]
	ldr r0, [r4]
	mov r1, #2
	lsr r2, r2, #0x10
	mov r3, #8
	bl FUN_02003A64
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02224FA0
MOD08_02224FA0: ; 0x02224FA0
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r1, #0xa
	mov r0, #0x14
	str r0, [sp]
	str r1, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x28
	add r2, r1, #0
	add r3, r1, #0
	bl MOD08_022181A8
	mov r0, #4
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0xa
	add r0, #0x4c
	add r2, r1, #0
	mov r3, #1
	bl MOD08_02218120
	add r0, r4, #0
	mov r1, #0
	add r0, #0x94
	str r1, [r0]
	add r0, r4, #0
	mov r1, #6
	add r0, #0x98
	str r1, [r0]
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02227468
	add r1, r0, #0
	lsl r2, r1, #1
	ldr r1, _0222503C ; =0x0222C664
	ldr r0, [r4, #0x20]
	ldrh r1, [r1, r2]
	bl FUN_0200C644
	ldr r0, [r4, #0x18]
	mov r1, #1
	bl FUN_0200C644
	add r0, r4, #0
	add r0, #0x28
	add r1, sp, #0x10
	add r2, sp, #0xc
	bl MOD08_0221825C
	add r0, r4, #0
	add r0, #0xc8
	ldr r0, [r0]
	cmp r0, #1
	bne _02225024
	ldr r1, [sp, #0x10]
	mov r0, #0
	bl _fsub
	str r0, [sp, #0x10]
_02225024:
	ldr r0, [r4, #0x18]
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0xc]
	bl FUN_0200C884
	ldr r1, [r4, #0x18]
	add r0, r4, #0
	bl MOD08_02224F74
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_0222503C: .word MOD8_0222C664

	thumb_func_start MOD08_02225040
MOD08_02225040: ; 0x02225040
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r0, #0x94
	ldr r0, [r0]
	mov r4, #0
	cmp r0, #0
	beq _0222505C
	cmp r0, #1
	beq _022250E4
	cmp r0, #2
	bne _0222505A
	b _02225164
_0222505A:
	b _02225166
_0222505C:
	add r0, r5, #0
	add r0, #0x28
	bl MOD08_02218224
	add r0, r5, #0
	add r0, #0x28
	add r1, sp, #0x10
	add r2, sp, #0xc
	bl MOD08_0221825C
	add r0, r5, #0
	add r0, #0xc8
	ldr r0, [r0]
	cmp r0, #1
	bne _02225084
	ldr r1, [sp, #0x10]
	add r0, r4, #0
	bl _fsub
	str r0, [sp, #0x10]
_02225084:
	ldr r0, [r5, #0x18]
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0xc]
	bl FUN_0200C884
	mov r0, #0
	str r0, [sp]
	ldr r1, [r5, #0x14]
	ldr r2, [r5, #0x10]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r5, #0x18]
	ldr r3, [r5, #0x3c]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl MOD08_02218314
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r5, #0
	add r0, #0x98
	str r1, [r0]
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	cmp r0, #0
	bge _02225166
	add r0, r5, #0
	add r0, #0x94
	ldr r0, [r0]
	mov r3, #0x14
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0x94
	str r1, [r0]
	str r3, [sp]
	mov r1, #0xa
	str r1, [sp, #4]
	mov r0, #4
	add r5, #0x28
	str r0, [sp, #8]
	add r0, r5, #0
	mov r2, #1
	bl MOD08_022181A8
	b _02225166
_022250E4:
	add r0, r5, #0
	add r0, #0x28
	bl MOD08_02218224
	add r0, r5, #0
	add r0, #0x4c
	bl MOD08_02218170
	cmp r0, #0
	beq _02225142
	mov r0, #0x4c
	ldrsh r0, [r5, r0]
	add r1, sp, #0x10
	add r2, sp, #0xc
	strh r0, [r5, #0x28]
	add r0, r5, #0
	add r0, #0x28
	bl MOD08_0221825C
	add r0, r5, #0
	add r0, #0xc8
	ldr r0, [r0]
	cmp r0, #1
	bne _0222511E
	ldr r1, [sp, #0x10]
	add r0, r4, #0
	bl _fsub
	str r0, [sp, #0x10]
_0222511E:
	ldr r0, [r5, #0x18]
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0xc]
	bl FUN_0200C884
	mov r0, #0
	str r0, [sp]
	ldr r1, [r5, #0x14]
	ldr r2, [r5, #0x10]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r5, #0x18]
	ldr r3, [r5, #0x3c]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl MOD08_02218314
	b _02225166
_02225142:
	add r0, r5, #0
	add r0, #0x94
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0x94
	str r1, [r0]
	ldr r0, [r5, #0x20]
	add r1, r4, #0
	bl FUN_0200C644
	ldr r0, [r5, #0x18]
	add r1, r4, #0
	bl FUN_0200C644
	mov r4, #1
	b _02225166
_02225164:
	mov r4, #1
_02225166:
	add r0, r4, #0
	add sp, #0x14
	pop {r4, r5, pc}

	thumb_func_start MOD08_0222516C
MOD08_0222516C: ; 0x0222516C
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0
	add r1, sp, #0xc
	ldr r0, [r4, #0x1c]
	add r1, #2
	add r2, sp, #0xc
	bl FUN_0200C7A0
	add r1, sp, #0xc
	mov r0, #0
	ldrsh r3, [r1, r0]
	mov r0, #2
	ldrsh r1, [r1, r0]
	mov r0, #8
	str r3, [sp]
	sub r3, #0x40
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r3, r3, #0x10
	add r0, #0x70
	add r2, r1, #0
	asr r3, r3, #0x10
	bl MOD08_02217E80
	mov r2, #0xa
	str r2, [sp]
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x28
	mov r1, #2
	mov r3, #0x14
	bl MOD08_022181A8
	add r0, r4, #0
	add r0, #0x28
	add r1, sp, #0x14
	add r2, sp, #0x10
	bl MOD08_0221825C
	add r0, r4, #0
	add r0, #0xcc
	ldr r0, [r0]
	cmp r0, #1
	bne _022251D4
	ldr r1, [sp, #0x14]
	mov r0, #0
	bl _fsub
	str r0, [sp, #0x14]
_022251D4:
	ldr r0, [r4, #0x1c]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	bl FUN_0200C884
	add r0, r4, #0
	ldr r1, [r4, #0x1c]
	add r0, #0x70
	bl MOD08_02217F08
	add r0, r4, #0
	mov r1, #0
	add r0, #0x94
	str r1, [r0]
	add r0, r4, #0
	mov r1, #6
	add r0, #0x98
	str r1, [r0]
	ldr r0, [r4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02227468
	add r1, r0, #0
	lsl r2, r1, #1
	ldr r1, _02225228 ; =0x0222C664
	ldr r0, [r4, #0x24]
	ldrh r1, [r1, r2]
	bl FUN_0200C644
	ldr r0, [r4, #0x1c]
	mov r1, #1
	bl FUN_0200C644
	ldr r1, [r4, #0x1c]
	add r0, r4, #0
	bl MOD08_02224F74
	add sp, #0x18
	pop {r4, pc}
	.align 2, 0
_02225228: .word MOD8_0222C664

	thumb_func_start MOD08_0222522C
MOD08_0222522C: ; 0x0222522C
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	add r0, #0x94
	ldr r0, [r0]
	mov r4, #0
	cmp r0, #0
	beq _02225246
	cmp r0, #1
	beq _02225276
	cmp r0, #2
	beq _022252C8
	b _022252CA
_02225246:
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r5, #0
	add r0, #0x98
	str r1, [r0]
	add r0, r5, #0
	ldr r1, [r5, #0x1c]
	add r0, #0x70
	bl MOD08_02217F08
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	cmp r0, #0
	bge _022252CA
	add r0, r5, #0
	add r0, #0x94
	ldr r0, [r0]
	add r5, #0x94
	add r0, r0, #1
	str r0, [r5]
	b _022252CA
_02225276:
	add r0, r5, #0
	ldr r1, [r5, #0x1c]
	add r0, #0x70
	bl MOD08_02217F08
	add r0, r5, #0
	add r0, #0x28
	bl MOD08_02218224
	add r6, r0, #0
	add r0, r5, #0
	add r0, #0x28
	add r1, sp, #4
	add r2, sp, #0
	bl MOD08_0221825C
	add r0, r5, #0
	add r0, #0xcc
	ldr r0, [r0]
	cmp r0, #1
	bne _022252AA
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl _fsub
	str r0, [sp, #4]
_022252AA:
	ldr r0, [r5, #0x1c]
	ldr r1, [sp, #4]
	ldr r2, [sp]
	bl FUN_0200C884
	cmp r6, #0
	bne _022252CA
	add r0, r5, #0
	add r0, #0x94
	ldr r0, [r0]
	add r5, #0x94
	add r0, r0, #1
	str r0, [r5]
	mov r4, #1
	b _022252CA
_022252C8:
	mov r4, #1
_022252CA:
	add r0, r4, #0
	add sp, #8
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_022252D0
MOD08_022252D0: ; 0x022252D0
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	add r2, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #6
	bhi _022253AA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022252EA: ; jump table
	.short _022252F8 - _022252EA - 2 ; case 0
	.short _0222531C - _022252EA - 2 ; case 1
	.short _02225336 - _022252EA - 2 ; case 2
	.short _0222534C - _022252EA - 2 ; case 3
	.short _02225362 - _022252EA - 2 ; case 4
	.short _02225388 - _022252EA - 2 ; case 5
	.short _0222539C - _022252EA - 2 ; case 6
_022252F8:
	ldr r0, [r4]
	mov r1, #0
	mov r2, #0x10
	bl MOD08_02227994
	mov r2, #8
	str r2, [sp]
	add r0, r4, #0
	str r2, [sp, #4]
	add r0, #0x9c
	mov r1, #0
	mov r3, #0x10
	bl MOD08_022186D4
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _022253AA
_0222531C:
	add r0, r4, #0
	add r0, #0x9c
	bl MOD08_02218704
	cmp r0, #0
	beq _022253AA
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	add r0, r4, #0
	bl MOD08_02224FA0
	b _022253AA
_02225336:
	add r0, r4, #0
	bl MOD08_02225040
	cmp r0, #0
	beq _022253AA
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #2
	str r0, [r4, #0xc]
	b _022253AA
_0222534C:
	ldr r0, [r4, #0xc]
	sub r0, r0, #1
	str r0, [r4, #0xc]
	bpl _022253AA
	add r0, r4, #0
	bl MOD08_0222516C
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _022253AA
_02225362:
	add r0, r4, #0
	bl MOD08_0222522C
	cmp r0, #0
	beq _022253AA
	ldr r0, [r4, #8]
	mov r1, #8
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #0x10
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x9c
	mov r2, #0
	add r3, r1, #0
	str r1, [sp, #4]
	bl MOD08_022186D4
	b _022253AA
_02225388:
	add r0, r4, #0
	add r0, #0x9c
	bl MOD08_02218704
	cmp r0, #0
	beq _022253AA
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _022253AA
_0222539C:
	ldr r0, [r4]
	add r1, r2, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
_022253AA:
	ldr r0, [r4, #4]
	bl FUN_0200BC1C
	add sp, #8
	pop {r4, pc}

	thumb_func_start MOD08_022253B4
MOD08_022253B4: ; 0x022253B4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r1, #0xd0
	add r6, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r6, [r4]
	add r0, r6, #0
	bl MOD08_02212504
	str r0, [r4, #4]
	ldr r0, [r4]
	bl MOD08_02215504
	add r1, r4, #0
	add r1, #0xc4
	str r0, [r1]
	add r0, r6, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	mov r1, #0
	add r7, r0, #0
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	add r0, r7, #0
	mov r1, #1
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r5, r0, #0x10
	add r0, r7, #0
	mov r1, #0x29
	bl FUN_0200782C
	sub r0, r5, r0
	lsl r0, r0, #0x10
	asr r5, r0, #0x10
	add r0, r6, #0
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	mov r1, #0
	str r0, [sp, #4]
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r7, r0, #0x10
	ldr r0, [sp, #4]
	mov r1, #1
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	ldr r0, [sp, #4]
	mov r1, #0x29
	bl FUN_0200782C
	sub r0, r6, r0
	lsl r0, r0, #0x10
	str r5, [r4, #0x14]
	asr r6, r0, #0x10
	ldr r0, [r4]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_0221552C
	str r0, [r4, #0x10]
	ldr r0, [r4]
	mov r1, #0
	bl MOD08_022124D8
	str r0, [r4, #0x18]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r4, #0x18]
	mov r1, #1
	bl FUN_0200C6B0
	ldr r0, [r4, #0x18]
	ldr r1, [sp]
	add r2, r5, #0
	bl FUN_0200C714
	ldr r0, [r4, #0x18]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0x18]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r4, #0x18]
	mov r1, #2
	bl FUN_0200C840
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_022124D8
	str r0, [r4, #0x1c]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r4, #0x1c]
	mov r1, #1
	bl FUN_0200C6B0
	ldr r0, [r4, #0x1c]
	add r1, r7, #0
	add r2, r6, #0
	bl FUN_0200C714
	ldr r0, [r4, #0x1c]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0x1c]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r4, #0x1c]
	mov r1, #2
	bl FUN_0200C840
	ldr r0, [r4, #0x1c]
	mov r1, #0
	mov r2, #0x28
	bl FUN_0200C8DC
	ldr r0, [r4]
	mov r1, #0
	bl MOD08_02215680
	add r1, r4, #0
	add r1, #0xc8
	str r0, [r1]
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_02215680
	add r1, r4, #0
	add r1, #0xcc
	str r0, [r1]
	ldr r0, [r4]
	mov r1, #2
	bl MOD08_022124D8
	str r0, [r4, #0x20]
	ldr r0, [r4]
	mov r1, #3
	bl MOD08_022124D8
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x20]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4]
	ldr r1, _02225520 ; =MOD08_022252D0
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02225520: .word MOD08_022252D0

	thumb_func_start MOD08_02225524
MOD08_02225524: ; 0x02225524
	push {r4, lr}
	sub sp, #0x20
	mov r2, #0xa
	add r4, r0, #0
	add r0, #0xf8
	mov r1, #0x19
	add r3, r2, #0
	str r2, [sp]
	bl MOD08_02218120
	mov r0, #0x3a
	ldrsh r0, [r4, r0]
	add r1, r4, #0
	mov r3, #0x38
	str r0, [sp]
	mov r0, #9
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x44]
	ldr r2, _02225570 ; =MOD08_02218170
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x40]
	add r1, #0xf8
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x3c]
	str r0, [sp, #0x18]
	mov r0, #0
	str r0, [sp, #0x1c]
	add r0, r4, #0
	ldrsh r3, [r4, r3]
	add r0, #0x48
	bl MOD08_0221847C
	add sp, #0x20
	pop {r4, pc}
	.align 2, 0
_02225570: .word MOD08_02218170

	thumb_func_start MOD08_02225574
MOD08_02225574: ; 0x02225574
	push {r4, lr}
	sub sp, #0x20
	add r4, r0, #0
	mov r0, #6
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0xa
	add r0, #0xf8
	add r2, r1, #0
	mov r3, #0x19
	bl MOD08_02218120
	mov r0, #0x3a
	ldrsh r0, [r4, r0]
	add r1, r4, #0
	mov r3, #0x38
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x3c]
	ldr r2, _022255CC ; =MOD08_02218170
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x40]
	add r1, #0xf8
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x44]
	str r0, [sp, #0x18]
	mov r0, #0
	str r0, [sp, #0x1c]
	add r0, r4, #0
	ldrsh r3, [r4, r3]
	add r0, #0x48
	bl MOD08_0221847C
	ldr r0, [r4, #0x3c]
	mov r1, #1
	bl FUN_0200C644
	add sp, #0x20
	pop {r4, pc}
	.align 2, 0
_022255CC: .word MOD08_02218170

	thumb_func_start MOD08_022255D0
MOD08_022255D0: ; 0x022255D0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r7, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #4
	bhi _02225688
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022255E8: ; jump table
	.short _022255F2 - _022255E8 - 2 ; case 0
	.short _02225600 - _022255E8 - 2 ; case 1
	.short _0222562E - _022255E8 - 2 ; case 2
	.short _02225652 - _022255E8 - 2 ; case 3
	.short _02225666 - _022255E8 - 2 ; case 4
_022255F2:
	add r0, r4, #0
	bl MOD08_02225524
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02225688
_02225600:
	add r0, r4, #0
	add r0, #0x48
	bl MOD08_02218524
	cmp r0, #0
	bne _02225688
	ldr r0, [r4, #0x3c]
	mov r1, #1
	bl FUN_0200C644
	ldr r0, [r4, #0xc]
	mov r1, #4
	add r0, r0, #1
	str r0, [r4, #0xc]
	mov r0, #6
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x14
	mov r2, #0
	mov r3, #1
	bl MOD08_022183C0
	b _02225688
_0222562E:
	mov r1, #0x38
	mov r2, #0x3a
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r3, [r4, #0x10]
	add r0, #0x14
	bl MOD08_02218454
	cmp r0, #0
	bne _02225688
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	add r0, r4, #0
	bl MOD08_02225574
	b _02225688
_02225652:
	add r0, r4, #0
	add r0, #0x48
	bl MOD08_02218524
	cmp r0, #0
	bne _02225688
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02225688
_02225666:
	mov r6, #0
	add r5, r4, #0
_0222566A:
	ldr r0, [r5, #0x3c]
	bl FUN_0200C3DC
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #3
	blt _0222566A
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r4]
	add r1, r7, #0
	bl MOD08_02212438
	pop {r3, r4, r5, r6, r7, pc}
_02225688:
	ldr r0, [r4, #8]
	bl FUN_0200BC1C
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02225690
MOD08_02225690: ; 0x02225690
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r6, r1, #0
	mov r1, #0x47
	lsl r1, r1, #2
	add r5, r0, #0
	str r2, [sp]
	add r7, r3, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4]
	ldr r0, [sp]
	str r6, [r4, #4]
	str r0, [r4, #8]
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	str r0, [r4, #0x10]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #0x38]
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #0x3a]
	ldr r0, [r4, #0x10]
	mov r1, #0x29
	bl FUN_0200782C
	mov r1, #0x3a
	ldrsh r1, [r4, r1]
	sub r0, r1, r0
	strh r0, [r4, #0x3a]
	add r0, sp, #4
	add r1, r5, #0
	bl MOD08_02215474
	mov r6, #0
	add r5, r4, #0
_022256EC:
	cmp r6, #0
	bne _022256FC
	add r0, r7, #0
	mov r1, #1
	str r7, [r5, #0x3c]
	bl FUN_0200C5C0
	b _0222570E
_022256FC:
	ldr r0, [r4, #4]
	ldr r1, [r4, #8]
	add r2, sp, #4
	bl FUN_0200C154
	mov r1, #1
	str r0, [r5, #0x3c]
	bl FUN_0200C90C
_0222570E:
	ldr r0, [r5, #0x3c]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r5, #0x3c]
	mov r1, #1
	bl FUN_0200C6B0
	mov r1, #0x38
	mov r2, #0x3a
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r5, #0x3c]
	bl FUN_0200C714
	ldr r0, [r5, #0x3c]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r5, #0x3c]
	mov r1, #2
	bl FUN_0200C840
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #3
	blt _022256EC
	ldr r0, [r4]
	ldr r1, _02225754 ; =MOD08_022255D0
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02225754: .word MOD08_022255D0

	thumb_func_start MOD08_02225758
MOD08_02225758: ; 0x02225758
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	mov r7, #0
	add r6, r5, #0
	str r1, [sp, #0x10]
	add r6, #0x30
	add r4, r7, #0
_02225768:
	mov r0, #0
	str r0, [sp]
	mov r0, #0x32
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #0x30
	mov r1, #0
	str r0, [sp, #0xc]
	ldr r2, _022257A8 ; =0x00007FFF
	add r0, r6, #0
	add r3, r1, #0
	bl MOD08_02217D14
	ldr r0, [r5, #0x38]
	add r7, r7, #1
	add r0, r0, r4
	str r0, [r5, #0x38]
	ldr r1, [r5, #0x48]
	ldr r0, [sp, #0x10]
	add r6, #0x24
	mul r0, r1
	str r0, [r5, #0x48]
	ldr r0, _022257AC ; =0x00002AAA
	add r5, #0x24
	add r4, r4, r0
	cmp r7, #6
	blt _02225768
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_022257A8: .word 0x00007FFF
_022257AC: .word 0x00002AAA

	thumb_func_start MOD08_022257B0
MOD08_022257B0: ; 0x022257B0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	mov r0, #0
	str r0, [sp, #4]
	add r0, r6, #0
	str r0, [sp]
	add r0, #0x30
	str r0, [sp]
	add r5, r6, #0
	add r4, r6, #0
_022257C6:
	ldr r0, [sp]
	bl MOD08_02217D98
	ldr r1, [r5, #0x38]
	mov r2, #0xa
	lsl r0, r1, #2
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #4
	lsl r1, r0, #2
	ldr r0, _0222586C ; =FX_SinCosTable_
	ldr r3, [r6, #0x14]
	ldrsh r0, [r0, r1]
	lsl r2, r2, #0xc
	mul r2, r3
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	add r3, r1, #0
	mov r1, #0x13
	lsl r1, r1, #4
	mov r2, #0x30
	add r7, r0, #0
	ldrsh r1, [r6, r1]
	ldrsh r2, [r5, r2]
	ldr r0, [r4, #0x18]
	add r1, r1, r2
	ldr r2, _02225870 ; =0x00000132
	lsl r1, r1, #0x10
	ldrsh r2, [r6, r2]
	asr r1, r1, #0x10
	mov ip, r2
	mov r2, #2
	lsl r2, r2, #0xa
	add r7, r7, r2
	ldr r2, _02225874 ; =0x00000000
	adc r3, r2
	lsl r2, r3, #0x14
	lsr r3, r7, #0xc
	orr r3, r2
	lsl r2, r3, #4
	asr r2, r2, #0x10
	mov r3, ip
	add r2, r3, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	ldr r1, [r5, #0x38]
	ldr r0, _02225878 ; =0x00003FFF
	cmp r1, r0
	blt _02225842
	ldr r0, _0222587C ; =0x0000BF49
	cmp r1, r0
	bgt _02225842
	ldr r0, [r4, #0x18]
	mov r1, #1
	bl FUN_0200C6B0
	b _02225852
_02225842:
	ldr r0, [r6]
	bl MOD08_02215574
	add r1, r0, #0
	ldr r0, [r4, #0x18]
	add r1, r1, #1
	bl FUN_0200C6B0
_02225852:
	ldr r0, [sp]
	add r5, #0x24
	add r0, #0x24
	str r0, [sp]
	ldr r0, [sp, #4]
	add r4, r4, #4
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #6
	blt _022257C6
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222586C: .word FX_SinCosTable_
_02225870: .word 0x00000132
_02225874: .word 0x00000000
_02225878: .word 0x00003FFF
_0222587C: .word 0x0000BF49

	thumb_func_start MOD08_02225880
MOD08_02225880: ; 0x02225880
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	add r7, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #4
	bhi _02225966
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222589A: ; jump table
	.short _022258A4 - _0222589A - 2 ; case 0
	.short _022258DA - _0222589A - 2 ; case 1
	.short _022258FA - _0222589A - 2 ; case 2
	.short _02225926 - _0222589A - 2 ; case 3
	.short _02225942 - _0222589A - 2 ; case 4
_022258A4:
	ldr r0, [r4]
	mov r1, #1
	mov r2, #0xf
	bl MOD08_02227994
	mov r0, #0
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	add r0, #0xfe
	add r0, r4, r0
	mov r1, #1
	mov r2, #0x10
	mov r3, #0xf
	bl MOD08_022186D4
	ldr r1, [r4, #0x14]
	add r0, r4, #0
	bl MOD08_02225758
	add r0, r4, #0
	bl MOD08_022257B0
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02225966
_022258DA:
	add r0, r4, #0
	bl MOD08_022257B0
	mov r0, #0x42
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD08_02218704
	cmp r0, #0
	beq _02225966
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	mov r0, #0x1c
	str r0, [r4, #0x10]
	b _02225966
_022258FA:
	add r0, r4, #0
	bl MOD08_022257B0
	ldr r0, [r4, #0x10]
	sub r0, r0, #1
	str r0, [r4, #0x10]
	bpl _02225966
	ldr r0, [r4, #0xc]
	mov r1, #0x10
	add r0, r0, #1
	str r0, [r4, #0xc]
	mov r0, #0xf
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	add r0, #0xfe
	add r0, r4, r0
	mov r2, #1
	mov r3, #0
	bl MOD08_022186D4
	b _02225966
_02225926:
	add r0, r4, #0
	bl MOD08_022257B0
	mov r0, #0x42
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD08_02218704
	cmp r0, #0
	beq _02225966
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02225966
_02225942:
	mov r6, #0
	add r5, r4, #0
_02225946:
	ldr r0, [r5, #0x18]
	bl FUN_0200C3DC
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #6
	blt _02225946
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r4]
	add r1, r7, #0
	bl MOD08_02212438
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02225966:
	ldr r0, [r4, #8]
	bl FUN_0200BC1C
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02225970
MOD08_02225970: ; 0x02225970
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r5, r1, #0
	mov r1, #0x4d
	lsl r1, r1, #2
	add r4, r0, #0
	str r2, [sp]
	add r7, r3, #0
	bl MOD08_02228064
	add r6, r0, #0
	str r4, [r6]
	ldr r0, [sp]
	str r5, [r6, #4]
	str r0, [r6, #8]
	add r0, r4, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r6]
	bl MOD08_022154D4
	mov r1, #0
	add r5, r0, #0
	bl FUN_0200782C
	mov r1, #0x13
	lsl r1, r1, #4
	strh r0, [r6, r1]
	add r0, r5, #0
	mov r1, #1
	bl FUN_0200782C
	ldr r1, _02225A14 ; =0x00000132
	strh r0, [r6, r1]
	add r0, sp, #4
	add r1, r4, #0
	bl MOD08_02215474
	mov r4, #0
	add r5, r6, #0
_022259C2:
	cmp r4, #0
	bne _022259CA
	str r7, [r5, #0x18]
	b _022259D6
_022259CA:
	ldr r0, [r6, #4]
	ldr r1, [r6, #8]
	add r2, sp, #4
	bl FUN_0200C154
	str r0, [r5, #0x18]
_022259D6:
	ldr r0, [r5, #0x18]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r5, #0x18]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r5, #0x18]
	mov r1, #1
	bl FUN_0200C5E0
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _022259C2
	ldr r0, [r6]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r6]
	bl MOD08_02217C1C
	str r0, [r6, #0x14]
	ldr r0, [r6]
	ldr r1, _02225A18 ; =MOD08_02225880
	add r2, r6, #0
	bl MOD08_02212400
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02225A14: .word 0x00000132
_02225A18: .word MOD08_02225880

	thumb_func_start MOD08_02225A1C
MOD08_02225A1C: ; 0x02225A1C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r1, #0
	add r1, sp, #8
	add r5, r2, #0
	add r1, #2
	add r2, sp, #8
	add r6, r0, #0
	add r4, r3, #0
	bl FUN_0200C7A0
	add r0, sp, #8
	mov r1, #0
	ldrsh r3, [r0, r1]
	mov r1, #2
	ldrsh r2, [r0, r1]
	lsl r0, r4, #7
	neg r0, r0
	add r0, r3, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	lsl r1, r2, #0x10
	lsl r4, r5, #8
	add r2, r2, r4
	str r0, [sp]
	mov r0, #0x3b
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	str r0, [sp, #4]
	add r0, r7, #0
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	asr r3, r3, #0x10
	bl MOD08_02217E80
	add r0, r6, #0
	mov r1, #1
	bl FUN_0200C644
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02225A70
MOD08_02225A70: ; 0x02225A70
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r0, r1, #0
	add r1, r4, #0
	bl MOD08_02217F08
	cmp r0, #0
	beq _02225B2A
	add r1, sp, #8
	add r0, r4, #0
	add r1, #2
	add r2, sp, #8
	bl FUN_0200C7A0
	add r1, sp, #8
	mov r0, #2
	ldrsh r0, [r1, r0]
	mov r1, #0x5b
	lsl r1, r1, #2
	str r0, [sp]
	ldr r0, [sp]
	mov r2, #0xe
	mul r1, r0
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #4
	lsl r1, r0, #2
	ldr r0, _02225B30 ; =FX_SinCosTable_
	lsl r2, r2, #0xc
	ldrsh r0, [r0, r1]
	mov r3, #0
	asr r7, r0, #0x1f
	add r1, r7, #0
	str r0, [sp, #4]
	bl _ll_mul
	add r3, r0, #0
	add r5, r1, #0
	add r6, sp, #8
	mov r2, #0
	ldrsh r2, [r6, r2]
	mov r6, #2
	lsl r6, r6, #0xa
	add r0, r4, #0
	add r6, r3, r6
	ldr r3, _02225B34 ; =0x00000000
	ldr r1, [sp]
	adc r5, r3
	lsl r3, r5, #0x14
	lsr r5, r6, #0xc
	orr r5, r3
	lsl r3, r5, #4
	asr r3, r3, #0x10
	add r2, r2, r3
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	mov r2, #0xae
	ldr r0, [sp, #4]
	add r1, r7, #0
	lsl r2, r2, #2
	mov r3, #0
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	neg r0, r1
	bl _fflt
	ldr r1, _02225B38 ; =0x45800000
	bl _fdiv
	add r1, r0, #0
	mov r0, #0xfe
	lsl r0, r0, #0x16
	bl _fadd
	add r1, r0, #0
	add r0, r4, #0
	add r2, r1, #0
	bl FUN_0200C884
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_02225B2A:
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02225B30: .word FX_SinCosTable_
_02225B34: .word 0x00000000
_02225B38: .word 0x45800000

	thumb_func_start MOD08_02225B3C
MOD08_02225B3C: ; 0x02225B3C
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0x9d
	add r7, r0, #0
	lsl r1, r1, #2
	ldr r0, [r7, r1]
	cmp r0, #0xf
	bge _02225B84
	sub r0, r1, #4
	ldr r0, [r7, r0]
	add r2, r0, #1
	sub r0, r1, #4
	str r2, [r7, r0]
	ldr r0, [r7, r0]
	cmp r0, #6
	ble _02225B84
	mov r2, #0
	sub r0, r1, #4
	str r2, [r7, r0]
	ldr r1, [r7, r1]
	add r3, r7, #0
	lsl r0, r1, #2
	mov r2, #0x24
	add r0, r7, r0
	add r3, #0x54
	mul r2, r1
	add r1, r3, r2
	ldr r0, [r0, #0x18]
	ldr r2, [r7, #0x10]
	ldr r3, [r7, #0x14]
	bl MOD08_02225A1C
	mov r0, #0x9d
	lsl r0, r0, #2
	ldr r1, [r7, r0]
	add r1, r1, #1
	str r1, [r7, r0]
_02225B84:
	mov r0, #0x9d
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	mov r4, #0
	cmp r0, #0
	ble _02225BB0
	add r6, r7, #0
	add r6, #0x54
	add r5, r7, #0
_02225B96:
	ldr r0, [r5, #0x18]
	add r1, r6, #0
	bl MOD08_02225A70
	str r0, [sp]
	mov r0, #0x9d
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	add r4, r4, #1
	add r6, #0x24
	add r5, r5, #4
	cmp r4, r0
	blt _02225B96
_02225BB0:
	cmp r0, #0xf
	blt _02225BBE
	ldr r0, [sp]
	cmp r0, #1
	bne _02225BBE
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02225BBE:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02225BC4
MOD08_02225BC4: ; 0x02225BC4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r7, r0, #0
	add r0, r6, #0
	bl MOD08_02225B3C
	cmp r0, #0
	beq _02225BF6
	mov r4, #0
	add r5, r6, #0
_02225BD8:
	ldr r0, [r5, #0x18]
	bl FUN_0200C3DC
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xf
	blt _02225BD8
	add r0, r6, #0
	bl FreeToHeap
	ldr r0, [r6]
	add r1, r7, #0
	bl MOD08_02212438
	pop {r3, r4, r5, r6, r7, pc}
_02225BF6:
	ldr r0, [r6, #8]
	bl FUN_0200BC1C
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02225C00
MOD08_02225C00: ; 0x02225C00
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r5, r1, #0
	mov r1, #0x9e
	lsl r1, r1, #2
	add r4, r0, #0
	str r2, [sp]
	add r7, r3, #0
	bl MOD08_02228064
	add r6, r0, #0
	str r4, [r6]
	ldr r0, [sp]
	str r5, [r6, #4]
	str r0, [r6, #8]
	add r0, r4, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r6]
	bl MOD08_022154D4
	mov r1, #0
	add r5, r0, #0
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #8]
	add r0, r5, #0
	mov r1, #1
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #4]
	add r0, sp, #0xc
	add r1, r4, #0
	bl MOD08_02215474
	mov r4, #0
	add r5, r6, #0
_02225C54:
	cmp r4, #0
	bne _02225C5C
	str r7, [r5, #0x18]
	b _02225C68
_02225C5C:
	ldr r0, [r6, #4]
	ldr r1, [r6, #8]
	add r2, sp, #0xc
	bl FUN_0200C154
	str r0, [r5, #0x18]
_02225C68:
	ldr r0, [r5, #0x18]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r5, #0x18]
	mov r1, #1
	bl FUN_0200C6B0
	ldr r0, [r5, #0x18]
	mov r1, #2
	bl FUN_0200C840
	ldr r0, [r5, #0x18]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r5, #0x18]
	ldr r1, [sp, #8]
	ldr r2, [sp, #4]
	bl FUN_0200C714
	add r0, r4, #0
	mov r1, #3
	bl _s32_div_f
	ldr r0, [r5, #0x18]
	bl FUN_0200C5C0
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xf
	blt _02225C54
	ldr r0, [r6]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r6]
	bl MOD08_02217C1C
	str r0, [r6, #0x10]
	ldr r0, [r6]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r6]
	bl MOD08_02217C44
	str r0, [r6, #0x14]
	ldr r0, [r6]
	ldr r1, _02225CD8 ; =MOD08_02225BC4
	add r2, r6, #0
	bl MOD08_02212400
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02225CD8: .word MOD08_02225BC4

	thumb_func_start MOD08_02225CDC
MOD08_02225CDC: ; 0x02225CDC
	ldr r1, [r0, #0x2c]
	cmp r1, #0
	beq _02225CEC
	cmp r1, #1
	beq _02225D00
	cmp r1, #2
	beq _02225D14
	bx lr
_02225CEC:
	ldr r1, _02225D28 ; =0x00007FFF
	str r1, [r0, #0x18]
	mov r1, #5
	str r1, [r0, #0x24]
	mov r1, #1
	lsl r1, r1, #0x10
	str r1, [r0, #0x1c]
	mov r1, #0x10
	str r1, [r0, #0x28]
	bx lr
_02225D00:
	ldr r1, _02225D28 ; =0x00007FFF
	str r1, [r0, #0x18]
	mov r1, #4
	mvn r1, r1
	str r1, [r0, #0x24]
	ldr r1, _02225D2C ; =0xFFFF0000
	str r1, [r0, #0x1c]
	mov r1, #0x10
	str r1, [r0, #0x28]
	bx lr
_02225D14:
	ldr r1, _02225D28 ; =0x00007FFF
	str r1, [r0, #0x18]
	mov r1, #0xa
	str r1, [r0, #0x24]
	lsl r1, r1, #0xd
	str r1, [r0, #0x1c]
	mov r1, #0x10
	str r1, [r0, #0x28]
	bx lr
	nop
_02225D28: .word 0x00007FFF
_02225D2C: .word 0xFFFF0000

	thumb_func_start MOD08_02225D30
MOD08_02225D30: ; 0x02225D30
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, [r5, #4]
	bl MOD08_02218894
	str r0, [sp, #8]
	ldr r0, [r5, #0x10]
	str r0, [sp]
	str r0, [sp, #4]
	sub r0, #8
	str r0, [sp, #4]
	ldr r0, [sp]
	add r0, #0x58
	str r0, [sp]
	ldr r0, [sp, #4]
	cmp r0, #0
	bge _02225D58
	mov r0, #0
	str r0, [sp, #4]
_02225D58:
	ldr r0, [sp]
	cmp r0, #0xc0
	ble _02225D62
	mov r0, #0xc0
	str r0, [sp]
_02225D62:
	mov r0, #0
	ldr r1, [r5, #0x20]
	mvn r0, r0
	mul r0, r1
	ldr r4, [sp, #4]
	str r0, [r5, #0x20]
	ldr r0, [sp]
	add r1, r4, #0
	cmp r1, r0
	bge _02225E02
_02225D76:
	mov r0, #2
	tst r0, r4
	ldr r1, [r5, #0x1c]
	beq _02225D86
	ldr r0, [r5, #0x20]
	lsl r0, r0, #0xc
	add r2, r1, r0
	b _02225D8C
_02225D86:
	ldr r0, [r5, #0x20]
	lsl r0, r0, #0xc
	sub r2, r1, r0
_02225D8C:
	ldr r1, [sp, #4]
	ldr r0, [r5, #0x18]
	sub r3, r4, r1
	ldr r1, _02225E08 ; =0x00000199
	mul r1, r3
	add r0, r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #4
	lsl r1, r0, #2
	ldr r0, _02225E0C ; =FX_SinCosTable_
	asr r3, r2, #0x1f
	ldrsh r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #2
	lsl r2, r2, #0xa
	add r2, r0, r2
	ldr r0, _02225E10 ; =0x00000000
	adc r1, r0
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	lsl r0, r1, #4
	asr r7, r0, #0x10
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x24]
	sub r0, r4, r0
	mul r0, r1
	mov r1, #0xa
	bl _s32_div_f
	add r0, r7, r0
	lsl r0, r0, #0x10
	ldr r1, [r5, #0x30]
	asr r7, r0, #0x10
	lsl r0, r1, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x10
	asr r0, r0, #0x10
	asr r1, r1, #0x10
	sub r6, r4, #1
	bpl _02225DE6
	add r6, #0xc0
_02225DE6:
	add r0, r0, r7
	lsl r0, r0, #0x10
	lsl r1, r1, #0x10
	lsr r0, r0, #0x10
	lsr r1, r1, #0x10
	bl MOD08_02218998
	ldr r1, [sp, #8]
	lsl r2, r6, #2
	str r0, [r1, r2]
	ldr r0, [sp]
	add r4, r4, #1
	cmp r4, r0
	blt _02225D76
_02225E02:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02225E08: .word 0x00000199
_02225E0C: .word FX_SinCosTable_
_02225E10: .word 0x00000000

	thumb_func_start MOD08_02225E14
MOD08_02225E14: ; 0x02225E14
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _02225E2A
	cmp r0, #1
	beq _02225E3E
	cmp r0, #2
	beq _02225E68
	pop {r4, r5, r6, pc}
_02225E2A:
	add r0, r4, #0
	bl MOD08_02225CDC
	add r0, r4, #0
	bl MOD08_02225D30
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	pop {r4, r5, r6, pc}
_02225E3E:
	ldr r0, [r4, #0x28]
	sub r0, r0, #1
	str r0, [r4, #0x28]
	add r0, r4, #0
	bl MOD08_02225D30
	ldr r0, [r4, #0x28]
	cmp r0, #0
	bge _02225EFA
	ldr r0, [r4, #0x2c]
	add r0, r0, #1
	str r0, [r4, #0x2c]
	cmp r0, #3
	bge _02225E60
	mov r0, #0
	str r0, [r4, #8]
	pop {r4, r5, r6, pc}
_02225E60:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	pop {r4, r5, r6, pc}
_02225E68:
	ldr r0, [r4, #0xc]
	mov r1, #6
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4, #4]
	bl MOD08_022188A8
	ldr r0, [r4, #4]
	bl MOD08_02218870
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_02215588
	add r5, r0, #0
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_02215600
	add r1, r0, #0
	lsl r0, r5, #0x18
	lsl r1, r1, #0x18
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	bl FUN_020178BC
	ldr r0, [r4]
	bl MOD08_02215574
	add r1, r0, #0
	lsl r1, r1, #0x18
	mov r0, #0
	lsr r1, r1, #0x18
	bl FUN_020178BC
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_02215588
	add r5, r0, #0
	ldr r0, [r4]
	bl MOD08_02212014
	add r3, r0, #0
	lsl r0, r5, #0x18
	mov r1, #1
	lsr r0, r0, #0x18
	lsl r1, r1, #0xe
	mov r2, #0
	bl FUN_02017F18
	ldr r0, [r4]
	bl MOD08_02212490
	add r5, r0, #0
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_02215588
	add r1, r0, #0
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	bl FUN_02018744
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r4]
	add r1, r6, #0
	bl MOD08_02212438
_02225EFA:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_02225EFC
MOD08_02225EFC: ; 0x02225EFC
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0x34
	add r7, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r7, [r4]
	add r0, r7, #0
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	mov r1, #0
	str r0, [r4, #0xc]
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r5, r0, #0x10
	ldr r0, [r4, #0xc]
	mov r1, #0x29
	bl FUN_0200782C
	sub r0, r5, r0
	lsl r0, r0, #0x10
	asr r5, r0, #0x10
	ldr r0, [r4, #0xc]
	mov r1, #6
	mov r2, #1
	bl FUN_02007558
	sub r6, #0x28
	lsl r0, r6, #0x10
	str r5, [r4, #0x14]
	sub r5, #0x28
	asr r0, r0, #0x10
	neg r0, r0
	neg r1, r5
	lsl r0, r0, #0x10
	lsl r1, r1, #0x10
	str r5, [r4, #0x10]
	lsr r0, r0, #0x10
	lsr r1, r1, #0x10
	bl MOD08_02218998
	str r0, [r4, #0x30]
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_022155C4
	bl MOD08_022189A0
	add r5, r0, #0
	ldr r0, [r4]
	bl MOD08_02212014
	add r2, r0, #0
	ldr r1, [r4, #0x30]
	add r0, r5, #0
	bl MOD08_022187F4
	str r0, [r4, #4]
	mov r0, #1
	str r0, [r4, #0x20]
	add r0, r7, #0
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_02227468
	sub r0, r0, #3
	cmp r0, #1
	bhi _02225FD0
	ldr r0, [r4]
	mov r1, #1
	bl MOD08_02215588
	add r5, r0, #0
	ldr r0, [r4]
	bl MOD08_02215574
	add r1, r0, #0
	lsl r0, r5, #0x18
	lsl r1, r1, #0x18
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	bl FUN_020178BC
	ldr r0, [r4]
	bl MOD08_02215574
	add r1, r0, #0
	add r1, r1, #1
	lsl r1, r1, #0x18
	mov r0, #0
	lsr r1, r1, #0x18
	bl FUN_020178BC
_02225FD0:
	ldr r0, [r4]
	ldr r1, _02225FDC ; =MOD08_02225E14
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02225FDC: .word MOD08_02225E14

	thumb_func_start MOD08_02225FE0
MOD08_02225FE0: ; 0x02225FE0
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #5
	bls _02225FF0
	b _02226134
_02225FF0:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02225FFC: ; jump table
	.short _02226008 - _02225FFC - 2 ; case 0
	.short _0222604E - _02225FFC - 2 ; case 1
	.short _02226088 - _02225FFC - 2 ; case 2
	.short _022260C2 - _02225FFC - 2 ; case 3
	.short _0222610E - _02225FFC - 2 ; case 4
	.short _02226126 - _02225FFC - 2 ; case 5
_02226008:
	mov r2, #0
	str r2, [sp]
	mov r0, #8
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0xc
	mov r1, #0x7f
	add r3, r2, #0
	bl MOD08_02217E80
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _02226138 ; =0xFFFF1FFF
	and r1, r0
	lsr r0, r2, #0xd
	orr r0, r1
	str r0, [r2]
	mov r1, #0
	ldr r0, [r4]
	add r2, r1, #0
	bl MOD08_02227A4C
	ldr r1, _0222613C ; =0x04000040
	mov r0, #0xff
	strh r0, [r1]
	mov r0, #0xbf
	strh r0, [r1, #4]
	mov r0, #7
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, pc}
_0222604E:
	ldr r0, [r4, #8]
	sub r0, r0, #1
	str r0, [r4, #8]
	bpl _02226134
	ldr r0, [r4]
	bl MOD08_02215504
	add r5, r0, #0
	ldr r0, [r4]
	bl MOD08_02214540
	add r2, r0, #0
	mov r3, #0
	lsl r2, r2, #0x10
	str r3, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	ldr r0, _02226140 ; =0x0000FFFF
	mov r1, #1
	str r0, [sp, #8]
	add r0, r5, #0
	lsr r2, r2, #0x10
	bl FUN_02003210
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, pc}
_02226088:
	add r0, r4, #0
	add r0, #0xc
	bl MOD08_02217ECC
	cmp r0, #0
	beq _022260B8
	mov r0, #0xc
	ldrsh r2, [r4, r0]
	mov r0, #0x7f
	add sp, #0xc
	sub r0, r0, r2
	lsl r1, r0, #8
	mov r0, #0xff
	lsl r0, r0, #8
	add r2, #0x80
	and r1, r0
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	ldr r1, _0222613C ; =0x04000040
	strh r0, [r1]
	mov r0, #0xbf
	strh r0, [r1, #4]
	pop {r4, r5, pc}
_022260B8:
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, pc}
_022260C2:
	ldr r0, [r4]
	bl MOD08_02215504
	bl FUN_020038E4
	cmp r0, #0
	bne _02226134
	ldr r0, [r4, #4]
	mov r2, #1
	add r0, r0, #1
	str r0, [r4, #4]
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _02226138 ; =0xFFFF1FFF
	and r0, r1
	str r0, [r2]
	ldr r0, [r4]
	bl MOD08_02215504
	add r5, r0, #0
	ldr r0, [r4]
	bl MOD08_02214540
	add r2, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r3, #0
	lsl r2, r2, #0x10
	ldr r0, _02226140 ; =0x0000FFFF
	str r3, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, #0
	mov r1, #1
	lsr r2, r2, #0x10
	bl FUN_02003210
	add sp, #0xc
	pop {r4, r5, pc}
_0222610E:
	ldr r0, [r4]
	bl MOD08_02215504
	bl FUN_020038E4
	cmp r0, #0
	bne _02226134
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, pc}
_02226126:
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
_02226134:
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02226138: .word 0xFFFF1FFF
_0222613C: .word 0x04000040
_02226140: .word 0x0000FFFF

	thumb_func_start MOD08_02226144
MOD08_02226144: ; 0x02226144
	push {r4, lr}
	mov r1, #0x34
	add r4, r0, #0
	bl MOD08_02228064
	add r2, r0, #0
	ldr r1, _0222615C ; =MOD08_02225FE0
	add r0, r4, #0
	str r4, [r2]
	bl MOD08_02212400
	pop {r4, pc}
	.align 2, 0
_0222615C: .word MOD08_02225FE0

	thumb_func_start MOD08_02226160
MOD08_02226160: ; 0x02226160
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #4
	bhi _02226210
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222617A: ; jump table
	.short _02226184 - _0222617A - 2 ; case 0
	.short _022261AA - _0222617A - 2 ; case 1
	.short _022261BE - _0222617A - 2 ; case 2
	.short _022261E4 - _0222617A - 2 ; case 3
	.short _022261F8 - _0222617A - 2 ; case 4
_02226184:
	ldr r0, [r4]
	mov r1, #0
	mov r2, #0x10
	bl MOD08_02227994
	mov r1, #0
	mov r2, #0x10
	str r1, [sp]
	mov r0, #8
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x14
	add r3, r2, #0
	bl MOD08_022186D4
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02226210
_022261AA:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02218704
	cmp r0, #0
	beq _02226210
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02226210
_022261BE:
	ldr r0, [r4, #0x10]
	bl FUN_0200C608
	cmp r0, #0
	bne _02226210
	ldr r0, [r4, #0xc]
	mov r2, #0
	add r0, r0, #1
	str r0, [r4, #0xc]
	mov r1, #0x10
	str r1, [sp]
	mov r0, #8
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x14
	add r3, r2, #0
	bl MOD08_022186D4
	b _02226210
_022261E4:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02218704
	cmp r0, #0
	beq _02226210
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02226210
_022261F8:
	ldr r0, [r4, #0x10]
	bl FUN_0200C3DC
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, pc}
_02226210:
	ldr r0, [r4, #8]
	bl FUN_0200BC1C
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_0222621C
MOD08_0222621C: ; 0x0222621C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	mov r1, #0x3c
	add r6, r0, #0
	str r2, [sp]
	add r5, r3, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r6, [r4]
	ldr r0, [sp]
	str r7, [r4, #4]
	str r0, [r4, #8]
	str r5, [r4, #0x10]
	add r0, r5, #0
	mov r1, #1
	bl FUN_0200C5E0
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r4]
	ldr r1, _02226254 ; =MOD08_02226160
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02226254: .word MOD08_02226160

	thumb_func_start MOD08_02226258
MOD08_02226258: ; 0x02226258
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #4
	bhi _0222631C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02226272: ; jump table
	.short _0222627C - _02226272 - 2 ; case 0
	.short _022262E6 - _02226272 - 2 ; case 1
	.short _02226328 - _02226272 - 2 ; case 2
	.short _02226394 - _02226272 - 2 ; case 3
	.short _022263E6 - _02226272 - 2 ; case 4
_0222627C:
	ldr r0, [r4, #0x68]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	ldr r0, [r4, #0x6c]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #4]
	ldr r0, [r4, #0x74]
	asr r0, r0, #0x10
	str r0, [sp, #8]
	ldr r1, [r4, #0x5c]
	ldr r2, [r4, #0x60]
	ldr r3, [r4, #0x64]
	add r0, r4, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	add r0, #0x14
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	asr r3, r3, #0x10
	bl MOD08_022181A8
	mov r1, #0xa
	mov r2, #8
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r3, [r4, #0x10]
	add r0, #0x38
	bl MOD08_02218454
	add r0, r4, #0
	ldr r1, [r4, #0x10]
	add r0, #0x14
	bl MOD08_022183A0
	mov r0, #0
	str r0, [sp]
	mov r1, #8
	mov r2, #0xc
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	ldr r3, [r4, #0x28]
	bl MOD08_022182DC
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, pc}
_022262E6:
	mov r1, #0xa
	mov r2, #8
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r3, [r4, #0x10]
	add r0, #0x38
	bl MOD08_02218454
	add r0, r4, #0
	ldr r1, [r4, #0x10]
	add r0, #0x14
	bl MOD08_022183A0
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r1, #8
	mov r2, #0xc
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	ldr r3, [r4, #0x28]
	bl MOD08_022182DC
	cmp r5, #0
	beq _0222631E
_0222631C:
	b _02226424
_0222631E:
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, pc}
_02226328:
	ldr r0, [r4, #0x64]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	ldr r0, [r4, #0x6c]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #4]
	ldr r0, [r4, #0x74]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	ldr r1, [r4, #0x60]
	ldr r2, [r4, #0x5c]
	ldr r3, [r4, #0x68]
	add r0, r4, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	add r0, #0x14
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	asr r3, r3, #0x10
	bl MOD08_022181A8
	mov r1, #0xa
	mov r2, #8
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r3, [r4, #0x10]
	add r0, #0x38
	bl MOD08_02218454
	add r0, r4, #0
	ldr r1, [r4, #0x10]
	add r0, #0x14
	bl MOD08_022183A0
	mov r0, #0
	str r0, [sp]
	mov r1, #8
	mov r2, #0xc
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	ldr r3, [r4, #0x28]
	bl MOD08_022182DC
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, pc}
_02226394:
	mov r1, #0xa
	mov r2, #8
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r3, [r4, #0x10]
	add r0, #0x38
	bl MOD08_02218454
	add r0, r4, #0
	ldr r1, [r4, #0x10]
	add r0, #0x14
	bl MOD08_022183A0
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r1, #8
	mov r2, #0xc
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	ldr r3, [r4, #0x28]
	bl MOD08_022182DC
	cmp r5, #0
	bne _02226424
	ldr r0, [r4, #0x70]
	sub r0, r0, #1
	str r0, [r4, #0x70]
	cmp r0, #0
	bgt _022263DE
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, pc}
_022263DE:
	mov r0, #0
	add sp, #0xc
	str r0, [r4, #4]
	pop {r4, r5, pc}
_022263E6:
	mov r2, #0xa
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl FUN_02007558
	mov r2, #8
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_02007558
	mov r1, #0xc
	add r2, r1, #0
	ldr r0, [r4, #0x10]
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r4, #0x10]
	add r2, #0xf3
	bl FUN_02007558
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
_02226424:
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start MOD08_02226428
MOD08_02226428: ; 0x02226428
	push {r3, r4, r5, lr}
	mov r1, #0x78
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4]
	add r0, r5, #0
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_0221552C
	strh r0, [r4, #0xc]
	ldr r0, [r4]
	bl MOD08_02212460
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD08_022154D4
	str r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #8]
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #0xa]
	mov r1, #0xa
	str r1, [r4, #0x5c]
	mov r0, #7
	str r0, [r4, #0x60]
	str r1, [r4, #0x64]
	mov r0, #0x1e
	str r0, [r4, #0x68]
	str r1, [r4, #0x6c]
	mov r3, #1
	ldr r0, _0222649C ; =0x00040003
	str r3, [r4, #0x70]
	str r0, [r4, #0x74]
	mov r1, #2
	add r0, r4, #0
	str r1, [sp]
	add r0, #0x38
	mov r2, #0
	bl MOD08_022183C0
	ldr r0, [r4]
	ldr r1, _022264A0 ; =MOD08_02226258
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, pc}
	nop
_0222649C: .word 0x00040003
_022264A0: .word MOD08_02226258

	thumb_func_start MOD08_022264A4
MOD08_022264A4: ; 0x022264A4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	ldr r1, [r4, #0x2c]
	add r0, #8
	bl MOD08_02217F08
	cmp r0, #0
	bne _022264CE
	ldr r0, [r4, #0x2c]
	bl FUN_0200C3DC
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
	pop {r3, r4, r5, pc}
_022264CE:
	ldr r0, [r4, #4]
	bl FUN_0200BC1C
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_022264D8
MOD08_022264D8: ; 0x022264D8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	mov r1, #0x30
	add r5, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r5, [r4]
	add r0, r5, #0
	bl MOD08_02212518
	str r0, [r4, #4]
	add r0, r5, #0
	bl MOD08_02212458
	add r6, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02227470
	cmp r0, #3
	bne _0222651C
	add r0, r5, #0
	mov r1, #0
	bl MOD08_022124B0
	str r0, [r4, #0x2c]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_022124B0
	bl FUN_0200C3DC
	b _02226532
_0222651C:
	add r0, r5, #0
	mov r1, #1
	bl MOD08_022124B0
	str r0, [r4, #0x2c]
	add r0, r5, #0
	mov r1, #0
	bl MOD08_022124B0
	bl FUN_0200C3DC
_02226532:
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02217C1C
	add r7, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02217C44
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0
	bl MOD08_02217B98
	str r0, [sp, #0x10]
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #1
	bl MOD08_02217B98
	ldr r1, [sp, #0x10]
	lsl r2, r7, #6
	add r6, r1, r2
	ldr r1, [sp, #0xc]
	lsl r1, r1, #4
	neg r1, r1
	add r5, r0, r1
	str r1, [sp, #8]
	lsl r1, r6, #0x10
	lsl r2, r5, #0x10
	ldr r0, [r4, #0x2c]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	ldr r0, [sp, #8]
	mov r2, #0x30
	add r0, r5, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	mul r2, r7
	str r0, [sp]
	mov r0, #6
	add r2, r6, r2
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r1, r6, #0x10
	lsl r2, r2, #0x10
	lsl r3, r5, #0x10
	add r0, #8
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	asr r3, r3, #0x10
	bl MOD08_02217E80
	ldr r0, [r4]
	ldr r1, _022265B0 ; =MOD08_022264A4
	add r2, r4, #0
	bl MOD08_02212400
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022265B0: .word MOD08_022264A4

	thumb_func_start MOD08_022265B4
MOD08_022265B4: ; 0x022265B4
	push {r4, r5, r6, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #5
	bls _022265C4
	b _022266E0
_022265C4:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022265D0: ; jump table
	.short _022265DC - _022265D0 - 2 ; case 0
	.short _022265F6 - _022265D0 - 2 ; case 1
	.short _02226644 - _022265D0 - 2 ; case 2
	.short _02226660 - _022265D0 - 2 ; case 3
	.short _022266A2 - _022265D0 - 2 ; case 4
	.short _022266BA - _022265D0 - 2 ; case 5
_022265DC:
	mov r1, #4
	add r0, r4, #0
	str r1, [sp]
	add r0, #0x40
	mov r2, #0
	mov r3, #1
	bl MOD08_022183C0
	ldr r0, [r4, #4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, r6, pc}
_022265F6:
	mov r1, #0x18
	mov r2, #0x1a
	add r0, r4, #0
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r3, [r4, #0x14]
	add r0, #0x40
	bl MOD08_02218454
	cmp r0, #0
	bne _022266E0
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0x1a
	ldrsh r3, [r4, r0]
	mov r0, #0x18
	ldrsh r1, [r4, r0]
	ldr r2, [r4, #0x10]
	sub r0, #0x1f
	mul r0, r2
	add r0, r3, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	add r0, r4, #0
	ldr r4, [r4, #0xc]
	mov r2, #0x28
	mul r2, r4
	add r2, r1, r2
	lsl r2, r2, #0x10
	add r0, #0x1c
	asr r2, r2, #0x10
	bl MOD08_02217E80
	add sp, #8
	pop {r4, r5, r6, pc}
_02226644:
	add r0, r4, #0
	ldr r1, [r4, #0x14]
	add r0, #0x1c
	bl MOD08_02217F2C
	cmp r0, #0
	bne _022266E0
	ldr r0, [r4, #4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #8
	str r0, [r4, #8]
	pop {r4, r5, r6, pc}
_02226660:
	ldr r0, [r4, #8]
	sub r0, r0, #1
	str r0, [r4, #8]
	bpl _022266E0
	ldr r0, [r4, #4]
	mov r5, #0x28
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0x1a
	ldrsh r3, [r4, r0]
	mov r0, #0x18
	ldrsh r2, [r4, r0]
	mov r0, #4
	str r3, [sp]
	str r0, [sp, #4]
	ldr r1, [r4, #0xc]
	add r0, r4, #0
	add r6, r1, #0
	mul r6, r5
	add r1, r2, r6
	lsl r1, r1, #0x10
	ldr r4, [r4, #0x10]
	sub r5, #0x2f
	mul r5, r4
	add r3, r3, r5
	lsl r3, r3, #0x10
	add r0, #0x1c
	asr r1, r1, #0x10
	asr r3, r3, #0x10
	bl MOD08_02217E80
	add sp, #8
	pop {r4, r5, r6, pc}
_022266A2:
	add r0, r4, #0
	ldr r1, [r4, #0x14]
	add r0, #0x1c
	bl MOD08_02217F2C
	cmp r0, #0
	bne _022266E0
	ldr r0, [r4, #4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, r6, pc}
_022266BA:
	mov r2, #0x18
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl FUN_02007558
	mov r2, #0x1a
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl FUN_02007558
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
_022266E0:
	add sp, #8
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_022266E4
MOD08_022266E4: ; 0x022266E4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r1, #0x64
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	str r5, [r4]
	bl MOD08_02212458
	add r6, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_022154D4
	str r0, [r4, #0x14]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #0x18]
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #0x1a]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02217C1C
	str r0, [r4, #0xc]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02217C44
	str r0, [r4, #0x10]
	ldr r0, [r4]
	ldr r1, _02226738 ; =MOD08_022265B4
	add r2, r4, #0
	bl MOD08_02212400
	pop {r4, r5, r6, pc}
	nop
_02226738: .word MOD08_022265B4

	thumb_func_start MOD08_0222673C
MOD08_0222673C: ; 0x0222673C
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #4
	bls _0222674C
	b _0222685C
_0222674C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02226758: ; jump table
	.short _02226762 - _02226758 - 2 ; case 0
	.short _02226798 - _02226758 - 2 ; case 1
	.short _022267C0 - _02226758 - 2 ; case 2
	.short _0222681E - _02226758 - 2 ; case 3
	.short _02226836 - _02226758 - 2 ; case 4
_02226762:
	mov r0, #0x16
	ldrsh r3, [r4, r0]
	mov r0, #0x14
	ldrsh r1, [r4, r0]
	ldr r0, [r4, #0xc]
	mov r5, #4
	lsl r0, r0, #4
	add r0, r3, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	str r5, [sp, #4]
	ldr r2, [r4, #8]
	sub r5, #0x2c
	mul r5, r2
	add r2, r1, r5
	add r0, r4, #0
	lsl r2, r2, #0x10
	add r0, #0x18
	asr r2, r2, #0x10
	bl MOD08_02217E80
	ldr r0, [r4, #4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_02226798:
	add r0, r4, #0
	ldr r1, [r4, #0x10]
	add r0, #0x18
	bl MOD08_02217F2C
	cmp r0, #0
	bne _0222685C
	ldr r0, [r4, #4]
	mov r1, #4
	add r0, r0, #1
	str r0, [r4, #4]
	add r4, #0x3c
	add r0, r4, #0
	mov r2, #0
	mov r3, #1
	str r1, [sp]
	bl MOD08_022183C0
	add sp, #8
	pop {r3, r4, r5, pc}
_022267C0:
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r5, r0, #0x10
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200782C
	lsl r0, r0, #0x10
	asr r2, r0, #0x10
	add r0, r4, #0
	ldr r3, [r4, #0x10]
	add r0, #0x3c
	add r1, r5, #0
	bl MOD08_02218454
	cmp r0, #0
	bne _0222685C
	ldr r0, [r4, #4]
	mov r5, #4
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0x16
	ldrsh r3, [r4, r0]
	mov r0, #0x14
	ldrsh r2, [r4, r0]
	add r0, r4, #0
	add r0, #0x18
	str r3, [sp]
	str r5, [sp, #4]
	ldr r1, [r4, #8]
	ldr r4, [r4, #0xc]
	sub r5, #0x2c
	mul r5, r1
	lsl r4, r4, #4
	add r1, r2, r5
	add r3, r3, r4
	lsl r1, r1, #0x10
	lsl r3, r3, #0x10
	asr r1, r1, #0x10
	asr r3, r3, #0x10
	bl MOD08_02217E80
	add sp, #8
	pop {r3, r4, r5, pc}
_0222681E:
	add r0, r4, #0
	ldr r1, [r4, #0x10]
	add r0, #0x18
	bl MOD08_02217F2C
	cmp r0, #0
	bne _0222685C
	ldr r0, [r4, #4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_02226836:
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl FUN_02007558
	mov r2, #0x16
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_02007558
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
_0222685C:
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02226860
MOD08_02226860: ; 0x02226860
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r1, #0x60
	bl MOD08_02228064
	add r4, r0, #0
	add r0, r5, #0
	str r5, [r4]
	bl MOD08_02212460
	add r6, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_022154D4
	str r0, [r4, #0x10]
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4, #0x14]
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #0x16]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02217C1C
	str r0, [r4, #8]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD08_02217C44
	str r0, [r4, #0xc]
	ldr r0, [r4]
	ldr r1, _022268B4 ; =MOD08_0222673C
	add r2, r4, #0
	bl MOD08_02212400
	pop {r4, r5, r6, pc}
	nop
_022268B4: .word MOD08_0222673C

	thumb_func_start MOD08_022268B8
MOD08_022268B8: ; 0x022268B8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	add r7, r1, #0
	add r4, r0, #0
	mov r1, #0xac
	add r6, r2, #0
	str r3, [sp]
	bl MOD08_02228064
	str r4, [r0]
	str r0, [sp, #4]
	str r6, [r0, #0xc]
	add r0, r4, #0
	bl MOD08_02212458
	add r5, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02217C1C
	ldr r1, [sp, #4]
	str r0, [r1, #0x10]
	ldr r1, [r1]
	add r0, sp, #8
	bl MOD08_02215474
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #0
	bl MOD08_02217B98
	add r1, sp, #8
	strh r0, [r1]
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #1
	bl MOD08_02217B98
	add r1, sp, #8
	ldr r5, [sp, #4]
	strh r0, [r1, #2]
	mov r4, #0
_0222690C:
	cmp r4, #0
	add r2, sp, #8
	bne _02226926
	ldr r0, [sp]
	mov r1, #0
	str r0, [r5, #0x14]
	ldrsh r1, [r2, r1]
	add r3, r2, #0
	mov r2, #2
	ldrsh r2, [r3, r2]
	bl FUN_0200C714
	b _02226930
_02226926:
	add r0, r7, #0
	add r1, r6, #0
	bl FUN_0200C154
	str r0, [r5, #0x14]
_02226930:
	ldr r0, [r5, #0x14]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r5, #0x14]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r5, #0x14]
	mov r1, #1
	bl FUN_0200C6B0
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #2
	blt _0222690C
	ldr r0, [sp, #4]
	ldr r1, _02226960 ; =MOD08_02226964
	ldr r0, [r0]
	ldr r2, [sp, #4]
	bl MOD08_02212400
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02226960: .word MOD08_02226964

	thumb_func_start MOD08_02226964
MOD08_02226964: ; 0x02226964
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r7, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #4
	bhi _02226A48
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222697C: ; jump table
	.short _02226986 - _0222697C - 2 ; case 0
	.short _022269AE - _0222697C - 2 ; case 1
	.short _022269CE - _0222697C - 2 ; case 2
	.short _02226A00 - _0222697C - 2 ; case 3
	.short _02226A26 - _0222697C - 2 ; case 4
_02226986:
	add r2, r4, #0
	ldr r0, [r4, #0x14]
	ldr r3, [r4, #0x10]
	add r1, #0x1c
	add r2, #0x64
	bl MOD08_02226A50
	add r1, r4, #0
	add r2, r4, #0
	ldr r0, [r4, #0x14]
	add r1, #0x1c
	add r2, #0x64
	bl MOD08_02226AB0
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #8
	str r0, [r4, #8]
	b _02226A48
_022269AE:
	ldr r0, [r4, #8]
	add r2, r4, #0
	sub r0, r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #0x14]
	add r1, #0x1c
	add r2, #0x64
	bl MOD08_02226AB0
	ldr r0, [r4, #8]
	cmp r0, #0
	bge _02226A48
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	b _02226A48
_022269CE:
	add r2, r4, #0
	ldr r0, [r4, #0x18]
	ldr r3, [r4, #0x10]
	add r1, #0x40
	add r2, #0x88
	bl MOD08_02226A50
	add r1, r4, #0
	add r2, r4, #0
	ldr r0, [r4, #0x18]
	add r1, #0x40
	add r2, #0x88
	bl MOD08_02226AB0
	add r1, r4, #0
	add r2, r4, #0
	ldr r0, [r4, #0x14]
	add r1, #0x1c
	add r2, #0x64
	bl MOD08_02226AB0
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	b _02226A48
_02226A00:
	add r2, r4, #0
	ldr r0, [r4, #0x14]
	add r1, #0x1c
	add r2, #0x64
	bl MOD08_02226AB0
	add r1, r4, #0
	add r2, r4, #0
	ldr r0, [r4, #0x18]
	add r1, #0x40
	add r2, #0x88
	bl MOD08_02226AB0
	cmp r0, #0
	beq _02226A48
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	b _02226A48
_02226A26:
	mov r6, #0
	add r5, r4, #0
_02226A2A:
	ldr r0, [r5, #0x14]
	bl FUN_0200C3DC
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _02226A2A
	ldr r0, [r4]
	add r1, r7, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
_02226A48:
	ldr r0, [r4, #0xc]
	bl FUN_0200BC1C
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02226A50
MOD08_02226A50: ; 0x02226A50
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r1, #0
	add r5, r0, #0
	mov r1, #2
	add r7, r2, #0
	add r4, r3, #0
	bl FUN_0200C840
	add r0, r5, #0
	mov r1, #1
	bl FUN_0200C644
	add r1, sp, #8
	add r0, r5, #0
	add r1, #2
	add r2, sp, #8
	bl FUN_0200C7A0
	add r1, sp, #8
	mov r0, #0
	ldrsh r3, [r1, r0]
	mov r0, #2
	ldrsh r1, [r1, r0]
	add r0, r3, #0
	sub r0, #0x20
	lsl r0, r0, #0x10
	lsl r2, r4, #4
	asr r0, r0, #0x10
	add r2, r1, r2
	str r0, [sp]
	mov r0, #0x20
	lsl r2, r2, #0x10
	str r0, [sp, #4]
	add r0, r6, #0
	asr r2, r2, #0x10
	bl MOD08_02217E80
	mov r0, #0x20
	mov r2, #0xa
	str r0, [sp]
	add r0, r7, #0
	mov r1, #2
	add r3, r2, #0
	bl MOD08_02218120
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02226AB0
MOD08_02226AB0: ; 0x02226AB0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, r1, #0
	add r4, r2, #0
	add r1, r5, #0
	bl MOD08_02217F08
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02218360
	cmp r0, #0
	beq _02226ACE
	mov r0, #0
	pop {r3, r4, r5, pc}
_02226ACE:
	add r0, r5, #0
	mov r1, #0
	bl FUN_0200C644
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02226ADC
MOD08_02226ADC: ; 0x02226ADC
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0x3c
	add r6, r0, #0
	add r7, r2, #0
	add r5, r3, #0
	bl MOD08_02228064
	add r4, r0, #0
	str r6, [r4]
	str r7, [r4, #0xc]
	str r5, [r4, #0x10]
	add r0, r5, #0
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r4, #0x10]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200C6B0
	ldr r0, [r4, #0x10]
	bl FUN_0200C68C
	str r0, [r4, #8]
	ldr r0, [r4]
	ldr r1, _02226B28 ; =MOD08_02226B2C
	add r2, r4, #0
	bl MOD08_02212400
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02226B28: .word MOD08_02226B2C

	thumb_func_start MOD08_02226B2C
MOD08_02226B2C: ; 0x02226B2C
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #4
	bhi _02226C18
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02226B46: ; jump table
	.short _02226B50 - _02226B46 - 2 ; case 0
	.short _02226B80 - _02226B46 - 2 ; case 1
	.short _02226BA6 - _02226B46 - 2 ; case 2
	.short _02226BE4 - _02226B46 - 2 ; case 3
	.short _02226C00 - _02226B46 - 2 ; case 4
_02226B50:
	mov r0, #4
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x14
	mov r1, #0
	mov r2, #0x10
	mov r3, #0x14
	bl MOD08_022186D4
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0200C644
	ldr r0, [r4]
	mov r1, #0
	mov r2, #0x14
	bl MOD08_02227994
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	b _02226C18
_02226B80:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02218704
	cmp r0, #0
	beq _02226C18
	ldr r0, [r4, #4]
	mov r1, #1
	add r0, r0, #1
	str r0, [r4, #4]
	ldr r0, [r4, #0x10]
	bl FUN_0200C5E0
	mov r1, #1
	ldr r0, [r4, #0x10]
	lsl r1, r1, #0xc
	bl FUN_0200C5F4
	b _02226C18
_02226BA6:
	ldr r0, [r4, #0x10]
	bl FUN_0200C630
	mov r1, #3
	bl _s32_div_f
	ldr r2, [r4, #8]
	ldr r0, [r4, #0x10]
	add r1, r2, r1
	bl FUN_0200C680
	ldr r0, [r4, #0x10]
	bl FUN_0200C608
	cmp r0, #0
	bne _02226C18
	ldr r0, [r4, #4]
	mov r1, #0x10
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0x14
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x14
	mov r2, #0
	mov r3, #4
	bl MOD08_022186D4
	b _02226C18
_02226BE4:
	add r0, r4, #0
	add r0, #0x14
	bl MOD08_02218704
	cmp r0, #0
	beq _02226C18
	ldr r0, [r4, #4]
	mov r1, #0
	add r0, r0, #1
	str r0, [r4, #4]
	ldr r0, [r4, #0x10]
	bl FUN_0200C644
	b _02226C18
_02226C00:
	ldr r0, [r4, #0x10]
	bl FUN_0200C3DC
	ldr r0, [r4]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, pc}
_02226C18:
	ldr r0, [r4, #0xc]
	bl FUN_0200BC1C
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02226C24
MOD08_02226C24: ; 0x02226C24
	push {r4, r5, r6, r7, lr}
	sub sp, #0x4c
	str r1, [sp, #4]
	str r2, [sp, #8]
	mov r1, #0x54
	add r5, r0, #0
	str r3, [sp, #0xc]
	bl MOD08_02228064
	ldr r1, [sp, #8]
	str r5, [r0]
	str r0, [sp, #0x14]
	str r1, [r0, #8]
	ldr r0, [r0]
	bl MOD08_02212458
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_02217C1C
	ldr r1, [sp, #0x14]
	str r0, [sp, #0x10]
	ldr r1, [r1]
	add r0, sp, #0x18
	bl MOD08_02215474
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0
	bl MOD08_02217B98
	add r1, sp, #0x18
	strh r0, [r1]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #1
	bl MOD08_02217B98
	ldr r7, [sp, #0x14]
	ldr r6, [sp, #0x14]
	ldr r5, [sp, #0x14]
	add r1, sp, #0x18
	add r7, #0x3c
	add r6, #0x24
	strh r0, [r1, #2]
	mov r4, #5
	add r5, #0x14
	add r7, #0x14
	add r6, #0x14
_02226C88:
	cmp r4, #5
	add r2, sp, #0x18
	bne _02226CA2
	ldr r0, [sp, #0xc]
	mov r1, #0
	str r0, [r5, #0xc]
	ldrsh r1, [r2, r1]
	add r3, r2, #0
	mov r2, #2
	ldrsh r2, [r3, r2]
	bl FUN_0200C714
	b _02226CAC
_02226CA2:
	ldr r0, [sp, #4]
	ldr r1, [sp, #8]
	bl FUN_0200C154
	str r0, [r5, #0xc]
_02226CAC:
	ldr r0, [r5, #0xc]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r5, #0xc]
	mov r1, #1
	bl FUN_0200C6B0
	ldr r0, [r5, #0xc]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [sp, #0x10]
	add r1, r6, #0
	str r0, [sp]
	ldr r0, [r5, #0xc]
	add r2, r7, #0
	add r3, r4, #0
	bl MOD08_02226CF4
	sub r5, r5, #4
	sub r7, r7, #4
	sub r6, r6, #4
	sub r4, r4, #1
	bpl _02226C88
	ldr r0, [sp, #0x14]
	ldr r1, _02226CF0 ; =MOD08_02226D78
	ldr r0, [r0]
	ldr r2, [sp, #0x14]
	bl MOD08_02212400
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
	nop
_02226CF0: .word MOD08_02226D78

	thumb_func_start MOD08_02226CF4
MOD08_02226CF4: ; 0x02226CF4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r3, #0
	add r6, r1, #0
	lsr r1, r4, #0x1f
	add r1, r4, r1
	asr r1, r1, #1
	add r5, r0, #0
	add r7, r2, #0
	bl FUN_0200C5C0
	lsl r0, r4, #1
	str r0, [r7]
	mov r0, #0x10
	add r1, sp, #0
	str r0, [r6]
	add r0, r5, #0
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	mov r1, #2
	add r6, r1, #0
	add r2, sp, #0
	sub r6, #0xe
	mul r6, r4
	ldr r0, [sp, #0x18]
	ldrsh r3, [r2, r1]
	add r6, #0x28
	add r4, r0, #0
	mul r4, r6
	add r0, r3, r4
	mov r3, #0
	strh r0, [r2, #2]
	ldrsh r0, [r2, r3]
	add r0, #0x28
	strh r0, [r2]
	ldrsh r1, [r2, r1]
	ldrsh r2, [r2, r3]
	add r0, r5, #0
	bl FUN_0200C714
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02226D48
MOD08_02226D48: ; 0x02226D48
	push {r3, lr}
	ldr r3, [r2]
	cmp r3, #0
	ble _02226D5E
	sub r1, r3, #1
	str r1, [r2]
	bne _02226D74
	mov r1, #1
	bl FUN_0200C644
	b _02226D74
_02226D5E:
	ldr r2, [r1]
	cmp r2, #0
	ble _02226D6A
	sub r0, r2, #1
	str r0, [r1]
	b _02226D74
_02226D6A:
	mov r1, #0
	bl FUN_0200C644
	mov r0, #1
	pop {r3, pc}
_02226D74:
	mov r0, #0
	pop {r3, pc}

	thumb_func_start MOD08_02226D78
MOD08_02226D78: ; 0x02226D78
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r1, #4]
	str r1, [sp]
	cmp r0, #0
	beq _02226D8A
	cmp r0, #1
	beq _02226DBC
	b _02226DE0
_02226D8A:
	add r6, r1, #0
	add r4, r1, #0
	mov r7, #0
	add r6, #0x3c
	add r4, #0x24
	add r5, r1, #0
_02226D96:
	ldr r0, [r5, #0xc]
	add r1, r4, #0
	add r2, r6, #0
	bl MOD08_02226D48
	add r7, r7, #1
	add r6, r6, #4
	add r4, r4, #4
	add r5, r5, #4
	cmp r7, #6
	blt _02226D96
	cmp r0, #0
	beq _02226DE0
	ldr r0, [sp]
	ldr r0, [r0, #4]
	add r1, r0, #1
	ldr r0, [sp]
	str r1, [r0, #4]
	b _02226DE0
_02226DBC:
	mov r5, #0
	add r4, r1, #0
_02226DC0:
	ldr r0, [r4, #0xc]
	bl FUN_0200C3DC
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #6
	blt _02226DC0
	ldr r0, [sp]
	add r1, r6, #0
	ldr r0, [r0]
	bl MOD08_02212438
	ldr r0, [sp]
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
_02226DE0:
	ldr r0, [sp]
	ldr r0, [r0, #8]
	bl FUN_0200BC1C
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02226DEC
MOD08_02226DEC: ; 0x02226DEC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	mov r7, #0
	add r6, r5, #0
	str r1, [sp, #0x10]
	add r6, #0x30
	add r4, r7, #0
_02226DFC:
	mov r0, #0
	str r0, [sp]
	mov r0, #0x32
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #0x30
	mov r1, #0
	str r0, [sp, #0xc]
	ldr r2, _02226E3C ; =0x00007FFF
	add r0, r6, #0
	add r3, r1, #0
	bl MOD08_02217D14
	ldr r0, [r5, #0x38]
	add r7, r7, #1
	add r0, r0, r4
	str r0, [r5, #0x38]
	ldr r1, [r5, #0x48]
	ldr r0, [sp, #0x10]
	add r6, #0x24
	mul r0, r1
	str r0, [r5, #0x48]
	ldr r0, _02226E40 ; =0x00002AAA
	add r5, #0x24
	add r4, r4, r0
	cmp r7, #6
	blt _02226DFC
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_02226E3C: .word 0x00007FFF
_02226E40: .word 0x00002AAA

	thumb_func_start MOD08_02226E44
MOD08_02226E44: ; 0x02226E44
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0
	add r7, r6, #0
	str r0, [sp]
	add r7, #0x30
	add r4, r6, #0
	add r5, r6, #0
_02226E54:
	add r0, r7, #0
	bl MOD08_02217D98
	mov r1, #0x13
	lsl r1, r1, #4
	mov r2, #0x30
	ldrsh r1, [r6, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r5, #0x18]
	add r1, r1, r2
	ldr r2, _02226EB0 ; =0x00000132
	lsl r1, r1, #0x10
	ldrsh r2, [r6, r2]
	asr r1, r1, #0x10
	bl FUN_0200C714
	ldr r1, [r4, #0x38]
	ldr r0, _02226EB4 ; =0x00003FFF
	cmp r1, r0
	blt _02226E8C
	ldr r0, _02226EB8 ; =0x0000BF49
	cmp r1, r0
	bgt _02226E8C
	ldr r0, [r5, #0x18]
	mov r1, #1
	bl FUN_0200C6B0
	b _02226E9C
_02226E8C:
	ldr r0, [r6]
	bl MOD08_02215574
	add r1, r0, #0
	ldr r0, [r5, #0x18]
	add r1, r1, #1
	bl FUN_0200C6B0
_02226E9C:
	ldr r0, [sp]
	add r7, #0x24
	add r0, r0, #1
	add r4, #0x24
	add r5, r5, #4
	str r0, [sp]
	cmp r0, #6
	blt _02226E54
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02226EB0: .word 0x00000132
_02226EB4: .word 0x00003FFF
_02226EB8: .word 0x0000BF49

	thumb_func_start MOD08_02226EBC
MOD08_02226EBC: ; 0x02226EBC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	add r7, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #4
	bhi _02226FA2
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02226ED6: ; jump table
	.short _02226EE0 - _02226ED6 - 2 ; case 0
	.short _02226F16 - _02226ED6 - 2 ; case 1
	.short _02226F36 - _02226ED6 - 2 ; case 2
	.short _02226F62 - _02226ED6 - 2 ; case 3
	.short _02226F7E - _02226ED6 - 2 ; case 4
_02226EE0:
	ldr r0, [r4]
	mov r1, #1
	mov r2, #0xf
	bl MOD08_02227994
	mov r0, #0
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	add r0, #0xfe
	add r0, r4, r0
	mov r1, #1
	mov r2, #0x10
	mov r3, #0xf
	bl MOD08_022186D4
	ldr r1, [r4, #0x14]
	add r0, r4, #0
	bl MOD08_02226DEC
	add r0, r4, #0
	bl MOD08_02226E44
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02226FA2
_02226F16:
	add r0, r4, #0
	bl MOD08_02226E44
	mov r0, #0x42
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD08_02218704
	cmp r0, #0
	beq _02226FA2
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	mov r0, #0x1c
	str r0, [r4, #0x10]
	b _02226FA2
_02226F36:
	add r0, r4, #0
	bl MOD08_02226E44
	ldr r0, [r4, #0x10]
	sub r0, r0, #1
	str r0, [r4, #0x10]
	bpl _02226FA2
	ldr r0, [r4, #0xc]
	mov r1, #0x10
	add r0, r0, #1
	str r0, [r4, #0xc]
	mov r0, #0xf
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	add r0, #0xfe
	add r0, r4, r0
	mov r2, #1
	mov r3, #0
	bl MOD08_022186D4
	b _02226FA2
_02226F62:
	add r0, r4, #0
	bl MOD08_02226E44
	mov r0, #0x42
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD08_02218704
	cmp r0, #0
	beq _02226FA2
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02226FA2
_02226F7E:
	mov r6, #0
	add r5, r4, #0
_02226F82:
	ldr r0, [r5, #0x18]
	bl FUN_0200C3DC
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #6
	blt _02226F82
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r4]
	add r1, r7, #0
	bl MOD08_02212438
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02226FA2:
	ldr r0, [r4, #8]
	bl FUN_0200BC1C
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02226FAC
MOD08_02226FAC: ; 0x02226FAC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r5, r1, #0
	mov r1, #0x4d
	lsl r1, r1, #2
	add r4, r0, #0
	str r2, [sp]
	add r7, r3, #0
	bl MOD08_02228064
	add r6, r0, #0
	str r4, [r6]
	ldr r0, [sp]
	str r5, [r6, #4]
	str r0, [r6, #8]
	add r0, r4, #0
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r6]
	bl MOD08_022154D4
	mov r1, #0
	add r5, r0, #0
	bl FUN_0200782C
	mov r1, #0x13
	lsl r1, r1, #4
	strh r0, [r6, r1]
	add r0, r5, #0
	mov r1, #1
	bl FUN_0200782C
	ldr r1, _02227050 ; =0x00000132
	strh r0, [r6, r1]
	add r0, sp, #4
	add r1, r4, #0
	bl MOD08_02215474
	mov r4, #0
	add r5, r6, #0
_02226FFE:
	cmp r4, #0
	bne _02227006
	str r7, [r5, #0x18]
	b _02227012
_02227006:
	ldr r0, [r6, #4]
	ldr r1, [r6, #8]
	add r2, sp, #4
	bl FUN_0200C154
	str r0, [r5, #0x18]
_02227012:
	ldr r0, [r5, #0x18]
	mov r1, #0x64
	bl FUN_0200C6C4
	ldr r0, [r5, #0x18]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r5, #0x18]
	mov r1, #1
	bl FUN_0200C5E0
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _02226FFE
	ldr r0, [r6]
	bl MOD08_02212458
	add r1, r0, #0
	ldr r0, [r6]
	bl MOD08_02217C1C
	str r0, [r6, #0x14]
	ldr r0, [r6]
	ldr r1, _02227054 ; =MOD08_02226EBC
	add r2, r6, #0
	bl MOD08_02212400
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02227050: .word 0x00000132
_02227054: .word MOD08_02226EBC

	thumb_func_start MOD08_02227058
MOD08_02227058: ; 0x02227058
	strh r1, [r0, #0xc]
	strh r2, [r0, #0xe]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02227060
MOD08_02227060: ; 0x02227060
	strh r1, [r0, #0x14]
	strh r2, [r0, #0x16]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02227068
MOD08_02227068: ; 0x02227068
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5, #0x1c]
	add r4, r1, #0
	bl MOD08_02212014
	add r6, r0, #0
	ldr r0, [r5, #0x1c]
	mov r1, #3
	bl MOD08_02215600
	add r1, r0, #0
	lsl r0, r4, #0x18
	lsl r1, r1, #0x18
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	bl FUN_020178BC
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	str r6, [sp, #0xc]
	ldr r1, [r5, #4]
	ldr r0, [r5]
	lsl r2, r1, #4
	ldr r1, _022270F8 ; =0x0222C670
	add r3, r4, #0
	ldr r1, [r1, r2]
	ldr r2, [r5, #0x2c]
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x80
	str r0, [sp, #8]
	ldr r2, [r5, #4]
	ldr r0, [r5, #0x30]
	lsl r3, r2, #4
	ldr r2, _022270FC ; =0x0222C674
	ldr r1, [r5]
	ldr r2, [r2, r3]
	add r3, r6, #0
	bl FUN_020030E8
	lsl r1, r4, #0x18
	ldr r0, [r5, #0x2c]
	lsr r1, r1, #0x18
	bl FUN_02018744
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	str r6, [sp, #0xc]
	ldr r1, [r5, #4]
	ldr r0, [r5]
	lsl r2, r1, #4
	ldr r1, _02227100 ; =0x0222C678
	add r3, r4, #0
	ldr r1, [r1, r2]
	ldr r2, [r5, #0x2c]
	bl FUN_020068C8
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_022270F8: .word MOD8_0222C670
_022270FC: .word MOD8_0222C674
_02227100: .word MOD8_0222C678

	thumb_func_start MOD08_02227104
MOD08_02227104: ; 0x02227104
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x18]
	cmp r0, #3
	bhi _022271C0
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222711C: ; jump table
	.short _02227124 - _0222711C - 2 ; case 0
	.short _02227134 - _0222711C - 2 ; case 1
	.short _0222714C - _0222711C - 2 ; case 2
	.short _0222716C - _0222711C - 2 ; case 3
_02227124:
	add r0, r4, #0
	mov r1, #2
	bl MOD08_02227068
	ldrb r0, [r4, #0x18]
	add r0, r0, #1
	strb r0, [r4, #0x18]
	b _0222720E
_02227134:
	ldrh r0, [r4, #0x16]
	mov r1, #4
	mov r2, #0x39
	str r0, [sp]
	ldrh r3, [r4, #0x14]
	ldr r0, _0222725C ; =0x04000050
	bl G2x_SetBlendAlpha_
	ldrb r0, [r4, #0x18]
	add r0, r0, #1
	strb r0, [r4, #0x18]
	b _0222720E
_0222714C:
	add r1, r4, #0
	add r1, #0x40
	ldrb r1, [r1]
	cmp r1, #0x14
	bls _0222715C
	add r0, r0, #1
	strb r0, [r4, #0x18]
	b _0222720E
_0222715C:
	add r0, r4, #0
	add r0, #0x40
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x40
	strb r1, [r0]
	b _0222720E
_0222716C:
	ldrh r0, [r4, #0x14]
	cmp r0, #0
	beq _02227176
	sub r0, r0, #1
	strh r0, [r4, #0x14]
_02227176:
	ldrh r0, [r4, #0x16]
	cmp r0, #0x10
	bhs _02227180
	add r0, r0, #1
	strh r0, [r4, #0x16]
_02227180:
	ldrh r0, [r4, #0x14]
	cmp r0, #0
	bne _022271B2
	ldrh r0, [r4, #0x16]
	cmp r0, #0x10
	bne _022271B2
	ldr r0, [r4, #0x2c]
	mov r1, #2
	bl FUN_02018744
	ldr r0, [r4, #0x34]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0x38]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0x3c]
	mov r1, #0
	bl FUN_0200C644
	ldrb r0, [r4, #0x18]
	add r0, r0, #1
	strb r0, [r4, #0x18]
_022271B2:
	ldrh r0, [r4, #0x16]
	ldrh r1, [r4, #0x14]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _02227260 ; =0x04000052
	strh r1, [r0]
	b _0222720E
_022271C0:
	ldr r0, _02227264 ; =0x0400004A
	mov r1, #0x3f
	ldrh r2, [r0]
	bic r2, r1
	mov r1, #0x1f
	orr r2, r1
	strh r2, [r0]
	ldrh r3, [r0]
	ldr r2, _02227268 ; =0xFFFFC0FF
	lsl r1, r1, #8
	and r2, r3
	orr r1, r2
	strh r1, [r0]
	mov r2, #0
	ldr r0, [r4, #0x2c]
	mov r1, #2
	add r3, r2, #0
	bl FUN_020179E0
	ldr r0, [r4, #0x2c]
	mov r1, #2
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _0222726C ; =0xFFFF1FFF
	and r0, r1
	str r0, [r2]
	ldr r0, [r4, #0x1c]
	add r1, r5, #0
	bl MOD08_02212438
	add r0, r4, #0
	bl MOD08_02228094
	pop {r3, r4, r5, pc}
_0222720E:
	mov r3, #0x10
	mov r0, #0xc
	ldrsh r1, [r4, r3]
	ldrsh r0, [r4, r0]
	mov r2, #0
	add r0, r1, r0
	strh r0, [r4, #0x10]
	mov r0, #0x12
	ldrsh r1, [r4, r0]
	mov r0, #0xe
	ldrsh r0, [r4, r0]
	add r0, r1, r0
	strh r0, [r4, #0x12]
	ldrsh r3, [r4, r3]
	ldr r0, [r4, #0x2c]
	mov r1, #2
	bl FUN_020179E0
	mov r3, #0x12
	ldrsh r3, [r4, r3]
	ldr r0, [r4, #0x2c]
	mov r1, #2
	mov r2, #3
	bl FUN_020179E0
	ldr r0, [r4, #0x34]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x38]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x3c]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x24]
	bl FUN_0200BC1C
	pop {r3, r4, r5, pc}
	nop
_0222725C: .word 0x04000050
_02227260: .word 0x04000052
_02227264: .word 0x0400004A
_02227268: .word 0xFFFFC0FF
_0222726C: .word 0xFFFF1FFF

	thumb_func_start MOD08_02227270
MOD08_02227270: ; 0x02227270
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #7
	str r1, [r4]
	add r5, r0, #0
	mov r1, #0
	bl MOD08_02212498
	str r0, [r4, #4]
	add r0, r5, #0
	mov r1, #1
	bl MOD08_02212498
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02227290
MOD08_02227290: ; 0x02227290
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r1, #0x44
	add r6, r0, #0
	bl MOD08_02228064
	add r4, r0, #0
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x18
	bl MOD08_02227B70
	add r2, r4, #0
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r4, #0x1c]
	mov r1, #0
	bl MOD08_022124D8
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x1c]
	mov r1, #1
	bl MOD08_022124D8
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x1c]
	mov r1, #2
	bl MOD08_022124D8
	str r0, [r4, #0x3c]
	ldr r0, [r4, #0x1c]
	mov r1, #2
	bl MOD08_02215600
	ldr r0, [r4, #0x34]
	mov r1, #2
	bl FUN_0200C6B0
	ldr r0, [r4, #0x38]
	mov r1, #2
	bl FUN_0200C6B0
	ldr r0, [r4, #8]
	cmp r0, #0
	bne _022272FA
	add r0, r6, #0
	bl MOD08_02212458
	b _02227300
_022272FA:
	add r0, r6, #0
	bl MOD08_02212460
_02227300:
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r6, #0
	bl MOD08_02212004
	cmp r0, #1
	bne _02227338
	ldr r0, [r4, #0x3c]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4, #0x1c]
	mov r1, #2
	bl MOD08_02215600
	add r5, r0, #0
	ldr r0, [r4, #0x34]
	add r1, r5, #0
	bl FUN_0200C6B0
	ldr r0, [r4, #0x38]
	add r1, r5, #0
	bl FUN_0200C6B0
	b _0222735C
_02227338:
	cmp r5, #1
	bhi _02227346
	ldr r0, [r4, #0x3c]
	mov r1, #0
	bl FUN_0200C644
	b _0222735C
_02227346:
	sub r0, r5, #3
	cmp r0, #1
	ldr r0, [r4, #0x3c]
	bhi _02227356
	mov r1, #3
	bl FUN_0200C6B0
	b _0222735C
_02227356:
	mov r1, #1
	bl FUN_0200C6B0
_0222735C:
	ldr r0, _022273A8 ; =0x0400004A
	ldr r1, _022273AC ; =0xFFFFC0FF
	ldrh r2, [r0]
	and r2, r1
	mov r1, #0x16
	lsl r1, r1, #8
	orr r2, r1
	lsr r1, r0, #0xd
	orr r1, r2
	strh r1, [r0]
	ldrh r2, [r0]
	mov r1, #0x3f
	bic r2, r1
	mov r1, #0x1b
	orr r2, r1
	mov r1, #0x20
	orr r2, r1
	strh r2, [r0]
	lsl r3, r1, #0x15
	ldr r2, [r3]
	ldr r0, _022273B0 ; =0xFFFF1FFF
	and r2, r0
	lsl r0, r1, #0xa
	orr r0, r2
	str r0, [r3]
	ldr r0, [r4, #0x38]
	mov r1, #2
	bl FUN_0200C90C
	mov r0, #0
	strh r0, [r4, #0x10]
	strh r0, [r4, #0x12]
	ldr r0, [r4, #0x1c]
	ldr r1, _022273B4 ; =MOD08_02227104
	add r2, r4, #0
	bl MOD08_02212400
	pop {r4, r5, r6, pc}
	.align 2, 0
_022273A8: .word 0x0400004A
_022273AC: .word 0xFFFFC0FF
_022273B0: .word 0xFFFF1FFF
_022273B4: .word MOD08_02227104

	thumb_func_start MOD08_022273B8
MOD08_022273B8: ; 0x022273B8
	push {r4, lr}
	sub sp, #0x18
	add r1, sp, #0
	add r4, r0, #0
	bl MOD08_02227270
	add r0, sp, #0
	mov r1, #0
	mov r2, #3
	bl MOD08_02227058
	add r0, sp, #0
	mov r1, #0xc
	mov r2, #4
	bl MOD08_02227060
	add r0, r4, #0
	add r1, sp, #0
	bl MOD08_02227290
	add sp, #0x18
	pop {r4, pc}

	thumb_func_start MOD08_022273E4
MOD08_022273E4: ; 0x022273E4
	push {r4, lr}
	sub sp, #0x18
	add r1, sp, #0
	add r4, r0, #0
	bl MOD08_02227270
	mov r1, #0
	add r0, sp, #0
	sub r2, r1, #3
	bl MOD08_02227058
	add r0, sp, #0
	mov r1, #0xc
	mov r2, #4
	bl MOD08_02227060
	add r0, r4, #0
	add r1, sp, #0
	bl MOD08_02227290
	add sp, #0x18
	pop {r4, pc}

	thumb_func_start MOD08_02227410
MOD08_02227410: ; 0x02227410
	push {r4, lr}
	sub sp, #0x18
	add r1, sp, #0
	add r4, r0, #0
	bl MOD08_02227270
	add r0, sp, #0
	mov r1, #0
	mov r2, #3
	bl MOD08_02227058
	add r0, sp, #0
	mov r1, #0xc
	mov r2, #4
	bl MOD08_02227060
	add r0, r4, #0
	add r1, sp, #0
	bl MOD08_02227290
	add sp, #0x18
	pop {r4, pc}

	thumb_func_start MOD08_0222743C
MOD08_0222743C: ; 0x0222743C
	push {r4, lr}
	sub sp, #0x18
	add r1, sp, #0
	add r4, r0, #0
	bl MOD08_02227270
	mov r1, #0
	add r0, sp, #0
	sub r2, r1, #6
	bl MOD08_02227058
	add r0, sp, #0
	mov r1, #0xc
	mov r2, #4
	bl MOD08_02227060
	add r0, r4, #0
	add r1, sp, #0
	bl MOD08_02227290
	add sp, #0x18
	pop {r4, pc}

	thumb_func_start MOD08_02227468
MOD08_02227468: ; 0x02227468
	ldr r3, _0222746C ; =MOD08_02215490
	bx r3
	.align 2, 0
_0222746C: .word MOD08_02215490

	thumb_func_start MOD08_02227470
MOD08_02227470: ; 0x02227470
	push {r4, lr}
	bl MOD08_02215490
	cmp r0, #5
	bhi _02227498
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02227486: ; jump table
	.short _02227492 - _02227486 - 2 ; case 0
	.short _02227496 - _02227486 - 2 ; case 1
	.short _02227492 - _02227486 - 2 ; case 2
	.short _02227496 - _02227486 - 2 ; case 3
	.short _02227492 - _02227486 - 2 ; case 4
	.short _02227496 - _02227486 - 2 ; case 5
_02227492:
	mov r4, #3
	b _02227498
_02227496:
	mov r4, #4
_02227498:
	add r0, r4, #0
	pop {r4, pc}

	thumb_func_start MOD08_0222749C
MOD08_0222749C: ; 0x0222749C
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r4, #0
_022274A4:
	add r0, r6, #0
	add r1, r4, #0
	bl MOD08_02215490
	cmp r0, r5
	bne _022274B4
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_022274B4:
	add r4, r4, #1
	cmp r4, #4
	blt _022274A4
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_022274C0
MOD08_022274C0: ; 0x022274C0
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl MOD08_02215490
	add r5, r0, #0
	cmp r5, #1
	bls _02227520
	mov r4, #0
_022274D0:
	add r0, r6, #0
	add r1, r4, #0
	bl MOD08_02215490
	cmp r5, #5
	bhi _02227514
	add r1, r5, r5
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022274E8: ; jump table
	.short _02227514 - _022274E8 - 2 ; case 0
	.short _02227514 - _022274E8 - 2 ; case 1
	.short _022274F4 - _022274E8 - 2 ; case 2
	.short _02227504 - _022274E8 - 2 ; case 3
	.short _022274FC - _022274E8 - 2 ; case 4
	.short _0222750C - _022274E8 - 2 ; case 5
_022274F4:
	cmp r0, #4
	bne _02227514
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_022274FC:
	cmp r0, #2
	bne _02227514
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_02227504:
	cmp r0, #5
	bne _02227514
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_0222750C:
	cmp r0, #3
	bne _02227514
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_02227514:
	add r4, r4, #1
	cmp r4, #4
	blt _022274D0
	bl ErrorHandling
	add r0, r5, #0
_02227520:
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_02227524
MOD08_02227524: ; 0x02227524
	push {r3, lr}
	cmp r0, #5
	bhi _0222755A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02227536: ; jump table
	.short _02227542 - _02227536 - 2 ; case 0
	.short _02227546 - _02227536 - 2 ; case 1
	.short _0222754A - _02227536 - 2 ; case 2
	.short _0222754E - _02227536 - 2 ; case 3
	.short _02227552 - _02227536 - 2 ; case 4
	.short _02227556 - _02227536 - 2 ; case 5
_02227542:
	mov r0, #1
	pop {r3, pc}
_02227546:
	mov r0, #0
	pop {r3, pc}
_0222754A:
	mov r0, #3
	pop {r3, pc}
_0222754E:
	mov r0, #2
	pop {r3, pc}
_02227552:
	mov r0, #5
	pop {r3, pc}
_02227556:
	mov r0, #4
	pop {r3, pc}
_0222755A:
	bl ErrorHandling
	mov r0, #0
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD08_02227564
MOD08_02227564: ; 0x02227564
	push {r3, r4, r5, r6}
	sub sp, #0x30
	ldr r6, _022275B8 ; =0x0222C6C8
	add r5, sp, #0x18
	mov r4, #0xc
_0222756E:
	ldrh r3, [r6]
	add r6, r6, #2
	strh r3, [r5]
	add r5, r5, #2
	sub r4, r4, #1
	bne _0222756E
	ldr r6, _022275BC ; =0x0222C6E0
	add r5, sp, #0
	mov r4, #0xc
_02227580:
	ldrh r3, [r6]
	add r6, r6, #2
	strh r3, [r5]
	add r5, r5, #2
	sub r4, r4, #1
	bne _02227580
	cmp r1, #0
	beq _022275A4
	lsl r3, r0, #2
	add r0, sp, #0
	add r1, r0, r3
	ldrh r0, [r0, r3]
	add sp, #0x30
	strh r0, [r2]
	ldrh r0, [r1, #2]
	strh r0, [r2, #2]
	pop {r3, r4, r5, r6}
	bx lr
_022275A4:
	lsl r3, r0, #2
	add r0, sp, #0x18
	add r1, r0, r3
	ldrh r0, [r0, r3]
	strh r0, [r2]
	ldrh r0, [r1, #2]
	strh r0, [r2, #2]
	add sp, #0x30
	pop {r3, r4, r5, r6}
	bx lr
	.align 2, 0
_022275B8: .word MOD8_0222C6C8
_022275BC: .word MOD8_0222C6E0

	thumb_func_start MOD08_022275C0
MOD08_022275C0: ; 0x022275C0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r2, #0
	bl MOD08_02227468
	add r6, r0, #0
	add r0, r5, #0
	bl MOD08_02212004
	add r1, r0, #0
	add r0, r6, #0
	add r2, r4, #0
	bl MOD08_02227564
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_022275E0
MOD08_022275E0: ; 0x022275E0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x114
	add r7, r2, #0
	mov r2, #0x12
	str r3, [sp]
	ldr r6, _02227654 ; =0x0222C6F8
	add r5, r0, #0
	add r4, r1, #0
	add r3, sp, #4
	lsl r2, r2, #4
_022275FC:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _022275FC
	cmp r7, #1
	bne _0222761E
	cmp r5, #0
	beq _02227612
	cmp r5, #1
	beq _02227616
	b _0222761A
_02227612:
	mov r5, #6
	b _0222761E
_02227616:
	mov r5, #7
	b _0222761E
_0222761A:
	bl ErrorHandling
_0222761E:
	mov r0, #0x12
	lsl r0, r0, #4
	add r1, sp, #4
	mul r0, r5
	add r0, r1, r0
	ldr r1, _02227658 ; =0x00000908
	add r1, sp
	ldr r1, [r1, #0x10]
	lsl r2, r1, #1
	ldr r1, [sp]
	add r2, r1, r2
	mov r1, #0xc
	add r3, r2, #0
	mul r3, r1
	add r1, r0, r3
	ldr r2, [r1, #8]
	ldr r1, [r1, #4]
	ldr r0, [r0, r3]
	str r0, [r4]
	str r1, [r4, #4]
	str r2, [r4, #8]
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x114
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02227654: .word MOD8_0222C6F8
_02227658: .word 0x00000908

	thumb_func_start MOD08_0222765C
MOD08_0222765C: ; 0x0222765C
	push {r3, r4, lr}
	sub sp, #4
	mov r4, #0
	str r4, [sp]
	bl MOD08_022275E0
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD08_0222766C
MOD08_0222766C: ; 0x0222766C
	push {r3, r4, lr}
	sub sp, #4
	mov r4, #1
	str r4, [sp]
	bl MOD08_022275E0
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD08_0222767C
MOD08_0222767C: ; 0x0222767C
	push {r3, r4, lr}
	sub sp, #4
	mov r4, #2
	str r4, [sp]
	bl MOD08_022275E0
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD08_0222768C
MOD08_0222768C: ; 0x0222768C
	push {r3, r4, lr}
	sub sp, #4
	mov r4, #3
	str r4, [sp]
	bl MOD08_022275E0
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD08_0222769C
MOD08_0222769C: ; 0x0222769C
	push {r3, r4, lr}
	sub sp, #4
	mov r4, #4
	str r4, [sp]
	bl MOD08_022275E0
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD08_022276AC
MOD08_022276AC: ; 0x022276AC
	push {r3, r4, lr}
	sub sp, #4
	mov r4, #5
	str r4, [sp]
	bl MOD08_022275E0
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD08_022276BC
MOD08_022276BC: ; 0x022276BC
	push {r3, r4, lr}
	sub sp, #4
	mov r4, #6
	str r4, [sp]
	bl MOD08_022275E0
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD08_022276CC
MOD08_022276CC: ; 0x022276CC
	push {r3, r4, lr}
	sub sp, #4
	mov r4, #7
	str r4, [sp]
	bl MOD08_022275E0
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD08_022276DC
MOD08_022276DC: ; 0x022276DC
	push {r3, r4, lr}
	sub sp, #4
	mov r4, #8
	str r4, [sp]
	bl MOD08_022275E0
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD08_022276EC
MOD08_022276EC: ; 0x022276EC
	push {r3, r4, lr}
	sub sp, #4
	mov r4, #9
	str r4, [sp]
	bl MOD08_022275E0
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD08_022276FC
MOD08_022276FC: ; 0x022276FC
	push {r3, r4, lr}
	sub sp, #4
	mov r4, #0xa
	str r4, [sp]
	bl MOD08_022275E0
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD08_0222770C
MOD08_0222770C: ; 0x0222770C
	push {r3, r4, lr}
	sub sp, #4
	mov r4, #0xb
	str r4, [sp]
	bl MOD08_022275E0
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD08_0222771C
MOD08_0222771C: ; 0x0222771C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl MOD08_02212468
	bl FUN_02013448
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02212004
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	add r3, r7, #0
	bl MOD08_0222765C
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_0222774C
MOD08_0222774C: ; 0x0222774C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl MOD08_02212468
	bl FUN_02013448
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02212004
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	add r3, r7, #0
	bl MOD08_0222766C
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_0222777C
MOD08_0222777C: ; 0x0222777C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl MOD08_02212468
	bl FUN_02013448
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02212004
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	add r3, r7, #0
	bl MOD08_0222767C
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_022277AC
MOD08_022277AC: ; 0x022277AC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl MOD08_02212468
	bl FUN_02013448
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02212004
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	add r3, r7, #0
	bl MOD08_0222768C
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_022277DC
MOD08_022277DC: ; 0x022277DC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl MOD08_02212468
	bl FUN_02013448
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02212004
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	add r3, r7, #0
	bl MOD08_0222769C
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_0222780C
MOD08_0222780C: ; 0x0222780C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl MOD08_02212468
	bl FUN_02013448
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02212004
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	add r3, r7, #0
	bl MOD08_022276AC
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_0222783C
MOD08_0222783C: ; 0x0222783C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl MOD08_02212468
	bl FUN_02013448
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02212004
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	add r3, r7, #0
	bl MOD08_022276BC
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_0222786C
MOD08_0222786C: ; 0x0222786C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl MOD08_02212468
	bl FUN_02013448
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02212004
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	add r3, r7, #0
	bl MOD08_022276CC
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_0222789C
MOD08_0222789C: ; 0x0222789C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl MOD08_02212468
	bl FUN_02013448
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02212004
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	add r3, r7, #0
	bl MOD08_022276DC
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_022278CC
MOD08_022278CC: ; 0x022278CC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl MOD08_02212468
	bl FUN_02013448
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02212004
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	add r3, r7, #0
	bl MOD08_022276EC
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_022278FC
MOD08_022278FC: ; 0x022278FC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl MOD08_02212468
	bl FUN_02013448
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02212004
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	add r3, r7, #0
	bl MOD08_022276FC
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_0222792C
MOD08_0222792C: ; 0x0222792C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl MOD08_02212468
	bl FUN_02013448
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD08_02227468
	add r5, r0, #0
	add r0, r4, #0
	bl MOD08_02212004
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	add r3, r7, #0
	bl MOD08_0222770C
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_0222795C
MOD08_0222795C: ; 0x0222795C
	mov r2, #0
	ldr r1, _02227968 ; =0x000068D0
	str r2, [r0]
	str r1, [r0, #4]
	str r2, [r0, #8]
	bx lr
	.align 2, 0
_02227968: .word 0x000068D0

	thumb_func_start MOD08_0222796C
MOD08_0222796C: ; 0x0222796C
	push {r3, lr}
	bl MOD08_0222765C
	pop {r3, pc}

	thumb_func_start MOD08_02227974
MOD08_02227974: ; 0x02227974
	push {r3, lr}
	add r3, r1, #0
	cmp r0, #0
	bne _02227984
	add r0, r3, #0
	bl FUN_02013428
	pop {r3, pc}
_02227984:
	ldr r2, _02227990 ; =0x0222C6BC
	ldmia r2!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r2]
	str r0, [r3]
	pop {r3, pc}
	.align 2, 0
_02227990: .word MOD8_0222C6BC

	thumb_func_start MOD08_02227994
MOD08_02227994: ; 0x02227994
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r1, #0
	mvn r1, r1
	add r4, r2, #0
	cmp r5, r1
	bne _022279A4
	mov r5, #0x1a
_022279A4:
	mov r1, #0
	mvn r1, r1
	cmp r4, r1
	bne _022279AE
	mov r4, #5
_022279AE:
	mov r1, #2
	bl MOD08_022155C4
	mov r1, #1
	add r2, r1, #0
	lsl r2, r0
	orr r2, r1
	ldr r0, _022279CC ; =0x04000050
	mov r1, #0
	add r3, r5, #0
	str r4, [sp]
	bl G2x_SetBlendAlpha_
	pop {r3, r4, r5, pc}
	nop
_022279CC: .word 0x04000050

	thumb_func_start MOD08_022279D0
MOD08_022279D0: ; 0x022279D0
	push {r3, r4, r5, lr}
	mov r0, #0
	add r4, r2, #0
	mvn r0, r0
	add r5, r1, #0
	cmp r4, r0
	bne _022279E0
	mov r4, #0x1a
_022279E0:
	mov r0, #0
	mvn r0, r0
	cmp r3, r0
	bne _022279EA
	mov r3, #5
_022279EA:
	ldr r0, _022279FC ; =0x04000050
	str r3, [sp]
	mov r1, #0
	add r2, r5, #0
	add r3, r4, #0
	bl G2x_SetBlendAlpha_
	pop {r3, r4, r5, pc}
	nop
_022279FC: .word 0x04000050

	thumb_func_start MOD08_02227A00
MOD08_02227A00: ; 0x02227A00
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0
	add r5, r1, #0
	mvn r0, r0
	add r4, r2, #0
	cmp r5, r0
	bne _02227A12
	mov r5, #0x1a
_02227A12:
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _02227A1C
	mov r4, #5
_02227A1C:
	add r0, r6, #0
	mov r1, #2
	bl MOD08_022155C4
	mov r1, #1
	add r2, r1, #0
	lsl r2, r0
	mov r0, #0x11
	add r7, r2, #0
	orr r7, r0
	add r0, r6, #0
	bl MOD08_022155C4
	mov r1, #1
	lsl r1, r0
	ldr r0, _02227A48 ; =0x04000050
	add r2, r7, #0
	add r3, r5, #0
	str r4, [sp]
	bl G2x_SetBlendAlpha_
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02227A48: .word 0x04000050

	thumb_func_start MOD08_02227A4C
MOD08_02227A4C: ; 0x02227A4C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r2, #0
	cmp r1, #0
	bne _02227AA0
	mov r1, #1
	bl MOD08_022155C4
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #2
	bl MOD08_022155C4
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #0
	bl MOD08_022155C4
	add r2, r0, #0
	mov r0, #1
	add r3, r0, #0
	add r1, r0, #0
	lsl r3, r7
	lsl r0, r2
	lsl r1, r6
	orr r0, r3
	orr r1, r0
	mov r0, #0x11
	add r2, r1, #0
	orr r2, r0
	ldr r0, _02227B20 ; =0x04000048
	ldrh r1, [r0]
	mov r0, #0x3f
	bic r1, r0
	orr r1, r2
	cmp r4, #0
	beq _02227A9A
	mov r0, #0x20
	orr r1, r0
_02227A9A:
	ldr r0, _02227B20 ; =0x04000048
	strh r1, [r0]
	b _02227AEA
_02227AA0:
	mov r1, #1
	bl MOD08_022155C4
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #2
	bl MOD08_022155C4
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #0
	bl MOD08_022155C4
	add r2, r0, #0
	mov r0, #1
	add r3, r0, #0
	add r1, r0, #0
	lsl r0, r2
	lsl r3, r7
	lsl r1, r6
	orr r0, r3
	orr r1, r0
	ldr r2, _02227B20 ; =0x04000048
	add r3, r1, #0
	mov r0, #0x11
	orr r3, r0
	ldrh r1, [r2]
	ldr r0, _02227B24 ; =0xFFFFC0FF
	and r1, r0
	lsl r0, r3, #8
	orr r1, r0
	cmp r4, #0
	beq _02227AE6
	lsr r0, r2, #0xd
	orr r1, r0
_02227AE6:
	ldr r0, _02227B20 ; =0x04000048
	strh r1, [r0]
_02227AEA:
	add r0, r5, #0
	mov r1, #0
	bl MOD08_022155C4
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl MOD08_022155C4
	mov r1, #1
	add r2, r1, #0
	lsl r1, r0
	lsl r2, r4
	orr r1, r2
	add r3, r1, #0
	ldr r1, _02227B28 ; =0x0400004A
	mov r0, #0x11
	orr r3, r0
	ldrh r2, [r1]
	mov r0, #0x3f
	bic r2, r0
	orr r2, r3
	mov r0, #0x20
	orr r0, r2
	strh r0, [r1]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02227B20: .word 0x04000048
_02227B24: .word 0xFFFFC0FF
_02227B28: .word 0x0400004A

	thumb_func_start MOD08_02227B2C
MOD08_02227B2C: ; 0x02227B2C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	cmp r5, #0
	bne _02227B3E
	mov r0, #0
	strh r0, [r4]
	strh r0, [r4, #2]
	pop {r3, r4, r5, pc}
_02227B3E:
	bl FUN_02008268
	cmp r0, #0
	bne _02227B4E
	mov r0, #0
	strh r0, [r4]
	strh r0, [r4, #2]
	pop {r3, r4, r5, pc}
_02227B4E:
	add r0, r5, #0
	mov r1, #0
	bl FUN_0200782C
	strh r0, [r4]
	add r0, r5, #0
	mov r1, #1
	bl FUN_0200782C
	strh r0, [r4, #2]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02227B64
MOD08_02227B64: ; 0x02227B64
	ldr r3, _02227B6C ; =FUN_0200C7A0
	add r2, r1, #2
	bx r3
	nop
_02227B6C: .word FUN_0200C7A0

	thumb_func_start MOD08_02227B70
MOD08_02227B70: ; 0x02227B70
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #0
	strb r1, [r4]
	strb r1, [r4, #1]
	strb r1, [r4, #2]
	add r5, r0, #0
	strb r1, [r4, #3]
	str r5, [r4, #4]
	bl MOD08_02212520
	str r0, [r4, #8]
	add r0, r5, #0
	bl MOD08_02212504
	str r0, [r4, #0xc]
	add r0, r5, #0
	bl MOD08_02212518
	str r0, [r4, #0x10]
	add r0, r5, #0
	bl MOD08_02212490
	str r0, [r4, #0x14]
	add r0, r5, #0
	bl MOD08_02215504
	str r0, [r4, #0x18]
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02227BAC
MOD08_02227BAC: ; 0x02227BAC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r1, #0
	add r4, r3, #0
	mov r1, #0
	str r1, [r4]
	mov r1, #0x40
	and r1, r7
	add r6, r0, #0
	add r5, r2, #0
	cmp r1, #0x40
	beq _02227BC6
	b _02227CE8
_02227BC6:
	bl MOD08_02212458
	add r7, r0, #0
	add r0, r6, #0
	add r1, r7, #0
	bl MOD08_022154D4
	add r2, r0, #0
	ldr r0, [r4]
	mov r3, #0x14
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	str r2, [r0, #8]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r1, r5, r1
	ldr r0, [r1, #8]
	cmp r0, #0
	beq _02227C08
	str r7, [r1, #0x10]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r1, r5, r1
	ldr r0, [r1, #8]
	add r1, r1, #4
	bl MOD08_02227B2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02227C08:
	add r0, r6, #0
	add r1, r7, #0
	bl MOD08_022274C0
	str r0, [sp, #4]
	ldr r1, [sp, #4]
	add r0, r6, #0
	bl MOD08_022154D4
	add r2, r0, #0
	ldr r0, [r4]
	mov r3, #0x14
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	str r2, [r0, #8]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	ldr r1, [r0, #8]
	cmp r1, #0
	beq _02227C50
	ldr r1, [sp, #4]
	str r1, [r0, #0x10]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r1, r5, r1
	ldr r0, [r1, #8]
	add r1, r1, #4
	bl MOD08_02227B2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02227C50:
	add r0, r6, #0
	add r1, r7, #0
	bl MOD08_02215490
	bl MOD08_02227524
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_0222749C
	add r7, r0, #0
	add r0, r6, #0
	add r1, r7, #0
	bl MOD08_022154D4
	add r2, r0, #0
	ldr r0, [r4]
	mov r3, #0x14
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	str r2, [r0, #8]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r1, r5, r1
	ldr r0, [r1, #8]
	cmp r0, #0
	beq _02227CA2
	str r7, [r1, #0x10]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r1, r5, r1
	ldr r0, [r1, #8]
	add r1, r1, #4
	bl MOD08_02227B2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02227CA2:
	add r0, r6, #0
	add r1, r7, #0
	bl MOD08_022274C0
	add r7, r0, #0
	add r0, r6, #0
	add r1, r7, #0
	bl MOD08_022154D4
	ldr r2, [r4]
	mov r1, #0x14
	add r3, r2, #0
	mul r3, r1
	add r2, r5, r3
	str r0, [r2, #8]
	ldr r0, [r4]
	add r2, r0, #0
	mul r2, r1
	add r2, r5, r2
	ldr r0, [r2, #8]
	cmp r0, #0
	beq _02227DCA
	str r7, [r2, #0x10]
	ldr r0, [r4]
	mul r1, r0
	add r1, r5, r1
	ldr r0, [r1, #8]
	add r1, r1, #4
	bl MOD08_02227B2C
	ldr r0, [r4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_02227CE8:
	mov r1, #0x20
	and r1, r7
	cmp r1, #0x20
	bne _02227DE8
	bl MOD08_02212458
	add r7, r0, #0
	add r0, r6, #0
	add r1, r7, #0
	bl MOD08_022274C0
	str r0, [sp, #8]
	cmp r0, r7
	beq _02227D42
	ldr r1, [sp, #8]
	add r0, r6, #0
	bl MOD08_022154D4
	add r2, r0, #0
	ldr r0, [r4]
	mov r3, #0x14
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	str r2, [r0, #8]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	ldr r1, [r0, #8]
	cmp r1, #0
	beq _02227D42
	ldr r1, [sp, #8]
	str r1, [r0, #0x10]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r1, r5, r1
	ldr r0, [r1, #8]
	add r1, r1, #4
	bl MOD08_02227B2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02227D42:
	add r0, r6, #0
	add r1, r7, #0
	bl MOD08_02215490
	bl MOD08_02227524
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_0222749C
	str r0, [sp]
	cmp r0, r7
	beq _02227D9A
	ldr r1, [sp]
	add r0, r6, #0
	bl MOD08_022154D4
	add r2, r0, #0
	ldr r0, [r4]
	mov r3, #0x14
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	str r2, [r0, #8]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	ldr r1, [r0, #8]
	cmp r1, #0
	beq _02227D9A
	ldr r1, [sp]
	str r1, [r0, #0x10]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r1, r5, r1
	ldr r0, [r1, #8]
	add r1, r1, #4
	bl MOD08_02227B2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02227D9A:
	ldr r1, [sp]
	add r0, r6, #0
	bl MOD08_022274C0
	str r0, [sp, #0xc]
	cmp r0, r7
	beq _02227DCA
	ldr r1, [sp, #0xc]
	add r0, r6, #0
	bl MOD08_022154D4
	ldr r2, [r4]
	mov r1, #0x14
	add r3, r2, #0
	mul r3, r1
	add r2, r5, r3
	str r0, [r2, #8]
	ldr r0, [r4]
	add r2, r0, #0
	mul r2, r1
	add r2, r5, r2
	ldr r0, [r2, #8]
	cmp r0, #0
	bne _02227DCC
_02227DCA:
	b _02227F82
_02227DCC:
	ldr r0, [sp, #0xc]
	str r0, [r2, #0x10]
	ldr r0, [r4]
	mul r1, r0
	add r1, r5, r1
	ldr r0, [r1, #8]
	add r1, r1, #4
	bl MOD08_02227B2C
	ldr r0, [r4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_02227DE8:
	mov r1, #2
	and r1, r7
	cmp r1, #2
	bne _02227E42
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_022154D4
	add r2, r0, #0
	ldr r0, [r4]
	mov r3, #0x14
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	str r2, [r0, #8]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	ldr r0, [r0, #8]
	cmp r0, #0
	beq _02227E42
	add r0, r6, #0
	bl MOD08_02212458
	add r2, r0, #0
	ldr r0, [r4]
	mov r3, #0x14
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	str r2, [r0, #0x10]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r1, r5, r1
	ldr r0, [r1, #8]
	add r1, r1, #4
	bl MOD08_02227B2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02227E42:
	add r0, r6, #0
	bl MOD08_0221553C
	cmp r0, #1
	bne _02227EB8
	mov r0, #4
	and r0, r7
	cmp r0, #4
	bne _02227EB8
	add r0, r6, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_022274C0
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_022154D4
	add r2, r0, #0
	ldr r0, [r4]
	mov r3, #0x14
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	str r2, [r0, #8]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	ldr r0, [r0, #8]
	cmp r0, #0
	beq _02227EB8
	add r0, r6, #0
	bl MOD08_02212458
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_022274C0
	add r2, r0, #0
	ldr r0, [r4]
	mov r3, #0x14
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	str r2, [r0, #0x10]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r1, r5, r1
	ldr r0, [r1, #8]
	add r1, r1, #4
	bl MOD08_02227B2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02227EB8:
	mov r0, #8
	and r0, r7
	cmp r0, #8
	bne _02227F14
	add r0, r6, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_022154D4
	add r2, r0, #0
	ldr r0, [r4]
	mov r3, #0x14
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	str r2, [r0, #8]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	ldr r0, [r0, #8]
	cmp r0, #0
	beq _02227F14
	add r0, r6, #0
	bl MOD08_02212460
	add r2, r0, #0
	ldr r0, [r4]
	mov r3, #0x14
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	str r2, [r0, #0x10]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r1, r5, r1
	ldr r0, [r1, #8]
	add r1, r1, #4
	bl MOD08_02227B2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02227F14:
	add r0, r6, #0
	bl MOD08_0221553C
	cmp r0, #1
	bne _02227F82
	mov r0, #0x10
	and r0, r7
	cmp r0, #0x10
	bne _02227F82
	add r0, r6, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_022274C0
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_022154D4
	ldr r2, [r4]
	mov r1, #0x14
	add r3, r2, #0
	mul r3, r1
	add r2, r5, r3
	str r0, [r2, #8]
	ldr r0, [r4]
	mul r1, r0
	add r0, r5, r1
	ldr r0, [r0, #8]
	cmp r0, #0
	beq _02227F82
	add r0, r6, #0
	bl MOD08_02212460
	add r1, r0, #0
	add r0, r6, #0
	bl MOD08_022274C0
	ldr r2, [r4]
	mov r1, #0x14
	add r3, r2, #0
	mul r3, r1
	add r2, r5, r3
	str r0, [r2, #0x10]
	ldr r0, [r4]
	mul r1, r0
	add r1, r5, r1
	ldr r0, [r1, #8]
	add r1, r1, #4
	bl MOD08_02227B2C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02227F82:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02227F88
MOD08_02227F88: ; 0x02227F88
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r4, r3, #0
	mov r1, #0
	str r1, [r4]
	mov r1, #2
	and r1, r6
	add r7, r0, #0
	add r5, r2, #0
	cmp r1, #2
	bne _02227FC8
	ldr r1, [r4]
	bl MOD08_022124D8
	add r2, r0, #0
	ldr r0, [r4]
	mov r3, #0x14
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	str r2, [r0, #0xc]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r1, r5, r1
	ldr r0, [r1, #0xc]
	add r1, r1, #4
	bl MOD08_02227B64
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02227FC8:
	mov r0, #4
	and r0, r6
	cmp r0, #4
	bne _02227FFC
	ldr r1, [r4]
	add r0, r7, #0
	bl MOD08_022124D8
	add r2, r0, #0
	ldr r0, [r4]
	mov r3, #0x14
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	str r2, [r0, #0xc]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r1, r5, r1
	ldr r0, [r1, #0xc]
	add r1, r1, #4
	bl MOD08_02227B64
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02227FFC:
	mov r0, #8
	and r0, r6
	cmp r0, #8
	bne _02228030
	ldr r1, [r4]
	add r0, r7, #0
	bl MOD08_022124D8
	add r2, r0, #0
	ldr r0, [r4]
	mov r3, #0x14
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	str r2, [r0, #0xc]
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r3
	add r1, r5, r1
	ldr r0, [r1, #0xc]
	add r1, r1, #4
	bl MOD08_02227B64
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02228030:
	mov r0, #0x10
	and r0, r6
	cmp r0, #0x10
	bne _02228060
	ldr r1, [r4]
	add r0, r7, #0
	bl MOD08_022124D8
	ldr r2, [r4]
	mov r1, #0x14
	add r3, r2, #0
	mul r3, r1
	add r2, r5, r3
	str r0, [r2, #0xc]
	ldr r0, [r4]
	mul r1, r0
	add r1, r5, r1
	ldr r0, [r1, #0xc]
	add r1, r1, #4
	bl MOD08_02227B64
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02228060:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_02228064
MOD08_02228064: ; 0x02228064
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r5, r1, #0
	cmp r4, #0
	bne _02228072
	bl ErrorHandling
_02228072:
	add r0, r4, #0
	bl MOD08_02212014
	add r1, r5, #0
	bl AllocFromHeap
	add r4, r0, #0
	bne _02228086
	bl ErrorHandling
_02228086:
	add r0, r4, #0
	mov r1, #0
	add r2, r5, #0
	bl memset
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02228094
MOD08_02228094: ; 0x02228094
	push {r4, lr}
	add r4, r0, #0
	bne _0222809E
	bl ErrorHandling
_0222809E:
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_022280A8
MOD08_022280A8: ; 0x022280A8
	cmp r0, #1
	blt _022280B2
	ldr r1, _022280C0 ; =0x00000113
	cmp r0, r1
	ble _022280B6
_022280B2:
	mov r0, #4
	b _022280BC
_022280B6:
	cmp r0, #0xff
	blt _022280BC
	sub r0, #0xff
_022280BC:
	sub r0, r0, #1
	bx lr
	.align 2, 0
_022280C0: .word 0x00000113

	thumb_func_start MOD08_022280C4
MOD08_022280C4: ; 0x022280C4
	push {r3, r4, r5}
	sub sp, #0x2c
	ldr r5, _02228100 ; =0x0222D0A4
	add r2, r0, #0
	add r4, sp, #0
	mov r3, #5
_022280D0:
	ldmia r5!, {r0, r1}
	stmia r4!, {r0, r1}
	sub r3, r3, #1
	bne _022280D0
	ldr r0, [r5]
	str r0, [r4]
	mov r0, #0
	add r3, r0, #0
	add r4, sp, #0
_022280E2:
	ldr r1, [r4]
	cmp r2, r1
	bne _022280F0
	add sp, #0x2c
	mov r0, #1
	pop {r3, r4, r5}
	bx lr
_022280F0:
	add r3, r3, #1
	add r4, r4, #4
	cmp r3, #0xb
	blo _022280E2
	add sp, #0x2c
	pop {r3, r4, r5}
	bx lr
	nop
_02228100: .word MOD8_0222D0A4

	thumb_func_start MOD08_02228104
MOD08_02228104: ; 0x02228104
	push {r4, r5}
	sub sp, #0x18
	ldr r3, _0222813C ; =0x0222D004
	add r2, sp, #0
	add r5, r0, #0
	add r4, r2, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	mov r0, #0
	add r2, r0, #0
_02228120:
	ldr r1, [r4]
	cmp r5, r1
	bne _0222812E
	add sp, #0x18
	mov r0, #1
	pop {r4, r5}
	bx lr
_0222812E:
	add r2, r2, #1
	add r4, r4, #4
	cmp r2, #6
	blo _02228120
	add sp, #0x18
	pop {r4, r5}
	bx lr
	.align 2, 0
_0222813C: .word MOD8_0222D004

	thumb_func_start MOD08_02228140
MOD08_02228140: ; 0x02228140
	push {r3, r4, r5}
	sub sp, #0xc
	ldr r5, _02228174 ; =0x0222CFF8
	add r3, r0, #0
	ldmia r5!, {r0, r1}
	add r4, sp, #0
	add r2, r4, #0
	stmia r4!, {r0, r1}
	ldr r0, [r5]
	str r0, [r4]
	mov r0, #1
	mov r4, #0
_02228158:
	ldr r1, [r2]
	cmp r3, r1
	bne _02228166
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, r5}
	bx lr
_02228166:
	add r4, r4, #1
	add r2, r2, #4
	cmp r4, #3
	blo _02228158
	add sp, #0xc
	pop {r3, r4, r5}
	bx lr
	.align 2, 0
_02228174: .word MOD8_0222CFF8

	thumb_func_start MOD08_02228178
MOD08_02228178: ; 0x02228178
	push {r3, lr}
	bl MOD08_022280A8
	lsl r1, r0, #3
	ldr r0, _02228188 ; =0x0222D208
	ldr r0, [r0, r1]
	pop {r3, pc}
	nop
_02228188: .word MOD8_0222D208

	thumb_func_start MOD08_0222818C
MOD08_0222818C: ; 0x0222818C
	push {r3, lr}
	bl MOD08_022280A8
	lsl r1, r0, #3
	ldr r0, _0222819C ; =0x0222D20C
	ldr r0, [r0, r1]
	pop {r3, pc}
	nop
_0222819C: .word MOD8_0222D20C

	thumb_func_start MOD08_022281A0
MOD08_022281A0: ; 0x022281A0
	push {r3, lr}
	bl MOD08_022280A8
	mov r1, #0xc
	mul r1, r0
	ldr r0, _022281B0 ; =0x0222D2A8
	ldr r0, [r0, r1]
	pop {r3, pc}
	.align 2, 0
_022281B0: .word MOD8_0222D2A8

	thumb_func_start MOD08_022281B4
MOD08_022281B4: ; 0x022281B4
	push {r3, lr}
	bl MOD08_022280A8
	mov r1, #0xc
	mul r1, r0
	ldr r0, _022281C4 ; =0x0222D2B0
	ldr r0, [r0, r1]
	pop {r3, pc}
	.align 2, 0
_022281C4: .word MOD8_0222D2B0

	thumb_func_start MOD08_022281C8
MOD08_022281C8: ; 0x022281C8
	push {r3, lr}
	bl MOD08_022280A8
	mov r1, #0xc
	mul r1, r0
	ldr r0, _022281D8 ; =0x0222D2AC
	ldr r0, [r0, r1]
	pop {r3, pc}
	.align 2, 0
_022281D8: .word MOD8_0222D2AC

	thumb_func_start MOD08_022281DC
MOD08_022281DC: ; 0x022281DC
	push {r4, lr}
	add r4, r1, #0
	bl MOD08_022280A8
	lsl r2, r0, #4
	ldr r0, _022281F0 ; =0x0222D398
	lsl r1, r4, #2
	add r0, r0, r2
	ldr r0, [r1, r0]
	pop {r4, pc}
	.align 2, 0
_022281F0: .word MOD8_0222D398

	thumb_func_start MOD08_022281F4
MOD08_022281F4: ; 0x022281F4
	push {r4, lr}
	mov r1, #0xb8
	add r4, r0, #0
	bl AllocFromHeap
	cmp r0, #0
	bne _0222820A
	bl ErrorHandling
	mov r0, #0
	pop {r4, pc}
_0222820A:
	add r1, r0, #0
	str r4, [r0]
	mov r2, #0
	add r1, #0x88
	str r2, [r1]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02228218
MOD08_02228218: ; 0x02228218
	push {r3, r4, r5, lr}
	add r5, r1, #0
	bl MOD08_022281F4
	add r1, r5, #0
	add r4, r0, #0
	bl MOD08_02228244
	mov r1, #0
	str r1, [r4, #0x10]
	add r2, r4, #0
	add r0, r1, #0
_02228230:
	str r0, [r2, #0x14]
	str r0, [r2, #0x38]
	str r0, [r2, #0x5c]
	add r1, r1, #1
	add r2, r2, #4
	cmp r1, #9
	blt _02228230
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_02228244
MOD08_02228244: ; 0x02228244
	push {r4, lr}
	add r3, r1, #0
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, r4, #4
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, #0xa1
	str r0, [r2]
	ldr r0, [r4, #0xc]
	mov r2, #0
	bl GetMonData
	add r1, r4, #0
	add r1, #0x9c
	str r0, [r1]
	add r0, r4, #0
	add r0, #0x9c
	ldr r0, [r0]
	cmp r0, #0xd
	blt _02228272
	bl ErrorHandling
_02228272:
	add r0, r4, #0
	add r0, #0x9c
	ldr r0, [r0]
	cmp r0, #0
	bne _0222829E
	add r0, r4, #0
	mov r2, #0
	add r0, #0x94
	str r2, [r0]
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _02228290
	add r4, #0x98
	str r0, [r4]
	pop {r4, pc}
_02228290:
	ldr r0, [r4, #0xc]
	mov r1, #0x9a
	bl GetMonData
	add r4, #0x98
	str r0, [r4]
	pop {r4, pc}
_0222829E:
	add r0, r4, #0
	mov r1, #1
	add r0, #0x94
	str r1, [r0]
	ldr r0, [r4, #0xc]
	add r4, #0xa0
	mov r1, #0xaa
	add r2, r4, #0
	bl GetMonData
	pop {r4, pc}

	thumb_func_start MOD08_022282B4
MOD08_022282B4: ; 0x022282B4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r4, r1, #0
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	cmp r0, #3
	bls _022282C8
	b _02228520
_022282C8:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022282D4: ; jump table
	.short _022282DC - _022282D4 - 2 ; case 0
	.short _02228376 - _022282D4 - 2 ; case 1
	.short _02228402 - _022282D4 - 2 ; case 2
	.short _0222848E - _022282D4 - 2 ; case 3
_022282DC:
	ldr r1, [r4]
	mov r0, #0x63
	bl NARC_ctor
	add r1, r4, #0
	add r1, #0x8c
	str r0, [r1]
	add r0, r4, #0
	add r6, r4, #0
	str r0, [sp, #0x14]
	add r0, #0xa0
	mov r5, #0
	add r6, #0x10
	str r0, [sp, #0x14]
_022282F8:
	ldr r0, [sp, #0x14]
	add r1, r5, #0
	bl Capsule_GetSealI
	add r7, r0, #0
	beq _02228360
	bl Seal_GetId
	cmp r0, #0
	beq _02228360
	cmp r0, #0x51
	bge _02228360
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02085FF4
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x10]
	lsl r0, r0, #2
	add r0, r4, r0
	str r7, [r0, #0x38]
	ldr r0, [r4, #0x10]
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #0x14]
	cmp r0, #0
	beq _02228332
	bl ErrorHandling
_02228332:
	add r0, r4, #0
	add r0, #0x8c
	ldr r0, [r0]
	ldr r1, [r4]
	ldr r2, [sp, #0x10]
	mov r3, #0
	bl MOD08_02215B00
	ldr r1, [r4, #0x10]
	lsl r1, r1, #2
	add r1, r4, r1
	str r0, [r1, #0x14]
	ldr r0, [r4, #0x10]
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #0x14]
	cmp r0, #0
	bne _0222835A
	bl ErrorHandling
_0222835A:
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
_02228360:
	add r5, r5, #1
	cmp r5, #2
	blt _022282F8
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	add r4, #0x90
	add r0, r0, #1
	add sp, #0x24
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_02228376:
	add r0, r4, #0
	add r6, r4, #0
	str r0, [sp, #0x18]
	add r0, #0xa0
	mov r5, #2
	add r6, #0x10
	str r0, [sp, #0x18]
_02228384:
	ldr r0, [sp, #0x18]
	add r1, r5, #0
	bl Capsule_GetSealI
	add r7, r0, #0
	beq _022283EC
	bl Seal_GetId
	cmp r0, #0
	beq _022283EC
	cmp r0, #0x51
	bge _022283EC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02085FF4
	str r0, [sp, #4]
	ldr r0, [r4, #0x10]
	lsl r0, r0, #2
	add r0, r4, r0
	str r7, [r0, #0x38]
	ldr r0, [r4, #0x10]
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #0x14]
	cmp r0, #0
	beq _022283BE
	bl ErrorHandling
_022283BE:
	add r0, r4, #0
	add r0, #0x8c
	ldr r0, [r0]
	ldr r1, [r4]
	ldr r2, [sp, #4]
	mov r3, #0
	bl MOD08_02215B00
	ldr r1, [r4, #0x10]
	lsl r1, r1, #2
	add r1, r4, r1
	str r0, [r1, #0x14]
	ldr r0, [r4, #0x10]
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #0x14]
	cmp r0, #0
	bne _022283E6
	bl ErrorHandling
_022283E6:
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
_022283EC:
	add r5, r5, #1
	cmp r5, #4
	blt _02228384
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	add r4, #0x90
	add r0, r0, #1
	add sp, #0x24
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_02228402:
	add r0, r4, #0
	add r6, r4, #0
	str r0, [sp, #0x1c]
	add r0, #0xa0
	mov r5, #4
	add r6, #0x10
	str r0, [sp, #0x1c]
_02228410:
	ldr r0, [sp, #0x1c]
	add r1, r5, #0
	bl Capsule_GetSealI
	add r7, r0, #0
	beq _02228478
	bl Seal_GetId
	cmp r0, #0
	beq _02228478
	cmp r0, #0x51
	bge _02228478
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02085FF4
	str r0, [sp, #8]
	ldr r0, [r4, #0x10]
	lsl r0, r0, #2
	add r0, r4, r0
	str r7, [r0, #0x38]
	ldr r0, [r4, #0x10]
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #0x14]
	cmp r0, #0
	beq _0222844A
	bl ErrorHandling
_0222844A:
	add r0, r4, #0
	add r0, #0x8c
	ldr r0, [r0]
	ldr r1, [r4]
	ldr r2, [sp, #8]
	mov r3, #0
	bl MOD08_02215B00
	ldr r1, [r4, #0x10]
	lsl r1, r1, #2
	add r1, r4, r1
	str r0, [r1, #0x14]
	ldr r0, [r4, #0x10]
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #0x14]
	cmp r0, #0
	bne _02228472
	bl ErrorHandling
_02228472:
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
_02228478:
	add r5, r5, #1
	cmp r5, #6
	blt _02228410
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	add r4, #0x90
	add r0, r0, #1
	add sp, #0x24
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0222848E:
	add r0, r4, #0
	add r6, r4, #0
	str r0, [sp, #0x20]
	add r0, #0xa0
	mov r5, #6
	add r6, #0x10
	str r0, [sp, #0x20]
_0222849C:
	ldr r0, [sp, #0x20]
	add r1, r5, #0
	bl Capsule_GetSealI
	add r7, r0, #0
	beq _02228504
	bl Seal_GetId
	cmp r0, #0
	beq _02228504
	cmp r0, #0x51
	bge _02228504
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02085FF4
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x10]
	lsl r0, r0, #2
	add r0, r4, r0
	str r7, [r0, #0x38]
	ldr r0, [r4, #0x10]
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #0x14]
	cmp r0, #0
	beq _022284D6
	bl ErrorHandling
_022284D6:
	add r0, r4, #0
	add r0, #0x8c
	ldr r0, [r0]
	ldr r1, [r4]
	ldr r2, [sp, #0xc]
	mov r3, #0
	bl MOD08_02215B00
	ldr r1, [r4, #0x10]
	lsl r1, r1, #2
	add r1, r4, r1
	str r0, [r1, #0x14]
	ldr r0, [r4, #0x10]
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #0x14]
	cmp r0, #0
	bne _022284FE
	bl ErrorHandling
_022284FE:
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
_02228504:
	add r5, r5, #1
	cmp r5, #8
	blt _0222849C
	add r0, r4, #0
	mov r1, #0xff
	add r0, #0x90
	add r4, #0x8c
	str r1, [r0]
	ldr r0, [r4]
	bl NARC_dtor
	ldr r0, [sp]
	bl FUN_0200CAB4
_02228520:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02228524
MOD08_02228524: ; 0x02228524
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x94
	ldr r0, [r0]
	cmp r0, #0
	bne _0222854E
	add r0, r4, #0
	add r0, #0x98
	ldr r0, [r0]
	bl MOD08_02228178
	add r2, r0, #0
	mov r0, #1
	str r0, [r4, #0x10]
	ldr r0, [r4]
	mov r1, #0x63
	mov r3, #0
	bl MOD08_02215ACC
	str r0, [r4, #0x14]
	pop {r4, pc}
_0222854E:
	mov r1, #0
	add r0, r4, #0
	mov r2, #0xfa
	str r1, [r4, #0x10]
	add r0, #0x90
	str r1, [r0]
	ldr r0, _0222856C ; =MOD08_022282B4
	add r1, r4, #0
	lsl r2, r2, #2
	bl FUN_0200CA44
	add r1, r4, #0
	bl MOD08_022282B4
	pop {r4, pc}
	.align 2, 0
_0222856C: .word MOD08_022282B4

	thumb_func_start MOD08_02228570
MOD08_02228570: ; 0x02228570
	mov r0, #1
	bx lr

	thumb_func_start MOD08_02228574
MOD08_02228574: ; 0x02228574
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r1, #1
	add r0, #0x88
	str r1, [r0]
	bl MOD08_0221268C
	add r0, r5, #0
	add r1, r4, #0
	bl MOD08_0222865C
	mov r2, #0xfa
	ldr r0, _022285A0 ; =MOD08_022285BC
	add r1, r5, #0
	lsl r2, r2, #2
	bl FUN_0200CA44
	add r5, #0x84
	str r0, [r5]
	pop {r3, r4, r5, pc}
	nop
_022285A0: .word MOD08_022285BC

	thumb_func_start MOD08_022285A4
MOD08_022285A4: ; 0x022285A4
	ldr r3, _022285AC ; =MOD08_02228574
	ldr r1, _022285B0 ; =MOD08_02228788
	bx r3
	nop
_022285AC: .word MOD08_02228574
_022285B0: .word MOD08_02228788

	thumb_func_start MOD08_022285B4
MOD08_022285B4: ; 0x022285B4
	add r0, #0x88
	ldr r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_022285BC
MOD08_022285BC: ; 0x022285BC
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	str r0, [sp]
	ldr r0, [r6, #0x10]
	mov r7, #0
	cmp r0, #9
	ble _022285CE
	bl ErrorHandling
_022285CE:
	ldr r0, [r6, #0x10]
	mov r4, #0
	cmp r0, #0
	ble _02228606
	add r5, r6, #0
_022285D8:
	ldr r0, [r5, #0x14]
	cmp r0, #0
	beq _022285FC
	bl FUN_020133C8
	cmp r0, #0
	bne _022285FA
	ldr r0, [r5, #0x5c]
	cmp r0, #0
	beq _022285FA
	ldr r0, [r5, #0x14]
	bl MOD08_02215B40
	mov r0, #0
	str r0, [r5, #0x14]
	str r0, [r5, #0x5c]
	b _022285FC
_022285FA:
	mov r7, #1
_022285FC:
	ldr r0, [r6, #0x10]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blt _022285D8
_02228606:
	cmp r7, #0
	bne _02228616
	mov r0, #0
	add r6, #0x88
	str r0, [r6]
	ldr r0, [sp]
	bl FUN_0200CAB4
_02228616:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_02228618
MOD08_02228618: ; 0x02228618
	ldr r3, _0222861C ; =FreeToHeap
	bx r3
	.align 2, 0
_0222861C: .word FreeToHeap

	thumb_func_start MOD08_02228620
MOD08_02228620: ; 0x02228620
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _02228654
	ldr r0, [r4, #0xc]
	mov r1, #1
	str r1, [r0]
	ldr r0, [r4, #0x10]
	ldr r2, [r4, #0x18]
	mov r1, #0
	add r3, r4, #0
	bl FUN_020133AC
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_02013440
	add r0, r5, #0
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
_02228654:
	sub r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_0222865C
MOD08_0222865C: ; 0x0222865C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r0, #0x94
	ldr r0, [r0]
	add r7, r1, #0
	cmp r0, #0
	bne _0222869A
	add r0, r6, #0
	add r0, #0x98
	ldr r0, [r0]
	bl MOD08_0222818C
	add r5, r0, #0
	mov r4, #0
	cmp r5, #0
	ble _0222868E
_0222867C:
	ldr r0, [r6, #0x14]
	add r1, r4, #0
	add r2, r7, #0
	add r3, r6, #0
	bl FUN_020133AC
	add r4, r4, #1
	cmp r4, r5
	blt _0222867C
_0222868E:
	mov r1, #1
	str r1, [r6, #0x5c]
	ldr r0, [r6, #0x14]
	bl FUN_02013440
	pop {r3, r4, r5, r6, r7, pc}
_0222869A:
	ldr r0, [r6, #0x10]
	mov r7, #0
	cmp r0, #0
	ble _02228700
	add r0, r6, #0
	str r0, [sp]
	add r0, #0x5c
	add r5, r6, #0
	str r0, [sp]
_022286AC:
	ldr r0, [r6]
	mov r1, #0x1c
	bl AllocFromHeap
	add r4, r0, #0
	bne _022286BC
	bl ErrorHandling
_022286BC:
	str r7, [r4]
	ldr r0, [r6, #4]
	str r0, [r4, #8]
	ldr r0, _02228704 ; =MOD08_022287C4
	str r0, [r4, #0x18]
	mov r0, #0
	str r0, [r5, #0x5c]
	ldr r0, [sp]
	str r0, [r4, #0xc]
	ldr r0, [r5, #0x14]
	str r0, [r4, #0x10]
	ldr r0, [r5, #0x38]
	str r0, [r4, #0x14]
	cmp r0, #0
	bne _022286DE
	bl ErrorHandling
_022286DE:
	ldr r0, [r4, #0x14]
	bl MOD08_0222A078
	str r0, [r4, #4]
	ldr r0, _02228708 ; =MOD08_02228620
	ldr r2, _0222870C ; =0x000003E9
	add r1, r4, #0
	bl FUN_0200CA44
	ldr r0, [sp]
	add r7, r7, #1
	add r0, r0, #4
	str r0, [sp]
	ldr r0, [r6, #0x10]
	add r5, r5, #4
	cmp r7, r0
	blt _022286AC
_02228700:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02228704: .word MOD08_022287C4
_02228708: .word MOD08_02228620
_0222870C: .word 0x000003E9

	thumb_func_start MOD08_02228710
MOD08_02228710: ; 0x02228710
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r3, #1
	add r5, r0, #0
	add r4, r1, #0
	bl MOD08_0222796C
	cmp r5, #5
	bhi _02228766
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222872E: ; jump table
	.short _0222873A - _0222872E - 2 ; case 0
	.short _02228742 - _0222872E - 2 ; case 1
	.short _0222874C - _0222872E - 2 ; case 2
	.short _02228754 - _0222872E - 2 ; case 3
	.short _0222875E - _0222872E - 2 ; case 4
	.short _02228766 - _0222872E - 2 ; case 5
_0222873A:
	mov r5, #0
	add r0, r5, #0
	sub r0, #0x10
	b _0222876E
_02228742:
	mov r5, #0xe
	mvn r5, r5
	add r0, r5, #0
	sub r0, #0xa
	b _0222876E
_0222874C:
	mov r5, #7
	mvn r5, r5
	sub r0, r5, #4
	b _0222876E
_02228754:
	mov r5, #0xd
	mvn r5, r5
	add r0, r5, #0
	sub r0, #0xb
	b _0222876E
_0222875E:
	mov r5, #7
	mvn r5, r5
	sub r0, r5, #4
	b _0222876E
_02228766:
	mov r5, #0xf
	mvn r5, r5
	add r0, r5, #0
	sub r0, #0xd
_0222876E:
	add r5, #0xa
	ldr r3, [r4]
	mov r1, #0xac
	add r2, r5, #0
	mul r2, r1
	sub r2, r3, r2
	str r2, [r4]
	add r0, #0x20
	ldr r2, [r4, #4]
	mul r1, r0
	sub r0, r2, r1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02228788
MOD08_02228788: ; 0x02228788
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl FUN_0201341C
	ldr r0, [r0, #4]
	add r1, sp, #0
	bl MOD08_02228710
	ldr r0, [r4, #0x20]
	ldr r1, [sp]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	add r0, r1, r0
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x20]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r1, r0
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x20]
	ldr r1, [sp, #8]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	add r0, r1, r0
	str r0, [r4, #0x30]
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD08_022287C4
MOD08_022287C4: ; 0x022287C4
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	bl FUN_0201341C
	add r4, r0, #0
	ldr r0, [r4, #8]
	add r1, sp, #0
	bl MOD08_02228710
	ldr r0, [r4, #0x14]
	bl Seal_GetId
	bl FUN_02086018
	ldr r0, [r4, #0x14]
	bl Seal_GetXCoord
	add r6, r0, #0
	ldr r0, [r4, #0x14]
	bl Seal_GetYCoord
	sub r6, #0xbe
	lsl r1, r6, #0x10
	asr r3, r1, #0x10
	ldr r2, [sp]
	mov r1, #0xac
	add r4, r3, #0
	mul r4, r1
	add r3, r2, r4
	mov r4, #0x64
	sub r0, r4, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	ldr r2, [sp, #4]
	mul r1, r0
	add r0, r2, r1
	str r3, [sp]
	str r0, [sp, #4]
	ldr r0, [r5, #0x20]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	add r0, r3, r0
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r1, r0
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #8]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	add r0, r1, r0
	str r0, [r5, #0x30]
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}

	thumb_func_start MOD08_02228838
MOD08_02228838: ; 0x02228838
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0201341C
	mov r1, #2
	ldrsh r2, [r0, r1]
	mov r1, #0x64
	mov r3, #0xac
	sub r1, r1, r2
	lsl r1, r1, #0x10
	asr r2, r1, #0x10
	add r1, r2, #0
	mov r2, #0
	ldrsh r0, [r0, r2]
	mul r1, r3
	sub r0, #0x81
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r2, r0, #0
	ldr r0, [r4, #0x20]
	mul r2, r3
	ldr r0, [r0]
	ldr r0, [r0, #4]
	add r0, r2, r0
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x20]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r1, r0
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x20]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x30]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02228880
MOD08_02228880: ; 0x02228880
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #8]
	mov r1, #0x24
	bl AllocFromHeap
	add r4, r0, #0
	bne _02228894
	bl ErrorHandling
_02228894:
	ldmia r5!, {r0, r1}
	add r2, r4, #0
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r5]
	str r0, [r2]
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _022288B8
	ldr r0, _022288DC ; =0x00000113
	bl MOD08_022281A0
	str r0, [r4, #0x20]
	ldr r0, _022288DC ; =0x00000113
	bl MOD08_022281B4
	b _022288C6
_022288B8:
	ldr r0, [r4, #4]
	bl MOD08_022281A0
	str r0, [r4, #0x20]
	ldr r0, [r4, #4]
	bl MOD08_022281B4
_022288C6:
	str r0, [r4, #0x1c]
	ldr r0, [r4, #8]
	ldr r2, [r4, #0x20]
	mov r1, #0x63
	mov r3, #0
	bl MOD08_02215ACC
	str r0, [r4, #0x18]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_022288DC: .word 0x00000113

	thumb_func_start MOD08_022288E0
MOD08_022288E0: ; 0x022288E0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r1, [r5, #0xc]
	cmp r1, #0xff
	bne _0222893A
	ldr r0, [r5, #0x10]
	cmp r0, #0
	beq _02228910
	ldr r0, [r5, #0x1c]
	mov r4, #0
	cmp r0, #0
	ble _02228944
	ldr r6, _02228950 ; =MOD08_02228838
_022288FA:
	ldr r0, [r5, #0x18]
	add r1, r4, #0
	add r2, r6, #0
	add r3, r5, #0
	bl FUN_020133AC
	ldr r0, [r5, #0x1c]
	add r4, r4, #1
	cmp r4, r0
	blt _022288FA
	b _02228944
_02228910:
	ldr r0, [r5, #0x1c]
	mov r4, #0
	cmp r0, #0
	ble _02228944
	ldr r6, _02228950 ; =MOD08_02228838
_0222891A:
	ldr r0, [r5, #4]
	bl MOD08_022281C8
	cmp r4, r0
	beq _02228930
	ldr r0, [r5, #0x18]
	add r1, r4, #0
	add r2, r6, #0
	add r3, r5, #0
	bl FUN_020133AC
_02228930:
	ldr r0, [r5, #0x1c]
	add r4, r4, #1
	cmp r4, r0
	blt _0222891A
	b _02228944
_0222893A:
	ldr r0, [r5, #0x18]
	ldr r2, _02228950 ; =MOD08_02228838
	add r3, r5, #0
	bl FUN_020133AC
_02228944:
	ldr r0, [r5, #0x18]
	mov r1, #1
	bl FUN_02013440
	pop {r4, r5, r6, pc}
	nop
_02228950: .word MOD08_02228838

	thumb_func_start MOD08_02228954
MOD08_02228954: ; 0x02228954
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	bl FUN_020133C8
	cmp r0, #0
	bne _0222896C
	ldr r0, [r4, #0x18]
	bl MOD08_02215B40
	mov r0, #0
	pop {r4, pc}
_0222896C:
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD08_02228970
MOD08_02228970: ; 0x02228970
	ldr r3, _02228974 ; =FreeToHeap
	bx r3
	.align 2, 0
_02228974: .word FreeToHeap

	thumb_func_start MOD08_02228978
MOD08_02228978: ; 0x02228978
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	bne _0222898C
	add r1, r1, #1
	str r1, [r4, #4]
	mov r1, #1
	bl MOD08_02229A18
_0222898C:
	add r0, r4, #0
	mov r1, #2
	bl MOD08_02229A1C
	cmp r0, #1
	bne _0222899C
	mov r0, #0
	pop {r4, pc}
_0222899C:
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD08_022289A0
MOD08_022289A0: ; 0x022289A0
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	bne _022289B4
	add r1, r1, #1
	str r1, [r4, #4]
	mov r1, #3
	bl MOD08_02229A18
_022289B4:
	add r0, r4, #0
	mov r1, #4
	bl MOD08_02229A1C
	cmp r0, #1
	bne _022289C4
	mov r0, #0
	pop {r4, pc}
_022289C4:
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD08_022289C8
MOD08_022289C8: ; 0x022289C8
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	bne _022289DC
	add r1, r1, #1
	str r1, [r4, #4]
	mov r1, #5
	bl MOD08_02229A18
_022289DC:
	add r0, r4, #0
	mov r1, #6
	bl MOD08_02229A1C
	cmp r0, #1
	bne _022289EC
	mov r0, #0
	pop {r4, pc}
_022289EC:
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD08_022289F0
MOD08_022289F0: ; 0x022289F0
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	bne _02228A04
	add r1, r1, #1
	str r1, [r4, #4]
	mov r1, #7
	bl MOD08_02229A18
_02228A04:
	add r0, r4, #0
	mov r1, #0xe
	bl MOD08_02229A1C
	cmp r0, #1
	bne _02228A14
	mov r0, #0
	pop {r4, pc}
_02228A14:
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD08_02228A18
MOD08_02228A18: ; 0x02228A18
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	bne _02228A2C
	add r1, r1, #1
	str r1, [r4, #4]
	mov r1, #0xf
	bl MOD08_02229A18
_02228A2C:
	add r0, r4, #0
	mov r1, #0x12
	bl MOD08_02229A1C
	cmp r0, #1
	bne _02228A3C
	mov r0, #0
	pop {r4, pc}
_02228A3C:
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD08_02228A40
MOD08_02228A40: ; 0x02228A40
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	bne _02228A54
	add r1, r1, #1
	str r1, [r4, #4]
	mov r1, #0x13
	bl MOD08_02229A18
_02228A54:
	add r0, r4, #0
	mov r1, #0x1b
	bl MOD08_02229A1C
	cmp r0, #1
	bne _02228A64
	mov r0, #0
	pop {r4, pc}
_02228A64:
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD08_02228A68
MOD08_02228A68: ; 0x02228A68
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	bne _02228A7C
	add r1, r1, #1
	str r1, [r4, #4]
	mov r1, #0x15
	bl MOD08_02229A18
_02228A7C:
	add r0, r4, #0
	mov r1, #0x16
	bl MOD08_02229A1C
	cmp r0, #1
	bne _02228A8C
	mov r0, #0
	pop {r4, pc}
_02228A8C:
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD08_02228A90
MOD08_02228A90: ; 0x02228A90
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	bne _02228AA4
	add r1, r1, #1
	str r1, [r4, #4]
	mov r1, #0x17
	bl MOD08_02229A18
_02228AA4:
	add r0, r4, #0
	mov r1, #0x1b
	bl MOD08_02229A1C
	cmp r0, #1
	bne _02228AB4
	mov r0, #0
	pop {r4, pc}
_02228AB4:
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD08_02228AB8
MOD08_02228AB8: ; 0x02228AB8
	str r1, [r0]
	mov r1, #0
	str r1, [r0, #4]
	bx lr

	thumb_func_start MOD08_02228AC0
MOD08_02228AC0: ; 0x02228AC0
	push {r3, lr}
	ldr r1, [r0]
	lsl r2, r1, #2
	ldr r1, _02228AD0 ; =0x0222D034
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	nop
_02228AD0: .word MOD8_0222D034

	thumb_func_start MOD08_02228AD4
MOD08_02228AD4: ; 0x02228AD4
	str r1, [r0, #0x14]
	mov r1, #0
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	str r1, [r0, #0x10]
	bx lr

	thumb_func_start MOD08_02228AE0
MOD08_02228AE0: ; 0x02228AE0
	mov r0, #1
	bx lr

	thumb_func_start MOD08_02228AE4
MOD08_02228AE4: ; 0x02228AE4
	push {r4, lr}
	add r4, r0, #0
	bl MOD08_02229114
	cmp r0, #0
	bne _02228AF8
	add r0, r4, #0
	mov r1, #2
	bl MOD08_02228AD4
_02228AF8:
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD08_02228AFC
MOD08_02228AFC: ; 0x02228AFC
	push {r3, lr}
	mov r1, #3
	bl MOD08_02228AD4
	mov r0, #1
	pop {r3, pc}

	thumb_func_start MOD08_02228B08
MOD08_02228B08: ; 0x02228B08
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #3
	bhi _02228BD8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02228B20: ; jump table
	.short _02228B28 - _02228B20 - 2 ; case 0
	.short _02228B7E - _02228B20 - 2 ; case 1
	.short _02228B94 - _02228B20 - 2 ; case 2
	.short _02228BB0 - _02228B20 - 2 ; case 3
_02228B28:
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl FUN_0200C5C0
	add r0, r4, #0
	add r0, #0xa0
	ldr r0, [r0]
	add r2, sp, #0
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x94
	ldr r0, [r0]
	add r1, sp, #0
	str r0, [sp, #8]
	mov r0, #0xff
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x30]
	add r2, #2
	bl FUN_0200C7A0
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xb4
	add r1, #0x94
	ldr r0, [r0]
	ldr r1, [r1]
	bl MOD08_0221590C
	add r1, r4, #0
	add r1, #0xd8
	str r0, [r1]
	add r0, sp, #0
	bl MOD08_02228880
	add r1, r4, #0
	add r1, #0xd0
	str r0, [r1]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02228BE0
_02228B7E:
	ldr r0, [r4, #0x30]
	bl FUN_0200C630
	cmp r0, #2
	blt _02228BE0
	mov r0, #0
	str r0, [r4, #0x24]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02228BE0
_02228B94:
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	bl MOD08_022288E0
	add r0, r4, #0
	add r0, #0xd8
	ldr r0, [r0]
	bl MOD08_02215918
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02228BE0
_02228BB0:
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	bl MOD08_02228954
	cmp r0, #0
	bne _02228BE0
	ldr r0, [r4, #0x30]
	mov r1, #0
	bl FUN_0200C61C
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	bl MOD08_02228970
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02228BE0
_02228BD8:
	add r0, r4, #0
	mov r1, #4
	bl MOD08_02228AD4
_02228BE0:
	mov r0, #1
	add sp, #0x14
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02228BE8
MOD08_02228BE8: ; 0x02228BE8
	mov r0, #1
	bx lr

	thumb_func_start MOD08_02228BEC
MOD08_02228BEC: ; 0x02228BEC
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0xc]
	cmp r1, #0
	bne _02228C2C
	add r1, r4, #0
	add r2, r4, #0
	ldr r0, [r4, #0x30]
	add r1, #0xb8
	add r2, #0xba
	bl FUN_0200C7A0
	add r0, r4, #0
	mov r1, #0x3c
	add r0, #0xbc
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0xb4
	add r0, #0xbe
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0xa
	add r0, #0xc0
	str r1, [r0]
	add r0, r4, #0
	mov r1, #0xc
	add r0, #0xc8
	str r1, [r0]
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02228C3C
_02228C2C:
	bl MOD08_02229114
	cmp r0, #0
	bne _02228C3C
	add r0, r4, #0
	mov r1, #6
	bl MOD08_02228AD4
_02228C3C:
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD08_02228C40
MOD08_02228C40: ; 0x02228C40
	mov r0, #1
	bx lr

	thumb_func_start MOD08_02228C44
MOD08_02228C44: ; 0x02228C44
	push {r3, lr}
	mov r1, #8
	bl MOD08_02228AD4
	mov r0, #1
	pop {r3, pc}

	thumb_func_start MOD08_02228C50
MOD08_02228C50: ; 0x02228C50
	push {r3, lr}
	mov r1, #9
	bl MOD08_02228AD4
	mov r0, #1
	pop {r3, pc}

	thumb_func_start MOD08_02228C5C
MOD08_02228C5C: ; 0x02228C5C
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _02228C6E
	cmp r0, #1
	beq _02228CA2
	b _02228CE4
_02228C6E:
	ldr r0, [r4, #0x30]
	bl FUN_0200C68C
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0xc
	str r0, [sp, #4]
	ldr r0, _02228D00 ; =0x0000037F
	mov r3, #1
	add r5, r3, #0
	str r0, [sp, #8]
	add r0, r4, #0
	lsl r5, r2
	add r0, #0xb0
	lsl r2, r5, #0x10
	ldr r0, [r0]
	mov r1, #4
	lsr r2, r2, #0x10
	sub r3, r3, #2
	bl FUN_02003210
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02228CFA
_02228CA2:
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	bne _02228CFA
	ldr r0, [r4, #0x30]
	bl FUN_0200C68C
	add r2, r0, #0
	mov r0, #0xc
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _02228D00 ; =0x0000037F
	mov r3, #1
	add r5, r3, #0
	str r0, [sp, #8]
	add r0, r4, #0
	lsl r5, r2
	add r0, #0xb0
	lsl r2, r5, #0x10
	ldr r0, [r0]
	mov r1, #4
	lsr r2, r2, #0x10
	sub r3, r3, #2
	bl FUN_02003210
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02228CFA
_02228CE4:
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	bne _02228CFA
	add r0, r4, #0
	mov r1, #0xa
	bl MOD08_02228AD4
_02228CFA:
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02228D00: .word 0x0000037F

	thumb_func_start MOD08_02228D04
MOD08_02228D04: ; 0x02228D04
	push {r3, lr}
	mov r1, #0xb
	bl MOD08_02228AD4
	mov r0, #1
	pop {r3, pc}

	thumb_func_start MOD08_02228D10
MOD08_02228D10: ; 0x02228D10
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _02228D22
	cmp r0, #1
	beq _02228D62
	b _02228D7E
_02228D22:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	cmp r0, #1
	blt _02228D7E
	add r1, sp, #8
	ldr r0, [r4, #0x30]
	add r1, #2
	add r2, sp, #8
	bl FUN_0200C7A0
	add r1, sp, #8
	mov r0, #0
	ldrsh r3, [r1, r0]
	mov r0, #2
	ldrsh r1, [r1, r0]
	add r0, r3, #0
	add r0, #0x20
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x48
	add r2, r1, #0
	bl MOD08_02217E80
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02228D7E
_02228D62:
	add r0, r4, #0
	ldr r1, [r4, #0x30]
	add r0, #0x48
	bl MOD08_02217F08
	cmp r0, #0
	bne _02228D7E
	ldr r0, [r4, #8]
	mov r1, #0xd
	add r0, r0, #1
	str r0, [r4, #8]
	add r0, r4, #0
	bl MOD08_02228AD4
_02228D7E:
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start MOD08_02228D84
MOD08_02228D84: ; 0x02228D84
	mov r0, #1
	bx lr

	thumb_func_start MOD08_02228D88
MOD08_02228D88: ; 0x02228D88
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r1, [r5, #8]
	cmp r1, #0
	beq _02228D98
	cmp r1, #1
	beq _02228DAE
	b _02228E0E
_02228D98:
	ldr r0, [r5, #0x30]
	mov r1, #1
	bl FUN_0200C5C0
	ldr r0, [r5, #0x30]
	mov r1, #0
	bl FUN_0200C61C
	ldr r0, [r5, #8]
	add r0, r0, #1
	str r0, [r5, #8]
_02228DAE:
	ldr r1, [r5, #0xc]
	mov r0, #6
	add r2, r1, #0
	mul r2, r0
	ldr r0, _02228E18 ; =0x0222D18A
	ldr r1, _02228E1C ; =0x0222D18C
	ldrsh r0, [r0, r2]
	ldrh r1, [r1, r2]
	str r0, [sp]
	ldr r0, [r5, #0x30]
	bl FUN_0200C61C
	ldr r0, [r5, #0xc]
	ldr r4, _02228E20 ; =0x0222D07C
	add r0, r0, #1
	str r0, [r5, #0xc]
	mov r6, #0
	mov r7, #0x75
_02228DD2:
	ldr r1, [r5, #0xc]
	ldr r0, [r4]
	cmp r1, r0
	bne _02228DE6
	ldr r0, [r4, #4]
	add r1, r7, #0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_020054A8
_02228DE6:
	add r6, r6, #1
	add r4, #8
	cmp r6, #5
	blt _02228DD2
	ldr r0, [r5, #0xc]
	cmp r0, #0x14
	bgt _02228DFA
	ldr r0, [sp]
	cmp r0, #0xff
	bne _02228E02
_02228DFA:
	ldr r0, [r5, #8]
	add r0, r0, #1
	str r0, [r5, #8]
	b _02228E14
_02228E02:
	ldr r0, [r5, #0x30]
	ldr r2, [sp]
	mov r1, #0
	bl FUN_0200C82C
	b _02228E14
_02228E0E:
	mov r1, #0xe
	bl MOD08_02228AD4
_02228E14:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02228E18: .word MOD8_0222D18A
_02228E1C: .word MOD8_0222D18C
_02228E20: .word MOD8_0222D07C

	thumb_func_start MOD08_02228E24
MOD08_02228E24: ; 0x02228E24
	mov r0, #1
	bx lr

	thumb_func_start MOD08_02228E28
MOD08_02228E28: ; 0x02228E28
	push {r3, lr}
	ldr r1, [r0, #0xc]
	add r1, r1, #1
	str r1, [r0, #0xc]
	cmp r1, #0xe
	blt _02228E44
	ldr r1, [r0, #8]
	add r1, r1, #1
	str r1, [r0, #8]
	mov r1, #0
	str r1, [r0, #0xc]
	mov r1, #0x10
	bl MOD08_02228AD4
_02228E44:
	mov r0, #1
	pop {r3, pc}

	thumb_func_start MOD08_02228E48
MOD08_02228E48: ; 0x02228E48
	push {r3, lr}
	mov r1, #0x11
	bl MOD08_02228AD4
	mov r0, #1
	pop {r3, pc}

	thumb_func_start MOD08_02228E54
MOD08_02228E54: ; 0x02228E54
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _02228E64
	cmp r0, #1
	beq _02228E74
	b _02228EDC
_02228E64:
	ldr r0, [r5, #0x18]
	cmp r0, #3
	blt _02228E6E
	bl ErrorHandling
_02228E6E:
	ldr r0, [r5, #8]
	add r0, r0, #1
	str r0, [r5, #8]
_02228E74:
	ldr r1, [r5, #0x18]
	mov r0, #0x18
	add r3, r1, #0
	mul r3, r0
	ldr r0, _02228EE0 ; =0x0222D0D0
	ldr r1, [r5, #0xc]
	add r0, r0, r3
	lsl r2, r1, #1
	ldrsh r4, [r2, r0]
	add r0, r1, #1
	str r0, [r5, #0xc]
	cmp r0, #0xb
	bgt _02228E92
	cmp r4, #0xff
	bne _02228EB2
_02228E92:
	ldr r0, [r5, #8]
	mov r1, #0
	add r0, r0, #1
	str r0, [r5, #8]
	ldr r0, [r5, #0x18]
	add r0, r0, #1
	str r0, [r5, #0x18]
	ldr r0, [r5, #0x30]
	bl FUN_0200C898
	add r0, r5, #0
	mov r1, #0x12
	bl MOD08_02228AD4
	mov r0, #1
	pop {r3, r4, r5, pc}
_02228EB2:
	cmp r0, #5
	bne _02228EBE
	ldr r0, _02228EE4 ; =0x000005FE
	mov r1, #0x75
	bl FUN_020054A8
_02228EBE:
	ldr r0, [r5, #0x30]
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200C82C
	ldr r0, _02228EE8 ; =0x0001FFFE
	mov r1, #0x5a
	mul r0, r4
	lsl r1, r1, #2
	bl _s32_div_f
	add r1, r0, #0
	ldr r0, [r5, #0x30]
	bl FUN_0200C8BC
_02228EDC:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_02228EE0: .word MOD8_0222D0D0
_02228EE4: .word 0x000005FE
_02228EE8: .word 0x0001FFFE

	thumb_func_start MOD08_02228EEC
MOD08_02228EEC: ; 0x02228EEC
	mov r0, #1
	bx lr

	thumb_func_start MOD08_02228EF0
MOD08_02228EF0: ; 0x02228EF0
	push {r3, lr}
	mov r1, #0x14
	bl MOD08_02228AD4
	mov r0, #1
	pop {r3, pc}

	thumb_func_start MOD08_02228EFC
MOD08_02228EFC: ; 0x02228EFC
	push {r3, lr}
	mov r1, #0x1b
	bl MOD08_02228AD4
	mov r0, #1
	pop {r3, pc}

	thumb_func_start MOD08_02228F08
MOD08_02228F08: ; 0x02228F08
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r4, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #3
	bhi _02228FDC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02228F20: ; jump table
	.short _02228F28 - _02228F20 - 2 ; case 0
	.short _02228F5A - _02228F20 - 2 ; case 1
	.short _02228FA2 - _02228F20 - 2 ; case 2
	.short _02228FB4 - _02228F20 - 2 ; case 3
_02228F28:
	ldr r0, [r4, #0x30]
	bl FUN_0200C68C
	mov r1, #0
	mov r3, #1
	add r2, r0, #0
	add r5, r3, #0
	lsl r5, r2
	lsl r2, r5, #0x10
	str r1, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	add r0, r4, #0
	str r1, [sp, #8]
	add r0, #0xb0
	ldr r0, [r0]
	mov r1, #4
	lsr r2, r2, #0x10
	sub r3, r3, #6
	bl FUN_02003210
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02228FF2
_02228F5A:
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	bne _02228FF2
	add r0, r4, #0
	add r0, #0xa0
	ldr r0, [r0]
	add r1, r4, #0
	str r0, [sp, #0x10]
	add r1, #0x94
	ldr r1, [r1]
	str r1, [sp, #0x14]
	bl MOD08_022281C8
	str r0, [sp, #0x18]
	mov r0, #0
	str r0, [sp, #0x1c]
	add r2, sp, #0xc
	ldr r0, [r4, #0x30]
	add r1, sp, #0xc
	add r2, #2
	bl FUN_0200C7A0
	add r0, sp, #0xc
	bl MOD08_02228880
	add r1, r4, #0
	add r1, #0xd0
	str r0, [r1]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02228FF2
_02228FA2:
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	bl MOD08_022288E0
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02228FF2
_02228FB4:
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	bl MOD08_02228954
	cmp r0, #0
	bne _02228FF2
	ldr r0, [r4, #0x30]
	mov r1, #0
	bl FUN_0200C61C
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	bl MOD08_02228970
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02228FF2
_02228FDC:
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	bne _02228FF2
	add r0, r4, #0
	mov r1, #0x16
	bl MOD08_02228AD4
_02228FF2:
	mov r0, #1
	add sp, #0x20
	pop {r3, r4, r5, pc}

	thumb_func_start MOD08_02228FF8
MOD08_02228FF8: ; 0x02228FF8
	mov r0, #1
	bx lr

	thumb_func_start MOD08_02228FFC
MOD08_02228FFC: ; 0x02228FFC
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r1, [r4, #8]
	cmp r1, #0
	beq _0222900E
	cmp r1, #1
	beq _02229040
	b _02229054
_0222900E:
	ldr r0, [r4, #0x30]
	bl FUN_0200C68C
	add r2, r0, #0
	mov r0, #0xa
	str r0, [sp]
	mov r0, #0
	mov r3, #1
	add r5, r3, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r0, r4, #0
	lsl r5, r2
	add r0, #0xb0
	lsl r2, r5, #0x10
	ldr r0, [r0]
	mov r1, #4
	lsr r2, r2, #0x10
	sub r3, r3, #6
	bl FUN_02003210
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _0222905A
_02229040:
	add r0, #0xb0
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	bne _0222905A
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _0222905A
_02229054:
	mov r1, #0x18
	bl MOD08_02228AD4
_0222905A:
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start MOD08_02229060
MOD08_02229060: ; 0x02229060
	push {r3, lr}
	mov r1, #0x19
	bl MOD08_02228AD4
	mov r0, #1
	pop {r3, pc}

	thumb_func_start MOD08_0222906C
MOD08_0222906C: ; 0x0222906C
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #8]
	cmp r1, #0
	beq _0222907C
	cmp r1, #1
	beq _0222908A
	b _022290E2
_0222907C:
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl FUN_0200C90C
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
_0222908A:
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #0
	beq _022290B2
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0x20
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x21
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x21
	strb r1, [r0]
	b _022290CE
_022290B2:
	add r0, r4, #0
	mov r1, #0
	add r0, #0x20
	strb r1, [r0]
	add r0, r4, #0
	mov r2, #0xf
	add r0, #0x21
	strb r2, [r0]
	ldr r0, [r4, #0x30]
	bl FUN_0200C644
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
_022290CE:
	add r0, r4, #0
	add r0, #0x20
	add r4, #0x21
	ldrb r1, [r0]
	ldrb r0, [r4]
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _022290EC ; =0x04000052
	strh r1, [r0]
	b _022290E8
_022290E2:
	mov r1, #0x1a
	bl MOD08_02228AD4
_022290E8:
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_022290EC: .word 0x04000052

	thumb_func_start MOD08_022290F0
MOD08_022290F0: ; 0x022290F0
	push {r3, lr}
	mov r1, #0x1b
	bl MOD08_02228AD4
	mov r0, #1
	pop {r3, pc}

	thumb_func_start MOD08_022290FC
MOD08_022290FC: ; 0x022290FC
	mov r0, #0
	bx lr

	thumb_func_start MOD08_02229100
MOD08_02229100: ; 0x02229100
	push {r3, lr}
	ldr r1, [r0, #0x14]
	lsl r2, r1, #2
	ldr r1, _02229110 ; =0x0222D118
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	nop
_02229110: .word MOD8_0222D118

	thumb_func_start MOD08_02229114
MOD08_02229114: ; 0x02229114
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #3
	bls _02229122
	b _02229322
_02229122:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222912E: ; jump table
	.short _02229136 - _0222912E - 2 ; case 0
	.short _022291A4 - _0222912E - 2 ; case 1
	.short _0222929E - _0222912E - 2 ; case 2
	.short _02229302 - _0222912E - 2 ; case 3
_02229136:
	mov r0, #0xba
	ldrsh r0, [r4, r0]
	add r1, r4, #0
	mov r2, #0xb8
	str r0, [sp]
	mov r0, #0xbe
	ldrsh r0, [r4, r0]
	mov r3, #0xbc
	add r1, #0x6c
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0xc8
	ldr r0, [r0]
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	add r0, r4, #0
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	add r0, #0x48
	bl MOD08_02217F50
	add r0, r4, #0
	mov r1, #0
	add r0, #0xc4
	str r1, [r0]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	add r0, r4, #0
	add r0, #0xd4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	bl MOD08_022280C4
	cmp r0, #1
	bne _0222928C
	bl LCRandom
	mov r1, #0x14
	bl _s32_div_f
	add r1, #0xa
	ldr r0, [r4, #0x30]
	lsl r1, r1, #0xd
	bl FUN_0200C8BC
	b _022293BE
_022291A4:
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	bl MOD08_022280C4
	cmp r0, #1
	bne _02229242
	mov r1, #2
	ldr r0, [r4, #0x30]
	lsl r1, r1, #0xc
	bl FUN_0200C8BC
	add r0, r4, #0
	add r0, #0xc4
	ldr r2, [r0]
	add r0, r4, #0
	add r0, #0xc0
	ldr r1, [r0]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	add r0, #0xa
	cmp r2, r0
	ble _022291DE
	mov r1, #2
	ldr r0, [r4, #0x30]
	lsl r1, r1, #0xc
	bl FUN_0200C8BC
_022291DE:
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	bl MOD08_02228104
	cmp r0, #1
	bne _02229242
	add r0, r4, #0
	add r0, #0xc4
	ldr r2, [r0]
	add r0, r4, #0
	add r0, #0xc0
	ldr r1, [r0]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	add r0, #0xa
	cmp r2, r0
	bne _02229242
	ldr r0, [r4, #0x30]
	bl FUN_0200C68C
	add r3, r0, #0
	mov r0, #0x10
	str r0, [sp]
	sub r0, #0x12
	str r0, [sp, #4]
	mov r2, #2
	add r1, r4, #0
	lsl r3, r3, #0x14
	str r2, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #0xe
	str r0, [sp, #0x10]
	ldr r0, _022293C4 ; =0x0000FFFF
	add r1, #0x94
	str r0, [sp, #0x14]
	ldr r0, _022293C8 ; =0x000003EA
	lsr r3, r3, #0x10
	str r0, [sp, #0x18]
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	ldr r1, [r1]
	bl MOD08_02218B20
	add r1, r4, #0
	add r1, #0xd4
	str r0, [r1]
_02229242:
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	cmp r0, #6
	blt _0222927A
	cmp r0, #8
	bgt _0222927A
	add r0, r4, #0
	add r0, #0xc0
	ldr r1, [r0]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r2, r0, #1
	add r0, r4, #0
	add r0, #0xc4
	ldr r1, [r0]
	cmp r1, r2
	ble _0222927A
	add r0, r2, #5
	cmp r1, r0
	blt _0222928C
_0222927A:
	add r0, r4, #0
	add r1, r4, #0
	ldr r2, [r4, #0x30]
	add r0, #0x48
	add r1, #0x6c
	bl MOD08_02217FE4
	cmp r0, #0
	beq _0222928E
_0222928C:
	b _022293BE
_0222928E:
	add r0, r4, #0
	mov r1, #0
	bl MOD08_02229FFC
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _022293BE
_0222929E:
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	bl MOD08_02228104
	cmp r0, #1
	bne _022292D2
	add r0, r4, #0
	add r0, #0xd4
	ldr r0, [r0]
	cmp r0, #0
	beq _022292D2
	bl MOD08_02218AF8
	cmp r0, #1
	beq _022293BE
	add r0, r4, #0
	add r0, #0xd4
	ldr r0, [r0]
	bl MOD08_02218B08
	mov r0, #1
	str r0, [r4, #0x28]
	add sp, #0x1c
	mov r0, #0
	pop {r3, r4, pc}
_022292D2:
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	cmp r0, #0xf
	blt _022292E6
	mov r0, #1
	str r0, [r4, #0x28]
	add sp, #0x1c
	mov r0, #0
	pop {r3, r4, pc}
_022292E6:
	add r0, r4, #0
	add r0, #0xa0
	ldr r1, [r0]
	ldr r0, _022293CC ; =0x00000111
	cmp r1, r0
	bne _022292FA
	ldr r0, _022293D0 ; =0x000007E8
	mov r1, #0x75
	bl FUN_020054A8
_022292FA:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _022293BE
_02229302:
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl FUN_0200C5C0
	add r0, r4, #0
	mov r1, #1
	bl MOD08_0222A008
	add r0, r4, #0
	mov r1, #0
	add r0, #0xc4
	str r1, [r0]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _022293BE
_02229322:
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	cmp r0, #0xf
	bne _0222937C
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	cmp r0, #0xc
	beq _02229378
	cmp r0, #0xd
	beq _02229378
	ldr r0, [r4, #0x30]
	bl FUN_0200C68C
	add r3, r0, #0
	mov r0, #0x10
	str r0, [sp]
	sub r0, #0x12
	str r0, [sp, #4]
	mov r2, #2
	add r1, r4, #0
	lsl r3, r3, #0x14
	str r2, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #0xe
	str r0, [sp, #0x10]
	ldr r0, _022293C4 ; =0x0000FFFF
	add r1, #0x94
	str r0, [sp, #0x14]
	ldr r0, _022293C8 ; =0x000003EA
	lsr r3, r3, #0x10
	str r0, [sp, #0x18]
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	ldr r1, [r1]
	bl MOD08_02218B20
	add r1, r4, #0
	add r1, #0xd4
	str r0, [r1]
_02229378:
	mov r0, #1
	str r0, [r4, #0x28]
_0222937C:
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	cmp r0, #0xf
	ble _022293BE
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	cmp r0, #0xc
	beq _022293B8
	cmp r0, #0xd
	beq _022293B8
	add r0, r4, #0
	add r0, #0xd4
	ldr r0, [r0]
	bl MOD08_02218AF8
	cmp r0, #1
	beq _022293BE
	add r4, #0xd4
	ldr r0, [r4]
	bl MOD08_02218B08
_022293B8:
	add sp, #0x1c
	mov r0, #0
	pop {r3, r4, pc}
_022293BE:
	mov r0, #1
	add sp, #0x1c
	pop {r3, r4, pc}
	.align 2, 0
_022293C4: .word 0x0000FFFF
_022293C8: .word 0x000003EA
_022293CC: .word 0x00000111
_022293D0: .word 0x000007E8

	thumb_func_start MOD08_022293D4
MOD08_022293D4: ; 0x022293D4
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #3
	bls _022293E2
	b _022295CE
_022293E2:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022293EE: ; jump table
	.short _022293F6 - _022293EE - 2 ; case 0
	.short _02229464 - _022293EE - 2 ; case 1
	.short _0222955E - _022293EE - 2 ; case 2
	.short _022295AE - _022293EE - 2 ; case 3
_022293F6:
	mov r0, #0xba
	ldrsh r0, [r4, r0]
	add r1, r4, #0
	mov r2, #0xb8
	str r0, [sp]
	mov r0, #0xbe
	ldrsh r0, [r4, r0]
	mov r3, #0xbc
	add r1, #0x6c
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0xc8
	ldr r0, [r0]
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	add r0, r4, #0
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	add r0, #0x48
	bl MOD08_02217F50
	add r0, r4, #0
	mov r1, #0
	add r0, #0xc4
	str r1, [r0]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	add r0, r4, #0
	add r0, #0xd4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	bl MOD08_022280C4
	cmp r0, #1
	bne _0222954C
	bl LCRandom
	mov r1, #0x14
	bl _s32_div_f
	add r1, #0xa
	ldr r0, [r4, #0x30]
	lsl r1, r1, #0xd
	bl FUN_0200C8BC
	b _02229656
_02229464:
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	bl MOD08_022280C4
	cmp r0, #1
	bne _02229502
	mov r1, #2
	ldr r0, [r4, #0x30]
	lsl r1, r1, #0xc
	bl FUN_0200C8BC
	add r0, r4, #0
	add r0, #0xc4
	ldr r2, [r0]
	add r0, r4, #0
	add r0, #0xc0
	ldr r1, [r0]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	add r0, #0xa
	cmp r2, r0
	ble _0222949E
	mov r1, #2
	ldr r0, [r4, #0x30]
	lsl r1, r1, #0xc
	bl FUN_0200C8BC
_0222949E:
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	bl MOD08_02228104
	cmp r0, #1
	bne _02229502
	add r0, r4, #0
	add r0, #0xc4
	ldr r2, [r0]
	add r0, r4, #0
	add r0, #0xc0
	ldr r1, [r0]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	add r0, #0xa
	cmp r2, r0
	bne _02229502
	ldr r0, [r4, #0x30]
	bl FUN_0200C68C
	add r3, r0, #0
	mov r0, #0x10
	str r0, [sp]
	sub r0, #0x12
	str r0, [sp, #4]
	mov r2, #2
	add r1, r4, #0
	lsl r3, r3, #0x14
	str r2, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #0xe
	str r0, [sp, #0x10]
	ldr r0, _0222965C ; =0x0000FFFF
	add r1, #0x94
	str r0, [sp, #0x14]
	ldr r0, _02229660 ; =0x000003EA
	lsr r3, r3, #0x10
	str r0, [sp, #0x18]
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	ldr r1, [r1]
	bl MOD08_02218B20
	add r1, r4, #0
	add r1, #0xd4
	str r0, [r1]
_02229502:
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	cmp r0, #6
	blt _0222953A
	cmp r0, #8
	bgt _0222953A
	add r0, r4, #0
	add r0, #0xc0
	ldr r1, [r0]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r2, r0, #1
	add r0, r4, #0
	add r0, #0xc4
	ldr r1, [r0]
	cmp r1, r2
	ble _0222953A
	add r0, r2, #5
	cmp r1, r0
	blt _0222954C
_0222953A:
	add r0, r4, #0
	add r1, r4, #0
	ldr r2, [r4, #0x30]
	add r0, #0x48
	add r1, #0x6c
	bl MOD08_02217FE4
	cmp r0, #0
	beq _0222954E
_0222954C:
	b _02229656
_0222954E:
	add r0, r4, #0
	mov r1, #0
	bl MOD08_02229FFC
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02229656
_0222955E:
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	bl MOD08_02228104
	cmp r0, #1
	bne _02229592
	add r0, r4, #0
	add r0, #0xd4
	ldr r0, [r0]
	cmp r0, #0
	beq _02229592
	bl MOD08_02218AF8
	cmp r0, #1
	beq _02229656
	add r0, r4, #0
	add r0, #0xd4
	ldr r0, [r0]
	bl MOD08_02218B08
	mov r0, #1
	str r0, [r4, #0x28]
	add sp, #0x1c
	mov r0, #0
	pop {r3, r4, pc}
_02229592:
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	cmp r0, #0xf
	blt _022295A6
	mov r0, #1
	str r0, [r4, #0x28]
	add sp, #0x1c
	mov r0, #0
	pop {r3, r4, pc}
_022295A6:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02229656
_022295AE:
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl FUN_0200C5C0
	add r0, r4, #0
	mov r1, #0
	bl MOD08_0222A008
	add r0, r4, #0
	mov r1, #0
	add r0, #0xc4
	str r1, [r0]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02229656
_022295CE:
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	cmp r0, #0xf
	bne _02229622
	ldr r0, [r4, #0x30]
	mov r1, #2
	bl FUN_0200C61C
	ldr r0, [r4, #0x30]
	bl FUN_0200C68C
	add r3, r0, #0
	mov r0, #0x10
	str r0, [sp]
	sub r0, #0x12
	str r0, [sp, #4]
	mov r2, #2
	add r1, r4, #0
	lsl r3, r3, #0x14
	str r2, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #0xe
	str r0, [sp, #0x10]
	ldr r0, _0222965C ; =0x0000FFFF
	add r1, #0x94
	str r0, [sp, #0x14]
	ldr r0, _02229660 ; =0x000003EA
	lsr r3, r3, #0x10
	str r0, [sp, #0x18]
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	ldr r1, [r1]
	bl MOD08_02218B20
	add r1, r4, #0
	add r1, #0xd4
	str r0, [r1]
	mov r0, #1
	str r0, [r4, #0x28]
_02229622:
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	cmp r0, #0xf
	ble _02229656
	add r0, r4, #0
	add r0, #0xd4
	ldr r0, [r0]
	bl MOD08_02218AF8
	cmp r0, #1
	beq _02229656
	add r4, #0xd4
	ldr r0, [r4]
	bl MOD08_02218B08
	add sp, #0x1c
	mov r0, #0
	pop {r3, r4, pc}
_02229656:
	mov r0, #1
	add sp, #0x1c
	pop {r3, r4, pc}
	.align 2, 0
_0222965C: .word 0x0000FFFF
_02229660: .word 0x000003EA

	thumb_func_start MOD08_02229664
MOD08_02229664: ; 0x02229664
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldr r1, [r4, #8]
	cmp r1, #7
	bls _02229672
	b _022297EA
_02229672:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222967E: ; jump table
	.short _0222968E - _0222967E - 2 ; case 0
	.short _022296CC - _0222967E - 2 ; case 1
	.short _022296FC - _0222967E - 2 ; case 2
	.short _02229732 - _0222967E - 2 ; case 3
	.short _02229742 - _0222967E - 2 ; case 4
	.short _02229770 - _0222967E - 2 ; case 5
	.short _0222979E - _0222967E - 2 ; case 6
	.short _022297CC - _0222967E - 2 ; case 7
_0222968E:
	mov r1, #0
	bl MOD08_0222A008
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl FUN_0200C5C0
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	cmp r0, #2
	blt _022296E2
	ldr r0, [r4, #0x30]
	mov r1, #0
	bl FUN_0200C61C
	add r0, r4, #0
	mov r1, #0
	add r0, #0xc4
	str r1, [r0]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _022297F0
_022296CC:
	add r0, #0xc4
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	cmp r0, #2
	bge _022296E4
_022296E2:
	b _022297F0
_022296E4:
	ldr r0, [r4, #0x30]
	mov r1, #2
	bl FUN_0200C61C
	add r0, r4, #0
	mov r1, #0
	add r0, #0xc4
	str r1, [r0]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _022297F0
_022296FC:
	add r0, #0xa0
	ldr r0, [r0]
	add r2, sp, #0
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x94
	ldr r0, [r0]
	add r1, sp, #0
	str r0, [sp, #8]
	mov r0, #0xff
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x30]
	add r2, #2
	bl FUN_0200C7A0
	add r0, sp, #0
	bl MOD08_02228880
	add r1, r4, #0
	add r1, #0xd0
	str r0, [r1]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _022297F0
_02229732:
	add r0, #0xd0
	ldr r0, [r0]
	bl MOD08_022288E0
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _022297F0
_02229742:
	add r0, #0xc4
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	cmp r0, #6
	blt _022297F0
	ldr r0, [r4, #0x30]
	mov r1, #2
	bl FUN_0200C61C
	add r0, r4, #0
	mov r1, #0
	add r0, #0xc4
	str r1, [r0]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _022297F0
_02229770:
	add r0, #0xc4
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	cmp r0, #6
	blt _022297F0
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl FUN_0200C61C
	add r0, r4, #0
	mov r1, #0
	add r0, #0xc4
	str r1, [r0]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _022297F0
_0222979E:
	add r0, #0xc4
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	cmp r0, #6
	blt _022297F0
	ldr r0, [r4, #0x30]
	mov r1, #0
	bl FUN_0200C61C
	add r0, r4, #0
	mov r1, #0
	add r0, #0xc4
	str r1, [r0]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _022297F0
_022297CC:
	add r0, #0xd0
	ldr r0, [r0]
	bl MOD08_02228954
	cmp r0, #0
	bne _022297F0
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	bl MOD08_02228970
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _022297F0
_022297EA:
	add sp, #0x14
	mov r0, #0
	pop {r3, r4, pc}
_022297F0:
	mov r0, #1
	add sp, #0x14
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD08_022297F8
MOD08_022297F8: ; 0x022297F8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _02229808
	cmp r0, #1
	beq _0222983C
	b _0222986E
_02229808:
	ldr r0, [r4, #0x10]
	cmp r0, #0
	bne _0222981E
	ldr r1, _0222987C ; =0xFFFFE001
	add r0, r4, #0
	add r0, #0x34
	lsr r2, r1, #0x13
	mov r3, #0xa
	bl MOD08_02218008
	b _0222982C
_0222981E:
	add r0, r4, #0
	ldr r1, _02229880 ; =0x00001FFF
	ldr r2, _0222987C ; =0xFFFFE001
	add r0, #0x34
	mov r3, #0xa
	bl MOD08_02218008
_0222982C:
	ldr r1, [r4, #0x10]
	mov r0, #1
	eor r0, r1
	str r0, [r4, #0x10]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02229876
_0222983C:
	ldr r1, [r4, #0x34]
	ldr r0, [r4, #0x30]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_0200C898
	add r0, r4, #0
	add r0, #0x34
	bl MOD08_02218058
	cmp r0, #0
	bne _02229876
	ldr r0, [r4, #0xc]
	cmp r0, #1
	blt _02229862
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	b _02229876
_02229862:
	add r0, r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4, #8]
	sub r0, r0, #1
	str r0, [r4, #8]
	b _02229876
_0222986E:
	mov r0, #0
	add r4, #0xc4
	str r0, [r4]
	pop {r4, pc}
_02229876:
	mov r0, #1
	pop {r4, pc}
	nop
_0222987C: .word 0xFFFFE001
_02229880: .word 0x00001FFF

	thumb_func_start MOD08_02229884
MOD08_02229884: ; 0x02229884
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0xff
	bne _02229896
	add sp, #4
	mov r0, #0
	pop {r3, r4, pc}
_02229896:
	ldr r0, [r4, #0x30]
	cmp r0, #0
	beq _022298BA
	add r1, sp, #0
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	add r1, sp, #0
	mov r0, #2
	ldrsh r2, [r1, r0]
	add r0, r4, #0
	add r0, #0xb8
	strh r2, [r0]
	mov r0, #0
	ldrsh r0, [r1, r0]
	add r4, #0xba
	strh r0, [r4]
_022298BA:
	mov r0, #1
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD08_022298C0
MOD08_022298C0: ; 0x022298C0
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _02229912
	add r0, r4, #0
	add r0, #0xdc
	ldr r0, [r0]
	cmp r0, #0
	ble _022298EA
	add r0, r4, #0
	add r0, #0xdc
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xdc
	str r1, [r0]
	ldr r0, [r4, #0x2c]
	bl FUN_0200BC1C
	pop {r4, pc}
_022298EA:
	add r1, #0x98
	ldr r1, [r1]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _02229914 ; =0x0222D01C
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	bne _02229900
	mov r0, #0
	str r0, [r4, #0x1c]
_02229900:
	ldr r0, [r4, #0x24]
	cmp r0, #1
	bne _0222990C
	ldr r0, [r4, #0x30]
	bl FUN_0200C5A8
_0222990C:
	ldr r0, [r4, #0x2c]
	bl FUN_0200BC1C
_02229912:
	pop {r4, pc}
	.align 2, 0
_02229914: .word MOD8_0222D01C

	thumb_func_start MOD08_02229918
MOD08_02229918: ; 0x02229918
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #4]
	mov r1, #0xe0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0xe0
	add r4, r0, #0
	bl MI_CpuFill8
	cmp r4, #0
	bne _02229936
	bl ErrorHandling
_02229936:
	add r3, r4, #0
	add r3, #0x90
	mov r2, #5
_0222993C:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222993C
	mov r0, #0
	str r0, [r4, #8]
	str r0, [r4, #0x10]
	str r0, [r4, #0xc]
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	str r0, [r4]
	str r0, [r4, #4]
	add r0, r4, #0
	add r0, #0xac
	ldr r0, [r0]
	bl FUN_0200BB34
	str r0, [r4, #0x2c]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xdc
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	bl MOD08_02228140
	str r0, [r4, #0x24]
	add r0, r4, #0
	mov r2, #0
	add r0, #0xc4
	str r2, [r0]
	add r0, r4, #0
	mov r1, #0x10
	add r0, #0x20
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x21
	strb r2, [r0]
	bl MOD08_0221268C
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r0, r0, #0x1f
	sub r0, r0, r1
	mov r2, #0x1f
	ror r0, r2
	add r0, r1, r0
	beq _022299AA
	add r0, r4, #0
	mov r1, #1
	add r0, #0x22
	strb r1, [r0]
	b _022299B2
_022299AA:
	add r0, r4, #0
	sub r2, #0x20
	add r0, #0x22
	strb r2, [r0]
_022299B2:
	add r0, r4, #0
	bl MOD08_02229E40
	add r0, r4, #0
	bl MOD08_02229F64
	add r0, r4, #0
	bl MOD08_02229A90
	mov r0, #1
	str r0, [r4, #0x1c]
	mov r0, #0
	str r0, [r4, #0x28]
	mov r2, #0xfa
	ldr r0, _022299E4 ; =MOD08_022298C0
	add r1, r4, #0
	lsl r2, r2, #2
	bl FUN_0200CA44
	add r1, r4, #0
	add r1, #0xcc
	str r0, [r1]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_022299E4: .word MOD08_022298C0

	thumb_func_start MOD08_022299E8
MOD08_022299E8: ; 0x022299E8
	push {r4, lr}
	add r4, r0, #0
	bne _022299F2
	bl ErrorHandling
_022299F2:
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _022299FC
	mov r0, #1
	pop {r4, pc}
_022299FC:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD08_02229A00
MOD08_02229A00: ; 0x02229A00
	push {r4, lr}
	add r4, r0, #0
	bne _02229A0A
	bl ErrorHandling
_02229A0A:
	ldr r0, [r4, #0x28]
	cmp r0, #0
	beq _02229A14
	mov r0, #1
	pop {r4, pc}
_02229A14:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD08_02229A18
MOD08_02229A18: ; 0x02229A18
	str r1, [r0, #0x14]
	bx lr

	thumb_func_start MOD08_02229A1C
MOD08_02229A1C: ; 0x02229A1C
	ldr r0, [r0, #0x14]
	cmp r0, r1
	bne _02229A26
	mov r0, #1
	bx lr
_02229A26:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD08_02229A2C
MOD08_02229A2C: ; 0x02229A2C
	push {r4, lr}
	add r4, r0, #0
	bne _02229A36
	bl ErrorHandling
_02229A36:
	add r0, r4, #0
	add r0, #0xac
	ldr r0, [r0]
	ldr r1, [r4, #0x2c]
	bl FUN_0200C398
	ldr r0, [r4, #0x30]
	bl FUN_0200C3DC
	add r0, r4, #0
	add r0, #0xcc
	ldr r0, [r0]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02229A5C
MOD08_02229A5C: ; 0x02229A5C
	add r2, r0, #0
	add r0, #0x98
	str r1, [r0]
	mov r0, #0
	str r0, [r2, #8]
	str r0, [r2, #0xc]
	str r0, [r2, #0x10]
	mov r0, #1
	add r1, r2, #0
	str r0, [r2, #0x1c]
	ldr r0, [r2, #0x30]
	ldr r3, _02229A7C ; =FUN_0200C7A0
	add r1, #0xb8
	add r2, #0xba
	bx r3
	nop
_02229A7C: .word FUN_0200C7A0

	thumb_func_start MOD08_02229A80
MOD08_02229A80: ; 0x02229A80
	push {r4, lr}
	add r4, r0, #0
	bne _02229A8A
	bl ErrorHandling
_02229A8A:
	add r4, #0x98
	ldr r0, [r4]
	pop {r4, pc}

	thumb_func_start MOD08_02229A90
MOD08_02229A90: ; 0x02229A90
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	add r2, r4, #0
	ldr r0, [r4, #0x30]
	add r1, #0xb8
	add r2, #0xba
	bl FUN_0200C7A0
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	cmp r0, #0x11
	bls _02229AAE
	b _02229CF6
_02229AAE:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02229ABA: ; jump table
	.short _02229ADE - _02229ABA - 2 ; case 0
	.short _02229ADE - _02229ABA - 2 ; case 1
	.short _02229ADE - _02229ABA - 2 ; case 2
	.short _02229ADE - _02229ABA - 2 ; case 3
	.short _02229ADE - _02229ABA - 2 ; case 4
	.short _02229ADE - _02229ABA - 2 ; case 5
	.short _02229AF6 - _02229ABA - 2 ; case 6
	.short _02229B1C - _02229ABA - 2 ; case 7
	.short _02229B50 - _02229ABA - 2 ; case 8
	.short _02229B76 - _02229ABA - 2 ; case 9
	.short _02229B9C - _02229ABA - 2 ; case 10
	.short _02229BC2 - _02229ABA - 2 ; case 11
	.short _02229BE8 - _02229ABA - 2 ; case 12
	.short _02229C14 - _02229ABA - 2 ; case 13
	.short _02229C4C - _02229ABA - 2 ; case 14
	.short _02229C72 - _02229ABA - 2 ; case 15
	.short _02229C9E - _02229ABA - 2 ; case 16
	.short _02229CCA - _02229ABA - 2 ; case 17
_02229ADE:
	add r1, r4, #0
	add r2, r4, #0
	ldr r0, [r4, #0x30]
	add r1, #0xbc
	add r2, #0xbe
	bl FUN_0200C7A0
	add r0, r4, #0
	mov r1, #0
	add r0, #0xc8
	str r1, [r0]
	b _02229CF6
_02229AF6:
	mov r0, #0
	add r2, r4, #0
	add r3, r4, #0
	add r1, r0, #0
	add r2, #0xbc
	add r3, #0xbe
	bl MOD08_02217B1C
	add r0, r4, #0
	mov r1, #0x30
	add r0, #0xc8
	str r1, [r0]
	mov r0, #0xbe
	ldrsh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xbe
	add r1, #0x20
	strh r1, [r0]
	b _02229CF6
_02229B1C:
	add r1, r4, #0
	add r2, r4, #0
	ldr r0, [r4, #0x30]
	add r1, #0xb8
	add r2, #0xba
	bl FUN_0200C7A0
	add r2, r4, #0
	add r3, r4, #0
	mov r0, #1
	mov r1, #4
	add r2, #0xbc
	add r3, #0xbe
	bl MOD08_02217B1C
	add r0, r4, #0
	mov r1, #0x30
	add r0, #0xc8
	str r1, [r0]
	mov r0, #0xbe
	ldrsh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xbe
	add r1, #0x20
	strh r1, [r0]
	b _02229CF6
_02229B50:
	add r2, r4, #0
	add r3, r4, #0
	mov r0, #1
	mov r1, #2
	add r2, #0xbc
	add r3, #0xbe
	bl MOD08_02217B1C
	add r0, r4, #0
	mov r1, #0x30
	add r0, #0xc8
	str r1, [r0]
	mov r0, #0xbe
	ldrsh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xbe
	add r1, #0x20
	strh r1, [r0]
	b _02229CF6
_02229B76:
	add r2, r4, #0
	add r3, r4, #0
	mov r0, #0
	mov r1, #1
	add r2, #0xbc
	add r3, #0xbe
	bl MOD08_02217B1C
	add r0, r4, #0
	mov r1, #0x30
	add r0, #0xc8
	str r1, [r0]
	mov r0, #0xbe
	ldrsh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xbe
	add r1, #0x20
	strh r1, [r0]
	b _02229CF6
_02229B9C:
	add r2, r4, #0
	add r3, r4, #0
	mov r0, #1
	mov r1, #3
	add r2, #0xbc
	add r3, #0xbe
	bl MOD08_02217B1C
	add r0, r4, #0
	mov r1, #0x30
	add r0, #0xc8
	str r1, [r0]
	mov r0, #0xbe
	ldrsh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xbe
	add r1, #0x20
	strh r1, [r0]
	b _02229CF6
_02229BC2:
	add r2, r4, #0
	add r3, r4, #0
	mov r0, #1
	mov r1, #5
	add r2, #0xbc
	add r3, #0xbe
	bl MOD08_02217B1C
	add r0, r4, #0
	mov r1, #0x30
	add r0, #0xc8
	str r1, [r0]
	mov r0, #0xbe
	ldrsh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xbe
	add r1, #0x20
	strh r1, [r0]
	b _02229CF6
_02229BE8:
	add r2, r4, #0
	add r3, r4, #0
	mov r0, #0
	mov r1, #1
	add r2, #0xbc
	add r3, #0xbe
	bl MOD08_02217B1C
	add r0, r4, #0
	mov r1, #0x10
	add r0, #0xc8
	str r1, [r0]
	mov r0, #0xbe
	ldrsh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xbe
	add r1, #0x10
	strh r1, [r0]
	mov r0, #0xc
	add r4, #0xc0
	str r0, [r4]
	pop {r4, pc}
_02229C14:
	add r2, r4, #0
	add r3, r4, #0
	mov r0, #0
	mov r1, #1
	add r2, #0xbc
	add r3, #0xbe
	bl MOD08_02217B1C
	add r0, r4, #0
	mov r1, #0x20
	add r0, #0xc8
	str r1, [r0]
	mov r0, #0xbc
	ldrsh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xbc
	sub r1, #0x14
	strh r1, [r0]
	mov r0, #0xbe
	ldrsh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xbe
	add r1, #0x26
	strh r1, [r0]
	mov r0, #0x10
	add r4, #0xc0
	str r0, [r4]
	pop {r4, pc}
_02229C4C:
	add r0, r4, #0
	mov r1, #0x80
	add r0, #0xbc
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0x40
	add r0, #0xbe
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0x20
	add r0, #0xc8
	str r1, [r0]
	mov r0, #0xbe
	ldrsh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xbe
	add r1, #0x20
	strh r1, [r0]
	b _02229CF6
_02229C72:
	add r2, r4, #0
	add r3, r4, #0
	mov r0, #0
	mov r1, #1
	add r2, #0xbc
	add r3, #0xbe
	bl MOD08_02217B1C
	add r0, r4, #0
	mov r1, #0x40
	add r0, #0xc8
	str r1, [r0]
	mov r0, #0xbe
	ldrsh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xbe
	add r1, #8
	strh r1, [r0]
	mov r0, #0x10
	add r4, #0xc0
	str r0, [r4]
	pop {r4, pc}
_02229C9E:
	add r2, r4, #0
	add r3, r4, #0
	mov r0, #1
	mov r1, #3
	add r2, #0xbc
	add r3, #0xbe
	bl MOD08_02217B1C
	add r0, r4, #0
	mov r1, #0x40
	add r0, #0xc8
	str r1, [r0]
	mov r0, #0xbe
	ldrsh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xbe
	add r1, #8
	strh r1, [r0]
	mov r0, #0x10
	add r4, #0xc0
	str r0, [r4]
	pop {r4, pc}
_02229CCA:
	add r2, r4, #0
	add r3, r4, #0
	mov r0, #1
	mov r1, #5
	add r2, #0xbc
	add r3, #0xbe
	bl MOD08_02217B1C
	add r0, r4, #0
	mov r1, #0x40
	add r0, #0xc8
	str r1, [r0]
	mov r0, #0xbe
	ldrsh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xbe
	add r1, #8
	strh r1, [r0]
	mov r0, #0x10
	add r4, #0xc0
	str r0, [r4]
	pop {r4, pc}
_02229CF6:
	mov r0, #0x14
	add r4, #0xc0
	str r0, [r4]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02229D00
MOD08_02229D00: ; 0x02229D00
	push {r4, lr}
	add r0, #0x90
	ldr r0, [r0]
	add r3, r1, #0
	add r4, r2, #0
	cmp r0, #0x11
	bls _02229D10
	b _02229E3C
_02229D10:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02229D1C: ; jump table
	.short _02229D40 - _02229D1C - 2 ; case 0
	.short _02229D56 - _02229D1C - 2 ; case 1
	.short _02229D6C - _02229D1C - 2 ; case 2
	.short _02229D98 - _02229D1C - 2 ; case 3
	.short _02229D82 - _02229D1C - 2 ; case 4
	.short _02229DAE - _02229D1C - 2 ; case 5
	.short _02229DC4 - _02229D1C - 2 ; case 6
	.short _02229DCE - _02229D1C - 2 ; case 7
	.short _02229DD8 - _02229D1C - 2 ; case 8
	.short _02229DE2 - _02229D1C - 2 ; case 9
	.short _02229DF0 - _02229D1C - 2 ; case 10
	.short _02229DFE - _02229D1C - 2 ; case 11
	.short _02229E0C - _02229D1C - 2 ; case 12
	.short _02229E1A - _02229D1C - 2 ; case 13
	.short _02229E28 - _02229D1C - 2 ; case 14
	.short _02229E32 - _02229D1C - 2 ; case 15
	.short _02229E32 - _02229D1C - 2 ; case 16
	.short _02229E32 - _02229D1C - 2 ; case 17
_02229D40:
	mov r0, #0
	add r2, r3, #0
	add r1, r0, #0
	add r3, r4, #0
	bl MOD08_02217B1C
	mov r0, #0
	ldrsh r0, [r4, r0]
	add r0, #0x20
	strh r0, [r4]
	pop {r4, pc}
_02229D56:
	add r2, r3, #0
	mov r0, #0
	mov r1, #1
	add r3, r4, #0
	bl MOD08_02217B1C
	mov r0, #0
	ldrsh r0, [r4, r0]
	add r0, #0x26
	strh r0, [r4]
	pop {r4, pc}
_02229D6C:
	add r2, r3, #0
	mov r0, #1
	mov r1, #2
	add r3, r4, #0
	bl MOD08_02217B1C
	mov r0, #0
	ldrsh r0, [r4, r0]
	add r0, #0x20
	strh r0, [r4]
	pop {r4, pc}
_02229D82:
	add r2, r3, #0
	mov r0, #1
	mov r1, #4
	add r3, r4, #0
	bl MOD08_02217B1C
	mov r0, #0
	ldrsh r0, [r4, r0]
	add r0, #0x20
	strh r0, [r4]
	pop {r4, pc}
_02229D98:
	add r2, r3, #0
	mov r0, #1
	mov r1, #3
	add r3, r4, #0
	bl MOD08_02217B1C
	mov r0, #0
	ldrsh r0, [r4, r0]
	add r0, #0x26
	strh r0, [r4]
	pop {r4, pc}
_02229DAE:
	add r2, r3, #0
	mov r0, #1
	mov r1, #5
	add r3, r4, #0
	bl MOD08_02217B1C
	mov r0, #0
	ldrsh r0, [r4, r0]
	add r0, #0x26
	strh r0, [r4]
	pop {r4, pc}
_02229DC4:
	mov r0, #0xa
	strh r0, [r3]
	mov r0, #0x64
	strh r0, [r4]
	pop {r4, pc}
_02229DCE:
	mov r0, #0xa
	strh r0, [r3]
	mov r0, #0x64
	strh r0, [r4]
	pop {r4, pc}
_02229DD8:
	mov r0, #0xa
	strh r0, [r3]
	mov r0, #0x64
	strh r0, [r4]
	pop {r4, pc}
_02229DE2:
	mov r0, #0
	add r2, r3, #0
	add r1, r0, #0
	add r3, r4, #0
	bl MOD08_02217B1C
	pop {r4, pc}
_02229DF0:
	mov r0, #0
	add r2, r3, #0
	add r1, r0, #0
	add r3, r4, #0
	bl MOD08_02217B1C
	pop {r4, pc}
_02229DFE:
	mov r0, #0
	add r2, r3, #0
	add r1, r0, #0
	add r3, r4, #0
	bl MOD08_02217B1C
	pop {r4, pc}
_02229E0C:
	mov r0, #0
	add r2, r3, #0
	add r1, r0, #0
	add r3, r4, #0
	bl MOD08_02217B1C
	pop {r4, pc}
_02229E1A:
	mov r0, #0
	add r2, r3, #0
	add r1, r0, #0
	add r3, r4, #0
	bl MOD08_02217B1C
	pop {r4, pc}
_02229E28:
	mov r0, #0xe6
	strh r0, [r3]
	mov r0, #0x20
	strh r0, [r4]
	pop {r4, pc}
_02229E32:
	mov r0, #0x1d
	mvn r0, r0
	strh r0, [r3]
	mov r0, #0xa0
	strh r0, [r4]
_02229E3C:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD08_02229E40
MOD08_02229E40: ; 0x02229E40
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r0, #0
	add r0, #0xac
	ldr r0, [r0]
	ldr r1, [r5, #0x2c]
	mov r2, #0xa
	bl FUN_0200BBF0
	add r0, r5, #0
	add r0, #0xa8
	ldr r0, [r0]
	cmp r0, #0
	bne _02229E70
	add r0, r5, #0
	add r0, #0xac
	ldr r0, [r0]
	bl FUN_0200BB68
	mov r2, #0x11
	mov r1, #0
	lsl r2, r2, #0x10
	bl FUN_02008D24
_02229E70:
	mov r1, #0
	add r2, sp, #0x1c
	mov r0, #0xa
_02229E76:
	add r1, r1, #1
	stmia r2!, {r0}
	cmp r1, #6
	blt _02229E76
	mov r0, #0
	str r0, [sp, #0x2c]
	str r0, [sp, #0x30]
	add r0, r5, #0
	add r0, #0xac
	ldr r0, [r0]
	ldr r1, [r5, #0x2c]
	add r2, sp, #0x1c
	bl FUN_0200BF60
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	mov r1, #0
	bl MOD08_022281DC
	add r6, r0, #0
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	mov r1, #1
	bl MOD08_022281DC
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	mov r1, #2
	bl MOD08_022281DC
	add r7, r0, #0
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	mov r1, #3
	bl MOD08_022281DC
	str r0, [sp, #0x18]
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x9c
	ldr r1, [r0]
	ldr r0, _02229F60 ; =0x00001770
	mov r2, #0x1b
	add r0, r1, r0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xac
	ldr r0, [r0]
	ldr r1, [r5, #0x2c]
	add r3, r6, #0
	bl FUN_0200C00C
	mov r0, #0x1b
	str r0, [sp]
	add r2, r5, #0
	str r4, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	add r0, r5, #0
	add r0, #0x9c
	ldr r1, [r0]
	ldr r0, _02229F60 ; =0x00001770
	add r2, #0xac
	add r0, r1, r0
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r0, #0xb0
	ldr r0, [r0]
	ldr r2, [r2]
	ldr r3, [r5, #0x2c]
	mov r1, #2
	bl FUN_0200C0DC
	mov r0, #1
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x9c
	ldr r1, [r0]
	ldr r0, _02229F60 ; =0x00001770
	mov r2, #0x1b
	add r0, r1, r0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xac
	ldr r0, [r0]
	ldr r1, [r5, #0x2c]
	add r3, r7, #0
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x9c
	ldr r1, [r0]
	ldr r0, _02229F60 ; =0x00001770
	ldr r3, [sp, #0x18]
	add r0, r1, r0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xac
	ldr r0, [r0]
	ldr r1, [r5, #0x2c]
	mov r2, #0x1b
	bl FUN_0200C13C
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02229F60: .word 0x00001770

	thumb_func_start MOD08_02229F64
MOD08_02229F64: ; 0x02229F64
	push {r3, r4, lr}
	sub sp, #0x34
	add r2, sp, #0
	add r1, sp, #0
	add r2, #2
	add r4, r0, #0
	bl MOD08_02229D00
	mov r0, #0
	add r1, sp, #0
	strh r0, [r1, #4]
	strh r0, [r1, #6]
	mov r1, #1
	str r1, [sp, #0x10]
	add r1, r4, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	add r1, #0xa4
	ldr r1, [r1]
	ldr r2, _02229FE0 ; =0x00001770
	str r1, [sp, #0x2c]
	str r0, [sp, #0x30]
	add r3, sp, #0
_02229F92:
	add r1, r4, #0
	add r1, #0x9c
	ldr r1, [r1]
	add r0, r0, #1
	add r1, r1, r2
	str r1, [r3, #0x14]
	add r3, r3, #4
	cmp r0, #6
	blt _02229F92
	add r0, r4, #0
	add r0, #0xac
	ldr r0, [r0]
	ldr r1, [r4, #0x2c]
	add r2, sp, #0
	bl FUN_0200C154
	str r0, [r4, #0x30]
	mov r1, #1
	bl FUN_0200C644
	ldr r0, [r4, #0x30]
	mov r1, #2
	bl FUN_0200C840
	ldr r0, [r4, #0x30]
	mov r1, #0
	bl FUN_0200C61C
	ldr r0, [r4, #0x30]
	mov r1, #0
	bl FUN_0200C5C0
	ldr r0, [r4, #0x30]
	bl FUN_0200C5A8
	bl MOD08_0221268C
	add sp, #0x34
	pop {r3, r4, pc}
	.align 2, 0
_02229FE0: .word 0x00001770

	thumb_func_start MOD08_02229FE4
MOD08_02229FE4: ; 0x02229FE4
	ldr r3, _02229FEC ; =FUN_0200C644
	ldr r0, [r0, #0x30]
	bx r3
	nop
_02229FEC: .word FUN_0200C644

	thumb_func_start MOD08_02229FF0
MOD08_02229FF0: ; 0x02229FF0
	ldr r3, _02229FF8 ; =FUN_0200C714
	ldr r0, [r0, #0x30]
	bx r3
	nop
_02229FF8: .word FUN_0200C714

	thumb_func_start MOD08_02229FFC
MOD08_02229FFC: ; 0x02229FFC
	ldr r3, _0222A004 ; =FUN_0200C898
	ldr r0, [r0, #0x30]
	bx r3
	nop
_0222A004: .word FUN_0200C898

	thumb_func_start MOD08_0222A008
MOD08_0222A008: ; 0x0222A008
	str r1, [r0, #0x24]
	bx lr

	thumb_func_start MOD08_0222A00C
MOD08_0222A00C: ; 0x0222A00C
	ldr r3, _0222A014 ; =FUN_0200C6C4
	ldr r0, [r0, #0x30]
	bx r3
	nop
_0222A014: .word FUN_0200C6C4

	thumb_func_start MOD08_0222A018
MOD08_0222A018: ; 0x0222A018
	ldr r3, _0222A020 ; =FUN_0200C6B0
	ldr r0, [r0, #0x30]
	bx r3
	nop
_0222A020: .word FUN_0200C6B0

	thumb_func_start MOD08_0222A024
MOD08_0222A024: ; 0x0222A024
	add r0, #0xdc
	str r1, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD08_0222A02C
MOD08_0222A02C: ; 0x0222A02C
	push {r3, lr}
	sub r1, r1, r3
	neg r1, r1
	sub r0, r0, r2
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	asr r1, r1, #0x10
	add r2, r1, #0
	asr r0, r0, #0x10
	mul r2, r1
	add r1, r0, #0
	mul r1, r0
	add r0, r2, r1
	lsl r0, r0, #0xc
	bl FX_Sqrt
	asr r1, r0, #0xb
	lsr r1, r1, #0x14
	add r1, r0, r1
	asr r0, r1, #0xc
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD08_0222A058
MOD08_0222A058: ; 0x0222A058
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl Seal_GetXCoord
	add r4, r0, #0
	add r0, r5, #0
	bl Seal_GetYCoord
	add r1, r0, #0
	add r0, r4, #0
	mov r2, #0xbe
	mov r3, #0x46
	bl MOD08_0222A02C
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_0222A078
MOD08_0222A078: ; 0x0222A078
	push {r4, lr}
	sub sp, #8
	ldr r3, _0222A0D0 ; =0x0222D4D8
	add r4, r0, #0
	add r2, sp, #0
	mov r1, #7
_0222A084:
	ldrb r0, [r3]
	add r3, r3, #1
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _0222A084
	add r0, r4, #0
	bl Seal_GetId
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02086018
	cmp r0, #0
	bne _0222A0C6
	add r0, r4, #0
	bl MOD08_0222A058
	cmp r0, #0x38
	blt _0222A0B0
	mov r0, #3
	b _0222A0BE
_0222A0B0:
	add r0, r0, #1
	mov r1, #0x14
	bl _s32_div_f
	cmp r0, #3
	blt _0222A0BE
	mov r0, #3
_0222A0BE:
	add r1, sp, #0
	add sp, #8
	ldrb r0, [r1, r0]
	pop {r4, pc}
_0222A0C6:
	add r0, sp, #0
	ldrb r0, [r0, #1]
	add sp, #8
	pop {r4, pc}
	nop
_0222A0D0: .word MOD8_0222D4D8

	thumb_func_start MOD08_0222A0D4
MOD08_0222A0D4: ; 0x0222A0D4
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r1, #0x48
	add r6, r0, #0
	bl AllocFromHeap
	add r4, r0, #0
	bne _0222A0EC
	bl ErrorHandling
	mov r0, #0
	pop {r4, r5, r6, pc}
_0222A0EC:
	bl MOD08_0221268C
	str r6, [r4]
	cmp r5, #0
	beq _0222A0FA
	ldr r0, [r5]
	str r0, [r4, #4]
_0222A0FA:
	mov r1, #0
	add r2, r4, #0
	add r0, r1, #0
_0222A100:
	add r1, r1, #1
	str r0, [r2, #8]
	add r2, r2, #4
	cmp r1, #0x10
	blt _0222A100
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_0222A110
MOD08_0222A110: ; 0x0222A110
	push {r4, r5, r6, lr}
	mov r4, #0
	add r5, r4, #0
	add r3, r0, #0
_0222A118:
	ldr r2, [r3, #8]
	cmp r2, #0
	bne _0222A138
	add r4, r0, #0
	ldr r0, [r0]
	add r4, #8
	lsl r6, r5, #2
	bl MOD08_0222A1A0
	str r0, [r4, r6]
	ldr r0, [r4, r6]
	mov r1, #0
	str r1, [r0, #0x18]
	ldr r4, [r4, r6]
	str r5, [r4]
	b _0222A140
_0222A138:
	add r5, r5, #1
	add r3, r3, #4
	cmp r5, #0x10
	blt _0222A118
_0222A140:
	cmp r4, #0
	bne _0222A148
	bl ErrorHandling
_0222A148:
	add r0, r4, #0
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_0222A14C
MOD08_0222A14C: ; 0x0222A14C
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_0222A154:
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _0222A15E
	bl FreeToHeap
_0222A15E:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x10
	blt _0222A154
	add r0, r6, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_0222A170
MOD08_0222A170: ; 0x0222A170
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_0222A176:
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _0222A194
	ldr r0, [r0, #0x10]
	bl MOD08_02215B40
	ldr r1, [r5, #8]
	ldr r0, [r1, #0x20]
	cmp r0, #0
	beq _0222A194
	ldr r0, [r1, #0x18]
	cmp r0, #0
	beq _0222A194
	bl FUN_0200CAB4
_0222A194:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x10
	blt _0222A176
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_0222A1A0
MOD08_0222A1A0: ; 0x0222A1A0
	push {r4, r5, r6, lr}
	add r6, r1, #0
	mov r1, #0x24
	add r5, r0, #0
	bl AllocFromHeap
	add r4, r0, #0
	bne _0222A1B8
	bl ErrorHandling
	mov r0, #0
	pop {r4, r5, r6, pc}
_0222A1B8:
	str r5, [r4, #4]
	ldr r1, [r6]
	ldr r0, [r6, #4]
	str r1, [r4, #8]
	str r0, [r4, #0xc]
	ldr r0, [r4, #8]
	bl MOD08_0222A260
	str r0, [r4, #0x1c]
	ldr r0, [r4, #4]
	ldr r1, [r4, #8]
	mov r2, #1
	bl MOD08_02215AA4
	str r0, [r4, #0x10]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD08_0222A1DC
MOD08_0222A1DC: ; 0x0222A1DC
	push {r4, lr}
	add r4, r0, #0
	mov r1, #1
	str r1, [r4, #0x20]
	ldr r1, _0222A1FC ; =MOD08_0222A258
	bl MOD08_0222A22C
	mov r2, #0xfa
	ldr r0, _0222A200 ; =MOD08_0222A208
	add r1, r4, #0
	lsl r2, r2, #2
	bl FUN_0200CA44
	str r0, [r4, #0x18]
	pop {r4, pc}
	nop
_0222A1FC: .word MOD08_0222A258
_0222A200: .word MOD08_0222A208

	thumb_func_start MOD08_0222A204
MOD08_0222A204: ; 0x0222A204
	ldr r0, [r0, #0x20]
	bx lr

	thumb_func_start MOD08_0222A208
MOD08_0222A208: ; 0x0222A208
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x10]
	bl FUN_020133C8
	cmp r0, #0
	bne _0222A228
	mov r0, #0
	str r0, [r4, #0x20]
	ldr r0, [r4, #0x10]
	bl MOD08_02215B40
	add r0, r5, #0
	bl FUN_0200CAB4
_0222A228:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD08_0222A22C
MOD08_0222A22C: ; 0x0222A22C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x1c]
	add r6, r1, #0
	mov r4, #0
	cmp r0, #0
	ble _0222A24E
_0222A23A:
	ldr r0, [r5, #0x10]
	add r1, r4, #0
	add r2, r6, #0
	add r3, r5, #0
	bl FUN_020133AC
	ldr r0, [r5, #0x1c]
	add r4, r4, #1
	cmp r4, r0
	blt _0222A23A
_0222A24E:
	ldr r0, [r5, #0x10]
	ldr r1, [r5, #0xc]
	bl FUN_02013440
	pop {r4, r5, r6, pc}

	thumb_func_start MOD08_0222A258
MOD08_0222A258: ; 0x0222A258
	ldr r3, _0222A25C ; =FUN_0201341C
	bx r3
	.align 2, 0
_0222A25C: .word FUN_0201341C

	thumb_func_start MOD08_0222A260
MOD08_0222A260: ; 0x0222A260
	push {r3, r4, r5, lr}
	sub sp, #0x58
	ldr r4, _0222A290 ; =0x0222D4E0
	add r5, r0, #0
	add r3, sp, #0
	mov r2, #0xb
_0222A26C:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222A26C
	sub r0, r5, #5
	cmp r0, #0x16
	blo _0222A284
	bl ErrorHandling
	add sp, #0x58
	mov r0, #0
	pop {r3, r4, r5, pc}
_0222A284:
	lsl r1, r0, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	add sp, #0x58
	pop {r3, r4, r5, pc}
	nop
_0222A290: .word MOD8_0222D4E0

	thumb_func_start MOD08_0222A294
MOD08_0222A294: ; 0x0222A294
	push {r3, lr}
	add r3, r1, #0
	ldr r1, [r0]
	mov r2, #0
	bl MOD08_0222A2B4
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD08_0222A2A4
MOD08_0222A2A4: ; 0x0222A2A4
	push {r3, lr}
	add r3, r1, #0
	ldr r1, [r0, #4]
	mov r2, #1
	bl MOD08_0222A2B4
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD08_0222A2B4
MOD08_0222A2B4: ; 0x0222A2B4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #0x18]
	add r7, r2, #0
	str r3, [sp, #0x10]
	bl FUN_020080E0
	ldr r0, [r5, #4]
	lsl r1, r0, #1
	add r1, r5, r1
	ldrh r6, [r1, #0x28]
	add r1, r5, r0
	add r1, #0x30
	ldrb r1, [r1]
	add r2, r5, r0
	add r2, #0x38
	str r1, [sp, #0x1c]
	add r1, r5, r0
	lsl r0, r0, #2
	ldrb r2, [r2]
	add r0, r5, r0
	add r1, #0x34
	ldr r0, [r0, #0x3c]
	ldrb r1, [r1]
	str r2, [sp, #0x18]
	str r0, [sp, #0x14]
	cmp r7, #0
	beq _0222A30A
	add r0, r5, r4
	add r0, #0x4c
	ldrb r2, [r0]
	mov r0, #1
	tst r0, r2
	beq _0222A306
	mov r4, #0
	b _0222A31C
_0222A306:
	mov r4, #2
	b _0222A31C
_0222A30A:
	add r0, r5, r4
	add r0, #0x4c
	ldrb r2, [r0]
	mov r0, #1
	tst r0, r2
	beq _0222A31A
	mov r4, #2
	b _0222A31C
_0222A31A:
	mov r4, #0
_0222A31C:
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [sp, #0x18]
	ldr r2, [sp, #0x1c]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	ldr r0, [sp, #0x14]
	lsl r1, r6, #0x10
	lsl r2, r2, #0x18
	lsl r3, r4, #0x18
	str r0, [sp, #8]
	add r0, sp, #0x28
	lsr r1, r1, #0x10
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02068C00
	ldr r0, [r5]
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #0x18]
	bl FUN_020081C0
	add r7, r0, #0
	add r3, sp, #0x28
	add r2, r7, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r5]
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #0x18]
	bl FUN_020080D0
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x10]
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r4, [sp, #8]
	ldrh r0, [r7, #6]
	str r0, [sp, #0xc]
	ldr r3, [r5]
	ldrh r0, [r7]
	lsl r3, r3, #2
	add r3, r5, r3
	ldr r3, [r3, #8]
	ldrh r1, [r7, #2]
	ldr r3, [r3]
	bl FUN_02012560
	ldr r1, [r5]
	ldr r3, [sp, #0x18]
	lsl r1, r1, #2
	add r1, r5, r1
	lsl r2, r4, #0x18
	lsl r3, r3, #0x18
	ldrh r0, [r7]
	ldr r1, [r1, #8]
	lsr r2, r2, #0x18
	str r0, [r1, #4]
	ldr r1, [r5]
	ldrh r0, [r7, #4]
	lsl r1, r1, #2
	add r1, r5, r1
	ldr r1, [r1, #8]
	lsr r3, r3, #0x18
	str r0, [r1, #8]
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x1c]
	str r0, [sp]
	lsl r0, r6, #0x10
	lsl r1, r1, #0x18
	lsr r0, r0, #0x10
	lsr r1, r1, #0x18
	bl FUN_02068E88
	ldr r1, [r5]
	lsl r1, r1, #2
	add r1, r5, r1
	ldr r1, [r1, #8]
	str r0, [r1, #0xc]
	ldr r0, [r5]
	lsl r1, r0, #2
	add r1, r5, r1
	ldr r1, [r1, #8]
	add r0, r5, r0
	ldr r1, [r1, #0xc]
	add r0, #0x4c
	lsl r1, r1, #0x18
	asr r7, r1, #0x18
	ldrb r0, [r0]
	mov r1, #1
	bl MOD08_0222A6A4
	str r0, [sp, #0x20]
	ldr r0, [r5]
	ldr r2, [sp, #0x20]
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #0x18]
	mov r1, #1
	add r2, r2, r7
	bl FUN_02007558
	cmp r4, #2
	bne _0222A48E
	mov r0, #1
	str r0, [sp]
	add r0, sp, #0x24
	add r0, #2
	mov r1, #0x8a
	mov r2, #0
	add r3, r6, #0
	bl ReadFromNarcMemberByIdPair
	mov r0, #1
	str r0, [sp]
	add r0, sp, #0x24
	add r0, #1
	mov r1, #0x90
	mov r2, #0
	add r3, r6, #0
	bl ReadFromNarcMemberByIdPair
	mov r0, #1
	str r0, [sp]
	add r0, sp, #0x24
	mov r1, #0x8e
	mov r2, #0
	add r3, r6, #0
	bl ReadFromNarcMemberByIdPair
	ldr r0, [r5]
	add r2, sp, #0x24
	lsl r0, r0, #2
	add r0, r5, r0
	ldrb r2, [r2]
	ldr r0, [r0, #0x18]
	mov r1, #0x2e
	bl FUN_02007558
	ldr r0, [r5]
	ldr r2, [sp, #0x20]
	lsl r0, r0, #2
	add r0, r5, r0
	add r2, #0x24
	ldr r0, [r0, #0x18]
	mov r1, #0x14
	str r2, [sp, #0x20]
	bl FUN_02007558
	ldr r0, [r5]
	add r3, sp, #0x24
	lsl r0, r0, #2
	mov r2, #1
	add r0, r5, r0
	ldrsb r2, [r3, r2]
	ldr r0, [r0, #0x18]
	mov r1, #0x15
	bl FUN_02007558
	ldr r0, [r5]
	mov r2, #0x24
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #0x18]
	mov r1, #0x16
	sub r2, r2, r7
	bl FUN_02007558
	ldr r0, [r5]
	add r3, sp, #0x24
	lsl r0, r0, #2
	mov r2, #2
	add r0, r5, r0
	ldrsb r2, [r3, r2]
	ldr r0, [r0, #0x18]
	mov r1, #0x29
	bl FUN_02007558
_0222A48E:
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_0222A494
MOD08_0222A494: ; 0x0222A494
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	ldr r0, [r5]
	str r1, [sp, #0x10]
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #0x18]
	bl FUN_0200813C
	ldr r0, [r5]
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #0x18]
	bl FUN_020081C0
	add r4, r0, #0
	ldr r0, [r5]
	lsl r1, r0, #1
	add r1, r5, r1
	ldrh r1, [r1, #0x28]
	lsl r3, r0, #2
	str r1, [sp, #0x1c]
	add r1, r5, r0
	add r1, #0x30
	ldrb r1, [r1]
	str r1, [sp, #0x18]
	add r1, r5, r0
	add r1, #0x38
	ldrb r1, [r1]
	add r0, r5, r0
	add r0, #0x4c
	str r1, [sp, #0x14]
	add r1, r5, r3
	ldr r7, [r1, #0x3c]
	ldrb r1, [r0]
	mov r0, #1
	tst r0, r1
	beq _0222A4E6
	mov r6, #2
	b _0222A4E8
_0222A4E6:
	mov r6, #0
_0222A4E8:
	str r7, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r6, [sp, #8]
	ldrh r0, [r4, #6]
	add r3, r5, r3
	ldr r2, [sp, #0x10]
	str r0, [sp, #0xc]
	ldr r3, [r3, #8]
	ldrh r0, [r4]
	ldrh r1, [r4, #2]
	ldr r3, [r3]
	bl FUN_02012560
	ldr r1, [r5]
	ldrh r0, [r4]
	lsl r1, r1, #2
	add r1, r5, r1
	ldr r1, [r1, #8]
	ldr r3, [sp, #0x14]
	str r0, [r1, #4]
	ldr r1, [r5]
	lsl r2, r6, #0x18
	lsl r1, r1, #2
	add r1, r5, r1
	lsl r3, r3, #0x18
	ldrh r0, [r4, #4]
	ldr r1, [r1, #8]
	lsr r2, r2, #0x18
	str r0, [r1, #8]
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	lsl r0, r0, #0x10
	lsl r1, r1, #0x18
	str r7, [sp]
	lsr r0, r0, #0x10
	lsr r1, r1, #0x18
	lsr r3, r3, #0x18
	bl FUN_02068E88
	ldr r1, [r5]
	lsl r1, r1, #2
	add r1, r5, r1
	ldr r1, [r1, #8]
	str r0, [r1, #0xc]
	ldr r0, [r5]
	mov r1, #1
	lsl r4, r0, #2
	add r0, r5, r0
	add r0, #0x4c
	ldrb r0, [r0]
	bl MOD08_0222A6A4
	add r1, r5, r4
	add r2, r0, #0
	ldr r0, [r1, #8]
	ldr r3, [r0, #0xc]
	ldr r0, [r1, #0x18]
	mov r1, #1
	add r2, r3, r2
	bl FUN_02007558
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD08_0222A568
MOD08_0222A568: ; 0x0222A568
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5]
	add r6, r1, #0
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #0x18]
	bl FUN_020080E0
	mov r0, #0x75
	add r2, sp, #0
	strh r0, [r2, #4]
	mov r0, #0xd2
	strh r0, [r2, #8]
	mov r0, #0
	strh r0, [r2, #0xa]
	strb r0, [r2, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5]
	add r1, r5, r0
	add r1, #0x4c
	ldrb r3, [r1]
	mov r1, #1
	tst r1, r3
	beq _0222A5A4
	mov r1, #0xd1
	strh r1, [r2, #6]
	mov r4, #0x87
	b _0222A5AA
_0222A5A4:
	mov r1, #0xd0
	strh r1, [r2, #6]
	mov r4, #0x86
_0222A5AA:
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #0x18]
	bl FUN_020081C0
	add r7, r0, #0
	add r3, sp, #4
	add r2, r7, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r5]
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #0x18]
	bl FUN_020080D0
	ldr r3, [r5]
	ldrh r0, [r7]
	lsl r3, r3, #2
	add r3, r5, r3
	ldr r3, [r3, #8]
	ldrh r1, [r7, #2]
	ldr r3, [r3]
	add r2, r6, #0
	bl FUN_02012420
	ldr r2, [r5]
	add r1, sp, #0
	lsl r2, r2, #2
	add r2, r5, r2
	ldrh r0, [r1, #4]
	ldr r2, [r2, #8]
	str r0, [r2, #4]
	ldr r0, [r5]
	ldrh r1, [r1, #8]
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #8]
	add r2, r4, #0
	str r1, [r0, #8]
	add r0, sp, #0
	mov r1, #0x79
	bl ReadWholeNarcMemberByIdPair
	add r0, sp, #0
	ldrb r1, [r0]
	ldr r0, [r5]
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #8]
	str r1, [r0, #0xc]
	ldr r0, [r5]
	mov r1, #1
	lsl r4, r0, #2
	add r0, r5, r0
	add r0, #0x4c
	ldrb r0, [r0]
	bl MOD08_0222A6A4
	add r2, r5, r4
	ldr r1, [r2, #8]
	ldr r1, [r1, #0xc]
	add r4, r1, r0
	ldr r0, [r2, #0x18]
	mov r1, #1
	add r2, r4, #0
	bl FUN_02007558
	ldr r1, [r5]
	mov r2, #1
	add r0, r5, r1
	add r0, #0x4c
	ldrb r0, [r0]
	tst r0, r2
	beq _0222A69E
	lsl r0, r1, #2
	add r0, r5, r0
	ldr r0, [r0, #0x18]
	mov r1, #0x2e
	bl FUN_02007558
	ldr r0, [r5]
	add r2, sp, #0
	ldrb r3, [r2]
	lsl r0, r0, #2
	add r0, r5, r0
	mov r2, #0x24
	sub r2, r2, r3
	ldr r0, [r0, #0x18]
	mov r1, #0x14
	add r2, r4, r2
	bl FUN_02007558
	ldr r0, [r5]
	mov r1, #0x15
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #0x18]
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r5]
	add r2, sp, #0
	lsl r0, r0, #2
	ldrb r3, [r2]
	add r0, r5, r0
	mov r2, #0x24
	ldr r0, [r0, #0x18]
	mov r1, #0x16
	sub r2, r2, r3
	bl FUN_02007558
	ldr r0, [r5]
	mov r1, #0x29
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r0, [r0, #0x18]
	mov r2, #0
	bl FUN_02007558
_0222A69E:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD08_0222A6A4
MOD08_0222A6A4: ; 0x0222A6A4
	cmp r1, #0
	bne _0222A6B0
	lsl r1, r0, #2
	ldr r0, _0222A6C0 ; =MOD8_0222D538
	ldrsh r0, [r0, r1]
	bx lr
_0222A6B0:
	mov r2, #6
	mul r2, r0
	ldr r0, _0222A6C4 ; =MOD8_0222D550
	lsl r1, r1, #1
	add r0, r0, r2
	ldrsh r0, [r1, r0]
	bx lr
	nop
_0222A6C0: .word MOD8_0222D538
_0222A6C4: .word MOD8_0222D550

	thumb_func_start MOD08_0222A6C8
MOD08_0222A6C8: ; 0x0222A6C8
	ldr r1, _0222A75C ; =0x0000013B
	cmp r0, r1
	bhi _0222A6F6
	bhs _0222A754
	cmp r0, #0x7d
	bhi _0222A6E4
	bhs _0222A754
	cmp r0, #0x63
	bhi _0222A6DE
	beq _0222A754
	b _0222A758
_0222A6DE:
	cmp r0, #0x78
	beq _0222A754
	b _0222A758
_0222A6E4:
	cmp r0, #0xc9
	bhi _0222A6F0
	bhs _0222A754
	cmp r0, #0x9f
	beq _0222A754
	b _0222A758
_0222A6F0:
	cmp r0, #0xd7
	beq _0222A754
	b _0222A758
_0222A6F6:
	add r2, r1, #0
	add r2, #0x4a
	cmp r0, r2
	bhi _0222A71E
	add r2, r1, #0
	add r2, #0x4a
	cmp r0, r2
	bhs _0222A754
	add r2, r1, #0
	add r2, #0x14
	cmp r0, r2
	bhi _0222A716
	add r1, #0x14
	cmp r0, r1
	beq _0222A754
	b _0222A758
_0222A716:
	add r1, #0x2c
	cmp r0, r1
	beq _0222A754
	b _0222A758
_0222A71E:
	add r2, r1, #0
	add r2, #0x98
	cmp r0, r2
	bhi _0222A74E
	add r2, r1, #0
	add r2, #0x98
	cmp r0, r2
	bhs _0222A754
	add r2, r1, #0
	add r2, #0x5c
	cmp r0, r2
	bhi _0222A758
	add r2, r1, #0
	add r2, #0x5b
	cmp r0, r2
	blo _0222A758
	add r2, r1, #0
	add r2, #0x5b
	cmp r0, r2
	beq _0222A754
	add r1, #0x5c
	cmp r0, r1
	beq _0222A754
	b _0222A758
_0222A74E:
	add r1, #0x99
	cmp r0, r1
	bne _0222A758
_0222A754:
	mov r0, #0
	bx lr
_0222A758:
	mov r0, #1
	bx lr
	.align 2, 0
_0222A75C: .word 0x0000013B

	.rodata
	.global MOD8_0222A760
MOD8_0222A760: ; 0x0222A760
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0xD7, 0x6A, 0x75, 0x66, 0x33, 0x62, 0x8F, 0x51, 0x6D, 0x4D, 0x6C, 0x41
	.byte 0x2A, 0x2D, 0x19, 0x73, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A780
MOD8_0222A780: ; 0x0222A780
	.byte 0xCD, 0x75, 0x39, 0x77, 0xAD, 0x49, 0x8C, 0x3D, 0x6A, 0x35, 0x29, 0x29, 0x08, 0x21, 0x42, 0x14
	.byte 0x22, 0x10, 0xF0, 0x49, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A7A0
MOD8_0222A7A0: ; 0x0222A7A0
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0x90, 0x39, 0x6F, 0x35, 0x4D, 0x2D, 0x4C, 0x29, 0x2B, 0x25, 0x09, 0x04
	.byte 0x06, 0x04, 0x74, 0x29, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A7C0
MOD8_0222A7C0: ; 0x0222A7C0
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0x75, 0x6D, 0xF1, 0x64, 0x6C, 0x5C, 0x08, 0x50, 0x86, 0x48, 0x00, 0x00
	.byte 0x00, 0x00, 0x7A, 0x5A, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A7E0
MOD8_0222A7E0: ; 0x0222A7E0
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0x94, 0x7F, 0x51, 0x7B, 0x0D, 0x77, 0xAA, 0x72, 0x67, 0x6E, 0x00, 0x00
	.byte 0x00, 0x00, 0xF7, 0x7F, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A800
MOD8_0222A800: ; 0x0222A800
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0xFF, 0x7D, 0x9F, 0x71, 0x3E, 0x61, 0xFD, 0x50, 0x9C, 0x40, 0x33, 0x50
	.byte 0x4F, 0x3C, 0xDF, 0x7E, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A820
MOD8_0222A820: ; 0x0222A820
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0xBF, 0x3F, 0x9F, 0x2B, 0x9F, 0x1B, 0x1C, 0x03, 0x99, 0x02, 0x14, 0x06
	.byte 0xB0, 0x05, 0xDF, 0x4F, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A840
MOD8_0222A840: ; 0x0222A840
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0xAF, 0x23, 0x6C, 0x1B, 0x09, 0x0F, 0xC6, 0x02, 0x67, 0x02, 0xE6, 0x01
	.byte 0x65, 0x05, 0xF5, 0x3B, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A860
MOD8_0222A860: ; 0x0222A860
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0x72, 0x7F, 0xE4, 0x7E, 0x64, 0x6A, 0xA0, 0x59, 0x60, 0x49, 0x20, 0x39
	.byte 0xC1, 0x28, 0xBA, 0x7F, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A880
MOD8_0222A880: ; 0x0222A880
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0xFF, 0x3D, 0x7F, 0x2D, 0xFF, 0x1C, 0x1C, 0x00, 0x19, 0x04, 0x34, 0x08
	.byte 0x4C, 0x08, 0x7F, 0x4E, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A8A0
MOD8_0222A8A0: ; 0x0222A8A0
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0x7A, 0x5A, 0x17, 0x4E, 0xB5, 0x45, 0x72, 0x3D, 0x30, 0x31, 0xED, 0x28
	.byte 0xCB, 0x20, 0xFB, 0x66, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A8C0
MOD8_0222A8C0: ; 0x0222A8C0
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0x9D, 0x77, 0x39, 0x67, 0xD6, 0x5A, 0x52, 0x4E, 0xEF, 0x41, 0x8D, 0x35
	.byte 0x4A, 0x2D, 0x7B, 0x6F, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A8E0
MOD8_0222A8E0: ; 0x0222A8E0
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0xD9, 0x50, 0xD5, 0x48, 0xD2, 0x3C, 0xEE, 0x30, 0xCD, 0x30, 0xAB, 0x24
	.byte 0xA9, 0x20, 0xDE, 0x51, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A900
MOD8_0222A900: ; 0x0222A900
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0x1C, 0x37, 0xFC, 0x26, 0xDC, 0x1A, 0x59, 0x02, 0xF7, 0x01, 0x92, 0x05
	.byte 0x0B, 0x05, 0x5D, 0x4F, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A920
MOD8_0222A920: ; 0x0222A920
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0x76, 0x42, 0x35, 0x36, 0x14, 0x2E, 0x90, 0x19, 0x4F, 0x15, 0x0C, 0x15
	.byte 0xCA, 0x10, 0x18, 0x5B, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A940
MOD8_0222A940: ; 0x0222A940
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0xDE, 0x32, 0x9C, 0x22, 0x3A, 0x12, 0xD8, 0x01, 0x96, 0x01, 0x51, 0x01
	.byte 0xED, 0x04, 0x1F, 0x3F, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A960
MOD8_0222A960: ; 0x0222A960
	.byte 0xB5, 0x56, 0xFF, 0x7F, 0xFC, 0x7D, 0x5B, 0x7D, 0xDA, 0x7C, 0x16, 0x70, 0x12, 0x64, 0x2E, 0x50
	.byte 0x09, 0x3C, 0x1A, 0x7F, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A980
MOD8_0222A980: ; 0x0222A980
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0xAF, 0x7E, 0x4A, 0x7E, 0xE6, 0x7D, 0x40, 0x71, 0x40, 0x65, 0x01, 0x51
	.byte 0xA2, 0x30, 0xF3, 0x7E, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39

	.global MOD8_0222A9A0
MOD8_0222A9A0: ; 0x0222A9A0
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0xDF, 0x3A, 0x9F, 0x2A, 0x5F, 0x1A, 0x9C, 0x01, 0x59, 0x01, 0x14, 0x05
	.byte 0xCF, 0x00, 0xDF, 0x43, 0x08, 0x21, 0x00, 0x00, 0x8C, 0x31, 0xB5, 0x56, 0xBB, 0x53, 0x0A, 0x39
	.byte 0x27, 0x00, 0x27, 0x00, 0x27, 0x00, 0x27, 0x00, 0x27, 0x00, 0x27, 0x00, 0x27, 0x00, 0x27, 0x00
	.byte 0x27, 0x00, 0x27, 0x00, 0x27, 0x00, 0x27, 0x00, 0x27, 0x00, 0x27, 0x00, 0x27, 0x00, 0x27, 0x00
	.byte 0x27, 0x00, 0x27, 0x00

	.global MOD8_0222A9E4
MOD8_0222A9E4: ; 0x0222A9E4
	.word MOD8_0222A760, MOD8_0222A9A0, MOD8_0222A980, MOD8_0222A960
	.word MOD8_0222A940, MOD8_0222A920, MOD8_0222A900, MOD8_0222A8E0
	.word MOD8_0222A8C0, MOD8_0222A8A0, MOD8_0222A880, MOD8_0222A860
	.word MOD8_0222A840, MOD8_0222A820, MOD8_0222A800, MOD8_0222A7E0
	.word MOD8_0222A7C0, MOD8_0222A7A0

	.global MOD8_0222AA2C
MOD8_0222AA2C: ; 0x0222AA2C
	.byte 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x40, 0x00

	.global MOD8_0222AA3C
MOD8_0222AA3C: ; 0x0222AA3C
	.byte 0x03, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00

	.global MOD8_0222AA4C
MOD8_0222AA4C: ; 0x0222AA4C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00

	.global MOD8_0222AA64
MOD8_0222AA64: ; 0x0222AA64
	.word MOD08_02213E3C, MOD08_02214130, MOD08_02214490, MOD08_02213F3C
	.word MOD08_02214258, MOD08_0221449C

	.global MOD8_0222AA7C
MOD8_0222AA7C: ; 0x0222AA7C
	.byte 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222AA94
MOD8_0222AA94: ; 0x0222AA94
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00

	.global MOD8_0222AAAC
MOD8_0222AAAC: ; 0x0222AAAC
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00

	.global MOD8_0222AAC4
MOD8_0222AAC4: ; 0x0222AAC4
	.word MOD08_022125B4, MOD08_022125B8, MOD08_02212614, MOD08_0221261C
	.word MOD08_02212624, MOD08_02212664

	.global MOD8_0222AADC
MOD8_0222AADC: ; 0x0222AADC
	.word MOD08_02214548, MOD08_0221454C, MOD08_022148BC, MOD08_022148D4
	.word MOD08_02214548, MOD08_022145F8, MOD08_022146D0

	.global MOD8_0222AAF8
MOD8_0222AAF8: ; 0x0222AAF8
	.byte 0x20, 0x00, 0x1C, 0x00, 0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0C, 0x00, 0x08, 0x00, 0x04, 0x00
	.byte 0x04, 0x00, 0x08, 0x00, 0x0C, 0x00, 0x10, 0x00, 0x14, 0x00, 0x18, 0x00, 0x1C, 0x00, 0x20, 0x00

	.global MOD8_0222AB18
MOD8_0222AB18: ; 0x0222AB18
	.byte 0xBD, 0x00, 0x00, 0x00, 0xBD, 0x00, 0x00, 0x00, 0x2E, 0x01, 0x00, 0x00, 0x2E, 0x01, 0x00, 0x00
	.byte 0x58, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0xA3, 0x01, 0x00, 0x00, 0x60, 0x01, 0x00, 0x00
	.byte 0xA4, 0x01, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x55, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x22, 0x00, 0x00, 0x00

	.global MOD8_0222AB4C
MOD8_0222AB4C: ; 0x0222AB4C
	.byte 0xFF, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00

	.global MOD8_0222ABDC
MOD8_0222ABDC: ; 0x0222ABDC
	.byte 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00

	.global MOD8_0222AC6C
MOD8_0222AC6C: ; 0x0222AC6C
	.word MOD08_022126DC, MOD08_022126FC, MOD08_02212928, MOD08_02212968
	.word MOD08_022129B4, MOD08_02214B3C, MOD08_022134A0, MOD08_022134A4
	.word MOD08_02214E98, MOD08_02214EC8, MOD08_02213030, MOD08_02213060
	.word MOD08_0221271C, MOD08_0221314C, MOD08_02213280, MOD08_022132B4
	.word MOD08_02214910, MOD08_02214960, MOD08_022149B8, MOD08_02214A0C
	.word MOD08_02214A2C, MOD08_02214A4C, MOD08_02214B70, MOD08_02214BA8
	.word MOD08_02214BC4, MOD08_02214D80, MOD08_02214DE4, MOD08_02214ED0
	.word MOD08_02214E3C, MOD08_02214E40, MOD08_0221308C, MOD08_022134A8
	.word MOD08_02213630, MOD08_022130C4, MOD08_02214AC8, MOD08_02214C64
	.word MOD08_02214CDC, MOD08_02214B28, MOD08_02214B2C, MOD08_02214B30
	.word MOD08_02213C38, MOD08_02213C3C, MOD08_02214B34, MOD08_02214B38
	.word MOD08_02214B54, MOD08_022130EC, MOD08_02212BC4, MOD08_02212C58
	.word MOD08_02212DA8, MOD08_02212E60, MOD08_02212F18, MOD08_02212F58
	.word MOD08_02212FAC, MOD08_02213004, MOD08_02215338, MOD08_022152A8
	.word MOD08_02213658, MOD08_022136D0, MOD08_02213780, MOD08_022139A0
	.word MOD08_022139CC, MOD08_02213BEC, MOD08_02213C00, MOD08_02213C1C
	.word MOD08_02213178, MOD08_022152B0, MOD08_0221530C, MOD08_0221273C
	.word MOD08_022128C0, MOD08_02212904, MOD08_022131BC, MOD08_02213218
	.word MOD08_02213240, MOD08_02214ED4, MOD08_02214F70, MOD08_02214FB4
	.word MOD08_02215010, MOD08_02215054, MOD08_02215098, MOD08_022151A4
	.word MOD08_02215258, MOD08_02215284, MOD08_02213A20, MOD08_02213BD4
	.word MOD08_022126A4

	.global MOD8_0222ADC0
MOD8_0222ADC0: ; 0x0222ADC0
	.byte 0x35, 0x00, 0x00, 0x00, 0xD0, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00
	.byte 0x34, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0xD0, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x33, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0xD0, 0x00, 0x00, 0x00
	.byte 0x32, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00
	.byte 0xD0, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00
	.byte 0x35, 0x00, 0x00, 0x00, 0xD0, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00
	.byte 0x34, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0xEE, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x33, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0xD1, 0x00, 0x00, 0x00
	.byte 0x36, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00
	.byte 0xF2, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00
	.byte 0x39, 0x00, 0x00, 0x00, 0xF5, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00
	.byte 0x38, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0xD2, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00
	.byte 0x3B, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0xD2, 0x00, 0x00, 0x00
	.byte 0x3B, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00
	.byte 0xEC, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00
	.byte 0x3A, 0x00, 0x00, 0x00, 0xED, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00
	.byte 0x3B, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0xF4, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00
	.byte 0x3B, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0xD3, 0x00, 0x00, 0x00
	.byte 0x3C, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00
	.byte 0xD5, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00
	.byte 0x40, 0x00, 0x00, 0x00, 0xDD, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00
	.byte 0x3C, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0xE5, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00
	.byte 0x3C, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0xDD, 0x00, 0x00, 0x00
	.byte 0x3C, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00
	.byte 0xD6, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00
	.byte 0x4D, 0x00, 0x00, 0x00, 0xD8, 0x00, 0x00, 0x00, 0x4A, 0x00, 0x00, 0x00, 0x4B, 0x00, 0x00, 0x00
	.byte 0x4C, 0x00, 0x00, 0x00, 0x53, 0x00, 0x00, 0x00, 0xDA, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
	.byte 0x51, 0x00, 0x00, 0x00, 0x52, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00, 0xDB, 0x00, 0x00, 0x00
	.byte 0x54, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x56, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00
	.byte 0xDC, 0x00, 0x00, 0x00, 0x59, 0x00, 0x00, 0x00, 0x59, 0x00, 0x00, 0x00, 0x59, 0x00, 0x00, 0x00
	.byte 0x5A, 0x00, 0x00, 0x00, 0xDE, 0x00, 0x00, 0x00, 0x5B, 0x00, 0x00, 0x00, 0x5B, 0x00, 0x00, 0x00
	.byte 0x5B, 0x00, 0x00, 0x00, 0x5D, 0x00, 0x00, 0x00, 0xDF, 0x00, 0x00, 0x00, 0x5E, 0x00, 0x00, 0x00
	.byte 0x5E, 0x00, 0x00, 0x00, 0x5C, 0x00, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00
	.byte 0x62, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00
	.byte 0x64, 0x00, 0x00, 0x00, 0xE1, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00
	.byte 0x65, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0xE2, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00
	.byte 0x65, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0xE1, 0x00, 0x00, 0x00
	.byte 0x65, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x6B, 0x00, 0x00, 0x00
	.byte 0xE4, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x69, 0x00, 0x00, 0x00, 0x6A, 0x00, 0x00, 0x00
	.byte 0x6B, 0x00, 0x00, 0x00, 0xE4, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x69, 0x00, 0x00, 0x00
	.byte 0x6A, 0x00, 0x00, 0x00, 0x6B, 0x00, 0x00, 0x00, 0xE4, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00
	.byte 0x69, 0x00, 0x00, 0x00, 0x6A, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00
	.byte 0x71, 0x00, 0x00, 0x00, 0x71, 0x00, 0x00, 0x00, 0x71, 0x00, 0x00, 0x00, 0x75, 0x00, 0x00, 0x00
	.byte 0xEA, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00
	.byte 0x77, 0x00, 0x00, 0x00, 0xEB, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
	.byte 0x79, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00
	.byte 0x7D, 0x00, 0x00, 0x00, 0x7D, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0xF1, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00
	.byte 0xF3, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00
	.byte 0x86, 0x00, 0x00, 0x00, 0xF6, 0x00, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00
	.byte 0x85, 0x00, 0x00, 0x00, 0x8A, 0x00, 0x00, 0x00, 0xF7, 0x00, 0x00, 0x00, 0x87, 0x00, 0x00, 0x00
	.byte 0x88, 0x00, 0x00, 0x00, 0x89, 0x00, 0x00, 0x00, 0x8B, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00
	.byte 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8D, 0x00, 0x00, 0x00
	.byte 0xF9, 0x00, 0x00, 0x00, 0x8E, 0x00, 0x00, 0x00, 0x8E, 0x00, 0x00, 0x00, 0x8E, 0x00, 0x00, 0x00
	.byte 0x8F, 0x00, 0x00, 0x00, 0xFA, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00
	.byte 0x90, 0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0x00, 0xFB, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0x00
	.byte 0x92, 0x00, 0x00, 0x00, 0x93, 0x00, 0x00, 0x00, 0x95, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00
	.byte 0x96, 0x00, 0x00, 0x00, 0x96, 0x00, 0x00, 0x00, 0x96, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00
	.byte 0xCB, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00
	.byte 0x97, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0x99, 0x00, 0x00, 0x00
	.byte 0x98, 0x00, 0x00, 0x00, 0x97, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00
	.byte 0x99, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0x9A, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00
	.byte 0x9C, 0x00, 0x00, 0x00, 0x9B, 0x00, 0x00, 0x00, 0x9B, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00
	.byte 0xD4, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00
	.byte 0x4E, 0x00, 0x00, 0x00, 0xD9, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00
	.byte 0x4F, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0xD7, 0x00, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00
	.byte 0x47, 0x00, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00, 0x66, 0x00, 0x00, 0x00, 0xE3, 0x00, 0x00, 0x00
	.byte 0x67, 0x00, 0x00, 0x00, 0x67, 0x00, 0x00, 0x00, 0x67, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x00, 0x00
	.byte 0xE7, 0x00, 0x00, 0x00, 0x6F, 0x00, 0x00, 0x00, 0x6F, 0x00, 0x00, 0x00, 0x6F, 0x00, 0x00, 0x00
	.byte 0x6C, 0x00, 0x00, 0x00, 0xE6, 0x00, 0x00, 0x00, 0x6D, 0x00, 0x00, 0x00, 0x6D, 0x00, 0x00, 0x00
	.byte 0x6D, 0x00, 0x00, 0x00, 0x7A, 0x00, 0x00, 0x00, 0xEF, 0x00, 0x00, 0x00, 0x7B, 0x00, 0x00, 0x00
	.byte 0x7B, 0x00, 0x00, 0x00, 0x7B, 0x00, 0x00, 0x00

	.global MOD8_0222B248
MOD8_0222B248: ; 0x0222B248
	.word MOD08_02215AA0, MOD08_02215B8C, MOD08_02215C44, MOD08_02215CE4
	.word MOD08_02215CA0, MOD08_02216414, MOD08_02216498, MOD08_02216420
	.word MOD08_0221642C, MOD08_02216438, MOD08_02216444, MOD08_02216450
	.word MOD08_0221645C, MOD08_02216468, MOD08_02216474, MOD08_02216480
	.word MOD08_0221648C, MOD08_022171CC, MOD08_02215E44, MOD08_02215D74
	.word MOD08_02215DDC, MOD08_02215D28, MOD08_02215B88

	.global MOD8_0222B2A4
MOD8_0222B2A4: ; 0x0222B2A4
	.byte 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xF0, 0xFF
	.byte 0xFF, 0x00, 0xF0, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x20, 0x00, 0xFF, 0x00, 0x20, 0x00, 0xFF, 0x00
	.byte 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x10, 0x00, 0xFF, 0x00, 0x04, 0x00, 0xFF, 0x00, 0xFF, 0x00
	.byte 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00

	.global MOD8_0222B2EC
MOD8_0222B2EC: ; 0x0222B2EC
	.byte 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x10, 0x00
	.byte 0xFF, 0x00, 0x10, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00
	.byte 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00
	.byte 0x18, 0x00, 0xFF, 0x00, 0x18, 0x00, 0xFF, 0x00

	.global MOD8_0222B334
MOD8_0222B334: ; 0x0222B334
	.byte 0xE0, 0xF6, 0xFF, 0xFF, 0xA0, 0x05, 0x00, 0x00, 0xE0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222B344
MOD8_0222B344: ; 0x0222B344
	.byte 0x80, 0xE9, 0xFF, 0xFF, 0x00, 0xEF, 0xFF, 0xFF, 0x10, 0x25, 0x00, 0x00, 0x40, 0xF8, 0xFF, 0xFF
	.byte 0x10, 0xD2, 0xFF, 0xFF, 0xD0, 0x0C, 0x00, 0x00, 0xC8, 0x35, 0x00, 0x00, 0x48, 0xFA, 0xFF, 0xFF
	.byte 0x00, 0xEB, 0xFF, 0xFF, 0x08, 0xF5, 0xFF, 0xFF, 0x48, 0x1B, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00

	.global MOD8_0222B374
MOD8_0222B374: ; 0x0222B374
	.byte 0x30, 0x0B, 0x00, 0x00, 0xA8, 0x0E, 0x00, 0x00, 0x80, 0xF4, 0xFF, 0xFF, 0xB0, 0x05, 0x00, 0x00
	.byte 0x18, 0x0B, 0x00, 0x00, 0xAA, 0xFC, 0xFF, 0xFF, 0x50, 0xF1, 0xFF, 0xFF, 0x18, 0xF6, 0xFF, 0xFF
	.byte 0xF0, 0x08, 0x00, 0x00, 0x68, 0x09, 0x00, 0x00, 0x10, 0xF3, 0xFF, 0xFF, 0x28, 0xF5, 0xFF, 0xFF

	.global MOD8_0222B3A4
MOD8_0222B3A4: ; 0x0222B3A4
	.byte 0x00, 0xEE, 0xFF, 0xFF, 0x80, 0xEE, 0xFF, 0xFF, 0xC8, 0x1D, 0x00, 0x00, 0xC8, 0x08, 0x00, 0x00
	.byte 0xC0, 0xDC, 0xFF, 0xFF, 0x36, 0xF4, 0xFF, 0xFF, 0x00, 0x33, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00
	.byte 0x80, 0xF6, 0xFF, 0xFF, 0x40, 0xED, 0xFF, 0xFF, 0x40, 0x18, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00
	.byte 0xA0, 0x1B, 0x00, 0x00, 0xC0, 0xF1, 0xFF, 0xFF

	.global MOD8_0222B3DC
MOD8_0222B3DC: ; 0x0222B3DC
	.byte 0xF4, 0xD4, 0xFF, 0xFF, 0x60, 0xF2, 0xFF, 0xFF, 0x80, 0x2A, 0x00, 0x00, 0xE8, 0x1D, 0x00, 0x00
	.byte 0x2C, 0xC5, 0xFF, 0xFF, 0xA8, 0xF3, 0xFF, 0xFF, 0x98, 0x3A, 0x00, 0x00, 0x48, 0x1C, 0x00, 0x00
	.byte 0xE0, 0xDF, 0xFF, 0xFF, 0x00, 0xEE, 0xFF, 0xFF, 0xE8, 0x20, 0x00, 0x00, 0xC0, 0x22, 0x00, 0x00
	.byte 0x98, 0x3A, 0x00, 0x00, 0x40, 0xF5, 0xFF, 0xFF

	.global MOD8_0222B414
MOD8_0222B414: ; 0x0222B414
	.byte 0x68, 0x0C, 0x00, 0x00, 0xA8, 0x07, 0x00, 0x00, 0xD8, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0xA0, 0x0C, 0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0x20, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x60, 0x17, 0x00, 0x00, 0xC0, 0x09, 0x00, 0x00, 0x40, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x80, 0x0A, 0x00, 0x00, 0x80, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x80, 0xFC, 0xFF, 0xFF, 0x80, 0x01, 0x00, 0x00, 0x20, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x20, 0x09, 0x00, 0x00, 0xA0, 0x05, 0x00, 0x00, 0xE0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x60, 0x07, 0x00, 0x00, 0x40, 0x07, 0x00, 0x00, 0xE0, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222B484
MOD8_0222B484: ; 0x0222B484
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222B488
MOD8_0222B488: ; 0x0222B488
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222B48C
MOD8_0222B48C: ; 0x0222B48C
	.byte 0x00, 0x00, 0x00, 0x00, 0x68, 0x09, 0x00, 0x00, 0xE0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xF8, 0xF9, 0xFF, 0xFF, 0x58, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x07, 0x00, 0x00
	.byte 0x50, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x02, 0x00, 0x00, 0xD0, 0xFD, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x98, 0x07, 0x00, 0x00, 0xA0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xF6, 0xFF, 0xFF, 0xD0, 0xFC, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x88, 0xF6, 0xFF, 0xFF, 0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x98, 0xFC, 0xFF, 0xFF
	.byte 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x68, 0xFA, 0xFF, 0xFF, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD8, 0x05, 0x00, 0x00
	.byte 0x08, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0xD8, 0x05, 0x00, 0x00, 0xB8, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xF8, 0xFF, 0xFF, 0xC8, 0xFC, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0xA0, 0x02, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x80, 0xF8, 0xFF, 0xFF, 0xCC, 0xFB, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222B634
MOD8_0222B634: ; 0x0222B634
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x05, 0x00, 0x00
	.byte 0xE0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0xFB, 0xFF, 0xFF, 0xF0, 0xFC, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0xF8, 0x07, 0x00, 0x00, 0xA0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xA0, 0x03, 0x00, 0x00, 0x98, 0xFD, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x06, 0x00, 0x00
	.byte 0x10, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xE8, 0xF8, 0xFF, 0xFF, 0x68, 0xFD, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xFA, 0xFF, 0xFF, 0x60, 0xFC, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x58, 0xFD, 0xFF, 0xFF, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFB, 0xFF, 0xFF, 0x08, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0xA0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x04, 0x00, 0x00
	.byte 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x90, 0xF9, 0xFF, 0xFF, 0x20, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x18, 0x03, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xFC, 0xFF, 0xFF, 0x60, 0xFC, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222B7E4
MOD8_0222B7E4: ; 0x0222B7E4
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222B7E8
MOD8_0222B7E8: ; 0x0222B7E8
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222B7EC
MOD8_0222B7EC: ; 0x0222B7EC
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x0C, 0x00, 0x00, 0xB8, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x40, 0xF2, 0xFF, 0xFF, 0x48, 0xF8, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x0D, 0x00, 0x00
	.byte 0xC8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0x40, 0xFA, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0xC0, 0x0C, 0x00, 0x00, 0x10, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xF0, 0xFF, 0xFF, 0xF0, 0xFC, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x60, 0xF3, 0xFF, 0xFF, 0x30, 0xF7, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x20, 0xFB, 0xFF, 0xFF
	.byte 0x30, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xC8, 0xFB, 0xFF, 0xFF, 0xD8, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x0C, 0x00, 0x00
	.byte 0x98, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x48, 0x08, 0x00, 0x00, 0x20, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0xF4, 0xFF, 0xFF, 0x60, 0xFA, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x60, 0x07, 0x00, 0x00, 0xB0, 0xFD, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0xE0, 0xF5, 0xFF, 0xFF, 0x70, 0xF5, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222B994
MOD8_0222B994: ; 0x0222B994
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222B998
MOD8_0222B998: ; 0x0222B998
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222B99C
MOD8_0222B99C: ; 0x0222B99C
	.byte 0x00, 0x00, 0x00, 0x00, 0xE0, 0x09, 0x00, 0x00, 0x34, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x58, 0xEF, 0xFF, 0xFF, 0x40, 0xEC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0x0F, 0x00, 0x00
	.byte 0x58, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x02, 0x00, 0x00, 0x60, 0xFD, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0xE0, 0x0A, 0x00, 0x00, 0x60, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0xEF, 0xFF, 0xFF, 0xE8, 0xF9, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xE8, 0xF3, 0xFF, 0xFF, 0x48, 0xF8, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x4C, 0xFD, 0xFF, 0xFF
	.byte 0xE8, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xE8, 0xFC, 0xFF, 0xFF, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0B, 0x00, 0x00
	.byte 0x50, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x60, 0x08, 0x00, 0x00, 0x90, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA8, 0xF4, 0xFF, 0xFF, 0x08, 0xFA, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x68, 0x04, 0x00, 0x00, 0x68, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x88, 0xF8, 0xFF, 0xFF, 0xE8, 0xF7, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222BB44
MOD8_0222BB44: ; 0x0222BB44
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222BB48
MOD8_0222BB48: ; 0x0222BB48
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222BB4C
MOD8_0222BB4C: ; 0x0222BB4C
	.byte 0x00, 0x00, 0x00, 0x00, 0xC0, 0x0E, 0x00, 0x00, 0x40, 0x08, 0x00, 0x00, 0xF8, 0x0B, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x7C, 0xEF, 0xFF, 0xFF, 0x58, 0xF5, 0xFF, 0xFF, 0xF8, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x17, 0x00, 0x00
	.byte 0x30, 0x06, 0x00, 0x00, 0xF8, 0x0B, 0x00, 0x00, 0x10, 0x04, 0x00, 0x00, 0xA8, 0xFD, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0xD0, 0x10, 0x00, 0x00, 0xE8, 0x09, 0x00, 0x00, 0xF8, 0x0B, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xE6, 0xFF, 0xFF, 0x08, 0xF8, 0xFF, 0xFF
	.byte 0xF8, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xE0, 0xEE, 0xFF, 0xFF, 0x68, 0xF4, 0xFF, 0xFF, 0xF8, 0x0B, 0x00, 0x00, 0xC0, 0xFC, 0xFF, 0xFF
	.byte 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x28, 0xF8, 0xFF, 0xFF, 0x78, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC2, 0x0F, 0x00, 0x00
	.byte 0x88, 0x0A, 0x00, 0x00, 0xF8, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x14, 0x0C, 0x00, 0x00, 0xDC, 0x0B, 0x00, 0x00, 0xF8, 0x0B, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0xED, 0xFF, 0xFF, 0x90, 0xF5, 0xFF, 0xFF
	.byte 0xF8, 0x0B, 0x00, 0x00, 0xC0, 0x06, 0x00, 0x00, 0x70, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x70, 0xF2, 0xFF, 0xFF, 0xD8, 0xED, 0xFF, 0xFF, 0xF8, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222BCF4
MOD8_0222BCF4: ; 0x0222BCF4
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222BCF8
MOD8_0222BCF8: ; 0x0222BCF8
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222BCFC
MOD8_0222BCFC: ; 0x0222BCFC
	.byte 0x00, 0x00, 0x00, 0x00, 0xA0, 0x07, 0x00, 0x00, 0x48, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x20, 0xF8, 0xFF, 0xFF, 0x38, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00
	.byte 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x03, 0x00, 0x00, 0x40, 0xFE, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0xC0, 0x06, 0x00, 0x00, 0x40, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD0, 0xF7, 0xFF, 0xFF, 0x18, 0xFD, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xD0, 0xF7, 0xFF, 0xFF, 0x28, 0xFB, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x10, 0xFD, 0xFF, 0xFF
	.byte 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0xFC, 0xFF, 0xFF, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD0, 0x06, 0x00, 0x00
	.byte 0x68, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0xD8, 0x05, 0x00, 0x00, 0xD8, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0xF8, 0xFF, 0xFF, 0x38, 0xFD, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x78, 0x02, 0x00, 0x00, 0x38, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x70, 0xF9, 0xFF, 0xFF, 0x88, 0xF9, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222BEA4
MOD8_0222BEA4: ; 0x0222BEA4
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222BEA8
MOD8_0222BEA8: ; 0x0222BEA8
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222BEAC
MOD8_0222BEAC: ; 0x0222BEAC
	.byte 0x00, 0x00, 0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xC0, 0xF8, 0xFF, 0xFF, 0xB8, 0xF9, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD0, 0x07, 0x00, 0x00
	.byte 0x40, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x02, 0x00, 0x00, 0xD0, 0xFA, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0xD0, 0x07, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xF7, 0xFF, 0xFF, 0x00, 0xFA, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xF0, 0xF7, 0xFF, 0xFF, 0xA8, 0xF8, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xFD, 0xFF, 0xFF
	.byte 0xE8, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xF8, 0xFA, 0xFF, 0xFF, 0x80, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x05, 0x00, 0x00
	.byte 0x40, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0xF8, 0x05, 0x00, 0x00, 0x28, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xFA, 0xFF, 0xFF, 0xE8, 0xF9, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x58, 0x03, 0x00, 0x00, 0x90, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x98, 0xFA, 0xFF, 0xFF, 0x10, 0xF8, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222C054
MOD8_0222C054: ; 0x0222C054
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222C058
MOD8_0222C058: ; 0x0222C058
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222C05C
MOD8_0222C05C: ; 0x0222C05C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xC0, 0xF2, 0xFF, 0xFF, 0x10, 0xF9, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x13, 0x00, 0x00
	.byte 0xF0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x50, 0xFD, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0xC0, 0x0E, 0x00, 0x00, 0xB0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0xEA, 0xFF, 0xFF, 0xC8, 0xF9, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x58, 0xF1, 0xFF, 0xFF, 0x48, 0xF7, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x58, 0xF9, 0xFF, 0xFF
	.byte 0x08, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x28, 0xF8, 0xFF, 0xFF, 0xC0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x0F, 0x00, 0x00
	.byte 0x30, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x54, 0x0A, 0x00, 0x00, 0x70, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0xF1, 0xFF, 0xFF, 0x70, 0xF8, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0xF8, 0x06, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x58, 0xF3, 0xFF, 0xFF, 0x48, 0xF5, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222C204
MOD8_0222C204: ; 0x0222C204
	.word MOD08_022173C8, MOD08_022173CC, MOD08_022174B0, MOD08_022174B4
	.word MOD08_022174B8, MOD08_02217580, MOD08_02217604, MOD08_02217684
	.word MOD08_022176EC, MOD08_022176F0, MOD08_022176F4, MOD08_022176F8
	.word MOD08_022176FC, MOD08_02217808

	.global MOD8_0222C23C
MOD8_0222C23C: ; 0x0222C23C
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00

	.global MOD8_0222C278
MOD8_0222C278: ; 0x0222C278
	.byte 0x00, 0xC2, 0x40, 0x17, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0xE8, 0x00, 0x00
	.byte 0x00, 0xC2, 0x40, 0x17, 0x00, 0x10, 0x00, 0x00, 0x00, 0xD0, 0x00, 0x20, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x20, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x24, 0xA0, 0x0E, 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222C2A8
MOD8_0222C2A8: ; 0x0222C2A8
	.word MOD08_02217904, MOD08_02217928, MOD08_02217964, MOD08_022179A0
	.word MOD08_022179DC, MOD08_02217A3C, MOD08_02217A78, MOD08_02217AB4
	.word MOD08_02217ADC

	.global MOD8_0222C2CC
MOD8_0222C2CC: ; 0x0222C2CC
	.byte 0x40, 0x00

	.global MOD8_0222C2CE
MOD8_0222C2CE: ; 0x0222C2CE
	.byte 0x70, 0x00, 0xC0, 0x00, 0x30, 0x00, 0xD8, 0x00, 0x70, 0x00, 0x50, 0x00, 0x2A, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x70, 0x00, 0xC0, 0x00, 0x30, 0x00, 0x28, 0x00
	.byte 0x70, 0x00, 0xD8, 0x00, 0x32, 0x00, 0x50, 0x00, 0x78, 0x00, 0xB0, 0x00, 0x2A, 0x00, 0x00, 0x00
	.byte 0x00, 0x00

	.global MOD8_0222C300
MOD8_0222C300: ; 0x0222C300
	.word MOD08_02218DCC, MOD08_0221D0EC, MOD08_022220B4, MOD08_0221F7F0
	.word MOD08_02222F28, MOD08_0222324C, MOD08_022234E0, MOD08_0222388C
	.word MOD08_02223B8C, MOD08_02223E58, MOD08_02219A2C, MOD08_022245B4
	.word MOD08_02224C1C, MOD08_02224EE4, MOD08_02225690, MOD08_02225970
	.word MOD08_02225C00, MOD08_0221EED8, MOD08_0222621C, MOD08_0221FA44
	.word MOD08_0221FDE4, MOD08_02220180, MOD08_0222057C, MOD08_022208A0
	.word MOD08_02220F14, MOD08_0221C45C, MOD08_0221C5D0, MOD08_0221C694
	.word MOD08_0221C844, MOD08_022268B8, MOD08_02226C24, MOD08_02226ADC
	.word MOD08_02226FAC

	.global MOD8_0222C384
MOD8_0222C384: ; 0x0222C384
	.word MOD08_02218C70, MOD08_02218C9C, MOD08_02218CEC, MOD08_02218D38
	.word MOD08_022196B8, MOD08_0221D418, MOD08_0221D6E0, MOD08_0221D910
	.word MOD08_022219F4, MOD08_02221C68, MOD08_022197E4, MOD08_02222348
	.word MOD08_02222654, MOD08_0221DC64, MOD08_0221DD68, MOD08_0221DF78
	.word MOD08_0221E0CC, MOD08_022229C8, MOD08_02222A78, MOD08_0221E22C
	.word MOD08_02222CC8, MOD08_0221E344, MOD08_0221E644, MOD08_02223680
	.word MOD08_0221E880, MOD08_022240B8, MOD08_0221E958, MOD08_0221EB7C
	.word MOD08_0221ECB0, MOD08_022246D8, MOD08_022248E8, MOD08_02224260
	.word MOD08_022253B4, MOD08_02219AD8, MOD08_02219C2C, MOD08_02219F6C
	.word MOD08_02218F60, MOD08_02225EFC, MOD08_0221A418, MOD08_0221EE14
	.word MOD08_0221A4C4, MOD08_02226144, MOD08_0221A1E0, MOD08_02226428
	.word MOD08_02219160, MOD08_02219488, MOD08_022264D8, MOD08_022266E4
	.word MOD08_02226860, MOD08_0221F224, MOD08_0221A56C, MOD08_0221A644
	.word MOD08_0221A7D0, MOD08_0221AA7C, MOD08_0221ACBC, MOD08_0222042C
	.word MOD08_0221ADF0, MOD08_0221AF1C, MOD08_02220A94, MOD08_02220D24
	.word MOD08_0221B0B0, MOD08_0221B170, MOD08_0221B38C, MOD08_0221B45C
	.word MOD08_0221B5B4, MOD08_0221BDD8, MOD08_0221C104, MOD08_0221B8E8
	.word MOD08_0221BAC0, MOD08_0221BBB8, MOD08_02221234, MOD08_0222157C
	.word MOD08_0221C2BC, MOD08_0221BF0C, MOD08_0221C888, MOD08_0221CB78
	.word MOD08_0221CEC4, MOD08_0221B264, MOD08_0221CDD4, MOD08_02221870
	.word MOD08_022273B8, MOD08_022273E4, MOD08_02227410, MOD08_0222743C

	.global MOD8_0222C4D4
MOD8_0222C4D4: ; 0x0222C4D4
	.byte 0x05, 0x00, 0x05, 0x00, 0x05, 0x00, 0x05, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x03, 0x00
	.byte 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0xFD, 0xFF, 0xFD, 0xFF, 0xFD, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF
	.byte 0xFC, 0xFF, 0xFB, 0xFF, 0xFB, 0xFF, 0xFB, 0xFF, 0xFB, 0xFF, 0xFB, 0xFF, 0xFB, 0xFF, 0xFB, 0xFF
	.byte 0xFB, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFD, 0xFF, 0xFD, 0xFF, 0xFD, 0xFF, 0x00, 0x00
	.byte 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x05, 0x00, 0x05, 0x00
	.byte 0x05, 0x00, 0x05, 0x00, 0xFF, 0x00, 0x00, 0x00

	.global MOD8_0222C52C
MOD8_0222C52C: ; 0x0222C52C
	.byte 0x02, 0x07, 0x0D, 0x12

	.global MOD8_0222C530
MOD8_0222C530: ; 0x0222C530
	.byte 0x64

	.global MOD8_0222C531
MOD8_0222C531: ; 0x0222C531
	.byte 0x73

	.global MOD8_0222C532
MOD8_0222C532: ; 0x0222C532
	.byte 0x06, 0x73, 0x64, 0x06

	.global MOD8_0222C536
MOD8_0222C536: ; 0x0222C536
	.byte 0x08, 0x02, 0x0D, 0x01, 0x12, 0x03

	.global MOD8_0222C53C
MOD8_0222C53C: ; 0x0222C53C
	.byte 0x00

	.global MOD8_0222C53D
MOD8_0222C53D: ; 0x0222C53D
	.byte 0x10

	.global MOD8_0222C53E
MOD8_0222C53E: ; 0x0222C53E
	.byte 0x05, 0x10, 0x00, 0x05, 0x00, 0x00, 0x05

	.global MOD8_0222C545
MOD8_0222C545: ; 0x0222C545
	.byte 0x01, 0xFF, 0xFF, 0x01, 0x01, 0xFF, 0x01, 0xFF, 0x01, 0xFF

	.global MOD8_0222C54F
MOD8_0222C54F: ; 0x0222C54F
	.byte 0x64

	.global MOD8_0222C550
MOD8_0222C550: ; 0x0222C550
	.byte 0x0A

	.global MOD8_0222C551
MOD8_0222C551: ; 0x0222C551
	.byte 0x64

	.global MOD8_0222C552
MOD8_0222C552: ; 0x0222C552
	.byte 0xB4

	.global MOD8_0222C553
MOD8_0222C553: ; 0x0222C553
	.byte 0x0A, 0x0A, 0x0A, 0xB4, 0x00, 0x05

	.global MOD8_0222C559
MOD8_0222C559: ; 0x0222C559
	.byte 0x64

	.global MOD8_0222C55A
MOD8_0222C55A: ; 0x0222C55A
	.byte 0x78

	.global MOD8_0222C55B
MOD8_0222C55B: ; 0x0222C55B
	.byte 0x64

	.global MOD8_0222C55C
MOD8_0222C55C: ; 0x0222C55C
	.byte 0x50

	.global MOD8_0222C55D
MOD8_0222C55D: ; 0x0222C55D
	.byte 0x05, 0x78, 0x64, 0x50, 0x78, 0x05, 0x64, 0x64, 0x78, 0x64, 0x05

	.global MOD8_0222C568
MOD8_0222C568: ; 0x0222C568
	.byte 0x64

	.global MOD8_0222C569
MOD8_0222C569: ; 0x0222C569
	.byte 0x64

	.global MOD8_0222C56A
MOD8_0222C56A: ; 0x0222C56A
	.byte 0x64

	.global MOD8_0222C56B
MOD8_0222C56B: ; 0x0222C56B
	.byte 0x46

	.global MOD8_0222C56C
MOD8_0222C56C: ; 0x0222C56C
	.byte 0x08, 0x64, 0x64, 0x46, 0x78, 0x03, 0x64, 0x64, 0x78, 0x64, 0x03

	.global MOD8_0222C577
MOD8_0222C577: ; 0x0222C577
	.byte 0x64

	.global MOD8_0222C578
MOD8_0222C578: ; 0x0222C578
	.byte 0x96

	.global MOD8_0222C579
MOD8_0222C579: ; 0x0222C579
	.byte 0x64

	.global MOD8_0222C57A
MOD8_0222C57A: ; 0x0222C57A
	.byte 0x32

	.global MOD8_0222C57B
MOD8_0222C57B: ; 0x0222C57B
	.byte 0x08, 0x96, 0x32, 0x32, 0x96, 0x08, 0x32, 0x64, 0x96, 0x64, 0x08

	.global MOD8_0222C586
MOD8_0222C586: ; 0x0222C586
	.byte 0x0C, 0x00, 0x0A, 0x00, 0x08, 0x00, 0x06, 0x00, 0x04, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD8_0222C596
MOD8_0222C596: ; 0x0222C596
	.byte 0x00, 0x00

	.global MOD8_0222C598
MOD8_0222C598: ; 0x0222C598
	.byte 0x20, 0x00

	.global MOD8_0222C59A
MOD8_0222C59A: ; 0x0222C59A
	.byte 0x07, 0x00, 0x00, 0x00, 0x20, 0x00, 0x0A, 0x00, 0x20, 0x00, 0x00, 0x00, 0x07, 0x00, 0x20, 0x00
	.byte 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00

	.global MOD8_0222C5B0
MOD8_0222C5B0: ; 0x0222C5B0
	.byte 0x38, 0x0E, 0x00, 0x00

	.global MOD8_0222C5B4
MOD8_0222C5B4: ; 0x0222C5B4
	.byte 0x03, 0x00, 0x00, 0x00, 0xAA, 0x0A, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x1C, 0x07, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x8E, 0x03, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00

	.global MOD8_0222C5D8
MOD8_0222C5D8: ; 0x0222C5D8
	.byte 0x05, 0x05, 0x05, 0x03

	.global MOD8_0222C5DC
MOD8_0222C5DC: ; 0x0222C5DC
	.byte 0x14, 0x02, 0x0D, 0x01, 0x12, 0x03

	.global MOD8_0222C5E2
MOD8_0222C5E2: ; 0x0222C5E2
	.byte 0x00, 0x00

	.global MOD8_0222C5E4
MOD8_0222C5E4: ; 0x0222C5E4
	.byte 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xAA, 0x00, 0x80, 0x00
	.byte 0xAA, 0x00, 0x00, 0x01, 0xAA, 0x00

	.global MOD8_0222C5FA
MOD8_0222C5FA: ; 0x0222C5FA
	.byte 0x50, 0x00, 0x32, 0x00, 0xB4, 0x00, 0x32, 0x00, 0x50, 0x00, 0x64, 0x00, 0xB4, 0x00, 0x64, 0x00
	.byte 0x50, 0x00, 0x4B, 0x00, 0xB4, 0x00, 0x4B, 0x00

	.global MOD8_0222C612
MOD8_0222C612: ; 0x0222C612
	.byte 0x78, 0x00

	.global MOD8_0222C614
MOD8_0222C614: ; 0x0222C614
	.byte 0x50, 0x00

	.global MOD8_0222C616
MOD8_0222C616: ; 0x0222C616
	.byte 0x88, 0x00

	.global MOD8_0222C618
MOD8_0222C618: ; 0x0222C618
	.byte 0x50, 0x00, 0x78, 0x00, 0x50, 0x00, 0x88, 0x00, 0x50, 0x00, 0x78, 0x00, 0x50, 0x00, 0x88, 0x00
	.byte 0x50, 0x00, 0x58, 0x00, 0x50, 0x00, 0xA8, 0x00, 0x50, 0x00

	.global MOD8_0222C632
MOD8_0222C632: ; 0x0222C632
	.byte 0x1E, 0x00, 0x28, 0x00, 0x32, 0x00, 0x35, 0x00, 0x1E, 0x00, 0x5D, 0x00, 0x32, 0x00, 0x35, 0x00
	.byte 0x1E, 0x00, 0x92, 0x00, 0x32, 0x00, 0x35, 0x00, 0x50, 0x00, 0x28, 0x00, 0x32, 0x00, 0x35, 0x00
	.byte 0x50, 0x00, 0x5D, 0x00, 0x32, 0x00, 0x35, 0x00, 0x50, 0x00, 0x92, 0x00, 0x32, 0x00, 0x35, 0x00
	.byte 0x00, 0x00

	.global MOD8_0222C664
MOD8_0222C664: ; 0x0222C664
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00

	.global MOD8_0222C670
MOD8_0222C670: ; 0x0222C670
	.byte 0x30, 0x00, 0x00, 0x00

	.global MOD8_0222C674
MOD8_0222C674: ; 0x0222C674
	.byte 0xCF, 0x00, 0x00, 0x00

	.global MOD8_0222C678
MOD8_0222C678: ; 0x0222C678
	.byte 0x31, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x00, 0x00, 0xCC, 0x00, 0x00, 0x00
	.byte 0x2B, 0x00, 0x00, 0x00, 0x2B, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0xCD, 0x00, 0x00, 0x00
	.byte 0x2D, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0xCE, 0x00, 0x00, 0x00
	.byte 0x2F, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x4D, 0x00, 0x00
	.byte 0x00, 0xF0, 0xFF, 0xFF

	.global MOD8_0222C6BC
MOD8_0222C6BC: ; 0x0222C6BC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222C6C8
MOD8_0222C6C8: ; 0x0222C6C8
	.byte 0x40, 0x00, 0x70, 0x00, 0xC0, 0x00, 0x30, 0x00, 0x28, 0x00, 0x70, 0x00, 0xD8, 0x00, 0x32, 0x00
	.byte 0x50, 0x00, 0x78, 0x00, 0xB0, 0x00, 0x2A, 0x00

	.global MOD8_0222C6E0
MOD8_0222C6E0: ; 0x0222C6E0
	.byte 0xD8, 0x00, 0x70, 0x00, 0x50, 0x00, 0x2A, 0x00, 0xD8, 0x00, 0x70, 0x00, 0x50, 0x00, 0x2A, 0x00
	.byte 0xD8, 0x00, 0x70, 0x00, 0x50, 0x00, 0x2A, 0x00

	.global MOD8_0222C6F8
MOD8_0222C6F8: ; 0x0222C6F8
	.byte 0x70, 0xDA, 0xFF, 0xFF, 0xA8, 0xEA, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x00, 0xD8, 0xFF, 0xFF
	.byte 0x00, 0xE7, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x80, 0xF0, 0xFF, 0xFF, 0x00, 0xF3, 0xFF, 0xFF
	.byte 0x40, 0x00, 0x00, 0x00, 0x58, 0xE6, 0xFF, 0xFF, 0x60, 0xF0, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00
	.byte 0x80, 0xF0, 0xFF, 0xFF, 0x00, 0xF3, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00, 0xC0, 0xE5, 0xFF, 0xFF
	.byte 0x60, 0xE9, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x48, 0xDE, 0xFF, 0xFF, 0xE8, 0xE4, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x48, 0xDE, 0xFF, 0xFF, 0xE8, 0xE4, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0xCF, 0xFF, 0xFF, 0x00, 0xF1, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCF, 0xFF, 0xFF
	.byte 0x00, 0xF1, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x60, 0xDA, 0xFF, 0xFF, 0x20, 0xE9, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x60, 0xDA, 0xFF, 0xFF, 0x20, 0xE9, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0xD0, 0xEF, 0xFF, 0xFF, 0xB0, 0xEB, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xD0, 0xEF, 0xFF, 0xFF
	.byte 0xB0, 0xEB, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x40, 0xCF, 0xFF, 0xFF, 0x40, 0xEF, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x40, 0xCF, 0xFF, 0xFF, 0x40, 0xEF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0xF9, 0xFF, 0xFF, 0x80, 0xEF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF9, 0xFF, 0xFF
	.byte 0x80, 0xEF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x80, 0xDF, 0xFF, 0xFF, 0xC0, 0xEF, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0xDF, 0xFF, 0xFF, 0xC0, 0xEF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x78, 0x23, 0x00, 0x00, 0xA0, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x23, 0x00, 0x00
	.byte 0xA0, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0xE7, 0xFF, 0xFF, 0x80, 0xF4, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x98, 0xE7, 0xFF, 0xFF, 0x80, 0xF4, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x30, 0x2B, 0x00, 0x00, 0x30, 0x11, 0x00, 0x00, 0x80, 0xEB, 0xFF, 0xFF, 0x00, 0x28, 0x00, 0x00
	.byte 0x00, 0x0C, 0x00, 0x00, 0x80, 0xEB, 0xFF, 0xFF, 0x80, 0x24, 0x00, 0x00, 0x80, 0x08, 0x00, 0x00
	.byte 0x80, 0xEB, 0xFF, 0xFF, 0x60, 0x22, 0x00, 0x00, 0x40, 0x19, 0x00, 0x00, 0x80, 0xEB, 0xFF, 0xFF
	.byte 0x80, 0x24, 0x00, 0x00, 0x80, 0x08, 0x00, 0x00, 0x80, 0xEB, 0xFF, 0xFF, 0xC0, 0x38, 0x00, 0x00
	.byte 0x60, 0x1F, 0x00, 0x00, 0x80, 0xEB, 0xFF, 0xFF, 0x68, 0x32, 0x00, 0x00, 0xF4, 0x13, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x68, 0x32, 0x00, 0x00, 0xF4, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x38, 0x15, 0x00, 0x00, 0x18, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x15, 0x00, 0x00
	.byte 0x18, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0x33, 0x00, 0x00, 0x08, 0x2C, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x58, 0x33, 0x00, 0x00, 0x08, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xD0, 0x40, 0x00, 0x00, 0x30, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD0, 0x40, 0x00, 0x00
	.byte 0x30, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x33, 0x00, 0x00, 0xC0, 0x1D, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x33, 0x00, 0x00, 0xC0, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x42, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00
	.byte 0x00, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x2A, 0x00, 0x00, 0x80, 0x11, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x2A, 0x00, 0x00, 0x80, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xE8, 0xE4, 0xFF, 0xFF, 0x20, 0xED, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE8, 0xE4, 0xFF, 0xFF
	.byte 0x20, 0xED, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x58, 0x20, 0x00, 0x00, 0x38, 0x15, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x58, 0x20, 0x00, 0x00, 0x38, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xA8, 0xC5, 0xFF, 0xFF, 0x58, 0xEC, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x00, 0xC4, 0xFF, 0xFF
	.byte 0x80, 0xE7, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x80, 0xD9, 0xFF, 0xFF, 0x80, 0xF3, 0xFF, 0xFF
	.byte 0x40, 0x00, 0x00, 0x00, 0x78, 0xD3, 0xFF, 0xFF, 0x80, 0xF4, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00
	.byte 0x80, 0xD9, 0xFF, 0xFF, 0x80, 0xF3, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x80, 0xD9, 0xFF, 0xFF
	.byte 0x80, 0xF3, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x10, 0xDB, 0xFF, 0xFF, 0xE0, 0xF3, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x10, 0xDB, 0xFF, 0xFF, 0xE0, 0xF3, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x40, 0xBA, 0xFF, 0xFF, 0xD8, 0xF1, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x40, 0xBA, 0xFF, 0xFF
	.byte 0xD8, 0xF1, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xD0, 0xCE, 0xFF, 0xFF, 0x60, 0xF4, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0xD0, 0xCE, 0xFF, 0xFF, 0x60, 0xF4, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x22, 0xE7, 0xFF, 0xFF, 0x40, 0xF1, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x22, 0xE7, 0xFF, 0xFF
	.byte 0x40, 0xF1, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC5, 0xFF, 0xFF, 0x80, 0xF7, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC5, 0xFF, 0xFF, 0x80, 0xF7, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x40, 0xE8, 0xFF, 0xFF, 0x80, 0xEA, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x40, 0xE8, 0xFF, 0xFF
	.byte 0x80, 0xEA, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD1, 0xFF, 0xFF, 0x80, 0xF3, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0xD1, 0xFF, 0xFF, 0x80, 0xF3, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x48, 0x2A, 0x00, 0x00, 0x40, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x2A, 0x00, 0x00
	.byte 0x40, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xD9, 0xFF, 0xFF, 0x80, 0xF3, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0xD9, 0xFF, 0xFF, 0x80, 0xF3, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0xC8, 0x1C, 0x00, 0x00, 0x48, 0x17, 0x00, 0x00, 0x80, 0xEB, 0xFF, 0xFF, 0x00, 0x35, 0x00, 0x00
	.byte 0x80, 0x0B, 0x00, 0x00, 0x80, 0xEB, 0xFF, 0xFF, 0x00, 0x35, 0x00, 0x00, 0x80, 0x0B, 0x00, 0x00
	.byte 0x80, 0xEB, 0xFF, 0xFF, 0x70, 0x31, 0x00, 0x00, 0x68, 0x16, 0x00, 0x00, 0x80, 0xEB, 0xFF, 0xFF
	.byte 0x00, 0x35, 0x00, 0x00, 0x80, 0x0B, 0x00, 0x00, 0x80, 0xEB, 0xFF, 0xFF, 0x00, 0x35, 0x00, 0x00
	.byte 0x80, 0x0B, 0x00, 0x00, 0x80, 0xEB, 0xFF, 0xFF, 0x40, 0x46, 0x00, 0x00, 0xC0, 0x18, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x40, 0x46, 0x00, 0x00, 0xC0, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x58, 0x1F, 0x00, 0x00, 0x78, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0x1F, 0x00, 0x00
	.byte 0x78, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x33, 0x00, 0x00, 0x40, 0x18, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x10, 0x33, 0x00, 0x00, 0x40, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x44, 0x00, 0x00, 0x40, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00
	.byte 0x40, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0xC0, 0x1C, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0xC0, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xC0, 0x50, 0x00, 0x00, 0x98, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x50, 0x00, 0x00
	.byte 0x98, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x34, 0x00, 0x00, 0x20, 0x15, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x34, 0x00, 0x00, 0x20, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xC0, 0xDA, 0xFF, 0xFF, 0xD0, 0xF3, 0xFF, 0xFF, 0xA8, 0x0A, 0x00, 0x00, 0xC0, 0xDA, 0xFF, 0xFF
	.byte 0xD0, 0xF3, 0xFF, 0xFF, 0xA8, 0x0A, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x80, 0x0B, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x80, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x0C, 0xEB, 0xFF, 0xFF, 0x58, 0xE6, 0xFF, 0xFF, 0x00, 0xFC, 0xFF, 0xFF, 0x80, 0xE2, 0xFF, 0xFF
	.byte 0x00, 0xE5, 0xFF, 0xFF, 0x00, 0xFC, 0xFF, 0xFF, 0xFC, 0xF6, 0xFF, 0xFF, 0x00, 0xEA, 0xFF, 0xFF
	.byte 0x00, 0xFC, 0xFF, 0xFF, 0x58, 0xF4, 0xFF, 0xFF, 0x68, 0xEB, 0xFF, 0xFF, 0x00, 0xFC, 0xFF, 0xFF
	.byte 0xFC, 0xF6, 0xFF, 0xFF, 0x00, 0xEA, 0xFF, 0xFF, 0x00, 0xFC, 0xFF, 0xFF, 0xFC, 0xF6, 0xFF, 0xFF
	.byte 0x00, 0xEA, 0xFF, 0xFF, 0x00, 0xFC, 0xFF, 0xFF, 0x50, 0xF6, 0xFF, 0xFF, 0x40, 0xEA, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x50, 0xF6, 0xFF, 0xFF, 0x40, 0xEA, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0xF8, 0xDF, 0xFF, 0xFF, 0x58, 0xED, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xDF, 0xFF, 0xFF
	.byte 0x58, 0xED, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x20, 0xEA, 0xFF, 0xFF, 0xB0, 0xE6, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x20, 0xEA, 0xFF, 0xFF, 0xB0, 0xE6, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x88, 0xFD, 0xFF, 0xFF, 0xC8, 0xEB, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x88, 0xFD, 0xFF, 0xFF
	.byte 0xC8, 0xEB, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDF, 0xFF, 0xFF, 0x40, 0xDF, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0xDF, 0xFF, 0xFF, 0x40, 0xDF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x80, 0xE6, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00
	.byte 0x80, 0xE6, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x40, 0xE5, 0xFF, 0xFF, 0x00, 0xE8, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x40, 0xE5, 0xFF, 0xFF, 0x00, 0xE8, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x20, 0x14, 0x00, 0x00, 0x40, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x14, 0x00, 0x00
	.byte 0x40, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xF6, 0xFF, 0xFF, 0x00, 0xEA, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0xFC, 0xF6, 0xFF, 0xFF, 0x00, 0xEA, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x50, 0x3B, 0x00, 0x00, 0x48, 0x11, 0x00, 0x00, 0x50, 0xE3, 0xFF, 0xFF, 0x00, 0x1B, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x50, 0xE3, 0xFF, 0xFF, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x50, 0xE3, 0xFF, 0xFF, 0xF8, 0x1A, 0x00, 0x00, 0x48, 0x20, 0x00, 0x00, 0x50, 0xE3, 0xFF, 0xFF
	.byte 0x00, 0x1B, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x50, 0xE3, 0xFF, 0xFF, 0x00, 0x1B, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x50, 0xE3, 0xFF, 0xFF, 0x10, 0x32, 0x00, 0x00, 0xE0, 0x15, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x10, 0x32, 0x00, 0x00, 0xE0, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xD8, 0x07, 0x00, 0x00, 0x58, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD8, 0x07, 0x00, 0x00
	.byte 0x58, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0x1F, 0x00, 0x00, 0xA8, 0x18, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x58, 0x1F, 0x00, 0x00, 0xA8, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x08, 0x2E, 0x00, 0x00, 0x08, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x2E, 0x00, 0x00
	.byte 0x08, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x40, 0x36, 0x00, 0x00, 0x98, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x36, 0x00, 0x00
	.byte 0x98, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x18, 0x00, 0x00, 0x40, 0x15, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x40, 0x18, 0x00, 0x00, 0x40, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xE0, 0xEA, 0xFF, 0xFF, 0x90, 0xE8, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xEA, 0xFF, 0xFF
	.byte 0x90, 0xE8, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xC8, 0x1C, 0x00, 0x00, 0x58, 0xEC, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00
	.byte 0x80, 0xE7, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x80, 0xF3, 0xFF, 0xFF
	.byte 0x40, 0x00, 0x00, 0x00, 0x70, 0x31, 0x00, 0x00, 0x80, 0xF4, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00
	.byte 0x00, 0x35, 0x00, 0x00, 0x80, 0xF3, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00
	.byte 0x80, 0xF3, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x80, 0xF3, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x80, 0xF3, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x90, 0x1D, 0x00, 0x00, 0x80, 0xF3, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x90, 0x1D, 0x00, 0x00
	.byte 0x80, 0xF3, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x80, 0xF3, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x80, 0xF3, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x35, 0x00, 0x00, 0x80, 0xF3, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00
	.byte 0x80, 0xF3, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x80, 0xF3, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x80, 0xF3, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x35, 0x00, 0x00, 0x80, 0xF3, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00
	.byte 0x80, 0xF3, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x80, 0xF3, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x80, 0xF3, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0xC0, 0xDA, 0xFF, 0xFF, 0x40, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xDA, 0xFF, 0xFF
	.byte 0x40, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x80, 0xF3, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x80, 0xF4, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x0C, 0xEB, 0xFF, 0xFF, 0x48, 0x11, 0x00, 0x00, 0x80, 0xEB, 0xFF, 0xFF, 0x80, 0xE2, 0xFF, 0xFF
	.byte 0x00, 0x10, 0x00, 0x00, 0x80, 0xEB, 0xFF, 0xFF, 0xFC, 0xF6, 0xFF, 0xFF, 0x00, 0x10, 0x00, 0x00
	.byte 0x80, 0xEB, 0xFF, 0xFF, 0x58, 0xF4, 0xFF, 0xFF, 0x48, 0x20, 0x00, 0x00, 0x80, 0xEB, 0xFF, 0xFF
	.byte 0xFC, 0xF6, 0xFF, 0xFF, 0x00, 0x10, 0x00, 0x00, 0x80, 0xEB, 0xFF, 0xFF, 0xFC, 0xF6, 0xFF, 0xFF
	.byte 0x00, 0x10, 0x00, 0x00, 0x80, 0xEB, 0xFF, 0xFF, 0x50, 0xF6, 0xFF, 0xFF, 0xE0, 0x15, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x50, 0xF6, 0xFF, 0xFF, 0xE0, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xF8, 0xDF, 0xFF, 0xFF, 0x58, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xDF, 0xFF, 0xFF
	.byte 0x58, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xEA, 0xFF, 0xFF, 0xA8, 0x18, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x20, 0xEA, 0xFF, 0xFF, 0xA8, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x88, 0xFD, 0xFF, 0xFF, 0x08, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xFD, 0xFF, 0xFF
	.byte 0x08, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDF, 0xFF, 0xFF, 0x00, 0x25, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0xDF, 0xFF, 0xFF, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x98, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00
	.byte 0x98, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xE5, 0xFF, 0xFF, 0x40, 0x15, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x40, 0xE5, 0xFF, 0xFF, 0x40, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x20, 0x14, 0x00, 0x00, 0x90, 0xE8, 0xFF, 0xFF, 0xA8, 0x0A, 0x00, 0x00, 0x20, 0x14, 0x00, 0x00
	.byte 0xE0, 0xEA, 0xFF, 0xFF, 0xA8, 0x0A, 0x00, 0x00, 0xFC, 0xF6, 0xFF, 0xFF, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x58, 0xF4, 0xFF, 0xFF, 0x48, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222CFF8
MOD8_0222CFF8: ; 0x0222CFF8
	.byte 0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD8_0222D004
MOD8_0222D004: ; 0x0222D004
	.byte 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00

	.global MOD8_0222D01C
MOD8_0222D01C: ; 0x0222D01C
	.word MOD08_02229114, MOD08_022293D4, MOD08_022297F8, MOD08_02229100
	.word MOD08_02229884, MOD08_02229664

	.global MOD8_0222D034
MOD8_0222D034: ; 0x0222D034
	.word MOD08_02228978, MOD08_022289A0, MOD08_022289C8, MOD08_022289F0
	.word MOD08_02228A18, MOD08_02228A40, MOD08_02228A68, MOD08_02228A90
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00

	.global MOD8_0222D07C
MOD8_0222D07C: ; 0x0222D07C
	.byte 0x01, 0x00, 0x00, 0x00, 0xE6, 0x05, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0xE6, 0x05, 0x00, 0x00
	.byte 0x0E, 0x00, 0x00, 0x00, 0xE7, 0x05, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0xE8, 0x05, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0xE9, 0x05, 0x00, 0x00

	.global MOD8_0222D0A4
MOD8_0222D0A4: ; 0x0222D0A4
	.byte 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00

	.global MOD8_0222D0D0
MOD8_0222D0D0: ; 0x0222D0D0
	.byte 0xFE, 0xFF, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x00, 0xFF, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00
	.byte 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xFF, 0xFF, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00

	.global MOD8_0222D118
MOD8_0222D118: ; 0x0222D118
	.word MOD08_02228AE0, MOD08_02228AE4, MOD08_02228AFC, MOD08_02228B08
	.word MOD08_02228BE8, MOD08_02228BEC, MOD08_02228C40, MOD08_02228C44
	.word MOD08_02228C50, MOD08_02228C5C, MOD08_02228D04, MOD08_02228D10
	.word MOD08_02228D84, MOD08_02228D88, MOD08_02228E24, MOD08_02228E28
	.word MOD08_02228E48, MOD08_02228E54, MOD08_02228EEC, MOD08_02228EF0
	.word MOD08_02228EFC, MOD08_02228F08, MOD08_02228FF8, MOD08_02228FFC
	.word MOD08_02229060, MOD08_0222906C, MOD08_022290F0, MOD08_022290FC
	.byte 0x00, 0x00

	.global MOD8_0222D18A
MOD8_0222D18A: ; 0x0222D18A
	.byte 0xF9, 0xFF

	.global MOD8_0222D18C
MOD8_0222D18C: ; 0x0222D18C
	.byte 0x01, 0x00, 0x01, 0x00, 0xFB, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFD, 0xFF, 0x00, 0x00, 0x01, 0x00
	.byte 0xFE, 0xFF, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x07, 0x00, 0x01, 0x00, 0x00, 0x00, 0xFB, 0xFF
	.byte 0x01, 0x00, 0x00, 0x00, 0xFD, 0xFF, 0x00, 0x00, 0x01, 0x00, 0xFE, 0xFF, 0x00, 0x00, 0x01, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x01, 0x00
	.byte 0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00, 0x01, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x01, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x01, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222D208
MOD8_0222D208: ; 0x0222D208
	.byte 0x01, 0x00, 0x00, 0x00

	.global MOD8_0222D20C
MOD8_0222D20C: ; 0x0222D20C
	.byte 0x05, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global MOD8_0222D2A8
MOD8_0222D2A8: ; 0x0222D2A8
	.byte 0x13, 0x00, 0x00, 0x00

	.global MOD8_0222D2AC
MOD8_0222D2AC: ; 0x0222D2AC
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD8_0222D2B0
MOD8_0222D2B0: ; 0x0222D2B0
	.byte 0x05, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x15, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x19, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00
	.byte 0x1D, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x21, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global MOD8_0222D398
MOD8_0222D398: ; 0x0222D398
	.byte 0xE0, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0xDF, 0x00, 0x00, 0x00, 0xDE, 0x00, 0x00, 0x00
	.byte 0xE3, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0xE2, 0x00, 0x00, 0x00, 0xE1, 0x00, 0x00, 0x00
	.byte 0xE6, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0xE5, 0x00, 0x00, 0x00, 0xE4, 0x00, 0x00, 0x00
	.byte 0xDD, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0xDC, 0x00, 0x00, 0x00, 0xDB, 0x00, 0x00, 0x00
	.byte 0xE9, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0xE7, 0x00, 0x00, 0x00
	.byte 0xEC, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0xEB, 0x00, 0x00, 0x00, 0xEA, 0x00, 0x00, 0x00
	.byte 0xEF, 0x00, 0x00, 0x00, 0x3D, 0x00, 0x00, 0x00, 0xEE, 0x00, 0x00, 0x00, 0xED, 0x00, 0x00, 0x00
	.byte 0xF2, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0xF1, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00
	.byte 0xF5, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0xF4, 0x00, 0x00, 0x00, 0xF3, 0x00, 0x00, 0x00
	.byte 0xF8, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0xF7, 0x00, 0x00, 0x00, 0xF6, 0x00, 0x00, 0x00
	.byte 0xFB, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0xFA, 0x00, 0x00, 0x00, 0xF9, 0x00, 0x00, 0x00
	.byte 0xFE, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00
	.byte 0x04, 0x01, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00
	.byte 0x07, 0x01, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x06, 0x01, 0x00, 0x00, 0x05, 0x01, 0x00, 0x00
	.byte 0x01, 0x01, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
	.byte 0x0A, 0x01, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0x09, 0x01, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00
	.byte 0x0D, 0x01, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00, 0x0C, 0x01, 0x00, 0x00, 0x0B, 0x01, 0x00, 0x00
	.byte 0x13, 0x01, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x12, 0x01, 0x00, 0x00, 0x11, 0x01, 0x00, 0x00
	.byte 0x10, 0x01, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x0F, 0x01, 0x00, 0x00, 0x0E, 0x01, 0x00, 0x00
	.byte 0x10, 0x01, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x0F, 0x01, 0x00, 0x00, 0x0E, 0x01, 0x00, 0x00

	.global MOD8_0222D4D8
MOD8_0222D4D8: ; 0x0222D4D8
	.byte 0x00, 0x08, 0x0E, 0x14, 0x14, 0x10, 0x10, 0x00

	.global MOD8_0222D4E0
MOD8_0222D4E0: ; 0x0222D4E0
	.byte 0x05, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD8_0222D538
MOD8_0222D538: ; 0x0222D538
	.byte 0x40, 0x00, 0x20, 0x00, 0xC0, 0x00, 0xE0, 0x00, 0x28, 0x00, 0x20, 0x00, 0xD8, 0x00, 0xE0, 0x00
	.byte 0x50, 0x00, 0x20, 0x00, 0xB0, 0x00, 0xE0, 0x00

	.global MOD8_0222D550
MOD8_0222D550: ; 0x0222D550
	.byte 0x50, 0x01

	.global MOD8_0222D552
MOD8_0222D552: ; 0x0222D552
	.byte 0x70, 0x00

	.global MOD8_0222D554
MOD8_0222D554: ; 0x0222D554
	.byte 0x00, 0xFE, 0xB0, 0xFF, 0x32, 0x00, 0x80, 0xFD, 0x3C, 0x01, 0x70, 0x00
	.byte 0x00, 0xFE, 0xC4, 0xFF, 0x32, 0x00, 0x9C, 0xFF, 0x64, 0x01, 0x78, 0x00, 0x00, 0x00, 0x9C, 0xFF
	.byte 0x2A, 0x00, 0x80, 0xFD

	.global MOD8_0222D574
MOD8_0222D574: ; 0x0222D574
	.byte 0xB0, 0xFF

	.global MOD8_0222D576
MOD8_0222D576: ; 0x0222D576
	.byte 0x70, 0x00

	.global MOD8_0222D578
MOD8_0222D578: ; 0x0222D578
	.byte 0x00, 0xFE, 0x50, 0x01, 0x32, 0x00, 0x00, 0xFE
	.byte 0xB0, 0xFF, 0x70, 0x00, 0x00, 0xFE, 0x50, 0x01, 0x32, 0x00, 0x00, 0xFE, 0xB0, 0xFF, 0x70, 0x00
	.byte 0x00, 0xFE, 0x50, 0x01, 0x32, 0x00, 0x00, 0xFE

	.data
	.global MOD8_0222D5A0
MOD8_0222D5A0: ; 0x0222D5A0
	.byte 0x14, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.bss
