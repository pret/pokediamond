	.include "asm/macros.inc"
	.include "global.inc"

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

	.text

	arm_func_start sub_020910EC
sub_020910EC: ; 0x020910EC
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
	bl sub_02091130
	add sp, sp, #0x14
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start sub_02091130
sub_02091130: ; 0x02091130
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
	bl sub_0209156C
	mov r1, r0
	add r0, sp, #0x1c
	add r2, sp, #0xc
	add r3, sp, #0x10
	bl sub_020913D4
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
	bl sub_02091230
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

	arm_func_start sub_02091230
sub_02091230:
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r2
	mov r4, r3
	add r0, sp, #0x10
	add r1, sp, #0x14
	mov r2, #0x30
	mov r3, #0x0
	bl sub_02091498
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
	bl sub_02091498
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
	bl sub_02091498
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
	bl sub_02091498
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
	bl sub_02091498
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

	arm_func_start sub_020913D4
sub_020913D4:
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

	arm_func_start sub_02091498
sub_02091498:
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

	arm_func_start sub_0209156C
sub_0209156C: ; 0x0209156C
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
	bl sub_02094FAC
	mov r4, r0
	add r0, sp, #0x4
	bl sub_0209502C
	add r0, sp, #0x18
	bl sub_0209502C
	add r0, sp, #0x2c
	bl sub_0209502C
	add r0, sp, #0x40
	bl sub_0209502C
	cmp r4, #0x0
	mvneq r5, #0x1
	beq _02091688
	add r2, sp, #0x4
	mov r0, r8
	mov r1, r7
	bl sub_02094C68
	cmp r0, #0x0
	mvneq r5, #0x1
	beq _02091688
	ldr r1, [sp, #0x78]
	add r0, sp, #0x2c
	bl sub_02094D7C
	cmp r0, #0x0
	mvneq r5, #0x1
	beq _02091688
	ldr r0, [sp, #0x70]
	ldr r1, [sp, #0x74]
	add r2, sp, #0x40
	bl sub_02094C68
	cmp r0, #0x0
	mvneq r5, #0x1
	beq _02091688
	add r0, sp, #0x18
	add r1, sp, #0x4
	add r2, sp, #0x2c
	add r3, sp, #0x40
	str r4, [sp, #0x0]
	bl sub_020931B8
	cmp r0, #0x0
	mvneq r5, #0x1
	beq _02091688
	add r0, sp, #0x18
	bl sub_02095188
	add r1, r0, #0x7
	mov r0, r1, asr #0x2
	add r0, r1, r0, lsr #0x1d
	mov r0, r0, asr #0x3
	cmp r0, r5
	mvngt r5, #0x0
	bgt _02091688
	add r0, sp, #0x18
	mov r1, r6
	bl sub_02094BEC
	mov r5, r0
_02091688:
	add r0, sp, #0x4
	bl sub_0209510C
	add r0, sp, #0x18
	bl sub_0209510C
	add r0, sp, #0x2c
	bl sub_0209510C
	add r0, sp, #0x40
	bl sub_0209510C
	cmp r4, #0x0
	beq _020916B8
	mov r0, r4
	bl sub_02094F3C
_020916B8:
	mov r0, r5
	add sp, sp, #0x58
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start sub_020916C8
sub_020916C8: ; 0x020916C8
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
	bl sub_02094D7C
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
	bl sub_02094D7C
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
	bl sub_02094E24
	add sp, sp, #0x7c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020917DC:
	ldr r0, [sp, #0xa4]
	str r0, [sp, #0x18]
	cmp r0, #0x0
	bne _02091810
	bl sub_02092860
	str r0, [sp, #0x18]
	cmp r0, #0x0
	beq _02091E6C
	ldr r2, [sp, #0xa0]
	mov r1, r5
	bl sub_02092894
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
	bl sub_02092C28
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
	bl sub_0209508C
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
	bl sub_02093214
	cmp r0, #0x0
	beq _02091E6C
	ldr r0, [sp, #0x14]
	mov r1, r10
	bl sub_0209508C
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
	bl sub_02094EBC
_02091A04:
	cmp r0, #0x0
	beq _02091E6C
	ldr r0, [r8, #0x8]
	mov r1, r10, lsl #0x2
	cmp r1, r0
	movle r0, r8
	ble _02091A28
	mov r0, r8
	bl sub_02094EBC
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
	bl sub_02094EBC
_02091A54:
	cmp r0, #0x0
	beq _02091E6C
	ldr r0, [r4, #0x8]
	cmp r5, r0
	movle r0, r4
	ble _02091A78
	mov r1, r5
	mov r0, r4
	bl sub_02094EBC
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
	bl sub_02094EBC
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
	bl sub_020937E8
	str r7, [sp, #0x0]
	ldr r0, [sp, #0x38]
	mov r1, r6
	mov r2, r5
	mov r3, r10
	bl sub_02092E30
	ldr r0, [sp, #0x10]
	cmp r0, #0x1
	ble _02091BA8
	ldr r1, [sp, #0x38]
	mov r0, r6
	mov r2, r10
	mov r3, r11
	bl sub_02092F70
	mov r0, r11
	mov r1, r6
	mov r2, r5
	mov r3, r10
	str r7, [sp, #0x0]
	bl sub_02092E30
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
	bl sub_020937E8
	str r7, [sp, #0x0]
	ldr r0, [r9, r4, lsl #0x2]
	mov r1, r6
	mov r2, r5
	mov r3, r10
	bl sub_02092E30
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
	bl sub_02092F70
	str r7, [sp, #0x0]
	mov r0, r8
	mov r1, r6
	mov r2, r5
	mov r3, r10
	bl sub_02092E30
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
	bl sub_020937E8
	mov r0, r8
	mov r1, r6
	mov r2, r5
	mov r3, r10
	str r7, [sp, #0x0]
	bl sub_02092E30
	b _02091DF8
_02091DBC:
	ldr r0, [sp, #0x14]
	str r10, [sp, #0x0]
	ldr r3, [r0, #0x0]
	mov r0, r6
	mov r1, r8
	mov r2, r10
	bl sub_020937E8
	ldr r0, [sp, #0x4]
	str r7, [sp, #0x0]
	ldr r0, [r0, #0x0]
	mov r1, r6
	mov r2, r5
	mov r3, r10
	bl sub_02092E30
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
	bl sub_02092E30
_02091E44:
	ldr r0, [sp, #0xa0]
	ldr r0, [r0, #0x108]
	ands r0, r0, #0x4000
	bne _02091E6C
	ldr r0, [sp, #0x4]
	mov r1, r0
	str r10, [r1, #0x4]
	bl sub_02095040
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
	bl sub_020927E4
_02091EB0:
	ldr r2, [sp, #0xc]
	ldr r1, [sp, #0xa0]
	ldr r0, [sp, #0x8]
	str r2, [r1, #0x0]
	add sp, sp, #0x7c
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start sub_02091ECC
sub_02091ECC: ; 0x02091ECC
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
	bl sub_02095188
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
	bl sub_02094D7C
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
	bl sub_02094D7C
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
	bl sub_02094E24
	add sp, sp, #0x18c
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_02091FC0:
	add r0, sp, #0x18
	bl sub_020927BC
	add r0, sp, #0x18
	mov r1, r4
	mov r2, r9
	bl sub_02092744
	cmp r0, #0x0
	ble _0209220C
	add r0, sp, #0x4c
	bl sub_0209502C
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
	bl sub_02093214
	cmp r0, #0x0
	beq _0209220C
	add r1, sp, #0x4c
	add r3, sp, #0x18
	mov r0, r6
	mov r2, r1
	str r9, [sp, #0x0]
	bl sub_02092698
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
	bl sub_0209502C
	sub r3, r4, #0x1
	mov r2, #0x14
	add r1, sp, #0x4c
	mla r1, r3, r2, r1
	mov r0, r5
	mov r2, r6
	add r3, sp, #0x18
	str r9, [sp, #0x0]
	bl sub_02092698
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
	bl sub_02094D7C
	cmp r0, #0x0
	beq _0209220C
	mov r0, r5
	str r0, [sp, #0x10]
	mov r0, #0x0
	str r0, [sp, #0x14]
_020920F4:
	ldr r0, [sp, #0x4]
	mov r1, r8
	bl sub_02094A8C
	cmp r0, #0x0
	bne _02092140
	cmp r5, #0x0
	bne _02092130
	mov r0, r10
	mov r1, r10
	mov r2, r10
	add r3, sp, #0x18
	str r9, [sp, #0x0]
	bl sub_02092698
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
	bl sub_02094A8C
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
	bl sub_02092698
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
	bl sub_02092698
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
	bl sub_02095164
	ldr r0, [sp, #0xc]
	add r4, r4, #0x1
	cmp r4, r0
	add r5, r5, #0x14
	blt _0209222C
_02092248:
	add r0, sp, #0x18
	bl sub_02092788
	ldr r0, [sp, #0x8]
	add sp, sp, #0x18c
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start sub_02092260
sub_02092260: ; 0x02092260
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
	bl sub_020951BC
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

	arm_func_start sub_020923A0
sub_020923A0: ; 0x020923A0
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x18
	mov r8, r0
	add r0, sp, #0x4
	mov r7, r1
	mov r6, r2
	mov r5, r3
	mvn r4, #0x0
	bl sub_0209502C
	add r0, sp, #0x4
	mov r1, #0x0
	bl sub_02094D7C
	add r0, sp, #0x4
	mov r1, r6
	bl sub_02094AFC
	cmp r0, #0x0
	beq _02092404
	add r2, sp, #0x4
	mov r0, r8
	mov r3, r7
	mov r1, #0x0
	str r5, [sp, #0x0]
	bl sub_02093248
	cmp r0, #0x0
	movne r4, r6
_02092404:
	add r0, sp, #0x4
	bl sub_0209510C
	mov r0, r4
	add sp, sp, #0x18
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start sub_0209241C
sub_0209241C: ; 0x0209241C
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
	bl sub_02094B98
	cmp r0, #0x0
	bge _020924DC
	mov r0, r10
	mov r1, #0x0
	bl sub_02094D7C
	mov r0, r9
	mov r1, r8
	bl sub_02094E24
	add sp, sp, #0xc
	str r11, [r6, #0x0]
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020924DC:
	mov r0, r8
	bl sub_02095188
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
	bl sub_020923A0
	str r0, [r7, #0x2c]
_02092534:
	ldr r2, [sp, #0x8]
	ldr r0, [sp, #0x4]
	mov r1, r8
	sub r2, r2, r4
	bl sub_02094134
	cmp r0, #0x0
	beq _02092684
	ldr r1, [sp, #0x4]
	mov r0, r5
	mov r3, r6
	add r2, r7, #0x14
	bl sub_0209390C
	cmp r0, #0x0
	beq _02092684
	ldr r2, [sp, #0x8]
	mov r0, r10
	mov r1, r5
	add r2, r2, r4
	bl sub_02094134
	cmp r0, #0x0
	beq _02092684
	mov r4, #0x0
	mov r0, r5
	mov r1, r7
	mov r2, r10
	mov r3, r6
	str r4, [r10, #0xc]
	bl sub_0209390C
	cmp r0, #0x0
	beq _02092684
	mov r0, r9
	mov r1, r8
	mov r2, r5
	bl sub_02093B50
	cmp r0, #0x0
	beq _02092684
	mov r5, r4
	mov r0, r9
	mov r1, r7
	str r5, [r9, #0xc]
	bl sub_02094B98
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
	bl sub_02093B50
	cmp r0, #0x0
	beq _02092684
	mov r0, r10
	mov r1, r4
	bl sub_0209400C
	cmp r0, #0x0
	beq _02092684
	mov r0, r9
	mov r1, r7
	bl sub_02094B98
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

	arm_func_start sub_02092698
sub_02092698:
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
	bl sub_0209305C
	cmp r0, #0x0
	bne _0209270C
	b _02092728
_020926F0:
	mov r0, r6
	mov r3, r4
	bl sub_0209390C
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
	bl sub_0209241C
	mov r5, #0x1
_02092728:
	ldr r1, [r4, #0x0]
	mov r0, r5
	sub r1, r1, #0x1
	str r1, [r4, #0x0]
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start sub_02092744
sub_02092744:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl sub_02094E24
	add r0, r5, #0x14
	mov r1, #0x0
	bl sub_02094D7C
	mov r0, r4
	bl sub_02095188
	str r0, [r5, #0x28]
	mov r0, #0x0
	str r0, [r5, #0x2c]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start sub_02092788
sub_02092788: ; 0x02092788
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl sub_0209510C
	add r0, r4, #0x14
	bl sub_0209510C
	ldr r0, [r4, #0x30]
	ands r0, r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, r4
	bl CallCustomDestructor
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start sub_020927BC
sub_020927BC: ; 0x020927BC
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl sub_0209502C
	add r0, r4, #0x14
	bl sub_0209502C
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x30]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start sub_020927E4
sub_020927E4: ; 0x020927E4
	stmdb sp!, {r4,lr}
	mov r4, r0
	add r0, r4, #0xc
	bl sub_0209510C
	add r0, r4, #0x20
	bl sub_0209510C
	add r0, r4, #0x34
	bl sub_0209510C
	ldr r0, [r4, #0x4c]
	ands r0, r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, r4
	bl CallCustomDestructor
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start sub_02092824
sub_02092824: ; 0x02092824
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r1, #0x0
	str r1, [r4, #0x0]
	add r0, r4, #0xc
	str r1, [r4, #0x8]
	bl sub_0209502C
	add r0, r4, #0x20
	bl sub_0209502C
	add r0, r4, #0x34
	bl sub_0209502C
	mov r0, #0x0
	str r0, [r4, #0x4c]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start sub_02092860
sub_02092860: ; 0x02092860
	stmdb sp!, {r4,lr}
	mov r0, #0x50
	bl CallCustomAllocator
	movs r4, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl sub_02092824
	mov r1, #0x1
	mov r0, r4
	str r1, [r4, #0x4c]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start sub_02092894
sub_02092894:
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
	bl sub_02094E24
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	add r0, sp, #0x0
	bl sub_0209502C
	mov r1, #0x1
	mov r0, r6
	str r1, [r7, #0x0]
	bl sub_02095188
	add r1, r0, #0x1f
	mov r0, r1, asr #0x4
	add r0, r1, r0, lsr #0x1b
	mov r2, r0, asr #0x5
	mov r0, r4
	mov r1, #0x0
	str r2, [r7, #0x8]
	bl sub_02094D7C
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r4
	mov r1, #0x20
	bl sub_02094AFC
	cmp r0, #0x0
	beq _02092A38
	ldr r0, [r6, #0x0]
	ldr r4, [r0, #0x0]
	mov r0, r4
	bl sub_02092D9C
	mov r1, r0
	add r0, sp, #0x0
	bl sub_02094D7C
	cmp r0, #0x0
	beq _02092A38
	add r0, sp, #0x0
	mov r2, #0x20
	mov r1, r0
	bl sub_02094250
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
	bl sub_02093EAC
	b _020929C4
_020929B0:
	add r0, sp, #0x0
	mvn r1, #0x0
	bl sub_02094D7C
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
	bl sub_02092260
	str r0, [r7, #0x48]
	add r0, r7, #0xc
	mov r1, #0x0
	bl sub_02094D7C
	ldr r1, [r7, #0x8]
	add r0, r7, #0xc
	mov r1, r1, lsl #0x6
	bl sub_02094AFC
	cmp r0, #0x0
	beq _02092A38
	add r0, r7, #0xc
	mov r1, r0
	mov r3, r5
	add r2, r7, #0x20
	bl sub_02093214
	ldr r1, [r7, #0x8]
	add r0, r7, #0xc
	bl sub_0209508C
_02092A38:
	add r0, sp, #0x0
	bl sub_0209510C
	mov r0, #0x1
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start sub_02092A50
sub_02092A50: ; 0x02092A50
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

	arm_func_start sub_02092C28
sub_02092C28:
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
	bl sub_02094EBC
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
	bl sub_02092A50
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

	arm_func_start sub_02092D9C
sub_02092D9C: ; 0x02092D9C
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

	arm_func_start sub_02092E30
sub_02092E30: ; 0x02092E30
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
	bl sub_020948AC
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
	bl sub_02094354
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

	arm_func_start sub_02092F70
sub_02092F70:
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
	bl sub_0209470C
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
	bl sub_020948AC
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
	bl sub_02094468
	ldr r0, [sp, #0x0]
	mov r1, r9
	mov r2, r11
	bl sub_020945B8
	ldr r2, [sp, #0x0]
	mov r0, r10
	mov r1, r10
	mov r3, r6
	bl sub_02094468
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start sub_0209305C
sub_0209305C:
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
	bl sub_02094EBC
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
	bl sub_02092F70
	b _02093170
_0209310C:
	cmp r5, #0x8
	bne _0209312C
	ldr r0, [r7, #0x0]
	ldr r1, [r8, #0x0]
	add r3, sp, #0x20
	mov r2, #0x8
	bl sub_02092F70
	b _02093170
_0209312C:
	ldr r0, [r4, #0x8]
	cmp r6, r0
	movle r0, r4
	ble _02093148
	mov r0, r4
	mov r1, r6
	bl sub_02094EBC
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
	bl sub_02092F70
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
	bl sub_02094E24
_020931A8:
	mov r0, #0x1
	add sp, sp, #0x64
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start sub_020931B8
sub_020931B8:
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
	bl sub_020916C8
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr
_020931FC:
	ldr r12, [sp, #0x10]
	str r12, [sp, #0x0]
	bl sub_02091ECC
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr

	arm_func_start sub_02093214
sub_02093214:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r12, r2
	str r3, [sp, #0x0]
	mov r1, r0
	mov r2, lr
	mov r3, r12
	mov r0, #0x0
	bl sub_02093248
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start sub_02093248
sub_02093248:
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
	bl sub_02094B98
	cmp r0, #0x0
	bge _020932F8
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _020932D4
	ldr r1, [sp, #0x4]
	bl sub_02094E24
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
	bl sub_02094D7C
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
	bl sub_02095188
	mov r1, r0, lsr #0x1f
	rsb r0, r1, r0, lsl #0x1b
	add r0, r1, r0, ror #0x1b
	rsb r0, r0, #0x20
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x1c]
	ldr r2, [sp, #0x8]
	mov r1, r6
	bl sub_02094250
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
	bl sub_02094250
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
	bl sub_0209502C
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
	bl sub_02094EBC
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
	bl sub_02094EBC
_020934CC:
	cmp r0, #0x0
	beq _020937D4
	ldr r1, [sp, #0x1c]
	add r0, sp, #0x38
	bl sub_02094B98
	cmp r0, #0x0
	blt _02093520
	add r0, sp, #0x38
	ldr r2, [sp, #0x1c]
	mov r1, r0
	bl sub_02093B50
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
	bl sub_02092260
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
	bl sub_0209470C
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
	bl sub_02093A0C
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
	bl sub_02093DD0
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
	bl sub_02095040
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _020937C4
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0x4]
	ldr r1, [sp, #0x18]
	add r2, r2, #0x20
	ldr r4, [r3, #0xc]
	bl sub_02094134
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

	arm_func_start sub_020937E8
sub_020937E8: ; 0x020937E8
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
	bl sub_0209470C
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
	bl sub_020948AC
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
	bl sub_020948AC
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
	bl sub_020948AC
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
	bl sub_020948AC
	str r0, [r4, #0x10]
	add r4, r4, #0x10
	add r9, r9, #0x10
	add r6, r6, #0x10
	b _02093840
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start sub_0209390C
sub_0209390C:
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
	bl sub_02094D7C
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
	bl sub_02094EBC
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
	bl sub_020937E8
	mov r0, r4
	str r11, [r10, #0xc]
	bl sub_02095040
	cmp r10, r4
	beq _020939FC
	mov r0, r10
	mov r1, r4
	bl sub_02094E24
_020939FC:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start sub_02093A0C
sub_02093A0C: ; 0x02093A0C
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
	bl sub_02093CB4
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
	bl sub_02094EBC
_02093ABC:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r6
	mov r1, r5
	bl sub_02094B98
	cmp r0, #0x0
	bge _02093B14
	mov r0, r7
	mov r1, r5
	mov r2, r6
	bl sub_02093B50
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
	bl sub_02093B50
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

	arm_func_start sub_02093B50
sub_02093B50:
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
	bl sub_02094EBC
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
	bl sub_02095040
	mov r0, #0x1
	ldmia sp!, {r4-r10,lr}
	bx lr

	arm_func_start sub_02093CB4
sub_02093CB4:
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
	bl sub_02094EBC
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
	bl sub_02094468
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

	arm_func_start sub_02093DD0
sub_02093DD0: ; 0x02093DD0
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
	bl sub_02094B98
	cmp r0, #0x0
	bge _02093E40
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl sub_02093B50
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
	bl sub_02093B50
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
	bl sub_02093CB4
	cmp r0, #0x0
	moveq r0, #0x0
	movne r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start sub_02093EAC
sub_02093EAC: ; 0x02093EAC
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
	bl sub_0209400C
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
	bl sub_02094EBC
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

	arm_func_start sub_0209400C
sub_0209400C:
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
	bl sub_02093EAC
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
	bl sub_02094EBC
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

	arm_func_start sub_02094134
sub_02094134:
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
	bl sub_02094D7C
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
	bl sub_02094EBC
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
	bl sub_02095040
	mov r0, #0x1
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start sub_02094250
sub_02094250:
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
	bl sub_02094EBC
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
	bl sub_02095040
	mov r0, #0x1
	ldmia sp!, {r4-r10,lr}
	bx lr

	arm_func_start sub_02094354
sub_02094354: ; 0x02094354
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

	arm_func_start sub_02094468
sub_02094468:
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

	arm_func_start sub_020945B8
sub_020945B8: ; 0x020945B8
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

	arm_func_start sub_0209470C
sub_0209470C: ; 0x0209470C
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

	arm_func_start sub_020948AC
sub_020948AC: ; 0x020948AC
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

	arm_func_start sub_02094A8C
sub_02094A8C:
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

	arm_func_start sub_02094AFC
sub_02094AFC:
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
	bl sub_02094EBC
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

	arm_func_start sub_02094B98
sub_02094B98:
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

	arm_func_start sub_02094BEC
sub_02094BEC: ; 0x02094BEC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl sub_02095188
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

	arm_func_start sub_02094C68
sub_02094C68:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	movs r5, r2
	mov r7, r0
	mov r6, r1
	bne _02094C88
	bl sub_02094FE0
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
	bl sub_02094EBC
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
	bl sub_02095040
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start sub_02094D7C
sub_02094D7C:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldr r2, [r4, #0x8]
	mov r5, r1
	cmp r2, #0x1
	bge _02094DA0
	mov r1, #0x2
	bl sub_02094EBC
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

	arm_func_start sub_02094DEC
sub_02094DEC: ; 0x02094DEC
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

	arm_func_start sub_02094E24
sub_02094E24:
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
	bl sub_02094EBC
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

	arm_func_start sub_02094EBC
sub_02094EBC:
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

	arm_func_start sub_02094F3C
sub_02094F3C: ; 0x02094F3C
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	add r4, r6, #0x4
	mov r5, #0x0
_02094F4C:
	mov r0, r4
	bl sub_02095164
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

	arm_func_start sub_02094F84
sub_02094F84: ; 0x02094F84
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

	arm_func_start sub_02094FAC
sub_02094FAC: ; 0x02094FAC
	stmdb sp!, {r4,lr}
	mov r0, #0x110
	bl CallCustomAllocator
	movs r4, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl sub_02094F84
	mov r1, #0x1
	mov r0, r4
	str r1, [r4, #0x108]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start sub_02094FE0
sub_02094FE0: ; 0x02094FE0
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

	arm_func_start sub_0209502C
sub_0209502C:
	ldr ip, _0209503C ; =MI_CpuFill8
	mov r1, #0x0
	mov r2, #0x14
	bx r12
	.balign 4
_0209503C: .word MI_CpuFill8

	arm_func_start sub_02095040
sub_02095040:
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

	arm_func_start sub_0209508C
sub_0209508C:
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
	bl sub_02094EBC
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

	arm_func_start sub_0209510C
sub_0209510C:
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

	arm_func_start sub_02095164
sub_02095164: ; 0x02095164
	stmdb sp!, {r4,lr}
	movs r4, r0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl sub_02094DEC
	mov r0, r4
	bl sub_0209510C
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start sub_02095188
sub_02095188: ; 0x02095188
	stmdb sp!, {r4,lr}
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, [r0, #0x0]
	sub r4, r1, #0x1
	ldr r0, [r0, r4, lsl #0x2]
	bl sub_020951BC
	add r0, r0, r4, lsl #0x5
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start sub_020951BC
sub_020951BC: ; 0x020951BC
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

	arm_func_start sub_0209521C
sub_0209521C: ; 0x0209521C
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

	arm_func_start sub_020952AC
sub_020952AC: ; 0x020952AC
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
