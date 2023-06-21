	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021E3444
ov05_021E3444: ; 0x021E3444
	push {r3, r4, r5, lr}
	add r5, r1, #0
	lsl r1, r0, #2
	ldr r0, _021E3470 ; =ov05_021F74E8
	add r4, r2, #0
	ldr r0, [r0, r1]
	mov r1, #0x20
	mov r2, #5
	mov r3, #4
	bl sub_020061E8
	bl sub_0201B6C8
	str r5, [r0, #0x10]
	str r4, [r0, #0x14]
	cmp r4, #0
	beq _021E346A
	mov r1, #0
	str r1, [r4]
_021E346A:
	mov r1, #0
	str r1, [r0, #0x18]
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021E3470: .word ov05_021F74E8

	thumb_func_start ov05_021E3474
ov05_021E3474: ; 0x021E3474
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #4
	mov r1, #0x4c
	str r2, [sp]
	add r5, r3, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x4c
	add r4, r0, #0
	bl memset
	ldr r0, _021E34B4 ; =ov05_021E34B8
	add r1, r4, #0
	mov r2, #5
	bl sub_0200CA44
	str r5, [r4, #0x48]
	cmp r5, #0
	beq _021E34A4
	mov r0, #0
	str r0, [r5]
_021E34A4:
	str r6, [r4, #0xc]
	ldr r0, [sp]
	str r7, [r4, #0x10]
	str r0, [r4, #0x14]
	ldr r0, [sp, #0x18]
	str r0, [r4, #4]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E34B4: .word ov05_021E34B8

	thumb_func_start ov05_021E34B8
ov05_021E34B8: ; 0x021E34B8
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldr r1, [r4]
	cmp r1, #5
	bhi _021E359E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E34D0: ; jump table
	.short _021E34DC - _021E34D0 - 2 ; case 0
	.short _021E3514 - _021E34D0 - 2 ; case 1
	.short _021E352E - _021E34D0 - 2 ; case 2
	.short _021E3542 - _021E34D0 - 2 ; case 3
	.short _021E355C - _021E34D0 - 2 ; case 4
	.short _021E3580 - _021E34D0 - 2 ; case 5
_021E34DC:
	ldr r0, [r4, #0xc]
	cmp r0, #1
	bne _021E34F6
	mov r0, #8
	str r0, [sp]
	add r0, r4, #0
	ldr r2, [r4, #0x14]
	add r0, #0x30
	mov r1, #0
	mov r3, #2
	bl ov05_021E372C
	b _021E350C
_021E34F6:
	cmp r0, #2
	bne _021E350C
	mov r0, #8
	str r0, [sp]
	add r0, r4, #0
	ldr r2, [r4, #0x14]
	add r0, #0x30
	mov r1, #0
	mov r3, #1
	bl ov05_021E372C
_021E350C:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E359E
_021E3514:
	mov r0, #3
	str r0, [sp]
	add r0, r4, #0
	ldr r2, [r4, #0x10]
	ldr r3, [r4, #0xc]
	add r0, #0x18
	mov r1, #0
	bl ov05_021E372C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E359E
_021E352E:
	add r0, r4, #0
	add r0, #0x18
	bl ov05_021E3738
	cmp r0, #0
	beq _021E359E
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E359E
_021E3542:
	mov r0, #3
	str r0, [sp]
	add r0, r4, #0
	ldr r1, [r4, #0x10]
	ldr r3, [r4, #0xc]
	add r0, #0x18
	mov r2, #0
	bl ov05_021E372C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E359E
_021E355C:
	add r0, r4, #0
	add r0, #0x18
	bl ov05_021E3738
	cmp r0, #0
	beq _021E359E
	ldr r0, [r4, #8]
	add r1, r0, #1
	str r1, [r4, #8]
	ldr r0, [r4, #4]
	cmp r1, r0
	bne _021E357A
	mov r0, #5
	str r0, [r4]
	b _021E359E
_021E357A:
	mov r0, #1
	str r0, [r4]
	b _021E359E
_021E3580:
	mov r1, #0
	str r1, [r4]
	str r1, [r4, #8]
	ldr r2, [r4, #0x48]
	cmp r2, #0
	beq _021E3590
	mov r1, #1
	str r1, [r2]
_021E3590:
	bl sub_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	add sp, #4
	pop {r3, r4, pc}
_021E359E:
	add r4, #0x30
	add r0, r4, #0
	bl ov05_021E3738
	add sp, #4
	pop {r3, r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021E35AC
ov05_021E35AC: ; 0x021E35AC
	ldr r0, [r0, #0x18]
	bx lr

	thumb_func_start ov05_021E35B0
ov05_021E35B0: ; 0x021E35B0
	str r1, [r0]
	str r1, [r0, #4]
	sub r1, r2, r1
	str r1, [r0, #8]
	str r3, [r0, #0x10]
	mov r1, #0
	str r1, [r0, #0xc]
	bx lr

	thumb_func_start ov05_021E35C0
ov05_021E35C0: ; 0x021E35C0
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #8]
	ldr r0, [r4, #0xc]
	mul r0, r1
	ldr r1, [r4, #0x10]
	bl _s32_div_f
	ldr r1, [r4, #4]
	add r0, r0, r1
	str r0, [r4]
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	add r0, r0, #1
	cmp r0, r1
	bgt _021E35E6
	str r0, [r4, #0xc]
	mov r0, #0
	pop {r4, pc}
_021E35E6:
	str r1, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}

	thumb_func_start ov05_021E35EC
ov05_021E35EC: ; 0x021E35EC
	str r1, [r0]
	str r1, [r0, #4]
	sub r1, r2, r1
	str r1, [r0, #8]
	str r3, [r0, #0x10]
	mov r1, #0
	str r1, [r0, #0xc]
	bx lr

	thumb_func_start ov05_021E35FC
ov05_021E35FC: ; 0x021E35FC
	push {r4, lr}
	add r4, r0, #0
	ldr r2, [r4, #0xc]
	ldr r0, [r4, #8]
	lsl r2, r2, #0xc
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r0, r0, r2
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	ldr r1, [r4, #0x10]
	lsl r1, r1, #0xc
	bl FX_Div
	ldr r1, [r4, #4]
	add r0, r0, r1
	str r0, [r4]
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	add r0, r0, #1
	cmp r0, r1
	bgt _021E363C
	str r0, [r4, #0xc]
	mov r0, #0
	pop {r4, pc}
_021E363C:
	str r1, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021E3644
ov05_021E3644: ; 0x021E3644
	push {r3, r4, r5, r6, r7, lr}
	ldr r4, [sp, #0x18]
	add r5, r0, #0
	add r7, r2, #0
	add r0, r3, #0
	add r6, r1, #0
	lsl r2, r4, #0xc
	str r3, [sp]
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	add r2, r0, #0
	sub r0, r7, r6
	mov r7, #2
	mov r3, #0
	lsl r7, r7, #0xa
	add r2, r2, r7
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r2, r2, #0xc
	orr r2, r1
	sub r2, r0, r2
	asr r1, r2, #0x1f
	lsr r0, r2, #0x13
	lsl r1, r1, #0xd
	orr r1, r0
	lsl r0, r2, #0xd
	add r0, r0, r7
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	add r1, r4, #0
	mul r1, r4
	lsl r1, r1, #0xc
	bl FX_Div
	str r6, [r5]
	ldr r1, [sp]
	str r6, [r5, #4]
	str r1, [r5, #8]
	str r0, [r5, #0xc]
	mov r0, #0
	str r0, [r5, #0x10]
	str r4, [r5, #0x14]
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021E36A4
ov05_021E36A4: ; 0x021E36A4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r6, [r5, #0x10]
	ldr r0, [r5, #8]
	lsl r2, r6, #0xc
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsr r4, r2, #0xc
	lsl r0, r1, #0x14
	add r2, r6, #0
	orr r4, r0
	ldr r0, [r5, #0xc]
	mul r2, r6
	lsl r2, r2, #0xc
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r0, r0, r2
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	lsl r1, r2, #2
	bl FX_Div
	ldr r1, [r5, #4]
	add r0, r4, r0
	add r0, r1, r0
	str r0, [r5]
	ldr r0, [r5, #0x10]
	ldr r1, [r5, #0x14]
	add r0, r0, #1
	cmp r0, r1
	bgt _021E3704
	str r0, [r5, #0x10]
	mov r0, #0
	pop {r4, r5, r6, pc}
_021E3704:
	str r1, [r5, #0x10]
	mov r0, #1
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021E370C
ov05_021E370C: ; 0x021E370C
	push {r3, lr}
	cmp r0, #1
	bne _021E371A
	ldr r0, _021E3724 ; =0x0400006C
	bl GXx_SetMasterBrightness_
	pop {r3, pc}
_021E371A:
	ldr r0, _021E3728 ; =0x0400106C
	bl GXx_SetMasterBrightness_
	pop {r3, pc}
	nop
_021E3724: .word 0x0400006C
_021E3728: .word 0x0400106C

	thumb_func_start ov05_021E372C
ov05_021E372C: ; 0x021E372C
	push {r3, lr}
	str r3, [r0, #0x14]
	ldr r3, [sp, #8]
	bl ov05_021E35B0
	pop {r3, pc}

	thumb_func_start ov05_021E3738
ov05_021E3738: ; 0x021E3738
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl ov05_021E35C0
	add r4, r0, #0
	ldr r0, _021E3750 ; =ov05_021E3754
	add r1, r5, #0
	mov r2, #0xa
	bl sub_0200CA98
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021E3750: .word ov05_021E3754

	thumb_func_start ov05_021E3754
ov05_021E3754: ; 0x021E3754
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1, #0x14]
	ldr r1, [r1]
	bl ov05_021E370C
	add r0, r4, #0
	bl sub_0200CAB4
	pop {r4, pc}

	thumb_func_start ov05_021E3768
ov05_021E3768: ; 0x021E3768
	push {r4, lr}
	mov r0, #4
	mov r1, #0x30
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x30
	add r4, r0, #0
	bl memset
	ldr r0, _021E379C ; =0x04000048
	mov r1, #0x3f
	ldrh r2, [r0]
	bic r2, r1
	mov r1, #0x1f
	orr r2, r1
	mov r1, #0x20
	orr r1, r2
	strh r1, [r0]
	ldrh r2, [r0]
	ldr r1, _021E37A0 ; =0xFFFFC0FF
	and r1, r2
	strh r1, [r0]
	add r0, r4, #0
	pop {r4, pc}
	nop
_021E379C: .word 0x04000048
_021E37A0: .word 0xFFFFC0FF

	thumb_func_start ov05_021E37A4
ov05_021E37A4: ; 0x021E37A4
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x24]
	cmp r1, #0
	beq _021E37B2
	bl ov05_021E3920
_021E37B2:
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021E37C8 ; =0xFFFF1FFF
	and r0, r1
	str r0, [r2]
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	nop
_021E37C8: .word 0xFFFF1FFF

	thumb_func_start ov05_021E37CC
ov05_021E37CC: ; 0x021E37CC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5, #0x24]
	add r7, r2, #0
	str r3, [sp, #4]
	ldr r4, [sp, #0x20]
	cmp r0, #0
	beq _021E37E4
	bl GF_AssertFail
_021E37E4:
	mov r0, #0
	str r0, [r6, #0x18]
	ldr r1, [r6, #0x10]
	add r6, #0x18
	ldr r1, [r1, #4]
	ldr r2, [sp, #0x24]
	ldr r1, [r1, #0x1c]
	ldr r3, [sp, #0x28]
	str r1, [r5, #0x20]
	str r7, [r5, #0x18]
	str r0, [r5, #0x1c]
	ldr r0, [sp, #4]
	str r6, [r5, #0x2c]
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021E3644
	cmp r4, #0
	blt _021E3824
	mov r0, #0xff
	ldr r2, _021E3850 ; =0x04000040
	sub r0, r0, r4
	strh r0, [r2]
	add r0, r4, #1
	mov r1, #0xc0
	lsl r0, r0, #0x18
	strh r1, [r2, #4]
	lsr r0, r0, #0x18
	strh r0, [r2, #2]
	strh r1, [r2, #6]
	b _021E3840
_021E3824:
	add r0, r4, #0
	add r0, #0xff
	lsl r0, r0, #0x18
	mov r2, #1
	sub r2, r2, r4
	lsl r2, r2, #0x18
	ldr r1, _021E3850 ; =0x04000040
	lsr r0, r0, #0x18
	strh r0, [r1]
	mov r0, #0xc0
	strh r0, [r1, #4]
	lsr r2, r2, #0x18
	strh r2, [r1, #2]
	strh r0, [r1, #6]
_021E3840:
	mov r2, #1
	ldr r0, _021E3854 ; =ov05_021E3858
	add r1, r5, #0
	lsl r2, r2, #0xa
	bl sub_0200CA98
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E3850: .word 0x04000040
_021E3854: .word ov05_021E3858

	thumb_func_start ov05_021E3858
ov05_021E3858: ; 0x021E3858
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r2, #1
	ldr r0, _021E3880 ; =ov05_021E38B8
	add r4, r1, #0
	lsl r2, r2, #0xa
	bl sub_0200CA98
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x20]
	ldr r1, _021E3884 ; =ov05_021E397C
	add r2, r4, #0
	bl ov05_021F4624
	str r0, [r4, #0x24]
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
	nop
_021E3880: .word ov05_021E38B8
_021E3884: .word ov05_021E397C

	thumb_func_start ov05_021E3888
ov05_021E3888: ; 0x021E3888
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r1, #0
	add r4, r2, #0
	add r6, r3, #0
	bl ov05_021E35AC
	cmp r0, #0
	beq _021E389E
	bl GF_AssertFail
_021E389E:
	str r4, [r5, #0x18]
	mov r0, #0
	str r0, [r5, #0x1c]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x1c]
	ldr r3, [sp, #0x20]
	add r0, r5, #0
	str r6, [sp]
	bl ov05_021E3644
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021E38B8
ov05_021E38B8: ; 0x021E38B8
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _021E38C8
	cmp r0, #1
	beq _021E3914
	pop {r4, pc}
_021E38C8:
	add r0, r4, #0
	bl ov05_021E36A4
	cmp r0, #0
	beq _021E38D8
	ldr r0, [r4, #0x1c]
	add r0, r0, #1
	str r0, [r4, #0x1c]
_021E38D8:
	ldr r0, [r4]
	asr r0, r0, #0xc
	bmi _021E38F6
	mov r1, #0xff
	sub r1, r1, r0
	ldr r2, _021E391C ; =0x04000040
	add r0, r0, #1
	strh r1, [r2]
	mov r1, #0xc0
	lsl r0, r0, #0x18
	strh r1, [r2, #4]
	lsr r0, r0, #0x18
	strh r0, [r2, #2]
	strh r1, [r2, #6]
	pop {r4, pc}
_021E38F6:
	add r1, r0, #0
	add r1, #0xff
	lsl r1, r1, #0x18
	ldr r3, _021E391C ; =0x04000040
	lsr r1, r1, #0x18
	strh r1, [r3]
	mov r1, #1
	sub r0, r1, r0
	mov r2, #0xc0
	lsl r0, r0, #0x18
	strh r2, [r3, #4]
	lsr r0, r0, #0x18
	strh r0, [r3, #2]
	strh r2, [r3, #6]
	pop {r4, pc}
_021E3914:
	add r0, r4, #0
	bl ov05_021E3920
	pop {r4, pc}
	.balign 4, 0
_021E391C: .word 0x04000040

	thumb_func_start ov05_021E3920
ov05_021E3920: ; 0x021E3920
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E3974 ; =0x04000048
	mov r2, #0x3f
	ldrh r3, [r0]
	mov r1, #0x1f
	bic r3, r2
	orr r3, r1
	mov r1, #0x20
	orr r3, r1
	strh r3, [r0]
	ldrh r3, [r0, #2]
	bic r3, r2
	add r2, r0, #0
	strh r3, [r0, #2]
	mov r3, #0
	sub r2, #8
	strh r3, [r2]
	sub r0, r0, #4
	strh r3, [r0]
	lsl r3, r1, #0x15
	ldr r2, [r3]
	ldr r0, _021E3978 ; =0xFFFF1FFF
	and r2, r0
	lsl r0, r1, #8
	orr r0, r2
	str r0, [r3]
	ldr r0, [r4, #0x2c]
	mov r1, #1
	str r1, [r0]
	ldr r0, [r4, #0x24]
	bl ov05_021F4648
	mov r0, #0
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x28]
	bl sub_0200CAB4
	mov r0, #0
	str r0, [r4, #0x28]
	pop {r4, pc}
	nop
_021E3974: .word 0x04000048
_021E3978: .word 0xFFFF1FFF

	thumb_func_start ov05_021E397C
ov05_021E397C: ; 0x021E397C
	push {r4, lr}
	ldr r0, _021E39EC ; =0x04000006
	add r4, r1, #0
	ldrh r0, [r0]
	ldr r1, [r4, #0x18]
	bl _u32_div_f
	mov r1, #1
	tst r0, r1
	ldr r0, [r4]
	bne _021E3994
	b _021E3996
_021E3994:
	neg r0, r0
_021E3996:
	asr r2, r0, #0xc
	ldr r0, _021E39F0 ; =0x000001FF
	add r1, r2, #0
	and r1, r0
	ldr r0, _021E39F4 ; =0x04000010
	cmp r2, #0
	str r1, [r0]
	str r1, [r0, #4]
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	ldr r1, _021E39F8 ; =0xFFFF1FFF
	blt _021E39C8
	add r3, r0, #0
	sub r3, #0x10
	ldr r2, [r3]
	and r2, r1
	lsl r1, r0, #9
	orr r1, r2
	str r1, [r3]
	add r0, #0x3a
	ldrh r2, [r0]
	mov r1, #0x3f
	bic r2, r1
	strh r2, [r0]
	pop {r4, pc}
_021E39C8:
	add r3, r0, #0
	sub r3, #0x10
	ldr r2, [r3]
	and r2, r1
	lsl r1, r0, #0xa
	orr r1, r2
	str r1, [r3]
	add r0, #0x3a
	ldrh r2, [r0]
	mov r1, #0x3f
	bic r2, r1
	mov r1, #0x1f
	orr r2, r1
	mov r1, #0x20
	orr r1, r2
	strh r1, [r0]
	pop {r4, pc}
	nop
_021E39EC: .word 0x04000006
_021E39F0: .word 0x000001FF
_021E39F4: .word 0x04000010
_021E39F8: .word 0xFFFF1FFF

	thumb_func_start ov05_021E39FC
ov05_021E39FC: ; 0x021E39FC
	push {r4, r5, r6, lr}
	mov r0, #4
	mov r1, #0x48
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x48
	add r4, r0, #0
	bl memset
	ldr r0, _021E3A40 ; =0x04000048
	mov r5, #0x3f
	ldrh r2, [r0]
	mov r1, #0x1f
	bic r2, r5
	add r3, r2, #0
	orr r3, r1
	mov r2, #0x20
	orr r3, r2
	strh r3, [r0]
	ldrh r6, [r0]
	ldr r3, _021E3A44 ; =0xFFFFC0FF
	lsl r1, r1, #8
	and r3, r6
	orr r3, r1
	lsl r1, r2, #8
	orr r1, r3
	strh r1, [r0]
	ldrh r1, [r0, #2]
	bic r1, r5
	strh r1, [r0, #2]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	nop
_021E3A40: .word 0x04000048
_021E3A44: .word 0xFFFFC0FF

	thumb_func_start ov05_021E3A48
ov05_021E3A48: ; 0x021E3A48
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x3c]
	cmp r1, #0
	beq _021E3A56
	bl ov05_021E3BA4
_021E3A56:
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021E3A6C ; =0xFFFF1FFF
	and r0, r1
	str r0, [r2]
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	nop
_021E3A6C: .word 0xFFFF1FFF

	thumb_func_start ov05_021E3A70
ov05_021E3A70: ; 0x021E3A70
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x3c]
	add r6, r2, #0
	add r7, r3, #0
	cmp r0, #0
	beq _021E3A84
	bl GF_AssertFail
_021E3A84:
	mov r1, #0
	str r1, [r5, #0x18]
	ldr r0, [r5, #0x10]
	mov r2, #0xff
	ldr r0, [r0, #4]
	add r5, #0x18
	ldr r0, [r0, #0x1c]
	lsl r2, r2, #0xc
	str r0, [r4, #0x38]
	mov r0, #0x60
	str r0, [r4, #0x30]
	str r1, [r4, #0x34]
	str r5, [r4, #0x44]
	add r0, r4, #0
	add r3, r7, #0
	str r6, [sp]
	bl ov05_021E3644
	add r0, r4, #0
	mov r2, #6
	ldr r3, [sp, #0x18]
	add r0, #0x18
	mov r1, #0
	lsl r2, r2, #0x10
	str r6, [sp]
	bl ov05_021E3644
	ldr r2, _021E3AD4 ; =0x04000040
	mov r1, #0xff
	strh r1, [r2]
	mov r0, #0xc0
	strh r0, [r2, #4]
	strh r1, [r2, #2]
	strh r0, [r2, #6]
	ldr r0, _021E3AD8 ; =ov05_021E3ADC
	add r1, r4, #0
	lsr r2, r2, #0x10
	bl sub_0200CA98
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E3AD4: .word 0x04000040
_021E3AD8: .word ov05_021E3ADC

	thumb_func_start ov05_021E3ADC
ov05_021E3ADC: ; 0x021E3ADC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r2, #1
	ldr r0, _021E3B04 ; =ov05_021E3B0C
	add r4, r1, #0
	lsl r2, r2, #0xa
	bl sub_0200CA98
	str r0, [r4, #0x40]
	ldr r0, [r4, #0x38]
	ldr r1, _021E3B08 ; =ov05_021E3B74
	add r2, r4, #0
	bl ov05_021F4624
	str r0, [r4, #0x3c]
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
	nop
_021E3B04: .word ov05_021E3B0C
_021E3B08: .word ov05_021E3B74

	thumb_func_start ov05_021E3B0C
ov05_021E3B0C: ; 0x021E3B0C
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x34]
	cmp r0, #0
	beq _021E3B1C
	cmp r0, #1
	beq _021E3B68
	pop {r4, pc}
_021E3B1C:
	add r0, r4, #0
	add r0, #0x18
	bl ov05_021E36A4
	add r0, r4, #0
	bl ov05_021E36A4
	cmp r0, #0
	beq _021E3B34
	ldr r0, [r4, #0x34]
	add r0, r0, #1
	str r0, [r4, #0x34]
_021E3B34:
	ldr r0, [r4]
	asr r2, r0, #0xc
	ldr r0, [r4, #0x18]
	mov r4, #0xff
	asr r1, r0, #0xc
	ldr r0, _021E3B70 ; =0x04000040
	sub r3, r4, r2
	strh r3, [r0]
	mov r3, #0x60
	sub r3, r3, r1
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	strh r3, [r0, #4]
	lsl r3, r2, #8
	lsl r2, r4, #8
	and r2, r3
	orr r2, r4
	add r1, #0x60
	strh r2, [r0, #2]
	lsl r2, r1, #8
	lsl r1, r4, #8
	and r2, r1
	mov r1, #0xc0
	orr r1, r2
	strh r1, [r0, #6]
	pop {r4, pc}
_021E3B68:
	add r0, r4, #0
	bl ov05_021E3BA4
	pop {r4, pc}
	.balign 4, 0
_021E3B70: .word 0x04000040

	thumb_func_start ov05_021E3B74
ov05_021E3B74: ; 0x021E3B74
	ldr r0, _021E3B9C ; =0x04000006
	ldr r1, [r1, #0x30]
	ldrh r2, [r0]
	cmp r2, r1
	ldr r1, _021E3BA0 ; =0xFFFF1FFF
	bhi _021E3B8E
	sub r3, r0, #6
	ldr r2, [r3]
	lsr r0, r0, #0xd
	and r1, r2
	orr r0, r1
	str r0, [r3]
	bx lr
_021E3B8E:
	sub r3, r0, #6
	ldr r2, [r3]
	lsr r0, r0, #0xc
	and r1, r2
	orr r0, r1
	str r0, [r3]
	bx lr
	.balign 4, 0
_021E3B9C: .word 0x04000006
_021E3BA0: .word 0xFFFF1FFF

	thumb_func_start ov05_021E3BA4
ov05_021E3BA4: ; 0x021E3BA4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E3BF8 ; =0x04000048
	mov r2, #0x3f
	ldrh r3, [r0]
	mov r1, #0x1f
	bic r3, r2
	orr r3, r1
	mov r1, #0x20
	orr r3, r1
	strh r3, [r0]
	ldrh r3, [r0, #2]
	bic r3, r2
	add r2, r0, #0
	strh r3, [r0, #2]
	mov r3, #0
	sub r2, #8
	strh r3, [r2]
	sub r0, r0, #4
	strh r3, [r0]
	lsl r3, r1, #0x15
	ldr r2, [r3]
	ldr r0, _021E3BFC ; =0xFFFF1FFF
	and r2, r0
	lsl r0, r1, #8
	orr r0, r2
	str r0, [r3]
	ldr r0, [r4, #0x44]
	mov r1, #1
	str r1, [r0]
	ldr r0, [r4, #0x3c]
	bl ov05_021F4648
	mov r0, #0
	str r0, [r4, #0x3c]
	ldr r0, [r4, #0x40]
	bl sub_0200CAB4
	mov r0, #0
	str r0, [r4, #0x40]
	pop {r4, pc}
	nop
_021E3BF8: .word 0x04000048
_021E3BFC: .word 0xFFFF1FFF

	thumb_func_start ov05_021E3C00
ov05_021E3C00: ; 0x021E3C00
	ldr r3, _021E3C0C ; =sub_0200CA98
	mov r2, #1
	add r1, r0, #0
	ldr r0, _021E3C10 ; =ov05_021E3C14
	lsl r2, r2, #0xa
	bx r3
	.balign 4, 0
_021E3C0C: .word sub_0200CA98
_021E3C10: .word ov05_021E3C14

	thumb_func_start ov05_021E3C14
ov05_021E3C14: ; 0x021E3C14
	push {r3, r4, r5, r6, lr}
	sub sp, #0x64
	ldr r6, _021E3D10 ; =ov05_021F7464
	add r3, sp, #0x54
	add r5, r0, #0
	add r4, r1, #0
	add r2, r3, #0
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl SetBothScreensModesAndDisable
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	ldr r3, _021E3D14 ; =ov05_021F74AC
	add r2, sp, #0x38
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, #1
	str r0, [r2]
	add r0, r4, #0
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	mov r1, #1
	add r2, sp, #0x38
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #1
	mov r1, #0x20
	mov r2, #0
	mov r3, #4
	bl BG_ClearCharDataRange
	add r0, r4, #0
	mov r1, #1
	bl BgClearTilemapBufferAndCommit
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r3, _021E3D18 ; =ov05_021F7490
	add r2, sp, #0x1c
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, #2
	str r0, [r2]
	add r0, r4, #0
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	mov r1, #2
	add r2, sp, #0x1c
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #2
	mov r1, #0x20
	mov r2, #0
	mov r3, #4
	bl BG_ClearCharDataRange
	add r0, r4, #0
	mov r1, #2
	bl BgClearTilemapBufferAndCommit
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r3, _021E3D1C ; =ov05_021F7474
	add r2, sp, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, r4, #0
	mov r1, #3
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	mov r1, #3
	add r2, sp, #0
	mov r3, #1
	bl InitBgFromTemplate
	mov r0, #3
	mov r1, #0x20
	mov r2, #0
	mov r3, #4
	bl BG_ClearCharDataRange
	add r0, r4, #0
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	mov r0, #8
	mov r1, #0
	bl GX_EngineAToggleLayers
	add r0, r5, #0
	bl sub_0200CAB4
	add sp, #0x64
	pop {r3, r4, r5, r6, pc}
	nop
_021E3D10: .word ov05_021F7464
_021E3D14: .word ov05_021F74AC
_021E3D18: .word ov05_021F7490
_021E3D1C: .word ov05_021F7474

	thumb_func_start ov05_021E3D20
ov05_021E3D20: ; 0x021E3D20
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r3, #0
	mov r3, #0
	add r5, r0, #0
	add r6, r1, #0
	add r1, r2, #0
	str r3, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #0x70
	add r2, r3, #0
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	mov r0, #0x70
	add r1, r6, #0
	add r2, r4, #0
	mov r3, #3
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	mov r0, #0x70
	add r1, r5, #0
	add r2, r4, #0
	mov r3, #3
	bl GfGfxLoader_LoadScrnData
	add sp, #0x10
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021E3D70
ov05_021E3D70: ; 0x021E3D70
	push {r3, r4, lr}
	sub sp, #0xc
	add r3, r1, #0
	add r4, r0, #0
	add r0, r3, #4
	str r0, [sp]
	ldr r0, [r3, #0x18]
	mov r2, #0
	str r0, [sp, #4]
	ldr r0, [r3, #0x1c]
	str r0, [sp, #8]
	ldr r1, [r3, #0x14]
	ldr r0, [r3]
	lsl r1, r1, #0x18
	ldr r3, [r3, #0x20]
	lsr r1, r1, #0x18
	bl Bg_SetTextDimAndAffineParams
	add r0, r4, #0
	bl sub_0200CAB4
	add sp, #0xc
	pop {r3, r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021E3DA0
ov05_021E3DA0: ; 0x021E3DA0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r0, r5, #4
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl MTX_Identity22_
	add r0, sp, #8
	ldrh r0, [r0, #0x14]
	ldr r3, _021E3E0C ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, r5, #4
	bl MTX_Rot22_
	mov r0, #1
	lsl r0, r0, #0xc
	add r1, r7, #0
	bl FX_Div
	add r7, r0, #0
	mov r0, #1
	ldr r1, [sp, #0x18]
	lsl r0, r0, #0xc
	bl FX_Div
	add r3, r0, #0
	add r0, r5, #4
	add r1, r0, #0
	add r2, r7, #0
	bl MTX_ScaleApply22
	str r4, [r5]
	mov r2, #1
	ldr r0, [sp, #0x20]
	str r6, [r5, #0x14]
	str r0, [r5, #0x18]
	ldr r0, [sp, #0x24]
	add r1, r5, #0
	str r0, [r5, #0x1c]
	ldr r0, [sp, #0x28]
	lsl r2, r2, #0xa
	str r0, [r5, #0x20]
	ldr r0, _021E3E10 ; =ov05_021E3D70
	bl sub_0200CA98
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E3E0C: .word FX_SinCosTable_
_021E3E10: .word ov05_021E3D70

	thumb_func_start ov05_021E3E14
ov05_021E3E14: ; 0x021E3E14
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r2, #0
	add r0, r1, #0
	add r1, r5, #4
	mov r2, #4
	bl sub_02008C9C
	mov r7, #0x4b
	str r0, [r5]
	mov r4, #0
	lsl r7, r7, #2
_021E3E2C:
	add r0, r6, #0
	add r1, r4, #0
	mov r2, #4
	bl sub_02008DEC
	str r0, [r5, r7]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021E3E2C
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021E3E44
ov05_021E3E44: ; 0x021E3E44
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5]
	bl sub_0201FD58
	mov r6, #0x4b
	mov r4, #0
	lsl r6, r6, #2
_021E3E54:
	ldr r0, [r5, r6]
	bl sub_02008E2C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021E3E54
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021E3E64
ov05_021E3E64: ; 0x021E3E64
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	ldr r6, [sp, #0x54]
	add r4, r1, #0
	str r6, [sp]
	mov r1, #1
	add r5, r0, #0
	str r1, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0x4b
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	str r2, [sp, #0x2c]
	add r7, r3, #0
	ldr r0, [r5, r0]
	ldr r2, [sp, #0x48]
	mov r1, #0x70
	mov r3, #0
	bl sub_02008F90
	str r0, [r4]
	str r6, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r7, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	ldr r2, [sp, #0x2c]
	mov r1, #0x70
	mov r3, #0
	bl sub_02008FEC
	str r0, [r4, #4]
	str r6, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0x4d
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, [sp, #0x4c]
	mov r1, #0x70
	mov r3, #0
	bl sub_020090AC
	str r0, [r4, #8]
	str r6, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, [sp, #0x50]
	mov r1, #0x70
	mov r3, #0
	bl sub_020090AC
	str r0, [r4, #0xc]
	ldr r0, [r4]
	bl sub_02009B04
	ldr r0, [r4]
	bl sub_02009474
	ldr r0, [r4, #4]
	bl sub_02009D68
	mov r0, #0
	mov r2, #0x4b
	str r6, [sp]
	mvn r0, r0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	lsl r2, r2, #2
	ldr r1, [r5, r2]
	add r4, #0x10
	str r1, [sp, #0x14]
	add r1, r2, #4
	ldr r1, [r5, r1]
	add r3, r6, #0
	str r1, [sp, #0x18]
	add r1, r2, #0
	add r1, #8
	ldr r1, [r5, r1]
	add r2, #0xc
	str r1, [sp, #0x1c]
	ldr r1, [r5, r2]
	add r2, r6, #0
	str r1, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	add r0, r4, #0
	add r1, r6, #0
	bl sub_02008AA4
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021E3F3C
ov05_021E3F3C: ; 0x021E3F3C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	bl sub_02009C0C
	ldr r0, [r4, #4]
	bl sub_02009E04
	mov r7, #0x4b
	mov r6, #0
	lsl r7, r7, #2
_021E3F54:
	ldr r0, [r5, r7]
	ldr r1, [r4]
	bl sub_02009490
	add r6, r6, #1
	add r4, r4, #4
	add r5, r5, #4
	cmp r6, #4
	blt _021E3F54
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021E3F68
ov05_021E3F68: ; 0x021E3F68
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r4, r1, #0
	lsl r1, r2, #0x10
	add r6, r0, #0
	add r0, sp, #8
	lsr r1, r1, #0x10
	add r7, r3, #0
	bl sub_020690AC
	add r0, r4, #0
	mov r1, #0x20
	bl AllocFromHeap
	add r1, sp, #4
	add r5, r0, #0
	ldrh r0, [r1, #4]
	ldrh r1, [r1, #8]
	add r2, sp, #4
	add r3, r4, #0
	bl GfGfxLoader_GetPlttData
	add r4, r0, #0
	add r0, sp, #0x20
	ldrh r0, [r0, #0x10]
	add r1, r5, #0
	mov r2, #0x10
	str r0, [sp]
	ldr r0, [sp, #4]
	add r3, r7, #0
	ldr r0, [r0, #0xc]
	bl BlendPalette
	add r0, r6, #0
	add r1, r5, #0
	mov r2, #0x20
	bl ov05_021E40F0
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021E3FC4
ov05_021E3FC4: ; 0x021E3FC4
	push {r4, lr}
	sub sp, #0x20
	ldr r0, [r0]
	add r1, #0x10
	str r0, [sp]
	ldr r0, [sp, #0x28]
	str r1, [sp, #4]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x2c]
	str r2, [sp, #8]
	str r0, [sp, #0x14]
	mov r0, #1
	str r0, [sp, #0x18]
	mov r0, #4
	str r0, [sp, #0x1c]
	add r0, sp, #0
	str r3, [sp, #0xc]
	bl sub_0201FF84
	add r4, r0, #0
	bne _021E3FF2
	bl GF_AssertFail
_021E3FF2:
	add r0, r4, #0
	add sp, #0x20
	pop {r4, pc}

	thumb_func_start ov05_021E3FF8
ov05_021E3FF8: ; 0x021E3FF8
	push {r4}
	sub sp, #0xc
	str r2, [sp, #4]
	str r3, [sp, #8]
	add r2, sp, #0
	add r4, r0, #0
	str r1, [sp]
	ldmia r2!, {r0, r1}
	stmia r4!, {r0, r1}
	ldr r0, [r2]
	str r0, [r4]
	add sp, #0xc
	pop {r4}
	bx lr

	thumb_func_start ov05_021E4014
ov05_021E4014: ; 0x021E4014
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r4, r2, #0
	add r5, r1, #0
	lsl r1, r4, #0x10
	add r6, r0, #0
	add r0, sp, #0x10
	lsr r1, r1, #0x10
	add r7, r3, #0
	bl sub_020690AC
	str r5, [sp]
	add r1, sp, #8
	ldrh r0, [r1, #8]
	ldrh r1, [r1, #0xa]
	mov r2, #0
	add r3, sp, #0xc
	bl GfGfxLoader_GetCharData
	str r0, [sp, #4]
	ldr r0, [sp, #0xc]
	ldr r0, [r0, #0x14]
	bl sub_02008A74
	add r0, sp, #0x28
	ldrh r0, [r0, #0x10]
	add r1, r5, #0
	add r2, r4, #0
	str r0, [sp]
	add r0, r6, #0
	add r3, r7, #0
	bl ov05_021E3F68
	ldr r0, [sp, #0xc]
	ldr r3, [sp, #0x3c]
	add r1, r5, #0
	add r2, sp, #8
	bl ov05_021E4080
	add r4, r0, #0
	ldr r2, [sp, #8]
	add r0, r6, #0
	add r1, r4, #0
	bl ov05_021E4118
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [sp, #4]
	bl FreeToHeap
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4080
ov05_021E4080: ; 0x021E4080
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp]
	ldr r4, [r0, #0x14]
	add r0, r1, #0
	mov r1, #2
	lsl r1, r1, #0xa
	str r2, [sp, #4]
	add r5, r3, #0
	bl AllocFromHeap
	mov ip, r0
	lsl r0, r5, #2
	mov r7, #0
	add r6, r4, r0
_021E409E:
	ldr r0, [sp]
	mov r2, #0
	ldrh r0, [r0, #2]
	add r3, r7, #0
	lsr r1, r7, #0x1f
	lsl r5, r7, #0x1d
	mul r3, r0
	sub r5, r5, r1
	mov r0, #0x1d
	ror r5, r0
	asr r0, r7, #2
	lsr r0, r0, #0x1d
	add r0, r7, r0
	asr r0, r0, #3
	add r1, r1, r5
	lsl r0, r0, #6
	add r0, r1, r0
	lsl r1, r0, #2
	mov r0, ip
	add r4, r2, #0
	add r5, r0, r1
_021E40C8:
	add r0, r3, r2
	lsl r0, r0, #2
	ldr r1, [r6, r0]
	lsl r0, r4, #2
	add r2, r2, #1
	add r4, #8
	str r1, [r5, r0]
	cmp r2, #8
	blt _021E40C8
	add r7, r7, #1
	cmp r7, #0x40
	blt _021E409E
	mov r1, #2
	ldr r0, [sp, #4]
	lsl r1, r1, #0xa
	str r1, [r0]
	mov r0, ip
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021E40F0
ov05_021E40F0: ; 0x021E40F0
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	bl sub_02020354
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl DC_FlushRange
	add r0, r6, #0
	mov r1, #1
	bl NNS_G2dGetImagePaletteLocation
	add r1, r0, #0
	add r0, r5, #0
	add r2, r4, #0
	bl GX_LoadOBJPltt
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021E4118
ov05_021E4118: ; 0x021E4118
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	bl sub_02020350
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl DC_FlushRange
	add r0, r6, #0
	mov r1, #1
	bl NNS_G2dGetImageLocation
	add r1, r0, #0
	add r0, r5, #0
	add r2, r4, #0
	bl GX_LoadOBJ
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021E4140
ov05_021E4140: ; 0x021E4140
	push {r4, lr}
	mov r1, #0x30
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x30
	add r4, r0, #0
	bl memset
	add r0, r4, #0
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4158
ov05_021E4158: ; 0x021E4158
	ldr r3, _021E415C ; =FreeToHeap
	bx r3
	.balign 4, 0
_021E415C: .word FreeToHeap

	thumb_func_start ov05_021E4160
ov05_021E4160: ; 0x021E4160
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r0, #0x2e
	ldrb r0, [r0]
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	cmp r0, #0
	beq _021E4176
	bl GF_AssertFail
_021E4176:
	ldr r3, [sp, #0x1c]
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov05_021E35B0
	add r0, r5, #0
	ldr r2, [sp, #0x18]
	ldr r3, [sp, #0x1c]
	add r0, #0x14
	add r1, r7, #0
	bl ov05_021E35B0
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x24]
	str r0, [r5, #0x28]
	add r0, r5, #0
	add r0, #0x2c
	strb r1, [r0]
	add r0, r5, #0
	ldr r1, [sp, #0x28]
	add r0, #0x2d
	strb r1, [r0]
	add r0, sp, #0x2c
	ldrb r1, [r0]
	add r0, r5, #0
	add r0, #0x2f
	strb r1, [r0]
	mov r0, #1
	add r5, #0x2e
	strb r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021E41B8
ov05_021E41B8: ; 0x021E41B8
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	add r1, r5, #0
	add r1, #0x2e
	ldrb r1, [r1]
	cmp r1, #0
	bne _021E41CE
	add sp, #8
	mov r0, #1
	pop {r4, r5, r6, pc}
_021E41CE:
	bl ov05_021E35C0
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0x14
	bl ov05_021E35C0
	add r0, r5, #0
	add r0, #0x2c
	ldrb r0, [r0]
	ldr r2, [r5]
	ldr r6, [r5, #0x14]
	lsr r1, r0, #1
	sub r1, r2, r1
	lsl r1, r1, #0x10
	asr r3, r1, #0x10
	add r1, r5, #0
	add r1, #0x2d
	ldrb r2, [r1]
	add r0, r3, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	lsr r1, r2, #1
	str r0, [sp]
	add r0, r5, #0
	sub r1, r6, r1
	add r0, #0x2f
	lsl r1, r1, #0x10
	ldrb r0, [r0]
	asr r1, r1, #0x10
	add r2, r1, r2
	str r0, [sp, #4]
	lsl r2, r2, #0x10
	ldr r0, [r5, #0x28]
	asr r2, r2, #0x10
	bl ov05_021E4338
	add r0, r4, #0
	add sp, #8
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4220
ov05_021E4220: ; 0x021E4220
	push {r4, lr}
	mov r1, #0x30
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x30
	add r4, r0, #0
	bl memset
	add r0, r4, #0
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4238
ov05_021E4238: ; 0x021E4238
	ldr r3, _021E423C ; =FreeToHeap
	bx r3
	.balign 4, 0
_021E423C: .word FreeToHeap

	thumb_func_start ov05_021E4240
ov05_021E4240: ; 0x021E4240
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r0, #0x2e
	ldrb r0, [r0]
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	cmp r0, #0
	beq _021E4256
	bl GF_AssertFail
_021E4256:
	ldr r3, [sp, #0x1c]
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov05_021E35B0
	add r0, r5, #0
	ldr r2, [sp, #0x18]
	ldr r3, [sp, #0x1c]
	add r0, #0x14
	add r1, r7, #0
	bl ov05_021E35B0
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x24]
	str r0, [r5, #0x28]
	add r0, r5, #0
	add r0, #0x2c
	strb r1, [r0]
	add r0, r5, #0
	ldr r1, [sp, #0x28]
	add r0, #0x2d
	strb r1, [r0]
	add r0, sp, #0x2c
	ldrb r1, [r0]
	add r0, r5, #0
	add r0, #0x2f
	strb r1, [r0]
	mov r0, #1
	add r5, #0x2e
	strb r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4298
ov05_021E4298: ; 0x021E4298
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	add r0, #0x2e
	ldrb r0, [r0]
	cmp r0, #0
	bne _021E42AC
	add sp, #8
	mov r0, #1
	pop {r4, r5, r6, pc}
_021E42AC:
	add r0, r5, #0
	add r0, #0x2c
	ldrb r0, [r0]
	ldr r2, [r5]
	ldr r4, [r5, #0x14]
	lsr r1, r0, #1
	sub r1, r2, r1
	lsl r1, r1, #0x10
	asr r3, r1, #0x10
	add r1, r5, #0
	add r1, #0x2d
	ldrb r2, [r1]
	add r0, r3, r0
	lsl r0, r0, #0x10
	lsr r1, r2, #1
	sub r1, r4, r1
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	asr r0, r0, #0x10
	str r0, [sp]
	mov r0, #0
	add r2, r1, r2
	str r0, [sp, #4]
	lsl r2, r2, #0x10
	ldr r0, [r5, #0x28]
	asr r2, r2, #0x10
	bl ov05_021E4338
	add r0, r5, #0
	bl ov05_021E35C0
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0x14
	bl ov05_021E35C0
	add r0, r5, #0
	add r0, #0x2c
	ldrb r0, [r0]
	ldr r2, [r5]
	ldr r6, [r5, #0x14]
	lsr r1, r0, #1
	sub r1, r2, r1
	lsl r1, r1, #0x10
	asr r3, r1, #0x10
	add r1, r5, #0
	add r1, #0x2d
	ldrb r2, [r1]
	add r0, r3, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	lsr r1, r2, #1
	str r0, [sp]
	add r0, r5, #0
	sub r1, r6, r1
	add r0, #0x2f
	lsl r1, r1, #0x10
	ldrb r0, [r0]
	asr r1, r1, #0x10
	add r2, r1, r2
	str r0, [sp, #4]
	lsl r2, r2, #0x10
	ldr r0, [r5, #0x28]
	asr r2, r2, #0x10
	bl ov05_021E4338
	add r0, r4, #0
	add sp, #8
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4338
ov05_021E4338: ; 0x021E4338
	push {r3, r4, r5, lr}
	sub sp, #8
	ldr r5, [sp, #0x18]
	add r4, r1, #0
	cmp r5, #0
	ble _021E4390
	cmp r2, #0
	ble _021E4390
	cmp r3, r5
	beq _021E4390
	cmp r4, r2
	beq _021E4390
	cmp r3, #0
	bge _021E4356
	mov r3, #0
_021E4356:
	mov r1, #1
	lsl r1, r1, #8
	cmp r5, r1
	ble _021E4360
	add r5, r1, #0
_021E4360:
	cmp r4, #0
	bge _021E4366
	mov r4, #0
_021E4366:
	mov r1, #1
	lsl r1, r1, #8
	cmp r2, r1
	ble _021E4370
	add r2, r1, #0
_021E4370:
	sub r1, r5, r3
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	str r1, [sp]
	sub r1, r2, r4
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	str r1, [sp, #4]
	lsl r2, r3, #0x10
	add r1, sp, #8
	lsl r3, r4, #0x10
	ldrb r1, [r1, #0x14]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl FillWindowPixelRect
_021E4390:
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021E4394
ov05_021E4394: ; 0x021E4394
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #4
	mov r1, #0xcc
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0xcc
	add r7, r0, #0
	bl memset
	mov r4, #0
	add r5, r7, #0
_021E43AE:
	add r0, r6, #0
	bl ov05_021E4220
	str r0, [r5, #4]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x30
	blt _021E43AE
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021E43C4
ov05_021E43C4: ; 0x021E43C4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_021E43CC:
	ldr r0, [r5, #4]
	bl ov05_021E4238
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x30
	blt _021E43CC
	add r0, r6, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021E43E4
ov05_021E43E4: ; 0x021E43E4
	push {r3, r4}
	str r3, [r0]
	ldr r3, _021E4420 ; =0xFFFFFFF8
	add r3, sp
	ldrb r4, [r3, #0x10]
	add r3, r0, #0
	add r3, #0xc9
	strb r4, [r3]
	add r3, r0, #0
	add r3, #0xc6
	strb r1, [r3]
	add r1, r0, #0
	add r1, #0xc7
	strb r2, [r1]
	add r1, r0, #0
	mov r2, #0
	add r1, #0xc4
	strb r2, [r1]
	add r1, r0, #0
	add r1, #0xc5
	strb r2, [r1]
	add r1, r0, #0
	add r1, #0xc8
	strb r2, [r1]
	mov r1, #1
	add r0, #0xca
	strb r1, [r0]
	pop {r3, r4}
	bx lr
	nop
_021E4420: .word 0xFFFFFFF8

	thumb_func_start ov05_021E4424
ov05_021E4424: ; 0x021E4424
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r6, r0, #0
	add r0, #0xca
	ldrb r0, [r0]
	cmp r0, #0
	bne _021E4438
	add sp, #0x1c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021E4438:
	add r0, r6, #0
	add r0, #0xc4
	ldrb r0, [r0]
	cmp r0, #0x30
	bhs _021E44BC
	mov r1, #0xc8
	ldrsb r0, [r6, r1]
	sub r2, r0, #1
	add r0, r6, #0
	add r0, #0xc8
	strb r2, [r0]
	ldrsb r0, [r6, r1]
	cmp r0, #0
	bgt _021E44BC
	add r0, r6, #0
	add r0, #0xc7
	ldrb r1, [r0]
	add r0, r6, #0
	add r0, #0xc8
	strb r1, [r0]
	add r0, r6, #0
	add r0, #0xc4
	ldrb r0, [r0]
	mov r1, #0x1d
	lsr r3, r0, #0x1f
	lsl r2, r0, #0x1d
	sub r2, r2, r3
	ror r2, r1
	add r2, r3, r2
	ldr r1, _021E4518 ; =ov05_021F745C
	mov r3, #0x20
	ldrb r1, [r1, r2]
	lsr r2, r0, #3
	lsl r4, r2, #5
	mov r2, #0xb0
	sub r2, r2, r4
	str r2, [sp]
	add r2, r6, #0
	add r2, #0xc6
	ldrb r2, [r2]
	lsl r0, r0, #2
	lsl r1, r1, #5
	str r2, [sp, #4]
	ldr r2, [r6]
	add r0, r6, r0
	str r2, [sp, #8]
	str r3, [sp, #0xc]
	add r2, r6, #0
	str r3, [sp, #0x10]
	add r2, #0xc9
	ldrb r2, [r2]
	sub r3, #0x30
	add r1, #0x10
	str r2, [sp, #0x14]
	ldr r0, [r0, #4]
	add r2, r1, #0
	sub r3, r3, r4
	bl ov05_021E4240
	add r0, r6, #0
	add r0, #0xc4
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r6, #0
	add r0, #0xc4
	strb r1, [r0]
_021E44BC:
	add r0, r6, #0
	add r0, #0xc5
	ldrb r4, [r0]
	add r0, r6, #0
	add r0, #0xc4
	ldrb r0, [r0]
	cmp r4, r0
	bge _021E44F4
	lsl r0, r4, #2
	add r7, r6, #0
	add r5, r6, r0
	add r7, #0xc5
_021E44D4:
	ldr r0, [r5, #4]
	bl ov05_021E4298
	str r0, [sp, #0x18]
	cmp r0, #1
	bne _021E44E6
	ldrb r0, [r7]
	add r0, r0, #1
	strb r0, [r7]
_021E44E6:
	add r0, r6, #0
	add r0, #0xc4
	ldrb r0, [r0]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blt _021E44D4
_021E44F4:
	add r0, r6, #0
	add r0, #0xc5
	ldrb r0, [r0]
	cmp r0, #0x30
	blo _021E4510
	ldr r0, [sp, #0x18]
	cmp r0, #1
	bne _021E4510
	mov r0, #0
	add r6, #0xca
	strb r0, [r6]
	add sp, #0x1c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021E4510:
	mov r0, #0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021E4518: .word ov05_021F745C

	thumb_func_start ov05_021E451C
ov05_021E451C: ; 0x021E451C
	push {r3, lr}
	mov r1, #0x1c
	bl AllocFromHeap
	add r3, r0, #0
	mov r2, #0x1c
	mov r1, #0
_021E452A:
	strb r1, [r3]
	add r3, r3, #1
	sub r2, r2, #1
	bne _021E452A
	pop {r3, pc}

	thumb_func_start ov05_021E4534
ov05_021E4534: ; 0x021E4534
	ldr r3, _021E4538 ; =FreeToHeap
	bx r3
	.balign 4, 0
_021E4538: .word FreeToHeap

	thumb_func_start ov05_021E453C
ov05_021E453C: ; 0x021E453C
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [sp, #8]
	str r1, [r0]
	ldr r1, _021E4560 ; =0xFFFFFFF8
	add r1, sp
	ldrb r1, [r1, #0x14]
	strb r1, [r0, #0x19]
	mov r1, #1
	strb r1, [r0, #0x18]
	add r1, r2, #0
	add r2, r3, #0
	add r0, r0, #4
	add r3, r4, #0
	bl ov05_021E35B0
	pop {r4, pc}
	nop
_021E4560: .word 0xFFFFFFF8

	thumb_func_start ov05_021E4564
ov05_021E4564: ; 0x021E4564
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldrb r0, [r5, #0x18]
	cmp r0, #0
	bne _021E4572
	mov r0, #1
	pop {r4, r5, r6, pc}
_021E4572:
	ldr r0, [r5, #4]
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r5, #4
	bl ov05_021E35C0
	ldr r2, [r5, #4]
	add r6, r0, #0
	lsl r2, r2, #0x10
	ldrb r3, [r5, #0x19]
	ldr r0, [r5]
	add r1, r4, #0
	lsr r2, r2, #0x10
	bl ov05_021E45A0
	cmp r6, #1
	bne _021E459C
	mov r0, #0
	strb r0, [r5, #0x18]
	mov r0, #1
	pop {r4, r5, r6, pc}
_021E459C:
	mov r0, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021E45A0
ov05_021E45A0: ; 0x021E45A0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r0, [sp, #8]
	asr r0, r2, #4
	add r4, r1, #0
	lsl r1, r0, #1
	lsl r0, r1, #1
	ldr r2, _021E4680 ; =FX_SinCosTable_
	add r1, r1, #1
	lsl r1, r1, #1
	ldrsh r0, [r2, r0]
	ldrsh r1, [r2, r1]
	str r3, [sp, #0xc]
	bl FX_Div
	str r0, [sp, #0x18]
	asr r0, r4, #4
	lsl r1, r0, #1
	lsl r0, r1, #1
	ldr r2, _021E4680 ; =FX_SinCosTable_
	add r1, r1, #1
	lsl r1, r1, #1
	ldrsh r0, [r2, r0]
	ldrsh r1, [r2, r1]
	bl FX_Div
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x18]
	mov r5, #0
	asr r0, r0, #0x1f
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x10]
	asr r0, r0, #0x1f
	str r0, [sp, #0x14]
_021E45E4:
	mov r0, #0x5f
	sub r0, r0, r5
	lsl r6, r0, #0xc
	asr r4, r6, #0x1f
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	add r2, r6, #0
	add r3, r4, #0
	bl _ll_mul
	mov r2, #2
	lsl r2, r2, #0xa
	add r2, r0, r2
	ldr r0, _021E4684 ; =0x00000000
	adc r1, r0
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	asr r7, r1, #0xc
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r2, r6, #0
	add r3, r4, #0
	bl _ll_mul
	mov r2, #2
	lsl r2, r2, #0xa
	add r2, r0, r2
	ldr r0, _021E4684 ; =0x00000000
	adc r1, r0
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	asr r0, r1, #0xc
	mov r1, #0x80
	add r4, r7, #0
	add r6, r0, #0
	mov r2, #0x80
	sub r0, r2, r0
	sub r1, r1, r7
	add r4, #0x80
	add r6, #0x80
	add r3, r0, #0
	cmp r0, r1
	ble _021E4642
	add r3, r1, #0
	add r1, r0, #0
_021E4642:
	cmp r6, r4
	ble _021E464C
	add r0, r6, #0
	add r6, r4, #0
	add r4, r0, #0
_021E464C:
	add r0, r1, #1
	str r0, [sp]
	ldr r0, [sp, #0xc]
	add r1, r5, #0
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	add r2, r5, #1
	bl ov05_021E4338
	add r0, r4, #1
	str r0, [sp]
	ldr r0, [sp, #0xc]
	mov r1, #0xbf
	str r0, [sp, #4]
	mov r2, #0xc0
	ldr r0, [sp, #8]
	sub r1, r1, r5
	sub r2, r2, r5
	add r3, r6, #0
	bl ov05_021E4338
	add r5, r5, #1
	cmp r5, #0x60
	blt _021E45E4
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E4680: .word FX_SinCosTable_
_021E4684: .word 0x00000000

	thumb_func_start ov05_021E4688
ov05_021E4688: ; 0x021E4688
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0x24
	add r6, r0, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x24
	add r7, r0, #0
	bl memset
	mov r4, #0
	add r5, r7, #0
_021E46A0:
	add r0, r6, #0
	bl ov05_021E451C
	add r4, r4, #1
	stmia r5!, {r0}
	cmp r4, #8
	blt _021E46A0
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021E46B4
ov05_021E46B4: ; 0x021E46B4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_021E46BC:
	ldr r0, [r5]
	bl ov05_021E4534
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #8
	blt _021E46BC
	add r0, r6, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021E46D4
ov05_021E46D4: ; 0x021E46D4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r1, [sp, #0xc]
	ldr r4, _021E474C ; =ov05_021F74C8
	str r0, [sp, #8]
	str r2, [sp, #0x10]
	str r3, [sp, #0x14]
	mov r6, #0
	add r5, r0, #0
_021E46E6:
	ldrh r1, [r4]
	ldr r0, _021E4750 ; =0x0000FFFF
	mul r0, r1
	mov r1, #0x5a
	lsl r1, r1, #2
	bl _s32_div_f
	add r7, r0, #0
	ldrh r1, [r4, #2]
	ldr r0, _021E4750 ; =0x0000FFFF
	mul r0, r1
	mov r1, #0x5a
	lsl r1, r1, #2
	bl _s32_div_f
	add r3, r0, #0
	ldr r0, [sp, #0x10]
	lsl r2, r7, #0x10
	str r0, [sp]
	ldr r0, [sp, #0x14]
	lsl r3, r3, #0x10
	str r0, [sp, #4]
	ldr r0, [r5]
	ldr r1, [sp, #0xc]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl ov05_021E453C
	add r6, r6, #1
	add r4, r4, #4
	add r5, r5, #4
	cmp r6, #8
	blt _021E46E6
	ldr r0, [sp, #8]
	mov r1, #1
	add r0, #0x20
	strb r1, [r0]
	add r1, #0xff
	str r1, [sp]
	str r0, [sp, #8]
	ldr r0, [sp, #0x14]
	mov r1, #0x5d
	str r0, [sp, #4]
	ldr r0, [sp, #0x10]
	mov r2, #0x63
	mov r3, #0
	bl ov05_021E4338
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E474C: .word ov05_021F74C8
_021E4750: .word 0x0000FFFF

	thumb_func_start ov05_021E4754
ov05_021E4754: ; 0x021E4754
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #0
	bne _021E4764
	mov r0, #1
	pop {r4, r5, r6, pc}
_021E4764:
	mov r4, #0
	add r5, r6, #0
_021E4768:
	ldr r0, [r5]
	bl ov05_021E4564
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #8
	blt _021E4768
	cmp r0, #1
	bne _021E4784
	mov r0, #0
	add r6, #0x20
	strb r0, [r6]
	mov r0, #1
	pop {r4, r5, r6, pc}
_021E4784:
	mov r0, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021E4788
ov05_021E4788: ; 0x021E4788
	push {r4, lr}
	mov r0, #4
	mov r1, #0xe8
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0xe8
	add r4, r0, #0
	bl memset
	add r0, r4, #0
	pop {r4, pc}

	thumb_func_start ov05_021E47A0
ov05_021E47A0: ; 0x021E47A0
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	add r1, #0xe0
	ldr r1, [r1]
	cmp r1, #0
	beq _021E47B2
	bl ov05_021E4918
_021E47B2:
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021E47BC
ov05_021E47BC: ; 0x021E47BC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldr r0, [sp, #0x18]
	add r6, r1, #0
	str r0, [sp, #0x18]
	add r0, r6, #0
	add r0, #0xe0
	ldr r0, [r0]
	add r7, r2, #0
	add r5, r3, #0
	cmp r0, #0
	beq _021E47D8
	bl GF_AssertFail
_021E47D8:
	mov r1, #0
	str r1, [r4, #0x18]
	ldr r0, [r4, #0x10]
	add r4, #0x18
	ldr r0, [r0, #4]
	add r3, r7, #0
	ldr r2, [r0, #0x1c]
	add r0, r6, #0
	add r0, #0xd8
	str r2, [r0]
	add r0, r6, #0
	str r1, [r6, #0x14]
	add r0, #0xe4
	str r4, [r0]
	add r0, r6, #0
	mov r2, #0xff
	bl ov05_021E35B0
	mov r4, #0
_021E47FE:
	add r0, r4, #0
	add r1, r5, #0
	bl _u32_div_f
	ldr r0, [sp, #0x18]
	mul r0, r1
	add r1, r5, #0
	bl _u32_div_f
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl _u32_div_f
	mov r1, #1
	tst r0, r1
	bne _021E4826
	add r0, r6, r4
	strb r7, [r0, #0x18]
	b _021E482E
_021E4826:
	ldr r0, [sp, #0x18]
	sub r1, r0, r7
	add r0, r6, r4
	strb r1, [r0, #0x18]
_021E482E:
	add r4, r4, #1
	cmp r4, #0xc0
	blt _021E47FE
	ldr r0, _021E4878 ; =0x04000048
	mov r1, #0x3f
	ldrh r3, [r0]
	ldr r2, [sp, #0x1c]
	bic r3, r1
	orr r3, r2
	mov r2, #0x20
	orr r3, r2
	strh r3, [r0]
	ldrh r3, [r0, #2]
	bic r3, r1
	ldr r1, [sp, #0x20]
	orr r1, r3
	strh r1, [r0, #2]
	add r1, r0, #0
	mov r3, #0
	sub r1, #8
	strh r3, [r1]
	mov r1, #0xc0
	sub r0, r0, #4
	strh r1, [r0]
	lsl r3, r2, #0x15
	ldr r1, [r3]
	ldr r0, _021E487C ; =0xFFFF1FFF
	and r1, r0
	lsl r0, r2, #8
	orr r0, r1
	str r0, [r3]
	ldr r0, _021E4880 ; =ov05_021E4884
	add r1, r6, #0
	lsl r2, r2, #5
	bl sub_0200CA98
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E4878: .word 0x04000048
_021E487C: .word 0xFFFF1FFF
_021E4880: .word ov05_021E4884

	thumb_func_start ov05_021E4884
ov05_021E4884: ; 0x021E4884
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0xd8
	ldr r0, [r0]
	ldr r1, _021E48B8 ; =ov05_021E48EC
	add r2, r4, #0
	bl ov05_021F4624
	add r1, r4, #0
	add r1, #0xdc
	str r0, [r1]
	mov r2, #1
	ldr r0, _021E48BC ; =ov05_021E48C0
	add r1, r4, #0
	lsl r2, r2, #0xa
	bl sub_0200CA98
	add r4, #0xe0
	str r0, [r4]
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
	nop
_021E48B8: .word ov05_021E48EC
_021E48BC: .word ov05_021E48C0

	thumb_func_start ov05_021E48C0
ov05_021E48C0: ; 0x021E48C0
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021E48D0
	cmp r0, #1
	beq _021E48E2
	pop {r4, pc}
_021E48D0:
	add r0, r4, #0
	bl ov05_021E35C0
	cmp r0, #1
	bne _021E48E8
	ldr r0, [r4, #0x14]
	add r0, r0, #1
	str r0, [r4, #0x14]
	pop {r4, pc}
_021E48E2:
	add r0, r4, #0
	bl ov05_021E4918
_021E48E8:
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021E48EC
ov05_021E48EC: ; 0x021E48EC
	ldr r0, _021E4910 ; =0x04000006
	ldrh r0, [r0]
	cmp r0, #0xc0
	bge _021E490E
	add r0, r1, r0
	ldrb r0, [r0, #0x18]
	ldr r2, [r1]
	add r0, r2, r0
	cmp r0, #0xff
	ble _021E4902
	mov r0, #0xff
_021E4902:
	lsl r0, r0, #0x18
	ldr r1, _021E4914 ; =0x04000040
	lsr r0, r0, #0x18
	strh r0, [r1]
	mov r0, #0xc0
	strh r0, [r1, #4]
_021E490E:
	bx lr
	.balign 4, 0
_021E4910: .word 0x04000006
_021E4914: .word 0x04000040

	thumb_func_start ov05_021E4918
ov05_021E4918: ; 0x021E4918
	push {r4, lr}
	mov r2, #1
	lsl r2, r2, #0x1a
	add r4, r0, #0
	ldr r1, [r2]
	ldr r0, _021E4958 ; =0xFFFF1FFF
	and r0, r1
	str r0, [r2]
	add r0, r4, #0
	add r0, #0xe4
	ldr r0, [r0]
	mov r1, #1
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xdc
	ldr r0, [r0]
	bl ov05_021F4648
	add r0, r4, #0
	mov r1, #0
	add r0, #0xdc
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xe0
	ldr r0, [r0]
	bl sub_0200CAB4
	mov r0, #0
	add r4, #0xe0
	str r0, [r4]
	pop {r4, pc}
	nop
_021E4958: .word 0xFFFF1FFF

	thumb_func_start ov05_021E495C
ov05_021E495C: ; 0x021E495C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5]
	mov r6, #1
	add r1, r0, #0
	tst r1, r6
	bne _021E4980
	mov r1, #0x72
	lsl r1, r1, #4
	tst r1, r0
	bne _021E4976
	cmp r0, #0
	bne _021E497A
_021E4976:
	mov r6, #0
	b _021E4980
_021E497A:
	bl GF_AssertFail
	mov r6, #0
_021E4980:
	ldr r0, [r5, #4]
	bl GetFirstAliveMonInParty_CrashIfNone
	add r7, r0, #0
	ldr r0, [r5, #8]
	bl GetFirstAliveMonInParty_CrashIfNone
	str r0, [sp]
	add r0, r7, #0
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	add r7, r0, #0
	ldr r0, [sp]
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	mov r1, #0x55
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	sub r0, r0, r7
	cmp r1, #0xc
	bhi _021E49E2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E49BE: ; jump table
	.short _021E49D8 - _021E49BE - 2 ; case 0
	.short _021E49D8 - _021E49BE - 2 ; case 1
	.short _021E49D8 - _021E49BE - 2 ; case 2
	.short _021E49D8 - _021E49BE - 2 ; case 3
	.short _021E49D8 - _021E49BE - 2 ; case 4
	.short _021E49E0 - _021E49BE - 2 ; case 5
	.short _021E49D8 - _021E49BE - 2 ; case 6
	.short _021E49DC - _021E49BE - 2 ; case 7
	.short _021E49D8 - _021E49BE - 2 ; case 8
	.short _021E49D8 - _021E49BE - 2 ; case 9
	.short _021E49D8 - _021E49BE - 2 ; case 10
	.short _021E49D8 - _021E49BE - 2 ; case 11
	.short _021E49D8 - _021E49BE - 2 ; case 12
_021E49D8:
	mov r4, #0
	b _021E49E2
_021E49DC:
	mov r4, #2
	b _021E49E2
_021E49E0:
	mov r4, #4
_021E49E2:
	cmp r0, #0
	ble _021E49E8
	add r4, r4, #1
_021E49E8:
	mov r0, #6
	mul r0, r6
	add r0, r4, r0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021E49F0
ov05_021E49F0: ; 0x021E49F0
	push {r4, r5, r6, lr}
	ldr r4, [sp, #0x14]
	add r5, r0, #0
	mov r0, #0
	strb r0, [r4]
	mov r0, #0xff
	strb r0, [r4, #1]
	lsl r0, r3, #0xc
	add r6, r1, #0
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #2
	add r3, r0, #0
	asr r0, r5, #0xc
	mov r5, #0
	lsl r2, r2, #0xa
	add r3, r3, r2
	adc r1, r5
	lsl r1, r1, #0x14
	lsr r3, r3, #0xc
	orr r3, r1
	asr r3, r3, #0xc
	lsr r1, r3, #0x1f
	add r1, r3, r1
	asr r1, r1, #1
	sub r0, r0, r1
	strb r0, [r4, #2]
	ldr r0, _021E4A38 ; =ov05_021E4A64
	add r1, r4, #0
	lsr r2, r2, #1
	strb r6, [r4, #3]
	bl sub_0200CA98
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021E4A38: .word ov05_021E4A64

	thumb_func_start ov05_021E4A3C
ov05_021E4A3C: ; 0x021E4A3C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	lsl r0, r2, #0xc
	add r4, r1, #0
	asr r1, r0, #0x1f
	asr r3, r5, #0x1f
	add r2, r5, #0
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	asr r0, r1, #0xc
	add r0, r4, r0
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021E4A64
ov05_021E4A64: ; 0x021E4A64
	push {r3, r4, r5, lr}
	ldrb r2, [r1, #4]
	ldrb r3, [r1, #3]
	cmp r2, #0
	bne _021E4A8C
	ldrb r4, [r1]
	ldrb r2, [r1, #2]
	ldrb r1, [r1, #1]
	lsl r5, r4, #8
	mov r4, #0xff
	lsl r4, r4, #8
	and r5, r4
	orr r5, r1
	ldr r1, _021E4AB0 ; =0x04000040
	lsl r2, r2, #8
	and r2, r4
	strh r5, [r1]
	orr r2, r3
	strh r2, [r1, #4]
	b _021E4AA8
_021E4A8C:
	ldrb r4, [r1]
	ldrb r2, [r1, #2]
	ldrb r1, [r1, #1]
	lsl r5, r4, #8
	mov r4, #0xff
	lsl r4, r4, #8
	and r5, r4
	orr r5, r1
	ldr r1, _021E4AB4 ; =0x04000042
	lsl r2, r2, #8
	and r2, r4
	strh r5, [r1]
	orr r2, r3
	strh r2, [r1, #4]
_021E4AA8:
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
	nop
_021E4AB0: .word 0x04000040
_021E4AB4: .word 0x04000042

	thumb_func_start ov05_021E4AB8
ov05_021E4AB8: ; 0x021E4AB8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E4ACC ; =0x0400006C
	ldr r1, [r1]
	bl GXx_SetMasterBrightness_
	add r0, r4, #0
	bl sub_0200CAB4
	pop {r4, pc}
	.balign 4, 0
_021E4ACC: .word 0x0400006C

	thumb_func_start ov05_021E4AD0
ov05_021E4AD0: ; 0x021E4AD0
	ldr r3, _021E4ADC ; =sub_0200CA98
	mov r2, #1
	add r1, r0, #0
	ldr r0, _021E4AE0 ; =ov05_021E4AB8
	lsl r2, r2, #0xa
	bx r3
	.balign 4, 0
_021E4ADC: .word sub_0200CA98
_021E4AE0: .word ov05_021E4AB8

	.section .rodata

	.global ov05_021F745C
ov05_021F745C: ; 0x021F745C
	.byte 0x00, 0x02, 0x05, 0x07, 0x01, 0x06, 0x03, 0x04

	.global ov05_021F7464
ov05_021F7464: ; 0x021F7464
	.word 0x00000001, 0x00000001, 0x00000000, 0x00000001

	.global ov05_021F7474
ov05_021F7474: ; 0x021F7474
	.word 0x00000000, 0x00000000, 0x00000800, 0x00000000
	.word 0x001F0101, 0x00010001, 0x00000000

	.global ov05_021F7490
ov05_021F7490: ; 0x021F7490
	.word 0x00000000, 0x00000000, 0x00000800, 0x00000000
	.word ov05_021E0000, 0x00000001, 0x00000000

	.global ov05_021F74AC
ov05_021F74AC: ; 0x021F74AC
	.word 0x00000000, 0x00000000, 0x00000800, 0x00000000
	.word 0x011D0001, 0x00000300, 0x00000000

	.global ov05_021F74C8
ov05_021F74C8: ; 0x021F74C8
	.short 0x0000, 0x0017, 0x002D, 0x0016, 0x002D, 0x0044, 0x005A, 0x0043
	.short 0x005B, 0x0071, 0x0087, 0x0070, 0x0087, 0x009E, 0x00B4, 0x009D

	.global ov05_021F74E8
ov05_021F74E8: ; 0x021F74E8
	.word ov05_021E8A68, ov05_021E88E8, ov05_021E8BEC, ov05_021E8D20
	.word ov05_021E8F20, ov05_021E9030, ov05_021E9140, ov05_021E94A8
	.word ov05_021E97A8, ov05_021E9B68, ov05_021EA0E4, ov05_021EA3A4
	.word ov05_021EBBC8, ov05_021EBBE8, ov05_021EBC08, ov05_021EBC28
	.word ov05_021EBC48, ov05_021EBC68, ov05_021EBC88, ov05_021EBCA8
	.word ov05_021EC3B8, ov05_021EC3D8, ov05_021EC3F8, ov05_021EC418
	.word ov05_021EC438, ov05_021EB448, ov05_021EB5B4, ov05_021EAD60
	.word ov05_021EB160, ov05_021EA884, ov05_021EAAE8
