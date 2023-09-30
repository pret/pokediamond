	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021F38CC
ov05_021F38CC: ; 0x021F38CC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	mov r1, #0
	add r2, r1, #0
	add r5, r0, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r5, #0
	mov r1, #0x46
	mov r2, #0
	bl GetMonData
	mov r1, #0xf
	and r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	add r0, r5, #0
	mov r1, #0x47
	mov r2, #0
	bl GetMonData
	mov r1, #0xf
	and r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #0x48
	mov r2, #0
	bl GetMonData
	mov r1, #0xf
	and r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0x49
	mov r2, #0
	bl GetMonData
	mov r1, #0xf
	and r0, r1
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	add r0, r5, #0
	mov r1, #0x4a
	mov r2, #0
	bl GetMonData
	mov r1, #0xf
	and r0, r1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r0, r5, #0
	mov r1, #0x4b
	mov r2, #0
	bl GetMonData
	mov r1, #0xf
	and r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	eor r0, r6
	asr r1, r4, #8
	mul r0, r7
	eor r0, r1
	lsl r1, r4, #0x18
	lsr r3, r1, #0x18
	lsl r0, r0, #0x10
	ldr r2, [sp, #4]
	ldr r1, [sp]
	lsr r0, r0, #0x10
	eor r2, r1
	ldr r1, [sp, #8]
	mul r2, r1
	add r1, r3, #0
	eor r1, r2
	lsl r1, r1, #0x10
	lsr r1, r1, #8
	add r0, r0, r1
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov05_021F3978
ov05_021F3978: ; 0x021F3978
	ldr r2, _021F399C ; =ov05_021FC5A4
	mov r3, #1
_021F397C:
	lsl r1, r3, #3
	add r1, r2, r1
	ldrh r1, [r1, #4]
	cmp r0, r1
	bhs _021F398E
	sub r0, r3, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_021F398E:
	add r1, r3, #1
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r3, #0xf
	blo _021F397C
	add r0, r3, #0
	bx lr
	.balign 4, 0
_021F399C: .word ov05_021FC5A4

	thumb_func_start ov05_021F39A0
ov05_021F39A0: ; 0x021F39A0
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r0, #4
	add r5, r1, #0
	bl sub_02087A6C
	add r4, r0, #0
	bl sub_02087A84
	add r0, r4, #0
	mov r1, #0
	mov r2, #4
	bl sub_02087A98
	add r0, r4, #0
	add r1, r6, #0
	bl sub_02087B58
	add r6, r0, #0
	add r0, r4, #0
	bl sub_02087B0C
	add r0, r5, #0
	bl ov05_021F3978
	lsl r4, r0, #3
	ldr r0, _021F3A0C ; =ov05_021FC5A8
	ldr r2, _021F3A10 ; =ov05_021FC5A6
	ldrh r0, [r0, r4]
	ldrh r2, [r2, r4]
	asr r1, r5, #0x1f
	mov r3, #0
	sub r0, r5, r0
	sbc r1, r3
	bl _ll_udiv
	add r2, r0, #0
	add r0, r6, #0
	ldr r6, _021F3A14 ; =ov05_021FC5A4
	add r3, r1, #0
	mov r5, #0
	ldrh r4, [r6, r4]
	add r1, r5, #0
	add r2, r4, r2
	adc r5, r3
	add r3, r5, #0
	bl _ll_mul
	mov r2, #0xa
	mov r3, #0
	bl _ll_udiv
	pop {r4, r5, r6, pc}
	nop
_021F3A0C: .word ov05_021FC5A8
_021F3A10: .word ov05_021FC5A6
_021F3A14: .word ov05_021FC5A4

	thumb_func_start Field_CheckPokemonSizeRecord
Field_CheckPokemonSizeRecord: ; 0x021F3A18
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	add r5, r1, #0
	bl SaveArray_Party_Get
	add r1, r5, #0
	bl Party_GetMonByIndex
	mov r1, #5
	mov r2, #0
	str r0, [sp]
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	ldr r0, [sp]
	bl ov05_021F38CC
	add r1, sp, #4
	strh r0, [r1, #2]
	ldrh r1, [r1, #2]
	add r0, r5, #0
	bl ov05_021F39A0
	add r6, r0, #0
	ldr r0, [r4, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205F3E8
	add r1, sp, #4
	strh r0, [r1]
	ldrh r1, [r1]
	add r0, r5, #0
	bl ov05_021F39A0
	add r7, r0, #0
	mov r0, #0xfa
	lsl r0, r0, #2
	mul r0, r6
	mov r1, #0xfe
	bl _u32_div_f
	add r0, r0, #5
	mov r1, #0xa
	bl _u32_div_f
	add r5, r0, #0
	mov r0, #0xfa
	lsl r0, r0, #2
	mul r0, r7
	mov r1, #0xfe
	bl _u32_div_f
	add r0, r0, #5
	mov r1, #0xa
	bl _u32_div_f
	cmp r5, r0
	bne _021F3A9A
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F3A9A:
	cmp r5, r0
	bls _021F3AAE
	ldr r2, [sp]
	add r0, r4, #0
	add r1, r6, #0
	bl sub_020619C0
	add sp, #8
	mov r0, #2
	pop {r3, r4, r5, r6, r7, pc}
_021F3AAE:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start Field_SetPokemonSizeRecord
Field_SetPokemonSizeRecord: ; 0x021F3AB4
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	add r5, r1, #0
	bl SaveArray_Party_Get
	add r1, r5, #0
	bl Party_GetMonByIndex
	bl ov05_021F38CC
	add r1, sp, #0
	strh r0, [r1]
	ldr r0, [r4, #0xc]
	bl Save_VarsFlags_Get
	add r1, sp, #0
	ldrh r1, [r1]
	bl sub_0205F3F8
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021F3AE0
ov05_021F3AE0: ; 0x021F3AE0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	mov r1, #0xf
	add r7, r2, #0
	add r4, r3, #0
	bl FieldSysGetAttrAddr
	add r1, sp, #0x10
	add r5, r0, #0
	ldrh r1, [r1, #0x10]
	add r0, r4, #0
	bl ov05_021F39A0
	mov r1, #0xfa
	lsl r1, r1, #2
	mul r1, r0
	add r0, r1, #0
	mov r1, #0xfe
	bl _u32_div_f
	add r0, r0, #5
	mov r1, #0xa
	bl _u32_div_f
	mov r1, #0xa
	add r4, r0, #0
	bl _u32_div_f
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5]
	add r1, r6, #0
	mov r3, #3
	bl BufferIntegerAsString
	add r0, r4, #0
	mov r1, #0xa
	bl _u32_div_f
	mov r0, #0
	add r2, r1, #0
	str r0, [sp]
	mov r3, #1
	str r3, [sp, #4]
	ldr r0, [r5]
	add r1, r7, #0
	bl BufferIntegerAsString
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start Field_BufferPokemonRecordSize
Field_BufferPokemonRecordSize: ; 0x021F3B4C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl Save_VarsFlags_Get
	bl sub_0205F3E8
	add r1, sp, #4
	strh r0, [r1]
	ldrh r0, [r1]
	add r1, r4, #0
	add r2, r6, #0
	str r0, [sp]
	add r0, r5, #0
	add r3, r7, #0
	bl ov05_021F3AE0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start Field_BufferPartyPokemonSize
Field_BufferPartyPokemonSize: ; 0x021F3B7C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	str r2, [sp, #4]
	ldr r0, [r5, #0xc]
	add r4, r3, #0
	add r7, r1, #0
	bl SaveArray_Party_Get
	add r1, r4, #0
	bl Party_GetMonByIndex
	mov r1, #5
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r6, #0
	bl ov05_021F38CC
	add r1, sp, #8
	strh r0, [r1]
	ldrh r0, [r1]
	add r1, r7, #0
	add r3, r4, #0
	str r0, [sp]
	ldr r2, [sp, #4]
	add r0, r5, #0
	bl ov05_021F3AE0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	.section .rodata

	.global ov05_021FC5A4
ov05_021FC5A4: ; 0x021FC5A4
	.byte 0x22, 0x01

	.global ov05_021FC5A6
ov05_021FC5A6: ; 0x021FC5A6
	.byte 0x01, 0x00

	.global ov05_021FC5A8
ov05_021FC5A8: ; 0x021FC5A8
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x2C, 0x01, 0x01, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x90, 0x01, 0x02, 0x00, 0x6E, 0x00, 0x00, 0x00
	.byte 0xF4, 0x01, 0x04, 0x00, 0x36, 0x01, 0x00, 0x00, 0x58, 0x02, 0x14, 0x00, 0xC6, 0x02, 0x00, 0x00
	.byte 0xBC, 0x02, 0x32, 0x00, 0x96, 0x0A, 0x00, 0x00, 0x20, 0x03, 0x64, 0x00, 0x1E, 0x1E, 0x00, 0x00
	.byte 0x84, 0x03, 0x96, 0x00, 0x2E, 0x45, 0x00, 0x00, 0xE8, 0x03, 0x96, 0x00, 0xC6, 0x7F, 0x00, 0x00
	.byte 0x4C, 0x04, 0x64, 0x00, 0x5E, 0xBA, 0x00, 0x00, 0xB0, 0x04, 0x32, 0x00, 0x6E, 0xE1, 0x00, 0x00
	.byte 0x14, 0x05, 0x14, 0x00, 0xF6, 0xF4, 0x00, 0x00, 0x78, 0x05, 0x05, 0x00, 0xC6, 0xFC, 0x00, 0x00
	.byte 0xDC, 0x05, 0x02, 0x00, 0xBA, 0xFE, 0x00, 0x00, 0x40, 0x06, 0x01, 0x00, 0x82, 0xFF, 0x00, 0x00
	.byte 0xA4, 0x06, 0x01, 0x00, 0xE6, 0xFF, 0x00, 0x00
