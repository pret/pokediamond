	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MOD04_021D8D18
MOD04_021D8D18: ; 0x021D8D18
	stmdb sp!, {r4, lr}
	ldr r2, _021D8D58 ; =UNK04_02210468
	ldr r1, _021D8D5C ; =0x000013D8
	ldr r2, [r2]
	mov r4, r0
	add r0, r2, r1
	bl OS_LockMutex
	ldr r2, _021D8D58 ; =UNK04_02210468
	ldr r1, _021D8D5C ; =0x000013D8
	ldr r0, [r2]
	add r0, r0, #0x1000
	str r4, [r0, #4]
	ldr r0, [r2]
	add r0, r0, r1
	bl OS_UnlockMutex
	ldmia sp!, {r4, pc}
	.align 2, 0
_021D8D58: .word UNK04_02210468
_021D8D5C: .word 0x000013D8
	arm_func_end MOD04_021D8D18

	arm_func_start MOD04_021D8D60
MOD04_021D8D60: ; 0x021D8D60
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x98
	ldr r4, _021D8EE0 ; =UNK04_0221046C
	mov r3, #0
	ldr r5, [r4, #4]
	ldr ip, [r4]
	cmp r5, r3
	mov r5, r0
	mov r6, r1
	mov r4, r2
	cmpeq ip, r3
	bne _021D8DC0
	ldr r0, _021D8EE4 ; =UNK04_0220BEF8
	bl strlen
	mov r3, r0
	ldr r1, _021D8EE8 ; =UNK04_0220BF04
	ldr r2, _021D8EE4 ; =UNK04_0220BEF8
	mov r0, r5
	bl MOD04_021DAB68
	cmp r0, #0
	beq _021D8E18
	add sp, sp, #0x98
	mov r0, #8
	ldmia sp!, {r4, r5, r6, pc}
_021D8DC0:
	ldr r0, _021D8EEC ; =UNK04_0220BF0C
	bl strlen
	mov r3, r0
	ldr r1, _021D8EE8 ; =UNK04_0220BF04
	ldr r2, _021D8EEC ; =UNK04_0220BF0C
	mov r0, r5
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x98
	movne r0, #8
	ldmneia sp!, {r4, r5, r6, pc}
	mov r0, r6
	bl strlen
	mov r3, r0
	ldr r1, _021D8EF0 ; =UNK04_0220BF14
	mov r0, r5
	mov r2, r6
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x98
	movne r0, #8
	ldmneia sp!, {r4, r5, r6, pc}
_021D8E18:
	ldr r1, _021D8EE0 ; =UNK04_0221046C
	add r0, sp, #0
	bl MOD04_021D9F78
	cmp r0, #0
	addeq sp, sp, #0x98
	moveq r0, #5
	ldmeqia sp!, {r4, r5, r6, pc}
	ldr r0, _021D8EF4 ; =UNK04_0221048C
	add r1, sp, #0
	ldr r2, [r0]
	mov r0, r5
	bl MOD04_021D9C2C
	cmp r0, #0
	addeq sp, sp, #0x98
	moveq r0, #8
	ldmeqia sp!, {r4, r5, r6, pc}
	ldr r0, _021D8EF8 ; =UNK04_02210460
	ldr r0, [r0]
	cmp r0, #1
	bne _021D8E94
	ldr r0, _021D8EFC ; =UNK04_0220BF1C
	bl strlen
	mov r3, r0
	ldr r1, _021D8F00 ; =UNK04_0220BF20
	ldr r2, _021D8EFC ; =UNK04_0220BF1C
	mov r0, r5
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x98
	movne r0, #8
	ldmneia sp!, {r4, r5, r6, pc}
_021D8E94:
	mov r0, r4
	bl wcslen
	cmp r0, #0
	beq _021D8ED4
	mov r0, r4
	bl wcslen
	mov r3, r0
	ldr r1, _021D8F04 ; =UNK04_0220BF28
	mov r0, r5
	mov r2, r4
	mov r3, r3, lsl #1
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x98
	movne r0, #8
	ldmneia sp!, {r4, r5, r6, pc}
_021D8ED4:
	mov r0, #0
	add sp, sp, #0x98
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021D8EE0: .word UNK04_0221046C
_021D8EE4: .word UNK04_0220BEF8
_021D8EE8: .word UNK04_0220BF04
_021D8EEC: .word UNK04_0220BF0C
_021D8EF0: .word UNK04_0220BF14
_021D8EF4: .word UNK04_0221048C
_021D8EF8: .word UNK04_02210460
_021D8EFC: .word UNK04_0220BF1C
_021D8F00: .word UNK04_0220BF20
_021D8F04: .word UNK04_0220BF28
	arm_func_end MOD04_021D8D60

	arm_func_start MOD04_021D8F08
MOD04_021D8F08: ; 0x021D8F08
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r0, _021D91BC ; =UNK04_02210468
	mov r1, #0
	ldr r0, [r0]
	str r1, [sp]
	add r0, r0, #0x1000
	ldr r0, [r0, #0x314]
	ldr r1, _021D91C0 ; =UNK04_0220BF34
	bl MOD04_021DA388
	str r0, [sp]
	cmp r0, #0
	beq _021D8F40
	bl MOD04_021DCA84
_021D8F40:
	ldr r0, _021D91BC ; =UNK04_02210468
	mov r2, #0
	ldr r1, [r0]
	ldr r0, _021D91C4 ; =errno
	str r2, [sp]
	str r2, [r0]
	add r0, r1, #0x1000
	ldr r0, [r0, #0x314]
	ldr r1, _021D91C8 ; =UNK04_0220BF3C
	bl MOD04_021DA388
	bl atol
	ldr r1, _021D91C4 ; =errno
	ldr r1, [r1]
	cmp r1, #0x22
	bne _021D8F9C
	ldr r0, _021D91BC ; =UNK04_02210468
	ldr r2, _021D91CC ; =0x00004E85
	ldr r1, [r0]
	add sp, sp, #4
	add r1, r1, #0x1000
	str r2, [r1, #8]
	mov r0, #0xc
	ldmia sp!, {r4, r5, pc}
_021D8F9C:
	cmp r0, #0xc8
	beq _021D8FC8
	ldr r2, _021D91BC ; =UNK04_02210468
	ldr r1, _021D91D0 ; =0x000059D8
	ldr r2, [r2]
	add r1, r0, r1
	add r0, r2, #0x1000
	str r1, [r0, #8]
	add sp, sp, #4
	mov r0, #0x12
	ldmia sp!, {r4, r5, pc}
_021D8FC8:
	ldr r0, _021D91BC ; =UNK04_02210468
	ldr r2, _021D91D4 ; =0x0000100C
	ldr r3, [r0]
	ldr r1, _021D91D8 ; =UNK04_0220BF48
	add r0, r3, #0x1000
	ldr r0, [r0, #0x314]
	add r2, r3, r2
	mov r3, #4
	bl MOD04_021DA334
	cmp r0, #0
	bgt _021D9014
	ldr r0, _021D91BC ; =UNK04_02210468
	ldr r2, _021D91CC ; =0x00004E85
	ldr r1, [r0]
	add sp, sp, #4
	add r1, r1, #0x1000
	str r2, [r1, #8]
	mov r0, #0xe
	ldmia sp!, {r4, r5, pc}
_021D9014:
	ldr r1, _021D91BC ; =UNK04_02210468
	ldr r0, _021D91D4 ; =0x0000100C
	ldr r2, [r1]
	add r1, sp, #0
	add r0, r2, r0
	mov r2, #0xa
	bl strtol
	ldr r2, _021D91BC ; =UNK04_02210468
	ldr r1, _021D91D4 ; =0x0000100C
	ldr r5, [r2]
	mov r4, r0
	add r0, r5, r1
	bl strlen
	ldr r1, _021D91D4 ; =0x0000100C
	ldr r2, [sp]
	add r1, r5, r1
	add r0, r1, r0
	cmp r2, r0
	ldrne r1, _021D91CC ; =0x00004E85
	addne r0, r5, #0x1000
	strne r1, [r0, #8]
	addne sp, sp, #4
	movne r0, #0xc
	ldmneia sp!, {r4, r5, pc}
	ldr r0, _021D91DC ; =0x00004E20
	add r1, r5, #0x1000
	add r0, r4, r0
	str r0, [r1, #8]
	cmp r4, #0x64
	bge _021D91B0
	ldr ip, _021D91BC ; =UNK04_02210468
	mov r0, #0
	ldr r1, [ip]
	ldr r5, _021D91E0 ; =0x00001052
	add r1, r1, #0x1000
	strb r0, [r1, #0x52]
	ldr r2, [ip]
	ldr r1, _021D91E4 ; =UNK04_0220BF54
	add r2, r2, #0x1000
	strb r0, [r2, #0x1f]
	ldr r2, [ip]
	ldr r3, _021D91E8 ; =0x0000012D
	add r2, r2, #0x1000
	strb r0, [r2, #0x17f]
	ldr r2, [ip]
	add r2, r2, #0x1000
	strb r0, [r2, #0x10]
	ldr r2, [ip]
	add r2, r2, #0x1000
	strb r0, [r2, #0x188]
	ldr r2, [ip]
	add r0, r2, #0x1000
	ldr r0, [r0, #0x314]
	add r2, r2, r5
	bl MOD04_021DA334
	ldr r0, _021D91BC ; =UNK04_02210468
	ldr r2, _021D91EC ; =0x0000101F
	ldr r3, [r0]
	ldr r1, _021D91F0 ; =UNK04_0220BF5C
	add r0, r3, #0x1000
	add r2, r3, r2
	ldr r0, [r0, #0x314]
	mov r3, #0x33
	bl MOD04_021DA334
	ldr r0, _021D91BC ; =UNK04_02210468
	ldr r2, _021D91F4 ; =0x0000117F
	ldr r3, [r0]
	ldr r1, _021D91F8 ; =UNK04_0220BF64
	add r0, r3, #0x1000
	add r2, r3, r2
	ldr r0, [r0, #0x314]
	mov r3, #9
	bl MOD04_021DA334
	ldr r0, _021D91BC ; =UNK04_02210468
	ldr r2, _021D91FC ; =0x00001010
	ldr r3, [r0]
	ldr r1, _021D9200 ; =UNK04_0220BF70
	add r0, r3, #0x1000
	add r2, r3, r2
	ldr r0, [r0, #0x314]
	mov r3, #0xf
	bl MOD04_021DA334
	ldr r0, _021D91BC ; =UNK04_02210468
	ldr r2, _021D9204 ; =0x00001188
	ldr r3, [r0]
	ldr r1, _021D9208 ; =UNK04_0220BF7C
	add r0, r3, #0x1000
	add r2, r3, r2
	ldr r0, [r0, #0x314]
	mov r3, #0x41
	bl MOD04_021DA2F4
	ldr r0, _021D91BC ; =UNK04_02210468
	mov r1, #0
	ldr r0, [r0]
	cmp r4, #0x28
	add r0, r0, #0x1000
	strb r1, [r0, #0x1b3]
	ldrne r0, _021D920C ; =UNK04_02210464
	movne r1, #1
	strne r1, [r0]
	ldreq r0, _021D920C ; =UNK04_02210464
	moveq r1, #2
	streq r1, [r0]
_021D91B0:
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021D91BC: .word UNK04_02210468
_021D91C0: .word UNK04_0220BF34
_021D91C4: .word errno
_021D91C8: .word UNK04_0220BF3C
_021D91CC: .word 0x00004E85
_021D91D0: .word 0x000059D8
_021D91D4: .word 0x0000100C
_021D91D8: .word UNK04_0220BF48
_021D91DC: .word 0x00004E20
_021D91E0: .word 0x00001052
_021D91E4: .word UNK04_0220BF54
_021D91E8: .word 0x0000012D
_021D91EC: .word 0x0000101F
_021D91F0: .word UNK04_0220BF5C
_021D91F4: .word 0x0000117F
_021D91F8: .word UNK04_0220BF64
_021D91FC: .word 0x00001010
_021D9200: .word UNK04_0220BF70
_021D9204: .word 0x00001188
_021D9208: .word UNK04_0220BF7C
_021D920C: .word UNK04_02210464
	arm_func_end MOD04_021D8F08

	arm_func_start MOD04_021D9210
MOD04_021D9210: ; 0x021D9210
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r0, _021D93F4 ; =UNK04_02210468
	mov r1, #0
	ldr r0, [r0]
	add r2, r0, #0x1000
	ldr r0, [r2, #0x314]
	ldr r5, [r2, #0x20c]
	ldr r4, [r2, #0x210]
	bl MOD04_021DA3DC
	cmp r0, #1
	beq _021D9260
	ldr r0, _021D93F4 ; =UNK04_02210468
	ldr r2, _021D93F8 ; =0x00004E84
	ldr r1, [r0]
	add sp, sp, #4
	add r1, r1, #0x1000
	str r2, [r1, #8]
	mov r0, #0xe
	ldmia sp!, {r4, r5, pc}
_021D9260:
	bl MOD04_021D8F08
	cmp r0, #0
	addne sp, sp, #4
	movne r0, #0xe
	ldmneia sp!, {r4, r5, pc}
	ldr r0, _021D93F4 ; =UNK04_02210468
	ldr r1, _021D93F8 ; =0x00004E84
	ldr r0, [r0]
	add r0, r0, #0x1000
	ldr r2, [r0, #8]
	cmp r2, r1
	bge _021D9334
	ldr r0, _021D93FC ; =0x00004E22
	cmp r2, r0
	bne _021D9328
	ldr r0, _021D9400 ; =UNK04_0220BF88
	ldr r1, _021D9404 ; =0x0000071F
	blx r5
	movs r5, r0
	bne _021D92D0
	ldr r0, _021D93F4 ; =UNK04_02210468
	ldr r2, _021D93F8 ; =0x00004E84
	ldr r1, [r0]
	add sp, sp, #4
	add r1, r1, #0x1000
	str r2, [r1, #8]
	mov r0, #2
	ldmia sp!, {r4, r5, pc}
_021D92D0:
	add r1, r5, #0x1f
	ldr r0, _021D9408 ; =UNK04_0221046C
	bic r1, r1, #0x1f
	bl FUN_02096710
	cmp r0, #1
	beq _021D9318
	ldr r0, _021D940C ; =UNK04_0220BF98
	mov r1, r5
	mov r2, #0
	blx r4
	ldr r0, _021D93F4 ; =UNK04_02210468
	ldr r2, _021D93F8 ; =0x00004E84
	ldr r1, [r0]
	add sp, sp, #4
	add r1, r1, #0x1000
	str r2, [r1, #8]
	mov r0, #0xf
	ldmia sp!, {r4, r5, pc}
_021D9318:
	ldr r0, _021D940C ; =UNK04_0220BF98
	mov r1, r5
	mov r2, #0
	blx r4
_021D9328:
	add sp, sp, #4
	mov r0, #0x15
	ldmia sp!, {r4, r5, pc}
_021D9334:
	ldr r0, _021D9410 ; =0x00004E88
	cmp r2, r0
	beq _021D9350
	ldr r0, _021D9414 ; =0x00004E8C
	cmp r2, r0
	beq _021D9378
	b _021D93E8
_021D9350:
	ldr r0, _021D9408 ; =UNK04_0221046C
	bl FUN_02096570
	ldr r0, _021D93F4 ; =UNK04_02210468
	ldr r2, _021D9410 ; =0x00004E88
	ldr r1, [r0]
	add sp, sp, #4
	add r1, r1, #0x1000
	str r2, [r1, #8]
	mov r0, #0x10
	ldmia sp!, {r4, r5, pc}
_021D9378:
	ldr r0, _021D9400 ; =UNK04_0220BF88
	mov r1, #0x700
	blx r5
	movs r5, r0
	bne _021D93AC
	ldr r0, _021D93F4 ; =UNK04_02210468
	ldr r2, _021D9414 ; =0x00004E8C
	ldr r1, [r0]
	add sp, sp, #4
	add r1, r1, #0x1000
	str r2, [r1, #8]
	mov r0, #0x11
	ldmia sp!, {r4, r5, pc}
_021D93AC:
	add r0, r5, #0x1f
	bic r0, r0, #0x1f
	bl DWCi_AUTH_MakeWiFiID
	ldr r0, _021D940C ; =UNK04_0220BF98
	mov r1, r5
	mov r2, #0
	blx r4
	ldr r0, _021D93F4 ; =UNK04_02210468
	ldr r2, _021D9414 ; =0x00004E8C
	ldr r1, [r0]
	add sp, sp, #4
	add r1, r1, #0x1000
	str r2, [r1, #8]
	mov r0, #0x11
	ldmia sp!, {r4, r5, pc}
_021D93E8:
	mov r0, #0x12
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021D93F4: .word UNK04_02210468
_021D93F8: .word 0x00004E84
_021D93FC: .word 0x00004E22
_021D9400: .word UNK04_0220BF88
_021D9404: .word 0x0000071F
_021D9408: .word UNK04_0221046C
_021D940C: .word UNK04_0220BF98
_021D9410: .word 0x00004E88
_021D9414: .word 0x00004E8C
	arm_func_end MOD04_021D9210

	arm_func_start MOD04_021D9418
MOD04_021D9418: ; 0x021D9418
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x14
	mov sb, #0
	mov r0, #1
	ldr r7, _021D96D4 ; =0x00001388
	ldr fp, _021D96D8 ; =0x000082EA
	ldr r5, _021D96DC ; =UNK04_02210468
	ldr r4, _021D96E0 ; =0x000013D8
	mov r6, sb
	str sb, [sp, #8]
	str sb, [sp, #0xc]
	str r0, [sp, #4]
_021D9448:
	ldr r0, [r5]
	add r0, r0, #0x1000
	ldr r1, [r0, #0x314]
	add r0, r1, #0x1000
	ldr r0, [r0, #0xba0]
	cmp r0, #0
	beq _021D9470
	ldr r0, _021D96E4 ; =0x00001B34
	add r0, r1, r0
	bl OS_JoinThread
_021D9470:
	ldr r0, [r5]
	add r1, r0, #0x1000
	ldr r0, [r1, #0x314]
	add r0, r0, #0x1000
	ldr r0, [r0, #0x20]
	cmp r0, #8
	beq _021D9518
	ldr r0, _021D96E8 ; =0x00004E84
	str r0, [r1, #8]
	ldr r0, [r5]
	add r0, r0, #0x1000
	ldr r0, [r0, #0x314]
	add r0, r0, #0x1000
	ldr r0, [r0, #0x20]
	cmp r0, #7
	bne _021D94C0
	mov r0, #0x14
	bl MOD04_021D8D18
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021D94C0:
	cmp sb, #2
	ble _021D9508
	cmp r0, #2
	bne _021D94E0
	mov r0, #9
	bl MOD04_021D8D18
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021D94E0:
	cmp r0, #3
	bne _021D94F8
	mov r0, #0xb
	bl MOD04_021D8D18
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021D94F8:
	mov r0, #0xd
	bl MOD04_021D8D18
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021D9508:
	ldr r0, [sp, #4]
	add sb, sb, #1
	str r0, [sp]
	b _021D9598
_021D9518:
	bl MOD04_021D9210
	cmp r0, #0x10
	beq _021D9544
	cmp r0, #0x11
	beq _021D956C
	cmp r0, #0x15
	bne _021D9578
	mov r0, #0x15
	bl MOD04_021D8D18
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021D9544:
	cmp sb, #2
	ble _021D955C
	mov r0, #0x10
	bl MOD04_021D8D18
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021D955C:
	ldr r0, [sp, #8]
	add sb, sb, #1
	str r0, [sp]
	b _021D9598
_021D956C:
	bl MOD04_021D8D18
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021D9578:
	cmp sb, #2
	blt _021D958C
	bl MOD04_021D8D18
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021D958C:
	ldr r0, [sp, #4]
	add sb, sb, #1
	str r0, [sp]
_021D9598:
	bl OS_GetTick
	mov r8, r0
	mov sl, r1
	bl OS_GetTick
	subs r2, r0, r8
	sbc r0, r1, sl
	mov r1, r0, lsl #6
	ldr r3, [sp, #0xc]
	orr r1, r1, r2, lsr #26
	mov r0, r2, lsl #6
	mov r2, fp
	bl _ll_udiv
	cmp r1, #0
	cmpeq r0, r7
	bhs _021D965C
_021D95D4:
	ldr r0, [r5]
	add r0, r0, r4
	bl OS_LockMutex
	ldr r2, [r5]
	add r1, r2, #0x1000
	ldr r0, [r1, #0x3f0]
	cmp r0, #1
	bne _021D961C
	ldr r2, _021D96E8 ; =0x00004E84
	ldr r0, _021D96E0 ; =0x000013D8
	str r2, [r1, #8]
	ldr r1, [r5]
	add r0, r1, r0
	bl OS_UnlockMutex
	mov r0, #0x14
	bl MOD04_021D8D18
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021D961C:
	add r0, r2, r4
	bl OS_UnlockMutex
	mov r0, r7
	bl OS_Sleep
	bl OS_GetTick
	subs r2, r0, r8
	sbc r0, r1, sl
	mov r1, r0, lsl #6
	orr r1, r1, r2, lsr #26
	mov r0, r2, lsl #6
	mov r2, fp
	mov r3, r6
	bl _ll_udiv
	cmp r1, #0
	cmpeq r0, r7
	blo _021D95D4
_021D965C:
	ldr r0, [r5]
	add r0, r0, #0x1000
	ldr r0, [r0, #0x314]
	bl MOD04_021DAE4C
	ldr r0, [r5]
	add r0, r0, r4
	bl OS_LockMutex
	ldr r0, [sp]
	bl MOD04_021D96EC
	ldr r1, [r5]
	add r1, r1, #0x1000
	str r0, [r1, #4]
	ldr r2, [r5]
	add r1, r2, #0x1000
	ldr r0, [r1, #4]
	cmp r0, #0
	beq _021D96C0
	ldr r2, _021D96E8 ; =0x00004E84
	ldr r0, _021D96E0 ; =0x000013D8
	str r2, [r1, #8]
	ldr r1, [r5]
	add r0, r1, r0
	bl OS_UnlockMutex
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021D96C0:
	add r0, r2, r4
	bl OS_UnlockMutex
	b _021D9448
	arm_func_end MOD04_021D9418

	arm_func_start MOD04_021D96CC
MOD04_021D96CC: ; 0x021D96CC
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021D96D4: .word 0x00001388
_021D96D8: .word 0x000082EA
_021D96DC: .word UNK04_02210468
_021D96E0: .word 0x000013D8
_021D96E4: .word 0x00001B34
_021D96E8: .word 0x00004E84
	arm_func_end MOD04_021D96CC

	arm_func_start MOD04_021D96EC
MOD04_021D96EC: ; 0x021D96EC
	stmdb sp!, {r4, lr}
	ldr r1, _021D97E0 ; =UNK04_0220BEB4
	mov r4, r0
	ldr r0, [r1]
	ldr r1, _021D97E4 ; =UNK04_0220BFA4
	bl strcmp
	cmp r0, #0
	ldrne r0, _021D97E0 ; =UNK04_0220BEB4
	movne r1, #1
	strne r1, [r0, #0x14]
	ldr r0, _021D97E8 ; =UNK04_02210468
	ldr r1, _021D97E0 ; =UNK04_0220BEB4
	ldr r0, [r0]
	add r0, r0, #0x1000
	ldr r2, [r0, #0x20c]
	str r2, [r1, #0xc]
	ldr r2, [r0, #0x210]
	str r2, [r1, #0x10]
	ldr r0, [r0, #0x314]
	bl MOD04_021DB608
	cmp r0, #0
	movne r0, #4
	ldmneia sp!, {r4, pc}
	cmp r4, #1
	bne _021D9758
	ldr r0, _021D97EC ; =UNK04_0221046C
	bl DWCi_BM_GetWiFiInfo
_021D9758:
	ldr r0, _021D97E8 ; =UNK04_02210468
	ldr r2, _021D97F0 ; =0x000011CC
	ldr r3, [r0]
	add r0, r3, #0x1000
	ldr r0, [r0, #0x314]
	add r1, r3, #0x1200
	add r2, r3, r2
	bl MOD04_021D8D60
	ldr r2, _021D97E8 ; =UNK04_02210468
	ldr r1, [r2]
	add r1, r1, #0x1000
	str r0, [r1, #4]
	ldr r0, [r2]
	add r0, r0, #0x1000
	ldr r1, [r0, #4]
	cmp r1, #0
	movne r0, #4
	ldmneia sp!, {r4, pc}
	ldr r0, [r0, #0x314]
	bl MOD04_021DB570
	cmp r0, #0
	movne r0, #4
	ldmneia sp!, {r4, pc}
	ldr r0, _021D97F4 ; =OSi_ThreadInfo
	ldr r0, [r0, #4]
	bl OS_GetThreadPriority
	ldr r1, _021D97E8 ; =UNK04_02210468
	ldr r2, [r1]
	sub r1, r0, #1
	add r0, r2, #0x1000
	ldr r0, [r0, #0x314]
	bl MOD04_021DB4A4
	mov r0, #0
	ldmia sp!, {r4, pc}
	.align 2, 0
_021D97E0: .word UNK04_0220BEB4
_021D97E4: .word UNK04_0220BFA4
_021D97E8: .word UNK04_02210468
_021D97EC: .word UNK04_0221046C
_021D97F0: .word 0x000011CC
_021D97F4: .word OSi_ThreadInfo
	arm_func_end MOD04_021D96EC

	arm_func_start MOD04_021D97F8
MOD04_021D97F8: ; 0x021D97F8
	stmdb sp!, {r4, lr}
	ldr r1, _021D9874 ; =UNK04_02210468
	mov r4, r0
	ldr r1, [r1]
	cmp r1, #0
	bne _021D981C
	mov r1, #0
	mov r2, #0x1c4
	bl MI_CpuFill8
_021D981C:
	ldr r1, _021D9874 ; =UNK04_02210468
	ldr r0, _021D9878 ; =0x00001008
	ldr r2, [r1]
	mov r1, r4
	add r0, r2, r0
	mov r2, #0x1c4
	bl MI_CpuCopy8
	ldr r1, [r4]
	ldr r0, _021D987C ; =0x00004E20
	cmp r1, r0
	blt _021D9854
	ldr r0, _021D9880 ; =0x00007530
	cmp r1, r0
	blt _021D985C
_021D9854:
	ldr r0, _021D9884 ; =0x00005206
	str r0, [r4]
_021D985C:
	ldr r1, [r4]
	ldr r0, _021D9888 ; =0x00004E84
	cmp r1, r0
	rsbge r0, r1, #0
	strge r0, [r4]
	ldmia sp!, {r4, pc}
	.align 2, 0
_021D9874: .word UNK04_02210468
_021D9878: .word 0x00001008
_021D987C: .word 0x00004E20
_021D9880: .word 0x00007530
_021D9884: .word 0x00005206
_021D9888: .word 0x00004E84
	arm_func_end MOD04_021D97F8

	arm_func_start MOD04_021D988C
MOD04_021D988C: ; 0x021D988C
	stmdb sp!, {r4, lr}
	ldr r0, _021D98D4 ; =UNK04_02210468
	ldr r1, [r0]
	cmp r1, #0
	moveq r0, #0x16
	ldmeqia sp!, {r4, pc}
	ldr r0, _021D98D8 ; =0x000013D8
	add r0, r1, r0
	bl OS_LockMutex
	ldr r1, _021D98D4 ; =UNK04_02210468
	ldr r0, _021D98D8 ; =0x000013D8
	ldr r2, [r1]
	add r1, r2, #0x1000
	add r0, r2, r0
	ldr r4, [r1, #4]
	bl OS_UnlockMutex
	mov r0, r4
	ldmia sp!, {r4, pc}
	.align 2, 0
_021D98D4: .word UNK04_02210468
_021D98D8: .word 0x000013D8
	arm_func_end MOD04_021D988C

	arm_func_start MOD04_021D98DC
MOD04_021D98DC: ; 0x021D98DC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021D9914 ; =UNK04_02210468
	ldr r1, [r0]
	add r0, r1, #0x1000
	ldr r0, [r0, #0x384]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _021D9918 ; =0x00001318
	add r0, r1, r0
	bl OS_JoinThread
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021D9914: .word UNK04_02210468
_021D9918: .word 0x00001318
	arm_func_end MOD04_021D98DC

	arm_func_start MOD04_021D991C
MOD04_021D991C: ; 0x021D991C
	stmdb sp!, {r4, lr}
	ldr r0, _021D996C ; =UNK04_02210468
	ldr r0, [r0]
	cmp r0, #0
	ldmeqia sp!, {r4, pc}
	add r1, r0, #0x1000
	ldr r0, [r1, #0x314]
	ldr r4, [r1, #0x210]
	cmp r0, #0
	beq _021D9948
	bl MOD04_021DAE4C
_021D9948:
	ldr r1, _021D996C ; =UNK04_02210468
	ldr r0, _021D9970 ; =UNK04_0220BFC4
	ldr r1, [r1]
	mov r2, #0
	blx r4
	ldr r0, _021D996C ; =UNK04_02210468
	mov r1, #0
	str r1, [r0]
	ldmia sp!, {r4, pc}
	.align 2, 0
_021D996C: .word UNK04_02210468
_021D9970: .word UNK04_0220BFC4
	arm_func_end MOD04_021D991C

	arm_func_start MOD04_021D9974
MOD04_021D9974: ; 0x021D9974
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021D9A0C ; =UNK04_02210468
	ldr r1, [r0]
	cmp r1, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _021D9A10 ; =0x000013D8
	add r0, r1, r0
	bl OS_LockMutex
	ldr r2, _021D9A0C ; =UNK04_02210468
	mov r3, #1
	ldr r0, [r2]
	ldr r1, _021D9A10 ; =0x000013D8
	add r0, r0, #0x1000
	str r3, [r0, #0x3f0]
	ldr r0, [r2]
	add r0, r0, r1
	bl OS_UnlockMutex
	ldr r0, _021D9A0C ; =UNK04_02210468
	ldr r0, [r0]
	add r0, r0, #0x1000
	ldr r0, [r0, #0x314]
	cmp r0, #0
	beq _021D99DC
	bl MOD04_021DB440
_021D99DC:
	ldr r0, _021D9A0C ; =UNK04_02210468
	ldr r1, [r0]
	add r0, r1, #0x1000
	ldr r0, [r0, #0x384]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _021D9A14 ; =0x00001318
	add r0, r1, r0
	bl OS_JoinThread
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021D9A0C: .word UNK04_02210468
_021D9A10: .word 0x000013D8
_021D9A14: .word 0x00001318
	arm_func_end MOD04_021D9974

	arm_func_start MOD04_021D9A18
MOD04_021D9A18: ; 0x021D9A18
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r1, _021D9ABC ; =UNK04_02210468
	ldr r0, _021D9AC0 ; =0x000013D8
	ldr r1, [r1]
	add r0, r1, r0
	bl OS_InitMutex
	ldr r1, _021D9ABC ; =UNK04_02210468
	mov r2, #0
	ldr r0, [r1]
	add r0, r0, #0x1000
	str r2, [r0, #0x3f0]
	ldr r1, [r1]
	add r0, r1, #0x1000
	ldr r0, [r0, #0x384]
	cmp r0, #0
	beq _021D9A74
	ldr r0, _021D9AC4 ; =0x00001318
	add r0, r1, r0
	bl OS_IsThreadTerminated
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {pc}
_021D9A74:
	ldr r2, _021D9ABC ; =UNK04_02210468
	ldr r0, _021D9AC4 ; =0x00001318
	ldr lr, [r2]
	mov r3, #0x1000
	ldr r1, _021D9AC8 ; =MOD04_021D9418
	str r3, [sp]
	mov ip, #0x10
	add r0, lr, r0
	add r3, lr, #0x1000
	str ip, [sp, #4]
	bl OS_CreateThread
	ldr r1, _021D9ABC ; =UNK04_02210468
	ldr r0, _021D9AC4 ; =0x00001318
	ldr r1, [r1]
	add r0, r1, r0
	bl OS_WakeupThreadDirect
	add sp, sp, #0xc
	ldmfd sp!, {pc}
	.align 2, 0
_021D9ABC: .word UNK04_02210468
_021D9AC0: .word 0x000013D8
_021D9AC4: .word 0x00001318
_021D9AC8: .word MOD04_021D9418
	arm_func_end MOD04_021D9A18

	arm_func_start MOD04_021D9ACC
MOD04_021D9ACC: ; 0x021D9ACC
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r2, _021D9BFC ; =UNK04_02210468
	mov r5, r0
	ldr r0, [r2]
	mov r4, r1
	cmp r0, #0
	addne sp, sp, #4
	ldr r2, [r5, #0x40]
	movne r0, #2
	ldmneia sp!, {r4, r5, pc}
	ldr r0, _021D9C00 ; =UNK04_0220BFD4
	ldr r1, _021D9C04 ; =0x000013F4
	blx r2
	ldr r1, _021D9BFC ; =UNK04_02210468
	cmp r0, #0
	str r0, [r1]
	addeq sp, sp, #4
	moveq r0, #2
	ldmeqia sp!, {r4, r5, pc}
	ldr r2, _021D9C04 ; =0x000013F4
	mov r1, #0
	bl MI_CpuFill8
	ldr r1, _021D9BFC ; =UNK04_02210468
	ldr r2, _021D9C08 ; =0x00001008
	ldr r0, [r1]
	ldr r3, _021D9C0C ; =UNK04_02210464
	add r0, r0, #0x1000
	str r4, [r0, #0x314]
	ldr r0, [r1]
	mov r1, #0
	add r0, r0, r2
	mov r2, #0x1c4
	str r1, [r3]
	bl MI_CpuFill8
	ldr r2, _021D9BFC ; =UNK04_02210468
	ldr r3, _021D9C10 ; =0x00004E84
	ldr r0, [r2]
	ldr r1, _021D9C14 ; =0x000011CC
	add r0, r0, #0x1000
	str r3, [r0, #8]
	ldr lr, [r2]
	mov r4, #4
	add ip, lr, r1
_021D9B7C:
	ldmia r5!, {r0, r1, r2, r3}
	stmia ip!, {r0, r1, r2, r3}
	subs r4, r4, #1
	bne _021D9B7C
	ldmia r5, {r0, r1}
	stmia ip, {r0, r1}
	add r0, lr, #0x1100
	mov r2, #0
	strh r2, [r0, #0xfe]
	ldr r1, _021D9BFC ; =UNK04_02210468
	mov r0, #1
	ldr r1, [r1]
	add r1, r1, #0x1000
	strb r2, [r1, #0x20b]
	bl MOD04_021D96EC
	ldr r2, _021D9BFC ; =UNK04_02210468
	ldr r1, [r2]
	add r1, r1, #0x1000
	str r0, [r1, #4]
	ldr r0, [r2]
	add r0, r0, #0x1000
	ldr r0, [r0, #4]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	ldr r0, _021D9C18 ; =UNK04_02210460
	mov r1, #0
	str r1, [r0]
	bl MOD04_021D9A18
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021D9BFC: .word UNK04_02210468
_021D9C00: .word UNK04_0220BFD4
_021D9C04: .word 0x000013F4
_021D9C08: .word 0x00001008
_021D9C0C: .word UNK04_02210464
_021D9C10: .word 0x00004E84
_021D9C14: .word 0x000011CC
_021D9C18: .word UNK04_02210460
	arm_func_end MOD04_021D9ACC

	arm_func_start MOD04_021D9C1C
MOD04_021D9C1C: ; 0x021D9C1C
	ldr r1, _021D9C28 ; =UNK04_0220BEB4
	str r0, [r1]
	bx lr
	.align 2, 0
_021D9C28: .word UNK04_0220BEB4
	arm_func_end MOD04_021D9C1C

	.section .data

	.global UNK04_0220BEB4
UNK04_0220BEB4: ; 0x0220BEB4
	.word UNK04_0220BED0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x4E, 0x00, 0x00

	.global UNK04_0220BED0
UNK04_0220BED0: ; 0x0220BED0
	.asciz "https://nas.test.nintendowifi.net/ac"

	.balign 4, 0
	.global UNK04_0220BEF8
UNK04_0220BEF8: ; 0x0220BEF8
	.asciz "acctcreate"

	.balign 4, 0
	.global UNK04_0220BF04
UNK04_0220BF04: ; 0x0220BF04
	.asciz "action"

	.balign 4, 0
	.global UNK04_0220BF0C
UNK04_0220BF0C: ; 0x0220BF0C
	.asciz "login"

	.balign 4, 0
	.global UNK04_0220BF14
UNK04_0220BF14: ; 0x0220BF14
	.asciz "gsbrcd"

	.balign 4, 0
	.global UNK04_0220BF1C
UNK04_0220BF1C: ; 0x0220BF1C
	.asciz "Y"

	.balign 4, 0
	.global UNK04_0220BF20
UNK04_0220BF20: ; 0x0220BF20
	.asciz "iswfc"

	.balign 4, 0
	.global UNK04_0220BF28
UNK04_0220BF28: ; 0x0220BF28
	.asciz "ingamesn"

	.balign 4, 0
	.global UNK04_0220BF34
UNK04_0220BF34: ; 0x0220BF34
	.asciz "Date"

	.balign 4, 0
	.global UNK04_0220BF3C
UNK04_0220BF3C: ; 0x0220BF3C
	.asciz "httpresult"

	.balign 4, 0
	.global UNK04_0220BF48
UNK04_0220BF48: ; 0x0220BF48
	.asciz "returncd"

	.balign 4, 0
	.global UNK04_0220BF54
UNK04_0220BF54: ; 0x0220BF54
	.asciz "token"

	.balign 4, 0
	.global UNK04_0220BF5C
UNK04_0220BF5C: ; 0x0220BF5C
	.asciz "locator"

	.balign 4, 0
	.global UNK04_0220BF64
UNK04_0220BF64: ; 0x0220BF64
	.asciz "challenge"

	.balign 4, 0
	.global UNK04_0220BF70
UNK04_0220BF70: ; 0x0220BF70
	.asciz "datetime"

	.balign 4, 0
	.global UNK04_0220BF7C
UNK04_0220BF7C: ; 0x0220BF7C
	.asciz "Set-Cookie"

	.balign 4, 0
	.global UNK04_0220BF88
UNK04_0220BF88: ; 0x0220BF88
	.asciz "ALLOC bmwork"

	.balign 4, 0
	.global UNK04_0220BF98
UNK04_0220BF98: ; 0x0220BF98
	.asciz "FREE bmwork"

	.balign 4, 0
	.global UNK04_0220BFA4
UNK04_0220BFA4: ; 0x0220BFA4
	.asciz "https://nas.nintendowifi.net/ac"

	.balign 4, 0
	.global UNK04_0220BFC4
UNK04_0220BFC4: ; 0x0220BFC4
	.asciz "FREE DWCauth"

	.balign 4, 0
	.global UNK04_0220BFD4
UNK04_0220BFD4: ; 0x0220BFD4
	.asciz "ALLOC DWCauth"

	.balign 4, 0
	.section .bss

	.global UNK04_02210460
UNK04_02210460: ; 0x02210460
	.space 0x4

	.global UNK04_02210464
UNK04_02210464: ; 0x02210464
	.space 0x4

	.global UNK04_02210468
UNK04_02210468: ; 0x02210468
	.space 0x4

	.global UNK04_0221046C
UNK04_0221046C: ; 0x0221046C
	.space 0x14

	.global UNK04_02210480
UNK04_02210480: ; 0x02210480
	.space 0x4

	.global UNK04_02210484
UNK04_02210484: ; 0x02210484
	.space 0x4

	.global UNK04_02210488
UNK04_02210488: ; 0x02210488
	.space 0x4

	.global UNK04_0221048C
UNK04_0221048C: ; 0x0221048C
	.space 0x4
