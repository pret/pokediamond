	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start sub_0202B374
sub_0202B374: ; 0x0202B374
	ldr r0, _0202B378 ; =0x00000B88
	bx lr
	.balign 4
_0202B378: .word 0x00000B88

	thumb_func_start sub_0202B37C
sub_0202B37C: ; 0x0202B37C
	ldr r3, _0202B388 ; =MIi_CpuClearFast
	add r1, r0, #0x0
	mov r0, #0x0
	ldr r2, _0202B38C ; =0x00000B88
	bx r3
	nop
_0202B388: .word MIi_CpuClearFast
_0202B38C: .word 0x00000B88

	thumb_func_start sub_0202B390
sub_0202B390: ; 0x0202B390
	push {r4, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	mov r0, #0x0
	add r1, #0xc
	mov r2, #0xc0
	bl MIi_CpuClearFast
	add r1, r4, #0x0
	mov r0, #0x0
	add r1, #0xcc
	mov r2, #0xc0
	bl MIi_CpuClearFast
	mov r1, #0x63
	lsl r1, r1, #0x2
	mov r0, #0x0
	add r1, r4, r1
	mov r2, #0xc0
	bl MIi_CpuClearFast
	add r0, r4, #0x0
	bl sub_0202B3F8
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0202B3C4
sub_0202B3C4: ; 0x0202B3C4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, r1
	ble _0202B3D4
	sub r0, r0, r1
	str r0, [r4, #0x4]
	pop {r4, pc}
_0202B3D4:
	add r0, r2, #0x0
	mov r1, #0xf
	bl _s32_div_f
	mov r0, #0xf
	sub r1, r0, r1
	str r1, [r4, #0x4]
	bne _0202B3E6
	str r0, [r4, #0x4]
_0202B3E6:
	mov r1, #0x0
	strb r1, [r4, #0x8]
	add r0, r1, #0x0
_0202B3EC:
	strb r0, [r4, r1]
	add r1, r1, #0x1
	cmp r1, #0x4
	blt _0202B3EC
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0202B3F8
sub_0202B3F8: ; 0x0202B3F8
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	bl sub_0202B40C
	add r0, r4, #0x0
	bl sub_0202B430
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0202B40C
sub_0202B40C: ; 0x0202B40C
	strb r1, [r0, #0x8]
	bx lr

	thumb_func_start sub_0202B410
sub_0202B410: ; 0x0202B410
	ldrb r0, [r0, #0x8]
	bx lr

	thumb_func_start sub_0202B414
sub_0202B414: ; 0x0202B414
	push {r3, lr}
	mov r3, #0x0
_0202B418:
	ldrb r2, [r0, r3]
	cmp r2, #0x0
	bne _0202B422
	strb r1, [r0, r3]
	pop {r3, pc}
_0202B422:
	add r3, r3, #0x1
	cmp r3, #0x4
	blt _0202B418
	bl GF_AssertFail
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_0202B430
sub_0202B430: ; 0x0202B430
	mov r2, #0x0
	add r1, r2, #0x0
_0202B434:
	strb r1, [r0, r2]
	add r2, r2, #0x1
	cmp r2, #0x4
	blt _0202B434
	bx lr
	.balign 4

	thumb_func_start sub_0202B440
sub_0202B440: ; 0x0202B440
	mov r3, #0x0
_0202B442:
	ldrb r2, [r0, r3]
	cmp r1, r2
	bne _0202B44C
	mov r0, #0x1
	bx lr
_0202B44C:
	add r3, r3, #0x1
	cmp r3, #0x4
	blt _0202B442
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_0202B458
sub_0202B458: ; 0x0202B458
	mov r2, #0x0
	add r3, r2, #0x0
_0202B45C:
	ldrb r1, [r0, r2]
	cmp r1, #0x0
	beq _0202B464
	add r3, r3, #0x1
_0202B464:
	add r2, r2, #0x1
	cmp r2, #0x4
	blt _0202B45C
	add r0, r3, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_0202B470
sub_0202B470: ; 0x0202B470
	push {r4-r6, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, sp, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl GF_RTC_CopyDate
	ldr r0, [sp, #0x8]
	ldr r3, [sp, #0x4]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x10
	ldr r0, [sp, #0x0]
	lsl r3, r3, #0x18
	lsl r0, r0, #0x18
	lsr r3, r3, #0x8
	orr r0, r3
	ldr r2, [sp, #0xc]
	orr r0, r1
	orr r0, r2
	str r0, [r5, #0x4]
	strb r4, [r5, #0x0]
	mov r0, #0x0
	strb r0, [r5, #0x1]
	add r5, #0x8
	add r0, r6, #0x0
	add r1, r5, #0x0
	mov r2, #0x28
	bl MIi_CpuCopyFast
	add sp, #0x10
	pop {r4-r6, pc}

	thumb_func_start sub_0202B4B0
sub_0202B4B0: ; 0x0202B4B0
	push {r3-r5, lr}
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl sub_0202B548
	mov r2, #0x0
	add r3, r0, #0x0
_0202B4BE:
	ldrb r1, [r3, #0x0]
	cmp r5, r1
	bne _0202B4E0
	mov r1, #0x30
	mul r1, r2
	add r0, r0, r1
	ldrb r1, [r0, #0x1]
	cmp r1, #0x3
	blo _0202B4DC
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl sub_0202B470
	mov r0, #0x1
	pop {r3-r5, pc}
_0202B4DC:
	mov r0, #0x0
	pop {r3-r5, pc}
_0202B4E0:
	add r2, r2, #0x1
	add r3, #0x30
	cmp r2, #0x4
	blt _0202B4BE
	mov r1, #0x0
	add r3, r0, #0x0
_0202B4EC:
	ldrb r2, [r3, #0x0]
	cmp r2, #0x0
	bne _0202B504
	mov r2, #0x30
	mul r2, r1
	add r0, r0, r2
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl sub_0202B470
	mov r0, #0x1
	pop {r3-r5, pc}
_0202B504:
	add r1, r1, #0x1
	add r3, #0x30
	cmp r1, #0x4
	blt _0202B4EC
	mov r1, #0x0
	add r3, r0, #0x0
_0202B510:
	ldrb r2, [r3, #0x1]
	cmp r2, #0x3
	blo _0202B528
	mov r2, #0x30
	mul r2, r1
	add r0, r0, r2
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl sub_0202B470
	mov r0, #0x1
	pop {r3-r5, pc}
_0202B528:
	add r1, r1, #0x1
	add r3, #0x30
	cmp r1, #0x4
	blt _0202B510
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start sub_0202B534
sub_0202B534: ; 0x0202B534
	add r0, #0x8
	bx lr

	thumb_func_start sub_0202B538
sub_0202B538: ; 0x0202B538
	ldrb r0, [r0, #0x6]
	bx lr

	thumb_func_start sub_0202B53C
sub_0202B53C: ; 0x0202B53C
	ldrb r0, [r0, #0x5]
	bx lr

	thumb_func_start sub_0202B540
sub_0202B540: ; 0x0202B540
	add r0, #0x18
	bx lr

	thumb_func_start sub_0202B544
sub_0202B544: ; 0x0202B544
	bx lr
	.balign 4

	thumb_func_start sub_0202B548
sub_0202B548: ; 0x0202B548
	push {r4, lr}
	mov r4, #0x0
	cmp r1, #0x4
	bhi _0202B57E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0202B55C: ; jump table (using 16-bit offset)
	.short _0202B57E - _0202B55C - 2; case 0
	.short _0202B566 - _0202B55C - 2; case 1
	.short _0202B56E - _0202B55C - 2; case 2
	.short _0202B574 - _0202B55C - 2; case 3
	.short _0202B57A - _0202B55C - 2; case 4
_0202B566:
	mov r1, #0x63
	lsl r1, r1, #0x2
	add r4, r0, r1
	b _0202B57E
_0202B56E:
	add r4, r0, #0x0
	add r4, #0xc
	b _0202B57E
_0202B574:
	add r4, r0, #0x0
	add r4, #0xcc
	b _0202B57E
_0202B57A:
	bl GF_AssertFail
_0202B57E:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0202B584
sub_0202B584: ; 0x0202B584
	push {r4, lr}
	mov r4, #0x0
	cmp r1, #0x4
	bhi _0202B5BA
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0202B598: ; jump table (using 16-bit offset)
	.short _0202B5BA - _0202B598 - 2; case 0
	.short _0202B5B0 - _0202B598 - 2; case 1
	.short _0202B5A2 - _0202B598 - 2; case 2
	.short _0202B5AA - _0202B598 - 2; case 3
	.short _0202B5B6 - _0202B598 - 2; case 4
_0202B5A2:
	mov r1, #0x93
	lsl r1, r1, #0x2
	add r4, r0, r1
	b _0202B5BA
_0202B5AA:
	ldr r1, _0202B5C0 ; =0x000006CC
	add r4, r0, r1
	b _0202B5BA
_0202B5B0:
	ldr r1, _0202B5C4 ; =0x0000090C
	add r4, r0, r1
	b _0202B5BA
_0202B5B6:
	bl GF_AssertFail
_0202B5BA:
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_0202B5C0: .word 0x000006CC
_0202B5C4: .word 0x0000090C

	thumb_func_start sub_0202B5C8
sub_0202B5C8: ; 0x0202B5C8
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start sub_0202B5CC
sub_0202B5CC: ; 0x0202B5CC
	ldrb r1, [r0, #0x1]
	cmp r1, #0x3
	bhs _0202B5D6
	add r1, r1, #0x1
	strb r1, [r0, #0x1]
_0202B5D6:
	bx lr

	thumb_func_start sub_0202B5D8
sub_0202B5D8: ; 0x0202B5D8
	add r0, #0x8
	bx lr

	thumb_func_start sub_0202B5DC
sub_0202B5DC: ; 0x0202B5DC
	push {r4-r7}
	mov r5, #0x0
	add r4, r5, #0x0
	ldr r6, [sp, #0x10]
	cmp r1, #0x0
	ble _0202B616
_0202B5E8:
	ldrb r7, [r0, #0x0]
	cmp r2, r7
	bne _0202B60E
	ldrb r7, [r0, #0x1]
	cmp r3, #0x0
	beq _0202B600
	cmp r7, #0x0
	beq _0202B600
	add r7, r4, #0x1
	strb r7, [r6, r5]
	add r5, r5, #0x1
	b _0202B60E
_0202B600:
	cmp r3, #0x0
	bne _0202B60E
	cmp r7, #0x0
	bne _0202B60E
	add r7, r4, #0x1
	strb r7, [r6, r5]
	add r5, r5, #0x1
_0202B60E:
	add r4, r4, #0x1
	add r0, #0x30
	cmp r4, r1
	blt _0202B5E8
_0202B616:
	add r0, r5, #0x0
	pop {r4-r7}
	bx lr

	thumb_func_start sub_0202B61C
sub_0202B61C: ; 0x0202B61C
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	mov r5, #0x0
	add r0, r1, #0x0
	add r4, r5, #0x0
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	ldr r7, [sp, #0x20]
	cmp r0, #0x0
	ble _0202B672
_0202B634:
	ldrb r2, [r6, #0x18]
	ldr r1, [sp, #0x4]
	ldrb r0, [r6, #0x19]
	cmp r1, r2
	bne _0202B668
	ldr r1, [sp, #0x8]
	cmp r1, #0x0
	beq _0202B654
	cmp r0, #0x0
	beq _0202B654
	add r0, r4, #0x1
	bl sub_0202B830
	strb r0, [r7, r5]
	add r5, r5, #0x1
	b _0202B668
_0202B654:
	ldr r1, [sp, #0x8]
	cmp r1, #0x0
	bne _0202B668
	cmp r0, #0x0
	bne _0202B668
	add r0, r4, #0x1
	bl sub_0202B830
	strb r0, [r7, r5]
	add r5, r5, #0x1
_0202B668:
	ldr r0, [sp, #0x0]
	add r4, r4, #0x1
	add r6, #0x48
	cmp r4, r0
	blt _0202B634
_0202B672:
	add r0, r5, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start sub_0202B678
sub_0202B678: ; 0x0202B678
	push {r3-r5, lr}
	ldr r5, [sp, #0x10]
	ldr r4, [sp, #0x14]
	cmp r1, #0x4
	bhi _0202B702
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0202B68E: ; jump table (using 16-bit offset)
	.short _0202B702 - _0202B68E - 2; case 0
	.short _0202B6DA - _0202B68E - 2; case 1
	.short _0202B698 - _0202B68E - 2; case 2
	.short _0202B6BA - _0202B68E - 2; case 3
	.short _0202B6FE - _0202B68E - 2; case 4
_0202B698:
	cmp r3, #0x0
	str r4, [sp, #0x0]
	beq _0202B6AA
	add r0, #0xc
	mov r1, #0x4
	add r3, r5, #0x0
	bl sub_0202B5DC
	pop {r3-r5, pc}
_0202B6AA:
	mov r1, #0x93
	lsl r1, r1, #0x2
	add r0, r0, r1
	mov r1, #0x10
	add r3, r5, #0x0
	bl sub_0202B61C
	pop {r3-r5, pc}
_0202B6BA:
	cmp r3, #0x0
	str r4, [sp, #0x0]
	beq _0202B6CC
	add r0, #0xcc
	mov r1, #0x4
	add r3, r5, #0x0
	bl sub_0202B5DC
	pop {r3-r5, pc}
_0202B6CC:
	ldr r1, _0202B708 ; =0x000006CC
	add r3, r5, #0x0
	add r0, r0, r1
	mov r1, #0x8
	bl sub_0202B61C
	pop {r3-r5, pc}
_0202B6DA:
	cmp r3, #0x0
	str r4, [sp, #0x0]
	beq _0202B6F0
	mov r1, #0x63
	lsl r1, r1, #0x2
	add r0, r0, r1
	mov r1, #0x4
	add r3, r5, #0x0
	bl sub_0202B5DC
	pop {r3-r5, pc}
_0202B6F0:
	ldr r1, _0202B70C ; =0x0000090C
	add r3, r5, #0x0
	add r0, r0, r1
	mov r1, #0x8
	bl sub_0202B61C
	pop {r3-r5, pc}
_0202B6FE:
	mov r0, #0x0
	pop {r3-r5, pc}
_0202B702:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0202B708: .word 0x000006CC
_0202B70C: .word 0x0000090C

	thumb_func_start sub_0202B710
sub_0202B710: ; 0x0202B710
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r6, r1, #0x0
	add r5, r2, #0x0
	add r0, sp, #0x8
	mov r1, #0x0
	mov r2, #0x4
	bl MI_CpuFill8
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	mov r3, #0x1
	bl sub_0202B678
	cmp r0, #0x0
	beq _0202B742
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_0202B742:
	mov r3, #0x1
	str r3, [sp, #0x0]
	add r0, sp, #0x8
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl sub_0202B678
	cmp r0, #0x0
	beq _0202B79E
	add r0, sp, #0x8
	ldrb r0, [r0, #0x0]
	mov r7, #0x0
	cmp r0, #0x0
	beq _0202B798
	add r5, sp, #0x8
_0202B764:
	ldrb r2, [r5, #0x0]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl sub_0202B7C8
	ldrb r0, [r0, #0x1]
	cmp r0, #0x3
	blo _0202B77A
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_0202B77A:
	add r7, r7, #0x1
	add r5, r5, #0x1
	cmp r7, #0x4
	bge _0202B786
	mov r1, #0x1
	b _0202B788
_0202B786:
	mov r1, #0x0
_0202B788:
	ldrb r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0202B792
	mov r0, #0x1
	b _0202B794
_0202B792:
	mov r0, #0x0
_0202B794:
	tst r0, r1
	bne _0202B764
_0202B798:
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_0202B79E:
	mov r5, #0x1
_0202B7A0:
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl sub_0202B7C8
	ldrb r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0202B7B6
	ldrb r0, [r0, #0x1]
	cmp r0, #0x3
	blo _0202B7BC
_0202B7B6:
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_0202B7BC:
	add r5, r5, #0x1
	cmp r5, #0x4
	ble _0202B7A0
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start sub_0202B7C8
sub_0202B7C8: ; 0x0202B7C8
	push {r4-r6, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r6, r1, #0x0
	bl sub_0202B820
	cmp r0, #0x1
	beq _0202B7DE
	bl GF_AssertFail
_0202B7DE:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl sub_0202B548
	mov r1, #0x80
	bic r4, r1
	sub r2, r4, #0x1
	mov r1, #0x30
	mul r1, r2
	add r0, r0, r1
	pop {r4-r6, pc}

	thumb_func_start sub_0202B7F4
sub_0202B7F4: ; 0x0202B7F4
	push {r4-r6, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r6, r1, #0x0
	bl sub_0202B820
	cmp r0, #0x0
	beq _0202B80A
	bl GF_AssertFail
_0202B80A:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl sub_0202B584
	mov r1, #0x80
	bic r4, r1
	sub r2, r4, #0x1
	mov r1, #0x48
	mul r1, r2
	add r0, r0, r1
	pop {r4-r6, pc}

	thumb_func_start sub_0202B820
sub_0202B820: ; 0x0202B820
	mov r1, #0x80
	tst r0, r1
	bne _0202B82A
	mov r0, #0x1
	bx lr
_0202B82A:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_0202B830
sub_0202B830: ; 0x0202B830
	mov r1, #0x80
	orr r0, r1
	bx lr
	.balign 4

	thumb_func_start sub_0202B838
sub_0202B838: ; 0x0202B838
	ldr r1, _0202B840 ; =0x00000B4C
	add r0, r0, r1
	bx lr
	nop
_0202B840: .word 0x00000B4C

	thumb_func_start sub_0202B844
sub_0202B844: ; 0x0202B844
	ldr r1, _0202B84C ; =0x00000B56
	add r0, r0, r1
	bx lr
	nop
_0202B84C: .word 0x00000B56

	thumb_func_start sub_0202B850
sub_0202B850: ; 0x0202B850
	ldr r1, _0202B858 ; =0x00000B7A
	add r0, r0, r1
	bx lr
	nop
_0202B858: .word 0x00000B7A

	thumb_func_start sub_0202B85C
sub_0202B85C: ; 0x0202B85C
	ldr r1, _0202B864 ; =0x00000B7C
	add r0, r0, r1
	bx lr
	nop
_0202B864: .word 0x00000B7C

	thumb_func_start sub_0202B868
sub_0202B868: ; 0x0202B868
	mov r1, #0x2e
	lsl r1, r1, #0x6
	add r0, r0, r1
	bx lr
