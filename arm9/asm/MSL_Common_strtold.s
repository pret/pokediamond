	.include "asm/macros.inc"
	.include "global.inc"

	.rodata

model$4434: ; 0x02104434
	.asciz "NAN("
	.size model$4434,.-model$4434

model$4439: ; 0x02104439
	.asciz "INFINITY"
	.size model$4439,.-model$4439

	.text

	arm_func_start __strtold
__strtold: ; 0x020E3310
	stmdb sp!, {r3-r11,lr}
	sub sp, sp, #0xa8
	ldr r4, [sp, #0xd0]
	mov r10, #0x0
	str r4, [sp, #0xd0]
	str r0, [sp, #0x0]
	add r6, sp, #0x80
	mov r9, r1
	mov r8, r2
	str r3, [sp, #0x4]
	mov r4, r10
	str r10, [sp, #0x2c]
	mov r5, #0x1
	mov r0, #0x4
_020E3348:
	strh r10, [r6, #0x0]
	strh r10, [r6, #0x2]
	strh r10, [r6, #0x4]
	strh r10, [r6, #0x6]
	add r6, r6, #0x8
	subs r0, r0, #0x1
	bne _020E3348
	mov r0, #0x0
	str r0, [sp, #0x28]
	strh r10, [r6, #0x0]
	strh r10, [r6, #0x2]
	ldr r2, [sp, #0x28]
	ldr r1, [sp, #0xd0]
	strh r10, [r6, #0x4]
	str r2, [r1, #0x0]
	mov r1, r2
	mov r0, r8
	str r1, [sp, #0x24]
	str r1, [sp, #0x20]
	str r1, [sp, #0x1c]
	str r1, [sp, #0x18]
	str r1, [sp, #0x10]
	str r1, [sp, #0xc]
	str r1, [sp, #0x8]
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	ldr r7, _020E42F0 ; =model$4439
	add r0, sp, #0x4d
	mov r6, #0x4
_020E33C0:
	ldrb r3, [r7, #0x0]
	ldrb r2, [r7, #0x1]
	add r7, r7, #0x2
	strb r3, [r0, #0x0]
	strb r2, [r0, #0x1]
	add r0, r0, #0x2
	subs r6, r6, #0x1
	bne _020E33C0
	ldrb r3, [r7, #0x0]
	ldr r2, _020E42F4 ; =model$4434
	strb r3, [r0, #0x0]
	ldrb r3, [r2, #0x1]
	ldrb r0, [r2, #0x2]
	ldrb r6, [r2, #0x0]
	strb r3, [sp, #0x31]
	strb r0, [sp, #0x32]
	ldrb r3, [r2, #0x3]
	ldrb r0, [r2, #0x4]
	strb r6, [sp, #0x30]
	strb r3, [sp, #0x33]
	strb r0, [sp, #0x34]
	b _020E4104
_020E3418:
	cmp r5, #0x100
	bgt _020E3490
	bge _020E3B98
	cmp r5, #0x20
	bgt _020E3474
	bge _020E3A6C
	cmp r5, #0x8
	bgt _020E3468
	cmp r5, #0x0
	addge pc, pc, r5, lsl #0x2
	b _020E4104
	b _020E4104 ; case 0
	b _020E34D4 ; case 1
	b _020E38B8 ; case 2
	b _020E4104 ; case 3
	b _020E3968 ; case 4
	b _020E4104 ; case 5
	b _020E4104 ; case 6
	b _020E4104 ; case 7
	b _020E3990 ; case 8
_020E3468:
	cmp r5, #0x10
	beq _020E3A34
	b _020E4104
_020E3474:
	cmp r5, #0x40
	bgt _020E3484
	beq _020E3AF8
	b _020E4104
_020E3484:
	cmp r5, #0x80
	beq _020E3B44
	b _020E4104
_020E3490:
	cmp r5, #0x2000
	bgt _020E34B8
	bge _020E36EC
	cmp r5, #0x200
	bgt _020E34AC
	beq _020E3BF8
	b _020E4104
_020E34AC:
	cmp r5, #0x400
	beq _020E3C20
	b _020E4104
_020E34B8:
	cmp r5, #0x4000
	bgt _020E34C8
	beq _020E35F4
	b _020E4104
_020E34C8:
	cmp r5, #0x8000
	beq _020E3C98
	b _020E4104
_020E34D4:
	cmp r1, #0x0
	blt _020E34E4
	cmp r1, #0x80
	blt _020E34EC
_020E34E4:
	mov r0, #0x0
	b _020E34FC
_020E34EC:
	mov r2, r1, lsl #0x1
	ldr r0, _020E42F8 ; =__msl_digit
	ldrh r0, [r0, r2]
	and r0, r0, #0x100
_020E34FC:
	cmp r0, #0x0
	beq _020E3528
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	blx r9
	mov r1, r0
	ldr r0, [sp, #0x2c]
	add r0, r0, #0x1
	str r0, [sp, #0x2c]
	b _020E4104
_020E3528:
	cmp r1, #0x0
	blt _020E3538
	cmp r1, #0x80
	blt _020E3540
_020E3538:
	mov r0, r1
	b _020E3548
_020E3540:
	ldr r0, _020E42FC ; =__upper_mapC
	ldrb r0, [r0, r1]
_020E3548:
	cmp r0, #0x49
	bgt _020E3574
	bge _020E35AC
	cmp r0, #0x2d
	bgt _020E35EC
	cmp r0, #0x2b
	blt _020E35EC
	beq _020E3588
	cmp r0, #0x2d
	beq _020E3580
	b _020E35EC
_020E3574:
	cmp r0, #0x4e
	beq _020E35CC
	b _020E35EC
_020E3580:
	mov r0, #0x1
	str r0, [sp, #0x28]
_020E3588:
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	mov r0, #0x1
	str r0, [sp, #0x18]
	b _020E4104
_020E35AC:
	add r4, r4, #0x1
	mov r0, r8
	mov r1, #0x0
	mov r2, r1
	blx r9
	mov r1, r0
	mov r5, #0x4000
	b _020E4104
_020E35CC:
	add r4, r4, #0x1
	mov r0, r8
	mov r1, #0x0
	mov r2, r1
	blx r9
	mov r1, r0
	mov r5, #0x2000
	b _020E4104
_020E35EC:
	mov r5, #0x2
	b _020E4104
_020E35F4:
	mov r5, #0x1
	add r7, sp, #0x4d
	add r0, sp, #0x76
	mov r6, #0x4
_020E3604:
	ldrb r3, [r7, #0x0]
	ldrb r2, [r7, #0x1]
	add r7, r7, #0x2
	strb r3, [r0, #0x0]
	strb r2, [r0, #0x1]
	add r0, r0, #0x2
	subs r6, r6, #0x1
	bne _020E3604
	ldrb r2, [r7, #0x0]
	add r6, sp, #0x77
	ldr r7, _020E42FC ; =__upper_mapC
	strb r2, [r0, #0x0]
	b _020E3658
_020E3638:
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	add r6, r6, #0x1
	add r5, r5, #0x1
	add r4, r4, #0x1
	blx r9
	mov r1, r0
_020E3658:
	cmp r5, #0x8
	bge _020E3688
	cmp r1, #0x0
	blt _020E3670
	cmp r1, #0x80
	blt _020E3678
_020E3670:
	mov r2, r1
	b _020E367C
_020E3678:
	ldrb r2, [r7, r1]
_020E367C:
	ldrsb r0, [r6, #0x0]
	cmp r0, r2
	beq _020E3638
_020E3688:
	cmp r5, #0x3
	cmpne r5, #0x8
	bne _020E36E4
	ldr r0, [sp, #0x28]
	cmp r0, #0x0
	beq _020E36B8
	ldr r1, _020E4300 ; =__float_huge
	mov r0, #0x0
	ldr r1, [r1, #0x0]
	bl _fsub
	bl _f2d
	b _020E36C4
_020E36B8:
	ldr r0, _020E4300 ; =__float_huge
	ldr r0, [r0, #0x0]
	bl _f2d
_020E36C4:
	ldr r2, [sp, #0x2c]
	add r3, r2, r5
	ldr r2, [sp, #0x18]
	add r3, r2, r3
	ldr r2, [sp, #0x4]
	add sp, sp, #0xa8
	str r3, [r2, #0x0]
	ldmia sp!, {r3-r11,pc}
_020E36E4:
	mov r5, #0x1000
	b _020E4104
_020E36EC:
	ldrb r3, [sp, #0x30]
	ldrb r0, [sp, #0x32]
	ldrb r2, [sp, #0x31]
	strb r3, [sp, #0x40]
	strb r0, [sp, #0x42]
	ldrb r3, [sp, #0x33]
	ldrb r0, [sp, #0x34]
	strb r2, [sp, #0x41]
	mov r5, #0x1
	strb r0, [sp, #0x44]
	mov r6, #0x0
	add r2, sp, #0x56
	strb r3, [sp, #0x43]
	mov r0, #0x8
_020E3724:
	strb r6, [r2, #0x0]
	strb r6, [r2, #0x1]
	strb r6, [r2, #0x2]
	strb r6, [r2, #0x3]
	add r2, r2, #0x4
	subs r0, r0, #0x1
	bne _020E3724
	add r7, sp, #0x41
	b _020E3768
_020E3748:
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	add r7, r7, #0x1
	add r5, r5, #0x1
	add r4, r4, #0x1
	blx r9
	mov r1, r0
_020E3768:
	cmp r5, #0x4
	bge _020E379C
	cmp r1, #0x0
	blt _020E3780
	cmp r1, #0x80
	blt _020E3788
_020E3780:
	mov r2, r1
	b _020E3790
_020E3788:
	ldr r0, _020E42FC ; =__upper_mapC
	ldrb r2, [r0, r1]
_020E3790:
	ldrsb r0, [r7, #0x0]
	cmp r0, r2
	beq _020E3748
_020E379C:
	sub r0, r5, #0x3
	cmp r0, #0x1
	bhi _020E38B0
	cmp r5, #0x4
	bne _020E3854
	ldr r7, _020E42F8 ; =__msl_digit
	b _020E37DC
_020E37B8:
	add r0, sp, #0x56
	strb r1, [r0, r6]
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	add r6, r6, #0x1
	add r4, r4, #0x1
	blx r9
	mov r1, r0
_020E37DC:
	cmp r6, #0x20
	bge _020E3844
	cmp r1, #0x0
	blt _020E37F4
	cmp r1, #0x80
	blt _020E37FC
_020E37F4:
	mov r0, #0x0
	b _020E3808
_020E37FC:
	mov r0, r1, lsl #0x1
	ldrh r0, [r7, r0]
	and r0, r0, #0x8
_020E3808:
	cmp r0, #0x0
	bne _020E37B8
	cmp r1, #0x0
	blt _020E3820
	cmp r1, #0x80
	blt _020E3828
_020E3820:
	mov r0, #0x0
	b _020E3834
_020E3828:
	mov r0, r1, lsl #0x1
	ldrh r0, [r7, r0]
	and r0, r0, #0x1
_020E3834:
	cmp r0, #0x0
	bne _020E37B8
	cmp r1, #0x2e
	beq _020E37B8
_020E3844:
	cmp r1, #0x29
	movne r5, #0x1000
	bne _020E4104
	add r6, r6, #0x1
_020E3854:
	add r0, sp, #0x56
	mov r1, #0x0
	strb r1, [r0, r6]
	ldr r1, [sp, #0x28]
	cmp r1, #0x0
	beq _020E3888
	bl nan
	mov r2, r0
	mov r0, #0x0
	mov r3, r1
	mov r1, r0
	bl _dsub
	b _020E388C
_020E3888:
	bl nan
_020E388C:
	ldr r2, [sp, #0x2c]
	add r2, r2, r5
	add r3, r6, r2
	ldr r2, [sp, #0x18]
	add r3, r2, r3
	ldr r2, [sp, #0x4]
	add sp, sp, #0xa8
	str r3, [r2, #0x0]
	ldmia sp!, {r3-r11,pc}
_020E38B0:
	mov r5, #0x1000
	b _020E4104
_020E38B8:
	cmp r1, #0x2e
	bne _020E38E0
	mov r5, #0x10
	add r4, r4, #0x1
	mov r0, r8
	mov r1, #0x0
	mov r2, r1
	blx r9
	mov r1, r0
	b _020E4104
_020E38E0:
	cmp r1, #0x0
	blt _020E38F0
	cmp r1, #0x80
	blt _020E38F8
_020E38F0:
	mov r0, #0x0
	b _020E3908
_020E38F8:
	mov r2, r1, lsl #0x1
	ldr r0, _020E42F8 ; =__msl_digit
	ldrh r0, [r0, r2]
	and r0, r0, #0x8
_020E3908:
	cmp r0, #0x0
	moveq r5, #0x1000
	beq _020E4104
	cmp r1, #0x30
	bne _020E3960
	add r4, r4, #0x1
	mov r0, r8
	mov r1, #0x0
	mov r2, r1
	blx r9
	cmp r0, #0x0
	mov r1, r0
	blt _020E394C
	cmp r0, #0x80
	bge _020E394C
	ldr r2, _020E42FC ; =__upper_mapC
	ldrb r0, [r2, r0]
_020E394C:
	cmp r0, #0x58
	moveq r5, #0x8000
	moveq r10, #0x1
	movne r5, #0x4
	b _020E4104
_020E3960:
	mov r5, #0x8
	b _020E4104
_020E3968:
	cmp r1, #0x30
	movne r5, #0x8
	bne _020E4104
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	b _020E4104
_020E3990:
	cmp r1, #0x0
	blt _020E39A0
	cmp r1, #0x80
	blt _020E39A8
_020E39A0:
	mov r0, #0x0
	b _020E39B8
_020E39A8:
	mov r2, r1, lsl #0x1
	ldr r0, _020E42F8 ; =__msl_digit
	ldrh r0, [r0, r2]
	and r0, r0, #0x8
_020E39B8:
	cmp r0, #0x0
	bne _020E39EC
	cmp r1, #0x2e
	movne r5, #0x40
	bne _020E4104
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	mov r5, #0x20
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	b _020E4104
_020E39EC:
	ldrb r2, [sp, #0x84]
	cmp r2, #0x14
	ldrcs r0, [sp, #0x1c]
	addcs r0, r0, #0x1
	strcs r0, [sp, #0x1c]
	bhs _020E3A18
	add r0, r2, #0x1
	strb r0, [sp, #0x84]
	add r0, sp, #0x80
	add r0, r0, r2
	strb r1, [r0, #0x5]
_020E3A18:
	add r4, r4, #0x1
	mov r0, r8
	mov r1, #0x0
	mov r2, r1
	blx r9
	mov r1, r0
	b _020E4104
_020E3A34:
	cmp r1, #0x0
	blt _020E3A44
	cmp r1, #0x80
	blt _020E3A4C
_020E3A44:
	mov r0, #0x0
	b _020E3A5C
_020E3A4C:
	mov r2, r1, lsl #0x1
	ldr r0, _020E42F8 ; =__msl_digit
	ldrh r0, [r0, r2]
	and r0, r0, #0x8
_020E3A5C:
	cmp r0, #0x0
	moveq r5, #0x1000
	movne r5, #0x20
	b _020E4104
_020E3A6C:
	cmp r1, #0x0
	blt _020E3A7C
	cmp r1, #0x80
	blt _020E3A84
_020E3A7C:
	mov r0, #0x0
	b _020E3A94
_020E3A84:
	mov r2, r1, lsl #0x1
	ldr r0, _020E42F8 ; =__msl_digit
	ldrh r0, [r0, r2]
	and r0, r0, #0x8
_020E3A94:
	cmp r0, #0x0
	moveq r5, #0x40
	beq _020E4104
	ldrb r3, [sp, #0x84]
	cmp r3, #0x14
	bhs _020E3ADC
	cmp r1, #0x30
	cmpeq r3, #0x0
	beq _020E3AD0
	ldrb r2, [sp, #0x84]
	add r0, sp, #0x80
	add r0, r0, r3
	add r2, r2, #0x1
	strb r2, [sp, #0x84]
	strb r1, [r0, #0x5]
_020E3AD0:
	ldr r0, [sp, #0x1c]
	sub r0, r0, #0x1
	str r0, [sp, #0x1c]
_020E3ADC:
	add r4, r4, #0x1
	mov r0, r8
	mov r1, #0x0
	mov r2, r1
	blx r9
	mov r1, r0
	b _020E4104
_020E3AF8:
	cmp r1, #0x0
	blt _020E3B08
	cmp r1, #0x80
	blt _020E3B10
_020E3B08:
	mov r0, r1
	b _020E3B18
_020E3B10:
	ldr r0, _020E42FC ; =__upper_mapC
	ldrb r0, [r0, r1]
_020E3B18:
	cmp r0, #0x45
	movne r5, #0x800
	bne _020E4104
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	mov r5, #0x80
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	b _020E4104
_020E3B44:
	cmp r1, #0x2b
	bne _020E3B68
	add r4, r4, #0x1
	mov r0, r8
	mov r1, #0x0
	mov r2, r1
	blx r9
	mov r1, r0
	b _020E3B90
_020E3B68:
	cmp r1, #0x2d
	bne _020E3B90
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	mov r0, #0x1
	str r0, [sp, #0x24]
_020E3B90:
	mov r5, #0x100
	b _020E4104
_020E3B98:
	cmp r1, #0x0
	blt _020E3BA8
	cmp r1, #0x80
	blt _020E3BB0
_020E3BA8:
	mov r0, #0x0
	b _020E3BC0
_020E3BB0:
	mov r2, r1, lsl #0x1
	ldr r0, _020E42F8 ; =__msl_digit
	ldrh r0, [r0, r2]
	and r0, r0, #0x8
_020E3BC0:
	cmp r0, #0x0
	moveq r5, #0x1000
	beq _020E4104
	cmp r1, #0x30
	movne r5, #0x400
	bne _020E4104
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	mov r5, #0x200
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	b _020E4104
_020E3BF8:
	cmp r1, #0x30
	movne r5, #0x400
	bne _020E4104
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	b _020E4104
_020E3C20:
	cmp r1, #0x0
	blt _020E3C30
	cmp r1, #0x80
	blt _020E3C38
_020E3C30:
	mov r0, #0x0
	b _020E3C48
_020E3C38:
	mov r2, r1, lsl #0x1
	ldr r0, _020E42F8 ; =__msl_digit
	ldrh r0, [r0, r2]
	and r0, r0, #0x8
_020E3C48:
	cmp r0, #0x0
	moveq r5, #0x800
	beq _020E4104
	ldr r0, [sp, #0x20]
	sub r2, r1, #0x30
	mov r1, #0xa
	mla r0, r1, r0, r2
	ldr r1, _020E4304 ; =0x00007FFF
	str r0, [sp, #0x20]
	cmp r0, r1
	ldrgt r0, [sp, #0xd0]
	movgt r1, #0x1
	strgt r1, [r0, #0x0]
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	b _020E4104
_020E3C98:
	cmp r10, #0x20
	bgt _020E3CE8
	bge _020E3FBC
	cmp r10, #0x8
	bgt _020E3CDC
	cmp r10, #0x0
	addge pc, pc, r10, lsl #0x2
	b _020E4104
	b _020E4104 ; case 0
	b _020E3D0C ; case 1
	b _020E3D5C ; case 2
	b _020E4104 ; case 3
	b _020E3D84 ; case 4
	b _020E4104 ; case 5
	b _020E4104 ; case 6
	b _020E4104 ; case 7
	b _020E3E94 ; case 8
_020E3CDC:
	cmp r10, #0x10
	beq _020E3F70
	b _020E4104
_020E3CE8:
	cmp r10, #0x80
	bgt _020E3D00
	bge _020E4064
	cmp r10, #0x40
	beq _020E4004
	b _020E4104
_020E3D00:
	cmp r10, #0x100
	beq _020E408C
	b _020E4104
_020E3D0C:
	mov r1, #0x0
	add r0, sp, #0x45
	str r0, [sp, #0x14]
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	strb r1, [r0, #0x4]
	strb r1, [r0, #0x5]
	strb r1, [r0, #0x6]
	strb r1, [r0, #0x7]
	mov r0, r8
	mov r2, r1
	str r1, [sp, #0x8]
	mov r11, r1
	mov r10, #0x2
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	b _020E4104
_020E3D5C:
	cmp r1, #0x30
	movne r10, #0x4
	bne _020E4104
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	b _020E4104
_020E3D84:
	cmp r1, #0x0
	blt _020E3D94
	cmp r1, #0x80
	blt _020E3D9C
_020E3D94:
	mov r0, #0x0
	b _020E3DAC
_020E3D9C:
	mov r2, r1, lsl #0x1
	ldr r0, _020E42F8 ; =__msl_digit
	ldrh r0, [r0, r2]
	and r0, r0, #0x400
_020E3DAC:
	cmp r0, #0x0
	bne _020E3DE0
	cmp r1, #0x2e
	movne r10, #0x10
	bne _020E4104
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	mov r10, #0x8
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	b _020E4104
_020E3DE0:
	ldr r2, [sp, #0x8]
	mov r0, #0xe
	cmp r2, r0
	bhs _020E3E78
	mov r0, r2
	add r0, r0, #0x1
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x14]
	add r2, r11, r11, lsr #0x1f
	cmp r1, #0x0
	ldrb r0, [r0, r2, asr #0x1]
	blt _020E3E20
	cmp r1, #0x80
	bge _020E3E20
	ldr r2, _020E42FC ; =__upper_mapC
	ldrb r1, [r2, r1]
_020E3E20:
	cmp r1, #0x41
	subge r1, r1, #0x37
	sublt r1, r1, #0x30
	mov r2, r11, lsr #0x1f
	and r3, r1, #0xff
	rsb r1, r2, r11, lsl #0x1f
	adds r1, r2, r1, ror #0x1f
	moveq r1, r3, lsl #0x4
	add r2, r11, r11, lsr #0x1f
	orrne r0, r0, r3
	andeq r1, r1, #0xff
	orreq r0, r0, r1
	ldr r1, [sp, #0x14]
	add r11, r11, #0x1
	strb r0, [r1, r2, asr #0x1]
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	b _020E4104
_020E3E78:
	add r4, r4, #0x1
	mov r0, r8
	mov r1, #0x0
	mov r2, r1
	blx r9
	mov r1, r0
	b _020E4104
_020E3E94:
	cmp r1, #0x0
	blt _020E3EA4
	cmp r1, #0x80
	blt _020E3EAC
_020E3EA4:
	mov r0, #0x0
	b _020E3EBC
_020E3EAC:
	mov r2, r1, lsl #0x1
	ldr r0, _020E42F8 ; =__msl_digit
	ldrh r0, [r0, r2]
	and r0, r0, #0x400
_020E3EBC:
	cmp r0, #0x0
	moveq r10, #0x10
	beq _020E4104
	ldr r2, [sp, #0x8]
	mov r0, #0xe
	cmp r2, r0
	bhs _020E3F54
	ldr r0, [sp, #0x14]
	add r2, r11, r11, lsr #0x1f
	cmp r1, #0x0
	ldrb r0, [r0, r2, asr #0x1]
	blt _020E3EFC
	cmp r1, #0x80
	bge _020E3EFC
	ldr r2, _020E42FC ; =__upper_mapC
	ldrb r1, [r2, r1]
_020E3EFC:
	cmp r1, #0x41
	subge r1, r1, #0x37
	sublt r1, r1, #0x30
	mov r2, r11, lsr #0x1f
	and r3, r1, #0xff
	rsb r1, r2, r11, lsl #0x1f
	adds r1, r2, r1, ror #0x1f
	moveq r1, r3, lsl #0x4
	add r2, r11, r11, lsr #0x1f
	orrne r0, r0, r3
	andeq r1, r1, #0xff
	orreq r0, r0, r1
	ldr r1, [sp, #0x14]
	add r11, r11, #0x1
	strb r0, [r1, r2, asr #0x1]
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	b _020E4104
_020E3F54:
	add r4, r4, #0x1
	mov r0, r8
	mov r1, #0x0
	mov r2, r1
	blx r9
	mov r1, r0
	b _020E4104
_020E3F70:
	cmp r1, #0x0
	blt _020E3F80
	cmp r1, #0x80
	blt _020E3F88
_020E3F80:
	mov r0, r1
	b _020E3F90
_020E3F88:
	ldr r0, _020E42FC ; =__upper_mapC
	ldrb r0, [r0, r1]
_020E3F90:
	cmp r0, #0x50
	movne r5, #0x800
	bne _020E4104
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	mov r10, #0x20
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	b _020E4104
_020E3FBC:
	cmp r1, #0x2d
	moveq r0, #0x1
	streq r0, [sp, #0xc]
	beq _020E3FE4
	cmp r1, #0x2b
	beq _020E3FE4
	mov r0, r8
	mov r2, #0x1
	blx r9
	sub r4, r4, #0x1
_020E3FE4:
	mov r10, #0x40
	add r4, r4, #0x1
	mov r0, r8
	mov r1, #0x0
	mov r2, r1
	blx r9
	mov r1, r0
	b _020E4104
_020E4004:
	cmp r1, #0x0
	blt _020E4014
	cmp r1, #0x80
	blt _020E401C
_020E4014:
	mov r0, #0x0
	b _020E402C
_020E401C:
	mov r2, r1, lsl #0x1
	ldr r0, _020E42F8 ; =__msl_digit
	ldrh r0, [r0, r2]
	and r0, r0, #0x8
_020E402C:
	cmp r0, #0x0
	moveq r5, #0x1000
	beq _020E4104
	cmp r1, #0x30
	movne r10, #0x100
	bne _020E4104
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	mov r10, #0x80
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	b _020E4104
_020E4064:
	cmp r1, #0x30
	movne r10, #0x100
	bne _020E4104
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	add r4, r4, #0x1
	blx r9
	mov r1, r0
	b _020E4104
_020E408C:
	cmp r1, #0x0
	blt _020E409C
	cmp r1, #0x80
	blt _020E40A4
_020E409C:
	mov r0, #0x0
	b _020E40B4
_020E40A4:
	mov r2, r1, lsl #0x1
	ldr r0, _020E42F8 ; =__msl_digit
	ldrh r0, [r0, r2]
	and r0, r0, #0x8
_020E40B4:
	cmp r0, #0x0
	moveq r5, #0x800
	beq _020E4104
	ldr r0, [sp, #0x10]
	sub r2, r1, #0x30
	mov r1, #0xa
	mla r0, r1, r0, r2
	str r0, [sp, #0x10]
	ldr r1, _020E4304 ; =0x00007FFF
	ldr r0, [sp, #0x20]
	add r4, r4, #0x1
	cmp r0, r1
	ldrgt r0, [sp, #0xd0]
	movgt r1, #0x1
	strgt r1, [r0, #0x0]
	mov r1, #0x0
	mov r0, r8
	mov r2, r1
	blx r9
	mov r1, r0
_020E4104:
	ldr r0, [sp, #0x0]
	cmp r4, r0
	bgt _020E4124
	mvn r0, #0x0
	cmp r1, r0
	beq _020E4124
	tst r5, #0x1800
	beq _020E3418
_020E4124:
	cmp r5, #0x8000
	beq _020E4140
	ldr r0, _020E4308 ; =0x00000E2C
	tst r5, r0
	moveq r0, #0x1
	movne r0, #0x0
	b _020E4164
_020E4140:
	sub r0, r4, #0x1
	cmp r0, #0x2
	ble _020E4158
	ldr r0, _020E430C ; =0x0000018E
	tst r10, r0
	bne _020E4160
_020E4158:
	mov r0, #0x1
	b _020E4164
_020E4160:
	mov r0, #0x0
_020E4164:
	cmp r0, #0x0
	movne r2, #0x0
	ldrne r0, [sp, #0x4]
	bne _020E4184
	ldr r0, [sp, #0x2c]
	sub r2, r4, #0x1
	add r2, r2, r0
	ldr r0, [sp, #0x4]
_020E4184:
	str r2, [r0, #0x0]
	mov r0, r8
	mov r2, #0x1
	blx r9
	cmp r10, #0x0
	bne _020E4388
	ldr r0, [sp, #0x24]
	ldrb r2, [sp, #0x84]
	cmp r0, #0x0
	ldrne r0, [sp, #0x20]
	rsbne r0, r0, #0x0
	strne r0, [sp, #0x20]
	add r0, sp, #0x85
	add r1, r0, r2
	b _020E41CC
_020E41C0:
	ldr r0, [sp, #0x1c]
	add r0, r0, #0x1
	str r0, [sp, #0x1c]
_020E41CC:
	cmp r2, #0x0
	sub r2, r2, #0x1
	beq _020E41E4
	ldrb r0, [r1, #-0x1]!
	cmp r0, #0x30
	beq _020E41C0
_020E41E4:
	add r0, r2, #0x1
	strb r0, [sp, #0x84]
	ands r2, r0, #0xff
	bne _020E4208
	add r1, r2, #0x1
	strb r1, [sp, #0x84]
	add r0, sp, #0x85
	mov r1, #0x30
	strb r1, [r0, r2]
_020E4208:
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	mov r2, #0x8000
	add r0, r1, r0
	rsb r2, r2, #0x0
	str r0, [sp, #0x20]
	cmp r0, r2
	blt _020E4230
	cmp r0, r2, lsr #0x11
	ble _020E423C
_020E4230:
	ldr r0, [sp, #0xd0]
	mov r1, #0x1
	str r1, [r0, #0x0]
_020E423C:
	ldr r0, [sp, #0xd0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020E4298
	ldr r0, [sp, #0x24]
	cmp r0, #0x0
	movne r0, #0x0
	addne sp, sp, #0xa8
	movne r1, r0
	ldmneia sp!, {r3-r11,pc}
	ldr r0, [sp, #0x28]
	cmp r0, #0x0
	ldreq r1, _020E4310 ; =__double_huge
	addeq sp, sp, #0xa8
	ldmeqia r1, {r0-r1}
	ldmeqia sp!, {r3-r11,pc}
	ldr r1, _020E4310 ; =__double_huge
	mov r0, #0x0
	ldmia r1, {r2-r3}
	mov r1, r0
	bl _dsub
	add sp, sp, #0xa8
	ldmia sp!, {r3-r11,pc}
_020E4298:
	ldr r1, [sp, #0x20]
	add r0, sp, #0x80
	strh r1, [sp, #0x82]
	bl __dec2num
	mov r4, r0
	mov r6, r1
	mov r0, #0x0
	mov r1, r0
	mov r2, r4
	mov r3, r6
	bl _dneq
	beq _020E4318
	mov r0, r4
	mov r1, r6
	mov r2, #0x0
	mov r3, #0x100000
	bl _dls
	bhs _020E4318
	ldr r0, [sp, #0xd0]
	mov r1, #0x1
	str r1, [r0, #0x0]
	b _020E4344
	.balign 4
_020E42F0: .word model$4439
_020E42F4: .word model$4434
_020E42F8: .word __msl_digit
_020E42FC: .word __upper_mapC
_020E4300: .word __float_huge
_020E4304: .word 0x00007FFF
_020E4308: .word 0x00000E2C
_020E430C: .word 0x0000018E
_020E4310: .word __double_huge
_020E4314: .word 0x7FEFFFFF
_020E4318:
	ldr r3, _020E4314 ; =0x7FEFFFFF
	mov r0, r4
	mov r1, r6
	mvn r2, #0x0
	bl _dgr
	bls _020E4344
	ldr r0, [sp, #0xd0]
	mov r2, #0x1
	ldr r1, _020E4310 ; =__double_huge
	str r2, [r0, #0x0]
	ldmia r1, {r4,r6}
_020E4344:
	ldr r0, [sp, #0x28]
	cmp r0, #0x0
	beq _020E4378
	ldr r0, _020E4308 ; =0x00000E2C
	tst r5, r0
	beq _020E4378
	mov r0, #0x0
	mov r1, r0
	mov r2, r4
	mov r3, r6
	bl _dsub
	mov r4, r0
	mov r6, r1
_020E4378:
	add sp, sp, #0xa8
	mov r0, r4
	mov r1, r6
	ldmia sp!, {r3-r11,pc}
_020E4388:
	ldr r0, [sp, #0xc]
	add r4, sp, #0x38
	cmp r0, #0x0
	ldrne r0, [sp, #0x10]
	ldrb r3, [sp, #0x45]
	rsbne r0, r0, #0x0
	strne r0, [sp, #0x10]
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #0x8]
	mov r2, #0x0
	add r0, r1, r0, lsl #0x2
	str r0, [sp, #0x10]
	mov r1, #0x80
	b _020E43D0
_020E43C0:
	ldr r0, [sp, #0x10]
	add r2, r2, #0x1
	sub r0, r0, #0x1
	str r0, [sp, #0x10]
_020E43D0:
	cmp r2, #0x4
	bhs _020E43E0
	tst r3, r1, asr r2
	beq _020E43C0
_020E43E0:
	adds r5, r2, #0x1
	beq _020E442C
	add r0, sp, #0x4c
	add r3, sp, #0x45
	str r0, [sp, #0x14]
	mov r1, #0x0
	cmp r0, r3
	blo _020E442C
	rsb r6, r5, #0x8
_020E4404:
	ldr r0, [sp, #0x14]
	ldrb r0, [r0, #0x0]
	orr r2, r1, r0, lsl r5
	mov r1, r0, asr r6
	ldr r0, [sp, #0x14]
	and r1, r1, #0xff
	strb r2, [r0], #-0x1
	str r0, [sp, #0x14]
	cmp r0, r3
	bhs _020E4404
_020E442C:
	mov r2, #0x0
	mov r6, r2
	strb r2, [r4, #0x0]
	strb r2, [r4, #0x1]
	strb r2, [r4, #0x2]
	strb r2, [r4, #0x3]
	strb r2, [r4, #0x4]
	strb r2, [r4, #0x5]
	strb r2, [r4, #0x6]
	strb r2, [r4, #0x7]
	mov r3, #0xc
	mov r7, #0x1
	mov r0, #0xff
	add r1, sp, #0x45
_020E4464:
	add r5, r2, #0x8
	cmp r5, #0x34
	ldrb r5, [r1, r6]
	rsbhi r8, r2, #0x34
	and r11, r3, #0x7
	andhi r5, r5, r0, lsl r8
	andhi r5, r5, #0xff
	mov r8, r5, asr r11
	and r9, r8, #0xff
	ldrb r10, [r4, r7]
	rsb r8, r11, #0x8
	mov r5, r5, lsl r8
	orr r9, r10, r9
	strb r9, [r4, r7]
	add r7, r7, #0x1
	add r2, r2, #0x8
	ldrb r8, [r4, r7]
	and r5, r5, #0xff
	cmp r2, #0x34
	orr r5, r8, r5
	strb r5, [r4, r7]
	add r3, r3, #0x8
	add r6, r6, #0x1
	blo _020E4464
	ldr r0, [sp, #0x10]
	mov r1, #0x800
	add r0, r0, #0xfe
	add r2, r0, #0x300
	rsb r1, r1, #0x0
	tst r2, r1
	beq _020E44FC
	ldr r2, [sp, #0xd0]
	mov r3, #0x1
	mov r0, #0x0
	add sp, sp, #0xa8
	mov r1, r0
	str r3, [r2, #0x0]
	ldmia sp!, {r3-r11,pc}
_020E44FC:
	ldrb r0, [r4, #0x1]
	mov r2, r2, lsl #0x15
	ldrb r1, [r4, #0x0]
	orr r0, r0, r2, lsr #0x11
	strb r0, [r4, #0x1]
	ldr r0, [sp, #0x28]
	orr r1, r1, r2, lsr #0x19
	cmp r0, #0x0
	andne r0, r1, #0xff
	strb r1, [r4, #0x0]
	orrne r0, r0, #0x80
	strneb r0, [r4, #0x0]
	mov r3, #0x0
_020E4530:
	rsb r1, r3, #0x7
	ldrb r2, [r4, r3]
	ldrb r0, [r4, r1]
	strb r0, [r4, r3]
	add r3, r3, #0x1
	strb r2, [r4, r1]
	cmp r3, #0x4
	blt _020E4530
	ldmia r4, {r0-r1}
	add sp, sp, #0xa8
	ldmia sp!, {r3-r11,pc}
	arm_func_end __strtold

	arm_func_start strtold
strtold: ; 0x020E455C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov r7, r0
	mov r0, #0x0
	mov r6, r1
	str r0, [sp, #0x8]
	add r4, sp, #0xc
	str r7, [sp, #0x4]
	ldr r1, _020E4630 ; =__StringRead
	add r2, sp, #0x4
	add r3, sp, #0x10
	sub r0, r0, #0x80000001
	str r4, [sp, #0x0]
	bl __strtold
	mov r5, r1
	mov r4, r0
	cmp r6, #0x0
	ldrne r0, [sp, #0x10]
	mov r1, r5
	addne r0, r7, r0
	strne r0, [r6, #0x0]
	mov r0, r4
	bl fabs
	ldr r2, [sp, #0xc]
	mov r6, r0
	mov r7, r1
	cmp r2, #0x0
	bne _020E4614
	mov r0, #0x0
	mov r1, r0
	mov r2, r4
	mov r3, r5
	bl _dneq
	beq _020E4620
	mov r0, r6
	mov r1, r7
	mov r2, #0x0
	mov r3, #0x100000
	bl _dls
	blo _020E4614
	ldr r3, _020E4634 ; =0x7FEFFFFF
	mov r0, r6
	mov r1, r7
	mvn r2, #0x0
	bl _dgr
	bls _020E4620
_020E4614:
	ldr r0, _020E4638 ; =errno
	mov r1, #0x22
	str r1, [r0, #0x0]
_020E4620:
	mov r0, r4
	mov r1, r5
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020E4630: .word __StringRead
_020E4634: .word 0x7FEFFFFF
_020E4638: .word errno
	arm_func_end strtold

	arm_func_start atod
atod: ; 0x020E463C
	ldr ip, _020E4648 ; =strtold
	mov r1, #0x0
	bx r12
	.balign 4
_020E4648: .word strtold
	arm_func_end atod

	.section .exceptix,4

	.word __strtold
	.short 4684
	.word UNK_020EC720
	.word strtold
	.short 225
	.word 0x00500F00
	.word atod
	.short 17
	.word 0x00000000

	.section .exception,8

UNK_020EC720: ; 0x020EC720
	.byte 0x00, 0xFF, 0x01, 0xD0
	.balign 8
