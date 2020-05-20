	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0202D4C4
FUN_0202D4C4: ; 0x0202D4C4
	ldr r3, [r0, #0x1c]
	mov r2, #0x0
	ldr r1, [r0, #0x18]
	cmp r3, #0x0
	ble _0202D4E0
_0202D4CE:
	ldrb r0, [r1, #0xe]
	cmp r0, #0x0
	bne _0202D4D8
	add r0, r1, #0x0
	bx lr
_0202D4D8:
	add r2, r2, #0x1
	add r1, #0x10
	cmp r2, r3
	blt _0202D4CE
_0202D4E0:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0202D4E4
FUN_0202D4E4: ; 0x0202D4E4
	ldr r3, [r0, #0x1c]
	mov r2, #0x0
	ldr r1, [r0, #0x18]
	cmp r3, #0x0
	ble _0202D500
_0202D4EE:
	ldrb r0, [r1, #0xe]
	cmp r0, #0x0
	beq _0202D4F8
	mov r0, #0x0
	bx lr
_0202D4F8:
	add r2, r2, #0x1
	add r1, #0x10
	cmp r2, r3
	blt _0202D4EE
_0202D500:
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_0202D504
FUN_0202D504: ; 0x0202D504
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0202D522
	ldr r1, [r1, #0x8]
	cmp r1, #0x0
	beq _0202D518
	str r1, [r0, #0x0]
	mov r0, #0x0
	str r0, [r1, #0x4]
	b _0202D51E
_0202D518:
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
_0202D51E:
	mov r0, #0x1
	bx lr
_0202D522:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0202D528
FUN_0202D528: ; 0x0202D528
	ldr r2, [r0, #0x0]
	strb r1, [r2, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x4]
	sub r1, r1, #0x1
	str r1, [r0, #0x4]
	bne _0202D53E
	mov r0, #0x1
	bx lr
_0202D53E:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0202D544
FUN_0202D544: ; 0x0202D544
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldrb r0, [r5, #0xe]
	add r4, r1, #0x0
	bl FUN_0202D9A0
	add r6, r0, #0x0
	ldr r0, _0202D5B8 ; =0x0000FFFF
	cmp r6, r0
	ldr r0, [r4, #0x4]
	bne _0202D56A
	cmp r0, #0x3
	bge _0202D57A
	ldrb r1, [r5, #0xf]
	mov r0, #0x1
	bic r1, r0
	strb r1, [r5, #0xf]
	mov r0, #0x1
	pop {r4-r6, pc}
_0202D56A:
	cmp r0, #0x1
	bge _0202D57A
	ldrb r1, [r5, #0xf]
	mov r0, #0x1
	bic r1, r0
	strb r1, [r5, #0xf]
	mov r0, #0x1
	pop {r4-r6, pc}
_0202D57A:
	ldrb r1, [r5, #0xe]
	add r0, r4, #0x0
	bl FUN_0202D528
	ldr r0, _0202D5B8 ; =0x0000FFFF
	cmp r6, r0
	bne _0202D5A4
	ldrh r1, [r5, #0xc]
	add r0, r4, #0x0
	asr r1, r1, #0x8
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_0202D528
	ldrh r1, [r5, #0xc]
	add r0, r4, #0x0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_0202D528
	b _0202D5A6
_0202D5A4:
	strh r6, [r5, #0xc]
_0202D5A6:
	ldrb r1, [r5, #0xf]
	mov r0, #0x1
	bic r1, r0
	mov r0, #0x1
	orr r0, r1
	strb r0, [r5, #0xf]
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_0202D5B8: .word 0x0000FFFF

	thumb_func_start FUN_0202D5BC
FUN_0202D5BC: ; 0x0202D5BC
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldrb r0, [r5, #0xe]
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_0202D9A0
	ldr r1, _0202D680 ; =0x0000FFFF
	cmp r0, r1
	bne _0202D5D6
	mov r2, #0x3
	b _0202D5D8
_0202D5D6:
	mov r2, #0x1
_0202D5D8:
	ldrh r0, [r5, #0xc]
	ldr r1, [r4, #0x4]
	add r0, r0, r2
	cmp r1, r0
	bge _0202D5EA
	cmp r7, #0x0
	bne _0202D5EA
	mov r0, #0x0
	pop {r3-r7, pc}
_0202D5EA:
	ldrb r0, [r5, #0xf]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	cmp r0, #0x1
	beq _0202D604
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202D544
	cmp r0, #0x0
	beq _0202D604
	mov r0, #0x0
	pop {r3-r7, pc}
_0202D604:
	ldrh r3, [r5, #0xc]
	ldr r2, [r4, #0x4]
	cmp r2, r3
	ldrb r0, [r5, #0xf]
	bge _0202D64E
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	beq _0202D61E
	ldr r1, [r4, #0x0]
	add r0, r6, #0x0
	bl FUN_0202D400
	b _0202D634
_0202D61E:
	mov r3, #0x0
	cmp r2, #0x0
	ble _0202D634
_0202D624:
	ldr r0, [r5, #0x0]
	ldrb r1, [r0, r3]
	ldr r0, [r4, #0x0]
	strb r1, [r0, r3]
	ldr r0, [r4, #0x4]
	add r3, r3, #0x1
	cmp r3, r0
	blt _0202D624
_0202D634:
	ldr r1, [r5, #0x0]
	ldr r0, [r4, #0x4]
	add r0, r1, r0
	str r0, [r5, #0x0]
	ldrh r1, [r5, #0xc]
	ldr r0, [r4, #0x4]
	sub r0, r1, r0
	strh r0, [r5, #0xc]
	mov r0, #0x0
	mvn r0, r0
	str r0, [r4, #0x4]
	mov r0, #0x1
	pop {r3-r7, pc}
_0202D64E:
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	beq _0202D660
	ldr r1, [r4, #0x0]
	add r0, r6, #0x0
	add r2, r3, #0x0
	bl FUN_0202D400
	b _0202D66A
_0202D660:
	ldr r0, [r5, #0x0]
	ldr r1, [r4, #0x0]
	add r2, r3, #0x0
	bl MI_CpuCopy8
_0202D66A:
	ldrh r0, [r5, #0xc]
	ldr r1, [r4, #0x0]
	add r0, r1, r0
	str r0, [r4, #0x0]
	ldrh r0, [r5, #0xc]
	ldr r1, [r4, #0x4]
	sub r0, r1, r0
	str r0, [r4, #0x4]
	mov r0, #0x1
	pop {r3-r7, pc}
	nop
_0202D680: .word 0x0000FFFF

	thumb_func_start FUN_0202D684
FUN_0202D684: ; 0x0202D684
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	add r7, r3, #0x0
	bl FUN_0202D4C4
	add r4, r0, #0x0
	bne _0202D69E
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_0202D69E:
	ldr r0, _0202D710 ; =0x0000FFFE
	cmp r7, r0
	blt _0202D6A8
	bl ErrorHandling
_0202D6A8:
	ldr r0, [sp, #0x0]
	bl FUN_0202D9A0
	add r6, r0, #0x0
	ldr r0, _0202D714 ; =0x0000FFFF
	cmp r6, r0
	bne _0202D6B8
	add r6, r7, #0x0
_0202D6B8:
	ldr r0, [sp, #0x24]
	cmp r0, #0x0
	beq _0202D6EA
	ldr r0, [r5, #0x14]
	bl FUN_0202D498
	add r1, r6, #0x3
	cmp r1, r0
	blt _0202D6D0
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_0202D6D0:
	ldr r0, [r5, #0x14]
	ldr r1, [sp, #0x4]
	ldr r3, _0202D718 ; =0x00000109
	add r2, r6, #0x0
	bl FUN_0202D3A4
	ldr r0, [r5, #0x14]
	bl FUN_0202D4BC
	ldrb r1, [r4, #0xf]
	mov r0, #0x2
	orr r0, r1
	strb r0, [r4, #0xf]
_0202D6EA:
	ldr r0, [sp, #0x0]
	strh r6, [r4, #0xc]
	strb r0, [r4, #0xe]
	ldr r0, [sp, #0x4]
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	bne _0202D700
	str r4, [r5, #0x4]
	str r4, [r5, #0x0]
	b _0202D708
_0202D700:
	str r4, [r0, #0x8]
	ldr r0, [r5, #0x4]
	str r0, [r4, #0x4]
	str r4, [r5, #0x4]
_0202D708:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0202D710: .word 0x0000FFFE
_0202D714: .word 0x0000FFFF
_0202D718: .word 0x00000109

	thumb_func_start FUN_0202D71C
FUN_0202D71C: ; 0x0202D71C
	ldr r1, [r0, #0x10]
	cmp r1, #0x0
	beq _0202D726
	add r0, r1, #0x0
	bx lr
_0202D726:
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0202D730
	add r0, r1, #0x0
	bx lr
_0202D730:
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	bne _0202D738
	mov r0, #0x0
_0202D738:
	bx lr
	.balign 4

	thumb_func_start FUN_0202D73C
FUN_0202D73C: ; 0x0202D73C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x10]
	cmp r1, #0x0
	beq _0202D74C
	mov r0, #0x0
	str r0, [r4, #0x10]
	pop {r4, pc}
_0202D74C:
	bl FUN_0202D504
	cmp r0, #0x0
	bne _0202D75C
	add r4, #0x8
	add r0, r4, #0x0
	bl FUN_0202D504
_0202D75C:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202D760
FUN_0202D760: ; 0x0202D760
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x4]
	mov r7, #0x1
	str r2, [sp, #0x0]
	cmp r0, #0x0
	ble _0202D7B6
_0202D770:
	add r0, r5, #0x0
	bl FUN_0202D71C
	add r6, r0, #0x0
	beq _0202D7B6
	add r0, r5, #0x0
	bl FUN_0202D73C
	ldr r2, [r5, #0x14]
	add r0, r6, #0x0
	add r1, r4, #0x0
	add r3, r7, #0x0
	bl FUN_0202D5BC
	cmp r0, #0x0
	bne _0202D794
	str r6, [r5, #0x10]
	b _0202D7B6
_0202D794:
	mov r0, #0x0
	ldr r1, [r4, #0x4]
	mvn r0, r0
	cmp r1, r0
	bne _0202D7A4
	str r6, [r5, #0x10]
	mov r0, #0x0
	pop {r3-r7, pc}
_0202D7A4:
	add r0, r6, #0x0
	mov r1, #0x0
	mov r2, #0x10
	bl MI_CpuFill8
	ldr r0, [r4, #0x4]
	ldr r7, [sp, #0x0]
	cmp r0, #0x0
	bgt _0202D770
_0202D7B6:
	ldr r0, [r4, #0x4]
	mov r2, #0x0
	cmp r0, #0x0
	ble _0202D7D2
	mov r1, #0xee
_0202D7C0:
	ldr r0, [r4, #0x0]
	add r2, r2, #0x1
	strb r1, [r0, #0x0]
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	ldr r0, [r4, #0x4]
	cmp r2, r0
	blt _0202D7C0
_0202D7D2:
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202D7D8
FUN_0202D7D8: ; 0x0202D7D8
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r6, r2, #0x0
	mov r1, #0x0
	mov r2, #0x20
	add r5, r0, #0x0
	bl MI_CpuFill8
	lsl r7, r4, #0x4
	mov r0, #0xf
	add r1, r7, #0x0
	bl FUN_02016998
	mov r1, #0x0
	add r2, r7, #0x0
	str r0, [r5, #0x18]
	bl MI_CpuFill8
	str r4, [r5, #0x1c]
	str r6, [r5, #0x14]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202D804
FUN_0202D804: ; 0x0202D804
	push {r4, lr}
	add r4, r0, #0x0
	ldr r2, [r4, #0x1c]
	ldr r0, [r4, #0x18]
	mov r1, #0x0
	lsl r2, r2, #0x4
	bl MI_CpuFill8
	mov r0, #0x0
	str r0, [r4, #0x0]
	str r0, [r4, #0x4]
	str r0, [r4, #0x8]
	str r0, [r4, #0xc]
	str r0, [r4, #0x10]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202D824
FUN_0202D824: ; 0x0202D824
	ldr r3, _0202D82C ; =FUN_02016A18
	ldr r0, [r0, #0x18]
	bx r3
	nop
_0202D82C: .word FUN_02016A18

	thumb_func_start FUN_0202D830
FUN_0202D830: ; 0x0202D830
	push {r3-r4}
	ldr r4, [r0, #0x1c]
	mov r2, #0x0
	ldr r3, [r0, #0x18]
	cmp r4, #0x0
	ble _0202D850
_0202D83C:
	ldrb r0, [r3, #0xe]
	cmp r0, r1
	bne _0202D848
	mov r0, #0x1
	pop {r3-r4}
	bx lr
_0202D848:
	add r2, r2, #0x1
	add r3, #0x10
	cmp r2, r4
	blt _0202D83C
_0202D850:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	.balign 4
