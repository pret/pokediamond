	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start ov04_021DD36C
ov04_021DD36C: ; 0x021DD36C
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	ands r4, r1, #3
	addne sp, sp, #8
	mvnne r0, #0
	ldmneia sp!, {r4, r5, r6, r7, r8, pc}
	mov r6, #0
	mov r5, r6
	cmp r1, #0
	bls _021DD3AC
_021DD394:
	ldrsb r4, [r0, r5]
	add r5, r5, #1
	cmp r4, #0x2a
	addne r6, r6, #6
	cmp r5, r1
	blo _021DD394
_021DD3AC:
	cmp r2, #0
	moveq r0, r6, asr #2
	addeq r0, r6, r0, lsr #29
	addeq sp, sp, #8
	moveq r0, r0, asr #3
	ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
	mov r4, r6, asr #2
	add r4, r6, r4, lsr #29
	mov r4, r4, asr #3
	cmp r3, r4
	addlo sp, sp, #8
	mvnlo r0, #0
	ldmloia sp!, {r4, r5, r6, r7, r8, pc}
	cmp r1, #0
	moveq r0, #0
	streqb r0, [r2]
	addeq sp, sp, #8
	ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
	mov r6, r2
	add ip, sp, #0
	mov lr, #0
	mov r1, #0x3f
	mov r3, #0x3e
_021DD408:
	mov r8, lr
	mov r5, ip
_021DD410:
	ldrsb r7, [r0, r8]
	cmp r7, #0x41
	blt _021DD42C
	cmp r7, #0x5a
	suble r7, r7, #0x41
	strleb r7, [r5]
	ble _021DD474
_021DD42C:
	cmp r7, #0x61
	blt _021DD444
	cmp r7, #0x7a
	suble r7, r7, #0x47
	strleb r7, [r5]
	ble _021DD474
_021DD444:
	cmp r7, #0x30
	blt _021DD45C
	cmp r7, #0x39
	addle r7, r7, #4
	strleb r7, [r5]
	ble _021DD474
_021DD45C:
	cmp r7, #0x2e
	streqb r3, [r5]
	beq _021DD474
	cmp r7, #0x2d
	streqb r1, [r5]
	strneb lr, [r5]
_021DD474:
	add r8, r8, #1
	cmp r8, #4
	add r5, r5, #1
	blt _021DD410
	ldrsb r8, [sp]
	ldrsb r7, [sp, #1]
	add r5, r6, #1
	mov r8, r8, lsl #2
	orr r7, r8, r7, asr #4
	sub r5, r5, r2
	strb r7, [r6]
	cmp r5, r4
	add r0, r0, #4
	bge _021DD4F0
	ldrsb r8, [sp, #1]
	ldrsb r7, [sp, #2]
	add r5, r6, #2
	mov r8, r8, lsl #4
	orr r7, r8, r7, asr #2
	sub r5, r5, r2
	strb r7, [r6, #1]
	cmp r5, r4
	bge _021DD4F0
	ldrsb r7, [sp, #2]
	ldrsb r5, [sp, #3]
	orr r5, r5, r7, lsl #6
	strb r5, [r6, #2]
	add r6, r6, #3
	sub r5, r6, r2
	cmp r5, r4
	blt _021DD408
_021DD4F0:
	mov r0, r5
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	arm_func_end ov04_021DD36C

	arm_func_start ov04_021DD4FC
ov04_021DD4FC: ; 0x021DD4FC
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0xc
	ldr r4, _021DD69C ; =0xAAAAAAAB
	str r2, [sp]
	umull r4, r5, r1, r4
	ldr r6, _021DD6A0 ; =0x00000003
	mov r5, r5, lsr #1
	umull r4, r5, r6, r5
	mov sl, r0
	subs r5, r1, r4
	movne r4, #4
	ldr r2, _021DD69C ; =0xAAAAAAAB
	ldr r0, [sp]
	moveq r4, #0
	cmp r0, #0
	umull r0, r2, r1, r2
	mov r2, r2, lsr #1
	addeq sp, sp, #0xc
	add r0, r4, r2, lsl #2
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	cmp r3, r0
	addlo sp, sp, #0xc
	mvnlo r0, #0
	ldmloia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	add r7, sl, r1
	ldr r6, [sp]
	cmp sl, r7
	beq _021DD68C
	mov r0, #1
	mov r5, #0
	str r0, [sp, #4]
	mov fp, #3
	mov r4, #0x2a
_021DD580:
	sub sb, r7, sl
	ldr r1, _021DD6A4 ; =0x2AAAAAAB
	mov r0, sb, lsl #3
	smull r2, r3, r1, r0
	ldr r1, _021DD6A8 ; =0x00000006
	add r3, r3, r0, lsr #31
	smull r2, r3, r1, r3
	subs r3, r0, r2
	ldr r1, _021DD6A4 ; =0x2AAAAAAB
	ldrne r8, [sp, #4]
	smull r2, r3, r1, r0
	moveq r8, r5
	add r3, r3, r0, lsr #31
	cmp sb, #3
	movge sb, fp
	add r0, sp, #8
	mov r1, r5
	mov r2, fp
	add r8, r3, r8
	bl MI_CpuFill8
	mov r0, sl
	add r1, sp, #8
	mov r2, sb
	bl MI_CpuCopy8
	ldr r0, _021DD6AC ; =ov04_0220C638
	cmp r8, #2
	ldr r1, [r0]
	ldrb r0, [sp, #8]
	mov r0, r0, asr #2
	ldrsb r0, [r1, r0]
	strb r0, [r6]
	strltb r4, [r6, #1]
	blt _021DD628
	ldrb r2, [sp, #8]
	ldr r0, _021DD6AC ; =ov04_0220C638
	ldrb r1, [sp, #9]
	mov r2, r2, lsl #4
	and r2, r2, #0x3f
	ldr r0, [r0]
	orr r1, r2, r1, asr #4
	ldrsb r0, [r0, r1]
	strb r0, [r6, #1]
_021DD628:
	cmp r8, #3
	strltb r4, [r6, #2]
	blt _021DD658
	ldrb r2, [sp, #9]
	ldr r0, _021DD6AC ; =ov04_0220C638
	ldrb r1, [sp, #0xa]
	mov r2, r2, lsl #2
	and r2, r2, #0x3f
	ldr r0, [r0]
	orr r1, r2, r1, asr #6
	ldrsb r0, [r0, r1]
	strb r0, [r6, #2]
_021DD658:
	cmp r8, #4
	strltb r4, [r6, #3]
	blt _021DD67C
	ldr r0, _021DD6AC ; =ov04_0220C638
	ldrb r1, [sp, #0xa]
	ldr r2, [r0]
	and r0, r1, #0x3f
	ldrsb r0, [r2, r0]
	strb r0, [r6, #3]
_021DD67C:
	add sl, sl, sb
	cmp sl, r7
	add r6, r6, #4
	bne _021DD580
_021DD68C:
	ldr r0, [sp]
	sub r0, r6, r0
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021DD69C: .word 0xAAAAAAAB
_021DD6A0: .word 0x00000003
_021DD6A4: .word 0x2AAAAAAB
_021DD6A8: .word 0x00000006
_021DD6AC: .word ov04_0220C638
	arm_func_end ov04_021DD4FC

	.section .data

	.global ov04_0220C638
ov04_0220C638: ; 0x0220C638
	.word ov04_0220C63C

	.global ov04_0220C63C
ov04_0220C63C: ; 0x0220C63C
	.asciz "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.-"

	.balign 4, 0
