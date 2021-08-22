	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MOD04_021DCA84
MOD04_021DCA84: ; 0x021DCA84
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0x40
	mov r6, r0
	bl strlen
	mov r4, r0
	ldr r0, _021DCCB4 ; =UNK04_0220C580
	bl strlen
	cmp r4, r0
	bne _021DCCA8
	ldrsb r0, [r6, #7]
	cmp r0, #0x20
	bne _021DCCA8
	ldrsb r0, [r6, #0xb]
	cmp r0, #0x20
	bne _021DCCA8
	ldrsb r0, [r6, #0x10]
	cmp r0, #0x20
	bne _021DCCA8
	ldrsb r0, [r6, #0x13]
	cmp r0, #0x3a
	bne _021DCCA8
	ldrsb r0, [r6, #0x16]
	cmp r0, #0x3a
	bne _021DCCA8
	ldrsb r0, [r6, #0x19]
	cmp r0, #0x20
	bne _021DCCA8
	add r0, sp, #0
	bl RTC_GetDate
	cmp r0, #0
	bne _021DCCA8
	add r0, sp, #0x10
	bl RTC_GetTime
	cmp r0, #0
	bne _021DCCA8
	add r0, sp, #0
	add r1, sp, #0x10
	bl RTC_ConvertDateTimeToSecond
	mov r4, r0
	mov r5, r1
	mvn r0, #0
	cmp r5, r0
	cmpeq r4, r0
	beq _021DCCA8
	add r0, sp, #0x1c
	mov r1, r6
	bl strcpy
	mov r2, #0
	ldr r1, _021DCCB8 ; =errno
	add r0, sp, #0x28
	strb r2, [sp, #0x23]
	strb r2, [sp, #0x27]
	strb r2, [sp, #0x2c]
	strb r2, [sp, #0x2f]
	strb r2, [sp, #0x32]
	strb r2, [sp, #0x35]
	str r2, [r1]
	bl atol
	ldr r1, _021DCCB8 ; =errno
	str r0, [sp]
	ldr r1, [r1]
	cmp r1, #0x22
	beq _021DCCA8
	sub r1, r0, #0x7d0
	mov r0, #0xd
	str r1, [sp]
	str r0, [sp, #4]
	mov r8, #0
	ldr r7, _021DCCBC ; =UNK04_0220C550
	add r6, sp, #0x24
_021DCB9C:
	ldr r0, [r7, r8, lsl #2]
	mov r1, r6
	bl strcmp
	cmp r0, #0
	addeq r0, r8, #1
	streq r0, [sp, #4]
	beq _021DCBC4
	add r8, r8, #1
	cmp r8, #0xc
	blt _021DCB9C
_021DCBC4:
	ldr r0, [sp, #4]
	cmp r0, #0xc
	bhi _021DCCA8
	ldr r1, _021DCCB8 ; =errno
	mov r2, #0
	add r0, sp, #0x21
	str r2, [r1]
	bl atol
	ldr r1, _021DCCB8 ; =errno
	str r0, [sp, #8]
	ldr r0, [r1]
	cmp r0, #0x22
	beq _021DCCA8
	mov r2, #0
	add r0, sp, #0x2d
	str r2, [r1]
	bl atol
	ldr r1, _021DCCB8 ; =errno
	str r0, [sp, #0x10]
	ldr r0, [r1]
	cmp r0, #0x22
	beq _021DCCA8
	mov r2, #0
	add r0, sp, #0x30
	str r2, [r1]
	bl atol
	ldr r1, _021DCCB8 ; =errno
	str r0, [sp, #0x14]
	ldr r0, [r1]
	cmp r0, #0x22
	beq _021DCCA8
	mov r2, #0
	add r0, sp, #0x33
	str r2, [r1]
	bl atol
	ldr r1, _021DCCB8 ; =errno
	str r0, [sp, #0x18]
	ldr r0, [r1]
	cmp r0, #0x22
	beq _021DCCA8
	add r0, sp, #0
	add r1, sp, #0x10
	bl RTC_ConvertDateTimeToSecond
	mvn r2, #0
	cmp r1, r2
	cmpeq r0, r2
	beq _021DCCA8
	subs r4, r4, r0
	ldr r2, _021DCCC0 ; =UNK04_022104FC
	sbc r3, r5, r1
	ldr r1, _021DCCC4 ; =UNK04_022104F8
	mov r0, #1
	str r3, [r2, #4]
	str r0, [r1]
	add sp, sp, #0x40
	str r4, [r2]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_021DCCA8:
	mov r0, #0
	add sp, sp, #0x40
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_021DCCB4: .word UNK04_0220C580
_021DCCB8: .word errno
_021DCCBC: .word UNK04_0220C550
_021DCCC0: .word UNK04_022104FC
_021DCCC4: .word UNK04_022104F8
	arm_func_end MOD04_021DCA84

	.section .data

	.global UNK04_0220C520
UNK04_0220C520: ; 0x0220C520
	.asciz "Dec"

	.balign 4, 0
	.global UNK04_0220C524
UNK04_0220C524: ; 0x0220C524
	.asciz "Jul"

	.balign 4, 0
	.global UNK04_0220C528
UNK04_0220C528: ; 0x0220C528
	.asciz "Oct"

	.balign 4, 0
	.global UNK04_0220C52C
UNK04_0220C52C: ; 0x0220C52C
	.asciz "Sep"

	.balign 4, 0
	.global UNK04_0220C530
UNK04_0220C530: ; 0x0220C530
	.asciz "Aug"

	.balign 4, 0
	.global UNK04_0220C534
UNK04_0220C534: ; 0x0220C534
	.asciz "Nov"

	.balign 4, 0
	.global UNK04_0220C538
UNK04_0220C538: ; 0x0220C538
	.asciz "Jun"

	.balign 4, 0
	.global UNK04_0220C53C
UNK04_0220C53C: ; 0x0220C53C
	.asciz "May"

	.balign 4, 0
	.global UNK04_0220C540
UNK04_0220C540: ; 0x0220C540
	.asciz "Apr"

	.balign 4, 0
	.global UNK04_0220C544
UNK04_0220C544: ; 0x0220C544
	.asciz "Mar"

	.balign 4, 0
	.global UNK04_0220C548
UNK04_0220C548: ; 0x0220C548
	.asciz "Feb"

	.balign 4, 0
	.global UNK04_0220C54C
UNK04_0220C54C: ; 0x0220C54C
	.asciz "Jan"

	.balign 4, 0
	.global UNK04_0220C550
UNK04_0220C550: ; 0x0220C550
	.word UNK04_0220C54C, UNK04_0220C548, UNK04_0220C544, UNK04_0220C540
	.word UNK04_0220C53C, UNK04_0220C538, UNK04_0220C524, UNK04_0220C530
	.word UNK04_0220C52C, UNK04_0220C528, UNK04_0220C534, UNK04_0220C520

	.global UNK04_0220C580
UNK04_0220C580: ; 0x0220C580
	.asciz "Fri, 03 Mar 2006 01:28:13 GMT"

	.balign 4, 0
	.section .bss

	.global UNK04_022104F8
UNK04_022104F8: ; 0x022104F8
	.space 0x4

	.global UNK04_022104FC
UNK04_022104FC: ; 0x022104FC
	.space 0x8
