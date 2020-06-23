	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD67_021D74E0
MOD67_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	bl FUN_02015F1C
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r2, [r0]
	ldr r1, _021D75C0 ; =0xFFFFE0FF
	ldr r3, _021D75C4 ; =0x04001000
	and r2, r1
	str r2, [r0]
	ldr r2, [r3]
	add r0, #0x50
	and r1, r2
	str r1, [r3]
	mov r1, #0
	strh r1, [r0]
	add r3, #0x50
	strh r1, [r3]
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	mov r2, #2
	mov r0, #3
	mov r1, #0x2a
	lsl r2, r2, #0x10
	bl FUN_0201681C
	add r0, r4, #0
	bl FUN_0200628C
	add r5, r0, #0
	ldr r1, _021D75C8 ; =0x00001068
	add r0, r4, #0
	mov r2, #0x2a
	bl FUN_02006268
	ldr r2, _021D75C8 ; =0x00001068
	mov r1, #0
	add r4, r0, #0
	bl memset
	mov r0, #0x2a
	bl FUN_02016B94
	str r0, [r4]
	str r5, [r4, #0x4c]
	add r0, r5, #0
	bl FUN_020289A4
	str r0, [r4, #0x44]
	add r0, r5, #0
	bl FUN_020238F4
	str r0, [r4, #0x48]
	mov r0, #0
	mov r1, #0x2a
	bl FUN_02079A70
	mov r0, #0
	mov r1, #0x2a
	bl FUN_02002C84
	bl MOD67_021D7680
	ldr r0, [r4]
	bl MOD67_021D76A0
	add r0, r4, #0
	bl MOD67_021D77B0
	add r0, r4, #0
	bl MOD67_021D7880
	add r0, r4, #0
	bl MOD67_021D7D60
	add r0, r4, #0
	mov r1, #0
	bl MOD67_021D7D9C
	add r0, r4, #0
	bl MOD67_021D7B84
	ldr r0, _021D75CC ; =MOD67_021D7660
	add r1, r4, #0
	bl FUN_02015F10
	bl FUN_0201E788
	bl FUN_02033E74
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r1, #0
	mov r0, #0x43
	add r2, r1, #0
	bl FUN_0200433C
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D75C0: .word 0xFFFFE0FF
_021D75C4: .word 0x04001000
_021D75C8: .word 0x00001068
_021D75CC: .word MOD67_021D7660
	thumb_func_end MOD67_021D74E0

	thumb_func_start MOD67_021D75D0
MOD67_021D75D0: ; 0x021D75D0
	push {r4, lr}
	add r4, r1, #0
	bl FUN_02006278
	ldr r1, [r4]
	cmp r1, #4
	bhi _021D7620
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D75EA: ; jump table
	.short _021D75F4 - _021D75EA - 2 ; case 0
	.short _021D75FC - _021D75EA - 2 ; case 1
	.short _021D7604 - _021D75EA - 2 ; case 2
	.short _021D760C - _021D75EA - 2 ; case 3
	.short _021D7614 - _021D75EA - 2 ; case 4
_021D75F4:
	bl MOD67_021D78C4
	str r0, [r4]
	b _021D7620
_021D75FC:
	bl MOD67_021D78D8
	str r0, [r4]
	b _021D7620
_021D7604:
	bl MOD67_021D795C
	str r0, [r4]
	b _021D7620
_021D760C:
	bl MOD67_021D7A38
	str r0, [r4]
	b _021D7620
_021D7614:
	bl MOD67_021D7AA8
	cmp r0, #1
	bne _021D7620
	mov r0, #1
	pop {r4, pc}
_021D7620:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD67_021D75D0

	thumb_func_start MOD67_021D7624
MOD67_021D7624: ; 0x021D7624
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02006278
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	add r0, r4, #0
	bl MOD67_021D7D84
	ldr r0, [r4]
	bl MOD67_021D777C
	add r0, r4, #0
	bl MOD67_021D78AC
	mov r0, #0
	bl FUN_02002CC0
	add r0, r5, #0
	bl FUN_0200627C
	mov r0, #0x2a
	bl FUN_020168D0
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD67_021D7624

	thumb_func_start MOD67_021D7660
MOD67_021D7660: ; 0x021D7660
	push {r3, lr}
	ldr r0, [r0]
	bl FUN_0201AB60
	ldr r3, _021D7678 ; =0x027E0000
	ldr r1, _021D767C ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r3, pc}
	nop
_021D7678: .word 0x027E0000
_021D767C: .word 0x00003FF8
	thumb_func_end MOD67_021D7660

	thumb_func_start MOD67_021D7680
MOD67_021D7680: ; 0x021D7680
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D769C ; =0x021D97B0
	add r3, sp, #0
	mov r2, #5
_021D768A:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D768A
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D769C: .word MOD67_021D97B0
	thumb_func_end MOD67_021D7680

	thumb_func_start MOD67_021D76A0
MOD67_021D76A0: ; 0x021D76A0
	push {r3, r4, r5, lr}
	sub sp, #0x80
	ldr r5, _021D7768 ; =0x021D9730
	add r3, sp, #0x70
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _021D776C ; =0x021D975C
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #0
	str r0, [r3]
	add r0, r4, #0
	add r3, r1, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _021D7770 ; =0x021D9740
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018744
	ldr r5, _021D7774 ; =0x021D9778
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D7778 ; =0x021D9794
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #3
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x2a
	bl FUN_02017F18
	mov r0, #1
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x2a
	bl FUN_02017F18
	add sp, #0x80
	pop {r3, r4, r5, pc}
	nop
_021D7768: .word MOD67_021D9730
_021D776C: .word MOD67_021D975C
_021D7770: .word MOD67_021D9740
_021D7774: .word MOD67_021D9778
_021D7778: .word MOD67_021D9794
	thumb_func_end MOD67_021D76A0

	thumb_func_start MOD67_021D777C
MOD67_021D777C: ; 0x021D777C
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0201E6D8
	add r0, r4, #0
	mov r1, #3
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #2
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #0
	bl FUN_020178A0
	mov r0, #0x2a
	add r1, r4, #0
	bl FUN_02016A8C
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD67_021D777C

	thumb_func_start MOD67_021D77B0
MOD67_021D77B0: ; 0x021D77B0
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, [r4, #0x48]
	bl FUN_020239CC
	cmp r0, #0
	bne _021D7802
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x2a
	str r0, [sp, #0xc]
	mov r1, #2
	ldr r2, [r4]
	mov r0, #0x50
	add r3, r1, #0
	bl FUN_0200687C
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0x2a
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x50
	mov r3, #2
	bl FUN_020068C8
	mov r2, #0
	str r2, [sp]
	mov r0, #0x2a
	str r0, [sp, #4]
	mov r0, #0x50
	mov r1, #4
	add r3, r2, #0
	bl FUN_02006930
	b _021D7844
_021D7802:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x2a
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x50
	mov r1, #3
	mov r3, #2
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x2a
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x50
	mov r1, #1
	mov r3, #2
	bl FUN_020068C8
	mov r2, #0
	str r2, [sp]
	mov r0, #0x2a
	str r0, [sp, #4]
	mov r0, #0x50
	mov r1, #5
	add r3, r2, #0
	bl FUN_02006930
_021D7844:
	ldr r0, [r4]
	mov r1, #2
	bl FUN_0201886C
	add r1, r4, #0
	mov r2, #2
	add r1, #0x5c
	lsl r2, r2, #0xa
	bl MIi_CpuCopy16
	ldr r0, [r4]
	add r4, #0x5c
	mov r3, #2
	mov r1, #3
	add r2, r4, #0
	lsl r3, r3, #0xa
	bl FUN_02017DFC
	mov r1, #0x1e
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x2a
	bl FUN_02002ED0
	mov r0, #4
	mov r1, #0
	bl FUN_02017FE4
	add sp, #0x10
	pop {r4, pc}
	thumb_func_end MOD67_021D77B0

	thumb_func_start MOD67_021D7880
MOD67_021D7880: ; 0x021D7880
	push {r4, lr}
	ldr r2, _021D78A8 ; =0x00000142
	add r4, r0, #0
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x2a
	bl NewMsgDataFromNarc
	str r0, [r4, #0x50]
	mov r0, #0x2a
	bl FUN_0200AA80
	str r0, [r4, #0x54]
	mov r0, #0x80
	mov r1, #0x2a
	bl String_ctor
	str r0, [r4, #0x58]
	pop {r4, pc}
	nop
_021D78A8: .word 0x00000142
	thumb_func_end MOD67_021D7880

	thumb_func_start MOD67_021D78AC
MOD67_021D78AC: ; 0x021D78AC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x50]
	bl DestroyMsgData
	ldr r0, [r4, #0x54]
	bl FUN_0200AB18
	ldr r0, [r4, #0x58]
	bl String_dtor
	pop {r4, pc}
	thumb_func_end MOD67_021D78AC

	thumb_func_start MOD67_021D78C4
MOD67_021D78C4: ; 0x021D78C4
	push {r3, lr}
	bl FUN_0200E308
	cmp r0, #1
	bne _021D78D2
	mov r0, #1
	pop {r3, pc}
_021D78D2:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD67_021D78C4

	thumb_func_start MOD67_021D78D8
MOD67_021D78D8: ; 0x021D78D8
	push {r3, lr}
	ldr r1, _021D7954 ; =0x021C48B8
	ldr r3, [r1, #0x48]
	mov r1, #0x20
	add r2, r3, #0
	tst r2, r1
	beq _021D78F8
	sub r1, #0x21
	bl MOD67_021D7B1C
	cmp r0, #1
	bne _021D78F4
	mov r0, #2
	pop {r3, pc}
_021D78F4:
	mov r0, #1
	pop {r3, pc}
_021D78F8:
	mov r1, #0x11
	tst r1, r3
	beq _021D7910
	mov r1, #1
	bl MOD67_021D7B1C
	cmp r0, #1
	bne _021D790C
	mov r0, #3
	pop {r3, pc}
_021D790C:
	mov r0, #1
	pop {r3, pc}
_021D7910:
	mov r2, #2
	add r1, r3, #0
	tst r1, r2
	beq _021D793A
	ldr r1, _021D7958 ; =0x0000105C
	ldrsb r1, [r0, r1]
	cmp r1, #0
	beq _021D792E
	sub r1, r2, #3
	bl MOD67_021D7B1C
	cmp r0, #1
	bne _021D793A
	mov r0, #2
	pop {r3, pc}
_021D792E:
	mov r0, #1
	mov r1, #0x2a
	bl FUN_02079A70
	mov r0, #4
	pop {r3, pc}
_021D793A:
	ldr r0, _021D7954 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #8
	tst r0, r1
	beq _021D7950
	mov r0, #1
	mov r1, #0x2a
	bl FUN_02079A70
	mov r0, #4
	pop {r3, pc}
_021D7950:
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
_021D7954: .word 0x021C48B8
_021D7958: .word 0x0000105C
	thumb_func_end MOD67_021D78D8

	thumb_func_start MOD67_021D795C
MOD67_021D795C: ; 0x021D795C
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r1, _021D7A18 ; =0x0000105E
	add r4, r0, #0
	ldrsb r1, [r4, r1]
	cmp r1, #0
	beq _021D7970
	cmp r1, #1
	beq _021D79AC
	b _021D7A12
_021D7970:
	bl MOD67_021D7AB0
	ldr r2, _021D7A1C ; =0x00001063
	add r0, r4, #0
	ldrb r1, [r4, r2]
	sub r2, r2, #7
	ldrsb r2, [r4, r2]
	sub r2, r2, #1
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	bl MOD67_021D7B5C
	ldr r1, _021D7A20 ; =0x0000105C
	ldrsb r0, [r4, r1]
	sub r0, r0, #1
	strb r0, [r4, r1]
	add r1, r1, #4
	ldrsb r2, [r4, r1]
	mov r1, #1
	add r0, r4, #0
	eor r1, r2
	bl MOD67_021D7D9C
	ldr r0, _021D7A18 ; =0x0000105E
	mov r1, #1
	strb r1, [r4, r0]
	ldr r0, _021D7A24 ; =0x00000691
	bl FUN_020054C8
	b _021D7A12
_021D79AC:
	bl MOD67_021D7C30
	cmp r0, #1
	bne _021D7A12
	ldr r1, _021D7A28 ; =0x0000105F
	mov r3, #0
	strb r3, [r4, r1]
	sub r0, r1, #1
	strb r3, [r4, r0]
	add r0, r1, #1
	ldrsb r2, [r4, r0]
	mov r0, #1
	eor r2, r0
	add r0, r1, #1
	strb r2, [r4, r0]
	ldr r2, _021D7A2C ; =0x0000085C
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r1, r1, #3
	ldrb r1, [r4, r1]
	ldr r0, [r4]
	add r2, r4, r2
	bl FUN_02018148
	mov r3, #0
	add r2, r4, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r1, _021D7A30 ; =0x00001061
	ldr r0, [r4]
	ldrb r1, [r4, r1]
	add r2, #0x5c
	bl FUN_02018148
	ldr r1, _021D7A34 ; =0x00001062
	ldr r0, [r4]
	ldrb r1, [r4, r1]
	bl FUN_0201AC68
	ldr r1, _021D7A30 ; =0x00001061
	ldr r0, [r4]
	ldrb r1, [r4, r1]
	bl FUN_0201AC68
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, pc}
_021D7A12:
	mov r0, #2
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_021D7A18: .word 0x0000105E
_021D7A1C: .word 0x00001063
_021D7A20: .word 0x0000105C
_021D7A24: .word 0x00000691
_021D7A28: .word 0x0000105F
_021D7A2C: .word 0x0000085C
_021D7A30: .word 0x00001061
_021D7A34: .word 0x00001062
	thumb_func_end MOD67_021D795C

	thumb_func_start MOD67_021D7A38
MOD67_021D7A38: ; 0x021D7A38
	push {r4, lr}
	ldr r1, _021D7A98 ; =0x0000105E
	add r4, r0, #0
	ldrsb r1, [r4, r1]
	cmp r1, #0
	beq _021D7A4A
	cmp r1, #1
	beq _021D7A72
	b _021D7A92
_021D7A4A:
	bl MOD67_021D7AB0
	ldr r1, _021D7A9C ; =0x0000105C
	ldrsb r0, [r4, r1]
	add r0, r0, #1
	strb r0, [r4, r1]
	add r1, r1, #4
	ldrsb r2, [r4, r1]
	mov r1, #1
	add r0, r4, #0
	eor r1, r2
	bl MOD67_021D7D9C
	ldr r0, _021D7A98 ; =0x0000105E
	mov r1, #1
	strb r1, [r4, r0]
	ldr r0, _021D7AA0 ; =0x00000691
	bl FUN_020054C8
	b _021D7A92
_021D7A72:
	bl MOD67_021D7CBC
	cmp r0, #1
	bne _021D7A92
	ldr r1, _021D7AA4 ; =0x0000105F
	mov r2, #0
	strb r2, [r4, r1]
	sub r0, r1, #1
	strb r2, [r4, r0]
	add r0, r1, #1
	ldrsb r2, [r4, r0]
	mov r0, #1
	add r1, r1, #1
	eor r2, r0
	strb r2, [r4, r1]
	pop {r4, pc}
_021D7A92:
	mov r0, #3
	pop {r4, pc}
	nop
_021D7A98: .word 0x0000105E
_021D7A9C: .word 0x0000105C
_021D7AA0: .word 0x00000691
_021D7AA4: .word 0x0000105F
	thumb_func_end MOD67_021D7A38

	thumb_func_start MOD67_021D7AA8
MOD67_021D7AA8: ; 0x021D7AA8
	ldr r3, _021D7AAC ; =FUN_0200E308
	bx r3
	.align 2, 0
_021D7AAC: .word FUN_0200E308
	thumb_func_end MOD67_021D7AA8

	thumb_func_start MOD67_021D7AB0
MOD67_021D7AB0: ; 0x021D7AB0
	ldr r2, _021D7AEC ; =0x00001060
	ldrsb r1, [r0, r2]
	cmp r1, #0
	bne _021D7AD2
	mov r3, #0
	add r1, r2, #2
	strb r3, [r0, r1]
	mov r3, #2
	add r1, r2, #1
	strb r3, [r0, r1]
	mov r3, #1
	add r1, r2, #4
	strb r3, [r0, r1]
	mov r3, #3
	add r1, r2, #3
	strb r3, [r0, r1]
	bx lr
_021D7AD2:
	mov r3, #1
	add r1, r2, #2
	strb r3, [r0, r1]
	mov r3, #3
	add r1, r2, #1
	strb r3, [r0, r1]
	mov r3, #0
	add r1, r2, #4
	strb r3, [r0, r1]
	mov r3, #2
	add r1, r2, #3
	strb r3, [r0, r1]
	bx lr
	.align 2, 0
_021D7AEC: .word 0x00001060
	thumb_func_end MOD67_021D7AB0

	thumb_func_start MOD67_021D7AF0
MOD67_021D7AF0: ; 0x021D7AF0
	push {r3, lr}
	ldr r0, [r0, #0x44]
	add r3, r1, #0
	add r1, sp, #0
	mov r2, #0
	bl FUN_02029584
	ldr r1, [sp]
	lsl r0, r1, #0x19
	lsr r0, r0, #0x19
	bne _021D7B16
	lsl r0, r1, #0x15
	lsr r0, r0, #0x1c
	bne _021D7B16
	lsl r0, r1, #0xd
	lsr r0, r0, #0x1b
	bne _021D7B16
	mov r0, #0
	pop {r3, pc}
_021D7B16:
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD67_021D7AF0

	thumb_func_start MOD67_021D7B1C
MOD67_021D7B1C: ; 0x021D7B1C
	push {r3, lr}
	cmp r1, #1
	ldr r1, _021D7B58 ; =0x0000105C
	bne _021D7B3C
	ldrsb r1, [r0, r1]
	cmp r1, #9
	beq _021D7B54
	add r1, r1, #1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD67_021D7AF0
	cmp r0, #1
	bne _021D7B54
	mov r0, #1
	pop {r3, pc}
_021D7B3C:
	ldrsb r1, [r0, r1]
	cmp r1, #0
	beq _021D7B54
	sub r1, r1, #1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD67_021D7AF0
	cmp r0, #1
	bne _021D7B54
	mov r0, #1
	pop {r3, pc}
_021D7B54:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_021D7B58: .word 0x0000105C
	thumb_func_end MOD67_021D7B1C

	thumb_func_start MOD67_021D7B5C
MOD67_021D7B5C: ; 0x021D7B5C
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0x20
	str r0, [sp]
	str r0, [sp, #4]
	str r2, [sp, #8]
	mov r2, #0
	ldr r0, [r5]
	add r3, r2, #0
	add r4, r1, #0
	bl FUN_020186B4
	ldr r0, [r5]
	add r1, r4, #0
	bl FUN_0201AC68
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD67_021D7B5C

	thumb_func_start MOD67_021D7B84
MOD67_021D7B84: ; 0x021D7B84
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #0
	bl FUN_0201886C
	ldr r2, _021D7B9C ; =0x0000085C
	add r1, r4, r2
	sub r2, #0x5c
	bl MIi_CpuCopy16
	pop {r4, pc}
	.align 2, 0
_021D7B9C: .word 0x0000085C
	thumb_func_end MOD67_021D7B84

	thumb_func_start MOD67_021D7BA0
MOD67_021D7BA0: ; 0x021D7BA0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	str r2, [sp, #0x10]
	add r6, r1, #0
	ldr r1, [sp, #0x10]
	add r7, r0, #0
	lsl r1, r1, #0x18
	ldr r0, [r7]
	lsr r1, r1, #0x18
	add r5, r3, #0
	bl FUN_0201886C
	str r0, [sp, #0x14]
	ldr r1, _021D7C2C ; =0x021D97D8
	lsl r0, r5, #5
	add r5, r1, r0
	ldr r0, [sp, #0x10]
	mov r4, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
_021D7BCA:
	ldrb r0, [r5, r4]
	cmp r0, #0xff
	bne _021D7BF0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x20
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	lsl r3, r4, #0x18
	ldr r0, [r7]
	ldr r1, [sp, #0x18]
	mov r2, #0
	lsr r3, r3, #0x18
	bl FUN_02018540
	b _021D7C10
_021D7BF0:
	ldr r0, [sp, #0x14]
	lsl r1, r4, #1
	mov r2, #0
	add r3, r0, r1
_021D7BF8:
	ldrb r0, [r5, r4]
	lsl r1, r2, #5
	add r0, r1, r0
	lsl r0, r0, #1
	ldrh r0, [r6, r0]
	lsl r1, r1, #1
	strh r0, [r3, r1]
	add r0, r2, #1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	cmp r2, #0x20
	blo _021D7BF8
_021D7C10:
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x20
	blo _021D7BCA
	ldr r1, [sp, #0x10]
	ldr r0, [r7]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_0201AC68
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021D7C2C: .word MOD67_021D97D8
	thumb_func_end MOD67_021D7BA0

	thumb_func_start MOD67_021D7C30
MOD67_021D7C30: ; 0x021D7C30
	push {r4, lr}
	ldr r3, _021D7CA8 ; =0x00001062
	add r4, r0, #0
	ldrb r2, [r4, r3]
	sub r3, r3, #3
	ldr r1, _021D7CAC ; =0x0000085C
	ldrsb r3, [r4, r3]
	add r1, r4, r1
	bl MOD67_021D7BA0
	ldr r3, _021D7CB0 ; =0x00001061
	add r1, r4, #0
	ldrb r2, [r4, r3]
	sub r3, r3, #2
	ldrsb r3, [r4, r3]
	add r0, r4, #0
	add r1, #0x5c
	bl MOD67_021D7BA0
	ldr r2, _021D7CB0 ; =0x00001061
	add r0, r4, #0
	ldrb r1, [r4, r2]
	sub r2, r2, #5
	ldrsb r2, [r4, r2]
	add r2, r2, #1
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	bl MOD67_021D7B5C
	ldr r0, _021D7CB4 ; =0x0000105F
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	ldrsb r1, [r4, r0]
	cmp r1, #9
	bne _021D7CA4
	add r0, r0, #5
	ldrb r0, [r4, r0]
	mov r1, #0
	bl FUN_020178BC
	ldr r0, _021D7CB8 ; =0x00001063
	mov r1, #1
	ldrb r0, [r4, r0]
	bl FUN_020178BC
	ldr r0, _021D7CA8 ; =0x00001062
	mov r1, #2
	ldrb r0, [r4, r0]
	bl FUN_020178BC
	ldr r0, _021D7CB0 ; =0x00001061
	mov r1, #3
	ldrb r0, [r4, r0]
	bl FUN_020178BC
	mov r0, #1
	pop {r4, pc}
_021D7CA4:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D7CA8: .word 0x00001062
_021D7CAC: .word 0x0000085C
_021D7CB0: .word 0x00001061
_021D7CB4: .word 0x0000105F
_021D7CB8: .word 0x00001063
	thumb_func_end MOD67_021D7C30

	thumb_func_start MOD67_021D7CBC
MOD67_021D7CBC: ; 0x021D7CBC
	push {r3, r4, r5, lr}
	ldr r3, _021D7D48 ; =0x00001064
	add r4, r0, #0
	ldrb r2, [r4, r3]
	sub r3, r3, #5
	ldrsb r5, [r4, r3]
	mov r3, #8
	ldr r1, _021D7D4C ; =0x0000085C
	sub r3, r3, r5
	lsl r3, r3, #0x10
	add r1, r4, r1
	lsr r3, r3, #0x10
	bl MOD67_021D7BA0
	ldr r3, _021D7D50 ; =0x00001063
	add r1, r4, #0
	ldrb r2, [r4, r3]
	sub r3, r3, #4
	ldrsb r5, [r4, r3]
	mov r3, #8
	add r0, r4, #0
	sub r3, r3, r5
	lsl r3, r3, #0x10
	add r1, #0x5c
	lsr r3, r3, #0x10
	bl MOD67_021D7BA0
	ldr r2, _021D7D50 ; =0x00001063
	add r0, r4, #0
	ldrb r1, [r4, r2]
	sub r2, r2, #7
	ldrb r2, [r4, r2]
	bl MOD67_021D7B5C
	ldr r0, _021D7D54 ; =0x0000105F
	ldrsb r1, [r4, r0]
	cmp r1, #1
	bne _021D7D30
	add r0, r0, #5
	ldrb r0, [r4, r0]
	mov r1, #0
	bl FUN_020178BC
	ldr r0, _021D7D50 ; =0x00001063
	mov r1, #1
	ldrb r0, [r4, r0]
	bl FUN_020178BC
	ldr r0, _021D7D58 ; =0x00001062
	mov r1, #2
	ldrb r0, [r4, r0]
	bl FUN_020178BC
	ldr r0, _021D7D5C ; =0x00001061
	mov r1, #3
	ldrb r0, [r4, r0]
	bl FUN_020178BC
_021D7D30:
	ldr r0, _021D7D54 ; =0x0000105F
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	ldrsb r0, [r4, r0]
	cmp r0, #9
	bne _021D7D42
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D7D42:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D7D48: .word 0x00001064
_021D7D4C: .word 0x0000085C
_021D7D50: .word 0x00001063
_021D7D54: .word 0x0000105F
_021D7D58: .word 0x00001062
_021D7D5C: .word 0x00001061
	thumb_func_end MOD67_021D7CBC

	thumb_func_start MOD67_021D7D60
MOD67_021D7D60: ; 0x021D7D60
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r4, _021D7D80 ; =0x021D98F8
	mov r6, #0
	add r5, r7, #4
_021D7D6A:
	ldr r0, [r7]
	add r1, r5, #0
	add r2, r4, #0
	bl FUN_02019150
	add r6, r6, #1
	add r4, #8
	add r5, #0x10
	cmp r6, #4
	blo _021D7D6A
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D7D80: .word MOD67_021D98F8
	thumb_func_end MOD67_021D7D60

	thumb_func_start MOD67_021D7D84
MOD67_021D7D84: ; 0x021D7D84
	push {r3, r4, r5, lr}
	mov r4, #0
	add r5, r0, #4
_021D7D8A:
	add r0, r5, #0
	bl FUN_02019178
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #4
	blo _021D7D8A
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD67_021D7D84

	thumb_func_start MOD67_021D7D9C
MOD67_021D7D9C: ; 0x021D7D9C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	cmp r1, #0
	bne _021D7DAC
	add r4, r5, #0
	add r6, r5, #4
	add r4, #0x14
	b _021D7DB4
_021D7DAC:
	add r6, r5, #0
	add r4, r5, #0
	add r6, #0x24
	add r4, #0x34
_021D7DB4:
	add r0, r6, #0
	mov r1, #0
	bl FUN_02019620
	add r0, r4, #0
	mov r1, #0
	bl FUN_02019620
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD67_021D7E00
	cmp r0, #1
	bne _021D7DF2
	add r0, r5, #0
	add r1, r4, #0
	bl MOD67_021D7F18
	add r0, r5, #0
	add r1, r4, #0
	bl MOD67_021D81C4
	add r0, r5, #0
	add r1, r4, #0
	bl MOD67_021D8208
	add r0, r5, #0
	add r1, r4, #0
	bl MOD67_021D8344
_021D7DF2:
	add r0, r6, #0
	bl FUN_02019220
	add r0, r4, #0
	bl FUN_02019220
	pop {r4, r5, r6, pc}
	thumb_func_end MOD67_021D7D9C

	thumb_func_start MOD67_021D7E00
MOD67_021D7E00: ; 0x021D7E00
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	ldr r3, _021D7F10 ; =0x0000105C
	add r5, r0, #0
	ldrb r3, [r5, r3]
	ldr r0, [r5, #0x44]
	add r7, r1, #0
	str r2, [sp, #0x10]
	add r1, sp, #0x14
	mov r2, #0
	bl FUN_02029584
	ldr r1, [sp, #0x14]
	lsl r0, r1, #0x19
	lsr r0, r0, #0x19
	bne _021D7E32
	lsl r0, r1, #0x15
	lsr r0, r0, #0x1c
	bne _021D7E32
	lsl r0, r1, #0xd
	lsr r0, r0, #0x1b
	bne _021D7E32
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D7E32:
	ldr r0, [r5, #0x50]
	mov r1, #1
	bl NewString_ReadMsgData
	ldr r2, [sp, #0x14]
	add r4, r0, #0
	lsl r2, r2, #0x15
	ldr r0, [r5, #0x54]
	mov r1, #0
	lsr r2, r2, #0x1c
	bl FUN_0200B764
	mov r0, #0
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r2, [sp, #0x14]
	ldr r0, [r5, #0x54]
	lsl r2, r2, #0xd
	lsr r2, r2, #0x1b
	mov r3, #2
	bl FUN_0200AD38
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D7F14 ; =0x00010200
	add r3, r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x58]
	add r0, r7, #0
	bl FUN_0201BDE0
	mov r0, #0
	ldr r1, [r5, #0x58]
	add r2, r0, #0
	bl FUN_02002E14
	ldr r1, [sp, #0x14]
	add r4, r0, #0
	lsl r1, r1, #0x12
	lsr r1, r1, #0x1d
	ldr r0, [r5, #0x50]
	add r1, r1, #2
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r1, #0
	add r4, #0xc
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D7F14 ; =0x00010200
	add r2, r6, #0
	str r0, [sp, #8]
	add r0, r7, #0
	add r3, r4, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r6, #0
	bl String_dtor
	ldr r0, [r5, #0x50]
	mov r1, #0
	bl NewString_ReadMsgData
	add r4, r0, #0
	ldr r0, [sp, #0x14]
	lsr r0, r0, #0x13
	bl FUN_02034824
	add r2, r0, #0
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200AFF4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r4, #0
	bl StringExpandPlaceholders
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D7F14 ; =0x00010200
	add r3, r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	mov r0, #1
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D7F10: .word 0x0000105C
_021D7F14: .word 0x00010200
	thumb_func_end MOD67_021D7E00

	thumb_func_start MOD67_021D7F18
MOD67_021D7F18: ; 0x021D7F18
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	ldr r3, _021D81C0 ; =0x0000105C
	add r6, r0, #0
	ldrb r3, [r6, r3]
	ldr r0, [r6, #0x44]
	add r7, r1, #0
	add r1, sp, #0
	mov r2, #1
	bl FUN_02029584
	mov r4, #0
	add r5, sp, #0
_021D7F32:
	ldrb r0, [r5]
	cmp r0, #0x23
	bls _021D7F3A
	b _021D81B0
_021D7F3A:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D7F46: ; jump table
	.short _021D7F8E - _021D7F46 - 2 ; case 0
	.short _021D7F92 - _021D7F46 - 2 ; case 1
	.short _021D7FA2 - _021D7F46 - 2 ; case 2
	.short _021D7FB2 - _021D7F46 - 2 ; case 3
	.short _021D7FC2 - _021D7F46 - 2 ; case 4
	.short _021D7FD2 - _021D7F46 - 2 ; case 5
	.short _021D7FE2 - _021D7F46 - 2 ; case 6
	.short _021D7FF2 - _021D7F46 - 2 ; case 7
	.short _021D8002 - _021D7F46 - 2 ; case 8
	.short _021D8012 - _021D7F46 - 2 ; case 9
	.short _021D8022 - _021D7F46 - 2 ; case 10
	.short _021D8032 - _021D7F46 - 2 ; case 11
	.short _021D8042 - _021D7F46 - 2 ; case 12
	.short _021D8052 - _021D7F46 - 2 ; case 13
	.short _021D8062 - _021D7F46 - 2 ; case 14
	.short _021D8072 - _021D7F46 - 2 ; case 15
	.short _021D8082 - _021D7F46 - 2 ; case 16
	.short _021D8092 - _021D7F46 - 2 ; case 17
	.short _021D80A2 - _021D7F46 - 2 ; case 18
	.short _021D80C2 - _021D7F46 - 2 ; case 19
	.short _021D80D2 - _021D7F46 - 2 ; case 20
	.short _021D8102 - _021D7F46 - 2 ; case 21
	.short _021D80F2 - _021D7F46 - 2 ; case 22
	.short _021D80E2 - _021D7F46 - 2 ; case 23
	.short _021D80B2 - _021D7F46 - 2 ; case 24
	.short _021D8122 - _021D7F46 - 2 ; case 25
	.short _021D8112 - _021D7F46 - 2 ; case 26
	.short _021D8132 - _021D7F46 - 2 ; case 27
	.short _021D8142 - _021D7F46 - 2 ; case 28
	.short _021D8152 - _021D7F46 - 2 ; case 29
	.short _021D8162 - _021D7F46 - 2 ; case 30
	.short _021D81B0 - _021D7F46 - 2 ; case 31
	.short _021D8182 - _021D7F46 - 2 ; case 32
	.short _021D8172 - _021D7F46 - 2 ; case 33
	.short _021D8192 - _021D7F46 - 2 ; case 34
	.short _021D81A2 - _021D7F46 - 2 ; case 35
_021D7F8E:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
_021D7F92:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D84A8
	b _021D81B0
_021D7FA2:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D84E4
	b _021D81B0
_021D7FB2:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8520
	b _021D81B0
_021D7FC2:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D855C
	b _021D81B0
_021D7FD2:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8598
	b _021D81B0
_021D7FE2:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D85D4
	b _021D81B0
_021D7FF2:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8610
	b _021D81B0
_021D8002:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D864C
	b _021D81B0
_021D8012:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8688
	b _021D81B0
_021D8022:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D86DC
	b _021D81B0
_021D8032:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D873C
	b _021D81B0
_021D8042:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8790
	b _021D81B0
_021D8052:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D87E4
	b _021D81B0
_021D8062:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8840
	b _021D81B0
_021D8072:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D88AC
	b _021D81B0
_021D8082:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8914
	b _021D81B0
_021D8092:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8950
	b _021D81B0
_021D80A2:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D898C
	b _021D81B0
_021D80B2:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D89E0
	b _021D81B0
_021D80C2:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8A3C
	b _021D81B0
_021D80D2:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8A98
	b _021D81B0
_021D80E2:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8AF4
	b _021D81B0
_021D80F2:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8B50
	b _021D81B0
_021D8102:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8BAC
	b _021D81B0
_021D8112:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8C08
	b _021D81B0
_021D8122:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8C64
	b _021D81B0
_021D8132:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8CC0
	b _021D81B0
_021D8142:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8D1C
	b _021D81B0
_021D8152:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8D78
	b _021D81B0
_021D8162:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8DD4
	b _021D81B0
_021D8172:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8E10
	b _021D81B0
_021D8182:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8E4C
	b _021D81B0
_021D8192:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8E88
	b _021D81B0
_021D81A2:
	lsl r3, r4, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl MOD67_021D8EC4
_021D81B0:
	add r4, r4, #1
	add r5, #8
	cmp r4, #4
	bhs _021D81BA
	b _021D7F32
_021D81BA:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D81C0: .word 0x0000105C
	thumb_func_end MOD67_021D7F18

	thumb_func_start MOD67_021D81C4
MOD67_021D81C4: ; 0x021D81C4
	push {r3, r4, r5, lr}
	ldr r3, _021D8204 ; =0x0000105C
	add r5, r0, #0
	ldrb r3, [r5, r3]
	ldr r0, [r5, #0x44]
	add r4, r1, #0
	add r1, sp, #0
	mov r2, #2
	bl FUN_02029584
	add r0, sp, #0
	ldrb r0, [r0]
	cmp r0, #0
	beq _021D8200
	cmp r0, #1
	beq _021D81EA
	cmp r0, #2
	beq _021D81F6
	pop {r3, r4, r5, pc}
_021D81EA:
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #0
	bl MOD67_021D8F40
	pop {r3, r4, r5, pc}
_021D81F6:
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #0
	bl MOD67_021D8FEC
_021D8200:
	pop {r3, r4, r5, pc}
	nop
_021D8204: .word 0x0000105C
	thumb_func_end MOD67_021D81C4

	thumb_func_start MOD67_021D8208
MOD67_021D8208: ; 0x021D8208
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	ldr r3, _021D8334 ; =0x0000105C
	add r4, r0, #0
	ldrb r3, [r4, r3]
	ldr r0, [r4, #0x44]
	add r7, r1, #0
	add r1, sp, #0x10
	mov r2, #3
	bl FUN_02029584
	add r0, sp, #0x10
	ldrh r1, [r0]
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1f
	bne _021D822A
	b _021D832E
_021D822A:
	ldrh r0, [r0, #2]
	bl FUN_02034824
	add r2, r0, #0
	ldr r1, _021D8338 ; =0x0000017E
	mov r0, #0x1a
	mov r3, #0x2a
	bl ReadMsgData_NewNarc_NewString
	add r6, r0, #0
	bl FUN_02021D3C
	add r5, r0, #0
	add r0, r6, #0
	bl String_dtor
	add r0, sp, #0x10
	ldrh r0, [r0]
	mov r1, #1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x11
	bl FUN_0206AC74
	cmp r0, #0x3f
	bne _021D828A
	ldr r0, [r4, #0x50]
	mov r1, #0x38
	bl NewString_ReadMsgData
	add r6, r0, #0
	ldr r0, [r4, #0x54]
	ldr r2, [r4, #0x4c]
	mov r1, #1
	bl FUN_0200ABE4
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	add r2, r6, #0
	bl StringExpandPlaceholders
	ldr r0, [r4, #0x58]
	bl FUN_02021D3C
	add r5, r5, r0
	add r0, r6, #0
	bl String_dtor
	b _021D82BA
_021D828A:
	add r2, sp, #0x10
	ldrh r2, [r2]
	ldr r1, _021D833C ; =0x0000022F
	mov r0, #0x1a
	lsl r2, r2, #0x10
	lsr r2, r2, #0x11
	mov r3, #0x2a
	bl ReadMsgData_NewNarc_NewString
	add r6, r0, #0
	bl FUN_02021D3C
	add r5, r5, r0
	add r0, r6, #0
	bl String_dtor
	add r2, sp, #0x10
	ldrh r2, [r2]
	ldr r0, [r4, #0x54]
	mov r1, #1
	lsl r2, r2, #0x10
	lsr r2, r2, #0x11
	bl FUN_0200B10C
_021D82BA:
	cmp r5, #0xe
	bhi _021D82CA
	ldr r0, [r4, #0x50]
	mov r1, #0x34
	bl NewString_ReadMsgData
	add r5, r0, #0
	b _021D82F2
_021D82CA:
	cmp r5, #0x10
	bhi _021D82DA
	ldr r0, [r4, #0x50]
	mov r1, #0x35
	bl NewString_ReadMsgData
	add r5, r0, #0
	b _021D82F2
_021D82DA:
	cmp r5, #0x13
	ldr r0, [r4, #0x50]
	bhi _021D82EA
	mov r1, #0x36
	bl NewString_ReadMsgData
	add r5, r0, #0
	b _021D82F2
_021D82EA:
	mov r1, #0x37
	bl NewString_ReadMsgData
	add r5, r0, #0
_021D82F2:
	add r0, sp, #0x10
	ldrh r0, [r0, #2]
	bl FUN_02034824
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl FUN_0200AFF4
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	add r2, r5, #0
	bl StringExpandPlaceholders
	mov r0, #0x60
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8340 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r4, #0x58]
	add r0, r7, #0
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r5, #0
	bl String_dtor
_021D832E:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D8334: .word 0x0000105C
_021D8338: .word 0x0000017E
_021D833C: .word 0x0000022F
_021D8340: .word 0x00010200
	thumb_func_end MOD67_021D8208

	thumb_func_start MOD67_021D8344
MOD67_021D8344: ; 0x021D8344
	push {r4, r5, r6, r7, lr}
	sub sp, #0x74
	ldr r3, _021D84A4 ; =0x0000105C
	add r6, r0, #0
	ldrb r3, [r6, r3]
	ldr r0, [r6, #0x44]
	add r7, r1, #0
	add r1, sp, #0
	mov r2, #4
	bl FUN_02029584
	mov r5, #0
	add r4, sp, #0
_021D835E:
	ldrb r0, [r4]
	cmp r0, #0x10
	bls _021D8366
	b _021D8496
_021D8366:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8372: ; jump table
	.short _021D8394 - _021D8372 - 2 ; case 0
	.short _021D8398 - _021D8372 - 2 ; case 1
	.short _021D83A8 - _021D8372 - 2 ; case 2
	.short _021D83B8 - _021D8372 - 2 ; case 3
	.short _021D83C8 - _021D8372 - 2 ; case 4
	.short _021D83D8 - _021D8372 - 2 ; case 5
	.short _021D83E8 - _021D8372 - 2 ; case 6
	.short _021D83F8 - _021D8372 - 2 ; case 7
	.short _021D8408 - _021D8372 - 2 ; case 8
	.short _021D8418 - _021D8372 - 2 ; case 9
	.short _021D8428 - _021D8372 - 2 ; case 10
	.short _021D8438 - _021D8372 - 2 ; case 11
	.short _021D8448 - _021D8372 - 2 ; case 12
	.short _021D8458 - _021D8372 - 2 ; case 13
	.short _021D8468 - _021D8372 - 2 ; case 14
	.short _021D8478 - _021D8372 - 2 ; case 15
	.short _021D8488 - _021D8372 - 2 ; case 16
_021D8394:
	add sp, #0x74
	pop {r4, r5, r6, r7, pc}
_021D8398:
	lsl r3, r5, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl MOD67_021D90D4
	b _021D8496
_021D83A8:
	lsl r3, r5, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl MOD67_021D9158
	b _021D8496
_021D83B8:
	lsl r3, r5, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl MOD67_021D91DC
	b _021D8496
_021D83C8:
	lsl r3, r5, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl MOD67_021D9274
	b _021D8496
_021D83D8:
	lsl r3, r5, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl MOD67_021D92F8
	b _021D8496
_021D83E8:
	lsl r3, r5, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl MOD67_021D9390
	b _021D8496
_021D83F8:
	lsl r3, r5, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl MOD67_021D93EC
	b _021D8496
_021D8408:
	lsl r3, r5, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl MOD67_021D9458
	b _021D8496
_021D8418:
	lsl r3, r5, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl MOD67_021D9494
	b _021D8496
_021D8428:
	lsl r3, r5, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl MOD67_021D94F0
	b _021D8496
_021D8438:
	lsl r3, r5, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl MOD67_021D952C
	b _021D8496
_021D8448:
	lsl r3, r5, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl MOD67_021D95B0
	b _021D8496
_021D8458:
	lsl r3, r5, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl MOD67_021D95EC
	b _021D8496
_021D8468:
	lsl r3, r5, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl MOD67_021D964C
	b _021D8496
_021D8478:
	lsl r3, r5, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl MOD67_021D9688
	b _021D8496
_021D8488:
	lsl r3, r5, #0x18
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl MOD67_021D96F4
_021D8496:
	add r5, r5, #1
	add r4, #0x3a
	cmp r5, #2
	bhs _021D84A0
	b _021D835E
_021D84A0:
	add sp, #0x74
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D84A4: .word 0x0000105C
	thumb_func_end MOD67_021D8344

	thumb_func_start MOD67_021D84A8
MOD67_021D84A8: ; 0x021D84A8
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #9
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D84E0 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D84E0: .word 0x00010200
	thumb_func_end MOD67_021D84A8

	thumb_func_start MOD67_021D84E4
MOD67_021D84E4: ; 0x021D84E4
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0xa
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D851C ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D851C: .word 0x00010200
	thumb_func_end MOD67_021D84E4

	thumb_func_start MOD67_021D8520
MOD67_021D8520: ; 0x021D8520
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0xb
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8558 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8558: .word 0x00010200
	thumb_func_end MOD67_021D8520

	thumb_func_start MOD67_021D855C
MOD67_021D855C: ; 0x021D855C
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0xc
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8594 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8594: .word 0x00010200
	thumb_func_end MOD67_021D855C

	thumb_func_start MOD67_021D8598
MOD67_021D8598: ; 0x021D8598
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0xd
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D85D0 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D85D0: .word 0x00010200
	thumb_func_end MOD67_021D8598

	thumb_func_start MOD67_021D85D4
MOD67_021D85D4: ; 0x021D85D4
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0xe
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D860C ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D860C: .word 0x00010200
	thumb_func_end MOD67_021D85D4

	thumb_func_start MOD67_021D8610
MOD67_021D8610: ; 0x021D8610
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0xf
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8648 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8648: .word 0x00010200
	thumb_func_end MOD67_021D8610

	thumb_func_start MOD67_021D864C
MOD67_021D864C: ; 0x021D864C
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0x10
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8684 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8684: .word 0x00010200
	thumb_func_end MOD67_021D864C

	thumb_func_start MOD67_021D8688
MOD67_021D8688: ; 0x021D8688
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x11
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r2, [r4, #2]
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200B430
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D86D8 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D86D8: .word 0x00010200
	thumb_func_end MOD67_021D8688

	thumb_func_start MOD67_021D86DC
MOD67_021D86DC: ; 0x021D86DC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x12
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r2, [r4, #2]
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200B430
	ldrh r2, [r4, #4]
	ldr r0, [r5, #0x54]
	mov r1, #1
	bl FUN_0200B10C
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8738 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D8738: .word 0x00010200
	thumb_func_end MOD67_021D86DC

	thumb_func_start MOD67_021D873C
MOD67_021D873C: ; 0x021D873C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x13
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r2, [r4, #4]
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200B10C
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D878C ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D878C: .word 0x00010200
	thumb_func_end MOD67_021D873C

	thumb_func_start MOD67_021D8790
MOD67_021D8790: ; 0x021D8790
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x14
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r2, [r4, #4]
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200B10C
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D87E0 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D87E0: .word 0x00010200
	thumb_func_end MOD67_021D8790

	thumb_func_start MOD67_021D87E4
MOD67_021D87E4: ; 0x021D87E4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x15
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r0, [r4, #2]
	bl FUN_02034824
	add r2, r0, #0
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200AFF4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D883C ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D883C: .word 0x00010200
	thumb_func_end MOD67_021D87E4

	thumb_func_start MOD67_021D8840
MOD67_021D8840: ; 0x021D8840
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	ldrh r4, [r2, #2]
	add r5, r0, #0
	add r6, r3, #0
	str r1, [sp, #0x10]
	cmp r4, #0x2f
	beq _021D8858
	cmp r4, #0x40
	beq _021D8858
	cmp r4, #0x31
	bne _021D8864
_021D8858:
	ldr r0, [r5, #0x50]
	mov r1, #0x17
	bl NewString_ReadMsgData
	add r7, r0, #0
	b _021D886E
_021D8864:
	ldr r0, [r5, #0x50]
	mov r1, #0x16
	bl NewString_ReadMsgData
	add r7, r0, #0
_021D886E:
	ldr r0, [r5, #0x54]
	mov r1, #0
	add r2, r4, #0
	bl FUN_0200AFF4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D88A8 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D88A8: .word 0x00010200
	thumb_func_end MOD67_021D8840

	thumb_func_start MOD67_021D88AC
MOD67_021D88AC: ; 0x021D88AC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldrh r0, [r2, #2]
	add r7, r1, #0
	add r4, r3, #0
	str r0, [sp, #0x10]
	bl FUN_02029960
	cmp r0, #0
	ldr r0, [r5, #0x50]
	bne _021D88CC
	mov r1, #0x17
	bl NewString_ReadMsgData
	b _021D88D2
_021D88CC:
	mov r1, #0x18
	bl NewString_ReadMsgData
_021D88D2:
	add r6, r0, #0
	ldr r0, [r5, #0x54]
	ldr r2, [sp, #0x10]
	mov r1, #0
	bl FUN_0200AFF4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r6, #0
	bl StringExpandPlaceholders
	lsl r0, r4, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8910 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x58]
	add r0, r7, #0
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r6, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D8910: .word 0x00010200
	thumb_func_end MOD67_021D88AC

	thumb_func_start MOD67_021D8914
MOD67_021D8914: ; 0x021D8914
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0x19
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D894C ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D894C: .word 0x00010200
	thumb_func_end MOD67_021D8914

	thumb_func_start MOD67_021D8950
MOD67_021D8950: ; 0x021D8950
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0x1a
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8988 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8988: .word 0x00010200
	thumb_func_end MOD67_021D8950

	thumb_func_start MOD67_021D898C
MOD67_021D898C: ; 0x021D898C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x1d
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r2, [r4, #6]
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200AE38
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D89DC ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D89DC: .word 0x00010200
	thumb_func_end MOD67_021D898C

	thumb_func_start MOD67_021D89E0
MOD67_021D89E0: ; 0x021D89E0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x23
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r0, [r4, #2]
	bl FUN_02034824
	add r2, r0, #0
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200AFF4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8A38 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D8A38: .word 0x00010200
	thumb_func_end MOD67_021D89E0

	thumb_func_start MOD67_021D8A3C
MOD67_021D8A3C: ; 0x021D8A3C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x1e
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r0, [r4, #2]
	bl FUN_02034824
	add r2, r0, #0
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200AFF4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8A94 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D8A94: .word 0x00010200
	thumb_func_end MOD67_021D8A3C

	thumb_func_start MOD67_021D8A98
MOD67_021D8A98: ; 0x021D8A98
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x1f
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r0, [r4, #2]
	bl FUN_02034824
	add r2, r0, #0
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200AFF4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8AF0 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D8AF0: .word 0x00010200
	thumb_func_end MOD67_021D8A98

	thumb_func_start MOD67_021D8AF4
MOD67_021D8AF4: ; 0x021D8AF4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x26
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r0, [r4, #2]
	bl FUN_02034824
	add r2, r0, #0
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200AFF4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8B4C ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D8B4C: .word 0x00010200
	thumb_func_end MOD67_021D8AF4

	thumb_func_start MOD67_021D8B50
MOD67_021D8B50: ; 0x021D8B50
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x21
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r0, [r4, #2]
	bl FUN_02034824
	add r2, r0, #0
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200AFF4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8BA8 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D8BA8: .word 0x00010200
	thumb_func_end MOD67_021D8B50

	thumb_func_start MOD67_021D8BAC
MOD67_021D8BAC: ; 0x021D8BAC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x20
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r0, [r4, #2]
	bl FUN_02034824
	add r2, r0, #0
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200AFF4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8C04 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D8C04: .word 0x00010200
	thumb_func_end MOD67_021D8BAC

	thumb_func_start MOD67_021D8C08
MOD67_021D8C08: ; 0x021D8C08
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x25
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r0, [r4, #2]
	bl FUN_02034824
	add r2, r0, #0
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200AFF4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8C60 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D8C60: .word 0x00010200
	thumb_func_end MOD67_021D8C08

	thumb_func_start MOD67_021D8C64
MOD67_021D8C64: ; 0x021D8C64
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x24
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r0, [r4, #2]
	bl FUN_02034824
	add r2, r0, #0
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200AFF4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8CBC ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D8CBC: .word 0x00010200
	thumb_func_end MOD67_021D8C64

	thumb_func_start MOD67_021D8CC0
MOD67_021D8CC0: ; 0x021D8CC0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x22
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r0, [r4, #2]
	bl FUN_02034824
	add r2, r0, #0
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200AFF4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8D18 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D8D18: .word 0x00010200
	thumb_func_end MOD67_021D8CC0

	thumb_func_start MOD67_021D8D1C
MOD67_021D8D1C: ; 0x021D8D1C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x29
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r0, [r4, #2]
	bl FUN_02034824
	add r2, r0, #0
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200AFF4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8D74 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D8D74: .word 0x00010200
	thumb_func_end MOD67_021D8D1C

	thumb_func_start MOD67_021D8D78
MOD67_021D8D78: ; 0x021D8D78
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x27
	add r6, r3, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r0, [r4, #2]
	bl FUN_02034824
	add r2, r0, #0
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl FUN_0200AFF4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8DD0 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D8DD0: .word 0x00010200
	thumb_func_end MOD67_021D8D78

	thumb_func_start MOD67_021D8DD4
MOD67_021D8DD4: ; 0x021D8DD4
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0x28
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8E0C ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8E0C: .word 0x00010200
	thumb_func_end MOD67_021D8DD4

	thumb_func_start MOD67_021D8E10
MOD67_021D8E10: ; 0x021D8E10
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0x2a
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8E48 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8E48: .word 0x00010200
	thumb_func_end MOD67_021D8E10

	thumb_func_start MOD67_021D8E4C
MOD67_021D8E4C: ; 0x021D8E4C
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0x2b
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8E84 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8E84: .word 0x00010200
	thumb_func_end MOD67_021D8E4C

	thumb_func_start MOD67_021D8E88
MOD67_021D8E88: ; 0x021D8E88
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0x1b
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8EC0 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8EC0: .word 0x00010200
	thumb_func_end MOD67_021D8E88

	thumb_func_start MOD67_021D8EC4
MOD67_021D8EC4: ; 0x021D8EC4
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0x1c
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8EFC ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8EFC: .word 0x00010200
	thumb_func_end MOD67_021D8EC4

	thumb_func_start MOD67_021D8F00
MOD67_021D8F00: ; 0x021D8F00
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r4, r2, #0
	str r3, [sp, #0xc]
	mov r0, #0x2a
	add r7, r1, #0
	bl AllocMonZeroed
	str r4, [sp]
	mov r1, #0
	str r1, [sp, #4]
	str r1, [sp, #8]
	add r6, r0, #0
	add r1, r7, #0
	mov r2, #1
	mov r3, #0x20
	bl CreateMonWithGenderNatureLetter
	add r0, r6, #0
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r5, #0x54]
	ldr r1, [sp, #0xc]
	bl FUN_0200AC60
	add r0, r6, #0
	bl FreeToHeap
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD67_021D8F00

	thumb_func_start MOD67_021D8F40
MOD67_021D8F40: ; 0x021D8F40
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r2, #0
	add r5, r0, #0
	ldrb r0, [r4, #1]
	add r7, r1, #0
	lsl r1, r0, #0x1e
	lsr r1, r1, #0x1e
	beq _021D8F58
	cmp r1, #1
	beq _021D8F64
	b _021D8F70
_021D8F58:
	ldr r0, [r5, #0x50]
	mov r1, #0x2c
	bl NewString_ReadMsgData
	add r6, r0, #0
	b _021D8F9A
_021D8F64:
	ldr r0, [r5, #0x50]
	mov r1, #0x2d
	bl NewString_ReadMsgData
	add r6, r0, #0
	b _021D8F9A
_021D8F70:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1e
	bne _021D8F82
	ldr r0, [r5, #0x50]
	mov r1, #0x2e
	bl NewString_ReadMsgData
	add r6, r0, #0
	b _021D8F9A
_021D8F82:
	cmp r0, #1
	ldr r0, [r5, #0x50]
	bne _021D8F92
	mov r1, #0x2f
	bl NewString_ReadMsgData
	add r6, r0, #0
	b _021D8F9A
_021D8F92:
	mov r1, #0x2c
	bl NewString_ReadMsgData
	add r6, r0, #0
_021D8F9A:
	ldrb r2, [r4, #1]
	ldrh r1, [r4, #2]
	add r0, r5, #0
	lsl r2, r2, #0x18
	lsr r2, r2, #0x1e
	mov r3, #0
	bl MOD67_021D8F00
	ldrb r2, [r4, #1]
	ldr r0, [r5, #0x54]
	mov r1, #1
	lsl r2, r2, #0x1a
	lsr r2, r2, #0x1c
	bl FUN_0200B468
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r6, #0
	bl StringExpandPlaceholders
	mov r0, #0x50
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8FE8 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x58]
	add r0, r7, #0
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r6, #0
	bl String_dtor
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8FE8: .word 0x00010200
	thumb_func_end MOD67_021D8F40

	thumb_func_start MOD67_021D8FEC
MOD67_021D8FEC: ; 0x021D8FEC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r2, #0
	add r5, r0, #0
	ldrb r0, [r4, #1]
	add r7, r1, #0
	lsl r1, r0, #0x1e
	lsr r1, r1, #0x1e
	beq _021D9004
	cmp r1, #1
	beq _021D9010
	b _021D901C
_021D9004:
	ldr r0, [r5, #0x50]
	mov r1, #0x30
	bl NewString_ReadMsgData
	add r6, r0, #0
	b _021D9046
_021D9010:
	ldr r0, [r5, #0x50]
	mov r1, #0x31
	bl NewString_ReadMsgData
	add r6, r0, #0
	b _021D9046
_021D901C:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1e
	bne _021D902E
	ldr r0, [r5, #0x50]
	mov r1, #0x32
	bl NewString_ReadMsgData
	add r6, r0, #0
	b _021D9046
_021D902E:
	cmp r0, #1
	ldr r0, [r5, #0x50]
	bne _021D903E
	mov r1, #0x33
	bl NewString_ReadMsgData
	add r6, r0, #0
	b _021D9046
_021D903E:
	mov r1, #0x30
	bl NewString_ReadMsgData
	add r6, r0, #0
_021D9046:
	ldrb r2, [r4, #1]
	ldrh r1, [r4, #2]
	add r0, r5, #0
	lsl r2, r2, #0x18
	lsr r2, r2, #0x1e
	mov r3, #0
	bl MOD67_021D8F00
	ldrb r2, [r4, #1]
	ldr r0, [r5, #0x54]
	mov r1, #1
	lsl r2, r2, #0x1a
	lsr r2, r2, #0x1c
	bl FUN_0200B468
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r6, #0
	bl StringExpandPlaceholders
	mov r0, #0x50
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9094 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x58]
	add r0, r7, #0
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r6, #0
	bl String_dtor
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9094: .word 0x00010200
	thumb_func_end MOD67_021D8FEC

	thumb_func_start MOD67_021D9098
MOD67_021D9098: ; 0x021D9098
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x20
	mov r1, #0x2a
	add r7, r2, #0
	str r3, [sp, #8]
	bl String_ctor
	add r1, r6, #0
	add r4, r0, #0
	bl FUN_02021E28
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, [r5, #0x54]
	ldr r1, [sp, #8]
	add r2, r4, #0
	add r3, r7, #0
	bl FUN_0200ABB4
	add r0, r4, #0
	bl String_dtor
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD67_021D9098

	thumb_func_start MOD67_021D90D4
MOD67_021D90D4: ; 0x021D90D4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r2, #0
	add r5, r0, #0
	ldrb r0, [r4, #1]
	str r1, [sp, #0x10]
	add r6, r3, #0
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	beq _021D90F2
	cmp r0, #1
	beq _021D90FE
	cmp r0, #2
	beq _021D910A
	b _021D9114
_021D90F2:
	ldr r0, [r5, #0x50]
	mov r1, #0x39
	bl NewString_ReadMsgData
	add r7, r0, #0
	b _021D9114
_021D90FE:
	ldr r0, [r5, #0x50]
	mov r1, #0x3a
	bl NewString_ReadMsgData
	add r7, r0, #0
	b _021D9114
_021D910A:
	ldr r0, [r5, #0x50]
	mov r1, #0x3b
	bl NewString_ReadMsgData
	add r7, r0, #0
_021D9114:
	ldrb r2, [r4, #1]
	add r0, r5, #0
	add r1, r4, #2
	lsl r2, r2, #0x1b
	lsr r2, r2, #0x1f
	mov r3, #0
	bl MOD67_021D9098
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x70
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9154 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D9154: .word 0x00010200
	thumb_func_end MOD67_021D90D4

	thumb_func_start MOD67_021D9158
MOD67_021D9158: ; 0x021D9158
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r2, #0
	add r5, r0, #0
	ldrb r0, [r4, #1]
	str r1, [sp, #0x10]
	add r6, r3, #0
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	beq _021D9176
	cmp r0, #1
	beq _021D9182
	cmp r0, #2
	beq _021D918E
	b _021D9198
_021D9176:
	ldr r0, [r5, #0x50]
	mov r1, #0x3c
	bl NewString_ReadMsgData
	add r7, r0, #0
	b _021D9198
_021D9182:
	ldr r0, [r5, #0x50]
	mov r1, #0x3d
	bl NewString_ReadMsgData
	add r7, r0, #0
	b _021D9198
_021D918E:
	ldr r0, [r5, #0x50]
	mov r1, #0x3e
	bl NewString_ReadMsgData
	add r7, r0, #0
_021D9198:
	ldrb r2, [r4, #1]
	add r0, r5, #0
	add r1, r4, #2
	lsl r2, r2, #0x1b
	lsr r2, r2, #0x1f
	mov r3, #0
	bl MOD67_021D9098
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x70
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D91D8 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D91D8: .word 0x00010200
	thumb_func_end MOD67_021D9158

	thumb_func_start MOD67_021D91DC
MOD67_021D91DC: ; 0x021D91DC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r2, #0
	add r5, r0, #0
	ldrb r0, [r4, #1]
	str r1, [sp, #0x10]
	add r6, r3, #0
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	beq _021D91FA
	cmp r0, #1
	beq _021D9206
	cmp r0, #2
	beq _021D9212
	b _021D921C
_021D91FA:
	ldr r0, [r5, #0x50]
	mov r1, #0x3f
	bl NewString_ReadMsgData
	add r7, r0, #0
	b _021D921C
_021D9206:
	ldr r0, [r5, #0x50]
	mov r1, #0x40
	bl NewString_ReadMsgData
	add r7, r0, #0
	b _021D921C
_021D9212:
	ldr r0, [r5, #0x50]
	mov r1, #0x41
	bl NewString_ReadMsgData
	add r7, r0, #0
_021D921C:
	ldrb r2, [r4, #1]
	add r0, r5, #0
	add r1, r4, #2
	lsl r2, r2, #0x1b
	lsr r2, r2, #0x1f
	mov r3, #0
	bl MOD67_021D9098
	ldrb r2, [r4, #1]
	add r1, r4, #0
	add r0, r5, #0
	lsl r2, r2, #0x1a
	add r1, #0x12
	lsr r2, r2, #0x1f
	mov r3, #1
	bl MOD67_021D9098
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x70
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9270 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D9270: .word 0x00010200
	thumb_func_end MOD67_021D91DC

	thumb_func_start MOD67_021D9274
MOD67_021D9274: ; 0x021D9274
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r2, #0
	add r5, r0, #0
	ldrb r0, [r4, #1]
	str r1, [sp, #0x10]
	add r6, r3, #0
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	beq _021D9292
	cmp r0, #1
	beq _021D929E
	cmp r0, #2
	beq _021D92AA
	b _021D92B4
_021D9292:
	ldr r0, [r5, #0x50]
	mov r1, #0x42
	bl NewString_ReadMsgData
	add r7, r0, #0
	b _021D92B4
_021D929E:
	ldr r0, [r5, #0x50]
	mov r1, #0x43
	bl NewString_ReadMsgData
	add r7, r0, #0
	b _021D92B4
_021D92AA:
	ldr r0, [r5, #0x50]
	mov r1, #0x44
	bl NewString_ReadMsgData
	add r7, r0, #0
_021D92B4:
	ldrb r2, [r4, #1]
	add r0, r5, #0
	add r1, r4, #2
	lsl r2, r2, #0x1b
	lsr r2, r2, #0x1f
	mov r3, #0
	bl MOD67_021D9098
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x70
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D92F4 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D92F4: .word 0x00010200
	thumb_func_end MOD67_021D9274

	thumb_func_start MOD67_021D92F8
MOD67_021D92F8: ; 0x021D92F8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r2, #0
	add r5, r0, #0
	ldrb r0, [r4, #1]
	str r1, [sp, #0x10]
	add r6, r3, #0
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	beq _021D9316
	cmp r0, #1
	beq _021D9322
	cmp r0, #2
	beq _021D932E
	b _021D9338
_021D9316:
	ldr r0, [r5, #0x50]
	mov r1, #0x45
	bl NewString_ReadMsgData
	add r7, r0, #0
	b _021D9338
_021D9322:
	ldr r0, [r5, #0x50]
	mov r1, #0x46
	bl NewString_ReadMsgData
	add r7, r0, #0
	b _021D9338
_021D932E:
	ldr r0, [r5, #0x50]
	mov r1, #0x47
	bl NewString_ReadMsgData
	add r7, r0, #0
_021D9338:
	ldrb r2, [r4, #1]
	add r0, r5, #0
	add r1, r4, #2
	lsl r2, r2, #0x1b
	lsr r2, r2, #0x1f
	mov r3, #0
	bl MOD67_021D9098
	ldrb r2, [r4, #1]
	add r1, r4, #0
	add r0, r5, #0
	lsl r2, r2, #0x1a
	add r1, #0x12
	lsr r2, r2, #0x1f
	mov r3, #1
	bl MOD67_021D9098
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x70
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D938C ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D938C: .word 0x00010200
	thumb_func_end MOD67_021D92F8

	thumb_func_start MOD67_021D9390
MOD67_021D9390: ; 0x021D9390
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x48
	add r6, r3, #0
	bl NewString_ReadMsgData
	ldrb r2, [r4, #1]
	add r7, r0, #0
	add r0, r5, #0
	lsl r2, r2, #0x1b
	add r1, r4, #2
	lsr r2, r2, #0x1f
	mov r3, #0
	bl MOD67_021D9098
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x70
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D93E8 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D93E8: .word 0x00010200
	thumb_func_end MOD67_021D9390

	thumb_func_start MOD67_021D93EC
MOD67_021D93EC: ; 0x021D93EC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x49
	add r6, r3, #0
	bl NewString_ReadMsgData
	ldrb r2, [r4, #1]
	add r7, r0, #0
	add r0, r5, #0
	lsl r2, r2, #0x1b
	add r1, r4, #2
	lsr r2, r2, #0x1f
	mov r3, #0
	bl MOD67_021D9098
	ldrb r2, [r4, #1]
	add r1, r4, #0
	add r0, r5, #0
	lsl r2, r2, #0x18
	add r1, #0x22
	lsr r2, r2, #0x1e
	mov r3, #1
	bl MOD67_021D9098
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x70
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9454 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D9454: .word 0x00010200
	thumb_func_end MOD67_021D93EC

	thumb_func_start MOD67_021D9458
MOD67_021D9458: ; 0x021D9458
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0x4a
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x70
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9490 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D9490: .word 0x00010200
	thumb_func_end MOD67_021D9458

	thumb_func_start MOD67_021D9494
MOD67_021D9494: ; 0x021D9494
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x4b
	add r6, r3, #0
	bl NewString_ReadMsgData
	ldrb r2, [r4, #1]
	add r1, r4, #0
	add r7, r0, #0
	lsl r2, r2, #0x18
	add r0, r5, #0
	add r1, #0x22
	lsr r2, r2, #0x1e
	mov r3, #0
	bl MOD67_021D9098
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x70
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D94EC ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D94EC: .word 0x00010200
	thumb_func_end MOD67_021D9494

	thumb_func_start MOD67_021D94F0
MOD67_021D94F0: ; 0x021D94F0
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0x4c
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x70
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9528 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D9528: .word 0x00010200
	thumb_func_end MOD67_021D94F0

	thumb_func_start MOD67_021D952C
MOD67_021D952C: ; 0x021D952C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r2, #0
	add r5, r0, #0
	ldrb r0, [r4, #1]
	str r1, [sp, #0x10]
	add r6, r3, #0
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	beq _021D954A
	cmp r0, #1
	beq _021D9556
	cmp r0, #2
	beq _021D9562
	b _021D956C
_021D954A:
	ldr r0, [r5, #0x50]
	mov r1, #0x4d
	bl NewString_ReadMsgData
	add r7, r0, #0
	b _021D956C
_021D9556:
	ldr r0, [r5, #0x50]
	mov r1, #0x4e
	bl NewString_ReadMsgData
	add r7, r0, #0
	b _021D956C
_021D9562:
	ldr r0, [r5, #0x50]
	mov r1, #0x4f
	bl NewString_ReadMsgData
	add r7, r0, #0
_021D956C:
	ldrb r2, [r4, #1]
	add r0, r5, #0
	add r1, r4, #2
	lsl r2, r2, #0x1b
	lsr r2, r2, #0x1f
	mov r3, #0
	bl MOD67_021D9098
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x70
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D95AC ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D95AC: .word 0x00010200
	thumb_func_end MOD67_021D952C

	thumb_func_start MOD67_021D95B0
MOD67_021D95B0: ; 0x021D95B0
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0x50
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x70
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D95E8 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D95E8: .word 0x00010200
	thumb_func_end MOD67_021D95B0

	thumb_func_start MOD67_021D95EC
MOD67_021D95EC: ; 0x021D95EC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	mov r1, #0x51
	add r4, r2, #0
	add r6, r3, #0
	bl NewString_ReadMsgData
	mov r1, #0
	str r1, [sp]
	mov r3, #1
	str r3, [sp, #4]
	ldrb r2, [r4, #1]
	add r7, r0, #0
	ldr r0, [r5, #0x54]
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x1c
	bl FUN_0200AD38
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x70
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9648 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D9648: .word 0x00010200
	thumb_func_end MOD67_021D95EC

	thumb_func_start MOD67_021D964C
MOD67_021D964C: ; 0x021D964C
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0x52
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x70
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9684 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D9684: .word 0x00010200
	thumb_func_end MOD67_021D964C

	thumb_func_start MOD67_021D9688
MOD67_021D9688: ; 0x021D9688
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	str r1, [sp, #0x10]
	add r4, r2, #0
	mov r1, #0x53
	add r6, r3, #0
	bl NewString_ReadMsgData
	ldrb r2, [r4, #1]
	add r7, r0, #0
	add r0, r5, #0
	lsl r2, r2, #0x1b
	add r1, r4, #2
	lsr r2, r2, #0x1f
	mov r3, #0
	bl MOD67_021D9098
	ldrb r2, [r4, #1]
	add r1, r4, #0
	add r0, r5, #0
	lsl r2, r2, #0x18
	add r1, #0x22
	lsr r2, r2, #0x1e
	mov r3, #1
	bl MOD67_021D9098
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r7, #0
	bl StringExpandPlaceholders
	lsl r0, r6, #4
	add r0, #0x70
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D96F0 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x58]
	add r3, r1, #0
	bl FUN_0201BDE0
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D96F0: .word 0x00010200
	thumb_func_end MOD67_021D9688

	thumb_func_start MOD67_021D96F4
MOD67_021D96F4: ; 0x021D96F4
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0x50]
	add r6, r1, #0
	add r5, r3, #0
	mov r1, #0x54
	bl NewString_ReadMsgData
	add r4, r0, #0
	lsl r0, r5, #4
	add r0, #0x70
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D972C ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D972C: .word 0x00010200
	thumb_func_end MOD67_021D96F4

	.rodata
	.global MOD67_021D9730
MOD67_021D9730: ; 0x021D9730
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD67_021D9740
MOD67_021D9740: ; 0x021D9740
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x08, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD67_021D975C
MOD67_021D975C: ; 0x021D975C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD67_021D9778
MOD67_021D9778: ; 0x021D9778
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1D, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD67_021D9794
MOD67_021D9794: ; 0x021D9794
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1C, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD67_021D97B0
MOD67_021D97B0: ; 0x021D97B0
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD67_021D97D8
MOD67_021D97D8: ; 0x021D97D8
	.byte 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
	.byte 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
	.byte 0x00, 0x01, 0x02, 0x03, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11
	.byte 0x12, 0x13, 0x14, 0x15, 0x16, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x00, 0x01, 0x02, 0x03, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13
	.byte 0x14, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x00, 0x01, 0x02, 0x03, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13
	.byte 0x1C, 0x1D, 0x1E, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x00, 0x01, 0x02, 0x03, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x00, 0x01, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x1C, 0x1D, 0x1E, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF

	.global MOD67_021D98F8
MOD67_021D98F8: ; 0x021D98F8
	.byte 0x00, 0x02, 0x02, 0x18, 0x02, 0x0F, 0x01, 0x00, 0x00, 0x04, 0x04, 0x1B, 0x12, 0x0F, 0x31, 0x00
	.byte 0x01, 0x02, 0x02, 0x18, 0x02, 0x0F, 0x01, 0x00, 0x01, 0x04, 0x04, 0x1B, 0x12, 0x0F, 0x31, 0x00

	.data
	.bss
