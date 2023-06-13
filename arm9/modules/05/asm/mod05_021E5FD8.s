	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021E5FD8
MOD05_021E5FD8: ; 0x021E5FD8
	ldr r3, _021E5FDC ; =FUN_020553D4
	bx r3
	.balign 4, 0
_021E5FDC: .word FUN_020553D4

	thumb_func_start MOD05_021E5FE0
MOD05_021E5FE0: ; 0x021E5FE0
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r6, #0
	bl FUN_020553E0
	ldr r5, _021E6010 ; =UNK05_021F7734
	add r4, r0, #0
_021E5FEE:
	mov r0, #1
	tst r0, r4
	beq _021E5FFA
	ldr r1, [r5]
	add r0, r7, #0
	blx r1
_021E5FFA:
	add r6, r6, #1
	lsr r4, r4, #1
	add r5, r5, #4
	cmp r6, #9
	blo _021E5FEE
	add r0, r7, #0
	mov r1, #0
	bl FUN_020553DC
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E6010: .word UNK05_021F7734

	thumb_func_start MOD05_021E6014
MOD05_021E6014: ; 0x021E6014
	push {r4, lr}
	add r4, r0, #0
	bl PlayerAvatar_GetGender
	add r1, r0, #0
	mov r0, #0
	bl FUN_020555A0
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021E726C
	add r0, r4, #0
	mov r1, #0
	bl FUN_020553A8
	add r0, r4, #0
	bl FUN_02055410
	add r0, r4, #0
	bl FUN_02055454
	cmp r0, #0
	beq _021E6048
	bl MOD05_021E4DE4
_021E6048:
	add r0, r4, #0
	mov r1, #0
	bl FUN_02055450
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E6054
MOD05_021E6054: ; 0x021E6054
	push {r4, lr}
	add r4, r0, #0
	bl PlayerAvatar_GetGender
	add r1, r0, #0
	mov r0, #1
	bl FUN_020555A0
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021E726C
	add r0, r4, #0
	mov r1, #1
	bl FUN_020553A8
	add r0, r4, #0
	bl FUN_02055410
	add r0, r4, #0
	bl FUN_02055454
	cmp r0, #0
	beq _021E6088
	bl MOD05_021E4DE4
_021E6088:
	add r0, r4, #0
	mov r1, #0
	bl FUN_02055450
	ldr r0, _021E6098 ; =0x00000618
	bl PlaySE
	pop {r4, pc}
	.balign 4, 0
_021E6098: .word 0x00000618

	thumb_func_start MOD05_021E609C
MOD05_021E609C: ; 0x021E609C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	bl PlayerAvatar_GetGender
	add r1, r0, #0
	mov r0, #2
	bl FUN_020555A0
	add r1, r0, #0
	add r0, r5, #0
	bl MOD05_021E726C
	add r0, r5, #0
	mov r1, #2
	bl FUN_020553A8
	add r0, r5, #0
	bl FUN_02055410
	add r0, r5, #0
	bl FUN_02055454
	cmp r0, #0
	beq _021E60D2
	bl MOD05_021E4DE4
_021E60D2:
	add r0, r5, #0
	mov r1, #0
	bl FUN_02055450
	add r0, r5, #0
	bl PlayerAvatar_GetFacingDirection
	add r4, r0, #0
	add r0, r5, #0
	bl FUN_020553A0
	add r6, r0, #0
	bl FUN_02058738
	mov r0, #1
	mov r1, #0
	str r0, [sp]
	add r0, r6, #0
	add r2, r1, #0
	add r3, r4, #0
	bl MOD06_0224ABAC
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_02055450
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E610C
MOD05_021E610C: ; 0x021E610C
	ldr r3, _021E6114 ; =FUN_020556C8
	mov r1, #1
	bx r3
	nop
_021E6114: .word FUN_020556C8

	thumb_func_start MOD05_021E6118
MOD05_021E6118: ; 0x021E6118
	push {r4, lr}
	add r4, r0, #0
	bl PlayerAvatar_GetGender
	add r1, r0, #0
	mov r0, #4
	bl FUN_020555A0
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021E726C
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E6134
MOD05_021E6134: ; 0x021E6134
	push {r4, lr}
	add r4, r0, #0
	bl PlayerAvatar_GetGender
	add r1, r0, #0
	mov r0, #6
	bl FUN_020555A0
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021E726C
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E6150
MOD05_021E6150: ; 0x021E6150
	push {r4, lr}
	add r4, r0, #0
	bl PlayerAvatar_GetGender
	add r1, r0, #0
	mov r0, #7
	bl FUN_020555A0
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021E726C
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E616C
MOD05_021E616C: ; 0x021E616C
	push {r4, lr}
	add r4, r0, #0
	bl PlayerAvatar_GetGender
	add r1, r0, #0
	mov r0, #8
	bl FUN_020555A0
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021E726C
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E6188
MOD05_021E6188: ; 0x021E6188
	push {r4, lr}
	add r4, r0, #0
	bl PlayerAvatar_GetGender
	add r1, r0, #0
	mov r0, #9
	bl FUN_020555A0
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021E726C
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E61A4
MOD05_021E61A4: ; 0x021E61A4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	add r4, r2, #0
	add r7, r3, #0
	bl FUN_020556B4
	cmp r0, #1
	bne _021E61CE
	add r0, r6, #0
	add r1, r5, #0
	add r2, r7, #0
	bl MOD05_021E68D8
	cmp r0, #1
	bne _021E61CA
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E61CA:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021E61CE:
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02055898
	cmp r0, #0
	bne _021E61DE
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021E61DE:
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _021E61FE
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	add r3, r7, #0
	bl MOD05_021E628C
	cmp r0, #1
	bne _021E61FA
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E61FA:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021E61FE:
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	add r3, r7, #0
	bl MOD05_021E6218
	cmp r0, #1
	bne _021E6212
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E6212:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E6218
MOD05_021E6218: ; 0x021E6218
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r4, r2, #0
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r7, r3, #0
	bl FUN_0205714C
	str r0, [sp]
	mov r0, #1
	tst r0, r7
	beq _021E6246
	ldr r3, [sp]
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl MOD05_021E62B4
	cmp r0, #1
	bne _021E6246
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E6246:
	mov r0, #2
	tst r0, r7
	beq _021E6260
	ldr r3, [sp]
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl MOD05_021E6714
	cmp r0, #1
	bne _021E6260
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E6260:
	ldr r3, [sp]
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl MOD05_021E65EC
	cmp r0, #1
	bne _021E6274
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E6274:
	ldr r3, [sp]
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl MOD05_021E6758
	cmp r0, #1
	bne _021E6288
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E6288:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021E628C
MOD05_021E628C: ; 0x021E628C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r2, #0
	add r5, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	bl FUN_0205714C
	add r3, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD05_021E6758
	cmp r0, #1
	bne _021E62B0
	mov r0, #1
	pop {r4, r5, r6, pc}
