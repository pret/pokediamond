	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD11_02242B78
MOD11_02242B78: ; 0x02242B78
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r7, r1, #0
	str r2, [sp, #4]
	add r1, r2, #0
	add r2, r3, #0
	str r0, [sp]
	bl MOD11_02230014
	ldr r1, [sp, #4]
	mov r2, #0xc0
	add r5, r1, #0
	mov r1, #0xb5
	lsl r1, r1, #6
	add r1, r7, r1
	mul r5, r2
	str r1, [sp, #0x18]
	mov r1, #5
	mov r2, #0
	add r4, r0, #0
	bl GetMonData
	ldr r1, [sp, #0x18]
	mov r2, #0
	strh r0, [r1, r5]
	add r0, r4, #0
	mov r1, #0xa4
	bl GetMonData
	ldr r1, _02242F4C ; =0x00002D42
	add r2, r7, r5
	strh r0, [r2, r1]
	add r0, r4, #0
	mov r1, #0xa5
	mov r2, #0
	bl GetMonData
	ldr r1, _02242F50 ; =0x00002D44
	add r2, r7, r5
	strh r0, [r2, r1]
	add r0, r4, #0
	mov r1, #0xa6
	mov r2, #0
	bl GetMonData
	ldr r1, _02242F54 ; =0x00002D46
	add r2, r7, r5
	strh r0, [r2, r1]
	add r0, r4, #0
	mov r1, #0xa7
	mov r2, #0
	bl GetMonData
	ldr r1, _02242F58 ; =0x00002D48
	add r2, r7, r5
	strh r0, [r2, r1]
	add r0, r4, #0
	mov r1, #0xa8
	mov r2, #0
	bl GetMonData
	add r1, r7, r5
	ldr r2, _02242F5C ; =0x00002D4A
	str r1, [sp, #0xc]
	strh r0, [r1, r2]
	add r0, r1, #0
	mov r6, #0
	str r0, [sp, #0x14]
	str r0, [sp, #0x10]
_02242C02:
	add r1, r6, #0
	add r0, r4, #0
	add r1, #0x36
	mov r2, #0
	bl GetMonData
	ldr r2, [sp, #0x14]
	ldr r1, _02242F60 ; =0x00002D4C
	strh r0, [r2, r1]
	add r1, r6, #0
	add r0, r4, #0
	add r1, #0x3a
	mov r2, #0
	bl GetMonData
	ldr r2, [sp, #0x10]
	ldr r1, _02242F64 ; =0x00002D6C
	strb r0, [r2, r1]
	add r1, r6, #0
	add r0, r4, #0
	add r1, #0x3e
	mov r2, #0
	bl GetMonData
	ldr r2, [sp, #0x10]
	ldr r1, _02242F68 ; =0x00002D70
	add r6, r6, #1
	strb r0, [r2, r1]
	ldr r0, [sp, #0x14]
	add r0, r0, #2
	str r0, [sp, #0x14]
	add r0, r2, #0
	add r0, r0, #1
	str r0, [sp, #0x10]
	cmp r6, #4
	blt _02242C02
	add r0, r1, #0
	sub r0, #0x1c
	add r6, r7, r0
	add r0, r4, #0
	mov r1, #0x46
	mov r2, #0
	bl GetMonData
	ldr r1, [r6, r5]
	mov r2, #0x1f
	bic r1, r2
	mov r2, #0x1f
	and r0, r2
	orr r0, r1
	str r0, [r6, r5]
	add r0, r4, #0
	mov r1, #0x47
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x1b
	ldr r2, [r6, r5]
	ldr r1, _02242F6C ; =0xFFFFFC1F
	lsr r0, r0, #0x16
	and r1, r2
	orr r0, r1
	str r0, [r6, r5]
	add r0, r4, #0
	mov r1, #0x48
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x1b
	ldr r2, [r6, r5]
	ldr r1, _02242F70 ; =0xFFFF83FF
	lsr r0, r0, #0x11
	and r1, r2
	orr r0, r1
	str r0, [r6, r5]
	add r0, r4, #0
	mov r1, #0x49
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x1b
	ldr r2, [r6, r5]
	ldr r1, _02242F74 ; =0xFFF07FFF
	lsr r0, r0, #0xc
	and r1, r2
	orr r0, r1
	str r0, [r6, r5]
	add r0, r4, #0
	mov r1, #0x4a
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x1b
	ldr r2, [r6, r5]
	ldr r1, _02242F78 ; =0xFE0FFFFF
	lsr r0, r0, #7
	and r1, r2
	orr r0, r1
	str r0, [r6, r5]
	add r0, r4, #0
	mov r1, #0x4b
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x1b
	ldr r2, [r6, r5]
	ldr r1, _02242F7C ; =0xC1FFFFFF
	lsr r0, r0, #2
	and r1, r2
	orr r0, r1
	str r0, [r6, r5]
	add r0, r4, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	ldr r2, [r6, r5]
	ldr r1, _02242F80 ; =0xBFFFFFFF
	lsl r0, r0, #0x1f
	and r1, r2
	lsr r0, r0, #1
	orr r0, r1
	str r0, [r6, r5]
	add r0, r4, #0
	mov r1, #0x4d
	mov r2, #0
	bl GetMonData
	ldr r2, [r6, r5]
	ldr r1, _02242F84 ; =0x7FFFFFFF
	lsl r0, r0, #0x1f
	and r1, r2
	orr r0, r1
	str r0, [r6, r5]
	ldr r0, _02242F88 ; =0x0000213C
	ldr r1, [r7, r0]
	mov r0, #1
	lsl r0, r0, #8
	tst r0, r1
	bne _02242D2E
	ldr r0, _02242F8C ; =0x00002D58
	mov r2, #0
	mov r1, #6
_02242D20:
	ldr r3, [sp, #0xc]
	add r2, r2, #1
	strb r1, [r3, r0]
	add r3, r3, #1
	str r3, [sp, #0xc]
	cmp r2, #8
	blt _02242D20
_02242D2E:
	ldr r0, _02242F90 ; =0x00002D68
	mov r1, #1
	add r0, r7, r0
	ldr r2, [r0, r5]
	bic r2, r1
	str r2, [r0, r5]
	ldr r2, [r0, r5]
	mov r1, #2
	bic r2, r1
	str r2, [r0, r5]
	ldr r2, [r0, r5]
	mov r1, #4
	bic r2, r1
	str r2, [r0, r5]
	ldr r2, [r0, r5]
	mov r1, #8
	bic r2, r1
	str r2, [r0, r5]
	ldr r2, [r0, r5]
	mov r1, #0x10
	bic r2, r1
	str r2, [r0, r5]
	ldr r2, [r0, r5]
	mov r1, #0x20
	bic r2, r1
	str r2, [r0, r5]
	ldr r2, [r0, r5]
	mov r1, #0x40
	bic r2, r1
	str r2, [r0, r5]
	ldr r2, [r0, r5]
	mov r1, #0x80
	bic r2, r1
	str r2, [r0, r5]
	ldr r2, [r0, r5]
	ldr r1, _02242F94 ; =0xFFFFFEFF
	and r1, r2
	str r1, [r0, r5]
	ldr r2, [r0, r5]
	ldr r1, _02242F98 ; =0xFFFFFDFF
	and r1, r2
	str r1, [r0, r5]
	ldr r2, [r0, r5]
	ldr r1, _02242F9C ; =0xFFFFFBFF
	and r1, r2
	str r1, [r0, r5]
	add r0, r4, #0
	mov r1, #0xb0
	mov r2, #0
	bl GetMonData
	ldr r1, _02242FA0 ; =0x00002D64
	add r2, r7, r5
	strb r0, [r2, r1]
	add r0, r4, #0
	mov r1, #0xb1
	mov r2, #0
	bl GetMonData
	ldr r1, _02242FA4 ; =0x00002D65
	add r2, r7, r5
	strb r0, [r2, r1]
	add r1, #0x59
	add r0, r7, r1
	str r0, [sp, #0x1c]
	add r0, r4, #0
	bl GetMonGender
	ldr r1, [sp, #0x1c]
	mov r2, #0xf
	ldrb r1, [r1, r5]
	bic r1, r2
	mov r2, #0xf
	and r0, r2
	orr r1, r0
	ldr r0, [sp, #0x1c]
	strb r1, [r0, r5]
	ldr r0, _02242FA8 ; =0x00002D66
	add r6, r7, r0
	add r0, r4, #0
	bl MonIsShiny
	ldrb r1, [r6, r5]
	mov r2, #0x20
	lsl r0, r0, #0x1f
	bic r1, r2
	lsr r0, r0, #0x1a
	orr r0, r1
	strb r0, [r6, r5]
	add r0, r4, #0
	mov r1, #0x70
	mov r2, #0
	bl GetMonData
	ldrb r1, [r6, r5]
	mov r2, #0x1f
	lsl r0, r0, #0x18
	bic r1, r2
	lsr r2, r0, #0x18
	mov r0, #0x1f
	and r0, r2
	orr r0, r1
	strb r0, [r6, r5]
	ldr r0, [sp]
	bl MOD11_0222FF74
	mov r1, #0x22
	lsl r1, r1, #4
	tst r0, r1
	beq _02242E24
	ldr r2, _02242FAC ; =0x00002D67
	mov r0, #0
	add r3, r7, r5
	add r1, r2, #0
	strb r0, [r3, r2]
	add r2, #0x51
	add r1, #0x45
	add r2, r7, r2
	str r0, [r3, r1]
	add r1, r2, r5
	str r1, [sp, #8]
	strh r0, [r2, r5]
	b _02242E58
_02242E24:
	add r0, r4, #0
	mov r1, #0xa
	mov r2, #0
	bl GetMonData
	ldr r1, _02242FAC ; =0x00002D67
	add r2, r7, r5
	strb r0, [r2, r1]
	add r0, r4, #0
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	ldr r1, _02242FB0 ; =0x00002DAC
	add r2, r7, r5
	str r0, [r2, r1]
	add r1, #0xc
	add r6, r7, r1
	add r0, r6, r5
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #6
	mov r2, #0
	bl GetMonData
	strh r0, [r6, r5]
_02242E58:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	add r6, r0, #0
	mul r6, r1
	add r0, r4, #0
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	ldr r1, _02242FB4 ; =0x00002D74
	add r2, r7, r6
	strb r0, [r2, r1]
	add r0, r4, #0
	mov r1, #9
	mov r2, #0
	bl GetMonData
	ldr r1, _02242FB8 ; =0x00002D75
	add r2, r7, r6
	strb r0, [r2, r1]
	add r0, r4, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	ldr r1, _02242FBC ; =0x00002D8C
	add r2, r7, r6
	str r0, [r2, r1]
	add r0, r4, #0
	mov r1, #0xa3
	mov r2, #0
	bl GetMonData
	ldr r1, _02242FC0 ; =0x00002D90
	add r2, r7, r6
	str r0, [r2, r1]
	add r0, r4, #0
	mov r1, #8
	mov r2, #0
	bl GetMonData
	ldr r1, _02242FC4 ; =0x00002DA4
	add r2, r7, r6
	str r0, [r2, r1]
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl GetMonData
	ldr r1, _02242FC8 ; =0x00002DA8
	add r2, r7, r6
	str r0, [r2, r1]
	add r0, r4, #0
	mov r1, #7
	mov r2, #0
	bl GetMonData
	ldr r1, _02242FCC ; =0x00002DB4
	add r2, r7, r6
	str r0, [r2, r1]
	add r0, r4, #0
	mov r1, #0x9c
	mov r2, #0
	bl GetMonData
	ldr r1, [sp, #0x1c]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1c
	ldrb r1, [r1, r5]
	mov r2, #0xf0
	lsr r0, r0, #0x18
	bic r1, r2
	orr r1, r0
	ldr r0, [sp, #0x1c]
	mov r2, #0
	strb r1, [r0, r5]
	add r0, r4, #0
	mov r1, #0x9a
	bl GetMonData
	ldr r1, _02242FD0 ; =0x00002DBF
	add r2, r7, r6
	strb r0, [r2, r1]
	mov r0, #5
	bl sub_02087A6C
	mov r1, #0
	mov r2, #5
	str r0, [sp, #0x20]
	bl sub_02087A98
	ldr r1, [sp, #0x18]
	ldr r0, [sp, #0x20]
	ldrh r1, [r1, r5]
	bl sub_02087B78
	ldr r1, _02242FD4 ; =0x00002D60
	add r2, r7, r6
	str r0, [r2, r1]
	ldr r0, [sp, #0x20]
	bl sub_02087B0C
	ldr r0, [sp, #0x20]
	bl sub_02087A84
	ldr r2, _02242FD8 ; =0x00002D76
	add r0, r4, #0
	add r2, r7, r2
	mov r1, #0x74
	add r2, r2, r6
	bl GetMonData
	ldr r2, _02242FDC ; =0x00002D94
	add r0, r4, #0
	add r2, r7, r2
	mov r1, #0x8f
	add r2, r2, r6
	bl GetMonData
	ldr r0, _02242FE0 ; =0x00002DBC
	b _02242FE4
	.align 2, 0
_02242F4C: .word 0x00002D42
_02242F50: .word 0x00002D44
_02242F54: .word 0x00002D46
_02242F58: .word 0x00002D48
_02242F5C: .word 0x00002D4A
_02242F60: .word 0x00002D4C
_02242F64: .word 0x00002D6C
_02242F68: .word 0x00002D70
_02242F6C: .word 0xFFFFFC1F
_02242F70: .word 0xFFFF83FF
_02242F74: .word 0xFFF07FFF
_02242F78: .word 0xFE0FFFFF
_02242F7C: .word 0xC1FFFFFF
_02242F80: .word 0xBFFFFFFF
_02242F84: .word 0x7FFFFFFF
_02242F88: .word 0x0000213C
_02242F8C: .word 0x00002D58
_02242F90: .word 0x00002D68
_02242F94: .word 0xFFFFFEFF
_02242F98: .word 0xFFFFFDFF
_02242F9C: .word 0xFFFFFBFF
_02242FA0: .word 0x00002D64
_02242FA4: .word 0x00002D65
_02242FA8: .word 0x00002D66
_02242FAC: .word 0x00002D67
_02242FB0: .word 0x00002DAC
_02242FB4: .word 0x00002D74
_02242FB8: .word 0x00002D75
_02242FBC: .word 0x00002D8C
_02242FC0: .word 0x00002D90
_02242FC4: .word 0x00002DA4
_02242FC8: .word 0x00002DA8
_02242FCC: .word 0x00002DB4
_02242FD0: .word 0x00002DBF
_02242FD4: .word 0x00002D60
_02242FD8: .word 0x00002D76
_02242FDC: .word 0x00002D94
_02242FE0: .word 0x00002DBC
_02242FE4:
	mov r2, #0
	add r1, r7, r6
	strb r2, [r1, r0]
	add r0, r0, #1
	strb r2, [r1, r0]
	ldr r0, [sp]
	ldr r1, [sp, #4]
	bl MOD11_02230270
	add r4, r0, #0
	ldr r0, [sp, #4]
	add r1, r7, r0
	ldr r0, _02243048 ; =0x0000219C
	ldrb r0, [r1, r0]
	bl MaskOfFlagNo
	lsl r1, r4, #3
	add r2, r7, r1
	mov r1, #0x71
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	lsl r1, r1, #3
	lsr r1, r1, #0x1a
	tst r0, r1
	beq _0224302C
	ldr r0, [sp, #8]
	mov r1, #0
	strh r1, [r0]
	ldr r0, _0224304C ; =0x00002DCC
	add sp, #0x24
	add r2, r7, r0
	ldr r1, [r2, r5]
	ldr r0, _02243050 ; =0xFFBFFFFF
	and r0, r1
	str r0, [r2, r5]
	pop {r4, r5, r6, r7, pc}
_0224302C:
	ldr r0, [sp, #8]
	ldrh r0, [r0]
	cmp r0, #0
	beq _02243042
	ldr r0, _0224304C ; =0x00002DCC
	add r2, r7, r0
	mov r0, #1
	ldr r1, [r2, r5]
	lsl r0, r0, #0x16
	orr r0, r1
	str r0, [r2, r5]
_02243042:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_02243048: .word 0x0000219C
_0224304C: .word 0x00002DCC
_02243050: .word 0xFFBFFFFF

	thumb_func_start MOD11_02243054
MOD11_02243054: ; 0x02243054
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r2, #0
	str r1, [sp]
	add r1, r5, #0
	add r2, r3, #0
	bl MOD11_02230014
	mov r1, #0xc0
	mul r1, r5
	str r1, [sp, #4]
	mov r1, #0xa4
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	ldr r2, [sp]
	ldr r1, [sp, #4]
	add r2, r2, r1
	ldr r1, _022431A8 ; =0x00002D42
	strh r0, [r2, r1]
	add r0, r6, #0
	mov r1, #0xa5
	mov r2, #0
	bl GetMonData
	ldr r2, [sp]
	ldr r1, [sp, #4]
	add r2, r2, r1
	ldr r1, _022431AC ; =0x00002D44
	strh r0, [r2, r1]
	add r0, r6, #0
	mov r1, #0xa6
	mov r2, #0
	bl GetMonData
	ldr r2, [sp]
	ldr r1, [sp, #4]
	add r2, r2, r1
	ldr r1, _022431B0 ; =0x00002D46
	strh r0, [r2, r1]
	add r0, r6, #0
	mov r1, #0xa7
	mov r2, #0
	bl GetMonData
	ldr r2, [sp]
	ldr r1, [sp, #4]
	add r2, r2, r1
	ldr r1, _022431B4 ; =0x00002D48
	strh r0, [r2, r1]
	add r0, r6, #0
	mov r1, #0xa8
	mov r2, #0
	bl GetMonData
	ldr r2, [sp]
	ldr r1, [sp, #4]
	add r2, r2, r1
	ldr r1, _022431B8 ; =0x00002D4A
	strh r0, [r2, r1]
	add r0, r6, #0
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	ldr r2, [sp]
	ldr r1, [sp, #4]
	add r2, r2, r1
	ldr r1, _022431BC ; =0x00002D74
	strb r0, [r2, r1]
	add r0, r6, #0
	mov r1, #9
	mov r2, #0
	bl GetMonData
	ldr r2, [sp]
	ldr r1, [sp, #4]
	add r2, r2, r1
	ldr r1, _022431C0 ; =0x00002D75
	strb r0, [r2, r1]
	add r0, r6, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	ldr r2, [sp]
	ldr r1, [sp, #4]
	add r2, r2, r1
	ldr r1, _022431C4 ; =0x00002D8C
	str r0, [r2, r1]
	add r0, r6, #0
	mov r1, #0xa3
	mov r2, #0
	bl GetMonData
	ldr r2, [sp]
	ldr r1, [sp, #4]
	add r2, r2, r1
	ldr r1, _022431C8 ; =0x00002D90
	str r0, [r2, r1]
	add r0, r1, #0
	add r0, #0x20
	ldr r2, [r2, r0]
	mov r0, #2
	lsl r0, r0, #0x14
	tst r0, r2
	bne _022431A4
	mov r0, #0xc0
	mul r0, r5
	ldr r2, [sp]
	str r0, [sp, #8]
	add r7, r2, r0
	add r1, #0x3c
	add r0, r2, #0
	add r0, r0, r1
	mov r4, #0
	add r5, r7, #0
	str r0, [sp, #0xc]
_02243142:
	add r0, r4, #0
	bl MaskOfFlagNo
	ldr r2, [sp, #0xc]
	ldr r1, [sp, #8]
	ldr r1, [r2, r1]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1c
	tst r0, r1
	bne _02243186
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x36
	mov r2, #0
	bl GetMonData
	ldr r1, _022431CC ; =0x00002D4C
	mov r2, #0
	strh r0, [r7, r1]
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x3a
	bl GetMonData
	ldr r1, _022431D0 ; =0x00002D6C
	mov r2, #0
	strb r0, [r5, r1]
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x3e
	bl GetMonData
	ldr r1, _022431D4 ; =0x00002D70
	strb r0, [r5, r1]
_02243186:
	add r4, r4, #1
	add r7, r7, #2
	add r5, r5, #1
	cmp r4, #4
	blt _02243142
	add r0, r6, #0
	mov r1, #8
	mov r2, #0
	bl GetMonData
	ldr r2, [sp]
	ldr r1, [sp, #4]
	add r2, r2, r1
	ldr r1, _022431D8 ; =0x00002DA4
	str r0, [r2, r1]
_022431A4:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022431A8: .word 0x00002D42
_022431AC: .word 0x00002D44
_022431B0: .word 0x00002D46
_022431B4: .word 0x00002D48
_022431B8: .word 0x00002D4A
_022431BC: .word 0x00002D74
_022431C0: .word 0x00002D75
_022431C4: .word 0x00002D8C
_022431C8: .word 0x00002D90
_022431CC: .word 0x00002D4C
_022431D0: .word 0x00002D6C
_022431D4: .word 0x00002D70
_022431D8: .word 0x00002DA4

	thumb_func_start MOD11_022431DC
MOD11_022431DC: ; 0x022431DC
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r2, #0
	add r5, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	bl GetNarcMemberSizeByIdPair
	mov r1, #0x19
	lsl r1, r1, #6
	cmp r0, r1
	blo _022431F8
	bl GF_AssertFail
_022431F8:
	add r0, r5, #0
	add r0, #0xac
	str r4, [r0]
	add r0, r5, #0
	add r0, #0xb0
	str r6, [r0]
	add r0, r5, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
	mov r0, #0x27
	lsl r0, r0, #8
	add r0, r5, r0
	add r1, r4, #0
	add r2, r6, #0
	bl ReadWholeNarcMemberByIdPair
	pop {r4, r5, r6, pc}

	thumb_func_start MOD11_0224321C
MOD11_0224321C: ; 0x0224321C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r2, #0
	add r5, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	bl GetNarcMemberSizeByIdPair
	mov r1, #0x19
	lsl r1, r1, #6
	cmp r0, r1
	blo _02243238
	bl GF_AssertFail
_02243238:
	add r0, r5, #0
	add r0, #0xb8
	ldr r0, [r0]
	cmp r0, #4
	blt _02243246
	bl GF_AssertFail
_02243246:
	add r1, r5, #0
	add r1, #0xb8
	ldr r1, [r1]
	add r0, r5, #0
	add r0, #0xac
	lsl r1, r1, #2
	add r1, r5, r1
	ldr r0, [r0]
	add r1, #0xbc
	str r0, [r1]
	add r1, r5, #0
	add r1, #0xb8
	ldr r1, [r1]
	add r0, r5, #0
	add r0, #0xb0
	lsl r1, r1, #2
	add r1, r5, r1
	ldr r0, [r0]
	add r1, #0xcc
	str r0, [r1]
	add r1, r5, #0
	add r1, #0xb8
	ldr r1, [r1]
	add r0, r5, #0
	add r0, #0xb4
	lsl r1, r1, #2
	add r1, r5, r1
	ldr r0, [r0]
	add r1, #0xdc
	str r0, [r1]
	add r0, r5, #0
	add r0, #0xb8
	ldr r0, [r0]
	add r2, r6, #0
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0xb8
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xac
	str r4, [r0]
	add r0, r5, #0
	add r0, #0xb0
	str r6, [r0]
	add r0, r5, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
	mov r0, #0x27
	lsl r0, r0, #8
	add r0, r5, r0
	add r1, r4, #0
	bl ReadWholeNarcMemberByIdPair
	pop {r4, r5, r6, pc}

	thumb_func_start MOD11_022432B4
MOD11_022432B4: ; 0x022432B4
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	add r1, #0xb8
	ldr r1, [r1]
	cmp r1, #0
	beq _022432FE
	add r1, r4, #0
	add r1, #0xb8
	ldr r1, [r1]
	sub r2, r1, #1
	add r1, r4, #0
	add r1, #0xb8
	str r2, [r1]
	add r1, r4, #0
	add r1, #0xb8
	ldr r1, [r1]
	lsl r2, r1, #2
	add r1, r4, r2
	add r2, r4, r2
	add r1, #0xbc
	add r2, #0xcc
	ldr r1, [r1]
	ldr r2, [r2]
	bl MOD11_022431DC
	add r0, r4, #0
	add r0, #0xb8
	ldr r0, [r0]
	lsl r0, r0, #2
	add r0, r4, r0
	add r0, #0xdc
	ldr r0, [r0]
	add r4, #0xb4
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
_022432FE:
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD11_02243304
MOD11_02243304: ; 0x02243304
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	lsl r0, r1, #6
	lsl r6, r2, #4
	add r1, r4, r0
	add r5, r1, r6
	mov r1, #0x22
	add r7, r3, #0
	mov r3, #0
	lsl r1, r1, #8
_02243318:
	ldrb r2, [r5, r1]
	cmp r2, #0
	bne _0224332C
	add r0, r4, r0
	add r0, r0, r6
	add r1, r0, r3
	mov r0, #0x22
	lsl r0, r0, #8
	strb r7, [r1, r0]
	b _02243334
_0224332C:
	add r3, r3, #1
	add r5, r5, #1
	cmp r3, #0x10
	blt _02243318
_02243334:
	cmp r3, #0x10
	blt _0224333C
	bl GF_AssertFail
_0224333C:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD11_02243340
MOD11_02243340: ; 0x02243340
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	str r2, [sp]
	add r4, r3, #0
	bne _02243350
	bl GF_AssertFail
_02243350:
	ldr r0, [sp]
	lsl r6, r5, #6
	lsl r5, r0, #4
	add r0, r7, r6
	add r3, r0, r5
	mov r0, #0x22
	mov r2, #0
	lsl r0, r0, #8
_02243360:
	ldrb r1, [r3, r0]
	cmp r4, r1
	bne _02243376
	add r1, r7, r6
	add r1, r1, r5
	add r3, r1, r2
	mov r1, #0x22
	mov r0, #0
	lsl r1, r1, #8
	strb r0, [r3, r1]
	b _0224337E
_02243376:
	add r2, r2, #1
	add r3, r3, #1
	cmp r2, #0x10
	blt _02243360
_0224337E:
	cmp r2, #0x10
	blt _02243386
	bl GF_AssertFail
_02243386:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD11_02243388
MOD11_02243388: ; 0x02243388
	push {r3, r4, r5, r6, r7, lr}
	mov r2, #0
	mov r4, #0x22
	mov lr, r0
	mov ip, r2
	add r7, r0, #0
	add r6, r2, #0
	lsl r4, r4, #8
_02243398:
	mov r0, #0
	add r3, r7, #0
_0224339C:
	add r1, r6, #0
_0224339E:
	add r5, r3, r1
	ldrb r5, [r5, r4]
	add r1, r1, #1
	add r2, r2, r5
	cmp r1, #0x10
	blt _0224339E
	add r0, r0, #1
	add r3, #0x10
	cmp r0, #4
	blt _0224339C
	mov r0, ip
	add r0, r0, #1
	add r7, #0x40
	mov ip, r0
	cmp r0, #4
	blt _02243398
	cmp r2, #0
	bne _022433CA
	ldr r1, _022433D8 ; =0x00003148
	mov r3, #0
	mov r0, lr
	str r3, [r0, r1]
_022433CA:
	cmp r2, #0
	bne _022433D2
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_022433D2:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022433D8: .word 0x00003148

	thumb_func_start MOD11_022433DC
MOD11_022433DC: ; 0x022433DC
	push {r3, lr}
	ldr r1, _022433F8 ; =0x00003148
	ldr r2, [r0, r1]
	add r2, r2, #1
	str r2, [r0, r1]
	ldr r1, [r0, r1]
	ldr r0, _022433FC ; =0x00000708
	cmp r1, r0
	ble _022433F4
	mov r0, #1
	bl sub_020336A0
_022433F4:
	pop {r3, pc}
	nop
_022433F8: .word 0x00003148
_022433FC: .word 0x00000708

	thumb_func_start MOD11_02243400
MOD11_02243400: ; 0x02243400
	push {r3, r4}
	lsl r1, r1, #8
	add r4, r0, r1
	mov r3, #0
	mov r0, #0x23
	mov r1, #1
	add r2, r3, #0
	lsl r0, r0, #8
	lsl r1, r1, #8
_02243412:
	add r3, r3, #1
	strb r2, [r4, r0]
	add r4, r4, #1
	cmp r3, r1
	blt _02243412
	pop {r3, r4}
	bx lr

	thumb_func_start MOD11_02243420
MOD11_02243420: ; 0x02243420
	push {r4, r5, r6, lr}
	mov r4, #0xb5
	lsl r4, r4, #6
	add r5, r0, r4
	mov r6, #0xc0
	add r4, r1, #0
	mul r4, r6
	add r4, r5, r4
	cmp r2, #0x64
	bls _02243436
	b _02243794
_02243436:
	add r5, r2, r2
	add r5, pc
	ldrh r5, [r5, #6]
	lsl r5, r5, #0x10
	asr r5, r5, #0x10
	add pc, r5
_02243442: ; jump table
	.short _0224350C - _02243442 - 2 ; case 0
	.short _02243510 - _02243442 - 2 ; case 1
	.short _02243514 - _02243442 - 2 ; case 2
	.short _02243518 - _02243442 - 2 ; case 3
	.short _0224351C - _02243442 - 2 ; case 4
	.short _02243520 - _02243442 - 2 ; case 5
	.short _02243524 - _02243442 - 2 ; case 6
	.short _02243524 - _02243442 - 2 ; case 7
	.short _02243524 - _02243442 - 2 ; case 8
	.short _02243524 - _02243442 - 2 ; case 9
	.short _0224352E - _02243442 - 2 ; case 10
	.short _02243536 - _02243442 - 2 ; case 11
	.short _0224353E - _02243442 - 2 ; case 12
	.short _02243546 - _02243442 - 2 ; case 13
	.short _0224354E - _02243442 - 2 ; case 14
	.short _02243556 - _02243442 - 2 ; case 15
	.short _0224355E - _02243442 - 2 ; case 16
	.short _02243566 - _02243442 - 2 ; case 17
	.short _0224356C - _02243442 - 2 ; case 18
	.short _0224356C - _02243442 - 2 ; case 19
	.short _0224356C - _02243442 - 2 ; case 20
	.short _0224356C - _02243442 - 2 ; case 21
	.short _0224356C - _02243442 - 2 ; case 22
	.short _0224356C - _02243442 - 2 ; case 23
	.short _0224356C - _02243442 - 2 ; case 24
	.short _0224356C - _02243442 - 2 ; case 25
	.short _02243576 - _02243442 - 2 ; case 26
	.short _0224357C - _02243442 - 2 ; case 27
	.short _0224357C - _02243442 - 2 ; case 28
	.short _02243582 - _02243442 - 2 ; case 29
	.short _0224358C - _02243442 - 2 ; case 30
	.short _02243596 - _02243442 - 2 ; case 31
	.short _02243596 - _02243442 - 2 ; case 32
	.short _02243596 - _02243442 - 2 ; case 33
	.short _02243596 - _02243442 - 2 ; case 34
	.short _022435A0 - _02243442 - 2 ; case 35
	.short _022435A0 - _02243442 - 2 ; case 36
	.short _022435A0 - _02243442 - 2 ; case 37
	.short _022435A0 - _02243442 - 2 ; case 38
	.short _022435AA - _02243442 - 2 ; case 39
	.short _022435AA - _02243442 - 2 ; case 40
	.short _022435AA - _02243442 - 2 ; case 41
	.short _022435AA - _02243442 - 2 ; case 42
	.short _022435BE - _02243442 - 2 ; case 43
	.short _022435C4 - _02243442 - 2 ; case 44
	.short _022435CA - _02243442 - 2 ; case 45
	.short _022435DC - _02243442 - 2 ; case 46
	.short _022435E8 - _02243442 - 2 ; case 47
	.short _022435EC - _02243442 - 2 ; case 48
	.short _022435F0 - _02243442 - 2 ; case 49
	.short _02243606 - _02243442 - 2 ; case 50
	.short _0224360A - _02243442 - 2 ; case 51
	.short _0224360E - _02243442 - 2 ; case 52
	.short _02243612 - _02243442 - 2 ; case 53
	.short _02243616 - _02243442 - 2 ; case 54
	.short _0224361A - _02243442 - 2 ; case 55
	.short _02243620 - _02243442 - 2 ; case 56
	.short _02243626 - _02243442 - 2 ; case 57
	.short _0224362C - _02243442 - 2 ; case 58
	.short _02243636 - _02243442 - 2 ; case 59
	.short _0224363C - _02243442 - 2 ; case 60
	.short _02243642 - _02243442 - 2 ; case 61
	.short _0224364C - _02243442 - 2 ; case 62
	.short _02243656 - _02243442 - 2 ; case 63
	.short _02243660 - _02243442 - 2 ; case 64
	.short _0224366A - _02243442 - 2 ; case 65
	.short _02243674 - _02243442 - 2 ; case 66
	.short _0224367E - _02243442 - 2 ; case 67
	.short _02243688 - _02243442 - 2 ; case 68
	.short _02243692 - _02243442 - 2 ; case 69
	.short _0224369C - _02243442 - 2 ; case 70
	.short _022436A6 - _02243442 - 2 ; case 71
	.short _022436B0 - _02243442 - 2 ; case 72
	.short _022436BA - _02243442 - 2 ; case 73
	.short _022436C2 - _02243442 - 2 ; case 74
	.short _022436CC - _02243442 - 2 ; case 75
	.short _022436D6 - _02243442 - 2 ; case 76
	.short _022436E0 - _02243442 - 2 ; case 77
	.short _022436EA - _02243442 - 2 ; case 78
	.short _022436F4 - _02243442 - 2 ; case 79
	.short _022436FE - _02243442 - 2 ; case 80
	.short _02243708 - _02243442 - 2 ; case 81
	.short _02243712 - _02243442 - 2 ; case 82
	.short _0224371C - _02243442 - 2 ; case 83
	.short _02243726 - _02243442 - 2 ; case 84
	.short _02243730 - _02243442 - 2 ; case 85
	.short _0224373A - _02243442 - 2 ; case 86
	.short _02243744 - _02243442 - 2 ; case 87
	.short _0224374A - _02243442 - 2 ; case 88
	.short _02243750 - _02243442 - 2 ; case 89
	.short _02243756 - _02243442 - 2 ; case 90
	.short _0224375C - _02243442 - 2 ; case 91
	.short _02243762 - _02243442 - 2 ; case 92
	.short _02243768 - _02243442 - 2 ; case 93
	.short _0224376E - _02243442 - 2 ; case 94
	.short _02243774 - _02243442 - 2 ; case 95
	.short _0224377A - _02243442 - 2 ; case 96
	.short _02243782 - _02243442 - 2 ; case 97
	.short _02243794 - _02243442 - 2 ; case 98
	.short _02243794 - _02243442 - 2 ; case 99
	.short _0224378A - _02243442 - 2 ; case 100
_0224350C:
	ldrh r0, [r4]
	pop {r4, r5, r6, pc}
_02243510:
	ldrh r0, [r4, #2]
	pop {r4, r5, r6, pc}
_02243514:
	ldrh r0, [r4, #4]
	pop {r4, r5, r6, pc}
_02243518:
	ldrh r0, [r4, #6]
	pop {r4, r5, r6, pc}
_0224351C:
	ldrh r0, [r4, #8]
	pop {r4, r5, r6, pc}
_02243520:
	ldrh r0, [r4, #0xa]
	pop {r4, r5, r6, pc}
_02243524:
	sub r0, r2, #6
	lsl r0, r0, #1
	add r0, r4, r0
	ldrh r0, [r0, #0xc]
	pop {r4, r5, r6, pc}
_0224352E:
	ldr r0, [r4, #0x14]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1b
	pop {r4, r5, r6, pc}
_02243536:
	ldr r0, [r4, #0x14]
	lsl r0, r0, #0x16
	lsr r0, r0, #0x1b
	pop {r4, r5, r6, pc}
_0224353E:
	ldr r0, [r4, #0x14]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1b
	pop {r4, r5, r6, pc}
_02243546:
	ldr r0, [r4, #0x14]
	lsl r0, r0, #0xc
	lsr r0, r0, #0x1b
	pop {r4, r5, r6, pc}
_0224354E:
	ldr r0, [r4, #0x14]
	lsl r0, r0, #7
	lsr r0, r0, #0x1b
	pop {r4, r5, r6, pc}
_02243556:
	ldr r0, [r4, #0x14]
	lsl r0, r0, #2
	lsr r0, r0, #0x1b
	pop {r4, r5, r6, pc}
_0224355E:
	ldr r0, [r4, #0x14]
	lsl r0, r0, #1
	lsr r0, r0, #0x1f
	pop {r4, r5, r6, pc}
_02243566:
	ldr r0, [r4, #0x14]
	lsr r0, r0, #0x1f
	pop {r4, r5, r6, pc}
_0224356C:
	sub r2, #0x12
	add r1, r4, r2
	mov r0, #0x18
	ldrsb r0, [r1, r0]
	pop {r4, r5, r6, pc}
_02243576:
	add r4, #0x27
	ldrb r0, [r4]
	pop {r4, r5, r6, pc}
_0224357C:
	bl MOD11_0224C740
	pop {r4, r5, r6, pc}
_02243582:
	add r4, #0x7e
	ldrb r0, [r4]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	pop {r4, r5, r6, pc}
_0224358C:
	add r4, #0x26
	ldrb r0, [r4]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1f
	pop {r4, r5, r6, pc}
_02243596:
	sub r2, #0x1f
	add r0, r4, r2
	add r0, #0x2c
	ldrb r0, [r0]
	pop {r4, r5, r6, pc}
_022435A0:
	sub r2, #0x23
	add r0, r4, r2
	add r0, #0x30
	ldrb r0, [r0]
	pop {r4, r5, r6, pc}
_022435AA:
	sub r2, #0x27
	lsl r0, r2, #1
	add r1, r4, r2
	add r0, r4, r0
	add r1, #0x30
	ldrh r0, [r0, #0xc]
	ldrb r1, [r1]
	bl WazaGetMaxPp
	pop {r4, r5, r6, pc}
_022435BE:
	add r4, #0x34
	ldrb r0, [r4]
	pop {r4, r5, r6, pc}
_022435C4:
	add r4, #0x35
	ldrb r0, [r4]
	pop {r4, r5, r6, pc}
_022435CA:
	mov r1, #0
_022435CC:
	ldrh r0, [r4, #0x36]
	add r1, r1, #1
	add r4, r4, #2
	strh r0, [r3]
	add r3, r3, #2
	cmp r1, #0xb
	blt _022435CC
	b _02243798
_022435DC:
	add r4, #0x36
	add r0, r3, #0
	add r1, r4, #0
	bl CopyU16ArrayToString
	b _02243798
_022435E8:
	ldr r0, [r4, #0x4c]
	pop {r4, r5, r6, pc}
_022435EC:
	ldr r0, [r4, #0x50]
	pop {r4, r5, r6, pc}
_022435F0:
	mov r1, #0
_022435F2:
	add r0, r4, #0
	add r0, #0x54
	ldrh r0, [r0]
	add r1, r1, #1
	add r4, r4, #2
	strh r0, [r3]
	add r3, r3, #2
	cmp r1, #0xb
	blt _022435F2
	b _02243798
_02243606:
	ldr r0, [r4, #0x64]
	pop {r4, r5, r6, pc}
_0224360A:
	ldr r0, [r4, #0x68]
	pop {r4, r5, r6, pc}
_0224360E:
	ldr r0, [r4, #0x6c]
	pop {r4, r5, r6, pc}
_02243612:
	ldr r0, [r4, #0x70]
	pop {r4, r5, r6, pc}
_02243616:
	ldr r0, [r4, #0x74]
	pop {r4, r5, r6, pc}
_0224361A:
	add r4, #0x78
	ldrh r0, [r4]
	pop {r4, r5, r6, pc}
_02243620:
	add r4, #0x7c
	ldrb r0, [r4]
	pop {r4, r5, r6, pc}
_02243626:
	add r4, #0x7d
	ldrb r0, [r4]
	pop {r4, r5, r6, pc}
_0224362C:
	add r4, #0x7e
	ldrb r0, [r4]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	pop {r4, r5, r6, pc}
_02243636:
	add r4, #0x80
	ldr r0, [r4]
	pop {r4, r5, r6, pc}
_0224363C:
	add r4, #0x84
	ldr r0, [r4]
	pop {r4, r5, r6, pc}
_02243642:
	add r4, #0x88
	ldr r0, [r4]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1d
	pop {r4, r5, r6, pc}
_0224364C:
	add r4, #0x88
	ldr r0, [r4]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1d
	pop {r4, r5, r6, pc}
_02243656:
	add r4, #0x88
	ldr r0, [r4]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1e
	pop {r4, r5, r6, pc}
_02243660:
	add r4, #0x88
	ldr r0, [r4]
	lsl r0, r0, #0x15
	lsr r0, r0, #0x1d
	pop {r4, r5, r6, pc}
_0224366A:
	add r4, #0x88
	ldr r0, [r4]
	lsl r0, r0, #0x13
	lsr r0, r0, #0x1e
	pop {r4, r5, r6, pc}
_02243674:
	add r4, #0x88
	ldr r0, [r4]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1e
	pop {r4, r5, r6, pc}
_0224367E:
	add r4, #0x88
	ldr r0, [r4]
	lsl r0, r0, #0xe
	lsr r0, r0, #0x1d
	pop {r4, r5, r6, pc}
_02243688:
	add r4, #0x88
	ldr r0, [r4]
	lsl r0, r0, #0xb
	lsr r0, r0, #0x1d
	pop {r4, r5, r6, pc}
_02243692:
	add r4, #0x88
	ldr r0, [r4]
	lsl r0, r0, #8
	lsr r0, r0, #0x1d
	pop {r4, r5, r6, pc}
_0224369C:
	add r4, #0x88
	ldr r0, [r4]
	lsl r0, r0, #5
	lsr r0, r0, #0x1d
	pop {r4, r5, r6, pc}
_022436A6:
	add r4, #0x88
	ldr r0, [r4]
	lsl r0, r0, #2
	lsr r0, r0, #0x1d
	pop {r4, r5, r6, pc}
_022436B0:
	add r4, #0x88
	ldr r0, [r4]
	lsl r0, r0, #1
	lsr r0, r0, #0x1f
	pop {r4, r5, r6, pc}
_022436BA:
	add r4, #0x88
	ldr r0, [r4]
	lsr r0, r0, #0x1f
	pop {r4, r5, r6, pc}
_022436C2:
	add r4, #0x8c
	ldr r0, [r4]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1e
	pop {r4, r5, r6, pc}
_022436CC:
	add r4, #0x8c
	ldr r0, [r4]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1c
	pop {r4, r5, r6, pc}
_022436D6:
	add r4, #0x8c
	ldr r0, [r4]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1e
	pop {r4, r5, r6, pc}
_022436E0:
	add r4, #0x8c
	ldr r0, [r4]
	lsl r0, r0, #0x16
	lsr r0, r0, #0x1e
	pop {r4, r5, r6, pc}
_022436EA:
	add r4, #0x8c
	ldr r0, [r4]
	lsl r0, r0, #0x13
	lsr r0, r0, #0x1d
	pop {r4, r5, r6, pc}
_022436F4:
	add r4, #0x8c
	ldr r0, [r4]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x1d
	pop {r4, r5, r6, pc}
_022436FE:
	add r4, #0x8c
	ldr r0, [r4]
	lsl r0, r0, #0xd
	lsr r0, r0, #0x1d
	pop {r4, r5, r6, pc}
_02243708:
	add r4, #0x8c
	ldr r0, [r4]
	lsl r0, r0, #0xa
	lsr r0, r0, #0x1d
	pop {r4, r5, r6, pc}
_02243712:
	add r4, #0x8c
	ldr r0, [r4]
	lsl r0, r0, #9
	lsr r0, r0, #0x1f
	pop {r4, r5, r6, pc}
_0224371C:
	add r4, #0x8c
	ldr r0, [r4]
	lsl r0, r0, #5
	lsr r0, r0, #0x1c
	pop {r4, r5, r6, pc}
_02243726:
	add r4, #0x8c
	ldr r0, [r4]
	lsl r0, r0, #4
	lsr r0, r0, #0x1f
	pop {r4, r5, r6, pc}
_02243730:
	add r4, #0x8c
	ldr r0, [r4]
	lsl r0, r0, #3
	lsr r0, r0, #0x1f
	pop {r4, r5, r6, pc}
_0224373A:
	add r4, #0x8c
	ldr r0, [r4]
	lsl r0, r0, #2
	lsr r0, r0, #0x1f
	pop {r4, r5, r6, pc}
_02243744:
	add r4, #0x90
	ldr r0, [r4]
	pop {r4, r5, r6, pc}
_0224374A:
	add r4, #0x94
	ldr r0, [r4]
	pop {r4, r5, r6, pc}
_02243750:
	add r4, #0x98
	ldr r0, [r4]
	pop {r4, r5, r6, pc}
_02243756:
	add r4, #0xa0
	ldr r0, [r4]
	pop {r4, r5, r6, pc}
_0224375C:
	add r4, #0xa4
	ldr r0, [r4]
	pop {r4, r5, r6, pc}
_02243762:
	add r4, #0xa8
	ldrh r0, [r4]
	pop {r4, r5, r6, pc}
_02243768:
	add r4, #0xac
	ldrh r0, [r4]
	pop {r4, r5, r6, pc}
_0224376E:
	add r4, #0xaa
	ldrh r0, [r4]
	pop {r4, r5, r6, pc}
_02243774:
	add r4, #0xbc
	ldr r0, [r4]
	pop {r4, r5, r6, pc}
_0224377A:
	ldr r0, [r4, #0x28]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	pop {r4, r5, r6, pc}
_02243782:
	ldr r0, [r4, #0x28]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	pop {r4, r5, r6, pc}
_0224378A:
	add r6, #0x78
	ldr r2, [r0, r6]
	bl MOD11_02243420
	pop {r4, r5, r6, pc}
_02243794:
	bl GF_AssertFail
_02243798:
	mov r0, #0
	pop {r4, r5, r6, pc}

	thumb_func_start MOD11_0224379C
MOD11_0224379C: ; 0x0224379C
	push {r4, r5, r6, lr}
	add r5, r2, #0
	mov r2, #0xb5
	lsl r2, r2, #6
	add r4, r0, r2
	mov r6, #0xc0
	add r2, r1, #0
	mul r2, r6
	add r2, r4, r2
	cmp r5, #0x64
	bls _022437B4
	b _02243D9E
_022437B4:
	add r4, r5, r5
	add r4, pc
	ldrh r4, [r4, #6]
	lsl r4, r4, #0x10
	asr r4, r4, #0x10
	add pc, r4
_022437C0: ; jump table
	.short _0224388A - _022437C0 - 2 ; case 0
	.short _02243890 - _022437C0 - 2 ; case 1
	.short _02243896 - _022437C0 - 2 ; case 2
	.short _0224389C - _022437C0 - 2 ; case 3
	.short _022438A2 - _022437C0 - 2 ; case 4
	.short _022438A8 - _022437C0 - 2 ; case 5
	.short _022438AE - _022437C0 - 2 ; case 6
	.short _022438AE - _022437C0 - 2 ; case 7
	.short _022438AE - _022437C0 - 2 ; case 8
	.short _022438AE - _022437C0 - 2 ; case 9
	.short _022438BA - _022437C0 - 2 ; case 10
	.short _022438CC - _022437C0 - 2 ; case 11
	.short _022438DE - _022437C0 - 2 ; case 12
	.short _022438F0 - _022437C0 - 2 ; case 13
	.short _02243902 - _022437C0 - 2 ; case 14
	.short _02243914 - _022437C0 - 2 ; case 15
	.short _02243926 - _022437C0 - 2 ; case 16
	.short _02243938 - _022437C0 - 2 ; case 17
	.short _02243948 - _022437C0 - 2 ; case 18
	.short _02243948 - _022437C0 - 2 ; case 19
	.short _02243948 - _022437C0 - 2 ; case 20
	.short _02243948 - _022437C0 - 2 ; case 21
	.short _02243948 - _022437C0 - 2 ; case 22
	.short _02243948 - _022437C0 - 2 ; case 23
	.short _02243948 - _022437C0 - 2 ; case 24
	.short _02243948 - _022437C0 - 2 ; case 25
	.short _02243954 - _022437C0 - 2 ; case 26
	.short _0224395C - _022437C0 - 2 ; case 27
	.short _02243964 - _022437C0 - 2 ; case 28
	.short _0224396C - _022437C0 - 2 ; case 29
	.short _02243984 - _022437C0 - 2 ; case 30
	.short _0224399C - _022437C0 - 2 ; case 31
	.short _0224399C - _022437C0 - 2 ; case 32
	.short _0224399C - _022437C0 - 2 ; case 33
	.short _0224399C - _022437C0 - 2 ; case 34
	.short _022439A8 - _022437C0 - 2 ; case 35
	.short _022439A8 - _022437C0 - 2 ; case 36
	.short _022439A8 - _022437C0 - 2 ; case 37
	.short _022439A8 - _022437C0 - 2 ; case 38
	.short _022439B4 - _022437C0 - 2 ; case 39
	.short _022439B4 - _022437C0 - 2 ; case 40
	.short _022439B4 - _022437C0 - 2 ; case 41
	.short _022439B4 - _022437C0 - 2 ; case 42
	.short _022439BA - _022437C0 - 2 ; case 43
	.short _022439C2 - _022437C0 - 2 ; case 44
	.short _022439CA - _022437C0 - 2 ; case 45
	.short _02243D9E - _022437C0 - 2 ; case 46
	.short _022439DC - _022437C0 - 2 ; case 47
	.short _022439E4 - _022437C0 - 2 ; case 48
	.short _022439EA - _022437C0 - 2 ; case 49
	.short _02243A00 - _022437C0 - 2 ; case 50
	.short _02243A06 - _022437C0 - 2 ; case 51
	.short _02243A0C - _022437C0 - 2 ; case 52
	.short _02243A12 - _022437C0 - 2 ; case 53
	.short _02243A18 - _022437C0 - 2 ; case 54
	.short _02243A1E - _022437C0 - 2 ; case 55
	.short _02243A26 - _022437C0 - 2 ; case 56
	.short _02243A2E - _022437C0 - 2 ; case 57
	.short _02243A36 - _022437C0 - 2 ; case 58
	.short _02243A4E - _022437C0 - 2 ; case 59
	.short _02243A56 - _022437C0 - 2 ; case 60
	.short _02243A5E - _022437C0 - 2 ; case 61
	.short _02243A76 - _022437C0 - 2 ; case 62
	.short _02243A8E - _022437C0 - 2 ; case 63
	.short _02243AA6 - _022437C0 - 2 ; case 64
	.short _02243ABE - _022437C0 - 2 ; case 65
	.short _02243AD6 - _022437C0 - 2 ; case 66
	.short _02243AEE - _022437C0 - 2 ; case 67
	.short _02243B06 - _022437C0 - 2 ; case 68
	.short _02243B1E - _022437C0 - 2 ; case 69
	.short _02243B36 - _022437C0 - 2 ; case 70
	.short _02243B4E - _022437C0 - 2 ; case 71
	.short _02243B66 - _022437C0 - 2 ; case 72
	.short _02243B7E - _022437C0 - 2 ; case 73
	.short _02243B94 - _022437C0 - 2 ; case 74
	.short _02243BAC - _022437C0 - 2 ; case 75
	.short _02243BC4 - _022437C0 - 2 ; case 76
	.short _02243BDC - _022437C0 - 2 ; case 77
	.short _02243BF4 - _022437C0 - 2 ; case 78
	.short _02243C0C - _022437C0 - 2 ; case 79
	.short _02243C24 - _022437C0 - 2 ; case 80
	.short _02243C3C - _022437C0 - 2 ; case 81
	.short _02243C54 - _022437C0 - 2 ; case 82
	.short _02243C6C - _022437C0 - 2 ; case 83
	.short _02243CE0 - _022437C0 - 2 ; case 84
	.short _02243CF8 - _022437C0 - 2 ; case 85
	.short _02243D10 - _022437C0 - 2 ; case 86
	.short _02243D28 - _022437C0 - 2 ; case 87
	.short _02243D30 - _022437C0 - 2 ; case 88
	.short _02243D38 - _022437C0 - 2 ; case 89
	.short _02243D40 - _022437C0 - 2 ; case 90
	.short _02243D48 - _022437C0 - 2 ; case 91
	.short _02243D50 - _022437C0 - 2 ; case 92
	.short _02243D58 - _022437C0 - 2 ; case 93
	.short _02243D60 - _022437C0 - 2 ; case 94
	.short _02243D68 - _022437C0 - 2 ; case 95
	.short _02243D70 - _022437C0 - 2 ; case 96
	.short _02243D82 - _022437C0 - 2 ; case 97
	.short _02243D9E - _022437C0 - 2 ; case 98
	.short _02243D9E - _022437C0 - 2 ; case 99
	.short _02243D94 - _022437C0 - 2 ; case 100
_0224388A:
	ldrh r0, [r3]
	strh r0, [r2]
	pop {r4, r5, r6, pc}
_02243890:
	ldrh r0, [r3]
	strh r0, [r2, #2]
	pop {r4, r5, r6, pc}
_02243896:
	ldrh r0, [r3]
	strh r0, [r2, #4]
	pop {r4, r5, r6, pc}
_0224389C:
	ldrh r0, [r3]
	strh r0, [r2, #6]
	pop {r4, r5, r6, pc}
_022438A2:
	ldrh r0, [r3]
	strh r0, [r2, #8]
	pop {r4, r5, r6, pc}
_022438A8:
	ldrh r0, [r3]
	strh r0, [r2, #0xa]
	pop {r4, r5, r6, pc}
_022438AE:
	sub r0, r5, #6
	lsl r0, r0, #1
	ldrh r1, [r3]
	add r0, r2, r0
	strh r1, [r0, #0xc]
	pop {r4, r5, r6, pc}
_022438BA:
	ldr r4, [r2, #0x14]
	mov r0, #0x1f
	bic r4, r0
	ldrb r1, [r3]
	mov r0, #0x1f
	and r0, r1
	orr r0, r4
	str r0, [r2, #0x14]
	pop {r4, r5, r6, pc}
_022438CC:
	ldr r1, [r2, #0x14]
	ldr r0, _02243C78 ; =0xFFFFFC1F
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x16
	orr r0, r1
	str r0, [r2, #0x14]
	pop {r4, r5, r6, pc}
_022438DE:
	ldr r1, [r2, #0x14]
	ldr r0, _02243C7C ; =0xFFFF83FF
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x11
	orr r0, r1
	str r0, [r2, #0x14]
	pop {r4, r5, r6, pc}
_022438F0:
	ldr r1, [r2, #0x14]
	ldr r0, _02243C80 ; =0xFFF07FFF
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0xc
	orr r0, r1
	str r0, [r2, #0x14]
	pop {r4, r5, r6, pc}
_02243902:
	ldr r1, [r2, #0x14]
	ldr r0, _02243C84 ; =0xFE0FFFFF
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1b
	lsr r0, r0, #7
	orr r0, r1
	str r0, [r2, #0x14]
	pop {r4, r5, r6, pc}
_02243914:
	ldr r1, [r2, #0x14]
	ldr r0, _02243C88 ; =0xC1FFFFFF
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1b
	lsr r0, r0, #2
	orr r0, r1
	str r0, [r2, #0x14]
	pop {r4, r5, r6, pc}
_02243926:
	ldr r1, [r2, #0x14]
	ldr r0, _02243C8C ; =0xBFFFFFFF
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1f
	lsr r0, r0, #1
	orr r0, r1
	str r0, [r2, #0x14]
	pop {r4, r5, r6, pc}
_02243938:
	ldr r1, [r2, #0x14]
	ldr r0, _02243C90 ; =0x7FFFFFFF
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1f
	orr r0, r1
	str r0, [r2, #0x14]
	pop {r4, r5, r6, pc}
_02243948:
	mov r0, #0
	ldrsb r1, [r3, r0]
	sub r5, #0x12
	add r0, r2, r5
	strb r1, [r0, #0x18]
	pop {r4, r5, r6, pc}
_02243954:
	ldrb r0, [r3]
	add r2, #0x27
	strb r0, [r2]
	pop {r4, r5, r6, pc}
_0224395C:
	ldrb r0, [r3]
	add r2, #0x24
	strb r0, [r2]
	pop {r4, r5, r6, pc}
_02243964:
	ldrb r0, [r3]
	add r2, #0x25
	strb r0, [r2]
	pop {r4, r5, r6, pc}
_0224396C:
	add r0, r2, #0
	add r0, #0x7e
	ldrb r4, [r0]
	ldrb r1, [r3]
	mov r0, #0xf
	bic r4, r0
	mov r0, #0xf
	and r0, r1
	orr r0, r4
	add r2, #0x7e
	strb r0, [r2]
	pop {r4, r5, r6, pc}
_02243984:
	add r0, r2, #0
	add r0, #0x26
	ldrb r1, [r0]
	mov r0, #0x20
	add r2, #0x26
	bic r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1a
	orr r0, r1
	strb r0, [r2]
	pop {r4, r5, r6, pc}
_0224399C:
	sub r5, #0x1f
	add r0, r2, r5
	ldrb r1, [r3]
	add r0, #0x2c
	strb r1, [r0]
	pop {r4, r5, r6, pc}
_022439A8:
	sub r5, #0x23
	add r0, r2, r5
	ldrb r1, [r3]
	add r0, #0x30
	strb r1, [r0]
	pop {r4, r5, r6, pc}
_022439B4:
	bl GF_AssertFail
	pop {r4, r5, r6, pc}
_022439BA:
	ldrb r0, [r3]
	add r2, #0x34
	strb r0, [r2]
	pop {r4, r5, r6, pc}
_022439C2:
	ldrb r0, [r3]
	add r2, #0x35
	strb r0, [r2]
	pop {r4, r5, r6, pc}
_022439CA:
	mov r1, #0
_022439CC:
	ldrh r0, [r3]
	add r1, r1, #1
	add r3, r3, #2
	strh r0, [r2, #0x36]
	add r2, r2, #2
	cmp r1, #0xb
	blt _022439CC
	pop {r4, r5, r6, pc}
_022439DC:
	mov r0, #0
	ldrsh r0, [r3, r0]
	str r0, [r2, #0x4c]
	pop {r4, r5, r6, pc}
_022439E4:
	ldrh r0, [r3]
	str r0, [r2, #0x50]
	pop {r4, r5, r6, pc}
_022439EA:
	mov r4, #0
_022439EC:
	ldrh r1, [r3]
	add r0, r2, #0
	add r0, #0x54
	add r4, r4, #1
	strh r1, [r0]
	add r3, r3, #2
	add r2, r2, #2
	cmp r4, #0xb
	blt _022439EC
	pop {r4, r5, r6, pc}
_02243A00:
	ldr r0, [r3]
	str r0, [r2, #0x64]
	pop {r4, r5, r6, pc}
_02243A06:
	ldr r0, [r3]
	str r0, [r2, #0x68]
	pop {r4, r5, r6, pc}
_02243A0C:
	ldr r0, [r3]
	str r0, [r2, #0x6c]
	pop {r4, r5, r6, pc}
_02243A12:
	ldr r0, [r3]
	str r0, [r2, #0x70]
	pop {r4, r5, r6, pc}
_02243A18:
	ldr r0, [r3]
	str r0, [r2, #0x74]
	pop {r4, r5, r6, pc}
_02243A1E:
	ldrh r0, [r3]
	add r2, #0x78
	strh r0, [r2]
	pop {r4, r5, r6, pc}
_02243A26:
	ldrb r0, [r3]
	add r2, #0x7c
	strb r0, [r2]
	pop {r4, r5, r6, pc}
_02243A2E:
	ldrb r0, [r3]
	add r2, #0x7d
	strb r0, [r2]
	pop {r4, r5, r6, pc}
_02243A36:
	add r0, r2, #0
	add r0, #0x7e
	ldrb r1, [r0]
	mov r0, #0xf0
	add r2, #0x7e
	bic r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x18
	orr r0, r1
	strb r0, [r2]
	pop {r4, r5, r6, pc}
_02243A4E:
	ldr r0, [r3]
	add r2, #0x80
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243A56:
	ldr r0, [r3]
	add r2, #0x84
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243A5E:
	add r0, r2, #0
	add r0, #0x88
	ldr r4, [r0]
	mov r0, #7
	bic r4, r0
	ldrb r1, [r3]
	mov r0, #7
	add r2, #0x88
	and r0, r1
	orr r0, r4
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243A76:
	add r0, r2, #0
	add r0, #0x88
	ldr r1, [r0]
	mov r0, #0x38
	bic r1, r0
	ldrb r0, [r3]
	add r2, #0x88
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1a
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243A8E:
	add r0, r2, #0
	add r0, #0x88
	ldr r1, [r0]
	mov r0, #0xc0
	bic r1, r0
	ldrb r0, [r3]
	add r2, #0x88
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x18
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243AA6:
	add r0, r2, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _02243C94 ; =0xFFFFF8FF
	add r2, #0x88
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x15
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243ABE:
	add r0, r2, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _02243C98 ; =0xFFFFE7FF
	add r2, #0x88
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x13
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243AD6:
	add r0, r2, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _02243C9C ; =0xFFFF9FFF
	add r2, #0x88
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x11
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243AEE:
	add r0, r2, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _02243CA0 ; =0xFFFC7FFF
	add r2, #0x88
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0xe
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243B06:
	add r0, r2, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _02243CA4 ; =0xFFE3FFFF
	add r2, #0x88
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0xb
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243B1E:
	add r0, r2, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _02243CA8 ; =0xFF1FFFFF
	add r2, #0x88
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1d
	lsr r0, r0, #8
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243B36:
	add r0, r2, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _02243CAC ; =0xF8FFFFFF
	add r2, #0x88
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1d
	lsr r0, r0, #5
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243B4E:
	add r0, r2, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _02243CB0 ; =0xC7FFFFFF
	add r2, #0x88
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1d
	lsr r0, r0, #2
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243B66:
	add r0, r2, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _02243C8C ; =0xBFFFFFFF
	add r2, #0x88
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1f
	lsr r0, r0, #1
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243B7E:
	add r0, r2, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _02243C90 ; =0x7FFFFFFF
	add r2, #0x88
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1f
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243B94:
	add r0, r2, #0
	add r0, #0x8c
	ldr r4, [r0]
	mov r0, #3
	bic r4, r0
	ldrb r1, [r3]
	mov r0, #3
	add r2, #0x8c
	and r0, r1
	orr r0, r4
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243BAC:
	add r0, r2, #0
	add r0, #0x8c
	ldr r1, [r0]
	mov r0, #0x3c
	bic r1, r0
	ldrb r0, [r3]
	add r2, #0x8c
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1a
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243BC4:
	add r0, r2, #0
	add r0, #0x8c
	ldr r1, [r0]
	mov r0, #0xc0
	bic r1, r0
	ldrb r0, [r3]
	add r2, #0x8c
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x18
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243BDC:
	add r0, r2, #0
	add r0, #0x8c
	ldr r1, [r0]
	ldr r0, _02243CB4 ; =0xFFFFFCFF
	add r2, #0x8c
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x16
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243BF4:
	add r0, r2, #0
	add r0, #0x8c
	ldr r1, [r0]
	ldr r0, _02243CB8 ; =0xFFFFE3FF
	add r2, #0x8c
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x13
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243C0C:
	add r0, r2, #0
	add r0, #0x8c
	ldr r1, [r0]
	ldr r0, _02243CBC ; =0xFFFF1FFF
	add r2, #0x8c
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x10
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243C24:
	add r0, r2, #0
	add r0, #0x8c
	ldr r1, [r0]
	ldr r0, _02243CC0 ; =0xFFF8FFFF
	add r2, #0x8c
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0xd
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243C3C:
	add r0, r2, #0
	add r0, #0x8c
	ldr r1, [r0]
	ldr r0, _02243CC4 ; =0xFFC7FFFF
	add r2, #0x8c
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0xa
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243C54:
	add r0, r2, #0
	add r0, #0x8c
	ldr r1, [r0]
	ldr r0, _02243CC8 ; =0xFFBFFFFF
	add r2, #0x8c
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1f
	lsr r0, r0, #9
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243C6C:
	add r0, r2, #0
	add r0, #0x8c
	ldr r1, [r0]
	ldr r0, _02243CCC ; =0xF87FFFFF
	b _02243CD0
	nop
_02243C78: .word 0xFFFFFC1F
_02243C7C: .word 0xFFFF83FF
_02243C80: .word 0xFFF07FFF
_02243C84: .word 0xFE0FFFFF
_02243C88: .word 0xC1FFFFFF
_02243C8C: .word 0xBFFFFFFF
_02243C90: .word 0x7FFFFFFF
_02243C94: .word 0xFFFFF8FF
_02243C98: .word 0xFFFFE7FF
_02243C9C: .word 0xFFFF9FFF
_02243CA0: .word 0xFFFC7FFF
_02243CA4: .word 0xFFE3FFFF
_02243CA8: .word 0xFF1FFFFF
_02243CAC: .word 0xF8FFFFFF
_02243CB0: .word 0xC7FFFFFF
_02243CB4: .word 0xFFFFFCFF
_02243CB8: .word 0xFFFFE3FF
_02243CBC: .word 0xFFFF1FFF
_02243CC0: .word 0xFFF8FFFF
_02243CC4: .word 0xFFC7FFFF
_02243CC8: .word 0xFFBFFFFF
_02243CCC: .word 0xF87FFFFF
_02243CD0:
	add r2, #0x8c
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1c
	lsr r0, r0, #5
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243CE0:
	add r0, r2, #0
	add r0, #0x8c
	ldr r1, [r0]
	ldr r0, _02243DA4 ; =0xF7FFFFFF
	add r2, #0x8c
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1f
	lsr r0, r0, #4
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243CF8:
	add r0, r2, #0
	add r0, #0x8c
	ldr r1, [r0]
	ldr r0, _02243DA8 ; =0xEFFFFFFF
	add r2, #0x8c
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1f
	lsr r0, r0, #3
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243D10:
	add r0, r2, #0
	add r0, #0x8c
	ldr r1, [r0]
	ldr r0, _02243DAC ; =0xDFFFFFFF
	add r2, #0x8c
	and r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1f
	lsr r0, r0, #2
	orr r0, r1
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243D28:
	ldr r0, [r3]
	add r2, #0x90
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243D30:
	ldr r0, [r3]
	add r2, #0x94
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243D38:
	ldr r0, [r3]
	add r2, #0x98
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243D40:
	ldr r0, [r3]
	add r2, #0xa0
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243D48:
	ldr r0, [r3]
	add r2, #0xa4
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243D50:
	ldrh r0, [r3]
	add r2, #0xa8
	strh r0, [r2]
	pop {r4, r5, r6, pc}
_02243D58:
	ldrh r0, [r3]
	add r2, #0xac
	strh r0, [r2]
	pop {r4, r5, r6, pc}
_02243D60:
	ldrh r0, [r3]
	add r2, #0xaa
	strh r0, [r2]
	pop {r4, r5, r6, pc}
_02243D68:
	ldr r0, [r3]
	add r2, #0xbc
	str r0, [r2]
	pop {r4, r5, r6, pc}
_02243D70:
	ldr r1, [r2, #0x28]
	mov r0, #0x40
	bic r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x19
	orr r0, r1
	str r0, [r2, #0x28]
	pop {r4, r5, r6, pc}
_02243D82:
	ldr r1, [r2, #0x28]
	mov r0, #0x80
	bic r1, r0
	ldrb r0, [r3]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x18
	orr r0, r1
	str r0, [r2, #0x28]
	pop {r4, r5, r6, pc}
_02243D94:
	add r6, #0x78
	ldr r2, [r0, r6]
	bl MOD11_0224379C
	pop {r4, r5, r6, pc}
_02243D9E:
	bl GF_AssertFail
	pop {r4, r5, r6, pc}
	.align 2, 0
_02243DA4: .word 0xF7FFFFFF
_02243DA8: .word 0xEFFFFFFF
_02243DAC: .word 0xDFFFFFFF

	thumb_func_start MOD11_02243DB0
MOD11_02243DB0: ; 0x02243DB0
	push {r4, lr}
	mov r4, #0xb5
	lsl r4, r4, #6
	add r4, r0, r4
	mov r0, #0xc0
	mul r0, r1
	add r1, r2, #0
	add r0, r4, r0
	add r2, r3, #0
	bl MOD11_02243DC8
	pop {r4, pc}

	thumb_func_start MOD11_02243DC8
MOD11_02243DC8: ; 0x02243DC8
	push {r4, r5, r6, lr}
	add r4, r0, #0
	add r5, r2, #0
	cmp r1, #0x61
	bls _02243DD4
	b _02244200
_02243DD4:
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02243DE0: ; jump table
	.short _02244200 - _02243DE0 - 2 ; case 0
	.short _02243EA4 - _02243DE0 - 2 ; case 1
	.short _02243EAC - _02243DE0 - 2 ; case 2
	.short _02243EB4 - _02243DE0 - 2 ; case 3
	.short _02243EBC - _02243DE0 - 2 ; case 4
	.short _02243EC4 - _02243DE0 - 2 ; case 5
	.short _02244200 - _02243DE0 - 2 ; case 6
	.short _02244200 - _02243DE0 - 2 ; case 7
	.short _02244200 - _02243DE0 - 2 ; case 8
	.short _02244200 - _02243DE0 - 2 ; case 9
	.short _02243ECC - _02243DE0 - 2 ; case 10
	.short _02243EE4 - _02243DE0 - 2 ; case 11
	.short _02243EFA - _02243DE0 - 2 ; case 12
	.short _02243F10 - _02243DE0 - 2 ; case 13
	.short _02243F26 - _02243DE0 - 2 ; case 14
	.short _02243F3C - _02243DE0 - 2 ; case 15
	.short _02244200 - _02243DE0 - 2 ; case 16
	.short _02244200 - _02243DE0 - 2 ; case 17
	.short _02243F52 - _02243DE0 - 2 ; case 18
	.short _02243F52 - _02243DE0 - 2 ; case 19
	.short _02243F52 - _02243DE0 - 2 ; case 20
	.short _02243F52 - _02243DE0 - 2 ; case 21
	.short _02243F52 - _02243DE0 - 2 ; case 22
	.short _02243F52 - _02243DE0 - 2 ; case 23
	.short _02243F52 - _02243DE0 - 2 ; case 24
	.short _02243F52 - _02243DE0 - 2 ; case 25
	.short _02244200 - _02243DE0 - 2 ; case 26
	.short _02244200 - _02243DE0 - 2 ; case 27
	.short _02244200 - _02243DE0 - 2 ; case 28
	.short _02244200 - _02243DE0 - 2 ; case 29
	.short _02244200 - _02243DE0 - 2 ; case 30
	.short _02243F70 - _02243DE0 - 2 ; case 31
	.short _02243F70 - _02243DE0 - 2 ; case 32
	.short _02243F70 - _02243DE0 - 2 ; case 33
	.short _02243F70 - _02243DE0 - 2 ; case 34
	.short _02243F96 - _02243DE0 - 2 ; case 35
	.short _02243F96 - _02243DE0 - 2 ; case 36
	.short _02243F96 - _02243DE0 - 2 ; case 37
	.short _02243F96 - _02243DE0 - 2 ; case 38
	.short _02244200 - _02243DE0 - 2 ; case 39
	.short _02244200 - _02243DE0 - 2 ; case 40
	.short _02244200 - _02243DE0 - 2 ; case 41
	.short _02244200 - _02243DE0 - 2 ; case 42
	.short _02243FA2 - _02243DE0 - 2 ; case 43
	.short _02243FB0 - _02243DE0 - 2 ; case 44
	.short _02244200 - _02243DE0 - 2 ; case 45
	.short _02244200 - _02243DE0 - 2 ; case 46
	.short _02243FD2 - _02243DE0 - 2 ; case 47
	.short _02243FE4 - _02243DE0 - 2 ; case 48
	.short _02244200 - _02243DE0 - 2 ; case 49
	.short _02243FEC - _02243DE0 - 2 ; case 50
	.short _02243FF4 - _02243DE0 - 2 ; case 51
	.short _02244200 - _02243DE0 - 2 ; case 52
	.short _02244200 - _02243DE0 - 2 ; case 53
	.short _02244200 - _02243DE0 - 2 ; case 54
	.short _02244200 - _02243DE0 - 2 ; case 55
	.short _02244200 - _02243DE0 - 2 ; case 56
	.short _02244200 - _02243DE0 - 2 ; case 57
	.short _02244200 - _02243DE0 - 2 ; case 58
	.short _02244200 - _02243DE0 - 2 ; case 59
	.short _02244200 - _02243DE0 - 2 ; case 60
	.short _02243FFC - _02243DE0 - 2 ; case 61
	.short _0224401A - _02243DE0 - 2 ; case 62
	.short _02244038 - _02243DE0 - 2 ; case 63
	.short _02244056 - _02243DE0 - 2 ; case 64
	.short _02244072 - _02243DE0 - 2 ; case 65
	.short _0224408E - _02243DE0 - 2 ; case 66
	.short _022440AA - _02243DE0 - 2 ; case 67
	.short _022440C6 - _02243DE0 - 2 ; case 68
	.short _022440E2 - _02243DE0 - 2 ; case 69
	.short _022440FE - _02243DE0 - 2 ; case 70
	.short _0224411A - _02243DE0 - 2 ; case 71
	.short _02244200 - _02243DE0 - 2 ; case 72
	.short _02244200 - _02243DE0 - 2 ; case 73
	.short _02244200 - _02243DE0 - 2 ; case 74
	.short _02244200 - _02243DE0 - 2 ; case 75
	.short _02244200 - _02243DE0 - 2 ; case 76
	.short _02244200 - _02243DE0 - 2 ; case 77
	.short _02244136 - _02243DE0 - 2 ; case 78
	.short _02244152 - _02243DE0 - 2 ; case 79
	.short _0224416E - _02243DE0 - 2 ; case 80
	.short _02244200 - _02243DE0 - 2 ; case 81
	.short _02244200 - _02243DE0 - 2 ; case 82
	.short _02244200 - _02243DE0 - 2 ; case 83
	.short _02244200 - _02243DE0 - 2 ; case 84
	.short _02244200 - _02243DE0 - 2 ; case 85
	.short _02244200 - _02243DE0 - 2 ; case 86
	.short _0224418A - _02243DE0 - 2 ; case 87
	.short _02244198 - _02243DE0 - 2 ; case 88
	.short _022441A6 - _02243DE0 - 2 ; case 89
	.short _022441B4 - _02243DE0 - 2 ; case 90
	.short _02244200 - _02243DE0 - 2 ; case 91
	.short _02244200 - _02243DE0 - 2 ; case 92
	.short _02244200 - _02243DE0 - 2 ; case 93
	.short _02244200 - _02243DE0 - 2 ; case 94
	.short _022441C2 - _02243DE0 - 2 ; case 95
	.short _022441D0 - _02243DE0 - 2 ; case 96
	.short _022441E8 - _02243DE0 - 2 ; case 97
_02243EA4:
	ldrh r0, [r4, #2]
	add r0, r0, r5
	strh r0, [r4, #2]
	pop {r4, r5, r6, pc}
_02243EAC:
	ldrh r0, [r4, #4]
	add r0, r0, r5
	strh r0, [r4, #4]
	pop {r4, r5, r6, pc}
_02243EB4:
	ldrh r0, [r4, #6]
	add r0, r0, r5
	strh r0, [r4, #6]
	pop {r4, r5, r6, pc}
_02243EBC:
	ldrh r0, [r4, #8]
	add r0, r0, r5
	strh r0, [r4, #8]
	pop {r4, r5, r6, pc}
_02243EC4:
	ldrh r0, [r4, #0xa]
	add r0, r0, r5
	strh r0, [r4, #0xa]
	pop {r4, r5, r6, pc}
_02243ECC:
	ldr r2, [r4, #0x14]
	mov r1, #0x1f
	add r0, r2, #0
	bic r0, r1
	lsl r1, r2, #0x1b
	lsr r1, r1, #0x1b
	add r2, r1, r5
	mov r1, #0x1f
	and r1, r2
	orr r0, r1
	str r0, [r4, #0x14]
	pop {r4, r5, r6, pc}
_02243EE4:
	ldr r1, [r4, #0x14]
	ldr r0, _02244208 ; =0xFFFFFC1F
	and r0, r1
	lsl r1, r1, #0x16
	lsr r1, r1, #0x1b
	add r1, r1, r5
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x16
	orr r0, r1
	str r0, [r4, #0x14]
	pop {r4, r5, r6, pc}
_02243EFA:
	ldr r1, [r4, #0x14]
	ldr r0, _0224420C ; =0xFFFF83FF
	and r0, r1
	lsl r1, r1, #0x11
	lsr r1, r1, #0x1b
	add r1, r1, r5
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x11
	orr r0, r1
	str r0, [r4, #0x14]
	pop {r4, r5, r6, pc}
_02243F10:
	ldr r1, [r4, #0x14]
	ldr r0, _02244210 ; =0xFFF07FFF
	and r0, r1
	lsl r1, r1, #0xc
	lsr r1, r1, #0x1b
	add r1, r1, r5
	lsl r1, r1, #0x1b
	lsr r1, r1, #0xc
	orr r0, r1
	str r0, [r4, #0x14]
	pop {r4, r5, r6, pc}
_02243F26:
	ldr r1, [r4, #0x14]
	ldr r0, _02244214 ; =0xFE0FFFFF
	and r0, r1
	lsl r1, r1, #7
	lsr r1, r1, #0x1b
	add r1, r1, r5
	lsl r1, r1, #0x1b
	lsr r1, r1, #7
	orr r0, r1
	str r0, [r4, #0x14]
	pop {r4, r5, r6, pc}
_02243F3C:
	ldr r1, [r4, #0x14]
	ldr r0, _02244218 ; =0xC1FFFFFF
	and r0, r1
	lsl r1, r1, #2
	lsr r1, r1, #0x1b
	add r1, r1, r5
	lsl r1, r1, #0x1b
	lsr r1, r1, #2
	orr r0, r1
	str r0, [r4, #0x14]
	pop {r4, r5, r6, pc}
_02243F52:
	add r4, #0x18
	sub r1, #0x12
	ldrsb r0, [r4, r1]
	add r0, r5, r0
	bpl _02243F62
	mov r0, #0
	strb r0, [r4, r1]
	pop {r4, r5, r6, pc}
_02243F62:
	cmp r0, #0xc
	ble _02243F6C
	mov r0, #0xc
	strb r0, [r4, r1]
	pop {r4, r5, r6, pc}
_02243F6C:
	strb r0, [r4, r1]
	pop {r4, r5, r6, pc}
_02243F70:
	add r6, r1, #0
	sub r6, #0x1f
	lsl r0, r6, #1
	add r1, r4, r6
	add r0, r4, r0
	add r1, #0x30
	ldrh r0, [r0, #0xc]
	ldrb r1, [r1]
	bl WazaGetMaxPp
	add r4, #0x2c
	ldrb r1, [r4, r6]
	add r1, r5, r1
	cmp r1, r0
	ble _02243F92
	strb r0, [r4, r6]
	pop {r4, r5, r6, pc}
_02243F92:
	strb r1, [r4, r6]
	pop {r4, r5, r6, pc}
_02243F96:
	add r4, #0x30
	sub r1, #0x23
	ldrb r0, [r4, r1]
	add r0, r0, r5
	strb r0, [r4, r1]
	pop {r4, r5, r6, pc}
_02243FA2:
	add r0, r4, #0
	add r0, #0x34
	ldrb r0, [r0]
	add r4, #0x34
	add r0, r0, r5
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02243FB0:
	add r0, r4, #0
	add r0, #0x35
	ldrb r0, [r0]
	add r0, r0, r5
	cmp r0, #0xff
	ble _02243FC4
	mov r0, #0xff
	add r4, #0x35
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02243FC4:
	add r0, r4, #0
	add r0, #0x35
	ldrb r0, [r0]
	add r4, #0x35
	add r0, r0, r5
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02243FD2:
	ldr r0, [r4, #0x4c]
	ldr r1, [r4, #0x50]
	add r0, r0, r5
	cmp r0, r1
	bls _02243FE0
	str r1, [r4, #0x4c]
	pop {r4, r5, r6, pc}
_02243FE0:
	str r0, [r4, #0x4c]
	pop {r4, r5, r6, pc}
_02243FE4:
	ldr r0, [r4, #0x50]
	add r0, r0, r5
	str r0, [r4, #0x50]
	pop {r4, r5, r6, pc}
_02243FEC:
	ldr r0, [r4, #0x64]
	add r0, r0, r5
	str r0, [r4, #0x64]
	pop {r4, r5, r6, pc}
_02243FF4:
	ldr r0, [r4, #0x68]
	add r0, r0, r5
	str r0, [r4, #0x68]
	pop {r4, r5, r6, pc}
_02243FFC:
	add r0, r4, #0
	add r0, #0x88
	ldr r2, [r0]
	mov r1, #7
	add r0, r2, #0
	bic r0, r1
	lsl r1, r2, #0x1d
	lsr r1, r1, #0x1d
	add r2, r1, r5
	mov r1, #7
	and r1, r2
	orr r0, r1
	add r4, #0x88
	str r0, [r4]
	pop {r4, r5, r6, pc}
_0224401A:
	add r0, r4, #0
	add r0, #0x88
	ldr r2, [r0]
	mov r1, #0x38
	add r0, r2, #0
	bic r0, r1
	lsl r1, r2, #0x1a
	lsr r1, r1, #0x1d
	add r1, r1, r5
	lsl r1, r1, #0x1d
	lsr r1, r1, #0x1a
	orr r0, r1
	add r4, #0x88
	str r0, [r4]
	pop {r4, r5, r6, pc}
_02244038:
	add r0, r4, #0
	add r0, #0x88
	ldr r2, [r0]
	mov r1, #0xc0
	add r0, r2, #0
	bic r0, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x1e
	add r1, r1, r5
	lsl r1, r1, #0x1e
	lsr r1, r1, #0x18
	orr r0, r1
	add r4, #0x88
	str r0, [r4]
	pop {r4, r5, r6, pc}
_02244056:
	add r0, r4, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _0224421C ; =0xFFFFF8FF
	add r4, #0x88
	and r0, r1
	lsl r1, r1, #0x15
	lsr r1, r1, #0x1d
	add r1, r1, r5
	lsl r1, r1, #0x1d
	lsr r1, r1, #0x15
	orr r0, r1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_02244072:
	add r0, r4, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _02244220 ; =0xFFFFE7FF
	add r4, #0x88
	and r0, r1
	lsl r1, r1, #0x13
	lsr r1, r1, #0x1e
	add r1, r1, r5
	lsl r1, r1, #0x1e
	lsr r1, r1, #0x13
	orr r0, r1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_0224408E:
	add r0, r4, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _02244224 ; =0xFFFF9FFF
	add r4, #0x88
	and r0, r1
	lsl r1, r1, #0x11
	lsr r1, r1, #0x1e
	add r1, r1, r5
	lsl r1, r1, #0x1e
	lsr r1, r1, #0x11
	orr r0, r1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_022440AA:
	add r0, r4, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _02244228 ; =0xFFFC7FFF
	add r4, #0x88
	and r0, r1
	lsl r1, r1, #0xe
	lsr r1, r1, #0x1d
	add r1, r1, r5
	lsl r1, r1, #0x1d
	lsr r1, r1, #0xe
	orr r0, r1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_022440C6:
	add r0, r4, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _0224422C ; =0xFFE3FFFF
	add r4, #0x88
	and r0, r1
	lsl r1, r1, #0xb
	lsr r1, r1, #0x1d
	add r1, r1, r5
	lsl r1, r1, #0x1d
	lsr r1, r1, #0xb
	orr r0, r1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_022440E2:
	add r0, r4, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _02244230 ; =0xFF1FFFFF
	add r4, #0x88
	and r0, r1
	lsl r1, r1, #8
	lsr r1, r1, #0x1d
	add r1, r1, r5
	lsl r1, r1, #0x1d
	lsr r1, r1, #8
	orr r0, r1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_022440FE:
	add r0, r4, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _02244234 ; =0xF8FFFFFF
	add r4, #0x88
	and r0, r1
	lsl r1, r1, #5
	lsr r1, r1, #0x1d
	add r1, r1, r5
	lsl r1, r1, #0x1d
	lsr r1, r1, #5
	orr r0, r1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_0224411A:
	add r0, r4, #0
	add r0, #0x88
	ldr r1, [r0]
	ldr r0, _02244238 ; =0xC7FFFFFF
	add r4, #0x88
	and r0, r1
	lsl r1, r1, #2
	lsr r1, r1, #0x1d
	add r1, r1, r5
	lsl r1, r1, #0x1d
	lsr r1, r1, #2
	orr r0, r1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_02244136:
	add r0, r4, #0
	add r0, #0x8c
	ldr r1, [r0]
	ldr r0, _0224423C ; =0xFFFFE3FF
	add r4, #0x8c
	and r0, r1
	lsl r1, r1, #0x13
	lsr r1, r1, #0x1d
	add r1, r1, r5
	lsl r1, r1, #0x1d
	lsr r1, r1, #0x13
	orr r0, r1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_02244152:
	add r0, r4, #0
	add r0, #0x8c
	ldr r1, [r0]
	ldr r0, _02244240 ; =0xFFFF1FFF
	add r4, #0x8c
	and r0, r1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x1d
	add r1, r1, r5
	lsl r1, r1, #0x1d
	lsr r1, r1, #0x10
	orr r0, r1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_0224416E:
	add r0, r4, #0
	add r0, #0x8c
	ldr r1, [r0]
	ldr r0, _02244244 ; =0xFFF8FFFF
	add r4, #0x8c
	and r0, r1
	lsl r1, r1, #0xd
	lsr r1, r1, #0x1d
	add r1, r1, r5
	lsl r1, r1, #0x1d
	lsr r1, r1, #0xd
	orr r0, r1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_0224418A:
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	add r4, #0x90
	add r0, r0, r5
	str r0, [r4]
	pop {r4, r5, r6, pc}
_02244198:
	add r0, r4, #0
	add r0, #0x94
	ldr r0, [r0]
	add r4, #0x94
	add r0, r0, r5
	str r0, [r4]
	pop {r4, r5, r6, pc}
_022441A6:
	add r0, r4, #0
	add r0, #0x98
	ldr r0, [r0]
	add r4, #0x98
	add r0, r0, r5
	str r0, [r4]
	pop {r4, r5, r6, pc}
_022441B4:
	add r0, r4, #0
	add r0, #0xa0
	ldr r0, [r0]
	add r4, #0xa0
	add r0, r0, r5
	str r0, [r4]
	pop {r4, r5, r6, pc}
_022441C2:
	add r0, r4, #0
	add r0, #0xbc
	ldr r0, [r0]
	add r4, #0xbc
	add r0, r0, r5
	str r0, [r4]
	pop {r4, r5, r6, pc}
_022441D0:
	ldr r2, [r4, #0x28]
	mov r1, #0x40
	add r0, r2, #0
	bic r0, r1
	lsl r1, r2, #0x19
	lsr r1, r1, #0x1f
	add r1, r1, r5
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x19
	orr r0, r1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, pc}
_022441E8:
	ldr r2, [r4, #0x28]
	mov r1, #0x80
	add r0, r2, #0
	bic r0, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x1f
	add r1, r1, r5
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x18
	orr r0, r1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, pc}
_02244200:
	bl GF_AssertFail
	pop {r4, r5, r6, pc}
	nop
_02244208: .word 0xFFFFFC1F
_0224420C: .word 0xFFFF83FF
_02244210: .word 0xFFF07FFF
_02244214: .word 0xFE0FFFFF
_02244218: .word 0xC1FFFFFF
_0224421C: .word 0xFFFFF8FF
_02244220: .word 0xFFFFE7FF
_02244224: .word 0xFFFF9FFF
_02244228: .word 0xFFFC7FFF
_0224422C: .word 0xFFE3FFFF
_02244230: .word 0xFF1FFFFF
_02244234: .word 0xF8FFFFFF
_02244238: .word 0xC7FFFFFF
_0224423C: .word 0xFFFFE3FF
_02244240: .word 0xFFFF1FFF
_02244244: .word 0xFFF8FFFF

	thumb_func_start MOD11_02244248
MOD11_02244248: ; 0x02244248
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x68
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #0x64]
	str r0, [sp, #0x60]
	ldr r0, [sp, #0x64]
	str r2, [sp, #8]
	str r0, [sp, #0x5c]
	ldr r0, [sp, #0x64]
	str r3, [sp, #0xc]
	str r0, [sp, #0x48]
	ldr r0, [sp, #0x64]
	add r5, r1, #0
	str r0, [sp, #0x44]
	ldr r0, [sp, #0x64]
	mov r2, #0xc0
	str r0, [sp, #0x40]
	ldr r0, [sp, #0x64]
	ldr r3, _0224455C ; =0x00002D8C
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x64]
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x64]
	str r0, [sp, #0x34]
	ldr r0, [sp, #8]
	add r1, r0, #0
	mul r1, r2
	add r0, r5, r1
	ldr r0, [r0, r3]
	str r1, [sp, #0x18]
	cmp r0, #0
	bne _0224429C
	ldr r1, [sp, #0xc]
	mul r2, r1
	add r1, r5, r2
	ldr r1, [r1, r3]
	cmp r1, #0
	beq _0224429C
	add sp, #0x68
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0224429C:
	cmp r0, #0
	beq _022442B6
	ldr r0, [sp, #0xc]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _0224455C ; =0x00002D8C
	add r1, r5, r1
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _022442B6
	add sp, #0x68
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_022442B6:
	ldr r1, [sp, #8]
	add r0, r5, #0
	bl MOD11_02246D1C
	str r0, [sp, #0x2c]
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	bl MOD11_02246D1C
	str r0, [sp, #0x28]
	ldr r1, [sp, #8]
	add r0, r5, #0
	bl MOD11_02249D90
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x58]
	ldr r1, [sp, #8]
	add r0, r5, #0
	mov r2, #0
	bl MOD11_02249DA4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x54]
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	bl MOD11_02249D90
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x50]
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	mov r2, #0
	bl MOD11_02249DA4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x4c]
	ldr r0, [sp, #0x18]
	ldr r2, _02244560 ; =0x00002D5B
	add r0, r5, r0
	ldrsb r4, [r0, r2]
	ldr r0, [sp, #0xc]
	mov r1, #0xc0
	mul r1, r0
	add r0, r5, r1
	str r1, [sp, #0x14]
	ldrsb r7, [r0, r2]
	ldr r1, [sp, #8]
	add r0, r5, #0
	bl MOD11_02246D1C
	cmp r0, #0x56
	bne _02244338
	sub r0, r4, #6
	lsl r0, r0, #1
	add r4, r0, #6
	cmp r4, #0xc
	ble _02244332
	mov r4, #0xc
_02244332:
	cmp r4, #0
	bge _02244338
	mov r4, #0
_02244338:
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	bl MOD11_02246D1C
	cmp r0, #0x56
	bne _02244356
	sub r0, r7, #6
	lsl r0, r0, #1
	add r7, r0, #6
	cmp r7, #0xc
	ble _02244350
	mov r7, #0xc
_02244350:
	cmp r7, #0
	bge _02244356
	mov r7, #0
_02244356:
	ldr r0, [sp, #0x18]
	lsl r1, r4, #1
	add r2, r5, r0
	ldr r0, _02244564 ; =0x00002D46
	ldrh r2, [r2, r0]
	ldr r0, _02244568 ; =MOD11_0225E284
	ldrb r0, [r0, r1]
	mul r0, r2
	ldr r2, _0224456C ; =MOD11_0225E285
	ldrb r1, [r2, r1]
	bl _s32_div_f
	add r6, r0, #0
	ldr r0, [sp, #0x14]
	lsl r1, r7, #1
	add r2, r5, r0
	ldr r0, _02244564 ; =0x00002D46
	ldrh r2, [r2, r0]
	ldr r0, _02244568 ; =MOD11_0225E284
	ldrb r0, [r0, r1]
	mul r0, r2
	ldr r2, _0224456C ; =MOD11_0225E285
	ldrb r1, [r2, r1]
	bl _s32_div_f
	add r4, r0, #0
	mov r0, #0xd
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl MOD11_02246870
	cmp r0, #0
	bne _022443FE
	mov r0, #0x4c
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl MOD11_02246870
	cmp r0, #0
	bne _022443FE
	ldr r0, [sp, #0x2c]
	cmp r0, #0x21
	bne _022443C4
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #3
	tst r0, r1
	bne _022443D6
_022443C4:
	ldr r0, [sp, #0x2c]
	cmp r0, #0x22
	bne _022443D8
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #0x30
	tst r0, r1
	beq _022443D8
_022443D6:
	lsl r6, r6, #1
_022443D8:
	ldr r0, [sp, #0x28]
	cmp r0, #0x21
	bne _022443EA
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #3
	tst r0, r1
	bne _022443FC
_022443EA:
	ldr r0, [sp, #0x28]
	cmp r0, #0x22
	bne _022443FE
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #0x30
	tst r0, r1
	beq _022443FE
_022443FC:
	lsl r4, r4, #1
_022443FE:
	mov r0, #0
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x18]
	ldr r7, _02244570 ; =MOD11_0225E24C
	add r0, r5, r0
	str r0, [sp, #0x1c]
_0224440A:
	ldr r2, [sp, #0x1c]
	ldr r1, _02244574 ; =0x00002DB8
	add r0, r5, #0
	ldrh r1, [r2, r1]
	mov r2, #1
	bl MOD11_0224C12C
	ldrb r1, [r7]
	cmp r1, r0
	bne _02244422
	lsr r6, r6, #1
	b _0224442E
_02244422:
	ldr r0, [sp, #0x24]
	add r7, r7, #1
	add r0, r0, #1
	str r0, [sp, #0x24]
	cmp r0, #8
	blo _0224440A
_0224442E:
	ldr r0, [sp, #0x58]
	cmp r0, #0x72
	bne _02244440
	mov r0, #0xf
	mul r0, r6
	mov r1, #0xa
	bl _u32_div_f
	add r6, r0, #0
_02244440:
	ldr r0, [sp, #0x58]
	cmp r0, #0x65
	bne _02244456
	ldr r0, [sp, #0x18]
	add r1, r5, r0
	mov r0, #0xb5
	lsl r0, r0, #6
	ldrh r0, [r1, r0]
	cmp r0, #0x84
	bne _02244456
	lsl r6, r6, #1
_02244456:
	ldr r0, [sp, #0x2c]
	cmp r0, #0x5f
	bne _02244478
	ldr r0, [sp, #0x18]
	add r1, r5, r0
	ldr r0, _02244578 ; =0x00002DAC
	ldr r0, [r1, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	beq _02244478
	mov r0, #0xf
	mul r0, r6
	mov r1, #0xa
	bl _u32_div_f
	add r6, r0, #0
	b _02244488
_02244478:
	ldr r0, [sp, #0x18]
	add r1, r5, r0
	ldr r0, _02244578 ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #0x40
	tst r0, r1
	beq _02244488
	lsr r6, r6, #2
_02244488:
	ldr r0, [sp, #0x2c]
	cmp r0, #0x70
	bne _022444A4
	ldr r1, [sp, #0x18]
	mov r0, #0x15
	add r2, r5, r1
	ldr r1, _0224457C ; =0x00002DD8
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	ldr r1, [r2, r1]
	sub r0, r0, r1
	cmp r0, #5
	bge _022444A4
	lsr r6, r6, #1
_022444A4:
	ldr r0, [sp, #0x2c]
	cmp r0, #0x54
	bne _022444C2
	ldr r0, [sp, #0x18]
	add r2, r5, r0
	ldr r0, _02244580 ; =0x00002DCC
	ldr r1, [r2, r0]
	lsl r1, r1, #9
	lsr r1, r1, #0x1f
	beq _022444C2
	sub r0, #0x14
	ldrh r0, [r2, r0]
	cmp r0, #0
	bne _022444C2
	lsl r6, r6, #1
_022444C2:
	ldr r0, [sp, #4]
	ldr r1, [sp, #8]
	bl MOD11_02230270
	lsl r0, r0, #2
	add r1, r5, r0
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r1, [r1, r0]
	mov r0, #3
	lsl r0, r0, #8
	tst r0, r1
	beq _022444DE
	lsl r6, r6, #1
_022444DE:
	ldr r0, [sp, #0x58]
	cmp r0, #0x33
	bne _0224451C
	ldr r1, [sp, #0x54]
	mov r0, #0x64
	bl _s32_div_f
	add r1, r0, #0
	ldr r0, [sp, #8]
	lsl r0, r0, #1
	add r2, r5, r0
	ldr r0, _02244584 ; =0x0000310C
	ldrh r0, [r2, r0]
	bl _s32_div_f
	cmp r1, #0
	bne _0224451C
	mov r0, #1
	str r0, [sp, #0x40]
	ldr r0, [sp, #0x80]
	cmp r0, #0
	bne _0224451C
	ldr r0, _02244580 ; =0x00002DCC
	ldr r1, [sp, #0x18]
	add r0, r5, r0
	ldr r2, [r0, r1]
	mov r1, #2
	lsl r1, r1, #0x1c
	orr r2, r1
	ldr r1, [sp, #0x18]
	str r2, [r0, r1]
_0224451C:
	ldr r0, [sp, #0x18]
	add r1, r5, r0
	ldr r0, _02244580 ; =0x00002DCC
	ldr r0, [r1, r0]
	lsl r0, r0, #3
	lsr r0, r0, #0x1f
	beq _0224452E
	mov r0, #1
	str r0, [sp, #0x40]
_0224452E:
	ldr r0, [sp, #0x58]
	cmp r0, #0x6a
	bne _02244538
	mov r0, #1
	str r0, [sp, #0x38]
_02244538:
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	ldr r7, _02244570 ; =MOD11_0225E24C
	add r0, r5, r0
	str r0, [sp, #0x20]
_02244544:
	ldr r2, [sp, #0x20]
	ldr r1, _02244574 ; =0x00002DB8
	add r0, r5, #0
	ldrh r1, [r2, r1]
	mov r2, #1
	bl MOD11_0224C12C
	ldrb r1, [r7]
	cmp r1, r0
	bne _02244588
	lsr r4, r4, #1
	b _02244594
	.align 2, 0
_0224455C: .word 0x00002D8C
_02244560: .word 0x00002D5B
_02244564: .word 0x00002D46
_02244568: .word MOD11_0225E284
_0224456C: .word MOD11_0225E285
_02244570: .word MOD11_0225E24C
_02244574: .word 0x00002DB8
_02244578: .word 0x00002DAC
_0224457C: .word 0x00002DD8
_02244580: .word 0x00002DCC
_02244584: .word 0x0000310C
_02244588:
	ldr r0, [sp, #0x10]
	add r7, r7, #1
	add r0, r0, #1
	str r0, [sp, #0x10]
	cmp r0, #8
	blo _02244544
_02244594:
	ldr r0, [sp, #0x50]
	cmp r0, #0x72
	bne _022445A6
	mov r0, #0xf
	mul r0, r4
	mov r1, #0xa
	bl _u32_div_f
	add r4, r0, #0
_022445A6:
	ldr r0, [sp, #0x50]
	cmp r0, #0x65
	bne _022445BC
	ldr r0, [sp, #0x14]
	add r1, r5, r0
	mov r0, #0xb5
	lsl r0, r0, #6
	ldrh r0, [r1, r0]
	cmp r0, #0x84
	bne _022445BC
	lsl r4, r4, #1
_022445BC:
	ldr r0, [sp, #0x28]
	cmp r0, #0x5f
	bne _022445DE
	ldr r0, [sp, #0x14]
	add r1, r5, r0
	ldr r0, _02244894 ; =0x00002DAC
	ldr r0, [r1, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	beq _022445DE
	mov r0, #0xf
	mul r0, r4
	mov r1, #0xa
	bl _u32_div_f
	add r4, r0, #0
	b _022445EE
_022445DE:
	ldr r0, [sp, #0x14]
	add r1, r5, r0
	ldr r0, _02244894 ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #0x40
	tst r0, r1
	beq _022445EE
	lsr r4, r4, #2
_022445EE:
	ldr r0, [sp, #0x28]
	cmp r0, #0x70
	bne _0224460A
	ldr r1, [sp, #0x14]
	mov r0, #0x15
	add r2, r5, r1
	ldr r1, _02244898 ; =0x00002DD8
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	ldr r1, [r2, r1]
	sub r0, r0, r1
	cmp r0, #5
	bge _0224460A
	lsr r4, r4, #1
_0224460A:
	ldr r0, [sp, #0x28]
	cmp r0, #0x54
	bne _02244628
	ldr r0, [sp, #0x14]
	add r2, r5, r0
	ldr r0, _0224489C ; =0x00002DCC
	ldr r1, [r2, r0]
	lsl r1, r1, #9
	lsr r1, r1, #0x1f
	beq _02244628
	sub r0, #0x14
	ldrh r0, [r2, r0]
	cmp r0, #0
	bne _02244628
	lsl r4, r4, #1
_02244628:
	ldr r0, [sp, #4]
	ldr r1, [sp, #0xc]
	bl MOD11_02230270
	lsl r0, r0, #2
	add r1, r5, r0
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r1, [r1, r0]
	mov r0, #3
	lsl r0, r0, #8
	tst r0, r1
	beq _02244644
	lsl r4, r4, #1
_02244644:
	ldr r0, [sp, #0x50]
	cmp r0, #0x33
	bne _02244682
	ldr r1, [sp, #0x4c]
	mov r0, #0x64
	bl _s32_div_f
	add r1, r0, #0
	ldr r0, [sp, #0xc]
	lsl r0, r0, #1
	add r2, r5, r0
	ldr r0, _022448A0 ; =0x0000310C
	ldrh r0, [r2, r0]
	bl _s32_div_f
	cmp r1, #0
	bne _02244682
	mov r0, #1
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x80]
	cmp r0, #0
	bne _02244682
	ldr r0, _0224489C ; =0x00002DCC
	ldr r1, [sp, #0x14]
	add r0, r5, r0
	ldr r2, [r0, r1]
	mov r1, #2
	lsl r1, r1, #0x1c
	orr r2, r1
	ldr r1, [sp, #0x14]
	str r2, [r0, r1]
_02244682:
	ldr r0, [sp, #0x14]
	add r1, r5, r0
	ldr r0, _0224489C ; =0x00002DCC
	ldr r0, [r1, r0]
	lsl r0, r0, #3
	lsr r0, r0, #0x1f
	beq _02244694
	mov r0, #1
	str r0, [sp, #0x3c]
_02244694:
	ldr r0, [sp, #0x50]
	cmp r0, #0x6a
	bne _0224469E
	mov r0, #1
	str r0, [sp, #0x34]
_0224469E:
	ldr r0, [sp, #8]
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, _022448A4 ; =0x000021F0
	str r6, [r1, r0]
	ldr r1, [sp, #0xc]
	lsl r1, r1, #2
	add r1, r5, r1
	str r4, [r1, r0]
	ldr r1, [sp, #0x80]
	cmp r1, #0
	bne _02244756
	ldr r1, [sp, #0xc]
	ldr r3, _022448A8 ; =0x000030BC
	lsl r1, r1, #4
	add r2, r5, r1
	add r1, r0, #0
	sub r1, #0x3c
	ldr r1, [r2, r1]
	sub r0, #0x3c
	str r1, [sp, #0x30]
	ldr r1, [sp, #8]
	lsl r1, r1, #1
	add r1, r5, r1
	ldrh r2, [r1, r3]
	ldr r1, [sp, #0xc]
	lsl r1, r1, #1
	add r1, r5, r1
	ldrh r7, [r1, r3]
	ldr r1, [sp, #8]
	lsl r1, r1, #4
	add r1, r5, r1
	ldr r0, [r1, r0]
	cmp r0, #1
	bne _0224470E
	ldr r0, [sp, #8]
	lsl r0, r0, #6
	add r1, r5, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _022446FC
	mov r0, #0xa5
	str r0, [sp, #0x60]
	b _0224470E
_022446FC:
	ldr r1, [sp, #8]
	add r0, r5, #0
	add r2, r2, #6
	mov r3, #0
	bl MOD11_02243420
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x60]
_0224470E:
	ldr r0, [sp, #0x30]
	cmp r0, #1
	bne _0224473E
	ldr r0, [sp, #0xc]
	lsl r0, r0, #6
	add r1, r5, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _0224472C
	mov r0, #0xa5
	str r0, [sp, #0x5c]
	b _0224473E
_0224472C:
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	add r2, r7, #6
	mov r3, #0
	bl MOD11_02243420
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x5c]
_0224473E:
	ldr r0, [sp, #0x60]
	mov r1, #0xfa
	lsl r0, r0, #4
	add r0, r5, r0
	lsl r1, r1, #2
	ldrsb r0, [r0, r1]
	str r0, [sp, #0x48]
	ldr r0, [sp, #0x5c]
	lsl r0, r0, #4
	add r0, r5, r0
	ldrsb r0, [r0, r1]
	str r0, [sp, #0x44]
_02244756:
	ldr r1, [sp, #0x48]
	ldr r0, [sp, #0x44]
	cmp r1, r0
	beq _02244760
	b _022448AC
_02244760:
	ldr r0, [sp, #0x40]
	cmp r0, #0
	beq _0224478C
	ldr r0, [sp, #0x3c]
	cmp r0, #0
	beq _0224478C
	cmp r6, r4
	bhs _02244776
	mov r0, #1
	str r0, [sp, #0x64]
	b _022448B4
_02244776:
	cmp r6, r4
	bne _02244784
	bl LCRandom
	mov r1, #1
	tst r0, r1
	bne _02244786
_02244784:
	b _022448B4
_02244786:
	mov r0, #2
	str r0, [sp, #0x64]
	b _022448B4
_0224478C:
	ldr r0, [sp, #0x40]
	cmp r0, #0
	bne _0224479E
	ldr r0, [sp, #0x3c]
	cmp r0, #0
	beq _0224479E
	mov r0, #1
	str r0, [sp, #0x64]
	b _022448B4
_0224479E:
	ldr r0, [sp, #0x40]
	cmp r0, #0
	beq _022447B0
	ldr r0, [sp, #0x3c]
	cmp r0, #0
	bne _022447B0
	mov r0, #0
	str r0, [sp, #0x64]
	b _022448B4
_022447B0:
	ldr r0, [sp, #0x38]
	cmp r0, #0
	beq _022447DA
	ldr r0, [sp, #0x34]
	cmp r0, #0
	beq _022447DA
	cmp r6, r4
	bls _022447C6
	mov r0, #1
	str r0, [sp, #0x64]
	b _022448B4
_022447C6:
	cmp r6, r4
	bne _022448B4
	bl LCRandom
	mov r1, #1
	tst r0, r1
	beq _022448B4
	mov r0, #2
	str r0, [sp, #0x64]
	b _022448B4
_022447DA:
	ldr r0, [sp, #0x38]
	cmp r0, #0
	beq _022447EC
	ldr r0, [sp, #0x34]
	cmp r0, #0
	bne _022447EC
	mov r0, #1
	str r0, [sp, #0x64]
	b _022448B4
_022447EC:
	ldr r0, [sp, #0x38]
	cmp r0, #0
	bne _022447FE
	ldr r0, [sp, #0x34]
	cmp r0, #0
	beq _022447FE
	mov r0, #0
	str r0, [sp, #0x64]
	b _022448B4
_022447FE:
	ldr r0, [sp, #0x2c]
	cmp r0, #0x64
	bne _02244828
	ldr r0, [sp, #0x28]
	cmp r0, #0x64
	bne _02244828
	cmp r6, r4
	bls _02244814
	mov r0, #1
	str r0, [sp, #0x64]
	b _022448B4
_02244814:
	cmp r6, r4
	bne _022448B4
	bl LCRandom
	mov r1, #1
	tst r0, r1
	beq _022448B4
	mov r0, #2
	str r0, [sp, #0x64]
	b _022448B4
_02244828:
	ldr r0, [sp, #0x2c]
	cmp r0, #0x64
	bne _0224483A
	ldr r0, [sp, #0x28]
	cmp r0, #0x64
	beq _0224483A
	mov r0, #1
	str r0, [sp, #0x64]
	b _022448B4
_0224483A:
	ldr r0, [sp, #0x2c]
	cmp r0, #0x64
	beq _0224484C
	ldr r0, [sp, #0x28]
	cmp r0, #0x64
	bne _0224484C
	mov r0, #0
	str r0, [sp, #0x64]
	b _022448B4
_0224484C:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #7
	lsl r0, r0, #0x10
	tst r0, r1
	beq _02244876
	cmp r6, r4
	bls _02244862
	mov r0, #1
	str r0, [sp, #0x64]
_02244862:
	cmp r6, r4
	bne _022448B4
	bl LCRandom
	mov r1, #1
	tst r0, r1
	beq _022448B4
	mov r0, #2
	str r0, [sp, #0x64]
	b _022448B4
_02244876:
	cmp r6, r4
	bhs _0224487E
	mov r0, #1
	str r0, [sp, #0x64]
_0224487E:
	cmp r6, r4
	bne _022448B4
	bl LCRandom
	mov r1, #1
	tst r0, r1
	beq _022448B4
	mov r0, #2
	str r0, [sp, #0x64]
	b _022448B4
	nop
_02244894: .word 0x00002DAC
_02244898: .word 0x00002DD8
_0224489C: .word 0x00002DCC
_022448A0: .word 0x0000310C
_022448A4: .word 0x000021F0
_022448A8: .word 0x000030BC
_022448AC:
	cmp r1, r0
	bge _022448B4
	mov r0, #1
	str r0, [sp, #0x64]
_022448B4:
	ldr r0, [sp, #0x64]
	add sp, #0x68
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD11_022448BC
MOD11_022448BC: ; 0x022448BC
	asr r1, r1, #1
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1d
	add r0, r0, r1
	mov r2, #0
	add r0, #0xa4
	str r2, [r0]
	bx lr

	thumb_func_start MOD11_022448CC
MOD11_022448CC: ; 0x022448CC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r2, [sp]
	add r5, r1, #0
	mov r4, #0
	bl MOD11_0222FF74
	add r7, r0, #0
	ldr r0, [sp]
	mov r1, #0xc0
	mul r1, r0
	add r0, r5, r1
	str r0, [sp, #4]
	ldr r0, [sp]
	asr r0, r0, #1
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1d
	add r6, r5, r0
	add r6, #0xa4
_022448F2:
	add r0, r4, #0
	bl MaskOfFlagNo
	ldr r1, _0224493C ; =0x00003108
	ldrb r1, [r5, r1]
	tst r0, r1
	bne _02244928
	ldr r0, [sp]
	bl MaskOfFlagNo
	ldr r1, _0224493C ; =0x00003108
	ldrb r1, [r5, r1]
	tst r0, r1
	bne _02244928
	ldr r1, [sp, #4]
	ldr r0, _02244940 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02244928
	ldr r0, _02244944 ; =0x0000219C
	add r1, r5, r4
	ldrb r0, [r1, r0]
	bl MaskOfFlagNo
	ldr r1, [r6]
	orr r0, r1
	str r0, [r6]
_02244928:
	add r4, r4, #2
	cmp r7, #0x4a
	beq _02244936
	cmp r7, #0x4b
	beq _02244936
	cmp r4, #2
	ble _022448F2
_02244936:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224493C: .word 0x00003108
_02244940: .word 0x00002D8C
_02244944: .word 0x0000219C

	thumb_func_start MOD11_02244948
MOD11_02244948: ; 0x02244948
	push {r4, r5, r6, lr}
	ldr r0, _022449D4 ; =0x00002170
	add r5, r1, #0
	add r4, r2, #0
	ldr r2, [r5, r0]
	mov r0, #2
	lsl r0, r0, #0x1c
	mov r6, #0
	tst r0, r2
	beq _0224497A
	add r0, r5, #0
	mov r1, #1
	bl MOD11_0224C5DC
	str r0, [r4]
	ldr r0, _022449D4 ; =0x00002170
	add r1, r6, #0
	str r1, [r5, r0]
	sub r0, r0, #4
	ldr r1, [r5, r0]
	ldr r0, _022449D8 ; =0x801FDA49
	tst r0, r1
	bne _022449CE
	mov r6, #1
	b _022449CE
_0224497A:
	cmp r2, #0
	beq _022449CE
	add r0, r5, #0
	mov r1, #1
	bl MOD11_0224C5DC
	str r0, [r4]
	add r0, r5, #0
	add r0, #0x94
	ldr r1, [r0]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _022449DC ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _022449C8
	ldr r1, _022449E0 ; =0x0000216C
	ldr r2, _022449D8 ; =0x801FDA49
	ldr r0, [r5, r1]
	tst r2, r0
	beq _022449C6
	add r1, r1, #4
	mov r2, #2
	ldr r1, [r5, r1]
	lsl r2, r2, #0x16
	tst r2, r1
	beq _022449B8
	ldr r2, _022449E4 ; =0x00040008
	tst r2, r0
	bne _022449C6
_022449B8:
	mov r2, #1
	lsl r2, r2, #0x1c
	tst r1, r2
	beq _022449C8
	ldr r1, _022449E8 ; =0x00010001
	tst r0, r1
	beq _022449C8
_022449C6:
	mov r6, #1
_022449C8:
	ldr r0, _022449D4 ; =0x00002170
	mov r1, #0
	str r1, [r5, r0]
_022449CE:
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	nop
_022449D4: .word 0x00002170
_022449D8: .word 0x801FDA49
_022449DC: .word 0x00002D8C
_022449E0: .word 0x0000216C
_022449E4: .word 0x00040008
_022449E8: .word 0x00010001

	thumb_func_start MOD11_022449EC
MOD11_022449EC: ; 0x022449EC
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, _02244C04 ; =0x00002174
	add r5, r1, #0
	add r4, r2, #0
	ldr r2, [r5, r0]
	mov r1, #2
	lsl r1, r1, #0x1c
	add r3, r2, #0
	mov r6, #0
	tst r3, r1
	beq _02244A20
	add r0, r5, #0
	mov r1, #2
	bl MOD11_0224C5DC
	str r0, [r4]
	ldr r0, _02244C04 ; =0x00002174
	add r1, r6, #0
	str r1, [r5, r0]
	sub r0, #8
	ldr r1, [r5, r0]
	ldr r0, _02244C08 ; =0x801FDA49
	tst r0, r1
	bne _02244AC0
	mov r6, #1
	b _02244C00
_02244A20:
	lsr r3, r1, #5
	tst r3, r2
	beq _02244A54
	add r0, r5, #0
	mov r1, #2
	bl MOD11_0224C5DC
	str r0, [r4]
	ldr r0, _02244C04 ; =0x00002174
	add r1, r6, #0
	str r1, [r5, r0]
	add r1, r5, #0
	add r1, #0x94
	ldr r1, [r1]
	add r0, r5, #0
	bl MOD11_0224AD9C
	cmp r0, #0
	bne _02244AC0
	ldr r0, _02244C0C ; =0x0000216C
	ldr r1, [r5, r0]
	ldr r0, _02244C08 ; =0x801FDA49
	tst r0, r1
	bne _02244AC0
	mov r6, #1
	b _02244C00
_02244A54:
	lsr r3, r1, #4
	tst r3, r2
	beq _02244A96
	add r0, r5, #0
	mov r1, #2
	bl MOD11_0224C5DC
	str r0, [r4]
	ldr r0, _02244C04 ; =0x00002174
	add r1, r6, #0
	str r1, [r5, r0]
	add r0, r5, #0
	add r0, #0x94
	ldr r1, [r0]
	mov r0, #0xc0
	mul r0, r1
	add r2, r5, r0
	ldr r0, _02244C10 ; =0x00002D8C
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _02244AC0
	add r0, r5, #0
	bl MOD11_0224AD9C
	cmp r0, #0
	bne _02244AC0
	ldr r0, _02244C0C ; =0x0000216C
	ldr r1, [r5, r0]
	ldr r0, _02244C08 ; =0x801FDA49
	tst r0, r1
	bne _02244AC0
	mov r6, #1
	b _02244C00
_02244A96:
	lsr r3, r1, #1
	tst r3, r2
	beq _02244AC6
	add r0, r5, #0
	mov r1, #2
	bl MOD11_0224C5DC
	str r0, [r4]
	ldr r0, _02244C04 ; =0x00002174
	add r1, r6, #0
	str r1, [r5, r0]
	add r0, r5, #0
	add r0, #0x94
	ldr r1, [r0]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _02244C10 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _02244AC2
_02244AC0:
	b _02244C00
_02244AC2:
	mov r6, #1
	b _02244C00
_02244AC6:
	lsr r1, r1, #3
	tst r1, r2
	beq _02244B50
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl MOD11_02246D1C
	cmp r0, #0x20
	ldr r0, _02244C14 ; =0x00003044
	bne _02244AEA
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _02244C18 ; =0x000003E5
	ldrb r0, [r1, r0]
	lsl r0, r0, #0x11
	lsr r6, r0, #0x10
	b _02244AF4
_02244AEA:
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _02244C18 ; =0x000003E5
	ldrb r6, [r1, r0]
_02244AF4:
	cmp r6, #0
	bne _02244AFC
	bl GF_AssertFail
_02244AFC:
	bl LCRandom
	mov r1, #0x64
	bl _s32_div_f
	cmp r1, r6
	bge _02244B16
	ldr r1, _02244C1C ; =0x0000213C
	mov r0, #1
	ldr r2, [r5, r1]
	lsl r0, r0, #0x16
	orr r0, r2
	str r0, [r5, r1]
_02244B16:
	ldr r2, _02244C04 ; =0x00002174
	add r0, r5, #0
	ldr r2, [r5, r2]
	mov r1, #2
	bl MOD11_0224C5DC
	str r0, [r4]
	ldr r1, _02244C04 ; =0x00002174
	mov r0, #0
	str r0, [r5, r1]
	add r0, r5, #0
	add r0, #0x94
	ldr r2, [r0]
	mov r0, #0xc0
	mul r0, r2
	add r2, r5, r0
	ldr r0, _02244C10 ; =0x00002D8C
	ldr r0, [r2, r0]
	cmp r0, #0
	bne _02244B4C
	add r0, r1, #0
	sub r0, #0x38
	ldr r2, [r5, r0]
	ldr r0, _02244C20 ; =0xFFBFFFFF
	sub r1, #0x38
	and r0, r2
	str r0, [r5, r1]
_02244B4C:
	mov r6, #1
	b _02244C00
_02244B50:
	cmp r2, #0
	beq _02244BD2
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl MOD11_02246D1C
	cmp r0, #0x20
	ldr r0, _02244C14 ; =0x00003044
	bne _02244B72
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _02244C18 ; =0x000003E5
	ldrb r0, [r1, r0]
	lsl r0, r0, #0x11
	lsr r7, r0, #0x10
	b _02244B7C
_02244B72:
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _02244C18 ; =0x000003E5
	ldrb r7, [r1, r0]
_02244B7C:
	cmp r7, #0
	bne _02244B84
	bl GF_AssertFail
_02244B84:
	bl LCRandom
	mov r1, #0x64
	bl _s32_div_f
	cmp r1, r7
	bge _02244C00
	ldr r2, _02244C04 ; =0x00002174
	add r0, r5, #0
	ldr r2, [r5, r2]
	mov r1, #2
	bl MOD11_0224C5DC
	str r0, [r4]
	ldr r0, _02244C04 ; =0x00002174
	mov r1, #0
	str r1, [r5, r0]
	add r0, r5, #0
	add r0, #0x94
	ldr r1, [r0]
	mov r0, #0xc0
	mul r0, r1
	add r2, r5, r0
	ldr r0, _02244C10 ; =0x00002D8C
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _02244C00
	add r0, r5, #0
	bl MOD11_0224AD9C
	cmp r0, #0
	bne _02244C00
	ldr r0, _02244C0C ; =0x0000216C
	ldr r1, [r5, r0]
	ldr r0, _02244C08 ; =0x801FDA49
	tst r0, r1
	bne _02244C00
	mov r6, #1
	b _02244C00
_02244BD2:
	add r0, r0, #4
	ldr r2, [r5, r0]
	cmp r2, #0
	beq _02244C00
	add r0, r5, #0
	mov r1, #3
	bl MOD11_0224C5DC
	str r0, [r4]
	ldr r0, _02244C24 ; =0x00002178
	add r1, r6, #0
	str r1, [r5, r0]
	add r0, r5, #0
	add r0, #0x94
	ldr r1, [r0]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _02244C10 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02244C00
	mov r6, #1
_02244C00:
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02244C04: .word 0x00002174
_02244C08: .word 0x801FDA49
_02244C0C: .word 0x0000216C
_02244C10: .word 0x00002D8C
_02244C14: .word 0x00003044
_02244C18: .word 0x000003E5
_02244C1C: .word 0x0000213C
_02244C20: .word 0xFFBFFFFF
_02244C24: .word 0x00002178

	thumb_func_start MOD11_02244C28
MOD11_02244C28: ; 0x02244C28
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r6, r0, #0
	mov r0, #0xff
	add r4, r1, #0
	add r5, r2, #0
	str r0, [sp, #0xc]
	cmp r3, #0
	beq _02244C44
	lsl r0, r3, #4
	add r1, r4, r0
	ldr r0, _02244F24 ; =0x000003E6
	ldrh r0, [r1, r0]
	b _02244C46
_02244C44:
	ldr r0, [sp, #0x34]
_02244C46:
	cmp r0, #4
	bne _02244CD6
	add r0, r6, #0
	bl MOD11_0222FF84
	str r0, [sp, #8]
	add r0, r6, #0
	add r1, r5, #0
	bl MOD11_0222FF7C
	bl MOD11_02253A4C
	ldr r1, _02244F28 ; =0x0000217E
	mov r2, #0
	strb r2, [r4, r1]
	ldrb r1, [r4, r1]
	ldr r2, [sp, #8]
	cmp r1, r2
	bge _02244CC4
	mov r2, #1
	add r5, r0, #0
	and r5, r2
_02244C72:
	ldr r0, _02244F2C ; =0x000021EC
	add r1, r4, r1
	ldrb r7, [r1, r0]
	mov r0, #0xc0
	mul r0, r7
	add r1, r4, r0
	ldr r0, _02244F30 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02244CB2
	add r0, r6, #0
	add r1, r7, #0
	bl MOD11_0222FF7C
	str r0, [sp]
	cmp r5, #0
	beq _02244C9E
	bl MOD11_02253A4C
	mov r1, #1
	tst r0, r1
	beq _02244CAE
_02244C9E:
	cmp r5, #0
	bne _02244CB2
	ldr r0, [sp]
	bl MOD11_02253A4C
	mov r1, #1
	tst r0, r1
	beq _02244CB2
_02244CAE:
	str r7, [sp, #0xc]
	b _02244CC4
_02244CB2:
	ldr r0, _02244F28 ; =0x0000217E
	ldrb r0, [r4, r0]
	add r1, r0, #1
	ldr r0, _02244F28 ; =0x0000217E
	strb r1, [r4, r0]
	ldrb r1, [r4, r0]
	ldr r0, [sp, #8]
	cmp r1, r0
	blt _02244C72
_02244CC4:
	ldr r1, _02244F28 ; =0x0000217E
	ldr r0, [sp, #8]
	ldrb r2, [r4, r1]
	cmp r2, r0
	bne _02244CD0
	b _02244F5C
_02244CD0:
	add r0, r2, #1
	strb r0, [r4, r1]
	b _02244F5C
_02244CD6:
	cmp r0, #8
	bne _02244D26
	add r0, r6, #0
	bl MOD11_0222FF84
	add r2, r0, #0
	ldr r0, _02244F28 ; =0x0000217E
	mov r1, #0
	strb r1, [r4, r0]
	ldrb r3, [r4, r0]
	cmp r3, r2
	bge _02244D18
	ldr r7, _02244F30 ; =0x00002D8C
_02244CF0:
	ldr r1, _02244F2C ; =0x000021EC
	add r6, r4, r3
	ldrb r1, [r6, r1]
	mov r6, #0xc0
	mul r6, r1
	add r6, r4, r6
	ldr r6, [r6, r7]
	cmp r6, #0
	beq _02244D0A
	cmp r1, r5
	beq _02244D0A
	str r1, [sp, #0xc]
	b _02244D18
_02244D0A:
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	ldr r1, _02244F28 ; =0x0000217E
	ldrb r3, [r4, r1]
	cmp r3, r2
	blt _02244CF0
_02244D18:
	cmp r3, r2
	beq _02244E02
	ldr r0, _02244F28 ; =0x0000217E
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _02244F5C
_02244D26:
	mov r1, #2
	lsl r1, r1, #8
	cmp r0, r1
	bne _02244D72
	ldr r1, [sp, #0x30]
	cmp r1, #1
	bne _02244D72
	add r0, r6, #0
	bl MOD11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _02244D6E
	bl LCRandom
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	bne _02244D6E
	add r0, r6, #0
	add r1, r5, #0
	bl MOD11_022302BC
	mov r1, #0xc0
	mul r1, r0
	str r0, [sp, #0xc]
	ldr r0, _02244F30 ; =0x00002D8C
	add r1, r4, r1
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _02244E02
	str r5, [sp, #0xc]
	b _02244F5C
_02244D6E:
	str r5, [sp, #0xc]
	b _02244F5C
_02244D72:
	mov r1, #1
	lsl r1, r1, #0xa
	cmp r0, r1
	bne _02244D8E
	ldr r1, [sp, #0x30]
	cmp r1, #1
	bne _02244D8E
	add r0, r6, #0
	add r1, r4, #0
	add r2, r5, #0
	bl MOD11_022482A4
	str r0, [sp, #0xc]
	b _02244F5C
_02244D8E:
	cmp r0, #0x80
	bne _02244DA0
	add r0, r6, #0
	add r1, r4, #0
	add r2, r5, #0
	bl MOD11_022482A4
	str r0, [sp, #0xc]
	b _02244F5C
_02244DA0:
	cmp r0, #0x10
	beq _02244DB0
	cmp r0, #0x20
	beq _02244DB0
	cmp r0, #1
	beq _02244DB0
	cmp r0, #0x40
	bne _02244DB4
_02244DB0:
	str r5, [sp, #0xc]
	b _02244F5C
_02244DB4:
	mov r1, #1
	lsl r1, r1, #8
	cmp r0, r1
	bne _02244DD8
	add r0, r6, #0
	bl MOD11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _02244DD4
	add r0, r6, #0
	add r1, r5, #0
	bl MOD11_022302BC
	str r0, [sp, #0xc]
	b _02244F5C
_02244DD4:
	str r5, [sp, #0xc]
	b _02244F5C
_02244DD8:
	lsl r1, r1, #1
	cmp r0, r1
	bne _02244E0C
	add r0, r6, #0
	bl MOD11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _02244E08
	lsl r0, r5, #4
	add r1, r4, r0
	ldr r0, _02244F34 ; =0x000021AC
	ldr r0, [r1, r0]
	mov r1, #0xc0
	mul r1, r0
	str r0, [sp, #0xc]
	ldr r0, _02244F30 ; =0x00002D8C
	add r1, r4, r1
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02244E04
_02244E02:
	b _02244F5C
_02244E04:
	str r5, [sp, #0xc]
	b _02244F5C
_02244E08:
	str r5, [sp, #0xc]
	b _02244F5C
_02244E0C:
	cmp r0, #2
	beq _02244E16
	ldr r0, [sp, #0x30]
	cmp r0, #1
	bne _02244ED6
_02244E16:
	add r0, r6, #0
	bl MOD11_0222FF74
	str r0, [sp, #0x10]
	add r0, r6, #0
	add r1, r5, #0
	bl MOD11_02230270
	add r7, r0, #0
	mov r1, #1
	eor r7, r1
	add r0, r6, #0
	add r1, r5, #0
	mov r2, #0
	bl MOD11_02230308
	str r0, [sp, #0x14]
	add r0, r6, #0
	add r1, r5, #0
	mov r2, #2
	bl MOD11_02230308
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x10]
	mov r1, #2
	tst r0, r1
	beq _02244EBE
	mov r0, #0x71
	lsl r0, r0, #2
	add r1, r4, r0
	lsl r0, r7, #3
	ldr r0, [r1, r0]
	lsl r1, r0, #0xb
	lsr r1, r1, #0x1f
	beq _02244E72
	lsl r0, r0, #9
	lsr r2, r0, #0x1e
	mov r0, #0xc0
	mul r0, r2
	add r1, r4, r0
	ldr r0, _02244F30 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02244E72
	str r2, [sp, #0xc]
	b _02244F5C
_02244E72:
	ldr r0, [sp, #0x14]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	add r0, r4, r2
	ldr r2, _02244F30 ; =0x00002D8C
	ldr r0, [r0, r2]
	cmp r0, #0
	beq _02244EA0
	ldr r3, [sp, #0x18]
	mul r1, r3
	add r1, r4, r1
	ldr r1, [r1, r2]
	cmp r1, #0
	beq _02244EA0
	bl LCRandom
	lsl r0, r0, #0x1f
	lsr r1, r0, #0x1d
	add r0, sp, #0x14
	ldr r0, [r0, r1]
	str r0, [sp, #0xc]
	b _02244F5C
_02244EA0:
	cmp r0, #0
	beq _02244EAA
	ldr r0, [sp, #0x14]
	str r0, [sp, #0xc]
	b _02244F5C
_02244EAA:
	ldr r2, [sp, #0x18]
	mov r0, #0xc0
	mul r0, r2
	add r1, r4, r0
	ldr r0, _02244F30 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02244F5C
	str r2, [sp, #0xc]
	b _02244F5C
_02244EBE:
	mov r0, #1
	add r2, r5, #0
	eor r2, r0
	mov r0, #0xc0
	mul r0, r2
	add r1, r4, r0
	ldr r0, _02244F30 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02244F5C
	str r2, [sp, #0xc]
	b _02244F5C
_02244ED6:
	add r0, r6, #0
	add r1, r5, #0
	bl MOD11_02230270
	mov r1, #1
	eor r0, r1
	str r0, [sp, #4]
	lsl r0, r5, #4
	add r1, r4, r0
	ldr r0, _02244F34 ; =0x000021AC
	ldr r7, [r1, r0]
	add r0, r6, #0
	bl MOD11_0222FF84
	mov r0, #0x71
	lsl r0, r0, #2
	add r1, r4, r0
	ldr r0, [sp, #4]
	lsl r0, r0, #3
	ldr r0, [r1, r0]
	lsl r1, r0, #0xb
	lsr r1, r1, #0x1f
	beq _02244F1A
	lsl r0, r0, #9
	lsr r0, r0, #0x1e
	mov r1, #0xc0
	mul r1, r0
	add r2, r4, r1
	ldr r1, _02244F30 ; =0x00002D8C
	ldr r1, [r2, r1]
	cmp r1, #0
	beq _02244F1A
	str r0, [sp, #0xc]
	b _02244F5C
_02244F1A:
	mov r0, #0xc0
	mul r0, r7
	add r1, r4, r0
	ldr r0, _02244F30 ; =0x00002D8C
	b _02244F38
	.align 2, 0
_02244F24: .word 0x000003E6
_02244F28: .word 0x0000217E
_02244F2C: .word 0x000021EC
_02244F30: .word 0x00002D8C
_02244F34: .word 0x000021AC
_02244F38:
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02244F42
	str r7, [sp, #0xc]
	b _02244F5C
_02244F42:
	add r0, r6, #0
	add r1, r4, #0
	add r2, r5, #0
	bl MOD11_022482A4
	mov r1, #0xc0
	mul r1, r0
	add r2, r4, r1
	ldr r1, _02244F64 ; =0x00002D8C
	ldr r1, [r2, r1]
	cmp r1, #0
	beq _02244F5C
	str r0, [sp, #0xc]
_02244F5C:
	ldr r0, [sp, #0xc]
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_02244F64: .word 0x00002D8C

	thumb_func_start MOD11_02244F68
MOD11_02244F68: ; 0x02244F68
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	str r0, [sp, #4]
	ldr r0, [r5, #0x6c]
	add r7, r2, #0
	add r6, r3, #0
	cmp r0, #0xff
	beq _02244FC2
	add r0, r5, #0
	add r1, r7, #0
	bl MOD11_02246D1C
	cmp r0, #0x60
	beq _02244FC2
	add r0, r5, #0
	add r1, r7, #0
	bl MOD11_02246D1C
	cmp r0, #0x68
	beq _02244FC2
	ldr r0, [sp, #4]
	add r1, r7, #0
	bl MOD11_02230270
	add r2, r0, #0
	mov r1, #1
	mov r0, #0x71
	eor r2, r1
	lsl r0, r0, #2
	add r1, r5, r0
	lsl r0, r2, #3
	ldr r0, [r1, r0]
	lsl r1, r0, #0xb
	lsr r1, r1, #0x1f
	beq _02244FC4
	lsl r0, r0, #9
	lsr r1, r0, #0x1e
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _022450F8 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02244FC4
_02244FC2:
	b _022450F4
_02244FC4:
	ldr r0, [sp, #4]
	add r1, r5, #0
	add r2, r7, #0
	add r3, r6, #0
	bl MOD11_0224C8EC
	str r0, [sp, #0xc]
	cmp r0, #0
	bne _02244FE0
	lsl r0, r6, #4
	add r1, r5, r0
	ldr r0, _022450FC ; =0x000003E2
	ldrb r0, [r1, r0]
	str r0, [sp, #0xc]
_02244FE0:
	ldr r0, [sp, #4]
	bl MOD11_0222FF84
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	cmp r0, #0xd
	bne _02245070
	lsl r0, r6, #4
	add r1, r5, r0
	ldr r0, _02245100 ; =0x000003E6
	ldrh r0, [r1, r0]
	cmp r0, #0
	beq _02244FFE
	cmp r0, #2
	bne _02245070
_02244FFE:
	ldr r0, _02245104 ; =0x0000213C
	ldr r1, [r5, r0]
	mov r0, #0x20
	tst r0, r1
	bne _02245070
	mov r0, #0x1f
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #9
	add r3, r7, #0
	bl MOD11_02246870
	cmp r0, #0
	beq _02245070
	ldr r0, [sp, #8]
	mov r6, #0
	cmp r0, #0
	ble _02245050
_02245024:
	ldr r0, _02245108 ; =0x000021EC
	add r1, r5, r6
	ldrb r4, [r1, r0]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x1f
	bne _02245048
	mov r0, #0xc0
	mul r0, r4
	add r1, r5, r0
	ldr r0, _022450F8 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02245048
	cmp r7, r4
	bne _02245050
_02245048:
	ldr r0, [sp, #8]
	add r6, r6, #1
	cmp r6, r0
	blt _02245024
_02245050:
	ldr r0, [r5, #0x6c]
	cmp r4, r0
	beq _022450F4
	mov r0, #0xb5
	lsl r0, r0, #2
	add r3, r5, r0
	mov r0, #0x1c
	add r2, r4, #0
	mul r2, r0
	ldr r1, [r3, r2]
	mov r0, #2
	orr r0, r1
	str r0, [r3, r2]
	add sp, #0x10
	str r4, [r5, #0x6c]
	pop {r3, r4, r5, r6, r7, pc}
_02245070:
	ldr r0, [sp, #0xc]
	cmp r0, #0xb
	bne _022450F4
	lsl r0, r6, #4
	add r1, r5, r0
	ldr r0, _02245100 ; =0x000003E6
	ldrh r0, [r1, r0]
	cmp r0, #0
	beq _02245086
	cmp r0, #2
	bne _022450F4
_02245086:
	ldr r0, _02245104 ; =0x0000213C
	ldr r1, [r5, r0]
	mov r0, #0x20
	tst r0, r1
	bne _022450F4
	mov r0, #0x72
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #9
	add r3, r7, #0
	bl MOD11_02246870
	cmp r0, #0
	beq _022450F4
	ldr r0, [sp, #8]
	mov r6, #0
	cmp r0, #0
	ble _022450D8
_022450AC:
	ldr r0, _02245108 ; =0x000021EC
	add r1, r5, r6
	ldrb r4, [r1, r0]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x72
	bne _022450D0
	mov r0, #0xc0
	mul r0, r4
	add r1, r5, r0
	ldr r0, _022450F8 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _022450D0
	cmp r7, r4
	bne _022450D8
_022450D0:
	ldr r0, [sp, #8]
	add r6, r6, #1
	cmp r6, r0
	blt _022450AC
_022450D8:
	ldr r0, [r5, #0x6c]
	cmp r4, r0
	beq _022450F4
	mov r0, #0xb5
	lsl r0, r0, #2
	add r3, r5, r0
	mov r0, #0x1c
	add r2, r4, #0
	mul r2, r0
	ldr r1, [r3, r2]
	mov r0, #4
	orr r0, r1
	str r0, [r3, r2]
	str r4, [r5, #0x6c]
_022450F4:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022450F8: .word 0x00002D8C
_022450FC: .word 0x000003E2
_02245100: .word 0x000003E6
_02245104: .word 0x0000213C
_02245108: .word 0x000021EC

	thumb_func_start MOD11_0224510C
MOD11_0224510C: ; 0x0224510C
	push {r3, r4, r5, lr}
	ldr r0, _02245188 ; =0x0000216C
	add r4, r1, #0
	ldr r1, [r4, r0]
	ldr r0, _0224518C ; =0x801FDA49
	mov r2, #0
	tst r0, r1
	bne _0224514A
	mov r0, #0xb5
	lsl r0, r0, #2
	add r1, r4, r0
	ldr r3, [r4, #0x6c]
	mov r0, #0x1c
	mul r0, r3
	ldr r3, [r1, r0]
	lsl r5, r3, #0x1e
	lsr r5, r5, #0x1f
	beq _0224514A
	mov r2, #2
	bic r3, r2
	str r3, [r1, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xb4
	bl MOD11_022431DC
	ldr r0, [r4, #8]
	mov r2, #1
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
_0224514A:
	ldr r0, _02245188 ; =0x0000216C
	ldr r1, [r4, r0]
	ldr r0, _0224518C ; =0x801FDA49
	tst r0, r1
	bne _02245182
	mov r0, #0xb5
	lsl r0, r0, #2
	add r1, r4, r0
	ldr r3, [r4, #0x6c]
	mov r0, #0x1c
	mul r0, r3
	ldr r3, [r1, r0]
	lsl r5, r3, #0x1d
	lsr r5, r5, #0x1f
	beq _02245182
	mov r2, #4
	bic r3, r2
	str r3, [r1, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xb4
	bl MOD11_022431DC
	ldr r0, [r4, #8]
	mov r2, #1
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
_02245182:
	add r0, r2, #0
	pop {r3, r4, r5, pc}
	nop
_02245188: .word 0x0000216C
_0224518C: .word 0x801FDA49

	thumb_func_start MOD11_02245190
MOD11_02245190: ; 0x02245190
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r4, r2, #0
	mov r0, #0xc0
	add r5, r1, #0
	mul r0, r4
	add r1, r5, r0
	ldr r0, _022451BC ; =0x00002DB8
	ldrh r0, [r1, r0]
	cmp r0, #0
	bne _022451B0
	lsl r1, r4, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	bl MOD11_0224C83C
_022451B0:
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl MOD11_02256150
	pop {r4, r5, r6, pc}
	.align 2, 0
_022451BC: .word 0x00002DB8

	thumb_func_start MOD11_022451C0
MOD11_022451C0: ; 0x022451C0
	push {r4, r5}
	ldr r0, _022451E8 ; =0x00002DB0
	add r4, r2, #0
	add r5, r1, r0
	mov r0, #0xc0
	mul r4, r0
	mov r0, #1
	ldr r3, [r5, r4]
	lsl r0, r0, #0xc
	orr r0, r3
	str r0, [r5, r4]
	ldr r0, _022451EC ; =0x00003044
	lsl r2, r2, #2
	ldr r3, [r1, r0]
	add r1, r1, r2
	add r0, #8
	str r3, [r1, r0]
	pop {r4, r5}
	bx lr
	nop
_022451E8: .word 0x00002DB0
_022451EC: .word 0x00003044

	thumb_func_start MOD11_022451F0
MOD11_022451F0: ; 0x022451F0
	push {r4, r5}
	ldr r4, _02245234 ; =0x00002DB0
	add r3, r2, #0
	mov r0, #0xc0
	mul r3, r0
	add r0, r1, r4
	ldr r5, [r0, r3]
	ldr r2, _02245238 ; =0xFFFFEFFF
	and r2, r5
	str r2, [r0, r3]
	ldr r5, [r0, r3]
	ldr r2, _0224523C ; =0xFFFFFCFF
	and r2, r5
	str r2, [r0, r3]
	add r0, r4, #0
	add r0, #0x10
	add r5, r1, r0
	ldr r2, [r5, r3]
	ldr r0, _02245240 ; =0xDFFBFF3F
	add r4, #0x18
	and r0, r2
	str r0, [r5, r3]
	add r2, r1, r4
	ldr r1, [r2, r3]
	ldr r0, _02245244 ; =0xFFFC7FFF
	and r0, r1
	str r0, [r2, r3]
	ldr r1, [r2, r3]
	ldr r0, _02245248 ; =0xFFE3FFFF
	and r0, r1
	str r0, [r2, r3]
	pop {r4, r5}
	bx lr
	nop
_02245234: .word 0x00002DB0
_02245238: .word 0xFFFFEFFF
_0224523C: .word 0xFFFFFCFF
_02245240: .word 0xDFFBFF3F
_02245244: .word 0xFFFC7FFF
_02245248: .word 0xFFE3FFFF

	thumb_func_start MOD11_0224524C
MOD11_0224524C: ; 0x0224524C
	mov r2, #0xc0
	mul r2, r1
	add r1, r0, r2
	ldr r0, _02245298 ; =0x00002DAC
	ldr r0, [r1, r0]
	mov r1, #7
	tst r1, r0
	beq _02245260
	mov r0, #1
	bx lr
_02245260:
	mov r1, #8
	tst r1, r0
	beq _0224526A
	mov r0, #2
	bx lr
_0224526A:
	mov r1, #0x10
	tst r1, r0
	beq _02245274
	mov r0, #3
	bx lr
_02245274:
	mov r1, #0x20
	tst r1, r0
	beq _0224527E
	mov r0, #4
	bx lr
_0224527E:
	mov r1, #0x40
	tst r1, r0
	beq _02245288
	mov r0, #5
	bx lr
_02245288:
	mov r1, #0x80
	tst r0, r1
	beq _02245292
	mov r0, #2
	bx lr
_02245292:
	mov r0, #0
	bx lr
	nop
_02245298: .word 0x00002DAC

	thumb_func_start MOD11_0224529C
MOD11_0224529C: ; 0x0224529C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r0, [sp]
	add r7, r1, #0
	bl MOD11_0222FF74
	mov r1, #0x84
	tst r1, r0
	beq _022452B4
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_022452B4:
	mov r1, #1
	add r2, r0, #0
	tst r2, r1
	bne _022452C2
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_022452C2:
	mov r2, #2
	tst r0, r2
	beq _022452CE
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_022452CE:
	ldr r0, [sp]
	bl MOD11_02230140
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #4]
_022452DA:
	ldr r0, [sp, #4]
	cmp r0, #4
	bls _022452E2
	b _02245478
_022452E2:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022452EE: ; jump table
	.short _022452F8 - _022452EE - 2 ; case 0
	.short _0224533C - _022452EE - 2 ; case 1
	.short _02245384 - _022452EE - 2 ; case 2
	.short _022453F8 - _022452EE - 2 ; case 3
	.short _02245478 - _022452EE - 2 ; case 4
_022452F8:
	ldr r0, _02245488 ; =0x00002E7C
	ldrb r0, [r7, r0]
	cmp r0, #1
	bne _02245334
	mov r0, #0x85
	lsl r0, r0, #6
	ldr r1, [r7, r0]
	mov r0, #0x20
	tst r0, r1
	bne _02245334
	ldr r0, [sp, #8]
	mov r1, #0xd
	mov r2, #5
	bl TrainerMessageWithIdPairExists
	cmp r0, #0
	beq _02245334
	mov r1, #0x85
	lsl r1, r1, #6
	ldr r2, [r7, r1]
	mov r0, #0x20
	orr r0, r2
	str r0, [r7, r1]
	mov r0, #0x13
	mov r1, #0xd
	lsl r0, r0, #4
	str r1, [r7, r0]
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02245334:
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	b _02245478
_0224533C:
	ldr r1, _0224548C ; =0x00002E7D
	mov r0, #2
	ldrb r2, [r7, r1]
	tst r0, r2
	bne _0224537C
	add r0, r1, #0
	sub r0, #0x31
	sub r1, #0x2d
	ldr r2, [r7, r0]
	ldr r0, [r7, r1]
	lsr r0, r0, #1
	cmp r2, r0
	bhi _0224537C
	ldr r0, [sp, #8]
	mov r1, #0xe
	mov r2, #5
	bl TrainerMessageWithIdPairExists
	cmp r0, #0
	beq _0224537C
	ldr r1, _0224548C ; =0x00002E7D
	mov r0, #2
	ldrb r2, [r7, r1]
	add sp, #0xc
	orr r0, r2
	strb r0, [r7, r1]
	mov r0, #0x13
	mov r1, #0xe
	lsl r0, r0, #4
	str r1, [r7, r0]
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0224537C:
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	b _02245478
_02245384:
	ldr r0, _0224548C ; =0x00002E7D
	ldrb r1, [r7, r0]
	mov r0, #3
	tst r0, r1
	bne _022453F0
	ldr r0, [sp]
	mov r1, #1
	bl MOD11_0222FF88
	mov r6, #0
	add r5, r0, #0
	add r4, r6, #0
	bl GetPartyCount
	cmp r0, #0
	ble _022453C6
_022453A4:
	add r0, r5, #0
	add r1, r4, #0
	bl GetPartyMonByIndex
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _022453BA
	add r6, r6, #1
_022453BA:
	add r0, r5, #0
	add r4, r4, #1
	bl GetPartyCount
	cmp r4, r0
	blt _022453A4
_022453C6:
	cmp r6, #1
	bne _022453F0
	ldr r0, [sp, #8]
	mov r1, #0xf
	mov r2, #5
	bl TrainerMessageWithIdPairExists
	cmp r0, #0
	beq _022453F0
	ldr r1, _0224548C ; =0x00002E7D
	mov r0, #3
	ldrb r2, [r7, r1]
	add sp, #0xc
	orr r0, r2
	strb r0, [r7, r1]
	mov r0, #0x13
	mov r1, #0xf
	lsl r0, r0, #4
	str r1, [r7, r0]
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_022453F0:
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	b _02245478
_022453F8:
	ldr r0, _0224548C ; =0x00002E7D
	ldrb r1, [r7, r0]
	mov r0, #4
	tst r0, r1
	bne _02245472
	ldr r0, [sp]
	mov r1, #1
	bl MOD11_0222FF88
	mov r6, #0
	add r5, r0, #0
	add r4, r6, #0
	bl GetPartyCount
	cmp r0, #0
	ble _0224543A
_02245418:
	add r0, r5, #0
	add r1, r4, #0
	bl GetPartyMonByIndex
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _0224542E
	add r6, r6, #1
_0224542E:
	add r0, r5, #0
	add r4, r4, #1
	bl GetPartyCount
	cmp r4, r0
	blt _02245418
_0224543A:
	cmp r6, #1
	bne _02245472
	ldr r0, _02245490 ; =0x00002E4C
	ldr r1, [r7, r0]
	add r0, r0, #4
	ldr r0, [r7, r0]
	lsr r0, r0, #1
	cmp r1, r0
	bhi _02245472
	ldr r0, [sp, #8]
	mov r1, #0x10
	mov r2, #5
	bl TrainerMessageWithIdPairExists
	cmp r0, #0
	beq _02245472
	ldr r1, _0224548C ; =0x00002E7D
	mov r0, #4
	ldrb r2, [r7, r1]
	add sp, #0xc
	orr r0, r2
	strb r0, [r7, r1]
	mov r0, #0x13
	mov r1, #0x10
	lsl r0, r0, #4
	str r1, [r7, r0]
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02245472:
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
_02245478:
	ldr r0, [sp, #4]
	cmp r0, #4
	beq _02245480
	b _022452DA
_02245480:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02245488: .word 0x00002E7C
_0224548C: .word 0x00002E7D
_02245490: .word 0x00002E4C

	thumb_func_start MOD11_02245494
MOD11_02245494: ; 0x02245494
	push {r3, r4, r5, r6, r7, lr}
	ldr r1, _02245574 ; =0x00002144
	add r5, r0, #0
	mov r4, #0
	add r0, r1, #0
	str r4, [r5, r1]
	mov r2, #1
	add r0, #0xc
	str r2, [r5, r0]
	add r0, r1, #0
	add r0, #8
	str r4, [r5, r0]
	add r0, r1, #0
	add r0, #0x10
	str r4, [r5, r0]
	add r0, r1, #0
	mov r2, #0xa
	add r0, #0x14
	str r2, [r5, r0]
	add r0, r1, #0
	add r0, #0x1c
	str r4, [r5, r0]
	add r0, r1, #0
	add r0, #0x20
	str r4, [r5, r0]
	add r0, r1, #0
	add r0, #0x28
	str r4, [r5, r0]
	mov r0, #0xff
	add r2, r1, #0
	str r0, [r5, #0x74]
	add r2, #0x2c
	str r4, [r5, r2]
	add r2, r1, #0
	add r2, #0x30
	str r4, [r5, r2]
	add r2, r1, #0
	add r2, #0x34
	str r4, [r5, r2]
	add r2, r5, #0
	add r2, #0x88
	str r4, [r2]
	add r2, r5, #0
	add r2, #0x8c
	str r4, [r2]
	add r2, r5, #0
	add r2, #0x94
	str r0, [r2]
	add r0, r1, #0
	add r0, #0x38
	strb r4, [r5, r0]
	add r0, r1, #0
	add r0, #0x39
	strb r4, [r5, r0]
	add r0, r1, #0
	add r0, #0x3a
	strb r4, [r5, r0]
	add r0, r1, #0
	add r0, #0x3c
	str r4, [r5, r0]
	add r0, r1, #0
	str r4, [r5, #0x38]
	add r0, #0x40
	str r4, [r5, r0]
	add r0, r1, #0
	add r0, #0x44
	str r4, [r5, r0]
	str r4, [r5, #0x10]
	str r4, [r5, #0x18]
	str r4, [r5, #0x20]
	str r4, [r5, #0x28]
	str r4, [r5, #0x30]
	str r4, [r5, #0x3c]
	str r4, [r5, #0x40]
	str r4, [r5, #0x48]
	str r4, [r5, #0x4c]
	str r4, [r5, #0x50]
	add r0, r1, #0
	str r4, [r5, #0x54]
	sub r0, #8
	ldr r2, [r5, r0]
	ldr r0, _02245578 ; =0xFF880000
	mov r7, #6
	and r2, r0
	add r0, r1, #0
	sub r0, #8
	str r2, [r5, r0]
	sub r0, r1, #4
	ldr r2, [r5, r0]
	ldr r0, _0224557C ; =0xFFFFFEA1
	and r2, r0
	sub r0, r1, #4
	str r2, [r5, r0]
	ldr r0, _02245580 ; =0x00003120
	strb r4, [r5, r0]
	mov r0, #0xb5
	lsl r0, r0, #2
	add r6, r5, r0
_02245558:
	mov r0, #0
	add r1, r6, #0
	mov r2, #0x1c
	bl MIi_CpuClearFast
	add r1, r5, r4
	ldr r0, _02245584 ; =0x000021A4
	add r4, r4, #1
	add r6, #0x1c
	strb r7, [r1, r0]
	cmp r4, #4
	blt _02245558
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02245574: .word 0x00002144
_02245578: .word 0xFF880000
_0224557C: .word 0xFFFFFEA1
_02245580: .word 0x00003120
_02245584: .word 0x000021A4

	thumb_func_start MOD11_02245588
MOD11_02245588: ; 0x02245588
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	str r0, [sp]
	mov r4, #0
	add r5, r6, #0
	mov r7, #0xff
_02245594:
	ldr r0, _022455F0 ; =0x0000306C
	add r2, r6, r4
	strh r7, [r5, r0]
	ldr r0, _022455F4 ; =0x000021A0
	mov r1, #6
	strb r1, [r2, r0]
	bl LCRandom
	ldr r1, _022455F8 ; =0x0000310C
	add r4, r4, #1
	strh r0, [r5, r1]
	add r5, r5, #2
	cmp r4, #4
	blt _02245594
	ldr r0, _022455FC ; =0x00002168
	mov r1, #1
	str r1, [r6, r0]
	mov r0, #0x5d
	lsl r0, r0, #2
	str r1, [r6, r0]
	ldr r0, [sp]
	bl MOD11_0222FF74
	mov r1, #2
	tst r0, r1
	bne _022455E4
	add r0, r1, #0
	bl MaskOfFlagNo
	ldr r1, _02245600 ; =0x00003108
	ldrb r2, [r6, r1]
	orr r0, r2
	strb r0, [r6, r1]
	mov r0, #3
	bl MaskOfFlagNo
	ldr r1, _02245600 ; =0x00003108
	ldrb r2, [r6, r1]
	orr r0, r2
	strb r0, [r6, r1]
_022455E4:
	ldr r0, _02245604 ; =0x0000311C
	mov r1, #6
	strb r1, [r6, r0]
	add r0, r0, #1
	strb r1, [r6, r0]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022455F0: .word 0x0000306C
_022455F4: .word 0x000021A0
_022455F8: .word 0x0000310C
_022455FC: .word 0x00002168
_02245600: .word 0x00003108
_02245604: .word 0x0000311C

	thumb_func_start MOD11_02245608
MOD11_02245608: ; 0x02245608
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x58
	str r1, [sp, #4]
	str r0, [sp]
	ldr r1, _0224594C ; =0x00002DC8
	ldr r0, [sp, #4]
	add r4, r2, #0
	add r1, r0, r1
	mov r0, #0xc0
	mul r0, r4
	add r5, r1, r0
	str r5, [sp, #0x14]
	add r3, sp, #0x20
	mov r2, #7
_02245624:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02245624
	ldr r0, [sp]
	bl MOD11_0222FF84
	add r6, r0, #0
	ldr r0, [sp]
	bl MOD11_0222FF74
	ldr r1, [sp, #4]
	lsl r2, r4, #4
	add r1, r1, r2
	ldr r2, _02245950 ; =0x000021A8
	mov r0, #0x27
	str r0, [r1, r2]
	ldr r1, [sp, #4]
	sub r2, #0x6c
	ldr r1, [r1, r2]
	add r0, #0xd9
	tst r0, r1
	bne _022456E2
	mov r5, #0
	cmp r6, #0
	ble _022456BE
	ldr r1, [sp, #4]
	ldr r2, _02245954 ; =0x00002DCC
	add r0, r1, #0
	add r2, r0, r2
	mov r0, #0x18
	mov ip, r0
	mov r7, #3
_02245666:
	ldr r0, _02245958 ; =0x00002DB0
	ldr r3, [r1, r0]
	mov r0, #1
	lsl r0, r0, #0x1a
	tst r0, r3
	beq _02245688
	ldr r0, [r2]
	lsl r0, r0, #0x16
	lsr r0, r0, #0x1e
	cmp r4, r0
	bne _02245688
	ldr r0, _02245958 ; =0x00002DB0
	ldr r3, [r1, r0]
	ldr r0, _0224595C ; =0xFBFFFFFF
	and r3, r0
	ldr r0, _02245958 ; =0x00002DB0
	str r3, [r1, r0]
_02245688:
	mov r0, #0xb7
	lsl r0, r0, #6
	ldr r3, [r1, r0]
	mov r0, #0x18
	tst r0, r3
	beq _022456B4
	ldr r0, [r2]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1e
	cmp r4, r0
	bne _022456B4
	mov r0, #0xb7
	lsl r0, r0, #6
	ldr r0, [r1, r0]
	mov r3, ip
	bic r0, r3
	mov r3, #0xb7
	lsl r3, r3, #6
	str r0, [r1, r3]
	ldr r0, [r2]
	bic r0, r7
	str r0, [r2]
_022456B4:
	add r5, r5, #1
	add r1, #0xc0
	add r2, #0xc0
	cmp r5, r6
	blt _02245666
_022456BE:
	mov r0, #0xc0
	mul r0, r4
	str r0, [sp, #0xc]
	ldr r2, [sp, #4]
	ldr r1, [sp, #0xc]
	mov r0, #0
	add r1, r2, r1
	ldr r2, _02245958 ; =0x00002DB0
	str r0, [r1, r2]
	ldr r1, [sp, #4]
	add r2, #0x10
	add r2, r1, r2
	ldr r1, [sp, #0xc]
	add r1, r2, r1
	str r1, [sp, #0x10]
	ldr r1, [sp, #0xc]
	str r0, [r2, r1]
	b _0224575A
_022456E2:
	mov r0, #0xc0
	mul r0, r4
	str r0, [sp, #0xc]
	ldr r1, _02245958 ; =0x00002DB0
	ldr r0, [sp, #4]
	ldr r2, [sp, #0xc]
	add r0, r0, r1
	ldr r3, [r0, r2]
	ldr r2, _02245960 ; =0x15100007
	and r3, r2
	ldr r2, [sp, #0xc]
	str r3, [r0, r2]
	add r2, r1, #0
	ldr r0, [sp, #4]
	add r2, #0x10
	add r0, r0, r2
	ldr r2, [sp, #0xc]
	add r2, r0, r2
	str r2, [sp, #0x10]
	ldr r2, [sp, #0xc]
	ldr r3, [r0, r2]
	ldr r2, _02245964 ; =0x0FA3843F
	and r3, r2
	ldr r2, [sp, #0xc]
	str r3, [r0, r2]
	mov r2, #0
	cmp r6, #0
	ble _0224575A
	ldr r0, [sp, #4]
	add r1, #0x1c
	add r3, r0, #0
	add r1, r3, r1
	mov r7, #0x18
_02245724:
	mov r3, #0xb7
	lsl r3, r3, #6
	ldr r5, [r0, r3]
	mov r3, #0x18
	tst r3, r5
	beq _02245750
	ldr r3, [r1]
	lsl r3, r3, #0x1e
	lsr r3, r3, #0x1e
	cmp r4, r3
	bne _02245750
	mov r3, #0xb7
	lsl r3, r3, #6
	ldr r5, [r0, r3]
	bic r5, r7
	str r5, [r0, r3]
	ldr r5, [r0, r3]
	mov r3, #0x10
	orr r5, r3
	mov r3, #0xb7
	lsl r3, r3, #6
	str r5, [r0, r3]
_02245750:
	add r2, r2, #1
	add r0, #0xc0
	add r1, #0xc0
	cmp r2, r6
	blt _02245724
_0224575A:
	mov r0, #0
	str r0, [sp, #8]
	cmp r6, #0
	ble _022457C2
	ldr r5, [sp, #4]
	ldr r1, _02245954 ; =0x00002DCC
	add r0, r5, #0
	add r7, r0, r1
_0224576A:
	add r0, r4, #0
	bl MaskOfFlagNo
	ldr r1, _02245958 ; =0x00002DB0
	lsl r0, r0, #0x10
	ldr r1, [r5, r1]
	tst r0, r1
	beq _02245792
	add r0, r4, #0
	bl MaskOfFlagNo
	ldr r1, _02245958 ; =0x00002DB0
	lsl r2, r0, #0x10
	mov r0, #0
	mvn r0, r0
	ldr r1, [r5, r1]
	eor r0, r2
	and r1, r0
	ldr r0, _02245958 ; =0x00002DB0
	str r1, [r5, r0]
_02245792:
	ldr r0, _02245958 ; =0x00002DB0
	ldr r1, [r5, r0]
	mov r0, #0xe
	lsl r0, r0, #0xc
	tst r0, r1
	beq _022457B4
	ldr r0, [r7]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1e
	cmp r4, r0
	bne _022457B4
	ldr r0, _02245958 ; =0x00002DB0
	ldr r1, [r5, r0]
	ldr r0, _02245968 ; =0xFFFF1FFF
	and r1, r0
	ldr r0, _02245958 ; =0x00002DB0
	str r1, [r5, r0]
_022457B4:
	ldr r0, [sp, #8]
	add r5, #0xc0
	add r0, r0, #1
	add r7, #0xc0
	str r0, [sp, #8]
	cmp r0, r6
	blt _0224576A
_022457C2:
	mov r2, #0
	add r1, r2, #0
_022457C6:
	ldr r0, [sp, #0x14]
	strb r1, [r0, r2]
	add r2, r2, #1
	cmp r2, #0x38
	blo _022457C6
	ldr r1, _0224596C ; =0x0000213C
	ldr r0, [sp, #4]
	ldr r1, [r0, r1]
	mov r0, #1
	lsl r0, r0, #8
	tst r0, r1
	beq _0224587A
	ldr r1, [sp, #4]
	ldr r0, [sp, #0xc]
	ldr r2, [sp, #0x38]
	add r0, r1, r0
	ldr r1, _02245970 ; =0x00002DE0
	str r2, [r0, r1]
	ldr r0, [sp, #4]
	sub r1, #0x14
	add r0, r0, r1
	ldr r1, [sp, #0xc]
	mov r2, #3
	ldr r1, [r0, r1]
	bic r1, r2
	ldr r2, [sp, #0x24]
	lsl r2, r2, #0x1e
	lsr r3, r2, #0x1e
	mov r2, #3
	and r2, r3
	orr r2, r1
	ldr r1, [sp, #0xc]
	str r2, [r0, r1]
	ldr r3, [sp, #0x20]
	ldr r1, [sp, #0x14]
	lsl r3, r3, #0x11
	lsr r3, r3, #0x1e
	lsl r3, r3, #0x1e
	ldr r1, [r1]
	ldr r2, _02245974 ; =0xFFFF9FFF
	lsr r3, r3, #0x11
	and r1, r2
	orr r3, r1
	ldr r1, [sp, #0x14]
	str r3, [r1]
	ldr r1, [sp, #0xc]
	ldr r3, [r0, r1]
	asr r1, r2, #5
	ldr r2, [sp, #0x24]
	and r1, r3
	lsl r2, r2, #0x16
	lsr r2, r2, #0x1e
	lsl r2, r2, #0x1e
	lsr r2, r2, #0x16
	orr r2, r1
	ldr r1, [sp, #0xc]
	str r2, [r0, r1]
	ldr r2, [r0, r1]
	ldr r1, _02245968 ; =0xFFFF1FFF
	and r1, r2
	ldr r2, [sp, #0x24]
	lsl r2, r2, #0x10
	lsr r2, r2, #0x1d
	lsl r2, r2, #0x1d
	lsr r2, r2, #0x10
	orr r2, r1
	ldr r1, [sp, #0xc]
	str r2, [r0, r1]
	ldr r3, [sp, #0x24]
	ldr r1, [r0, r1]
	lsl r3, r3, #0xa
	ldr r2, _02245978 ; =0xFFC7FFFF
	lsr r3, r3, #0x1d
	lsl r3, r3, #0x1d
	and r1, r2
	lsr r3, r3, #0xa
	orr r3, r1
	ldr r1, [sp, #0xc]
	str r3, [r0, r1]
	ldr r3, [r0, r1]
	asr r1, r2, #3
	ldr r2, [sp, #0x24]
	and r1, r3
	lsl r2, r2, #0xd
	lsr r2, r2, #0x1d
	lsl r2, r2, #0x1d
	lsr r2, r2, #0xd
	orr r2, r1
	ldr r1, [sp, #0xc]
	str r2, [r0, r1]
_0224587A:
	mov r0, #0xc0
	add r3, r0, #0
	ldr r2, [sp, #4]
	add r3, #0x90
	ldr r2, [r2, r3]
	add r1, r4, #0
	ldr r3, [sp, #4]
	mul r1, r0
	add r5, r0, #0
	add r1, r3, r1
	ldr r3, _0224597C ; =0x00002DD4
	add r2, r2, #1
	str r2, [r1, r3]
	ldr r2, [sp, #4]
	add r5, #0x90
	ldr r2, [r2, r5]
	add r0, #0x90
	add r5, r2, #1
	add r2, r3, #4
	str r5, [r1, r2]
	ldr r1, [sp, #0x14]
	lsl r7, r4, #1
	ldr r2, [r1]
	ldr r1, _02245980 ; =0xBFFFFFFF
	mov r5, #0
	and r1, r2
	ldr r2, [sp, #4]
	ldr r0, [r2, r0]
	add r0, r0, #1
	lsl r0, r0, #0x1f
	lsr r0, r0, #1
	orr r1, r0
	ldr r0, [sp, #0x14]
	str r1, [r0]
	add r0, r2, #0
	ldr r1, _02245984 ; =0x0000305C
	add r3, r0, r7
	add r0, r1, #0
	strh r5, [r3, r1]
	add r0, #8
	strh r5, [r3, r0]
	add r0, r1, #0
	mov r2, #0xff
	add r0, #0x10
	strh r2, [r3, r0]
	add r0, r1, #0
	add r0, #0x18
	strh r5, [r3, r0]
	add r0, r1, #0
	add r0, #0x20
	strh r5, [r3, r0]
	add r0, r1, #0
	add r0, #0x28
	strh r5, [r3, r0]
	ldr r0, [sp, #4]
	lsl r2, r4, #3
	add r0, r0, r2
	add r2, r1, #0
	add r2, #0x30
	strh r5, [r0, r2]
	add r2, r1, #0
	add r2, #0x32
	strh r5, [r0, r2]
	add r2, r1, #0
	add r2, #0x34
	strh r5, [r0, r2]
	add r2, r1, #0
	add r2, #0x36
	strh r5, [r0, r2]
	add r0, r1, #0
	add r0, #0x50
	strh r5, [r3, r0]
	add r0, r1, #0
	add r0, #0x68
	strh r5, [r3, r0]
	add r0, r1, #0
	add r0, #0x70
	strh r5, [r3, r0]
	add r0, r1, #0
	add r0, #0x78
	strh r5, [r3, r0]
	add r1, #0x80
	add r0, r4, #0
	strh r5, [r3, r1]
	bl MaskOfFlagNo
	mov r1, #6
	lsl r3, r0, #8
	sub r0, r5, #1
	ldr r2, [sp, #4]
	lsl r1, r1, #6
	ldr r2, [r2, r1]
	eor r0, r3
	and r2, r0
	ldr r0, [sp, #4]
	str r2, [r0, r1]
	ldr r0, [sp, #0x10]
	ldr r1, [r0]
	mov r0, #2
	lsl r0, r0, #0x16
	tst r0, r1
	beq _022459A2
	ldr r0, _02245988 ; =0x00002D42
	b _0224598C
	nop
_0224594C: .word 0x00002DC8
_02245950: .word 0x000021A8
_02245954: .word 0x00002DCC
_02245958: .word 0x00002DB0
_0224595C: .word 0xFBFFFFFF
_02245960: .word 0x15100007
_02245964: .word 0x0FA3843F
_02245968: .word 0xFFFF1FFF
_0224596C: .word 0x0000213C
_02245970: .word 0x00002DE0
_02245974: .word 0xFFFF9FFF
_02245978: .word 0xFFC7FFFF
_0224597C: .word 0x00002DD4
_02245980: .word 0xBFFFFFFF
_02245984: .word 0x0000305C
_02245988: .word 0x00002D42
_0224598C:
	ldr r1, [sp, #4]
	add r5, r1, r0
	ldr r1, [sp, #0xc]
	ldrh r3, [r5, r1]
	add r1, r0, #2
	ldr r0, [sp, #4]
	add r2, r0, r1
	ldr r0, [sp, #0xc]
	ldrh r1, [r2, r0]
	strh r1, [r5, r0]
	strh r3, [r2, r0]
_022459A2:
	mov r5, #0
	cmp r6, #0
	ble _022459E6
	ldr r0, [sp, #4]
	str r0, [sp, #0x18]
	add r7, r0, r7
_022459AE:
	cmp r5, r4
	beq _022459D2
	ldr r0, [sp]
	add r1, r5, #0
	bl MOD11_02230270
	str r0, [sp, #0x1c]
	ldr r0, [sp]
	add r1, r4, #0
	bl MOD11_02230270
	ldr r1, [sp, #0x1c]
	cmp r1, r0
	beq _022459D2
	ldr r1, [sp, #0x18]
	ldr r0, _02245A08 ; =0x00003084
	mov r2, #0
	strh r2, [r1, r0]
_022459D2:
	ldr r0, _02245A0C ; =0x0000308C
	mov r1, #0
	strh r1, [r7, r0]
	ldr r0, [sp, #0x18]
	add r5, r5, #1
	add r0, r0, #2
	str r0, [sp, #0x18]
	add r7, #8
	cmp r5, r6
	blt _022459AE
_022459E6:
	lsl r1, r4, #0x18
	ldr r0, [sp, #4]
	lsr r1, r1, #0x18
	bl MOD11_0224C818
	lsl r1, r4, #0x18
	ldr r0, [sp, #4]
	lsr r1, r1, #0x18
	bl MOD11_0224C830
	lsl r1, r4, #0x18
	ldr r0, [sp, #4]
	lsr r1, r1, #0x18
	bl MOD11_0224C83C
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02245A08: .word 0x00003084
_02245A0C: .word 0x0000308C

	thumb_func_start MOD11_02245A10
MOD11_02245A10: ; 0x02245A10
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r1, [sp, #4]
	str r0, [sp]
	add r5, r2, #0
	bl MOD11_0222FF84
	str r0, [sp, #0xc]
	mov r0, #0xc0
	mul r0, r5
	ldr r1, [sp, #4]
	str r0, [sp, #8]
	add r3, r1, r0
	ldr r0, _02245C34 ; =0x00002D58
	mov r2, #0
	mov r1, #6
_02245A30:
	add r2, r2, #1
	strb r1, [r3, r0]
	add r3, r3, #1
	cmp r2, #8
	blt _02245A30
	mov r0, #0xc0
	add r1, r5, #0
	mul r1, r0
	ldr r0, [sp, #4]
	mov r7, #0
	add r2, r0, r1
	ldr r1, _02245C38 ; =0x00002DB0
	add r0, r1, #0
	str r7, [r2, r1]
	add r0, #0x10
	str r7, [r2, r0]
	ldr r0, [sp, #0xc]
	cmp r0, #0
	ble _02245AD6
	ldr r4, [sp, #4]
	add r1, #0x1c
	add r0, r4, #0
	add r6, r0, r1
_02245A5E:
	ldr r0, _02245C38 ; =0x00002DB0
	ldr r1, [r4, r0]
	mov r0, #1
	lsl r0, r0, #0x1a
	tst r0, r1
	beq _02245A80
	ldr r0, [r6]
	lsl r0, r0, #0x16
	lsr r0, r0, #0x1e
	cmp r5, r0
	bne _02245A80
	ldr r0, _02245C38 ; =0x00002DB0
	ldr r1, [r4, r0]
	ldr r0, _02245C3C ; =0xFBFFFFFF
	and r1, r0
	ldr r0, _02245C38 ; =0x00002DB0
	str r1, [r4, r0]
_02245A80:
	add r0, r5, #0
	bl MaskOfFlagNo
	ldr r1, _02245C38 ; =0x00002DB0
	lsl r0, r0, #0x10
	ldr r1, [r4, r1]
	tst r0, r1
	beq _02245AA8
	add r0, r5, #0
	bl MaskOfFlagNo
	ldr r1, _02245C38 ; =0x00002DB0
	lsl r2, r0, #0x10
	mov r0, #0
	mvn r0, r0
	ldr r1, [r4, r1]
	eor r0, r2
	and r1, r0
	ldr r0, _02245C38 ; =0x00002DB0
	str r1, [r4, r0]
_02245AA8:
	ldr r0, _02245C38 ; =0x00002DB0
	ldr r1, [r4, r0]
	mov r0, #0xe
	lsl r0, r0, #0xc
	tst r0, r1
	beq _02245ACA
	ldr r0, [r6]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1e
	cmp r5, r0
	bne _02245ACA
	ldr r0, _02245C38 ; =0x00002DB0
	ldr r1, [r4, r0]
	ldr r0, _02245C40 ; =0xFFFF1FFF
	and r1, r0
	ldr r0, _02245C38 ; =0x00002DB0
	str r1, [r4, r0]
_02245ACA:
	ldr r0, [sp, #0xc]
	add r7, r7, #1
	add r4, #0xc0
	add r6, #0xc0
	cmp r7, r0
	blt _02245A5E
_02245AD6:
	ldr r1, _02245C44 ; =0x00002DC8
	ldr r0, [sp, #4]
	add r1, r0, r1
	ldr r0, [sp, #8]
	add r6, r1, r0
	mov r1, #0
	add r0, r1, #0
_02245AE4:
	strb r0, [r6, r1]
	add r1, r1, #1
	cmp r1, #0x38
	blo _02245AE4
	mov r2, #0x75
	ldr r1, [sp, #4]
	lsl r2, r2, #2
	add r2, r1, r2
	lsl r1, r5, #6
	add r1, r2, r1
	mov r4, #0
_02245AFA:
	strb r4, [r1, r0]
	add r0, r0, #1
	cmp r0, #0x40
	blo _02245AFA
	mov r2, #0xc0
	add r3, r2, #0
	ldr r0, [sp, #4]
	add r3, #0x90
	ldr r0, [r0, r3]
	add r1, r5, #0
	ldr r3, [sp, #4]
	mul r1, r2
	add r3, r3, r1
	add r1, r2, #0
	ldr r7, _02245C48 ; =0x00002DD4
	add r0, r0, #1
	str r0, [r3, r7]
	ldr r0, [sp, #4]
	add r1, #0x90
	ldr r0, [r0, r1]
	add r1, r7, #4
	add r0, r0, #1
	str r0, [r3, r1]
	ldr r1, [r6]
	ldr r0, _02245C4C ; =0xBFFFFFFF
	add r2, #0x90
	and r0, r1
	ldr r1, [sp, #4]
	mov r3, #0xff
	ldr r1, [r1, r2]
	add r1, r1, #1
	lsl r1, r1, #0x1f
	lsr r1, r1, #1
	orr r0, r1
	str r0, [r6]
	ldr r0, [sp, #4]
	lsl r6, r5, #1
	add r2, r0, r6
	ldr r0, _02245C50 ; =0x0000305C
	add r1, r0, #0
	strh r4, [r2, r0]
	add r1, #8
	strh r4, [r2, r1]
	add r1, r0, #0
	add r1, #0x10
	strh r3, [r2, r1]
	add r1, r0, #0
	add r1, #0x18
	strh r4, [r2, r1]
	add r1, r0, #0
	add r1, #0x20
	strh r4, [r2, r1]
	add r1, r0, #0
	add r1, #0x28
	strh r4, [r2, r1]
	ldr r1, [sp, #4]
	lsl r3, r5, #3
	add r1, r1, r3
	add r3, r0, #0
	add r3, #0x30
	strh r4, [r1, r3]
	add r3, r0, #0
	add r3, #0x32
	strh r4, [r1, r3]
	add r3, r0, #0
	add r3, #0x34
	strh r4, [r1, r3]
	add r3, r0, #0
	add r3, #0x36
	strh r4, [r1, r3]
	add r1, r0, #0
	add r1, #0x50
	strh r4, [r2, r1]
	add r1, r0, #0
	add r1, #0x68
	strh r4, [r2, r1]
	add r1, r0, #0
	add r1, #0x70
	strh r4, [r2, r1]
	add r1, r0, #0
	add r1, #0x78
	strh r4, [r2, r1]
	add r0, #0x80
	strh r4, [r2, r0]
	add r0, r5, #0
	bl MaskOfFlagNo
	mov r1, #6
	lsl r3, r0, #8
	mov r0, #0
	mvn r0, r0
	ldr r2, [sp, #4]
	lsl r1, r1, #6
	ldr r2, [r2, r1]
	eor r0, r3
	and r2, r0
	ldr r0, [sp, #4]
	mov r4, #0
	str r2, [r0, r1]
	ldr r0, [sp, #0xc]
	cmp r0, #0
	ble _02245C00
	ldr r7, [sp, #4]
	add r0, r7, #0
	add r6, r0, r6
_02245BCC:
	cmp r4, r5
	beq _02245BEE
	ldr r0, [sp]
	add r1, r4, #0
	bl MOD11_02230270
	str r0, [sp, #0x10]
	ldr r0, [sp]
	add r1, r5, #0
	bl MOD11_02230270
	ldr r1, [sp, #0x10]
	cmp r1, r0
	beq _02245BEE
	ldr r0, _02245C54 ; =0x00003084
	mov r1, #0
	strh r1, [r7, r0]
_02245BEE:
	ldr r0, _02245C58 ; =0x0000308C
	mov r1, #0
	strh r1, [r6, r0]
	ldr r0, [sp, #0xc]
	add r4, r4, #1
	add r7, r7, #2
	add r6, #8
	cmp r4, r0
	blt _02245BCC
_02245C00:
	mov r1, #0x4f
	ldr r0, [sp, #4]
	lsl r1, r1, #2
	add r3, r0, r1
	lsl r2, r5, #2
	ldr r1, [r3, r2]
	mov r0, #1
	bic r1, r0
	str r1, [r3, r2]
	lsl r1, r5, #0x18
	ldr r0, [sp, #4]
	lsr r1, r1, #0x18
	bl MOD11_0224C818
	lsl r1, r5, #0x18
	ldr r0, [sp, #4]
	lsr r1, r1, #0x18
	bl MOD11_0224C830
	lsl r1, r5, #0x18
	ldr r0, [sp, #4]
	lsr r1, r1, #0x18
	bl MOD11_0224C83C
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02245C34: .word 0x00002D58
_02245C38: .word 0x00002DB0
_02245C3C: .word 0xFBFFFFFF
_02245C40: .word 0xFFFF1FFF
_02245C44: .word 0x00002DC8
_02245C48: .word 0x00002DD4
_02245C4C: .word 0xBFFFFFFF
_02245C50: .word 0x0000305C
_02245C54: .word 0x00003084
_02245C58: .word 0x0000308C

	thumb_func_start MOD11_02245C5C
MOD11_02245C5C: ; 0x02245C5C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #0x75
	add r5, r1, #0
	lsl r0, r0, #2
	add r7, r5, r0
	mov r0, #0xd1
	lsl r0, r0, #2
	add r6, r5, r0
	mov r0, #8
	add r4, r5, #0
	str r0, [sp, #8]
_02245C7A:
	mov r0, #0
	add r1, r7, #0
	mov r2, #0x40
	bl MIi_CpuClearFast
	mov r0, #0
	add r1, r6, #0
	mov r2, #4
	bl MIi_CpuClearFast
	ldr r0, _02245D24 ; =0x00002DB0
	ldr r1, [r4, r0]
	ldr r0, [sp, #8]
	bic r1, r0
	ldr r0, _02245D24 ; =0x00002DB0
	str r1, [r4, r0]
	add r0, #0x20
	ldr r0, [r4, r0]
	add r1, r0, #1
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	cmp r1, r0
	bge _02245CB6
	ldr r0, _02245D24 ; =0x00002DB0
	ldr r1, [r4, r0]
	ldr r0, _02245D28 ; =0xFFBFFFFF
	and r1, r0
	ldr r0, _02245D24 ; =0x00002DB0
	str r1, [r4, r0]
_02245CB6:
	ldr r0, _02245D2C ; =0x00002DAC
	ldr r1, [r4, r0]
	mov r0, #7
	tst r0, r1
	beq _02245CD6
	ldr r0, _02245D24 ; =0x00002DB0
	ldr r1, [r4, r0]
	mov r0, #1
	lsl r0, r0, #0xc
	tst r0, r1
	beq _02245CD6
	ldr r0, [sp]
	ldr r2, [sp, #4]
	add r1, r5, #0
	bl MOD11_022451F0
_02245CD6:
	ldr r0, _02245D2C ; =0x00002DAC
	ldr r1, [r4, r0]
	mov r0, #7
	tst r0, r1
	beq _02245CF8
	ldr r0, _02245D24 ; =0x00002DB0
	ldr r1, [r4, r0]
	mov r0, #3
	lsl r0, r0, #0xa
	tst r0, r1
	beq _02245CF8
	ldr r0, _02245D24 ; =0x00002DB0
	ldr r1, [r4, r0]
	ldr r0, _02245D30 ; =0xFFFFF3FF
	and r1, r0
	ldr r0, _02245D24 ; =0x00002DB0
	str r1, [r4, r0]
_02245CF8:
	ldr r0, [sp, #4]
	add r7, #0x40
	add r0, r0, #1
	add r6, r6, #4
	add r4, #0xc0
	str r0, [sp, #4]
	cmp r0, #4
	blt _02245C7A
	mov r2, #0x71
	lsl r2, r2, #2
	ldr r0, [r5, r2]
	ldr r1, _02245D34 ; =0xFFEFFFFF
	and r0, r1
	str r0, [r5, r2]
	add r0, r2, #0
	add r0, #8
	ldr r0, [r5, r0]
	add r2, #8
	and r0, r1
	str r0, [r5, r2]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02245D24: .word 0x00002DB0
_02245D28: .word 0xFFBFFFFF
_02245D2C: .word 0x00002DAC
_02245D30: .word 0xFFFFF3FF
_02245D34: .word 0xFFEFFFFF

	thumb_func_start MOD11_02245D38
MOD11_02245D38: ; 0x02245D38
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	str r0, [sp]
	ldr r0, [sp, #0x70]
	add r7, r1, #0
	str r0, [sp, #0x70]
	str r2, [sp, #4]
	add r0, r7, #0
	add r1, r2, #0
	add r5, r3, #0
	bl MOD11_02249D90
	str r0, [sp, #0x34]
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	add r4, r7, r1
	str r1, [sp, #0x38]
	ldr r0, [sp, #0x70]
	mov r1, #1
	and r0, r1
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x70]
	mov r1, #2
	and r0, r1
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x70]
	mov r1, #4
	and r0, r1
	str r0, [sp, #0x24]
	ldr r0, [sp, #4]
	mov r1, #8
	lsl r0, r0, #1
	add r0, r7, r0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x70]
	mov r2, #0x10
	and r0, r1
	ldr r1, _02245F50 ; =0x00002DC8
	str r0, [sp, #0x1c]
	add r0, r7, r1
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x70]
	sub r1, #0x88
	and r0, r2
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x70]
	mov r2, #0x20
	and r0, r2
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x70]
	mov r2, #0x40
	and r0, r2
	str r0, [sp, #0x10]
	ldr r2, [sp, #0x70]
	mov r0, #0x80
	and r2, r0
	str r2, [sp, #0xc]
	lsl r2, r0, #2
	ldr r0, [sp, #0x70]
	mov r6, #0
	and r0, r2
	str r0, [sp, #8]
	add r0, r7, r1
	str r0, [sp, #0x40]
	ldr r0, _02245F54 ; =0x00002DE8
	str r4, [sp, #0x30]
	add r0, r4, r0
	str r0, [sp, #0x44]
	ldr r0, _02245F58 ; =0x00002DB0
	add r0, r4, r0
	str r0, [sp, #0x48]
	ldr r0, _02245F5C ; =0x00002DEC
	add r0, r4, r0
	str r0, [sp, #0x4c]
	ldr r0, _02245F60 ; =0x00002DF8
	add r0, r4, r0
	str r0, [sp, #0x50]
	ldr r0, _02245F60 ; =0x00002DF8
	add r0, r4, r0
	str r0, [sp, #0x58]
	ldr r0, _02245F60 ; =0x00002DF8
	add r0, r4, r0
	str r0, [sp, #0x54]
_02245DE0:
	ldr r0, _02245F64 ; =0x00002D4C
	ldrh r0, [r4, r0]
	cmp r0, #0
	bne _02245DF6
	ldr r0, [sp, #0x2c]
	cmp r0, #0
	beq _02245DF6
	add r0, r6, #0
	bl MaskOfFlagNo
	orr r5, r0
_02245DF6:
	ldr r1, [sp, #0x30]
	ldr r0, _02245F68 ; =0x00002D6C
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _02245E0E
	ldr r0, [sp, #0x28]
	cmp r0, #0
	beq _02245E0E
	add r0, r6, #0
	bl MaskOfFlagNo
	orr r5, r0
_02245E0E:
	ldr r0, [sp, #0x44]
	ldrh r1, [r0]
	ldr r0, _02245F64 ; =0x00002D4C
	ldrh r0, [r4, r0]
	cmp r1, r0
	bne _02245E28
	ldr r0, [sp, #0x24]
	cmp r0, #0
	beq _02245E28
	add r0, r6, #0
	bl MaskOfFlagNo
	orr r5, r0
_02245E28:
	ldr r1, [sp, #0x20]
	ldr r0, _02245F6C ; =0x0000307C
	ldrh r1, [r1, r0]
	ldr r0, _02245F64 ; =0x00002D4C
	ldrh r0, [r4, r0]
	cmp r1, r0
	bne _02245E50
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	beq _02245E50
	ldr r0, [sp, #0x48]
	ldr r1, [r0]
	mov r0, #2
	lsl r0, r0, #0x1e
	tst r0, r1
	beq _02245E50
	add r0, r6, #0
	bl MaskOfFlagNo
	orr r5, r0
_02245E50:
	ldr r1, [sp, #0x3c]
	ldr r0, [sp, #0x38]
	ldr r0, [r1, r0]
	lsl r0, r0, #0x15
	lsr r0, r0, #0x1d
	beq _02245E7A
	ldr r0, [sp, #0x18]
	cmp r0, #0
	beq _02245E7A
	ldr r0, _02245F64 ; =0x00002D4C
	ldrh r0, [r4, r0]
	lsl r0, r0, #4
	add r1, r7, r0
	ldr r0, _02245F70 ; =0x000003E1
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _02245E7A
	add r0, r6, #0
	bl MaskOfFlagNo
	orr r5, r0
_02245E7A:
	ldr r3, _02245F64 ; =0x00002D4C
	ldr r0, [sp]
	ldrh r3, [r4, r3]
	ldr r2, [sp, #4]
	add r1, r7, #0
	bl MOD11_022471C4
	cmp r0, #0
	beq _02245E9A
	ldr r0, [sp, #0x14]
	cmp r0, #0
	beq _02245E9A
	add r0, r6, #0
	bl MaskOfFlagNo
	orr r5, r0
_02245E9A:
	ldr r3, _02245F64 ; =0x00002D4C
	ldr r0, [sp]
	ldrh r3, [r4, r3]
	ldr r2, [sp, #4]
	add r1, r7, #0
	bl MOD11_02247314
	cmp r0, #0
	beq _02245EBA
	ldr r0, [sp, #0x10]
	cmp r0, #0
	beq _02245EBA
	add r0, r6, #0
	bl MaskOfFlagNo
	orr r5, r0
_02245EBA:
	ldr r3, _02245F64 ; =0x00002D4C
	ldr r0, [sp]
	ldrh r3, [r4, r3]
	ldr r2, [sp, #4]
	add r1, r7, #0
	bl MOD11_02247348
	cmp r0, #0
	beq _02245EDA
	ldr r0, [sp, #0xc]
	cmp r0, #0
	beq _02245EDA
	add r0, r6, #0
	bl MaskOfFlagNo
	orr r5, r0
_02245EDA:
	ldr r0, [sp, #0x4c]
	ldrh r1, [r0]
	cmp r1, #0
	beq _02245EF2
	ldr r0, _02245F64 ; =0x00002D4C
	ldrh r0, [r4, r0]
	cmp r1, r0
	beq _02245EF2
	add r0, r6, #0
	bl MaskOfFlagNo
	orr r5, r0
_02245EF2:
	ldr r0, [sp, #0x34]
	cmp r0, #0x36
	beq _02245F00
	cmp r0, #0x72
	beq _02245F00
	cmp r0, #0x7c
	bne _02245F38
_02245F00:
	ldr r0, [sp, #8]
	cmp r0, #0
	beq _02245F38
	ldr r1, [sp, #0x40]
	ldr r0, [sp, #0x38]
	add r0, r1, r0
	ldr r1, [sp, #0x50]
	ldrh r1, [r1]
	bl MOD11_022461AC
	cmp r0, #4
	bne _02245F20
	ldr r0, [sp, #0x54]
	mov r1, #0
	strh r1, [r0]
	b _02245F38
_02245F20:
	ldr r0, [sp, #0x58]
	ldrh r1, [r0]
	cmp r1, #0
	beq _02245F38
	ldr r0, _02245F64 ; =0x00002D4C
	ldrh r0, [r4, r0]
	cmp r1, r0
	beq _02245F38
	add r0, r6, #0
	bl MaskOfFlagNo
	orr r5, r0
_02245F38:
	ldr r0, [sp, #0x30]
	add r6, r6, #1
	add r0, r0, #1
	add r4, r4, #2
	str r0, [sp, #0x30]
	cmp r6, #4
	bge _02245F48
	b _02245DE0
_02245F48:
	add r0, r5, #0
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	nop
_02245F50: .word 0x00002DC8
_02245F54: .word 0x00002DE8
_02245F58: .word 0x00002DB0
_02245F5C: .word 0x00002DEC
_02245F60: .word 0x00002DF8
_02245F64: .word 0x00002D4C
_02245F68: .word 0x00002D6C
_02245F6C: .word 0x0000307C
_02245F70: .word 0x000003E1

	thumb_func_start MOD11_02245F74
MOD11_02245F74: ; 0x02245F74
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r7, r3, #0
	mov r3, #1
	str r3, [sp, #8]
	mov r3, #4
	str r3, [sp]
	mov r3, #0
	str r0, [sp, #4]
	add r5, r1, #0
	add r6, r2, #0
	ldr r4, [sp, #0x40]
	bl MOD11_02245D38
	str r0, [sp, #0xc]
	add r0, r7, #0
	bl MaskOfFlagNo
	ldr r1, [sp, #0xc]
	tst r0, r1
	beq _02245FC6
	mov r0, #0xa
	strb r0, [r4, #1]
	ldr r0, _02246188 ; =0x00000261
	add r1, r6, #0
	strh r0, [r4, #2]
	add r0, r5, #0
	bl MOD11_0224682C
	str r0, [r4, #4]
	mov r0, #0xc0
	mul r0, r6
	add r1, r5, r0
	lsl r0, r7, #1
	add r1, r1, r0
	ldr r0, _0224618C ; =0x00002D4C
	ldrh r0, [r1, r0]
	str r0, [r4, #8]
	mov r0, #0
	str r0, [sp, #8]
	b _02246182
_02245FC6:
	mov r0, #8
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	add r2, r6, #0
	mov r3, #0
	bl MOD11_02245D38
	str r0, [sp, #0x10]
	add r0, r7, #0
	bl MaskOfFlagNo
	ldr r1, [sp, #0x10]
	tst r0, r1
	beq _02245FFE
	mov r0, #2
	strb r0, [r4, #1]
	mov r0, #0x99
	lsl r0, r0, #2
	strh r0, [r4, #2]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD11_0224682C
	str r0, [r4, #4]
	mov r0, #0
	str r0, [sp, #8]
	b _02246182
_02245FFE:
	mov r0, #0x10
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	add r2, r6, #0
	mov r3, #0
	bl MOD11_02245D38
	str r0, [sp, #0x14]
	add r0, r7, #0
	bl MaskOfFlagNo
	ldr r1, [sp, #0x14]
	tst r0, r1
	beq _02246044
	mov r0, #0xa
	strb r0, [r4, #1]
	ldr r0, _02246190 ; =0x00000265
	add r1, r6, #0
	strh r0, [r4, #2]
	add r0, r5, #0
	bl MOD11_0224682C
	str r0, [r4, #4]
	mov r0, #0xc0
	mul r0, r6
	add r1, r5, r0
	lsl r0, r7, #1
	add r1, r1, r0
	ldr r0, _0224618C ; =0x00002D4C
	ldrh r0, [r1, r0]
	str r0, [r4, #8]
	mov r0, #0
	str r0, [sp, #8]
	b _02246182
_02246044:
	mov r0, #0x20
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	add r2, r6, #0
	mov r3, #0
	bl MOD11_02245D38
	str r0, [sp, #0x18]
	add r0, r7, #0
	bl MaskOfFlagNo
	ldr r1, [sp, #0x18]
	tst r0, r1
	beq _0224608C
	mov r0, #0xa
	strb r0, [r4, #1]
	mov r0, #0x9a
	lsl r0, r0, #2
	strh r0, [r4, #2]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD11_0224682C
	str r0, [r4, #4]
	mov r0, #0xc0
	mul r0, r6
	add r1, r5, r0
	lsl r0, r7, #1
	add r1, r1, r0
	ldr r0, _0224618C ; =0x00002D4C
	ldrh r0, [r1, r0]
	str r0, [r4, #8]
	mov r0, #0
	str r0, [sp, #8]
	b _02246182
_0224608C:
	mov r0, #0x40
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	add r2, r6, #0
	mov r3, #0
	bl MOD11_02245D38
	str r0, [sp, #0x1c]
	add r0, r7, #0
	bl MaskOfFlagNo
	ldr r1, [sp, #0x1c]
	tst r0, r1
	beq _022460D2
	mov r0, #0xa
	strb r0, [r4, #1]
	ldr r0, _02246194 ; =0x000003E9
	add r1, r6, #0
	strh r0, [r4, #2]
	add r0, r5, #0
	bl MOD11_0224682C
	str r0, [r4, #4]
	mov r0, #0xc0
	mul r0, r6
	add r1, r5, r0
	lsl r0, r7, #1
	add r1, r1, r0
	ldr r0, _0224618C ; =0x00002D4C
	ldrh r0, [r1, r0]
	str r0, [r4, #8]
	mov r0, #0
	str r0, [sp, #8]
	b _02246182
_022460D2:
	mov r0, #0x80
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	add r2, r6, #0
	mov r3, #0
	bl MOD11_02245D38
	str r0, [sp, #0x20]
	add r0, r7, #0
	bl MaskOfFlagNo
	ldr r1, [sp, #0x20]
	tst r0, r1
	beq _0224611C
	mov r0, #0x22
	strb r0, [r4, #1]
	ldr r0, _02246198 ; =0x00000421
	add r1, r6, #0
	strh r0, [r4, #2]
	add r0, r5, #0
	bl MOD11_0224682C
	str r0, [r4, #4]
	ldr r0, _0224619C ; =0x00000179
	str r0, [r4, #8]
	mov r0, #0xc0
	mul r0, r6
	add r1, r5, r0
	lsl r0, r7, #1
	add r1, r1, r0
	ldr r0, _0224618C ; =0x00002D4C
	ldrh r0, [r1, r0]
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [sp, #8]
	b _02246182
_0224611C:
	mov r0, #2
	lsl r0, r0, #8
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	add r2, r6, #0
	mov r3, #0
	bl MOD11_02245D38
	str r0, [sp, #0x24]
	add r0, r7, #0
	bl MaskOfFlagNo
	ldr r1, [sp, #0x24]
	tst r0, r1
	beq _0224615C
	mov r0, #0x18
	strb r0, [r4, #1]
	ldr r0, _022461A0 ; =0x0000038F
	strh r0, [r4, #2]
	mov r0, #0xc0
	mul r0, r6
	add r2, r5, r0
	ldr r0, _022461A4 ; =0x00002DB8
	ldrh r1, [r2, r0]
	add r0, #0x40
	str r1, [r4, #4]
	ldrh r0, [r2, r0]
	str r0, [r4, #8]
	mov r0, #0
	str r0, [sp, #8]
	b _02246182
_0224615C:
	mov r0, #2
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	add r2, r6, #0
	mov r3, #0
	bl MOD11_02245D38
	add r5, r0, #0
	add r0, r7, #0
	bl MaskOfFlagNo
	tst r0, r5
	beq _02246182
	mov r0, #0
	str r0, [sp, #8]
	strb r0, [r4, #1]
	ldr r0, _022461A8 ; =0x00000337
	strh r0, [r4, #2]
_02246182:
	ldr r0, [sp, #8]
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02246188: .word 0x00000261
_0224618C: .word 0x00002D4C
_02246190: .word 0x00000265
_02246194: .word 0x000003E9
_02246198: .word 0x00000421
_0224619C: .word 0x00000179
_022461A0: .word 0x0000038F
_022461A4: .word 0x00002DB8
_022461A8: .word 0x00000337

	thumb_func_start MOD11_022461AC
MOD11_022461AC: ; 0x022461AC
	mov r3, #0
_022461AE:
	ldrh r2, [r0, #0xc]
	cmp r1, r2
	beq _022461BC
	add r3, r3, #1
	add r0, r0, #2
	cmp r3, #4
	blt _022461AE
_022461BC:
	add r0, r3, #0
	bx lr

	thumb_func_start MOD11_022461C0
MOD11_022461C0: ; 0x022461C0
	push {r4, r5, r6, lr}
	add r6, r2, #0
	add r1, r6, #0
	add r5, r0, #0
	add r4, r3, #0
	bl MOD11_02249D90
	mov r1, #1
	cmp r0, #0x69
	beq _022461E6
	mov r0, #0xc0
	mul r0, r6
	add r2, r5, r0
	mov r0, #0xb7
	lsl r0, r0, #6
	ldr r2, [r2, r0]
	lsl r0, r1, #0xa
	tst r0, r2
	beq _022461FC
_022461E6:
	lsl r0, r4, #1
	add r2, r4, r0
	ldr r0, _0224626C ; =MOD11_0225E379
	ldrb r0, [r0, r2]
	cmp r0, #2
	bne _022461FC
	ldr r0, _02246270 ; =MOD11_0225E37A
	ldrb r0, [r0, r2]
	cmp r0, #0
	bne _022461FC
	mov r1, #0
_022461FC:
	lsl r0, r6, #6
	add r2, r5, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r2, r0]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	beq _0224621A
	lsl r0, r4, #1
	add r2, r4, r0
	ldr r0, _0224626C ; =MOD11_0225E379
	ldrb r0, [r0, r2]
	cmp r0, #2
	bne _0224621A
	mov r1, #0
_0224621A:
	mov r0, #6
	lsl r0, r0, #6
	ldr r2, [r5, r0]
	mov r0, #7
	lsl r0, r0, #0xc
	tst r0, r2
	beq _0224623E
	lsl r0, r4, #1
	add r2, r4, r0
	ldr r0, _0224626C ; =MOD11_0225E379
	ldrb r0, [r0, r2]
	cmp r0, #2
	bne _0224623E
	ldr r0, _02246270 ; =MOD11_0225E37A
	ldrb r0, [r0, r2]
	cmp r0, #0
	bne _0224623E
	mov r1, #0
_0224623E:
	mov r0, #0xc0
	mul r0, r6
	add r2, r5, r0
	mov r0, #0xb7
	lsl r0, r0, #6
	ldr r2, [r2, r0]
	mov r0, #1
	lsl r0, r0, #0x16
	tst r0, r2
	beq _02246268
	lsl r0, r4, #1
	add r2, r4, r0
	ldr r0, _0224626C ; =MOD11_0225E379
	ldrb r0, [r0, r2]
	cmp r0, #0x11
	bne _02246268
	ldr r0, _02246270 ; =MOD11_0225E37A
	ldrb r0, [r0, r2]
	cmp r0, #0
	bne _02246268
	mov r1, #0
_02246268:
	add r0, r1, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224626C: .word MOD11_0225E379
_02246270: .word MOD11_0225E37A

	thumb_func_start MOD11_02246274
MOD11_02246274: ; 0x02246274
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	ldr r0, [sp, #0x50]
	add r5, r1, #0
	str r0, [sp, #0x50]
	ldr r0, [sp, #0x54]
	str r2, [sp, #8]
	str r0, [sp, #0x54]
	add r0, r2, #0
	add r4, r3, #0
	ldr r7, [sp, #0x48]
	ldr r6, [sp, #0x4c]
	cmp r0, #0xa5
	bne _02246296
	ldr r0, [sp, #0x50]
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
_02246296:
	add r0, r5, #0
	add r1, r7, #0
	bl MOD11_02249D90
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x24]
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #0
	bl MOD11_02249DA4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x1c]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD11_02249D90
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x20]
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0
	bl MOD11_02249DA4
	add r0, r5, #0
	add r1, r7, #0
	bl MOD11_02246D1C
	cmp r0, #0x60
	bne _022462DE
	mov r0, #0
	str r0, [sp, #0x28]
	b _022462F6
_022462DE:
	cmp r4, #0
	beq _022462EA
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x28]
	b _022462F6
_022462EA:
	ldr r0, [sp, #8]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _02246588 ; =0x000003E2
	ldrb r0, [r1, r0]
	str r0, [sp, #0x28]
_022462F6:
	ldr r0, [sp, #8]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _0224658C ; =0x000003E1
	ldrb r0, [r1, r0]
	str r0, [sp, #0x14]
	ldr r0, _02246590 ; =0x0000213C
	ldr r1, [r5, r0]
	mov r0, #2
	lsl r0, r0, #0xa
	tst r0, r1
	bne _02246354
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #0x1b
	mov r3, #0
	bl MOD11_02243420
	ldr r1, [sp, #0x28]
	cmp r1, r0
	beq _02246332
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #0x1c
	mov r3, #0
	bl MOD11_02243420
	ldr r1, [sp, #0x28]
	cmp r1, r0
	bne _02246354
_02246332:
	add r0, r5, #0
	add r1, r7, #0
	bl MOD11_02246D1C
	cmp r0, #0x5b
	bne _02246346
	ldr r0, [sp, #0x50]
	lsl r0, r0, #1
	str r0, [sp, #0x50]
	b _02246354
_02246346:
	ldr r1, [sp, #0x50]
	mov r0, #0xf
	mul r0, r1
	mov r1, #0xa
	bl _s32_div_f
	str r0, [sp, #0x50]
_02246354:
	add r0, r5, #0
	add r1, r7, #0
	add r2, r6, #0
	mov r3, #0x1a
	bl MOD11_02246D84
	cmp r0, #1
	bne _02246380
	ldr r0, [sp, #0x28]
	cmp r0, #4
	bne _02246380
	ldr r0, [sp, #0x20]
	cmp r0, #0x69
	beq _02246380
	ldr r0, [sp, #0x54]
	ldr r1, [r0]
	mov r0, #2
	lsl r0, r0, #0xa
	orr r1, r0
	ldr r0, [sp, #0x54]
	str r1, [r0]
	b _0224649C
_02246380:
	mov r0, #0xc0
	add r1, r6, #0
	mul r1, r0
	ldr r0, _02246594 ; =0x00002DCC
	add r3, r5, r1
	ldr r2, [r3, r0]
	lsl r2, r2, #0x10
	lsr r2, r2, #0x1d
	beq _022463B8
	sub r0, #0xc
	ldr r2, [r3, r0]
	mov r0, #1
	lsl r0, r0, #0xa
	tst r2, r0
	bne _022463B8
	ldr r2, [sp, #0x28]
	cmp r2, #4
	bne _022463B8
	ldr r2, [sp, #0x20]
	cmp r2, #0x69
	beq _022463B8
	ldr r1, [sp, #0x54]
	lsl r0, r0, #0xa
	ldr r1, [r1]
	orr r1, r0
	ldr r0, [sp, #0x54]
	str r1, [r0]
	b _0224649C
_022463B8:
	add r0, r5, r1
	mov r4, #0
	str r0, [sp, #0x18]
_022463BE:
	lsl r0, r4, #1
	ldr r1, _02246598 ; =MOD11_0225E378
	add r0, r4, r0
	add r1, r1, r0
	str r1, [sp, #0xc]
	ldr r1, _02246598 ; =MOD11_0225E378
	ldrb r1, [r1, r0]
	cmp r1, #0xfe
	bne _022463EE
	ldr r1, [sp, #0x18]
	ldr r0, _0224659C ; =0x00002DB0
	ldr r1, [r1, r0]
	mov r0, #2
	lsl r0, r0, #0x1c
	tst r0, r1
	bne _0224649C
	add r0, r5, #0
	add r1, r7, #0
	bl MOD11_02246D1C
	cmp r0, #0x71
	beq _0224649C
	add r4, r4, #1
	b _02246490
_022463EE:
	ldr r0, [sp, #0x28]
	cmp r0, r1
	bne _0224648E
	ldr r0, [sp, #0xc]
	add r1, r6, #0
	ldrb r0, [r0, #1]
	mov r2, #0x1b
	mov r3, #0
	str r0, [sp, #0x10]
	add r0, r5, #0
	bl MOD11_02243420
	ldr r1, [sp, #0x10]
	cmp r1, r0
	bne _02246434
	add r0, r5, #0
	add r1, r7, #0
	add r2, r6, #0
	add r3, r4, #0
	bl MOD11_022461C0
	cmp r0, #1
	bne _02246434
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0xc]
	str r0, [sp]
	ldr r0, [sp, #0x54]
	ldr r3, [sp, #0x50]
	str r0, [sp, #4]
	ldrb r2, [r2, #2]
	add r0, r5, #0
	add r1, r7, #0
	bl MOD11_0224C648
	str r0, [sp, #0x50]
_02246434:
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0x1c
	mov r3, #0
	bl MOD11_02243420
	ldr r1, [sp, #0x10]
	cmp r1, r0
	bne _0224648E
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0x1b
	mov r3, #0
	bl MOD11_02243420
	str r0, [sp, #0x2c]
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0x1c
	mov r3, #0
	bl MOD11_02243420
	ldr r1, [sp, #0x2c]
	cmp r1, r0
	beq _0224648E
	add r0, r5, #0
	add r1, r7, #0
	add r2, r6, #0
	add r3, r4, #0
	bl MOD11_022461C0
	cmp r0, #1
	bne _0224648E
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0xc]
	str r0, [sp]
	ldr r0, [sp, #0x54]
	ldr r3, [sp, #0x50]
	str r0, [sp, #4]
	ldrb r2, [r2, #2]
	add r0, r5, #0
	add r1, r7, #0
	bl MOD11_0224C648
	str r0, [sp, #0x50]
_0224648E:
	add r4, r4, #1
_02246490:
	lsl r0, r4, #1
	add r1, r4, r0
	ldr r0, _02246598 ; =MOD11_0225E378
	ldrb r0, [r0, r1]
	cmp r0, #0xff
	bne _022463BE
_0224649C:
	add r0, r5, #0
	add r1, r7, #0
	add r2, r6, #0
	mov r3, #0x19
	bl MOD11_02246D84
	cmp r0, #1
	bne _022464E0
	ldr r1, [sp, #8]
	add r0, r5, #0
	bl MOD11_0224C6D4
	cmp r0, #0
	beq _022464E0
	ldr r0, [sp, #0x54]
	ldr r1, [r0]
	mov r0, #2
	tst r0, r1
	beq _022464CA
	mov r0, #6
	and r0, r1
	cmp r0, #6
	bne _022464E0
_022464CA:
	ldr r0, [sp, #0x14]
	cmp r0, #0
	beq _022464E0
	ldr r0, [sp, #0x54]
	ldr r1, [r0]
	mov r0, #1
	lsl r0, r0, #0x12
	orr r1, r0
	ldr r0, [sp, #0x54]
	str r1, [r0]
	b _02246582
_022464E0:
	ldr r0, _02246590 ; =0x0000213C
	ldr r2, [r5, r0]
	mov r0, #2
	lsl r0, r0, #0xa
	add r1, r2, #0
	tst r1, r0
	bne _0224656E
	lsl r0, r0, #4
	tst r0, r2
	bne _0224656E
	ldr r0, [sp, #0x54]
	ldr r1, [r0]
	mov r0, #2
	tst r0, r1
	beq _0224654A
	ldr r0, [sp, #0x14]
	cmp r0, #0
	beq _0224654A
	add r0, r5, #0
	add r1, r7, #0
	add r2, r6, #0
	mov r3, #0x6f
	bl MOD11_02246D84
	cmp r0, #1
	beq _02246524
	add r0, r5, #0
	add r1, r7, #0
	add r2, r6, #0
	mov r3, #0x74
	bl MOD11_02246D84
	cmp r0, #1
	bne _02246532
_02246524:
	ldr r0, [sp, #0x50]
	lsl r1, r0, #1
	add r0, r0, r1
	mov r1, #4
	bl MOD11_022476C0
	str r0, [sp, #0x50]
_02246532:
	ldr r0, [sp, #0x24]
	cmp r0, #0x5f
	bne _0224654A
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x50]
	add r0, #0x64
	str r0, [sp, #0x1c]
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	str r0, [sp, #0x50]
_0224654A:
	ldr r0, [sp, #0x54]
	ldr r1, [r0]
	mov r0, #4
	tst r0, r1
	beq _02246582
	ldr r0, [sp, #0x14]
	cmp r0, #0
	beq _02246582
	add r0, r5, #0
	add r1, r7, #0
	bl MOD11_02246D1C
	cmp r0, #0x6e
	bne _02246582
	ldr r0, [sp, #0x50]
	lsl r0, r0, #1
	str r0, [sp, #0x50]
	b _02246582
_0224656E:
	ldr r0, [sp, #0x54]
	ldr r1, [r0]
	mov r0, #2
	bic r1, r0
	ldr r0, [sp, #0x54]
	str r1, [r0]
	mov r0, #4
	bic r1, r0
	ldr r0, [sp, #0x54]
	str r1, [r0]
_02246582:
	ldr r0, [sp, #0x50]
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02246588: .word 0x000003E2
_0224658C: .word 0x000003E1
_02246590: .word 0x0000213C
_02246594: .word 0x00002DCC
_02246598: .word MOD11_0225E378
_0224659C: .word 0x00002DB0

	thumb_func_start MOD11_022465A0
MOD11_022465A0: ; 0x022465A0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r0, #0
	ldr r0, [sp, #0x2c]
	str r1, [sp]
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x30]
	str r3, [sp, #4]
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x34]
	ldr r6, [sp, #0x38]
	str r0, [sp, #0x34]
	add r0, r1, #0
	cmp r0, #0xa5
	beq _022466B6
	add r0, r3, #0
	cmp r0, #0x60
	bne _022465CA
	mov r0, #0
	str r0, [sp, #0xc]
	b _022465E2
_022465CA:
	cmp r2, #0
	beq _022465D6
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	b _022465E2
_022465D6:
	add r0, r1, #0
	lsl r0, r0, #4
	add r1, r7, r0
	ldr r0, _022466BC ; =0x000003E2
	ldrb r0, [r1, r0]
	str r0, [sp, #0xc]
_022465E2:
	ldr r0, [sp, #4]
	cmp r0, #0x68
	beq _02246612
	ldr r0, [sp, #0x28]
	cmp r0, #0x1a
	bne _02246612
	ldr r0, [sp, #0xc]
	cmp r0, #4
	bne _02246612
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r7, r0]
	mov r0, #7
	lsl r0, r0, #0xc
	tst r0, r1
	bne _02246612
	ldr r0, [sp, #0x2c]
	cmp r0, #0x69
	beq _02246612
	ldr r1, [r6]
	mov r0, #8
	orr r0, r1
	str r0, [r6]
	b _02246686
_02246612:
	mov r4, #0
_02246614:
	lsl r0, r4, #1
	add r1, r4, r0
	ldr r0, _022466C0 ; =MOD11_0225E378
	add r5, r0, r1
	ldrb r1, [r0, r1]
	cmp r1, #0xfe
	bne _0224662C
	ldr r0, [sp, #4]
	cmp r0, #0x71
	beq _02246686
	add r4, r4, #1
	b _0224667A
_0224662C:
	ldr r0, [sp, #0xc]
	cmp r0, r1
	bne _02246678
	ldrb r0, [r5, #1]
	ldr r1, [sp, #0x30]
	str r0, [sp, #8]
	cmp r1, r0
	bne _02246652
	ldr r1, [sp, #0x2c]
	add r0, r7, #0
	add r2, r4, #0
	bl MOD11_022466C4
	cmp r0, #1
	bne _02246652
	ldrb r0, [r5, #2]
	add r1, r6, #0
	bl MOD11_02246714
_02246652:
	ldr r1, [sp, #0x34]
	ldr r0, [sp, #8]
	cmp r1, r0
	bne _02246678
	ldr r1, [sp, #0x30]
	ldr r0, [sp, #0x34]
	cmp r1, r0
	beq _02246678
	ldr r1, [sp, #0x2c]
	add r0, r7, #0
	add r2, r4, #0
	bl MOD11_022466C4
	cmp r0, #1
	bne _02246678
	ldrb r0, [r5, #2]
	add r1, r6, #0
	bl MOD11_02246714
_02246678:
	add r4, r4, #1
_0224667A:
	lsl r0, r4, #1
	add r1, r4, r0
	ldr r0, _022466C0 ; =MOD11_0225E378
	ldrb r0, [r0, r1]
	cmp r0, #0xff
	bne _02246614
_02246686:
	ldr r0, [sp, #4]
	cmp r0, #0x68
	beq _022466B6
	ldr r0, [sp, #0x28]
	cmp r0, #0x19
	bne _022466B6
	ldr r1, [sp]
	add r0, r7, #0
	bl MOD11_0224C6D4
	cmp r0, #0
	beq _022466B6
	ldr r1, [r6]
	mov r0, #2
	tst r0, r1
	beq _022466AE
	mov r0, #6
	and r0, r1
	cmp r0, #6
	bne _022466B6
_022466AE:
	ldr r1, [r6]
	mov r0, #8
	orr r0, r1
	str r0, [r6]
_022466B6:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022466BC: .word 0x000003E2
_022466C0: .word MOD11_0225E378

	thumb_func_start MOD11_022466C4
MOD11_022466C4: ; 0x022466C4
	push {r3, r4}
	mov r3, #1
	cmp r1, #0x69
	bne _022466E2
	lsl r1, r2, #1
	add r4, r2, r1
	ldr r1, _0224670C ; =MOD11_0225E379
	ldrb r1, [r1, r4]
	cmp r1, #2
	bne _022466E2
	ldr r1, _02246710 ; =MOD11_0225E37A
	ldrb r1, [r1, r4]
	cmp r1, #0
	bne _022466E2
	mov r3, #0
_022466E2:
	mov r1, #6
	lsl r1, r1, #6
	ldr r1, [r0, r1]
	mov r0, #7
	lsl r0, r0, #0xc
	tst r0, r1
	beq _02246706
	lsl r0, r2, #1
	add r1, r2, r0
	ldr r0, _0224670C ; =MOD11_0225E379
	ldrb r0, [r0, r1]
	cmp r0, #2
	bne _02246706
	ldr r0, _02246710 ; =MOD11_0225E37A
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _02246706
	mov r3, #0
_02246706:
	add r0, r3, #0
	pop {r3, r4}
	bx lr
	.align 2, 0
_0224670C: .word MOD11_0225E379
_02246710: .word MOD11_0225E37A

	thumb_func_start MOD11_02246714
MOD11_02246714: ; 0x02246714
	cmp r0, #0
	beq _02246722
	cmp r0, #5
	beq _02246734
	cmp r0, #0x14
	beq _0224674C
	bx lr
_02246722:
	ldr r2, [r1]
	mov r0, #8
	orr r2, r0
	mov r0, #4
	bic r2, r0
	mov r0, #2
	bic r2, r0
	str r2, [r1]
	bx lr
_02246734:
	ldr r2, [r1]
	mov r0, #2
	tst r0, r2
	beq _02246744
	mov r0, #2
	bic r2, r0
	str r2, [r1]
	bx lr
_02246744:
	mov r0, #4
	orr r0, r2
	str r0, [r1]
	bx lr
_0224674C:
	ldr r2, [r1]
	mov r0, #4
	tst r0, r2
	beq _0224675C
	mov r0, #4
	bic r2, r0
	str r2, [r1]
	bx lr
_0224675C:
	mov r0, #2
	orr r0, r2
	str r0, [r1]
	bx lr

	thumb_func_start MOD11_02246764
MOD11_02246764: ; 0x02246764
	mov r2, #0xd1
	lsl r2, r2, #2
	add r2, r0, r2
	lsl r0, r1, #2
	ldr r0, [r2, r0]
	lsl r1, r0, #0x1f
	lsr r1, r1, #0x1f
	bne _022467A4
	lsl r1, r0, #0x1e
	lsr r1, r1, #0x1f
	bne _022467A4
	lsl r1, r0, #0x1d
	lsr r1, r1, #0x1f
	bne _022467A4
	lsl r1, r0, #0x1c
	lsr r1, r1, #0x1f
	bne _022467A4
	lsl r1, r0, #0x1b
	lsr r1, r1, #0x1f
	bne _022467A4
	lsl r1, r0, #0x1a
	lsr r1, r1, #0x1f
	bne _022467A4
	lsl r1, r0, #0x19
	lsr r1, r1, #0x1f
	bne _022467A4
	lsl r1, r0, #0x17
	lsr r1, r1, #0x1f
	bne _022467A4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	beq _022467A8
_022467A4:
	mov r0, #1
	bx lr
_022467A8:
	mov r0, #0
	bx lr

	thumb_func_start MOD11_022467AC
MOD11_022467AC: ; 0x022467AC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r0, [sp]
	add r5, r1, #0
	add r6, r2, #0
	str r3, [sp, #4]
	mov r4, #0
	bl MOD11_0222FF84
	add r7, r0, #0
	cmp r6, #0
	beq _022467CA
	cmp r6, #1
	beq _022467EE
	b _02246822
_022467CA:
	add r0, r4, #0
	cmp r7, #0
	ble _02246822
	ldr r2, _02246828 ; =0x00002D8C
_022467D2:
	ldr r1, [sp, #4]
	cmp r0, r1
	beq _022467E4
	ldr r1, [r5, r2]
	cmp r1, #0
	beq _022467E4
	add r1, r4, #1
	lsl r1, r1, #0x18
	lsr r4, r1, #0x18
_022467E4:
	add r0, r0, #1
	add r5, #0xc0
	cmp r0, r7
	blt _022467D2
	b _02246822
_022467EE:
	add r6, r4, #0
	cmp r7, #0
	ble _02246822
_022467F4:
	ldr r0, [sp]
	add r1, r6, #0
	bl MOD11_02230270
	str r0, [sp, #8]
	ldr r0, [sp]
	ldr r1, [sp, #4]
	bl MOD11_02230270
	ldr r1, [sp, #8]
	cmp r1, r0
	bne _0224681A
	ldr r0, _02246828 ; =0x00002D8C
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _0224681A
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_0224681A:
	add r6, r6, #1
	add r5, #0xc0
	cmp r6, r7
	blt _022467F4
_02246822:
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02246828: .word 0x00002D8C

	thumb_func_start MOD11_0224682C
MOD11_0224682C: ; 0x0224682C
	add r2, r0, r1
	ldr r0, _02246838 ; =0x0000219C
	ldrb r0, [r2, r0]
	lsl r0, r0, #8
	orr r0, r1
	bx lr
	.align 2, 0
_02246838: .word 0x0000219C

	thumb_func_start MOD11_0224683C
MOD11_0224683C: ; 0x0224683C
	push {r4, r5}
	lsl r3, r1, #4
	add r5, r0, r3
	ldr r3, _02246868 ; =0x000021B4
	mov r2, #0
	ldr r4, [r5, r3]
	cmp r4, #1
	bne _02246862
	sub r3, r3, #4
	ldr r3, [r5, r3]
	cmp r3, #0
	beq _02246862
	mov r2, #0xc0
	mul r2, r1
	add r1, r0, r2
	lsl r0, r3, #1
	add r1, r1, r0
	ldr r0, _0224686C ; =0x00002D4A
	ldrh r2, [r1, r0]
_02246862:
	add r0, r2, #0
	pop {r4, r5}
	bx lr
	.align 2, 0
_02246868: .word 0x000021B4
_0224686C: .word 0x00002D4A

	thumb_func_start MOD11_02246870
MOD11_02246870: ; 0x02246870
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	str r2, [sp, #4]
	str r0, [sp]
	add r7, r1, #0
	str r3, [sp, #8]
	ldr r6, [sp, #0x70]
	mov r4, #0
	bl MOD11_0222FF84
	add r5, r0, #0
	ldr r0, [sp, #4]
	cmp r0, #9
	bhi _022468E4
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02246898: ; jump table
	.short _022468AC - _02246898 - 2 ; case 0
	.short _022468E6 - _02246898 - 2 ; case 1
	.short _02246932 - _02246898 - 2 ; case 2
	.short _0224696C - _02246898 - 2 ; case 3
	.short _022469B8 - _02246898 - 2 ; case 4
	.short _02246A0A - _02246898 - 2 ; case 5
	.short _02246A2C - _02246898 - 2 ; case 6
	.short _02246A54 - _02246898 - 2 ; case 7
	.short _02246A80 - _02246898 - 2 ; case 8
	.short _02246AB4 - _02246898 - 2 ; case 9
_022468AC:
	add r0, r4, #0
	str r0, [sp, #0x44]
	cmp r5, #0
	ble _022468E4
_022468B4:
	ldr r0, [sp]
	ldr r1, [sp, #0x44]
	bl MOD11_02230270
	str r0, [sp, #0x48]
	ldr r0, [sp]
	ldr r1, [sp, #8]
	bl MOD11_02230270
	ldr r1, [sp, #0x48]
	cmp r1, r0
	bne _022468DA
	ldr r1, [sp, #0x44]
	add r0, r7, #0
	bl MOD11_02246D1C
	cmp r6, r0
	bne _022468DA
	add r4, r4, #1
_022468DA:
	ldr r0, [sp, #0x44]
	add r0, r0, #1
	str r0, [sp, #0x44]
	cmp r0, r5
	blt _022468B4
_022468E4:
	b _02246AEC
_022468E6:
	add r0, r4, #0
	str r0, [sp, #0xc]
	cmp r5, #0
	ble _02246930
	str r7, [sp, #0x30]
_022468F0:
	ldr r0, [sp]
	ldr r1, [sp, #0xc]
	bl MOD11_02230270
	str r0, [sp, #0x4c]
	ldr r0, [sp]
	ldr r1, [sp, #8]
	bl MOD11_02230270
	ldr r1, [sp, #0x4c]
	cmp r1, r0
	bne _02246920
	ldr r1, [sp, #0x30]
	ldr r0, _02246AF4 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02246920
	ldr r1, [sp, #0xc]
	add r0, r7, #0
	bl MOD11_02246D1C
	cmp r6, r0
	bne _02246920
	add r4, r4, #1
_02246920:
	ldr r0, [sp, #0x30]
	add r0, #0xc0
	str r0, [sp, #0x30]
	ldr r0, [sp, #0xc]
	add r0, r0, #1
	str r0, [sp, #0xc]
	cmp r0, r5
	blt _022468F0
_02246930:
	b _02246AEC
_02246932:
	add r0, r4, #0
	str r0, [sp, #0x10]
	cmp r5, #0
	ble _0224696A
_0224693A:
	ldr r0, [sp]
	ldr r1, [sp, #0x10]
	bl MOD11_02230270
	str r0, [sp, #0x50]
	ldr r0, [sp]
	ldr r1, [sp, #8]
	bl MOD11_02230270
	ldr r1, [sp, #0x50]
	cmp r1, r0
	beq _02246960
	ldr r1, [sp, #0x10]
	add r0, r7, #0
	bl MOD11_02246D1C
	cmp r6, r0
	bne _02246960
	add r4, r4, #1
_02246960:
	ldr r0, [sp, #0x10]
	add r0, r0, #1
	str r0, [sp, #0x10]
	cmp r0, r5
	blt _0224693A
_0224696A:
	b _02246AEC
_0224696C:
	add r0, r4, #0
	str r0, [sp, #0x14]
	cmp r5, #0
	ble _022469B6
	str r7, [sp, #0x34]
_02246976:
	ldr r0, [sp]
	ldr r1, [sp, #0x14]
	bl MOD11_02230270
	str r0, [sp, #0x54]
	ldr r0, [sp]
	ldr r1, [sp, #8]
	bl MOD11_02230270
	ldr r1, [sp, #0x54]
	cmp r1, r0
	beq _022469A6
	ldr r1, [sp, #0x34]
	ldr r0, _02246AF4 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _022469A6
	ldr r1, [sp, #0x14]
	add r0, r7, #0
	bl MOD11_02246D1C
	cmp r6, r0
	bne _022469A6
	add r4, r4, #1
_022469A6:
	ldr r0, [sp, #0x34]
	add r0, #0xc0
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x14]
	add r0, r0, #1
	str r0, [sp, #0x14]
	cmp r0, r5
	blt _02246976
_022469B6:
	b _02246AEC
_022469B8:
	add r0, r4, #0
	str r0, [sp, #0x18]
	cmp r5, #0
	ble _02246A08
	str r7, [sp, #0x38]
_022469C2:
	ldr r0, [sp]
	ldr r1, [sp, #0x18]
	bl MOD11_02230270
	str r0, [sp, #0x58]
	ldr r0, [sp]
	ldr r1, [sp, #8]
	bl MOD11_02230270
	ldr r1, [sp, #0x58]
	cmp r1, r0
	beq _022469F8
	ldr r1, [sp, #0x38]
	ldr r0, _02246AF4 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _022469F8
	ldr r1, [sp, #0x18]
	add r0, r7, #0
	bl MOD11_02246D1C
	cmp r6, r0
	bne _022469F8
	ldr r0, [sp, #0x18]
	bl MaskOfFlagNo
	orr r4, r0
_022469F8:
	ldr r0, [sp, #0x38]
	add r0, #0xc0
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x18]
	add r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, r5
	blt _022469C2
_02246A08:
	b _02246AEC
_02246A0A:
	add r0, r4, #0
	str r0, [sp, #0x1c]
	cmp r5, #0
	ble _02246AEC
_02246A12:
	ldr r1, [sp, #0x1c]
	add r0, r7, #0
	bl MOD11_02246D1C
	cmp r6, r0
	bne _02246A20
	add r4, r4, #1
_02246A20:
	ldr r0, [sp, #0x1c]
	add r0, r0, #1
	str r0, [sp, #0x1c]
	cmp r0, r5
	blt _02246A12
	b _02246AEC
_02246A2C:
	add r0, r4, #0
	str r0, [sp, #0x20]
	cmp r5, #0
	ble _02246AEC
_02246A34:
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #8]
	cmp r1, r0
	beq _02246A48
	add r0, r7, #0
	bl MOD11_02246D1C
	cmp r6, r0
	bne _02246A48
	add r4, r4, #1
_02246A48:
	ldr r0, [sp, #0x20]
	add r0, r0, #1
	str r0, [sp, #0x20]
	cmp r0, r5
	blt _02246A34
	b _02246AEC
_02246A54:
	add r0, r4, #0
	str r0, [sp, #0x24]
	cmp r5, #0
	ble _02246AEC
_02246A5C:
	ldr r1, [sp, #0x24]
	ldr r0, [sp, #8]
	cmp r1, r0
	beq _02246A74
	add r0, r7, #0
	bl MOD11_02246D1C
	cmp r6, r0
	bne _02246A74
	ldr r0, [sp, #0x24]
	add r4, r0, #1
	b _02246AEC
_02246A74:
	ldr r0, [sp, #0x24]
	add r0, r0, #1
	str r0, [sp, #0x24]
	cmp r0, r5
	blt _02246A5C
	b _02246AEC
_02246A80:
	add r0, r4, #0
	str r0, [sp, #0x28]
	cmp r5, #0
	ble _02246AEC
	str r7, [sp, #0x3c]
_02246A8A:
	ldr r1, [sp, #0x28]
	add r0, r7, #0
	bl MOD11_02246D1C
	cmp r6, r0
	bne _02246AA2
	ldr r1, [sp, #0x3c]
	ldr r0, _02246AF4 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02246AA2
	add r4, r4, #1
_02246AA2:
	ldr r0, [sp, #0x3c]
	add r0, #0xc0
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x28]
	add r0, r0, #1
	str r0, [sp, #0x28]
	cmp r0, r5
	blt _02246A8A
	b _02246AEC
_02246AB4:
	add r0, r4, #0
	str r0, [sp, #0x2c]
	cmp r5, #0
	ble _02246AEC
	str r7, [sp, #0x40]
_02246ABE:
	ldr r1, [sp, #0x2c]
	ldr r0, [sp, #8]
	cmp r1, r0
	beq _02246ADC
	add r0, r7, #0
	bl MOD11_02246D1C
	cmp r6, r0
	bne _02246ADC
	ldr r1, [sp, #0x40]
	ldr r0, _02246AF4 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02246ADC
	add r4, r4, #1
_02246ADC:
	ldr r0, [sp, #0x40]
	add r0, #0xc0
	str r0, [sp, #0x40]
	ldr r0, [sp, #0x2c]
	add r0, r0, #1
	str r0, [sp, #0x2c]
	cmp r0, r5
	blt _02246ABE
_02246AEC:
	add r0, r4, #0
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	nop
_02246AF4: .word 0x00002D8C

	thumb_func_start MOD11_02246AF8
MOD11_02246AF8: ; 0x02246AF8
	lsl r1, r1, #4
	add r1, r0, r1
	ldr r0, _02246B54 ; =0x000003DE
	ldrh r2, [r1, r0]
	cmp r2, #0x9b
	bgt _02246B2A
	cmp r2, #0x97
	blt _02246B10
	beq _02246B4A
	cmp r2, #0x9b
	beq _02246B4A
	b _02246B4E
_02246B10:
	cmp r2, #0x27
	bgt _02246B1C
	bge _02246B4A
	cmp r2, #0x1a
	beq _02246B4A
	b _02246B4E
_02246B1C:
	cmp r2, #0x4b
	bgt _02246B24
	beq _02246B4A
	b _02246B4E
_02246B24:
	cmp r2, #0x91
	beq _02246B4A
	b _02246B4E
_02246B2A:
	mov r1, #1
	lsl r1, r1, #8
	cmp r2, r1
	bgt _02246B3A
	bge _02246B4A
	cmp r2, #0xff
	beq _02246B4A
	b _02246B4E
_02246B3A:
	add r0, r1, #7
	cmp r2, r0
	bgt _02246B44
	beq _02246B4A
	b _02246B4E
_02246B44:
	add r1, #0x10
	cmp r2, r1
	bne _02246B4E
_02246B4A:
	mov r0, #1
	bx lr
_02246B4E:
	mov r0, #0
	bx lr
	nop
_02246B54: .word 0x000003DE

	thumb_func_start MOD11_02246B58
MOD11_02246B58: ; 0x02246B58
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r5, r1, #0
	add r4, r2, #0
	add r7, r3, #0
	mov r0, #1
	cmp r6, #0x70
	blo _02246B76
	bl LCRandom
	mov r1, #0x70
	bl _u32_div_f
	add r6, r1, #0
	mov r0, #0
_02246B76:
	lsl r1, r6, #1
	ldr r2, _02246B90 ; =MOD11_0225E378
	add r1, r6, r1
	ldrb r2, [r2, r1]
	strb r2, [r5]
	ldr r2, _02246B94 ; =MOD11_0225E379
	ldrb r2, [r2, r1]
	strb r2, [r4]
	ldr r2, _02246B98 ; =MOD11_0225E37A
	ldrb r1, [r2, r1]
	strb r1, [r7]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02246B90: .word MOD11_0225E378
_02246B94: .word MOD11_0225E379
_02246B98: .word MOD11_0225E37A

	thumb_func_start MOD11_02246B9C
MOD11_02246B9C: ; 0x02246B9C
	push {r3, r4, r5, r6, r7, lr}
	ldr r4, _02246BE4 ; =MOD11_0225E378
	add r5, r1, #0
	str r0, [sp]
	add r6, r2, #0
	mov r1, #0x28
_02246BA8:
	ldrb r2, [r4]
	ldr r0, [sp]
	cmp r0, r2
	bne _02246BD6
	ldrb r7, [r4, #1]
	cmp r5, r7
	bne _02246BC2
	ldrb r0, [r4, #2]
	mul r0, r1
	mov r1, #0xa
	bl _s32_div_f
	add r1, r0, #0
_02246BC2:
	cmp r6, r7
	bne _02246BD6
	cmp r5, r6
	beq _02246BD6
	ldrb r0, [r4, #2]
	mul r0, r1
	mov r1, #0xa
	bl _s32_div_f
	add r1, r0, #0
_02246BD6:
	add r4, r4, #3
	ldrb r0, [r4]
	cmp r0, #0xff
	bne _02246BA8
	add r0, r1, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02246BE4: .word MOD11_0225E378

	thumb_func_start MOD11_02246BE8
MOD11_02246BE8: ; 0x02246BE8
	cmp r0, #0
	beq _02246C10
	cmp r0, #0xd6
	beq _02246C10
	ldr r2, _02246C18 ; =0x0000017F
	cmp r0, r2
	beq _02246C10
	add r1, r2, #0
	sub r1, #0x6d
	cmp r0, r1
	beq _02246C10
	sub r1, r2, #1
	cmp r0, r1
	beq _02246C10
	ldr r1, _02246C1C ; =0x0000FF8A
	add r0, r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #1
	bhi _02246C14
_02246C10:
	mov r0, #1
	bx lr
_02246C14:
	mov r0, #0
	bx lr
	.align 2, 0
_02246C18: .word 0x0000017F
_02246C1C: .word 0x0000FF8A

	thumb_func_start MOD11_02246C20
MOD11_02246C20: ; 0x02246C20
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r2, #0
	cmp r1, #0xae
	bne _02246C4C
	add r1, r4, #0
	mov r2, #0x1b
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #7
	beq _02246C48
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x1c
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #7
	bne _02246C4C
_02246C48:
	mov r0, #1
	pop {r3, r4, r5, pc}
_02246C4C:
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD11_02246C50
MOD11_02246C50: ; 0x02246C50
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r2, #0
	add r5, r1, #0
	add r1, r6, #0
	mov r7, #0
	bl MOD11_02230270
	str r0, [sp]
	ldr r0, _02246CA4 ; =0x00002DB8
	add r4, r5, r0
	mov r0, #0xc0
	mul r0, r6
	str r0, [sp, #4]
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _02246C9E
	ldr r0, _02246CA8 ; =0x0000219C
	add r1, r5, r6
	ldrb r0, [r1, r0]
	bl MaskOfFlagNo
	ldr r1, [sp]
	lsl r1, r1, #3
	add r2, r5, r1
	mov r1, #0x71
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	lsl r1, r1, #3
	lsr r1, r1, #0x1a
	tst r0, r1
	bne _02246C9E
	ldr r0, [sp, #4]
	ldrh r0, [r4, r0]
	bl ItemIdIsMail
	cmp r0, #0
	bne _02246C9E
	mov r7, #1
_02246C9E:
	add r0, r7, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02246CA4: .word 0x00002DB8
_02246CA8: .word 0x0000219C

	thumb_func_start MOD11_02246CAC
MOD11_02246CAC: ; 0x02246CAC
	push {r3, lr}
	mov r2, #0xc0
	mul r2, r1
	add r1, r0, r2
	ldr r0, _02246CC8 ; =0x00002DB8
	ldrh r0, [r1, r0]
	bl ItemIdIsMail
	cmp r0, #0
	bne _02246CC4
	mov r0, #1
	pop {r3, pc}
_02246CC4:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_02246CC8: .word 0x00002DB8

	thumb_func_start MOD11_02246CCC
MOD11_02246CCC: ; 0x02246CCC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r1, [r5, #0x6c]
	mov r0, #0xc0
	add r3, r1, #0
	ldr r1, _02246D18 ; =0x00002D74
	mul r3, r0
	add r2, r5, r1
	ldrb r4, [r2, r3]
	ldr r2, [r5, #0x64]
	mov r6, #0
	mul r0, r2
	add r0, r5, r0
	ldrb r0, [r0, r1]
	cmp r0, r4
	blo _02246CF0
	mov r6, #1
	b _02246D14
_02246CF0:
	bl LCRandom
	ldr r2, [r5, #0x64]
	mov r1, #0xc0
	mul r1, r2
	add r2, r5, r1
	ldr r1, _02246D18 ; =0x00002D74
	lsl r0, r0, #0x18
	ldrb r1, [r2, r1]
	lsr r0, r0, #0x18
	add r1, r1, r4
	mul r0, r1
	asr r0, r0, #8
	add r1, r0, #1
	lsr r0, r4, #2
	cmp r1, r0
	ble _02246D14
	mov r6, #1
_02246D14:
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_02246D18: .word 0x00002D74

	thumb_func_start MOD11_02246D1C
MOD11_02246D1C: ; 0x02246D1C
	push {r4, r5}
	mov r2, #0xc0
	mul r2, r1
	mov r3, #0xb7
	mov r4, #2
	add r5, r0, r2
	lsl r3, r3, #6
	ldr r1, [r5, r3]
	lsl r4, r4, #0x14
	tst r4, r1
	beq _02246D40
	sub r3, #0x59
	ldrb r3, [r5, r3]
	cmp r3, #0x79
	beq _02246D40
	mov r0, #0
	pop {r4, r5}
	bx lr
_02246D40:
	mov r3, #6
	lsl r3, r3, #6
	ldr r4, [r0, r3]
	mov r3, #7
	lsl r3, r3, #0xc
	tst r3, r4
	beq _02246D5E
	ldr r3, _02246D80 ; =0x00002D67
	add r4, r0, r2
	ldrb r3, [r4, r3]
	cmp r3, #0x1a
	bne _02246D5E
	mov r0, #0
	pop {r4, r5}
	bx lr
_02246D5E:
	mov r3, #1
	lsl r3, r3, #0xa
	tst r1, r3
	beq _02246D76
	ldr r1, _02246D80 ; =0x00002D67
	add r3, r0, r2
	ldrb r1, [r3, r1]
	cmp r1, #0x1a
	bne _02246D76
	mov r0, #0
	pop {r4, r5}
	bx lr
_02246D76:
	add r1, r0, r2
	ldr r0, _02246D80 ; =0x00002D67
	ldrb r0, [r1, r0]
	pop {r4, r5}
	bx lr
	.align 2, 0
_02246D80: .word 0x00002D67

	thumb_func_start MOD11_02246D84
MOD11_02246D84: ; 0x02246D84
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	str r2, [sp]
	add r4, r3, #0
	mov r6, #0
	bl MOD11_02246D1C
	cmp r0, #0x68
	beq _02246DA8
	ldr r1, [sp]
	add r0, r5, #0
	bl MOD11_02246D1C
	cmp r4, r0
	bne _02246DD6
	mov r6, #1
	b _02246DD6
_02246DA8:
	ldr r1, [sp]
	add r0, r5, #0
	bl MOD11_02246D1C
	cmp r4, r0
	bne _02246DD6
	mov r0, #0xb5
	lsl r0, r0, #2
	add r1, r5, r0
	mov r0, #0x1c
	mul r0, r7
	ldr r3, [r1, r0]
	lsl r2, r3, #0x1c
	lsr r2, r2, #0x1f
	bne _02246DD6
	mov r2, #8
	orr r3, r2
	str r3, [r1, r0]
	ldr r1, _02246DDC ; =0x0000213C
	lsl r0, r2, #0x14
	ldr r3, [r5, r1]
	orr r0, r3
	str r0, [r5, r1]
_02246DD6:
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02246DDC: .word 0x0000213C

	thumb_func_start MOD11_02246DE0
MOD11_02246DE0: ; 0x02246DE0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	mov r6, #0
	str r0, [sp]
	str r1, [sp, #4]
	add r4, r2, #0
	str r6, [sp, #0x18]
	bl MOD11_0222FF74
	add r5, r0, #0
	ldr r0, [sp]
	add r1, r4, #0
	bl MOD11_0222FF88
	str r0, [sp, #0x14]
	ldr r0, [sp]
	add r1, r4, #0
	bl MOD11_0222FFC8
	add r7, r0, #0
	mov r0, #8
	tst r0, r5
	bne _02246E22
	mov r0, #0x10
	tst r0, r5
	beq _02246E36
	ldr r0, [sp]
	add r1, r4, #0
	bl MOD11_02230260
	mov r1, #1
	tst r0, r1
	beq _02246E36
_02246E22:
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, [sp, #4]
	mov r5, #0
	add r1, r0, r4
	ldr r0, _02246ECC ; =0x0000219C
	ldrb r0, [r1, r0]
	str r0, [sp, #0xc]
	str r0, [sp, #8]
	b _02246E72
_02246E36:
	mov r0, #2
	tst r0, r5
	beq _02246E60
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, [sp, #4]
	mov r5, #0
	add r1, r0, r4
	ldr r0, _02246ECC ; =0x0000219C
	ldrb r0, [r1, r0]
	add r1, r4, #0
	str r0, [sp, #0xc]
	ldr r0, [sp]
	bl MOD11_022302BC
	ldr r1, [sp, #4]
	add r1, r1, r0
	ldr r0, _02246ECC ; =0x0000219C
	ldrb r0, [r1, r0]
	str r0, [sp, #8]
	b _02246E72
_02246E60:
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, [sp, #4]
	mov r5, #0
	add r1, r0, r4
	ldr r0, _02246ECC ; =0x0000219C
	ldrb r0, [r1, r0]
	str r0, [sp, #0xc]
	str r0, [sp, #8]
_02246E72:
	cmp r5, r7
	bge _02246EBC
_02246E76:
	ldr r0, [sp, #0x14]
	add r1, r5, #0
	bl GetPartyMonByIndex
	mov r1, #5
	mov r2, #0
	add r4, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _02246EB6
	add r0, r4, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _02246EB6
	add r0, r4, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _02246EB6
	ldr r0, [sp, #0xc]
	cmp r0, r5
	beq _02246EB6
	ldr r0, [sp, #8]
	cmp r0, r5
	beq _02246EB6
	add r6, r6, #1
_02246EB6:
	add r5, r5, #1
	cmp r5, r7
	blt _02246E76
_02246EBC:
	ldr r0, [sp, #0x10]
	cmp r6, r0
	blt _02246EC6
	mov r0, #1
	str r0, [sp, #0x18]
_02246EC6:
	ldr r0, [sp, #0x18]
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02246ECC: .word 0x0000219C

	thumb_func_start MOD11_02246ED0
MOD11_02246ED0: ; 0x02246ED0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r1, #0
	add r6, r2, #0
	add r7, r0, #0
	add r4, r3, #0
	bl MOD11_0222FF74
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD11_02249D90
	str r0, [sp, #8]
	cmp r0, #0x3e
	beq _02246F06
	mov r1, #0xa9
	ldr r0, [sp, #0xc]
	lsl r1, r1, #2
	tst r0, r1
	bne _02246F06
	add r0, r5, #0
	add r1, r6, #0
	bl MOD11_02246D1C
	cmp r0, #0x32
	bne _02246F0C
_02246F06:
	add sp, #0x14
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_02246F0C:
	add r0, r7, #0
	add r1, r6, #0
	bl MOD11_02230270
	add r0, r7, #0
	bl MOD11_0222FF84
	mov r0, #0x17
	str r0, [sp]
	add r0, r7, #0
	add r1, r5, #0
	mov r2, #9
	add r3, r6, #0
	bl MOD11_02246870
	str r0, [sp, #0x10]
	cmp r0, #0
	beq _02246F62
	add r0, r5, #0
	add r1, r6, #0
	bl MOD11_02246D1C
	cmp r0, #0x17
	beq _02246F62
	cmp r4, #0
	bne _02246F46
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02246F46:
	mov r0, #0xb
	strb r0, [r4, #1]
	mov r0, #0x27
	strh r0, [r4, #2]
	ldr r1, [sp, #0x10]
	add r0, r5, #0
	bl MOD11_0224682C
	str r0, [r4, #4]
	mov r0, #0x17
	str r0, [r4, #8]
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02246F62:
	mov r0, #0x47
	str r0, [sp]
	add r0, r7, #0
	add r1, r5, #0
	mov r2, #3
	add r3, r6, #0
	bl MOD11_02246870
	str r0, [sp, #4]
	cmp r0, #0
	beq _02247014
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #7
	lsl r0, r0, #0xc
	tst r0, r1
	bne _02246FEE
	ldr r0, [sp, #8]
	cmp r0, #0x69
	beq _02246FEE
	add r0, r5, #0
	add r1, r6, #0
	bl MOD11_02246D1C
	cmp r0, #0x1a
	beq _02247014
	mov r0, #0xc0
	mul r0, r6
	add r1, r5, r0
	ldr r0, _022470A8 ; =0x00002DCC
	ldr r0, [r1, r0]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x1d
	bne _02247014
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0x1b
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #2
	beq _02247014
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0x1c
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #2
	beq _02247014
	cmp r4, #0
	bne _02246FD2
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02246FD2:
	mov r0, #0xb
	strb r0, [r4, #1]
	mov r0, #0x27
	strh r0, [r4, #2]
	ldr r1, [sp, #4]
	add r0, r5, #0
	bl MOD11_0224682C
	str r0, [r4, #4]
	mov r0, #0x47
	str r0, [r4, #8]
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02246FEE:
	cmp r4, #0
	bne _02246FF8
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02246FF8:
	mov r0, #0xb
	strb r0, [r4, #1]
	mov r0, #0x27
	strh r0, [r4, #2]
	ldr r1, [sp, #4]
	add r0, r5, #0
	bl MOD11_0224682C
	str r0, [r4, #4]
	mov r0, #0x47
	str r0, [r4, #8]
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02247014:
	mov r0, #0x2a
	str r0, [sp]
	add r0, r7, #0
	add r1, r5, #0
	mov r2, #3
	add r3, r6, #0
	bl MOD11_02246870
	add r7, r0, #0
	beq _0224706E
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0x1b
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #8
	beq _02247048
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0x1c
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #8
	bne _0224706E
_02247048:
	cmp r4, #0
	bne _02247052
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02247052:
	mov r0, #0xb
	strb r0, [r4, #1]
	mov r0, #0x27
	strh r0, [r4, #2]
	add r0, r5, #0
	add r1, r7, #0
	bl MOD11_0224682C
	str r0, [r4, #4]
	mov r0, #0x2a
	str r0, [r4, #8]
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0224706E:
	mov r0, #0xc0
	mul r0, r6
	add r3, r5, r0
	ldr r0, _022470AC ; =0x00002DB0
	ldr r1, _022470B0 ; =0x0400E000
	ldr r2, [r3, r0]
	tst r2, r1
	bne _02247088
	add r0, #0x10
	ldr r2, [r3, r0]
	lsr r0, r1, #0x10
	tst r0, r2
	beq _022470A0
_02247088:
	cmp r4, #0
	bne _02247092
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02247092:
	mov r0, #0
	strb r0, [r4, #1]
	ldr r0, _022470B4 ; =0x0000031A
	add sp, #0x14
	strh r0, [r4, #2]
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_022470A0:
	mov r0, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_022470A8: .word 0x00002DCC
_022470AC: .word 0x00002DB0
_022470B0: .word 0x0400E000
_022470B4: .word 0x0000031A

	thumb_func_start MOD11_022470B8
MOD11_022470B8: ; 0x022470B8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r4, r2, #0
	str r0, [sp]
	bl MOD11_0222FF74
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_02249D90
	mov r6, #0
	cmp r0, #0x3e
	bne _022470EC
	mov r0, #0x75
	lsl r0, r0, #2
	add r3, r5, r0
	lsl r2, r4, #6
	ldr r1, [r3, r2]
	ldr r0, _02247184 ; =0xFFFFFE7F
	mov r6, #1
	and r1, r0
	mov r0, #0x80
	orr r0, r1
	str r0, [r3, r2]
	b _0224717E
_022470EC:
	mov r0, #0xa9
	lsl r0, r0, #2
	tst r0, r7
	beq _022470F8
	mov r6, #1
	b _0224717E
_022470F8:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x32
	bne _0224711C
	mov r1, #0x75
	lsl r1, r1, #2
	add r5, r5, r1
	lsl r3, r4, #6
	ldr r2, [r5, r3]
	ldr r0, _02247184 ; =0xFFFFFE7F
	sub r1, #0xd4
	and r0, r2
	orr r0, r1
	str r0, [r5, r3]
	mov r6, #1
	b _0224717E
_0224711C:
	mov r0, #1
	add r1, r4, #0
	eor r1, r0
	mov r2, #0xc0
	add r3, r1, #0
	mul r3, r2
	add r1, r5, r3
	ldr r3, _02247188 ; =0x00002D46
	mul r2, r4
	add r2, r5, r2
	ldrh r1, [r1, r3]
	ldrh r2, [r2, r3]
	cmp r2, r1
	bhs _02247164
	lsl r0, r2, #7
	bl _s32_div_f
	ldr r1, _0224718C ; =0x0000311E
	ldrb r2, [r5, r1]
	mov r1, #0x1e
	mul r1, r2
	add r0, r1, r0
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r2, r0, #0x18
	sub r2, r2, r1
	mov r0, #0x18
	ror r2, r0
	add r0, r1, r2
	cmp r7, r0
	ble _02247166
	mov r6, #1
	b _02247166
_02247164:
	add r6, r0, #0
_02247166:
	cmp r6, #0
	bne _02247176
	ldr r0, [sp]
	add r1, r4, #0
	mov r2, #0
	mov r3, #0x47
	bl MOD11_022564A8
_02247176:
	ldr r0, _0224718C ; =0x0000311E
	ldrb r1, [r5, r0]
	add r1, r1, #1
	strb r1, [r5, r0]
_0224717E:
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02247184: .word 0xFFFFFE7F
_02247188: .word 0x00002D46
_0224718C: .word 0x0000311E

	thumb_func_start MOD11_02247190
MOD11_02247190: ; 0x02247190
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD11_02246D1C
	cmp r0, #0x36
	bne _022471BA
	mov r2, #0xc0
	mul r2, r4
	add r3, r5, r2
	ldr r2, _022471C0 ; =0x00002DC8
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r2, [r3, r2]
	ldr r1, [r5, r0]
	mov r0, #1
	lsl r2, r2, #1
	and r1, r0
	lsr r2, r2, #0x1f
	cmp r1, r2
	bne _022471BC
_022471BA:
	mov r0, #0
_022471BC:
	pop {r3, r4, r5, pc}
	nop
_022471C0: .word 0x00002DC8

	thumb_func_start MOD11_022471C4
MOD11_022471C4: ; 0x022471C4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r1, #0
	mov r1, #0
	str r0, [sp]
	add r4, r2, #0
	add r5, r3, #0
	str r1, [sp, #4]
	bl MOD11_0222FF84
	str r0, [sp, #0xc]
	ldr r0, [sp]
	add r1, r4, #0
	bl MOD11_02230270
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	mov r7, #0
	cmp r0, #0
	ble _0224722E
	ldr r4, _02247234 ; =0x00002D4C
_022471EE:
	ldr r0, [sp]
	add r1, r7, #0
	bl MOD11_02230270
	ldr r1, [sp, #8]
	cmp r1, r0
	beq _02247224
	mov r0, #0xb7
	lsl r0, r0, #6
	ldr r1, [r6, r0]
	mov r0, #2
	lsl r0, r0, #0xc
	tst r0, r1
	beq _02247224
	mov r1, #0
	add r2, r6, #0
_0224720E:
	ldrh r0, [r2, r4]
	cmp r5, r0
	beq _0224721C
	add r1, r1, #1
	add r2, r2, #2
	cmp r1, #4
	blt _0224720E
_0224721C:
	cmp r1, #4
	beq _02247224
	mov r0, #1
	str r0, [sp, #4]
_02247224:
	ldr r0, [sp, #0xc]
	add r7, r7, #1
	add r6, #0xc0
	cmp r7, r0
	blt _022471EE
_0224722E:
	ldr r0, [sp, #4]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02247234: .word 0x00002D4C

	thumb_func_start MOD11_02247238
MOD11_02247238: ; 0x02247238
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	mov r6, #0
	bl MOD11_0222FF84
	add r3, r6, #0
	cmp r0, #0
	ble _02247260
	mov r1, #0xb7
	lsl r1, r1, #6
_0224724E:
	ldr r2, [r5, r1]
	tst r2, r4
	beq _02247258
	mov r6, #1
	b _02247260
_02247258:
	add r3, r3, #1
	add r5, #0xc0
	cmp r3, r0
	blt _0224724E
_02247260:
	add r0, r6, #0
	pop {r4, r5, r6, pc}

	thumb_func_start MOD11_02247264
MOD11_02247264: ; 0x02247264
	ldr r2, _02247284 ; =0x0000216C
	mov r0, #0
	str r0, [r1, r2]
	add r0, r2, #0
	mov r3, #1
	sub r0, #0x1c
	str r3, [r1, r0]
	add r0, r2, #0
	sub r0, #0x30
	ldr r3, [r1, r0]
	ldr r0, _02247288 ; =0xFFEFFFFF
	sub r2, #0x30
	and r0, r3
	str r0, [r1, r2]
	bx lr
	nop
_02247284: .word 0x0000216C
_02247288: .word 0xFFEFFFFF

	thumb_func_start MOD11_0224728C
MOD11_0224728C: ; 0x0224728C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	str r0, [sp, #4]
	str r1, [sp, #8]
	bl MOD11_0222FF84
	mov r2, #0
	str r0, [sp, #0x14]
	cmp r0, #0
	ble _022472B0
	ldr r1, _02247310 ; =0x000021EC
_022472A2:
	ldr r0, [sp, #8]
	add r0, r0, r2
	strb r2, [r0, r1]
	ldr r0, [sp, #0x14]
	add r2, r2, #1
	cmp r2, r0
	blt _022472A2
_022472B0:
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	sub r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, #0
	ble _0224730C
_022472BE:
	ldr r0, [sp, #0x10]
	add r4, r0, #1
	ldr r0, [sp, #0x14]
	cmp r4, r0
	bge _02247300
	ldr r1, [sp, #8]
	ldr r0, [sp, #0x10]
	add r6, r1, r0
_022472CE:
	ldr r0, _02247310 ; =0x000021EC
	ldr r1, [sp, #8]
	ldrb r0, [r6, r0]
	str r0, [sp, #0xc]
	ldr r0, [sp, #8]
	ldr r2, [sp, #0xc]
	add r7, r0, r4
	ldr r0, _02247310 ; =0x000021EC
	ldrb r5, [r7, r0]
	mov r0, #1
	str r0, [sp]
	ldr r0, [sp, #4]
	add r3, r5, #0
	bl MOD11_02244248
	cmp r0, #0
	beq _022472F8
	ldr r0, _02247310 ; =0x000021EC
	ldr r1, [sp, #0xc]
	strb r5, [r6, r0]
	strb r1, [r7, r0]
_022472F8:
	ldr r0, [sp, #0x14]
	add r4, r4, #1
	cmp r4, r0
	blt _022472CE
_02247300:
	ldr r0, [sp, #0x10]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [sp, #0x10]
	cmp r1, r0
	blt _022472BE
_0224730C:
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02247310: .word 0x000021EC

	thumb_func_start MOD11_02247314
MOD11_02247314: ; 0x02247314
	push {r3, r4}
	mov r2, #6
	lsl r2, r2, #6
	ldr r2, [r1, r2]
	mov r1, #7
	lsl r1, r1, #0xc
	mov r0, #0
	tst r1, r2
	beq _0224733E
	ldr r4, _02247344 ; =MOD11_0225E278
	add r2, r0, #0
_0224732A:
	ldrh r1, [r4]
	cmp r3, r1
	bne _02247336
	mov r0, #1
	pop {r3, r4}
	bx lr
_02247336:
	add r2, r2, #1
	add r4, r4, #2
	cmp r2, #6
	blo _0224732A
_0224733E:
	pop {r3, r4}
	bx lr
	nop
_02247344: .word MOD11_0225E278

	thumb_func_start MOD11_02247348
MOD11_02247348: ; 0x02247348
	push {r3, r4}
	mov r4, #0xc0
	mul r4, r2
	add r2, r1, r4
	ldr r1, _02247378 ; =0x00002DCC
	mov r0, #0
	ldr r1, [r2, r1]
	lsl r1, r1, #0xd
	lsr r1, r1, #0x1d
	beq _02247374
	ldr r4, _0224737C ; =MOD11_0225E29E
	add r2, r0, #0
_02247360:
	ldrh r1, [r4]
	cmp r3, r1
	bne _0224736C
	mov r0, #1
	pop {r3, r4}
	bx lr
_0224736C:
	add r2, r2, #1
	add r4, r4, #2
	cmp r2, #0xe
	blo _02247360
_02247374:
	pop {r3, r4}
	bx lr
	.align 2, 0
_02247378: .word 0x00002DCC
_0224737C: .word MOD11_0225E29E

	thumb_func_start MOD11_02247380
MOD11_02247380: ; 0x02247380
	push {r4, r5, r6, r7}
	mov r0, #0xc1
	lsl r0, r0, #6
	ldr r3, [r1, r0]
	ldr r0, _022473E8 ; =0x00000183
	cmp r3, r0
	beq _022473E4
	ldr r4, [r1, #0x64]
	mov r0, #0xc0
	add r2, r4, #0
	mul r2, r0
	ldr r4, _022473EC ; =0x00002DCC
	add r0, r1, r2
	ldr r4, [r0, r4]
	lsl r4, r4, #0x13
	lsr r7, r4, #0x1d
	cmp r7, #4
	beq _022473E4
	mov r6, #0
	cmp r7, #0
	bls _022473BA
	ldr r4, _022473F0 ; =0x00002DF0
_022473AC:
	ldrh r5, [r0, r4]
	cmp r3, r5
	beq _022473E4
	add r6, r6, #1
	add r0, r0, #2
	cmp r6, r7
	blo _022473AC
_022473BA:
	add r2, r1, r2
	lsl r0, r6, #1
	add r2, r2, r0
	ldr r0, _022473F0 ; =0x00002DF0
	strh r3, [r2, r0]
	sub r0, #0x24
	add r2, r1, r0
	ldr r3, [r1, #0x64]
	mov r0, #0xc0
	add r1, r3, #0
	mul r1, r0
	ldr r3, [r2, r1]
	ldr r0, _022473F4 ; =0xFFFFE3FF
	and r0, r3
	lsl r3, r3, #0x13
	lsr r3, r3, #0x1d
	add r3, r3, #1
	lsl r3, r3, #0x1d
	lsr r3, r3, #0x13
	orr r0, r3
	str r0, [r2, r1]
_022473E4:
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
_022473E8: .word 0x00000183
_022473EC: .word 0x00002DCC
_022473F0: .word 0x00002DF0
_022473F4: .word 0xFFFFE3FF

	thumb_func_start MOD11_022473F8
MOD11_022473F8: ; 0x022473F8
	mov r3, #0xc0
	mul r3, r2
	add r3, r1, r3
	ldr r1, _02247414 ; =0x00002D4C
	mov r0, #0
_02247402:
	ldrh r2, [r3, r1]
	cmp r2, #0
	beq _02247410
	add r0, r0, #1
	add r3, r3, #2
	cmp r0, #4
	blt _02247402
_02247410:
	bx lr
	nop
_02247414: .word 0x00002D4C

	thumb_func_start MOD11_02247418
MOD11_02247418: ; 0x02247418
	push {r3, r4, r5, r6, r7, lr}
	add r4, r2, #0
	mov r2, #0
	add r5, r0, #0
	add r7, r1, #0
	str r2, [sp]
	bl MOD11_02246D1C
	cmp r0, #0x60
	bne _02247430
	mov r6, #0
	b _02247444
_02247430:
	ldr r0, _02247594 ; =0x00002160
	ldr r6, [r5, r0]
	cmp r6, #0
	bne _02247444
	ldr r0, _02247598 ; =0x00003044
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _0224759C ; =0x000003E2
	ldrb r6, [r1, r0]
_02247444:
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	mov r3, #0xa
	bl MOD11_02246D84
	cmp r0, #1
	bne _02247474
	cmp r6, #0xd
	bne _02247474
	cmp r7, r4
	beq _02247474
	mov r0, #0xc0
	mul r0, r4
	add r1, r5, r0
	ldr r0, _022475A0 ; =0x00002D90
	ldr r0, [r1, r0]
	mov r1, #4
	bl MOD11_022476C0
	ldr r1, _022475A4 ; =0x0000215C
	str r0, [r5, r1]
	mov r0, #0xb2
	str r0, [sp]
_02247474:
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	mov r3, #0xb
	bl MOD11_02246D84
	cmp r0, #1
	bne _022474BA
	cmp r6, #0xb
	bne _022474BA
	ldr r0, _022475A8 ; =0x0000213C
	ldr r1, [r5, r0]
	mov r0, #0x20
	tst r0, r1
	bne _022474BA
	ldr r0, _02247598 ; =0x00003044
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _022475AC ; =0x000003E1
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _022474BA
	mov r0, #0xc0
	mul r0, r4
	add r1, r5, r0
	ldr r0, _022475A0 ; =0x00002D90
	ldr r0, [r1, r0]
	mov r1, #4
	bl MOD11_022476C0
	ldr r1, _022475A4 ; =0x0000215C
	str r0, [r5, r1]
	mov r0, #0xb2
	str r0, [sp]
_022474BA:
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	mov r3, #0x12
	bl MOD11_02246D84
	cmp r0, #1
	bne _02247500
	cmp r6, #0xa
	bne _02247500
	mov r0, #0xc0
	mul r0, r4
	add r1, r5, r0
	ldr r0, _022475B0 ; =0x00002DAC
	ldr r0, [r1, r0]
	mov r1, #0x20
	tst r0, r1
	bne _02247500
	ldr r0, _022475A8 ; =0x0000213C
	ldr r0, [r5, r0]
	tst r0, r1
	bne _02247500
	ldr r0, _02247598 ; =0x00003044
	ldr r3, [r5, r0]
	lsl r0, r3, #4
	add r2, r5, r0
	ldr r0, _022475AC ; =0x000003E1
	ldrb r0, [r2, r0]
	cmp r0, #0
	bne _022474FC
	add r1, #0xe5
	cmp r3, r1
	bne _02247500
_022474FC:
	mov r0, #0xb3
	str r0, [sp]
_02247500:
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	mov r3, #0x2b
	bl MOD11_02246D84
	cmp r0, #1
	bne _0224752C
	ldr r0, _02247598 ; =0x00003044
	ldr r2, _022475B4 ; =MOD11_0225FF84
	ldr r3, [r5, r0]
	mov r1, #0
_02247518:
	ldrh r0, [r2]
	cmp r3, r0
	bne _02247524
	mov r0, #0xb5
	str r0, [sp]
	b _0224752C
_02247524:
	add r1, r1, #1
	add r2, r2, #2
	cmp r1, #0xc
	blo _02247518
_0224752C:
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	mov r3, #0x4e
	bl MOD11_02246D84
	cmp r0, #1
	bne _02247548
	cmp r6, #0xd
	bne _02247548
	cmp r7, r4
	beq _02247548
	mov r0, #0xb6
	str r0, [sp]
_02247548:
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	mov r3, #0x57
	bl MOD11_02246D84
	cmp r0, #1
	bne _0224758E
	cmp r6, #0xb
	bne _0224758E
	ldr r0, _022475A8 ; =0x0000213C
	ldr r1, [r5, r0]
	mov r0, #0x20
	tst r0, r1
	bne _0224758E
	ldr r0, _02247598 ; =0x00003044
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _022475AC ; =0x000003E1
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _0224758E
	mov r0, #0xc0
	mul r0, r4
	add r1, r5, r0
	ldr r0, _022475A0 ; =0x00002D90
	ldr r0, [r1, r0]
	mov r1, #4
	bl MOD11_022476C0
	ldr r1, _022475A4 ; =0x0000215C
	str r0, [r5, r1]
	mov r0, #0xb2
	str r0, [sp]
_0224758E:
	ldr r0, [sp]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02247594: .word 0x00002160
_02247598: .word 0x00003044
_0224759C: .word 0x000003E2
_022475A0: .word 0x00002D90
_022475A4: .word 0x0000215C
_022475A8: .word 0x0000213C
_022475AC: .word 0x000003E1
_022475B0: .word 0x00002DAC
_022475B4: .word MOD11_0225FF84

	thumb_func_start MOD11_022475B8
MOD11_022475B8: ; 0x022475B8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r4, r1, #0
	mov r6, #0
	bl MOD11_02246D1C
	cmp r0, #3
	beq _022475D0
	cmp r0, #0x3d
	beq _02247616
	b _02247696
_022475D0:
	mov r2, #0xc0
	add r0, r4, #0
	mul r0, r2
	ldr r3, _022476B4 ; =0x00002D8C
	add r0, r5, r0
	ldr r1, [r0, r3]
	cmp r1, #0
	beq _02247696
	add r1, r3, #0
	sub r1, #0x31
	ldrsb r1, [r0, r1]
	cmp r1, #0xc
	bge _02247696
	add r2, #0x90
	ldr r1, [r5, r2]
	add r3, #0x48
	ldr r0, [r0, r3]
	add r1, r1, #1
	cmp r1, r0
	beq _02247696
	add r0, r5, #0
	mov r1, #0x11
	add r0, #0x8c
	str r1, [r0]
	add r0, r5, #0
	mov r1, #3
	add r0, #0x88
	str r1, [r0]
	add r0, r5, #0
	add r0, #0x94
	str r4, [r0]
	mov r0, #0xc
	str r0, [sp]
	mov r6, #1
	b _02247696
_02247616:
	ldr r1, _022476B8 ; =0x00002DAC
	mov r0, #0xc0
	add r7, r4, #0
	mul r7, r0
	add r0, r5, r1
	str r0, [sp, #4]
	ldr r0, [r0, r7]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	beq _02247696
	add r0, r5, r7
	sub r1, #0x20
	ldr r0, [r0, r1]
	cmp r0, #0
	beq _02247696
	bl LCRandom
	mov r1, #0xa
	bl _s32_div_f
	cmp r1, #3
	bge _02247696
	ldr r0, [sp, #4]
	mov r1, #7
	ldr r0, [r0, r7]
	tst r1, r0
	beq _02247656
	mov r0, #0x13
	add r1, r6, #0
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0224768A
_02247656:
	ldr r1, _022476BC ; =0x00000F88
	tst r1, r0
	beq _02247666
	mov r0, #0x13
	mov r1, #1
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0224768A
_02247666:
	mov r1, #0x10
	tst r1, r0
	beq _02247676
	mov r0, #0x13
	mov r1, #2
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _0224768A
_02247676:
	mov r1, #0x40
	tst r0, r1
	beq _02247684
	mov r0, #3
	add r1, #0xf0
	str r0, [r5, r1]
	b _0224768A
_02247684:
	mov r0, #4
	add r1, #0xf0
	str r0, [r5, r1]
_0224768A:
	mov r0, #0x46
	lsl r0, r0, #2
	str r4, [r5, r0]
	mov r0, #0xbe
	str r0, [sp]
	mov r6, #1
_02247696:
	cmp r6, #1
	bne _022476AC
	ldr r2, [sp]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022431DC
	ldr r0, [r5, #8]
	str r0, [r5, #0xc]
	mov r0, #0x15
	str r0, [r5, #8]
_022476AC:
	add r0, r6, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022476B4: .word 0x00002D8C
_022476B8: .word 0x00002DAC
_022476BC: .word 0x00000F88

	thumb_func_start MOD11_022476C0
MOD11_022476C0: ; 0x022476C0
	push {r4, lr}
	cmp r0, #0
	bge _022476CC
	mov r4, #0
	mvn r4, r4
	b _022476CE
_022476CC:
	mov r4, #1
_022476CE:
	bl _s32_div_f
	cmp r0, #0
	bne _022476D8
	add r0, r4, #0
_022476D8:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD11_022476DC
MOD11_022476DC: ; 0x022476DC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0xd0
	add r7, r0, #0
	add r4, r1, #0
	bl MOD11_0222FF84
	str r0, [sp, #0x80]
	mov r0, #0
	str r0, [sp, #0x84]
	str r0, [sp, #0xcc]
_022476F0:
	ldr r0, [r4, #0x58]
	cmp r0, #0xf
	bls _022476FA
	bl _02248282
_022476FA:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02247706: ; jump table
	.short _02247726 - _02247706 - 2 ; case 0
	.short _022477A2 - _02247706 - 2 ; case 1
	.short _0224785A - _02247706 - 2 ; case 2
	.short _0224796A - _02247706 - 2 ; case 3
	.short _022479E0 - _02247706 - 2 ; case 4
	.short _02247B34 - _02247706 - 2 ; case 5
	.short _02247C74 - _02247706 - 2 ; case 6
	.short _02247E76 - _02247706 - 2 ; case 7
	.short _02247FCC - _02247706 - 2 ; case 8
	.short _022480A4 - _02247706 - 2 ; case 9
	.short _02248118 - _02247706 - 2 ; case 10
	.short _022481A6 - _02247706 - 2 ; case 11
	.short _022481C4 - _02247706 - 2 ; case 12
	.short _022481FE - _02247706 - 2 ; case 13
	.short _0224823A - _02247706 - 2 ; case 14
	.short _0224827A - _02247706 - 2 ; case 15
_02247726:
	ldr r0, _02247A18 ; =0x00003121
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _02247798
	add r0, r7, #0
	bl MOD11_0223125C
	cmp r0, #0xf
	bhi _0224778C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02247744: ; jump table
	.short _0224778C - _02247744 - 2 ; case 0
	.short _0224778C - _02247744 - 2 ; case 1
	.short _02247764 - _02247744 - 2 ; case 2
	.short _02247764 - _02247744 - 2 ; case 3
	.short _02247764 - _02247744 - 2 ; case 4
	.short _0224776E - _02247744 - 2 ; case 5
	.short _0224776E - _02247744 - 2 ; case 6
	.short _0224776E - _02247744 - 2 ; case 7
	.short _0224778C - _02247744 - 2 ; case 8
	.short _0224778C - _02247744 - 2 ; case 9
	.short _0224777A - _02247744 - 2 ; case 10
	.short _0224778C - _02247744 - 2 ; case 11
	.short _0224778C - _02247744 - 2 ; case 12
	.short _0224778C - _02247744 - 2 ; case 13
	.short _02247784 - _02247744 - 2 ; case 14
	.short _02247784 - _02247744 - 2 ; case 15
_02247764:
	ldr r0, _02247A1C ; =0x0000010F
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _0224778C
_0224776E:
	mov r0, #0x11
	lsl r0, r0, #4
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _0224778C
_0224777A:
	ldr r0, _02247A20 ; =0x00000111
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _0224778C
_02247784:
	ldr r0, _02247A24 ; =0x00000112
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
_0224778C:
	ldr r0, [sp, #0x84]
	cmp r0, #1
	bne _02247798
	ldr r0, _02247A18 ; =0x00003121
	mov r1, #1
	strb r1, [r4, r0]
_02247798:
	ldr r0, [r4, #0x58]
	add r0, r0, #1
	str r0, [r4, #0x58]
	bl _02248282
_022477A2:
	ldr r0, [sp, #0x80]
	mov r6, #0
	cmp r0, #0
	ble _02247846
	ldr r0, _02247A28 ; =0x00002D68
	add r0, r4, r0
	str r0, [sp, #0x90]
_022477B0:
	ldr r0, _02247A2C ; =0x000021EC
	add r1, r4, r6
	ldrb r5, [r1, r0]
	add r0, r7, #0
	mov r2, #0
	add r1, r5, #0
	bl MOD11_02230308
	str r0, [sp, #0x88]
	add r0, r7, #0
	add r1, r5, #0
	mov r2, #2
	bl MOD11_02230308
	add r2, r0, #0
	ldr r1, [sp, #0x88]
	add r0, r4, #0
	bl MOD11_0224C84C
	mov r1, #0x12
	lsl r1, r1, #4
	str r0, [r4, r1]
	mov r0, #0xc0
	mul r0, r5
	ldr r1, [sp, #0x90]
	str r0, [sp, #0x8c]
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	bne _0224783E
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r2, [r4, r0]
	cmp r2, #0xff
	beq _0224783E
	ldr r0, [sp, #0x8c]
	add r1, r4, r0
	ldr r0, _02247A30 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0224783E
	mov r0, #0xc0
	mul r0, r2
	add r1, r4, r0
	ldr r0, _02247A30 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0224783E
	add r0, r4, #0
	add r1, r5, #0
	bl MOD11_02246D1C
	cmp r0, #0x24
	bne _0224783E
	ldr r1, [sp, #0x90]
	ldr r0, [sp, #0x8c]
	ldr r1, [r1, r0]
	mov r0, #4
	add r2, r1, #0
	orr r2, r0
	ldr r1, [sp, #0x90]
	ldr r0, [sp, #0x8c]
	str r2, [r1, r0]
	mov r0, #0x46
	lsl r0, r0, #2
	str r5, [r4, r0]
	mov r0, #0xbb
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _02247846
_0224783E:
	ldr r0, [sp, #0x80]
	add r6, r6, #1
	cmp r6, r0
	blt _022477B0
_02247846:
	ldr r0, [sp, #0x80]
	cmp r6, r0
	beq _02247850
	bl _02248282
_02247850:
	ldr r0, [r4, #0x58]
	add r0, r0, #1
	str r0, [r4, #0x58]
	bl _02248282
_0224785A:
	mov r0, #0
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x80]
	cmp r0, #0
	ble _02247958
	ldr r0, _02247A28 ; =0x00002D68
	add r6, r4, r0
	mov r0, #1
	str r0, [sp, #0xbc]
	str r0, [sp, #0xb8]
	str r0, [sp, #0xb4]
	str r0, [sp, #0xb0]
_02247872:
	ldr r0, [sp, #0x2c]
	add r1, r4, r0
	ldr r0, _02247A2C ; =0x000021EC
	ldrb r1, [r1, r0]
	mov r0, #0xc0
	add r5, r1, #0
	mul r5, r0
	ldr r0, [r6, r5]
	str r1, [sp, #0x10]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bne _0224793C
	ldr r0, _02247A30 ; =0x00002D8C
	add r1, r4, r5
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0224793C
	ldr r1, [sp, #0x10]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x2d
	bgt _022478A8
	bge _022478D8
	cmp r0, #2
	beq _022478B6
	b _0224793C
_022478A8:
	cmp r0, #0x46
	bgt _022478B0
	beq _022478FA
	b _0224793C
_022478B0:
	cmp r0, #0x75
	beq _0224791C
	b _0224793C
_022478B6:
	ldr r0, [r6, r5]
	ldr r1, [sp, #0xb0]
	bic r0, r1
	mov r1, #1
	orr r0, r1
	str r0, [r6, r5]
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r0, #2
	tst r0, r1
	bne _0224793C
	mov r0, #0xb7
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _0224793C
_022478D8:
	ldr r0, [r6, r5]
	ldr r1, [sp, #0xb4]
	bic r0, r1
	mov r1, #1
	orr r0, r1
	str r0, [r6, r5]
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r0, #8
	tst r0, r1
	bne _0224793C
	mov r0, #0xb8
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _0224793C
_022478FA:
	ldr r0, [r6, r5]
	ldr r1, [sp, #0xb8]
	bic r0, r1
	mov r1, #1
	orr r0, r1
	str r0, [r6, r5]
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r0, #0x20
	tst r0, r1
	bne _0224793C
	mov r0, #0xb9
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _0224793C
_0224791C:
	ldr r0, [r6, r5]
	ldr r1, [sp, #0xbc]
	bic r0, r1
	mov r1, #1
	orr r0, r1
	str r0, [r6, r5]
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r0, #0x80
	tst r0, r1
	bne _0224793C
	mov r0, #0xfc
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
_0224793C:
	ldr r0, [sp, #0x84]
	cmp r0, #1
	bne _0224794C
	mov r1, #0x46
	ldr r0, [sp, #0x10]
	lsl r1, r1, #2
	str r0, [r4, r1]
	b _02247958
_0224794C:
	ldr r0, [sp, #0x2c]
	add r1, r0, #1
	ldr r0, [sp, #0x80]
	str r1, [sp, #0x2c]
	cmp r1, r0
	blt _02247872
_02247958:
	ldr r1, [sp, #0x2c]
	ldr r0, [sp, #0x80]
	cmp r1, r0
	bne _022479D2
	ldr r0, [r4, #0x58]
	add r0, r0, #1
	str r0, [r4, #0x58]
	bl _02248282
_0224796A:
	ldr r0, [sp, #0x80]
	mov r5, #0
	cmp r0, #0
	ble _022479CC
	ldr r0, _02247A28 ; =0x00002D68
	add r0, r4, r0
	str r0, [sp, #0x94]
_02247978:
	ldr r0, _02247A2C ; =0x000021EC
	add r1, r4, r5
	ldrb r1, [r1, r0]
	mov r0, #0xc0
	add r6, r1, #0
	mul r6, r0
	ldr r0, [sp, #0x94]
	str r1, [sp, #0x14]
	ldr r0, [r0, r6]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bne _022479C4
	ldr r0, _02247A30 ; =0x00002D8C
	add r1, r4, r6
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _022479C4
	ldr r1, [sp, #0x14]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x16
	bne _022479C4
	ldr r0, [sp, #0x94]
	ldr r1, [r0, r6]
	mov r0, #2
	orr r1, r0
	ldr r0, [sp, #0x94]
	str r1, [r0, r6]
	mov r1, #0x46
	ldr r0, [sp, #0x14]
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0xba
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _022479CC
_022479C4:
	ldr r0, [sp, #0x80]
	add r5, r5, #1
	cmp r5, r0
	blt _02247978
_022479CC:
	ldr r0, [sp, #0x80]
	cmp r5, r0
	beq _022479D6
_022479D2:
	bl _02248282
_022479D6:
	ldr r0, [r4, #0x58]
	add r0, r0, #1
	str r0, [r4, #0x58]
	bl _02248282
_022479E0:
	mov r0, #0
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x80]
	cmp r0, #0
	bgt _022479EC
	b _02247B22
_022479EC:
	ldr r0, _02247A28 ; =0x00002D68
	add r0, r4, r0
	str r0, [sp, #0x9c]
_022479F2:
	ldr r0, [sp, #0x30]
	add r1, r4, r0
	ldr r0, _02247A2C ; =0x000021EC
	ldrb r1, [r1, r0]
	mov r0, #0xc0
	mul r0, r1
	str r1, [sp, #0x18]
	ldr r1, [sp, #0x9c]
	str r0, [sp, #0x98]
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	beq _02247A0E
	b _02247B14
_02247A0E:
	ldr r0, [sp, #0x98]
	add r1, r4, r0
	ldr r0, _02247A30 ; =0x00002D8C
	b _02247A34
	nop
_02247A18: .word 0x00003121
_02247A1C: .word 0x0000010F
_02247A20: .word 0x00000111
_02247A24: .word 0x00000112
_02247A28: .word 0x00002D68
_02247A2C: .word 0x000021EC
_02247A30: .word 0x00002D8C
_02247A34:
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02247B14
	ldr r1, [sp, #0x18]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x58
	bne _02247B14
	mov r0, #0
	str r0, [sp, #0x78]
	str r0, [sp, #0x74]
	str r0, [sp, #0x7c]
	ldr r0, [sp, #0x80]
	cmp r0, #0
	ble _02247ACE
	add r5, r4, #0
_02247A56:
	ldr r1, [sp, #0x18]
	add r0, r7, #0
	bl MOD11_02230270
	add r6, r0, #0
	ldr r1, [sp, #0x7c]
	add r0, r7, #0
	bl MOD11_02230270
	cmp r6, r0
	beq _02247AC0
	ldr r0, _02247D60 ; =0x00002DB0
	ldr r1, [r5, r0]
	mov r0, #1
	lsl r0, r0, #0x18
	tst r0, r1
	bne _02247AC0
	ldr r0, _02247D64 ; =0x00002D8C
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _02247AC0
	ldr r0, _02247D68 ; =0x00002D5A
	ldrsb r0, [r5, r0]
	lsl r2, r0, #1
	ldr r0, _02247D6C ; =MOD11_0225E284
	add r1, r0, r2
	ldr r0, _02247D70 ; =0x00002D44
	ldrb r1, [r1, #1]
	ldrh r3, [r5, r0]
	ldr r0, _02247D6C ; =MOD11_0225E284
	ldrb r0, [r0, r2]
	mul r0, r3
	bl _s32_div_f
	ldr r1, [sp, #0x78]
	add r0, r1, r0
	str r0, [sp, #0x78]
	ldr r0, _02247D74 ; =0x00002D5D
	ldrsb r0, [r5, r0]
	lsl r2, r0, #1
	ldr r0, _02247D6C ; =MOD11_0225E284
	add r1, r0, r2
	ldr r0, _02247D78 ; =0x00002D4A
	ldrb r1, [r1, #1]
	ldrh r3, [r5, r0]
	ldr r0, _02247D6C ; =MOD11_0225E284
	ldrb r0, [r0, r2]
	mul r0, r3
	bl _s32_div_f
	ldr r1, [sp, #0x74]
	add r0, r1, r0
	str r0, [sp, #0x74]
_02247AC0:
	ldr r0, [sp, #0x7c]
	add r5, #0xc0
	add r1, r0, #1
	ldr r0, [sp, #0x80]
	str r1, [sp, #0x7c]
	cmp r1, r0
	blt _02247A56
_02247ACE:
	ldr r1, [sp, #0x9c]
	ldr r0, [sp, #0x98]
	ldr r1, [r1, r0]
	mov r0, #8
	add r2, r1, #0
	orr r2, r0
	ldr r1, [sp, #0x9c]
	ldr r0, [sp, #0x98]
	str r2, [r1, r0]
	ldr r1, [sp, #0x78]
	ldr r0, [sp, #0x74]
	add r0, r1, r0
	beq _02247B14
	ldr r0, [sp, #0x74]
	cmp r1, r0
	blt _02247AF2
	mov r1, #0x12
	b _02247AF4
_02247AF2:
	mov r1, #0xf
_02247AF4:
	add r0, r4, #0
	add r0, #0x8c
	str r1, [r0]
	add r0, r4, #0
	mov r1, #3
	add r0, #0x88
	str r1, [r0]
	add r1, r4, #0
	ldr r0, [sp, #0x18]
	add r1, #0x94
	str r0, [r1]
	mov r0, #0xc
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _02247B22
_02247B14:
	ldr r0, [sp, #0x30]
	add r1, r0, #1
	ldr r0, [sp, #0x80]
	str r1, [sp, #0x30]
	cmp r1, r0
	bge _02247B22
	b _022479F2
_02247B22:
	ldr r1, [sp, #0x30]
	ldr r0, [sp, #0x80]
	cmp r1, r0
	beq _02247B2C
	b _02248282
_02247B2C:
	ldr r0, [r4, #0x58]
	add r0, r0, #1
	str r0, [r4, #0x58]
	b _02248282
_02247B34:
	mov r0, #0
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x80]
	cmp r0, #0
	bgt _02247B40
	b _02247C62
_02247B40:
	ldr r0, _02247D7C ; =0x00002D68
	add r6, r4, r0
_02247B44:
	ldr r0, [sp, #0x34]
	add r1, r4, r0
	ldr r0, _02247D80 ; =0x000021EC
	ldrb r1, [r1, r0]
	mov r0, #0xc0
	add r5, r1, #0
	mul r5, r0
	ldr r0, [r6, r5]
	str r1, [sp, #0x1c]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	bne _02247C54
	ldr r0, _02247D64 ; =0x00002D8C
	add r1, r4, r5
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02247C54
	ldr r1, [sp, #0x1c]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x6b
	bne _02247C54
	ldr r1, [r6, r5]
	mov r0, #0x10
	orr r0, r1
	str r0, [r6, r5]
	mov r0, #0
	str r0, [sp, #0x70]
	ldr r0, [sp, #0x80]
	cmp r0, #0
	ble _02247C40
	add r0, r4, r5
	str r4, [sp, #0x50]
	str r0, [sp, #0x4c]
_02247B8A:
	ldr r1, [sp, #0x1c]
	add r0, r7, #0
	bl MOD11_02230270
	add r5, r0, #0
	ldr r1, [sp, #0x70]
	add r0, r7, #0
	bl MOD11_02230270
	cmp r5, r0
	beq _02247C2E
	ldr r1, [sp, #0x50]
	ldr r0, _02247D64 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02247C2E
	mov r0, #0
	str r0, [sp, #0x6c]
	add r6, r1, #0
_02247BB0:
	ldr r0, _02247D84 ; =0x00002D4C
	ldrh r5, [r6, r0]
	cmp r5, #0
	beq _02247C1C
	mov r0, #0
	str r0, [sp, #0xc8]
	ldr r0, [sp, #0x70]
	add r1, r4, #0
	str r0, [sp]
	ldr r0, [sp, #0x1c]
	add r2, r5, #0
	str r0, [sp, #4]
	ldr r0, _02247D88 ; =0x00002144
	mov r3, #0
	ldr r0, [r4, r0]
	str r0, [sp, #8]
	add r0, sp, #0xc8
	str r0, [sp, #0xc]
	add r0, r7, #0
	bl MOD11_02246274
	ldr r1, _02247D88 ; =0x00002144
	str r0, [r4, r1]
	ldr r1, [sp, #0xc8]
	mov r0, #8
	tst r0, r1
	bne _02247C1C
	add r0, r4, #0
	add r1, r5, #0
	bl MOD11_0224C8C0
	cmp r0, #0
	bne _02247C1C
	ldr r1, [sp, #0xc8]
	mov r0, #2
	tst r0, r1
	bne _02247C16
	lsl r0, r5, #4
	add r1, r4, r0
	ldr r0, _02247D8C ; =0x000003DE
	ldrh r0, [r1, r0]
	cmp r0, #0x26
	bne _02247C1C
	ldr r1, [sp, #0x4c]
	ldr r0, _02247D90 ; =0x00002D74
	ldr r2, [sp, #0x50]
	ldrb r0, [r1, r0]
	ldr r1, _02247D90 ; =0x00002D74
	ldrb r1, [r2, r1]
	cmp r0, r1
	bhi _02247C1C
_02247C16:
	mov r0, #1
	str r0, [sp, #0x84]
	b _02247C28
_02247C1C:
	ldr r0, [sp, #0x6c]
	add r6, r6, #2
	add r0, r0, #1
	str r0, [sp, #0x6c]
	cmp r0, #4
	blt _02247BB0
_02247C28:
	ldr r0, [sp, #0x84]
	cmp r0, #1
	beq _02247C40
_02247C2E:
	ldr r0, [sp, #0x50]
	add r0, #0xc0
	str r0, [sp, #0x50]
	ldr r0, [sp, #0x70]
	add r1, r0, #1
	ldr r0, [sp, #0x80]
	str r1, [sp, #0x70]
	cmp r1, r0
	blt _02247B8A
_02247C40:
	ldr r0, [sp, #0x84]
	cmp r0, #1
	bne _02247C62
	mov r1, #0x46
	ldr r0, [sp, #0x1c]
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0xc2
	str r0, [sp, #0xcc]
	b _02247C62
_02247C54:
	ldr r0, [sp, #0x34]
	add r1, r0, #1
	ldr r0, [sp, #0x80]
	str r1, [sp, #0x34]
	cmp r1, r0
	bge _02247C62
	b _02247B44
_02247C62:
	ldr r1, [sp, #0x34]
	ldr r0, [sp, #0x80]
	cmp r1, r0
	beq _02247C6C
	b _02248282
_02247C6C:
	ldr r0, [r4, #0x58]
	add r0, r0, #1
	str r0, [r4, #0x58]
	b _02248282
_02247C74:
	mov r0, #0
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x80]
	cmp r0, #0
	bgt _02247C80
	b _02247E64
_02247C80:
	ldr r0, _02247D7C ; =0x00002D68
	add r6, r4, r0
_02247C84:
	ldr r0, [sp, #0x38]
	add r1, r4, r0
	ldr r0, _02247D80 ; =0x000021EC
	ldrb r1, [r1, r0]
	mov r0, #0xc0
	add r5, r1, #0
	mul r5, r0
	ldr r0, [r6, r5]
	str r1, [sp, #0x20]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1f
	bne _02247CB2
	ldr r0, _02247D64 ; =0x00002D8C
	add r1, r4, r5
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02247CB2
	ldr r1, [sp, #0x20]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x6c
	beq _02247CB4
_02247CB2:
	b _02247E56
_02247CB4:
	ldr r1, [r6, r5]
	mov r0, #0x20
	orr r0, r1
	str r0, [r6, r5]
	mov r5, #0
	ldr r0, [sp, #0x80]
	str r5, [sp, #0x5c]
	str r5, [sp, #0x68]
	cmp r0, #0
	bgt _02247CCA
	b _02247DF2
_02247CCA:
	str r4, [sp, #0x58]
_02247CCC:
	ldr r1, [sp, #0x20]
	add r0, r7, #0
	bl MOD11_02230270
	add r6, r0, #0
	ldr r1, [sp, #0x68]
	add r0, r7, #0
	bl MOD11_02230270
	cmp r6, r0
	beq _02247DDE
	ldr r1, [sp, #0x58]
	ldr r0, _02247D64 ; =0x00002D8C
	ldr r1, [r1, r0]
	cmp r1, #0
	beq _02247DDE
	ldr r0, [sp, #0x5c]
	add r0, r0, r1
	str r0, [sp, #0x5c]
	mov r0, #0
	str r0, [sp, #0x64]
	ldr r0, [sp, #0x58]
	str r0, [sp, #0x54]
_02247CFA:
	ldr r1, [sp, #0x54]
	ldr r0, _02247D84 ; =0x00002D4C
	ldrh r6, [r1, r0]
	ldr r1, _02247D94 ; =0x000003E1
	lsl r0, r6, #4
	add r0, r4, r0
	ldrb r1, [r0, r1]
	str r1, [sp, #0x60]
	cmp r1, #1
	bne _02247DB2
	ldr r1, _02247D8C ; =0x000003DE
	ldrh r0, [r0, r1]
	cmp r0, #0x59
	bgt _02247D1E
	bge _02247D46
	cmp r0, #0x26
	beq _02247D2C
	b _02247D98
_02247D1E:
	cmp r0, #0x90
	bgt _02247D26
	beq _02247D46
	b _02247D98
_02247D26:
	cmp r0, #0xe3
	beq _02247D46
	b _02247D98
_02247D2C:
	cmp r5, #0x96
	blo _02247D3C
	bne _02247DCE
	bl LCRandom
	mov r1, #1
	tst r0, r1
	beq _02247DCE
_02247D3C:
	mov r5, #0x96
	add r0, r5, #0
	add r0, #0x8e
	str r6, [r4, r0]
	b _02247DCE
_02247D46:
	cmp r5, #0x78
	blo _02247D56
	bne _02247DCE
	bl LCRandom
	mov r1, #1
	tst r0, r1
	beq _02247DCE
_02247D56:
	mov r5, #0x78
	add r0, r5, #0
	add r0, #0xac
	str r6, [r4, r0]
	b _02247DCE
	.align 2, 0
_02247D60: .word 0x00002DB0
_02247D64: .word 0x00002D8C
_02247D68: .word 0x00002D5A
_02247D6C: .word MOD11_0225E284
_02247D70: .word 0x00002D44
_02247D74: .word 0x00002D5D
_02247D78: .word 0x00002D4A
_02247D7C: .word 0x00002D68
_02247D80: .word 0x000021EC
_02247D84: .word 0x00002D4C
_02247D88: .word 0x00002144
_02247D8C: .word 0x000003DE
_02247D90: .word 0x00002D74
_02247D94: .word 0x000003E1
_02247D98:
	cmp r5, #0x50
	blo _02247DA8
	bne _02247DCE
	bl LCRandom
	mov r1, #1
	tst r0, r1
	beq _02247DCE
_02247DA8:
	mov r5, #0x50
	add r0, r5, #0
	add r0, #0xd4
	str r6, [r4, r0]
	b _02247DCE
_02247DB2:
	add r0, r1, #0
	cmp r5, r0
	blo _02247DC6
	cmp r5, r0
	bne _02247DCE
	bl LCRandom
	mov r1, #1
	tst r0, r1
	beq _02247DCE
_02247DC6:
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r5, [sp, #0x60]
	str r6, [r4, r0]
_02247DCE:
	ldr r0, [sp, #0x54]
	add r0, r0, #2
	str r0, [sp, #0x54]
	ldr r0, [sp, #0x64]
	add r0, r0, #1
	str r0, [sp, #0x64]
	cmp r0, #4
	blt _02247CFA
_02247DDE:
	ldr r0, [sp, #0x58]
	add r0, #0xc0
	str r0, [sp, #0x58]
	ldr r0, [sp, #0x68]
	add r1, r0, #1
	ldr r0, [sp, #0x80]
	str r1, [sp, #0x68]
	cmp r1, r0
	bge _02247DF2
	b _02247CCC
_02247DF2:
	cmp r5, #0
	beq _02247E08
	mov r1, #0x46
	ldr r0, [sp, #0x20]
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0xc3
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _02247E64
_02247E08:
	ldr r0, [sp, #0x5c]
	cmp r0, #0
	beq _02247E64
	ldr r2, [sp, #0x20]
	add r0, r7, #0
	add r1, r4, #0
	bl MOD11_022482A4
	add r5, r0, #0
	add r0, r7, #0
	add r1, r4, #0
	add r2, r5, #0
	bl MOD11_022473F8
	add r6, r0, #0
	bl LCRandom
	add r1, r6, #0
	bl _s32_div_f
	mov r0, #0xc0
	add r2, r5, #0
	mul r2, r0
	lsl r3, r1, #1
	add r1, r4, r2
	add r2, r3, r1
	ldr r1, _02248144 ; =0x00002D4C
	ldrh r2, [r2, r1]
	add r1, r0, #0
	add r1, #0x64
	str r2, [r4, r1]
	ldr r1, [sp, #0x20]
	add r0, #0x58
	str r1, [r4, r0]
	mov r0, #0xc3
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _02247E64
_02247E56:
	ldr r0, [sp, #0x38]
	add r1, r0, #1
	ldr r0, [sp, #0x80]
	str r1, [sp, #0x38]
	cmp r1, r0
	bge _02247E64
	b _02247C84
_02247E64:
	ldr r1, [sp, #0x38]
	ldr r0, [sp, #0x80]
	cmp r1, r0
	beq _02247E6E
	b _02248282
_02247E6E:
	ldr r0, [r4, #0x58]
	add r0, r0, #1
	str r0, [r4, #0x58]
	b _02248282
_02247E76:
	mov r0, #0
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x80]
	cmp r0, #0
	bgt _02247E82
	b _02247FBA
_02247E82:
	ldr r0, _02248148 ; =0x00002D68
	add r0, r4, r0
	str r0, [sp, #0xa0]
_02247E88:
	ldr r0, [sp, #0x3c]
	add r1, r4, r0
	ldr r0, _0224814C ; =0x000021EC
	ldrb r5, [r1, r0]
	mov r0, #0xc0
	add r6, r5, #0
	mul r6, r0
	ldr r0, [sp, #0xa0]
	ldr r0, [r0, r6]
	lsl r0, r0, #0x17
	lsr r0, r0, #0x1f
	bne _02247F9A
	ldr r0, _02248150 ; =0x00002D8C
	add r1, r4, r6
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02247F9A
	add r0, r4, #0
	add r1, r5, #0
	bl MOD11_02246D1C
	cmp r0, #0x77
	bne _02247F9A
	ldr r0, [sp, #0xa0]
	ldr r1, [r0, r6]
	mov r0, #1
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, [sp, #0xa0]
	str r1, [r0, r6]
	add r0, r7, #0
	bl MOD11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _02247F74
	add r0, r7, #0
	add r1, r5, #0
	mov r2, #0
	bl MOD11_02230308
	str r0, [sp, #0xc0]
	add r0, r7, #0
	add r1, r5, #0
	mov r2, #2
	bl MOD11_02230308
	ldr r2, [sp, #0xc0]
	mov r1, #0xc0
	mul r1, r2
	ldr r2, _02248150 ; =0x00002D8C
	add r1, r4, r1
	ldr r3, [r1, r2]
	str r0, [sp, #0xc4]
	cmp r3, #0
	beq _02247F38
	add r2, #0x2c
	ldrh r2, [r1, r2]
	cmp r2, #0
	beq _02247F38
	mov r2, #0xc0
	mul r2, r0
	add r0, r4, r2
	ldr r2, _02248150 ; =0x00002D8C
	ldr r2, [r0, r2]
	cmp r2, #0
	beq _02247F38
	ldr r2, _02248154 ; =0x00002DB8
	ldrh r0, [r0, r2]
	cmp r0, #0
	beq _02247F38
	bl LCRandom
	lsl r0, r0, #0x1f
	lsr r1, r0, #0x1d
	add r0, sp, #0xc0
	ldr r1, [r0, r1]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _02248154 ; =0x00002DB8
	ldrh r1, [r1, r0]
	mov r0, #0x4a
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #1
	str r0, [sp, #0x84]
	b _02247F9A
_02247F38:
	cmp r3, #0
	beq _02247F50
	ldr r0, _02248154 ; =0x00002DB8
	ldrh r1, [r1, r0]
	cmp r1, #0
	beq _02247F50
	mov r0, #0x4a
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #1
	str r0, [sp, #0x84]
	b _02247F9A
_02247F50:
	ldr r1, [sp, #0xc4]
	mov r0, #0xc0
	mul r0, r1
	ldr r1, _02248150 ; =0x00002D8C
	add r0, r4, r0
	ldr r1, [r0, r1]
	cmp r1, #0
	beq _02247F9A
	ldr r1, _02248154 ; =0x00002DB8
	ldrh r1, [r0, r1]
	cmp r1, #0
	beq _02247F9A
	mov r0, #0x4a
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #1
	str r0, [sp, #0x84]
	b _02247F9A
_02247F74:
	mov r0, #1
	add r1, r5, #0
	eor r1, r0
	mov r0, #0xc0
	mul r0, r1
	ldr r1, _02248150 ; =0x00002D8C
	add r0, r4, r0
	ldr r1, [r0, r1]
	cmp r1, #0
	beq _02247F9A
	ldr r1, _02248154 ; =0x00002DB8
	ldrh r1, [r0, r1]
	cmp r1, #0
	beq _02247F9A
	mov r0, #0x4a
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #1
	str r0, [sp, #0x84]
_02247F9A:
	ldr r0, [sp, #0x84]
	cmp r0, #1
	bne _02247FAC
	mov r0, #0x46
	lsl r0, r0, #2
	str r5, [r4, r0]
	mov r0, #0xfd
	str r0, [sp, #0xcc]
	b _02247FBA
_02247FAC:
	ldr r0, [sp, #0x3c]
	add r1, r0, #1
	ldr r0, [sp, #0x80]
	str r1, [sp, #0x3c]
	cmp r1, r0
	bge _02247FBA
	b _02247E88
_02247FBA:
	ldr r1, [sp, #0x3c]
	ldr r0, [sp, #0x80]
	cmp r1, r0
	beq _02247FC4
	b _02248282
_02247FC4:
	ldr r0, [r4, #0x58]
	add r0, r0, #1
	str r0, [r4, #0x58]
	b _02248282
_02247FCC:
	mov r0, #0
	str r0, [sp, #0x40]
	ldr r0, [sp, #0x80]
	cmp r0, #0
	ble _02248094
	ldr r0, _02248148 ; =0x00002D68
	add r0, r4, r0
	str r0, [sp, #0xa4]
_02247FDC:
	ldr r0, [sp, #0x40]
	add r1, r4, r0
	ldr r0, _0224814C ; =0x000021EC
	ldrb r6, [r1, r0]
	mov r0, #0xc0
	add r5, r6, #0
	mul r5, r0
	ldr r0, [sp, #0xa4]
	ldr r0, [r0, r5]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	bne _02248038
	ldr r0, _02248150 ; =0x00002D8C
	add r1, r4, r5
	ldr r0, [r1, r0]
	str r1, [sp, #0x48]
	cmp r0, #0
	beq _02248038
	add r0, r4, #0
	add r1, r6, #0
	bl MOD11_02246D1C
	cmp r0, #0x70
	bne _02248038
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r2, [r4, r0]
	ldr r1, [sp, #0x48]
	ldr r0, _02248158 ; =0x00002DD8
	ldr r0, [r1, r0]
	cmp r2, r0
	bgt _02248038
	ldr r0, [sp, #0xa4]
	mov r2, #0x40
	ldr r0, [r0, r5]
	add r1, r0, #0
	orr r1, r2
	ldr r0, [sp, #0xa4]
	add r2, #0xd8
	str r1, [r0, r5]
	str r6, [r4, r2]
	mov r0, #0xc4
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _02248094
_02248038:
	ldr r0, [sp, #0xa4]
	ldr r0, [r0, r5]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bne _02248088
	ldr r0, _02248150 ; =0x00002D8C
	add r1, r4, r5
	ldr r0, [r1, r0]
	str r1, [sp, #0x44]
	cmp r0, #0
	beq _02248088
	add r0, r4, #0
	add r1, r6, #0
	bl MOD11_02246D1C
	cmp r0, #0x70
	bne _02248088
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r2, [r4, r0]
	ldr r1, [sp, #0x44]
	ldr r0, _02248158 ; =0x00002DD8
	ldr r0, [r1, r0]
	sub r0, r2, r0
	cmp r0, #5
	bne _02248088
	ldr r0, [sp, #0xa4]
	mov r2, #0x80
	ldr r0, [r0, r5]
	add r1, r0, #0
	orr r1, r2
	ldr r0, [sp, #0xa4]
	add r2, #0x98
	str r1, [r0, r5]
	str r6, [r4, r2]
	mov r0, #0xc5
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _02248094
_02248088:
	ldr r0, [sp, #0x40]
	add r1, r0, #1
	ldr r0, [sp, #0x80]
	str r1, [sp, #0x40]
	cmp r1, r0
	blt _02247FDC
_02248094:
	ldr r1, [sp, #0x40]
	ldr r0, [sp, #0x80]
	cmp r1, r0
	bne _0224810E
	ldr r0, [r4, #0x58]
	add r0, r0, #1
	str r0, [r4, #0x58]
	b _02248282
_022480A4:
	ldr r0, [sp, #0x80]
	mov r5, #0
	cmp r0, #0
	ble _02248108
	ldr r0, _02248148 ; =0x00002D68
	add r0, r4, r0
	str r0, [sp, #0xa8]
_022480B2:
	ldr r0, _0224814C ; =0x000021EC
	add r1, r4, r5
	ldrb r1, [r1, r0]
	mov r0, #0xc0
	add r6, r1, #0
	mul r6, r0
	ldr r0, [sp, #0xa8]
	str r1, [sp, #0x24]
	ldr r0, [r0, r6]
	lsl r0, r0, #0x16
	lsr r0, r0, #0x1f
	bne _02248100
	ldr r0, _02248150 ; =0x00002D8C
	add r1, r4, r6
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02248100
	ldr r1, [sp, #0x24]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x68
	bne _02248100
	ldr r0, [sp, #0xa8]
	mov r2, #2
	ldr r0, [r0, r6]
	lsl r2, r2, #8
	add r1, r0, #0
	orr r1, r2
	ldr r0, [sp, #0xa8]
	sub r2, #0xe8
	str r1, [r0, r6]
	ldr r0, [sp, #0x24]
	str r0, [r4, r2]
	mov r0, #0xb1
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _02248108
_02248100:
	ldr r0, [sp, #0x80]
	add r5, r5, #1
	cmp r5, r0
	blt _022480B2
_02248108:
	ldr r0, [sp, #0x80]
	cmp r5, r0
	beq _02248110
_0224810E:
	b _02248282
_02248110:
	ldr r0, [r4, #0x58]
	add r0, r0, #1
	str r0, [r4, #0x58]
	b _02248282
_02248118:
	ldr r0, [sp, #0x80]
	mov r5, #0
	cmp r0, #0
	ble _02248198
	ldr r0, _02248148 ; =0x00002D68
	add r0, r4, r0
	str r0, [sp, #0xac]
_02248126:
	ldr r0, _0224814C ; =0x000021EC
	add r1, r4, r5
	ldrb r1, [r1, r0]
	mov r0, #0xc0
	add r6, r1, #0
	mul r6, r0
	ldr r0, [sp, #0xac]
	str r1, [sp, #0x28]
	ldr r0, [r0, r6]
	lsl r0, r0, #0x15
	lsr r0, r0, #0x1f
	bne _02248190
	ldr r0, _02248150 ; =0x00002D8C
	b _0224815C
	nop
_02248144: .word 0x00002D4C
_02248148: .word 0x00002D68
_0224814C: .word 0x000021EC
_02248150: .word 0x00002D8C
_02248154: .word 0x00002DB8
_02248158: .word 0x00002DD8
_0224815C:
	add r1, r4, r6
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02248190
	ldr r1, [sp, #0x28]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x2e
	bne _02248190
	ldr r0, [sp, #0xac]
	ldr r1, [r0, r6]
	mov r0, #1
	lsl r0, r0, #0xa
	orr r1, r0
	ldr r0, [sp, #0xac]
	str r1, [r0, r6]
	mov r1, #0x46
	ldr r0, [sp, #0x28]
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r1, #5
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _02248198
_02248190:
	ldr r0, [sp, #0x80]
	add r5, r5, #1
	cmp r5, r0
	blt _02248126
_02248198:
	ldr r0, [sp, #0x80]
	cmp r5, r0
	bne _02248282
	ldr r0, [r4, #0x58]
	add r0, r0, #1
	str r0, [r4, #0x58]
	b _02248282
_022481A6:
	add r0, r7, #0
	add r1, r4, #0
	bl MOD11_0224AE78
	cmp r0, #1
	bne _022481BC
	ldr r0, _02248294 ; =0x00000106
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _02248282
_022481BC:
	ldr r0, [r4, #0x58]
	add r0, r0, #1
	str r0, [r4, #0x58]
	b _02248282
_022481C4:
	ldr r0, [sp, #0x80]
	mov r5, #0
	cmp r0, #0
	ble _022481F6
	mov r6, #2
_022481CE:
	ldr r1, _02248298 ; =0x000021EC
	add r2, r4, r5
	ldrb r2, [r2, r1]
	mov r1, #0xc0
	add r0, r4, #0
	mul r1, r2
	add r2, r4, r1
	ldr r1, _0224829C ; =0x00002DB8
	ldrh r1, [r2, r1]
	mov r2, #1
	bl MOD11_0224C12C
	cmp r0, #0x39
	bne _022481EE
	ldr r0, _022482A0 ; =0x00002168
	str r6, [r4, r0]
_022481EE:
	ldr r0, [sp, #0x80]
	add r5, r5, #1
	cmp r5, r0
	blt _022481CE
_022481F6:
	ldr r0, [r4, #0x58]
	add r0, r0, #1
	str r0, [r4, #0x58]
	b _02248282
_022481FE:
	ldr r0, [sp, #0x80]
	mov r5, #0
	cmp r0, #0
	ble _0224822C
	ldr r6, _02248298 ; =0x000021EC
_02248208:
	add r2, r4, r5
	ldrb r2, [r2, r6]
	add r0, r7, #0
	add r1, r4, #0
	mov r3, #1
	bl MOD11_02248898
	cmp r0, #1
	bne _02248224
	mov r0, #0xdd
	str r0, [sp, #0xcc]
	mov r0, #1
	str r0, [sp, #0x84]
	b _0224822C
_02248224:
	ldr r0, [sp, #0x80]
	add r5, r5, #1
	cmp r5, r0
	blt _02248208
_0224822C:
	ldr r0, [sp, #0x80]
	cmp r5, r0
	bne _02248282
	ldr r0, [r4, #0x58]
	add r0, r0, #1
	str r0, [r4, #0x58]
	b _02248282
_0224823A:
	ldr r0, [sp, #0x80]
	mov r5, #0
	cmp r0, #0
	ble _0224826C
_02248242:
	ldr r0, _02248298 ; =0x000021EC
	add r1, r4, r5
	ldrb r6, [r1, r0]
	add r0, r7, #0
	add r1, r4, #0
	add r2, r6, #0
	add r3, sp, #0xcc
	bl MOD11_022493A0
	cmp r0, #1
	bne _02248264
	mov r0, #0x46
	lsl r0, r0, #2
	str r6, [r4, r0]
	mov r0, #1
	str r0, [sp, #0x84]
	b _0224826C
_02248264:
	ldr r0, [sp, #0x80]
	add r5, r5, #1
	cmp r5, r0
	blt _02248242
_0224826C:
	ldr r0, [sp, #0x80]
	cmp r5, r0
	bne _02248282
	ldr r0, [r4, #0x58]
	add r0, r0, #1
	str r0, [r4, #0x58]
	b _02248282
_0224827A:
	mov r0, #0
	str r0, [r4, #0x58]
	mov r0, #2
	str r0, [sp, #0x84]
_02248282:
	ldr r0, [sp, #0x84]
	cmp r0, #0
	bne _0224828C
	bl _022476F0
_0224828C:
	ldr r0, [sp, #0xcc]
	add sp, #0xd0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02248294: .word 0x00000106
_02248298: .word 0x000021EC
_0224829C: .word 0x00002DB8
_022482A0: .word 0x00002168

	thumb_func_start MOD11_022482A4
MOD11_022482A4: ; 0x022482A4
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	bl MOD11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _022482FA
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0
	bl MOD11_02230308
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #2
	bl MOD11_02230308
	str r0, [sp, #4]
	bl LCRandom
	mov r3, #1
	add r2, r0, #0
	and r2, r3
	lsl r0, r2, #2
	add r1, sp, #0
	ldr r0, [r1, r0]
	mov r4, #0xc0
	mul r4, r0
	add r5, r6, r4
	ldr r4, _02248304 ; =0x00002D8C
	ldr r4, [r5, r4]
	cmp r4, #0
	bne _022482FE
	add r0, r2, #0
	eor r0, r3
	lsl r0, r0, #2
	add sp, #8
	ldr r0, [r1, r0]
	pop {r4, r5, r6, pc}
_022482FA:
	mov r0, #1
	eor r0, r4
_022482FE:
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_02248304: .word 0x00002D8C

	thumb_func_start MOD11_02248308
MOD11_02248308: ; 0x02248308
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldr r1, [r5, #0x6c]
	add r7, r0, #0
	add r4, r2, #0
	mov r6, #0
	cmp r1, #0xff
	bne _0224831C
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
_0224831C:
	add r0, r5, #0
	bl MOD11_0224AD9C
	cmp r0, #1
	bne _0224832A
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
_0224832A:
	ldr r1, [r5, #0x6c]
	add r0, r5, #0
	bl MOD11_02246D1C
	cmp r0, #0x26
	bgt _0224835A
	blt _0224833A
	b _022485FC
_0224833A:
	cmp r0, #0x10
	bgt _02248346
	bge _02248408
	cmp r0, #9
	beq _02248372
	b _0224887A
_02248346:
	cmp r0, #0x1b
	bgt _02248358
	cmp r0, #0x18
	blt _02248358
	bne _02248352
	b _022484B0
_02248352:
	cmp r0, #0x1b
	bne _02248358
	b _02248546
_02248358:
	b _0224887A
_0224835A:
	cmp r0, #0x38
	bgt _0224836A
	blt _02248362
	b _02248752
_02248362:
	cmp r0, #0x31
	bne _02248368
	b _022486BE
_02248368:
	b _0224887A
_0224836A:
	cmp r0, #0x6a
	bne _02248370
	b _022487FA
_02248370:
	b _0224887A
_02248372:
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r5, r0
	ldr r0, _02248660 ; =0x00002D8C
	ldr r1, [r2, r0]
	cmp r1, #0
	beq _022483E6
	add r1, r0, #0
	add r1, #0x20
	ldr r1, [r2, r1]
	cmp r1, #0
	bne _022483E6
	ldr r2, _02248664 ; =0x0000216C
	ldr r1, _02248668 ; =0x801FDA49
	ldr r3, [r5, r2]
	tst r1, r3
	bne _022483E6
	add r1, r2, #0
	sub r1, #0x30
	ldr r3, [r5, r1]
	mov r1, #0x20
	tst r1, r3
	bne _022483E6
	sub r2, #0x2c
	ldr r2, [r5, r2]
	mov r1, #0x10
	tst r1, r2
	bne _022483E6
	ldr r2, [r5, #0x6c]
	mov r1, #0x1c
	mul r1, r2
	add r1, r5, r1
	lsr r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _022483C6
	mov r0, #0x2e
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _022483E6
_022483C6:
	ldr r0, _0224866C ; =0x00003044
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _02248670 ; =0x000003E9
	ldrb r1, [r1, r0]
	mov r0, #1
	tst r0, r1
	beq _022483E6
	bl LCRandom
	mov r1, #0xa
	bl _s32_div_f
	cmp r1, #3
	blt _022483E8
_022483E6:
	b _0224887A
_022483E8:
	add r0, r5, #0
	mov r1, #3
	add r0, #0x88
	str r1, [r0]
	add r0, r5, #0
	ldr r1, [r5, #0x64]
	add r0, #0x94
	str r1, [r0]
	mov r0, #0x46
	ldr r1, [r5, #0x6c]
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r0, #0x1f
	str r0, [r4]
	mov r6, #1
	b _0224887A
_02248408:
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl MOD11_02246D1C
	cmp r0, #0x60
	bne _02248418
	add r7, r6, #0
	b _02248432
_02248418:
	ldr r0, _02248674 ; =0x00002160
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _02248426
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	b _02248432
_02248426:
	ldr r0, _0224866C ; =0x00003044
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _02248678 ; =0x000003E2
	ldrb r7, [r1, r0]
_02248432:
	ldr r1, [r5, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r2, r5, r0
	ldr r0, _02248660 ; =0x00002D8C
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _02248516
	ldr r0, _02248664 ; =0x0000216C
	ldr r2, [r5, r0]
	ldr r0, _02248668 ; =0x801FDA49
	tst r0, r2
	bne _02248516
	ldr r0, _0224866C ; =0x00003044
	ldr r3, [r5, r0]
	cmp r3, #0xa5
	beq _02248516
	mov r0, #0x1c
	ldr r2, _02248660 ; =0x00002D8C
	mul r0, r1
	add r0, r5, r0
	lsr r2, r2, #4
	ldr r2, [r0, r2]
	cmp r2, #0
	bne _0224846E
	mov r2, #0x2e
	lsl r2, r2, #4
	ldr r0, [r0, r2]
	cmp r0, #0
	beq _02248516
_0224846E:
	mov r0, #0x85
	lsl r0, r0, #6
	ldr r2, [r5, r0]
	mov r0, #0x10
	tst r0, r2
	bne _02248516
	lsl r0, r3, #4
	add r2, r5, r0
	ldr r0, _0224867C ; =0x000003E1
	ldrb r0, [r2, r0]
	cmp r0, #0
	beq _02248516
	add r0, r5, #0
	mov r2, #0x1b
	mov r3, #0
	bl MOD11_02243420
	cmp r7, r0
	beq _02248516
	ldr r1, [r5, #0x6c]
	add r0, r5, #0
	mov r2, #0x1c
	mov r3, #0
	bl MOD11_02243420
	cmp r7, r0
	beq _02248516
	mov r0, #0xbc
	str r0, [r4]
	add r0, #0x74
	str r7, [r5, r0]
	mov r6, #1
	b _0224887A
_022484B0:
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r5, r0
	ldr r0, _02248660 ; =0x00002D8C
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _02248516
	add r0, r5, #0
	bl MOD11_02246D1C
	cmp r0, #0x62
	beq _02248516
	ldr r1, _02248664 ; =0x0000216C
	ldr r0, _02248668 ; =0x801FDA49
	ldr r2, [r5, r1]
	tst r0, r2
	bne _02248516
	add r0, r1, #0
	sub r0, #0x30
	ldr r2, [r5, r0]
	mov r0, #0x20
	tst r0, r2
	bne _02248516
	sub r1, #0x2c
	ldr r1, [r5, r1]
	mov r0, #0x10
	tst r0, r1
	bne _02248516
	ldr r1, [r5, #0x6c]
	mov r0, #0x1c
	mul r0, r1
	add r2, r5, r0
	mov r0, #0xb6
	lsl r0, r0, #2
	ldr r1, [r2, r0]
	cmp r1, #0
	bne _02248504
	add r0, #8
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _02248516
_02248504:
	ldr r0, _0224866C ; =0x00003044
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _02248670 ; =0x000003E9
	ldrb r1, [r1, r0]
	mov r0, #1
	tst r0, r1
	bne _02248518
_02248516:
	b _0224887A
_02248518:
	ldr r0, [r5, #0x64]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	ldr r0, _02248680 ; =0x00002D90
	add r2, r5, r2
	ldr r2, [r2, r0]
	sub r1, #0xc1
	add r0, r2, #0
	mul r0, r1
	mov r1, #8
	bl MOD11_022476C0
	ldr r1, _02248684 ; =0x0000215C
	mov r6, #1
	str r0, [r5, r1]
	mov r0, #0x46
	ldr r1, [r5, #0x64]
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r0, #0xbd
	str r0, [r4]
	b _0224887A
_02248546:
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r5, r0
	ldr r0, _02248660 ; =0x00002D8C
	ldr r1, [r2, r0]
	cmp r1, #0
	beq _02248650
	add r1, r0, #0
	add r1, #0x20
	ldr r1, [r2, r1]
	cmp r1, #0
	bne _02248650
	ldr r2, _02248664 ; =0x0000216C
	ldr r1, _02248668 ; =0x801FDA49
	ldr r3, [r5, r2]
	tst r1, r3
	bne _02248650
	add r1, r2, #0
	sub r1, #0x30
	ldr r3, [r5, r1]
	mov r1, #0x20
	tst r1, r3
	bne _02248650
	sub r2, #0x2c
	ldr r2, [r5, r2]
	mov r1, #0x10
	tst r1, r2
	bne _02248650
	ldr r2, [r5, #0x6c]
	mov r1, #0x1c
	mul r1, r2
	add r1, r5, r1
	lsr r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _0224859A
	mov r0, #0x2e
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02248650
_0224859A:
	ldr r0, _0224866C ; =0x00003044
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _02248670 ; =0x000003E9
	ldrb r1, [r1, r0]
	mov r0, #1
	tst r0, r1
	beq _02248650
	bl LCRandom
	mov r1, #0xa
	bl _s32_div_f
	cmp r1, #3
	bge _02248650
	bl LCRandom
	mov r1, #3
	bl _s32_div_f
	cmp r1, #0
	beq _022485D0
	cmp r1, #1
	beq _022485D6
	cmp r1, #2
	beq _022485DC
_022485D0:
	mov r0, #0x16
	str r0, [r4]
	b _022485E0
_022485D6:
	mov r0, #0x1f
	str r0, [r4]
	b _022485E0
_022485DC:
	mov r0, #0x12
	str r0, [r4]
_022485E0:
	add r0, r5, #0
	mov r1, #3
	add r0, #0x88
	str r1, [r0]
	add r0, r5, #0
	ldr r1, [r5, #0x64]
	add r0, #0x94
	str r1, [r0]
	mov r0, #0x46
	ldr r1, [r5, #0x6c]
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r6, #1
	b _0224887A
_022485FC:
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r5, r0
	ldr r0, _02248660 ; =0x00002D8C
	ldr r1, [r2, r0]
	cmp r1, #0
	beq _02248650
	add r1, r0, #0
	add r1, #0x20
	ldr r1, [r2, r1]
	cmp r1, #0
	bne _02248650
	ldr r2, _02248664 ; =0x0000216C
	ldr r1, _02248668 ; =0x801FDA49
	ldr r3, [r5, r2]
	tst r1, r3
	bne _02248650
	add r1, r2, #0
	sub r1, #0x30
	ldr r3, [r5, r1]
	mov r1, #0x20
	tst r1, r3
	bne _02248650
	sub r2, #0x2c
	ldr r2, [r5, r2]
	mov r1, #0x10
	tst r1, r2
	bne _02248650
	ldr r2, [r5, #0x6c]
	mov r1, #0x1c
	mul r1, r2
	add r1, r5, r1
	lsr r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _02248652
	mov r0, #0x2e
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _02248652
_02248650:
	b _0224887A
_02248652:
	ldr r0, _0224866C ; =0x00003044
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _02248670 ; =0x000003E9
	b _02248688
	nop
_02248660: .word 0x00002D8C
_02248664: .word 0x0000216C
_02248668: .word 0x801FDA49
_0224866C: .word 0x00003044
_02248670: .word 0x000003E9
_02248674: .word 0x00002160
_02248678: .word 0x000003E2
_0224867C: .word 0x000003E1
_02248680: .word 0x00002D90
_02248684: .word 0x0000215C
_02248688:
	ldrb r1, [r1, r0]
	mov r0, #1
	tst r0, r1
	beq _02248770
	bl LCRandom
	mov r1, #0xa
	bl _s32_div_f
	cmp r1, #3
	bge _02248770
	add r0, r5, #0
	mov r1, #3
	add r0, #0x88
	str r1, [r0]
	add r0, r5, #0
	ldr r1, [r5, #0x64]
	add r0, #0x94
	str r1, [r0]
	mov r0, #0x46
	ldr r1, [r5, #0x6c]
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r0, #0x16
	str r0, [r4]
	mov r6, #1
	b _0224887A
_022486BE:
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r5, r0
	ldr r0, _02248880 ; =0x00002D8C
	ldr r1, [r2, r0]
	cmp r1, #0
	beq _02248770
	add r1, r0, #0
	add r1, #0x20
	ldr r1, [r2, r1]
	cmp r1, #0
	bne _02248770
	ldr r2, _02248884 ; =0x0000216C
	ldr r1, _02248888 ; =0x801FDA49
	ldr r3, [r5, r2]
	tst r1, r3
	bne _02248770
	add r1, r2, #0
	sub r1, #0x30
	ldr r3, [r5, r1]
	mov r1, #0x20
	tst r1, r3
	bne _02248770
	sub r2, #0x2c
	ldr r2, [r5, r2]
	mov r1, #0x10
	tst r1, r2
	bne _02248770
	ldr r2, [r5, #0x6c]
	mov r1, #0x1c
	mul r1, r2
	add r1, r5, r1
	lsr r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _02248712
	mov r0, #0x2e
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02248770
_02248712:
	ldr r0, _0224888C ; =0x00003044
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _02248890 ; =0x000003E9
	ldrb r1, [r1, r0]
	mov r0, #1
	tst r0, r1
	beq _02248770
	bl LCRandom
	mov r1, #0xa
	bl _s32_div_f
	cmp r1, #3
	bge _02248770
	add r0, r5, #0
	mov r1, #3
	add r0, #0x88
	str r1, [r0]
	add r0, r5, #0
	ldr r1, [r5, #0x64]
	add r0, #0x94
	str r1, [r0]
	mov r0, #0x46
	ldr r1, [r5, #0x6c]
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r0, #0x19
	str r0, [r4]
	mov r6, #1
	b _0224887A
_02248752:
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r5, r0
	ldr r0, _02248880 ; =0x00002D8C
	ldr r1, [r2, r0]
	cmp r1, #0
	beq _02248770
	add r1, r0, #0
	add r1, #0x24
	ldr r2, [r2, r1]
	mov r1, #0xf
	lsl r1, r1, #0x10
	tst r1, r2
	beq _02248772
_02248770:
	b _0224887A
_02248772:
	ldr r2, _02248884 ; =0x0000216C
	ldr r1, _02248888 ; =0x801FDA49
	ldr r3, [r5, r2]
	tst r1, r3
	bne _0224887A
	add r1, r2, #0
	sub r1, #0x30
	ldr r3, [r5, r1]
	mov r1, #0x20
	tst r1, r3
	bne _0224887A
	sub r2, #0x2c
	ldr r2, [r5, r2]
	mov r1, #0x10
	tst r1, r2
	bne _0224887A
	ldr r2, [r5, #0x6c]
	mov r1, #0x1c
	mul r1, r2
	add r1, r5, r1
	lsr r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _022487AC
	mov r0, #0x2e
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0224887A
_022487AC:
	ldr r0, _0224888C ; =0x00003044
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _02248890 ; =0x000003E9
	ldrb r1, [r1, r0]
	mov r0, #1
	tst r0, r1
	beq _0224887A
	mov r0, #0xc0
	mul r0, r2
	add r1, r5, r0
	ldr r0, _02248880 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0224887A
	bl LCRandom
	mov r1, #0xa
	bl _s32_div_f
	cmp r1, #3
	bge _0224887A
	add r0, r5, #0
	mov r1, #3
	add r0, #0x88
	str r1, [r0]
	add r0, r5, #0
	ldr r1, [r5, #0x64]
	add r0, #0x94
	str r1, [r0]
	mov r0, #0x46
	ldr r1, [r5, #0x6c]
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r0, #0x6a
	str r0, [r4]
	mov r6, #1
	b _0224887A
_022487FA:
	ldr r1, [r5, #0x6c]
	ldr r0, [r5, #0x74]
	cmp r1, r0
	bne _0224887A
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl MOD11_02246D1C
	cmp r0, #0x62
	beq _0224887A
	mov r0, #6
	str r0, [sp]
	add r0, r7, #0
	add r1, r5, #0
	mov r2, #8
	add r3, r6, #0
	bl MOD11_02246870
	cmp r0, #0
	bne _0224887A
	mov r2, #0x85
	lsl r2, r2, #6
	ldr r1, [r5, r2]
	mov r0, #0x10
	tst r0, r1
	bne _0224887A
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _02248880 ; =0x00002D8C
	ldr r3, [r1, r0]
	cmp r3, #0
	beq _0224887A
	add r2, #0x2c
	ldr r3, [r5, r2]
	ldr r2, _02248888 ; =0x801FDA49
	tst r2, r3
	bne _0224887A
	ldr r2, _0224888C ; =0x00003044
	ldr r2, [r5, r2]
	lsl r2, r2, #4
	add r3, r5, r2
	ldr r2, _02248890 ; =0x000003E9
	ldrb r3, [r3, r2]
	mov r2, #1
	tst r3, r2
	beq _0224887A
	add r0, r0, #4
	ldr r1, [r1, r0]
	sub r0, r2, #2
	mul r0, r1
	mov r1, #4
	bl MOD11_022476C0
	ldr r1, _02248894 ; =0x0000215C
	mov r6, #1
	str r0, [r5, r1]
	mov r0, #0x46
	ldr r1, [r5, #0x64]
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r0, #0xc1
	str r0, [r4]
_0224887A:
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02248880: .word 0x00002D8C
_02248884: .word 0x0000216C
_02248888: .word 0x801FDA49
_0224888C: .word 0x00003044
_02248890: .word 0x000003E9
_02248894: .word 0x0000215C

	thumb_func_start MOD11_02248898
MOD11_02248898: ; 0x02248898
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r2, #0
	add r0, r4, #0
	add r1, r5, #0
	add r7, r3, #0
	mov r6, #0
	bl MOD11_02246D1C
	cmp r0, #0x28
	bgt _022488DE
	bge _02248978
	cmp r0, #7
	bgt _022488B8
	beq _02248926
	b _022489D0
_022488B8:
	add r1, r0, #0
	sub r1, #0xc
	cmp r1, #8
	bhi _022488E8
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022488CC: ; jump table
	.short _02248994 - _022488CC - 2 ; case 0
	.short _022489D0 - _022488CC - 2 ; case 1
	.short _022489D0 - _022488CC - 2 ; case 2
	.short _02248940 - _022488CC - 2 ; case 3
	.short _022489D0 - _022488CC - 2 ; case 4
	.short _022488F0 - _022488CC - 2 ; case 5
	.short _022489D0 - _022488CC - 2 ; case 6
	.short _022489D0 - _022488CC - 2 ; case 7
	.short _0224890A - _022488CC - 2 ; case 8
_022488DE:
	cmp r0, #0x48
	bgt _022488EA
	bge _02248940
	cmp r0, #0x29
	beq _0224895C
_022488E8:
	b _022489D0
_022488EA:
	cmp r0, #0x54
	beq _022489B2
	b _022489D0
_022488F0:
	mov r0, #0xc0
	add r1, r5, #0
	mul r1, r0
	add r2, r4, r1
	ldr r1, _02248A04 ; =0x00002DAC
	ldr r2, [r2, r1]
	ldr r1, _02248A08 ; =0x00000F88
	tst r1, r2
	beq _022489D0
	mov r6, #1
	add r0, #0x70
	str r6, [r4, r0]
	b _022489D0
_0224890A:
	mov r0, #0xc0
	add r1, r5, #0
	mul r1, r0
	add r2, r4, r1
	ldr r1, _02248A0C ; =0x00002DB0
	ldr r2, [r2, r1]
	mov r1, #7
	tst r1, r2
	beq _022489D0
	mov r1, #5
	add r0, #0x70
	str r1, [r4, r0]
	mov r6, #1
	b _022489D0
_02248926:
	mov r0, #0xc0
	mul r0, r5
	add r1, r4, r0
	ldr r0, _02248A04 ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #0x40
	tst r1, r0
	beq _022489D0
	mov r1, #3
	add r0, #0xf0
	str r1, [r4, r0]
	mov r6, #1
	b _022489D0
_02248940:
	mov r0, #0xc0
	add r1, r5, #0
	mul r1, r0
	add r2, r4, r1
	ldr r1, _02248A04 ; =0x00002DAC
	ldr r2, [r2, r1]
	mov r1, #7
	tst r1, r2
	beq _022489D0
	mov r1, #0
	add r0, #0x70
	str r1, [r4, r0]
	mov r6, #1
	b _022489D0
_0224895C:
	mov r0, #0xc0
	add r1, r5, #0
	mul r1, r0
	add r2, r4, r1
	ldr r1, _02248A04 ; =0x00002DAC
	ldr r2, [r2, r1]
	mov r1, #0x10
	tst r1, r2
	beq _022489D0
	mov r1, #2
	add r0, #0x70
	str r1, [r4, r0]
	mov r6, #1
	b _022489D0
_02248978:
	mov r0, #0xc0
	add r1, r5, #0
	mul r1, r0
	add r2, r4, r1
	ldr r1, _02248A04 ; =0x00002DAC
	ldr r2, [r2, r1]
	mov r1, #0x20
	tst r1, r2
	beq _022489D0
	mov r1, #4
	add r0, #0x70
	str r1, [r4, r0]
	mov r6, #1
	b _022489D0
_02248994:
	mov r0, #0xc0
	add r1, r5, #0
	mul r1, r0
	add r2, r4, r1
	ldr r1, _02248A0C ; =0x00002DB0
	ldr r2, [r2, r1]
	mov r1, #0xf
	lsl r1, r1, #0x10
	tst r1, r2
	beq _022489D0
	mov r1, #6
	add r0, #0x70
	str r1, [r4, r0]
	mov r6, #1
	b _022489D0
_022489B2:
	mov r0, #0xc0
	add r3, r5, #0
	mul r3, r0
	ldr r0, _02248A10 ; =0x00002DB8
	add r1, r4, r3
	ldrh r1, [r1, r0]
	cmp r1, #0
	beq _022489D0
	add r0, #0x14
	add r2, r4, r0
	mov r0, #1
	ldr r1, [r2, r3]
	lsl r0, r0, #0x16
	orr r0, r1
	str r0, [r2, r3]
_022489D0:
	cmp r6, #1
	bne _022489FE
	mov r0, #0x46
	lsl r0, r0, #2
	str r5, [r4, r0]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD11_02246D1C
	mov r1, #0x4b
	lsl r1, r1, #2
	str r0, [r4, r1]
	cmp r7, #0
	bne _022489FE
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xdd
	bl MOD11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
_022489FE:
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02248A04: .word 0x00002DAC
_02248A08: .word 0x00000F88
_02248A0C: .word 0x00002DB0
_02248A10: .word 0x00002DB8

	thumb_func_start MOD11_02248A14
MOD11_02248A14: ; 0x02248A14
	mov r0, #0
	cmp r1, #0x28
	bgt _02248A34
	bge _02248A6A
	cmp r1, #7
	bgt _02248A24
	beq _02248A4C
	bx lr
_02248A24:
	cmp r1, #0x11
	bgt _02248A72
	cmp r1, #0xf
	blt _02248A72
	beq _02248A56
	cmp r1, #0x11
	beq _02248A42
	bx lr
_02248A34:
	cmp r1, #0x29
	bgt _02248A3C
	beq _02248A60
	bx lr
_02248A3C:
	cmp r1, #0x48
	beq _02248A56
	bx lr
_02248A42:
	ldr r1, _02248A74 ; =0x00000F88
	tst r1, r2
	beq _02248A72
	mov r0, #1
	bx lr
_02248A4C:
	mov r1, #0x40
	tst r1, r2
	beq _02248A72
	mov r0, #1
	bx lr
_02248A56:
	mov r1, #7
	tst r1, r2
	beq _02248A72
	mov r0, #1
	bx lr
_02248A60:
	mov r1, #0x10
	tst r1, r2
	beq _02248A72
	mov r0, #1
	bx lr
_02248A6A:
	mov r1, #0x20
	tst r1, r2
	beq _02248A72
	mov r0, #1
_02248A72:
	bx lr
	.align 2, 0
_02248A74: .word 0x00000F88

	thumb_func_start MOD11_02248A78
MOD11_02248A78: ; 0x02248A78
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	ldr r1, [r4, #0x6c]
	str r0, [sp]
	mov r7, #0
	add r0, r4, #0
	add r6, r2, #0
	add r5, r7, #0
	bl MOD11_02246D1C
	cmp r0, #0x1c
	bne _02248ABA
	ldr r0, [r4, #0x6c]
	cmp r0, #0xff
	beq _02248ABA
	add r1, r4, #0
	add r1, #0x94
	ldr r1, [r1]
	cmp r0, r1
	bne _02248ABA
	ldr r1, _02248BFC ; =0x0000213C
	ldr r2, [r4, r1]
	mov r1, #0x80
	tst r2, r1
	beq _02248ABA
	add r1, #0x98
	str r0, [r4, r1]
	add r0, r4, #0
	ldr r1, [r4, #0x64]
	add r0, #0x94
	str r1, [r0]
	mov r7, #1
	b _02248AEA
_02248ABA:
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x1c
	bne _02248AEA
	add r1, r4, #0
	add r1, #0x94
	ldr r0, [r4, #0x64]
	ldr r1, [r1]
	cmp r0, r1
	bne _02248AEA
	ldr r1, _02248BFC ; =0x0000213C
	ldr r2, [r4, r1]
	mov r1, #0x80
	tst r2, r1
	beq _02248AEA
	add r1, #0x98
	str r0, [r4, r1]
	add r0, r4, #0
	ldr r1, [r4, #0x6c]
	add r0, #0x94
	str r1, [r0]
	mov r7, #1
_02248AEA:
	cmp r7, #1
	bne _02248B3A
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _02248C00 ; =0x00002DAC
	ldr r0, [r1, r0]
	ldr r1, _02248C04 ; =0x00000F88
	tst r1, r0
	beq _02248B08
	mov r5, #0x16
	b _02248B1A
_02248B08:
	mov r1, #0x10
	tst r1, r0
	beq _02248B12
	mov r5, #0x19
	b _02248B1A
_02248B12:
	mov r1, #0x40
	tst r0, r1
	beq _02248B1A
	mov r5, #0x1f
_02248B1A:
	cmp r5, #0
	beq _02248B3A
	add r0, r4, #0
	mov r1, #3
	add r0, #0x88
	str r1, [r0]
	add r0, r4, #0
	mov r1, #1
	add r2, r5, #0
	bl MOD11_022431DC
	str r6, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
_02248B3A:
	ldr r0, [sp]
	add r1, r4, #0
	bl MOD11_0224AE78
	add r5, r0, #0
	cmp r5, #1
	bne _02248B5C
	ldr r2, _02248C08 ; =0x00000106
	add r0, r4, #0
	mov r1, #1
	bl MOD11_022431DC
	str r6, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
_02248B5C:
	ldr r1, [r4, #0x6c]
	add r0, r4, #0
	bl MOD11_02249D90
	cmp r0, #0x6b
	bne _02248B9C
	ldr r0, [r4, #0x6c]
	cmp r0, #0xff
	beq _02248B9C
	add r1, r4, #0
	add r1, #0x94
	ldr r1, [r1]
	cmp r0, r1
	bne _02248B9C
	mov r1, #0x1c
	add r2, r0, #0
	mul r2, r1
	add r3, r4, r2
	mov r2, #0xba
	lsl r2, r2, #2
	ldr r3, [r3, r2]
	mov r2, #4
	tst r2, r3
	beq _02248B9C
	add r1, #0xfc
	str r0, [r4, r1]
	add r0, r4, #0
	ldr r1, [r4, #0x64]
	add r0, #0x94
	str r1, [r0]
	mov r5, #1
	b _02248BD6
_02248B9C:
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl MOD11_02249D90
	cmp r0, #0x6b
	bne _02248BD6
	add r1, r4, #0
	add r1, #0x94
	ldr r0, [r4, #0x64]
	ldr r1, [r1]
	cmp r0, r1
	bne _02248BD6
	mov r1, #0x1c
	add r2, r0, #0
	mul r2, r1
	add r3, r4, r2
	mov r2, #0xba
	lsl r2, r2, #2
	ldr r3, [r3, r2]
	mov r2, #4
	tst r2, r3
	beq _02248BD6
	add r1, #0xfc
	str r0, [r4, r1]
	add r0, r4, #0
	ldr r1, [r4, #0x6c]
	add r0, #0x94
	str r1, [r0]
	mov r5, #1
_02248BD6:
	cmp r5, #1
	bne _02248BF6
	add r0, r4, #0
	mov r1, #5
	add r0, #0x88
	str r1, [r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x6a
	bl MOD11_022431DC
	str r6, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
_02248BF6:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02248BFC: .word 0x0000213C
_02248C00: .word 0x00002DAC
_02248C04: .word 0x00000F88
_02248C08: .word 0x00000106

	thumb_func_start MOD11_02248C0C
MOD11_02248C0C: ; 0x02248C0C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r0, [sp]
	add r4, r1, #0
	mov r0, #0
	str r0, [sp, #0xc]
	str r2, [sp, #4]
	add r0, r4, #0
	add r1, r2, #0
	bl MOD11_02249D90
	str r0, [sp, #0x10]
	ldr r1, [sp, #4]
	add r0, r4, #0
	mov r2, #0
	bl MOD11_02249DA4
	add r6, r0, #0
	ldr r0, [sp, #4]
	mov r3, #0xc0
	add r5, r0, #0
	ldr r0, _02248F50 ; =0x00002D8C
	mul r5, r3
	add r1, r4, r0
	ldr r2, [r1, r5]
	str r1, [sp, #0x14]
	cmp r2, #0
	bne _02248C46
	b _02249274
_02248C46:
	ldr r1, [sp, #0x10]
	cmp r1, #0x35
	bhi _02248CE8
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02248C58: ; jump table
	.short _02249246 - _02248C58 - 2 ; case 0
	.short _02248CC4 - _02248C58 - 2 ; case 1
	.short _02249246 - _02248C58 - 2 ; case 2
	.short _02249246 - _02248C58 - 2 ; case 3
	.short _02248D00 - _02248C58 - 2 ; case 4
	.short _02248D14 - _02248C58 - 2 ; case 5
	.short _02248D28 - _02248C58 - 2 ; case 6
	.short _02248D3C - _02248C58 - 2 ; case 7
	.short _02248D50 - _02248C58 - 2 ; case 8
	.short _02248D64 - _02248C58 - 2 ; case 9
	.short _02248DC6 - _02248C58 - 2 ; case 10
	.short _02248DDA - _02248C58 - 2 ; case 11
	.short _02248CDC - _02248C58 - 2 ; case 12
	.short _02248E3A - _02248C58 - 2 ; case 13
	.short _02248E76 - _02248C58 - 2 ; case 14
	.short _02248EB2 - _02248C58 - 2 ; case 15
	.short _02248EEE - _02248C58 - 2 ; case 16
	.short _02248F2C - _02248C58 - 2 ; case 17
	.short _02249246 - _02248C58 - 2 ; case 18
	.short _02249246 - _02248C58 - 2 ; case 19
	.short _02249246 - _02248C58 - 2 ; case 20
	.short _02249246 - _02248C58 - 2 ; case 21
	.short _02249246 - _02248C58 - 2 ; case 22
	.short _02249246 - _02248C58 - 2 ; case 23
	.short _02249246 - _02248C58 - 2 ; case 24
	.short _02249246 - _02248C58 - 2 ; case 25
	.short _02249246 - _02248C58 - 2 ; case 26
	.short _02249246 - _02248C58 - 2 ; case 27
	.short _02249246 - _02248C58 - 2 ; case 28
	.short _02249246 - _02248C58 - 2 ; case 29
	.short _02249246 - _02248C58 - 2 ; case 30
	.short _02249246 - _02248C58 - 2 ; case 31
	.short _02249246 - _02248C58 - 2 ; case 32
	.short _02249246 - _02248C58 - 2 ; case 33
	.short _02249246 - _02248C58 - 2 ; case 34
	.short _02248F86 - _02248C58 - 2 ; case 35
	.short _02248FCA - _02248C58 - 2 ; case 36
	.short _02249012 - _02248C58 - 2 ; case 37
	.short _02249058 - _02248C58 - 2 ; case 38
	.short _0224909E - _02248C58 - 2 ; case 39
	.short _022490E4 - _02248C58 - 2 ; case 40
	.short _02249128 - _02248C58 - 2 ; case 41
	.short _02249246 - _02248C58 - 2 ; case 42
	.short _022491D8 - _02248C58 - 2 ; case 43
	.short _0224920C - _02248C58 - 2 ; case 44
	.short _02249246 - _02248C58 - 2 ; case 45
	.short _02249246 - _02248C58 - 2 ; case 46
	.short _02249246 - _02248C58 - 2 ; case 47
	.short _02249194 - _02248C58 - 2 ; case 48
	.short _02249246 - _02248C58 - 2 ; case 49
	.short _02249246 - _02248C58 - 2 ; case 50
	.short _02249246 - _02248C58 - 2 ; case 51
	.short _02249246 - _02248C58 - 2 ; case 52
	.short _022491BC - _02248C58 - 2 ; case 53
_02248CC4:
	add r1, r4, r5
	add r0, r0, #4
	ldr r0, [r1, r0]
	lsr r0, r0, #1
	cmp r2, r0
	bhi _02248CE8
	ldr r0, _02248F54 ; =0x0000215C
	mov r7, #0xc6
	str r6, [r4, r0]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249246
_02248CDC:
	add r1, r4, r5
	add r0, r0, #4
	ldr r1, [r1, r0]
	lsr r0, r1, #1
	cmp r2, r0
	bls _02248CEA
_02248CE8:
	b _02249246
_02248CEA:
	add r0, r6, #0
	mul r0, r1
	mov r1, #0x64
	bl MOD11_022476C0
	ldr r1, _02248F54 ; =0x0000215C
	mov r7, #0xc6
	str r0, [r4, r1]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249246
_02248D00:
	add r1, r4, r5
	add r0, #0x20
	ldr r1, [r1, r0]
	mov r0, #0x40
	tst r0, r1
	beq _02248DF2
	mov r0, #1
	mov r7, #0xc7
	str r0, [sp, #0xc]
	b _02249246
_02248D14:
	add r1, r4, r5
	add r0, #0x20
	ldr r1, [r1, r0]
	mov r0, #7
	tst r0, r1
	beq _02248DF2
	mov r0, #1
	mov r7, #0xc8
	str r0, [sp, #0xc]
	b _02249246
_02248D28:
	add r1, r4, r5
	add r0, #0x20
	ldr r1, [r1, r0]
	ldr r0, _02248F58 ; =0x00000F88
	tst r0, r1
	beq _02248DF2
	mov r0, #1
	mov r7, #0xc9
	str r0, [sp, #0xc]
	b _02249246
_02248D3C:
	add r1, r4, r5
	add r0, #0x20
	ldr r1, [r1, r0]
	mov r0, #0x10
	tst r0, r1
	beq _02248DF2
	mov r0, #1
	mov r7, #0xca
	str r0, [sp, #0xc]
	b _02249246
_02248D50:
	add r1, r4, r5
	add r0, #0x20
	ldr r1, [r1, r0]
	mov r0, #0x20
	tst r0, r1
	beq _02248DF2
	mov r0, #1
	mov r7, #0xcb
	str r0, [sp, #0xc]
	b _02249246
_02248D64:
	mov r0, #0
	str r0, [sp, #8]
	add r0, r4, r5
	ldr r3, _02248F5C ; =0x00002D4C
	add r1, r0, #0
_02248D6E:
	ldrh r2, [r0, r3]
	cmp r2, #0
	beq _02248D7C
	ldr r2, _02248F60 ; =0x00002D6C
	ldrb r2, [r1, r2]
	cmp r2, #0
	beq _02248D8A
_02248D7C:
	ldr r2, [sp, #8]
	add r0, r0, #2
	add r2, r2, #1
	add r1, r1, #1
	str r2, [sp, #8]
	cmp r2, #4
	blt _02248D6E
_02248D8A:
	ldr r0, [sp, #8]
	cmp r0, #4
	beq _02248DF2
	mov r0, #0xb5
	lsl r0, r0, #6
	ldr r1, [sp, #8]
	add r0, r4, r0
	add r0, r0, r5
	add r1, #0x1f
	add r2, r6, #0
	bl MOD11_02243DC8
	ldr r0, [sp]
	ldr r2, [sp, #4]
	add r1, r4, #0
	bl MOD11_02245190
	ldr r0, [sp, #8]
	add r1, r4, r5
	lsl r0, r0, #1
	add r1, r1, r0
	ldr r0, _02248F5C ; =0x00002D4C
	mov r7, #0xcc
	ldrh r1, [r1, r0]
	mov r0, #0x49
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249246
_02248DC6:
	add r1, r4, r5
	add r0, #0x24
	ldr r1, [r1, r0]
	mov r0, #7
	tst r0, r1
	beq _02248DF2
	mov r0, #1
	mov r7, #0xcd
	str r0, [sp, #0xc]
	b _02249246
_02248DDA:
	add r2, r0, #0
	add r1, r4, r5
	add r2, #0x20
	ldr r2, [r1, r2]
	lsl r3, r2, #0x18
	lsr r3, r3, #0x18
	bne _02248DF4
	add r0, #0x24
	ldr r1, [r1, r0]
	mov r0, #7
	tst r0, r1
	bne _02248DF4
_02248DF2:
	b _02249246
_02248DF4:
	mov r0, #0x40
	tst r0, r2
	beq _02248DFC
	mov r7, #0xc7
_02248DFC:
	mov r0, #7
	tst r0, r2
	beq _02248E04
	mov r7, #0xc8
_02248E04:
	ldr r0, _02248F58 ; =0x00000F88
	tst r0, r2
	beq _02248E0C
	mov r7, #0xc9
_02248E0C:
	mov r0, #0x10
	tst r0, r2
	beq _02248E14
	mov r7, #0xca
_02248E14:
	mov r0, #0x20
	tst r0, r2
	beq _02248E1C
	mov r7, #0xcb
_02248E1C:
	ldr r0, _02248F64 ; =0x00002DB0
	add r1, r4, r5
	ldr r1, [r1, r0]
	mov r0, #7
	and r0, r1
	beq _02248E2A
	mov r7, #0xcd
_02248E2A:
	cmp r3, #0
	beq _02248E34
	cmp r0, #0
	beq _02248E34
	mov r7, #0xce
_02248E34:
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249246
_02248E3A:
	add r1, r4, r5
	add r0, r0, #4
	ldr r0, [r1, r0]
	lsr r1, r0, #1
	cmp r2, r1
	bhi _02248EFA
	add r1, r6, #0
	bl MOD11_022476C0
	ldr r1, _02248F54 ; =0x0000215C
	add r2, r4, r5
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r0, _02248F68 ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _02248E6E
	mov r7, #0xcf
	b _02248E70
_02248E6E:
	mov r7, #0xc6
_02248E70:
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249246
_02248E76:
	add r1, r4, r5
	add r0, r0, #4
	ldr r0, [r1, r0]
	lsr r1, r0, #1
	cmp r2, r1
	bhi _02248EFA
	add r1, r6, #0
	bl MOD11_022476C0
	ldr r1, _02248F54 ; =0x0000215C
	add r2, r4, r5
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #1
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r0, _02248F68 ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _02248EAA
	mov r7, #0xcf
	b _02248EAC
_02248EAA:
	mov r7, #0xc6
_02248EAC:
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249246
_02248EB2:
	add r1, r4, r5
	add r0, r0, #4
	ldr r0, [r1, r0]
	lsr r1, r0, #1
	cmp r2, r1
	bhi _02248EFA
	add r1, r6, #0
	bl MOD11_022476C0
	ldr r1, _02248F54 ; =0x0000215C
	add r2, r4, r5
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #2
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r0, _02248F68 ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _02248EE6
	mov r7, #0xcf
	b _02248EE8
_02248EE6:
	mov r7, #0xc6
_02248EE8:
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249246
_02248EEE:
	add r1, r4, r5
	add r0, r0, #4
	ldr r0, [r1, r0]
	lsr r1, r0, #1
	cmp r2, r1
	bls _02248EFC
_02248EFA:
	b _02249246
_02248EFC:
	add r1, r6, #0
	bl MOD11_022476C0
	ldr r1, _02248F54 ; =0x0000215C
	add r2, r4, r5
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #3
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r0, _02248F68 ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _02248F24
	mov r7, #0xcf
	b _02248F26
_02248F24:
	mov r7, #0xc6
_02248F26:
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249246
_02248F2C:
	add r1, r4, r5
	add r0, r0, #4
	ldr r0, [r1, r0]
	lsr r1, r0, #1
	cmp r2, r1
	bhi _02249000
	add r1, r6, #0
	bl MOD11_022476C0
	ldr r1, _02248F54 ; =0x0000215C
	add r2, r4, r5
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #4
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r0, _02248F68 ; =0x00002DA8
	b _02248F6C
	.align 2, 0
_02248F50: .word 0x00002D8C
_02248F54: .word 0x0000215C
_02248F58: .word 0x00000F88
_02248F5C: .word 0x00002D4C
_02248F60: .word 0x00002D6C
_02248F64: .word 0x00002DB0
_02248F68: .word 0x00002DA8
_02248F6C:
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _02248F7E
	mov r7, #0xcf
	b _02248F80
_02248F7E:
	mov r7, #0xc6
_02248F80:
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249246
_02248F86:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _02248F98
	lsr r0, r6, #0x1f
	add r0, r6, r0
	asr r6, r0, #1
_02248F98:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _0224927C ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r6, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _02249000
	ldr r0, _02249280 ; =0x00002D59
	add r1, r4, r5
	ldrsb r0, [r1, r0]
	cmp r0, #0xc
	bge _02249000
	mov r1, #0x13
	mov r0, #1
	lsl r1, r1, #4
	str r0, [sp, #0xc]
	str r0, [r4, r1]
	mov r7, #0xd0
	b _02249246
_02248FCA:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _02248FDC
	lsr r0, r6, #0x1f
	add r0, r6, r0
	asr r6, r0, #1
_02248FDC:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _0224927C ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r6, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _02249000
	ldr r0, _02249284 ; =0x00002D5A
	add r1, r4, r5
	ldrsb r0, [r1, r0]
	cmp r0, #0xc
	blt _02249002
_02249000:
	b _02249246
_02249002:
	mov r0, #0x13
	mov r1, #2
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #1
	mov r7, #0xd0
	str r0, [sp, #0xc]
	b _02249246
_02249012:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _02249024
	lsr r0, r6, #0x1f
	add r0, r6, r0
	asr r6, r0, #1
_02249024:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _0224927C ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r6, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _0224911E
	ldr r0, _02249288 ; =0x00002D5B
	add r1, r4, r5
	ldrsb r0, [r1, r0]
	cmp r0, #0xc
	bge _0224911E
	mov r0, #0x13
	mov r1, #3
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #1
	mov r7, #0xd0
	str r0, [sp, #0xc]
	b _02249246
_02249058:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _0224906A
	lsr r0, r6, #0x1f
	add r0, r6, r0
	asr r6, r0, #1
_0224906A:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _0224927C ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r6, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _0224911E
	ldr r0, _0224928C ; =0x00002D5C
	add r1, r4, r5
	ldrsb r0, [r1, r0]
	cmp r0, #0xc
	bge _0224911E
	mov r0, #0x13
	mov r1, #4
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #1
	mov r7, #0xd0
	str r0, [sp, #0xc]
	b _02249246
_0224909E:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _022490B0
	lsr r0, r6, #0x1f
	add r0, r6, r0
	asr r6, r0, #1
_022490B0:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _0224927C ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r6, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _0224911E
	ldr r0, _02249290 ; =0x00002D5D
	add r1, r4, r5
	ldrsb r0, [r1, r0]
	cmp r0, #0xc
	bge _0224911E
	mov r0, #0x13
	mov r1, #5
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #1
	mov r7, #0xd0
	str r0, [sp, #0xc]
	b _02249246
_022490E4:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _022490F6
	lsr r0, r6, #0x1f
	add r0, r6, r0
	asr r6, r0, #1
_022490F6:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _0224927C ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r6, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _0224911E
	ldr r0, _02249294 ; =0x00002DB0
	add r1, r4, r5
	ldr r1, [r1, r0]
	mov r0, #1
	lsl r0, r0, #0x14
	tst r0, r1
	beq _02249120
_0224911E:
	b _02249246
_02249120:
	mov r0, #1
	mov r7, #0xd1
	str r0, [sp, #0xc]
	b _02249246
_02249128:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _0224913A
	lsr r0, r6, #0x1f
	add r0, r6, r0
	asr r6, r0, #1
_0224913A:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _0224927C ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r6, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _02249246
	ldr r0, _02249280 ; =0x00002D59
	mov r2, #0
	add r3, r4, r5
_0224915A:
	ldrsb r1, [r3, r0]
	cmp r1, #0xc
	blt _02249168
	add r2, r2, #1
	add r3, r3, #1
	cmp r2, #5
	blt _0224915A
_02249168:
	cmp r2, #5
	beq _02249246
	ldr r6, _02249280 ; =0x00002D59
	add r5, r4, r5
	mov r7, #5
_02249172:
	bl LCRandom
	add r1, r7, #0
	bl _s32_div_f
	add r0, r5, r1
	ldrsb r0, [r0, r6]
	cmp r0, #0xc
	beq _02249172
	mov r0, #0x13
	add r1, r1, #1
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #1
	mov r7, #0xd2
	str r0, [sp, #0xc]
	b _02249246
_02249194:
	ldr r6, _02249298 ; =0x00002D58
	add r1, r4, r5
	mov r0, #0
	mov r5, #6
	add r3, r6, #0
_0224919E:
	ldrsb r2, [r1, r3]
	cmp r2, #6
	bge _022491AA
	mov r2, #1
	strb r5, [r1, r6]
	str r2, [sp, #0xc]
_022491AA:
	add r0, r0, #1
	add r1, r1, #1
	cmp r0, #8
	blt _0224919E
	ldr r0, [sp, #0xc]
	cmp r0, #1
	bne _02249246
	mov r7, #0xd3
	b _02249246
_022491BC:
	add r1, r4, r5
	add r0, #0x24
	ldr r1, [r1, r0]
	mov r0, #0xf
	lsl r0, r0, #0x10
	tst r0, r1
	beq _02249246
	mov r0, #6
	add r3, #0x70
	str r0, [r4, r3]
	mov r0, #1
	mov r7, #0xd4
	str r0, [sp, #0xc]
	b _02249246
_022491D8:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _022491EA
	lsr r0, r6, #0x1f
	add r0, r6, r0
	asr r6, r0, #1
_022491EA:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _0224927C ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r6, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _02249246
	mov r0, #1
	ldr r7, _0224929C ; =0x00000109
	str r0, [sp, #0xc]
	b _02249246
_0224920C:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _0224921E
	lsr r0, r6, #0x1f
	add r0, r6, r0
	asr r6, r0, #1
_0224921E:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _0224927C ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r6, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _02249246
	ldr r0, _022492A0 ; =0x00002DCC
	add r2, r4, r0
	mov r0, #1
	ldr r1, [r2, r5]
	lsl r0, r0, #0x1c
	orr r0, r1
	str r0, [r2, r5]
_02249246:
	ldr r0, [sp, #0xc]
	cmp r0, #1
	bne _02249274
	mov r1, #0x46
	ldr r0, [sp, #4]
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02249B4C
	mov r1, #0x4a
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	mov r1, #1
	add r2, r7, #0
	bl MOD11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
_02249274:
	ldr r0, [sp, #0xc]
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224927C: .word 0x00002D90
_02249280: .word 0x00002D59
_02249284: .word 0x00002D5A
_02249288: .word 0x00002D5B
_0224928C: .word 0x00002D5C
_02249290: .word 0x00002D5D
_02249294: .word 0x00002DB0
_02249298: .word 0x00002D58
_0224929C: .word 0x00000109
_022492A0: .word 0x00002DCC

	thumb_func_start MOD11_022492A4
MOD11_022492A4: ; 0x022492A4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r6, r2, #0
	mov r7, #0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD11_02249D90
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r6, #0
	add r2, r7, #0
	bl MOD11_02249DA4
	mov r0, #0xc0
	add r4, r6, #0
	mul r4, r0
	ldr r0, _02249394 ; =0x00002D8C
	add r1, r5, r0
	str r1, [sp, #8]
	ldr r1, [r1, r4]
	cmp r1, #0
	beq _0224938E
	ldr r2, [sp, #4]
	cmp r2, #0x44
	beq _022492E2
	add r0, r2, #0
	cmp r0, #0x6c
	beq _022492FE
	b _02249364
_022492E2:
	add r2, r5, r4
	add r0, r0, #4
	ldr r0, [r2, r0]
	cmp r1, r0
	bhs _02249364
	mov r1, #0x10
	bl MOD11_022476C0
	ldr r1, _02249398 ; =0x0000215C
	mov r7, #1
	str r0, [r5, r1]
	mov r0, #0xd5
	str r0, [sp]
	b _02249364
_022492FE:
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0x1b
	add r3, r7, #0
	bl MOD11_02243420
	cmp r0, #3
	beq _0224931E
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0x1c
	add r3, r7, #0
	bl MOD11_02243420
	cmp r0, #3
	bne _0224933E
_0224931E:
	ldr r0, _0224939C ; =0x00002D90
	add r1, r5, r4
	ldr r0, [r1, r0]
	ldr r1, [sp, #8]
	ldr r1, [r1, r4]
	cmp r1, r0
	bhs _02249364
	mov r1, #0x10
	bl MOD11_022476C0
	ldr r1, _02249398 ; =0x0000215C
	mov r7, #1
	str r0, [r5, r1]
	mov r0, #0xd5
	str r0, [sp]
	b _02249364
_0224933E:
	add r0, r5, #0
	add r1, r6, #0
	bl MOD11_02246D1C
	cmp r0, #0x62
	beq _02249364
	ldr r0, _0224939C ; =0x00002D90
	add r1, r5, r4
	ldr r1, [r1, r0]
	sub r0, r7, #1
	mul r0, r1
	mov r1, #8
	bl MOD11_022476C0
	ldr r1, _02249398 ; =0x0000215C
	mov r7, #1
	str r0, [r5, r1]
	mov r0, #0xd7
	str r0, [sp]
_02249364:
	cmp r7, #1
	bne _0224938E
	mov r0, #0x46
	lsl r0, r0, #2
	str r6, [r5, r0]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD11_02249B4C
	mov r1, #0x4a
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r2, [sp]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022431DC
	ldr r0, [r5, #8]
	str r0, [r5, #0xc]
	mov r0, #0x15
	str r0, [r5, #8]
_0224938E:
	add r0, r7, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02249394: .word 0x00002D8C
_02249398: .word 0x0000215C
_0224939C: .word 0x00002D90

	thumb_func_start MOD11_022493A0
MOD11_022493A0: ; 0x022493A0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r0, [sp]
	add r4, r1, #0
	mov r0, #0
	str r0, [sp, #0xc]
	str r2, [sp, #4]
	add r0, r4, #0
	add r1, r2, #0
	add r6, r3, #0
	bl MOD11_02249D90
	str r0, [sp, #0x10]
	ldr r1, [sp, #4]
	add r0, r4, #0
	mov r2, #0
	bl MOD11_02249DA4
	add r7, r0, #0
	ldr r0, [sp, #4]
	mov r3, #0xc0
	add r5, r0, #0
	ldr r0, _022496E4 ; =0x00002D8C
	mul r5, r3
	add r1, r4, r0
	ldr r2, [r1, r5]
	str r1, [sp, #0x14]
	cmp r2, #0
	bne _022493DC
	b _02249A50
_022493DC:
	ldr r1, [sp, #0x10]
	cmp r1, #0x35
	bhi _02249480
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022493EE: ; jump table
	.short _02249A3C - _022493EE - 2 ; case 0
	.short _0224945A - _022493EE - 2 ; case 1
	.short _02249A3C - _022493EE - 2 ; case 2
	.short _02249A3C - _022493EE - 2 ; case 3
	.short _0224949A - _022493EE - 2 ; case 4
	.short _022494B0 - _022493EE - 2 ; case 5
	.short _022494C6 - _022493EE - 2 ; case 6
	.short _022494DC - _022493EE - 2 ; case 7
	.short _022494F2 - _022493EE - 2 ; case 8
	.short _02249508 - _022493EE - 2 ; case 9
	.short _0224956C - _022493EE - 2 ; case 10
	.short _02249582 - _022493EE - 2 ; case 11
	.short _02249474 - _022493EE - 2 ; case 12
	.short _022496BC - _022493EE - 2 ; case 13
	.short _0224972C - _022493EE - 2 ; case 14
	.short _0224976A - _022493EE - 2 ; case 15
	.short _022497A8 - _022493EE - 2 ; case 16
	.short _022497E6 - _022493EE - 2 ; case 17
	.short _02249A3C - _022493EE - 2 ; case 18
	.short _02249A3C - _022493EE - 2 ; case 19
	.short _02249A3C - _022493EE - 2 ; case 20
	.short _02249A3C - _022493EE - 2 ; case 21
	.short _02249A3C - _022493EE - 2 ; case 22
	.short _02249A3C - _022493EE - 2 ; case 23
	.short _02249A3C - _022493EE - 2 ; case 24
	.short _02249A3C - _022493EE - 2 ; case 25
	.short _02249A3C - _022493EE - 2 ; case 26
	.short _02249A3C - _022493EE - 2 ; case 27
	.short _02249A3C - _022493EE - 2 ; case 28
	.short _02249A3C - _022493EE - 2 ; case 29
	.short _02249A3C - _022493EE - 2 ; case 30
	.short _02249A3C - _022493EE - 2 ; case 31
	.short _02249A3C - _022493EE - 2 ; case 32
	.short _02249A3C - _022493EE - 2 ; case 33
	.short _02249A3C - _022493EE - 2 ; case 34
	.short _02249826 - _022493EE - 2 ; case 35
	.short _0224986C - _022493EE - 2 ; case 36
	.short _022498B4 - _022493EE - 2 ; case 37
	.short _022498FC - _022493EE - 2 ; case 38
	.short _02249946 - _022493EE - 2 ; case 39
	.short _0224998E - _022493EE - 2 ; case 40
	.short _022499D2 - _022493EE - 2 ; case 41
	.short _02249A3C - _022493EE - 2 ; case 42
	.short _0224964A - _022493EE - 2 ; case 43
	.short _02249680 - _022493EE - 2 ; case 44
	.short _02249A3C - _022493EE - 2 ; case 45
	.short _02249A3C - _022493EE - 2 ; case 46
	.short _02249A3C - _022493EE - 2 ; case 47
	.short _02249602 - _022493EE - 2 ; case 48
	.short _02249A3C - _022493EE - 2 ; case 49
	.short _02249A3C - _022493EE - 2 ; case 50
	.short _02249A3C - _022493EE - 2 ; case 51
	.short _02249A3C - _022493EE - 2 ; case 52
	.short _0224962C - _022493EE - 2 ; case 53
_0224945A:
	add r1, r4, r5
	add r0, r0, #4
	ldr r0, [r1, r0]
	lsr r0, r0, #1
	cmp r2, r0
	bhi _02249480
	ldr r0, _022496E8 ; =0x0000215C
	str r7, [r4, r0]
	mov r0, #0xc6
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_02249474:
	add r1, r4, r5
	add r0, r0, #4
	ldr r1, [r1, r0]
	lsr r0, r1, #1
	cmp r2, r0
	bls _02249482
_02249480:
	b _02249A3C
_02249482:
	add r0, r7, #0
	mul r0, r1
	mov r1, #0x64
	bl MOD11_022476C0
	ldr r1, _022496E8 ; =0x0000215C
	str r0, [r4, r1]
	mov r0, #0xc6
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_0224949A:
	add r1, r4, r5
	add r0, #0x20
	ldr r1, [r1, r0]
	mov r0, #0x40
	tst r0, r1
	beq _0224959C
	mov r0, #0xc7
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_022494B0:
	add r1, r4, r5
	add r0, #0x20
	ldr r1, [r1, r0]
	mov r0, #7
	tst r0, r1
	beq _0224959C
	mov r0, #0xc8
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_022494C6:
	add r1, r4, r5
	add r0, #0x20
	ldr r1, [r1, r0]
	ldr r0, _022496EC ; =0x00000F88
	tst r0, r1
	beq _0224959C
	mov r0, #0xc9
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_022494DC:
	add r1, r4, r5
	add r0, #0x20
	ldr r1, [r1, r0]
	mov r0, #0x10
	tst r0, r1
	beq _0224959C
	mov r0, #0xca
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_022494F2:
	add r1, r4, r5
	add r0, #0x20
	ldr r1, [r1, r0]
	mov r0, #0x20
	tst r0, r1
	beq _0224959C
	mov r0, #0xcb
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_02249508:
	mov r0, #0
	str r0, [sp, #8]
	add r0, r4, r5
	ldr r3, _022496F0 ; =0x00002D4C
	add r1, r0, #0
_02249512:
	ldrh r2, [r0, r3]
	cmp r2, #0
	beq _02249520
	ldr r2, _022496F4 ; =0x00002D6C
	ldrb r2, [r1, r2]
	cmp r2, #0
	beq _0224952E
_02249520:
	ldr r2, [sp, #8]
	add r0, r0, #2
	add r2, r2, #1
	add r1, r1, #1
	str r2, [sp, #8]
	cmp r2, #4
	blt _02249512
_0224952E:
	ldr r0, [sp, #8]
	cmp r0, #4
	beq _0224959C
	mov r0, #0xb5
	lsl r0, r0, #6
	ldr r1, [sp, #8]
	add r0, r4, r0
	add r0, r0, r5
	add r1, #0x1f
	add r2, r7, #0
	bl MOD11_02243DC8
	ldr r0, [sp]
	ldr r2, [sp, #4]
	add r1, r4, #0
	bl MOD11_02245190
	ldr r0, [sp, #8]
	add r1, r4, r5
	lsl r0, r0, #1
	add r1, r1, r0
	ldr r0, _022496F0 ; =0x00002D4C
	ldrh r1, [r1, r0]
	mov r0, #0x49
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #0xcc
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_0224956C:
	add r1, r4, r5
	add r0, #0x24
	ldr r1, [r1, r0]
	mov r0, #7
	tst r0, r1
	beq _0224959C
	mov r0, #0xcd
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_02249582:
	add r1, r0, #0
	add r1, #0x20
	add r1, r4, r1
	ldr r2, [r1, r5]
	lsl r3, r2, #0x18
	lsr r3, r3, #0x18
	bne _0224959E
	add r3, r4, r5
	add r0, #0x24
	ldr r3, [r3, r0]
	mov r0, #7
	tst r0, r3
	bne _0224959E
_0224959C:
	b _02249A3C
_0224959E:
	mov r0, #0x40
	tst r0, r2
	beq _022495A8
	mov r0, #0xc7
	str r0, [r6]
_022495A8:
	ldr r2, [r1, r5]
	mov r0, #7
	tst r0, r2
	beq _022495B4
	mov r0, #0xc8
	str r0, [r6]
_022495B4:
	ldr r2, [r1, r5]
	ldr r0, _022496EC ; =0x00000F88
	tst r0, r2
	beq _022495C0
	mov r0, #0xc9
	str r0, [r6]
_022495C0:
	ldr r2, [r1, r5]
	mov r0, #0x10
	tst r0, r2
	beq _022495CC
	mov r0, #0xca
	str r0, [r6]
_022495CC:
	ldr r2, [r1, r5]
	mov r0, #0x20
	tst r0, r2
	beq _022495D8
	mov r0, #0xcb
	str r0, [r6]
_022495D8:
	ldr r0, _022496F8 ; =0x00002DB0
	mov r2, #7
	add r0, r4, r0
	ldr r3, [r0, r5]
	tst r2, r3
	beq _022495E8
	mov r2, #0xcd
	str r2, [r6]
_022495E8:
	ldr r1, [r1, r5]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	beq _022495FC
	ldr r1, [r0, r5]
	mov r0, #7
	tst r0, r1
	beq _022495FC
	mov r0, #0xce
	str r0, [r6]
_022495FC:
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_02249602:
	ldr r7, _022496FC ; =0x00002D58
	add r1, r4, r5
	mov r0, #0
	mov r5, #6
	add r3, r7, #0
_0224960C:
	ldrsb r2, [r1, r3]
	cmp r2, #6
	bge _02249618
	mov r2, #1
	strb r5, [r1, r7]
	str r2, [sp, #0xc]
_02249618:
	add r0, r0, #1
	add r1, r1, #1
	cmp r0, #8
	blt _0224960C
	ldr r0, [sp, #0xc]
	cmp r0, #1
	bne _022496C8
	mov r0, #0xd3
	str r0, [r6]
	b _02249A3C
_0224962C:
	add r1, r4, r5
	add r0, #0x24
	ldr r1, [r1, r0]
	mov r0, #0xf
	lsl r0, r0, #0x10
	tst r0, r1
	beq _022496C8
	mov r0, #6
	add r3, #0x70
	str r0, [r4, r3]
	mov r0, #0xd4
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_0224964A:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _0224965C
	lsr r0, r7, #0x1f
	add r0, r7, r0
	asr r7, r0, #1
_0224965C:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _02249700 ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r7, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _022496C8
	ldr r0, _02249704 ; =0x00000109
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_02249680:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _02249692
	lsr r0, r7, #0x1f
	add r0, r7, r0
	asr r7, r0, #1
_02249692:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _02249700 ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r7, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _022496C8
	ldr r0, _02249708 ; =0x00002DCC
	add r2, r4, r0
	mov r0, #1
	ldr r1, [r2, r5]
	lsl r0, r0, #0x1c
	orr r0, r1
	str r0, [r2, r5]
	b _02249A3C
_022496BC:
	add r1, r4, r5
	add r0, r0, #4
	ldr r0, [r1, r0]
	lsr r1, r0, #1
	cmp r2, r1
	bls _022496CA
_022496C8:
	b _02249A3C
_022496CA:
	add r1, r7, #0
	bl MOD11_022476C0
	ldr r1, _022496E8 ; =0x0000215C
	add r2, r4, r5
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r0, _0224970C ; =0x00002DA8
	b _02249710
	nop
_022496E4: .word 0x00002D8C
_022496E8: .word 0x0000215C
_022496EC: .word 0x00000F88
_022496F0: .word 0x00002D4C
_022496F4: .word 0x00002D6C
_022496F8: .word 0x00002DB0
_022496FC: .word 0x00002D58
_02249700: .word 0x00002D90
_02249704: .word 0x00000109
_02249708: .word 0x00002DCC
_0224970C: .word 0x00002DA8
_02249710:
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _02249722
	mov r0, #0xcf
	b _02249724
_02249722:
	mov r0, #0xc6
_02249724:
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_0224972C:
	add r1, r4, r5
	add r0, r0, #4
	ldr r0, [r1, r0]
	lsr r1, r0, #1
	cmp r2, r1
	bhi _022497F2
	add r1, r7, #0
	bl MOD11_022476C0
	ldr r1, _02249A58 ; =0x0000215C
	add r2, r4, r5
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #1
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r0, _02249A5C ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _02249760
	mov r0, #0xcf
	b _02249762
_02249760:
	mov r0, #0xc6
_02249762:
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_0224976A:
	add r1, r4, r5
	add r0, r0, #4
	ldr r0, [r1, r0]
	lsr r1, r0, #1
	cmp r2, r1
	bhi _022497F2
	add r1, r7, #0
	bl MOD11_022476C0
	ldr r1, _02249A58 ; =0x0000215C
	add r2, r4, r5
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #2
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r0, _02249A5C ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _0224979E
	mov r0, #0xcf
	b _022497A0
_0224979E:
	mov r0, #0xc6
_022497A0:
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_022497A8:
	add r1, r4, r5
	add r0, r0, #4
	ldr r0, [r1, r0]
	lsr r1, r0, #1
	cmp r2, r1
	bhi _022497F2
	add r1, r7, #0
	bl MOD11_022476C0
	ldr r1, _02249A58 ; =0x0000215C
	add r2, r4, r5
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #3
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r0, _02249A5C ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _022497DC
	mov r0, #0xcf
	b _022497DE
_022497DC:
	mov r0, #0xc6
_022497DE:
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_022497E6:
	add r1, r4, r5
	add r0, r0, #4
	ldr r0, [r1, r0]
	lsr r1, r0, #1
	cmp r2, r1
	bls _022497F4
_022497F2:
	b _02249A3C
_022497F4:
	add r1, r7, #0
	bl MOD11_022476C0
	ldr r1, _02249A58 ; =0x0000215C
	add r2, r4, r5
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #4
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r0, _02249A5C ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _0224981C
	mov r0, #0xcf
	b _0224981E
_0224981C:
	mov r0, #0xc6
_0224981E:
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_02249826:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _02249838
	lsr r0, r7, #0x1f
	add r0, r7, r0
	asr r7, r0, #1
_02249838:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _02249A60 ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r7, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _02249932
	ldr r0, _02249A64 ; =0x00002D59
	add r1, r4, r5
	ldrsb r0, [r1, r0]
	cmp r0, #0xc
	bge _02249932
	mov r1, #0x13
	mov r0, #1
	lsl r1, r1, #4
	str r0, [sp, #0xc]
	str r0, [r4, r1]
	mov r0, #0xd0
	str r0, [r6]
	b _02249A3C
_0224986C:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _0224987E
	lsr r0, r7, #0x1f
	add r0, r7, r0
	asr r7, r0, #1
_0224987E:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _02249A60 ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r7, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _02249932
	ldr r0, _02249A68 ; =0x00002D5A
	add r1, r4, r5
	ldrsb r0, [r1, r0]
	cmp r0, #0xc
	bge _02249932
	mov r0, #0x13
	mov r1, #2
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #0xd0
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_022498B4:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _022498C6
	lsr r0, r7, #0x1f
	add r0, r7, r0
	asr r7, r0, #1
_022498C6:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _02249A60 ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r7, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _02249932
	ldr r0, _02249A6C ; =0x00002D5B
	add r1, r4, r5
	ldrsb r0, [r1, r0]
	cmp r0, #0xc
	bge _02249932
	mov r0, #0x13
	mov r1, #3
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #0xd0
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_022498FC:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _0224990E
	lsr r0, r7, #0x1f
	add r0, r7, r0
	asr r7, r0, #1
_0224990E:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _02249A60 ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r7, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _02249932
	ldr r0, _02249A70 ; =0x00002D5C
	add r1, r4, r5
	ldrsb r0, [r1, r0]
	cmp r0, #0xc
	blt _02249934
_02249932:
	b _02249A3C
_02249934:
	mov r0, #0x13
	mov r1, #4
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #0xd0
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_02249946:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _02249958
	lsr r0, r7, #0x1f
	add r0, r7, r0
	asr r7, r0, #1
_02249958:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _02249A60 ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r7, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _02249A3C
	ldr r0, _02249A74 ; =0x00002D5D
	add r1, r4, r5
	ldrsb r0, [r1, r0]
	cmp r0, #0xc
	bge _02249A3C
	mov r0, #0x13
	mov r1, #5
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #0xd0
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_0224998E:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _022499A0
	lsr r0, r7, #0x1f
	add r0, r7, r0
	asr r7, r0, #1
_022499A0:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _02249A60 ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r7, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _02249A3C
	ldr r0, _02249A78 ; =0x00002DB0
	add r1, r4, r5
	ldr r1, [r1, r0]
	mov r0, #1
	lsl r0, r0, #0x14
	tst r0, r1
	bne _02249A3C
	mov r0, #0xd1
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
	b _02249A3C
_022499D2:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x52
	bne _022499E4
	lsr r0, r7, #0x1f
	add r0, r7, r0
	asr r7, r0, #1
_022499E4:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _02249A60 ; =0x00002D90
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, r7, #0
	bl _u32_div_f
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r5]
	cmp r1, r0
	bhi _02249A3C
	ldr r0, _02249A64 ; =0x00002D59
	mov r2, #0
	add r3, r4, r5
_02249A04:
	ldrsb r1, [r3, r0]
	cmp r1, #0xc
	blt _02249A12
	add r2, r2, #1
	add r3, r3, #1
	cmp r2, #5
	blt _02249A04
_02249A12:
	cmp r2, #5
	beq _02249A3C
	ldr r7, _02249A64 ; =0x00002D59
	add r5, r4, r5
_02249A1A:
	bl LCRandom
	mov r1, #5
	bl _s32_div_f
	add r0, r5, r1
	ldrsb r0, [r0, r7]
	cmp r0, #0xc
	beq _02249A1A
	mov r0, #0x13
	add r1, r1, #1
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #0xd2
	str r0, [r6]
	mov r0, #1
	str r0, [sp, #0xc]
_02249A3C:
	ldr r0, [sp, #0xc]
	cmp r0, #1
	bne _02249A50
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02249B4C
	mov r1, #0x4a
	lsl r1, r1, #2
	str r0, [r4, r1]
_02249A50:
	ldr r0, [sp, #0xc]
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02249A58: .word 0x0000215C
_02249A5C: .word 0x00002DA8
_02249A60: .word 0x00002D90
_02249A64: .word 0x00002D59
_02249A68: .word 0x00002D5A
_02249A6C: .word 0x00002D5B
_02249A70: .word 0x00002D5C
_02249A74: .word 0x00002D5D
_02249A78: .word 0x00002DB0

	thumb_func_start MOD11_02249A7C
MOD11_02249A7C: ; 0x02249A7C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r4, r2, #0
	mov r6, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_02249D90
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD11_02249DA4
	str r0, [sp, #8]
	mov r0, #0xc0
	mul r0, r4
	str r0, [sp]
	add r1, r5, r0
	ldr r0, _02249B40 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02249B38
	cmp r7, #0x63
	beq _02249ABA
	cmp r7, #0x64
	beq _02249AD0
	cmp r7, #0x73
	beq _02249AE6
	b _02249B0E
_02249ABA:
	add r0, r5, #0
	add r0, #0x94
	str r4, [r0]
	add r0, r5, #0
	mov r1, #5
	add r0, #0x88
	str r1, [r0]
	mov r0, #0x2f
	str r0, [sp, #4]
	mov r6, #1
	b _02249B0E
_02249AD0:
	add r0, r5, #0
	add r0, #0x94
	str r4, [r0]
	add r0, r5, #0
	mov r1, #5
	add r0, #0x88
	str r1, [r0]
	mov r0, #0x19
	str r0, [sp, #4]
	mov r6, #1
	b _02249B0E
_02249AE6:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x62
	beq _02249B0E
	ldr r0, [sp]
	add r1, r5, r0
	ldr r0, _02249B44 ; =0x00002D90
	ldr r1, [r1, r0]
	sub r0, r6, #1
	mul r0, r1
	ldr r1, [sp, #8]
	bl MOD11_022476C0
	ldr r1, _02249B48 ; =0x0000215C
	mov r6, #1
	str r0, [r5, r1]
	mov r0, #0xd7
	str r0, [sp, #4]
_02249B0E:
	cmp r6, #1
	bne _02249B38
	mov r0, #0x46
	lsl r0, r0, #2
	str r4, [r5, r0]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_02249B4C
	mov r1, #0x4a
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r2, [sp, #4]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022431DC
	ldr r0, [r5, #8]
	str r0, [r5, #0xc]
	mov r0, #0x15
	str r0, [r5, #8]
_02249B38:
	add r0, r6, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02249B40: .word 0x00002D8C
_02249B44: .word 0x00002D90
_02249B48: .word 0x0000215C

	thumb_func_start MOD11_02249B4C
MOD11_02249B4C: ; 0x02249B4C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD11_02246D1C
	cmp r0, #0x67
	bne _02249B5E
	mov r0, #0
	pop {r3, r4, r5, pc}
_02249B5E:
	mov r0, #0xc0
	mul r0, r4
	add r2, r5, r0
	ldr r0, _02249B78 ; =0x00002DCC
	ldr r1, [r2, r0]
	lsl r1, r1, #0xa
	lsr r1, r1, #0x1d
	beq _02249B72
	mov r0, #0
	pop {r3, r4, r5, pc}
_02249B72:
	sub r0, #0x14
	ldrh r0, [r2, r0]
	pop {r3, r4, r5, pc}
	.align 2, 0
_02249B78: .word 0x00002DCC

	thumb_func_start MOD11_02249B7C
MOD11_02249B7C: ; 0x02249B7C
	lsl r1, r1, #4
	add r1, r0, r1
	ldr r0, _02249B90 ; =0x000021A8
	ldr r0, [r1, r0]
	cmp r0, #0x27
	bne _02249B8C
	mov r0, #1
	bx lr
_02249B8C:
	mov r0, #0
	bx lr
	.align 2, 0
_02249B90: .word 0x000021A8

	thumb_func_start MOD11_02249B94
MOD11_02249B94: ; 0x02249B94
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r1, [r5, #0x6c]
	str r0, [sp]
	add r6, r2, #0
	mov r7, #0
	cmp r1, #0xff
	bne _02249BAC
	add sp, #0xc
	add r0, r7, #0
	pop {r4, r5, r6, r7, pc}
_02249BAC:
	add r0, r5, #0
	bl MOD11_0224AD9C
	cmp r0, #1
	bne _02249BBC
	add sp, #0xc
	add r0, r7, #0
	pop {r4, r5, r6, r7, pc}
_02249BBC:
	ldr r1, [r5, #0x6c]
	add r0, r5, #0
	bl MOD11_02249D90
	add r4, r0, #0
	ldr r1, [r5, #0x6c]
	add r0, r5, #0
	add r2, r7, #0
	bl MOD11_02249DA4
	str r0, [sp, #4]
	ldr r0, [sp]
	ldr r1, [r5, #0x64]
	bl MOD11_02230270
	str r0, [sp, #8]
	cmp r4, #0x2e
	bgt _02249BF2
	cmp r4, #0x2a
	blt _02249BF0
	bne _02249BE8
	b _02249D24
_02249BE8:
	cmp r4, #0x2d
	beq _02249C74
	cmp r4, #0x2e
	beq _02249CD2
_02249BF0:
	b _02249D6A
_02249BF2:
	cmp r4, #0x73
	bne _02249C5C
	ldr r0, [r5, #0x64]
	mov r1, #0xc0
	mul r1, r0
	add r3, r5, r1
	ldr r1, _02249D70 ; =0x00002D8C
	ldr r2, [r3, r1]
	cmp r2, #0
	beq _02249C5C
	add r1, #0x2c
	ldrh r1, [r3, r1]
	cmp r1, #0
	bne _02249C5C
	add r1, r5, r0
	ldr r0, _02249D74 ; =0x0000219C
	ldrb r0, [r1, r0]
	bl MaskOfFlagNo
	ldr r1, [sp, #8]
	lsl r1, r1, #3
	add r2, r5, r1
	mov r1, #0x71
	lsl r1, r1, #2
	ldr r2, [r2, r1]
	lsl r2, r2, #3
	lsr r2, r2, #0x1a
	tst r0, r2
	bne _02249C5C
	ldr r0, _02249D78 ; =0x00003044
	sub r1, #0xaa
	ldr r0, [r5, r0]
	cmp r0, r1
	beq _02249C5C
	ldr r2, [r5, #0x6c]
	mov r1, #0x1c
	mul r1, r2
	add r3, r5, r1
	mov r1, #0xb6
	lsl r1, r1, #2
	ldr r2, [r3, r1]
	cmp r2, #0
	bne _02249C50
	add r1, #8
	ldr r1, [r3, r1]
	cmp r1, #0
	beq _02249C5C
_02249C50:
	mov r1, #0x85
	lsl r1, r1, #6
	ldr r2, [r5, r1]
	mov r1, #0x10
	tst r1, r2
	beq _02249C5E
_02249C5C:
	b _02249D6A
_02249C5E:
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _02249D7C ; =0x000003E9
	ldrb r1, [r1, r0]
	mov r0, #1
	tst r1, r0
	beq _02249D6A
	mov r1, #0xd8
	str r1, [r6]
	add r7, r0, #0
	b _02249D6A
_02249C74:
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r5, r0
	ldr r0, _02249D70 ; =0x00002D8C
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _02249D6A
	add r0, r5, #0
	bl MOD11_02246D1C
	cmp r0, #0x62
	beq _02249D6A
	mov r0, #0x85
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #0x10
	tst r0, r1
	bne _02249D6A
	ldr r1, [r5, #0x6c]
	mov r0, #0x1c
	mul r0, r1
	add r1, r5, r0
	mov r0, #0xb6
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02249D6A
	ldr r0, [r5, #0x64]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	ldr r0, _02249D80 ; =0x00002D90
	add r2, r5, r2
	ldr r2, [r2, r0]
	sub r1, #0xc1
	add r0, r2, #0
	mul r0, r1
	ldr r1, [sp, #4]
	bl MOD11_022476C0
	ldr r1, _02249D84 ; =0x0000215C
	mov r7, #1
	str r0, [r5, r1]
	lsr r0, r1, #5
	str r0, [r6]
	b _02249D6A
_02249CD2:
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r5, r0
	ldr r0, _02249D70 ; =0x00002D8C
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _02249D6A
	add r0, r5, #0
	bl MOD11_02246D1C
	cmp r0, #0x62
	beq _02249D6A
	ldr r1, [r5, #0x6c]
	mov r0, #0x1c
	mul r0, r1
	add r1, r5, r0
	mov r0, #0x2e
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02249D6A
	ldr r0, [r5, #0x64]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	ldr r0, _02249D80 ; =0x00002D90
	add r2, r5, r2
	ldr r2, [r2, r0]
	sub r1, #0xc1
	add r0, r2, #0
	mul r0, r1
	ldr r1, [sp, #4]
	bl MOD11_022476C0
	ldr r1, _02249D84 ; =0x0000215C
	mov r7, #1
	str r0, [r5, r1]
	lsr r0, r1, #5
	str r0, [r6]
	b _02249D6A
_02249D24:
	ldr r1, [r5, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	ldr r2, _02249D70 ; =0x00002D8C
	add r0, r5, r0
	ldr r1, [r0, r2]
	cmp r1, #0
	beq _02249D6A
	ldr r1, _02249D88 ; =0x0000216C
	ldr r3, [r5, r1]
	mov r1, #2
	tst r1, r3
	beq _02249D6A
	add r1, r2, #4
	ldr r0, [r0, r1]
	ldr r1, [sp, #4]
	bl MOD11_022476C0
	ldr r1, _02249D84 ; =0x0000215C
	mov r7, #1
	str r0, [r5, r1]
	mov r1, #0xc6
	str r1, [r6]
	ldr r0, [r5, #0x6c]
	add r1, #0x52
	str r0, [r5, r1]
	ldr r0, [r5, #0x6c]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	ldr r0, _02249D8C ; =0x00002DB8
	add r2, r5, r2
	ldrh r0, [r2, r0]
	add r1, #0x68
	str r0, [r5, r1]
_02249D6A:
	add r0, r7, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02249D70: .word 0x00002D8C
_02249D74: .word 0x0000219C
_02249D78: .word 0x00003044
_02249D7C: .word 0x000003E9
_02249D80: .word 0x00002D90
_02249D84: .word 0x0000215C
_02249D88: .word 0x0000216C
_02249D8C: .word 0x00002DB8

	thumb_func_start MOD11_02249D90
MOD11_02249D90: ; 0x02249D90
	push {r4, lr}
	add r4, r0, #0
	bl MOD11_02249B4C
	add r1, r0, #0
	add r0, r4, #0
	mov r2, #1
	bl MOD11_0224C12C
	pop {r4, pc}

	thumb_func_start MOD11_02249DA4
MOD11_02249DA4: ; 0x02249DA4
	push {r4, lr}
	add r4, r0, #0
	cmp r2, #0
	beq _02249DB6
	cmp r2, #1
	beq _02249DD2
	cmp r2, #2
	beq _02249DBE
	b _02249DDC
_02249DB6:
	bl MOD11_02249B4C
	add r1, r0, #0
	b _02249DDC
_02249DBE:
	mov r0, #0xc0
	mul r0, r1
	add r2, r4, r0
	ldr r0, _02249DE8 ; =0x00002DCC
	ldr r0, [r2, r0]
	lsl r0, r0, #0xa
	lsr r0, r0, #0x1d
	beq _02249DD2
	mov r0, #0
	pop {r4, pc}
_02249DD2:
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _02249DEC ; =0x00002DB8
	ldrh r1, [r1, r0]
_02249DDC:
	add r0, r4, #0
	mov r2, #2
	bl MOD11_0224C12C
	pop {r4, pc}
	nop
_02249DE8: .word 0x00002DCC
_02249DEC: .word 0x00002DB8

	thumb_func_start MOD11_02249DF0
MOD11_02249DF0: ; 0x02249DF0
	push {r4, lr}
	add r4, r0, #0
	bl MOD11_02249B4C
	add r1, r0, #0
	add r0, r4, #0
	mov r2, #0xb
	bl MOD11_0224C12C
	pop {r4, pc}

	thumb_func_start MOD11_02249E04
MOD11_02249E04: ; 0x02249E04
	push {r4, lr}
	add r4, r0, #0
	bl MOD11_02249B4C
	add r1, r0, #0
	add r0, r4, #0
	mov r2, #0xc
	bl MOD11_0224C12C
	pop {r4, pc}

	thumb_func_start MOD11_02249E18
MOD11_02249E18: ; 0x02249E18
	mov r2, #0xc0
	mul r2, r1
	ldr r1, _02249E28 ; =0x00002DB8
	add r2, r0, r2
	ldrh r1, [r2, r1]
	ldr r3, _02249E2C ; =MOD11_0224C12C
	mov r2, #8
	bx r3
	.align 2, 0
_02249E28: .word 0x00002DB8
_02249E2C: .word MOD11_0224C12C

	thumb_func_start MOD11_02249E30
MOD11_02249E30: ; 0x02249E30
	push {r3, lr}
	mov r2, #0xc0
	mul r2, r1
	ldr r1, _02249E54 ; =0x00002DCC
	add r3, r0, r2
	ldr r2, [r3, r1]
	lsl r2, r2, #0xa
	lsr r2, r2, #0x1d
	beq _02249E46
	mov r0, #0
	pop {r3, pc}
_02249E46:
	sub r1, #0x14
	ldrh r1, [r3, r1]
	mov r2, #9
	bl MOD11_0224C12C
	pop {r3, pc}
	nop
_02249E54: .word 0x00002DCC

	thumb_func_start MOD11_02249E58
MOD11_02249E58: ; 0x02249E58
	push {r3, lr}
	mov r2, #0xc0
	mul r2, r1
	ldr r1, _02249E7C ; =0x00002DCC
	add r3, r0, r2
	ldr r2, [r3, r1]
	lsl r2, r2, #0xa
	lsr r2, r2, #0x1d
	beq _02249E6E
	mov r0, #0
	pop {r3, pc}
_02249E6E:
	sub r1, #0x14
	ldrh r1, [r3, r1]
	mov r2, #0xa
	bl MOD11_0224C12C
	pop {r3, pc}
	nop
_02249E7C: .word 0x00002DCC

	thumb_func_start MOD11_02249E80
MOD11_02249E80: ; 0x02249E80
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	add r4, r2, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	mov r6, #0
	bl MOD11_02249D90
	cmp r0, #0x7a
	bne _02249E9E
	add sp, #8
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
_02249E9E:
	mov r0, #0xc0
	add r7, r4, #0
	mul r7, r0
	ldr r0, _02249F80 ; =0x00002DB0
	add r2, r5, r7
	ldr r1, [r2, r0]
	ldr r3, _02249F84 ; =0x0400E000
	tst r1, r3
	bne _02249EBA
	add r0, #0x10
	ldr r1, [r2, r0]
	lsr r0, r3, #0x10
	tst r0, r1
	beq _02249EBC
_02249EBA:
	mov r6, #1
_02249EBC:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x17
	beq _02249EDC
	mov r0, #0x17
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #3
	add r3, r4, #0
	bl MOD11_02246870
	cmp r0, #0
	bne _02249F10
_02249EDC:
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x1b
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #8
	beq _02249EFC
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x1c
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #8
	bne _02249F12
_02249EFC:
	mov r0, #0x2a
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #3
	add r3, r4, #0
	bl MOD11_02246870
	cmp r0, #0
	beq _02249F12
_02249F10:
	mov r6, #1
_02249F12:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x1a
	beq _02249F4A
	ldr r0, _02249F88 ; =0x00002DCC
	add r1, r5, r7
	ldr r0, [r1, r0]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x1d
	bne _02249F4A
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x1b
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #2
	beq _02249F4A
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x1c
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #2
	bne _02249F64
_02249F4A:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_02249D90
	cmp r0, #0x69
	beq _02249F64
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #7
	lsl r0, r0, #0xc
	tst r0, r1
	beq _02249F7A
_02249F64:
	mov r0, #0x47
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #3
	add r3, r4, #0
	bl MOD11_02246870
	cmp r0, #0
	beq _02249F7A
	mov r6, #1
_02249F7A:
	add r0, r6, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02249F80: .word 0x00002DB0
_02249F84: .word 0x0400E000
_02249F88: .word 0x00002DCC

	thumb_func_start MOD11_02249F8C
MOD11_02249F8C: ; 0x02249F8C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r1, #0
	str r0, [sp]
	mov r6, #0
	str r2, [sp, #4]
	add r0, r4, #0
	add r1, r2, #0
	add r5, r6, #0
	bl MOD11_02249E18
	add r7, r0, #0
	ldr r1, [sp, #4]
	add r0, r4, #0
	mov r2, #1
	bl MOD11_02249DA4
	str r0, [sp, #0x10]
	ldr r1, [r4, #0x6c]
	add r0, r4, #0
	bl MOD11_0224AD9C
	cmp r0, #1
	bne _02249FC2
	add sp, #0x14
	add r0, r6, #0
	pop {r4, r5, r6, r7, pc}
_02249FC2:
	cmp r7, #0x17
	bls _02249FC8
	b _0224A444
_02249FC8:
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02249FD4: ; jump table
	.short _0224A444 - _02249FD4 - 2 ; case 0
	.short _0224A04E - _02249FD4 - 2 ; case 1
	.short _0224A066 - _02249FD4 - 2 ; case 2
	.short _0224A07E - _02249FD4 - 2 ; case 3
	.short _0224A096 - _02249FD4 - 2 ; case 4
	.short _0224A0AE - _02249FD4 - 2 ; case 5
	.short _0224A0C6 - _02249FD4 - 2 ; case 6
	.short _0224A004 - _02249FD4 - 2 ; case 7
	.short _0224A13C - _02249FD4 - 2 ; case 8
	.short _0224A154 - _02249FD4 - 2 ; case 9
	.short _0224A024 - _02249FD4 - 2 ; case 10
	.short _0224A1B6 - _02249FD4 - 2 ; case 11
	.short _0224A1FC - _02249FD4 - 2 ; case 12
	.short _0224A242 - _02249FD4 - 2 ; case 13
	.short _0224A288 - _02249FD4 - 2 ; case 14
	.short _0224A2CE - _02249FD4 - 2 ; case 15
	.short _0224A314 - _02249FD4 - 2 ; case 16
	.short _0224A360 - _02249FD4 - 2 ; case 17
	.short _0224A37E - _02249FD4 - 2 ; case 18
	.short _0224A39C - _02249FD4 - 2 ; case 19
	.short _0224A3BA - _02249FD4 - 2 ; case 20
	.short _0224A424 - _02249FD4 - 2 ; case 21
	.short _0224A3D8 - _02249FD4 - 2 ; case 22
	.short _0224A43E - _02249FD4 - 2 ; case 23
_0224A004:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r4, r0
	ldr r0, _0224A320 ; =0x00002D8C
	ldr r1, [r2, r0]
	add r0, r0, #4
	ldr r0, [r2, r0]
	cmp r1, r0
	beq _0224A020
	ldr r1, _0224A324 ; =0x0000215C
	ldr r0, [sp, #0x10]
	mov r5, #0xc6
	str r0, [r4, r1]
_0224A020:
	mov r6, #1
	b _0224A45A
_0224A024:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A328 ; =0x00002D90
	ldr r2, [r1, r0]
	sub r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, r2
	beq _0224A04A
	ldr r1, [sp, #0x10]
	add r0, r1, #0
	mul r0, r2
	mov r1, #0x64
	bl MOD11_022476C0
	ldr r1, _0224A324 ; =0x0000215C
	mov r5, #0xc6
	str r0, [r4, r1]
_0224A04A:
	mov r6, #1
	b _0224A45A
_0224A04E:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A32C ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #0x40
	tst r0, r1
	beq _0224A062
	mov r5, #0xc7
_0224A062:
	mov r6, #1
	b _0224A45A
_0224A066:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A32C ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #7
	tst r0, r1
	beq _0224A07A
	mov r5, #0xc8
_0224A07A:
	mov r6, #1
	b _0224A45A
_0224A07E:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A32C ; =0x00002DAC
	ldr r1, [r1, r0]
	ldr r0, _0224A330 ; =0x00000F88
	tst r0, r1
	beq _0224A092
	mov r5, #0xc9
_0224A092:
	mov r6, #1
	b _0224A45A
_0224A096:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A32C ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #0x10
	tst r0, r1
	beq _0224A0AA
	mov r5, #0xca
_0224A0AA:
	mov r6, #1
	b _0224A45A
_0224A0AE:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A32C ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #0x20
	tst r0, r1
	beq _0224A0C2
	mov r5, #0xcb
_0224A0C2:
	mov r6, #1
	b _0224A45A
_0224A0C6:
	str r5, [sp, #0xc]
_0224A0C8:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	add r7, r1, #0
	mul r7, r0
	add r1, r4, r7
	ldr r0, _0224A334 ; =0x00002D4C
	add r2, r6, r1
	ldrh r0, [r2, r0]
	cmp r0, #0
	beq _0224A0FA
	add r2, r5, r1
	ldr r1, _0224A338 ; =0x00002D70
	ldrb r1, [r2, r1]
	bl WazaGetMaxPp
	add r1, r4, r7
	add r2, r5, r1
	ldr r1, _0224A33C ; =0x00002D6C
	ldrb r1, [r2, r1]
	sub r1, r0, r1
	ldr r0, [sp, #0xc]
	cmp r1, r0
	ble _0224A0FA
	str r1, [sp, #0xc]
	str r5, [sp, #8]
_0224A0FA:
	add r5, r5, #1
	add r6, r6, #2
	cmp r5, #4
	blt _0224A0C8
	mov r0, #0xb5
	lsl r0, r0, #6
	ldr r1, [sp, #8]
	add r0, r4, r0
	ldr r2, [sp, #0x10]
	add r0, r0, r7
	add r1, #0x1f
	bl MOD11_02243DC8
	ldr r0, [sp]
	ldr r2, [r4, #0x64]
	add r1, r4, #0
	bl MOD11_02245190
	ldr r0, [r4, #0x64]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	ldr r0, [sp, #8]
	add r2, r4, r2
	lsl r0, r0, #1
	add r2, r2, r0
	ldr r0, _0224A334 ; =0x00002D4C
	add r1, #0x64
	ldrh r0, [r2, r0]
	mov r5, #0xcc
	mov r6, #1
	str r0, [r4, r1]
	b _0224A45A
_0224A13C:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A340 ; =0x00002DB0
	ldr r1, [r1, r0]
	mov r0, #7
	tst r0, r1
	beq _0224A150
	mov r5, #0xcd
_0224A150:
	mov r6, #1
	b _0224A45A
_0224A154:
	ldr r2, [r4, #0x64]
	mov r0, #0xc0
	add r1, r2, #0
	mul r1, r0
	ldr r6, _0224A32C ; =0x00002DAC
	add r0, r4, r1
	ldr r2, [r0, r6]
	lsl r3, r2, #0x18
	lsr r3, r3, #0x18
	bne _0224A172
	add r6, r6, #4
	ldr r6, [r0, r6]
	mov r0, #7
	tst r0, r6
	beq _0224A1B2
_0224A172:
	mov r0, #0x40
	tst r0, r2
	beq _0224A17A
	mov r5, #0xc7
_0224A17A:
	mov r0, #7
	tst r0, r2
	beq _0224A182
	mov r5, #0xc8
_0224A182:
	ldr r0, _0224A330 ; =0x00000F88
	tst r0, r2
	beq _0224A18A
	mov r5, #0xc9
_0224A18A:
	mov r0, #0x10
	tst r0, r2
	beq _0224A192
	mov r5, #0xca
_0224A192:
	mov r0, #0x20
	tst r0, r2
	beq _0224A19A
	mov r5, #0xcb
_0224A19A:
	ldr r0, _0224A340 ; =0x00002DB0
	add r1, r4, r1
	ldr r1, [r1, r0]
	mov r0, #7
	and r0, r1
	beq _0224A1A8
	mov r5, #0xcd
_0224A1A8:
	cmp r3, #0
	beq _0224A1B2
	cmp r0, #0
	beq _0224A1B2
	mov r5, #0xce
_0224A1B2:
	mov r6, #1
	b _0224A45A
_0224A1B6:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	ldr r1, _0224A328 ; =0x00002D90
	add r2, r4, r0
	ldr r0, [r2, r1]
	sub r1, r1, #4
	ldr r1, [r2, r1]
	cmp r1, r0
	beq _0224A1F8
	ldr r1, [sp, #0x10]
	bl MOD11_022476C0
	ldr r1, _0224A324 ; =0x0000215C
	str r0, [r4, r1]
	mov r0, #0x13
	add r1, r6, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r2, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r2
	add r2, r4, r0
	ldr r0, _0224A344 ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	sub r1, r6, #1
	cmp r0, r1
	bne _0224A1F6
	mov r5, #0xcf
	b _0224A1F8
_0224A1F6:
	mov r5, #0xc6
_0224A1F8:
	mov r6, #1
	b _0224A45A
_0224A1FC:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	ldr r1, _0224A328 ; =0x00002D90
	add r2, r4, r0
	ldr r0, [r2, r1]
	sub r1, r1, #4
	ldr r1, [r2, r1]
	cmp r1, r0
	beq _0224A23E
	ldr r1, [sp, #0x10]
	bl MOD11_022476C0
	ldr r1, _0224A324 ; =0x0000215C
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #1
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r2, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r2
	add r2, r4, r0
	ldr r0, _0224A344 ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	sub r1, r6, #1
	cmp r0, r1
	bne _0224A23C
	mov r5, #0xcf
	b _0224A23E
_0224A23C:
	mov r5, #0xc6
_0224A23E:
	mov r6, #1
	b _0224A45A
_0224A242:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	ldr r1, _0224A328 ; =0x00002D90
	add r2, r4, r0
	ldr r0, [r2, r1]
	sub r1, r1, #4
	ldr r1, [r2, r1]
	cmp r1, r0
	beq _0224A284
	ldr r1, [sp, #0x10]
	bl MOD11_022476C0
	ldr r1, _0224A324 ; =0x0000215C
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #2
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r2, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r2
	add r2, r4, r0
	ldr r0, _0224A344 ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	sub r1, r6, #1
	cmp r0, r1
	bne _0224A282
	mov r5, #0xcf
	b _0224A284
_0224A282:
	mov r5, #0xc6
_0224A284:
	mov r6, #1
	b _0224A45A
_0224A288:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	ldr r1, _0224A328 ; =0x00002D90
	add r2, r4, r0
	ldr r0, [r2, r1]
	sub r1, r1, #4
	ldr r1, [r2, r1]
	cmp r1, r0
	beq _0224A2CA
	ldr r1, [sp, #0x10]
	bl MOD11_022476C0
	ldr r1, _0224A324 ; =0x0000215C
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #3
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r2, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r2
	add r2, r4, r0
	ldr r0, _0224A344 ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	sub r1, r6, #1
	cmp r0, r1
	bne _0224A2C8
	mov r5, #0xcf
	b _0224A2CA
_0224A2C8:
	mov r5, #0xc6
_0224A2CA:
	mov r6, #1
	b _0224A45A
_0224A2CE:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	ldr r1, _0224A328 ; =0x00002D90
	add r2, r4, r0
	ldr r0, [r2, r1]
	sub r1, r1, #4
	ldr r1, [r2, r1]
	cmp r1, r0
	beq _0224A310
	ldr r1, [sp, #0x10]
	bl MOD11_022476C0
	ldr r1, _0224A324 ; =0x0000215C
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #4
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r2, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r2
	add r2, r4, r0
	ldr r0, _0224A344 ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	sub r1, r6, #1
	cmp r0, r1
	bne _0224A30E
	mov r5, #0xcf
	b _0224A310
_0224A30E:
	mov r5, #0xc6
_0224A310:
	mov r6, #1
	b _0224A45A
_0224A314:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	add r2, r1, #0
	mul r2, r0
	ldr r1, _0224A348 ; =0x00002D59
	b _0224A34C
	.align 2, 0
_0224A320: .word 0x00002D8C
_0224A324: .word 0x0000215C
_0224A328: .word 0x00002D90
_0224A32C: .word 0x00002DAC
_0224A330: .word 0x00000F88
_0224A334: .word 0x00002D4C
_0224A338: .word 0x00002D70
_0224A33C: .word 0x00002D6C
_0224A340: .word 0x00002DB0
_0224A344: .word 0x00002DA8
_0224A348: .word 0x00002D59
_0224A34C:
	add r2, r4, r2
	ldrsb r1, [r2, r1]
	cmp r1, #0xc
	bge _0224A35C
	mov r1, #1
	add r0, #0x70
	str r1, [r4, r0]
	mov r5, #0xd0
_0224A35C:
	mov r6, #1
	b _0224A45A
_0224A360:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	add r2, r1, #0
	mul r2, r0
	ldr r1, _0224A4C0 ; =0x00002D5A
	add r2, r4, r2
	ldrsb r1, [r2, r1]
	cmp r1, #0xc
	bge _0224A37A
	mov r1, #2
	add r0, #0x70
	str r1, [r4, r0]
	mov r5, #0xd0
_0224A37A:
	mov r6, #1
	b _0224A45A
_0224A37E:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	add r2, r1, #0
	mul r2, r0
	ldr r1, _0224A4C4 ; =0x00002D5B
	add r2, r4, r2
	ldrsb r1, [r2, r1]
	cmp r1, #0xc
	bge _0224A398
	mov r1, #3
	add r0, #0x70
	str r1, [r4, r0]
	mov r5, #0xd0
_0224A398:
	mov r6, #1
	b _0224A45A
_0224A39C:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	add r2, r1, #0
	mul r2, r0
	ldr r1, _0224A4C8 ; =0x00002D5C
	add r2, r4, r2
	ldrsb r1, [r2, r1]
	cmp r1, #0xc
	bge _0224A3B6
	mov r1, #4
	add r0, #0x70
	str r1, [r4, r0]
	mov r5, #0xd0
_0224A3B6:
	mov r6, #1
	b _0224A45A
_0224A3BA:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	add r2, r1, #0
	mul r2, r0
	ldr r1, _0224A4CC ; =0x00002D5D
	add r2, r4, r2
	ldrsb r1, [r2, r1]
	cmp r1, #0xc
	bge _0224A3D4
	mov r1, #5
	add r0, #0x70
	str r1, [r4, r0]
	mov r5, #0xd0
_0224A3D4:
	mov r6, #1
	b _0224A45A
_0224A3D8:
	ldr r2, [r4, #0x64]
	mov r1, #0xc0
	mul r1, r2
	add r3, r4, r1
	ldr r1, _0224A4D0 ; =0x00002D59
	add r0, r6, #0
_0224A3E4:
	ldrsb r2, [r3, r1]
	cmp r2, #0xc
	blt _0224A3F2
	add r0, r0, #1
	add r3, r3, #1
	cmp r0, #5
	blt _0224A3E4
_0224A3F2:
	cmp r0, #5
	beq _0224A420
	ldr r5, _0224A4D0 ; =0x00002D59
	mov r7, #5
	mov r6, #0xc0
_0224A3FC:
	bl LCRandom
	add r1, r7, #0
	bl _s32_div_f
	ldr r0, [r4, #0x64]
	add r2, r0, #0
	mul r2, r6
	add r0, r4, r2
	add r0, r1, r0
	ldrsb r0, [r0, r5]
	cmp r0, #0xc
	beq _0224A3FC
	mov r0, #0x13
	add r1, r1, #1
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r5, #0xd2
_0224A420:
	mov r6, #1
	b _0224A45A
_0224A424:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A4D4 ; =0x00002DB0
	ldr r1, [r1, r0]
	mov r0, #1
	lsl r0, r0, #0x14
	tst r0, r1
	bne _0224A43A
	mov r5, #0xd1
_0224A43A:
	mov r6, #1
	b _0224A45A
_0224A43E:
	ldr r5, _0224A4D8 ; =0x00000109
	mov r6, #1
	b _0224A45A
_0224A444:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _0224A4DC ; =0x00002DB8
	add r1, r4, r1
	ldrh r0, [r1, r0]
	bl ItemIdIsBerry
	cmp r0, #1
	bne _0224A45A
	mov r6, #1
_0224A45A:
	cmp r6, #1
	bne _0224A4B8
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x67
	beq _0224A482
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	add r2, r1, #0
	mul r2, r0
	mov r1, #0xb7
	add r2, r4, r2
	lsl r1, r1, #6
	ldr r2, [r2, r1]
	mov r1, #1
	lsl r1, r1, #0x1a
	tst r1, r2
	beq _0224A48C
_0224A482:
	mov r0, #0x4e
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _0224A490
_0224A48C:
	add r0, #0x78
	str r5, [r4, r0]
_0224A490:
	ldr r0, [sp, #4]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	ldr r0, _0224A4DC ; =0x00002DB8
	add r2, r4, r2
	ldrh r0, [r2, r0]
	add r1, #0x68
	str r0, [r4, r1]
	ldr r2, [r4, #0x64]
	mov r0, #0xba
	lsl r0, r0, #2
	mov r1, #0x1c
	add r3, r2, #0
	mul r3, r1
	add r0, r4, r0
	ldr r2, [r0, r3]
	mov r1, #2
	orr r1, r2
	str r1, [r0, r3]
_0224A4B8:
	add r0, r6, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0224A4C0: .word 0x00002D5A
_0224A4C4: .word 0x00002D5B
_0224A4C8: .word 0x00002D5C
_0224A4CC: .word 0x00002D5D
_0224A4D0: .word 0x00002D59
_0224A4D4: .word 0x00002DB0
_0224A4D8: .word 0x00000109
_0224A4DC: .word 0x00002DB8

	thumb_func_start MOD11_0224A4E0
MOD11_0224A4E0: ; 0x0224A4E0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r1, #0
	str r0, [sp]
	str r2, [sp, #4]
	add r0, r4, #0
	add r1, r2, #0
	bl MOD11_02249E30
	add r6, r0, #0
	ldr r1, [sp, #4]
	add r0, r4, #0
	mov r2, #2
	bl MOD11_02249DA4
	str r0, [sp, #0x10]
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD11_02249E58
	ldr r1, _0224A84C ; =0x00002154
	add r2, r4, #0
	str r0, [r4, r1]
	ldr r0, _0224A850 ; =0x00003118
	mov r5, #0
	str r5, [r4, r0]
	add r2, #0x88
	str r5, [r2]
	ldr r1, [r4, r1]
	cmp r1, #0
	bne _0224A524
	add sp, #0x14
	add r0, r5, #0
	pop {r4, r5, r6, r7, pc}
_0224A524:
	cmp r6, #0x1e
	bls _0224A52A
	b _0224AAAC
_0224A52A:
	add r1, r6, r6
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0224A536: ; jump table
	.short _0224AAAC - _0224A536 - 2 ; case 0
	.short _0224A5A2 - _0224A536 - 2 ; case 1
	.short _0224A5BA - _0224A536 - 2 ; case 2
	.short _0224A5D2 - _0224A536 - 2 ; case 3
	.short _0224A5EA - _0224A536 - 2 ; case 4
	.short _0224A602 - _0224A536 - 2 ; case 5
	.short _0224A61A - _0224A536 - 2 ; case 6
	.short _0224A574 - _0224A536 - 2 ; case 7
	.short _0224A69C - _0224A536 - 2 ; case 8
	.short _0224A6B4 - _0224A536 - 2 ; case 9
	.short _0224A580 - _0224A536 - 2 ; case 10
	.short _0224A77A - _0224A536 - 2 ; case 11
	.short _0224A7BC - _0224A536 - 2 ; case 12
	.short _0224A7FE - _0224A536 - 2 ; case 13
	.short _0224A840 - _0224A536 - 2 ; case 14
	.short _0224A8B0 - _0224A536 - 2 ; case 15
	.short _0224A9AC - _0224A536 - 2 ; case 16
	.short _0224A9CA - _0224A536 - 2 ; case 17
	.short _0224A9E8 - _0224A536 - 2 ; case 18
	.short _0224AA06 - _0224A536 - 2 ; case 19
	.short _0224AA24 - _0224A536 - 2 ; case 20
	.short _0224AA8E - _0224A536 - 2 ; case 21
	.short _0224AA42 - _0224A536 - 2 ; case 22
	.short _0224AAA8 - _0224A536 - 2 ; case 23
	.short _0224A8F2 - _0224A536 - 2 ; case 24
	.short _0224A91A - _0224A536 - 2 ; case 25
	.short _0224A93E - _0224A536 - 2 ; case 26
	.short _0224A954 - _0224A536 - 2 ; case 27
	.short _0224A96A - _0224A536 - 2 ; case 28
	.short _0224A980 - _0224A536 - 2 ; case 29
	.short _0224A996 - _0224A536 - 2 ; case 30
_0224A574:
	ldr r1, [sp, #0x10]
	sub r2, r0, #4
	str r1, [r4, r2]
	mov r1, #0xc6
	str r1, [r4, r0]
	b _0224AAAC
_0224A580:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A854 ; =0x00002D90
	ldr r0, [r1, r0]
	ldr r1, [sp, #0x10]
	mul r0, r1
	mov r1, #0x64
	bl MOD11_022476C0
	ldr r1, _0224A858 ; =0x00003114
	mov r2, #0xc6
	str r0, [r4, r1]
	add r0, r1, #4
	str r2, [r4, r0]
	b _0224AAAC
_0224A5A2:
	ldr r2, [r4, #0x6c]
	mov r1, #0xc0
	mul r1, r2
	add r2, r4, r1
	ldr r1, _0224A85C ; =0x00002DAC
	ldr r2, [r2, r1]
	mov r1, #0x40
	tst r1, r2
	beq _0224A65C
	mov r1, #0xc7
	str r1, [r4, r0]
	b _0224AAAC
_0224A5BA:
	ldr r2, [r4, #0x6c]
	mov r1, #0xc0
	mul r1, r2
	add r2, r4, r1
	ldr r1, _0224A85C ; =0x00002DAC
	ldr r2, [r2, r1]
	mov r1, #7
	tst r1, r2
	beq _0224A65C
	mov r1, #0xc8
	str r1, [r4, r0]
	b _0224AAAC
_0224A5D2:
	ldr r2, [r4, #0x6c]
	mov r1, #0xc0
	mul r1, r2
	add r2, r4, r1
	ldr r1, _0224A85C ; =0x00002DAC
	ldr r2, [r2, r1]
	ldr r1, _0224A860 ; =0x00000F88
	tst r1, r2
	beq _0224A65C
	mov r1, #0xc9
	str r1, [r4, r0]
	b _0224AAAC
_0224A5EA:
	ldr r2, [r4, #0x6c]
	mov r1, #0xc0
	mul r1, r2
	add r2, r4, r1
	ldr r1, _0224A85C ; =0x00002DAC
	ldr r2, [r2, r1]
	mov r1, #0x10
	tst r1, r2
	beq _0224A65C
	mov r1, #0xca
	str r1, [r4, r0]
	b _0224AAAC
_0224A602:
	ldr r2, [r4, #0x6c]
	mov r1, #0xc0
	mul r1, r2
	add r2, r4, r1
	ldr r1, _0224A85C ; =0x00002DAC
	ldr r2, [r2, r1]
	mov r1, #0x20
	tst r1, r2
	beq _0224A65C
	mov r1, #0xcb
	str r1, [r4, r0]
	b _0224AAAC
_0224A61A:
	add r6, r5, #0
	add r7, r5, #0
_0224A61E:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	str r0, [sp, #8]
	ldr r0, _0224A864 ; =0x00002D4C
	add r2, r7, r1
	ldrh r0, [r2, r0]
	cmp r0, #0
	beq _0224A650
	add r2, r6, r1
	ldr r1, _0224A868 ; =0x00002D70
	ldrb r1, [r2, r1]
	bl WazaGetMaxPp
	ldr r1, [sp, #8]
	add r1, r4, r1
	add r2, r6, r1
	ldr r1, _0224A86C ; =0x00002D6C
	ldrb r1, [r2, r1]
	sub r0, r0, r1
	cmp r0, r5
	ble _0224A650
	add r5, r0, #0
	str r6, [sp, #0xc]
_0224A650:
	add r6, r6, #1
	add r7, r7, #2
	cmp r6, #4
	blt _0224A61E
	cmp r5, #0
	bne _0224A65E
_0224A65C:
	b _0224AAAC
_0224A65E:
	mov r0, #0xb5
	lsl r0, r0, #6
	add r1, r4, r0
	ldr r0, [sp, #8]
	ldr r2, [sp, #0x10]
	add r0, r1, r0
	ldr r1, [sp, #0xc]
	add r1, #0x1f
	bl MOD11_02243DC8
	ldr r0, [sp]
	ldr r2, [r4, #0x6c]
	add r1, r4, #0
	bl MOD11_02245190
	ldr r0, [r4, #0x6c]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	ldr r0, [sp, #0xc]
	add r2, r4, r2
	lsl r0, r0, #1
	add r2, r2, r0
	ldr r0, _0224A864 ; =0x00002D4C
	add r1, #0x64
	ldrh r0, [r2, r0]
	str r0, [r4, r1]
	ldr r0, _0224A850 ; =0x00003118
	mov r1, #0xcc
	str r1, [r4, r0]
	b _0224AAAC
_0224A69C:
	ldr r2, [r4, #0x6c]
	mov r1, #0xc0
	mul r1, r2
	add r2, r4, r1
	ldr r1, _0224A870 ; =0x00002DB0
	ldr r2, [r2, r1]
	mov r1, #7
	tst r1, r2
	beq _0224A770
	mov r1, #0xcd
	str r1, [r4, r0]
	b _0224AAAC
_0224A6B4:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	ldr r1, _0224A85C ; =0x00002DAC
	add r3, r4, r0
	ldr r0, [r3, r1]
	lsl r2, r0, #0x18
	lsr r2, r2, #0x18
	bne _0224A6D0
	add r1, r1, #4
	ldr r2, [r3, r1]
	mov r1, #7
	tst r1, r2
	beq _0224A770
_0224A6D0:
	mov r1, #0x40
	tst r0, r1
	beq _0224A6DC
	ldr r0, _0224A850 ; =0x00003118
	mov r1, #0xc7
	str r1, [r4, r0]
_0224A6DC:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A85C ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #7
	tst r0, r1
	beq _0224A6F4
	ldr r0, _0224A850 ; =0x00003118
	mov r1, #0xc8
	str r1, [r4, r0]
_0224A6F4:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A85C ; =0x00002DAC
	ldr r1, [r1, r0]
	ldr r0, _0224A860 ; =0x00000F88
	tst r0, r1
	beq _0224A70C
	ldr r0, _0224A850 ; =0x00003118
	mov r1, #0xc9
	str r1, [r4, r0]
_0224A70C:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A85C ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #0x10
	tst r0, r1
	beq _0224A724
	ldr r0, _0224A850 ; =0x00003118
	mov r1, #0xca
	str r1, [r4, r0]
_0224A724:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A85C ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #0x20
	tst r0, r1
	beq _0224A73C
	ldr r0, _0224A850 ; =0x00003118
	mov r1, #0xcb
	str r1, [r4, r0]
_0224A73C:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A870 ; =0x00002DB0
	ldr r1, [r1, r0]
	mov r0, #7
	tst r0, r1
	beq _0224A754
	ldr r0, _0224A850 ; =0x00003118
	mov r1, #0xcd
	str r1, [r4, r0]
_0224A754:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r2, r4, r0
	ldr r0, _0224A85C ; =0x00002DAC
	ldr r1, [r2, r0]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	beq _0224A770
	add r0, r0, #4
	ldr r1, [r2, r0]
	mov r0, #7
	tst r0, r1
	bne _0224A772
_0224A770:
	b _0224AAAC
_0224A772:
	ldr r0, _0224A850 ; =0x00003118
	mov r1, #0xce
	str r1, [r4, r0]
	b _0224AAAC
_0224A77A:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A854 ; =0x00002D90
	ldr r0, [r1, r0]
	ldr r1, [sp, #0x10]
	bl MOD11_022476C0
	ldr r1, _0224A858 ; =0x00003114
	str r0, [r4, r1]
	mov r0, #0x13
	add r1, r5, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r2, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r2
	add r2, r4, r0
	ldr r0, _0224A874 ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	sub r1, r5, #1
	cmp r0, r1
	ldr r0, _0224A850 ; =0x00003118
	bne _0224A7B6
	mov r1, #0xcf
	str r1, [r4, r0]
	b _0224AAAC
_0224A7B6:
	mov r1, #0xc6
	str r1, [r4, r0]
	b _0224AAAC
_0224A7BC:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A854 ; =0x00002D90
	ldr r0, [r1, r0]
	ldr r1, [sp, #0x10]
	bl MOD11_022476C0
	ldr r1, _0224A858 ; =0x00003114
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #1
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r2, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r2
	add r2, r4, r0
	ldr r0, _0224A874 ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	sub r1, r5, #1
	cmp r0, r1
	ldr r0, _0224A850 ; =0x00003118
	bne _0224A7F8
	mov r1, #0xcf
	str r1, [r4, r0]
	b _0224AAAC
_0224A7F8:
	mov r1, #0xc6
	str r1, [r4, r0]
	b _0224AAAC
_0224A7FE:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A854 ; =0x00002D90
	ldr r0, [r1, r0]
	ldr r1, [sp, #0x10]
	bl MOD11_022476C0
	ldr r1, _0224A858 ; =0x00003114
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #2
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r2, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r2
	add r2, r4, r0
	ldr r0, _0224A874 ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	sub r1, r5, #1
	cmp r0, r1
	ldr r0, _0224A850 ; =0x00003118
	bne _0224A83A
	mov r1, #0xcf
	str r1, [r4, r0]
	b _0224AAAC
_0224A83A:
	mov r1, #0xc6
	str r1, [r4, r0]
	b _0224AAAC
_0224A840:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224A854 ; =0x00002D90
	b _0224A878
	.align 2, 0
_0224A84C: .word 0x00002154
_0224A850: .word 0x00003118
_0224A854: .word 0x00002D90
_0224A858: .word 0x00003114
_0224A85C: .word 0x00002DAC
_0224A860: .word 0x00000F88
_0224A864: .word 0x00002D4C
_0224A868: .word 0x00002D70
_0224A86C: .word 0x00002D6C
_0224A870: .word 0x00002DB0
_0224A874: .word 0x00002DA8
_0224A878:
	ldr r0, [r1, r0]
	ldr r1, [sp, #0x10]
	bl MOD11_022476C0
	ldr r1, _0224AB14 ; =0x00003114
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #3
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r2, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r2
	add r2, r4, r0
	ldr r0, _0224AB18 ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	sub r1, r5, #1
	cmp r0, r1
	ldr r0, _0224AB1C ; =0x00003118
	bne _0224A8AA
	mov r1, #0xcf
	str r1, [r4, r0]
	b _0224AAAC
_0224A8AA:
	mov r1, #0xc6
	str r1, [r4, r0]
	b _0224AAAC
_0224A8B0:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0224AB20 ; =0x00002D90
	ldr r0, [r1, r0]
	ldr r1, [sp, #0x10]
	bl MOD11_022476C0
	ldr r1, _0224AB14 ; =0x00003114
	str r0, [r4, r1]
	mov r0, #0x13
	mov r1, #4
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r2, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r2
	add r2, r4, r0
	ldr r0, _0224AB18 ; =0x00002DA8
	ldr r0, [r2, r0]
	bl GetFlavorPreferenceFromPID
	sub r1, r5, #1
	cmp r0, r1
	ldr r0, _0224AB1C ; =0x00003118
	bne _0224A8EC
	mov r1, #0xcf
	str r1, [r4, r0]
	b _0224AAAC
_0224A8EC:
	mov r1, #0xc6
	str r1, [r4, r0]
	b _0224AAAC
_0224A8F2:
	ldr r2, _0224AB24 ; =0x00002D58
	mov r6, #6
	mov r3, #0xd3
	mov r7, #0xc0
_0224A8FA:
	ldr r0, [r4, #0x6c]
	add r1, r0, #0
	mul r1, r7
	add r0, r4, r1
	add r0, r0, r5
	ldrsb r1, [r0, r2]
	cmp r1, #6
	bge _0224A912
	ldr r1, _0224AB24 ; =0x00002D58
	strb r6, [r0, r1]
	ldr r0, _0224AB1C ; =0x00003118
	str r3, [r4, r0]
_0224A912:
	add r5, r5, #1
	cmp r5, #8
	blt _0224A8FA
	b _0224AAAC
_0224A91A:
	ldr r2, [r4, #0x6c]
	mov r1, #0xc0
	add r3, r2, #0
	mul r3, r1
	ldr r2, _0224AB28 ; =0x00002DB0
	add r3, r4, r3
	ldr r3, [r3, r2]
	mov r2, #0xf
	lsl r2, r2, #0x10
	tst r2, r3
	bne _0224A932
	b _0224AAAC
_0224A932:
	mov r2, #6
	add r1, #0x70
	str r2, [r4, r1]
	mov r1, #0xd4
	str r1, [r4, r0]
	b _0224AAAC
_0224A93E:
	add r2, r4, #0
	ldr r1, [sp, #4]
	add r2, #0x94
	str r1, [r2]
	add r1, r4, #0
	mov r2, #2
	add r1, #0x88
	str r2, [r1]
	mov r1, #0xe
	str r1, [r4, r0]
	b _0224AAAC
_0224A954:
	add r2, r4, #0
	ldr r1, [sp, #4]
	add r2, #0x94
	str r1, [r2]
	add r1, r4, #0
	mov r2, #2
	add r1, #0x88
	str r2, [r1]
	mov r1, #0x1f
	str r1, [r4, r0]
	b _0224AAAC
_0224A96A:
	add r2, r4, #0
	ldr r1, [sp, #4]
	add r2, #0x94
	str r1, [r2]
	add r1, r4, #0
	mov r2, #2
	add r1, #0x88
	str r2, [r1]
	mov r1, #0x16
	str r1, [r4, r0]
	b _0224AAAC
_0224A980:
	add r2, r4, #0
	ldr r1, [sp, #4]
	add r2, #0x94
	str r1, [r2]
	add r1, r4, #0
	mov r2, #2
	add r1, #0x88
	str r2, [r1]
	mov r1, #0x2f
	str r1, [r4, r0]
	b _0224AAAC
_0224A996:
	add r2, r4, #0
	ldr r1, [sp, #4]
	add r2, #0x94
	str r1, [r2]
	add r1, r4, #0
	mov r2, #2
	add r1, #0x88
	str r2, [r1]
	mov r1, #0x19
	str r1, [r4, r0]
	b _0224AAAC
_0224A9AC:
	ldr r2, [r4, #0x6c]
	mov r1, #0xc0
	add r3, r2, #0
	mul r3, r1
	ldr r2, _0224AB2C ; =0x00002D59
	add r3, r4, r3
	ldrsb r2, [r3, r2]
	cmp r2, #0xc
	bge _0224AAAC
	mov r2, #1
	add r1, #0x70
	str r2, [r4, r1]
	mov r1, #0xd0
	str r1, [r4, r0]
	b _0224AAAC
_0224A9CA:
	ldr r2, [r4, #0x6c]
	mov r1, #0xc0
	add r3, r2, #0
	mul r3, r1
	ldr r2, _0224AB30 ; =0x00002D5A
	add r3, r4, r3
	ldrsb r2, [r3, r2]
	cmp r2, #0xc
	bge _0224AAAC
	mov r2, #2
	add r1, #0x70
	str r2, [r4, r1]
	mov r1, #0xd0
	str r1, [r4, r0]
	b _0224AAAC
_0224A9E8:
	ldr r2, [r4, #0x6c]
	mov r1, #0xc0
	add r3, r2, #0
	mul r3, r1
	ldr r2, _0224AB34 ; =0x00002D5B
	add r3, r4, r3
	ldrsb r2, [r3, r2]
	cmp r2, #0xc
	bge _0224AAAC
	mov r2, #3
	add r1, #0x70
	str r2, [r4, r1]
	mov r1, #0xd0
	str r1, [r4, r0]
	b _0224AAAC
_0224AA06:
	ldr r2, [r4, #0x6c]
	mov r1, #0xc0
	add r3, r2, #0
	mul r3, r1
	ldr r2, _0224AB38 ; =0x00002D5C
	add r3, r4, r3
	ldrsb r2, [r3, r2]
	cmp r2, #0xc
	bge _0224AAAC
	mov r2, #4
	add r1, #0x70
	str r2, [r4, r1]
	mov r1, #0xd0
	str r1, [r4, r0]
	b _0224AAAC
_0224AA24:
	ldr r2, [r4, #0x6c]
	mov r1, #0xc0
	add r3, r2, #0
	mul r3, r1
	ldr r2, _0224AB3C ; =0x00002D5D
	add r3, r4, r3
	ldrsb r2, [r3, r2]
	cmp r2, #0xc
	bge _0224AAAC
	mov r2, #5
	add r1, #0x70
	str r2, [r4, r1]
	mov r1, #0xd0
	str r1, [r4, r0]
	b _0224AAAC
_0224AA42:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r2, r4, r0
	ldr r0, _0224AB2C ; =0x00002D59
_0224AA4C:
	ldrsb r1, [r2, r0]
	cmp r1, #0xc
	blt _0224AA5A
	add r5, r5, #1
	add r2, r2, #1
	cmp r5, #5
	blt _0224AA4C
_0224AA5A:
	cmp r5, #5
	beq _0224AAAC
	ldr r5, _0224AB2C ; =0x00002D59
	mov r7, #5
	mov r6, #0xc0
_0224AA64:
	bl LCRandom
	add r1, r7, #0
	bl _s32_div_f
	ldr r0, [r4, #0x6c]
	add r2, r0, #0
	mul r2, r6
	add r0, r4, r2
	add r0, r1, r0
	ldrsb r0, [r0, r5]
	cmp r0, #0xc
	beq _0224AA64
	mov r0, #0x13
	add r1, r1, #1
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r0, _0224AB1C ; =0x00003118
	mov r1, #0xd2
	str r1, [r4, r0]
	b _0224AAAC
_0224AA8E:
	ldr r2, [r4, #0x6c]
	mov r1, #0xc0
	mul r1, r2
	add r2, r4, r1
	ldr r1, _0224AB28 ; =0x00002DB0
	ldr r2, [r2, r1]
	mov r1, #1
	lsl r1, r1, #0x14
	tst r1, r2
	bne _0224AAAC
	mov r1, #0xd1
	str r1, [r4, r0]
	b _0224AAAC
_0224AAA8:
	ldr r1, _0224AB40 ; =0x00000109
	str r1, [r4, r0]
_0224AAAC:
	ldr r0, [r4, #0x6c]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	add r0, r4, r2
	mov r2, #0xb7
	lsl r2, r2, #6
	ldr r3, [r0, r2]
	mov r0, #1
	lsl r0, r0, #0x1a
	tst r0, r3
	beq _0224AACC
	ldr r0, _0224AB1C ; =0x00003118
	mov r1, #0
	str r1, [r4, r0]
	b _0224AB0C
_0224AACC:
	ldr r0, [sp, #4]
	sub r2, #8
	add r3, r0, #0
	mul r3, r1
	add r0, r4, r3
	ldrh r0, [r0, r2]
	add r1, #0x68
	str r0, [r4, r1]
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #0
	bne _0224AB04
	ldr r0, _0224AB1C ; =0x00003118
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0224AB04
	mov r0, #0xba
	ldr r1, [r4, #0x64]
	lsl r0, r0, #2
	add r3, r4, r0
	mov r0, #0x1c
	add r2, r1, #0
	mul r2, r0
	ldr r1, [r3, r2]
	mov r0, #2
	orr r0, r1
	str r0, [r3, r2]
_0224AB04:
	mov r0, #0x46
	ldr r1, [r4, #0x6c]
	lsl r0, r0, #2
	str r1, [r4, r0]
_0224AB0C:
	mov r0, #1
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0224AB14: .word 0x00003114
_0224AB18: .word 0x00002DA8
_0224AB1C: .word 0x00003118
_0224AB20: .word 0x00002D90
_0224AB24: .word 0x00002D58
_0224AB28: .word 0x00002DB0
_0224AB2C: .word 0x00002D59
_0224AB30: .word 0x00002D5A
_0224AB34: .word 0x00002D5B
_0224AB38: .word 0x00002D5C
_0224AB3C: .word 0x00002D5D
_0224AB40: .word 0x00000109

	thumb_func_start MOD11_0224AB44
MOD11_0224AB44: ; 0x0224AB44
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl MOD11_02249D90
	cmp r0, #0x68
	bne _0224ABD2
	ldr r5, [r4, #0x64]
	mov r6, #0xc0
	add r3, r5, #0
	mul r3, r6
	ldr r0, _0224ABE8 ; =0x00002DB0
	add r2, r4, r3
	ldr r1, [r2, r0]
	lsl r6, r6, #4
	tst r6, r1
	bne _0224ABE6
	mov r6, #0x70
	tst r6, r1
	bne _0224ABE6
	ldr r6, _0224ABEC ; =0x0000213C
	ldr r7, [r4, r6]
	mov r6, #2
	lsl r6, r6, #8
	tst r7, r6
	bne _0224ABE6
	lsl r6, r6, #3
	tst r1, r6
	bne _0224ABE6
	mov r6, #0xc1
	lsl r6, r6, #6
	lsl r5, r5, #1
	add r7, r4, r5
	add r5, r6, #0
	add r5, #0x9c
	ldrh r5, [r7, r5]
	ldr r1, [r4, r6]
	cmp r1, r5
	bne _0224ABB8
	add r1, r0, #0
	add r1, #0x1c
	ldr r1, [r2, r1]
	lsl r1, r1, #5
	lsr r5, r1, #0x1c
	cmp r5, #0xa
	bhs _0224ABE6
	add r0, #0x1c
	add r0, r4, r0
	ldr r2, [r0, r3]
	ldr r1, _0224ABF0 ; =0xF87FFFFF
	and r2, r1
	add r1, r5, #1
	lsl r1, r1, #0x1c
	lsr r1, r1, #5
	orr r1, r2
	str r1, [r0, r3]
	pop {r3, r4, r5, r6, r7, pc}
_0224ABB8:
	add r0, #0x1c
	add r2, r4, r0
	ldr r1, [r2, r3]
	ldr r0, _0224ABF0 ; =0xF87FFFFF
	and r0, r1
	str r0, [r2, r3]
	ldr r0, [r4, #0x64]
	ldr r1, [r4, r6]
	lsl r0, r0, #1
	add r0, r4, r0
	add r6, #0x9c
	strh r1, [r0, r6]
	pop {r3, r4, r5, r6, r7, pc}
_0224ABD2:
	ldr r0, _0224ABF4 ; =0x00002DCC
	ldr r1, [r4, #0x64]
	add r3, r4, r0
	mov r0, #0xc0
	add r2, r1, #0
	mul r2, r0
	ldr r1, [r3, r2]
	ldr r0, _0224ABF0 ; =0xF87FFFFF
	and r0, r1
	str r0, [r3, r2]
_0224ABE6:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224ABE8: .word 0x00002DB0
_0224ABEC: .word 0x0000213C
_0224ABF0: .word 0xF87FFFFF
_0224ABF4: .word 0x00002DCC

	thumb_func_start MOD11_0224ABF8
MOD11_0224ABF8: ; 0x0224ABF8
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl MOD11_02249D90
	cmp r0, #0x68
	bne _0224AC84
	ldr r5, _0224AC9C ; =0x0000216C
	ldr r0, _0224ACA0 ; =0x801FDA49
	ldr r1, [r4, r5]
	tst r0, r1
	beq _0224AC98
	ldr r2, [r4, #0x64]
	mov r0, #0xc1
	lsl r0, r0, #6
	lsl r1, r2, #1
	ldr r3, [r4, r0]
	add r1, r4, r1
	add r0, #0x9c
	ldrh r0, [r1, r0]
	cmp r3, r0
	bne _0224AC98
	mov r0, #0xc0
	add r1, r2, #0
	mul r1, r0
	ldr r3, _0224ACA4 ; =0x00002DCC
	add r6, r4, r1
	ldr r0, [r6, r3]
	lsl r0, r0, #5
	lsr r0, r0, #0x1c
	beq _0224AC98
	mov r7, #0x1c
	mul r7, r2
	mov r2, #0xb5
	add r7, r4, r7
	lsl r2, r2, #2
	ldr r7, [r7, r2]
	lsl r7, r7, #0x17
	lsr r7, r7, #0x1d
	bne _0224AC98
	add r7, r3, #0
	sub r7, #0x1c
	ldr r6, [r6, r7]
	mov r7, #0xc0
	lsl r7, r7, #4
	tst r7, r6
	bne _0224AC98
	mov r7, #0x70
	tst r7, r6
	bne _0224AC98
	sub r5, #0x30
	ldr r5, [r4, r5]
	sub r2, #0xd4
	tst r2, r5
	bne _0224AC98
	mov r2, #1
	lsl r2, r2, #0xc
	tst r2, r6
	bne _0224AC98
	add r2, r4, r3
	sub r0, r0, #1
	lsl r0, r0, #0x1c
	ldr r4, [r2, r1]
	ldr r3, _0224ACA8 ; =0xF87FFFFF
	lsr r0, r0, #5
	and r3, r4
	orr r0, r3
	str r0, [r2, r1]
	pop {r3, r4, r5, r6, r7, pc}
_0224AC84:
	ldr r0, _0224ACA4 ; =0x00002DCC
	ldr r1, [r4, #0x64]
	add r3, r4, r0
	mov r0, #0xc0
	add r2, r1, #0
	mul r2, r0
	ldr r1, [r3, r2]
	ldr r0, _0224ACA8 ; =0xF87FFFFF
	and r0, r1
	str r0, [r3, r2]
_0224AC98:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224AC9C: .word 0x0000216C
_0224ACA0: .word 0x801FDA49
_0224ACA4: .word 0x00002DCC
_0224ACA8: .word 0xF87FFFFF

	thumb_func_start MOD11_0224ACAC
MOD11_0224ACAC: ; 0x0224ACAC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	cmp r3, #1
	bne _0224ACBE
	sub r0, r2, #2
	cmp r0, #1
	bhi _0224ACBE
	mov r0, #1
	b _0224ACC0
_0224ACBE:
	mov r0, #0
_0224ACC0:
	cmp r0, #1
	mov r0, #0xc0
	add r4, r1, #0
	mul r4, r0
	ldr r2, _0224ACFC ; =0x00002D8C
	add r1, r5, r4
	ldr r0, [r1, r2]
	add r2, r2, #4
	ldr r1, [r1, r2]
	lsl r0, r0, #0x10
	lsl r1, r1, #0x10
	lsr r0, r0, #0x10
	lsr r1, r1, #0x10
	mov r2, #0x30
	mov r6, #0
	bl sub_02079A54
	ldr r1, _0224AD00 ; =0x00002DAC
	add r2, r5, r4
	ldr r1, [r2, r1]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bne _0224ACF6
	cmp r0, #4
	beq _0224ACF8
	cmp r0, #3
	beq _0224ACF8
_0224ACF6:
	mov r6, #0xb
_0224ACF8:
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224ACFC: .word 0x00002D8C
_0224AD00: .word 0x00002DAC

	thumb_func_start MOD11_0224AD04
MOD11_0224AD04: ; 0x0224AD04
	push {r3, r4}
	mov r3, #0xc0
	add r4, r1, #0
	mul r4, r3
	add r1, r0, r4
	ldr r0, _0224AD34 ; =0x00002DB0
	mov r2, #1
	ldr r0, [r1, r0]
	lsl r1, r2, #0x16
	tst r1, r0
	bne _0224AD2C
	lsl r1, r3, #4
	tst r1, r0
	bne _0224AD2C
	mov r1, #0x70
	tst r1, r0
	bne _0224AD2C
	lsl r1, r2, #0xc
	tst r0, r1
	beq _0224AD2E
_0224AD2C:
	mov r2, #0
_0224AD2E:
	add r0, r2, #0
	pop {r3, r4}
	bx lr
	.align 2, 0
_0224AD34: .word 0x00002DB0

	thumb_func_start MOD11_0224AD38
MOD11_0224AD38: ; 0x0224AD38
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	mov r1, #0
	add r6, r2, #0
	bl MOD11_022301D4
	str r0, [sp, #0xc]
	add r0, r5, #0
	bl MOD11_022302B0
	str r0, [sp, #8]
	add r0, r5, #0
	bl MOD11_02230294
	add r7, r0, #0
	add r0, r5, #0
	bl MOD11_0222FF74
	mov r1, #2
	lsl r1, r1, #8
	tst r0, r1
	beq _0224AD76
	add r0, r6, #0
	mov r1, #0x9a
	mov r2, #0
	bl GetMonData
	add r2, r0, #0
	b _0224AD7A
_0224AD76:
	sub r1, #0xd8
	ldr r2, [r4, r1]
_0224AD7A:
	str r7, [sp]
	mov r0, #5
	str r0, [sp, #4]
	ldr r1, [sp, #0xc]
	ldr r3, [sp, #8]
	add r0, r6, #0
	bl sub_0206A014
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD11_0224AD90
MOD11_0224AD90: ; 0x0224AD90
	lsl r1, r1, #8
	add r1, r0, r1
	mov r0, #0x23
	lsl r0, r0, #8
	ldrb r0, [r1, r0]
	bx lr

	thumb_func_start MOD11_0224AD9C
MOD11_0224AD9C: ; 0x0224AD9C
	mov r3, #0x1c
	mul r3, r1
	add r1, r0, r3
	mov r0, #0xba
	lsl r0, r0, #2
	ldr r1, [r1, r0]
	mov r0, #8
	mov r2, #0
	tst r0, r1
	beq _0224ADB2
	mov r2, #1
_0224ADB2:
	add r0, r2, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD11_0224ADB8
MOD11_0224ADB8: ; 0x0224ADB8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	mov r1, #0
	bl MOD11_022301D4
	add r4, r0, #0
	bl PlayerProfile_GetTrainerID
	add r6, r0, #0
	add r0, r4, #0
	bl PlayerProfile_GetTrainerGender
	add r7, r0, #0
	add r0, r4, #0
	bl PlayerProfile_GetNamePtr
	ldr r2, [r5, #0x64]
	mov r1, #0xc0
	add r4, r2, #0
	mul r4, r1
	ldr r1, _0224AE10 ; =0x00002DB4
	add r3, r5, r4
	ldr r2, [r3, r1]
	cmp r6, r2
	bne _0224AE0C
	add r2, r1, #0
	add r2, #0xa
	ldrb r2, [r3, r2]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x1c
	cmp r7, r2
	bne _0224AE0C
	sub r1, #0x20
	add r1, r5, r1
	add r1, r1, r4
	mov r2, #7
	bl StringNotEqualN
	cmp r0, #0
	bne _0224AE0C
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0224AE0C:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224AE10: .word 0x00002DB4

	thumb_func_start MOD11_0224AE14
MOD11_0224AE14: ; 0x0224AE14
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	mov r1, #0
	bl MOD11_022301D4
	add r4, r0, #0
	bl PlayerProfile_GetTrainerID
	add r6, r0, #0
	add r0, r4, #0
	bl PlayerProfile_GetTrainerGender
	add r7, r0, #0
	add r0, r4, #0
	bl PlayerProfile_GetNamePtr
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #0x8f
	add r2, sp, #0
	bl GetMonData
	add r0, r5, #0
	mov r1, #7
	mov r2, #0
	bl GetMonData
	cmp r6, r0
	bne _0224AE72
	add r0, r5, #0
	mov r1, #0x9c
	mov r2, #0
	bl GetMonData
	cmp r7, r0
	bne _0224AE72
	add r0, r4, #0
	add r1, sp, #0
	mov r2, #7
	bl StringNotEqualN
	cmp r0, #0
	bne _0224AE72
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0224AE72:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD11_0224AE78
MOD11_0224AE78: ; 0x0224AE78
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r4, #0
	add r7, r0, #0
	add r5, r1, #0
	str r4, [sp, #4]
	bl MOD11_0222FF84
	cmp r0, #0
	bgt _0224AE8E
	b _0224B232
_0224AE8E:
	ldr r0, _0224B1B8 ; =0x00002D66
	add r6, r5, r0
_0224AE92:
	ldr r0, _0224B1BC ; =0x000021EC
	add r1, r5, r4
	ldrb r1, [r1, r0]
	mov r0, #0x46
	lsl r0, r0, #2
	str r1, [r5, r0]
	ldr r3, [r5, r0]
	mov r0, #0xc0
	mul r0, r3
	add r2, r5, r0
	mov r0, #0xb5
	lsl r0, r0, #6
	ldrh r1, [r2, r0]
	ldr r0, _0224B1C0 ; =0x0000015F
	cmp r1, r0
	bne _0224AEC6
	ldr r0, _0224B1C4 ; =0x00002D8C
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _0224AEC6
	add r0, r5, #0
	add r1, r3, #0
	bl MOD11_02246D1C
	cmp r0, #0x3b
	beq _0224AEC8
_0224AEC6:
	b _0224B096
_0224AEC8:
	mov r0, #0xd
	str r0, [sp]
	add r0, r7, #0
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl MOD11_02246870
	cmp r0, #0
	bne _0224AEF0
	mov r0, #0x4c
	str r0, [sp]
	add r0, r7, #0
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl MOD11_02246870
	cmp r0, #0
	beq _0224AEF2
_0224AEF0:
	b _0224B04A
_0224AEF2:
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #0xf3
	tst r1, r0
	bne _0224AF4A
	mov r1, #0x46
	lsl r1, r1, #2
	ldr r2, [r5, r1]
	mov r1, #0xc0
	mul r1, r2
	ldr r2, _0224B1C8 ; =0x00002D64
	add r1, r5, r1
	ldrb r2, [r1, r2]
	cmp r2, #0
	beq _0224AF4A
	ldr r2, _0224B1CC ; =0x00002D65
	ldrb r2, [r1, r2]
	cmp r2, #0
	beq _0224AF4A
	ldr r3, _0224B1C8 ; =0x00002D64
	mov r2, #0
	mov r0, #0x46
	strb r2, [r1, r3]
	lsl r0, r0, #2
	ldr r4, [r5, r0]
	mov r1, #0xc0
	add r6, r4, #0
	mul r6, r1
	add r6, r5, r6
	add r4, r3, #1
	strb r2, [r6, r4]
	add r2, r3, #2
	ldr r0, [r5, r0]
	add r2, r5, r2
	add r3, r0, #0
	mul r3, r1
	ldrb r1, [r2, r3]
	mov r0, #0x1f
	bic r1, r0
	mov r0, #1
	strb r1, [r2, r3]
	str r0, [sp, #4]
	b _0224B232
_0224AF4A:
	mov r1, #0x30
	tst r1, r0
	beq _0224AF9E
	mov r1, #0x46
	lsl r1, r1, #2
	ldr r2, [r5, r1]
	mov r1, #0xc0
	mul r1, r2
	ldr r2, _0224B1C8 ; =0x00002D64
	add r1, r5, r1
	ldrb r2, [r1, r2]
	cmp r2, #0xa
	beq _0224AF9E
	ldr r2, _0224B1CC ; =0x00002D65
	ldrb r2, [r1, r2]
	cmp r2, #0xa
	beq _0224AF9E
	ldr r3, _0224B1C8 ; =0x00002D64
	mov r2, #0xa
	mov r0, #0x46
	strb r2, [r1, r3]
	lsl r0, r0, #2
	ldr r4, [r5, r0]
	mov r1, #0xc0
	add r6, r4, #0
	mul r6, r1
	add r6, r5, r6
	add r4, r3, #1
	strb r2, [r6, r4]
	add r2, r3, #2
	ldr r0, [r5, r0]
	add r2, r5, r2
	add r3, r0, #0
	mul r3, r1
	ldrb r1, [r2, r3]
	mov r0, #0x1f
	bic r1, r0
	mov r0, #1
	str r0, [sp, #4]
	orr r0, r1
	strb r0, [r2, r3]
	b _0224B232
_0224AF9E:
	mov r1, #3
	tst r1, r0
	beq _0224AFF4
	mov r1, #0x46
	lsl r1, r1, #2
	ldr r2, [r5, r1]
	mov r1, #0xc0
	mul r1, r2
	ldr r2, _0224B1C8 ; =0x00002D64
	add r1, r5, r1
	ldrb r2, [r1, r2]
	cmp r2, #0xb
	beq _0224AFF4
	ldr r2, _0224B1CC ; =0x00002D65
	ldrb r2, [r1, r2]
	cmp r2, #0xb
	beq _0224AFF4
	ldr r3, _0224B1C8 ; =0x00002D64
	mov r2, #0xb
	mov r0, #0x46
	strb r2, [r1, r3]
	lsl r0, r0, #2
	ldr r4, [r5, r0]
	mov r1, #0xc0
	add r6, r4, #0
	mul r6, r1
	add r6, r5, r6
	add r4, r3, #1
	strb r2, [r6, r4]
	add r2, r3, #2
	ldr r0, [r5, r0]
	add r2, r5, r2
	add r3, r0, #0
	mul r3, r1
	ldrb r1, [r2, r3]
	mov r0, #0x1f
	bic r1, r0
	mov r0, #2
	orr r0, r1
	strb r0, [r2, r3]
	mov r0, #1
	str r0, [sp, #4]
	b _0224B232
_0224AFF4:
	mov r1, #0xc0
	tst r0, r1
	beq _0224B096
	add r0, r1, #0
	add r0, #0x58
	ldr r1, [r5, r0]
	mov r0, #0xc0
	mul r0, r1
	ldr r1, _0224B1C8 ; =0x00002D64
	add r0, r5, r0
	ldrb r1, [r0, r1]
	cmp r1, #0xf
	beq _0224B096
	ldr r1, _0224B1CC ; =0x00002D65
	ldrb r1, [r0, r1]
	cmp r1, #0xf
	beq _0224B096
	ldr r3, _0224B1C8 ; =0x00002D64
	mov r2, #0xf
	strb r2, [r0, r3]
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r4, [r5, r0]
	mov r1, #0xc0
	add r6, r4, #0
	mul r6, r1
	add r6, r5, r6
	add r4, r3, #1
	strb r2, [r6, r4]
	add r2, r3, #2
	ldr r0, [r5, r0]
	add r2, r5, r2
	add r3, r0, #0
	mul r3, r1
	ldrb r1, [r2, r3]
	mov r0, #0x1f
	bic r1, r0
	mov r0, #3
	orr r0, r1
	strb r0, [r2, r3]
	mov r0, #1
	str r0, [sp, #4]
	b _0224B232
_0224B04A:
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	mov r0, #0xc0
	mul r0, r1
	ldr r1, _0224B1C8 ; =0x00002D64
	add r0, r5, r0
	ldrb r1, [r0, r1]
	cmp r1, #0
	beq _0224B096
	ldr r1, _0224B1CC ; =0x00002D65
	ldrb r1, [r0, r1]
	cmp r1, #0
	beq _0224B096
	ldr r3, _0224B1C8 ; =0x00002D64
	mov r2, #0
	strb r2, [r0, r3]
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r4, [r5, r0]
	mov r1, #0xc0
	add r6, r4, #0
	mul r6, r1
	add r6, r5, r6
	add r4, r3, #1
	strb r2, [r6, r4]
	add r2, r3, #2
	ldr r0, [r5, r0]
	add r2, r5, r2
	add r3, r0, #0
	mul r3, r1
	ldrb r1, [r2, r3]
	mov r0, #0x1f
	bic r1, r0
	mov r0, #1
	strb r1, [r2, r3]
	str r0, [sp, #4]
	b _0224B232
_0224B096:
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	mov r0, #0xc0
	mul r0, r1
	mov r1, #0xb5
	add r0, r5, r0
	lsl r1, r1, #6
	ldrh r2, [r0, r1]
	ldr r1, _0224B1D0 ; =0x000001A5
	cmp r2, r1
	bne _0224B1A2
	ldr r1, _0224B1C4 ; =0x00002D8C
	ldr r0, [r0, r1]
	cmp r0, #0
	beq _0224B1A2
	mov r0, #0xd
	str r0, [sp]
	add r0, r7, #0
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl MOD11_02246870
	cmp r0, #0
	bne _0224B182
	mov r0, #0x4c
	str r0, [sp]
	add r0, r7, #0
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl MOD11_02246870
	cmp r0, #0
	bne _0224B182
	mov r0, #6
	lsl r0, r0, #6
	ldr r2, [r5, r0]
	mov r0, #0xf3
	tst r0, r2
	bne _0224B10C
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0xc0
	add r3, r0, #0
	mul r3, r1
	ldrb r0, [r6, r3]
	lsl r1, r0, #0x1b
	lsr r1, r1, #0x1b
	cmp r1, #1
	bne _0224B10C
	mov r1, #0x1f
	bic r0, r1
	strb r0, [r6, r3]
	mov r0, #1
	str r0, [sp, #4]
	b _0224B232
_0224B10C:
	mov r0, #0x30
	tst r0, r2
	beq _0224B134
	mov r0, #0x46
	lsl r0, r0, #2
_0224B116:
	ldr r0, [r5, r0]
	mov r1, #0xc0
	add r3, r0, #0
	mul r3, r1
	ldrb r0, [r6, r3]
	lsl r1, r0, #0x1b
	lsr r1, r1, #0x1b
	bne _0224B134
	mov r1, #0x1f
	bic r0, r1
	mov r1, #1
	orr r0, r1
	str r1, [sp, #4]
	strb r0, [r6, r3]
	b _0224B232
_0224B134:
	mov r0, #3
	tst r0, r2
	beq _0224B15C
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0xc0
	add r3, r0, #0
	mul r3, r1
	ldrb r0, [r6, r3]
	lsl r1, r0, #0x1b
	lsr r1, r1, #0x1b
	cmp r1, #1
	bne _0224B15C
	mov r1, #0x1f
	bic r0, r1
	strb r0, [r6, r3]
	mov r0, #1
	str r0, [sp, #4]
	b _0224B232
_0224B15C:
	mov r0, #0xc0
	tst r0, r2
	beq _0224B1A2
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	mov r0, #0xc0
	mul r0, r1
	ldrb r2, [r6, r0]
	lsl r1, r2, #0x1b
	lsr r1, r1, #0x1b
	cmp r1, #1
	bne _0224B1A2
	mov r1, #0x1f
	bic r2, r1
	strb r2, [r6, r0]
	mov r0, #1
	str r0, [sp, #4]
	b _0224B232
_0224B182:
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	mov r0, #0xc0
	mul r0, r1
	ldrb r2, [r6, r0]
	lsl r1, r2, #0x1b
	lsr r1, r1, #0x1b
	cmp r1, #1
	bne _0224B1A2
	mov r1, #0x1f
	bic r2, r1
	strb r2, [r6, r0]
	mov r0, #1
	str r0, [sp, #4]
	b _0224B232
_0224B1A2:
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	mov r0, #0xc0
	mul r0, r1
	mov r1, #0xb5
	add r0, r5, r0
	lsl r1, r1, #6
	ldrh r2, [r0, r1]
	ldr r1, _0224B1D4 ; =0x000001ED
	b _0224B1D8
	.align 2, 0
_0224B1B8: .word 0x00002D66
_0224B1BC: .word 0x000021EC
_0224B1C0: .word 0x0000015F
_0224B1C4: .word 0x00002D8C
_0224B1C8: .word 0x00002D64
_0224B1CC: .word 0x00002D65
_0224B1D0: .word 0x000001A5
_0224B1D4: .word 0x000001ED
_0224B1D8:
	cmp r2, r1
	bne _0224B224
	ldr r1, _0224B238 ; =0x00002D8C
	ldr r1, [r0, r1]
	cmp r1, #0
	beq _0224B224
	ldr r1, _0224B23C ; =0x00002DB8
	mov r2, #5
	ldrh r0, [r0, r1]
	mov r1, #1
	bl GetItemAttr
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl GetArceusTypeByHeldItemEffect
	mov r1, #0x46
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	mov r2, #0xc0
	add r3, r1, #0
	mul r3, r2
	ldrb r1, [r6, r3]
	lsl r2, r1, #0x1b
	lsr r2, r2, #0x1b
	cmp r0, r2
	beq _0224B224
	mov r2, #0x1f
	lsl r0, r0, #0x18
	bic r1, r2
	lsr r2, r0, #0x18
	mov r0, #0x1f
	and r0, r2
	orr r0, r1
	strb r0, [r6, r3]
	mov r0, #1
	str r0, [sp, #4]
	b _0224B232
_0224B224:
	add r0, r7, #0
	add r4, r4, #1
	bl MOD11_0222FF84
	cmp r4, r0
	bge _0224B232
	b _0224AE92
_0224B232:
	ldr r0, [sp, #4]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224B238: .word 0x00002D8C
_0224B23C: .word 0x00002DB8

	thumb_func_start MOD11_0224B240
MOD11_0224B240: ; 0x0224B240
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp, #4]
	str r1, [sp]
	mov r7, #0
	bl MOD11_0222FF84
	cmp r0, #0
	ble _0224B282
	ldr r5, [sp]
	ldr r4, _0224B288 ; =0x0000312C
_0224B256:
	mov r1, #0
_0224B258:
	add r0, r5, r1
	strb r1, [r0, r4]
	add r1, r1, #1
	cmp r1, #6
	blt _0224B258
	ldr r1, [sp]
	ldr r0, [sp, #4]
	add r3, r1, #0
	add r6, r3, r7
	ldr r3, _0224B28C ; =0x0000219C
	add r2, r7, #0
	ldrb r3, [r6, r3]
	bl MOD11_0224B290
	ldr r0, [sp, #4]
	add r5, r5, #6
	add r7, r7, #1
	bl MOD11_0222FF84
	cmp r7, r0
	blt _0224B256
_0224B282:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224B288: .word 0x0000312C
_0224B28C: .word 0x0000219C

	thumb_func_start MOD11_0224B290
MOD11_0224B290: ; 0x0224B290
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r6, r1, #0
	add r5, r2, #0
	add r4, r3, #0
	bl MOD11_0222FF74
	mov r1, #2
	tst r1, r0
	beq _0224B2AA
	mov r1, #0x18
	tst r1, r0
	beq _0224B2BE
_0224B2AA:
	mov r1, #0x10
	tst r0, r1
	beq _0224B2E2
	add r0, r7, #0
	add r1, r5, #0
	bl MOD11_02230260
	mov r1, #1
	tst r0, r1
	bne _0224B2E2
_0224B2BE:
	add r0, r7, #0
	add r1, r5, #0
	bl MOD11_02230260
	cmp r0, #4
	beq _0224B2D6
	add r0, r7, #0
	add r1, r5, #0
	bl MOD11_02230260
	cmp r0, #5
	bne _0224B2DA
_0224B2D6:
	mov r1, #1
	b _0224B2DC
_0224B2DA:
	mov r1, #0
_0224B2DC:
	mov r0, #1
	and r5, r0
	b _0224B2E4
_0224B2E2:
	mov r1, #0
_0224B2E4:
	mov r2, #6
	mul r2, r5
	ldr r3, _0224B30C ; =0x0000312C
	mov r0, #0
	add r7, r6, r2
_0224B2EE:
	ldrb r5, [r7, r3]
	cmp r4, r5
	beq _0224B2FC
	add r0, r0, #1
	add r7, r7, #1
	cmp r0, #6
	blt _0224B2EE
_0224B2FC:
	ldr r3, _0224B30C ; =0x0000312C
	add r3, r6, r3
	add r4, r3, r2
	ldrb r3, [r4, r1]
	ldrb r2, [r4, r0]
	strb r2, [r4, r1]
	strb r3, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224B30C: .word 0x0000312C

	thumb_func_start MOD11_0224B310
MOD11_0224B310: ; 0x0224B310
	push {r4, r5, r6, r7, lr}
	sub sp, #0x8c
	str r0, [sp, #4]
	ldr r0, [sp, #0xa0]
	add r5, r1, #0
	str r0, [sp, #0xa0]
	ldr r0, [sp, #0xb4]
	str r2, [sp, #8]
	str r0, [sp, #0xb4]
	mov r0, #0
	str r0, [sp, #0x84]
	ldr r0, [sp, #0xb4]
	str r3, [sp, #0xc]
	cmp r0, #1
	beq _0224B334
	bhi _0224B334
	bl GF_AssertFail
_0224B334:
	add r0, sp, #0x90
	ldrb r0, [r0, #0x1c]
	mov r2, #1
	mov r3, #0
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	bl MOD11_02243420
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x7c]
	add r0, sp, #0xb0
	ldrb r0, [r0]
	mov r2, #2
	mov r3, #0
	str r0, [sp, #0x20]
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	bl MOD11_02243420
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x78]
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	mov r2, #4
	mov r3, #0
	bl MOD11_02243420
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x74]
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	mov r2, #5
	mov r3, #0
	bl MOD11_02243420
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	mov r2, #0x13
	mov r3, #0
	bl MOD11_02243420
	sub r0, r0, #6
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [sp, #0x70]
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	mov r2, #0x14
	mov r3, #0
	bl MOD11_02243420
	sub r0, r0, #6
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [sp, #0x6c]
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	mov r2, #0x16
	mov r3, #0
	bl MOD11_02243420
	sub r0, r0, #6
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [sp, #0x68]
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	mov r2, #0x17
	mov r3, #0
	bl MOD11_02243420
	sub r0, r0, #6
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [sp, #0x64]
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	mov r2, #0x2b
	mov r3, #0
	bl MOD11_02243420
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r2, #0
	str r0, [sp, #0x60]
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	add r3, r2, #0
	bl MOD11_02243420
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #0
	str r0, [sp, #0x58]
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	add r3, r2, #0
	bl MOD11_02243420
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x54]
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	mov r2, #0x2f
	mov r3, #0
	bl MOD11_02243420
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #0x50]
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	mov r2, #0x2f
	mov r3, #0
	bl MOD11_02243420
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	mov r2, #0x30
	mov r3, #0
	bl MOD11_02243420
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4c]
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	mov r2, #0x30
	mov r3, #0
	bl MOD11_02243420
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	mov r2, #0x34
	mov r3, #0
	bl MOD11_02243420
	str r0, [sp, #0x48]
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	mov r2, #0x34
	mov r3, #0
	bl MOD11_02243420
	str r0, [sp, #0x44]
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	bl MOD11_02246D1C
	add r7, r0, #0
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	bl MOD11_02246D1C
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	mov r2, #0x1d
	mov r3, #0
	bl MOD11_02243420
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x40]
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	mov r2, #0x1d
	mov r3, #0
	bl MOD11_02243420
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x3c]
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	mov r2, #0x1b
	mov r3, #0
	bl MOD11_02243420
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	mov r2, #0x1b
	mov r3, #0
	bl MOD11_02243420
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x38]
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	mov r2, #0x1c
	mov r3, #0
	bl MOD11_02243420
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	mov r2, #0x1c
	mov r3, #0
	bl MOD11_02243420
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x34]
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	bl MOD11_02249B4C
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #1
	bl MOD11_0224C12C
	str r0, [sp, #0x30]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #2
	bl MOD11_0224C12C
	str r0, [sp, #0x2c]
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	bl MOD11_02249B4C
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #1
	bl MOD11_0224C12C
	str r0, [sp, #0x28]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #2
	bl MOD11_0224C12C
	ldr r0, [sp, #4]
	bl MOD11_0222FF74
	str r0, [sp, #0x5c]
	add r0, sp, #0x90
	ldrh r4, [r0, #0x14]
	cmp r4, #0
	bne _0224B534
	ldr r0, [sp, #8]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _0224B754 ; =0x000003E1
	ldrb r4, [r1, r0]
_0224B534:
	cmp r7, #0x60
	bne _0224B53C
	mov r6, #0
	b _0224B558
_0224B53C:
	add r0, sp, #0x90
	ldrb r1, [r0, #0x18]
	cmp r1, #0
	bne _0224B550
	ldr r0, [sp, #8]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _0224B758 ; =0x000003E2
	ldrb r6, [r1, r0]
	b _0224B558
_0224B550:
	mov r0, #0x3f
	and r0, r1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
_0224B558:
	ldr r0, _0224B75C ; =0x00002158
	ldr r0, [r5, r0]
	cmp r0, #0xa
	bge _0224B564
	bl GF_AssertFail
_0224B564:
	ldr r0, _0224B75C ; =0x00002158
	mov r1, #0xa
	ldr r0, [r5, r0]
	mul r0, r4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, sp, #0x90
	ldrb r0, [r0, #0x1c]
	mov r1, #0xc0
	mul r1, r0
	add r2, r5, r1
	mov r1, #0xb7
	lsl r1, r1, #6
	ldr r2, [r2, r1]
	mov r1, #2
	lsl r1, r1, #8
	tst r1, r2
	beq _0224B594
	cmp r6, #0xd
	bne _0224B594
	lsl r1, r4, #0x11
	lsr r4, r1, #0x10
_0224B594:
	lsl r0, r0, #6
	add r1, r5, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	beq _0224B5B2
	mov r0, #0xf
	mul r0, r4
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0224B5B2:
	cmp r7, #0x65
	bne _0224B5CE
	ldr r0, [sp, #8]
	cmp r0, #0xa5
	beq _0224B5CE
	cmp r4, #0x3c
	bhi _0224B5CE
	mov r0, #0xf
	mul r0, r4
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0224B5CE:
	ldr r0, [sp, #8]
	lsl r0, r0, #4
	str r0, [sp, #0x18]
	add r1, r5, r0
	mov r0, #0x3e
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	cmp r7, #0x25
	str r0, [sp, #0x80]
	beq _0224B5E6
	cmp r7, #0x4a
	bne _0224B5EE
_0224B5E6:
	ldr r0, [sp, #0x7c]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x10
	str r0, [sp, #0x7c]
_0224B5EE:
	cmp r7, #0x70
	bne _0224B61C
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #3
	mov r3, #0
	bl MOD11_0224C474
	str r0, [sp, #0x88]
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	mov r2, #0x59
	mov r3, #0
	bl MOD11_02243420
	ldr r1, [sp, #0x88]
	sub r0, r1, r0
	cmp r0, #5
	bge _0224B61C
	ldr r0, [sp, #0x7c]
	lsl r0, r0, #0xf
	lsr r0, r0, #0x10
	str r0, [sp, #0x7c]
_0224B61C:
	ldr r3, _0224B760 ; =MOD11_0225E336
	mov r2, #0
_0224B620:
	ldrb r1, [r3]
	ldr r0, [sp, #0x30]
	cmp r0, r1
	bne _0224B640
	ldrb r0, [r3, #1]
	cmp r6, r0
	bne _0224B640
	ldr r0, [sp, #0x2c]
	mov r1, #0x64
	add r0, #0x64
	mul r0, r4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	b _0224B648
_0224B640:
	add r2, r2, #1
	add r3, r3, #2
	cmp r2, #0x21
	blo _0224B620
_0224B648:
	ldr r0, [sp, #0x30]
	cmp r0, #0x36
	bne _0224B660
	ldr r1, [sp, #0x7c]
	mov r0, #0x96
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x7c]
_0224B660:
	ldr r0, [sp, #0x30]
	cmp r0, #0x7c
	bne _0224B678
	ldr r1, [sp, #0x74]
	mov r0, #0x96
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x74]
_0224B678:
	ldr r0, [sp, #0x30]
	cmp r0, #0x3b
	bne _0224B6A6
	ldr r0, [sp, #0x5c]
	mov r1, #0x80
	tst r0, r1
	bne _0224B6A6
	ldr r1, _0224B764 ; =0x0000FE84
	ldr r0, [sp, #0x58]
	add r0, r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #1
	bhi _0224B6A6
	ldr r1, [sp, #0x74]
	mov r0, #0x96
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x74]
_0224B6A6:
	ldr r0, [sp, #0x28]
	cmp r0, #0x3b
	bne _0224B6D4
	ldr r0, [sp, #0x5c]
	mov r1, #0x80
	tst r0, r1
	bne _0224B6D4
	ldr r1, _0224B764 ; =0x0000FE84
	ldr r0, [sp, #0x54]
	add r0, r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #1
	bhi _0224B6D4
	ldr r1, [sp, #0x10]
	mov r0, #0x96
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
_0224B6D4:
	ldr r0, [sp, #0x30]
	cmp r0, #0x3c
	bne _0224B6EA
	ldr r1, _0224B768 ; =0x0000016E
	ldr r0, [sp, #0x58]
	cmp r0, r1
	bne _0224B6EA
	ldr r0, [sp, #0x74]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x10
	str r0, [sp, #0x74]
_0224B6EA:
	ldr r0, [sp, #0x28]
	cmp r0, #0x3d
	bne _0224B700
	ldr r1, _0224B768 ; =0x0000016E
	ldr r0, [sp, #0x54]
	cmp r0, r1
	bne _0224B700
	ldr r0, [sp, #0x10]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
_0224B700:
	ldr r0, [sp, #0x30]
	cmp r0, #0x46
	bne _0224B710
	ldr r0, [sp, #0x58]
	cmp r0, #0x19
	bne _0224B710
	lsl r0, r4, #0x11
	lsr r4, r0, #0x10
_0224B710:
	ldr r0, [sp, #0x28]
	cmp r0, #0x59
	bne _0224B724
	ldr r0, [sp, #0x54]
	cmp r0, #0x84
	bne _0224B724
	ldr r0, [sp, #0x78]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x10
	str r0, [sp, #0x78]
_0224B724:
	ldr r0, [sp, #0x30]
	cmp r0, #0x5a
	bne _0224B740
	ldr r1, _0224B76C ; =0x0000FF98
	ldr r0, [sp, #0x58]
	add r0, r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #1
	bhi _0224B740
	ldr r0, [sp, #0x7c]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x10
	str r0, [sp, #0x7c]
_0224B740:
	ldr r0, [sp, #0x30]
	cmp r0, #2
	bne _0224B78A
	cmp r6, #0x10
	beq _0224B74E
	cmp r6, #8
	bne _0224B78A
_0224B74E:
	ldr r1, _0224B770 ; =0x000001E3
	b _0224B774
	nop
_0224B754: .word 0x000003E1
_0224B758: .word 0x000003E2
_0224B75C: .word 0x00002158
_0224B760: .word MOD11_0225E336
_0224B764: .word 0x0000FE84
_0224B768: .word 0x0000016E
_0224B76C: .word 0x0000FF98
_0224B770: .word 0x000001E3
_0224B774:
	ldr r0, [sp, #0x58]
	cmp r0, r1
	bne _0224B78A
	ldr r0, [sp, #0x2c]
	mov r1, #0x64
	add r0, #0x64
	mul r0, r4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0224B78A:
	ldr r0, [sp, #0x30]
	cmp r0, #3
	bne _0224B7B2
	cmp r6, #0x10
	beq _0224B798
	cmp r6, #0xb
	bne _0224B7B2
_0224B798:
	mov r1, #0x79
	ldr r0, [sp, #0x58]
	lsl r1, r1, #2
	cmp r0, r1
	bne _0224B7B2
	ldr r0, [sp, #0x2c]
	mov r1, #0x64
	add r0, #0x64
	mul r0, r4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0224B7B2:
	ldr r0, [sp, #0x30]
	cmp r0, #0x5d
	bne _0224B7CE
	ldr r0, [sp, #0x80]
	cmp r0, #0
	bne _0224B7CE
	ldr r0, [sp, #0x2c]
	mov r1, #0x64
	add r0, #0x64
	mul r0, r4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0224B7CE:
	ldr r0, [sp, #0x30]
	cmp r0, #0x5e
	bne _0224B7EC
	ldr r0, [sp, #0x80]
	cmp r0, #1
	bne _0224B7EC
	ldr r0, [sp, #0x2c]
	mov r1, #0x64
	add r0, #0x64
	str r0, [sp, #0x2c]
	mul r0, r4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0224B7EC:
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x20]
	add r0, r5, #0
	mov r3, #0x2f
	bl MOD11_02246D84
	cmp r0, #1
	bne _0224B808
	cmp r6, #0xa
	beq _0224B804
	cmp r6, #0xf
	bne _0224B808
_0224B804:
	lsl r0, r4, #0xf
	lsr r4, r0, #0x10
_0224B808:
	cmp r7, #0x37
	bne _0224B81E
	ldr r1, [sp, #0x7c]
	mov r0, #0x96
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x7c]
_0224B81E:
	cmp r7, #0x3e
	bne _0224B83A
	ldr r0, [sp, #0x48]
	cmp r0, #0
	beq _0224B83A
	ldr r1, [sp, #0x7c]
	mov r0, #0x96
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x7c]
_0224B83A:
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x20]
	add r0, r5, #0
	mov r3, #0x3f
	bl MOD11_02246D84
	cmp r0, #1
	bne _0224B862
	ldr r0, [sp, #0x44]
	cmp r0, #0
	beq _0224B862
	ldr r1, [sp, #0x78]
	mov r0, #0x96
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x78]
_0224B862:
	cmp r7, #0x39
	bne _0224B88C
	mov r0, #0x3a
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r3, [sp, #0x24]
	add r1, r5, #0
	mov r2, #1
	bl MOD11_02246870
	cmp r0, #0
	beq _0224B88C
	ldr r1, [sp, #0x74]
	mov r0, #0x96
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x74]
_0224B88C:
	cmp r7, #0x3a
	bne _0224B8B6
	mov r0, #0x39
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r3, [sp, #0x24]
	add r1, r5, #0
	mov r2, #1
	bl MOD11_02246870
	cmp r0, #0
	beq _0224B8B6
	ldr r1, [sp, #0x74]
	mov r0, #0x96
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x74]
_0224B8B6:
	cmp r6, #0xd
	bne _0224B8CE
	mov r2, #1
	ldr r0, [sp, #4]
	add r1, r5, #0
	lsl r2, r2, #0x10
	bl MOD11_02247238
	cmp r0, #0
	beq _0224B8CE
	lsl r0, r4, #0xf
	lsr r4, r0, #0x10
_0224B8CE:
	cmp r6, #0xa
	bne _0224B8E6
	mov r2, #2
	ldr r0, [sp, #4]
	add r1, r5, #0
	lsl r2, r2, #0x10
	bl MOD11_02247238
	cmp r0, #0
	beq _0224B8E6
	lsl r0, r4, #0xf
	lsr r4, r0, #0x10
_0224B8E6:
	cmp r6, #0xc
	bne _0224B90A
	cmp r7, #0x41
	bne _0224B90A
	ldr r0, [sp, #0x4c]
	mov r1, #3
	bl _s32_div_f
	ldr r1, [sp, #0x50]
	cmp r1, r0
	bgt _0224B90A
	mov r0, #0x96
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0224B90A:
	cmp r6, #0xa
	bne _0224B92E
	cmp r7, #0x42
	bne _0224B92E
	ldr r0, [sp, #0x4c]
	mov r1, #3
	bl _s32_div_f
	ldr r1, [sp, #0x50]
	cmp r1, r0
	bgt _0224B92E
	mov r0, #0x96
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0224B92E:
	cmp r6, #0xb
	bne _0224B952
	cmp r7, #0x43
	bne _0224B952
	ldr r0, [sp, #0x4c]
	mov r1, #3
	bl _s32_div_f
	ldr r1, [sp, #0x50]
	cmp r1, r0
	bgt _0224B952
	mov r0, #0x96
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0224B952:
	cmp r6, #6
	bne _0224B976
	cmp r7, #0x44
	bne _0224B976
	ldr r0, [sp, #0x4c]
	mov r1, #3
	bl _s32_div_f
	ldr r1, [sp, #0x50]
	cmp r1, r0
	bgt _0224B976
	mov r0, #0x96
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0224B976:
	cmp r6, #0xa
	bne _0224B98E
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x20]
	add r0, r5, #0
	mov r3, #0x55
	bl MOD11_02246D84
	cmp r0, #1
	bne _0224B98E
	lsl r0, r4, #0xf
	lsr r4, r0, #0x10
_0224B98E:
	cmp r6, #0xa
	bne _0224B9B0
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x20]
	add r0, r5, #0
	mov r3, #0x57
	bl MOD11_02246D84
	cmp r0, #1
	bne _0224B9B0
	mov r0, #0x7d
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0224B9B0:
	cmp r7, #0x56
	bne _0224B9F0
	ldr r0, [sp, #0x70]
	mov r1, #5
	lsl r0, r0, #0x19
	asr r0, r0, #0x18
	str r0, [sp, #0x70]
	ldr r0, [sp, #0x70]
	mvn r1, r1
	cmp r0, r1
	bge _0224B9C8
	str r1, [sp, #0x70]
_0224B9C8:
	ldr r0, [sp, #0x70]
	cmp r0, #6
	ble _0224B9D2
	mov r0, #6
	str r0, [sp, #0x70]
_0224B9D2:
	ldr r0, [sp, #0x68]
	mov r1, #5
	lsl r0, r0, #0x19
	asr r0, r0, #0x18
	str r0, [sp, #0x68]
	ldr r0, [sp, #0x68]
	mvn r1, r1
	cmp r0, r1
	bge _0224B9E6
	str r1, [sp, #0x68]
_0224B9E6:
	ldr r0, [sp, #0x68]
	cmp r0, #6
	ble _0224B9F0
	mov r0, #6
	str r0, [sp, #0x68]
_0224B9F0:
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x20]
	add r0, r5, #0
	mov r3, #0x56
	bl MOD11_02246D84
	cmp r0, #1
	bne _0224BA3C
	ldr r0, [sp, #0x6c]
	mov r1, #5
	lsl r0, r0, #0x19
	asr r0, r0, #0x18
	str r0, [sp, #0x6c]
	ldr r0, [sp, #0x6c]
	mvn r1, r1
	cmp r0, r1
	bge _0224BA14
	str r1, [sp, #0x6c]
_0224BA14:
	ldr r0, [sp, #0x6c]
	cmp r0, #6
	ble _0224BA1E
	mov r0, #6
	str r0, [sp, #0x6c]
_0224BA1E:
	ldr r0, [sp, #0x64]
	mov r1, #5
	lsl r0, r0, #0x19
	asr r0, r0, #0x18
	str r0, [sp, #0x64]
	ldr r0, [sp, #0x64]
	mvn r1, r1
	cmp r0, r1
	bge _0224BA32
	str r1, [sp, #0x64]
_0224BA32:
	ldr r0, [sp, #0x64]
	cmp r0, #6
	ble _0224BA3C
	mov r0, #6
	str r0, [sp, #0x64]
_0224BA3C:
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x20]
	add r0, r5, #0
	mov r3, #0x6d
	bl MOD11_02246D84
	cmp r0, #1
	bne _0224BA52
	mov r0, #0
	str r0, [sp, #0x70]
	str r0, [sp, #0x68]
_0224BA52:
	cmp r7, #0x6d
	bne _0224BA5C
	mov r0, #0
	str r0, [sp, #0x6c]
	str r0, [sp, #0x64]
_0224BA5C:
	ldr r0, [sp, #0x70]
	add r0, r0, #6
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [sp, #0x70]
	ldr r0, [sp, #0x6c]
	add r0, r0, #6
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [sp, #0x6c]
	ldr r0, [sp, #0x68]
	add r0, r0, #6
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [sp, #0x68]
	ldr r0, [sp, #0x64]
	add r0, r0, #6
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	str r0, [sp, #0x64]
	cmp r7, #0x4f
	bne _0224BAAA
	ldr r1, [sp, #0x40]
	ldr r0, [sp, #0x3c]
	cmp r1, r0
	bne _0224BAAA
	add r0, r1, #0
	cmp r0, #2
	beq _0224BAAA
	ldr r0, [sp, #0x3c]
	cmp r0, #2
	beq _0224BAAA
	mov r0, #0x7d
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0224BAAA:
	cmp r7, #0x4f
	bne _0224BAD0
	ldr r1, [sp, #0x40]
	ldr r0, [sp, #0x3c]
	cmp r1, r0
	beq _0224BAD0
	add r0, r1, #0
	cmp r0, #2
	beq _0224BAD0
	ldr r0, [sp, #0x3c]
	cmp r0, #2
	beq _0224BAD0
	mov r0, #0x4b
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0224BAD0:
	ldr r2, _0224BDDC ; =MOD11_0225E2BA
	mov r3, #0
_0224BAD4:
	ldrh r1, [r2]
	ldr r0, [sp, #8]
	cmp r0, r1
	bne _0224BAF0
	cmp r7, #0x59
	bne _0224BAF0
	mov r0, #0xc
	mul r0, r4
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	b _0224BAF8
_0224BAF0:
	add r3, r3, #1
	add r2, r2, #2
	cmp r3, #0xf
	blo _0224BAD4
_0224BAF8:
	mov r0, #0xd
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl MOD11_02246870
	cmp r0, #0
	bne _0224BBCA
	mov r0, #0x4c
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl MOD11_02246870
	cmp r0, #0
	bne _0224BBCA
	ldr r0, [sp, #0xa0]
	mov r1, #0x30
	and r0, r1
	str r0, [sp, #0x1c]
	beq _0224BB40
	cmp r7, #0x5e
	bne _0224BB40
	ldr r1, [sp, #0x74]
	mov r0, #0xf
	mul r0, r1
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x74]
_0224BB40:
	ldr r0, [sp, #0xa0]
	mov r1, #0xc
	tst r0, r1
	beq _0224BB66
	ldr r0, [sp, #0x38]
	cmp r0, #5
	beq _0224BB54
	ldr r0, [sp, #0x34]
	cmp r0, #5
	bne _0224BB66
_0224BB54:
	ldr r1, [sp, #0x10]
	mov r0, #0xf
	mul r0, r1
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
_0224BB66:
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	beq _0224BB92
	mov r0, #0x7a
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r3, [sp, #0x24]
	add r1, r5, #0
	mov r2, #1
	bl MOD11_02246870
	cmp r0, #0
	beq _0224BB92
	ldr r1, [sp, #0x7c]
	mov r0, #0xf
	mul r0, r1
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x7c]
_0224BB92:
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	beq _0224BBCA
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	bl MOD11_02246D1C
	cmp r0, #0x68
	beq _0224BBCA
	mov r0, #0x7a
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r3, [sp, #0x20]
	add r1, r5, #0
	mov r2, #1
	bl MOD11_02246870
	cmp r0, #0
	beq _0224BBCA
	ldr r1, [sp, #0x10]
	mov r0, #0xf
	mul r0, r1
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
_0224BBCA:
	ldr r0, [sp, #0x18]
	add r1, r5, r0
	ldr r0, _0224BDE0 ; =0x000003DE
	ldrh r0, [r1, r0]
	str r0, [sp, #0x14]
	cmp r0, #7
	bne _0224BBE0
	ldr r0, [sp, #0x78]
	lsl r0, r0, #0xf
	lsr r0, r0, #0x10
	str r0, [sp, #0x78]
_0224BBE0:
	ldr r0, [sp, #0x80]
	cmp r0, #0
	bne _0224BCE2
	ldr r0, [sp, #0xb4]
	cmp r0, #1
	bls _0224BC0E
	ldr r0, [sp, #0x70]
	cmp r0, #6
	ble _0224BC08
	lsl r1, r0, #1
	ldr r0, _0224BDE4 ; =MOD11_0225E284
	ldr r2, [sp, #0x7c]
	ldrb r0, [r0, r1]
	mul r0, r2
	ldr r2, _0224BDE8 ; =MOD11_0225E285
	ldrb r1, [r2, r1]
	bl _s32_div_f
	str r0, [sp, #0x84]
	b _0224BC24
_0224BC08:
	ldr r0, [sp, #0x7c]
	str r0, [sp, #0x84]
	b _0224BC24
_0224BC0E:
	ldr r0, [sp, #0x70]
	ldr r2, [sp, #0x7c]
	lsl r1, r0, #1
	ldr r0, _0224BDE4 ; =MOD11_0225E284
	ldrb r0, [r0, r1]
	mul r0, r2
	ldr r2, _0224BDE8 ; =MOD11_0225E285
	ldrb r1, [r2, r1]
	bl _s32_div_f
	str r0, [sp, #0x84]
_0224BC24:
	ldr r0, [sp, #0x84]
	add r1, r0, #0
	ldr r0, [sp, #0x60]
	mul r1, r4
	str r1, [sp, #0x84]
	lsl r0, r0, #1
	mov r1, #5
	bl _s32_div_f
	add r1, r0, #2
	ldr r0, [sp, #0x84]
	mul r1, r0
	ldr r0, [sp, #0xb4]
	str r1, [sp, #0x84]
	cmp r0, #1
	bls _0224BC60
	ldr r0, [sp, #0x6c]
	cmp r0, #6
	bge _0224BC76
	lsl r1, r0, #1
	ldr r0, _0224BDE4 ; =MOD11_0225E284
	ldr r2, [sp, #0x78]
	ldrb r0, [r0, r1]
	mul r0, r2
	ldr r2, _0224BDE8 ; =MOD11_0225E285
	ldrb r1, [r2, r1]
	bl _s32_div_f
	str r0, [sp, #0x78]
	b _0224BC76
_0224BC60:
	ldr r0, [sp, #0x6c]
	ldr r2, [sp, #0x78]
	lsl r1, r0, #1
	ldr r0, _0224BDE4 ; =MOD11_0225E284
	ldrb r0, [r0, r1]
	mul r0, r2
	ldr r2, _0224BDE8 ; =MOD11_0225E285
	ldrb r1, [r2, r1]
	bl _s32_div_f
	str r0, [sp, #0x78]
_0224BC76:
	ldr r0, [sp, #0x84]
	ldr r1, [sp, #0x78]
	bl _s32_div_f
	mov r1, #0x32
	bl _s32_div_f
	str r0, [sp, #0x84]
	ldr r0, [sp, #0x48]
	mov r1, #0x10
	tst r0, r1
	beq _0224BC9C
	cmp r7, #0x3e
	beq _0224BC9C
	ldr r0, [sp, #0x84]
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r0, r1, #1
	str r0, [sp, #0x84]
_0224BC9C:
	ldr r0, [sp, #0xc]
	mov r2, #1
	tst r0, r2
	beq _0224BCB0
	ldr r0, [sp, #0xb4]
	cmp r0, #1
	bne _0224BCB0
	ldr r0, [sp, #0x14]
	cmp r0, #0xba
	bne _0224BCB2
_0224BCB0:
	b _0224BDC8
_0224BCB2:
	ldr r0, [sp, #0x5c]
	mov r1, #2
	tst r0, r1
	beq _0224BCD6
	ldr r0, [sp, #4]
	ldr r3, [sp, #0x20]
	add r1, r5, #0
	bl MOD11_022467AC
	cmp r0, #2
	bne _0224BCD6
	ldr r0, [sp, #0x84]
	mov r1, #3
	lsl r0, r0, #1
	bl _s32_div_f
	str r0, [sp, #0x84]
	b _0224BDC8
_0224BCD6:
	ldr r0, [sp, #0x84]
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r0, r1, #1
	str r0, [sp, #0x84]
	b _0224BDC8
_0224BCE2:
	cmp r0, #1
	bne _0224BDC8
	ldr r0, [sp, #0xb4]
	cmp r0, #1
	bls _0224BD0E
	ldr r0, [sp, #0x68]
	cmp r0, #6
	ble _0224BD08
	lsl r1, r0, #1
	ldr r0, _0224BDE4 ; =MOD11_0225E284
	ldr r2, [sp, #0x74]
	ldrb r0, [r0, r1]
	mul r0, r2
	ldr r2, _0224BDE8 ; =MOD11_0225E285
	ldrb r1, [r2, r1]
	bl _s32_div_f
	str r0, [sp, #0x84]
	b _0224BD24
_0224BD08:
	ldr r0, [sp, #0x74]
	str r0, [sp, #0x84]
	b _0224BD24
_0224BD0E:
	ldr r0, [sp, #0x68]
	ldr r2, [sp, #0x74]
	lsl r1, r0, #1
	ldr r0, _0224BDE4 ; =MOD11_0225E284
	ldrb r0, [r0, r1]
	mul r0, r2
	ldr r2, _0224BDE8 ; =MOD11_0225E285
	ldrb r1, [r2, r1]
	bl _s32_div_f
	str r0, [sp, #0x84]
_0224BD24:
	ldr r0, [sp, #0x84]
	add r1, r0, #0
	ldr r0, [sp, #0x60]
	mul r1, r4
	str r1, [sp, #0x84]
	lsl r0, r0, #1
	mov r1, #5
	bl _s32_div_f
	add r1, r0, #2
	ldr r0, [sp, #0x84]
	mul r1, r0
	ldr r0, [sp, #0xb4]
	str r1, [sp, #0x84]
	cmp r0, #1
	bls _0224BD60
	ldr r0, [sp, #0x64]
	cmp r0, #6
	bge _0224BD76
	lsl r1, r0, #1
	ldr r0, _0224BDE4 ; =MOD11_0225E284
	ldr r2, [sp, #0x10]
	ldrb r0, [r0, r1]
	mul r0, r2
	ldr r2, _0224BDE8 ; =MOD11_0225E285
	ldrb r1, [r2, r1]
	bl _s32_div_f
	str r0, [sp, #0x10]
	b _0224BD76
_0224BD60:
	ldr r0, [sp, #0x64]
	ldr r2, [sp, #0x10]
	lsl r1, r0, #1
	ldr r0, _0224BDE4 ; =MOD11_0225E284
	ldrb r0, [r0, r1]
	mul r0, r2
	ldr r2, _0224BDE8 ; =MOD11_0225E285
	ldrb r1, [r2, r1]
	bl _s32_div_f
	str r0, [sp, #0x10]
_0224BD76:
	ldr r0, [sp, #0x84]
	ldr r1, [sp, #0x10]
	bl _s32_div_f
	mov r1, #0x32
	bl _s32_div_f
	str r0, [sp, #0x84]
	ldr r0, [sp, #0xc]
	mov r1, #2
	tst r0, r1
	beq _0224BDC8
	ldr r0, [sp, #0xb4]
	cmp r0, #1
	bne _0224BDC8
	ldr r0, [sp, #0x14]
	cmp r0, #0xba
	beq _0224BDC8
	ldr r0, [sp, #0x5c]
	tst r0, r1
	beq _0224BDBE
	ldr r0, [sp, #4]
	ldr r3, [sp, #0x20]
	add r1, r5, #0
	mov r2, #1
	bl MOD11_022467AC
	cmp r0, #2
	bne _0224BDBE
	ldr r0, [sp, #0x84]
	mov r1, #3
	lsl r0, r0, #1
	bl _s32_div_f
	str r0, [sp, #0x84]
	b _0224BDC8
_0224BDBE:
	ldr r0, [sp, #0x84]
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r0, r1, #1
	str r0, [sp, #0x84]
_0224BDC8:
	ldr r0, [sp, #0x5c]
	mov r1, #2
	add r4, r0, #0
	and r4, r1
	beq _0224BE16
	ldr r0, [sp, #0x18]
	add r1, r5, r0
	ldr r0, _0224BDEC ; =0x000003E6
	b _0224BDF0
	nop
_0224BDDC: .word MOD11_0225E2BA
_0224BDE0: .word 0x000003DE
_0224BDE4: .word MOD11_0225E284
_0224BDE8: .word MOD11_0225E285
_0224BDEC: .word 0x000003E6
_0224BDF0:
	ldrh r0, [r1, r0]
	cmp r0, #4
	bne _0224BE16
	ldr r0, [sp, #4]
	ldr r3, [sp, #0x20]
	add r1, r5, #0
	mov r2, #1
	bl MOD11_022467AC
	cmp r0, #2
	bne _0224BE16
	ldr r0, [sp, #0x84]
	lsl r1, r0, #1
	add r1, r0, r1
	asr r0, r1, #1
	lsr r0, r0, #0x1e
	add r0, r1, r0
	asr r0, r0, #2
	str r0, [sp, #0x84]
_0224BE16:
	cmp r4, #0
	beq _0224BE46
	ldr r0, [sp, #0x18]
	add r1, r5, r0
	ldr r0, _0224BF08 ; =0x000003E6
	ldrh r0, [r1, r0]
	cmp r0, #8
	bne _0224BE46
	ldr r0, [sp, #4]
	ldr r3, [sp, #0x20]
	add r1, r5, #0
	mov r2, #0
	bl MOD11_022467AC
	cmp r0, #2
	blo _0224BE46
	ldr r0, [sp, #0x84]
	lsl r1, r0, #1
	add r1, r0, r1
	asr r0, r1, #1
	lsr r0, r0, #0x1e
	add r0, r1, r0
	asr r0, r0, #2
	str r0, [sp, #0x84]
_0224BE46:
	mov r0, #0xd
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl MOD11_02246870
	cmp r0, #0
	bne _0224BEDE
	mov r0, #0x4c
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl MOD11_02246870
	cmp r0, #0
	bne _0224BEDE
	ldr r0, [sp, #0xa0]
	mov r1, #3
	tst r0, r1
	beq _0224BE9A
	cmp r6, #0xa
	beq _0224BE80
	cmp r6, #0xb
	beq _0224BE8C
	b _0224BE9A
_0224BE80:
	ldr r0, [sp, #0x84]
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r0, r1, #1
	str r0, [sp, #0x84]
	b _0224BE9A
_0224BE8C:
	ldr r1, [sp, #0x84]
	mov r0, #0xf
	mul r0, r1
	mov r1, #0xa
	bl _s32_div_f
	str r0, [sp, #0x84]
_0224BE9A:
	ldr r1, _0224BF0C ; =0x000080CF
	ldr r0, [sp, #0xa0]
	tst r0, r1
	beq _0224BEB2
	ldr r0, [sp, #8]
	cmp r0, #0x4c
	bne _0224BEB2
	ldr r0, [sp, #0x84]
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r0, r1, #1
	str r0, [sp, #0x84]
_0224BEB2:
	ldr r0, [sp, #0xa0]
	mov r1, #0x30
	tst r0, r1
	beq _0224BEDE
	cmp r6, #0xa
	beq _0224BEC4
	cmp r6, #0xb
	beq _0224BED4
	b _0224BEDE
_0224BEC4:
	ldr r1, [sp, #0x84]
	mov r0, #0xf
	mul r0, r1
	mov r1, #0xa
	bl _s32_div_f
	str r0, [sp, #0x84]
	b _0224BEDE
_0224BED4:
	ldr r0, [sp, #0x84]
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r0, r1, #1
	str r0, [sp, #0x84]
_0224BEDE:
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	mov r2, #0x49
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #0
	beq _0224BF00
	cmp r6, #0xa
	bne _0224BF00
	ldr r1, [sp, #0x84]
	mov r0, #0xf
	mul r0, r1
	mov r1, #0xa
	bl _s32_div_f
	str r0, [sp, #0x84]
_0224BF00:
	ldr r0, [sp, #0x84]
	add r0, r0, #2
	add sp, #0x8c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224BF08: .word 0x000003E6
_0224BF0C: .word 0x000080CF

	thumb_func_start MOD11_0224BF10
MOD11_0224BF10: ; 0x0224BF10
	push {r4, lr}
	add r4, r1, #0
	beq _0224BF36
	bl LCRandom
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1c
	sub r1, r1, r2
	mov r0, #0x1c
	ror r1, r0
	add r0, r2, r1
	mov r1, #0x64
	sub r0, r1, r0
	mul r0, r4
	bl _s32_div_f
	add r4, r0, #0
	bne _0224BF36
	mov r4, #1
_0224BF36:
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD11_0224BF3C
MOD11_0224BF3C: ; 0x0224BF3C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r7, #1
	str r1, [sp]
	str r2, [sp, #4]
	str r3, [sp, #8]
	bl MOD11_02249B4C
	add r1, r0, #0
	add r0, r4, #0
	add r2, r7, #0
	bl MOD11_0224C12C
	add r3, r0, #0
	ldr r1, [sp]
	mov r0, #0xc0
	mul r0, r1
	mov r1, #0xb5
	lsl r1, r1, #6
	add r2, r4, r0
	add r0, r1, #0
	add r0, #0x70
	ldr r0, [r2, r0]
	ldr r6, [sp, #4]
	str r0, [sp, #0x10]
	mov r0, #0xc0
	mul r0, r6
	add r6, r4, r0
	add r0, r1, #0
	add r0, #0x80
	ldr r0, [r6, r0]
	ldrh r5, [r2, r1]
	add r1, #0x27
	str r0, [sp, #0xc]
	ldrb r0, [r2, r1]
	cmp r0, #0x69
	bne _0224BF8C
	add r2, r7, #0
	b _0224BF8E
_0224BF8C:
	mov r2, #0
_0224BF8E:
	cmp r3, #0x42
	bne _0224BF96
	mov r6, #1
	b _0224BF98
_0224BF96:
	mov r6, #0
_0224BF98:
	mov r1, #1
	ldr r0, [sp, #0x10]
	lsl r1, r1, #0x14
	tst r0, r1
	beq _0224BFA6
	mov r0, #1
	b _0224BFA8
_0224BFA6:
	mov r0, #0
_0224BFA8:
	cmp r3, #0x58
	bne _0224BFB4
	cmp r5, #0x71
	bne _0224BFB4
	mov r1, #1
	b _0224BFB6
_0224BFB4:
	mov r1, #0
_0224BFB6:
	cmp r3, #0x5b
	bne _0224BFC2
	cmp r5, #0x53
	bne _0224BFC2
	mov r3, #1
	b _0224BFC4
_0224BFC2:
	mov r3, #0
_0224BFC4:
	lsl r0, r0, #1
	add r5, r6, r0
	ldr r0, [sp, #8]
	add r0, r0, r5
	add r2, r2, r0
	lsl r0, r1, #1
	add r1, r2, r0
	lsl r0, r3, #1
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #4
	bls _0224BFE0
	mov r5, #4
_0224BFE0:
	bl LCRandom
	ldr r1, _0224C040 ; =MOD11_0225E244
	ldrb r1, [r1, r5]
	bl _s32_div_f
	cmp r1, #0
	bne _0224C026
	ldr r1, [sp]
	ldr r2, [sp, #4]
	add r0, r4, #0
	mov r3, #4
	bl MOD11_02246D84
	cmp r0, #0
	bne _0224C026
	ldr r1, [sp]
	ldr r2, [sp, #4]
	add r0, r4, #0
	mov r3, #0x4b
	bl MOD11_02246D84
	cmp r0, #0
	bne _0224C026
	mov r0, #7
	ldr r1, [sp, #0x28]
	lsl r0, r0, #0xc
	tst r0, r1
	bne _0224C026
	mov r1, #2
	ldr r0, [sp, #0xc]
	lsl r1, r1, #0xe
	tst r0, r1
	bne _0224C026
	mov r7, #2
_0224C026:
	cmp r7, #2
	bne _0224C038
	ldr r1, [sp]
	add r0, r4, #0
	bl MOD11_02246D1C
	cmp r0, #0x61
	bne _0224C038
	mov r7, #3
_0224C038:
	add r0, r7, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0224C040: .word MOD11_0225E244

	thumb_func_start MOD11_0224C044
MOD11_0224C044: ; 0x0224C044
	push {r3, r4}
	ldr r4, _0224C074 ; =MOD11_0225E300
	ldr r1, _0224C078 ; =0x0000FFFE
	mov r3, #0
_0224C04C:
	ldrh r2, [r4]
	cmp r0, r2
	beq _0224C05C
	add r4, r4, #2
	ldrh r2, [r4]
	add r3, r3, #1
	cmp r2, r1
	bne _0224C04C
_0224C05C:
	ldr r0, _0224C074 ; =MOD11_0225E300
	lsl r1, r3, #1
	ldrh r1, [r0, r1]
	ldr r0, _0224C078 ; =0x0000FFFE
	cmp r1, r0
	bne _0224C06E
	mov r0, #1
	pop {r3, r4}
	bx lr
_0224C06E:
	mov r0, #0
	pop {r3, r4}
	bx lr
	.align 2, 0
_0224C074: .word MOD11_0225E300
_0224C078: .word 0x0000FFFE

	thumb_func_start MOD11_0224C07C
MOD11_0224C07C: ; 0x0224C07C
	push {r3, r4}
	ldr r4, _0224C0AC ; =MOD11_0225E300
	ldr r1, _0224C0B0 ; =0x0000FFFF
	mov r3, #0
_0224C084:
	ldrh r2, [r4]
	cmp r0, r2
	beq _0224C094
	add r4, r4, #2
	ldrh r2, [r4]
	add r3, r3, #1
	cmp r2, r1
	bne _0224C084
_0224C094:
	ldr r0, _0224C0AC ; =MOD11_0225E300
	lsl r1, r3, #1
	ldrh r1, [r0, r1]
	ldr r0, _0224C0B0 ; =0x0000FFFF
	cmp r1, r0
	bne _0224C0A6
	mov r0, #1
	pop {r3, r4}
	bx lr
_0224C0A6:
	mov r0, #0
	pop {r3, r4}
	bx lr
	.align 2, 0
_0224C0AC: .word MOD11_0225E300
_0224C0B0: .word 0x0000FFFF

	thumb_func_start MOD11_0224C0B4
MOD11_0224C0B4: ; 0x0224C0B4
	push {r4, r5}
	lsl r1, r1, #4
	add r4, r0, r1
	ldr r1, _0224C0E8 ; =0x000003DE
	ldr r3, _0224C0EC ; =MOD11_0225E254
	ldrh r1, [r4, r1]
	ldr r4, _0224C0E8 ; =0x000003DE
	mov r2, #0
_0224C0C4:
	ldrh r5, [r3]
	lsl r5, r5, #4
	add r5, r0, r5
	ldrh r5, [r5, r4]
	cmp r1, r5
	beq _0224C0D8
	add r2, r2, #1
	add r3, r3, #2
	cmp r2, #6
	blo _0224C0C4
_0224C0D8:
	cmp r2, #6
	bne _0224C0E2
	mov r0, #1
	pop {r4, r5}
	bx lr
_0224C0E2:
	mov r0, #0
	pop {r4, r5}
	bx lr
	.align 2, 0
_0224C0E8: .word 0x000003DE
_0224C0EC: .word MOD11_0225E254

	thumb_func_start MOD11_0224C0F0
MOD11_0224C0F0: ; 0x0224C0F0
	push {r4, r5}
	lsl r1, r1, #4
	add r4, r0, r1
	ldr r1, _0224C124 ; =0x000003DE
	ldr r3, _0224C128 ; =MOD11_0225E26C
	ldrh r1, [r4, r1]
	ldr r4, _0224C124 ; =0x000003DE
	mov r2, #0
_0224C100:
	ldrh r5, [r3]
	lsl r5, r5, #4
	add r5, r0, r5
	ldrh r5, [r5, r4]
	cmp r1, r5
	beq _0224C114
	add r2, r2, #1
	add r3, r3, #2
	cmp r2, #6
	blo _0224C100
_0224C114:
	cmp r2, #6
	bne _0224C11E
	mov r0, #1
	pop {r4, r5}
	bx lr
_0224C11E:
	mov r0, #0
	pop {r4, r5}
	bx lr
	.align 2, 0
_0224C124: .word 0x000003DE
_0224C128: .word MOD11_0225E26C

	thumb_func_start MOD11_0224C12C
MOD11_0224C12C: ; 0x0224C12C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, r1, #0
	mov r1, #0
	add r4, r2, #0
	bl GetItemIndexMapping
	add r1, r0, #0
	ldr r0, _0224C14C ; =0x00002120
	ldr r0, [r5, r0]
	bl GetItemDataPtrFromArray
	add r1, r4, #0
	bl GetItemAttr_PreloadedItemData
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224C14C: .word 0x00002120

	thumb_func_start MOD11_0224C150
MOD11_0224C150: ; 0x0224C150
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r2, #0
	bl MOD11_0222FF84
	add r6, r0, #0
	mov r4, #0
	cmp r6, #0
	ble _0224C174
_0224C162:
	add r0, r7, #0
	add r1, r4, #0
	bl MOD11_02230270
	cmp r5, r0
	beq _0224C174
	add r4, r4, #1
	cmp r4, r6
	blt _0224C162
_0224C174:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD11_0224C178
MOD11_0224C178: ; 0x0224C178
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	str r0, [sp, #4]
	add r5, r1, #0
	bl MOD11_0222FF84
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	sub r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, #0
	ble _0224C1FE
_0224C194:
	ldr r0, [sp, #0x14]
	add r7, r0, #1
	ldr r0, [sp, #0x10]
	cmp r7, r0
	bge _0224C1F2
	ldr r0, [sp, #0x14]
	add r0, r5, r0
	str r0, [sp, #0xc]
_0224C1A4:
	ldr r1, [sp, #0xc]
	ldr r0, _0224C204 ; =0x000021E8
	ldrb r6, [r1, r0]
	add r1, r5, r7
	ldrb r4, [r1, r0]
	lsl r0, r6, #4
	str r1, [sp, #8]
	add r1, r5, r0
	ldr r0, _0224C208 ; =0x000021B4
	ldr r0, [r1, r0]
	lsl r1, r4, #4
	add r2, r5, r1
	ldr r1, _0224C208 ; =0x000021B4
	ldr r1, [r2, r1]
	cmp r0, r1
	bne _0224C1EA
	cmp r0, #1
	beq _0224C1CC
	mov r0, #1
	b _0224C1CE
_0224C1CC:
	mov r0, #0
_0224C1CE:
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	add r2, r6, #0
	add r3, r4, #0
	bl MOD11_02244248
	cmp r0, #0
	beq _0224C1EA
	ldr r1, [sp, #0xc]
	ldr r0, _0224C204 ; =0x000021E8
	strb r4, [r1, r0]
	ldr r1, [sp, #8]
	strb r6, [r1, r0]
_0224C1EA:
	ldr r0, [sp, #0x10]
	add r7, r7, #1
	cmp r7, r0
	blt _0224C1A4
_0224C1F2:
	ldr r0, [sp, #0x14]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [sp, #0x14]
	cmp r1, r0
	blt _0224C194
_0224C1FE:
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_0224C204: .word 0x000021E8
_0224C208: .word 0x000021B4

	thumb_func_start MOD11_0224C20C
MOD11_0224C20C: ; 0x0224C20C
	push {r4, r5}
	mov r4, #0xc0
	mul r4, r1
	add r5, r0, r4
	ldr r0, _0224C24C ; =0x00002DB0
	mov r1, #1
	ldr r4, [r5, r0]
	lsl r1, r1, #0x18
	mov r3, #0
	tst r1, r4
	bne _0224C22C
	add r0, #0x10
	ldr r1, [r5, r0]
	ldr r0, _0224C250 ; =0x200400C0
	tst r0, r1
	beq _0224C244
_0224C22C:
	ldr r4, _0224C254 ; =MOD11_0225E2D8
	mov r1, #0
_0224C230:
	ldr r0, [r4]
	cmp r2, r0
	bne _0224C23A
	mov r3, #1
	b _0224C246
_0224C23A:
	add r1, r1, #1
	add r4, r4, #4
	cmp r1, #0xa
	blo _0224C230
	b _0224C246
_0224C244:
	mov r3, #1
_0224C246:
	add r0, r3, #0
	pop {r4, r5}
	bx lr
	.align 2, 0
_0224C24C: .word 0x00002DB0
_0224C250: .word 0x200400C0
_0224C254: .word MOD11_0225E2D8

	thumb_func_start MOD11_0224C258
MOD11_0224C258: ; 0x0224C258
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r1, #0
	ldr r1, [r5, #0x64]
	str r0, [sp]
	add r0, r5, #0
	add r4, r2, #0
	mov r6, #0
	bl MOD11_02249D90
	str r0, [sp, #0xc]
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	add r2, r6, #0
	bl MOD11_02249DA4
	str r0, [sp, #0x10]
	ldr r1, [r5, #0x6c]
	add r0, r5, #0
	bl MOD11_02249D90
	add r7, r0, #0
	ldr r1, [r5, #0x6c]
	add r0, r5, #0
	add r2, r6, #0
	bl MOD11_02249DA4
	str r0, [sp, #8]
	ldr r0, [sp]
	ldr r1, [r5, #0x64]
	bl MOD11_02230270
	str r0, [sp, #4]
	ldr r0, [sp, #0xc]
	cmp r0, #0x57
	bne _0224C2F4
	ldr r0, _0224C41C ; =0x0000213C
	ldr r1, [r5, r0]
	mov r0, #2
	lsl r0, r0, #0xc
	tst r0, r1
	beq _0224C2F4
	ldr r0, [r5, #0x64]
	mov r1, #0x1c
	mul r1, r0
	add r2, r5, r1
	mov r1, #0xbb
	lsl r1, r1, #2
	ldr r2, [r2, r1]
	cmp r2, #0
	beq _0224C2F4
	ldr r1, [r5, #0x6c]
	cmp r0, r1
	beq _0224C2F4
	mov r1, #0xc0
	mul r1, r0
	ldr r3, _0224C420 ; =0x00002D8C
	add r1, r5, r1
	ldr r0, [r1, r3]
	add r3, r3, #4
	ldr r1, [r1, r3]
	cmp r0, r1
	bhs _0224C2F4
	cmp r0, #0
	beq _0224C2F4
	ldr r1, [sp, #0x10]
	neg r0, r2
	bl MOD11_022476C0
	ldr r1, _0224C424 ; =0x0000215C
	mov r6, #1
	str r0, [r5, r1]
	mov r0, #0x46
	ldr r1, [r5, #0x64]
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r0, #0xd5
	str r0, [r4]
_0224C2F4:
	ldr r0, [sp, #0xc]
	cmp r0, #0x61
	bne _0224C356
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl MOD11_02246D1C
	cmp r0, #0x62
	beq _0224C356
	ldr r0, _0224C41C ; =0x0000213C
	ldr r1, [r5, r0]
	mov r0, #2
	lsl r0, r0, #0xc
	tst r0, r1
	beq _0224C356
	ldr r0, _0224C428 ; =0x00003044
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	mov r0, #0x3e
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	cmp r0, #2
	beq _0224C356
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	add r2, r1, #0
	mul r2, r0
	ldr r3, _0224C420 ; =0x00002D8C
	add r2, r5, r2
	ldr r1, [r2, r3]
	cmp r1, #0
	beq _0224C356
	add r1, r3, #4
	ldr r1, [r2, r1]
	sub r0, #0xc1
	mul r0, r1
	mov r1, #0xa
	bl MOD11_022476C0
	ldr r1, _0224C424 ; =0x0000215C
	mov r6, #1
	str r0, [r5, r1]
	mov r0, #0x46
	ldr r1, [r5, #0x64]
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r0, #0xd6
	str r0, [r4]
_0224C356:
	cmp r7, #0x2d
	bne _0224C3AA
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r5, r0
	ldr r0, _0224C420 ; =0x00002D8C
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _0224C3AA
	add r0, r5, #0
	bl MOD11_02246D1C
	cmp r0, #0x62
	beq _0224C3AA
	ldr r1, [r5, #0x6c]
	mov r0, #0x1c
	mul r0, r1
	add r1, r5, r0
	mov r0, #0xb6
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0224C3AA
	ldr r0, [r5, #0x64]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	ldr r0, _0224C42C ; =0x00002D90
	add r2, r5, r2
	ldr r2, [r2, r0]
	sub r1, #0xc1
	add r0, r2, #0
	mul r0, r1
	ldr r1, [sp, #8]
	bl MOD11_022476C0
	ldr r1, _0224C424 ; =0x0000215C
	mov r6, #1
	str r0, [r5, r1]
	lsr r0, r1, #5
	str r0, [r4]
_0224C3AA:
	cmp r7, #0x73
	bne _0224C416
	ldr r0, [r5, #0x64]
	mov r1, #0xc0
	mul r1, r0
	add r3, r5, r1
	ldr r1, _0224C420 ; =0x00002D8C
	ldr r2, [r3, r1]
	cmp r2, #0
	beq _0224C416
	add r1, #0x2c
	ldrh r1, [r3, r1]
	cmp r1, #0
	bne _0224C416
	add r1, r5, r0
	ldr r0, _0224C430 ; =0x0000219C
	ldrb r0, [r1, r0]
	bl MaskOfFlagNo
	ldr r1, [sp, #4]
	lsl r1, r1, #3
	add r2, r5, r1
	mov r1, #0x71
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	lsl r1, r1, #3
	lsr r1, r1, #0x1a
	tst r0, r1
	bne _0224C416
	ldr r1, [r5, #0x6c]
	mov r0, #0x1c
	mul r0, r1
	add r2, r5, r0
	mov r0, #0xb6
	lsl r0, r0, #2
	ldr r1, [r2, r0]
	cmp r1, #0
	bne _0224C3FE
	add r0, #8
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _0224C416
_0224C3FE:
	ldr r0, _0224C428 ; =0x00003044
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _0224C434 ; =0x000003E9
	ldrb r1, [r1, r0]
	mov r0, #1
	tst r1, r0
	beq _0224C416
	mov r1, #0xd8
	str r1, [r4]
	add r6, r0, #0
_0224C416:
	add r0, r6, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224C41C: .word 0x0000213C
_0224C420: .word 0x00002D8C
_0224C424: .word 0x0000215C
_0224C428: .word 0x00003044
_0224C42C: .word 0x00002D90
_0224C430: .word 0x0000219C
_0224C434: .word 0x000003E9

	thumb_func_start MOD11_0224C438
MOD11_0224C438: ; 0x0224C438
	push {r4, r5, r6, lr}
	add r6, r2, #0
	add r4, r1, #0
	add r1, r6, #0
	add r5, r0, #0
	bl MOD11_02246D1C
	cmp r0, #0x2e
	bne _0224C46A
	cmp r6, #0xff
	beq _0224C46A
	ldr r0, _0224C46C ; =0x00002D6C
	add r1, r5, r0
	mov r0, #0xc0
	mul r0, r4
	add r0, r1, r0
	lsl r1, r4, #1
	add r2, r5, r1
	ldr r1, _0224C470 ; =0x000030BC
	ldrh r2, [r2, r1]
	ldrb r1, [r0, r2]
	cmp r1, #0
	beq _0224C46A
	sub r1, r1, #1
	strb r1, [r0, r2]
_0224C46A:
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224C46C: .word 0x00002D6C
_0224C470: .word 0x000030BC

	thumb_func_start MOD11_0224C474
MOD11_0224C474: ; 0x0224C474
	push {r4, lr}
	add r4, r1, #0
	cmp r2, #0xc
	bhi _0224C528
	add r1, r2, r2
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0224C488: ; jump table
	.short _0224C4A2 - _0224C488 - 2 ; case 0
	.short _0224C4B4 - _0224C488 - 2 ; case 1
	.short _0224C4CA - _0224C488 - 2 ; case 2
	.short _0224C4D2 - _0224C488 - 2 ; case 3
	.short _0224C4DA - _0224C488 - 2 ; case 4
	.short _0224C4E0 - _0224C488 - 2 ; case 5
	.short _0224C4E6 - _0224C488 - 2 ; case 6
	.short _0224C4F2 - _0224C488 - 2 ; case 7
	.short _0224C4FE - _0224C488 - 2 ; case 8
	.short _0224C508 - _0224C488 - 2 ; case 9
	.short _0224C510 - _0224C488 - 2 ; case 10
	.short _0224C516 - _0224C488 - 2 ; case 11
	.short _0224C51E - _0224C488 - 2 ; case 12
_0224C4A2:
	add r1, r3, #0
	bl MOD11_02230270
	lsl r0, r0, #2
	add r1, r4, r0
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	pop {r4, pc}
_0224C4B4:
	add r1, r3, #0
	bl MOD11_02230270
	lsl r0, r0, #3
	add r1, r4, r0
	mov r0, #0x71
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1d
	pop {r4, pc}
_0224C4CA:
	ldr r0, _0224C530 ; =0x0000219C
	add r1, r4, r3
	ldrb r0, [r1, r0]
	pop {r4, pc}
_0224C4D2:
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	pop {r4, pc}
_0224C4DA:
	ldr r0, _0224C534 ; =0x00003109
	ldrb r0, [r4, r0]
	pop {r4, pc}
_0224C4E0:
	ldr r0, _0224C538 ; =0x0000311D
	ldrb r0, [r4, r0]
	pop {r4, pc}
_0224C4E6:
	lsl r0, r3, #2
	add r1, r4, r0
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	pop {r4, pc}
_0224C4F2:
	lsl r0, r3, #2
	add r1, r4, r0
	mov r0, #0x59
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	pop {r4, pc}
_0224C4FE:
	lsl r0, r3, #4
	add r1, r4, r0
	ldr r0, _0224C53C ; =0x000021A8
	ldr r0, [r1, r0]
	pop {r4, pc}
_0224C508:
	mov r0, #0x3d
	lsl r0, r0, #4
	ldrb r0, [r4, r0]
	pop {r4, pc}
_0224C510:
	ldr r0, _0224C540 ; =0x00003108
	ldrb r0, [r4, r0]
	pop {r4, pc}
_0224C516:
	ldr r0, _0224C544 ; =0x000003DA
	add r1, r4, r3
	ldrb r0, [r1, r0]
	pop {r4, pc}
_0224C51E:
	lsl r0, r3, #4
	add r1, r4, r0
	ldr r0, _0224C548 ; =0x000021B0
	ldr r0, [r1, r0]
	pop {r4, pc}
_0224C528:
	bl GF_AssertFail
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_0224C530: .word 0x0000219C
_0224C534: .word 0x00003109
_0224C538: .word 0x0000311D
_0224C53C: .word 0x000021A8
_0224C540: .word 0x00003108
_0224C544: .word 0x000003DA
_0224C548: .word 0x000021B0

	thumb_func_start MOD11_0224C54C
MOD11_0224C54C: ; 0x0224C54C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r4, [sp, #0x10]
	cmp r2, #0xb
	bhi _0224C5CA
	add r1, r2, r2
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0224C562: ; jump table
	.short _0224C57A - _0224C562 - 2 ; case 0
	.short _0224C58C - _0224C562 - 2 ; case 1
	.short _0224C5AA - _0224C562 - 2 ; case 2
	.short _0224C5B2 - _0224C562 - 2 ; case 3
	.short _0224C5CA - _0224C562 - 2 ; case 4
	.short _0224C5CA - _0224C562 - 2 ; case 5
	.short _0224C5CA - _0224C562 - 2 ; case 6
	.short _0224C5CA - _0224C562 - 2 ; case 7
	.short _0224C5CA - _0224C562 - 2 ; case 8
	.short _0224C5BA - _0224C562 - 2 ; case 9
	.short _0224C5CA - _0224C562 - 2 ; case 10
	.short _0224C5C2 - _0224C562 - 2 ; case 11
_0224C57A:
	add r1, r3, #0
	bl MOD11_02230270
	lsl r0, r0, #2
	add r1, r5, r0
	mov r0, #0x6f
	lsl r0, r0, #2
	str r4, [r1, r0]
	pop {r3, r4, r5, pc}
_0224C58C:
	add r1, r3, #0
	bl MOD11_02230270
	mov r1, #0x71
	lsl r1, r1, #2
	add r1, r5, r1
	lsl r0, r0, #3
	ldr r3, [r1, r0]
	ldr r2, _0224C5D0 ; =0xFFFF8FFF
	and r3, r2
	lsl r2, r4, #0x1d
	lsr r2, r2, #0x11
	orr r2, r3
	str r2, [r1, r0]
	pop {r3, r4, r5, pc}
_0224C5AA:
	ldr r0, _0224C5D4 ; =0x0000219C
	add r1, r5, r3
	strb r4, [r1, r0]
	pop {r3, r4, r5, pc}
_0224C5B2:
	mov r0, #0x15
	lsl r0, r0, #4
	str r4, [r5, r0]
	pop {r3, r4, r5, pc}
_0224C5BA:
	mov r0, #0x3d
	lsl r0, r0, #4
	strb r4, [r5, r0]
	pop {r3, r4, r5, pc}
_0224C5C2:
	ldr r0, _0224C5D8 ; =0x000003DA
	add r1, r5, r3
	strb r4, [r1, r0]
	pop {r3, r4, r5, pc}
_0224C5CA:
	bl GF_AssertFail
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224C5D0: .word 0xFFFF8FFF
_0224C5D4: .word 0x0000219C
_0224C5D8: .word 0x000003DA

	thumb_func_start MOD11_0224C5DC
MOD11_0224C5DC: ; 0x0224C5DC
	push {r4, lr}
	add r3, r0, #0
	add r3, #0x88
	str r1, [r3]
	add r3, r0, #0
	ldr r1, _0224C640 ; =0x007FFFFF
	add r4, r2, #0
	and r4, r1
	add r3, #0x8c
	str r4, [r3]
	lsl r1, r1, #0x17
	add r3, r2, #0
	and r3, r1
	add r1, r0, #0
	add r1, #0x90
	str r3, [r1]
	mov r3, #1
	lsl r3, r3, #0x1e
	add r1, r2, #0
	tst r1, r3
	beq _0224C60E
	ldr r1, [r0, #0x64]
	add r0, #0x94
	str r1, [r0]
	b _0224C62E
_0224C60E:
	lsl r1, r3, #1
	tst r1, r2
	beq _0224C61C
	ldr r1, [r0, #0x6c]
	add r0, #0x94
	str r1, [r0]
	b _0224C62E
_0224C61C:
	lsr r1, r3, #1
	tst r1, r2
	bne _0224C628
	lsr r1, r3, #2
	tst r1, r2
	beq _0224C62E
_0224C628:
	mov r1, #0
	add r0, #0x94
	str r1, [r0]
_0224C62E:
	cmp r4, #0x91
	blo _0224C636
	bl GF_AssertFail
_0224C636:
	ldr r0, _0224C644 ; =MOD11_0225E4C8
	lsl r1, r4, #2
	ldr r0, [r0, r1]
	pop {r4, pc}
	nop
_0224C640: .word 0x007FFFFF
_0224C644: .word MOD11_0225E4C8

	thumb_func_start MOD11_0224C648
MOD11_0224C648: ; 0x0224C648
	push {r3, r4, r5, lr}
	ldr r1, _0224C6D0 ; =0x0000213C
	add r5, r2, #0
	ldr r2, [r0, r1]
	mov r0, #2
	lsl r0, r0, #0xa
	add r1, r2, #0
	ldr r4, [sp, #0x14]
	tst r1, r0
	bne _0224C672
	lsl r0, r0, #4
	tst r0, r2
	bne _0224C672
	cmp r3, #0
	beq _0224C672
	add r0, r3, #0
	mul r0, r5
	mov r1, #0xa
	bl MOD11_022476C0
	add r3, r0, #0
_0224C672:
	cmp r5, #0
	beq _0224C680
	cmp r5, #5
	beq _0224C692
	cmp r5, #0x14
	beq _0224C6B0
	b _0224C6CC
_0224C680:
	ldr r1, [r4]
	mov r0, #8
	orr r1, r0
	mov r0, #4
	bic r1, r0
	mov r0, #2
	bic r1, r0
	str r1, [r4]
	b _0224C6CC
_0224C692:
	ldr r0, [sp, #0x10]
	cmp r0, #0
	beq _0224C6CC
	ldr r1, [r4]
	mov r0, #2
	tst r0, r1
	beq _0224C6A8
	mov r0, #2
	bic r1, r0
	str r1, [r4]
	b _0224C6CC
_0224C6A8:
	mov r0, #4
	orr r0, r1
	str r0, [r4]
	b _0224C6CC
_0224C6B0:
	ldr r0, [sp, #0x10]
	cmp r0, #0
	beq _0224C6CC
	ldr r1, [r4]
	mov r0, #4
	tst r0, r1
	beq _0224C6C6
	mov r0, #4
	bic r1, r0
	str r1, [r4]
	b _0224C6CC
_0224C6C6:
	mov r0, #2
	orr r0, r1
	str r0, [r4]
_0224C6CC:
	add r0, r3, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224C6D0: .word 0x0000213C

	thumb_func_start MOD11_0224C6D4
MOD11_0224C6D4: ; 0x0224C6D4
	lsl r1, r1, #4
	add r2, r0, r1
	ldr r1, _0224C738 ; =0x000003DE
	ldrh r3, [r2, r1]
	cmp r3, #0x9b
	bgt _0224C706
	cmp r3, #0x97
	blt _0224C6EC
	beq _0224C726
	cmp r3, #0x9b
	beq _0224C726
	b _0224C732
_0224C6EC:
	cmp r3, #0x27
	bgt _0224C6F8
	bge _0224C726
	cmp r3, #0x1a
	beq _0224C726
	b _0224C732
_0224C6F8:
	cmp r3, #0x4b
	bgt _0224C700
	beq _0224C726
	b _0224C732
_0224C700:
	cmp r3, #0x91
	beq _0224C726
	b _0224C732
_0224C706:
	mov r2, #1
	lsl r2, r2, #8
	cmp r3, r2
	bgt _0224C716
	bge _0224C726
	cmp r3, #0xff
	beq _0224C726
	b _0224C732
_0224C716:
	add r1, r2, #7
	cmp r3, r1
	bgt _0224C720
	beq _0224C726
	b _0224C732
_0224C720:
	add r2, #0x11
	cmp r3, r2
	bne _0224C732
_0224C726:
	ldr r1, _0224C73C ; =0x0000213C
	ldr r1, [r0, r1]
	mov r0, #2
	lsl r0, r0, #8
	and r0, r1
	bx lr
_0224C732:
	mov r0, #1
	bx lr
	nop
_0224C738: .word 0x000003DE
_0224C73C: .word 0x0000213C

	thumb_func_start MOD11_0224C740
MOD11_0224C740: ; 0x0224C740
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	cmp r2, #0x1b
	bne _0224C756
	mov r0, #0xc0
	mul r0, r6
	add r1, r5, r0
	ldr r0, _0224C80C ; =0x00002D64
	ldrb r4, [r1, r0]
	b _0224C76A
_0224C756:
	cmp r2, #0x1c
	bne _0224C766
	mov r0, #0xc0
	mul r0, r6
	add r1, r5, r0
	ldr r0, _0224C810 ; =0x00002D65
	ldrb r4, [r1, r0]
	b _0224C76A
_0224C766:
	bl GF_AssertFail
_0224C76A:
	mov r0, #0xc0
	mul r0, r6
	mov r2, #0xb5
	add r1, r5, r0
	lsl r2, r2, #6
	ldrh r3, [r1, r2]
	ldr r0, _0224C814 ; =0x000001ED
	cmp r3, r0
	bne _0224C806
	add r0, r2, #0
	add r0, #0x27
	ldrb r0, [r1, r0]
	cmp r0, #0x79
	bne _0224C806
	add r2, #0x78
	ldrh r1, [r1, r2]
	add r0, r5, #0
	mov r2, #1
	bl MOD11_0224C12C
	sub r0, #0x7d
	cmp r0, #0xf
	bhi _0224C804
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224C7A4: ; jump table
	.short _0224C7C4 - _0224C7A4 - 2 ; case 0
	.short _0224C7C8 - _0224C7A4 - 2 ; case 1
	.short _0224C7CC - _0224C7A4 - 2 ; case 2
	.short _0224C7D0 - _0224C7A4 - 2 ; case 3
	.short _0224C7D4 - _0224C7A4 - 2 ; case 4
	.short _0224C7D8 - _0224C7A4 - 2 ; case 5
	.short _0224C7DC - _0224C7A4 - 2 ; case 6
	.short _0224C7E0 - _0224C7A4 - 2 ; case 7
	.short _0224C7E4 - _0224C7A4 - 2 ; case 8
	.short _0224C7E8 - _0224C7A4 - 2 ; case 9
	.short _0224C7EC - _0224C7A4 - 2 ; case 10
	.short _0224C7F0 - _0224C7A4 - 2 ; case 11
	.short _0224C7F4 - _0224C7A4 - 2 ; case 12
	.short _0224C7F8 - _0224C7A4 - 2 ; case 13
	.short _0224C7FC - _0224C7A4 - 2 ; case 14
	.short _0224C800 - _0224C7A4 - 2 ; case 15
_0224C7C4:
	mov r4, #0xa
	b _0224C806
_0224C7C8:
	mov r4, #0xb
	b _0224C806
_0224C7CC:
	mov r4, #0xd
	b _0224C806
_0224C7D0:
	mov r4, #0xc
	b _0224C806
_0224C7D4:
	mov r4, #0xf
	b _0224C806
_0224C7D8:
	mov r4, #1
	b _0224C806
_0224C7DC:
	mov r4, #3
	b _0224C806
_0224C7E0:
	mov r4, #4
	b _0224C806
_0224C7E4:
	mov r4, #2
	b _0224C806
_0224C7E8:
	mov r4, #0xe
	b _0224C806
_0224C7EC:
	mov r4, #6
	b _0224C806
_0224C7F0:
	mov r4, #5
	b _0224C806
_0224C7F4:
	mov r4, #7
	b _0224C806
_0224C7F8:
	mov r4, #0x10
	b _0224C806
_0224C7FC:
	mov r4, #0x11
	b _0224C806
_0224C800:
	mov r4, #8
	b _0224C806
_0224C804:
	mov r4, #0
_0224C806:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	nop
_0224C80C: .word 0x00002D64
_0224C810: .word 0x00002D65
_0224C814: .word 0x000001ED

	thumb_func_start MOD11_0224C818
MOD11_0224C818: ; 0x0224C818
	lsl r1, r1, #3
	add r3, r0, r1
	mov r2, #0
	mov r0, #0x37
	add r1, r2, #0
	lsl r0, r0, #4
_0224C824:
	add r2, r2, #1
	strh r1, [r3, r0]
	add r3, r3, #2
	cmp r2, #4
	blt _0224C824
	bx lr

	thumb_func_start MOD11_0224C830
MOD11_0224C830: ; 0x0224C830
	add r1, r0, r1
	mov r0, #0x39
	mov r2, #0
	lsl r0, r0, #4
	strb r2, [r1, r0]
	bx lr

	thumb_func_start MOD11_0224C83C
MOD11_0224C83C: ; 0x0224C83C
	lsl r1, r1, #1
	add r1, r0, r1
	mov r0, #0xe5
	mov r2, #0
	lsl r0, r0, #2
	strh r2, [r1, r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD11_0224C84C
MOD11_0224C84C: ; 0x0224C84C
	push {r4, r5, r6, lr}
	add r4, r2, #0
	add r3, r0, #0
	mov r2, #0xc0
	add r5, r1, #0
	mul r1, r2
	ldr r6, _0224C8BC ; =0x00002D67
	add r1, r3, r1
	ldrb r1, [r1, r6]
	mov r0, #0xff
	cmp r1, #0x3b
	beq _0224C890
	cmp r1, #0x24
	beq _0224C890
	cmp r1, #0x79
	beq _0224C890
	mul r2, r4
	add r2, r3, r2
	ldrb r2, [r2, r6]
	cmp r2, #0x3b
	beq _0224C890
	cmp r2, #0x24
	beq _0224C890
	cmp r2, #0x79
	beq _0224C890
	bl LCRandom
	mov r1, #1
	tst r0, r1
	beq _0224C88C
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_0224C88C:
	add r0, r5, #0
	pop {r4, r5, r6, pc}
_0224C890:
	cmp r1, #0x3b
	beq _0224C8A0
	cmp r1, #0x24
	beq _0224C8A0
	cmp r1, #0x79
	beq _0224C8A0
	add r0, r5, #0
	pop {r4, r5, r6, pc}
_0224C8A0:
	mov r1, #0xc0
	mul r1, r4
	add r2, r3, r1
	ldr r1, _0224C8BC ; =0x00002D67
	ldrb r1, [r2, r1]
	cmp r1, #0x3b
	beq _0224C8B8
	cmp r1, #0x24
	beq _0224C8B8
	cmp r1, #0x79
	beq _0224C8B8
	add r0, r4, #0
_0224C8B8:
	pop {r4, r5, r6, pc}
	nop
_0224C8BC: .word 0x00002D67

	thumb_func_start MOD11_0224C8C0
MOD11_0224C8C0: ; 0x0224C8C0
	lsl r1, r1, #4
	add r1, r0, r1
	ldr r0, _0224C8E4 ; =0x000003DE
	ldr r3, _0224C8E8 ; =MOD11_0225E260
	ldrh r1, [r1, r0]
	mov r2, #0
_0224C8CC:
	ldrh r0, [r3]
	cmp r0, r1
	bne _0224C8D6
	mov r0, #1
	bx lr
_0224C8D6:
	add r2, r2, #1
	add r3, r3, #2
	cmp r2, #6
	blo _0224C8CC
	mov r0, #0
	bx lr
	nop
_0224C8E4: .word 0x000003DE
_0224C8E8: .word MOD11_0225E260

	thumb_func_start MOD11_0224C8EC
MOD11_0224C8EC: ; 0x0224C8EC
	push {r3, r4, r5, r6, r7, lr}
	add r6, r2, #0
	ldr r2, _0224CA58 ; =0x00000137
	add r7, r0, #0
	add r4, r1, #0
	cmp r3, r2
	bgt _0224C904
	blt _0224C8FE
	b _0224CA00
_0224C8FE:
	cmp r3, #0xed
	beq _0224C9A6
	b _0224CA52
_0224C904:
	add r0, r2, #0
	add r0, #0x34
	cmp r3, r0
	bgt _0224C914
	add r2, #0x34
	cmp r3, r2
	beq _0224C91C
	b _0224CA52
_0224C914:
	add r2, #0x8a
	cmp r3, r2
	beq _0224C928
	b _0224CA52
_0224C91C:
	add r0, r4, #0
	add r1, r6, #0
	bl MOD11_02249E04
	add r5, r0, #0
	b _0224CA54
_0224C928:
	add r0, r4, #0
	add r1, r6, #0
	bl MOD11_02249D90
	sub r0, #0x7d
	cmp r0, #0xf
	bhi _0224C9A2
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224C942: ; jump table
	.short _0224C982 - _0224C942 - 2 ; case 0
	.short _0224C986 - _0224C942 - 2 ; case 1
	.short _0224C98E - _0224C942 - 2 ; case 2
	.short _0224C98A - _0224C942 - 2 ; case 3
	.short _0224C996 - _0224C942 - 2 ; case 4
	.short _0224C962 - _0224C942 - 2 ; case 5
	.short _0224C96A - _0224C942 - 2 ; case 6
	.short _0224C96E - _0224C942 - 2 ; case 7
	.short _0224C966 - _0224C942 - 2 ; case 8
	.short _0224C992 - _0224C942 - 2 ; case 9
	.short _0224C976 - _0224C942 - 2 ; case 10
	.short _0224C972 - _0224C942 - 2 ; case 11
	.short _0224C97A - _0224C942 - 2 ; case 12
	.short _0224C99A - _0224C942 - 2 ; case 13
	.short _0224C99E - _0224C942 - 2 ; case 14
	.short _0224C97E - _0224C942 - 2 ; case 15
_0224C962:
	mov r5, #1
	b _0224CA54
_0224C966:
	mov r5, #2
	b _0224CA54
_0224C96A:
	mov r5, #3
	b _0224CA54
_0224C96E:
	mov r5, #4
	b _0224CA54
_0224C972:
	mov r5, #5
	b _0224CA54
_0224C976:
	mov r5, #6
	b _0224CA54
_0224C97A:
	mov r5, #7
	b _0224CA54
_0224C97E:
	mov r5, #8
	b _0224CA54
_0224C982:
	mov r5, #0xa
	b _0224CA54
_0224C986:
	mov r5, #0xb
	b _0224CA54
_0224C98A:
	mov r5, #0xc
	b _0224CA54
_0224C98E:
	mov r5, #0xd
	b _0224CA54
_0224C992:
	mov r5, #0xe
	b _0224CA54
_0224C996:
	mov r5, #0xf
	b _0224CA54
_0224C99A:
	mov r5, #0x10
	b _0224CA54
_0224C99E:
	mov r5, #0x11
	b _0224CA54
_0224C9A2:
	mov r5, #0
	b _0224CA54
_0224C9A6:
	ldr r0, _0224CA5C ; =0x00002D54
	add r1, r4, r0
	mov r0, #0xc0
	mul r0, r6
	ldr r4, [r1, r0]
	lsl r0, r4, #2
	lsr r0, r0, #0x1b
	lsl r0, r0, #0x1f
	lsr r5, r0, #0x1a
	lsl r0, r4, #7
	lsr r0, r0, #0x1b
	lsl r0, r0, #0x1f
	lsr r3, r0, #0x1b
	lsl r0, r4, #0xc
	lsr r0, r0, #0x1b
	lsl r0, r0, #0x1f
	lsr r2, r0, #0x1c
	lsl r0, r4, #0x11
	lsr r0, r0, #0x1b
	lsl r0, r0, #0x1f
	lsr r1, r0, #0x1d
	lsl r0, r4, #0x1b
	lsl r4, r4, #0x16
	lsr r4, r4, #0x1b
	lsr r6, r0, #0x1b
	mov r0, #1
	lsl r4, r4, #0x1f
	and r0, r6
	lsr r4, r4, #0x1e
	orr r0, r4
	orr r0, r1
	orr r0, r2
	orr r0, r3
	add r1, r5, #0
	orr r1, r0
	mov r0, #0xf
	mul r0, r1
	mov r1, #0x3f
	bl _s32_div_f
	add r5, r0, #1
	cmp r5, #9
	blt _0224CA54
	add r5, r5, #1
	b _0224CA54
_0224CA00:
	mov r2, #0xd
	str r2, [sp]
	mov r2, #8
	mov r3, #0
	bl MOD11_02246870
	cmp r0, #0
	bne _0224CA54
	mov r0, #0x4c
	str r0, [sp]
	add r0, r7, #0
	add r1, r4, #0
	mov r2, #8
	mov r3, #0
	bl MOD11_02246870
	cmp r0, #0
	bne _0224CA54
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	ldr r1, _0224CA60 ; =0x000080FF
	tst r1, r0
	beq _0224CA54
	mov r1, #3
	tst r1, r0
	beq _0224CA38
	mov r5, #0xb
_0224CA38:
	mov r1, #0xc
	tst r1, r0
	beq _0224CA40
	mov r5, #5
_0224CA40:
	mov r1, #0x30
	tst r1, r0
	beq _0224CA48
	mov r5, #0xa
_0224CA48:
	mov r1, #0xc0
	tst r0, r1
	beq _0224CA54
	mov r5, #0xf
	b _0224CA54
_0224CA52:
	mov r5, #0
_0224CA54:
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224CA58: .word 0x00000137
_0224CA5C: .word 0x00002D54
_0224CA60: .word 0x000080FF

	.section .rodata

	.global MOD11_0225E244
MOD11_0225E244: ; 0x0225E244
	.byte 0x10, 0x08, 0x04, 0x03
	.byte 0x02, 0x00, 0x00, 0x00

	.global MOD11_0225E24C
MOD11_0225E24C: ; 0x0225E24C
	.byte 0x31, 0x69, 0x79, 0x74, 0x75, 0x78, 0x76, 0x77

	.global MOD11_0225E254
MOD11_0225E254: ; 0x0225E254
	.byte 0x90, 0x00, 0x66, 0x00
	.byte 0xA6, 0x00, 0x77, 0x00, 0xE3, 0x00, 0xA5, 0x00

	.global MOD11_0225E260
MOD11_0225E260: ; 0x0225E260
	.byte 0x29, 0x00, 0x57, 0x00, 0x58, 0x00, 0x59, 0x00
	.byte 0x90, 0x00, 0xE3, 0x00

	.global MOD11_0225E26C
MOD11_0225E26C: ; 0x0225E26C
	.byte 0x44, 0x00, 0xF3, 0x00, 0xA8, 0x00, 0x57, 0x01, 0x08, 0x01, 0xC0, 0x01

	.global MOD11_0225E278
MOD11_0225E278: ; 0x0225E278
	.byte 0x13, 0x00, 0x54, 0x01, 0x1A, 0x00, 0x88, 0x00, 0x96, 0x00, 0x89, 0x01

	.global MOD11_0225E284
MOD11_0225E284: ; 0x0225E284
	.byte 0x0A

	.global MOD11_0225E285
MOD11_0225E285: ; 0x0225E285
	.byte 0x28, 0x0A, 0x23
	.byte 0x0A, 0x1E, 0x0A, 0x19, 0x0A, 0x14, 0x0A, 0x0F, 0x0A, 0x0A, 0x0F, 0x0A, 0x14, 0x0A, 0x19, 0x0A
	.byte 0x1E, 0x0A, 0x23, 0x0A, 0x28, 0x0A

	.global MOD11_0225E29E
MOD11_0225E29E: ; 0x0225E29E
	.byte 0x69, 0x00, 0x87, 0x00, 0x9C, 0x00, 0xD0, 0x00, 0xEA, 0x00
	.byte 0xEB, 0x00, 0xEC, 0x00, 0x00, 0x01, 0xC8, 0x01, 0x2F, 0x01, 0x63, 0x01, 0xCD, 0x01, 0x69, 0x01
	.byte 0x11, 0x01

	.global MOD11_0225E2BA
MOD11_0225E2BA: ; 0x0225E2BA
	.byte 0x08, 0x00, 0x07, 0x00, 0x09, 0x00, 0xB7, 0x00, 0x08, 0x01, 0x92, 0x00, 0xDF, 0x00
	.byte 0x67, 0x01, 0x05, 0x00, 0x04, 0x00, 0x35, 0x01, 0x45, 0x01, 0x99, 0x01, 0xA2, 0x01, 0x47, 0x01

	.global MOD11_0225E2D8
MOD11_0225E2D8: ; 0x0225E2D8
	.byte 0x0F, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00
	.byte 0x13, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00
	.byte 0x19, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00

	.global MOD11_0225E300
MOD11_0225E300: ; 0x0225E300
	.byte 0x76, 0x00, 0xA5, 0x00, 0xA6, 0x00, 0x66, 0x00
	.byte 0xC0, 0x01, 0xFE, 0xFF, 0xD6, 0x00, 0x12, 0x01, 0x77, 0x00, 0x44, 0x00, 0xF3, 0x00, 0xB6, 0x00
	.byte 0xC5, 0x00, 0xCB, 0x00, 0xC2, 0x00, 0xA8, 0x00, 0x0A, 0x01, 0x21, 0x01, 0x0E, 0x01, 0x57, 0x01
	.byte 0x0F, 0x01, 0x08, 0x01, 0x6C, 0x01, 0x7F, 0x01, 0x7E, 0x01, 0x9F, 0x01, 0xFF, 0xFF

	.global MOD11_0225E336
MOD11_0225E336: ; 0x0225E336
	.byte 0x38, 0x06
	.byte 0x43, 0x08, 0x47, 0x04, 0x48, 0x05, 0x49, 0x0C, 0x4A, 0x11, 0x4B, 0x01, 0x4C, 0x0D, 0x4D, 0x0B
	.byte 0x4E, 0x02, 0x4F, 0x03, 0x50, 0x0F, 0x51, 0x07, 0x52, 0x0E, 0x53, 0x0A, 0x54, 0x10, 0x55, 0x00
	.byte 0x7D, 0x0A, 0x7E, 0x0B, 0x7F, 0x0D, 0x80, 0x0C, 0x81, 0x0F, 0x82, 0x01, 0x83, 0x03, 0x84, 0x04
	.byte 0x85, 0x02, 0x86, 0x0E, 0x87, 0x06, 0x88, 0x05, 0x89, 0x07, 0x8A, 0x10, 0x8B, 0x11, 0x8C, 0x08

	.global MOD11_0225E378
MOD11_0225E378: ; 0x0225E378
	.byte 0x00

	.global MOD11_0225E379
MOD11_0225E379: ; 0x0225E379
	.byte 0x05

	.global MOD11_0225E37A
MOD11_0225E37A: ; 0x0225E37A
	.byte 0x05, 0x00
	.byte 0x08, 0x05, 0x0A, 0x0A, 0x05, 0x0A, 0x0B, 0x05, 0x0A, 0x0C, 0x14, 0x0A
	.byte 0x0F, 0x14, 0x0A, 0x06, 0x14, 0x0A, 0x05, 0x05, 0x0A, 0x10, 0x05, 0x0A, 0x08, 0x14, 0x0B, 0x0A
	.byte 0x14, 0x0B, 0x0B, 0x05, 0x0B, 0x0C, 0x05, 0x0B, 0x04, 0x14, 0x0B, 0x05, 0x14, 0x0B, 0x10, 0x05
	.byte 0x0D, 0x0B, 0x14, 0x0D, 0x0D, 0x05, 0x0D, 0x0C, 0x05, 0x0D, 0x04, 0x00, 0x0D, 0x02, 0x14, 0x0D
	.byte 0x10, 0x05, 0x0C, 0x0A, 0x05, 0x0C, 0x0B, 0x14, 0x0C, 0x0C, 0x05, 0x0C, 0x03, 0x05, 0x0C, 0x04
	.byte 0x14, 0x0C, 0x02, 0x05, 0x0C, 0x06, 0x05, 0x0C, 0x05, 0x14, 0x0C, 0x10, 0x05, 0x0C, 0x08, 0x05
	.byte 0x0F, 0x0B, 0x05, 0x0F, 0x0C, 0x14, 0x0F, 0x0F, 0x05, 0x0F, 0x04, 0x14, 0x0F, 0x02, 0x14, 0x0F
	.byte 0x10, 0x14, 0x0F, 0x08, 0x05, 0x0F, 0x0A, 0x05, 0x01, 0x00, 0x14, 0x01, 0x0F, 0x14, 0x01, 0x03
	.byte 0x05, 0x01, 0x02, 0x05, 0x01, 0x0E, 0x05, 0x01, 0x06, 0x05, 0x01, 0x05, 0x14, 0x01, 0x11, 0x14
	.byte 0x01, 0x08, 0x14, 0x03, 0x0C, 0x14, 0x03, 0x03, 0x05, 0x03, 0x04, 0x05, 0x03, 0x05, 0x05, 0x03
	.byte 0x07, 0x05, 0x03, 0x08, 0x00, 0x04, 0x0A, 0x14, 0x04, 0x0D, 0x14, 0x04, 0x0C, 0x05, 0x04, 0x03
	.byte 0x14, 0x04, 0x02, 0x00, 0x04, 0x06, 0x05, 0x04, 0x05, 0x14, 0x04, 0x08, 0x14, 0x02, 0x0D, 0x05
	.byte 0x02, 0x0C, 0x14, 0x02, 0x01, 0x14, 0x02, 0x06, 0x14, 0x02, 0x05, 0x05, 0x02, 0x08, 0x05, 0x0E
	.byte 0x01, 0x14, 0x0E, 0x03, 0x14, 0x0E, 0x0E, 0x05, 0x0E, 0x11, 0x00, 0x0E, 0x08, 0x05, 0x06, 0x0A
	.byte 0x05, 0x06, 0x0C, 0x14, 0x06, 0x01, 0x05, 0x06, 0x03, 0x05, 0x06, 0x02, 0x05, 0x06, 0x0E, 0x14
	.byte 0x06, 0x07, 0x05, 0x06, 0x11, 0x14, 0x06, 0x08, 0x05, 0x05, 0x0A, 0x14, 0x05, 0x0F, 0x14, 0x05
	.byte 0x01, 0x05, 0x05, 0x04, 0x05, 0x05, 0x02, 0x14, 0x05, 0x06, 0x14, 0x05, 0x08, 0x05, 0x07, 0x00
	.byte 0x00, 0x07, 0x0E, 0x14, 0x07, 0x11, 0x05, 0x07, 0x08, 0x05, 0x07, 0x07, 0x14, 0x10, 0x10, 0x14
	.byte 0x10, 0x08, 0x05, 0x11, 0x01, 0x05, 0x11, 0x0E, 0x14, 0x11, 0x07, 0x14, 0x11, 0x11, 0x05, 0x11
	.byte 0x08, 0x05, 0x08, 0x0A, 0x05, 0x08, 0x0B, 0x05, 0x08, 0x0D, 0x05, 0x08, 0x0F, 0x14, 0x08, 0x05
	.byte 0x14, 0x08, 0x08, 0x05, 0xFE, 0xFE, 0x00, 0x00, 0x07, 0x00, 0x01, 0x07, 0x00, 0xFF, 0xFF, 0x00

	.global MOD11_0225E4C8
MOD11_0225E4C8: ; 0x0225E4C8
	.byte 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00
	.byte 0x1B, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00
	.byte 0x0E, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00
	.byte 0x0D, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x0C, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00
	.byte 0x56, 0x00, 0x00, 0x00, 0x5D, 0x00, 0x00, 0x00, 0x77, 0x00, 0x00, 0x00, 0x73, 0x00, 0x00, 0x00
	.byte 0x82, 0x00, 0x00, 0x00, 0x8A, 0x00, 0x00, 0x00, 0x93, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x0C, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x8E, 0x00, 0x00, 0x00, 0x95, 0x00, 0x00, 0x00
	.byte 0x96, 0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0x00, 0x97, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00
	.byte 0x18, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00
	.byte 0x2B, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00
	.byte 0x34, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00
	.byte 0x44, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x4D, 0x00, 0x00, 0x00
	.byte 0x4E, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x51, 0x00, 0x00, 0x00
	.byte 0x52, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00
	.byte 0x59, 0x00, 0x00, 0x00, 0x5B, 0x00, 0x00, 0x00, 0x5C, 0x00, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00
	.byte 0x60, 0x00, 0x00, 0x00, 0x61, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00
	.byte 0x65, 0x00, 0x00, 0x00, 0x67, 0x00, 0x00, 0x00, 0x69, 0x00, 0x00, 0x00, 0x6A, 0x00, 0x00, 0x00
	.byte 0x6D, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x71, 0x00, 0x00, 0x00, 0x72, 0x00, 0x00, 0x00
	.byte 0x78, 0x00, 0x00, 0x00, 0x7A, 0x00, 0x00, 0x00, 0x7B, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00
	.byte 0x7D, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00
	.byte 0x83, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x86, 0x00, 0x00, 0x00, 0x87, 0x00, 0x00, 0x00
	.byte 0x8C, 0x00, 0x00, 0x00, 0x8D, 0x00, 0x00, 0x00, 0x8F, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0x00
	.byte 0x9A, 0x00, 0x00, 0x00, 0x9B, 0x00, 0x00, 0x00, 0x9C, 0x00, 0x00, 0x00, 0x9E, 0x00, 0x00, 0x00
	.byte 0x9F, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0xA1, 0x00, 0x00, 0x00, 0xA2, 0x00, 0x00, 0x00
	.byte 0xA3, 0x00, 0x00, 0x00, 0xA4, 0x00, 0x00, 0x00, 0xA5, 0x00, 0x00, 0x00, 0xA6, 0x00, 0x00, 0x00
	.byte 0xA7, 0x00, 0x00, 0x00, 0xA8, 0x00, 0x00, 0x00, 0xAA, 0x00, 0x00, 0x00, 0xAB, 0x00, 0x00, 0x00
	.byte 0xAD, 0x00, 0x00, 0x00, 0xAF, 0x00, 0x00, 0x00, 0xDA, 0x00, 0x00, 0x00, 0xDB, 0x00, 0x00, 0x00
	.byte 0xDC, 0x00, 0x00, 0x00, 0xE2, 0x00, 0x00, 0x00, 0xF6, 0x00, 0x00, 0x00, 0xF7, 0x00, 0x00, 0x00
	.byte 0xF8, 0x00, 0x00, 0x00, 0xF9, 0x00, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x05, 0x01, 0x00, 0x00
	.byte 0x76, 0x00, 0x00, 0x00

	.section .data

	.global MOD11_0225FF84
MOD11_0225FF84: ; 0x0225FF84
	.byte 0x2D, 0x00, 0x2E, 0x00, 0x2F, 0x00, 0x30, 0x00, 0x67, 0x00, 0xAD, 0x00
	.byte 0xFD, 0x00, 0x3F, 0x01, 0x40, 0x01, 0x30, 0x01, 0x95, 0x01, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00
