	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD85_021D74E0
MOD85_021D74E0: ; 0x021D74E0
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	bl FUN_02015F1C
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #2
	mov r0, #3
	mov r1, #0x4f
	lsl r2, r2, #0x12
	bl FUN_0201681C
	add r0, r5, #0
	mov r1, #8
	mov r2, #0x4f
	bl FUN_02006268
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4]
	strb r0, [r4, #1]
	strb r0, [r4, #2]
	strb r0, [r4, #3]
	strb r0, [r4, #4]
	strb r0, [r4, #5]
	strb r0, [r4, #6]
	strb r0, [r4, #7]
	add r0, r5, #0
	bl FUN_0200628C
	str r0, [r4]
	bl MOD85_021D76CC
	add r5, r0, #0
	str r5, [r4, #4]
	bl MOD85_021D811C
	add r0, r5, #0
	bl MOD85_021D7FCC
	add r0, r5, #0
	bl MOD85_021D76FC
	add r0, r5, #0
	bl MOD85_021D797C
	add r0, r5, #0
	bl MOD85_021D7B28
	bl MOD85_021D7C6C
	add r0, r5, #0
	bl MOD85_021D7CB0
	add r0, r5, #0
	bl MOD85_021D8188
	add r0, r5, #0
	bl MOD85_021DC108
	add r0, r5, #0
	bl MOD85_021DC24C
	add r0, r5, #0
	bl MOD85_021DC384
	mov r1, #0
	mov r0, #0x42
	add r2, r1, #0
	bl FUN_0200433C
	add r0, r5, #0
	bl MOD85_021D8020
	mov r0, #8
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x4f
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021D74E0

	thumb_func_start MOD85_021D75A0
MOD85_021D75A0: ; 0x021D75A0
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	bl FUN_02006278
	ldr r5, [r0, #4]
	ldr r0, [r4]
	cmp r0, #3
	bhi _021D7626
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D75BE: ; jump table
	.short _021D75C6 - _021D75BE - 2 ; case 0
	.short _021D75D6 - _021D75BE - 2 ; case 1
	.short _021D7608 - _021D75BE - 2 ; case 2
	.short _021D7616 - _021D75BE - 2 ; case 3
_021D75C6:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D7626
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D7626
_021D75D6:
	add r0, r5, #0
	bl MOD85_021D820C
	cmp r0, #1
	bne _021D7626
	ldr r0, [r4]
	mov r1, #0
	add r0, r0, #1
	str r0, [r4]
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4f
	str r0, [sp, #8]
	mov r0, #2
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
	add r0, r5, #0
	mov r1, #0
	bl MOD85_021D7FF4
	b _021D7626
_021D7608:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D7626
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021D7616:
	add r0, r5, #0
	bl MOD85_021D8014
	cmp r0, #0
	bne _021D7626
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_021D7626:
	ldr r0, _021D7640 ; =0x0000044C
	ldr r0, [r5, r0]
	bl FUN_02064584
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl MOD85_021DE830
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_021D7640: .word 0x0000044C
	thumb_func_end MOD85_021D75A0

	thumb_func_start MOD85_021D7644
MOD85_021D7644: ; 0x021D7644
	push {r4, r5, r6, lr}
	add r5, r0, #0
	bl FUN_02006278
	add r6, r0, #0
	mov r0, #0
	ldr r4, [r6, #4]
	add r1, r0, #0
	bl FUN_02015F10
	add r0, r6, #0
	add r1, r4, #0
	bl MOD85_021D769C
	add r0, r4, #0
	bl MOD85_021D7FE4
	add r0, r4, #0
	bl MOD85_021D77DC
	add r0, r4, #0
	bl MOD85_021D7BB8
	add r0, r4, #0
	bl MOD85_021D81AC
	add r0, r4, #0
	bl MOD85_021D8044
	add r0, r4, #0
	bl MOD85_021D8134
	add r0, r4, #0
	bl MOD85_021D76F4
	add r0, r5, #0
	bl FUN_0200627C
	mov r0, #0x4f
	bl FUN_020168D0
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD85_021D7644

	thumb_func_start MOD85_021D769C
MOD85_021D769C: ; 0x021D769C
	push {r3, lr}
	add r2, r1, #0
	ldr r3, [r2, #0x60]
	ldr r1, _021D76C8 ; =0x0000C350
	cmp r3, r1
	bls _021D76AA
	add r3, r1, #0
_021D76AA:
	ldr r1, [r0]
	ldr r1, [r1]
	str r3, [r1]
	ldr r3, [r2, #0x20]
	ldr r1, [r0]
	str r3, [r1, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	cmp r0, #0
	beq _021D76C6
	ldr r2, [r2, #0xc]
	mov r1, #0xe
	bl FUN_0202A11C
_021D76C6:
	pop {r3, pc}
	.align 2, 0
_021D76C8: .word 0x0000C350
	thumb_func_end MOD85_021D769C

	thumb_func_start MOD85_021D76CC
MOD85_021D76CC: ; 0x021D76CC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D76EC ; =0x000004C8
	bl MOD85_021D80F8
	ldr r1, [r4]
	ldr r1, [r1]
	str r1, [r0, #0x60]
	add r1, r0, #0
	ldr r2, [r4, #4]
	add r1, #0x88
	str r2, [r1]
	ldr r2, [r4, #0x10]
	ldr r1, _021D76F0 ; =0x000004C4
	str r2, [r0, r1]
	pop {r4, pc}
	.align 2, 0
_021D76EC: .word 0x000004C8
_021D76F0: .word 0x000004C4
	thumb_func_end MOD85_021D76CC

	thumb_func_start MOD85_021D76F4
MOD85_021D76F4: ; 0x021D76F4
	ldr r3, _021D76F8 ; =FreeToHeap
	bx r3
	.align 2, 0
_021D76F8: .word FreeToHeap
	thumb_func_end MOD85_021D76F4

	thumb_func_start MOD85_021D76FC
MOD85_021D76FC: ; 0x021D76FC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	mov r0, #0x4f
	bl FUN_02016B94
	ldr r1, _021D77CC ; =0x0000043C
	str r0, [r4, r1]
	bl MOD85_021D77F8
	ldr r0, _021D77CC ; =0x0000043C
	ldr r0, [r4, r0]
	bl MOD85_021D7818
	bl MOD85_021D7930
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	mov r0, #2
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #4
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #8
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #1
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #2
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #4
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #8
	mov r1, #1
	bl FUN_0201E74C
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	ldr r0, _021D77D0 ; =0x04000008
	mov r2, #3
	ldrh r1, [r0]
	mov r3, #1
	mov r7, #2
	bic r1, r2
	strh r1, [r0]
	ldrh r1, [r0, #2]
	ldr r6, _021D77D4 ; =0x04001008
	bic r1, r2
	orr r1, r3
	strh r1, [r0, #2]
	ldrh r1, [r0, #4]
	bic r1, r2
	orr r1, r7
	strh r1, [r0, #4]
	ldrh r5, [r0, #6]
	mov r1, #3
	bic r5, r2
	orr r5, r1
	strh r5, [r0, #6]
	ldrh r5, [r6]
	bic r5, r2
	strh r5, [r6]
	ldrh r5, [r6, #2]
	bic r5, r2
	orr r3, r5
	strh r3, [r6, #2]
	ldrh r3, [r6, #4]
	add r0, #0x48
	bic r3, r2
	orr r3, r7
	strh r3, [r6, #4]
	ldrh r3, [r6, #6]
	bic r3, r2
	orr r1, r3
	strh r1, [r6, #6]
	mov r1, #9
	str r1, [sp]
	mov r1, #4
	mov r2, #0x10
	mov r3, #8
	bl G2x_SetBlendAlpha_
	ldr r0, _021D77D8 ; =MOD85_021D80DC
	add r1, r4, #0
	bl FUN_02015F10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D77CC: .word 0x0000043C
_021D77D0: .word 0x04000008
_021D77D4: .word 0x04001008
_021D77D8: .word MOD85_021D80DC
	thumb_func_end MOD85_021D76FC

	thumb_func_start MOD85_021D77DC
MOD85_021D77DC: ; 0x021D77DC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D77F4 ; =0x0000043C
	ldr r0, [r4, r0]
	bl MOD85_021D7904
	add r0, r4, #0
	bl MOD85_021D7D04
	bl MOD85_021D7CA4
	pop {r4, pc}
	.align 2, 0
_021D77F4: .word 0x0000043C
	thumb_func_end MOD85_021D77DC

	thumb_func_start MOD85_021D77F8
MOD85_021D77F8: ; 0x021D77F8
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D7814 ; =0x021DED7C
	add r3, sp, #0
	mov r2, #5
_021D7802:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7802
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D7814: .word MOD85_021DED7C
	thumb_func_end MOD85_021D77F8

	thumb_func_start MOD85_021D7818
MOD85_021D7818: ; 0x021D7818
	push {r3, r4, r5, lr}
	sub sp, #0x80
	ldr r2, _021D78EC ; =0x04000304
	add r4, r0, #0
	ldrh r1, [r2]
	lsr r0, r2, #0xb
	ldr r5, _021D78F0 ; =0x021DECEC
	orr r0, r1
	strh r0, [r2]
	add r3, sp, #0x70
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _021D78F4 ; =0x021DED28
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
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x4f
	bl FUN_02017F18
	ldr r5, _021D78F8 ; =0x021DED44
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
	ldr r5, _021D78FC ; =0x021DED60
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
	add r0, r4, #0
	mov r1, #2
	bl FUN_02018744
	ldr r5, _021D7900 ; =0x021DED0C
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #7
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #7
	bl FUN_02018744
	add sp, #0x80
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D78EC: .word 0x04000304
_021D78F0: .word MOD85_021DECEC
_021D78F4: .word MOD85_021DED28
_021D78F8: .word MOD85_021DED44
_021D78FC: .word MOD85_021DED60
_021D7900: .word MOD85_021DED0C
	thumb_func_end MOD85_021D7818

	thumb_func_start MOD85_021D7904
MOD85_021D7904: ; 0x021D7904
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #2
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #7
	bl FUN_020178A0
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D7904

	thumb_func_start MOD85_021D7930
MOD85_021D7930: ; 0x021D7930
	push {r4, r5}
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r2, [r0]
	ldr r1, _021D7978 ; =0xFFFF1FFF
	add r5, r0, #0
	and r2, r1
	lsr r1, r0, #0xd
	orr r1, r2
	str r1, [r0]
	add r5, #0x48
	ldrh r3, [r5]
	mov r1, #0x3f
	mov r2, #0x1f
	bic r3, r1
	add r4, r3, #0
	orr r4, r2
	mov r3, #0x20
	orr r4, r3
	strh r4, [r5]
	add r4, r0, #0
	add r4, #0x4a
	ldrh r5, [r4]
	bic r5, r1
	add r1, r5, #0
	orr r1, r2
	orr r1, r3
	strh r1, [r4]
	add r1, r0, #0
	mov r2, #0xff
	add r1, #0x40
	strh r2, [r1]
	add r0, #0x44
	strh r2, [r0]
	pop {r4, r5}
	bx lr
	.align 2, 0
_021D7978: .word 0xFFFF1FFF
	thumb_func_end MOD85_021D7930

	thumb_func_start MOD85_021D797C
MOD85_021D797C: ; 0x021D797C
	push {r3, r4, r5, lr}
	mov r1, #3
	mov r2, #0
	add r4, r0, #0
	bl MOD85_021D8144
	ldr r1, _021D7B1C ; =0x00000448
	add r5, r0, #0
	add r1, r4, r1
	bl FUN_020B0138
	ldr r1, _021D7B1C ; =0x00000448
	mov r2, #0x1a
	ldr r1, [r4, r1]
	mov r0, #1
	ldr r1, [r1, #0xc]
	lsl r2, r2, #4
	mov r3, #0
	bl FUN_02017FB4
	add r0, r5, #0
	bl FreeToHeap
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl MOD85_021D8144
	ldr r1, _021D7B20 ; =0x00000444
	add r5, r0, #0
	add r1, r4, r1
	bl FUN_020B0088
	ldr r0, _021D7B20 ; =0x00000444
	mov r1, #0
	ldr r3, [r4, r0]
	sub r0, #8
	str r1, [sp]
	ldr r2, [r3, #0x14]
	ldr r0, [r4, r0]
	ldr r3, [r3, #0x10]
	mov r1, #1
	bl FUN_02017E14
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD85_021D8144
	mov r1, #0x11
	lsl r1, r1, #6
	add r1, r4, r1
	add r5, r0, #0
	bl FUN_020B0180
	mov r0, #0x11
	lsl r0, r0, #6
	ldr r3, [r4, r0]
	sub r0, r0, #4
	add r2, r3, #0
	ldr r0, [r4, r0]
	ldr r3, [r3, #8]
	mov r1, #1
	add r2, #0xc
	bl FUN_02017DFC
	ldr r0, _021D7B24 ; =0x0000043C
	mov r1, #1
	ldr r0, [r4, r0]
	bl FUN_02017CD0
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	mov r1, #8
	mov r2, #0
	bl MOD85_021D8144
	ldr r1, _021D7B20 ; =0x00000444
	add r5, r0, #0
	add r1, r4, r1
	bl FUN_020B0088
	ldr r0, _021D7B20 ; =0x00000444
	mov r1, #0
	ldr r3, [r4, r0]
	sub r0, #8
	str r1, [sp]
	ldr r2, [r3, #0x14]
	ldr r0, [r4, r0]
	ldr r3, [r3, #0x10]
	mov r1, #2
	bl FUN_02017E14
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	mov r1, #9
	mov r2, #0
	bl MOD85_021D8144
	mov r1, #0x11
	lsl r1, r1, #6
	add r1, r4, r1
	add r5, r0, #0
	bl FUN_020B0180
	mov r0, #0x11
	lsl r0, r0, #6
	ldr r3, [r4, r0]
	sub r0, r0, #4
	add r2, r3, #0
	ldr r0, [r4, r0]
	ldr r3, [r3, #8]
	mov r1, #2
	add r2, #0xc
	bl FUN_02017DFC
	ldr r0, _021D7B24 ; =0x0000043C
	mov r1, #2
	ldr r0, [r4, r0]
	bl FUN_02017CD0
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	mov r1, #3
	mov r2, #0
	bl MOD85_021D8144
	ldr r1, _021D7B1C ; =0x00000448
	add r5, r0, #0
	add r1, r4, r1
	bl FUN_020B0138
	ldr r1, _021D7B1C ; =0x00000448
	mov r2, #0x1a
	ldr r1, [r4, r1]
	mov r0, #7
	ldr r1, [r1, #0xc]
	lsl r2, r2, #4
	mov r3, #0
	bl FUN_02017FB4
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	mov r1, #2
	mov r2, #0
	bl MOD85_021D8144
	ldr r1, _021D7B20 ; =0x00000444
	add r5, r0, #0
	add r1, r4, r1
	bl FUN_020B0088
	ldr r0, _021D7B20 ; =0x00000444
	mov r1, #0
	ldr r3, [r4, r0]
	sub r0, #8
	str r1, [sp]
	ldr r2, [r3, #0x14]
	ldr r0, [r4, r0]
	ldr r3, [r3, #0x10]
	mov r1, #7
	bl FUN_02017E14
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	mov r1, #4
	mov r2, #0
	bl MOD85_021D8144
	mov r1, #0x11
	lsl r1, r1, #6
	add r1, r4, r1
	add r5, r0, #0
	bl FUN_020B0180
	mov r0, #0x11
	lsl r0, r0, #6
	ldr r3, [r4, r0]
	sub r0, r0, #4
	add r2, r3, #0
	ldr r0, [r4, r0]
	ldr r3, [r3, #8]
	mov r1, #7
	add r2, #0xc
	bl FUN_02017DFC
	ldr r0, _021D7B24 ; =0x0000043C
	mov r1, #7
	ldr r0, [r4, r0]
	bl FUN_02017CD0
	add r0, r5, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7B1C: .word 0x00000448
_021D7B20: .word 0x00000444
_021D7B24: .word 0x0000043C
	thumb_func_end MOD85_021D797C

	thumb_func_start MOD85_021D7B28
MOD85_021D7B28: ; 0x021D7B28
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, _021D7BA4 ; =0x00000408
	mov r1, #0
	add r4, r5, r0
	str r1, [sp]
	mov r2, #0x4f
	str r2, [sp, #4]
	add r0, #0x34
	ldr r0, [r5, r0]
	mov r2, #1
	mov r3, #0xf
	bl FUN_0200CB00
	ldr r1, _021D7BA8 ; =0x000004C4
	mov r2, #0x1f
	ldr r0, [r5, r1]
	sub r1, #0x88
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x4f
	str r0, [sp, #4]
	ldr r0, [r5, r1]
	mov r1, #0
	mov r3, #0xe
	bl FUN_0200CD68
	mov r1, #0x1e
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x4f
	bl FUN_02002EEC
	ldr r2, _021D7BAC ; =0x000001E9
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x4f
	bl NewMsgDataFromNarc
	ldr r1, _021D7BA4 ; =0x00000408
	str r0, [r5, r1]
	mov r0, #0x4f
	bl FUN_0200AA80
	str r0, [r4, #4]
	ldr r0, _021D7BB0 ; =0x0000043C
	add r1, r4, #0
	ldr r0, [r5, r0]
	ldr r2, _021D7BB4 ; =0x021DECE4
	add r1, #8
	bl FUN_02019150
	mov r0, #1
	lsl r0, r0, #8
	mov r1, #0x4f
	bl String_ctor
	str r0, [r4, #0x18]
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7BA4: .word 0x00000408
_021D7BA8: .word 0x000004C4
_021D7BAC: .word 0x000001E9
_021D7BB0: .word 0x0000043C
_021D7BB4: .word MOD85_021DECE4
	thumb_func_end MOD85_021D7B28

	thumb_func_start MOD85_021D7BB8
MOD85_021D7BB8: ; 0x021D7BB8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _021D7BE8 ; =0x00000408
	add r4, r5, r0
	add r6, r4, #0
	add r6, #8
	add r0, r6, #0
	bl FUN_02019570
	add r0, r6, #0
	bl FUN_02019178
	ldr r0, _021D7BE8 ; =0x00000408
	ldr r0, [r5, r0]
	bl DestroyMsgData
	ldr r0, [r4, #4]
	bl FUN_0200AB18
	ldr r0, [r4, #0x18]
	bl String_dtor
	pop {r4, r5, r6, pc}
	nop
_021D7BE8: .word 0x00000408
	thumb_func_end MOD85_021D7BB8

	thumb_func_start MOD85_021D7BEC
MOD85_021D7BEC: ; 0x021D7BEC
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, _021D7C40 ; =0x00000408
	add r6, r1, #0
	add r4, r5, r0
	add r0, r4, #0
	add r0, #8
	mov r1, #1
	mov r2, #0x1f
	mov r3, #0xe
	bl FUN_0200D0BC
	add r0, r4, #0
	add r0, #8
	mov r1, #0xf
	bl FUN_02019620
	ldr r0, _021D7C40 ; =0x00000408
	ldr r2, [r4, #0x18]
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl ReadMsgDataIntoString
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r3, [sp, #8]
	add r0, r4, #0
	ldr r2, [r4, #0x18]
	add r0, #8
	mov r1, #1
	bl FUN_0201BD84
	add r4, #8
	add r0, r4, #0
	bl FUN_02019220
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021D7C40: .word 0x00000408
	thumb_func_end MOD85_021D7BEC

	thumb_func_start MOD85_021D7C44
MOD85_021D7C44: ; 0x021D7C44
	push {r3, r4, r5, lr}
	ldr r4, _021D7C68 ; =0x00000408
	add r5, r0, #0
	add r0, r5, r4
	add r0, #8
	mov r1, #1
	bl FUN_0200D0E0
	add r0, r5, r4
	add r0, #8
	mov r1, #0
	bl FUN_02019620
	add r0, r5, r4
	add r0, #8
	bl FUN_02019220
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7C68: .word 0x00000408
	thumb_func_end MOD85_021D7C44

	thumb_func_start MOD85_021D7C6C
MOD85_021D7C6C: ; 0x021D7C6C
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _021D7C9C ; =0x021DECFC
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r1, _021D7CA0 ; =0x00200010
	add r0, r2, #0
	add r2, r1, #0
	bl FUN_0201D060
	mov r0, #0x10
	mov r1, #0x4f
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021D7C9C: .word MOD85_021DECFC
_021D7CA0: .word 0x00200010
	thumb_func_end MOD85_021D7C6C

	thumb_func_start MOD85_021D7CA4
MOD85_021D7CA4: ; 0x021D7CA4
	push {r3, lr}
	bl FUN_0201D12C
	bl FUN_0201E08C
	pop {r3, pc}
	thumb_func_end MOD85_021D7CA4

	thumb_func_start MOD85_021D7CB0
MOD85_021D7CB0: ; 0x021D7CB0
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r0, #0
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r1, #0x80
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x4f
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	mov r0, #0x10
	str r0, [sp]
	mov r1, #0x40
	str r1, [sp, #4]
	mov r2, #0x20
	str r2, [sp, #8]
	mov r3, #0xb
	str r3, [sp, #0xc]
	mov r0, #8
	str r0, [sp, #0x10]
	str r3, [sp, #0x14]
	str r3, [sp, #0x18]
	mov r0, #0x4f
	add r3, r1, #0
	bl MOD85_021DE5A4
	mov r1, #0x45
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD85_021D7D1C
	add sp, #0x1c
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D7CB0

	thumb_func_start MOD85_021D7D04
MOD85_021D7D04: ; 0x021D7D04
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021D7FC8
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD85_021DE710
	bl FUN_02009FA0
	pop {r4, pc}
	thumb_func_end MOD85_021D7D04

	thumb_func_start MOD85_021D7D1C
MOD85_021D7D1C: ; 0x021D7D1C
	push {r3, r4, lr}
	sub sp, #4
	mov r2, #0x45
	add r4, r0, #0
	mov r0, #0
	lsl r2, r2, #4
	str r0, [sp]
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	mov r1, #1
	mov r3, #0xb
	bl MOD85_021DE840
	mov r1, #1
	mov r2, #0x45
	str r1, [sp]
	lsl r2, r2, #4
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	mov r3, #0x15
	bl MOD85_021DE840
	mov r2, #0x45
	mov r0, #6
	lsl r2, r2, #4
	str r0, [sp]
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	mov r1, #2
	mov r3, #0x44
	bl MOD85_021DE840
	mov r2, #0x45
	mov r0, #7
	lsl r2, r2, #4
	str r0, [sp]
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	mov r1, #2
	mov r3, #0x47
	bl MOD85_021DE840
	mov r2, #0x45
	mov r0, #8
	lsl r2, r2, #4
	str r0, [sp]
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	mov r1, #2
	mov r3, #0x40
	bl MOD85_021DE840
	mov r2, #0x45
	mov r0, #9
	lsl r2, r2, #4
	str r0, [sp]
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	mov r1, #2
	mov r3, #0x3c
	bl MOD85_021DE840
	mov r2, #0x45
	mov r0, #0
	lsl r2, r2, #4
	str r0, [sp]
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	mov r1, #3
	mov r3, #0xa
	bl MOD85_021DE910
	mov r1, #1
	mov r2, #0x45
	str r1, [sp]
	lsl r2, r2, #4
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	mov r3, #0x14
	bl MOD85_021DE910
	mov r2, #0x45
	mov r0, #6
	lsl r2, r2, #4
	str r0, [sp]
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	mov r1, #2
	mov r3, #0x43
	bl MOD85_021DE910
	mov r2, #0x45
	mov r0, #7
	lsl r2, r2, #4
	str r0, [sp]
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	mov r1, #2
	mov r3, #0x3f
	bl MOD85_021DE910
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0xc
	mov r3, #0
	bl MOD85_021DE9E4
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x16
	mov r3, #1
	bl MOD85_021DE9E4
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x45
	mov r3, #6
	bl MOD85_021DE9E4
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x48
	mov r3, #7
	bl MOD85_021DE9E4
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x41
	mov r3, #8
	bl MOD85_021DE9E4
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x3d
	mov r3, #9
	bl MOD85_021DE9E4
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0xd
	mov r3, #0
	bl MOD85_021DEA4C
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x17
	mov r3, #1
	bl MOD85_021DEA4C
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x46
	mov r3, #6
	bl MOD85_021DEA4C
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x49
	mov r3, #7
	bl MOD85_021DEA4C
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x42
	mov r3, #8
	bl MOD85_021DEA4C
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x3e
	mov r3, #9
	bl MOD85_021DEA4C
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD85_021DE8A8
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl MOD85_021DE8A8
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD85_021DE8A8
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #7
	bl MOD85_021DE8A8
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #8
	bl MOD85_021DE8A8
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #9
	bl MOD85_021DE8A8
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD85_021DE8DC
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl MOD85_021DE8DC
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD85_021DE8DC
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #7
	bl MOD85_021DE8DC
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #8
	bl MOD85_021DE8DC
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #9
	bl MOD85_021DE8DC
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD85_021DE97C
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl MOD85_021DE97C
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD85_021DE97C
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #7
	bl MOD85_021DE97C
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD85_021DE9B0
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl MOD85_021DE9B0
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #6
	bl MOD85_021DE9B0
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #7
	bl MOD85_021DE9B0
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D7D1C

	thumb_func_start MOD85_021D7FC8
MOD85_021D7FC8: ; 0x021D7FC8
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021D7FC8

	thumb_func_start MOD85_021D7FCC
MOD85_021D7FCC: ; 0x021D7FCC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x4f
	mov r1, #0x80
	bl FUN_020643C0
	ldr r1, _021D7FE0 ; =0x0000044C
	str r0, [r4, r1]
	pop {r4, pc}
	nop
_021D7FE0: .word 0x0000044C
	thumb_func_end MOD85_021D7FCC

	thumb_func_start MOD85_021D7FE4
MOD85_021D7FE4: ; 0x021D7FE4
	ldr r1, _021D7FEC ; =0x0000044C
	ldr r3, _021D7FF0 ; =FUN_020643F0
	ldr r0, [r0, r1]
	bx r3
	.align 2, 0
_021D7FEC: .word 0x0000044C
_021D7FF0: .word FUN_020643F0
	thumb_func_end MOD85_021D7FE4

	thumb_func_start MOD85_021D7FF4
MOD85_021D7FF4: ; 0x021D7FF4
	ldr r2, _021D8010 ; =0x00000424
	add r2, r0, r2
	ldr r0, [r2, #8]
	cmp r0, r1
	beq _021D800C
	ldr r0, [r2, #0xc]
	cmp r0, r1
	beq _021D800C
	str r1, [r2, #0xc]
	mov r0, #1
	str r0, [r2]
	str r0, [r2, #4]
_021D800C:
	bx lr
	nop
_021D8010: .word 0x00000424
	thumb_func_end MOD85_021D7FF4

	thumb_func_start MOD85_021D8014
MOD85_021D8014: ; 0x021D8014
	ldr r1, _021D801C ; =0x00000428
	ldr r0, [r0, r1]
	bx lr
	nop
_021D801C: .word 0x00000428
	thumb_func_end MOD85_021D8014

	thumb_func_start MOD85_021D8020
MOD85_021D8020: ; 0x021D8020
	push {r4, lr}
	add r1, r0, #0
	ldr r0, _021D803C ; =0x00000424
	mov r2, #0x90
	add r4, r1, r0
	mov r0, #0
	str r0, [r4, #8]
	mov r0, #3
	str r0, [r4, #0xc]
	ldr r0, _021D8040 ; =MOD85_021D8054
	bl FUN_0200CA44
	str r0, [r4, #0x10]
	pop {r4, pc}
	.align 2, 0
_021D803C: .word 0x00000424
_021D8040: .word MOD85_021D8054
	thumb_func_end MOD85_021D8020

	thumb_func_start MOD85_021D8044
MOD85_021D8044: ; 0x021D8044
	ldr r1, _021D804C ; =0x00000434
	ldr r3, _021D8050 ; =FUN_0200CAB4
	ldr r0, [r0, r1]
	bx r3
	.align 2, 0
_021D804C: .word 0x00000434
_021D8050: .word FUN_0200CAB4
	thumb_func_end MOD85_021D8044

	thumb_func_start MOD85_021D8054
MOD85_021D8054: ; 0x021D8054
	push {r4, lr}
	ldr r0, _021D80D8 ; =0x00000424
	add r4, r1, r0
	ldr r1, [r4]
	cmp r1, #0
	beq _021D80D4
	cmp r1, #1
	beq _021D806A
	cmp r1, #2
	beq _021D809E
	pop {r4, pc}
_021D806A:
	ldr r1, [r4, #8]
	cmp r1, #0
	beq _021D807A
	cmp r1, #1
	beq _021D8084
	cmp r1, #2
	beq _021D808E
	b _021D8096
_021D807A:
	mov r0, #1
	add r1, r0, #0
	bl FUN_020047C8
	b _021D8096
_021D8084:
	add r0, #0x7c
	mov r1, #0
	bl FUN_02005350
	b _021D8096
_021D808E:
	add r0, #0x7d
	mov r1, #0
	bl FUN_02005350
_021D8096:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_021D809E:
	ldr r1, [r4, #0xc]
	cmp r1, #0
	beq _021D80AE
	cmp r1, #1
	beq _021D80B8
	cmp r1, #2
	beq _021D80C0
	b _021D80C6
_021D80AE:
	mov r0, #1
	mov r1, #0
	bl FUN_020047C8
	b _021D80C6
_021D80B8:
	add r0, #0x7c
	bl FUN_020051F4
	b _021D80C6
_021D80C0:
	add r0, #0x7d
	bl FUN_020051F4
_021D80C6:
	ldr r0, [r4, #0xc]
	str r0, [r4, #8]
	mov r0, #3
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4, #4]
	str r0, [r4]
_021D80D4:
	pop {r4, pc}
	nop
_021D80D8: .word 0x00000424
	thumb_func_end MOD85_021D8054

	thumb_func_start MOD85_021D80DC
MOD85_021D80DC: ; 0x021D80DC
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0201C30C
	bl FUN_02009F80
	ldr r0, _021D80F4 ; =0x0000043C
	ldr r0, [r4, r0]
	bl FUN_0201AB60
	pop {r4, pc}
	nop
_021D80F4: .word 0x0000043C
	thumb_func_end MOD85_021D80DC

	thumb_func_start MOD85_021D80F8
MOD85_021D80F8: ; 0x021D80F8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x4f
	add r1, r5, #0
	bl AllocFromHeap
	add r4, r0, #0
	bne _021D810C
	bl ErrorHandling
_021D810C:
	add r0, r4, #0
	mov r1, #0
	add r2, r5, #0
	bl memset
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021D80F8

	thumb_func_start MOD85_021D811C
MOD85_021D811C: ; 0x021D811C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x85
	mov r1, #0x4f
	bl NARC_ctor
	ldr r1, _021D8130 ; =0x00000438
	str r0, [r4, r1]
	pop {r4, pc}
	nop
_021D8130: .word 0x00000438
	thumb_func_end MOD85_021D811C

	thumb_func_start MOD85_021D8134
MOD85_021D8134: ; 0x021D8134
	ldr r1, _021D813C ; =0x00000438
	ldr r3, _021D8140 ; =NARC_dtor
	ldr r0, [r0, r1]
	bx r3
	.align 2, 0
_021D813C: .word 0x00000438
_021D8140: .word NARC_dtor
	thumb_func_end MOD85_021D8134

	thumb_func_start MOD85_021D8144
MOD85_021D8144: ; 0x021D8144
	push {r4, r5, r6, lr}
	add r4, r0, #0
	ldr r0, _021D8184 ; =0x00000438
	add r6, r1, #0
	ldr r0, [r4, r0]
	add r5, r2, #0
	bl NARC_GetMemberSize
	add r1, r0, #0
	cmp r5, #1
	bne _021D8162
	mov r0, #0x4f
	bl AllocFromHeap
	b _021D8168
_021D8162:
	mov r0, #0x4f
	bl AllocFromHeapAtEnd
_021D8168:
	add r5, r0, #0
	cmp r5, #0
	bne _021D8172
	bl ErrorHandling
_021D8172:
	ldr r0, _021D8184 ; =0x00000438
	add r1, r6, #0
	ldr r0, [r4, r0]
	add r2, r5, #0
	bl NARC_ReadWholeMember
	add r0, r5, #0
	pop {r4, r5, r6, pc}
	nop
_021D8184: .word 0x00000438
	thumb_func_end MOD85_021D8144

	thumb_func_start MOD85_021D8188
MOD85_021D8188: ; 0x021D8188
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021D81C8
	add r0, r4, #0
	bl MOD85_021D92E8
	add r0, r4, #0
	bl MOD85_021DAD20
	add r0, r4, #0
	bl MOD85_021DAEC0
	add r0, r4, #0
	bl MOD85_021DB494
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D8188

	thumb_func_start MOD85_021D81AC
MOD85_021D81AC: ; 0x021D81AC
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021D931C
	add r0, r4, #0
	bl MOD85_021DAD44
	add r0, r4, #0
	bl MOD85_021DAEE4
	add r0, r4, #0
	bl MOD85_021DB600
	pop {r4, pc}
	thumb_func_end MOD85_021D81AC

	thumb_func_start MOD85_021D81C8
MOD85_021D81C8: ; 0x021D81C8
	push {r3, r4, r5, r6, r7, lr}
	mov r7, #0x15
	add r5, r0, #0
	mov r4, #0
	lsl r6, r7, #0x11
_021D81D2:
	bl LCRandom
	add r1, r7, #0
	bl _s32_div_f
	add r0, r5, #0
	add r0, #0xa8
	str r1, [r0]
	lsl r0, r1, #0x11
	sub r1, r6, r0
	add r0, r5, #0
	add r0, #0x90
	str r1, [r0]
	add r0, r5, #0
	add r0, #0x90
	mov r1, #0x2a
	ldr r0, [r0]
	lsl r1, r1, #0x10
	bl _s32_div_f
	add r0, r5, #0
	add r0, #0x90
	add r4, r4, #1
	add r5, r5, #4
	str r1, [r0]
	cmp r4, #3
	blt _021D81D2
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021D81C8

	thumb_func_start MOD85_021D820C
MOD85_021D820C: ; 0x021D820C
	push {r3, r4, r5, lr}
	ldr r4, _021D822C ; =0x021DEF94
	add r5, r0, #0
_021D8212:
	ldr r1, [r5]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	blx r1
	cmp r0, #1
	beq _021D8212
	cmp r0, #2
	bne _021D8228
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8228:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D822C: .word MOD85_021DEF94
	thumb_func_end MOD85_021D820C

	thumb_func_start MOD85_021D8230
MOD85_021D8230: ; 0x021D8230
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	str r1, [r4, #0x64]
	mov r3, #1
	add r2, r4, #0
	str r1, [r4, #0x68]
	lsl r3, r3, #0x10
	add r2, #0x8c
	str r3, [r2]
	str r1, [r4, #0x74]
	str r1, [r4, #8]
	mov r2, #1
	str r2, [r4]
	bl MOD85_021DC094
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021DC094
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021DC094
	add r0, r4, #0
	bl MOD85_021DB754
	add r0, r4, #0
	bl MOD85_021DB95C
	ldr r1, [r4, #0x60]
	cmp r1, #0
	bne _021D827C
	mov r0, #0x3c
	str r0, [r4]
	mov r0, #0x3f
	str r0, [r4, #4]
	b _021D8298
_021D827C:
	cmp r1, #3
	bge _021D828A
	mov r0, #0x3b
	str r0, [r4]
	mov r0, #0x3f
	str r0, [r4, #4]
	b _021D8298
_021D828A:
	ldr r0, _021D829C ; =0x0000C350
	cmp r1, r0
	blt _021D8298
	mov r0, #0x3d
	str r0, [r4]
	mov r0, #1
	str r0, [r4, #4]
_021D8298:
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_021D829C: .word 0x0000C350
	thumb_func_end MOD85_021D8230

	thumb_func_start MOD85_021D82A0
MOD85_021D82A0: ; 0x021D82A0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #8
	bl MOD85_021DBD54
	cmp r0, #0
	beq _021D82BC
	add r0, r4, #0
	bl MOD85_021DB9A0
	mov r0, #0x3f
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
_021D82BC:
	mov r0, #1
	lsl r0, r0, #0xa
	bl MOD85_021DBD54
	cmp r0, #0
	beq _021D82F0
	ldr r0, [r4, #0x60]
	sub r0, r0, #3
	str r0, [r4, #0x60]
	ldr r0, _021D82F4 ; =0x0000045C
	ldr r1, [r4, r0]
	add r1, r1, #3
	str r1, [r4, r0]
	mov r0, #2
	str r0, [r4]
	ldr r0, _021D82F8 ; =0x000005ED
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD85_021DB9A0
	add r0, r4, #0
	bl MOD85_021DB76C
	mov r0, #0
	pop {r4, pc}
_021D82F0:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D82F4: .word 0x0000045C
_021D82F8: .word 0x000005ED
	thumb_func_end MOD85_021D82A0

	thumb_func_start MOD85_021D82FC
MOD85_021D82FC: ; 0x021D82FC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #8
	bl MOD85_021DBD54
	cmp r0, #0
	beq _021D8318
	ldr r0, [r4, #0x60]
	add r0, r0, #3
	str r0, [r4, #0x60]
	mov r0, #0x3f
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
_021D8318:
	mov r0, #0x12
	lsl r0, r0, #6
	bl MOD85_021DBD54
	cmp r0, #0
	beq _021D832C
	mov r0, #3
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D832C:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021D82FC

	thumb_func_start MOD85_021D8330
MOD85_021D8330: ; 0x021D8330
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DA804
	mov r0, #0x46
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	add r1, r0, #4
	ldr r1, [r4, r1]
	add r0, r0, #4
	add r1, r1, #1
	str r1, [r4, r0]
	mov r0, #0
	str r0, [r4, #0x70]
	ldr r1, [r4, #0x74]
	mov r0, #0x33
	tst r0, r1
	beq _021D835C
	mov r0, #1
	str r0, [r4, #0x70]
_021D835C:
	mov r0, #0
	str r0, [r4, #0x30]
	ldr r0, [r4, #0x74]
	cmp r0, #0
	beq _021D8398
	add r0, r4, #0
	bl MOD85_021DA948
	cmp r0, #0
	bne _021D8378
	mov r0, #0x55
	mov r1, #4
	lsl r0, r0, #2
	b _021D838C
_021D8378:
	ldr r0, [r4, #0x74]
	bl MOD85_021DBF70
	mov r1, #0x55
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0x49
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	add r1, r1, #1
_021D838C:
	str r1, [r4, r0]
	mov r1, #1
	add r0, r4, #0
	str r1, [r4, #0x30]
	bl MOD85_021DAEF4
_021D8398:
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021DC094
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021DC094
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021DC094
	add r0, r4, #0
	bl MOD85_021DB76C
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021D9338
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021D9338
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021D9338
	add r0, r4, #0
	bl MOD85_021DBFA4
	mov r1, #1
	add r0, r4, #0
	str r1, [r4, #0x7c]
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x84
	str r1, [r0]
	mov r0, #0
	str r0, [r4, #0x6c]
	mov r0, #4
	str r0, [r4]
	ldr r0, _021D83F8 ; =0x000005EE
	bl FUN_020054C8
	mov r0, #1
	pop {r4, pc}
	nop
_021D83F8: .word 0x000005EE
	thumb_func_end MOD85_021D8330

	thumb_func_start MOD85_021D83FC
MOD85_021D83FC: ; 0x021D83FC
	mov r1, #1
	ldr r2, [r0, #0x6c]
	lsl r1, r1, #0xc
	add r2, r2, r1
	lsl r1, r1, #3
	str r2, [r0, #0x6c]
	cmp r2, r1
	blt _021D8418
	mov r1, #0
	str r1, [r0, #0x6c]
	mov r1, #5
	str r1, [r0]
	mov r0, #1
	bx lr
_021D8418:
	mov r0, #0
	bx lr
	thumb_func_end MOD85_021D83FC

	thumb_func_start MOD85_021D841C
MOD85_021D841C: ; 0x021D841C
	push {r4, lr}
	ldr r1, _021D850C ; =0x021C48B8
	add r4, r0, #0
	ldr r2, [r1, #0x48]
	ldr r1, [r4, #0x7c]
	cmp r1, #1
	bne _021D8462
	mov r1, #2
	lsl r1, r1, #0xa
	add r3, r2, #0
	tst r3, r1
	beq _021D8462
	mov r2, #2
	str r2, [r4, #0x7c]
	bl MOD85_021DBFB4
	add r0, r4, #0
	bl MOD85_021DBFDC
	cmp r0, #0
	bne _021D844A
	mov r0, #0
	str r0, [r4, #0x70]
_021D844A:
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021DC050
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021D9350
	ldr r0, _021D8510 ; =0x00000626
	bl FUN_020054C8
	b _021D84EA
_021D8462:
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #1
	bne _021D84A6
	mov r1, #2
	add r0, r2, #0
	tst r0, r1
	beq _021D84A6
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	bl MOD85_021DBFB4
	add r0, r4, #0
	bl MOD85_021DBFDC
	cmp r0, #0
	bne _021D848E
	mov r0, #0
	str r0, [r4, #0x70]
_021D848E:
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021DC050
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021D9350
	ldr r0, _021D8510 ; =0x00000626
	bl FUN_020054C8
	b _021D84EA
_021D84A6:
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #1
	bne _021D84EA
	mov r1, #1
	add r0, r2, #0
	tst r0, r1
	beq _021D84EA
	add r0, r4, #0
	mov r2, #2
	add r0, #0x84
	str r2, [r0]
	add r0, r4, #0
	bl MOD85_021DBFB4
	add r0, r4, #0
	bl MOD85_021DBFDC
	cmp r0, #0
	bne _021D84D4
	mov r0, #0
	str r0, [r4, #0x70]
_021D84D4:
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021DC050
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021D9350
	ldr r0, _021D8510 ; =0x00000626
	bl FUN_020054C8
_021D84EA:
	ldr r0, [r4, #0x7c]
	cmp r0, #2
	bne _021D8508
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #2
	bne _021D8508
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #2
	bne _021D8508
	mov r0, #6
	str r0, [r4]
_021D8508:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D850C: .word 0x021C48B8
_021D8510: .word 0x00000626
	thumb_func_end MOD85_021D841C

	thumb_func_start MOD85_021D8514
MOD85_021D8514: ; 0x021D8514
	push {r4, lr}
	mov r1, #0
	add r4, r0, #0
	bl MOD85_021D9360
	cmp r0, #1
	beq _021D853A
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021D9360
	cmp r0, #1
	beq _021D853A
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021D9360
	cmp r0, #1
	bne _021D853E
_021D853A:
	mov r0, #0
	pop {r4, pc}
_021D853E:
	add r0, r4, #0
	bl MOD85_021DB754
	mov r0, #7
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD85_021D8514

	thumb_func_start MOD85_021D854C
MOD85_021D854C: ; 0x021D854C
	push {r4, lr}
	add r4, r0, #0
	add r2, r4, #0
	ldr r1, [r4, #0x74]
	add r2, #0x48
	bl MOD85_021DBED4
	str r0, [r4, #0x44]
	cmp r0, #6
	bne _021D8584
	ldr r1, [r4, #0x74]
	mov r0, #0xaa
	tst r0, r1
	beq _021D8570
	mov r0, #0x10
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D8570:
	cmp r1, #0
	beq _021D857C
	mov r0, #0xa
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D857C:
	mov r0, #8
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D8584:
	ldr r2, [r4, #0x74]
	mov r1, #0xaa
	tst r1, r2
	beq _021D859E
	mov r0, #2
	tst r0, r2
	beq _021D8596
	mov r0, #0x15
	b _021D8598
_021D8596:
	mov r0, #0x13
_021D8598:
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D859E:
	cmp r0, #2
	bne _021D85AA
	mov r0, #0xe
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D85AA:
	mov r0, #0xc
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D854C

	thumb_func_start MOD85_021D85B4
MOD85_021D85B4: ; 0x021D85B4
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DB754
	mov r0, #0
	str r0, [r4, #0x6c]
	mov r0, #9
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD85_021D85B4

	thumb_func_start MOD85_021D85C8
MOD85_021D85C8: ; 0x021D85C8
	mov r1, #1
	ldr r2, [r0, #0x6c]
	lsl r1, r1, #0xc
	add r2, r2, r1
	lsl r1, r1, #3
	str r2, [r0, #0x6c]
	cmp r2, r1
	blt _021D85DE
	mov r1, #0
	str r1, [r0, #0x6c]
	str r1, [r0]
_021D85DE:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021D85C8

	thumb_func_start MOD85_021D85E4
MOD85_021D85E4: ; 0x021D85E4
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DB754
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021DAEF4
	mov r0, #0xb
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021D85E4

	thumb_func_start MOD85_021D85FC
MOD85_021D85FC: ; 0x021D85FC
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DAF08
	cmp r0, #1
	bne _021D8618
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021DAEF4
	mov r0, #0
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D8618:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021D85FC

	thumb_func_start MOD85_021D861C
MOD85_021D861C: ; 0x021D861C
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DC0D8
	ldr r1, _021D8648 ; =0x00000458
	str r0, [r4, #0x64]
	ldr r2, [r4, r1]
	add r0, r2, r0
	str r0, [r4, r1]
	mov r0, #0
	str r0, [r4, #0x6c]
	mov r0, #0xd
	str r0, [r4]
	add r0, r4, #0
	bl MOD85_021DAD54
	add r0, r4, #0
	mov r1, #0xb
	bl MOD85_021DAEF4
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D8648: .word 0x00000458
	thumb_func_end MOD85_021D861C

	thumb_func_start MOD85_021D864C
MOD85_021D864C: ; 0x021D864C
	push {r4, lr}
	add r4, r0, #0
	mov r1, #1
	ldr r2, [r4, #0x6c]
	lsl r1, r1, #0xc
	add r2, r2, r1
	mov r1, #0x1e
	lsl r1, r1, #0xc
	str r2, [r4, #0x6c]
	cmp r2, r1
	bne _021D866A
	mov r1, #2
	bl MOD85_021DAEF4
	b _021D8690
_021D866A:
	ble _021D8690
	bl MOD85_021DAD68
	cmp r0, #1
	bne _021D8690
	add r0, r4, #0
	bl MOD85_021DAF08
	cmp r0, #1
	bne _021D8690
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021DAEF4
	mov r0, #0
	str r0, [r4, #0x6c]
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D8690:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021D864C

	thumb_func_start MOD85_021D8694
MOD85_021D8694: ; 0x021D8694
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	str r1, [r4, #0x64]
	str r1, [r4, #0x6c]
	mov r1, #0xf
	str r1, [r4]
	bl MOD85_021DAD54
	add r0, r4, #0
	mov r1, #0xb
	bl MOD85_021DAEF4
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D8694

	thumb_func_start MOD85_021D86B4
MOD85_021D86B4: ; 0x021D86B4
	push {r4, lr}
	add r4, r0, #0
	mov r1, #1
	ldr r2, [r4, #0x6c]
	lsl r1, r1, #0xc
	add r2, r2, r1
	mov r1, #0xf
	lsl r1, r1, #0xc
	str r2, [r4, #0x6c]
	cmp r2, r1
	bne _021D86D2
	mov r1, #2
	bl MOD85_021DAEF4
	b _021D86FA
_021D86D2:
	ble _021D86FA
	bl MOD85_021DAD68
	cmp r0, #1
	bne _021D86FA
	add r0, r4, #0
	bl MOD85_021DAF08
	cmp r0, #1
	bne _021D86FA
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021DAEF4
	mov r0, #0
	str r0, [r4, #0x6c]
	mov r0, #3
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D86FA:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D86B4

	thumb_func_start MOD85_021D8700
MOD85_021D8700: ; 0x021D8700
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DB754
	add r0, r4, #0
	bl MOD85_021DA96C
	add r0, r4, #0
	bl MOD85_021DAA2C
	add r0, r4, #0
	mov r1, #0xb
	bl MOD85_021DAEF4
	mov r0, #0
	str r0, [r4, #0x6c]
	mov r1, #0x11
	str r1, [r4]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D8700

	thumb_func_start MOD85_021D8728
MOD85_021D8728: ; 0x021D8728
	push {r4, lr}
	add r4, r0, #0
	mov r1, #1
	ldr r2, [r4, #0x6c]
	lsl r1, r1, #0xc
	add r2, r2, r1
	lsl r1, r1, #3
	str r2, [r4, #0x6c]
	cmp r2, r1
	blt _021D874E
	mov r1, #3
	bl MOD85_021DAEF4
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021D7FF4
	mov r0, #0x12
	str r0, [r4]
_021D874E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D8728

	thumb_func_start MOD85_021D8754
MOD85_021D8754: ; 0x021D8754
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DAF08
	cmp r0, #1
	bne _021D8768
	mov r0, #0x17
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D8768:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021D8754

	thumb_func_start MOD85_021D876C
MOD85_021D876C: ; 0x021D876C
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DC0D8
	str r0, [r4, #0x64]
	mov r0, #0
	str r0, [r4, #0x6c]
	mov r0, #0x14
	str r0, [r4]
	add r0, r4, #0
	bl MOD85_021DAD54
	add r0, r4, #0
	bl MOD85_021DA96C
	add r0, r4, #0
	bl MOD85_021DAA2C
	add r0, r4, #0
	mov r1, #0xb
	bl MOD85_021DAEF4
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021D876C

	thumb_func_start MOD85_021D879C
MOD85_021D879C: ; 0x021D879C
	push {r4, lr}
	add r4, r0, #0
	mov r1, #1
	ldr r2, [r4, #0x6c]
	lsl r1, r1, #0xc
	add r2, r2, r1
	mov r1, #0x1e
	lsl r1, r1, #0xc
	str r2, [r4, #0x6c]
	cmp r2, r1
	bne _021D87C2
	mov r1, #1
	bl MOD85_021D7FF4
	add r0, r4, #0
	mov r1, #3
	bl MOD85_021DAEF4
	b _021D87E2
_021D87C2:
	blt _021D87E2
	bl MOD85_021DAD68
	cmp r0, #1
	bne _021D87E2
	add r0, r4, #0
	bl MOD85_021DAF08
	cmp r0, #1
	bne _021D87E2
	mov r0, #0
	str r0, [r4, #0x6c]
	mov r0, #0x17
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D87E2:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D879C

	thumb_func_start MOD85_021D87E8
MOD85_021D87E8: ; 0x021D87E8
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	str r1, [r4, #0x6c]
	mov r1, #0x16
	str r1, [r4]
	bl MOD85_021DAD54
	add r0, r4, #0
	mov r1, #0xb
	bl MOD85_021DAEF4
	add r0, r4, #0
	bl MOD85_021DA96C
	add r0, r4, #0
	bl MOD85_021DAA2C
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021D87E8

	thumb_func_start MOD85_021D8810
MOD85_021D8810: ; 0x021D8810
	push {r4, lr}
	add r4, r0, #0
	mov r1, #1
	ldr r2, [r4, #0x6c]
	lsl r1, r1, #0xc
	add r3, r2, r1
	lsl r2, r1, #3
	str r3, [r4, #0x6c]
	cmp r3, r2
	bne _021D8834
	mov r1, #3
	bl MOD85_021DAEF4
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021D7FF4
	b _021D8858
_021D8834:
	lsl r1, r1, #3
	cmp r3, r1
	blt _021D8858
	bl MOD85_021DAD68
	cmp r0, #1
	bne _021D8858
	add r0, r4, #0
	bl MOD85_021DAF08
	cmp r0, #1
	bne _021D8858
	mov r0, #0
	str r0, [r4, #0x6c]
	mov r0, #0x18
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D8858:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021D8810

	thumb_func_start MOD85_021D885C
MOD85_021D885C: ; 0x021D885C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x50]
	cmp r0, #6
	blt _021D886A
	bl ErrorHandling
_021D886A:
	mov r0, #0x19
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D885C

	thumb_func_start MOD85_021D8874
MOD85_021D8874: ; 0x021D8874
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x50]
	cmp r0, #6
	blt _021D8882
	bl ErrorHandling
_021D8882:
	mov r0, #0x1c
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D8874

	thumb_func_start MOD85_021D888C
MOD85_021D888C: ; 0x021D888C
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	str r1, [r4, #0x64]
	str r1, [r4, #0x68]
	mov r2, #0x1a
	str r2, [r4]
	str r1, [r4, #0x74]
	bl MOD85_021DC094
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021DC094
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021DC094
	add r0, r4, #0
	bl MOD85_021DB754
	add r0, r4, #0
	bl MOD85_021DB95C
	add r0, r4, #0
	mov r1, #7
	bl MOD85_021DAEF4
	ldr r1, [r4, #0x60]
	cmp r1, #0
	bne _021D88D4
	mov r0, #0x3c
	str r0, [r4]
	mov r0, #0x3f
	str r0, [r4, #4]
	b _021D88F0
_021D88D4:
	cmp r1, #3
	bge _021D88E2
	mov r0, #0x3b
	str r0, [r4]
	mov r0, #0x3f
	str r0, [r4, #4]
	b _021D88F0
_021D88E2:
	ldr r0, _021D88F4 ; =0x0000C350
	cmp r1, r0
	blt _021D88F0
	mov r0, #0x3d
	str r0, [r4]
	mov r0, #0x1a
	str r0, [r4, #4]
_021D88F0:
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_021D88F4: .word 0x0000C350
	thumb_func_end MOD85_021D888C

	thumb_func_start MOD85_021D88F8
MOD85_021D88F8: ; 0x021D88F8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #8
	bl MOD85_021DBD54
	cmp r0, #0
	beq _021D8914
	mov r0, #0x3f
	str r0, [r4]
	add r0, r4, #0
	bl MOD85_021DB9A0
	mov r0, #0
	pop {r4, pc}
_021D8914:
	mov r0, #1
	lsl r0, r0, #0xa
	bl MOD85_021DBD54
	cmp r0, #0
	beq _021D8948
	ldr r0, [r4, #0x60]
	sub r0, r0, #3
	str r0, [r4, #0x60]
	ldr r0, _021D894C ; =0x0000045C
	ldr r1, [r4, r0]
	add r1, r1, #3
	str r1, [r4, r0]
	mov r0, #0x1b
	str r0, [r4]
	ldr r0, _021D8950 ; =0x000005ED
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD85_021DB9A0
	add r0, r4, #0
	bl MOD85_021DB76C
	mov r0, #0
	pop {r4, pc}
_021D8948:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D894C: .word 0x0000045C
_021D8950: .word 0x000005ED
	thumb_func_end MOD85_021D88F8

	thumb_func_start MOD85_021D8954
MOD85_021D8954: ; 0x021D8954
	push {r4, lr}
	add r4, r0, #0
	mov r0, #8
	bl MOD85_021DBD54
	cmp r0, #0
	beq _021D8970
	ldr r0, [r4, #0x60]
	add r0, r0, #3
	str r0, [r4, #0x60]
	mov r0, #0x3f
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
_021D8970:
	mov r0, #0x12
	lsl r0, r0, #6
	bl MOD85_021DBD54
	cmp r0, #0
	beq _021D8984
	mov r0, #0x1c
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D8984:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021D8954

	thumb_func_start MOD85_021D8988
MOD85_021D8988: ; 0x021D8988
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DAAF0
	mov r1, #0x46
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	add r0, r0, #1
	str r0, [r4, r1]
	add r0, r1, #0
	add r0, #8
	ldr r0, [r4, r0]
	add r1, #8
	add r0, r0, #1
	str r0, [r4, r1]
	mov r0, #0
	str r0, [r4, #0x70]
	ldr r1, [r4, #0x74]
	mov r0, #0x33
	tst r0, r1
	beq _021D89B6
	mov r0, #1
	str r0, [r4, #0x70]
_021D89B6:
	mov r0, #0
	str r0, [r4, #0x30]
	ldr r0, [r4, #0x74]
	cmp r0, #0
	beq _021D89C4
	mov r0, #1
	str r0, [r4, #0x30]
_021D89C4:
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021DC094
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021DC094
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021DC094
	add r0, r4, #0
	bl MOD85_021DB76C
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021D9338
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021D9338
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021D9338
	add r0, r4, #0
	bl MOD85_021DBFA4
	add r0, r4, #0
	mov r1, #9
	bl MOD85_021DAEF4
	mov r1, #1
	add r0, r4, #0
	str r1, [r4, #0x7c]
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x84
	str r1, [r0]
	mov r0, #0
	str r0, [r4, #0x6c]
	mov r0, #0x1d
	str r0, [r4]
	ldr r0, _021D8A2C ; =0x000005EE
	bl FUN_020054C8
	mov r0, #1
	pop {r4, pc}
	nop
_021D8A2C: .word 0x000005EE
	thumb_func_end MOD85_021D8988

	thumb_func_start MOD85_021D8A30
MOD85_021D8A30: ; 0x021D8A30
	mov r1, #1
	ldr r2, [r0, #0x6c]
	lsl r1, r1, #0xc
	add r2, r2, r1
	lsl r1, r1, #3
	str r2, [r0, #0x6c]
	cmp r2, r1
	blt _021D8A4C
	mov r1, #0
	str r1, [r0, #0x6c]
	mov r1, #0x1e
	str r1, [r0]
	mov r0, #1
	bx lr
_021D8A4C:
	mov r0, #0
	bx lr
	thumb_func_end MOD85_021D8A30

	thumb_func_start MOD85_021D8A50
MOD85_021D8A50: ; 0x021D8A50
	push {r4, lr}
	ldr r1, _021D8B40 ; =0x021C48B8
	add r4, r0, #0
	ldr r2, [r1, #0x48]
	ldr r1, [r4, #0x7c]
	cmp r1, #1
	bne _021D8A96
	mov r1, #2
	lsl r1, r1, #0xa
	add r3, r2, #0
	tst r3, r1
	beq _021D8A96
	mov r2, #2
	str r2, [r4, #0x7c]
	bl MOD85_021DBFB4
	add r0, r4, #0
	bl MOD85_021DBFDC
	cmp r0, #0
	bne _021D8A7E
	mov r0, #0
	str r0, [r4, #0x70]
_021D8A7E:
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021DC050
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021D9350
	ldr r0, _021D8B44 ; =0x00000626
	bl FUN_020054C8
	b _021D8B1E
_021D8A96:
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #1
	bne _021D8ADA
	mov r1, #2
	add r0, r2, #0
	tst r0, r1
	beq _021D8ADA
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	bl MOD85_021DBFB4
	add r0, r4, #0
	bl MOD85_021DBFDC
	cmp r0, #0
	bne _021D8AC2
	mov r0, #0
	str r0, [r4, #0x70]
_021D8AC2:
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021DC050
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021D9350
	ldr r0, _021D8B44 ; =0x00000626
	bl FUN_020054C8
	b _021D8B1E
_021D8ADA:
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #1
	bne _021D8B1E
	mov r1, #1
	add r0, r2, #0
	tst r0, r1
	beq _021D8B1E
	add r0, r4, #0
	mov r2, #2
	add r0, #0x84
	str r2, [r0]
	add r0, r4, #0
	bl MOD85_021DBFB4
	add r0, r4, #0
	bl MOD85_021DBFDC
	cmp r0, #0
	bne _021D8B08
	mov r0, #0
	str r0, [r4, #0x70]
_021D8B08:
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021DC050
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021D9350
	ldr r0, _021D8B44 ; =0x00000626
	bl FUN_020054C8
_021D8B1E:
	ldr r0, [r4, #0x7c]
	cmp r0, #2
	bne _021D8B3C
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #2
	bne _021D8B3C
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #2
	bne _021D8B3C
	mov r0, #0x1f
	str r0, [r4]
_021D8B3C:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D8B40: .word 0x021C48B8
_021D8B44: .word 0x00000626
	thumb_func_end MOD85_021D8A50

	thumb_func_start MOD85_021D8B48
MOD85_021D8B48: ; 0x021D8B48
	push {r4, lr}
	mov r1, #0
	add r4, r0, #0
	bl MOD85_021D9360
	cmp r0, #1
	beq _021D8B6E
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021D9360
	cmp r0, #1
	beq _021D8B6E
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021D9360
	cmp r0, #1
	bne _021D8B72
_021D8B6E:
	mov r0, #0
	pop {r4, pc}
_021D8B72:
	add r0, r4, #0
	bl MOD85_021DB754
	mov r0, #0x20
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD85_021D8B48

	thumb_func_start MOD85_021D8B80
MOD85_021D8B80: ; 0x021D8B80
	push {r4, lr}
	add r4, r0, #0
	add r2, r4, #0
	ldr r1, [r4, #0x74]
	add r2, #0x48
	bl MOD85_021DBED4
	str r0, [r4, #0x44]
	cmp r0, #6
	bne _021D8B9C
	mov r0, #0x21
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D8B9C:
	mov r1, #3
	ldr r2, [r4, #0x74]
	lsl r1, r1, #8
	tst r1, r2
	beq _021D8BAE
	mov r0, #0x27
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D8BAE:
	cmp r0, #2
	bne _021D8BBA
	mov r0, #0x25
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D8BBA:
	mov r0, #0x23
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D8B80

	thumb_func_start MOD85_021D8BC4
MOD85_021D8BC4: ; 0x021D8BC4
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DB754
	add r0, r4, #0
	mov r1, #7
	bl MOD85_021DAEF4
	mov r0, #0
	str r0, [r4, #0x6c]
	mov r0, #0x22
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD85_021D8BC4

	thumb_func_start MOD85_021D8BE0
MOD85_021D8BE0: ; 0x021D8BE0
	mov r1, #1
	ldr r2, [r0, #0x6c]
	lsl r1, r1, #0xc
	add r2, r2, r1
	lsl r1, r1, #3
	str r2, [r0, #0x6c]
	cmp r2, r1
	blt _021D8BFC
	mov r1, #0
	str r1, [r0, #0x6c]
	mov r1, #0x19
	str r1, [r0]
	mov r0, #1
	bx lr
_021D8BFC:
	mov r0, #0
	bx lr
	thumb_func_end MOD85_021D8BE0

	thumb_func_start MOD85_021D8C00
MOD85_021D8C00: ; 0x021D8C00
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DC0D8
	ldr r1, _021D8C2C ; =0x00000458
	str r0, [r4, #0x64]
	ldr r2, [r4, r1]
	add r0, r2, r0
	str r0, [r4, r1]
	mov r0, #0
	str r0, [r4, #0x6c]
	mov r0, #0x24
	str r0, [r4]
	add r0, r4, #0
	bl MOD85_021DAD54
	add r0, r4, #0
	mov r1, #0xa
	bl MOD85_021DAEF4
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D8C2C: .word 0x00000458
	thumb_func_end MOD85_021D8C00

	thumb_func_start MOD85_021D8C30
MOD85_021D8C30: ; 0x021D8C30
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DAD68
	cmp r0, #1
	bne _021D8C4C
	add r0, r4, #0
	mov r1, #7
	bl MOD85_021DAEF4
	mov r0, #0x19
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D8C4C:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021D8C30

	thumb_func_start MOD85_021D8C50
MOD85_021D8C50: ; 0x021D8C50
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	str r1, [r4, #0x64]
	str r1, [r4, #0x6c]
	mov r1, #0x26
	str r1, [r4]
	bl MOD85_021DAD54
	add r0, r4, #0
	mov r1, #0xa
	bl MOD85_021DAEF4
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D8C50

	thumb_func_start MOD85_021D8C70
MOD85_021D8C70: ; 0x021D8C70
	push {r4, lr}
	add r4, r0, #0
	mov r1, #1
	ldr r2, [r4, #0x6c]
	lsl r1, r1, #0xc
	add r2, r2, r1
	mov r1, #0xf
	lsl r1, r1, #0xc
	str r2, [r4, #0x6c]
	cmp r2, r1
	ble _021D8CA8
	bl MOD85_021DAD68
	cmp r0, #1
	bne _021D8CA8
	add r0, r4, #0
	mov r1, #7
	bl MOD85_021DAEF4
	add r0, r4, #0
	bl MOD85_021DB754
	mov r0, #0
	str r0, [r4, #0x6c]
	mov r0, #0x1c
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D8CA8:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021D8C70

	thumb_func_start MOD85_021D8CAC
MOD85_021D8CAC: ; 0x021D8CAC
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DC0D8
	ldr r1, _021D8CF0 ; =0x00000458
	str r0, [r4, #0x64]
	ldr r2, [r4, r1]
	add r0, r2, r0
	str r0, [r4, r1]
	mov r0, #0
	str r0, [r4, #0x6c]
	mov r0, #0x28
	str r0, [r4]
	add r0, r4, #0
	bl MOD85_021DAD54
	add r0, r4, #0
	mov r1, #0xa
	bl MOD85_021DAEF4
	add r0, r4, #0
	bl MOD85_021DBB0C
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021D7FF4
	add r0, r4, #0
	bl MOD85_021DE264
	ldr r1, _021D8CF4 ; =0x00000454
	str r0, [r4, r1]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D8CF0: .word 0x00000458
_021D8CF4: .word 0x00000454
	thumb_func_end MOD85_021D8CAC

	thumb_func_start MOD85_021D8CF8
MOD85_021D8CF8: ; 0x021D8CF8
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DAD68
	cmp r0, #1
	bne _021D8D1C
	ldr r0, _021D8D20 ; =0x00000454
	ldr r0, [r4, r0]
	bl FUN_02064520
	add r0, r4, #0
	mov r1, #7
	bl MOD85_021DAEF4
	mov r0, #0x29
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D8D1C:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D8D20: .word 0x00000454
	thumb_func_end MOD85_021D8CF8

	thumb_func_start MOD85_021D8D24
MOD85_021D8D24: ; 0x021D8D24
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DAF10
	mov r0, #0
	str r0, [r4, #0x1c]
	str r0, [r4, #0x14]
	mov r0, #1
	str r0, [r4, #8]
	mov r1, #0x2a
	str r1, [r4]
	pop {r4, pc}
	thumb_func_end MOD85_021D8D24

	thumb_func_start MOD85_021D8D3C
MOD85_021D8D3C: ; 0x021D8D3C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x1c]
	add r1, r0, #1
	ldr r0, _021D8D84 ; =0x000003E7
	str r1, [r4, #0x1c]
	cmp r1, r0
	bls _021D8D54
	str r0, [r4, #0x1c]
_021D8D54:
	ldr r1, [r4, #0x1c]
	add r0, r4, #0
	bl MOD85_021DE118
	mov r0, #0x10
	str r0, [r4, #0x10]
	mov r0, #1
	str r0, [r4, #8]
	mov r0, #0
	str r0, [r4, #0x24]
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	add r0, r4, #0
	bl MOD85_021DAC44
	cmp r0, #0
	bne _021D8D7A
	mov r0, #1
	str r0, [r4, #0x2c]
_021D8D7A:
	mov r0, #0x2b
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	nop
_021D8D84: .word 0x000003E7
	thumb_func_end MOD85_021D8D3C

	thumb_func_start MOD85_021D8D88
MOD85_021D8D88: ; 0x021D8D88
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	sub r0, r0, #1
	str r0, [r4, #0x10]
	cmp r0, #1
	bge _021D8D9A
	bl ErrorHandling
_021D8D9A:
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021DC094
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021DC094
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021DC094
	add r0, r4, #0
	bl MOD85_021DB754
	add r0, r4, #0
	bl MOD85_021DB95C
	add r0, r4, #0
	mov r1, #7
	bl MOD85_021DAEF4
	mov r2, #0x2c
	str r2, [r4]
	ldr r1, [r4, #0x60]
	cmp r1, #0
	bne _021D8DDA
	mov r0, #0x3c
	str r0, [r4]
	mov r0, #0x3f
	str r0, [r4, #4]
	b _021D8DF4
_021D8DDA:
	cmp r1, #1
	bge _021D8DE8
	mov r0, #0x3c
	str r0, [r4]
	mov r0, #0x3f
	str r0, [r4, #4]
	b _021D8DF4
_021D8DE8:
	ldr r0, _021D8DF8 ; =0x0000C350
	cmp r1, r0
	blt _021D8DF4
	mov r0, #0x3d
	str r0, [r4]
	str r2, [r4, #4]
_021D8DF4:
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_021D8DF8: .word 0x0000C350
	thumb_func_end MOD85_021D8D88

	thumb_func_start MOD85_021D8DFC
MOD85_021D8DFC: ; 0x021D8DFC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #8
	bl MOD85_021DBD54
	cmp r0, #0
	beq _021D8E12
	mov r0, #0x3f
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
_021D8E12:
	mov r0, #1
	lsl r0, r0, #0xa
	bl MOD85_021DBD54
	cmp r0, #0
	beq _021D8E58
	ldr r0, [r4, #0x60]
	sub r0, r0, #1
	str r0, [r4, #0x60]
	ldr r0, [r4, #0x14]
	sub r0, r0, #1
	str r0, [r4, #0x14]
	ldr r0, _021D8E5C ; =0x0000045C
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, #0x14]
	cmp r0, #0
	bge _021D8E3C
	mov r0, #0
	str r0, [r4, #0x14]
_021D8E3C:
	mov r0, #0x2d
	str r0, [r4]
	ldr r0, _021D8E60 ; =0x000005ED
	bl FUN_020054C8
	add r0, r4, #0
	bl MOD85_021DB9A0
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021DB714
	mov r0, #0
	pop {r4, pc}
_021D8E58:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D8E5C: .word 0x0000045C
_021D8E60: .word 0x000005ED
	thumb_func_end MOD85_021D8DFC

	thumb_func_start MOD85_021D8E64
MOD85_021D8E64: ; 0x021D8E64
	push {r4, lr}
	add r4, r0, #0
	mov r0, #8
	bl MOD85_021DBD54
	cmp r0, #0
	beq _021D8E80
	ldr r0, [r4, #0x60]
	add r0, r0, #1
	str r0, [r4, #0x60]
	mov r0, #0x3f
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
_021D8E80:
	mov r0, #0x12
	lsl r0, r0, #6
	bl MOD85_021DBD54
	cmp r0, #0
	beq _021D8E94
	mov r0, #0x2e
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D8E94:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021D8E64

	thumb_func_start MOD85_021D8E98
MOD85_021D8E98: ; 0x021D8E98
	push {r4, lr}
	mov r2, #0x46
	add r4, r0, #0
	lsl r2, r2, #4
	ldr r1, [r4, r2]
	add r1, r1, #1
	str r1, [r4, r2]
	add r1, r2, #0
	add r1, #0xc
	ldr r1, [r4, r1]
	add r2, #0xc
	add r1, r1, #1
	str r1, [r4, r2]
	mov r1, #1
	str r1, [r4, #0x74]
	str r1, [r4, #0x30]
	str r1, [r4, #0x70]
	mov r1, #0
	bl MOD85_021DC094
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021DC094
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021DC094
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021DB714
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021D9338
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021D9338
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021D9338
	add r0, r4, #0
	bl MOD85_021DBFA4
	add r0, r4, #0
	bl MOD85_021DAD0C
	mov r1, #1
	add r0, r4, #0
	str r1, [r4, #0x7c]
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x84
	str r1, [r0]
	mov r0, #0
	str r0, [r4, #0x6c]
	mov r0, #0x2f
	str r0, [r4]
	ldr r0, _021D8F80 ; =0x000005EE
	bl FUN_020054C8
	ldr r0, [r4, #0x24]
	cmp r0, #0
	bne _021D8F4C
	ldr r0, [r4, #0x28]
	cmp r0, #0
	bne _021D8F4C
	add r0, r4, #0
	bl MOD85_021DAC20
	cmp r0, #1
	bne _021D8F3E
	mov r0, #1
	str r0, [r4, #0x28]
	mov r0, #0x13
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
_021D8F3E:
	ldr r0, [r4, #0x28]
	cmp r0, #1
	bne _021D8F4C
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021DBB54
_021D8F4C:
	ldr r0, [r4, #0x24]
	cmp r0, #0
	bne _021D8F7C
	ldr r0, [r4, #0x28]
	cmp r0, #0
	bne _021D8F7C
	add r0, r4, #0
	bl MOD85_021DABFC
	cmp r0, #1
	bne _021D8F6E
	mov r0, #1
	str r0, [r4, #0x24]
	ldr r0, _021D8F84 ; =0x000004BC
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
_021D8F6E:
	ldr r0, [r4, #0x24]
	cmp r0, #1
	bne _021D8F7C
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021DBB54
_021D8F7C:
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_021D8F80: .word 0x000005EE
_021D8F84: .word 0x000004BC
	thumb_func_end MOD85_021D8E98

	thumb_func_start MOD85_021D8F88
MOD85_021D8F88: ; 0x021D8F88
	push {r3, lr}
	mov r1, #1
	ldr r2, [r0, #0x6c]
	lsl r1, r1, #0xc
	add r2, r2, r1
	lsl r1, r1, #3
	str r2, [r0, #0x6c]
	cmp r2, r1
	blt _021D8FAC
	mov r1, #0
	str r1, [r0, #0x6c]
	mov r1, #0x30
	str r1, [r0]
	mov r1, #6
	bl MOD85_021DAEF4
	mov r0, #1
	pop {r3, pc}
_021D8FAC:
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD85_021D8F88

	thumb_func_start MOD85_021D8FB0
MOD85_021D8FB0: ; 0x021D8FB0
	push {r4, lr}
	ldr r1, _021D90A8 ; =0x021C48B8
	add r4, r0, #0
	ldr r2, [r1, #0x48]
	ldr r1, [r4, #0x7c]
	cmp r1, #1
	bne _021D8FF8
	mov r1, #2
	lsl r1, r1, #0xa
	add r3, r2, #0
	tst r3, r1
	beq _021D8FF8
	mov r2, #2
	str r2, [r4, #0x7c]
	bl MOD85_021DBFB4
	add r0, r4, #0
	bl MOD85_021DC01C
	cmp r0, #0
	bne _021D8FE0
	mov r0, #0
	str r0, [r4, #0x70]
	str r0, [r4, #0x30]
_021D8FE0:
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021DC050
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021D9350
	ldr r0, _021D90AC ; =0x000005F5
	bl FUN_020054C8
	b _021D9084
_021D8FF8:
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #1
	bne _021D903E
	mov r1, #2
	add r0, r2, #0
	tst r0, r1
	beq _021D903E
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	bl MOD85_021DBFB4
	add r0, r4, #0
	bl MOD85_021DC01C
	cmp r0, #0
	bne _021D9026
	mov r0, #0
	str r0, [r4, #0x70]
	str r0, [r4, #0x30]
_021D9026:
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021DC050
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021D9350
	ldr r0, _021D90AC ; =0x000005F5
	bl FUN_020054C8
	b _021D9084
_021D903E:
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #1
	bne _021D9084
	mov r1, #1
	add r0, r2, #0
	tst r0, r1
	beq _021D9084
	add r0, r4, #0
	mov r2, #2
	add r0, #0x84
	str r2, [r0]
	add r0, r4, #0
	bl MOD85_021DBFB4
	add r0, r4, #0
	bl MOD85_021DC01C
	cmp r0, #0
	bne _021D906E
	mov r0, #0
	str r0, [r4, #0x70]
	str r0, [r4, #0x30]
_021D906E:
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021DC050
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021D9350
	ldr r0, _021D90AC ; =0x000005F5
	bl FUN_020054C8
_021D9084:
	ldr r0, [r4, #0x7c]
	cmp r0, #2
	bne _021D90A2
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #2
	bne _021D90A2
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #2
	bne _021D90A2
	mov r0, #0x31
	str r0, [r4]
_021D90A2:
	mov r0, #0
	pop {r4, pc}
	nop
_021D90A8: .word 0x021C48B8
_021D90AC: .word 0x000005F5
	thumb_func_end MOD85_021D8FB0

	thumb_func_start MOD85_021D90B0
MOD85_021D90B0: ; 0x021D90B0
	push {r4, lr}
	mov r1, #0
	add r4, r0, #0
	bl MOD85_021D9360
	cmp r0, #1
	beq _021D90D6
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021D9360
	cmp r0, #1
	beq _021D90D6
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021D9360
	cmp r0, #1
	bne _021D90DA
_021D90D6:
	mov r0, #0
	pop {r4, pc}
_021D90DA:
	add r0, r4, #0
	bl MOD85_021DB754
	mov r0, #0x32
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD85_021D90B0

	thumb_func_start MOD85_021D90E8
MOD85_021D90E8: ; 0x021D90E8
	push {r4, lr}
	add r4, r0, #0
	add r2, r4, #0
	ldr r1, [r4, #0x74]
	add r2, #0x48
	bl MOD85_021DBF48
	str r0, [r4, #0x44]
	cmp r0, #6
	ldr r0, [r4, #0x28]
	bne _021D910E
	cmp r0, #1
	bne _021D9106
	mov r0, #3
	str r0, [r4, #0x28]
_021D9106:
	mov r0, #0x33
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
_021D910E:
	cmp r0, #1
	bne _021D9116
	mov r0, #2
	str r0, [r4, #0x28]
_021D9116:
	mov r0, #0x34
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D90E8

	thumb_func_start MOD85_021D9120
MOD85_021D9120: ; 0x021D9120
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DB754
	add r0, r4, #0
	mov r1, #7
	bl MOD85_021DAEF4
	ldr r0, [r4, #0x10]
	cmp r0, #1
	bgt _021D913A
	mov r0, #0x36
	b _021D913C
_021D913A:
	mov r0, #0x2b
_021D913C:
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D9120

	thumb_func_start MOD85_021D9144
MOD85_021D9144: ; 0x021D9144
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x44]
	lsl r2, r1, #2
	ldr r1, _021D9170 ; =0x021DFC4C
	ldr r3, [r1, r2]
	ldr r1, _021D9174 ; =0x00000458
	str r3, [r4, #0x64]
	ldr r2, [r4, r1]
	add r2, r2, r3
	str r2, [r4, r1]
	bl MOD85_021DAD54
	add r0, r4, #0
	mov r1, #0xa
	bl MOD85_021DAEF4
	mov r0, #0
	str r0, [r4, #0x6c]
	mov r1, #0x35
	str r1, [r4]
	pop {r4, pc}
	.align 2, 0
_021D9170: .word MOD85_021DFC4C
_021D9174: .word 0x00000458
	thumb_func_end MOD85_021D9144

	thumb_func_start MOD85_021D9178
MOD85_021D9178: ; 0x021D9178
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DAD68
	cmp r0, #0
	bne _021D9188
	mov r0, #0
	pop {r4, pc}
_021D9188:
	add r0, r4, #0
	mov r1, #7
	bl MOD85_021DAEF4
	ldr r0, [r4, #0x10]
	cmp r0, #1
	bgt _021D919A
	mov r0, #0x36
	b _021D919C
_021D919A:
	mov r0, #0x2b
_021D919C:
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D9178

	thumb_func_start MOD85_021D91A4
MOD85_021D91A4: ; 0x021D91A4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	sub r0, r0, #1
	str r0, [r4, #0x10]
	beq _021D91B4
	bl ErrorHandling
_021D91B4:
	ldr r0, [r4, #0x2c]
	cmp r0, #1
	bne _021D91D0
	ldr r0, [r4, #0x24]
	cmp r0, #0
	bne _021D91D0
	add r0, r4, #0
	mov r1, #8
	bl MOD85_021DAEF4
	mov r0, #0x3a
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
_021D91D0:
	mov r0, #0x37
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD85_021D91A4

	thumb_func_start MOD85_021D91D8
MOD85_021D91D8: ; 0x021D91D8
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DAC58
	add r0, r4, #0
	bl MOD85_021DACAC
	ldr r1, [r4, #0x24]
	cmp r1, #1
	bne _021D91EE
	mov r0, #2
_021D91EE:
	cmp r0, #2
	bne _021D9202
	add r0, r4, #0
	mov r1, #5
	bl MOD85_021DAEF4
	mov r0, #0x38
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
_021D9202:
	cmp r0, #1
	bne _021D9216
	add r0, r4, #0
	mov r1, #0xc
	bl MOD85_021DAEF4
	mov r0, #0x39
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
_021D9216:
	mov r0, #0x23
	bl FUN_02005578
	mov r0, #0x2a
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021D91D8

	thumb_func_start MOD85_021D9224
MOD85_021D9224: ; 0x021D9224
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DAF08
	cmp r0, #0
	bne _021D9234
	mov r0, #0
	pop {r4, pc}
_021D9234:
	mov r0, #0x2a
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD85_021D9224

	thumb_func_start MOD85_021D923C
MOD85_021D923C: ; 0x021D923C
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DAF08
	cmp r0, #0
	bne _021D924C
	mov r0, #0
	pop {r4, pc}
_021D924C:
	mov r0, #0x2a
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD85_021D923C

	thumb_func_start MOD85_021D9254
MOD85_021D9254: ; 0x021D9254
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DAF08
	cmp r0, #0
	bne _021D9264
	mov r0, #0
	pop {r4, pc}
_021D9264:
	ldr r1, [r4, #0x1c]
	ldr r0, [r4, #0x20]
	cmp r1, r0
	bls _021D926E
	str r1, [r4, #0x20]
_021D926E:
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021D7FF4
	add r0, r4, #0
	bl MOD85_021DBB30
	mov r0, #0
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD85_021D9254

	thumb_func_start MOD85_021D9284
MOD85_021D9284: ; 0x021D9284
	push {r4, lr}
	mov r1, #0
	add r4, r0, #0
	bl MOD85_021D7BEC
	mov r0, #0x3e
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D9284

	thumb_func_start MOD85_021D9298
MOD85_021D9298: ; 0x021D9298
	push {r4, lr}
	mov r1, #2
	add r4, r0, #0
	bl MOD85_021D7BEC
	mov r0, #0x3e
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D9298

	thumb_func_start MOD85_021D92AC
MOD85_021D92AC: ; 0x021D92AC
	push {r4, lr}
	mov r1, #1
	add r4, r0, #0
	bl MOD85_021D7BEC
	mov r0, #0x3e
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021D92AC

	thumb_func_start MOD85_021D92C0
MOD85_021D92C0: ; 0x021D92C0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #3
	bl MOD85_021DBD54
	cmp r0, #0
	beq _021D92D8
	add r0, r4, #0
	bl MOD85_021D7C44
	ldr r0, [r4, #4]
	str r0, [r4]
_021D92D8:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021D92C0

	thumb_func_start MOD85_021D92DC
MOD85_021D92DC: ; 0x021D92DC
	push {r3, lr}
	bl MOD85_021DB9A0
	mov r0, #2
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD85_021D92DC

	thumb_func_start MOD85_021D92E8
MOD85_021D92E8: ; 0x021D92E8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r7, #0
	add r5, #0xb4
	mov r4, #0
	add r6, r5, #0
_021D92F4:
	mov r0, #0
	str r0, [r5]
	add r2, r4, #0
	str r4, [r5, #0x10]
	ldr r0, _021D9318 ; =MOD85_021D936C
	add r1, r6, #0
	add r2, #0x81
	str r7, [r5, #0x20]
	bl FUN_0200CA44
	str r0, [r5, #0x1c]
	add r4, r4, #1
	add r5, #0x24
	add r6, #0x24
	cmp r4, #3
	blo _021D92F4
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9318: .word MOD85_021D936C
	thumb_func_end MOD85_021D92E8

	thumb_func_start MOD85_021D931C
MOD85_021D931C: ; 0x021D931C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_021D9322:
	add r0, r5, #0
	add r0, #0xd0
	ldr r0, [r0]
	bl FUN_0200CAB4
	add r4, r4, #1
	add r5, #0x24
	cmp r4, #3
	blo _021D9322
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021D931C

	thumb_func_start MOD85_021D9338
MOD85_021D9338: ; 0x021D9338
	mov r2, #0x24
	add r3, r1, #0
	mul r3, r2
	add r1, r0, r3
	add r0, r0, r3
	mov r2, #1
	add r1, #0xb4
	str r2, [r1]
	add r0, #0xb8
	str r2, [r0]
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021D9338

	thumb_func_start MOD85_021D9350
MOD85_021D9350: ; 0x021D9350
	mov r2, #0x24
	mul r2, r1
	add r0, r0, r2
	mov r3, #2
	add r0, #0xb4
	str r3, [r0]
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021D9350

	thumb_func_start MOD85_021D9360
MOD85_021D9360: ; 0x021D9360
	mov r2, #0x24
	mul r2, r1
	add r0, r0, r2
	add r0, #0xb8
	ldr r0, [r0]
	bx lr
	thumb_func_end MOD85_021D9360

	thumb_func_start MOD85_021D936C
MOD85_021D936C: ; 0x021D936C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldr r4, [r5, #0x20]
	ldr r6, _021D9388 ; =0x021DEE20
_021D9374:
	ldr r2, [r5]
	add r0, r5, #0
	lsl r2, r2, #2
	ldr r2, [r6, r2]
	add r1, r4, #0
	blx r2
	cmp r0, #1
	beq _021D9374
	pop {r4, r5, r6, pc}
	nop
_021D9388: .word MOD85_021DEE20
	thumb_func_end MOD85_021D936C

	thumb_func_start MOD85_021D938C
MOD85_021D938C: ; 0x021D938C
	mov r0, #0
	bx lr
	thumb_func_end MOD85_021D938C

	thumb_func_start MOD85_021D9390
MOD85_021D9390: ; 0x021D9390
	push {r3, lr}
	add r2, r0, #0
	add r0, r1, #0
	ldr r1, [r2, #0x10]
	add r2, r0, #0
	add r2, #0x8c
	ldr r2, [r2]
	bl MOD85_021DA744
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD85_021D9390

	thumb_func_start MOD85_021D93A8
MOD85_021D93A8: ; 0x021D93A8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r2, [r5]
	add r4, r1, #0
	add r2, r2, #1
	str r2, [r5]
	mov r2, #0
	str r2, [r5, #0x14]
	str r2, [r5, #0x18]
	ldr r2, [r4, #0x30]
	cmp r2, #1
	ldr r2, [r4, #8]
	bne _021D93F2
	cmp r2, #0
	bne _021D93DC
	bl MOD85_021D94E4
	cmp r0, #0
	bne _021D9400
	add r0, r5, #0
	add r1, r4, #0
	bl MOD85_021D9EDC
	mov r0, #0
	str r0, [r4, #0x30]
	b _021D9400
_021D93DC:
	bl MOD85_021D951C
	cmp r0, #0
	bne _021D9400
	add r0, r5, #0
	add r1, r4, #0
	bl MOD85_021D9F8C
	mov r0, #0
	str r0, [r4, #0x30]
	b _021D9400
_021D93F2:
	cmp r2, #0
	bne _021D93FC
	bl MOD85_021D9EDC
	b _021D9400
_021D93FC:
	bl MOD85_021D9F8C
_021D9400:
	mov r0, #1
	pop {r3, r4, r5, pc}
	thumb_func_end MOD85_021D93A8

	thumb_func_start MOD85_021D9404
MOD85_021D9404: ; 0x021D9404
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r3, r1, #0
	ldr r1, [r5, #0x10]
	add r7, r3, #0
	lsl r0, r1, #2
	add r7, #0x90
	str r0, [sp]
	ldr r0, [r7, r0]
	mov r4, #0
	lsr r6, r0, #0x1f
	lsl r2, r0, #0xf
	sub r2, r2, r6
	mov r0, #0xf
	ror r2, r0
	add r0, r6, r2
	beq _021D943E
	add r2, r3, #0
	add r2, #0x8c
	ldr r2, [r2]
	mov r4, #1
	cmp r0, r2
	bge _021D9436
	add r2, r0, #0
_021D9436:
	add r0, r3, #0
	bl MOD85_021DA780
	b _021D9464
_021D943E:
	ldr r2, [r5, #0x18]
	cmp r2, #0
	beq _021D9464
	sub r0, r2, #1
	str r0, [r5, #0x18]
	add r0, r3, #0
	add r3, #0x8c
	ldr r2, [r3]
	mov r4, #1
	bl MOD85_021DA744
	ldr r0, [sp]
	ldr r0, [r7, r0]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0xf
	sub r1, r1, r2
	mov r0, #0xf
	ror r1, r0
	add r0, r2, r1
_021D9464:
	cmp r0, #0
	bne _021D94A0
	ldr r6, [r5, #0x18]
	cmp r6, #0
	bne _021D94A0
	ldr r3, _021D94A8 ; =0x021DEE34
	add r2, sp, #4
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	cmp r6, #4
	str r0, [r2]
	ble _021D9484
	mov r6, #4
_021D9484:
	lsl r1, r6, #2
	add r0, sp, #4
	ldr r0, [r0, r1]
	str r0, [r5, #8]
	mov r0, #0
	str r0, [r5, #0xc]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	cmp r4, #0
	bne _021D94A0
	add sp, #0x18
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D94A0:
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D94A8: .word MOD85_021DEE34
	thumb_func_end MOD85_021D9404

	thumb_func_start MOD85_021D94AC
MOD85_021D94AC: ; 0x021D94AC
	push {r3, r4}
	ldr r2, [r0, #0x10]
	ldr r3, [r0, #8]
	add r1, #0x9c
	lsl r2, r2, #2
	str r3, [r1, r2]
	ldr r3, [r0, #8]
	neg r3, r3
	str r3, [r0, #8]
	ldr r3, [r0, #0xc]
	add r4, r3, #1
	mov r3, #1
	str r4, [r0, #0xc]
	tst r3, r4
	bne _021D94D0
	ldr r3, [r0, #8]
	asr r3, r3, #2
	str r3, [r0, #8]
_021D94D0:
	ldr r3, [r0, #8]
	cmp r3, #0
	bne _021D94DE
	mov r3, #0
	str r3, [r0]
	str r3, [r0, #4]
	str r3, [r1, r2]
_021D94DE:
	mov r0, #0
	pop {r3, r4}
	bx lr
	thumb_func_end MOD85_021D94AC

	thumb_func_start MOD85_021D94E4
MOD85_021D94E4: ; 0x021D94E4
	push {r3, lr}
	ldr r2, [r1, #0x74]
	cmp r2, #0
	bne _021D94F0
	mov r0, #0
	pop {r3, pc}
_021D94F0:
	ldr r2, [r0, #0x10]
	cmp r2, #0
	beq _021D9500
	cmp r2, #1
	beq _021D9506
	cmp r2, #2
	beq _021D950C
	b _021D9512
_021D9500:
	bl MOD85_021D953C
	pop {r3, pc}
_021D9506:
	bl MOD85_021D9578
	pop {r3, pc}
_021D950C:
	bl MOD85_021D95B4
	pop {r3, pc}
_021D9512:
	bl ErrorHandling
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD85_021D94E4

	thumb_func_start MOD85_021D951C
MOD85_021D951C: ; 0x021D951C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x74]
	cmp r0, #0
	bne _021D952C
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D952C:
	bl MOD85_021DBD74
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD85_021D9E94
	pop {r3, r4, r5, pc}
	thumb_func_end MOD85_021D951C

	thumb_func_start MOD85_021D953C
MOD85_021D953C: ; 0x021D953C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x74]
	bl MOD85_021DBD74
	add r6, r0, #0
	cmp r6, #6
	bne _021D9552
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D9552:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD85_021DA058
	cmp r0, #1
	bne _021D956A
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD85_021D95F0
	pop {r4, r5, r6, pc}
_021D956A:
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD85_021D9708
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD85_021D953C

	thumb_func_start MOD85_021D9578
MOD85_021D9578: ; 0x021D9578
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x74]
	bl MOD85_021DBD74
	add r6, r0, #0
	cmp r6, #6
	bne _021D958E
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D958E:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD85_021DA058
	cmp r0, #1
	bne _021D95A6
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD85_021D9A48
	pop {r4, r5, r6, pc}
_021D95A6:
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD85_021D9AF0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD85_021D9578

	thumb_func_start MOD85_021D95B4
MOD85_021D95B4: ; 0x021D95B4
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x74]
	bl MOD85_021DBD74
	add r6, r0, #0
	cmp r6, #6
	bne _021D95CA
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D95CA:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD85_021DA058
	cmp r0, #1
	bne _021D95E2
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD85_021D9A48
	pop {r4, r5, r6, pc}
_021D95E2:
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD85_021D9AF0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD85_021D95B4

	thumb_func_start MOD85_021D95F0
MOD85_021D95F0: ; 0x021D95F0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r0, [sp]
	ldr r0, [r0, #0x10]
	add r4, r1, #0
	add r6, r2, #0
	str r0, [sp, #8]
	mov r7, #1
_021D9600:
	ldr r1, [sp, #8]
	add r0, r4, #0
	add r2, r7, #0
	bl MOD85_021DBD30
	cmp r6, r0
	bne _021D9638
	mov r5, #0
	cmp r7, #3
	bgt _021D9638
_021D9614:
	add r0, r4, #0
	add r1, r5, #0
	add r2, r6, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D9630
	ldr r0, [sp]
	add r1, r7, r5
	str r1, [r0, #0x14]
	str r5, [r0, #0x18]
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021D9630:
	add r5, r5, #1
	add r0, r7, r5
	cmp r0, #3
	ble _021D9614
_021D9638:
	add r7, r7, #1
	cmp r7, #3
	ble _021D9600
	mov r0, #4
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x70]
	cmp r0, #1
	bne _021D964C
	mov r0, #0x15
	str r0, [sp, #0x10]
_021D964C:
	add r0, r4, #0
	add r0, #0xa8
	ldr r0, [r0]
	mov r7, #1
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	cmp r0, #1
	blt _021D9700
_021D965C:
	mov r2, #1
	ldr r1, [sp, #8]
	add r0, r4, #0
	sub r2, r2, r7
	bl MOD85_021DBD30
	cmp r6, r0
	bne _021D96F8
	mov r5, #0
_021D966E:
	add r0, r7, r5
	str r0, [sp, #4]
	ldr r1, [sp, #4]
	add r0, r4, #0
	add r2, r6, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D96F2
	cmp r5, #0
	bne _021D96B4
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0xc]
	lsr r0, r0, #0x1f
	lsl r2, r1, #0x1e
	sub r2, r2, r0
	mov r1, #0x1e
	ror r2, r1
	add r0, r0, r2
	bne _021D96E2
	add r0, r4, #0
	add r1, r7, #2
	add r2, r6, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D96E2
	ldr r0, [sp]
	mov r1, #3
	str r1, [r0, #0x14]
	add r1, r7, #2
	str r1, [r0, #0x18]
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021D96B4:
	cmp r5, #1
	bne _021D96E2
	ldr r0, [sp, #0xc]
	mov r1, #6
	bl _s32_div_f
	cmp r1, #2
	bge _021D96E2
	add r0, r4, #0
	add r1, r7, #2
	add r2, r6, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D96E2
	ldr r0, [sp]
	mov r1, #3
	str r1, [r0, #0x14]
	add r1, r7, #2
	str r1, [r0, #0x18]
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021D96E2:
	ldr r0, [sp]
	add r1, r5, #1
	str r1, [r0, #0x14]
	ldr r1, [sp, #4]
	add sp, #0x14
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021D96F2:
	add r5, r5, #1
	cmp r5, #3
	blt _021D966E
_021D96F8:
	ldr r0, [sp, #0x10]
	add r7, r7, #1
	cmp r7, r0
	ble _021D965C
_021D9700:
	mov r0, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021D95F0

	thumb_func_start MOD85_021D9708
MOD85_021D9708: ; 0x021D9708
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r4, r2, #0
	add r2, r0, #0
	ldr r7, [r2, #0x10]
	add r2, sp, #0xc
	str r2, [sp]
	add r2, sp, #0x14
	add r3, sp, #0x10
	str r0, [sp, #4]
	add r5, r1, #0
	bl MOD85_021DA0A8
	cmp r0, #0
	bne _021D972C
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D972C:
	add r0, r5, #0
	mov r1, #0
	add r2, r4, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D979C
	ldr r2, [sp, #0x14]
	add r0, r5, #0
	add r1, r7, #0
	bl MOD85_021DBD30
	cmp r4, r0
	bne _021D9758
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #4]
	add sp, #0x18
	str r1, [r0, #0x14]
	mov r1, #0
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9758:
	ldr r2, [sp, #0x10]
	cmp r2, #0
	beq _021D977A
	add r0, r5, #0
	add r1, r7, #0
	bl MOD85_021DBD30
	cmp r4, r0
	bne _021D977A
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #4]
	add sp, #0x18
	str r1, [r0, #0x14]
	mov r1, #0
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D977A:
	ldr r2, [sp, #0xc]
	cmp r2, #0
	beq _021D979C
	add r0, r5, #0
	add r1, r7, #0
	bl MOD85_021DBD30
	cmp r4, r0
	bne _021D979C
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #4]
	add sp, #0x18
	str r1, [r0, #0x14]
	mov r1, #0
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D979C:
	mov r0, #4
	str r0, [sp, #8]
	ldr r0, [r5, #0x70]
	cmp r0, #1
	bne _021D97AA
	mov r0, #0x15
	str r0, [sp, #8]
_021D97AA:
	ldr r0, [sp, #0x10]
	cmp r0, #0
	bne _021D97F2
	ldr r0, [sp, #8]
	mov r6, #1
	cmp r0, #1
	blt _021D97EC
_021D97B8:
	ldr r2, [sp, #0x14]
	add r0, r5, #0
	add r1, r7, #0
	sub r2, r2, r6
	bl MOD85_021DBD30
	cmp r4, r0
	bne _021D97E4
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D97E4
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #4]
	add sp, #0x18
	str r1, [r0, #0x14]
	str r6, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D97E4:
	ldr r0, [sp, #8]
	add r6, r6, #1
	cmp r6, r0
	ble _021D97B8
_021D97EC:
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D97F2:
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bne _021D98C4
	ldr r0, [sp, #8]
	mov r6, #1
	cmp r0, #1
	blt _021D98BE
_021D9800:
	mov r0, #1
	tst r0, r6
	beq _021D985E
	ldr r2, [sp, #0x14]
	add r0, r5, #0
	add r1, r7, #0
	sub r2, r2, r6
	bl MOD85_021DBD30
	cmp r4, r0
	bne _021D9832
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D9832
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #4]
	add sp, #0x18
	str r1, [r0, #0x14]
	str r6, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9832:
	ldr r2, [sp, #0x10]
	add r0, r5, #0
	add r1, r7, #0
	sub r2, r2, r6
	bl MOD85_021DBD30
	cmp r4, r0
	bne _021D98B6
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D98B6
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #4]
	add sp, #0x18
	str r1, [r0, #0x14]
	str r6, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D985E:
	ldr r2, [sp, #0x10]
	add r0, r5, #0
	add r1, r7, #0
	sub r2, r2, r6
	bl MOD85_021DBD30
	cmp r4, r0
	bne _021D988A
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D988A
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #4]
	add sp, #0x18
	str r1, [r0, #0x14]
	str r6, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D988A:
	ldr r2, [sp, #0x14]
	add r0, r5, #0
	add r1, r7, #0
	sub r2, r2, r6
	bl MOD85_021DBD30
	cmp r4, r0
	bne _021D98B6
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D98B6
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #4]
	add sp, #0x18
	str r1, [r0, #0x14]
	str r6, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D98B6:
	ldr r0, [sp, #8]
	add r6, r6, #1
	cmp r6, r0
	ble _021D9800
_021D98BE:
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D98C4:
	ldr r0, [sp, #8]
	mov r6, #1
	cmp r0, #1
	bge _021D98CE
	b _021D9A42
_021D98CE:
	mov r0, #3
	and r0, r6
	bne _021D9958
	ldr r2, [sp, #0x14]
	add r0, r5, #0
	add r1, r7, #0
	sub r2, r2, r6
	bl MOD85_021DBD30
	cmp r4, r0
	bne _021D9900
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D9900
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #4]
	add sp, #0x18
	str r1, [r0, #0x14]
	str r6, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9900:
	ldr r2, [sp, #0x10]
	add r0, r5, #0
	add r1, r7, #0
	sub r2, r2, r6
	bl MOD85_021DBD30
	cmp r4, r0
	bne _021D992C
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D992C
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #4]
	add sp, #0x18
	str r1, [r0, #0x14]
	str r6, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D992C:
	ldr r2, [sp, #0xc]
	add r0, r5, #0
	add r1, r7, #0
	sub r2, r2, r6
	bl MOD85_021DBD30
	cmp r4, r0
	bne _021D9A38
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D9A38
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #4]
	add sp, #0x18
	str r1, [r0, #0x14]
	str r6, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9958:
	cmp r0, #1
	bne _021D99B4
	ldr r2, [sp, #0x10]
	add r0, r5, #0
	add r1, r7, #0
	sub r2, r2, r6
	bl MOD85_021DBD30
	cmp r4, r0
	bne _021D9988
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D9988
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #4]
	add sp, #0x18
	str r1, [r0, #0x14]
	str r6, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9988:
	ldr r2, [sp, #0x14]
	add r0, r5, #0
	add r1, r7, #0
	sub r2, r2, r6
	bl MOD85_021DBD30
	cmp r4, r0
	bne _021D9A38
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D9A38
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #4]
	add sp, #0x18
	str r1, [r0, #0x14]
	str r6, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D99B4:
	ldr r2, [sp, #0xc]
	add r0, r5, #0
	add r1, r7, #0
	sub r2, r2, r6
	bl MOD85_021DBD30
	cmp r4, r0
	bne _021D99E0
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D99E0
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #4]
	add sp, #0x18
	str r1, [r0, #0x14]
	str r6, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D99E0:
	ldr r2, [sp, #0x14]
	add r0, r5, #0
	add r1, r7, #0
	sub r2, r2, r6
	bl MOD85_021DBD30
	cmp r4, r0
	bne _021D9A0C
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D9A0C
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #4]
	add sp, #0x18
	str r1, [r0, #0x14]
	str r6, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9A0C:
	ldr r2, [sp, #0x10]
	add r0, r5, #0
	add r1, r7, #0
	sub r2, r2, r6
	bl MOD85_021DBD30
	cmp r4, r0
	bne _021D9A38
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD85_021DA290
	cmp r0, #1
	bne _021D9A38
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #4]
	add sp, #0x18
	str r1, [r0, #0x14]
	str r6, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9A38:
	ldr r0, [sp, #8]
	add r6, r6, #1
	cmp r6, r0
	bgt _021D9A42
	b _021D98CE
_021D9A42:
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD85_021D9708

	thumb_func_start MOD85_021D9A48
MOD85_021D9A48: ; 0x021D9A48
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	ldr r7, [r0, #0x10]
	str r0, [sp]
	add r4, r1, #0
	add r6, r2, #0
	mov r5, #1
_021D9A56:
	add r0, r4, #0
	add r1, r7, #0
	add r2, r5, #0
	bl MOD85_021DBD30
	cmp r6, r0
	bne _021D9A72
	ldr r0, [sp]
	mov r1, #0
	str r5, [r0, #0x14]
	str r1, [r0, #0x18]
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9A72:
	add r5, r5, #1
	cmp r5, #3
	ble _021D9A56
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r4, #0x70]
	cmp r0, #1
	bne _021D9A86
	mov r0, #0x15
	str r0, [sp, #4]
_021D9A86:
	ldr r0, [sp, #4]
	mov r5, #1
	cmp r0, #1
	blt _021D9AE8
_021D9A8E:
	mov r2, #1
	add r0, r4, #0
	add r1, r7, #0
	sub r2, r2, r5
	bl MOD85_021DBD30
	cmp r6, r0
	bne _021D9AE0
	lsr r2, r5, #0x1f
	lsl r1, r5, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	cmp r0, #1
	bne _021D9ABE
	ldr r0, [sp]
	mov r1, #3
	str r1, [r0, #0x14]
	add r1, r5, #2
	str r1, [r0, #0x18]
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9ABE:
	sub r0, r0, #2
	cmp r0, #1
	bhi _021D9AD4
	ldr r0, [sp]
	mov r1, #2
	str r1, [r0, #0x14]
	add r1, r5, #1
	str r1, [r0, #0x18]
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9AD4:
	ldr r1, [sp]
	mov r0, #1
	str r0, [r1, #0x14]
	add sp, #8
	str r5, [r1, #0x18]
	pop {r3, r4, r5, r6, r7, pc}
_021D9AE0:
	ldr r0, [sp, #4]
	add r5, r5, #1
	cmp r5, r0
	ble _021D9A8E
_021D9AE8:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021D9A48

	thumb_func_start MOD85_021D9AF0
MOD85_021D9AF0: ; 0x021D9AF0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x48
	add r5, r2, #0
	add r2, r0, #0
	ldr r7, [r2, #0x10]
	add r2, sp, #0x3c
	str r2, [sp]
	add r2, sp, #0x44
	add r3, sp, #0x40
	str r0, [sp, #4]
	add r6, r1, #0
	bl MOD85_021DA0A8
	cmp r0, #0
	bne _021D9B14
	add sp, #0x48
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D9B14:
	ldr r2, [sp, #0x44]
	add r0, r6, #0
	add r1, r7, #0
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9B32
	ldr r1, [sp, #0x44]
	ldr r0, [sp, #4]
	add sp, #0x48
	str r1, [r0, #0x14]
	mov r1, #0
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9B32:
	ldr r2, [sp, #0x40]
	cmp r2, #0
	beq _021D9B54
	add r0, r6, #0
	add r1, r7, #0
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9B54
	ldr r1, [sp, #0x40]
	ldr r0, [sp, #4]
	add sp, #0x48
	str r1, [r0, #0x14]
	mov r1, #0
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9B54:
	ldr r2, [sp, #0x3c]
	cmp r2, #0
	beq _021D9B76
	add r0, r6, #0
	add r1, r7, #0
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9B76
	ldr r1, [sp, #0x3c]
	ldr r0, [sp, #4]
	add sp, #0x48
	str r1, [r0, #0x14]
	mov r1, #0
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9B76:
	ldr r0, [r6, #0x70]
	mov r4, #4
	cmp r0, #1
	bne _021D9B80
	mov r4, #0x15
_021D9B80:
	ldr r0, [sp, #0x40]
	cmp r0, #0
	bne _021D9BC0
	mov r0, #1
	str r0, [sp, #0x38]
	cmp r4, #1
	blt _021D9BBA
_021D9B8E:
	ldr r3, [sp, #0x44]
	ldr r2, [sp, #0x38]
	add r0, r6, #0
	add r1, r7, #0
	sub r2, r3, r2
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9BB0
	ldr r1, [sp, #0x44]
	ldr r0, [sp, #4]
	str r1, [r0, #0x14]
	ldr r1, [sp, #0x38]
	add sp, #0x48
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9BB0:
	ldr r0, [sp, #0x38]
	add r0, r0, #1
	str r0, [sp, #0x38]
	cmp r0, r4
	ble _021D9B8E
_021D9BBA:
	add sp, #0x48
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D9BC0:
	lsl r0, r7, #2
	add r0, r6, r0
	add r0, #0xa8
	ldr r1, [sp, #0x3c]
	ldr r0, [r0]
	cmp r1, #0
	bne _021D9CA6
	mov r1, #1
	str r1, [sp, #8]
	tst r0, r1
	beq _021D9C3C
	cmp r4, #1
	blt _021D9C06
_021D9BDA:
	ldr r3, [sp, #0x44]
	ldr r2, [sp, #8]
	add r0, r6, #0
	add r1, r7, #0
	sub r2, r3, r2
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9BFC
	ldr r1, [sp, #0x44]
	ldr r0, [sp, #4]
	str r1, [r0, #0x14]
	ldr r1, [sp, #8]
	add sp, #0x48
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9BFC:
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
	cmp r0, r4
	ble _021D9BDA
_021D9C06:
	mov r0, #1
	str r0, [sp, #0xc]
	cmp r4, #1
	blt _021D9CA0
_021D9C0E:
	ldr r3, [sp, #0x40]
	ldr r2, [sp, #0xc]
	add r0, r6, #0
	add r1, r7, #0
	sub r2, r3, r2
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9C30
	ldr r1, [sp, #0x40]
	ldr r0, [sp, #4]
	str r1, [r0, #0x14]
	ldr r1, [sp, #0xc]
	add sp, #0x48
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9C30:
	ldr r0, [sp, #0xc]
	add r0, r0, #1
	str r0, [sp, #0xc]
	cmp r0, r4
	ble _021D9C0E
	b _021D9CA0
_021D9C3C:
	cmp r4, #1
	blt _021D9C6C
_021D9C40:
	ldr r3, [sp, #0x40]
	ldr r2, [sp, #8]
	add r0, r6, #0
	add r1, r7, #0
	sub r2, r3, r2
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9C62
	ldr r1, [sp, #0x40]
	ldr r0, [sp, #4]
	str r1, [r0, #0x14]
	ldr r1, [sp, #8]
	add sp, #0x48
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9C62:
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
	cmp r0, r4
	ble _021D9C40
_021D9C6C:
	mov r0, #1
	str r0, [sp, #0x10]
	cmp r4, #1
	blt _021D9CA0
_021D9C74:
	ldr r3, [sp, #0x44]
	ldr r2, [sp, #0x10]
	add r0, r6, #0
	add r1, r7, #0
	sub r2, r3, r2
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9C96
	ldr r1, [sp, #0x44]
	ldr r0, [sp, #4]
	str r1, [r0, #0x14]
	ldr r1, [sp, #0x10]
	add sp, #0x48
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9C96:
	ldr r0, [sp, #0x10]
	add r0, r0, #1
	str r0, [sp, #0x10]
	cmp r0, r4
	ble _021D9C74
_021D9CA0:
	add sp, #0x48
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D9CA6:
	mov r1, #3
	bl _s32_div_f
	cmp r1, #0
	bne _021D9D4E
	mov r0, #1
	str r0, [sp, #0x14]
	cmp r4, #1
	blt _021D9CE4
_021D9CB8:
	ldr r3, [sp, #0x44]
	ldr r2, [sp, #0x14]
	add r0, r6, #0
	add r1, r7, #0
	sub r2, r3, r2
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9CDA
	ldr r1, [sp, #0x44]
	ldr r0, [sp, #4]
	str r1, [r0, #0x14]
	ldr r1, [sp, #0x14]
	add sp, #0x48
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9CDA:
	ldr r0, [sp, #0x14]
	add r0, r0, #1
	str r0, [sp, #0x14]
	cmp r0, r4
	ble _021D9CB8
_021D9CE4:
	mov r0, #1
	str r0, [sp, #0x18]
	cmp r4, #1
	blt _021D9D18
_021D9CEC:
	ldr r3, [sp, #0x40]
	ldr r2, [sp, #0x18]
	add r0, r6, #0
	add r1, r7, #0
	sub r2, r3, r2
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9D0E
	ldr r1, [sp, #0x40]
	ldr r0, [sp, #4]
	str r1, [r0, #0x14]
	ldr r1, [sp, #0x18]
	add sp, #0x48
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9D0E:
	ldr r0, [sp, #0x18]
	add r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, r4
	ble _021D9CEC
_021D9D18:
	mov r0, #1
	str r0, [sp, #0x1c]
	cmp r4, #1
	blt _021D9D4C
_021D9D20:
	ldr r3, [sp, #0x3c]
	ldr r2, [sp, #0x1c]
	add r0, r6, #0
	add r1, r7, #0
	sub r2, r3, r2
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9D42
	ldr r1, [sp, #0x3c]
	ldr r0, [sp, #4]
	str r1, [r0, #0x14]
	ldr r1, [sp, #0x1c]
	add sp, #0x48
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9D42:
	ldr r0, [sp, #0x1c]
	add r0, r0, #1
	str r0, [sp, #0x1c]
	cmp r0, r4
	ble _021D9D20
_021D9D4C:
	b _021D9E8C
_021D9D4E:
	cmp r1, #1
	bne _021D9DF0
	mov r0, #1
	str r0, [sp, #0x20]
	cmp r4, #1
	blt _021D9D86
_021D9D5A:
	ldr r3, [sp, #0x40]
	ldr r2, [sp, #0x20]
	add r0, r6, #0
	add r1, r7, #0
	sub r2, r3, r2
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9D7C
	ldr r1, [sp, #0x40]
	ldr r0, [sp, #4]
	str r1, [r0, #0x14]
	ldr r1, [sp, #0x20]
	add sp, #0x48
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9D7C:
	ldr r0, [sp, #0x20]
	add r0, r0, #1
	str r0, [sp, #0x20]
	cmp r0, r4
	ble _021D9D5A
_021D9D86:
	mov r0, #1
	str r0, [sp, #0x24]
	cmp r4, #1
	blt _021D9DBA
_021D9D8E:
	ldr r3, [sp, #0x3c]
	ldr r2, [sp, #0x24]
	add r0, r6, #0
	add r1, r7, #0
	sub r2, r3, r2
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9DB0
	ldr r1, [sp, #0x3c]
	ldr r0, [sp, #4]
	str r1, [r0, #0x14]
	ldr r1, [sp, #0x24]
	add sp, #0x48
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9DB0:
	ldr r0, [sp, #0x24]
	add r0, r0, #1
	str r0, [sp, #0x24]
	cmp r0, r4
	ble _021D9D8E
_021D9DBA:
	mov r0, #1
	str r0, [sp, #0x28]
	cmp r4, #1
	blt _021D9E8C
_021D9DC2:
	ldr r3, [sp, #0x44]
	ldr r2, [sp, #0x28]
	add r0, r6, #0
	add r1, r7, #0
	sub r2, r3, r2
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9DE4
	ldr r1, [sp, #0x44]
	ldr r0, [sp, #4]
	str r1, [r0, #0x14]
	ldr r1, [sp, #0x28]
	add sp, #0x48
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9DE4:
	ldr r0, [sp, #0x28]
	add r0, r0, #1
	str r0, [sp, #0x28]
	cmp r0, r4
	ble _021D9DC2
	b _021D9E8C
_021D9DF0:
	mov r0, #1
	str r0, [sp, #0x2c]
	cmp r4, #1
	blt _021D9E24
_021D9DF8:
	ldr r3, [sp, #0x3c]
	ldr r2, [sp, #0x2c]
	add r0, r6, #0
	add r1, r7, #0
	sub r2, r3, r2
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9E1A
	ldr r1, [sp, #0x3c]
	ldr r0, [sp, #4]
	str r1, [r0, #0x14]
	ldr r1, [sp, #0x2c]
	add sp, #0x48
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9E1A:
	ldr r0, [sp, #0x2c]
	add r0, r0, #1
	str r0, [sp, #0x2c]
	cmp r0, r4
	ble _021D9DF8
_021D9E24:
	mov r0, #1
	str r0, [sp, #0x30]
	cmp r4, #1
	blt _021D9E58
_021D9E2C:
	ldr r3, [sp, #0x44]
	ldr r2, [sp, #0x30]
	add r0, r6, #0
	add r1, r7, #0
	sub r2, r3, r2
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9E4E
	ldr r1, [sp, #0x44]
	ldr r0, [sp, #4]
	str r1, [r0, #0x14]
	ldr r1, [sp, #0x30]
	add sp, #0x48
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9E4E:
	ldr r0, [sp, #0x30]
	add r0, r0, #1
	str r0, [sp, #0x30]
	cmp r0, r4
	ble _021D9E2C
_021D9E58:
	mov r0, #1
	str r0, [sp, #0x34]
	cmp r4, #1
	blt _021D9E8C
_021D9E60:
	ldr r3, [sp, #0x40]
	ldr r2, [sp, #0x34]
	add r0, r6, #0
	add r1, r7, #0
	sub r2, r3, r2
	bl MOD85_021DBD30
	cmp r5, r0
	bne _021D9E82
	ldr r1, [sp, #0x40]
	ldr r0, [sp, #4]
	str r1, [r0, #0x14]
	ldr r1, [sp, #0x34]
	add sp, #0x48
	str r1, [r0, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9E82:
	ldr r0, [sp, #0x34]
	add r0, r0, #1
	str r0, [sp, #0x34]
	cmp r0, r4
	ble _021D9E60
_021D9E8C:
	mov r0, #0
	add sp, #0x48
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021D9AF0

	thumb_func_start MOD85_021D9E94
MOD85_021D9E94: ; 0x021D9E94
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp]
	ldr r0, [r0, #0x10]
	add r6, r1, #0
	str r0, [sp, #4]
	ldr r0, [r6, #0x70]
	add r7, r2, #0
	mov r5, #4
	cmp r0, #1
	bne _021D9EAC
	mov r5, #0x15
_021D9EAC:
	mov r4, #0
	cmp r5, #0
	blt _021D9ED6
_021D9EB2:
	mov r2, #2
	ldr r1, [sp, #4]
	add r0, r6, #0
	sub r2, r2, r4
	bl MOD85_021DBD30
	cmp r7, r0
	bne _021D9ED0
	ldr r0, [sp]
	mov r1, #2
	str r1, [r0, #0x14]
	str r4, [r0, #0x18]
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9ED0:
	add r4, r4, #1
	cmp r4, r5
	ble _021D9EB2
_021D9ED6:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD85_021D9E94

	thumb_func_start MOD85_021D9EDC
MOD85_021D9EDC: ; 0x021D9EDC
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r0, #0
	add r0, r4, #0
	bl MOD85_021DA040
	ldr r1, [r6, #0x10]
	cmp r1, #0
	beq _021D9EF2
	cmp r0, #2
	blt _021D9F88
_021D9EF2:
	cmp r1, #0
	bne _021D9F18
	cmp r0, #2
	bge _021D9F18
	mov r5, #0
_021D9EFC:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD85_021DA24C
	cmp r0, #0
	bne _021D9F0C
	str r5, [r6, #0x18]
	pop {r4, r5, r6, pc}
_021D9F0C:
	add r5, r5, #1
	cmp r5, #0x15
	ble _021D9EFC
	bl ErrorHandling
	pop {r4, r5, r6, pc}
_021D9F18:
	cmp r1, #0
	beq _021D9F26
	cmp r1, #1
	beq _021D9F46
	cmp r1, #2
	beq _021D9F66
	b _021D9F84
_021D9F26:
	mov r5, #1
_021D9F28:
	add r0, r6, #0
	add r1, r4, #0
	add r2, r5, #0
	bl MOD85_021DA2AC
	cmp r0, #0
	bne _021D9F3A
	str r5, [r6, #0x18]
	pop {r4, r5, r6, pc}
_021D9F3A:
	add r5, r5, #1
	cmp r5, #0x15
	ble _021D9F28
	bl ErrorHandling
	pop {r4, r5, r6, pc}
_021D9F46:
	mov r5, #1
_021D9F48:
	add r0, r6, #0
	add r1, r4, #0
	add r2, r5, #0
	bl MOD85_021DA3F8
	cmp r0, #0
	bne _021D9F5A
	str r5, [r6, #0x18]
	pop {r4, r5, r6, pc}
_021D9F5A:
	add r5, r5, #1
	cmp r5, #0x15
	ble _021D9F48
	bl ErrorHandling
	b _021D9F84
_021D9F66:
	mov r5, #1
_021D9F68:
	add r0, r6, #0
	add r1, r4, #0
	add r2, r5, #0
	bl MOD85_021DA530
	cmp r0, #0
	bne _021D9F7A
	str r5, [r6, #0x18]
	pop {r4, r5, r6, pc}
_021D9F7A:
	add r5, r5, #1
	cmp r5, #0x15
	ble _021D9F68
	bl ErrorHandling
_021D9F84:
	bl ErrorHandling
_021D9F88:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD85_021D9EDC

	thumb_func_start MOD85_021D9F8C
MOD85_021D9F8C: ; 0x021D9F8C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r6, r0, #0
	add r0, r4, #0
	bl MOD85_021DA040
	ldr r1, [r6, #0x10]
	cmp r1, #0
	beq _021D9FA2
	cmp r0, #2
	blt _021DA03C
_021D9FA2:
	cmp r1, #0
	bne _021D9FCA
	cmp r0, #2
	bge _021D9FCA
	mov r5, #0
	mov r7, #2
_021D9FAE:
	add r0, r4, #0
	mov r1, #0
	sub r2, r7, r5
	bl MOD85_021DBD30
	cmp r0, #3
	beq _021D9FC0
	str r5, [r6, #0x18]
	pop {r3, r4, r5, r6, r7, pc}
_021D9FC0:
	add r5, r5, #1
	cmp r5, #0x15
	blt _021D9FAE
	bl ErrorHandling
_021D9FCA:
	ldr r0, [r6, #0x10]
	cmp r0, #0
	beq _021D9FDA
	cmp r0, #1
	beq _021D9FFA
	cmp r0, #2
	beq _021DA01A
	b _021DA038
_021D9FDA:
	mov r5, #0
_021D9FDC:
	add r0, r6, #0
	add r1, r4, #0
	add r2, r5, #0
	bl MOD85_021DA668
	cmp r0, #0
	bne _021D9FEE
	str r5, [r6, #0x18]
	pop {r3, r4, r5, r6, r7, pc}
_021D9FEE:
	add r5, r5, #1
	cmp r5, #0x15
	blt _021D9FDC
	bl ErrorHandling
	pop {r3, r4, r5, r6, r7, pc}
_021D9FFA:
	mov r5, #0
_021D9FFC:
	add r0, r6, #0
	add r1, r4, #0
	add r2, r5, #0
	bl MOD85_021DA6B4
	cmp r0, #0
	bne _021DA00E
	str r5, [r6, #0x18]
	pop {r3, r4, r5, r6, r7, pc}
_021DA00E:
	add r5, r5, #1
	cmp r5, #0x15
	ble _021D9FFC
	bl ErrorHandling
	pop {r3, r4, r5, r6, r7, pc}
_021DA01A:
	mov r5, #0
_021DA01C:
	add r0, r6, #0
	add r1, r4, #0
	add r2, r5, #0
	bl MOD85_021DA6FC
	cmp r0, #0
	bne _021DA02E
	str r5, [r6, #0x18]
	pop {r3, r4, r5, r6, r7, pc}
_021DA02E:
	add r5, r5, #1
	cmp r5, #0x15
	ble _021DA01C
	bl ErrorHandling
_021DA038:
	bl ErrorHandling
_021DA03C:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021D9F8C

	thumb_func_start MOD85_021DA040
MOD85_021DA040: ; 0x021DA040
	mov r2, #0
	add r3, r2, #0
_021DA044:
	ldr r1, [r0, #0x7c]
	cmp r1, #1
	beq _021DA04C
	add r3, r3, #1
_021DA04C:
	add r2, r2, #1
	add r0, r0, #4
	cmp r2, #3
	blt _021DA044
	add r0, r3, #0
	bx lr
	thumb_func_end MOD85_021DA040

	thumb_func_start MOD85_021DA058
MOD85_021DA058: ; 0x021DA058
	ldr r0, [r0, #0x10]
	cmp r0, #0
	beq _021DA068
	cmp r0, #1
	beq _021DA07E
	cmp r0, #2
	beq _021DA090
	b _021DA0A2
_021DA068:
	add r0, r1, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #1
	bne _021DA07A
	add r1, #0x84
	ldr r0, [r1]
	cmp r0, #1
	beq _021DA0A2
_021DA07A:
	mov r0, #0
	bx lr
_021DA07E:
	ldr r0, [r1, #0x7c]
	cmp r0, #1
	bne _021DA08C
	add r1, #0x84
	ldr r0, [r1]
	cmp r0, #1
	beq _021DA0A2
_021DA08C:
	mov r0, #0
	bx lr
_021DA090:
	ldr r0, [r1, #0x7c]
	cmp r0, #1
	bne _021DA09E
	add r1, #0x80
	ldr r0, [r1]
	cmp r0, #1
	beq _021DA0A2
_021DA09E:
	mov r0, #0
	bx lr
_021DA0A2:
	mov r0, #1
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021DA058

	thumb_func_start MOD85_021DA0A8
MOD85_021DA0A8: ; 0x021DA0A8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp]
	add r5, r1, #0
	ldr r0, [sp, #0x20]
	add r1, r3, #0
	str r0, [sp, #0x20]
	add r0, r5, #0
	add r0, #0x80
	ldr r0, [r0]
	ldr r7, [r5, #0x7c]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x84
	ldr r0, [r0]
	mov r3, #0
	mov ip, r0
	add r0, r5, #0
	add r0, #0xc8
	ldr r4, [r0]
	add r0, r5, #0
	add r0, #0xec
	ldr r6, [r0]
	mov r0, #0x11
	lsl r0, r0, #4
	ldr r5, [r5, r0]
	ldr r0, [sp, #0x20]
	str r3, [r2]
	str r3, [r1]
	str r3, [r0]
	ldr r0, [sp]
	ldr r0, [r0, #0x10]
	cmp r0, #0
	beq _021DA0F6
	cmp r0, #1
	beq _021DA160
	cmp r0, #2
	beq _021DA1DC
	b _021DA240
_021DA0F6:
	ldr r0, [sp, #4]
	cmp r0, #1
	beq _021DA124
	mov r0, ip
	cmp r0, #1
	beq _021DA124
	cmp r6, r5
	bne _021DA10E
	add sp, #8
	str r6, [r2]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA10E:
	cmp r5, #1
	bne _021DA11C
	mov r0, #3
	str r0, [r2]
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA11C:
	mov r0, #1
	str r0, [r2]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_021DA124:
	ldr r0, [sp, #4]
	cmp r0, #1
	beq _021DA148
	cmp r6, #2
	bne _021DA140
	mov r0, #1
	str r0, [r2]
	mov r2, #2
	str r2, [r1]
	ldr r1, [sp, #0x20]
	mov r2, #3
	str r2, [r1]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_021DA140:
	add sp, #8
	str r6, [r2]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA148:
	cmp r5, #2
	bne _021DA154
	add sp, #8
	str r5, [r2]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA154:
	mov r0, #1
	str r0, [r2]
	mov r2, #3
	str r2, [r1]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_021DA160:
	cmp r7, #1
	beq _021DA180
	mov r0, ip
	cmp r0, #1
	beq _021DA180
	cmp r4, r5
	bne _021DA176
	add sp, #8
	str r4, [r2]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA176:
	mov r0, #2
	str r0, [r2]
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA180:
	cmp r7, #1
	beq _021DA1B0
	cmp r4, #2
	bne _021DA192
	mov r0, #2
	str r0, [r2]
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA192:
	cmp r4, #1
	bne _021DA1A2
	mov r0, #1
	str r0, [r2]
	mov r2, #2
	str r2, [r1]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_021DA1A2:
	mov r0, #2
	str r0, [r2]
	mov r0, #3
	str r0, [r1]
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA1B0:
	cmp r5, #2
	bne _021DA1BE
	mov r0, #2
	str r0, [r2]
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA1BE:
	cmp r5, #1
	bne _021DA1CE
	mov r0, #1
	str r0, [r2]
	mov r2, #2
	str r2, [r1]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_021DA1CE:
	mov r0, #2
	str r0, [r2]
	mov r0, #3
	str r0, [r1]
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA1DC:
	cmp r7, #1
	beq _021DA204
	ldr r0, [sp, #4]
	cmp r0, #1
	beq _021DA204
	cmp r4, r6
	bne _021DA1F2
	add sp, #8
	str r4, [r2]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA1F2:
	cmp r4, #1
	bne _021DA1FA
	mov r0, #3
	b _021DA1FC
_021DA1FA:
	mov r0, #1
_021DA1FC:
	str r0, [r2]
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA204:
	cmp r7, #1
	beq _021DA222
	cmp r4, #2
	bne _021DA216
	mov r0, #2
	str r0, [r2]
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA216:
	mov r0, #1
	str r0, [r2]
	mov r2, #3
	str r2, [r1]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_021DA222:
	cmp r6, #2
	bne _021DA238
	mov r0, #1
	str r0, [r2]
	mov r2, #2
	str r2, [r1]
	ldr r1, [sp, #0x20]
	mov r2, #3
	str r2, [r1]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_021DA238:
	add sp, #8
	str r6, [r2]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA240:
	bl ErrorHandling
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021DA0A8

	thumb_func_start MOD85_021DA24C
MOD85_021DA24C: ; 0x021DA24C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r2, #1
	mov r1, #0
	sub r2, r2, r4
	add r5, r0, #0
	bl MOD85_021DBD30
	cmp r0, #3
	bne _021DA264
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DA264:
	mov r2, #2
	add r0, r5, #0
	mov r1, #0
	sub r2, r2, r4
	bl MOD85_021DBD30
	cmp r0, #3
	bne _021DA278
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DA278:
	mov r2, #3
	add r0, r5, #0
	mov r1, #0
	sub r2, r2, r4
	bl MOD85_021DBD30
	cmp r0, #3
	bne _021DA28C
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DA28C:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD85_021DA24C

	thumb_func_start MOD85_021DA290
MOD85_021DA290: ; 0x021DA290
	push {r3, lr}
	cmp r2, #3
	bne _021DA29A
	mov r0, #1
	pop {r3, pc}
_021DA29A:
	bl MOD85_021DA24C
	cmp r0, #0
	bne _021DA2A6
	mov r0, #1
	pop {r3, pc}
_021DA2A6:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD85_021DA290

	thumb_func_start MOD85_021DA2AC
MOD85_021DA2AC: ; 0x021DA2AC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r4, r1, #0
	add r0, r4, #0
	add r0, #0xf0
	ldr r7, [r0]
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r6, [r4, r0]
	mov r1, #1
	add r0, r2, #0
	sub r0, r1, r0
	str r0, [sp, #0x10]
	str r2, [sp]
	ldr r2, [sp, #0x10]
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021DBD30
	mov r1, #1
	add r5, r0, #0
	add r0, r4, #0
	sub r2, r1, r7
	bl MOD85_021DBD30
	str r0, [sp, #0x14]
	mov r0, #1
	sub r0, r0, r6
	str r0, [sp, #4]
	ldr r2, [sp, #4]
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021DBD30
	cmp r5, #3
	beq _021DA2FE
	ldr r1, [sp, #0x14]
	cmp r5, r1
	bne _021DA304
	cmp r5, r0
	bne _021DA304
_021DA2FE:
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA304:
	ldr r2, [sp]
	mov r3, #2
	add r0, r4, #0
	mov r1, #0
	sub r2, r3, r2
	bl MOD85_021DBD30
	add r5, r0, #0
	mov r0, #2
	sub r0, r0, r7
	str r0, [sp, #0xc]
	ldr r2, [sp, #0xc]
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021DBD30
	mov r1, #2
	str r0, [sp, #0x18]
	add r0, r4, #0
	sub r2, r1, r6
	bl MOD85_021DBD30
	cmp r5, #3
	beq _021DA33E
	ldr r1, [sp, #0x18]
	cmp r5, r1
	bne _021DA344
	cmp r5, r0
	bne _021DA344
_021DA33E:
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA344:
	ldr r0, [sp]
	mov r1, #3
	sub r0, r1, r0
	str r0, [sp, #8]
	ldr r2, [sp, #8]
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021DBD30
	mov r2, #3
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	sub r2, r2, r7
	bl MOD85_021DBD30
	add r7, r0, #0
	mov r0, #3
	sub r0, r0, r6
	str r0, [sp, #0x1c]
	ldr r2, [sp, #0x1c]
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021DBD30
	cmp r5, #3
	beq _021DA382
	cmp r5, r7
	bne _021DA388
	cmp r5, r0
	bne _021DA388
_021DA382:
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA388:
	ldr r2, [sp, #0x10]
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021DBD30
	add r5, r0, #0
	ldr r2, [sp, #0xc]
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021DBD30
	add r6, r0, #0
	ldr r2, [sp, #0x1c]
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021DBD30
	cmp r5, #3
	beq _021DA3B6
	cmp r5, r6
	bne _021DA3BC
	cmp r5, r0
	bne _021DA3BC
_021DA3B6:
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA3BC:
	ldr r2, [sp, #8]
	add r0, r4, #0
	mov r1, #0
	bl MOD85_021DBD30
	add r5, r0, #0
	ldr r2, [sp, #0xc]
	add r0, r4, #0
	mov r1, #1
	bl MOD85_021DBD30
	add r6, r0, #0
	ldr r2, [sp, #4]
	add r0, r4, #0
	mov r1, #2
	bl MOD85_021DBD30
	cmp r5, #3
	beq _021DA3EA
	cmp r5, r6
	bne _021DA3F0
	cmp r5, r0
	bne _021DA3F0
_021DA3EA:
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA3F0:
	mov r0, #0
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021DA2AC

	thumb_func_start MOD85_021DA3F8
MOD85_021DA3F8: ; 0x021DA3F8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r1, #0
	add r0, r5, #0
	add r0, #0xcc
	ldr r6, [r0]
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r4, [r5, r0]
	mov r0, #1
	sub r0, r0, r6
	str r0, [sp, #0xc]
	add r7, r2, #0
	ldr r2, [sp, #0xc]
	add r0, r5, #0
	mov r1, #0
	bl MOD85_021DBD30
	mov r1, #1
	str r0, [sp, #0x10]
	add r0, r5, #0
	sub r2, r1, r7
	bl MOD85_021DBD30
	str r0, [sp, #0x14]
	mov r0, #1
	sub r0, r0, r4
	str r0, [sp]
	ldr r2, [sp]
	add r0, r5, #0
	mov r1, #2
	bl MOD85_021DBD30
	ldr r2, [sp, #0x10]
	ldr r1, [sp, #0x14]
	cmp r2, r1
	bne _021DA44E
	add r1, r2, #0
	cmp r1, r0
	bne _021DA44E
	add sp, #0x24
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021DA44E:
	mov r2, #2
	add r0, r5, #0
	mov r1, #0
	sub r2, r2, r6
	bl MOD85_021DBD30
	str r0, [sp, #0x18]
	mov r0, #2
	sub r0, r0, r7
	str r0, [sp, #8]
	ldr r2, [sp, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD85_021DBD30
	mov r1, #2
	str r0, [sp, #0x1c]
	add r0, r5, #0
	sub r2, r1, r4
	bl MOD85_021DBD30
	ldr r2, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	cmp r2, r1
	bne _021DA48C
	add r1, r2, #0
	cmp r1, r0
	bne _021DA48C
	add sp, #0x24
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021DA48C:
	mov r0, #3
	sub r0, r0, r6
	str r0, [sp, #4]
	ldr r2, [sp, #4]
	add r0, r5, #0
	mov r1, #0
	bl MOD85_021DBD30
	mov r2, #3
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	sub r2, r2, r7
	bl MOD85_021DBD30
	str r0, [sp, #0x20]
	mov r0, #3
	sub r7, r0, r4
	add r0, r5, #0
	mov r1, #2
	add r2, r7, #0
	bl MOD85_021DBD30
	ldr r1, [sp, #0x20]
	cmp r6, r1
	bne _021DA4CA
	cmp r6, r0
	bne _021DA4CA
	add sp, #0x24
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021DA4CA:
	ldr r2, [sp, #0xc]
	add r0, r5, #0
	mov r1, #0
	bl MOD85_021DBD30
	add r4, r0, #0
	ldr r2, [sp, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD85_021DBD30
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #2
	add r2, r7, #0
	bl MOD85_021DBD30
	cmp r4, r6
	bne _021DA4FA
	cmp r4, r0
	bne _021DA4FA
	add sp, #0x24
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021DA4FA:
	ldr r2, [sp, #4]
	add r0, r5, #0
	mov r1, #0
	bl MOD85_021DBD30
	add r4, r0, #0
	ldr r2, [sp, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD85_021DBD30
	add r6, r0, #0
	ldr r2, [sp]
	add r0, r5, #0
	mov r1, #2
	bl MOD85_021DBD30
	cmp r4, r6
	bne _021DA52A
	cmp r4, r0
	bne _021DA52A
	add sp, #0x24
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021DA52A:
	mov r0, #0
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD85_021DA3F8

	thumb_func_start MOD85_021DA530
MOD85_021DA530: ; 0x021DA530
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r1, #0
	add r0, r5, #0
	add r0, #0xcc
	ldr r6, [r0]
	add r0, r5, #0
	add r0, #0xf0
	ldr r4, [r0]
	mov r0, #1
	sub r0, r0, r6
	str r0, [sp, #0xc]
	add r7, r2, #0
	ldr r2, [sp, #0xc]
	add r0, r5, #0
	mov r1, #0
	bl MOD85_021DBD30
	mov r1, #1
	str r0, [sp, #0x10]
	add r0, r5, #0
	sub r2, r1, r4
	bl MOD85_021DBD30
	str r0, [sp, #0x14]
	mov r0, #1
	sub r0, r0, r7
	str r0, [sp]
	ldr r2, [sp]
	add r0, r5, #0
	mov r1, #2
	bl MOD85_021DBD30
	ldr r2, [sp, #0x10]
	ldr r1, [sp, #0x14]
	cmp r2, r1
	bne _021DA586
	add r1, r2, #0
	cmp r1, r0
	bne _021DA586
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA586:
	mov r2, #2
	add r0, r5, #0
	mov r1, #0
	sub r2, r2, r6
	bl MOD85_021DBD30
	str r0, [sp, #0x18]
	mov r0, #2
	sub r0, r0, r4
	str r0, [sp, #8]
	ldr r2, [sp, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD85_021DBD30
	mov r1, #2
	str r0, [sp, #0x1c]
	add r0, r5, #0
	sub r2, r1, r7
	bl MOD85_021DBD30
	ldr r2, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	cmp r2, r1
	bne _021DA5C4
	add r1, r2, #0
	cmp r1, r0
	bne _021DA5C4
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA5C4:
	mov r0, #3
	sub r0, r0, r6
	str r0, [sp, #4]
	ldr r2, [sp, #4]
	add r0, r5, #0
	mov r1, #0
	bl MOD85_021DBD30
	mov r2, #3
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	sub r2, r2, r4
	bl MOD85_021DBD30
	add r4, r0, #0
	mov r0, #3
	sub r7, r0, r7
	add r0, r5, #0
	mov r1, #2
	add r2, r7, #0
	bl MOD85_021DBD30
	cmp r6, r4
	bne _021DA600
	cmp r6, r0
	bne _021DA600
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA600:
	ldr r2, [sp, #0xc]
	add r0, r5, #0
	mov r1, #0
	bl MOD85_021DBD30
	add r4, r0, #0
	ldr r2, [sp, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD85_021DBD30
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #2
	add r2, r7, #0
	bl MOD85_021DBD30
	cmp r4, r6
	bne _021DA630
	cmp r4, r0
	bne _021DA630
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA630:
	ldr r2, [sp, #4]
	add r0, r5, #0
	mov r1, #0
	bl MOD85_021DBD30
	add r4, r0, #0
	ldr r2, [sp, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD85_021DBD30
	add r6, r0, #0
	ldr r2, [sp]
	add r0, r5, #0
	mov r1, #2
	bl MOD85_021DBD30
	cmp r4, r6
	bne _021DA660
	cmp r4, r0
	bne _021DA660
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA660:
	mov r0, #0
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021DA530

	thumb_func_start MOD85_021DA668
MOD85_021DA668: ; 0x021DA668
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r0, r5, #0
	add r0, #0xf0
	ldr r7, [r0]
	mov r0, #0x45
	lsl r0, r0, #2
	mov r3, #2
	ldr r6, [r5, r0]
	add r0, r5, #0
	mov r1, #0
	sub r2, r3, r2
	bl MOD85_021DBD30
	mov r2, #2
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #1
	sub r2, r2, r7
	bl MOD85_021DBD30
	mov r1, #2
	add r7, r0, #0
	add r0, r5, #0
	sub r2, r1, r6
	bl MOD85_021DBD30
	cmp r4, #3
	beq _021DA6AA
	cmp r4, r7
	bne _021DA6AE
	cmp r4, r0
	bne _021DA6AE
_021DA6AA:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA6AE:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021DA668

	thumb_func_start MOD85_021DA6B4
MOD85_021DA6B4: ; 0x021DA6B4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r2, #0
	add r2, r5, #0
	add r2, #0xcc
	mov r0, #0x45
	ldr r3, [r2]
	lsl r0, r0, #2
	mov r2, #2
	ldr r6, [r5, r0]
	add r0, r5, #0
	mov r1, #0
	sub r2, r2, r3
	bl MOD85_021DBD30
	mov r2, #2
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #1
	sub r2, r2, r7
	bl MOD85_021DBD30
	mov r1, #2
	add r7, r0, #0
	add r0, r5, #0
	sub r2, r1, r6
	bl MOD85_021DBD30
	cmp r4, r7
	bne _021DA6F8
	cmp r4, r0
	bne _021DA6F8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA6F8:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD85_021DA6B4

	thumb_func_start MOD85_021DA6FC
MOD85_021DA6FC: ; 0x021DA6FC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r2, #0
	add r2, r5, #0
	add r2, #0xcc
	add r0, r5, #0
	ldr r3, [r2]
	add r0, #0xf0
	mov r2, #2
	ldr r6, [r0]
	add r0, r5, #0
	mov r1, #0
	sub r2, r2, r3
	bl MOD85_021DBD30
	mov r2, #2
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #1
	sub r2, r2, r6
	bl MOD85_021DBD30
	mov r1, #2
	add r6, r0, #0
	add r0, r5, #0
	sub r2, r1, r7
	bl MOD85_021DBD30
	cmp r4, r6
	bne _021DA740
	cmp r4, r0
	bne _021DA740
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DA740:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD85_021DA6FC

	thumb_func_start MOD85_021DA744
MOD85_021DA744: ; 0x021DA744
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r4, r6, #0
	lsl r5, r1, #2
	add r4, #0x90
	ldr r0, [r4, r5]
	mov r1, #0x2a
	add r0, r0, r2
	str r0, [r4, r5]
	ldr r0, [r4, r5]
	lsl r1, r1, #0x10
	bl _s32_div_f
	str r1, [r4, r5]
	ldr r1, [r4, r5]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r1, r0, #0xc
	asr r0, r1, #4
	lsr r0, r0, #0x1b
	add r0, r1, r0
	asr r1, r0, #5
	mov r0, #0x15
	sub r1, r0, r1
	add r0, r6, r5
	add r0, #0xa8
	str r1, [r0]
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD85_021DA744

	thumb_func_start MOD85_021DA780
MOD85_021DA780: ; 0x021DA780
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r7, #0
	add r5, #0x90
	lsl r4, r1, #2
	ldr r0, [r5, r4]
	lsr r6, r0, #0x1f
	lsl r3, r0, #0xf
	sub r3, r3, r6
	mov r0, #0xf
	ror r3, r0
	add r0, r6, r3
	beq _021DA7B4
	cmp r0, r2
	bge _021DA7A0
	add r2, r0, #0
_021DA7A0:
	add r0, r7, #0
	bl MOD85_021DA744
	ldr r0, [r5, r4]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0xf
	sub r1, r1, r2
	mov r0, #0xf
	ror r1, r0
	add r0, r2, r1
_021DA7B4:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021DA780

	thumb_func_start MOD85_021DA7B8
MOD85_021DA7B8: ; 0x021DA7B8
	push {r3, lr}
	bl LCRandom
	mov r1, #0x64
	bl _u32_div_f
	add r0, r1, #0
	pop {r3, pc}
	thumb_func_end MOD85_021DA7B8

	thumb_func_start MOD85_021DA7C8
MOD85_021DA7C8: ; 0x021DA7C8
	ldr r3, [r1]
	sub r2, r3, r0
	str r2, [r1]
	bpl _021DA7D4
	mov r2, #0
	str r2, [r1]
_021DA7D4:
	cmp r3, r0
	bhs _021DA7DC
	mov r0, #1
	bx lr
_021DA7DC:
	mov r0, #0
	bx lr
	thumb_func_end MOD85_021DA7C8

	thumb_func_start MOD85_021DA7E0
MOD85_021DA7E0: ; 0x021DA7E0
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DA7B8
	add r4, #0x88
	ldr r1, [r4]
	lsl r2, r1, #2
	ldr r1, _021DA800 ; =0x021DFC7C
	ldr r1, [r1, r2]
	cmp r1, r0
	bls _021DA7FA
	mov r0, #1
	pop {r4, pc}
_021DA7FA:
	mov r0, #0
	pop {r4, pc}
	nop
_021DA800: .word MOD85_021DFC7C
	thumb_func_end MOD85_021DA7E0

	thumb_func_start MOD85_021DA804
MOD85_021DA804: ; 0x021DA804
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r1, #0
	str r1, [r5, #0x74]
	bl MOD85_021DA7E0
	cmp r0, #1
	beq _021DA816
	b _021DA928
_021DA816:
	add r0, r5, #0
	bl MOD85_021DA7B8
	add r1, r5, #0
	str r0, [sp]
	add r1, #0x88
	ldr r1, [r1]
	ldr r0, _021DA92C ; =0x021DFD24
	lsl r3, r1, #4
	mov r1, #0x47
	lsl r1, r1, #4
	ldr r2, [r5, r1]
	add r4, r0, r3
	add r2, r2, #1
	str r2, [r5, r1]
	ldrh r0, [r0, r3]
	add r1, sp, #0
	bl MOD85_021DA7C8
	cmp r0, #0
	beq _021DA856
	ldr r1, [r5, #0x74]
	mov r0, #8
	orr r0, r1
	str r0, [r5, #0x74]
	mov r0, #0x4a
	lsl r0, r0, #4
	ldr r1, [r5, r0]
	add r1, r1, #1
	str r1, [r5, r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DA856:
	ldrh r0, [r4, #2]
	add r1, sp, #0
	bl MOD85_021DA7C8
	cmp r0, #0
	beq _021DA876
	ldr r1, [r5, #0x74]
	mov r0, #4
	orr r0, r1
	str r0, [r5, #0x74]
	ldr r0, _021DA930 ; =0x0000049C
	ldr r1, [r5, r0]
	add r1, r1, #1
	str r1, [r5, r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DA876:
	ldrh r0, [r4, #4]
	add r1, sp, #0
	bl MOD85_021DA7C8
	cmp r0, #0
	beq _021DA898
	ldr r1, [r5, #0x74]
	mov r0, #0x80
	orr r0, r1
	str r0, [r5, #0x74]
	mov r0, #0x4b
	lsl r0, r0, #4
	ldr r1, [r5, r0]
	add r1, r1, #1
	str r1, [r5, r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DA898:
	ldrh r0, [r4, #6]
	add r1, sp, #0
	bl MOD85_021DA7C8
	cmp r0, #0
	beq _021DA8B8
	ldr r1, [r5, #0x74]
	mov r0, #0x40
	orr r0, r1
	str r0, [r5, #0x74]
	ldr r0, _021DA934 ; =0x000004AC
	ldr r1, [r5, r0]
	add r1, r1, #1
	str r1, [r5, r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DA8B8:
	ldrh r0, [r4, #8]
	add r1, sp, #0
	bl MOD85_021DA7C8
	cmp r0, #0
	beq _021DA8D8
	ldr r1, [r5, #0x74]
	mov r0, #0x20
	orr r0, r1
	str r0, [r5, #0x74]
	ldr r0, _021DA938 ; =0x000004A8
	ldr r1, [r5, r0]
	add r1, r1, #1
	str r1, [r5, r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DA8D8:
	ldrh r0, [r4, #0xa]
	add r1, sp, #0
	bl MOD85_021DA7C8
	cmp r0, #0
	beq _021DA8F8
	ldr r1, [r5, #0x74]
	mov r0, #0x10
	orr r0, r1
	str r0, [r5, #0x74]
	ldr r0, _021DA93C ; =0x000004A4
	ldr r1, [r5, r0]
	add r1, r1, #1
	str r1, [r5, r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DA8F8:
	ldrh r0, [r4, #0xc]
	add r1, sp, #0
	bl MOD85_021DA7C8
	cmp r0, #0
	ldr r1, [r5, #0x74]
	beq _021DA918
	mov r0, #2
	orr r0, r1
	str r0, [r5, #0x74]
	ldr r0, _021DA940 ; =0x00000498
	ldr r1, [r5, r0]
	add r1, r1, #1
	str r1, [r5, r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DA918:
	mov r0, #1
	orr r1, r0
	str r1, [r5, #0x74]
	ldr r1, _021DA944 ; =0x00000494
	ldr r2, [r5, r1]
	add r2, r2, #1
	str r2, [r5, r1]
	pop {r3, r4, r5, pc}
_021DA928:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DA92C: .word MOD85_021DFD24
_021DA930: .word 0x0000049C
_021DA934: .word 0x000004AC
_021DA938: .word 0x000004A8
_021DA93C: .word 0x000004A4
_021DA940: .word 0x00000498
_021DA944: .word 0x00000494
	thumb_func_end MOD85_021DA804

	thumb_func_start MOD85_021DA948
MOD85_021DA948: ; 0x021DA948
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DA7B8
	add r4, #0x88
	ldr r1, [r4]
	lsl r2, r1, #2
	ldr r1, _021DA968 ; =0x021DFC34
	ldr r1, [r1, r2]
	cmp r0, r1
	bhs _021DA962
	mov r0, #1
	pop {r4, pc}
_021DA962:
	mov r0, #0
	pop {r4, pc}
	nop
_021DA968: .word MOD85_021DFC34
	thumb_func_end MOD85_021DA948

	thumb_func_start MOD85_021DA96C
MOD85_021DA96C: ; 0x021DA96C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	bl MOD85_021DA7B8
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x88
	ldr r1, [r0]
	mov r0, #0x48
	ldr r2, _021DAA1C ; =0x021E0090
	mul r0, r1
	add r0, r2, r0
	str r0, [sp]
	mov r6, #0
	add r4, r0, #0
	add r7, sp, #4
_021DA98E:
	ldr r0, [r4]
	add r1, r7, #0
	bl MOD85_021DA7C8
	cmp r0, #1
	bne _021DA9EE
	mov r0, #0xc
	add r1, r6, #0
	mul r1, r0
	ldr r0, [sp]
	add r1, r0, r1
	ldr r0, [r1, #4]
	str r0, [r5, #0x50]
	ldr r0, [r1, #8]
	str r0, [r5, #0x4c]
	ldr r0, [r5, #0x50]
	lsl r1, r0, #2
	ldr r0, _021DAA20 ; =0x021DFCC4
	ldr r0, [r0, r1]
	str r0, [r5, #0x18]
	ldr r0, [r5, #0x4c]
	cmp r0, #0
	beq _021DA9C8
	cmp r0, #1
	beq _021DA9D4
	cmp r0, #2
	beq _021DA9E0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_021DA9C8:
	ldr r0, _021DAA24 ; =0x00000478
	add sp, #8
	ldr r1, [r5, r0]
	add r1, r1, #1
	str r1, [r5, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021DA9D4:
	ldr r0, _021DAA28 ; =0x0000047C
	add sp, #8
	ldr r1, [r5, r0]
	add r1, r1, #1
	str r1, [r5, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021DA9E0:
	mov r0, #0x12
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	add sp, #8
	add r1, r1, #1
	str r1, [r5, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021DA9EE:
	add r6, r6, #1
	add r4, #0xc
	cmp r6, #6
	blt _021DA98E
	sub r1, r6, #1
	mov r0, #0xc
	add r2, r1, #0
	mul r2, r0
	ldr r0, [sp]
	add r1, r0, r2
	ldr r0, [r1, #4]
	str r0, [r5, #0x50]
	ldr r0, [r1, #8]
	str r0, [r5, #0x4c]
	ldr r0, [r5, #0x50]
	lsl r1, r0, #2
	ldr r0, _021DAA20 ; =0x021DFCC4
	ldr r0, [r0, r1]
	str r0, [r5, #0x18]
	bl ErrorHandling
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DAA1C: .word MOD85_021E0090
_021DAA20: .word MOD85_021DFCC4
_021DAA24: .word 0x00000478
_021DAA28: .word 0x0000047C
	thumb_func_end MOD85_021DA96C

	thumb_func_start MOD85_021DAA2C
MOD85_021DAA2C: ; 0x021DAA2C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	mov r4, #0
	bl MOD85_021DA7B8
	str r0, [sp, #4]
	add r0, r6, #0
	add r0, #0x88
	ldr r1, [r0]
	mov r0, #0x48
	mul r0, r1
	ldr r2, _021DAABC ; =0x021DFEE0
	ldr r1, [r6, #0x4c]
	add r2, r2, r0
	mov r0, #0x18
	mul r0, r1
	add r5, r2, r0
	str r5, [sp]
	add r7, sp, #4
_021DAA54:
	ldr r0, [r5]
	add r1, r7, #0
	bl MOD85_021DA7C8
	cmp r0, #1
	bne _021DAAA4
	ldr r0, [sp]
	lsl r1, r4, #3
	add r0, r0, r1
	ldr r1, [r0, #4]
	mov r0, #0x56
	lsl r0, r0, #2
	str r1, [r6, r0]
	ldr r0, [r6, r0]
	cmp r0, #0
	beq _021DAA80
	cmp r0, #1
	beq _021DAA8C
	cmp r0, #2
	beq _021DAA98
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_021DAA80:
	ldr r0, _021DAAC0 ; =0x00000488
	add sp, #8
	ldr r1, [r6, r0]
	add r1, r1, #1
	str r1, [r6, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021DAA8C:
	ldr r0, _021DAAC4 ; =0x00000484
	add sp, #8
	ldr r1, [r6, r0]
	add r1, r1, #1
	str r1, [r6, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021DAA98:
	ldr r0, _021DAAC8 ; =0x0000048C
	add sp, #8
	ldr r1, [r6, r0]
	add r1, r1, #1
	str r1, [r6, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021DAAA4:
	add r4, r4, #1
	add r5, #8
	cmp r4, #3
	blo _021DAA54
	mov r0, #0x56
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r6, r0]
	bl ErrorHandling
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DAABC: .word MOD85_021DFEE0
_021DAAC0: .word 0x00000488
_021DAAC4: .word 0x00000484
_021DAAC8: .word 0x0000048C
	thumb_func_end MOD85_021DAA2C

	thumb_func_start MOD85_021DAACC
MOD85_021DAACC: ; 0x021DAACC
	push {r4, lr}
	add r1, r0, #0
	add r1, #0x88
	ldr r1, [r1]
	lsl r2, r1, #2
	ldr r1, _021DAAEC ; =0x021DFC94
	ldr r4, [r1, r2]
	bl MOD85_021DA7B8
	cmp r0, r4
	bhs _021DAAE6
	mov r0, #1
	pop {r4, pc}
_021DAAE6:
	mov r0, #0
	pop {r4, pc}
	nop
_021DAAEC: .word MOD85_021DFC94
	thumb_func_end MOD85_021DAACC

	thumb_func_start MOD85_021DAAF0
MOD85_021DAAF0: ; 0x021DAAF0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r1, r4, #0
	add r1, #0x88
	ldr r1, [r1]
	ldr r2, _021DABE4 ; =0x021DFD84
	lsl r1, r1, #4
	add r5, r2, r1
	bl MOD85_021DA7B8
	str r0, [sp]
	mov r0, #0
	str r0, [r4, #0x74]
	add r0, r4, #0
	bl MOD85_021DAACC
	cmp r0, #0
	bne _021DAB7A
	ldr r0, _021DABE8 ; =0x00000474
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, #0x50]
	cmp r1, #5
	bhi _021DAB6A
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021DAB2E: ; jump table
	.short _021DAB3A - _021DAB2E - 2 ; case 0
	.short _021DAB3A - _021DAB2E - 2 ; case 1
	.short _021DAB3A - _021DAB2E - 2 ; case 2
	.short _021DAB52 - _021DAB2E - 2 ; case 3
	.short _021DAB52 - _021DAB2E - 2 ; case 4
	.short _021DAB52 - _021DAB2E - 2 ; case 5
_021DAB3A:
	mov r1, #2
	ldr r2, [r4, #0x74]
	lsl r1, r1, #8
	orr r1, r2
	str r1, [r4, #0x74]
	add r1, r0, #0
	add r1, #0x44
	ldr r1, [r4, r1]
	add r0, #0x44
	add r1, r1, #1
	str r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021DAB52:
	mov r1, #1
	ldr r2, [r4, #0x74]
	lsl r1, r1, #8
	orr r1, r2
	str r1, [r4, #0x74]
	add r1, r0, #0
	add r1, #0x40
	ldr r1, [r4, r1]
	add r0, #0x40
	add r1, r1, #1
	str r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021DAB6A:
	bl ErrorHandling
	mov r0, #2
	ldr r1, [r4, #0x74]
	lsl r0, r0, #8
	orr r0, r1
	str r0, [r4, #0x74]
	pop {r3, r4, r5, pc}
_021DAB7A:
	ldr r0, [r5]
	add r1, sp, #0
	bl MOD85_021DA7C8
	cmp r0, #1
	bne _021DAB98
	ldr r1, [r4, #0x74]
	mov r0, #4
	orr r0, r1
	str r0, [r4, #0x74]
	ldr r0, _021DABEC ; =0x0000049C
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021DAB98:
	ldr r0, [r5, #4]
	add r1, sp, #0
	bl MOD85_021DA7C8
	cmp r0, #1
	bne _021DABB6
	ldr r1, [r4, #0x74]
	mov r0, #0x40
	orr r0, r1
	str r0, [r4, #0x74]
	ldr r0, _021DABF0 ; =0x000004AC
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021DABB6:
	ldr r0, [r5, #4]
	add r1, sp, #0
	bl MOD85_021DA7C8
	cmp r0, #1
	bne _021DABD4
	ldr r1, [r4, #0x74]
	mov r0, #0x10
	orr r0, r1
	str r0, [r4, #0x74]
	ldr r0, _021DABF4 ; =0x000004A4
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021DABD4:
	mov r0, #1
	str r0, [r4, #0x74]
	ldr r0, _021DABF8 ; =0x00000494
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	pop {r3, r4, r5, pc}
	nop
_021DABE4: .word MOD85_021DFD84
_021DABE8: .word 0x00000474
_021DABEC: .word 0x0000049C
_021DABF0: .word 0x000004AC
_021DABF4: .word 0x000004A4
_021DABF8: .word 0x00000494
	thumb_func_end MOD85_021DAAF0

	thumb_func_start MOD85_021DABFC
MOD85_021DABFC: ; 0x021DABFC
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DA7B8
	add r4, #0x88
	ldr r1, [r4]
	lsl r2, r1, #2
	ldr r1, _021DAC1C ; =0x021DFCDC
	ldr r1, [r1, r2]
	cmp r0, r1
	bhs _021DAC16
	mov r0, #1
	pop {r4, pc}
_021DAC16:
	mov r0, #0
	pop {r4, pc}
	nop
_021DAC1C: .word MOD85_021DFCDC
	thumb_func_end MOD85_021DABFC

	thumb_func_start MOD85_021DAC20
MOD85_021DAC20: ; 0x021DAC20
	push {r4, lr}
	add r4, r0, #0
	bl MOD85_021DA7B8
	add r4, #0x88
	ldr r1, [r4]
	lsl r2, r1, #2
	ldr r1, _021DAC40 ; =0x021DFC64
	ldr r1, [r1, r2]
	cmp r0, r1
	bhs _021DAC3A
	mov r0, #1
	pop {r4, pc}
_021DAC3A:
	mov r0, #0
	pop {r4, pc}
	nop
_021DAC40: .word MOD85_021DFC64
	thumb_func_end MOD85_021DAC20

	thumb_func_start MOD85_021DAC44
MOD85_021DAC44: ; 0x021DAC44
	push {r4, lr}
	ldr r4, [r0, #0x18]
	bl MOD85_021DA7B8
	cmp r0, r4
	bhs _021DAC54
	mov r0, #1
	pop {r4, pc}
_021DAC54:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021DAC44

	thumb_func_start MOD85_021DAC58
MOD85_021DAC58: ; 0x021DAC58
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	ldr r4, [r5, #0x18]
	bl MOD85_021DA7B8
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	ldr r1, _021DACA8 ; =0x021DFCF4
	lsl r0, r0, #3
	add r6, r1, r0
	ldr r0, [r5, #0x28]
	cmp r0, #2
	bne _021DAC7C
	sub r4, #0xa
	b _021DAC9A
_021DAC7C:
	ldr r0, [r6]
	add r1, sp, #0
	bl MOD85_021DA7C8
	cmp r0, #1
	bne _021DAC8C
	sub r4, #0xa
	b _021DAC9A
_021DAC8C:
	ldr r0, [r6, #4]
	add r1, sp, #0
	bl MOD85_021DA7C8
	cmp r0, #1
	bne _021DAC9A
	sub r4, r4, #5
_021DAC9A:
	cmp r4, #0
	bge _021DACA0
	mov r4, #0
_021DACA0:
	str r4, [r5, #0x18]
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_021DACA8: .word MOD85_021DFCF4
	thumb_func_end MOD85_021DAC58

	thumb_func_start MOD85_021DACAC
MOD85_021DACAC: ; 0x021DACAC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r4, [r5, #0x18]
	bl MOD85_021DA7B8
	str r0, [sp]
	add r5, #0x88
	ldr r1, [r5]
	mov r0, #0x90
	mul r0, r1
	ldr r2, _021DAD08 ; =0x021E0240
	mov r1, #0
	add r5, r2, r0
	add r2, r5, #0
_021DACC8:
	ldr r0, [r2]
	cmp r4, r0
	blo _021DACF8
	lsl r4, r1, #4
	add r0, r5, r4
	ldr r0, [r0, #4]
	add r1, sp, #0
	bl MOD85_021DA7C8
	cmp r0, #1
	bne _021DACE2
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DACE2:
	add r0, r5, r4
	ldr r0, [r0, #8]
	add r1, sp, #0
	bl MOD85_021DA7C8
	cmp r0, #1
	bne _021DACF4
	mov r0, #0
	pop {r3, r4, r5, pc}
_021DACF4:
	mov r0, #2
	pop {r3, r4, r5, pc}
_021DACF8:
	add r1, r1, #1
	add r2, #0x10
	cmp r1, #9
	blt _021DACC8
	bl ErrorHandling
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DAD08: .word MOD85_021E0240
	thumb_func_end MOD85_021DACAC

	thumb_func_start MOD85_021DAD0C
MOD85_021DAD0C: ; 0x021DAD0C
	push {r4, lr}
	add r4, r0, #0
	bl LCRandom
	mov r1, #6
	bl _s32_div_f
	str r1, [r4, #0x34]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DAD0C

	thumb_func_start MOD85_021DAD20
MOD85_021DAD20: ; 0x021DAD20
	push {r4, lr}
	mov r1, #0x12
	lsl r1, r1, #4
	add r4, r0, r1
	mov r1, #0
	str r1, [r4]
	str r1, [r4, #4]
	str r0, [r4, #0xc]
	ldr r0, _021DAD40 ; =MOD85_021DAD70
	add r1, r4, #0
	mov r2, #0x8a
	bl FUN_0200CA44
	str r0, [r4, #0x10]
	pop {r4, pc}
	nop
_021DAD40: .word MOD85_021DAD70
	thumb_func_end MOD85_021DAD20

	thumb_func_start MOD85_021DAD44
MOD85_021DAD44: ; 0x021DAD44
	mov r1, #0x13
	lsl r1, r1, #4
	ldr r3, _021DAD50 ; =FUN_0200CAB4
	ldr r0, [r0, r1]
	bx r3
	nop
_021DAD50: .word FUN_0200CAB4
	thumb_func_end MOD85_021DAD44

	thumb_func_start MOD85_021DAD54
MOD85_021DAD54: ; 0x021DAD54
	mov r1, #0x49
	lsl r1, r1, #2
	mov r3, #0
	str r3, [r0, r1]
	add r2, r1, #4
	str r3, [r0, r2]
	mov r2, #1
	sub r1, r1, #4
	str r2, [r0, r1]
	bx lr
	thumb_func_end MOD85_021DAD54

	thumb_func_start MOD85_021DAD68
MOD85_021DAD68: ; 0x021DAD68
	mov r1, #0x49
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr
	thumb_func_end MOD85_021DAD68

	thumb_func_start MOD85_021DAD70
MOD85_021DAD70: ; 0x021DAD70
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5]
	ldr r4, [r5, #0xc]
	cmp r0, #3
	bhi _021DAE5E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DAD88: ; jump table
	.short _021DAE5E - _021DAD88 - 2 ; case 0
	.short _021DAD90 - _021DAD88 - 2 ; case 1
	.short _021DAD9E - _021DAD88 - 2 ; case 2
	.short _021DADC0 - _021DAD88 - 2 ; case 3
_021DAD90:
	add r0, r5, #0
	bl MOD85_021DAE70
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DAD9E:
	ldr r0, [r5, #0x14]
	cmp r0, #0
	beq _021DADAC
	bl MOD85_021DB7B8
	cmp r0, #1
	bne _021DAE5E
_021DADAC:
	ldr r0, [r5, #0x18]
	cmp r0, #0
	beq _021DADBA
	bl MOD85_021DB7B8
	cmp r0, #1
	bne _021DAE5E
_021DADBA:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
_021DADC0:
	mov r0, #1
	lsl r0, r0, #0xa
	bl MOD85_021DBD54
	cmp r0, #0
	bne _021DADD2
	ldr r0, [r4, #0x64]
	cmp r0, #0
	bne _021DAE20
_021DADD2:
	ldr r0, _021DAE60 ; =0x0000062D
	bl FUN_020054C8
	ldr r1, [r4, #0x60]
	ldr r0, [r4, #0x64]
	add r1, r1, r0
	ldr r0, _021DAE64 ; =0x0000C350
	str r1, [r4, #0x60]
	cmp r1, r0
	blt _021DADE8
	str r0, [r4, #0x60]
_021DADE8:
	ldr r0, [r4, #8]
	cmp r0, #1
	bne _021DADF6
	ldr r1, [r4, #0x14]
	ldr r0, [r4, #0x64]
	add r0, r1, r0
	str r0, [r4, #0x14]
_021DADF6:
	mov r0, #0
	str r0, [r4, #0x64]
	ldr r0, [r5, #0x14]
	cmp r0, #0
	beq _021DAE08
	bl FUN_02064520
	mov r0, #0
	str r0, [r5, #0x14]
_021DAE08:
	ldr r0, [r5, #0x18]
	cmp r0, #0
	beq _021DAE16
	bl FUN_02064520
	mov r0, #0
	str r0, [r5, #0x18]
_021DAE16:
	mov r0, #1
	str r0, [r5, #4]
	mov r0, #0
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DAE20:
	ldr r1, _021DAE68 ; =0x021C48B8
	mov r0, #3
	ldr r2, [r1, #0x44]
	ldr r1, _021DAE6C ; =0x00000C03
	tst r1, r2
	beq _021DAE2E
	mov r0, #1
_021DAE2E:
	ldr r1, [r5, #8]
	add r1, r1, #1
	str r1, [r5, #8]
	tst r0, r1
	bne _021DAE5E
	ldr r0, [r4, #0x64]
	sub r0, r0, #1
	str r0, [r4, #0x64]
	ldr r0, [r4, #0x60]
	add r1, r0, #1
	ldr r0, _021DAE64 ; =0x0000C350
	str r1, [r4, #0x60]
	cmp r1, r0
	blt _021DAE4C
	str r0, [r4, #0x60]
_021DAE4C:
	ldr r0, _021DAE60 ; =0x0000062D
	bl FUN_020054C8
	ldr r0, [r4, #8]
	cmp r0, #1
	bne _021DAE5E
	ldr r0, [r4, #0x14]
	add r0, r0, #1
	str r0, [r4, #0x14]
_021DAE5E:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DAE60: .word 0x0000062D
_021DAE64: .word 0x0000C350
_021DAE68: .word 0x021C48B8
_021DAE6C: .word 0x00000C03
	thumb_func_end MOD85_021DAD70

	thumb_func_start MOD85_021DAE70
MOD85_021DAE70: ; 0x021DAE70
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r7, [r5, #0xc]
	ldr r6, [r7, #0x48]
	cmp r6, #0
	bne _021DAE80
	bl ErrorHandling
_021DAE80:
	mov r4, #0
_021DAE82:
	mov r0, #1
	tst r0, r6
	beq _021DAEB4
	ldr r0, [r5, #0x14]
	cmp r0, #0
	bne _021DAE9C
	ldr r2, [r7, #0x64]
	add r0, r7, #0
	add r1, r4, #0
	bl MOD85_021DB784
	str r0, [r5, #0x14]
	b _021DAEB4
_021DAE9C:
	ldr r0, [r5, #0x18]
	cmp r0, #0
	bne _021DAEB0
	ldr r2, [r7, #0x64]
	add r0, r7, #0
	add r1, r4, #0
	bl MOD85_021DB784
	str r0, [r5, #0x18]
	b _021DAEB4
_021DAEB0:
	bl ErrorHandling
_021DAEB4:
	add r4, r4, #1
	lsr r6, r6, #1
	cmp r4, #5
	blt _021DAE82
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021DAE70

	thumb_func_start MOD85_021DAEC0
MOD85_021DAEC0: ; 0x021DAEC0
	push {r4, lr}
	mov r1, #0x4f
	lsl r1, r1, #2
	add r4, r0, r1
	mov r1, #0
	str r1, [r4]
	str r1, [r4, #4]
	str r0, [r4, #0x20]
	ldr r0, _021DAEE0 ; =MOD85_021DAF80
	add r1, r4, #0
	mov r2, #0x84
	bl FUN_0200CA44
	str r0, [r4, #0x24]
	pop {r4, pc}
	nop
_021DAEE0: .word MOD85_021DAF80
	thumb_func_end MOD85_021DAEC0

	thumb_func_start MOD85_021DAEE4
MOD85_021DAEE4: ; 0x021DAEE4
	mov r1, #0x16
	lsl r1, r1, #4
	ldr r3, _021DAEF0 ; =FUN_0200CAB4
	ldr r0, [r0, r1]
	bx r3
	nop
_021DAEF0: .word FUN_0200CAB4
	thumb_func_end MOD85_021DAEE4

	thumb_func_start MOD85_021DAEF4
MOD85_021DAEF4: ; 0x021DAEF4
	mov r2, #0x4f
	lsl r2, r2, #2
	add r2, r0, r2
	str r1, [r2]
	mov r0, #0
	str r0, [r2, #4]
	str r0, [r2, #8]
	str r0, [r2, #0x10]
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021DAEF4

	thumb_func_start MOD85_021DAF08
MOD85_021DAF08: ; 0x021DAF08
	mov r1, #0x51
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr
	thumb_func_end MOD85_021DAF08

	thumb_func_start MOD85_021DAF10
MOD85_021DAF10: ; 0x021DAF10
	push {r4, lr}
	mov r1, #0x52
	add r4, r0, #0
	mov r2, #0
	lsl r1, r1, #2
	str r2, [r4, r1]
	bl MOD85_021DD984
	mov r1, #0x5d
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD85_021DDB10
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD85_021DDCAC
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD85_021DDE10
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r4, r1]
	pop {r4, pc}
	thumb_func_end MOD85_021DAF10

	thumb_func_start MOD85_021DAF4C
MOD85_021DAF4C: ; 0x021DAF4C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x52
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, #0x2c
	ldr r0, [r4, r0]
	bl FUN_02064520
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02064520
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02064520
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	bl FUN_02064520
	pop {r4, pc}
	thumb_func_end MOD85_021DAF4C

	thumb_func_start MOD85_021DAF80
MOD85_021DAF80: ; 0x021DAF80
	push {r3, r4, r5, lr}
	ldr r4, _021DAF9C ; =0x021DEED0
	add r5, r1, #0
_021DAF86:
	ldr r1, [r5]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	ldr r1, [r5, #4]
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	blx r1
	cmp r0, #1
	beq _021DAF86
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DAF9C: .word MOD85_021DEED0
	thumb_func_end MOD85_021DAF80

	thumb_func_start MOD85_021DAFA0
MOD85_021DAFA0: ; 0x021DAFA0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0x18]
	bl MOD85_021DC4B4
	str r0, [r4, #0x28]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021DAFA0

	thumb_func_start MOD85_021DAFB8
MOD85_021DAFB8: ; 0x021DAFB8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl MOD85_021DC520
	cmp r0, #0
	bne _021DAFCA
	mov r0, #0
	pop {r4, pc}
_021DAFCA:
	ldr r0, [r4, #0x28]
	mov r1, #1
	bl MOD85_021DC4EC
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021DAFB8

	thumb_func_start MOD85_021DAFDC
MOD85_021DAFDC: ; 0x021DAFDC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl MOD85_021DC520
	cmp r0, #0
	bne _021DAFEE
	mov r0, #0
	pop {r4, pc}
_021DAFEE:
	ldr r0, [r4, #0x28]
	mov r1, #5
	bl MOD85_021DC4EC
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021DAFDC

	thumb_func_start MOD85_021DB004
MOD85_021DB004: ; 0x021DB004
	mov r0, #0
	bx lr
	thumb_func_end MOD85_021DB004

	thumb_func_start MOD85_021DB008
MOD85_021DB008: ; 0x021DB008
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	mov r1, #4
	bl MOD85_021DC4EC
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB008

	thumb_func_start MOD85_021DB020
MOD85_021DB020: ; 0x021DB020
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl MOD85_021DC520
	cmp r0, #1
	bne _021DB03E
	ldr r0, [r4, #0x28]
	bl FUN_02064520
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DB03E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB020

	thumb_func_start MOD85_021DB044
MOD85_021DB044: ; 0x021DB044
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	mov r1, #2
	bl MOD85_021DC4EC
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB044

	thumb_func_start MOD85_021DB05C
MOD85_021DB05C: ; 0x021DB05C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl MOD85_021DC520
	cmp r0, #1
	bne _021DB082
	ldr r0, [r4, #0x20]
	bl MOD85_021DCBE0
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0x1c]
	bl MOD85_021DCEC0
	str r0, [r4, #0x30]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DB082:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB05C

	thumb_func_start MOD85_021DB088
MOD85_021DB088: ; 0x021DB088
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	bl MOD85_021DCF0C
	cmp r0, #1
	bne _021DB0AC
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl MOD85_021DCEF8
	ldr r0, [r4, #0x28]
	mov r1, #1
	bl MOD85_021DC500
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DB0AC:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021DB088

	thumb_func_start MOD85_021DB0B0
MOD85_021DB0B0: ; 0x021DB0B0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	bl MOD85_021DCF0C
	cmp r0, #1
	bne _021DB0CE
	ldr r0, [r4, #0x2c]
	bl FUN_02064520
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DB0CE:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB0B0

	thumb_func_start MOD85_021DB0D4
MOD85_021DB0D4: ; 0x021DB0D4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x20]
	bl MOD85_021DCBE0
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x30]
	mov r1, #2
	bl MOD85_021DCEF8
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB0D4

	thumb_func_start MOD85_021DB0F4
MOD85_021DB0F4: ; 0x021DB0F4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	bl MOD85_021DCF0C
	cmp r0, #1
	bne _021DB124
	ldr r0, [r4, #0x30]
	bl FUN_02064520
	ldr r0, [r4, #0x2c]
	bl FUN_02064520
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl MOD85_021DC500
	ldr r0, [r4, #0x28]
	mov r1, #3
	bl MOD85_021DC4EC
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DB124:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021DB0F4

	thumb_func_start MOD85_021DB128
MOD85_021DB128: ; 0x021DB128
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl MOD85_021DC520
	cmp r0, #1
	bne _021DB144
	ldr r0, [r4, #0x28]
	mov r1, #4
	bl MOD85_021DC4EC
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DB144:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021DB128

	thumb_func_start MOD85_021DB148
MOD85_021DB148: ; 0x021DB148
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl MOD85_021DC520
	cmp r0, #1
	bne _021DB166
	ldr r0, [r4, #0x28]
	bl FUN_02064520
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DB166:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB148

	thumb_func_start MOD85_021DB16C
MOD85_021DB16C: ; 0x021DB16C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	mov r1, #3
	bl MOD85_021DCEF8
	ldr r0, [r4, #0x20]
	bl MOD85_021DD54C
	str r0, [r4, #0x34]
	mov r0, #0
	str r0, [r4, #0x10]
	ldr r1, [r4, #4]
	add r1, r1, #1
	str r1, [r4, #4]
	pop {r4, pc}
	thumb_func_end MOD85_021DB16C

	thumb_func_start MOD85_021DB18C
MOD85_021DB18C: ; 0x021DB18C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	cmp r0, #0x30
	blt _021DB1B2
	mov r0, #0
	str r0, [r4, #0x10]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0x23
	bl FUN_02005578
	ldr r0, [r4, #0x30]
	mov r1, #4
	bl MOD85_021DCEF8
_021DB1B2:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB18C

	thumb_func_start MOD85_021DB1B8
MOD85_021DB1B8: ; 0x021DB1B8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x34]
	bl MOD85_021DD578
	cmp r0, #1
	bne _021DB1E2
	ldr r0, [r4, #0x30]
	mov r1, #3
	bl MOD85_021DCEF8
	ldr r0, [r4, #0x34]
	bl FUN_02064520
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	str r0, [r4, #0x10]
	mov r0, #1
	str r0, [r4, #8]
_021DB1E2:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB1B8

	thumb_func_start MOD85_021DB1E8
MOD85_021DB1E8: ; 0x021DB1E8
	push {r3, lr}
	ldr r1, [r0, #0x20]
	ldr r3, _021DB210 ; =0x021DEF04
	ldr r2, [r1, #0x34]
	mov r1, #0x18
	mul r1, r2
	add r2, r3, r1
	ldr r1, [r0, #4]
	add r1, r1, #1
	str r1, [r0, #4]
	mov r1, #0
	str r1, [r0, #0x14]
	lsl r1, r1, #2
	add r1, r2, r1
	ldr r0, [r0, #0x30]
	ldr r1, [r1, #0xc]
	bl MOD85_021DCEF8
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_021DB210: .word MOD85_021DEF04
	thumb_func_end MOD85_021DB1E8

	thumb_func_start MOD85_021DB214
MOD85_021DB214: ; 0x021DB214
	push {r3, r4, r5, lr}
	ldr r2, [r0, #0x20]
	mov r1, #0
	add r4, r1, #0
	add r5, r2, #0
_021DB21E:
	ldr r3, [r5, #0x7c]
	cmp r3, #1
	beq _021DB226
	add r1, r1, #1
_021DB226:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _021DB21E
	ldr r3, [r0, #0x14]
	cmp r3, #2
	bge _021DB250
	cmp r3, r1
	beq _021DB250
	ldr r3, [r2, #0x34]
	mov r2, #0x18
	ldr r4, _021DB254 ; =0x021DEF04
	str r1, [r0, #0x14]
	mul r2, r3
	add r2, r4, r2
	lsl r1, r1, #2
	add r1, r2, r1
	ldr r0, [r0, #0x30]
	ldr r1, [r1, #0xc]
	bl MOD85_021DCEF8
_021DB250:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DB254: .word MOD85_021DEF04
	thumb_func_end MOD85_021DB214

	thumb_func_start MOD85_021DB258
MOD85_021DB258: ; 0x021DB258
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	mov r1, #3
	bl MOD85_021DCEF8
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB258

	thumb_func_start MOD85_021DB270
MOD85_021DB270: ; 0x021DB270
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x20]
	bl MOD85_021DAF4C
	ldr r0, [r4, #0x20]
	bl MOD85_021DCBE0
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x30]
	mov r1, #2
	bl MOD85_021DCEF8
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021DB270

	thumb_func_start MOD85_021DB294
MOD85_021DB294: ; 0x021DB294
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	bl MOD85_021DCF0C
	cmp r0, #1
	bne _021DB2C4
	ldr r0, [r4, #0x30]
	bl FUN_02064520
	ldr r0, [r4, #0x2c]
	bl FUN_02064520
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl MOD85_021DC500
	ldr r0, [r4, #0x28]
	mov r1, #3
	bl MOD85_021DC4EC
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DB2C4:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021DB294

	thumb_func_start MOD85_021DB2C8
MOD85_021DB2C8: ; 0x021DB2C8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl MOD85_021DC520
	cmp r0, #1
	bne _021DB2F8
	ldr r0, [r4, #0x20]
	bl MOD85_021DDA30
	ldr r0, [r4, #0x20]
	bl MOD85_021DDBBC
	ldr r0, [r4, #0x20]
	mov r1, #0
	bl MOD85_021DDF40
	ldr r0, [r4, #0x20]
	mov r1, #1
	bl MOD85_021DDF40
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DB2F8:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021DB2C8

	thumb_func_start MOD85_021DB2FC
MOD85_021DB2FC: ; 0x021DB2FC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	cmp r0, #0x2d
	blt _021DB31C
	mov r0, #0
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x28]
	mov r1, #4
	bl MOD85_021DC4EC
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DB31C:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021DB2FC

	thumb_func_start MOD85_021DB320
MOD85_021DB320: ; 0x021DB320
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl MOD85_021DC520
	cmp r0, #1
	bne _021DB33E
	ldr r0, [r4, #0x28]
	bl FUN_02064520
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DB33E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB320

	thumb_func_start MOD85_021DB344
MOD85_021DB344: ; 0x021DB344
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	mov r1, #4
	bl MOD85_021DCEF8
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB344

	thumb_func_start MOD85_021DB360
MOD85_021DB360: ; 0x021DB360
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	mov r1, #8
	bl MOD85_021DCEF8
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB360

	thumb_func_start MOD85_021DB37C
MOD85_021DB37C: ; 0x021DB37C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	mov r1, #6
	bl MOD85_021DC4EC
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #1
	str r0, [r4, #8]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB37C

	thumb_func_start MOD85_021DB398
MOD85_021DB398: ; 0x021DB398
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x20]
	bl MOD85_021DCBE0
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x30]
	mov r1, #2
	bl MOD85_021DCEF8
	mov r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB398

	thumb_func_start MOD85_021DB3BC
MOD85_021DB3BC: ; 0x021DB3BC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	bl MOD85_021DCF0C
	cmp r0, #1
	bne _021DB3F0
	ldr r0, [r4, #0x2c]
	bl FUN_02064520
	ldr r0, [r4, #0x30]
	bl FUN_02064520
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl MOD85_021DC500
	ldr r0, [r4, #0x28]
	mov r1, #3
	bl MOD85_021DC4EC
	mov r0, #0
	str r0, [r4, #0x10]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DB3F0:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021DB3BC

	thumb_func_start MOD85_021DB3F4
MOD85_021DB3F4: ; 0x021DB3F4
	push {r3, lr}
	ldr r1, [r0, #0x10]
	add r1, r1, #1
	str r1, [r0, #0x10]
	cmp r1, #0x1e
	blt _021DB412
	mov r1, #0
	str r1, [r0, #0x10]
	ldr r1, [r0, #4]
	add r1, r1, #1
	str r1, [r0, #4]
	ldr r0, [r0, #0x28]
	mov r1, #2
	bl MOD85_021DC4EC
_021DB412:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB3F4

	thumb_func_start MOD85_021DB418
MOD85_021DB418: ; 0x021DB418
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl MOD85_021DC520
	cmp r0, #1
	bne _021DB442
	ldr r0, [r4, #0x20]
	bl MOD85_021DCBE0
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0x1c]
	bl MOD85_021DCEC0
	str r0, [r4, #0x30]
	mov r0, #0
	str r0, [r4, #0xc]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DB442:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB418

	thumb_func_start MOD85_021DB448
MOD85_021DB448: ; 0x021DB448
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	bl MOD85_021DCF0C
	cmp r0, #1
	bne _021DB46C
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl MOD85_021DCEF8
	ldr r0, [r4, #0x28]
	mov r1, #1
	bl MOD85_021DC500
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DB46C:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021DB448

	thumb_func_start MOD85_021DB470
MOD85_021DB470: ; 0x021DB470
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	bl MOD85_021DCF0C
	cmp r0, #1
	bne _021DB48E
	ldr r0, [r4, #0x2c]
	bl FUN_02064520
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DB48E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB470

	thumb_func_start MOD85_021DB494
MOD85_021DB494: ; 0x021DB494
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	mov r1, #0x61
	add r5, r0, #0
	lsl r1, r1, #2
	add r4, r5, r1
	mov r1, #3
	mov r2, #0
	str r5, [r4]
	bl MOD85_021D8144
	add r1, sp, #0
	add r6, r0, #0
	bl FUN_020B0138
	ldr r0, [sp]
	mov r1, #1
	add r2, r4, #4
	bl MOD85_021DB604
	add r2, r4, #0
	ldr r0, [sp]
	mov r1, #2
	add r2, #0xa4
	bl MOD85_021DB604
	add r2, r4, #0
	ldr r0, [sp]
	mov r1, #3
	add r2, #0xc4
	bl MOD85_021DB604
	add r2, r4, #0
	ldr r0, [sp]
	mov r1, #3
	add r2, #0xe4
	bl MOD85_021DB604
	mov r2, #0x41
	lsl r2, r2, #2
	ldr r0, [sp]
	mov r1, #4
	add r2, r4, r2
	bl MOD85_021DB604
	mov r2, #0x49
	lsl r2, r2, #2
	ldr r0, [sp]
	mov r1, #4
	add r2, r4, r2
	bl MOD85_021DB604
	add r0, r6, #0
	bl FreeToHeap
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl MOD85_021D8144
	add r1, sp, #0
	add r6, r0, #0
	bl FUN_020B0138
	add r2, r4, #0
	ldr r0, [sp]
	mov r1, #0
	add r2, #0x24
	bl MOD85_021DB604
	add r0, r6, #0
	bl FreeToHeap
	add r0, r5, #0
	mov r1, #6
	mov r2, #0
	bl MOD85_021D8144
	add r1, sp, #0
	add r6, r0, #0
	bl FUN_020B0138
	add r2, r4, #0
	ldr r0, [sp]
	mov r1, #0
	add r2, #0x44
	bl MOD85_021DB604
	add r0, r6, #0
	bl FreeToHeap
	add r0, r5, #0
	mov r1, #7
	mov r2, #0
	bl MOD85_021D8144
	add r1, sp, #0
	add r6, r0, #0
	bl FUN_020B0138
	add r2, r4, #0
	ldr r0, [sp]
	mov r1, #0
	add r2, #0x64
	bl MOD85_021DB604
	add r0, r6, #0
	bl FreeToHeap
	add r0, r5, #0
	mov r1, #0x4a
	mov r2, #0
	bl MOD85_021D8144
	add r1, sp, #0
	add r6, r0, #0
	bl FUN_020B0138
	mov r2, #0x51
	lsl r2, r2, #2
	ldr r0, [sp]
	mov r1, #0
	add r2, r4, r2
	bl MOD85_021DB604
	add r0, r6, #0
	bl FreeToHeap
	add r0, r5, #0
	mov r1, #0x4b
	mov r2, #0
	bl MOD85_021D8144
	add r1, sp, #0
	add r6, r0, #0
	bl FUN_020B0138
	mov r2, #0x59
	lsl r2, r2, #2
	ldr r0, [sp]
	mov r1, #0
	add r2, r4, r2
	bl MOD85_021DB604
	mov r2, #0x61
	lsl r2, r2, #2
	ldr r0, [sp]
	mov r1, #0
	add r2, r4, r2
	bl MOD85_021DB604
	add r0, r6, #0
	bl FreeToHeap
	add r0, r5, #0
	mov r1, #0x4c
	mov r2, #0
	bl MOD85_021D8144
	add r1, sp, #0
	add r5, r0, #0
	bl FUN_020B0138
	mov r2, #0x69
	lsl r2, r2, #2
	ldr r0, [sp]
	mov r1, #0
	add r2, r4, r2
	bl MOD85_021DB604
	mov r2, #0x71
	lsl r2, r2, #2
	ldr r0, [sp]
	mov r1, #0
	add r2, r4, r2
	bl MOD85_021DB604
	add r0, r5, #0
	bl FreeToHeap
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD85_021DB494

	thumb_func_start MOD85_021DB600
MOD85_021DB600: ; 0x021DB600
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021DB600

	thumb_func_start MOD85_021DB604
MOD85_021DB604: ; 0x021DB604
	ldr r3, [r0, #0xc]
	lsl r0, r1, #5
	add r3, r3, r0
	mov r1, #0
_021DB60C:
	ldrh r0, [r3]
	add r1, r1, #1
	add r3, r3, #2
	strh r0, [r2]
	add r2, r2, #2
	cmp r1, #0x10
	blt _021DB60C
	bx lr
	thumb_func_end MOD85_021DB604

	thumb_func_start MOD85_021DB61C
MOD85_021DB61C: ; 0x021DB61C
	push {r0, r1, r2, r3}
	push {r3, r4, r5, r6}
	add r1, r2, #0
	add r0, r3, #0
	add r2, sp, #0x10
	add r3, sp, #0x14
	cmp r1, #0x10
	bls _021DB62E
	mov r1, #0x10
_021DB62E:
	ldrh r4, [r2]
	ldrh r3, [r3]
	lsl r2, r4, #0x16
	lsr r6, r2, #0x1b
	lsl r2, r4, #0x1b
	lsr r5, r2, #0x1b
	lsl r2, r4, #0x11
	lsl r4, r3, #0x11
	lsr r2, r2, #0x1b
	lsr r4, r4, #0x1b
	sub r4, r4, r2
	mul r4, r1
	asr r4, r4, #4
	add r2, r2, r4
	lsl r4, r2, #0xa
	lsl r2, r3, #0x1b
	lsl r3, r3, #0x16
	lsr r3, r3, #0x1b
	lsr r2, r2, #0x1b
	sub r3, r3, r6
	sub r2, r2, r5
	mul r2, r1
	mul r3, r1
	asr r1, r3, #4
	asr r2, r2, #4
	add r1, r6, r1
	add r2, r5, r2
	lsl r1, r1, #5
	orr r1, r2
	orr r1, r4
	strh r1, [r0]
	pop {r3, r4, r5, r6}
	add sp, #0x10
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021DB61C

	thumb_func_start MOD85_021DB674
MOD85_021DB674: ; 0x021DB674
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	str r2, [sp]
	add r6, r3, #0
	mov r7, #0
_021DB680:
	ldrh r0, [r5]
	ldrh r1, [r4]
	ldr r2, [sp]
	add r3, r6, #0
	bl MOD85_021DB61C
	add r7, r7, #1
	add r6, r6, #2
	add r4, r4, #2
	add r5, r5, #2
	cmp r7, #0x10
	blt _021DB680
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB674

	thumb_func_start MOD85_021DB69C
MOD85_021DB69C: ; 0x021DB69C
	push {r4, lr}
	add r4, r2, #0
	lsl r0, r1, #0x18
	add r1, r3, #0
	lsl r3, r4, #0x15
	lsr r0, r0, #0x18
	mov r2, #0x20
	lsr r3, r3, #0x10
	bl FUN_02017FB4
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB69C

	thumb_func_start MOD85_021DB6B4
MOD85_021DB6B4: ; 0x021DB6B4
	push {r4, lr}
	add r3, r1, #0
	lsl r4, r3, #2
	ldr r2, _021DB6D0 ; =0x021E05C0
	lsl r3, r3, #5
	ldr r2, [r2, r4]
	mov r4, #0x8a
	lsl r4, r4, #2
	add r4, r0, r4
	mov r1, #1
	add r3, r4, r3
	bl MOD85_021DB69C
	pop {r4, pc}
	.align 2, 0
_021DB6D0: .word MOD85_021E05C0
	thumb_func_end MOD85_021DB6B4

	thumb_func_start MOD85_021DB6D4
MOD85_021DB6D4: ; 0x021DB6D4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r2, #0x61
	lsl r2, r2, #2
	ldr r0, _021DB710 ; =0x021E05C0
	lsl r4, r1, #2
	ldr r6, [r0, r4]
	add r0, r2, #0
	add r3, r7, r2
	add r0, #0x60
	add r4, r3, r0
	add r0, r3, #0
	sub r2, #0x40
	lsl r5, r1, #5
	add r1, r3, r2
	add r0, #0xa4
	add r0, r0, r5
	add r1, r1, r5
	mov r2, #0xa
	add r3, r4, r5
	bl MOD85_021DB674
	add r0, r7, #0
	mov r1, #1
	add r2, r6, #0
	add r3, r4, r5
	bl MOD85_021DB69C
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DB710: .word MOD85_021E05C0
	thumb_func_end MOD85_021DB6D4

	thumb_func_start MOD85_021DB714
MOD85_021DB714: ; 0x021DB714
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r2, #0x61
	lsl r2, r2, #2
	ldr r0, _021DB750 ; =0x021E05C0
	lsl r4, r1, #2
	ldr r6, [r0, r4]
	add r0, r2, #0
	add r3, r7, r2
	add r0, #0x60
	add r4, r3, r0
	add r0, r3, #0
	sub r2, #0x40
	lsl r5, r1, #5
	add r1, r3, r2
	add r0, #0xa4
	add r0, r0, r5
	add r1, r1, r5
	mov r2, #0xc
	add r3, r4, r5
	bl MOD85_021DB674
	add r0, r7, #0
	mov r1, #1
	add r2, r6, #0
	add r3, r4, r5
	bl MOD85_021DB69C
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DB750: .word MOD85_021E05C0
	thumb_func_end MOD85_021DB714

	thumb_func_start MOD85_021DB754
MOD85_021DB754: ; 0x021DB754
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_021DB75A:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD85_021DB6B4
	add r4, r4, #1
	cmp r4, #5
	blt _021DB75A
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB754

	thumb_func_start MOD85_021DB76C
MOD85_021DB76C: ; 0x021DB76C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_021DB772:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD85_021DB6D4
	add r4, r4, #1
	cmp r4, #5
	blt _021DB772
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB76C

	thumb_func_start MOD85_021DB784
MOD85_021DB784: ; 0x021DB784
	push {r4, lr}
	sub sp, #0x20
	add r4, sp, #0x14
	mov r3, #0
	str r3, [r4]
	str r3, [r4, #4]
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	str r3, [r4, #8]
	str r0, [sp, #0x10]
	add r1, sp, #8
	str r1, [sp]
	mov r1, #0x8f
	str r1, [sp, #4]
	ldr r1, _021DB7B0 ; =0x0000044C
	add r2, r4, #0
	ldr r0, [r0, r1]
	ldr r1, _021DB7B4 ; =0x021DEE0C
	bl FUN_020644E4
	add sp, #0x20
	pop {r4, pc}
	.align 2, 0
_021DB7B0: .word 0x0000044C
_021DB7B4: .word MOD85_021DEE0C
	thumb_func_end MOD85_021DB784

	thumb_func_start MOD85_021DB7B8
MOD85_021DB7B8: ; 0x021DB7B8
	push {r3, lr}
	bl FUN_02064738
	ldr r0, [r0, #0xc]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB7B8

	thumb_func_start MOD85_021DB7C4
MOD85_021DB7C4: ; 0x021DB7C4
	push {r4, lr}
	add r4, r1, #0
	bl FUN_0206475C
	ldr r1, [r0, #8]
	str r1, [r4, #0x1c]
	ldr r1, [r0]
	str r1, [r4, #0x10]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	mov r0, #0x61
	ldr r1, [r4, #0x1c]
	lsl r0, r0, #2
	add r0, r1, r0
	str r0, [r4, #0x20]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB7C4

	thumb_func_start MOD85_021DB7E8
MOD85_021DB7E8: ; 0x021DB7E8
	ldr r3, _021DB7F0 ; =MOD85_021DB6B4
	ldr r0, [r1, #0x1c]
	ldr r1, [r1, #0x10]
	bx r3
	.align 2, 0
_021DB7F0: .word MOD85_021DB6B4
	thumb_func_end MOD85_021DB7E8

	thumb_func_start MOD85_021DB7F4
MOD85_021DB7F4: ; 0x021DB7F4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	ldr r2, [r4, #0x10]
	ldr r0, _021DB958 ; =0x021E05C0
	lsl r1, r2, #2
	ldr r0, [r0, r1]
	lsl r5, r2, #5
	mov r1, #0x79
	ldr r2, [r4, #0x20]
	lsl r1, r1, #2
	add r6, r2, r1
	sub r1, #0xa0
	str r0, [sp]
	add r0, r2, #0
	add r1, r2, r1
	ldr r2, [r4]
	add r0, #0xa4
	cmp r2, #4
	bls _021DB81C
	b _021DB956
_021DB81C:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021DB828: ; jump table
	.short _021DB832 - _021DB828 - 2 ; case 0
	.short _021DB874 - _021DB828 - 2 ; case 1
	.short _021DB8D8 - _021DB828 - 2 ; case 2
	.short _021DB91A - _021DB828 - 2 ; case 3
	.short _021DB956 - _021DB828 - 2 ; case 4
_021DB832:
	mov r7, #1
	ldr r2, [r4, #0x18]
	lsl r7, r7, #0xe
	add r3, r2, r7
	lsl r2, r7, #2
	str r3, [r4, #0x18]
	cmp r3, r2
	ble _021DB844
	str r2, [r4, #0x18]
_021DB844:
	ldr r2, [r4, #0x18]
	asr r3, r2, #0xb
	lsr r3, r3, #0x14
	add r3, r2, r3
	asr r2, r3, #0xc
	cmp r2, #0x10
	bne _021DB858
	ldr r3, [r4]
	add r3, r3, #1
	str r3, [r4]
_021DB858:
	lsl r2, r2, #0x10
	add r0, r0, r5
	add r1, r1, r5
	lsr r2, r2, #0x10
	add r3, r6, r5
	bl MOD85_021DB674
	ldr r0, [r4, #0x1c]
	ldr r2, [sp]
	mov r1, #1
	add r3, r6, r5
	bl MOD85_021DB69C
	pop {r3, r4, r5, r6, r7, pc}
_021DB874:
	mov r2, #1
	ldr r3, [r4, #0x18]
	lsl r2, r2, #0xe
	sub r2, r3, r2
	str r2, [r4, #0x18]
	bpl _021DB884
	mov r2, #0
	str r2, [r4, #0x18]
_021DB884:
	ldr r2, [r4, #0x18]
	asr r3, r2, #0xb
	lsr r3, r3, #0x14
	add r3, r2, r3
	asr r2, r3, #0xc
	bne _021DB8BC
	ldr r3, [r4, #4]
	add r3, r3, #1
	str r3, [r4, #4]
	cmp r3, #4
	blt _021DB8B6
	ldr r3, [r4, #0x14]
	cmp r3, #0
	beq _021DB8AC
	ldr r3, [r4]
	add r3, r3, #1
	str r3, [r4]
	mov r3, #1
	str r3, [r4, #0xc]
	b _021DB8BC
_021DB8AC:
	mov r3, #4
	str r3, [r4]
	mov r3, #1
	str r3, [r4, #0xc]
	b _021DB8BC
_021DB8B6:
	ldr r3, [r4]
	sub r3, r3, #1
	str r3, [r4]
_021DB8BC:
	lsl r2, r2, #0x10
	add r0, r0, r5
	add r1, r1, r5
	lsr r2, r2, #0x10
	add r3, r6, r5
	bl MOD85_021DB674
	ldr r0, [r4, #0x1c]
	ldr r2, [sp]
	mov r1, #1
	add r3, r6, r5
	bl MOD85_021DB69C
	pop {r3, r4, r5, r6, r7, pc}
_021DB8D8:
	mov r7, #2
	ldr r2, [r4, #0x18]
	lsl r7, r7, #0xe
	add r3, r2, r7
	lsl r2, r7, #1
	str r3, [r4, #0x18]
	cmp r3, r2
	ble _021DB8EA
	str r2, [r4, #0x18]
_021DB8EA:
	ldr r2, [r4, #0x18]
	asr r3, r2, #0xb
	lsr r3, r3, #0x14
	add r3, r2, r3
	asr r2, r3, #0xc
	cmp r2, #0x10
	bne _021DB8FE
	ldr r3, [r4]
	add r3, r3, #1
	str r3, [r4]
_021DB8FE:
	lsl r2, r2, #0x10
	add r0, r0, r5
	add r1, r1, r5
	lsr r2, r2, #0x10
	add r3, r6, r5
	bl MOD85_021DB674
	ldr r0, [r4, #0x1c]
	ldr r2, [sp]
	mov r1, #1
	add r3, r6, r5
	bl MOD85_021DB69C
	pop {r3, r4, r5, r6, r7, pc}
_021DB91A:
	mov r2, #2
	ldr r3, [r4, #0x18]
	lsl r2, r2, #0xe
	sub r2, r3, r2
	str r2, [r4, #0x18]
	bpl _021DB92A
	mov r2, #0
	str r2, [r4, #0x18]
_021DB92A:
	ldr r2, [r4, #0x18]
	asr r3, r2, #0xb
	lsr r3, r3, #0x14
	add r3, r2, r3
	asr r2, r3, #0xc
	bne _021DB93C
	ldr r3, [r4]
	sub r3, r3, #1
	str r3, [r4]
_021DB93C:
	lsl r2, r2, #0x10
	add r0, r0, r5
	add r1, r1, r5
	lsr r2, r2, #0x10
	add r3, r6, r5
	bl MOD85_021DB674
	ldr r0, [r4, #0x1c]
	ldr r2, [sp]
	mov r1, #1
	add r3, r6, r5
	bl MOD85_021DB69C
_021DB956:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DB958: .word MOD85_021E05C0
	thumb_func_end MOD85_021DB7F4

	thumb_func_start MOD85_021DB95C
MOD85_021DB95C: ; 0x021DB95C
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	add r1, sp, #8
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	mov r0, #0x4d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021DB97A
	bl ErrorHandling
_021DB97A:
	str r4, [sp]
	mov r0, #0x8f
	str r0, [sp, #4]
	ldr r0, _021DB998 ; =0x0000044C
	ldr r1, _021DB99C ; =0x021DEE5C
	ldr r0, [r4, r0]
	add r2, sp, #8
	mov r3, #0
	bl FUN_020644E4
	mov r1, #0x4d
	lsl r1, r1, #2
	str r0, [r4, r1]
	add sp, #0x14
	pop {r3, r4, pc}
	.align 2, 0
_021DB998: .word 0x0000044C
_021DB99C: .word MOD85_021DEE5C
	thumb_func_end MOD85_021DB95C

	thumb_func_start MOD85_021DB9A0
MOD85_021DB9A0: ; 0x021DB9A0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x4d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021DB9BA
	bl FUN_02064520
	mov r0, #0x4d
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
_021DB9BA:
	add r0, r4, #0
	bl MOD85_021DB754
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DB9A0

	thumb_func_start MOD85_021DB9C4
MOD85_021DB9C4: ; 0x021DB9C4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	ldr r0, [r6, #4]
	ldr r1, _021DBADC ; =0x021DF094
	lsl r0, r0, #4
	add r4, r1, r0
	mov r0, #1
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, _021DBAE0 ; =0x021E05C0
	add r5, r6, #0
	str r0, [sp]
	mov r7, #0
_021DB9E0:
	ldr r1, [r4]
	ldr r0, [sp, #0xc]
	tst r0, r1
	beq _021DBA6C
	ldr r0, [r6, #8]
	cmp r0, #0
	bne _021DB9F8
	ldr r0, [r4, #4]
	str r0, [r5, #0x14]
	mov r0, #0
	str r0, [sp, #8]
	b _021DBA2C
_021DB9F8:
	ldr r1, [r4, #4]
	ldr r0, [r4, #8]
	cmp r1, r0
	ldr r1, [r5, #0x14]
	bge _021DBA18
	ldr r0, [r4, #0xc]
	add r1, r1, r0
	str r1, [r5, #0x14]
	ldr r0, [r4, #8]
	cmp r1, r0
	blt _021DBA12
	str r0, [r5, #0x14]
	b _021DBA2C
_021DBA12:
	mov r0, #0
	str r0, [sp, #8]
	b _021DBA2C
_021DBA18:
	ldr r0, [r4, #0xc]
	sub r1, r1, r0
	str r1, [r5, #0x14]
	ldr r0, [r4, #8]
	cmp r1, r0
	bgt _021DBA28
	str r0, [r5, #0x14]
	b _021DBA2C
_021DBA28:
	mov r0, #0
	str r0, [sp, #8]
_021DBA2C:
	ldr r0, [sp]
	mov r2, #0x51
	ldr r0, [r0]
	ldr r1, [r6, #0x2c]
	str r0, [sp, #4]
	mov r0, #0x79
	lsl r0, r0, #2
	add r0, r1, r0
	str r0, [sp, #0x10]
	add r0, r1, #0
	lsl r2, r2, #2
	add r1, r1, r2
	ldr r3, [r5, #0x14]
	add r0, #0xa4
	asr r2, r3, #0xb
	lsr r2, r2, #0x14
	add r2, r3, r2
	ldr r3, [sp, #0x10]
	lsl r2, r2, #4
	add r0, r0, r7
	add r1, r1, r7
	lsr r2, r2, #0x10
	add r3, r3, r7
	bl MOD85_021DB674
	ldr r3, [sp, #0x10]
	ldr r0, [r6, #0x28]
	ldr r2, [sp, #4]
	mov r1, #1
	add r3, r3, r7
	bl MOD85_021DB69C
_021DBA6C:
	ldr r0, [sp]
	add r5, r5, #4
	add r0, r0, #4
	str r0, [sp]
	ldr r0, [sp, #0xc]
	add r7, #0x20
	lsl r0, r0, #1
	str r0, [sp, #0xc]
	cmp r0, #0x10
	bls _021DB9E0
	cmp r0, #0x20
	bhi _021DBAB6
	add r5, r6, #0
	mov r7, #1
	add r5, #0xc
	mov r1, #0
	lsl r7, r7, #0xc
	mov r0, #0x20
_021DBA90:
	ldr r2, [r4]
	tst r2, r0
	beq _021DBAAC
	ldr r2, [r5]
	add r2, r2, r7
	str r2, [r5]
	ldr r3, [r6, #0xc]
	ldr r2, [r4, #4]
	cmp r3, r2
	blt _021DBAA8
	str r1, [r6, #0xc]
	b _021DBAAC
_021DBAA8:
	mov r2, #0
	str r2, [sp, #8]
_021DBAAC:
	ldr r2, [sp, #0xc]
	lsl r2, r2, #1
	str r2, [sp, #0xc]
	cmp r2, #0x20
	bls _021DBA90
_021DBAB6:
	mov r0, #1
	str r0, [r6, #8]
	ldr r0, [sp, #8]
	cmp r0, #1
	bne _021DBAD6
	mov r3, #0
	str r3, [r6, #8]
	ldr r0, [r6, #4]
	ldr r1, _021DBADC ; =0x021DF094
	add r0, r0, #1
	str r0, [r6, #4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0x40
	bne _021DBAD6
	str r3, [r6, #4]
_021DBAD6:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021DBADC: .word MOD85_021DF094
_021DBAE0: .word MOD85_021E05C0
	thumb_func_end MOD85_021DB9C4

	thumb_func_start MOD85_021DBAE4
MOD85_021DBAE4: ; 0x021DBAE4
	push {r4, lr}
	add r4, r1, #0
	bl FUN_0206475C
	mov r1, #0x61
	lsl r1, r1, #2
	str r0, [r4, #0x28]
	add r0, r0, r1
	str r0, [r4, #0x2c]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DBAE4

	thumb_func_start MOD85_021DBAFC
MOD85_021DBAFC: ; 0x021DBAFC
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021DBAFC

	thumb_func_start MOD85_021DBB00
MOD85_021DBB00: ; 0x021DBB00
	ldr r3, _021DBB08 ; =MOD85_021DB9C4
	add r0, r1, #0
	bx r3
	nop
_021DBB08: .word MOD85_021DB9C4
	thumb_func_end MOD85_021DBB00

	thumb_func_start MOD85_021DBB0C
MOD85_021DBB0C: ; 0x021DBB0C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x4f
	mov r1, #0x10
	bl AllocFromHeapAtEnd
	add r1, r0, #0
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	ldr r0, _021DBB2C ; =MOD85_021DBB88
	mov r2, #0x8f
	str r4, [r1, #0xc]
	bl FUN_0200CA44
	pop {r4, pc}
	.align 2, 0
_021DBB2C: .word MOD85_021DBB88
	thumb_func_end MOD85_021DBB0C

	thumb_func_start MOD85_021DBB30
MOD85_021DBB30: ; 0x021DBB30
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x4f
	mov r1, #0x10
	bl AllocFromHeapAtEnd
	add r1, r0, #0
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	ldr r0, _021DBB50 ; =MOD85_021DBBE8
	mov r2, #0x8f
	str r4, [r1, #0xc]
	bl FUN_0200CA44
	pop {r4, pc}
	.align 2, 0
_021DBB50: .word MOD85_021DBBE8
	thumb_func_end MOD85_021DBB30

	thumb_func_start MOD85_021DBB54
MOD85_021DBB54: ; 0x021DBB54
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0x4f
	mov r1, #0x10
	bl AllocFromHeapAtEnd
	add r1, r0, #0
	mov r0, #0
	str r0, [r1]
	mov r0, #2
	str r4, [r1, #8]
	lsl r0, r0, #0xe
	str r0, [r1, #4]
	ldr r0, _021DBB84 ; =MOD85_021DBC48
	mov r2, #0x8f
	str r5, [r1, #0xc]
	bl FUN_0200CA44
	mov r0, #0x5f
	lsl r0, r0, #4
	bl FUN_020054C8
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DBB84: .word MOD85_021DBC48
	thumb_func_end MOD85_021DBB54

	thumb_func_start MOD85_021DBB88
MOD85_021DBB88: ; 0x021DBB88
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	mov r0, #0x61
	ldr r1, [r5, #0xc]
	lsl r0, r0, #2
	add r2, r1, r0
	mov r0, #2
	ldr r3, [r5, #4]
	lsl r0, r0, #0xa
	add r0, r3, r0
	asr r3, r0, #0xb
	lsr r3, r3, #0x14
	add r1, r2, #0
	add r6, r2, #0
	add r3, r0, r3
	str r0, [r5, #4]
	lsl r0, r3, #4
	lsr r4, r0, #0x10
	add r1, #0x24
	add r6, #0x84
	cmp r4, #0x10
	bls _021DBBB8
	mov r4, #0x10
_021DBBB8:
	add r0, r2, #4
	add r2, r4, #0
	add r3, r6, #0
	bl MOD85_021DB674
	ldr r0, [r5, #0xc]
	mov r1, #7
	mov r2, #1
	add r3, r6, #0
	bl MOD85_021DB69C
	cmp r4, #0x10
	beq _021DBBDA
	ldr r0, [r5, #0xc]
	ldr r0, [r0]
	cmp r0, #0x3f
	bne _021DBBE6
_021DBBDA:
	add r0, r5, #0
	bl FreeToHeap
	add r0, r7, #0
	bl FUN_0200CAB4
_021DBBE6:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD85_021DBB88

	thumb_func_start MOD85_021DBBE8
MOD85_021DBBE8: ; 0x021DBBE8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	mov r0, #0x61
	ldr r1, [r5, #0xc]
	lsl r0, r0, #2
	add r2, r1, r0
	mov r1, #2
	ldr r3, [r5, #4]
	lsl r1, r1, #0xa
	add r1, r3, r1
	asr r3, r1, #0xb
	lsr r3, r3, #0x14
	add r0, r2, #0
	add r6, r2, #0
	add r3, r1, r3
	str r1, [r5, #4]
	lsl r1, r3, #4
	lsr r4, r1, #0x10
	add r0, #0x24
	add r6, #0x84
	cmp r4, #0x10
	bls _021DBC18
	mov r4, #0x10
_021DBC18:
	add r1, r2, #4
	add r2, r4, #0
	add r3, r6, #0
	bl MOD85_021DB674
	ldr r0, [r5, #0xc]
	mov r1, #7
	mov r2, #1
	add r3, r6, #0
	bl MOD85_021DB69C
	cmp r4, #0x10
	beq _021DBC3A
	ldr r0, [r5, #0xc]
	ldr r0, [r0]
	cmp r0, #0x3f
	bne _021DBC46
_021DBC3A:
	add r0, r5, #0
	bl FreeToHeap
	add r0, r7, #0
	bl FUN_0200CAB4
_021DBC46:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD85_021DBBE8

	thumb_func_start MOD85_021DBC48
MOD85_021DBC48: ; 0x021DBC48
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldr r1, [r5, #0xc]
	mov r2, #0x61
	lsl r2, r2, #2
	add r7, r0, #0
	add r0, r1, r2
	add r6, r1, r2
	ldr r3, [r1]
	add r0, #0x24
	add r6, #0x84
	cmp r3, #0x3f
	bne _021DBC70
	add r0, r5, #0
	bl FreeToHeap
	add r0, r7, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, r6, r7, pc}
_021DBC70:
	ldr r3, [r5, #8]
	cmp r3, #0
	bne _021DBC7C
	add r1, r1, r2
	add r1, #0x44
	b _021DBC80
_021DBC7C:
	add r1, r1, r2
	add r1, #0x64
_021DBC80:
	ldr r2, [r5]
	cmp r2, #0
	beq _021DBC8C
	cmp r2, #1
	beq _021DBCC2
	pop {r3, r4, r5, r6, r7, pc}
_021DBC8C:
	mov r2, #1
	ldr r3, [r5, #4]
	lsl r2, r2, #0xc
	add r3, r3, r2
	asr r2, r3, #0xb
	lsr r2, r2, #0x14
	add r2, r3, r2
	asr r2, r2, #0xc
	str r3, [r5, #4]
	cmp r2, #0x10
	ble _021DBCAA
	ldr r3, [r5]
	mov r2, #0x10
	add r3, r3, #1
	str r3, [r5]
_021DBCAA:
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	add r3, r6, #0
	bl MOD85_021DB674
	ldr r0, [r5, #0xc]
	mov r1, #7
	mov r2, #1
	add r3, r6, #0
	bl MOD85_021DB69C
	pop {r3, r4, r5, r6, r7, pc}
_021DBCC2:
	mov r2, #1
	ldr r3, [r5, #4]
	lsl r2, r2, #0xa
	sub r2, r3, r2
	asr r3, r2, #0xb
	lsr r3, r3, #0x14
	add r3, r2, r3
	str r2, [r5, #4]
	asr r4, r3, #0xc
	bpl _021DBCD8
	mov r4, #0
_021DBCD8:
	lsl r2, r4, #0x10
	lsr r2, r2, #0x10
	add r3, r6, #0
	bl MOD85_021DB674
	ldr r0, [r5, #0xc]
	mov r1, #7
	mov r2, #1
	add r3, r6, #0
	bl MOD85_021DB69C
	cmp r4, #0
	bne _021DBCFE
	add r0, r5, #0
	bl FreeToHeap
	add r0, r7, #0
	bl FUN_0200CAB4
_021DBCFE:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD85_021DBC48

	thumb_func_start MOD85_021DBD00
MOD85_021DBD00: ; 0x021DBD00
	push {r4, lr}
	add r4, r1, #0
	lsl r1, r4, #2
	add r0, r0, r1
	add r0, #0xa8
	ldr r0, [r0]
	mov r1, #0x15
	add r0, r2, r0
	bl _s32_div_f
	cmp r1, #0
	bge _021DBD1A
	add r1, #0x15
_021DBD1A:
	mov r0, #0x54
	add r2, r4, #0
	mul r2, r0
	ldr r0, _021DBD2C ; =0x021DFDE4
	lsl r1, r1, #2
	add r0, r0, r2
	ldr r0, [r1, r0]
	pop {r4, pc}
	nop
_021DBD2C: .word MOD85_021DFDE4
	thumb_func_end MOD85_021DBD00

	thumb_func_start MOD85_021DBD30
MOD85_021DBD30: ; 0x021DBD30
	push {r4, r5, r6, lr}
	lsl r4, r1, #2
	add r4, r0, r4
	add r4, #0x90
	ldr r4, [r4]
	mov r3, #0
	lsr r6, r4, #0x1f
	lsl r5, r4, #0xf
	sub r5, r5, r6
	mov r4, #0xf
	ror r5, r4
	add r4, r6, r5
	beq _021DBD4C
	sub r3, r3, #1
_021DBD4C:
	add r2, r2, r3
	bl MOD85_021DBD00
	pop {r4, r5, r6, pc}
	thumb_func_end MOD85_021DBD30

	thumb_func_start MOD85_021DBD54
MOD85_021DBD54: ; 0x021DBD54
	ldr r1, _021DBD70 ; =0x021C48B8
	ldr r1, [r1, #0x48]
	and r1, r0
	cmp r1, r0
	bne _021DBD62
	mov r0, #2
	bx lr
_021DBD62:
	tst r0, r1
	beq _021DBD6A
	mov r0, #1
	bx lr
_021DBD6A:
	mov r0, #0
	bx lr
	nop
_021DBD70: .word 0x021C48B8
	thumb_func_end MOD85_021DBD54

	thumb_func_start MOD85_021DBD74
MOD85_021DBD74: ; 0x021DBD74
	mov r2, #3
	add r1, r0, #0
	tst r1, r2
	beq _021DBD80
	mov r0, #2
	bx lr
_021DBD80:
	mov r1, #0xc
	tst r1, r0
	beq _021DBD8A
	add r0, r2, #0
	bx lr
_021DBD8A:
	mov r1, #0x30
	tst r1, r0
	beq _021DBD94
	mov r0, #4
	bx lr
_021DBD94:
	mov r1, #0xc0
	add r2, r0, #0
	tst r2, r1
	beq _021DBDA0
	mov r0, #5
	bx lr
_021DBDA0:
	add r1, #0x40
	tst r1, r0
	beq _021DBDAA
	mov r0, #1
	bx lr
_021DBDAA:
	mov r1, #2
	lsl r1, r1, #8
	tst r0, r1
	beq _021DBDB6
	mov r0, #0
	bx lr
_021DBDB6:
	mov r0, #6
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021DBD74

	thumb_func_start MOD85_021DBDBC
MOD85_021DBDBC: ; 0x021DBDBC
	push {r4, r5, r6, lr}
	mov r1, #0
	mov r2, #1
	add r5, r0, #0
	bl MOD85_021DBD30
	mov r1, #1
	add r4, r0, #0
	add r0, r5, #0
	add r2, r1, #0
	bl MOD85_021DBD30
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #2
	mov r2, #1
	bl MOD85_021DBD30
	cmp r4, #3
	beq _021DBDEC
	cmp r4, r6
	bne _021DBDF0
	cmp r4, r0
	bne _021DBDF0
_021DBDEC:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_021DBDF0:
	mov r0, #6
	pop {r4, r5, r6, pc}
	thumb_func_end MOD85_021DBDBC

	thumb_func_start MOD85_021DBDF4
MOD85_021DBDF4: ; 0x021DBDF4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r1, #0
	mov r2, #2
	bl MOD85_021DBD30
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #1
	mov r2, #2
	bl MOD85_021DBD30
	mov r1, #2
	add r6, r0, #0
	add r0, r5, #0
	add r2, r1, #0
	bl MOD85_021DBD30
	cmp r4, #3
	beq _021DBE24
	cmp r4, r6
	bne _021DBE28
	cmp r4, r0
	bne _021DBE28
_021DBE24:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_021DBE28:
	mov r0, #6
	pop {r4, r5, r6, pc}
	thumb_func_end MOD85_021DBDF4

	thumb_func_start MOD85_021DBE2C
MOD85_021DBE2C: ; 0x021DBE2C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r1, #0
	mov r2, #3
	bl MOD85_021DBD30
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #1
	mov r2, #3
	bl MOD85_021DBD30
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #2
	mov r2, #3
	bl MOD85_021DBD30
	cmp r4, #3
	beq _021DBE5C
	cmp r4, r6
	bne _021DBE60
	cmp r4, r0
	bne _021DBE60
_021DBE5C:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_021DBE60:
	mov r0, #6
	pop {r4, r5, r6, pc}
	thumb_func_end MOD85_021DBE2C

	thumb_func_start MOD85_021DBE64
MOD85_021DBE64: ; 0x021DBE64
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r1, #0
	mov r2, #1
	bl MOD85_021DBD30
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #1
	mov r2, #2
	bl MOD85_021DBD30
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #2
	mov r2, #3
	bl MOD85_021DBD30
	cmp r4, #3
	beq _021DBE94
	cmp r4, r6
	bne _021DBE98
	cmp r4, r0
	bne _021DBE98
_021DBE94:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_021DBE98:
	mov r0, #6
	pop {r4, r5, r6, pc}
	thumb_func_end MOD85_021DBE64

	thumb_func_start MOD85_021DBE9C
MOD85_021DBE9C: ; 0x021DBE9C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r1, #0
	mov r2, #3
	bl MOD85_021DBD30
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #1
	mov r2, #2
	bl MOD85_021DBD30
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #2
	mov r2, #1
	bl MOD85_021DBD30
	cmp r4, #3
	beq _021DBECC
	cmp r4, r6
	bne _021DBED0
	cmp r4, r0
	bne _021DBED0
_021DBECC:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_021DBED0:
	mov r0, #6
	pop {r4, r5, r6, pc}
	thumb_func_end MOD85_021DBE9C

	thumb_func_start MOD85_021DBED4
MOD85_021DBED4: ; 0x021DBED4
	push {r4, r5, r6, lr}
	add r4, r2, #0
	mov r1, #0
	add r5, r0, #0
	str r1, [r4]
	mov r6, #6
	bl MOD85_021DBDBC
	cmp r0, #6
	beq _021DBEF2
	ldr r1, [r4]
	add r6, r0, #0
	mov r0, #2
	orr r0, r1
	str r0, [r4]
_021DBEF2:
	add r0, r5, #0
	bl MOD85_021DBDF4
	cmp r0, #6
	beq _021DBF06
	ldr r1, [r4]
	add r6, r0, #0
	mov r0, #1
	orr r0, r1
	str r0, [r4]
_021DBF06:
	add r0, r5, #0
	bl MOD85_021DBE2C
	cmp r0, #6
	beq _021DBF1A
	ldr r1, [r4]
	add r6, r0, #0
	mov r0, #4
	orr r0, r1
	str r0, [r4]
_021DBF1A:
	add r0, r5, #0
	bl MOD85_021DBE64
	cmp r0, #6
	beq _021DBF2E
	ldr r1, [r4]
	add r6, r0, #0
	mov r0, #8
	orr r0, r1
	str r0, [r4]
_021DBF2E:
	add r0, r5, #0
	bl MOD85_021DBE9C
	cmp r0, #6
	beq _021DBF42
	ldr r1, [r4]
	add r6, r0, #0
	mov r0, #0x10
	orr r0, r1
	str r0, [r4]
_021DBF42:
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD85_021DBED4

	thumb_func_start MOD85_021DBF48
MOD85_021DBF48: ; 0x021DBF48
	push {r3, r4, r5, lr}
	add r5, r2, #0
	mov r1, #0
	str r1, [r5]
	bl MOD85_021DBDF4
	add r4, r0, #0
	cmp r4, #6
	beq _021DBF6A
	cmp r4, #2
	beq _021DBF62
	bl ErrorHandling
_021DBF62:
	ldr r1, [r5]
	mov r0, #1
	orr r0, r1
	str r0, [r5]
_021DBF6A:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DBF48

	thumb_func_start MOD85_021DBF70
MOD85_021DBF70: ; 0x021DBF70
	push {r3, lr}
	mov r2, #3
	add r1, r0, #0
	tst r1, r2
	beq _021DBF7E
	mov r0, #1
	pop {r3, pc}
_021DBF7E:
	mov r1, #0xc
	tst r1, r0
	beq _021DBF88
	mov r0, #0
	pop {r3, pc}
_021DBF88:
	mov r1, #0x30
	tst r1, r0
	beq _021DBF92
	mov r0, #2
	pop {r3, pc}
_021DBF92:
	mov r1, #0xc0
	tst r0, r1
	beq _021DBF9C
	add r0, r2, #0
	pop {r3, pc}
_021DBF9C:
	bl ErrorHandling
	mov r0, #4
	pop {r3, pc}
	thumb_func_end MOD85_021DBF70

	thumb_func_start MOD85_021DBFA4
MOD85_021DBFA4: ; 0x021DBFA4
	mov r2, #0
	add r1, r2, #0
_021DBFA8:
	add r2, r2, #1
	str r1, [r0, #0x54]
	add r0, r0, #4
	cmp r2, #3
	blt _021DBFA8
	bx lr
	thumb_func_end MOD85_021DBFA4

	thumb_func_start MOD85_021DBFB4
MOD85_021DBFB4: ; 0x021DBFB4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r4, #0
	add r1, r5, #0
_021DBFBE:
	ldr r0, [r1, #0x54]
	cmp r0, #0
	beq _021DBFCC
	add r4, r4, #1
	add r1, r1, #4
	cmp r4, #3
	blt _021DBFBE
_021DBFCC:
	cmp r4, #3
	blt _021DBFD4
	bl ErrorHandling
_021DBFD4:
	lsl r0, r4, #2
	add r0, r5, r0
	str r6, [r0, #0x54]
	pop {r4, r5, r6, pc}
	thumb_func_end MOD85_021DBFB4

	thumb_func_start MOD85_021DBFDC
MOD85_021DBFDC: ; 0x021DBFDC
	push {r4, r5, r6}
	sub sp, #0xc
	ldr r6, _021DC018 ; =0x021DEDC8
	add r4, r0, #0
	ldmia r6!, {r0, r1}
	add r5, sp, #0
	add r3, r5, #0
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	mov r2, #0
	str r0, [r5]
_021DBFF2:
	ldr r1, [r4, #0x54]
	cmp r1, #0
	beq _021DC006
	ldr r0, [r3]
	cmp r1, r0
	beq _021DC006
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6}
	bx lr
_021DC006:
	add r2, r2, #1
	add r4, r4, #4
	add r3, r3, #4
	cmp r2, #3
	blt _021DBFF2
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, r6}
	bx lr
	.align 2, 0
_021DC018: .word MOD85_021DEDC8
	thumb_func_end MOD85_021DBFDC

	thumb_func_start MOD85_021DC01C
MOD85_021DC01C: ; 0x021DC01C
	push {r3, r4}
	ldr r2, [r0, #0x34]
	mov r1, #0x18
	ldr r3, _021DC04C ; =0x021DEF04
	mul r1, r2
	mov r4, #0
	add r3, r3, r1
_021DC02A:
	ldr r2, [r0, #0x54]
	cmp r2, #0
	beq _021DC03C
	ldr r1, [r3]
	cmp r2, r1
	beq _021DC03C
	mov r0, #0
	pop {r3, r4}
	bx lr
_021DC03C:
	add r4, r4, #1
	add r0, r0, #4
	add r3, r3, #4
	cmp r4, #3
	blt _021DC02A
	mov r0, #1
	pop {r3, r4}
	bx lr
	.align 2, 0
_021DC04C: .word MOD85_021DEF04
	thumb_func_end MOD85_021DC01C

	thumb_func_start MOD85_021DC050
MOD85_021DC050: ; 0x021DC050
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #3
	str r0, [sp]
	mov r0, #2
	lsl r2, r1, #3
	ldr r3, _021DC08C ; =0x021DEE9C
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	add r5, r3, r2
	ldr r2, [r3, r2]
	ldr r0, _021DC090 ; =0x0000043C
	ldr r3, [r5, #4]
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r4, r0]
	mov r1, #1
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_020186B4
	ldr r0, _021DC090 ; =0x0000043C
	mov r1, #1
	ldr r0, [r4, r0]
	bl FUN_0201AC68
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_021DC08C: .word MOD85_021DEE9C
_021DC090: .word 0x0000043C
	thumb_func_end MOD85_021DC050

	thumb_func_start MOD85_021DC094
MOD85_021DC094: ; 0x021DC094
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #3
	str r0, [sp]
	mov r0, #2
	lsl r2, r1, #3
	ldr r3, _021DC0D0 ; =0x021DEE9C
	str r0, [sp, #4]
	mov r0, #5
	str r0, [sp, #8]
	add r5, r3, r2
	ldr r2, [r3, r2]
	ldr r0, _021DC0D4 ; =0x0000043C
	ldr r3, [r5, #4]
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r4, r0]
	mov r1, #1
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_020186B4
	ldr r0, _021DC0D4 ; =0x0000043C
	mov r1, #1
	ldr r0, [r4, r0]
	bl FUN_0201AC68
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_021DC0D0: .word MOD85_021DEE9C
_021DC0D4: .word 0x0000043C
	thumb_func_end MOD85_021DC094

	thumb_func_start MOD85_021DC0D8
MOD85_021DC0D8: ; 0x021DC0D8
	push {r3, r4, r5, lr}
	ldr r4, [r0, #0x44]
	ldr r5, [r0, #0x48]
	cmp r4, #6
	bne _021DC0E6
	bl ErrorHandling
_021DC0E6:
	ldr r3, _021DC104 ; =0x021DFCAC
	lsl r2, r4, #2
	mov r1, #0
	ldr r3, [r3, r2]
	add r0, r1, #0
	mov r2, #1
_021DC0F2:
	add r4, r5, #0
	tst r4, r2
	beq _021DC0FA
	add r0, r0, r3
_021DC0FA:
	add r1, r1, #1
	lsr r5, r5, #1
	cmp r1, #5
	blt _021DC0F2
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DC104: .word MOD85_021DFCAC
	thumb_func_end MOD85_021DC0D8

	thumb_func_start MOD85_021DC108
MOD85_021DC108: ; 0x021DC108
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r7, r0, #0
	mov r4, #0
	add r0, sp, #8
	str r4, [r0]
	str r4, [r0, #4]
	mov r6, #0x11
	lsl r6, r6, #0xe
	str r4, [r0, #8]
	str r7, [sp, #0x14]
	cmp r4, #3
	bge _021DC15A
_021DC122:
	mov r5, #0
_021DC124:
	str r6, [sp, #8]
	str r4, [sp, #0x1c]
	str r5, [sp, #0x18]
	add r0, sp, #0x14
	str r0, [sp]
	mov r0, #0x8b
	str r0, [sp, #4]
	ldr r0, _021DC160 ; =0x0000044C
	ldr r1, _021DC164 ; =0x021DF938
	ldr r0, [r7, r0]
	add r2, sp, #8
	mov r3, #0
	bl FUN_020644E4
	mov r0, #2
	lsl r0, r0, #0x10
	add r5, r5, r0
	mov r0, #0xa
	lsl r0, r0, #0x10
	cmp r5, r0
	blt _021DC124
	mov r0, #0xf
	lsl r0, r0, #0xe
	add r4, r4, #1
	add r6, r6, r0
	cmp r4, #3
	blt _021DC122
_021DC15A:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DC160: .word 0x0000044C
_021DC164: .word MOD85_021DF938
	thumb_func_end MOD85_021DC108

	thumb_func_start MOD85_021DC168
MOD85_021DC168: ; 0x021DC168
	push {r3, r4, r5, lr}
	sub sp, #0x28
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0206475C
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, r4, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, sp, #0x1c
	str r0, [r2]
	add r0, r5, #0
	bl FUN_0206477C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #3
	str r0, [sp, #0x14]
	mov r0, #2
	str r0, [sp, #0x18]
	mov r0, #0x45
	ldr r1, [r4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, r4, #0
	add r1, #0xc
	add r2, sp, #0x1c
	mov r3, #1
	bl MOD85_021DEC00
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #1
	add sp, #0x28
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DC168

	thumb_func_start MOD85_021DC1C0
MOD85_021DC1C0: ; 0x021DC1C0
	ldr r3, _021DC1C8 ; =MOD85_021DECA0
	add r1, #0xc
	add r0, r1, #0
	bx r3
	.align 2, 0
_021DC1C8: .word MOD85_021DECA0
	thumb_func_end MOD85_021DC1C0

	thumb_func_start MOD85_021DC1CC
MOD85_021DC1CC: ; 0x021DC1CC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	ldr r7, [r5, #8]
	str r0, [sp]
	ldr r0, [r5]
	lsl r6, r7, #2
	add r0, r0, r6
	add r0, #0x90
	ldr r1, [r5, #4]
	ldr r0, [r0]
	add r0, r1, r0
	mov r1, #0xa
	lsl r1, r1, #0x10
	bl _s32_div_f
	add r4, r1, #0
	ldr r0, [sp]
	add r1, sp, #4
	bl FUN_0206477C
	ldr r1, [r5]
	mov r0, #1
	add r1, r1, r6
	add r1, #0x9c
	lsl r0, r0, #0x10
	ldr r1, [r1]
	add r0, r4, r0
	add r0, r0, r1
	str r0, [sp, #8]
	ldr r0, [r5, #0x10]
	add r1, sp, #4
	bl FUN_02020044
	asr r2, r4, #0x10
	lsr r2, r2, #0xf
	add r2, r4, r2
	ldr r0, [r5]
	add r1, r7, #0
	asr r2, r2, #0x11
	bl MOD85_021DBD00
	lsl r1, r0, #2
	ldr r0, _021DC244 ; =0x021DF9D8
	ldr r4, [r0, r1]
	ldr r0, [r5, #0x10]
	bl FUN_020201DC
	cmp r4, r0
	beq _021DC240
	ldr r0, [r5, #0x10]
	add r1, r4, #0
	bl FUN_02020130
	ldr r0, [r5, #0x10]
	mov r1, #0
	bl FUN_02020208
_021DC240:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DC244: .word MOD85_021DF9D8
	thumb_func_end MOD85_021DC1CC

	thumb_func_start MOD85_021DC248
MOD85_021DC248: ; 0x021DC248
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021DC248

	thumb_func_start MOD85_021DC24C
MOD85_021DC24C: ; 0x021DC24C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	ldr r3, _021DC290 ; =0x021DF628
	add r5, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #8
	add r6, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r4, #1
	str r0, [r2]
	mov r7, #0x8d
_021DC264:
	str r5, [sp]
	ldr r0, _021DC294 ; =0x0000044C
	str r7, [sp, #4]
	ldr r0, [r5, r0]
	ldr r1, _021DC298 ; =0x021DF94C
	add r2, r6, #0
	add r3, r4, #0
	bl FUN_020644E4
	mov r0, #0xa
	mul r4, r0
	mov r0, #2
	ldr r1, [sp, #8]
	lsl r0, r0, #0xe
	sub r0, r1, r0
	str r0, [sp, #8]
	ldr r0, _021DC29C ; =0x000186A0
	cmp r4, r0
	blo _021DC264
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021DC290: .word MOD85_021DF628
_021DC294: .word 0x0000044C
_021DC298: .word MOD85_021DF94C
_021DC29C: .word 0x000186A0
	thumb_func_end MOD85_021DC24C

	thumb_func_start MOD85_021DC2A0
MOD85_021DC2A0: ; 0x021DC2A0
	push {r3, r4, r5, lr}
	sub sp, #0x28
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_02064754
	mov r1, #0xa
	str r0, [r4, #4]
	mul r1, r0
	str r1, [r4, #8]
	add r0, r5, #0
	bl FUN_0206475C
	str r0, [r4]
	add r0, r5, #0
	add r1, sp, #0x1c
	bl FUN_0206477C
	mov r0, #0
	str r0, [sp]
	mov r3, #1
	str r3, [sp, #4]
	str r3, [sp, #8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	str r3, [sp, #0x14]
	str r3, [sp, #0x18]
	mov r0, #0x45
	ldr r1, [r4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, r4, #0
	add r1, #0xc
	add r2, sp, #0x1c
	bl MOD85_021DEC00
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #1
	add sp, #0x28
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DC2A0

	thumb_func_start MOD85_021DC2F8
MOD85_021DC2F8: ; 0x021DC2F8
	ldr r3, _021DC300 ; =MOD85_021DECA0
	add r1, #0xc
	add r0, r1, #0
	bx r3
	.align 2, 0
_021DC300: .word MOD85_021DECA0
	thumb_func_end MOD85_021DC2F8

	thumb_func_start MOD85_021DC304
MOD85_021DC304: ; 0x021DC304
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5]
	ldr r4, [r0, #0x60]
	ldr r0, [r5, #4]
	cmp r0, #1
	bls _021DC326
	cmp r4, r0
	bhs _021DC326
	ldr r0, [r5, #0x10]
	mov r1, #0
	bl FUN_020200A0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_021DC326:
	ldr r0, [r5, #0x10]
	mov r1, #1
	bl FUN_020200A0
	ldr r1, [r5, #8]
	add r0, r4, #0
	bl _u32_div_f
	add r4, r1, #0
	ldr r1, [r5, #4]
	add r0, r4, #0
	bl _u32_div_f
	add r4, r0, #0
	ldr r0, [r5, #0x10]
	bl FUN_020201DC
	cmp r4, r0
	beq _021DC35A
	ldr r0, [r5, #0x10]
	add r1, r4, #0
	bl FUN_02020130
	ldr r0, [r5, #0x10]
	bl FUN_02020198
_021DC35A:
	add r0, r6, #0
	add r1, sp, #0
	bl FUN_0206477C
	ldr r0, _021DC37C ; =0x021DFAD8
	lsl r1, r4, #2
	ldr r0, [r0, r1]
	ldr r2, [sp]
	add r1, sp, #0
	add r0, r2, r0
	str r0, [sp]
	ldr r0, [r5, #0x10]
	bl FUN_02020044
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021DC37C: .word MOD85_021DFAD8
	thumb_func_end MOD85_021DC304

	thumb_func_start MOD85_021DC380
MOD85_021DC380: ; 0x021DC380
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021DC380

	thumb_func_start MOD85_021DC384
MOD85_021DC384: ; 0x021DC384
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	ldr r3, _021DC3C8 ; =0x021DF6F4
	add r5, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #8
	add r6, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r4, #1
	str r0, [r2]
	mov r7, #0x8d
_021DC39C:
	str r5, [sp]
	ldr r0, _021DC3CC ; =0x0000044C
	str r7, [sp, #4]
	ldr r0, [r5, r0]
	ldr r1, _021DC3D0 ; =0x021DF960
	add r2, r6, #0
	add r3, r4, #0
	bl FUN_020644E4
	mov r0, #0xa
	mul r4, r0
	mov r0, #2
	ldr r1, [sp, #8]
	lsl r0, r0, #0xe
	sub r0, r1, r0
	str r0, [sp, #8]
	ldr r0, _021DC3D4 ; =0x000186A0
	cmp r4, r0
	blo _021DC39C
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021DC3C8: .word MOD85_021DF6F4
_021DC3CC: .word 0x0000044C
_021DC3D0: .word MOD85_021DF960
_021DC3D4: .word 0x000186A0
	thumb_func_end MOD85_021DC384

	thumb_func_start MOD85_021DC3D8
MOD85_021DC3D8: ; 0x021DC3D8
	push {r3, r4, r5, lr}
	sub sp, #0x28
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_02064754
	mov r1, #0xa
	str r0, [r4, #4]
	mul r1, r0
	str r1, [r4, #8]
	add r0, r5, #0
	bl FUN_0206475C
	str r0, [r4]
	add r0, r5, #0
	add r1, sp, #0x1c
	bl FUN_0206477C
	mov r0, #0
	str r0, [sp]
	mov r3, #1
	str r3, [sp, #4]
	str r3, [sp, #8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	str r3, [sp, #0x14]
	str r3, [sp, #0x18]
	mov r0, #0x45
	ldr r1, [r4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, r4, #0
	add r1, #0xc
	add r2, sp, #0x1c
	bl MOD85_021DEC00
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #1
	add sp, #0x28
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DC3D8

	thumb_func_start MOD85_021DC430
MOD85_021DC430: ; 0x021DC430
	ldr r3, _021DC438 ; =MOD85_021DECA0
	add r1, #0xc
	add r0, r1, #0
	bx r3
	.align 2, 0
_021DC438: .word MOD85_021DECA0
	thumb_func_end MOD85_021DC430

	thumb_func_start MOD85_021DC43C
MOD85_021DC43C: ; 0x021DC43C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5]
	ldr r4, [r0, #0x64]
	ldr r0, [r5, #4]
	cmp r4, r0
	ldr r0, [r5, #0x10]
	bhs _021DC45A
	mov r1, #0
	bl FUN_020200A0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_021DC45A:
	mov r1, #1
	bl FUN_020200A0
	ldr r1, [r5, #8]
	add r0, r4, #0
	bl _u32_div_f
	add r4, r1, #0
	ldr r1, [r5, #4]
	add r0, r4, #0
	bl _u32_div_f
	add r4, r0, #0
	ldr r0, [r5, #0x10]
	bl FUN_020201DC
	cmp r4, r0
	beq _021DC48C
	ldr r0, [r5, #0x10]
	add r1, r4, #0
	bl FUN_02020130
	ldr r0, [r5, #0x10]
	bl FUN_02020198
_021DC48C:
	add r0, r6, #0
	add r1, sp, #0
	bl FUN_0206477C
	ldr r0, _021DC4AC ; =0x021DFAB0
	lsl r1, r4, #2
	ldr r0, [r0, r1]
	ldr r2, [sp]
	add r1, sp, #0
	add r0, r2, r0
	str r0, [sp]
	ldr r0, [r5, #0x10]
	bl FUN_02020044
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021DC4AC: .word MOD85_021DFAB0
	thumb_func_end MOD85_021DC43C

	thumb_func_start MOD85_021DC4B0
MOD85_021DC4B0: ; 0x021DC4B0
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021DC4B0

	thumb_func_start MOD85_021DC4B4
MOD85_021DC4B4: ; 0x021DC4B4
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	ldr r6, _021DC4E0 ; =0x021DF808
	add r5, sp, #8
	add r4, r0, #0
	add r3, r1, #0
	ldmia r6!, {r0, r1}
	add r2, r5, #0
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	ldr r1, _021DC4E4 ; =0x021DF974
	str r0, [r5]
	str r4, [sp]
	mov r0, #0x86
	str r0, [sp, #4]
	ldr r0, _021DC4E8 ; =0x0000044C
	ldr r0, [r4, r0]
	bl FUN_020644E4
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	nop
_021DC4E0: .word MOD85_021DF808
_021DC4E4: .word MOD85_021DF974
_021DC4E8: .word 0x0000044C
	thumb_func_end MOD85_021DC4B4

	thumb_func_start MOD85_021DC4EC
MOD85_021DC4EC: ; 0x021DC4EC
	push {r4, lr}
	add r4, r1, #0
	bl FUN_02064738
	str r4, [r0]
	mov r1, #0
	str r1, [r0, #4]
	str r1, [r0, #8]
	str r1, [r0, #0x30]
	pop {r4, pc}
	thumb_func_end MOD85_021DC4EC

	thumb_func_start MOD85_021DC500
MOD85_021DC500: ; 0x021DC500
	push {r4, lr}
	add r4, r1, #0
	bl FUN_02064738
	cmp r4, #1
	ldr r0, [r0, #0x40]
	bne _021DC516
	mov r1, #0
	bl FUN_020200A0
	pop {r4, pc}
_021DC516:
	mov r1, #1
	bl FUN_020200A0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DC500

	thumb_func_start MOD85_021DC520
MOD85_021DC520: ; 0x021DC520
	push {r3, lr}
	bl FUN_02064738
	ldr r0, [r0, #8]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD85_021DC520

	thumb_func_start MOD85_021DC52C
MOD85_021DC52C: ; 0x021DC52C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0206475C
	str r0, [r4, #0x38]
	add r0, r5, #0
	bl FUN_02064754
	str r0, [r4, #0x10]
	mov r0, #1
	pop {r3, r4, r5, pc}
	thumb_func_end MOD85_021DC52C

	thumb_func_start MOD85_021DC544
MOD85_021DC544: ; 0x021DC544
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x40]
	cmp r0, #0
	beq _021DC55C
	ldr r0, [r4, #0x38]
	bl MOD85_021DCB00
	add r4, #0x3c
	add r0, r4, #0
	bl MOD85_021DECA0
_021DC55C:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DC544

	thumb_func_start MOD85_021DC560
MOD85_021DC560: ; 0x021DC560
	push {r3, r4, r5, lr}
	ldr r4, _021DC57C ; =0x021DF9F0
	add r5, r1, #0
_021DC566:
	ldr r1, [r5]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	ldr r1, [r5, #4]
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	blx r1
	cmp r0, #1
	beq _021DC566
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DC57C: .word MOD85_021DF9F0
	thumb_func_end MOD85_021DC560

	thumb_func_start MOD85_021DC580
MOD85_021DC580: ; 0x021DC580
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021DC580

	thumb_func_start MOD85_021DC584
MOD85_021DC584: ; 0x021DC584
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x10]
	bl MOD85_021DCA68
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021DC584

	thumb_func_start MOD85_021DC598
MOD85_021DC598: ; 0x021DC598
	ldr r1, [r0, #0xc]
	cmp r1, #2
	bne _021DC5A4
	ldr r1, [r0, #4]
	add r1, r1, #1
	str r1, [r0, #4]
_021DC5A4:
	mov r0, #0
	bx lr
	thumb_func_end MOD85_021DC598

	thumb_func_start MOD85_021DC5A8
MOD85_021DC5A8: ; 0x021DC5A8
	push {r4, r5, lr}
	sub sp, #0xc
	ldr r5, _021DC5D8 ; =0x021DF820
	add r4, r0, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r4, #0
	str r0, [r3]
	ldr r0, [r4, #0x38]
	add r1, #0x3c
	bl MOD85_021DCB6C
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_021DC5D8: .word MOD85_021DF820
	thumb_func_end MOD85_021DC5A8

	thumb_func_start MOD85_021DC5DC
MOD85_021DC5DC: ; 0x021DC5DC
	mov r0, #0
	bx lr
	thumb_func_end MOD85_021DC5DC

	thumb_func_start MOD85_021DC5E0
MOD85_021DC5E0: ; 0x021DC5E0
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r3, _021DC63C ; =0x021DF7E4
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r5, _021DC640 ; =0x021DF70C
	str r0, [r2]
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r2, #0
	str r0, [r3]
	ldr r0, [r4, #0x40]
	bl FUN_02020064
	ldr r0, [r4, #0x40]
	mov r1, #0
	bl FUN_02020088
	ldr r0, [r4, #0x40]
	add r1, sp, #0xc
	bl FUN_02020044
	ldr r0, [r4, #0x40]
	mov r1, #0
	bl FUN_02020130
	ldr r0, [r4, #0x40]
	mov r1, #0
	bl FUN_02020208
	ldr r0, _021DC644 ; =0x00000624
	bl FUN_020054C8
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_021DC63C: .word MOD85_021DF7E4
_021DC640: .word MOD85_021DF70C
_021DC644: .word 0x00000624
	thumb_func_end MOD85_021DC5E0

	thumb_func_start MOD85_021DC648
MOD85_021DC648: ; 0x021DC648
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	add r1, sp, #0xc
	bl MOD85_021DECBC
	ldr r0, [r4, #0x40]
	add r1, sp, #0
	bl MOD85_021DECD0
	mov r0, #1
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0xe
	sub r1, r1, r0
	str r1, [sp, #0x10]
	ldr r2, [sp]
	ldr r1, _021DC6AC ; =0x000001C7
	sub r2, r2, r1
	str r2, [sp]
	ldr r2, [sp, #4]
	sub r1, r2, r1
	str r1, [sp, #4]
	ldr r1, [r4, #0x30]
	add r1, r1, #1
	str r1, [r4, #0x30]
	cmp r1, #9
	blo _021DC696
	mov r1, #0x16
	lsr r0, r0, #2
	lsl r1, r1, #0x10
	str r1, [sp, #0x10]
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [r4, #0x30]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DC696:
	ldr r0, [r4, #0x40]
	add r1, sp, #0xc
	bl FUN_02020044
	ldr r0, [r4, #0x40]
	add r1, sp, #0
	bl FUN_02020064
	mov r0, #0
	add sp, #0x18
	pop {r4, pc}
	.align 2, 0
_021DC6AC: .word 0x000001C7
	thumb_func_end MOD85_021DC648

	thumb_func_start MOD85_021DC6B0
MOD85_021DC6B0: ; 0x021DC6B0
	ldr r1, [r0, #0x30]
	add r1, r1, #1
	str r1, [r0, #0x30]
	cmp r1, #3
	blo _021DC6C8
	mov r1, #0
	str r1, [r0, #0x30]
	mov r1, #1
	str r1, [r0, #8]
	ldr r1, [r0, #4]
	add r1, r1, #1
	str r1, [r0, #4]
_021DC6C8:
	mov r0, #0
	bx lr
	thumb_func_end MOD85_021DC6B0

	thumb_func_start MOD85_021DC6CC
MOD85_021DC6CC: ; 0x021DC6CC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	mov r1, #1
	bl FUN_02020130
	ldr r0, [r4, #0x40]
	bl FUN_02020198
	ldr r0, [r4, #0x40]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x6d
	lsl r0, r0, #4
	bl FUN_020054C8
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021DC6CC

	thumb_func_start MOD85_021DC6F8
MOD85_021DC6F8: ; 0x021DC6F8
	ldr r1, [r0, #0x30]
	add r1, r1, #1
	str r1, [r0, #0x30]
	cmp r1, #4
	blo _021DC710
	mov r1, #0
	str r1, [r0, #0x30]
	mov r1, #1
	str r1, [r0, #8]
	ldr r1, [r0, #4]
	add r1, r1, #1
	str r1, [r0, #4]
_021DC710:
	mov r0, #0
	bx lr
	thumb_func_end MOD85_021DC6F8

	thumb_func_start MOD85_021DC714
MOD85_021DC714: ; 0x021DC714
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r3, _021DC774 ; =0x021DF754
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r5, _021DC778 ; =0x021DF670
	str r0, [r2]
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r5, r2, #0
	str r0, [r3]
	add r3, r4, #0
	ldmia r5!, {r0, r1}
	add r3, #0x14
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r2, #0
	str r0, [r3]
	ldr r0, [r4, #0x40]
	bl FUN_02020044
	ldr r0, [r4, #0x40]
	add r1, sp, #0xc
	bl FUN_02020064
	ldr r0, [r4, #0x40]
	mov r1, #0
	bl FUN_02020088
	ldr r0, [r4, #0x40]
	mov r1, #3
	bl FUN_02020130
	ldr r0, [r4, #0x40]
	bl FUN_02020198
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #1
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DC774: .word MOD85_021DF754
_021DC778: .word MOD85_021DF670
	thumb_func_end MOD85_021DC714

	thumb_func_start MOD85_021DC77C
MOD85_021DC77C: ; 0x021DC77C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x2c
	ldr r5, _021DC7DC ; =0x021DFA0C
	add r4, r0, #0
	add r2, sp, #0
	ldmia r5!, {r0, r1}
	add r3, r2, #0
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	add r6, r4, #0
	add r6, #0x14
	stmia r2!, {r0, r1}
	add r5, sp, #0x20
	ldmia r6!, {r0, r1}
	add r2, r5, #0
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	str r0, [r5]
	ldr r1, [r4, #0x30]
	ldr r0, [sp, #0x24]
	lsr r1, r1, #1
	lsl r1, r1, #2
	ldr r1, [r3, r1]
	add r0, r0, r1
	str r0, [sp, #0x24]
	ldr r0, [r4, #0x40]
	add r1, r2, #0
	bl FUN_02020044
	ldr r0, [r4, #0x30]
	add r0, r0, #1
	str r0, [r4, #0x30]
	cmp r0, #0x10
	blo _021DC7D6
	mov r0, #0
	str r0, [r4, #0x30]
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DC7D6:
	mov r0, #0
	add sp, #0x2c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021DC7DC: .word MOD85_021DFA0C
	thumb_func_end MOD85_021DC77C

	thumb_func_start MOD85_021DC7E0
MOD85_021DC7E0: ; 0x021DC7E0
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r3, _021DC840 ; =0x021DF640
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r5, _021DC844 ; =0x021DF730
	str r0, [r2]
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r5, r2, #0
	str r0, [r3]
	add r3, r4, #0
	ldmia r5!, {r0, r1}
	add r3, #0x14
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r2, #0
	str r0, [r3]
	ldr r0, [r4, #0x40]
	bl FUN_02020044
	ldr r0, [r4, #0x40]
	add r1, sp, #0xc
	bl FUN_02020064
	ldr r0, [r4, #0x40]
	mov r1, #0
	bl FUN_02020088
	ldr r0, [r4, #0x40]
	mov r1, #4
	bl FUN_02020130
	ldr r0, [r4, #0x40]
	bl FUN_02020198
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #1
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DC840: .word MOD85_021DF640
_021DC844: .word MOD85_021DF730
	thumb_func_end MOD85_021DC7E0

	thumb_func_start MOD85_021DC848
MOD85_021DC848: ; 0x021DC848
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	add r1, sp, #0xc
	bl MOD85_021DECBC
	ldr r0, [r4, #0x40]
	add r1, sp, #0
	bl MOD85_021DECD0
	mov r0, #1
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0xe
	add r1, r1, r0
	str r1, [sp, #0x10]
	ldr r2, [sp]
	ldr r1, _021DC8B0 ; =0x000001C7
	add r2, r2, r1
	str r2, [sp]
	ldr r2, [sp, #4]
	add r1, r2, r1
	str r1, [sp, #4]
	ldr r1, [r4, #0x30]
	add r1, r1, #1
	str r1, [r4, #0x30]
	cmp r1, #0xa
	blo _021DC89A
	mov r1, #7
	lsr r0, r0, #2
	lsl r1, r1, #0x12
	str r1, [sp, #0x10]
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [r4, #0x30]
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DC89A:
	ldr r0, [r4, #0x40]
	add r1, sp, #0xc
	bl FUN_02020044
	ldr r0, [r4, #0x40]
	add r1, sp, #0
	bl FUN_02020064
	mov r0, #0
	add sp, #0x18
	pop {r4, pc}
	.align 2, 0
_021DC8B0: .word 0x000001C7
	thumb_func_end MOD85_021DC848

	thumb_func_start MOD85_021DC8B4
MOD85_021DC8B4: ; 0x021DC8B4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	ldr r3, _021DC934 ; =0x021DF6AC
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0x18
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r3, _021DC938 ; =0x021DF61C
	str r0, [r2]
	add r2, sp, #0xc
	ldmia r3!, {r0, r1}
	add r6, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r5, sp, #0
	mov r7, #0
	str r7, [r5]
	str r0, [r2]
	add r3, r6, #0
	str r7, [r5, #4]
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	str r7, [r5, #8]
	add r2, #0x14
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r2, r4, #0
	ldmia r5!, {r0, r1}
	add r2, #0x20
	stmia r2!, {r0, r1}
	ldr r0, [r5]
	add r1, r6, #0
	str r0, [r2]
	str r7, [r4, #0x30]
	str r7, [r4, #0x34]
	str r7, [r4, #0x2c]
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #0x40]
	bl FUN_02020044
	ldr r0, [r4, #0x40]
	add r1, sp, #0x18
	bl FUN_02020064
	ldr r0, [r4, #0x40]
	add r1, r7, #0
	bl FUN_02020088
	ldr r0, [r4, #0x40]
	mov r1, #2
	bl FUN_02020130
	ldr r0, [r4, #0x40]
	bl FUN_02020198
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #1
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021DC934: .word MOD85_021DF6AC
_021DC938: .word MOD85_021DF61C
	thumb_func_end MOD85_021DC8B4

	thumb_func_start MOD85_021DC93C
MOD85_021DC93C: ; 0x021DC93C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x60
	ldr r3, _021DC9D8 ; =0x021DFA2C
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0x40
	add r6, r2, #0
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r3, _021DC9DC ; =0x021DFA4C
	add r2, sp, #0x20
	ldmia r3!, {r0, r1}
	add r5, r2, #0
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r3, _021DC9E0 ; =0x021DFA6C
	add r2, sp, #0
	add r7, r2, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r1, [r4, #0x34]
	ldr r0, [r4, #0x2c]
	lsl r1, r1, #2
	ldr r1, [r6, r1]
	add r0, r0, r1
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x34]
	ldr r1, [r4, #0x14]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r0, r1, r0
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x30]
	add r2, r0, #1
	str r2, [r4, #0x30]
	ldr r1, [r4, #0x34]
	lsl r0, r1, #2
	ldr r0, [r7, r0]
	cmp r2, r0
	blo _021DC9BC
	add r0, r1, #1
	str r0, [r4, #0x34]
	cmp r0, #8
	blt _021DC9B8
	mov r0, #0
	str r0, [r4, #0x34]
_021DC9B8:
	mov r0, #0
	str r0, [r4, #0x30]
_021DC9BC:
	add r1, r4, #0
	ldr r0, [r4, #0x40]
	add r1, #0x14
	bl FUN_02020044
	ldr r1, [r4, #0x2c]
	ldr r0, [r4, #0x40]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_02020088
	mov r0, #0
	add sp, #0x60
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DC9D8: .word MOD85_021DFA2C
_021DC9DC: .word MOD85_021DFA4C
_021DC9E0: .word MOD85_021DFA6C
	thumb_func_end MOD85_021DC93C

	thumb_func_start MOD85_021DC9E4
MOD85_021DC9E4: ; 0x021DC9E4
	push {r3, r4, r5, r6, lr}
	sub sp, #0x24
	ldr r3, _021DCA60 ; =0x021DF5F8
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0x18
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r5, _021DCA64 ; =0x021DF658
	str r0, [r2]
	add r2, sp, #0xc
	add r3, r2, #0
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r5]
	add r5, r4, #0
	str r0, [r2]
	add r2, sp, #0
	mov r0, #0
	str r0, [r2]
	str r0, [r2, #4]
	add r6, r3, #0
	str r0, [r2, #8]
	ldmia r6!, {r0, r1}
	add r5, #0x14
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	str r0, [r5]
	add r5, r4, #0
	ldmia r2!, {r0, r1}
	add r5, #0x20
	stmia r5!, {r0, r1}
	ldr r0, [r2]
	add r1, r3, #0
	str r0, [r5]
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #0x40]
	bl FUN_02020044
	ldr r0, [r4, #0x40]
	add r1, sp, #0x18
	bl FUN_02020064
	ldr r0, [r4, #0x40]
	mov r1, #0
	bl FUN_02020088
	ldr r0, [r4, #0x40]
	mov r1, #2
	bl FUN_02020130
	ldr r0, [r4, #0x40]
	bl FUN_02020198
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #1
	add sp, #0x24
	pop {r3, r4, r5, r6, pc}
	nop
_021DCA60: .word MOD85_021DF5F8
_021DCA64: .word MOD85_021DF658
	thumb_func_end MOD85_021DC9E4

	thumb_func_start MOD85_021DCA68
MOD85_021DCA68: ; 0x021DCA68
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r5, r1, #0
	ldr r4, [r6, #0x38]
	cmp r5, #5
	blt _021DCA78
	bl ErrorHandling
_021DCA78:
	mov r1, #2
	mov r2, #0x45
	ldr r7, _021DCAF0 ; =0x021DFB30
	lsl r3, r5, #4
	str r1, [sp]
	lsl r2, r2, #4
	ldr r0, [r4, r2]
	sub r2, #0x18
	add r5, r7, r3
	ldr r2, [r4, r2]
	ldr r3, [r7, r3]
	bl MOD85_021DE840
	mov r1, #2
	mov r2, #0x45
	str r1, [sp]
	lsl r2, r2, #4
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	ldr r3, [r5, #4]
	bl MOD85_021DE910
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	ldr r2, [r5, #8]
	mov r3, #2
	bl MOD85_021DE9E4
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	ldr r2, [r5, #0xc]
	mov r3, #2
	bl MOD85_021DEA4C
	ldr r0, _021DCAF4 ; =MOD85_021DCB18
	ldr r2, _021DCAF8 ; =0x00000101
	add r1, r6, #0
	bl FUN_0200CA60
	cmp r0, #0
	bne _021DCADC
	bl ErrorHandling
_021DCADC:
	ldr r0, _021DCAFC ; =MOD85_021DCB44
	ldr r2, _021DCAF8 ; =0x00000101
	add r1, r6, #0
	bl FUN_0200CA98
	cmp r0, #0
	bne _021DCAEE
	bl ErrorHandling
_021DCAEE:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DCAF0: .word MOD85_021DFB30
_021DCAF4: .word MOD85_021DCB18
_021DCAF8: .word 0x00000101
_021DCAFC: .word MOD85_021DCB44
	thumb_func_end MOD85_021DCA68

	thumb_func_start MOD85_021DCB00
MOD85_021DCB00: ; 0x021DCB00
	push {r3, lr}
	mov r1, #2
	mov r2, #0x45
	str r1, [sp]
	lsl r2, r2, #4
	ldr r0, [r0, r2]
	add r2, r1, #0
	add r3, r1, #0
	bl MOD85_021DEAB4
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD85_021DCB00

	thumb_func_start MOD85_021DCB18
MOD85_021DCB18: ; 0x021DCB18
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	mov r0, #0x45
	ldr r4, [r5, #0x38]
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #2
	bl MOD85_021DE8A8
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #2
	bl MOD85_021DE97C
	mov r0, #1
	str r0, [r5, #0xc]
	add r0, r6, #0
	bl FUN_0200CAB4
	pop {r4, r5, r6, pc}
	thumb_func_end MOD85_021DCB18

	thumb_func_start MOD85_021DCB44
MOD85_021DCB44: ; 0x021DCB44
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x38]
	cmp r0, #1
	bne _021DCB68
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #2
	bl MOD85_021DE9B0
	mov r0, #2
	str r0, [r4, #0xc]
	add r0, r5, #0
	bl FUN_0200CAB4
_021DCB68:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DCB44

	thumb_func_start MOD85_021DCB6C
MOD85_021DCB6C: ; 0x021DCB6C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x34
	add r5, r0, #0
	add r4, r1, #0
	add r1, sp, #0x28
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	ldr r6, _021DCBDC ; =0x021DF85C
	str r0, [r1, #8]
	ldmia r6!, {r0, r1}
	add r3, sp, #0x1c
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	add r1, r4, #0
	str r0, [r3]
	mov r0, #1
	str r0, [sp]
	mov r3, #2
	str r3, [sp, #4]
	str r3, [sp, #8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	str r3, [sp, #0x14]
	mov r0, #7
	str r0, [sp, #0x18]
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl MOD85_021DEC00
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_020200EC
	ldr r0, [r4, #4]
	add r1, sp, #0x28
	bl FUN_02020054
	ldr r0, [r4, #4]
	add r1, sp, #0x1c
	bl FUN_02020064
	mov r0, #0
	bl MathUtil_0201B9A0
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl FUN_02020088
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_020200BC
	add sp, #0x34
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021DCBDC: .word MOD85_021DF85C
	thumb_func_end MOD85_021DCB6C

	thumb_func_start MOD85_021DCBE0
MOD85_021DCBE0: ; 0x021DCBE0
	push {r4, r5, lr}
	sub sp, #0x14
	ldr r5, _021DCC0C ; =0x021DF6E8
	add r3, r0, #0
	ldmia r5!, {r0, r1}
	add r4, sp, #8
	add r2, r4, #0
	stmia r4!, {r0, r1}
	ldr r0, [r5]
	ldr r1, _021DCC10 ; =0x021DF8AC
	str r0, [r4]
	str r3, [sp]
	mov r0, #0x87
	str r0, [sp, #4]
	ldr r0, _021DCC14 ; =0x0000044C
	ldr r0, [r3, r0]
	mov r3, #0
	bl FUN_020644E4
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_021DCC0C: .word MOD85_021DF6E8
_021DCC10: .word MOD85_021DF8AC
_021DCC14: .word 0x0000044C
	thumb_func_end MOD85_021DCBE0

	thumb_func_start MOD85_021DCC18
MOD85_021DCC18: ; 0x021DCC18
	push {r4, lr}
	add r4, r1, #0
	bl FUN_0206475C
	str r0, [r4, #0x10]
	add r0, r4, #0
	bl MOD85_021DCD50
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD85_021DCC18

	thumb_func_start MOD85_021DCC2C
MOD85_021DCC2C: ; 0x021DCC2C
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _021DCC54
	mov r1, #3
	str r1, [sp]
	mov r0, #0x45
	ldr r2, [r4, #0x10]
	lsl r0, r0, #4
	ldr r0, [r2, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl MOD85_021DEAB4
	add r4, #0x14
	add r0, r4, #0
	bl MOD85_021DECA0
_021DCC54:
	add sp, #4
	pop {r3, r4, pc}
	thumb_func_end MOD85_021DCC2C

	thumb_func_start MOD85_021DCC58
MOD85_021DCC58: ; 0x021DCC58
	push {r4, lr}
	sub sp, #0x28
	add r4, r1, #0
	ldr r1, [r4]
	cmp r1, #3
	bhi _021DCCF4
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021DCC70: ; jump table
	.short _021DCC78 - _021DCC70 - 2 ; case 0
	.short _021DCCBA - _021DCC70 - 2 ; case 1
	.short _021DCCD2 - _021DCC70 - 2 ; case 2
	.short _021DCCF4 - _021DCC70 - 2 ; case 3
_021DCC78:
	ldr r1, [r4, #0xc]
	cmp r1, #2
	bne _021DCCF4
	add r1, sp, #0x1c
	bl FUN_0206477C
	mov r0, #1
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r3, #2
	str r3, [sp, #0x14]
	mov r0, #5
	str r0, [sp, #0x18]
	mov r0, #0x45
	ldr r1, [r4, #0x10]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, r4, #0
	add r1, #0x14
	add r2, sp, #0x1c
	bl MOD85_021DEC00
	ldr r0, [r4, #0x18]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021DCCBA:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0xf
	blo _021DCCF4
	ldr r0, [r4]
	add sp, #0x28
	add r0, r0, #1
	str r0, [r4]
	mov r0, #1
	str r0, [r4, #4]
	pop {r4, pc}
_021DCCD2:
	mov r1, #3
	str r1, [sp]
	mov r0, #0x45
	ldr r2, [r4, #0x10]
	lsl r0, r0, #4
	ldr r0, [r2, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl MOD85_021DEAB4
	add r0, r4, #0
	add r0, #0x14
	bl MOD85_021DECA0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021DCCF4:
	add sp, #0x28
	pop {r4, pc}
	thumb_func_end MOD85_021DCC58

	thumb_func_start MOD85_021DCCF8
MOD85_021DCCF8: ; 0x021DCCF8
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021DCCF8

	thumb_func_start MOD85_021DCCFC
MOD85_021DCCFC: ; 0x021DCCFC
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	mov r0, #0x45
	ldr r4, [r5, #0x10]
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #3
	bl MOD85_021DE8A8
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #3
	bl MOD85_021DE97C
	mov r0, #1
	str r0, [r5, #0xc]
	add r0, r6, #0
	bl FUN_0200CAB4
	pop {r4, r5, r6, pc}
	thumb_func_end MOD85_021DCCFC

	thumb_func_start MOD85_021DCD28
MOD85_021DCD28: ; 0x021DCD28
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	cmp r0, #1
	bne _021DCD4C
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #3
	bl MOD85_021DE9B0
	mov r0, #2
	str r0, [r4, #0xc]
	add r0, r5, #0
	bl FUN_0200CAB4
_021DCD4C:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DCD28

	thumb_func_start MOD85_021DCD50
MOD85_021DCD50: ; 0x021DCD50
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r2, #0x45
	ldr r4, [r5, #0x10]
	mov r0, #3
	lsl r2, r2, #4
	str r0, [sp]
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	mov r1, #2
	mov r3, #0x2c
	bl MOD85_021DE840
	mov r2, #0x45
	mov r0, #3
	lsl r2, r2, #4
	str r0, [sp]
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	mov r1, #2
	mov r3, #0x2f
	bl MOD85_021DE910
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x2d
	mov r3, #3
	bl MOD85_021DE9E4
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x2e
	mov r3, #3
	bl MOD85_021DEA4C
	ldr r0, _021DCDCC ; =MOD85_021DCCFC
	ldr r2, _021DCDD0 ; =0x00000101
	add r1, r5, #0
	bl FUN_0200CA60
	cmp r0, #0
	bne _021DCDB8
	bl ErrorHandling
_021DCDB8:
	ldr r0, _021DCDD4 ; =MOD85_021DCD28
	ldr r2, _021DCDD0 ; =0x00000101
	add r1, r5, #0
	bl FUN_0200CA98
	cmp r0, #0
	bne _021DCDCA
	bl ErrorHandling
_021DCDCA:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DCDCC: .word MOD85_021DCCFC
_021DCDD0: .word 0x00000101
_021DCDD4: .word MOD85_021DCD28
	thumb_func_end MOD85_021DCD50

	thumb_func_start MOD85_021DCDD8
MOD85_021DCDD8: ; 0x021DCDD8
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	mov r0, #0x45
	ldr r4, [r5, #0x20]
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #4
	bl MOD85_021DE8A8
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #4
	bl MOD85_021DE97C
	mov r0, #1
	str r0, [r5, #0x10]
	add r0, r6, #0
	bl FUN_0200CAB4
	pop {r4, r5, r6, pc}
	thumb_func_end MOD85_021DCDD8

	thumb_func_start MOD85_021DCE04
MOD85_021DCE04: ; 0x021DCE04
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x10]
	ldr r1, [r4, #0x20]
	cmp r0, #1
	bne _021DCE28
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #4
	bl MOD85_021DE9B0
	mov r0, #2
	str r0, [r4, #0x10]
	add r0, r5, #0
	bl FUN_0200CAB4
_021DCE28:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DCE04

	thumb_func_start MOD85_021DCE2C
MOD85_021DCE2C: ; 0x021DCE2C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x18]
	mov r2, #0x45
	lsl r3, r0, #4
	ldr r7, _021DCEB0 ; =0x021DFB00
	ldr r4, [r6, #0x20]
	mov r0, #4
	lsl r2, r2, #4
	str r0, [sp]
	ldr r0, [r4, r2]
	sub r2, #0x18
	add r5, r7, r3
	ldr r2, [r4, r2]
	ldr r3, [r7, r3]
	mov r1, #2
	bl MOD85_021DE840
	mov r2, #0x45
	mov r0, #4
	str r0, [sp]
	lsl r2, r2, #4
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	ldr r3, [r5, #4]
	mov r1, #2
	bl MOD85_021DE910
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	ldr r2, [r5, #8]
	mov r3, #4
	bl MOD85_021DE9E4
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	ldr r2, [r5, #0xc]
	mov r3, #4
	bl MOD85_021DEA4C
	ldr r0, _021DCEB4 ; =MOD85_021DCDD8
	ldr r2, _021DCEB8 ; =0x00000101
	add r1, r6, #0
	bl FUN_0200CA60
	cmp r0, #0
	bne _021DCE9C
	bl ErrorHandling
_021DCE9C:
	ldr r0, _021DCEBC ; =MOD85_021DCE04
	ldr r2, _021DCEB8 ; =0x00000101
	add r1, r6, #0
	bl FUN_0200CA98
	cmp r0, #0
	bne _021DCEAE
	bl ErrorHandling
_021DCEAE:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DCEB0: .word MOD85_021DFB00
_021DCEB4: .word MOD85_021DCDD8
_021DCEB8: .word 0x00000101
_021DCEBC: .word MOD85_021DCE04
	thumb_func_end MOD85_021DCE2C

	thumb_func_start MOD85_021DCEC0
MOD85_021DCEC0: ; 0x021DCEC0
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	ldr r6, _021DCEEC ; =0x021DF838
	add r5, sp, #8
	add r4, r0, #0
	add r3, r1, #0
	ldmia r6!, {r0, r1}
	add r2, r5, #0
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	ldr r1, _021DCEF0 ; =0x021DF8C0
	str r0, [r5]
	str r4, [sp]
	mov r0, #0x89
	str r0, [sp, #4]
	ldr r0, _021DCEF4 ; =0x0000044C
	ldr r0, [r4, r0]
	bl FUN_020644E4
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	nop
_021DCEEC: .word MOD85_021DF838
_021DCEF0: .word MOD85_021DF8C0
_021DCEF4: .word 0x0000044C
	thumb_func_end MOD85_021DCEC0

	thumb_func_start MOD85_021DCEF8
MOD85_021DCEF8: ; 0x021DCEF8
	push {r4, lr}
	add r4, r1, #0
	bl FUN_02064738
	str r4, [r0, #4]
	mov r1, #0
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	str r1, [r0, #0x14]
	pop {r4, pc}
	thumb_func_end MOD85_021DCEF8

	thumb_func_start MOD85_021DCF0C
MOD85_021DCF0C: ; 0x021DCF0C
	push {r3, lr}
	bl FUN_02064738
	ldr r0, [r0, #0xc]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD85_021DCF0C

	thumb_func_start MOD85_021DCF18
MOD85_021DCF18: ; 0x021DCF18
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0206475C
	str r0, [r4, #0x20]
	add r0, r5, #0
	bl FUN_02064754
	str r0, [r4, #0x18]
	add r0, r4, #0
	bl MOD85_021DCE2C
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DCF18

	thumb_func_start MOD85_021DCF38
MOD85_021DCF38: ; 0x021DCF38
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldr r0, [r4, #0x28]
	cmp r0, #0
	beq _021DCF60
	mov r1, #4
	str r1, [sp]
	mov r0, #0x45
	ldr r2, [r4, #0x20]
	lsl r0, r0, #4
	ldr r0, [r2, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl MOD85_021DEAB4
	add r4, #0x24
	add r0, r4, #0
	bl MOD85_021DECA0
_021DCF60:
	add sp, #4
	pop {r3, r4, pc}
	thumb_func_end MOD85_021DCF38

	thumb_func_start MOD85_021DCF64
MOD85_021DCF64: ; 0x021DCF64
	push {r3, r4, r5, lr}
	ldr r4, _021DCF80 ; =0x021DFA8C
	add r5, r1, #0
_021DCF6A:
	ldr r1, [r5, #4]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	ldr r1, [r5, #8]
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	blx r1
	cmp r0, #1
	beq _021DCF6A
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DCF80: .word MOD85_021DFA8C
	thumb_func_end MOD85_021DCF64

	thumb_func_start MOD85_021DCF84
MOD85_021DCF84: ; 0x021DCF84
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021DCF84

	thumb_func_start MOD85_021DCF88
MOD85_021DCF88: ; 0x021DCF88
	push {r4, r5, lr}
	sub sp, #0x34
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	cmp r0, #2
	bne _021DCFFA
	ldr r5, _021DD000 ; =0x021DF6D0
	add r3, sp, #0x28
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, sp, #0x1c
	str r0, [r3]
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	mov r0, #1
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r3, #2
	str r3, [sp, #0x14]
	mov r0, #6
	str r0, [sp, #0x18]
	mov r0, #0x45
	ldr r1, [r4, #0x20]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, r4, #0
	add r1, #0x24
	bl MOD85_021DEC00
	ldr r0, [r4, #0x28]
	mov r1, #2
	bl FUN_020200EC
	ldr r0, [r4, #0x28]
	add r1, sp, #0x1c
	bl FUN_02020054
	mov r0, #0
	bl MathUtil_0201B9A0
	add r1, r0, #0
	ldr r0, [r4, #0x28]
	bl FUN_02020088
	mov r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
_021DCFFA:
	mov r0, #0
	add sp, #0x34
	pop {r4, r5, pc}
	.align 2, 0
_021DD000: .word MOD85_021DF6D0
	thumb_func_end MOD85_021DCF88

	thumb_func_start MOD85_021DD004
MOD85_021DD004: ; 0x021DD004
	mov r0, #0
	bx lr
	thumb_func_end MOD85_021DD004

	thumb_func_start MOD85_021DD008
MOD85_021DD008: ; 0x021DD008
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r3, _021DD05C ; =0x021DF7FC
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r5, _021DD060 ; =0x021DF7F0
	str r0, [r2]
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r2, #0
	str r0, [r3]
	ldr r0, [r4, #0x28]
	bl FUN_02020064
	ldr r0, [r4, #0x28]
	add r1, sp, #0xc
	bl FUN_02020044
	ldr r0, [r4, #0x28]
	mov r1, #1
	bl FUN_02020130
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl FUN_020200D8
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl FUN_020200BC
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DD05C: .word MOD85_021DF7FC
_021DD060: .word MOD85_021DF7F0
	thumb_func_end MOD85_021DD008

	thumb_func_start MOD85_021DD064
MOD85_021DD064: ; 0x021DD064
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	add r1, sp, #0xc
	bl MOD85_021DECBC
	ldr r0, [r4, #0x28]
	add r1, sp, #0
	bl MOD85_021DECD0
	ldr r0, [sp]
	add r0, #0xc0
	str r0, [sp]
	ldr r0, [sp, #4]
	add r0, #0xc0
	str r0, [sp, #4]
	ldr r0, [r4, #0x14]
	add r0, r0, #1
	str r0, [r4, #0x14]
	cmp r0, #0x10
	blt _021DD0AE
	mov r0, #5
	lsl r0, r0, #0x12
	str r0, [sp, #0x10]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [r4, #0x14]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #0x23
	bl FUN_02005578
_021DD0AE:
	ldr r0, [r4, #0x28]
	add r1, sp, #0
	bl FUN_02020064
	ldr r0, [r4, #0x28]
	add r1, sp, #0xc
	bl FUN_02020044
	mov r0, #0
	add sp, #0x18
	pop {r4, pc}
	thumb_func_end MOD85_021DD064

	thumb_func_start MOD85_021DD0C4
MOD85_021DD0C4: ; 0x021DD0C4
	push {r4, lr}
	add r4, r0, #0
	mov r1, #1
	ldr r0, [r4, #0x28]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	ldr r0, [r4, #0x14]
	add r0, r0, #1
	str r0, [r4, #0x14]
	cmp r0, #9
	blt _021DD0EA
	mov r0, #0
	str r0, [r4, #0x14]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #1
	str r0, [r4, #0xc]
_021DD0EA:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DD0C4

	thumb_func_start MOD85_021DD0F0
MOD85_021DD0F0: ; 0x021DD0F0
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r3, _021DD14C ; =0x021DF7D8
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r5, _021DD150 ; =0x021DF7CC
	str r0, [r2]
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r2, #0
	str r0, [r3]
	ldr r0, [r4, #0x28]
	bl FUN_02020064
	ldr r0, [r4, #0x28]
	add r1, sp, #0xc
	bl FUN_02020044
	ldr r0, [r4, #0x28]
	mov r1, #1
	bl FUN_02020130
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl FUN_020200D8
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl FUN_020200BC
	ldr r0, _021DD154 ; =0x000006D1
	bl FUN_020054C8
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_021DD14C: .word MOD85_021DF7D8
_021DD150: .word MOD85_021DF7CC
_021DD154: .word 0x000006D1
	thumb_func_end MOD85_021DD0F0

	thumb_func_start MOD85_021DD158
MOD85_021DD158: ; 0x021DD158
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	add r1, sp, #0xc
	bl MOD85_021DECBC
	ldr r0, [r4, #0x28]
	add r1, sp, #0
	bl MOD85_021DECD0
	mov r0, #6
	ldr r1, [sp]
	lsl r0, r0, #6
	sub r1, r1, r0
	str r1, [sp]
	ldr r1, [sp, #4]
	sub r0, r1, r0
	str r0, [sp, #4]
	ldr r0, [r4, #0x14]
	add r0, r0, #1
	str r0, [r4, #0x14]
	cmp r0, #8
	blt _021DD1A4
	mov r0, #0x1d
	lsl r0, r0, #0x10
	str r0, [sp, #0x10]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [r4, #0x14]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #1
	str r0, [r4, #0xc]
_021DD1A4:
	ldr r0, [r4, #0x28]
	add r1, sp, #0
	bl FUN_02020064
	ldr r0, [r4, #0x28]
	add r1, sp, #0xc
	bl FUN_02020044
	mov r0, #0
	add sp, #0x18
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DD158

	thumb_func_start MOD85_021DD1BC
MOD85_021DD1BC: ; 0x021DD1BC
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r3, _021DD21C ; =0x021DF7B4
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r5, _021DD220 ; =0x021DF7A8
	str r0, [r2]
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r2, #0
	str r0, [r3]
	ldr r0, [r4, #0x28]
	bl FUN_02020064
	ldr r0, [r4, #0x28]
	add r1, sp, #0xc
	bl FUN_02020044
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl FUN_02020130
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl FUN_020200BC
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl FUN_020200D8
	ldr r0, [r4, #0x28]
	bl FUN_02020198
	mov r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_021DD21C: .word MOD85_021DF7B4
_021DD220: .word MOD85_021DF7A8
	thumb_func_end MOD85_021DD1BC

	thumb_func_start MOD85_021DD224
MOD85_021DD224: ; 0x021DD224
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r3, _021DD290 ; =0x021DF760
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r5, _021DD294 ; =0x021DF6DC
	str r0, [r2]
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r2, #0
	str r0, [r3]
	ldr r0, [r4, #0x28]
	bl FUN_02020064
	ldr r0, [r4, #0x28]
	add r1, sp, #0xc
	bl FUN_02020044
	ldr r0, [r4, #0x28]
	mov r1, #1
	bl FUN_020200BC
	mov r1, #2
	ldr r0, [r4, #0x28]
	lsl r1, r1, #0xa
	bl FUN_020200D8
	ldr r0, [r4, #0x28]
	bl FUN_020201DC
	cmp r0, #2
	beq _021DD27E
	ldr r0, [r4, #0x28]
	mov r1, #2
	bl FUN_02020130
	ldr r0, [r4, #0x28]
	bl FUN_02020198
_021DD27E:
	mov r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_021DD290: .word MOD85_021DF760
_021DD294: .word MOD85_021DF6DC
	thumb_func_end MOD85_021DD224

	thumb_func_start MOD85_021DD298
MOD85_021DD298: ; 0x021DD298
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r3, _021DD2F8 ; =0x021DF67C
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r5, _021DD2FC ; =0x021DF850
	str r0, [r2]
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r2, #0
	str r0, [r3]
	ldr r0, [r4, #0x28]
	bl FUN_02020064
	ldr r0, [r4, #0x28]
	add r1, sp, #0xc
	bl FUN_02020044
	ldr r0, [r4, #0x28]
	mov r1, #5
	bl FUN_02020130
	ldr r0, [r4, #0x28]
	mov r1, #1
	bl FUN_020200BC
	mov r1, #1
	ldr r0, [r4, #0x28]
	lsl r1, r1, #0xc
	bl FUN_020200D8
	ldr r0, [r4, #0x28]
	bl FUN_02020198
	mov r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DD2F8: .word MOD85_021DF67C
_021DD2FC: .word MOD85_021DF850
	thumb_func_end MOD85_021DD298

	thumb_func_start MOD85_021DD300
MOD85_021DD300: ; 0x021DD300
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r3, _021DD360 ; =0x021DF688
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r5, _021DD364 ; =0x021DF73C
	str r0, [r2]
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r2, #0
	str r0, [r3]
	ldr r0, [r4, #0x28]
	bl FUN_02020064
	ldr r0, [r4, #0x28]
	add r1, sp, #0xc
	bl FUN_02020044
	ldr r0, [r4, #0x28]
	mov r1, #4
	bl FUN_02020130
	ldr r0, [r4, #0x28]
	mov r1, #1
	bl FUN_020200BC
	mov r1, #1
	ldr r0, [r4, #0x28]
	lsl r1, r1, #0xc
	bl FUN_020200D8
	ldr r0, [r4, #0x28]
	bl FUN_02020198
	mov r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DD360: .word MOD85_021DF688
_021DD364: .word MOD85_021DF73C
	thumb_func_end MOD85_021DD300

	thumb_func_start MOD85_021DD368
MOD85_021DD368: ; 0x021DD368
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r3, _021DD3C8 ; =0x021DF718
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r5, _021DD3CC ; =0x021DF724
	str r0, [r2]
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r2, #0
	str r0, [r3]
	ldr r0, [r4, #0x28]
	bl FUN_02020064
	ldr r0, [r4, #0x28]
	add r1, sp, #0xc
	bl FUN_02020044
	ldr r0, [r4, #0x28]
	mov r1, #3
	bl FUN_02020130
	ldr r0, [r4, #0x28]
	mov r1, #1
	bl FUN_020200BC
	mov r1, #1
	ldr r0, [r4, #0x28]
	lsl r1, r1, #0xc
	bl FUN_020200D8
	ldr r0, [r4, #0x28]
	bl FUN_02020198
	mov r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DD3C8: .word MOD85_021DF718
_021DD3CC: .word MOD85_021DF724
	thumb_func_end MOD85_021DD368

	thumb_func_start MOD85_021DD3D0
MOD85_021DD3D0: ; 0x021DD3D0
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r3, _021DD434 ; =0x021DF778
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r5, _021DD438 ; =0x021DF604
	str r0, [r2]
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r2, #0
	str r0, [r3]
	ldr r0, [r4, #0x28]
	bl FUN_02020064
	ldr r0, [r4, #0x28]
	add r1, sp, #0xc
	bl FUN_02020044
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl FUN_020200BC
	mov r1, #1
	ldr r0, [r4, #0x28]
	lsl r1, r1, #0xc
	bl FUN_020200D8
	ldr r0, [r4, #0x28]
	mov r1, #5
	bl FUN_02020130
	ldr r0, [r4, #0x28]
	bl FUN_02020198
	mov r0, #0
	str r0, [r4, #0x14]
	mov r1, #1
	str r1, [r4, #0xc]
	ldr r1, [r4, #8]
	add r1, r1, #1
	str r1, [r4, #8]
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_021DD434: .word MOD85_021DF778
_021DD438: .word MOD85_021DF604
	thumb_func_end MOD85_021DD3D0

	thumb_func_start MOD85_021DD43C
MOD85_021DD43C: ; 0x021DD43C
	push {r4, lr}
	add r4, r0, #0
	mov r1, #1
	ldr r0, [r4, #0x28]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	ldr r0, [r4, #0x28]
	bl FUN_02020388
	cmp r0, #0
	bne _021DD468
	ldr r0, [r4, #0x14]
	add r0, r0, #1
	str r0, [r4, #0x14]
	cmp r0, #8
	blt _021DD468
	mov r0, #0
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x28]
	bl FUN_02020198
_021DD468:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD85_021DD43C

	thumb_func_start MOD85_021DD46C
MOD85_021DD46C: ; 0x021DD46C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	mov r0, #0x45
	ldr r4, [r5, #0x2c]
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #5
	bl MOD85_021DE8A8
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #5
	bl MOD85_021DE97C
	mov r0, #1
	str r0, [r5, #0x10]
	add r0, r6, #0
	bl FUN_0200CAB4
	pop {r4, r5, r6, pc}
	thumb_func_end MOD85_021DD46C

	thumb_func_start MOD85_021DD498
MOD85_021DD498: ; 0x021DD498
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4, #0x2c]
	add r5, r0, #0
	mov r0, #1
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _021DD4C0
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #5
	bl MOD85_021DE9B0
	mov r0, #2
	str r0, [r4, #0x10]
	add r0, r5, #0
	bl FUN_0200CAB4
_021DD4C0:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DD498

	thumb_func_start MOD85_021DD4C4
MOD85_021DD4C4: ; 0x021DD4C4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r2, #0x45
	ldr r4, [r5, #0x2c]
	mov r0, #5
	lsl r2, r2, #4
	str r0, [sp]
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	mov r1, #2
	mov r3, #0x38
	bl MOD85_021DE840
	mov r2, #0x45
	mov r0, #5
	lsl r2, r2, #4
	str r0, [sp]
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	mov r1, #2
	mov r3, #0x3b
	bl MOD85_021DE910
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x39
	mov r3, #5
	bl MOD85_021DE9E4
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x3a
	mov r3, #5
	bl MOD85_021DEA4C
	ldr r0, _021DD540 ; =MOD85_021DD46C
	ldr r2, _021DD544 ; =0x00000101
	add r1, r5, #0
	bl FUN_0200CA60
	cmp r0, #0
	bne _021DD52C
	bl ErrorHandling
_021DD52C:
	ldr r0, _021DD548 ; =MOD85_021DD498
	ldr r2, _021DD544 ; =0x00000101
	add r1, r5, #0
	bl FUN_0200CA98
	cmp r0, #0
	bne _021DD53E
	bl ErrorHandling
_021DD53E:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DD540: .word MOD85_021DD46C
_021DD544: .word 0x00000101
_021DD548: .word MOD85_021DD498
	thumb_func_end MOD85_021DD4C4

	thumb_func_start MOD85_021DD54C
MOD85_021DD54C: ; 0x021DD54C
	push {lr}
	sub sp, #0x14
	add r2, sp, #8
	mov r3, #0
	str r3, [r2]
	str r3, [r2, #4]
	str r3, [r2, #8]
	str r0, [sp]
	mov r1, #0x88
	str r1, [sp, #4]
	ldr r1, _021DD570 ; =0x0000044C
	ldr r0, [r0, r1]
	ldr r1, _021DD574 ; =0x021DF8D4
	bl FUN_020644E4
	add sp, #0x14
	pop {pc}
	nop
_021DD570: .word 0x0000044C
_021DD574: .word MOD85_021DF8D4
	thumb_func_end MOD85_021DD54C

	thumb_func_start MOD85_021DD578
MOD85_021DD578: ; 0x021DD578
	push {r3, lr}
	bl FUN_02064738
	ldr r0, [r0, #4]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD85_021DD578

	thumb_func_start MOD85_021DD584
MOD85_021DD584: ; 0x021DD584
	push {r4, lr}
	add r4, r1, #0
	bl FUN_0206475C
	str r0, [r4, #0x2c]
	add r0, r4, #0
	bl MOD85_021DD4C4
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD85_021DD584

	thumb_func_start MOD85_021DD598
MOD85_021DD598: ; 0x021DD598
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldr r0, [r4, #0x34]
	cmp r0, #0
	beq _021DD5CE
	mov r1, #5
	str r1, [sp]
	mov r0, #0x45
	ldr r2, [r4, #0x2c]
	lsl r0, r0, #4
	ldr r0, [r2, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl MOD85_021DEAB4
	add r0, r4, #0
	add r0, #0x30
	bl MOD85_021DECA0
	ldr r0, [r4, #0x40]
	cmp r0, #0
	beq _021DD5CE
	add r4, #0x3c
	add r0, r4, #0
	bl MOD85_021DECA0
_021DD5CE:
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD85_021DD598

	thumb_func_start MOD85_021DD5D4
MOD85_021DD5D4: ; 0x021DD5D4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r1, #0
	add r1, sp, #0xc
	add r7, r0, #0
	add r4, r2, #0
	add r6, r3, #0
	bl FUN_0206477C
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	add r0, r0, r6
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x30]
	add r0, r1, r0
	str r0, [sp, #0x10]
	add r0, r7, #0
	add r1, sp, #0xc
	bl FUN_0206476C
	ldr r0, [sp, #0x38]
	cmp r0, #0
	bne _021DD60A
	ldr r0, [sp, #0xc]
	add r0, r5, r0
	str r0, [sp]
	b _021DD610
_021DD60A:
	ldr r0, [sp, #0xc]
	sub r0, r5, r0
	str r0, [sp]
_021DD610:
	ldr r0, [sp, #0x10]
	add r1, sp, #0
	sub r0, r4, r0
	str r0, [sp, #4]
	ldr r0, [sp, #0x34]
	bl FUN_02020044
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021DD5D4

	thumb_func_start MOD85_021DD624
MOD85_021DD624: ; 0x021DD624
	push {r4, r5, r6, lr}
	sub sp, #0x40
	add r4, r1, #0
	ldr r1, [r4]
	add r6, r0, #0
	cmp r1, #0xa
	bls _021DD634
	b _021DD96C
_021DD634:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021DD640: ; jump table
	.short _021DD656 - _021DD640 - 2 ; case 0
	.short _021DD6C8 - _021DD640 - 2 ; case 1
	.short _021DD750 - _021DD640 - 2 ; case 2
	.short _021DD764 - _021DD640 - 2 ; case 3
	.short _021DD796 - _021DD640 - 2 ; case 4
	.short _021DD7C8 - _021DD640 - 2 ; case 5
	.short _021DD7FA - _021DD640 - 2 ; case 6
	.short _021DD842 - _021DD640 - 2 ; case 7
	.short _021DD858 - _021DD640 - 2 ; case 8
	.short _021DD8A4 - _021DD640 - 2 ; case 9
	.short _021DD904 - _021DD640 - 2 ; case 10
_021DD656:
	ldr r0, [r4, #0x10]
	cmp r0, #2
	beq _021DD65E
	b _021DD96C
_021DD65E:
	ldr r5, _021DD970 ; =0x021DF82C
	add r3, sp, #0x34
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	mov r0, #1
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r3, #2
	str r3, [sp, #0x14]
	mov r0, #4
	str r0, [sp, #0x18]
	mov r0, #0x45
	ldr r1, [r4, #0x2c]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, r4, #0
	add r1, #0x30
	bl MOD85_021DEC00
	mov r0, #1
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r3, #2
	str r3, [sp, #0x14]
	mov r0, #4
	str r0, [sp, #0x18]
	mov r0, #0x45
	ldr r1, [r4, #0x2c]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, r4, #0
	add r1, #0x3c
	add r2, sp, #0x34
	bl MOD85_021DEC00
	ldr r0, [r4, #0x40]
	mov r1, #1
	bl FUN_02020100
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021DD6C8:
	add r0, r6, #0
	add r1, sp, #0x28
	mov r5, #0
	bl FUN_0206477C
	mov r1, #2
	ldr r2, [sp, #0x2c]
	lsl r1, r1, #0xe
	ldr r0, [sp, #0x28]
	add r2, r2, r1
	add r0, r0, r1
	str r2, [sp, #0x2c]
	lsl r2, r1, #3
	str r0, [sp, #0x28]
	cmp r0, r2
	blt _021DD6EE
	add r0, r2, #0
	str r0, [sp, #0x28]
	add r5, r5, #1
_021DD6EE:
	mov r0, #0xe
	ldr r1, [sp, #0x2c]
	lsl r0, r0, #0xe
	cmp r1, r0
	blt _021DD700
	mov r0, #1
	lsl r0, r0, #0x12
	str r0, [sp, #0x2c]
	add r5, r5, #1
_021DD700:
	add r0, r6, #0
	add r1, sp, #0x28
	bl FUN_0206476C
	mov r0, #2
	ldr r1, [sp, #0x28]
	lsl r0, r0, #0x10
	sub r0, r1, r0
	str r0, [sp, #0x1c]
	mov r0, #0x69
	ldr r1, [sp, #0x2c]
	lsl r0, r0, #0xe
	sub r0, r0, r1
	str r0, [sp, #0x20]
	ldr r0, [r4, #0x34]
	add r1, sp, #0x1c
	bl FUN_02020044
	mov r0, #0x12
	ldr r1, [sp, #0x28]
	lsl r0, r0, #0x10
	sub r0, r0, r1
	str r0, [sp, #0x1c]
	mov r0, #0x69
	ldr r1, [sp, #0x2c]
	lsl r0, r0, #0xe
	sub r0, r0, r1
	str r0, [sp, #0x20]
	ldr r0, [r4, #0x40]
	add r1, sp, #0x1c
	bl FUN_02020044
	cmp r5, #2
	beq _021DD746
	b _021DD96C
_021DD746:
	ldr r0, [r4]
	add sp, #0x40
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_021DD750:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #8
	blo _021DD84C
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021DD764:
	ldr r3, _021DD974 ; =0xFFFFC000
	mov r2, #0x69
	str r3, [sp]
	ldr r0, [r4, #0x34]
	lsl r1, r3, #3
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r0, r6, #0
	lsl r2, r2, #0xe
	asr r3, r3, #1
	bl MOD85_021DD5D4
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #4
	blo _021DD84C
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4]
	add sp, #0x40
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_021DD796:
	mov r3, #1
	lsl r3, r3, #0xe
	str r3, [sp]
	ldr r1, [r4, #0x34]
	mov r2, #0x69
	str r1, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	ldr r1, _021DD978 ; =0xFFFE0000
	lsl r2, r2, #0xe
	lsr r3, r3, #1
	bl MOD85_021DD5D4
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #4
	blo _021DD84C
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4]
	add sp, #0x40
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_021DD7C8:
	ldr r3, _021DD974 ; =0xFFFFC000
	mov r2, #0x69
	str r3, [sp]
	ldr r1, [r4, #0x40]
	lsl r2, r2, #0xe
	str r1, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	mov r1, #0x12
	lsl r1, r1, #0x10
	asr r3, r3, #1
	bl MOD85_021DD5D4
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #4
	blo _021DD84C
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4]
	add sp, #0x40
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_021DD7FA:
	mov r1, #1
	lsl r1, r1, #0xe
	str r1, [sp]
	ldr r1, [r4, #0x40]
	mov r2, #0x69
	str r1, [sp, #4]
	mov r3, #1
	mov r1, #0x12
	str r3, [sp, #8]
	lsl r1, r1, #0x10
	lsl r2, r2, #0xe
	lsl r3, r3, #0xd
	bl MOD85_021DD5D4
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #4
	blo _021DD84C
	mov r1, #0
	str r1, [r4, #8]
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	cmp r0, #2
	bhs _021DD836
	mov r0, #3
	add sp, #0x40
	str r0, [r4]
	pop {r4, r5, r6, pc}
_021DD836:
	str r1, [r4, #0xc]
	ldr r0, [r4]
	add sp, #0x40
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_021DD842:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #8
	bhs _021DD84E
_021DD84C:
	b _021DD96C
_021DD84E:
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021DD858:
	ldr r3, _021DD974 ; =0xFFFFC000
	mov r2, #0x69
	str r3, [sp]
	ldr r0, [r4, #0x34]
	lsl r1, r3, #3
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r0, r6, #0
	lsl r2, r2, #0xe
	asr r3, r3, #1
	bl MOD85_021DD5D4
	mov r3, #0
	str r3, [sp]
	ldr r0, [r4, #0x40]
	mov r1, #0x12
	str r0, [sp, #4]
	mov r0, #1
	mov r2, #0x69
	str r0, [sp, #8]
	add r0, r6, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0xe
	bl MOD85_021DD5D4
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #4
	blo _021DD96C
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4]
	add sp, #0x40
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_021DD8A4:
	mov r3, #1
	lsl r3, r3, #0xe
	str r3, [sp]
	ldr r1, [r4, #0x34]
	mov r2, #0x69
	str r1, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	ldr r1, _021DD978 ; =0xFFFE0000
	lsl r2, r2, #0xe
	lsr r3, r3, #1
	bl MOD85_021DD5D4
	mov r3, #0
	str r3, [sp]
	ldr r0, [r4, #0x40]
	mov r1, #0x12
	str r0, [sp, #4]
	mov r0, #1
	mov r2, #0x69
	str r0, [sp, #8]
	add r0, r6, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0xe
	bl MOD85_021DD5D4
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #4
	blo _021DD96C
	mov r1, #0
	str r1, [r4, #8]
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	cmp r0, #2
	bhs _021DD8F8
	mov r0, #8
	add sp, #0x40
	str r0, [r4]
	pop {r4, r5, r6, pc}
_021DD8F8:
	str r1, [r4, #0xc]
	ldr r0, [r4]
	add sp, #0x40
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_021DD904:
	ldr r3, _021DD97C ; =0xFFFF8000
	mov r2, #0x69
	str r3, [sp]
	ldr r1, [r4, #0x34]
	lsl r2, r2, #0xe
	str r1, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	lsl r1, r3, #2
	bl MOD85_021DD5D4
	mov r3, #0
	str r3, [sp]
	ldr r0, [r4, #0x40]
	mov r1, #0x12
	str r0, [sp, #4]
	mov r0, #1
	mov r2, #0x69
	str r0, [sp, #8]
	add r0, r6, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0xe
	bl MOD85_021DD5D4
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #4
	blo _021DD962
	add r0, r4, #0
	add r0, #0x30
	bl MOD85_021DECA0
	add r0, r4, #0
	add r0, #0x3c
	bl MOD85_021DECA0
	mov r1, #5
	str r1, [sp]
	mov r0, #0x45
	ldr r2, [r4, #0x2c]
	lsl r0, r0, #4
	ldr r0, [r2, r0]
	add r2, r1, #0
	add r3, r1, #0
	bl MOD85_021DEAB4
_021DD962:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #1
	str r0, [r4, #4]
_021DD96C:
	add sp, #0x40
	pop {r4, r5, r6, pc}
	.align 2, 0
_021DD970: .word MOD85_021DF82C
_021DD974: .word 0xFFFFC000
_021DD978: .word 0xFFFE0000
_021DD97C: .word 0xFFFF8000
	thumb_func_end MOD85_021DD624

	thumb_func_start MOD85_021DD980
MOD85_021DD980: ; 0x021DD980
	bx lr
	.align 2, 0
	thumb_func_end MOD85_021DD980

	thumb_func_start MOD85_021DD984
MOD85_021DD984: ; 0x021DD984
	push {r4, r5, lr}
	sub sp, #0x14
	ldr r5, _021DD9B0 ; =0x021DF6B8
	add r3, r0, #0
	ldmia r5!, {r0, r1}
	add r4, sp, #8
	add r2, r4, #0
	stmia r4!, {r0, r1}
	ldr r0, [r5]
	ldr r1, _021DD9B4 ; =0x021DF8E8
	str r0, [r4]
	str r3, [sp]
	mov r0, #0x8e
	str r0, [sp, #4]
	ldr r0, _021DD9B8 ; =0x0000044C
	ldr r0, [r3, r0]
	mov r3, #0
	bl FUN_020644E4
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_021DD9B0: .word MOD85_021DF6B8
_021DD9B4: .word MOD85_021DF8E8
_021DD9B8: .word 0x0000044C
	thumb_func_end MOD85_021DD984

	thumb_func_start MOD85_021DD9BC
MOD85_021DD9BC: ; 0x021DD9BC
	push {r3, r4, r5, lr}
	sub sp, #0x28
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0206475C
	str r0, [r4]
	add r0, r5, #0
	add r1, sp, #0x1c
	bl FUN_0206477C
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r3, #2
	str r3, [sp, #0x14]
	mov r0, #3
	str r0, [sp, #0x18]
	mov r0, #0x45
	ldr r1, [r4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, r4, #4
	add r2, sp, #0x1c
	bl MOD85_021DEC00
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #1
	add sp, #0x28
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DD9BC

	thumb_func_start MOD85_021DDA08
MOD85_021DDA08: ; 0x021DDA08
	ldr r3, _021DDA10 ; =MOD85_021DECA0
	add r0, r1, #4
	bx r3
	nop
_021DDA10: .word MOD85_021DECA0
	thumb_func_end MOD85_021DDA08

	thumb_func_start MOD85_021DDA14
MOD85_021DDA14: ; 0x021DDA14
	mov r0, #0x52
	ldr r2, [r1]
	lsl r0, r0, #2
	ldr r0, [r2, r0]
	mov r3, #1
	cmp r0, #1
	bne _021DDA24
	mov r3, #0
_021DDA24:
	ldr r0, [r1, #8]
	add r1, r3, #0
	ldr r3, _021DDA2C ; =FUN_020200A0
	bx r3
	.align 2, 0
_021DDA2C: .word FUN_020200A0
	thumb_func_end MOD85_021DDA14

	thumb_func_start MOD85_021DDA30
MOD85_021DDA30: ; 0x021DDA30
	push {lr}
	sub sp, #0x14
	mov r1, #0x15
	lsl r1, r1, #0xe
	str r1, [sp, #8]
	mov r1, #0x13
	lsl r1, r1, #0x10
	str r1, [sp, #0xc]
	str r0, [sp]
	mov r1, #0x8e
	str r1, [sp, #4]
	ldr r1, _021DDA58 ; =0x0000044C
	add r2, sp, #8
	ldr r0, [r0, r1]
	ldr r1, _021DDA5C ; =0x021DF924
	mov r3, #0
	bl FUN_020644E4
	add sp, #0x14
	pop {pc}
	.align 2, 0
_021DDA58: .word 0x0000044C
_021DDA5C: .word MOD85_021DF924
	thumb_func_end MOD85_021DDA30

	thumb_func_start MOD85_021DDA60
MOD85_021DDA60: ; 0x021DDA60
	push {r3, r4, r5, lr}
	sub sp, #0x40
	add r5, r0, #0
	add r4, r1, #0
	add r1, sp, #0x28
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	ldr r3, _021DDAEC ; =0x021DF6A0
	str r0, [r1, #8]
	ldmia r3!, {r0, r1}
	add r2, sp, #0x1c
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, r5, #0
	bl FUN_0206475C
	str r0, [r4, #4]
	add r0, r5, #0
	add r1, sp, #0x34
	bl FUN_0206477C
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r3, #2
	str r3, [sp, #0x14]
	mov r0, #3
	str r0, [sp, #0x18]
	mov r0, #0x45
	ldr r1, [r4, #4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, r4, #0
	add r1, #8
	add r2, sp, #0x34
	bl MOD85_021DEC00
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl FUN_020200EC
	ldr r0, [r4, #0xc]
	add r1, sp, #0x28
	bl FUN_02020054
	ldr r0, [r4, #0xc]
	add r1, sp, #0x1c
	bl FUN_02020064
	mov r0, #0
	bl MathUtil_0201B9A0
	add r1, r0, #0
	ldr r0, [r4, #0xc]
	bl FUN_02020088
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #1
	add sp, #0x40
	pop {r3, r4, r5, pc}
	nop
_021DDAEC: .word MOD85_021DF6A0
	thumb_func_end MOD85_021DDA60

	thumb_func_start MOD85_021DDAF0
MOD85_021DDAF0: ; 0x021DDAF0
	ldr r3, _021DDAF8 ; =MOD85_021DECA0
	add r1, #8
	add r0, r1, #0
	bx r3
	.align 2, 0
_021DDAF8: .word MOD85_021DECA0
	thumb_func_end MOD85_021DDAF0

	thumb_func_start MOD85_021DDAFC
MOD85_021DDAFC: ; 0x021DDAFC
	push {r3, lr}
	ldr r2, [r1]
	add r2, r2, #1
	str r2, [r1]
	cmp r2, #0x2d
	blt _021DDB0C
	bl FUN_02064520
_021DDB0C:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD85_021DDAFC

	thumb_func_start MOD85_021DDB10
MOD85_021DDB10: ; 0x021DDB10
	push {r4, r5, lr}
	sub sp, #0x14
	ldr r5, _021DDB3C ; =0x021DF790
	add r3, r0, #0
	ldmia r5!, {r0, r1}
	add r4, sp, #8
	add r2, r4, #0
	stmia r4!, {r0, r1}
	ldr r0, [r5]
	ldr r1, _021DDB40 ; =0x021DF988
	str r0, [r4]
	str r3, [sp]
	mov r0, #0x8e
	str r0, [sp, #4]
	ldr r0, _021DDB44 ; =0x0000044C
	ldr r0, [r3, r0]
	mov r3, #0
	bl FUN_020644E4
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_021DDB3C: .word MOD85_021DF790
_021DDB40: .word MOD85_021DF988
_021DDB44: .word 0x0000044C
	thumb_func_end MOD85_021DDB10

	thumb_func_start MOD85_021DDB48
MOD85_021DDB48: ; 0x021DDB48
	push {r3, r4, r5, lr}
	sub sp, #0x28
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0206475C
	str r0, [r4]
	add r0, r5, #0
	add r1, sp, #0x1c
	bl FUN_0206477C
	mov r0, #0
	str r0, [sp]
	mov r1, #7
	str r1, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	mov r3, #2
	str r3, [sp, #0x14]
	mov r0, #3
	str r0, [sp, #0x18]
	mov r0, #0x45
	ldr r1, [r4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, r4, #4
	add r2, sp, #0x1c
	bl MOD85_021DEC00
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #1
	add sp, #0x28
	pop {r3, r4, r5, pc}
	thumb_func_end MOD85_021DDB48

	thumb_func_start MOD85_021DDB94
MOD85_021DDB94: ; 0x021DDB94
	ldr r3, _021DDB9C ; =MOD85_021DECA0
	add r0, r1, #4
	bx r3
	nop
_021DDB9C: .word MOD85_021DECA0
	thumb_func_end MOD85_021DDB94

	thumb_func_start MOD85_021DDBA0
MOD85_021DDBA0: ; 0x021DDBA0
	mov r0, #0x52
	ldr r2, [r1]
	lsl r0, r0, #2
	ldr r0, [r2, r0]
	mov r3, #1
	cmp r0, #1
	bne _021DDBB0
	mov r3, #0
_021DDBB0:
	ldr r0, [r1, #8]
	add r1, r3, #0
	ldr r3, _021DDBB8 ; =FUN_020200A0
	bx r3
	.align 2, 0
_021DDBB8: .word FUN_020200A0
	thumb_func_end MOD85_021DDBA0

	thumb_func_start MOD85_021DDBBC
MOD85_021DDBBC: ; 0x021DDBBC
	push {r4, r5, lr}
	sub sp, #0x14
	ldr r5, _021DDBF0 ; =0x021DF64C
	add r3, r0, #0
	ldmia r5!, {r0, r1}
	add r4, sp, #8
	add r2, r4, #0
	stmia r4!, {r0, r1}
	ldr r0, [r5]
	ldr r1, _021DDBF4 ; =0x021DF9B0
	str r0, [r4]
	mov r0, #0x11
	lsl r0, r0, #0xe
	str r0, [sp, #8]
	lsl r0, r0, #2
	str r0, [sp, #0xc]
	str r3, [sp]
	mov r0, #0x8e
	str r0, [sp, #4]
	ldr r0, _021DDBF8 ; =0x0000044C
	ldr r0, [r3, r0]
	mov r3, #0
	bl FUN_020644E4
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_021DDBF0: .word MOD85_021DF64C
_021DDBF4: .word MOD85_021DF9B0
_021DDBF8: .word 0x0000044C
	thumb_func_end MOD85_021DDBBC

	thumb_func_start MOD85_021DDBFC
MOD85_021DDBFC: ; 0x021DDBFC
	push {r3, r4, r5, lr}
	sub sp, #0x40
	add r5, r0, #0
	add r4, r1, #0
	add r1, sp, #0x28
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	ldr r3, _021DDC88 ; =0x021DF748
	str r0, [r1, #8]
	ldmia r3!, {r0, r1}
	add r2, sp, #0x1c
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, r5, #0
	bl FUN_0206475C
	str r0, [r4, #4]
	add r0, r5, #0
	add r1, sp, #0x34
	bl FUN_0206477C
	mov r0, #0
	str r0, [sp]
	mov r1, #7
	str r1, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	mov r3, #2
	str r3, [sp, #0x14]
	mov r0, #3
	str r0, [sp, #0x18]
	mov r0, #0x45
	ldr r1, [r4, #4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, r4, #0
	add r1, #8
	add r2, sp, #0x34
	bl MOD85_021DEC00
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl FUN_020200EC
	ldr r0, [r4, #0xc]
	add r1, sp, #0x28
	bl FUN_02020054
	ldr r0, [r4, #0xc]
	add r1, sp, #0x1c
	bl FUN_02020064
	mov r0, #0
	bl MathUtil_0201B9A0
	add r1, r0, #0
	ldr r0, [r4, #0xc]
	bl FUN_02020088
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #1
	add sp, #0x40
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DDC88: .word MOD85_021DF748
	thumb_func_end MOD85_021DDBFC

	thumb_func_start MOD85_021DDC8C
MOD85_021DDC8C: ; 0x021DDC8C
	ldr r3, _021DDC94 ; =MOD85_021DECA0
	add r1, #8
	add r0, r1, #0
	bx r3
	.align 2, 0
_021DDC94: .word MOD85_021DECA0
	thumb_func_end MOD85_021DDC8C

	thumb_func_start MOD85_021DDC98
MOD85_021DDC98: ; 0x021DDC98
	push {r3, lr}
	ldr r2, [r1]
	add r2, r2, #1
	str r2, [r1]
	cmp r2, #0x2d
	blt _021DDCA8
	bl FUN_02064520
_021DDCA8:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD85_021DDC98

	thumb_func_start MOD85_021DDCAC
MOD85_021DDCAC: ; 0x021DDCAC
	push {r4, r5, lr}
	sub sp, #0x14
	ldr r5, _021DDCD8 ; =0x021DF610
	add r3, r0, #0
	ldmia r5!, {r0, r1}
	add r4, sp, #8
	add r2, r4, #0
	stmia r4!, {r0, r1}
	ldr r0, [r5]
	ldr r1, _021DDCDC ; =0x021DF898
	str r0, [r4]
	str r3, [sp]
	mov r0, #0x8e
	str r0, [sp, #4]
	ldr r0, _021DDCE0 ; =0x0000044C
	ldr r0, [r3, r0]
	mov r3, #0
	bl FUN_020644E4
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_021DDCD8: .word MOD85_021DF610
_021DDCDC: .word MOD85_021DF898
_021DDCE0: .word 0x0000044C
	thumb_func_end MOD85_021DDCAC

	thumb_func_start MOD85_021DDCE4
MOD85_021DDCE4: ; 0x021DDCE4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r4, r0, #0
	add r7, r1, #0
	bl FUN_0206475C
	str r0, [r7]
	add r0, r4, #0
	add r1, sp, #0x1c
	bl FUN_0206477C
	mov r6, #0
	add r4, r7, #4
	add r5, r7, #0
_021DDD00:
	mov r0, #0
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #2
	str r0, [sp, #0x14]
	mov r0, #3
	str r0, [sp, #0x18]
	mov r0, #0x45
	ldr r1, [r7]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, r4, #0
	add r2, sp, #0x1c
	mov r3, #2
	bl MOD85_021DEC00
	ldr r0, [r5, #8]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r5, #8]
	mov r1, #1
	bl FUN_020200BC
	add r6, r6, #1
	add r4, #0xc
	add r5, #0xc
	cmp r6, #2
	blt _021DDD00
	mov r0, #1
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD85_021DDCE4

	thumb_func_start MOD85_021DDD4C
MOD85_021DDD4C: ; 0x021DDD4C
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #4
	bl MOD85_021DECA0
	add r4, #0x10
	add r0, r4, #0
	bl MOD85_021DECA0
	pop {r4, pc}
	thumb_func_end MOD85_021DDD4C

	thumb_func_start MOD85_021DDD60
MOD85_021DDD60: ; 0x021DDD60
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	mov r0, #0x4f
	ldr r1, [r5]
	lsl r0, r0, #2
	add r4, r1, r0
	ldr r0, [r5, #8]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r5, #0x14]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r4, #0xc]
	cmp r0, #1
	beq _021DDE06
	ldr r3, _021DDE0C ; =0x021DF76C
	add r2, sp, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r6, #0
	str r0, [r2]
	ldr r0, [r5]
	ldr r7, [r0, #0x10]
	cmp r7, #0x63
	bls _021DDD9C
	mov r7, #0x63
_021DDD9C:
	add r0, r7, #0
	mov r1, #0x64
	bl _u32_div_f
	add r0, r1, #0
	mov r1, #0xa
	bl _u32_div_f
	add r4, r0, #0
	beq _021DDDDA
	ldr r0, [r5, #8]
	add r1, sp, #0
	bl FUN_02020044
	ldr r0, [r5, #8]
	add r1, r4, #0
	bl FUN_02020130
	ldr r0, [r5, #8]
	bl FUN_02020198
	ldr r0, [r5, #8]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #2
	ldr r1, [sp]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp]
	add r6, r6, #1
_021DDDDA:
	mov r0, #0xc
	add r4, r6, #0
	add r5, #8
	mul r4, r0
	ldr r0, [r5, r4]
	add r1, sp, #0
	bl FUN_02020044
	add r0, r7, #0
	mov r1, #0xa
	bl _u32_div_f
	ldr r0, [r5, r4]
	bl FUN_02020130
	ldr r0, [r5, r4]
	bl FUN_02020198
	ldr r0, [r5, r4]
	mov r1, #1
	bl FUN_020200A0
_021DDE06:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_021DDE0C: .word MOD85_021DF76C
	thumb_func_end MOD85_021DDD60

	thumb_func_start MOD85_021DDE10
MOD85_021DDE10: ; 0x021DDE10
	push {r4, r5, lr}
	sub sp, #0x14
	ldr r5, _021DDE3C ; =0x021DF844
	add r3, r0, #0
	ldmia r5!, {r0, r1}
	add r4, sp, #8
	add r2, r4, #0
	stmia r4!, {r0, r1}
	ldr r0, [r5]
	ldr r1, _021DDE40 ; =0x021DF8FC
	str r0, [r4]
	str r3, [sp]
	mov r0, #0x8e
	str r0, [sp, #4]
	ldr r0, _021DDE44 ; =0x0000044C
	ldr r0, [r3, r0]
	mov r3, #0
	bl FUN_020644E4
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_021DDE3C: .word MOD85_021DF844
_021DDE40: .word MOD85_021DF8FC
_021DDE44: .word 0x0000044C
	thumb_func_end MOD85_021DDE10

	thumb_func_start MOD85_021DDE48
MOD85_021DDE48: ; 0x021DDE48
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	ldr r3, _021DDEAC ; =0x021DF6C4
	add r4, r0, #0
	add r6, r1, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0x1c
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, r4, #0
	bl FUN_0206475C
	str r0, [r6]
	mov r4, #0
	add r5, r6, #4
	mov r7, #2
_021DDE6A:
	mov r0, #0
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r7, [sp, #0x14]
	mov r0, #3
	str r0, [sp, #0x18]
	mov r0, #0x45
	ldr r1, [r6]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, r5, #0
	add r2, sp, #0x1c
	add r3, r7, #0
	bl MOD85_021DEC00
	mov r0, #2
	ldr r1, [sp, #0x1c]
	lsl r0, r0, #0xe
	add r0, r1, r0
	add r4, r4, #1
	add r5, #0xc
	str r0, [sp, #0x1c]
	cmp r4, #5
	blt _021DDE6A
	mov r0, #1
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DDEAC: .word MOD85_021DF6C4
	thumb_func_end MOD85_021DDE48

	thumb_func_start MOD85_021DDEB0
MOD85_021DDEB0: ; 0x021DDEB0
	push {r3, r4, r5, lr}
	mov r4, #0
	add r5, r1, #4
_021DDEB6:
	add r0, r5, #0
	bl MOD85_021DECA0
	add r4, r4, #1
	add r5, #0xc
	cmp r4, #5
	blt _021DDEB6
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DDEB0

	thumb_func_start MOD85_021DDEC8
MOD85_021DDEC8: ; 0x021DDEC8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	mov r0, #0x52
	ldr r1, [r5]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r7, #1
	cmp r0, #1
	bne _021DDEDC
	mov r7, #0
_021DDEDC:
	mov r6, #0
	add r4, r5, #0
_021DDEE0:
	ldr r0, [r4, #8]
	add r1, r7, #0
	bl FUN_020200A0
	add r6, r6, #1
	add r4, #0xc
	cmp r6, #5
	blt _021DDEE0
	cmp r7, #0
	beq _021DDF34
	ldr r0, [r5]
	ldr r6, [r0, #0x14]
	ldr r0, _021DDF38 ; =0x0000C350
	cmp r6, r0
	ble _021DDF00
	add r6, r0, #0
_021DDF00:
	ldr r4, _021DDF3C ; =0x00002710
	mov r7, #0xa
_021DDF04:
	add r1, r4, #0
	add r0, r6, #0
	mul r1, r7
	bl _s32_div_f
	add r0, r1, #0
	add r1, r4, #0
	bl _s32_div_f
	add r1, r0, #0
	ldr r0, [r5, #8]
	bl FUN_02020130
	ldr r0, [r5, #8]
	bl FUN_02020198
	add r0, r4, #0
	mov r1, #0xa
	bl _s32_div_f
	add r4, r0, #0
	add r5, #0xc
	cmp r4, #1
	bge _021DDF04
_021DDF34:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DDF38: .word 0x0000C350
_021DDF3C: .word 0x00002710
	thumb_func_end MOD85_021DDEC8

	thumb_func_start MOD85_021DDF40
MOD85_021DDF40: ; 0x021DDF40
	push {lr}
	sub sp, #0x14
	add r3, r1, #0
	add r2, sp, #8
	mov r1, #0
	str r1, [r2]
	str r1, [r2, #4]
	str r1, [r2, #8]
	str r0, [sp]
	mov r1, #0x8e
	str r1, [sp, #4]
	ldr r1, _021DDF64 ; =0x0000044C
	ldr r0, [r0, r1]
	ldr r1, _021DDF68 ; =0x021DF99C
	bl FUN_020644E4
	add sp, #0x14
	pop {pc}
	.align 2, 0
_021DDF64: .word 0x0000044C
_021DDF68: .word MOD85_021DF99C
	thumb_func_end MOD85_021DDF40

	thumb_func_start MOD85_021DDF6C
MOD85_021DDF6C: ; 0x021DDF6C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	add r6, r0, #0
	add r5, r1, #0
	add r1, sp, #0x2c
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	ldr r3, _021DE0D0 ; =0x021DF79C
	str r0, [r1, #8]
	ldmia r3!, {r0, r1}
	add r2, sp, #0x20
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, r6, #0
	bl FUN_0206475C
	add r4, r0, #0
	add r0, r6, #0
	bl FUN_02064754
	str r0, [r5]
	str r4, [r5, #0x14]
	ldr r0, [r5]
	cmp r0, #0
	bne _021DDFD6
	ldr r1, [r4, #0x1c]
	ldr r0, _021DE0D4 ; =0x000003E7
	str r1, [r5, #4]
	cmp r1, r0
	bls _021DDFAE
	str r0, [r5, #4]
_021DDFAE:
	ldr r0, [r5, #4]
	cmp r0, #0x64
	blo _021DDFBA
	mov r0, #3
	str r0, [r5, #8]
	b _021DDFC8
_021DDFBA:
	cmp r0, #0xa
	blo _021DDFC4
	mov r0, #2
	str r0, [r5, #8]
	b _021DDFC8
_021DDFC4:
	mov r0, #1
	str r0, [r5, #8]
_021DDFC8:
	mov r0, #0x32
	lsl r0, r0, #0xe
	str r0, [sp, #0x38]
	mov r0, #0x13
	lsl r0, r0, #0x10
	str r0, [sp, #0x3c]
	b _021DE022
_021DDFD6:
	ldr r1, [r4, #0x14]
	ldr r0, _021DE0D8 ; =0x0001869F
	str r1, [r5, #4]
	cmp r1, r0
	bls _021DDFE2
	str r0, [r5, #4]
_021DDFE2:
	ldr r1, [r5, #4]
	ldr r0, _021DE0DC ; =0x00002710
	cmp r1, r0
	blo _021DDFF0
	mov r0, #5
	str r0, [r5, #8]
	b _021DE016
_021DDFF0:
	mov r0, #0xfa
	lsl r0, r0, #2
	cmp r1, r0
	blo _021DDFFE
	mov r0, #4
	str r0, [r5, #8]
	b _021DE016
_021DDFFE:
	cmp r1, #0x64
	blo _021DE008
	mov r0, #3
	str r0, [r5, #8]
	b _021DE016
_021DE008:
	cmp r1, #0xa
	blo _021DE012
	mov r0, #2
	str r0, [r5, #8]
	b _021DE016
_021DE012:
	mov r0, #1
	str r0, [r5, #8]
_021DE016:
	mov r0, #0x32
	lsl r0, r0, #0xe
	str r0, [sp, #0x38]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #0x3c]
_021DE022:
	ldr r0, [r5, #8]
	mov r7, #0
	mov r6, #1
	cmp r0, #0
	bls _021DE0C6
	add r0, r5, #0
	str r0, [sp, #0x1c]
	add r0, #0x18
	str r0, [sp, #0x1c]
	add r4, r5, #0
_021DE036:
	mov r0, #0
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #2
	str r0, [sp, #0x14]
	mov r0, #3
	str r0, [sp, #0x18]
	mov r0, #0x45
	ldr r1, [r5, #0x14]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	ldr r1, [sp, #0x1c]
	add r2, sp, #0x38
	mov r3, #2
	bl MOD85_021DEC00
	ldr r0, [r4, #0x1c]
	mov r1, #2
	bl FUN_020200EC
	ldr r0, [r4, #0x1c]
	add r1, sp, #0x2c
	bl FUN_02020054
	ldr r0, [r4, #0x1c]
	add r1, sp, #0x20
	bl FUN_02020064
	mov r0, #0
	bl MathUtil_0201B9A0
	add r1, r0, #0
	ldr r0, [r4, #0x1c]
	bl FUN_02020088
	mov r1, #0xa
	ldr r0, [r5, #4]
	mul r1, r6
	bl _u32_div_f
	add r0, r1, #0
	add r1, r6, #0
	bl _u32_div_f
	add r1, r0, #0
	ldr r0, [r4, #0x1c]
	bl FUN_02020130
	ldr r0, [r4, #0x1c]
	bl FUN_02020198
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x38]
	add r0, #0xc
	str r0, [sp, #0x1c]
	mov r0, #0xa
	mul r6, r0
	mov r0, #1
	lsl r0, r0, #0x10
	sub r0, r1, r0
	str r0, [sp, #0x38]
	ldr r0, [r5, #8]
	add r7, r7, #1
	add r4, #0xc
	cmp r7, r0
	blo _021DE036
_021DE0C6:
	str r7, [r5, #0x10]
	mov r0, #1
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	nop
_021DE0D0: .word MOD85_021DF79C
_021DE0D4: .word 0x000003E7
_021DE0D8: .word 0x0001869F
_021DE0DC: .word 0x00002710
	thumb_func_end MOD85_021DDF6C

	thumb_func_start MOD85_021DE0E0
MOD85_021DE0E0: ; 0x021DE0E0
	push {r4, r5, r6, lr}
	add r6, r1, #0
	ldr r0, [r6, #0x10]
	mov r4, #0
	cmp r0, #0
	ble _021DE100
	add r5, r6, #0
	add r5, #0x18
_021DE0F0:
	add r0, r5, #0
	bl MOD85_021DECA0
	ldr r0, [r6, #0x10]
	add r4, r4, #1
	add r5, #0xc
	cmp r4, r0
	blt _021DE0F0
_021DE100:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD85_021DE0E0

	thumb_func_start MOD85_021DE104
MOD85_021DE104: ; 0x021DE104
	push {r3, lr}
	ldr r2, [r1, #0xc]
	add r2, r2, #1
	str r2, [r1, #0xc]
	cmp r2, #0x2d
	blt _021DE114
	bl FUN_02064520
_021DE114:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD85_021DE104

	thumb_func_start MOD85_021DE118
MOD85_021DE118: ; 0x021DE118
	push {r4, r5, lr}
	sub sp, #0x14
	ldr r5, _021DE14C ; =0x021DF664
	add r2, r0, #0
	add r3, r1, #0
	ldmia r5!, {r0, r1}
	add r4, sp, #8
	stmia r4!, {r0, r1}
	ldr r0, [r5]
	str r0, [r4]
	ldr r0, _021DE150 ; =0x000003E7
	cmp r3, r0
	bls _021DE134
	add r3, r0, #0
_021DE134:
	str r2, [sp]
	mov r0, #0x8e
	str r0, [sp, #4]
	ldr r0, _021DE154 ; =0x0000044C
	ldr r1, _021DE158 ; =0x021DF9C4
	ldr r0, [r2, r0]
	add r2, sp, #8
	bl FUN_020644E4
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_021DE14C: .word MOD85_021DF664
_021DE150: .word 0x000003E7
_021DE154: .word 0x0000044C
_021DE158: .word MOD85_021DF9C4
	thumb_func_end MOD85_021DE118

	thumb_func_start MOD85_021DE15C
MOD85_021DE15C: ; 0x021DE15C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r4, r0, #0
	add r5, r1, #0
	bl FUN_0206475C
	str r0, [r5, #8]
	add r0, r4, #0
	bl FUN_02064754
	str r0, [sp, #0x20]
	add r0, r4, #0
	add r1, sp, #0x24
	bl FUN_0206477C
	ldr r0, [sp, #0x20]
	cmp r0, #0x64
	blo _021DE192
	mov r0, #3
	str r0, [r5, #4]
	mov r0, #1
	ldr r1, [sp, #0x24]
	lsl r0, r0, #0x10
	sub r0, r1, r0
	mov r4, #0x64
	str r0, [sp, #0x24]
	b _021DE1AA
_021DE192:
	cmp r0, #0xa
	blo _021DE1A6
	mov r0, #2
	str r0, [r5, #4]
	ldr r1, [sp, #0x24]
	lsl r0, r0, #0xe
	sub r0, r1, r0
	mov r4, #0xa
	str r0, [sp, #0x24]
	b _021DE1AA
_021DE1A6:
	mov r4, #1
	str r4, [r5, #4]
_021DE1AA:
	ldr r0, [r5, #4]
	mov r6, #0
	cmp r0, #0
	ble _021DE226
	add r0, r5, #0
	str r0, [sp, #0x1c]
	add r0, #0xc
	str r0, [sp, #0x1c]
	add r7, r5, #0
_021DE1BC:
	mov r0, #0
	str r0, [sp]
	mov r0, #9
	str r0, [sp, #4]
	mov r0, #7
	str r0, [sp, #8]
	mov r0, #9
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #2
	str r0, [sp, #0x14]
	mov r0, #3
	str r0, [sp, #0x18]
	mov r0, #0x45
	ldr r1, [r5, #8]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	ldr r1, [sp, #0x1c]
	add r2, sp, #0x24
	mov r3, #2
	bl MOD85_021DEC00
	mov r1, #0xa
	ldr r0, [sp, #0x20]
	mul r1, r4
	bl _u32_div_f
	add r0, r1, #0
	add r1, r4, #0
	bl _u32_div_f
	add r1, r0, #0
	ldr r0, [r7, #0x10]
	bl FUN_02020130
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x24]
	add r0, #0xc
	str r0, [sp, #0x1c]
	mov r0, #1
	lsl r0, r0, #0x10
	add r0, r1, r0
	str r0, [sp, #0x24]
	add r0, r4, #0
	mov r1, #0xa
	add r7, #0xc
	add r6, r6, #1
	bl _u32_div_f
	add r4, r0, #0
	ldr r0, [r5, #4]
	cmp r6, r0
	blt _021DE1BC
_021DE226:
	mov r0, #1
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD85_021DE15C

	thumb_func_start MOD85_021DE22C
MOD85_021DE22C: ; 0x021DE22C
	push {r4, r5, r6, lr}
	add r6, r1, #0
	ldr r0, [r6, #4]
	mov r4, #0
	cmp r0, #0
	ble _021DE24C
	add r5, r6, #0
	add r5, #0xc
_021DE23C:
	add r0, r5, #0
	bl MOD85_021DECA0
	ldr r0, [r6, #4]
	add r4, r4, #1
	add r5, #0xc
	cmp r4, r0
	blt _021DE23C
_021DE24C:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD85_021DE22C

	thumb_func_start MOD85_021DE250
MOD85_021DE250: ; 0x021DE250
	push {r3, lr}
	ldr r2, [r1]
	add r2, r2, #1
	str r2, [r1]
	cmp r2, #0x3c
	blt _021DE260
	bl FUN_02064520
_021DE260:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD85_021DE250

	thumb_func_start MOD85_021DE264
MOD85_021DE264: ; 0x021DE264
	push {lr}
	sub sp, #0x14
	add r2, sp, #8
	mov r3, #0
	str r3, [r2]
	str r3, [r2, #4]
	str r3, [r2, #8]
	str r0, [sp]
	mov r1, #0x8c
	str r1, [sp, #4]
	ldr r1, _021DE288 ; =0x0000044C
	ldr r0, [r0, r1]
	ldr r1, _021DE28C ; =0x021DF910
	bl FUN_020644E4
	add sp, #0x14
	pop {pc}
	nop
_021DE288: .word 0x0000044C
_021DE28C: .word MOD85_021DF910
	thumb_func_end MOD85_021DE264

	thumb_func_start MOD85_021DE290
MOD85_021DE290: ; 0x021DE290
	push {r4, lr}
	add r4, r1, #0
	bl FUN_0206475C
	str r0, [r4, #0x44]
	ldr r0, [r0, #0x44]
	add r3, r4, #0
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x44]
	add r3, #0x1c
	ldr r0, [r0, #0x48]
	mov r1, #1
_021DE2A8:
	add r2, r0, #0
	tst r2, r1
	bne _021DE2BC
	ldr r2, [r3]
	lsr r0, r0, #1
	add r2, r2, #1
	str r2, [r3]
	ldr r2, [r4, #0x1c]
	cmp r2, #5
	blt _021DE2A8
_021DE2BC:
	ldr r0, [r4, #0x1c]
	cmp r0, #5
	blt _021DE2C6
	bl ErrorHandling
_021DE2C6:
	add r0, r4, #0
	bl MOD85_021DE4F0
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD85_021DE290

	thumb_func_start MOD85_021DE2D0
MOD85_021DE2D0: ; 0x021DE2D0
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	ldr r0, [r7, #0x14]
	cmp r0, #0
	bne _021DE30C
	add r5, r7, #0
	mov r6, #0
	add r4, r7, #0
	add r5, #0x20
_021DE2E2:
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _021DE2EE
	add r0, r5, #0
	bl MOD85_021DECA0
_021DE2EE:
	add r6, r6, #1
	add r4, #0xc
	add r5, #0xc
	cmp r6, #3
	blt _021DE2E2
	mov r1, #0xa
	str r1, [sp]
	mov r0, #0x45
	ldr r2, [r7, #0x44]
	lsl r0, r0, #4
	ldr r0, [r2, r0]
	mov r2, #8
	add r3, r1, #0
	bl MOD85_021DEAB4
_021DE30C:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021DE2D0

	thumb_func_start MOD85_021DE310
MOD85_021DE310: ; 0x021DE310
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r5, r1, #0
	ldr r0, [r5]
	cmp r0, #5
	bhi _021DE33A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DE328: ; jump table
	.short _021DE334 - _021DE328 - 2 ; case 0
	.short _021DE3AE - _021DE328 - 2 ; case 1
	.short _021DE3F8 - _021DE328 - 2 ; case 2
	.short _021DE410 - _021DE328 - 2 ; case 3
	.short _021DE454 - _021DE328 - 2 ; case 4
	.short _021DE46C - _021DE328 - 2 ; case 5
_021DE334:
	ldr r0, [r5, #8]
	cmp r0, #2
	beq _021DE33C
_021DE33A:
	b _021DE4A0
_021DE33C:
	mov r4, #0
	add r7, r5, #0
	str r4, [sp, #0x20]
	add r7, #0x20
	add r6, r5, #0
_021DE346:
	ldr r1, [r5, #0x1c]
	mov r0, #0x24
	add r2, r1, #0
	mul r2, r0
	ldr r0, _021DE4A4 ; =0x021DFB80
	add r0, r0, r2
	add r3, r4, r0
	add r2, sp, #0x24
	ldmia r3!, {r0, r1}
	mov ip, r2
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r3, #3
	str r0, [r2]
	mov r0, #0
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	mov r0, #0x45
	ldr r1, [r5, #0x44]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, r7, #0
	mov r2, ip
	bl MOD85_021DEC00
	ldr r0, [r6, #0x24]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [sp, #0x20]
	add r4, #0xc
	add r0, r0, #1
	add r7, #0xc
	add r6, #0xc
	str r0, [sp, #0x20]
	cmp r0, #3
	blt _021DE346
	ldr r0, [r5]
	add sp, #0x30
	add r0, r0, #1
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021DE3AE:
	mov r6, #0
	str r6, [sp, #0x1c]
	add r4, r5, #0
	add r7, sp, #0x24
_021DE3B6:
	ldr r0, [r4, #0x24]
	add r1, r7, #0
	bl MOD85_021DECBC
	mov r0, #1
	ldr r1, [sp, #0x28]
	lsl r0, r0, #0xe
	add r1, r1, r0
	mov r0, #0xf
	lsl r0, r0, #0x10
	str r1, [sp, #0x28]
	cmp r1, r0
	blt _021DE3D4
	str r0, [sp, #0x28]
	b _021DE3D8
_021DE3D4:
	mov r0, #1
	str r0, [sp, #0x1c]
_021DE3D8:
	ldr r0, [r4, #0x24]
	add r1, r7, #0
	bl FUN_02020044
	add r6, r6, #1
	add r4, #0xc
	cmp r6, #3
	blt _021DE3B6
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	bne _021DE4A0
	ldr r0, [r5]
	add sp, #0x30
	add r0, r0, #1
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021DE3F8:
	ldr r0, [r5, #0xc]
	add r0, r0, #1
	str r0, [r5, #0xc]
	cmp r0, #0x1e
	blt _021DE4A0
	mov r0, #0
	str r0, [r5, #0xc]
	ldr r0, [r5]
	add sp, #0x30
	add r0, r0, #1
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021DE410:
	ldr r0, [r5, #0xc]
	add r0, r0, #1
	str r0, [r5, #0xc]
	cmp r0, #0xc
	blt _021DE41E
	mov r7, #1
	b _021DE420
_021DE41E:
	mov r7, #0
_021DE420:
	mov r6, #0
	add r4, r5, #0
_021DE424:
	ldr r0, [r4, #0x24]
	add r1, r7, #0
	bl FUN_020200A0
	add r6, r6, #1
	add r4, #0xc
	cmp r6, #3
	blt _021DE424
	ldr r0, [r5, #0xc]
	cmp r0, #0x1e
	blt _021DE4A0
	mov r1, #0
	str r1, [r5, #0xc]
	ldr r0, [r5, #0x10]
	add r0, r0, #1
	str r0, [r5, #0x10]
	cmp r0, #3
	blt _021DE4A0
	str r1, [r5, #0x10]
	ldr r0, [r5]
	add sp, #0x30
	add r0, r0, #1
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021DE454:
	ldr r0, [r5, #0xc]
	add r0, r0, #1
	str r0, [r5, #0xc]
	cmp r0, #0x1e
	blt _021DE4A0
	mov r0, #0
	str r0, [r5, #0xc]
	ldr r0, [r5]
	add sp, #0x30
	add r0, r0, #1
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021DE46C:
	add r4, r5, #0
	mov r6, #0
	add r4, #0x20
_021DE472:
	add r0, r4, #0
	bl MOD85_021DECA0
	add r6, r6, #1
	add r4, #0xc
	cmp r6, #3
	blt _021DE472
	mov r1, #0xa
	str r1, [sp]
	mov r0, #0x45
	ldr r2, [r5, #0x44]
	lsl r0, r0, #4
	ldr r0, [r2, r0]
	mov r2, #8
	add r3, r1, #0
	bl MOD85_021DEAB4
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	mov r0, #1
	str r0, [r5, #4]
	str r0, [r5, #0x14]
_021DE4A0:
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DE4A4: .word MOD85_021DFB80
	thumb_func_end MOD85_021DE310

	thumb_func_start MOD85_021DE4A8
MOD85_021DE4A8: ; 0x021DE4A8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	mov r0, #0x45
	ldr r1, [r4, #0x44]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #0xa
	bl MOD85_021DE8A8
	mov r0, #1
	str r0, [r4, #8]
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	thumb_func_end MOD85_021DE4A8

	thumb_func_start MOD85_021DE4C8
MOD85_021DE4C8: ; 0x021DE4C8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #8]
	ldr r1, [r4, #0x44]
	cmp r0, #1
	bne _021DE4EC
	mov r0, #0x45
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #0xa
	bl MOD85_021DE8DC
	mov r0, #2
	str r0, [r4, #8]
	add r0, r5, #0
	bl FUN_0200CAB4
_021DE4EC:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DE4C8

	thumb_func_start MOD85_021DE4F0
MOD85_021DE4F0: ; 0x021DE4F0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x18]
	ldr r4, [r5, #0x44]
	cmp r0, #0
	bne _021DE538
	mov r2, #0x45
	mov r0, #0xa
	lsl r2, r2, #4
	str r0, [sp]
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	mov r1, #3
	mov r3, #0xe
	bl MOD85_021DE840
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0xf
	mov r3, #0xa
	bl MOD85_021DE9E4
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x10
	mov r3, #0xa
	bl MOD85_021DEA4C
	b _021DE572
_021DE538:
	mov r2, #0x45
	mov r0, #0xa
	lsl r2, r2, #4
	str r0, [sp]
	ldr r0, [r4, r2]
	sub r2, #0x18
	ldr r2, [r4, r2]
	mov r1, #3
	mov r3, #0x11
	bl MOD85_021DE840
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x12
	mov r3, #0xa
	bl MOD85_021DE9E4
	mov r1, #0x45
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, #0x18
	ldr r1, [r4, r1]
	mov r2, #0x13
	mov r3, #0xa
	bl MOD85_021DEA4C
_021DE572:
	ldr r0, _021DE598 ; =MOD85_021DE4A8
	ldr r2, _021DE59C ; =0x00000101
	add r1, r5, #0
	bl FUN_0200CA60
	cmp r0, #0
	bne _021DE584
	bl ErrorHandling
_021DE584:
	ldr r0, _021DE5A0 ; =MOD85_021DE4C8
	ldr r2, _021DE59C ; =0x00000101
	add r1, r5, #0
	bl FUN_0200CA98
	cmp r0, #0
	bne _021DE596
	bl ErrorHandling
_021DE596:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DE598: .word MOD85_021DE4A8
_021DE59C: .word 0x00000101
_021DE5A0: .word MOD85_021DE4C8
	thumb_func_end MOD85_021DE4F0

	thumb_func_start MOD85_021DE5A4
MOD85_021DE5A4: ; 0x021DE5A4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r1, [sp, #4]
	ldr r1, [sp, #0x28]
	str r0, [sp]
	str r1, [sp, #0x28]
	mov r1, #0x57
	lsl r1, r1, #2
	str r2, [sp, #8]
	add r7, r3, #0
	ldr r5, [sp, #0x20]
	ldr r6, [sp, #0x24]
	bl AllocFromHeap
	add r4, r0, #0
	bne _021DE5C8
	bl ErrorHandling
_021DE5C8:
	ldr r0, [sp]
	add r1, r4, #0
	str r0, [r4]
	strb r7, [r4, #4]
	strb r5, [r4, #5]
	ldr r0, [sp, #0x28]
	strb r6, [r4, #6]
	strb r0, [r4, #7]
	ldr r0, [sp, #0x2c]
	ldr r2, [sp]
	strb r0, [r4, #8]
	ldr r0, [sp, #0x30]
	add r1, #0x10
	strb r0, [r4, #9]
	ldr r0, [sp, #0x34]
	strb r0, [r4, #0xa]
	ldr r0, [sp, #0x38]
	strb r0, [r4, #0xb]
	ldr r0, [sp, #4]
	bl FUN_02008C9C
	str r0, [r4, #0xc]
	ldr r0, [sp, #8]
	ldr r1, [sp]
	bl FUN_0201C328
	mov r1, #0x4e
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [sp, #8]
	ldr r1, [sp]
	bl FUN_0201C24C
	ldr r2, [sp]
	add r0, r7, #0
	mov r1, #0
	bl FUN_02008DEC
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r2, [sp]
	add r0, r5, #0
	mov r1, #1
	bl FUN_02008DEC
	mov r1, #5
	lsl r1, r1, #6
	str r0, [r4, r1]
	ldr r2, [sp]
	add r0, r6, #0
	mov r1, #2
	bl FUN_02008DEC
	mov r1, #0x51
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [sp, #0x28]
	ldr r2, [sp]
	mov r1, #3
	bl FUN_02008DEC
	mov r1, #0x52
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [sp]
	lsl r1, r7, #3
	bl AllocFromHeap
	mov r1, #0x53
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [sp]
	lsl r1, r5, #3
	bl AllocFromHeap
	mov r1, #0x15
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r0, [sp]
	lsl r1, r6, #3
	bl AllocFromHeap
	mov r1, #0x55
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r1, [sp, #0x28]
	ldr r0, [sp]
	lsl r1, r1, #3
	bl AllocFromHeap
	mov r1, #0x56
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r1, #0
	cmp r7, #0
	bls _021DE6A4
	bls _021DE6A4
	ldr r0, [sp, #0x2c]
	add r2, r1, #0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
_021DE694:
	mov r3, #0x53
	lsl r3, r3, #2
	ldr r3, [r4, r3]
	add r1, r1, #1
	strh r0, [r3, r2]
	add r2, #8
	cmp r1, r7
	blo _021DE694
_021DE6A4:
	mov r3, #0
	cmp r5, #0
	bls _021DE6C4
	bls _021DE6C4
	ldr r0, [sp, #0x30]
	mov r7, #0x15
	lsl r0, r0, #0x10
	add r2, r3, #0
	lsr r1, r0, #0x10
	lsl r7, r7, #4
_021DE6B8:
	ldr r0, [r4, r7]
	add r3, r3, #1
	strh r1, [r0, r2]
	add r2, #8
	cmp r3, r5
	blo _021DE6B8
_021DE6C4:
	mov r1, #0
	cmp r6, #0
	bls _021DE6E4
	bls _021DE6E4
	ldr r2, [sp, #0x34]
	add r0, r1, #0
	lsl r2, r2, #0x10
	lsr r5, r2, #0x10
	mov r2, #0x55
	lsl r2, r2, #2
_021DE6D8:
	ldr r3, [r4, r2]
	add r1, r1, #1
	strh r5, [r3, r0]
	add r0, #8
	cmp r1, r6
	blo _021DE6D8
_021DE6E4:
	ldr r0, [sp, #0x28]
	mov r1, #0
	cmp r0, #0
	bls _021DE708
	bls _021DE708
	ldr r2, [sp, #0x38]
	mov r3, #0x56
	lsl r2, r2, #0x10
	add r0, r1, #0
	lsr r5, r2, #0x10
	lsl r3, r3, #2
_021DE6FA:
	ldr r2, [r4, r3]
	add r1, r1, #1
	strh r5, [r2, r0]
	ldr r2, [sp, #0x28]
	add r0, #8
	cmp r1, r2
	blo _021DE6FA
_021DE708:
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021DE5A4

	thumb_func_start MOD85_021DE710
MOD85_021DE710: ; 0x021DE710
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldrb r0, [r5, #4]
	mov r6, #0
	cmp r0, #0
	bls _021DE73E
	mov r7, #0x53
	add r4, r6, #0
	lsl r7, r7, #2
_021DE722:
	ldr r1, [r5, r7]
	ldrb r2, [r5, #8]
	add r0, r1, r4
	ldrh r1, [r1, r4]
	cmp r2, r1
	beq _021DE734
	ldr r0, [r0, #4]
	bl FUN_02009C0C
_021DE734:
	ldrb r0, [r5, #4]
	add r6, r6, #1
	add r4, #8
	cmp r6, r0
	blo _021DE722
_021DE73E:
	ldrb r0, [r5, #5]
	mov r6, #0
	cmp r0, #0
	bls _021DE768
	mov r7, #0x15
	add r4, r6, #0
	lsl r7, r7, #4
_021DE74C:
	ldr r1, [r5, r7]
	ldrb r2, [r5, #9]
	add r0, r1, r4
	ldrh r1, [r1, r4]
	cmp r2, r1
	beq _021DE75E
	ldr r0, [r0, #4]
	bl FUN_02009E04
_021DE75E:
	ldrb r0, [r5, #5]
	add r6, r6, #1
	add r4, #8
	cmp r6, r0
	blo _021DE74C
_021DE768:
	ldrb r0, [r5, #6]
	mov r6, #0
	cmp r0, #0
	bls _021DE792
	mov r7, #0x55
	add r4, r6, #0
	lsl r7, r7, #2
_021DE776:
	ldr r1, [r5, r7]
	ldrb r2, [r5, #0xa]
	add r0, r1, r4
	ldrh r1, [r1, r4]
	cmp r2, r1
	beq _021DE788
	ldr r0, [r0, #4]
	bl FUN_02009474
_021DE788:
	ldrb r0, [r5, #6]
	add r6, r6, #1
	add r4, #8
	cmp r6, r0
	blo _021DE776
_021DE792:
	ldrb r0, [r5, #7]
	mov r6, #0
	cmp r0, #0
	bls _021DE7BC
	mov r7, #0x56
	add r4, r6, #0
	lsl r7, r7, #2
_021DE7A0:
	ldr r1, [r5, r7]
	ldrb r2, [r5, #0xb]
	add r0, r1, r4
	ldrh r1, [r1, r4]
	cmp r2, r1
	beq _021DE7B2
	ldr r0, [r0, #4]
	bl FUN_02009474
_021DE7B2:
	ldrb r0, [r5, #7]
	add r6, r6, #1
	add r4, #8
	cmp r6, r0
	blo _021DE7A0
_021DE7BC:
	mov r0, #0x4f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02008E2C
	mov r0, #5
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	bl FUN_02008E2C
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02008E2C
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02008E2C
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FreeToHeap
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FreeToHeap
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FreeToHeap
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FreeToHeap
	bl FUN_0201C29C
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0201C350
	ldr r0, [r5, #0xc]
	bl FUN_0201FDB4
	ldr r0, [r5, #0xc]
	bl FUN_0201FD58
	add r0, r5, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021DE710

	thumb_func_start MOD85_021DE830
MOD85_021DE830: ; 0x021DE830
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_0201FDEC
	bl FUN_0201C348
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD85_021DE830

	thumb_func_start MOD85_021DE840
MOD85_021DE840: ; 0x021DE840
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldrb r5, [r4, #4]
	add r7, r1, #0
	mov r1, #0
	str r2, [sp, #0xc]
	mov ip, r3
	cmp r5, #0
	bls _021DE8A0
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r6, [r4, r0]
	ldrb r3, [r4, #8]
	add r2, r6, #0
_021DE85E:
	ldrh r0, [r2]
	cmp r3, r0
	bne _021DE898
	ldr r0, [sp, #0x28]
	lsl r5, r1, #3
	mov r1, #0x53
	strh r0, [r6, r5]
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	mov r3, #0
	add r2, r2, r5
	strh r3, [r2, #2]
	str r0, [sp]
	str r7, [sp, #4]
	ldr r0, [r4]
	sub r1, #0x10
	str r0, [sp, #8]
	ldr r0, [r4, r1]
	ldr r1, [sp, #0xc]
	mov r2, ip
	bl FUN_020091E0
	mov r1, #0x53
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	add sp, #0x10
	add r1, r1, r5
	str r0, [r1, #4]
	pop {r3, r4, r5, r6, r7, pc}
_021DE898:
	add r1, r1, #1
	add r2, #8
	cmp r1, r5
	blo _021DE85E
_021DE8A0:
	bl ErrorHandling
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD85_021DE840

	thumb_func_start MOD85_021DE8A8
MOD85_021DE8A8: ; 0x021DE8A8
	push {r3, r4, r5, lr}
	ldrb r2, [r0, #4]
	mov r4, #0
	cmp r2, #0
	bls _021DE8D4
	mov r3, #0x53
	lsl r3, r3, #2
	ldr r5, [r0, r3]
	add r3, r5, #0
_021DE8BA:
	ldrh r0, [r3]
	cmp r1, r0
	bne _021DE8CC
	lsl r0, r4, #3
	add r0, r5, r0
	ldr r0, [r0, #4]
	bl FUN_02009B04
	pop {r3, r4, r5, pc}
_021DE8CC:
	add r4, r4, #1
	add r3, #8
	cmp r4, r2
	blo _021DE8BA
_021DE8D4:
	bl ErrorHandling
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DE8A8

	thumb_func_start MOD85_021DE8DC
MOD85_021DE8DC: ; 0x021DE8DC
	push {r3, r4, r5, lr}
	ldrb r2, [r0, #4]
	mov r4, #0
	cmp r2, #0
	bls _021DE908
	mov r3, #0x53
	lsl r3, r3, #2
	ldr r5, [r0, r3]
	add r3, r5, #0
_021DE8EE:
	ldrh r0, [r3]
	cmp r1, r0
	bne _021DE900
	lsl r0, r4, #3
	add r0, r5, r0
	ldr r0, [r0, #4]
	bl FUN_02009474
	pop {r3, r4, r5, pc}
_021DE900:
	add r4, r4, #1
	add r3, #8
	cmp r4, r2
	blo _021DE8EE
_021DE908:
	bl ErrorHandling
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DE8DC

	thumb_func_start MOD85_021DE910
MOD85_021DE910: ; 0x021DE910
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldrb r5, [r4, #4]
	add r7, r1, #0
	mov r1, #0
	str r2, [sp, #0x10]
	mov ip, r3
	cmp r5, #0
	bls _021DE974
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r6, [r4, r0]
	ldrb r3, [r4, #9]
	add r2, r6, #0
_021DE92E:
	ldrh r0, [r2]
	cmp r3, r0
	bne _021DE96C
	ldr r0, [sp, #0x28]
	lsl r5, r1, #3
	mov r1, #0x15
	strh r0, [r6, r5]
	lsl r1, r1, #4
	ldr r2, [r4, r1]
	mov r3, #0
	add r2, r2, r5
	strh r3, [r2, #2]
	str r0, [sp]
	str r7, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, [r4]
	sub r1, #0x10
	str r0, [sp, #0xc]
	ldr r0, [r4, r1]
	ldr r1, [sp, #0x10]
	mov r2, ip
	bl FUN_02009298
	mov r1, #0x15
	lsl r1, r1, #4
	ldr r1, [r4, r1]
	add sp, #0x14
	add r1, r1, r5
	str r0, [r1, #4]
	pop {r4, r5, r6, r7, pc}
_021DE96C:
	add r1, r1, #1
	add r2, #8
	cmp r1, r5
	blo _021DE92E
_021DE974:
	bl ErrorHandling
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD85_021DE910

	thumb_func_start MOD85_021DE97C
MOD85_021DE97C: ; 0x021DE97C
	push {r3, r4, r5, lr}
	ldrb r2, [r0, #5]
	mov r4, #0
	cmp r2, #0
	bls _021DE9A8
	mov r3, #0x15
	lsl r3, r3, #4
	ldr r5, [r0, r3]
	add r3, r5, #0
_021DE98E:
	ldrh r0, [r3]
	cmp r1, r0
	bne _021DE9A0
	lsl r0, r4, #3
	add r0, r5, r0
	ldr r0, [r0, #4]
	bl FUN_02009D68
	pop {r3, r4, r5, pc}
_021DE9A0:
	add r4, r4, #1
	add r3, #8
	cmp r4, r2
	blo _021DE98E
_021DE9A8:
	bl ErrorHandling
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DE97C

	thumb_func_start MOD85_021DE9B0
MOD85_021DE9B0: ; 0x021DE9B0
	push {r3, r4, r5, lr}
	ldrb r2, [r0, #5]
	mov r4, #0
	cmp r2, #0
	bls _021DE9DC
	mov r3, #0x15
	lsl r3, r3, #4
	ldr r5, [r0, r3]
	add r3, r5, #0
_021DE9C2:
	ldrh r0, [r3]
	cmp r1, r0
	bne _021DE9D4
	lsl r0, r4, #3
	add r0, r5, r0
	ldr r0, [r0, #4]
	bl FUN_02009474
	pop {r3, r4, r5, pc}
_021DE9D4:
	add r4, r4, #1
	add r3, #8
	cmp r4, r2
	blo _021DE9C2
_021DE9DC:
	bl ErrorHandling
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD85_021DE9B0

	thumb_func_start MOD85_021DE9E4
MOD85_021DE9E4: ; 0x021DE9E4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldrb r5, [r4, #4]
	str r1, [sp, #0xc]
	mov ip, r2
	add r6, r3, #0
	mov r1, #0
	cmp r5, #0
	bls _021DEA44
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r7, [r4, r0]
	ldrb r3, [r4, #0xa]
	add r2, r7, #0
_021DEA02:
	ldrh r0, [r2]
	cmp r3, r0
	bne _021DEA3C
	lsl r5, r1, #3
	mov r0, #0x55
	strh r6, [r7, r5]
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	mov r3, #0
	add r1, r1, r5
	strh r3, [r1, #2]
	str r6, [sp]
	mov r1, #2
	str r1, [sp, #4]
	ldr r1, [r4]
	sub r0, #0x10
	str r1, [sp, #8]
	ldr r0, [r4, r0]
	ldr r1, [sp, #0xc]
	mov r2, ip
	bl FUN_02009358
	mov r1, #0x55
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	add sp, #0x10
	add r1, r1, r5
	str r0, [r1, #4]
	pop {r3, r4, r5, r6, r7, pc}
_021DEA3C:
	add r1, r1, #1
	add r2, #8
	cmp r1, r5
	blo _021DEA02
_021DEA44:
	bl ErrorHandling
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD85_021DE9E4

	thumb_func_start MOD85_021DEA4C
MOD85_021DEA4C: ; 0x021DEA4C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldrb r5, [r4, #4]
	str r1, [sp, #0xc]
	mov ip, r2
	add r6, r3, #0
	mov r1, #0
	cmp r5, #0
	bls _021DEAAC
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r7, [r4, r0]
	ldrb r3, [r4, #0xb]
	add r2, r7, #0
_021DEA6A:
	ldrh r0, [r2]
	cmp r3, r0
	bne _021DEAA4
	lsl r5, r1, #3
	mov r0, #0x56
	strh r6, [r7, r5]
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	mov r3, #0
	add r1, r1, r5
	strh r3, [r1, #2]
	str r6, [sp]
	mov r1, #3
	str r1, [sp, #4]
	ldr r1, [r4]
	sub r0, #0x10
	str r1, [sp, #8]
	ldr r0, [r4, r0]
	ldr r1, [sp, #0xc]
	mov r2, ip
	bl FUN_02009358
	mov r1, #0x56
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	add sp, #0x10
	add r1, r1, r5
	str r0, [r1, #4]
	pop {r3, r4, r5, r6, r7, pc}
_021DEAA4:
	add r1, r1, #1
	add r2, #8
	cmp r1, r5
	blo _021DEA6A
_021DEAAC:
	bl ErrorHandling
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD85_021DEA4C

	thumb_func_start MOD85_021DEAB4
MOD85_021DEAB4: ; 0x021DEAB4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r0, #0
	add r0, r1, #0
	ldrb r1, [r4, #8]
	add r7, r2, #0
	str r3, [sp]
	ldr r6, [sp, #0x20]
	cmp r0, r1
	beq _021DEB10
	ldrb r5, [r4, #4]
	mov r2, #0
	cmp r5, #0
	bls _021DEB10
	mov r1, #0x53
	lsl r1, r1, #2
	ldr r3, [r4, r1]
	mov ip, r3
_021DEAD8:
	ldrh r1, [r3]
	cmp r0, r1
	bne _021DEB08
	lsl r5, r2, #3
	mov r0, ip
	add r0, r0, r5
	ldr r0, [r0, #4]
	bl FUN_02009C0C
	mov r1, #0x4f
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	add r1, #0x10
	ldr r1, [r4, r1]
	add r1, r1, r5
	ldr r1, [r1, #4]
	bl FUN_02009490
	mov r0, #0x53
	lsl r0, r0, #2
	ldrb r1, [r4, #8]
	ldr r0, [r4, r0]
	strh r1, [r0, r5]
	b _021DEB10
_021DEB08:
	add r2, r2, #1
	add r3, #8
	cmp r2, r5
	blo _021DEAD8
_021DEB10:
	ldrb r0, [r4, #9]
	cmp r7, r0
	beq _021DEB5E
	ldrb r0, [r4, #5]
	mov r1, #0
	cmp r0, #0
	bls _021DEB5E
	mov r2, #0x15
	lsl r2, r2, #4
	ldr r3, [r4, r2]
	str r3, [sp, #4]
_021DEB26:
	ldrh r2, [r3]
	cmp r7, r2
	bne _021DEB56
	ldr r0, [sp, #4]
	lsl r5, r1, #3
	add r0, r0, r5
	ldr r0, [r0, #4]
	bl FUN_02009E04
	mov r1, #5
	lsl r1, r1, #6
	ldr r0, [r4, r1]
	add r1, #0x10
	ldr r1, [r4, r1]
	add r1, r1, r5
	ldr r1, [r1, #4]
	bl FUN_02009490
	mov r0, #0x15
	lsl r0, r0, #4
	ldrb r1, [r4, #9]
	ldr r0, [r4, r0]
	strh r1, [r0, r5]
	b _021DEB5E
_021DEB56:
	add r1, r1, #1
	add r3, #8
	cmp r1, r0
	blo _021DEB26
_021DEB5E:
	ldrb r1, [r4, #0xa]
	ldr r0, [sp]
	cmp r0, r1
	beq _021DEBAE
	ldrb r3, [r4, #6]
	mov r5, #0
	cmp r3, #0
	bls _021DEBAE
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r7, [r4, r0]
	add r2, r7, #0
_021DEB76:
	ldrh r1, [r2]
	ldr r0, [sp]
	cmp r0, r1
	bne _021DEBA6
	lsl r5, r5, #3
	add r0, r7, r5
	ldr r0, [r0, #4]
	bl FUN_02009474
	mov r1, #0x51
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	add r1, #0x10
	ldr r1, [r4, r1]
	add r1, r1, r5
	ldr r1, [r1, #4]
	bl FUN_02009490
	mov r0, #0x55
	lsl r0, r0, #2
	ldrb r1, [r4, #0xa]
	ldr r0, [r4, r0]
	strh r1, [r0, r5]
	b _021DEBAE
_021DEBA6:
	add r5, r5, #1
	add r2, #8
	cmp r5, r3
	blo _021DEB76
_021DEBAE:
	ldrb r0, [r4, #0xb]
	cmp r6, r0
	beq _021DEBFC
	ldrb r1, [r4, #7]
	mov r2, #0
	cmp r1, #0
	bls _021DEBFC
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r5, r0, #0
_021DEBC4:
	ldrh r3, [r5]
	cmp r6, r3
	bne _021DEBF4
	lsl r5, r2, #3
	add r0, r0, r5
	ldr r0, [r0, #4]
	bl FUN_02009474
	mov r1, #0x52
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	add r1, #0x10
	ldr r1, [r4, r1]
	add r1, r1, r5
	ldr r1, [r1, #4]
	bl FUN_02009490
	mov r0, #0x56
	lsl r0, r0, #2
	ldrb r1, [r4, #0xb]
	ldr r0, [r4, r0]
	add sp, #8
	strh r1, [r0, r5]
	pop {r3, r4, r5, r6, r7, pc}
_021DEBF4:
	add r2, r2, #1
	add r5, #8
	cmp r2, r1
	blo _021DEBC4
_021DEBFC:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD85_021DEAB4

	thumb_func_start MOD85_021DEC00
MOD85_021DEC00: ; 0x021DEC00
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x70
	add r5, r0, #0
	ldrb r0, [r5, #0xb]
	add r4, r1, #0
	ldr r1, [sp, #0x98]
	add r6, r2, #0
	add r7, r3, #0
	cmp r1, r0
	bne _021DEC1A
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x98]
_021DEC1A:
	ldr r0, [sp, #0x98]
	mov r1, #0x4f
	str r0, [sp]
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [sp, #0x88]
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x9c]
	ldr r2, [sp, #0x90]
	str r0, [sp, #0x10]
	ldr r0, [r5, r1]
	ldr r3, [sp, #0x94]
	str r0, [sp, #0x14]
	add r0, r1, #4
	ldr r0, [r5, r0]
	str r0, [sp, #0x18]
	add r0, r1, #0
	add r0, #8
	ldr r0, [r5, r0]
	add r1, #0xc
	str r0, [sp, #0x1c]
	ldr r0, [r5, r1]
	ldr r1, [sp, #0x8c]
	str r0, [sp, #0x20]
	mov r0, #0
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	add r0, sp, #0x4c
	bl FUN_02008AA4
	ldr r0, [sp, #0x88]
	cmp r0, #1
	bne _021DEC6A
	ldr r0, [sp, #0x4c]
	str r0, [r4, #8]
	mov r0, #1
	b _021DEC6C
_021DEC6A:
	mov r0, #0
_021DEC6C:
	str r0, [r4]
	ldr r0, [r5, #0xc]
	add r2, sp, #0x34
	str r0, [sp, #0x2c]
	add r0, sp, #0x4c
	str r0, [sp, #0x30]
	ldmia r6!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r6]
	str r0, [r2]
	ldr r0, [sp, #0xa0]
	str r7, [sp, #0x44]
	str r0, [sp, #0x40]
	ldr r0, [r5]
	str r0, [sp, #0x48]
	add r0, sp, #0x2c
	bl FUN_0201FF84
	str r0, [r4, #4]
	cmp r0, #0
	bne _021DEC9A
	bl ErrorHandling
_021DEC9A:
	add sp, #0x70
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD85_021DEC00

	thumb_func_start MOD85_021DECA0
MOD85_021DECA0: ; 0x021DECA0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #1
	bne _021DECB0
	ldr r0, [r4, #8]
	bl FUN_02009CDC
_021DECB0:
	ldr r0, [r4, #4]
	bl FUN_0201FFC8
	mov r0, #0
	str r0, [r4, #4]
	pop {r4, pc}
	thumb_func_end MOD85_021DECA0

	thumb_func_start MOD85_021DECBC
MOD85_021DECBC: ; 0x021DECBC
	push {r4, lr}
	add r4, r1, #0
	bl FUN_0202011C
	add r2, r0, #0
	ldmia r2!, {r0, r1}
	stmia r4!, {r0, r1}
	ldr r0, [r2]
	str r0, [r4]
	pop {r4, pc}
	thumb_func_end MOD85_021DECBC

	thumb_func_start MOD85_021DECD0
MOD85_021DECD0: ; 0x021DECD0
	push {r4, lr}
	add r4, r1, #0
	bl FUN_02020120
	add r2, r0, #0
	ldmia r2!, {r0, r1}
	stmia r4!, {r0, r1}
	ldr r0, [r2]
	str r0, [r4]
	pop {r4, pc}
	thumb_func_end MOD85_021DECD0

	.rodata
	.global MOD85_021DECE4
MOD85_021DECE4: ; 0x021DECE4
	.byte 0x00, 0x02, 0x13, 0x1A, 0x04, 0x0F, 0x3D, 0x00

	.global MOD85_021DECEC
MOD85_021DECEC: ; 0x021DECEC
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DECFC
MOD85_021DECFC: ; 0x021DECFC
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00

	.global MOD85_021DED0C
MOD85_021DED0C: ; 0x021DED0C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x03, 0x08, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DED28
MOD85_021DED28: ; 0x021DED28
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DED44
MOD85_021DED44: ; 0x021DED44
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x01, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DED60
MOD85_021DED60: ; 0x021DED60
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x02, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DED7C
MOD85_021DED7C: ; 0x021DED7C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xB0, 0x1D, 0x02, 0x7D, 0xB3, 0x1D, 0x02
	.byte 0x05, 0xB0, 0x1D, 0x02, 0x59, 0xB2, 0x1D, 0x02, 0x05, 0xB0, 0x1D, 0x02, 0x61, 0xB3, 0x1D, 0x02
	.byte 0x05, 0xB0, 0x1D, 0x02, 0x45, 0xB3, 0x1D, 0x02, 0x05, 0xB0, 0x1D, 0x02

	.global MOD85_021DEDC8
MOD85_021DEDC8: ; 0x021DEDC8
	.byte 0x00, 0x08, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x09, 0xB0, 0x1D, 0x02
	.byte 0x21, 0xB0, 0x1D, 0x02, 0x05, 0xB0, 0x1D, 0x02, 0xE9, 0xB1, 0x1D, 0x02, 0x15, 0xB2, 0x1D, 0x02
	.byte 0x05, 0xB0, 0x1D, 0x02, 0xA1, 0xAF, 0x1D, 0x02, 0xB9, 0xAF, 0x1D, 0x02, 0xDD, 0xAF, 0x1D, 0x02
	.byte 0x05, 0xB0, 0x1D, 0x02, 0x6D, 0xB1, 0x1D, 0x02, 0x8D, 0xB1, 0x1D, 0x02, 0xB9, 0xB1, 0x1D, 0x02
	.byte 0x05, 0xB0, 0x1D, 0x02

	.global MOD85_021DEE0C
MOD85_021DEE0C: ; 0x021DEE0C
	.byte 0x24, 0x00, 0x00, 0x00, 0xC5, 0xB7, 0x1D, 0x02, 0xE9, 0xB7, 0x1D, 0x02, 0xF5, 0xB7, 0x1D, 0x02
	.byte 0x95, 0x47, 0x06, 0x02

	.global MOD85_021DEE20
MOD85_021DEE20: ; 0x021DEE20
	.byte 0x8D, 0x93, 0x1D, 0x02, 0x91, 0x93, 0x1D, 0x02, 0xA9, 0x93, 0x1D, 0x02, 0x05, 0x94, 0x1D, 0x02
	.byte 0xAD, 0x94, 0x1D, 0x02

	.global MOD85_021DEE34
MOD85_021DEE34: ; 0x021DEE34
	.byte 0x00, 0x40, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00
	.byte 0x00, 0x00, 0x01, 0x00, 0xD5, 0xB0, 0x1D, 0x02, 0xF5, 0xB0, 0x1D, 0x02, 0x29, 0xB1, 0x1D, 0x02
	.byte 0x49, 0xB1, 0x1D, 0x02, 0x05, 0xB0, 0x1D, 0x02

	.global MOD85_021DEE5C
MOD85_021DEE5C: ; 0x021DEE5C
	.byte 0x30, 0x00, 0x00, 0x00, 0xE5, 0xBA, 0x1D, 0x02, 0xFD, 0xBA, 0x1D, 0x02, 0x01, 0xBB, 0x1D, 0x02
	.byte 0x95, 0x47, 0x06, 0x02, 0x45, 0xB0, 0x1D, 0x02, 0x5D, 0xB0, 0x1D, 0x02, 0x89, 0xB0, 0x1D, 0x02
	.byte 0xB1, 0xB0, 0x1D, 0x02, 0x05, 0xB0, 0x1D, 0x02, 0x71, 0xB2, 0x1D, 0x02, 0x95, 0xB2, 0x1D, 0x02
	.byte 0xC9, 0xB2, 0x1D, 0x02, 0xFD, 0xB2, 0x1D, 0x02, 0x21, 0xB3, 0x1D, 0x02, 0x05, 0xB0, 0x1D, 0x02

	.global MOD85_021DEE9C
MOD85_021DEE9C: ; 0x021DEE9C
	.byte 0x07, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00
	.byte 0x16, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x99, 0xB3, 0x1D, 0x02, 0xBD, 0xB3, 0x1D, 0x02
	.byte 0xF5, 0xB3, 0x1D, 0x02, 0x19, 0xB4, 0x1D, 0x02, 0x49, 0xB4, 0x1D, 0x02, 0x71, 0xB4, 0x1D, 0x02
	.byte 0x05, 0xB0, 0x1D, 0x02

	.global MOD85_021DEED0
MOD85_021DEED0: ; 0x021DEED0
	.byte 0xA4, 0xED, 0x1D, 0x02, 0xEC, 0xED, 0x1D, 0x02, 0xD4, 0xED, 0x1D, 0x02, 0x70, 0xEE, 0x1D, 0x02
	.byte 0x48, 0xEE, 0x1D, 0x02, 0xFC, 0xED, 0x1D, 0x02, 0xE0, 0xED, 0x1D, 0x02, 0xB0, 0xED, 0x1D, 0x02
	.byte 0x84, 0xEE, 0x1D, 0x02, 0xC0, 0xED, 0x1D, 0x02, 0xB8, 0xED, 0x1D, 0x02, 0xA8, 0xED, 0x1D, 0x02
	.byte 0xB4, 0xEE, 0x1D, 0x02

	.global MOD85_021DEF04
MOD85_021DEF04: ; 0x021DEF04
	.byte 0x00, 0x08, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00

	.global MOD85_021DEF94
MOD85_021DEF94: ; 0x021DEF94
	.byte 0x31, 0x82, 0x1D, 0x02, 0xA1, 0x82, 0x1D, 0x02, 0xFD, 0x82, 0x1D, 0x02, 0x31, 0x83, 0x1D, 0x02
	.byte 0xFD, 0x83, 0x1D, 0x02, 0x1D, 0x84, 0x1D, 0x02, 0x15, 0x85, 0x1D, 0x02, 0x4D, 0x85, 0x1D, 0x02
	.byte 0xB5, 0x85, 0x1D, 0x02, 0xC9, 0x85, 0x1D, 0x02, 0xE5, 0x85, 0x1D, 0x02, 0xFD, 0x85, 0x1D, 0x02
	.byte 0x1D, 0x86, 0x1D, 0x02, 0x4D, 0x86, 0x1D, 0x02, 0x95, 0x86, 0x1D, 0x02, 0xB5, 0x86, 0x1D, 0x02
	.byte 0x01, 0x87, 0x1D, 0x02, 0x29, 0x87, 0x1D, 0x02, 0x55, 0x87, 0x1D, 0x02, 0x6D, 0x87, 0x1D, 0x02
	.byte 0x9D, 0x87, 0x1D, 0x02, 0xE9, 0x87, 0x1D, 0x02, 0x11, 0x88, 0x1D, 0x02, 0x5D, 0x88, 0x1D, 0x02
	.byte 0x75, 0x88, 0x1D, 0x02, 0x8D, 0x88, 0x1D, 0x02, 0xF9, 0x88, 0x1D, 0x02, 0x55, 0x89, 0x1D, 0x02
	.byte 0x89, 0x89, 0x1D, 0x02, 0x31, 0x8A, 0x1D, 0x02, 0x51, 0x8A, 0x1D, 0x02, 0x49, 0x8B, 0x1D, 0x02
	.byte 0x81, 0x8B, 0x1D, 0x02, 0xC5, 0x8B, 0x1D, 0x02, 0xE1, 0x8B, 0x1D, 0x02, 0x01, 0x8C, 0x1D, 0x02
	.byte 0x31, 0x8C, 0x1D, 0x02, 0x51, 0x8C, 0x1D, 0x02, 0x71, 0x8C, 0x1D, 0x02, 0xAD, 0x8C, 0x1D, 0x02
	.byte 0xF9, 0x8C, 0x1D, 0x02, 0x25, 0x8D, 0x1D, 0x02, 0x3D, 0x8D, 0x1D, 0x02, 0x89, 0x8D, 0x1D, 0x02
	.byte 0xFD, 0x8D, 0x1D, 0x02, 0x65, 0x8E, 0x1D, 0x02, 0x99, 0x8E, 0x1D, 0x02, 0x89, 0x8F, 0x1D, 0x02
	.byte 0xB1, 0x8F, 0x1D, 0x02, 0xB1, 0x90, 0x1D, 0x02, 0xE9, 0x90, 0x1D, 0x02, 0x21, 0x91, 0x1D, 0x02
	.byte 0x45, 0x91, 0x1D, 0x02, 0x79, 0x91, 0x1D, 0x02, 0xA5, 0x91, 0x1D, 0x02, 0xD9, 0x91, 0x1D, 0x02
	.byte 0x25, 0x92, 0x1D, 0x02, 0x3D, 0x92, 0x1D, 0x02, 0x55, 0x92, 0x1D, 0x02, 0x85, 0x92, 0x1D, 0x02
	.byte 0x99, 0x92, 0x1D, 0x02, 0xAD, 0x92, 0x1D, 0x02, 0xC1, 0x92, 0x1D, 0x02, 0xDD, 0x92, 0x1D, 0x02

	.global MOD85_021DF094
MOD85_021DF094: ; 0x021DF094
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x18, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x18, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x40, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xBD, 0xD1, 0x1D, 0x02, 0x05, 0xD0, 0x1D, 0x02, 0x69, 0xD3, 0x1D, 0x02, 0x05, 0xD0, 0x1D, 0x02
	.byte 0xE5, 0xC9, 0x1D, 0x02, 0xDD, 0xC5, 0x1D, 0x02, 0x01, 0xD3, 0x1D, 0x02, 0x05, 0xD0, 0x1D, 0x02
	.byte 0x99, 0xD2, 0x1D, 0x02, 0x05, 0xD0, 0x1D, 0x02, 0x89, 0xCF, 0x1D, 0x02, 0x05, 0xD0, 0x1D, 0x02
	.byte 0x25, 0xD2, 0x1D, 0x02, 0x05, 0xD0, 0x1D, 0x02, 0xB5, 0xC8, 0x1D, 0x02, 0x3D, 0xC9, 0x1D, 0x02
	.byte 0xDD, 0xC5, 0x1D, 0x02

	.global MOD85_021DF5F8
MOD85_021DF5F8: ; 0x021DF5F8
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF604
MOD85_021DF604: ; 0x021DF604
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF610
MOD85_021DF610: ; 0x021DF610
	.byte 0x00, 0xE0, 0x00, 0x00, 0x00, 0x80, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF61C
MOD85_021DF61C: ; 0x021DF61C
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF628
MOD85_021DF628: ; 0x021DF628
	.byte 0x00, 0xC0, 0x06, 0x00, 0x00, 0x40, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD1, 0xD3, 0x1D, 0x02
	.byte 0x3D, 0xD4, 0x1D, 0x02, 0x05, 0xD0, 0x1D, 0x02

	.global MOD85_021DF640
MOD85_021DF640: ; 0x021DF640
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF64C
MOD85_021DF64C: ; 0x021DF64C
	.byte 0x00, 0x80, 0x0C, 0x00, 0x00, 0x80, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF658
MOD85_021DF658: ; 0x021DF658
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF664
MOD85_021DF664: ; 0x021DF664
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF670
MOD85_021DF670: ; 0x021DF670
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF67C
MOD85_021DF67C: ; 0x021DF67C
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF688
MOD85_021DF688: ; 0x021DF688
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0xC7, 0x1D, 0x02
	.byte 0x7D, 0xC7, 0x1D, 0x02, 0xDD, 0xC5, 0x1D, 0x02

	.global MOD85_021DF6A0
MOD85_021DF6A0: ; 0x021DF6A0
	.byte 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF6AC
MOD85_021DF6AC: ; 0x021DF6AC
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF6B8
MOD85_021DF6B8: ; 0x021DF6B8
	.byte 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF6C4
MOD85_021DF6C4: ; 0x021DF6C4
	.byte 0x00, 0xC0, 0x0D, 0x00, 0x00, 0x80, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF6D0
MOD85_021DF6D0: ; 0x021DF6D0
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF6DC
MOD85_021DF6DC: ; 0x021DF6DC
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF6E8
MOD85_021DF6E8: ; 0x021DF6E8
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF6F4
MOD85_021DF6F4: ; 0x021DF6F4
	.byte 0x00, 0x40, 0x0B, 0x00, 0x00, 0x40, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE1, 0xC7, 0x1D, 0x02
	.byte 0x49, 0xC8, 0x1D, 0x02, 0xDD, 0xC5, 0x1D, 0x02

	.global MOD85_021DF70C
MOD85_021DF70C: ; 0x021DF70C
	.byte 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF718
MOD85_021DF718: ; 0x021DF718
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF724
MOD85_021DF724: ; 0x021DF724
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF730
MOD85_021DF730: ; 0x021DF730
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF73C
MOD85_021DF73C: ; 0x021DF73C
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF748
MOD85_021DF748: ; 0x021DF748
	.byte 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF754
MOD85_021DF754: ; 0x021DF754
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF760
MOD85_021DF760: ; 0x021DF760
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF76C
MOD85_021DF76C: ; 0x021DF76C
	.byte 0x00, 0x40, 0x03, 0x00, 0x00, 0x80, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF778
MOD85_021DF778: ; 0x021DF778
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCD, 0xC6, 0x1D, 0x02
	.byte 0xF9, 0xC6, 0x1D, 0x02, 0xDD, 0xC5, 0x1D, 0x02

	.global MOD85_021DF790
MOD85_021DF790: ; 0x021DF790
	.byte 0x00, 0x80, 0x0C, 0x00, 0x00, 0x80, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF79C
MOD85_021DF79C: ; 0x021DF79C
	.byte 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF7A8
MOD85_021DF7A8: ; 0x021DF7A8
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF7B4
MOD85_021DF7B4: ; 0x021DF7B4
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF1, 0xD0, 0x1D, 0x02
	.byte 0x59, 0xD1, 0x1D, 0x02, 0x05, 0xD0, 0x1D, 0x02

	.global MOD85_021DF7CC
MOD85_021DF7CC: ; 0x021DF7CC
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF7D8
MOD85_021DF7D8: ; 0x021DF7D8
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF7E4
MOD85_021DF7E4: ; 0x021DF7E4
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF7F0
MOD85_021DF7F0: ; 0x021DF7F0
	.byte 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF7FC
MOD85_021DF7FC: ; 0x021DF7FC
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF808
MOD85_021DF808: ; 0x021DF808
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF820
MOD85_021DF820: ; 0x021DF820
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF82C
MOD85_021DF82C: ; 0x021DF82C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF838
MOD85_021DF838: ; 0x021DF838
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF844
MOD85_021DF844: ; 0x021DF844
	.byte 0x00, 0xE0, 0x00, 0x00, 0x00, 0x80, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF850
MOD85_021DF850: ; 0x021DF850
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DF85C
MOD85_021DF85C: ; 0x021DF85C
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0xD0, 0x1D, 0x02
	.byte 0x65, 0xD0, 0x1D, 0x02, 0xC5, 0xD0, 0x1D, 0x02, 0x05, 0xD0, 0x1D, 0x02, 0x85, 0xC5, 0x1D, 0x02
	.byte 0x99, 0xC5, 0x1D, 0x02, 0xA9, 0xC5, 0x1D, 0x02, 0xDD, 0xC5, 0x1D, 0x02, 0xE1, 0xC5, 0x1D, 0x02
	.byte 0x49, 0xC6, 0x1D, 0x02, 0xB1, 0xC6, 0x1D, 0x02, 0xDD, 0xC5, 0x1D, 0x02

	.global MOD85_021DF898
MOD85_021DF898: ; 0x021DF898
	.byte 0x18, 0x00, 0x00, 0x00, 0xE5, 0xDC, 0x1D, 0x02, 0x4D, 0xDD, 0x1D, 0x02, 0x61, 0xDD, 0x1D, 0x02
	.byte 0x95, 0x47, 0x06, 0x02

	.global MOD85_021DF8AC
MOD85_021DF8AC: ; 0x021DF8AC
	.byte 0x20, 0x00, 0x00, 0x00, 0x19, 0xCC, 0x1D, 0x02, 0x2D, 0xCC, 0x1D, 0x02, 0x59, 0xCC, 0x1D, 0x02
	.byte 0xF9, 0xCC, 0x1D, 0x02

	.global MOD85_021DF8C0
MOD85_021DF8C0: ; 0x021DF8C0
	.byte 0x30, 0x00, 0x00, 0x00, 0x19, 0xCF, 0x1D, 0x02, 0x39, 0xCF, 0x1D, 0x02, 0x65, 0xCF, 0x1D, 0x02
	.byte 0x85, 0xCF, 0x1D, 0x02

	.global MOD85_021DF8D4
MOD85_021DF8D4: ; 0x021DF8D4
	.byte 0x48, 0x00, 0x00, 0x00, 0x85, 0xD5, 0x1D, 0x02, 0x99, 0xD5, 0x1D, 0x02, 0x25, 0xD6, 0x1D, 0x02
	.byte 0x81, 0xD9, 0x1D, 0x02

	.global MOD85_021DF8E8
MOD85_021DF8E8: ; 0x021DF8E8
	.byte 0x10, 0x00, 0x00, 0x00, 0xBD, 0xD9, 0x1D, 0x02, 0x09, 0xDA, 0x1D, 0x02, 0x15, 0xDA, 0x1D, 0x02
	.byte 0x95, 0x47, 0x06, 0x02

	.global MOD85_021DF8FC
MOD85_021DF8FC: ; 0x021DF8FC
	.byte 0x40, 0x00, 0x00, 0x00, 0x49, 0xDE, 0x1D, 0x02, 0xB1, 0xDE, 0x1D, 0x02, 0xC9, 0xDE, 0x1D, 0x02
	.byte 0x95, 0x47, 0x06, 0x02

	.global MOD85_021DF910
MOD85_021DF910: ; 0x021DF910
	.byte 0x48, 0x00, 0x00, 0x00, 0x91, 0xE2, 0x1D, 0x02, 0xD1, 0xE2, 0x1D, 0x02, 0x11, 0xE3, 0x1D, 0x02
	.byte 0x95, 0x47, 0x06, 0x02

	.global MOD85_021DF924
MOD85_021DF924: ; 0x021DF924
	.byte 0x14, 0x00, 0x00, 0x00, 0x61, 0xDA, 0x1D, 0x02, 0xF1, 0xDA, 0x1D, 0x02, 0xFD, 0xDA, 0x1D, 0x02
	.byte 0x95, 0x47, 0x06, 0x02

	.global MOD85_021DF938
MOD85_021DF938: ; 0x021DF938
	.byte 0x18, 0x00, 0x00, 0x00, 0x69, 0xC1, 0x1D, 0x02, 0xC1, 0xC1, 0x1D, 0x02, 0xCD, 0xC1, 0x1D, 0x02
	.byte 0x49, 0xC2, 0x1D, 0x02

	.global MOD85_021DF94C
MOD85_021DF94C: ; 0x021DF94C
	.byte 0x18, 0x00, 0x00, 0x00, 0xA1, 0xC2, 0x1D, 0x02, 0xF9, 0xC2, 0x1D, 0x02, 0x05, 0xC3, 0x1D, 0x02
	.byte 0x81, 0xC3, 0x1D, 0x02

	.global MOD85_021DF960
MOD85_021DF960: ; 0x021DF960
	.byte 0x18, 0x00, 0x00, 0x00, 0xD9, 0xC3, 0x1D, 0x02, 0x31, 0xC4, 0x1D, 0x02, 0x3D, 0xC4, 0x1D, 0x02
	.byte 0xB1, 0xC4, 0x1D, 0x02

	.global MOD85_021DF974
MOD85_021DF974: ; 0x021DF974
	.byte 0x48, 0x00, 0x00, 0x00, 0x2D, 0xC5, 0x1D, 0x02, 0x45, 0xC5, 0x1D, 0x02, 0x61, 0xC5, 0x1D, 0x02
	.byte 0x81, 0xC5, 0x1D, 0x02

	.global MOD85_021DF988
MOD85_021DF988: ; 0x021DF988
	.byte 0x10, 0x00, 0x00, 0x00, 0x49, 0xDB, 0x1D, 0x02, 0x95, 0xDB, 0x1D, 0x02, 0xA1, 0xDB, 0x1D, 0x02
	.byte 0x95, 0x47, 0x06, 0x02

	.global MOD85_021DF99C
MOD85_021DF99C: ; 0x021DF99C
	.byte 0x54, 0x00, 0x00, 0x00, 0x6D, 0xDF, 0x1D, 0x02, 0xE1, 0xE0, 0x1D, 0x02, 0x05, 0xE1, 0x1D, 0x02
	.byte 0x95, 0x47, 0x06, 0x02

	.global MOD85_021DF9B0
MOD85_021DF9B0: ; 0x021DF9B0
	.byte 0x14, 0x00, 0x00, 0x00, 0xFD, 0xDB, 0x1D, 0x02, 0x8D, 0xDC, 0x1D, 0x02, 0x99, 0xDC, 0x1D, 0x02
	.byte 0x95, 0x47, 0x06, 0x02

	.global MOD85_021DF9C4
MOD85_021DF9C4: ; 0x021DF9C4
	.byte 0x30, 0x00, 0x00, 0x00, 0x5D, 0xE1, 0x1D, 0x02, 0x2D, 0xE2, 0x1D, 0x02, 0x51, 0xE2, 0x1D, 0x02
	.byte 0x95, 0x47, 0x06, 0x02

	.global MOD85_021DF9D8
MOD85_021DF9D8: ; 0x021DF9D8
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00

	.global MOD85_021DF9F0
MOD85_021DF9F0: ; 0x021DF9F0
	.byte 0x78, 0xF8, 0x1D, 0x02, 0x88, 0xF8, 0x1D, 0x02, 0x84, 0xF7, 0x1D, 0x02, 0x94, 0xF6, 0x1D, 0x02
	.byte 0x00, 0xF7, 0x1D, 0x02, 0xEC, 0xF5, 0x1D, 0x02, 0xC4, 0xF5, 0x1D, 0x02

	.global MOD85_021DFA0C
MOD85_021DFA0C: ; 0x021DFA0C
	.byte 0x00, 0x80, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0xC0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DFA2C
MOD85_021DFA2C: ; 0x021DFA2C
	.byte 0xF0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DFA4C
MOD85_021DFA4C: ; 0x021DFA4C
	.byte 0x00, 0xE0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DFA6C
MOD85_021DFA6C: ; 0x021DFA6C
	.byte 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00

	.global MOD85_021DFA8C
MOD85_021DFA8C: ; 0x021DFA8C
	.byte 0xDC, 0xF5, 0x1D, 0x02, 0x68, 0xF8, 0x1D, 0x02, 0xC0, 0xF7, 0x1D, 0x02, 0xB4, 0xF5, 0x1D, 0x02
	.byte 0xE4, 0xF5, 0x1D, 0x02, 0xD4, 0xF5, 0x1D, 0x02, 0xCC, 0xF5, 0x1D, 0x02, 0xBC, 0xF5, 0x1D, 0x02
	.byte 0x34, 0xF6, 0x1D, 0x02

	.global MOD85_021DFAB0
MOD85_021DFAB0: ; 0x021DFAB0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DFAD8
MOD85_021DFAD8: ; 0x021DFAD8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DFB00
MOD85_021DFB00: ; 0x021DFB00
	.byte 0x30, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x34, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00
	.byte 0x30, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00

	.global MOD85_021DFB30
MOD85_021DFB30: ; 0x021DFB30
	.byte 0x18, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00
	.byte 0x1C, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00
	.byte 0x24, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00
	.byte 0x28, 0x00, 0x00, 0x00, 0x2B, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x00, 0x00

	.global MOD85_021DFB80
MOD85_021DFB80: ; 0x021DFB80
	.byte 0x00, 0x40, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00
	.byte 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x0B, 0x00, 0x00, 0x00, 0x05, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x0B, 0x00
	.byte 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x04, 0x00, 0x00, 0x00, 0x07, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0xC0, 0x0B, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x04, 0x00
	.byte 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x05, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x0B, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x40, 0x04, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00
	.byte 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x0B, 0x00, 0x00, 0x00, 0x03, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD85_021DFC34
MOD85_021DFC34: ; 0x021DFC34
	.byte 0x50, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
	.byte 0x50, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00

	.global MOD85_021DFC4C
MOD85_021DFC4C: ; 0x021DFC4C
	.byte 0x64, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00

	.global MOD85_021DFC64
MOD85_021DFC64: ; 0x021DFC64
	.byte 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00

	.global MOD85_021DFC7C
MOD85_021DFC7C: ; 0x021DFC7C
	.byte 0x19, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00
	.byte 0x23, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00

	.global MOD85_021DFC94
MOD85_021DFC94: ; 0x021DFC94
	.byte 0x19, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00
	.byte 0x23, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00

	.global MOD85_021DFCAC
MOD85_021DFCAC: ; 0x021DFCAC
	.byte 0x64, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00

	.global MOD85_021DFCC4
MOD85_021DFCC4: ; 0x021DFCC4
	.byte 0x32, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x46, 0x00, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x00

	.global MOD85_021DFCDC
MOD85_021DFCDC: ; 0x021DFCDC
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00

	.global MOD85_021DFCF4
MOD85_021DFCF4: ; 0x021DFCF4
	.byte 0x19, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00

	.global MOD85_021DFD24
MOD85_021DFD24: ; 0x021DFD24
	.byte 0x01, 0x00, 0x04, 0x00, 0x02, 0x00, 0x0D, 0x00, 0x01, 0x00, 0x27, 0x00, 0x01, 0x00, 0x27, 0x00
	.byte 0x01, 0x00, 0x04, 0x00, 0x02, 0x00, 0x0D, 0x00, 0x01, 0x00, 0x27, 0x00, 0x01, 0x00, 0x27, 0x00
	.byte 0x02, 0x00, 0x03, 0x00, 0x04, 0x00, 0x0B, 0x00, 0x02, 0x00, 0x26, 0x00, 0x02, 0x00, 0x26, 0x00
	.byte 0x03, 0x00, 0x02, 0x00, 0x04, 0x00, 0x0B, 0x00, 0x02, 0x00, 0x26, 0x00, 0x02, 0x00, 0x26, 0x00
	.byte 0x04, 0x00, 0x01, 0x00, 0x06, 0x00, 0x09, 0x00, 0x03, 0x00, 0x25, 0x00, 0x03, 0x00, 0x25, 0x00
	.byte 0x04, 0x00, 0x01, 0x00, 0x06, 0x00, 0x09, 0x00, 0x03, 0x00, 0x25, 0x00, 0x03, 0x00, 0x25, 0x00

	.global MOD85_021DFD84
MOD85_021DFD84: ; 0x021DFD84
	.byte 0x05, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00

	.global MOD85_021DFDE4
MOD85_021DFDE4: ; 0x021DFDE4
	.byte 0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00

	.global MOD85_021DFEE0
MOD85_021DFEE0: ; 0x021DFEE0
	.byte 0x05, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x4B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x4B, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x4B, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x4B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x4B, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x4B, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x4B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x4B, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x4B, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD85_021E0090
MOD85_021E0090: ; 0x021E0090
	.byte 0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD85_021E0240
MOD85_021E0240: ; 0x021E0240
	.byte 0x4B, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
	.byte 0x41, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00
	.byte 0x37, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x2D, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00
	.byte 0x23, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x19, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x4B, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
	.byte 0x41, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00
	.byte 0x37, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x2D, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00
	.byte 0x23, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x19, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x4B, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
	.byte 0x41, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00
	.byte 0x37, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x2D, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00
	.byte 0x23, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x19, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x4B, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
	.byte 0x41, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00
	.byte 0x37, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x2D, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00
	.byte 0x23, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x19, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x4B, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
	.byte 0x41, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00
	.byte 0x37, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x2D, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00
	.byte 0x23, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x19, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x4B, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
	.byte 0x41, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00
	.byte 0x37, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x2D, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00
	.byte 0x23, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x19, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00

	.data
	.global MOD85_021E05C0
MOD85_021E05C0: ; 0x021E05C0
	.byte 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.bss
