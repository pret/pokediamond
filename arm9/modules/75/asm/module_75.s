	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD75_021E6BA0
MOD75_021E6BA0: ; 0x021E6BA0
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	bl FUN_02015F1C
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r2, [r0]
	ldr r1, _021E6D58 ; =0xFFFFE0FF
	ldr r3, _021E6D5C ; =0x04001000
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
	mov r1, #6
	mov r0, #3
	lsl r2, r1, #0xf
	bl FUN_0201681C
	ldr r1, _021E6D60 ; =0x000004A4
	add r0, r5, #0
	mov r2, #6
	bl FUN_02006268
	ldr r2, _021E6D60 ; =0x000004A4
	mov r1, #0
	add r4, r0, #0
	bl memset
	add r0, r5, #0
	bl FUN_0200628C
	add r1, r4, #0
	add r1, #0xc4
	str r0, [r1]
	add r0, r4, #0
	bl MOD75_021E6FA4
	mov r0, #6
	bl FUN_02016B94
	str r0, [r4]
	add r0, r4, #0
	add r0, #0xcc
	ldr r0, [r0]
	bl PlayerData_GetTrainerGender
	ldr r1, _021E6D64 ; =0x00000425
	mov r3, #0
	strb r0, [r4, r1]
	mov r1, #6
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r1, #3
	add r2, r1, #0
	bl FUN_0200E1D0
	mov r0, #3
	mov r1, #8
	bl FUN_0201669C
	add r0, r4, #0
	bl MOD75_021E7470
	add r0, r4, #0
	bl MOD75_021E737C
	add r0, r4, #0
	bl MOD75_021E771C
	add r0, r4, #0
	bl MOD75_021E73E8
	add r0, r4, #0
	bl MOD75_021E7CE4
	bl MOD75_021E7034
	ldr r0, [r4]
	bl MOD75_021E7054
	add r0, r4, #0
	bl MOD75_021E7214
	add r0, r4, #0
	bl MOD75_021E8680
	bl FUN_0201CC08
	mov r0, #4
	bl FUN_0201CC24
	add r0, r4, #0
	bl MOD75_021EA604
	mov r0, #1
	bl FUN_02002BB8
	add r0, r4, #0
	bl MOD75_021EA7BC
	add r0, r4, #0
	bl MOD75_021EA81C
	add r0, r4, #0
	bl MOD75_021EA8BC
	add r0, r4, #0
	bl MOD75_021EA9F8
	add r0, r4, #0
	bl MOD75_021EB048
	add r0, r4, #0
	bl MOD75_021EAD94
	add r0, r4, #0
	bl MOD75_021E7580
	add r0, r4, #0
	add r0, #0xc4
	ldr r3, [r0]
	add r0, r3, #0
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	add r2, r1, #0
	mul r2, r0
	add r0, r3, #0
	add r1, r3, #0
	add r0, #0xa
	add r1, #8
	add r0, r0, r2
	add r1, r1, r2
	add r2, r3, r2
	ldrb r2, [r2, #0xd]
	bl MOD75_021E7758
	add r0, r4, #0
	add r0, #0xc4
	ldr r3, [r0]
	add r0, r3, #0
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	add r2, r1, #0
	mul r2, r0
	add r0, r3, #0
	add r1, r3, #0
	add r0, #0xa
	add r1, #8
	add r0, r0, r2
	add r1, r1, r2
	add r2, r3, r2
	ldrb r2, [r2, #0xd]
	mov r3, #9
	bl MOD75_021E7794
	add r0, r4, #0
	bl MOD75_021EB9B4
	add r0, r4, #0
	add r0, #0xc4
	ldr r3, [r0]
	add r0, r3, #0
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	add r2, r1, #0
	mul r2, r0
	add r2, r3, r2
	ldrh r1, [r2, #0xa]
	ldrh r2, [r2, #8]
	add r0, r4, #0
	bl MOD75_021E77E8
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r0, #0x65
	ldrb r0, [r0]
	add r0, #0xfc
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #1
	bhi _021E6D3A
	add r0, r4, #0
	bl MOD75_021EB8E8
_021E6D3A:
	ldr r0, _021E6D68 ; =MOD75_021E700C
	add r1, r4, #0
	bl FUN_02015F10
	mov r1, #0
	mov r0, #0x33
	add r2, r1, #0
	bl FUN_0200433C
	bl FUN_02033F20
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_021E6D58: .word 0xFFFFE0FF
_021E6D5C: .word 0x04001000
_021E6D60: .word 0x000004A4
_021E6D64: .word 0x00000425
_021E6D68: .word MOD75_021E700C
	thumb_func_end MOD75_021E6BA0

	thumb_func_start MOD75_021E6D6C
MOD75_021E6D6C: ; 0x021E6D6C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	bl FUN_02006278
	ldr r1, [r4]
	add r5, r0, #0
	cmp r1, #0x18
	bhi _021E6DC2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E6D88: ; jump table
	.short _021E6DBA - _021E6D88 - 2 ; case 0
	.short _021E6DF2 - _021E6D88 - 2 ; case 1
	.short _021E6DFA - _021E6D88 - 2 ; case 2
	.short _021E6E36 - _021E6D88 - 2 ; case 3
	.short _021E6E44 - _021E6D88 - 2 ; case 4
	.short _021E6EE0 - _021E6D88 - 2 ; case 5
	.short _021E6EE0 - _021E6D88 - 2 ; case 6
	.short _021E6E4C - _021E6D88 - 2 ; case 7
	.short _021E6E54 - _021E6D88 - 2 ; case 8
	.short _021E6E5C - _021E6D88 - 2 ; case 9
	.short _021E6E64 - _021E6D88 - 2 ; case 10
	.short _021E6E6C - _021E6D88 - 2 ; case 11
	.short _021E6E74 - _021E6D88 - 2 ; case 12
	.short _021E6E7C - _021E6D88 - 2 ; case 13
	.short _021E6E84 - _021E6D88 - 2 ; case 14
	.short _021E6E8C - _021E6D88 - 2 ; case 15
	.short _021E6E94 - _021E6D88 - 2 ; case 16
	.short _021E6E9C - _021E6D88 - 2 ; case 17
	.short _021E6EA4 - _021E6D88 - 2 ; case 18
	.short _021E6EAC - _021E6D88 - 2 ; case 19
	.short _021E6EB4 - _021E6D88 - 2 ; case 20
	.short _021E6EBC - _021E6D88 - 2 ; case 21
	.short _021E6EC4 - _021E6D88 - 2 ; case 22
	.short _021E6ECC - _021E6D88 - 2 ; case 23
	.short _021E6ED4 - _021E6D88 - 2 ; case 24
_021E6DBA:
	bl FUN_0200E308
	cmp r0, #1
	beq _021E6DC4
_021E6DC2:
	b _021E6EE0
_021E6DC4:
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #2
	bne _021E6DD8
	mov r0, #0x10
	str r0, [r4]
	b _021E6EE0
_021E6DD8:
	cmp r0, #1
	bne _021E6DE2
	mov r0, #0xe
	str r0, [r4]
	b _021E6EE0
_021E6DE2:
	cmp r0, #3
	bne _021E6DEC
	mov r0, #0x17
	str r0, [r4]
	b _021E6EE0
_021E6DEC:
	mov r0, #1
	str r0, [r4]
	b _021E6EE0
_021E6DF2:
	bl MOD75_021E7AE0
	str r0, [r4]
	b _021E6EE0
_021E6DFA:
	bl MOD75_021E86C0
	add r0, r5, #0
	bl MOD75_021E7EE4
	cmp r0, #1
	bne _021E6EE0
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #2
	bne _021E6E1C
	mov r0, #0x10
	str r0, [r4]
	b _021E6EE0
_021E6E1C:
	cmp r0, #1
	bne _021E6E26
	mov r0, #0xe
	str r0, [r4]
	b _021E6EE0
_021E6E26:
	cmp r0, #3
	bne _021E6E30
	mov r0, #0x17
	str r0, [r4]
	b _021E6EE0
_021E6E30:
	mov r0, #1
	str r0, [r4]
	b _021E6EE0
_021E6E36:
	bl MOD75_021E88BC
	cmp r0, #1
	bne _021E6EE0
	mov r0, #1
	str r0, [r4]
	b _021E6EE0
_021E6E44:
	bl MOD75_021E8CF4
	str r0, [r4]
	b _021E6EE0
_021E6E4C:
	bl MOD75_021E94D0
	str r0, [r4]
	b _021E6EE0
_021E6E54:
	bl MOD75_021E95BC
	str r0, [r4]
	b _021E6EE0
_021E6E5C:
	bl MOD75_021E95E0
	str r0, [r4]
	b _021E6EE0
_021E6E64:
	bl MOD75_021E971C
	str r0, [r4]
	b _021E6EE0
_021E6E6C:
	bl MOD75_021E9750
	str r0, [r4]
	b _021E6EE0
_021E6E74:
	bl MOD75_021E8EB0
	str r0, [r4]
	b _021E6EE0
_021E6E7C:
	bl MOD75_021E8FC8
	str r0, [r4]
	b _021E6EE0
_021E6E84:
	bl MOD75_021E9840
	str r0, [r4]
	b _021E6EE0
_021E6E8C:
	bl MOD75_021E9930
	str r0, [r4]
	b _021E6EE0
_021E6E94:
	bl MOD75_021E9980
	str r0, [r4]
	b _021E6EE0
_021E6E9C:
	bl MOD75_021E9B4C
	str r0, [r4]
	b _021E6EE0
_021E6EA4:
	bl MOD75_021E9B88
	str r0, [r4]
	b _021E6EE0
_021E6EAC:
	bl MOD75_021E9D6C
	str r0, [r4]
	b _021E6EE0
_021E6EB4:
	bl MOD75_021E9D90
	str r0, [r4]
	b _021E6EE0
_021E6EBC:
	bl MOD75_021E9EE4
	str r0, [r4]
	b _021E6EE0
_021E6EC4:
	bl MOD75_021E9F74
	str r0, [r4]
	b _021E6EE0
_021E6ECC:
	bl MOD75_021E9FDC
	str r0, [r4]
	b _021E6EE0
_021E6ED4:
	bl FUN_0200E308
	cmp r0, #1
	bne _021E6EE0
	mov r0, #1
	pop {r3, r4, r5, pc}
_021E6EE0:
	add r0, r5, #0
	bl MOD75_021E85D8
	add r0, r5, #0
	bl MOD75_021EC3B8
	add r0, r5, #0
	bl MOD75_021EC018
	add r5, #0xdc
	ldr r0, [r5]
	bl FUN_0200BC1C
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD75_021E6D6C

	thumb_func_start MOD75_021E6F00
MOD75_021E6F00: ; 0x021E6F00
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02006278
	add r4, r0, #0
	bl MOD75_021EBFE4
	add r0, r4, #0
	bl MOD75_021E7AA4
	add r0, r4, #0
	bl MOD75_021E752C
	add r0, r4, #4
	bl MOD75_021EA7A0
	ldr r0, [r4]
	bl MOD75_021E71BC
	bl FUN_0201CD04
	bl FUN_0201C29C
	add r0, r4, #0
	bl MOD75_021EB110
	add r0, r4, #0
	bl MOD75_021EA7F8
	add r0, r4, #0
	bl MOD75_021EADC0
	add r0, r4, #0
	bl MOD75_021E773C
	mov r0, #0xfe
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl String_dtor
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl DestroyMsgData
	mov r0, #0x47
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl DestroyMsgData
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl DestroyMsgData
	mov r0, #0x11
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_0200B990
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200AB18
	add r4, #0xd4
	ldr r0, [r4]
	bl NARC_dtor
	add r0, r5, #0
	bl FUN_0200627C
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	mov r0, #6
	bl FUN_020168D0
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD75_021E6F00

	thumb_func_start MOD75_021E6FA4
MOD75_021E6FA4: ; 0x021E6FA4
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	ldr r0, [r0]
	bl FUN_0206F158
	add r1, r4, #0
	add r1, #0xc8
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	ldr r0, [r0]
	bl Sav2_GetPlayerDataPtr
	add r1, r4, #0
	add r1, #0xcc
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	ldr r0, [r0]
	bl LoadPlayerDataAddress
	add r4, #0xd0
	str r0, [r4]
	pop {r4, pc}
	thumb_func_end MOD75_021E6FA4

	thumb_func_start MOD75_021E6FDC
MOD75_021E6FDC: ; 0x021E6FDC
	add r0, #0xc4
	ldr r0, [r0]
	ldr r3, _021E6FE8 ; =FUN_0202A9B0
	ldr r0, [r0]
	bx r3
	nop
_021E6FE8: .word FUN_0202A9B0
	thumb_func_end MOD75_021E6FDC

	thumb_func_start MOD75_021E6FEC
MOD75_021E6FEC: ; 0x021E6FEC
	push {r4, lr}
	add r4, r1, #0
	bl MOD75_021E6FDC
	bl FUN_0202AB4C
	strb r4, [r0]
	pop {r4, pc}
	thumb_func_end MOD75_021E6FEC

	thumb_func_start MOD75_021E6FFC
MOD75_021E6FFC: ; 0x021E6FFC
	push {r4, lr}
	add r4, r1, #0
	bl MOD75_021E6FDC
	add r1, r4, #0
	bl FUN_0202AB68
	pop {r4, pc}
	thumb_func_end MOD75_021E6FFC

	thumb_func_start MOD75_021E700C
MOD75_021E700C: ; 0x021E700C
	push {r3, lr}
	ldr r0, [r0]
	bl FUN_0201AB60
	bl FUN_0201C30C
	bl FUN_0200BC30
	ldr r3, _021E702C ; =0x027E0000
	ldr r1, _021E7030 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r3, pc}
	nop
_021E702C: .word 0x027E0000
_021E7030: .word 0x00003FF8
	thumb_func_end MOD75_021E700C

	thumb_func_start MOD75_021E7034
MOD75_021E7034: ; 0x021E7034
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021E7050 ; =0x021EC568
	add r3, sp, #0
	mov r2, #5
_021E703E:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021E703E
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021E7050: .word MOD75_021EC568
	thumb_func_end MOD75_021E7034

	thumb_func_start MOD75_021E7054
MOD75_021E7054: ; 0x021E7054
	push {r4, r5, lr}
	sub sp, #0xd4
	ldr r5, _021E719C ; =0x021EC41C
	add r3, sp, #0xc4
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _021E71A0 ; =0x021EC440
	add r3, sp, #0xa8
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
	ldr r5, _021E71A4 ; =0x021EC45C
	add r3, sp, #0x8c
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
	ldr r5, _021E71A8 ; =0x021EC494
	add r3, sp, #0x70
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
	ldr r5, _021E71AC ; =0x021EC4E8
	add r3, sp, #0x54
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
	ldr r5, _021E71B0 ; =0x021EC478
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	add r0, r4, #0
	mov r1, #4
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	ldr r5, _021E71B4 ; =0x021EC4B0
	add r3, sp, #0x1c
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
	ldr r5, _021E71B8 ; =0x021EC4CC
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
	mov r3, #1
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #7
	mov r2, #9
	mov r3, #0x80
	bl FUN_0201AF50
	add r0, r4, #0
	mov r1, #7
	mov r2, #0xc
	mov r3, #0x50
	bl FUN_0201AF50
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #6
	bl FUN_02017F18
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #6
	bl FUN_02017F18
	add sp, #0xd4
	pop {r4, r5, pc}
	nop
_021E719C: .word MOD75_021EC41C
_021E71A0: .word MOD75_021EC440
_021E71A4: .word MOD75_021EC45C
_021E71A8: .word MOD75_021EC494
_021E71AC: .word MOD75_021EC4E8
_021E71B0: .word MOD75_021EC478
_021E71B4: .word MOD75_021EC4B0
_021E71B8: .word MOD75_021EC4CC
	thumb_func_end MOD75_021E7054

	thumb_func_start MOD75_021E71BC
MOD75_021E71BC: ; 0x021E71BC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x1f
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #0x1b
	mov r1, #0
	bl FUN_0201E74C
	add r0, r4, #0
	mov r1, #7
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #5
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #4
	bl FUN_020178A0
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
	mov r0, #6
	add r1, r4, #0
	bl FUN_02016A8C
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD75_021E71BC

	thumb_func_start MOD75_021E7214
MOD75_021E7214: ; 0x021E7214
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0xd
	mov r1, #6
	bl NARC_ctor
	add r1, r4, #0
	add r1, #0xd4
	str r0, [r1]
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #6
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0xd
	mov r1, #7
	mov r3, #1
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #6
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0xd
	mov r1, #0xa
	mov r3, #1
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #6
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0xd
	mov r1, #9
	mov r3, #3
	bl FUN_020068C8
	mov r2, #0
	str r2, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0xd
	mov r1, #8
	add r3, r2, #0
	bl FUN_02006930
	mov r0, #0x20
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0xd
	mov r1, #0x12
	mov r2, #0
	lsl r3, r0, #5
	bl FUN_02006930
	mov r1, #0x16
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #6
	bl FUN_02002EEC
	mov r1, #0
	str r1, [sp]
	mov r0, #6
	str r0, [sp, #4]
	ldr r0, [r4]
	ldr r2, _021E7374 ; =0x000003F7
	mov r3, #0xe
	bl FUN_0200CB00
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	ldr r0, [r4]
	ldr r2, _021E7378 ; =0x000003D9
	mov r1, #0
	mov r3, #0xc
	bl FUN_0200CD68
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #6
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0xd
	mov r1, #0xb
	mov r3, #5
	bl FUN_0200687C
	mov r3, #0
	str r3, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0xd
	mov r1, #0xc
	mov r2, #4
	bl FUN_02006930
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #6
	str r0, [sp, #0xc]
	mov r0, #0xd
	ldr r2, [r4]
	add r1, r0, #0
	mov r3, #5
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #6
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0xd
	mov r1, #0x25
	mov r3, #7
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #6
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0xd
	mov r1, #0x24
	mov r3, #7
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #6
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0xd
	mov r1, #0xf
	mov r3, #4
	bl FUN_0200687C
	mov r3, #0x40
	str r3, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0xd
	mov r1, #0xe
	mov r2, #4
	bl FUN_02006930
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021E7374: .word 0x000003F7
_021E7378: .word 0x000003D9
	thumb_func_end MOD75_021E7214

	thumb_func_start MOD75_021E737C
MOD75_021E737C: ; 0x021E737C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	mov r1, #0x1a
	mov r2, #7
	mov r3, #6
	bl NewMsgDataFromNarc
	mov r1, #0x45
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #1
	mov r1, #2
	mov r2, #0
	mov r3, #6
	bl FUN_0200B870
	mov r1, #0x11
	lsl r1, r1, #4
	str r0, [r4, r1]
	mov r0, #6
	bl FUN_0200AA80
	mov r2, #0x46
	lsl r2, r2, #2
	str r0, [r4, r2]
	mov r0, #0
	mov r1, #0x1a
	add r2, #0x40
	mov r3, #6
	bl NewMsgDataFromNarc
	mov r1, #0x47
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r2, #0x93
	mov r0, #0
	mov r1, #0x1a
	lsl r2, r2, #2
	mov r3, #6
	bl NewMsgDataFromNarc
	mov r1, #0x12
	lsl r1, r1, #4
	str r0, [r4, r1]
	sub r1, #0x20
	add r0, r1, #0
	mov r1, #6
	bl String_ctor
	mov r1, #0xfe
	lsl r1, r1, #2
	str r0, [r4, r1]
	pop {r4, pc}
	thumb_func_end MOD75_021E737C

	thumb_func_start MOD75_021E73E8
MOD75_021E73E8: ; 0x021E73E8
	push {r4, r5}
	ldr r2, _021E741C ; =0x00000424
	mov r1, #0
	strb r1, [r0, r2]
	add r4, r2, #0
	mov r3, #0xc
_021E73F4:
	add r2, r0, #0
	add r2, #0xc4
	ldr r5, [r2]
	add r2, r1, #0
	mul r2, r3
	add r2, r5, r2
	ldr r2, [r2, #4]
	cmp r2, #0
	beq _021E740C
	ldrb r2, [r0, r4]
	add r2, r2, #1
	strb r2, [r0, r4]
_021E740C:
	add r1, r1, #1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, #8
	blo _021E73F4
	pop {r4, r5}
	bx lr
	nop
_021E741C: .word 0x00000424
	thumb_func_end MOD75_021E73E8

	thumb_func_start MOD75_021E7420
MOD75_021E7420: ; 0x021E7420
	push {r3, r4}
	add r0, #0xc4
	ldr r0, [r0]
	add r4, r0, #4
	add r0, #0x64
	ldrb r3, [r0]
	mov r0, #0xc
	mul r0, r3
	cmp r2, #0
	ldr r2, [r4, r0]
	bne _021E743E
	lsl r0, r1, #2
	ldrh r0, [r2, r0]
	pop {r3, r4}
	bx lr
_021E743E:
	lsl r0, r1, #2
	add r0, r2, r0
	ldrh r0, [r0, #2]
	pop {r3, r4}
	bx lr
	thumb_func_end MOD75_021E7420

	thumb_func_start MOD75_021E7448
MOD75_021E7448: ; 0x021E7448
	add r3, r1, #0
	add r1, r2, #0
	add r2, r3, #0
	ldr r3, _021E7454 ; =ReadMsgDataIntoString
	bx r3
	nop
_021E7454: .word ReadMsgDataIntoString
	thumb_func_end MOD75_021E7448

	thumb_func_start MOD75_021E7458
MOD75_021E7458: ; 0x021E7458
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r0, r2, #0
	bl TMHMGetMove
	add r1, r0, #0
	add r0, r5, #0
	add r2, r4, #0
	bl ReadMsgDataIntoString
	pop {r3, r4, r5, pc}
	thumb_func_end MOD75_021E7458

	thumb_func_start MOD75_021E7470
MOD75_021E7470: ; 0x021E7470
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r5, #0
	add r0, #0x64
	strb r5, [r0]
	add r0, r7, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r6, r0, #4
	ldr r0, [r0, #0x6c]
	cmp r0, #0
	bne _021E74AE
	mov r3, #1
	add r2, r5, #0
	mov r1, #0xc
_021E7492:
	add r0, r5, #0
	mul r0, r1
	add r4, r6, r0
	ldr r0, [r6, r0]
	cmp r0, #0
	beq _021E7528
	add r0, r5, #1
	lsl r0, r0, #0x10
	strh r3, [r4, #4]
	lsr r5, r0, #0x10
	strh r2, [r4, #6]
	cmp r5, #8
	blo _021E7492
	pop {r3, r4, r5, r6, r7, pc}
_021E74AE:
	mov r0, #0xc
	mul r0, r5
	add r4, r6, r0
	ldr r0, [r6, r0]
	cmp r0, #0
	beq _021E74F2
	add r0, r7, #0
	add r0, #0xc4
	ldr r0, [r0]
	ldrb r1, [r4, #8]
	add r2, sp, #0
	ldr r0, [r0, #0x6c]
	add r2, #1
	add r3, sp, #0
	bl FUN_0206F17C
	add r0, sp, #0
	ldrb r0, [r0, #1]
	cmp r0, #0
	bne _021E74DC
	mov r1, #1
	add r0, sp, #0
	strb r1, [r0, #1]
_021E74DC:
	add r0, sp, #0
	ldrb r0, [r0, #1]
	strh r0, [r4, #4]
	add r0, sp, #0
	ldrb r0, [r0]
	strh r0, [r4, #6]
	add r0, r5, #1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #8
	blo _021E74AE
_021E74F2:
	add r0, r7, #0
	add r0, #0xc4
	ldr r0, [r0]
	ldr r0, [r0, #0x6c]
	bl FUN_0206F18C
	mov r1, #0
	mov r3, #0xc
_021E7502:
	add r2, r1, #0
	mul r2, r3
	add r4, r6, r2
	ldr r2, [r6, r2]
	cmp r2, #0
	beq _021E7528
	ldrb r2, [r4, #8]
	cmp r0, r2
	bne _021E751E
	add r2, r7, #0
	add r2, #0xc4
	ldr r2, [r2]
	add r2, #0x64
	strb r1, [r2]
_021E751E:
	add r1, r1, #1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	cmp r1, #8
	blo _021E7502
_021E7528:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD75_021E7470

	thumb_func_start MOD75_021E752C
MOD75_021E752C: ; 0x021E752C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r0, #0xc4
	ldr r1, [r0]
	ldr r0, [r1, #0x6c]
	cmp r0, #0
	beq _021E757E
	add r7, r1, #4
	mov r4, #0
	add r5, r7, #0
_021E7540:
	ldr r0, [r5]
	cmp r0, #0
	beq _021E7568
	add r0, r6, #0
	add r0, #0xc4
	ldrh r2, [r5, #4]
	ldrh r3, [r5, #6]
	ldr r0, [r0]
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldrb r1, [r5, #8]
	ldr r0, [r0, #0x6c]
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_0206F190
	add r4, r4, #1
	add r5, #0xc
	cmp r4, #8
	blo _021E7540
_021E7568:
	add r6, #0xc4
	ldr r1, [r6]
	ldr r0, [r1, #0x6c]
	add r1, #0x64
	ldrb r2, [r1]
	mov r1, #0xc
	mul r1, r2
	add r1, r7, r1
	ldrb r1, [r1, #8]
	bl FUN_0206F19C
_021E757E:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD75_021E752C

	thumb_func_start MOD75_021E7580
MOD75_021E7580: ; 0x021E7580
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r2, r0, #4
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r4, r2, r0
	ldrb r1, [r4, #8]
	ldr r0, _021E7718 ; =0x021EC674
	ldrb r0, [r0, r1]
	mov r1, #6
	add r0, r0, #3
	bl FUN_02012838
	mov r1, #0x16
	lsl r1, r1, #4
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	sub r1, #0x4c
	mov r2, #0x20
	add r3, r2, #0
	ldr r1, [r5, r1]
	sub r3, #0x23
	bl FUN_02012880
	ldrb r3, [r4, #8]
	cmp r3, #3
	bne _021E764A
	ldr r0, _021E7718 ; =0x021EC674
	mov r6, #0
	ldrb r0, [r0, r3]
	cmp r0, #0
	bls _021E761A
	str r6, [sp]
	add r7, r5, #0
_021E75CE:
	ldr r0, [r4]
	ldr r2, [sp]
	ldr r1, [sp]
	ldrh r2, [r0, r2]
	add r1, r0, r1
	cmp r2, #0
	beq _021E761A
	ldrh r0, [r1, #2]
	cmp r0, #0
	beq _021E761A
	mov r0, #0x12
	mov r1, #0x59
	lsl r0, r0, #4
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r7, r1]
	mov r3, #6
	bl MOD75_021E7458
	mov r0, #0x16
	mov r1, #0x59
	lsl r0, r0, #4
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r7, r1]
	add r2, r6, #0
	bl FUN_020128A0
	ldr r0, [sp]
	ldrb r1, [r4, #8]
	add r0, r0, #4
	str r0, [sp]
	ldr r0, _021E7718 ; =0x021EC674
	add r6, r6, #1
	ldrb r0, [r0, r1]
	add r7, r7, #4
	cmp r6, r0
	blo _021E75CE
_021E761A:
	mov r1, #0x16
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	sub r1, #0x4c
	mov r2, #0x20
	add r3, r2, #0
	ldr r1, [r5, r1]
	sub r3, #0x22
	bl FUN_02012880
	mov r1, #0x16
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	sub r1, #0x4c
	mov r2, #0x20
	add r3, r2, #0
	ldr r1, [r5, r1]
	sub r3, #0x23
	bl FUN_02012880
	add r0, r6, #3
	add sp, #8
	strb r0, [r4, #9]
	pop {r3, r4, r5, r6, r7, pc}
_021E764A:
	ldr r0, _021E7718 ; =0x021EC674
	mov r6, #0
	ldrb r0, [r0, r3]
	cmp r0, #0
	bls _021E76A4
	str r6, [sp, #4]
	add r7, r5, #0
_021E7658:
	ldr r2, [r4]
	ldr r0, [sp, #4]
	ldr r1, [sp, #4]
	add r0, r2, r0
	ldrh r2, [r2, r1]
	cmp r2, #0
	beq _021E76A4
	ldrh r0, [r0, #2]
	cmp r0, #0
	beq _021E76A4
	mov r0, #0x47
	mov r1, #0x59
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r7, r1]
	mov r3, #6
	bl MOD75_021E7448
	mov r0, #0x16
	mov r1, #0x59
	lsl r0, r0, #4
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r7, r1]
	add r2, r6, #0
	bl FUN_020128A0
	ldr r0, [sp, #4]
	ldrb r3, [r4, #8]
	add r0, r0, #4
	str r0, [sp, #4]
	ldr r0, _021E7718 ; =0x021EC674
	add r6, r6, #1
	ldrb r0, [r0, r3]
	add r7, r7, #4
	cmp r6, r0
	blo _021E7658
_021E76A4:
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #5
	beq _021E76FC
	cmp r3, #4
	bne _021E76CC
	mov r1, #0x16
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	sub r1, #0x4c
	mov r2, #0x20
	add r3, r2, #0
	ldr r1, [r5, r1]
	sub r3, #0x22
	bl FUN_02012880
	b _021E76E0
_021E76CC:
	mov r1, #0x16
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	sub r1, #0x4c
	mov r2, #0x29
	add r3, r2, #0
	ldr r1, [r5, r1]
	sub r3, #0x2b
	bl FUN_02012880
_021E76E0:
	mov r1, #0x16
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	sub r1, #0x4c
	mov r2, #0x20
	add r3, r2, #0
	ldr r1, [r5, r1]
	sub r3, #0x23
	bl FUN_02012880
	add r0, r6, #3
	add sp, #8
	strb r0, [r4, #9]
	pop {r3, r4, r5, r6, r7, pc}
_021E76FC:
	mov r1, #0x16
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	sub r1, #0x4c
	mov r2, #0x20
	add r3, r2, #0
	ldr r1, [r5, r1]
	sub r3, #0x23
	bl FUN_02012880
	add r0, r6, #2
	strb r0, [r4, #9]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E7718: .word MOD75_021EC674
	thumb_func_end MOD75_021E7580

	thumb_func_start MOD75_021E771C
MOD75_021E771C: ; 0x021E771C
	push {r3, r4, r5, r6, r7, lr}
	mov r6, #0x59
	add r5, r0, #0
	mov r4, #0
	mov r7, #0x12
	lsl r6, r6, #2
_021E7728:
	add r0, r7, #0
	mov r1, #6
	bl String_ctor
	str r0, [r5, r6]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xa5
	blo _021E7728
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD75_021E771C

	thumb_func_start MOD75_021E773C
MOD75_021E773C: ; 0x021E773C
	push {r4, r5, r6, lr}
	mov r6, #0x59
	add r5, r0, #0
	mov r4, #0
	lsl r6, r6, #2
_021E7746:
	ldr r0, [r5, r6]
	bl String_dtor
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xa5
	blo _021E7746
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD75_021E773C

	thumb_func_start MOD75_021E7758
MOD75_021E7758: ; 0x021E7758
	push {r4, r5}
	sub r2, r2, #1
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	cmp r2, #8
	bls _021E7768
	mov r5, #7
	b _021E776E
_021E7768:
	sub r3, r2, #1
	lsl r3, r3, #0x18
	lsr r5, r3, #0x18
_021E776E:
	ldrh r3, [r0]
	cmp r3, #0
	beq _021E7780
	sub r4, r2, #1
	add r3, r3, r5
	cmp r3, r4
	ble _021E7780
	sub r3, r4, r5
	strh r3, [r0]
_021E7780:
	ldrh r3, [r0]
	ldrh r0, [r1]
	sub r2, r2, #1
	add r0, r3, r0
	cmp r0, r2
	blt _021E7790
	sub r0, r2, r3
	strh r0, [r1]
_021E7790:
	pop {r4, r5}
	bx lr
	thumb_func_end MOD75_021E7758

	thumb_func_start MOD75_021E7794
MOD75_021E7794: ; 0x021E7794
	push {r3, r4, r5, r6}
	sub r2, r2, #1
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	cmp r2, #8
	bls _021E77A4
	mov r5, #7
	b _021E77AA
_021E77A4:
	sub r4, r2, #1
	lsl r4, r4, #0x18
	lsr r5, r4, #0x18
_021E77AA:
	ldrh r6, [r1]
	asr r4, r3, #1
	add r3, r4, #2
	cmp r6, r3
	blt _021E77E2
	sub r6, r6, r4
	mov r3, #0
	sub r6, r6, #2
	bmi _021E77E2
	sub r2, r2, #1
_021E77BE:
	ldrh r6, [r0]
	add r6, r6, r5
	cmp r2, r6
	beq _021E77E2
	ldrh r6, [r1]
	add r3, r3, #1
	lsl r3, r3, #0x18
	sub r6, r6, #1
	strh r6, [r1]
	ldrh r6, [r0]
	lsr r3, r3, #0x18
	add r6, r6, #1
	strh r6, [r0]
	ldrh r6, [r1]
	sub r6, r6, r4
	sub r6, r6, #2
	cmp r3, r6
	ble _021E77BE
_021E77E2:
	pop {r3, r4, r5, r6}
	bx lr
	.align 2, 0
	thumb_func_end MOD75_021E7794

	thumb_func_start MOD75_021E77E8
MOD75_021E77E8: ; 0x021E77E8
	push {r4, r5, r6, lr}
	sub sp, #0x20
	ldr r6, _021E786C ; =0x021EC504
	add r5, sp, #0
	add r4, r0, #0
	add r3, r1, #0
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	str r0, [sp]
	add r0, r4, #4
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0xc4
	ldr r1, [r0]
	add r0, r1, #0
	add r0, #0x64
	ldrb r5, [r0]
	mov r0, #0xc
	add r6, r5, #0
	mul r6, r0
	add r1, r1, r6
	ldrb r5, [r1, #0xd]
	add r1, sp, #0
	strh r5, [r1, #0x10]
	add r5, r4, #0
	str r4, [sp, #0x1c]
	add r5, #0xc4
	ldr r5, [r5]
	add r6, r5, #0
	add r6, #0x64
	ldrb r6, [r6]
	mul r0, r6
	add r0, r5, r0
	ldrb r0, [r0, #0xc]
	add r0, #0xfd
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #1
	bhi _021E784C
	mov r0, #0x23
	b _021E784E
_021E784C:
	mov r0, #0
_021E784E:
	strb r0, [r1, #0x15]
	add r1, r3, #0
	add r0, sp, #0
	mov r3, #6
	bl FUN_020010A8
	mov r1, #0x57
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #4
	bl FUN_02019220
	add sp, #0x20
	pop {r4, r5, r6, pc}
	nop
_021E786C: .word MOD75_021EC504
	thumb_func_end MOD75_021E77E8

	thumb_func_start MOD75_021E7870
MOD75_021E7870: ; 0x021E7870
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	mov r1, #0x13
	add r4, r2, #0
	bl FUN_02001470
	add r5, r0, #0
	cmp r4, #1
	beq _021E78F8
	ldr r0, _021E7960 ; =0x00000482
	ldrb r0, [r5, r0]
	cmp r0, #0
	beq _021E7890
	cmp r0, #1
	beq _021E7898
	b _021E78A0
_021E7890:
	ldr r0, _021E7964 ; =0x000006CC
	bl FUN_020054C8
	b _021E78A6
_021E7898:
	ldr r0, _021E7968 ; =0x000006CD
	bl FUN_020054C8
	b _021E78A6
_021E78A0:
	ldr r0, _021E796C ; =0x000006CE
	bl FUN_020054C8
_021E78A6:
	ldr r0, _021E7960 ; =0x00000482
	mov r1, #3
	ldrb r0, [r5, r0]
	add r0, r0, #1
	bl _s32_div_f
	ldr r0, _021E7960 ; =0x00000482
	strb r1, [r5, r0]
	add r0, #0x10
	ldrb r0, [r5, r0]
	cmp r0, #0
	beq _021E78CC
	add r0, r5, #0
	add r0, #0xe0
	ldr r0, [r0]
	bl FUN_0200C608
	cmp r0, #0
	bne _021E78F8
_021E78CC:
	add r0, r5, #0
	add r0, #0xe0
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0200C61C
	add r0, r5, #0
	add r0, #0xc4
	ldr r1, [r0]
	add r0, r5, #0
	add r2, r1, #0
	add r2, #0x64
	ldrb r3, [r2]
	mov r2, #0xc
	add r0, #0xe0
	mul r2, r3
	add r1, r1, r2
	ldrb r1, [r1, #0xc]
	ldr r0, [r0]
	add r1, #8
	bl FUN_0200C5C0
_021E78F8:
	ldr r0, _021E7970 ; =0x0000047A
	ldrb r0, [r5, r0]
	cmp r0, #1
	beq _021E795C
	add r0, r5, #0
	add r0, #0x14
	mov r1, #0
	bl FUN_02019620
	mov r1, #1
	mvn r1, r1
	cmp r7, r1
	beq _021E793C
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	lsl r7, r7, #2
	add r4, r0, #4
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	add r6, r1, #0
	mul r6, r0
	ldr r1, [r4, r6]
	add r0, r5, #0
	ldrh r1, [r1, r7]
	bl MOD75_021EAAE8
	ldr r1, [r4, r6]
	add r0, r5, #0
	ldrh r1, [r1, r7]
	bl MOD75_021EC034
	b _021E794C
_021E793C:
	add r0, r5, #0
	lsr r1, r1, #0x10
	bl MOD75_021EAAE8
	ldr r1, _021E7974 ; =0x0000FFFF
	add r0, r5, #0
	bl MOD75_021EC034
_021E794C:
	ldr r0, _021E7978 ; =0x00000479
	ldrb r0, [r5, r0]
	cmp r0, #0
	bne _021E795C
	add r5, #0x14
	add r0, r5, #0
	bl FUN_02019220
_021E795C:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E7960: .word 0x00000482
_021E7964: .word 0x000006CC
_021E7968: .word 0x000006CD
_021E796C: .word 0x000006CE
_021E7970: .word 0x0000047A
_021E7974: .word 0x0000FFFF
_021E7978: .word 0x00000479
	thumb_func_end MOD75_021E7870

	thumb_func_start MOD75_021E797C
MOD75_021E797C: ; 0x021E797C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	mov r1, #0x13
	str r0, [sp]
	add r7, r2, #0
	bl FUN_02001470
	add r4, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r2, r0, #4
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r6, r2, r0
	ldr r0, _021E7A98 ; =0x0000047A
	ldrb r1, [r4, r0]
	cmp r1, #1
	bne _021E79BA
	add r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, r5
	bne _021E79BA
	ldr r0, [sp]
	mov r1, #8
	mov r2, #0
	mov r3, #9
	bl FUN_020013E8
	b _021E79C6
_021E79BA:
	ldr r0, [sp]
	mov r1, #1
	mov r2, #0
	mov r3, #2
	bl FUN_020013E8
_021E79C6:
	ldrb r0, [r6, #8]
	cmp r0, #7
	bne _021E79F8
	mov r0, #2
	mvn r0, r0
	cmp r5, r0
	beq _021E7A94
	add r0, r0, #1
	cmp r5, r0
	beq _021E7A94
	add r0, r4, #0
	add r0, #0xc8
	ldr r0, [r0]
	bl FUN_0206EBC4
	ldr r2, [r6]
	lsl r1, r5, #2
	ldrh r1, [r2, r1]
	cmp r1, r0
	bne _021E7A94
	add r0, r4, #0
	add r1, r7, #0
	bl MOD75_021EB004
	pop {r3, r4, r5, r6, r7, pc}
_021E79F8:
	cmp r0, #3
	bne _021E7A24
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	bne _021E7A0E
	add r0, r4, #0
	add r1, r7, #0
	bl MOD75_021EAFB0
	pop {r3, r4, r5, r6, r7, pc}
_021E7A0E:
	sub r0, r0, #1
	cmp r5, r0
	beq _021E7A94
	ldr r2, [r6]
	lsl r1, r5, #2
	add r1, r2, r1
	add r0, r4, #0
	add r2, r7, #0
	bl MOD75_021EAE90
	pop {r3, r4, r5, r6, r7, pc}
_021E7A24:
	cmp r0, #4
	bne _021E7A50
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	bne _021E7A3A
	add r0, r4, #0
	add r1, r7, #0
	bl MOD75_021EAFB0
	pop {r3, r4, r5, r6, r7, pc}
_021E7A3A:
	sub r0, r0, #1
	cmp r5, r0
	beq _021E7A94
	ldr r2, [r6]
	lsl r1, r5, #2
	add r1, r2, r1
	add r0, r4, #0
	add r2, r7, #0
	bl MOD75_021EAF0C
	pop {r3, r4, r5, r6, r7, pc}
_021E7A50:
	mov r0, #2
	mvn r0, r0
	cmp r5, r0
	beq _021E7A94
	add r0, r0, #1
	cmp r5, r0
	beq _021E7A94
	ldr r0, _021E7A98 ; =0x0000047A
	ldrb r1, [r4, r0]
	cmp r1, #1
	bne _021E7A82
	add r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, r5
	bne _021E7A82
	ldr r2, [r6]
	lsl r1, r5, #2
	add r1, r2, r1
	ldrh r1, [r1, #2]
	ldr r3, _021E7A9C ; =0x00080900
	add r0, r4, #0
	add r2, r7, #0
	bl MOD75_021EADDC
	pop {r3, r4, r5, r6, r7, pc}
_021E7A82:
	ldr r2, [r6]
	lsl r1, r5, #2
	add r1, r2, r1
	ldrh r1, [r1, #2]
	ldr r3, _021E7AA0 ; =0x00010200
	add r0, r4, #0
	add r2, r7, #0
	bl MOD75_021EADDC
_021E7A94:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E7A98: .word 0x0000047A
_021E7A9C: .word 0x00080900
_021E7AA0: .word 0x00010200
	thumb_func_end MOD75_021E797C

	thumb_func_start MOD75_021E7AA4
MOD75_021E7AA4: ; 0x021E7AA4
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xc4
	ldr r3, [r0]
	add r0, r3, #0
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	add r2, r1, #0
	add r1, r3, #0
	mul r2, r0
	mov r0, #0x57
	lsl r0, r0, #2
	add r1, #0xa
	ldr r0, [r4, r0]
	add r3, #8
	add r1, r1, r2
	add r2, r3, r2
	bl FUN_02001300
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_02012870
	mov r0, #0x57
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	pop {r4, pc}
	thumb_func_end MOD75_021E7AA4

	thumb_func_start MOD75_021E7AE0
MOD75_021E7AE0: ; 0x021E7AE0
	push {r4, lr}
	add r4, r0, #0
	bl MOD75_021E86C0
	add r0, r4, #0
	bl MOD75_021EA2D8
	cmp r0, #1
	bne _021E7AF6
	mov r0, #1
	pop {r4, pc}
_021E7AF6:
	add r0, r4, #0
	bl MOD75_021E7D14
	cmp r0, #1
	bne _021E7B04
	mov r0, #2
	pop {r4, pc}
_021E7B04:
	add r0, r4, #0
	bl MOD75_021E8304
	cmp r0, #1
	bne _021E7B12
	mov r0, #2
	pop {r4, pc}
_021E7B12:
	add r0, r4, #0
	bl MOD75_021E7B7C
	cmp r0, #1
	bne _021E7B60
	add r0, r4, #0
	mov r1, #2
	bl MOD75_021EC090
	add r0, r4, #0
	add r0, #0x14
	mov r1, #0
	bl FUN_02019620
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02019570
	add r0, r4, #0
	bl MOD75_021E8B70
	add r0, r4, #0
	add r0, #0xc4
	ldr r2, [r0]
	add r0, r2, #0
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r0, r2, r0
	ldrb r0, [r0, #0xc]
	cmp r0, #3
	bne _021E7B5C
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021E8DAC
_021E7B5C:
	mov r0, #4
	pop {r4, pc}
_021E7B60:
	cmp r0, #2
	bne _021E7B6E
	add r0, r4, #0
	bl MOD75_021E8864
	mov r0, #3
	pop {r4, pc}
_021E7B6E:
	cmp r0, #3
	bne _021E7B76
	mov r0, #0x18
	pop {r4, pc}
_021E7B76:
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD75_021E7AE0

	thumb_func_start MOD75_021E7B7C
MOD75_021E7B7C: ; 0x021E7B7C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r2, r0, #4
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r4, r2, r0
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #6
	add r2, r4, #4
	bl FUN_02001448
	ldr r0, _021E7CD8 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #4
	tst r0, r1
	beq _021E7BC0
	add r0, r5, #0
	bl MOD75_021E8808
	cmp r0, #1
	bne _021E7BC0
	ldr r0, _021E7CDC ; =0x000005DC
	bl FUN_020054C8
	add sp, #4
	mov r0, #2
	pop {r3, r4, r5, r6, pc}
_021E7BC0:
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02001204
	add r6, r0, #0
	mov r0, #0x57
	lsl r0, r0, #2
	add r1, sp, #0
	ldr r0, [r5, r0]
	add r1, #2
	add r2, sp, #0
	bl FUN_02001448
	add r0, sp, #0
	ldrh r2, [r0]
	ldrh r0, [r4, #4]
	cmp r0, r2
	beq _021E7BFC
	sub r2, r2, #1
	add r0, r5, #0
	lsl r2, r2, #4
	add r0, #0xf0
	add r2, #0x18
	lsl r2, r2, #0x10
	ldr r0, [r0]
	mov r1, #0xb1
	asr r2, r2, #0x10
	bl FUN_0200C714
_021E7BFC:
	add r0, sp, #0
	ldrh r1, [r0, #2]
	strh r1, [r4, #6]
	ldrh r0, [r0]
	strh r0, [r4, #4]
	mov r0, #0
	mvn r0, r0
	cmp r6, r0
	bne _021E7C38
	add r0, r5, #0
	bl MOD75_021E87B8
	cmp r0, #1
	bne _021E7C38
	add r1, sp, #0
	ldrh r2, [r1, #2]
	ldrh r1, [r1]
	mov r0, #0x57
	lsl r0, r0, #2
	add r1, r2, r1
	lsl r1, r1, #0x10
	ldr r0, [r5, r0]
	lsr r1, r1, #0x10
	bl FUN_02001464
	add r6, r0, #0
	mov r0, #0x49
	mov r1, #1
	lsl r0, r0, #4
	strb r1, [r5, r0]
_021E7C38:
	mov r0, #1
	mvn r0, r0
	cmp r6, r0
	beq _021E7C6E
	add r0, r0, #1
	cmp r6, r0
	bne _021E7CAC
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0200145C
	cmp r0, #1
	bne _021E7C5E
	add r0, r5, #0
	mov r1, #0x24
	bl MOD75_021EA0CC
	b _021E7CD2
_021E7C5E:
	cmp r0, #2
	bne _021E7CD2
	mov r1, #0x23
	add r0, r5, #0
	mvn r1, r1
	bl MOD75_021EA0CC
	b _021E7CD2
_021E7C6E:
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #5
	bne _021E7C82
	add sp, #4
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_021E7C82:
	ldr r0, _021E7CDC ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #0
	add r0, #0x66
	strh r1, [r0]
	add r5, #0xc4
	ldr r0, [r5]
	mov r1, #5
	add r0, #0x68
	strh r1, [r0]
	mov r0, #1
	mov r1, #6
	bl FUN_02079A70
	add sp, #4
	mov r0, #3
	pop {r3, r4, r5, r6, pc}
_021E7CAC:
	ldr r0, _021E7CDC ; =0x000005DC
	bl FUN_020054C8
	ldr r0, [r4]
	lsl r2, r6, #2
	ldrh r1, [r0, r2]
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	add sp, #4
	add r0, #0x66
	strh r1, [r0]
	ldr r0, [r4]
	add r0, r0, r2
	ldrh r1, [r0, #2]
	ldr r0, _021E7CE0 ; =0x0000048A
	strh r1, [r5, r0]
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021E7CD2:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021E7CD8: .word gMain
_021E7CDC: .word 0x000005DC
_021E7CE0: .word 0x0000048A
	thumb_func_end MOD75_021E7B7C

	thumb_func_start MOD75_021E7CE4
MOD75_021E7CE4: ; 0x021E7CE4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E7D0C ; =0x00000424
	ldrb r2, [r4, r0]
	mov r0, #0xa
	add r1, r2, #0
	mul r1, r0
	mov r0, #0x5a
	sub r0, r0, r1
	add r1, r2, #1
	bl _s32_div_f
	add r1, r0, #6
	ldr r0, _021E7D10 ; =0x00000427
	strb r1, [r4, r0]
	ldrb r1, [r4, r0]
	add r0, r0, #1
	add r1, r1, #4
	strb r1, [r4, r0]
	pop {r4, pc}
	.align 2, 0
_021E7D0C: .word 0x00000424
_021E7D10: .word 0x00000427
	thumb_func_end MOD75_021E7CE4

	thumb_func_start MOD75_021E7D14
MOD75_021E7D14: ; 0x021E7D14
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E7DF8 ; =gMain
	ldr r1, [r0, #0x4c]
	mov r0, #0x20
	tst r0, r1
	beq _021E7D88
	ldr r0, _021E7DFC ; =0x00000424
	ldrb r0, [r4, r0]
	cmp r0, #1
	bne _021E7D2E
	mov r0, #0
	pop {r4, pc}
_021E7D2E:
	ldr r0, _021E7E00 ; =0x000006CA
	bl FUN_020054C8
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r0, #0x64
	ldrb r0, [r0]
	cmp r0, #0
	beq _021E7D58
	ldr r1, _021E7E04 ; =0x00000429
	sub r0, r0, #1
	strb r0, [r4, r1]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, #0x4f
	add r0, #0x64
	ldrb r0, [r0]
	sub r0, r0, #1
	b _021E7D68
_021E7D58:
	ldr r1, _021E7DFC ; =0x00000424
	ldrb r0, [r4, r1]
	sub r2, r0, #1
	add r0, r1, #5
	strb r2, [r4, r0]
	ldrb r0, [r4, r1]
	add r1, #0x54
	sub r0, r0, #1
_021E7D68:
	strb r0, [r4, r1]
	add r0, r4, #0
	bl MOD75_021EC0C4
	ldr r0, _021E7E08 ; =0x0000042A
	mov r1, #0
	strb r1, [r4, r0]
	add r0, r4, #0
	bl MOD75_021E7E0C
	ldr r0, [r4]
	mov r1, #4
	bl FUN_0201AC68
	mov r0, #1
	pop {r4, pc}
_021E7D88:
	mov r0, #0x10
	tst r0, r1
	beq _021E7DF2
	ldr r0, _021E7DFC ; =0x00000424
	ldrb r0, [r4, r0]
	cmp r0, #1
	bne _021E7D9A
	mov r0, #0
	pop {r4, pc}
_021E7D9A:
	ldr r0, _021E7E00 ; =0x000006CA
	bl FUN_020054C8
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	ldr r1, _021E7DFC ; =0x00000424
	add r0, #0x64
	ldrb r0, [r0]
	add r2, r0, #1
	ldrb r0, [r4, r1]
	cmp r2, r0
	bge _021E7DCA
	add r0, r1, #5
	strb r2, [r4, r0]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, #0x54
	add r0, #0x64
	ldrb r0, [r0]
	add r0, r0, #1
	strb r0, [r4, r1]
	b _021E7DD4
_021E7DCA:
	add r0, r1, #5
	mov r2, #0
	strb r2, [r4, r0]
	add r1, #0x54
	strb r2, [r4, r1]
_021E7DD4:
	add r0, r4, #0
	bl MOD75_021EC0C4
	ldr r0, _021E7E08 ; =0x0000042A
	mov r1, #1
	strb r1, [r4, r0]
	add r0, r4, #0
	bl MOD75_021E7E0C
	ldr r0, [r4]
	mov r1, #4
	bl FUN_0201AC68
	mov r0, #1
	pop {r4, pc}
_021E7DF2:
	mov r0, #0
	pop {r4, pc}
	nop
_021E7DF8: .word gMain
_021E7DFC: .word 0x00000424
_021E7E00: .word 0x000006CA
_021E7E04: .word 0x00000429
_021E7E08: .word 0x0000042A
	thumb_func_end MOD75_021E7D14

	thumb_func_start MOD75_021E7E0C
MOD75_021E7E0C: ; 0x021E7E0C
	push {r4, lr}
	add r4, r0, #0
	bl MOD75_021E7E60
	ldr r0, _021E7E28 ; =0x0000042D
	mov r1, #3
	strb r1, [r4, r0]
	add r1, r0, #3
	ldrb r2, [r4, r1]
	mov r1, #0x80
	add r0, r0, #3
	bic r2, r1
	strb r2, [r4, r0]
	pop {r4, pc}
	.align 2, 0
_021E7E28: .word 0x0000042D
	thumb_func_end MOD75_021E7E0C

	thumb_func_start MOD75_021E7E2C
MOD75_021E7E2C: ; 0x021E7E2C
	push {r4, lr}
	ldr r1, _021E7E58 ; =0x0000042A
	add r4, r0, #0
	ldrb r2, [r4, r1]
	cmp r2, #2
	beq _021E7E3E
	bl MOD75_021E7E60
	b _021E7E44
_021E7E3E:
	mov r2, #2
	add r0, r1, #1
	strb r2, [r4, r0]
_021E7E44:
	ldr r0, _021E7E5C ; =0x0000042D
	mov r1, #0
	strb r1, [r4, r0]
	add r1, r0, #3
	ldrb r2, [r4, r1]
	mov r1, #0x80
	add r0, r0, #3
	orr r1, r2
	strb r1, [r4, r0]
	pop {r4, pc}
	.align 2, 0
_021E7E58: .word 0x0000042A
_021E7E5C: .word 0x0000042D
	thumb_func_end MOD75_021E7E2C

	thumb_func_start MOD75_021E7E60
MOD75_021E7E60: ; 0x021E7E60
	push {r4, lr}
	ldr r1, _021E7EE0 ; =0x00000429
	add r4, r0, #0
	add r1, r4, r1
	mov r2, #0
	strb r2, [r1, #2]
	strb r2, [r1, #3]
	strb r2, [r1, #5]
	ldrb r3, [r1, #7]
	mov r2, #0xf
	bic r3, r2
	strb r3, [r1, #7]
	ldrb r3, [r1, #7]
	mov r2, #0x70
	bic r3, r2
	strb r3, [r1, #7]
	bl MOD75_021E7AA4
	add r0, r4, #4
	mov r1, #0
	bl FUN_02019620
	add r0, r4, #0
	add r0, #0x14
	mov r1, #0
	bl FUN_02019620
	add r0, r4, #4
	bl FUN_02019220
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02019220
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0200C644
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0200C644
	add r1, r4, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r0, r4, #0
	add r1, #0x64
	ldrb r1, [r1]
	mov r2, #0
	bl MOD75_021EA96C
	add r0, r4, #0
	add r4, #0xc4
	ldr r1, [r4]
	mov r2, #0
	add r1, #0x64
	ldrb r1, [r1]
	bl MOD75_021E84E4
	pop {r4, pc}
	.align 2, 0
_021E7EE0: .word 0x00000429
	thumb_func_end MOD75_021E7E60

	thumb_func_start MOD75_021E7EE4
MOD75_021E7EE4: ; 0x021E7EE4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _021E8018 ; =0x00000429
	add r4, r5, r0
	bl FUN_02020A98
	cmp r0, #0
	bne _021E7F00
	ldrb r1, [r4, #7]
	mov r0, #0x70
	bic r1, r0
	mov r0, #0x10
	orr r0, r1
	strb r0, [r4, #7]
_021E7F00:
	add r0, r5, #0
	bl MOD75_021E83CC
	add r6, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r6, r0
	beq _021E7F16
	ldrb r0, [r4]
	cmp r6, r0
	beq _021E7F22
_021E7F16:
	ldrb r1, [r4, #7]
	mov r0, #0xf
	bic r1, r0
	mov r0, #1
	orr r0, r1
	strb r0, [r4, #7]
_021E7F22:
	add r0, r5, #0
	bl MOD75_021E8020
	cmp r0, #0
	bne _021E7FB6
	ldrb r0, [r4, #7]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1d
	cmp r0, #1
	bne _021E7FB6
	mov r0, #0
	mvn r0, r0
	cmp r6, r0
	beq _021E7FB6
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	ldrb r1, [r4]
	add r0, #0x64
	strb r1, [r0]
	lsl r0, r6, #0x18
	ldrb r1, [r4]
	lsr r0, r0, #0x18
	cmp r1, r0
	bls _021E7F6E
	mov r2, #0
	strb r2, [r4, #1]
	strb r2, [r4, #2]
	ldrb r1, [r4]
	add r0, r5, #0
	bl MOD75_021E84E4
	ldrb r1, [r4]
	add r0, r5, #0
	mov r2, #0
	bl MOD75_021EA96C
	b _021E7F92
_021E7F6E:
	cmp r1, r0
	bhs _021E7F8E
	mov r0, #1
	strb r0, [r4, #1]
	mov r2, #0
	strb r2, [r4, #2]
	ldrb r1, [r4]
	add r0, r5, #0
	bl MOD75_021E84E4
	ldrb r1, [r4]
	add r0, r5, #0
	mov r2, #0
	bl MOD75_021EA96C
	b _021E7F92
_021E7F8E:
	mov r0, #2
	strb r0, [r4, #1]
_021E7F92:
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	strb r0, [r4]
	ldrb r2, [r4, #7]
	mov r1, #0xf
	bic r2, r1
	strb r2, [r4, #7]
	ldrb r2, [r4, #7]
	mov r1, #0x70
	bic r2, r1
	strb r2, [r4, #7]
	mov r1, #0
	strb r1, [r4, #4]
	ldr r1, _021E801C ; =0x00000478
	strb r0, [r5, r1]
	add r0, r5, #0
	bl MOD75_021EC0C4
_021E7FB6:
	add r0, r5, #0
	bl MOD75_021E819C
	add r6, r0, #0
	add r0, r5, #0
	bl MOD75_021E8424
	add r7, r0, #0
	add r0, r5, #0
	bl MOD75_021EC0DC
	cmp r6, #1
	bne _021E8012
	cmp r7, #1
	bne _021E8012
	ldrb r0, [r4, #7]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r0, #1
	bne _021E8012
	add r0, r5, #0
	bl MOD75_021EC0AC
	cmp r0, #1
	bne _021E8012
	ldrb r0, [r4, #7]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _021E8004
	ldrb r1, [r4]
	add r0, r5, #0
	mov r2, #1
	bl MOD75_021E84E4
	ldr r0, [r5]
	mov r1, #4
	bl FUN_0201AC68
_021E8004:
	add r5, #0xfc
	ldr r0, [r5]
	mov r1, #1
	bl FUN_0200C644
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021E8012:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E8018: .word 0x00000429
_021E801C: .word 0x00000478
	thumb_func_end MOD75_021E7EE4

	thumb_func_start MOD75_021E8020
MOD75_021E8020: ; 0x021E8020
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021E8188 ; =gMain
	ldr r1, _021E818C ; =0x00000429
	ldr r2, [r0, #0x48]
	mov r0, #0x20
	add r4, r5, r1
	tst r0, r2
	beq _021E80D8
	sub r0, r1, #5
	ldrb r0, [r5, r0]
	cmp r0, #1
	bne _021E803E
	mov r0, #1
	pop {r3, r4, r5, pc}
_021E803E:
	ldr r0, _021E8190 ; =0x000006CA
	bl FUN_020054C8
	add r1, r5, #0
	add r1, #0xc4
	ldr r3, [r1]
	add r0, r5, #0
	add r0, #0xe0
	ldrb r2, [r4]
	mov r1, #0xc
	ldr r0, [r0]
	mul r1, r2
	add r1, r3, r1
	ldrb r1, [r1, #0xc]
	bl FUN_0200C5C0
	ldrb r1, [r4]
	add r0, r5, #0
	mov r2, #0
	bl MOD75_021E84E4
	ldr r0, [r5]
	mov r1, #4
	bl FUN_0201AC68
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	ldrb r1, [r4]
	add r0, #0x64
	strb r1, [r0]
	ldrb r0, [r4]
	cmp r0, #0
	beq _021E808E
	sub r0, r0, #1
	strb r0, [r4]
	ldr r0, _021E8194 ; =0x00000478
	ldrb r1, [r5, r0]
	sub r1, r1, #1
	b _021E809C
_021E808E:
	ldr r0, _021E8198 ; =0x00000424
	ldrb r1, [r5, r0]
	sub r1, r1, #1
	strb r1, [r4]
	ldrb r1, [r5, r0]
	add r0, #0x54
	sub r1, r1, #1
_021E809C:
	strb r1, [r5, r0]
	mov r0, #0
	strb r0, [r4, #2]
	strb r0, [r4, #1]
	ldrb r1, [r4, #7]
	mov r0, #0x70
	bic r1, r0
	mov r0, #0x10
	orr r0, r1
	strb r0, [r4, #7]
	ldrb r1, [r4, #7]
	mov r0, #0xf
	bic r1, r0
	mov r0, #1
	orr r0, r1
	strb r0, [r4, #7]
	ldrb r1, [r4, #7]
	mov r0, #0x80
	bic r1, r0
	strb r1, [r4, #7]
	ldrb r0, [r4, #4]
	cmp r0, #3
	beq _021E80CE
	mov r0, #4
	strb r0, [r4, #4]
_021E80CE:
	add r0, r5, #0
	bl MOD75_021EC0C4
	mov r0, #1
	pop {r3, r4, r5, pc}
_021E80D8:
	mov r0, #0x10
	tst r0, r2
	beq _021E8182
	sub r0, r1, #5
	ldrb r0, [r5, r0]
	cmp r0, #1
	bne _021E80EA
	mov r0, #1
	pop {r3, r4, r5, pc}
_021E80EA:
	ldr r0, _021E8190 ; =0x000006CA
	bl FUN_020054C8
	add r1, r5, #0
	add r1, #0xc4
	ldr r3, [r1]
	add r0, r5, #0
	add r0, #0xe0
	ldrb r2, [r4]
	mov r1, #0xc
	ldr r0, [r0]
	mul r1, r2
	add r1, r3, r1
	ldrb r1, [r1, #0xc]
	bl FUN_0200C5C0
	ldrb r1, [r4]
	add r0, r5, #0
	mov r2, #0
	bl MOD75_021E84E4
	ldr r0, [r5]
	mov r1, #4
	bl FUN_0201AC68
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	ldrb r1, [r4]
	add r0, #0x64
	strb r1, [r0]
	ldrb r0, [r4]
	ldr r1, _021E8198 ; =0x00000424
	add r2, r0, #1
	ldrb r0, [r5, r1]
	cmp r2, r0
	bge _021E8140
	add r0, r1, #0
	strb r2, [r4]
	add r0, #0x54
	ldrb r0, [r5, r0]
	add r0, r0, #1
	b _021E8144
_021E8140:
	mov r0, #0
	strb r0, [r4]
_021E8144:
	add r1, #0x54
	strb r0, [r5, r1]
	mov r0, #0
	strb r0, [r4, #2]
	mov r0, #1
	strb r0, [r4, #1]
	ldrb r2, [r4, #7]
	mov r1, #0x70
	bic r2, r1
	mov r1, #0x10
	orr r1, r2
	strb r1, [r4, #7]
	ldrb r2, [r4, #7]
	mov r1, #0xf
	bic r2, r1
	orr r0, r2
	strb r0, [r4, #7]
	ldrb r1, [r4, #7]
	mov r0, #0x80
	bic r1, r0
	strb r1, [r4, #7]
	ldrb r0, [r4, #4]
	cmp r0, #3
	beq _021E8178
	mov r0, #4
	strb r0, [r4, #4]
_021E8178:
	add r0, r5, #0
	bl MOD75_021EC0C4
	mov r0, #1
	pop {r3, r4, r5, pc}
_021E8182:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021E8188: .word gMain
_021E818C: .word 0x00000429
_021E8190: .word 0x000006CA
_021E8194: .word 0x00000478
_021E8198: .word 0x00000424
	thumb_func_end MOD75_021E8020

	thumb_func_start MOD75_021E819C
MOD75_021E819C: ; 0x021E819C
	push {r4, r5, r6, lr}
	ldr r1, _021E8300 ; =0x00000429
	add r5, r0, #0
	add r4, r5, r1
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _021E81B6
	cmp r1, #1
	beq _021E81C2
	cmp r1, #2
	bne _021E81B4
	b _021E82F8
_021E81B4:
	b _021E82FC
_021E81B6:
	mov r0, #0
	strb r0, [r4, #3]
	ldrb r0, [r4, #2]
	add r0, r0, #1
	strb r0, [r4, #2]
	b _021E82FC
_021E81C2:
	ldrb r1, [r4, #3]
	cmp r1, #8
	bhs _021E81D2
	add r1, r1, #1
	strb r1, [r4, #3]
	bl MOD75_021EA8BC
	b _021E82FC
_021E81D2:
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021E8206
	add r1, r5, #0
	add r1, #0xc4
	ldr r3, [r1]
	add r1, r3, #0
	add r1, #0x64
	ldrb r6, [r1]
	mov r1, #0xc
	add r2, r6, #0
	mul r2, r1
	add r1, r3, #0
	add r1, #0xa
	add r3, #8
	add r1, r1, r2
	add r2, r3, r2
	bl FUN_02001300
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_02012870
_021E8206:
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	ldrb r1, [r4]
	add r0, #0x64
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0xc4
	ldr r1, [r0]
	add r0, r5, #0
	add r2, r1, #0
	add r2, #0x64
	ldrb r3, [r2]
	mov r2, #0xc
	add r0, #0xe0
	mul r2, r3
	add r1, r1, r2
	ldrb r1, [r1, #0xc]
	ldr r0, [r0]
	bl FUN_0200C5C0
	add r0, r5, #0
	bl MOD75_021EA9F8
	add r1, r5, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r0, r5, #0
	add r1, #0x64
	ldrb r1, [r1]
	mov r2, #1
	bl MOD75_021EA96C
	add r0, r5, #0
	bl MOD75_021E7580
	add r0, r5, #0
	add r0, #0xc4
	ldr r3, [r0]
	add r0, r3, #0
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	add r2, r1, #0
	mul r2, r0
	add r0, r3, #0
	add r1, r3, #0
	add r0, #0xa
	add r1, #8
	add r0, r0, r2
	add r1, r1, r2
	add r2, r3, r2
	ldrb r2, [r2, #0xd]
	bl MOD75_021E7758
	add r0, r5, #0
	add r0, #0xc4
	ldr r3, [r0]
	add r0, r3, #0
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	add r2, r1, #0
	mul r2, r0
	add r0, r3, #0
	add r1, r3, #0
	add r0, #0xa
	add r1, #8
	add r0, r0, r2
	add r1, r1, r2
	add r2, r3, r2
	ldrb r2, [r2, #0xd]
	mov r3, #9
	bl MOD75_021E7794
	add r0, r5, #0
	add r0, #0xc4
	ldr r1, [r0]
	add r0, r1, #0
	add r0, #0x64
	ldrb r2, [r0]
	mov r0, #0xc
	add r3, r2, #0
	mul r3, r0
	add r2, r1, r3
	ldrh r1, [r2, #0xa]
	ldrh r2, [r2, #8]
	add r0, r5, #0
	bl MOD75_021E77E8
	add r0, r5, #0
	add r0, #0xc4
	ldr r2, [r0]
	add r0, r5, #0
	add r3, r2, #0
	add r3, #0x64
	ldrb r6, [r3]
	mov r3, #0xc
	add r0, #0xf0
	mul r3, r6
	add r2, r2, r3
	ldrh r2, [r2, #8]
	ldr r0, [r0]
	mov r1, #0xb1
	sub r2, r2, #1
	lsl r2, r2, #4
	add r2, #0x18
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	add r5, #0xf0
	ldr r0, [r5]
	mov r1, #1
	bl FUN_0200C644
	ldrb r0, [r4, #2]
	add r0, r0, #1
	strb r0, [r4, #2]
	mov r0, #1
	pop {r4, r5, r6, pc}
_021E82F8:
	mov r0, #1
	pop {r4, r5, r6, pc}
_021E82FC:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_021E8300: .word 0x00000429
	thumb_func_end MOD75_021E819C

	thumb_func_start MOD75_021E8304
MOD75_021E8304: ; 0x021E8304
	push {r4, lr}
	add r4, r0, #0
	bl MOD75_021E8374
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _021E8318
	mov r0, #0
	pop {r4, pc}
_021E8318:
	ldr r2, _021E836C ; =0x00000424
	ldrb r1, [r4, r2]
	cmp r1, #1
	bne _021E8324
	mov r0, #0
	pop {r4, pc}
_021E8324:
	add r1, r4, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r1, #0x64
	ldrb r3, [r1]
	lsl r1, r0, #0x18
	lsr r1, r1, #0x18
	cmp r3, r1
	bne _021E833E
	mov r3, #2
	add r1, r2, #6
	strb r3, [r4, r1]
	b _021E8350
_021E833E:
	cmp r3, r1
	bls _021E834A
	mov r3, #0
	add r1, r2, #6
	strb r3, [r4, r1]
	b _021E8350
_021E834A:
	mov r3, #1
	add r1, r2, #6
	strb r3, [r4, r1]
_021E8350:
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldr r0, _021E8370 ; =0x00000429
	strb r1, [r4, r0]
	add r0, #0x4f
	strb r1, [r4, r0]
	add r0, r4, #0
	bl MOD75_021EC0C4
	add r0, r4, #0
	bl MOD75_021E7E2C
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_021E836C: .word 0x00000424
_021E8370: .word 0x00000429
	thumb_func_end MOD75_021E8304

	thumb_func_start MOD75_021E8374
MOD75_021E8374: ; 0x021E8374
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, _021E83BC ; =0x00000424
	ldrb r0, [r5, r0]
	lsl r1, r0, #3
	ldr r0, _021E83C0 ; =0x021EC628
	ldr r0, [r0, r1]
	bl FUN_02020988
	add r4, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	beq _021E83B6
	ldr r1, _021E83C4 ; =0x0000FFFE
	add r0, sp, #4
	strh r1, [r0]
	add r0, sp, #4
	str r0, [sp]
	ldr r3, _021E83C8 ; =UNK_021C48F8
	ldr r0, [r5]
	ldrh r2, [r3, #0x1c]
	ldrh r3, [r3, #0x1e]
	mov r1, #4
	bl FUN_0201AFBC
	cmp r0, #0
	bne _021E83B6
	mov r0, #0
	add sp, #8
	mvn r0, r0
	pop {r3, r4, r5, pc}
_021E83B6:
	add r0, r4, #0
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_021E83BC: .word 0x00000424
_021E83C0: .word MOD75_021EC628
_021E83C4: .word 0x0000FFFE
_021E83C8: .word UNK_021C48F8
	thumb_func_end MOD75_021E8374

	thumb_func_start MOD75_021E83CC
MOD75_021E83CC: ; 0x021E83CC
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, _021E8414 ; =0x00000424
	ldrb r0, [r5, r0]
	lsl r1, r0, #3
	ldr r0, _021E8418 ; =0x021EC628
	ldr r0, [r0, r1]
	bl FUN_02020968
	add r4, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	beq _021E840E
	ldr r1, _021E841C ; =0x0000FFFE
	add r0, sp, #4
	strh r1, [r0]
	add r0, sp, #4
	str r0, [sp]
	ldr r3, _021E8420 ; =UNK_021C48F8
	ldr r0, [r5]
	ldrh r2, [r3, #0x1c]
	ldrh r3, [r3, #0x1e]
	mov r1, #4
	bl FUN_0201AFBC
	cmp r0, #0
	bne _021E840E
	mov r0, #0
	add sp, #8
	mvn r0, r0
	pop {r3, r4, r5, pc}
_021E840E:
	add r0, r4, #0
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_021E8414: .word 0x00000424
_021E8418: .word MOD75_021EC628
_021E841C: .word 0x0000FFFE
_021E8420: .word UNK_021C48F8
	thumb_func_end MOD75_021E83CC

	thumb_func_start MOD75_021E8424
MOD75_021E8424: ; 0x021E8424
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021E84D4 ; =0x00000429
	add r4, r5, r0
	ldrb r0, [r4, #4]
	cmp r0, #4
	bhi _021E84CA
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E843E: ; jump table
	.short _021E8448 - _021E843E - 2 ; case 0
	.short _021E8460 - _021E843E - 2 ; case 1
	.short _021E84B0 - _021E843E - 2 ; case 2
	.short _021E84BE - _021E843E - 2 ; case 3
	.short _021E84C2 - _021E843E - 2 ; case 4
_021E8448:
	mov r0, #0
	strb r0, [r4, #5]
	ldrb r1, [r4, #7]
	mov r0, #0x80
	orr r0, r1
	strb r0, [r4, #7]
	ldrb r0, [r4]
	strb r0, [r4, #6]
	ldrb r0, [r4, #4]
	add r0, r0, #1
	strb r0, [r4, #4]
	b _021E84CA
_021E8460:
	ldrb r0, [r4, #5]
	cmp r0, #3
	bne _021E84CA
	ldr r0, _021E84D8 ; =0x000005E4
	bl FUN_020054C8
	ldrb r1, [r4, #6]
	add r0, r5, #0
	mov r2, #2
	bl MOD75_021E84E4
	ldr r0, [r5]
	mov r1, #4
	bl FUN_0201AC68
	ldrb r0, [r4, #6]
	lsl r3, r0, #1
	ldr r0, _021E84DC ; =0x00000424
	ldrb r0, [r5, r0]
	lsl r1, r0, #3
	ldr r0, _021E84E0 ; =0x021EC624
	ldr r2, [r0, r1]
	add r0, r5, #0
	ldrb r1, [r2, r3]
	add r3, r3, #1
	ldrb r2, [r2, r3]
	lsl r1, r1, #3
	add r1, #0x14
	lsl r2, r2, #3
	add r2, #0x14
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl MOD75_021EC380
	ldrb r0, [r4, #4]
	add r0, r0, #1
	strb r0, [r4, #4]
	b _021E84CA
_021E84B0:
	ldrb r1, [r4, #5]
	cmp r1, #7
	bne _021E84CA
	add r0, r0, #1
	strb r0, [r4, #4]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021E84BE:
	mov r0, #1
	pop {r3, r4, r5, pc}
_021E84C2:
	mov r0, #3
	strb r0, [r4, #4]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021E84CA:
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021E84D4: .word 0x00000429
_021E84D8: .word 0x000005E4
_021E84DC: .word 0x00000424
_021E84E0: .word MOD75_021EC624
	thumb_func_end MOD75_021E8424

	thumb_func_start MOD75_021E84E4
MOD75_021E84E4: ; 0x021E84E4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldr r0, [r4]
	add r5, r1, #0
	mov r1, #4
	add r6, r2, #0
	bl FUN_0201886C
	add r7, r0, #0
	ldr r0, _021E856C ; =0x00000424
	ldrb r0, [r4, r0]
	add r4, #0xc4
	lsl r1, r0, #3
	ldr r0, _021E8570 ; =0x021EC624
	ldr r1, [r0, r1]
	lsl r0, r5, #1
	add r2, r1, r0
	ldr r1, [r4]
	mov r0, #0xc
	mul r0, r5
	add r0, r1, r0
	ldrb r3, [r0, #0xc]
	lsl r0, r6, #2
	add r1, r6, r0
	lsr r5, r3, #1
	mov r0, #0x96
	mul r0, r5
	mov r5, #1
	and r5, r3
	mov r3, #0xf
	mul r3, r5
	add r0, r0, r3
	add r0, #0x1e
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r4, #0
	mov ip, r0
_021E8530:
	mov r0, #0x1e
	add r1, r4, #0
	mul r1, r0
	mov r0, ip
	mov r3, #0
	add r5, r0, r1
_021E853C:
	ldrb r6, [r2, #1]
	mov r0, #2
	add r1, r3, r5
	lsl r0, r0, #0xc
	add r1, r1, r0
	add r6, r4, r6
	lsl r6, r6, #5
	ldrb r0, [r2]
	add r6, r3, r6
	add r0, r0, r6
	lsl r0, r0, #1
	strh r1, [r7, r0]
	add r0, r3, #1
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	cmp r3, #5
	blo _021E853C
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #5
	blo _021E8530
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E856C: .word 0x00000424
_021E8570: .word MOD75_021EC624
	thumb_func_end MOD75_021E84E4

	thumb_func_start MOD75_021E8574
MOD75_021E8574: ; 0x021E8574
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	add r4, r1, #0
	ldr r0, [r0]
	mov r1, #4
	bl FUN_0201886C
	mov ip, r0
	add r1, r4, #0
	mov r0, #6
	mul r1, r0
	ldr r0, _021E85D4 ; =0x00000276
	mov r4, #3
	add r0, r1, r0
	lsl r0, r0, #0x10
	mov r6, #0
	lsr r7, r0, #0x10
	lsl r4, r4, #0xc
_021E8598:
	mov r0, #0x1e
	mul r0, r6
	add r2, r7, r0
	add r0, r6, #7
	lsl r3, r0, #6
	mov r0, ip
	mov r1, #0
	add r3, r0, r3
_021E85A8:
	add r0, r1, r2
	lsl r5, r1, #1
	add r0, r0, r4
	add r5, r3, r5
	strh r0, [r5, #0x1a]
	add r0, r1, #1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	cmp r1, #6
	blo _021E85A8
	add r0, r6, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #6
	blo _021E8598
	ldr r0, [sp]
	mov r1, #4
	ldr r0, [r0]
	bl FUN_0201AC68
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E85D4: .word 0x00000276
	thumb_func_end MOD75_021E8574

	thumb_func_start MOD75_021E85D8
MOD75_021E85D8: ; 0x021E85D8
	push {r4, lr}
	mov r1, #0x49
	add r4, r0, #0
	lsl r1, r1, #4
	ldrb r2, [r4, r1]
	cmp r2, #3
	bhi _021E8674
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021E85F2: ; jump table
	.short _021E8674 - _021E85F2 - 2 ; case 0
	.short _021E85FA - _021E85F2 - 2 ; case 1
	.short _021E8622 - _021E85F2 - 2 ; case 2
	.short _021E864E - _021E85F2 - 2 ; case 3
_021E85FA:
	mov r1, #0x80
	mov r2, #0x50
	bl MOD75_021EC380
	ldr r0, _021E8678 ; =0x000005E4
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #2
	bl MOD75_021E8574
	ldr r0, _021E867C ; =0x00000491
	mov r1, #0
	strb r1, [r4, r0]
	sub r1, r0, #1
	ldrb r1, [r4, r1]
	sub r0, r0, #1
	add r1, r1, #1
	strb r1, [r4, r0]
	pop {r4, pc}
_021E8622:
	add r2, r1, #1
	ldrb r2, [r4, r2]
	cmp r2, #3
	bne _021E8642
	mov r1, #1
	bl MOD75_021E8574
	mov r0, #0x49
	lsl r0, r0, #4
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	mov r1, #0
	add r0, r0, #1
	strb r1, [r4, r0]
	pop {r4, pc}
_021E8642:
	add r0, r1, #1
	ldrb r0, [r4, r0]
	add r2, r0, #1
	add r0, r1, #1
	strb r2, [r4, r0]
	pop {r4, pc}
_021E864E:
	add r2, r1, #1
	ldrb r2, [r4, r2]
	cmp r2, #2
	bne _021E866A
	mov r1, #0
	bl MOD75_021E8574
	mov r0, #0x49
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r4, r0]
	add r0, r0, #1
	strb r1, [r4, r0]
	pop {r4, pc}
_021E866A:
	add r0, r1, #1
	ldrb r0, [r4, r0]
	add r2, r0, #1
	add r0, r1, #1
	strb r2, [r4, r0]
_021E8674:
	pop {r4, pc}
	nop
_021E8678: .word 0x000005E4
_021E867C: .word 0x00000491
	thumb_func_end MOD75_021E85D8

	thumb_func_start MOD75_021E8680
MOD75_021E8680: ; 0x021E8680
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0
	add r5, r0, #0
	bl MOD75_021E8574
	ldr r0, _021E86BC ; =0x00000424
	ldrb r0, [r5, r0]
	cmp r0, #1
	beq _021E86B2
	mov r4, #0
	cmp r0, #0
	bls _021E86B2
	ldr r6, _021E86BC ; =0x00000424
	add r7, r4, #0
_021E869C:
	add r0, r5, #0
	add r1, r4, #0
	add r2, r7, #0
	bl MOD75_021E84E4
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldrb r0, [r5, r6]
	cmp r4, r0
	blo _021E869C
_021E86B2:
	ldr r0, [r5]
	mov r1, #4
	bl FUN_0201AC68
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021E86BC: .word 0x00000424
	thumb_func_end MOD75_021E8680

	thumb_func_start MOD75_021E86C0
MOD75_021E86C0: ; 0x021E86C0
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, _021E87B4 ; =0x00000481
	ldrb r1, [r4, r0]
	cmp r1, #0
	bne _021E87A2
	sub r0, r0, #1
	ldrb r0, [r4, r0]
	cmp r0, #3
	bhi _021E8794
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E86E2: ; jump table
	.short _021E86EA - _021E86E2 - 2 ; case 0
	.short _021E86EA - _021E86E2 - 2 ; case 1
	.short _021E8740 - _021E86E2 - 2 ; case 2
	.short _021E8740 - _021E86E2 - 2 ; case 3
_021E86EA:
	add r0, r4, #0
	add r0, #0xe8
	add r1, sp, #0
	ldr r0, [r0]
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	add r3, sp, #0
	mov r1, #2
	ldrsh r0, [r3, r1]
	mov r2, #0
	sub r0, r0, #1
	strh r0, [r3, #2]
	add r0, r4, #0
	add r0, #0xe8
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldr r0, [r0]
	bl FUN_0200C714
	add r0, r4, #0
	add r0, #0xec
	add r1, sp, #0
	ldr r0, [r0]
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	add r3, sp, #0
	mov r1, #2
	ldrsh r0, [r3, r1]
	mov r2, #0
	add r0, r0, #1
	strh r0, [r3, #2]
	add r0, r4, #0
	add r0, #0xec
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldr r0, [r0]
	bl FUN_0200C714
	b _021E8794
_021E8740:
	add r0, r4, #0
	add r0, #0xe8
	add r1, sp, #0
	ldr r0, [r0]
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	add r3, sp, #0
	mov r1, #2
	ldrsh r0, [r3, r1]
	mov r2, #0
	add r0, r0, #1
	strh r0, [r3, #2]
	add r0, r4, #0
	add r0, #0xe8
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldr r0, [r0]
	bl FUN_0200C714
	add r0, r4, #0
	add r0, #0xec
	add r1, sp, #0
	ldr r0, [r0]
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	add r3, sp, #0
	mov r1, #2
	ldrsh r0, [r3, r1]
	mov r2, #0
	sub r0, r0, #1
	strh r0, [r3, #2]
	add r0, r4, #0
	add r0, #0xec
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldr r0, [r0]
	bl FUN_0200C714
_021E8794:
	mov r1, #0x12
	lsl r1, r1, #6
	ldrb r0, [r4, r1]
	add r2, r0, #1
	mov r0, #3
	and r0, r2
	strb r0, [r4, r1]
_021E87A2:
	ldr r1, _021E87B4 ; =0x00000481
	ldrb r0, [r4, r1]
	add r2, r0, #1
	mov r0, #3
	and r0, r2
	strb r0, [r4, r1]
	add sp, #4
	pop {r3, r4, pc}
	nop
_021E87B4: .word 0x00000481
	thumb_func_end MOD75_021E86C0

	thumb_func_start MOD75_021E87B8
MOD75_021E87B8: ; 0x021E87B8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, _021E87FC ; =0x021EC3F4
	bl FUN_02020988
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _021E87F4
	ldr r1, _021E8800 ; =0x0000FFFE
	add r0, sp, #4
	strh r1, [r0]
	add r0, sp, #4
	str r0, [sp]
	ldr r3, _021E8804 ; =UNK_021C48F8
	ldr r0, [r4]
	ldrh r2, [r3, #0x1c]
	ldrh r3, [r3, #0x1e]
	mov r1, #4
	bl FUN_0201AFBC
	cmp r0, #0
	beq _021E87EE
	add sp, #8
	mov r0, #1
	pop {r4, pc}
_021E87EE:
	add sp, #8
	mov r0, #0
	pop {r4, pc}
_021E87F4:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	nop
_021E87FC: .word MOD75_021EC3F4
_021E8800: .word 0x0000FFFE
_021E8804: .word UNK_021C48F8
	thumb_func_end MOD75_021E87B8

	thumb_func_start MOD75_021E8808
MOD75_021E8808: ; 0x021E8808
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r2, r0, #4
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r4, r2, r0
	mov r0, #0x57
	lsl r0, r0, #2
	ldrh r2, [r4, #6]
	ldrh r1, [r4, #4]
	ldr r0, [r5, r0]
	add r1, r2, r1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_02001464
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	bne _021E883C
	mov r0, #0
	pop {r3, r4, r5, pc}
_021E883C:
	add r5, #0xc4
	ldr r0, [r5]
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #0
	beq _021E884C
	mov r0, #0
	pop {r3, r4, r5, pc}
_021E884C:
	ldrb r0, [r4, #8]
	add r0, #0xfd
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #1
	bls _021E885C
	mov r0, #1
	b _021E885E
_021E885C:
	mov r0, #0
_021E885E:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
	thumb_func_end MOD75_021E8808

	thumb_func_start MOD75_021E8864
MOD75_021E8864: ; 0x021E8864
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r2, r0, #4
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r3, r2, r0
	ldr r1, _021E88B4 ; =0x0000047A
	mov r0, #1
	strb r0, [r4, r1]
	ldrh r2, [r3, #6]
	ldrh r0, [r3, #4]
	add r2, r2, r0
	add r0, r1, #1
	strb r2, [r4, r0]
	mov r0, #0x57
	add r1, r1, #1
	lsl r0, r0, #2
	ldrb r1, [r4, r1]
	ldr r0, [r4, r0]
	bl FUN_02001464
	ldr r1, _021E88B8 ; =0x0000047C
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD75_021EB3D8
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02001328
	add r0, r4, #0
	bl MOD75_021E8AAC
	pop {r4, pc}
	nop
_021E88B4: .word 0x0000047A
_021E88B8: .word 0x0000047C
	thumb_func_end MOD75_021E8864

	thumb_func_start MOD75_021E88BC
MOD75_021E88BC: ; 0x021E88BC
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	bl MOD75_021EA3F4
	cmp r0, #1
	bne _021E88D0
	add sp, #4
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_021E88D0:
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r2, r0, #4
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r4, r2, r0
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #6
	add r2, r4, #4
	bl FUN_02001448
	add r0, r5, #0
	bl MOD75_021E87B8
	cmp r0, #1
	bne _021E8912
	ldr r0, _021E89E8 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	bl MOD75_021E89F0
	mov r1, #0x49
	mov r0, #1
	lsl r1, r1, #4
	add sp, #4
	strb r0, [r5, r1]
	pop {r3, r4, r5, r6, pc}
_021E8912:
	ldr r0, _021E89EC ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #4
	tst r0, r1
	beq _021E892E
	ldr r0, _021E89E8 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	bl MOD75_021E89F0
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021E892E:
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02001204
	add r6, r0, #0
	mov r0, #0x57
	lsl r0, r0, #2
	add r1, sp, #0
	ldr r0, [r5, r0]
	add r1, #2
	add r2, sp, #0
	bl FUN_02001448
	add r0, sp, #0
	ldrh r2, [r0]
	ldrh r0, [r4, #4]
	cmp r0, r2
	beq _021E896A
	sub r2, r2, #1
	add r0, r5, #0
	lsl r2, r2, #4
	add r0, #0xf4
	add r2, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r0]
	mov r1, #0xb1
	asr r2, r2, #0x10
	bl FUN_0200C714
_021E896A:
	add r0, sp, #0
	ldrh r1, [r0, #2]
	strh r1, [r4, #6]
	ldrh r0, [r0]
	strh r0, [r4, #4]
	mov r0, #1
	mvn r0, r0
	cmp r6, r0
	beq _021E89AA
	add r0, r0, #1
	cmp r6, r0
	bne _021E89CE
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0200145C
	cmp r0, #1
	bne _021E899A
	add r0, r5, #0
	mov r1, #0x24
	bl MOD75_021EA0CC
	b _021E89E0
_021E899A:
	cmp r0, #2
	bne _021E89E0
	mov r1, #0x23
	add r0, r5, #0
	mvn r1, r1
	bl MOD75_021EA0CC
	b _021E89E0
_021E89AA:
	ldr r0, _021E89E8 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _021E89EC ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _021E89C2
	add r0, r5, #0
	bl MOD75_021E89F0
	b _021E89C8
_021E89C2:
	add r0, r5, #0
	bl MOD75_021E8A48
_021E89C8:
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021E89CE:
	ldr r0, _021E89E8 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	bl MOD75_021E89F0
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021E89E0:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_021E89E8: .word 0x000005DC
_021E89EC: .word gMain
	thumb_func_end MOD75_021E88BC

	thumb_func_start MOD75_021E89F0
MOD75_021E89F0: ; 0x021E89F0
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r2, r0, #4
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r0, r2, r0
	ldrh r2, [r0, #6]
	ldrh r1, [r0, #4]
	add r1, r2, r1
	lsl r1, r1, #0x10
	lsr r2, r1, #0x10
	ldr r1, _021E8A44 ; =0x0000047B
	ldrb r1, [r4, r1]
	cmp r1, r2
	beq _021E8A3C
	sub r2, r2, #1
	cmp r1, r2
	beq _021E8A3C
	sub r1, r1, #1
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r0]
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	bl MoveItemSlotInList
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_02012870
	add r0, r4, #0
	bl MOD75_021E7580
_021E8A3C:
	add r0, r4, #0
	bl MOD75_021E8A48
	pop {r4, pc}
	.align 2, 0
_021E8A44: .word 0x0000047B
	thumb_func_end MOD75_021E89F0

	thumb_func_start MOD75_021E8A48
MOD75_021E8A48: ; 0x021E8A48
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r2, r0, #4
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r4, r2, r0
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #6
	add r2, r4, #4
	bl FUN_02001300
	mov r0, #0x57
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
	ldr r0, _021E8AA4 ; =0x0000047B
	ldrh r1, [r4, #6]
	ldrb r2, [r5, r0]
	ldrh r0, [r4, #4]
	add r1, r1, r0
	cmp r2, r1
	bge _021E8A84
	sub r0, r0, #1
	strh r0, [r4, #4]
_021E8A84:
	ldr r0, _021E8AA8 ; =0x0000047A
	mov r2, #0
	strb r2, [r5, r0]
	add r1, r0, #1
	strb r2, [r5, r1]
	add r0, r0, #2
	str r2, [r5, r0]
	ldrh r1, [r4, #6]
	ldrh r2, [r4, #4]
	add r0, r5, #0
	bl MOD75_021E77E8
	add r0, r5, #0
	bl MOD75_021E8AAC
	pop {r3, r4, r5, pc}
	.align 2, 0
_021E8AA4: .word 0x0000047B
_021E8AA8: .word 0x0000047A
	thumb_func_end MOD75_021E8A48

	thumb_func_start MOD75_021E8AAC
MOD75_021E8AAC: ; 0x021E8AAC
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r2, r0, #4
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r2, r2, r0
	ldr r0, _021E8B68 ; =0x0000047A
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _021E8B18
	ldrh r2, [r2, #4]
	add r0, r4, #0
	add r0, #0xf0
	sub r2, r2, #1
	lsl r2, r2, #4
	add r2, #0x18
	lsl r2, r2, #0x10
	ldr r0, [r0]
	mov r1, #0xb1
	asr r2, r2, #0x10
	bl FUN_0200C714
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	mov r1, #1
	bl FUN_0200C644
	add r0, r4, #0
	add r0, #0xf4
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, _021E8B6C ; =0x00000424
	ldrb r0, [r4, r0]
	cmp r0, #1
	beq _021E8B66
	add r0, r4, #0
	add r0, #0xe8
	ldr r0, [r0]
	mov r1, #1
	bl FUN_0200C644
	add r4, #0xec
	ldr r0, [r4]
	mov r1, #1
	bl FUN_0200C644
	pop {r4, pc}
_021E8B18:
	ldrh r2, [r2, #4]
	add r0, r4, #0
	add r0, #0xf4
	sub r2, r2, #1
	lsl r2, r2, #4
	add r2, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r0]
	mov r1, #0xb1
	asr r2, r2, #0x10
	bl FUN_0200C714
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0200C644
	add r0, r4, #0
	add r0, #0xf4
	ldr r0, [r0]
	mov r1, #1
	bl FUN_0200C644
	ldr r0, _021E8B6C ; =0x00000424
	ldrb r0, [r4, r0]
	cmp r0, #1
	beq _021E8B66
	add r0, r4, #0
	add r0, #0xe8
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0200C644
	add r4, #0xec
	ldr r0, [r4]
	mov r1, #0
	bl FUN_0200C644
_021E8B66:
	pop {r4, pc}
	.align 2, 0
_021E8B68: .word 0x0000047A
_021E8B6C: .word 0x00000424
	thumb_func_end MOD75_021E8AAC

	thumb_func_start MOD75_021E8B70
MOD75_021E8B70: ; 0x021E8B70
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #0
	add r0, #0x66
	ldrh r0, [r0]
	mov r2, #6
	bl LoadItemDataOrGfx
	add r7, r0, #0
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r4, #0
	add r1, r0, #0
	add r1, #0x64
	ldrb r2, [r1]
	mov r1, #0xc
	mul r1, r2
	add r1, r0, r1
	add r0, #0x65
	ldrb r0, [r0]
	ldrb r6, [r1, #0xc]
	cmp r0, #0
	beq _021E8BA8
	b _021E8CB6
_021E8BA8:
	cmp r6, #4
	bne _021E8BB4
	mov r1, #9
	add r0, sp, #0
	strb r1, [r0]
	add r4, r4, #1
_021E8BB4:
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, r0, #0
	add r1, #0x76
	ldrh r1, [r1]
	lsl r1, r1, #0x10
	lsr r2, r1, #0x11
	ldr r1, _021E8CE8 ; =0x0000FFFE
	add r1, r2, r1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	cmp r1, #1
	bhi _021E8BEC
	add r1, r0, #0
	add r1, #0x64
	ldrb r2, [r1]
	mov r1, #0xc
	mul r1, r2
	add r0, r0, r1
	ldrb r0, [r0, #0xc]
	cmp r0, #5
	bne _021E8C66
	mov r1, #2
	add r0, sp, #0
	strb r1, [r0, r4]
	add r4, r4, #1
	b _021E8C66
_021E8BEC:
	add r0, r7, #0
	mov r1, #6
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0
	beq _021E8C66
	add r0, r5, #0
	add r0, #0xc4
	ldr r1, [r0]
	ldr r2, _021E8CEC ; =0x000001C2
	add r0, r1, #0
	add r0, #0x66
	ldrh r0, [r0]
	cmp r0, r2
	bne _021E8C20
	add r2, r1, #0
	add r2, #0x76
	ldrh r2, [r2]
	lsl r2, r2, #0x1f
	lsr r2, r2, #0x1f
	cmp r2, #1
	bne _021E8C20
	mov r1, #1
	add r0, sp, #0
	strb r1, [r0, r4]
	b _021E8C64
_021E8C20:
	add r2, r1, #0
	add r2, #0x64
	ldrb r3, [r2]
	mov r2, #0xc
	mul r2, r3
	add r2, r1, r2
	ldrb r3, [r2, #0xc]
	cmp r3, #5
	bne _021E8C3A
	mov r1, #2
	add r0, sp, #0
	strb r1, [r0, r4]
	b _021E8C64
_021E8C3A:
	ldr r2, _021E8CF0 ; =0x000001C1
	cmp r0, r2
	bne _021E8C48
	mov r1, #4
	add r0, sp, #0
	strb r1, [r0, r4]
	b _021E8C64
_021E8C48:
	cmp r3, #4
	bne _021E8C5E
	ldr r0, [r1, #0x70]
	bl FUN_0205D51C
	cmp r0, #1
	bne _021E8C5E
	mov r1, #3
	add r0, sp, #0
	strb r1, [r0, r4]
	b _021E8C64
_021E8C5E:
	mov r1, #0
	add r0, sp, #0
	strb r1, [r0, r4]
_021E8C64:
	add r4, r4, #1
_021E8C66:
	add r0, r7, #0
	mov r1, #3
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0
	bne _021E8C84
	mov r0, #8
	add r1, sp, #0
	strb r0, [r1, r4]
	add r4, r4, #1
	cmp r6, #3
	beq _021E8C84
	mov r0, #5
	strb r0, [r1, r4]
	add r4, r4, #1
_021E8C84:
	add r0, r7, #0
	mov r1, #4
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0
	beq _021E8CCC
	add r0, r5, #0
	add r0, #0xc8
	ldr r0, [r0]
	bl FUN_0206EBC4
	add r1, r5, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r1, #0x66
	ldrh r1, [r1]
	cmp r1, r0
	bne _021E8CAC
	mov r1, #7
	b _021E8CAE
_021E8CAC:
	mov r1, #6
_021E8CAE:
	add r0, sp, #0
	strb r1, [r0, r4]
	add r4, r4, #1
	b _021E8CCC
_021E8CB6:
	add r0, #0xfc
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #1
	bhi _021E8CCC
	mov r1, #0xa
	add r0, sp, #0
	strb r1, [r0]
	mov r1, #9
	strb r1, [r0, #1]
	add r4, r4, #2
_021E8CCC:
	add r2, r4, #1
	lsl r2, r2, #0x18
	mov r0, #0xb
	add r1, sp, #0
	strb r0, [r1, r4]
	add r0, r5, #0
	lsr r2, r2, #0x18
	bl MOD75_021EB130
	add r0, r7, #0
	bl FreeToHeap
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021E8CE8: .word 0x0000FFFE
_021E8CEC: .word 0x000001C2
_021E8CF0: .word 0x000001C1
	thumb_func_end MOD75_021E8B70

	thumb_func_start MOD75_021E8CF4
MOD75_021E8CF4: ; 0x021E8CF4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD75_021EA510
	cmp r0, #1
	bne _021E8D04
	mov r0, #4
	pop {r3, r4, r5, pc}
_021E8D04:
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02001C78
	add r4, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _021E8D38
	add r0, r5, #0
	bl MOD75_021E87B8
	cmp r0, #1
	bne _021E8D38
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02001DDC
	add r4, r0, #0
	mov r0, #0x49
	mov r1, #1
	lsl r0, r0, #4
	strb r1, [r5, r0]
_021E8D38:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _021E8D6E
	add r0, r0, #1
	cmp r4, r0
	bne _021E8DA0
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02001E60
	cmp r0, #1
	bne _021E8D5E
	add r0, r5, #0
	mov r1, #0x12
	bl MOD75_021EA0CC
	b _021E8DA6
_021E8D5E:
	cmp r0, #2
	bne _021E8DA6
	mov r1, #0x11
	add r0, r5, #0
	mvn r1, r1
	bl MOD75_021EA0CC
	b _021E8DA6
_021E8D6E:
	add r0, r5, #0
	mov r1, #1
	bl MOD75_021EC090
	add r0, r5, #0
	bl MOD75_021EB344
	add r0, r5, #0
	add r0, #0xc4
	ldr r2, [r0]
	add r0, r2, #0
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r0, r2, r0
	ldrb r0, [r0, #0xc]
	cmp r0, #3
	bne _021E8D9C
	add r0, r5, #0
	mov r1, #0
	bl MOD75_021E8DAC
_021E8D9C:
	mov r0, #1
	pop {r3, r4, r5, pc}
_021E8DA0:
	add r0, r5, #0
	blx r4
	pop {r3, r4, r5, pc}
_021E8DA6:
	mov r0, #4
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD75_021E8CF4

	thumb_func_start MOD75_021E8DAC
MOD75_021E8DAC: ; 0x021E8DAC
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	cmp r1, #0
	bne _021E8DDA
	mov r0, #0x12
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	ldr r2, _021E8E08 ; =0x021EC5C0
	mov r1, #1
	mov r3, #0
	bl FUN_02018148
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #1
	bl FUN_0200C644
	b _021E8DFC
_021E8DDA:
	mov r0, #0x12
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	ldr r2, _021E8E0C ; =0x021EC5F2
	mov r1, #1
	mov r3, #0
	bl FUN_02018148
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0200C644
_021E8DFC:
	ldr r0, [r4]
	mov r1, #1
	bl FUN_0201AC68
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_021E8E08: .word MOD75_021EC5C0
_021E8E0C: .word MOD75_021EC5F2
	thumb_func_end MOD75_021E8DAC

	thumb_func_start MOD75_021E8E10
MOD75_021E8E10: ; 0x021E8E10
	lsl r1, r0, #2
	ldr r0, _021E8E18 ; =0x021EC590
	ldr r0, [r0, r1]
	bx lr
	.align 2, 0
_021E8E18: .word MOD75_021EC590
	thumb_func_end MOD75_021E8E10

	thumb_func_start MOD75_021E8E1C
MOD75_021E8E1C: ; 0x021E8E1C
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	bl MOD75_021EB344
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #6
	add r0, #0x66
	ldrh r0, [r0]
	add r2, r1, #0
	bl GetItemAttr
	add r1, r0, #0
	lsl r1, r1, #0x10
	mov r0, #2
	lsr r1, r1, #0x10
	bl FUN_0205CE48
	add r1, r0, #0
	beq _021E8E9C
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	ldr r0, [r0, #0x70]
	blx r1
	add r3, r0, #0
	beq _021E8E9C
	mov r0, #6
	add r2, r4, #0
	str r0, [sp]
	add r2, #0xc4
	ldr r2, [r2]
	add r0, r4, #0
	mov r1, #0xfe
	add r2, #0x66
	add r0, #0xcc
	lsl r1, r1, #2
	ldrh r2, [r2]
	ldr r0, [r0]
	ldr r1, [r4, r1]
	bl FUN_0206E51C
	add r0, r4, #0
	add r0, #0x64
	mov r1, #0xf
	bl FUN_02019620
	add r0, r4, #0
	ldr r2, _021E8EA8 ; =0x000003D9
	add r0, #0x64
	mov r1, #0
	mov r3, #0xc
	bl FUN_0200D0BC
	add r0, r4, #0
	bl MOD75_021EB660
	ldr r1, _021E8EAC ; =0x00000426
	add sp, #4
	strb r0, [r4, r1]
	mov r0, #0xc
	pop {r3, r4, pc}
_021E8E9C:
	add r0, r4, #0
	bl MOD75_021E8F10
	add sp, #4
	pop {r3, r4, pc}
	nop
_021E8EA8: .word 0x000003D9
_021E8EAC: .word 0x00000426
	thumb_func_end MOD75_021E8E1C

	thumb_func_start MOD75_021E8EB0
MOD75_021E8EB0: ; 0x021E8EB0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E8F04 ; =0x00000426
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0
	bne _021E8F00
	ldr r0, _021E8F08 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	bne _021E8ED2
	ldr r0, _021E8F0C ; =UNK_021C48F8
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	beq _021E8F00
_021E8ED2:
	add r0, r4, #0
	add r0, #0x64
	mov r1, #0
	bl FUN_0200D0E0
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02019220
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021EC090
	add r4, #0xc4
	ldr r0, [r4]
	add r0, #0x65
	ldrb r0, [r0]
	cmp r0, #3
	bne _021E8EFC
	mov r0, #0x17
	pop {r4, pc}
_021E8EFC:
	mov r0, #1
	pop {r4, pc}
_021E8F00:
	mov r0, #0xc
	pop {r4, pc}
	.align 2, 0
_021E8F04: .word 0x00000426
_021E8F08: .word gMain
_021E8F0C: .word UNK_021C48F8
	thumb_func_end MOD75_021E8EB0

	thumb_func_start MOD75_021E8F10
MOD75_021E8F10: ; 0x021E8F10
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r2, r0, #4
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r2, r2, r0
	ldr r1, _021E8FB0 ; =0x00000483
	mov r0, #0
	strb r0, [r4, r1]
	ldrb r0, [r2, #8]
	cmp r0, #3
	bne _021E8F3A
	ldr r2, _021E8FB4 ; =MOD75_021E8FD8
	add r0, r1, #1
	str r2, [r4, r0]
	mov r0, #0xd
	pop {r4, pc}
_021E8F3A:
	add r0, r4, #0
	add r0, #0xc4
	ldr r2, [r0]
	sub r1, #0x8b
	ldr r0, [r2]
	add r2, #0x66
	ldrh r2, [r2]
	ldr r1, [r4, r1]
	mov r3, #6
	bl FUN_0206E3F8
	cmp r0, #1
	bne _021E8F7A
	add r0, r4, #0
	add r0, #0x64
	mov r1, #0xf
	bl FUN_02019620
	add r0, r4, #0
	ldr r2, _021E8FB8 ; =0x000003D9
	add r0, #0x64
	mov r1, #0
	mov r3, #0xc
	bl FUN_0200D0BC
	add r0, r4, #0
	bl MOD75_021EB660
	ldr r1, _021E8FBC ; =0x00000426
	strb r0, [r4, r1]
	mov r0, #0xc
	pop {r4, pc}
_021E8F7A:
	add r1, r4, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r0, r4, #0
	add r1, #0x66
	ldrh r1, [r1]
	bl MOD75_021E91B8
	cmp r0, #1
	bne _021E8F98
	ldr r1, _021E8FC0 ; =MOD75_021E9394
	ldr r0, _021E8FC4 ; =0x00000484
	str r1, [r4, r0]
	mov r0, #0xd
	pop {r4, pc}
_021E8F98:
	mov r0, #1
	mov r1, #6
	bl FUN_02079A70
	add r4, #0xc4
	ldr r0, [r4]
	mov r1, #0
	add r0, #0x68
	strh r1, [r0]
	mov r0, #0x18
	pop {r4, pc}
	nop
_021E8FB0: .word 0x00000483
_021E8FB4: .word MOD75_021E8FD8
_021E8FB8: .word 0x000003D9
_021E8FBC: .word 0x00000426
_021E8FC0: .word MOD75_021E9394
_021E8FC4: .word 0x00000484
	thumb_func_end MOD75_021E8F10

	thumb_func_start MOD75_021E8FC8
MOD75_021E8FC8: ; 0x021E8FC8
	push {r3, lr}
	ldr r1, _021E8FD4 ; =0x00000484
	ldr r1, [r0, r1]
	blx r1
	pop {r3, pc}
	nop
_021E8FD4: .word 0x00000484
	thumb_func_end MOD75_021E8FC8

	thumb_func_start MOD75_021E8FD8
MOD75_021E8FD8: ; 0x021E8FD8
	push {r3, r4, r5, lr}
	ldr r1, _021E91A4 ; =0x00000483
	add r4, r0, #0
	ldrb r2, [r4, r1]
	cmp r2, #3
	bls _021E8FE6
	b _021E91A0
_021E8FE6:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021E8FF2: ; jump table
	.short _021E8FFA - _021E8FF2 - 2 ; case 0
	.short _021E9070 - _021E8FF2 - 2 ; case 1
	.short _021E90D0 - _021E8FF2 - 2 ; case 2
	.short _021E90EA - _021E8FF2 - 2 ; case 3
_021E8FFA:
	add r0, #0xc4
	ldr r0, [r0]
	add r0, #0x66
	ldrh r0, [r0]
	bl TMHMGetMove
	add r5, r0, #0
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	add r2, r5, #0
	bl FUN_0200AD5C
	add r0, r5, #0
	bl MoveIsHM
	cmp r0, #1
	bne _021E9034
	mov r0, #0x45
	mov r2, #0xfe
	lsl r0, r0, #2
	lsl r2, r2, #2
	ldr r0, [r4, r0]
	ldr r2, [r4, r2]
	mov r1, #0x3b
	bl ReadMsgDataIntoString
	b _021E9046
_021E9034:
	mov r0, #0x45
	mov r2, #0xfe
	lsl r0, r0, #2
	lsl r2, r2, #2
	ldr r0, [r4, r0]
	ldr r2, [r4, r2]
	mov r1, #0x3a
	bl ReadMsgDataIntoString
_021E9046:
	add r0, r4, #0
	add r0, #0x64
	mov r1, #0xf
	bl FUN_02019620
	add r0, r4, #0
	ldr r2, _021E91A8 ; =0x000003D9
	add r0, #0x64
	mov r1, #0
	mov r3, #0xc
	bl FUN_0200D0BC
	add r0, r4, #0
	bl MOD75_021EB660
	ldr r1, _021E91AC ; =0x00000426
	strb r0, [r4, r1]
	mov r0, #1
	add r1, #0x5d
	strb r0, [r4, r1]
	b _021E91A0
_021E9070:
	sub r1, #0x5d
	ldrb r0, [r4, r1]
	bl FUN_0201BD70
	cmp r0, #0
	bne _021E9132
	ldr r0, _021E91B0 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	bne _021E908E
	ldr r0, _021E91B4 ; =UNK_021C48F8
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	beq _021E9132
_021E908E:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x3c
	bl NewString_ReadMsgData
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x64
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	add r2, r5, #0
	bl StringExpandPlaceholders
	add r0, r5, #0
	bl String_dtor
	add r0, r4, #0
	bl MOD75_021EB660
	ldr r1, _021E91AC ; =0x00000426
	strb r0, [r4, r1]
	mov r0, #2
	add r1, #0x5d
	strb r0, [r4, r1]
	b _021E91A0
_021E90D0:
	sub r1, #0x5d
	ldrb r0, [r4, r1]
	bl FUN_0201BD70
	cmp r0, #0
	bne _021E91A0
	add r0, r4, #0
	bl MOD75_021EB6E0
	ldr r0, _021E91A4 ; =0x00000483
	mov r1, #3
	strb r1, [r4, r0]
	b _021E91A0
_021E90EA:
	bl MOD75_021EA510
	cmp r0, #1
	beq _021E91A0
	add r0, r4, #0
	bl MOD75_021E87B8
	cmp r0, #1
	bne _021E9114
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	mov r2, #6
	bl FUN_020021CC
	mov r1, #0x49
	mov r2, #1
	lsl r1, r1, #4
	strb r2, [r4, r1]
	b _021E9120
_021E9114:
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl FUN_020021AC
_021E9120:
	cmp r0, #0
	beq _021E9134
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _021E917A
	add r1, r1, #1
	cmp r0, r1
	beq _021E9152
_021E9132:
	b _021E91A0
_021E9134:
	mov r0, #1
	mov r1, #6
	bl FUN_02079A70
	add r0, r4, #0
	mov r1, #0
	bl MOD75_021E8DAC
	add r4, #0xc4
	ldr r0, [r4]
	mov r1, #0
	add r0, #0x68
	strh r1, [r0]
	mov r0, #0x18
	pop {r3, r4, r5, pc}
_021E9152:
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02001E60
	cmp r0, #1
	bne _021E916A
	add r0, r4, #0
	mov r1, #0x12
	bl MOD75_021EA0CC
	b _021E91A0
_021E916A:
	cmp r0, #2
	bne _021E91A0
	mov r1, #0x11
	add r0, r4, #0
	mvn r1, r1
	bl MOD75_021EA0CC
	b _021E91A0
_021E917A:
	add r0, r4, #0
	add r0, #0x64
	mov r1, #0
	bl FUN_0200D0E0
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02019220
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021EC090
	add r0, r4, #0
	mov r1, #0
	bl MOD75_021E8DAC
	mov r0, #1
	pop {r3, r4, r5, pc}
_021E91A0:
	mov r0, #0xd
	pop {r3, r4, r5, pc}
	.align 2, 0
_021E91A4: .word 0x00000483
_021E91A8: .word 0x000003D9
_021E91AC: .word 0x00000426
_021E91B0: .word gMain
_021E91B4: .word UNK_021C48F8
	thumb_func_end MOD75_021E8FD8

	thumb_func_start MOD75_021E91B8
MOD75_021E91B8: ; 0x021E91B8
	push {r3, r4, r5, lr}
	add r4, r0, #0
	mov r0, #0x46
	add r2, r4, #0
	lsl r0, r0, #2
	add r2, #0xcc
	add r5, r1, #0
	ldr r0, [r4, r0]
	ldr r2, [r2]
	mov r1, #0
	bl FUN_0200ABC0
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	add r2, r5, #0
	bl FUN_0200AE38
	cmp r5, #0x44
	bne _021E9200
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x40
	bl NewString_ReadMsgData
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021E6FFC
	ldr r0, _021E925C ; =0x00000488
	mov r1, #0
	strh r1, [r4, r0]
	b _021E923E
_021E9200:
	cmp r5, #0x45
	bne _021E9222
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x3f
	bl NewString_ReadMsgData
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #2
	bl MOD75_021E6FFC
	ldr r0, _021E925C ; =0x00000488
	mov r1, #0
	strh r1, [r4, r0]
	b _021E923E
_021E9222:
	cmp r5, #0x4d
	beq _021E922E
	cmp r5, #0x4c
	beq _021E922E
	cmp r5, #0x4f
	bne _021E923A
_021E922E:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD75_021E9260
	add r5, r0, #0
	b _021E923E
_021E923A:
	mov r0, #0
	pop {r3, r4, r5, pc}
_021E923E:
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	add r2, r5, #0
	bl StringExpandPlaceholders
	add r0, r5, #0
	bl String_dtor
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_021E925C: .word 0x00000488
	thumb_func_end MOD75_021E91B8

	thumb_func_start MOD75_021E9260
MOD75_021E9260: ; 0x021E9260
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r5, r1, #0
	bl MOD75_021E6FDC
	bl FUN_0202AB54
	cmp r0, #0
	bne _021E9286
	ldr r0, _021E92B8 ; =0x00000488
	mov r1, #0
	strh r1, [r4, r0]
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x3e
	bl NewString_ReadMsgData
	pop {r3, r4, r5, pc}
_021E9286:
	add r0, r5, #0
	mov r1, #2
	mov r2, #6
	bl GetItemAttr
	add r1, r0, #0
	lsl r1, r1, #0x18
	add r0, r4, #0
	lsr r1, r1, #0x18
	bl MOD75_021E6FEC
	ldr r0, _021E92B8 ; =0x00000488
	mov r1, #1
	strh r1, [r4, r0]
	mov r0, #6
	lsl r0, r0, #8
	bl FUN_020054C8
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x3d
	bl NewString_ReadMsgData
	pop {r3, r4, r5, pc}
	.align 2, 0
_021E92B8: .word 0x00000488
	thumb_func_end MOD75_021E9260

	thumb_func_start MOD75_021E92BC
MOD75_021E92BC: ; 0x021E92BC
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	add r0, #0xc4
	ldr r2, [r0]
	add r0, r2, #0
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	add r3, r1, #0
	mul r3, r0
	add r1, r2, r3
	mov r0, #6
	str r0, [sp]
	ldr r3, _021E9390 ; =0x00000488
	ldr r0, [r1, #4]
	ldrb r1, [r1, #0xd]
	add r2, #0x66
	ldrh r2, [r2]
	ldrh r3, [r4, r3]
	sub r1, r1, #3
	bl FUN_0206EE20
	add r0, r4, #0
	add r0, #0xc4
	ldr r3, [r0]
	add r0, r3, #0
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	add r2, r1, #0
	add r1, r3, #0
	mul r2, r0
	mov r0, #0x57
	lsl r0, r0, #2
	add r1, #0xa
	ldr r0, [r4, r0]
	add r3, #8
	add r1, r1, r2
	add r2, r3, r2
	bl FUN_02001300
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_02012870
	add r0, r4, #0
	bl MOD75_021E7580
	add r0, r4, #0
	add r0, #0xc4
	ldr r3, [r0]
	add r0, r3, #0
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	add r2, r1, #0
	mul r2, r0
	add r0, r3, #0
	add r1, r3, #0
	add r0, #0xa
	add r1, #8
	add r0, r0, r2
	add r1, r1, r2
	add r2, r3, r2
	ldrb r2, [r2, #0xd]
	bl MOD75_021E7758
	add r0, r4, #0
	add r0, #0xc4
	ldr r3, [r0]
	add r0, r3, #0
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	add r2, r1, #0
	mul r2, r0
	add r0, r3, #0
	add r1, r3, #0
	add r0, #0xa
	add r1, #8
	add r0, r0, r2
	add r1, r1, r2
	add r2, r3, r2
	ldrb r2, [r2, #0xd]
	mov r3, #9
	bl MOD75_021E7794
	add r0, r4, #0
	add r0, #0xc4
	ldr r3, [r0]
	add r0, r3, #0
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	add r2, r1, #0
	mul r2, r0
	add r2, r3, r2
	ldrh r1, [r2, #0xa]
	ldrh r2, [r2, #8]
	add r0, r4, #0
	bl MOD75_021E77E8
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_021E9390: .word 0x00000488
	thumb_func_end MOD75_021E92BC

	thumb_func_start MOD75_021E9394
MOD75_021E9394: ; 0x021E9394
	push {r4, lr}
	ldr r1, _021E9428 ; =0x00000483
	add r4, r0, #0
	ldrb r2, [r4, r1]
	cmp r2, #0
	beq _021E93AA
	cmp r2, #1
	beq _021E93D2
	cmp r2, #2
	beq _021E9402
	b _021E9422
_021E93AA:
	add r0, #0x64
	mov r1, #0xf
	bl FUN_02019620
	add r0, r4, #0
	ldr r2, _021E942C ; =0x000003D9
	add r0, #0x64
	mov r1, #0
	mov r3, #0xc
	bl FUN_0200D0BC
	add r0, r4, #0
	bl MOD75_021EB660
	ldr r1, _021E9430 ; =0x00000426
	strb r0, [r4, r1]
	mov r0, #1
	add r1, #0x5d
	strb r0, [r4, r1]
	b _021E9422
_021E93D2:
	sub r1, #0x5d
	ldrb r0, [r4, r1]
	bl FUN_0201BD70
	cmp r0, #0
	bne _021E9422
	ldr r0, _021E9434 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	bne _021E93F0
	ldr r0, _021E9438 ; =UNK_021C48F8
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	beq _021E9422
_021E93F0:
	add r0, r4, #0
	add r0, #0x64
	mov r1, #0
	bl FUN_0200D0E0
	ldr r0, _021E9428 ; =0x00000483
	mov r1, #2
	strb r1, [r4, r0]
	b _021E9422
_021E9402:
	add r1, r1, #5
	ldrsh r1, [r4, r1]
	cmp r1, #0
	beq _021E940E
	bl MOD75_021E92BC
_021E940E:
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02019220
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021EC090
	mov r0, #1
	pop {r4, pc}
_021E9422:
	mov r0, #0xd
	pop {r4, pc}
	nop
_021E9428: .word 0x00000483
_021E942C: .word 0x000003D9
_021E9430: .word 0x00000426
_021E9434: .word gMain
_021E9438: .word UNK_021C48F8
	thumb_func_end MOD75_021E9394

	thumb_func_start MOD75_021E943C
MOD75_021E943C: ; 0x021E943C
	push {r4, lr}
	add r4, r0, #0
	bl MOD75_021EB344
	mov r0, #1
	mov r1, #6
	bl FUN_02079A70
	add r4, #0xc4
	ldr r0, [r4]
	mov r1, #1
	add r0, #0x68
	strh r1, [r0]
	mov r0, #0x18
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD75_021E943C

	thumb_func_start MOD75_021E945C
MOD75_021E945C: ; 0x021E945C
	push {r4, lr}
	add r4, r0, #0
	bl MOD75_021EB344
	mov r0, #1
	mov r1, #6
	bl FUN_02079A70
	add r4, #0xc4
	ldr r0, [r4]
	mov r1, #3
	add r0, #0x68
	strh r1, [r0]
	mov r0, #0x18
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD75_021E945C

	thumb_func_start MOD75_021E947C
MOD75_021E947C: ; 0x021E947C
	push {r4, lr}
	add r4, r0, #0
	bl MOD75_021EB344
	ldr r0, _021E94CC ; =0x00000488
	mov r1, #1
	strh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xc4
	ldr r2, [r0]
	mov r3, #6
	add r0, r2, #0
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r1, r2, r0
	ldr r0, [r1, #4]
	ldrb r1, [r1, #0xd]
	add r2, #0x66
	ldrh r2, [r2]
	sub r1, r1, #3
	bl FUN_0206EF10
	cmp r0, #1
	bne _021E94BA
	add r0, r4, #0
	bl MOD75_021EB5B0
	mov r0, #8
	pop {r4, pc}
_021E94BA:
	add r0, r4, #0
	bl MOD75_021EB454
	add r0, r4, #0
	mov r1, #0
	bl MOD75_021EC24C
	mov r0, #7
	pop {r4, pc}
	.align 2, 0
_021E94CC: .word 0x00000488
	thumb_func_end MOD75_021E947C

	thumb_func_start MOD75_021E94D0
MOD75_021E94D0: ; 0x021E94D0
	push {r4, lr}
	ldr r2, _021E95AC ; =0x00000488
	add r4, r0, #0
	add r1, r4, r2
	add r2, r2, #2
	ldrh r2, [r4, r2]
	bl MOD75_021EA594
	cmp r0, #1
	bne _021E94EE
	add r0, r4, #0
	bl MOD75_021EB504
	mov r0, #7
	pop {r4, pc}
_021E94EE:
	add r0, r4, #0
	bl MOD75_021E87B8
	cmp r0, #1
	bne _021E9512
	add r0, r4, #0
	bl MOD75_021EB5B0
	add r0, r4, #0
	mov r1, #0
	bl MOD75_021EC298
	mov r0, #0x49
	mov r1, #1
	lsl r0, r0, #4
	strb r1, [r4, r0]
	mov r0, #8
	pop {r4, pc}
_021E9512:
	ldr r1, _021E95AC ; =0x00000488
	add r0, r4, r1
	add r1, r1, #2
	ldrh r1, [r4, r1]
	bl FUN_02079AAC
	cmp r0, #0
	beq _021E955E
	cmp r0, #1
	beq _021E952C
	cmp r0, #2
	beq _021E9544
	b _021E955E
_021E952C:
	add r0, r4, #0
	mov r1, #0x12
	bl MOD75_021EA0CC
	add r0, r4, #0
	bl MOD75_021EB504
	ldr r0, _021E95B0 ; =0x00000638
	bl FUN_020054C8
	mov r0, #7
	pop {r4, pc}
_021E9544:
	mov r1, #0x11
	add r0, r4, #0
	mvn r1, r1
	bl MOD75_021EA0CC
	add r0, r4, #0
	bl MOD75_021EB504
	ldr r0, _021E95B0 ; =0x00000638
	bl FUN_020054C8
	mov r0, #7
	pop {r4, pc}
_021E955E:
	ldr r0, _021E95B4 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _021E9580
	add r0, r4, #0
	bl MOD75_021EB5B0
	add r0, r4, #0
	mov r1, #0
	bl MOD75_021EC298
	ldr r0, _021E95B8 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #8
	pop {r4, pc}
_021E9580:
	mov r0, #2
	tst r0, r1
	beq _021E95A6
	add r0, r4, #0
	bl MOD75_021EB580
	add r0, r4, #0
	mov r1, #0
	bl MOD75_021EC298
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021EC090
	ldr r0, _021E95B8 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #1
	pop {r4, pc}
_021E95A6:
	mov r0, #7
	pop {r4, pc}
	nop
_021E95AC: .word 0x00000488
_021E95B0: .word 0x00000638
_021E95B4: .word gMain
_021E95B8: .word 0x000005DC
	thumb_func_end MOD75_021E94D0

	thumb_func_start MOD75_021E95BC
MOD75_021E95BC: ; 0x021E95BC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E95DC ; =0x00000426
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0
	bne _021E95D6
	add r0, r4, #0
	bl MOD75_021EB6E0
	mov r0, #9
	pop {r4, pc}
_021E95D6:
	mov r0, #8
	pop {r4, pc}
	nop
_021E95DC: .word 0x00000426
	thumb_func_end MOD75_021E95BC

	thumb_func_start MOD75_021E95E0
MOD75_021E95E0: ; 0x021E95E0
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	bl MOD75_021EA510
	cmp r0, #1
	bne _021E95F4
	add sp, #8
	mov r0, #9
	pop {r3, r4, r5, pc}
_021E95F4:
	add r0, r5, #0
	bl MOD75_021E87B8
	cmp r0, #1
	bne _021E9616
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	mov r2, #6
	bl FUN_020021CC
	mov r1, #0x49
	mov r2, #1
	lsl r1, r1, #4
	strb r2, [r5, r1]
	b _021E9622
_021E9616:
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #6
	bl FUN_020021AC
_021E9622:
	cmp r0, #0
	beq _021E9636
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _021E96EC
	add r1, r1, #1
	cmp r0, r1
	beq _021E96C4
	b _021E970C
_021E9636:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x35
	bl NewString_ReadMsgData
	add r4, r0, #0
	ldr r0, _021E9714 ; =0x00000488
	ldrsh r0, [r5, r0]
	cmp r0, #1
	bne _021E9664
	add r2, r5, #0
	add r2, #0xc4
	ldr r2, [r2]
	mov r0, #0x46
	add r2, #0x66
	lsl r0, r0, #2
	ldrh r2, [r2]
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_0200AE38
	b _021E967A
_021E9664:
	add r2, r5, #0
	add r2, #0xc4
	ldr r2, [r2]
	mov r0, #0x46
	add r2, #0x66
	lsl r0, r0, #2
	ldrh r2, [r2]
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_0200AEA8
_021E967A:
	mov r0, #0
	str r0, [sp]
	mov r1, #1
	mov r0, #0x46
	ldr r2, _021E9714 ; =0x00000488
	str r1, [sp, #4]
	lsl r0, r0, #2
	ldrsh r2, [r5, r2]
	ldr r0, [r5, r0]
	mov r3, #3
	bl FUN_0200AD38
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	add r0, #0x64
	mov r1, #0xf
	bl FUN_02019620
	add r0, r5, #0
	bl MOD75_021EB660
	ldr r1, _021E9718 ; =0x00000426
	add sp, #8
	strb r0, [r5, r1]
	mov r0, #0xa
	pop {r3, r4, r5, pc}
_021E96C4:
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02001E60
	cmp r0, #1
	bne _021E96DC
	add r0, r5, #0
	mov r1, #0x12
	bl MOD75_021EA0CC
	b _021E970C
_021E96DC:
	cmp r0, #2
	bne _021E970C
	mov r1, #0x11
	add r0, r5, #0
	mvn r1, r1
	bl MOD75_021EA0CC
	b _021E970C
_021E96EC:
	add r0, r5, #0
	add r0, #0x64
	mov r1, #0
	bl FUN_0200D0E0
	add r0, r5, #0
	add r0, #0x14
	bl FUN_02019220
	add r0, r5, #0
	mov r1, #1
	bl MOD75_021EC090
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, pc}
_021E970C:
	mov r0, #9
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_021E9714: .word 0x00000488
_021E9718: .word 0x00000426
	thumb_func_end MOD75_021E95E0

	thumb_func_start MOD75_021E971C
MOD75_021E971C: ; 0x021E971C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E9748 ; =0x00000426
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0
	beq _021E9730
	mov r0, #0xa
	pop {r4, pc}
_021E9730:
	ldr r0, _021E974C ; =0x00000479
	mov r1, #1
	strb r1, [r4, r0]
	add r0, r4, #0
	bl MOD75_021E92BC
	add r4, #0x64
	add r0, r4, #0
	bl FUN_02019220
	mov r0, #0xb
	pop {r4, pc}
	.align 2, 0
_021E9748: .word 0x00000426
_021E974C: .word 0x00000479
	thumb_func_end MOD75_021E971C

	thumb_func_start MOD75_021E9750
MOD75_021E9750: ; 0x021E9750
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E9798 ; =0x00000426
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0
	bne _021E9794
	ldr r0, _021E979C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	bne _021E9772
	ldr r0, _021E97A0 ; =UNK_021C48F8
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	beq _021E9794
_021E9772:
	ldr r0, _021E97A4 ; =0x00000479
	mov r1, #0
	strb r1, [r4, r0]
	add r0, r4, #0
	add r0, #0x64
	bl FUN_0200D0E0
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02019220
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021EC090
	mov r0, #1
	pop {r4, pc}
_021E9794:
	mov r0, #0xb
	pop {r4, pc}
	.align 2, 0
_021E9798: .word 0x00000426
_021E979C: .word gMain
_021E97A0: .word UNK_021C48F8
_021E97A4: .word 0x00000479
	thumb_func_end MOD75_021E9750

	thumb_func_start MOD75_021E97A8
MOD75_021E97A8: ; 0x021E97A8
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r0, #0xc8
	add r1, #0x66
	ldrh r1, [r1]
	ldr r0, [r0]
	bl FUN_0206EBCC
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02001328
	add r0, r4, #0
	bl MOD75_021EB344
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02019220
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021EC090
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD75_021E97A8

	thumb_func_start MOD75_021E97E4
MOD75_021E97E4: ; 0x021E97E4
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xc8
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0206EBCC
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02001328
	add r0, r4, #0
	bl MOD75_021EB344
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02019220
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021EC090
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD75_021E97E4

	thumb_func_start MOD75_021E9818
MOD75_021E9818: ; 0x021E9818
	push {r4, lr}
	add r4, r0, #0
	bl MOD75_021EB344
	mov r0, #1
	mov r1, #6
	bl FUN_02079A70
	add r0, r4, #0
	mov r1, #0
	bl MOD75_021E8DAC
	add r4, #0xc4
	ldr r0, [r4]
	mov r1, #2
	add r0, #0x68
	strh r1, [r0]
	mov r0, #0x18
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD75_021E9818

	thumb_func_start MOD75_021E9840
MOD75_021E9840: ; 0x021E9840
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD75_021E86C0
	add r0, r5, #0
	bl MOD75_021EA2D8
	cmp r0, #1
	bne _021E9856
	mov r0, #0xe
	pop {r3, r4, r5, pc}
_021E9856:
	add r0, r5, #0
	bl MOD75_021E7D14
	cmp r0, #1
	bne _021E9864
	mov r0, #2
	pop {r3, r4, r5, pc}
_021E9864:
	add r0, r5, #0
	bl MOD75_021E8304
	cmp r0, #1
	bne _021E9872
	mov r0, #2
	pop {r3, r4, r5, pc}
_021E9872:
	add r0, r5, #0
	bl MOD75_021E7B7C
	cmp r0, #1
	bne _021E9912
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #3
	add r0, #0x66
	ldrh r0, [r0]
	mov r2, #6
	bl GetItemAttr
	cmp r0, #0
	beq _021E98FC
	add r0, r5, #0
	add r0, #0x64
	mov r1, #0xf
	bl FUN_02019620
	add r0, r5, #0
	ldr r2, _021E9928 ; =0x000003D9
	add r0, #0x64
	mov r1, #0
	mov r3, #0xc
	bl FUN_0200D0BC
	add r2, r5, #0
	add r2, #0xc4
	ldr r2, [r2]
	mov r0, #0x46
	add r2, #0x66
	lsl r0, r0, #2
	ldrh r2, [r2]
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_0200AE38
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x2e
	bl NewString_ReadMsgData
	add r4, r0, #0
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	bl MOD75_021EB660
	ldr r1, _021E992C ; =0x00000426
	strb r0, [r5, r1]
	add r0, r5, #0
	mov r1, #2
	bl MOD75_021EC090
	mov r0, #0xf
	pop {r3, r4, r5, pc}
_021E98FC:
	add r5, #0xc4
	ldr r0, [r5]
	mov r1, #4
	add r0, #0x68
	strh r1, [r0]
	mov r0, #1
	mov r1, #6
	bl FUN_02079A70
	mov r0, #0x18
	pop {r3, r4, r5, pc}
_021E9912:
	cmp r0, #3
	bne _021E9924
	add r5, #0xc4
	ldr r0, [r5]
	mov r1, #4
	add r0, #0x68
	strh r1, [r0]
	mov r0, #0x18
	pop {r3, r4, r5, pc}
_021E9924:
	mov r0, #0xe
	pop {r3, r4, r5, pc}
	.align 2, 0
_021E9928: .word 0x000003D9
_021E992C: .word 0x00000426
	thumb_func_end MOD75_021E9840

	thumb_func_start MOD75_021E9930
MOD75_021E9930: ; 0x021E9930
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E9974 ; =0x00000426
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0
	bne _021E9970
	ldr r0, _021E9978 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	bne _021E9952
	ldr r0, _021E997C ; =UNK_021C48F8
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	beq _021E9970
_021E9952:
	add r0, r4, #0
	add r0, #0x64
	mov r1, #0
	bl FUN_0200D0E0
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02019220
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021EC090
	mov r0, #0xe
	pop {r4, pc}
_021E9970:
	mov r0, #0xf
	pop {r4, pc}
	.align 2, 0
_021E9974: .word 0x00000426
_021E9978: .word gMain
_021E997C: .word UNK_021C48F8
	thumb_func_end MOD75_021E9930

	thumb_func_start MOD75_021E9980
MOD75_021E9980: ; 0x021E9980
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	bl MOD75_021E86C0
	add r0, r5, #0
	bl MOD75_021EA2D8
	cmp r0, #1
	bne _021E999A
	add sp, #8
	mov r0, #0x10
	pop {r3, r4, r5, pc}
_021E999A:
	add r0, r5, #0
	bl MOD75_021E7D14
	cmp r0, #1
	bne _021E99AA
	add sp, #8
	mov r0, #2
	pop {r3, r4, r5, pc}
_021E99AA:
	add r0, r5, #0
	bl MOD75_021E8304
	cmp r0, #1
	bne _021E99BA
	add sp, #8
	mov r0, #2
	pop {r3, r4, r5, pc}
_021E99BA:
	add r0, r5, #0
	bl MOD75_021E7B7C
	cmp r0, #1
	beq _021E99C6
	b _021E9B2A
_021E99C6:
	add r0, r5, #0
	mov r1, #0
	bl MOD75_021EB808
	add r0, r5, #0
	add r0, #0x64
	mov r1, #0xf
	bl FUN_02019620
	add r0, r5, #0
	ldr r2, _021E9B3C ; =0x000003D9
	add r0, #0x64
	mov r1, #0
	mov r3, #0xc
	bl FUN_0200D0BC
	add r2, r5, #0
	add r2, #0xc4
	ldr r2, [r2]
	mov r0, #0x46
	add r2, #0x66
	lsl r0, r0, #2
	ldrh r2, [r2]
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_0200AE38
	add r0, r5, #0
	mov r1, #2
	bl MOD75_021EC090
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #0
	add r0, #0x66
	ldrh r0, [r0]
	mov r2, #6
	bl GetItemAttr
	ldr r1, _021E9B40 ; =0x0000048C
	mov r2, #6
	str r0, [r5, r1]
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #3
	add r0, #0x66
	ldrh r0, [r0]
	bl GetItemAttr
	cmp r0, #0
	bne _021E9A38
	ldr r1, _021E9B40 ; =0x0000048C
	ldr r0, [r5, r1]
	cmp r0, #0
	bne _021E9A6E
_021E9A38:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x4a
	bl NewString_ReadMsgData
	add r4, r0, #0
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	bl MOD75_021EB660
	ldr r1, _021E9B44 ; =0x00000426
	add sp, #8
	strb r0, [r5, r1]
	mov r0, #0x16
	pop {r3, r4, r5, pc}
_021E9A6E:
	mov r2, #1
	sub r0, r1, #4
	strh r2, [r5, r0]
	ldr r0, [r5, r1]
	mov r3, #6
	lsr r0, r0, #1
	str r0, [r5, r1]
	add r0, r5, #0
	add r0, #0xc4
	ldr r2, [r0]
	add r0, r2, #0
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r1, r2, r0
	ldr r0, [r1, #4]
	ldrb r1, [r1, #0xd]
	add r2, #0x66
	ldrh r2, [r2]
	sub r1, r1, #3
	bl FUN_0206EF10
	cmp r0, #1
	bne _021E9AF4
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x4c
	bl NewString_ReadMsgData
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, _021E9B48 ; =0x00000488
	mov r0, #0x46
	ldrsh r3, [r5, r2]
	add r2, r2, #4
	lsl r0, r0, #2
	ldr r2, [r5, r2]
	ldr r0, [r5, r0]
	mul r2, r3
	mov r3, #6
	bl FUN_0200AD38
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	bl MOD75_021EB660
	ldr r1, _021E9B44 ; =0x00000426
	add sp, #8
	strb r0, [r5, r1]
	mov r0, #0x13
	pop {r3, r4, r5, pc}
_021E9AF4:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x4b
	bl NewString_ReadMsgData
	add r4, r0, #0
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	bl MOD75_021EB660
	ldr r1, _021E9B44 ; =0x00000426
	add sp, #8
	strb r0, [r5, r1]
	mov r0, #0x11
	pop {r3, r4, r5, pc}
_021E9B2A:
	cmp r0, #3
	bne _021E9B34
	add sp, #8
	mov r0, #0x18
	pop {r3, r4, r5, pc}
_021E9B34:
	mov r0, #0x10
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_021E9B3C: .word 0x000003D9
_021E9B40: .word 0x0000048C
_021E9B44: .word 0x00000426
_021E9B48: .word 0x00000488
	thumb_func_end MOD75_021E9980

	thumb_func_start MOD75_021E9B4C
MOD75_021E9B4C: ; 0x021E9B4C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E9B80 ; =0x00000426
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0
	bne _021E9B7C
	ldr r0, _021E9B84 ; =0x0000048A
	ldrh r1, [r4, r0]
	cmp r1, #0x63
	bls _021E9B68
	mov r1, #0x63
	strh r1, [r4, r0]
_021E9B68:
	add r0, r4, #0
	mov r1, #0
	bl MOD75_021EB708
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021EC24C
	mov r0, #0x12
	pop {r4, pc}
_021E9B7C:
	mov r0, #0x11
	pop {r4, pc}
	.align 2, 0
_021E9B80: .word 0x00000426
_021E9B84: .word 0x0000048A
	thumb_func_end MOD75_021E9B4C

	thumb_func_start MOD75_021E9B88
MOD75_021E9B88: ; 0x021E9B88
	push {r3, r4, r5, lr}
	sub sp, #8
	ldr r2, _021E9D54 ; =0x00000488
	add r4, r0, #0
	add r1, r4, r2
	add r2, r2, #2
	ldrh r2, [r4, r2]
	bl MOD75_021EA594
	cmp r0, #1
	bne _021E9BAC
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021EB708
	add sp, #8
	mov r0, #0x12
	pop {r3, r4, r5, pc}
_021E9BAC:
	add r0, r4, #0
	bl MOD75_021E87B8
	cmp r0, #1
	bne _021E9C2C
	add r0, r4, #0
	mov r1, #0
	bl MOD75_021EC298
	add r0, r4, #0
	add r0, #0x74
	mov r1, #1
	bl FUN_0200CCF8
	add r0, r4, #0
	add r0, #0x64
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x4c
	bl NewString_ReadMsgData
	mov r1, #0
	add r5, r0, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, _021E9D54 ; =0x00000488
	mov r0, #0x46
	ldrsh r3, [r4, r2]
	add r2, r2, #4
	lsl r0, r0, #2
	ldr r2, [r4, r2]
	ldr r0, [r4, r0]
	mul r2, r3
	mov r3, #6
	bl FUN_0200AD38
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	add r2, r5, #0
	bl StringExpandPlaceholders
	add r0, r5, #0
	bl String_dtor
	add r0, r4, #0
	bl MOD75_021EB660
	ldr r1, _021E9D58 ; =0x00000426
	add sp, #8
	strb r0, [r4, r1]
	mov r0, #1
	add r1, #0x6a
	strb r0, [r4, r1]
	mov r0, #0x13
	pop {r3, r4, r5, pc}
_021E9C2C:
	ldr r1, _021E9D54 ; =0x00000488
	add r0, r4, r1
	add r1, r1, #2
	ldrh r1, [r4, r1]
	bl FUN_02079AAC
	cmp r0, #0
	beq _021E9C80
	cmp r0, #1
	beq _021E9C46
	cmp r0, #2
	beq _021E9C62
	b _021E9C80
_021E9C46:
	add r0, r4, #0
	mov r1, #0x12
	bl MOD75_021EA0CC
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021EB708
	ldr r0, _021E9D5C ; =0x00000638
	bl FUN_020054C8
	add sp, #8
	mov r0, #0x12
	pop {r3, r4, r5, pc}
_021E9C62:
	mov r1, #0x11
	add r0, r4, #0
	mvn r1, r1
	bl MOD75_021EA0CC
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021EB708
	ldr r0, _021E9D5C ; =0x00000638
	bl FUN_020054C8
	add sp, #8
	mov r0, #0x12
	pop {r3, r4, r5, pc}
_021E9C80:
	ldr r0, _021E9D60 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _021E9D00
	add r0, r4, #0
	mov r1, #0
	bl MOD75_021EC298
	add r0, r4, #0
	add r0, #0x74
	mov r1, #1
	bl FUN_0200CCF8
	add r0, r4, #0
	add r0, #0x64
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x4c
	bl NewString_ReadMsgData
	mov r1, #0
	add r5, r0, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, _021E9D54 ; =0x00000488
	mov r0, #0x46
	ldrsh r3, [r4, r2]
	add r2, r2, #4
	lsl r0, r0, #2
	ldr r2, [r4, r2]
	ldr r0, [r4, r0]
	mul r2, r3
	mov r3, #6
	bl FUN_0200AD38
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	add r2, r5, #0
	bl StringExpandPlaceholders
	add r0, r5, #0
	bl String_dtor
	add r0, r4, #0
	bl MOD75_021EB660
	ldr r1, _021E9D58 ; =0x00000426
	strb r0, [r4, r1]
	ldr r0, _021E9D64 ; =0x000005DC
	bl FUN_020054C8
	add sp, #8
	mov r0, #0x13
	pop {r3, r4, r5, pc}
_021E9D00:
	mov r0, #2
	tst r0, r1
	beq _021E9D4C
	ldr r0, _021E9D68 ; =0x0000048C
	mov r1, #0
	str r1, [r4, r0]
	add r0, r4, #0
	bl MOD75_021EC298
	add r0, r4, #0
	add r0, #0x84
	mov r1, #1
	bl FUN_0200CCF8
	add r0, r4, #0
	add r0, #0x74
	mov r1, #1
	bl FUN_0200CCF8
	add r0, r4, #0
	add r0, #0x64
	mov r1, #0
	bl FUN_0200D0E0
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02019220
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021EC090
	ldr r0, _021E9D64 ; =0x000005DC
	bl FUN_020054C8
	add sp, #8
	mov r0, #0x10
	pop {r3, r4, r5, pc}
_021E9D4C:
	mov r0, #0x12
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_021E9D54: .word 0x00000488
_021E9D58: .word 0x00000426
_021E9D5C: .word 0x00000638
_021E9D60: .word gMain
_021E9D64: .word 0x000005DC
_021E9D68: .word 0x0000048C
	thumb_func_end MOD75_021E9B88

	thumb_func_start MOD75_021E9D6C
MOD75_021E9D6C: ; 0x021E9D6C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E9D8C ; =0x00000426
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0
	bne _021E9D86
	add r0, r4, #0
	bl MOD75_021EB6E0
	mov r0, #0x14
	pop {r4, pc}
_021E9D86:
	mov r0, #0x13
	pop {r4, pc}
	nop
_021E9D8C: .word 0x00000426
	thumb_func_end MOD75_021E9D6C

	thumb_func_start MOD75_021E9D90
MOD75_021E9D90: ; 0x021E9D90
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	bl MOD75_021EA510
	cmp r0, #1
	bne _021E9DA4
	add sp, #8
	mov r0, #0x14
	pop {r3, r4, r5, pc}
_021E9DA4:
	add r0, r5, #0
	bl MOD75_021E87B8
	cmp r0, #1
	bne _021E9DC6
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	mov r2, #6
	bl FUN_020021CC
	mov r1, #0x49
	mov r2, #1
	lsl r1, r1, #4
	strb r2, [r5, r1]
	b _021E9DD2
_021E9DC6:
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #6
	bl FUN_020021AC
_021E9DD2:
	cmp r0, #0
	beq _021E9DE6
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _021E9EA2
	add r1, r1, #1
	cmp r0, r1
	beq _021E9E7A
	b _021E9ED2
_021E9DE6:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x4d
	bl NewString_ReadMsgData
	add r4, r0, #0
	ldr r0, _021E9ED8 ; =0x00000488
	ldrsh r0, [r5, r0]
	cmp r0, #1
	ble _021E9E14
	add r2, r5, #0
	add r2, #0xc4
	ldr r2, [r2]
	mov r0, #0x46
	add r2, #0x66
	lsl r0, r0, #2
	ldrh r2, [r2]
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_0200AEA8
	b _021E9E2A
_021E9E14:
	add r2, r5, #0
	add r2, #0xc4
	ldr r2, [r2]
	mov r0, #0x46
	add r2, #0x66
	lsl r0, r0, #2
	ldrh r2, [r2]
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_0200AE38
_021E9E2A:
	mov r0, #0
	str r0, [sp]
	mov r1, #1
	mov r0, #0x46
	ldr r2, _021E9ED8 ; =0x00000488
	str r1, [sp, #4]
	ldrsh r3, [r5, r2]
	add r2, r2, #4
	lsl r0, r0, #2
	ldr r2, [r5, r2]
	ldr r0, [r5, r0]
	mul r2, r3
	mov r3, #6
	bl FUN_0200AD38
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	add r0, #0x64
	mov r1, #0xf
	bl FUN_02019620
	add r0, r5, #0
	bl MOD75_021EB660
	ldr r1, _021E9EDC ; =0x00000426
	add sp, #8
	strb r0, [r5, r1]
	mov r0, #0x15
	pop {r3, r4, r5, pc}
_021E9E7A:
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02001E60
	cmp r0, #1
	bne _021E9E92
	add r0, r5, #0
	mov r1, #0x12
	bl MOD75_021EA0CC
	b _021E9ED2
_021E9E92:
	cmp r0, #2
	bne _021E9ED2
	mov r1, #0x11
	add r0, r5, #0
	mvn r1, r1
	bl MOD75_021EA0CC
	b _021E9ED2
_021E9EA2:
	ldr r0, _021E9EE0 ; =0x0000048C
	mov r1, #0
	str r1, [r5, r0]
	add r0, r5, #0
	add r0, #0x84
	mov r1, #1
	bl FUN_0200CCF8
	add r0, r5, #0
	add r0, #0x64
	mov r1, #0
	bl FUN_0200D0E0
	add r0, r5, #0
	add r0, #0x14
	bl FUN_02019220
	add r0, r5, #0
	mov r1, #1
	bl MOD75_021EC090
	add sp, #8
	mov r0, #0x10
	pop {r3, r4, r5, pc}
_021E9ED2:
	mov r0, #0x14
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_021E9ED8: .word 0x00000488
_021E9EDC: .word 0x00000426
_021E9EE0: .word 0x0000048C
	thumb_func_end MOD75_021E9D90

	thumb_func_start MOD75_021E9EE4
MOD75_021E9EE4: ; 0x021E9EE4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E9F64 ; =0x00000426
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0
	beq _021E9EF8
	mov r0, #0x15
	pop {r4, pc}
_021E9EF8:
	ldr r0, _021E9F68 ; =0x00000644
	bl FUN_020054C8
	ldr r1, _021E9F6C ; =0x00000488
	add r0, r4, #0
	ldrsh r2, [r4, r1]
	add r1, r1, #4
	add r0, #0xcc
	ldr r1, [r4, r1]
	ldr r0, [r0]
	mul r1, r2
	bl PlayerData_AddMoney
	ldr r0, _021E9F6C ; =0x00000488
	ldrsh r0, [r4, r0]
	cmp r0, #1
	bne _021E9F38
	add r0, r4, #0
	add r0, #0xc4
	ldr r1, [r0]
	add r0, r1, #0
	add r0, #0x75
	ldrb r0, [r0]
	cmp r0, #0xff
	beq _021E9F44
	add r0, r1, #0
	add r0, #0x75
	ldrb r0, [r0]
	add r1, #0x75
	add r0, r0, #1
	strb r0, [r1]
	b _021E9F44
_021E9F38:
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #2
	add r0, #0x75
	strb r1, [r0]
_021E9F44:
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021EB808
	ldr r0, _021E9F70 ; =0x00000479
	mov r1, #1
	strb r1, [r4, r0]
	add r0, r4, #0
	bl MOD75_021E92BC
	add r4, #0x64
	add r0, r4, #0
	bl FUN_02019220
	mov r0, #0x16
	pop {r4, pc}
	.align 2, 0
_021E9F64: .word 0x00000426
_021E9F68: .word 0x00000644
_021E9F6C: .word 0x00000488
_021E9F70: .word 0x00000479
	thumb_func_end MOD75_021E9EE4

	thumb_func_start MOD75_021E9F74
MOD75_021E9F74: ; 0x021E9F74
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021E9FCC ; =0x00000426
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0
	bne _021E9FC8
	ldr r0, _021E9FD0 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	bne _021E9F96
	ldr r0, _021E9FD4 ; =UNK_021C48F8
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	beq _021E9FC8
_021E9F96:
	ldr r0, _021E9FD8 ; =0x00000479
	mov r1, #0
	strb r1, [r4, r0]
	add r0, #0x13
	str r1, [r4, r0]
	add r0, r4, #0
	add r0, #0x84
	mov r1, #1
	bl FUN_0200CCF8
	add r0, r4, #0
	add r0, #0x64
	mov r1, #0
	bl FUN_0200D0E0
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02019220
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021EC090
	mov r0, #0x10
	pop {r4, pc}
_021E9FC8:
	mov r0, #0x16
	pop {r4, pc}
	.align 2, 0
_021E9FCC: .word 0x00000426
_021E9FD0: .word gMain
_021E9FD4: .word UNK_021C48F8
_021E9FD8: .word 0x00000479
	thumb_func_end MOD75_021E9F74

	thumb_func_start MOD75_021E9FDC
MOD75_021E9FDC: ; 0x021E9FDC
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	bl MOD75_021E86C0
	add r0, r4, #0
	bl MOD75_021EA2D8
	cmp r0, #1
	bne _021E9FF6
	add sp, #4
	mov r0, #0x17
	pop {r3, r4, pc}
_021E9FF6:
	add r0, r4, #0
	bl MOD75_021E7D14
	cmp r0, #1
	bne _021EA006
	add sp, #4
	mov r0, #2
	pop {r3, r4, pc}
_021EA006:
	add r0, r4, #0
	bl MOD75_021E8304
	cmp r0, #1
	bne _021EA016
	add sp, #4
	mov r0, #2
	pop {r3, r4, pc}
_021EA016:
	add r0, r4, #0
	bl MOD75_021E7B7C
	cmp r0, #1
	bne _021EA0A8
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, r0, #0
	add r1, #0x64
	ldrb r2, [r1]
	mov r1, #0xc
	mul r1, r2
	add r1, r0, r1
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _021EA090
	add r0, #0x66
	ldrh r0, [r0]
	mov r1, #6
	add r2, r1, #0
	bl GetItemAttr
	cmp r0, #0xd
	beq _021EA090
	mov r3, #6
	add r2, r4, #0
	str r3, [sp]
	add r2, #0xc4
	ldr r2, [r2]
	add r0, r4, #0
	mov r1, #0xfe
	add r2, #0x66
	add r0, #0xcc
	lsl r1, r1, #2
	ldrh r2, [r2]
	ldr r0, [r0]
	ldr r1, [r4, r1]
	sub r3, r3, #7
	bl FUN_0206E51C
	add r0, r4, #0
	add r0, #0x64
	mov r1, #0xf
	bl FUN_02019620
	add r0, r4, #0
	ldr r2, _021EA0C4 ; =0x000003D9
	add r0, #0x64
	mov r1, #0
	mov r3, #0xc
	bl FUN_0200D0BC
	add r0, r4, #0
	bl MOD75_021EB660
	ldr r1, _021EA0C8 ; =0x00000426
	add sp, #4
	strb r0, [r4, r1]
	mov r0, #0xc
	pop {r3, r4, pc}
_021EA090:
	add r4, #0xc4
	ldr r0, [r4]
	mov r1, #0
	add r0, #0x68
	strh r1, [r0]
	mov r0, #1
	mov r1, #6
	bl FUN_02079A70
	add sp, #4
	mov r0, #0x18
	pop {r3, r4, pc}
_021EA0A8:
	cmp r0, #3
	bne _021EA0BC
	add r4, #0xc4
	ldr r0, [r4]
	mov r1, #5
	add r0, #0x68
	strh r1, [r0]
	add sp, #4
	mov r0, #0x18
	pop {r3, r4, pc}
_021EA0BC:
	mov r0, #0x17
	add sp, #4
	pop {r3, r4, pc}
	nop
_021EA0C4: .word 0x000003D9
_021EA0C8: .word 0x00000426
	thumb_func_end MOD75_021E9FDC

	thumb_func_start MOD75_021EA0CC
MOD75_021EA0CC: ; 0x021EA0CC
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4]
	add r5, r1, #0
	mov r1, #7
	bl FUN_02018878
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r0, r0, r5
	lsl r0, r0, #0x10
	asr r5, r0, #0x10
	mov r0, #0x5a
	lsl r0, r0, #2
	cmp r5, r0
	blt _021EA0F4
	sub r0, r5, r0
	lsl r0, r0, #0x10
	asr r5, r0, #0x10
	b _021EA0FE
_021EA0F4:
	cmp r5, #0
	bge _021EA0FE
	add r0, r5, r0
	lsl r0, r0, #0x10
	asr r5, r0, #0x10
_021EA0FE:
	lsl r3, r5, #0x10
	ldr r0, [r4]
	mov r1, #7
	mov r2, #0
	lsr r3, r3, #0x10
	bl FUN_0201AF08
	ldr r0, _021EA114 ; =0x0000049A
	strh r5, [r4, r0]
	pop {r3, r4, r5, pc}
	nop
_021EA114: .word 0x0000049A
	thumb_func_end MOD75_021EA0CC

	thumb_func_start MOD75_021EA118
MOD75_021EA118: ; 0x021EA118
	push {r3, lr}
	ldr r0, _021EA12C ; =0x021EC404
	bl FUN_020209F4
	cmp r0, #1
	bne _021EA128
	mov r0, #1
	pop {r3, pc}
_021EA128:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_021EA12C: .word MOD75_021EC404
	thumb_func_end MOD75_021EA118

	thumb_func_start MOD75_021EA130
MOD75_021EA130: ; 0x021EA130
	push {r3, lr}
	ldr r0, _021EA144 ; =0x021EC410
	bl FUN_020209A8
	cmp r0, #1
	bne _021EA140
	mov r0, #1
	pop {r3, pc}
_021EA140:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_021EA144: .word MOD75_021EC410
	thumb_func_end MOD75_021EA130

	thumb_func_start MOD75_021EA148
MOD75_021EA148: ; 0x021EA148
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	bl MOD75_021EA118
	cmp r0, #1
	bne _021EA176
	ldr r1, _021EA2BC ; =0x00000492
	mov r0, #1
	strb r0, [r5, r1]
	mov r2, #0
	add r0, r1, #6
	strh r2, [r5, r0]
	add r0, r1, #2
	str r2, [r5, r0]
	add r0, r1, #0
	ldr r2, _021EA2C0 ; =UNK_021C48F8
	add r0, #0xc
	ldrh r3, [r2, #0x1c]
	add r1, #0xe
	strh r3, [r5, r0]
	ldrh r0, [r2, #0x1e]
	strh r0, [r5, r1]
_021EA176:
	ldr r0, _021EA2BC ; =0x00000492
	ldrb r0, [r5, r0]
	cmp r0, #1
	beq _021EA180
	b _021EA2B6
_021EA180:
	bl MOD75_021EA130
	cmp r0, #1
	beq _021EA18A
	b _021EA2A8
_021EA18A:
	mov r3, #0x50
	ldr r1, _021EA2C4 ; =0x0000049E
	str r3, [sp]
	ldr r4, _021EA2C0 ; =UNK_021C48F8
	ldrh r0, [r5, r1]
	add r1, r1, #2
	ldrh r1, [r5, r1]
	ldrh r2, [r4, #0x1c]
	mov r7, #0x80
	ldrh r4, [r4, #0x1e]
	sub r1, r3, r1
	sub r0, r7, r0
	sub r2, r7, r2
	sub r3, r3, r4
	bl CircularDistance
	add r4, r0, #0
	mov r0, #0x50
	lsl r1, r4, #1
	bl MathUtil_0201BC84
	lsl r0, r0, #8
	mov r1, #0xb6
	bl _s32_div_f
	ldr r1, _021EA2C8 ; =0x0000049A
	asr r3, r0, #8
	ldrsh r2, [r5, r1]
	add r0, r5, r1
	add r2, r2, r3
	strh r2, [r0]
	ldrsh r1, [r5, r1]
	cmp r1, #0
	bge _021EA1DC
	mov r1, #0
	ldrsh r2, [r0, r1]
	add r1, r7, #0
	add r1, #0xe8
	add r1, r2, r1
	strh r1, [r0]
	b _021EA1EC
_021EA1DC:
	add r2, r7, #0
	add r2, #0xe8
	cmp r1, r2
	blt _021EA1EC
	mov r1, #0
	ldrsh r1, [r0, r1]
	sub r1, r1, r2
	strh r1, [r0]
_021EA1EC:
	ldr r3, _021EA2C8 ; =0x0000049A
	ldr r0, [r5]
	ldrh r3, [r5, r3]
	mov r1, #7
	mov r2, #0
	bl FUN_0201AF08
	ldr r0, _021EA2CC ; =0x000001F6
	add r1, r6, #0
	bl _s32_div_f
	add r6, r0, #0
	cmp r4, #0
	ble _021EA250
	ldr r0, _021EA2D0 ; =0x00000498
	ldrsh r1, [r5, r0]
	cmp r1, #0
	bge _021EA22A
	add r0, r4, #0
	add r1, r6, #0
	bl _s32_div_f
	ldr r1, _021EA2D0 ; =0x00000498
	strh r0, [r5, r1]
	add r0, r4, #0
	add r1, r6, #0
	bl _s32_div_f
	ldr r0, _021EA2D4 ; =0x00000494
	str r1, [r5, r0]
	b _021EA298
_021EA22A:
	sub r0, r0, #4
	ldr r0, [r5, r0]
	add r1, r6, #0
	add r0, r0, r4
	bl _s32_div_f
	ldr r1, _021EA2D0 ; =0x00000498
	ldrsh r2, [r5, r1]
	add r0, r2, r0
	strh r0, [r5, r1]
	sub r0, r1, #4
	ldr r0, [r5, r0]
	add r1, r6, #0
	add r0, r0, r4
	bl _s32_div_f
	ldr r0, _021EA2D4 ; =0x00000494
	str r1, [r5, r0]
	b _021EA298
_021EA250:
	bge _021EA298
	ldr r0, _021EA2D0 ; =0x00000498
	ldrsh r1, [r5, r0]
	cmp r1, #0
	ble _021EA274
	add r0, r4, #0
	add r1, r6, #0
	bl _s32_div_f
	ldr r1, _021EA2D0 ; =0x00000498
	strh r0, [r5, r1]
	add r0, r4, #0
	add r1, r6, #0
	bl _s32_div_f
	ldr r0, _021EA2D4 ; =0x00000494
	str r1, [r5, r0]
	b _021EA298
_021EA274:
	sub r0, r0, #4
	ldr r0, [r5, r0]
	add r1, r6, #0
	add r0, r0, r4
	bl _s32_div_f
	ldr r1, _021EA2D0 ; =0x00000498
	ldrsh r2, [r5, r1]
	add r0, r2, r0
	strh r0, [r5, r1]
	sub r0, r1, #4
	ldr r0, [r5, r0]
	add r1, r6, #0
	add r0, r0, r4
	bl _s32_div_f
	ldr r0, _021EA2D4 ; =0x00000494
	str r1, [r5, r0]
_021EA298:
	ldr r1, _021EA2C0 ; =UNK_021C48F8
	ldr r0, _021EA2C4 ; =0x0000049E
	ldrh r2, [r1, #0x1c]
	strh r2, [r5, r0]
	ldrh r1, [r1, #0x1e]
	add r0, r0, #2
	strh r1, [r5, r0]
	b _021EA2B2
_021EA2A8:
	ldr r0, _021EA2BC ; =0x00000492
	mov r1, #0
	strb r1, [r5, r0]
	add r0, r0, #6
	strh r1, [r5, r0]
_021EA2B2:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021EA2B6:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021EA2BC: .word 0x00000492
_021EA2C0: .word UNK_021C48F8
_021EA2C4: .word 0x0000049E
_021EA2C8: .word 0x0000049A
_021EA2CC: .word 0x000001F6
_021EA2D0: .word 0x00000498
_021EA2D4: .word 0x00000494
	thumb_func_end MOD75_021EA148

	thumb_func_start MOD75_021EA2D8
MOD75_021EA2D8: ; 0x021EA2D8
	push {r4, lr}
	mov r1, #0x24
	add r4, r0, #0
	bl MOD75_021EA148
	ldr r1, _021EA324 ; =0x00000498
	ldrsh r1, [r4, r1]
	cmp r1, #0
	ble _021EA306
	add r0, r4, #0
	mov r1, #0x40
	bl MOD75_021EA328
	cmp r0, #1
	ldr r0, _021EA324 ; =0x00000498
	bne _021EA2FE
	ldrsh r1, [r4, r0]
	sub r1, r1, #1
	b _021EA300
_021EA2FE:
	mov r1, #0
_021EA300:
	strh r1, [r4, r0]
	mov r0, #1
	pop {r4, pc}
_021EA306:
	bge _021EA322
	add r0, r4, #0
	mov r1, #0x80
	bl MOD75_021EA328
	cmp r0, #1
	ldr r0, _021EA324 ; =0x00000498
	bne _021EA31C
	ldrsh r1, [r4, r0]
	add r1, r1, #1
	b _021EA31E
_021EA31C:
	mov r1, #0
_021EA31E:
	strh r1, [r4, r0]
	mov r0, #1
_021EA322:
	pop {r4, pc}
	.align 2, 0
_021EA324: .word 0x00000498
	thumb_func_end MOD75_021EA2D8

	thumb_func_start MOD75_021EA328
MOD75_021EA328: ; 0x021EA328
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r4, r0, #0
	add r0, #0xc4
	ldr r3, [r0]
	mov r5, #0xc
	add r0, r3, #0
	add r0, #0x64
	ldrb r0, [r0]
	add r2, r0, #0
	mul r2, r5
	add r0, r3, r2
	ldrh r0, [r0, #0xa]
	add r3, sp, #0x10
	strh r0, [r3, #2]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r2, r0, #0
	add r2, #0x64
	ldrb r2, [r2]
	mul r5, r2
	add r0, r0, r5
	ldrh r0, [r0, #8]
	strh r0, [r3]
	mov r0, #1
	str r0, [sp]
	add r0, sp, #0x10
	str r1, [sp, #4]
	add r0, #2
	str r0, [sp, #8]
	add r0, sp, #0x10
	str r0, [sp, #0xc]
	mov r0, #0x57
	lsl r0, r0, #2
	ldrh r2, [r3, #2]
	ldrh r3, [r3]
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02001354
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, r0, #0
	add r1, #0x64
	ldrb r2, [r1]
	mov r1, #0xc
	add r5, r2, #0
	mul r5, r1
	add r1, sp, #0x10
	add r2, r0, r5
	ldrh r3, [r1, #2]
	ldrh r0, [r2, #0xa]
	cmp r3, r0
	bne _021EA3A6
	ldrh r1, [r1]
	ldrh r0, [r2, #8]
	cmp r1, r0
	bne _021EA3A6
	add sp, #0x14
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_021EA3A6:
	add r2, sp, #0x10
	ldrh r2, [r2]
	add r0, r4, #0
	add r0, #0xf0
	sub r2, r2, #1
	lsl r2, r2, #4
	add r2, #0x18
	lsl r2, r2, #0x10
	ldr r0, [r0]
	mov r1, #0xb1
	asr r2, r2, #0x10
	bl FUN_0200C714
	add r0, r4, #0
	add r0, #0xc4
	ldr r6, [r0]
	add r2, sp, #0x10
	add r0, r6, #0
	add r0, #0x64
	ldrb r0, [r0]
	ldrh r5, [r2, #2]
	mov r1, #0xc
	add r3, r0, #0
	mul r3, r1
	add r0, r6, r3
	strh r5, [r0, #0xa]
	add r4, #0xc4
	ldr r3, [r4]
	ldrh r2, [r2]
	add r0, r3, #0
	add r0, #0x64
	ldrb r0, [r0]
	mul r1, r0
	add r0, r3, r1
	strh r2, [r0, #8]
	mov r0, #1
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD75_021EA328

	thumb_func_start MOD75_021EA3F4
MOD75_021EA3F4: ; 0x021EA3F4
	push {r4, lr}
	mov r1, #0x24
	add r4, r0, #0
	bl MOD75_021EA148
	ldr r1, _021EA440 ; =0x00000498
	ldrsh r1, [r4, r1]
	cmp r1, #0
	ble _021EA422
	add r0, r4, #0
	mov r1, #0x40
	bl MOD75_021EA444
	cmp r0, #1
	ldr r0, _021EA440 ; =0x00000498
	bne _021EA41A
	ldrsh r1, [r4, r0]
	sub r1, r1, #1
	b _021EA41C
_021EA41A:
	mov r1, #0
_021EA41C:
	strh r1, [r4, r0]
	mov r0, #1
	pop {r4, pc}
_021EA422:
	bge _021EA43E
	add r0, r4, #0
	mov r1, #0x80
	bl MOD75_021EA444
	cmp r0, #1
	ldr r0, _021EA440 ; =0x00000498
	bne _021EA438
	ldrsh r1, [r4, r0]
	add r1, r1, #1
	b _021EA43A
_021EA438:
	mov r1, #0
_021EA43A:
	strh r1, [r4, r0]
	mov r0, #1
_021EA43E:
	pop {r4, pc}
	.align 2, 0
_021EA440: .word 0x00000498
	thumb_func_end MOD75_021EA3F4

	thumb_func_start MOD75_021EA444
MOD75_021EA444: ; 0x021EA444
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r4, r0, #0
	add r0, #0xc4
	ldr r3, [r0]
	mov r5, #0xc
	add r0, r3, #0
	add r0, #0x64
	ldrb r0, [r0]
	add r2, r0, #0
	mul r2, r5
	add r0, r3, r2
	ldrh r0, [r0, #0xa]
	add r3, sp, #0x10
	strh r0, [r3, #2]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r2, r0, #0
	add r2, #0x64
	ldrb r2, [r2]
	mul r5, r2
	add r0, r0, r5
	ldrh r0, [r0, #8]
	strh r0, [r3]
	mov r0, #1
	str r0, [sp]
	add r0, sp, #0x10
	str r1, [sp, #4]
	add r0, #2
	str r0, [sp, #8]
	add r0, sp, #0x10
	str r0, [sp, #0xc]
	mov r0, #0x57
	lsl r0, r0, #2
	ldrh r2, [r3, #2]
	ldrh r3, [r3]
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02001354
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, r0, #0
	add r1, #0x64
	ldrb r2, [r1]
	mov r1, #0xc
	add r5, r2, #0
	mul r5, r1
	add r1, sp, #0x10
	add r2, r0, r5
	ldrh r3, [r1, #2]
	ldrh r0, [r2, #0xa]
	cmp r3, r0
	bne _021EA4C2
	ldrh r1, [r1]
	ldrh r0, [r2, #8]
	cmp r1, r0
	bne _021EA4C2
	add sp, #0x14
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_021EA4C2:
	add r2, sp, #0x10
	ldrh r2, [r2]
	add r0, r4, #0
	add r0, #0xf4
	sub r2, r2, #1
	lsl r2, r2, #4
	add r2, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r0]
	mov r1, #0xb1
	asr r2, r2, #0x10
	bl FUN_0200C714
	add r0, r4, #0
	add r0, #0xc4
	ldr r6, [r0]
	add r2, sp, #0x10
	add r0, r6, #0
	add r0, #0x64
	ldrb r0, [r0]
	ldrh r5, [r2, #2]
	mov r1, #0xc
	add r3, r0, #0
	mul r3, r1
	add r0, r6, r3
	strh r5, [r0, #0xa]
	add r4, #0xc4
	ldr r3, [r4]
	ldrh r2, [r2]
	add r0, r3, #0
	add r0, #0x64
	ldrb r0, [r0]
	mul r1, r0
	add r0, r3, r1
	strh r2, [r0, #8]
	mov r0, #1
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD75_021EA444

	thumb_func_start MOD75_021EA510
MOD75_021EA510: ; 0x021EA510
	push {r4, lr}
	mov r1, #0x12
	add r4, r0, #0
	bl MOD75_021EA148
	ldr r1, _021EA55C ; =0x00000498
	ldrsh r1, [r4, r1]
	cmp r1, #0
	ble _021EA53E
	add r0, r4, #0
	mov r1, #2
	bl MOD75_021EA560
	cmp r0, #1
	ldr r0, _021EA55C ; =0x00000498
	bne _021EA536
	ldrsh r1, [r4, r0]
	sub r1, r1, #1
	b _021EA538
_021EA536:
	mov r1, #0
_021EA538:
	strh r1, [r4, r0]
	mov r0, #1
	pop {r4, pc}
_021EA53E:
	bge _021EA55A
	add r0, r4, #0
	mov r1, #3
	bl MOD75_021EA560
	cmp r0, #1
	ldr r0, _021EA55C ; =0x00000498
	bne _021EA554
	ldrsh r1, [r4, r0]
	add r1, r1, #1
	b _021EA556
_021EA554:
	mov r1, #0
_021EA556:
	strh r1, [r4, r0]
	mov r0, #1
_021EA55A:
	pop {r4, pc}
	.align 2, 0
_021EA55C: .word 0x00000498
	thumb_func_end MOD75_021EA510

	thumb_func_start MOD75_021EA560
MOD75_021EA560: ; 0x021EA560
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r6, r1, #0
	bl FUN_02001E5C
	add r4, r0, #0
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl FUN_02001DDC
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02001E5C
	cmp r4, r0
	beq _021EA590
	mov r0, #1
	pop {r4, r5, r6, pc}
_021EA590:
	mov r0, #0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD75_021EA560

	thumb_func_start MOD75_021EA594
MOD75_021EA594: ; 0x021EA594
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	mov r1, #0x12
	add r5, r0, #0
	add r6, r2, #0
	bl MOD75_021EA148
	ldr r7, _021EA5FC ; =0x00000498
	mov r1, #0
	ldrsh r2, [r5, r7]
	ldrsh r3, [r4, r1]
	cmp r2, #0
	ble _021EA5D4
	sub r0, r2, #1
	strh r0, [r5, r7]
	ldrsh r0, [r4, r1]
	add r0, r0, #1
	strh r0, [r4]
	ldrsh r0, [r4, r1]
	cmp r0, r6
	ble _021EA5C2
	mov r0, #1
	strh r0, [r4]
_021EA5C2:
	mov r0, #0
	ldrsh r1, [r4, r0]
	cmp r1, r3
	beq _021EA5F8
	ldr r0, _021EA600 ; =0x00000638
	bl FUN_020054C8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021EA5D4:
	bge _021EA5F8
	add r0, r2, #1
	strh r0, [r5, r7]
	ldrsh r0, [r4, r1]
	sub r0, r0, #1
	strh r0, [r4]
	ldrsh r0, [r4, r1]
	cmp r0, #0
	bgt _021EA5E8
	strh r6, [r4]
_021EA5E8:
	mov r0, #0
	ldrsh r1, [r4, r0]
	cmp r1, r3
	beq _021EA5F8
	ldr r0, _021EA600 ; =0x00000638
	bl FUN_020054C8
	mov r0, #1
_021EA5F8:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021EA5FC: .word 0x00000498
_021EA600: .word 0x00000638
	thumb_func_end MOD75_021EA594

	thumb_func_start MOD75_021EA604
MOD75_021EA604: ; 0x021EA604
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x11
	str r0, [sp, #4]
	mov r0, #0x12
	str r0, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r1, r4, #4
	mov r2, #2
	mov r3, #0xe
	bl FUN_02019064
	mov r0, #0x12
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	ldr r0, _021EA780 ; =0x00000133
	add r1, r4, #0
	str r0, [sp, #0x10]
	mov r2, #0
	ldr r0, [r4]
	add r1, #0x14
	add r3, r2, #0
	bl FUN_02019064
	mov r0, #0xd
	str r0, [sp]
	mov r0, #0x24
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, _021EA784 ; =0x000001F3
	add r1, r4, #0
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r1, #0x24
	mov r2, #2
	mov r3, #0
	bl FUN_02019064
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0xe
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	ldr r0, _021EA788 ; =0x0000025F
	add r1, r4, #0
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r1, #0x34
	mov r2, #0
	mov r3, #6
	bl FUN_02019064
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0xd
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	ldr r0, _021EA788 ; =0x0000025F
	add r1, r4, #0
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r1, #0x44
	mov r2, #0
	mov r3, #6
	bl FUN_02019064
	mov r0, #0xb
	str r0, [sp]
	mov r0, #0xc
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _021EA78C ; =0x00000297
	add r1, r4, #0
	str r0, [sp, #0x10]
	mov r2, #0
	ldr r0, [r4]
	add r1, #0x54
	add r3, r2, #0
	bl FUN_02019064
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	ldr r0, _021EA790 ; =0x000002AF
	add r1, r4, #0
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r1, #0x64
	mov r2, #0
	mov r3, #2
	bl FUN_02019064
	mov r0, #0xd
	str r0, [sp]
	mov r0, #0xc
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	ldr r0, _021EA794 ; =0x00000337
	add r1, r4, #0
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r1, #0x74
	mov r2, #0
	mov r3, #0x13
	bl FUN_02019064
	mov r3, #1
	add r1, r4, #0
	str r3, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	ldr r0, _021EA798 ; =0x00000367
	add r1, #0x84
	str r0, [sp, #0x10]
	ldr r0, [r4]
	mov r2, #0
	bl FUN_02019064
	mov r0, #0x13
	str r0, [sp]
	mov r0, #7
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	ldr r0, _021EA79C ; =0x00000387
	add r1, r4, #0
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r1, #0x94
	mov r2, #0
	mov r3, #0x18
	bl FUN_02019064
	mov r0, #0xc
	str r0, [sp]
	mov r0, #0xb
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	ldr r0, _021EA79C ; =0x00000387
	mov r2, #0
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r4, #0xa4
	add r1, r4, #0
	mov r3, #1
	bl FUN_02019064
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_021EA780: .word 0x00000133
_021EA784: .word 0x000001F3
_021EA788: .word 0x0000025F
_021EA78C: .word 0x00000297
_021EA790: .word 0x000002AF
_021EA794: .word 0x00000337
_021EA798: .word 0x00000367
_021EA79C: .word 0x00000387
	thumb_func_end MOD75_021EA604

	thumb_func_start MOD75_021EA7A0
MOD75_021EA7A0: ; 0x021EA7A0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_021EA7A6:
	lsl r0, r4, #4
	add r0, r5, r0
	bl FUN_02019178
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0xb
	blo _021EA7A6
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD75_021EA7A0

	thumb_func_start MOD75_021EA7BC
MOD75_021EA7BC: ; 0x021EA7BC
	push {r3, r4, r5, r6, r7, lr}
	mov r2, #0x57
	add r5, r0, #0
	mov r0, #1
	mov r1, #0x1a
	lsl r2, r2, #2
	mov r3, #6
	bl NewMsgDataFromNarc
	ldr r7, _021EA7F4 ; =0x00000404
	add r6, r0, #0
	mov r4, #0
_021EA7D4:
	add r0, r6, #0
	add r1, r4, #0
	bl NewString_ReadMsgData
	lsl r1, r4, #2
	add r1, r5, r1
	str r0, [r1, r7]
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #8
	blo _021EA7D4
	add r0, r6, #0
	bl DestroyMsgData
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021EA7F4: .word 0x00000404
	thumb_func_end MOD75_021EA7BC

	thumb_func_start MOD75_021EA7F8
MOD75_021EA7F8: ; 0x021EA7F8
	push {r4, r5, r6, lr}
	ldr r6, _021EA818 ; =0x00000404
	add r5, r0, #0
	mov r4, #0
_021EA800:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, r6]
	bl String_dtor
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #8
	blo _021EA800
	pop {r4, r5, r6, pc}
	nop
_021EA818: .word 0x00000404
	thumb_func_end MOD75_021EA7F8

	thumb_func_start MOD75_021EA81C
MOD75_021EA81C: ; 0x021EA81C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r4, #0
	mov r6, #0xd
	mov r7, #1
_021EA828:
	str r6, [sp]
	ldr r2, _021EA878 ; =0x000001FF
	str r7, [sp, #4]
	add r2, r4, r2
	lsl r2, r2, #0x10
	lsl r3, r4, #0x18
	str r7, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	ldr r0, [r5]
	mov r1, #2
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	mov r0, #0xe
	str r0, [sp]
	mov r0, #1
	ldr r2, _021EA87C ; =0x00000223
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #3
	add r2, r4, r2
	str r0, [sp, #0xc]
	lsl r2, r2, #0x10
	lsl r3, r4, #0x18
	ldr r0, [r5]
	mov r1, #2
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0xc
	blo _021EA828
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021EA878: .word 0x000001FF
_021EA87C: .word 0x00000223
	thumb_func_end MOD75_021EA81C

	thumb_func_start MOD75_021EA880
MOD75_021EA880: ; 0x021EA880
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0
	add r4, r2, #0
	add r2, r0, #0
	add r6, r1, #0
	bl FUN_02002E14
	add r3, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021EA8B8 ; =0x00010200
	lsr r3, r3, #1
	add r5, #0x24
	str r0, [sp, #8]
	mov r1, #0
	add r0, r5, #0
	add r2, r6, #0
	sub r3, r4, r3
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_021EA8B8: .word 0x00010200
	thumb_func_end MOD75_021EA880

	thumb_func_start MOD75_021EA8BC
MOD75_021EA8BC: ; 0x021EA8BC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r0, #0x24
	mov r1, #0
	bl FUN_02019620
	add r2, r4, #0
	add r2, #0xc4
	ldr r6, [r2]
	ldr r1, _021EA94C ; =0x00000429
	add r2, r6, #0
	add r2, #0x64
	ldrb r3, [r2]
	mov r2, #0xc
	add r0, r4, r1
	add r5, r3, #0
	mul r5, r2
	add r3, r6, r5
	ldrb r3, [r3, #0xc]
	lsl r3, r3, #2
	add r5, r4, r3
	add r3, r1, #0
	sub r3, #0x25
	ldr r7, [r5, r3]
	ldrb r3, [r0]
	sub r1, #0x25
	add r5, r3, #0
	mul r5, r2
	add r3, r6, r5
	ldrb r3, [r3, #0xc]
	lsl r3, r3, #2
	add r3, r4, r3
	ldr r1, [r3, r1]
	ldrb r3, [r0, #1]
	ldrb r0, [r0, #3]
	cmp r3, #0
	bne _021EA91E
	mul r2, r0
	add r2, #0x92
	lsl r0, r2, #0x10
	lsr r5, r0, #0x10
	add r2, r5, #0
	sub r2, #0x60
	lsl r2, r2, #0x10
	add r0, r4, #0
	lsr r2, r2, #0x10
	bl MOD75_021EA880
	b _021EA936
_021EA91E:
	mul r2, r0
	mov r0, #0x92
	sub r0, r0, r2
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r2, r5, #0
	add r2, #0x60
	lsl r2, r2, #0x10
	add r0, r4, #0
	lsr r2, r2, #0x10
	bl MOD75_021EA880
_021EA936:
	add r0, r4, #0
	add r1, r7, #0
	add r2, r5, #0
	bl MOD75_021EA880
	add r4, #0x24
	add r0, r4, #0
	bl FUN_02019548
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021EA94C: .word 0x00000429
	thumb_func_end MOD75_021EA8BC

	thumb_func_start MOD75_021EA950
MOD75_021EA950: ; 0x021EA950
	push {r3, r4, r5, lr}
	add r0, #0xd4
	ldr r0, [r0]
	add r5, r1, #0
	mov r1, #0x11
	mov r2, #6
	bl NARC_AllocAndReadWholeMember
	add r1, r5, #0
	add r4, r0, #0
	bl FUN_020B0030
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD75_021EA950

	thumb_func_start MOD75_021EA96C
MOD75_021EA96C: ; 0x021EA96C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r1, #0
	add r1, sp, #0x18
	add r5, r0, #0
	add r6, r2, #0
	bl MOD75_021EA950
	add r7, r0, #0
	cmp r6, #1
	bne _021EA998
	add r0, r5, #0
	add r0, #0xc4
	ldr r1, [r0]
	mov r0, #0xc
	mul r0, r4
	add r0, r1, r0
	ldrb r0, [r0, #0xc]
	lsl r0, r0, #5
	add r0, #0x10
	lsl r0, r0, #0x18
	b _021EA9A8
_021EA998:
	add r0, r5, #0
	add r0, #0xc4
	ldr r1, [r0]
	mov r0, #0xc
	mul r0, r4
	add r0, r1, r0
	ldrb r0, [r0, #0xc]
	lsl r0, r0, #0x1d
_021EA9A8:
	lsr r2, r0, #0x18
	mov r0, #1
	lsl r0, r0, #8
	str r0, [sp]
	mov r0, #0x10
	ldr r1, _021EA9F4 ; =0x00000427
	str r0, [sp, #4]
	ldrb r0, [r5, r1]
	add r1, r1, #1
	ldrb r1, [r5, r1]
	add r3, r1, #0
	mul r3, r4
	add r0, r0, r3
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	mov r0, #0xa
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	add r0, r5, #0
	ldr r1, [r1, #0x14]
	add r0, #0x54
	mov r3, #0
	bl FUN_02019658
	add r5, #0x54
	add r0, r5, #0
	bl FUN_02019220
	mov r0, #6
	add r1, r7, #0
	bl FUN_02016A8C
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021EA9F4: .word 0x00000427
	thumb_func_end MOD75_021EA96C

	thumb_func_start MOD75_021EA9F8
MOD75_021EA9F8: ; 0x021EA9F8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	add r1, sp, #0x1c
	bl MOD75_021EA950
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r0, #0x54
	mov r1, #0
	bl FUN_02019620
	ldr r0, _021EAAA0 ; =0x00000424
	mov r4, #0
	ldrb r0, [r5, r0]
	cmp r0, #0
	bls _021EAA8C
	mov r7, #1
	add r6, r5, #0
	lsl r7, r7, #8
	add r6, #0x54
_021EAA22:
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, r0, #0
	add r1, #0x64
	ldrb r1, [r1]
	cmp r4, r1
	bne _021EAA42
	mov r1, #0xc
	mul r1, r4
	add r0, r0, r1
	ldrb r0, [r0, #0xc]
	lsl r0, r0, #5
	add r0, #0x10
	lsl r0, r0, #0x18
	b _021EAA4C
_021EAA42:
	mov r1, #0xc
	mul r1, r4
	add r0, r0, r1
	ldrb r0, [r0, #0xc]
	lsl r0, r0, #0x1d
_021EAA4C:
	lsr r2, r0, #0x18
	str r7, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	ldr r0, _021EAAA4 ; =0x00000427
	ldrb r3, [r5, r0]
	add r0, r0, #1
	ldrb r0, [r5, r0]
	add r1, r0, #0
	mul r1, r4
	add r0, r3, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	mov r0, #0xa
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x1c]
	add r0, r6, #0
	ldr r1, [r1, #0x14]
	mov r3, #0
	bl FUN_02019658
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, _021EAAA0 ; =0x00000424
	ldrb r0, [r5, r0]
	cmp r4, r0
	blo _021EAA22
_021EAA8C:
	add r5, #0x54
	add r0, r5, #0
	bl FUN_02019220
	ldr r1, [sp, #0x18]
	mov r0, #6
	bl FUN_02016A8C
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021EAAA0: .word 0x00000424
_021EAAA4: .word 0x00000427
	thumb_func_end MOD75_021EA9F8

	thumb_func_start MOD75_021EAAA8
MOD75_021EAAA8: ; 0x021EAAA8
	push {r3, r4, r5, lr}
	lsl r1, r1, #0x10
	add r4, r2, #0
	lsr r1, r1, #0x10
	mov r2, #0
	add r5, r0, #0
	bl MOD75_021E7420
	add r2, r0, #0
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_0200AE38
	pop {r3, r4, r5, pc}
	thumb_func_end MOD75_021EAAA8

	thumb_func_start MOD75_021EAAC8
MOD75_021EAAC8: ; 0x021EAAC8
	push {r3, r4, r5, lr}
	lsl r1, r1, #0x10
	add r4, r2, #0
	lsr r1, r1, #0x10
	mov r2, #0
	add r5, r0, #0
	bl MOD75_021E7420
	add r2, r0, #0
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_0200AEA8
	pop {r3, r4, r5, pc}
	thumb_func_end MOD75_021EAAC8

	thumb_func_start MOD75_021EAAE8
MOD75_021EAAE8: ; 0x021EAAE8
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, _021EAB3C ; =0x0000FFFF
	add r6, r1, #0
	cmp r6, r0
	beq _021EAB0A
	mov r0, #0x82
	mov r1, #6
	bl String_ctor
	add r1, r6, #0
	mov r2, #6
	add r4, r0, #0
	bl GetItemDescIntoString
	b _021EAB18
_021EAB0A:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x5e
	bl NewString_ReadMsgData
	add r4, r0, #0
_021EAB18:
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021EAB40 ; =0x000F0E00
	add r5, #0x14
	str r0, [sp, #8]
	add r0, r5, #0
	add r2, r4, #0
	mov r3, #0x28
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021EAB3C: .word 0x0000FFFF
_021EAB40: .word 0x000F0E00
	thumb_func_end MOD75_021EAAE8

	thumb_func_start MOD75_021EAB44
MOD75_021EAB44: ; 0x021EAB44
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r4, r5, #0
	add r0, r1, #0
	add r4, #0x14
	bl TMHMGetMove
	str r0, [sp, #0x10]
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x62
	bl NewString_ReadMsgData
	mov r1, #0
	add r6, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021EAD90 ; =0x000F0E00
	add r2, r6, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x56
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021EAD90 ; =0x000F0E00
	mov r1, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r2, r6, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x59
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021EAD90 ; =0x000F0E00
	add r2, r6, #0
	str r0, [sp, #8]
	add r0, r4, #0
	mov r3, #0x60
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x57
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021EAD90 ; =0x000F0E00
	mov r1, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r2, r6, #0
	mov r3, #0x60
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x58
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021EAD90 ; =0x000F0E00
	mov r1, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r2, r6, #0
	mov r3, #0x60
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	ldr r0, [sp, #0x10]
	mov r1, #0
	bl WazaGetMaxPp
	add r7, r0, #0
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x5a
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	add r2, r7, #0
	mov r3, #2
	bl FUN_0200AD38
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_dtor
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021EAD90 ; =0x000F0E00
	mov r2, #0xfe
	str r0, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	add r0, r4, #0
	mov r3, #0x30
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	mov r1, #2
	bl GetWazaAttr
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	cmp r7, #1
	bhi _021EACBA
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x18
	bl NewString_ReadMsgData
	b _021EACC6
_021EACBA:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x5b
	bl NewString_ReadMsgData
_021EACC6:
	mov r1, #0
	add r6, r0, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r2, r7, #0
	mov r3, #3
	bl FUN_0200AD38
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_dtor
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021EAD90 ; =0x000F0E00
	mov r2, #0xfe
	str r0, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	add r0, r4, #0
	mov r3, #0xa0
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	mov r1, #4
	bl GetWazaAttr
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	bne _021EAD30
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x18
	bl NewString_ReadMsgData
	b _021EAD3C
_021EAD30:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x5b
	bl NewString_ReadMsgData
_021EAD3C:
	mov r1, #0
	add r6, r0, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r2, r7, #0
	mov r3, #3
	bl FUN_0200AD38
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_dtor
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021EAD90 ; =0x000F0E00
	mov r2, #0xfe
	str r0, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	add r0, r4, #0
	mov r3, #0xa0
	bl AddTextPrinterParameterized2
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021EAD90: .word 0x000F0E00
	thumb_func_end MOD75_021EAB44

	thumb_func_start MOD75_021EAD94
MOD75_021EAD94: ; 0x021EAD94
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x26
	bl NewString_ReadMsgData
	mov r1, #0xff
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x25
	bl NewString_ReadMsgData
	mov r1, #1
	lsl r1, r1, #0xa
	str r0, [r4, r1]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD75_021EAD94

	thumb_func_start MOD75_021EADC0
MOD75_021EADC0: ; 0x021EADC0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xff
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl String_dtor
	mov r0, #1
	lsl r0, r0, #0xa
	ldr r0, [r4, r0]
	bl String_dtor
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD75_021EADC0

	thumb_func_start MOD75_021EADDC
MOD75_021EADDC: ; 0x021EADDC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	str r1, [sp, #0x10]
	add r0, #0xc4
	ldr r0, [r0]
	add r4, r2, #0
	add r1, r0, #0
	add r1, #0x64
	ldrb r2, [r1]
	mov r1, #0xc
	add r6, r3, #0
	mul r1, r2
	add r0, r0, r1
	ldrb r0, [r0, #0xc]
	cmp r0, #3
	str r4, [sp]
	bne _021EAE18
	mov r2, #0xff
	str r2, [sp, #4]
	str r6, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	add r0, r5, #4
	mov r3, #0x73
	bl AddTextPrinterParameterized2
	b _021EAE2E
_021EAE18:
	mov r2, #0xff
	str r2, [sp, #4]
	str r6, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	add r0, r5, #4
	mov r3, #0x6d
	bl AddTextPrinterParameterized2
_021EAE2E:
	mov r0, #0xa
	mov r1, #6
	bl String_ctor
	mov r1, #0
	add r7, r0, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, [sp, #0x10]
	mov r3, #3
	bl FUN_0200AD38
	mov r0, #0x46
	mov r2, #1
	lsl r0, r0, #2
	lsl r2, r2, #0xa
	ldr r0, [r5, r0]
	ldr r2, [r5, r2]
	add r1, r7, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r7, #0
	add r2, r0, #0
	bl FUN_02002E14
	add r3, r0, #0
	str r4, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r4, #0x86
	str r6, [sp, #8]
	mov r1, #0
	add r0, r5, #4
	add r2, r7, #0
	sub r3, r4, r3
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD75_021EADDC

	thumb_func_start MOD75_021EAE90
MOD75_021EAE90: ; 0x021EAE90
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r6, r1, #0
	add r4, r2, #0
	add r5, r0, #0
	mov r0, #0x69
	ldrh r2, [r6]
	lsl r0, r0, #2
	cmp r2, r0
	bhs _021EAEDA
	add r1, r0, #0
	sub r1, #0x5d
	sub r1, r2, r1
	lsl r1, r1, #0x10
	lsr r2, r1, #0x10
	mov r1, #2
	str r1, [sp]
	add r3, r5, #4
	str r3, [sp, #4]
	mov r3, #0
	str r3, [sp, #8]
	add r3, r4, #5
	str r3, [sp, #0xc]
	sub r0, #0x94
	ldr r0, [r5, r0]
	add r3, r1, #0
	bl FUN_0200BA78
	lsl r2, r4, #0x10
	ldrh r1, [r6, #2]
	ldr r3, _021EAF08 ; =0x00010200
	add r0, r5, #0
	lsr r2, r2, #0x10
	bl MOD75_021EADDC
	add sp, #0x10
	pop {r4, r5, r6, pc}
_021EAEDA:
	sub r1, r0, #1
	sub r1, r2, r1
	add r2, r5, #4
	str r2, [sp]
	mov r2, #0x10
	str r2, [sp, #4]
	add r2, r4, #5
	str r2, [sp, #8]
	sub r0, #0x94
	lsl r1, r1, #0x10
	ldr r0, [r5, r0]
	lsr r1, r1, #0x10
	mov r2, #2
	mov r3, #1
	bl FUN_0200B9EC
	add r0, r5, #0
	add r1, r4, #0
	bl MOD75_021EAF70
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_021EAF08: .word 0x00010200
	thumb_func_end MOD75_021EAE90

	thumb_func_start MOD75_021EAF0C
MOD75_021EAF0C: ; 0x021EAF0C
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	add r6, r2, #0
	bl ItemToBerryId
	mov r1, #2
	add r2, r0, #0
	str r1, [sp]
	add r0, r5, #4
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r0, r6, #5
	str r0, [sp, #0xc]
	mov r0, #0x11
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r2, r2, #1
	add r3, r1, #0
	bl FUN_0200BA78
	lsl r2, r6, #0x10
	ldrh r1, [r4, #2]
	ldr r3, _021EAF50 ; =0x00010200
	add r0, r5, #0
	lsr r2, r2, #0x10
	bl MOD75_021EADDC
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_021EAF50: .word 0x00010200
	thumb_func_end MOD75_021EAF0C

	thumb_func_start MOD75_021EAF54
MOD75_021EAF54: ; 0x021EAF54
	push {r3, r4, r5, lr}
	add r0, #0xd4
	ldr r0, [r0]
	add r5, r1, #0
	mov r1, #0x26
	mov r2, #6
	bl NARC_AllocAndReadWholeMember
	add r1, r5, #0
	add r4, r0, #0
	bl FUN_020B0030
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD75_021EAF54

	thumb_func_start MOD75_021EAF70
MOD75_021EAF70: ; 0x021EAF70
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r4, r1, #0
	add r1, sp, #0x18
	add r5, r0, #0
	bl MOD75_021EAF54
	add r6, r0, #0
	mov r0, #0x40
	str r0, [sp]
	mov r0, #0x10
	lsl r1, r4, #0x10
	str r0, [sp, #4]
	mov r3, #0
	str r3, [sp, #8]
	lsr r1, r1, #0x10
	str r1, [sp, #0xc]
	mov r1, #0x18
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	add r0, r5, #4
	ldr r1, [r1, #0x14]
	mov r2, #0x28
	bl FUN_02019658
	mov r0, #6
	add r1, r6, #0
	bl FUN_02016A8C
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD75_021EAF70

	thumb_func_start MOD75_021EAFB0
MOD75_021EAFB0: ; 0x021EAFB0
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0x45
	lsl r0, r0, #2
	add r4, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0x29
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r0, #0x88
	str r0, [sp]
	mov r0, #0x10
	mov r1, #0
	lsl r3, r4, #0x10
	str r0, [sp, #4]
	add r0, r5, #4
	add r2, r1, #0
	lsr r3, r3, #0x10
	bl FUN_020196F4
	mov r1, #0
	str r4, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021EB000 ; =0x00010200
	add r2, r6, #0
	str r0, [sp, #8]
	add r0, r5, #4
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_021EB000: .word 0x00010200
	thumb_func_end MOD75_021EAFB0

	thumb_func_start MOD75_021EB004
MOD75_021EB004: ; 0x021EB004
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r4, r1, #0
	add r1, sp, #0x18
	add r5, r0, #0
	bl MOD75_021EAF54
	add r6, r0, #0
	mov r0, #0x40
	str r0, [sp]
	mov r0, #0x10
	mov r2, #0
	str r0, [sp, #4]
	mov r1, #0x60
	str r1, [sp, #8]
	lsl r1, r4, #0x10
	lsr r1, r1, #0x10
	str r1, [sp, #0xc]
	mov r1, #0x28
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	add r0, r5, #4
	ldr r1, [r1, #0x14]
	add r3, r2, #0
	bl FUN_02019658
	mov r0, #6
	add r1, r6, #0
	bl FUN_02016A8C
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD75_021EB004

	thumb_func_start MOD75_021EB048
MOD75_021EB048: ; 0x021EB048
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl NewString_ReadMsgData
	mov r1, #0x49
	lsl r1, r1, #2
	str r0, [r4, r1]
	sub r1, #0x10
	ldr r0, [r4, r1]
	mov r1, #6
	bl NewString_ReadMsgData
	mov r1, #0x4a
	lsl r1, r1, #2
	str r0, [r4, r1]
	sub r1, #0x14
	ldr r0, [r4, r1]
	mov r1, #0x10
	bl NewString_ReadMsgData
	mov r1, #0x4b
	lsl r1, r1, #2
	str r0, [r4, r1]
	sub r1, #0x18
	ldr r0, [r4, r1]
	mov r1, #0x5f
	bl NewString_ReadMsgData
	mov r1, #0x13
	lsl r1, r1, #4
	str r0, [r4, r1]
	sub r1, #0x1c
	ldr r0, [r4, r1]
	mov r1, #0x60
	bl NewString_ReadMsgData
	mov r1, #0x4d
	lsl r1, r1, #2
	str r0, [r4, r1]
	sub r1, #0x20
	ldr r0, [r4, r1]
	mov r1, #1
	bl NewString_ReadMsgData
	mov r1, #0x4e
	lsl r1, r1, #2
	str r0, [r4, r1]
	sub r1, #0x24
	ldr r0, [r4, r1]
	mov r1, #2
	bl NewString_ReadMsgData
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [r4, r1]
	sub r1, #0x28
	ldr r0, [r4, r1]
	mov r1, #0x12
	bl NewString_ReadMsgData
	mov r1, #5
	lsl r1, r1, #6
	str r0, [r4, r1]
	sub r1, #0x2c
	ldr r0, [r4, r1]
	mov r1, #3
	bl NewString_ReadMsgData
	mov r1, #0x51
	lsl r1, r1, #2
	str r0, [r4, r1]
	sub r1, #0x30
	ldr r0, [r4, r1]
	mov r1, #4
	bl NewString_ReadMsgData
	mov r1, #0x52
	lsl r1, r1, #2
	str r0, [r4, r1]
	sub r1, #0x34
	ldr r0, [r4, r1]
	mov r1, #5
	bl NewString_ReadMsgData
	mov r1, #0x53
	lsl r1, r1, #2
	str r0, [r4, r1]
	sub r1, #0x38
	ldr r0, [r4, r1]
	mov r1, #8
	bl NewString_ReadMsgData
	mov r1, #0x15
	lsl r1, r1, #4
	str r0, [r4, r1]
	pop {r4, pc}
	thumb_func_end MOD75_021EB048

	thumb_func_start MOD75_021EB110
MOD75_021EB110: ; 0x021EB110
	push {r4, r5, r6, lr}
	mov r6, #0x49
	add r5, r0, #0
	mov r4, #0
	lsl r6, r6, #2
_021EB11A:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, r6]
	bl String_dtor
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0xc
	blo _021EB11A
	pop {r4, r5, r6, pc}
	thumb_func_end MOD75_021EB110

	thumb_func_start MOD75_021EB130
MOD75_021EB130: ; 0x021EB130
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r5, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r6, r1, #0
	add r1, r0, #0
	add r1, #0x64
	add r7, r2, #0
	ldrb r2, [r1]
	mov r1, #0xc
	mul r1, r2
	add r0, r0, r1
	ldrb r0, [r0, #0xc]
	cmp r0, #4
	bne _021EB180
	lsl r0, r7, #1
	mov r3, #0x17
	sub r1, r3, r0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp]
	mov r1, #8
	lsl r0, r0, #0x18
	str r1, [sp, #4]
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	ldr r0, _021EB338 ; =0x00000337
	add r1, r5, #0
	str r0, [sp, #0x10]
	ldr r0, [r5]
	add r1, #0xb4
	mov r2, #0
	bl FUN_02019064
	mov r0, #4
	str r0, [sp, #0x14]
	b _021EB1B0
_021EB180:
	lsl r0, r7, #1
	mov r1, #0x17
	sub r1, r1, r0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp]
	mov r1, #7
	lsl r0, r0, #0x18
	str r1, [sp, #4]
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	ldr r0, _021EB338 ; =0x00000337
	add r1, r5, #0
	str r0, [sp, #0x10]
	ldr r0, [r5]
	add r1, #0xb4
	mov r2, #0
	mov r3, #0x18
	bl FUN_02019064
	mov r0, #3
	str r0, [sp, #0x14]
_021EB1B0:
	add r0, r7, #0
	mov r1, #6
	bl FUN_02012838
	mov r1, #0x55
	lsl r1, r1, #2
	mov r4, #0
	str r0, [r5, r1]
	cmp r7, #0
	ble _021EB1EC
_021EB1C4:
	ldrb r0, [r6, r4]
	bl MOD75_021E8E10
	ldrb r1, [r6, r4]
	add r2, r0, #0
	mov r0, #0x55
	lsl r1, r1, #2
	add r3, r5, r1
	mov r1, #0x49
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r3, r1]
	bl FUN_020128A0
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, r7
	blt _021EB1C4
_021EB1EC:
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	str r0, [sp, #0x1c]
	add r0, r5, #0
	add r0, #0xb4
	str r0, [sp, #0x20]
	add r0, sp, #0x1c
	strb r1, [r0, #8]
	mov r1, #1
	strb r1, [r0, #9]
	strb r7, [r0, #0xa]
	ldrb r2, [r0, #0xb]
	mov r1, #0xf
	bic r2, r1
	strb r2, [r0, #0xb]
	ldrb r2, [r0, #0xb]
	mov r1, #0x30
	bic r2, r1
	strb r2, [r0, #0xb]
	cmp r7, #4
	ldrb r2, [r0, #0xb]
	blo _021EB228
	mov r1, #0xc0
	bic r2, r1
	mov r1, #0x40
	orr r1, r2
	strb r1, [r0, #0xb]
	b _021EB22E
_021EB228:
	mov r1, #0xc0
	bic r2, r1
	strb r2, [r0, #0xb]
_021EB22E:
	mov r0, #6
	str r0, [sp]
	mov r0, #2
	mov r2, #0
	str r0, [sp, #4]
	add r0, sp, #0x1c
	mov r1, #8
	add r3, r2, #0
	bl FUN_02001B8C
	mov r1, #0x56
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r5, #0
	add r0, #0xc4
	ldr r2, [r0]
	mov r3, #0xc
	add r0, r2, #0
	add r0, #0x64
	ldrb r0, [r0]
	add r1, r0, #0
	mul r1, r3
	add r0, r2, r1
	ldrb r0, [r0, #0xc]
	cmp r0, #3
	bne _021EB298
	add r0, r5, #0
	add r0, #0x14
	mov r1, #0
	bl FUN_02019620
	add r1, r5, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r0, r5, #0
	add r1, #0x66
	ldrh r1, [r1]
	bl MOD75_021EAB44
	add r0, r5, #0
	add r0, #0x14
	bl FUN_02019220
	add r1, r5, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r0, r5, #0
	add r1, #0x66
	ldrh r1, [r1]
	mov r2, #1
	bl MOD75_021EC2B8
	b _021EB31E
_021EB298:
	ldr r0, [sp, #0x14]
	add r4, r5, #4
	lsl r6, r0, #4
	ldr r2, _021EB33C ; =0x000003D9
	add r0, r4, r6
	mov r1, #1
	bl FUN_0200D0BC
	add r0, r4, r6
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x2a
	bl NewString_ReadMsgData
	str r0, [sp, #0x18]
	mov r0, #0x38
	mov r1, #6
	bl String_ctor
	add r7, r0, #0
	add r0, r5, #0
	add r0, #0xc4
	ldr r1, [r0]
	add r0, r1, #4
	add r1, #0x64
	ldrb r2, [r1]
	mov r1, #0xc
	mul r1, r2
	add r1, r0, r1
	ldrh r2, [r1, #6]
	ldrh r1, [r1, #4]
	add r0, r5, #0
	add r1, r2, r1
	sub r1, r1, #1
	mov r2, #0
	bl MOD75_021EAAA8
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, [sp, #0x18]
	add r1, r7, #0
	bl StringExpandPlaceholders
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	add r0, r4, r6
	mov r1, #1
	add r2, r7, #0
	str r3, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r7, #0
	bl String_dtor
	ldr r0, [sp, #0x18]
	bl String_dtor
	add r0, r4, r6
	bl FUN_02019220
_021EB31E:
	add r0, r5, #0
	ldr r2, _021EB340 ; =0x000003F7
	add r0, #0xb4
	mov r1, #1
	mov r3, #0xe
	bl FUN_0200CCA4
	add r5, #0xb4
	add r0, r5, #0
	bl FUN_02019220
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021EB338: .word 0x00000337
_021EB33C: .word 0x000003D9
_021EB340: .word 0x000003F7
	thumb_func_end MOD75_021EB130

	thumb_func_start MOD75_021EB344
MOD75_021EB344: ; 0x021EB344
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, #0xc4
	ldr r2, [r0]
	add r0, r2, #0
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r0, r2, r0
	ldrb r0, [r0, #0xc]
	cmp r0, #4
	bne _021EB362
	mov r1, #4
	b _021EB364
_021EB362:
	mov r1, #3
_021EB364:
	cmp r0, #3
	beq _021EB37A
	lsl r6, r1, #4
	add r4, r5, #4
	add r0, r4, r6
	mov r1, #1
	bl FUN_0200D0E0
	add r0, r4, r6
	bl FUN_0201958C
_021EB37A:
	add r0, r5, #0
	add r0, #0xb4
	mov r1, #1
	bl FUN_0200CCF8
	add r0, r5, #0
	add r0, #0xb4
	bl FUN_0201958C
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02001C5C
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02012870
	add r0, r5, #0
	add r0, #0xb4
	bl FUN_02019178
	add r0, r5, #0
	add r0, #0x14
	mov r1, #0
	bl FUN_02019620
	add r1, r5, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r0, r5, #0
	add r1, #0x66
	ldrh r1, [r1]
	bl MOD75_021EAAE8
	add r0, r5, #0
	add r0, #0x14
	bl FUN_02019220
	mov r1, #0
	add r0, r5, #0
	add r2, r1, #0
	bl MOD75_021EC2B8
	pop {r4, r5, r6, pc}
	thumb_func_end MOD75_021EB344

	thumb_func_start MOD75_021EB3D8
MOD75_021EB3D8: ; 0x021EB3D8
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r0, #0x14
	mov r1, #0
	bl FUN_02019620
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x2d
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r0, #0x82
	mov r1, #6
	bl String_ctor
	ldr r1, _021EB44C ; =0x0000047B
	add r4, r0, #0
	ldrb r1, [r5, r1]
	add r0, r5, #0
	mov r2, #0
	sub r1, r1, #1
	bl MOD75_021EAAA8
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	add r2, r6, #0
	bl StringExpandPlaceholders
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021EB450 ; =0x000F0E00
	add r2, r4, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0x14
	mov r3, #0x28
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r5, #0x14
	add r0, r5, #0
	bl FUN_02019220
	add r0, r4, #0
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021EB44C: .word 0x0000047B
_021EB450: .word 0x000F0E00
	thumb_func_end MOD75_021EB3D8

	thumb_func_start MOD75_021EB454
MOD75_021EB454: ; 0x021EB454
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	ldr r2, _021EB4FC ; =0x000003F7
	add r5, r0, #0
	add r0, #0x94
	mov r1, #1
	mov r3, #0xe
	bl FUN_0200CCA4
	add r0, r5, #0
	bl MOD75_021EB504
	add r0, r5, #0
	ldr r2, _021EB500 ; =0x000003D9
	add r0, #0x34
	mov r1, #1
	mov r3, #0xc
	bl FUN_0200D0BC
	add r0, r5, #0
	add r0, #0x34
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x34
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r0, #0x38
	mov r1, #6
	bl String_ctor
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r2, r0, #4
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r1, r2, r0
	ldrh r2, [r1, #6]
	ldrh r1, [r1, #4]
	add r0, r5, #0
	add r1, r2, r1
	sub r1, r1, #1
	mov r2, #0
	bl MOD75_021EAAA8
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	add r2, r6, #0
	bl StringExpandPlaceholders
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x34
	mov r1, #1
	add r2, r4, #0
	str r3, [sp, #8]
	bl AddTextPrinterParameterized
	add r5, #0x34
	add r0, r5, #0
	bl FUN_02019220
	add r0, r4, #0
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021EB4FC: .word 0x000003F7
_021EB500: .word 0x000003D9
	thumb_func_end MOD75_021EB454

	thumb_func_start MOD75_021EB504
MOD75_021EB504: ; 0x021EB504
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r5, #0
	add r4, #0x94
	add r0, r4, #0
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x54
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, _021EB57C ; =0x00000488
	mov r0, #0x46
	lsl r0, r0, #2
	ldrsh r2, [r5, r2]
	ldr r0, [r5, r0]
	mov r1, #0
	mov r3, #3
	bl FUN_0200AD38
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r6, #0
	bl StringExpandPlaceholders
	mov r0, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	mov r2, #0xfe
	str r1, [sp, #8]
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	add r0, r4, #0
	mov r3, #0x10
	bl AddTextPrinterParameterized
	add r0, r4, #0
	bl FUN_02019220
	add r0, r6, #0
	bl String_dtor
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021EB57C: .word 0x00000488
	thumb_func_end MOD75_021EB504

	thumb_func_start MOD75_021EB580
MOD75_021EB580: ; 0x021EB580
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x34
	mov r1, #1
	bl FUN_0200D0E0
	add r0, r4, #0
	add r0, #0x94
	mov r1, #1
	bl FUN_0200CCF8
	add r0, r4, #0
	add r0, #0x34
	bl FUN_0201958C
	add r0, r4, #0
	add r0, #0x94
	bl FUN_0201958C
	add r4, #0x14
	add r0, r4, #0
	bl FUN_02019220
	pop {r4, pc}
	thumb_func_end MOD75_021EB580

	thumb_func_start MOD75_021EB5B0
MOD75_021EB5B0: ; 0x021EB5B0
	push {r3, r4, r5, lr}
	sub sp, #8
	ldr r2, _021EB654 ; =0x000003D9
	add r5, r0, #0
	add r0, #0x64
	mov r1, #1
	mov r3, #0xc
	bl FUN_0200D0BC
	add r0, r5, #0
	add r0, #0x64
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r2, r0, #4
	add r0, #0x64
	ldrb r1, [r0]
	mov r0, #0xc
	mul r0, r1
	add r1, r2, r0
	ldr r0, _021EB658 ; =0x00000488
	ldrsh r0, [r5, r0]
	cmp r0, #1
	bne _021EB606
	ldrh r2, [r1, #6]
	ldrh r1, [r1, #4]
	add r0, r5, #0
	add r1, r2, r1
	sub r1, r1, #1
	mov r2, #0
	bl MOD75_021EAAA8
	b _021EB616
_021EB606:
	ldrh r2, [r1, #6]
	ldrh r1, [r1, #4]
	add r0, r5, #0
	add r1, r2, r1
	sub r1, r1, #1
	mov r2, #0
	bl MOD75_021EAAC8
_021EB616:
	mov r0, #0
	str r0, [sp]
	mov r1, #1
	mov r0, #0x46
	ldr r2, _021EB658 ; =0x00000488
	str r1, [sp, #4]
	lsl r0, r0, #2
	ldrsh r2, [r5, r2]
	ldr r0, [r5, r0]
	mov r3, #3
	bl FUN_0200AD38
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	bl MOD75_021EB660
	ldr r1, _021EB65C ; =0x00000426
	strb r0, [r5, r1]
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_021EB654: .word 0x000003D9
_021EB658: .word 0x00000488
_021EB65C: .word 0x00000426
	thumb_func_end MOD75_021EB5B0

	thumb_func_start MOD75_021EB660
MOD75_021EB660: ; 0x021EB660
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #1
	bl FUN_02002B60
	mov r0, #0
	bl FUN_02002B7C
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	bl FUN_02024FF4
	mov r3, #0
	str r3, [sp]
	str r0, [sp, #4]
	ldr r0, _021EB69C ; =MOD75_021EB6A0
	mov r2, #0xfe
	str r0, [sp, #8]
	lsl r2, r2, #2
	add r0, r4, #0
	ldr r2, [r4, r2]
	add r0, #0x64
	mov r1, #1
	bl AddTextPrinterParameterized
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_021EB69C: .word MOD75_021EB6A0
	thumb_func_end MOD75_021EB660

	thumb_func_start MOD75_021EB6A0
MOD75_021EB6A0: ; 0x021EB6A0
	push {r3, lr}
	cmp r1, #4
	bhi _021EB6D8
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EB6B2: ; jump table
	.short _021EB6D8 - _021EB6B2 - 2 ; case 0
	.short _021EB6BC - _021EB6B2 - 2 ; case 1
	.short _021EB6C2 - _021EB6B2 - 2 ; case 2
	.short _021EB6C8 - _021EB6B2 - 2 ; case 3
	.short _021EB6D0 - _021EB6B2 - 2 ; case 4
_021EB6BC:
	bl FUN_02005514
	pop {r3, pc}
_021EB6C2:
	bl FUN_02005CBC
	pop {r3, pc}
_021EB6C8:
	ldr r0, _021EB6DC ; =0x0000060D
	bl FUN_020054C8
	b _021EB6D8
_021EB6D0:
	ldr r0, _021EB6DC ; =0x0000060D
	bl FUN_02005508
	pop {r3, pc}
_021EB6D8:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_021EB6DC: .word 0x0000060D
	thumb_func_end MOD75_021EB6A0

	thumb_func_start MOD75_021EB6E0
MOD75_021EB6E0: ; 0x021EB6E0
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #6
	str r0, [sp]
	ldr r0, [r4]
	ldr r1, _021EB700 ; =0x021EC6AC
	ldr r2, _021EB704 ; =0x000003F7
	mov r3, #0xe
	bl FUN_02002198
	mov r1, #0x56
	lsl r1, r1, #2
	str r0, [r4, r1]
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_021EB700: .word MOD75_021EC6AC
_021EB704: .word 0x000003F7
	thumb_func_end MOD75_021EB6E0

	thumb_func_start MOD75_021EB708
MOD75_021EB708: ; 0x021EB708
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r5, #0
	add r4, #0x74
	cmp r1, #0
	bne _021EB722
	ldr r2, _021EB7FC ; =0x000003F7
	add r0, r4, #0
	mov r1, #1
	mov r3, #0xe
	bl FUN_0200CCA4
_021EB722:
	add r0, r4, #0
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x50
	bl NewString_ReadMsgData
	mov r3, #2
	add r6, r0, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, _021EB800 ; =0x00000488
	mov r0, #0x46
	lsl r0, r0, #2
	ldrsh r2, [r5, r2]
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_0200AD38
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r6, #0
	bl StringExpandPlaceholders
	mov r0, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	mov r2, #0xfe
	str r1, [sp, #8]
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	add r0, r4, #0
	add r3, r1, #0
	bl AddTextPrinterParameterized
	add r0, r6, #0
	bl String_dtor
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x51
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r2, _021EB804 ; =0x0000048C
	mov r0, #0x46
	ldr r3, [r5, r2]
	sub r2, r2, #4
	ldrsh r2, [r5, r2]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mul r2, r3
	mov r1, #0
	mov r3, #6
	bl FUN_0200AD38
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r6, #0
	bl StringExpandPlaceholders
	mov r1, #0xfe
	lsl r1, r1, #2
	mov r0, #0
	ldr r1, [r5, r1]
	add r2, r0, #0
	bl FUN_02002E14
	add r3, r0, #0
	mov r0, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	mov r2, #0xfe
	str r1, [sp, #8]
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	mov r5, #0x60
	add r0, r4, #0
	sub r3, r5, r3
	bl AddTextPrinterParameterized
	add r0, r4, #0
	bl FUN_02019220
	add r0, r6, #0
	bl String_dtor
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021EB7FC: .word 0x000003F7
_021EB800: .word 0x00000488
_021EB804: .word 0x0000048C
	thumb_func_end MOD75_021EB708

	thumb_func_start MOD75_021EB808
MOD75_021EB808: ; 0x021EB808
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r5, #0
	add r4, #0x84
	cmp r1, #0
	bne _021EB854
	add r0, r4, #0
	mov r1, #0xf
	bl FUN_02019620
	ldr r2, _021EB8E4 ; =0x000003F7
	add r0, r4, #0
	mov r1, #1
	mov r3, #0xe
	bl FUN_0200CCA4
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x4e
	bl NewString_ReadMsgData
	mov r1, #0
	add r6, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	add r0, r4, #0
	add r2, r6, #0
	add r3, r1, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r6, #0
	bl String_dtor
	b _021EB866
_021EB854:
	mov r0, #0x50
	str r0, [sp]
	mov r3, #0x10
	add r0, r4, #0
	mov r1, #0xf
	mov r2, #0
	str r3, [sp, #4]
	bl FUN_020196F4
_021EB866:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x4f
	bl NewString_ReadMsgData
	add r6, r0, #0
	add r0, r5, #0
	add r0, #0xcc
	ldr r0, [r0]
	bl PlayerData_GetMoney
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	mov r3, #6
	bl FUN_0200AD38
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r6, #0
	bl StringExpandPlaceholders
	mov r1, #0xfe
	lsl r1, r1, #2
	mov r0, #0
	ldr r1, [r5, r1]
	add r2, r0, #0
	bl FUN_02002E14
	add r3, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	mov r2, #0xfe
	str r1, [sp, #8]
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	mov r5, #0x50
	add r0, r4, #0
	sub r3, r5, r3
	bl AddTextPrinterParameterized
	add r0, r4, #0
	bl FUN_02019220
	add r0, r6, #0
	bl String_dtor
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021EB8E4: .word 0x000003F7
	thumb_func_end MOD75_021EB808

	thumb_func_start MOD75_021EB8E8
MOD75_021EB8E8: ; 0x021EB8E8
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r5, #0
	add r4, #0xa4
	add r0, r4, #0
	mov r1, #0xf
	bl FUN_02019620
	ldr r2, _021EB9B0 ; =0x000003F7
	add r0, r4, #0
	mov r1, #1
	mov r3, #0xe
	bl FUN_0200CCA4
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x6c
	bl NewString_ReadMsgData
	mov r1, #0
	add r6, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	add r0, r4, #0
	add r2, r6, #0
	add r3, r1, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r6, #0
	bl String_dtor
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x6d
	bl NewString_ReadMsgData
	add r6, r0, #0
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	ldr r0, [r0]
	bl FUN_02028048
	bl FUN_020281B8
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	mov r3, #3
	bl FUN_0200AD38
	mov r0, #0x46
	mov r1, #0xfe
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_dtor
	mov r1, #0xfe
	lsl r1, r1, #2
	mov r0, #0
	ldr r1, [r5, r1]
	add r2, r0, #0
	bl FUN_02002E14
	add r3, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	mov r2, #0xfe
	str r1, [sp, #8]
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	mov r5, #0x58
	add r0, r4, #0
	sub r3, r5, r3
	bl AddTextPrinterParameterized
	add r0, r4, #0
	bl FUN_02019220
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021EB9B0: .word 0x000003F7
	thumb_func_end MOD75_021EB8E8

	thumb_func_start MOD75_021EB9B4
MOD75_021EB9B4: ; 0x021EB9B4
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	mov r0, #0x20
	mov r1, #6
	bl FUN_0201C24C
	add r0, r4, #0
	bl MOD75_021EB9E4
	add r0, r4, #0
	bl MOD75_021EBA80
	add r0, r4, #0
	bl MOD75_021EBEAC
	pop {r4, pc}
	thumb_func_end MOD75_021EB9B4

	thumb_func_start MOD75_021EB9E4
MOD75_021EB9E4: ; 0x021EB9E4
	push {r3, r4, r5, r6, lr}
	sub sp, #0x4c
	ldr r3, _021EBA74 ; =0x021EC6D4
	add r2, sp, #0x34
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	mov r0, #6
	bl FUN_0200BB14
	add r1, r4, #0
	add r1, #0xd8
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xd8
	ldr r0, [r0]
	bl FUN_0200BB34
	add r1, r4, #0
	add r1, #0xdc
	add r2, sp, #0x14
	ldr r5, _021EBA78 ; =0x021EC6EC
	str r0, [r1]
	ldmia r5!, {r0, r1}
	add r3, r2, #0
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	ldr r6, _021EBA7C ; =0x021EC6C0
	stmia r2!, {r0, r1}
	add r5, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r5, #0
	stmia r5!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	add r1, r3, #0
	str r0, [r5]
	add r0, r4, #0
	add r0, #0xd8
	ldr r0, [r0]
	mov r3, #0x20
	bl FUN_0200BB6C
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xc
	bl FUN_0200BBF0
	add r0, r4, #0
	add r0, #0xd8
	add r4, #0xdc
	ldr r0, [r0]
	ldr r1, [r4]
	add r2, sp, #0x34
	bl FUN_0200BF60
	add sp, #0x4c
	pop {r3, r4, r5, r6, pc}
	nop
_021EBA74: .word MOD75_021EC6D4
_021EBA78: .word MOD75_021EC6EC
_021EBA7C: .word MOD75_021EC6C0
	thumb_func_end MOD75_021EB9E4

	thumb_func_start MOD75_021EBA80
MOD75_021EBA80: ; 0x021EBA80
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, _021EBE38 ; =0x00000425
	ldrb r0, [r5, r0]
	cmp r0, #0
	bne _021EBA94
	mov r3, #2
	mov r4, #3
	b _021EBA98
_021EBA94:
	mov r3, #0x22
	mov r4, #0x23
_021EBA98:
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _021EBE3C ; =0x0000C0F9
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	bl FUN_0200C00C
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _021EBE40 ; =0x0000C0FA
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #0x15
	bl FUN_0200C00C
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _021EBE44 ; =0x0000C0FB
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #0x18
	bl FUN_0200C00C
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _021EBE48 ; =0x0000C0FC
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #0x1b
	bl FUN_0200C00C
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _021EBE4C ; =0x0000C0FD
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #6
	bl FUN_0200C00C
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _021EBE50 ; =0x0000C0FE
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #0x1e
	bl FUN_0200C00C
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0xc1
	lsl r0, r0, #8
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x3e
	mov r3, #4
	bl FUN_0200C00C
	mov r0, #0
	mov r1, #1
	bl GetItemIndexMapping
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _021EBE54 ; =0x0000C0FF
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x10
	bl FUN_0200C00C
	ldr r0, _021EBE58 ; =0x0000C101
	add r1, r5, #0
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #1
	mov r3, #0
	bl FUN_0206E130
	ldr r0, _021EBE5C ; =0x0000C102
	add r1, r5, #0
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #1
	mov r3, #0
	bl FUN_0206E2AC
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, _021EBE3C ; =0x0000C0F9
	add r1, r5, #0
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	add r3, r4, #0
	bl FUN_0200C06C
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, _021EBE40 ; =0x0000C0FA
	add r1, r5, #0
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #0x10
	bl FUN_0200C06C
	mov r0, #0
	mov r1, #2
	bl GetItemIndexMapping
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, _021EBE48 ; =0x0000C0FC
	add r1, r5, #0
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x10
	bl FUN_0200C06C
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, _021EBE4C ; =0x0000C0FD
	add r1, r5, #0
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x3e
	mov r3, #0xa
	bl FUN_0200C06C
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r3, _021EBE50 ; =0x0000C0FE
	mov r2, #1
	bl FUN_0206E164
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	ldr r0, _021EBE44 ; =0x0000C0FB
	add r1, r5, #0
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #0x1f
	bl FUN_0200C06C
	mov r0, #0
	str r0, [sp]
	ldr r0, _021EBE3C ; =0x0000C0F9
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #1
	bl FUN_0200C124
	mov r0, #0
	str r0, [sp]
	ldr r0, _021EBE40 ; =0x0000C0FA
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #0x14
	bl FUN_0200C124
	mov r0, #0
	str r0, [sp]
	ldr r0, _021EBE44 ; =0x0000C0FB
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #0x17
	bl FUN_0200C124
	mov r0, #0
	str r0, [sp]
	ldr r0, _021EBE48 ; =0x0000C0FC
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #0x1a
	bl FUN_0200C124
	mov r0, #0
	str r0, [sp]
	ldr r0, _021EBE4C ; =0x0000C0FD
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #5
	bl FUN_0200C124
	mov r0, #0
	str r0, [sp]
	ldr r0, _021EBE50 ; =0x0000C0FE
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #0x1d
	bl FUN_0200C124
	bl FUN_0206E708
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _021EBE54 ; =0x0000C0FF
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x10
	bl FUN_0200C124
	mov r0, #0
	str r0, [sp]
	mov r0, #0xc1
	lsl r0, r0, #8
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x3e
	mov r3, #5
	bl FUN_0200C124
	mov r3, #0
	add r1, r5, #0
	ldr r0, _021EBE3C ; =0x0000C0F9
	str r3, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	bl FUN_0200C13C
	mov r0, #0
	str r0, [sp]
	ldr r0, _021EBE40 ; =0x0000C0FA
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #0x13
	bl FUN_0200C13C
	mov r0, #0
	str r0, [sp]
	ldr r0, _021EBE44 ; =0x0000C0FB
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #0x16
	bl FUN_0200C13C
	mov r0, #0
	str r0, [sp]
	ldr r0, _021EBE48 ; =0x0000C0FC
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #0x19
	bl FUN_0200C13C
	mov r0, #0
	str r0, [sp]
	ldr r0, _021EBE4C ; =0x0000C0FD
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #4
	bl FUN_0200C13C
	mov r0, #0
	str r0, [sp]
	ldr r0, _021EBE50 ; =0x0000C0FE
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xd
	mov r3, #0x1c
	bl FUN_0200C13C
	bl FUN_0206E70C
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _021EBE54 ; =0x0000C0FF
	b _021EBE60
	nop
_021EBE38: .word 0x00000425
_021EBE3C: .word 0x0000C0F9
_021EBE40: .word 0x0000C0FA
_021EBE44: .word 0x0000C0FB
_021EBE48: .word 0x0000C0FC
_021EBE4C: .word 0x0000C0FD
_021EBE50: .word 0x0000C0FE
_021EBE54: .word 0x0000C0FF
_021EBE58: .word 0x0000C101
_021EBE5C: .word 0x0000C102
_021EBE60:
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x10
	bl FUN_0200C13C
	mov r0, #0
	str r0, [sp]
	mov r0, #0xc1
	lsl r0, r0, #8
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x3e
	mov r3, #6
	bl FUN_0200C13C
	add r0, r5, #0
	add r0, #0xd8
	add r5, #0xdc
	ldr r2, _021EBEA8 ; =0x0000C101
	ldr r0, [r0]
	ldr r1, [r5]
	add r3, r2, #0
	bl FUN_0206E1D4
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_021EBEA8: .word 0x0000C101
	thumb_func_end MOD75_021EBA80

	thumb_func_start MOD75_021EBEAC
MOD75_021EBEAC: ; 0x021EBEAC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r4, _021EBFD8 ; =0x021EC70C
	mov r7, #0
	add r6, r5, #0
_021EBEB8:
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, r4, #0
	bl FUN_0200C154
	add r1, r6, #0
	add r1, #0xe0
	add r7, r7, #1
	str r0, [r1]
	add r4, #0x34
	add r6, r6, #4
	cmp r7, #0xc
	blo _021EBEB8
	add r0, r5, #0
	add r0, #0xf4
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0200C644
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0200C644
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_0200C644
	mov r0, #0x43
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_0200C644
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r0, #0x65
	ldrb r0, [r0]
	add r0, #0xfc
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #1
	bhi _021EBF2A
	add r0, r5, #0
	add r0, #0xe4
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0200C644
_021EBF2A:
	ldr r0, _021EBFDC ; =0x00000424
	ldrb r0, [r5, r0]
	cmp r0, #1
	bne _021EBF4A
	add r0, r5, #0
	add r0, #0xe8
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0200C644
	add r0, r5, #0
	add r0, #0xec
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0200C644
_021EBF4A:
	add r0, r5, #0
	mov r1, #0
	bl MOD75_021EC298
	add r0, r5, #0
	add r0, #0xc4
	ldr r1, [r0]
	add r0, r5, #0
	add r2, r1, #0
	add r2, #0x64
	ldrb r3, [r2]
	mov r2, #0xc
	add r0, #0xe0
	mul r2, r3
	add r1, r1, r2
	ldrb r1, [r1, #0xc]
	ldr r0, [r0]
	bl FUN_0200C5C0
	add r1, r5, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r0, r5, #0
	add r1, #0x64
	ldrb r1, [r1]
	bl MOD75_021EC18C
	add r1, r0, #0
	add r0, r5, #0
	add r0, #0xe4
	ldr r0, [r0]
	mov r2, #0x61
	bl FUN_0200C714
	add r0, r5, #0
	add r0, #0xc4
	ldr r2, [r0]
	add r0, r5, #0
	add r3, r2, #0
	add r3, #0x64
	ldrb r4, [r3]
	mov r3, #0xc
	add r0, #0xf0
	mul r3, r4
	add r2, r2, r3
	ldrh r2, [r2, #8]
	ldr r0, [r0]
	mov r1, #0xb1
	sub r2, r2, #1
	lsl r2, r2, #4
	add r2, #0x18
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	ldr r4, _021EBFE0 ; =0x021EC6B4
	add r3, sp, #0
	ldmia r4!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	add r1, r2, #0
	add r5, #0xe0
	str r0, [r3]
	ldr r0, [r5]
	mov r2, #2
	ldr r0, [r0]
	bl FUN_02020074
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021EBFD8: .word MOD75_021EC70C
_021EBFDC: .word 0x00000424
_021EBFE0: .word MOD75_021EC6B4
	thumb_func_end MOD75_021EBEAC

	thumb_func_start MOD75_021EBFE4
MOD75_021EBFE4: ; 0x021EBFE4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_021EBFEC:
	add r0, r5, #0
	add r0, #0xe0
	ldr r0, [r0]
	bl FUN_0200C3DC
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xc
	blo _021EBFEC
	add r0, r6, #0
	add r1, r6, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	bl FUN_0200C398
	add r6, #0xd8
	ldr r0, [r6]
	bl FUN_0200BD04
	pop {r4, r5, r6, pc}
	thumb_func_end MOD75_021EBFE4

	thumb_func_start MOD75_021EC018
MOD75_021EC018: ; 0x021EC018
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_021EC01E:
	add r0, r5, #0
	add r0, #0xe0
	ldr r0, [r0]
	bl FUN_0200C5A8
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xc
	blo _021EC01E
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD75_021EC018

	thumb_func_start MOD75_021EC034
MOD75_021EC034: ; 0x021EC034
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl GetItemIndexMapping
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _021EC088 ; =0x0000C0FF
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x10
	bl FUN_0200C9D8
	add r0, r4, #0
	mov r1, #2
	bl GetItemIndexMapping
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _021EC08C ; =0x0000C0FC
	mov r2, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r5, #0xdc
	ldr r0, [r0]
	ldr r1, [r5]
	bl FUN_0200CA0C
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_021EC088: .word 0x0000C0FF
_021EC08C: .word 0x0000C0FC
	thumb_func_end MOD75_021EC034

	thumb_func_start MOD75_021EC090
MOD75_021EC090: ; 0x021EC090
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0xf0
	ldr r0, [r0]
	add r4, r1, #0
	bl FUN_0200C66C
	add r5, #0xe4
	ldr r0, [r5]
	add r1, r4, #0
	bl FUN_0200C66C
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD75_021EC090

	thumb_func_start MOD75_021EC0AC
MOD75_021EC0AC: ; 0x021EC0AC
	ldr r1, _021EC0C0 ; =0x00000454
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _021EC0B8
	mov r0, #1
	b _021EC0BA
_021EC0B8:
	mov r0, #0
_021EC0BA:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
	.align 2, 0
_021EC0C0: .word 0x00000454
	thumb_func_end MOD75_021EC0AC

	thumb_func_start MOD75_021EC0C4
MOD75_021EC0C4: ; 0x021EC0C4
	ldr r1, _021EC0D4 ; =0x00000457
	mov r2, #0
	strb r2, [r0, r1]
	ldr r3, _021EC0D8 ; =MOD75_021EC1A4
	mov r2, #1
	sub r1, r1, #3
	strb r2, [r0, r1]
	bx r3
	.align 2, 0
_021EC0D4: .word 0x00000457
_021EC0D8: .word MOD75_021EC1A4
	thumb_func_end MOD75_021EC0C4

	thumb_func_start MOD75_021EC0DC
MOD75_021EC0DC: ; 0x021EC0DC
	push {r3, lr}
	ldr r1, _021EC0F0 ; =0x00000454
	ldrb r1, [r0, r1]
	cmp r1, #0
	beq _021EC0EE
	cmp r1, #1
	bne _021EC0EE
	bl MOD75_021EC0F4
_021EC0EE:
	pop {r3, pc}
	.align 2, 0
_021EC0F0: .word 0x00000454
	thumb_func_end MOD75_021EC0DC

	thumb_func_start MOD75_021EC0F4
MOD75_021EC0F4: ; 0x021EC0F4
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r0, #0xe4
	ldr r0, [r0]
	ldr r0, [r0]
	bl FUN_0202011C
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r2, _021EC180 ; =0x00000455
	ldrb r0, [r4, r2]
	cmp r0, #0
	bne _021EC12C
	add r1, r2, #2
	ldrb r1, [r4, r1]
	ldr r0, [sp]
	lsl r1, r1, #2
	add r3, r4, r1
	add r1, r2, #3
	ldr r1, [r3, r1]
	sub r0, r0, r1
	str r0, [sp]
	b _021EC13E
_021EC12C:
	add r1, r2, #2
	ldrb r1, [r4, r1]
	ldr r0, [sp]
	lsl r1, r1, #2
	add r3, r4, r1
	add r1, r2, #3
	ldr r1, [r3, r1]
	add r0, r0, r1
	str r0, [sp]
_021EC13E:
	add r0, r4, #0
	add r0, #0xe4
	ldr r0, [r0]
	add r1, sp, #0
	ldr r0, [r0]
	bl FUN_02020044
	ldr r1, _021EC184 ; =0x00000457
	ldrb r0, [r4, r1]
	add r0, r0, #1
	strb r0, [r4, r1]
	ldrb r0, [r4, r1]
	cmp r0, #8
	bne _021EC17C
	add r1, #0x21
	ldrb r1, [r4, r1]
	add r0, r4, #0
	bl MOD75_021EC18C
	lsl r0, r0, #0xc
	str r0, [sp]
	add r0, r4, #0
	add r0, #0xe4
	ldr r0, [r0]
	add r1, sp, #0
	ldr r0, [r0]
	bl FUN_02020044
	ldr r0, _021EC188 ; =0x00000454
	mov r1, #0
	strb r1, [r4, r0]
_021EC17C:
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_021EC180: .word 0x00000455
_021EC184: .word 0x00000457
_021EC188: .word 0x00000454
	thumb_func_end MOD75_021EC0F4

	thumb_func_start MOD75_021EC18C
MOD75_021EC18C: ; 0x021EC18C
	ldr r2, _021EC1A0 ; =0x00000427
	ldrb r3, [r0, r2]
	add r2, r2, #1
	ldrb r0, [r0, r2]
	mul r1, r0
	add r0, r3, r1
	add r0, r0, #6
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
	.align 2, 0
_021EC1A0: .word 0x00000427
	thumb_func_end MOD75_021EC18C

	thumb_func_start MOD75_021EC1A4
MOD75_021EC1A4: ; 0x021EC1A4
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r0, #0xe4
	ldr r0, [r0]
	ldr r0, [r0]
	bl FUN_0202011C
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r1, _021EC240 ; =0x00000478
	str r0, [r2]
	ldrb r1, [r4, r1]
	add r0, r4, #0
	bl MOD75_021EC18C
	lsl r1, r0, #0xc
	ldr r0, [sp]
	cmp r1, r0
	bge _021EC1DE
	sub r0, r0, r1
	mov r1, #0x64
	bl _s32_div_f
	mov r2, #0
	b _021EC1E8
_021EC1DE:
	sub r0, r1, r0
	mov r1, #0x64
	bl _s32_div_f
	mov r2, #1
_021EC1E8:
	ldr r1, _021EC244 ; =0x00000455
	mov r3, #0x28
	strb r2, [r4, r1]
	add r5, r0, #0
	ldr r1, _021EC248 ; =0x00000458
	mov r2, #0
	mul r5, r3
	str r2, [r4, r1]
	add r3, r1, #4
	str r5, [r4, r3]
	mov r3, #0x19
	add r5, r0, #0
	mul r5, r3
	add r3, r1, #0
	add r3, #8
	str r5, [r4, r3]
	mov r3, #0xf
	add r5, r0, #0
	mul r5, r3
	add r3, r1, #0
	add r3, #0xc
	str r5, [r4, r3]
	mov r3, #0xa
	add r5, r0, #0
	mul r5, r3
	add r3, r1, #0
	add r3, #0x10
	str r5, [r4, r3]
	mov r3, #7
	add r5, r0, #0
	mul r5, r3
	add r3, r1, #0
	add r3, #0x14
	str r5, [r4, r3]
	lsl r3, r0, #1
	add r3, r0, r3
	add r0, r1, #0
	add r0, #0x18
	str r3, [r4, r0]
	add r1, #0x1c
	str r2, [r4, r1]
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_021EC240: .word 0x00000478
_021EC244: .word 0x00000455
_021EC248: .word 0x00000458
	thumb_func_end MOD75_021EC1A4

	thumb_func_start MOD75_021EC24C
MOD75_021EC24C: ; 0x021EC24C
	push {r4, lr}
	add r4, r0, #0
	cmp r1, #0
	bne _021EC272
	mov r0, #1
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	mov r1, #0xdc
	mov r2, #0x9c
	bl FUN_0200C714
	mov r0, #0x41
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xdc
	mov r2, #0xb4
	bl FUN_0200C714
	b _021EC28E
_021EC272:
	mov r0, #1
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	mov r1, #0xa2
	mov r2, #0x6c
	bl FUN_0200C714
	mov r0, #0x41
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xa2
	mov r2, #0x84
	bl FUN_0200C714
_021EC28E:
	add r0, r4, #0
	mov r1, #1
	bl MOD75_021EC298
	pop {r4, pc}
	thumb_func_end MOD75_021EC24C

	thumb_func_start MOD75_021EC298
MOD75_021EC298: ; 0x021EC298
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #1
	lsl r0, r0, #8
	ldr r0, [r5, r0]
	add r4, r1, #0
	bl FUN_0200C644
	mov r0, #0x41
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_0200C644
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD75_021EC298

	thumb_func_start MOD75_021EC2B8
MOD75_021EC2B8: ; 0x021EC2B8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0x42
	lsl r0, r0, #2
	add r4, r2, #0
	add r6, r1, #0
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_0200C644
	mov r0, #0x43
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_0200C644
	cmp r4, #0
	beq _021EC374
	add r0, r6, #0
	bl TMHMGetMove
	mov r1, #3
	add r4, r0, #0
	bl GetWazaAttr
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r0, r4, #0
	mov r1, #1
	bl GetWazaAttr
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	bl FUN_0206E12C
	add r7, r0, #0
	add r0, r6, #0
	bl FUN_0206E0F0
	add r3, r0, #0
	mov r0, #1
	str r0, [sp]
	ldr r0, _021EC378 ; =0x0000C101
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, r7, #0
	bl FUN_0200C9D8
	add r0, r6, #0
	bl FUN_0206E114
	add r1, r0, #0
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r1, #6
	bl FUN_0200C66C
	bl FUN_0206E2A8
	add r6, r0, #0
	add r0, r4, #0
	bl FUN_0206E278
	add r3, r0, #0
	mov r0, #1
	str r0, [sp]
	ldr r0, _021EC37C ; =0x0000C102
	add r1, r5, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, r6, #0
	bl FUN_0200C9D8
	add r0, r4, #0
	bl FUN_0206E290
	add r1, r0, #0
	mov r0, #0x43
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r1, #6
	bl FUN_0200C66C
_021EC374:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021EC378: .word 0x0000C101
_021EC37C: .word 0x0000C102
	thumb_func_end MOD75_021EC2B8

	thumb_func_start MOD75_021EC380
MOD75_021EC380: ; 0x021EC380
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, #0xf8
	add r4, r1, #0
	ldr r0, [r0]
	mov r1, #1
	add r6, r2, #0
	bl FUN_0200C644
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	add r1, r4, #0
	add r2, r6, #0
	bl FUN_0200C714
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0200C61C
	add r5, #0xf8
	ldr r0, [r5]
	mov r1, #0
	bl FUN_0200C5C0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD75_021EC380

	thumb_func_start MOD75_021EC3B8
MOD75_021EC3B8: ; 0x021EC3B8
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xf8
	ldr r0, [r0]
	bl FUN_0200C658
	cmp r0, #1
	bne _021EC3EE
	add r0, r4, #0
	add r0, #0xf8
	mov r1, #1
	ldr r0, [r0]
	lsl r1, r1, #0xc
	bl FUN_0200C5B4
	add r0, r4, #0
	add r0, #0xf8
	ldr r0, [r0]
	bl FUN_0200C630
	cmp r0, #2
	bne _021EC3EE
	add r4, #0xf8
	ldr r0, [r4]
	mov r1, #0
	bl FUN_0200C644
_021EC3EE:
	pop {r4, pc}
	thumb_func_end MOD75_021EC3B8

	.rodata
	.global MOD75_021EC3F0
MOD75_021EC3F0: ; 0x021EC3F0
	.byte 0x11, 0x12, 0x00, 0x00

	.global MOD75_021EC3F4
MOD75_021EC3F4: ; 0x021EC3F4
	.byte 0x38, 0x67, 0x68, 0x97, 0xFF, 0x00, 0x00, 0x00

	.global MOD75_021EC3FC
MOD75_021EC3FC: ; 0x021EC3FC
	.byte 0x90, 0xB7, 0x88, 0xAF, 0xFF, 0x00, 0x00, 0x00

	.global MOD75_021EC404
MOD75_021EC404: ; 0x021EC404
	.byte 0xFE, 0x80, 0x50, 0x1A, 0xFE, 0x80, 0x50, 0x40, 0xFF, 0x00, 0x00, 0x00

	.global MOD75_021EC410
MOD75_021EC410: ; 0x021EC410
	.byte 0xFE, 0x80, 0x50, 0x10, 0xFE, 0x80, 0x50, 0x50, 0xFF, 0x00, 0x00, 0x00

	.global MOD75_021EC41C
MOD75_021EC41C: ; 0x021EC41C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD75_021EC42C
MOD75_021EC42C: ; 0x021EC42C
	.byte 0x20, 0x47, 0x08, 0x2F, 0x78, 0x9F, 0x28, 0x4F, 0x78, 0x9F, 0xB0, 0xD7, 0x20, 0x47, 0xD0, 0xF7
	.byte 0xFF, 0x00, 0x00, 0x00

	.global MOD75_021EC440
MOD75_021EC440: ; 0x021EC440
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD75_021EC45C
MOD75_021EC45C: ; 0x021EC45C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD75_021EC478
MOD75_021EC478: ; 0x021EC478
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD75_021EC494
MOD75_021EC494: ; 0x021EC494
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1D, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD75_021EC4B0
MOD75_021EC4B0: ; 0x021EC4B0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD75_021EC4CC
MOD75_021EC4CC: ; 0x021EC4CC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x1D, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD75_021EC4E8
MOD75_021EC4E8: ; 0x021EC4E8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1C, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD75_021EC504
MOD75_021EC504: ; 0x021EC504
	.word 0x00000000, MOD75_021E7870, MOD75_021E797C, 0x00000000
	.byte 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00

	.global MOD75_021EC524
MOD75_021EC524: ; 0x021EC524
	.byte 0x50, 0x77, 0x10, 0x37, 0x78, 0x9F, 0x28, 0x4F, 0x90, 0xB7, 0x50, 0x77, 0x90, 0xB7, 0x88, 0xAF
	.byte 0x78, 0x9F, 0xB0, 0xD7, 0x50, 0x77, 0xC8, 0xEF, 0x20, 0x47, 0xD0, 0xF7, 0xFF, 0x00, 0x00, 0x00

	.global MOD75_021EC544
MOD75_021EC544: ; 0x021EC544
	.byte 0x20, 0x47, 0x08, 0x2F, 0x50, 0x77, 0x10, 0x37, 0x78, 0x9F, 0x28, 0x4F, 0x90, 0xB7, 0x50, 0x77
	.byte 0x90, 0xB7, 0x88, 0xAF, 0x78, 0x9F, 0xB0, 0xD7, 0x50, 0x77, 0xC8, 0xEF, 0x20, 0x47, 0xD0, 0xF7
	.byte 0xFF, 0x00, 0x00, 0x00

	.global MOD75_021EC568
MOD75_021EC568: ; 0x021EC568
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD75_021EC590
MOD75_021EC590: ; 0x021EC590
	.word MOD75_021E8E1C, MOD75_021E8E1C, MOD75_021E8E1C, MOD75_021E8E1C
	.word MOD75_021E8E1C, MOD75_021E947C, MOD75_021E97A8, MOD75_021E97E4
	.word MOD75_021E9818, MOD75_021E943C, MOD75_021E945C, 0xFFFFFFFE

	.global MOD75_021EC5C0
MOD75_021EC5C0: ; 0x021EC5C0
	.byte 0x77, 0x10, 0x78, 0x10, 0x78, 0x10, 0x79, 0x10, 0x26, 0x10, 0x10, 0x10, 0x11, 0x10, 0x11, 0x10
	.byte 0x12, 0x10, 0x13, 0x10, 0x14, 0x10, 0x01, 0x10, 0x01, 0x10, 0x01, 0x10, 0x34, 0x10, 0x14, 0x10
	.byte 0x01, 0x10, 0x01, 0x10, 0x01, 0x10, 0x34, 0x10, 0x30, 0x10, 0x31, 0x10, 0x31, 0x10, 0x32, 0x10
	.byte 0x33, 0x10

	.global MOD75_021EC5F2
MOD75_021EC5F2: ; 0x021EC5F2
	.byte 0x26, 0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x26, 0x10, 0x02, 0x10, 0x02, 0x10
	.byte 0x02, 0x10, 0x02, 0x10, 0x26, 0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x26, 0x10
	.byte 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x26, 0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10
	.byte 0x02, 0x10

	.global MOD75_021EC624
MOD75_021EC624: ; 0x021EC624
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD75_021EC628
MOD75_021EC628: ; 0x021EC628
	.word 0x00000000, MOD75_021EC3F0, MOD75_021EC3FC, 0x00000000
	.word 0x00000000, 0x00000000, 0x00000000, MOD75_021EC66C
	.word MOD75_021EC42C, 0x00000000, 0x00000000, 0x00000000
	.word 0x00000000, MOD75_021EC67C, MOD75_021EC524, MOD75_021EC69C
	.word MOD75_021EC544

	.global MOD75_021EC66C
MOD75_021EC66C: ; 0x021EC66C
	.byte 0x01, 0x04, 0x05, 0x0F, 0x16, 0x0F, 0x1A, 0x04

	.global MOD75_021EC674
MOD75_021EC674: ; 0x021EC674
	.byte 0xA5, 0x28, 0x0F, 0x64, 0x40, 0x0C, 0x1E, 0x32

	.global MOD75_021EC67C
MOD75_021EC67C: ; 0x021EC67C
	.byte 0x02, 0x0A, 0x05, 0x0F, 0x0A, 0x12, 0x11, 0x12
	.byte 0x16, 0x0F, 0x19, 0x0A, 0x1A, 0x04, 0x00, 0x00

	.global MOD75_021EC68C
MOD75_021EC68C: ; 0x021EC68C
	.word MOD75_021E6BA0, MOD75_021E6D6C, MOD75_021E6F00, 0xFFFFFFFF

	.global MOD75_021EC69C
MOD75_021EC69C: ; 0x021EC69C
	.byte 0x01, 0x04, 0x02, 0x0A, 0x05, 0x0F, 0x0A, 0x12
	.byte 0x11, 0x12, 0x16, 0x0F, 0x19, 0x0A, 0x1A, 0x04

	.global MOD75_021EC6AC
MOD75_021EC6AC: ; 0x021EC6AC
	.byte 0x00, 0x17, 0x0D, 0x07, 0x04, 0x03, 0x1B, 0x03

	.global MOD75_021EC6B4
MOD75_021EC6B4: ; 0x021EC6B4
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global MOD75_021EC6C0
MOD75_021EC6C0: ; 0x021EC6C0
	.byte 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x40, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00

	.global MOD75_021EC6D4
MOD75_021EC6D4: ; 0x021EC6D4
	.byte 0x0A, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD75_021EC6EC
MOD75_021EC6EC: ; 0x021EC6EC
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00

	.global MOD75_021EC70C
MOD75_021EC70C: ; 0x021EC70C
	.byte 0x30, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xF9, 0xC0, 0x00, 0x00, 0xF9, 0xC0, 0x00, 0x00, 0xF9, 0xC0, 0x00, 0x00
	.byte 0xF9, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xFA, 0xC0, 0x00, 0x00, 0xFA, 0xC0, 0x00, 0x00
	.byte 0xFA, 0xC0, 0x00, 0x00, 0xFA, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x60, 0x00, 0x00, 0x00, 0x01, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xFD, 0xC0, 0x00, 0x00
	.byte 0xFA, 0xC0, 0x00, 0x00, 0xFD, 0xC0, 0x00, 0x00, 0xFD, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x00, 0x60, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0xFD, 0xC0, 0x00, 0x00, 0xFA, 0xC0, 0x00, 0x00, 0xFD, 0xC0, 0x00, 0x00, 0xFD, 0xC0, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xB1, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xFB, 0xC0, 0x00, 0x00, 0xFA, 0xC0, 0x00, 0x00, 0xFB, 0xC0, 0x00, 0x00
	.byte 0xFB, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0xB1, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xFC, 0xC0, 0x00, 0x00, 0xFA, 0xC0, 0x00, 0x00
	.byte 0xFC, 0xC0, 0x00, 0x00, 0xFC, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xFE, 0xC0, 0x00, 0x00
	.byte 0xFB, 0xC0, 0x00, 0x00, 0xFE, 0xC0, 0x00, 0x00, 0xFE, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0xAC, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0xFF, 0xC0, 0x00, 0x00, 0xFC, 0xC0, 0x00, 0x00, 0xFF, 0xC0, 0x00, 0x00, 0xFF, 0xC0, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xDC, 0x00, 0x9C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x00, 0x00, 0xFD, 0xC0, 0x00, 0x00, 0x00, 0xC1, 0x00, 0x00
	.byte 0x00, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0xDC, 0x00, 0xB4, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x00, 0x00, 0xFD, 0xC0, 0x00, 0x00
	.byte 0x00, 0xC1, 0x00, 0x00, 0x00, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0xC1, 0x00, 0x00
	.byte 0xFE, 0xC0, 0x00, 0x00, 0x01, 0xC1, 0x00, 0x00, 0x01, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA8, 0x00, 0x98, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x02, 0xC1, 0x00, 0x00, 0xFE, 0xC0, 0x00, 0x00, 0x01, 0xC1, 0x00, 0x00, 0x01, 0xC1, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.data
	.bss
