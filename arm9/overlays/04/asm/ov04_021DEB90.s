	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start ov04_021DEB90
ov04_021DEB90: ; 0x021DEB90
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl ov04_021FD43C
	bl ov04_021EFB28
	ldr r2, _021DEBCC ; =ov04_02210540
	ldr r1, _021DEBD0 ; =0xFFFE8515
	str r0, [r2]
	mov r0, #9
	bl ov04_021DD6B0
	ldr r0, _021DEBD4 ; =ov04_0221053C
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0]
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DEBCC: .word ov04_02210540
_021DEBD0: .word 0xFFFE8515
_021DEBD4: .word ov04_0221053C
	arm_func_end ov04_021DEB90

	arm_func_start ov04_021DEBD8
ov04_021DEBD8: ; 0x021DEBD8
	ldr ip, _021DEBE0 ; =ov04_021EAC1C
	bx ip
	.align 2, 0
_021DEBE0: .word ov04_021EAC1C
	arm_func_end ov04_021DEBD8

	arm_func_start ov04_021DEBE4
ov04_021DEBE4: ; 0x021DEBE4
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0xc
	mov r7, #0
	mov fp, r0
	mov sb, r1
	mov sl, r7
	bl ov04_021E852C
	cmp r0, #0
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	cmp sb, #4
	addls pc, pc, sb, lsl #2
	b _021DEC48
_021DEC18: ; jump table
	b _021DEC2C ; case 0
	b _021DEC2C ; case 1
	b _021DEC34 ; case 2
	b _021DEC34 ; case 3
	b _021DEC40 ; case 4
_021DEC2C:
	mov r4, r7
	b _021DEC48
_021DEC34:
	mov r4, #6
	ldr r6, _021DEF4C ; =0xFFFFE250
	b _021DEC48
_021DEC40:
	ldr r6, _021DEF50 ; =0xFFFFE24F
	mov r4, #9
