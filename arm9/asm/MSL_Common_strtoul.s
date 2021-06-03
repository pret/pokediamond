	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start __strtoul
__strtoul:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	ldr r4, [sp, #0x38]
	movs r9, r0
	ldr r0, [sp, #0x34]
	str r4, [sp, #0x38]
	mov r4, #0x0
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x38]
	str r1, [sp, #0x0]
	str r4, [r0, #0x0]
	mov r0, r4
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x34]
	mov r1, r4
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x30]
	str r4, [sp, #0x8]
	mov r8, r2
	mov r7, r3
	mov r5, r4
	mov r10, r4
	str r0, [sp, #0x30]
	mov r4, #0x1
	bmi _020E46CC
	cmp r9, #0x1
	beq _020E46CC
	cmp r9, #0x24
	bgt _020E46CC
	ldr r0, [sp, #0x0]
	cmp r0, #0x1
	bge _020E46D4
_020E46CC:
	mov r4, #0x40
	b _020E46F0
_020E46D4:
	ldr r1, [sp, #0x8]
	mov r0, r7
	mov r3, r1
	mov r2, r1
	add r5, r3, #0x1
	blx r8
	mov r6, r0
_020E46F0:
	cmp r9, #0x0
	beq _020E4708
	mov r1, r9
	mvn r0, #0x0
	bl _u32_div_f
	str r0, [sp, #0x4]
_020E4708:
	mvn r11, #0x0
	b _020E49C8
_020E4710:
	cmp r4, #0x8
	bgt _020E4748
	cmp r4, #0x0
	addge pc, pc, r4, lsl #0x2
	b _020E49C8
	b _020E49C8
	b _020E4754
	b _020E4800
	b _020E49C8
	b _020E483C
	b _020E49C8
	b _020E49C8
	b _020E49C8
	b _020E487C
_020E4748:
	cmp r4, #0x10
	beq _020E487C
	b _020E49C8
_020E4754:
	cmp r6, #0x0
	blt _020E4764
	cmp r6, #0x80
	blt _020E476C
_020E4764:
	mov r0, #0x0
	b _020E477C
_020E476C:
	ldr r0, _020E4A2C ; =__msl_digit
	mov r1, r6, lsl #0x1
	ldrh r0, [r0, r1]
	and r0, r0, #0x100
_020E477C:
	cmp r0, #0x0
	beq _020E47A8
	mov r1, #0x0
	mov r0, r7
	mov r2, r1
	blx r8
	mov r6, r0
	ldr r0, [sp, #0x8]
	add r0, r0, #0x1
	str r0, [sp, #0x8]
	b _020E49C8
_020E47A8:
	cmp r6, #0x2b
	bne _020E47CC
	mov r1, #0x0
	mov r0, r7
	mov r2, r1
	add r5, r5, #0x1
	blx r8
	mov r6, r0
	b _020E47F8
_020E47CC:
	cmp r6, #0x2d
	bne _020E47F8
	mov r1, #0x0
	mov r0, r7
	mov r2, r1
	add r5, r5, #0x1
	blx r8
	mov r6, r0
	ldr r0, [sp, #0x34]
	mov r1, #0x1
	str r1, [r0, #0x0]
_020E47F8:
	mov r4, #0x2
	b _020E49C8
_020E4800:
	cmp r9, #0x0
	cmpne r9, #0x10
	bne _020E4834
	cmp r6, #0x30
	bne _020E4834
	mov r1, #0x0
	mov r0, r7
	mov r2, r1
	mov r4, #0x4
	add r5, r5, #0x1
	blx r8
	mov r6, r0
	b _020E49C8
_020E4834:
	mov r4, #0x8
	b _020E49C8
_020E483C:
	cmp r6, #0x58
	cmpne r6, #0x78
	bne _020E486C
	mov r1, #0x0
	mov r0, r7
	mov r2, r1
	mov r9, #0x10
	mov r4, #0x8
	add r5, r5, #0x1
	blx r8
	mov r6, r0
	b _020E49C8
_020E486C:
	cmp r9, #0x0
	moveq r9, #0x8
	mov r4, #0x10
	b _020E49C8
_020E487C:
	ldr r0, [sp, #0x4]
	cmp r9, #0x0
	moveq r9, #0xa
	cmp r0, #0x0
	bne _020E48A0
	mov r0, r11
	mov r1, r9
	bl _u32_div_f
	str r0, [sp, #0x4]
_020E48A0:
	cmp r6, #0x0
	blt _020E48B0
	cmp r6, #0x80
	blt _020E48B8
_020E48B0:
	mov r0, #0x0
	b _020E48C8
_020E48B8:
	ldr r0, _020E4A2C ; =__msl_digit
	mov r1, r6, lsl #0x1
	ldrh r0, [r0, r1]
	and r0, r0, #0x8
_020E48C8:
	cmp r0, #0x0
	beq _020E48F0
	sub r6, r6, #0x30
	cmp r6, r9
	blt _020E4978
	cmp r4, #0x10
	moveq r4, #0x20
	movne r4, #0x40
	add r6, r6, #0x30
	b _020E49C8
_020E48F0:
	cmp r6, #0x0
	blt _020E4900
	cmp r6, #0x80
	blt _020E4908
_020E4900:
	mov r0, #0x0
	b _020E4918
_020E4908:
	ldr r0, _020E4A2C ; =__msl_digit
	mov r1, r6, lsl #0x1
	ldrh r0, [r0, r1]
	and r0, r0, #0x1
_020E4918:
	cmp r0, #0x0
	beq _020E494C
	cmp r6, #0x0
	blt _020E4930
	cmp r6, #0x80
	blt _020E4938
_020E4930:
	mov r0, r6
	b _020E4940
_020E4938:
	ldr r0, _020E4A30 ; =__upper_mapC
	ldrb r0, [r0, r6]
_020E4940:
	sub r0, r0, #0x37
	cmp r0, r9
	blt _020E495C
_020E494C:
	cmp r4, #0x10
	moveq r4, #0x20
	movne r4, #0x40
	b _020E49C8
_020E495C:
	cmp r6, #0x0
	blt _020E4974
	cmp r6, #0x80
	bge _020E4974
	ldr r0, _020E4A30 ; =__upper_mapC
	ldrb r6, [r0, r6]
_020E4974:
	sub r6, r6, #0x37
_020E4978:
	ldr r0, [sp, #0x4]
	mov r4, #0x10
	cmp r10, r0
	ldrhi r0, [sp, #0x38]
	movhi r1, #0x1
	strhi r1, [r0, #0x0]
	mul r0, r10, r9
	mov r10, r0
	sub r0, r11, r0
	cmp r6, r0
	ldrhi r0, [sp, #0x38]
	movhi r1, #0x1
	strhi r1, [r0, #0x0]
	mov r1, #0x0
	mov r0, r7
	mov r2, r1
	add r10, r10, r6
	add r5, r5, #0x1
	blx r8
	mov r6, r0
_020E49C8:
	ldr r0, [sp, #0x0]
	cmp r5, r0
	bgt _020E49E4
	cmp r6, r11
	beq _020E49E4
	tst r4, #0x60
	beq _020E4710
_020E49E4:
	tst r4, #0x34
	bne _020E49FC
	ldr r0, [sp, #0x30]
	mov r10, #0x0
	str r10, [r0, #0x0]
	b _020E4A10
_020E49FC:
	ldr r0, [sp, #0x8]
	sub r1, r5, #0x1
	add r1, r1, r0
	ldr r0, [sp, #0x30]
	str r1, [r0, #0x0]
_020E4A10:
	mov r0, r7
	mov r1, r6
	mov r2, #0x1
	blx r8
	mov r0, r10
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020E4A2C: .word __msl_digit
_020E4A30: .word __upper_mapC
    arm_func_end __strtoul

	arm_func_start __strtoull
__strtoull: ; 0x020E4A34
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x1c
	ldr r4, [sp, #0x48]
	movs r9, r0
	ldr r0, [sp, #0x44]
	str r4, [sp, #0x48]
	mov r4, #0x0
	str r0, [sp, #0x44]
	ldr r0, [sp, #0x48]
	str r1, [sp, #0x0]
	str r4, [r0, #0x0]
	mov r0, r4
	str r0, [sp, #0xc]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x44]
	mov r1, r4
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x40]
	str r4, [sp, #0x14]
	mov r8, r2
	mov r7, r3
	mov r5, r4
	mov r10, r4
	mov r11, r4
	str r0, [sp, #0x40]
	mov r4, #0x1
	bmi _020E4ABC
	cmp r9, #0x1
	beq _020E4ABC
	cmp r9, #0x24
	bgt _020E4ABC
	ldr r0, [sp, #0x0]
	cmp r0, #0x1
	bge _020E4AC4
_020E4ABC:
	mov r4, #0x40
	b _020E4ADC
_020E4AC4:
	ldr r1, [sp, #0x14]
	mov r0, r7
	mov r2, r1
	add r5, r1, #0x1
	blx r8
	mov r6, r0
_020E4ADC:
	cmp r9, #0x0
	beq _020E4B00
	mvn r0, #0x0
	mov r1, r0
	mov r3, r9, asr #0x1f
	mov r2, r9
	bl _ll_udiv
	str r0, [sp, #0xc]
	str r1, [sp, #0x8]
_020E4B00:
	mvn r0, #0x0
	str r0, [sp, #0x18]
	b _020E4E08
_020E4B0C:
	cmp r4, #0x8
	bgt _020E4B44
	cmp r4, #0x0
	addge pc, pc, r4, lsl #0x2
	b _020E4E08
	b _020E4E08
	b _020E4B50
	b _020E4BFC
	b _020E4E08
	b _020E4C38
	b _020E4E08
	b _020E4E08
	b _020E4E08
	b _020E4C78
_020E4B44:
	cmp r4, #0x10
	beq _020E4C78
	b _020E4E08
_020E4B50:
	cmp r6, #0x0
	blt _020E4B60
	cmp r6, #0x80
	blt _020E4B68
_020E4B60:
	mov r0, #0x0
	b _020E4B78
_020E4B68:
	ldr r0, _020E4E78 ; =__msl_digit
	mov r1, r6, lsl #0x1
	ldrh r0, [r0, r1]
	and r0, r0, #0x100
_020E4B78:
	cmp r0, #0x0
	beq _020E4BA4
	mov r1, #0x0
	mov r0, r7
	mov r2, r1
	blx r8
	mov r6, r0
	ldr r0, [sp, #0x14]
	add r0, r0, #0x1
	str r0, [sp, #0x14]
	b _020E4E08
_020E4BA4:
	cmp r6, #0x2b
	bne _020E4BC8
	mov r1, #0x0
	mov r0, r7
	mov r2, r1
	add r5, r5, #0x1
	blx r8
	mov r6, r0
	b _020E4BF4
_020E4BC8:
	cmp r6, #0x2d
	bne _020E4BF4
	mov r1, #0x0
	mov r0, r7
	mov r2, r1
	add r5, r5, #0x1
	blx r8
	mov r6, r0
	ldr r0, [sp, #0x44]
	mov r1, #0x1
	str r1, [r0, #0x0]
_020E4BF4:
	mov r4, #0x2
	b _020E4E08
_020E4BFC:
	cmp r9, #0x0
	cmpne r9, #0x10
	bne _020E4C30
	cmp r6, #0x30
	bne _020E4C30
	mov r1, #0x0
	mov r0, r7
	mov r2, r1
	mov r4, #0x4
	add r5, r5, #0x1
	blx r8
	mov r6, r0
	b _020E4E08
_020E4C30:
	mov r4, #0x8
	b _020E4E08
_020E4C38:
	cmp r6, #0x58
	cmpne r6, #0x78
	bne _020E4C68
	mov r1, #0x0
	mov r0, r7
	mov r2, r1
	mov r9, #0x10
	mov r4, #0x8
	add r5, r5, #0x1
	blx r8
	mov r6, r0
	b _020E4E08
_020E4C68:
	cmp r9, #0x0
	moveq r9, #0x8
	mov r4, #0x10
	b _020E4E08
_020E4C78:
	ldr r1, [sp, #0x8]
	mov r0, #0x0
	cmp r9, #0x0
	moveq r9, #0xa
	cmp r1, r0
	ldr r1, [sp, #0xc]
	cmpeq r1, r0
	bne _020E4CB4
	ldr r0, [sp, #0x18]
	mov r3, r9, asr #0x1f
	mov r1, r0
	mov r2, r9
	bl _ll_udiv
	str r0, [sp, #0xc]
	str r1, [sp, #0x8]
_020E4CB4:
	cmp r6, #0x0
	blt _020E4CC4
	cmp r6, #0x80
	blt _020E4CCC
_020E4CC4:
	mov r0, #0x0
	b _020E4CDC
_020E4CCC:
	ldr r0, _020E4E78 ; =__msl_digit
	mov r1, r6, lsl #0x1
	ldrh r0, [r0, r1]
	and r0, r0, #0x8
_020E4CDC:
	cmp r0, #0x0
	beq _020E4D04
	sub r6, r6, #0x30
	cmp r6, r9
	blt _020E4D8C
	cmp r4, #0x10
	moveq r4, #0x20
	movne r4, #0x40
	add r6, r6, #0x30
	b _020E4E08
_020E4D04:
	cmp r6, #0x0
	blt _020E4D14
	cmp r6, #0x80
	blt _020E4D1C
_020E4D14:
	mov r0, #0x0
	b _020E4D2C
_020E4D1C:
	ldr r0, _020E4E78 ; =__msl_digit
	mov r1, r6, lsl #0x1
	ldrh r0, [r0, r1]
	and r0, r0, #0x1
_020E4D2C:
	cmp r0, #0x0
	beq _020E4D60
	cmp r6, #0x0
	blt _020E4D44
	cmp r6, #0x80
	blt _020E4D4C
_020E4D44:
	mov r0, r6
	b _020E4D54
_020E4D4C:
	ldr r0, _020E4E7C ; =__upper_mapC
	ldrb r0, [r0, r6]
_020E4D54:
	sub r0, r0, #0x37
	cmp r0, r9
	blt _020E4D70
_020E4D60:
	cmp r4, #0x10
	moveq r4, #0x20
	movne r4, #0x40
	b _020E4E08
_020E4D70:
	cmp r6, #0x0
	blt _020E4D88
	cmp r6, #0x80
	bge _020E4D88
	ldr r0, _020E4E7C ; =__upper_mapC
	ldrb r6, [r0, r6]
_020E4D88:
	sub r6, r6, #0x37
_020E4D8C:
	ldr r0, [sp, #0x8]
	umull r2, r3, r10, r9
	cmp r11, r0
	ldr r0, [sp, #0xc]
	mov r4, #0x10
	cmpeq r10, r0
	ldrhi r0, [sp, #0x48]
	movhi r1, #0x1
	strhi r1, [r0, #0x0]
	mov r1, r9, asr #0x1f
	mla r3, r10, r1, r3
	mla r3, r11, r9, r3
	ldr r1, [sp, #0x18]
	mov r10, r2
	subs r2, r1, r2
	mov r0, r6, asr #0x1f
	sbc r1, r1, r3
	cmp r0, r1
	cmpeq r6, r2
	ldrhi r1, [sp, #0x48]
	movhi r2, #0x1
	strhi r2, [r1, #0x0]
	mov r1, #0x0
	mov r11, r3
	adds r10, r10, r6
	adc r11, r11, r0
	mov r0, r7
	mov r2, r1
	add r5, r5, #0x1
	blx r8
	mov r6, r0
_020E4E08:
	ldr r0, [sp, #0x0]
	cmp r5, r0
	bgt _020E4E28
	ldr r0, [sp, #0x18]
	cmp r6, r0
	beq _020E4E28
	tst r4, #0x60
	beq _020E4B0C
_020E4E28:
	tst r4, #0x34
	bne _020E4E44
	ldr r0, [sp, #0x40]
	mov r10, #0x0
	mov r11, r10
	str r10, [r0, #0x0]
	b _020E4E58
_020E4E44:
	ldr r0, [sp, #0x14]
	sub r1, r5, #0x1
	add r1, r1, r0
	ldr r0, [sp, #0x40]
	str r1, [r0, #0x0]
_020E4E58:
	mov r0, r7
	mov r1, r6
	mov r2, #0x1
	blx r8
	mov r0, r10
	mov r1, r11
	add sp, sp, #0x1c
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020E4E78: .word __msl_digit
_020E4E7C: .word __upper_mapC
    arm_func_end __strtoull

	arm_func_start strtoul
strtoul: ; 0x020E4E80
	stmdb sp!, {r3-r5,lr}
	sub sp, sp, #0x20
	mov r5, r0
	mov lr, #0x0
	mov r0, r2
	mov r4, r1
	add r2, sp, #0x1c
	str r5, [sp, #0xc]
	str lr, [sp, #0x10]
	str r2, [sp, #0x0]
	add r1, sp, #0x18
	str r1, [sp, #0x4]
	add r12, sp, #0x14
	ldr r2, _020E4F10 ; =__StringRead
	add r3, sp, #0xc
	sub r1, lr, #0x80000001
	str r12, [sp, #0x8]
	bl __strtoul
	cmp r4, #0x0
	ldrne r1, [sp, #0x1c]
	addne r1, r5, r1
	strne r1, [r4, #0x0]
	ldr r1, [sp, #0x14]
	cmp r1, #0x0
	beq _020E4EFC
	ldr r0, _020E4F14 ; =errno
	mov r1, #0x22
	str r1, [r0, #0x0]
	add sp, sp, #0x20
	mvn r0, #0x0
	ldmia sp!, {r3-r5,pc}
_020E4EFC:
	ldr r1, [sp, #0x18]
	cmp r1, #0x0
	rsbne r0, r0, #0x0
	add sp, sp, #0x20
	ldmia sp!, {r3-r5,pc}
	.balign 4
_020E4F10: .word __StringRead
_020E4F14: .word errno
    arm_func_end strtoul

	arm_func_start strtol
strtol: ; 0x020E4F18
	stmdb sp!, {r3-r5,lr}
	sub sp, sp, #0x20
	mov r5, r0
	mov lr, #0x0
	mov r0, r2
	mov r4, r1
	add r2, sp, #0x1c
	str r5, [sp, #0xc]
	str lr, [sp, #0x10]
	str r2, [sp, #0x0]
	add r1, sp, #0x18
	str r1, [sp, #0x4]
	add r12, sp, #0x14
	ldr r2, _020E4FD8 ; =__StringRead
	add r3, sp, #0xc
	sub r1, lr, #0x80000001
	str r12, [sp, #0x8]
	bl __strtoul
	cmp r4, #0x0
	ldrne r1, [sp, #0x1c]
	addne r1, r5, r1
	strne r1, [r4, #0x0]
	ldr r1, [sp, #0x14]
	cmp r1, #0x0
	bne _020E4FA4
	ldr r2, [sp, #0x18]
	cmp r2, #0x0
	bne _020E4F94
	mvn r1, #0x80000000
	cmp r0, r1
	bhi _020E4FA4
_020E4F94:
	cmp r2, #0x0
	beq _020E4FC8
	cmp r0, #0x80000000
	bls _020E4FC8
_020E4FA4:
	ldr r0, [sp, #0x18]
	ldr r1, _020E4FDC ; =errno
	mov r2, #0x22
	cmp r0, #0x0
	movne r0, #0x80000000
	str r2, [r1, #0x0]
	add sp, sp, #0x20
	mvneq r0, #0x80000000
	ldmia sp!, {r3-r5,pc}
_020E4FC8:
	cmp r2, #0x0
	rsbne r0, r0, #0x0
	add sp, sp, #0x20
	ldmia sp!, {r3-r5,pc}
	.balign 4
_020E4FD8: .word __StringRead
_020E4FDC: .word errno
    arm_func_end strtol

	arm_func_start atol
atol: ; 0x020E4FE0
	ldr ip, _020E4FF0 ; =strtol
	mov r1, #0x0
	mov r2, #0xa
	bx r12
	.balign 4
_020E4FF0: .word strtol
    arm_func_end atol

    .section .exceptix,4

	.word __strtoul
	.short 1001
	.word 0x0060FF00
	.word __strtoull
	.short 1101
	.word 0x0080FF00
	.word strtoul
	.short 153
	.word 0x00600300
	.word strtol
	.short 201
	.word 0x00600300
	.word atol
	.short 21
	.word 0x00000000
