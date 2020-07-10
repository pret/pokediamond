	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD56_02211E60
MOD56_02211E60: ; 0x02211E60
	sub r0, #9
	cmp r0, #5
	bhi _02211E82
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02211E72: ; jump table
	.short _02211E7E - _02211E72 - 2 ; case 0
	.short _02211E7E - _02211E72 - 2 ; case 1
	.short _02211E7E - _02211E72 - 2 ; case 2
	.short _02211E7E - _02211E72 - 2 ; case 3
	.short _02211E7E - _02211E72 - 2 ; case 4
	.short _02211E7E - _02211E72 - 2 ; case 5
_02211E7E:
	mov r0, #1
	bx lr
_02211E82:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD56_02211E60

	thumb_func_start MOD56_02211E88
MOD56_02211E88: ; 0x02211E88
	push {r4, lr}
	add r4, r0, #0
	bl MOD56_02211E60
	cmp r0, #0
	beq _02211E98
	mov r0, #1
	pop {r4, pc}
_02211E98:
	cmp r4, #0xf
	bne _02211EA0
	mov r0, #1
	pop {r4, pc}
_02211EA0:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD56_02211E88

	thumb_func_start MOD56_02211EA4
MOD56_02211EA4: ; 0x02211EA4
	cmp r0, #7
	bhi _02211EC8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02211EB4: ; jump table
	.short _02211EC8 - _02211EB4 - 2 ; case 0
	.short _02211EC8 - _02211EB4 - 2 ; case 1
	.short _02211EC4 - _02211EB4 - 2 ; case 2
	.short _02211EC4 - _02211EB4 - 2 ; case 3
	.short _02211EC4 - _02211EB4 - 2 ; case 4
	.short _02211EC4 - _02211EB4 - 2 ; case 5
	.short _02211EC4 - _02211EB4 - 2 ; case 6
	.short _02211EC4 - _02211EB4 - 2 ; case 7
_02211EC4:
	mov r0, #1
	bx lr
_02211EC8:
	mov r0, #0
	bx lr
	thumb_func_end MOD56_02211EA4

	thumb_func_start MOD56_02211ECC
MOD56_02211ECC: ; 0x02211ECC
	push {r4, lr}
	add r4, r0, #0
	bl MOD56_02211EA4
	cmp r0, #0
	beq _02211EDC
	mov r0, #1
	pop {r4, pc}
_02211EDC:
	cmp r4, #1
	beq _02211EE4
	cmp r4, #8
	bne _02211EE8
_02211EE4:
	mov r0, #1
	pop {r4, pc}
_02211EE8:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD56_02211ECC

	thumb_func_start MOD56_02211EEC
MOD56_02211EEC: ; 0x02211EEC
	sub r0, #0xc
	cmp r0, #3
	bhi _02211F0A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02211EFE: ; jump table
	.short _02211F06 - _02211EFE - 2 ; case 0
	.short _02211F06 - _02211EFE - 2 ; case 1
	.short _02211F06 - _02211EFE - 2 ; case 2
	.short _02211F06 - _02211EFE - 2 ; case 3
_02211F06:
	mov r0, #1
	bx lr
_02211F0A:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD56_02211EEC

	thumb_func_start MOD56_02211F10
MOD56_02211F10: ; 0x02211F10
	mov r1, #0x11
	cmp r0, #0x10
	bhi _02211F82
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02211F22: ; jump table
	.short _02211F82 - _02211F22 - 2 ; case 0
	.short _02211F80 - _02211F22 - 2 ; case 1
	.short _02211F68 - _02211F22 - 2 ; case 2
	.short _02211F6C - _02211F22 - 2 ; case 3
	.short _02211F70 - _02211F22 - 2 ; case 4
	.short _02211F74 - _02211F22 - 2 ; case 5
	.short _02211F78 - _02211F22 - 2 ; case 6
	.short _02211F7C - _02211F22 - 2 ; case 7
	.short _02211F64 - _02211F22 - 2 ; case 8
	.short _02211F48 - _02211F22 - 2 ; case 9
	.short _02211F4C - _02211F22 - 2 ; case 10
	.short _02211F50 - _02211F22 - 2 ; case 11
	.short _02211F54 - _02211F22 - 2 ; case 12
	.short _02211F58 - _02211F22 - 2 ; case 13
	.short _02211F5C - _02211F22 - 2 ; case 14
	.short _02211F44 - _02211F22 - 2 ; case 15
	.short _02211F60 - _02211F22 - 2 ; case 16
_02211F44:
	mov r1, #8
	b _02211F82
_02211F48:
	mov r1, #2
	b _02211F82
_02211F4C:
	mov r1, #3
	b _02211F82
_02211F50:
	mov r1, #4
	b _02211F82
_02211F54:
	mov r1, #5
	b _02211F82
_02211F58:
	mov r1, #6
	b _02211F82
_02211F5C:
	mov r1, #7
	b _02211F82
_02211F60:
	mov r1, #1
	b _02211F82
_02211F64:
	mov r1, #0xf
	b _02211F82
_02211F68:
	mov r1, #9
	b _02211F82
_02211F6C:
	mov r1, #0xa
	b _02211F82
_02211F70:
	mov r1, #0xb
	b _02211F82
_02211F74:
	mov r1, #0xc
	b _02211F82
_02211F78:
	mov r1, #0xd
	b _02211F82
_02211F7C:
	mov r1, #0xe
	b _02211F82
_02211F80:
	mov r1, #0x10
_02211F82:
	add r0, r1, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD56_02211F10

	thumb_func_start MOD56_02211F88
MOD56_02211F88: ; 0x02211F88
	push {r3, r4, r5, r6, r7, lr}
	add r0, #0xc4
	ldr r0, [r0]
	bl FUN_0206BB1C
	str r0, [sp]
	bl GetPartyCount
	mov r5, #0
	add r7, r0, #0
	add r4, r5, #0
	cmp r7, #0
	ble _02211FCE
_02211FA2:
	ldr r0, [sp]
	add r1, r4, #0
	bl GetPartyMonByIndex
	mov r1, #0xa2
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _02211FC8
	add r0, r6, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _02211FC8
	add r5, r5, #1
_02211FC8:
	add r4, r4, #1
	cmp r4, r7
	blt _02211FA2
_02211FCE:
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD56_02211F88

	thumb_func_start MOD56_02211FD4
MOD56_02211FD4: ; 0x02211FD4
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	bl FUN_02015F1C
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _02212074 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _02212078 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	mov r0, #0x36
	bl FUN_02016B94
	add r1, r4, #0
	add r1, #0xc0
	str r0, [r1]
	mov r0, #0x36
	bl FUN_0200AA80
	add r1, r4, #0
	add r1, #0xc8
	str r0, [r1]
	mov r2, #0x25
	mov r0, #0
	mov r1, #0x1a
	lsl r2, r2, #4
	mov r3, #0x36
	bl NewMsgDataFromNarc
	add r1, r4, #0
	add r1, #0xcc
	str r0, [r1]
	ldr r2, _0221207C ; =0x00000265
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x36
	bl NewMsgDataFromNarc
	add r1, r4, #0
	add r1, #0xd0
	str r0, [r1]
	bl MOD56_022122B4
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	bl MOD56_022122D4
	add r0, r4, #0
	bl MOD56_0221257C
	ldr r0, _02212080 ; =MOD56_0221228C
	add r1, r4, #0
	bl FUN_02015F10
	bl MOD56_0221269C
	add r0, r4, #0
	bl MOD56_022126E0
	add r0, r4, #0
	bl MOD56_022127D4
	pop {r4, pc}
	.align 2, 0
_02212074: .word 0xFFFFE0FF
_02212078: .word 0x04001000
_0221207C: .word 0x00000265
_02212080: .word MOD56_0221228C
	thumb_func_end MOD56_02211FD4

	thumb_func_start MOD56_02212084
MOD56_02212084: ; 0x02212084
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #0
	beq _02212098
	cmp r1, #1
	beq _0221214E
	b _0221215C