_021DEC48:
	cmp r4, #0
	bne _021DED00
	mov r0, fp
	bl ov04_021FD3C4
	movs r7, r0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r0, _021DEF54 ; =ov04_0221053C
	ldrb r8, [r7, #1]
	ldr r1, [r0]
	mov r5, #1
	mov r0, r5,lsl  r8
	ldr r1, [r1, #0x644]
	ands r0, r1, r0
	mov r0, r8
	moveq r5, #0
	bl ov04_021EA9D8
	ldr r0, _021DEF54 ; =ov04_0221053C
	ldr r1, [r0]
	ldrb r0, [r1, #0x369]
	cmp r0, #2
	bne _021DECA8
	cmp sb, #0
	beq _021DECBC
_021DECA8:
	ldrb r0, [r1, #0x369]
	cmp r0, #3
	bne _021DECC0
	cmp r8, #0
	bne _021DECC0
_021DECBC:
	mov sl, #1
_021DECC0:
	mov r0, r8
	bl ov04_021DF56C
	ldr r1, _021DEF54 ; =ov04_0221053C
	ldrb r7, [r7]
	ldr r2, _021DEF58 ; =ov04_02210544
	mov fp, #0
	ldr r3, [r1]
	str fp, [r2, r7, lsl #2]
	ldrb r2, [r3, #0x361]
	mov r7, r0
	sub r0, r2, #1
	strb r0, [r3, #0x361]
	ldr r1, [r1]
	ldrb r0, [r1, #0x368]
	sub r0, r0, #1
	strb r0, [r1, #0x368]
_021DED00:
	ldr r0, _021DEF54 ; =ov04_0221053C
	ldr r1, [r0]
	ldrb r0, [r1, #0x2d]
	cmp r0, #0
	bne _021DED58
	ldr r0, [r1, #0x24]
	cmp r0, #6
	bne _021DED58
	cmp r5, #0
	bne _021DED58
	ldrb r0, [r1, #0x369]
	cmp r0, #2
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	cmp r4, #0
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	bl ov04_021E85D4
	mov r0, r7
	bl ov04_021E8A50
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021DED58:
	mov r0, r4
	mov r1, r6
	mov r2, r7
	bl ov04_021E8A74
	cmp r0, #0
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	cmp r4, #0
	beq _021DED90
	mov r0, r4
	mov r1, r6
	bl ov04_021DD6B0
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021DED90:
	ldr r0, _021DEF54 ; =ov04_0221053C
	ldr r1, [r0]
	ldrb r0, [r1, #0x2d]
	cmp r0, #0
	bne _021DEE04
	ldrb r0, [r1, #0x369]
	cmp r0, #2
	beq _021DEDBC
	ldrb r0, [r1, #0x369]
	cmp r0, #3
	bne _021DEE04
_021DEDBC:
	ldr r2, _021DEF54 ; =ov04_0221053C
	ldr r1, [r2]
	ldrb r0, [r1, #0x361]
	add r6, r0, #2
	add r3, r1, r6, lsl #2
	ldr r3, [r3, #0x448]
	cmp r3, #0
	beq _021DEE04
	add r3, r1, r6
	ldrb r3, [r3, #0x624]
	add r0, r0, #1
	add r0, r1, r0
	strb r3, [r0, #0x624]
	ldr r0, [r2]
	ldrb r1, [r0, #0x361]
	add r0, r1, #1
	add r1, r1, #3
	bl ov04_021E8830
_021DEE04:
	ldr r0, _021DEF54 ; =ov04_0221053C
	ldr r1, [r0]
	ldrb r0, [r1, #0x369]
	cmp r0, #2
	bne _021DEE4C
	ldrb r0, [r1, #0x2d]
	cmp r0, #0
	bne _021DEE2C
	bl ov04_021E85D4
	b _021DEE68
_021DEE2C:
	ldrb r0, [r1, #0x361]
	cmp r0, #0
	bne _021DEE68
	ldr r1, _021DEF5C ; =ov04_0220D334
	mov r0, #1
	mov r2, #0
	bl ov04_021E1E30
	b _021DEE68
_021DEE4C:
	ldrb r0, [r1, #0x361]
	cmp r0, #0
	bne _021DEE68
	ldr r1, _021DEF5C ; =ov04_0220D334
	mov r0, #1
	mov r2, #0
	bl ov04_021E1E30
_021DEE68:
	ldr r0, _021DEF54 ; =ov04_0221053C
	ldr r1, [r0]
	ldrb r0, [r1, #0x369]
	cmp r0, #0
	beq _021DEE88
	ldrb r0, [r1, #0x369]
	cmp r0, #1
	bne _021DEEA4
_021DEE88:
	ldr r0, _021DEF54 ; =ov04_0221053C
	ldr r2, [r0]
	ldrb r1, [r2, #0x368]
	strb r1, [r2, #0x36a]
	ldr r0, [r0]
	ldr r0, [r0, #0x364]
	bl ov04_02202308
_021DEEA4:
	ldr r0, _021DEF54 ; =ov04_0221053C
	ldr r6, [r0]
	ldr r0, [r6, #0x90]
	cmp r0, #0
	beq _021DEF00
	cmp r5, #0
	beq _021DEF00
	cmp sb, #0
	moveq r5, #1
	mov r0, r7
	movne r5, #0
	bl ov04_021E1F18
	str r0, [sp]
	ldr r1, [r6, #0x94]
	ldr r0, _021DEF54 ; =ov04_0221053C
	str r1, [sp, #4]
	ldr r1, [r0]
	mov r0, r4
	ldr r4, [r1, #0x90]
	mov r1, r5
	mov r2, sl
	mov r3, r8
	blx r4
_021DEF00:
	ldr r0, _021DEF54 ; =ov04_0221053C
	ldr r1, [r0]
	ldrb r0, [r1, #0x2d]
	cmp r0, #0
	bne _021DEF24
	ldrb r0, [r1, #0x369]
	cmp r0, #2
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021DEF24:
	ldrb r0, [r1, #0x361]
	cmp r0, #0
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	bl ov04_02200D6C
	bl ov04_021E8DC0
	mov r0, #3
	bl ov04_021DF5CC
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021DEF4C: .word 0xFFFFE250
_021DEF50: .word 0xFFFFE24F
_021DEF54: .word ov04_0221053C
_021DEF58: .word ov04_02210544
_021DEF5C: .word ov04_0220D334
	arm_func_end ov04_021DEBE4

	arm_func_start ov04_021DEF60
ov04_021DEF60: ; 0x021DEF60
	ldr ip, _021DEF68 ; =ov04_021EAC5C
	bx ip
	.align 2, 0
_021DEF68: .word ov04_021EAC5C
	arm_func_end ov04_021DEF60

	arm_func_start ov04_021DEF6C
ov04_021DEF6C: ; 0x021DEF6C
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	add r4, sp, #0
	mov r3, #0
	strb r3, [r4]
	strb r3, [r4, #1]
	strb r3, [r4, #2]
	strb r3, [r4, #3]
	strb r3, [r4, #4]
	strb r3, [r4, #5]
	strb r3, [r4, #6]
	strb r3, [r4, #7]
	strb r3, [r4, #8]
	strb r3, [r4, #9]
	strb r3, [r4, #0xa]
	mov r5, r1
	strb r3, [r4, #0xb]
	ldr r4, [r5, #8]
	mov r6, r0
	bl ov04_021E2068
	cmp r0, #0
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	ldr r0, _021DF0C8 ; =ov04_0220D338
	bl strlen
	mov r2, r0
	ldr r1, _021DF0C8 ; =ov04_0220D338
	mov r0, r4
	bl memcmp
	cmp r0, #0
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	ldr r0, _021DF0C8 ; =ov04_0220D338
	bl strlen
	add r4, r4, r0
	mov r0, r4
	mov r1, #0x76
	bl strchr
	sub r7, r0, r4
	add r0, sp, #0
	mov r1, r4
	mov r2, r7
	bl strncpy
	cmp r7, #0xa
	addhi sp, sp, #0xc
	ldmhiia sp!, {r4, r5, r6, r7, pc}
	add r0, sp, #0
	mov r1, #0
	mov r2, #0xa
	bl strtoul
	cmp r0, #3
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	ldr r0, _021DF0CC ; =ov04_0220D340
	add r1, r7, #1
	add r4, r4, r1
	bl strlen
	mov r2, r0
	ldr r1, _021DF0CC ; =ov04_0220D340
	mov r0, r4
	bl memcmp
	cmp r0, #0
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	ldr r0, _021DF0D0 ; =ov04_0221053C
	ldr r1, [r0]
	ldr r0, [r1, #0x24]
	cmp r0, #5
	beq _021DF0A8
	cmp r0, #6
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	ldrb r0, [r1, #0x369]
	cmp r0, #2
	beq _021DF0A8
	ldrb r0, [r1, #0x369]
	cmp r0, #3
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
_021DF0A8:
	ldr r0, _021DF0CC ; =ov04_0220D340
	bl strlen
	add r2, r4, r0
	ldr r1, [r5]
	mov r0, r6
	bl ov04_021E8EF4
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021DF0C8: .word ov04_0220D338
_021DF0CC: .word ov04_0220D340
_021DF0D0: .word ov04_0221053C
	arm_func_end ov04_021DEF6C

	arm_func_start ov04_021DF0D4
ov04_021DF0D4: ; 0x021DF0D4
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, [r1, #4]
	ldr r0, _021DF120 ; =0x00000603
	cmp r1, r0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _021DF124 ; =0x00000901
	cmp r1, r0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _021DF128 ; =0x00000B01
	cmp r1, r0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #3
	bl ov04_021DF414
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DF120: .word 0x00000603
_021DF124: .word 0x00000901
_021DF128: .word 0x00000B01
	arm_func_end ov04_021DF0D4

	arm_func_start ov04_021DF12C
ov04_021DF12C: ; 0x021DF12C
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	movs r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bne _021DF174
	cmp r6, #0
	beq _021DF174
	ldr r0, _021DF2AC ; =ov04_0221053C
	ldr r0, [r0]
	ldr r0, [r0, #0x4f4]
	cmp r0, #0
	bne _021DF1D8
	bl ov04_021E8DC0
	mov r0, #3
	bl ov04_021DF5CC
	b _021DF1D8
_021DF174:
	cmp r7, #0
	bne _021DF1D8
	mov r0, #6
	bl ov04_021DF5CC
	ldr r1, _021DF2AC ; =ov04_0221053C
	mov r0, #0
	ldr r3, [r1]
	ldrb r1, [r3, #0x361]
	cmp r1, #0
	blt _021DF1D8
	ldr r2, [r3, #0x64]
_021DF1A0:
	add r1, r3, r0, lsl #2
	ldr r1, [r1, #0x448]
	cmp r2, r1
	bne _021DF1C8
	ldr r1, _021DF2AC ; =ov04_0221053C
	ldr r1, [r1]
	add r0, r1, r0
	ldrb r0, [r0, #0x624]
	strb r0, [r1, #0x2c]
	b _021DF1D8
_021DF1C8:
	ldrb r1, [r3, #0x361]
	add r0, r0, #1
	cmp r0, r1
	ble _021DF1A0
_021DF1D8:
	ldr r1, _021DF2AC ; =ov04_0221053C
	ldr r0, _021DF2B0 ; =0x00000624
	ldr r2, [r1]
	ldrb r1, [r2, #0x361]
	add r0, r2, r0
	add r1, r1, #1
	bl ov04_021DF530
	ldr r1, _021DF2AC ; =ov04_0221053C
	ldr r1, [r1]
	str r0, [r1, #0x644]
	bl ov04_021E8780
	ldr r0, _021DF2AC ; =ov04_0221053C
	ldr r1, [r0]
	ldrb r0, [r1, #0x369]
	cmp r0, #2
	beq _021DF224
	ldrb r0, [r1, #0x369]
	cmp r0, #3
	bne _021DF258
_021DF224:
	ldr r0, _021DF2AC ; =ov04_0221053C
	ldr r1, [sp, #0x20]
	ldr r3, [r0]
	mov r0, r7
	str r1, [sp]
	ldr r2, [r3, #0x8c]
	mov r1, r6
	str r2, [sp, #4]
	ldr r6, [r3, #0x88]
	mov r2, r5
	mov r3, r4
	blx r6
	b _021DF26C
_021DF258:
	ldr r2, [r1, #0x84]
	ldr r3, [r1, #0x80]
	mov r0, r7
	mov r1, r6
	blx r3
_021DF26C:
	cmp r7, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r0, _021DF2AC ; =ov04_0221053C
	ldr r0, [r0]
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r0, [r0, #0x24]
	cmp r0, #5
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	mov r0, #3
	bl ov04_021DF5CC
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021DF2AC: .word ov04_0221053C
_021DF2B0: .word 0x00000624
	arm_func_end ov04_021DF12C

	arm_func_start ov04_021DF2B4
ov04_021DF2B4: ; 0x021DF2B4
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r2, _021DF300 ; =ov04_0221053C
	mov r5, r0
	ldr r0, [r2]
	mov r4, r1
	ldr r0, [r0, #0x28]
	cmp r0, #4
	beq _021DF2DC
	bl ov04_021DF5CC
_021DF2DC:
	ldr r1, _021DF300 ; =ov04_0221053C
	mov r0, r5
	ldr r3, [r1]
	mov r1, r4
	ldr r2, [r3, #0x7c]
	ldr r3, [r3, #0x78]
	blx r3
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021DF300: .word ov04_0221053C
	arm_func_end ov04_021DF2B4

	arm_func_start ov04_021DF304
ov04_021DF304: ; 0x021DF304
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	movs r5, r0
	mov r4, r1
	bne _021DF334
	ldr r1, _021DF36C ; =ov04_0221053C
	mov r0, #3
	ldr r1, [r1]
	str r4, [r1, #0x64]
	bl ov04_021DF5CC
	bl ov04_021E1ED4
	b _021DF33C
_021DF334:
	mov r0, #0
	bl ov04_021DF5CC
_021DF33C:
	ldr r0, _021DF36C ; =ov04_0221053C
	ldr r0, [r0]
	ldr r3, [r0, #0x70]
	cmp r3, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	ldr r2, [r0, #0x74]
	mov r0, r5
	mov r1, r4
	blx r3
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021DF36C: .word ov04_0221053C
	arm_func_end ov04_021DF304

	arm_func_start ov04_021DF370
ov04_021DF370: ; 0x021DF370
	stmdb sp!, {r4, lr}
	movs r4, r0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	cmp r4, #7
	addls pc, pc, r4, lsl #2
	b _021DF3F4
_021DF38C: ; jump table
	b _021DF3F4 ; case 0
	b _021DF3AC ; case 1
	b _021DF3B8 ; case 2
	b _021DF3C8 ; case 3
	b _021DF3D4 ; case 4
	b _021DF3B8 ; case 5
	b _021DF3E0 ; case 6
	b _021DF3EC ; case 7
_021DF3AC:
	mov r0, #9
	mvn r2, #0
	b _021DF3F4
_021DF3B8:
	mov r0, #0
	mov r2, r0
	mov r4, r0
	b _021DF3F4
_021DF3C8:
	mov r0, #6
	mvn r2, #9
	b _021DF3F4
_021DF3D4:
	mov r0, #6
	mvn r2, #0x1d
	b _021DF3F4
_021DF3E0:
	mov r0, #6
	mvn r2, #0x45
	b _021DF3F4
_021DF3EC:
	mov r0, #6
	mvn r2, #0x4f
_021DF3F4:
	cmp r0, #0
	beq _021DF408
	ldr r1, _021DF410 ; =0xFFFEFA48
	add r1, r2, r1
	bl ov04_021E0EAC
_021DF408:
	mov r0, r4
	ldmia sp!, {r4, pc}
	.align 2, 0
_021DF410: .word 0xFFFEFA48
	arm_func_end ov04_021DF370

	arm_func_start ov04_021DF414
ov04_021DF414: ; 0x021DF414
	stmdb sp!, {r4, r5, r6, lr}
	movs r6, r0
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	cmp r6, #4
	addls pc, pc, r6, lsl #2
	b _021DF470
_021DF430: ; jump table
	b _021DF470 ; case 0
	b _021DF444 ; case 1
	b _021DF450 ; case 2
	b _021DF45C ; case 3
	b _021DF468 ; case 4
_021DF444:
	mov r4, #9
	mvn r5, #0
	b _021DF470
_021DF450:
	mov r4, #9
	mvn r5, #1
	b _021DF470
_021DF45C:
	mov r4, #6
	mvn r5, #9
	b _021DF470
_021DF468:
	mov r4, #6
	mvn r5, #0x13
_021DF470:
	ldr r0, _021DF51C ; =ov04_0221053C
	ldr r1, [r0]
	ldr r0, [r1, #0x24]
	cmp r0, #5
	addls pc, pc, r0, lsl #2
	b _021DF500
_021DF488: ; jump table
	b _021DF500 ; case 0
	b _021DF4A0 ; case 1
	b _021DF4B8 ; case 2
	b _021DF500 ; case 3
	b _021DF4F4 ; case 4
	b _021DF4DC ; case 5
_021DF4A0:
	ldr r1, _021DF520 ; =0xFFFF11B8
	mov r0, r4
	add r5, r5, r1
	mov r1, r5
	bl ov04_021E0EAC
	b _021DF508
_021DF4B8:
	ldr r1, [r1, #0x9c]
	ldr r0, _021DF520 ; =0xFFFF11B8
	cmp r1, #1
	add r5, r5, r0
	bge _021DF508
	mov r0, r4
	mov r1, r5
	bl ov04_021E0EAC
	b _021DF508
_021DF4DC:
	ldr r1, _021DF524 ; =0xFFFEC398
	mov r0, r4
	add r5, r5, r1
	mov r1, r5
	bl ov04_021E8E08
	b _021DF508
_021DF4F4:
	ldr r0, _021DF528 ; =0xFFFEEAA8
	add r5, r5, r0
	b _021DF508
_021DF500:
	ldr r0, _021DF52C ; =0xFFFE9C88
	add r5, r5, r0
_021DF508:
	mov r0, r4
	mov r1, r5
	bl ov04_021E2114
	mov r0, r6
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021DF51C: .word ov04_0221053C
_021DF520: .word 0xFFFF11B8
_021DF524: .word 0xFFFEC398
_021DF528: .word 0xFFFEEAA8
_021DF52C: .word 0xFFFE9C88
	arm_func_end ov04_021DF414

	arm_func_start ov04_021DF530
ov04_021DF530: ; 0x021DF530
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov lr, #0
	mov ip, lr
	cmp r1, #0
	ble _021DF560
	mov r3, #1
_021DF54C:
	ldrb r2, [r0, ip]
	add ip, ip, #1
	cmp ip, r1
	orr lr, lr, r3, lsl r2
	blt _021DF54C
_021DF560:
	mov r0, lr
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end ov04_021DF530

	arm_func_start ov04_021DF56C
ov04_021DF56C: ; 0x021DF56C
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	mov r4, r0
	add r0, sp, #0
	bl ov04_021E874C
	mov r1, r0
	cmp r1, #0
	mov r0, #0
	ble _021DF5B0
	ldr r3, [sp]
_021DF594:
	ldrb r2, [r3]
	cmp r4, r2
	beq _021DF5B0
	add r0, r0, #1
	cmp r0, r1
	add r3, r3, #1
	blt _021DF594
_021DF5B0:
	cmp r0, r1
	addeq sp, sp, #8
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	bl ov04_021E8830
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	arm_func_end ov04_021DF56C

	arm_func_start ov04_021DF5CC
ov04_021DF5CC: ; 0x021DF5CC
	ldr r1, _021DF5E8 ; =ov04_0221053C
	ldr r3, [r1]
	ldr r2, [r3, #0x24]
	str r2, [r3, #0x28]
	ldr r1, [r1]
	str r0, [r1, #0x24]
	bx lr
	.align 2, 0
_021DF5E8: .word ov04_0221053C
	arm_func_end ov04_021DF5CC

	arm_func_start ov04_021DF5EC
ov04_021DF5EC: ; 0x021DF5EC
	bx lr
	arm_func_end ov04_021DF5EC

	arm_func_start ov04_021DF5F0
ov04_021DF5F0: ; 0x021DF5F0
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	mov r5, #0
	ldr r4, _021DF634 ; =ov04_02210544
_021DF600:
	ldr r0, [r4, r5, lsl #2]
	cmp r0, #0
	beq _021DF620
	bl ov04_021FD3C4
	ldrb r0, [r0, #1]
	cmp r6, r0
	moveq r0, #1
	ldmeqia sp!, {r4, r5, r6, pc}
_021DF620:
	add r5, r5, #1
	cmp r5, #0x20
	blt _021DF600
	mov r0, #0
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021DF634: .word ov04_02210544
	arm_func_end ov04_021DF5F0

	arm_func_start ov04_021DF638
ov04_021DF638: ; 0x021DF638
	ldr r1, _021DF644 ; =ov04_022105C4
	add r0, r1, r0, lsl #3
	bx lr
	.align 2, 0
_021DF644: .word ov04_022105C4
	arm_func_end ov04_021DF638

	arm_func_start ov04_021DF648
ov04_021DF648: ; 0x021DF648
	stmdb sp!, {lr}
	sub sp, sp, #4
	cmp r1, #0
	mov ip, #0
	ble _021DF684
	ldr r2, _021DF6B8 ; =ov04_0221053C
	ldr r3, [r2]
_021DF664:
	add r2, r3, ip, lsl #2
	ldr r2, [r2, #0x448]
	cmp r0, r2
	beq _021DF684
	add r2, ip, #1
	and ip, r2, #0xff
	cmp ip, r1
	blt _021DF664
_021DF684:
	cmp ip, r1
	addge sp, sp, #4
	movge r0, #0
	ldmgeia sp!, {pc}
	ldr r0, _021DF6B8 ; =ov04_0221053C
	ldr r0, [r0]
	add r0, r0, ip
	ldrb r0, [r0, #0x624]
	bl ov04_021DF760
	bl ov04_021DF730
	bl ov04_021DF6BC
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DF6B8: .word ov04_0221053C
	arm_func_end ov04_021DF648

	arm_func_start ov04_021DF6BC
ov04_021DF6BC: ; 0x021DF6BC
	ldr r1, _021DF6C8 ; =ov04_02210544
	add r0, r1, r0, lsl #2
	bx lr
	.align 2, 0
_021DF6C8: .word ov04_02210544
	arm_func_end ov04_021DF6BC

	arm_func_start ov04_021DF6CC
ov04_021DF6CC: ; 0x021DF6CC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _021DF6FC ; =ov04_02210544
	mov r0, #0
	mov r2, #0x80
	bl MIi_CpuClear32
	ldr r1, _021DF700 ; =ov04_022105C4
	mov r0, #0
	mov r2, #0x100
	bl MIi_CpuClear32
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DF6FC: .word ov04_02210544
_021DF700: .word ov04_022105C4
	arm_func_end ov04_021DF6CC

	arm_func_start ov04_021DF704
ov04_021DF704: ; 0x021DF704
	ldr r2, _021DF72C ; =ov04_02210544
	mov r0, #0
_021DF70C:
	ldr r1, [r2, r0, lsl #2]
	cmp r1, #0
	bxeq lr
	add r0, r0, #1
	cmp r0, #0x20
	blt _021DF70C
	mvn r0, #0
	bx lr
	.align 2, 0
_021DF72C: .word ov04_02210544
	arm_func_end ov04_021DF704

	arm_func_start ov04_021DF730
ov04_021DF730: ; 0x021DF730
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl ov04_021FD3C4
	ldrb r0, [r0]
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end ov04_021DF730

	arm_func_start ov04_021DF748
ov04_021DF748: ; 0x021DF748
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl ov04_021FD3C4
	ldrb r0, [r0, #1]
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end ov04_021DF748

	arm_func_start ov04_021DF760
ov04_021DF760: ; 0x021DF760
	stmdb sp!, {r4, r5, r6, lr}
	ldr r1, _021DF7BC ; =ov04_0221053C
	mov r6, r0
	ldr r0, [r1]
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	ldr r4, _021DF7C0 ; =ov04_02210544
	mov r5, #0
_021DF784:
	ldr r0, [r4, r5, lsl #2]
	cmp r0, #0
	beq _021DF7A8
	bl ov04_021FD3C4
	ldrb r0, [r0, #1]
	cmp r6, r0
	ldreq r0, _021DF7C0 ; =ov04_02210544
	ldreq r0, [r0, r5, lsl #2]
	ldmeqia sp!, {r4, r5, r6, pc}
_021DF7A8:
	add r5, r5, #1
	cmp r5, #0x20
	blt _021DF784
	mov r0, #0
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021DF7BC: .word ov04_0221053C
_021DF7C0: .word ov04_02210544
	arm_func_end ov04_021DF760

	arm_func_start ov04_021DF7C4
ov04_021DF7C4: ; 0x021DF7C4
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r0, _021DF87C ; =ov04_0221053C
	ldr r0, [r0]
	ldr r0, [r0]
	cmp r0, #0
	addne sp, sp, #8
	movne r0, #0
	ldmneia sp!, {r4, pc}
	mov r0, #0x4000
	bl ov04_021DE8C8
	add r0, r0, #0xc000
	mov r1, r0, lsl #0x10
	ldr r3, _021DF87C ; =ov04_0221053C
	mov r0, #0
	mov r2, r0
	mov r1, r1, lsr #0x10
	ldr r4, [r3]
	bl ov04_021FFEB0
	ldr r1, _021DF880 ; =ov04_021DEB90
	ldr r2, _021DF87C ; =ov04_0221053C
	str r1, [sp]
	mov r1, r0
	ldr r0, [r2]
	ldr r2, [r4, #0x14]
	ldr r3, [r4, #0x18]
	bl ov04_021FD71C
	mov r4, r0
	bl ov04_021DF370
	cmp r0, #0
	addne sp, sp, #8
	movne r0, r4
	ldmneia sp!, {r4, pc}
	ldr r0, _021DF87C ; =ov04_0221053C
	ldr r1, _021DF884 ; =ov04_021E9204
	ldr r0, [r0]
	ldr r0, [r0]
	bl ov04_021FD6C8
	ldr r0, _021DF87C ; =ov04_0221053C
	ldr r1, _021DF888 ; =ov04_021E9464
	ldr r0, [r0]
	ldr r0, [r0]
	bl ov04_021FD434
	mov r0, r4
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_021DF87C: .word ov04_0221053C
_021DF880: .word ov04_021DEB90
_021DF884: .word ov04_021E9204
_021DF888: .word ov04_021E9464
	arm_func_end ov04_021DF7C4

	arm_func_start ov04_021DF88C
ov04_021DF88C: ; 0x021DF88C
	ldr r0, _021DF8A4 ; =ov04_0221053C
	ldr r0, [r0]
	cmp r0, #0
	ldrne r0, [r0, #0x24]
	moveq r0, #0
	bx lr
	.align 2, 0
_021DF8A4: .word ov04_0221053C
	arm_func_end ov04_021DF88C

	arm_func_start ov04_021DF8A8
ov04_021DF8A8: ; 0x021DF8A8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _021DF8F0 ; =ov04_0221053C
	ldr r2, [r1]
	cmp r2, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {pc}
	mov r1, #1
	mov r1, r1,lsl  r0
	ldr r2, [r2, #0x644]
	ands r1, r2, r1
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {pc}
	bl ov04_021DF5F0
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DF8F0: .word ov04_0221053C
	arm_func_end ov04_021DF8A8

	arm_func_start ov04_021DF8F4
ov04_021DF8F4: ; 0x021DF8F4
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r2, _021DF954 ; =ov04_0221053C
	ldr r3, [r2]
	cmp r3, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {pc}
	ldr r1, _021DF958 ; =0x00000624
	add r1, r3, r1
	str r1, [r0]
	ldr r2, [r2]
	ldrb r1, [r2, #0x369]
	cmp r1, #2
	beq _021DF93C
	ldrb r1, [r2, #0x369]
	cmp r1, #3
	bne _021DF948
_021DF93C:
	bl ov04_021E86A4
	add sp, sp, #4
	ldmfd sp!, {pc}
_021DF948:
	bl ov04_021E874C
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DF954: .word ov04_0221053C
_021DF958: .word 0x00000624
	arm_func_end ov04_021DF8F4

	arm_func_start ov04_021DF95C
ov04_021DF95C: ; 0x021DF95C
	ldr r0, _021DF974 ; =ov04_0221053C
	ldr r0, [r0]
	cmp r0, #0
	ldrneb r0, [r0, #0x2c]
	moveq r0, #0
	bx lr
	.align 2, 0
_021DF974: .word ov04_0221053C
	arm_func_end ov04_021DF95C

	arm_func_start ov04_021DF978
ov04_021DF978: ; 0x021DF978
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021DF9D0 ; =ov04_0221053C
	ldr r1, [r0]
	cmp r1, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {pc}
	ldrb r0, [r1, #0x369]
	cmp r0, #2
	beq _021DF9B0
	ldrb r0, [r1, #0x369]
	cmp r0, #3
	bne _021DF9C0
_021DF9B0:
	bl ov04_021E87D8
	add sp, sp, #4
	add r0, r0, #1
	ldmfd sp!, {pc}
_021DF9C0:
	bl ov04_021E8804
	add r0, r0, #1
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DF9D0: .word ov04_0221053C
	arm_func_end ov04_021DF978

	arm_func_start ov04_021DF9D4
ov04_021DF9D4: ; 0x021DF9D4
	stmdb sp!, {r4, lr}
	ldr r1, _021DFA3C ; =ov04_0221053C
	mov r4, r0
	ldr r0, [r1]
	cmp r0, #0
	beq _021DFA14
	bl ov04_021DD6D4
	cmp r0, #0
	bne _021DFA14
	ldr r0, _021DFA3C ; =ov04_0221053C
	ldr r0, [r0]
	ldr r0, [r0, #0x24]
	cmp r0, #5
	beq _021DFA1C
	cmp r0, #6
	beq _021DFA1C
_021DFA14:
	mvn r0, #0
	ldmia sp!, {r4, pc}
_021DFA1C:
	mov r0, r4
	bl ov04_021DF760
	cmp r0, #0
	mvneq r0, #1
	ldmeqia sp!, {r4, pc}
	bl ov04_021FD488
	mov r0, #0
	ldmia sp!, {r4, pc}
	.align 2, 0
_021DFA3C: .word ov04_0221053C
	arm_func_end ov04_021DF9D4

	arm_func_start ov04_021DFA40
ov04_021DFA40: ; 0x021DFA40
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021DFAF0 ; =ov04_0221053C
	ldr r0, [r0]
	cmp r0, #0
	beq _021DFA80
	bl ov04_021DD6D4
	cmp r0, #0
	bne _021DFA80
	ldr r0, _021DFAF0 ; =ov04_0221053C
	ldr r2, [r0]
	ldr r0, [r2, #0x24]
	cmp r0, #5
	beq _021DFA8C
	cmp r0, #6
	beq _021DFA8C
_021DFA80:
	add sp, sp, #4
	mvn r0, #0
	ldmfd sp!, {pc}
_021DFA8C:
	ldrb r0, [r2, #0x361]
	cmp r0, #0
	bne _021DFAC0
	ldr r1, _021DFAF4 ; =ov04_0220D334
	mov r0, #1
	mov r2, #0
	bl ov04_021E1E30
	bl ov04_02200D6C
	mov r0, #3
	bl ov04_021DF5CC
	add sp, sp, #4
	mov r0, #1
	ldmfd sp!, {pc}
_021DFAC0:
	mov r1, #1
	ldr r0, _021DFAF0 ; =ov04_0221053C
	strb r1, [r2, #0x2d]
	ldr r0, [r0]
	ldr r0, [r0]
	bl ov04_021FD45C
	ldr r1, _021DFAF0 ; =ov04_0221053C
	mov r0, #0
	ldr r1, [r1]
	strb r0, [r1, #0x2d]
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DFAF0: .word ov04_0221053C
_021DFAF4: .word ov04_0220D334
	arm_func_end ov04_021DFA40

	arm_func_start ov04_021DFAF8
ov04_021DFAF8: ; 0x021DFAF8
	ldr r2, _021DFB1C ; =ov04_0221053C
	ldr r3, [r2]
	cmp r3, #0
	moveq r0, #0
	strne r0, [r3, #0x90]
	ldrne r2, [r2]
	movne r0, #1
	strne r1, [r2, #0x94]
	bx lr
	.align 2, 0
_021DFB1C: .word ov04_0221053C
	arm_func_end ov04_021DFAF8

	arm_func_start ov04_021DFB20
ov04_021DFB20: ; 0x021DFB20
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0x224
	mvn ip, #0
	mov r7, r0
	mov r6, r1
	mov r4, r2
	mov r5, r3
	str ip, [sp, #8]
	bl ov04_021DD6D4
	cmp r0, #0
	bne _021DFB60
	ldr r0, _021DFD04 ; =ov04_0221053C
	ldr r0, [r0]
	ldr r0, [r0, #0x24]
	cmp r0, #3
	beq _021DFB6C
_021DFB60:
	add sp, sp, #0x224
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, pc}
_021DFB6C:
	bl ov04_021DF6CC
	ldr r1, _021DFD04 ; =ov04_0221053C
	mov r0, #5
	ldr r2, [r1]
	str r6, [r2, #0x88]
	ldr r1, [r1]
	str r4, [r1, #0x8c]
	bl ov04_021DF5CC
	mov r0, r7
	bl ov04_021E1F84
	movs r4, r0
	beq _021DFBB8
	ldr r0, _021DFD04 ; =ov04_0221053C
	mov r1, r4
	ldr r0, [r0]
	add r0, r0, #0x1c
	bl ov04_021F05F4
	cmp r0, #0
	bne _021DFBC0
_021DFBB8:
	mov r5, #0xb
	b _021DFC8C
_021DFBC0:
	ldr r0, _021DFD04 ; =ov04_0221053C
	add r2, sp, #8
	ldr r0, [r0]
	mov r1, r4
	add r0, r0, #0x1c
	bl ov04_021F0664
	ldr r0, _021DFD04 ; =ov04_0221053C
	ldr r1, [sp, #8]
	ldr r0, [r0]
	add r2, sp, #0x10
	add r0, r0, #0x1c
	bl ov04_021F06E4
	ldr r0, [sp, #0x14]
	cmp r0, #6
	movne r5, #0xb
	bne _021DFC8C
	ldr r0, _021DFD08 ; =ov04_0220D344
	mov r6, #0x30
	add r1, sp, #0xc
	add r2, sp, #0x18
	mov r3, #0x2f
	strb r6, [sp, #0xc]
	bl ov04_021DE9F4
	add r0, sp, #0xc
	mov r1, #0
	mov r2, #0xa
	bl strtoul
	and r6, r0, #0xff
	ldr r0, _021DFD0C ; =ov04_0220D348
	add r1, sp, #0xc
	add r2, sp, #0x18
	mov r3, #0x2f
	bl ov04_021DE9F4
	add r0, sp, #0xc
	mov r1, #0
	mov r2, #0xa
	bl strtoul
	and r0, r0, #0xff
	cmp r0, r6
	moveq r5, #0xd
	beq _021DFC8C
	ldr r6, [sp, #0x238]
	ldr r1, _021DFD10 ; =ov04_021DF12C
	mov r0, r4
	mov r3, r5
	mov r2, #0
	str r6, [sp]
	bl ov04_021E9FD0
	add sp, sp, #0x224
	mov r0, #1
	ldmia sp!, {r4, r5, r6, r7, pc}
_021DFC8C:
	mov r0, r5
	mov r1, #0
	bl ov04_021DD6B0
	ldr r0, _021DFD04 ; =ov04_0221053C
	mov r1, #0
	ldr r4, [r0]
	mov r0, r5
	str r1, [sp]
	ldr r2, [r4, #0x8c]
	mov r3, r1
	str r2, [sp, #4]
	ldr r4, [r4, #0x88]
	mov r2, #1
	blx r4
	ldr r0, _021DFD04 ; =ov04_0221053C
	ldr r0, [r0]
	cmp r0, #0
	beq _021DFCF8
	ldr r0, [r0, #0x24]
	cmp r0, #5
	bne _021DFCF8
	mov r0, #3
	bl ov04_021DF5CC
	ldr r1, _021DFD14 ; =ov04_0220D334
	mov r0, #1
	mov r2, #0
	bl ov04_021E1E30
_021DFCF8:
	mov r0, #1
	add sp, sp, #0x224
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021DFD04: .word ov04_0221053C
_021DFD08: .word ov04_0220D344
_021DFD0C: .word ov04_0220D348
_021DFD10: .word ov04_021DF12C
_021DFD14: .word ov04_0220D334
	arm_func_end ov04_021DFB20

	arm_func_start ov04_021DFD18
ov04_021DFD18: ; 0x021DFD18
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl ov04_021DD6D4
	cmp r0, #0
	bne _021DFD50
	ldr r0, _021DFDB4 ; =ov04_0221053C
	ldr r0, [r0]
	ldr r0, [r0, #0x24]
	cmp r0, #3
	beq _021DFD5C
_021DFD50:
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, pc}
_021DFD5C:
	bl ov04_021DF6CC
	ldr r1, _021DFDB4 ; =ov04_0221053C
	mov r2, #0
	ldr r3, [r1]
	mov r0, #5
	str r6, [r3, #0x88]
	ldr r3, [r1]
	str r5, [r3, #0x8c]
	ldr r1, [r1]
	strb r2, [r1, #0x2c]
	bl ov04_021DF5CC
	sub r0, r7, #1
	ldr r5, [sp, #0x18]
	ldr r1, _021DFDB8 ; =ov04_021DF12C
	mov r3, r4
	and r0, r0, #0xff
	mov r2, #0
	str r5, [sp]
	bl ov04_021EA138
	mov r0, #1
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021DFDB4: .word ov04_0221053C
_021DFDB8: .word ov04_021DF12C
	arm_func_end ov04_021DFD18

	arm_func_start ov04_021DFDBC
ov04_021DFDBC: ; 0x021DFDBC
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x10
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl ov04_021DD6D4
	cmp r0, #0
	bne _021DFDF8
	ldr r0, _021DFE5C ; =ov04_0221053C
	ldr r2, [r0]
	ldr r1, [r2, #0x24]
	cmp r1, #3
	blt _021DFDF8
	cmp r1, #4
	bne _021DFE04
_021DFDF8:
	add sp, sp, #0x10
	mov r0, #0
	ldmia sp!, {r4, r5, r6, pc}
_021DFE04:
	str r6, [r2, #0x78]
	ldr r1, [r0]
	mov r0, #4
	str r5, [r1, #0x7c]
	bl ov04_021DF5CC
	ldr r0, _021DFE5C ; =ov04_0221053C
	ldr r1, [sp, #0x20]
	ldr r3, [r0]
	ldr r0, [sp, #0x24]
	str r4, [sp]
	str r1, [sp, #4]
	ldr r4, [sp, #0x28]
	str r0, [sp, #8]
	ldr r2, _021DFE60 ; =ov04_021DF2B4
	add r0, r3, #0xe0
	add r1, r3, #0x1e0
	mov r3, #0
	str r4, [sp, #0xc]
	bl ov04_021E2174
	mov r0, #1
	add sp, sp, #0x10
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021DFE5C: .word ov04_0221053C
_021DFE60: .word ov04_021DF2B4
	arm_func_end ov04_021DFDBC

	arm_func_start ov04_021DFE64
ov04_021DFE64: ; 0x021DFE64
	stmdb sp!, {r4, r5, r6, lr}
	movs r4, r0
	mov r6, r2
	mov r5, r3
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	bl ov04_021DD6D4
	cmp r0, #0
	bne _021DFE9C
	ldr r0, _021DFF6C ; =ov04_0221053C
	ldr r2, [r0]
	ldr r1, [r2, #0x24]
	cmp r1, #0
	beq _021DFEA4
_021DFE9C:
	mov r0, #0
	ldmia sp!, {r4, r5, r6, pc}
_021DFEA4:
	str r6, [r2, #0x70]
	ldr r1, [r0]
	cmp r4, #0
	str r5, [r1, #0x74]
	beq _021DFEC4
	ldrh r1, [r4]
	cmp r1, #0
	bne _021DFECC
_021DFEC4:
	mov r5, #0
	b _021DFF18
_021DFECC:
	ldr r1, [r0]
	mov r0, #0
	add r1, r1, #0x2e
	mov r2, #0x34
	bl MIi_CpuClear16
	mov r0, r4
	bl ov04_021DE89C
	cmp r0, #0x19
	movhi r5, #0x19
	bhi _021DFF00
	mov r0, r4
	bl ov04_021DE89C
	mov r5, r0
_021DFF00:
	ldr r1, _021DFF6C ; =ov04_0221053C
	mov r0, r4
	ldr r1, [r1]
	mov r2, r5, lsl #1
	add r1, r1, #0x2e
	bl MIi_CpuCopy16
_021DFF18:
	ldr r0, _021DFF6C ; =ov04_0221053C
	mov r1, #0
	ldr r0, [r0]
	add r0, r0, r5, lsl #1
	strh r1, [r0, #0x2e]
	bl ov04_021DDC1C
	cmp r0, #4
	beq _021DFF4C
	ldr r1, _021DFF70 ; =0xFFFF1596
	mov r0, #2
	bl ov04_021E0EAC
	mov r0, #1
	ldmia sp!, {r4, r5, r6, pc}
_021DFF4C:
	mov r0, #1
	bl ov04_021DF5CC
	ldr r0, _021DFF6C ; =ov04_0221053C
	ldr r0, [r0]
	ldr r0, [r0, #0x68]
	bl ov04_021EE898
	mov r0, #1
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021DFF6C: .word ov04_0221053C
_021DFF70: .word 0xFFFF1596
	arm_func_end ov04_021DFE64

	arm_func_start ov04_021DFF74
ov04_021DFF74: ; 0x021DFF74
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl ov04_021DD984
	cmp r0, #0
	beq _021DFF8C
	bl ov04_021DF5EC
_021DFF8C:
	ldr r0, _021E01E4 ; =ov04_0221053C
	ldr r0, [r0]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, [r0, #0x24]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl ov04_021DD6D4
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _021E01E4 ; =ov04_0221053C
	ldr r0, [r0]
	ldr r0, [r0, #0x24]
	cmp r0, #6
	addls pc, pc, r0, lsl #2
	b _021E0194
_021DFFD8: ; jump table
	b _021E0194 ; case 0
	b _021DFFF4 ; case 1
	b _021E0124 ; case 2
	b _021E012C ; case 3
	b _021E012C ; case 4
	b _021E013C ; case 5
	b _021E014C ; case 6
_021DFFF4:
	bl ov04_021EE6A0
	cmp r0, #1
	beq _021E0014
	cmp r0, #2
	beq _021E00FC
	cmp r0, #3
	beq _021E0110
	b _021E0194
_021E0014:
	ldr r0, _021E01E4 ; =ov04_0221053C
	mov r2, #0
	ldr r0, [r0]
	ldr r1, [r0, #0xa0]
	add r0, r0, #0x1c
	bl ov04_021F0F94
	bl ov04_021DF414
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _021E01E4 ; =ov04_0221053C
	mov r1, #0
	ldr r0, [r0]
	ldr r2, _021E01E8 ; =ov04_021DF0D4
	mov r3, r1
	add r0, r0, #0x1c
	bl ov04_021F0EB0
	bl ov04_021DF414
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _021E01E4 ; =ov04_0221053C
	ldr r2, _021E01EC ; =ov04_021DEF6C
	ldr r0, [r0]
	mov r1, #3
	add r0, r0, #0x1c
	mov r3, #0
	bl ov04_021F0EB0
	bl ov04_021DF414
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _021E01E4 ; =ov04_0221053C
	ldr r2, _021E01F0 ; =ov04_021E20C8
	ldr r0, [r0]
	mov r1, #1
	add r0, r0, #0x1c
	mov r3, #0
	bl ov04_021F0EB0
	bl ov04_021DF414
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _021E01E4 ; =ov04_0221053C
	ldr r2, _021E01F4 ; =ov04_021E1FE4
	ldr r0, [r0]
	mov r1, #2
	add r0, r0, #0x1c
	mov r3, #0
	bl ov04_021F0EB0
	bl ov04_021DF414
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #2
	bl ov04_021DF5CC
	bl ov04_021E1034
	b _021E0194
_021E00FC:
	ldr r1, _021E01F8 ; =0xFFFFB172
	mov r0, #3
	bl ov04_021E0EAC
	add sp, sp, #4
	ldmfd sp!, {pc}
_021E0110:
	ldr r1, _021E01FC ; =0xFFFFB17B
	mov r0, #4
	bl ov04_021E0EAC
	add sp, sp, #4
	ldmfd sp!, {pc}
_021E0124:
	bl ov04_021E0F1C
	b _021E0194
_021E012C:
	bl ov04_021E2228
	mov r0, #0
	bl ov04_021E9568
	b _021E0194
_021E013C:
	mov r0, #1
	bl ov04_021E9568
	bl ov04_021E2228
	b _021E0194
_021E014C:
	bl ov04_021EAA64
	bl ov04_021E2228
	ldr r0, _021E01E4 ; =ov04_0221053C
	ldr r1, [r0]
	ldrb r0, [r1, #0x369]
	cmp r0, #2
	beq _021E0174
	ldrb r0, [r1, #0x369]
	cmp r0, #3
	bne _021E0180
_021E0174:
	mov r0, #1
	bl ov04_021E9568
	b _021E0194
_021E0180:
	ldr r0, [r1]
	cmp r0, #0
	beq _021E0194
	mov r0, #0
	bl ov04_021E9568
_021E0194:
	ldr r0, _021E01E4 ; =ov04_0221053C
	ldr r1, [r0]
	ldrb r0, [r1, #0x36c]
	cmp r0, #1
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, [r1, #0x364]
	cmp r0, #0
	beq _021E01CC
	bl ov04_02202280
	ldr r0, _021E01E4 ; =ov04_0221053C
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0, #0x364]
_021E01CC:
	ldr r0, _021E01E4 ; =ov04_0221053C
	mov r1, #0
	ldr r0, [r0]
	strb r1, [r0, #0x36c]
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021E01E4: .word ov04_0221053C
_021E01E8: .word ov04_021DF0D4
_021E01EC: .word ov04_021DEF6C
_021E01F0: .word ov04_021E20C8
_021E01F4: .word ov04_021E1FE4
_021E01F8: .word 0xFFFFB172
_021E01FC: .word 0xFFFFB17B
	arm_func_end ov04_021DFF74

	arm_func_start ov04_021E0200
ov04_021E0200: ; 0x021E0200
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021E0370 ; =ov04_0221053C
	ldr r0, [r0]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, [r0, #0x364]
	cmp r0, #0
	beq _021E023C
	bl ov04_02202280
	ldr r0, _021E0370 ; =ov04_0221053C
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0, #0x364]
_021E023C:
	ldr r0, _021E0370 ; =ov04_0221053C
	mov r2, #0
	ldr r1, [r0]
	strb r2, [r1, #0x36c]
	ldr r0, [r0]
	ldr r0, [r0, #0x438]
	cmp r0, #0
	beq _021E0270
	bl ov04_02203E80
	ldr r0, _021E0370 ; =ov04_0221053C
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0, #0x438]
_021E0270:
	bl ov04_02200D6C
	bl ov04_021FBE7C
	ldr r0, _021E0370 ; =ov04_0221053C
	ldr ip, [r0]
	ldr r0, [ip, #0x1c]
	cmp r0, #0
	beq _021E0324
	mov r1, #0
	mov r2, r1
	mov r3, r1
	add r0, ip, #0x1c
	bl ov04_021F0EB0
	ldr r0, _021E0370 ; =ov04_0221053C
	mov r2, #0
	ldr r0, [r0]
	mov r3, r2
	add r0, r0, #0x1c
	mov r1, #3
	bl ov04_021F0EB0
	ldr r0, _021E0370 ; =ov04_0221053C
	mov r2, #0
	ldr r0, [r0]
	mov r3, r2
	add r0, r0, #0x1c
	mov r1, #1
	bl ov04_021F0EB0
	ldr r0, _021E0370 ; =ov04_0221053C
	mov r2, #0
	ldr r0, [r0]
	mov r1, #2
	add r0, r0, #0x1c
	mov r3, r2
	bl ov04_021F0EB0
	ldr r0, _021E0370 ; =ov04_0221053C
	ldr r0, [r0]
	add r0, r0, #0x1c
	bl ov04_021F0F18
	ldr r0, _021E0370 ; =ov04_0221053C
	ldr r0, [r0]
	add r0, r0, #0x1c
	bl ov04_021F0F64
	mov r1, #0
	ldr r0, _021E0370 ; =ov04_0221053C
	ldr r0, [r0]
	str r1, [r0, #0x1c]
_021E0324:
	bl ov04_021E0E48
	bl ov04_021E1D90
	bl ov04_021E854C
	bl ov04_021EA9C4
	ldr r0, _021E0370 ; =ov04_0221053C
	ldr r0, [r0]
	ldr r0, [r0]
	cmp r0, #0
	beq _021E035C
	bl ov04_021FD704
	ldr r0, _021E0370 ; =ov04_0221053C
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0]
_021E035C:
	ldr r0, _021E0370 ; =ov04_0221053C
	mov r1, #0
	str r1, [r0]
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021E0370: .word ov04_0221053C
	arm_func_end ov04_021E0200

	arm_func_start ov04_021E0374
ov04_021E0374: ; 0x021E0374
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x10
	ldr ip, _021E05D8 ; =ov04_0221053C
	mov r6, r1
	mov r5, r2
	mov r4, r3
	str r0, [ip]
	bl ov04_021DD6F0
	ldr r0, _021E05D8 ; =ov04_0221053C
	mov r2, #0
	ldr r1, [r0]
	ldr r3, _021E05DC ; =ov04_021E8F80
	str r2, [r1]
	ldr r1, [r0]
	ldr r2, _021E05E0 ; =ov04_021DEF60
	str r3, [r1, #4]
	ldr r1, [r0]
	ldr ip, [sp, #0x24]
	str r2, [r1, #8]
	cmp ip, #0
	ldr r2, [r0]
	ldr r3, _021E05E4 ; =ov04_021DEBE4
	ldr r1, _021E05E8 ; =ov04_021DEBD8
	str r3, [r2, #0xc]
	ldr r0, [r0]
	ldr r3, [sp, #0x28]
	str r1, [r0, #0x10]
	ldr r0, _021E05D8 ; =ov04_0221053C
	moveq ip, #0x2000
	ldr r0, [r0]
	cmp r3, #0
	str ip, [r0, #0x14]
	moveq r3, #0x2000
	ldr r1, _021E05D8 ; =ov04_0221053C
	mov r0, #0
	ldr r2, [r1]
	ldr ip, _021E05EC ; =ov04_02210F94
	str r3, [r2, #0x18]
	ldr r2, [r1]
	ldr r3, _021E05F0 ; =ov04_02211094
	str r0, [r2, #0x1c]
	ldr r2, [r1]
	str r6, [r2, #0x20]
	ldr r2, [r1]
	str r0, [r2, #0x24]
	ldr r2, [r1]
	str r0, [r2, #0x28]
	ldr r2, [r1]
	strb r0, [r2, #0x2c]
	ldr r2, [r1]
	strb r0, [r2, #0x2d]
	ldr r2, [r1]
	str r0, [r2, #0x64]
	ldr r2, [r1]
	str ip, [r2, #0x68]
	ldr r2, [r1]
	str r3, [r2, #0x6c]
	ldr r2, [r1]
	str r0, [r2, #0x70]
	ldr r2, [r1]
	str r0, [r2, #0x74]
	ldr r2, [r1]
	str r0, [r2, #0x78]
	ldr r2, [r1]
	str r0, [r2, #0x7c]
	ldr r2, [r1]
	str r0, [r2, #0x80]
	ldr r2, [r1]
	str r0, [r2, #0x84]
	ldr r2, [r1]
	str r0, [r2, #0x88]
	ldr r2, [r1]
	str r0, [r2, #0x8c]
	ldr r2, [r1]
	str r0, [r2, #0x90]
	ldr r1, [r1]
	str r0, [r1, #0x94]
	bl ov04_021DF6CC
	ldr r0, _021E05D8 ; =ov04_0221053C
	mov r3, r5
	ldr r2, [r0]
	ldr r1, [r6, #0x24]
	ldr r0, _021E05F4 ; =ov04_021DF304
	str r1, [sp]
	add r1, r2, #0x2e
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r5, #0
	add r0, r2, #0x98
	mov r1, r6
	add r2, r2, #0x1c
	str r5, [sp, #0xc]
	bl ov04_021E1074
	ldr r0, _021E05D8 ; =ov04_0221053C
	ldr r2, [sp, #0x30]
	ldr r5, [r0]
	ldr r3, [sp, #0x2c]
	str r2, [sp]
	add r0, r5, #0x2f8
	add r1, r5, #0x1c
	add r2, r5, #0x2e
	bl ov04_021E234C
	ldr r0, _021E05D8 ; =ov04_0221053C
	ldr r1, _021E05EC ; =ov04_02210F94
	ldr r2, [r0]
	ldr r0, _021E05F0 ; =ov04_02211094
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, [sp, #0x2c]
	ldr r0, [sp, #0x30]
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	add r0, r2, #0x354
	add r1, r2, #0x1c
	add r3, r2, #4
	bl ov04_021EA368
	ldr r1, _021E05D8 ; =ov04_0221053C
	ldr r0, _021E05F8 ; =0x000007D8
	ldr r1, [r1]
	add r0, r1, r0
	bl ov04_021EACB4
	mov r0, r4
	bl strlen
	cmp r0, #0x100
	movhs r5, #0xff
	bhs _021E0578
	mov r0, r4
	bl strlen
	mov r5, r0
_021E0578:
	ldr r1, _021E05EC ; =ov04_02210F94
	mov r0, r4
	mov r2, r5
	bl MI_CpuCopy8
	ldr r0, [sp, #0x20]
	ldr r1, _021E05EC ; =ov04_02210F94
	mov r2, #0
	strb r2, [r1, r5]
	bl strlen
	cmp r0, #0x100
	movhs r4, #0xff
	bhs _021E05B4
	ldr r0, [sp, #0x20]
	bl strlen
	mov r4, r0
_021E05B4:
	ldr r0, [sp, #0x20]
	ldr r1, _021E05F0 ; =ov04_02211094
	mov r2, r4
	bl MI_CpuCopy8
	ldr r0, _021E05F0 ; =ov04_02211094
	mov r1, #0
	strb r1, [r0, r4]
	add sp, sp, #0x10
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021E05D8: .word ov04_0221053C
_021E05DC: .word ov04_021E8F80
_021E05E0: .word ov04_021DEF60
_021E05E4: .word ov04_021DEBE4
_021E05E8: .word ov04_021DEBD8
_021E05EC: .word ov04_02210F94
_021E05F0: .word ov04_02211094
_021E05F4: .word ov04_021DF304
_021E05F8: .word 0x000007D8
	arm_func_end ov04_021E0374

	.section .data

	.global ov04_0220D334
ov04_0220D334: ; 0x0220D334
	.byte 0x00, 0x00, 0x00, 0x00

	.global ov04_0220D338
ov04_0220D338: ; 0x0220D338
	.asciz "GPCM"

	.balign 4, 0
	.global ov04_0220D340
ov04_0220D340: ; 0x0220D340
	.asciz "MAT"

	.balign 4, 0
	.global ov04_0220D344
ov04_0220D344: ; 0x0220D344
	.asciz "SCM"

	.balign 4, 0
	.global ov04_0220D348
ov04_0220D348: ; 0x0220D348
	.asciz "SCN"

	.balign 4, 0
	.section .bss

	.global ov04_0221053C
ov04_0221053C: ; 0x0221053C
	.space 0x4

	.global ov04_02210540
ov04_02210540: ; 0x02210540
	.space 0x4

	.global ov04_02210544
ov04_02210544: ; 0x02210544
	.space 0x80

	.global ov04_022105C4
ov04_022105C4: ; 0x022105C4
	.space 0x100
