	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD82_0222D5C0
MOD82_0222D5C0: ; 0x0222D5C0
	push {r3, r4}
	ldr r3, _0222D5D8 ; =0x0222FB00
	mov r4, #1
	str r4, [r3]
	mov r4, #0
	str r4, [r3, #4]
	str r0, [r3, #8]
	str r1, [r3, #0xc]
	str r2, [r3, #0x10]
	pop {r3, r4}
	bx lr
	nop
_0222D5D8: .word 0x0222FB00
	thumb_func_end MOD82_0222D5C0

	thumb_func_start MOD82_0222D5DC
MOD82_0222D5DC: ; 0x0222D5DC
	push {r3, lr}
	ldr r1, _0222D7B8 ; =0x0222FB00
	ldr r0, [r1]
	cmp r0, #0xa
	bls _0222D5E8
	b _0222D7B4
_0222D5E8:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222D5F4: ; jump table
	.short _0222D7B4 - _0222D5F4 - 2 ; case 0
	.short _0222D7B4 - _0222D5F4 - 2 ; case 1
	.short _0222D60A - _0222D5F4 - 2 ; case 2
	.short _0222D7A8 - _0222D5F4 - 2 ; case 3
	.short _0222D654 - _0222D5F4 - 2 ; case 4
	.short _0222D7A8 - _0222D5F4 - 2 ; case 5
	.short _0222D6C4 - _0222D5F4 - 2 ; case 6
	.short _0222D7A8 - _0222D5F4 - 2 ; case 7
	.short _0222D736 - _0222D5F4 - 2 ; case 8
	.short _0222D7A8 - _0222D5F4 - 2 ; case 9
	.short _0222D7B4 - _0222D5F4 - 2 ; case 10
_0222D60A:
	bl MOD79_022123A8
	cmp r0, #1
	beq _0222D618
	cmp r0, #7
	beq _0222D630
	pop {r3, pc}
_0222D618:
	ldr r0, _0222D7B8 ; =0x0222FB00
	mov r1, #0xa
	str r1, [r0]
	bl MOD79_02212474
	bl MOD82_0222D99C
	ldr r1, _0222D7B8 ; =0x0222FB00
	str r0, [r1, #4]
	bl MOD56_0221244C
	pop {r3, pc}
_0222D630:
	ldr r0, _0222D7B8 ; =0x0222FB00
	mov r1, #0xa
	str r1, [r0]
	bl MOD79_02212480
	cmp r0, #0
	ble _0222D646
	ldr r0, _0222D7BC ; =0x0222FC00
	ldrb r1, [r0, #3]
	ldr r0, _0222D7B8 ; =0x0222FB00
	b _0222D64C
_0222D646:
	mov r1, #1
	ldr r0, _0222D7B8 ; =0x0222FB00
	mvn r1, r1
_0222D64C:
	str r1, [r0, #4]
	bl MOD56_0221244C
	pop {r3, pc}
_0222D654:
	bl MOD79_022123A8
	cmp r0, #1
	beq _0222D662
	cmp r0, #7
	beq _0222D67A
	pop {r3, pc}
_0222D662:
	ldr r0, _0222D7B8 ; =0x0222FB00
	mov r1, #0xa
	str r1, [r0]
	bl MOD79_02212474
	bl MOD82_0222D99C
	ldr r1, _0222D7B8 ; =0x0222FB00
	str r0, [r1, #4]
	bl MOD56_0221244C
	pop {r3, pc}
_0222D67A:
	ldr r0, _0222D7B8 ; =0x0222FB00
	mov r1, #0xa
	str r1, [r0]
	bl MOD79_02212480
	ldr r1, _0222D7C0 ; =0x00000A38
	cmp r0, r1
	bne _0222D692
	ldr r0, _0222D7B8 ; =0x0222FB00
	mov r1, #0
	str r1, [r0, #4]
	b _0222D6BE
_0222D692:
	ldr r0, _0222D7BC ; =0x0222FC00
	ldr r0, [r0, #8]
	ldrb r0, [r0]
	cmp r0, #2
	beq _0222D6A2
	cmp r0, #5
	beq _0222D6AC
	b _0222D6B6
_0222D6A2:
	mov r1, #2
	ldr r0, _0222D7B8 ; =0x0222FB00
	mvn r1, r1
	str r1, [r0, #4]
	b _0222D6BE
_0222D6AC:
	mov r1, #1
	ldr r0, _0222D7B8 ; =0x0222FB00
	mvn r1, r1
	str r1, [r0, #4]
	b _0222D6BE
_0222D6B6:
	mov r1, #4
	ldr r0, _0222D7B8 ; =0x0222FB00
	mvn r1, r1
	str r1, [r0, #4]
_0222D6BE:
	bl MOD56_0221244C
	pop {r3, pc}
_0222D6C4:
	bl MOD79_022123A8
	cmp r0, #1
	beq _0222D6D2
	cmp r0, #7
	beq _0222D6EA
	pop {r3, pc}
_0222D6D2:
	ldr r0, _0222D7B8 ; =0x0222FB00
	mov r1, #0xa
	str r1, [r0]
	bl MOD79_02212474
	bl MOD82_0222D99C
	ldr r1, _0222D7B8 ; =0x0222FB00
	str r0, [r1, #4]
	bl MOD56_0221244C
	pop {r3, pc}
_0222D6EA:
	ldr r0, _0222D7B8 ; =0x0222FB00
	mov r1, #0xa
	ldr r2, _0222D7BC ; =0x0222FC00
	str r1, [r0]
	ldrb r2, [r2, #3]
	cmp r2, #5
	bhi _0222D728
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0222D704: ; jump table
	.short _0222D728 - _0222D704 - 2 ; case 0
	.short _0222D710 - _0222D704 - 2 ; case 1
	.short _0222D716 - _0222D704 - 2 ; case 2
	.short _0222D728 - _0222D704 - 2 ; case 3
	.short _0222D71C - _0222D704 - 2 ; case 4
	.short _0222D722 - _0222D704 - 2 ; case 5
_0222D710:
	mov r1, #0
	str r1, [r0, #4]
	b _0222D730
_0222D716:
	sub r1, #0xd
	str r1, [r0, #4]
	b _0222D730
_0222D71C:
	sub r1, #0xb
	str r1, [r0, #4]
	b _0222D730
_0222D722:
	sub r1, #0xc
	str r1, [r0, #4]
	b _0222D730
_0222D728:
	mov r1, #4
	ldr r0, _0222D7B8 ; =0x0222FB00
	mvn r1, r1
	str r1, [r0, #4]
_0222D730:
	bl MOD56_0221244C
	pop {r3, pc}
_0222D736:
	bl MOD79_022123A8
	cmp r0, #1
	beq _0222D744
	cmp r0, #7
	beq _0222D75C
	pop {r3, pc}
_0222D744:
	ldr r0, _0222D7B8 ; =0x0222FB00
	mov r1, #0xa
	str r1, [r0]
	bl MOD79_02212474
	bl MOD82_0222D99C
	ldr r1, _0222D7B8 ; =0x0222FB00
	str r0, [r1, #4]
	bl MOD56_0221244C
	pop {r3, pc}
_0222D75C:
	ldr r0, _0222D7B8 ; =0x0222FB00
	mov r1, #0xa
	ldr r2, _0222D7BC ; =0x0222FC00
	str r1, [r0]
	ldrb r2, [r2, #3]
	cmp r2, #5
	bhi _0222D79A
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0222D776: ; jump table
	.short _0222D79A - _0222D776 - 2 ; case 0
	.short _0222D782 - _0222D776 - 2 ; case 1
	.short _0222D79A - _0222D776 - 2 ; case 2
	.short _0222D788 - _0222D776 - 2 ; case 3
	.short _0222D78E - _0222D776 - 2 ; case 4
	.short _0222D794 - _0222D776 - 2 ; case 5
_0222D782:
	mov r1, #0
	str r1, [r0, #4]
	b _0222D7A2
_0222D788:
	mov r1, #1
	str r1, [r0, #4]
	b _0222D7A2
_0222D78E:
	mov r1, #2
	str r1, [r0, #4]
	b _0222D7A2
_0222D794:
	sub r1, #0xc
	str r1, [r0, #4]
	b _0222D7A2
_0222D79A:
	mov r1, #4
	ldr r0, _0222D7B8 ; =0x0222FB00
	mvn r1, r1
	str r1, [r0, #4]
_0222D7A2:
	bl MOD56_0221244C
	pop {r3, pc}
_0222D7A8:
	mov r0, #0xa
	str r0, [r1]
	sub r0, #0xe
	str r0, [r1, #4]
	bl MOD56_0221244C
_0222D7B4:
	pop {r3, pc}
	nop
_0222D7B8: .word 0x0222FB00
_0222D7BC: .word 0x0222FC00
_0222D7C0: .word 0x00000A38
	thumb_func_end MOD82_0222D5DC

	thumb_func_start MOD82_0222D7C4
MOD82_0222D7C4: ; 0x0222D7C4
	ldr r1, _0222D7E0 ; =0x0222FB00
	ldr r0, [r1]
	cmp r0, #1
	beq _0222D7D2
	cmp r0, #0xa
	beq _0222D7D6
	b _0222D7DC
_0222D7D2:
	mov r0, #1
	bx lr
_0222D7D6:
	mov r0, #1
	str r0, [r1]
	bx lr
_0222D7DC:
	mov r0, #0
	bx lr
	.align 2, 0
_0222D7E0: .word 0x0222FB00
	thumb_func_end MOD82_0222D7C4

	thumb_func_start MOD82_0222D7E4
MOD82_0222D7E4: ; 0x0222D7E4
	ldr r0, _0222D7EC ; =0x0222FB00
	ldr r0, [r0, #4]
	bx lr
	nop
_0222D7EC: .word 0x0222FB00
	thumb_func_end MOD82_0222D7E4

	thumb_func_start MOD82_0222D7F0
MOD82_0222D7F0: ; 0x0222D7F0
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	bl MOD79_022122E4
	ldr r0, _0222D830 ; =0x0222FB00
	sub r1, r4, #1
	strb r1, [r0, #0x14]
	mov r0, #2
	str r0, [sp]
	ldr r0, _0222D834 ; =0x0222F8E0
	ldr r1, _0222D838 ; =0x0222FB14
	ldr r3, _0222D83C ; =0x0222FC03
	mov r2, #1
	bl MOD82_0222D964
	cmp r0, #0
	beq _0222D81E
	ldr r0, _0222D830 ; =0x0222FB00
	mov r1, #2
	str r1, [r0]
	add sp, #4
	pop {r3, r4, pc}
_0222D81E:
	ldr r0, _0222D830 ; =0x0222FB00
	mov r1, #0xa
	str r1, [r0]
	sub r1, #0xf
	str r1, [r0, #4]
	bl MOD56_0221244C
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0222D830: .word 0x0222FB00
_0222D834: .word 0x0222F8E0
_0222D838: .word 0x0222FB14
_0222D83C: .word 0x0222FC03
	thumb_func_end MOD82_0222D7F0

	thumb_func_start MOD82_0222D840
MOD82_0222D840: ; 0x0222D840
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	ldr r0, _0222D88C ; =0x0222FC00
	add r6, r2, #0
	add r4, r1, #0
	str r6, [r0, #8]
	bl MOD79_022122E4
	ldr r0, _0222D890 ; =0x0222FB00
	sub r1, r5, #1
	strb r1, [r0, #0x14]
	sub r1, r4, #1
	strb r1, [r0, #0x15]
	ldr r0, _0222D894 ; =0x00000A38
	ldr r1, _0222D898 ; =0x0222FB14
	str r0, [sp]
	ldr r0, _0222D89C ; =0x0222F92C
	mov r2, #2
	add r3, r6, #0
	bl MOD82_0222D964
	cmp r0, #0
	beq _0222D87A
	ldr r0, _0222D890 ; =0x0222FB00
	mov r1, #4
	str r1, [r0]
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0222D87A:
	ldr r0, _0222D890 ; =0x0222FB00
	mov r1, #0xa
	str r1, [r0]
	sub r1, #0xf
	str r1, [r0, #4]
	bl MOD56_0221244C
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0222D88C: .word 0x0222FC00
_0222D890: .word 0x0222FB00
_0222D894: .word 0x00000A38
_0222D898: .word 0x0222FB14
_0222D89C: .word 0x0222F92C
	thumb_func_end MOD82_0222D840

	thumb_func_start MOD82_0222D8A0
MOD82_0222D8A0: ; 0x0222D8A0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl MOD79_022122E4
	ldr r0, _0222D904 ; =0x0222FB14
	add r1, r7, #0
	mov r2, #0xe4
	bl memcpy
	ldr r0, _0222D908 ; =0x0222FBE0
	sub r1, r5, #1
	strb r1, [r0, #0x18]
	sub r1, r4, #1
	strb r1, [r0, #0x19]
	ldr r3, _0222D90C ; =0x0222FBFB
	ldr r2, _0222D910 ; =0x0222FB0C
	strb r6, [r0, #0x1a]
	mov r1, #8
_0222D8CA:
	ldrb r0, [r2]
	add r2, r2, #1
	strb r0, [r3]
	add r3, r3, #1
	sub r1, r1, #1
	bne _0222D8CA
	mov r0, #2
	str r0, [sp]
	ldr r0, _0222D914 ; =0x0222F978
	ldr r1, _0222D904 ; =0x0222FB14
	ldr r3, _0222D918 ; =0x0222FC03
	mov r2, #0xef
	bl MOD82_0222D964
	cmp r0, #0
	beq _0222D8F2
	ldr r0, _0222D91C ; =0x0222FB00
	mov r1, #6
	str r1, [r0]
	pop {r3, r4, r5, r6, r7, pc}
_0222D8F2:
	ldr r0, _0222D91C ; =0x0222FB00
	mov r1, #0xa
	str r1, [r0]
	sub r1, #0xf
	str r1, [r0, #4]
	bl MOD56_0221244C
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222D904: .word 0x0222FB14
_0222D908: .word 0x0222FBE0
_0222D90C: .word 0x0222FBFB
_0222D910: .word 0x0222FB0C
_0222D914: .word 0x0222F978
_0222D918: .word 0x0222FC03
_0222D91C: .word 0x0222FB00
	thumb_func_end MOD82_0222D8A0

	thumb_func_start MOD82_0222D920
MOD82_0222D920: ; 0x0222D920
	push {r3, lr}
	bl MOD79_022122E4
	mov r0, #2
	str r0, [sp]
	ldr r0, _0222D954 ; =0x0222F9C4
	ldr r1, _0222D958 ; =0x0222FB14
	ldr r3, _0222D95C ; =0x0222FC03
	mov r2, #0
	bl MOD82_0222D964
	cmp r0, #0
	beq _0222D942
	ldr r0, _0222D960 ; =0x0222FB00
	mov r1, #8
	str r1, [r0]
	pop {r3, pc}
_0222D942:
	ldr r0, _0222D960 ; =0x0222FB00
	mov r1, #0xa
	str r1, [r0]
	sub r1, #0xf
	str r1, [r0, #4]
	bl MOD56_0221244C
	pop {r3, pc}
	nop
_0222D954: .word 0x0222F9C4
_0222D958: .word 0x0222FB14
_0222D95C: .word 0x0222FC03
_0222D960: .word 0x0222FB00
	thumb_func_end MOD82_0222D920

	thumb_func_start MOD82_0222D964
MOD82_0222D964: ; 0x0222D964
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r1, #0
	ldr r1, [sp, #0x18]
	str r3, [sp]
	str r1, [sp, #4]
	add r4, r2, #0
	ldr r1, _0222D998 ; =0x0222FB00
	add r2, r5, #0
	ldr r1, [r1, #8]
	add r3, r4, #0
	bl MOD79_02212308
	cmp r0, #0
	beq _0222D98A
	cmp r0, #1
	beq _0222D990
	cmp r0, #2
	b _0222D990
_0222D98A:
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222D990:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_0222D998: .word 0x0222FB00
	thumb_func_end MOD82_0222D964

	thumb_func_start MOD82_0222D99C
MOD82_0222D99C: ; 0x0222D99C
	push {r4, lr}
	cmp r0, #0x20
	bhi _0222DA14
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222D9AE: ; jump table
	.short _0222D9F0 - _0222D9AE - 2 ; case 0
	.short _0222D9F0 - _0222D9AE - 2 ; case 1
	.short _0222D9F6 - _0222D9AE - 2 ; case 2
	.short _0222D9F0 - _0222D9AE - 2 ; case 3
	.short _0222D9F0 - _0222D9AE - 2 ; case 4
	.short _0222D9F0 - _0222D9AE - 2 ; case 5
	.short _0222D9F0 - _0222D9AE - 2 ; case 6
	.short _0222DA14 - _0222D9AE - 2 ; case 7
	.short _0222D9F6 - _0222D9AE - 2 ; case 8
	.short _0222D9F0 - _0222D9AE - 2 ; case 9
	.short _0222D9F0 - _0222D9AE - 2 ; case 10
	.short _0222D9FC - _0222D9AE - 2 ; case 11
	.short _0222DA02 - _0222D9AE - 2 ; case 12
	.short _0222DA02 - _0222D9AE - 2 ; case 13
	.short _0222D9F0 - _0222D9AE - 2 ; case 14
	.short _0222DA0E - _0222D9AE - 2 ; case 15
	.short _0222DA08 - _0222D9AE - 2 ; case 16
	.short _0222DA08 - _0222D9AE - 2 ; case 17
	.short _0222DA08 - _0222D9AE - 2 ; case 18
	.short _0222DA08 - _0222D9AE - 2 ; case 19
	.short _0222D9F0 - _0222D9AE - 2 ; case 20
	.short _0222D9F0 - _0222D9AE - 2 ; case 21
	.short _0222D9F0 - _0222D9AE - 2 ; case 22
	.short _0222D9F0 - _0222D9AE - 2 ; case 23
	.short _0222DA14 - _0222D9AE - 2 ; case 24
	.short _0222D9F6 - _0222D9AE - 2 ; case 25
	.short _0222DA08 - _0222D9AE - 2 ; case 26
	.short _0222DA08 - _0222D9AE - 2 ; case 27
	.short _0222DA08 - _0222D9AE - 2 ; case 28
	.short _0222DA08 - _0222D9AE - 2 ; case 29
	.short _0222DA0E - _0222D9AE - 2 ; case 30
	.short _0222DA08 - _0222D9AE - 2 ; case 31
	.short _0222D9F0 - _0222D9AE - 2 ; case 32
_0222D9F0:
	mov r4, #4
	mvn r4, r4
	b _0222DA18
_0222D9F6:
	mov r4, #4
	mvn r4, r4
	b _0222DA18
_0222D9FC:
	mov r4, #6
	mvn r4, r4
	b _0222DA18
_0222DA02:
	mov r4, #6
	mvn r4, r4
	b _0222DA18
_0222DA08:
	mov r4, #1
	mvn r4, r4
	b _0222DA18
_0222DA0E:
	mov r4, #1
	mvn r4, r4
	b _0222DA18
_0222DA14:
	mov r4, #4
	mvn r4, r4
_0222DA18:
	mov r0, #4
	mvn r0, r0
	cmp r4, r0
	beq _0222DA30
	bl WCM_GetPhase
	cmp r0, #9
	beq _0222DA2C
	mov r4, #5
	mvn r4, r4
_0222DA2C:
	bl MOD04_021DD6F0
_0222DA30:
	add r0, r4, #0
	pop {r4, pc}
	thumb_func_end MOD82_0222D99C

	thumb_func_start MOD82_0222DA34
MOD82_0222DA34: ; 0x0222DA34
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5]
	cmp r0, #0
	beq _0222DA48
	cmp r0, #1
	beq _0222DB34
	b _0222DB4A
_0222DA48:
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	bl FUN_02015F1C
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _0222DB50 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _0222DB54 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r2, #5
	mov r0, #3
	mov r1, #0x44
	lsl r2, r2, #0x10
	bl FUN_0201681C
	ldr r1, _0222DB58 ; =0x00000EC8
	add r0, r6, #0
	mov r2, #0x44
	bl FUN_02006268
	ldr r2, _0222DB58 ; =0x00000EC8
	mov r1, #0
	add r4, r0, #0
	bl memset
	mov r0, #0x44
	bl FUN_02016B94
	str r0, [r4, #4]
	ldr r0, _0222DB5C ; =0x0222FC0C
	add r2, sp, #0
	ldr r3, _0222DB60 ; =0x0222F814
	str r4, [r0]
	add r7, r2, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r7, #0
	bl FUN_02016BBC
	mov r0, #0xb
	mov r1, #0x20
	mov r2, #0x44
	bl FUN_0200AA90
	ldr r1, _0222DB64 ; =0x00000B78
	ldr r2, _0222DB68 ; =0x0000024E
	str r0, [r4, r1]
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x44
	bl FUN_0200A86C
	ldr r1, _0222DB6C ; =0x00000B7C
	mov r2, #0x25
	str r0, [r4, r1]
	mov r0, #0
	mov r1, #0x1a
	lsl r2, r2, #4
	mov r3, #0x44
	bl FUN_0200A86C
	mov r1, #0x2e
	lsl r1, r1, #6
	str r0, [r4, r1]
	ldr r2, _0222DB70 ; =0x00000265
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x44
	bl FUN_0200A86C
	ldr r1, _0222DB74 ; =0x00000B84
	str r0, [r4, r1]
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	add r0, r4, #0
	add r1, r6, #0
	bl MOD82_0222DD04
	add r0, r4, #0
	bl MOD82_0222DFD4
	mov r1, #0
	mov r0, #0x34
	add r2, r1, #0
	bl FUN_0200433C
	ldr r1, _0222DB78 ; =0x00020020
	mov r0, #0x44
	bl FUN_02016998
	str r0, [r4, #0x24]
	add r0, #0x1f
	mov r1, #0x1f
	bic r0, r1
	mov r1, #2
	lsl r1, r1, #0x10
	mov r2, #0
	bl tempName_NNS_FndCreateExpHeapEx
	str r0, [r4, #0x28]
	mov r0, #1
	str r0, [r5]
	b _0222DB4A
_0222DB34:
	bl FUN_02088858
	bl FUN_020888BC
	bl FUN_0202E49C
	mov r0, #0
	str r0, [r5]
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0222DB4A:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222DB50: .word 0xFFFFE0FF
_0222DB54: .word 0x04001000
_0222DB58: .word 0x00000EC8
_0222DB5C: .word 0x0222FC0C
_0222DB60: .word 0x0222F814
_0222DB64: .word 0x00000B78
_0222DB68: .word 0x0000024E
_0222DB6C: .word 0x00000B7C
_0222DB70: .word 0x00000265
_0222DB74: .word 0x00000B84
_0222DB78: .word 0x00020020
	thumb_func_end MOD82_0222DA34

	thumb_func_start MOD82_0222DB7C
MOD82_0222DB7C: ; 0x0222DB7C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	bl FUN_02006278
	add r5, r0, #0
	bl MOD04_021DD984
	bl MOD82_0222D5DC
	bl MOD04_021DD984
	ldr r1, [r4]
	cmp r1, #5
	bhi _0222DC24
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222DBA4: ; jump table
	.short _0222DBB0 - _0222DBA4 - 2 ; case 0
	.short _0222DBCC - _0222DBA4 - 2 ; case 1
	.short _0222DBE0 - _0222DBA4 - 2 ; case 2
	.short _0222DBEE - _0222DBA4 - 2 ; case 3
	.short _0222DC02 - _0222DBA4 - 2 ; case 4
	.short _0222DC20 - _0222DBA4 - 2 ; case 5
_0222DBB0:
	bl FUN_0202E4C8
	cmp r0, #0
	beq _0222DC24
	ldr r1, [r5, #0x28]
	ldr r0, _0222DC38 ; =0x0222FC0C
	str r1, [r0, #4]
	ldr r0, _0222DC3C ; =MOD82_0222DF74
	ldr r1, _0222DC40 ; =MOD82_0222DF9C
	bl MOD04_021DD968
	mov r0, #1
	str r0, [r4]
	b _0222DC24
_0222DBCC:
	ldr r3, [r5, #0x10]
	mov r2, #0xc
	add r6, r3, #0
	mul r6, r2
	ldr r2, _0222DC44 ; =0x0222FA0C
	add r0, r5, #0
	ldr r2, [r2, r6]
	blx r2
	str r0, [r4]
	b _0222DC24
_0222DBE0:
	bl FUN_0200E308
	cmp r0, #0
	beq _0222DC24
	mov r0, #3
	str r0, [r4]
	b _0222DC24
_0222DBEE:
	ldr r3, [r5, #0x10]
	mov r2, #0xc
	add r6, r3, #0
	mul r6, r2
	ldr r2, _0222DC48 ; =0x0222FA10
	add r0, r5, #0
	ldr r2, [r2, r6]
	blx r2
	str r0, [r4]
	b _0222DC24
_0222DC02:
	bl FUN_0200E308
	cmp r0, #0
	beq _0222DC24
	ldr r3, [r5, #0x10]
	mov r2, #0xc
	add r6, r3, #0
	mul r6, r2
	ldr r2, _0222DC4C ; =0x0222FA14
	ldr r1, [r4]
	ldr r2, [r2, r6]
	add r0, r5, #0
	blx r2
	str r0, [r4]
	b _0222DC24
_0222DC20:
	mov r0, #1
	pop {r4, r5, r6, pc}
_0222DC24:
	mov r0, #0xba
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _0222DC32
	bl FUN_0201FDEC
_0222DC32:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_0222DC38: .word 0x0222FC0C
_0222DC3C: .word MOD82_0222DF74
_0222DC40: .word MOD82_0222DF9C
_0222DC44: .word 0x0222FA0C
_0222DC48: .word 0x0222FA10
_0222DC4C: .word 0x0222FA14
	thumb_func_end MOD82_0222DB7C

	thumb_func_start MOD82_0222DC50
MOD82_0222DC50: ; 0x0222DC50
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02006278
	add r4, r0, #0
	ldr r0, [r4, #0x24]
	bl FUN_02016A18
	bl FUN_020888CC
	bl FUN_02088868
	add r0, r4, #0
	bl MOD82_0222DFFC
	ldr r0, _0222DCB8 ; =0x00000B84
	ldr r0, [r4, r0]
	bl FUN_0200A8B8
	mov r0, #0x2e
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	bl FUN_0200A8B8
	ldr r0, _0222DCBC ; =0x00000B7C
	ldr r0, [r4, r0]
	bl FUN_0200A8B8
	ldr r0, _0222DCC0 ; =0x00000B78
	ldr r0, [r4, r0]
	bl FUN_0200AB18
	add r0, r4, #0
	bl MOD82_0222DD20
	bl FUN_0202E4F0
	ldr r0, [r4, #4]
	bl FUN_02016A18
	add r0, r5, #0
	bl FUN_0200627C
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	mov r0, #0x44
	bl FUN_020168D0
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222DCB8: .word 0x00000B84
_0222DCBC: .word 0x00000B7C
_0222DCC0: .word 0x00000B78
	thumb_func_end MOD82_0222DC50

	thumb_func_start MOD82_0222DCC4
MOD82_0222DCC4: ; 0x0222DCC4
	push {r3, lr}
	bl FUN_0201C30C
	bl FUN_02009F80
	ldr r3, _0222DCDC ; =0x027E0000
	ldr r1, _0222DCE0 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r3, pc}
	.align 2, 0
_0222DCDC: .word 0x027E0000
_0222DCE0: .word 0x00003FF8
	thumb_func_end MOD82_0222DCC4

	thumb_func_start MOD82_0222DCE4
MOD82_0222DCE4: ; 0x0222DCE4
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _0222DD00 ; =0x0222F834
	add r3, sp, #0
	mov r2, #5
_0222DCEE:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222DCEE
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_0222DD00: .word 0x0222F834
	thumb_func_end MOD82_0222DCE4

	thumb_func_start MOD82_0222DD04
MOD82_0222DD04: ; 0x0222DD04
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	bl FUN_0200628C
	mov r1, #0
	str r0, [r4]
	add r0, r4, #0
	add r2, r1, #0
	str r1, [r4, #0x10]
	bl MOD82_0222DFCC
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD82_0222DD04

	thumb_func_start MOD82_0222DD20
MOD82_0222DD20: ; 0x0222DD20
	bx lr
	.align 2, 0
	thumb_func_end MOD82_0222DD20

	thumb_func_start MOD82_0222DD24
MOD82_0222DD24: ; 0x0222DD24
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _0222DD50 ; =0x0222F824
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_0201D040
	mov r0, #0x14
	mov r1, #0x44
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_0222DD50: .word 0x0222F824
	thumb_func_end MOD82_0222DD24

	thumb_func_start MOD82_0222DD54
MOD82_0222DD54: ; 0x0222DD54
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r1, #0x7e
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x44
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	ldr r1, _0222DE40 ; =0x00000BA4
	mov r0, #0xa
	add r1, r6, r1
	mov r2, #0x44
	bl FUN_02008C9C
	mov r1, #0xba
	lsl r1, r1, #4
	str r0, [r6, r1]
	add r0, r1, #4
	mov r2, #1
	add r0, r6, r0
	mov r1, #0
	lsl r2, r2, #0x14
	bl FUN_02008D24
	ldr r7, _0222DE44 ; =0x00000CCC
	mov r4, #0
	add r5, r6, #0
_0222DD9C:
	mov r0, #2
	add r1, r4, #0
	mov r2, #0x44
	bl FUN_02008DEC
	str r0, [r5, r7]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0222DD9C
	mov r0, #0
	str r0, [sp]
	mov r3, #1
	str r3, [sp, #4]
	mov r0, #0x44
	str r0, [sp, #8]
	ldr r0, _0222DE44 ; =0x00000CCC
	mov r1, #0x68
	ldr r0, [r6, r0]
	mov r2, #0x23
	bl FUN_02008F34
	ldr r1, _0222DE48 ; =0x00000CDC
	mov r3, #0
	str r0, [r6, r1]
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	mov r0, #0x44
	sub r1, #0xc
	str r0, [sp, #0xc]
	ldr r0, [r6, r1]
	mov r1, #0x68
	mov r2, #9
	bl FUN_02008FEC
	mov r1, #0xce
	lsl r1, r1, #4
	str r0, [r6, r1]
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x44
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r6, r1]
	mov r1, #0x68
	mov r2, #0x24
	mov r3, #1
	bl FUN_020090AC
	ldr r1, _0222DE4C ; =0x00000CE4
	mov r2, #0x25
	str r0, [r6, r1]
	mov r0, #0
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x44
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r6, r1]
	mov r1, #0x68
	mov r3, #1
	bl FUN_020090AC
	ldr r1, _0222DE50 ; =0x00000CE8
	str r0, [r6, r1]
	sub r1, #0xc
	ldr r0, [r6, r1]
	bl FUN_02009A50
	mov r0, #0xce
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	bl FUN_02009CF0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0222DE40: .word 0x00000BA4
_0222DE44: .word 0x00000CCC
_0222DE48: .word 0x00000CDC
_0222DE4C: .word 0x00000CE4
_0222DE50: .word 0x00000CE8
	thumb_func_end MOD82_0222DD54

	thumb_func_start MOD82_0222DE54
MOD82_0222DE54: ; 0x0222DE54
	push {r3, r4}
	mov r4, #0xba
	lsl r4, r4, #4
	ldr r1, [r1, r4]
	str r1, [r0]
	str r2, [r0, #4]
	mov r2, #0
	mov r1, #1
	str r2, [r0, #0x10]
	lsl r1, r1, #0xc
	str r1, [r0, #0x14]
	str r1, [r0, #0x18]
	str r1, [r0, #0x1c]
	strh r2, [r0, #0x20]
	mov r1, #1
	str r1, [r0, #0x24]
	str r3, [r0, #0x28]
	mov r1, #0x44
	str r1, [r0, #0x2c]
	pop {r3, r4}
	bx lr
	.align 2, 0
	thumb_func_end MOD82_0222DE54

	thumb_func_start MOD82_0222DE80
MOD82_0222DE80: ; 0x0222DE80
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	mov r1, #0
	add r5, r0, #0
	str r1, [sp]
	sub r0, r1, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, _0222DF28 ; =0x00000CCC
	str r1, [sp, #0x10]
	ldr r0, [r5, r2]
	add r3, r1, #0
	str r0, [sp, #0x14]
	add r0, r2, #4
	ldr r0, [r5, r0]
	str r0, [sp, #0x18]
	add r0, r2, #0
	add r0, #8
	ldr r0, [r5, r0]
	str r0, [sp, #0x1c]
	add r0, r2, #0
	add r0, #0xc
	ldr r0, [r5, r0]
	add r2, #0x40
	str r0, [sp, #0x20]
	str r1, [sp, #0x24]
	add r0, r5, r2
	add r2, r1, #0
	str r1, [sp, #0x28]
	bl FUN_02008AA4
	ldr r2, _0222DF2C ; =0x00000D0C
	add r0, sp, #0x2c
	add r1, r5, #0
	add r2, r5, r2
	mov r3, #1
	bl MOD82_0222DE54
	ldr r4, _0222DF30 ; =0x0222F80C
	ldr r7, _0222DF34 ; =0x00000D78
	mov r6, #0
_0222DED4:
	ldrh r0, [r4]
	lsl r0, r0, #0xc
	str r0, [sp, #0x34]
	ldrh r0, [r4, #2]
	lsl r0, r0, #0xc
	str r0, [sp, #0x38]
	add r0, sp, #0x2c
	bl FUN_0201FE94
	ldr r1, _0222DF34 ; =0x00000D78
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, _0222DF34 ; =0x00000D78
	add r1, r6, #0
	ldr r0, [r5, r0]
	bl FUN_02020130
	ldr r0, [r5, r7]
	mov r1, #0
	bl FUN_020200A0
	add r6, r6, #1
	add r4, r4, #4
	add r5, r5, #4
	cmp r6, #2
	blt _0222DED4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	bl FUN_02033E74
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0222DF28: .word 0x00000CCC
_0222DF2C: .word 0x00000D0C
_0222DF30: .word 0x0222F80C
_0222DF34: .word 0x00000D78
	thumb_func_end MOD82_0222DE80

	thumb_func_start MOD82_0222DF38
MOD82_0222DF38: ; 0x0222DF38
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	ldr r5, _0222DF68 ; =0x0222F804
	add r4, sp, #4
	ldrh r6, [r5]
	add r3, sp, #4
	strh r6, [r4]
	ldrh r6, [r5, #2]
	strh r6, [r4, #2]
	ldrh r6, [r5, #4]
	ldrh r5, [r5, #6]
	strh r6, [r4, #4]
	strh r5, [r4, #6]
	strb r1, [r4, #2]
	strh r2, [r4, #6]
	mov r1, #0x44
	str r1, [sp]
	add r1, r3, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_02002198
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0222DF68: .word 0x0222F804
	thumb_func_end MOD82_0222DF38

	thumb_func_start MOD82_0222DF6C
MOD82_0222DF6C: ; 0x0222DF6C
	str r1, [r0, #0x1c]
	str r2, [r0, #0x20]
	bx lr
	.align 2, 0
	thumb_func_end MOD82_0222DF6C

	thumb_func_start MOD82_0222DF74
MOD82_0222DF74: ; 0x0222DF74
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	bl OS_DisableInterrupts
	add r6, r0, #0
	ldr r0, _0222DF98 ; =0x0222FC0C
	add r1, r5, #0
	ldr r0, [r0, #4]
	add r2, r4, #0
	bl tempName_NNS_FndAllocFromExpHeapEx
	add r4, r0, #0
	add r0, r6, #0
	bl OS_RestoreInterrupts
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222DF98: .word 0x0222FC0C
	thumb_func_end MOD82_0222DF74

	thumb_func_start MOD82_0222DF9C
MOD82_0222DF9C: ; 0x0222DF9C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	beq _0222DFB8
	bl OS_DisableInterrupts
	add r4, r0, #0
	ldr r0, _0222DFBC ; =0x0222FC0C
	add r1, r5, #0
	ldr r0, [r0, #4]
	bl FUN_020ADDF0
	add r0, r4, #0
	bl OS_RestoreInterrupts
_0222DFB8:
	pop {r3, r4, r5, pc}
	nop
_0222DFBC: .word 0x0222FC0C
	thumb_func_end MOD82_0222DF9C

	thumb_func_start MOD82_0222DFC0
MOD82_0222DFC0: ; 0x0222DFC0
	push {r3, lr}
	bl MOD04_021DDB08
	mov r1, #3
	sub r0, r1, r0
	pop {r3, pc}
	thumb_func_end MOD82_0222DFC0

	thumb_func_start MOD82_0222DFCC
MOD82_0222DFCC: ; 0x0222DFCC
	str r1, [r0, #0x14]
	str r2, [r0, #0x18]
	bx lr
	.align 2, 0
	thumb_func_end MOD82_0222DFCC

	thumb_func_start MOD82_0222DFD4
MOD82_0222DFD4: ; 0x0222DFD4
	push {r4, lr}
	add r4, r0, #0
	bl MOD82_0222DCE4
	bl MOD82_0222DD24
	add r0, r4, #0
	bl MOD82_0222DD54
	add r0, r4, #0
	bl MOD82_0222DE80
	ldr r0, _0222DFF8 ; =MOD82_0222DCC4
	mov r1, #0
	bl FUN_02015F10
	pop {r4, pc}
	nop
_0222DFF8: .word MOD82_0222DCC4
	thumb_func_end MOD82_0222DFD4

	thumb_func_start MOD82_0222DFFC
MOD82_0222DFFC: ; 0x0222DFFC
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, _0222E048 ; =0x00000CDC
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	mov r0, #0xce
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	bl FUN_02009E04
	ldr r7, _0222E04C ; =0x00000CCC
	mov r4, #0
	add r5, r6, #0
_0222E018:
	ldr r0, [r5, r7]
	bl FUN_02008E2C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0222E018
	mov r0, #0xba
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	bl FUN_0201FD58
	mov r0, #0xba
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r6, r0]
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E048: .word 0x00000CDC
_0222E04C: .word 0x00000CCC
	thumb_func_end MOD82_0222DFFC

	thumb_func_start MOD82_0222E050
MOD82_0222E050: ; 0x0222E050
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD82_0222E4AC
	mov r0, #8
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x44
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldr r0, [r4, #4]
	bl MOD82_0222E15C
	add r0, r4, #0
	bl MOD82_0222E264
	add r0, r4, #0
	bl MOD82_0222E35C
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	mov r0, #2
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E74C
	mov r0, #2
	mov r1, #1
	bl FUN_0201E74C
	ldr r0, [r4]
	ldr r0, [r0, #0xc]
	bl FUN_02033288
	add r0, r4, #0
	bl MOD82_0222F6D0
	ldr r0, [r4]
	mov r1, #0
	ldr r0, [r0]
	bl FUN_0202A444
	str r0, [r4, #0x38]
	str r0, [r4, #0x3c]
	mov r0, #1
	str r0, [r4, #0x44]
	ldr r0, _0222E110 ; =0x00000EB4
	mov r1, #0
	str r1, [r4, r0]
	bl MOD04_021DDD7C
	cmp r0, #0
	bne _0222E104
	ldr r0, [r4]
	ldr r0, [r0, #0x24]
	cmp r0, #0
	beq _0222E0FE
	ldr r0, _0222E114 ; =0x00000F0F
	mov r1, #0x2e
	str r0, [sp]
	lsl r1, r1, #6
	mov r2, #1
	ldr r1, [r4, r1]
	add r0, r4, #0
	add r3, r2, #0
	bl MOD82_0222F59C
	add r0, r4, #0
	mov r1, #0x2d
	mov r2, #2
	bl MOD82_0222DF6C
	add r0, r4, #0
	bl MOD82_0222F700
	b _0222E108
_0222E0FE:
	mov r0, #0
	str r0, [r4, #0x1c]
	b _0222E108
_0222E104:
	mov r0, #0x31
	str r0, [r4, #0x1c]
_0222E108:
	mov r0, #2
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_0222E110: .word 0x00000EB4
_0222E114: .word 0x00000F0F
	thumb_func_end MOD82_0222E050

	thumb_func_start MOD82_0222E118
MOD82_0222E118: ; 0x0222E118
	push {r4, lr}
	add r4, r0, #0
	bl MOD82_0222DFC0
	bl FUN_02033EEC
	ldr r1, [r4, #0x1c]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _0222E134 ; =0x0222FA18
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
	nop
_0222E134: .word 0x0222FA18
	thumb_func_end MOD82_0222E118

	thumb_func_start MOD82_0222E138
MOD82_0222E138: ; 0x0222E138
	push {r4, lr}
	add r4, r0, #0
	bl MOD82_0222E504
	add r0, r4, #0
	bl MOD82_0222E474
	ldr r0, [r4, #4]
	bl MOD82_0222E240
	ldr r0, [r4, #0x14]
	str r0, [r4, #0x10]
	cmp r0, #0
	bne _0222E158
	mov r0, #5
	pop {r4, pc}
_0222E158:
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD82_0222E138

	thumb_func_start MOD82_0222E15C
MOD82_0222E15C: ; 0x0222E15C
	push {r3, r4, r5, lr}
	sub sp, #0x70
	ldr r5, _0222E230 ; =0x0222F894
	add r4, r0, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0x54
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
	mov r0, #1
	mov r1, #0
	bl FUN_0201E6E4
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _0222E234 ; =0x0222F878
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
	mov r0, #2
	mov r1, #0
	bl FUN_0201E6E4
	ldr r5, _0222E238 ; =0x0222F8B0
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #4
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #1
	mov r1, #0
	bl FUN_0201E74C
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	ldr r5, _0222E23C ; =0x0222F85C
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #5
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #2
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x44
	bl FUN_02017F18
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x44
	bl FUN_02017F18
	add sp, #0x70
	pop {r3, r4, r5, pc}
	nop
_0222E230: .word 0x0222F894
_0222E234: .word 0x0222F878
_0222E238: .word 0x0222F8B0
_0222E23C: .word 0x0222F85C
	thumb_func_end MOD82_0222E15C

	thumb_func_start MOD82_0222E240
MOD82_0222E240: ; 0x0222E240
	push {r4, lr}
	add r4, r0, #0
	mov r1, #5
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #4
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #0
	bl FUN_020178A0
	pop {r4, pc}
	thumb_func_end MOD82_0222E240

	thumb_func_start MOD82_0222E264
MOD82_0222E264: ; 0x0222E264
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r4, [r5, #4]
	mov r2, #0
	str r2, [sp]
	mov r0, #0x44
	str r0, [sp, #4]
	mov r0, #0x5c
	mov r1, #3
	add r3, r2, #0
	bl FUN_02006930
	mov r3, #0
	str r3, [sp]
	mov r0, #0x44
	str r0, [sp, #4]
	mov r0, #0x5c
	mov r1, #3
	mov r2, #4
	bl FUN_02006930
	mov r1, #0x1a
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x44
	bl FUN_02002EEC
	mov r1, #0x1a
	mov r0, #4
	lsl r1, r1, #4
	mov r2, #0x44
	bl FUN_02002EEC
	ldr r0, [r5]
	ldr r0, [r0, #0x10]
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x44
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200CD68
	mov r1, #0
	str r1, [sp]
	mov r0, #0x44
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_0200CB00
	mov r1, #0
	mov r0, #0x36
	str r1, [sp]
	lsl r0, r0, #6
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0x44
	str r0, [sp, #0xc]
	mov r0, #0x5c
	mov r1, #2
	add r2, r4, #0
	mov r3, #1
	bl FUN_0200687C
	mov r1, #0
	mov r0, #6
	str r1, [sp]
	lsl r0, r0, #8
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0x44
	str r0, [sp, #0xc]
	mov r0, #0x5c
	mov r1, #4
	add r2, r4, #0
	mov r3, #1
	bl FUN_020068C8
	mov r1, #0
	mov r0, #0x36
	str r1, [sp]
	lsl r0, r0, #6
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0x44
	str r0, [sp, #0xc]
	mov r0, #0x5c
	mov r1, #9
	add r2, r4, #0
	mov r3, #5
	bl FUN_0200687C
	mov r1, #0
	mov r0, #6
	str r1, [sp]
	lsl r0, r0, #8
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0x44
	str r0, [sp, #0xc]
	mov r0, #0x5c
	mov r1, #0xa
	add r2, r4, #0
	mov r3, #5
	bl FUN_020068C8
	mov r0, #0
	add r1, r0, #0
	bl FUN_02017FE4
	mov r0, #4
	mov r1, #0
	bl FUN_02017FE4
	add sp, #0x10
	pop {r3, r4, r5, pc}
	thumb_func_end MOD82_0222E264

	thumb_func_start MOD82_0222E35C
MOD82_0222E35C: ; 0x0222E35C
	push {r3, r4, lr}
	sub sp, #0x14
	mov r3, #4
	add r4, r0, #0
	str r3, [sp]
	mov r0, #0x17
	str r0, [sp, #4]
	mov r0, #0x10
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0xa4
	mov r1, #0x37
	str r0, [sp, #0x10]
	lsl r1, r1, #6
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	bl FUN_02019064
	mov r0, #0x37
	lsl r0, r0, #6
	add r0, r4, r0
	mov r1, #0
	bl FUN_02019620
	mov r0, #0xe
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x94
	mov r1, #0xda
	str r0, [sp, #0x10]
	lsl r1, r1, #4
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #0x1a
	bl FUN_02019064
	mov r0, #0xda
	lsl r0, r0, #4
	add r0, r4, r0
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0xe
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x9c
	mov r1, #0xd9
	str r0, [sp, #0x10]
	lsl r1, r1, #4
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #0x1a
	bl FUN_02019064
	mov r0, #0xd9
	lsl r0, r0, #4
	add r0, r4, r0
	mov r1, #0xf
	bl FUN_02019620
	mov r2, #1
	mov r1, #0xdb
	lsl r1, r1, #4
	str r2, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #0x85
	lsl r0, r0, #2
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r3, #4
	bl FUN_02019064
	mov r0, #0xdb
	lsl r0, r0, #4
	add r0, r4, r0
	mov r1, #6
	bl FUN_02019620
	mov r3, #1
	ldr r0, _0222E46C ; =0x00010406
	str r3, [sp]
	str r0, [sp, #4]
	ldr r1, _0222E470 ; =0x00000B8C
	mov r0, #0xdb
	lsl r0, r0, #4
	ldr r1, [r4, r1]
	add r0, r4, r0
	mov r2, #0
	bl MOD82_0222F62C
	mov r0, #0x13
	str r0, [sp]
	mov r1, #0x1b
	str r1, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x28
	str r0, [sp, #0x10]
	lsl r1, r1, #7
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #2
	bl FUN_02019064
	mov r0, #0x36
	lsl r0, r0, #6
	add r0, r4, r0
	mov r1, #0xf
	bl FUN_02019620
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_0222E46C: .word 0x00010406
_0222E470: .word 0x00000B8C
	thumb_func_end MOD82_0222E35C

	thumb_func_start MOD82_0222E474
MOD82_0222E474: ; 0x0222E474
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x36
	lsl r0, r0, #6
	add r0, r4, r0
	bl FUN_02019178
	mov r0, #0xdb
	lsl r0, r0, #4
	add r0, r4, r0
	bl FUN_02019178
	mov r0, #0xd9
	lsl r0, r0, #4
	add r0, r4, r0
	bl FUN_02019178
	mov r0, #0xda
	lsl r0, r0, #4
	add r0, r4, r0
	bl FUN_02019178
	mov r0, #0x37
	lsl r0, r0, #6
	add r0, r4, r0
	bl FUN_02019178
	pop {r4, pc}
	thumb_func_end MOD82_0222E474

	thumb_func_start MOD82_0222E4AC
MOD82_0222E4AC: ; 0x0222E4AC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xb4
	mov r1, #0x44
	bl FUN_020219F4
	ldr r1, _0222E4F4 ; =0x00000B88
	str r0, [r4, r1]
	mov r0, #4
	mov r1, #0x44
	bl FUN_020219F4
	mov r1, #0xb9
	lsl r1, r1, #4
	str r0, [r4, r1]
	mov r0, #3
	mov r1, #0x44
	bl FUN_020219F4
	ldr r1, _0222E4F8 ; =0x00000B94
	str r0, [r4, r1]
	sub r1, #0x18
	ldr r0, [r4, r1]
	mov r1, #0xa
	bl FUN_0200A914
	ldr r1, _0222E4FC ; =0x00000B8C
	str r0, [r4, r1]
	mov r0, #1
	lsl r0, r0, #8
	mov r1, #0x44
	bl FUN_020219F4
	ldr r1, _0222E500 ; =0x00000B98
	str r0, [r4, r1]
	pop {r4, pc}
	.align 2, 0
_0222E4F4: .word 0x00000B88
_0222E4F8: .word 0x00000B94
_0222E4FC: .word 0x00000B8C
_0222E500: .word 0x00000B98
	thumb_func_end MOD82_0222E4AC

	thumb_func_start MOD82_0222E504
MOD82_0222E504: ; 0x0222E504
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222E534 ; =0x00000B98
	ldr r0, [r4, r0]
	bl FUN_02021A20
	ldr r0, _0222E538 ; =0x00000B8C
	ldr r0, [r4, r0]
	bl FUN_02021A20
	ldr r0, _0222E53C ; =0x00000B94
	ldr r0, [r4, r0]
	bl FUN_02021A20
	mov r0, #0xb9
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_02021A20
	ldr r0, _0222E540 ; =0x00000B88
	ldr r0, [r4, r0]
	bl FUN_02021A20
	pop {r4, pc}
	.align 2, 0
_0222E534: .word 0x00000B98
_0222E538: .word 0x00000B8C
_0222E53C: .word 0x00000B94
_0222E540: .word 0x00000B88
	thumb_func_end MOD82_0222E504

	thumb_func_start MOD82_0222E544
MOD82_0222E544: ; 0x0222E544
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222E56C ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	ldr r1, _0222E570 ; =0x00000B84
	mov r2, #0x10
	ldr r1, [r4, r1]
	mov r3, #1
	bl MOD82_0222F59C
	add r0, r4, #0
	mov r1, #0x2e
	mov r2, #1
	bl MOD82_0222DF6C
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_0222E56C: .word 0x00000F0F
_0222E570: .word 0x00000B84
	thumb_func_end MOD82_0222E544

	thumb_func_start MOD82_0222E574
MOD82_0222E574: ; 0x0222E574
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #0xeb
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0x44
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0222E5CC
	sub r1, r1, #1
	cmp r0, r1
	bne _0222E5A8
	bl FUN_020332DC
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl MOD82_0222DFCC
	mov r0, #0x2c
	str r0, [r4, #0x1c]
	b _0222E5CC
_0222E5A8:
	ldr r0, _0222E5D4 ; =0x00000F0F
	mov r1, #0x2e
	str r0, [sp]
	lsl r1, r1, #6
	mov r2, #1
	ldr r1, [r4, r1]
	add r0, r4, #0
	add r3, r2, #0
	bl MOD82_0222F59C
	add r0, r4, #0
	mov r1, #0x2d
	mov r2, #2
	bl MOD82_0222DF6C
	add r0, r4, #0
	bl MOD82_0222F700
_0222E5CC:
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_0222E5D4: .word 0x00000F0F
	thumb_func_end MOD82_0222E574

	thumb_func_start MOD82_0222E5D8
MOD82_0222E5D8: ; 0x0222E5D8
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222E600 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r1, #0x2e
	lsl r1, r1, #6
	ldr r1, [r4, r1]
	mov r2, #8
	mov r3, #1
	bl MOD82_0222F59C
	add r0, r4, #0
	mov r1, #0x2e
	mov r2, #0x32
	bl MOD82_0222DF6C
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0222E600: .word 0x00000F0F
	thumb_func_end MOD82_0222E5D8

	thumb_func_start MOD82_0222E604
MOD82_0222E604: ; 0x0222E604
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xeb
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0x44
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0222E656
	sub r1, r1, #1
	cmp r0, r1
	bne _0222E636
	bl MOD04_021DDD7C
	cmp r0, #0
	bne _0222E630
	mov r0, #0
	str r0, [r4, #0x1c]
	b _0222E656
_0222E630:
	mov r0, #0x27
	str r0, [r4, #0x1c]
	b _0222E656
_0222E636:
	bl MOD04_021DDD7C
	cmp r0, #0
	bne _0222E64C
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl MOD82_0222DFCC
	mov r0, #0x2c
	b _0222E64E
_0222E64C:
	mov r0, #0x27
_0222E64E:
	str r0, [r4, #0x1c]
	ldr r0, [r4]
	mov r1, #1
	str r1, [r0, #0x20]
_0222E656:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD82_0222E604

	thumb_func_start MOD82_0222E65C
MOD82_0222E65C: ; 0x0222E65C
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x2c
	mov r1, #2
	mov r2, #1
	mov r3, #0x14
	bl MOD04_021DDEE0
	mov r0, #2
	bl MOD04_021DDE7C
	bl MOD04_021DDDCC
	mov r0, #3
	str r0, [r4, #0x1c]
	pop {r4, pc}
	thumb_func_end MOD82_0222E65C

	thumb_func_start MOD82_0222E67C
MOD82_0222E67C: ; 0x0222E67C
	push {r3, r4, lr}
	sub sp, #0x44
	add r4, r0, #0
	bl MOD04_021DDCE8
	bl MOD04_021DDD7C
	cmp r0, #0
	beq _0222E6E8
	bl MOD04_021DDC1C
	cmp r0, #4
	beq _0222E6DE
	cmp r0, #7
	beq _0222E6A0
	cmp r0, #8
	beq _0222E6C4
	b _0222E6E8
_0222E6A0:
	add r0, sp, #4
	bl MOD04_021DD808
	ldr r1, _0222E6F0 ; =0x00000EB8
	str r0, [r4, r1]
	ldr r2, [sp, #4]
	add r0, r1, #4
	str r2, [r4, r0]
	bl MOD04_021DD6F0
	bl MOD04_021DDBBC
	add r0, r4, #0
	bl MOD82_0222F724
	mov r0, #0x35
	str r0, [r4, #0x1c]
	b _0222E6E8
_0222E6C4:
	add r0, sp, #0
	bl MOD04_021DD808
	add r0, r4, #0
	bl MOD82_0222F724
	mov r1, #0x33
	mov r0, #0x3b
	str r1, [r4, #0x1c]
	sub r1, #0x35
	lsl r0, r0, #6
	str r1, [r4, r0]
	b _0222E6E8
_0222E6DE:
	add r0, sp, #8
	bl MOD04_021DD9DC
	mov r0, #4
	str r0, [r4, #0x1c]
_0222E6E8:
	mov r0, #3
	add sp, #0x44
	pop {r3, r4, pc}
	nop
_0222E6F0: .word 0x00000EB8
	thumb_func_end MOD82_0222E67C

	thumb_func_start MOD82_0222E6F4
MOD82_0222E6F4: ; 0x0222E6F4
	push {r4, lr}
	add r4, r0, #0
	bl MOD04_021DE05C
	cmp r0, #0
	beq _0222E704
	mov r0, #5
	str r0, [r4, #0x1c]
_0222E704:
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD82_0222E6F4

	thumb_func_start MOD82_0222E708
MOD82_0222E708: ; 0x0222E708
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	bl MOD04_021DDF4C
	cmp r0, #3
	beq _0222E720
	cmp r0, #4
	beq _0222E726
	cmp r0, #5
	beq _0222E726
	b _0222E794
_0222E720:
	mov r0, #6
	str r0, [r4, #0x1c]
	b _0222E794
_0222E726:
	add r0, r4, #0
	bl MOD82_0222F724
	add r0, sp, #4
	add r1, sp, #0
	bl MOD04_021DD718
	ldr r1, _0222E79C ; =0x00000EB8
	str r0, [r4, r1]
	ldr r2, [sp, #4]
	add r0, r1, #4
	str r2, [r4, r0]
	bl MOD04_021DD6F0
	bl MOD04_021DDBBC
	ldr r0, [sp]
	cmp r0, #7
	bhi _0222E782
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222E758: ; jump table
	.short _0222E782 - _0222E758 - 2 ; case 0
	.short _0222E768 - _0222E758 - 2 ; case 1
	.short _0222E768 - _0222E758 - 2 ; case 2
	.short _0222E782 - _0222E758 - 2 ; case 3
	.short _0222E76E - _0222E758 - 2 ; case 4
	.short _0222E782 - _0222E758 - 2 ; case 5
	.short _0222E778 - _0222E758 - 2 ; case 6
	.short _0222E77E - _0222E758 - 2 ; case 7
_0222E768:
	mov r0, #0x35
	str r0, [r4, #0x1c]
	b _0222E782
_0222E76E:
	bl MOD04_021EB550
	mov r0, #0x35
	str r0, [r4, #0x1c]
	b _0222E782
_0222E778:
	mov r0, #0x35
	str r0, [r4, #0x1c]
	b _0222E782
_0222E77E:
	bl FUN_020335E0
_0222E782:
	ldr r1, [sp, #4]
	ldr r0, _0222E7A0 ; =0xFFFFB1E0
	cmp r1, r0
	bge _0222E794
	ldr r0, _0222E7A4 ; =0xFFFF8AD1
	cmp r1, r0
	blt _0222E794
	mov r0, #0x35
	str r0, [r4, #0x1c]
_0222E794:
	mov r0, #3
	add sp, #8
	pop {r4, pc}
	nop
_0222E79C: .word 0x00000EB8
_0222E7A0: .word 0xFFFFB1E0
_0222E7A4: .word 0xFFFF8AD1
	thumb_func_end MOD82_0222E708

	thumb_func_start MOD82_0222E7A8
MOD82_0222E7A8: ; 0x0222E7A8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	ldr r0, [r0, #8]
	bl FUN_02023830
	cmp r0, #0
	bne _0222E7C2
	ldr r1, [r5]
	ldr r0, [r1, #8]
	ldr r1, [r1, #0x1c]
	bl FUN_02023834
_0222E7C2:
	ldr r0, [r5]
	ldr r0, [r0, #8]
	bl FUN_02023830
	add r4, r0, #0
	ldr r0, [r5]
	ldr r0, [r0, #0x14]
	bl DWC_CreateFriendKey
	add r3, r0, #0
	add r2, r1, #0
	add r0, r4, #0
	add r1, r3, #0
	bl MOD82_0222D5C0
	mov r0, #7
	str r0, [r5, #0x1c]
	mov r0, #3
	pop {r3, r4, r5, pc}
	thumb_func_end MOD82_0222E7A8

	thumb_func_start MOD82_0222E7E8
MOD82_0222E7E8: ; 0x0222E7E8
	push {r4, lr}
	add r4, r0, #0
	bl MOD82_0222D920
	mov r0, #8
	str r0, [r4, #0x1c]
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD82_0222E7E8

	thumb_func_start MOD82_0222E7F8
MOD82_0222E7F8: ; 0x0222E7F8
	push {r4, lr}
	add r4, r0, #0
	bl MOD82_0222D7C4
	cmp r0, #0
	beq _0222E8AA
	bl MOD82_0222D7E4
	add r1, r0, #7
	cmp r1, #9
	bhi _0222E8AA
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222E81A: ; jump table
	.short _0222E882 - _0222E81A - 2 ; case 0
	.short _0222E894 - _0222E81A - 2 ; case 1
	.short _0222E8A6 - _0222E81A - 2 ; case 2
	.short _0222E882 - _0222E81A - 2 ; case 3
	.short _0222E8AA - _0222E81A - 2 ; case 4
	.short _0222E894 - _0222E81A - 2 ; case 5
	.short _0222E870 - _0222E81A - 2 ; case 6
	.short _0222E82E - _0222E81A - 2 ; case 7
	.short _0222E85E - _0222E81A - 2 ; case 8
	.short _0222E870 - _0222E81A - 2 ; case 9
_0222E82E:
	add r0, r4, #0
	bl MOD82_0222F724
	ldr r0, [r4]
	ldr r0, [r0, #0x18]
	cmp r0, #0
	beq _0222E846
	cmp r0, #1
	beq _0222E852
	cmp r0, #2
	beq _0222E858
	b _0222E8AA
_0222E846:
	add r0, r4, #0
	mov r1, #9
	mov r2, #0xb
	bl MOD82_0222DF6C
	b _0222E8AA
_0222E852:
	mov r0, #0x17
	str r0, [r4, #0x1c]
	b _0222E8AA
_0222E858:
	mov r0, #0x1b
	str r0, [r4, #0x1c]
	b _0222E8AA
_0222E85E:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222E8AA
_0222E870:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222E8AA
_0222E882:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222E8AA
_0222E894:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222E8AA
_0222E8A6:
	bl FUN_020335E0
_0222E8AA:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD82_0222E7F8

	thumb_func_start MOD82_0222E8B0
MOD82_0222E8B0: ; 0x0222E8B0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x38]
	bl MOD82_0222D7F0
	mov r0, #0xa
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F700
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD82_0222E8B0

	thumb_func_start MOD82_0222E8C8
MOD82_0222E8C8: ; 0x0222E8C8
	push {r4, lr}
	add r4, r0, #0
	bl MOD82_0222D7C4
	cmp r0, #0
	beq _0222E954
	bl MOD82_0222D7E4
	add r1, r0, #7
	cmp r1, #6
	bhi _0222E944
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222E8EA: ; jump table
	.short _0222E928 - _0222E8EA - 2 ; case 0
	.short _0222E91C - _0222E8EA - 2 ; case 1
	.short _0222E934 - _0222E8EA - 2 ; case 2
	.short _0222E928 - _0222E8EA - 2 ; case 3
	.short _0222E910 - _0222E8EA - 2 ; case 4
	.short _0222E904 - _0222E8EA - 2 ; case 5
	.short _0222E8F8 - _0222E8EA - 2 ; case 6
_0222E8F8:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	b _0222E94E
_0222E904:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	b _0222E94E
_0222E910:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	b _0222E94E
_0222E91C:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	b _0222E94E
_0222E928:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	b _0222E94E
_0222E934:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	bl FUN_020335E0
	b _0222E94E
_0222E944:
	cmp r0, #0
	ble _0222E94E
	str r0, [r4, #0x40]
	ldr r0, [r4, #0x20]
	str r0, [r4, #0x1c]
_0222E94E:
	add r0, r4, #0
	bl MOD82_0222F724
_0222E954:
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD82_0222E8C8

	thumb_func_start MOD82_0222E958
MOD82_0222E958: ; 0x0222E958
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222E980 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	ldr r1, _0222E984 ; =0x00000B7C
	mov r2, #0
	ldr r1, [r4, r1]
	mov r3, #1
	bl MOD82_0222F59C
	add r0, r4, #0
	mov r1, #0x2d
	mov r2, #0xc
	bl MOD82_0222DF6C
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_0222E980: .word 0x00000F0F
_0222E984: .word 0x00000B7C
	thumb_func_end MOD82_0222E958

	thumb_func_start MOD82_0222E988
MOD82_0222E988: ; 0x0222E988
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xda
	lsl r0, r0, #4
	add r0, r4, r0
	mov r1, #0
	mov r2, #0x1f
	mov r3, #0xa
	bl FUN_0200CCA4
	mov r1, #0xb9
	mov r0, #0xda
	lsl r1, r1, #4
	lsl r0, r0, #4
	ldr r1, [r4, r1]
	ldr r2, [r4, #0x44]
	add r0, r4, r0
	mov r3, #3
	bl MOD82_0222F694
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	bl MOD82_0222F6D8
	mov r0, #0xda
	lsl r0, r0, #4
	add r0, r4, r0
	bl FUN_020191D0
	mov r0, #0xd
	str r0, [r4, #0x1c]
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD82_0222E988

	thumb_func_start MOD82_0222E9CC
MOD82_0222E9CC: ; 0x0222E9CC
	push {r3, r4, lr}
	sub sp, #0x1c
	ldr r2, _0222EA9C ; =0x021C48B8
	mov r1, #0x40
	ldr r3, [r2, #0x4c]
	add r4, r0, #0
	tst r1, r3
	beq _0222EA08
	ldr r0, [r4, #0x44]
	add r1, r0, #1
	str r1, [r4, #0x44]
	ldr r0, [r4, #0x40]
	cmp r1, r0
	ble _0222E9EC
	mov r0, #1
	str r0, [r4, #0x44]
_0222E9EC:
	mov r1, #0xb9
	mov r0, #0xda
	lsl r1, r1, #4
	lsl r0, r0, #4
	ldr r1, [r4, r1]
	ldr r2, [r4, #0x44]
	add r0, r4, r0
	mov r3, #3
	bl MOD82_0222F694
	ldr r0, _0222EAA0 ; =0x000005DC
	bl FUN_020054C8
	b _0222EA94
_0222EA08:
	mov r1, #0x80
	tst r1, r3
	beq _0222EA38
	ldr r0, [r4, #0x44]
	sub r0, r0, #1
	str r0, [r4, #0x44]
	cmp r0, #1
	bge _0222EA1C
	ldr r0, [r4, #0x40]
	str r0, [r4, #0x44]
_0222EA1C:
	mov r1, #0xb9
	mov r0, #0xda
	lsl r1, r1, #4
	lsl r0, r0, #4
	ldr r1, [r4, r1]
	ldr r2, [r4, #0x44]
	add r0, r4, r0
	mov r3, #3
	bl MOD82_0222F694
	ldr r0, _0222EAA0 ; =0x000005DC
	bl FUN_020054C8
	b _0222EA94
_0222EA38:
	ldr r2, [r2, #0x48]
	mov r1, #1
	tst r1, r2
	beq _0222EA7C
	add r0, sp, #0
	add r1, sp, #0x10
	bl MOD04_021DE1F8
	ldr r0, [r4]
	ldr r1, [r4, #0x3c]
	ldr r2, [r4, #0x44]
	lsl r1, r1, #0x18
	lsl r2, r2, #0x18
	ldr r0, [r0, #4]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	add r3, sp, #0
	bl FUN_0202A6B4
	cmp r0, #0
	beq _0222EA66
	mov r0, #0x12
	b _0222EA68
_0222EA66:
	mov r0, #0xe
_0222EA68:
	mov r1, #0
	str r0, [r4, #0x1c]
	add r0, r4, #0
	add r2, r1, #0
	bl MOD82_0222F6D8
	ldr r0, _0222EAA0 ; =0x000005DC
	bl FUN_020054C8
	b _0222EA94
_0222EA7C:
	mov r1, #2
	tst r1, r2
	beq _0222EA94
	mov r1, #0
	add r2, r1, #0
	bl MOD82_0222F6D8
	mov r0, #0x13
	str r0, [r4, #0x1c]
	ldr r0, _0222EAA0 ; =0x000005DC
	bl FUN_020054C8
_0222EA94:
	mov r0, #3
	add sp, #0x1c
	pop {r3, r4, pc}
	nop
_0222EA9C: .word 0x021C48B8
_0222EAA0: .word 0x000005DC
	thumb_func_end MOD82_0222E9CC

	thumb_func_start MOD82_0222EAA4
MOD82_0222EAA4: ; 0x0222EAA4
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _0222EB00 ; =0x00000B78
	ldr r2, [r4, #0x44]
	ldr r0, [r4, r0]
	mov r1, #0
	mov r3, #3
	bl FUN_0200AD38
	mov r3, #2
	str r3, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r0, _0222EB00 ; =0x00000B78
	ldr r2, [r4, #0x3c]
	ldr r0, [r4, r0]
	bl FUN_0200AD38
	ldr r0, _0222EB04 ; =0x00000F0F
	mov r2, #1
	str r0, [sp]
	ldr r1, _0222EB08 ; =0x00000B7C
	add r0, r4, #0
	ldr r1, [r4, r1]
	add r3, r2, #0
	bl MOD82_0222F4D8
	add r0, r4, #0
	mov r1, #0x2d
	mov r2, #0xf
	bl MOD82_0222DF6C
	add r4, #0x48
	ldr r2, _0222EB0C ; =0x00000A38
	mov r0, #0
	add r1, r4, #0
	bl MIi_CpuClearFast
	mov r0, #3
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_0222EB00: .word 0x00000B78
_0222EB04: .word 0x00000F0F
_0222EB08: .word 0x00000B7C
_0222EB0C: .word 0x00000A38
	thumb_func_end MOD82_0222EAA4

	thumb_func_start MOD82_0222EB10
MOD82_0222EB10: ; 0x0222EB10
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222EB38 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	ldr r1, _0222EB3C ; =0x00000B7C
	mov r2, #2
	ldr r1, [r4, r1]
	mov r3, #1
	bl MOD82_0222F4D8
	add r0, r4, #0
	mov r1, #0x2d
	mov r2, #0xb
	bl MOD82_0222DF6C
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_0222EB38: .word 0x00000F0F
_0222EB3C: .word 0x00000B7C
	thumb_func_end MOD82_0222EB10

	thumb_func_start MOD82_0222EB40
MOD82_0222EB40: ; 0x0222EB40
	push {r4, lr}
	add r4, r0, #0
	add r2, r4, #0
	ldr r0, [r4, #0x38]
	ldr r1, [r4, #0x44]
	add r2, #0x48
	bl MOD82_0222D840
	add r0, r4, #0
	bl MOD82_0222F700
	mov r0, #0x10
	str r0, [r4, #0x1c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD82_0222EB40

	thumb_func_start MOD82_0222EB60
MOD82_0222EB60: ; 0x0222EB60
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r0, #0
	bl MOD82_0222D7C4
	cmp r0, #0
	beq _0222EC44
	bl MOD82_0222D7E4
	add r1, r0, #7
	cmp r1, #7
	bhi _0222EC44
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222EB84: ; jump table
	.short _0222EC1E - _0222EB84 - 2 ; case 0
	.short _0222EC0C - _0222EB84 - 2 ; case 1
	.short _0222EC30 - _0222EB84 - 2 ; case 2
	.short _0222EBFA - _0222EB84 - 2 ; case 3
	.short _0222EBFA - _0222EB84 - 2 ; case 4
	.short _0222EBE8 - _0222EB84 - 2 ; case 5
	.short _0222EBD6 - _0222EB84 - 2 ; case 6
	.short _0222EB94 - _0222EB84 - 2 ; case 7
_0222EB94:
	ldr r0, [r4]
	ldr r2, [r4, #0x38]
	ldr r3, [r4, #0x44]
	add r1, r4, #0
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r0, #4]
	add r1, #0x48
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_0202A754
	add r0, r4, #0
	mov r1, #0x25
	mov r2, #0x11
	bl MOD82_0222DF6C
	add r0, sp, #0
	add r1, sp, #0x10
	bl MOD04_021DE1F8
	ldr r0, [r4]
	ldr r1, [r4, #0x3c]
	ldr r2, [r4, #0x44]
	lsl r1, r1, #0x18
	lsl r2, r2, #0x18
	ldr r0, [r0, #4]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	add r3, sp, #0
	bl FUN_0202A60C
	b _0222EC44
_0222EBD6:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222EC44
_0222EBE8:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222EC44
_0222EBFA:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #9
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222EC44
_0222EC0C:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222EC44
_0222EC1E:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222EC44
_0222EC30:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	bl FUN_020335E0
_0222EC44:
	mov r0, #3
	add sp, #0x1c
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD82_0222EB60

	thumb_func_start MOD82_0222EC4C
MOD82_0222EC4C: ; 0x0222EC4C
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222EC80 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	ldr r1, _0222EC84 ; =0x00000B7C
	mov r2, #3
	ldr r1, [r4, r1]
	mov r3, #1
	bl MOD82_0222F59C
	add r0, r4, #0
	mov r1, #0x2d
	mov r2, #0x2b
	bl MOD82_0222DF6C
	add r0, r4, #0
	bl MOD82_0222F724
	ldr r0, [r4]
	mov r1, #0
	str r1, [r0, #0x20]
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_0222EC80: .word 0x00000F0F
_0222EC84: .word 0x00000B7C
	thumb_func_end MOD82_0222EC4C

	thumb_func_start MOD82_0222EC88
MOD82_0222EC88: ; 0x0222EC88
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222ECB4 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	ldr r1, _0222ECB8 ; =0x00000B7C
	mov r2, #7
	ldr r1, [r4, r1]
	mov r3, #1
	bl MOD82_0222F59C
	add r0, r4, #0
	mov r1, #0x2d
	mov r2, #0x18
	bl MOD82_0222DF6C
	add r0, r4, #0
	bl MOD82_0222F700
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0222ECB4: .word 0x00000F0F
_0222ECB8: .word 0x00000B7C
	thumb_func_end MOD82_0222EC88

	thumb_func_start MOD82_0222ECBC
MOD82_0222ECBC: ; 0x0222ECBC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	ldr r0, [r0]
	bl FUN_0202A524
	add r4, r0, #0
	ldr r0, [r5]
	add r1, sp, #0
	ldr r0, [r0, #4]
	bl FUN_0202A784
	ldr r0, [r5]
	mov r2, #0x2a
	lsl r2, r2, #6
	ldr r0, [r0, #0xc]
	mov r1, #1
	add r2, r5, r2
	bl FUN_02066840
	add r1, sp, #0
	ldrb r0, [r1]
	mov r3, #0x2a
	lsl r3, r3, #6
	ldrb r1, [r1, #1]
	add r2, r4, #0
	add r3, r5, r3
	bl MOD82_0222D8A0
	mov r0, #0x19
	str r0, [r5, #0x1c]
	mov r0, #3
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD82_0222ECBC

	thumb_func_start MOD82_0222ED00
MOD82_0222ED00: ; 0x0222ED00
	push {r4, lr}
	add r4, r0, #0
	bl MOD82_0222D7C4
	cmp r0, #0
	beq _0222EDB8
	bl MOD82_0222D7E4
	add r1, r0, #7
	cmp r1, #7
	bhi _0222EDB8
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222ED22: ; jump table
	.short _0222ED92 - _0222ED22 - 2 ; case 0
	.short _0222ED80 - _0222ED22 - 2 ; case 1
	.short _0222EDA4 - _0222ED22 - 2 ; case 2
	.short _0222ED92 - _0222ED22 - 2 ; case 3
	.short _0222ED6E - _0222ED22 - 2 ; case 4
	.short _0222ED5C - _0222ED22 - 2 ; case 5
	.short _0222ED4A - _0222ED22 - 2 ; case 6
	.short _0222ED32 - _0222ED22 - 2 ; case 7
_0222ED32:
	ldr r0, [r4]
	mov r1, #5
	ldr r0, [r0]
	mov r2, #2
	bl FUN_0202A578
	add r0, r4, #0
	mov r1, #0x25
	mov r2, #0x1a
	bl MOD82_0222DF6C
	b _0222EDB8
_0222ED4A:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222EDB8
_0222ED5C:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222EDB8
_0222ED6E:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222EDB8
_0222ED80:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222EDB8
_0222ED92:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222EDB8
_0222EDA4:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	bl FUN_020335E0
_0222EDB8:
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD82_0222ED00

	thumb_func_start MOD82_0222EDBC
MOD82_0222EDBC: ; 0x0222EDBC
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222EDF0 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	ldr r1, _0222EDF4 ; =0x00000B7C
	mov r2, #8
	ldr r1, [r4, r1]
	mov r3, #1
	bl MOD82_0222F59C
	add r0, r4, #0
	mov r1, #0x2d
	mov r2, #0x2b
	bl MOD82_0222DF6C
	add r0, r4, #0
	bl MOD82_0222F724
	ldr r0, [r4]
	mov r1, #0
	str r1, [r0, #0x20]
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_0222EDF0: .word 0x00000F0F
_0222EDF4: .word 0x00000B7C
	thumb_func_end MOD82_0222EDBC

	thumb_func_start MOD82_0222EDF8
MOD82_0222EDF8: ; 0x0222EDF8
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222EE20 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	ldr r1, _0222EE24 ; =0x00000B7C
	mov r2, #5
	ldr r1, [r4, r1]
	mov r3, #1
	bl MOD82_0222F59C
	add r0, r4, #0
	mov r1, #0x2d
	mov r2, #0x1c
	bl MOD82_0222DF6C
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_0222EE20: .word 0x00000F0F
_0222EE24: .word 0x00000B7C
	thumb_func_end MOD82_0222EDF8

	thumb_func_start MOD82_0222EE28
MOD82_0222EE28: ; 0x0222EE28
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	str r0, [r4, #0x3c]
	mov r0, #0xd9
	lsl r0, r0, #4
	add r0, r4, r0
	mov r1, #0
	mov r2, #0x1f
	mov r3, #0xa
	bl FUN_0200CCA4
	ldr r1, _0222EE70 ; =0x00000B94
	mov r0, #0xd9
	lsl r0, r0, #4
	ldr r1, [r4, r1]
	ldr r2, [r4, #0x3c]
	add r0, r4, r0
	mov r3, #2
	bl MOD82_0222F694
	mov r1, #1
	add r0, r4, #0
	add r2, r1, #0
	bl MOD82_0222F6D8
	mov r0, #0xd9
	lsl r0, r0, #4
	add r0, r4, r0
	bl FUN_020191D0
	mov r0, #0x1d
	str r0, [r4, #0x1c]
	mov r0, #3
	pop {r4, pc}
	nop
_0222EE70: .word 0x00000B94
	thumb_func_end MOD82_0222EE28

	thumb_func_start MOD82_0222EE74
MOD82_0222EE74: ; 0x0222EE74
	push {r4, lr}
	ldr r2, _0222EF18 ; =0x021C48B8
	mov r1, #0x40
	ldr r3, [r2, #0x4c]
	add r4, r0, #0
	tst r1, r3
	beq _0222EEAA
	ldr r0, [r4, #0x3c]
	add r0, r0, #1
	str r0, [r4, #0x3c]
	cmp r0, #0xa
	ble _0222EE90
	mov r0, #1
	str r0, [r4, #0x3c]
_0222EE90:
	ldr r1, _0222EF1C ; =0x00000B94
	mov r0, #0xd9
	lsl r0, r0, #4
	ldr r1, [r4, r1]
	ldr r2, [r4, #0x3c]
	add r0, r4, r0
	mov r3, #2
	bl MOD82_0222F694
	ldr r0, _0222EF20 ; =0x000005DC
	bl FUN_020054C8
	b _0222EF12
_0222EEAA:
	mov r1, #0x80
	tst r1, r3
	beq _0222EED8
	ldr r0, [r4, #0x3c]
	sub r0, r0, #1
	str r0, [r4, #0x3c]
	cmp r0, #1
	bge _0222EEBE
	mov r0, #0xa
	str r0, [r4, #0x3c]
_0222EEBE:
	ldr r1, _0222EF1C ; =0x00000B94
	mov r0, #0xd9
	lsl r0, r0, #4
	ldr r1, [r4, r1]
	ldr r2, [r4, #0x3c]
	add r0, r4, r0
	mov r3, #2
	bl MOD82_0222F694
	ldr r0, _0222EF20 ; =0x000005DC
	bl FUN_020054C8
	b _0222EF12
_0222EED8:
	ldr r2, [r2, #0x48]
	mov r1, #1
	tst r1, r2
	beq _0222EEFA
	mov r1, #0
	add r2, r1, #0
	bl MOD82_0222F6D8
	add r0, r4, #0
	mov r1, #9
	mov r2, #0x1e
	bl MOD82_0222DF6C
	ldr r0, _0222EF20 ; =0x000005DC
	bl FUN_020054C8
	b _0222EF12
_0222EEFA:
	mov r1, #2
	tst r1, r2
	beq _0222EF12
	mov r1, #0
	add r2, r1, #0
	bl MOD82_0222F6D8
	mov r0, #0x15
	str r0, [r4, #0x1c]
	ldr r0, _0222EF20 ; =0x000005DC
	bl FUN_020054C8
_0222EF12:
	mov r0, #3
	pop {r4, pc}
	nop
_0222EF18: .word 0x021C48B8
_0222EF1C: .word 0x00000B94
_0222EF20: .word 0x000005DC
	thumb_func_end MOD82_0222EE74

	thumb_func_start MOD82_0222EF24
MOD82_0222EF24: ; 0x0222EF24
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222EF4C ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	ldr r1, _0222EF50 ; =0x00000B7C
	mov r2, #6
	ldr r1, [r4, r1]
	mov r3, #1
	bl MOD82_0222F59C
	add r0, r4, #0
	mov r1, #0x2d
	mov r2, #0x1f
	bl MOD82_0222DF6C
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_0222EF4C: .word 0x00000F0F
_0222EF50: .word 0x00000B7C
	thumb_func_end MOD82_0222EF24

	thumb_func_start MOD82_0222EF54
MOD82_0222EF54: ; 0x0222EF54
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	str r0, [r4, #0x44]
	mov r0, #0xda
	lsl r0, r0, #4
	add r0, r4, r0
	mov r1, #0
	mov r2, #0x1f
	mov r3, #0xa
	bl FUN_0200CCA4
	mov r1, #0xb9
	mov r0, #0xda
	lsl r1, r1, #4
	lsl r0, r0, #4
	ldr r1, [r4, r1]
	ldr r2, [r4, #0x44]
	add r0, r4, r0
	mov r3, #3
	bl MOD82_0222F694
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	bl MOD82_0222F6D8
	mov r0, #0xda
	lsl r0, r0, #4
	add r0, r4, r0
	bl FUN_020191D0
	mov r0, #0x20
	str r0, [r4, #0x1c]
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD82_0222EF54

	thumb_func_start MOD82_0222EF9C
MOD82_0222EF9C: ; 0x0222EF9C
	push {r4, lr}
	ldr r2, _0222F040 ; =0x021C48B8
	mov r1, #0x40
	ldr r3, [r2, #0x4c]
	add r4, r0, #0
	tst r1, r3
	beq _0222EFD8
	ldr r0, [r4, #0x44]
	add r1, r0, #1
	str r1, [r4, #0x44]
	ldr r0, [r4, #0x40]
	add r0, r0, #1
	cmp r1, r0
	bne _0222EFBC
	mov r0, #1
	str r0, [r4, #0x44]
_0222EFBC:
	mov r1, #0xb9
	mov r0, #0xda
	lsl r1, r1, #4
	lsl r0, r0, #4
	ldr r1, [r4, r1]
	ldr r2, [r4, #0x44]
	add r0, r4, r0
	mov r3, #3
	bl MOD82_0222F694
	ldr r0, _0222F044 ; =0x000005DC
	bl FUN_020054C8
	b _0222F03C
_0222EFD8:
	mov r1, #0x80
	tst r1, r3
	beq _0222F008
	ldr r0, [r4, #0x44]
	sub r0, r0, #1
	str r0, [r4, #0x44]
	cmp r0, #1
	bge _0222EFEC
	ldr r0, [r4, #0x40]
	str r0, [r4, #0x44]
_0222EFEC:
	mov r1, #0xb9
	mov r0, #0xda
	lsl r1, r1, #4
	lsl r0, r0, #4
	ldr r1, [r4, r1]
	ldr r2, [r4, #0x44]
	add r0, r4, r0
	mov r3, #3
	bl MOD82_0222F694
	ldr r0, _0222F044 ; =0x000005DC
	bl FUN_020054C8
	b _0222F03C
_0222F008:
	ldr r2, [r2, #0x48]
	mov r1, #1
	tst r1, r2
	beq _0222F024
	mov r1, #0
	add r2, r1, #0
	bl MOD82_0222F6D8
	mov r0, #0x21
	str r0, [r4, #0x1c]
	ldr r0, _0222F044 ; =0x000005DC
	bl FUN_020054C8
	b _0222F03C
_0222F024:
	mov r1, #2
	tst r1, r2
	beq _0222F03C
	mov r1, #0
	add r2, r1, #0
	bl MOD82_0222F6D8
	mov r0, #0x1b
	str r0, [r4, #0x1c]
	ldr r0, _0222F044 ; =0x000005DC
	bl FUN_020054C8
_0222F03C:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_0222F040: .word 0x021C48B8
_0222F044: .word 0x000005DC
	thumb_func_end MOD82_0222EF9C

	thumb_func_start MOD82_0222F048
MOD82_0222F048: ; 0x0222F048
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _0222F09C ; =0x00000B78
	ldr r2, [r4, #0x44]
	ldr r0, [r4, r0]
	mov r1, #0
	mov r3, #3
	bl FUN_0200AD38
	mov r3, #2
	str r3, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r0, _0222F09C ; =0x00000B78
	ldr r2, [r4, #0x3c]
	ldr r0, [r4, r0]
	bl FUN_0200AD38
	ldr r0, _0222F0A0 ; =0x00000F0F
	mov r2, #1
	str r0, [sp]
	ldr r1, _0222F0A4 ; =0x00000B7C
	add r0, r4, #0
	ldr r1, [r4, r1]
	add r3, r2, #0
	bl MOD82_0222F4D8
	add r0, r4, #0
	mov r1, #0x2d
	mov r2, #0x22
	bl MOD82_0222DF6C
	mov r0, #0x22
	str r0, [r4, #0x1c]
	mov r0, #3
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_0222F09C: .word 0x00000B78
_0222F0A0: .word 0x00000F0F
_0222F0A4: .word 0x00000B7C
	thumb_func_end MOD82_0222F048

	thumb_func_start MOD82_0222F0A8
MOD82_0222F0A8: ; 0x0222F0A8
	push {r4, lr}
	add r4, r0, #0
	add r2, r4, #0
	ldr r0, [r4, #0x3c]
	ldr r1, [r4, #0x44]
	add r2, #0x48
	bl MOD82_0222D840
	mov r0, #0x23
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F700
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD82_0222F0A8

	thumb_func_start MOD82_0222F0C8
MOD82_0222F0C8: ; 0x0222F0C8
	push {r4, lr}
	add r4, r0, #0
	bl MOD82_0222D7C4
	cmp r0, #0
	beq _0222F18C
	bl MOD82_0222D7E4
	add r1, r0, #7
	cmp r1, #7
	bhi _0222F18C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222F0EA: ; jump table
	.short _0222F166 - _0222F0EA - 2 ; case 0
	.short _0222F154 - _0222F0EA - 2 ; case 1
	.short _0222F178 - _0222F0EA - 2 ; case 2
	.short _0222F166 - _0222F0EA - 2 ; case 3
	.short _0222F142 - _0222F0EA - 2 ; case 4
	.short _0222F130 - _0222F0EA - 2 ; case 5
	.short _0222F11E - _0222F0EA - 2 ; case 6
	.short _0222F0FA - _0222F0EA - 2 ; case 7
_0222F0FA:
	ldr r0, [r4]
	ldr r2, [r4, #0x3c]
	ldr r3, [r4, #0x44]
	ldr r1, _0222F190 ; =0x00000684
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r0, #4]
	add r1, r4, r1
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_0202A838
	add r0, r4, #0
	mov r1, #0x25
	mov r2, #0x24
	bl MOD82_0222DF6C
	b _0222F18C
_0222F11E:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222F18C
_0222F130:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222F18C
_0222F142:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #9
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222F18C
_0222F154:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222F18C
_0222F166:
	mov r1, #9
	str r1, [r4, #0x1c]
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD82_0222F724
	b _0222F18C
_0222F178:
	mov r1, #0x3b
	lsl r1, r1, #6
	str r0, [r4, r1]
	mov r0, #0x33
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
	bl FUN_020335E0
_0222F18C:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_0222F190: .word 0x00000684
	thumb_func_end MOD82_0222F0C8

	thumb_func_start MOD82_0222F194
MOD82_0222F194: ; 0x0222F194
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222F1C8 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	ldr r1, _0222F1CC ; =0x00000B7C
	mov r2, #3
	ldr r1, [r4, r1]
	mov r3, #1
	bl MOD82_0222F59C
	add r0, r4, #0
	mov r1, #0x2d
	mov r2, #0x2b
	bl MOD82_0222DF6C
	add r0, r4, #0
	bl MOD82_0222F724
	ldr r0, [r4]
	mov r1, #0
	str r1, [r0, #0x20]
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_0222F1C8: .word 0x00000F0F
_0222F1CC: .word 0x00000B7C
	thumb_func_end MOD82_0222F194

	thumb_func_start MOD82_0222F1D0
MOD82_0222F1D0: ; 0x0222F1D0
	mov r1, #0x27
	str r1, [r0, #0x1c]
	mov r0, #3
	bx lr
	thumb_func_end MOD82_0222F1D0

	thumb_func_start MOD82_0222F1D8
MOD82_0222F1D8: ; 0x0222F1D8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #2
	ldr r0, [r0, #0xc]
	bl FUN_02022840
	mov r0, #0x26
	str r0, [r4, #0x1c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD82_0222F1D8

	thumb_func_start MOD82_0222F1F0
MOD82_0222F1F0: ; 0x0222F1F0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	ldr r0, [r0, #0xc]
	bl FUN_02022854
	cmp r0, #2
	bne _0222F20A
	ldr r0, [r4, #0x20]
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD82_0222F724
_0222F20A:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD82_0222F1F0

	thumb_func_start MOD82_0222F210
MOD82_0222F210: ; 0x0222F210
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222F238 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	ldr r1, _0222F23C ; =0x00000B7C
	mov r2, #4
	ldr r1, [r4, r1]
	mov r3, #1
	bl MOD82_0222F59C
	add r0, r4, #0
	mov r1, #0x2e
	mov r2, #0x14
	bl MOD82_0222DF6C
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_0222F238: .word 0x00000F0F
_0222F23C: .word 0x00000B7C
	thumb_func_end MOD82_0222F210

	thumb_func_start MOD82_0222F240
MOD82_0222F240: ; 0x0222F240
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xeb
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0x44
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0222F26E
	sub r1, r1, #1
	cmp r0, r1
	bne _0222F264
	mov r0, #0xb
	str r0, [r4, #0x1c]
	b _0222F26E
_0222F264:
	mov r0, #0x27
	str r0, [r4, #0x1c]
	ldr r0, [r4]
	mov r1, #1
	str r1, [r0, #0x20]
_0222F26E:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD82_0222F240

	thumb_func_start MOD82_0222F274
MOD82_0222F274: ; 0x0222F274
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222F29C ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	ldr r1, _0222F2A0 ; =0x00000B7C
	mov r2, #9
	ldr r1, [r4, r1]
	mov r3, #1
	bl MOD82_0222F59C
	add r0, r4, #0
	mov r1, #0x2e
	mov r2, #0x16
	bl MOD82_0222DF6C
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_0222F29C: .word 0x00000F0F
_0222F2A0: .word 0x00000B7C
	thumb_func_end MOD82_0222F274

	thumb_func_start MOD82_0222F2A4
MOD82_0222F2A4: ; 0x0222F2A4
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xeb
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0x44
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0222F2D2
	sub r1, r1, #1
	cmp r0, r1
	bne _0222F2C8
	mov r0, #0x1b
	str r0, [r4, #0x1c]
	b _0222F2D2
_0222F2C8:
	mov r0, #0x27
	str r0, [r4, #0x1c]
	ldr r0, [r4]
	mov r1, #1
	str r1, [r0, #0x20]
_0222F2D2:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD82_0222F2A4

	thumb_func_start MOD82_0222F2D8
MOD82_0222F2D8: ; 0x0222F2D8
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222F300 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	ldr r1, _0222F304 ; =0x00000B84
	mov r2, #0x19
	ldr r1, [r4, r1]
	mov r3, #1
	bl MOD82_0222F59C
	add r0, r4, #0
	mov r1, #0x2d
	mov r2, #0x28
	bl MOD82_0222DF6C
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_0222F300: .word 0x00000F0F
_0222F304: .word 0x00000B84
	thumb_func_end MOD82_0222F2D8

	thumb_func_start MOD82_0222F308
MOD82_0222F308: ; 0x0222F308
	push {r4, lr}
	add r4, r0, #0
	bl MOD04_021DDBBC
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl MOD82_0222DFCC
	mov r0, #0x29
	str r0, [r4, #0x1c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD82_0222F308

	thumb_func_start MOD82_0222F324
MOD82_0222F324: ; 0x0222F324
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222F350 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	ldr r1, _0222F354 ; =0x00000B84
	mov r2, #0x1a
	ldr r1, [r4, r1]
	mov r3, #1
	bl MOD82_0222F59C
	add r0, r4, #0
	mov r1, #0x2f
	mov r2, #0x2c
	bl MOD82_0222DF6C
	ldr r0, _0222F358 ; =0x00000EC4
	mov r1, #0
	str r1, [r4, r0]
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0222F350: .word 0x00000F0F
_0222F354: .word 0x00000B84
_0222F358: .word 0x00000EC4
	thumb_func_end MOD82_0222F324

	thumb_func_start MOD82_0222F35C
MOD82_0222F35C: ; 0x0222F35C
	mov r0, #3
	bx lr
	thumb_func_end MOD82_0222F35C

	thumb_func_start MOD82_0222F360
MOD82_0222F360: ; 0x0222F360
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl FUN_02033ED0
	bl FUN_020332DC
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x44
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #0
	str r0, [r4, #0x1c]
	mov r0, #4
	add sp, #0xc
	pop {r3, r4, pc}
	thumb_func_end MOD82_0222F360

	thumb_func_start MOD82_0222F390
MOD82_0222F390: ; 0x0222F390
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xeb
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0x44
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0222F3B8
	sub r1, r1, #1
	cmp r0, r1
	bne _0222F3B4
	mov r0, #0
	str r0, [r4, #0x1c]
	b _0222F3B8
_0222F3B4:
	mov r0, #0x27
	str r0, [r4, #0x1c]
_0222F3B8:
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD82_0222F390

	thumb_func_start MOD82_0222F3BC
MOD82_0222F3BC: ; 0x0222F3BC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x3b
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r4, #0
	add r0, r0, #7
	cmp r0, #9
	bhi _0222F400
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222F3DA: ; jump table
	.short _0222F3FA - _0222F3DA - 2 ; case 0
	.short _0222F3EE - _0222F3DA - 2 ; case 1
	.short _0222F400 - _0222F3DA - 2 ; case 2
	.short _0222F3FA - _0222F3DA - 2 ; case 3
	.short _0222F3FE - _0222F3DA - 2 ; case 4
	.short _0222F3EE - _0222F3DA - 2 ; case 5
	.short _0222F3F6 - _0222F3DA - 2 ; case 6
	.short _0222F400 - _0222F3DA - 2 ; case 7
	.short _0222F3F2 - _0222F3DA - 2 ; case 8
	.short _0222F3F6 - _0222F3DA - 2 ; case 9
_0222F3EE:
	mov r4, #0xd
	b _0222F400
_0222F3F2:
	mov r4, #0xb
	b _0222F400
_0222F3F6:
	mov r4, #0xc
	b _0222F400
_0222F3FA:
	mov r4, #0xe
	b _0222F400
_0222F3FE:
	mov r4, #0xf
_0222F400:
	add r0, r5, #0
	bl MOD82_0222F724
	ldr r0, _0222F428 ; =0x00000F0F
	ldr r1, _0222F42C ; =0x00000B7C
	str r0, [sp]
	ldr r1, [r5, r1]
	add r0, r5, #0
	add r2, r4, #0
	mov r3, #1
	bl MOD82_0222F59C
	add r0, r5, #0
	mov r1, #0x2d
	mov r2, #0x34
	bl MOD82_0222DF6C
	mov r0, #3
	pop {r3, r4, r5, pc}
	nop
_0222F428: .word 0x00000F0F
_0222F42C: .word 0x00000B7C
	thumb_func_end MOD82_0222F3BC

	thumb_func_start MOD82_0222F430
MOD82_0222F430: ; 0x0222F430
	push {r4, lr}
	add r4, r0, #0
	bl FUN_020332DC
	bl MOD04_021DDBBC
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl MOD82_0222DFCC
	mov r0, #0x2c
	str r0, [r4, #0x1c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD82_0222F430

	thumb_func_start MOD82_0222F450
MOD82_0222F450: ; 0x0222F450
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222F46C ; =0x00000B9C
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0222F468
	ldr r0, [r4, #0x20]
	str r0, [r4, #0x1c]
_0222F468:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_0222F46C: .word 0x00000B9C
	thumb_func_end MOD82_0222F450

	thumb_func_start MOD82_0222F470
MOD82_0222F470: ; 0x0222F470
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222F49C ; =0x00000B9C
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0222F498
	ldr r0, _0222F4A0 ; =0x00000EC4
	ldr r0, [r4, r0]
	cmp r0, #0x1e
	ble _0222F490
	ldr r0, [r4, #0x20]
	str r0, [r4, #0x1c]
_0222F490:
	ldr r0, _0222F4A0 ; =0x00000EC4
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
_0222F498:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_0222F49C: .word 0x00000B9C
_0222F4A0: .word 0x00000EC4
	thumb_func_end MOD82_0222F470

	thumb_func_start MOD82_0222F4A4
MOD82_0222F4A4: ; 0x0222F4A4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222F4D4 ; =0x00000B9C
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0222F4CE
	mov r2, #0x91
	ldr r0, [r4, #4]
	mov r1, #0xd
	lsl r2, r2, #2
	bl MOD82_0222DF38
	mov r1, #0xeb
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r0, [r4, #0x20]
	str r0, [r4, #0x1c]
_0222F4CE:
	mov r0, #3
	pop {r4, pc}
	nop
_0222F4D4: .word 0x00000B9C
	thumb_func_end MOD82_0222F4A4

	thumb_func_start MOD82_0222F4D8
MOD82_0222F4D8: ; 0x0222F4D8
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r0, r1, #0
	add r1, r2, #0
	add r4, r3, #0
	bl FUN_0200A914
	add r6, r0, #0
	ldr r1, _0222F53C ; =0x00000B78
	add r2, r6, #0
	ldr r0, [r5, r1]
	add r1, #0x10
	ldr r1, [r5, r1]
	bl FUN_0200B7B8
	mov r0, #0x36
	lsl r0, r0, #6
	add r0, r5, r0
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0x36
	lsl r0, r0, #6
	add r0, r5, r0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200D0BC
	mov r3, #0
	str r3, [sp]
	str r4, [sp, #4]
	mov r0, #0x36
	lsl r0, r0, #6
	ldr r2, _0222F540 ; =0x00000B88
	str r3, [sp, #8]
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	bl FUN_0201BD84
	ldr r1, _0222F544 ; =0x00000B9C
	str r0, [r5, r1]
	add r0, r6, #0
	bl FUN_02021A20
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_0222F53C: .word 0x00000B78
_0222F540: .word 0x00000B88
_0222F544: .word 0x00000B9C
	thumb_func_end MOD82_0222F4D8

	thumb_func_start MOD82_0222F548
MOD82_0222F548: ; 0x0222F548
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222F56C ; =0x00000EBC
	ldr r0, [r4, r0]
	neg r0, r0
	bl MOD04_021D80E0
	ldr r2, _0222F56C ; =0x00000EBC
	add r1, r0, #0
	ldr r2, [r4, r2]
	add r0, r4, #0
	neg r2, r2
	bl MOD82_0222F7C0
	mov r0, #0x36
	str r0, [r4, #0x1c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_0222F56C: .word 0x00000EBC
	thumb_func_end MOD82_0222F548

	thumb_func_start MOD82_0222F570
MOD82_0222F570: ; 0x0222F570
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222F598 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	bne _0222F584
	mov r0, #2
	tst r0, r1
	beq _0222F594
_0222F584:
	mov r0, #0x37
	lsl r0, r0, #6
	add r0, r4, r0
	mov r1, #0
	bl FUN_0200CCF8
	mov r0, #0
	str r0, [r4, #0x1c]
_0222F594:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_0222F598: .word 0x021C48B8
	thumb_func_end MOD82_0222F570

	thumb_func_start MOD82_0222F59C
MOD82_0222F59C: ; 0x0222F59C
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r0, r1, #0
	add r1, r2, #0
	ldr r2, _0222F5EC ; =0x00000B88
	add r4, r3, #0
	ldr r2, [r5, r2]
	bl FUN_0200A8E0
	mov r0, #0x36
	lsl r0, r0, #6
	add r0, r5, r0
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0x36
	lsl r0, r0, #6
	add r0, r5, r0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200D0BC
	mov r3, #0
	str r3, [sp]
	str r4, [sp, #4]
	mov r0, #0x36
	lsl r0, r0, #6
	ldr r2, _0222F5EC ; =0x00000B88
	str r3, [sp, #8]
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	bl FUN_0201BD84
	ldr r1, _0222F5F0 ; =0x00000B9C
	str r0, [r5, r1]
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_0222F5EC: .word 0x00000B88
_0222F5F0: .word 0x00000B9C
	thumb_func_end MOD82_0222F59C

	thumb_func_start MOD82_0222F5F4
MOD82_0222F5F4: ; 0x0222F5F4
	push {r4, lr}
	add r4, r0, #0
	cmp r3, #1
	beq _0222F602
	cmp r3, #2
	beq _0222F618
	b _0222F626
_0222F602:
	ldr r0, [sp, #0xc]
	mov r2, #0
	bl FUN_02002E14
	ldrb r1, [r4, #7]
	lsl r1, r1, #3
	sub r1, r1, r0
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r2, r0, #1
	b _0222F626
_0222F618:
	ldr r0, [sp, #0xc]
	mov r2, #0
	bl FUN_02002E14
	ldrb r1, [r4, #7]
	lsl r1, r1, #3
	sub r2, r1, r0
_0222F626:
	add r0, r2, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD82_0222F5F4

	thumb_func_start MOD82_0222F62C
MOD82_0222F62C: ; 0x0222F62C
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r3, #0
	ldr r3, [sp, #0x24]
	add r5, r0, #0
	str r3, [sp]
	mov r3, #1
	str r3, [sp, #4]
	ldr r3, [sp, #0x20]
	add r6, r1, #0
	bl MOD82_0222F5F4
	add r3, r0, #0
	str r4, [sp]
	mov r1, #0
	ldr r0, [sp, #0x24]
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r5, #0
	mov r1, #1
	add r2, r6, #0
	bl FUN_0201BDE0
	add sp, #0x10
	pop {r4, r5, r6, pc}
	thumb_func_end MOD82_0222F62C

	thumb_func_start MOD82_0222F660
MOD82_0222F660: ; 0x0222F660
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r3, #0
	ldr r3, [sp, #0x24]
	add r5, r0, #0
	str r3, [sp]
	mov r3, #0
	str r3, [sp, #4]
	ldr r3, [sp, #0x20]
	add r6, r1, #0
	bl MOD82_0222F5F4
	add r3, r0, #0
	str r4, [sp]
	mov r1, #0
	ldr r0, [sp, #0x24]
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, #0
	add r2, r6, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD82_0222F660

	thumb_func_start MOD82_0222F694
MOD82_0222F694: ; 0x0222F694
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	mov r1, #0xf
	add r5, r0, #0
	add r6, r2, #0
	add r7, r3, #0
	bl FUN_02019620
	mov r0, #1
	str r0, [sp]
	add r0, r4, #0
	add r1, r6, #0
	add r2, r7, #0
	mov r3, #2
	bl FUN_02021B04
	mov r3, #1
	ldr r0, _0222F6CC ; =0x00010200
	str r3, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0
	bl MOD82_0222F660
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222F6CC: .word 0x00010200
	thumb_func_end MOD82_0222F694

	thumb_func_start MOD82_0222F6D0
MOD82_0222F6D0: ; 0x0222F6D0
	ldr r3, _0222F6D4 ; =FUN_02033E74
	bx r3
	.align 2, 0
_0222F6D4: .word FUN_02033E74
	thumb_func_end MOD82_0222F6D0

	thumb_func_start MOD82_0222F6D8
MOD82_0222F6D8: ; 0x0222F6D8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r2, #0
	cmp r1, #1
	bhi _0222F6F6
	ldr r0, _0222F6F8 ; =0x00000D78
	add r1, r4, #0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r0, _0222F6FC ; =0x00000D7C
	add r1, r4, #0
	ldr r0, [r5, r0]
	bl FUN_020200A0
_0222F6F6:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222F6F8: .word 0x00000D78
_0222F6FC: .word 0x00000D7C
	thumb_func_end MOD82_0222F6D8

	thumb_func_start MOD82_0222F700
MOD82_0222F700: ; 0x0222F700
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222F720 ; =0x00000EB4
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0222F71C
	mov r0, #0x36
	lsl r0, r0, #6
	add r0, r4, r0
	mov r1, #1
	bl FUN_0200D858
	ldr r1, _0222F720 ; =0x00000EB4
	str r0, [r4, r1]
_0222F71C:
	pop {r4, pc}
	nop
_0222F720: .word 0x00000EB4
	thumb_func_end MOD82_0222F700

	thumb_func_start MOD82_0222F724
MOD82_0222F724: ; 0x0222F724
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222F73C ; =0x00000EB4
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0222F73A
	bl FUN_0200DBFC
	ldr r0, _0222F73C ; =0x00000EB4
	mov r1, #0
	str r1, [r4, r0]
_0222F73A:
	pop {r4, pc}
	.align 2, 0
_0222F73C: .word 0x00000EB4
	thumb_func_end MOD82_0222F724

	thumb_func_start MOD82_0222F740
MOD82_0222F740: ; 0x0222F740
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #1
	add r6, r1, #0
	lsl r0, r0, #8
	mov r1, #0x44
	bl FUN_020219F4
	add r4, r0, #0
	ldr r0, _0222F7B0 ; =0x00000B84
	add r1, r6, #0
	ldr r0, [r5, r0]
	add r2, r4, #0
	bl FUN_0200A8E0
	ldr r1, _0222F7B4 ; =0x00000B78
	add r2, r4, #0
	ldr r0, [r5, r1]
	add r1, #0x20
	ldr r1, [r5, r1]
	bl FUN_0200B7B8
	mov r0, #0x37
	lsl r0, r0, #6
	add r0, r5, r0
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0x37
	lsl r0, r0, #6
	add r0, r5, r0
	mov r1, #1
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_0200CCA4
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	mov r0, #0x37
	lsl r0, r0, #6
	ldr r2, _0222F7B8 ; =0x00000B98
	str r3, [sp, #8]
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	bl FUN_0201BD84
	ldr r1, _0222F7BC ; =0x00000B9C
	str r0, [r5, r1]
	add r0, r4, #0
	bl FUN_02021A20
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0222F7B0: .word 0x00000B84
_0222F7B4: .word 0x00000B78
_0222F7B8: .word 0x00000B98
_0222F7BC: .word 0x00000B9C
	thumb_func_end MOD82_0222F740

	thumb_func_start MOD82_0222F7C0
MOD82_0222F7C0: ; 0x0222F7C0
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0
	add r4, r1, #0
	mvn r0, r0
	cmp r4, r0
	bne _0222F7D2
	mov r4, #0xb
_0222F7D2:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _0222F800 ; =0x00000B78
	mov r1, #0
	ldr r0, [r5, r0]
	mov r3, #5
	bl FUN_0200AD38
	mov r0, #0x36
	lsl r0, r0, #6
	add r0, r5, r0
	mov r1, #1
	bl FUN_0200D0E0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD82_0222F740
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_0222F800: .word 0x00000B78
	thumb_func_end MOD82_0222F7C0

	.section .rodata
	; 0x0222F804
	.byte 0x00, 0x17, 0x0D, 0x07, 0x04, 0x0D, 0x00, 0x00, 0xE0, 0x00, 0x6F, 0x00, 0xE0, 0x00, 0x81, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1B, 0x02, 0x00, 0x02, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1E, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1E, 0x04
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.section .data
	; 0x0222F8E0
	.byte 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x67, 0x61, 0x6D, 0x65, 0x73, 0x74, 0x61, 0x74, 0x73
	.byte 0x32, 0x2E, 0x67, 0x73, 0x2E, 0x6E, 0x69, 0x6E, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x77, 0x69, 0x66
	.byte 0x69, 0x2E, 0x6E, 0x65, 0x74, 0x2F, 0x70, 0x6F, 0x6B, 0x65, 0x6D, 0x6F, 0x6E, 0x64, 0x70, 0x64
	.byte 0x73, 0x2F, 0x62, 0x61, 0x74, 0x74, 0x6C, 0x65, 0x74, 0x6F, 0x77, 0x65, 0x72, 0x2F, 0x72, 0x6F
	.byte 0x6F, 0x6D, 0x6E, 0x75, 0x6D, 0x2E, 0x61, 0x73, 0x70, 0x00, 0x00, 0x00, 0x68, 0x74, 0x74, 0x70
	.byte 0x3A, 0x2F, 0x2F, 0x67, 0x61, 0x6D, 0x65, 0x73, 0x74, 0x61, 0x74, 0x73, 0x32, 0x2E, 0x67, 0x73
	.byte 0x2E, 0x6E, 0x69, 0x6E, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x77, 0x69, 0x66, 0x69, 0x2E, 0x6E, 0x65
	.byte 0x74, 0x2F, 0x70, 0x6F, 0x6B, 0x65, 0x6D, 0x6F, 0x6E, 0x64, 0x70, 0x64, 0x73, 0x2F, 0x62, 0x61
	.byte 0x74, 0x74, 0x6C, 0x65, 0x74, 0x6F, 0x77, 0x65, 0x72, 0x2F, 0x64, 0x6F, 0x77, 0x6E, 0x6C, 0x6F
	.byte 0x61, 0x64, 0x2E, 0x61, 0x73, 0x70, 0x00, 0x00, 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x67
	.byte 0x61, 0x6D, 0x65, 0x73, 0x74, 0x61, 0x74, 0x73, 0x32, 0x2E, 0x67, 0x73, 0x2E, 0x6E, 0x69, 0x6E
	.byte 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x77, 0x69, 0x66, 0x69, 0x2E, 0x6E, 0x65, 0x74, 0x2F, 0x70, 0x6F
	.byte 0x6B, 0x65, 0x6D, 0x6F, 0x6E, 0x64, 0x70, 0x64, 0x73, 0x2F, 0x62, 0x61, 0x74, 0x74, 0x6C, 0x65
	.byte 0x74, 0x6F, 0x77, 0x65, 0x72, 0x2F, 0x75, 0x70, 0x6C, 0x6F, 0x61, 0x64, 0x2E, 0x61, 0x73, 0x70
	.byte 0x00, 0x00, 0x00, 0x00, 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x67, 0x61, 0x6D, 0x65, 0x73
	.byte 0x74, 0x61, 0x74, 0x73, 0x32, 0x2E, 0x67, 0x73, 0x2E, 0x6E, 0x69, 0x6E, 0x74, 0x65, 0x6E, 0x64
	.byte 0x6F, 0x77, 0x69, 0x66, 0x69, 0x2E, 0x6E, 0x65, 0x74, 0x2F, 0x70, 0x6F, 0x6B, 0x65, 0x6D, 0x6F
	.byte 0x6E, 0x64, 0x70, 0x64, 0x73, 0x2F, 0x62, 0x61, 0x74, 0x74, 0x6C, 0x65, 0x74, 0x6F, 0x77, 0x65
	.byte 0x72, 0x2F, 0x69, 0x6E, 0x66, 0x6F, 0x2E, 0x61, 0x73, 0x70, 0x00, 0x00, 0x51, 0xE0, 0x22, 0x02
	.byte 0x19, 0xE1, 0x22, 0x02, 0x39, 0xE1, 0x22, 0x02, 0x45, 0xE5, 0x22, 0x02, 0x75, 0xE5, 0x22, 0x02
	.byte 0x5D, 0xE6, 0x22, 0x02, 0x7D, 0xE6, 0x22, 0x02, 0xF5, 0xE6, 0x22, 0x02, 0x09, 0xE7, 0x22, 0x02
	.byte 0xA9, 0xE7, 0x22, 0x02, 0xE9, 0xE7, 0x22, 0x02, 0xF9, 0xE7, 0x22, 0x02, 0xB1, 0xE8, 0x22, 0x02
	.byte 0xC9, 0xE8, 0x22, 0x02, 0x59, 0xE9, 0x22, 0x02, 0x89, 0xE9, 0x22, 0x02, 0xCD, 0xE9, 0x22, 0x02
	.byte 0xA5, 0xEA, 0x22, 0x02, 0x41, 0xEB, 0x22, 0x02, 0x61, 0xEB, 0x22, 0x02, 0x4D, 0xEC, 0x22, 0x02
	.byte 0x11, 0xEB, 0x22, 0x02, 0x11, 0xF2, 0x22, 0x02, 0x41, 0xF2, 0x22, 0x02, 0x75, 0xF2, 0x22, 0x02
	.byte 0xA5, 0xF2, 0x22, 0x02, 0x89, 0xEC, 0x22, 0x02, 0xBD, 0xEC, 0x22, 0x02, 0x01, 0xED, 0x22, 0x02
	.byte 0xBD, 0xED, 0x22, 0x02, 0xF9, 0xED, 0x22, 0x02, 0x29, 0xEE, 0x22, 0x02, 0x75, 0xEE, 0x22, 0x02
	.byte 0x25, 0xEF, 0x22, 0x02, 0x55, 0xEF, 0x22, 0x02, 0x9D, 0xEF, 0x22, 0x02, 0x49, 0xF0, 0x22, 0x02
	.byte 0xA9, 0xF0, 0x22, 0x02, 0xC9, 0xF0, 0x22, 0x02, 0x95, 0xF1, 0x22, 0x02, 0xD9, 0xF1, 0x22, 0x02
	.byte 0xF1, 0xF1, 0x22, 0x02, 0xD9, 0xF2, 0x22, 0x02, 0x09, 0xF3, 0x22, 0x02, 0x25, 0xF3, 0x22, 0x02
	.byte 0x5D, 0xF3, 0x22, 0x02, 0xD1, 0xF1, 0x22, 0x02, 0x61, 0xF3, 0x22, 0x02, 0x51, 0xF4, 0x22, 0x02
	.byte 0xA5, 0xF4, 0x22, 0x02, 0x71, 0xF4, 0x22, 0x02, 0x91, 0xF3, 0x22, 0x02, 0xD9, 0xE5, 0x22, 0x02
	.byte 0x05, 0xE6, 0x22, 0x02, 0xBD, 0xF3, 0x22, 0x02, 0x31, 0xF4, 0x22, 0x02, 0x49, 0xF5, 0x22, 0x02
	.byte 0x71, 0xF5, 0x22, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.section .bss
	; 0x0222FB00
	.space 0x120