_02212098:
	bl FUN_0200628C
	add r6, r0, #0
	ldr r0, [r6, #4]
	cmp r0, #1
	bne _022120B2
	mov r2, #7
	mov r0, #3
	mov r1, #0x36
	lsl r2, r2, #0x10
	bl FUN_0201681C
	b _022120BE
_022120B2:
	mov r2, #0xb
	mov r0, #3
	mov r1, #0x36
	lsl r2, r2, #0x10
	bl FUN_0201681C
_022120BE:
	mov r1, #0x3f
	add r0, r4, #0
	lsl r1, r1, #4
	mov r2, #0x36
	bl FUN_02006268
	mov r2, #0x3f
	mov r1, #0
	lsl r2, r2, #4
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0x5e
	mov r1, #8
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	ldr r1, [r6]
	add r0, #0xc4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	bl FUN_020286EC
	str r0, [r4]
	mov r1, #0xef
	ldr r0, [r6, #4]
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r1, #0
	mov r2, #8
	sub r0, #8
	str r2, [r4, r0]
	sub r2, #9
	add r1, #0x1c
	str r2, [r4, r1]
	mov r0, #0xf
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #0xf
	mov r1, #0
	bl FUN_0201E74C
	add r0, r4, #0
	bl MOD56_0221244C
	add r0, r4, #0
	bl MOD56_02211FD4
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x36
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	bl FUN_02033590
	cmp r0, #0
	bne _02212146
	bl FUN_02088858
_02212146:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0221215C
_0221214E:
	bl FUN_02006278
	mov r0, #0
	str r0, [r5]
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_0221215C:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD56_02212084

	thumb_func_start MOD56_02212164
MOD56_02212164: ; 0x02212164
	push {r3, r4, r5, lr}
	add r5, r1, #0
	bl FUN_02006278
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #0
	beq _0221217E
	cmp r1, #1
	beq _0221218C
	cmp r1, #2
	beq _022121A2
	b _022121AE
_0221217E:
	bl FUN_0200E308
	cmp r0, #0
	beq _022121AE
	mov r0, #1
	str r0, [r5]
	b _022121AE
_0221218C:
	mov r2, #0x3b
	lsl r2, r2, #4
	ldr r2, [r4, r2]
	lsl r3, r2, #2
	ldr r2, _022121C0 ; =0x022164E0
	ldr r2, [r2, r3]
	cmp r2, #0
	beq _022121AE
	blx r2
	str r0, [r5]
	b _022121AE
_022121A2:
	bl FUN_0200E308
	cmp r0, #0
	beq _022121AE
	mov r0, #1
	pop {r3, r4, r5, pc}
_022121AE:
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _022121BC
	bl FUN_0201FDEC
_022121BC:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_022121C0: .word MOD56_022164E0
	thumb_func_end MOD56_02212164

	thumb_func_start MOD56_022121C4
MOD56_022121C4: ; 0x022121C4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	mov r0, #0xb
	lsl r0, r0, #6
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	mov r0, #0xb1
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009E04
	mov r7, #0x2b
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #4
_022121EC:
	ldr r0, [r5, r7]
	bl FUN_02008E2C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _022121EC
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_0201FD58
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	add r0, r6, #0
	bl MOD56_0221295C
	add r0, r6, #0
	add r0, #0xc0
	ldr r0, [r0]
	bl MOD56_02212540
	add r0, r6, #0
	add r0, #0xd0
	ldr r0, [r0]
	bl DestroyMsgData
	add r0, r6, #0
	add r0, #0xcc
	ldr r0, [r0]
	bl DestroyMsgData
	add r6, #0xc8
	ldr r0, [r6]
	bl FUN_0200AB18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD56_022121C4

	thumb_func_start MOD56_02212240
MOD56_02212240: ; 0x02212240
	push {r4, r5, r6, lr}
	add r5, r0, #0
	bl FUN_02006278
	add r4, r0, #0
	bl MOD56_022121C4
	add r0, r5, #0
	bl FUN_0200628C
	add r6, r0, #0
	mov r0, #0xed
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	str r1, [r6, #4]
	ldr r0, [r4, r0]
	cmp r0, #8
	beq _02212268
	cmp r0, #0xa
	bne _0221226E
_02212268:
	bl FUN_02088868
	b _02212274
_0221226E:
	bl MOD04_021D853C
	str r0, [r6, #8]
_02212274:
	add r0, r4, #0
	bl MOD56_022124E4
	add r0, r5, #0
	bl FUN_0200627C
	mov r0, #0x36
	bl FUN_020168D0
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD56_02212240

	thumb_func_start MOD56_0221228C
MOD56_0221228C: ; 0x0221228C
	push {r3, lr}
	add r0, #0xc0
	ldr r0, [r0]
	bl FUN_0201AB60
	bl FUN_0201C30C
	bl FUN_02009F80
	ldr r3, _022122AC ; =0x027E0000
	ldr r1, _022122B0 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r3, pc}
	.align 2, 0
_022122AC: .word 0x027E0000
_022122B0: .word 0x00003FF8
	thumb_func_end MOD56_0221228C

	thumb_func_start MOD56_022122B4
MOD56_022122B4: ; 0x022122B4
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _022122D0 ; =0x02216454
	add r3, sp, #0
	mov r2, #5
_022122BE:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _022122BE
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_022122D0: .word MOD56_02216454
	thumb_func_end MOD56_022122B4

	thumb_func_start MOD56_022122D4
MOD56_022122D4: ; 0x022122D4
	push {r4, r5, lr}
	sub sp, #0x9c
	ldr r5, _0221242C ; =0x02216330
	add r3, sp, #0x8c
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _02212430 ; =0x02216368
	add r3, sp, #0x70
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
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x36
	bl FUN_02017F18
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _02212434 ; =0x02216384
	add r3, sp, #0x54
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
	mov r0, #1
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x36
	bl FUN_02017F18
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018744
	ldr r5, _02212438 ; =0x022163A0
	add r3, sp, #0x38
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
	mov r0, #2
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x36
	bl FUN_02017F18
	add r0, r4, #0
	mov r1, #2
	bl FUN_02018744
	ldr r5, _0221243C ; =0x022163BC
	add r3, sp, #0x1c
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
	mov r0, #3
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x36
	bl FUN_02017F18
	add r0, r4, #0
	mov r1, #3
	bl FUN_02018744
	ldr r5, _02212440 ; =0x022163D8
	add r3, sp, #0
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
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x36
	bl FUN_02017F18
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x36
	bl FUN_02017F18
	mov r0, #0
	mov r1, #3
	bl FUN_020178BC
	mov r0, #1
	mov r1, #2
	bl FUN_020178BC
	mov r0, #3
	mov r1, #1
	bl FUN_020178BC
	mov r0, #2
	mov r1, #0
	bl FUN_020178BC
	ldr r0, _02212444 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	ldr r0, _02212448 ; =0x04001050
	strh r1, [r0]
	add sp, #0x9c
	pop {r4, r5, pc}
	.align 2, 0
_0221242C: .word MOD56_02216330
_02212430: .word MOD56_02216368
_02212434: .word MOD56_02216384
_02212438: .word MOD56_022163A0
_0221243C: .word MOD56_022163BC
_02212440: .word MOD56_022163D8
_02212444: .word 0x04000050
_02212448: .word 0x04001050
	thumb_func_end MOD56_022122D4

	thumb_func_start MOD56_0221244C
MOD56_0221244C: ; 0x0221244C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
	mov r7, #8
_02212456:
	add r0, r7, #0
	mov r1, #0x36
	bl String_ctor
	add r1, r5, #0
	add r1, #0xd4
	str r0, [r1]
	ldr r0, [r6]
	add r1, r4, #0
	bl FUN_020283A4
	add r1, r0, #0
	add r0, r5, #0
	add r0, #0xd4
	ldr r0, [r0]
	bl FUN_02021E28
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x20
	blt _02212456
	mov r0, #0x5f
	lsl r0, r0, #2
	mov r1, #0x36
	bl String_ctor
	mov r1, #0x57
	lsl r1, r1, #2
	str r0, [r6, r1]
	add r1, #0x20
	add r0, r1, #0
	mov r1, #0x36
	bl String_ctor
	mov r1, #0x5d
	lsl r1, r1, #2
	add r7, r1, #0
	str r0, [r6, r1]
	mov r5, #0
	add r4, r6, #0
	sub r7, #0x10
_022124A8:
	mov r0, #0x5f
	lsl r0, r0, #2
	mov r1, #0x36
	bl String_ctor
	str r0, [r4, r7]
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #4
	blt _022124A8
	mov r0, #0x5f
	lsl r0, r0, #2
	mov r1, #0x36
	bl String_ctor
	mov r1, #0x56
	lsl r1, r1, #2
	str r0, [r6, r1]
	mov r0, #0xb4
	mov r1, #0x36
	bl String_ctor
	mov r1, #0x16
	lsl r1, r1, #4
	str r0, [r6, r1]
	mov r0, #0x3b
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r6, r0]
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD56_0221244C

	thumb_func_start MOD56_022124E4
MOD56_022124E4: ; 0x022124E4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r4, #0
	add r5, r7, #0
_022124EC:
	add r0, r5, #0
	add r0, #0xd4
	ldr r0, [r0]
	bl String_dtor
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x20
	blt _022124EC
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r7, r0]
	bl String_dtor
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	bl String_dtor
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	bl String_dtor
	mov r6, #0x59
	mov r5, #0
	add r4, r7, #0
	lsl r6, r6, #2
_02212524:
	ldr r0, [r4, r6]
	bl String_dtor
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #4
	blt _02212524
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	bl String_dtor
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD56_022124E4

	thumb_func_start MOD56_02212540
MOD56_02212540: ; 0x02212540
	push {r4, lr}
	add r4, r0, #0
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
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD56_02212540

	thumb_func_start MOD56_0221257C
MOD56_0221257C: ; 0x0221257C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r0, #0xc0
	ldr r4, [r0]
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
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E74C
	mov r2, #0
	str r2, [sp]
	mov r0, #0x36
	str r0, [sp, #4]
	mov r0, #0x5c
	mov r1, #3
	add r3, r2, #0
	bl FUN_02006930
	mov r3, #0
	str r3, [sp]
	mov r0, #0x36
	str r0, [sp, #4]
	mov r0, #0x5c
	mov r1, #3
	mov r2, #4
	bl FUN_02006930
	mov r1, #0x1a
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x36
	bl FUN_02002EEC
	mov r1, #6
	mov r0, #0
	lsl r1, r1, #6
	mov r2, #0x36
	bl FUN_02002EEC
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x36
	str r0, [sp, #0xc]
	mov r0, #0x5c
	mov r1, #2
	add r2, r4, #0
	bl FUN_0200687C
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x36
	str r0, [sp, #0xc]
	mov r0, #0x5c
	mov r1, #4
	add r2, r4, #0
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x36
	str r0, [sp, #0xc]
	mov r0, #0x5c
	mov r1, #9
	add r2, r4, #0
	mov r3, #4
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x36
	str r0, [sp, #0xc]
	mov r0, #0x5c
	mov r1, #0xa
	add r2, r4, #0
	mov r3, #4
	bl FUN_020068C8
	add r5, #0xc4
	ldr r0, [r5]
	bl LoadPlayerDataAddress
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x36
	str r0, [sp, #4]
	ldr r2, _02212694 ; =0x000001E2
	add r0, r4, #0
	mov r1, #2
	mov r3, #0xa
	bl FUN_0200CD68
	mov r0, #0
	str r0, [sp]
	mov r0, #0x36
	str r0, [sp, #4]
	ldr r2, _02212698 ; =0x000001D9
	add r0, r4, #0
	mov r1, #2
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0
	str r0, [sp]
	mov r0, #0x36
	str r0, [sp, #4]
	ldr r2, _02212698 ; =0x000001D9
	add r0, r4, #0
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CB00
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_02212694: .word 0x000001E2
_02212698: .word 0x000001D9
	thumb_func_end MOD56_0221257C

	thumb_func_start MOD56_0221269C
MOD56_0221269C: ; 0x0221269C
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _022126D8 ; =0x02216340
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_0201D040
	mov r0, #0x14
	mov r1, #0x36
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	ldr r1, _022126DC ; =0x00100010
	mov r0, #1
	bl FUN_02008D44
	mov r0, #1
	bl FUN_02008DDC
	add sp, #0x10
	pop {r4, pc}
	nop
_022126D8: .word MOD56_02216340
_022126DC: .word 0x00100010
	thumb_func_end MOD56_0221269C

	thumb_func_start MOD56_022126E0
MOD56_022126E0: ; 0x022126E0
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
	mov r2, #0x36
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	mov r1, #0x62
	lsl r1, r1, #2
	mov r0, #0x1e
	add r1, r6, r1
	mov r2, #0x36
	bl FUN_02008C9C
	mov r1, #0x61
	lsl r1, r1, #2
	str r0, [r6, r1]
	add r0, r1, #4
	mov r2, #1
	add r0, r6, r0
	mov r1, #0
	lsl r2, r2, #0x14
	bl FUN_02008D24
	mov r7, #0x2b
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #4
_0221272C:
	mov r0, #2
	add r1, r4, #0
	mov r2, #0x36
	bl FUN_02008DEC
	str r0, [r5, r7]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0221272C
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x36
	str r0, [sp, #8]
	mov r0, #0x2b
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	mov r1, #0x5c
	mov r2, #7
	bl FUN_02008F34
	mov r1, #0xb
	lsl r1, r1, #6
	str r0, [r6, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #7
	str r0, [sp, #8]
	mov r0, #0x36
	sub r1, #0xc
	str r0, [sp, #0xc]
	ldr r0, [r6, r1]
	mov r1, #0x5c
	mov r2, #8
	bl FUN_02008FEC
	mov r1, #0xb1
	lsl r1, r1, #2
	str r0, [r6, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x36
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r6, r1]
	mov r1, #0x5c
	mov r2, #1
	bl FUN_020090AC
	mov r1, #0xb2
	lsl r1, r1, #2
	str r0, [r6, r1]
	mov r2, #0
	str r2, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x36
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r6, r1]
	mov r1, #0x5c
	add r3, r2, #0
	bl FUN_020090AC
	mov r1, #0xb3
	lsl r1, r1, #2
	str r0, [r6, r1]
	sub r1, #0xc
	ldr r0, [r6, r1]
	bl FUN_02009A50
	mov r0, #0xb1
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009CF0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD56_022126E0

	thumb_func_start MOD56_022127D4
MOD56_022127D4: ; 0x022127D4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	mov r1, #0
	add r5, r0, #0
	str r1, [sp]
	sub r0, r1, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r2, #0x2b
	str r1, [sp, #0x10]
	lsl r2, r2, #4
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
	add r2, #0x30
	str r0, [sp, #0x20]
	str r1, [sp, #0x24]
	add r0, r5, r2
	add r2, r1, #0
	str r1, [sp, #0x28]
	bl FUN_02008AA4
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r4, #0
	str r0, [sp, #0x2c]
	mov r0, #0x2e
	lsl r0, r0, #4
	add r0, r5, r0
	str r0, [sp, #0x30]
	mov r0, #1
	lsl r0, r0, #0xc
	mov r7, #6
	str r4, [sp, #0x3c]
	str r0, [sp, #0x40]
	str r0, [sp, #0x44]
	str r0, [sp, #0x48]
	add r0, sp, #0x2c
	strh r4, [r0, #0x20]
	mov r0, #1
	str r0, [sp, #0x50]
	str r0, [sp, #0x54]
	mov r0, #0x36
	str r0, [sp, #0x58]
	mov r6, #0x20
	lsl r7, r7, #0xe
_02212848:
	mov r0, #1
	lsl r1, r6, #0xc
	lsl r0, r0, #0x14
	add r0, r1, r0
	str r0, [sp, #0x38]
	add r0, sp, #0x2c
	str r7, [sp, #0x34]
	bl FUN_0201FE94
	mov r1, #0xca
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0xca
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_02020130
	mov r0, #0xca
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #2
	bl FUN_02020238
	mov r0, #0xca
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	add r4, r4, #1
	add r6, #0x20
	add r5, r5, #4
	cmp r4, #5
	blt _02212848
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD56_022127D4

	thumb_func_start MOD56_022128A4
MOD56_022128A4: ; 0x022128A4
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019048
	cmp r0, #0
	beq _022128CE
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl FUN_0200CCF8
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019178
_022128CE:
	mov r0, #1
	str r0, [sp]
	mov r0, #0x16
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _02212954 ; =0x000001CA
	mov r1, #0xd7
	str r0, [sp, #0x10]
	add r0, r4, #0
	add r0, #0xc0
	lsl r1, r1, #2
	ldr r0, [r0]
	add r1, r4, r1
	mov r2, #3
	mov r3, #5
	bl FUN_02019064
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl FUN_02019620
	add r0, r4, #0
	mov r2, #0x16
	add r0, #0xcc
	lsl r2, r2, #4
	ldr r0, [r0]
	ldr r2, [r4, r2]
	mov r1, #0x11
	bl ReadMsgDataIntoString
	mov r1, #0x16
	lsl r1, r1, #4
	ldr r1, [r4, r1]
	mov r0, #1
	mov r2, #0
	mov r3, #0xb0
	bl FUN_02002F40
	mov r1, #0
	add r3, r0, #0
	str r1, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	ldr r0, _02212958 ; =0x000F0E00
	add r2, #0x61
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #0xd7
	lsl r0, r0, #2
	ldr r2, [r4, r2]
	add r0, r4, r0
	mov r1, #1
	bl FUN_0201BDE0
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019220
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_02212954: .word 0x000001CA
_02212958: .word 0x000F0E00
	thumb_func_end MOD56_022128A4

	thumb_func_start MOD56_0221295C
MOD56_0221295C: ; 0x0221295C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019048
	cmp r0, #0
	beq _02212978
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019178
_02212978:
	mov r0, #0xcf
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019048
	cmp r0, #0
	beq _02212990
	mov r0, #0xcf
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019178
_02212990:
	mov r0, #0xe7
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019048
	cmp r0, #0
	beq _022129A8
	mov r0, #0xe7
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019178
_022129A8:
	mov r0, #0xd3
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019048
	cmp r0, #0
	beq _022129C0
	mov r0, #0xd3
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019178
_022129C0:
	mov r0, #0xdf
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019048
	cmp r0, #0
	beq _022129D8
	mov r0, #0xdf
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019178
_022129D8:
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	beq _022129EA
	mov r1, #0
	add r2, r1, #0
	bl FUN_02001300
_022129EA:
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	cmp r0, #0
	beq _02212A00
	bl FUN_02012870
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb0
	str r1, [r0]
_02212A00:
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019048
	cmp r0, #0
	beq _02212A18
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019178
_02212A18:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD56_0221295C

	thumb_func_start MOD56_02212A1C
MOD56_02212A1C: ; 0x02212A1C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r1, _02212B30 ; =0x00000497
	mov r0, #0xb
	mov r2, #1
	bl FUN_0200433C
	bl FUN_02033590
	cmp r0, #0
	beq _02212A9A
	bl FUN_02033E74
	bl MOD04_021D853C
	add r1, r0, #0
	add r0, r5, #0
	bl MOD56_022160E4
	bl FUN_020334DC
	add r1, r0, #0
	str r0, [r5, #4]
	add r1, #0x22
	ldrb r1, [r1]
	add r0, #0x21
	strb r1, [r0]
	ldr r0, [r5, #4]
	ldrb r0, [r0, #0x1b]
	cmp r0, #8
	bne _02212A80
	bl FUN_02033208
	bl FUN_020334DC
	add r1, r0, #0
	str r0, [r5, #4]
	add r1, #0x22
	ldrb r1, [r1]
	add r0, #0x21
	strb r1, [r0]
	mov r0, #0xf1
	mov r1, #0x14
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0x40
	sub r0, #0x14
	str r1, [r5, r0]
	b _02212B2C
_02212A80:
	add r0, r5, #0
	mov r1, #0x2b
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x10
	bl FUN_02031588
	mov r0, #0x3b
	mov r1, #0x3c
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02212B2C
_02212A9A:
	add r0, r5, #0
	bl MOD56_022128A4
	ldr r0, [r5]
	bl FUN_02028228
	bl DWC_CheckHasProfile
	cmp r0, #0
	bne _02212AFA
	mov r0, #0
	mov r1, #3
	bl FUN_020178BC
	mov r0, #3
	mov r1, #2
	bl FUN_020178BC
	mov r0, #2
	mov r1, #1
	bl FUN_020178BC
	mov r0, #1
	mov r1, #0
	bl FUN_020178BC
	add r0, r5, #0
	mov r1, #0x11
	bl MOD56_02215FF4
	mov r0, #0x36
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, _02212B34 ; =0x02216310
	ldr r2, _02212B38 ; =0x000001D9
	mov r3, #0xb
	bl FUN_02002198
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0x3b
	mov r1, #6
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02212B2C
_02212AFA:
	ldr r0, [r5]
	bl FUN_02028228
	bl DWC_CheckValidConsole
	cmp r0, #0
	bne _02212B1A
	add r0, r5, #0
	mov r1, #0x13
	bl MOD56_02215FF4
	mov r0, #0x3b
	mov r1, #3
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02212B2C
_02212B1A:
	add r0, r5, #0
	mov r1, #0x10
	mov r2, #1
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #1
	lsl r0, r0, #4
	str r1, [r5, r0]
_02212B2C:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02212B30: .word 0x00000497
_02212B34: .word MOD56_02216310
_02212B38: .word 0x000001D9
	thumb_func_end MOD56_02212A1C

	thumb_func_start MOD56_02212B3C
MOD56_02212B3C: ; 0x02212B3C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02212B76
	mov r0, #0x36
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, _02212B7C ; =0x022162F8
	ldr r2, _02212B80 ; =0x000001D9
	mov r3, #0xb
	bl FUN_02002198
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0x3b
	mov r1, #2
	lsl r0, r0, #4
	str r1, [r5, r0]
_02212B76:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_02212B7C: .word MOD56_022162F8
_02212B80: .word 0x000001D9
	thumb_func_end MOD56_02212B3C

	thumb_func_start MOD56_02212B84
MOD56_02212B84: ; 0x02212B84
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	add r4, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _02212BA2
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_02212BA2:
	cmp r0, #0
	bne _02212BD4
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	ldr r1, _02212BE0 ; =0x000004A4
	bl FUN_0203346C
	str r0, [r5, #4]
	add r0, r5, #0
	mov r1, #0x16
	mov r2, #1
	bl MOD56_02215EA4
	mov r0, #0xcf
	lsl r0, r0, #2
	ldr r1, _02212BE4 ; =0x000001E2
	add r0, r5, r0
	bl FUN_0200D858
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r5, r1]
	mov r1, #0xe
	b _02212BD6
_02212BD4:
	mov r1, #0x22
_02212BD6:
	mov r0, #0x3b
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02212BE0: .word 0x000004A4
_02212BE4: .word 0x000001E2
	thumb_func_end MOD56_02212B84

	thumb_func_start MOD56_02212BE8
MOD56_02212BE8: ; 0x02212BE8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, _02212C44 ; =gUnknown21C48B8
	add r5, r0, #0
	ldr r2, [r1, #0x48]
	mov r1, #3
	tst r1, r2
	beq _02212C40
	mov r1, #0x14
	bl MOD56_02215FF4
	mov r0, #0
	mov r1, #3
	bl FUN_020178BC
	mov r0, #3
	mov r1, #2
	bl FUN_020178BC
	mov r0, #2
	mov r1, #1
	bl FUN_020178BC
	mov r0, #1
	mov r1, #0
	bl FUN_020178BC
	mov r0, #0x36
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, _02212C48 ; =0x02216310
	ldr r2, _02212C4C ; =0x000001D9
	mov r3, #0xb
	bl FUN_02002198
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0x3b
	mov r1, #4
	lsl r0, r0, #4
	str r1, [r5, r0]
_02212C40:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02212C44: .word gUnknown21C48B8
_02212C48: .word MOD56_02216310
_02212C4C: .word 0x000001D9
	thumb_func_end MOD56_02212BE8

	thumb_func_start MOD56_02212C50
MOD56_02212C50: ; 0x02212C50
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	add r4, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021AC
	add r6, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r6, r0
	bne _02212C74
	add sp, #4
	add r0, r4, #0
	pop {r3, r4, r5, r6, pc}
_02212C74:
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
	cmp r6, #0
	bne _02212CB4
	add r0, r5, #0
	mov r1, #0x15
	bl MOD56_02215FF4
	mov r0, #0x36
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, _02212CC4 ; =0x02216310
	ldr r2, _02212CC8 ; =0x000001D9
	mov r3, #0xb
	bl FUN_02002198
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r1, #5
	b _02212CB6
_02212CB4:
	mov r1, #0x22
_02212CB6:
	mov r0, #0x3b
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_02212CC4: .word MOD56_02216310
_02212CC8: .word 0x000001D9
	thumb_func_end MOD56_02212C50

	thumb_func_start MOD56_02212CCC
MOD56_02212CCC: ; 0x02212CCC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	add r4, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021AC
	add r6, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r6, r0
	bne _02212CEC
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_02212CEC:
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
	cmp r6, #0
	bne _02212D44
	ldr r0, [r5]
	bl FUN_020281E8
	mov r1, #0x3b
	mov r0, #0xe
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, #0xf4
	bl FUN_0203346C
	str r0, [r5, #4]
	add r0, r5, #0
	mov r1, #0x16
	mov r2, #1
	bl MOD56_02215EA4
	mov r0, #0xcf
	lsl r0, r0, #2
	ldr r1, _02212D50 ; =0x000001E2
	add r0, r5, r0
	bl FUN_0200D858
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r5, r1]
	mov r1, #1
	mov r0, #0x3d
	b _02212D48
_02212D44:
	mov r1, #0x22
	mov r0, #0x3b
_02212D48:
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_02212D50: .word 0x000001E2
	thumb_func_end MOD56_02212CCC

	thumb_func_start MOD56_02212D54
MOD56_02212D54: ; 0x02212D54
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	add r4, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021AC
	add r6, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r6, r0
	bne _02212D74
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_02212D74:
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
	cmp r6, #0
	bne _02212DC6
	mov r1, #0x3b
	mov r0, #0xe
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, #0xf4
	bl FUN_0203346C
	str r0, [r5, #4]
	add r0, r5, #0
	mov r1, #0x16
	mov r2, #1
	bl MOD56_02215EA4
	mov r0, #0xcf
	lsl r0, r0, #2
	ldr r1, _02212DD4 ; =0x000001E2
	add r0, r5, r0
	bl FUN_0200D858
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r5, r1]
	mov r1, #1
	mov r0, #0x3d
	b _02212DCA
_02212DC6:
	mov r1, #0x22
	mov r0, #0x3b
_02212DCA:
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	nop
_02212DD4: .word 0x000001E2
	thumb_func_end MOD56_02212D54

	thumb_func_start MOD56_02212DD8
MOD56_02212DD8: ; 0x02212DD8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0
	mov r1, #3
	bl FUN_020178BC
	mov r0, #1
	mov r1, #2
	bl FUN_020178BC
	mov r0, #3
	mov r1, #1
	bl FUN_020178BC
	mov r0, #2
	mov r1, #0
	bl FUN_020178BC
	mov r0, #0x3b
	mov r1, #0xf
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD56_02212DD8

	thumb_func_start MOD56_02212E0C
MOD56_02212E0C: ; 0x02212E0C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	str r1, [sp]
	bl FUN_020238F4
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	bl FUN_02024DA0
	str r0, [sp, #0x10]
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	bl FUN_0206BB1C
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	bl FUN_02029AFC
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	bl GetPartyCount
	mov r6, #0
	str r0, [sp, #4]
	cmp r0, #0
	ble _02212E82
	add r4, r6, #0
_02212E52:
	ldr r0, [sp, #0xc]
	add r1, r6, #0
	bl GetPartyMonByIndex
	mov r1, #5
	mov r2, #0
	add r7, r0, #0
	bl GetMonData
	ldr r1, [r5, #4]
	mov r2, #0
	strh r0, [r1, r4]
	add r0, r7, #0
	mov r1, #6
	bl GetMonData
	ldr r1, [r5, #4]
	add r6, r6, #1
	add r1, r1, r4
	strh r0, [r1, #0xc]
	ldr r0, [sp, #4]
	add r4, r4, #2
	cmp r6, r0
	blt _02212E52
_02212E82:
	ldr r0, [sp, #0x14]
	bl FUN_02023A68
	ldr r1, [r5, #4]
	strb r0, [r1, #0x18]
	ldr r0, [sp, #0x14]
	bl FUN_02023A70
	ldr r1, [r5, #4]
	strb r0, [r1, #0x19]
	ldr r0, [sp, #0x10]
	bl FUN_02024CA4
	ldr r1, [r5, #4]
	strb r0, [r1, #0x1a]
	ldr r1, [r5, #4]
	ldr r0, [sp]
	strb r0, [r1, #0x1b]
	ldr r0, [r5, #4]
	mov r1, #0
	strb r1, [r0, #0x1c]
	ldr r0, [sp, #0x14]
	bl FUN_02023A28
	ldr r1, [r5, #4]
	strb r0, [r1, #0x1d]
	ldr r0, [sp, #0x14]
	bl FUN_020239CC
	ldr r1, [r5, #4]
	strb r0, [r1, #0x1e]
	ldr r0, [sp, #8]
	bl FUN_02029B38
	ldr r1, [r5, #4]
	strb r0, [r1, #0x1f]
	ldr r0, [sp, #8]
	bl FUN_02029B3C
	ldr r1, [r5, #4]
	add r1, #0x20
	strb r0, [r1]
	ldr r0, [r5, #4]
	mov r1, #1
	add r0, #0x21
	strb r1, [r0]
	ldr r0, [r5, #4]
	add r0, #0x22
	strb r1, [r0]
	ldr r0, [r5, #4]
	mov r1, #0x24
	bl MOD04_021D8478
	ldr r0, [r5, #4]
	mov r1, #0x24
	add r0, #0x24
	bl MOD04_021D83D4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD56_02212E0C

	thumb_func_start MOD56_02212EFC
MOD56_02212EFC: ; 0x02212EFC
	push {r3, r4, r5, r6, r7, lr}
	mov r5, #0
	add r6, r0, #0
	add r4, r5, #0
	add r7, r5, #0
_02212F06:
	add r0, r6, r4
	strb r7, [r0, #0xc]
	add r0, r4, #0
	bl MOD04_021D8480
	cmp r0, #0
	beq _02212F1C
	add r0, r6, r5
	add r1, r4, #1
	strb r1, [r0, #0xc]
	add r5, r5, #1
_02212F1C:
	add r4, r4, #1
	cmp r4, #0x20
	blt _02212F06
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD56_02212EFC

	thumb_func_start MOD56_02212F28
MOD56_02212F28: ; 0x02212F28
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	add r7, r0, #0
	str r4, [sp]
	add r5, r4, #0
	add r6, r7, #0
_02212F34:
	ldr r0, [r7, #4]
	add r0, r0, r5
	add r0, #0x3f
	ldrb r1, [r0]
	ldr r0, [r6, #0x2c]
	cmp r0, r1
	beq _02212F6E
	str r1, [r6, #0x2c]
	ldr r3, [r7, #4]
	ldr r0, [r7]
	add r3, r3, r5
	add r3, #0x41
	ldrb r3, [r3]
	add r1, r4, #0
	mov r2, #7
	bl FUN_020282E8
	ldr r3, [r7, #4]
	ldr r0, [r7]
	add r3, r3, r5
	add r3, #0x42
	ldrb r3, [r3]
	add r1, r4, #0
	mov r2, #8
	bl FUN_020282E8
	ldr r0, [sp]
	add r0, r0, #1
	str r0, [sp]
_02212F6E:
	add r4, r4, #1
	add r5, #0x24
	add r6, r6, #4
	cmp r4, #0x20
	blt _02212F34
	ldr r0, [sp]
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD56_02212F28

	thumb_func_start MOD56_02212F7C
MOD56_02212F7C: ; 0x02212F7C
	push {r4, r5, r6, lr}
	sub sp, #8
	add r4, r0, #0
	add r5, r1, #0
	bl FUN_02033180
	mov r1, #0
	mvn r1, r1
	cmp r5, r1
	beq _02212F98
	cmp r5, #0xb
	beq _02212F98
	cmp r0, r1
	bne _02212F9E
_02212F98:
	mov r6, #0xe
	mov r5, #0xb
	b _02212FAC
_02212F9E:
	sub r1, r1, #1
	cmp r0, r1
	bne _02212FAA
	mov r6, #0xd
	mov r5, #0xc
	b _02212FAC
_02212FAA:
	add r6, r5, #0
_02212FAC:
	add r0, r4, #0
	bl MOD56_02216120
	bl FUN_02033180
	add r2, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0xc8
	ldr r0, [r0]
	mov r1, #0
	mov r3, #5
	bl FUN_0200AD38
	add r0, r4, #0
	add r1, r6, #0
	bl MOD56_02215FF4
	cmp r5, #0xb
	bhi _02213022
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02212FE6: ; jump table
	.short _02213022 - _02212FE6 - 2 ; case 0
	.short _02212FFE - _02212FE6 - 2 ; case 1
	.short _02213022 - _02212FE6 - 2 ; case 2
	.short _02213022 - _02212FE6 - 2 ; case 3
	.short _02212FFE - _02212FE6 - 2 ; case 4
	.short _02212FFE - _02212FE6 - 2 ; case 5
	.short _0221300A - _02212FE6 - 2 ; case 6
	.short _0221300A - _02212FE6 - 2 ; case 7
	.short _0221300A - _02212FE6 - 2 ; case 8
	.short _0221300A - _02212FE6 - 2 ; case 9
	.short _02213016 - _02212FE6 - 2 ; case 10
	.short _02212FFE - _02212FE6 - 2 ; case 11
_02212FFE:
	mov r0, #0x3b
	mov r1, #0xa
	lsl r0, r0, #4
	add sp, #8
	str r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0221300A:
	mov r0, #0x3b
	mov r1, #0xa
	lsl r0, r0, #4
	add sp, #8
	str r1, [r4, r0]
	pop {r4, r5, r6, pc}
_02213016:
	mov r0, #0x3b
	mov r1, #0xa
	lsl r0, r0, #4
	add sp, #8
	str r1, [r4, r0]
	pop {r4, r5, r6, pc}
_02213022:
	mov r0, #0x3b
	mov r1, #0x23
	lsl r0, r0, #4
	str r1, [r4, r0]
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD56_02212F7C

	thumb_func_start MOD56_02213030
MOD56_02213030: ; 0x02213030
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02033180
	bl MOD04_021D80E0
	add r1, r0, #0
	add r0, r4, #0
	bl MOD56_02212F7C
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD56_02213030

	thumb_func_start MOD56_02213048
MOD56_02213048: ; 0x02213048
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _02213088 ; =gUnknown21C48B8
	add r4, r1, #0
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _02213084
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019048
	cmp r0, #0
	beq _0221307C
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
_0221307C:
	mov r0, #0x3b
	mov r1, #8
	lsl r0, r0, #4
	str r1, [r5, r0]
_02213084:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02213088: .word gUnknown21C48B8
	thumb_func_end MOD56_02213048

	thumb_func_start MOD56_0221308C
MOD56_0221308C: ; 0x0221308C
	mov r2, #0x3b
	mov r3, #9
	lsl r2, r2, #4
	str r3, [r0, r2]
	add r0, r1, #0
	bx lr
	thumb_func_end MOD56_0221308C

	thumb_func_start MOD56_02213098
MOD56_02213098: ; 0x02213098
	mov r2, #0x3b
	mov r3, #0xb
	lsl r2, r2, #4
	str r3, [r0, r2]
	add r0, r1, #0
	bx lr
	thumb_func_end MOD56_02213098

	thumb_func_start MOD56_022130A4
MOD56_022130A4: ; 0x022130A4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _022130F0 ; =gUnknown21C48B8
	add r4, r1, #0
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _022130EA
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019048
	cmp r0, #0
	beq _022130D8
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
_022130D8:
	add r0, r5, #0
	mov r1, #0x33
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0xb
	lsl r0, r0, #4
	str r1, [r5, r0]
_022130EA:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_022130F0: .word gUnknown21C48B8
	thumb_func_end MOD56_022130A4

	thumb_func_start MOD56_022130F4
MOD56_022130F4: ; 0x022130F4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0221312E
	mov r0, #0x36
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, _02213134 ; =0x02216308
	ldr r2, _02213138 ; =0x000001D9
	mov r3, #0xb
	bl FUN_02002198
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0x3b
	mov r1, #0xc
	lsl r0, r0, #4
	str r1, [r5, r0]
_0221312E:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_02213134: .word MOD56_02216308
_02213138: .word 0x000001D9
	thumb_func_end MOD56_022130F4

	thumb_func_start MOD56_0221313C
MOD56_0221313C: ; 0x0221313C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	add r4, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _0221315A
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_0221315A:
	cmp r0, #0
	bne _02213172
	bl FUN_020331C4
	add r0, r5, #0
	mov r1, #0x10
	bl MOD56_0221617C
	mov r0, #0x3b
	mov r1, #0xd
	lsl r0, r0, #4
	b _02213186
_02213172:
	bl FUN_020331C4
	bl FUN_0202DBA4
	mov r0, #0xed
	mov r1, #8
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0x22
	sub r0, r0, #4
_02213186:
	str r1, [r5, r0]
	add r0, r5, #0
	bl MOD56_02216120
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD56_0221313C

	thumb_func_start MOD56_02213194
MOD56_02213194: ; 0x02213194
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	str r1, [sp, #0x10]
	bl FUN_0202E4C8
	cmp r0, #0
	bne _0221326E
	add r0, r6, #0
	add r0, #0xc0
	ldr r0, [r0]
	mov r1, #3
	bl FUN_02018744
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	add r2, r6, #0
	str r3, [sp, #8]
	mov r0, #0x36
	str r0, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	mov r0, #0x5c
	mov r1, #4
	bl FUN_020068C8
	add r0, r6, #0
	add r0, #0xb0
	ldr r0, [r0]
	cmp r0, #0
	beq _02213206
	mov r0, #0xdf
	lsl r0, r0, #2
	add r0, r6, r0
	bl FUN_02019178
	add r0, r6, #0
	add r0, #0xb4
	mov r1, #0
	ldr r0, [r0]
	add r2, r1, #0
	bl FUN_02001300
	add r0, r6, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
	add r0, r6, #0
	add r0, #0xb0
	ldr r0, [r0]
	bl FUN_02012870
	add r0, r6, #0
	mov r1, #0
	add r0, #0xb0
	str r1, [r0]
_02213206:
	add r0, r6, #0
	add r0, #0xc
	mov r1, #0
	mov r2, #0x20
	bl MI_CpuFill8
	add r0, r6, #0
	add r0, #0x2c
	mov r1, #0
	mov r2, #0x80
	bl MI_CpuFill8
	mov r7, #0xca
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_02213226:
	ldr r0, [r5, r7]
	mov r1, #0
	bl FUN_020200A0
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blt _02213226
	add r0, r6, #0
	bl MOD56_022128A4
	add r0, r6, #0
	add r0, #0xc4
	ldr r0, [r0]
	ldr r1, _02213274 ; =0x000004A4
	bl FUN_0203346C
	str r0, [r6, #4]
	add r0, r6, #0
	mov r1, #0x16
	mov r2, #1
	bl MOD56_02215EA4
	mov r0, #0xcf
	lsl r0, r0, #2
	ldr r1, _02213278 ; =0x000001E2
	add r0, r6, r0
	bl FUN_0200D858
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r6, r1]
	mov r0, #0x3b
	mov r1, #0xe
	lsl r0, r0, #4
	str r1, [r6, r0]
_0221326E:
	ldr r0, [sp, #0x10]
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02213274: .word 0x000004A4
_02213278: .word 0x000001E2
	thumb_func_end MOD56_02213194

	thumb_func_start MOD56_0221327C
MOD56_0221327C: ; 0x0221327C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_02033138
	cmp r0, #0
	beq _022132E0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #8
	beq _022132B6
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _022132B6
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD7C
	mov r0, #0x5e
	mov r1, #8
	lsl r0, r0, #2
	str r1, [r5, r0]
_022132B6:
	mov r0, #0x3d
	lsl r0, r0, #4
	ldr r1, [r5, r0]
	cmp r1, #0
	beq _022132C8
	mov r1, #0x10
	sub r0, #0x20
	str r1, [r5, r0]
	b _022132F6
_022132C8:
	add r0, r5, #0
	mov r1, #0x10
	bl MOD56_02212E0C
	add r0, r5, #0
	bl MOD56_02212EFC
	mov r0, #0x3b
	mov r1, #0x12
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _022132F6
_022132E0:
	bl FUN_02033250
	cmp r0, #0
	bne _022132F0
	bl FUN_0203300C
	cmp r0, #3
	bne _022132F6
_022132F0:
	add r0, r5, #0
	bl MOD56_02213030
_022132F6:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD56_0221327C

	thumb_func_start MOD56_022132FC
MOD56_022132FC: ; 0x022132FC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0xf1
	lsl r0, r0, #2
	add r4, r1, #0
	ldr r1, [r5, r0]
	cmp r1, #0
	ble _02213314
	sub r1, r1, #1
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_02213314:
	bl FUN_02033154
	cmp r0, #0
	beq _02213326
	mov r0, #0x3b
	mov r1, #0x12
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02213364
_02213326:
	bl FUN_0203300C
	cmp r0, #4
	bge _02213340
	bl FUN_02033128
	cmp r0, #0
	bne _02213340
	mov r0, #0
	bl FUN_02030E7C
	cmp r0, #0
	bne _0221334E
_02213340:
	bl FUN_020331E8
	mov r0, #0x3b
	mov r1, #0x12
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02213364
_0221334E:
	bl FUN_02033250
	cmp r0, #0
	bne _0221335E
	bl FUN_0203300C
	cmp r0, #3
	bne _02213364
_0221335E:
	add r0, r5, #0
	bl MOD56_02213030
_02213364:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD56_022132FC

	thumb_func_start MOD56_02213368
MOD56_02213368: ; 0x02213368
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD56_02216120
	add r0, r5, #0
	mov r1, #0x12
	bl MOD56_02215FF4
	mov r0, #0x3b
	mov r1, #0x11
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD56_02213368

	thumb_func_start MOD56_02213388
MOD56_02213388: ; 0x02213388
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _02213418 ; =gUnknown21C48B8
	add r4, r1, #0
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _02213412
	mov r1, #0xef
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	cmp r0, #1
	bne _022133B6
	add r0, r1, #0
	mov r2, #0xa
	sub r0, #8
	str r2, [r5, r0]
	mov r0, #0x22
	sub r1, #0xc
	str r0, [r5, r1]
	bl FUN_020331C4
	b _02213412
_022133B6:
	ldr r0, [r5]
	bl FUN_02028448
	cmp r0, #0
	bne _022133DA
	add r0, r5, #0
	mov r1, #0x19
	mov r2, #1
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x3a
	lsl r0, r0, #4
	str r1, [r5, r0]
	mov r1, #1
	add r0, #0x14
	str r1, [r5, r0]
	b _02213412
_022133DA:
	add r0, r5, #0
	mov r1, #0x10
	bl MOD56_02212E0C
	add r0, r5, #0
	bl MOD56_02212EFC
	mov r0, #0x3b
	mov r1, #0x12
	lsl r0, r0, #4
	str r1, [r5, r0]
	sub r0, #0x44
	add r0, r5, r0
	bl FUN_02019048
	cmp r0, #0
	beq _02213412
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
_02213412:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_02213418: .word gUnknown21C48B8
	thumb_func_end MOD56_02213388

	thumb_func_start MOD56_0221341C
MOD56_0221341C: ; 0x0221341C
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	ldr r5, _02213618 ; =0x00010200
	bl FUN_020238F4
	mov r1, #0x36
	bl FUN_020239A0
	add r6, r0, #0
	mov r0, #0xd3
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019048
	cmp r0, #0
	bne _0221344C
	add r0, r6, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
_0221344C:
	mov r0, #0xd3
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl FUN_02019620
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	add r0, r5, #0
	str r0, [sp, #8]
	mov r0, #0xd3
	lsl r0, r0, #2
	add r0, r4, r0
	add r2, r6, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
	add r0, r6, #0
	bl String_dtor
	ldr r0, [r4, #4]
	ldrb r0, [r0, #0x1b]
	cmp r0, #0x10
	bls _02213484
	b _02213614
_02213484:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02213490: ; jump table
	.short _022135D8 - _02213490 - 2 ; case 0
	.short _022134B2 - _02213490 - 2 ; case 1
	.short _0221350C - _02213490 - 2 ; case 2
	.short _0221350C - _02213490 - 2 ; case 3
	.short _0221350C - _02213490 - 2 ; case 4
	.short _0221350C - _02213490 - 2 ; case 5
	.short _0221350C - _02213490 - 2 ; case 6
	.short _0221350C - _02213490 - 2 ; case 7
	.short _0221359A - _02213490 - 2 ; case 8
	.short _02213522 - _02213490 - 2 ; case 9
	.short _02213536 - _02213490 - 2 ; case 10
	.short _0221354A - _02213490 - 2 ; case 11
	.short _0221355E - _02213490 - 2 ; case 12
	.short _02213572 - _02213490 - 2 ; case 13
	.short _02213586 - _02213490 - 2 ; case 14
	.short _022135B0 - _02213490 - 2 ; case 15
	.short _022135C4 - _02213490 - 2 ; case 16
_022134B2:
	ldr r5, _0221361C ; =0x00020E00
	bl MOD04_021D853C
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _022134D4
	add r0, r4, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r4, r2]
	mov r1, #0x1a
	bl ReadMsgDataIntoString
	b _022135DC
_022134D4:
	bl MOD04_021D853C
	add r1, r0, #0
	ldr r0, [r4]
	mov r2, #8
	bl FUN_0202822C
	cmp r0, #0
	bne _022134EA
	ldr r5, _02213620 ; =0x00050600
	b _022134F2
_022134EA:
	cmp r0, #1
	bne _022134F2
	mov r5, #0xc1
	lsl r5, r5, #0xa
_022134F2:
	bl MOD04_021D853C
	add r1, r0, #0
	ldr r0, [r4]
	bl FUN_020283A4
	add r1, r0, #0
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02021E28
	b _022135DC
_0221350C:
	add r0, r4, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r4, r2]
	mov r1, #0x17
	bl ReadMsgDataIntoString
	ldr r5, _0221361C ; =0x00020E00
	b _022135DC
_02213522:
	add r0, r4, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r4, r2]
	mov r1, #0x3b
	bl ReadMsgDataIntoString
	b _022135DC
_02213536:
	add r0, r4, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r4, r2]
	mov r1, #0x3c
	bl ReadMsgDataIntoString
	b _022135DC
_0221354A:
	add r0, r4, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r4, r2]
	mov r1, #0x3a
	bl ReadMsgDataIntoString
	b _022135DC
_0221355E:
	add r0, r4, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r4, r2]
	mov r1, #0x3e
	bl ReadMsgDataIntoString
	b _022135DC
_02213572:
	add r0, r4, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r4, r2]
	mov r1, #0x3f
	bl ReadMsgDataIntoString
	b _022135DC
_02213586:
	add r0, r4, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r4, r2]
	mov r1, #0x3d
	bl ReadMsgDataIntoString
	b _022135DC
_0221359A:
	add r0, r4, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r4, r2]
	mov r1, #0x19
	bl ReadMsgDataIntoString
	ldr r5, _0221361C ; =0x00020E00
	b _022135DC
_022135B0:
	add r0, r4, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r4, r2]
	mov r1, #0x18
	bl ReadMsgDataIntoString
	b _022135DC
_022135C4:
	add r0, r4, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r4, r2]
	mov r1, #0x2d
	bl ReadMsgDataIntoString
	b _022135DC
_022135D8:
	add sp, #0x10
	pop {r4, r5, r6, pc}
_022135DC:
	mov r1, #0x56
	lsl r1, r1, #2
	mov r0, #0
	ldr r1, [r4, r1]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0
	add r3, r0, #0
	mov r0, #0xd3
	lsl r0, r0, #2
	str r1, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	str r5, [sp, #8]
	mov r5, #0x9c
	str r1, [sp, #0xc]
	add r2, #0x59
	ldr r2, [r4, r2]
	add r0, r4, r0
	sub r3, r5, r3
	bl FUN_0201BDE0
	mov r0, #0xd3
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019220
_02213614:
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_02213618: .word 0x00010200
_0221361C: .word 0x00020E00
_02213620: .word 0x00050600
	thumb_func_end MOD56_0221341C

	thumb_func_start MOD56_02213624
MOD56_02213624: ; 0x02213624
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	mov r1, #0x13
	add r7, r2, #0
	bl FUN_02001470
	add r4, r0, #0
	ldr r6, _02213750 ; =0x00010200
	cmp r5, #0x20
	beq _02213642
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	bne _02213644
_02213642:
	b _0221374C
_02213644:
	mov r1, #0x24
	ldr r0, [r4, #4]
	mul r1, r5
	add r0, r0, r1
	add r0, #0x3f
	ldrb r0, [r0]
	cmp r0, #0x11
	bhi _022136B6
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02213660: ; jump table
	.short _022136B6 - _02213660 - 2 ; case 0
	.short _02213684 - _02213660 - 2 ; case 1
	.short _0221368A - _02213660 - 2 ; case 2
	.short _0221368A - _02213660 - 2 ; case 3
	.short _0221368A - _02213660 - 2 ; case 4
	.short _0221368A - _02213660 - 2 ; case 5
	.short _0221368A - _02213660 - 2 ; case 6
	.short _0221368A - _02213660 - 2 ; case 7
	.short _022136A8 - _02213660 - 2 ; case 8
	.short _02213690 - _02213660 - 2 ; case 9
	.short _02213694 - _02213660 - 2 ; case 10
	.short _02213698 - _02213660 - 2 ; case 11
	.short _0221369C - _02213660 - 2 ; case 12
	.short _022136A0 - _02213660 - 2 ; case 13
	.short _022136A4 - _02213660 - 2 ; case 14
	.short _022136AE - _02213660 - 2 ; case 15
	.short _022136B2 - _02213660 - 2 ; case 16
	.short _022136B6 - _02213660 - 2 ; case 17
_02213684:
	mov r1, #0x1a
	ldr r6, _02213754 ; =0x00020E00
	b _022136B8
_0221368A:
	mov r1, #0x17
	ldr r6, _02213754 ; =0x00020E00
	b _022136B8
_02213690:
	mov r1, #0x3b
	b _022136B8
_02213694:
	mov r1, #0x3c
	b _022136B8
_02213698:
	mov r1, #0x3a
	b _022136B8
_0221369C:
	mov r1, #0x3e
	b _022136B8
_022136A0:
	mov r1, #0x3f
	b _022136B8
_022136A4:
	mov r1, #0x3d
	b _022136B8
_022136A8:
	mov r1, #0x19
	ldr r6, _02213754 ; =0x00020E00
	b _022136B8
_022136AE:
	mov r1, #0x18
	b _022136B8
_022136B2:
	mov r1, #0x2d
	b _022136B8
_022136B6:
	mov r1, #0x37
_022136B8:
	cmp r1, #0
	beq _02213706
	add r0, r4, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r4, r2]
	bl ReadMsgDataIntoString
	mov r1, #0x56
	lsl r1, r1, #2
	mov r0, #0
	ldr r1, [r4, r1]
	add r2, r0, #0
	bl FUN_02002E14
	mov ip, r0
	mov r0, #0xdf
	lsl r0, r0, #2
	str r7, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	str r6, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	add r2, #0x59
	ldr r2, [r4, r2]
	mov r6, #0xa4
	mov r3, ip
	add r0, r4, r0
	sub r3, r6, r3
	bl FUN_0201BDE0
	mov r0, #0xdf
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019220
_02213706:
	ldr r0, [r4]
	add r1, r5, #0
	mov r2, #8
	bl FUN_0202822C
	ldr r1, _02213750 ; =0x00010200
	cmp r0, #0
	bne _0221371A
	ldr r1, _02213758 ; =0x00050600
	b _02213722
_0221371A:
	cmp r0, #1
	bne _02213722
	mov r1, #0xc1
	lsl r1, r1, #0xa
_02213722:
	str r7, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	lsl r2, r5, #2
	str r1, [sp, #8]
	mov r1, #0
	add r2, r4, r2
	mov r0, #0xdf
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0xd4
	ldr r2, [r2]
	add r0, r4, r0
	mov r3, #8
	bl FUN_0201BDE0
	mov r0, #0xdf
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019220
_0221374C:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02213750: .word 0x00010200
_02213754: .word 0x00020E00
_02213758: .word 0x00050600
	thumb_func_end MOD56_02213624

	thumb_func_start MOD56_0221375C
MOD56_0221375C: ; 0x0221375C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r4, r1, #0
	ldr r1, _0221389C ; =0x022162E0
	add r5, r3, #0
	ldrh r3, [r1, #0x10]
	add r7, r2, #0
	add r2, sp, #0
	strh r3, [r2, #0x30]
	ldrh r3, [r1, #0x12]
	add r0, #0xc0
	strh r3, [r2, #0x32]
	ldrh r3, [r1, #0x14]
	strh r3, [r2, #0x34]
	ldrh r3, [r1, #0x16]
	strh r3, [r2, #0x36]
	ldrh r3, [r1, #8]
	strh r3, [r2, #0x28]
	ldrh r3, [r1, #0xa]
	strh r3, [r2, #0x2a]
	ldrh r3, [r1, #0xc]
	strh r3, [r2, #0x2c]
	ldrh r3, [r1, #0xe]
	strh r3, [r2, #0x2e]
	ldrh r3, [r1, #0x38]
	strh r3, [r2, #0x20]
	ldrh r3, [r1, #0x3a]
	strh r3, [r2, #0x22]
	ldrh r3, [r1, #0x3c]
	strh r3, [r2, #0x24]
	ldrh r3, [r1, #0x3e]
	strh r3, [r2, #0x26]
	ldrh r3, [r1]
	strh r3, [r2, #0x18]
	ldrh r3, [r1, #2]
	strh r3, [r2, #0x1a]
	ldrh r3, [r1, #4]
	strh r3, [r2, #0x1c]
	ldrh r3, [r1, #6]
	strh r3, [r2, #0x1e]
	ldrh r3, [r1, #0x20]
	strh r3, [r2, #0x10]
	ldrh r3, [r1, #0x22]
	strh r3, [r2, #0x12]
	ldrh r3, [r1, #0x24]
	strh r3, [r2, #0x14]
	ldrh r1, [r1, #0x26]
	strh r1, [r2, #0x16]
	ldr r1, _022138A0 ; =0x02216320
	ldrh r3, [r1]
	strh r3, [r2, #8]
	ldrh r3, [r1, #2]
	strh r3, [r2, #0xa]
	ldrh r3, [r1, #4]
	strh r3, [r2, #0xc]
	ldrh r3, [r1, #6]
	strh r3, [r2, #0xe]
	ldrh r3, [r1, #8]
	strh r3, [r2]
	ldrh r3, [r1, #0xa]
	strh r3, [r2, #2]
	ldrh r3, [r1, #0xc]
	strh r3, [r2, #4]
	ldrh r1, [r1, #0xe]
	strh r1, [r2, #6]
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0201886C
	add r1, r0, #0
	mov r2, #0
	cmp r4, #0x11
	bhi _0221383A
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022137FA: ; jump table
	.short _0221383A - _022137FA - 2 ; case 0
	.short _0221381E - _022137FA - 2 ; case 1
	.short _02213826 - _022137FA - 2 ; case 2
	.short _02213826 - _022137FA - 2 ; case 3
	.short _02213826 - _022137FA - 2 ; case 4
	.short _02213826 - _022137FA - 2 ; case 5
	.short _02213826 - _022137FA - 2 ; case 6
	.short _02213826 - _022137FA - 2 ; case 7
	.short _0221382E - _022137FA - 2 ; case 8
	.short _02213822 - _022137FA - 2 ; case 9
	.short _02213822 - _022137FA - 2 ; case 10
	.short _02213822 - _022137FA - 2 ; case 11
	.short _02213822 - _022137FA - 2 ; case 12
	.short _02213822 - _022137FA - 2 ; case 13
	.short _02213822 - _022137FA - 2 ; case 14
	.short _0221382A - _022137FA - 2 ; case 15
	.short _02213832 - _022137FA - 2 ; case 16
	.short _02213836 - _022137FA - 2 ; case 17
_0221381E:
	add r0, sp, #0x18
	b _0221383C
_02213822:
	mov r2, #1
	lsl r2, r2, #0xc
_02213826:
	add r0, sp, #0x30
	b _0221383C
_0221382A:
	mov r2, #1
	lsl r2, r2, #0xc
_0221382E:
	add r0, sp, #0x28
	b _0221383C
_02213832:
	add r0, sp, #0x20
	b _0221383C
_02213836:
	add r0, sp, #8
	b _0221383C
_0221383A:
	add r0, sp, #0
_0221383C:
	ldr r3, [sp, #0x50]
	ldrh r4, [r0]
	lsl r3, r3, #5
	add r5, r5, r3
	add r6, r4, r2
	lsl r4, r5, #1
	strh r6, [r1, r4]
	ldrh r4, [r0, #2]
	add r6, r5, #1
	lsl r6, r6, #1
	add r4, r4, r2
	strh r4, [r1, r6]
	add r6, r5, #0
	ldrh r4, [r0, #4]
	add r6, #0x20
	lsl r6, r6, #1
	add r4, r4, r2
	strh r4, [r1, r6]
	ldrh r0, [r0, #6]
	add r5, #0x21
	add r2, r0, r2
	lsl r0, r5, #1
	strh r2, [r1, r0]
	cmp r7, #0
	beq _02213872
	add r2, sp, #0
	b _02213874
_02213872:
	add r2, sp, #0x10
_02213874:
	ldr r0, [sp, #0x54]
	ldrh r4, [r2]
	add r0, r0, r3
	lsl r3, r0, #1
	strh r4, [r1, r3]
	add r3, r0, #1
	ldrh r4, [r2, #2]
	lsl r3, r3, #1
	strh r4, [r1, r3]
	add r3, r0, #0
	add r3, #0x20
	add r0, #0x21
	ldrh r4, [r2, #4]
	lsl r3, r3, #1
	lsl r0, r0, #1
	strh r4, [r1, r3]
	ldrh r2, [r2, #6]
	strh r2, [r1, r0]
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0221389C: .word MOD56_022162E0
_022138A0: .word MOD56_02216320
	thumb_func_end MOD56_0221375C

	thumb_func_start MOD56_022138A4
MOD56_022138A4: ; 0x022138A4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r0, #0xc0
	add r7, r1, #0
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0201886C
	mov r6, #0
	mov r4, #5
_022138BA:
	add r0, r7, r6
	cmp r0, #0x20
	blt _022138C6
	mov r1, #0
	mov r2, #1
	b _022138E2
_022138C6:
	add r0, r5, r0
	ldrb r1, [r0, #0xc]
	cmp r1, #0
	bne _022138D4
	mov r1, #0
	mov r2, #1
	b _022138E2
_022138D4:
	mov r2, #0x24
	ldr r0, [r5, #4]
	mul r2, r1
	add r0, r0, r2
	ldrb r1, [r0, #0x1b]
	add r0, #0x21
	ldrb r2, [r0]
_022138E2:
	str r4, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	add r0, r5, #0
	mov r3, #3
	bl MOD56_0221375C
	add r6, r6, #1
	add r4, r4, #3
	cmp r6, #5
	blt _022138BA
	ldr r0, [r5, #4]
	ldrb r1, [r0, #0x1b]
	add r0, #0x21
	ldrb r2, [r0]
	cmp r1, #1
	bne _02213906
	mov r1, #0
_02213906:
	mov r0, #0x15
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	add r0, r5, #0
	mov r3, #3
	bl MOD56_0221375C
	add r5, #0xc0
	ldr r0, [r5]
	mov r1, #0
	bl FUN_02017CD0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD56_022138A4

	thumb_func_start MOD56_02213924
MOD56_02213924: ; 0x02213924
	push {r3, lr}
	cmp r2, #0
	bne _02213930
	ldr r0, _02213934 ; =0x000005DC
	bl FUN_020054C8
_02213930:
	pop {r3, pc}
	nop
_02213934: .word 0x000005DC
	thumb_func_end MOD56_02213924

	thumb_func_start MOD56_02213938
MOD56_02213938: ; 0x02213938
	push {r3, r4, r5, r6, r7, lr}
	mov r6, #0
	mov r7, #0x5d
	add r5, r0, #0
	add r4, r6, #0
	lsl r7, r7, #2
_02213944:
	add r0, r5, r4
	ldrb r2, [r0, #0xc]
	cmp r2, #0
	beq _0221395C
	add r0, r5, #0
	add r0, #0xb0
	ldr r0, [r0]
	ldr r1, [r5, r7]
	sub r2, r2, #1
	bl FUN_020128A0
	add r6, r6, #1
_0221395C:
	add r4, r4, #1
	cmp r4, #0x20
	blt _02213944
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xb0
	add r1, #0xcc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x1b
	mov r3, #0x20
	bl FUN_02012880
	add r0, r5, #0
	add r0, #0xb0
	add r5, #0xcc
	mov r2, #0x2e
	add r3, r2, #0
	ldr r0, [r0]
	ldr r1, [r5]
	sub r3, #0x30
	bl FUN_02012880
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD56_02213938

	thumb_func_start MOD56_02213990
MOD56_02213990: ; 0x02213990
	push {r3, r4, r5, r6, lr}
	sub sp, #0x34
	add r5, r0, #0
	mov r0, #0x22
	mov r1, #0x36
	bl FUN_02012838
	add r1, r5, #0
	add r1, #0xb0
	str r0, [r1]
	add r0, r5, #0
	bl MOD56_02213938
	add r4, r0, #0
	mov r0, #0xdf
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019048
	cmp r0, #0
	beq _022139D0
	mov r0, #0xdf
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0xdf
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
_022139D0:
	mov r0, #5
	str r0, [sp]
	mov r0, #0x15
	str r0, [sp, #4]
	mov r0, #0xe
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	add r0, r5, #0
	add r0, #0xc0
	mov r1, #0xdf
	lsl r1, r1, #2
	ldr r0, [r0]
	add r1, r5, r1
	mov r2, #3
	mov r3, #6
	bl FUN_02019064
	ldr r6, _02213A3C ; =0x022163F4
	add r3, sp, #0x14
	add r2, r3, #0
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r5, #0
	add r0, #0xb0
	ldr r0, [r0]
	add r1, r4, #2
	str r0, [sp, #0x14]
	mov r0, #0xdf
	lsl r0, r0, #2
	add r0, r5, r0
	str r0, [sp, #0x20]
	add r0, sp, #0x14
	strh r1, [r0, #0x10]
	mov r1, #0
	add r0, r2, #0
	add r2, r1, #0
	mov r3, #0x36
	str r5, [sp, #0x30]
	bl FUN_020010A8
	add r5, #0xb4
	str r0, [r5]
	add sp, #0x34
	pop {r3, r4, r5, r6, pc}
	nop
_02213A3C: .word MOD56_022163F4
	thumb_func_end MOD56_02213990

	thumb_func_start MOD56_02213A40
MOD56_02213A40: ; 0x02213A40
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0xd3
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019048
	cmp r0, #0
	beq _02213A6A
	mov r0, #0xd3
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0xd3
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019178
_02213A6A:
	mov r0, #0x15
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	lsl r0, r0, #5
	str r0, [sp, #0x10]
	add r0, r4, #0
	add r0, #0xc0
	mov r1, #0xd3
	lsl r1, r1, #2
	ldr r0, [r0]
	add r1, r4, r1
	mov r2, #3
	mov r3, #7
	bl FUN_02019064
	add sp, #0x14
	pop {r3, r4, pc}
	thumb_func_end MOD56_02213A40

	thumb_func_start MOD56_02213A94
MOD56_02213A94: ; 0x02213A94
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r4, r1, #0
	bl MOD56_02216248
	add r0, r5, #0
	bl MOD56_02216274
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	mov r1, #3
	bl FUN_02018744
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	add r2, r5, #0
	str r3, [sp, #8]
	mov r0, #0x36
	str r0, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	mov r0, #0x5c
	mov r1, #5
	bl FUN_020068C8
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019048
	cmp r0, #0
	beq _02213AF0
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200CCF8
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
_02213AF0:
	add r0, r5, #0
	add r0, #0xb0
	ldr r0, [r0]
	cmp r0, #0
	beq _02213B2C
	mov r0, #0xdf
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
	add r0, r5, #0
	add r0, #0xb4
	mov r1, #0
	ldr r0, [r0]
	add r2, r1, #0
	bl FUN_02001300
	add r0, r5, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xb0
	ldr r0, [r0]
	bl FUN_02012870
	add r0, r5, #0
	mov r1, #0
	add r0, #0xb0
	str r1, [r0]
_02213B2C:
	mov r0, #1
	str r0, [sp]
	mov r0, #0x15
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _02213BEC ; =0x000001CA
	mov r1, #0xd7
	str r0, [sp, #0x10]
	add r0, r5, #0
	add r0, #0xc0
	lsl r1, r1, #2
	ldr r0, [r0]
	add r1, r5, r1
	mov r2, #3
	mov r3, #4
	bl FUN_02019064
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_02019620
	add r0, r5, #0
	mov r2, #0x16
	add r0, #0xcc
	lsl r2, r2, #4
	ldr r0, [r0]
	ldr r2, [r5, r2]
	mov r1, #0x12
	bl ReadMsgDataIntoString
	mov r3, #0
	str r3, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	ldr r0, _02213BF0 ; =0x000F0E00
	add r2, #0x61
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	mov r0, #0xd7
	lsl r0, r0, #2
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	bl FUN_0201BDE0
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019220
	add r0, r5, #0
	bl MOD56_02216120
	add r0, r5, #0
	bl MOD56_02212EFC
	add r0, r5, #0
	bl MOD56_02213990
	add r0, r5, #0
	bl MOD56_02213A40
	add r0, r5, #0
	mov r1, #0
	bl MOD56_022138A4
	add r0, r5, #0
	mov r1, #0x10
	bl MOD56_0221617C
	mov r1, #0
	mov r0, #0xf6
	mvn r1, r1
	lsl r0, r0, #2
	str r1, [r5, r0]
	bl MOD04_021D865C
	mov r0, #0x33
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x3b
	mov r1, #0x13
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_02213BEC: .word 0x000001CA
_02213BF0: .word 0x000F0E00
	thumb_func_end MOD56_02213A94

	thumb_func_start MOD56_02213BF4
MOD56_02213BF4: ; 0x02213BF4
	push {r3, lr}
	bl FUN_0203300C
	cmp r0, #1
	bne _02213C02
	mov r0, #1
	pop {r3, pc}
_02213C02:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD56_02213BF4

	thumb_func_start MOD56_02213C08
MOD56_02213C08: ; 0x02213C08
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	bl MOD56_02212EFC
	add r4, r0, #0
	add r0, r5, #0
	bl MOD56_02212F28
	ldr r1, [r5, #8]
	cmp r1, r4
	bne _02213C24
	cmp r0, #0
	beq _02213CA8
_02213C24:
	add r0, r5, #0
	add r0, #0xb0
	ldr r0, [r0]
	bl FUN_0201291C
	add r0, r5, #0
	add r0, #0xb4
	ldr r0, [r0]
	mov r1, #2
	add r2, r4, #2
	bl FUN_02001538
	cmp r4, #3
	ble _02213C50
	add r0, r5, #0
	add r0, #0xb4
	ldr r0, [r0]
	mov r1, #3
	mov r2, #5
	bl FUN_02001538
	b _02213C5E
_02213C50:
	add r0, r5, #0
	add r0, #0xb4
	ldr r0, [r0]
	mov r1, #3
	add r2, r4, #2
	bl FUN_02001538
_02213C5E:
	add r0, r5, #0
	bl MOD56_02213938
	add r0, r5, #0
	add r0, #0xb4
	add r1, sp, #0xc
	ldr r0, [r0]
	add r1, #2
	add r2, sp, #0xc
	bl FUN_02001448
	cmp r4, #3
	blt _02213C84
	add r0, sp, #0xc
	ldrh r1, [r0, #2]
	sub r2, r4, #3
	cmp r2, r1
	bgt _02213C84
	strh r2, [r0, #2]
_02213C84:
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	add r0, r5, #0
	str r1, [sp, #8]
	add r3, sp, #0xc
	add r0, #0xb4
	ldrh r2, [r3, #2]
	ldrh r3, [r3]
	ldr r0, [r0]
	bl FUN_020013C8
	add r0, r5, #0
	add r0, #0xb4
	ldr r0, [r0]
	bl FUN_02001328
	str r4, [r5, #8]
_02213CA8:
	add r0, r5, #0
	add r0, #0xb4
	add r1, sp, #0xc
	ldr r0, [r0]
	add r1, #2
	add r2, sp, #0xc
	bl FUN_02001448
	add r0, sp, #0xc
	ldr r1, [r5, #8]
	ldrh r3, [r0]
	ldrh r2, [r0, #2]
	add r1, r1, #2
	add r4, r2, r3
	cmp r1, r4
	bgt _02213D0C
	cmp r1, r4
	bgt _02213CF0
_02213CCC:
	cmp r2, #0
	beq _02213CD8
	ldrh r1, [r0, #2]
	sub r1, r1, #1
	strh r1, [r0, #2]
	b _02213CE2
_02213CD8:
	cmp r3, #0
	beq _02213CE2
	ldrh r1, [r0]
	sub r1, r1, #1
	strh r1, [r0]
_02213CE2:
	ldrh r3, [r0]
	ldr r1, [r5, #8]
	ldrh r2, [r0, #2]
	add r4, r1, #2
	add r1, r2, r3
	cmp r4, r1
	ble _02213CCC
_02213CF0:
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	add r0, r5, #0
	str r1, [sp, #8]
	add r0, #0xb4
	ldr r0, [r0]
	bl FUN_020013C8
	add r0, r5, #0
	add r0, #0xb4
	ldr r0, [r0]
	bl FUN_02001328
_02213D0C:
	add r1, sp, #0xc
	ldrh r1, [r1, #2]
	add r0, r5, #0
	bl MOD56_022138A4
	add r2, sp, #0xc
	ldrh r3, [r2]
	mov r0, #0x33
	lsl r0, r0, #4
	lsl r2, r3, #1
	add r2, r3, r2
	add r2, r2, #6
	ldr r0, [r5, r0]
	mov r1, #0x10
	lsl r2, r2, #3
	bl MOD56_02214470
	add r0, sp, #0xc
	ldrh r0, [r0, #2]
	cmp r0, #0
	beq _02213D52
	mov r0, #0xca
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x20
	bl MOD56_02214470
	mov r0, #0xca
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	b _02213D5E
_02213D52:
	mov r0, #0xca
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
_02213D5E:
	add r0, sp, #0xc
	ldrh r1, [r0, #2]
	ldr r0, [r5, #8]
	sub r0, r0, #3
	cmp r1, r0
	bge _02213D88
	mov r0, #0xcb
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x9c
	bl MOD56_02214470
	mov r0, #0xcb
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	add sp, #0x10
	pop {r3, r4, r5, pc}
_02213D88:
	mov r0, #0xcb
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	thumb_func_end MOD56_02213C08

	thumb_func_start MOD56_02213D98
MOD56_02213D98: ; 0x02213D98
	push {r4, r5, r6, lr}
	mov r6, #0
	mvn r6, r6
	add r5, r0, #0
	add r4, r1, #0
	bl MOD56_02213C08
	bl MOD04_021D8640
	add r1, r6, #0
	cmp r0, r1
	bne _02213DEE
	ldr r0, _02213F84 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #1
	lsl r0, r0, #0xa
	tst r0, r1
	beq _02213DEE
	add r0, r5, #0
	bl MOD56_0221620C
	cmp r0, #0
	beq _02213DD2
	add r0, r5, #0
	mov r1, #0x35
	mov r2, #0
	bl MOD56_02215EA4
	b _02213DDC
_02213DD2:
	add r0, r5, #0
	mov r1, #0x36
	mov r2, #0
	bl MOD56_02215EA4
_02213DDC:
	ldr r0, _02213F88 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0x3b
	mov r1, #0x14
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_02213DEE:
	bl FUN_02033250
	cmp r0, #0
	beq _02213E00
	add r0, r5, #0
	bl MOD56_02213030
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_02213E00:
	add r0, r5, #0
	bl MOD56_02213BF4
	cmp r0, #0
	beq _02213E1C
	ldr r0, _02213F8C ; =0x00000624
	bl FUN_020054C8
	mov r0, #0x3b
	mov r1, #0x2f
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_02213E1C:
	mov r0, #0xf6
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	bne _02213E5C
	bl MOD04_021D8640
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _02213E5C
	bl MOD04_021D8640
	mov r1, #0xf6
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r1, [r5, r1]
	add r0, r5, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #0x2a
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0xeb
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
	b _02213ECE
_02213E5C:
	mov r0, #0xf6
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	beq _02213ECE
	bl MOD04_021D8640
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _02213ECE
	mov r0, #0xdf
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
	add r0, r5, #0
	add r0, #0xb4
	mov r1, #0
	ldr r0, [r0]
	add r2, r1, #0
	bl FUN_02001300
	add r0, r5, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xb0
	ldr r0, [r0]
	bl FUN_02012870
	add r0, r5, #0
	mov r1, #0
	add r0, #0xb0
	str r1, [r0]
	mov r1, #0xf6
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	add r0, r5, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #0xe
	mov r2, #0
	bl MOD56_02215EA4
	bl FUN_020331E8
	mov r0, #0x3b
	mov r1, #0x1b
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_02213ECE:
	mov r0, #0xf6
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	bne _02213EE8
	add r0, r5, #0
	add r0, #0xb4
	ldr r0, [r0]
	bl FUN_02001204
	add r6, r0, #0
_02213EE8:
	mov r0, #1
	mvn r0, r0
	cmp r6, r0
	beq _02213EFA
	add r0, r0, #1
	cmp r6, r0
	bne _02213F32
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_02213EFA:
	ldr r0, _02213F88 ; =0x000005DD
	bl FUN_020054C8
	ldr r0, [r5, #4]
	ldrb r0, [r0, #0x1b]
	bl MOD56_02211E88
	cmp r0, #0
	beq _02213F16
	mov r0, #0x3b
	mov r1, #0x27
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02213F2E
_02213F16:
	mov r0, #0xed
	mov r1, #8
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0x38
	sub r0, r0, #4
	str r1, [r5, r0]
	add r0, r5, #0
	mov r1, #0x18
	mov r2, #1
	bl MOD56_02215EA4
_02213F2E:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_02213F32:
	ldr r0, _02213F88 ; =0x000005DD
	bl FUN_020054C8
	ldr r0, [r5, #4]
	ldrb r0, [r0, #0x1b]
	bl MOD56_02211E88
	cmp r0, #0
	beq _02213F4E
	mov r0, #0x3b
	mov r1, #0x27
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02213F7E
_02213F4E:
	cmp r6, #0x20
	bne _02213F76
	ldr r0, [r5, #4]
	ldrb r0, [r0, #0x1b]
	cmp r0, #0x10
	bne _02213F64
	mov r0, #0x3b
	mov r1, #0x24
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02213F7E
_02213F64:
	bl MOD56_02211E88
	cmp r0, #0
	beq _02213F7E
	mov r0, #0x3b
	mov r1, #0x27
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02213F7E
_02213F76:
	mov r0, #0x3b
	mov r1, #0x2a
	lsl r0, r0, #4
	str r1, [r5, r0]
_02213F7E:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	nop
_02213F84: .word gUnknown21C48B8
_02213F88: .word 0x000005DD
_02213F8C: .word 0x00000624
	thumb_func_end MOD56_02213D98

	thumb_func_start MOD56_02213F90
MOD56_02213F90: ; 0x02213F90
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD56_02213BF4
	cmp r0, #0
	beq _02213FA8
	mov r0, #0x3b
	mov r1, #0x13
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02213FC8
_02213FA8:
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02213FC8
	mov r0, #0x3b
	mov r1, #0x13
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r5, #0
	bl MOD56_02216120
_02213FC8:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD56_02213F90

	thumb_func_start MOD56_02213FCC
MOD56_02213FCC: ; 0x02213FCC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, _022140A0 ; =gUnknown21C48B8
	add r5, r0, #0
	ldr r2, [r1, #0x48]
	mov r1, #2
	tst r1, r2
	beq _02213FEE
	mov r1, #0x43
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x41
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221407C
_02213FEE:
	bl FUN_0203300C
	cmp r0, #5
	bne _02214016
	bl MOD04_021D853C
	add r1, r0, #0
	add r0, r5, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #0xb
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1b
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221407C
_02214016:
	bl FUN_0203300C
	cmp r0, #3
	bne _0221403E
	bl MOD04_021D853C
	add r1, r0, #0
	add r0, r5, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #0xe
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1b
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221407C
_0221403E:
	bl FUN_0203300C
	cmp r0, #4
	beq _0221404E
	bl FUN_02033128
	cmp r0, #0
	beq _0221406E
_0221404E:
	bl MOD04_021D853C
	add r1, r0, #0
	add r0, r5, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #0xf
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1b
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221407C
_0221406E:
	bl FUN_02033250
	cmp r0, #0
	beq _0221407C
	add r0, r5, #0
	bl MOD56_02213030
_0221407C:
	bl FUN_0203300C
	cmp r0, #1
	bne _0221409A
	add r0, r5, #0
	bl MOD56_02216274
	add r0, r5, #0
	mov r1, #1
	bl MOD56_0221617C
	mov r0, #0x3b
	mov r1, #0x18
	lsl r0, r0, #4
	str r1, [r5, r0]
_0221409A:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_022140A0: .word gUnknown21C48B8
	thumb_func_end MOD56_02213FCC

	thumb_func_start MOD56_022140A4
MOD56_022140A4: ; 0x022140A4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0203300C
	cmp r0, #1
	bne _022140D8
	bl MOD04_021D853C
	add r1, r0, #0
	add r0, r5, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #0xa
	mov r2, #0
	bl MOD56_02215EA4
	add r0, r5, #0
	mov r1, #1
	bl MOD56_0221617C
	mov r0, #0x3b
	mov r1, #0x17
	lsl r0, r0, #4
	str r1, [r5, r0]
_022140D8:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD56_022140A4

	thumb_func_start MOD56_022140DC
MOD56_022140DC: ; 0x022140DC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02214116
	ldr r0, _0221411C ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0221410E
	add r0, r5, #0
	bl MOD56_02216120
	mov r0, #0x3b
	mov r1, #0x18
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02214116
_0221410E:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD56_02214120
_02214116:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_0221411C: .word gUnknown21C48B8
	thumb_func_end MOD56_022140DC

	thumb_func_start MOD56_02214120
MOD56_02214120: ; 0x02214120
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD56_02213C08
	mov r0, #0xce
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0xcd
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	bl FUN_0203300C
	cmp r0, #5
	bne _0221416A
	bl MOD04_021D853C
	add r1, r0, #0
	add r0, r5, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #0xb
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1b
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221422E
_0221416A:
	bl FUN_0203300C
	cmp r0, #3
	bne _02214192
	bl MOD04_021D853C
	add r1, r0, #0
	add r0, r5, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #0xe
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1b
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221422E
_02214192:
	bl FUN_0203300C
	cmp r0, #4
	beq _022141A2
	bl FUN_02033128
	cmp r0, #0
	beq _022141C2
_022141A2:
	bl MOD04_021D853C
	add r1, r0, #0
	add r0, r5, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #0xf
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1b
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221422E
_022141C2:
	bl FUN_02033250
	cmp r0, #0
	beq _022141D2
	add r0, r5, #0
	bl MOD56_02213030
	b _0221422E
_022141D2:
	ldr r0, _02214234 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _022141F0
	add r0, r5, #0
	mov r1, #0x10
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x19
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221422E
_022141F0:
	bl MOD04_021D861C
	cmp r0, #0
	beq _02214214
	mov r0, #0xce
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x20
	mov r2, #0xb0
	bl MOD56_02214470
	mov r0, #0xce
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	b _0221422E
_02214214:
	mov r0, #0xcd
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x20
	mov r2, #0xb0
	bl MOD56_02214470
	mov r0, #0xcd
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
_0221422E:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_02214234: .word gUnknown21C48B8
	thumb_func_end MOD56_02214120

	thumb_func_start MOD56_02214238
MOD56_02214238: ; 0x02214238
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0221427E
	bl MOD04_021D853C
	add r1, r0, #0
	ldr r0, [r5]
	bl FUN_020285D0
	mov r0, #0x36
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, _02214284 ; =0x02216308
	ldr r2, _02214288 ; =0x000001D9
	mov r3, #0xb
	bl FUN_02002198
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0x3b
	mov r1, #0x1a
	lsl r0, r0, #4
	str r1, [r5, r0]
_0221427E:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_02214284: .word MOD56_02216308
_02214288: .word 0x000001D9
	thumb_func_end MOD56_02214238

	thumb_func_start MOD56_0221428C
MOD56_0221428C: ; 0x0221428C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	add r4, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _022142F0
	bl FUN_0203300C
	cmp r0, #4
	bge _022142C0
	bl FUN_02033128
	cmp r0, #0
	bne _022142C0
	mov r0, #0
	bl FUN_02030E7C
	cmp r0, #0
	bne _022142EC
_022142C0:
	add r0, r5, #0
	mov r1, #0x10
	bl MOD56_0221617C
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021EC
	mov r0, #0
	mov r1, #0xf6
	mvn r0, r0
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	mov r2, #0x14
	sub r0, #0x14
	str r2, [r5, r0]
	mov r0, #0x40
	sub r1, #0x28
	str r0, [r5, r1]
_022142EC:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_022142F0:
	cmp r0, #0
	bne _0221431A
	add r0, r5, #0
	mov r1, #0x10
	bl MOD56_0221617C
	bl FUN_0203323C
	mov r0, #0
	mov r1, #0xf6
	mvn r0, r0
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	mov r2, #0x14
	sub r0, #0x14
	str r2, [r5, r0]
	mov r0, #0x40
	sub r1, #0x28
	str r0, [r5, r1]
	b _02214322
_0221431A:
	mov r0, #0x3b
	mov r1, #0x18
	lsl r0, r0, #4
	str r1, [r5, r0]
_02214322:
	add r0, r5, #0
	bl MOD56_02216120
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD56_0221428C

	thumb_func_start MOD56_0221432C
MOD56_0221432C: ; 0x0221432C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldr r1, [r5, #4]
	ldrb r1, [r1, #0x1b]
	cmp r1, #0x10
	beq _02214340
	mov r1, #0x10
	bl MOD56_0221617C
_02214340:
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _0221435E
	mov r0, #0xf1
	mov r1, #0x1e
	lsl r0, r0, #2
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_0221435E:
	mov r0, #0xf1
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	sub r1, r1, #1
	str r1, [r5, r0]
	ldr r1, _022143B0 ; =gUnknown21C48B8
	ldr r2, [r1, #0x48]
	mov r1, #3
	tst r1, r2
	bne _02214378
	ldr r0, [r5, r0]
	cmp r0, #0
	bne _022143AC
_02214378:
	add r0, r5, #0
	bl MOD56_02216120
	bl FUN_020331E8
	add r0, r5, #0
	add r0, #0xb0
	ldr r0, [r0]
	cmp r0, #0
	bne _0221439C
	mov r0, #0xf1
	mov r1, #0x14
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0x40
	sub r0, #0x14
	str r1, [r5, r0]
	b _022143AC
_0221439C:
	mov r1, #0
	mov r0, #0xf6
	mvn r1, r1
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0x13
	sub r0, #0x28
	str r1, [r5, r0]
_022143AC:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_022143B0: .word gUnknown21C48B8
	thumb_func_end MOD56_0221432C

	thumb_func_start MOD56_022143B4
MOD56_022143B4: ; 0x022143B4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _022143D0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_022143D0:
	ldr r0, _02214400 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _022143FA
	add r0, r5, #0
	bl MOD56_02216120
	add r0, r5, #0
	mov r1, #0x10
	bl MOD56_0221617C
	bl FUN_020331E8
	mov r0, #0xf1
	mov r1, #0x14
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0x40
	sub r0, #0x14
	str r1, [r5, r0]
_022143FA:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_02214400: .word gUnknown21C48B8
	thumb_func_end MOD56_022143B4

	thumb_func_start MOD56_02214404
MOD56_02214404: ; 0x02214404
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _02214420
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_02214420:
	ldr r0, _02214460 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0221445C
	add r0, r5, #0
	bl MOD56_02216120
	add r0, r5, #0
	mov r1, #0x10
	bl MOD56_0221617C
	add r0, r5, #0
	add r0, #0xb0
	ldr r0, [r0]
	cmp r0, #0
	bne _0221444C
	mov r0, #0x3b
	mov r1, #0x12
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221445C
_0221444C:
	mov r1, #0
	mov r0, #0xf6
	mvn r1, r1
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0x13
	sub r0, #0x28
	str r1, [r5, r0]
_0221445C:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02214460: .word gUnknown21C48B8
	thumb_func_end MOD56_02214404

	thumb_func_start MOD56_02214464
MOD56_02214464: ; 0x02214464
	add r0, r1, #0
	bx lr
	thumb_func_end MOD56_02214464

	thumb_func_start MOD56_02214468
MOD56_02214468: ; 0x02214468
	add r0, r1, #0
	bx lr
	thumb_func_end MOD56_02214468

	thumb_func_start MOD56_0221446C
MOD56_0221446C: ; 0x0221446C
	add r0, r1, #0
	bx lr
	thumb_func_end MOD56_0221446C

	thumb_func_start MOD56_02214470
MOD56_02214470: ; 0x02214470
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r5, r2, #0
	cmp r1, #0
	ble _0221448E
	lsl r0, r1, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0221449C
_0221448E:
	lsl r0, r1, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0221449C:
	bl _ffix
	str r0, [sp]
	cmp r5, #0
	ble _022144B8
	lsl r0, r5, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _022144C6
_022144B8:
	lsl r0, r5, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_022144C6:
	bl _ffix
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, sp, #0
	bl FUN_02020044
	add sp, #0xc
	pop {r4, r5, pc}
	thumb_func_end MOD56_02214470

	thumb_func_start MOD56_022144DC
MOD56_022144DC: ; 0x022144DC
	push {r4, lr}
	add r4, r1, #0
	ldr r1, _02214500 ; =gUnknown21C48B8
	ldr r2, [r1, #0x48]
	mov r1, #3
	tst r1, r2
	beq _022144FC
	mov r1, #0xed
	mov r2, #8
	lsl r1, r1, #2
	str r2, [r0, r1]
	mov r2, #0x22
	sub r1, r1, #4
	str r2, [r0, r1]
	bl FUN_020331C4
_022144FC:
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0
_02214500: .word gUnknown21C48B8
	thumb_func_end MOD56_022144DC

	thumb_func_start MOD56_02214504
MOD56_02214504: ; 0x02214504
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #6
	mov r2, #0
	add r5, r0, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x28
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD56_02214504

	thumb_func_start MOD56_02214520
MOD56_02214520: ; 0x02214520
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0221455A
	mov r0, #0x36
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, _02214560 ; =0x02216308
	ldr r2, _02214564 ; =0x000001D9
	mov r3, #0xb
	bl FUN_02002198
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0x3b
	mov r1, #0x29
	lsl r0, r0, #4
	str r1, [r5, r0]
_0221455A:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_02214560: .word MOD56_02216308
_02214564: .word 0x000001D9
	thumb_func_end MOD56_02214520

	thumb_func_start MOD56_02214568
MOD56_02214568: ; 0x02214568
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	add r6, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021AC
	add r4, r0, #0
	mov r0, #0xf6
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	bne _022145A8
	bl MOD04_021D8640
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _022145A8
	cmp r4, r1
	bne _022145A6
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021EC
_022145A6:
	mov r4, #1
_022145A8:
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _022145B4
	add r0, r6, #0
	pop {r4, r5, r6, pc}
_022145B4:
	cmp r4, #0
	bne _022145C0
	add r0, r5, #0
	mov r1, #0x10
	bl MOD56_0221617C
_022145C0:
	add r0, r5, #0
	bl MOD56_02216120
	mov r0, #0x3b
	mov r1, #0x13
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD56_02214568

	thumb_func_start MOD56_022145D4
MOD56_022145D4: ; 0x022145D4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	ldr r3, _022146C0 ; =0x02216414
	add r2, sp, #0x14
	add r5, r0, #0
	add r7, r1, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	mov r0, #4
	mov r1, #0x36
	bl FUN_02012838
	add r1, r5, #0
	add r1, #0xb8
	ldr r4, _022146C4 ; =0x02216480
	str r0, [r1]
	mov r6, #0
_02214602:
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xb8
	add r1, #0xcc
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, [r4]
	ldr r3, [r4, #4]
	bl FUN_02012880
	add r6, r6, #1
	add r4, #8
	cmp r6, #4
	blt _02214602
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019048
	cmp r0, #0
	beq _02214642
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200CCF8
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
_02214642:
	mov r0, #9
	str r0, [sp]
	mov r0, #0xf
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x33
	str r0, [sp, #0x10]
	add r0, r5, #0
	add r0, #0xc0
	mov r1, #0xe3
	lsl r1, r1, #2
	ldr r0, [r0]
	add r1, r5, r1
	mov r2, #2
	mov r3, #0x10
	bl FUN_02019064
	mov r0, #0xe3
	lsl r0, r0, #2
	ldr r2, _022146C8 ; =0x000001D9
	add r0, r5, r0
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	add r0, r5, #0
	add r0, #0xb8
	ldr r0, [r0]
	mov r2, #0xe3
	lsl r2, r2, #2
	str r0, [sp, #0x14]
	add r0, r5, r2
	str r0, [sp, #0x20]
	add r2, #0x50
	ldrh r2, [r5, r2]
	add r0, sp, #0x14
	mov r1, #0
	mov r3, #0x36
	bl FUN_020010A8
	add r1, r5, #0
	add r1, #0xbc
	str r0, [r1]
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019220
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x25
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r7, #0
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022146C0: .word MOD56_02216414
_022146C4: .word MOD56_02216480
_022146C8: .word 0x000001D9
	thumb_func_end MOD56_022145D4

	thumb_func_start MOD56_022146CC
MOD56_022146CC: ; 0x022146CC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	bl MOD56_02211F88
	add r7, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _022146EE
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
_022146EE:
	add r0, r5, #0
	add r0, #0xbc
	ldr r0, [r0]
	bl FUN_02001204
	add r4, r0, #0
	add r0, r5, #0
	bl MOD56_02213BF4
	cmp r0, #0
	beq _02214708
	mov r4, #1
	mvn r4, r4
_02214708:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _0221471A
	add r0, r0, #1
	cmp r4, r0
	bne _02214730
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
_0221471A:
	mov r0, #0x3b
	mov r1, #0x13
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r5, #0
	bl MOD56_02216120
	ldr r0, _02214804 ; =0x000005DD
	bl FUN_020054C8
	b _022147CE
_02214730:
	ldr r0, _02214804 ; =0x000005DD
	bl FUN_020054C8
	cmp r4, #0xf
	bne _02214752
	cmp r7, #2
	bge _02214752
	add r0, r5, #0
	mov r1, #0x34
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1d
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _022147CE
_02214752:
	cmp r4, #1
	bne _0221476E
	cmp r7, #2
	bge _0221476E
	add r0, r5, #0
	mov r1, #0x42
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1d
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _022147CE
_0221476E:
	cmp r4, #1
	bhi _022147B8
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200CCF8
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
	add r0, r5, #0
	add r0, #0xbc
	mov r2, #0xf7
	lsl r2, r2, #2
	ldr r0, [r0]
	mov r1, #0
	add r2, r5, r2
	bl FUN_02001300
	add r0, r5, #0
	add r0, #0xb8
	ldr r0, [r0]
	bl FUN_02012870
	add r0, r5, #0
	add r1, r4, #0
	bl MOD56_02214808
	mov r0, #0x3b
	mov r1, #0x26
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
_022147B8:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD56_0221617C
	mov r0, #0x3b
	mov r1, #0x13
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r5, #0
	bl MOD56_02216120
_022147CE:
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200CCF8
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
	add r0, r5, #0
	add r0, #0xbc
	mov r2, #0xf7
	lsl r2, r2, #2
	ldr r0, [r0]
	mov r1, #0
	add r2, r5, r2
	bl FUN_02001300
	add r5, #0xb8
	ldr r0, [r5]
	bl FUN_02012870
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02214804: .word 0x000005DD
	thumb_func_end MOD56_022146CC

	thumb_func_start MOD56_02214808
MOD56_02214808: ; 0x02214808
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r0, #0
	cmp r1, #0
	bne _0221481A
	ldr r4, _0221490C ; =0x022164A0
	mov r7, #4
	mov r1, #1
	b _02214820
_0221481A:
	ldr r4, _02214910 ; =0x022164C0
	mov r7, #4
	mov r1, #0
_02214820:
	ldr r0, _02214914 ; =0x000003E2
	ldr r3, _02214918 ; =0x02216414
	strh r1, [r5, r0]
	add r2, sp, #0x14
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r7, #0
	mov r1, #0x36
	bl FUN_02012838
	add r1, r5, #0
	add r1, #0xb8
	mov r6, #0
	str r0, [r1]
	cmp r7, #0
	ble _02214868
_0221484C:
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xb8
	add r1, #0xcc
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, [r4]
	ldr r3, [r4, #4]
	bl FUN_02012880
	add r6, r6, #1
	add r4, #8
	cmp r6, r7
	blt _0221484C
_02214868:
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019048
	cmp r0, #0
	beq _0221488C
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200CCF8
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
_0221488C:
	mov r1, #9
	str r1, [sp]
	mov r1, #0xf
	lsl r0, r7, #1
	str r1, [sp, #4]
	lsl r1, r0, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #8]
	mov r1, #0xd
	str r1, [sp, #0xc]
	mov r1, #0x3b
	sub r0, r1, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	add r0, r5, #0
	add r0, #0xc0
	mov r1, #0xe3
	lsl r1, r1, #2
	ldr r0, [r0]
	add r1, r5, r1
	mov r2, #2
	mov r3, #0x10
	bl FUN_02019064
	mov r0, #0xe3
	lsl r0, r0, #2
	ldr r2, _0221491C ; =0x000001D9
	add r0, r5, r0
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	add r0, r5, #0
	add r0, #0xb8
	ldr r0, [r0]
	mov r3, #0xe3
	lsl r3, r3, #2
	str r0, [sp, #0x14]
	add r0, r5, r3
	add r2, r3, #0
	str r0, [sp, #0x20]
	add r2, #0x56
	ldrh r2, [r5, r2]
	add r3, #0x52
	add r0, sp, #0x14
	lsl r2, r2, #1
	add r2, r5, r2
	ldrh r2, [r2, r3]
	mov r1, #0
	mov r3, #0x36
	bl FUN_020010A8
	add r1, r5, #0
	add r1, #0xbc
	str r0, [r1]
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019220
	mov r0, #1
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0221490C: .word MOD56_022164A0
_02214910: .word MOD56_022164C0
_02214914: .word 0x000003E2
_02214918: .word MOD56_02216414
_0221491C: .word 0x000001D9
	thumb_func_end MOD56_02214808

	thumb_func_start MOD56_02214920
MOD56_02214920: ; 0x02214920
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r6, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _0221493C
	add r0, r6, #0
	pop {r4, r5, r6, pc}
_0221493C:
	add r0, r5, #0
	add r0, #0xbc
	ldr r0, [r0]
	bl FUN_02001204
	add r4, r0, #0
	add r0, r5, #0
	bl MOD56_02213BF4
	cmp r0, #0
	beq _02214956
	mov r4, #1
	mvn r4, r4
_02214956:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _02214968
	add r0, r0, #1
	cmp r4, r0
	bne _02214978
	add r0, r6, #0
	pop {r4, r5, r6, pc}
_02214968:
	ldr r0, _022149D0 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0x3b
	mov r1, #0x24
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02214994
_02214978:
	ldr r0, _022149D0 ; =0x000005DD
	bl FUN_020054C8
	add r0, r5, #0
	add r1, r4, #0
	bl MOD56_0221617C
	mov r0, #0x3b
	mov r1, #0x13
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r5, #0
	bl MOD56_02216120
_02214994:
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200CCF8
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
	ldr r3, _022149D4 ; =0x000003DE
	add r0, r5, #0
	add r2, r5, r3
	add r3, r3, #4
	ldrh r3, [r5, r3]
	add r0, #0xbc
	ldr r0, [r0]
	lsl r3, r3, #1
	mov r1, #0
	add r2, r2, r3
	bl FUN_02001300
	add r5, #0xb8
	ldr r0, [r5]
	bl FUN_02012870
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	nop
_022149D0: .word 0x000005DD
_022149D4: .word 0x000003DE
	thumb_func_end MOD56_02214920

	thumb_func_start MOD56_022149D8
MOD56_022149D8: ; 0x022149D8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x4c
	ldr r3, _02214BB0 ; =0x02216434
	add r5, r0, #0
	mov r0, #3
	add r2, sp, #0x2c
	str r1, [sp, #0x14]
	str r0, [sp, #0x20]
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r5, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r1, sp, #0x28
	bl FUN_0200143C
	add r0, sp, #0x28
	ldrh r0, [r0]
	add r0, r5, r0
	ldrb r0, [r0, #0xc]
	sub r0, r0, #1
	str r0, [sp, #0x18]
	ldr r1, [sp, #0x18]
	mov r0, #0x24
	mul r0, r1
	ldr r1, [r5, #4]
	add r1, r1, r0
	add r1, #0x3f
	ldrb r6, [r1]
	mov r1, #0xf9
	lsl r1, r1, #2
	strh r6, [r5, r1]
	ldr r2, [r5, #4]
	add r2, #0x45
	ldrb r2, [r2, r0]
	add r0, r1, #2
	mov r1, #0x36
	strh r2, [r5, r0]
	ldr r0, [r5, #4]
	add r0, #0x21
	ldrb r0, [r0]
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x1c]
	mov r0, #3
	bl FUN_02012838
	add r1, r5, #0
	add r1, #0xb8
	str r0, [r1]
	mov r0, #0
	ldr r4, _02214BB4 ; =0x02216350
	str r0, [sp, #0x24]
	add r7, sp, #0x28
_02214A52:
	ldr r0, [sp, #0x24]
	cmp r0, #0
	bne _02214AC8
	add r0, r6, #0
	bl MOD56_02211ECC
	cmp r0, #0
	bne _02214A6A
	cmp r6, #0
	beq _02214A6A
	cmp r6, #0x11
	blo _02214A7E
_02214A6A:
	ldrh r0, [r7, #0x16]
	sub r0, r0, #1
	strh r0, [r7, #0x16]
	ldrh r0, [r7, #0x14]
	sub r0, r0, #1
	strh r0, [r7, #0x14]
	ldr r0, [sp, #0x20]
	sub r0, r0, #1
	str r0, [sp, #0x20]
	b _02214ADC
_02214A7E:
	cmp r6, #0x10
	bne _02214AB2
	ldr r0, [sp, #0x1c]
	cmp r0, #2
	bne _02214A9E
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xb8
	add r1, #0xcc
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r3, [r4, #4]
	mov r2, #0x1a
	bl FUN_02012880
	b _02214ADC
_02214A9E:
	ldrh r0, [r7, #0x16]
	sub r0, r0, #1
	strh r0, [r7, #0x16]
	ldrh r0, [r7, #0x14]
	sub r0, r0, #1
	strh r0, [r7, #0x14]
	ldr r0, [sp, #0x20]
	sub r0, r0, #1
	str r0, [sp, #0x20]
	b _02214ADC
_02214AB2:
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xb8
	add r1, #0xcc
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, [r4]
	ldr r3, [r4, #4]
	bl FUN_02012880
	b _02214ADC
_02214AC8:
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xb8
	add r1, #0xcc
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, [r4]
	ldr r3, [r4, #4]
	bl FUN_02012880
_02214ADC:
	ldr r0, [sp, #0x24]
	add r4, #8
	add r0, r0, #1
	str r0, [sp, #0x24]
	cmp r0, #3
	blo _02214A52
	ldr r0, [sp, #0x20]
	mov r1, #3
	sub r0, r1, r0
	lsl r0, r0, #1
	add r0, #0xb
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0xf
	str r0, [sp, #4]
	ldr r0, [sp, #0x20]
	mov r1, #0xe3
	lsl r0, r0, #0x19
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x3b
	str r0, [sp, #0x10]
	add r0, r5, #0
	add r0, #0xc0
	lsl r1, r1, #2
	ldr r0, [r0]
	add r1, r5, r1
	mov r2, #2
	mov r3, #0x10
	bl FUN_02019064
	mov r0, #0xe3
	lsl r0, r0, #2
	ldr r2, _02214BB8 ; =0x000001D9
	add r0, r5, r0
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	add r0, r5, #0
	add r0, #0xb8
	ldr r0, [r0]
	mov r1, #0
	str r0, [sp, #0x2c]
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r5, r0
	str r0, [sp, #0x38]
	add r0, sp, #0x2c
	add r2, r1, #0
	mov r3, #0x36
	bl FUN_020010A8
	add r1, r5, #0
	add r1, #0xbc
	str r0, [r1]
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019220
	ldr r1, [sp, #0x18]
	add r0, r5, #0
	bl MOD56_022160E4
	cmp r6, #0xf
	bne _02214B6C
	mov r1, #3
	b _02214B9A
_02214B6C:
	add r0, r6, #0
	bl MOD56_02211E60
	cmp r0, #0
	beq _02214B7A
	mov r1, #2
	b _02214B9A
_02214B7A:
	cmp r6, #8
	bne _02214B82
	mov r1, #0x30
	b _02214B9A
_02214B82:
	add r0, r6, #0
	bl MOD56_02211EA4
	cmp r0, #0
	beq _02214B90
	mov r1, #0x2f
	b _02214B9A
_02214B90:
	cmp r6, #1
	bne _02214B98
	mov r1, #0x31
	b _02214B9A
_02214B98:
	mov r1, #4
_02214B9A:
	add r0, r5, #0
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x2b
	lsl r0, r0, #4
	str r1, [r5, r0]
	ldr r0, [sp, #0x14]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02214BB0: .word MOD56_02216434
_02214BB4: .word MOD56_02216350
_02214BB8: .word 0x000001D9
	thumb_func_end MOD56_022149D8

	thumb_func_start MOD56_02214BBC
MOD56_02214BBC: ; 0x02214BBC
	push {r4, r5}
	ldr r2, _02214BF8 ; =0x000001EF
	mov r5, #0
	add r1, r2, #0
	sub r1, #0x1f
	add r3, r2, #0
_02214BC8:
	ldrh r4, [r0]
	cmp r4, r3
	bne _02214BD4
	mov r0, #0
	pop {r4, r5}
	bx lr
_02214BD4:
	cmp r4, r2
	bls _02214BDE
	mov r0, #0
	pop {r4, r5}
	bx lr
_02214BDE:
	ldrh r4, [r0, #0xc]
	cmp r4, r1
	bls _02214BEA
	mov r0, #0
	pop {r4, r5}
	bx lr
_02214BEA:
	add r5, r5, #1
	add r0, r0, #2
	cmp r5, #6
	blt _02214BC8
	mov r0, #1
	pop {r4, r5}
	bx lr
	.align 2, 0
_02214BF8: .word 0x000001EF
	thumb_func_end MOD56_02214BBC

	thumb_func_start MOD56_02214BFC
MOD56_02214BFC: ; 0x02214BFC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	str r1, [sp]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r6, #0
	bl FUN_0201BD70
	cmp r0, #0
	beq _02214C1E
	ldr r0, [sp]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_02214C1E:
	add r0, r4, #0
	add r0, #0xbc
	ldr r0, [r0]
	bl FUN_02001204
	add r5, r0, #0
	add r0, r4, #0
	bl MOD56_02213BF4
	cmp r0, #0
	beq _02214C36
	sub r5, r6, #2
_02214C36:
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	beq _02214C4A
	add r0, r0, #1
	cmp r5, r0
	bne _02214C5A
	ldr r0, [sp]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_02214C4A:
	ldr r0, _02214E20 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0x3b
	mov r1, #0x13
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _02214DE2
_02214C5A:
	ldr r0, _02214E20 ; =0x000005DD
	bl FUN_020054C8
	cmp r5, #1
	beq _02214C66
	b _02214DD6
_02214C66:
	mov r0, #0x3b
	mov r1, #0x13
	lsl r0, r0, #4
	str r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r1, sp, #0xc
	bl FUN_0200143C
	add r0, sp, #0xc
	ldrh r0, [r0]
	add r0, r4, r0
	ldrb r5, [r0, #0xc]
	mov r0, #0xfa
	lsl r0, r0, #2
	strh r5, [r4, r0]
	cmp r5, #0
	bne _02214C8E
	b _02214DE2
_02214C8E:
	add r0, r4, #0
	bl MOD56_02211F88
	sub r1, r5, #1
	str r0, [sp, #8]
	mov r0, #0x24
	add r3, r1, #0
	ldr r2, [r4, #4]
	mul r3, r0
	add r0, r2, r3
	add r0, #0x3f
	ldrb r0, [r0]
	str r0, [sp, #4]
	add r0, r2, r3
	add r0, #0x45
	ldrb r7, [r0]
	mov r0, #0xf9
	lsl r0, r0, #2
	ldrh r1, [r4, r0]
	ldr r0, [sp, #4]
	cmp r1, r0
	bne _02214CC6
	mov r0, #0xf9
	lsl r0, r0, #2
	add r0, r0, #2
	ldrh r0, [r4, r0]
	cmp r0, r7
	beq _02214CE4
_02214CC6:
	add r0, r4, #0
	sub r1, r5, #1
	bl MOD56_022160E4
	add r0, r4, #0
	mov r1, #0xc
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1d
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r6, #1
	b _02214DE2
_02214CE4:
	add r2, #0x24
	add r0, r2, r3
	bl MOD56_02214BBC
	cmp r0, #0
	bne _02214D0E
	add r0, r4, #0
	sub r1, r5, #1
	bl MOD56_022160E4
	add r0, r4, #0
	mov r1, #0xc
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1d
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r6, #1
	b _02214DE2
_02214D0E:
	ldr r0, [sp, #4]
	bl MOD56_02211EEC
	cmp r0, #0
	beq _02214D46
	ldr r0, [sp, #8]
	cmp r0, #2
	bge _02214D46
	ldr r0, [sp, #4]
	cmp r0, #0xf
	bne _02214D30
	add r0, r4, #0
	mov r1, #0x34
	mov r2, #0
	bl MOD56_02215EA4
	b _02214D3A
_02214D30:
	add r0, r4, #0
	mov r1, #0x42
	mov r2, #0
	bl MOD56_02215EA4
_02214D3A:
	mov r0, #0x3b
	mov r1, #0x1d
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r6, #1
	b _02214DE2
_02214D46:
	ldr r0, [r4, #4]
	add r0, #0x21
	ldrb r0, [r0]
	cmp r7, r0
	beq _02214D76
	cmp r7, #0
	beq _02214D60
	add r0, r4, #0
	mov r1, #0x44
	mov r2, #0
	bl MOD56_02215EA4
	b _02214D6A
_02214D60:
	add r0, r4, #0
	mov r1, #0x45
	mov r2, #0
	bl MOD56_02215EA4
_02214D6A:
	mov r0, #0x3b
	mov r1, #0x3e
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r6, #1
	b _02214DE2
_02214D76:
	ldr r0, [sp, #4]
	bl MOD56_02211F10
	add r7, r0, #0
	cmp r7, #0x11
	beq _02214DE2
	sub r0, r5, #1
	bl MOD04_021D8480
	cmp r0, #6
	bne _02214DE2
	sub r0, r5, #1
	bl FUN_02032FDC
	cmp r0, #0
	beq _02214DE2
	add r0, r4, #0
	add r1, r7, #0
	bl MOD56_0221617C
	add r0, r4, #0
	sub r1, r5, #1
	bl MOD56_022160E4
	add r0, r4, #0
	mov r1, #0xd
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0xcf
	lsl r0, r0, #2
	ldr r1, _02214E24 ; =0x000001E2
	add r0, r4, r0
	bl FUN_0200D858
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r4, r1]
	cmp r7, #1
	beq _02214DCA
	mov r1, #0x2c
	b _02214DCC
_02214DCA:
	mov r1, #0x15
_02214DCC:
	mov r0, #0x3b
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r6, #1
	b _02214DE2
_02214DD6:
	cmp r5, #2
	bne _02214DE2
	mov r0, #0x3b
	mov r1, #0x35
	lsl r0, r0, #4
	str r1, [r4, r0]
_02214DE2:
	cmp r6, #0
	bne _02214DEC
	add r0, r4, #0
	bl MOD56_02216120
_02214DEC:
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl FUN_0200CCF8
	mov r0, #0xe3
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019178
	add r0, r4, #0
	add r0, #0xbc
	mov r1, #0
	ldr r0, [r0]
	add r2, r1, #0
	bl FUN_02001300
	add r4, #0xb8
	ldr r0, [r4]
	bl FUN_02012870
	ldr r0, [sp]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02214E20: .word 0x000005DD
_02214E24: .word 0x000001E2
	thumb_func_end MOD56_02214BFC

	thumb_func_start MOD56_02214E28
MOD56_02214E28: ; 0x02214E28
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, _02214F08 ; =gUnknown21C48B8
	add r5, r0, #0
	ldr r2, [r1, #0x48]
	mov r1, #2
	tst r1, r2
	beq _02214E4A
	mov r1, #0x43
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x2d
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02214F02
_02214E4A:
	bl FUN_0203300C
	cmp r0, #3
	bne _02214E72
	bl MOD04_021D853C
	add r1, r0, #0
	add r0, r5, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #0xe
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1b
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02214F02
_02214E72:
	bl FUN_0203300C
	cmp r0, #5
	bne _02214E9A
	bl MOD04_021D853C
	add r1, r0, #0
	add r0, r5, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #0xb
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1b
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02214F02
_02214E9A:
	bl FUN_0203300C
	cmp r0, #4
	beq _02214EAA
	bl FUN_02033128
	cmp r0, #0
	beq _02214ECA
_02214EAA:
	bl MOD04_021D853C
	add r1, r0, #0
	add r0, r5, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #0xe
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1b
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02214F02
_02214ECA:
	bl FUN_02033250
	cmp r0, #0
	beq _02214EDA
	add r0, r5, #0
	bl MOD56_02213030
	b _02214F02
_02214EDA:
	bl FUN_0203300C
	cmp r0, #1
	bne _02214F02
	add r0, r5, #0
	bl MOD56_02216274
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0202DB14
	mov r0, #0xf1
	mov r1, #0x1e
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0x30
	sub r0, #0x14
	str r1, [r5, r0]
_02214F02:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_02214F08: .word gUnknown21C48B8
	thumb_func_end MOD56_02214E28

	thumb_func_start MOD56_02214F0C
MOD56_02214F0C: ; 0x02214F0C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02214F46
	mov r0, #0x36
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, _02214F4C ; =0x02216308
	ldr r2, _02214F50 ; =0x000001D9
	mov r3, #0xb
	bl FUN_02002198
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0x3b
	mov r1, #0x42
	lsl r0, r0, #4
	str r1, [r5, r0]
_02214F46:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_02214F4C: .word MOD56_02216308
_02214F50: .word 0x000001D9
	thumb_func_end MOD56_02214F0C

	thumb_func_start MOD56_02214F54
MOD56_02214F54: ; 0x02214F54
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	add r6, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021AC
	add r4, r0, #0
	add r0, r5, #0
	bl MOD56_02213BF4
	cmp r0, #0
	beq _02214F90
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _02214F86
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021EC
_02214F86:
	mov r0, #0x3b
	mov r1, #0x15
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02214FCC
_02214F90:
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _02214F9C
	add r0, r6, #0
	pop {r4, r5, r6, pc}
_02214F9C:
	cmp r4, #0
	bne _02214FC4
	add r0, r5, #0
	bl MOD56_02216248
	add r0, r5, #0
	mov r1, #0x10
	bl MOD56_0221617C
	bl FUN_020331E8
	mov r1, #0
	mov r0, #0xf6
	mvn r1, r1
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0x13
	sub r0, #0x28
	str r1, [r5, r0]
	b _02214FCC
_02214FC4:
	mov r0, #0x3b
	mov r1, #0x15
	lsl r0, r0, #4
	str r1, [r5, r0]
_02214FCC:
	add r0, r5, #0
	bl MOD56_02216120
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD56_02214F54

	thumb_func_start MOD56_02214FD8
MOD56_02214FD8: ; 0x02214FD8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02215012
	mov r0, #0x36
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, _02215018 ; =0x02216308
	ldr r2, _0221501C ; =0x000001D9
	mov r3, #0xb
	bl FUN_02002198
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0x3b
	mov r1, #0x2e
	lsl r0, r0, #4
	str r1, [r5, r0]
_02215012:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_02215018: .word MOD56_02216308
_0221501C: .word 0x000001D9
	thumb_func_end MOD56_02214FD8

	thumb_func_start MOD56_02215020
MOD56_02215020: ; 0x02215020
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	add r6, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021AC
	add r4, r0, #0
	add r0, r5, #0
	bl MOD56_02213BF4
	cmp r0, #0
	beq _0221505C
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _02215052
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021EC
_02215052:
	mov r0, #0x3b
	mov r1, #0x2c
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02215098
_0221505C:
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _02215068
	add r0, r6, #0
	pop {r4, r5, r6, pc}
_02215068:
	cmp r4, #0
	bne _02215090
	add r0, r5, #0
	bl MOD56_02216248
	add r0, r5, #0
	mov r1, #0x10
	bl MOD56_0221617C
	bl FUN_020331E8
	mov r1, #0
	mov r0, #0xf6
	mvn r1, r1
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0x13
	sub r0, #0x28
	str r1, [r5, r0]
	b _02215098
_02215090:
	mov r0, #0x3b
	mov r1, #0x2c
	lsl r0, r0, #4
	str r1, [r5, r0]
_02215098:
	add r0, r5, #0
	bl MOD56_02216120
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD56_02215020

	thumb_func_start MOD56_022150A4
MOD56_022150A4: ; 0x022150A4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #4]
	add r6, r1, #0
	ldrb r4, [r0, #0x1b]
	bl MOD04_021D853C
	mov r1, #0x24
	ldr r2, [r5, #4]
	mul r1, r0
	add r0, r2, r1
	add r0, #0x3f
	ldrb r0, [r0]
	cmp r4, #0xc
	bne _022150D0
	cmp r0, #5
	bne _022150D0
	mov r0, #0x3b
	mov r1, #0x30
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221517E
_022150D0:
	cmp r4, #0xd
	bne _022150E2
	cmp r0, #6
	bne _022150E2
	mov r0, #0x3b
	mov r1, #0x30
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221517E
_022150E2:
	cmp r4, #0xe
	bne _022150F4
	cmp r0, #7
	bne _022150F4
	mov r0, #0x3b
	mov r1, #0x30
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221517E
_022150F4:
	cmp r4, #9
	bne _02215106
	cmp r0, #2
	bne _02215106
	mov r0, #0x3b
	mov r1, #0x30
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221517E
_02215106:
	cmp r4, #0xa
	bne _02215118
	cmp r0, #3
	bne _02215118
	mov r0, #0x3b
	mov r1, #0x30
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221517E
_02215118:
	cmp r4, #0xb
	bne _0221512A
	cmp r0, #4
	bne _0221512A
	mov r0, #0x3b
	mov r1, #0x30
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221517E
_0221512A:
	cmp r4, #0xf
	bne _0221513C
	cmp r0, #8
	bne _0221513C
	mov r0, #0x3b
	mov r1, #0x30
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221517E
_0221513C:
	cmp r4, #0x10
	bne _02215150
	cmp r0, #1
	bne _02215150
	mov r0, #0x3b
	mov r1, #0x16
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r6, #0
	pop {r4, r5, r6, pc}
_02215150:
	bl MOD04_021D853C
	add r1, r0, #0
	add r0, r5, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #0xe
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1d
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r5, #0
	mov r1, #0x10
	bl MOD56_0221617C
	bl FUN_020331E8
	add r0, r6, #0
	pop {r4, r5, r6, pc}
_0221517E:
	bl MOD04_021D853C
	add r1, r0, #0
	add r0, r5, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #7
	mov r2, #0
	bl MOD56_02215EA4
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #0
	bl FUN_0202DB14
	mov r0, #0x3b
	mov r1, #0x30
	lsl r0, r0, #4
	str r1, [r5, r0]
	mov r1, #0x1e
	add r0, #0x14
	str r1, [r5, r0]
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD56_022150A4

	thumb_func_start MOD56_022151B4
MOD56_022151B4: ; 0x022151B4
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0203300C
	cmp r0, #3
	blt _022151E0
	mov r1, #0xf6
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	add r0, r4, #0
	bl MOD56_022160E4
	add r0, r4, #0
	mov r1, #0xe
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1b
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _022151F4
_022151E0:
	bl FUN_02033250
	cmp r0, #0
	beq _022151F0
	add r0, r4, #0
	bl MOD56_02213030
	b _022151F4
_022151F0:
	mov r0, #0
	pop {r4, pc}
_022151F4:
	mov r0, #0xfb
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD56_022151B4

	thumb_func_start MOD56_02215200
MOD56_02215200: ; 0x02215200
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0203300C
	cmp r0, #4
	bge _02215220
	bl FUN_02033128
	cmp r0, #0
	bne _02215220
	mov r0, #0
	bl FUN_02030E7C
	cmp r0, #0
	bne _0221525A
_02215220:
	mov r1, #0xfb
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	cmp r0, #0
	beq _02215236
	add r0, r5, #0
	mov r1, #0x40
	mov r2, #0
	bl MOD56_02215EA4
	b _0221524A
_02215236:
	sub r1, #0x14
	ldr r1, [r5, r1]
	add r0, r5, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #0xe
	mov r2, #0
	bl MOD56_02215EA4
_0221524A:
	mov r0, #0xfb
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0x1b
	sub r0, #0x3c
	str r1, [r5, r0]
	b _022152A2
_0221525A:
	add r0, r5, #0
	bl MOD56_022151B4
	cmp r0, #0
	bne _022152A2
	mov r0, #0xf1
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	cmp r1, #0
	bne _02215292
	mov r0, #0xd
	bl FUN_020315D8
	cmp r0, #0
	beq _022152A2
	bl FUN_0203168C
	mov r0, #0xe
	bl FUN_02031588
	mov r0, #0xfb
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0x31
	sub r0, #0x3c
	str r1, [r5, r0]
	b _022152A2
_02215292:
	sub r1, r1, #1
	str r1, [r5, r0]
	ldr r0, [r5, r0]
	cmp r0, #0
	bne _022152A2
	mov r0, #0xd
	bl FUN_02031588
_022152A2:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD56_02215200

	thumb_func_start MOD56_022152A8
MOD56_022152A8: ; 0x022152A8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD56_022151B4
	cmp r0, #0
	bne _022152DA
	mov r0, #0xe
	bl FUN_020315D8
	cmp r0, #0
	beq _022152DA
	ldr r0, [r5, #4]
	ldrb r1, [r0, #0x1b]
	add r0, sp, #0
	strh r1, [r0]
	bl FUN_02031190
	add r1, sp, #0
	bl FUN_020316AC
	mov r0, #0x3b
	mov r1, #0x32
	lsl r0, r0, #4
	str r1, [r5, r0]
_022152DA:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD56_022152A8

	thumb_func_start MOD56_022152E0
MOD56_022152E0: ; 0x022152E0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	bl FUN_02031190
	mov r1, #1
	sub r0, r1, r0
	bl FUN_020316E0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD56_022151B4
	cmp r0, #0
	bne _0221534A
	cmp r4, #0
	beq _0221534A
	ldr r0, [r5, #4]
	ldrb r0, [r0, #0x1b]
	bl MOD56_02211F10
	lsl r0, r0, #0x10
	ldrh r1, [r4]
	lsr r0, r0, #0x10
	cmp r1, r0
	beq _0221531C
	ldr r0, [r5, #4]
	ldrb r0, [r0, #0x1b]
	cmp r1, r0
	bne _0221532C
_0221531C:
	mov r0, #0xf
	bl FUN_02031588
	mov r0, #0x3b
	mov r1, #0x33
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0221534A
_0221532C:
	bl MOD04_021D853C
	add r1, r0, #0
	add r0, r5, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #0xc
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1b
	lsl r0, r0, #4
	str r1, [r5, r0]
_0221534A:
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD56_022152E0

	thumb_func_start MOD56_02215350
MOD56_02215350: ; 0x02215350
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD56_022151B4
	cmp r0, #0
	bne _02215382
	mov r0, #0xf
	bl FUN_020315D8
	cmp r0, #0
	beq _02215382
	bl FUN_0202DBE0
	mov r0, #1
	add r1, r0, #0
	bl FUN_020334E8
	mov r0, #0x12
	bl FUN_02031588
	mov r0, #0x3b
	mov r1, #0x34
	lsl r0, r0, #4
	str r1, [r5, r0]
_02215382:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD56_02215350

	thumb_func_start MOD56_02215388
MOD56_02215388: ; 0x02215388
	push {r4, r5, lr}
	sub sp, #0x2c
	add r4, r0, #0
	add r5, r1, #0
	bl MOD56_022151B4
	cmp r0, #0
	bne _02215476
	mov r0, #0x12
	bl FUN_020315D8
	cmp r0, #0
	beq _02215476
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, sp, #0xc
	mov r2, #0x36
	bl FUN_020339B4
	add r0, r4, #0
	bl MOD56_02216120
	bl MOD04_021D853C
	mov r1, #0x24
	ldr r2, [r4, #4]
	mul r1, r0
	add r0, r2, r1
	add r0, #0x3f
	ldrb r1, [r0]
	cmp r1, #0xf
	beq _022153CE
	cmp r1, #8
	bne _022153DA
_022153CE:
	mov r0, #0xed
	mov r2, #7
	lsl r0, r0, #2
	mov r1, #8
	str r2, [r4, r0]
	b _02215450
_022153DA:
	cmp r1, #9
	beq _022153E2
	cmp r1, #2
	bne _022153EE
_022153E2:
	mov r0, #0xed
	mov r2, #1
	lsl r0, r0, #2
	mov r1, #2
	str r2, [r4, r0]
	b _02215450
_022153EE:
	cmp r1, #0xa
	beq _022153F6
	cmp r1, #3
	bne _02215402
_022153F6:
	mov r0, #0xed
	mov r2, #2
	lsl r0, r0, #2
	mov r1, #3
	str r2, [r4, r0]
	b _02215450
_02215402:
	cmp r1, #0xb
	beq _0221540A
	cmp r1, #4
	bne _02215416
_0221540A:
	mov r0, #0xed
	mov r2, #3
	lsl r0, r0, #2
	mov r1, #4
	str r2, [r4, r0]
	b _02215450
_02215416:
	cmp r1, #0xc
	beq _0221541E
	cmp r1, #5
	bne _0221542A
_0221541E:
	mov r0, #0xed
	mov r2, #4
	lsl r0, r0, #2
	mov r1, #5
	str r2, [r4, r0]
	b _02215450
_0221542A:
	cmp r1, #0xd
	beq _02215432
	cmp r1, #6
	bne _0221543E
_02215432:
	mov r0, #0xed
	mov r2, #5
	lsl r0, r0, #2
	mov r1, #6
	str r2, [r4, r0]
	b _02215450
_0221543E:
	cmp r1, #0xe
	beq _02215446
	cmp r1, #7
	bne _02215450
_02215446:
	mov r0, #0xed
	mov r2, #6
	lsl r0, r0, #2
	mov r1, #7
	str r2, [r4, r0]
_02215450:
	add r0, r4, #0
	bl MOD56_0221617C
	mov r0, #1
	bl FUN_02031400
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x36
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r5, #2
_02215476:
	add r0, r5, #0
	add sp, #0x2c
	pop {r4, r5, pc}
	thumb_func_end MOD56_02215388

	thumb_func_start MOD56_0221547C
MOD56_0221547C: ; 0x0221547C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r0, #0xc0
	add r4, r1, #0
	ldr r0, [r0]
	mov r1, #3
	bl FUN_02018744
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	add r2, r5, #0
	str r3, [sp, #8]
	mov r0, #0x36
	str r0, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	mov r0, #0x5c
	mov r1, #5
	bl FUN_020068C8
	mov r0, #0xf3
	mov r1, #0
	lsl r0, r0, #2
	strb r1, [r5, r0]
	mov r1, #0x12
	sub r0, #0x1c
	str r1, [r5, r0]
	add r0, r4, #0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	thumb_func_end MOD56_0221547C

	thumb_func_start MOD56_022154BC
MOD56_022154BC: ; 0x022154BC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r0, #0xc0
	add r7, r1, #0
	ldr r0, [r0]
	mov r1, #3
	bl FUN_02018744
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x36
	add r2, r5, #0
	str r0, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	mov r0, #0x5c
	mov r1, #6
	mov r3, #1
	bl FUN_020068C8
	mov r0, #0xcb
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x33
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0xca
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0xe7
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019048
	cmp r0, #0
	beq _02215532
	mov r0, #0xe7
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200CCF8
	mov r0, #0xe7
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
_02215532:
	mov r0, #2
	str r0, [sp]
	mov r0, #0x1a
	str r0, [sp, #4]
	mov r0, #0xe
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	add r0, r5, #0
	add r0, #0xc0
	mov r1, #0xe7
	lsl r1, r1, #2
	mov r2, #3
	ldr r0, [r0]
	add r1, r5, r1
	add r3, r2, #0
	bl FUN_02019064
	mov r0, #0xe7
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_02019620
	add r0, r5, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r1, sp, #0x14
	bl FUN_0200143C
	add r0, sp, #0x14
	ldrh r0, [r0]
	add r0, r5, r0
	ldrb r0, [r0, #0xc]
	sub r0, r0, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r5, #0
	add r1, r4, #0
	bl MOD56_022160E4
	add r0, r5, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r5, r2]
	mov r1, #0x20
	bl ReadMsgDataIntoString
	mov r2, #0x16
	add r0, r5, #0
	lsl r2, r2, #4
	add r0, #0xc8
	ldr r1, [r5, r2]
	sub r2, #8
	ldr r0, [r0]
	ldr r2, [r5, r2]
	bl StringExpandPlaceholders
	mov r3, #0
	str r3, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	ldr r0, _02215964 ; =0x00010200
	add r2, #0x61
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	mov r0, #0xe7
	lsl r0, r0, #2
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	bl FUN_0201BDE0
	mov r0, #0xe7
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019220
	add r0, r5, #0
	mov r1, #0x29
	mov r2, #0
	bl MOD56_02215EA4
	add r0, r5, #0
	mov r2, #0x16
	add r0, #0xcc
	lsl r2, r2, #4
	ldr r0, [r0]
	ldr r2, [r5, r2]
	mov r1, #0x21
	bl ReadMsgDataIntoString
	mov r0, #0x10
	str r0, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	ldr r0, _02215964 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0xe7
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0x61
	ldr r2, [r5, r2]
	add r0, r5, r0
	add r3, r1, #0
	bl FUN_0201BDE0
	mov r0, #0x36
	bl FUN_02023928
	add r6, r0, #0
	ldr r0, [r5]
	add r1, r4, #0
	bl FUN_020283E8
	add r1, r0, #0
	add r0, r6, #0
	bl FUN_0202395C
	add r0, r5, #0
	add r0, #0xc8
	ldr r0, [r0]
	mov r1, #0
	add r2, r6, #0
	bl FUN_0200ABC0
	add r0, r6, #0
	bl FreeToHeap
	add r0, r5, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r5, r2]
	mov r1, #0x4e
	bl ReadMsgDataIntoString
	mov r2, #0x16
	add r0, r5, #0
	lsl r2, r2, #4
	add r0, #0xc8
	ldr r1, [r5, r2]
	sub r2, #8
	ldr r0, [r0]
	ldr r2, [r5, r2]
	bl StringExpandPlaceholders
	mov r1, #0x16
	lsl r1, r1, #4
	mov r0, #0
	ldr r1, [r5, r1]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xce
	sub r3, r1, r0
	mov r0, #0x10
	str r0, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	ldr r0, _02215964 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0xe7
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0x61
	ldr r2, [r5, r2]
	add r0, r5, r0
	bl FUN_0201BDE0
	add r0, r5, #0
	mov r2, #0x16
	add r0, #0xcc
	lsl r2, r2, #4
	ldr r0, [r0]
	ldr r2, [r5, r2]
	mov r1, #0x22
	bl ReadMsgDataIntoString
	mov r0, #0x20
	str r0, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	ldr r0, _02215964 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0xe7
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0x61
	ldr r2, [r5, r2]
	add r0, r5, r0
	add r3, r1, #0
	bl FUN_0201BDE0
	ldr r0, [r5]
	add r1, r4, #0
	mov r2, #1
	bl FUN_0202822C
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xc8
	ldr r0, [r0]
	mov r1, #0
	mov r3, #4
	bl FUN_0200AD38
	add r0, r5, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r5, r2]
	mov r1, #0x23
	bl ReadMsgDataIntoString
	mov r2, #0x16
	add r0, r5, #0
	lsl r2, r2, #4
	add r0, #0xc8
	ldr r1, [r5, r2]
	sub r2, #8
	ldr r0, [r0]
	ldr r2, [r5, r2]
	bl StringExpandPlaceholders
	mov r0, #0x30
	str r0, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	ldr r0, _02215964 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0xe7
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0x61
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r3, #0x1e
	bl FUN_0201BDE0
	ldr r0, [r5]
	add r1, r4, #0
	mov r2, #2
	bl FUN_0202822C
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xc8
	ldr r0, [r0]
	mov r1, #0
	mov r3, #4
	bl FUN_0200AD38
	add r0, r5, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r5, r2]
	mov r1, #0x24
	bl ReadMsgDataIntoString
	mov r2, #0x16
	add r0, r5, #0
	lsl r2, r2, #4
	add r0, #0xc8
	ldr r1, [r5, r2]
	sub r2, #8
	ldr r0, [r0]
	ldr r2, [r5, r2]
	bl StringExpandPlaceholders
	mov r1, #0x16
	lsl r1, r1, #4
	mov r0, #0
	ldr r1, [r5, r1]
	add r2, r0, #0
	bl FUN_02002E14
	add r6, r0, #0
	mov r0, #0x30
	str r0, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	ldr r0, _02215964 ; =0x00010200
	mov r3, #0xce
	str r0, [sp, #8]
	mov r1, #0
	mov r0, #0xe7
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0x61
	ldr r2, [r5, r2]
	add r0, r5, r0
	sub r3, r3, r6
	bl FUN_0201BDE0
	add r0, r5, #0
	mov r2, #0x16
	add r0, #0xcc
	lsl r2, r2, #4
	ldr r0, [r0]
	ldr r2, [r5, r2]
	mov r1, #0x25
	bl ReadMsgDataIntoString
	mov r0, #0x40
	str r0, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	ldr r0, _02215964 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0xe7
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0x61
	ldr r2, [r5, r2]
	add r0, r5, r0
	add r3, r1, #0
	bl FUN_0201BDE0
	ldr r0, [r5]
	add r1, r4, #0
	mov r2, #3
	bl FUN_0202822C
	add r6, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xc8
	ldr r0, [r0]
	mov r1, #0
	add r2, r6, #0
	mov r3, #4
	bl FUN_0200AD38
	cmp r6, #1
	bne _02215810
	add r0, r5, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r5, r2]
	mov r1, #0x26
	bl ReadMsgDataIntoString
	b _02215822
_02215810:
	add r0, r5, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r5, r2]
	mov r1, #0x4f
	bl ReadMsgDataIntoString
_02215822:
	mov r2, #0x16
	add r0, r5, #0
	lsl r2, r2, #4
	add r0, #0xc8
	ldr r1, [r5, r2]
	sub r2, #8
	ldr r0, [r0]
	ldr r2, [r5, r2]
	bl StringExpandPlaceholders
	mov r1, #0x16
	lsl r1, r1, #4
	mov r0, #0
	ldr r1, [r5, r1]
	add r2, r0, #0
	bl FUN_02002E14
	add r6, r0, #0
	mov r0, #0x40
	str r0, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	ldr r0, _02215964 ; =0x00010200
	mov r3, #0xce
	str r0, [sp, #8]
	mov r1, #0
	mov r0, #0xe7
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0x61
	ldr r2, [r5, r2]
	add r0, r5, r0
	sub r3, r3, r6
	bl FUN_0201BDE0
	add r0, r5, #0
	mov r2, #0x16
	add r0, #0xcc
	lsl r2, r2, #4
	ldr r0, [r0]
	ldr r2, [r5, r2]
	mov r1, #0x27
	bl ReadMsgDataIntoString
	mov r0, #0x50
	str r0, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	ldr r0, _02215964 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0xe7
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0x61
	ldr r2, [r5, r2]
	add r0, r5, r0
	add r3, r1, #0
	bl FUN_0201BDE0
	ldr r0, [r5]
	add r1, r4, #0
	mov r2, #6
	bl FUN_0202822C
	add r2, r0, #0
	beq _0221594C
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xc8
	mov r1, #2
	ldr r0, [r0]
	add r3, r1, #0
	bl FUN_0200AD38
	ldr r0, [r5]
	add r1, r4, #0
	mov r2, #4
	bl FUN_0202822C
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xc8
	ldr r0, [r0]
	mov r1, #0
	mov r3, #4
	bl FUN_0200AD38
	ldr r0, [r5]
	add r1, r4, #0
	mov r2, #5
	bl FUN_0202822C
	add r2, r0, #0
	add r0, r5, #0
	add r0, #0xc8
	ldr r0, [r0]
	mov r1, #1
	bl FUN_0200B764
	add r0, r5, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r5, r2]
	mov r1, #0x28
	bl ReadMsgDataIntoString
	mov r2, #0x16
	add r0, r5, #0
	lsl r2, r2, #4
	add r0, #0xc8
	ldr r1, [r5, r2]
	sub r2, #8
	ldr r0, [r0]
	ldr r2, [r5, r2]
	bl StringExpandPlaceholders
	mov r1, #0x16
	lsl r1, r1, #4
	mov r0, #0
	ldr r1, [r5, r1]
	add r2, r0, #0
	bl FUN_02002E14
	add r3, r0, #0
	mov r0, #0x60
	str r0, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	ldr r0, _02215964 ; =0x00010200
	mov r4, #0xce
	str r0, [sp, #8]
	mov r1, #0
	mov r0, #0xe7
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0x61
	ldr r2, [r5, r2]
	add r0, r5, r0
	sub r3, r4, r3
	bl FUN_0201BDE0
_0221594C:
	mov r0, #0xe7
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019220
	mov r0, #0x3b
	mov r1, #0x36
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r7, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02215964: .word 0x00010200
	thumb_func_end MOD56_022154BC

	thumb_func_start MOD56_02215968
MOD56_02215968: ; 0x02215968
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _02215984
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_02215984:
	add r0, r5, #0
	bl MOD56_02213BF4
	cmp r0, #0
	beq _02215996
	mov r0, #0x3b
	mov r1, #0x37
	lsl r0, r0, #4
	str r1, [r5, r0]
_02215996:
	ldr r0, _022159AC ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _022159A8
	mov r0, #0x3b
	mov r1, #0x37
	lsl r0, r0, #4
	str r1, [r5, r0]
_022159A8:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_022159AC: .word gUnknown21C48B8
	thumb_func_end MOD56_02215968

	thumb_func_start MOD56_022159B0
MOD56_022159B0: ; 0x022159B0
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0xe7
	lsl r0, r0, #2
	add r4, r1, #0
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200CCF8
	mov r0, #0xe7
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	mov r1, #1
	bl FUN_02018744
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	mov r1, #3
	bl FUN_02018744
	add r0, r5, #0
	bl MOD56_02216120
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	add r2, r5, #0
	str r3, [sp, #8]
	mov r0, #0x36
	str r0, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	mov r0, #0x5c
	mov r1, #5
	bl FUN_020068C8
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_02019620
	add r0, r5, #0
	mov r2, #0x16
	add r0, #0xcc
	lsl r2, r2, #4
	ldr r0, [r0]
	ldr r2, [r5, r2]
	mov r1, #0x12
	bl ReadMsgDataIntoString
	mov r3, #0
	str r3, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	ldr r0, _02215A88 ; =0x000F0E00
	add r2, #0x61
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	mov r0, #0xd7
	lsl r0, r0, #2
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	bl FUN_0201BDE0
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019220
	add r0, r5, #0
	bl MOD56_02212EFC
	add r0, r5, #0
	bl MOD56_02213A40
	add r0, r5, #0
	mov r1, #0
	bl MOD56_022138A4
	ldr r1, [r5, #4]
	add r0, r5, #0
	ldrb r1, [r1, #0x1b]
	bl MOD56_0221617C
	mov r0, #0x33
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x3b
	mov r1, #0x13
	lsl r0, r0, #4
	str r1, [r5, r0]
	sub r1, #0x14
	str r1, [r5, #8]
	add r0, r4, #0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_02215A88: .word 0x000F0E00
	thumb_func_end MOD56_022159B0

	thumb_func_start MOD56_02215A8C
MOD56_02215A8C: ; 0x02215A8C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02215AC6
	mov r0, #0x36
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, _02215ACC ; =0x02216308
	ldr r2, _02215AD0 ; =0x000001D9
	mov r3, #0xb
	bl FUN_02002198
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0x3b
	mov r1, #0x39
	lsl r0, r0, #4
	str r1, [r5, r0]
_02215AC6:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_02215ACC: .word MOD56_02216308
_02215AD0: .word 0x000001D9
	thumb_func_end MOD56_02215A8C

	thumb_func_start MOD56_02215AD4
MOD56_02215AD4: ; 0x02215AD4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	add r6, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021AC
	add r4, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _02215AFE
	add r0, r6, #0
	pop {r4, r5, r6, pc}
_02215AFE:
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _02215B0A
	add r0, r6, #0
	pop {r4, r5, r6, pc}
_02215B0A:
	cmp r4, #0
	bne _02215B26
	add r0, r5, #0
	mov r1, #0x19
	mov r2, #1
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x3a
	lsl r0, r0, #4
	str r1, [r5, r0]
	mov r1, #1
	add r0, #0x14
	b _02215B32
_02215B26:
	add r0, r5, #0
	bl MOD56_02216120
	mov r0, #0x3b
	mov r1, #0x13
	lsl r0, r0, #4
_02215B32:
	str r1, [r5, r0]
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD56_02215AD4

	thumb_func_start MOD56_02215B38
MOD56_02215B38: ; 0x02215B38
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _02215B54
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_02215B54:
	mov r0, #0xf1
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	cmp r1, #1
	bne _02215B66
	mov r1, #0
	str r1, [r5, r0]
	bl FUN_020331C4
_02215B66:
	bl FUN_02031810
	cmp r0, #0
	bne _02215B8C
	ldr r0, [r5]
	bl FUN_0202858C
	add r0, r5, #0
	mov r1, #0x1a
	mov r2, #1
	bl MOD56_02215EA4
	mov r1, #0x3b
	lsl r0, r1, #4
	str r1, [r5, r0]
	mov r0, #0xf1
	mov r1, #0x1e
	lsl r0, r0, #2
	str r1, [r5, r0]
_02215B8C:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD56_02215B38

	thumb_func_start MOD56_02215B90
MOD56_02215B90: ; 0x02215B90
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _02215BAC
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_02215BAC:
	mov r1, #0xf1
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	sub r0, r0, #1
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	cmp r0, #0
	bne _02215BD0
	add r0, r1, #0
	mov r2, #8
	sub r0, #0x10
	str r2, [r5, r0]
	mov r0, #0x22
	sub r1, #0x14
	str r0, [r5, r1]
	add r0, r5, #0
	bl MOD56_02216120
_02215BD0:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD56_02215B90

	thumb_func_start MOD56_02215BD4
MOD56_02215BD4: ; 0x02215BD4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0
	add r4, r1, #0
	add r1, r0, #0
	bl FUN_020334E8
	mov r0, #0x10
	bl FUN_020315D8
	cmp r0, #0
	bne _02215BF0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_02215BF0:
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02215C24
	mov r0, #0x36
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, _02215C28 ; =0x02216308
	ldr r2, _02215C2C ; =0x000001D9
	mov r3, #0xb
	bl FUN_02002198
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0x3b
	mov r1, #0x3d
	lsl r0, r0, #4
	str r1, [r5, r0]
_02215C24:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02215C28: .word MOD56_02216308
_02215C2C: .word 0x000001D9
	thumb_func_end MOD56_02215BD4

	thumb_func_start MOD56_02215C30
MOD56_02215C30: ; 0x02215C30
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _02215C4C
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_02215C4C:
	bl FUN_02033138
	cmp r0, #0
	bne _02215C64
	bl FUN_02033128
	cmp r0, #0
	bne _02215C64
	bl FUN_0203300C
	cmp r0, #3
	blt _02215C84
_02215C64:
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021EC
	add r0, r5, #0
	mov r1, #0x40
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1c
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02215D18
_02215C84:
	bl FUN_02033250
	cmp r0, #0
	beq _02215CA0
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021EC
	add r0, r5, #0
	bl MOD56_02213030
	b _02215D18
_02215CA0:
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _02215CB8
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_02215CB8:
	cmp r0, #0
	bne _02215CF0
	add r0, r5, #0
	mov r1, #0x48
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0xcf
	lsl r0, r0, #2
	ldr r1, _02215D1C ; =0x000001E2
	add r0, r5, r0
	bl FUN_0200D858
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r5, r1]
	mov r1, #0xfb
	mov r0, #1
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	mov r2, #0x30
	sub r0, #0x3c
	str r2, [r5, r0]
	mov r0, #0x1e
	sub r1, #0x28
	str r0, [r5, r1]
	b _02215D08
_02215CF0:
	add r0, r5, #0
	bl MOD56_02216120
	bl FUN_0203323C
	mov r0, #0xf1
	mov r1, #0x14
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0x40
	sub r0, #0x14
	str r1, [r5, r0]
_02215D08:
	bl FUN_020334DC
	add r1, r0, #0
	str r0, [r5, #4]
	add r1, #0x22
	ldrb r1, [r1]
	add r0, #0x21
	strb r1, [r0]
_02215D18:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02215D1C: .word 0x000001E2
	thumb_func_end MOD56_02215C30

	thumb_func_start MOD56_02215D20
MOD56_02215D20: ; 0x02215D20
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02215D5A
	mov r0, #0x36
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r1, _02215D60 ; =0x02216308
	ldr r2, _02215D64 ; =0x000001D9
	mov r3, #0xb
	bl FUN_02002198
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0x3b
	mov r1, #0x3f
	lsl r0, r0, #4
	str r1, [r5, r0]
_02215D5A:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_02215D60: .word MOD56_02216308
_02215D64: .word 0x000001D9
	thumb_func_end MOD56_02215D20

	thumb_func_start MOD56_02215D68
MOD56_02215D68: ; 0x02215D68
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0203300C
	cmp r0, #3
	blt _02215D96
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021EC
	add r0, r5, #0
	mov r1, #0x40
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0x3b
	mov r1, #0x1c
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02215E6A
_02215D96:
	bl FUN_02033250
	cmp r0, #0
	beq _02215DB2
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021EC
	add r0, r5, #0
	bl MOD56_02213030
	b _02215E6A
_02215DB2:
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x36
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _02215DCA
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_02215DCA:
	cmp r0, #0
	bne _02215E58
	mov r0, #0xf9
	lsl r0, r0, #2
	ldrh r0, [r5, r0]
	bl MOD56_02211F10
	add r6, r0, #0
	cmp r6, #0x11
	beq _02215E58
	mov r0, #0xfa
	lsl r0, r0, #2
	ldrh r0, [r5, r0]
	sub r0, r0, #1
	bl MOD04_021D8480
	cmp r0, #6
	bne _02215E58
	mov r0, #0xfa
	lsl r0, r0, #2
	ldrh r0, [r5, r0]
	sub r0, r0, #1
	bl FUN_02032FDC
	cmp r0, #0
	beq _02215E58
	mov r0, #0
	bl FUN_02031400
	add r0, r5, #0
	bl MOD56_022161DC
	add r0, r5, #0
	add r1, r6, #0
	bl MOD56_0221617C
	mov r1, #0xfa
	lsl r1, r1, #2
	ldrh r1, [r5, r1]
	add r0, r5, #0
	sub r1, r1, #1
	bl MOD56_022160E4
	add r0, r5, #0
	mov r1, #0xd
	mov r2, #0
	bl MOD56_02215EA4
	mov r0, #0xcf
	lsl r0, r0, #2
	ldr r1, _02215E70 ; =0x000001E2
	add r0, r5, r0
	bl FUN_0200D858
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r5, r1]
	cmp r6, #1
	beq _02215E4C
	mov r0, #0x3b
	mov r1, #0x2c
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_02215E4C:
	mov r0, #0x3b
	mov r1, #0x15
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_02215E58:
	add r0, r5, #0
	bl MOD56_02216120
	mov r0, #0x3b
	mov r1, #0x13
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_02215E6A:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	nop
_02215E70: .word 0x000001E2
	thumb_func_end MOD56_02215D68

	thumb_func_start MOD56_02215E74
MOD56_02215E74: ; 0x02215E74
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	bl FUN_02031810
	cmp r0, #0
	bne _02215E9C
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x36
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r4, #2
_02215E9C:
	add r0, r4, #0
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD56_02215E74

	thumb_func_start MOD56_02215EA4
MOD56_02215EA4: ; 0x02215EA4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r4, r1, #0
	add r6, r2, #0
	bl LoadPlayerDataAddress
	bl FUN_02024FF4
	add r7, r0, #0
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019048
	cmp r0, #0
	beq _02215EE0
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
_02215EE0:
	mov r0, #0xcf
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019048
	cmp r0, #0
	beq _02215F04
	mov r0, #0xcf
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0xcf
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
_02215F04:
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #8
	beq _02215F30
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _02215F30
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD7C
	mov r0, #0x5e
	mov r1, #8
	lsl r0, r0, #2
	str r1, [r5, r0]
_02215F30:
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, _02215FEC ; =0x0000012D
	mov r1, #0xcf
	str r0, [sp, #0x10]
	add r0, r5, #0
	add r0, #0xc0
	lsl r1, r1, #2
	mov r2, #2
	ldr r0, [r0]
	add r1, r5, r1
	add r3, r2, #0
	bl FUN_02019064
	cmp r6, #0
	beq _02215F70
	add r0, r5, #0
	mov r2, #0x56
	add r0, #0xd0
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r5, r2]
	add r1, r4, #0
	bl ReadMsgDataIntoString
	b _02215F82
_02215F70:
	add r0, r5, #0
	mov r2, #0x56
	add r0, #0xcc
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r5, r2]
	add r1, r4, #0
	bl ReadMsgDataIntoString
_02215F82:
	mov r2, #0x57
	add r0, r5, #0
	lsl r2, r2, #2
	add r0, #0xc8
	ldr r1, [r5, r2]
	sub r2, r2, #4
	ldr r0, [r0]
	ldr r2, [r5, r2]
	bl StringExpandPlaceholders
	mov r0, #0xcf
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0xcf
	lsl r0, r0, #2
	ldr r2, _02215FF0 ; =0x000001E2
	add r0, r5, r0
	mov r1, #1
	mov r3, #0xa
	bl FUN_0200D0BC
	mov r0, #1
	bl FUN_02002B60
	mov r0, #0
	bl FUN_02002B7C
	mov r3, #0
	str r3, [sp]
	str r7, [sp, #4]
	mov r2, #0x57
	mov r0, #0xcf
	lsl r0, r0, #2
	str r3, [sp, #8]
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	bl FUN_0201BD84
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0xcf
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019220
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02215FEC: .word 0x0000012D
_02215FF0: .word 0x000001E2
	thumb_func_end MOD56_02215EA4

	thumb_func_start MOD56_02215FF4
MOD56_02215FF4: ; 0x02215FF4
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r4, r1, #0
	bl MOD56_02216274
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019048
	cmp r0, #0
	beq _02216024
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
_02216024:
	mov r0, #0xcf
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019048
	cmp r0, #0
	beq _02216048
	mov r0, #0xcf
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0xcf
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019178
_02216048:
	mov r3, #4
	str r3, [sp]
	mov r0, #0x17
	str r0, [sp, #4]
	mov r0, #0x10
	str r0, [sp, #8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	mov r0, #0x69
	str r0, [sp, #0x10]
	add r0, r5, #0
	add r0, #0xc0
	mov r1, #0xdb
	lsl r1, r1, #2
	ldr r0, [r0]
	add r1, r5, r1
	mov r2, #2
	bl FUN_02019064
	add r0, r5, #0
	mov r2, #0x56
	add r0, #0xd0
	lsl r2, r2, #2
	ldr r0, [r0]
	ldr r2, [r5, r2]
	add r1, r4, #0
	bl ReadMsgDataIntoString
	mov r2, #0x57
	add r0, r5, #0
	lsl r2, r2, #2
	add r0, #0xc8
	ldr r1, [r5, r2]
	sub r2, r2, #4
	ldr r0, [r0]
	ldr r2, [r5, r2]
	bl StringExpandPlaceholders
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0xdb
	lsl r0, r0, #2
	ldr r2, _022160E0 ; =0x000001D9
	add r0, r5, r0
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	mov r3, #0
	mov r0, #0xdb
	lsl r0, r0, #2
	str r3, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	str r3, [sp, #8]
	add r2, #0x5d
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	bl FUN_0201BD84
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_02019220
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_022160E0: .word 0x000001D9
	thumb_func_end MOD56_02215FF4

	thumb_func_start MOD56_022160E4
MOD56_022160E4: ; 0x022160E4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0
	add r6, r1, #0
	mvn r0, r0
	cmp r6, r0
	beq _0221611C
	mov r0, #0x36
	bl FUN_02023928
	add r4, r0, #0
	ldr r0, [r5]
	add r1, r6, #0
	bl FUN_020283A4
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0202395C
	add r5, #0xc8
	ldr r0, [r5]
	mov r1, #0
	add r2, r4, #0
	bl FUN_0200ABC0
	add r0, r4, #0
	bl FreeToHeap
_0221611C:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD56_022160E4

	thumb_func_start MOD56_02216120
MOD56_02216120: ; 0x02216120
	push {r4, lr}
	add r4, r0, #0
	bl MOD56_02216274
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #8
	beq _02216154
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _02216154
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD7C
	mov r0, #0x5e
	mov r1, #8
	lsl r0, r0, #2
	str r1, [r4, r0]
_02216154:
	mov r0, #0xcf
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019048
	cmp r0, #0
	beq _02216178
	mov r0, #0xcf
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0xcf
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019178
_02216178:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD56_02216120

	thumb_func_start MOD56_0221617C
MOD56_0221617C: ; 0x0221617C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldr r1, [r5, #4]
	ldrb r0, [r1, #0x1b]
	cmp r0, r4
	beq _022161C8
	add r0, r4, #0
	strb r4, [r1, #0x1b]
	bl MOD56_02211EA4
	cmp r0, #0
	bne _022161C8
	cmp r4, #8
	beq _022161C8
	cmp r4, #1
	bne _022161A8
	mov r0, #0
	mov r1, #0x1e
	bl FUN_020053CC
	b _022161C8
_022161A8:
	cmp r4, #0x10
	bne _022161C8
	ldr r0, _022161D8 ; =0x00000497
	mov r1, #0x5a
	bl FUN_0200488C
	mov r0, #7
	mov r1, #0x12
	mov r2, #0
	bl FUN_02004828
	mov r0, #0x7f
	mov r1, #0x1e
	mov r2, #1
	bl FUN_0200538C
_022161C8:
	ldr r0, [r5, #4]
	mov r1, #0x24
	bl MOD04_021D8478
	add r0, r5, #0
	bl MOD56_0221341C
	pop {r3, r4, r5, pc}
	.align 2, 0
_022161D8: .word 0x00000497
	thumb_func_end MOD56_0221617C

	thumb_func_start MOD56_022161DC
MOD56_022161DC: ; 0x022161DC
	push {r4, lr}
	add r4, r0, #0
	ldr r2, [r4, #4]
	add r0, r2, #0
	add r0, #0x21
	ldrb r1, [r0]
	mov r0, #1
	add r2, #0x21
	sub r0, r0, r1
	strb r0, [r2]
	ldr r0, [r4, #4]
	add r0, #0x21
	ldrb r0, [r0]
	bl MOD04_021D8678
	ldr r0, [r4, #4]
	mov r1, #0x24
	bl MOD04_021D8478
	ldr r0, [r4, #4]
	add r0, #0x21
	ldrb r0, [r0]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD56_022161DC

	thumb_func_start MOD56_0221620C
MOD56_0221620C: ; 0x0221620C
	push {r4, lr}
	add r4, r0, #0
	ldr r2, [r4, #4]
	add r0, r2, #0
	add r0, #0x22
	ldrb r1, [r0]
	mov r0, #1
	add r2, #0x22
	sub r0, r0, r1
	strb r0, [r2]
	ldr r1, [r4, #4]
	add r0, r1, #0
	add r0, #0x22
	ldrb r0, [r0]
	add r1, #0x21
	strb r0, [r1]
	ldr r0, [r4, #4]
	add r0, #0x21
	ldrb r0, [r0]
	bl MOD04_021D8678
	ldr r0, [r4, #4]
	mov r1, #0x24
	bl MOD04_021D8478
	ldr r0, [r4, #4]
	add r0, #0x22
	ldrb r0, [r0]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD56_0221620C

	thumb_func_start MOD56_02216248
MOD56_02216248: ; 0x02216248
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	add r0, r1, #0
	add r0, #0x22
	ldrb r0, [r0]
	add r1, #0x21
	strb r0, [r1]
	ldr r0, [r4, #4]
	add r0, #0x21
	ldrb r0, [r0]
	bl MOD04_021D8678
	ldr r0, [r4, #4]
	mov r1, #0x24
	bl MOD04_021D8478
	ldr r0, [r4, #4]
	add r0, #0x22
	ldrb r0, [r0]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD56_02216248

	thumb_func_start MOD56_02216274
MOD56_02216274: ; 0x02216274
	push {r4, lr}
	add r4, r0, #0
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _022162DC
	bl FUN_0200DC24
	mov r0, #6
	mov r1, #0
	lsl r0, r0, #6
	str r1, [r4, r0]
	sub r0, #8
	ldr r0, [r4, r0]
	cmp r0, #8
	beq _022162B8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _022162B8
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD7C
	mov r0, #0x5e
	mov r1, #8
	lsl r0, r0, #2
	str r1, [r4, r0]
_022162B8:
	mov r0, #0xcf
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019048
	cmp r0, #0
	beq _022162DC
	mov r0, #0xcf
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0xcf
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019178
_022162DC:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD56_02216274

	.rodata
	.global MOD56_022162E0
MOD56_022162E0: ; 0x022162E0
	.byte 0x4A, 0x00, 0x4B, 0x00, 0x4A, 0x08, 0x4B, 0x08, 0x25, 0x00, 0x26, 0x00, 0x2A, 0x00, 0x25, 0x0C
	.byte 0x17, 0x00, 0x18, 0x00, 0x18, 0x0C, 0x20, 0x00

	.global MOD56_022162F8
MOD56_022162F8: ; 0x022162F8
	.byte 0x02, 0x19, 0x0D, 0x06, 0x04, 0x0D, 0x51, 0x00, 0x48, 0x00, 0x49, 0x00, 0x48, 0x08, 0x49, 0x08

	.global MOD56_02216308
MOD56_02216308: ; 0x02216308
	.byte 0x02, 0x19, 0x0D, 0x06, 0x04, 0x0D, 0x15, 0x01

	.global MOD56_02216310
MOD56_02216310: ; 0x02216310
	.byte 0x01, 0x19, 0x13, 0x06, 0x04, 0x0D, 0x51, 0x00, 0x2F, 0x00, 0x2F, 0x04, 0x2F, 0x08, 0x2F, 0x0C

	.global MOD56_02216320
MOD56_02216320: ; 0x02216320
	.byte 0x44, 0x00, 0x45, 0x00, 0x46, 0x00, 0x47, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00

	.global MOD56_02216330
MOD56_02216330: ; 0x02216330
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD56_02216340
MOD56_02216340: ; 0x02216340
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00

	.global MOD56_02216350
MOD56_02216350: ; 0x02216350
	.byte 0x1D, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x1F, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF

	.global MOD56_02216368
MOD56_02216368: ; 0x02216368
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x18, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD56_02216384
MOD56_02216384: ; 0x02216384
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1A, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD56_022163A0
MOD56_022163A0: ; 0x022163A0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1C, 0x02, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD56_022163BC
MOD56_022163BC: ; 0x022163BC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD56_022163D8
MOD56_022163D8: ; 0x022163D8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD56_022163F4
MOD56_022163F4: ; 0x022163F4
	.word 0x00000000, MOD56_02213924, MOD56_02213624, 0x00000000
	.byte 0x22, 0x00, 0x05, 0x00, 0x00, 0x08, 0x00, 0x10, 0x20, 0x00, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00

	.global MOD56_02216414
MOD56_02216414: ; 0x02216414
	.word 0x00000000, MOD56_02213924, 0x00000000, 0x00000000
	.byte 0x04, 0x00, 0x04, 0x00, 0x00, 0x08, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD56_02216434
MOD56_02216434: ; 0x02216434
	.word 0x00000000, MOD56_02213924, 0x00000000, 0x00000000
	.byte 0x03, 0x00, 0x03, 0x00, 0x00, 0x08, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD56_02216454
MOD56_02216454: ; 0x02216454
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.data
	.global MOD56_02216480
MOD56_02216480: ; 0x02216480
	.byte 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x18, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF

	.global MOD56_022164A0
MOD56_022164A0: ; 0x022164A0
	.byte 0x3A, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00
	.byte 0x3C, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF

	.global MOD56_022164C0
MOD56_022164C0: ; 0x022164C0
	.byte 0x3D, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x3F, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF

	.global MOD56_022164E0
MOD56_022164E0: ; 0x022164E0
	.word MOD56_02212A1C, MOD56_02212B3C, MOD56_02212B84, MOD56_02212BE8
	.word MOD56_02212C50, MOD56_02212CCC, MOD56_02212D54, MOD56_02213048
	.word MOD56_0221308C, MOD56_02213098, MOD56_022130A4, MOD56_022130F4
	.word MOD56_0221313C, MOD56_02213194, MOD56_02212DD8, MOD56_0221327C
	.word MOD56_02213368, MOD56_02213388, MOD56_02213A94, MOD56_02213D98
	.word MOD56_02213F90, MOD56_02213FCC, MOD56_022140A4, MOD56_022140DC
	.word MOD56_02214120, MOD56_02214238, MOD56_0221428C, MOD56_0221432C
	.word MOD56_022143B4, MOD56_02214404, MOD56_02214464, MOD56_02214468
	.word MOD56_0221446C, MOD56_0221547C, MOD56_02215E74, MOD56_022144DC
	.word MOD56_022145D4, MOD56_022146CC, MOD56_02214920, MOD56_02214504
	.word MOD56_02214520, MOD56_02214568, MOD56_022149D8, MOD56_02214BFC
	.word MOD56_02214E28, MOD56_02214FD8, MOD56_02215020, MOD56_022150A4
	.word MOD56_02215200, MOD56_022152A8, MOD56_022152E0, MOD56_02215350
	.word MOD56_02215388, MOD56_022154BC, MOD56_02215968, MOD56_022159B0
	.word MOD56_02215A8C, MOD56_02215AD4, MOD56_02215B38, MOD56_02215B90
	.word MOD56_02215BD4, MOD56_02215C30, MOD56_02215D20, MOD56_02215D68
	.word MOD56_022132FC, MOD56_02214F0C, MOD56_02214F54, 0x00000000
	.word 0x00000000, 0x00000000, 0x00000000, 0x00000000

	.bss
