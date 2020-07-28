	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD63_021DA640
MOD63_021DA640: ; 0x021DA640
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _021DA66C ; =MOD63_021DBE4C
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_0201D040
	mov r0, #5
	mov r1, #0x4c
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021DA66C: .word MOD63_021DBE4C
	thumb_func_end MOD63_021DA640

	thumb_func_start MOD63_021DA670
MOD63_021DA670: ; 0x021DA670
	push {r3, r4, r5, r6, lr}
	sub sp, #0x2c
	add r6, r0, #0
	mov r0, #0
	str r6, [sp]
	mvn r0, r0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r2, [sp, #0x10]
	mov r2, #0x4b
	add r5, r1, #0
	lsl r2, r2, #2
	ldr r1, [r5, r2]
	add r4, r3, #0
	str r1, [sp, #0x14]
	add r1, r2, #4
	ldr r1, [r5, r1]
	add r3, r6, #0
	str r1, [sp, #0x18]
	add r1, r2, #0
	add r1, #8
	ldr r1, [r5, r1]
	add r2, #0xc
	str r1, [sp, #0x1c]
	ldr r1, [r5, r2]
	add r2, r6, #0
	str r1, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x40]
	add r1, r6, #0
	bl FUN_02008AA4
	ldr r0, [r5]
	mov r1, #0
	str r0, [r4]
	ldr r0, [sp, #0x40]
	str r0, [r4, #4]
	str r1, [r4, #8]
	str r1, [r4, #0xc]
	mov r0, #1
	str r1, [r4, #0x10]
	lsl r0, r0, #0xc
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	strh r1, [r4, #0x20]
	mov r0, #1
	str r0, [r4, #0x24]
	str r0, [r4, #0x28]
	mov r0, #0x4c
	str r0, [r4, #0x2c]
	add sp, #0x2c
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD63_021DA670

	thumb_func_start MOD63_021DA6E0
MOD63_021DA6E0: ; 0x021DA6E0
	mov r0, #0x1b
	lsl r0, r0, #4
	bx lr
	.align 2, 0
	thumb_func_end MOD63_021DA6E0

	thumb_func_start MOD63_021DA6E8
MOD63_021DA6E8: ; 0x021DA6E8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	mov r2, #1
	lsl r2, r2, #0x1a
	add r5, r0, #0
	ldr r1, [r2]
	ldr r0, _021DA9FC ; =0xFFCFFFEF
	and r1, r0
	mov r0, #0x10
	orr r0, r1
	str r0, [r2]
	bl MOD63_021DA640
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r1, #0x80
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x4c
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	mov r0, #0x19
	add r1, r5, #4
	mov r2, #0x4c
	bl FUN_02008C9C
	mov r2, #1
	str r0, [r5]
	add r0, r5, #4
	mov r1, #0
	lsl r2, r2, #0x14
	bl FUN_02008D24
	ldr r4, _021DAA00 ; =MOD63_021DBE28
	mov r7, #0
	add r6, r5, #0
_021DA73C:
	ldrb r0, [r4]
	add r1, r7, #0
	mov r2, #0x4c
	bl FUN_02008DEC
	mov r1, #0x4b
	lsl r1, r1, #2
	str r0, [r6, r1]
	add r7, r7, #1
	add r4, r4, #1
	add r6, r6, #4
	cmp r7, #4
	blt _021DA73C
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe0
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x26
	bl FUN_02008F34
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe0
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x27
	mov r3, #0
	bl FUN_02008F34
	mov r1, #0x53
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe0
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x28
	mov r3, #0
	bl FUN_02008F34
	mov r1, #0x57
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #3
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe0
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x29
	mov r3, #0
	bl FUN_02008F34
	mov r1, #0x5b
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #4
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe0
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x2a
	mov r3, #0
	bl FUN_02008F34
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	add r0, #0xe4
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x21
	bl FUN_02008FEC
	mov r1, #5
	lsl r1, r1, #6
	str r0, [r5, r1]
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	add r0, #0xe4
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x22
	mov r3, #0
	bl FUN_02008FEC
	mov r1, #0x15
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	add r0, #0xe4
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x23
	mov r3, #0
	bl FUN_02008FEC
	mov r1, #0x16
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #3
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	add r0, #0xe4
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x24
	mov r3, #0
	bl FUN_02008FEC
	mov r1, #0x17
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #4
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	add r0, #0xe4
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x25
	mov r3, #0
	bl FUN_02008FEC
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r5, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe8
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x2b
	bl FUN_020090AC
	mov r1, #0x51
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe8
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x2c
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x55
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #2
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe8
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x2d
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x59
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #3
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe8
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x2e
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x5d
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #4
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe8
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x2f
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x61
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xec
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x30
	bl FUN_020090AC
	mov r1, #0x52
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #1
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xec
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x31
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x56
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #2
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xec
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x32
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x5a
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #3
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xec
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x33
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #4
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xec
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x34
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x62
	lsl r1, r1, #2
	add r7, r1, #0
	add r6, r1, #0
	str r0, [r5, r1]
	mov r4, #0
	sub r7, #0x4c
	sub r6, #0x48
_021DA9DC:
	ldr r0, [r5, r7]
	bl FUN_02009A50
	ldr r0, [r5, r6]
	bl FUN_02009CF0
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #5
	blt _021DA9DC
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021DA9FC: .word 0xFFCFFFEF
_021DAA00: .word MOD63_021DBE28
	thumb_func_end MOD63_021DA6E8

	thumb_func_start MOD63_021DAA04
MOD63_021DAA04: ; 0x021DAA04
	push {r3, r4, r5, r6, r7, lr}
	mov r7, #5
	add r5, r0, #0
	mov r4, #0
	lsl r7, r7, #6
_021DAA0E:
	lsl r0, r4, #4
	add r6, r5, r0
	mov r0, #0x4f
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	ldr r0, [r6, r7]
	bl FUN_02009E04
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #5
	blo _021DAA0E
	mov r6, #0x4b
	mov r4, #0
	lsl r6, r6, #2
_021DAA32:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, r6]
	bl FUN_02008E2C
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021DAA32
	ldr r0, [r5]
	bl FUN_0201FD58
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD63_021DAA04

	thumb_func_start MOD63_021DAA5C
MOD63_021DAA5C: ; 0x021DAA5C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xa4
	ldr r3, _021DABC0 ; =MOD63_021DBE5C
	add r5, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0x38
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r3, _021DABC4 ; =MOD63_021DBE74
	add r2, sp, #0x20
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r3, _021DABC8 ; =MOD63_021DBE8C
	add r2, sp, #8
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, sp, #0x80
	str r0, [sp]
	mov r0, #0
	add r1, r5, #0
	mov r2, #1
	add r3, sp, #0x50
	bl MOD63_021DA670
	mov r0, #5
	lsl r0, r0, #0x10
	str r0, [sp, #0x58]
	mov r0, #7
	lsl r0, r0, #0x10
	str r0, [sp, #0x5c]
	add r0, sp, #0x50
	bl FUN_0201FE94
	mov r1, #0x63
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	mov r1, #0
	bl FUN_020200BC
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	add r0, sp, #0x80
	str r0, [sp]
	mov r0, #1
	add r1, r5, #0
	add r2, r0, #0
	add r3, sp, #0x50
	bl MOD63_021DA670
	mov r0, #5
	lsl r0, r0, #0x10
	str r0, [sp, #0x58]
	mov r0, #7
	lsl r0, r0, #0x10
	str r0, [sp, #0x5c]
	add r0, sp, #0x50
	bl FUN_0201FE94
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	mov r1, #0
	bl FUN_020200BC
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	add r0, r5, #0
	mov r1, #3
	bl MOD63_021DAC80
	add r0, sp, #0x80
	str r0, [sp]
	mov r0, #2
	add r1, r5, #0
	mov r2, #1
	add r3, sp, #0x50
	bl MOD63_021DA670
	mov r0, #5
	lsl r0, r0, #0x12
	str r0, [sp, #0x58]
	mov r0, #7
	lsl r0, r0, #0x10
	str r0, [sp, #0x5c]
	add r0, sp, #0x50
	bl FUN_0201FE94
	mov r1, #0x65
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0
	str r0, [sp, #4]
	add r7, sp, #0x20
	add r6, sp, #8
	add r4, sp, #0x38
_021DAB58:
	add r0, sp, #0x80
	str r0, [sp]
	mov r0, #3
	add r1, r5, #0
	mov r2, #0
	add r3, sp, #0x50
	bl MOD63_021DA670
	ldr r0, [r7]
	lsl r0, r0, #0xc
	str r0, [sp, #0x58]
	ldr r0, [r6]
	lsl r0, r0, #0xc
	str r0, [sp, #0x5c]
	add r0, sp, #0x50
	bl FUN_0201FE94
	ldr r1, [r4]
	lsl r1, r1, #2
	add r2, r5, r1
	mov r1, #0x63
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	lsl r0, r0, #2
	add r1, r5, r0
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [r4]
	lsl r0, r0, #2
	add r1, r5, r0
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [sp, #4]
	add r7, r7, #4
	add r0, r0, #1
	add r6, r6, #4
	add r4, r4, #4
	str r0, [sp, #4]
	cmp r0, #6
	blt _021DAB58
	add sp, #0xa4
	pop {r4, r5, r6, r7, pc}
	nop
_021DABC0: .word MOD63_021DBE5C
_021DABC4: .word MOD63_021DBE74
_021DABC8: .word MOD63_021DBE8C
	thumb_func_end MOD63_021DAA5C

	thumb_func_start MOD63_021DABCC
MOD63_021DABCC: ; 0x021DABCC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x58
	add r2, r0, #0
	add r0, sp, #0x34
	add r6, r1, #0
	str r0, [sp]
	add r1, r2, #0
	mov r0, #4
	mov r2, #0
	add r3, sp, #4
	bl MOD63_021DA670
	mov r0, #2
	str r0, [sp, #0x2c]
	mov r5, #0
	add r7, sp, #4
_021DABEC:
	add r0, r6, #0
	add r1, r5, #0
	bl MOD63_021DAF80
	add r4, r0, #0
	add r0, r7, #0
	bl FUN_0201FE94
	str r0, [r4]
	mov r1, #0
	bl FUN_020200BC
	ldr r0, [r4]
	mov r1, #0
	bl FUN_020200A0
	add r5, r5, #1
	cmp r5, #0x10
	blt _021DABEC
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD63_021DABCC

	thumb_func_start MOD63_021DAC18
MOD63_021DAC18: ; 0x021DAC18
	ldr r3, _021DAC20 ; =FUN_0201FDEC
	ldr r0, [r0]
	bx r3
	nop
_021DAC20: .word FUN_0201FDEC
	thumb_func_end MOD63_021DAC18

	thumb_func_start MOD63_021DAC24
MOD63_021DAC24: ; 0x021DAC24
	lsl r1, r1, #2
	add r1, r0, r1
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r3, _021DAC34 ; =FUN_020200A0
	add r1, r2, #0
	bx r3
	.align 2, 0
_021DAC34: .word FUN_020200A0
	thumb_func_end MOD63_021DAC24

	thumb_func_start MOD63_021DAC38
MOD63_021DAC38: ; 0x021DAC38
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r2, #0
	mov r2, #0x63
	lsl r2, r2, #2
	add r4, r0, r2
	lsl r5, r1, #2
	ldr r0, [r4, r5]
	add r7, r3, #0
	bl FUN_0202011C
	add r3, r0, #0
	add r2, sp, #0
	ldmia r3!, {r0, r1}
	mov ip, r2
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, ip
	str r0, [r2]
	str r6, [sp]
	str r7, [sp, #4]
	ldr r0, [r4, r5]
	bl FUN_02020044
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD63_021DAC38

	thumb_func_start MOD63_021DAC6C
MOD63_021DAC6C: ; 0x021DAC6C
	push {r3, lr}
	mov r2, #0xb
	mov r3, #7
	mov r1, #1
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	bl MOD63_021DAC38
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD63_021DAC6C

	thumb_func_start MOD63_021DAC80
MOD63_021DAC80: ; 0x021DAC80
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	bl FUN_02020130
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_02020130
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021DAC80

	thumb_func_start MOD63_021DACA0
MOD63_021DACA0: ; 0x021DACA0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	bl FUN_020200BC
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_020200BC
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021DACA0

	thumb_func_start MOD63_021DACC0
MOD63_021DACC0: ; 0x021DACC0
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0202011C
	add r5, r0, #0
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	mov r0, #0xe
	ldr r1, [sp]
	lsl r0, r0, #0xc
	sub r1, r1, r0
	mov r0, #0xb
	lsl r0, r0, #0x10
	str r1, [sp]
	cmp r1, r0
	bgt _021DAD04
	str r0, [sp]
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r2, #0
	bl FUN_02020044
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_021DAD04:
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r2, #0
	bl FUN_02020044
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021DACC0

	thumb_func_start MOD63_021DAD18
MOD63_021DAD18: ; 0x021DAD18
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	lsl r4, r1, #2
	mov r0, #0x63
	add r1, r5, r4
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r6, r2, #0
	bl FUN_02020354
	mov r1, #1
	bl FUN_020B19C4
	add r7, r0, #0
	cmp r6, #0
	bne _021DAD44
	ldr r0, _021DAD64 ; =MOD63_021DBFA0
	add r1, r7, #0
	mov r2, #0x20
	bl GX_LoadOBJPltt
	pop {r3, r4, r5, r6, r7, pc}
_021DAD44:
	ldr r0, _021DAD68 ; =MOD63_021DBF64
	ldr r0, [r0, r4]
	lsl r0, r0, #4
	add r1, r5, r0
	mov r0, #5
	lsl r0, r0, #6
	ldr r0, [r1, r0]
	bl FUN_0200955C
	ldr r0, [r0, #0xc]
	add r1, r7, #0
	mov r2, #0x20
	bl GX_LoadOBJPltt
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DAD64: .word MOD63_021DBFA0
_021DAD68: .word MOD63_021DBF64
	thumb_func_end MOD63_021DAD18

	thumb_func_start MOD63_021DAD6C
MOD63_021DAD6C: ; 0x021DAD6C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	ldr r3, _021DAE44 ; =MOD63_021DBE40
	add r2, sp, #0x18
	str r0, [sp]
	str r1, [sp, #4]
	ldmia r3!, {r0, r1}
	str r2, [sp, #8]
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r3, _021DAE48 ; =MOD63_021DBE34
	str r0, [r2]
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r1, _021DAE4C ; =0x000005C8
	str r0, [r2]
	ldr r0, [sp, #4]
	cmp r0, r1
	blt _021DADE6
	mov r4, #0
_021DAD98:
	ldr r0, [sp, #8]
	lsl r7, r4, #2
	ldr r0, [r0, r7]
	lsl r1, r0, #2
	ldr r0, [sp]
	add r5, r0, r1
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0x24
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	str r0, [r3]
	ldr r0, _021DAE50 ; =MOD63_021DBF4C
	ldr r1, [sp, #0x24]
	ldr r0, [r0, r7]
	sub r0, r1, r0
	str r0, [sp, #0x24]
	mov r0, #1
	ldr r1, [sp, #0x28]
	lsl r0, r0, #0xe
	sub r0, r1, r0
	str r0, [sp, #0x28]
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r2, #0
	bl FUN_02020044
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #3
	blo _021DAD98
_021DADE6:
	ldr r1, _021DAE54 ; =0x000005E6
	ldr r0, [sp, #4]
	cmp r0, r1
	blt _021DAE3E
	mov r5, #0
_021DADF0:
	lsl r7, r5, #2
	add r0, sp, #0xc
	ldr r0, [r0, r7]
	lsl r1, r0, #2
	ldr r0, [sp]
	add r4, r0, r1
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0x24
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	str r0, [r3]
	ldr r0, _021DAE58 ; =MOD63_021DBF58
	ldr r1, [sp, #0x24]
	ldr r0, [r0, r7]
	sub r0, r1, r0
	str r0, [sp, #0x24]
	mov r0, #1
	ldr r1, [sp, #0x28]
	lsl r0, r0, #0xe
	sub r0, r1, r0
	str r0, [sp, #0x28]
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r2, #0
	bl FUN_02020044
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #3
	blo _021DADF0
_021DAE3E:
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DAE44: .word MOD63_021DBE40
_021DAE48: .word MOD63_021DBE34
_021DAE4C: .word 0x000005C8
_021DAE50: .word MOD63_021DBF4C
_021DAE54: .word 0x000005E6
_021DAE58: .word MOD63_021DBF58
	thumb_func_end MOD63_021DAD6C

	.section .rodata

	.global MOD63_021DBE28
MOD63_021DBE28: ; 0x021DBE28
	.byte 0x05, 0x05, 0x05, 0x05, 0x4C, 0x00, 0x00, 0x00, 0x4C, 0x00, 0x00, 0x00

	.global MOD63_021DBE34
MOD63_021DBE34: ; 0x021DBE34
	.byte 0x06, 0x00, 0x00, 0x00
	.byte 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00

	.global MOD63_021DBE40
MOD63_021DBE40: ; 0x021DBE40
	.byte 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00

	.global MOD63_021DBE4C
MOD63_021DBE4C: ; 0x021DBE4C
	.byte 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x4C, 0x00, 0x00, 0x00

	.global MOD63_021DBE5C
MOD63_021DBE5C: ; 0x021DBE5C
	.byte 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00

	.global MOD63_021DBE74
MOD63_021DBE74: ; 0x021DBE74
	.byte 0x08, 0x01, 0x00, 0x00
	.byte 0x20, 0x01, 0x00, 0x00, 0x20, 0x01, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00
	.byte 0xE0, 0x00, 0x00, 0x00

	.global MOD63_021DBE8C
MOD63_021DBE8C: ; 0x021DBE8C
	.byte 0x80, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00
	.byte 0xE0, 0x00, 0x00, 0x00, 0xD0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x4C, 0x00, 0x00, 0x00
	.byte 0x4C, 0x00, 0x00, 0x00

	.section .data

	.global MOD63_021DBF4C
MOD63_021DBF4C: ; 0x021DBF4C
	.byte 0x00, 0x60, 0x00, 0x00
	.byte 0x00, 0x58, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00

	.global MOD63_021DBF58
MOD63_021DBF58: ; 0x021DBF58
	.byte 0x00, 0x40, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00
	.byte 0x00, 0x58, 0x00, 0x00

	.global MOD63_021DBF64
MOD63_021DBF64: ; 0x021DBF64
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.section .bss

	.global MOD63_021DBFA0
MOD63_021DBFA0: ; 0x021DBFA0
	.space 0x20