_021E62B0:
	mov r0, #0
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021E62B4
MOD05_021E62B4: ; 0x021E62B4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	add r4, r2, #0
	cmp r3, #1
	beq _021E62C4
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021E62C4:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021E727C
	add r6, r0, #0
	bne _021E62D4
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021E62D4:
	bl FUN_02058458
	cmp r0, #0x54
	beq _021E62E0
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021E62E0:
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_02059918
	mov r1, #1
	bic r0, r1
	beq _021E62F2
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021E62F2:
	add r0, r4, #0
	add r1, r7, #0
	add r2, r5, #0
	add r3, r6, #0
	bl MOD05_021E6304
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E6304
MOD05_021E6304: ; 0x021E6304
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0x14
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl MOD05_021E72B8
	add r2, r0, #0
	str r5, [r2, #4]
	str r4, [r2, #8]
	str r7, [r2, #0x10]
	ldr r1, _021E6328 ; =MOD05_021E632C
	add r0, r4, #0
	str r6, [r2, #0xc]
	bl FUN_020463CC
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E6328: .word MOD05_021E632C

	thumb_func_start MOD05_021E632C
MOD05_021E632C: ; 0x021E632C
	push {r4, r5, r6, lr}
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl FUN_020553A0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0x10]
	cmp r0, #0
	beq _021E634E
	cmp r0, #1
	beq _021E639A
	cmp r0, #2
	beq _021E63C0
	b _021E63CA
_021E634E:
	add r0, r5, #0
	bl FUN_0205AD98
	cmp r0, #0
	beq _021E63CA
	add r0, r6, #0
	bl FUN_0205AD98
	cmp r0, #0
	bne _021E636C
	ldr r0, [r4, #0xc]
	bl FUN_020570C4
	cmp r0, #0
	beq _021E63CA
_021E636C:
	ldr r0, [r4, #4]
	mov r1, #8
	bl FUN_0205AFDC
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_0205ADDC
	ldr r0, [r4, #4]
	mov r1, #0x20
	bl FUN_0205AFDC
	add r1, r0, #0
	add r0, r6, #0
	bl FUN_0205ADDC
	ldr r0, _021E63D0 ; =0x00000627
	bl PlaySE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E63CA
_021E639A:
	add r0, r5, #0
	bl FUN_0205AE28
	cmp r0, #0
	beq _021E63CA
	add r0, r6, #0
	bl FUN_0205AE28
	cmp r0, #0
	beq _021E63CA
	add r0, r5, #0
	bl FUN_0205AE50
	add r0, r6, #0
	bl FUN_0205AE50
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021E63C0:
	add r0, r4, #0
	bl MOD05_021E72DC
	mov r0, #1
	pop {r4, r5, r6, pc}
_021E63CA:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_021E63D0: .word 0x00000627

	thumb_func_start MOD05_021E63D4
MOD05_021E63D4: ; 0x021E63D4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0x2c
	add r7, r1, #0
	add r5, r2, #0
	bl MOD05_021E72B8
	add r4, r0, #0
	str r7, [r4, #4]
	str r6, [r4, #0x1c]
	ldr r0, [r6, #0x38]
	str r0, [r4, #0x20]
	bl FUN_020553A0
	add r2, r4, #0
	str r0, [r4, #0x24]
	add r2, #0xc
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r6, #0x10]
	ldr r1, _021E640C ; =MOD05_021E6484
	add r2, r4, #0
	bl FUN_0204640C
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E640C: .word MOD05_021E6484

	thumb_func_start CallFieldTask_Surf
CallFieldTask_Surf: ; 0x021E6410
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r6, r2, #0
	add r5, r1, #0
	bl FUN_02046528
	add r4, r0, #0
	add r1, r6, #0
	bl MOD05_021E72E8
	add r1, r0, #0
	add r0, r4, #0
	add r2, sp, #0
	bl MOD05_021E7228
	add r0, r4, #0
	add r1, r5, #0
	add r2, sp, #0
	bl MOD05_021E63D4
	add sp, #0x10
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021E643C
MOD05_021E643C: ; 0x021E643C
	push {r4, r5, r6, lr}
	add r4, r2, #0
	add r5, r1, #0
	bl FUN_020553A0
	add r6, r0, #0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	bl FUN_0205481C
	cmp r0, #1
	bne _021E647E
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	bl FUN_02054B78
	cmp r0, #1
	beq _021E646C
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	bl FUN_02054B6C
	cmp r0, #1
	bne _021E647A
_021E646C:
	add r0, r6, #0
	bl FUN_02058A68
	cmp r0, #1
	bne _021E647A
	mov r0, #0
	pop {r4, r5, r6, pc}
_021E647A:
	mov r0, #1
	pop {r4, r5, r6, pc}
_021E647E:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E6484
MOD05_021E6484: ; 0x021E6484
	push {r3, r4, r5, r6, r7, lr}
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #7
	bhi _021E64D4
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E649E: ; jump table
	.short _021E64AE - _021E649E - 2 ; case 0
	.short _021E64CA - _021E649E - 2 ; case 1
	.short _021E64E2 - _021E649E - 2 ; case 2
	.short _021E6500 - _021E649E - 2 ; case 3
	.short _021E6514 - _021E649E - 2 ; case 4
	.short _021E655E - _021E649E - 2 ; case 5
	.short _021E658A - _021E649E - 2 ; case 6
	.short _021E65AC - _021E649E - 2 ; case 7
_021E64AE:
	ldr r0, [r4, #0x1c]
	mov r1, #0
	bl FUN_0204AB20
	ldr r0, [r4, #0x1c]
	ldr r1, _021E65E8 ; =0x0000047F
	mov r2, #1
	bl FUN_0204ABDC
	ldr r0, [r4]
	add r0, r0, #1
	add r0, r0, #1
	str r0, [r4]
	b _021E65E4
_021E64CA:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0xa
	bgt _021E64D6
_021E64D4:
	b _021E65E4
_021E64D6:
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E65E4
_021E64E2:
	ldr r0, [r4, #0xc]
	cmp r0, #1
	bne _021E64FA
	add r1, r4, #0
	ldr r0, [r4, #0x1c]
	add r1, #0xc
	bl MOD05_021E723C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E65E4
_021E64FA:
	mov r0, #4
	str r0, [r4]
	b _021E65E4
_021E6500:
	add r0, r4, #0
	add r0, #0xc
	bl MOD05_021E7250
	cmp r0, #1
	bne _021E65E4
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E65E4
_021E6514:
	ldr r0, [r4, #0x20]
	bl GetPlayerXCoord
	add r5, r0, #0
	ldr r0, [r4, #4]
	bl FUN_02059BF4
	add r6, r0, #0
	ldr r0, [r4, #0x20]
	bl GetPlayerYCoord
	add r7, r0, #0
	ldr r0, [r4, #4]
	bl FUN_02059C00
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, [r4, #0x24]
	ldr r3, [r4, #4]
	add r1, r5, r6
	add r2, r7, r2
	bl MOD06_0224ABAC
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0x28]
	bl FUN_02055450
	ldr r0, [r4, #0x20]
	mov r1, #2
	bl FUN_020553A8
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E65E4
_021E655E:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0xa
	ble _021E65E4
	ldr r0, [r4, #0x20]
	bl PlayerAvatar_GetGender
	add r1, r0, #0
	mov r0, #0
	bl FUN_020555A0
	add r1, r0, #0
	ldr r0, [r4, #0x20]
	bl MOD05_021E726C
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E65E4
_021E658A:
	ldr r0, [r4, #0x24]
	bl FUN_0205AD98
	cmp r0, #1
	bne _021E65E4
	ldr r0, [r4, #4]
	mov r1, #0x34
	bl FUN_0205AFDC
	add r1, r0, #0
	ldr r0, [r4, #0x24]
	bl FUN_0205ADDC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E65E4
_021E65AC:
	ldr r0, [r4, #0x24]
	bl FUN_0205AE28
	cmp r0, #0
	beq _021E65E4
	ldr r0, [r4, #0x24]
	bl FUN_0205AE50
	ldr r0, [r4, #0x28]
	mov r1, #1
	bl MOD06_0224ADF8
	ldr r0, [r4, #0x20]
	bl PlayerAvatar_GetGender
	add r1, r0, #0
	mov r0, #2
	bl FUN_020555A0
	add r1, r0, #0
	ldr r0, [r4, #0x20]
	bl MOD05_021E726C
	add r0, r4, #0
	bl MOD05_021E72DC
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E65E4:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E65E8: .word 0x0000047F

	thumb_func_start MOD05_021E65EC
MOD05_021E65EC: ; 0x021E65EC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	add r4, r2, #0
	cmp r3, #1
	bne _021E6602
	add r0, r5, #0
	bl PlayerAvatar_GetState
	cmp r0, #2
	beq _021E6606
_021E6602:
	mov r0, #0
	pop {r4, r5, r6, pc}
_021E6606:
	add r0, r5, #0
	bl FUN_020553A0
	add r1, r0, #0
	add r0, r5, #0
	add r2, r4, #0
	bl FUN_02056B74
	cmp r0, #0x20
	bne _021E661E
	mov r0, #0
	pop {r4, r5, r6, pc}
_021E661E:
	mov r1, #0x20
	bic r0, r1
	beq _021E6628
	mov r0, #0
	pop {r4, r5, r6, pc}
_021E6628:
	add r0, r4, #0
	add r1, r6, #0
	add r2, r5, #0
	bl MOD05_021E6638
	mov r0, #1
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E6638
MOD05_021E6638: ; 0x021E6638
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0x18
	add r5, r1, #0
	add r7, r2, #0
	bl MOD05_021E72B8
	add r4, r0, #0
	str r6, [r4, #4]
	str r5, [r4, #8]
	str r7, [r4, #0xc]
	add r0, r7, #0
	bl FUN_020553A0
	str r0, [r4, #0x10]
	add r0, r7, #0
	bl FUN_02055454
	str r0, [r4, #0x14]
	cmp r0, #0
	bne _021E6666
	bl GF_AssertFail
_021E6666:
	ldr r1, _021E6674 ; =MOD05_021E6678
	add r0, r5, #0
	add r2, r4, #0
	bl FUN_020463CC
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E6674: .word MOD05_021E6678

	thumb_func_start MOD05_021E6678
MOD05_021E6678: ; 0x021E6678
	push {r4, lr}
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021E668C
	cmp r0, #1
	beq _021E66CC
	b _021E6710
_021E668C:
	ldr r0, [r4, #0x10]
	bl FUN_0205AD98
	cmp r0, #1
	bne _021E6710
	ldr r0, [r4, #0xc]
	bl PlayerAvatar_GetGender
	add r1, r0, #0
	mov r0, #0
	bl FUN_020555A0
	add r1, r0, #0
	ldr r0, [r4, #0xc]
	bl MOD05_021E726C
	ldr r0, [r4, #4]
	mov r1, #0x34
	bl FUN_0205AFDC
	add r1, r0, #0
	ldr r0, [r4, #0x10]
	bl FUN_0205ADDC
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl MOD06_0224ADF8
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E6710
_021E66CC:
	ldr r0, [r4, #0x10]
	bl FUN_0205AE28
	cmp r0, #0
	beq _021E6710
	ldr r0, [r4, #0x10]
	bl FUN_0205AE50
	ldr r0, [r4, #0x14]
	bl MOD05_021E4DE4
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl FUN_02055450
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl FUN_020553A8
	ldr r0, [r4, #8]
	ldr r1, [r0, #0x1c]
	ldr r1, [r1]
	bl FUN_0204ABA8
	add r1, r0, #0
	ldr r0, [r4, #8]
	mov r2, #1
	bl FUN_0204ABDC
	add r0, r4, #0
	bl MOD05_021E72DC
	mov r0, #1
	pop {r4, pc}
_021E6710:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD05_021E6714
MOD05_021E6714: ; 0x021E6714
	push {r4, r5, r6, lr}
	add r4, r2, #0
	add r6, r0, #0
	add r5, r1, #0
	cmp r4, #1
	bne _021E672E
	cmp r3, #1
	bne _021E672E
	add r0, r5, #0
	bl PlayerAvatar_GetState
	cmp r0, #2
	beq _021E6732
_021E672E:
	mov r0, #0
	pop {r4, r5, r6, pc}
_021E6732:
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02057278
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02054A48
	cmp r0, #0
	bne _021E674A
	mov r0, #0
	pop {r4, r5, r6, pc}
_021E674A:
	add r0, r6, #0
	add r1, r4, #0
	bl MOD05_021E6BD8
	mov r0, #1
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E6758
MOD05_021E6758: ; 0x021E6758
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl FUN_02055764
	cmp r0, #1
	bne _021E676C
	mov r0, #0
	pop {r4, r5, r6, pc}
_021E676C:
	add r0, r4, #0
	bl FUN_020553A0
	bl FUN_02058720
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	add r0, r6, #0
	bl FUN_02054984
	cmp r0, #1
	beq _021E6792
	add r0, r6, #0
	bl FUN_020549A0
	cmp r0, #1
	beq _021E6792
	mov r0, #0
	pop {r4, r5, r6, pc}
_021E6792:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021E67A0
	mov r0, #1
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E67A0
MOD05_021E67A0: ; 0x021E67A0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x10
	add r4, r1, #0
	bl MOD05_021E72B8
	add r2, r0, #0
	str r5, [r2, #8]
	ldr r1, _021E67BC ; =MOD05_021E67C0
	add r0, r5, #0
	str r4, [r2, #0xc]
	bl FUN_020463CC
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021E67BC: .word MOD05_021E67C0

	thumb_func_start MOD05_021E67C0
MOD05_021E67C0: ; 0x021E67C0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r0, #0
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl FUN_020553A0
	add r7, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021E67E4
	cmp r0, #1
	beq _021E67F0
	cmp r0, #2
	beq _021E682A
	b _021E68C6
_021E67E4:
	ldr r0, _021E68CC ; =0x00000651
	bl PlaySE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021E67F0:
	add r0, r7, #0
	bl FUN_0205AD98
	cmp r0, #0
	bne _021E6804
	ldr r0, [r4, #0xc]
	bl FUN_020570C4
	cmp r0, #0
	beq _021E68C6
_021E6804:
	ldr r0, [r4, #4]
	cmp r0, #5
	blt _021E6824
	ldr r0, _021E68D0 ; =0x00000652
	bl PlaySE
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0205574C
	add r0, r4, #0
	bl MOD05_021E72DC
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021E6824:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021E682A:
	ldr r0, [r4, #0xc]
	bl PlayerAvatar_GetFacingDirection
	ldr r2, _021E68D4 ; =gSystem
	str r0, [sp]
	ldr r1, [r2, #0x48]
	ldr r2, [r2, #0x44]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r4, #0xc]
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	bl FUN_02057020
	add r5, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	beq _021E68C6
	ldr r0, [sp]
	cmp r5, r0
	beq _021E68C6
	mov r0, #1
	str r0, [r4]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	add r0, r7, #0
	bl FUN_02058720
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020549A0
	cmp r0, #1
	bne _021E68A2
	add r0, r6, #0
	bl FUN_02046528
	add r1, sp, #8
	str r0, [sp, #4]
	bl MOD06_0223C08C
	cmp r0, #1
	bne _021E68A2
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0205574C
	add r0, r4, #0
	bl MOD05_021E72DC
	ldr r0, [sp, #4]
	ldr r2, [sp, #8]
	add r1, r6, #0
	bl FUN_02046A20
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021E68A2:
	ldr r0, [r4, #4]
	cmp r0, #5
	bge _021E68AC
	mov r6, #0x28
	b _021E68B6
_021E68AC:
	add r0, r7, #0
	mov r1, #1
	mov r6, #0x30
	bl FUN_02058A18
_021E68B6:
	add r0, r5, #0
	add r1, r6, #0
	bl FUN_0205AFDC
	add r1, r0, #0
	ldr r0, [r4, #0xc]
	bl FUN_02057260
_021E68C6:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021E68CC: .word 0x00000651
_021E68D0: .word 0x00000652
_021E68D4: .word gSystem

	thumb_func_start MOD05_021E68D8
MOD05_021E68D8: ; 0x021E68D8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl FUN_020553A0
	bl FUN_0205AD98
	cmp r0, #0
	bne _021E68F0
	mov r0, #0
	pop {r3, r4, r5, pc}
_021E68F0:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021E6904
	cmp r0, #1
	bne _021E6900
	mov r0, #1
	pop {r3, r4, r5, pc}
_021E6900:
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021E6904
MOD05_021E6904: ; 0x021E6904
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl FUN_02055408
	cmp r0, #1
	bge _021E6916
	mov r0, #0
	pop {r4, pc}
_021E6916:
	add r0, r4, #0
	bl FUN_02055314
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021E727C
	add r4, r0, #0
	bne _021E692C
	mov r0, #0
	pop {r4, pc}
_021E692C:
	bl FUN_02058458
	cmp r0, #0x76
	beq _021E6938
	mov r0, #0
	pop {r4, pc}
_021E6938:
	add r0, r4, #0
	bl MOD05_021F1AF8
	add r0, r4, #0
	bl FUN_02057654
	ldr r0, _021E6950 ; =0x0000065B
	bl PlaySE
	mov r0, #0
	pop {r4, pc}
	nop
_021E6950: .word 0x0000065B

	thumb_func_start MOD05_021E6954
MOD05_021E6954: ; 0x021E6954
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0x30
	add r7, r1, #0
	add r5, r2, #0
	bl MOD05_021E72B8
	add r4, r0, #0
	str r7, [r4, #4]
	str r6, [r4, #0xc]
	ldr r0, [r6, #0x38]
	str r0, [r4, #0x10]
	bl FUN_020553A0
	add r2, r4, #0
	str r0, [r4, #0x14]
	add r2, #0x1c
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r6, #0x10]
	ldr r1, _021E698C ; =MOD05_021E69FC
	add r2, r4, #0
	bl FUN_0204640C
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E698C: .word MOD05_021E69FC

	thumb_func_start CallFieldTask_RockClimb
CallFieldTask_RockClimb: ; 0x021E6990
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r6, r2, #0
	add r5, r1, #0
	bl FUN_02046528
	add r4, r0, #0
	add r1, r6, #0
	bl MOD05_021E72E8
	add r1, r0, #0
	add r0, r4, #0
	add r2, sp, #0
	bl MOD05_021E7228
	add r0, r4, #0
	add r1, r5, #0
	add r2, sp, #0
	bl MOD05_021E6954
	add sp, #0x10
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021E69BC
MOD05_021E69BC: ; 0x021E69BC
	push {r3, lr}
	cmp r1, #3
	bhi _021E69F6
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E69CE: ; jump table
	.short _021E69D6 - _021E69CE - 2 ; case 0
	.short _021E69D6 - _021E69CE - 2 ; case 1
	.short _021E69E6 - _021E69CE - 2 ; case 2
	.short _021E69E6 - _021E69CE - 2 ; case 3
_021E69D6:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020548FC
	cmp r0, #1
	bne _021E69F6
	mov r0, #1
	pop {r3, pc}
_021E69E6:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02054908
	cmp r0, #1
	bne _021E69F6
	mov r0, #1
	pop {r3, pc}
_021E69F6:
	mov r0, #0
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E69FC
MOD05_021E69FC: ; 0x021E69FC
	push {r4, r5, r6, lr}
	bl FUN_0204652C
	ldr r6, _021E6A24 ; =UNK05_021F7714
	add r5, r0, #0
_021E6A06:
	ldr r1, [r5]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r1, [r6, r1]
	blx r1
	add r4, r0, #0
	cmp r4, #2
	beq _021E6A06
	cmp r4, #1
	bne _021E6A20
	add r0, r5, #0
	bl MOD05_021E72DC
_021E6A20:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021E6A24: .word UNK05_021F7714

	thumb_func_start MOD05_021E6A28
MOD05_021E6A28: ; 0x021E6A28
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r4, #0xc]
	add r1, #0x1c
	bl MOD05_021E723C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD05_021E6A40
MOD05_021E6A40: ; 0x021E6A40
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x1c
	bl MOD05_021E7250
	cmp r0, #1
	bne _021E6A54
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021E6A54:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD05_021E6A58
MOD05_021E6A58: ; 0x021E6A58
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x10]
	bl GetPlayerXCoord
	add r4, r0, #0
	ldr r0, [r5, #4]
	bl FUN_02059BF4
	add r6, r0, #0
	ldr r0, [r5, #0x10]
	bl GetPlayerYCoord
	add r7, r0, #0
	ldr r0, [r5, #4]
	bl FUN_02059C00
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, [r5, #0x14]
	ldr r3, [r5, #4]
	add r1, r4, r6
	add r2, r7, r2
	bl MOD06_0224AEE8
	str r0, [r5, #0x18]
	ldr r0, [r5, #0xc]
	bl MOD06_0224F0BC
	str r0, [r5, #0x2c]
	ldr r0, _021E6AA8 ; =0x00000627
	bl PlaySE
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E6AA8: .word 0x00000627

	thumb_func_start MOD05_021E6AAC
MOD05_021E6AAC: ; 0x021E6AAC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	bl FUN_0205AD98
	cmp r0, #1
	bne _021E6AD0
	ldr r0, [r4, #4]
	mov r1, #0x34
	bl FUN_0205AFDC
	add r1, r0, #0
	ldr r0, [r4, #0x14]
	bl FUN_0205ADDC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021E6AD0:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD05_021E6AD4
MOD05_021E6AD4: ; 0x021E6AD4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	bl FUN_0205AE28
	cmp r0, #1
	bne _021E6AF0
	ldr r0, [r4]
	mov r1, #1
	add r0, r0, #1
	str r0, [r4]
	ldr r0, [r4, #0x18]
	bl MOD06_0224AF68
_021E6AF0:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD05_021E6AF4
MOD05_021E6AF4: ; 0x021E6AF4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	bl FUN_0205AD98
	cmp r0, #1
	bne _021E6B18
	ldr r0, [r4, #4]
	mov r1, #0x10
	bl FUN_0205AFDC
	add r1, r0, #0
	ldr r0, [r4, #0x14]
	bl FUN_0205ADDC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021E6B18:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD05_021E6B1C
MOD05_021E6B1C: ; 0x021E6B1C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x14]
	bl FUN_0205AE28
	cmp r0, #0
	bne _021E6B2E
	mov r0, #0
	pop {r3, r4, r5, pc}
_021E6B2E:
	ldr r0, [r5, #0x14]
	bl FUN_020584D4
	add r4, r0, #0
	ldr r0, [r5, #0x14]
	add r1, r4, #0
	bl FUN_02059C90
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, r4, #0
	bl MOD05_021E69BC
	cmp r0, #1
	bne _021E6B54
	mov r0, #5
	str r0, [r5]
	mov r0, #2
	pop {r3, r4, r5, pc}
_021E6B54:
	ldr r0, [r5, #4]
	mov r1, #0x34
	bl FUN_0205AFDC
	add r1, r0, #0
	ldr r0, [r5, #0x14]
	bl FUN_0205ADDC
	mov r1, #0
	str r1, [r5, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	ldr r0, [r5, #0x18]
	bl MOD06_0224AF68
	ldr r0, [r5, #0x2c]
	bl MOD06_0224F0D0
	mov r0, #0
	str r0, [r5, #0x2c]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021E6B80
MOD05_021E6B80: ; 0x021E6B80
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	bl FUN_0205AE28
	cmp r0, #0
	bne _021E6B92
	mov r0, #0
	pop {r4, pc}
_021E6B92:
	ldr r0, [r4, #0x14]
	bl FUN_0205AE50
	ldr r0, [r4, #0x18]
	bl MOD05_021E4DE4
	mov r0, #1
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E6BA4
MOD05_021E6BA4: ; 0x021E6BA4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0x54
	add r7, r1, #0
	add r5, r2, #0
	bl MOD05_021E72B8
	add r4, r0, #0
	str r7, [r4, #4]
	str r6, [r4, #0x34]
	.balign 4, 0
_021E6BB8: .word 0x63A06BB0

	thumb_func_start MOD05_021E6BBC
MOD05_021E6BBC: ; 0x021E6BBC
	ldr r0, [r6, #0x38]
	bl FUN_020553A0
	str r0, [r4, #0x3c]
	cmp r5, #0
	beq _021E6BD4
	add r2, r4, #0
	add r2, #0x40
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
_021E6BD4:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021E6BD8
MOD05_021E6BD8: ; 0x021E6BD8
	push {r4, lr}
	mov r2, #0
	add r4, r0, #0
	bl MOD05_021E6BA4
	add r2, r0, #0
	ldr r1, _021E6BF0 ; =MOD05_021E6C30
	add r0, r4, #0
	bl FUN_020463CC
	pop {r4, pc}
	nop
_021E6BF0: .word MOD05_021E6C30

	thumb_func_start CallFieldTask_Waterfall
CallFieldTask_Waterfall: ; 0x021E6BF4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r2, #0
	add r5, r0, #0
	add r6, r1, #0
	bl FUN_02046528
	add r4, r0, #0
	add r1, r7, #0
	bl MOD05_021E72E8
	add r1, r0, #0
	add r0, r4, #0
	add r2, sp, #0
	bl MOD05_021E7228
	add r0, r4, #0
	add r1, r6, #0
	add r2, sp, #0
	bl MOD05_021E6BA4
	add r2, r0, #0
	ldr r1, _021E6C2C ; =MOD05_021E6C30
	add r0, r5, #0
	bl FUN_0204640C
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E6C2C: .word MOD05_021E6C30

	thumb_func_start MOD05_021E6C30
MOD05_021E6C30: ; 0x021E6C30
	push {r4, r5, r6, lr}
	bl FUN_0204652C
	ldr r6, _021E6C70 ; =UNK05_021F7700
	ldr r4, _021E6C74 ; =UNK05_021F76EC
	add r5, r0, #0
_021E6C3C:
	ldr r0, [r5, #4]
	cmp r0, #0
	bne _021E6C4E
	ldr r1, [r5]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	blx r1
	b _021E6C58
_021E6C4E:
	ldr r1, [r5]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r1, [r6, r1]
	blx r1
_021E6C58:
	cmp r0, #2
	beq _021E6C3C
	cmp r0, #1
	bne _021E6C6A
	add r0, r5, #0
	bl MOD05_021E72DC
	mov r0, #1
	pop {r4, r5, r6, pc}
_021E6C6A:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_021E6C70: .word UNK05_021F7700
_021E6C74: .word UNK05_021F76EC

	thumb_func_start MOD05_021E6C78
MOD05_021E6C78: ; 0x021E6C78
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	cmp r0, #1
	bne _021E6C96
	add r1, r4, #0
	ldr r0, [r4, #0x34]
	add r1, #0x40
	bl MOD05_021E723C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
_021E6C96:
	mov r0, #2
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E6CA0
MOD05_021E6CA0: ; 0x021E6CA0
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x40
	bl MOD05_021E7250
	cmp r0, #1
	bne _021E6CBA
	ldr r0, _021E6CC0 ; =0x0000064D
	bl PlaySE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021E6CBA:
	mov r0, #0
	pop {r4, pc}
	nop
_021E6CC0: .word 0x0000064D

	thumb_func_start MOD05_021E6CC4
MOD05_021E6CC4: ; 0x021E6CC4
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r0, [r5, #0x3c]
	bl FUN_02058B2C
	add r4, r0, #0
	mov r0, #0
	bl FUN_02059BF4
	lsl r0, r0, #1
	add r4, r4, r0
	ldr r0, [r5, #0x3c]
	bl FUN_02058B4C
	add r6, r0, #0
	mov r0, #0
	bl FUN_02059C00
	lsl r0, r0, #1
	add r6, r6, r0
	add r2, r5, #0
	add r0, r4, #0
	add r1, r6, #0
	add r2, #0x28
	bl FUN_02059E60
	add r1, r5, #0
	ldr r0, [r5, #0x34]
	add r1, #0x28
	bl FUN_02059E9C
	str r4, [r5, #0xc]
	ldr r0, [r5, #0x2c]
	asr r1, r0, #3
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	str r0, [r5, #0x10]
	str r6, [r5, #0x14]
	ldr r0, [r5, #0x3c]
	add r1, sp, #0xc
	bl FUN_02058B5C
	ldr r1, [sp, #0x14]
	ldr r0, [r5, #0x30]
	cmp r1, r0
	bgt _021E6D2A
	bl GF_AssertFail
_021E6D2A:
	ldr r1, [sp, #0x10]
	ldr r0, [r5, #0x2c]
	cmp r1, r0
	blt _021E6D36
	bl GF_AssertFail
_021E6D36:
	mov r0, #0
	str r0, [sp]
	ldr r1, [r5, #0x2c]
	ldr r0, [sp, #0x10]
	add r3, sp, #0
	sub r2, r1, r0
	ldr r1, [r5, #0x30]
	ldr r0, [sp, #0x14]
	str r2, [sp, #4]
	sub r1, r1, r0
	asr r0, r2, #5
	lsr r0, r0, #0x1a
	add r0, r2, r0
	asr r0, r0, #6
	str r0, [sp, #4]
	asr r0, r1, #5
	lsr r0, r0, #0x1a
	add r0, r1, r0
	add r2, r5, #0
	str r1, [sp, #8]
	asr r0, r0, #6
	str r0, [sp, #8]
	ldmia r3!, {r0, r1}
	add r2, #0x1c
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r5, #0x34]
	bl MOD06_0224ED94
	str r0, [r5, #0x50]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	mov r0, #0
	add sp, #0x18
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021E6D80
MOD05_021E6D80: ; 0x021E6D80
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #0x3c]
	add r1, sp, #0
	bl FUN_02058B5C
	ldr r1, [sp, #4]
	ldr r0, [r4, #0x20]
	add r1, r1, r0
	str r1, [sp, #4]
	ldr r0, [r4, #0x2c]
	cmp r1, r0
	ble _021E6D9E
	str r0, [sp, #4]
_021E6D9E:
	ldr r0, [r4, #0x3c]
	add r1, sp, #0
	bl FUN_02058B6C
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0x20
	blt _021E6DBA
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021E6DBA:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start MOD05_021E6DC0
MOD05_021E6DC0: ; 0x021E6DC0
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #0x3c]
	add r1, sp, #0
	bl FUN_02058B5C
	ldr r1, [sp, #4]
	ldr r0, [r4, #0x20]
	add r1, r1, r0
	str r1, [sp, #4]
	ldr r0, [r4, #0x2c]
	cmp r1, r0
	ble _021E6DDE
	str r0, [sp, #4]
_021E6DDE:
	ldr r1, [sp, #8]
	ldr r0, [r4, #0x24]
	add r1, r1, r0
	str r1, [sp, #8]
	ldr r0, [r4, #0x30]
	cmp r1, r0
	bge _021E6DEE
	str r0, [sp, #8]
_021E6DEE:
	ldr r0, [r4, #0x3c]
	add r1, sp, #0
	bl FUN_02058B6C
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0x40
	bge _021E6E06
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021E6E06:
	ldr r1, [sp, #8]
	ldr r0, [r4, #0x30]
	cmp r1, r0
	beq _021E6E12
	bl GF_AssertFail
_021E6E12:
	ldr r1, [sp, #4]
	ldr r0, [r4, #0x2c]
	cmp r1, r0
	beq _021E6E1E
	bl GF_AssertFail
_021E6E1E:
	ldr r0, [r4, #0x3c]
	ldr r1, [r4, #0xc]
	bl FUN_02058B30
	ldr r0, [r4, #0x3c]
	ldr r1, [r4, #0x10]
	bl FUN_02058B40
	ldr r0, [r4, #0x3c]
	ldr r1, [r4, #0x14]
	bl FUN_02058B50
	ldr r0, [r4, #0x3c]
	bl FUN_02059C60
	ldr r0, [r4, #0x50]
	bl MOD06_0224EDA8
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start MOD05_021E6E48
MOD05_021E6E48: ; 0x021E6E48
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	cmp r0, #1
	bne _021E6E66
	add r1, r4, #0
	ldr r0, [r4, #0x34]
	add r1, #0x40
	bl MOD05_021E723C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
_021E6E66:
	mov r0, #2
	str r0, [r4]
	pop {r4, pc}

	thumb_func_start MOD05_021E6E6C
MOD05_021E6E6C: ; 0x021E6E6C
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x40
	bl MOD05_021E7250
	cmp r0, #1
	bne _021E6E86
	ldr r0, _021E6E8C ; =0x0000064D
	bl PlaySE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021E6E86:
	mov r0, #0
	pop {r4, pc}
	nop
_021E6E8C: .word 0x0000064D

	thumb_func_start MOD05_021E6E90
MOD05_021E6E90: ; 0x021E6E90
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r0, [r5, #0x3c]
	bl FUN_02058B2C
	add r4, r0, #0
	mov r0, #1
	bl FUN_02059BF4
	lsl r0, r0, #1
	add r4, r4, r0
	ldr r0, [r5, #0x3c]
	bl FUN_02058B4C
	add r6, r0, #0
	mov r0, #1
	bl FUN_02059C00
	lsl r0, r0, #1
	add r6, r6, r0
	add r2, r5, #0
	add r0, r4, #0
	add r1, r6, #0
	add r2, #0x28
	bl FUN_02059E60
	add r1, r5, #0
	ldr r0, [r5, #0x34]
	add r1, #0x28
	bl FUN_02059E9C
	mov r0, #0
	str r0, [r5, #0x18]
	str r4, [r5, #0xc]
	ldr r0, [r5, #0x2c]
	asr r1, r0, #3
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	str r0, [r5, #0x10]
	str r6, [r5, #0x14]
	ldr r0, [r5, #0x3c]
	add r1, sp, #0xc
	bl FUN_02058B5C
	ldr r1, [sp, #0x14]
	ldr r0, [r5, #0x30]
	cmp r1, r0
	blt _021E6EFA
	bl GF_AssertFail
_021E6EFA:
	ldr r1, [sp, #0x10]
	ldr r0, [r5, #0x2c]
	cmp r1, r0
	bgt _021E6F06
	bl GF_AssertFail
_021E6F06:
	mov r0, #0
	str r0, [sp]
	ldr r1, [r5, #0x2c]
	ldr r0, [sp, #0x10]
	add r3, sp, #0
	sub r2, r1, r0
	ldr r1, [r5, #0x30]
	ldr r0, [sp, #0x14]
	str r2, [sp, #4]
	sub r1, r1, r0
	asr r0, r2, #5
	lsr r0, r0, #0x1a
	add r0, r2, r0
	asr r0, r0, #6
	str r0, [sp, #4]
	asr r0, r1, #5
	lsr r0, r0, #0x1a
	add r0, r1, r0
	add r2, r5, #0
	str r1, [sp, #8]
	asr r0, r0, #6
	str r0, [sp, #8]
	ldmia r3!, {r0, r1}
	add r2, #0x1c
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r5, #0x34]
	bl MOD06_0224ED94
	str r0, [r5, #0x50]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	mov r0, #0
	add sp, #0x18
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021E6F50
MOD05_021E6F50: ; 0x021E6F50
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #0x3c]
	add r1, sp, #0
	bl FUN_02058B5C
	ldr r1, [sp, #8]
	ldr r0, [r4, #0x24]
	add r1, r1, r0
	str r1, [sp, #8]
	ldr r0, [r4, #0x30]
	cmp r1, r0
	ble _021E6F70
	str r0, [sp, #8]
	b _021E6F78
_021E6F70:
	ldr r1, [r4, #0x18]
	ldr r0, [r4, #0x24]
	add r0, r1, r0
	str r0, [r4, #0x18]
_021E6F78:
	ldr r0, [r4, #0x3c]
	add r1, sp, #0
	bl FUN_02058B6C
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0x20
	blt _021E6F94
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021E6F94:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E6F9C
MOD05_021E6F9C: ; 0x021E6F9C
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #0x3c]
	add r1, sp, #0
	bl FUN_02058B5C
	ldr r1, [sp, #4]
	ldr r0, [r4, #0x20]
	add r1, r1, r0
	str r1, [sp, #4]
	ldr r0, [r4, #0x2c]
	cmp r1, r0
	bge _021E6FBA
	str r0, [sp, #4]
_021E6FBA:
	ldr r1, [sp, #8]
	ldr r0, [r4, #0x24]
	add r1, r1, r0
	str r1, [sp, #8]
	ldr r0, [r4, #0x30]
	cmp r1, r0
	ble _021E6FCC
	str r0, [sp, #8]
	b _021E6FD4
_021E6FCC:
	ldr r1, [r4, #0x18]
	ldr r0, [r4, #0x24]
	add r0, r1, r0
	str r0, [r4, #0x18]
_021E6FD4:
	ldr r0, [r4, #0x3c]
	add r1, sp, #0
	bl FUN_02058B6C
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0x40
	bge _021E6FEC
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021E6FEC:
	ldr r1, [sp, #8]
	ldr r0, [r4, #0x30]
	cmp r1, r0
	beq _021E6FF8
	bl GF_AssertFail
_021E6FF8:
	ldr r1, [sp, #4]
	ldr r0, [r4, #0x2c]
	cmp r1, r0
	beq _021E7004
	bl GF_AssertFail
_021E7004:
	ldr r0, [r4, #0x3c]
	ldr r1, [r4, #0xc]
	bl FUN_02058B30
	ldr r0, [r4, #0x3c]
	ldr r1, [r4, #0x10]
	bl FUN_02058B40
	ldr r0, [r4, #0x3c]
	ldr r1, [r4, #0x14]
	bl FUN_02058B50
	ldr r0, [r4, #0x3c]
	bl FUN_02059C60
	ldr r0, [r4, #0x50]
	bl MOD06_0224EDA8
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E7030
MOD05_021E7030: ; 0x021E7030
	push {r3, lr}
	bl FUN_02046528
	bl MOD05_021E703C
	pop {r3, pc}

	thumb_func_start MOD05_021E703C
MOD05_021E703C: ; 0x021E703C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x18
	bl MOD05_021E72B8
	add r4, r0, #0
	str r5, [r4]
	ldr r0, [r5, #0x38]
	str r0, [r4, #4]
	bl FUN_020553A0
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	bl PlayerAvatar_GetGender
	str r0, [r4, #0x10]
	ldr r0, [r5, #0x10]
	ldr r1, _021E7068 ; =MOD05_021E706C
	add r2, r4, #0
	bl FUN_0204640C
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021E7068: .word MOD05_021E706C

	thumb_func_start MOD05_021E706C
MOD05_021E706C: ; 0x021E706C
	push {r4, lr}
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021E7084
	cmp r0, #1
	beq _021E7096
	cmp r0, #2
	beq _021E70C8
	b _021E70E2
_021E7084:
	ldr r0, [r4, #8]
	ldr r1, _021E70E8 ; =UNK05_021F7758
	bl FUN_0205AEA4
	str r0, [r4, #0x14]
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _021E70E2
_021E7096:
	ldr r0, [r4, #0x14]
	bl FUN_0205AEF0
	cmp r0, #1
	bne _021E70E2
	ldr r1, [r4, #0x10]
	mov r0, #5
	bl FUN_020555A0
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD05_021E726C
	ldr r0, [r4, #0x14]
	bl FUN_0205AEFC
	ldr r0, [r4, #8]
	ldr r1, _021E70EC ; =UNK05_021F77BC
	bl FUN_0205AEA4
	str r0, [r4, #0x14]
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _021E70E2
_021E70C8:
	ldr r0, [r4, #0x14]
	bl FUN_0205AEF0
	cmp r0, #1
	bne _021E70E2
	ldr r0, [r4, #0x14]
	bl FUN_0205AEFC
	add r0, r4, #0
	bl MOD05_021E72DC
	mov r0, #1
	pop {r4, pc}
_021E70E2:
	mov r0, #0
	pop {r4, pc}
	nop
_021E70E8: .word UNK05_021F7758
_021E70EC: .word UNK05_021F77BC

	thumb_func_start MOD05_021E70F0
MOD05_021E70F0: ; 0x021E70F0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl FUN_020553A0
	add r5, r0, #0
	bl FUN_02058934
	cmp r0, #0
	beq _021E7136
	add r0, r4, #0
	bl PlayerAvatar_GetState
	cmp r0, #0
	bne _021E7136
	add r0, r5, #0
	bl FUN_02058458
	sub r0, #0xc4
	cmp r0, #1
	bls _021E7136
	add r0, r4, #0
	bl FUN_020553E0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #0x40
	bl MOD05_021E5FD8
	add r0, r4, #0
	bl MOD05_021E5FE0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021E5FD8
_021E7136:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021E7138
MOD05_021E7138: ; 0x021E7138
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl FUN_020553A0
	add r5, r0, #0
	bl FUN_02058934
	cmp r0, #0
	beq _021E7180
	add r0, r4, #0
	bl PlayerAvatar_GetState
	cmp r0, #0
	bne _021E7180
	add r0, r5, #0
	bl FUN_02058458
	cmp r0, #0xc4
	beq _021E7162
	cmp r0, #0xc5
	bne _021E7180
_021E7162:
	add r0, r4, #0
	bl FUN_020553E0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl MOD05_021E5FD8
	add r0, r4, #0
	bl MOD05_021E5FE0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021E5FD8
_021E7180:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E7184
MOD05_021E7184: ; 0x021E7184
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r5, [r6, #0x38]
	add r0, r5, #0
	bl PlayerAvatar_GetState
	add r7, r0, #0
	beq _021E7198
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021E7198:
	add r0, r5, #0
	bl FUN_020553A0
	str r0, [sp]
	mov r0, #4
	mov r1, #0x10
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	mov r0, #0
	str r0, [r4]
	str r6, [r4, #8]
	str r5, [r4, #0xc]
	ldr r0, [sp]
	str r7, [r4, #4]
	bl FUN_02058914
	add r0, r5, #0
	mov r1, #0x80
	bl MOD05_021E5FD8
	add r0, r5, #0
	bl MOD05_021E5FE0
	ldr r0, _021E71E0 ; =MOD05_021E7218
	ldr r2, _021E71E4 ; =0x0000FFFF
	add r1, r4, #0
	bl FUN_0200CA44
	add r4, r0, #0
	bne _021E71DA
	bl GF_AssertFail
_021E71DA:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E71E0: .word MOD05_021E7218
_021E71E4: .word 0x0000FFFF

	thumb_func_start MOD05_021E71E8
MOD05_021E71E8: ; 0x021E71E8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	beq _021E7216
	bl FUN_0201B6C8
	add r6, r0, #0
	ldr r4, [r6, #0xc]
	add r0, r4, #0
	bl PlayerAvatar_GetGender
	add r1, r0, #0
	mov r0, #0
	bl FUN_020555A0
	add r0, r4, #0
	bl MOD05_021E6014
	add r0, r6, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_021E7216:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021E7218
MOD05_021E7218: ; 0x021E7218
	push {r3, lr}
	ldr r0, [r1, #0xc]
	bl FUN_020553A0
	bl FUN_020586A0
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E7228
MOD05_021E7228: ; 0x021E7228
	push {r4, lr}
	add r4, r2, #0
	mov r2, #1
	str r2, [r4]
	str r1, [r4, #8]
	ldr r0, [r0, #0x38]
	bl PlayerAvatar_GetGender
	str r0, [r4, #4]
	pop {r4, pc}

	thumb_func_start MOD05_021E723C
MOD05_021E723C: ; 0x021E723C
	push {r4, lr}
	add r4, r1, #0
	ldr r2, [r4, #8]
	ldr r3, [r4, #4]
	mov r1, #0
	bl MOD06_0224666C
	str r0, [r4, #0xc]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E7250
MOD05_021E7250: ; 0x021E7250
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl MOD06_022466A0
	cmp r0, #1
	bne _021E7268
	ldr r0, [r4, #0xc]
	bl MOD06_022466AC
	mov r0, #1
	pop {r4, pc}
_021E7268:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD05_021E726C
MOD05_021E726C: ; 0x021E726C
	push {r4, lr}
	add r4, r1, #0
	bl FUN_020553A0
	add r1, r4, #0
	bl MOD05_021F3490
	pop {r4, pc}

	thumb_func_start MOD05_021E727C
MOD05_021E727C: ; 0x021E727C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r4, r0, #0
	bl GetPlayerXCoord
	add r6, r0, #0
	add r0, r5, #0
	bl FUN_02059BF4
	add r7, r0, #0
	add r0, r4, #0
	bl GetPlayerYCoord
	str r0, [sp]
	add r0, r5, #0
	bl FUN_02059C00
	add r5, r0, #0
	add r0, r4, #0
	bl FUN_020553A0
	bl FUN_02058578
	ldr r2, [sp]
	add r1, r6, r7
	add r2, r2, r5
	bl FUN_02058D74
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E72B8
MOD05_021E72B8: ; 0x021E72B8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #4
	add r1, r5, #0
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	bne _021E72CC
	bl GF_AssertFail
_021E72CC:
	add r0, r4, #0
	mov r1, #0
	add r2, r5, #0
	bl memset
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E72DC
MOD05_021E72DC: ; 0x021E72DC
	ldr r3, _021E72E4 ; =FreeToHeapExplicit
	add r1, r0, #0
	mov r0, #4
	bx r3
	.balign 4, 0
_021E72E4: .word FreeToHeapExplicit

	thumb_func_start MOD05_021E72E8
MOD05_021E72E8: ; 0x021E72E8
	push {r4, lr}
	ldr r0, [r0, #0xc]
	add r4, r1, #0
	bl SaveArray_PlayerParty_Get
	add r1, r4, #0
	bl GetPartyMonByIndex
	pop {r4, pc}
	.balign 4, 0

	.section .rodata

	.global UNK05_021F76EC
UNK05_021F76EC: ; 0x021F76EC
	.word MOD05_021E6C78, MOD05_021E6CA0, MOD05_021E6CC4, MOD05_021E6D80
	.word MOD05_021E6DC0

	.global UNK05_021F7700
UNK05_021F7700: ; 0x021F7700
	.word MOD05_021E6E48, MOD05_021E6E6C, MOD05_021E6E90, MOD05_021E6F50
	.word MOD05_021E6F9C

	.global UNK05_021F7714
UNK05_021F7714: ; 0x021F7714
	.word MOD05_021E6A28, MOD05_021E6A40, MOD05_021E6A58, MOD05_021E6AAC
	.word MOD05_021E6AD4, MOD05_021E6AF4, MOD05_021E6B1C, MOD05_021E6B80

	.global UNK05_021F7734
UNK05_021F7734: ; 0x021F7734
	.word MOD05_021E6014, MOD05_021E6054, MOD05_021E609C, MOD05_021E610C
	.word MOD05_021E6118, MOD05_021E6134, MOD05_021E6150, MOD05_021E616C
	.word MOD05_021E6188

	.global UNK05_021F7758
UNK05_021F7758: ; 0x021F7758
	.byte 0x01, 0x00, 0x01, 0x00 ;short?
	.byte 0x3C, 0x00, 0x02, 0x00, 0x02, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00
	.byte 0x3C, 0x00, 0x02, 0x00, 0x03, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x02, 0x00, 0x01, 0x00, 0x01, 0x00
	.byte 0x3C, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00
	.byte 0x3C, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00
	.byte 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00
	.byte 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0xFE, 0x00, 0x00, 0x00

	.global UNK05_021F77BC
UNK05_021F77BC: ; 0x021F77BC
	.byte 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00 ;short?
	.byte 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00
	.byte 0x01, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x01, 0x00
	.byte 0x00, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x01, 0x00
	.byte 0x01, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x02, 0x00, 0x02, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x03, 0x00
	.byte 0x00, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x04, 0x00, 0x03, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x05, 0x00
	.byte 0x01, 0x00, 0x01, 0x00, 0xFE, 0x00, 0x00, 0x00
