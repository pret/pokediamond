	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; _end
	arm_func_start FUN_020B20C8
FUN_020B20C8: ; 0x020B20C8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r6, #0x0
	str r6, [r0, #0x38]
	ldr r7, [sp, #0x30]
	str r6, [r0, #0x30]
	mov r10, r1
	str r7, [r0, #0x34]
	str r0, [sp, #0x0]
	movs r8, r3
	mov r9, r2
	str r10, [r0, #0x3c]
	ldr r11, [sp, #0x34]
	beq _020B215C
	mov r0, #0x1
	str r6, [sp, #0x8]
	str r0, [sp, #0x4]
_020B210C:
	mov r0, #0x28
	mul r4, r6, r0
	ldr r1, [sp, #0x4]
	add r0, r10, r4
	bl FUN_020B1AD4
	mov r0, #0x54
	mla r5, r6, r0, r9
	ldr r1, [sp, #0x8]
	mov r0, r7
	str r5, [r10, r4]
	bl FUN_020AFC04
	mov r1, r0
	mov r0, r5
	mov r2, r11
	bl FUN_020B1F80
	add r0, r6, #0x1
	mov r0, r0, lsl #0x10
	mov r6, r0, lsr #0x10
	cmp r6, r8
	blo _020B210C
_020B215C:
	ldr r0, [sp, #0x0]
	bl FUN_020B04C0
	ldr r0, [sp, #0x0]
	ldr r3, [sp, #0x38]
	ldr r2, [sp, #0x0]
	add r0, r0, #0x44
	mov r1, #0x1
	str r3, [r2, #0x40]
	bl FUN_020B1A68
	ldr r0, [sp, #0x0]
	mov r1, #0x0
	strh r1, [r0, #0x2c]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
	arm_func_end FUN_020B20C8

	; _end
	arm_func_start FUN_020B2194
FUN_020B2194: ; 0x020B2194
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	bl FUN_020B0518
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
	mov r0, r7
	bl FUN_020B06E0
	mov r4, r0
	ldrh r1, [r4, #0x0]
	ldr r0, [r7, #0x40]
	bl FUN_020AFF34
	ldr r1, [r7, #0x18]
	mov r6, r0
	ldr r1, [r1, #0x4]
	add r0, r7, #0x44
	and r5, r1, #0xff
	mov r1, #0x1
	bl FUN_020B1A68
	cmp r5, #0x0
	beq _020B2234
	cmp r5, #0x2
	bne _020B2208
	ldrsh r1, [r4, #0x4]
	ldrsh r2, [r4, #0x6]
	add r0, r7, #0x44
	bl FUN_020B1AB4
	b _020B2234
_020B2208:
	ldr r1, [r4, #0x4]
	ldr r2, [r4, #0x8]
	add r0, r7, #0x44
	bl FUN_020B1A78
	ldrh r1, [r4, #0x2]
	add r0, r7, #0x44
	bl FUN_020B1A98
	ldrsh r1, [r4, #0xc]
	ldrsh r2, [r4, #0xe]
	add r0, r7, #0x44
	bl FUN_020B1AB4
_020B2234:
	ldrh r2, [r7, #0x2c]
	mov r1, r6
	add r0, r7, #0x30
	bl FUN_020B24E0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	arm_func_end FUN_020B2194

	; _end
	arm_func_start FUN_020B224C
FUN_020B224C: ; 0x020B224C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldr r2, [r4, #0x0]
	mov r6, r1
	ldrh r5, [r2, #0x4]
	bl FUN_020B0534
	cmp r0, #0x0
	beq _020B2318
	ldrh r1, [r4, #0x2c]
	mov r0, r4
	add r1, r1, r5
	strh r1, [r4, #0x2c]
	bl FUN_020B06E0
	mov r5, r0
	ldrh r1, [r5, #0x0]
	ldr r0, [r4, #0x40]
	bl FUN_020AFF34
	ldr r1, [r4, #0x18]
	mov r7, r0
	ldr r1, [r1, #0x4]
	add r0, r4, #0x44
	and r6, r1, #0xff
	mov r1, #0x1
	bl FUN_020B1A68
	cmp r6, #0x0
	beq _020B2300
	cmp r6, #0x2
	bne _020B22D4
	ldrsh r1, [r5, #0x4]
	ldrsh r2, [r5, #0x6]
	add r0, r4, #0x44
	bl FUN_020B1AB4
	b _020B2300
_020B22D4:
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x8]
	add r0, r4, #0x44
	bl FUN_020B1A78
	ldrh r1, [r5, #0x2]
	add r0, r4, #0x44
	bl FUN_020B1A98
	ldrsh r1, [r5, #0xc]
	ldrsh r2, [r5, #0xe]
	add r0, r4, #0x44
	bl FUN_020B1AB4
_020B2300:
	ldrh r2, [r4, #0x2c]
	mov r1, r7
	add r0, r4, #0x30
	bl FUN_020B24E0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
_020B2318:
	mov r1, r6
	add r0, r4, #0x30
	bl FUN_020B232C
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	arm_func_end FUN_020B224C

	; _end
	arm_func_start FUN_020B232C
FUN_020B232C: ; 0x020B232C
	stmdb sp!, {r4-r8,lr}
	mov r7, r0
	ldr r0, [r7, #0x8]
	mov r6, r1
	cmp r0, #0x1
	bne _020B238C
	ldr r0, [r7, #0x0]
	ldr r4, [r7, #0xc]
	ldrh r0, [r0, #0x2]
	mov r5, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r8,pc}
	mov r8, #0x58
_020B2360:
	mla r0, r5, r8, r4
	mov r1, r6
	bl FUN_020B1EC4
	ldr r1, [r7, #0x0]
	add r0, r5, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r1, #0x2]
	mov r5, r0, lsr #0x10
	cmp r5, r1
	blo _020B2360
	ldmia sp!, {r4-r8,pc}
_020B238C:
	ldr r0, [r7, #0x0]
	ldr r4, [r7, #0xc]
	ldrh r0, [r0, #0x0]
	mov r5, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r8,pc}
	mov r8, #0x28
_020B23A8:
	mul r0, r5, r8
	ldr r0, [r4, r0]
	mov r1, r6
	bl FUN_020B1EC4
	ldr r1, [r7, #0x0]
	add r0, r5, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r1, #0x0]
	mov r5, r0, lsr #0x10
	cmp r5, r1
	blo _020B23A8
	ldmia sp!, {r4-r8,pc}
	arm_func_end FUN_020B232C

	; _end
	arm_func_start FUN_020B23D8
FUN_020B23D8: ; 0x020B23D8
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	ldrh r0, [r5, #0x0]
	mov r4, #0x0
	mov r6, r4
	cmp r0, #0x0
	bls _020B2424
_020B23F4:
	mov r0, r5
	mov r1, r6
	bl FUN_020AFF34
	ldrh r0, [r0, #0x0]
	ldrh r1, [r5, #0x0]
	cmp r0, r4
	movhi r4, r0
	add r0, r6, #0x1
	mov r0, r0, lsl #0x10
	mov r6, r0, lsr #0x10
	cmp r6, r1
	blo _020B23F4
_020B2424:
	mov r0, r4
	ldmia sp!, {r4-r6,pc}
	arm_func_end FUN_020B23D8

	; _end
	arm_func_start FUN_020B242C
FUN_020B242C: ; 0x020B242C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	bl FUN_020B0438
	mov r1, #0x0
	mov r0, r7
	strh r1, [r7, #0x2c]
	bl FUN_020B06E0
	mov r4, r0
	ldrh r1, [r4, #0x0]
	ldr r0, [r7, #0x40]
	bl FUN_020AFF34
	ldr r1, [r7, #0x18]
	mov r6, r0
	ldr r1, [r1, #0x4]
	add r0, r7, #0x44
	and r5, r1, #0xff
	mov r1, #0x1
	bl FUN_020B1A68
	cmp r5, #0x0
	beq _020B24C8
	cmp r5, #0x2
	bne _020B249C
	ldrsh r1, [r4, #0x4]
	ldrsh r2, [r4, #0x6]
	add r0, r7, #0x44
	bl FUN_020B1AB4
	b _020B24C8
_020B249C:
	ldr r1, [r4, #0x4]
	ldr r2, [r4, #0x8]
	add r0, r7, #0x44
	bl FUN_020B1A78
	ldrh r1, [r4, #0x2]
	add r0, r7, #0x44
	bl FUN_020B1A98
	ldrsh r1, [r4, #0xc]
	ldrsh r2, [r4, #0xe]
	add r0, r7, #0x44
	bl FUN_020B1AB4
_020B24C8:
	ldrh r2, [r7, #0x2c]
	mov r1, r6
	add r0, r7, #0x30
	bl FUN_020B24E0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	arm_func_end FUN_020B242C

	; _end
	arm_func_start FUN_020B24E0
FUN_020B24E0: ; 0x020B24E0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r10, r1
	str r0, [sp, #0x0]
	str r10, [r0, #0x0]
	ldr r0, [r0, #0x8]
	mov r9, r2
	cmp r0, #0x1
	bne _020B2654
	ldrh r1, [r10, #0x2]
	ldr r0, [sp, #0x0]
	mov r4, #0x0
	ldr r8, [r0, #0xc]
	cmp r1, #0x0
	bls _020B2544
	mov r3, r4
	mov r0, #0x58
_020B2524:
	mla r1, r4, r0, r8
	str r3, [r1, #0x54]
	add r1, r4, #0x1
	mov r1, r1, lsl #0x10
	ldrh r2, [r10, #0x2]
	mov r4, r1, lsr #0x10
	cmp r4, r2
	blo _020B2524
_020B2544:
	ldrh r0, [r10, #0x0]
	mov r5, #0x0
	cmp r0, #0x0
	addls sp, sp, #0x14
	ldmlsia sp!, {r4-r11,pc}
	str r5, [sp, #0x4]
	mov r11, #0x1
_020B2560:
	ldr r0, [r10, #0x4]
	mov r1, #0x58
	add r7, r0, r5, lsl #0x3
	ldrh r0, [r7, #0x6]
	and r0, r0, #0xff00
	mov r0, r0, lsl #0x8
	mov r0, r0, lsr #0x10
	mla r6, r0, r1, r8
	ldr r0, [r6, #0x54]
	cmp r0, #0x0
	bne _020B2634
	ldr r0, [sp, #0x0]
	ldrh r1, [r7, #0x0]
	ldr r0, [r0, #0x4]
	bl FUN_020AFC04
	mov r4, r0
	mov r0, r6
	mov r1, r4
	bl FUN_020B1EE4
	str r11, [r6, #0x8]
	ldrh r0, [r7, #0x6]
	and r0, r0, #0xf
	cmp r0, #0x1
	bne _020B2630
	ldrh r1, [r4, #0x0]
	ldr r7, [sp, #0x4]
	mov r3, r7
	cmp r1, #0x0
	bls _020B25F0
	ldr r2, [r4, #0xc]
_020B25D8:
	add r0, r2, r3, lsl #0x3
	ldrh r0, [r0, #0x4]
	add r3, r3, #0x1
	cmp r3, r1
	add r7, r7, r0
	blo _020B25D8
_020B25F0:
	mov r0, r6
	bl FUN_020B0408
	cmp r0, #0x0
	beq _020B261C
	mov r0, r9
	mov r1, r7
	bl _u32_div_f
	mov r0, r6
	mov r1, r1, lsl #0xc
	bl FUN_020B1EC4
	b _020B2630
_020B261C:
	cmp r9, r7
	movcc r7, r9
	mov r0, r6
	mov r1, r7, lsl #0xc
	bl FUN_020B1EC4
_020B2630:
	str r11, [r6, #0x54]
_020B2634:
	add r0, r5, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r10, #0x0]
	mov r5, r0, lsr #0x10
	cmp r5, r1
	blo _020B2560
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,pc}
_020B2654:
	ldrh r1, [r10, #0x0]
	ldr r0, [sp, #0x0]
	mov r4, #0x0
	cmp r1, #0x0
	ldr r11, [r0, #0xc]
	addls sp, sp, #0x14
	ldmlsia sp!, {r4-r11,pc}
	mov r0, #0x1
	str r4, [sp, #0xc]
	str r0, [sp, #0x8]
_020B267C:
	mov r0, #0x28
	mul r2, r4, r0
	ldr r3, [r10, #0x4]
	mov r0, r4, lsl #0x3
	ldrh r1, [r3, r0]
	ldr r0, [sp, #0x0]
	ldr r6, [r11, r2]
	ldr r0, [r0, #0x4]
	add r7, r3, r4, lsl #0x3
	bl FUN_020AFC04
	mov r5, r0
	mov r0, r6
	mov r1, r5
	bl FUN_020B1EE4
	ldr r0, [sp, #0x8]
	str r0, [r6, #0x8]
	ldrh r0, [r7, #0x6]
	and r0, r0, #0xf
	cmp r0, #0x1
	bne _020B2740
	ldrh r1, [r5, #0x0]
	ldr r8, [sp, #0xc]
	mov r0, r8
	cmp r1, #0x0
	bls _020B2700
	ldr r3, [r5, #0xc]
_020B26E4:
	add r1, r3, r0, lsl #0x3
	ldrh r2, [r1, #0x4]
	add r0, r0, #0x1
	ldrh r1, [r5, #0x0]
	add r8, r8, r2
	cmp r0, r1
	blo _020B26E4
_020B2700:
	mov r0, r6
	bl FUN_020B0408
	cmp r0, #0x0
	beq _020B272C
	mov r0, r9
	mov r1, r8
	bl _u32_div_f
	mov r0, r6
	mov r1, r1, lsl #0xc
	bl FUN_020B1EC4
	b _020B2740
_020B272C:
	cmp r9, r8
	movcc r8, r9
	mov r0, r6
	mov r1, r8, lsl #0xc
	bl FUN_020B1EC4
_020B2740:
	mov r0, #0x28
	mla r3, r4, r0, r11
	ldr r0, [sp, #0x8]
	str r0, [r3, #0x8]
	ldrsh r1, [r7, #0x2]
	ldrsh r2, [r7, #0x4]
	add r0, r3, #0xc
	bl FUN_020B1AB4
	add r0, r4, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r10, #0x0]
	mov r4, r0, lsr #0x10
	cmp r4, r1
	blo _020B267C
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,pc}
	arm_func_end FUN_020B24E0

