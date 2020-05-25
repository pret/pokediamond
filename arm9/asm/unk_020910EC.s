	.include "asm/macros.inc"
	.include "global.inc"

	.extern OSi_ThreadInfo

	.section .rodata

	.global UNK_020FF500
UNK_020FF500: ; 0x020FF500
	.byte 0x00, 0x08, 0x01, 0x01, 0x01, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FF50C
UNK_020FF50C: ; 0x020FF50C
	.byte 0x00, 0x08, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FF518
UNK_020FF518: ; 0x020FF518
	.byte 0x00, 0x08, 0x01, 0x01, 0x01, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FF524
UNK_020FF524: ; 0x020FF524
	.byte 0x00, 0x01, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04

	.global UNK_020FF534
UNK_020FF534: ; 0x020FF534
	.byte 0x06, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00
	.byte 0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00

	.global UNK_020FF554
UNK_020FF554: ; 0x020FF554
	.byte 0x05, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00

	.global UNK_020FF564
UNK_020FF564: ; 0x020FF564
	.byte 0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00

	.global UNK_020FF56C
UNK_020FF56C: ; 0x020FF56C
	.byte 0x03, 0x00, 0x01, 0x00

	.global UNK_020FF570
UNK_020FF570: ; 0x020FF570
	.byte 0x02, 0x00

	.global UNK_020FF572
UNK_020FF572: ; 0x020FF572
	.byte 0x01

	.global UNK_020FF573
UNK_020FF573: ; 0x020FF573
	.byte 0x00

	.global UNK_020FF574
UNK_020FF574: ; 0x020FF574
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020FF578
UNK_020FF578: ; 0x020FF578
	.byte 0x01, 0x02, 0x00, 0x04, 0x03, 0x05, 0x06, 0x07

	.global UNK_020FF580
UNK_020FF580: ; 0x020FF580
	.byte 0x05, 0x09, 0x01, 0x0E, 0x0C, 0x02, 0x0A, 0x00, 0x0B, 0x0D, 0x03, 0x04, 0x08, 0x06, 0x0F, 0x07

	.section .data

	.global UNK_02106170
UNK_02106170: ; 0x02106170
	.word UNK_020FF573
	.word UNK_020FF572
	.word UNK_020FF570
	.word UNK_020FF56C
	.word UNK_020FF564
	.word UNK_020FF554
	.word UNK_020FF534

	.global UNK_0210618C
UNK_0210618C: ; 0x0210618C
	.asciz "%s%c%c%c%c%s"

	.balign 4, 0
	.global UNK_0210619C
UNK_0210619C: ; 0x0210619C
	; .asciz "0123456789abcdefghijklmnopqrstuvwxyz"
	.byte 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66
	.byte 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76
	.byte 0x00, 0x00, 0x00, 0x00

	.balign 4, 0
	.global UNK_021061C0
UNK_021061C0: ; 0x021061C0
	.word -26

	.global UNK_021061C4
UNK_021061C4: ; 0x021061C4
	.byte 0x01, 0x01, 0xC0, 0x05, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08
	.byte 0x00, 0x08, 0x0C, 0x20, 0x00, 0x00, 0x00, 0x00

	.global UNK_021061DC
UNK_021061DC: ; 0x021061DC
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x66, 0x04, 0x00, 0x00, 0x00, 0x00, 0x61, 0x08, 0x00, 0x00
	.byte 0x00, 0x08, 0x0C, 0x20, 0x00, 0x08, 0x0D, 0x20

	.global UNK_021061F4
UNK_021061F4: ; 0x021061F4
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEA, 0x05, 0x00, 0x00, 0x00, 0x00, 0xEB, 0x06, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0D, 0x20

	.global UNK_0210620C
UNK_0210620C: ; 0x0210620C
	.byte 0x25, 0x64, 0x2E, 0x25, 0x64, 0x2E, 0x25, 0x64, 0x2E, 0x25, 0x64, 0x00

	.global UNK_02106218
UNK_02106218: ; 0x02106218
	.byte 0x10, 0x00, 0x00, 0x00

	.global UNK_0210621C
UNK_0210621C: ; 0x0210621C
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00

	.global UNK_02106224
UNK_02106224: ; 0x02106224
	.asciz "NintendoDS"

	.balign 4, 0
	.global UNK_02106230
UNK_02106230: ; 0x02106230
	.byte 0xAA, 0xAA, 0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00

	.section .bss

	.global UNK_021C8C78
UNK_021C8C78: ; 0x021C8C78
	.space 0x4

	.global UNK_021C8C7C
UNK_021C8C7C: ; 0x021C8C7C
	.space 0x4

	.global UNK_021C8C80
UNK_021C8C80: ; 0x021C8C80
	.space 0x4

	.global UNK_021C8C84
UNK_021C8C84: ; 0x021C8C84
	.space 0x5

	.global UNK_021C8C89
UNK_021C8C89: ; 0x021C8C89
	.space 0x1

	.global UNK_021C8C8A
UNK_021C8C8A: ; 0x021C8C8A
	.space 0x4

	.global UNK_021C8C8E
UNK_021C8C8E: ; 0x021C8C8E
	.space 0x2

	.global UNK_021C8C90
UNK_021C8C90: ; 0x021C8C90
	.space 0x10

	.global UNK_021C8CA0
UNK_021C8CA0: ; 0x021C8CA0
	.space 0x20

	.global UNK_021C8CC0
UNK_021C8CC0: ; 0x021C8CC0
	.space 0x4

	.global UNK_021C8CC4
UNK_021C8CC4: ; 0x021C8CC4
	.space 0x4

	.global UNK_021C8CC8
UNK_021C8CC8: ; 0x021C8CC8
	.space 0x4

	.global UNK_021C8CCC
UNK_021C8CCC: ; 0x021C8CCC
	.space 0x4

	.global UNK_021C8CD0
UNK_021C8CD0: ; 0x021C8CD0
	.space 0x4

	.global UNK_021C8CD4
UNK_021C8CD4: ; 0x021C8CD4
	.space 0x30

	.global UNK_021C8D04
UNK_021C8D04: ; 0x021C8D04
	.space 0x4

	.global UNK_021C8D08
UNK_021C8D08: ; 0x021C8D08
	.space 0x20

	.global UNK_021C8D28
UNK_021C8D28: ; 0x021C8D28
	.space 0x8

	.global UNK_021C8D30
UNK_021C8D30: ; 0x021C8D30
	.space 0x4

	.global UNK_021C8D34
UNK_021C8D34: ; 0x021C8D34
	.space 0x4

	.global UNK_021C8D38
UNK_021C8D38: ; 0x021C8D38
	.space 0x4

	.global UNK_021C8D3C
UNK_021C8D3C: ; 0x021C8D3C
	.space 0x4

	.global UNK_021C8D40
UNK_021C8D40: ; 0x021C8D40
	.space 0x4

	.global UNK_021C8D44
UNK_021C8D44: ; 0x021C8D44
	.space 0x8

	.global UNK_021C8D4C
UNK_021C8D4C: ; 0x021C8D4C
	.space 0x10

	.global UNK_021C8D5C
UNK_021C8D5C: ; 0x021C8D5C
	.space 0x10

	.global UNK_021C8D6C
UNK_021C8D6C: ; 0x021C8D6C
	.space 0x38

	.global UNK_021C8DA4
UNK_021C8DA4: ; 0x021C8DA4
	.space 0x104

	.global UNK_021C8EA8
UNK_021C8EA8: ; 0x021C8EA8
	.space 0x4

	.global UNK_021C8EAC
UNK_021C8EAC: ; 0x021C8EAC
	.space 0x4

	.global UNK_021C8EB0
UNK_021C8EB0: ; 0x021C8EB0
	.space 0x4

	.global UNK_021C8EB4
UNK_021C8EB4: ; 0x021C8EB4
	.space 0x4

	.global UNK_021C8EB8
UNK_021C8EB8: ; 0x021C8EB8
	.space 0x4

	.global UNK_021C8EBC
UNK_021C8EBC: ; 0x021C8EBC
	.space 0x4

	.global UNK_021C8EC0
UNK_021C8EC0: ; 0x021C8EC0
	.space 0x4

	.global UNK_021C8EC4
UNK_021C8EC4: ; 0x021C8EC4
	.space 0x4

	.text

	; Nintendo DWC

	arm_func_start FUN_020910EC
FUN_020910EC: ; 0x020910EC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x14
	mov r12, r0
	mov r4, r1
	mov r5, r2
	mov r2, r4
	add r0, sp, #0x0
	mov r1, r12
	mov r4, r3
	bl MATH_CalcSHA1
	add r0, sp, #0x0
	mov r1, r5
	mov r2, r4
	bl FUN_02091130
	add sp, sp, #0x14
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02091130
FUN_02091130: ; 0x02091130
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x120
	mov r3, #0x0
	str r3, [sp, #0x10]
	str r3, [sp, #0x18]
	str r2, [sp, #0x0]
	mov r3, #0x80
	mov r4, r0
	mov r2, r1
	ldr ip, _0209122C ; =0x00010001
	str r3, [sp, #0x4]
	add r0, sp, #0x1c
	mov r1, #0x100
	str r12, [sp, #0x8]
	bl FUN_0209156C
	mov r1, r0
	add r0, sp, #0x1c
	add r2, sp, #0xc
	add r3, sp, #0x10
	bl FUN_020913D4
	cmp r0, #0x0
	addeq sp, sp, #0x120
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	add r1, sp, #0x14
	add r0, sp, #0x18
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r2, #0x0
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	mov r3, r2
	bl FUN_02091230
	cmp r0, #0x0
	addeq sp, sp, #0x120
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, [sp, #0x18]
	cmp r0, #0x14
	addne sp, sp, #0x120
	movne r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	ldr r2, [sp, #0x14]
	mov r3, #0x0
_020911EC:
	ldrb r1, [r2, #0x0]
	ldrb r0, [r4, #0x0]
	cmp r1, r0
	addne sp, sp, #0x120
	movne r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	add r3, r3, #0x1
	cmp r3, #0x14
	add r4, r4, #0x1
	add r2, r2, #0x1
	blt _020911EC
	mov r0, #0x1
	add sp, sp, #0x120
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209122C: .word 0x00010001

	arm_func_start FUN_02091230
FUN_02091230:
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r2
	mov r4, r3
	add r0, sp, #0x10
	add r1, sp, #0x14
	mov r2, #0x30
	mov r3, #0x0
	bl FUN_02091498
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	addeq sp, sp, #0x10
	bxeq lr
	add r0, sp, #0x10
	add r1, sp, #0x14
	mov r2, #0x30
	mov r3, #0x0
	bl FUN_02091498
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	addeq sp, sp, #0x10
	bxeq lr
	add r0, sp, #0x10
	add r1, sp, #0x14
	add r3, sp, #0x0
	mov r2, #0x6
	bl FUN_02091498
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	addeq sp, sp, #0x10
	bxeq lr
	cmp r5, #0x0
	ldrne r0, [sp, #0x10]
	strne r0, [r5, #0x0]
	cmp r4, #0x0
	ldrne r0, [sp, #0x0]
	strne r0, [r4, #0x0]
	ldr r2, [sp, #0x0]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r0, r0, r2
	str r0, [sp, #0x10]
	cmp r1, r2
	addcc sp, sp, #0x4
	movcc r0, #0x0
	ldmccia sp!, {r4-r5,lr}
	addcc sp, sp, #0x10
	bxcc lr
	sub r12, r1, r2
	add r0, sp, #0x10
	add r1, sp, #0x14
	add r3, sp, #0x0
	mov r2, #0x5
	str r12, [sp, #0x14]
	bl FUN_02091498
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r2, [sp, #0x0]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r0, r0, r2
	str r0, [sp, #0x10]
	cmp r1, r2
	addcc sp, sp, #0x4
	movcc r0, #0x0
	ldmccia sp!, {r4-r5,lr}
	addcc sp, sp, #0x10
	bxcc lr
	sub r12, r1, r2
	add r0, sp, #0x10
	add r1, sp, #0x14
	add r3, sp, #0x0
	mov r2, #0x4
	str r12, [sp, #0x14]
	bl FUN_02091498
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r1, [sp, #0x20]
	cmp r1, #0x0
	ldrne r0, [sp, #0x10]
	strne r0, [r1, #0x0]
	ldr r1, [sp, #0x24]
	cmp r1, #0x0
	ldrne r0, [sp, #0x0]
	strne r0, [r1, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	add sp, sp, #0x10
	bx lr

	arm_func_start FUN_020913D4
FUN_020913D4:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r1, #0xa
	addcc sp, sp, #0x4
	movcc r0, #0x0
	ldmccia sp!, {lr}
	bxcc lr
	ldrb r12, [r0, #0x0]
	add lr, r0, r1
	cmp r12, #0x1
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {lr}
	bxne lr
	add r12, r0, #0x1
	mov r1, #0x0
_02091414:
	ldrb r0, [r12], #0x1
	cmp r0, #0xff
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {lr}
	bxne lr
	add r1, r1, #0x1
	cmp r1, #0x8
	blt _02091414
	cmp r12, lr
	beq _02091458
_02091440:
	ldrb r0, [r12, #0x0]
	cmp r0, #0xff
	bne _02091458
	add r12, r12, #0x1
	cmp r12, lr
	bne _02091440
_02091458:
	cmp r12, lr
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {lr}
	bxeq lr
	ldrb r0, [r12, #0x0]
	cmp r0, #0x0
	movne r0, #0x0
	addeq r0, r12, #0x1
	subeq r1, lr, r0
	streq r1, [r3, #0x0]
	streq r0, [r2, #0x0]
	moveq r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_02091498
FUN_02091498:
	stmdb sp!, {r4-r6,lr}
	ldr r5, [r0, #0x0]
	mov r6, #0x0
	ldrb r4, [r5, #0x0]
	add r5, r5, #0x1
	mov r12, r6
	cmp r4, r2
	ldr r2, [r1, #0x0]
	movne r0, r6
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	cmp r2, #0x1
	movcc r0, r6
	ldmccia sp!, {r4-r6,lr}
	bxcc lr
	ldrb lr, [r5, #0x0]
	sub r4, r2, #0x1
	ands r2, lr, #0x80
	beq _02091534
	and r2, lr, #0x7f
	and lr, r2, #0xff
	add r2, lr, #0x1
	cmp r4, r2
	movcc r0, r6
	ldmccia sp!, {r4-r6,lr}
	bxcc lr
	cmp r3, #0x0
	sub r6, r4, lr
	beq _0209152C
	ldrb r2, [r5, #0x1]
	add r5, r5, #0x1
	and r4, r2, #0x7f
_02091518:
	sub r2, lr, #0x1
	add r12, r4, r12, lsl #0x7
	ands lr, r2, #0xff
	bne _02091518
	b _02091550
_0209152C:
	add r5, r5, lr
	b _02091550
_02091534:
	add r5, r5, #0x1
	cmp r4, #0x1
	mov r12, lr
	movcc r0, r6
	ldmccia sp!, {r4-r6,lr}
	bxcc lr
	sub r6, r4, #0x1
_02091550:
	str r5, [r0, #0x0]
	str r6, [r1, #0x0]
	cmp r3, #0x0
	strne r12, [r3, #0x0]
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_0209156C
FUN_0209156C: ; 0x0209156C
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x58
	movs r6, r0
	mov r5, r1
	mov r8, r2
	mov r7, r3
	beq _0209159C
	cmp r8, #0x0
	beq _0209159C
	ldr r0, [sp, #0x70]
	cmp r0, #0x0
	bne _020915AC
_0209159C:
	add sp, sp, #0x58
	mvn r0, #0x2
	ldmia sp!, {r4-r8,lr}
	bx lr
_020915AC:
	bl FUN_02094FAC
	mov r4, r0
	add r0, sp, #0x4
	bl FUN_0209502C
	add r0, sp, #0x18
	bl FUN_0209502C
	add r0, sp, #0x2c
	bl FUN_0209502C
	add r0, sp, #0x40
	bl FUN_0209502C
	cmp r4, #0x0
	mvneq r5, #0x1
	beq _02091688
	add r2, sp, #0x4
	mov r0, r8
	mov r1, r7
	bl FUN_02094C68
	cmp r0, #0x0
	mvneq r5, #0x1
	beq _02091688
	ldr r1, [sp, #0x78]
	add r0, sp, #0x2c
	bl FUN_02094D7C
	cmp r0, #0x0
	mvneq r5, #0x1
	beq _02091688
	ldr r0, [sp, #0x70]
	ldr r1, [sp, #0x74]
	add r2, sp, #0x40
	bl FUN_02094C68
	cmp r0, #0x0
	mvneq r5, #0x1
	beq _02091688
	add r0, sp, #0x18
	add r1, sp, #0x4
	add r2, sp, #0x2c
	add r3, sp, #0x40
	str r4, [sp, #0x0]
	bl FUN_020931B8
	cmp r0, #0x0
	mvneq r5, #0x1
	beq _02091688
	add r0, sp, #0x18
	bl FUN_02095188
	add r1, r0, #0x7
	mov r0, r1, asr #0x2
	add r0, r1, r0, lsr #0x1d
	mov r0, r0, asr #0x3
	cmp r0, r5
	mvngt r5, #0x0
	bgt _02091688
	add r0, sp, #0x18
	mov r1, r6
	bl FUN_02094BEC
	mov r5, r0
_02091688:
	add r0, sp, #0x4
	bl FUN_0209510C
	add r0, sp, #0x18
	bl FUN_0209510C
	add r0, sp, #0x2c
	bl FUN_0209510C
	add r0, sp, #0x40
	bl FUN_0209510C
	cmp r4, #0x0
	beq _020916B8
	mov r0, r4
	bl FUN_02094F3C
_020916B8:
	mov r0, r5
	add sp, sp, #0x58
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_020916C8
FUN_020916C8: ; 0x020916C8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x7c
	mov r4, #0x0
	mov r5, r3
	mov r3, r4
	str r3, [sp, #0x34]
	ldr r3, [r5, #0x0]
	str r0, [sp, #0x4]
	mov r0, r4
	ldr r3, [r3, #0x0]
	str r0, [sp, #0x1c]
	str r0, [sp, #0x20]
	ands r0, r3, #0x1
	ldr r0, [sp, #0xa0]
	str r4, [sp, #0x8]
	str r0, [sp, #0xa0]
	mov r7, r1
	mov r6, r2
	addeq sp, sp, #0x7c
	moveq r0, r4
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r1, [r7, #0x4]
	ldr r0, [r0, #0x0]
	cmp r1, #0x0
	str r0, [sp, #0xc]
	beq _0209174C
	cmp r1, #0x1
	bne _02091768
	ldr r0, [r7, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02091768
_0209174C:
	ldr r0, [sp, #0x4]
	mov r1, #0x0
	bl FUN_02094D7C
	add sp, sp, #0x7c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_02091768:
	ldr r1, [r6, #0x4]
	cmp r1, #0x0
	beq _0209178C
	cmp r1, #0x1
	bne _020917A8
	ldr r0, [r6, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020917A8
_0209178C:
	ldr r0, [sp, #0x4]
	mov r1, #0x1
	bl FUN_02094D7C
	add sp, sp, #0x7c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020917A8:
	cmp r1, #0x1
	bne _020917DC
	ldr r0, [r6, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	bne _020917DC
	ldr r0, [sp, #0x4]
	mov r1, r7
	bl FUN_02094E24
	add sp, sp, #0x7c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020917DC:
	ldr r0, [sp, #0xa4]
	str r0, [sp, #0x18]
	cmp r0, #0x0
	bne _02091810
	bl FUN_02092860
	str r0, [sp, #0x18]
	cmp r0, #0x0
	beq _02091E6C
	ldr r2, [sp, #0xa0]
	mov r1, r5
	bl FUN_02092894
	cmp r0, #0x0
	beq _02091E6C
_02091810:
	ldr r3, [sp, #0xa0]
	add r1, sp, #0x34
	mov r4, r3
	ldr r4, [r4, #0x10c]
	mov r0, r6
	mov r2, #0x0
	str r4, [sp, #0x1c]
	bl FUN_02092C28
	cmp r0, #0x0
	beq _02091E6C
	ldr r0, [sp, #0xa0]
	ldr r0, [r0, #0x0]
	add r1, r0, #0x1
	ldr r0, [sp, #0xa0]
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x34]
	ldrb r1, [r0, #0x2]
	ldrb r0, [r0, #0x3]
	str r0, [sp, #0x10]
	add r0, r1, #0x3f
	bl _s32_div_f
	ldr r1, [sp, #0x34]
	mov r4, r0
	add r0, r1, #0x4
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x18]
	ldr r3, [r7, #0x4]
	ldr r10, [r0, #0x24]
	cmp r3, r10
	bne _020918A8
	ldr r1, [r7, #0x0]
	sub r2, r10, #0x1
	ldr r0, [r5, #0x0]
	ldr r1, [r1, r2, lsl #0x2]
	ldr r0, [r0, r2, lsl #0x2]
	cmp r1, r0
	strcc r7, [sp, #0x14]
	blo _02091960
_020918A8:
	cmp r3, r10
	bge _0209191C
	ldr r0, [sp, #0xa0]
	ldr r3, [r0, #0x0]
	add r1, r0, #0x4
	add r2, r3, #0x1
	str r2, [r0, #0x0]
	mov r0, #0x14
	mla r0, r3, r0, r1
	ldr r2, [r7, #0x4]
	mov r1, r0
	str r2, [r1, #0x4]
	mov r1, r10
	str r0, [sp, #0x14]
	bl FUN_0209508C
	ldr r0, [r7, #0x4]
	mov r2, #0x0
	cmp r0, #0x0
	ble _02091960
_020918F4:
	ldr r1, [r7, #0x0]
	ldr r0, [sp, #0x14]
	ldr r1, [r1, r2, lsl #0x2]
	ldr r0, [r0, #0x0]
	str r1, [r0, r2, lsl #0x2]
	ldr r0, [r7, #0x4]
	add r2, r2, #0x1
	cmp r2, r0
	blt _020918F4
	b _02091960
_0209191C:
	ldr r0, [sp, #0xa0]
	mov r2, r5
	ldr r3, [r0, #0x0]
	mov r1, r7
	add r5, r3, #0x1
	str r5, [r0, #0x0]
	add r5, r0, #0x4
	mov r0, #0x14
	mla r0, r3, r0, r5
	ldr r3, [sp, #0xa0]
	str r0, [sp, #0x14]
	bl FUN_02093214
	cmp r0, #0x0
	beq _02091E6C
	ldr r0, [sp, #0x14]
	mov r1, r10
	bl FUN_0209508C
_02091960:
	ldr r0, [sp, #0xa0]
	ldr r3, [r0, #0x0]
	ldr r0, [r6, #0x4]
	add r1, r3, #0x1
	mul r2, r0, r4
	ldr r0, [sp, #0xa0]
	mov r4, r2, lsl #0x1
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r4, r4, #0x7
	add r2, r1, #0x1
	str r2, [r0, #0x0]
	ldr r2, [sp, #0x10]
	ldr r0, [r0, #0x0]
	mul r5, r2, r10
	mov r2, r4, asr #0x1
	add r2, r4, r2, lsr #0x1e
	add r5, r5, r2, asr #0x2
	ldr r2, [sp, #0xa0]
	mov r6, #0x14
	add r2, r2, #0x4
	mla r8, r1, r6, r2
	mla r4, r3, r6, r2
	ldr r1, [sp, #0xa0]
	add r3, r0, #0x1
	mla r7, r0, r6, r2
	str r3, [r1, #0x0]
	mov r0, r1
	ldr r0, [r0, #0x0]
	mla r6, r0, r6, r2
	add r1, r0, #0x1
	ldr r0, [sp, #0xa0]
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0x8]
	cmp r10, r0
	ldrle r0, [sp, #0x4]
	ble _02091A04
	ldr r0, [sp, #0x4]
	mov r1, r10
	bl FUN_02094EBC
_02091A04:
	cmp r0, #0x0
	beq _02091E6C
	ldr r0, [r8, #0x8]
	mov r1, r10, lsl #0x2
	cmp r1, r0
	movle r0, r8
	ble _02091A28
	mov r0, r8
	bl FUN_02094EBC
_02091A28:
	cmp r0, #0x0
	beq _02091E6C
	ldr r1, [r7, #0x8]
	mov r0, r10, lsl #0x1
	str r0, [sp, #0x24]
	cmp r0, r1
	movle r0, r7
	ble _02091A54
	ldr r1, [sp, #0x24]
	mov r0, r7
	bl FUN_02094EBC
_02091A54:
	cmp r0, #0x0
	beq _02091E6C
	ldr r0, [r4, #0x8]
	cmp r5, r0
	movle r0, r4
	ble _02091A78
	mov r1, r5
	mov r0, r4
	bl FUN_02094EBC
_02091A78:
	cmp r0, #0x0
	beq _02091E6C
	ldr r1, [r6, #0x8]
	ldr r0, [sp, #0x24]
	cmp r0, r1
	movle r0, r6
	ble _02091AA0
	ldr r1, [sp, #0x24]
	mov r0, r6
	bl FUN_02094EBC
_02091AA0:
	cmp r0, #0x0
	beq _02091E6C
	ldr r0, [sp, #0x18]
	ldr r11, [r8, #0x0]
	ldr r8, [r7, #0x0]
	ldr r6, [r6, #0x0]
	ldr r1, [r4, #0x0]
	ldr r7, [r0, #0x48]
	ldr r5, [r0, #0x20]
	ldr r3, [sp, #0x18]
	str r1, [sp, #0x38]
	str r10, [sp, #0x0]
	ldr r1, [sp, #0x14]
	ldr r3, [r3, #0xc]
	ldr r1, [r1, #0x0]
	mov r0, r6
	mov r2, r10
	bl FUN_020937E8
	str r7, [sp, #0x0]
	ldr r0, [sp, #0x38]
	mov r1, r6
	mov r2, r5
	mov r3, r10
	bl FUN_02092E30
	ldr r0, [sp, #0x10]
	cmp r0, #0x1
	ble _02091BA8
	ldr r1, [sp, #0x38]
	mov r0, r6
	mov r2, r10
	mov r3, r11
	bl FUN_02092F70
	mov r0, r11
	mov r1, r6
	mov r2, r5
	mov r3, r10
	str r7, [sp, #0x0]
	bl FUN_02092E30
	ldr r0, [sp, #0x10]
	mov r4, #0x1
	cmp r0, #0x1
	ble _02091BA8
	mov r0, r10, lsl #0x2
	str r0, [sp, #0x28]
	add r9, sp, #0x38
_02091B54:
	sub r3, r4, #0x1
	ldr r2, [r9, r3, lsl #0x2]
	ldr r1, [sp, #0x28]
	mov r0, r6
	add r1, r2, r1
	str r1, [r9, r4, lsl #0x2]
	str r10, [sp, #0x0]
	ldr r1, [r9, r3, lsl #0x2]
	mov r2, r10
	mov r3, r11
	bl FUN_020937E8
	str r7, [sp, #0x0]
	ldr r0, [r9, r4, lsl #0x2]
	mov r1, r6
	mov r2, r5
	mov r3, r10
	bl FUN_02092E30
	ldr r0, [sp, #0x10]
	add r4, r4, #0x1
	cmp r4, r0
	blt _02091B54
_02091BA8:
	ldr r3, [sp, #0x34]
	add r0, r3, #0x1
	str r0, [sp, #0x34]
	add r2, r0, #0x1
	ldrb r1, [r3, #0x0]
	str r2, [sp, #0x34]
	ldrb r9, [r3, #0x1]
	cmp r9, #0xff
	bne _02091C28
	cmp r1, #0x0
	bne _02091C28
	add r0, r2, #0x1
	str r0, [sp, #0x34]
	ldrb r1, [r2, #0x0]
	b _02091BF8
_02091BE4:
	add r9, r9, #0x100
	ldr r1, [sp, #0x34]
	add r1, r1, #0x2
	str r1, [sp, #0x34]
	ldrb r1, [r0, #0x1]
_02091BF8:
	ldr r0, [sp, #0x34]
	ldrb r2, [r0, #0x0]
	cmp r2, #0xff
	bne _02091C10
	cmp r1, #0x0
	beq _02091BE4
_02091C10:
	ldr r2, [sp, #0x34]
	add r2, r2, #0x1
	str r2, [sp, #0x34]
	ldrb r0, [r0, #0x0]
	add r0, r0, #0x1
	add r9, r9, r0
_02091C28:
	mov r2, r1, asr #0x1
	add r0, sp, #0x38
	ldr r0, [r0, r2, lsl #0x2]
	mov r1, r8
	mov r2, r10, lsl #0x2
	bl MI_CpuCopy8
	cmp r9, #0x0
	beq _02091E00
	mov r0, #0xff
	str r0, [sp, #0x2c]
	mov r0, #0x0
	str r0, [sp, #0x30]
_02091C58:
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	beq _02091C8C
	mov r3, r0
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x20]
	ldr r3, [r3, #0x0]
	blx r3
	cmp r0, #0x0
	ldr r0, [sp, #0x20]
	add r0, r0, #0x1
	str r0, [sp, #0x20]
	bne _02091E6C
_02091C8C:
	ldr r0, [sp, #0xa0]
	ldr r0, [r0, #0x108]
	ands r0, r0, #0x4000
	bne _02091E6C
	cmp r9, #0x0
	ldr r4, [sp, #0x30]
	ble _02091CE0
_02091CA8:
	mov r0, r6
	mov r1, r8
	mov r2, r10
	mov r3, r11
	bl FUN_02092F70
	str r7, [sp, #0x0]
	mov r0, r8
	mov r1, r6
	mov r2, r5
	mov r3, r10
	bl FUN_02092E30
	add r4, r4, #0x1
	cmp r4, r9
	blt _02091CA8
_02091CE0:
	ldr r2, [sp, #0x34]
	add r0, r2, #0x1
	str r0, [sp, #0x34]
	add r1, r0, #0x1
	ldrb r0, [r2, #0x0]
	str r1, [sp, #0x34]
	ldrb r9, [r2, #0x1]
	cmp r9, #0xff
	bne _02091D60
	cmp r0, #0x0
	bne _02091D60
	add r0, r1, #0x1
	str r0, [sp, #0x34]
	ldrb r0, [r1, #0x0]
	b _02091D30
_02091D1C:
	add r9, r9, #0x100
	ldr r0, [sp, #0x34]
	add r0, r0, #0x2
	str r0, [sp, #0x34]
	ldrb r0, [r1, #0x1]
_02091D30:
	ldr r1, [sp, #0x34]
	ldrb r2, [r1, #0x0]
	cmp r2, #0xff
	bne _02091D48
	cmp r0, #0x0
	beq _02091D1C
_02091D48:
	ldr r2, [sp, #0x34]
	add r2, r2, #0x1
	str r2, [sp, #0x34]
	ldrb r1, [r1, #0x0]
	add r1, r1, #0x1
	add r9, r9, r1
_02091D60:
	cmp r0, #0x0
	bne _02091D70
	cmp r9, #0x0
	beq _02091E00
_02091D70:
	cmp r9, #0x0
	bne _02091D80
	cmp r0, #0x1
	beq _02091DBC
_02091D80:
	mov r1, r0, asr #0x1
	str r10, [sp, #0x0]
	add r0, sp, #0x38
	ldr r3, [r0, r1, lsl #0x2]
	mov r0, r6
	mov r1, r8
	mov r2, r10
	bl FUN_020937E8
	mov r0, r8
	mov r1, r6
	mov r2, r5
	mov r3, r10
	str r7, [sp, #0x0]
	bl FUN_02092E30
	b _02091DF8
_02091DBC:
	ldr r0, [sp, #0x14]
	str r10, [sp, #0x0]
	ldr r3, [r0, #0x0]
	mov r0, r6
	mov r1, r8
	mov r2, r10
	bl FUN_020937E8
	ldr r0, [sp, #0x4]
	str r7, [sp, #0x0]
	ldr r0, [r0, #0x0]
	mov r1, r6
	mov r2, r5
	mov r3, r10
	bl FUN_02092E30
	b _02091E44
_02091DF8:
	cmp r9, #0x0
	bne _02091C58
_02091E00:
	ldr r0, [sp, #0x24]
	mov r2, r10
	cmp r10, r0
	bge _02091E28
	mov r1, #0x0
_02091E14:
	ldr r0, [sp, #0x24]
	str r1, [r8, r2, lsl #0x2]
	add r2, r2, #0x1
	cmp r2, r0
	blt _02091E14
_02091E28:
	ldr r0, [sp, #0x4]
	str r7, [sp, #0x0]
	ldr r0, [r0, #0x0]
	mov r1, r8
	mov r2, r5
	mov r3, r10
	bl FUN_02092E30
_02091E44:
	ldr r0, [sp, #0xa0]
	ldr r0, [r0, #0x108]
	ands r0, r0, #0x4000
	bne _02091E6C
	ldr r0, [sp, #0x4]
	mov r1, r0
	str r10, [r1, #0x4]
	bl FUN_02095040
	mov r0, #0x1
	str r0, [sp, #0x8]
_02091E6C:
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	beq _02091E94
	ldr r3, [r0, #0x0]
	mov r1, #0xff
	mvn r2, #0x0
	blx r3
	cmp r0, #0x0
	movne r0, #0x0
	strne r0, [sp, #0x8]
_02091E94:
	ldr r0, [sp, #0xa4]
	cmp r0, #0x0
	bne _02091EB0
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	beq _02091EB0
	bl FUN_020927E4
_02091EB0:
	ldr r2, [sp, #0xc]
	ldr r1, [sp, #0xa0]
	ldr r0, [sp, #0x8]
	str r2, [r1, #0x0]
	add sp, sp, #0x7c
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_02091ECC
FUN_02091ECC: ; 0x02091ECC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x18c
	mov r10, r0
	mov r0, #0x0
	str r0, [sp, #0x8]
	mov r5, r1
	ldr r1, [sp, #0x8]
	mov r0, r2
	str r2, [sp, #0x4]
	mov r4, r3
	str r1, [sp, #0xc]
	ldr r9, [sp, #0x1b0]
	bl FUN_02095188
	ldr r1, [r5, #0x4]
	mov r8, r0
	cmp r1, #0x0
	beq _02091F28
	cmp r1, #0x1
	bne _02091F44
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02091F44
_02091F28:
	mov r0, r10
	mov r1, #0x0
	bl FUN_02094D7C
	add sp, sp, #0x18c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_02091F44:
	ldr r0, [sp, #0x4]
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _02091F6C
	cmp r1, #0x1
	bne _02091F88
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02091F88
_02091F6C:
	mov r0, r10
	mov r1, #0x1
	bl FUN_02094D7C
	add sp, sp, #0x18c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_02091F88:
	cmp r1, #0x1
	bne _02091FC0
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	bne _02091FC0
	mov r0, r10
	mov r1, r5
	bl FUN_02094E24
	add sp, sp, #0x18c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_02091FC0:
	add r0, sp, #0x18
	bl FUN_020927BC
	add r0, sp, #0x18
	mov r1, r4
	mov r2, r9
	bl FUN_02092744
	cmp r0, #0x0
	ble _0209220C
	add r0, sp, #0x4c
	bl FUN_0209502C
	ldr r2, [r9, #0x0]
	add r1, r9, #0x4
	mov r0, #0x14
	mla r6, r2, r0, r1
	add r1, r2, #0x1
	str r1, [r9, #0x0]
	mov r2, r4
	mov r4, #0x1
	add r0, sp, #0x4c
	mov r1, r5
	mov r3, r9
	str r4, [sp, #0xc]
	bl FUN_02093214
	cmp r0, #0x0
	beq _0209220C
	add r1, sp, #0x4c
	add r3, sp, #0x18
	mov r0, r6
	mov r2, r1
	str r9, [sp, #0x0]
	bl FUN_02092698
	cmp r0, #0x0
	beq _0209220C
	cmp r8, #0x11
	movle r11, r4
	ble _02092068
	cmp r8, #0x100
	movge r11, #0x5
	bge _02092068
	cmp r8, #0x80
	movge r11, #0x4
	movlt r11, #0x3
_02092068:
	sub r0, r11, #0x1
	mov r4, #0x1
	mov r7, r4, lsl r0
	cmp r7, #0x1
	ble _020920C4
	add r5, sp, #0x60
_02092080:
	mov r0, r5
	bl FUN_0209502C
	sub r3, r4, #0x1
	mov r2, #0x14
	add r1, sp, #0x4c
	mla r1, r3, r2, r1
	mov r0, r5
	mov r2, r6
	add r3, sp, #0x18
	str r9, [sp, #0x0]
	bl FUN_02092698
	cmp r0, #0x0
	beq _0209220C
	add r4, r4, #0x1
	cmp r4, r7
	add r5, r5, #0x14
	blt _02092080
_020920C4:
	mov r5, #0x1
	mov r0, r10
	mov r1, r5
	str r4, [sp, #0xc]
	sub r8, r8, #0x1
	bl FUN_02094D7C
	cmp r0, #0x0
	beq _0209220C
	mov r0, r5
	str r0, [sp, #0x10]
	mov r0, #0x0
	str r0, [sp, #0x14]
_020920F4:
	ldr r0, [sp, #0x4]
	mov r1, r8
	bl FUN_02094A8C
	cmp r0, #0x0
	bne _02092140
	cmp r5, #0x0
	bne _02092130
	mov r0, r10
	mov r1, r10
	mov r2, r10
	add r3, sp, #0x18
	str r9, [sp, #0x0]
	bl FUN_02092698
	cmp r0, #0x0
	beq _0209220C
_02092130:
	cmp r8, #0x0
	beq _02092204
	sub r8, r8, #0x1
	b _020920F4
_02092140:
	ldr r6, [sp, #0x10]
	ldr r7, [sp, #0x14]
	cmp r11, #0x1
	mov r4, r6
	ble _02092184
_02092154:
	subs r1, r8, r4
	bmi _02092184
	ldr r0, [sp, #0x4]
	bl FUN_02094A8C
	cmp r0, #0x0
	subne r0, r4, r7
	movne r0, r6, lsl r0
	movne r7, r4
	add r4, r4, #0x1
	orrne r6, r0, #0x1
	cmp r4, r11
	blt _02092154
_02092184:
	cmp r5, #0x0
	add r5, r7, #0x1
	bne _020921C8
	cmp r5, #0x0
	ldr r4, [sp, #0x14]
	ble _020921C8
_0209219C:
	mov r0, r10
	mov r1, r10
	mov r2, r10
	add r3, sp, #0x18
	str r9, [sp, #0x0]
	bl FUN_02092698
	cmp r0, #0x0
	beq _0209220C
	add r4, r4, #0x1
	cmp r4, r5
	blt _0209219C
_020921C8:
	mov r3, r6, asr #0x1
	mov r1, #0x14
	add r0, sp, #0x4c
	mla r2, r3, r1, r0
	mov r0, r10
	mov r1, r10
	add r3, sp, #0x18
	str r9, [sp, #0x0]
	bl FUN_02092698
	cmp r0, #0x0
	beq _0209220C
	add r0, r7, #0x1
	ldr r5, [sp, #0x14]
	subs r8, r8, r0
	bpl _020920F4
_02092204:
	mov r0, #0x1
	str r0, [sp, #0x8]
_0209220C:
	ldr r0, [sp, #0xc]
	ldr r1, [r9, #0x0]
	cmp r0, #0x0
	sub r0, r1, #0x1
	str r0, [r9, #0x0]
	mov r4, #0x0
	ble _02092248
	add r5, sp, #0x4c
_0209222C:
	mov r0, r5
	bl FUN_02095164
	ldr r0, [sp, #0xc]
	add r4, r4, #0x1
	cmp r4, r0
	add r5, r5, #0x14
	blt _0209222C
_02092248:
	add r0, sp, #0x18
	bl FUN_02092788
	ldr r0, [sp, #0x8]
	add sp, sp, #0x18c
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_02092260
FUN_02092260: ; 0x02092260
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	movs r8, r2
	mov r10, r0
	mov r9, r1
	mov r11, #0x0
	mov r5, #0x2
	addeq sp, sp, #0x4
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	mov r0, r8
	bl FUN_020951BC
	cmp r0, #0x20
	beq _020922B4
	mov r1, #0x1
	cmp r10, r1, lsl r0
	addhi sp, sp, #0x4
	movhi r0, r11
	ldmhiia sp!, {r4-r11,lr}
	bxhi lr
_020922B4:
	cmp r10, r8
	rsb r2, r0, #0x20
	subcs r10, r10, r8
	cmp r2, #0x0
	movne r1, r10, lsl r2
	rsbne r0, r2, #0x20
	orrne r10, r1, r9, lsr r0
	movne r8, r8, lsl r2
	ldr r4, _0209239C ; =0x0000FFFF
	movne r9, r9, lsl r2
	and r7, r4, r8, lsr #0x10
	and r6, r8, r4
_020922E4:
	mov r0, r10, lsr #0x10
	cmp r0, r7
	moveq r0, r4
	beq _02092300
	mov r0, r10
	mov r1, r7
	bl _u32_div_f
_02092300:
	mul r12, r0, r7
	mul r3, r0, r6
	and r2, r4, r9, lsr #0x10
_0209230C:
	mov lr, #0x10000
	sub r1, r10, r12
	rsb lr, lr, #0x0
	ands lr, r1, lr
	bne _02092338
	add r1, r2, r1, lsl #0x10
	cmp r3, r1
	subhi r12, r12, r7
	subhi r3, r3, r6
	subhi r0, r0, #0x1
	bhi _0209230C
_02092338:
	mul r2, r0, r6
	and r1, r2, r4
	mul r3, r0, r7
	mov r1, r1, lsl #0x10
	cmp r9, r1
	add r2, r3, r2, lsr #0x10
	addcc r2, r2, #0x1
	cmp r10, r2
	addcc r10, r10, r8
	sub r9, r9, r1
	subcc r0, r0, #0x1
	sub r1, r10, r2
	subs r5, r5, #0x1
	beq _0209238C
	and r2, r0, r4
	mov r1, r1, lsl #0x10
	and r0, r9, r4
	orr r10, r1, r9, lsr #0x10
	mov r11, r2, lsl #0x10
	mov r9, r0, lsl #0x10
	b _020922E4
_0209238C:
	orr r0, r11, r0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209239C: .word 0x0000FFFF

	arm_func_start FUN_020923A0
FUN_020923A0: ; 0x020923A0
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x18
	mov r8, r0
	add r0, sp, #0x4
	mov r7, r1
	mov r6, r2
	mov r5, r3
	mvn r4, #0x0
	bl FUN_0209502C
	add r0, sp, #0x4
	mov r1, #0x0
	bl FUN_02094D7C
	add r0, sp, #0x4
	mov r1, r6
	bl FUN_02094AFC
	cmp r0, #0x0
	beq _02092404
	add r2, sp, #0x4
	mov r0, r8
	mov r3, r7
	mov r1, #0x0
	str r5, [sp, #0x0]
	bl FUN_02093248
	cmp r0, #0x0
	movne r4, r6
_02092404:
	add r0, sp, #0x4
	bl FUN_0209510C
	mov r0, r4
	add sp, sp, #0x18
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_0209241C
FUN_0209241C: ; 0x0209241C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	ldr r6, [sp, #0x30]
	mov r9, r1
	ldr r11, [r6, #0x0]
	movs r10, r0
	add r0, r11, #0x1
	str r0, [r6, #0x0]
	ldr r7, [r6, #0x0]
	add r4, r6, #0x4
	mov r0, #0x14
	mla r5, r11, r0, r4
	add r12, r7, #0x1
	mov r1, #0x0
	str r5, [sp, #0x4]
	mla r5, r7, r0, r4
	str r12, [r6, #0x0]
	str r1, [sp, #0x0]
	ldreq r1, [r6, #0x0]
	mov r8, r2
	mlaeq r10, r1, r0, r4
	addeq r0, r1, #0x1
	streq r0, [r6, #0x0]
	mov r7, r3
	cmp r9, #0x0
	bne _0209249C
	ldr r2, [r6, #0x0]
	add r1, r6, #0x4
	mov r0, #0x14
	mla r9, r2, r0, r1
	add r0, r2, #0x1
	str r0, [r6, #0x0]
_0209249C:
	mov r0, r8
	mov r1, r7
	bl FUN_02094B98
	cmp r0, #0x0
	bge _020924DC
	mov r0, r10
	mov r1, #0x0
	bl FUN_02094D7C
	mov r0, r9
	mov r1, r8
	bl FUN_02094E24
	add sp, sp, #0xc
	str r11, [r6, #0x0]
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020924DC:
	mov r0, r8
	bl FUN_02095188
	ldr r1, [r7, #0x28]
	mov r2, r0
	mov r0, r1, lsl #0x1
	cmp r0, r2
	movgt r2, r0
	suble r0, r2, r0
	movgt r4, #0x0
	addle r0, r0, r0, lsr #0x1f
	movle r4, r0, asr #0x1
	ldr r1, [r7, #0x2c]
	add r0, r2, r2, lsr #0x1f
	mov r0, r0, asr #0x1
	cmp r2, r1
	str r0, [sp, #0x8]
	beq _02092534
	mov r1, r7
	mov r3, r6
	add r0, r7, #0x14
	bl FUN_020923A0
	str r0, [r7, #0x2c]
_02092534:
	ldr r2, [sp, #0x8]
	ldr r0, [sp, #0x4]
	mov r1, r8
	sub r2, r2, r4
	bl FUN_02094134
	cmp r0, #0x0
	beq _02092684
	ldr r1, [sp, #0x4]
	mov r0, r5
	mov r3, r6
	add r2, r7, #0x14
	bl FUN_0209390C
	cmp r0, #0x0
	beq _02092684
	ldr r2, [sp, #0x8]
	mov r0, r10
	mov r1, r5
	add r2, r2, r4
	bl FUN_02094134
	cmp r0, #0x0
	beq _02092684
	mov r4, #0x0
	mov r0, r5
	mov r1, r7
	mov r2, r10
	mov r3, r6
	str r4, [r10, #0xc]
	bl FUN_0209390C
	cmp r0, #0x0
	beq _02092684
	mov r0, r9
	mov r1, r8
	mov r2, r5
	bl FUN_02093B50
	cmp r0, #0x0
	beq _02092684
	mov r5, r4
	mov r0, r9
	mov r1, r7
	str r5, [r9, #0xc]
	bl FUN_02094B98
	cmp r0, #0x0
	blt _02092630
	mov r4, #0x1
_020925E4:
	cmp r5, #0x2
	add r5, r5, #0x1
	bgt _02092684
	mov r0, r9
	mov r1, r9
	mov r2, r7
	bl FUN_02093B50
	cmp r0, #0x0
	beq _02092684
	mov r0, r10
	mov r1, r4
	bl FUN_0209400C
	cmp r0, #0x0
	beq _02092684
	mov r0, r9
	mov r1, r7
	bl FUN_02094B98
	cmp r0, #0x0
	bge _020925E4
_02092630:
	ldr r0, [r9, #0x4]
	mov r1, #0x1
	cmp r0, #0x0
	beq _0209265C
	cmp r0, #0x1
	bne _02092658
	ldr r0, [r9, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0209265C
_02092658:
	mov r1, #0x0
_0209265C:
	cmp r1, #0x0
	movne r0, #0x0
	ldreq r0, [r8, #0xc]
	str r0, [r9, #0xc]
	mov r0, #0x1
	ldr r2, [r8, #0xc]
	ldr r1, [r7, #0xc]
	str r0, [sp, #0x0]
	eor r0, r2, r1
	str r0, [r10, #0xc]
_02092684:
	ldr r0, [sp, #0x0]
	str r11, [r6, #0x0]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_02092698
FUN_02092698:
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	ldr r4, [sp, #0x20]
	mov r12, #0x14
	ldr r5, [r4, #0x0]
	add lr, r4, #0x4
	mla r6, r5, r12, lr
	add r12, r5, #0x1
	mov r8, r0
	mov r7, r3
	str r12, [r4, #0x0]
	cmp r2, #0x0
	mov r5, #0x0
	beq _02092708
	cmp r1, r2
	bne _020926F0
	mov r0, r6
	mov r2, r4
	bl FUN_0209305C
	cmp r0, #0x0
	bne _0209270C
	b _02092728
_020926F0:
	mov r0, r6
	mov r3, r4
	bl FUN_0209390C
	cmp r0, #0x0
	bne _0209270C
	b _02092728
_02092708:
	mov r6, r1
_0209270C:
	mov r1, r8
	mov r2, r6
	mov r3, r7
	mov r0, #0x0
	str r4, [sp, #0x0]
	bl FUN_0209241C
	mov r5, #0x1
_02092728:
	ldr r1, [r4, #0x0]
	mov r0, r5
	sub r1, r1, #0x1
	str r1, [r4, #0x0]
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_02092744
FUN_02092744:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl FUN_02094E24
	add r0, r5, #0x14
	mov r1, #0x0
	bl FUN_02094D7C
	mov r0, r4
	bl FUN_02095188
	str r0, [r5, #0x28]
	mov r0, #0x0
	str r0, [r5, #0x2c]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02092788
FUN_02092788: ; 0x02092788
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_0209510C
	add r0, r4, #0x14
	bl FUN_0209510C
	ldr r0, [r4, #0x30]
	ands r0, r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, r4
	bl CallCustomDestructor
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020927BC
FUN_020927BC: ; 0x020927BC
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_0209502C
	add r0, r4, #0x14
	bl FUN_0209502C
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x30]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020927E4
FUN_020927E4: ; 0x020927E4
	stmdb sp!, {r4,lr}
	mov r4, r0
	add r0, r4, #0xc
	bl FUN_0209510C
	add r0, r4, #0x20
	bl FUN_0209510C
	add r0, r4, #0x34
	bl FUN_0209510C
	ldr r0, [r4, #0x4c]
	ands r0, r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, r4
	bl CallCustomDestructor
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02092824
FUN_02092824: ; 0x02092824
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r1, #0x0
	str r1, [r4, #0x0]
	add r0, r4, #0xc
	str r1, [r4, #0x8]
	bl FUN_0209502C
	add r0, r4, #0x20
	bl FUN_0209502C
	add r0, r4, #0x34
	bl FUN_0209502C
	mov r0, #0x0
	str r0, [r4, #0x4c]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02092860
FUN_02092860: ; 0x02092860
	stmdb sp!, {r4,lr}
	mov r0, #0x50
	bl CallCustomAllocator
	movs r4, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl FUN_02092824
	mov r1, #0x1
	mov r0, r4
	str r1, [r4, #0x4c]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02092894
FUN_02092894:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov r6, r1
	ldr r3, [r6, #0x4]
	mov r7, r0
	cmp r3, #0x0
	mov r5, r2
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	add r0, r7, #0x20
	add r4, r7, #0xc
	bl FUN_02094E24
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	add r0, sp, #0x0
	bl FUN_0209502C
	mov r1, #0x1
	mov r0, r6
	str r1, [r7, #0x0]
	bl FUN_02095188
	add r1, r0, #0x1f
	mov r0, r1, asr #0x4
	add r0, r1, r0, lsr #0x1b
	mov r2, r0, asr #0x5
	mov r0, r4
	mov r1, #0x0
	str r2, [r7, #0x8]
	bl FUN_02094D7C
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r4
	mov r1, #0x20
	bl FUN_02094AFC
	cmp r0, #0x0
	beq _02092A38
	ldr r0, [r6, #0x0]
	ldr r4, [r0, #0x0]
	mov r0, r4
	bl FUN_02092D9C
	mov r1, r0
	add r0, sp, #0x0
	bl FUN_02094D7C
	cmp r0, #0x0
	beq _02092A38
	add r0, sp, #0x0
	mov r2, #0x20
	mov r1, r0
	bl FUN_02094250
	cmp r0, #0x0
	beq _02092A38
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020929B0
	cmp r0, #0x1
	bne _020929A0
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020929B0
_020929A0:
	add r0, sp, #0x0
	mov r1, #0x1
	bl FUN_02093EAC
	b _020929C4
_020929B0:
	add r0, sp, #0x0
	mvn r1, #0x0
	bl FUN_02094D7C
	cmp r0, #0x0
	beq _02092A38
_020929C4:
	ldr r2, [sp, #0x4]
	cmp r2, #0x1
	ldrge r0, [sp, #0x0]
	ldrge r1, [r0, #0x0]
	movlt r1, #0x0
	cmp r2, #0x2
	ldrge r0, [sp, #0x0]
	mov r2, r4
	ldrge r0, [r0, #0x4]
	movlt r0, #0x0
	bl FUN_02092260
	str r0, [r7, #0x48]
	add r0, r7, #0xc
	mov r1, #0x0
	bl FUN_02094D7C
	ldr r1, [r7, #0x8]
	add r0, r7, #0xc
	mov r1, r1, lsl #0x6
	bl FUN_02094AFC
	cmp r0, #0x0
	beq _02092A38
	add r0, r7, #0xc
	mov r1, r0
	mov r3, r5
	add r2, r7, #0x20
	bl FUN_02093214
	ldr r1, [r7, #0x8]
	add r0, r7, #0xc
	bl FUN_0209508C
_02092A38:
	add r0, sp, #0x0
	bl FUN_0209510C
	mov r0, #0x1
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_02092A50
FUN_02092A50: ; 0x02092A50
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r4, r2
	mov r7, r1
	cmp r4, #0x6
	mov r5, r0
	movgt r4, #0x6
	mov r1, #0x1
	mov r2, r1, lsl r4
	ldr r0, [r7, #0x4]
	sub r2, r2, #0x1
	add r0, r4, r0, lsl #0x5
	ldr r3, _02092C24 ; =UNK_02106170
	str r2, [sp, #0x0]
	ldr r2, [r3, r4, lsl #0x2]
	mov r1, r4
	sub r0, r0, #0x1
	str r2, [sp, #0x4]
	mov r6, #0x0
	bl _s32_div_f
	mov r12, #0x0
	mov r0, r0, lsl #0x1
	add r0, r0, #0x2
	mov r8, r6
	add r1, r5, r0
	strb r8, [r5, r0]
	strb r8, [r1, #-0x1]
	ldr r0, [r7, #0x0]
	ldr r2, [r7, #0x4]
	ldr r7, [r0, #0x0]
	add lr, r0, #0x4
	cmp r2, #0x1
	sub r9, r1, #0x2
	ldrgt r8, [lr], #0x4
	mov r10, r7
	mov r0, r12
	str r12, [sp, #0x8]
	mov r1, #0xff
	mov r11, r12
_02092AEC:
	ldr r3, [sp, #0x0]
	and r3, r10, r3
	ldr r10, [sp, #0x4]
	ldrb r10, [r10, r3]
	cmp r10, #0x0
	beq _02092B4C
	add r12, r12, r10
	add r6, r6, r10
	cmp r6, #0x20
	blo _02092B34
	cmp r2, #0x1
	ble _02092B4C
	sub r2, r2, #0x1
	mov r7, r8
	cmp r2, #0x1
	movle r8, r11
	ldrgt r8, [lr], #0x4
	sub r6, r6, #0x20
_02092B34:
	cmp r6, #0x0
	moveq r10, r7
	movne r10, r7, lsr r6
	rsbne r3, r6, #0x20
	orrne r10, r10, r8, lsl r3
	b _02092AEC
_02092B4C:
	cmp r3, #0x0
	beq _02092BD0
	strb r12, [r9, #0x0]
	strb r3, [r9, #-0x1]
	cmp r12, #0x100
	sub r9, r9, #0x2
	blo _02092B88
	cmp r12, #0x100
	blo _02092B88
_02092B70:
	strb r1, [r9, #0x0]
	sub r12, r12, #0x100
	strb r0, [r9, #-0x1]
	sub r9, r9, #0x2
	cmp r12, #0x100
	bhs _02092B70
_02092B88:
	mov r12, r4
	add r6, r6, r4
	cmp r6, #0x20
	blo _02092BB8
	cmp r2, #0x1
	ble _02092BD0
	sub r2, r2, #0x1
	mov r7, r8
	cmp r2, #0x1
	ldrle r8, [sp, #0x8]
	sub r6, r6, #0x20
	ldrgt r8, [lr], #0x4
_02092BB8:
	cmp r6, #0x0
	moveq r10, r7
	movne r10, r7, lsr r6
	rsbne r3, r6, #0x20
	orrne r10, r10, r8, lsl r3
	b _02092AEC
_02092BD0:
	add r9, r9, #0x1
	mov r0, #0x2
	b _02092BF4
_02092BDC:
	strb r2, [r5, #0x0]
	ldrb r1, [r9, #0x1]
	add r9, r9, #0x2
	add r0, r0, #0x2
	strb r1, [r5, #0x1]
	add r5, r5, #0x2
_02092BF4:
	ldrb r2, [r9, #0x0]
	cmp r2, #0x0
	bne _02092BDC
	ldrb r1, [r9, #0x1]
	cmp r1, #0x0
	bne _02092BDC
	mov r1, #0x0
	strb r1, [r5, #0x0]
	strb r1, [r5, #0x1]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_02092C24: .word UNK_02106170

	arm_func_start FUN_02092C28
FUN_02092C28:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r5, [r3], #0x4
	mov r2, #0x14
	mla r4, r5, r2, r3
	mov r9, r0
	ldr r0, [r9, #0x4]
	mov r8, r1
	cmp r0, #0x0
	mov r5, #0x0
	mov r1, r0, lsl #0x5
	addeq sp, sp, #0x4
	moveq r0, r5
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	cmp r0, #0x1
	bne _02092CC8
	cmp r0, #0x1
	bne _02092C8C
	ldr r2, [r9, #0x0]
	ldr r1, _02092D8C ; =0x00010001
	ldr r2, [r2, #0x0]
	cmp r2, r1
	ldreq r5, _02092D90 ; =UNK_020FF500
	beq _02092CB8
_02092C8C:
	ldr r1, [r9, #0x0]
	ldr r1, [r1, #0x0]
	cmp r1, #0x11
	bne _02092CA8
	cmp r0, #0x1
	ldreq r5, _02092D94 ; =UNK_020FF518
	beq _02092CB8
_02092CA8:
	cmp r1, #0x3
	bne _02092CB8
	cmp r0, #0x1
	ldreq r5, _02092D98 ; =UNK_020FF50C
_02092CB8:
	mov r7, #0x1
	mov r6, r7
	mov r1, #0x20
	b _02092CF8
_02092CC8:
	cmp r1, #0x100
	movge r7, #0x5
	movge r6, #0x10
	movge r1, #0x7
	bge _02092CF8
	cmp r1, #0x80
	movge r6, #0x8
	movge r1, r6
	movge r7, #0x4
	movlt r7, #0x3
	movlt r6, #0x4
	movlt r1, #0xb
_02092CF8:
	mul r1, r0, r1
	mov r0, r1, lsl #0x1
	add r1, r0, #0x7
	mov r0, r1, asr #0x1
	add r0, r1, r0, lsr #0x1e
	cmp r5, #0x0
	mov r1, r0, asr #0x2
	bne _02092D74
	ldr r0, [r4, #0x8]
	cmp r1, r0
	movle r0, r4
	ble _02092D30
	mov r0, r4
	bl FUN_02094EBC
_02092D30:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r5, [r4, #0x0]
	mov r1, r9
	mov r2, r7
	add r0, r5, #0x4
	bl FUN_02092A50
	add r1, r0, #0x2
	mov r0, r1, asr #0x8
	strb r0, [r5, #0x0]
	strb r1, [r5, #0x1]
	strb r7, [r5, #0x2]
	strb r6, [r5, #0x3]
	b _02092D78
_02092D74:
	mov r1, #0x8
_02092D78:
	str r5, [r8, #0x0]
	add r0, r1, #0x2
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_02092D8C: .word 0x00010001
_02092D90: .word UNK_020FF500
_02092D94: .word UNK_020FF518
_02092D98: .word UNK_020FF50C

	arm_func_start FUN_02092D9C
FUN_02092D9C: ; 0x02092D9C
	stmdb sp!, {r4-r10,lr}
	mov r10, r0
	mov r1, r10
	rsb r0, r10, #0x0
	bl _u32_div_f
	movs r8, r1
	mov r7, r10
	mov r5, #0x0
	mov r6, #0x1
	mvn r4, #0x0
	beq _02092E04
_02092DC8:
	mov r0, r7
	mov r1, r8
	bl _u32_div_f
	mov r9, r1
	mov r0, r7
	mov r1, r8
	bl _u32_div_f
	mla r1, r0, r6, r5
	mov r5, r6
	mov r7, r8
	mov r6, r1
	mov r8, r9
	cmp r9, #0x0
	rsb r4, r4, #0x0
	bne _02092DC8
_02092E04:
	cmp r4, #0x0
	sublt r5, r10, r5
	cmp r7, #0x1
	movne r1, #0x0
	bne _02092E24
	mov r0, r5
	mov r1, r10
	bl _u32_div_f
_02092E24:
	mov r0, r1
	ldmia sp!, {r4-r10,lr}
	bx lr

	arm_func_start FUN_02092E30
FUN_02092E30: ; 0x02092E30
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r7, r3
	mov r9, r1
	mov r6, #0x0
	mov r10, r0
	mov r8, r2
	mov r4, r6
	cmp r7, #0x0
	add r5, r9, r7, lsl #0x2
	ldr r11, [sp, #0x30]
	ble _02092EC0
	mov r0, #0x1
	str r6, [sp, #0x4]
	str r0, [sp, #0x0]
_02092E6C:
	ldr r1, [r9, #0x0]
	mov r0, r9
	mul r3, r1, r11
	mov r1, r8
	mov r2, r7
	bl FUN_020948AC
	add r1, r0, r6
	ldr r0, [r5, #0x0]
	cmp r1, r6
	ldrcc r6, [sp, #0x0]
	add r0, r0, r1
	str r0, [r5, #0x0]
	ldr r0, [r5, #0x0]
	ldrcs r6, [sp, #0x4]
	cmp r0, r1
	add r4, r4, #0x1
	addcc r6, r6, #0x1
	cmp r4, r7
	add r9, r9, #0x4
	add r5, r5, #0x4
	blt _02092E6C
_02092EC0:
	cmp r6, #0x0
	sub r2, r7, #0x1
	bne _02092F14
	ldr r1, [r9, r2, lsl #0x2]
	ldr r0, [r8, r2, lsl #0x2]
	cmp r1, r0
	bne _02092F00
	cmp r2, #0x0
	ble _02092F00
_02092EE4:
	ldr r1, [r9, r2, lsl #0x2]
	ldr r0, [r8, r2, lsl #0x2]
	cmp r1, r0
	bne _02092F00
	sub r2, r2, #0x1
	cmp r2, #0x0
	bgt _02092EE4
_02092F00:
	ldr r1, [r9, r2, lsl #0x2]
	ldr r0, [r8, r2, lsl #0x2]
	cmp r1, r0
	movcs r6, #0x1
	movcc r6, #0x0
_02092F14:
	cmp r6, #0x0
	beq _02092F3C
	mov r0, r10
	mov r1, r9
	mov r2, r8
	mov r3, r7
	bl FUN_02094354
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
_02092F3C:
	cmp r7, #0x0
	addle sp, sp, #0xc
	mov r1, #0x0
	ldmleia sp!, {r4-r11,lr}
	bxle lr
_02092F50:
	ldr r0, [r9, r1, lsl #0x2]
	str r0, [r10, r1, lsl #0x2]
	add r1, r1, #0x1
	cmp r1, r7
	blt _02092F50
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_02092F70
FUN_02092F70:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r11, r2
	mov r6, r11, lsl #0x1
	mov r10, r0
	mov r7, r11
	mov r9, r1
	sub r7, r7, #0x1
	sub r2, r6, #0x1
	mov r0, #0x0
	str r0, [r10, r2, lsl #0x2]
	ldr r0, [r10, r2, lsl #0x2]
	str r3, [sp, #0x0]
	mov r5, r9
	str r0, [r10, #0x0]
	cmp r7, #0x0
	add r4, r10, #0x4
	ble _02092FD8
	add r5, r5, #0x4
	ldr r3, [r9, #0x0]
	mov r0, r4
	mov r1, r5
	mov r2, r7
	bl FUN_0209470C
	str r0, [r4, r7, lsl #0x2]
	add r4, r4, #0x8
_02092FD8:
	sub r8, r11, #0x2
	cmp r8, #0x0
	ble _02093018
_02092FE4:
	mov r0, r5
	sub r7, r7, #0x1
	add r5, r5, #0x4
	ldr r3, [r0, #0x0]
	mov r0, r4
	mov r1, r5
	mov r2, r7
	bl FUN_020948AC
	sub r8, r8, #0x1
	str r0, [r4, r7, lsl #0x2]
	cmp r8, #0x0
	add r4, r4, #0x8
	bgt _02092FE4
_02093018:
	mov r0, r10
	mov r1, r10
	mov r2, r10
	mov r3, r6
	bl FUN_02094468
	ldr r0, [sp, #0x0]
	mov r1, r9
	mov r2, r11
	bl FUN_020945B8
	ldr r2, [sp, #0x0]
	mov r0, r10
	mov r1, r10
	mov r3, r6
	bl FUN_02094468
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_0209305C
FUN_0209305C:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x64
	ldr r5, [r2, #0x0]
	mov r9, r0
	mov r8, r1
	cmp r8, r9
	add r3, r2, #0x4
	mov r2, #0x14
	movne r7, r9
	addeq r0, r5, #0x1
	mla r4, r5, r2, r3
	mlaeq r7, r0, r2, r3
	ldr r5, [r8, #0x4]
	cmp r5, #0x0
	movle r0, #0x0
	strle r0, [r9, #0x4]
	addle sp, sp, #0x64
	movle r0, #0x1
	ldmleia sp!, {r4-r9,lr}
	bxle lr
	ldr r0, [r7, #0x8]
	mov r6, r5, lsl #0x1
	cmp r6, r0
	movle r0, r7
	ble _020930CC
	mov r0, r7
	mov r1, r6
	bl FUN_02094EBC
_020930CC:
	cmp r0, #0x0
	addeq sp, sp, #0x64
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	str r6, [r7, #0x4]
	mov r0, #0x0
	str r0, [r7, #0xc]
	cmp r5, #0x4
	bne _0209310C
	ldr r0, [r7, #0x0]
	ldr r1, [r8, #0x0]
	add r3, sp, #0x0
	mov r2, #0x4
	bl FUN_02092F70
	b _02093170
_0209310C:
	cmp r5, #0x8
	bne _0209312C
	ldr r0, [r7, #0x0]
	ldr r1, [r8, #0x0]
	add r3, sp, #0x20
	mov r2, #0x8
	bl FUN_02092F70
	b _02093170
_0209312C:
	ldr r0, [r4, #0x8]
	cmp r6, r0
	movle r0, r4
	ble _02093148
	mov r0, r4
	mov r1, r6
	bl FUN_02094EBC
_02093148:
	cmp r0, #0x0
	addeq sp, sp, #0x64
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r0, [r7, #0x0]
	ldr r1, [r8, #0x0]
	ldr r3, [r4, #0x0]
	mov r2, r5
	bl FUN_02092F70
_02093170:
	cmp r6, #0x0
	ble _02093194
	ldr r1, [r7, #0x0]
	sub r0, r6, #0x1
	ldr r0, [r1, r0, lsl #0x2]
	cmp r0, #0x0
	ldreq r0, [r7, #0x4]
	subeq r0, r0, #0x1
	streq r0, [r7, #0x4]
_02093194:
	cmp r7, r9
	beq _020931A8
	mov r0, r9
	mov r1, r7
	bl FUN_02094E24
_020931A8:
	mov r0, #0x1
	add sp, sp, #0x64
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_020931B8
FUN_020931B8:
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r12, [r3, #0x4]
	cmp r12, #0x0
	ble _020931FC
	ldr r12, [r3, #0x0]
	ldr r12, [r12, #0x0]
	ands r12, r12, #0x1
	beq _020931FC
	ldr lr, [sp, #0x10]
	mov r12, #0x0
	str lr, [sp, #0x0]
	str r12, [sp, #0x4]
	bl FUN_020916C8
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr
_020931FC:
	ldr r12, [sp, #0x10]
	str r12, [sp, #0x0]
	bl FUN_02091ECC
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_02093214
FUN_02093214:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r12, r2
	str r3, [sp, #0x0]
	mov r1, r0
	mov r2, lr
	mov r3, r12
	mov r0, #0x0
	bl FUN_02093248
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_02093248
FUN_02093248:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4c
	mov r6, r3
	ldr r3, [r6, #0x4]
	mov r8, r0
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	cmp r3, #0x0
	ldr r4, [sp, #0x70]
	beq _02093288
	cmp r3, #0x1
	bne _02093298
	ldr r0, [r6, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02093298
_02093288:
	add sp, sp, #0x4c
	mov r0, #0x0
	ldmia sp!, {r4-r11,lr}
	bx lr
_02093298:
	ldr r0, [sp, #0x4]
	mov r1, r6
	bl FUN_02094B98
	cmp r0, #0x0
	bge _020932F8
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _020932D4
	ldr r1, [sp, #0x4]
	bl FUN_02094E24
	cmp r0, #0x0
	addeq sp, sp, #0x4c
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
_020932D4:
	cmp r8, #0x0
	beq _020932E8
	mov r0, r8
	mov r1, #0x0
	bl FUN_02094D7C
_020932E8:
	add sp, sp, #0x4c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020932F8:
	ldr r3, [r4, #0x0]
	add r0, r4, #0x4
	mov r2, #0x14
	mla r1, r3, r2, r0
	mov r3, #0x0
	str r3, [r1, #0xc]
	ldr r5, [r4, #0x0]
	str r1, [sp, #0x14]
	add r4, r5, #0x1
	mla r1, r4, r2, r0
	add r3, r5, #0x2
	str r1, [sp, #0x18]
	mla r1, r3, r2, r0
	cmp r8, #0x0
	str r1, [sp, #0x1c]
	addeq r1, r5, #0x3
	mlaeq r8, r1, r2, r0
	mov r0, r6
	bl FUN_02095188
	mov r1, r0, lsr #0x1f
	rsb r0, r1, r0, lsl #0x1b
	add r0, r1, r0, ror #0x1b
	rsb r0, r0, #0x20
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x1c]
	ldr r2, [sp, #0x8]
	mov r1, r6
	bl FUN_02094250
	cmp r0, #0x0
	addeq sp, sp, #0x4c
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r2, [sp, #0x8]
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x4]
	ldr r3, [sp, #0x1c]
	mov r4, #0x0
	add r2, r2, #0x20
	str r4, [r3, #0xc]
	bl FUN_02094250
	cmp r0, #0x0
	addeq sp, sp, #0x4c
	moveq r0, r4
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r0, [sp, #0x18]
	mov r1, r4
	str r1, [r0, #0xc]
	ldr r0, [sp, #0x1c]
	ldr r0, [r0, #0x4]
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x28]
	ldr r4, [r0, #0x4]
	add r0, sp, #0x38
	sub r1, r4, r1
	str r1, [sp, #0x10]
	bl FUN_0209502C
	ldr r0, [sp, #0x18]
	ldr r2, [r0, #0x0]
	ldr r0, [sp, #0x28]
	sub r1, r0, #0x1
	ldr r0, [sp, #0x10]
	add r0, r2, r0, lsl #0x2
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x28]
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x18]
	ldr r2, [r0, #0x8]
	ldr r0, [sp, #0x28]
	cmp r0, #0x1
	add r0, r2, #0x1
	str r0, [sp, #0x40]
	ldr r0, [sp, #0x1c]
	moveq r5, #0x0
	ldr r2, [r0, #0x0]
	ldr r0, [r2, r1, lsl #0x2]
	str r0, [sp, #0x24]
	ldrne r0, [sp, #0x28]
	subne r0, r0, #0x2
	ldrne r5, [r2, r0, lsl #0x2]
	ldr r0, [sp, #0x18]
	ldr r2, [r8, #0x8]
	ldr r1, [r0, #0x0]
	sub r0, r4, #0x1
	add r7, r1, r0, lsl #0x2
	ldr r0, [sp, #0x10]
	add r1, r0, #0x1
	cmp r1, r2
	movle r0, r8
	ble _02093470
	mov r0, r8
	bl FUN_02094EBC
_02093470:
	cmp r0, #0x0
	beq _020937D4
	ldr r0, [sp, #0x4]
	ldr r1, [r6, #0xc]
	ldr r3, [r0, #0xc]
	ldr r0, [sp, #0x10]
	sub r2, r0, #0x1
	eor r0, r3, r1
	str r0, [r8, #0xc]
	ldr r0, [sp, #0x10]
	str r0, [r8, #0x4]
	ldr r0, [sp, #0x28]
	ldr r3, [r8, #0x0]
	add r1, r0, #0x1
	add r0, r3, r2, lsl #0x2
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x14]
	ldr r0, [r0, #0x8]
	cmp r1, r0
	ldrle r0, [sp, #0x14]
	ble _020934CC
	ldr r0, [sp, #0x14]
	bl FUN_02094EBC
_020934CC:
	cmp r0, #0x0
	beq _020937D4
	ldr r1, [sp, #0x1c]
	add r0, sp, #0x38
	bl FUN_02094B98
	cmp r0, #0x0
	blt _02093520
	add r0, sp, #0x38
	ldr r2, [sp, #0x1c]
	mov r1, r0
	bl FUN_02093B50
	cmp r0, #0x0
	beq _020937D4
	ldr r0, [sp, #0x20]
	mov r2, #0x1
	str r2, [r0, #0x0]
	ldr r0, [r8, #0x4]
	ldr r1, [r8, #0x0]
	sub r0, r0, #0x1
	str r2, [r1, r0, lsl #0x2]
	b _0209352C
_02093520:
	ldr r0, [r8, #0x4]
	sub r0, r0, #0x1
	str r0, [r8, #0x4]
_0209352C:
	ldr r0, [sp, #0x10]
	sub r1, r0, #0x1
	ldr r0, [sp, #0x20]
	cmp r1, #0x0
	sub r0, r0, #0x4
	str r0, [sp, #0x20]
	mov r0, #0x0
	str r0, [sp, #0xc]
	ble _0209377C
	ldr r8, _020937E4 ; =0x0000FFFF
	cmp r1, #0x0
	and r0, r5, r8
	str r0, [sp, #0x2c]
	and r0, r8, r5, lsr #0x10
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x24]
	and r4, r0, r8
	ble _0209377C
	and r9, r8, r0, lsr #0x10
	mvn r0, #0x0
	str r0, [sp, #0x34]
_02093580:
	ldr r1, [sp, #0x38]
	ldr r0, [sp, #0x3c]
	sub r1, r1, #0x4
	add r0, r0, #0x1
	str r0, [sp, #0x3c]
	str r1, [sp, #0x38]
	ldr r11, [r7, #0x0]
	ldr r0, [sp, #0x24]
	ldr r5, [r7, #-0x4]
	cmp r11, r0
	ldreq r6, [sp, #0x34]
	beq _020935C4
	ldr r2, [sp, #0x24]
	mov r0, r11
	mov r1, r5
	bl FUN_02092260
	mov r6, r0
_020935C4:
	ldr r0, [sp, #0x2c]
	and r2, r6, r8
	mul r12, r0, r2
	ldr r0, [sp, #0x30]
	and lr, r8, r6, lsr #0x10
	ldr r1, [sp, #0x30]
	mul r0, r2, r0
	mul r3, r1, lr
	ldr r1, [sp, #0x2c]
	mul r10, r9, lr
	mla r1, lr, r1, r0
	cmp r1, r0
	addcc r3, r3, #0x10000
	and r0, r8, r1, lsr #0x10
	add r3, r3, r0
	and r0, r1, r8
	add r12, r12, r0, lsl #0x10
	cmp r12, r0, lsl #0x10
	mul r0, r2, r9
	mul r1, r4, r2
	mla r2, lr, r4, r0
	addcc r3, r3, #0x1
	cmp r2, r0
	addcc r10, r10, #0x10000
	and r0, r8, r2, lsr #0x10
	add r10, r10, r0
	and r0, r2, r8
	add r1, r1, r0, lsl #0x10
	cmp r1, r0, lsl #0x10
	addcc r10, r10, #0x1
	sub r1, r5, r1
	cmp r1, r5
	addhi r10, r10, #0x1
	subs r0, r11, r10
	bne _02093674
	cmp r3, r1
	blo _02093674
	cmp r3, r1
	bne _0209366C
	ldr r0, [r7, #-0x8]
	cmp r12, r0
	bls _02093674
_0209366C:
	sub r6, r6, #0x1
	b _020935C4
_02093674:
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x1c]
	ldr r0, [r0, #0x0]
	ldr r1, [r1, #0x0]
	ldr r2, [sp, #0x28]
	mov r3, r6
	bl FUN_0209470C
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x28]
	ldr r3, [r1, #0x0]
	ldr r1, [sp, #0x28]
	str r0, [r3, r2, lsl #0x2]
	add r1, r1, #0x1
	cmp r1, #0x0
	ble _020936D4
	ldr r0, [sp, #0x14]
	ldr r2, [r0, #0x0]
_020936B8:
	sub r0, r1, #0x1
	ldr r0, [r2, r0, lsl #0x2]
	cmp r0, #0x0
	bne _020936D4
	sub r1, r1, #0x1
	cmp r1, #0x0
	bgt _020936B8
_020936D4:
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x14]
	str r1, [r0, #0x4]
	add r0, sp, #0x38
	mov r1, r0
	ldr r5, [sp, #0x3c]
	bl FUN_02093A0C
	ldr r0, [sp, #0x18]
	ldr r1, [r0, #0x4]
	ldr r0, [sp, #0x3c]
	add r0, r1, r0
	sub r1, r0, r5
	ldr r0, [sp, #0x18]
	str r1, [r0, #0x4]
	ldr r0, [sp, #0x44]
	cmp r0, #0x0
	beq _0209374C
	add r0, sp, #0x38
	ldr r2, [sp, #0x1c]
	mov r1, r0
	sub r6, r6, #0x1
	ldr r5, [sp, #0x3c]
	bl FUN_02093DD0
	ldr r0, [sp, #0x18]
	ldr r1, [r0, #0x4]
	ldr r0, [sp, #0x3c]
	sub r0, r0, r5
	add r1, r1, r0
	ldr r0, [sp, #0x18]
	str r1, [r0, #0x4]
_0209374C:
	ldr r0, [sp, #0x20]
	sub r7, r7, #0x4
	str r6, [r0], #-0x4
	str r0, [sp, #0x20]
	ldr r0, [sp, #0xc]
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	sub r1, r0, #0x1
	ldr r0, [sp, #0xc]
	cmp r0, r1
	blt _02093580
_0209377C:
	ldr r0, [sp, #0x18]
	bl FUN_02095040
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _020937C4
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0x4]
	ldr r1, [sp, #0x18]
	add r2, r2, #0x20
	ldr r4, [r3, #0xc]
	bl FUN_02094134
	cmp r0, #0x0
	addeq sp, sp, #0x4c
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r0, [sp, #0x0]
	str r4, [r0, #0xc]
_020937C4:
	add sp, sp, #0x4c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020937D4:
	mov r0, #0x0
	add sp, sp, #0x4c
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020937E4: .word 0x0000FFFF

	arm_func_start FUN_020937E8
FUN_020937E8: ; 0x020937E8
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r5, [sp, #0x20]
	mov r7, r2
	mov r9, r0
	mov r8, r1
	mov r6, r3
	cmp r7, r5
	bge _02093824
	mov r1, r7
	mov r0, r8
	mov r7, r5
	mov r8, r6
	mov r5, r1
	mov r6, r0
_02093824:
	ldr r3, [r6, #0x0]
	mov r0, r9
	mov r1, r8
	mov r2, r7
	add r4, r9, r7, lsl #0x2
	bl FUN_0209470C
	str r0, [r9, r7, lsl #0x2]
_02093840:
	sub r0, r5, #0x1
	cmp r0, #0x0
	addle sp, sp, #0x4
	ldmleia sp!, {r4-r9,lr}
	bxle lr
	ldr r3, [r6, #0x4]
	mov r1, r8
	mov r2, r7
	add r0, r9, #0x4
	bl FUN_020948AC
	sub r1, r5, #0x2
	cmp r1, #0x0
	addle sp, sp, #0x4
	str r0, [r4, #0x4]
	ldmleia sp!, {r4-r9,lr}
	bxle lr
	ldr r3, [r6, #0x8]
	mov r1, r8
	mov r2, r7
	add r0, r9, #0x8
	bl FUN_020948AC
	sub r1, r5, #0x3
	cmp r1, #0x0
	addle sp, sp, #0x4
	str r0, [r4, #0x8]
	ldmleia sp!, {r4-r9,lr}
	bxle lr
	ldr r3, [r6, #0xc]
	mov r1, r8
	mov r2, r7
	add r0, r9, #0xc
	bl FUN_020948AC
	sub r5, r5, #0x4
	cmp r5, #0x0
	addle sp, sp, #0x4
	str r0, [r4, #0xc]
	ldmleia sp!, {r4-r9,lr}
	bxle lr
	ldr r3, [r6, #0x10]
	mov r1, r8
	mov r2, r7
	add r0, r9, #0x10
	bl FUN_020948AC
	str r0, [r4, #0x10]
	add r4, r4, #0x10
	add r9, r9, #0x10
	add r6, r6, #0x10
	b _02093840
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_0209390C
FUN_0209390C:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r9, r1
	ldr r6, [r9, #0x4]
	mov r8, r2
	mov r10, r0
	cmp r6, #0x0
	ldr r5, [r8, #0x4]
	beq _02093938
	cmp r5, #0x0
	bne _02093954
_02093938:
	mov r0, r10
	mov r1, #0x0
	bl FUN_02094D7C
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_02093954:
	ldr r1, [r9, #0xc]
	ldr r0, [r8, #0xc]
	cmp r10, r9
	add r7, r6, r5
	eor r11, r1, r0
	beq _02093974
	cmp r10, r8
	bne _0209398C
_02093974:
	ldr r0, [r3, #0x0]
	add r2, r3, #0x4
	add r1, r0, #0x1
	mov r0, #0x14
	mla r4, r1, r0, r2
	b _02093990
_0209398C:
	mov r4, r10
_02093990:
	ldr r0, [r4, #0x8]
	cmp r7, r0
	movle r0, r4
	ble _020939AC
	mov r0, r4
	mov r1, r7
	bl FUN_02094EBC
_020939AC:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	str r7, [r4, #0x4]
	str r5, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r1, [r9, #0x0]
	ldr r3, [r8, #0x0]
	mov r2, r6
	bl FUN_020937E8
	mov r0, r4
	str r11, [r10, #0xc]
	bl FUN_02095040
	cmp r10, r4
	beq _020939FC
	mov r0, r10
	mov r1, r4
	bl FUN_02094E24
_020939FC:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_02093A0C
FUN_02093A0C: ; 0x02093A0C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	ldr r1, [r6, #0xc]
	mov r3, #0x0
	mov r7, r0
	mov r5, r2
	mov r4, r3
	cmp r1, #0x0
	beq _02093A54
	ldr r0, [r5, #0xc]
	cmp r0, #0x0
	movne r0, r6
	moveq r3, #0x1
	movne r6, r5
	movne r5, r0
	moveq r4, r3
	b _02093A60
_02093A54:
	ldr r0, [r5, #0xc]
	cmp r0, #0x0
	movne r3, #0x1
_02093A60:
	cmp r3, #0x0
	beq _02093A94
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl FUN_02093CB4
	cmp r0, #0x0
	moveq r0, #0x0
	add sp, sp, #0x4
	strne r4, [r7, #0xc]
	movne r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_02093A94:
	ldr r0, [r5, #0x4]
	ldr r1, [r6, #0x4]
	cmp r1, r0
	movle r1, r0
	ldr r0, [r7, #0x8]
	cmp r1, r0
	movle r0, r7
	ble _02093ABC
	mov r0, r7
	bl FUN_02094EBC
_02093ABC:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r6
	mov r1, r5
	bl FUN_02094B98
	cmp r0, #0x0
	bge _02093B14
	mov r0, r7
	mov r1, r5
	mov r2, r6
	bl FUN_02093B50
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, #0x1
	str r0, [r7, #0xc]
	b _02093B40
_02093B14:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl FUN_02093B50
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, #0x0
	str r0, [r7, #0xc]
_02093B40:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_02093B50
FUN_02093B50:
	stmdb sp!, {r4-r10,lr}
	mov r8, r1
	mov r7, r2
	ldr r5, [r7, #0x4]
	ldr r6, [r8, #0x4]
	mov r4, r0
	cmp r6, r5
	movlt r0, #0x0
	ldmltia sp!, {r4-r10,lr}
	bxlt lr
	ldr r1, [r4, #0x8]
	cmp r6, r1
	ble _02093B8C
	mov r1, r6
	bl FUN_02094EBC
_02093B8C:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r10,lr}
	bxeq lr
	mov r3, #0x0
	mov r0, r3
	cmp r5, #0x0
	ldr r2, [r8, #0x0]
	ldr r9, [r7, #0x0]
	ldr r1, [r4, #0x0]
	ble _02093C0C
	mov r12, r3
	mov r7, r3
	mov lr, #0x1
_02093BC4:
	cmp r3, #0x0
	ldr r10, [r2], #0x4
	ldr r8, [r9], #0x4
	beq _02093BEC
	cmp r10, r8
	movls r3, lr
	sub r8, r10, r8
	movhi r3, r12
	sub r10, r8, #0x1
	b _02093BFC
_02093BEC:
	cmp r10, r8
	movcc r3, lr
	movcs r3, r7
	sub r10, r10, r8
_02093BFC:
	add r0, r0, #0x1
	cmp r0, r5
	str r10, [r1], #0x4
	blt _02093BC4
_02093C0C:
	cmp r3, #0x0
	beq _02093C3C
	cmp r0, r6
	bge _02093C3C
_02093C1C:
	ldr r5, [r2], #0x4
	add r0, r0, #0x1
	sub r3, r5, #0x1
	cmp r5, r3
	str r3, [r1], #0x4
	bhi _02093C3C
	cmp r0, r6
	blt _02093C1C
_02093C3C:
	cmp r1, r2
	beq _02093C9C
_02093C44:
	cmp r0, r6
	bge _02093C9C
	ldr r5, [r2, #0x0]
	add r3, r0, #0x1
	str r5, [r1, #0x0]
	cmp r3, r6
	bge _02093C9C
	ldr r5, [r2, #0x4]
	add r3, r0, #0x2
	str r5, [r1, #0x4]
	cmp r3, r6
	bge _02093C9C
	ldr r5, [r2, #0x8]
	add r3, r0, #0x3
	str r5, [r1, #0x8]
	cmp r3, r6
	ldrlt r3, [r2, #0xc]
	add r0, r0, #0x4
	strlt r3, [r1, #0xc]
	addlt r2, r2, #0x10
	addlt r1, r1, #0x10
	blt _02093C44
_02093C9C:
	mov r0, r4
	str r6, [r4, #0x4]
	bl FUN_02095040
	mov r0, #0x1
	ldmia sp!, {r4-r10,lr}
	bx lr

	arm_func_start FUN_02093CB4
FUN_02093CB4:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r8, r2
	ldr r2, [r4, #0x4]
	ldr r1, [r8, #0x4]
	mov r9, r0
	cmp r2, r1
	movlt r0, r4
	movlt r4, r8
	movlt r8, r0
	ldr r6, [r4, #0x4]
	ldr r0, [r9, #0x8]
	add r1, r6, #0x1
	cmp r1, r0
	ldr r7, [r8, #0x4]
	movle r0, r9
	ble _02093D04
	mov r0, r9
	bl FUN_02094EBC
_02093D04:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	str r6, [r9, #0x4]
	ldr r5, [r4, #0x0]
	ldr r4, [r9, #0x0]
	ldr r2, [r8, #0x0]
	mov r0, r4
	mov r1, r5
	mov r3, r7
	bl FUN_02094468
	cmp r0, #0x0
	add r4, r4, r7, lsl #0x2
	add r5, r5, r7, lsl #0x2
	beq _02093D9C
	cmp r7, r6
	bge _02093D7C
_02093D50:
	ldr r2, [r5], #0x4
	mov r3, r4
	add r1, r2, #0x1
	str r1, [r4], #0x4
	ldr r1, [r3, #0x0]
	add r7, r7, #0x1
	cmp r1, r2
	movcs r0, #0x0
	bhs _02093D7C
	cmp r7, r6
	blt _02093D50
_02093D7C:
	cmp r7, r6
	blt _02093D9C
	cmp r0, #0x0
	movne r0, #0x1
	strne r0, [r4], #0x4
	ldrne r0, [r9, #0x4]
	addne r0, r0, #0x1
	strne r0, [r9, #0x4]
_02093D9C:
	cmp r4, r5
	beq _02093DC0
	cmp r7, r6
	bge _02093DC0
_02093DAC:
	ldr r0, [r5], #0x4
	add r7, r7, #0x1
	cmp r7, r6
	str r0, [r4], #0x4
	blt _02093DAC
_02093DC0:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_02093DD0
FUN_02093DD0: ; 0x02093DD0
	stmdb sp!, {r4-r6,lr}
	mov r5, r1
	mov r4, r2
	ldr r2, [r5, #0xc]
	ldr r1, [r4, #0xc]
	mov r6, r0
	eors r0, r2, r1
	beq _02093E74
	cmp r2, #0x0
	movne r0, r5
	movne r5, r4
	movne r4, r0
	mov r0, r5
	mov r1, r4
	bl FUN_02094B98
	cmp r0, #0x0
	bge _02093E40
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl FUN_02093B50
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r0, #0x1
	str r0, [r6, #0xc]
	b _02093E68
_02093E40:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_02093B50
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r0, #0x0
	str r0, [r6, #0xc]
_02093E68:
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_02093E74:
	cmp r2, #0x0
	movne r0, #0x1
	strne r0, [r6, #0xc]
	moveq r0, #0x0
	streq r0, [r6, #0xc]
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_02093CB4
	cmp r0, #0x0
	moveq r0, #0x0
	movne r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_02093EAC
FUN_02093EAC: ; 0x02093EAC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r4, r1
	mov r5, r0
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r2, [r5, #0xc]
	cmp r2, #0x0
	beq _02093EF8
	mov r2, #0x0
	str r2, [r5, #0xc]
	bl FUN_0209400C
	mov r1, #0x1
	add sp, sp, #0x4
	str r1, [r5, #0xc]
	ldmia sp!, {r4-r5,lr}
	bx lr
_02093EF8:
	ldr r1, [r5, #0x4]
	cmp r1, #0x1
	bgt _02093F9C
	cmp r1, #0x0
	bne _02093F54
	ldr r1, [r5, #0x8]
	cmp r1, #0x1
	bge _02093F20
	mov r1, #0x1
	bl FUN_02094EBC
_02093F20:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r1, [r5, #0x0]
	mov r0, #0x1
	str r4, [r1, #0x0]
	str r0, [r5, #0xc]
	add sp, sp, #0x4
	str r0, [r5, #0x4]
	ldmia sp!, {r4-r5,lr}
	bx lr
_02093F54:
	ldr r2, [r5, #0x0]
	ldr r1, [r2, #0x0]
	cmp r1, r4
	moveq r0, #0x0
	streq r0, [r5, #0x4]
	beq _02093F8C
	cmp r1, r4
	subhi r0, r1, r4
	strhi r0, [r2, #0x0]
	movls r0, #0x1
	strls r0, [r5, #0xc]
	ldrls r0, [r5, #0x0]
	subls r1, r4, r1
	strls r1, [r0, #0x0]
_02093F8C:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r5,lr}
	bx lr
_02093F9C:
	mov r0, #0x0
	mov r1, #0x1
_02093FA4:
	ldr r12, [r5, #0x0]
	mov r3, r0, lsl #0x2
	ldr r2, [r12, r0, lsl #0x2]
	cmp r2, r4
	ldrcs r1, [r12, r3]
	subcs r1, r1, r4
	strcs r1, [r12, r3]
	bhs _02093FDC
	ldr r2, [r12, r3]
	add r0, r0, #0x1
	sub r2, r2, r4
	mov r4, r1
	str r2, [r12, r3]
	b _02093FA4
_02093FDC:
	ldr r1, [r5, #0x0]
	ldr r1, [r1, r3]
	cmp r1, #0x0
	bne _02093FFC
	ldr r1, [r5, #0x4]
	sub r1, r1, #0x1
	cmp r0, r1
	streq r1, [r5, #0x4]
_02093FFC:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209400C
FUN_0209400C:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r4, r1
	mov r5, r0
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r2, [r5, #0xc]
	cmp r2, #0x0
	beq _020940B4
	ldr r2, [r5, #0x4]
	cmp r2, #0x1
	ble _02094064
	mov r2, #0x0
	str r2, [r5, #0xc]
	bl FUN_02093EAC
	mov r1, #0x1
	add sp, sp, #0x4
	str r1, [r5, #0xc]
	ldmia sp!, {r4-r5,lr}
	bx lr
_02094064:
	ldr r2, [r5, #0x0]
	ldr r1, [r2, #0x0]
	cmp r1, r4
	subhi r0, r1, r4
	strhi r0, [r2, #0x0]
	bhi _020940A4
	cmp r1, r4
	movcs r0, #0x0
	strcs r0, [r5, #0xc]
	strcs r0, [r5, #0x4]
	bhs _020940A4
	mov r0, #0x0
	str r0, [r5, #0xc]
	ldr r0, [r5, #0x0]
	sub r1, r4, r1
	str r1, [r0, #0x0]
_020940A4:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r5,lr}
	bx lr
_020940B4:
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x8]
	add r1, r1, #0x1
	cmp r1, r2
	ble _020940CC
	bl FUN_02094EBC
_020940CC:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r1, [r5, #0x0]
	ldr r0, [r5, #0x4]
	mov r3, #0x0
	str r3, [r1, r0, lsl #0x2]
	mov r0, #0x1
_020940F4:
	ldr r2, [r5, #0x0]
	ldr r1, [r2, r3, lsl #0x2]
	add r1, r4, r1
	cmp r4, r1
	str r1, [r2, r3, lsl #0x2]
	movhi r4, r0
	addhi r3, r3, #0x1
	bhi _020940F4
	ldr r0, [r5, #0x4]
	cmp r3, r0
	addge r0, r0, #0x1
	strge r0, [r5, #0x4]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02094134
FUN_02094134:
	stmdb sp!, {r4-r8,lr}
	mov r7, r1
	mov r1, r2, asr #0x4
	mov r3, r2, lsr #0x1f
	add r1, r2, r1, lsr #0x1b
	rsb r2, r3, r2, lsl #0x1b
	add r4, r3, r2, ror #0x1b
	ldr r2, [r7, #0x4]
	mov r6, r1, asr #0x5
	mov r8, r0
	cmp r6, r2
	rsb r5, r4, #0x20
	ble _0209417C
	mov r1, #0x0
	bl FUN_02094D7C
	mov r0, #0x1
	ldmia sp!, {r4-r8,lr}
	bx lr
_0209417C:
	cmp r8, r7
	beq _020941B4
	sub r1, r2, r6
	ldr r2, [r8, #0x8]
	add r1, r1, #0x2
	cmp r1, r2
	ble _0209419C
	bl FUN_02094EBC
_0209419C:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r0, [r7, #0xc]
	str r0, [r8, #0xc]
_020941B4:
	ldr r0, [r7, #0x0]
	ldr r1, [r7, #0x4]
	add r2, r0, r6, lsl #0x2
	ldr r0, [r8, #0x0]
	sub r7, r1, r6
	mov r6, r2
	str r7, [r8, #0x4]
	cmp r4, #0x0
	bne _020941FC
	add r2, r7, #0x1
	cmp r2, #0x0
	ble _0209423C
_020941E4:
	ldr r1, [r6], #0x4
	sub r2, r2, #0x1
	cmp r2, #0x0
	str r1, [r0], #0x4
	bgt _020941E4
	b _0209423C
_020941FC:
	cmp r7, #0x1
	add r6, r2, #0x4
	ldr r3, [r2, #0x0]
	mov r2, #0x1
	ble _0209422C
_02094210:
	mov r1, r3, lsr r4
	ldr r3, [r6], #0x4
	add r2, r2, #0x1
	orr r1, r1, r3, lsl r5
	cmp r2, r7
	str r1, [r0], #0x4
	blt _02094210
_0209422C:
	mov r1, r3, lsr r4
	str r1, [r0, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
_0209423C:
	mov r0, r8
	bl FUN_02095040
	mov r0, #0x1
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_02094250
FUN_02094250:
	stmdb sp!, {r4-r10,lr}
	mov r4, r1
	mov r7, r2
	mov r1, r7, asr #0x4
	mov r5, r0
	add r2, r7, r1, lsr #0x1b
	ldr r1, [r4, #0x4]
	ldr r3, [r5, #0x8]
	add r1, r1, r2, asr #0x5
	add r1, r1, #0x1
	cmp r1, r3
	mov r6, r2, asr #0x5
	ble _02094288
	bl FUN_02094EBC
_02094288:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r10,lr}
	bxeq lr
	ldr r0, [r4, #0xc]
	mov r1, r7, lsr #0x1f
	str r0, [r5, #0xc]
	ldr r3, [r4, #0x4]
	rsb r0, r1, r7, lsl #0x1b
	adds r12, r1, r0, ror #0x1b
	ldr r2, [r4, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r3, r6
	mov r3, #0x0
	str r3, [r0, r1, lsl #0x2]
	rsb r3, r12, #0x20
	bne _020942F0
	ldr r1, [r4, #0x4]
	subs r7, r1, #0x1
	bmi _02094324
_020942D8:
	ldr r3, [r2, r7, lsl #0x2]
	add r1, r6, r7
	str r3, [r0, r1, lsl #0x2]
	subs r7, r7, #0x1
	bpl _020942D8
	b _02094324
_020942F0:
	ldr r1, [r4, #0x4]
	subs r1, r1, #0x1
	bmi _02094324
_020942FC:
	add r9, r6, r1
	add r8, r9, #0x1
	ldr r10, [r2, r1, lsl #0x2]
	ldr lr, [r0, r8, lsl #0x2]
	mov r7, r10, lsl r12
	orr lr, lr, r10, lsr r3
	str lr, [r0, r8, lsl #0x2]
	str r7, [r0, r9, lsl #0x2]
	subs r1, r1, #0x1
	bpl _020942FC
_02094324:
	mov r2, r6, lsl #0x2
	mov r1, #0x0
	bl MI_CpuFill8
	ldr r1, [r4, #0x4]
	mov r0, r5
	add r1, r1, r6
	add r1, r1, #0x1
	str r1, [r5, #0x4]
	bl FUN_02095040
	mov r0, #0x1
	ldmia sp!, {r4-r10,lr}
	bx lr

	arm_func_start FUN_02094354
FUN_02094354: ; 0x02094354
	stmdb sp!, {r4-r10,lr}
	cmp r3, #0x0
	movle r0, #0x0
	ldmleia sp!, {r4-r10,lr}
	bxle lr
	mov r6, #0x0
	mov r4, r6
	mov lr, r6
	mov r12, r6
	mov r7, r6
	mov r5, #0x1
_02094380:
	ldr r10, [r1, #0x0]
	ldr r9, [r2, #0x0]
	sub r8, r10, r9
	sub r8, r8, r6
	str r8, [r0, #0x0]
	cmp r10, r9
	beq _020943A8
	cmp r10, r9
	movcc r6, r5
	movcs r6, r4
_020943A8:
	sub r8, r3, #0x1
	cmp r8, #0x0
	ble _0209445C
	ldr r10, [r1, #0x4]
	ldr r9, [r2, #0x4]
	sub r8, r10, r9
	sub r8, r8, r6
	str r8, [r0, #0x4]
	cmp r10, r9
	beq _020943DC
	cmp r10, r9
	movcc r6, r5
	movcs r6, lr
_020943DC:
	sub r8, r3, #0x2
	cmp r8, #0x0
	ble _0209445C
	ldr r10, [r1, #0x8]
	ldr r9, [r2, #0x8]
	sub r8, r10, r9
	sub r8, r8, r6
	str r8, [r0, #0x8]
	cmp r10, r9
	beq _02094410
	cmp r10, r9
	movcc r6, r5
	movcs r6, r12
_02094410:
	sub r8, r3, #0x3
	cmp r8, #0x0
	ble _0209445C
	ldr r10, [r1, #0xc]
	ldr r9, [r2, #0xc]
	sub r8, r10, r9
	sub r8, r8, r6
	str r8, [r0, #0xc]
	cmp r10, r9
	beq _02094444
	cmp r10, r9
	movcc r6, r5
	movcs r6, r7
_02094444:
	sub r3, r3, #0x4
	cmp r3, #0x0
	addgt r1, r1, #0x10
	addgt r2, r2, #0x10
	addgt r0, r0, #0x10
	bgt _02094380
_0209445C:
	mov r0, r6
	ldmia sp!, {r4-r10,lr}
	bx lr

	arm_func_start FUN_02094468
FUN_02094468:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	cmp r3, #0x0
	addle sp, sp, #0xc
	movle r0, #0x0
	ldmleia sp!, {r4-r11,lr}
	bxle lr
	mov r12, #0x0
	mov r7, r12
	mov r6, r12
	mov r5, r12
	mov r4, r12
	mov lr, r12
	mov r11, r12
	str r12, [sp, #0x0]
	str r12, [sp, #0x4]
	mov r8, #0x1
_020944AC:
	ldr r9, [r1, #0x0]
	add r10, r9, r12
	ldr r9, [r2, #0x0]
	cmp r10, r12
	movcc r12, r8
	add r9, r10, r9
	movcs r12, r7
	cmp r9, r10
	movcc r10, r8
	movcs r10, r6
	str r9, [r0, #0x0]
	sub r9, r3, #0x1
	add r12, r12, r10
	cmp r9, #0x0
	ble _020945A8
	ldr r9, [r1, #0x4]
	ldr r10, [r2, #0x4]
	add r9, r9, r12
	cmp r9, r12
	movcc r12, r8
	add r10, r9, r10
	movcs r12, r5
	cmp r10, r9
	movcc r9, r8
	movcs r9, r4
	add r12, r12, r9
	sub r9, r3, #0x2
	str r10, [r0, #0x4]
	cmp r9, #0x0
	ble _020945A8
	ldr r9, [r1, #0x8]
	ldr r10, [r2, #0x8]
	add r9, r9, r12
	cmp r9, r12
	movcc r12, r8
	add r10, r9, r10
	movcs r12, lr
	cmp r10, r9
	movcc r9, r8
	movcs r9, r11
	add r12, r12, r9
	sub r9, r3, #0x3
	str r10, [r0, #0x8]
	cmp r9, #0x0
	ble _020945A8
	ldr r9, [r1, #0xc]
	ldr r10, [r2, #0xc]
	add r9, r9, r12
	cmp r9, r12
	movcc r12, r8
	add r10, r9, r10
	ldrcs r12, [sp, #0x0]
	cmp r10, r9
	movcc r9, r8
	ldrcs r9, [sp, #0x4]
	sub r3, r3, #0x4
	cmp r3, #0x0
	str r10, [r0, #0xc]
	add r12, r12, r9
	addgt r1, r1, #0x10
	addgt r2, r2, #0x10
	addgt r0, r0, #0x10
	bgt _020944AC
_020945A8:
	mov r0, r12
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_020945B8
FUN_020945B8: ; 0x020945B8
	stmdb sp!, {r4-r8,lr}
	cmp r2, #0x0
	ldmleia sp!, {r4-r8,lr}
	bxle lr
	mov r3, #0x8000
	ldr lr, _02094708 ; =0x0000FFFF
	rsb r12, r3, #0x0
_020945D4:
	ldr r5, [r1, #0x0]
	mov r3, #0x8000
	and r4, r5, lr
	and r7, lr, r5, lsr #0x10
	mul r6, r4, r7
	mul r5, r4, r4
	and r4, r6, lr
	add r8, r5, r4, lsl #0x11
	rsb r3, r3, #0x0
	mul r5, r7, r7
	and r3, r6, r3
	add r3, r5, r3, lsr #0xf
	cmp r8, r4, lsl #0x11
	addcc r3, r3, #0x1
	str r8, [r0, #0x0]
	str r3, [r0, #0x4]
	subs r3, r2, #0x1
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r4, [r1, #0x4]
	and r7, lr, r4, lsr #0x10
	and r3, r4, lr
	mul r6, r3, r7
	mul r4, r3, r3
	and r3, r6, lr
	add r8, r4, r3, lsl #0x11
	mul r5, r7, r7
	and r4, r6, r12
	cmp r8, r3, lsl #0x11
	add r3, r5, r4, lsr #0xf
	addcc r3, r3, #0x1
	str r8, [r0, #0x8]
	str r3, [r0, #0xc]
	subs r3, r2, #0x2
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r5, [r1, #0x8]
	mov r3, #0x8000
	and r4, r5, lr
	and r7, lr, r5, lsr #0x10
	mul r6, r4, r7
	mul r5, r4, r4
	and r4, r6, lr
	add r8, r5, r4, lsl #0x11
	rsb r3, r3, #0x0
	mul r5, r7, r7
	and r3, r6, r3
	add r3, r5, r3, lsr #0xf
	cmp r8, r4, lsl #0x11
	addcc r3, r3, #0x1
	str r8, [r0, #0x10]
	str r3, [r0, #0x14]
	subs r3, r2, #0x3
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r5, [r1, #0xc]
	mov r3, #0x8000
	and r4, r5, lr
	and r7, lr, r5, lsr #0x10
	mul r6, r4, r7
	mul r5, r4, r4
	and r4, r6, lr
	add r8, r5, r4, lsl #0x11
	rsb r3, r3, #0x0
	mul r5, r7, r7
	and r3, r6, r3
	add r3, r5, r3, lsr #0xf
	cmp r8, r4, lsl #0x11
	addcc r3, r3, #0x1
	str r8, [r0, #0x18]
	subs r2, r2, #0x4
	str r3, [r0, #0x1c]
	addne r1, r1, #0x10
	addne r0, r0, #0x20
	bne _020945D4
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_02094708: .word 0x0000FFFF

	arm_func_start FUN_0209470C
FUN_0209470C: ; 0x0209470C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	mov r4, #0x0
	addle sp, sp, #0x4
	movle r0, r4
	ldmleia sp!, {r4-r9,lr}
	bxle lr
	ldr r5, _020948A8 ; =0x0000FFFF
	and lr, r3, r5
	and r12, r5, r3, lsr #0x10
_02094738:
	ldr r3, [r1, #0x0]
	and r7, r5, r3, lsr #0x10
	mul r6, lr, r7
	and r3, r3, r5
	mla r9, r12, r3, r6
	mul r8, r3, lr
	mul r3, r7, r12
	cmp r9, r6
	and r6, r9, r5
	addcc r3, r3, #0x10000
	and r7, r5, r9, lsr #0x10
	add r8, r8, r6, lsl #0x10
	cmp r8, r6, lsl #0x10
	add r3, r3, r7
	add r6, r8, r4
	addcc r3, r3, #0x1
	cmp r6, r4
	addcc r3, r3, #0x1
	str r6, [r0, #0x0]
	mov r4, r3
	subs r6, r2, #0x1
	beq _02094898
	ldr r4, [r1, #0x4]
	and r7, r5, r4, lsr #0x10
	mul r6, lr, r7
	and r4, r4, r5
	mla r9, r12, r4, r6
	mul r8, r4, lr
	mul r4, r7, r12
	cmp r9, r6
	and r6, r9, r5
	addcc r4, r4, #0x10000
	and r7, r5, r9, lsr #0x10
	add r8, r8, r6, lsl #0x10
	cmp r8, r6, lsl #0x10
	add r4, r4, r7
	add r6, r8, r3
	addcc r4, r4, #0x1
	cmp r6, r3
	addcc r4, r4, #0x1
	str r6, [r0, #0x4]
	subs r3, r2, #0x2
	beq _02094898
	ldr r3, [r1, #0x8]
	and r7, r5, r3, lsr #0x10
	mul r6, lr, r7
	and r3, r3, r5
	mla r9, r12, r3, r6
	mul r8, r3, lr
	mul r3, r7, r12
	cmp r9, r6
	and r6, r9, r5
	addcc r3, r3, #0x10000
	and r7, r5, r9, lsr #0x10
	add r8, r8, r6, lsl #0x10
	cmp r8, r6, lsl #0x10
	add r3, r3, r7
	add r6, r8, r4
	addcc r3, r3, #0x1
	cmp r6, r4
	addcc r3, r3, #0x1
	str r6, [r0, #0x8]
	mov r4, r3
	subs r6, r2, #0x3
	beq _02094898
	ldr r4, [r1, #0xc]
	and r7, r5, r4, lsr #0x10
	mul r6, lr, r7
	and r4, r4, r5
	mla r9, r12, r4, r6
	mul r8, r4, lr
	mul r4, r7, r12
	cmp r9, r6
	and r6, r9, r5
	addcc r4, r4, #0x10000
	and r7, r5, r9, lsr #0x10
	add r8, r8, r6, lsl #0x10
	cmp r8, r6, lsl #0x10
	add r4, r4, r7
	add r6, r8, r3
	addcc r4, r4, #0x1
	cmp r6, r3
	addcc r4, r4, #0x1
	subs r2, r2, #0x4
	str r6, [r0, #0xc]
	addne r1, r1, #0x10
	addne r0, r0, #0x10
	bne _02094738
_02094898:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020948A8: .word 0x0000FFFF

	arm_func_start FUN_020948AC
FUN_020948AC: ; 0x020948AC
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	mov r12, #0x0
	addle sp, sp, #0x4
	movle r0, r12
	ldmleia sp!, {r4-r9,lr}
	bxle lr
	ldr r5, _02094A88 ; =0x0000FFFF
	and r4, r3, r5
	and lr, r5, r3, lsr #0x10
_020948D8:
	ldr r3, [r1, #0x0]
	and r7, r5, r3, lsr #0x10
	mul r6, r4, r7
	and r3, r3, r5
	mla r9, lr, r3, r6
	mul r8, r3, r4
	mul r3, r7, lr
	cmp r9, r6
	and r6, r9, r5
	addcc r3, r3, #0x10000
	and r7, r5, r9, lsr #0x10
	add r8, r8, r6, lsl #0x10
	cmp r8, r6, lsl #0x10
	add r3, r3, r7
	ldr r6, [r0, #0x0]
	addcc r3, r3, #0x1
	add r7, r8, r12
	cmp r7, r12
	add r7, r7, r6
	addcc r3, r3, #0x1
	cmp r7, r6
	addcc r3, r3, #0x1
	mov r12, r3
	str r7, [r0, #0x0]
	subs r6, r2, #0x1
	beq _02094A78
	ldr r12, [r1, #0x4]
	and r7, r5, r12, lsr #0x10
	mul r6, r4, r7
	and r12, r12, r5
	mla r9, lr, r12, r6
	mul r8, r12, r4
	mul r12, r7, lr
	cmp r9, r6
	and r6, r9, r5
	addcc r12, r12, #0x10000
	and r7, r5, r9, lsr #0x10
	add r8, r8, r6, lsl #0x10
	cmp r8, r6, lsl #0x10
	add r12, r12, r7
	add r6, r8, r3
	addcc r12, r12, #0x1
	cmp r6, r3
	ldr r3, [r0, #0x4]
	addcc r12, r12, #0x1
	add r6, r6, r3
	cmp r6, r3
	addcc r12, r12, #0x1
	str r6, [r0, #0x4]
	subs r3, r2, #0x2
	beq _02094A78
	ldr r3, [r1, #0x8]
	and r7, r5, r3, lsr #0x10
	mul r6, r4, r7
	and r3, r3, r5
	mla r9, lr, r3, r6
	mul r8, r3, r4
	mul r3, r7, lr
	cmp r9, r6
	and r6, r9, r5
	addcc r3, r3, #0x10000
	and r7, r5, r9, lsr #0x10
	add r8, r8, r6, lsl #0x10
	cmp r8, r6, lsl #0x10
	add r3, r3, r7
	ldr r6, [r0, #0x8]
	addcc r3, r3, #0x1
	add r7, r8, r12
	cmp r7, r12
	add r7, r7, r6
	addcc r3, r3, #0x1
	cmp r7, r6
	addcc r3, r3, #0x1
	mov r12, r3
	str r7, [r0, #0x8]
	subs r6, r2, #0x3
	beq _02094A78
	ldr r12, [r1, #0xc]
	and r7, r5, r12, lsr #0x10
	mul r6, r4, r7
	and r12, r12, r5
	mla r9, lr, r12, r6
	mul r8, r12, r4
	mul r12, r7, lr
	cmp r9, r6
	and r6, r9, r5
	addcc r12, r12, #0x10000
	and r7, r5, r9, lsr #0x10
	add r8, r8, r6, lsl #0x10
	cmp r8, r6, lsl #0x10
	add r12, r12, r7
	add r6, r8, r3
	addcc r12, r12, #0x1
	cmp r6, r3
	ldr r3, [r0, #0xc]
	addcc r12, r12, #0x1
	add r6, r6, r3
	cmp r6, r3
	addcc r12, r12, #0x1
	subs r2, r2, #0x4
	str r6, [r0, #0xc]
	addne r1, r1, #0x10
	addne r0, r0, #0x10
	bne _020948D8
_02094A78:
	mov r0, r12
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_02094A88: .word 0x0000FFFF

	arm_func_start FUN_02094A8C
FUN_02094A8C:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r1, #0x0
	addlt sp, sp, #0x4
	movlt r0, #0x0
	ldmltia sp!, {lr}
	bxlt lr
	mov r2, r1, asr #0x4
	add r2, r1, r2, lsr #0x1b
	mov r3, r1, lsr #0x1f
	ldr r12, [r0, #0x4]
	mov lr, r2, asr #0x5
	cmp r12, lr
	rsb r1, r3, r1, lsl #0x1b
	addle sp, sp, #0x4
	add r2, r3, r1, ror #0x1b
	movle r0, #0x0
	ldmleia sp!, {lr}
	bxle lr
	ldr r1, [r0, #0x0]
	mov r0, #0x1
	mov r2, r0, lsl r2
	ldr r1, [r1, lr, lsl #0x2]
	ands r1, r2, r1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_02094AFC
FUN_02094AFC:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r2, r1, asr #0x4
	add r2, r1, r2, lsr #0x1b
	mov r3, r1, lsr #0x1f
	rsb r1, r3, r1, lsl #0x1b
	ldr r4, [r6, #0x4]
	mov r5, r2, asr #0x5
	cmp r4, r5
	add r4, r3, r1, ror #0x1b
	bgt _02094B7C
	ldr r2, [r6, #0x8]
	add r1, r5, #0x1
	cmp r1, r2
	ble _02094B3C
	bl FUN_02094EBC
_02094B3C:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r3, [r6, #0x4]
	add r2, r5, #0x1
	cmp r3, r2
	bge _02094B74
	mov r1, #0x0
_02094B60:
	ldr r0, [r6, #0x0]
	str r1, [r0, r3, lsl #0x2]
	add r3, r3, #0x1
	cmp r3, r2
	blt _02094B60
_02094B74:
	add r0, r5, #0x1
	str r0, [r6, #0x4]
_02094B7C:
	ldr r2, [r6, #0x0]
	mov r0, #0x1
	ldr r1, [r2, r5, lsl #0x2]
	orr r1, r1, r0, lsl r4
	str r1, [r2, r5, lsl #0x2]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_02094B98
FUN_02094B98:
	ldr r3, [r0, #0x4]
	ldr r2, [r1, #0x4]
	subs r2, r3, r2
	movne r0, r2
	bxne lr
	subs r2, r3, #0x1
	ldr r12, [r0, #0x0]
	ldr r3, [r1, #0x0]
	bmi _02094BE4
_02094BBC:
	ldr r1, [r12, r2, lsl #0x2]
	ldr r0, [r3, r2, lsl #0x2]
	cmp r1, r0
	beq _02094BDC
	cmp r1, r0
	movhi r0, #0x1
	mvnls r0, #0x0
	bx lr
_02094BDC:
	subs r2, r2, #0x1
	bpl _02094BBC
_02094BE4:
	mov r0, #0x0
	bx lr

	arm_func_start FUN_02094BEC
FUN_02094BEC: ; 0x02094BEC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl FUN_02095188
	add r1, r0, #0x7
	mov r0, r1, asr #0x2
	add r0, r1, r0, lsr #0x1d
	mov r0, r0, asr #0x3
	cmp r0, #0x0
	addle sp, sp, #0x4
	sub r12, r0, #0x1
	ldmleia sp!, {r4-r5,lr}
	bxle lr
_02094C24:
	mov r3, r12, lsr #0x1f
	mov r1, r12, asr #0x1
	rsb r2, r3, r12, lsl #0x1e
	add r1, r12, r1, lsr #0x1e
	add r2, r3, r2, ror #0x1e
	ldr r3, [r5, #0x0]
	mov r1, r1, asr #0x2
	ldr r3, [r3, r1, lsl #0x2]
	mov r1, r2, lsl #0x3
	mov r1, r3, lsr r1
	cmp r12, #0x0
	strb r1, [r4], #0x1
	sub r12, r12, #0x1
	bgt _02094C24
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02094C68
FUN_02094C68:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	movs r5, r2
	mov r7, r0
	mov r6, r1
	bne _02094C88
	bl FUN_02094FE0
	mov r5, r0
_02094C88:
	cmp r5, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	cmp r6, #0x0
	mov r4, #0x0
	addeq sp, sp, #0x4
	moveq r0, r5
	streq r4, [r5, #0x4]
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	add r0, r6, #0x2
	mov r2, r0, lsl #0x3
	add r1, r2, #0x1f
	mov r0, r1, asr #0x4
	add r0, r1, r0, lsr #0x1b
	ldr r1, [r5, #0x8]
	mov r0, r0, asr #0x5
	cmp r0, r1
	movle r0, r5
	ble _02094CF8
	mov r0, r2, asr #0x4
	add r0, r2, r0, lsr #0x1b
	mov r1, r0, asr #0x5
	mov r0, r5
	add r1, r1, #0x1
	bl FUN_02094EBC
_02094CF8:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	sub r0, r6, #0x1
	mov r1, r0, lsr #0x2
	add r12, r1, #0x1
	cmp r6, #0x0
	str r12, [r5, #0x4]
	and r3, r0, #0x3
	sub r6, r6, #0x1
	beq _02094D64
	mov r1, #0x0
	mov r0, #0x3
_02094D34:
	ldrb r2, [r7], #0x1
	cmp r3, #0x0
	sub r3, r3, #0x1
	orr r4, r2, r4, lsl #0x8
	ldreq r2, [r5, #0x0]
	subeq r12, r12, #0x1
	streq r4, [r2, r12, lsl #0x2]
	moveq r4, r1
	moveq r3, r0
	cmp r6, #0x0
	sub r6, r6, #0x1
	bne _02094D34
_02094D64:
	mov r0, r5
	bl FUN_02095040
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_02094D7C
FUN_02094D7C:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldr r2, [r4, #0x8]
	mov r5, r1
	cmp r2, #0x1
	bge _02094DA0
	mov r1, #0x2
	bl FUN_02094EBC
_02094DA0:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	mov r0, #0x0
	str r0, [r4, #0xc]
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x0]
	str r5, [r0, #0x0]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	movne r0, #0x1
	strne r0, [r4, #0x4]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02094DEC
FUN_02094DEC: ; 0x02094DEC
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02094E10
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	mov r2, r2, lsl #0x2
	bl MI_CpuFill8
_02094E10:
	mov r0, #0x0
	str r0, [r4, #0x4]
	str r0, [r4, #0xc]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02094E24
FUN_02094E24:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	cmp r5, r4
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r1, [r4, #0x4]
	ldr r2, [r5, #0x8]
	cmp r1, r2
	ble _02094E58
	bl FUN_02094EBC
_02094E58:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r2, [r4, #0x4]
	ldr r0, [r4, #0x0]
	ldr r1, [r5, #0x0]
	mov r2, r2, lsl #0x2
	bl MI_CpuCopy8
	ldr r0, [r4, #0x4]
	str r0, [r5, #0x4]
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	bne _02094EA4
	ldr r1, [r5, #0x0]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x0]
_02094EA4:
	ldr r1, [r4, #0xc]
	mov r0, r5
	str r1, [r5, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02094EBC
FUN_02094EBC:
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	ldr r0, [r5, #0x8]
	mov r4, r1
	cmp r4, r0
	ble _02094F30
	ldr r0, [r5, #0x10]
	ands r0, r0, #0x2
	movne r0, #0x0
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	add r0, r4, #0x1
	mov r0, r0, lsl #0x2
	bl CallCustomAllocator
	movs r6, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _02094F28
	ldr r2, [r5, #0x4]
	mov r1, r6
	mov r2, r2, lsl #0x2
	bl MI_CpuCopy8
	ldr r0, [r5, #0x0]
	bl CallCustomDestructor
_02094F28:
	str r6, [r5, #0x0]
	str r4, [r5, #0x8]
_02094F30:
	mov r0, r5
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_02094F3C
FUN_02094F3C: ; 0x02094F3C
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	add r4, r6, #0x4
	mov r5, #0x0
_02094F4C:
	mov r0, r4
	bl FUN_02095164
	add r5, r5, #0x1
	cmp r5, #0xc
	add r4, r4, #0x14
	blt _02094F4C
	ldr r0, [r6, #0x108]
	ands r0, r0, #0x1
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r0, r6
	bl CallCustomDestructor
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_02094F84
FUN_02094F84: ; 0x02094F84
	stmdb sp!, {r4,lr}
	mov r1, #0x0
	mov r2, #0x110
	mov r4, r0
	bl MI_CpuFill8
	mov r0, #0x0
	str r0, [r4, #0x0]
	str r0, [r4, #0x108]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02094FAC
FUN_02094FAC: ; 0x02094FAC
	stmdb sp!, {r4,lr}
	mov r0, #0x110
	bl CallCustomAllocator
	movs r4, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl FUN_02094F84
	mov r1, #0x1
	mov r0, r4
	str r1, [r4, #0x108]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02094FE0
FUN_02094FE0: ; 0x02094FE0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, #0x14
	bl CallCustomAllocator
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {lr}
	bxeq lr
	mov r1, #0x1
	str r1, [r0, #0x10]
	mov r1, #0x0
	str r1, [r0, #0x4]
	str r1, [r0, #0xc]
	str r1, [r0, #0x8]
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_0209502C
FUN_0209502C:
	ldr ip, _0209503C ; =MI_CpuFill8
	mov r1, #0x0
	mov r2, #0x14
	bx r12
	.balign 4
_0209503C: .word MI_CpuFill8

	arm_func_start FUN_02095040
FUN_02095040:
	ldr r3, [r0, #0x4]
	cmp r3, #0x0
	bxle lr
	ldr r2, [r0, #0x0]
	sub r1, r3, #0x1
	cmp r3, #0x0
	add r3, r2, r1, lsl #0x2
	bxle lr
	add r2, r0, #0x4
_02095064:
	ldr r1, [r3], #-0x4
	cmp r1, #0x0
	bxne lr
	ldr r1, [r2, #0x0]
	sub r1, r1, #0x1
	str r1, [r2, #0x0]
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	bgt _02095064
	bx lr

	arm_func_start FUN_0209508C
FUN_0209508C:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r2, [r5, #0x4]
	mov r4, r1
	cmp r2, r4
	addge sp, sp, #0x4
	ldmgeia sp!, {r4-r5,lr}
	bxge lr
	ldr r2, [r5, #0x8]
	cmp r4, r2
	ble _020950C0
	bl FUN_02094EBC
_020950C0:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r2, [r5, #0x4]
	cmp r2, r4
	addge sp, sp, #0x4
	ldmgeia sp!, {r4-r5,lr}
	bxge lr
	mov r1, #0x0
_020950EC:
	ldr r0, [r5, #0x0]
	str r1, [r0, r2, lsl #0x2]
	add r2, r2, #0x1
	cmp r2, r4
	blt _020950EC
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209510C
FUN_0209510C:
	stmdb sp!, {r4,lr}
	movs r4, r0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02095138
	ldr r1, [r4, #0x10]
	ands r1, r1, #0x2
	bne _02095138
	bl CallCustomDestructor
_02095138:
	ldr r0, [r4, #0x10]
	orr r0, r0, #0x8000
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x10]
	ands r0, r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, r4
	bl CallCustomDestructor
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02095164
FUN_02095164: ; 0x02095164
	stmdb sp!, {r4,lr}
	movs r4, r0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl FUN_02094DEC
	mov r0, r4
	bl FUN_0209510C
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02095188
FUN_02095188: ; 0x02095188
	stmdb sp!, {r4,lr}
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, [r0, #0x0]
	sub r4, r1, #0x1
	ldr r0, [r0, r4, lsl #0x2]
	bl FUN_020951BC
	add r0, r0, r4, lsl #0x5
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020951BC
FUN_020951BC: ; 0x020951BC
	mov r1, #0x10000
	rsb r1, r1, #0x0
	ands r1, r0, r1
	beq _020951DC
	ands r1, r0, #0xff000000
	movne r2, #0x18
	moveq r2, #0x10
	b _020951E8
_020951DC:
	ands r1, r0, #0xff00
	movne r2, #0x8
	moveq r2, #0x0
_020951E8:
	mov r1, r0, lsr r2
	ands r0, r1, #0xf0
	ldreq r0, _02095218 ; =UNK_020FF524
	ldreqsb r0, [r0, r1]
	addeq r0, r0, r2
	bxeq lr
	ldr r0, _02095218 ; =UNK_020FF524
	mov r1, r1, lsr #0x4
	ldrsb r0, [r0, r1]
	add r0, r0, r2
	add r0, r0, #0x4
	bx lr
	.balign 4
_02095218: .word UNK_020FF524

	arm_func_start FUN_0209521C
FUN_0209521C: ; 0x0209521C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r3, #0x0
	strb r3, [r0, #0x0]
	cmp r2, #0x10
	strb r3, [r0, #0x1]
	movhi r2, #0x10
	add r0, r0, #0x4
_0209523C:
	strb r3, [r0, r3]
	add r3, r3, #0x1
	cmp r3, #0x100
	blt _0209523C
	mov r6, #0x0
	mov r7, r6
	mov r4, r6
	mov r3, r6
	and r12, r2, #0xff
_02095260:
	ldrb r5, [r0, r4]
	ldrb lr, [r1, r7]
	add r2, r7, #0x1
	and r7, r2, #0xff
	add r2, r5, lr
	add r2, r6, r2
	and r6, r2, #0xff
	ldrb r2, [r0, r6]
	add lr, r0, r4
	add r4, r4, #0x1
	strb r2, [lr, #0x0]
	cmp r7, r12
	moveq r7, r3
	cmp r4, #0x100
	strb r5, [r0, r6]
	blt _02095260
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_020952AC
FUN_020952AC: ; 0x020952AC
	stmdb sp!, {r4-r9,lr}
	ldrb r7, [r0, #0x0]
	ldrb r6, [r0, #0x1]
	add r0, r0, #0x4
	mov lr, #0x1000000
	add r7, lr, r7, lsl #0x18
	mov r6, r6, lsl #0x18
	ldrb r9, [r0, r7, lsr #0x18]
	subs r2, r2, #0x1
	bmi _0209530C
_020952D4:
	add r6, r6, r9, lsl #0x18
	subs r2, r2, #0x1
	ldrb r8, [r0, r6, lsr #0x18]
	ldrb r5, [r1], #0x1
	strb r8, [r0, r7, lsr #0x18]
	strb r9, [r0, r6, lsr #0x18]
	add r4, r9, r8
	and r4, r4, #0xff
	add r7, r7, lr
	ldrb r4, [r0, r4]
	ldrb r9, [r0, r7, lsr #0x18]
	eor r5, r5, r4
	strb r5, [r3], #0x1
	bge _020952D4
_0209530C:
	sub r7, r7, lr
	mov r7, r7, lsr #0x18
	mov r6, r6, lsr #0x18
	strb r7, [r0, #-0x4]
	strb r6, [r0, #-0x3]
	ldmia sp!, {r4-r9,pc}

	arm_func_start FUN_02095324
FUN_02095324: ; 0x02095324
	ldr r0, _0209532C ; =UNK_021C8C84
	bx lr
	.balign 4
_0209532C: .word UNK_021C8C84

	arm_func_start FUN_02095330
FUN_02095330: ; 0x02095330
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	mov r4, r0
	ldr r3, [r4, #0x8]
	ldr r2, [r4, #0xc]
	ldr r1, _020953E4 ; =UNK_021C8C84
	str r2, [sp, #0x4]
	str r3, [sp, #0x0]
	mov r2, #0x5
	bl MI_CpuCopy8
	ldr r1, [sp, #0x0]
	ldr r2, [r4, #0x4]
	ldr r0, [sp, #0x4]
	mov r2, r2, lsr #0x8
	mov r12, r1, lsr #0x5
	mov r3, r0, lsr #0x5
	orr r12, r12, r0, lsl #0x1b
	and lr, r2, #0x7
	and r0, r1, #0x1f
	orr lr, lr, r0, lsl #0x3
	ldr r2, _020953E4 ; =UNK_021C8C84
	ldr r1, _020953E8 ; =UNK_021C8C8A
	strb lr, [r2, #0x5]
	add r0, sp, #0x0
	str r12, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r2, #0x4
	bl MI_CpuCopy8
	ldrh r0, [r4, #0x10]
	ldr r1, [sp, #0x4]
	ldr r3, _020953E4 ; =UNK_021C8C84
	and r1, r1, #0x3f
	and r0, r0, #0x3
	orr r0, r1, r0, lsl #0x6
	strb r0, [r3, #0xa]
	ldrh r2, [r4, #0x10]
	add r0, r4, #0x12
	ldr r1, _020953EC ; =UNK_021C8C90
	mov r4, r2, asr #0x2
	mov r2, #0x2
	strb r4, [r3, #0xb]
	bl MI_CpuCopy8
	ldr r0, _020953E4 ; =UNK_021C8C84
	add sp, sp, #0x8
	ldmia sp!, {r4,pc}
	.balign 4
_020953E4: .word UNK_021C8C84
_020953E8: .word UNK_021C8C8A
_020953EC: .word UNK_021C8C90

	arm_func_start FUN_020953F0
FUN_020953F0: ; 0x020953F0
	ldr r3, _02095420 ; =UNK_021C8C78
	and r12, r1, #0xff
	ldr r0, _02095424 ; =UNK_021C8C7C
	mov r1, #0x1
	strh r12, [r3, #0x0]
	str r1, [r0, #0x0]
	cmp r2, #0x0
	movne r0, #0xff
	strneh r0, [r3, #0x0]
	ldr r0, _02095420 ; =UNK_021C8C78
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4
_02095420: .word UNK_021C8C78
_02095424: .word UNK_021C8C7C

	arm_func_start FUN_02095428
FUN_02095428:
	stmdb sp!, {r4-r6,lr}
	mov r5, #0x4
	mov r4, #0x1
_02095434:
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
	cmp r0, #0x0
	beq _02095434
	ldr r1, _02095490 ; =FUN_020953F0
	mov r0, #0x4
	bl PXI_SetFifoRecvCallback
	mov r4, #0x40000
	mov r6, #0x7
	mov r5, #0x0
_02095460:
	mov r0, r6
	mov r1, r5
	mov r2, r5
	mov r3, r5
	bl FUN_020955F4
	cmp r0, #0x1
	beq _02095488
	mov r0, r4
	bl SVC_WaitByLoop
	b _02095460
_02095488:
	mov r0, #0x1
	ldmia sp!, {r4-r6,pc}
	.balign 4
_02095490: .word FUN_020953F0

	arm_func_start FUN_02095494
FUN_02095494:
	stmdb sp!, {r4-r6,lr}
	mov r5, r2
	mov r4, r3
	mov r6, r0
	mov r0, r1
	mov r1, r5
	mov r2, r4
	bl FUN_0209555C
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl memcmp
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020954E0
FUN_020954E0: ; 0x020954E0
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r5, #0x4
	mov r4, #0x1
_020954F8:
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
	cmp r0, #0x0
	beq _020954F8
	ldr r1, _02095558 ; =FUN_020953F0
	mov r0, #0x4
	bl PXI_SetFifoRecvCallback
	mov r0, r6
	mov r1, r7
	bl DC_StoreRange
	mov r4, #0x40000
	mov r5, #0x2
_0209552C:
	mov r0, r5
	mov r1, r8
	mov r2, r7
	mov r3, r6
	bl FUN_020955F4
	cmp r0, #0x1
	ldmeqia sp!, {r4-r8,pc}
	mov r0, r4
	bl SVC_WaitByLoop
	b _0209552C
	ldmia sp!, {r4-r8,pc}
	.balign 4
_02095558: .word FUN_020953F0

	arm_func_start FUN_0209555C
FUN_0209555C:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r4, r2
	mov r6, r0
	mov r0, r4
	mov r5, r1
	bl DC_InvalidateRange
	mov r8, #0x4
	mov r7, #0x1
_02095580:
	mov r0, r8
	mov r1, r7
	bl PXI_IsCallbackReady
	cmp r0, #0x0
	beq _02095580
	ldr r1, _020955F0 ; =FUN_020953F0
	mov r0, #0x4
	bl PXI_SetFifoRecvCallback
	mov r0, r5, lsl #0x10
	mov r8, r0, lsr #0x10
	mov r7, #0x40000
	mov r9, #0x1
_020955B0:
	mov r0, r9
	mov r1, r6
	mov r2, r8
	mov r3, r4
	bl FUN_020955F4
	cmp r0, #0x1
	beq _020955D8
	mov r0, r7
	bl SVC_WaitByLoop
	b _020955B0
_020955D8:
	mov r0, r4
	mov r1, r5
	bl DC_InvalidateRange
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020955F0: .word FUN_020953F0

	arm_func_start FUN_020955F4
FUN_020955F4: ; 0x020955F4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc4
	ldr ip, _02095AAC ; =0x0000FFFF
	ldr sl, _02095AB0 ; =UNK_021C8CA0
	and r8, r2, r12
	and r7, r1, r12
	mov r5, r1, lsr #0x10
	mov r4, r3, lsr #0x10
	and r1, r3, r12
	orr r3, r8, #0x30000
	str r3, [sp, #0xc]
	ldr r3, _02095AB4 ; =0x01050000
	orr r2, r2, #0x20000
	orr r3, r1, r3
	str r3, [sp, #0x14]
	orr r1, r1, #0x1040000
	mov r9, r0
	and r0, r5, #0xff
	str r2, [sp, #0x1c]
	str r1, [sp, #0x24]
	ldr r1, _02095AB8 ; =0x02002200
	mov r8, #0x0
	orr r2, r4, #0x40000
	orr r1, r1, r10, lsr #0x18
	str r1, [sp, #0x28]
	and r1, r12, r10, lsr #0x8
	orr r1, r1, #0x10000
	ldr r3, _02095ABC ; =0x02002300
	str r2, [sp, #0x10]
	orr r2, r0, r3
	str r2, [sp, #0x8]
	orr r2, r4, #0x30000
	str r2, [sp, #0x20]
	ldr r2, _02095AC0 ; =0x02002500
	mov r6, r10, lsl #0x8
	str r1, [sp, #0x2c]
	and r1, r6, #0xff00
	orr r0, r0, r2
	ldr r3, _02095AC4 ; =0x01020000
	str r0, [sp, #0x18]
	orr r0, r1, r3
	str r0, [sp, #0x30]
	mov r0, #0x20000
	str r0, [sp, #0x40]
	mov r0, #0x5
	str r0, [sp, #0xac]
	mov r0, #0x3
	str r0, [sp, #0xb0]
	mov r0, #0x6
	str r0, [sp, #0xb8]
	mov r0, #0x4000
	orr r7, r7, #0x10000
	str r8, [sp, #0xb4]
	mov r4, #0x1
	str r8, [sp, #0xa8]
	mov r5, #0x4
	str r8, [sp, #0xa4]
	str r8, [sp, #0xa0]
	str r8, [sp, #0x90]
	str r8, [sp, #0x98]
	str r8, [sp, #0x9c]
	str r8, [sp, #0x94]
	str r8, [sp, #0x8c]
	str r8, [sp, #0x6c]
	str r8, [sp, #0x74]
	str r8, [sp, #0x7c]
	str r8, [sp, #0x84]
	str r8, [sp, #0x88]
	str r8, [sp, #0x80]
	str r8, [sp, #0x78]
	str r8, [sp, #0x70]
	str r8, [sp, #0x68]
	str r8, [sp, #0x64]
	str r8, [sp, #0x38]
	str r8, [sp, #0x44]
	str r8, [sp, #0x4c]
	str r8, [sp, #0x54]
	str r8, [sp, #0x5c]
	str r8, [sp, #0x60]
	str r8, [sp, #0x58]
	str r8, [sp, #0x50]
	str r8, [sp, #0x48]
	str r8, [sp, #0x3c]
	str r8, [sp, #0x34]
	mov r6, r8
	str r0, [sp, #0xbc]
_0209574C:
	cmp r8, #0x0
	bne _02095988
	ldr r0, _02095AC8 ; =UNK_021C8C7C
	cmp r9, #0x7
	str r6, [r0, #0x0]
	addls pc, pc, r9, lsl #0x2
	b _0209574C
_02095768:
	b _0209574C
_0209576C:
	b _02095788
_02095770:
	b _02095834
_02095774:
	b _02095854
_02095778:
	b _020958F0
_0209577C:
	b _020958F0
_02095780:
	b _02095948
_02095784:
	b _02095968
_02095788:
	ldr r1, [sp, #0x8]
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x34]
	blt _0209574C
	ldr r2, [sp, #0x38]
	mov r0, r5
	mov r1, r7
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x3c]
	blt _0209574C
	ldr r1, [sp, #0x40]
	ldr r2, [sp, #0x44]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x48]
	blt _0209574C
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x4c]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x50]
	blt _0209574C
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0x54]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x58]
	blt _0209574C
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x5c]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x60]
	movge r8, r4
	b _0209574C
_02095834:
	ldr r1, _02095ACC ; =0x03002000
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movge r8, r4
	ldrlt r8, [sp, #0x64]
	b _0209574C
_02095854:
	ldr r1, [sp, #0x18]
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x68]
	blt _020958E0
	ldr r2, [sp, #0x6c]
	mov r0, r5
	mov r1, r7
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x70]
	blt _020958E0
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x74]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x78]
	blt _020958E0
	ldr r1, [sp, #0x20]
	ldr r2, [sp, #0x7c]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x80]
	blt _020958E0
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x84]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x88]
	movge r8, r4
_020958E0:
	bl OS_GetTick
	str r0, [sp, #0x0]
	mov r11, r1
	b _0209574C
_020958F0:
	ldr r1, [sp, #0x28]
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x8c]
	blt _0209574C
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x90]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x94]
	blt _0209574C
	ldr r1, [sp, #0x30]
	ldr r2, [sp, #0x98]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x9c]
	movge r8, r4
	b _0209574C
_02095948:
	ldr r1, _02095AD0 ; =0x03002D00
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movge r8, r4
	ldrlt r8, [sp, #0xa0]
	b _0209574C
_02095968:
	ldr r1, _02095AD4 ; =0x03002100
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movge r8, r4
	ldrlt r8, [sp, #0xa4]
	b _0209574C
_02095988:
	ldr r0, _02095AC8 ; =UNK_021C8C7C
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	bne _0209574C
	ldr r0, _02095AD8 ; =UNK_021C8C78
	ldr r8, [sp, #0xa8]
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02095AA0
	cmp r9, #0x7
	addls pc, pc, r9, lsl #0x2
	b _0209574C
	b _0209574C
	b _020959D8
	b _020959E4
	b _020959EC
	b _020959F4
	b _020959F4
	b _02095A88
	b _02095A94
_020959D8:
	add sp, sp, #0xc4
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_020959E4:
	mov r9, r5
	b _0209574C
_020959EC:
	ldr r9, [sp, #0xac]
	b _0209574C
_020959F4:
	mov r0, r10
	mov r1, r4
	bl DC_InvalidateRange
	cmp r9, #0x4
	bne _02095A24
	ldrb r0, [r10, #0x0]
	ands r0, r0, #0x2
	ldrne r9, [sp, #0xb0]
	bne _0209574C
	add sp, sp, #0xc4
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_02095A24:
	ldrb r1, [r10, #0x0]
	ands r0, r1, #0x1
	addeq sp, sp, #0xc4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r11,pc}
	ands r0, r1, #0x20
	bne _02095A74
	bl OS_GetTick
	ldr r2, [sp, #0x0]
	ldr r3, [sp, #0xb4]
	subs r2, r0, r2
	sbc r0, r1, r11
	mov r1, r0, lsl #0x6
	orr r1, r1, r2, lsr #0x1a
	mov r0, r2, lsl #0x6
	ldr r2, _02095ADC ; =0x000082EA
	bl _ll_udiv
	cmp r1, #0x0
	cmpeq r0, #0xfa0
	bls _02095A7C
_02095A74:
	ldr r9, [sp, #0xb8]
	b _0209574C
_02095A7C:
	ldr r0, [sp, #0xbc]
	bl SVC_WaitByLoop
	b _0209574C
_02095A88:
	add sp, sp, #0xc4
	mov r0, r8
	ldmia sp!, {r4-r11,pc}
_02095A94:
	add sp, sp, #0xc4
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_02095AA0:
	mov r0, r8
	add sp, sp, #0xc4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_02095AAC: .word 0x0000FFFF
_02095AB0: .word UNK_021C8CA0
_02095AB4: .word 0x01050000
_02095AB8: .word 0x02002200
_02095ABC: .word 0x02002300
_02095AC0: .word 0x02002500
_02095AC4: .word 0x01020000
_02095AC8: .word UNK_021C8C7C
_02095ACC: .word 0x03002000
_02095AD0: .word 0x03002D00
_02095AD4: .word 0x03002100
_02095AD8: .word UNK_021C8C78
_02095ADC: .word 0x000082EA

	arm_func_start FUN_02095AE0
FUN_02095AE0:
	ldrb r0, [r0, #0x0]
	cmp r0, #0x7f
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x1
	movcc r0, #0x0
	bxcc lr
	cmp r0, #0xdf
	movls r0, #0x1
	movhi r0, #0x0
	bx lr

	arm_func_start FUN_02095B0C
FUN_02095B0C:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r5, r0
	mov r4, r1
	bl FUN_02095AE0
	cmp r0, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
	add r1, sp, #0x0
	mov r0, r5
	mov r2, #0x4
	bl MI_CpuCopy8
	add r1, sp, #0x4
	mov r0, r4
	mov r2, #0x4
	bl MI_CpuCopy8
	ldr r3, [sp, #0x4]
	ldr r2, [sp, #0x0]
	mvn r0, #0x1
	orr r1, r2, r3
	cmp r1, r0
	addeq sp, sp, #0xc
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
	mvn r0, r3
	ands r0, r2, r0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_02095B88
FUN_02095B88:
	mov r2, #0x0
_02095B8C:
	ldrb r1, [r0, r2]
	cmp r1, #0x0
	movne r0, #0x1
	bxne lr
	add r2, r2, #0x1
	cmp r2, #0x20
	blt _02095B8C
	mov r0, #0x0
	bx lr

	arm_func_start FUN_02095BB0
FUN_02095BB0: ; 0x02095BB0
	mvn r2, #0x0
	mov r12, #0x0
	eor r3, r2, r2, lsr r0
	mov r2, r12
_02095BC0:
	rsb r0, r2, #0x18
	mov r0, r3, lsr r0
	strb r0, [r1, r12]
	add r12, r12, #0x1
	cmp r12, #0x4
	add r2, r2, #0x8
	blt _02095BC0
	bx lr

	arm_func_start FUN_02095BE0
FUN_02095BE0: ; 0x02095BE0
	stmdb sp!, {r4,lr}
	mov lr, #0x0
	mov r4, lr
	mov r2, lr
_02095BF0:
	ldrb r3, [r0, lr]
	mov r12, r2
_02095BF8:
	mov r1, r3, asr r12
	ands r1, r1, #0x1
	add r12, r12, #0x1
	addne r4, r4, #0x1
	cmp r12, #0x8
	blt _02095BF8
	add lr, lr, #0x1
	cmp lr, #0x4
	blt _02095BF0
	and r0, r4, #0xff
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02095C24
FUN_02095C24: ; 0x02095C24
	ldr ip, _02095C34 ; =MI_CpuCopy8
	ldr r1, _02095C38 ; =UNK_021C8C84
	mov r2, #0xe
	bx r12
	.balign 4
_02095C34: .word MI_CpuCopy8
_02095C38: .word UNK_021C8C84

	arm_func_start FUN_02095C3C
FUN_02095C3C:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r1, _02095CD8 ; =UNK_021C8C80
	mov r10, r0
	ldr r8, [r1, #0x0]
	mov r7, r10
	mov r9, #0x0
	add r4, r10, #0x400
	add r6, r10, #0x500
	mov r5, #0x100
	mov r11, #0xfe
_02095C68:
	mov r0, r6
	mov r1, r7
	mov r2, r11
	bl MATH_CalcCRC16
	add r1, r10, r9, lsl #0x8
	strh r0, [r1, #0xfe]
_02095C80:
	mov r0, r8
	mov r1, r5
	mov r2, r7
	bl FUN_020954E0
	mov r0, r7
	mov r1, r8
	mov r2, r5
	mov r3, r4
	bl FUN_02095494
	cmp r0, #0x0
	beq _02095C80
	add r9, r9, #0x1
	cmp r9, #0x4
	add r7, r7, #0x100
	add r8, r8, #0x100
	blt _02095C68
	bl FUN_02095428
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_02095CD8: .word UNK_021C8C80

	arm_func_start FUN_02095CDC
FUN_02095CDC: ; 0x02095CDC
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r3, _02095D64 ; =UNK_021C8C80
	mov r4, r0
	ldr r6, [r3, #0x0]
	mov r9, r1
	mov r8, r2
	mov r7, #0x0
	mov r5, #0x100
_02095D00:
	ldr r0, [r9, r7, lsl #0x2]
	cmp r0, #0x0
	beq _02095D38
_02095D0C:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_020954E0
	mov r0, r4
	mov r1, r6
	mov r2, r5
	mov r3, r8
	bl FUN_02095494
	cmp r0, #0x0
	beq _02095D0C
_02095D38:
	add r7, r7, #0x1
	cmp r7, #0x4
	add r4, r4, #0x100
	add r6, r6, #0x100
	blt _02095D00
	bl FUN_02095428
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_02095D64: .word UNK_021C8C80

	arm_func_start FUN_02095D68
FUN_02095D68:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _02095D98 ; =UNK_021C8C80
	mov r2, r0
	ldr r0, [r1, #0x0]
	mov r1, #0x400
	bl FUN_0209555C
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_02095D98: .word UNK_021C8C80

	arm_func_start FUN_02095D9C
FUN_02095D9C:
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x20
	mov r1, r0
	mov r2, r4
	bl FUN_0209555C
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldrh r2, [r4, #0x0]
	ldr r1, _02095DDC ; =UNK_021C8C80
	mov r0, #0x1
	mov r2, r2, lsl #0x3
	sub r2, r2, #0x400
	str r2, [r1, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_02095DDC: .word UNK_021C8C80

	arm_func_start FUN_02095DE0
FUN_02095DE0:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r2, _02095EBC ; =UNK_021C8C80
	mov r10, r1
	ldr r8, [r2, #0x0]
	bl FUN_02095330
	ldr r1, _02095EC0 ; =0x0000A001
	add r0, r10, #0x200
	bl MATHi_CRC16InitTableRev
	mov r9, #0x0
	add r4, r10, #0x100
	add r6, r10, #0xf0
	mov r7, #0x100
	mov r5, #0xe
	mov r11, #0xfe
_02095E1C:
	mov r0, r8
	mov r1, r7
	mov r2, r10
	bl FUN_0209555C
	cmp r0, #0x0
	bne _02095E44
	bl OS_Terminate
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_02095E44:
	ldr r0, _02095EC4 ; =UNK_021C8C84
	mov r1, r6
	mov r2, r5
	bl MI_CpuCopy8
	mov r1, r10
	mov r2, r11
	add r0, r10, #0x200
	bl MATH_CalcCRC16
	strh r0, [r10, #0xfe]
_02095E68:
	mov r0, r8
	mov r1, r7
	mov r2, r10
	bl FUN_020954E0
	mov r0, r10
	mov r1, r8
	mov r2, r7
	mov r3, r4
	bl FUN_02095494
	cmp r0, #0x0
	beq _02095E68
	add r9, r9, #0x1
	cmp r9, #0x2
	add r8, r8, #0x100
	blt _02095E1C
	bl FUN_02095428
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_02095EBC: .word UNK_021C8C80
_02095EC0: .word 0x0000A001
_02095EC4: .word UNK_021C8C84

	arm_func_start FUN_02095EC8
FUN_02095EC8:
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, _02095F90 ; =UNK_021C8C84
	mov r1, r4
	mov r2, #0x6
	bl MI_CpuCopy8
	ldr r3, [r4, #0x0]
	mvn r0, #0x0
	ldr r2, [r4, #0x4]
	ldr r1, _02095F94 ; =0x000007FF
	and r0, r3, r0
	str r0, [r4, #0x0]
	and r1, r2, r1
	ldr r0, _02095F98 ; =UNK_021C8C89
	str r1, [r4, #0x4]
	add r1, r4, #0x8
	mov r2, #0x6
	bl MI_CpuCopy8
	add r12, r4, #0x8
	ldr r1, [r4, #0x8]
	ldr r0, [r12, #0x4]
	mov r1, r1, lsr #0x3
	orr r1, r1, r0, lsl #0x1d
	str r1, [r4, #0x8]
	mov r0, r0, lsr #0x3
	str r0, [r12, #0x4]
	ldr r3, [r4, #0x8]
	mvn r0, #0x0
	ldr r2, [r12, #0x4]
	ldr r1, _02095F94 ; =0x000007FF
	and r0, r3, r0
	str r0, [r4, #0x8]
	and r1, r2, r1
	ldr r0, _02095F9C ; =UNK_021C8C8E
	str r1, [r12, #0x4]
	add r1, r4, #0x10
	mov r2, #0x2
	bl MI_CpuCopy8
	ldrh r1, [r4, #0x10]
	ldr r3, _02095FA0 ; =0x000003FF
	ldr r0, _02095FA4 ; =UNK_021C8C90
	mov r1, r1, asr #0x6
	strh r1, [r4, #0x10]
	ldrh r12, [r4, #0x10]
	add r1, r4, #0x12
	mov r2, #0x2
	and r3, r12, r3
	strh r3, [r4, #0x10]
	bl MI_CpuCopy8
	ldmia sp!, {r4,pc}
	.balign 4
_02095F90: .word UNK_021C8C84
_02095F94: .word 0x000007FF
_02095F98: .word UNK_021C8C89
_02095F9C: .word UNK_021C8C8E
_02095FA0: .word 0x000003FF
_02095FA4: .word UNK_021C8C90

	arm_func_start FUN_02095FA8
FUN_02095FA8: ; 0x02095FA8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _02095FD8 ; =UNK_021C8C80
	mov r2, r0
	ldr r0, [r1, #0x0]
	mov r1, #0x300
	bl FUN_0209555C
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_02095FD8: .word UNK_021C8C80

	arm_func_start FUN_02095FDC
FUN_02095FDC: ; 0x02095FDC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	add r1, r5, r4, lsl #0x8
	mov r0, #0x0
	mov r2, #0x100
	bl MIi_CpuClear16
	add r0, r5, r4, lsl #0x8
	mov r1, #0xff
	strb r1, [r0, #0xe7]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_02096010
FUN_02096010: ; 0x02096010
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov r7, r0
	mov r1, r7
	mov r0, #0x0
	mov r2, #0x400
	bl MIi_CpuClear16
	mov r2, #0x0
	mov r1, #0xff
_02096034:
	add r0, r7, r2, lsl #0x8
	add r2, r2, #0x1
	strb r1, [r0, #0xe7]
	cmp r2, #0x3
	blt _02096034
	add r0, sp, #0x0
	bl FUN_020967A4
	add r0, sp, #0x0
	bl FUN_02095330
	mov r6, r0
	mov r5, #0x0
	mov r4, #0xe
_02096064:
	mov r0, r6
	mov r2, r4
	add r1, r7, #0xf0
	bl MI_CpuCopy8
	add r5, r5, #0x1
	cmp r5, #0x2
	add r7, r7, #0x100
	blt _02096064
	mov r0, #0x0
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_02096090
FUN_02096090:
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	mov r4, r0
	ldrb r0, [r4, #0xe7]
	cmp r0, #0xff
	addeq sp, sp, #0x8
	moveq r0, #0x1
	ldmeqia sp!, {r4,pc}
	cmp r0, #0x2
	addhi sp, sp, #0x8
	movhi r0, #0x0
	ldmhiia sp!, {r4,pc}
	add r0, r4, #0x40
	bl FUN_02095B88
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r1, _0209618C ; =UNK_020FF574
	add r0, r4, #0xc0
	mov r2, #0x4
	bl memcmp
	cmp r0, #0x0
	beq _02096140
	add r0, r4, #0xc4
	bl FUN_02095AE0
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldrb r0, [r4, #0xd0]
	cmp r0, #0x20
	addhi sp, sp, #0x8
	movhi r0, #0x0
	ldmhiia sp!, {r4,pc}
	add r1, sp, #0x0
	bl FUN_02095BB0
	add r1, sp, #0x0
	add r0, r4, #0xc0
	bl FUN_02095B0C
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_02096140:
	ldr r1, _0209618C ; =UNK_020FF574
	add r0, r4, #0xc8
	mov r2, #0x4
	bl memcmp
	cmp r0, #0x0
	beq _02096180
	add r0, r4, #0xc8
	bl FUN_02095AE0
	cmp r0, #0x0
	bne _02096180
	add r0, r4, #0xcc
	bl FUN_02095AE0
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_02096180:
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4,pc}
	.balign 4
_0209618C: .word UNK_020FF574

	arm_func_start FUN_02096190
FUN_02096190: ; 0x02096190
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r10, r0
	mov r1, #0x0
	mov r2, #0x700
	bl MI_CpuFill8
	mov r0, r10
	bl FUN_02095D9C
	cmp r0, #0x0
	addeq sp, sp, #0x14
	ldreq r0, _020964B4 ; =0xFFFFD8EF
	ldmeqia sp!, {r4-r11,pc}
	ldr r1, _020964B8 ; =0x0000A001
	add r0, r10, #0x500
	bl MATHi_CRC16InitTableRev
	mov r0, r10
	bl FUN_02095D68
	cmp r0, #0x0
	addeq sp, sp, #0x14
	ldreq r0, _020964B4 ; =0xFFFFD8EF
	ldmeqia sp!, {r4-r11,pc}
	add r0, sp, #0x0
	mov r1, #0x0
	mov r2, #0x10
	bl MI_CpuFill8
	mov r8, r10
	mov r7, r10
	mov r9, #0x0
	add r11, sp, #0x0
	add r6, r10, #0x500
	mov r4, #0x1
	mov r5, #0xfe
_02096210:
	mov r0, r6
	mov r1, r8
	mov r2, r5
	bl MATH_CalcCRC16
	add r1, r10, r9, lsl #0x8
	ldrh r1, [r1, #0xfe]
	cmp r0, r1
	bne _02096240
	mov r0, r7
	bl FUN_02096090
	cmp r0, #0x0
	strne r4, [r11, r9, lsl #0x2]
_02096240:
	add r9, r9, #0x1
	cmp r9, #0x3
	add r8, r8, #0x100
	add r7, r7, #0x100
	blt _02096210
	add r0, r10, #0x500
	add r1, r10, #0x300
	mov r2, #0xfe
	bl MATH_CalcCRC16
	add r1, r10, #0x300
	ldrh r1, [r1, #0xfe]
	cmp r0, r1
	moveq r0, #0x1
	ldr r1, [sp, #0x0]
	streq r0, [sp, #0xc]
	cmp r1, #0x0
	beq _020962BC
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020962BC
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _020962BC
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	beq _020962BC
	add r0, r10, #0xf0
	bl FUN_02095C24
	add sp, sp, #0x14
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_020962BC:
	cmp r1, #0x0
	bne _0209630C
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _0209630C
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	bne _0209630C
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	bne _0209630C
	mov r0, r10
	bl FUN_02096010
	mov r0, r10
	bl FUN_02095C3C
	cmp r0, #0x0
	movne r0, #0x0
	add sp, sp, #0x14
	ldreq r0, _020964BC ; =0xFFFFD8F0
	ldmia sp!, {r4-r11,pc}
_0209630C:
	cmp r1, #0x0
	beq _02096320
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _0209635C
_02096320:
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _02096338
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	bne _0209635C
_02096338:
	mov r0, r10
	bl FUN_02096010
	mov r0, r10
	bl FUN_02095C3C
	cmp r0, #0x0
	movne r0, #0x0
	add sp, sp, #0x14
	ldreq r0, _020964BC ; =0xFFFFD8F0
	ldmia sp!, {r4-r11,pc}
_0209635C:
	cmp r1, #0x0
	bne _02096394
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _02096394
	mov r0, r10
	bl FUN_02096010
	mov r0, r10
	bl FUN_02095C3C
	cmp r0, #0x0
	ldrne r0, _020964C0 ; =0xFFFFD8ED
	add sp, sp, #0x14
	ldreq r0, _020964BC ; =0xFFFFD8F0
	ldmia sp!, {r4-r11,pc}
_02096394:
	cmp r1, #0x0
	bne _020963C4
	mov r0, r10
	mov r1, #0x0
	bl FUN_02095FDC
	add r0, r10, #0x1f0
	add r1, r10, #0xf0
	mov r2, #0xe
	bl MI_CpuCopy8
	ldrb r0, [r10, #0x1ef]
	strb r0, [r10, #0xef]
	b _020963F4
_020963C4:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _020963F4
	mov r0, r10
	mov r1, #0x1
	bl FUN_02095FDC
	add r0, r10, #0xf0
	add r1, r10, #0x1f0
	mov r2, #0xe
	bl MI_CpuCopy8
	ldrb r0, [r10, #0xef]
	strb r0, [r10, #0x1ef]
_020963F4:
	add r0, r10, #0xf0
	bl FUN_02095C24
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	bne _02096414
	mov r0, r10
	mov r1, #0x2
	bl FUN_02095FDC
_02096414:
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	bne _02096430
	add r1, r10, #0x300
	mov r0, #0x0
	mov r2, #0x100
	bl MIi_CpuClear16
_02096430:
	mov r4, #0x0
	mov r1, r4
	add r0, sp, #0x0
	add r5, r10, #0xef
	mov r6, #0x1
_02096444:
	ldr r2, [r0, r1, lsl #0x2]
	cmp r2, #0x0
	bne _0209647C
	ldrb r2, [r10, #0xef]
	mov r7, r6, lsl r1
	ands r2, r2, r7
	beq _0209647C
	ldrb r3, [r5, #0x0]
	mvn r2, r7
	mov r4, r6
	and r2, r3, r2
	strb r2, [r5, #0x0]
	ldrb r2, [r10, #0xef]
	strb r2, [r10, #0x1ef]
_0209647C:
	add r1, r1, #0x1
	cmp r1, #0x3
	blt _02096444
	mov r0, r10
	bl FUN_02095C3C
	cmp r0, #0x0
	addeq sp, sp, #0x14
	ldreq r0, _020964BC ; =0xFFFFD8F0
	ldmeqia sp!, {r4-r11,pc}
	cmp r4, #0x0
	ldrne r0, _020964C4 ; =0xFFFFD8EE
	moveq r0, #0x0
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020964B4: .word 0xFFFFD8EF
_020964B8: .word 0x0000A001
_020964BC: .word 0xFFFFD8F0
_020964C0: .word 0xFFFFD8ED
_020964C4: .word 0xFFFFD8EE

	arm_func_start FUN_020964C8
FUN_020964C8:
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	add r0, sp, #0x0
	bl FUN_02095EC8
	ldr r2, [sp, #0x8]
	ldr r1, [sp, #0xc]
	mov r0, #0x0
	cmp r1, r0
	cmpeq r2, r0
	bne _0209650C
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	cmp r1, r0
	cmpeq r2, r0
	addeq sp, sp, #0x14
	moveq r0, #0x1
	ldmeqia sp!, {pc}
_0209650C:
	mov r0, #0x0
	add sp, sp, #0x14
	ldmia sp!, {pc}

	arm_func_start FUN_02096518
FUN_02096518: ; 0x02096518
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x18
	mov r4, r0
	add r0, sp, #0x0
	bl FUN_02095EC8
	add r0, sp, #0x0
	ldmia r0, {r2-r3}
	stmia r4, {r2-r3}
	add r1, sp, #0x8
	add r0, r4, #0x8
	ldmia r1, {r2-r3}
	stmia r0, {r2-r3}
	ldr r2, [sp, #0x0]
	ldr r1, [sp, #0x4]
	mov r0, #0x0
	cmp r1, r0
	cmpeq r2, r0
	streq r0, [r4, #0x10]
	movne r0, #0x1
	strne r0, [r4, #0x10]
	add sp, sp, #0x18
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02096570
FUN_02096570: ; 0x02096570
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x28
	add r2, sp, #0x0
	mov r1, #0x0
	strb r1, [r2, #0x0]
	strb r1, [r2, #0x1]
	strb r1, [r2, #0x2]
	strb r1, [r2, #0x3]
	strb r1, [r2, #0x4]
	mov r5, r0
	strb r1, [r2, #0x5]
	bl FUN_02095EC8
	bl RTC_Init
	add r0, sp, #0x8
	bl RTC_GetDate
	cmp r0, #0x0
	addne sp, sp, #0x28
	movne r0, #0x0
	ldmneia sp!, {r4-r10,pc}
	add r0, sp, #0x18
	bl RTC_GetTime
	cmp r0, #0x0
	addne sp, sp, #0x28
	movne r0, #0x0
	ldmneia sp!, {r4-r10,pc}
	add r0, sp, #0x8
	add r1, sp, #0x18
	bl RTC_ConvertDateTimeToSecond
	mov r4, r0
	mov r0, #0x0
	subs r2, r4, r0
	sbcs r2, r1, r0
	addlt sp, sp, #0x28
	ldmltia sp!, {r4-r10,pc}
	bl OS_IsTickAvailable
	cmp r0, #0x0
	beq _0209660C
	ldr r0, _02096700 ; =OS_GetTick
	adds r4, r4, r0
_0209660C:
	add r0, sp, #0x0
	bl OS_GetMacAddress
	ldrb r1, [sp, #0x0]
	ldr r6, _02096704 ; =0x5D588B65
	ldr r7, _02096708 ; =0x00269EC3
	ldrb r0, [sp, #0x1]
	mla r9, r4, r6, r7
	mov r1, r1, lsl #0x10
	orr r1, r1, r0, lsl #0x8
	ldrb r2, [sp, #0x2]
	ldr r0, _0209670C ; =0x000009BF
	ldrb r8, [sp, #0x3]
	orr r1, r2, r1
	cmp r1, r0
	movne r1, #0x1
	mov r2, r9, lsr #0x10
	mov r0, #0x3e8
	mul r3, r2, r0
	mov r2, r3, lsr #0x10
	mov r3, r8, lsl #0x10
	ldrb r4, [sp, #0x4]
	ldrb r0, [sp, #0x5]
	mov r8, #0x0
	orr r10, r3, r4, lsl #0x8
	strh r2, [r5, #0x10]
	str r8, [r5, #0x8]
	str r8, [r5, #0xc]
	moveq r1, #0x0
	ldr r2, [r5, #0xc]
	ldr r3, [r5, #0x8]
	cmp r2, r8
	cmpeq r3, r8
	and r4, r1, #0xff
	orr r10, r0, r10
	bne _020966F4
_02096698:
	mla r9, r6, r9, r7
	b _020966A4
_020966A0:
	mla r9, r6, r9, r7
_020966A4:
	cmp r9, #0x0
	beq _020966A0
	ldrh r1, [r5, #0x12]
	mov r0, r9, lsl #0x10
	mov r0, r0, lsr #0x10
	cmp r1, r0
	beq _020966A0
	strh r0, [r5, #0x12]
	ldrh r0, [r5, #0x12]
	mov r1, r10
	mov r2, r4
	mov r3, r8
	bl FUN_02096988
	str r0, [r5, #0x8]
	str r1, [r5, #0xc]
	ldr r0, [r5, #0xc]
	ldr r1, [r5, #0x8]
	cmp r0, r8
	cmpeq r1, r8
	beq _02096698
_020966F4:
	mov r0, #0x1
	add sp, sp, #0x28
	ldmia sp!, {r4-r10,pc}
	.balign 4
_02096700: .word OS_GetTick
_02096704: .word 0x5D588B65
_02096708: .word 0x00269EC3
_0209670C: .word 0x000009BF

	arm_func_start FUN_02096710
FUN_02096710: ; 0x02096710
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x14
	mov r5, r0
	add r0, sp, #0x0
	mov r4, r1
	bl FUN_02095EC8
	add r12, r5, #0x8
	ldmia r12, {r2-r3}
	stmia r5, {r2-r3}
	add r1, sp, #0x8
	ldmia r1, {r2-r3}
	mov r0, r5
	mov r1, r4
	stmia r12, {r2-r3}
	bl FUN_02095DE0
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x14
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_02096760
FUN_02096760: ; 0x02096760
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x18
	mov r4, r0
	add r0, sp, #0x0
	bl FUN_020967A4
	cmp r0, #0x0
	addeq sp, sp, #0x18
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	add r0, sp, #0x0
	mov r1, r4
	bl FUN_02095DE0
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x18
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020967A4
FUN_020967A4:
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x28
	mov r8, r0
	bl FUN_02095EC8
	bl RTC_Init
	add r0, sp, #0x8
	bl RTC_GetDate
	cmp r0, #0x0
	addne sp, sp, #0x28
	movne r0, #0x0
	ldmneia sp!, {r4-r10,pc}
	add r0, sp, #0x18
	bl RTC_GetTime
	cmp r0, #0x0
	addne sp, sp, #0x28
	movne r0, #0x0
	ldmneia sp!, {r4-r10,pc}
	add r0, sp, #0x8
	add r1, sp, #0x18
	bl RTC_ConvertDateTimeToSecond
	mov r4, r0
	mov r0, #0x0
	subs r2, r4, r0
	sbcs r2, r1, r0
	addlt sp, sp, #0x28
	ldmltia sp!, {r4-r10,pc}
	bl OS_IsTickAvailable
	cmp r0, #0x0
	beq _02096820
	ldr r0, _02096978 ; =OS_GetTick
	adds r4, r4, r0
_02096820:
	add r0, sp, #0x0
	bl OS_GetMacAddress
	ldrb r1, [sp, #0x0]
	ldr sb, _0209697C ; =0x5D588B65
	ldr sl, _02096980 ; =0x00269EC3
	ldrb r0, [sp, #0x1]
	mla r5, r4, r9, r10
	mov r1, r1, lsl #0x10
	orr r1, r1, r0, lsl #0x8
	ldrb r2, [sp, #0x2]
	ldr r0, _02096984 ; =0x000009BF
	ldrb r6, [sp, #0x3]
	orr r1, r2, r1
	cmp r1, r0
	movne r1, #0x1
	moveq r1, #0x0
	mov r2, r5, lsr #0x10
	mov r0, #0x3e8
	mul r3, r2, r0
	mov r2, r3, lsr #0x10
	ldrb r0, [sp, #0x5]
	ldrb r4, [sp, #0x4]
	mov r3, r6, lsl #0x10
	and r7, r1, #0xff
	orr r3, r3, r4, lsl #0x8
	strh r2, [r8, #0x10]
	mov r4, #0x0
	str r4, [r8, #0x0]
	str r4, [r8, #0x4]
	ldrh r2, [r8, #0x12]
	orr r6, r0, r3
	cmp r2, #0x0
	bne _02096910
	str r4, [r8, #0x8]
	str r4, [r8, #0xc]
	ldr r0, [r8, #0xc]
	ldr r1, [r8, #0x8]
	cmp r0, r4
	cmpeq r1, r4
	bne _0209696C
_020968C0:
	mul r0, r5, r9
	adds r5, r0, r10
	bne _020968D8
_020968CC:
	mul r0, r5, r9
	adds r5, r0, r10
	beq _020968CC
_020968D8:
	strh r5, [r8, #0x12]
	ldrh r0, [r8, #0x12]
	mov r1, r6
	mov r2, r7
	mov r3, r4
	bl FUN_02096988
	str r0, [r8, #0x8]
	str r1, [r8, #0xc]
	ldr r0, [r8, #0xc]
	ldr r1, [r8, #0x8]
	cmp r0, r4
	cmpeq r1, #0x0
	beq _020968C0
	b _0209696C
_02096910:
	str r4, [r8, #0x8]
	str r4, [r8, #0xc]
	ldr r0, [r8, #0xc]
	ldr r1, [r8, #0x8]
	cmp r0, r4
	cmpeq r1, r4
	bne _0209696C
	add r5, r8, #0x12
_02096930:
	ldrh r0, [r5, #0x0]
	mov r1, r6
	mov r2, r7
	add r0, r0, #0x1
	strh r0, [r5, #0x0]
	ldrh r0, [r8, #0x12]
	mov r3, r4
	bl FUN_02096988
	str r0, [r8, #0x8]
	str r1, [r8, #0xc]
	ldr r0, [r8, #0xc]
	ldr r1, [r8, #0x8]
	cmp r0, r4
	cmpeq r1, r4
	beq _02096930
_0209696C:
	mov r0, #0x1
	add sp, sp, #0x28
	ldmia sp!, {r4-r10,pc}
	.balign 4
_02096978: .word OS_GetTick
_0209697C: .word 0x5D588B65
_02096980: .word 0x00269EC3
_02096984: .word 0x000009BF

	arm_func_start FUN_02096988
FUN_02096988: ; 0x02096988
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov lr, #0x0
	and r12, lr, #0x0
	mvn r5, #0xff000000
	ldr r4, _02096B08 ; =0x0000FFFF
	and r2, r2, #0x1
	mov r6, r12, lsl #0x2
	and r3, r3, #0x3
	and r5, r1, r5
	orr r1, r3, r2, lsl #0x2
	orr r6, r6, r2, lsr #0x1e
	mov r7, r12, lsl #0x3
	and r2, r0, r4
	orr r0, r1, r5, lsl #0x3
	orr r1, r0, r2, lsl #0x1b
	mov r3, r12, lsl #0x1b
	orr r3, r3, r2, lsr #0x5
	orr r7, r7, r5, lsr #0x1d
	orr r0, r12, r6
	orr r0, r7, r0
	orr r0, r3, r0
	add r2, sp, #0x0
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
_020969EC:
	ldrb r0, [r2, #0x0]
	add lr, lr, #0x1
	cmp lr, #0x6
	eor r0, r0, #0xd6
	strb r0, [r2], #0x1
	blt _020969EC
	ldr r2, _02096B0C ; =UNK_020FF580
	add r5, sp, #0x0
	mov r4, #0x0
_02096A10:
	ldrb r3, [r5, #0x0]
	add r4, r4, #0x1
	cmp r4, #0x5
	mov r0, r3, asr #0x4
	and r1, r0, #0xf
	and r0, r3, #0xf
	ldrb r1, [r2, r1]
	ldrb r0, [r2, r0]
	orr r0, r0, r1, lsl #0x4
	strb r0, [r5], #0x1
	blt _02096A10
	add r0, sp, #0x0
	add r1, sp, #0x8
	mov r2, #0x8
	bl MI_CpuCopy8
	ldr r4, _02096B10 ; =UNK_020FF578
	add r5, sp, #0x8
	mov r3, #0x0
	add r1, sp, #0x0
_02096A5C:
	ldrb r2, [r5, #0x0]
	ldrb r0, [r4, #0x0]
	add r3, r3, #0x1
	cmp r3, #0x5
	strb r2, [r1, r0]
	add r5, r5, #0x1
	add r4, r4, #0x1
	blt _02096A5C
	ldrb r2, [sp, #0x5]
	mov r0, #0x0
	ldr r3, [sp, #0x0]
	and r2, r2, #0x7
	strb r0, [sp, #0x7]
	strb r0, [sp, #0x6]
	strb r2, [sp, #0x5]
	ldr r2, [sp, #0x4]
	mov r4, r3, lsl #0x1
	mov r2, r2, lsl #0x1
	orr r2, r2, r3, lsr #0x1f
	str r2, [sp, #0x4]
	ldrb r2, [sp, #0x5]
	str r4, [sp, #0x0]
	ldrb r3, [sp, #0x0]
	mov r2, r2, asr #0x3
	and r2, r2, #0x1
	orr r2, r3, r2
	strb r2, [sp, #0x0]
_02096AC8:
	ldrb r2, [r1, #0x0]
	add r0, r0, #0x1
	cmp r0, #0x6
	eor r2, r2, #0x67
	strb r2, [r1], #0x1
	blt _02096AC8
	ldrb r0, [sp, #0x5]
	mov r1, #0x0
	strb r1, [sp, #0x7]
	and r0, r0, #0x7
	strb r1, [sp, #0x6]
	strb r0, [sp, #0x5]
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,pc}
	.balign 4
_02096B08: .word 0x0000FFFF
_02096B0C: .word UNK_020FF580
_02096B10: .word UNK_020FF578

	.extern _SDK_NintendoDWC

	arm_func_start FUN_02096B14
FUN_02096B14: ; 0x02096B14
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldr r0, _02096B74 ; =_SDK_NintendoDWC
	mov r4, #0x0
	bl OSi_ReferSymbol
	mov r0, r6
	bl FUN_02096190
	mov r5, r0
	bl FUN_020964C8
	cmp r0, #0x0
	beq _02096B4C
	mov r0, r6
	bl FUN_02096760
	mov r4, #0x1
_02096B4C:
	cmp r5, #0x0
	bge _02096B64
	cmp r4, #0x0
	movne r0, #0x2
	moveq r0, #0x3
	ldmia sp!, {r4-r6,pc}
_02096B64:
	cmp r4, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	ldmia sp!, {r4-r6,pc}
	.balign 4
_02096B74: .word _SDK_NintendoDWC

	; Nintendo Wifi (?)

	arm_func_start FUN_02096B78
FUN_02096B78: ; 0x02096B78
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r7, r0
	bl FUN_020974C8
	mov r5, r0
	mov r0, r4
	bl FUN_020974C8
	cmp r5, r0
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r7,pc}
	cmp r5, #0x3
	bne _02096BD8
	mov r0, r7
	bl FUN_02097544
	mov r5, r0
	mov r0, r4
	bl FUN_02097544
	cmp r5, r0
	moveq r0, #0x1
	add sp, sp, #0x4
	movne r0, #0x0
	ldmia sp!, {r4-r7,pc}
_02096BD8:
	cmp r5, #0x1
	bne _02096C34
	mov r0, r7
	bl FUN_02097568
	mov r5, r0
	mov r6, r1
	mov r0, r4
	bl FUN_02097568
	cmp r6, r1
	cmpeq r5, r0
	bne _02096C28
	mov r0, r7
	bl FUN_02097560
	mov r5, r0
	mov r0, r4
	bl FUN_02097560
	cmp r5, r0
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r7,pc}
_02096C28:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_02096C34:
	cmp r5, #0x2
	bne _02096C6C
	mov r0, r7
	bl FUN_0209754C
	mov r5, r0
	mov r6, r1
	mov r0, r4
	bl FUN_0209754C
	cmp r6, r1
	cmpeq r5, r0
	moveq r0, #0x1
	add sp, sp, #0x4
	movne r0, #0x0
	ldmia sp!, {r4-r7,pc}
_02096C6C:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_02096C78
FUN_02096C78: ; 0x02096C78
	ldr ip, _02096C8C ; =FUN_02097218
	mov r3, r0
	mov r0, r1
	ldr r1, [r3, #0x24]
	bx r12
	.balign 4
_02096C8C: .word FUN_02097218

	arm_func_start FUN_02096C90
FUN_02096C90: ; 0x02096C90
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r5, r0
	mov r1, #0x0
	mov r2, #0xc
	bl MI_CpuFill8
	mov r0, r5
	mov r1, r4
	bl FUN_020974F4
	mov r0, r5
	mov r1, #0x3
	bl FUN_02097440
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_02096CCC
FUN_02096CCC: ; 0x02096CCC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r5, r0
	mov r0, r4
	mov r1, #0x0
	mov r2, #0xc
	bl MI_CpuFill8
	mov r0, r5
	bl FUN_0209702C
	cmp r0, #0x0
	addeq r0, r5, #0x4
	ldmeqia r0, {r0-r2}
	addeq sp, sp, #0x4
	stmeqia r4, {r0-r2}
	ldmeqia sp!, {r4-r5,pc}
	ldr r1, [r5, #0x1c]
	mov r0, r4
	bl FUN_020974F4
	mov r0, r4
	mov r1, #0x3
	bl FUN_02097440
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_02096D2C
FUN_02096D2C: ; 0x02096D2C
	stmdb sp!, {r4-r6,lr}
	mov r5, r1
	mov r4, r2
	mov r6, r0
	mov r1, #0x0
	mov r2, #0xc
	bl MI_CpuFill8
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_020974FC
	mov r0, r6
	mov r1, #0x2
	bl FUN_02097440
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_02096D68
FUN_02096D68: ; 0x02096D68
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r3, r0
	ldr r0, [r3, #0x1c]
	mov r2, #0x0
	mov r1, r2
	cmp r0, #0x0
	beq _02096D94
	ldr r1, [r3, #0x24]
	bl FUN_020973D0
	mov r2, r0
_02096D94:
	mov r0, r2
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_02096DA0
FUN_02096DA0: ; 0x02096DA0
	stmdb sp!, {r4-r6,lr}
	mov r4, r1
	mov r6, r0
	mov r0, r4
	bl FUN_020974C8
	cmp r0, #0x1
	beq _02096E14
	cmp r0, #0x2
	beq _02096DD0
	cmp r0, #0x3
	beq _02096E08
	b _02096E1C
_02096DD0:
	mov r0, r4
	bl FUN_0209754C
	ldr r2, [r6, #0x24]
	mov r4, r0
	mov r5, r1
	bl FUN_02097344
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r2, [r6, #0x24]
	mov r0, r4
	mov r1, r5
	bl FUN_02097324
	ldmia sp!, {r4-r6,pc}
_02096E08:
	mov r0, r4
	bl FUN_02097544
	ldmia sp!, {r4-r6,pc}
_02096E14:
	mvn r0, #0x0
	ldmia sp!, {r4-r6,pc}
_02096E1C:
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_02096E24
FUN_02096E24: ; 0x02096E24
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020974C8
	cmp r0, #0x2
	movne r0, #0x0
	movne r1, r0
	ldmneia sp!, {r4,pc}
	mov r0, r4
	bl FUN_0209754C
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02096E4C
FUN_02096E4C: ; 0x02096E4C
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x400
	mov r4, r0
	ldr r1, [r4, #0x20]
	add r0, sp, #0x0
	bic r2, r1, #0x1
	ldr r1, _02096E8C ; =0xEDB88320
	str r2, [r4, #0x20]
	bl MATHi_CRC32InitTableRev
	add r0, sp, #0x0
	mov r1, r4
	mov r2, #0x3c
	bl MATH_CalcCRC32
	str r0, [r4, #0x3c]
	add sp, sp, #0x400
	ldmia sp!, {r4,pc}
	.balign 4
_02096E8C: .word 0xEDB88320

	arm_func_start thunk_FUN_02096e4c
thunk_FUN_02096e4c: ; 0x02096E90
	ldr ip, _02096E98 ; =FUN_02096E4C
	bx r12
	.balign 4
_02096E98: .word FUN_02096E4C

	arm_func_start FUN_02096E9C
FUN_02096E9C: ; 0x02096E9C
	ldr r0, [r0, #0x20]
	and r0, r0, #0x1
	cmp r0, #0x1
	moveq r0, #0x1
	movne r0, #0x0
	bx lr

	arm_func_start FUN_02096EB4
FUN_02096EB4: ; 0x02096EB4
	ldr ip, _02096EBC ; =FUN_02096E9C
	bx r12
	.balign 4
_02096EBC: .word FUN_02096E9C

	arm_func_start FUN_02096EC0
FUN_02096EC0: ; 0x02096EC0
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x400
	mov r4, r0
	add r3, r4, #0x10
	mov r12, r2
	ldmia r1, {r0-r2}
	stmia r3, {r0-r2}
	ldr r1, _02096F14 ; =0xEDB88320
	add r0, sp, #0x0
	str r12, [r4, #0x1c]
	bl MATHi_CRC32InitTableRev
	add r0, sp, #0x0
	mov r1, r4
	mov r2, #0x3c
	bl MATH_CalcCRC32
	str r0, [r4, #0x3c]
	ldr r0, [r4, #0x20]
	orr r0, r0, #0x1
	str r0, [r4, #0x20]
	add sp, sp, #0x400
	ldmia sp!, {r4,pc}
	.balign 4
_02096F14: .word 0xEDB88320

	arm_func_start FUN_02096F18
FUN_02096F18: ; 0x02096F18
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x18
	mov r4, r0
	add r0, r4, #0x10
	bl FUN_020974C8
	cmp r0, #0x0
	addeq sp, sp, #0x18
	moveq r0, #0x1
	ldmeqia sp!, {r4,pc}
	add r0, sp, #0x0
	bl FUN_02096518
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	addeq sp, sp, #0x18
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	add r0, r4, #0x10
	bl FUN_02097568
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x0]
	cmp r2, r1
	cmpeq r3, r0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x18
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02096F80
FUN_02096F80: ; 0x02096F80
	stmdb sp!, {r4,lr}
	mov r4, r0
	add r0, r4, #0x10
	bl FUN_0209703C
	cmp r0, #0x0
	beq _02096FA8
	ldr r0, [r4, #0x1c]
	cmp r0, #0x0
	movgt r0, #0x1
	ldmgtia sp!, {r4,pc}
_02096FA8:
	mov r0, #0x0
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02096FB0
FUN_02096FB0: ; 0x02096FB0
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x400
	ldr r1, _02096FF0 ; =0xEDB88320
	mov r4, r0
	add r0, sp, #0x0
	bl MATHi_CRC32InitTableRev
	add r0, sp, #0x0
	mov r1, r4
	mov r2, #0x3c
	bl MATH_CalcCRC32
	ldr r1, [r4, #0x3c]
	cmp r0, r1
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x400
	ldmia sp!, {r4,pc}
	.balign 4
_02096FF0: .word 0xEDB88320

	arm_func_start thunk_FUN_02097190
thunk_FUN_02097190: ; 0x02096FF4
	ldr ip, _02096FFC ; =FUN_02097190
	bx r12
	.balign 4
_02096FFC: .word FUN_02097190

	arm_func_start FUN_02097000
FUN_02097000: ; 0x02097000
	ldr ip, _02097008 ; =FUN_0209700C
	bx r12
	.balign 4
_02097008: .word FUN_0209700C

	arm_func_start FUN_0209700C
FUN_0209700C: ; 0x0209700C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020974C8
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_0209702C
FUN_0209702C:
	ldr ip, _02097038 ; =FUN_0209703C
	add r0, r0, #0x10
	bx r12
	.balign 4
_02097038: .word FUN_0209703C

	arm_func_start FUN_0209703C
FUN_0209703C:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020974C8
	cmp r0, #0x1
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_0209705C
FUN_0209705C: ; 0x0209705C
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x18
	mov r4, r0
	add r0, sp, #0x0
	bl FUN_02096518
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	beq _020970A4
	mov r0, r4
	bl FUN_02097568
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x0]
	cmp r2, r1
	cmpeq r3, r0
	moveq r0, #0x1
	add sp, sp, #0x18
	movne r0, #0x0
	ldmia sp!, {r4,pc}
_020970A4:
	mov r0, r4
	bl FUN_02097568
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x8]
	cmp r2, r1
	cmpeq r3, r0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x18
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020970CC
FUN_020970CC: ; 0x020970CC
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x38
	mov r6, r0
	add r0, sp, #0x14
	bl OS_GetLowEntropyData
	mov r3, #0x1
	add r2, sp, #0x14
_020970E8:
	add r0, r2, r3, lsl #0x2
	ldr r1, [r2, r3, lsl #0x2]
	ldr r0, [r0, #-0x4]
	eor r0, r1, r0
	str r0, [r2, r3, lsl #0x2]
	add r3, r3, #0x1
	cmp r3, #0x8
	blo _020970E8
	add r0, sp, #0x0
	ldr r5, [sp, #0x30]
	mov r4, #0x0
	bl FUN_02096518
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	beq _02097138
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	mov r0, r6
	bl FUN_02097510
	b _02097148
_02097138:
	ldr r1, [sp, #0x8]
	ldr r2, [sp, #0xc]
	mov r0, r6
	bl FUN_02097510
_02097148:
	ldr r0, _02097184 ; =0x6C078965
	ldr r1, _02097188 ; =0x5D588B65
	umull r3, r2, r5, r0
	mla r2, r5, r1, r2
	ldr r1, _0209718C ; =0x00269EC3
	mla r2, r4, r0, r2
	adds r0, r3, r1
	mov r0, r6
	adc r1, r2, #0x0
	bl FUN_02097508
	mov r0, r6
	mov r1, #0x1
	bl FUN_02097440
	add sp, sp, #0x38
	ldmia sp!, {r4-r6,pc}
	.balign 4
_02097184: .word 0x6C078965
_02097188: .word 0x5D588B65
_0209718C: .word 0x00269EC3

	arm_func_start FUN_02097190
FUN_02097190: ; 0x02097190
	stmdb sp!, {r4-r5,lr}
	ldr ip, _02097210 ; =0x00000404
	sub sp, sp, r12
	mov r4, r1
	mov r1, #0x0
	mov r2, #0x40
	mov r5, r0
	bl MI_CpuFill8
	mov r0, #0x40
	str r0, [r5, #0x0]
	mov r0, #0x0
	str r0, [r5, #0x1c]
	add r0, r5, #0x4
	str r4, [r5, #0x24]
	bl FUN_020970CC
	add r0, r5, #0x10
	mov r1, #0x0
	bl FUN_02097440
	ldr r1, _02097214 ; =0xEDB88320
	add r0, sp, #0x0
	bl MATHi_CRC32InitTableRev
	add r0, sp, #0x0
	mov r1, r5
	mov r2, #0x3c
	bl MATH_CalcCRC32
	str r0, [r5, #0x3c]
	ldr r0, [r5, #0x20]
	orr r0, r0, #0x1
	str r0, [r5, #0x20]
	ldr ip, _02097210 ; =0x00000404
	add sp, sp, r12
	ldmia sp!, {r4-r5,pc}
	.balign 4
_02097210: .word 0x00000404
_02097214: .word 0xEDB88320

	arm_func_start FUN_02097218
FUN_02097218: ; 0x02097218
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x40
	mov r6, r0
	mov r4, r1
	mov r5, r2
	bl FUN_02097568
	add r3, sp, #0x14
	mov r2, #0x2b
	bl FUN_020972A8
	mov r0, r6
	bl FUN_02097560
	mov r1, #0x0
	mov r2, #0x20
	add r3, sp, #0x29
	bl FUN_020972A8
	mov r1, r4, lsr #0x18
	and r1, r1, #0xff
	str r1, [sp, #0x0]
	mov r1, r4, lsr #0x10
	and r1, r1, #0xff
	str r1, [sp, #0x4]
	mov r1, r4, lsr #0x8
	and r1, r1, #0xff
	str r1, [sp, #0x8]
	and r1, r4, #0xff
	str r1, [sp, #0xc]
	add r2, sp, #0x29
	str r2, [sp, #0x10]
	ldr r2, _020972A4 ; =UNK_0210618C
	mov r0, r5
	mov r1, #0x15
	add r3, sp, #0x14
	bl OS_SNPrintf
	add sp, sp, #0x40
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020972A4: .word UNK_0210618C

	arm_func_start FUN_020972A8
FUN_020972A8: ; 0x020972A8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr lr, _0209731C ; =0x66666667
	add r4, r2, #0x4
	smull r12, r2, lr, r4
	mov r2, r2, asr #0x1
	mov r12, r4, lsr #0x1f
	add r2, r12, r2
	cmp r2, #0x0
	ldr r6, _02097320 ; =UNK_0210619C
	mov r7, #0x0
	ble _0209730C
	add r4, r3, r2
	sub r4, r4, #0x1
	mov r12, #0x1f
_020972E4:
	and r5, r0, r12
	ldrsb r5, [r6, r5]
	mov r0, r0, lsr #0x5
	mov lr, r1, lsr #0x5
	strb r5, [r4, -r7]
	add r7, r7, #0x1
	orr r0, r0, r1, lsl #0x1b
	mov r1, lr
	cmp r7, r2
	blt _020972E4
_0209730C:
	mov r0, #0x0
	strb r0, [r3, r2]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_0209731C: .word 0x66666667
_02097320: .word UNK_0210619C

	arm_func_start FUN_02097324
FUN_02097324: ; 0x02097324
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_02097344
	cmp r0, #0x0
	mvnne r0, #0x0
	andne r0, r4, r0
	moveq r0, #0x0
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02097344
FUN_02097344:
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x108
	mov r4, r1
	and r3, r4, #0x0
	mov r1, #0x0
	and r12, r0, #0x80000000
	cmp r3, r1
	cmpeq r12, r1
	addne sp, sp, #0x108
	movne r0, r1
	ldmneia sp!, {r4,pc}
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	mov r1, #0x7
	str r2, [sp, #0x4]
	bl MATHi_CRC8InitTable
	add r0, sp, #0x8
	add r1, sp, #0x0
	mov r2, #0x8
	bl MATH_CalcCRC8
	and r2, r0, #0x7f
	mov r1, r2, asr #0x1f
	mov r0, #0x0
	cmp r1, r0
	cmpeq r2, r4
	moveq r0, #0x1
	add sp, sp, #0x108
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020973B4
FUN_020973B4: ; 0x020973B4
	ldr ip, _020973CC ; =FUN_02097344
	mov r3, r0
	mov r0, r1
	mov r1, r2
	ldr r2, [r3, #0x24]
	bx r12
	.balign 4
_020973CC: .word FUN_02097344

	arm_func_start FUN_020973D0
FUN_020973D0: ; 0x020973D0
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x108
	mov r4, r0
	str r1, [sp, #0x4]
	add r0, sp, #0x8
	mov r1, #0x7
	str r4, [sp, #0x0]
	bl MATHi_CRC8InitTable
	add r0, sp, #0x8
	add r1, sp, #0x0
	mov r2, #0x8
	bl MATH_CalcCRC8
	and r0, r0, #0x7f
	orr r1, r0, #0x0
	orr r0, r4, #0x0
	add sp, sp, #0x108
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02097414
FUN_02097414: ; 0x02097414
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020974C8
	cmp r0, #0x3
	ldmneia sp!, {r4,pc}
	mov r0, r4
	bl FUN_020974E0
	orr r1, r0, #0x4
	mov r0, r4
	bl FUN_0209746C
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02097440
FUN_02097440: ; 0x02097440
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl FUN_020974E0
	bic r1, r0, #0x3
	mov r0, r5
	orr r1, r1, r4
	bl FUN_0209746C
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_0209746C
FUN_0209746C: ; 0x0209746C
	ldr ip, _0209747C ; =FUN_02097588
	ldr r3, _02097480 ; =0x001FFFFF
	mov r2, #0xb
	bx r12
	.balign 4
_0209747C: .word FUN_02097588
_02097480: .word 0x001FFFFF

	arm_func_start FUN_02097484
FUN_02097484: ; 0x02097484
	ldr ip, _0209748C ; =FUN_020974C8
	bx r12
	.balign 4
_0209748C: .word FUN_020974C8

	arm_func_start FUN_02097490
FUN_02097490: ; 0x02097490
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020974C8
	cmp r0, #0x3
	bne _020974C0
	mov r0, r4
	bl FUN_020974E0
	and r0, r0, #0x4
	cmp r0, #0x4
	moveq r0, #0x1
	movne r0, #0x0
	ldmia sp!, {r4,pc}
_020974C0:
	mov r0, #0x0
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020974C8
FUN_020974C8: ; 0x020974C8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020974E0
	and r0, r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020974E0
FUN_020974E0: ; 0x020974E0
	ldr r1, [r0, #0x0]
	ldr r0, _020974F0 ; =0x001FFFFF
	and r0, r0, r1, lsr #0xb
	bx lr
	.balign 4
_020974F0: .word 0x001FFFFF

	arm_func_start FUN_020974F4
FUN_020974F4: ; 0x020974F4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start FUN_020974FC
FUN_020974FC: ; 0x020974FC
	str r1, [r0, #0x4]
	str r2, [r0, #0x8]
	bx lr

	arm_func_start FUN_02097508
FUN_02097508: ; 0x02097508
	str r1, [r0, #0x8]
	bx lr

	arm_func_start FUN_02097510
FUN_02097510: ; 0x02097510
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r12, #0x0
	mov r4, r1
	mov r1, r2
	ldr r3, _02097540 ; =0x000007FF
	mov r2, r12
	mov r5, r0
	bl FUN_02097588
	str r4, [r5, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_02097540: .word 0x000007FF

	arm_func_start FUN_02097544
FUN_02097544:
	ldr r0, [r0, #0x4]
	bx lr

	arm_func_start FUN_0209754C
FUN_0209754C: ; 0x0209754C
	ldr r1, [r0, #0x8]
	ldr r0, [r0, #0x4]
	orr r1, r1, #0x0
	orr r0, r0, #0x0
	bx lr

	arm_func_start FUN_02097560
FUN_02097560:
	ldr r0, [r0, #0x8]
	bx lr

	arm_func_start FUN_02097568
FUN_02097568: ; 0x02097568
	ldr r2, [r0, #0x0]
	ldr r1, _02097584 ; =0x000007FF
	ldr r0, [r0, #0x4]
	and r1, r2, r1
	orr r1, r1, #0x0
	orr r0, r0, #0x0
	bx lr
	.balign 4
_02097584: .word 0x000007FF

	arm_func_start FUN_02097588
FUN_02097588: ; 0x02097588
	mvn r12, r3
	ands r12, r1, r12
	movne r0, #0x0
	bxne lr
	mvn r3, r3, lsl r2
	ldr r12, [r0, #0x0]
	and r3, r12, r3
	orr r1, r3, r1, lsl r2
	str r1, [r0, #0x0]
	mov r0, #0x1
	bx lr

	arm_func_start FUN_020975B4
FUN_020975B4: ; 0x020975B4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020A8850
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020975D8
FUN_020975D8: ; 0x020975D8
	ldr r0, _020975EC ; =UNK_021C8CCC
	ldr r1, [r0, #0x0]
	orr r1, r1, #0x2
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020975EC: .word UNK_021C8CCC

	arm_func_start FUN_020975F0
FUN_020975F0: ; 0x020975F0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _02097654 ; =UNK_021C8CC0
	ldr r0, _02097658 ; =UNK_021C8CCC
	ldr lr, [r1, #0x0]
	ldr r3, [r0, #0x0]
	ldr r12, [lr, #0x4]
	ldr r2, _0209765C ; =UNK_021C8F04
	ldr r1, _02097660 ; =UNK_021C8ED0
	str r12, [r2, #0x0]
	ldr r12, [lr, #0x8]
	ldr r2, _02097664 ; =UNK_021C8EE0
	str r12, [r1, #0x0]
	ldr r12, [lr, #0xc]
	ldr r1, _02097668 ; =UNK_021C8F1C
	str r12, [r2, #0x0]
	ldr r12, [lr, #0x10]
	orr r2, r3, #0x2
	str r12, [r1, #0x0]
	ldr r3, [lr, #0x14]
	str r3, [r1, #0x4]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02097654: .word UNK_021C8CC0
_02097658: .word UNK_021C8CCC
_0209765C: .word UNK_021C8F04
_02097660: .word UNK_021C8ED0
_02097664: .word UNK_021C8EE0
_02097668: .word UNK_021C8F1C

	arm_func_start FUN_0209766C
FUN_0209766C: ; 0x0209766C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020977C0 ; =UNK_021C8CC0
	ldr r5, _020977C4 ; =UNK_021C8CD4
	ldr r4, [r0, #0x0]
	mov r0, r5
	mov r1, #0x0
	mov r2, #0x30
	bl MI_CpuFill8
	ldr r0, _020977C8 ; =UNK_021C8CC4
	ldr r2, [r4, #0x18]
	mov r1, r5
	str r2, [r1, #0x4]
	ldr r12, [r4, #0x1c]
	mov r2, #0x0
	ldr r3, _020977CC ; =FUN_020975B4
	ldr r0, [r0, #0x0]
	str r12, [r1, #0x8]
	str r3, [r1, #0x10]
	str r2, [r1, #0x14]
	str r2, [r1, #0x18]
	str r0, [r1, #0x2c]
	ldr r0, [r4, #0x24]
	cmp r0, #0x0
	strne r0, [r5, #0x20]
	moveq r0, #0x4000
	streq r0, [r5, #0x20]
	ldr r0, [r4, #0x28]
	cmp r0, #0x0
	strne r0, [r5, #0x1c]
	bne _02097700
	ldr r1, _020977C0 ; =UNK_021C8CC0
	ldr r0, [r5, #0x20]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x18]
	blx r1
	str r0, [r5, #0x1c]
_02097700:
	ldr r0, [r4, #0x30]
	ldr r12, [r4, #0x34]
	cmp r0, #0x0
	moveq r0, #0x240
	cmp r12, #0x0
	sub r2, r0, #0x28
	moveq r12, #0x10c0
	add r0, r12, r12, lsr #0x1f
	str r2, [r5, #0x24]
	ldr r1, _020977D0 ; =UNK_021061DC
	mov r3, r0, asr #0x1
	ldr r0, _020977D4 ; =UNK_021C8F04
	mov r2, #0x0
	strh r12, [r1, #0x2]
	strh r3, [r1, #0x4]
	str r2, [r0, #0x0]
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02097774
	ldr r0, _020977D8 ; =UNK_021C8CCC
	mov r1, #0x1
	str r1, [r0, #0x0]
	ldr r1, _020977DC ; =FUN_020975D8
	str r2, [r5, #0x0]
	ldr r0, _020977E0 ; =UNK_021C8CC8
	str r1, [r5, #0xc]
	ldr r0, [r0, #0x0]
	str r0, [r5, #0x28]
	b _0209778C
_02097774:
	ldr r0, _020977D8 ; =UNK_021C8CCC
	mov r1, #0x1
	str r2, [r0, #0x0]
	ldr r0, _020977E4 ; =FUN_020975F0
	str r1, [r5, #0x0]
	str r0, [r5, #0xc]
_0209778C:
	ldr r0, [r4, #0x2c]
	cmp r0, #0x0
	moveq r0, #0xb
	bl FUN_0209FC88
	ldr r0, _020977E8 ; =FUN_0209F65C
	bl FUN_020A87BC
	ldr r0, _020977EC ; =FUN_020996C0
	bl FUN_0209FD24
	mov r0, r5
	bl FUN_0209FD94
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020977C0: .word UNK_021C8CC0
_020977C4: .word UNK_021C8CD4
_020977C8: .word UNK_021C8CC4
_020977CC: .word FUN_020975B4
_020977D0: .word UNK_021061DC
_020977D4: .word UNK_021C8F04
_020977D8: .word UNK_021C8CCC
_020977DC: .word FUN_020975D8
_020977E0: .word UNK_021C8CC8
_020977E4: .word FUN_020975F0
_020977E8: .word FUN_0209F65C
_020977EC: .word FUN_020996C0

	arm_func_start FUN_020977F0
FUN_020977F0: ; 0x020977F0
	stmdb sp!, {r4,lr}
	ldr r0, _02097828 ; =UNK_021C8CC0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x20]
	bl FUN_02097B78
	movs r4, r0
	bmi _0209781C
	ldr r0, _0209782C ; =UNK_021061F4
	bl FUN_02097F70
	ldr r1, _02097830 ; =UNK_021C8CD0
	str r0, [r1, #0x0]
_0209781C:
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02097828: .word UNK_021C8CC0
_0209782C: .word UNK_021061F4
_02097830: .word UNK_021C8CD0

	.extern _SDK_NintendoWiFi

	arm_func_start FUN_02097834
FUN_02097834: ; 0x02097834
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, _02097870 ; =_SDK_NintendoWiFi
	bl OSi_ReferSymbol
	ldr r0, _02097874 ; =UNK_021C8CC0
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	str r4, [r0, #0x0]
	bl FUN_0209766C
	bl FUN_020977F0
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02097870: .word _SDK_NintendoWiFi
_02097874: .word UNK_021C8CC0

	; Ubiquitous CPS (?)

	arm_func_start FUN_02097878
FUN_02097878: ; 0x02097878
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	add r6, sp, #0x0
	mov r4, #0x0
	mov r5, #0x1
_02097890:
	mov r0, r9
	mov r1, r6
	mov r2, r5
	bl OS_ReadMessage
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r1, [r0, #0x0]
	blx r1
	mov r7, r0
	bl OS_DisableInterrupts
	mov r8, r0
	bl OS_DisableScheduler
	mov r0, r9
	mov r1, r4
	mov r2, r4
	bl OS_ReceiveMessage
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	strne r7, [r0, #0x6c]
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _02097908
	mov r1, r7
	mov r2, r4
	bl OS_SendMessage
_02097908:
	ldr r0, [sp, #0x0]
	bl FUN_02097A64
	bl OS_EnableScheduler
	mov r0, r8
	bl OS_RestoreInterrupts
	b _02097890
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_0209792C
FUN_0209792C: ; 0x0209792C
	stmdb sp!, {r4,lr}
	mov r4, r1
	bl FUN_02097A50
	mov r1, r4
	bl FUN_02097968
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02097948
FUN_02097948:
	ldr ip, _02097954 ; =FUN_02097968
	ldr r0, [r0, #0x68]
	bx r12
	.balign 4
_02097954: .word FUN_02097968

	arm_func_start FUN_02097958
FUN_02097958: ; 0x02097958
	ldr ip, _02097964 ; =FUN_02097968
	ldr r0, [r0, #0x64]
	bx r12
	.balign 4
_02097964: .word FUN_02097968

	arm_func_start FUN_02097968
FUN_02097968: ; 0x02097968
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x2c
	mov r4, r1
	ldrsb r2, [r4, #0xd]
	mov r5, r0
	cmp r2, #0x1
	bne _020979BC
	add r0, sp, #0x8
	add r1, sp, #0x4
	mov r2, #0x1
	bl OS_InitMessageQueue
	add r2, sp, #0x8
	mov r0, r5
	mov r1, r4
	str r2, [r4, #0x8]
	bl FUN_020979F8
	add r0, sp, #0x8
	add r1, sp, #0x0
	mov r2, #0x1
	bl OS_ReceiveMessage
	b _020979CC
_020979BC:
	mov r2, #0x0
	str r2, [r4, #0x8]
	bl FUN_020979F8
	str r0, [sp, #0x0]
_020979CC:
	ldr r0, [sp, #0x0]
	add sp, sp, #0x2c
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020979DC
FUN_020979DC:
	stmdb sp!, {r4,lr}
	mov r4, r1
	bl FUN_02097A50
	mov r1, r4
	bl FUN_020979F8
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020979F8
FUN_020979F8:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r5, r1
	beq _02097A14
	ldrsb r1, [r5, #0xd]
	ands r1, r1, #0x1
	beq _02097A1C
_02097A14:
	mov r2, #0x1
	b _02097A20
_02097A1C:
	mov r2, #0x0
_02097A20:
	mov r1, r5
	bl OS_SendMessage
	movs r4, r0
	bne _02097A38
	mov r0, r5
	bl FUN_02097A64
_02097A38:
	cmp r4, #0x0
	movne r0, #0x0
	mvneq r0, #0x29
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02097A50
FUN_02097A50: ; 0x02097A50
	ldr r1, [r0, #0x64]
	cmp r1, #0x0
	ldreq r1, [r0, #0x68]
	mov r0, r1
	bx lr

	arm_func_start FUN_02097A64
FUN_02097A64:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	movs r1, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r0, _02097A94 ; =UNK_021C8D08
	mov r2, #0x0
	bl OS_SendMessage
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02097A94: .word UNK_021C8D08

	arm_func_start FUN_02097A98
FUN_02097A98: ; 0x02097A98
	stmdb sp!, {r4-r6,lr}
	mov r4, r2
	mov r6, r0
	mov r0, r4
	mov r5, r1
	bl FUN_02097AE0
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	str r6, [r0, #0x0]
	str r5, [r0, #0x4]
	mov r1, #0x0
	str r1, [r0, #0x8]
	ldrsb r1, [r5, #0x73]
	strb r1, [r0, #0xc]
	strb r4, [r0, #0xd]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_02097AE0
FUN_02097AE0:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r0
	ldr r0, _02097B10 ; =UNK_021C8D08
	add r1, sp, #0x0
	bl OS_ReceiveMessage
	cmp r0, #0x0
	ldrne r0, [sp, #0x0]
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02097B10: .word UNK_021C8D08

	arm_func_start FUN_02097B14
FUN_02097B14: ; 0x02097B14
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _02097B6C ; =UNK_021C8D08
	ldr r1, [r0, #0x1c]
	ldr r0, [r0, #0x14]
	cmp r1, r0
	addlt sp, sp, #0x4
	mvnlt r0, #0x0
	ldmltia sp!, {lr}
	bxlt lr
	ldr r0, _02097B70 ; =UNK_021C8CC0
	ldr r1, _02097B74 ; =UNK_021C8D04
	ldr r2, [r0, #0x0]
	ldr r0, [r1, #0x0]
	ldr r1, [r2, #0x1c]
	blx r1
	ldr r1, _02097B74 ; =UNK_021C8D04
	mov r0, #0x0
	str r0, [r1, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02097B6C: .word UNK_021C8D08
_02097B70: .word UNK_021C8CC0
_02097B74: .word UNK_021C8D04

	arm_func_start FUN_02097B78
FUN_02097B78: ; 0x02097B78
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	mov r0, #0x2c
	mul r1, r4, r0
	ldr r0, _02097C08 ; =UNK_021C8CC0
	mov r2, r4, lsl #0x2
	add r2, r2, #0x3
	ldr r0, [r0, #0x0]
	add r1, r1, #0x3
	bic r5, r2, #0x3
	bic r2, r1, #0x3
	ldr r1, [r0, #0x18]
	add r0, r2, r5
	blx r1
	movs r6, r0
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, _02097C0C ; =UNK_021C8D08
	mov r1, r6
	mov r2, r4
	bl OS_InitMessageQueue
	cmp r4, #0x0
	add r5, r6, r5
	ble _02097BF4
_02097BDC:
	mov r0, r5
	bl FUN_02097A64
	sub r4, r4, #0x1
	cmp r4, #0x0
	add r5, r5, #0x2c
	bgt _02097BDC
_02097BF4:
	ldr r1, _02097C10 ; =UNK_021C8D04
	mov r0, #0x0
	str r6, [r1, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_02097C08: .word UNK_021C8CC0
_02097C0C: .word UNK_021C8D08
_02097C10: .word UNK_021C8D04

	arm_func_start FUN_02097C14
FUN_02097C14: ; 0x02097C14
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r5, r2
	mov r7, r0
	mov r0, r5
	mov r6, r1
	bl FUN_02097DC4
	add r4, r7, r0
	ldrb r2, [r5, #0x3]
	mov r0, r6
	mov r1, r7
	bl OS_InitMessageQueue
	add r0, r6, #0xe0
	bl OS_InitMutex
	ldrh r2, [r5, #0x0]
	add r0, r6, #0x20
	ldr r1, _02097C88 ; =FUN_02097878
	str r2, [sp, #0x0]
	ldrb r12, [r5, #0x2]
	mov r2, r6
	mov r3, r4
	str r12, [sp, #0x4]
	bl OS_CreateThread
	add r0, r6, #0x20
	bl OS_WakeupThreadDirect
	mov r0, r4
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02097C88: .word FUN_02097878

	arm_func_start FUN_02097C8C
FUN_02097C8C: ; 0x02097C8C
	stmdb sp!, {r4,lr}
	mov r4, r0
	cmp r2, #0x0
	moveq r0, #0x0
	str r0, [r1, #0x4]
	mov r0, r2
	str r2, [r1, #0x0]
	bl FUN_02099F6C
	add r0, r4, r0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02097CB8
FUN_02097CB8: ; 0x02097CB8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	ldrsb r1, [r6, #0x0]
	mov r7, r0
	add r4, r7, #0x80
	strb r1, [r7, #0x73]
	ldrsb r0, [r6, #0x1]
	strb r0, [r7, #0x72]
	ldrh r0, [r6, #0x2]
	cmp r0, #0x0
	beq _02097D40
	str r4, [r7, #0x64]
	ldrh r2, [r6, #0x4]
	mov r1, r4
	add r0, r4, #0x114
	strh r2, [r4, #0xfc]
	add r2, r6, #0x10
	mov r5, r4
	bl FUN_02097C14
	ldrh r2, [r6, #0x2]
	add r1, r7, #0x3c
	bl FUN_02097C8C
	ldrh r2, [r6, #0x8]
	add r1, r7, #0x50
	bl FUN_02097C8C
	ldrh r3, [r6, #0xe]
	add r1, r5, #0x100
	mov r2, #0x0
	strh r3, [r1, #0xa]
	str r2, [r5, #0x110]
	ldr r1, [r5, #0x110]
	mov r4, r0
	str r1, [r5, #0x10c]
_02097D40:
	ldrh r0, [r6, #0x6]
	cmp r0, #0x0
	ldreq r0, _02097DC0 ; =UNK_021C8CD0
	ldreq r0, [r0, #0x0]
	ldreq r0, [r0, #0x68]
	streq r0, [r7, #0x68]
	beq _02097DB0
	str r4, [r7, #0x68]
	mov r1, r4
	str r7, [r4, #0x10c]
	add r0, r4, #0x110
	add r2, r6, #0x14
	mov r5, r4
	bl FUN_02097C14
	ldrh r2, [r6, #0x6]
	add r1, r7, #0x48
	bl FUN_02097C8C
	ldrh r2, [r6, #0xa]
	add r1, r7, #0x58
	bl FUN_02097C8C
	ldrh r2, [r6, #0xc]
	add r1, r4, #0xf8
	bl FUN_02097C8C
	mov r1, #0x0
	str r1, [r5, #0x108]
	ldr r1, [r5, #0x108]
	mov r4, r0
	str r1, [r5, #0x104]
_02097DB0:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02097DC0: .word UNK_021C8CD0

	arm_func_start FUN_02097DC4
FUN_02097DC4: ; 0x02097DC4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrb r0, [r5, #0x3]
	mov r0, r0, lsl #0x2
	bl FUN_02099F6C
	mov r4, r0
	ldrh r0, [r5, #0x0]
	bl FUN_02099F6C
	add r0, r4, r0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02097DF8
FUN_02097DF8: ; 0x02097DF8
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrh r0, [r5, #0x2]
	mov r4, #0x80
	cmp r0, #0x0
	beq _02097E38
	add r4, r4, #0x114
	bl FUN_02099F6C
	add r4, r4, r0
	ldrh r0, [r5, #0x8]
	bl FUN_02099F6C
	add r4, r4, r0
	add r0, r5, #0x10
	bl FUN_02097DC4
	add r4, r4, r0
_02097E38:
	ldrh r0, [r5, #0x6]
	cmp r0, #0x0
	beq _02097E74
	add r4, r4, #0x110
	bl FUN_02099F6C
	add r4, r4, r0
	ldrh r0, [r5, #0xa]
	bl FUN_02099F6C
	add r4, r4, r0
	ldrh r0, [r5, #0xc]
	bl FUN_02099F6C
	add r4, r4, r0
	add r0, r5, #0x14
	bl FUN_02097DC4
	add r4, r4, r0
_02097E74:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02097E84
FUN_02097E84: ; 0x02097E84
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	bl FUN_02097DF8
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _02097EF4 ; =UNK_021C8CC0
	mov r5, r0
	ldr r1, [r1, #0x0]
	mov r0, r4
	ldr r1, [r1, #0x18]
	blx r1
	movs r6, r0
	beq _02097EDC
	mov r2, r4
	mov r1, #0x0
	bl MI_CpuFill8
	mov r0, r6
	mov r1, r7
	bl FUN_02097CB8
	mov r0, r6
	bl FUN_0209A094
_02097EDC:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02097EF4: .word UNK_021C8CC0

	arm_func_start FUN_02097EF8
FUN_02097EF8: ; 0x02097EF8
	stmdb sp!, {r4,lr}
	ldr r4, [r0, #0x4]
	mov r0, r4
	bl FUN_0209CC28
	ldrsb r0, [r4, #0x73]
	ldr r1, [r4, #0x68]
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _02097F58
_02097F1C:
	b _02097F30
_02097F20:
	b _02097F40
_02097F24:
	b _02097F54
_02097F28:
	b _02097F58
_02097F2C:
	b _02097F30
_02097F30:
	add r0, r1, #0x20
	bl FUN_0209CB0C
	bl FUN_0209CB44
	b _02097F58
_02097F40:
	bl FUN_0209CB44
	bl FUN_0209CBE8
	ldr r0, _02097F6C ; =FUN_02098550
	bl FUN_0209CAA8
	b _02097F58
_02097F54:
	bl FUN_0209CBE8
_02097F58:
	mov r0, #0x1
	strh r0, [r4, #0x70]
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02097F6C: .word FUN_02098550

	arm_func_start FUN_02097F70
FUN_02097F70: ; 0x02097F70
	stmdb sp!, {r4,lr}
	bl FUN_02097E84
	movs r4, r0
	mvneq r0, #0x30
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, _02097FB0 ; =FUN_02097EF8
	mov r1, r4
	mov r2, #0x1
	bl FUN_02097A98
	mov r1, r0
	mov r0, r4
	bl FUN_0209792C
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02097FB0: .word FUN_02097EF8

	arm_func_start FUN_02097FB4
FUN_02097FB4: ; 0x02097FB4
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r6, r0
	ldr r4, [r6, #0x4]
	ldr r5, [r4, #0x64]
	add r0, r5, #0xe0
	bl OS_LockMutex
	mov r1, #0x0
	ldrh r0, [r6, #0x10]
	mov r2, r1
	bl FUN_0209CB78
	bl FUN_0209CA54
	mov r2, #0x0
	add r0, sp, #0x0
	add r1, sp, #0x4
	str r2, [r5, #0xf8]
	bl FUN_0209C8E0
	ldrh r2, [sp, #0x0]
	ldr r1, [r6, #0x14]
	strh r2, [r1, #0x0]
	ldr r1, [r6, #0x18]
	str r0, [r1, #0x0]
	ldrsh r1, [r4, #0x70]
	add r0, r5, #0xe0
	orr r1, r1, #0x4
	strh r1, [r4, #0x70]
	bl OS_UnlockMutex
	mov r0, #0x0
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_02098030
FUN_02098030:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl FUN_02099FA8
	cmp r0, #0x0
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	cmp r6, #0x0
	mov r1, #0x0
	beq _0209806C
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_0209806C:
	cmp r1, #0x0
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x2
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldrsb r0, [r6, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _020980A8
	cmp r0, #0x4
	movne r1, #0x0
_020980A8:
	cmp r1, #0x0
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrsb r2, [r6, #0x72]
	cmp r2, #0x1
	mvnne r0, #0x5
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldrh r0, [r6, #0x74]
	cmp r0, #0x0
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, _0209811C ; =FUN_02097FB4
	mov r1, r6
	bl FUN_02097A98
	mov r1, r0
	ldrh r2, [r6, #0x74]
	mov r0, r6
	strh r2, [r1, #0x10]
	str r5, [r1, #0x14]
	str r4, [r1, #0x18]
	ldrsh r2, [r6, #0x70]
	orr r2, r2, #0x2
	strh r2, [r6, #0x70]
	bl FUN_02097958
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209811C: .word FUN_02097FB4

	arm_func_start FUN_02098120
FUN_02098120:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl FUN_02099FA8
	cmp r0, #0x0
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	cmp r6, #0x0
	mov r1, #0x0
	beq _02098164
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_02098164:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x2
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrsb r0, [r6, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _020981A8
	cmp r0, #0x4
	movne r1, #0x0
_020981A8:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrsb r0, [r6, #0x72]
	cmp r0, #0x1
	addne sp, sp, #0x4
	mvnne r0, #0x5
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldr r0, _02098228 ; =UNK_021061DC
	bl FUN_02097F70
	movs r7, r0
	addmi sp, sp, #0x4
	ldmmiia sp!, {r4-r7,lr}
	bxmi lr
	ldrh r1, [r6, #0x74]
	bl FUN_020984B4
	cmp r0, #0x0
	addlt sp, sp, #0x4
	ldmltia sp!, {r4-r7,lr}
	bxlt lr
	mov r0, r7
	mov r1, r5
	mov r2, r4
	bl FUN_02098030
	cmp r0, #0x0
	movge r0, r7
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02098228: .word UNK_021061DC

	arm_func_start FUN_0209822C
FUN_0209822C: ; 0x0209822C
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_02099FA8
	cmp r0, #0x0
	mvnne r0, #0x1b
	ldmneia sp!, {r4,lr}
	bxne lr
	cmp r4, #0x0
	mov r1, #0x0
	beq _02098260
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_02098260:
	cmp r1, #0x0
	mvneq r0, #0x26
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x2
	mvnne r0, #0x1b
	ldmneia sp!, {r4,lr}
	bxne lr
	ldrsb r0, [r4, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _0209829C
	cmp r0, #0x4
	movne r1, #0x0
_0209829C:
	cmp r1, #0x0
	mvneq r0, #0x1b
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrsb r0, [r4, #0x72]
	cmp r0, #0x1
	moveq r0, #0x0
	mvnne r0, #0x5
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020982C4
FUN_020982C4: ; 0x020982C4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldr r4, [r7, #0x4]
	mov r5, #0x0
	ldr r6, [r4, #0x64]
	add r0, r6, #0xe0
	bl OS_LockMutex
	ldrh r0, [r7, #0x10]
	ldrh r1, [r7, #0x12]
	ldr r2, [r7, #0x14]
	bl FUN_0209CB78
	mov r0, r5
	str r0, [r6, #0xf8]
	ldrsb r0, [r7, #0xc]
	cmp r0, #0x0
	beq _02098310
	cmp r0, #0x4
	bne _02098318
_02098310:
	bl FUN_0209C934
	mov r5, r0
_02098318:
	add r0, r6, #0xe0
	bl OS_UnlockMutex
	cmp r5, #0x0
	ldrnesh r1, [r4, #0x70]
	mvnne r0, #0x4b
	moveq r0, #0x0
	orrne r1, r1, #0x40
	strneh r1, [r4, #0x70]
	ldreqsh r1, [r4, #0x70]
	orreq r1, r1, #0x4
	streqh r1, [r4, #0x70]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_02098350
FUN_02098350: ; 0x02098350
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldrsb r2, [r4, #0x72]
	ldr r0, _020983AC ; =FUN_020982C4
	mov r1, r4
	bl FUN_02097A98
	movs r1, r0
	mvneq r0, #0x20
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrh r2, [r4, #0x74]
	mov r0, r4
	strh r2, [r1, #0x10]
	ldrh r2, [r4, #0x76]
	strh r2, [r1, #0x12]
	ldr r2, [r4, #0x78]
	str r2, [r1, #0x14]
	ldrsh r2, [r4, #0x70]
	orr r2, r2, #0x2
	strh r2, [r4, #0x70]
	bl FUN_02097958
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020983AC: .word FUN_020982C4

	arm_func_start FUN_020983B0
FUN_020983B0: ; 0x020983B0
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl FUN_02099FA8
	cmp r0, #0x0
	bne _020983D8
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x8
	beq _020983E4
_020983D8:
	mvn r0, #0x1b
	ldmia sp!, {r4-r6,lr}
	bx lr
_020983E4:
	cmp r6, #0x0
	mov r1, #0x0
	beq _020983FC
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_020983FC:
	cmp r1, #0x0
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrsb r0, [r6, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _02098424
	cmp r0, #0x4
	movne r1, #0x0
_02098424:
	cmp r1, #0x0
	beq _0209849C
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x4
	beq _02098450
	ldrsb r0, [r6, #0x72]
	cmp r0, #0x1
	mvneq r0, #0x1d
	movne r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
_02098450:
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x2
	beq _02098478
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x40
	ldrne r0, [r6, #0x6c]
	ldreq r0, _020984B0 ; =UNK_021061C0
	ldreq r0, [r0, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
_02098478:
	strh r5, [r6, #0x76]
	mov r0, r6
	str r4, [r6, #0x78]
	bl FUN_02098350
	ldrsb r1, [r6, #0x72]
	cmp r1, #0x1
	mvnne r0, #0x19
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209849C:
	strh r5, [r6, #0x76]
	str r4, [r6, #0x78]
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020984B0: .word UNK_021061C0

	arm_func_start FUN_020984B4
FUN_020984B4:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	mov r5, r1
	bl FUN_02099FA8
	cmp r0, #0x0
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	cmp r4, #0x0
	mov r1, #0x0
	beq _020984F4
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_020984F4:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x2
	addne sp, sp, #0x4
	mvnne r0, #0x6
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	strh r5, [r4, #0x74]
	ldrsb r0, [r4, #0x73]
	cmp r0, #0x1
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r0, r4
	bl FUN_02098350
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02098550
FUN_02098550: ; 0x02098550
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r7, r2
	ldr r6, [r7, #0x64]
	mov r9, r0
	mov r8, r1
	bl OS_DisableInterrupts
	add r1, r6, #0x100
	ldrh r2, [r1, #0x8]
	ldrh r1, [r1, #0xa]
	mov r4, r0
	add r0, r2, r8
	cmp r1, r0
	blo _02098618
	ldr r1, _02098668 ; =UNK_021C8CC0
	add r0, r8, #0xc
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x18]
	blx r1
	movs r5, r0
	beq _02098604
	add r1, r6, #0x100
	ldrh r3, [r1, #0x8]
	mov r2, #0x0
	mov r0, r9
	add r3, r3, r8
	strh r3, [r1, #0x8]
	str r2, [r5, #0x0]
	strh r8, [r5, #0x4]
	ldrh r3, [r7, #0x18]
	mov r2, r8
	add r1, r5, #0xc
	strh r3, [r5, #0x6]
	ldr r3, [r7, #0x1c]
	str r3, [r5, #0x8]
	bl MI_CpuCopy8
	ldr r0, [r6, #0x100]
	cmp r0, #0x0
	ldrne r0, [r6, #0x100]
	strne r5, [r0, #0x0]
	str r5, [r6, #0x100]
	ldr r0, [r6, #0x104]
	cmp r0, #0x0
	streq r5, [r6, #0x104]
	b _02098628
_02098604:
	ldr r0, _0209866C ; =UNK_021C8D28
	ldr r1, [r0, #0x0]
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	b _02098628
_02098618:
	ldr r0, _0209866C ; =UNK_021C8D28
	ldr r1, [r0, #0x4]
	add r1, r1, #0x1
	str r1, [r0, #0x4]
_02098628:
	ldrh r0, [r7, #0x74]
	cmp r0, #0x0
	ldreqh r0, [r7, #0xa]
	streqh r0, [r7, #0x74]
	ldrh r1, [r7, #0x1a]
	add r0, r6, #0x10c
	strh r1, [r7, #0x18]
	ldr r1, [r7, #0x20]
	str r1, [r7, #0x1c]
	bl OS_WakeupThread
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_02098668: .word UNK_021C8CC0
_0209866C: .word UNK_021C8D28

	arm_func_start FUN_02098670
FUN_02098670: ; 0x02098670
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r10, r0
	ldr r9, [r10, #0x64]
	str r1, [sp, #0x0]
	ldr r0, [r9, #0x104]
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	bl OS_DisableInterrupts
	ldr r8, [r9, #0x104]
	str r0, [sp, #0xc]
	cmp r8, #0x0
	bne _02098710
	ldr r0, [sp, #0x3c]
	and r7, r0, #0x1
	add r6, r9, #0x10c
	mov r4, #0x1
	mov r5, #0x0
_020986B8:
	cmp r7, #0x0
	mvneq r11, #0x5
	beq _02098710
	mov r0, r6
	bl OS_SleepThread
	mov r0, r10
	bl FUN_02099FA8
	cmp r0, #0x0
	bne _020986FC
	mov r1, r5
	cmp r10, #0x0
	beq _020986F4
	ldrsh r0, [r10, #0x70]
	ands r0, r0, #0x1
	movne r1, r4
_020986F4:
	cmp r1, #0x0
	bne _02098704
_020986FC:
	mvn r11, #0x37
	b _02098710
_02098704:
	ldr r8, [r9, #0x104]
	cmp r8, #0x0
	beq _020986B8
_02098710:
	cmp r8, #0x0
	beq _020987A4
	ldrh r1, [r8, #0x4]
	ldr r0, [sp, #0x4]
	cmp r0, r1
	strgt r1, [sp, #0x4]
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	add r0, r8, #0xc
	bl MI_CpuCopy8
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	ldrneh r1, [r8, #0x6]
	strneh r1, [r0, #0x0]
	ldr r1, [sp, #0x38]
	cmp r1, #0x0
	ldrne r0, [r8, #0x8]
	strne r0, [r1, #0x0]
	ldrsb r0, [r9, #0xfe]
	ldrh r11, [r8, #0x4]
	cmp r0, #0x0
	bne _020987A4
	ldr r0, [r8, #0x0]
	ldr r1, _020987BC ; =UNK_021C8CC0
	str r0, [r9, #0x104]
	ldr r0, [r8, #0x0]
	cmp r0, #0x0
	moveq r0, #0x0
	streq r0, [r9, #0x100]
	ldr r1, [r1, #0x0]
	mov r0, r8
	ldr r1, [r1, #0x1c]
	blx r1
	add r0, r9, #0x100
	ldrh r1, [r0, #0x8]
	sub r1, r1, r11
	strh r1, [r0, #0x8]
_020987A4:
	ldr r0, [sp, #0xc]
	bl OS_RestoreInterrupts
	mov r0, r11
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020987BC: .word UNK_021C8CC0

	arm_func_start FUN_020987C0
FUN_020987C0: ; 0x020987C0
	stmdb sp!, {r4-r6,lr}
	ldr r6, [r0, #0x64]
	bl OS_DisableInterrupts
	ldr r4, [r6, #0xf8]
	mov r5, r0
	cmp r4, #0x0
	beq _020987EC
	mov r1, #0x0
	mov r0, r4
	str r1, [r6, #0xf8]
	bl FUN_0209C52C
_020987EC:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_02098800
FUN_02098800: ; 0x02098800
	ldr ip, _0209880C ; =FUN_020987C0
	ldr r0, [r0, #0x4]
	bx r12
	.balign 4
_0209880C: .word FUN_020987C0

	arm_func_start FUN_02098810
FUN_02098810:
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r1, [r4, #0x64]
	ldrh r0, [r1, #0xfc]
	ldr r1, [r1, #0xf8]
	cmp r1, r0
	movlt r0, #0x0
	ldmltia sp!, {r4,lr}
	bxlt lr
	ldr r0, _02098864 ; =FUN_02098800
	mov r1, r4
	mov r2, #0x0
	bl FUN_02097A98
	movs r1, r0
	mvneq r0, #0x20
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, r4
	bl FUN_02097958
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02098864: .word FUN_02098800

	arm_func_start FUN_02098868
FUN_02098868: ; 0x02098868
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	ldr r9, [r0, #0x4]
	ldr r1, [r0, #0x10]
	ldr r8, [r9, #0x64]
	str r1, [sp, #0x4]
	ldr r1, [r0, #0x18]
	ldr r10, [r0, #0x14]
	ldr r0, [r0, #0x1c]
	ldr r7, [r8, #0xf8]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	add r11, sp, #0x10
	mov r5, #0x0
	mov r6, #0x1
	mov r4, #0xa
_020988A8:
	mov r0, r11
	bl FUN_0209C638
	cmp r0, #0x0
	beq _02098904
	ldr r1, [sp, #0x10]
	sub r1, r1, r7
	cmp r1, #0x0
	bgt _02098904
	ldrsb r0, [r9, #0x73]
	mov r1, r6
	cmp r0, #0x0
	beq _020988E0
	cmp r0, #0x4
	movne r1, r5
_020988E0:
	cmp r1, #0x0
	beq _020988F8
	ldrb r0, [r9, #0x8]
	cmp r0, #0x4
	movne r0, #0x0
	bne _02098904
_020988F8:
	mov r0, r4
	bl OS_Sleep
	b _020988A8
_02098904:
	ldrsb r1, [r9, #0x73]
	cmp r1, #0x4
	bne _02098954
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r1, [sp, #0x10]
	cmp r10, r1
	movhi r10, r1
	ldr r1, [sp, #0x4]
	mov r2, r10
	bl MI_CpuCopy8
	mov r0, r10
	bl FUN_0209C52C
	add sp, sp, #0x14
	mov r0, r10
	ldmia sp!, {r4-r11,lr}
	bx lr
_02098954:
	cmp r0, #0x0
	moveq r4, #0x0
	beq _02098980
	ldr r4, [sp, #0xc]
	ldr r1, [sp, #0x4]
	ldr r3, [sp, #0x8]
	mov r0, r9
	mov r2, r10
	str r4, [sp, #0x0]
	bl FUN_02098AA4
	mov r4, r0
_02098980:
	cmp r4, #0x0
	addle sp, sp, #0x14
	movle r0, r4
	ldmleia sp!, {r4-r11,lr}
	bxle lr
	ldrh r0, [r8, #0xfc]
	ldr r1, [r8, #0xf8]
	cmp r1, r0
	blt _020989AC
	mov r0, r9
	bl FUN_020987C0
_020989AC:
	mov r0, r4
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_020989BC
FUN_020989BC: ; 0x020989BC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	ldr r0, _02098A10 ; =FUN_02098868
	mov r1, r7
	mov r2, #0x1
	mov r4, r3
	bl FUN_02097A98
	mov r1, r0
	str r6, [r1, #0x10]
	str r5, [r1, #0x14]
	ldr r2, [sp, #0x18]
	str r4, [r1, #0x18]
	mov r0, r7
	str r2, [r1, #0x1c]
	bl FUN_02097958
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02098A10: .word FUN_02098868

	arm_func_start FUN_02098A14
FUN_02098A14:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x64]
	ldr r5, [r0, #0xc4]
	ldr r4, [r0, #0xf8]
	ldr r0, [r5, #0x44]
	subs lr, r0, r4
	bmi _02098A78
	ldrh r12, [r5, #0xa]
	ldr r0, [sp, #0x10]
	cmp lr, #0x0
	strh r12, [r2, #0x0]
	ldrh r2, [r5, #0x18]
	strh r2, [r3, #0x0]
	ldr r2, [r5, #0x1c]
	str r2, [r0, #0x0]
	str lr, [r1, #0x0]
	bne _02098A90
	ldrb r0, [r5, #0x8]
	cmp r0, #0x4
	beq _02098A90
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_02098A78:
	mvn r0, #0x0
	str r0, [r1, #0x0]
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_02098A90:
	ldr r0, [r5, #0x40]
	add r0, r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_02098AA4
FUN_02098AA4: ; 0x02098AA4
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x14
	mov r9, r0
	mov r8, r1
	mov r7, r2
	mov r6, r3
	bl OS_DisableInterrupts
	add r1, sp, #0xc
	mov r5, r0
	str r1, [sp, #0x0]
	add r1, sp, #0x8
	mov r0, r9
	add r2, sp, #0x4
	add r3, sp, #0x6
	bl FUN_02098A14
	cmp r0, #0x0
	beq _02098B48
	ldr r4, [sp, #0x8]
	cmp r4, #0x0
	mvneq r4, #0x5
	beq _02098B64
	ldrsb r1, [r9, #0x73]
	cmp r7, r4
	movgt r7, r4
	mov r2, #0x1
	cmp r1, #0x0
	beq _02098B18
	cmp r1, #0x4
	movne r2, #0x0
_02098B18:
	cmp r2, #0x0
	mov r1, r8
	mov r2, r7
	movne r4, r7
	bl MI_CpuCopy8
	ldr r1, [r9, #0x64]
	ldrsb r0, [r1, #0xfe]
	cmp r0, #0x0
	ldreq r0, [r1, #0xf8]
	addeq r0, r0, r4
	streq r0, [r1, #0xf8]
	b _02098B64
_02098B48:
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	ldrsh r0, [r9, #0x70]
	moveq r4, #0x0
	mvnne r4, #0x1b
	bic r0, r0, #0x6
	strh r0, [r9, #0x70]
_02098B64:
	cmp r4, #0x0
	blt _02098B9C
	cmp r6, #0x0
	beq _02098B8C
	ldr r1, [sp, #0x30]
	cmp r1, #0x0
	ldrneh r0, [sp, #0x6]
	strneh r0, [r6, #0x0]
	ldrne r0, [sp, #0xc]
	strne r0, [r1, #0x0]
_02098B8C:
	ldrh r0, [r9, #0x74]
	cmp r0, #0x0
	ldreqh r0, [sp, #0x4]
	streqh r0, [r9, #0x74]
_02098B9C:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x14
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_02098BB4
FUN_02098BB4: ; 0x02098BB4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldrsb r12, [r7, #0x73]
	mov r6, r1
	mov r5, r2
	mov r4, r3
	cmp r12, #0x4
	bne _02098BF0
	ldr r4, [sp, #0x18]
	str r4, [sp, #0x0]
	bl FUN_020989BC
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_02098BF0:
	ldr r12, [sp, #0x18]
	str r12, [sp, #0x0]
	bl FUN_02098AA4
	mvn r1, #0x5
	cmp r0, r1
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldr r1, [sp, #0x1c]
	ands r1, r1, #0x1
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r12, [sp, #0x18]
	mov r0, r7
	mov r1, r6
	mov r2, r5
	mov r3, r4
	str r12, [sp, #0x0]
	bl FUN_020989BC
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_02098C4C
FUN_02098C4C: ; 0x02098C4C
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	ldr r5, [sp, #0x28]
	mov r7, r0
	ands r0, r5, #0x2
	ldr r5, [r7, #0x64]
	beq _02098C74
	cmp r5, #0x0
	movne r6, #0x1
	bne _02098C78
_02098C74:
	mov r6, #0x0
_02098C78:
	cmp r6, #0x0
	ldrnesb r4, [r5, #0xfe]
	movne r0, #0x1
	strneb r0, [r5, #0xfe]
	ldrsb r0, [r7, #0x73]
	cmp r0, #0x1
	bne _02098CB4
	ldr r0, [sp, #0x20]
	ldr r12, [sp, #0x24]
	str r0, [sp, #0x0]
	mov r0, r7
	str r12, [sp, #0x4]
	bl FUN_02098670
	mov r8, r0
	b _02098CDC
_02098CB4:
	ldr r0, [sp, #0x20]
	ldr r12, [sp, #0x24]
	str r0, [sp, #0x0]
	mov r0, r7
	str r12, [sp, #0x4]
	bl FUN_02098BB4
	movs r8, r0
	bmi _02098CDC
	mov r0, r7
	bl FUN_02098810
_02098CDC:
	cmp r6, #0x0
	strneb r4, [r5, #0xfe]
	mov r0, r8
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_02098CF4
FUN_02098CF4:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0xc
	mov r9, r0
	mov r8, r1
	mov r7, r2
	mov r6, r3
	bl FUN_02099FA8
	cmp r0, #0x0
	addne sp, sp, #0xc
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r9,lr}
	bxne lr
	ldr r0, [sp, #0x2c]
	ands r0, r0, #0x4
	bne _02098D3C
	ldrsb r0, [r9, #0x72]
	cmp r0, #0x0
	bne _02098D5C
_02098D3C:
	ldrsb r0, [r9, #0x73]
	cmp r0, #0x4
	addeq sp, sp, #0xc
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	mov r4, #0x0
	b _02098D78
_02098D5C:
	bl OS_GetProcMode
	cmp r0, #0x12
	addeq sp, sp, #0xc
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	mov r4, #0x1
_02098D78:
	cmp r9, #0x0
	mov r1, #0x0
	beq _02098D90
	ldrsh r0, [r9, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_02098D90:
	cmp r1, #0x0
	addeq sp, sp, #0xc
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldrsb r0, [r9, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _02098DBC
	cmp r0, #0x4
	movne r1, #0x0
_02098DBC:
	cmp r1, #0x0
	beq _02098DEC
	ldrsh r0, [r9, #0x70]
	ands r0, r0, #0x4
	beq _02098DDC
	ldrsh r0, [r9, #0x70]
	ands r0, r0, #0x8
	beq _02098DEC
_02098DDC:
	add sp, sp, #0xc
	mvn r0, #0x37
	ldmia sp!, {r4-r9,lr}
	bx lr
_02098DEC:
	ands r0, r4, #0x1
	ldr r5, [r9, #0x64]
	bne _02098E18
	add r0, r5, #0xe0
	bl OS_TryLockMutex
	cmp r0, #0x0
	bne _02098E20
	add sp, sp, #0xc
	mvn r0, #0x5
	ldmia sp!, {r4-r9,lr}
	bx lr
_02098E18:
	add r0, r5, #0xe0
	bl OS_LockMutex
_02098E20:
	ldr r0, [sp, #0x28]
	ldr r12, [sp, #0x2c]
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	mov r0, r9
	mov r1, r8
	mov r2, r7
	mov r3, r6
	str r12, [sp, #0x8]
	bl FUN_02098C4C
	mov r4, r0
	add r0, r5, #0xe0
	bl OS_UnlockMutex
	mov r0, r4
	add sp, sp, #0xc
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_02098E64
FUN_02098E64: ; 0x02098E64
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r2
	ldr r5, [r6, #0x14]
	ldr r4, [r6, #0x1c]
	cmp r5, r1
	mov r7, r0
	movgt r5, r1
	movgt r4, #0x0
	bgt _02098E98
	sub r0, r1, r5
	cmp r4, r0
	movgt r4, r0
_02098E98:
	cmp r5, #0x0
	ble _02098EC8
	ldr r0, [r6, #0x10]
	mov r1, r7
	mov r2, r5
	bl MI_CpuCopy8
	ldr r0, [r6, #0x10]
	add r0, r0, r5
	str r0, [r6, #0x10]
	ldr r0, [r6, #0x14]
	sub r0, r0, r5
	str r0, [r6, #0x14]
_02098EC8:
	cmp r4, #0x0
	ble _02098EF8
	ldr r0, [r6, #0x18]
	mov r2, r4
	add r1, r7, r5
	bl MI_CpuCopy8
	ldr r0, [r6, #0x18]
	add r0, r0, r4
	str r0, [r6, #0x18]
	ldr r0, [r6, #0x1c]
	sub r0, r0, r4
	str r0, [r6, #0x1c]
_02098EF8:
	add r0, r5, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_02098F08
FUN_02098F08: ; 0x02098F08
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _02098FBC ; =OSi_ThreadInfo
	mov r4, r0
	ldr r0, [r1, #0x4]
	ldr r5, [r0, #0xa4]
	bl OS_DisableInterrupts
	cmp r5, #0x0
	beq _02098F74
	ldrh r3, [r5, #0x2e]
	cmp r3, #0x0
	beq _02098F64
	ldrh r2, [r5, #0x2c]
	cmp r2, #0x0
	beq _02098F64
	ldr r1, _02098FC0 ; =UNK_021C8CD4
	cmp r3, r2
	ldr r1, [r1, #0x24]
	movgt r3, r2
	cmp r3, r1
	movgt r3, r1
	mov r5, r3, lsl #0x1
	b _02098F80
_02098F64:
	ldr r1, _02098FC0 ; =UNK_021C8CD4
	ldr r1, [r1, #0x24]
	mov r5, r1, lsl #0x1
	b _02098F80
_02098F74:
	ldr r1, _02098FC0 ; =UNK_021C8CD4
	ldr r1, [r1, #0x24]
	mov r5, r1, lsl #0x1
_02098F80:
	bl OS_RestoreInterrupts
	cmp r5, #0x0
	ble _02098FAC
	mov r0, r4
	mov r1, r5
	bl _s32_div_f
	cmp r0, #0x0
	mulgt r0, r5, r0
	addgt sp, sp, #0x4
	ldmgtia sp!, {r4-r5,lr}
	bxgt lr
_02098FAC:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_02098FBC: .word OSi_ThreadInfo
_02098FC0: .word UNK_021C8CD4

	arm_func_start FUN_02098FC4
FUN_02098FC4: ; 0x02098FC4
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r8, r0
	ldr r7, [r8, #0x4]
	mov r4, #0x0
	ldrsb r0, [r7, #0x73]
	ldr r6, [r7, #0x68]
	mov r1, #0x1
	cmp r0, #0x0
	beq _02098FF4
	cmp r0, #0x4
	movne r1, r4
_02098FF4:
	cmp r1, #0x0
	beq _02099008
	ldrsh r0, [r7, #0x70]
	ands r0, r0, #0x4
	beq _020990DC
_02099008:
	ldr r2, [r8, #0x28]
	cmp r2, #0x0
	beq _02099020
	ldrh r0, [r8, #0x24]
	ldrh r1, [r8, #0x26]
	bl FUN_0209CB78
_02099020:
	ldrsb r1, [r7, #0x73]
	mov r0, #0x1
	cmp r1, #0x0
	beq _02099038
	cmp r1, #0x4
	movne r0, #0x0
_02099038:
	cmp r0, #0x0
	movne r2, #0x36
	moveq r2, #0x2a
	ldr r0, [r7, #0x4c]
	cmp r1, #0x0
	add r5, r0, r2
	beq _0209905C
	cmp r1, #0x4
	bne _02099070
_0209905C:
	ldr r0, [r7, #0x48]
	sub r0, r0, r2
	bl FUN_02098F08
	mov r9, r0
	b _02099078
_02099070:
	ldr r0, [r7, #0x48]
	sub r9, r0, r2
_02099078:
	mov r0, r5
	mov r1, r9
	mov r2, r8
	bl FUN_02098E64
	mov r1, r0
	cmp r1, #0x0
	ble _020990E0
	mov r0, r5
	bl FUN_0209C030
	cmp r0, #0x0
	bgt _020990D4
	ldrsb r0, [r7, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _020990BC
	cmp r0, #0x4
	movne r1, #0x0
_020990BC:
	cmp r1, #0x0
	ldrnesh r0, [r7, #0x70]
	mvn r4, #0x4b
	bicne r0, r0, #0xe
	strneh r0, [r7, #0x70]
	b _020990E0
_020990D4:
	add r4, r4, r0
	b _02099078
_020990DC:
	mvn r4, #0x4b
_020990E0:
	ldrh r2, [r8, #0x20]
	add r1, r6, #0x100
	add r0, r6, #0x104
	strh r2, [r1, #0x2]
	bl OS_WakeupThread
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_02099104
FUN_02099104:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	ldr r6, [r9, #0x68]
	mov r4, r1
	mov r8, r2
	ldr r1, [r6, #0x10c]
	ldr r2, [sp, #0x28]
	ldr r0, _0209929C ; =FUN_02098FC4
	mov r7, r3
	bl FUN_02097A98
	movs r5, r0
	addeq sp, sp, #0x4
	mvneq r0, #0x20
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r0, [sp, #0x28]
	ands r0, r0, #0x1
	beq _02099164
	ldrsb r0, [r9, #0x73]
	cmp r0, #0x1
	movne r0, #0x3
	strneb r0, [r5, #0xd]
	bne _0209916C
_02099164:
	mov r0, #0x0
	strb r0, [r5, #0xd]
_0209916C:
	ldr r2, [r6, #0xf8]
	add r1, r7, r8
	cmp r1, r2
	ldr r3, [r6, #0xfc]
	bge _020991A0
	add r0, r3, r7
	str r0, [r5, #0x10]
	str r8, [r5, #0x14]
	mov r0, #0x0
	str r0, [r5, #0x18]
	mov r7, r1
	str r0, [r5, #0x1c]
	b _020991D8
_020991A0:
	add r0, r3, r7
	str r0, [r5, #0x10]
	sub r0, r2, r7
	str r0, [r5, #0x14]
	str r3, [r5, #0x18]
	ldr r0, [r5, #0x14]
	sub r0, r8, r0
	str r0, [r5, #0x1c]
	ldr r7, [r5, #0x1c]
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	mov r2, r7
	add r0, r4, r0
	bl MI_CpuCopy8
_020991D8:
	ldr r1, [r5, #0x10]
	ldr r2, [r5, #0x14]
	mov r0, r4
	bl MI_CpuCopy8
	add r0, r6, #0x100
	ldrh r4, [r0, #0x0]
	strh r7, [r5, #0x20]
	ldrh r1, [r5, #0x20]
	strh r1, [r0, #0x0]
	ldrsb r0, [r9, #0x73]
	cmp r0, #0x1
	bne _02099268
	ldrh r0, [r9, #0x74]
	cmp r0, #0x0
	bne _02099224
	bl FUN_0209CC8C
	strh r0, [r9, #0x74]
	ldrh r0, [r9, #0x74]
	strh r0, [r9, #0xa]
_02099224:
	ldrh r0, [r9, #0x74]
	strh r0, [r5, #0x24]
	ldr r1, [r9, #0x78]
	cmp r1, #0x0
	beq _02099244
	ldr r0, [sp, #0x24]
	cmp r0, #0x0
	beq _02099258
_02099244:
	ldr r1, [sp, #0x24]
	ldrh r0, [sp, #0x20]
	str r1, [r5, #0x28]
	strh r0, [r5, #0x26]
	b _02099270
_02099258:
	str r1, [r5, #0x28]
	ldrh r0, [r9, #0x76]
	strh r0, [r5, #0x26]
	b _02099270
_02099268:
	mov r0, #0x0
	str r0, [r5, #0x28]
_02099270:
	ldr r0, [r6, #0x10c]
	mov r1, r5
	bl FUN_02097948
	cmp r0, #0x0
	addne r0, r6, #0x100
	movne r8, #0x0
	strneh r4, [r0, #0x0]
	mov r0, r8
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_0209929C: .word FUN_02098FC4

	arm_func_start FUN_020992A0
FUN_020992A0:
	ldr r2, [r0, #0x68]
	add r0, r2, #0x100
	ldrh r1, [r0, #0x0]
	ldrh r0, [r0, #0x2]
	ldr r2, [r2, #0xf8]
	sub r0, r0, r1
	subs r0, r0, #0x1
	addmi r0, r0, r2
	bx lr

	arm_func_start FUN_020992C4
FUN_020992C4: ; 0x020992C4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r10, r0
	mov r9, r1
	mov r8, r2
	cmp r8, r9
	mov r11, r3
	ldr r7, [r10, #0x68]
	movgt r8, r9
	bl OS_DisableInterrupts
	ldr r1, [sp, #0x28]
	str r0, [sp, #0x0]
	and r5, r1, #0x1
	add r4, r7, #0x104
_020992FC:
	mov r0, r10
	bl FUN_020992A0
	mov r6, r0
	cmp r6, r8
	blt _02099328
	add r0, r7, #0x100
	ldrh r0, [r0, #0x0]
	cmp r6, r9
	movge r6, r9
	str r0, [r11, #0x0]
	b _02099340
_02099328:
	cmp r5, #0x0
	moveq r6, #0x0
	beq _02099340
	mov r0, r4
	bl OS_SleepThread
	b _020992FC
_02099340:
	ldr r0, [sp, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_02099358
FUN_02099358: ; 0x02099358
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x1c
	mov r10, r0
	ldr r4, [r10, #0x68]
	ldrsb r0, [r10, #0x73]
	ldr r4, [r4, #0x10c]
	mov r9, r1
	cmp r0, #0x1
	ldr r0, [r4, #0x48]
	mov r8, r2
	str r3, [sp, #0xc]
	ldr r7, [sp, #0x40]
	ldr r6, [sp, #0x44]
	mov r4, #0x0
	bne _020993B4
	sub r0, r0, #0x2a
	cmp r8, r0
	addgt sp, sp, #0x1c
	mvngt r0, #0x22
	ldmgtia sp!, {r4-r11,lr}
	bxgt lr
	str r8, [sp, #0x10]
	b _020993C4
_020993B4:
	sub r0, r0, #0x36
	str r0, [sp, #0x10]
	cmp r8, r0
	strle r8, [sp, #0x10]
_020993C4:
	cmp r8, #0x0
	ble _02099460
	and r11, r6, #0x1
_020993D0:
	ldr r2, [sp, #0x10]
	mov r0, r10
	mov r1, r8
	add r3, sp, #0x14
	str r6, [sp, #0x0]
	bl FUN_020992C4
	mov r5, r0
	cmp r5, #0x0
	ble _02099438
	ldr r0, [sp, #0xc]
	mov r1, r9
	str r0, [sp, #0x0]
	str r7, [sp, #0x4]
	str r6, [sp, #0x8]
	ldr r3, [sp, #0x14]
	mov r0, r10
	mov r2, r5
	bl FUN_02099104
	cmp r0, #0x0
	addle sp, sp, #0x1c
	mvnle r0, #0x5
	ldmleia sp!, {r4-r11,lr}
	bxle lr
	add r9, r9, r5
	sub r8, r8, r5
	add r4, r4, r5
_02099438:
	cmp r11, #0x0
	bne _02099458
	cmp r5, #0x0
	bgt _02099460
	add sp, sp, #0x1c
	mvn r0, #0x5
	ldmia sp!, {r4-r11,lr}
	bx lr
_02099458:
	cmp r8, #0x0
	bgt _020993D0
_02099460:
	mov r0, r4
	add sp, sp, #0x1c
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FUN_02099470
FUN_02099470: ; 0x02099470
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r5, r3
	bl FUN_02099FA8
	cmp r0, #0x0
	addne sp, sp, #0x8
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	cmp r8, #0x0
	mov r1, #0x0
	beq _020994B8
	ldrsh r0, [r8, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_020994B8:
	cmp r1, #0x0
	addeq sp, sp, #0x8
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldrsb r0, [r8, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _020994E4
	cmp r0, #0x4
	movne r1, #0x0
_020994E4:
	cmp r1, #0x0
	beq _02099514
	ldrsh r0, [r8, #0x70]
	ands r0, r0, #0x4
	beq _02099504
	ldrsh r0, [r8, #0x70]
	ands r0, r0, #0x8
	beq _02099514
_02099504:
	add sp, sp, #0x8
	mvn r0, #0x37
	ldmia sp!, {r4-r8,lr}
	bx lr
_02099514:
	ldr r0, [sp, #0x24]
	ldr r4, [r8, #0x68]
	ands r0, r0, #0x4
	bne _02099530
	ldrsb r0, [r8, #0x72]
	cmp r0, #0x0
	bne _02099554
_02099530:
	add r0, r4, #0xe0
	bl OS_TryLockMutex
	cmp r0, #0x0
	addeq sp, sp, #0x8
	mvneq r0, #0x5
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r12, #0x0
	b _02099560
_02099554:
	add r0, r4, #0xe0
	bl OS_LockMutex
	mov r12, #0x1
_02099560:
	ldr r1, [sp, #0x20]
	mov r0, r8
	str r1, [sp, #0x0]
	mov r1, r7
	mov r2, r6
	mov r3, r5
	str r12, [sp, #0x4]
	bl FUN_02099358
	mov r5, r0
	add r0, r4, #0xe0
	bl OS_UnlockMutex
	mov r0, r5
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_0209959C
FUN_0209959C: ; 0x0209959C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x4]
	mov r1, #0x1
	ldrsb r0, [r0, #0x73]
	cmp r0, #0x0
	beq _020995C0
	cmp r0, #0x4
	movne r1, #0x0
_020995C0:
	cmp r1, #0x0
	beq _020995CC
	bl FUN_0209C840
_020995CC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020995DC
FUN_020995DC: ; 0x020995DC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	bl FUN_02099FA8
	cmp r0, #0x0
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	cmp r4, #0x0
	mov r1, #0x0
	beq _02099618
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_02099618:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x4
	beq _02099644
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x8
	beq _02099654
_02099644:
	add sp, sp, #0x4
	mvn r0, #0x37
	ldmia sp!, {r4-r5,lr}
	bx lr
_02099654:
	ldrsh r0, [r4, #0x70]
	orr r0, r0, #0x8
	strh r0, [r4, #0x70]
	ldr r5, [r4, #0x68]
	cmp r5, #0x0
	beq _020996AC
	ldr r1, [r5, #0x10c]
	cmp r1, #0x0
	beq _020996AC
	ldrsb r2, [r4, #0x72]
	ldr r0, _020996BC ; =FUN_0209959C
	bl FUN_02097A98
	movs r1, r0
	addeq sp, sp, #0x4
	mvneq r0, #0x20
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r0, [r5, #0x10c]
	bl FUN_02097948
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020996AC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020996BC: .word FUN_0209959C

	arm_func_start FUN_020996C0
FUN_020996C0: ; 0x020996C0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r4, _02099704 ; =UNK_021C8D34
	mov r5, r0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020996F0
_020996E0:
	bl FUN_020997B8
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _020996E0
_020996F0:
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_02099704: .word UNK_021C8D34

	arm_func_start FUN_02099708
FUN_02099708: ; 0x02099708
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	movs r8, r0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	add r0, r8, #0x20
	bl OS_JoinThread
	bl OS_DisableInterrupts
	mov r7, r0
	bl OS_DisableScheduler
	add r1, sp, #0x0
	mov r0, r8
	mov r2, #0x0
	bl OS_ReceiveMessage
	cmp r0, #0x0
	beq _0209979C
	add r4, sp, #0x0
	mvn r6, #0xa
	mov r5, #0x0
_02099758:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _02099784
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0209977C
	mov r1, r6
	mov r2, r5
	bl OS_SendMessage
_0209977C:
	ldr r0, [sp, #0x0]
	bl FUN_02097A64
_02099784:
	mov r0, r8
	mov r1, r4
	mov r2, r5
	bl OS_ReceiveMessage
	cmp r0, #0x0
	bne _02099758
_0209979C:
	bl OS_EnableScheduler
	bl OS_RescheduleThread
	mov r0, r7
	bl OS_RestoreInterrupts
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_020997B8
FUN_020997B8:
	stmdb sp!, {r4-r6,lr}
	movs r4, r0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r0, #0x0
	strh r0, [r4, #0x70]
	ldrsb r1, [r4, #0x73]
	mov r2, #0x1
	cmp r1, #0x0
	beq _020997E8
	cmp r1, #0x4
	movne r2, r0
_020997E8:
	cmp r2, #0x0
	beq _02099804
	ldr r0, [r4, #0x68]
	bl FUN_02099708
	ldr r0, [r4, #0x64]
	bl FUN_02099708
	b _02099884
_02099804:
	cmp r1, #0x1
	bne _02099874
	ldr r0, [r4, #0x64]
	ldr r0, [r0, #0x104]
	cmp r0, #0x0
	beq _0209983C
	ldr r5, _020998C0 ; =UNK_021C8CC0
_02099820:
	ldr r1, [r5, #0x0]
	ldr r6, [r0, #0x0]
	ldr r1, [r1, #0x1c]
	blx r1
	mov r0, r6
	cmp r6, #0x0
	bne _02099820
_0209983C:
	ldr r0, [r4, #0x64]
	mov r1, #0x0
	add r0, r0, #0x100
	strh r1, [r0, #0x8]
	ldr r0, [r4, #0x64]
	str r1, [r0, #0x100]
	ldr r0, [r4, #0x64]
	str r1, [r0, #0x104]
	ldr r0, [r4, #0x64]
	add r0, r0, #0x10c
	bl OS_WakeupThread
	ldr r0, [r4, #0x64]
	bl FUN_02099708
	b _02099884
_02099874:
	cmp r1, #0x2
	bne _02099884
	ldr r0, [r4, #0x68]
	bl FUN_02099708
_02099884:
	bl OS_DisableInterrupts
	mov r5, r0
	mov r0, r4
	bl FUN_0209A054
	mov r0, r4
	bl FUN_02099FF0
	ldr r1, _020998C0 ; =UNK_021C8CC0
	mov r0, r4
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x1c]
	blx r1
	mov r0, r5
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020998C0: .word UNK_021C8CC0

	arm_func_start FUN_020998C4
FUN_020998C4: ; 0x020998C4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r4, [r0, #0x4]
	mov r1, #0x1
	ldrsb r0, [r4, #0x73]
	cmp r0, #0x0
	beq _020998E8
	cmp r0, #0x4
	movne r1, #0x0
_020998E8:
	cmp r1, #0x0
	beq _02099908
	ldr r0, [r4, #0x68]
	add r0, r0, #0x20
	bl OS_JoinThread
	bl FUN_0209C840
	bl FUN_0209C7AC
	bl FUN_0209CB24
_02099908:
	bl FUN_0209CC10
	ldrsh r0, [r4, #0x70]
	mov r1, #0x0
	bic r0, r0, #0x6
	strh r0, [r4, #0x70]
	ldrsb r0, [r4, #0x73]
	cmp r0, #0x2
	ldreq r0, [r4, #0x68]
	ldrne r0, [r4, #0x64]
	bl FUN_020979F8
	bl OS_DisableInterrupts
	mov r5, r0
	mov r0, r4
	bl FUN_0209A054
	mov r0, r4
	bl FUN_0209A06C
	mov r0, r5
	bl OS_RestoreInterrupts
	ldrsh r1, [r4, #0x70]
	mov r0, #0x0
	orr r1, r1, #0x20
	strh r1, [r4, #0x70]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209996C
FUN_0209996C: ; 0x0209996C
	stmdb sp!, {r4,lr}
	mov r4, r0
	cmp r4, #0x0
	mvnle r0, #0x1b
	ldmleia sp!, {r4,lr}
	bxle lr
	bl FUN_02099F78
	cmp r0, #0x0
	mvnne r0, #0x19
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r0, r4
	bl FUN_02099FA8
	cmp r0, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	cmp r4, #0x0
	mov r1, #0x0
	beq _020999C8
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_020999C8:
	cmp r1, #0x0
	mvneq r0, #0x26
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x10
	mvnne r0, #0x19
	ldmneia sp!, {r4,lr}
	bxne lr
	ldrsh r0, [r4, #0x70]
	mov r1, #0x1
	orr r0, r0, #0x18
	strh r0, [r4, #0x70]
	ldrsb r0, [r4, #0x73]
	cmp r0, #0x0
	beq _02099A10
	cmp r0, #0x4
	movne r1, #0x0
_02099A10:
	cmp r1, #0x0
	beq _02099A24
	ldr r0, [r4, #0x68]
	mov r1, #0x0
	bl FUN_020979F8
_02099A24:
	ldr r0, _02099A54 ; =FUN_020998C4
	mov r1, r4
	mov r2, #0x1
	bl FUN_02097A98
	mov r1, r0
	mov r2, #0x0
	mov r0, r4
	str r2, [r1, #0x8]
	bl FUN_020979DC
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02099A54: .word FUN_020998C4

	arm_func_start FUN_02099A58
FUN_02099A58:
	stmdb sp!, {r4,lr}
	movs r4, r0
	bmi _02099A88
	bl FUN_02099FA8
	cmp r0, #0x0
	beq _02099A88
	mov r0, r4
	bl FUN_02099F78
	cmp r0, #0x0
	moveq r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
_02099A88:
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_02099A94
FUN_02099A94: ; 0x02099A94
	stmdb sp!, {r4,lr}
	ldr r0, _02099B10 ; =UNK_021C8CD0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02099AE8
	bl FUN_02099B14
	movs r4, r0
	bne _02099AE0
	ldr r0, _02099B10 ; =UNK_021C8CD0
	ldr r0, [r0, #0x0]
	bl FUN_0209996C
	ldr r0, _02099B10 ; =UNK_021C8CD0
	ldr r0, [r0, #0x0]
	bl FUN_02099A58
	cmp r0, #0x0
	ldrne r0, _02099B10 ; =UNK_021C8CD0
	movne r1, #0x0
	strne r1, [r0, #0x0]
	mvn r4, #0x19
_02099AE0:
	bl FUN_020996C0
	b _02099B04
_02099AE8:
	bl FUN_0209FD34
	cmp r0, #0x0
	mvneq r4, #0x19
	beq _02099B04
	mov r0, #0x0
	bl FUN_020A87BC
	mov r4, #0x0
_02099B04:
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02099B10: .word UNK_021C8CD0

	arm_func_start FUN_02099B14
FUN_02099B14: ; 0x02099B14
	stmdb sp!, {r4-r6,lr}
	ldr r4, _02099BBC ; =UNK_021C8CD0
	ldr r5, _02099BC0 ; =UNK_021C8D30
_02099B20:
	bl OS_DisableInterrupts
	ldr r6, [r5, #0x0]
	cmp r6, #0x0
	beq _02099B54
	ldr r2, [r4, #0x0]
_02099B34:
	cmp r6, r2
	beq _02099B48
	ldrsh r1, [r6, #0x70]
	ands r1, r1, #0x10
	beq _02099B54
_02099B48:
	ldr r6, [r6, #0x7c]
	cmp r6, #0x0
	bne _02099B34
_02099B54:
	bl OS_RestoreInterrupts
	cmp r6, #0x0
	beq _02099B6C
	mov r0, r6
	bl FUN_0209996C
	b _02099B20
_02099B6C:
	ldr r0, _02099BC0 ; =UNK_021C8D30
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02099B98
	ldr r0, _02099BBC ; =UNK_021C8CD0
	ldr r0, [r0, #0x0]
	cmp r1, r0
	bne _02099BB0
	ldr r0, [r1, #0x7c]
	cmp r0, #0x0
	bne _02099BB0
_02099B98:
	ldr r0, _02099BC4 ; =UNK_021C8D34
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
_02099BB0:
	mvn r0, #0x19
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_02099BBC: .word UNK_021C8CD0
_02099BC0: .word UNK_021C8D30
_02099BC4: .word UNK_021C8D34

	arm_func_start FUN_02099BC8
FUN_02099BC8: ; 0x02099BC8
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _02099C68 ; =UNK_021C8CC8
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	ldreq r0, _02099C6C ; =UNK_021C8F04
	ldreq r0, [r0, #0x0]
	streq r0, [r1, #0x0]
	bl FUN_02099A94
	mvn r4, #0x19
	cmp r0, r4
	bne _02099C10
	mov r5, #0x64
_02099BFC:
	mov r0, r5
	bl OS_Sleep
	bl FUN_02099A94
	cmp r0, r4
	beq _02099BFC
_02099C10:
	bl FUN_02097B14
	movs r4, r0
	bmi _02099C58
	bl FUN_0209FCC4
	mov r0, #0x0
	bl FUN_0209FD24
	ldr r0, _02099C70 ; =UNK_021C8CC0
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x28]
	cmp r0, #0x0
	bne _02099C4C
	ldr r0, _02099C74 ; =UNK_021C8CD4
	ldr r1, [r1, #0x1c]
	ldr r0, [r0, #0x1c]
	blx r1
_02099C4C:
	ldr r0, _02099C70 ; =UNK_021C8CC0
	mov r1, #0x0
	str r1, [r0, #0x0]
_02099C58:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_02099C68: .word UNK_021C8CC8
_02099C6C: .word UNK_021C8F04
_02099C70: .word UNK_021C8CC0
_02099C74: .word UNK_021C8CD4

	arm_func_start FUN_02099C78
FUN_02099C78:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _02099CE0 ; =UNK_021C8F04
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	bne _02099CBC
	ldr r0, _02099CE4 ; =UNK_021C8CCC
	ldr r0, [r0, #0x0]
	and r0, r0, #0x3
	cmp r0, #0x1
	bne _02099CCC
	bl OS_GetProcMode
	cmp r0, #0x12
	beq _02099CCC
	mov r0, #0xa
	bl OS_Sleep
	b _02099CCC
_02099CBC:
	ldr r0, _02099CE8 ; =UNK_021C8CC8
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	streq r2, [r0, #0x0]
_02099CCC:
	ldr r0, _02099CE0 ; =UNK_021C8F04
	ldr r0, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02099CE0: .word UNK_021C8F04
_02099CE4: .word UNK_021C8CCC
_02099CE8: .word UNK_021C8CC8

	arm_func_start FUN_02099CEC
FUN_02099CEC: ; 0x02099CEC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl FUN_02099C78
	cmp r0, #0x0
	ldrne r1, _02099D24 ; =UNK_021C8F1C
	mvneq r0, #0x26
	movne r0, #0x0
	strne r5, [r1, #0x0]
	strne r4, [r1, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_02099D24: .word UNK_021C8F1C

	arm_func_start FUN_02099D28
FUN_02099D28:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _02099D84 ; =UNK_021C8F1C
	mov r5, r0
	ldr r7, [r1, #0x0]
	mov r2, #0x0
	ldr r6, [r1, #0x4]
	mov r0, r4
	str r2, [r1, #0x0]
	str r2, [r1, #0x4]
	bl FUN_0209AB80
	ldr r1, _02099D84 ; =UNK_021C8F1C
	mov r4, r0
	mov r0, r5
	str r7, [r1, #0x0]
	str r6, [r1, #0x4]
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02099D84: .word UNK_021C8F1C

	arm_func_start FUN_02099D88
FUN_02099D88: ; 0x02099D88
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x64
	movs r4, r0
	addeq sp, sp, #0x64
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r1, _02099E34 ; =UNK_021C8CC0
	mov r0, #0xfd0
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x18]
	blx r1
	movs r5, r0
	addeq sp, sp, #0x64
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	add r0, sp, #0x0
	mov r1, #0x0
	mov r2, #0x64
	bl MI_CpuFill8
	ldr r3, _02099E38 ; =0x00000B68
	ldr r1, _02099E3C ; =0x00000466
	add r2, r5, r3
	add r0, sp, #0x0
	str r5, [sp, #0x40]
	str r3, [sp, #0x3c]
	str r2, [sp, #0x4c]
	str r1, [sp, #0x48]
	bl FUN_0209CC28
	mov r0, r4
	bl FUN_0209AB80
	mov r4, r0
	bl FUN_0209CC10
	ldr r1, _02099E34 ; =UNK_021C8CC0
	mov r0, r5
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x1c]
	blx r1
	mov r0, r4
	add sp, sp, #0x64
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_02099E34: .word UNK_021C8CC0
_02099E38: .word 0x00000B68
_02099E3C: .word 0x00000466

	arm_func_start FUN_02099E40
FUN_02099E40:
	ldr r2, [r0, #0x64]
	mov r3, #0x0
	cmp r2, #0x0
	beq _02099E88
	ldrsb r1, [r0, #0x73]
	cmp r1, #0x1
	bne _02099E6C
	ldr r0, [r2, #0x104]
	cmp r0, #0x0
	ldrneh r3, [r0, #0x4]
	b _02099E88
_02099E6C:
	cmp r1, #0x0
	beq _02099E7C
	cmp r1, #0x4
	bne _02099E88
_02099E7C:
	ldr r1, [r0, #0x44]
	ldr r0, [r2, #0xf8]
	sub r3, r1, r0
_02099E88:
	mov r0, r3
	bx lr

	arm_func_start FUN_02099E90
FUN_02099E90:
	stmdb sp!, {r4-r6,lr}
	mov r4, #0x0
	mov r5, r0
	bl FUN_02099FA8
	cmp r0, #0x0
	orrne r4, r4, #0x80
	bne _02099F60
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x40
	ldrsb r0, [r5, #0x73]
	orrne r4, r4, #0x20
	cmp r0, #0x1
	beq _02099ED0
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x4
	beq _02099F00
_02099ED0:
	bl OS_DisableInterrupts
	mov r6, r0
	mov r0, r5
	bl FUN_02099E40
	cmp r0, #0x0
	mov r0, r5
	orrgt r4, r4, #0x1
	bl FUN_020992A0
	cmp r0, #0x0
	mov r0, r6
	orrgt r4, r4, #0x8
	bl OS_RestoreInterrupts
_02099F00:
	ldrsb r0, [r5, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _02099F18
	cmp r0, #0x4
	movne r1, #0x0
_02099F18:
	cmp r1, #0x0
	beq _02099F60
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x4
	beq _02099F48
	ldrb r0, [r5, #0x8]
	cmp r0, #0x4
	beq _02099F48
	ands r0, r4, #0x1
	ldreqsh r0, [r5, #0x70]
	biceq r0, r0, #0x6
	streqh r0, [r5, #0x70]
_02099F48:
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x2
	bne _02099F60
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x4
	orreq r4, r4, #0x40
_02099F60:
	mov r0, r4
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_02099F6C
FUN_02099F6C:
	add r0, r0, #0x3
	bic r0, r0, #0x3
	bx lr

	arm_func_start FUN_02099F78
FUN_02099F78:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r1, r0
	ldr r0, _02099FA4 ; =UNK_021C8D34
	bl FUN_0209A008
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02099FA4: .word UNK_021C8D34

	arm_func_start FUN_02099FA8
FUN_02099FA8:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r1, r0
	cmp r1, #0x0
	ble _02099FCC
	ldr r0, _02099FEC ; =UNK_021C8D30
	bl FUN_0209A008
	cmp r0, #0x0
	bne _02099FDC
_02099FCC:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {lr}
	bx lr
_02099FDC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02099FEC: .word UNK_021C8D30

	arm_func_start FUN_02099FF0
FUN_02099FF0: ; 0x02099FF0
	ldr ip, _0209A000 ; =FUN_0209A034
	mov r1, r0
	ldr r0, _0209A004 ; =UNK_021C8D34
	bx r12
	.balign 4
_0209A000: .word FUN_0209A034
_0209A004: .word UNK_021C8D34

	arm_func_start FUN_0209A008
FUN_0209A008:
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _0209A02C
_0209A014:
	cmp r2, r1
	bxeq lr
	add r0, r2, #0x7c
	ldr r2, [r2, #0x7c]
	cmp r2, #0x0
	bne _0209A014
_0209A02C:
	mov r0, #0x0
	bx lr

	arm_func_start FUN_0209A034
FUN_0209A034: ; 0x0209A034
	stmdb sp!, {r4,lr}
	mov r4, r1
	bl FUN_0209A008
	cmp r0, #0x0
	ldrne r1, [r4, #0x7c]
	strne r1, [r0, #0x0]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_0209A054
FUN_0209A054: ; 0x0209A054
	ldr ip, _0209A064 ; =FUN_0209A034
	mov r1, r0
	ldr r0, _0209A068 ; =UNK_021C8D30
	bx r12
	.balign 4
_0209A064: .word FUN_0209A034
_0209A068: .word UNK_021C8D30

	arm_func_start FUN_0209A06C
FUN_0209A06C: ; 0x0209A06C
	ldr ip, _0209A07C ; =FUN_0209A084
	mov r1, r0
	ldr r0, _0209A080 ; =UNK_021C8D34
	bx r12
	.balign 4
_0209A07C: .word FUN_0209A084
_0209A080: .word UNK_021C8D34

	arm_func_start FUN_0209A084
FUN_0209A084: ; 0x0209A084
	ldr r2, [r0, #0x0]
	str r2, [r1, #0x7c]
	str r1, [r0, #0x0]
	bx lr

	arm_func_start FUN_0209A094
FUN_0209A094: ; 0x0209A094
	ldr ip, _0209A0A4 ; =FUN_0209A084
	mov r1, r0
	ldr r0, _0209A0A8 ; =UNK_021C8D30
	bx r12
	.balign 4
_0209A0A4: .word FUN_0209A084
_0209A0A8: .word UNK_021C8D30

	arm_func_start FUN_0209A0AC
FUN_0209A0AC: ; 0x0209A0AC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r9, r2
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x8]
	mov r0, #0x0
	mov r8, r3
	mvn r2, #0x0
	cmp r8, r2
	cmpeq r9, r2
	movne r11, #0x1
	mov r10, r1
	moveq r11, #0x0
	str r0, [sp, #0x4]
_0209A0E8:
	ldr r5, [sp, #0x4]
	ldr r7, [sp, #0x0]
	mov r6, r5
	cmp r10, #0x0
	bls _0209A128
_0209A0FC:
	ldrsh r1, [r7, #0x4]
	ldr r0, [r7, #0x0]
	orr r4, r1, #0xe0
	bl FUN_02099E90
	ands r0, r4, r0
	strh r0, [r7, #0x6]
	add r6, r6, #0x1
	addne r5, r5, #0x1
	cmp r6, r10
	add r7, r7, #0x8
	blo _0209A0FC
_0209A128:
	cmp r5, #0x0
	bgt _0209A160
	cmp r11, #0x0
	beq _0209A148
	mov r1, #0x0
	subs r0, r1, r9
	sbcs r0, r1, r8
	bge _0209A160
_0209A148:
	ldr r0, [sp, #0x8]
	bl OS_Sleep
	ldr r0, _0209A170 ; =0x0000020B
	subs r9, r9, r0
	sbc r8, r8, #0x0
	b _0209A0E8
_0209A160:
	mov r0, r5
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209A170: .word 0x0000020B

	arm_func_start FUN_0209A174
FUN_0209A174: ; 0x0209A174
	mov r2, r0, lsr #0x18
	strb r2, [r1, #0x0]
	mov r2, r0, lsr #0x10
	strb r2, [r1, #0x1]
	mov r2, r0, lsr #0x8
	strb r2, [r1, #0x2]
	strb r0, [r1, #0x3]
	bx lr

	arm_func_start FUN_0209A194
FUN_0209A194: ; 0x0209A194
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x18
	cmp r0, #0x2
	mov r4, r2
	addne sp, sp, #0x18
	movne r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	cmp r3, #0x10
	addcc sp, sp, #0x18
	movcc r0, #0x0
	ldmccia sp!, {r4,lr}
	bxcc lr
	mov r0, r1
	add r1, sp, #0xc
	mov r2, #0x4
	bl MI_CpuCopy8
	ldr r0, [sp, #0xc]
	add r1, sp, #0x10
	bl FUN_0209A174
	ldrb r1, [sp, #0x12]
	ldr r2, _0209A220 ; =UNK_0210620C
	mov r0, r4
	str r1, [sp, #0x0]
	ldrb r3, [sp, #0x11]
	mov r1, #0x10
	str r3, [sp, #0x4]
	ldrb r3, [sp, #0x10]
	str r3, [sp, #0x8]
	ldrb r3, [sp, #0x13]
	bl OS_SNPrintf
	mov r0, r4
	add sp, sp, #0x18
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209A220: .word UNK_0210620C

	arm_func_start FUN_0209A224
FUN_0209A224: ; 0x0209A224
	stmdb sp!, {r4,lr}
	mov r4, r1
	bl FUN_02099D28
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r2, r0, lsr #0x18
	mov r1, r0, lsr #0x8
	mov r3, r0, lsl #0x8
	mov r12, r0, lsl #0x18
	and r2, r2, #0xff
	and r0, r1, #0xff00
	and r1, r3, #0xff0000
	orr r0, r2, r0
	and r2, r12, #0xff000000
	orr r0, r1, r0
	orr r0, r2, r0
	str r0, [r4, #0x0]
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_0209A27C
FUN_0209A27C: ; 0x0209A27C
	stmdb sp!, {r0-r3}

	arm_func_start FUN_0209A280
FUN_0209A280: ; 0x0209A280
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _0209A2B0 ; =UNK_021C8D5C
	add r1, sp, #0x8
	mov r0, #0x2
	mov r3, #0x10
	bl FUN_0209A194
	ldr r0, _0209A2B0 ; =UNK_021C8D5C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_0209A2B0: .word UNK_021C8D5C

	arm_func_start THUNK_FUN_02099BC8
THUNK_FUN_02099BC8: ; 0x0209A2B4
	ldr ip, _0209A2BC ; =FUN_02099BC8
	bx r12
	.balign 4
_0209A2BC: .word FUN_02099BC8

	arm_func_start FUN_0209A2C0
FUN_0209A2C0: ; 0x0209A2C0
	stmdb sp!, {r4-r8,lr}
	ldr r1, [r0, #0xc]
	ldr ip, _0209A430 ; =UNK_021C8D6C
	cmp r1, #0x1
	moveq r1, #0x1
	movne r1, #0x0
	str r1, [r12, #0x0]
	ldr r6, [r0, #0x10]
	ldr r5, _0209A434 ; =FUN_0209A484
	mov r2, r6, lsr #0x18
	mov r1, r6, lsr #0x8
	mov r3, r6, lsl #0x8
	and r2, r2, #0xff
	and r1, r1, #0xff00
	mov r6, r6, lsl #0x18
	orr r1, r2, r1
	and r3, r3, #0xff0000
	orr r1, r3, r1
	and r2, r6, #0xff000000
	orr r1, r2, r1
	str r1, [r12, #0x4]
	ldr r7, [r0, #0x14]
	ldr r4, _0209A438 ; =FUN_0209A444
	mov r2, r7, lsr #0x18
	mov r1, r7, lsr #0x8
	mov r6, r7, lsl #0x8
	and r2, r2, #0xff
	and r1, r1, #0xff00
	mov r7, r7, lsl #0x18
	orr r1, r2, r1
	and r6, r6, #0xff0000
	and r2, r7, #0xff000000
	orr r1, r6, r1
	orr r1, r2, r1
	str r1, [r12, #0x8]
	ldr r1, [r0, #0x18]
	ldr r3, _0209A43C ; =UNK_021C8D40
	mov r7, r1, lsr #0x18
	mov r6, r1, lsr #0x8
	mov r8, r1, lsl #0x8
	and r7, r7, #0xff
	and r6, r6, #0xff00
	mov r1, r1, lsl #0x18
	orr r6, r7, r6
	and r8, r8, #0xff0000
	and r7, r1, #0xff000000
	orr r1, r8, r6
	orr r1, r7, r1
	str r1, [r12, #0xc]
	ldr r1, [r0, #0x1c]
	ldr r2, _0209A440 ; =UNK_021C8D3C
	mov r7, r1, lsr #0x18
	mov r6, r1, lsr #0x8
	mov r8, r1, lsl #0x8
	and r7, r7, #0xff
	and r6, r6, #0xff00
	mov r1, r1, lsl #0x18
	orr r6, r7, r6
	and r8, r8, #0xff0000
	and r7, r1, #0xff000000
	orr r1, r8, r6
	orr r1, r7, r1
	str r1, [r12, #0x10]
	ldr r1, [r0, #0x20]
	mov lr, #0x40
	mov r7, r1, lsr #0x18
	mov r6, r1, lsr #0x8
	mov r8, r1, lsl #0x8
	and r7, r7, #0xff
	and r6, r6, #0xff00
	mov r1, r1, lsl #0x18
	orr r6, r7, r6
	and r8, r8, #0xff0000
	and r7, r1, #0xff000000
	orr r1, r8, r6
	orr r1, r7, r1
	str r5, [r12, #0x18]
	str r4, [r12, #0x1c]
	str r1, [r12, #0x14]
	ldr r1, [r0, #0x4]
	str r1, [r3, #0x0]
	ldr r1, [r0, #0x8]
	str lr, [r12, #0x20]
	str r1, [r2, #0x0]
	ldr r1, [r0, #0x2c]
	str r1, [r12, #0x30]
	ldr r1, [r0, #0x30]
	mov r0, r12
	str r1, [r12, #0x34]
	bl FUN_02097834
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209A430: .word UNK_021C8D6C
_0209A434: .word FUN_0209A484
_0209A438: .word FUN_0209A444
_0209A43C: .word UNK_021C8D40
_0209A440: .word UNK_021C8D3C

	arm_func_start FUN_0209A444
FUN_0209A444: ; 0x0209A444
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r1, _0209A480 ; =UNK_021C8D3C
	ldr r2, [r0, #-0x4]
	ldr r3, [r1, #0x0]
	sub r1, r0, #0x4
	mov r0, #0x0
	blx r3
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209A480: .word UNK_021C8D3C

	arm_func_start FUN_0209A484
FUN_0209A484: ; 0x0209A484
	stmdb sp!, {r4,lr}
	ldr r1, _0209A4B0 ; =UNK_021C8D40
	add r4, r0, #0x4
	ldr r2, [r1, #0x0]
	mov r1, r4
	mov r0, #0x0
	blx r2
	cmp r0, #0x0
	strne r4, [r0], #0x4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209A4B0: .word UNK_021C8D40

	arm_func_start FUN_0209A4B4
FUN_0209A4B4: ; 0x0209A4B4
	cmp r0, #0x0
	mvneq r0, #0x0
	bxeq lr
	cmp r1, #0x3
	beq _0209A4D4
	cmp r1, #0x4
	beq _0209A4E8
	b _0209A4FC
_0209A4D4:
	ldrsb r0, [r0, #0x72]
	cmp r0, #0x1
	moveq r0, #0x0
	movne r0, #0x4
	bx lr
_0209A4E8:
	ands r1, r2, #0x4
	movne r1, #0x0
	strneb r1, [r0, #0x72]
	moveq r1, #0x1
	streqb r1, [r0, #0x72]
_0209A4FC:
	mov r0, #0x0
	bx lr

	arm_func_start FUN_0209A504
FUN_0209A504: ; 0x0209A504
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	mov r4, r1
	add r1, sp, #0x0
	add r2, sp, #0x4
	bl FUN_02098120
	cmp r0, #0x0
	addlt sp, sp, #0x8
	ldmltia sp!, {r4,lr}
	bxlt lr
	ldrh r1, [sp, #0x0]
	mov r2, r1, asr #0x8
	mov r1, r1, lsl #0x8
	and r2, r2, #0xff
	and r1, r1, #0xff00
	orr r1, r2, r1
	strh r1, [r4, #0x2]
	ldr r12, [sp, #0x4]
	mov r2, r12, lsr #0x18
	mov r1, r12, lsr #0x8
	mov r3, r12, lsl #0x8
	mov r12, r12, lsl #0x18
	and r2, r2, #0xff
	and r1, r1, #0xff00
	and r3, r3, #0xff0000
	orr r1, r2, r1
	and r2, r12, #0xff000000
	orr r1, r3, r1
	orr r1, r2, r1
	str r1, [r4, #0x4]
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_0209A588
FUN_0209A588: ; 0x0209A588
	ldr ip, _0209A590 ; =FUN_0209822C
	bx r12
	.balign 4
_0209A590: .word FUN_0209822C

	arm_func_start FUN_0209A594
FUN_0209A594: ; 0x0209A594
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r12, [r1, #0x0]
	ldr r0, [r0, #0x0]
	mov r2, r12, lsr #0x18
	mov r4, r0, lsr #0x18
	mov lr, r0, lsr #0x8
	mov r1, r12, lsr #0x8
	mov r5, r0, lsl #0x8
	mov r3, r12, lsl #0x8
	mov r0, r0, lsl #0x18
	mov r12, r12, lsl #0x18
	and r4, r4, #0xff
	and lr, lr, #0xff00
	and r2, r2, #0xff
	and r1, r1, #0xff00
	and r5, r5, #0xff0000
	orr r4, r4, lr
	and r3, r3, #0xff0000
	orr r1, r2, r1
	and lr, r0, #0xff000000
	orr r0, r5, r4
	and r2, r12, #0xff000000
	orr r1, r3, r1
	orr r0, lr, r0
	orr r1, r2, r1
	bl FUN_02099CEC
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209A60C
FUN_0209A60C: ; 0x0209A60C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_02099C78
	mov r2, r0, lsr #0x18
	mov r1, r0, lsr #0x8
	mov r3, r0, lsl #0x8
	mov r12, r0, lsl #0x18
	and r2, r2, #0xff
	and r0, r1, #0xff00
	and r1, r3, #0xff0000
	orr r0, r2, r0
	and r2, r12, #0xff000000
	orr r0, r1, r0
	orr r0, r2, r0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_0209A650
FUN_0209A650: ; 0x0209A650
	stmdb sp!, {r4-r6,lr}
	movs r5, r0
	mov r4, r1
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	bl FUN_02099C78
	cmp r5, #0x0
	ldrneh r1, [r5, #0x74]
	mov r2, r0, lsr #0x18
	mov r6, #0x8
	moveq r1, #0x0
	cmp r0, #0x0
	moveq r1, #0x0
	mov r1, r1, lsl #0x10
	mov r3, r1, lsr #0x10
	mov r5, r3, asr #0x8
	mov lr, r3, lsl #0x8
	strb r6, [r4, #0x0]
	mov r6, #0x2
	mov r1, r0, lsr #0x8
	mov r3, r0, lsl #0x8
	mov r12, r0, lsl #0x18
	and r0, r1, #0xff00
	and r2, r2, #0xff
	orr r0, r2, r0
	and r1, r3, #0xff0000
	and r5, r5, #0xff
	and lr, lr, #0xff00
	strb r6, [r4, #0x1]
	orr r3, r5, lr
	and r2, r12, #0xff000000
	orr r0, r1, r0
	strh r3, [r4, #0x2]
	orr r0, r2, r0
	str r0, [r4, #0x4]
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_0209A6EC
FUN_0209A6EC: ; 0x0209A6EC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl FUN_02099D88
	movs r4, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r0, _0209A7A4 ; =UNK_021C8DA4
	ldr r2, _0209A7A8 ; =0x00000101
	mov r1, #0x0
	bl MI_CpuFill8
	ldr r0, _0209A7A4 ; =UNK_021C8DA4
	ldr r2, _0209A7A8 ; =0x00000101
	mov r1, r5
	bl STD_CopyLString
	mov r1, r4, lsr #0x18
	mov r0, r4, lsr #0x8
	mov r2, r4, lsl #0x8
	mov r3, r4, lsl #0x18
	and r1, r1, #0xff
	and r0, r0, #0xff00
	and r2, r2, #0xff0000
	orr r0, r1, r0
	and r3, r3, #0xff000000
	orr r1, r2, r0
	ldr r5, _0209A7A4 ; =UNK_021C8DA4
	ldr r0, _0209A7AC ; =UNK_021C8D4C
	ldr ip, _0209A7B0 ; =UNK_021C8D44
	mov r4, #0x0
	ldr r2, _0209A7B4 ; =UNK_021C8D38
	orr r1, r3, r1
	mov lr, #0x2
	mov r3, #0x4
	str r5, [r0, #0x0]
	str r4, [r0, #0x4]
	strh lr, [r0, #0x8]
	strh r3, [r0, #0xa]
	str r12, [r0, #0xc]
	str r2, [r12, #0x0]
	str r4, [r12, #0x4]
	str r1, [r2, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209A7A4: .word UNK_021C8DA4
_0209A7A8: .word 0x00000101
_0209A7AC: .word UNK_021C8D4C
_0209A7B0: .word UNK_021C8D44
_0209A7B4: .word UNK_021C8D38

	arm_func_start thunk_FUN_0209996c
thunk_FUN_0209996c: ; 0x0209A7B8
	ldr ip, _0209A7C0 ; =FUN_0209996C
	bx r12
	.balign 4
_0209A7C0: .word FUN_0209996C

	arm_func_start thunk_FUN_020995dc
thunk_FUN_020995dc: ; 0x0209A7C4
	ldr ip, _0209A7CC ; =FUN_020995DC
	bx r12
	.balign 4
_0209A7CC: .word FUN_020995DC

	arm_func_start FUN_0209A7D0
FUN_0209A7D0: ; 0x0209A7D0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	ldr r5, [sp, #0x20]
	cmp r5, #0x0
	moveq r5, #0x0
	moveq r4, r5
	beq _0209A83C
	ldrh r4, [r5, #0x2]
	ldr r6, [r5, #0x4]
	mov r7, r4, asr #0x8
	mov r12, r4, lsl #0x8
	mov r4, r6, lsr #0x18
	mov lr, r6, lsr #0x8
	mov r5, r6, lsl #0x8
	mov r6, r6, lsl #0x18
	and r7, r7, #0xff
	and r12, r12, #0xff00
	orr r7, r7, r12
	and r4, r4, #0xff
	and lr, lr, #0xff00
	and r5, r5, #0xff0000
	orr r4, r4, lr
	mov r12, r7, lsl #0x10
	orr r4, r5, r4
	and r6, r6, #0xff000000
	mov r5, r12, lsr #0x10
	orr r4, r6, r4
_0209A83C:
	str r4, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r3, r5
	bl FUN_02099470
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_0209A858
FUN_0209A858: ; 0x0209A858
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	mov r12, #0x0
	str r12, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r3, r12
	bl FUN_02099470
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_0209A880
FUN_0209A880: ; 0x0209A880
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	add r12, sp, #0xc
	str r12, [sp, #0x0]
	str r3, [sp, #0x4]
	add r3, sp, #0x8
	bl FUN_02098CF4
	cmp r0, #0x0
	addlt sp, sp, #0x14
	ldmltia sp!, {lr}
	bxlt lr
	ldr r1, [sp, #0x18]
	cmp r1, #0x0
	addeq sp, sp, #0x14
	ldmeqia sp!, {lr}
	bxeq lr
	ldrh r2, [sp, #0x8]
	mov r3, r2, asr #0x8
	mov r2, r2, lsl #0x8
	and r3, r3, #0xff
	and r2, r2, #0xff00
	orr r2, r3, r2
	strh r2, [r1, #0x2]
	ldr lr, [sp, #0xc]
	mov r3, lr, lsr #0x18
	mov r2, lr, lsr #0x8
	mov r12, lr, lsl #0x8
	mov lr, lr, lsl #0x18
	and r3, r3, #0xff
	and r2, r2, #0xff00
	and r12, r12, #0xff0000
	orr r2, r3, r2
	and r3, lr, #0xff000000
	orr r2, r12, r2
	orr r2, r3, r2
	str r2, [r1, #0x4]
	add sp, sp, #0x14
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_0209A91C
FUN_0209A91C: ; 0x0209A91C
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	mov r12, #0x0
	str r12, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r3, r12
	bl FUN_02098CF4
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_0209A944
FUN_0209A944: ; 0x0209A944
	stmdb sp!, {r4,lr}
	ldrh r2, [r1, #0x2]
	ldr lr, [r1, #0x4]
	mov r4, r2, asr #0x8
	mov r1, r2, lsl #0x8
	mov r3, lr, lsr #0x18
	mov r2, lr, lsr #0x8
	mov r12, lr, lsl #0x8
	mov lr, lr, lsl #0x18
	and r4, r4, #0xff
	and r1, r1, #0xff00
	orr r1, r4, r1
	mov r1, r1, lsl #0x10
	and r3, r3, #0xff
	and r2, r2, #0xff00
	and r12, r12, #0xff0000
	orr r2, r3, r2
	and r3, lr, #0xff000000
	orr r2, r12, r2
	mov r1, r1, lsr #0x10
	orr r2, r3, r2
	bl FUN_020983B0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_0209A9A4
FUN_0209A9A4: ; 0x0209A9A4
	ldrh r1, [r1, #0x2]
	ldr ip, _0209A9CC ; =FUN_020984B4
	mov r2, r1, asr #0x8
	mov r1, r1, lsl #0x8
	and r2, r2, #0xff
	and r1, r1, #0xff00
	orr r1, r2, r1
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	bx r12
	.balign 4
_0209A9CC: .word FUN_020984B4

	arm_func_start FUN_0209A9D0
FUN_0209A9D0: ; 0x0209A9D0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r1, #0x1
	bne _0209A9F4
	ldr r0, _0209AA08 ; =UNK_021061DC
	bl FUN_02097F70
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209A9F4:
	ldr r0, _0209AA0C ; =UNK_021061C4
	bl FUN_02097F70
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209AA08: .word UNK_021061DC
_0209AA0C: .word UNK_021061C4

	arm_func_start FUN_0209AA10
FUN_0209AA10: ; 0x0209AA10
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldr r6, [r7, #0x4]
	ldr r5, [r6, #0x64]
	add r0, r5, #0xe0
	ldr r4, [r5, #0xc4]
	bl OS_LockMutex
	ldr r1, [r7, #0x10]
	cmp r1, #0x0
	beq _0209AA54
	mov r0, #0x1
	str r1, [r4, #0xc]
	bl CPS_SetSsl
	mov r0, #0x4
	strb r0, [r6, #0x73]
	b _0209AA68
_0209AA54:
	mov r0, #0x0
	strb r0, [r6, #0x73]
	bl CPS_SetSsl
	mov r0, #0x0
	str r0, [r4, #0xc]
_0209AA68:
	add r0, r5, #0xe0
	bl OS_UnlockMutex
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_0209AA80
FUN_0209AA80: ; 0x0209AA80
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	ldr r0, _0209AACC ; =FUN_0209AA10
	mov r1, r5
	mov r2, #0x1
	bl FUN_02097A98
	movs r1, r0
	addeq sp, sp, #0x4
	mvneq r0, #0x20
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	mov r0, r5
	str r4, [r1, #0x10]
	bl FUN_02097958
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209AACC: .word FUN_0209AA10

	arm_func_start FUN_0209AAD0
FUN_0209AAD0: ; 0x0209AAD0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl FUN_02099FA8
	cmp r0, #0x0
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldrsb r0, [r5, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _0209AB10
	cmp r0, #0x4
	movne r1, #0x0
_0209AB10:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	cmp r5, #0x0
	mov r1, #0x0
	beq _0209AB3C
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_0209AB3C:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x2
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r0, r5
	mov r1, r4
	bl FUN_0209AA80
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209AB80
FUN_0209AB80: ; 0x0209AB80
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	ldr r6, _0209ACC0 ; =CPSiRand32ctx
	mov r9, #0x0
	ldr r11, [r6, #0x8]
	ldr r2, [r6, #0x0]
	ldr r1, [r6, #0x4]
	umull r5, r4, r11, r2
	mla r4, r11, r1, r4
	ldr r10, [r6, #0xc]
	ldr r3, [r6, #0x10]
	mla r4, r10, r2, r4
	adds r5, r3, r5
	ldr r1, [r6, #0x14]
	umull r8, r7, r11, r5
	adc r4, r1, r4
	mla r7, r11, r4, r7
	mla r7, r10, r5, r7
	mov r2, r9, lsl #0x10
	adds r8, r3, r8
	str r5, [r6, #0x0]
	adc r5, r1, r7
	mov r3, r9, lsl #0x10
	orr r2, r2, r4, lsr #0x10
	str r4, [r6, #0x4]
	orr r3, r3, r5, lsr #0x10
	add r1, sp, #0x4
	mov r10, r0
	strh r2, [sp, #0x8]
	str r8, [r6, #0x0]
	str r5, [r6, #0x4]
	strh r3, [sp, #0xa]
	bl FUN_0209AD34
	cmp r0, #0x0
	ldrne r0, [sp, #0x4]
	addne sp, sp, #0xc
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	mov r0, #0x1
	ldr r6, _0209ACC4 ; =UNK_021C8F1C
	strb r0, [sp, #0x0]
	strb r0, [sp, #0x1]
	add r5, sp, #0x8
	mov r4, r9
	mov r11, r9
_0209AC34:
	mov r8, r11
	add r7, sp, #0x0
_0209AC3C:
	ldrb r0, [r7, #0x0]
	cmp r0, #0x0
	beq _0209AC80
	mov r0, r8, lsl #0x1
	ldrh r2, [r5, r0]
	ldr r1, [r6, r8, lsl #0x2]
	mov r0, r10
	bl FUN_0209ACC8
	str r0, [sp, #0x4]
	cmp r0, #0x0
	beq _0209AC74
	mvn r1, #0x0
	cmp r0, r1
	bne _0209AC9C
_0209AC74:
	mvn r1, #0x0
	cmp r0, r1
	streqb r4, [r7, #0x0]
_0209AC80:
	add r8, r8, #0x1
	cmp r8, #0x2
	add r7, r7, #0x1
	blt _0209AC3C
	add r9, r9, #0x1
	cmp r9, #0x3
	blt _0209AC34
_0209AC9C:
	ldr r1, [sp, #0x4]
	mvn r0, #0x0
	cmp r1, r0
	moveq r0, #0x0
	streq r0, [sp, #0x4]
	ldr r0, [sp, #0x4]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209ACC0: .word CPSiRand32ctx
_0209ACC4: .word UNK_021C8F1C

	arm_func_start FUN_0209ACC8
FUN_0209ACC8: ; 0x0209ACC8
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	movs r5, r1
	mov r6, r0
	mov r4, r2
	addeq sp, sp, #0x8
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	bl FUN_0209CB44
	bl FUN_0209CBE8
	mov r2, r5
	mov r0, #0x0
	mov r1, #0x35
	bl FUN_0209CB78
	mov r0, r6
	mov r2, r4
	mov r3, #0x0
	str r3, [sp, #0x0]
	mov r1, #0x1
	bl FUN_0209AE18
	mov r4, r0
	bl FUN_0209CB24
	mov r0, r4
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_0209AD34
FUN_0209AD34:
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r6, #0x0
	mov r8, r0
	mov r7, r1
	mov r5, r6
	add r4, sp, #0x0
_0209AD50:
	mov r0, r8
	mov r1, r4
	mov r6, r6, lsl #0x8
	bl FUN_0209ADE4
	ldr r2, [sp, #0x0]
	cmp r8, r2
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r8, r2
	cmp r0, #0xff
	bhi _0209ADB0
	cmp r5, #0x3
	beq _0209AD9C
	ldrb r1, [r2, #0x0]
	add r8, r2, #0x1
	cmp r1, #0x2e
	bne _0209ADB0
_0209AD9C:
	cmp r5, #0x3
	bne _0209ADC0
	ldrb r1, [r8, #0x0]
	cmp r1, #0x0
	beq _0209ADC0
_0209ADB0:
	add sp, sp, #0x8
	mov r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
_0209ADC0:
	add r5, r5, #0x1
	cmp r5, #0x4
	orr r6, r6, r0
	blt _0209AD50
	str r6, [r7, #0x0]
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_0209ADE4
FUN_0209ADE4: ; 0x0209ADE4
	str r0, [r1, #0x0]
	mov r12, #0x0
	mov r2, #0xa
_0209ADF0:
	ldrb r3, [r0, #0x0]
	sub r3, r3, #0x30
	and r3, r3, #0xff
	cmp r3, #0x9
	mlals r12, r2, r12, r3
	addls r0, r0, #0x1
	strls r0, [r1, #0x0]
	bls _0209ADF0
	mov r0, r12
	bx lr

	arm_func_start FUN_0209AE18
FUN_0209AE18: ; 0x0209AE18
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4c
	mov r9, r2
	mov r2, r9, asr #0x8
	mov r10, r1
	orr r1, r2, r9, lsl #0x8
	strh r1, [sp, #0x10]
	cmp r10, #0x20
	mov r5, #0x0
	movne r1, #0x1
	strneh r1, [sp, #0x12]
	ldreq r1, _0209B0C8 ; =0x00001001
	strh r5, [sp, #0x16]
	streqh r1, [sp, #0x12]
	mov r1, #0x100
	strh r1, [sp, #0x14]
	add r1, sp, #0x1c
	strh r5, [sp, #0x18]
	strh r5, [sp, #0x1a]
	str r5, [sp, #0xc]
	ldrb r6, [r0], #0x1
	str r3, [sp, #0x0]
	ldr r8, [sp, #0x70]
	add r2, r1, #0x1
	cmp r6, #0x0
	beq _0209AED8
	add r4, sp, #0x10
_0209AE84:
	cmp r6, #0x2e
	beq _0209AEB8
	sub r3, r2, r4
	cmp r3, #0x3c
	addge sp, sp, #0x4c
	mvnge r0, #0x0
	ldmgeia sp!, {r4-r11,lr}
	bxge lr
	strb r6, [r2], #0x1
	ldr r3, [sp, #0xc]
	add r3, r3, #0x1
	str r3, [sp, #0xc]
	b _0209AECC
_0209AEB8:
	ldr r3, [sp, #0xc]
	strb r3, [r1, #0x0]
	mov r1, r2
	str r5, [sp, #0xc]
	add r2, r2, #0x1
_0209AECC:
	ldrb r6, [r0], #0x1
	cmp r6, #0x0
	bne _0209AE84
_0209AED8:
	ldr r0, [sp, #0xc]
	mov r3, #0x0
	strb r0, [r1, #0x0]
	strb r3, [r2, #0x0]
	mov r0, r10, lsr #0x8
	strb r0, [r2, #0x1]
	strb r10, [r2, #0x2]
	strb r3, [r2, #0x3]
	mov r3, #0x1
	add r0, sp, #0x10
	add r1, r2, #0x5
	sub r1, r1, r0
	strb r3, [r2, #0x4]
	bl FUN_0209C030
	mov r6, #0x0
	bl OS_GetTick
	mov r5, r0, lsr #0x10
	mov r0, #0x2
	str r0, [sp, #0x8]
	mov r0, #0x1
	orr r5, r5, r1, lsl #0x10
	str r0, [sp, #0x4]
	mvn r11, #0x0
	b _0209B084
_0209AF38:
	bl FUN_0209BF9C
	cmp r0, #0x0
	bne _0209AF4C
	bl FUN_020A005C
	b _0209B084
_0209AF4C:
	add r0, sp, #0xc
	bl FUN_0209C638
	ldr r1, [sp, #0xc]
	cmp r1, #0xc
	bls _0209B07C
	ldrh r3, [r0, #0x0]
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	cmp r9, r2, lsr #0x10
	bne _0209B07C
	ldrb r2, [r0, #0x3]
	and r2, r2, #0xf
	cmp r2, #0x3
	moveq r6, r11
	beq _0209B07C
	cmp r2, #0x0
	bne _0209B07C
	ldrb r2, [r0, #0x4]
	add r4, r0, r1
	ldrb r1, [r0, #0x5]
	add r0, r0, #0xc
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	movs r1, r1, lsr #0x10
	sub r7, r1, #0x1
	beq _0209AFCC
_0209AFB8:
	bl FUN_0209B0D0
	cmp r7, #0x0
	add r0, r0, #0x4
	sub r7, r7, #0x1
	bne _0209AFB8
_0209AFCC:
	cmp r0, r4
	bhs _0209B07C
_0209AFD4:
	bl FUN_0209B0D0
	ldrb r7, [r0, #0x8]
	ldrb r1, [r0, #0x9]
	ldrb r3, [r0, #0x0]
	ldrb r2, [r0, #0x1]
	orr r1, r1, r7, lsl #0x8
	mov r1, r1, lsl #0x10
	orr r3, r2, r3, lsl #0x8
	mov r2, r1, lsr #0x10
	mov r1, r3, lsl #0x10
	cmp r10, r1, lsr #0x10
	bne _0209B06C
	cmp r10, #0xc
	beq _0209B04C
	add r1, r0, #0x6
	add r3, r1, r2
	add r4, r0, #0x8
	ldrb r1, [r1, r2]
	ldrb r0, [r3, #0x1]
	add r3, r4, r2
	ldrb r2, [r4, r2]
	orr r0, r0, r1, lsl #0x8
	ldrb r1, [r3, #0x1]
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	orr r0, r1, r2, lsl #0x8
	mov r1, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r6, r1, r0, lsr #0x10
	b _0209B07C
_0209B04C:
	cmp r2, r8
	ldrhi r6, [sp, #0x8]
	bhi _0209B07C
	ldr r1, [sp, #0x0]
	add r0, r0, #0xa
	bl MI_CpuCopy8
	ldr r6, [sp, #0x4]
	b _0209B07C
_0209B06C:
	add r1, r2, #0xa
	add r0, r0, r1
	cmp r0, r4
	blo _0209AFD4
_0209B07C:
	ldr r0, [sp, #0xc]
	bl FUN_0209C52C
_0209B084:
	ldr r0, _0209B0CC ; =UNK_021C8EFC
	ldr r0, [r0, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209B0B8
	cmp r6, #0x0
	bne _0209B0B8
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	sub r0, r0, r5
	cmp r0, #0xf
	blt _0209AF38
_0209B0B8:
	mov r0, r6
	add sp, sp, #0x4c
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209B0C8: .word 0x00001001
_0209B0CC: .word UNK_021C8EFC

	arm_func_start FUN_0209B0D0
FUN_0209B0D0:
	ldrb r2, [r0], #0x1
	cmp r2, #0x0
	bxeq lr
_0209B0DC:
	and r1, r2, #0xc0
	cmp r1, #0xc0
	addeq r0, r0, #0x1
	bxeq lr
	add r0, r0, r2
	ldrb r2, [r0], #0x1
	cmp r2, #0x0
	bne _0209B0DC
	bx lr

	arm_func_start FUN_0209B100
FUN_0209B100: ; 0x0209B100
	stmdb sp!, {r4,lr}
	bl FUN_0209CB44
	bl FUN_0209CBE8
	ldr r1, _0209B168 ; =UNK_021C8ED4
	mov r0, #0x44
	ldr r2, [r1, #0x0]
	mov r1, #0x43
	bl FUN_0209CB78
	ldr r4, _0209B16C ; =UNK_021C924A
	mov r1, #0x7
	mov r0, r4
	mov r2, #0x0
	bl FUN_0209B8E0
	mov r1, #0xff
	add r2, r0, #0x1
	strb r1, [r0, #0x0]
	mov r0, #0x0
	mov r1, #0x12c
	sub r3, r2, r4
	bl FUN_0209B8A0
	sub r1, r0, r4
	mov r0, r4
	bl FUN_0209C030
	bl FUN_0209CB24
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209B168: .word UNK_021C8ED4
_0209B16C: .word UNK_021C924A

	arm_func_start FUN_0209B170
FUN_0209B170:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r5, r0
	bl FUN_0209CB44
	bl FUN_0209CBE8
	cmp r4, #0x1
	bne _0209B1A8
	ldr r1, _0209B28C ; =UNK_021C8ED4
	mov r0, #0x44
	ldr r2, [r1, #0x0]
	mov r1, #0x43
	bl FUN_0209CB78
	b _0209B1B8
_0209B1A8:
	mov r0, #0x44
	mov r1, #0x43
	mvn r2, #0x0
	bl FUN_0209CB78
_0209B1B8:
	mov r6, #0x0
_0209B1BC:
	mov r0, r4
	bl FUN_0209B6BC
	mov r1, r6
	bl FUN_0209B2FC
	movs r7, r0
	bne _0209B1E0
	add r6, r6, #0x1
	cmp r6, #0x4
	blt _0209B1BC
_0209B1E0:
	bl FUN_0209CB24
	cmp r7, #0x2
	bne _0209B224
	ldr r0, _0209B290 ; =UNK_021C8F00
	mov r1, #0x3
	ldr r3, [r0, #0x0]
	ldr r2, _0209B294 ; =UNK_021C8EEC
	mov r3, r3, lsr #0x1
	str r3, [r5, #0x0]
	ldr r3, [r0, #0x0]
	add sp, sp, #0x4
	mul r1, r3, r1
	mov r1, r1, lsr #0x3
	str r1, [r2, #0x0]
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209B224:
	ldr r1, _0209B294 ; =UNK_021C8EEC
	cmp r4, #0x1
	ldr r0, [r1, #0x0]
	mov r0, r0, lsr #0x1
	str r0, [r1, #0x0]
	str r0, [r5, #0x0]
	beq _0209B24C
	cmp r4, #0x2
	beq _0209B270
	b _0209B27C
_0209B24C:
	cmp r0, #0x3c
	bhs _0209B27C
	mov r2, #0x1
	ldr r0, _0209B290 ; =UNK_021C8F00
	str r2, [r5, #0x0]
	ldr r0, [r0, #0x0]
	mov r0, r0, lsr #0x3
	str r0, [r1, #0x0]
	b _0209B27C
_0209B270:
	cmp r0, #0x3c
	movcc r0, #0x1
	strcc r0, [r5, #0x0]
_0209B27C:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209B28C: .word UNK_021C8ED4
_0209B290: .word UNK_021C8F00
_0209B294: .word UNK_021C8EEC

	arm_func_start FUN_0209B298
FUN_0209B298:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl FUN_0209CB44
	bl FUN_0209CBE8
	mov r0, #0x44
	mov r1, #0x43
	mvn r2, #0x0
	bl FUN_0209CB78
	mov r4, #0x0
_0209B2BC:
	bl FUN_0209B7D8
	mov r1, r4
	bl FUN_0209B2FC
	mov r5, r0
	cmp r5, #0x1
	beq _0209B2E0
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _0209B2BC
_0209B2E0:
	bl FUN_0209CB24
	cmp r5, #0x1
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209B2FC
FUN_0209B2FC: ; 0x0209B2FC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	add r2, r1, #0x1
	mov r1, #0xf
	mul r1, r2, r1
	str r1, [sp, #0x8]
	str r0, [sp, #0x0]
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	str r0, [sp, #0x4]
	orr r0, r0, r1, lsl #0x10
	mov r4, #0x0
	str r0, [sp, #0x4]
	mov r0, #0x3
	mov r9, r4
	ldr r5, _0209B698 ; =UNK_021C8F1C
	mov r7, #0x2
	mov r8, #0x1
	ldr fp, _0209B69C ; =UNK_021C8EE0
	ldr r6, _0209B6A0 ; =UNK_021C8ED0
	str r0, [sp, #0xc]
	b _0209B64C
_0209B354:
	bl FUN_0209BF9C
	cmp r0, #0x0
	bne _0209B368
	bl FUN_020A005C
	b _0209B64C
_0209B368:
	add r0, sp, #0x10
	bl FUN_0209C638
	mov r10, r0
	ldr r0, [sp, #0x10]
	cmp r0, #0xf0
	bls _0209B644
	ldrb r0, [r10, #0x0]
	cmp r0, #0x2
	bne _0209B644
	ldrh r1, [r10, #0x6]
	ldrh r2, [r10, #0x4]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r1, r0, lsl #0x10
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	orr r1, r0, r1, lsr #0x10
	ldr r0, [sp, #0x0]
	cmp r0, r1
	bne _0209B644
	ldr r1, _0209B6A4 ; =UNK_021C8F14
	add r0, r10, #0x1c
	bl FUN_0209F9A0
	cmp r0, #0x0
	bne _0209B644
	ldrb r3, [r10, #0x10]
	ldrb r0, [r10, #0x11]
	ldrb r2, [r10, #0x12]
	ldrb r1, [r10, #0x13]
	orr r0, r0, r3, lsl #0x8
	mov r0, r0, lsl #0x10
	orr r1, r1, r2, lsl #0x8
	mov r0, r0, lsr #0x10
	mov r2, r0, lsl #0x10
	mov r0, r1, lsl #0x10
	orr r0, r2, r0, lsr #0x10
	ldrb r2, [r10, #0xec]
	ldr r1, [sp, #0x10]
	ldr r4, [sp, #0xc]
	add r1, r10, r1
	cmp r2, #0x63
	bne _0209B644
	ldrb r2, [r10, #0xed]
	cmp r2, #0x82
	bne _0209B644
	ldrb r2, [r10, #0xee]
	cmp r2, #0x53
	bne _0209B644
	add r2, r10, #0xf0
	ldrb r3, [r10, #0xef]
	cmp r3, #0x63
	bne _0209B644
	b _0209B630
_0209B448:
	cmp r3, #0x0
	beq _0209B630
	cmp r3, #0x33
	bgt _0209B48C
	cmp r3, #0x33
	bge _0209B588
	cmp r3, #0x6
	bgt _0209B624
	cmp r3, #0x1
	blt _0209B624
	cmp r3, #0x1
	beq _0209B4AC
	cmp r3, #0x3
	beq _0209B4E0
	cmp r3, #0x6
	beq _0209B514
	b _0209B624
_0209B48C:
	cmp r3, #0x35
	bgt _0209B4A0
	cmp r3, #0x35
	beq _0209B5C0
	b _0209B624
_0209B4A0:
	cmp r3, #0x36
	beq _0209B5F0
	b _0209B624
_0209B4AC:
	ldrb lr, [r2, #0x1]
	ldrb r12, [r2, #0x2]
	ldrb r10, [r2, #0x3]
	ldrb r3, [r2, #0x4]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r3, r10, r3, lsr #0x10
	str r3, [r6, #0x0]
	b _0209B624
_0209B4E0:
	ldrb lr, [r2, #0x1]
	ldrb r12, [r2, #0x2]
	ldrb r10, [r2, #0x3]
	ldrb r3, [r2, #0x4]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r3, r10, r3, lsr #0x10
	str r3, [r11, #0x0]
	b _0209B624
_0209B514:
	ldrb r3, [r2, #0x0]
	cmp r3, #0x8
	strcc r9, [r5, #0x4]
	blo _0209B554
	ldrb lr, [r2, #0x5]
	ldrb r12, [r2, #0x6]
	ldrb r10, [r2, #0x7]
	ldrb r3, [r2, #0x8]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r3, r10, r3, lsr #0x10
	str r3, [r5, #0x4]
_0209B554:
	ldrb lr, [r2, #0x1]
	ldrb r12, [r2, #0x2]
	ldrb r10, [r2, #0x3]
	ldrb r3, [r2, #0x4]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r3, r10, r3, lsr #0x10
	str r3, [r5, #0x0]
	b _0209B624
_0209B588:
	ldrb lr, [r2, #0x1]
	ldrb r12, [r2, #0x2]
	ldrb r10, [r2, #0x3]
	ldrb r3, [r2, #0x4]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r10, r10, r3, lsr #0x10
	ldr r3, _0209B6A8 ; =UNK_021C8F00
	str r10, [r3, #0x0]
	b _0209B624
_0209B5C0:
	ldrb r3, [r2, #0x1]
	cmp r3, #0x2
	beq _0209B5E0
	cmp r3, #0x5
	ldreq r3, _0209B6AC ; =UNK_021C8F04
	moveq r4, r7
	streq r0, [r3, #0x0]
	b _0209B624
_0209B5E0:
	ldr r3, _0209B6B0 ; =UNK_021C8EE8
	mov r4, r8
	str r0, [r3, #0x0]
	b _0209B624
_0209B5F0:
	ldrb lr, [r2, #0x1]
	ldrb r12, [r2, #0x2]
	ldrb r10, [r2, #0x3]
	ldrb r3, [r2, #0x4]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r10, r10, r3, lsr #0x10
	ldr r3, _0209B6B4 ; =UNK_021C8ED4
	str r10, [r3, #0x0]
_0209B624:
	ldrb r3, [r2, #0x0]
	add r3, r3, #0x1
	add r2, r2, r3
_0209B630:
	cmp r2, r1
	bhs _0209B644
	ldrb r3, [r2], #0x1
	cmp r3, #0xff
	bne _0209B448
_0209B644:
	ldr r0, [sp, #0x10]
	bl FUN_0209C52C
_0209B64C:
	ldr r0, _0209B6B8 ; =UNK_021C8EFC
	ldr r0, [r0, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209B688
	cmp r4, #0x0
	bne _0209B688
	bl OS_GetTick
	mov r2, r0, lsr #0x10
	ldr r0, [sp, #0x4]
	orr r2, r2, r1, lsl #0x10
	sub r1, r2, r0
	ldr r0, [sp, #0x8]
	cmp r1, r0
	blt _0209B354
_0209B688:
	mov r0, r4
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209B698: .word UNK_021C8F1C
_0209B69C: .word UNK_021C8EE0
_0209B6A0: .word UNK_021C8ED0
_0209B6A4: .word UNK_021C8F14
_0209B6A8: .word UNK_021C8F00
_0209B6AC: .word UNK_021C8F04
_0209B6B0: .word UNK_021C8EE8
_0209B6B4: .word UNK_021C8ED4
_0209B6B8: .word UNK_021C8EFC

	arm_func_start FUN_0209B6BC
FUN_0209B6BC: ; 0x0209B6BC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r4, _0209B7CC ; =UNK_021C924A
	mov r5, r0
	add r2, sp, #0x0
	mov r0, r4
	mov r1, #0x3
	bl FUN_0209B8E0
	mov r12, r0
	cmp r5, #0x0
	bne _0209B790
	mov r0, #0x32
	strb r0, [r12, #0x0]
	mov r0, #0x4
	ldr r3, _0209B7D0 ; =UNK_021C8EE8
	strb r0, [r12, #0x1]
	ldr r1, [r3, #0x0]
	mov lr, #0x36
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, asr #0x8
	strb r1, [r12, #0x2]
	ldr r1, [r3, #0x0]
	ldr r2, _0209B7D4 ; =UNK_021C8ED4
	mov r1, r1, lsr #0x10
	strb r1, [r12, #0x3]
	ldr r1, [r3, #0x0]
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, asr #0x8
	strb r1, [r12, #0x4]
	ldr r1, [r3, #0x0]
	strb r1, [r12, #0x5]
	strb lr, [r12, #0x6]
	strb r0, [r12, #0x7]
	ldr r0, [r2, #0x0]
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #0x8
	strb r0, [r12, #0x8]
	ldr r0, [r2, #0x0]
	mov r0, r0, lsr #0x10
	strb r0, [r12, #0x9]
	ldr r0, [r2, #0x0]
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #0x8
	strb r0, [r12, #0xa]
	ldr r0, [r2, #0x0]
	strb r0, [r12, #0xb]
	add r12, r12, #0xc
_0209B790:
	add r2, r12, #0x1
	mov lr, #0xff
	sub r3, r2, r4
	mov r0, #0x0
	mov r1, #0x12c
	strb lr, [r12, #0x0]
	bl FUN_0209B8A0
	mov r1, r0
	mov r0, r4
	sub r1, r1, r4
	bl FUN_0209C030
	ldr r0, [sp, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209B7CC: .word UNK_021C924A
_0209B7D0: .word UNK_021C8EE8
_0209B7D4: .word UNK_021C8ED4

	arm_func_start FUN_0209B7D8
FUN_0209B7D8: ; 0x0209B7D8
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldr r4, _0209B898 ; =UNK_021C924A
	add r2, sp, #0x0
	mov r0, r4
	mov r1, #0x1
	bl FUN_0209B8E0
	ldr r1, _0209B89C ; =UNK_021C8EE8
	mov r12, r0
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	beq _0209B85C
	mov r0, #0x32
	strb r0, [r12, #0x0]
	mov r0, #0x4
	strb r0, [r12, #0x1]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #0x8
	strb r0, [r12, #0x2]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsr #0x10
	strb r0, [r12, #0x3]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #0x8
	strb r0, [r12, #0x4]
	ldr r0, [r1, #0x0]
	strb r0, [r12, #0x5]
	add r12, r12, #0x6
_0209B85C:
	add r2, r12, #0x1
	mov lr, #0xff
	sub r3, r2, r4
	mov r0, #0x0
	mov r1, #0x12c
	strb lr, [r12, #0x0]
	bl FUN_0209B8A0
	mov r1, r0
	mov r0, r4
	sub r1, r1, r4
	bl FUN_0209C030
	ldr r0, [sp, #0x0]
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209B898: .word UNK_021C924A
_0209B89C: .word UNK_021C8EE8

	arm_func_start FUN_0209B8A0
FUN_0209B8A0: ; 0x0209B8A0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r12, r0
	mov r5, r2
	cmp r3, r1
	bhs _0209B8D0
	sub r4, r1, r3
	mov r0, r5
	mov r1, r12
	mov r2, r4
	bl MI_CpuFill8
	add r5, r5, r4
_0209B8D0:
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209B8E0
FUN_0209B8E0: ; 0x0209B8E0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	mov r4, r2
	mov r1, #0x0
	mov r2, #0xec
	mov r6, r0
	bl MI_CpuFill8
	ldr r0, _0209BA5C ; =0x00000101
	mov r1, #0x6
	strh r0, [r6, #0x0]
	ldr r0, _0209BA60 ; =CPSiRand32ctx
	strb r1, [r6, #0x2]
	ldr r3, [r0, #0x8]
	ldr r2, [r0, #0x0]
	ldr r1, [r0, #0x4]
	umull lr, r12, r3, r2
	mla r12, r3, r1, r12
	ldr r1, [r0, #0xc]
	ldr r7, [r0, #0x10]
	mla r12, r1, r2, r12
	adds r3, r7, lr
	ldr r1, [r0, #0x14]
	str r3, [r0, #0x0]
	adc r1, r1, r12
	str r1, [r0, #0x4]
	mov r0, r1, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	cmp r4, #0x0
	mov r2, r3, asr #0x8
	mov r0, r1, lsl #0x10
	strne r1, [r4, #0x0]
	mov r1, r0, lsr #0x10
	orr r2, r2, r3, lsl #0x8
	mov r0, r1, asr #0x8
	strh r2, [r6, #0x4]
	orr r0, r0, r1, lsl #0x8
	strh r0, [r6, #0x6]
	ldr r2, _0209BA64 ; =UNK_021C8F04
	ldr r0, _0209BA68 ; =UNK_021C8F14
	ldr r1, [r2, #0x0]
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r3, r1, lsr #0x10
	mov r1, r3, asr #0x8
	orr r1, r1, r3, lsl #0x8
	strh r1, [r6, #0xc]
	ldr r2, [r2, #0x0]
	add r1, r6, #0x1c
	mov r2, r2, lsl #0x10
	mov r3, r2, lsr #0x10
	mov r2, r3, asr #0x8
	orr r3, r2, r3, lsl #0x8
	mov r2, #0x6
	strh r3, [r6, #0xe]
	bl MI_CpuCopy8
	ldr r0, _0209BA6C ; =0x00008263
	ldr r1, _0209BA70 ; =0x00006353
	strh r0, [r6, #0xec]
	strh r1, [r6, #0xee]
	ldr r0, _0209BA74 ; =0x00000135
	mov r1, #0x7
	strh r0, [r6, #0xf0]
	strb r5, [r6, #0xf2]
	mov r0, #0x3d
	strb r0, [r6, #0xf3]
	strb r1, [r6, #0xf4]
	mov r3, #0x1
	ldr r0, _0209BA68 ; =UNK_021C8F14
	add r1, r6, #0xf6
	mov r2, #0x6
	strb r3, [r6, #0xf5]
	bl MI_CpuCopy8
	mov r1, #0xc
	strb r1, [r6, #0xfc]
	mov r2, #0xa
	ldr r0, _0209BA78 ; =UNK_02106224
	add r1, r6, #0xfe
	strb r2, [r6, #0xfd]
	bl MI_CpuCopy8
	mov r1, #0x37
	strb r1, [r6, #0x108]
	mov r2, #0x3
	ldr r0, _0209BA7C ; =0x0000010D
	strb r2, [r6, #0x109]
	mov r1, #0x1
	strb r1, [r6, #0x10a]
	strb r2, [r6, #0x10b]
	mov r1, #0x6
	strb r1, [r6, #0x10c]
	add r0, r6, r0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209BA5C: .word 0x00000101
_0209BA60: .word CPSiRand32ctx
_0209BA64: .word UNK_021C8F04
_0209BA68: .word UNK_021C8F14
_0209BA6C: .word 0x00008263
_0209BA70: .word 0x00006353
_0209BA74: .word 0x00000135
_0209BA78: .word UNK_02106224
_0209BA7C: .word 0x0000010D

	arm_func_start FUN_0209BA80
FUN_0209BA80: ; 0x0209BA80
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x54
	ldr r3, _0209BE40 ; =UNK_021C8EF8
	mov r1, #0x0
	ldr r0, _0209BE44 ; =UNK_021C8FD8
	mov r2, #0x64
	str r1, [r3, #0x0]
	bl MI_CpuFill8
	ldr r0, _0209BE44 ; =UNK_021C8FD8
	mov r3, #0x180
	ldr r2, _0209BE48 ; =UNK_021C93A0
	ldr r1, _0209BE4C ; =UNK_021C9220
	str r3, [r0, #0x3c]
	str r2, [r0, #0x40]
	str r3, [r0, #0x48]
	str r1, [r0, #0x4c]
	bl FUN_0209CC28
	mov r11, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x4c]
	mov r1, r0
	ldr r0, _0209BE50 ; =UNK_021C8EC0
	ldr r5, [sp, #0x0]
	str r1, [r0, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x10]
	mov r0, r5
	str r0, [sp, #0x34]
	str r0, [sp, #0x3c]
	mov r0, #0x3
	str r0, [sp, #0x1c]
	mov r0, r5
	str r0, [sp, #0x30]
	str r0, [sp, #0x28]
	str r0, [sp, #0x24]
	str r0, [sp, #0x20]
	str r0, [sp, #0xc]
	mov r0, #0x69
	str r0, [sp, #0x44]
	mov r0, #0x3e8
	mov r6, r11
	mov r4, r11
	mov r10, r11
	str r11, [sp, #0x14]
	str r11, [sp, #0x18]
	str r11, [sp, #0x38]
	str r11, [sp, #0x2c]
	str r11, [sp, #0x40]
	str r11, [sp, #0x48]
	str r0, [sp, #0x8]
_0209BB50:
	ldr r0, [sp, #0x8]
	bl OS_Sleep
	ldr r0, _0209BE40 ; =UNK_021C8EF8
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0209BE14
	bl OS_GetTick
	mov r9, r0, lsr #0x10
	ldr r0, _0209BE54 ; =UNK_021C8EFC
	orr r9, r9, r1, lsl #0x10
	ldr r0, [r0, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209BC8C
	ldr r0, [sp, #0x4c]
	subs r0, r0, #0x1
	str r0, [sp, #0x4c]
	bne _0209BCA4
	ldr r0, _0209BE58 ; =UNK_021C8EC4
	ldr r0, [r0, #0x0]
	ands r0, r0, #0x1
	beq _0209BBBC
	cmp r11, #0x0
	bne _0209BCA4
	bl FUN_0209BE78
	ldr r11, [sp, #0xc]
	b _0209BCA4
_0209BBBC:
	cmp r11, #0x3
	addls pc, pc, r11, lsl #0x2
	b _0209BCA4
_0209BBC8:
	b _0209BBD8
_0209BBCC:
	b _0209BC28
_0209BBD0:
	b _0209BC4C
_0209BBD4:
	b _0209BCA4
_0209BBD8:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ldrne r1, [sp, #0x10]
	ldrne r0, _0209BE50 ; =UNK_021C8EC0
	strne r1, [r0, #0x0]
	ldrne r0, [sp, #0x14]
	strne r0, [sp, #0x4]
	bl FUN_0209B298
	cmp r0, #0x0
	beq _0209BC14
	ldr r1, [sp, #0x18]
	add r0, sp, #0x4c
	bl FUN_0209B170
	cmp r0, #0x0
	bne _0209BC20
_0209BC14:
	bl FUN_0209BE78
	ldr r11, [sp, #0x1c]
	b _0209BCA4
_0209BC20:
	ldr r11, [sp, #0x20]
	b _0209BCA4
_0209BC28:
	ldr r1, [sp, #0x24]
	add r0, sp, #0x4c
	bl FUN_0209B170
	cmp r0, #0x0
	bne _0209BCA4
	ldr r0, [sp, #0x4c]
	cmp r0, #0x3c
	ldrcc r11, [sp, #0x10]
	b _0209BCA4
_0209BC4C:
	ldr r1, [sp, #0x10]
	add r0, sp, #0x4c
	bl FUN_0209B170
	cmp r0, #0x0
	ldrne r11, [sp, #0x28]
	bne _0209BCA4
	ldr r0, [sp, #0x4c]
	cmp r0, #0x3c
	bhs _0209BCA4
	ldr r0, [sp, #0x1c]
	bl FUN_020A0098
	ldr r0, [sp, #0x30]
	ldr r11, [sp, #0x2c]
	str r0, [sp, #0x4c]
	str r0, [sp, #0x0]
	b _0209BCA4
_0209BC8C:
	ldr r0, [sp, #0x34]
	bl FUN_020A0098
	ldr r0, [sp, #0x3c]
	ldr r11, [sp, #0x38]
	str r0, [sp, #0x4c]
	str r0, [sp, #0x0]
_0209BCA4:
	ldr r1, [sp, #0x40]
	ldr r0, _0209BE5C ; =UNK_021C8F78
_0209BCAC:
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _0209BCD4
	ldrh r2, [r0, #0xa]
	sub r2, r9, r2
	mov r2, r2, lsl #0x10
	mov r3, r2, asr #0x10
	ldr r2, _0209BE60 ; =0x000003BD
	cmp r3, r2
	strgt r6, [r0, #0x0]
_0209BCD4:
	add r0, r0, #0xc
	add r1, r1, #0x1
	cmp r1, #0x8
	blt _0209BCAC
	ldr r0, _0209BE64 ; =UNK_021C8EE0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0209BD10
	ldr r1, [sp, #0x0]
	subs r1, r1, #0x1
	str r1, [sp, #0x0]
	bne _0209BD10
	bl FUN_0209F338
	ldr r0, [sp, #0x44]
	str r0, [sp, #0x0]
_0209BD10:
	ldr r0, _0209BE68 ; =OSi_ThreadInfo
	ldr r7, [r0, #0x8]
	cmp r7, #0x0
	beq _0209BDAC
_0209BD20:
	ldr r0, [r7, #0xa4]
	cmp r0, #0x0
	beq _0209BDA0
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0209BDA0
	ldrb r2, [r0, #0x8]
	cmp r2, #0x3
	bne _0209BD6C
	ldr r1, [r0, #0x10]
	sub r1, r9, r1
	cmp r1, #0x27
	ble _0209BD6C
	strb r5, [r0, #0x8]
	ldrh r1, [r0, #0x1a]
	strh r1, [r0, #0x18]
	ldr r1, [r0, #0x20]
	str r1, [r0, #0x1c]
	b _0209BDA0
_0209BD6C:
	cmp r2, #0x2
	bne _0209BDA0
	ldr r1, [r0, #0x10]
	sub r1, r9, r1
	cmp r1, #0x27
	ble _0209BDA0
	ldr r1, [r0, #0x4]
	cmp r1, #0x1
	bne _0209BDA0
	strb r4, [r0, #0x8]
	str r4, [r0, #0x4]
	ldr r0, [r0, #0x0]
	bl OS_WakeupThreadDirect
_0209BDA0:
	ldr r7, [r7, #0x68]
	cmp r7, #0x0
	bne _0209BD20
_0209BDAC:
	ldr r7, [sp, #0x48]
	ldr r8, _0209BE6C ; =UNK_021C9520
_0209BDB4:
	ldrh r0, [r8, #0x4]
	cmp r0, #0x0
	beq _0209BDE4
	ldr r0, [r8, #0x2c]
	sub r0, r9, r0
	cmp r0, #0xef
	ble _0209BDE4
	ldr r1, _0209BE70 ; =CPSiFree
	ldr r0, [r8, #0x34]
	ldr r1, [r1, #0x0]
	blx r1
	strh r10, [r8, #0x4]
_0209BDE4:
	add r8, r8, #0x38
	add r7, r7, #0x1
	cmp r7, #0x8
	blt _0209BDB4
	mov r0, r9
	bl CPSi_SslPeriodical
	ldr r0, _0209BE74 ; =UNK_021C8EF0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0209BB50
	blx r0
	b _0209BB50
_0209BE14:
	ldr r0, _0209BE58 ; =UNK_021C8EC4
	ldr r0, [r0, #0x0]
	ands r0, r0, #0x1
	bne _0209BE30
	cmp r11, #0x3
	beq _0209BE30
	bl FUN_0209B100
_0209BE30:
	bl FUN_0209CC10
	add sp, sp, #0x54
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209BE40: .word UNK_021C8EF8
_0209BE44: .word UNK_021C8FD8
_0209BE48: .word UNK_021C93A0
_0209BE4C: .word UNK_021C9220
_0209BE50: .word UNK_021C8EC0
_0209BE54: .word UNK_021C8EFC
_0209BE58: .word UNK_021C8EC4
_0209BE5C: .word UNK_021C8F78
_0209BE60: .word 0x000003BD
_0209BE64: .word UNK_021C8EE0
_0209BE68: .word OSi_ThreadInfo
_0209BE6C: .word UNK_021C9520
_0209BE70: .word CPSiFree
_0209BE74: .word UNK_021C8EF0

	arm_func_start FUN_0209BE78
FUN_0209BE78: ; 0x0209BE78
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r0, _0209BF3C ; =UNK_021C8ECC
	ldr r0, [r0, #0x0]
	blx r0
	ldr r0, _0209BF40 ; =UNK_021C8F04
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	bl FUN_0209F338
	mov r0, #0x64
	bl OS_Sleep
	ldr r0, _0209BF40 ; =UNK_021C8F04
	ldr r0, [r0, #0x0]
	bl FUN_0209F338
	bl OS_GetTick
	mov r4, r0, lsr #0x10
	orr r4, r4, r1, lsl #0x10
	ldr r6, _0209BF44 ; =UNK_021C8EAC
	mov r7, #0x64
	ldr r5, _0209BF48 ; =UNK_021C8EFC
	b _0209BF00
_0209BED8:
	ldrb r0, [r6, #0x0]
	cmp r0, #0x0
	beq _0209BEF8
	mov r0, #0x4
	bl FUN_020A0098
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209BEF8:
	mov r0, r7
	bl OS_Sleep
_0209BF00:
	ldr r0, [r5, #0x0]
	blx r0
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	sub r0, r0, r4
	cmp r0, #0x17
	blt _0209BED8
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209BF3C: .word UNK_021C8ECC
_0209BF40: .word UNK_021C8F04
_0209BF44: .word UNK_021C8EAC
_0209BF48: .word UNK_021C8EFC

	arm_func_start FUN_0209BF4C
FUN_0209BF4C: ; 0x0209BF4C
	stmdb sp!, {r4,lr}
	ldr r0, _0209BF98 ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r4, [r0, #0xa4]
	cmp r4, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r1, [r4, #0x60]
	cmp r1, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r2, #0x0
	ldr r0, [r4, #0x5c]
	mov r3, r2
	bl FUN_0209C0E8
	mov r0, #0x0
	str r0, [r4, #0x60]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209BF98: .word OSi_ThreadInfo

	arm_func_start FUN_0209BF9C
FUN_0209BF9C:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _0209C02C ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xa4]
	cmp r0, #0x0
	beq _0209C01C
	ldrb r1, [r0, #0x9]
	cmp r1, #0x0
	beq _0209BFD4
	bl CPSi_SslGetLength
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209BFD4:
	ldr r1, [r0, #0x44]
	cmp r1, #0x0
	bne _0209BFFC
	ldrb r0, [r0, #0x8]
	cmp r0, #0x4
	beq _0209BFFC
	add r0, r0, #0xf6
	and r0, r0, #0xff
	cmp r0, #0x1
	bhi _0209C00C
_0209BFFC:
	add sp, sp, #0x4
	mov r0, r1
	ldmia sp!, {lr}
	bx lr
_0209C00C:
	add sp, sp, #0x4
	mvn r0, #0x0
	ldmia sp!, {lr}
	bx lr
_0209C01C:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209C02C: .word OSi_ThreadInfo

	arm_func_start FUN_0209C030
FUN_0209C030:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r3, _0209C0E4 ; =OSi_ThreadInfo
	mov r2, r0
	ldr r4, [r3, #0x4]
	mov r3, r1
	ldr r5, [r4, #0xa4]
	cmp r5, #0x0
	beq _0209C0D4
	ldr r4, [r5, #0x60]
	cmp r4, #0x0
	beq _0209C0BC
	ldr r0, [r5, #0x5c]
	mov r1, r4
	bl FUN_0209C0E8
	ldr r1, [r5, #0x60]
	mov r4, r0
	cmp r4, r1
	movcs r0, #0x0
	strcs r0, [r5, #0x60]
	addcs sp, sp, #0x4
	subcs r0, r4, r1
	ldmcsia sp!, {r4-r5,lr}
	bxcs lr
	ldr r0, [r5, #0x5c]
	sub r2, r1, r4
	add r1, r0, r4
	bl memmove
	ldr r1, [r5, #0x60]
	add sp, sp, #0x4
	sub r1, r1, r4
	mov r0, #0x0
	str r1, [r5, #0x60]
	ldmia sp!, {r4-r5,lr}
	bx lr
_0209C0BC:
	mov r2, #0x0
	mov r3, r2
	bl FUN_0209C0E8
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_0209C0D4:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209C0E4: .word OSi_ThreadInfo

	arm_func_start FUN_0209C0E8
FUN_0209C0E8:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr ip, _0209C1CC ; =OSi_ThreadInfo
	mov r7, r1
	ldr r12, [r12, #0x4]
	mov r6, r2
	ldr r4, [r12, #0xa4]
	mov r5, r3
	cmp r4, #0x0
	beq _0209C1BC
	ldrb r12, [r4, #0x8]
	cmp r12, #0xa
	bne _0209C14C
	cmp r7, #0x0
	beq _0209C12C
	mov r2, r4
	bl FUN_0209EB00
_0209C12C:
	cmp r5, #0x0
	beq _0209C144
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_0209EB00
_0209C144:
	add r0, r7, r5
	b _0209C1A4
_0209C14C:
	cmp r12, #0xb
	bne _0209C184
	cmp r7, #0x0
	beq _0209C164
	mov r2, r4
	bl FUN_0209EC40
_0209C164:
	cmp r5, #0x0
	beq _0209C17C
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_0209EC40
_0209C17C:
	add r0, r7, r5
	b _0209C1A4
_0209C184:
	ldrb r12, [r4, #0x9]
	cmp r12, #0x0
	beq _0209C19C
	str r4, [sp, #0x0]
	bl CPSi_SslWrite2
	b _0209C1A4
_0209C19C:
	str r4, [sp, #0x0]
	bl CPSi_TcpWrite2Raw
_0209C1A4:
	ldr r1, _0209C1D0 ; =UNK_021C8EA8
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
_0209C1BC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209C1CC: .word OSi_ThreadInfo
_0209C1D0: .word UNK_021C8EA8

	arm_func_start CPSi_TcpWrite2Raw
CPSi_TcpWrite2Raw:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x1c
	mov r4, #0x0
	mov r10, r0
	ldr r8, [sp, #0x40]
	mov r0, r4
	str r4, [sp, #0xc]
	mov r9, r1
	mov r11, r2
	str r3, [sp, #0x8]
	mov r6, r4
	str r0, [r8, #0x34]
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	str r0, [sp, #0x10]
	orr r0, r0, r1, lsl #0x10
	str r0, [sp, #0x10]
	mov r0, r6
	str r0, [sp, #0x18]
	mov r0, #0x1
	ldr r4, _0209C3EC ; =UNK_021C8EFC
	str r0, [sp, #0x14]
	b _0209C39C
_0209C230:
	ldr r7, [r8, #0x28]
	ldr r3, [sp, #0x8]
	str r8, [sp, #0x0]
	mov r0, r10
	mov r1, r9
	mov r2, r11
	str r6, [sp, #0x4]
	bl FUN_0209C3F0
	bl OS_GetTick
	mov r5, r0, lsr #0x10
	orr r5, r5, r1, lsl #0x10
_0209C25C:
	bl FUN_020A005C
	ldr r0, [r4, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209C2B8
	ldrb r0, [r8, #0x8]
	cmp r0, #0x4
	bne _0209C2B8
	ldr r1, [r8, #0x28]
	ldr r0, [r8, #0x30]
	cmp r1, r0
	beq _0209C2B8
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	sub r0, r0, r5
	cmp r0, #0xf
	bge _0209C2B8
	cmp r6, #0x0
	beq _0209C25C
	ldrh r0, [r8, #0x2c]
	cmp r0, #0x0
	beq _0209C25C
_0209C2B8:
	ldr r0, [r8, #0x30]
	subs r7, r0, r7
	ldr r0, [sp, #0xc]
	add r0, r0, r7
	str r0, [sp, #0xc]
	beq _0209C2E4
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	str r0, [sp, #0x10]
	orr r0, r0, r1, lsl #0x10
	str r0, [sp, #0x10]
_0209C2E4:
	ldr r0, [r8, #0x30]
	str r0, [r8, #0x28]
	ldrb r0, [r8, #0x8]
	cmp r0, #0x4
	bne _0209C36C
	ldrh r0, [r8, #0x2c]
	cmp r0, #0x0
	bne _0209C36C
	cmp r7, #0x0
	bne _0209C36C
	cmp r6, #0x0
	bne _0209C370
	bl OS_GetTick
	mov r5, r0, lsr #0x10
	orr r5, r5, r1, lsl #0x10
	b _0209C334
_0209C324:
	bl FUN_020A005C
	ldrh r0, [r8, #0x2c]
	cmp r0, #0x0
	bne _0209C35C
_0209C334:
	ldr r0, [r4, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209C35C
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	sub r0, r0, r5
	cmp r0, #0xf
	blt _0209C324
_0209C35C:
	ldrh r0, [r8, #0x2c]
	cmp r0, #0x0
	ldreq r6, [sp, #0x14]
	b _0209C370
_0209C36C:
	ldr r6, [sp, #0x18]
_0209C370:
	cmp r7, r9
	addcc r10, r10, r7
	subcc r9, r9, r7
	blo _0209C39C
	sub r1, r7, r9
	add r10, r11, r1
	ldr r0, [sp, #0x8]
	ldr r11, [sp, #0x18]
	sub r9, r0, r1
	mov r0, r11
	str r0, [sp, #0x8]
_0209C39C:
	ldr r0, [r4, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209C3DC
	cmp r9, #0x0
	beq _0209C3DC
	ldrb r0, [r8, #0x8]
	cmp r0, #0x4
	bne _0209C3DC
	bl OS_GetTick
	mov r2, r0, lsr #0x10
	ldr r0, [sp, #0x10]
	orr r2, r2, r1, lsl #0x10
	sub r0, r2, r0
	cmp r0, #0x9f
	blt _0209C230
_0209C3DC:
	ldr r0, [sp, #0xc]
	add sp, sp, #0x1c
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209C3EC: .word UNK_021C8EFC

	arm_func_start FUN_0209C3F0
FUN_0209C3F0: ; 0x0209C3F0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r2
	mov r4, r3
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x14]
	bl FUN_0209C44C
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r2, [sp, #0x10]
	mov r0, r5
	mov r1, r4
	mov r3, #0x0
	bl FUN_0209C44C
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209C44C
FUN_0209C44C:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r8, r2
	ldr r11, [r8, #0x34]
	mov r10, r0
	movs r0, r3
	mov r0, r11, lsl #0x1
	movne r6, #0x1
	add r5, r0, #0x4
	mov r0, #0x18
	str r3, [sp, #0x4]
	mov r9, r1
	ldreqh r6, [r8, #0x2c]
	mov r4, #0x0
	str r0, [sp, #0x8]
	b _0209C504
_0209C48C:
	ldr r0, _0209C528 ; =UNK_021C8EB0
	ldrh r7, [r8, #0x2e]
	ldrh r0, [r0, #0x0]
	ldr r1, [r8, #0x34]
	cmp r7, r6
	movcs r7, r6
	cmp r0, r7
	movcc r7, r0
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	biceq r7, r7, #0x1
	cmp r9, r7
	sub r0, r1, r11
	movcc r7, r9
	adds r0, r5, r0
	moveq r7, r4
	mov r11, r1
	sub r5, r0, #0x1
	cmp r7, #0x0
	beq _0209C518
	ldr r3, [sp, #0x8]
	mov r0, r10
	mov r1, r7
	mov r2, r8
	str r4, [sp, #0x0]
	sub r6, r6, r7
	bl FUN_0209E878
	bl OS_YieldThread
	add r10, r10, r7
	sub r9, r9, r7
_0209C504:
	cmp r9, #0x0
	beq _0209C518
	ldrb r0, [r8, #0x8]
	cmp r0, #0x4
	beq _0209C48C
_0209C518:
	mov r0, r7
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209C528: .word UNK_021C8EB0

	arm_func_start FUN_0209C52C
FUN_0209C52C: ; 0x0209C52C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _0209C57C ; =OSi_ThreadInfo
	ldr r1, [r1, #0x4]
	ldr r1, [r1, #0xa4]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldrb r2, [r1, #0x9]
	cmp r2, #0x0
	beq _0209C56C
	bl CPSi_SslConsume
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C56C:
	bl CPSi_SocConsumeRaw
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209C57C: .word OSi_ThreadInfo

	arm_func_start CPSi_SocConsumeRaw
CPSi_SocConsumeRaw:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r7, r0
	bl OS_DisableInterrupts
	ldr r2, [r4, #0x44]
	ldr r1, [r4, #0x3c]
	mov r6, r0
	cmp r2, r1
	mov r5, #0x0
	bne _0209C5B4
	cmp r7, #0x0
	movne r5, #0x1
_0209C5B4:
	cmp r7, r2
	movcs r0, #0x0
	strcs r0, [r4, #0x44]
	bhs _0209C5D8
	ldr r0, [r4, #0x40]
	sub r2, r2, r7
	add r1, r0, r7
	str r2, [r4, #0x44]
	bl memmove
_0209C5D8:
	mov r0, r6
	bl OS_RestoreInterrupts
	ldrb r0, [r4, #0x8]
	cmp r0, #0xa
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	cmp r0, #0xb
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, [r4, #0x44]
	cmp r0, #0x0
	beq _0209C620
	cmp r5, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
_0209C620:
	mov r0, r4
	mov r1, #0x1b
	bl FUN_0209DF84
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_0209C638
FUN_0209C638:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _0209C6BC ; =OSi_ThreadInfo
	ldr r1, [r1, #0x4]
	ldr r1, [r1, #0xa4]
	cmp r1, #0x0
	beq _0209C6A4
	ldrb r2, [r1, #0x8]
	add r2, r2, #0xf6
	and r2, r2, #0xff
	cmp r2, #0x1
	bhi _0209C678
	bl FUN_0209C74C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C678:
	ldrb r2, [r1, #0x9]
	cmp r2, #0x0
	beq _0209C694
	bl CPSi_SslRead
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C694:
	bl CPSi_TcpReadRaw
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C6A4:
	mov r1, #0x0
	str r1, [r0, #0x0]
	mov r0, r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209C6BC: .word OSi_ThreadInfo

	arm_func_start CPSi_TcpReadRaw
CPSi_TcpReadRaw: ; 0x0209C6C0
	stmdb sp!, {r4-r8,lr}
	mov r4, r1
	ldr r1, [r4, #0x44]
	mov r5, r0
	cmp r1, #0x0
	bne _0209C728
	ldrb r0, [r4, #0x8]
	cmp r0, #0x4
	bne _0209C728
	bl OS_DisableInterrupts
	mov r8, r0
	mov r7, #0x2
	mov r6, #0x0
	b _0209C704
_0209C6F8:
	mov r0, r6
	str r7, [r4, #0x4]
	bl OS_SleepThread
_0209C704:
	ldr r0, [r4, #0x44]
	cmp r0, #0x0
	bne _0209C71C
	ldrb r0, [r4, #0x8]
	cmp r0, #0x4
	beq _0209C6F8
_0209C71C:
	mov r0, r8
	bl OS_RestoreInterrupts
	b _0209C72C
_0209C728:
	bl OS_YieldThread
_0209C72C:
	ldr r0, [r4, #0x44]
	str r0, [r5, #0x0]
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	ldrne r0, [r4, #0x40]
	moveq r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FUN_0209C74C
FUN_0209C74C: ; 0x0209C74C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r8, r1
	mov r9, r0
	bl OS_DisableInterrupts
	ldr r7, [r8, #0x44]
	mov r6, r0
	cmp r7, #0x0
	bne _0209C790
	mov r5, #0x3
	mov r4, #0x0
_0209C778:
	mov r0, r4
	str r5, [r8, #0x4]
	bl OS_SleepThread
	ldr r7, [r8, #0x44]
	cmp r7, #0x0
	beq _0209C778
_0209C790:
	mov r0, r6
	bl OS_RestoreInterrupts
	str r7, [r9, #0x0]
	ldr r0, [r8, #0x40]
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_0209C7AC
FUN_0209C7AC: ; 0x0209C7AC
	stmdb sp!, {r4-r6,lr}
	ldr r0, _0209C838 ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r4, [r0, #0xa4]
	cmp r4, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrb r0, [r4, #0x9]
	cmp r0, #0x0
	beq _0209C7DC
	mov r0, r4
	bl CPSi_SslClose
_0209C7DC:
	bl OS_GetTick
	mov r6, r0, lsr #0x10
	orr r6, r6, r1, lsl #0x10
	ldr r5, _0209C83C ; =UNK_021C8EFC
	b _0209C7F4
_0209C7F0:
	bl FUN_020A005C
_0209C7F4:
	ldr r0, [r5, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209C828
	ldrb r0, [r4, #0x8]
	cmp r0, #0x0
	beq _0209C828
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	sub r0, r0, r6
	cmp r0, #0x27
	blt _0209C7F0
_0209C828:
	mov r0, #0x0
	strb r0, [r4, #0x8]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209C838: .word OSi_ThreadInfo
_0209C83C: .word UNK_021C8EFC

	arm_func_start FUN_0209C840
FUN_0209C840:
	stmdb sp!, {r4,lr}
	ldr r0, _0209C880 ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r4, [r0, #0xa4]
	cmp r4, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrb r0, [r4, #0x9]
	cmp r0, #0x0
	beq _0209C870
	mov r0, r4
	bl CPSi_SslShutdown
_0209C870:
	mov r0, r4
	bl CPSi_TcpShutdownRaw
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209C880: .word OSi_ThreadInfo

	arm_func_start CPSi_TcpShutdownRaw
CPSi_TcpShutdownRaw: ; 0x0209C884
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_YieldThread
	ldrb r1, [r4, #0x8]
	add r0, r1, #0xfd
	and r0, r0, #0xff
	cmp r0, #0x1
	bhi _0209C8C0
	mov r0, r4
	mov r1, #0x19
	bl FUN_0209DF70
	mov r0, #0x7
	strb r0, [r4, #0x8]
	ldmia sp!, {r4,lr}
	bx lr
_0209C8C0:
	cmp r1, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, r4
	mov r1, #0x1a
	bl FUN_0209DF84
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_0209C8E0
FUN_0209C8E0: ; 0x0209C8E0
	ldr r2, _0209C930 ; =OSi_ThreadInfo
	ldr r2, [r2, #0x4]
	ldr r3, [r2, #0xa4]
	cmp r3, #0x0
	beq _0209C928
	ldrb r2, [r3, #0x8]
	cmp r2, #0x4
	beq _0209C908
	cmp r2, #0xa
	bne _0209C928
_0209C908:
	cmp r0, #0x0
	ldrneh r2, [r3, #0x18]
	strneh r2, [r0, #0x0]
	cmp r1, #0x0
	ldrne r0, [r3, #0x14]
	strne r0, [r1, #0x0]
	ldr r0, [r3, #0x1c]
	bx lr
_0209C928:
	mov r0, #0x0
	bx lr
	.balign 4
_0209C930: .word OSi_ThreadInfo

	arm_func_start FUN_0209C934
FUN_0209C934: ; 0x0209C934
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _0209C98C ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xa4]
	cmp r0, #0x0
	beq _0209C97C
	ldrb r1, [r0, #0x9]
	cmp r1, #0x0
	beq _0209C96C
	bl CPSi_SslConnect
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C96C:
	bl CPSi_TcpConnectRaw
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C97C:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209C98C: .word OSi_ThreadInfo

	arm_func_start CPSi_TcpConnectRaw
CPSi_TcpConnectRaw:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r10, r0
	bl FUN_0209CC3C
	mov r8, r0
	mov r9, #0x0
	mov r11, r9
	mov r4, #0x1
	mov r6, #0x2
	mov r5, #0x18
_0209C9B8:
	str r8, [r10, #0x28]
	strb r6, [r10, #0x8]
	bl OS_GetTick
	mov r2, r0, lsr #0x10
	orr r2, r2, r1, lsl #0x10
	str r2, [r10, #0x10]
	mov r0, r10
	mov r1, r6
	mov r2, r5
	bl FUN_0209DF98
	bl OS_DisableInterrupts
	mov r7, r0
	ldr r0, _0209CA50 ; =UNK_021C8F04
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0209CA04
	mov r0, r11
	str r4, [r10, #0x4]
	bl OS_SleepThread
_0209CA04:
	mov r0, r7
	bl OS_RestoreInterrupts
	ldrb r0, [r10, #0x8]
	cmp r0, #0x4
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r0, _0209CA50 ; =UNK_021C8F04
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0209CA40
	add r9, r9, #0x1
	cmp r9, #0x3
	blo _0209C9B8
_0209CA40:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209CA50: .word UNK_021C8F04

	arm_func_start FUN_0209CA54
FUN_0209CA54: ; 0x0209CA54
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _0209CAA4 ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xa4]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldrb r1, [r0, #0x9]
	cmp r1, #0x0
	beq _0209CA94
	bl CPSi_SslListen
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209CA94:
	bl FUN_0209CAC4
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209CAA4: .word OSi_ThreadInfo

	arm_func_start FUN_0209CAA8
FUN_0209CAA8:
	ldr r1, _0209CAC0 ; =OSi_ThreadInfo
	ldr r1, [r1, #0x4]
	ldr r1, [r1, #0xa4]
	cmp r1, #0x0
	strne r0, [r1, #0x38]
	bx lr
	.balign 4
_0209CAC0: .word OSi_ThreadInfo

	arm_func_start FUN_0209CAC4
FUN_0209CAC4: ; 0x0209CAC4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl FUN_0209CC3C
	str r0, [r5, #0x28]
	mov r0, #0x1
	strb r0, [r5, #0x8]
	bl OS_DisableInterrupts
	mov r4, r0
	mov r1, #0x1
	mov r0, #0x0
	str r1, [r5, #0x4]
	bl OS_SleepThread
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_0209CB0C
FUN_0209CB0C: ; 0x0209CB0C
	ldr r1, _0209CB20 ; =OSi_ThreadInfo
	ldr r1, [r1, #0x4]
	ldr r1, [r1, #0xa4]
	str r1, [r0, #0xa4]
	bx lr
	.balign 4
_0209CB20: .word OSi_ThreadInfo

	arm_func_start FUN_0209CB24
FUN_0209CB24: ; 0x0209CB24
	ldr r0, _0209CB40 ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r1, [r0, #0xa4]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x0]
	bx lr
	.balign 4
_0209CB40: .word OSi_ThreadInfo

	arm_func_start FUN_0209CB44
FUN_0209CB44: ; 0x0209CB44
	ldr r0, _0209CB74 ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r1, [r0, #0xa4]
	cmp r1, #0x0
	bxeq lr
	str r0, [r1, #0x0]
	mov r0, #0x0
	strb r0, [r1, #0x8]
	str r0, [r1, #0x44]
	str r0, [r1, #0x60]
	str r0, [r1, #0x38]
	bx lr
	.balign 4
_0209CB74: .word OSi_ThreadInfo

	arm_func_start FUN_0209CB78
FUN_0209CB78: ; 0x0209CB78
	stmdb sp!, {r4,lr}
	ldr r3, _0209CBDC ; =OSi_ThreadInfo
	ldr r3, [r3, #0x4]
	ldr r4, [r3, #0xa4]
	cmp r4, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r3, _0209CBE0 ; =0x7F000001
	cmp r2, r3
	ldreq r2, _0209CBE4 ; =UNK_021C8F04
	ldreq r2, [r2, #0x0]
	cmp r0, #0x0
	strh r1, [r4, #0x1a]
	ldrh r1, [r4, #0x1a]
	strh r1, [r4, #0x18]
	str r2, [r4, #0x20]
	ldr r1, [r4, #0x20]
	str r1, [r4, #0x1c]
	strneh r0, [r4, #0xa]
	ldmneia sp!, {r4,lr}
	bxne lr
	bl FUN_0209CC8C
	strh r0, [r4, #0xa]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209CBDC: .word OSi_ThreadInfo
_0209CBE0: .word 0x7F000001
_0209CBE4: .word UNK_021C8F04

	arm_func_start FUN_0209CBE8
FUN_0209CBE8: ; 0x0209CBE8
	ldr r0, _0209CC0C ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r1, [r0, #0xa4]
	cmp r1, #0x0
	movne r0, #0xa
	strneb r0, [r1, #0x8]
	movne r0, #0x0
	strne r0, [r1, #0x44]
	bx lr
	.balign 4
_0209CC0C: .word OSi_ThreadInfo

	arm_func_start FUN_0209CC10
FUN_0209CC10: ; 0x0209CC10
	ldr r0, _0209CC24 ; =OSi_ThreadInfo
	mov r1, #0x0
	ldr r0, [r0, #0x4]
	str r1, [r0, #0xa4]
	bx lr
	.balign 4
_0209CC24: .word OSi_ThreadInfo

	arm_func_start FUN_0209CC28
FUN_0209CC28: ; 0x0209CC28
	ldr r1, _0209CC38 ; =OSi_ThreadInfo
	ldr r1, [r1, #0x4]
	str r0, [r1, #0xa4]
	bx lr
	.balign 4
_0209CC38: .word OSi_ThreadInfo

	arm_func_start FUN_0209CC3C
FUN_0209CC3C: ; 0x0209CC3C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _0209CC88 ; =CPSiRand32ctx
	ldr r3, [r1, #0x8]
	ldr r2, [r1, #0x0]
	ldr r0, [r1, #0x4]
	umull lr, r12, r3, r2
	mla r12, r3, r0, r12
	ldr r0, [r1, #0xc]
	ldr r3, [r1, #0x10]
	mla r12, r0, r2, r12
	adds r2, r3, lr
	ldr r0, [r1, #0x14]
	str r2, [r1, #0x0]
	adc r0, r0, r12
	str r0, [r1, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209CC88: .word CPSiRand32ctx

	arm_func_start FUN_0209CC8C
FUN_0209CC8C: ; 0x0209CC8C
	stmdb sp!, {r4-r8,lr}
	ldr r0, _0209CD30 ; =OSi_ThreadInfo
	ldr r6, [r0, #0x8]
	ldr r2, _0209CD34 ; =UNK_021C8EBC
	mov r4, #0x400
	mov r3, #0x1
	mov r5, #0x0
	ldr r1, _0209CD38 ; =0x00001388
_0209CCAC:
	ldrh r12, [r2, #0x0]
	mov r0, r5
	add r12, r12, #0x1
	strh r12, [r2, #0x0]
	ldrh r12, [r2, #0x0]
	cmp r12, #0x400
	blo _0209CCD0
	cmp r12, r1
	blo _0209CCD4
_0209CCD0:
	strh r4, [r2, #0x0]
_0209CCD4:
	mov r8, r6
	cmp r6, #0x0
	beq _0209CD18
	ldrh r7, [r2, #0x0]
_0209CCE4:
	ldr lr, [r8, #0xa4]
	cmp lr, #0x0
	beq _0209CD0C
	ldr r12, [lr, #0x0]
	cmp r12, #0x0
	beq _0209CD0C
	ldrh r12, [lr, #0xa]
	cmp r12, r7
	moveq r0, r3
	beq _0209CD18
_0209CD0C:
	ldr r8, [r8, #0x68]
	cmp r8, #0x0
	bne _0209CCE4
_0209CD18:
	cmp r0, #0x0
	bne _0209CCAC
	ldr r0, _0209CD34 ; =UNK_021C8EBC
	ldrh r0, [r0, #0x0]
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209CD30: .word OSi_ThreadInfo
_0209CD34: .word UNK_021C8EBC
_0209CD38: .word 0x00001388

	arm_func_start FUN_0209CD3C
FUN_0209CD3C: ; 0x0209CD3C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r5, _0209CDAC ; =0x00000806
	add r4, sp, #0x0
_0209CD4C:
	mov r0, r4
	bl FUN_0209F57C
	ldr r3, [sp, #0x0]
	cmp r3, #0x22
	bls _0209CDA4
	ldrh r2, [r0, #0xc]
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	cmp r1, #0x800
	beq _0209CD88
	cmp r1, r5
	beq _0209CD98
	b _0209CDA4
_0209CD88:
	add r0, r0, #0xe
	sub r1, r3, #0xe
	bl FUN_0209CDB0
	b _0209CDA4
_0209CD98:
	add r0, r0, #0xe
	sub r1, r3, #0xe
	bl FUN_0209E614
_0209CDA4:
	bl FUN_0209F51C
	b _0209CD4C
	.balign 4
_0209CDAC: .word 0x00000806

	arm_func_start FUN_0209CDB0
FUN_0209CDB0: ; 0x0209CDB0
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r4, r0
	ldrh r12, [r4, #0xc]
	ldrh r6, [r4, #0x10]
	ldrh r2, [r4, #0xe]
	ldrh r0, [r4, #0x12]
	mov r5, r6, asr #0x8
	mov r3, r12, asr #0x8
	orr r5, r5, r6, lsl #0x8
	orr r12, r3, r12, lsl #0x8
	mov r3, r5, lsl #0x10
	mov r5, r0, asr #0x8
	mov r12, r12, lsl #0x10
	mov lr, r2, asr #0x8
	mov r6, r3, lsr #0x10
	orr r0, r5, r0, lsl #0x8
	mov r3, r12, lsr #0x10
	orr r2, lr, r2, lsl #0x8
	mov r5, r6, lsl #0x10
	mov r0, r0, lsl #0x10
	mov r3, r3, lsl #0x10
	mov r2, r2, lsl #0x10
	orr r0, r5, r0, lsr #0x10
	orr r2, r3, r2, lsr #0x10
	mov r5, r1
	cmp r0, r2
	beq _0209CEF0
	bl FUN_0209F9CC
	cmp r0, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrh r1, [r4, #0x2]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	cmp r5, r0, lsr #0x10
	addcc sp, sp, #0x8
	ldmccia sp!, {r4-r6,lr}
	bxcc lr
	ldrb r1, [r4, #0x0]
	mov r0, r4
	and r1, r1, #0xf
	mov r1, r1, lsl #0x2
	bl FUN_0209FB84
	ldr r1, _0209CFA0 ; =0x0000FFFF
	cmp r0, r1
	addne sp, sp, #0x8
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldrh r2, [r4, #0x10]
	ldrh r12, [r4, #0x12]
	ldr r1, _0209CFA4 ; =UNK_021C8F04
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r2, r12, asr #0x8
	mov r3, r0, lsr #0x10
	orr r0, r2, r12, lsl #0x8
	mov r2, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	ldr r1, [r1, #0x0]
	orr r0, r2, r0, lsr #0x10
	cmp r1, r0
	bne _0209CEF0
	ldrh r2, [r4, #0xc]
	ldrh r12, [r4, #0xe]
	sub r0, r4, #0x8
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r2, r12, asr #0x8
	mov r3, r1, lsr #0x10
	orr r1, r2, r12, lsl #0x8
	mov r2, r3, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r1, r2, r1, lsr #0x10
	mov r2, #0x1
	bl FUN_0209F12C
_0209CEF0:
	add r1, sp, #0x0
	mov r0, r4
	bl FUN_0209CFAC
	movs r4, r0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrh r2, [r4, #0x2]
	ldrb r3, [r4, #0x0]
	ldrb r12, [r4, #0x9]
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	and r3, r3, #0xf
	mov r2, r1, lsr #0x10
	cmp r12, #0x11
	add r1, r4, r3, lsl #0x2
	sub r2, r2, r3, lsl #0x2
	bne _0209CF44
	bl FUN_0209D2BC
	b _0209CF70
_0209CF44:
	ldr r3, _0209CFA4 ; =UNK_021C8F04
	ldr r3, [r3, #0x0]
	cmp r3, #0x0
	beq _0209CF70
	cmp r12, #0x1
	bne _0209CF64
	bl FUN_0209E2E0
	b _0209CF70
_0209CF64:
	cmp r12, #0x6
	bne _0209CF70
	bl FUN_0209D4D8
_0209CF70:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r1, _0209CFA8 ; =CPSiFree
	sub r0, r4, #0xe
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209CFA0: .word 0x0000FFFF
_0209CFA4: .word UNK_021C8F04
_0209CFA8: .word CPSiFree

	arm_func_start FUN_0209CFAC
FUN_0209CFAC: ; 0x0209CFAC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r6, #0x0
	mov r10, r0
	str r6, [r1, #0x0]
	ldrh r3, [r10, #0x6]
	str r1, [sp, #0x0]
	ldr r2, _0209D2A4 ; =0x00003FFF
	mov r1, r3, asr #0x8
	orr r1, r1, r3, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	str r1, [sp, #0x4]
	ands r1, r1, r2
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldrh r1, [r10, #0xc]
	ldrh r3, [r10, #0xe]
	ldrb r4, [r10, #0x0]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r3, asr #0x8
	mov r2, r0, lsr #0x10
	orr r0, r1, r3, lsl #0x8
	and r3, r4, #0xf
	ldrh r9, [r10, #0x4]
	mov r2, r2, lsl #0x10
	mov r1, r0, lsl #0x10
	ldr r5, _0209D2A8 ; =UNK_021C9520
	mov r0, r6
	mov r7, r3, lsl #0x2
	orr r4, r2, r1, lsr #0x10
_0209D034:
	ldrh r2, [r5, #0x4]
	cmp r2, #0x0
	beq _0209D058
	ldr r1, [r5, #0x0]
	cmp r1, r4
	bne _0209D058
	ldrh r1, [r5, #0x6]
	cmp r1, r9
	beq _0209D078
_0209D058:
	cmp r2, #0x0
	bne _0209D068
	cmp r6, #0x0
	moveq r6, r5
_0209D068:
	add r0, r0, #0x1
	cmp r0, #0x8
	add r5, r5, #0x38
	blo _0209D034
_0209D078:
	ldrh r2, [r10, #0x2]
	cmp r0, #0x8
	ldr r1, _0209D2AC ; =0x00001FFF
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r2, r0, lsr #0x10
	ldr r0, [sp, #0x4]
	and r8, r0, r1
	sub r0, r2, r7
	str r0, [sp, #0x8]
	mov r0, r8, lsl #0x3
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x8]
	add r11, r0, r8, lsl #0x3
	bne _0209D150
	cmp r6, #0x0
	beq _0209D0C8
	cmp r11, #0x1000
	bls _0209D0D8
_0209D0C8:
	add sp, sp, #0x14
	mov r0, #0x0
	ldmia sp!, {r4-r11,lr}
	bx lr
_0209D0D8:
	ldr r1, _0209D2B0 ; =CPSiAlloc
	ldr r0, _0209D2B4 ; =0x0000100E
	ldr r1, [r1, #0x0]
	add r0, r7, r0
	mov r5, r6
	blx r1
	str r0, [r6, #0x34]
	ldr r0, [r6, #0x34]
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	str r4, [r6, #0x0]
	strh r9, [r6, #0x6]
	mov r0, #0x0
	strh r0, [r6, #0x8]
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	str r0, [r6, #0x2c]
	ldr r1, [r6, #0x34]
	mov r0, r10
	add r1, r1, #0xe
	add r1, r1, r7
	str r1, [r6, #0x30]
	ldr r1, [r6, #0x34]
	mov r2, r7
	add r1, r1, #0xe
	bl MI_CpuCopy8
_0209D150:
	ldrh r0, [r5, #0x4]
	cmp r0, #0x8
	beq _0209D164
	cmp r11, #0x1000
	bls _0209D18C
_0209D164:
	mov r0, #0x0
	strh r0, [r5, #0x4]
	ldr r1, _0209D2B8 ; =CPSiFree
	ldr r0, [r5, #0x34]
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x14
	mov r0, #0x0
	ldmia sp!, {r4-r11,lr}
	bx lr
_0209D18C:
	ldr r0, [sp, #0x8]
	ldr r2, [sp, #0x8]
	add r0, r0, #0x7
	add r1, r8, r0, lsr #0x3
	ldr r0, [sp, #0x4]
	ands r0, r0, #0x2000
	streqh r11, [r5, #0xa]
	streqh r1, [r5, #0x8]
	ldrh r3, [r5, #0x4]
	add r0, r10, r7
	add r3, r5, r3, lsl #0x1
	strh r8, [r3, #0xc]
	ldrh r3, [r5, #0x4]
	add r3, r5, r3, lsl #0x1
	strh r1, [r3, #0x1c]
	ldrh r1, [r5, #0x4]
	add r1, r1, #0x1
	strh r1, [r5, #0x4]
	ldr r3, [r5, #0x30]
	ldr r1, [sp, #0xc]
	add r1, r3, r1
	bl MI_CpuCopy8
	ldrh r6, [r5, #0x8]
	cmp r6, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldrh r7, [r5, #0x4]
	mov r3, #0x0
	mov r4, r3
	cmp r7, #0x0
	bls _0209D244
	mov r0, r3
_0209D214:
	add r2, r5, r4, lsl #0x1
	ldrh r1, [r2, #0xc]
	cmp r1, r3
	bhi _0209D238
	ldrh r1, [r2, #0x1c]
	cmp r3, r1
	movcc r3, r1
	movcc r4, r0
	blo _0209D23C
_0209D238:
	add r4, r4, #0x1
_0209D23C:
	cmp r4, r7
	blo _0209D214
_0209D244:
	cmp r3, r6
	addcc sp, sp, #0x14
	movcc r0, #0x0
	ldmccia sp!, {r4-r11,lr}
	bxcc lr
	ldr r0, [r5, #0x34]
	ldrh r3, [r5, #0xa]
	ldrb r1, [r0, #0xe]
	add r0, r0, #0xe
	mov r2, #0x0
	and r1, r1, #0xf
	add r1, r3, r1, lsl #0x2
	mov r1, r1, lsl #0x10
	mov r3, r1, lsr #0x10
	mov r1, r3, asr #0x8
	orr r1, r1, r3, lsl #0x8
	strh r1, [r0, #0x2]
	strh r2, [r5, #0x4]
	ldr r1, [sp, #0x0]
	mov r2, #0x1
	str r2, [r1, #0x0]
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209D2A4: .word 0x00003FFF
_0209D2A8: .word UNK_021C9520
_0209D2AC: .word 0x00001FFF
_0209D2B0: .word CPSiAlloc
_0209D2B4: .word 0x0000100E
_0209D2B8: .word CPSiFree

	arm_func_start FUN_0209D2BC
FUN_0209D2BC: ; 0x0209D2BC
	stmdb sp!, {r4-r8,lr}
	mov r6, r1
	ldrh r1, [r6, #0x6]
	mov r7, r0
	mov r5, r2
	cmp r1, #0x0
	beq _0209D2F8
	mov r0, r6
	mov r1, r5
	mov r2, r7
	mov r3, #0x11
	bl FUN_0209FB28
	cmp r0, #0x0
	ldmneia sp!, {r4-r8,lr}
	bxne lr
_0209D2F8:
	bl OS_DisableInterrupts
	ldr r1, _0209D4D4 ; =OSi_ThreadInfo
	mov r8, r0
	ldr r2, [r1, #0x8]
	cmp r2, #0x0
	beq _0209D4C4
	mvn r12, #0x0
_0209D314:
	ldr r4, [r2, #0xa4]
	cmp r4, #0x0
	beq _0209D4B8
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0209D4B8
	ldrb r0, [r4, #0x8]
	cmp r0, #0xa
	bne _0209D4B8
	ldrh r3, [r6, #0x2]
	ldrh r1, [r4, #0xa]
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	mov r0, r0, lsl #0x10
	cmp r1, r0, lsr #0x10
	bne _0209D4B8
	ldrh r3, [r4, #0x18]
	cmp r3, #0x0
	beq _0209D378
	ldrh r1, [r6, #0x0]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	cmp r3, r0, lsr #0x10
	bne _0209D4B8
_0209D378:
	ldr r1, [r4, #0x1c]
	cmp r1, #0x0
	beq _0209D3C0
	cmp r1, r12
	beq _0209D3C0
	ldrh lr, [r7, #0xc]
	ldrh r0, [r7, #0xe]
	mov r3, lr, asr #0x8
	orr r3, r3, lr, lsl #0x8
	mov r3, r3, lsl #0x10
	mov lr, r0, asr #0x8
	mov r3, r3, lsr #0x10
	orr r0, lr, r0, lsl #0x8
	mov r3, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r3, r0, lsr #0x10
	cmp r1, r0
	bne _0209D4B8
_0209D3C0:
	ldrh r1, [r7, #0x10]
	ldrh r3, [r7, #0x12]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r3, asr #0x8
	mov r2, r0, lsr #0x10
	orr r0, r1, r3, lsl #0x8
	mov r1, r2, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r1, r0, lsr #0x10
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x1c]
	cmp r0, #0x0
	bne _0209D43C
	ldrh r1, [r7, #0xc]
	ldrh r3, [r7, #0xe]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r3, asr #0x8
	mov r2, r0, lsr #0x10
	orr r0, r1, r3, lsl #0x8
	mov r1, r2, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r1, r0, lsr #0x10
	str r0, [r4, #0x1c]
	ldrh r1, [r6, #0x0]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	strh r0, [r4, #0x18]
_0209D43C:
	ldr r0, [r4, #0x44]
	cmp r0, #0x0
	bne _0209D4C4
	ldr r1, [r4, #0x3c]
	sub r0, r5, #0x8
	cmp r0, r1
	strhi r1, [r4, #0x44]
	strls r0, [r4, #0x44]
	ldr r1, [r4, #0x40]
	ldr r2, [r4, #0x44]
	add r0, r6, #0x8
	bl MI_CpuCopy8
	ldr r0, [r4, #0x4]
	cmp r0, #0x3
	bne _0209D48C
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl OS_WakeupThreadDirect
	b _0209D4C4
_0209D48C:
	ldr r3, [r4, #0x38]
	cmp r3, #0x0
	beq _0209D4C4
	ldr r0, [r4, #0x40]
	ldr r1, [r4, #0x44]
	mov r2, r4
	blx r3
	cmp r0, #0x0
	movne r0, #0x0
	strne r0, [r4, #0x44]
	b _0209D4C4
_0209D4B8:
	ldr r2, [r2, #0x68]
	cmp r2, #0x0
	bne _0209D314
_0209D4C4:
	mov r0, r8
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209D4D4: .word OSi_ThreadInfo

	arm_func_start FUN_0209D4D8
FUN_0209D4D8:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	mov r0, r5
	mov r1, r4
	mov r2, r6
	mov r3, #0x6
	bl FUN_0209FB28
	cmp r0, #0x0
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldrb r0, [r5, #0xc]
	ldrb r2, [r5, #0xd]
	and r1, r0, #0xf0
	mov r0, r1, asr #0x1
	add r0, r1, r0, lsr #0x1e
	and r1, r2, #0x17
	cmp r1, #0x10
	sub r4, r4, r0, asr #0x2
	bgt _0209D558
	cmp r1, #0x10
	bge _0209D5C4
	cmp r1, #0x2
	bgt _0209D5F4
	cmp r1, #0x1
	blt _0209D5F4
	cmp r1, #0x1
	beq _0209D5DC
	cmp r1, #0x2
	beq _0209D57C
	b _0209D5F4
_0209D558:
	cmp r1, #0x12
	bgt _0209D5F4
	cmp r1, #0x11
	blt _0209D5F4
	cmp r1, #0x11
	beq _0209D5C4
	cmp r1, #0x12
	beq _0209D5A0
	b _0209D5F4
_0209D57C:
	ands r0, r2, #0x28
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_0209DBB0
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209D5A0:
	ands r0, r2, #0x28
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_0209DA9C
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209D5C4:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_0209D774
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209D5DC:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_0209D674
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209D5F4:
	ands r0, r2, #0x4
	beq _0209D610
	mov r0, r6
	mov r1, r5
	bl FUN_0209D62C
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209D610:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	mov r3, #0x0
	bl FUN_0209DE34
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_0209D62C
FUN_0209D62C: ; 0x0209D62C
	stmdb sp!, {r4,lr}
	bl FUN_0209E0C8
	movs r4, r0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl OS_YieldThread
	mov r1, #0x0
	strb r1, [r4, #0x8]
	ldr r0, [r4, #0x4]
	sub r0, r0, #0x1
	cmp r0, #0x1
	ldmhiia sp!, {r4,lr}
	bxhi lr
	str r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl OS_WakeupThreadDirect
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_0209D674
FUN_0209D674: ; 0x0209D674
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl FUN_0209E0C8
	movs r4, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrb r1, [r4, #0x8]
	cmp r1, #0x4
	beq _0209D72C
	cmp r1, #0x7
	beq _0209D6BC
	cmp r1, #0x8
	beq _0209D6E4
	b _0209D754
_0209D6BC:
	ldr r2, [r4, #0x24]
	mov r1, #0x0
	add r2, r2, #0x1
	str r2, [r4, #0x24]
	bl FUN_0209DF84
	mov r0, #0x9
	add sp, sp, #0x4
	strb r0, [r4, #0x8]
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209D6E4:
	ldr r2, [r4, #0x24]
	mov r1, #0x0
	add r2, r2, #0x1
	str r2, [r4, #0x24]
	bl FUN_0209DF84
	mov r1, #0x0
	strb r1, [r4, #0x8]
	ldr r0, [r4, #0x4]
	cmp r0, #0x2
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	str r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl OS_WakeupThreadDirect
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209D72C:
	ldr r2, [r4, #0x24]
	mov r1, #0x0
	add r2, r2, #0x1
	str r2, [r4, #0x24]
	bl FUN_0209DF70
	mov r0, #0x6
	add sp, sp, #0x4
	strb r0, [r4, #0x8]
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209D754:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	mov r3, #0x0
	bl FUN_0209DE34
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_0209D774
FUN_0209D774: ; 0x0209D774
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r8, r0
	mov r7, r1
	mov r6, r2
	bl FUN_0209E0C8
	movs r5, r0
	bne _0209D7B4
	mov r0, r8
	mov r1, r7
	mov r2, r6
	mov r3, #0x0
	bl FUN_0209DE34
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
_0209D7B4:
	ldrh r3, [r7, #0x8]
	ldrh r1, [r7, #0xa]
	ldrb r4, [r7, #0xd]
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r3, r1, asr #0x8
	mov r2, r2, lsr #0x10
	orr r1, r3, r1, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r1, r2, r1, lsr #0x10
	str r1, [r5, #0x30]
	ldrh r9, [r7, #0x4]
	ldrh r1, [r7, #0x6]
	ldrb r3, [r5, #0x8]
	mov r2, r9, asr #0x8
	orr r2, r2, r9, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r9, r1, asr #0x8
	mov r2, r2, lsr #0x10
	orr r1, r9, r1, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r1, r1, lsl #0x10
	cmp r3, #0x4
	orr r2, r2, r1, lsr #0x10
	bne _0209D840
	ldr r1, [r5, #0x24]
	cmp r1, r2
	beq _0209D840
	mov r1, #0x0
	bl FUN_0209DF84
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
_0209D840:
	ldrh r1, [r7, #0xe]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	strh r0, [r5, #0x2c]
	ldrb r0, [r5, #0x8]
	cmp r0, #0x9
	addls pc, pc, r0, lsl #0x2
	b _0209DA70
_0209D860:
	b _0209D888
_0209D864:
	b _0209DA70
_0209D868:
	b _0209D888
_0209D86C:
	b _0209D8A0
_0209D870:
	b _0209D8CC
_0209D874:
	b _0209DA70
_0209D878:
	b _0209DA4C
_0209D87C:
	b _0209D9D8
_0209D880:
	b _0209D9D8
_0209D884:
	b _0209DA4C
_0209D888:
	mov r0, r8
	mov r1, r7
	mov r2, r6
	mov r3, #0x0
	bl FUN_0209DE34
	b _0209DA8C
_0209D8A0:
	mov r0, #0x4
	strb r0, [r5, #0x8]
	ldr r0, [r5, #0x4]
	cmp r0, #0x1
	bne _0209D8C4
	mov r0, #0x0
	str r0, [r5, #0x4]
	ldr r0, [r5, #0x0]
	bl OS_WakeupThreadDirect
_0209D8C4:
	cmp r6, #0x0
	beq _0209DA8C
_0209D8CC:
	ldr r0, [r5, #0x34]
	add r0, r0, #0x1
	str r0, [r5, #0x34]
	ldr r1, [r5, #0x3c]
	ldr r0, [r5, #0x44]
	sub r0, r1, r0
	cmp r6, r0
	movhi r9, #0x0
	movhi r6, r0
	movls r9, #0x1
	cmp r6, #0x0
	beq _0209D968
	bl OS_DisableInterrupts
	ldrb r1, [r7, #0xc]
	ldr r12, [r5, #0x40]
	ldr r3, [r5, #0x44]
	and r2, r1, #0xf0
	mov r1, r2, asr #0x1
	add r1, r2, r1, lsr #0x1e
	mov r8, r0
	mov r2, r6
	add r0, r7, r1, asr #0x2
	add r1, r12, r3
	bl MI_CpuCopy8
	ldr r1, [r5, #0x44]
	mov r0, r8
	add r1, r1, r6
	str r1, [r5, #0x44]
	ldr r1, [r5, #0x24]
	add r1, r1, r6
	str r1, [r5, #0x24]
	bl OS_RestoreInterrupts
	ldr r0, [r5, #0x4]
	cmp r0, #0x2
	bne _0209D968
	mov r0, #0x0
	str r0, [r5, #0x4]
	ldr r0, [r5, #0x0]
	bl OS_WakeupThreadDirect
_0209D968:
	cmp r9, #0x0
	beq _0209D9C0
	ands r0, r4, #0x1
	beq _0209D9C0
	mov r0, #0x6
	strb r0, [r5, #0x8]
	ldr r1, [r5, #0x24]
	mov r0, r5
	add r2, r1, #0x1
	mov r1, #0x0
	str r2, [r5, #0x24]
	bl FUN_0209DF70
	cmp r6, #0x0
	bne _0209DA8C
	ldr r0, [r5, #0x4]
	cmp r0, #0x2
	bne _0209DA8C
	mov r0, #0x0
	str r0, [r5, #0x4]
	ldr r0, [r5, #0x0]
	bl OS_WakeupThreadDirect
	b _0209DA8C
_0209D9C0:
	cmp r6, #0x0
	beq _0209DA8C
	mov r0, r5
	mov r1, #0x0
	bl FUN_0209DF84
	b _0209DA8C
_0209D9D8:
	ands r0, r4, #0x1
	beq _0209DA20
	ldr r1, [r5, #0x24]
	add r0, r6, #0x1
	add r2, r1, r0
	mov r0, r5
	mov r1, #0x0
	str r2, [r5, #0x24]
	bl FUN_0209DF84
	mov r1, #0x0
	strb r1, [r5, #0x8]
	ldr r0, [r5, #0x4]
	cmp r0, #0x2
	bne _0209DA8C
	str r1, [r5, #0x4]
	ldr r0, [r5, #0x0]
	bl OS_WakeupThreadDirect
	b _0209DA8C
_0209DA20:
	cmp r6, #0x0
	beq _0209DA40
	ldr r1, [r5, #0x24]
	mov r0, r5
	add r2, r1, r6
	mov r1, #0x0
	str r2, [r5, #0x24]
	bl FUN_0209DF84
_0209DA40:
	mov r0, #0x8
	strb r0, [r5, #0x8]
	b _0209DA8C
_0209DA4C:
	mov r1, #0x0
	strb r1, [r5, #0x8]
	ldr r0, [r5, #0x4]
	cmp r0, #0x2
	bne _0209DA8C
	str r1, [r5, #0x4]
	ldr r0, [r5, #0x0]
	bl OS_WakeupThreadDirect
	b _0209DA8C
_0209DA70:
	ands r0, r4, #0x1
	ldrne r0, [r5, #0x24]
	mov r1, #0x0
	addne r0, r0, #0x1
	strne r0, [r5, #0x24]
	mov r0, r5
	bl FUN_0209DF84
_0209DA8C:
	bl OS_YieldThread
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start FUN_0209DA9C
FUN_0209DA9C: ; 0x0209DA9C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r5, r1
	mov r6, r2
	bl FUN_0209E0C8
	movs r4, r0
	beq _0209DAC8
	ldrb r0, [r4, #0x8]
	cmp r0, #0x2
	beq _0209DAE8
_0209DAC8:
	mov r0, r7
	mov r1, r5
	mov r2, r6
	mov r3, #0x0
	bl FUN_0209DE34
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209DAE8:
	bl OS_YieldThread
	ldrh r2, [r5, #0x4]
	ldrh r12, [r5, #0x6]
	mov r0, r5
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r2, r12, asr #0x8
	mov r3, r1, lsr #0x10
	orr r1, r2, r12, lsl #0x8
	mov r2, r3, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r1, r2, r1, lsr #0x10
	add r1, r1, #0x1
	str r1, [r4, #0x24]
	ldrh r3, [r5, #0x8]
	ldrh lr, [r5, #0xa]
	mov r1, r4
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r3, lr, asr #0x8
	mov r12, r2, lsr #0x10
	orr r2, r3, lr, lsl #0x8
	mov r3, r12, lsl #0x10
	mov r2, r2, lsl #0x10
	orr r2, r3, r2, lsr #0x10
	str r2, [r4, #0x30]
	ldrh r3, [r5, #0xe]
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	strh r2, [r4, #0x2c]
	bl FUN_0209E044
	mov r0, r4
	mov r1, #0x0
	bl FUN_0209DF84
	mov r0, #0x4
	strb r0, [r4, #0x8]
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl OS_WakeupThreadDirect
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_0209DBB0
FUN_0209DBB0: ; 0x0209DBB0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldrh r12, [r4, #0x10]
	ldrh r7, [r4, #0xc]
	ldrh r3, [r4, #0x12]
	mov r5, r12, asr #0x8
	mov r6, r7, asr #0x8
	orr r5, r5, r12, lsl #0x8
	orr r6, r6, r7, lsl #0x8
	mov r12, r6, lsl #0x10
	ldrh r0, [r4, #0xe]
	mov lr, r5, lsl #0x10
	mov r5, r3, asr #0x8
	mov r6, r0, asr #0x8
	mov r7, r12, lsr #0x10
	orr r0, r6, r0, lsl #0x8
	orr r3, r5, r3, lsl #0x8
	mov r12, lr, lsr #0x10
	mov r6, r7, lsl #0x10
	mov r0, r0, lsl #0x10
	mov r5, r12, lsl #0x10
	mov r3, r3, lsl #0x10
	mov r7, r1
	orr r1, r5, r3, lsr #0x10
	orr r0, r6, r0, lsr #0x10
	mov r5, r2
	bl FUN_0209E3DC
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r4
	mov r1, r7
	mov r2, r5
	bl FUN_0209DCB4
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	mov r0, r4
	mov r1, r7
	bl FUN_0209E200
	movs r2, r0
	beq _0209DC7C
	mov r0, r4
	mov r1, r7
	bl FUN_0209DD44
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209DC7C:
	bl OS_YieldThread
	mov r0, r4
	mov r1, r7
	bl FUN_0209E200
	movs r2, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r4
	mov r1, r7
	bl FUN_0209DD44
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_0209DCB4
FUN_0209DCB4:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl FUN_0209E0C8
	movs r2, r0
	beq _0209DD38
	ldrb r0, [r2, #0x8]
	cmp r0, #0x1
	bne _0209DCEC
	mov r0, r6
	mov r1, r5
	bl FUN_0209DD44
	b _0209DD2C
_0209DCEC:
	add r0, r0, #0xfd
	and r0, r0, #0xff
	cmp r0, #0x1
	bhi _0209DD18
	ldr r1, [r2, #0x28]
	mov r0, r6
	sub r3, r1, #0x1
	mov r1, r5
	str r3, [r2, #0x28]
	bl FUN_0209DD44
	b _0209DD2C
_0209DD18:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	mov r3, #0x0
	bl FUN_0209DE34
_0209DD2C:
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209DD38:
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_0209DD44
FUN_0209DD44: ; 0x0209DD44
	stmdb sp!, {r4-r6,lr}
	mov r4, r2
	mov r2, #0x3
	mov r6, r0
	mov r5, r1
	strb r2, [r4, #0x8]
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	str r0, [r4, #0x10]
	ldrh r2, [r6, #0x10]
	ldrh r3, [r6, #0x12]
	mov r0, r5
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r1, r1, lsr #0x10
	mov r3, r1, lsl #0x10
	mov r1, r2, lsl #0x10
	orr r1, r3, r1, lsr #0x10
	str r1, [r4, #0x14]
	ldrh r3, [r5, #0x0]
	mov r1, r4
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	strh r2, [r4, #0x18]
	ldrh r3, [r6, #0xc]
	ldrh r6, [r6, #0xe]
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r3, r6, asr #0x8
	orr r3, r3, r6, lsl #0x8
	mov r2, r2, lsr #0x10
	mov r6, r2, lsl #0x10
	mov r2, r3, lsl #0x10
	orr r2, r6, r2, lsr #0x10
	str r2, [r4, #0x1c]
	ldrh r3, [r5, #0x4]
	ldrh r6, [r5, #0x6]
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r3, r6, asr #0x8
	mov r5, r2, lsr #0x10
	orr r2, r3, r6, lsl #0x8
	mov r3, r5, lsl #0x10
	mov r2, r2, lsl #0x10
	orr r2, r3, r2, lsr #0x10
	add r2, r2, #0x1
	str r2, [r4, #0x24]
	bl FUN_0209E044
	mov r0, r4
	mov r1, #0x12
	mov r2, #0x0
	bl FUN_0209DF98
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_0209DE34
FUN_0209DE34: ; 0x0209DE34
	stmdb sp!, {r4-r8,lr}
	ldr r4, _0209DF6C ; =UNK_021C903C
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r0, r4
	mov r1, #0x0
	mov r2, #0x64
	mov r5, r3
	bl MI_CpuFill8
	ldrh r2, [r7, #0x2]
	mov r1, r4
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	strh r0, [r1, #0xa]
	ldrh r2, [r7, #0x0]
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	strh r0, [r1, #0x18]
	ldrh r2, [r8, #0xc]
	ldrh r8, [r8, #0xe]
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r2, r8, asr #0x8
	mov r3, r0, lsr #0x10
	orr r0, r2, r8, lsl #0x8
	mov r2, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r2, r0, lsr #0x10
	str r0, [r1, #0x1c]
	ldrb r0, [r7, #0xd]
	ands r0, r0, #0x10
	beq _0209DF04
	ldrh r2, [r7, #0x8]
	ldrh r6, [r7, #0xa]
	mov r0, r4
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r2, r6, asr #0x8
	mov r3, r1, lsr #0x10
	orr r1, r2, r6, lsl #0x8
	mov r2, r3, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r3, r2, r1, lsr #0x10
	mov r2, r5
	mov r1, #0x4
	str r3, [r4, #0x28]
	bl FUN_0209DF98
	ldmia sp!, {r4-r8,lr}
	bx lr
_0209DF04:
	mov r0, #0x0
	str r0, [r4, #0x28]
	ldrh r1, [r7, #0x4]
	ldrh r3, [r7, #0x6]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r3, asr #0x8
	mov r2, r0, lsr #0x10
	orr r0, r1, r3, lsl #0x8
	mov r1, r2, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r1, r0, lsr #0x10
	add r0, r6, r0
	str r0, [r4, #0x24]
	ldrb r0, [r7, #0xd]
	mov r2, r5
	mov r1, #0x14
	ands r0, r0, #0x3
	ldrne r0, [r4, #0x24]
	addne r0, r0, #0x1
	strne r0, [r4, #0x24]
	mov r0, r4
	bl FUN_0209DF98
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209DF6C: .word UNK_021C903C

	arm_func_start FUN_0209DF70
FUN_0209DF70:
	ldr ip, _0209DF80 ; =FUN_0209DF98
	mov r2, r1
	mov r1, #0x11
	bx r12
	.balign 4
_0209DF80: .word FUN_0209DF98

	arm_func_start FUN_0209DF84
FUN_0209DF84: ; 0x0209DF84
	ldr ip, _0209DF94 ; =FUN_0209DF98
	mov r2, r1
	mov r1, #0x10
	bx r12
	.balign 4
_0209DF94: .word FUN_0209DF98

	arm_func_start FUN_0209DF98
FUN_0209DF98: ; 0x0209DF98
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r6, r0
	ldr r0, [r6, #0x1c]
	mov r5, r1
	mov r4, r2
	bl FUN_0209E014
	cmp r0, #0x0
	bne _0209DFD0
	ldr r0, _0209E00C ; =OSi_ThreadInfo
	ldr r1, _0209E010 ; =UNK_021C9160
	ldr r0, [r0, #0x4]
	cmp r0, r1
	beq _0209DFF4
_0209DFD0:
	mov r0, #0x0
	mov r1, r0
	mov r2, r6
	mov r3, r5
	str r4, [sp, #0x0]
	bl FUN_0209E878
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209DFF4:
	ldr r0, [r6, #0x1c]
	bl FUN_0209FAB0
	bl FUN_0209F338
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209E00C: .word OSi_ThreadInfo
_0209E010: .word UNK_021C9160

	arm_func_start FUN_0209E014
FUN_0209E014:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_0209FAB0
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {lr}
	bxeq lr
	bl FUN_0209F438
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_0209E044
FUN_0209E044: ; 0x0209E044
	mov r2, #0x218
	strh r2, [r1, #0x2e]
	ldrb r2, [r0, #0xc]
	add r3, r0, #0x14
	and r2, r2, #0xf0
	mov r0, r2, asr #0x1
	add r0, r2, r0, lsr #0x1e
	mov r0, r0, asr #0x2
	subs r0, r0, #0x14
	sub r12, r0, #0x1
	bxeq lr
_0209E070:
	ldrb r0, [r3], #0x1
	cmp r0, #0x0
	bxeq lr
	cmp r0, #0x1
	beq _0209E0B8
	cmp r0, #0x2
	bne _0209E0A8
	ldrb r2, [r3, #0x1]
	ldrb r0, [r3, #0x2]
	add r3, r3, #0x3
	sub r12, r12, #0x3
	orr r0, r0, r2, lsl #0x8
	strh r0, [r1, #0x2e]
	b _0209E0B8
_0209E0A8:
	ldrb r0, [r3, #0x0]
	sub r0, r0, #0x1
	sub r12, r12, r0
	add r3, r3, r0
_0209E0B8:
	cmp r12, #0x0
	sub r12, r12, #0x1
	bne _0209E070
	bx lr

	arm_func_start FUN_0209E0C8
FUN_0209E0C8: ; 0x0209E0C8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r2, _0209E140 ; =OSi_ThreadInfo
	mov r7, r0
	ldr r4, [r2, #0x8]
	mov r6, r1
	cmp r4, #0x0
	beq _0209E130
_0209E0E8:
	ldr r5, [r4, #0xa4]
	cmp r5, #0x0
	beq _0209E124
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0209E124
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl FUN_0209E144
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, r5
	ldmneia sp!, {r4-r7,lr}
	bxne lr
_0209E124:
	ldr r4, [r4, #0x68]
	cmp r4, #0x0
	bne _0209E0E8
_0209E130:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209E140: .word OSi_ThreadInfo

	arm_func_start FUN_0209E144
FUN_0209E144:
	stmdb sp!, {r4-r6,lr}
	ldrb r4, [r2, #0x8]
	mov r12, #0x0
	mov r3, r12
	mov r6, r12
	mov r5, r12
	cmp r4, #0xa
	beq _0209E16C
	cmp r4, #0xb
	movne r5, #0x1
_0209E16C:
	cmp r5, #0x0
	beq _0209E190
	ldrh lr, [r1, #0x2]
	ldrh r5, [r2, #0xa]
	mov r4, lr, asr #0x8
	orr r4, r4, lr, lsl #0x8
	mov lr, r4, lsl #0x10
	cmp r5, lr, lsr #0x10
	moveq r6, #0x1
_0209E190:
	cmp r6, #0x0
	beq _0209E1B4
	ldrh r4, [r1, #0x0]
	ldrh lr, [r2, #0x18]
	mov r1, r4, asr #0x8
	orr r1, r1, r4, lsl #0x8
	mov r1, r1, lsl #0x10
	cmp lr, r1, lsr #0x10
	moveq r3, #0x1
_0209E1B4:
	cmp r3, #0x0
	beq _0209E1F4
	ldrh r1, [r0, #0xc]
	ldrh lr, [r0, #0xe]
	ldr r3, [r2, #0x1c]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, lr, asr #0x8
	mov r2, r0, lsr #0x10
	orr r0, r1, lr, lsl #0x8
	mov r1, r2, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r1, r0, lsr #0x10
	cmp r3, r0
	moveq r12, #0x1
_0209E1F4:
	mov r0, r12
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FUN_0209E200
FUN_0209E200: ; 0x0209E200
	stmdb sp!, {r4-r6,lr}
	ldr r2, _0209E2DC ; =OSi_ThreadInfo
	ldr r3, [r2, #0x8]
	cmp r3, #0x0
	beq _0209E2D0
_0209E214:
	ldr r12, [r3, #0xa4]
	cmp r12, #0x0
	beq _0209E2C4
	ldr r2, [r12, #0x0]
	cmp r2, #0x0
	beq _0209E2C4
	ldrb r2, [r12, #0x8]
	cmp r2, #0x1
	bne _0209E2C4
	ldrh r5, [r1, #0x2]
	ldrh r4, [r12, #0xa]
	mov r2, r5, asr #0x8
	orr r2, r2, r5, lsl #0x8
	mov r2, r2, lsl #0x10
	cmp r4, r2, lsr #0x10
	bne _0209E2C4
	ldrh r5, [r12, #0x18]
	cmp r5, #0x0
	beq _0209E278
	ldrh r4, [r1, #0x0]
	mov r2, r4, asr #0x8
	orr r2, r2, r4, lsl #0x8
	mov r2, r2, lsl #0x10
	cmp r5, r2, lsr #0x10
	bne _0209E2C4
_0209E278:
	ldr r2, [r12, #0x1c]
	cmp r2, #0x0
	beq _0209E2B8
	ldrh r5, [r0, #0xc]
	ldrh r6, [r0, #0xe]
	mov r4, r5, asr #0x8
	orr r4, r4, r5, lsl #0x8
	mov lr, r4, lsl #0x10
	mov r4, r6, asr #0x8
	mov lr, lr, lsr #0x10
	orr r4, r4, r6, lsl #0x8
	mov r5, lr, lsl #0x10
	mov lr, r4, lsl #0x10
	orr r4, r5, lr, lsr #0x10
	cmp r2, r4
	bne _0209E2C4
_0209E2B8:
	mov r0, r12
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209E2C4:
	ldr r3, [r3, #0x68]
	cmp r3, #0x0
	bne _0209E214
_0209E2D0:
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209E2DC: .word OSi_ThreadInfo

	arm_func_start FUN_0209E2E0
FUN_0209E2E0: ; 0x0209E2E0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	mov r4, r2
	mov r6, r0
	mov r0, r5
	mov r1, r4
	bl FUN_0209FB84
	ldr r1, _0209E3D8 ; =0x0000FFFF
	cmp r0, r1
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrh r12, [r6, #0x10]
	ldrh r7, [r6, #0xc]
	ldrh r0, [r6, #0xe]
	ldrh r1, [r6, #0x12]
	mov r3, r7, asr #0x8
	mov lr, r0, asr #0x8
	orr r0, lr, r0, lsl #0x8
	mov r2, r12, asr #0x8
	orr r7, r3, r7, lsl #0x8
	orr r3, r2, r12, lsl #0x8
	mov r2, r7, lsl #0x10
	mov r12, r1, asr #0x8
	orr r1, r12, r1, lsl #0x8
	mov r3, r3, lsl #0x10
	mov r7, r2, lsr #0x10
	mov r2, r3, lsr #0x10
	mov r3, r7, lsl #0x10
	mov r0, r0, lsl #0x10
	mov r2, r2, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r0, r3, r0, lsr #0x10
	orr r1, r2, r1, lsr #0x10
	bl FUN_0209E3DC
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrb r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0209E3A0
	cmp r0, #0x8
	beq _0209E3BC
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209E3A0:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_0209E40C
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209E3BC:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_0209E524
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209E3D8: .word 0x0000FFFF

	arm_func_start FUN_0209E3DC
FUN_0209E3DC:
	cmp r0, #0x0
	beq _0209E404
	mvn r2, #0x0
	cmp r0, r2
	beq _0209E404
	cmp r1, #0x0
	beq _0209E404
	cmp r1, r2
	movne r0, #0x1
	bxne lr
_0209E404:
	mov r0, #0x0
	bx lr

	arm_func_start FUN_0209E40C
FUN_0209E40C: ; 0x0209E40C
	stmdb sp!, {r4-r8,lr}
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl OS_DisableInterrupts
	ldr r1, _0209E520 ; =OSi_ThreadInfo
	mov r8, r0
	ldr r2, [r1, #0x8]
	cmp r2, #0x0
	beq _0209E510
_0209E434:
	ldr r4, [r2, #0xa4]
	cmp r4, #0x0
	beq _0209E504
	ldr r3, [r4, #0x0]
	cmp r3, #0x0
	beq _0209E504
	ldrb r0, [r4, #0x8]
	cmp r0, #0xb
	bne _0209E504
	ldrh r1, [r6, #0x4]
	mov r0, r3, lsl #0x10
	mov r0, r0, lsr #0x10
	cmp r0, r1
	bne _0209E504
	ldrh r1, [r4, #0xa]
	ldrh r0, [r6, #0x6]
	cmp r1, r0
	bne _0209E504
	ldr r0, [r4, #0x44]
	cmp r0, #0x0
	bne _0209E504
	ldrh r12, [r7, #0xc]
	ldrh r1, [r7, #0xe]
	ldr r0, [r4, #0x1c]
	mov r3, r12, asr #0x8
	orr r3, r3, r12, lsl #0x8
	mov r3, r3, lsl #0x10
	mov r12, r1, asr #0x8
	mov r3, r3, lsr #0x10
	orr r1, r12, r1, lsl #0x8
	mov r3, r3, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r1, r3, r1, lsr #0x10
	cmp r0, r1
	bne _0209E504
	ldr r1, [r4, #0x3c]
	sub r0, r5, #0x8
	cmp r0, r1
	strhi r1, [r4, #0x44]
	strls r0, [r4, #0x44]
	ldr r1, [r4, #0x40]
	ldr r2, [r4, #0x44]
	add r0, r6, #0x8
	bl MI_CpuCopy8
	ldr r0, [r4, #0x4]
	cmp r0, #0x3
	bne _0209E510
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl OS_WakeupThreadDirect
	b _0209E510
_0209E504:
	ldr r2, [r2, #0x68]
	cmp r2, #0x0
	bne _0209E434
_0209E510:
	mov r0, r8
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209E520: .word OSi_ThreadInfo

	arm_func_start FUN_0209E524
FUN_0209E524: ; 0x0209E524
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r6, r0
	ldrh r3, [r6, #0xc]
	ldrh r4, [r6, #0xe]
	mov r5, r1
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r4, asr #0x8
	mov r3, r0, lsr #0x10
	orr r0, r1, r4, lsl #0x8
	mov r1, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r1, r0, lsr #0x10
	mov r4, r2
	bl FUN_0209FAB0
	movs r7, r0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	bl FUN_0209F438
	cmp r0, #0x0
	bne _0209E598
	mov r0, r7
	bl FUN_0209F338
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209E598:
	mov r2, #0x0
	strb r2, [r5, #0x0]
	mov r0, r5
	mov r1, r4
	strh r2, [r5, #0x2]
	bl FUN_0209FB84
	mov r1, r0, asr #0x8
	orr r0, r1, r0, lsl #0x8
	strh r0, [r5, #0x2]
	ldrh r1, [r6, #0xc]
	ldrh r6, [r6, #0xe]
	mov r2, #0x0
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r6, asr #0x8
	mov r3, r0, lsr #0x10
	orr r0, r1, r6, lsl #0x8
	mov r1, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r6, r1, r0, lsr #0x10
	mov r0, r5
	mov r1, r4
	mov r3, r2
	str r6, [sp, #0x0]
	mov r4, #0x1
	str r4, [sp, #0x4]
	bl FUN_0209ECFC
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_0209E614
FUN_0209E614: ; 0x0209E614
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	cmp r1, #0x1c
	mov r6, r0
	addcc sp, sp, #0x4
	ldmccia sp!, {r4-r7,lr}
	bxcc lr
	ldr r1, _0209E7BC ; =UNK_021C8F14
	add r0, r6, #0x8
	bl FUN_0209F9A0
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, _0209E7C0 ; =UNK_021C8F04
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrh r0, [r6, #0x0]
	cmp r0, #0x100
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrh r0, [r6, #0x2]
	cmp r0, #0x8
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrh r1, [r6, #0x4]
	ldr r0, _0209E7C4 ; =0x00000406
	cmp r1, r0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrh r1, [r6, #0x6]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0x10
	cmp r4, #0x1
	beq _0209E6D0
	cmp r4, #0x2
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
_0209E6D0:
	ldrh r1, [r6, #0xe]
	ldrh r5, [r6, #0x10]
	ldr r2, _0209E7C0 ; =UNK_021C8F04
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r1, r5, asr #0x8
	orr r0, r1, r5, lsl #0x8
	mov r1, r0, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r1, r3, r1, lsr #0x10
	ldr r0, [r2, #0x0]
	ldrh r3, [r6, #0x18]
	ldrh lr, [r6, #0x1a]
	cmp r1, r0
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	moveq r5, #0x1
	mov r3, lr, asr #0x8
	mov r12, r2, lsr #0x10
	orr r2, r3, lr, lsl #0x8
	mov r3, r12, lsl #0x10
	mov r2, r2, lsl #0x10
	orr r2, r3, r2, lsr #0x10
	movne r5, #0x0
	cmp r0, r2
	moveq r7, #0x1
	movne r7, #0x0
	cmp r5, #0x0
	bne _0209E75C
	mov r2, r7
	add r0, r6, #0x8
	bl FUN_0209F12C
_0209E75C:
	cmp r4, #0x1
	bne _0209E780
	cmp r7, #0x0
	beq _0209E780
	mov r0, r6
	bl FUN_0209E7CC
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209E780:
	cmp r4, #0x2
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	cmp r7, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	cmp r5, #0x0
	ldrne r0, _0209E7C8 ; =UNK_021C8EAC
	movne r1, #0x1
	strneb r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209E7BC: .word UNK_021C8F14
_0209E7C0: .word UNK_021C8F04
_0209E7C4: .word 0x00000406
_0209E7C8: .word UNK_021C8EAC

	arm_func_start FUN_0209E7CC
FUN_0209E7CC: ; 0x0209E7CC
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r3, #0x200
	add r0, r4, #0x8
	add r1, r4, #0x12
	mov r2, #0xa
	strh r3, [r4, #0x6]
	bl MI_CpuCopy8
	ldr r0, _0209E870 ; =UNK_021C8F14
	add r1, r4, #0x8
	mov r2, #0x6
	bl MI_CpuCopy8
	ldr r3, _0209E874 ; =UNK_021C8F04
	add r0, r4, #0x12
	ldr r2, [r3, #0x0]
	sub r1, r4, #0xe
	mov r2, r2, lsr #0x10
	mov r2, r2, lsl #0x10
	mov r12, r2, lsr #0x10
	mov r2, r12, asr #0x8
	orr r2, r2, r12, lsl #0x8
	strh r2, [r4, #0xe]
	ldr r3, [r3, #0x0]
	mov r2, #0x6
	mov r3, r3, lsl #0x10
	mov r12, r3, lsr #0x10
	mov r3, r12, asr #0x8
	orr r3, r3, r12, lsl #0x8
	strh r3, [r4, #0x10]
	bl MI_CpuCopy8
	ldr r0, _0209E870 ; =UNK_021C8F14
	sub r1, r4, #0x8
	mov r2, #0x6
	bl MI_CpuCopy8
	sub r0, r4, #0xe
	mov r1, #0x2a
	mov r2, #0x0
	mov r3, r2
	bl FUN_0209F930
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209E870: .word UNK_021C8F14
_0209E874: .word UNK_021C8F04

	arm_func_start FUN_0209E878
FUN_0209E878: ; 0x0209E878
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0xc
	mov r7, r2
	ldrb r2, [r7, #0x8]
	mov r9, r0
	mov r8, r1
	cmp r2, #0x0
	mov r6, r3
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r0, _0209EAEC ; =OSi_ThreadInfo
	ldr r3, _0209EAF0 ; =UNK_021C8F04
	ldr r1, _0209EAF4 ; =UNK_021C9160
	ldr r0, [r0, #0x4]
	ldr r12, [r3, #0x0]
	cmp r0, r1
	ldreq r4, _0209EAF8 ; =UNK_021C8F5E
	ldrne r0, [r7, #0x4c]
	addne r4, r0, #0x22
	ands r0, r6, #0x2
	movne r5, #0x18
	moveq r5, #0x14
	add r1, r5, r8
	mov r2, r1, lsl #0x10
	mov r1, r12, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r12, r1, lsr #0x10
	mov r1, r12, asr #0x8
	orr r1, r1, r12, lsl #0x8
	strh r1, [r4, #-0xc]
	ldr r1, [r3, #0x0]
	mov r12, r2, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r2, r1, lsr #0x10
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	strh r1, [r4, #-0xa]
	ldr r1, [r7, #0x1c]
	mov r3, r12, asr #0x8
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r2, r1, lsr #0x10
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	strh r1, [r4, #-0x8]
	ldr r1, [r7, #0x1c]
	mov r2, r5, lsr #0x2
	mov r1, r1, lsl #0x10
	mov lr, r1, lsr #0x10
	mov r1, lr, asr #0x8
	orr r1, r1, lr, lsl #0x8
	strh r1, [r4, #-0x6]
	mov r1, #0x600
	strh r1, [r4, #-0x4]
	orr r1, r3, r12, lsl #0x8
	strh r1, [r4, #-0x2]
	ldrh r12, [r7, #0xa]
	cmp r0, #0x0
	mov r2, r2, lsl #0x4
	mov r3, r12, asr #0x8
	orr r3, r3, r12, lsl #0x8
	strh r3, [r4, #0x0]
	ldrh r3, [r7, #0x18]
	mov r1, #0x0
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [r4, #0x2]
	ldr r0, [r7, #0x28]
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [r4, #0x4]
	ldr r0, [r7, #0x28]
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [r4, #0x6]
	ldr r0, [r7, #0x24]
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [r4, #0x8]
	ldr r0, [r7, #0x24]
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [r4, #0xa]
	strb r2, [r4, #0xc]
	strb r6, [r4, #0xd]
	ldr r2, [r7, #0x3c]
	ldr r0, [r7, #0x44]
	sub r0, r2, r0
	mov r0, r0, lsl #0x10
	mov r2, r0, lsr #0x10
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	strh r0, [r4, #0xe]
	strh r1, [r4, #0x10]
	strh r1, [r4, #0x12]
	beq _0209EA64
	ldr r1, _0209EAFC ; =UNK_021C8EB0
	ldrh r0, [r1, #0x0]
	add r0, r0, #0x2040000
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r2, r0, lsr #0x10
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	strh r0, [r4, #0x14]
	ldrh r0, [r1, #0x0]
	add r0, r0, #0x2040000
	mov r0, r0, lsl #0x10
	mov r1, r0, lsr #0x10
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	strh r0, [r4, #0x16]
_0209EA64:
	sub r0, r4, #0xc
	add r1, r5, #0xc
	mov r2, #0x0
	bl FUN_0209FBC8
	mov r2, r0
	mov r0, r9
	mov r1, r8
	bl FUN_0209FBC8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl FUN_0209FBAC
	mov r3, r0, asr #0x8
	orr r0, r3, r0, lsl #0x8
	strh r0, [r4, #0x10]
	mov r0, r4
	ldr r4, [r7, #0x1c]
	mov r3, #0x6
	str r4, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r1, r5
	mov r2, r9
	mov r3, r8
	bl FUN_0209ECFC
	ands r0, r6, #0x3
	ldr r0, [r7, #0x28]
	add r1, r7, #0x28
	add r0, r0, r8
	str r0, [r7, #0x28]
	ldrne r0, [r1, #0x0]
	addne r0, r0, #0x1
	strne r0, [r1, #0x0]
	add sp, sp, #0xc
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_0209EAEC: .word OSi_ThreadInfo
_0209EAF0: .word UNK_021C8F04
_0209EAF4: .word UNK_021C9160
_0209EAF8: .word UNK_021C8F5E
_0209EAFC: .word UNK_021C8EB0

	arm_func_start FUN_0209EB00
FUN_0209EB00:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	ldr r7, _0209EC3C ; =UNK_021C8F04
	mov r5, r2
	ldr r2, [r7, #0x0]
	mov r6, r1
	mov r1, r2, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r2, r1, lsr #0x10
	ldr r3, [r5, #0x4c]
	mov r1, r2, asr #0x8
	add r4, r3, #0x22
	orr r1, r1, r2, lsl #0x8
	strh r1, [r4, #-0xc]
	ldr r1, [r7, #0x0]
	add r2, r6, #0x8
	mov r1, r1, lsl #0x10
	mov r7, r1, lsr #0x10
	mov r1, r7, asr #0x8
	orr r1, r1, r7, lsl #0x8
	strh r1, [r4, #-0xa]
	ldr r1, [r5, #0x1c]
	mov r2, r2, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r7, r1, lsr #0x10
	mov r1, r7, asr #0x8
	orr r1, r1, r7, lsl #0x8
	strh r1, [r4, #-0x8]
	ldr r1, [r5, #0x1c]
	mov r2, r2, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r7, r1, lsr #0x10
	mov r1, r7, asr #0x8
	orr r7, r1, r7, lsl #0x8
	mov r1, r2, asr #0x8
	strh r7, [r4, #-0x6]
	mov r7, #0x1100
	strh r7, [r4, #-0x4]
	orr r1, r1, r2, lsl #0x8
	strh r1, [r4, #0x4]
	ldrh r1, [r4, #0x4]
	mov r7, r0
	sub r0, r4, #0xc
	strh r1, [r4, #-0x2]
	ldrh lr, [r5, #0x18]
	mov r2, #0x0
	mov r1, #0x14
	mov r12, lr, asr #0x8
	orr r12, r12, lr, lsl #0x8
	strh r12, [r4, #0x2]
	ldrh lr, [r5, #0xa]
	mov r12, lr, asr #0x8
	orr r12, r12, lr, lsl #0x8
	strh r12, [r3, #0x22]
	strh r2, [r4, #0x6]
	bl FUN_0209FBC8
	mov r2, r0
	mov r0, r7
	mov r1, r6
	bl FUN_0209FBC8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl FUN_0209FBAC
	mov r2, r7
	mov r3, r6
	mov r1, r0, asr #0x8
	orr r0, r1, r0, lsl #0x8
	strh r0, [r4, #0x6]
	ldr r1, [r5, #0x1c]
	mov r0, r4
	str r1, [sp, #0x0]
	mov r1, #0x11
	str r1, [sp, #0x4]
	mov r1, #0x8
	bl FUN_0209ECFC
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209EC3C: .word UNK_021C8F04

	arm_func_start FUN_0209EC40
FUN_0209EC40:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r5, r2
	ldr r3, [r5, #0x4c]
	mov r6, r1
	mov r1, #0x8
	ldr r2, _0209ECF4 ; =OSi_ThreadInfo
	strh r1, [r3, #0x22]
	ldr r2, [r2, #0x4]
	add r4, r3, #0x22
	strh r2, [r4, #0x4]
	mov r2, #0x0
	ldr r3, _0209ECF8 ; =UNK_021C8EB4
	strh r2, [r4, #0x2]
	ldrh lr, [r3, #0x0]
	mov r7, r0
	mov r0, r4
	strh lr, [r5, #0xa]
	ldrh r12, [r3, #0x0]
	add r12, r12, #0x1
	strh r12, [r3, #0x0]
	strh lr, [r4, #0x6]
	bl FUN_0209FBC8
	mov r2, r0
	mov r0, r7
	mov r1, r6
	bl FUN_0209FBC8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl FUN_0209FBAC
	mov r2, r7
	mov r3, r6
	mov r1, r0, asr #0x8
	orr r0, r1, r0, lsl #0x8
	strh r0, [r4, #0x2]
	ldr r1, [r5, #0x1c]
	mov r0, r4
	str r1, [sp, #0x0]
	mov r1, #0x1
	str r1, [sp, #0x4]
	mov r1, #0x8
	bl FUN_0209ECFC
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209ECF4: .word OSi_ThreadInfo
_0209ECF8: .word UNK_021C8EB4

	arm_func_start FUN_0209ECFC
FUN_0209ECFC: ; 0x0209ECFC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r10, r0
	mov r0, #0x45
	strb r0, [r10, #-0x14]
	mov r5, #0x0
	ldr r0, _0209EF0C ; =UNK_021C8EB8
	strb r5, [r10, #-0x13]
	ldrh r7, [r0, #0x0]
	ldr r6, [sp, #0x30]
	ldrb r4, [sp, #0x34]
	add r7, r7, #0x1
	strh r7, [r0, #0x0]
	ldrh r9, [r0, #0x0]
	mov r0, r6, lsr #0x10
	mov r7, #0x80
	mov r8, r9, asr #0x8
	orr r8, r8, r9, lsl #0x8
	strh r8, [r10, #-0x10]
	strb r7, [r10, #-0xc]
	ldr r7, _0209EF10 ; =UNK_021C8F04
	strb r4, [r10, #-0xb]
	ldr r8, [r7, #0x0]
	mov r4, r0, lsl #0x10
	mov r0, r8, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r8, r0, lsr #0x10
	mov r0, r8, asr #0x8
	orr r0, r0, r8, lsl #0x8
	strh r0, [r10, #-0x8]
	ldr r0, [r7, #0x0]
	mov r8, r4, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r7, r0, lsr #0x10
	mov r4, r7, asr #0x8
	mov r0, r6, lsl #0x10
	orr r9, r4, r7, lsl #0x8
	mov r7, r8, asr #0x8
	mov r4, r0, lsr #0x10
	mov r0, r4, asr #0x8
	strh r9, [r10, #-0x6]
	orr r7, r7, r8, lsl #0x8
	ldr fp, _0209EF14 ; =0x000005C8
	mov r9, r1
	strh r7, [r10, #-0x4]
	orr r0, r0, r4, lsl #0x8
	mov r8, r2
	mov r7, r3
	strh r0, [r10, #-0x2]
	cmp r9, r11
	bls _0209EE74
	mov r4, r10
	cmp r9, r11
	bls _0209EE14
	str r5, [sp, #0x8]
_0209EDD8:
	ldr r1, [sp, #0x8]
	mov r0, r10
	mov r2, r4
	mov r3, r11
	str r6, [sp, #0x0]
	orr r12, r5, #0x2000
	str r12, [sp, #0x4]
	bl FUN_0209EF18
	add r0, r5, #0xb9
	sub r9, r9, r11
	mov r0, r0, lsl #0x10
	cmp r9, r11
	add r4, r4, r11
	mov r5, r0, lsr #0x10
	bhi _0209EDD8
_0209EE14:
	cmp r9, #0x0
	beq _0209EE74
	cmp r7, #0x0
	beq _0209EE48
	mov r0, r10
	mov r2, r4
	mov r3, r9
	str r6, [sp, #0x0]
	orr r4, r5, #0x2000
	mov r1, #0x0
	str r4, [sp, #0x4]
	bl FUN_0209EF18
	b _0209EE64
_0209EE48:
	str r6, [sp, #0x0]
	mov r0, r10
	mov r2, r4
	mov r3, r9
	mov r1, #0x0
	str r5, [sp, #0x4]
	bl FUN_0209EF18
_0209EE64:
	add r0, r5, r9, lsr #0x3
	mov r0, r0, lsl #0x10
	mov r5, r0, lsr #0x10
	mov r9, #0x0
_0209EE74:
	ldr r0, _0209EF14 ; =0x000005C8
	add r1, r9, r7
	cmp r1, r0
	bls _0209EED4
	mov r11, #0x0
_0209EE88:
	ldr r0, _0209EF14 ; =0x000005C8
	mov r1, r9
	sub r4, r0, r9
	mov r0, r10
	mov r2, r8
	mov r3, r4
	str r6, [sp, #0x0]
	orr r9, r5, #0x2000
	str r9, [sp, #0x4]
	bl FUN_0209EF18
	add r0, r5, #0xb9
	mov r1, r0, lsl #0x10
	ldr r0, _0209EF14 ; =0x000005C8
	sub r7, r7, r4
	mov r9, r11
	cmp r7, r0
	add r8, r8, r4
	mov r5, r1, lsr #0x10
	bhi _0209EE88
_0209EED4:
	adds r0, r9, r7
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	str r6, [sp, #0x0]
	mov r0, r10
	mov r1, r9
	mov r2, r8
	mov r3, r7
	str r5, [sp, #0x4]
	bl FUN_0209EF18
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209EF0C: .word UNK_021C8EB8
_0209EF10: .word UNK_021C8F04
_0209EF14: .word 0x000005C8

	arm_func_start FUN_0209EF18
FUN_0209EF18: ; 0x0209EF18
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r7, r1
	mov r5, r3
	add r1, r7, #0x14
	add r1, r1, r5
	ldr r3, [sp, #0x24]
	mov r1, r1, lsl #0x10
	mov r4, r1, lsr #0x10
	mov r1, r3, lsl #0x10
	mov r3, r4, asr #0x8
	mov r1, r1, lsr #0x10
	mov r8, r0
	orr r3, r3, r4, lsl #0x8
	mov r0, r1, asr #0x8
	strh r3, [r8, #-0x12]
	orr r0, r0, r1, lsl #0x8
	strh r0, [r8, #-0xe]
	mov r3, #0x0
	sub r0, r8, #0x14
	mov r1, #0x14
	mov r6, r2
	strh r3, [r8, #-0xa]
	ldr r4, [sp, #0x20]
	bl FUN_0209FB84
	mov r2, r0, asr #0x8
	ldr r1, _0209F040 ; =0x7F000001
	orr r0, r2, r0, lsl #0x8
	strh r0, [r8, #-0xa]
	cmp r4, r1
	beq _0209EFC4
	ldr r0, _0209F044 ; =UNK_021C8F04
	ldr r0, [r0, #0x0]
	cmp r4, r0
	beq _0209EFC4
	mov r2, r6
	mov r3, r5
	str r4, [sp, #0x0]
	mov r12, #0x800
	sub r0, r8, #0x14
	add r1, r7, #0x14
	str r12, [sp, #0x4]
	bl FUN_0209F050
_0209EFC4:
	ldr r0, _0209F040 ; =0x7F000001
	cmp r4, r0
	beq _0209EFF8
	ldr r0, _0209F044 ; =UNK_021C8F04
	ldr r0, [r0, #0x0]
	cmp r4, r0
	beq _0209EFF8
	mov r0, r4
	bl FUN_0209FA54
	cmp r0, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
_0209EFF8:
	ldr r0, _0209F048 ; =UNK_02106230
	sub r1, r8, #0x1c
	mov r2, #0x8
	bl MI_CpuCopy8
	bl OS_DisableInterrupts
	mov r4, r0
	ldr r0, _0209F04C ; =UNK_021C8F14
	str r6, [sp, #0x0]
	mov r1, r0
	str r5, [sp, #0x4]
	sub r2, r8, #0x1c
	add r3, r7, #0x1c
	bl FUN_0209F6C0
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209F040: .word 0x7F000001
_0209F044: .word UNK_021C8F04
_0209F048: .word UNK_02106230
_0209F04C: .word UNK_021C8F14

	arm_func_start FUN_0209F050
FUN_0209F050: ; 0x0209F050
	stmdb sp!, {r4-r8,lr}
	ldrh r5, [sp, #0x1c]
	ldr r4, [sp, #0x18]
	mov r8, r0
	mov r0, r5, asr #0x8
	orr r12, r0, r5, lsl #0x8
	mov r0, r4
	mov r7, r1
	mov r6, r2
	mov r5, r3
	strh r12, [r8, #-0x2]
	bl FUN_0209FA54
	cmp r0, #0x0
	bne _0209F0CC
	mov r0, r4
	bl FUN_0209FAB0
	movs r4, r0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	bl FUN_0209F438
	cmp r0, #0x0
	bne _0209F0B0
	mov r0, r4
	bl FUN_0209F2AC
_0209F0B0:
	cmp r0, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	sub r1, r8, #0xe
	mov r2, #0x6
	bl MI_CpuCopy8
	b _0209F0FC
_0209F0CC:
	mov r0, #0x1
	strb r0, [r8, #-0xe]
	mov r1, #0x0
	mov r0, r4, lsr #0x10
	strb r1, [r8, #-0xd]
	mov r1, #0x5e
	strb r1, [r8, #-0xc]
	and r0, r0, #0x7f
	strb r0, [r8, #-0xb]
	mov r0, r4, lsr #0x8
	strb r0, [r8, #-0xa]
	strb r4, [r8, #-0x9]
_0209F0FC:
	ldr r0, _0209F128 ; =UNK_021C8F14
	sub r1, r8, #0x8
	mov r2, #0x6
	bl MI_CpuCopy8
	mov r2, r6
	mov r3, r5
	sub r0, r8, #0xe
	add r1, r7, #0xe
	bl FUN_0209F930
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209F128: .word UNK_021C8F14

	arm_func_start FUN_0209F12C
FUN_0209F12C: ; 0x0209F12C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r3, _0209F29C ; =0x7F000001
	mov r6, r1
	cmp r6, r3
	mov r7, r0
	mov r4, r2
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, _0209F2A0 ; =UNK_021C8F04
	ldr r0, [r0, #0x0]
	cmp r6, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r6
	bl FUN_0209FAD8
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r6
	bl FUN_0209FA54
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	mov r0, r0, lsl #0x10
	ldr r1, _0209F2A4 ; =UNK_021C8F78
	mov r5, r0, lsr #0x10
	mov r2, #0x0
_0209F1B8:
	ldr r0, [r1, #0x0]
	cmp r6, r0
	bne _0209F1F8
	mov r0, #0xc
	mul r4, r2, r0
	ldr r0, _0209F2A4 ; =UNK_021C8F78
	ldr r3, _0209F2A8 ; =UNK_021C8F82
	add r1, r0, r4
	mov r0, r7
	add r1, r1, #0x4
	mov r2, #0x6
	strh r5, [r3, r4]
	bl MI_CpuCopy8
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209F1F8:
	add r2, r2, #0x1
	cmp r2, #0x8
	add r1, r1, #0xc
	blo _0209F1B8
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r12, #0x0
	ldr r4, _0209F2A4 ; =UNK_021C8F78
	mov r0, r12
	mov r3, r12
_0209F228:
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	moveq r0, r3
	beq _0209F264
	ldrh r1, [r4, #0xa]
	add r4, r4, #0xc
	sub r1, r5, r1
	mov r1, r1, lsl #0x10
	mov r2, r1, asr #0x10
	cmp r2, r12
	movgt r0, r3
	add r3, r3, #0x1
	movgt r12, r1, lsr #0x10
	cmp r3, #0x8
	blo _0209F228
_0209F264:
	mov r1, #0xc
	mul r4, r0, r1
	ldr r3, _0209F2A4 ; =UNK_021C8F78
	mov r0, r7
	add r1, r3, r4
	add r1, r1, #0x4
	mov r2, #0x6
	str r6, [r3, r4]
	bl MI_CpuCopy8
	ldr r0, _0209F2A8 ; =UNK_021C8F82
	strh r5, [r0, r4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209F29C: .word 0x7F000001
_0209F2A0: .word UNK_021C8F04
_0209F2A4: .word UNK_021C8F78
_0209F2A8: .word UNK_021C8F82

	arm_func_start FUN_0209F2AC
FUN_0209F2AC:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	mov r8, #0x0
	ldr r4, _0209F334 ; =UNK_021C8F04
	mov r6, r8
	mov r5, #0x64
_0209F2C8:
	mov r0, r9
	bl FUN_0209F338
	mov r7, r6
_0209F2D4:
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	mov r0, r5
	bl OS_Sleep
	mov r0, r9
	bl FUN_0209F438
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r9,lr}
	bxne lr
	add r7, r7, #0x1
	cmp r7, #0x14
	blo _0209F2D4
	add r8, r8, #0x1
	cmp r8, #0x8
	blo _0209F2C8
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_0209F334: .word UNK_021C8F04

	arm_func_start FUN_0209F338
FUN_0209F338: ; 0x0209F338
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x30
	mov r4, r0
	add r0, sp, #0x0
	mov r1, #0x0
	mov r2, #0x2a
	bl MI_CpuFill8
	add r0, sp, #0x0
	mov r1, #0xff
	mov r2, #0x6
	bl MI_CpuFill8
	ldr r0, _0209F428 ; =UNK_021C8F14
	add r1, sp, #0x6
	mov r2, #0x6
	bl MI_CpuCopy8
	mov r0, #0x1
	ldr r1, _0209F42C ; =0x00000608
	strb r0, [sp, #0xf]
	strh r1, [sp, #0xc]
	strb r0, [sp, #0x15]
	mov r0, #0x8
	ldr r1, _0209F430 ; =0x00000406
	strb r0, [sp, #0x10]
	strh r1, [sp, #0x12]
	ldr r0, _0209F428 ; =UNK_021C8F14
	add r1, sp, #0x16
	mov r2, #0x6
	bl MI_CpuCopy8
	ldr r0, _0209F434 ; =UNK_021C8F04
	mov r1, r4, lsr #0x10
	ldr r3, [r0, #0x0]
	mov r0, r1, lsl #0x10
	mov r2, r0, lsr #0x10
	mov r0, r4, lsl #0x10
	mov r1, r0, lsr #0x10
	mov r0, r3, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0x10
	mov r0, r3, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r0, r4, asr #0x8
	orr r0, r0, r4, lsl #0x8
	strh r0, [sp, #0x1c]
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [sp, #0x1e]
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	strh r0, [sp, #0x26]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r2, #0x0
	strh r0, [sp, #0x28]
	add r0, sp, #0x0
	mov r1, #0x2a
	mov r3, r2
	bl FUN_0209F930
	add sp, sp, #0x30
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209F428: .word UNK_021C8F14
_0209F42C: .word 0x00000608
_0209F430: .word 0x00000406
_0209F434: .word UNK_021C8F04

	arm_func_start FUN_0209F438
FUN_0209F438:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	bl OS_DisableInterrupts
	ldr r1, _0209F504 ; =0x7F000001
	mov r4, r0
	cmp r7, r1
	mov r5, #0x0
	beq _0209F46C
	ldr r0, _0209F508 ; =UNK_021C8F04
	ldr r0, [r0, #0x0]
	cmp r7, r0
	bne _0209F474
_0209F46C:
	ldr r5, _0209F50C ; =UNK_021C8F14
	b _0209F4EC
_0209F474:
	mov r0, r7
	bl FUN_0209FA68
	cmp r0, #0x0
	bne _0209F494
	mov r0, r7
	bl FUN_0209FA54
	cmp r0, #0x0
	beq _0209F49C
_0209F494:
	ldr r5, _0209F510 ; =UNK_0210621C
	b _0209F4EC
_0209F49C:
	ldr r1, _0209F514 ; =UNK_021C8F78
	mov r6, r5
_0209F4A4:
	ldr r0, [r1, #0x0]
	cmp r7, r0
	bne _0209F4DC
	bl OS_GetTick
	mov r2, #0xc
	mul r3, r6, r2
	ldr r2, _0209F514 ; =UNK_021C8F78
	mov r5, r0, lsr #0x10
	add r0, r2, r3
	ldr r2, _0209F518 ; =UNK_021C8F82
	orr r5, r5, r1, lsl #0x10
	strh r5, [r2, r3]
	add r5, r0, #0x4
	b _0209F4EC
_0209F4DC:
	add r6, r6, #0x1
	cmp r6, #0x8
	add r1, r1, #0xc
	blo _0209F4A4
_0209F4EC:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209F504: .word 0x7F000001
_0209F508: .word UNK_021C8F04
_0209F50C: .word UNK_021C8F14
_0209F510: .word UNK_0210621C
_0209F514: .word UNK_021C8F78
_0209F518: .word UNK_021C8F82

	arm_func_start FUN_0209F51C
FUN_0209F51C: ; 0x0209F51C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r2, _0209F570 ; =UNK_021C8EE4
	ldr r1, _0209F574 ; =UNK_021C8F0C
	ldr lr, [r2, #0x0]
	ldr r12, [r1, #0x0]
	ldr r3, [r2, #0x0]
	ldr r1, _0209F578 ; =UNK_021C8F10
	ldrh r3, [r12, r3]
	add r3, lr, r3
	str r3, [r2, #0x0]
	ldr r3, [r2, #0x0]
	ldr r1, [r1, #0x0]
	cmp r3, r1
	movcs r1, #0x0
	strcs r1, [r2, #0x0]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209F570: .word UNK_021C8EE4
_0209F574: .word UNK_021C8F0C
_0209F578: .word UNK_021C8F10

	arm_func_start FUN_0209F57C
FUN_0209F57C: ; 0x0209F57C
	stmdb sp!, {r4-r10,lr}
	mov r6, r0
	bl OS_DisableInterrupts
	ldr sl, _0209F644 ; =UNK_021C8EE4
	ldr sb, _0209F648 ; =UNK_021C8EDC
	ldr r2, [r10, #0x0]
	ldr r1, [r9, #0x0]
	mov r5, r0
	cmp r2, r1
	bne _0209F5D4
	ldr r8, _0209F64C ; =OSi_ThreadInfo
	ldr r7, _0209F650 ; =UNK_021C8F08
	mov r4, #0x0
_0209F5B0:
	ldr r1, [r8, #0x4]
	mov r0, r4
	str r1, [r7, #0x0]
	bl OS_SleepThread
	str r4, [r7, #0x0]
	ldr r1, [r10, #0x0]
	ldr r0, [r9, #0x0]
	cmp r1, r0
	beq _0209F5B0
_0209F5D4:
	mov r0, r5
	bl OS_RestoreInterrupts
	ldr r0, _0209F654 ; =UNK_021C8F0C
	ldr r5, [r0, #0x0]
	ldr r0, _0209F644 ; =UNK_021C8EE4
	ldr r1, _0209F658 ; =UNK_021C8F10
	mov r3, #0x0
_0209F5F0:
	ldr r4, [r1, #0x0]
	ldr r2, [r0, #0x0]
	sub r2, r4, r2
	cmp r2, #0x2
	strcc r3, [r0, #0x0]
	ldr r2, [r0, #0x0]
	ldrh r2, [r5, r2]
	cmp r2, #0x0
	streq r3, [r0, #0x0]
	cmp r2, #0x0
	beq _0209F5F0
	sub r0, r2, #0x2
	ldr r1, _0209F654 ; =UNK_021C8F0C
	str r0, [r6, #0x0]
	ldr r0, _0209F644 ; =UNK_021C8EE4
	ldr r1, [r1, #0x0]
	ldr r0, [r0, #0x0]
	add r0, r1, r0
	add r0, r0, #0x2
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_0209F644: .word UNK_021C8EE4
_0209F648: .word UNK_021C8EDC
_0209F64C: .word OSi_ThreadInfo
_0209F650: .word UNK_021C8F08
_0209F654: .word UNK_021C8F0C
_0209F658: .word UNK_021C8F10

	arm_func_start FUN_0209F65C
FUN_0209F65C: ; 0x0209F65C
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	mov r12, #0x0
	str r12, [sp, #0x0]
	str r12, [sp, #0x4]
	bl FUN_0209F6C0
	ldr r0, _0209F6BC ; =UNK_021C8F08
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0xc
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r0, [r0, #0x0]
	bl OS_IsThreadTerminated
	cmp r0, #0x0
	addne sp, sp, #0xc
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _0209F6BC ; =UNK_021C8F08
	ldr r0, [r0, #0x0]
	bl OS_WakeupThreadDirect
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209F6BC: .word UNK_021C8F08

	arm_func_start FUN_0209F6C0
FUN_0209F6C0: ; 0x0209F6C0
	stmdb sp!, {r4-r8,lr}
	ldr r4, _0209F918 ; =UNK_021C8F0C
	mov r7, r0
	ldr r0, [r4, #0x0]
	mov r6, r2
	mov r5, r3
	cmp r0, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r2, _0209F91C ; =UNK_021C8F10
	ldr r2, [r2, #0x0]
	cmp r2, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r2, [sp, #0x1c]
	add r2, r5, r2
	cmp r2, #0x8
	ldmccia sp!, {r4-r8,lr}
	bxcc lr
	ldr r3, _0209F920 ; =0x000005E4
	cmp r2, r3
	ldmhiia sp!, {r4-r8,lr}
	bxhi lr
	ldr r3, _0209F924 ; =UNK_02106230
	ldrb r8, [r6, #0x0]
	ldrb r4, [r3, #0x0]
	cmp r8, r4
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldrb r8, [r6, #0x1]
	ldrb r4, [r3, #0x1]
	cmp r8, r4
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldrb r4, [r6, #0x2]
	ldrb r3, [r3, #0x2]
	cmp r4, r3
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldrb r3, [r6, #0x6]
	cmp r3, #0x8
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldrb r3, [r6, #0x7]
	cmp r3, #0x0
	beq _0209F784
	cmp r3, #0x6
	ldmneia sp!, {r4-r8,lr}
	bxne lr
_0209F784:
	ldr r4, _0209F928 ; =UNK_021C8EDC
	add r2, r2, #0x9
	bic r2, r2, #0x1
	ldr lr, [r4, #0x0]
	mov r3, r2, lsl #0x10
	ldr ip, _0209F92C ; =UNK_021C8EE4
	ldr r8, [r4, #0x0]
	ldr r4, [r12, #0x0]
	mov r2, r3, lsr #0x10
	cmp r8, r4
	add r4, lr, r3, lsr #0x10
	bhs _0209F7C4
	ldr r3, [r12, #0x0]
	cmp r3, r4
	ldmlsia sp!, {r4-r8,lr}
	bxls lr
_0209F7C4:
	ldr r3, _0209F91C ; =UNK_021C8F10
	ldr r8, [r3, #0x0]
	cmp r4, r8
	bne _0209F7F0
	ldr r3, _0209F92C ; =UNK_021C8EE4
	mov r4, #0x0
	ldr r3, [r3, #0x0]
	cmp r3, #0x0
	bne _0209F814
	ldmia sp!, {r4-r8,lr}
	bx lr
_0209F7F0:
	ldr r3, [r3, #0x0]
	cmp r4, r3
	bls _0209F814
	ldr r3, _0209F92C ; =UNK_021C8EE4
	mov r4, r2
	ldr r3, [r3, #0x0]
	cmp r3, r2
	ldmlsia sp!, {r4-r8,lr}
	bxls lr
_0209F814:
	ldr ip, _0209F928 ; =UNK_021C8EDC
	ldr r3, _0209F91C ; =UNK_021C8F10
	ldr lr, [r12, #0x0]
	ldr r8, [r3, #0x0]
	add lr, lr, r2
	cmp lr, r8
	bls _0209F858
	ldr r8, [r3, #0x0]
	ldr r3, [r12, #0x0]
	sub r3, r8, r3
	cmp r3, #0x2
	ldrcs r3, [r12, #0x0]
	movcs r8, #0x0
	strcsh r8, [r0, r3]
	ldr r0, _0209F928 ; =UNK_021C8EDC
	mov r3, #0x0
	str r3, [r0, #0x0]
_0209F858:
	ldr ip, _0209F918 ; =UNK_021C8F0C
	ldr r3, _0209F928 ; =UNK_021C8EDC
	ldr r8, [r12, #0x0]
	ldr lr, [r3, #0x0]
	mov r0, r1
	strh r2, [r8, lr]
	ldr r12, [r12, #0x0]
	ldr r1, [r3, #0x0]
	mov r2, #0x6
	add r1, r12, r1
	add r1, r1, #0x2
	bl MI_CpuCopy8
	ldr r1, _0209F918 ; =UNK_021C8F0C
	ldr r0, _0209F928 ; =UNK_021C8EDC
	ldr r2, [r1, #0x0]
	ldr r1, [r0, #0x0]
	mov r0, r7
	add r1, r2, r1
	add r1, r1, #0x8
	mov r2, #0x6
	bl MI_CpuCopy8
	ldr r1, _0209F918 ; =UNK_021C8F0C
	ldr r0, _0209F928 ; =UNK_021C8EDC
	ldr r2, [r1, #0x0]
	ldr r1, [r0, #0x0]
	add r0, r6, #0x6
	add r1, r2, r1
	add r1, r1, #0xe
	sub r2, r5, #0x6
	bl MI_CpuCopy8
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	beq _0209F908
	ldr r2, [sp, #0x1c]
	cmp r2, #0x0
	beq _0209F908
	ldr r3, _0209F918 ; =UNK_021C8F0C
	ldr r1, _0209F928 ; =UNK_021C8EDC
	ldr r3, [r3, #0x0]
	ldr r1, [r1, #0x0]
	add r1, r3, r1
	add r1, r1, #0x8
	add r1, r1, r5
	bl MI_CpuCopy8
_0209F908:
	ldr r0, _0209F928 ; =UNK_021C8EDC
	str r4, [r0, #0x0]
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209F918: .word UNK_021C8F0C
_0209F91C: .word UNK_021C8F10
_0209F920: .word 0x000005E4
_0209F924: .word UNK_02106230
_0209F928: .word UNK_021C8EDC
_0209F92C: .word UNK_021C8EE4

	arm_func_start FUN_0209F930
FUN_0209F930: ; 0x0209F930
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	add r1, r6, r5
	mov r4, r3
	cmp r1, r2
	beq _0209F958
	mov r0, r2
	mov r2, r4
	bl MI_CpuCopy8
_0209F958:
	ldr r0, _0209F998 ; =UNK_02106230
	add r1, r6, #0x6
	mov r2, #0x6
	bl MI_CpuCopy8
	add r2, r5, r4
	mov r0, r6
	add r1, r6, #0x6
	sub r2, r2, #0x6
	bl FUN_020A8644
	cmp r0, #0x0
	movlt r1, #0x1
	ldr r0, _0209F99C ; =UNK_021C8EA8
	movge r1, #0x0
	strb r1, [r0, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209F998: .word UNK_02106230
_0209F99C: .word UNK_021C8EA8

	arm_func_start FUN_0209F9A0
FUN_0209F9A0:
	mov r12, #0x0
_0209F9A4:
	ldrh r3, [r0], #0x2
	ldrh r2, [r1], #0x2
	cmp r3, r2
	movne r0, #0x1
	bxne lr
	add r12, r12, #0x1
	cmp r12, #0x3
	blt _0209F9A4
	mov r0, #0x0
	bx lr

	arm_func_start FUN_0209F9CC
FUN_0209F9CC:
	stmdb sp!, {r4-r6,lr}
	ldr r1, _0209FA4C ; =UNK_021C8F04
	mov r5, #0x1
	ldr r1, [r1, #0x0]
	mov r6, r0
	mov r4, r5
	mov r2, r5
	mov r0, r5
	cmp r1, #0x0
	beq _0209F9FC
	cmp r6, r1
	movne r0, #0x0
_0209F9FC:
	cmp r0, #0x0
	bne _0209FA10
	ldr r0, _0209FA50 ; =0x7F000001
	cmp r6, r0
	movne r2, #0x0
_0209FA10:
	cmp r2, #0x0
	bne _0209FA28
	mov r0, r6
	bl FUN_0209FA68
	cmp r0, #0x0
	moveq r4, #0x0
_0209FA28:
	cmp r4, #0x0
	bne _0209FA40
	mov r0, r6
	bl FUN_0209FA54
	cmp r0, #0x0
	moveq r5, #0x0
_0209FA40:
	mov r0, r5
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209FA4C: .word UNK_021C8F04
_0209FA50: .word 0x7F000001

	arm_func_start FUN_0209FA54
FUN_0209FA54:
	and r0, r0, #0xf0000000
	cmp r0, #0xe0000000
	moveq r0, #0x1
	movne r0, #0x0
	bx lr

	arm_func_start FUN_0209FA68
FUN_0209FA68:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, #0x0
	bl FUN_0209FAD8
	cmp r0, #0x0
	beq _0209FA9C
	ldr r0, _0209FAAC ; =UNK_021C8ED0
	ldr r0, [r0, #0x0]
	mvn r1, r0
	and r0, r1, r5
	cmp r1, r0
	moveq r4, #0x1
_0209FA9C:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209FAAC: .word UNK_021C8ED0

	arm_func_start FUN_0209FAB0
FUN_0209FAB0:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_0209FAD8
	cmp r0, #0x0
	ldreq r0, _0209FAD4 ; =UNK_021C8EE0
	ldreq r4, [r0, #0x0]
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209FAD4: .word UNK_021C8EE0

	arm_func_start FUN_0209FAD8
FUN_0209FAD8:
	mvn r1, #0x0
	cmp r0, r1
	mov r12, #0x1
	beq _0209FB14
	ldr r1, _0209FB1C ; =0x7F000001
	cmp r0, r1
	beq _0209FB14
	ldr r2, _0209FB20 ; =UNK_021C8ED0
	ldr r1, _0209FB24 ; =UNK_021C8F04
	ldr r3, [r2, #0x0]
	ldr r1, [r1, #0x0]
	and r2, r0, r3
	and r0, r1, r3
	cmp r2, r0
	movne r12, #0x0
_0209FB14:
	mov r0, r12
	bx lr
	.balign 4
_0209FB1C: .word 0x7F000001
_0209FB20: .word UNK_021C8ED0
_0209FB24: .word UNK_021C8F04

	arm_func_start FUN_0209FB28
FUN_0209FB28:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r2
	mov r2, r3
	mov r5, r1
	bl FUN_0209FBC8
	mov r2, r0
	add r0, r4, #0xc
	mov r1, #0x8
	bl FUN_0209FBC8
	add r1, r0, r5
	ands r0, r1, #0x10000
	ldrne r0, _0209FB80 ; =0x0000FFFF
	addne r1, r1, #0x1
	andne r1, r1, r0
	ldr r0, _0209FB80 ; =0x0000FFFF
	cmp r1, r0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209FB80: .word 0x0000FFFF

	arm_func_start FUN_0209FB84
FUN_0209FB84: ; 0x0209FB84
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, #0x0
	bl FUN_0209FBC8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl FUN_0209FBAC
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_0209FBAC
FUN_0209FBAC: ; 0x0209FBAC
	ldr r1, _0209FBC4 ; =0x0000FFFF
	eor r0, r0, r1
	mov r0, r0, lsl #0x10
	movs r0, r0, lsr #0x10
	moveq r0, r1
	bx lr
	.balign 4
_0209FBC4: .word 0x0000FFFF

	arm_func_start FUN_0209FBC8
FUN_0209FBC8: ; 0x0209FBC8
	ands r3, r0, #0x1
	beq _0209FC00
	cmp r1, #0x1
	bls _0209FC54
_0209FBD8:
	ldrb r12, [r0, #0x0]
	ldrb r3, [r0, #0x1]
	sub r1, r1, #0x2
	cmp r1, #0x1
	orr r3, r3, r12, lsl #0x8
	mov r3, r3, lsl #0x10
	add r2, r2, r3, lsr #0x10
	add r0, r0, #0x2
	bhi _0209FBD8
	b _0209FC54
_0209FC00:
	mov r2, r2, lsl #0x10
	mov r3, r2, lsr #0x10
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	cmp r1, #0x1
	mov r2, r2, lsr #0x10
	bls _0209FC38
_0209FC20:
	ldrh r3, [r0, #0x0]
	sub r1, r1, #0x2
	cmp r1, #0x1
	add r2, r2, r3
	add r0, r0, #0x2
	bhi _0209FC20
_0209FC38:
	ldr r3, _0209FC7C ; =0x00FF00FF
	ldr ip, _0209FC80 ; =0xFF00FF00
	and r3, r3, r2, lsr #0x8
	and r2, r12, r2, lsl #0x8
	orr r3, r3, r2
	mov r2, r3, lsr #0x10
	orr r2, r2, r3, lsl #0x10
_0209FC54:
	cmp r1, #0x0
	ldrneb r0, [r0, #0x0]
	addne r2, r2, r0, lsl #0x8
	ldr r0, _0209FC84 ; =0x0000FFFF
	and r0, r2, r0
	add r0, r0, r2, lsr #0x10
	add r0, r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bx lr
	.balign 4
_0209FC7C: .word 0x00FF00FF
_0209FC80: .word 0xFF00FF00
_0209FC84: .word 0x0000FFFF

	arm_func_start FUN_0209FC88
FUN_0209FC88: ; 0x0209FC88
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r2, _0209FCB8 ; =UNK_02106218
	ldr r0, _0209FCBC ; =UNK_021C9160
	mov r1, r4
	str r4, [r2, #0x0]
	bl OS_SetThreadPriority
	ldr r0, _0209FCC0 ; =UNK_021C90A0
	mov r1, r4
	bl OS_SetThreadPriority
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209FCB8: .word UNK_02106218
_0209FCBC: .word UNK_021C9160
_0209FCC0: .word UNK_021C90A0

	arm_func_start FUN_0209FCC4
FUN_0209FCC4:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_0209FD34
	ldr r0, _0209FD10 ; =UNK_021C90A0
	bl OS_JoinThread
	ldr r0, _0209FD14 ; =UNK_021C9160
	bl OS_DestroyThread
	ldr r1, _0209FD18 ; =UNK_021C8F08
	mov r0, #0x0
	str r0, [r1, #0x0]
	bl FUN_020A0098
	ldr r1, _0209FD1C ; =UNK_021C8F0C
	mov r2, #0x0
	ldr r0, _0209FD20 ; =UNK_021C8F10
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209FD10: .word UNK_021C90A0
_0209FD14: .word UNK_021C9160
_0209FD18: .word UNK_021C8F08
_0209FD1C: .word UNK_021C8F0C
_0209FD20: .word UNK_021C8F10

	arm_func_start FUN_0209FD24
FUN_0209FD24: ; 0x0209FD24
	ldr r1, _0209FD30 ; =UNK_021C8EF0
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_0209FD30: .word UNK_021C8EF0

	arm_func_start FUN_0209FD34
FUN_0209FD34:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	mov r5, r0
	ldr r0, _0209FD8C ; =UNK_021C90A0
	bl OS_IsThreadTerminated
	movs r4, r0
	bne _0209FD74
	ldr r1, _0209FD90 ; =UNK_021C8EF8
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	bne _0209FD74
	ldr r0, _0209FD8C ; =UNK_021C90A0
	mov r2, #0x1
	str r2, [r1, #0x0]
	bl OS_WakeupThreadDirect
_0209FD74:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209FD8C: .word UNK_021C90A0
_0209FD90: .word UNK_021C8EF8

	.extern _SDK_UbiquitousCPS

	arm_func_start FUN_0209FD94
FUN_0209FD94: ; 0x0209FD94
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r4, r0
	ldr r0, _0209FFD4 ; =_SDK_UbiquitousCPS
	bl OSi_ReferSymbol
	ldr r12, [r4, #0x14]
	ldr r6, [r4, #0x18]
	mov r1, #0x0
	cmp r6, r1
	cmpeq r12, r1
	beq _0209FDEC
	ldr r0, _0209FFD8 ; =CPSiRand32ctx
	ldr r5, _0209FFDC ; =0x6C078965
	ldr r3, _0209FFE0 ; =0x5D588B65
	ldr r2, _0209FFE4 ; =0x00269EC3
	str r12, [r0, #0x0]
	str r6, [r0, #0x4]
	str r5, [r0, #0x8]
	str r3, [r0, #0xc]
	str r2, [r0, #0x10]
	str r1, [r0, #0x14]
	b _0209FE1C
_0209FDEC:
	bl OS_GetTick
	ldr r2, _0209FFD8 ; =CPSiRand32ctx
	ldr ip, _0209FFDC ; =0x6C078965
	ldr r6, _0209FFE0 ; =0x5D588B65
	ldr r5, _0209FFE4 ; =0x00269EC3
	mov r3, #0x0
	str r0, [r2, #0x0]
	str r1, [r2, #0x4]
	str r12, [r2, #0x8]
	str r6, [r2, #0xc]
	str r5, [r2, #0x10]
	str r3, [r2, #0x14]
_0209FE1C:
	ldr r2, [r4, #0x4]
	cmp r2, #0x0
	beq _0209FE4C
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	beq _0209FE4C
	ldr r1, _0209FFE8 ; =CPSiAlloc
	ldr r0, _0209FFEC ; =CPSiFree
	str r2, [r1, #0x0]
	ldr r1, [r4, #0x8]
	str r1, [r0, #0x0]
	b _0209FE60
_0209FE4C:
	ldr r2, _0209FFF0 ; =FUN_020A0058
	ldr r1, _0209FFE8 ; =CPSiAlloc
	ldr r0, _0209FFEC ; =CPSiFree
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
_0209FE60:
	ldr r1, [r4, #0x0]
	ldr r0, _0209FFF4 ; =UNK_021C8EC4
	ldr ip, _0209FFD8 ; =CPSiRand32ctx
	str r1, [r0, #0x0]
	ldr r1, [r4, #0x24]
	ldr r3, [r12, #0x8]
	cmp r1, #0x0
	ldrne r0, _0209FFF8 ; =UNK_021C8EB0
	strneh r1, [r0, #0x0]
	ldreq r1, _0209FFFC ; =0x000005B4
	ldreq r0, _0209FFF8 ; =UNK_021C8EB0
	streqh r1, [r0, #0x0]
	ldr r2, [r4, #0x28]
	ldr r1, _020A0000 ; =UNK_021C8EE8
	ldr r0, _020A0004 ; =UNK_021C8ED8
	str r2, [r1, #0x0]
	ldr r1, [r4, #0x2c]
	ldr r2, [r12, #0x0]
	str r1, [r0, #0x0]
	ldr r1, [r4, #0xc]
	umull lr, r5, r3, r2
	cmp r1, #0x0
	ldrne r0, _020A0008 ; =UNK_021C8ECC
	strne r1, [r0, #0x0]
	ldreq r1, _0209FFF0 ; =FUN_020A0058
	ldreq r0, _020A0008 ; =UNK_021C8ECC
	streq r1, [r0, #0x0]
	ldr r1, [r4, #0x10]
	cmp r1, #0x0
	ldrne r0, _020A000C ; =UNK_021C8EFC
	strne r1, [r0, #0x0]
	ldreq r1, _020A0010 ; =FUN_020A0050
	ldreq r0, _020A000C ; =UNK_021C8EFC
	streq r1, [r0, #0x0]
	ldr r1, [r12, #0x4]
	ldr r0, _020A0014 ; =0x00000F88
	mla r5, r3, r1, r5
	ldr r1, [r12, #0xc]
	ldr r3, [r12, #0x10]
	mla r5, r1, r2, r5
	adds r2, r3, lr
	ldr r1, [r12, #0x14]
	mov r3, #0x0
	adc r1, r1, r5
	umull lr, r5, r1, r0
	mla r5, r1, r3, r5
	mla r5, r3, r0, r5
	ldr r6, [r4, #0x1c]
	ldr r0, _020A0018 ; =UNK_021C8F0C
	ldr lr, _020A001C ; =UNK_021C8F10
	str r6, [r0, #0x0]
	ldr r4, [r4, #0x20]
	ldr r0, _020A0020 ; =UNK_021C8EE4
	str r4, [lr, #0x0]
	str r3, [r0, #0x0]
	ldr lr, _020A0024 ; =UNK_021C8EDC
	ldr r4, _020A0028 ; =UNK_021C8EBC
	add r5, r5, #0x400
	ldr r0, _020A002C ; =UNK_021C8F14
	str r3, [lr, #0x0]
	str r2, [r12, #0x0]
	str r1, [r12, #0x4]
	strh r5, [r4, #0x0]
	bl OS_GetMacAddress
	ldr r0, _020A0030 ; =UNK_021C8EAC
	mov r2, #0x0
	strb r2, [r0, #0x0]
	mov r1, #0x800
	str r1, [sp, #0x0]
	ldr r0, _020A0034 ; =UNK_02106218
	ldr r1, _020A0038 ; =FUN_0209CD3C
	ldr r4, [r0, #0x0]
	ldr r0, _020A003C ; =UNK_021C9160
	ldr r3, _020A0040 ; =pool_initialized
	str r4, [sp, #0x4]
	bl OS_CreateThread
	mov r1, #0x800
	ldr r0, _020A0034 ; =UNK_02106218
	str r1, [sp, #0x0]
	ldr r1, [r0, #0x0]
	ldr r0, _020A0044 ; =UNK_021C90A0
	str r1, [sp, #0x4]
	ldr r1, _020A0048 ; =FUN_0209BA80
	ldr r3, _020A004C ; =UNK_021C9EE0
	mov r2, #0x0
	bl OS_CreateThread
	ldr r0, _020A003C ; =UNK_021C9160
	bl OS_WakeupThreadDirect
	ldr r0, _020A0044 ; =UNK_021C90A0
	bl OS_WakeupThreadDirect
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209FFD4: .word _SDK_UbiquitousCPS
_0209FFD8: .word CPSiRand32ctx
_0209FFDC: .word 0x6C078965
_0209FFE0: .word 0x5D588B65
_0209FFE4: .word 0x00269EC3
_0209FFE8: .word CPSiAlloc
_0209FFEC: .word CPSiFree
_0209FFF0: .word FUN_020A0058
_0209FFF4: .word UNK_021C8EC4
_0209FFF8: .word UNK_021C8EB0
_0209FFFC: .word 0x000005B4
_020A0000: .word UNK_021C8EE8
_020A0004: .word UNK_021C8ED8
_020A0008: .word UNK_021C8ECC
_020A000C: .word UNK_021C8EFC
_020A0010: .word FUN_020A0050
_020A0014: .word 0x00000F88
_020A0018: .word UNK_021C8F0C
_020A001C: .word UNK_021C8F10
_020A0020: .word UNK_021C8EE4
_020A0024: .word UNK_021C8EDC
_020A0028: .word UNK_021C8EBC
_020A002C: .word UNK_021C8F14
_020A0030: .word UNK_021C8EAC
_020A0034: .word UNK_02106218
_020A0038: .word FUN_0209CD3C
_020A003C: .word UNK_021C9160
_020A0040: .word pool_initialized
_020A0044: .word UNK_021C90A0
_020A0048: .word FUN_0209BA80
_020A004C: .word UNK_021C9EE0

	; Ubiquitous SSL (?)

	arm_func_start FUN_020A0050
FUN_020A0050: ; 0x020A0050
	mov r0, #0x1
	bx lr

	arm_func_start FUN_020A0058
FUN_020A0058: ; 0x020A0058
	bx lr

	arm_func_start FUN_020A005C
FUN_020A005C:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020A0094 ; =UNK_021C8ED8
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020A0084
	bl OS_YieldThread
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A0084:
	bl OS_Sleep
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A0094: .word UNK_021C8ED8

	arm_func_start FUN_020A0098
FUN_020A0098: ; 0x020A0098
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r1, _020A01B8 ; =UNK_021C8F04
	ldr r5, _020A01BC ; =UNK_021C8EC0
	ldr r1, [r1, #0x0]
	ldr r3, _020A01C0 ; =UNK_021C8F1C
	cmp r1, #0x0
	mov r1, #0x0
	movne r6, #0x1
	ldr ip, _020A01C4 ; =UNK_021C8ED0
	ldr r2, _020A01C8 ; =UNK_021C8ED4
	moveq r6, #0x0
	ldr lr, _020A01B8 ; =UNK_021C8F04
	ldr r4, _020A01CC ; =UNK_021C8EE0
	cmp r6, #0x0
	str r1, [r12, #0x0]
	str r1, [r3, #0x0]
	str r1, [r3, #0x4]
	str r1, [r2, #0x0]
	addeq sp, sp, #0x4
	str r0, [r5, #0x0]
	str r1, [lr, #0x0]
	str r1, [r4, #0x0]
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, _020A01D0 ; =UNK_021C8F78
	mov r2, #0x60
	bl MI_CpuFill8
	ldr r0, _020A01D4 ; =OSi_ThreadInfo
	ldr r5, [r0, #0x8]
	cmp r5, #0x0
	beq _020A016C
	mov r4, #0x0
_020A011C:
	ldr r1, [r5, #0xa4]
	cmp r1, #0x0
	beq _020A0160
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	beq _020A0160
	ldrb r0, [r1, #0x8]
	cmp r0, #0xa
	beq _020A0148
	cmp r0, #0xb
	strneb r4, [r1, #0x8]
_020A0148:
	ldr r0, [r1, #0x4]
	cmp r0, #0x0
	beq _020A0160
	str r4, [r1, #0x4]
	ldr r0, [r1, #0x0]
	bl OS_WakeupThreadDirect
_020A0160:
	ldr r5, [r5, #0x68]
	cmp r5, #0x0
	bne _020A011C
_020A016C:
	ldr r6, _020A01D8 ; =UNK_021C9520
	mov r7, #0x0
	ldr r4, _020A01DC ; =CPSiFree
	mov r5, r7
_020A017C:
	ldrh r0, [r6, #0x4]
	cmp r0, #0x0
	beq _020A0198
	ldr r0, [r6, #0x34]
	ldr r1, [r4, #0x0]
	blx r1
	strh r5, [r6, #0x4]
_020A0198:
	add r7, r7, #0x1
	cmp r7, #0x8
	add r6, r6, #0x38
	blt _020A017C
	bl CPSi_SslCleanup
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020A01B8: .word UNK_021C8F04
_020A01BC: .word UNK_021C8EC0
_020A01C0: .word UNK_021C8F1C
_020A01C4: .word UNK_021C8ED0
_020A01C8: .word UNK_021C8ED4
_020A01CC: .word UNK_021C8EE0
_020A01D0: .word UNK_021C8F78
_020A01D4: .word OSi_ThreadInfo
_020A01D8: .word UNK_021C9520
_020A01DC: .word CPSiFree
