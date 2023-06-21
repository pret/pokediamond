	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F7374
UNK_020F7374: ; 0x020F7374
	.byte 0x58, 0x44, 0x30, 0x1C, 0x20, 0x18, 0x10, 0x08, 0x62, 0x4E, 0x3A, 0x26

	.text

	thumb_func_start sub_0205DD18
sub_0205DD18: ; 0x0205DD18
	push {r4, lr}
	mov r1, #0xd4
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r0, #0x1
	lsl r0, r0, #0x10
	add r3, r4, #0x0
	lsr r1, r0, #0x1
	add r2, r0, #0x0
	add r3, #0xbc
	bl sub_0201B7DC
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0205DD38
sub_0205DD38: ; 0x0205DD38
	ldr r3, _0205DD3C ; =FreeToHeap
	bx r3
	.balign 4
_0205DD3C: .word FreeToHeap

	thumb_func_start sub_0205DD40
sub_0205DD40: ; 0x0205DD40
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	str r1, [r4, #0x4]
	str r1, [r4, #0x0]
	str r1, [r4, #0x8]
	str r1, [r4, #0xc]
	str r1, [r4, #0x10]
	add r0, #0xd0
	strb r1, [r0, #0x0]
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	add r0, #0x1c
	mov r2, #0xa0
	str r1, [r4, #0x18]
	bl MI_CpuFill8
	mov r3, #0x0
	add r2, r3, #0x0
	mov r0, #0x28
_0205DD6A:
	add r1, r3, #0x0
	mul r1, r0
	add r1, r4, r1
	str r2, [r1, #0x28]
	add r1, r3, #0x1
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r3, #0x4
	blo _0205DD6A
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0205DD80
sub_0205DD80: ; 0x0205DD80
	push {r4-r7, lr}
	sub sp, #0x2c
	str r1, [sp, #0x10]
	ldr r1, _0205DECC ; =UNK_020F7374
	str r2, [sp, #0x14]
	ldrb r2, [r1, #0x4]
	str r0, [sp, #0xc]
	add r0, sp, #0x28
	strb r2, [r0, #0x0]
	ldrb r2, [r1, #0x5]
	str r3, [sp, #0x18]
	strb r2, [r0, #0x1]
	ldrb r2, [r1, #0x6]
	ldrb r1, [r1, #0x7]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldr r0, [sp, #0xc]
	ldr r0, [r0, #0x38]
	bl sub_02055360
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	mov r5, #0x0
	str r0, [sp, #0x24]
	add r0, #0x1c
	str r5, [sp, #0x20]
	str r0, [sp, #0x24]
_0205DDB6:
	add r0, sp, #0x28
	ldrb r4, [r0, r5]
	cmp r4, #0x0
	bne _0205DDC2
	bl GF_AssertFail
_0205DDC2:
	cmp r4, #0x1
	bhi _0205DDCA
	mov r6, #0x0
	b _0205DDF2
_0205DDCA:
	bl LCRandom
	add r6, r0, #0x0
	ldr r0, _0205DED0 ; =0x0000FFFF
	add r1, r4, #0x0
	bl _s32_div_f
	add r1, r0, #0x0
	add r1, r1, #0x1
	lsl r1, r1, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r6, r4
	blo _0205DDF2
	bl GF_AssertFail
_0205DDF2:
	lsl r1, r5, #0x1
	mov r0, #0x9
	sub r0, r0, r1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	lsl r0, r6, #0x18
	lsr r6, r0, #0x18
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl _s32_div_f
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bne _0205DE1C
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl _s32_div_f
	add r1, r5, r1
	add r0, r5, #0x0
	b _0205DE5C
_0205DE1C:
	cmp r0, #0x1
	bne _0205DE30
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl _s32_div_f
	add r0, r5, r4
	add r1, r5, r1
	sub r0, r0, #0x1
	b _0205DE5C
_0205DE30:
	lsl r7, r4, #0x1
	cmp r6, r7
	bge _0205DE3A
	bl GF_AssertFail
_0205DE3A:
	sub r0, r6, r7
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	lsr r3, r1, #0x1f
	lsl r2, r1, #0x1f
	lsr r0, r1, #0x1
	add r0, r5, r0
	sub r2, r2, r3
	mov r1, #0x1f
	ror r2, r1
	add r0, r0, #0x1
	add r1, r3, r2
	bne _0205DE58
	add r1, r5, #0x0
	b _0205DE5C
_0205DE58:
	add r1, r5, r4
	sub r1, r1, #0x1
_0205DE5C:
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r0, r0, #0x18
	str r1, [sp, #0x0]
	lsr r0, r0, #0x18
	str r0, [sp, #0x4]
	mov r0, #0x28
	add r1, r5, #0x0
	mul r1, r0
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x10]
	add r0, r0, r1
	str r0, [sp, #0x8]
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0xc]
	ldr r1, [r1, #0x4]
	ldr r3, [sp, #0x14]
	bl sub_0205E12C
	cmp r0, #0x0
	beq _0205DE90
	ldr r0, [sp, #0x20]
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x20]
_0205DE90:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x4
	blo _0205DDB6
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	bne _0205DEBE
	ldr r0, [sp, #0x18]
	bl sub_0205DD40
	ldr r0, [sp, #0xc]
	add r1, r0, #0x0
	ldr r1, [r1, #0x1c]
	ldr r1, [r1, #0x0]
	bl FieldSystem_GetOverriddenMusicId
	add r1, r0, #0x0
	ldr r0, [sp, #0xc]
	mov r2, #0x1
	bl FieldSystem_PlayOrFadeToNewMusicId
	b _0205DEC4
_0205DEBE:
	ldr r0, [sp, #0x18]
	mov r1, #0x1
	str r1, [r0, #0x10]
_0205DEC4:
	ldr r0, [sp, #0x18]
	ldr r0, [r0, #0x10]
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4
_0205DECC: .word UNK_020F7374
_0205DED0: .word 0x0000FFFF

	thumb_func_start sub_0205DED4
sub_0205DED4: ; 0x0205DED4
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	add r6, r2, #0x0
	mov r4, #0x0
_0205DEE0:
	mov r0, #0x28
	mul r0, r4
	add r5, r6, r0
	ldr r0, [r5, #0x28]
	cmp r0, #0x0
	beq _0205DF36
	ldr r1, [sp, #0x4]
	add r0, r4, #0x0
	bl sub_0205E2A0
	str r0, [r5, #0x2c]
	cmp r0, #0x0
	bne _0205DF24
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #0x4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	cmp r7, #0x64
	blo _0205DF12
	bl GF_AssertFail
_0205DF12:
	cmp r7, #0x32
	bhs _0205DF1A
	mov r0, #0x0
	b _0205DF1C
_0205DF1A:
	mov r0, #0x1
_0205DF1C:
	str r0, [r5, #0x24]
	mov r0, #0x0
	str r0, [r5, #0x30]
	b _0205DF36
_0205DF24:
	ldr r0, [r6, #0x0]
	str r0, [r5, #0x24]
	ldr r0, [sp, #0x0]
	add r0, #0x90
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	bl sub_0205E40C
	str r0, [r5, #0x30]
_0205DF36:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x4
	blo _0205DEE0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start sub_0205DF44
sub_0205DF44: ; 0x0205DF44
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	mov r6, #0x0
_0205DF4C:
	mov r0, #0x28
	mul r0, r6
	add r4, r7, r0
	ldr r0, [r4, #0x28]
	cmp r0, #0x0
	beq _0205DF8C
	ldr r0, [r4, #0x30]
	ldr r1, [r4, #0x1c]
	ldr r2, [r4, #0x20]
	cmp r0, #0x0
	beq _0205DF6E
	add r0, r5, #0x0
	mov r3, #0x2
	bl ov06_0224B818
	str r0, [r4, #0x34]
	b _0205DF90
_0205DF6E:
	ldr r0, [r4, #0x24]
	cmp r0, #0x0
	bne _0205DF80
	add r0, r5, #0x0
	mov r3, #0x0
	bl ov06_0224B818
	str r0, [r4, #0x34]
	b _0205DF90
_0205DF80:
	add r0, r5, #0x0
	mov r3, #0x1
	bl ov06_0224B818
	str r0, [r4, #0x34]
	b _0205DF90
_0205DF8C:
	mov r0, #0x0
	str r0, [r4, #0x34]
_0205DF90:
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #0x4
	blo _0205DF4C
	pop {r3-r7, pc}

	thumb_func_start sub_0205DF9C
sub_0205DF9C: ; 0x0205DF9C
	push {r3-r7, lr}
	mov r4, #0x0
	add r7, r0, #0x0
	add r6, r4, #0x0
_0205DFA4:
	mov r0, #0x28
	mul r0, r6
	add r5, r7, r0
	ldr r0, [r5, #0x34]
	cmp r0, #0x0
	beq _0205DFCA
	bl ov06_0224B86C
	cmp r0, #0x0
	beq _0205DFD0
	ldr r0, [r5, #0x34]
	bl sub_02064520
	mov r0, #0x0
	str r0, [r5, #0x34]
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	b _0205DFD0
_0205DFCA:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_0205DFD0:
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #0x4
	blo _0205DFA4
	cmp r4, #0x4
	blo _0205DFE2
	mov r0, #0x1
	pop {r3-r7, pc}
_0205DFE2:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_0205DFE8
sub_0205DFE8: ; 0x0205DFE8
	push {r3-r7, lr}
	sub sp, #0x8
	ldr r7, [sp, #0x24]
	add r6, r0, #0x0
	mov r12, r1
	ldr r0, [sp, #0x28]
	mov r1, #0x0
	add r4, r3, #0x0
	str r1, [r7, #0x0]
	str r2, [sp, #0x0]
	str r1, [r0, #0x0]
	str r0, [sp, #0x28]
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r2, r12
	add r3, sp, #0x4
	ldr r5, [sp, #0x20]
	bl sub_0205E1B8
	cmp r0, #0x0
	bne _0205E018
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_0205E018:
	mov r0, #0x1
	str r0, [r4, #0x18]
	add r0, sp, #0x4
	ldrb r1, [r0, #0x0]
	mov r0, #0x28
	mul r0, r1
	add r0, r4, r0
	ldr r1, [r0, #0x2c]
	ldr r6, [r0, #0x24]
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	bne _0205E062
	cmp r1, #0x0
	beq _0205E05E
	add r0, r4, #0x4
	bl sub_0205E4D8
	str r6, [r5, #0x0]
	mov r0, #0x1
	str r0, [r7, #0x0]
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	bl sub_0205E1F0
	add r0, sp, #0x4
	ldrb r1, [r0, #0x0]
	mov r0, #0x28
	mul r0, r1
	add r0, r4, r0
	ldr r1, [r0, #0x30]
	ldr r0, [sp, #0x28]
	add sp, #0x8
	str r1, [r0, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
_0205E05E:
	str r6, [r5, #0x0]
	b _0205E074
_0205E062:
	str r6, [r5, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x14]
	ldr r0, [sp, #0x0]
	bl sub_0205E258
	add r1, r4, #0x0
	add r1, #0xd0
	strb r0, [r1, #0x0]
_0205E074:
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x0]
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_0205E080
sub_0205E080: ; 0x0205E080
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x0
	bne _0205E090
	bl GF_AssertFail
_0205E090:
	str r4, [r5, #0x8]
	str r6, [r5, #0xc]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_0205E098
sub_0205E098: ; 0x0205E098
	ldr r3, [r0, #0x8]
	str r3, [r1, #0x0]
	ldr r0, [r0, #0xc]
	str r0, [r2, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_0205E0A4
sub_0205E0A4: ; 0x0205E0A4
	ldr r0, [r0, #0x18]
	bx lr

	thumb_func_start sub_0205E0A8
sub_0205E0A8: ; 0x0205E0A8
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	beq _0205E126
	ldr r0, [r7, #0x10]
	cmp r0, #0x0
	bne _0205E126
	mov r6, #0x0
	add r5, r6, #0x0
_0205E0C0:
	add r0, r7, #0x0
	add r0, #0x90
	ldr r1, [r0, #0x0]
	add r0, r1, #0x0
	add r0, #0x1c
	add r4, r0, r5
	add r0, r4, #0x0
	add r0, #0x1c
	add r1, #0xbc
	bl sub_0201B76C
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	beq _0205E0E4
	cmp r0, #0x0
	bne _0205E0E4
	mov r0, #0x0
	str r0, [r4, #0xc]
_0205E0E4:
	add r6, r6, #0x1
	add r5, #0x28
	cmp r6, #0x4
	blt _0205E0C0
	add r0, r7, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	mov r2, #0x0
	add r3, r0, #0x0
	add r4, r2, #0x0
	add r3, #0x1c
_0205E0FA:
	ldr r1, [r3, #0xc]
	cmp r1, #0x0
	bne _0205E102
	add r2, r2, #0x1
_0205E102:
	add r4, r4, #0x1
	add r3, #0x28
	cmp r4, #0x4
	blt _0205E0FA
	cmp r2, #0x4
	bne _0205E126
	bl sub_0205DD40
	ldr r1, [r7, #0x1c]
	add r0, r7, #0x0
	ldr r1, [r1, #0x0]
	bl FieldSystem_GetOverriddenMusicId
	add r1, r0, #0x0
	add r0, r7, #0x0
	mov r2, #0x1
	bl FieldSystem_PlayOrFadeToNewMusicId
_0205E126:
	pop {r3-r7, pc}

	thumb_func_start sub_0205E128
sub_0205E128: ; 0x0205E128
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start sub_0205E12C
sub_0205E12C: ; 0x0205E12C
	push {r4-r7, lr}
	sub sp, #0xc
	str r1, [sp, #0x4]
	add r1, sp, #0x10
	sub r4, r2, #0x4
	ldrb r2, [r1, #0x10]
	ldrb r1, [r1, #0x14]
	ldr r5, [sp, #0x28]
	add r4, r4, r2
	sub r2, r3, #0x4
	add r6, r2, r1
	str r4, [r5, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	add r7, r0, #0x0
	str r6, [r5, #0x4]
	bl sub_0204A6E0
	bl sub_0205478C
	cmp r0, #0x0
	beq _0205E1AE
	lsl r0, r4, #0x10
	str r0, [r5, #0x1c]
	lsl r0, r6, #0x10
	str r0, [r5, #0x24]
	add r0, sp, #0x8
	str r0, [sp, #0x0]
	ldr r2, [r5, #0x1c]
	ldr r3, [r5, #0x24]
	add r0, r7, #0x0
	mov r1, #0x0
	bl sub_0204A708
	ldr r1, [sp, #0x4]
	str r0, [r5, #0x20]
	cmp r1, r0
	beq _0205E180
	mov r0, #0x0
	add sp, #0xc
	str r0, [r5, #0xc]
	pop {r4-r7, pc}
_0205E180:
	asr r1, r4, #0x4
	asr r2, r6, #0x4
	lsr r1, r1, #0x1b
	lsr r2, r2, #0x1b
	add r1, r4, r1
	add r2, r6, r2
	ldr r0, [r7, #0x28]
	asr r1, r1, #0x5
	asr r2, r2, #0x5
	bl MapMatrix_GetMapHeader
	ldr r1, [r7, #0x1c]
	ldr r1, [r1, #0x0]
	cmp r1, r0
	beq _0205E1A6
	mov r0, #0x0
	add sp, #0xc
	str r0, [r5, #0xc]
	pop {r4-r7, pc}
_0205E1A6:
	mov r0, #0x1
	add sp, #0xc
	str r0, [r5, #0xc]
	pop {r4-r7, pc}
_0205E1AE:
	mov r0, #0x0
	str r0, [r5, #0xc]
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start sub_0205E1B8
sub_0205E1B8: ; 0x0205E1B8
	push {r4-r7}
	mov r5, #0x0
	mov r6, #0x28
_0205E1BE:
	add r4, r5, #0x0
	mul r4, r6
	add r4, r0, r4
	ldr r7, [r4, #0x28]
	cmp r7, #0x0
	beq _0205E1DE
	ldr r7, [r4, #0x1c]
	cmp r1, r7
	bne _0205E1DE
	ldr r4, [r4, #0x20]
	cmp r2, r4
	bne _0205E1DE
	strb r5, [r3, #0x0]
	mov r0, #0x1
	pop {r4-r7}
	bx lr
_0205E1DE:
	add r4, r5, #0x1
	lsl r4, r4, #0x18
	lsr r5, r4, #0x18
	cmp r5, #0x4
	blo _0205E1BE
	mov r0, #0x0
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start sub_0205E1F0
sub_0205E1F0: ; 0x0205E1F0
	push {r4-r6, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	bl Save_Roamers_Get
	bl sub_0202A9AC
	add r3, r5, #0x0
	add r3, #0xd0
	ldrb r3, [r3, #0x0]
	add r4, r0, #0x0
	add r1, r4, #0x2
	lsl r6, r3, #0x2
	ldrh r3, [r1, r6]
	ldr r2, [r5, #0x4]
	cmp r3, r2
	bge _0205E256
	strh r2, [r1, r6]
	add r1, r5, #0x0
	add r1, #0xd0
	ldrb r1, [r1, #0x0]
	ldr r2, [r5, #0x8]
	lsl r1, r1, #0x2
	strh r2, [r4, r1]
	bl ov06_02245844
	add r0, r5, #0x0
	add r0, #0xd0
	ldrb r0, [r0, #0x0]
	ldr r2, [r5, #0x4]
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldrh r0, [r0, #0x2]
	cmp r0, r2
	bgt _0205E256
	mov r1, #0x0
	mov r3, #0x2
_0205E23A:
	sub r0, r3, r1
	lsl r6, r0, #0x2
	add r6, r4, r6
	ldrh r6, [r6, #0x2]
	cmp r2, r6
	bne _0205E24C
	add r5, #0xd0
	strb r0, [r5, #0x0]
	pop {r4-r6, pc}
_0205E24C:
	add r1, r1, #0x1
	cmp r1, #0x3
	blt _0205E23A
	bl GF_AssertFail
_0205E256:
	pop {r4-r6, pc}

	thumb_func_start sub_0205E258
sub_0205E258: ; 0x0205E258
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl Save_Roamers_Get
	bl sub_0202A9AC
	mov r2, #0x0
_0205E266:
	lsl r1, r2, #0x2
	ldrh r1, [r0, r1]
	cmp r1, #0x0
	bne _0205E272
	add r0, r2, #0x0
	pop {r3, pc}
_0205E272:
	add r1, r2, #0x1
	lsl r1, r1, #0x18
	lsr r2, r1, #0x18
	cmp r2, #0x3
	blo _0205E266
	ldrh r2, [r0, #0x2]
	ldrh r1, [r0, #0x6]
	cmp r2, r1
	blo _0205E288
	mov r1, #0x1
	b _0205E28A
_0205E288:
	mov r1, #0x0
_0205E28A:
	lsl r1, r1, #0x18
	lsr r2, r1, #0x18
	lsl r1, r2, #0x2
	add r1, r0, r1
	ldrh r1, [r1, #0x2]
	ldrh r0, [r0, #0xa]
	cmp r1, r0
	blo _0205E29C
	mov r2, #0x2
_0205E29C:
	add r0, r2, #0x0
	pop {r3, pc}

	thumb_func_start sub_0205E2A0
sub_0205E2A0: ; 0x0205E2A0
	push {r3-r7, lr}
	sub sp, #0x8
	ldr r3, _0205E308 ; =UNK_020F7374
	add r5, r0, #0x0
	ldrb r4, [r3, #0x0]
	add r2, sp, #0x0
	add r0, sp, #0x4
	strb r4, [r2, #0x4]
	ldrb r4, [r3, #0x1]
	add r7, sp, #0x0
	cmp r1, #0x1
	strb r4, [r2, #0x5]
	ldrb r4, [r3, #0x2]
	strb r4, [r2, #0x6]
	ldrb r4, [r3, #0x3]
	strb r4, [r2, #0x7]
	ldrb r4, [r3, #0x8]
	strb r4, [r2, #0x0]
	ldrb r4, [r3, #0x9]
	strb r4, [r2, #0x1]
	ldrb r4, [r3, #0xa]
	strb r4, [r2, #0x2]
	ldrb r3, [r3, #0xb]
	strb r3, [r2, #0x3]
	bne _0205E2D6
	add r6, r0, #0x0
	b _0205E2DC
_0205E2D6:
	cmp r1, #0x4
	bne _0205E2DC
	add r6, r7, #0x0
_0205E2DC:
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #0x4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x64
	blo _0205E2F4
	bl GF_AssertFail
_0205E2F4:
	ldrb r0, [r6, r5]
	cmp r4, r0
	bge _0205E300
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_0205E300:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0205E308: .word UNK_020F7374

	thumb_func_start sub_0205E30C
sub_0205E30C: ; 0x0205E30C
	push {r3-r7, lr}
	add r7, r0, #0x0
	bl TaskManager_GetFieldSystem
	add r4, r0, #0x0
	add r0, r7, #0x0
	bl sub_0204652C
	add r5, r0, #0x0
	ldr r1, [r5, #0x0]
	cmp r1, #0x4
	bhi _0205E3FC
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0205E330: ; jump table (using 16-bit offset)
	.short _0205E33A - _0205E330 - 2; case 0
	.short _0205E3C0 - _0205E330 - 2; case 1
	.short _0205E3CC - _0205E330 - 2; case 2
	.short _0205E3EC - _0205E330 - 2; case 3
	.short _0205E3DE - _0205E330 - 2; case 4
_0205E33A:
	ldr r0, [r4, #0x34]
	bl sub_02058780
	ldr r0, [r4, #0xc]
	bl Save_Roamers_Get
	bl sub_0202AB40
	add r6, r0, #0x0
	ldrb r0, [r6, #0x0]
	cmp r0, #0x32
	bhs _0205E374
	mov r2, #0x0
	ldr r1, _0205E400 ; =0x0000230A
	add r0, r7, #0x0
	add r3, r2, #0x0
	bl sub_02038CD8
	add r0, r4, #0x0
	mov r1, #0x29
	bl FieldSysGetAttrAddr
	ldrb r2, [r6, #0x0]
	mov r1, #0x32
	sub r1, r1, r2
	strh r1, [r0, #0x0]
	mov r0, #0x4
	str r0, [r5, #0x0]
	b _0205E3FC
_0205E374:
	mov r0, #0x0
	strb r0, [r6, #0x0]
	ldr r0, [r4, #0x38]
	bl GetPlayerXCoord
	add r6, r0, #0x0
	ldr r0, [r4, #0x38]
	bl GetPlayerYCoord
	add r3, r4, #0x0
	add r3, #0x90
	add r2, r0, #0x0
	ldr r3, [r3, #0x0]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl sub_0205DD80
	add r0, r4, #0x0
	add r0, #0x90
	ldr r2, [r0, #0x0]
	ldr r0, [r2, #0x10]
	cmp r0, #0x0
	beq _0205E3BA
	add r0, r4, #0x0
	mov r1, #0x1
	bl sub_0205DED4
	add r0, r4, #0x0
	add r4, #0x90
	ldr r1, [r4, #0x0]
	bl sub_0205DF44
	mov r0, #0x1
	str r0, [r5, #0x0]
	b _0205E3FC
_0205E3BA:
	mov r0, #0x3
	str r0, [r5, #0x0]
	b _0205E3FC
_0205E3C0:
	ldr r0, _0205E404 ; =0x0000047E
	bl sub_0200521C
	mov r0, #0x2
	str r0, [r5, #0x0]
	b _0205E3FC
_0205E3CC:
	add r4, #0x90
	ldr r0, [r4, #0x0]
	bl sub_0205DF9C
	cmp r0, #0x0
	beq _0205E3FC
	mov r0, #0x4
	str r0, [r5, #0x0]
	b _0205E3FC
_0205E3DE:
	bl FreeToHeap
	ldr r0, [r4, #0x34]
	bl sub_020587B0
	mov r0, #0x1
	pop {r3-r7, pc}
_0205E3EC:
	mov r2, #0x0
	ldr r1, _0205E408 ; =0x0000230B
	add r0, r7, #0x0
	add r3, r2, #0x0
	bl sub_02038CD8
	mov r0, #0x4
	str r0, [r5, #0x0]
_0205E3FC:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0205E400: .word 0x0000230A
_0205E404: .word 0x0000047E
_0205E408: .word 0x0000230B

	thumb_func_start sub_0205E40C
sub_0205E40C: ; 0x0205E40C
	push {r3-r5, lr}
	cmp r0, #0x0
	bne _0205E416
	mov r0, #0x0
	pop {r3-r5, pc}
_0205E416:
	add r2, r0, #0x0
	mov r1, #0xc8
	ldr r0, _0205E478 ; =0x00002008
	mul r2, r1
	sub r5, r0, r2
	cmp r5, #0xc8
	bge _0205E426
	add r5, r1, #0x0
_0205E426:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bne _0205E430
	bl GF_AssertFail
_0205E430:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	cmp r0, #0x1
	bhi _0205E43C
	mov r4, #0x0
	b _0205E46A
_0205E43C:
	bl LCRandom
	add r4, r0, #0x0
	lsl r1, r5, #0x10
	ldr r0, _0205E47C ; =0x0000FFFF
	lsr r1, r1, #0x10
	bl _s32_div_f
	add r1, r0, #0x0
	add r1, r1, #0x1
	lsl r1, r1, #0x10
	add r0, r4, #0x0
	lsr r1, r1, #0x10
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	cmp r4, r0
	blo _0205E46A
	bl GF_AssertFail
_0205E46A:
	cmp r4, #0x0
	bne _0205E472
	mov r0, #0x1
	pop {r3-r5, pc}
_0205E472:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0205E478: .word 0x00002008
_0205E47C: .word 0x0000FFFF

	thumb_func_start sub_0205E480
sub_0205E480: ; 0x0205E480
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	add r0, r0, #0x4
	bl sub_0205E4D8
	add r0, r4, #0x0
	add r4, #0x90
	ldr r1, [r4, #0x0]
	bl sub_0205E1F0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0205E49C
sub_0205E49C: ; 0x0205E49C
	add r0, #0x90
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start sub_0205E4A4
sub_0205E4A4: ; 0x0205E4A4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl Save_Bag_Get
	ldr r1, _0205E4D4 ; =0x000001AF
	mov r2, #0x1
	mov r3, #0x4
	bl Bag_HasItem
	cmp r0, #0x1
	bne _0205E4D0
	ldr r0, [r4, #0xc]
	bl Save_Roamers_Get
	bl sub_0202AB40
	ldrb r1, [r0, #0x0]
	cmp r1, #0x32
	bhs _0205E4D0
	add r1, r1, #0x1
	strb r1, [r0, #0x0]
_0205E4D0:
	pop {r4, pc}
	nop
_0205E4D4: .word 0x000001AF

	thumb_func_start sub_0205E4D8
sub_0205E4D8: ; 0x0205E4D8
	ldr r1, [r0, #0x0]
	add r2, r1, #0x1
	ldr r1, _0205E4E8 ; =0x000003E7
	str r2, [r0, #0x0]
	cmp r2, r1
	ble _0205E4E6
	str r1, [r0, #0x0]
_0205E4E6:
	bx lr
	.balign 4
_0205E4E8: .word 0x000003E7
