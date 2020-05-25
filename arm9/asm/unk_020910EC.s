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
