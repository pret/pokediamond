    .include "asm/macros.inc"
    .include "global.inc"

	.extern gGameLanguage
	.extern gGameVersion

	.section .rodata

	.global UNK_020F7ECC
UNK_020F7ECC: ; 0x020F7ECC
	.short 0x002D, 0x005F
	.short 0x0014, 0x0050

	.global UNK_020F7ED4
UNK_020F7ED4: ; 0x020F7ED4
	.byte 0x05, 0x03, 0x02
	.byte 0x05, 0x03, 0x02
	.byte 0x01, 0x01, 0x00
	.byte 0x03, 0x02, 0x01
	.byte 0x01, 0x01, 0x00
	.byte 0x01, 0x01, 0x01
	.byte 0xFF, 0xFF, 0xFF
	.byte 0xFB, 0xFB, 0xF6
	.byte 0xFB, 0xFB, 0xF6
	.byte 0x03, 0x02, 0x01

	.global sLegendaryMonsList
sLegendaryMonsList: ; 0x020F7EF2
	.short 0x0096 ; MEWTWO
	.short 0x0097 ; MEW
	.short 0x00FA ; LUGIA
	.short 0x00F9 ; HO-OH
	.short 0x00FB ; CELEBI
	.short 0x017E ; KYOGRE
	.short 0x017F ; GROUDON
	.short 0x0180 ; RAYQUAZA
	.short 0x0181 ; JIRACHI
	.short 0x0182 ; DEOXYS
	.short 0x01E3 ; DIALGA
	.short 0x01E4 ; PALKIA
	.short 0x01E7 ; GIRATINA
	.short 0x01E9 ; PHIONE
	.short 0x01EA ; MANAPHY
	.short 0x01EB ; DARKRAI
	.short 0x01EC ; SHAYMIN
	.short 0x01ED ; ARCEUS

	.global UNK_020F7F16
UNK_020F7F16: ; 0x020F7F16
	.byte  0,  0,  0,  0,  0
	.byte  1,  0,  0,  0, -1
	.byte  1,  0, -1,  0,  0
	.byte  1, -1,  0,  0,  0
	.byte  1,  0,  0, -1,  0
	.byte -1,  0,  0,  0,  1
	.byte  0,  0,  0,  0,  0
	.byte  0,  0, -1,  0,  1
	.byte  0, -1,  0,  0,  1
	.byte  0,  0,  0, -1,  1
	.byte -1,  0,  1,  0,  0
	.byte  0,  0,  1,  0, -1
	.byte  0,  0,  0,  0,  0
	.byte  0, -1,  1,  0,  0
	.byte  0,  0,  1, -1,  0
	.byte -1,  1,  0,  0,  0
	.byte  0,  1,  0,  0, -1
	.byte  0,  1, -1,  0,  0
	.byte  0,  0,  0,  0,  0
	.byte  0,  1,  0, -1,  0
	.byte -1,  0,  0,  1,  0
	.byte  0,  0,  0,  1, -1
	.byte  0,  0, -1,  1,  0
	.byte  0, -1,  0,  1,  0
	.byte  0,  0,  0,  0,  0

	.global UNK_020F7F93
UNK_020F7F93: ; 0x020F7F93
	.byte  0,  0,  0,  0,  0
	.byte  1, -1,  0,  0,  0
	.byte  1,  0, -1,  0,  0
	.byte  1,  0,  0, -1,  0
	.byte  1,  0,  0,  0, -1
	.byte -1,  1,  0,  0,  0
	.byte  0,  0,  0,  0,  0
	.byte  0,  1, -1,  0,  0
	.byte  0,  1,  0, -1,  0
	.byte  0,  1,  0,  0, -1
	.byte -1,  0,  1,  0,  0
	.byte  0, -1,  1,  0,  0
	.byte  0,  0,  0,  0,  0
	.byte  0,  0,  1, -1,  0
	.byte  0,  0,  1,  0, -1
	.byte -1,  0,  0,  1,  0
	.byte  0, -1,  0,  1,  0
	.byte  0,  0, -1,  1,  0
	.byte  0,  0,  0,  0,  0
	.byte  0,  0,  0,  1, -1
	.byte -1,  0,  0,  0,  1
	.byte  0, -1,  0,  0,  1
	.byte  0,  0, -1,  0,  1
	.byte  0,  0,  0, -1,  1
	.byte  0,  0,  0,  0,  0

	.section .data

	.global UNK_02105FC8
UNK_02105FC8: ; 0x02105FC8
	.asciz "poketool/personal/pms.narc"

	.section .bss

	.global UNK_021C5AC0
UNK_021C5AC0: ; 0x021C5AC0
	.space 0x194

	.text

	thumb_func_start ZeroMonData
ZeroMonData: ; 0x02066978
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r4, #0x0
	mov r2, #0xec
	bl MIi_CpuClearFast
	add r0, r4, #0x0
	ldrh r2, [r4, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3A4
	add r0, r4, #0x0
	ldr r2, [r4, #0x0]
	add r0, #0x88
	mov r1, #0x64
	bl FUN_0206A3A4
	pop {r4, pc}

	thumb_func_start FUN_020669A0
FUN_020669A0: ; 0x020669A0
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r4, #0x0
	mov r2, #0x88
	bl MIi_CpuClearFast
	add r0, r4, #0x0
	ldrh r2, [r4, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3A4
	pop {r4, pc}

	thumb_func_start FUN_020669BC
FUN_020669BC: ; 0x020669BC
	mov r0, #0xec
	bx lr

	thumb_func_start FUN_020669C0
FUN_020669C0: ; 0x020669C0
	push {r4, lr}
	mov r1, #0xec
	bl AllocFromHeap
	add r4, r0, #0x0
	bl ZeroMonData
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020669D4
FUN_020669D4: ; 0x020669D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldrh r0, [r5, #0x4]
	mov r4, #0x0
	lsl r1, r0, #0x1f
	lsr r1, r1, #0x1f
	bne _02066A1A
	lsl r0, r0, #0x1e
	mov r4, #0x1
	lsr r0, r0, #0x1f
	beq _020669EE
	bl ErrorHandling
_020669EE:
	ldrh r1, [r5, #0x4]
	mov r0, #0x1
	bic r1, r0
	mov r0, #0x1
	orr r0, r1
	strh r0, [r5, #0x4]
	ldrh r1, [r5, #0x4]
	mov r0, #0x2
	orr r0, r1
	strh r0, [r5, #0x4]
	add r0, r5, #0x0
	ldr r2, [r5, #0x0]
	add r0, #0x88
	mov r1, #0x64
	bl FUN_0206A3D0
	add r0, r5, #0x0
	ldrh r2, [r5, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3D0
_02066A1A:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02066A20
FUN_02066A20: ; 0x02066A20
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldrh r2, [r5, #0x4]
	mov r4, #0x0
	lsl r0, r2, #0x1f
	lsr r0, r0, #0x1f
	cmp r0, #0x1
	bne _02066A68
	cmp r1, #0x1
	bne _02066A68
	mov r0, #0x1
	bic r2, r0
	strh r2, [r5, #0x4]
	ldrh r1, [r5, #0x4]
	mov r0, #0x2
	mov r4, #0x1
	bic r1, r0
	strh r1, [r5, #0x4]
	add r0, r5, #0x0
	ldr r2, [r5, #0x0]
	add r0, #0x88
	mov r1, #0x64
	bl FUN_0206A3A4
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3F8
	strh r0, [r5, #0x6]
	add r0, r5, #0x0
	ldrh r2, [r5, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3A4
_02066A68:
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02066A6C
FUN_02066A6C: ; 0x02066A6C
	push {r4, lr}
	add r2, r0, #0x0
	ldrh r1, [r2, #0x4]
	mov r4, #0x0
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1f
	bne _02066A8E
	mov r0, #0x2
	orr r0, r1
	strh r0, [r2, #0x4]
	add r0, r2, #0x0
	ldrh r2, [r2, #0x6]
	add r0, #0x8
	mov r1, #0x80
	mov r4, #0x1
	bl FUN_0206A3D0
_02066A8E:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02066A94
FUN_02066A94: ; 0x02066A94
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldrh r2, [r5, #0x4]
	mov r4, #0x0
	lsl r0, r2, #0x1e
	lsr r0, r0, #0x1f
	cmp r0, #0x1
	bne _02066AC8
	cmp r1, #0x1
	bne _02066AC8
	mov r0, #0x2
	bic r2, r0
	add r0, r5, #0x0
	strh r2, [r5, #0x4]
	add r0, #0x8
	mov r1, #0x80
	mov r4, #0x1
	bl FUN_0206A3F8
	strh r0, [r5, #0x6]
	add r0, r5, #0x0
	ldrh r2, [r5, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3A4
_02066AC8:
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start CreateMon
CreateMon: ; 0x02066ACC
	push {r0-r3}
	push {r3-r6, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r3, #0x0
	bl ZeroMonData
	ldr r0, [sp, #0x50]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x54]
	add r3, r6, #0x0
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x58]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x5c]
	str r0, [sp, #0xc]
	ldr r2, [sp, #0x48]
	add r0, r5, #0x0
	bl CreateBoxMon
	add r0, r5, #0x0
	add r0, #0x88
	mov r1, #0x64
	mov r2, #0x0
	bl FUN_0206A3A4
	add r0, r5, #0x0
	ldr r2, [r5, #0x0]
	add r0, #0x88
	mov r1, #0x64
	bl FUN_0206A3A4
	add r0, r5, #0x0
	mov r1, #0xa0
	add r2, sp, #0x48
	bl FUN_02067830
	mov r0, #0x0
	bl FUN_020256BC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xa9
	add r2, r4, #0x0
	bl FUN_02067830
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x0
	str r0, [sp, #0x10]
	add r0, r5, #0x0
	mov r1, #0xa1
	add r2, sp, #0x10
	bl FUN_02067830
	mov r0, #0x0
	add r1, sp, #0x14
	mov r2, #0x18
	bl MIi_CpuClearFast
	add r0, r5, #0x0
	mov r1, #0xaa
	add r2, sp, #0x14
	bl FUN_02067830
	add r0, r5, #0x0
	bl FUN_02066ED8
	add sp, #0x2c
	pop {r3-r6}
	pop {r3}
	add sp, #0x10
	bx r3

	thumb_func_start CreateBoxMon
CreateBoxMon: ; 0x02066B64
	push {r0-r3}
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl FUN_020669A0
	add r0, r5, #0x0
	bl FUN_02066A6C
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	bne _02066B8E
	bl rand_LC
	add r4, r0, #0x0
	bl rand_LC
	lsl r0, r0, #0x10
	orr r0, r4
	str r0, [sp, #0x34]
_02066B8E:
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, sp, #0x34
	bl FUN_02067960
	ldr r0, [sp, #0x38]
	cmp r0, #0x2
	bne _02066BD6
	ldr r7, _02066D84 ; =0xFFFF0000
	add r6, r7, #0x0
_02066BA2:
	bl rand_LC
	add r4, r0, #0x0
	bl rand_LC
	ldr r1, [sp, #0x34]
	lsl r0, r0, #0x10
	add r3, r4, #0x0
	orr r3, r0
	lsl r0, r1, #0x10
	lsr r2, r0, #0x10
	add r0, r1, #0x0
	and r0, r7
	lsr r1, r0, #0x10
	add r0, r3, #0x0
	str r3, [sp, #0x3c]
	and r0, r6
	lsl r3, r3, #0x10
	lsr r0, r0, #0x10
	lsr r3, r3, #0x10
	eor r0, r3
	eor r0, r1
	eor r0, r2
	cmp r0, #0x8
	blo _02066BA2
	b _02066BDE
_02066BD6:
	cmp r0, #0x1
	beq _02066BDE
	mov r0, #0x0
	str r0, [sp, #0x3c]
_02066BDE:
	add r0, r5, #0x0
	mov r1, #0x7
	add r2, sp, #0x3c
	bl FUN_02067960
	ldr r2, _02066D88 ; =gGameLanguage
	add r0, r5, #0x0
	mov r1, #0xc
	bl FUN_02067960
	add r0, r5, #0x0
	mov r1, #0x5
	add r2, sp, #0x24
	bl FUN_02067960
	add r0, r5, #0x0
	mov r1, #0xb2
	mov r2, #0x0
	bl FUN_02067960
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0x28]
	bl FUN_02068758
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x8
	add r2, sp, #0x8
	bl FUN_02067960
	ldr r0, [sp, #0x24]
	mov r1, #0x14
	bl FUN_02068678
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x9
	add r2, sp, #0x8
	bl FUN_02067960
	add r0, r5, #0x0
	mov r1, #0x9b
	add r2, sp, #0x28
	bl FUN_02067960
	ldr r2, _02066D8C ; =gGameVersion
	add r0, r5, #0x0
	mov r1, #0x79
	bl FUN_02067960
	mov r0, #0x4
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x9a
	add r2, sp, #0x8
	bl FUN_02067960
	ldr r0, [sp, #0x2c]
	cmp r0, #0x20
	bge _02066C94
	add r0, r5, #0x0
	mov r1, #0x46
	add r2, sp, #0x2c
	bl FUN_02067960
	add r0, r5, #0x0
	mov r1, #0x47
	add r2, sp, #0x2c
	bl FUN_02067960
	add r0, r5, #0x0
	mov r1, #0x48
	add r2, sp, #0x2c
	bl FUN_02067960
	add r0, r5, #0x0
	mov r1, #0x49
	add r2, sp, #0x2c
	bl FUN_02067960
	add r0, r5, #0x0
	mov r1, #0x4a
	add r2, sp, #0x2c
	bl FUN_02067960
	add r0, r5, #0x0
	mov r1, #0x4b
	add r2, sp, #0x2c
	bl FUN_02067960
	b _02066D18
_02066C94:
	bl rand_LC
	mov r1, #0x1f
	str r0, [sp, #0x8]
	and r0, r1
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r1, #0x46
	add r2, sp, #0x4
	bl FUN_02067960
	mov r0, #0x3e
	ldr r1, [sp, #0x8]
	lsl r0, r0, #0x4
	and r0, r1
	lsr r0, r0, #0x5
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r1, #0x47
	add r2, sp, #0x4
	bl FUN_02067960
	mov r0, #0x1f
	ldr r1, [sp, #0x8]
	lsl r0, r0, #0xa
	and r0, r1
	lsr r0, r0, #0xa
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r1, #0x48
	add r2, sp, #0x4
	bl FUN_02067960
	bl rand_LC
	mov r1, #0x1f
	str r0, [sp, #0x8]
	and r0, r1
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r1, #0x49
	add r2, sp, #0x4
	bl FUN_02067960
	mov r0, #0x3e
	ldr r1, [sp, #0x8]
	lsl r0, r0, #0x4
	and r0, r1
	lsr r0, r0, #0x5
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r1, #0x4a
	add r2, sp, #0x4
	bl FUN_02067960
	mov r0, #0x1f
	ldr r1, [sp, #0x8]
	lsl r0, r0, #0xa
	and r0, r1
	lsr r0, r0, #0xa
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r1, #0x4b
	add r2, sp, #0x4
	bl FUN_02067960
_02066D18:
	ldr r0, [sp, #0x24]
	mov r1, #0x18
	bl FUN_02068678
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x24]
	mov r1, #0x19
	bl FUN_02068678
	str r0, [sp, #0x4]
	cmp r0, #0x0
	beq _02066D50
	ldr r1, [sp, #0x34]
	mov r0, #0x1
	tst r0, r1
	beq _02066D44
	add r0, r5, #0x0
	mov r1, #0xa
	add r2, sp, #0x4
	bl FUN_02067960
	b _02066D5A
_02066D44:
	add r0, r5, #0x0
	mov r1, #0xa
	add r2, sp, #0x8
	bl FUN_02067960
	b _02066D5A
_02066D50:
	add r0, r5, #0x0
	mov r1, #0xa
	add r2, sp, #0x8
	bl FUN_02067960
_02066D5A:
	add r0, r5, #0x0
	bl FUN_020689E8
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x6f
	add r2, sp, #0x8
	bl FUN_02067960
	add r0, r5, #0x0
	bl FUN_020695F4
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02066A94
	add sp, #0xc
	pop {r4-r7}
	pop {r3}
	add sp, #0x10
	bx r3
	.balign 4
_02066D84: .word 0xFFFF0000
_02066D88: .word gGameLanguage
_02066D8C: .word gGameVersion

	thumb_func_start CreateMonWithNature
CreateMonWithNature: ; 0x02066D90
	push {r3-r7, lr}
	sub sp, #0x18
	str r2, [sp, #0x10]
	str r3, [sp, #0x14]
	ldr r4, [sp, #0x30]
	add r6, r0, #0x0
	add r7, r1, #0x0
_02066D9E:
	bl rand_LC
	add r5, r0, #0x0
	bl rand_LC
	lsl r0, r0, #0x10
	orr r5, r0
	add r0, r5, #0x0
	bl GetNatureFromPersonality
	cmp r4, r0
	bne _02066D9E
	mov r0, #0x1
	str r0, [sp, #0x0]
	str r5, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x14]
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl CreateMon
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02066DD4
FUN_02066DD4: ; 0x02066DD4
	push {r4-r7, lr}
	sub sp, #0x24
	str r1, [sp, #0x14]
	str r2, [sp, #0x18]
	str r3, [sp, #0x1c]
	str r0, [sp, #0x10]
	add r0, sp, #0x28
	ldrb r0, [r0, #0x18]
	ldr r6, [sp, #0x38]
	ldr r7, [sp, #0x3c]
	cmp r0, #0x0
	beq _02066E4C
	cmp r0, #0x1d
	bhs _02066E4C
	sub r0, r0, #0x1
	str r0, [sp, #0x20]
_02066DF4:
	bl rand_LC
	add r4, r0, #0x0
	bl rand_LC
	lsl r0, r0, #0x10
	orr r4, r0
	mov r3, #0x3
	lsl r3, r3, #0x10
	and r3, r4
	mov r0, #0x3
	add r2, r4, #0x0
	and r2, r0
	lsl r0, r0, #0x8
	and r0, r4
	lsr r1, r0, #0x6
	mov r0, #0x3
	lsl r0, r0, #0x18
	and r0, r4
	lsr r0, r0, #0x12
	lsr r3, r3, #0xc
	orr r0, r3
	orr r0, r1
	orr r0, r2
	mov r1, #0x1c
	bl _u32_div_f
	lsl r0, r1, #0x10
	lsr r5, r0, #0x10
	add r0, r4, #0x0
	bl GetNatureFromPersonality
	cmp r7, r0
	bne _02066DF4
	ldr r0, [sp, #0x14]
	add r1, r4, #0x0
	bl FUN_02068A20
	cmp r6, r0
	bne _02066DF4
	ldr r0, [sp, #0x20]
	cmp r5, r0
	bne _02066DF4
	b _02066E58
_02066E4C:
	ldr r0, [sp, #0x14]
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02066E74
	add r4, r0, #0x0
_02066E58:
	mov r0, #0x1
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x18]
	ldr r3, [sp, #0x1c]
	bl CreateMon
	add sp, #0x24
	pop {r4-r7, pc}

	thumb_func_start FUN_02066E74
FUN_02066E74: ; 0x02066E74
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r1, #0x12
	add r4, r2, #0x0
	bl FUN_02068678
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	beq _02066EA0
	cmp r0, #0xfe
	beq _02066EA0
	cmp r0, #0xff
	beq _02066EA0
	cmp r5, #0x0
	bne _02066EA0
	mov r1, #0x19
	bl _s32_div_f
	add r1, r0, #0x1
	mov r0, #0x19
	mul r0, r1
	add r4, r0, r4
_02066EA0:
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02066EA4
FUN_02066EA4: ; 0x02066EA4
	push {r0-r3}
	push {r4, lr}
	sub sp, #0x10
	mov r3, #0x1
	str r3, [sp, #0x0]
	ldr r3, [sp, #0x28]
	add r4, r0, #0x0
	str r3, [sp, #0x4]
	mov r3, #0x0
	str r3, [sp, #0x8]
	str r3, [sp, #0xc]
	bl CreateMon
	add r0, r4, #0x0
	mov r1, #0xae
	add r2, sp, #0x24
	bl FUN_02067830
	add r0, r4, #0x0
	bl FUN_02066ED8
	add sp, #0x10
	pop {r4}
	pop {r3}
	add sp, #0x10
	bx r3

	thumb_func_start FUN_02066ED8
FUN_02066ED8: ; 0x02066ED8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020669D4
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020687C0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r1, #0xa0
	add r2, sp, #0x0
	bl FUN_02067830
	add r0, r5, #0x0
	bl FUN_02066F04
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02066A20
	pop {r3-r5, pc}

	thumb_func_start FUN_02066F04
FUN_02066F04: ; 0x02066F04
	push {r3-r7, lr}
	sub sp, #0x58
	add r5, r0, #0x0
	bl FUN_020669D4
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl FUN_020671BC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xa3
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x2c]
	add r0, r5, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x54]
	add r0, r5, #0x0
	mov r1, #0x46
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x30]
	add r0, r5, #0x0
	mov r1, #0xd
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x34]
	add r0, r5, #0x0
	mov r1, #0x47
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x28]
	add r0, r5, #0x0
	mov r1, #0xe
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x14]
	add r0, r5, #0x0
	mov r1, #0x48
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x24]
	add r0, r5, #0x0
	mov r1, #0xf
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x10]
	add r0, r5, #0x0
	mov r1, #0x49
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x20]
	add r0, r5, #0x0
	mov r1, #0x10
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	mov r1, #0x4a
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x1c]
	add r0, r5, #0x0
	mov r1, #0x11
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x4b
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x18]
	add r0, r5, #0x0
	mov r1, #0x12
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x38]
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	add r7, r0, #0x0
	mov r0, #0x0
	mov r1, #0x2c
	bl AllocFromHeap
	add r6, r0, #0x0
	ldr r1, [sp, #0x38]
	add r0, r7, #0x0
	add r2, r6, #0x0
	bl FUN_0206A380
	mov r0, #0x49
	lsl r0, r0, #0x2
	cmp r7, r0
	bne _02066FFC
	mov r0, #0x1
	b _0206701E
_02066FFC:
	ldr r0, [sp, #0x34]
	asr r0, r0, #0x1
	lsr r1, r0, #0x1e
	ldr r0, [sp, #0x34]
	add r1, r0, r1
	asr r0, r1, #0x2
	ldrb r1, [r6, #0x0]
	lsl r2, r1, #0x1
	ldr r1, [sp, #0x30]
	add r1, r1, r2
	add r0, r0, r1
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	add r0, r4, r0
	add r0, #0xa
_0206701E:
	str r0, [sp, #0x50]
	add r0, r5, #0x0
	mov r1, #0xa3
	add r2, sp, #0x50
	bl FUN_02067830
	ldr r0, [sp, #0x14]
	asr r0, r0, #0x1
	lsr r1, r0, #0x1e
	ldr r0, [sp, #0x14]
	add r1, r0, r1
	asr r0, r1, #0x2
	ldrb r1, [r6, #0x1]
	lsl r2, r1, #0x1
	ldr r1, [sp, #0x28]
	add r1, r1, r2
	add r0, r0, r1
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	add r0, r0, #0x5
	str r0, [sp, #0x4c]
	add r0, r5, #0x0
	bl FUN_02068854
	ldr r1, [sp, #0x4c]
	mov r2, #0x1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_02068894
	str r0, [sp, #0x4c]
	add r0, r5, #0x0
	mov r1, #0xa4
	add r2, sp, #0x4c
	bl FUN_02067830
	ldr r0, [sp, #0x10]
	asr r0, r0, #0x1
	lsr r1, r0, #0x1e
	ldr r0, [sp, #0x10]
	add r1, r0, r1
	asr r0, r1, #0x2
	ldrb r1, [r6, #0x2]
	lsl r2, r1, #0x1
	ldr r1, [sp, #0x24]
	add r1, r1, r2
	add r0, r0, r1
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	add r0, r0, #0x5
	str r0, [sp, #0x48]
	add r0, r5, #0x0
	bl FUN_02068854
	ldr r1, [sp, #0x48]
	mov r2, #0x2
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_02068894
	str r0, [sp, #0x48]
	add r0, r5, #0x0
	mov r1, #0xa5
	add r2, sp, #0x48
	bl FUN_02067830
	ldr r0, [sp, #0xc]
	asr r0, r0, #0x1
	lsr r1, r0, #0x1e
	ldr r0, [sp, #0xc]
	add r1, r0, r1
	asr r0, r1, #0x2
	ldrb r1, [r6, #0x3]
	lsl r2, r1, #0x1
	ldr r1, [sp, #0x20]
	add r1, r1, r2
	add r0, r0, r1
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	add r0, r0, #0x5
	str r0, [sp, #0x44]
	add r0, r5, #0x0
	bl FUN_02068854
	ldr r1, [sp, #0x44]
	mov r2, #0x3
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_02068894
	str r0, [sp, #0x44]
	add r0, r5, #0x0
	mov r1, #0xa6
	add r2, sp, #0x44
	bl FUN_02067830
	ldr r0, [sp, #0x8]
	asr r0, r0, #0x1
	lsr r1, r0, #0x1e
	ldr r0, [sp, #0x8]
	add r1, r0, r1
	asr r0, r1, #0x2
	ldrb r1, [r6, #0x4]
	lsl r2, r1, #0x1
	ldr r1, [sp, #0x1c]
	add r1, r1, r2
	add r0, r0, r1
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	add r0, r0, #0x5
	str r0, [sp, #0x40]
	add r0, r5, #0x0
	bl FUN_02068854
	ldr r1, [sp, #0x40]
	mov r2, #0x4
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_02068894
	str r0, [sp, #0x40]
	add r0, r5, #0x0
	mov r1, #0xa7
	add r2, sp, #0x40
	bl FUN_02067830
	ldr r0, [sp, #0x4]
	asr r0, r0, #0x1
	lsr r1, r0, #0x1e
	ldr r0, [sp, #0x4]
	add r1, r0, r1
	asr r0, r1, #0x2
	ldrb r1, [r6, #0x5]
	lsl r2, r1, #0x1
	ldr r1, [sp, #0x18]
	add r1, r1, r2
	add r0, r0, r1
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	add r0, r0, #0x5
	str r0, [sp, #0x3c]
	add r0, r5, #0x0
	bl FUN_02068854
	ldr r1, [sp, #0x3c]
	mov r2, #0x5
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_02068894
	str r0, [sp, #0x3c]
	add r0, r5, #0x0
	mov r1, #0xa8
	add r2, sp, #0x3c
	bl FUN_02067830
	add r0, r6, #0x0
	bl FreeToHeap
	ldr r1, [sp, #0x54]
	cmp r1, #0x0
	bne _0206717C
	ldr r0, [sp, #0x2c]
	cmp r0, #0x0
	bne _020671A0
_0206717C:
	mov r0, #0x49
	lsl r0, r0, #0x2
	cmp r7, r0
	bne _0206718A
	mov r0, #0x1
	str r0, [sp, #0x54]
	b _020671A0
_0206718A:
	cmp r1, #0x0
	bne _02067194
	ldr r0, [sp, #0x50]
	str r0, [sp, #0x54]
	b _020671A0
_02067194:
	ldr r1, [sp, #0x50]
	ldr r0, [sp, #0x2c]
	ldr r2, [sp, #0x54]
	sub r0, r1, r0
	add r0, r2, r0
	str r0, [sp, #0x54]
_020671A0:
	ldr r0, [sp, #0x54]
	cmp r0, #0x0
	beq _020671B0
	add r0, r5, #0x0
	mov r1, #0xa2
	add r2, sp, #0x54
	bl FUN_02067830
_020671B0:
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02066A20
	add sp, #0x58
	pop {r3-r7, pc}

	thumb_func_start FUN_020671BC
FUN_020671BC: ; 0x020671BC
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldrh r0, [r5, #0x4]
	add r4, r1, #0x0
	add r6, r2, #0x0
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bne _02067204
	add r0, r5, #0x0
	ldr r2, [r5, #0x0]
	add r0, #0x88
	mov r1, #0x64
	bl FUN_0206A3D0
	add r0, r5, #0x0
	ldrh r2, [r5, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3D0
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3F8
	ldrh r1, [r5, #0x6]
	cmp r0, r1
	beq _02067204
	cmp r0, r1
	beq _020671FC
	bl ErrorHandling
_020671FC:
	ldrh r1, [r5, #0x4]
	mov r0, #0x4
	orr r0, r1
	strh r0, [r5, #0x4]
_02067204:
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl GetMonData
	add r4, r0, #0x0
	ldrh r0, [r5, #0x4]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bne _02067230
	add r0, r5, #0x0
	ldr r2, [r5, #0x0]
	add r0, #0x88
	mov r1, #0x64
	bl FUN_0206A3A4
	add r0, r5, #0x0
	ldrh r2, [r5, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3A4
_02067230:
	add r0, r4, #0x0
	pop {r4-r6, pc}

	thumb_func_start GetMonData
GetMonData: ; 0x02067234
	push {r3, lr}
	add r3, r1, #0x0
	sub r3, #0x9f
	cmp r3, #0xb
	bhi _020672B6
	add r3, r3, r3
	add r3, pc
	ldrh r3, [r3, #0x6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_0206724A: ; jump table (using 16-bit offset)
	.short _02067262 - _0206724A - 2; case 0
	.short _02067268 - _0206724A - 2; case 1
	.short _0206726E - _0206724A - 2; case 2
	.short _02067274 - _0206724A - 2; case 3
	.short _0206727A - _0206724A - 2; case 4
	.short _02067280 - _0206724A - 2; case 5
	.short _02067286 - _0206724A - 2; case 6
	.short _0206728C - _0206724A - 2; case 7
	.short _02067292 - _0206724A - 2; case 8
	.short _02067298 - _0206724A - 2; case 9
	.short _0206729E - _0206724A - 2; case 10
	.short _020672AA - _0206724A - 2; case 11
_02067262:
	add r0, #0x88
	ldr r0, [r0, #0x0]
	pop {r3, pc}
_02067268:
	add r0, #0x8c
	ldrb r0, [r0, #0x0]
	pop {r3, pc}
_0206726E:
	add r0, #0x8d
	ldrb r0, [r0, #0x0]
	pop {r3, pc}
_02067274:
	add r0, #0x8e
	ldrh r0, [r0, #0x0]
	pop {r3, pc}
_0206727A:
	add r0, #0x90
	ldrh r0, [r0, #0x0]
	pop {r3, pc}
_02067280:
	add r0, #0x92
	ldrh r0, [r0, #0x0]
	pop {r3, pc}
_02067286:
	add r0, #0x94
	ldrh r0, [r0, #0x0]
	pop {r3, pc}
_0206728C:
	add r0, #0x96
	ldrh r0, [r0, #0x0]
	pop {r3, pc}
_02067292:
	add r0, #0x98
	ldrh r0, [r0, #0x0]
	pop {r3, pc}
_02067298:
	add r0, #0x9a
	ldrh r0, [r0, #0x0]
	pop {r3, pc}
_0206729E:
	add r0, #0x9c
	add r1, r2, #0x0
	bl FUN_020256D0
	mov r0, #0x1
	pop {r3, pc}
_020672AA:
	add r0, #0xd4
	add r1, r2, #0x0
	bl FUN_02029C74
	mov r0, #0x1
	pop {r3, pc}
_020672B6:
	bl GetBoxMonData
	pop {r3, pc}

	thumb_func_start FUN_020672BC
FUN_020672BC: ; 0x020672BC
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldrh r0, [r5, #0x4]
	add r4, r1, #0x0
	add r6, r2, #0x0
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bne _020672F8
	ldrh r2, [r5, #0x6]
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3D0
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3F8
	ldrh r1, [r5, #0x6]
	cmp r0, r1
	beq _020672F8
	cmp r0, r1
	beq _020672F0
	bl ErrorHandling
_020672F0:
	ldrh r1, [r5, #0x4]
	mov r0, #0x4
	orr r0, r1
	strh r0, [r5, #0x4]
_020672F8:
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl GetBoxMonData
	add r4, r0, #0x0
	ldrh r0, [r5, #0x4]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bne _02067318
	ldrh r2, [r5, #0x6]
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3A4
_02067318:
	add r0, r4, #0x0
	pop {r4-r6, pc}

	thumb_func_start GetBoxMonData
GetBoxMonData: ; 0x0206731C
	push {r4-r7, lr}
	sub sp, #0xc
	str r1, [sp, #0x4]
	add r1, r0, #0x0
	mov r4, #0x0
	str r2, [sp, #0x8]
	ldr r1, [r1, #0x0]
	str r0, [sp, #0x0]
	add r2, r4, #0x0
	bl GetSubstruct
	add r5, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r2, #0x1
	add r1, r0, #0x0
	ldr r1, [r1, #0x0]
	bl GetSubstruct
	add r6, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r2, #0x2
	add r1, r0, #0x0
	ldr r1, [r1, #0x0]
	bl GetSubstruct
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r2, #0x3
	add r1, r0, #0x0
	ldr r1, [r1, #0x0]
	bl GetSubstruct
	add r1, r0, #0x0
	ldr r0, [sp, #0x4]
	cmp r0, #0xb2
	bls _02067366
	b _020674D8
_02067366:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02067372: ; jump table (using 16-bit offset)
	.short _020674DC - _02067372 - 2; case 0
	.short _020674E2 - _02067372 - 2; case 1
	.short _020674EC - _02067372 - 2; case 2
	.short _020674F6 - _02067372 - 2; case 3
	.short _02067500 - _02067372 - 2; case 4
	.short _0206754C - _02067372 - 2; case 5
	.short _0206755E - _02067372 - 2; case 6
	.short _02067562 - _02067372 - 2; case 7
	.short _02067566 - _02067372 - 2; case 8
	.short _0206756A - _02067372 - 2; case 9
	.short _0206756E - _02067372 - 2; case 10
	.short _02067572 - _02067372 - 2; case 11
	.short _02067576 - _02067372 - 2; case 12
	.short _0206757A - _02067372 - 2; case 13
	.short _0206757E - _02067372 - 2; case 14
	.short _02067582 - _02067372 - 2; case 15
	.short _02067586 - _02067372 - 2; case 16
	.short _0206758A - _02067372 - 2; case 17
	.short _0206758E - _02067372 - 2; case 18
	.short _02067592 - _02067372 - 2; case 19
	.short _02067596 - _02067372 - 2; case 20
	.short _0206759A - _02067372 - 2; case 21
	.short _0206759E - _02067372 - 2; case 22
	.short _020675A2 - _02067372 - 2; case 23
	.short _020675A6 - _02067372 - 2; case 24
	.short _020675AA - _02067372 - 2; case 25
	.short _020675AA - _02067372 - 2; case 26
	.short _020675AA - _02067372 - 2; case 27
	.short _020675AA - _02067372 - 2; case 28
	.short _020675AA - _02067372 - 2; case 29
	.short _020675AA - _02067372 - 2; case 30
	.short _020675AA - _02067372 - 2; case 31
	.short _020675AA - _02067372 - 2; case 32
	.short _020675AA - _02067372 - 2; case 33
	.short _020675AA - _02067372 - 2; case 34
	.short _020675AA - _02067372 - 2; case 35
	.short _020675AA - _02067372 - 2; case 36
	.short _020675AA - _02067372 - 2; case 37
	.short _020675AA - _02067372 - 2; case 38
	.short _020675AA - _02067372 - 2; case 39
	.short _020675AA - _02067372 - 2; case 40
	.short _020675AA - _02067372 - 2; case 41
	.short _020675AA - _02067372 - 2; case 42
	.short _020675AA - _02067372 - 2; case 43
	.short _020675AA - _02067372 - 2; case 44
	.short _020675AA - _02067372 - 2; case 45
	.short _020675AA - _02067372 - 2; case 46
	.short _020675AA - _02067372 - 2; case 47
	.short _020675AA - _02067372 - 2; case 48
	.short _020675AA - _02067372 - 2; case 49
	.short _020675AA - _02067372 - 2; case 50
	.short _020675AA - _02067372 - 2; case 51
	.short _020675AA - _02067372 - 2; case 52
	.short _020675AA - _02067372 - 2; case 53
	.short _020675D0 - _02067372 - 2; case 54
	.short _020675D0 - _02067372 - 2; case 55
	.short _020675D0 - _02067372 - 2; case 56
	.short _020675D0 - _02067372 - 2; case 57
	.short _020675DC - _02067372 - 2; case 58
	.short _020675DC - _02067372 - 2; case 59
	.short _020675DC - _02067372 - 2; case 60
	.short _020675DC - _02067372 - 2; case 61
	.short _020675E8 - _02067372 - 2; case 62
	.short _020675E8 - _02067372 - 2; case 63
	.short _020675E8 - _02067372 - 2; case 64
	.short _020675E8 - _02067372 - 2; case 65
	.short _020675F4 - _02067372 - 2; case 66
	.short _020675F4 - _02067372 - 2; case 67
	.short _020675F4 - _02067372 - 2; case 68
	.short _020675F4 - _02067372 - 2; case 69
	.short _0206760C - _02067372 - 2; case 70
	.short _02067614 - _02067372 - 2; case 71
	.short _0206761C - _02067372 - 2; case 72
	.short _02067624 - _02067372 - 2; case 73
	.short _0206762C - _02067372 - 2; case 74
	.short _02067634 - _02067372 - 2; case 75
	.short _0206763C - _02067372 - 2; case 76
	.short _0206764E - _02067372 - 2; case 77
	.short _02067654 - _02067372 - 2; case 78
	.short _02067654 - _02067372 - 2; case 79
	.short _02067654 - _02067372 - 2; case 80
	.short _02067654 - _02067372 - 2; case 81
	.short _02067654 - _02067372 - 2; case 82
	.short _02067654 - _02067372 - 2; case 83
	.short _02067654 - _02067372 - 2; case 84
	.short _02067654 - _02067372 - 2; case 85
	.short _02067654 - _02067372 - 2; case 86
	.short _02067654 - _02067372 - 2; case 87
	.short _02067654 - _02067372 - 2; case 88
	.short _02067654 - _02067372 - 2; case 89
	.short _02067654 - _02067372 - 2; case 90
	.short _02067654 - _02067372 - 2; case 91
	.short _02067654 - _02067372 - 2; case 92
	.short _02067654 - _02067372 - 2; case 93
	.short _02067654 - _02067372 - 2; case 94
	.short _02067654 - _02067372 - 2; case 95
	.short _02067654 - _02067372 - 2; case 96
	.short _02067654 - _02067372 - 2; case 97
	.short _02067654 - _02067372 - 2; case 98
	.short _02067654 - _02067372 - 2; case 99
	.short _02067654 - _02067372 - 2; case 100
	.short _02067654 - _02067372 - 2; case 101
	.short _02067654 - _02067372 - 2; case 102
	.short _02067654 - _02067372 - 2; case 103
	.short _02067654 - _02067372 - 2; case 104
	.short _02067654 - _02067372 - 2; case 105
	.short _02067654 - _02067372 - 2; case 106
	.short _02067654 - _02067372 - 2; case 107
	.short _02067654 - _02067372 - 2; case 108
	.short _02067654 - _02067372 - 2; case 109
	.short _0206767C - _02067372 - 2; case 110
	.short _02067684 - _02067372 - 2; case 111
	.short _0206768C - _02067372 - 2; case 112
	.short _02067694 - _02067372 - 2; case 113
	.short _02067698 - _02067372 - 2; case 114
	.short _020674D8 - _02067372 - 2; case 115
	.short _0206769C - _02067372 - 2; case 116
	.short _020674D8 - _02067372 - 2; case 117
	.short _020676D0 - _02067372 - 2; case 118
	.short _020676CC - _02067372 - 2; case 119
	.short _020676FE - _02067372 - 2; case 120
	.short _02067702 - _02067372 - 2; case 121
	.short _02067706 - _02067372 - 2; case 122
	.short _02067706 - _02067372 - 2; case 123
	.short _02067706 - _02067372 - 2; case 124
	.short _02067706 - _02067372 - 2; case 125
	.short _02067706 - _02067372 - 2; case 126
	.short _02067706 - _02067372 - 2; case 127
	.short _02067706 - _02067372 - 2; case 128
	.short _02067706 - _02067372 - 2; case 129
	.short _02067706 - _02067372 - 2; case 130
	.short _02067706 - _02067372 - 2; case 131
	.short _02067706 - _02067372 - 2; case 132
	.short _02067706 - _02067372 - 2; case 133
	.short _02067706 - _02067372 - 2; case 134
	.short _02067706 - _02067372 - 2; case 135
	.short _02067706 - _02067372 - 2; case 136
	.short _02067706 - _02067372 - 2; case 137
	.short _02067706 - _02067372 - 2; case 138
	.short _02067706 - _02067372 - 2; case 139
	.short _02067706 - _02067372 - 2; case 140
	.short _02067706 - _02067372 - 2; case 141
	.short _02067706 - _02067372 - 2; case 142
	.short _0206772C - _02067372 - 2; case 143
	.short _02067746 - _02067372 - 2; case 144
	.short _0206774E - _02067372 - 2; case 145
	.short _02067752 - _02067372 - 2; case 146
	.short _02067756 - _02067372 - 2; case 147
	.short _0206775A - _02067372 - 2; case 148
	.short _0206775E - _02067372 - 2; case 149
	.short _02067762 - _02067372 - 2; case 150
	.short _02067766 - _02067372 - 2; case 151
	.short _0206776A - _02067372 - 2; case 152
	.short _0206776E - _02067372 - 2; case 153
	.short _02067772 - _02067372 - 2; case 154
	.short _02067776 - _02067372 - 2; case 155
	.short _0206777E - _02067372 - 2; case 156
	.short _02067786 - _02067372 - 2; case 157
	.short _0206778A - _02067372 - 2; case 158
	.short _020674D8 - _02067372 - 2; case 159
	.short _02067540 - _02067372 - 2; case 160
	.short _020674D8 - _02067372 - 2; case 161
	.short _020674D8 - _02067372 - 2; case 162
	.short _020674D8 - _02067372 - 2; case 163
	.short _020674D8 - _02067372 - 2; case 164
	.short _020674D8 - _02067372 - 2; case 165
	.short _020674D8 - _02067372 - 2; case 166
	.short _020674D8 - _02067372 - 2; case 167
	.short _020674D8 - _02067372 - 2; case 168
	.short _020674D8 - _02067372 - 2; case 169
	.short _020674D8 - _02067372 - 2; case 170
	.short _02067506 - _02067372 - 2; case 171
	.short _02067510 - _02067372 - 2; case 172
	.short _02067522 - _02067372 - 2; case 173
	.short _0206778E - _02067372 - 2; case 174
	.short _020677C0 - _02067372 - 2; case 175
	.short _020677D8 - _02067372 - 2; case 176
	.short _020677D8 - _02067372 - 2; case 177
	.short _02067810 - _02067372 - 2; case 178
_020674D8:
	mov r4, #0x0
	b _0206781A
_020674DC:
	ldr r0, [sp, #0x0]
	ldr r4, [r0, #0x0]
	b _0206781A
_020674E2:
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x4]
	lsl r0, r0, #0x1f
	lsr r4, r0, #0x1f
	b _0206781A
_020674EC:
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x4]
	lsl r0, r0, #0x1e
	lsr r4, r0, #0x1f
	b _0206781A
_020674F6:
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x4]
	lsl r0, r0, #0x1d
	lsr r4, r0, #0x1f
	b _0206781A
_02067500:
	ldr r0, [sp, #0x0]
	ldrh r4, [r0, #0x6]
	b _0206781A
_02067506:
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0206753A
	mov r4, #0x1
	b _0206781A
_02067510:
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x4]
	lsl r0, r0, #0x1d
	lsr r4, r0, #0x1f
	bne _0206753A
	ldr r0, [r6, #0x10]
	lsl r0, r0, #0x1
	lsr r4, r0, #0x1f
	b _0206781A
_02067522:
	ldrh r4, [r5, #0x0]
	cmp r4, #0x0
	beq _0206753A
	ldr r0, [r6, #0x10]
	lsl r0, r0, #0x1
	lsr r0, r0, #0x1f
	bne _0206753C
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x4]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	bne _0206753C
_0206753A:
	b _0206781A
_0206753C:
	ldr r4, _02067820 ; =0x000001EE
	b _0206781A
_02067540:
	ldrh r0, [r5, #0x0]
	ldr r1, [r5, #0x8]
	bl FUN_02068800
	add r4, r0, #0x0
	b _0206781A
_0206754C:
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x4]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	beq _0206755A
	ldr r4, _02067820 ; =0x000001EE
	b _0206781A
_0206755A:
	ldrh r4, [r5, #0x0]
	b _0206781A
_0206755E:
	ldrh r4, [r5, #0x2]
	b _0206781A
_02067562:
	ldr r4, [r5, #0x4]
	b _0206781A
_02067566:
	ldr r4, [r5, #0x8]
	b _0206781A
_0206756A:
	ldrb r4, [r5, #0xc]
	b _0206781A
_0206756E:
	ldrb r4, [r5, #0xd]
	b _0206781A
_02067572:
	ldrb r4, [r5, #0xe]
	b _0206781A
_02067576:
	ldrb r4, [r5, #0xf]
	b _0206781A
_0206757A:
	ldrb r4, [r5, #0x10]
	b _0206781A
_0206757E:
	ldrb r4, [r5, #0x11]
	b _0206781A
_02067582:
	ldrb r4, [r5, #0x12]
	b _0206781A
_02067586:
	ldrb r4, [r5, #0x13]
	b _0206781A
_0206758A:
	ldrb r4, [r5, #0x14]
	b _0206781A
_0206758E:
	ldrb r4, [r5, #0x15]
	b _0206781A
_02067592:
	ldrb r4, [r5, #0x16]
	b _0206781A
_02067596:
	ldrb r4, [r5, #0x17]
	b _0206781A
_0206759A:
	ldrb r4, [r5, #0x18]
	b _0206781A
_0206759E:
	ldrb r4, [r5, #0x19]
	b _0206781A
_020675A2:
	ldrb r4, [r5, #0x1a]
	b _0206781A
_020675A6:
	ldrb r4, [r5, #0x1b]
	b _0206781A
_020675AA:
	ldr r2, [sp, #0x4]
	mov r0, #0x1
	sub r2, #0x19
	add r1, r4, #0x0
	str r2, [sp, #0x4]
	bl _ll_shl
	ldr r2, [r5, #0x1c]
	add r3, r4, #0x0
	and r3, r1
	and r2, r0
	mov r1, #0x0
	mov r0, #0x0
	eor r1, r3
	eor r0, r2
	orr r0, r1
	beq _02067676
	mov r4, #0x1
	b _0206781A
_020675D0:
	ldr r0, [sp, #0x4]
	sub r0, #0x36
	str r0, [sp, #0x4]
	lsl r0, r0, #0x1
	ldrh r4, [r6, r0]
	b _0206781A
_020675DC:
	ldr r0, [sp, #0x4]
	sub r0, #0x3a
	str r0, [sp, #0x4]
	add r0, r6, r0
	ldrb r4, [r0, #0x8]
	b _0206781A
_020675E8:
	ldr r0, [sp, #0x4]
	sub r0, #0x3e
	str r0, [sp, #0x4]
	add r0, r6, r0
	ldrb r4, [r0, #0xc]
	b _0206781A
_020675F4:
	ldr r0, [sp, #0x4]
	sub r0, #0x42
	str r0, [sp, #0x4]
	ldr r1, [sp, #0x4]
	lsl r0, r0, #0x1
	add r1, r6, r1
	ldrh r0, [r6, r0]
	ldrb r1, [r1, #0xc]
	bl FUN_0206AB30
	add r4, r0, #0x0
	b _0206781A
_0206760C:
	ldr r0, [r6, #0x10]
	lsl r0, r0, #0x1b
	lsr r4, r0, #0x1b
	b _0206781A
_02067614:
	ldr r0, [r6, #0x10]
	lsl r0, r0, #0x16
	lsr r4, r0, #0x1b
	b _0206781A
_0206761C:
	ldr r0, [r6, #0x10]
	lsl r0, r0, #0x11
	lsr r4, r0, #0x1b
	b _0206781A
_02067624:
	ldr r0, [r6, #0x10]
	lsl r0, r0, #0xc
	lsr r4, r0, #0x1b
	b _0206781A
_0206762C:
	ldr r0, [r6, #0x10]
	lsl r0, r0, #0x7
	lsr r4, r0, #0x1b
	b _0206781A
_02067634:
	ldr r0, [r6, #0x10]
	lsl r0, r0, #0x2
	lsr r4, r0, #0x1b
	b _0206781A
_0206763C:
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x4]
	lsl r0, r0, #0x1d
	lsr r4, r0, #0x1f
	bne _02067676
	ldr r0, [r6, #0x10]
	lsl r0, r0, #0x1
	lsr r4, r0, #0x1f
	b _0206781A
_0206764E:
	ldr r0, [r6, #0x10]
	lsr r4, r0, #0x1f
	b _0206781A
_02067654:
	ldr r2, [sp, #0x4]
	mov r0, #0x1
	sub r2, #0x4e
	add r1, r4, #0x0
	str r2, [sp, #0x4]
	bl _ll_shl
	ldr r2, [r6, #0x14]
	add r3, r4, #0x0
	and r3, r1
	and r2, r0
	mov r1, #0x0
	mov r0, #0x0
	eor r1, r3
	eor r0, r2
	orr r0, r1
	bne _02067678
_02067676:
	b _0206781A
_02067678:
	mov r4, #0x1
	b _0206781A
_0206767C:
	ldrb r0, [r6, #0x18]
	lsl r0, r0, #0x1f
	lsr r4, r0, #0x1f
	b _0206781A
_02067684:
	ldrb r0, [r6, #0x18]
	lsl r0, r0, #0x1d
	lsr r4, r0, #0x1e
	b _0206781A
_0206768C:
	ldrb r0, [r6, #0x18]
	lsl r0, r0, #0x18
	lsr r4, r0, #0x1b
	b _0206781A
_02067694:
	ldrb r4, [r6, #0x19]
	b _0206781A
_02067698:
	ldrh r4, [r6, #0x1a]
	b _0206781A
_0206769C:
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x4]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	beq _020676B2
	ldr r0, _02067824 ; =0x000001EF
	ldr r2, [sp, #0x8]
	add r1, r4, #0x0
	bl FUN_0200A99C
	b _0206781A
_020676B2:
	ldr r1, [sp, #0x8]
_020676B4:
	ldrh r0, [r7, #0x0]
	add r4, r4, #0x1
	add r7, r7, #0x2
	strh r0, [r1, #0x0]
	add r1, r1, #0x2
	cmp r4, #0xa
	blo _020676B4
	ldr r2, _02067828 ; =0x0000FFFF
	ldr r0, [sp, #0x8]
	lsl r1, r4, #0x1
	strh r2, [r0, r1]
	b _0206781A
_020676CC:
	ldr r0, [r6, #0x10]
	lsr r4, r0, #0x1f
_020676D0:
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x4]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	beq _020676F4
	ldr r0, _02067824 ; =0x000001EF
	mov r1, #0x0
	bl FUN_0200AA50
	add r5, r0, #0x0
	ldr r0, [sp, #0x8]
	add r1, r5, #0x0
	bl FUN_02021A74
	add r0, r5, #0x0
	bl FUN_02021A20
	b _0206781A
_020676F4:
	ldr r0, [sp, #0x8]
	add r1, r7, #0x0
	bl FUN_02021E28
	b _0206781A
_020676FE:
	ldrb r4, [r7, #0x16]
	b _0206781A
_02067702:
	ldrb r4, [r7, #0x17]
	b _0206781A
_02067706:
	ldr r2, [sp, #0x4]
	mov r0, #0x1
	sub r2, #0x7a
	add r1, r4, #0x0
	str r2, [sp, #0x4]
	bl _ll_shl
	ldr r3, [r7, #0x18]
	ldr r2, [r7, #0x1c]
	and r3, r0
	and r2, r1
	mov r1, #0x0
	mov r0, #0x0
	eor r1, r2
	eor r0, r3
	orr r0, r1
	beq _0206781A
	mov r4, #0x1
	b _0206781A
_0206772C:
	ldr r2, [sp, #0x8]
_0206772E:
	ldrh r0, [r1, #0x0]
	add r4, r4, #0x1
	add r1, r1, #0x2
	strh r0, [r2, #0x0]
	add r2, r2, #0x2
	cmp r4, #0x7
	blo _0206772E
	ldr r2, _02067828 ; =0x0000FFFF
	ldr r0, [sp, #0x8]
	lsl r1, r4, #0x1
	strh r2, [r0, r1]
	b _0206781A
_02067746:
	ldr r0, [sp, #0x8]
	bl FUN_02021E28
	b _0206781A
_0206774E:
	ldrb r4, [r1, #0x10]
	b _0206781A
_02067752:
	ldrb r4, [r1, #0x11]
	b _0206781A
_02067756:
	ldrb r4, [r1, #0x12]
	b _0206781A
_0206775A:
	ldrb r4, [r1, #0x13]
	b _0206781A
_0206775E:
	ldrb r4, [r1, #0x14]
	b _0206781A
_02067762:
	ldrb r4, [r1, #0x15]
	b _0206781A
_02067766:
	ldrh r4, [r1, #0x16]
	b _0206781A
_0206776A:
	ldrh r4, [r1, #0x18]
	b _0206781A
_0206776E:
	ldrb r4, [r1, #0x1a]
	b _0206781A
_02067772:
	ldrb r4, [r1, #0x1b]
	b _0206781A
_02067776:
	ldrb r0, [r1, #0x1c]
	lsl r0, r0, #0x19
	lsr r4, r0, #0x19
	b _0206781A
_0206777E:
	ldrb r0, [r1, #0x1c]
	lsl r0, r0, #0x18
	lsr r4, r0, #0x1f
	b _0206781A
_02067786:
	ldrb r4, [r1, #0x1d]
	b _0206781A
_0206778A:
	ldrh r4, [r1, #0x1e]
	b _0206781A
_0206778E:
	ldr r4, [r6, #0x10]
	lsl r0, r4, #0x2
	lsr r0, r0, #0x1b
	lsl r5, r0, #0x19
	lsl r0, r4, #0x7
	lsr r0, r0, #0x1b
	lsl r3, r0, #0x14
	lsl r0, r4, #0xc
	lsr r0, r0, #0x1b
	lsl r2, r0, #0xf
	lsl r0, r4, #0x11
	lsr r0, r0, #0x1b
	lsl r1, r0, #0xa
	lsl r0, r4, #0x1b
	lsl r4, r4, #0x16
	lsr r4, r4, #0x1b
	lsr r0, r0, #0x1b
	lsl r4, r4, #0x5
	orr r0, r4
	orr r0, r1
	orr r0, r2
	orr r0, r3
	add r4, r5, #0x0
	orr r4, r0
	b _0206781A
_020677C0:
	ldrh r0, [r5, #0x0]
	cmp r0, #0x1d
	beq _020677CA
	cmp r0, #0x20
	bne _020677D4
_020677CA:
	ldr r0, [r6, #0x10]
	lsr r0, r0, #0x1f
	bne _020677D4
	mov r4, #0x0
	b _0206781A
_020677D4:
	mov r4, #0x1
	b _0206781A
_020677D8:
	ldrh r0, [r5, #0x0]
	ldr r1, _0206782C ; =0x000001ED
	cmp r0, r1
	bne _020677FC
	ldrb r1, [r5, #0xd]
	cmp r1, #0x79
	bne _020677FC
	ldrh r0, [r5, #0x2]
	mov r1, #0x1
	add r2, r4, #0x0
	bl FUN_0206E7B8
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl GetArceusTypeByPlate
	add r4, r0, #0x0
	b _0206781A
_020677FC:
	ldrb r1, [r6, #0x18]
	ldr r2, [sp, #0x4]
	lsl r1, r1, #0x18
	sub r2, #0xaa
	lsr r1, r1, #0x1b
	str r2, [sp, #0x4]
	bl FUN_02068654
	add r4, r0, #0x0
	b _0206781A
_02067810:
	ldrh r0, [r5, #0x0]
	ldr r2, [sp, #0x8]
	add r1, r4, #0x0
	bl FUN_0200A99C
_0206781A:
	add r0, r4, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02067820: .word 0x000001EE
_02067824: .word 0x000001EF
_02067828: .word 0x0000FFFF
_0206782C: .word 0x000001ED

	thumb_func_start FUN_02067830
FUN_02067830: ; 0x02067830
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldrh r0, [r5, #0x4]
	add r4, r1, #0x0
	add r6, r2, #0x0
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bne _02067886
	add r0, r5, #0x0
	ldr r2, [r5, #0x0]
	add r0, #0x88
	mov r1, #0x64
	bl FUN_0206A3D0
	add r0, r5, #0x0
	ldrh r2, [r5, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3D0
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3F8
	ldrh r1, [r5, #0x6]
	cmp r0, r1
	beq _02067886
	cmp r0, r1
	beq _02067870
	bl ErrorHandling
_02067870:
	ldrh r1, [r5, #0x4]
	mov r0, #0x4
	orr r0, r1
	strh r0, [r5, #0x4]
	ldrh r2, [r5, #0x6]
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3A4
	pop {r4-r6, pc}
_02067886:
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl SetMonData
	ldrh r0, [r5, #0x4]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bne _020678BC
	add r0, r5, #0x0
	ldr r2, [r5, #0x0]
	add r0, #0x88
	mov r1, #0x64
	bl FUN_0206A3A4
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3F8
	strh r0, [r5, #0x6]
	add r0, r5, #0x0
	ldrh r2, [r5, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3A4
_020678BC:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start SetMonData
SetMonData: ; 0x020678C0
	push {r3, lr}
	add r3, r0, #0x0
	add r0, r1, #0x0
	sub r0, #0x9f
	cmp r0, #0xb
	bhi _02067958
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020678D8: ; jump table (using 16-bit offset)
	.short _020678F0 - _020678D8 - 2; case 0
	.short _020678F8 - _020678D8 - 2; case 1
	.short _02067900 - _020678D8 - 2; case 2
	.short _02067908 - _020678D8 - 2; case 3
	.short _02067910 - _020678D8 - 2; case 4
	.short _02067918 - _020678D8 - 2; case 5
	.short _02067920 - _020678D8 - 2; case 6
	.short _02067928 - _020678D8 - 2; case 7
	.short _02067930 - _020678D8 - 2; case 8
	.short _02067938 - _020678D8 - 2; case 9
	.short _02067940 - _020678D8 - 2; case 10
	.short _0206794C - _020678D8 - 2; case 11
_020678F0:
	ldr r0, [r2, #0x0]
	add r3, #0x88
	str r0, [r3, #0x0]
	pop {r3, pc}
_020678F8:
	ldrb r0, [r2, #0x0]
	add r3, #0x8c
	strb r0, [r3, #0x0]
	pop {r3, pc}
_02067900:
	ldrb r0, [r2, #0x0]
	add r3, #0x8d
	strb r0, [r3, #0x0]
	pop {r3, pc}
_02067908:
	ldrh r0, [r2, #0x0]
	add r3, #0x8e
	strh r0, [r3, #0x0]
	pop {r3, pc}
_02067910:
	ldrh r0, [r2, #0x0]
	add r3, #0x90
	strh r0, [r3, #0x0]
	pop {r3, pc}
_02067918:
	ldrh r0, [r2, #0x0]
	add r3, #0x92
	strh r0, [r3, #0x0]
	pop {r3, pc}
_02067920:
	ldrh r0, [r2, #0x0]
	add r3, #0x94
	strh r0, [r3, #0x0]
	pop {r3, pc}
_02067928:
	ldrh r0, [r2, #0x0]
	add r3, #0x96
	strh r0, [r3, #0x0]
	pop {r3, pc}
_02067930:
	ldrh r0, [r2, #0x0]
	add r3, #0x98
	strh r0, [r3, #0x0]
	pop {r3, pc}
_02067938:
	ldrh r0, [r2, #0x0]
	add r3, #0x9a
	strh r0, [r3, #0x0]
	pop {r3, pc}
_02067940:
	add r3, #0x9c
	add r0, r2, #0x0
	add r1, r3, #0x0
	bl FUN_020256D0
	pop {r3, pc}
_0206794C:
	add r3, #0xd4
	add r0, r2, #0x0
	add r1, r3, #0x0
	bl FUN_02029C74
	pop {r3, pc}
_02067958:
	add r0, r3, #0x0
	bl SetBoxMonData
	pop {r3, pc}

	thumb_func_start FUN_02067960
FUN_02067960: ; 0x02067960
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldrh r0, [r5, #0x4]
	add r4, r1, #0x0
	add r6, r2, #0x0
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bne _020679AA
	ldrh r2, [r5, #0x6]
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3D0
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3F8
	ldrh r1, [r5, #0x6]
	cmp r0, r1
	beq _020679AA
	cmp r0, r1
	beq _02067994
	bl ErrorHandling
_02067994:
	ldrh r1, [r5, #0x4]
	mov r0, #0x4
	orr r0, r1
	strh r0, [r5, #0x4]
	ldrh r2, [r5, #0x6]
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3A4
	pop {r4-r6, pc}
_020679AA:
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl SetBoxMonData
	ldrh r0, [r5, #0x4]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bne _020679D4
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3F8
	strh r0, [r5, #0x6]
	add r0, r5, #0x0
	ldrh r2, [r5, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3A4
_020679D4:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start SetBoxMonData
SetBoxMonData: ; 0x020679D8
	push {r4-r7, lr}
	sub sp, #0x4c
	str r1, [sp, #0x4]
	add r1, r0, #0x0
	add r4, r2, #0x0
	ldr r1, [r1, #0x0]
	str r0, [sp, #0x0]
	mov r2, #0x0
	bl GetSubstruct
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r2, #0x1
	add r1, r0, #0x0
	ldr r1, [r1, #0x0]
	bl GetSubstruct
	add r5, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r2, #0x2
	add r1, r0, #0x0
	ldr r1, [r1, #0x0]
	bl GetSubstruct
	add r6, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r2, #0x3
	add r1, r0, #0x0
	ldr r1, [r1, #0x0]
	bl GetSubstruct
	add r1, r0, #0x0
	ldr r0, [sp, #0x4]
	cmp r0, #0xb2
	bls _02067A20
	b _02067FF6
_02067A20:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02067A2C: ; jump table (using 16-bit offset)
	.short _02067B92 - _02067A2C - 2; case 0
	.short _02067B9C - _02067A2C - 2; case 1
	.short _02067BBA - _02067A2C - 2; case 2
	.short _02067BD6 - _02067A2C - 2; case 3
	.short _02067BEE - _02067A2C - 2; case 4
	.short _02067BF8 - _02067A2C - 2; case 5
	.short _02067C00 - _02067A2C - 2; case 6
	.short _02067C08 - _02067A2C - 2; case 7
	.short _02067C10 - _02067A2C - 2; case 8
	.short _02067C18 - _02067A2C - 2; case 9
	.short _02067C20 - _02067A2C - 2; case 10
	.short _02067C28 - _02067A2C - 2; case 11
	.short _02067C30 - _02067A2C - 2; case 12
	.short _02067C38 - _02067A2C - 2; case 13
	.short _02067C40 - _02067A2C - 2; case 14
	.short _02067C48 - _02067A2C - 2; case 15
	.short _02067C50 - _02067A2C - 2; case 16
	.short _02067C58 - _02067A2C - 2; case 17
	.short _02067C60 - _02067A2C - 2; case 18
	.short _02067C68 - _02067A2C - 2; case 19
	.short _02067C70 - _02067A2C - 2; case 20
	.short _02067C78 - _02067A2C - 2; case 21
	.short _02067C80 - _02067A2C - 2; case 22
	.short _02067C88 - _02067A2C - 2; case 23
	.short _02067C90 - _02067A2C - 2; case 24
	.short _02067C98 - _02067A2C - 2; case 25
	.short _02067C98 - _02067A2C - 2; case 26
	.short _02067C98 - _02067A2C - 2; case 27
	.short _02067C98 - _02067A2C - 2; case 28
	.short _02067C98 - _02067A2C - 2; case 29
	.short _02067C98 - _02067A2C - 2; case 30
	.short _02067C98 - _02067A2C - 2; case 31
	.short _02067C98 - _02067A2C - 2; case 32
	.short _02067C98 - _02067A2C - 2; case 33
	.short _02067C98 - _02067A2C - 2; case 34
	.short _02067C98 - _02067A2C - 2; case 35
	.short _02067C98 - _02067A2C - 2; case 36
	.short _02067C98 - _02067A2C - 2; case 37
	.short _02067C98 - _02067A2C - 2; case 38
	.short _02067C98 - _02067A2C - 2; case 39
	.short _02067C98 - _02067A2C - 2; case 40
	.short _02067C98 - _02067A2C - 2; case 41
	.short _02067C98 - _02067A2C - 2; case 42
	.short _02067C98 - _02067A2C - 2; case 43
	.short _02067C98 - _02067A2C - 2; case 44
	.short _02067C98 - _02067A2C - 2; case 45
	.short _02067C98 - _02067A2C - 2; case 46
	.short _02067C98 - _02067A2C - 2; case 47
	.short _02067C98 - _02067A2C - 2; case 48
	.short _02067C98 - _02067A2C - 2; case 49
	.short _02067C98 - _02067A2C - 2; case 50
	.short _02067C98 - _02067A2C - 2; case 51
	.short _02067C98 - _02067A2C - 2; case 52
	.short _02067C98 - _02067A2C - 2; case 53
	.short _02067CC6 - _02067A2C - 2; case 54
	.short _02067CC6 - _02067A2C - 2; case 55
	.short _02067CC6 - _02067A2C - 2; case 56
	.short _02067CC6 - _02067A2C - 2; case 57
	.short _02067CD6 - _02067A2C - 2; case 58
	.short _02067CD6 - _02067A2C - 2; case 59
	.short _02067CD6 - _02067A2C - 2; case 60
	.short _02067CD6 - _02067A2C - 2; case 61
	.short _02067CE6 - _02067A2C - 2; case 62
	.short _02067CE6 - _02067A2C - 2; case 63
	.short _02067CE6 - _02067A2C - 2; case 64
	.short _02067CE6 - _02067A2C - 2; case 65
	.short _02067FF6 - _02067A2C - 2; case 66
	.short _02067FF6 - _02067A2C - 2; case 67
	.short _02067FF6 - _02067A2C - 2; case 68
	.short _02067FF6 - _02067A2C - 2; case 69
	.short _02067CF6 - _02067A2C - 2; case 70
	.short _02067D0A - _02067A2C - 2; case 71
	.short _02067D1E - _02067A2C - 2; case 72
	.short _02067D32 - _02067A2C - 2; case 73
	.short _02067D46 - _02067A2C - 2; case 74
	.short _02067D5A - _02067A2C - 2; case 75
	.short _02067D6E - _02067A2C - 2; case 76
	.short _02067D82 - _02067A2C - 2; case 77
	.short _02067D94 - _02067A2C - 2; case 78
	.short _02067D94 - _02067A2C - 2; case 79
	.short _02067D94 - _02067A2C - 2; case 80
	.short _02067D94 - _02067A2C - 2; case 81
	.short _02067D94 - _02067A2C - 2; case 82
	.short _02067D94 - _02067A2C - 2; case 83
	.short _02067D94 - _02067A2C - 2; case 84
	.short _02067D94 - _02067A2C - 2; case 85
	.short _02067D94 - _02067A2C - 2; case 86
	.short _02067D94 - _02067A2C - 2; case 87
	.short _02067D94 - _02067A2C - 2; case 88
	.short _02067D94 - _02067A2C - 2; case 89
	.short _02067D94 - _02067A2C - 2; case 90
	.short _02067D94 - _02067A2C - 2; case 91
	.short _02067D94 - _02067A2C - 2; case 92
	.short _02067D94 - _02067A2C - 2; case 93
	.short _02067D94 - _02067A2C - 2; case 94
	.short _02067D94 - _02067A2C - 2; case 95
	.short _02067D94 - _02067A2C - 2; case 96
	.short _02067D94 - _02067A2C - 2; case 97
	.short _02067D94 - _02067A2C - 2; case 98
	.short _02067D94 - _02067A2C - 2; case 99
	.short _02067D94 - _02067A2C - 2; case 100
	.short _02067D94 - _02067A2C - 2; case 101
	.short _02067D94 - _02067A2C - 2; case 102
	.short _02067D94 - _02067A2C - 2; case 103
	.short _02067D94 - _02067A2C - 2; case 104
	.short _02067D94 - _02067A2C - 2; case 105
	.short _02067D94 - _02067A2C - 2; case 106
	.short _02067D94 - _02067A2C - 2; case 107
	.short _02067D94 - _02067A2C - 2; case 108
	.short _02067D94 - _02067A2C - 2; case 109
	.short _02067DC2 - _02067A2C - 2; case 110
	.short _02067DD6 - _02067A2C - 2; case 111
	.short _02067DEA - _02067A2C - 2; case 112
	.short _02067DFE - _02067A2C - 2; case 113
	.short _02067E06 - _02067A2C - 2; case 114
	.short _02067FF6 - _02067A2C - 2; case 115
	.short _02067E2C - _02067A2C - 2; case 116
	.short _02067E0E - _02067A2C - 2; case 117
	.short _02067E6C - _02067A2C - 2; case 118
	.short _02067E40 - _02067A2C - 2; case 119
	.short _02067E7A - _02067A2C - 2; case 120
	.short _02067E82 - _02067A2C - 2; case 121
	.short _02067E8A - _02067A2C - 2; case 122
	.short _02067E8A - _02067A2C - 2; case 123
	.short _02067E8A - _02067A2C - 2; case 124
	.short _02067E8A - _02067A2C - 2; case 125
	.short _02067E8A - _02067A2C - 2; case 126
	.short _02067E8A - _02067A2C - 2; case 127
	.short _02067E8A - _02067A2C - 2; case 128
	.short _02067E8A - _02067A2C - 2; case 129
	.short _02067E8A - _02067A2C - 2; case 130
	.short _02067E8A - _02067A2C - 2; case 131
	.short _02067E8A - _02067A2C - 2; case 132
	.short _02067E8A - _02067A2C - 2; case 133
	.short _02067E8A - _02067A2C - 2; case 134
	.short _02067E8A - _02067A2C - 2; case 135
	.short _02067E8A - _02067A2C - 2; case 136
	.short _02067E8A - _02067A2C - 2; case 137
	.short _02067E8A - _02067A2C - 2; case 138
	.short _02067E8A - _02067A2C - 2; case 139
	.short _02067E8A - _02067A2C - 2; case 140
	.short _02067E8A - _02067A2C - 2; case 141
	.short _02067E8A - _02067A2C - 2; case 142
	.short _02067ECE - _02067A2C - 2; case 143
	.short _02067EE2 - _02067A2C - 2; case 144
	.short _02067EEE - _02067A2C - 2; case 145
	.short _02067EF6 - _02067A2C - 2; case 146
	.short _02067EFE - _02067A2C - 2; case 147
	.short _02067F06 - _02067A2C - 2; case 148
	.short _02067F0E - _02067A2C - 2; case 149
	.short _02067F16 - _02067A2C - 2; case 150
	.short _02067F1E - _02067A2C - 2; case 151
	.short _02067F26 - _02067A2C - 2; case 152
	.short _02067F2E - _02067A2C - 2; case 153
	.short _02067F36 - _02067A2C - 2; case 154
	.short _02067F3E - _02067A2C - 2; case 155
	.short _02067F52 - _02067A2C - 2; case 156
	.short _02067F66 - _02067A2C - 2; case 157
	.short _02067F6E - _02067A2C - 2; case 158
	.short _02067FF6 - _02067A2C - 2; case 159
	.short _02067FF6 - _02067A2C - 2; case 160
	.short _02067FF6 - _02067A2C - 2; case 161
	.short _02067FF6 - _02067A2C - 2; case 162
	.short _02067FF6 - _02067A2C - 2; case 163
	.short _02067FF6 - _02067A2C - 2; case 164
	.short _02067FF6 - _02067A2C - 2; case 165
	.short _02067FF6 - _02067A2C - 2; case 166
	.short _02067FF6 - _02067A2C - 2; case 167
	.short _02067FF6 - _02067A2C - 2; case 168
	.short _02067FF6 - _02067A2C - 2; case 169
	.short _02067FF6 - _02067A2C - 2; case 170
	.short _02067FF6 - _02067A2C - 2; case 171
	.short _02067FF6 - _02067A2C - 2; case 172
	.short _02067FF6 - _02067A2C - 2; case 173
	.short _02067F76 - _02067A2C - 2; case 174
	.short _02067FF6 - _02067A2C - 2; case 175
	.short _02067FF6 - _02067A2C - 2; case 176
	.short _02067FF6 - _02067A2C - 2; case 177
	.short _02067FDE - _02067A2C - 2; case 178
_02067B92:
	ldr r0, [sp, #0x0]
	ldr r1, [r4, #0x0]
	add sp, #0x4c
	str r1, [r0, #0x0]
	pop {r4-r7, pc}
_02067B9C:
	bl ErrorHandling
	ldr r0, [sp, #0x0]
	ldrb r1, [r4, #0x0]
	ldrh r2, [r0, #0x4]
	mov r0, #0x1
	bic r2, r0
	mov r0, #0x1
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	ldr r0, [sp, #0x0]
	add sp, #0x4c
	strh r1, [r0, #0x4]
	pop {r4-r7, pc}
_02067BBA:
	bl ErrorHandling
	ldr r0, [sp, #0x0]
	ldrh r1, [r0, #0x4]
	mov r0, #0x2
	bic r1, r0
	ldrb r0, [r4, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1e
	orr r1, r0
	ldr r0, [sp, #0x0]
	add sp, #0x4c
	strh r1, [r0, #0x4]
	pop {r4-r7, pc}
_02067BD6:
	ldr r0, [sp, #0x0]
	ldrh r1, [r0, #0x4]
	mov r0, #0x4
	bic r1, r0
	ldrb r0, [r4, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1d
	orr r1, r0
	ldr r0, [sp, #0x0]
	add sp, #0x4c
	strh r1, [r0, #0x4]
	pop {r4-r7, pc}
_02067BEE:
	ldrh r1, [r4, #0x0]
	ldr r0, [sp, #0x0]
	add sp, #0x4c
	strh r1, [r0, #0x6]
	pop {r4-r7, pc}
_02067BF8:
	ldrh r0, [r4, #0x0]
	add sp, #0x4c
	strh r0, [r7, #0x0]
	pop {r4-r7, pc}
_02067C00:
	ldrh r0, [r4, #0x0]
	add sp, #0x4c
	strh r0, [r7, #0x2]
	pop {r4-r7, pc}
_02067C08:
	ldr r0, [r4, #0x0]
	add sp, #0x4c
	str r0, [r7, #0x4]
	pop {r4-r7, pc}
_02067C10:
	ldr r0, [r4, #0x0]
	add sp, #0x4c
	str r0, [r7, #0x8]
	pop {r4-r7, pc}
_02067C18:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r7, #0xc]
	pop {r4-r7, pc}
_02067C20:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r7, #0xd]
	pop {r4-r7, pc}
_02067C28:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r7, #0xe]
	pop {r4-r7, pc}
_02067C30:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r7, #0xf]
	pop {r4-r7, pc}
_02067C38:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r7, #0x10]
	pop {r4-r7, pc}
_02067C40:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r7, #0x11]
	pop {r4-r7, pc}
_02067C48:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r7, #0x12]
	pop {r4-r7, pc}
_02067C50:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r7, #0x13]
	pop {r4-r7, pc}
_02067C58:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r7, #0x14]
	pop {r4-r7, pc}
_02067C60:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r7, #0x15]
	pop {r4-r7, pc}
_02067C68:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r7, #0x16]
	pop {r4-r7, pc}
_02067C70:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r7, #0x17]
	pop {r4-r7, pc}
_02067C78:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r7, #0x18]
	pop {r4-r7, pc}
_02067C80:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r7, #0x19]
	pop {r4-r7, pc}
_02067C88:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r7, #0x1a]
	pop {r4-r7, pc}
_02067C90:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r7, #0x1b]
	pop {r4-r7, pc}
_02067C98:
	ldrb r4, [r4, #0x0]
	ldr r2, [sp, #0x4]
	mov r1, #0x0
	sub r2, #0x19
	add r0, r4, #0x0
	str r2, [sp, #0x4]
	bl _ll_shl
	cmp r4, #0x0
	beq _02067CB6
	ldr r1, [r7, #0x1c]
	add sp, #0x4c
	orr r0, r1
	str r0, [r7, #0x1c]
	pop {r4-r7, pc}
_02067CB6:
	mov r1, #0x0
	sub r1, r1, #0x1
	ldr r2, [r7, #0x1c]
	eor r0, r1
	and r0, r2
	add sp, #0x4c
	str r0, [r7, #0x1c]
	pop {r4-r7, pc}
_02067CC6:
	ldr r0, [sp, #0x4]
	ldrh r1, [r4, #0x0]
	sub r0, #0x36
	str r0, [sp, #0x4]
	lsl r0, r0, #0x1
	add sp, #0x4c
	strh r1, [r5, r0]
	pop {r4-r7, pc}
_02067CD6:
	ldr r0, [sp, #0x4]
	ldrb r1, [r4, #0x0]
	sub r0, #0x3a
	str r0, [sp, #0x4]
	add r0, r5, r0
	strb r1, [r0, #0x8]
	add sp, #0x4c
	pop {r4-r7, pc}
_02067CE6:
	ldr r0, [sp, #0x4]
	ldrb r1, [r4, #0x0]
	sub r0, #0x3e
	str r0, [sp, #0x4]
	add r0, r5, r0
	strb r1, [r0, #0xc]
	add sp, #0x4c
	pop {r4-r7, pc}
_02067CF6:
	ldr r2, [r5, #0x10]
	mov r0, #0x1f
	bic r2, r0
	ldrb r1, [r4, #0x0]
	mov r0, #0x1f
	add sp, #0x4c
	and r0, r1
	orr r0, r2
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_02067D0A:
	ldr r1, [r5, #0x10]
	ldr r0, _02067FFC ; =0xFFFFFC1F
	add sp, #0x4c
	and r1, r0
	ldrb r0, [r4, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x16
	orr r0, r1
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_02067D1E:
	ldr r1, [r5, #0x10]
	ldr r0, _02068000 ; =0xFFFF83FF
	add sp, #0x4c
	and r1, r0
	ldrb r0, [r4, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x11
	orr r0, r1
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_02067D32:
	ldr r1, [r5, #0x10]
	ldr r0, _02068004 ; =0xFFF07FFF
	add sp, #0x4c
	and r1, r0
	ldrb r0, [r4, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0xc
	orr r0, r1
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_02067D46:
	ldr r1, [r5, #0x10]
	ldr r0, _02068008 ; =0xFE0FFFFF
	add sp, #0x4c
	and r1, r0
	ldrb r0, [r4, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x7
	orr r0, r1
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_02067D5A:
	ldr r1, [r5, #0x10]
	ldr r0, _0206800C ; =0xC1FFFFFF
	add sp, #0x4c
	and r1, r0
	ldrb r0, [r4, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x2
	orr r0, r1
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_02067D6E:
	ldr r1, [r5, #0x10]
	ldr r0, _02068010 ; =0xBFFFFFFF
	add sp, #0x4c
	and r1, r0
	ldrb r0, [r4, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1
	orr r0, r1
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_02067D82:
	ldr r1, [r5, #0x10]
	ldr r0, _02068014 ; =0x7FFFFFFF
	add sp, #0x4c
	and r1, r0
	ldrb r0, [r4, #0x0]
	lsl r0, r0, #0x1f
	orr r0, r1
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_02067D94:
	ldrb r4, [r4, #0x0]
	ldr r2, [sp, #0x4]
	mov r1, #0x0
	sub r2, #0x4e
	add r0, r4, #0x0
	str r2, [sp, #0x4]
	bl _ll_shl
	cmp r4, #0x0
	beq _02067DB2
	ldr r1, [r5, #0x14]
	add sp, #0x4c
	orr r0, r1
	str r0, [r5, #0x14]
	pop {r4-r7, pc}
_02067DB2:
	mov r1, #0x0
	sub r1, r1, #0x1
	ldr r2, [r5, #0x14]
	eor r0, r1
	and r0, r2
	add sp, #0x4c
	str r0, [r5, #0x14]
	pop {r4-r7, pc}
_02067DC2:
	ldrb r2, [r5, #0x18]
	ldrb r1, [r4, #0x0]
	mov r0, #0x1
	bic r2, r0
	mov r0, #0x1
	and r0, r1
	orr r0, r2
	add sp, #0x4c
	strb r0, [r5, #0x18]
	pop {r4-r7, pc}
_02067DD6:
	ldrb r1, [r5, #0x18]
	mov r0, #0x6
	add sp, #0x4c
	bic r1, r0
	ldrb r0, [r4, #0x0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1d
	orr r0, r1
	strb r0, [r5, #0x18]
	pop {r4-r7, pc}
_02067DEA:
	ldrb r1, [r5, #0x18]
	mov r0, #0xf8
	add sp, #0x4c
	bic r1, r0
	ldrb r0, [r4, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x18
	orr r0, r1
	strb r0, [r5, #0x18]
	pop {r4-r7, pc}
_02067DFE:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r5, #0x19]
	pop {r4-r7, pc}
_02067E06:
	ldrh r0, [r4, #0x0]
	add sp, #0x4c
	strh r0, [r5, #0x1a]
	pop {r4-r7, pc}
_02067E0E:
	ldrh r0, [r7, #0x0]
	mov r1, #0x0
	add r2, sp, #0x34
	bl FUN_0200A99C
	add r0, sp, #0x34
	add r1, r4, #0x0
	bl StringNotEqual
	ldr r2, [r5, #0x10]
	ldr r1, _02068014 ; =0x7FFFFFFF
	lsl r0, r0, #0x1f
	and r1, r2
	orr r0, r1
	str r0, [r5, #0x10]
_02067E2C:
	mov r1, #0x0
_02067E2E:
	ldrh r0, [r4, #0x0]
	add r1, r1, #0x1
	add r4, r4, #0x2
	strh r0, [r6, #0x0]
	add r6, r6, #0x2
	cmp r1, #0xb
	blo _02067E2E
	add sp, #0x4c
	pop {r4-r7, pc}
_02067E40:
	ldrh r0, [r7, #0x0]
	add r2, sp, #0x1c
	mov r1, #0x0
	add r2, #0x2
	bl FUN_0200A99C
	add r0, r4, #0x0
	add r1, sp, #0x8
	mov r2, #0xb
	bl FUN_02021EF0
	add r0, sp, #0x1c
	add r0, #0x2
	add r1, sp, #0x8
	bl StringNotEqual
	ldr r2, [r5, #0x10]
	ldr r1, _02068014 ; =0x7FFFFFFF
	lsl r0, r0, #0x1f
	and r1, r2
	orr r0, r1
	str r0, [r5, #0x10]
_02067E6C:
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r2, #0xb
	bl FUN_02021EF0
	add sp, #0x4c
	pop {r4-r7, pc}
_02067E7A:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r6, #0x16]
	pop {r4-r7, pc}
_02067E82:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r6, #0x17]
	pop {r4-r7, pc}
_02067E8A:
	ldrb r4, [r4, #0x0]
	ldr r2, [sp, #0x4]
	mov r1, #0x0
	sub r2, #0x7a
	add r0, r4, #0x0
	str r2, [sp, #0x4]
	bl _ll_shl
	cmp r4, #0x0
	beq _02067EB2
	add r4, r6, #0x0
	add r4, #0x18
	ldr r3, [r6, #0x18]
	ldr r2, [r4, #0x4]
	orr r0, r3
	orr r1, r2
	str r0, [r6, #0x18]
	add sp, #0x4c
	str r1, [r4, #0x4]
	pop {r4-r7, pc}
_02067EB2:
	add r4, r6, #0x0
	mov r5, #0x0
	mvn r5, r5
	add r4, #0x18
	ldr r3, [r6, #0x18]
	eor r0, r5
	ldr r2, [r4, #0x4]
	eor r1, r5
	and r0, r3
	and r1, r2
	str r0, [r6, #0x18]
	add sp, #0x4c
	str r1, [r4, #0x4]
	pop {r4-r7, pc}
_02067ECE:
	mov r2, #0x0
_02067ED0:
	ldrh r0, [r4, #0x0]
	add r2, r2, #0x1
	add r4, r4, #0x2
	strh r0, [r1, #0x0]
	add r1, r1, #0x2
	cmp r2, #0x8
	blo _02067ED0
	add sp, #0x4c
	pop {r4-r7, pc}
_02067EE2:
	add r0, r4, #0x0
	mov r2, #0x8
	bl FUN_02021EF0
	add sp, #0x4c
	pop {r4-r7, pc}
_02067EEE:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r1, #0x10]
	pop {r4-r7, pc}
_02067EF6:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r1, #0x11]
	pop {r4-r7, pc}
_02067EFE:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r1, #0x12]
	pop {r4-r7, pc}
_02067F06:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r1, #0x13]
	pop {r4-r7, pc}
_02067F0E:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r1, #0x14]
	pop {r4-r7, pc}
_02067F16:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r1, #0x15]
	pop {r4-r7, pc}
_02067F1E:
	ldrh r0, [r4, #0x0]
	add sp, #0x4c
	strh r0, [r1, #0x16]
	pop {r4-r7, pc}
_02067F26:
	ldrh r0, [r4, #0x0]
	add sp, #0x4c
	strh r0, [r1, #0x18]
	pop {r4-r7, pc}
_02067F2E:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r1, #0x1a]
	pop {r4-r7, pc}
_02067F36:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r1, #0x1b]
	pop {r4-r7, pc}
_02067F3E:
	ldrb r3, [r1, #0x1c]
	ldrb r2, [r4, #0x0]
	mov r0, #0x7f
	bic r3, r0
	mov r0, #0x7f
	and r0, r2
	orr r0, r3
	strb r0, [r1, #0x1c]
	add sp, #0x4c
	pop {r4-r7, pc}
_02067F52:
	ldrb r2, [r1, #0x1c]
	mov r0, #0x80
	add sp, #0x4c
	bic r2, r0
	ldrb r0, [r4, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x18
	orr r0, r2
	strb r0, [r1, #0x1c]
	pop {r4-r7, pc}
_02067F66:
	ldrb r0, [r4, #0x0]
	add sp, #0x4c
	strb r0, [r1, #0x1d]
	pop {r4-r7, pc}
_02067F6E:
	ldrh r0, [r4, #0x0]
	add sp, #0x4c
	strh r0, [r1, #0x1e]
	pop {r4-r7, pc}
_02067F76:
	ldr r2, [r5, #0x10]
	mov r0, #0x1f
	bic r2, r0
	ldr r1, [r4, #0x0]
	mov r0, #0x1f
	and r1, r0
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	ldr r0, _02067FFC ; =0xFFFFFC1F
	str r1, [r5, #0x10]
	and r1, r0
	ldr r0, [r4, #0x0]
	add sp, #0x4c
	lsr r0, r0, #0x5
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x16
	orr r1, r0
	ldr r0, _02068000 ; =0xFFFF83FF
	str r1, [r5, #0x10]
	and r1, r0
	ldr r0, [r4, #0x0]
	lsr r0, r0, #0xa
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x11
	orr r1, r0
	ldr r0, _02068004 ; =0xFFF07FFF
	str r1, [r5, #0x10]
	and r1, r0
	ldr r0, [r4, #0x0]
	lsr r0, r0, #0xf
	lsl r0, r0, #0x1b
	lsr r0, r0, #0xc
	orr r1, r0
	ldr r0, _02068008 ; =0xFE0FFFFF
	str r1, [r5, #0x10]
	and r1, r0
	ldr r0, [r4, #0x0]
	lsr r0, r0, #0x14
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x7
	orr r1, r0
	ldr r0, _0206800C ; =0xC1FFFFFF
	str r1, [r5, #0x10]
	and r1, r0
	ldr r0, [r4, #0x0]
	lsr r0, r0, #0x19
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x2
	orr r0, r1
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_02067FDE:
	ldrh r0, [r7, #0x0]
	mov r1, #0x0
	bl FUN_0200AA50
	add r4, r0, #0x0
	add r1, r6, #0x0
	mov r2, #0xb
	bl FUN_02021EF0
	add r0, r4, #0x0
	bl FUN_02021A20
_02067FF6:
	add sp, #0x4c
	pop {r4-r7, pc}
	nop
_02067FFC: .word 0xFFFFFC1F
_02068000: .word 0xFFFF83FF
_02068004: .word 0xFFF07FFF
_02068008: .word 0xFE0FFFFF
_0206800C: .word 0xC1FFFFFF
_02068010: .word 0xBFFFFFFF
_02068014: .word 0x7FFFFFFF

	thumb_func_start FUN_02068018
FUN_02068018: ; 0x02068018
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldrh r0, [r5, #0x4]
	add r4, r1, #0x0
	add r6, r2, #0x0
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bne _02068066
	add r0, r5, #0x0
	ldr r2, [r5, #0x0]
	add r0, #0x88
	mov r1, #0x64
	bl FUN_0206A3D0
	add r0, r5, #0x0
	ldrh r2, [r5, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3D0
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3F8
	ldrh r1, [r5, #0x6]
	cmp r0, r1
	beq _02068066
	cmp r0, r1
	beq _02068058
	bl ErrorHandling
_02068058:
	ldrh r2, [r5, #0x6]
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3A4
	pop {r4-r6, pc}
_02068066:
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020680A0
	ldrh r0, [r5, #0x4]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bne _0206809C
	add r0, r5, #0x0
	ldr r2, [r5, #0x0]
	add r0, #0x88
	mov r1, #0x64
	bl FUN_0206A3A4
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3F8
	strh r0, [r5, #0x6]
	add r0, r5, #0x0
	ldrh r2, [r5, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3A4
_0206809C:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020680A0
FUN_020680A0: ; 0x020680A0
	push {r3, lr}
	add r3, r1, #0x0
	sub r3, #0x9f
	cmp r3, #0xa
	bhi _020680F8
	add r3, r3, r3
	add r3, pc
	ldrh r3, [r3, #0x6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_020680B6: ; jump table (using 16-bit offset)
	.short _020680F2 - _020680B6 - 2; case 0
	.short _020680F2 - _020680B6 - 2; case 1
	.short _020680F2 - _020680B6 - 2; case 2
	.short _020680CC - _020680B6 - 2; case 3
	.short _020680F2 - _020680B6 - 2; case 4
	.short _020680F2 - _020680B6 - 2; case 5
	.short _020680F2 - _020680B6 - 2; case 6
	.short _020680F2 - _020680B6 - 2; case 7
	.short _020680F2 - _020680B6 - 2; case 8
	.short _020680F2 - _020680B6 - 2; case 9
	.short _020680F2 - _020680B6 - 2; case 10
_020680CC:
	add r1, r0, #0x0
	add r1, #0x90
	ldrh r3, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x8e
	ldrh r1, [r1, #0x0]
	add r1, r1, r2
	cmp r1, r3
	ble _020680E4
	add r0, #0x8e
	strh r3, [r0, #0x0]
	pop {r3, pc}
_020680E4:
	add r1, r0, #0x0
	add r1, #0x8e
	ldrh r1, [r1, #0x0]
	add r0, #0x8e
	add r1, r1, r2
	strh r1, [r0, #0x0]
	pop {r3, pc}
_020680F2:
	bl ErrorHandling
	pop {r3, pc}
_020680F8:
	bl FUN_02068100
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02068100
FUN_02068100: ; 0x02068100
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r1, #0x0
	add r1, r0, #0x0
	add r6, r2, #0x0
	ldr r1, [r1, #0x0]
	str r0, [sp, #0x0]
	mov r2, #0x0
	bl GetSubstruct
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r2, #0x1
	add r1, r0, #0x0
	ldr r1, [r1, #0x0]
	bl GetSubstruct
	add r5, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r2, #0x2
	add r1, r0, #0x0
	ldr r1, [r1, #0x0]
	bl GetSubstruct
	ldr r0, [sp, #0x0]
	mov r2, #0x3
	add r1, r0, #0x0
	ldr r1, [r1, #0x0]
	bl GetSubstruct
	cmp r7, #0xb2
	bls _02068142
	b _02068500
_02068142:
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0206814E: ; jump table (using 16-bit offset)
	.short _02068500 - _0206814E - 2; case 0
	.short _02068500 - _0206814E - 2; case 1
	.short _02068500 - _0206814E - 2; case 2
	.short _02068500 - _0206814E - 2; case 3
	.short _02068500 - _0206814E - 2; case 4
	.short _02068500 - _0206814E - 2; case 5
	.short _02068500 - _0206814E - 2; case 6
	.short _02068500 - _0206814E - 2; case 7
	.short _020682B4 - _0206814E - 2; case 8
	.short _020682D8 - _0206814E - 2; case 9
	.short _02068500 - _0206814E - 2; case 10
	.short _02068500 - _0206814E - 2; case 11
	.short _02068500 - _0206814E - 2; case 12
	.short _020682EE - _0206814E - 2; case 13
	.short _020682F8 - _0206814E - 2; case 14
	.short _02068302 - _0206814E - 2; case 15
	.short _0206830C - _0206814E - 2; case 16
	.short _02068316 - _0206814E - 2; case 17
	.short _02068320 - _0206814E - 2; case 18
	.short _0206832A - _0206814E - 2; case 19
	.short _02068340 - _0206814E - 2; case 20
	.short _02068356 - _0206814E - 2; case 21
	.short _0206836C - _0206814E - 2; case 22
	.short _02068382 - _0206814E - 2; case 23
	.short _02068398 - _0206814E - 2; case 24
	.short _02068500 - _0206814E - 2; case 25
	.short _02068500 - _0206814E - 2; case 26
	.short _02068500 - _0206814E - 2; case 27
	.short _02068500 - _0206814E - 2; case 28
	.short _02068500 - _0206814E - 2; case 29
	.short _02068500 - _0206814E - 2; case 30
	.short _02068500 - _0206814E - 2; case 31
	.short _02068500 - _0206814E - 2; case 32
	.short _02068500 - _0206814E - 2; case 33
	.short _02068500 - _0206814E - 2; case 34
	.short _02068500 - _0206814E - 2; case 35
	.short _02068500 - _0206814E - 2; case 36
	.short _02068500 - _0206814E - 2; case 37
	.short _02068500 - _0206814E - 2; case 38
	.short _02068500 - _0206814E - 2; case 39
	.short _02068500 - _0206814E - 2; case 40
	.short _02068500 - _0206814E - 2; case 41
	.short _02068500 - _0206814E - 2; case 42
	.short _02068500 - _0206814E - 2; case 43
	.short _02068500 - _0206814E - 2; case 44
	.short _02068500 - _0206814E - 2; case 45
	.short _02068500 - _0206814E - 2; case 46
	.short _02068500 - _0206814E - 2; case 47
	.short _02068500 - _0206814E - 2; case 48
	.short _02068500 - _0206814E - 2; case 49
	.short _02068500 - _0206814E - 2; case 50
	.short _02068500 - _0206814E - 2; case 51
	.short _02068500 - _0206814E - 2; case 52
	.short _02068500 - _0206814E - 2; case 53
	.short _02068500 - _0206814E - 2; case 54
	.short _02068500 - _0206814E - 2; case 55
	.short _02068500 - _0206814E - 2; case 56
	.short _02068500 - _0206814E - 2; case 57
	.short _020683AE - _0206814E - 2; case 58
	.short _020683AE - _0206814E - 2; case 59
	.short _020683AE - _0206814E - 2; case 60
	.short _020683AE - _0206814E - 2; case 61
	.short _020683EA - _0206814E - 2; case 62
	.short _020683EA - _0206814E - 2; case 63
	.short _020683EA - _0206814E - 2; case 64
	.short _020683EA - _0206814E - 2; case 65
	.short _02068504 - _0206814E - 2; case 66
	.short _02068504 - _0206814E - 2; case 67
	.short _02068504 - _0206814E - 2; case 68
	.short _02068504 - _0206814E - 2; case 69
	.short _02068404 - _0206814E - 2; case 70
	.short _0206842E - _0206814E - 2; case 71
	.short _02068458 - _0206814E - 2; case 72
	.short _02068482 - _0206814E - 2; case 73
	.short _020684AC - _0206814E - 2; case 74
	.short _020684D6 - _0206814E - 2; case 75
	.short _02068500 - _0206814E - 2; case 76
	.short _02068500 - _0206814E - 2; case 77
	.short _02068500 - _0206814E - 2; case 78
	.short _02068500 - _0206814E - 2; case 79
	.short _02068500 - _0206814E - 2; case 80
	.short _02068500 - _0206814E - 2; case 81
	.short _02068500 - _0206814E - 2; case 82
	.short _02068500 - _0206814E - 2; case 83
	.short _02068500 - _0206814E - 2; case 84
	.short _02068500 - _0206814E - 2; case 85
	.short _02068500 - _0206814E - 2; case 86
	.short _02068500 - _0206814E - 2; case 87
	.short _02068500 - _0206814E - 2; case 88
	.short _02068500 - _0206814E - 2; case 89
	.short _02068500 - _0206814E - 2; case 90
	.short _02068500 - _0206814E - 2; case 91
	.short _02068500 - _0206814E - 2; case 92
	.short _02068500 - _0206814E - 2; case 93
	.short _02068500 - _0206814E - 2; case 94
	.short _02068500 - _0206814E - 2; case 95
	.short _02068500 - _0206814E - 2; case 96
	.short _02068500 - _0206814E - 2; case 97
	.short _02068500 - _0206814E - 2; case 98
	.short _02068500 - _0206814E - 2; case 99
	.short _02068500 - _0206814E - 2; case 100
	.short _02068500 - _0206814E - 2; case 101
	.short _02068500 - _0206814E - 2; case 102
	.short _02068500 - _0206814E - 2; case 103
	.short _02068500 - _0206814E - 2; case 104
	.short _02068500 - _0206814E - 2; case 105
	.short _02068500 - _0206814E - 2; case 106
	.short _02068500 - _0206814E - 2; case 107
	.short _02068500 - _0206814E - 2; case 108
	.short _02068500 - _0206814E - 2; case 109
	.short _02068500 - _0206814E - 2; case 110
	.short _02068500 - _0206814E - 2; case 111
	.short _02068500 - _0206814E - 2; case 112
	.short _02068500 - _0206814E - 2; case 113
	.short _02068500 - _0206814E - 2; case 114
	.short _02068500 - _0206814E - 2; case 115
	.short _02068500 - _0206814E - 2; case 116
	.short _02068500 - _0206814E - 2; case 117
	.short _02068500 - _0206814E - 2; case 118
	.short _02068500 - _0206814E - 2; case 119
	.short _02068500 - _0206814E - 2; case 120
	.short _02068500 - _0206814E - 2; case 121
	.short _02068500 - _0206814E - 2; case 122
	.short _02068500 - _0206814E - 2; case 123
	.short _02068500 - _0206814E - 2; case 124
	.short _02068500 - _0206814E - 2; case 125
	.short _02068500 - _0206814E - 2; case 126
	.short _02068500 - _0206814E - 2; case 127
	.short _02068500 - _0206814E - 2; case 128
	.short _02068500 - _0206814E - 2; case 129
	.short _02068500 - _0206814E - 2; case 130
	.short _02068500 - _0206814E - 2; case 131
	.short _02068500 - _0206814E - 2; case 132
	.short _02068500 - _0206814E - 2; case 133
	.short _02068500 - _0206814E - 2; case 134
	.short _02068500 - _0206814E - 2; case 135
	.short _02068500 - _0206814E - 2; case 136
	.short _02068500 - _0206814E - 2; case 137
	.short _02068500 - _0206814E - 2; case 138
	.short _02068500 - _0206814E - 2; case 139
	.short _02068500 - _0206814E - 2; case 140
	.short _02068500 - _0206814E - 2; case 141
	.short _02068500 - _0206814E - 2; case 142
	.short _02068500 - _0206814E - 2; case 143
	.short _02068500 - _0206814E - 2; case 144
	.short _02068500 - _0206814E - 2; case 145
	.short _02068500 - _0206814E - 2; case 146
	.short _02068500 - _0206814E - 2; case 147
	.short _02068500 - _0206814E - 2; case 148
	.short _02068500 - _0206814E - 2; case 149
	.short _02068500 - _0206814E - 2; case 150
	.short _02068500 - _0206814E - 2; case 151
	.short _02068500 - _0206814E - 2; case 152
	.short _02068500 - _0206814E - 2; case 153
	.short _02068500 - _0206814E - 2; case 154
	.short _02068500 - _0206814E - 2; case 155
	.short _02068500 - _0206814E - 2; case 156
	.short _02068500 - _0206814E - 2; case 157
	.short _02068500 - _0206814E - 2; case 158
	.short _02068500 - _0206814E - 2; case 159
	.short _02068500 - _0206814E - 2; case 160
	.short _02068500 - _0206814E - 2; case 161
	.short _02068500 - _0206814E - 2; case 162
	.short _02068500 - _0206814E - 2; case 163
	.short _02068500 - _0206814E - 2; case 164
	.short _02068500 - _0206814E - 2; case 165
	.short _02068500 - _0206814E - 2; case 166
	.short _02068500 - _0206814E - 2; case 167
	.short _02068500 - _0206814E - 2; case 168
	.short _02068500 - _0206814E - 2; case 169
	.short _02068500 - _0206814E - 2; case 170
	.short _02068500 - _0206814E - 2; case 171
	.short _02068500 - _0206814E - 2; case 172
	.short _02068500 - _0206814E - 2; case 173
	.short _02068500 - _0206814E - 2; case 174
	.short _02068500 - _0206814E - 2; case 175
	.short _02068500 - _0206814E - 2; case 176
	.short _02068500 - _0206814E - 2; case 177
	.short _02068500 - _0206814E - 2; case 178
_020682B4:
	ldrh r0, [r4, #0x0]
	mov r1, #0x64
	bl FUN_02068758
	ldr r1, [r4, #0x8]
	add r1, r1, r6
	cmp r1, r0
	bls _020682D2
	ldrh r0, [r4, #0x0]
	mov r1, #0x64
	bl FUN_02068758
	add sp, #0xc
	str r0, [r4, #0x8]
	pop {r4-r7, pc}
_020682D2:
	add sp, #0xc
	str r1, [r4, #0x8]
	pop {r4-r7, pc}
_020682D8:
	ldrb r0, [r4, #0xc]
	add r0, r0, r6
	cmp r0, #0xff
	ble _020682E8
	mov r0, #0xff
	add sp, #0xc
	strb r0, [r4, #0xc]
	pop {r4-r7, pc}
_020682E8:
	add sp, #0xc
	strb r0, [r4, #0xc]
	pop {r4-r7, pc}
_020682EE:
	ldrb r0, [r4, #0x10]
	add sp, #0xc
	add r0, r0, r6
	strb r0, [r4, #0x10]
	pop {r4-r7, pc}
_020682F8:
	ldrb r0, [r4, #0x11]
	add sp, #0xc
	add r0, r0, r6
	strb r0, [r4, #0x11]
	pop {r4-r7, pc}
_02068302:
	ldrb r0, [r4, #0x12]
	add sp, #0xc
	add r0, r0, r6
	strb r0, [r4, #0x12]
	pop {r4-r7, pc}
_0206830C:
	ldrb r0, [r4, #0x13]
	add sp, #0xc
	add r0, r0, r6
	strb r0, [r4, #0x13]
	pop {r4-r7, pc}
_02068316:
	ldrb r0, [r4, #0x14]
	add sp, #0xc
	add r0, r0, r6
	strb r0, [r4, #0x14]
	pop {r4-r7, pc}
_02068320:
	ldrb r0, [r4, #0x15]
	add sp, #0xc
	add r0, r0, r6
	strb r0, [r4, #0x15]
	pop {r4-r7, pc}
_0206832A:
	ldrb r0, [r4, #0x16]
	add r0, r0, r6
	cmp r0, #0xff
	ble _0206833A
	mov r0, #0xff
	add sp, #0xc
	strb r0, [r4, #0x16]
	pop {r4-r7, pc}
_0206833A:
	add sp, #0xc
	strb r0, [r4, #0x16]
	pop {r4-r7, pc}
_02068340:
	ldrb r0, [r4, #0x17]
	add r0, r0, r6
	cmp r0, #0xff
	ble _02068350
	mov r0, #0xff
	add sp, #0xc
	strb r0, [r4, #0x17]
	pop {r4-r7, pc}
_02068350:
	add sp, #0xc
	strb r0, [r4, #0x17]
	pop {r4-r7, pc}
_02068356:
	ldrb r0, [r4, #0x18]
	add r0, r0, r6
	cmp r0, #0xff
	ble _02068366
	mov r0, #0xff
	add sp, #0xc
	strb r0, [r4, #0x18]
	pop {r4-r7, pc}
_02068366:
	add sp, #0xc
	strb r0, [r4, #0x18]
	pop {r4-r7, pc}
_0206836C:
	ldrb r0, [r4, #0x19]
	add r0, r0, r6
	cmp r0, #0xff
	ble _0206837C
	mov r0, #0xff
	add sp, #0xc
	strb r0, [r4, #0x19]
	pop {r4-r7, pc}
_0206837C:
	add sp, #0xc
	strb r0, [r4, #0x19]
	pop {r4-r7, pc}
_02068382:
	ldrb r0, [r4, #0x1a]
	add r0, r0, r6
	cmp r0, #0xff
	ble _02068392
	mov r0, #0xff
	add sp, #0xc
	strb r0, [r4, #0x1a]
	pop {r4-r7, pc}
_02068392:
	add sp, #0xc
	strb r0, [r4, #0x1a]
	pop {r4-r7, pc}
_02068398:
	ldrb r0, [r4, #0x1b]
	add r0, r0, r6
	cmp r0, #0xff
	ble _020683A8
	mov r0, #0xff
	add sp, #0xc
	strb r0, [r4, #0x1b]
	pop {r4-r7, pc}
_020683A8:
	add sp, #0xc
	strb r0, [r4, #0x1b]
	pop {r4-r7, pc}
_020683AE:
	add r0, r5, #0x0
	str r0, [sp, #0x4]
	add r0, #0xc
	str r0, [sp, #0x4]
	sub r7, #0x3a
	ldr r1, [sp, #0x4]
	lsl r0, r7, #0x1
	str r0, [sp, #0x8]
	add r4, r5, #0x0
	ldrh r0, [r5, r0]
	ldrb r1, [r1, r7]
	add r4, #0x8
	bl FUN_0206AB30
	ldrb r1, [r4, r7]
	add r1, r6, r1
	cmp r1, r0
	ble _020683E4
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x4]
	ldrh r0, [r5, r0]
	ldrb r1, [r1, r7]
	bl FUN_0206AB30
	add sp, #0xc
	strb r0, [r4, r7]
	pop {r4-r7, pc}
_020683E4:
	add sp, #0xc
	strb r1, [r4, r7]
	pop {r4-r7, pc}
_020683EA:
	add r5, #0xc
	sub r7, #0x3e
	ldrb r0, [r5, r7]
	add r0, r6, r0
	cmp r0, #0x3
	ble _020683FE
	mov r0, #0x3
	add sp, #0xc
	strb r0, [r5, r7]
	pop {r4-r7, pc}
_020683FE:
	add sp, #0xc
	strb r0, [r5, r7]
	pop {r4-r7, pc}
_02068404:
	ldr r1, [r5, #0x10]
	lsl r0, r1, #0x1b
	lsr r0, r0, #0x1b
	add r2, r0, r6
	cmp r2, #0x1f
	bls _0206841E
	mov r0, #0x1f
	bic r1, r0
	mov r0, #0x1f
	orr r0, r1
	add sp, #0xc
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_0206841E:
	mov r0, #0x1f
	bic r1, r0
	mov r0, #0x1f
	and r0, r2
	orr r0, r1
	add sp, #0xc
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_0206842E:
	ldr r1, [r5, #0x10]
	lsl r0, r1, #0x16
	lsr r0, r0, #0x1b
	add r2, r0, r6
	cmp r2, #0x1f
	ldr r0, _02068508 ; =0xFFFFFC1F
	bls _0206844A
	and r1, r0
	mov r0, #0x3e
	lsl r0, r0, #0x4
	orr r0, r1
	add sp, #0xc
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_0206844A:
	and r1, r0
	lsl r0, r2, #0x1b
	lsr r0, r0, #0x16
	orr r0, r1
	add sp, #0xc
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_02068458:
	ldr r1, [r5, #0x10]
	lsl r0, r1, #0x11
	lsr r0, r0, #0x1b
	add r2, r0, r6
	cmp r2, #0x1f
	ldr r0, _0206850C ; =0xFFFF83FF
	bls _02068474
	and r1, r0
	mov r0, #0x1f
	lsl r0, r0, #0xa
	orr r0, r1
	add sp, #0xc
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_02068474:
	and r1, r0
	lsl r0, r2, #0x1b
	lsr r0, r0, #0x11
	orr r0, r1
	add sp, #0xc
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_02068482:
	ldr r1, [r5, #0x10]
	lsl r0, r1, #0xc
	lsr r0, r0, #0x1b
	add r2, r0, r6
	cmp r2, #0x1f
	ldr r0, _02068510 ; =0xFFF07FFF
	bls _0206849E
	and r1, r0
	mov r0, #0x3e
	lsl r0, r0, #0xe
	orr r0, r1
	add sp, #0xc
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_0206849E:
	and r1, r0
	lsl r0, r2, #0x1b
	lsr r0, r0, #0xc
	orr r0, r1
	add sp, #0xc
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_020684AC:
	ldr r1, [r5, #0x10]
	lsl r0, r1, #0x7
	lsr r0, r0, #0x1b
	add r2, r0, r6
	cmp r2, #0x1f
	ldr r0, _02068514 ; =0xFE0FFFFF
	bls _020684C8
	and r1, r0
	mov r0, #0x1f
	lsl r0, r0, #0x14
	orr r0, r1
	add sp, #0xc
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_020684C8:
	and r1, r0
	lsl r0, r2, #0x1b
	lsr r0, r0, #0x7
	orr r0, r1
	add sp, #0xc
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_020684D6:
	ldr r1, [r5, #0x10]
	lsl r0, r1, #0x2
	lsr r0, r0, #0x1b
	add r2, r0, r6
	cmp r2, #0x1f
	ldr r0, _02068518 ; =0xC1FFFFFF
	bls _020684F2
	and r1, r0
	mov r0, #0x3e
	lsl r0, r0, #0x18
	orr r0, r1
	add sp, #0xc
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_020684F2:
	and r1, r0
	lsl r0, r2, #0x1b
	lsr r0, r0, #0x2
	orr r0, r1
	add sp, #0xc
	str r0, [r5, #0x10]
	pop {r4-r7, pc}
_02068500:
	bl ErrorHandling
_02068504:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02068508: .word 0xFFFFFC1F
_0206850C: .word 0xFFFF83FF
_02068510: .word 0xFFF07FFF
_02068514: .word 0xFE0FFFFF
_02068518: .word 0xC1FFFFFF

	thumb_func_start FUN_0206851C
FUN_0206851C: ; 0x0206851C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x2c
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0206A370
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02068538
FUN_02068538: ; 0x02068538
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r6, r1, #0x0
	cmp r4, #0x0
	bne _02068546
	bl ErrorHandling
_02068546:
	cmp r6, #0x20
	bhi _0206863A
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02068556: ; jump table (using 16-bit offset)
	.short _02068598 - _02068556 - 2; case 0
	.short _0206859C - _02068556 - 2; case 1
	.short _020685A0 - _02068556 - 2; case 2
	.short _020685A4 - _02068556 - 2; case 3
	.short _020685A8 - _02068556 - 2; case 4
	.short _020685AC - _02068556 - 2; case 5
	.short _020685B0 - _02068556 - 2; case 6
	.short _020685B4 - _02068556 - 2; case 7
	.short _020685B8 - _02068556 - 2; case 8
	.short _020685BC - _02068556 - 2; case 9
	.short _020685C0 - _02068556 - 2; case 10
	.short _020685C8 - _02068556 - 2; case 11
	.short _020685D0 - _02068556 - 2; case 12
	.short _020685D8 - _02068556 - 2; case 13
	.short _020685E0 - _02068556 - 2; case 14
	.short _020685E8 - _02068556 - 2; case 15
	.short _020685F0 - _02068556 - 2; case 16
	.short _020685F4 - _02068556 - 2; case 17
	.short _020685F8 - _02068556 - 2; case 18
	.short _020685FC - _02068556 - 2; case 19
	.short _02068600 - _02068556 - 2; case 20
	.short _02068604 - _02068556 - 2; case 21
	.short _02068608 - _02068556 - 2; case 22
	.short _0206860C - _02068556 - 2; case 23
	.short _02068610 - _02068556 - 2; case 24
	.short _02068614 - _02068556 - 2; case 25
	.short _02068618 - _02068556 - 2; case 26
	.short _0206861C - _02068556 - 2; case 27
	.short _02068624 - _02068556 - 2; case 28
	.short _0206862C - _02068556 - 2; case 29
	.short _02068630 - _02068556 - 2; case 30
	.short _02068634 - _02068556 - 2; case 31
	.short _02068638 - _02068556 - 2; case 32
_02068598:
	ldrb r5, [r4, #0x0]
	b _0206863A
_0206859C:
	ldrb r5, [r4, #0x1]
	b _0206863A
_020685A0:
	ldrb r5, [r4, #0x2]
	b _0206863A
_020685A4:
	ldrb r5, [r4, #0x3]
	b _0206863A
_020685A8:
	ldrb r5, [r4, #0x4]
	b _0206863A
_020685AC:
	ldrb r5, [r4, #0x5]
	b _0206863A
_020685B0:
	ldrb r5, [r4, #0x6]
	b _0206863A
_020685B4:
	ldrb r5, [r4, #0x7]
	b _0206863A
_020685B8:
	ldrb r5, [r4, #0x8]
	b _0206863A
_020685BC:
	ldrb r5, [r4, #0x9]
	b _0206863A
_020685C0:
	ldrh r0, [r4, #0xa]
	lsl r0, r0, #0x1e
	lsr r5, r0, #0x1e
	b _0206863A
_020685C8:
	ldrh r0, [r4, #0xa]
	lsl r0, r0, #0x1c
	lsr r5, r0, #0x1e
	b _0206863A
_020685D0:
	ldrh r0, [r4, #0xa]
	lsl r0, r0, #0x1a
	lsr r5, r0, #0x1e
	b _0206863A
_020685D8:
	ldrh r0, [r4, #0xa]
	lsl r0, r0, #0x18
	lsr r5, r0, #0x1e
	b _0206863A
_020685E0:
	ldrh r0, [r4, #0xa]
	lsl r0, r0, #0x16
	lsr r5, r0, #0x1e
	b _0206863A
_020685E8:
	ldrh r0, [r4, #0xa]
	lsl r0, r0, #0x14
	lsr r5, r0, #0x1e
	b _0206863A
_020685F0:
	ldrh r5, [r4, #0xc]
	b _0206863A
_020685F4:
	ldrh r5, [r4, #0xe]
	b _0206863A
_020685F8:
	ldrb r5, [r4, #0x10]
	b _0206863A
_020685FC:
	ldrb r5, [r4, #0x11]
	b _0206863A
_02068600:
	ldrb r5, [r4, #0x12]
	b _0206863A
_02068604:
	ldrb r5, [r4, #0x13]
	b _0206863A
_02068608:
	ldrb r5, [r4, #0x14]
	b _0206863A
_0206860C:
	ldrb r5, [r4, #0x15]
	b _0206863A
_02068610:
	ldrb r5, [r4, #0x16]
	b _0206863A
_02068614:
	ldrb r5, [r4, #0x17]
	b _0206863A
_02068618:
	ldrb r5, [r4, #0x18]
	b _0206863A
_0206861C:
	ldrb r0, [r4, #0x19]
	lsl r0, r0, #0x19
	lsr r5, r0, #0x19
	b _0206863A
_02068624:
	ldrb r0, [r4, #0x19]
	lsl r0, r0, #0x18
	lsr r5, r0, #0x1f
	b _0206863A
_0206862C:
	ldr r5, [r4, #0x1c]
	b _0206863A
_02068630:
	ldr r5, [r4, #0x20]
	b _0206863A
_02068634:
	ldr r5, [r4, #0x24]
	b _0206863A
_02068638:
	ldr r5, [r4, #0x28]
_0206863A:
	add r0, r5, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02068640
FUN_02068640: ; 0x02068640
	push {r4, lr}
	add r4, r0, #0x0
	bne _0206864A
	bl ErrorHandling
_0206864A:
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02068654
FUN_02068654: ; 0x02068654
	push {r3-r5, lr}
	add r4, r2, #0x0
	bl ConvertUnownOrArceusSpecies
	mov r1, #0x0
	bl FUN_0206851C
	add r5, r0, #0x0
	add r1, r4, #0x0
	bl FUN_02068538
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02068640
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02068678
FUN_02068678: ; 0x02068678
	push {r3-r5, lr}
	add r4, r1, #0x0
	mov r1, #0x0
	bl FUN_0206851C
	add r5, r0, #0x0
	add r1, r4, #0x0
	bl FUN_02068538
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02068640
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02068698
FUN_02068698: ; 0x02068698
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_020669D4
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r0, r5, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_02068758
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r7, #0x1
	bl FUN_02068758
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x8
	mov r2, #0x0
	bl FUN_020671BC
	add r7, r0, #0x0
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02066A20
	sub r1, r7, r4
	mov r0, #0x64
	mul r0, r1
	sub r1, r6, r4
	bl _u32_div_f
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3-r7, pc}

	thumb_func_start FUN_020686F8
FUN_020686F8: ; 0x020686F8
	ldr r3, _020686FC ; =FUN_02068700
	bx r3
	.balign 4
_020686FC: .word FUN_02068700

	thumb_func_start FUN_02068700
FUN_02068700: ; 0x02068700
	push {r4-r6, lr}
	mov r1, #0x5
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_020672BC
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r0, r4, #0x0
	bl FUN_020687C8
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r4, #0x0
	mov r1, #0x8
	mov r2, #0x0
	bl FUN_020672BC
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02068758
	sub r0, r0, r4
	pop {r4-r6, pc}

	thumb_func_start FUN_02068734
FUN_02068734: ; 0x02068734
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02068758
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02068758
FUN_02068758: ; 0x02068758
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x15
	bl FUN_02068678
	add r1, r4, #0x0
	bl GetExpByGrowthRateAndLevel
	pop {r4, pc}
	.balign 4

	thumb_func_start LoadGrowthTable
LoadGrowthTable: ; 0x0206876C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x8
	blt _0206877A
	bl ErrorHandling
_0206877A:
	add r0, r4, #0x0
	mov r1, #0x3 ; NARC_POKETOOL_PERSONAL_GROWTBL
	add r2, r5, #0x0
	bl ReadWholeNarcMemberByIdPair
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start GetExpByGrowthRateAndLevel
GetExpByGrowthRateAndLevel: ; 0x02068788
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	cmp r6, #0x8
	blt _02068796
	bl ErrorHandling
_02068796:
	cmp r5, #0x65
	ble _0206879E
	bl ErrorHandling
_0206879E:
	mov r1, #0x65
	mov r0, #0x0
	lsl r1, r1, #0x2
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl LoadGrowthTable
	lsl r0, r5, #0x2
	ldr r5, [r4, r0]
	add r0, r4, #0x0
	bl FreeToHeap
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020687C0
FUN_020687C0: ; 0x020687C0
	ldr r3, _020687C4 ; =FUN_020687C8
	bx r3
	.balign 4
_020687C4: .word FUN_020687C8

	thumb_func_start FUN_020687C8
FUN_020687C8: ; 0x020687C8
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_02066A6C
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020672BC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x8
	mov r2, #0x0
	bl FUN_020672BC
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02066A94
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	add r1, r7, #0x0
	bl FUN_02068800
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02068800
FUN_02068800: ; 0x02068800
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	mov r1, #0x0
	bl FUN_0206851C
	add r6, r0, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02068824
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02068640
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02068824
FUN_02068824: ; 0x02068824
	push {r4, lr}
	mov r1, #0x15
	add r4, r2, #0x0
	bl FUN_02068538
	ldr r1, _0206884C ; =UNK_021C5AC0
	bl LoadGrowthTable
	ldr r2, _02068850 ; =UNK_021C5AC0 + 4
	mov r1, #0x1
_02068838:
	ldr r0, [r2, #0x0]
	cmp r0, r4
	bhi _02068846
	add r1, r1, #0x1
	add r2, r2, #0x4
	cmp r1, #0x65
	blt _02068838
_02068846:
	sub r0, r1, #0x1
	pop {r4, pc}
	nop
_0206884C: .word UNK_021C5AC0
_02068850: .word UNK_021C5AC0 + 4

	thumb_func_start FUN_02068854
FUN_02068854: ; 0x02068854
	ldr r3, _02068858 ; =FUN_0206885C
	bx r3
	.balign 4
_02068858: .word FUN_0206885C

	thumb_func_start FUN_0206885C
FUN_0206885C: ; 0x0206885C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02066A6C
	mov r1, #0x0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_020672BC
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02066A94
	add r0, r6, #0x0
	bl GetNatureFromPersonality
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start GetNatureFromPersonality
GetNatureFromPersonality: ; 0x02068884
	push {r3, lr}
	mov r1, #0x19
	bl _u32_div_f
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02068894
FUN_02068894: ; 0x02068894
	push {r3, lr}
	cmp r2, #0x1
	blo _0206889E
	cmp r2, #0x5
	bls _020688A2
_0206889E:
	add r0, r1, #0x0
	pop {r3, pc}
_020688A2:
	lsl r3, r0, #0x2
	add r3, r0, r3
	ldr r0, _020688E4 ; =UNK_020F7F93
	sub r2, r2, #0x1
	add r0, r0, r3
	ldrsb r2, [r2, r0]
	mov r0, #0x0
	mvn r0, r0
	cmp r2, r0
	beq _020688CE
	cmp r2, #0x1
	bne _020688E0
	mov r0, #0x6e
	mul r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	b _020688E0
_020688CE:
	mov r0, #0x5a
	mul r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
_020688E0:
	add r0, r1, #0x0
	pop {r3, pc}
	.balign 4
_020688E4: .word UNK_020F7F93

	thumb_func_start FUN_020688E8
FUN_020688E8: ; 0x020688E8
	push {r3-r7, lr}
	sub sp, #0x8
	add r6, r1, #0x0
	add r5, r0, #0x0
	str r2, [sp, #0x0]
	cmp r6, #0x5
	bne _02068900
	bl rand_LC
	mov r1, #0x1
	tst r0, r1
	bne _020689D4
_02068900:
	add r0, r5, #0x0
	mov r1, #0xad
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	beq _020689D4
	ldr r0, _020689D8 ; =0x000001EE
	cmp r1, r0
	beq _020689D4
	add r0, r5, #0x0
	mov r1, #0x6
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_0206E7B8
	lsl r0, r0, #0x18
	mov r4, #0x0
	lsr r7, r0, #0x18
	add r0, r5, #0x0
	mov r1, #0x9
	add r2, r4, #0x0
	bl FUN_020671BC
	add r1, sp, #0x4
	strh r0, [r1, #0x0]
	add r0, r4, #0x0
	ldrsh r1, [r1, r0]
	cmp r1, #0x64
	blt _0206894E
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_0206894E:
	cmp r1, #0xc8
	blt _02068958
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02068958:
	lsl r0, r6, #0x1
	add r1, r6, r0
	ldr r0, _020689DC ; =UNK_020F7ED4
	add r0, r0, r1
	ldrsb r4, [r4, r0]
	cmp r4, #0x0
	ble _0206897A
	add r0, r5, #0x0
	mov r1, #0x9a
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0xb
	bne _0206897A
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	asr r4, r0, #0x18
_0206897A:
	cmp r4, #0x0
	ble _02068994
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl FUN_020671BC
	ldr r1, [sp, #0x0]
	cmp r1, r0
	bne _02068994
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	asr r4, r0, #0x18
_02068994:
	cmp r4, #0x0
	ble _020689AA
	cmp r7, #0x34
	bne _020689AA
	mov r0, #0x96
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x18
	asr r4, r0, #0x18
_020689AA:
	add r0, sp, #0x4
	mov r1, #0x0
	ldrsh r2, [r0, r1]
	add r2, r2, r4
	strh r2, [r0, #0x0]
	ldrsh r2, [r0, r1]
	cmp r2, #0x0
	bge _020689BC
	strh r1, [r0, #0x0]
_020689BC:
	add r1, sp, #0x4
	mov r0, #0x0
	ldrsh r0, [r1, r0]
	cmp r0, #0xff
	ble _020689CA
	mov r0, #0xff
	strh r0, [r1, #0x0]
_020689CA:
	add r0, r5, #0x0
	mov r1, #0x9
	add r2, sp, #0x4
	bl FUN_02067830
_020689D4:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_020689D8: .word 0x000001EE
_020689DC: .word UNK_020F7ED4

	thumb_func_start FUN_020689E0
FUN_020689E0: ; 0x020689E0
	ldr r3, _020689E4 ; =FUN_020689E8
	bx r3
	.balign 4
_020689E4: .word FUN_020689E8

	thumb_func_start FUN_020689E8
FUN_020689E8: ; 0x020689E8
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_02066A6C
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020672BC
	lsl r0, r0, #0x10
	mov r1, #0x0
	lsr r4, r0, #0x10
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_020672BC
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02066A94
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_02068A20
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02068A20
FUN_02068A20: ; 0x02068A20
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	mov r1, #0x0
	bl FUN_0206851C
	add r6, r0, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02068A44
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02068640
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02068A44
FUN_02068A44: ; 0x02068A44
	push {r4, lr}
	mov r1, #0x12
	add r4, r2, #0x0
	bl FUN_02068538
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	beq _02068A5E
	cmp r1, #0xfe
	beq _02068A62
	cmp r1, #0xff
	beq _02068A66
	b _02068A6A
_02068A5E:
	mov r0, #0x0
	pop {r4, pc}
_02068A62:
	mov r0, #0x1
	pop {r4, pc}
_02068A66:
	mov r0, #0x2
	pop {r4, pc}
_02068A6A:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	cmp r1, r0
	bls _02068A76
	mov r0, #0x1
	b _02068A78
_02068A76:
	mov r0, #0x0
_02068A78:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02068A80
FUN_02068A80: ; 0x02068A80
	ldr r3, _02068A84 ; =FUN_02068A88
	bx r3
	.balign 4
_02068A84: .word FUN_02068A88

	thumb_func_start FUN_02068A88
FUN_02068A88: ; 0x02068A88
	push {r3-r5, lr}
	mov r1, #0x7
	mov r2, #0x0
	add r5, r0, #0x0
	bl FUN_020672BC
	mov r1, #0x0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_020672BC
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02068AAC
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02068AAC
FUN_02068AAC: ; 0x02068AAC
	ldr r3, _02068AD4 ; =0xFFFF0000
	lsl r2, r1, #0x10
	and r1, r3
	and r3, r0
	lsl r0, r0, #0x10
	lsr r3, r3, #0x10
	lsr r0, r0, #0x10
	lsr r1, r1, #0x10
	eor r0, r3
	lsr r2, r2, #0x10
	eor r0, r1
	eor r0, r2
	cmp r0, #0x8
	bhs _02068ACC
	mov r0, #0x1
	b _02068ACE
_02068ACC:
	mov r0, #0x0
_02068ACE:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
	.balign 4
_02068AD4: .word 0xFFFF0000

	thumb_func_start FUN_02068AD8
FUN_02068AD8: ; 0x02068AD8
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, _02068B64 ; =0xFFFF0000
	and r0, r7
	lsr r1, r0, #0x10
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	eor r0, r1
	lsr r7, r0, #0x3
	bl rand_LC
	mov r1, #0x7
	and r0, r1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	bl rand_LC
	mov r1, #0x7
	and r0, r1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	mov r4, #0x0
_02068B04:
	add r0, r4, #0x0
	bl MaskOfFlagNo
	tst r0, r7
	beq _02068B34
	bl rand_LC
	mov r1, #0x1
	tst r0, r1
	beq _02068B26
	add r0, r4, #0x3
	bl MaskOfFlagNo
	orr r0, r6
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	b _02068B56
_02068B26:
	add r0, r4, #0x3
	bl MaskOfFlagNo
	orr r0, r5
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	b _02068B56
_02068B34:
	bl rand_LC
	mov r1, #0x1
	tst r0, r1
	beq _02068B56
	add r0, r4, #0x3
	bl MaskOfFlagNo
	orr r0, r6
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r0, r4, #0x3
	bl MaskOfFlagNo
	orr r0, r5
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
_02068B56:
	add r4, r4, #0x1
	cmp r4, #0xd
	blt _02068B04
	lsl r0, r5, #0x10
	orr r0, r6
	pop {r3-r7, pc}
	nop
_02068B64: .word 0xFFFF0000

	thumb_func_start FUN_02068B68
FUN_02068B68: ; 0x02068B68
	ldr r3, _02068B6C ; =FUN_02068B70
	bx r3
	.balign 4
_02068B6C: .word FUN_02068B70

	thumb_func_start FUN_02068B70
FUN_02068B70: ; 0x02068B70
	push {r4-r7, lr}
	sub sp, #0x1c
	add r5, r1, #0x0
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	str r2, [sp, #0x10]
	bl FUN_02066A6C
	str r0, [sp, #0x18]
	add r0, r5, #0x0
	mov r1, #0xad
	mov r2, #0x0
	bl FUN_020672BC
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r5, #0x0
	bl FUN_020689E8
	str r0, [sp, #0x14]
	add r0, r5, #0x0
	bl FUN_02068A88
	mov r1, #0x0
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_020672BC
	add r6, r0, #0x0
	ldr r0, _02068BF8 ; =0x000001EE
	cmp r4, r0
	bne _02068BCA
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020672BC
	ldr r1, _02068BFC ; =0x000001EA
	cmp r0, r1
	bne _02068BC6
	mov r0, #0x1
	b _02068BD8
_02068BC6:
	mov r0, #0x0
	b _02068BD8
_02068BCA:
	add r0, r5, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020672BC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
_02068BD8:
	str r7, [sp, #0x0]
	str r0, [sp, #0x4]
	str r6, [sp, #0x8]
	ldr r0, [sp, #0xc]
	ldr r2, [sp, #0x14]
	ldr r3, [sp, #0x10]
	add r1, r4, #0x0
	bl FUN_02068C00
	ldr r1, [sp, #0x18]
	add r0, r5, #0x0
	bl FUN_02066A94
	add sp, #0x1c
	pop {r4-r7, pc}
	nop
_02068BF8: .word 0x000001EE
_02068BFC: .word 0x000001EA

	thumb_func_start FUN_02068C00
FUN_02068C00: ; 0x02068C00
	push {r4-r7}
	add r7, r2, #0x0
	add r5, r3, #0x0
	add r4, r0, #0x0
	add r0, r1, #0x0
	ldr r3, [sp, #0x10]
	ldr r2, [sp, #0x14]
	mov r1, #0x0
	strh r1, [r4, #0x6]
	strb r1, [r4, #0x8]
	str r1, [r4, #0xc]
	ldr r1, _02068E0C ; =0x000001A5
	cmp r0, r1
	bgt _02068C68
	bge _02068D1E
	add r6, r1, #0x0
	sub r6, #0x46
	cmp r0, r6
	bgt _02068C36
	sub r1, #0x46
	cmp r0, r1
	blt _02068C2E
	b _02068D58
_02068C2E:
	cmp r0, #0xc9
	bne _02068C34
	b _02068D90
_02068C34:
	b _02068DD4
_02068C36:
	add r6, r1, #0x0
	sub r6, #0x23
	cmp r0, r6
	bgt _02068C48
	sub r1, #0x23
	cmp r0, r1
	bne _02068C46
	b _02068D76
_02068C46:
	b _02068DD4
_02068C48:
	add r6, r1, #0x0
	sub r6, #0x8
	cmp r0, r6
	bgt _02068C66
	add r6, r1, #0x0
	sub r6, #0x9
	cmp r0, r6
	blt _02068C66
	add r6, r1, #0x0
	sub r6, #0x9
	cmp r0, r6
	beq _02068CAA
	sub r1, #0x8
	cmp r0, r1
	beq _02068CC8
_02068C66:
	b _02068DD4
_02068C68:
	add r6, r1, #0x0
	add r6, #0x48
	cmp r0, r6
	bgt _02068C8E
	add r6, r1, #0x0
	add r6, #0x48
	cmp r0, r6
	bge _02068D3A
	add r6, r1, #0x2
	cmp r0, r6
	bgt _02068C8C
	add r6, r1, #0x1
	cmp r0, r6
	blt _02068C8C
	beq _02068CE6
	add r1, r1, #0x2
	cmp r0, r1
	beq _02068D02
_02068C8C:
	b _02068DD4
_02068C8E:
	add r6, r1, #0x0
	add r6, #0x49
	cmp r0, r6
	bgt _02068CA0
	add r1, #0x49
	cmp r0, r1
	bne _02068C9E
	b _02068DAC
_02068C9E:
	b _02068DD4
_02068CA0:
	add r1, #0x4a
	cmp r0, r1
	bne _02068CA8
	b _02068DC4
_02068CA8:
	b _02068DD4
_02068CAA:
	cmp r2, #0x2
	bls _02068CB0
	mov r2, #0x0
_02068CB0:
	mov r0, #0x75
	strh r0, [r4, #0x0]
	lsr r0, r5, #0x1
	lsl r1, r2, #0x1
	add r0, #0x48
	add r0, r0, r1
	add r3, #0x92
	strh r0, [r4, #0x2]
	add r0, r3, r1
	strh r0, [r4, #0x4]
	pop {r4-r7}
	bx lr
_02068CC8:
	cmp r2, #0x2
	bls _02068CCE
	mov r2, #0x0
_02068CCE:
	mov r0, #0x75
	strh r0, [r4, #0x0]
	lsr r0, r5, #0x1
	lsl r1, r2, #0x1
	add r0, #0x4e
	add r0, r0, r1
	add r3, #0x98
	strh r0, [r4, #0x2]
	add r0, r3, r1
	strh r0, [r4, #0x4]
	pop {r4-r7}
	bx lr
_02068CE6:
	cmp r2, #0x1
	bls _02068CEC
	mov r2, #0x0
_02068CEC:
	mov r0, #0x75
	add r5, #0x54
	strh r0, [r4, #0x0]
	add r0, r5, r2
	strh r0, [r4, #0x2]
	add r3, #0x9e
	lsl r0, r2, #0x1
	add r0, r3, r0
	strh r0, [r4, #0x4]
	pop {r4-r7}
	bx lr
_02068D02:
	cmp r2, #0x1
	bls _02068D08
	mov r2, #0x0
_02068D08:
	mov r0, #0x75
	add r5, #0x58
	strh r0, [r4, #0x0]
	add r0, r5, r2
	strh r0, [r4, #0x2]
	add r3, #0xa2
	lsl r0, r2, #0x1
	add r0, r3, r0
	strh r0, [r4, #0x4]
	pop {r4-r7}
	bx lr
_02068D1E:
	cmp r2, #0x1
	bls _02068D24
	mov r2, #0x0
_02068D24:
	mov r0, #0x75
	add r5, #0x5c
	strh r0, [r4, #0x0]
	add r0, r5, r2
	strh r0, [r4, #0x2]
	lsl r0, r3, #0x1
	add r0, #0xa6
	add r0, r2, r0
	strh r0, [r4, #0x4]
	pop {r4-r7}
	bx lr
_02068D3A:
	cmp r2, #0x11
	bls _02068D40
	mov r2, #0x0
_02068D40:
	mov r0, #0x75
	strh r0, [r4, #0x0]
	lsr r0, r5, #0x1
	lsl r1, r2, #0x1
	add r0, #0x60
	add r0, r0, r1
	add r3, #0xaa
	strh r0, [r4, #0x2]
	add r0, r3, r1
	strh r0, [r4, #0x4]
	pop {r4-r7}
	bx lr
_02068D58:
	cmp r2, #0x3
	bls _02068D5E
	mov r2, #0x0
_02068D5E:
	mov r0, #0x75
	strh r0, [r4, #0x0]
	lsl r0, r5, #0x1
	add r0, #0x40
	add r0, r2, r0
	strh r0, [r4, #0x2]
	lsl r0, r3, #0x2
	add r0, #0x8a
	add r0, r2, r0
	strh r0, [r4, #0x4]
	pop {r4-r7}
	bx lr
_02068D76:
	cmp r2, #0x3
	bls _02068D7C
	mov r2, #0x0
_02068D7C:
	mov r0, #0x75
	strh r0, [r4, #0x0]
	lsr r1, r5, #0x1
	lsl r0, r2, #0x1
	add r0, r1, r0
	strh r0, [r4, #0x2]
	add r3, #0x86
	strh r3, [r4, #0x4]
	pop {r4-r7}
	bx lr
_02068D90:
	cmp r2, #0x1c
	blo _02068D96
	mov r2, #0x0
_02068D96:
	mov r0, #0x75
	lsr r1, r5, #0x1
	strh r0, [r4, #0x0]
	add r1, #0x8
	lsl r0, r2, #0x1
	add r0, r1, r0
	strh r0, [r4, #0x2]
	add r3, #0x88
	strh r3, [r4, #0x4]
	pop {r4-r7}
	bx lr
_02068DAC:
	cmp r2, #0x1
	bls _02068DB2
	mov r2, #0x0
_02068DB2:
	mov r0, #0x75
	strh r0, [r4, #0x0]
	add r0, r2, #0x0
	add r0, #0x84
	strh r0, [r4, #0x2]
	add r2, #0xce
	strh r2, [r4, #0x4]
	pop {r4-r7}
	bx lr
_02068DC4:
	mov r0, #0x75
	strh r0, [r4, #0x0]
	mov r0, #0x84
	strh r0, [r4, #0x2]
	mov r0, #0xce
	strh r0, [r4, #0x4]
	pop {r4-r7}
	bx lr
_02068DD4:
	mov r1, #0x4
	strh r1, [r4, #0x0]
	cmp r7, #0x1
	beq _02068DE0
	mov r2, #0x1
	b _02068DE2
_02068DE0:
	mov r2, #0x0
_02068DE2:
	mov r1, #0x6
	mul r1, r0
	add r6, r5, r1
	add r2, r6, r2
	add r1, r1, #0x4
	strh r2, [r4, #0x2]
	add r1, r3, r1
	strh r1, [r4, #0x4]
	ldr r1, _02068E10 ; =0x00000147
	cmp r0, r1
	bne _02068E06
	cmp r5, #0x2
	bne _02068E06
	strh r1, [r4, #0x6]
	mov r0, #0x0
	strb r0, [r4, #0x8]
	ldr r0, [sp, #0x18]
	str r0, [r4, #0xc]
_02068E06:
	pop {r4-r7}
	bx lr
	nop
_02068E0C: .word 0x000001A5
_02068E10: .word 0x00000147

	thumb_func_start FUN_02068E14
FUN_02068E14: ; 0x02068E14
	ldr r3, _02068E18 ; =FUN_02068E1C
	bx r3
	.balign 4
_02068E18: .word FUN_02068E1C

	thumb_func_start FUN_02068E1C
FUN_02068E1C: ; 0x02068E1C
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r1, #0x0
	mov r1, #0xad
	mov r2, #0x0
	add r5, r0, #0x0
	bl FUN_020672BC
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r5, #0x0
	bl FUN_020689E8
	mov r1, #0x0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_020672BC
	add r6, r0, #0x0
	ldr r0, _02068E80 ; =0x000001EE
	cmp r4, r0
	bne _02068E62
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020672BC
	ldr r1, _02068E84 ; =0x000001EA
	cmp r0, r1
	bne _02068E5E
	mov r3, #0x1
	b _02068E70
_02068E5E:
	mov r3, #0x0
	b _02068E70
_02068E62:
	add r0, r5, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020672BC
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
_02068E70:
	str r6, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r0, r4, #0x0
	add r2, r7, #0x0
	bl FUN_02068E88
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02068E80: .word 0x000001EE
_02068E84: .word 0x000001EA

	thumb_func_start FUN_02068E88
FUN_02068E88: ; 0x02068E88
	push {r3-r5, lr}
	ldr r4, _02068FDC ; =0x000001A5
	cmp r0, r4
	bgt _02068ED6
	bge _02068F54
	add r5, r4, #0x0
	sub r5, #0x46
	cmp r0, r5
	bgt _02068EA6
	sub r4, #0x46
	cmp r0, r4
	bge _02068F74
	cmp r0, #0xc9
	beq _02068F94
	b _02068FB8
_02068EA6:
	add r5, r4, #0x0
	sub r5, #0x23
	cmp r0, r5
	bgt _02068EB6
	sub r4, #0x23
	cmp r0, r4
	beq _02068F84
	b _02068FB8
_02068EB6:
	add r5, r4, #0x0
	sub r5, #0x8
	cmp r0, r5
	bgt _02068FB8
	add r5, r4, #0x0
	sub r5, #0x9
	cmp r0, r5
	blt _02068FB8
	add r5, r4, #0x0
	sub r5, #0x9
	cmp r0, r5
	beq _02068F14
	sub r4, #0x8
	cmp r0, r4
	beq _02068F26
	b _02068FB8
_02068ED6:
	add r5, r4, #0x0
	add r5, #0x48
	cmp r0, r5
	bgt _02068EFC
	add r5, r4, #0x0
	add r5, #0x48
	cmp r0, r5
	bge _02068F62
	add r5, r4, #0x2
	cmp r0, r5
	bgt _02068FB8
	add r5, r4, #0x1
	cmp r0, r5
	blt _02068FB8
	beq _02068F38
	add r4, r4, #0x2
	cmp r0, r4
	beq _02068F46
	b _02068FB8
_02068EFC:
	add r5, r4, #0x0
	add r5, #0x49
	cmp r0, r5
	bgt _02068F0C
	add r4, #0x49
	cmp r0, r4
	beq _02068FA6
	b _02068FB8
_02068F0C:
	add r4, #0x4a
	cmp r0, r4
	beq _02068FB2
	b _02068FB8
_02068F14:
	cmp r3, #0x2
	bls _02068F1A
	mov r3, #0x0
_02068F1A:
	lsr r1, r2, #0x1
	add r1, #0x48
	lsl r0, r3, #0x1
	mov r4, #0x79 ; NARC_POKETOOL_POKEGRA_HEIGHT_O
	add r3, r1, r0
	b _02068FCA
_02068F26:
	cmp r3, #0x2
	bls _02068F2C
	mov r3, #0x0
_02068F2C:
	lsr r1, r2, #0x1
	add r1, #0x4e
	lsl r0, r3, #0x1
	mov r4, #0x79 ; NARC_POKETOOL_POKEGRA_HEIGHT_O
	add r3, r1, r0
	b _02068FCA
_02068F38:
	cmp r3, #0x1
	bls _02068F3E
	mov r3, #0x0
_02068F3E:
	add r2, #0x54
	mov r4, #0x79 ; NARC_POKETOOL_POKEGRA_HEIGHT_O
	add r3, r2, r3
	b _02068FCA
_02068F46:
	cmp r3, #0x1
	bls _02068F4C
	mov r3, #0x0
_02068F4C:
	add r2, #0x58
	mov r4, #0x79 ; NARC_POKETOOL_POKEGRA_HEIGHT_O
	add r3, r2, r3
	b _02068FCA
_02068F54:
	cmp r3, #0x1
	bls _02068F5A
	mov r3, #0x0
_02068F5A:
	add r2, #0x5c
	mov r4, #0x79 ; NARC_POKETOOL_POKEGRA_HEIGHT_O
	add r3, r2, r3
	b _02068FCA
_02068F62:
	cmp r3, #0x11
	bls _02068F68
	mov r3, #0x0
_02068F68:
	lsr r1, r2, #0x1
	add r1, #0x60
	lsl r0, r3, #0x1
	mov r4, #0x79 ; NARC_POKETOOL_POKEGRA_HEIGHT_O
	add r3, r1, r0
	b _02068FCA
_02068F74:
	cmp r3, #0x3
	bls _02068F7A
	mov r3, #0x0
_02068F7A:
	lsl r0, r2, #0x1
	add r0, #0x40
	mov r4, #0x79 ; NARC_POKETOOL_POKEGRA_HEIGHT_O
	add r3, r3, r0
	b _02068FCA
_02068F84:
	cmp r3, #0x3
	bls _02068F8A
	mov r3, #0x0
_02068F8A:
	lsr r1, r2, #0x1
	lsl r0, r3, #0x1
	mov r4, #0x79 ; NARC_POKETOOL_POKEGRA_HEIGHT_O
	add r3, r1, r0
	b _02068FCA
_02068F94:
	cmp r3, #0x1c
	blo _02068F9A
	mov r3, #0x0
_02068F9A:
	lsr r1, r2, #0x1
	add r1, #0x8
	lsl r0, r3, #0x1
	mov r4, #0x79 ; NARC_POKETOOL_POKEGRA_HEIGHT_O
	add r3, r1, r0
	b _02068FCA
_02068FA6:
	cmp r3, #0x1
	bls _02068FAC
	mov r3, #0x0
_02068FAC:
	mov r4, #0x79 ; NARC_POKETOOL_POKEGRA_HEIGHT_O
	add r3, #0x84
	b _02068FCA
_02068FB2:
	mov r4, #0x79 ; NARC_POKETOOL_POKEGRA_HEIGHT_O
	mov r3, #0x84
	b _02068FCA
_02068FB8:
	mov r4, #0x5 ; NARC_POKETOOL_POKEGRA_HEIGHT
	cmp r1, #0x1
	beq _02068FC2
	mov r1, #0x1
	b _02068FC4
_02068FC2:
	mov r1, #0x0
_02068FC4:
	lsl r0, r0, #0x2
	add r0, r2, r0
	add r3, r0, r1
_02068FCA:
	add r0, sp, #0x0
	add r1, r4, #0x0
	add r2, r3, #0x0
	bl ReadWholeNarcMemberByIdPair
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	pop {r3-r5, pc}
	nop
_02068FDC: .word 0x000001A5

	thumb_func_start FUN_02068FE0
FUN_02068FE0: ; 0x02068FE0
	push {r4, lr}
	add r4, r0, #0x0
	cmp r2, #0x2
	bne _02068FEE
	mov r0, #0x3c
	strh r0, [r4, #0x0]
	b _02068FFC
_02068FEE:
	mov r0, #0x6
	strh r0, [r4, #0x0]
	add r0, r1, #0x0
	bl FUN_0206AA30
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
_02068FFC:
	lsl r0, r1, #0x1
	strh r0, [r4, #0x2]
	add r0, r0, #0x1
	strh r0, [r4, #0x4]
	mov r0, #0x0
	strh r0, [r4, #0x6]
	strb r0, [r4, #0x8]
	str r0, [r4, #0xc]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02069010
FUN_02069010: ; 0x02069010
	push {r3-r5, lr}
	sub sp, #0x20
	add r5, r1, #0x0
	mov r3, #0x1c
	add r4, r0, #0x0
	str r3, [sp, #0x0]
	add r0, sp, #0x4
	mov r1, #0x72 ; NARC_POKETOOL_POKEANM_POKEANM
	mov r2, #0x0
	mul r3, r5
	bl ReadFromNarcMemberByIdPair
	add r0, sp, #0xc
	add r1, r4, #0x0
	mov r2, #0x14
	bl MI_CpuCopy8
	add sp, #0x20
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02069038
FUN_02069038: ; 0x02069038
	push {r3-r7, lr}
	sub sp, #0x28
	add r4, r0, #0x0
	add r6, r2, #0x0
	add r5, r3, #0x0
	mov r3, #0x1c
	add r0, sp, #0x8
	add r7, r1, #0x0
	str r3, [sp, #0x0]
	add r0, #0x2
	mov r1, #0x72 ; NARC_POKETOOL_POKEANM_POKEANM
	mov r2, #0x0
	mul r3, r6
	bl ReadFromNarcMemberByIdPair
	cmp r5, #0x2
	bne _0206906C
	add r1, sp, #0x4
	mov r0, #0x6
	ldrsb r0, [r1, r0]
	strh r0, [r1, #0x0]
	ldrb r0, [r1, #0x7]
	strh r0, [r1, #0x2]
	ldr r0, [sp, #0x44]
	strb r0, [r1, #0x4]
	b _02069096
_0206906C:
	ldr r0, [sp, #0x40]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02014C3C
	add r5, r0, #0x0
	cmp r5, #0x3
	blt _02069080
	bl ErrorHandling
_02069080:
	lsl r2, r5, #0x1
	add r0, sp, #0xc
	ldrsb r1, [r0, r2]
	add r0, sp, #0x4
	strh r1, [r0, #0x0]
	add r1, sp, #0xc
	add r1, #0x1
	ldrb r1, [r1, r2]
	strh r1, [r0, #0x2]
	ldr r1, [sp, #0x44]
	strb r1, [r0, #0x4]
_02069096:
	ldr r3, [sp, #0x48]
	add r0, r4, #0x0
	lsl r3, r3, #0x18
	add r1, r7, #0x0
	add r2, sp, #0x4
	lsr r3, r3, #0x18
	bl FUN_02014C54
	add sp, #0x28
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020690AC
FUN_020690AC: ; 0x020690AC
	mov r2, #0x3c
	strh r2, [r0, #0x0]
	lsl r1, r1, #0x1
	strh r1, [r0, #0x2]
	add r1, r1, #0x1
	strh r1, [r0, #0x4]
	mov r1, #0x0
	strh r1, [r0, #0x6]
	strb r1, [r0, #0x8]
	str r1, [r0, #0xc]
	bx lr
	.balign 4

	thumb_func_start FUN_020690C4
FUN_020690C4: ; 0x020690C4
	mov r0, #0xec
	bx lr

	thumb_func_start FUN_020690C8
FUN_020690C8: ; 0x020690C8
	mov r0, #0x88
	bx lr

	thumb_func_start FUN_020690CC
FUN_020690CC: ; 0x020690CC
	ldr r3, _020690D0 ; =FUN_020690D4
	bx r3
	.balign 4
_020690D0: .word FUN_020690D4

	thumb_func_start FUN_020690D4
FUN_020690D4: ; 0x020690D4
	push {r3, lr}
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020672BC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}

	thumb_func_start FUN_020690E4
FUN_020690E4: ; 0x020690E4
	bx lr
	.balign 4

	thumb_func_start FUN_020690E8
FUN_020690E8: ; 0x020690E8
	push {r3-r5, lr}
	sub sp, #0x8
	mov r1, #0x5
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r4, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r0, #0x1
	add r0, sp, #0x0
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x8
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r1, #0x15
	bl FUN_02068678
	mov r1, #0x64
	add r5, r0, #0x0
	bl GetExpByGrowthRateAndLevel
	ldr r1, [sp, #0x4]
	cmp r1, r0
	bls _02069138
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0x8
	add r2, sp, #0x4
	bl FUN_02067830
_02069138:
	add r0, sp, #0x0
	ldrb r1, [r0, #0x0]
	cmp r1, #0x64
	bls _02069146
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r5, pc}
_02069146:
	add r0, r5, #0x0
	bl GetExpByGrowthRateAndLevel
	ldr r1, [sp, #0x4]
	cmp r1, r0
	blo _02069162
	add r0, r4, #0x0
	mov r1, #0xa0
	add r2, sp, #0x0
	bl FUN_02067830
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r5, pc}
_02069162:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r5, pc}

	thumb_func_start FUN_02069168
FUN_02069168: ; 0x02069168
	push {r4-r7, lr}
	sub sp, #0x44
	add r7, r1, #0x0
	str r0, [sp, #0x0]
	mov r6, #0x0
	add r4, r2, #0x0
	add r0, r7, #0x0
	mov r1, #0x5
	add r2, r6, #0x0
	str r3, [sp, #0x4]
	ldr r5, [sp, #0x58]
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x2c]
	add r0, r7, #0x0
	mov r1, #0x6
	add r2, r6, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r1, r6, #0x0
	str r0, [sp, #0x28]
	add r0, r7, #0x0
	add r2, r1, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x30]
	add r0, r7, #0x0
	mov r1, #0x14
	add r2, r6, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x10]
	ldr r1, _020694A0 ; =0xFFFF0000
	ldr r0, [sp, #0x30]
	add r2, r6, #0x0
	and r0, r1
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x28]
	mov r1, #0x1
	bl FUN_0206E7B8
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldr r0, [sp, #0x2c]
	cmp r0, #0x40
	beq _020691E4
	cmp r1, #0x3f
	bne _020691E4
	cmp r4, #0x3
	beq _020691E4
	add sp, #0x44
	add r0, r6, #0x0
	pop {r4-r7, pc}
_020691E4:
	cmp r5, #0x0
	bne _020691EA
	add r5, sp, #0x40
_020691EA:
	mov r0, #0x0
	mov r1, #0x2a
	bl AllocFromHeap
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x2c]
	ldr r1, [sp, #0x18]
	bl FUN_0206A394
	cmp r4, #0x3
	bls _02069202
	b _0206954A
_02069202:
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0206920E: ; jump table (using 16-bit offset)
	.short _02069216 - _0206920E - 2; case 0
	.short _02069486 - _0206920E - 2; case 1
	.short _020694BE - _0206920E - 2; case 2
	.short _020694BE - _0206920E - 2; case 3
_02069216:
	add r0, r7, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x14]
	add r0, r7, #0x0
	mov r1, #0x9
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x20]
	mov r0, #0x0
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x1c]
	mov r1, #0xa
	ldr r4, [sp, #0x18]
	bl _s32_div_f
	str r1, [sp, #0x8]
_02069246:
	ldrh r0, [r4, #0x0]
	cmp r0, #0x1a
	bls _0206924E
	b _02069472
_0206924E:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0206925A: ; jump table (using 16-bit offset)
	.short _02069472 - _0206925A - 2; case 0
	.short _02069290 - _0206925A - 2; case 1
	.short _0206929E - _0206925A - 2; case 2
	.short _020692B4 - _0206925A - 2; case 3
	.short _020692CA - _0206925A - 2; case 4
	.short _02069472 - _0206925A - 2; case 5
	.short _02069472 - _0206925A - 2; case 6
	.short _02069472 - _0206925A - 2; case 7
	.short _020692DA - _0206925A - 2; case 8
	.short _02069306 - _0206925A - 2; case 9
	.short _02069332 - _0206925A - 2; case 10
	.short _0206935E - _0206925A - 2; case 11
	.short _02069376 - _0206925A - 2; case 12
	.short _0206938C - _0206925A - 2; case 13
	.short _0206939C - _0206925A - 2; case 14
	.short _020693A2 - _0206925A - 2; case 15
	.short _02069472 - _0206925A - 2; case 16
	.short _02069472 - _0206925A - 2; case 17
	.short _020693B2 - _0206925A - 2; case 18
	.short _020693CA - _0206925A - 2; case 19
	.short _020693E2 - _0206925A - 2; case 20
	.short _020693F6 - _0206925A - 2; case 21
	.short _0206940E - _0206925A - 2; case 22
	.short _0206942C - _0206925A - 2; case 23
	.short _0206944A - _0206925A - 2; case 24
	.short _02069458 - _0206925A - 2; case 25
	.short _02069466 - _0206925A - 2; case 26
_02069290:
	ldr r0, [sp, #0x20]
	cmp r0, #0xdc
	blo _0206936C
	ldrh r6, [r4, #0x4]
	mov r0, #0x1
	str r0, [r5, #0x0]
	b _02069472
_0206929E:
	bl FUN_0201277C
	cmp r0, #0x0
	bne _0206936C
	ldr r0, [sp, #0x20]
	cmp r0, #0xdc
	blo _0206936C
	ldrh r6, [r4, #0x4]
	mov r0, #0x2
	str r0, [r5, #0x0]
	b _02069472
_020692B4:
	bl FUN_0201277C
	cmp r0, #0x1
	bne _0206936C
	ldr r0, [sp, #0x20]
	cmp r0, #0xdc
	blo _0206936C
	ldrh r6, [r4, #0x4]
	mov r0, #0x3
	str r0, [r5, #0x0]
	b _02069472
_020692CA:
	ldrh r1, [r4, #0x2]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bgt _0206936C
	ldrh r6, [r4, #0x4]
	mov r0, #0x4
	str r0, [r5, #0x0]
	b _02069472
_020692DA:
	ldrh r1, [r4, #0x2]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bgt _0206936C
	add r0, r7, #0x0
	mov r1, #0xa4
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x34]
	add r0, r7, #0x0
	mov r1, #0xa5
	mov r2, #0x0
	bl FUN_020671BC
	ldr r1, [sp, #0x34]
	cmp r1, r0
	bls _0206936C
	ldrh r6, [r4, #0x4]
	mov r0, #0x8
	str r0, [r5, #0x0]
	b _02069472
_02069306:
	ldrh r1, [r4, #0x2]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bgt _0206936C
	add r0, r7, #0x0
	mov r1, #0xa4
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x38]
	add r0, r7, #0x0
	mov r1, #0xa5
	mov r2, #0x0
	bl FUN_020671BC
	ldr r1, [sp, #0x38]
	cmp r1, r0
	bne _0206936C
	ldrh r6, [r4, #0x4]
	mov r0, #0x9
	str r0, [r5, #0x0]
	b _02069472
_02069332:
	ldrh r1, [r4, #0x2]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bgt _0206936C
	add r0, r7, #0x0
	mov r1, #0xa4
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x3c]
	add r0, r7, #0x0
	mov r1, #0xa5
	mov r2, #0x0
	bl FUN_020671BC
	ldr r1, [sp, #0x3c]
	cmp r1, r0
	bhs _0206936C
	ldrh r6, [r4, #0x4]
	mov r0, #0xa
	str r0, [r5, #0x0]
	b _02069472
_0206935E:
	ldrh r1, [r4, #0x2]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bgt _0206936C
	ldr r0, [sp, #0x8]
	cmp r0, #0x5
	blt _0206936E
_0206936C:
	b _02069472
_0206936E:
	ldrh r6, [r4, #0x4]
	mov r0, #0xb
	str r0, [r5, #0x0]
	b _02069472
_02069376:
	ldrh r1, [r4, #0x2]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bgt _02069472
	ldr r0, [sp, #0x8]
	cmp r0, #0x5
	blt _02069472
	ldrh r6, [r4, #0x4]
	mov r0, #0xc
	str r0, [r5, #0x0]
	b _02069472
_0206938C:
	ldrh r1, [r4, #0x2]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bgt _02069472
	ldrh r6, [r4, #0x4]
	mov r0, #0xd
	str r0, [r5, #0x0]
	b _02069472
_0206939C:
	mov r0, #0xe
	str r0, [r5, #0x0]
	b _02069472
_020693A2:
	ldrh r1, [r4, #0x2]
	ldr r0, [sp, #0x10]
	cmp r1, r0
	bgt _02069472
	ldrh r6, [r4, #0x4]
	mov r0, #0xf
	str r0, [r5, #0x0]
	b _02069472
_020693B2:
	bl FUN_0201277C
	cmp r0, #0x0
	bne _02069472
	ldrh r1, [r4, #0x2]
	ldr r0, [sp, #0x28]
	cmp r0, r1
	bne _02069472
	ldrh r6, [r4, #0x4]
	mov r0, #0x12
	str r0, [r5, #0x0]
	b _02069472
_020693CA:
	bl FUN_0201277C
	cmp r0, #0x1
	bne _02069472
	ldrh r1, [r4, #0x2]
	ldr r0, [sp, #0x28]
	cmp r0, r1
	bne _02069472
	ldrh r6, [r4, #0x4]
	mov r0, #0x13
	str r0, [r5, #0x0]
	b _02069472
_020693E2:
	ldrh r1, [r4, #0x2]
	add r0, r7, #0x0
	bl FUN_02069A38
	cmp r0, #0x1
	bne _02069472
	ldrh r6, [r4, #0x4]
	mov r0, #0x14
	str r0, [r5, #0x0]
	b _02069472
_020693F6:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _02069472
	ldrh r1, [r4, #0x2]
	bl FUN_0206BAE4
	cmp r0, #0x1
	bne _02069472
	ldrh r6, [r4, #0x4]
	mov r0, #0x15
	str r0, [r5, #0x0]
	b _02069472
_0206940E:
	add r0, r7, #0x0
	mov r1, #0x6f
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _02069472
	ldrh r1, [r4, #0x2]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bgt _02069472
	ldrh r6, [r4, #0x4]
	mov r0, #0x16
	str r0, [r5, #0x0]
	b _02069472
_0206942C:
	add r0, r7, #0x0
	mov r1, #0x6f
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x1
	bne _02069472
	ldrh r1, [r4, #0x2]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bgt _02069472
	ldrh r6, [r4, #0x4]
	mov r0, #0x17
	str r0, [r5, #0x0]
	b _02069472
_0206944A:
	ldr r1, [sp, #0x4]
	cmp r1, r0
	bne _02069472
	ldrh r6, [r4, #0x4]
	mov r0, #0x18
	str r0, [r5, #0x0]
	b _02069472
_02069458:
	ldr r1, [sp, #0x4]
	cmp r1, r0
	bne _02069472
	ldrh r6, [r4, #0x4]
	mov r0, #0x19
	str r0, [r5, #0x0]
	b _02069472
_02069466:
	ldr r1, [sp, #0x4]
	cmp r1, r0
	bne _02069472
	ldrh r6, [r4, #0x4]
	mov r0, #0x1a
	str r0, [r5, #0x0]
_02069472:
	cmp r6, #0x0
	bne _0206954A
	ldr r0, [sp, #0x24]
	add r4, r4, #0x6
	add r0, r0, #0x1
	str r0, [sp, #0x24]
	cmp r0, #0x7
	bge _02069484
	b _02069246
_02069484:
	b _0206954A
_02069486:
	ldr r3, [sp, #0x18]
	mov r4, #0x0
	mov r7, #0x6
	mov r2, #0x5
_0206948E:
	ldrh r0, [r3, #0x0]
	cmp r0, #0x5
	beq _0206949A
	cmp r0, #0x6
	beq _020694A4
	b _020694B0
_0206949A:
	ldrh r6, [r3, #0x4]
	str r2, [r5, #0x0]
	b _020694B0
	.balign 4
_020694A0: .word 0xFFFF0000
_020694A4:
	ldrh r1, [r3, #0x2]
	ldr r0, [sp, #0x28]
	cmp r0, r1
	bne _020694B0
	ldrh r6, [r3, #0x4]
	str r7, [r5, #0x0]
_020694B0:
	cmp r6, #0x0
	bne _0206954A
	add r4, r4, #0x1
	add r3, r3, #0x6
	cmp r4, #0x7
	blt _0206948E
	b _0206954A
_020694BE:
	mov r0, #0x0
	ldr r4, [sp, #0x18]
	str r0, [sp, #0xc]
_020694C4:
	ldrh r2, [r4, #0x0]
	cmp r2, #0x7
	bne _020694E4
	ldrh r1, [r4, #0x2]
	ldr r0, [sp, #0x4]
	cmp r0, r1
	bne _020694E4
	ldr r0, [sp, #0xc]
	mov r1, #0x6
	mul r1, r0
	ldr r0, [sp, #0x18]
	add r0, r0, r1
	ldrh r6, [r0, #0x4]
	mov r0, #0x0
	str r0, [r5, #0x0]
	b _0206954A
_020694E4:
	cmp r2, #0x10
	bne _02069510
	add r0, r7, #0x0
	mov r1, #0x6f
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _02069510
	ldrh r1, [r4, #0x2]
	ldr r0, [sp, #0x4]
	cmp r0, r1
	bne _02069510
	ldr r0, [sp, #0xc]
	mov r1, #0x6
	mul r1, r0
	ldr r0, [sp, #0x18]
	add r0, r0, r1
	ldrh r6, [r0, #0x4]
	mov r0, #0x0
	str r0, [r5, #0x0]
	b _0206954A
_02069510:
	ldrh r0, [r4, #0x0]
	cmp r0, #0x11
	bne _0206953E
	add r0, r7, #0x0
	mov r1, #0x6f
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x1
	bne _0206953E
	ldrh r1, [r4, #0x2]
	ldr r0, [sp, #0x4]
	cmp r0, r1
	bne _0206953E
	ldr r0, [sp, #0xc]
	mov r1, #0x6
	mul r1, r0
	ldr r0, [sp, #0x18]
	add r0, r0, r1
	ldrh r6, [r0, #0x4]
	mov r0, #0x0
	str r0, [r5, #0x0]
	b _0206954A
_0206953E:
	ldr r0, [sp, #0xc]
	add r4, r4, #0x6
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	cmp r0, #0x7
	blt _020694C4
_0206954A:
	ldr r0, [sp, #0x18]
	bl FreeToHeap
	add r0, r6, #0x0
	add sp, #0x44
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02069558
FUN_02069558: ; 0x02069558
	push {r3-r4, lr}
	sub sp, #0x4c
	add r4, r0, #0x0
	mov r1, #0x0
	add r0, sp, #0x0
	strh r1, [r0, #0x0]
	ldr r0, _020695A0 ; =0x000001EE
	cmp r4, r0
	blo _0206956E
	bl ErrorHandling
_0206956E:
	add r0, sp, #0x4
	bl FS_InitFile
	ldr r1, _020695A4 ; =UNK_02105FC8
	add r0, sp, #0x4
	bl FS_OpenFile
	add r0, sp, #0x4
	lsl r1, r4, #0x1
	mov r2, #0x0
	bl FS_SeekFile
	add r0, sp, #0x4
	add r1, sp, #0x0
	mov r2, #0x2
	bl FS_ReadFile
	add r0, sp, #0x4
	bl FS_CloseFile
	add r0, sp, #0x0
	ldrh r0, [r0, #0x0]
	add sp, #0x4c
	pop {r3-r4, pc}
	nop
_020695A0: .word 0x000001EE
_020695A4: .word UNK_02105FC8

	thumb_func_start FUN_020695A8
FUN_020695A8: ; 0x020695A8
	push {r3, lr}
	cmp r0, #0xb9
	bgt _020695CC
	cmp r0, #0xb7
	blt _020695BA
	beq _020695EC
	cmp r0, #0xb9
	beq _020695EC
	b _020695E8
_020695BA:
	cmp r0, #0x7a
	bgt _020695C6
	bge _020695EC
	cmp r0, #0x71
	beq _020695EC
	b _020695E8
_020695C6:
	cmp r0, #0x8f
	beq _020695EC
	b _020695E8
_020695CC:
	cmp r0, #0xe2
	bgt _020695D8
	bge _020695EC
	cmp r0, #0xca
	beq _020695EC
	b _020695E8
_020695D8:
	ldr r1, _020695F0 ; =0x0000013B
	cmp r0, r1
	bgt _020695E2
	beq _020695EC
	b _020695E8
_020695E2:
	add r1, #0x2b
	cmp r0, r1
	beq _020695EC
_020695E8:
	bl FUN_02069558
_020695EC:
	pop {r3, pc}
	nop
_020695F0: .word 0x0000013B

	thumb_func_start FUN_020695F4
FUN_020695F4: ; 0x020695F4
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	mov r0, #0x0
	mov r1, #0x2c
	bl AllocFromHeap
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02066A6C
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020672BC
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r5, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020672BC
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020687C8
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldr r2, [sp, #0x0]
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_02069F9C
	ldr r0, [sp, #0x0]
	ldrh r1, [r0, #0x0]
	ldr r0, _02069690 ; =0x0000FFFF
	cmp r1, r0
	beq _0206967C
	ldr r4, [sp, #0x0]
	lsl r7, r6, #0x9
_02069648:
	ldrh r1, [r4, #0x0]
	mov r0, #0xfe
	lsl r0, r0, #0x8
	and r0, r1
	cmp r0, r7
	bgt _0206967C
	ldr r0, _02069694 ; =0x000001FF
	and r0, r1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020696A8
	ldr r1, _02069690 ; =0x0000FFFF
	cmp r0, r1
	bne _02069672
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02069718
_02069672:
	add r4, r4, #0x2
	ldrh r1, [r4, #0x0]
	ldr r0, _02069690 ; =0x0000FFFF
	cmp r1, r0
	bne _02069648
_0206967C:
	ldr r0, [sp, #0x0]
	bl FreeToHeap
	ldr r1, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02066A94
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02069690: .word 0x0000FFFF
_02069694: .word 0x000001FF

	thumb_func_start FUN_02069698
FUN_02069698: ; 0x02069698
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_020690E4
	add r1, r4, #0x0
	bl FUN_020696A8
	pop {r4, pc}

	thumb_func_start FUN_020696A8
FUN_020696A8: ; 0x020696A8
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r1, #0x0
	ldr r1, _02069700 ; =0x0000FFFF
	add r6, r0, #0x0
	str r1, [sp, #0x4]
	bl FUN_02066A6C
	mov r4, #0x0
	str r0, [sp, #0x0]
	add r7, r4, #0x0
_020696BE:
	add r1, r4, #0x0
	add r0, r6, #0x0
	add r1, #0x36
	add r2, r7, #0x0
	bl FUN_020672BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bne _020696E0
	lsl r2, r4, #0x18
	add r0, r6, #0x0
	add r1, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_020697D4
	str r5, [sp, #0x4]
	b _020696F0
_020696E0:
	cmp r0, r5
	bne _020696EA
	ldr r0, _02069704 ; =0x0000FFFE
	str r0, [sp, #0x4]
	b _020696F0
_020696EA:
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _020696BE
_020696F0:
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	bl FUN_02066A94
	ldr r0, [sp, #0x4]
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02069700: .word 0x0000FFFF
_02069704: .word 0x0000FFFE

	thumb_func_start FUN_02069708
FUN_02069708: ; 0x02069708
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_020690E4
	add r1, r4, #0x0
	bl FUN_02069718
	pop {r4, pc}

	thumb_func_start FUN_02069718
FUN_02069718: ; 0x02069718
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	bl FUN_02066A6C
	str r0, [sp, #0xc]
	add r0, sp, #0x18
	mov r4, #0x0
	str r0, [sp, #0x4]
	add r7, sp, #0x14
	add r6, sp, #0x10
_02069730:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x37
	mov r2, #0x0
	bl FUN_020672BC
	ldr r1, [sp, #0x4]
	mov r2, #0x0
	strh r0, [r1, #0x0]
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x3b
	bl FUN_020672BC
	add r1, r4, #0x0
	strb r0, [r7, #0x0]
	add r0, r5, #0x0
	add r1, #0x3f
	mov r2, #0x0
	bl FUN_020672BC
	strb r0, [r6, #0x0]
	ldr r0, [sp, #0x4]
	add r4, r4, #0x1
	add r0, r0, #0x2
	str r0, [sp, #0x4]
	add r7, r7, #0x1
	add r6, r6, #0x1
	cmp r4, #0x3
	blt _02069730
	ldr r0, [sp, #0x0]
	add r1, sp, #0x10
	strh r0, [r1, #0xe]
	ldr r0, [sp, #0x0]
	mov r1, #0x5
	bl FUN_0206AB18
	add r1, sp, #0x10
	strb r0, [r1, #0x7]
	mov r4, #0x0
	add r0, sp, #0x18
	strb r4, [r1, #0x3]
	str r0, [sp, #0x8]
	add r7, sp, #0x14
	add r6, sp, #0x10
_0206978A:
	add r1, r4, #0x0
	ldr r2, [sp, #0x8]
	add r0, r5, #0x0
	add r1, #0x36
	bl FUN_02067960
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x3a
	add r2, r7, #0x0
	bl FUN_02067960
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x3e
	add r2, r6, #0x0
	bl FUN_02067960
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	add r0, r0, #0x2
	str r0, [sp, #0x8]
	add r7, r7, #0x1
	add r6, r6, #0x1
	cmp r4, #0x4
	blt _0206978A
	ldr r1, [sp, #0xc]
	add r0, r5, #0x0
	bl FUN_02066A94
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020697CC
FUN_020697CC: ; 0x020697CC
	ldr r3, _020697D0 ; =FUN_020697D4
	bx r3
	.balign 4
_020697D0: .word FUN_020697D4

	thumb_func_start FUN_020697D4
FUN_020697D4: ; 0x020697D4
	push {r0-r3}
	push {r3-r5, lr}
	add r4, r2, #0x0
	add r1, r4, #0x0
	add r1, #0x36
	add r2, sp, #0x14
	add r5, r0, #0x0
	bl FUN_02067960
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x3e
	mov r2, #0x0
	bl FUN_020672BC
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	add r0, sp, #0x10
	ldrh r0, [r0, #0x4]
	bl FUN_0206AB30
	add r1, sp, #0x0
	strb r0, [r1, #0x0]
	add r4, #0x3a
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, sp, #0x0
	bl FUN_02067960
	pop {r3-r5}
	pop {r3}
	add sp, #0x10
	bx r3
	.balign 4

	thumb_func_start FUN_02069818
FUN_02069818: ; 0x02069818
	push {r3-r7, lr}
	sub sp, #0x10
	add r7, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0x0
	mov r1, #0x2c
	str r2, [sp, #0x0]
	str r0, [sp, #0x8]
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r7, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	add r0, r7, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0xc]
	add r0, r7, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0xc]
	add r2, r4, #0x0
	bl FUN_02069F9C
	ldr r0, [r5, #0x0]
	lsl r0, r0, #0x1
	ldrh r2, [r4, r0]
	ldr r0, _020698D8 ; =0x0000FFFF
	cmp r2, r0
	bne _0206987A
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0206987A:
	mov r0, #0xfe
	lsl r0, r0, #0x8
	add r3, r2, #0x0
	and r3, r0
	lsl r6, r6, #0x9
	cmp r6, r3
	beq _020698AC
	ldr r1, _020698D8 ; =0x0000FFFF
_0206988A:
	ldr r2, [r5, #0x0]
	add r2, r2, #0x1
	str r2, [r5, #0x0]
	lsl r2, r2, #0x1
	ldrh r2, [r4, r2]
	cmp r2, r1
	bne _020698A4
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_020698A4:
	add r3, r2, #0x0
	and r3, r0
	cmp r6, r3
	bne _0206988A
_020698AC:
	cmp r6, r3
	bne _020698CC
	ldr r0, _020698DC ; =0x000001FF
	add r1, r2, #0x0
	and r1, r0
	ldr r0, [sp, #0x0]
	strh r1, [r0, #0x0]
	ldr r0, [r5, #0x0]
	ldr r1, [sp, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	ldrh r1, [r1, #0x0]
	add r0, r7, #0x0
	bl FUN_02069698
	str r0, [sp, #0x8]
_020698CC:
	add r0, r4, #0x0
	bl FreeToHeap
	ldr r0, [sp, #0x8]
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_020698D8: .word 0x0000FFFF
_020698DC: .word 0x000001FF

	thumb_func_start FUN_020698E0
FUN_020698E0: ; 0x020698E0
	ldr r3, _020698E4 ; =FUN_020698E8
	bx r3
	.balign 4
_020698E4: .word FUN_020698E8

	thumb_func_start FUN_020698E8
FUN_020698E8: ; 0x020698E8
	push {r4-r6, lr}
	sub sp, #0x8
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r1, #0x36
	mov r2, #0x0
	add r5, r0, #0x0
	bl FUN_020672BC
	add r1, sp, #0x0
	strh r0, [r1, #0x4]
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x3a
	mov r2, #0x0
	bl FUN_020672BC
	add r1, sp, #0x0
	strb r0, [r1, #0x2]
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x3e
	mov r2, #0x0
	bl FUN_020672BC
	add r1, sp, #0x0
	strb r0, [r1, #0x0]
	add r1, r6, #0x0
	add r0, r5, #0x0
	add r1, #0x36
	mov r2, #0x0
	bl FUN_020672BC
	add r1, sp, #0x0
	strh r0, [r1, #0x6]
	add r1, r6, #0x0
	add r0, r5, #0x0
	add r1, #0x3a
	mov r2, #0x0
	bl FUN_020672BC
	add r1, sp, #0x0
	strb r0, [r1, #0x3]
	add r1, r6, #0x0
	add r0, r5, #0x0
	add r1, #0x3e
	mov r2, #0x0
	bl FUN_020672BC
	add r1, sp, #0x0
	strb r0, [r1, #0x1]
	add r1, r4, #0x0
	add r2, sp, #0x4
	add r0, r5, #0x0
	add r1, #0x36
	add r2, #0x2
	bl FUN_02067960
	add r1, r4, #0x0
	add r2, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x3a
	add r2, #0x3
	bl FUN_02067960
	add r4, #0x3e
	add r2, sp, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, #0x1
	bl FUN_02067960
	add r1, r6, #0x0
	add r0, r5, #0x0
	add r1, #0x36
	add r2, sp, #0x4
	bl FUN_02067960
	add r1, r6, #0x0
	add r2, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x3a
	add r2, #0x2
	bl FUN_02067960
	add r6, #0x3e
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, sp, #0x0
	bl FUN_02067960
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020699A4
FUN_020699A4: ; 0x020699A4
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x3
	bhs _02069A0A
	mov r7, #0x0
	add r6, sp, #0x0
_020699B2:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x37
	add r2, r7, #0x0
	bl FUN_020671BC
	add r1, r4, #0x0
	strh r0, [r6, #0x2]
	add r0, r5, #0x0
	add r1, #0x3b
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r4, #0x0
	strb r0, [r6, #0x1]
	add r0, r5, #0x0
	add r1, #0x3f
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r4, #0x0
	add r2, sp, #0x0
	strb r0, [r6, #0x0]
	add r0, r5, #0x0
	add r1, #0x36
	add r2, #0x2
	bl FUN_02067830
	add r1, r4, #0x0
	add r2, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x3a
	add r2, #0x1
	bl FUN_02067830
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x3e
	add r2, sp, #0x0
	bl FUN_02067830
	add r4, r4, #0x1
	cmp r4, #0x3
	blo _020699B2
_02069A0A:
	mov r1, #0x0
	add r0, sp, #0x0
	strh r1, [r0, #0x2]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x0]
	add r2, sp, #0x0
	add r0, r5, #0x0
	mov r1, #0x39
	add r2, #0x2
	bl FUN_02067830
	add r2, sp, #0x0
	add r0, r5, #0x0
	mov r1, #0x3d
	add r2, #0x1
	bl FUN_02067830
	add r0, r5, #0x0
	mov r1, #0x41
	add r2, sp, #0x0
	bl FUN_02067830
	pop {r3-r7, pc}

	thumb_func_start FUN_02069A38
FUN_02069A38: ; 0x02069A38
	push {r3-r7, lr}
	mov r4, #0x0
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r7, r4, #0x0
_02069A42:
	add r1, r4, #0x0
	add r0, r6, #0x0
	add r1, #0x36
	add r2, r7, #0x0
	bl FUN_020671BC
	cmp r5, r0
	beq _02069A58
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _02069A42
_02069A58:
	cmp r4, #0x4
	beq _02069A60
	mov r0, #0x1
	pop {r3-r7, pc}
_02069A60:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02069A64
FUN_02069A64: ; 0x02069A64
	push {r4-r5, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r3, r4, #0x0
	mov r2, #0x11
_02069A74:
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02069A74
	ldrh r1, [r4, #0x4]
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1f
	beq _02069A8E
	mov r0, #0x1
	bic r1, r0
	mov r0, #0x1
	orr r0, r1
	strh r0, [r4, #0x4]
_02069A8E:
	add r0, r4, #0x0
	mov r1, #0x9f
	add r2, sp, #0x0
	bl FUN_02067830
	add r0, r4, #0x0
	mov r1, #0xa2
	add r2, sp, #0x0
	bl FUN_02067830
	add r0, r4, #0x0
	mov r1, #0xa3
	add r2, sp, #0x0
	bl FUN_02067830
	mov r0, #0x0
	bl FUN_020256BC
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0xa9
	add r2, r5, #0x0
	bl FUN_02067830
	add r0, r5, #0x0
	bl FreeToHeap
	add r0, r4, #0x0
	mov r1, #0xa1
	add r2, sp, #0x0
	bl FUN_02067830
	mov r0, #0x0
	add r1, sp, #0x4
	mov r2, #0x18
	bl MIi_CpuClearFast
	add r0, r4, #0x0
	mov r1, #0xaa
	add r2, sp, #0x4
	bl FUN_02067830
	add r0, r4, #0x0
	bl FUN_02066ED8
	add sp, #0x1c
	pop {r4-r5, pc}

	thumb_func_start FUN_02069AEC
FUN_02069AEC: ; 0x02069AEC
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	bl FUN_0206B9AC
	add r7, r0, #0x0
	mov r6, #0x1
	mov r5, #0x0
	cmp r7, #0x0
	ble _02069B3C
_02069AFE:
	ldr r0, [sp, #0x0]
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02069B36
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _02069B36
	add r0, r4, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, r6
	bls _02069B36
	add r6, r0, #0x0
_02069B36:
	add r5, r5, #0x1
	cmp r5, r7
	blt _02069AFE
_02069B3C:
	add r0, r6, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02069B40
FUN_02069B40: ; 0x02069B40
	push {r3, lr}
	sub sp, #0x8
	add r3, r0, #0x0
	mov r0, #0x2
	str r0, [sp, #0x0]
	add r0, sp, #0x4
	mov r1, #0x6d ; NARC_POKETOOL_POKEZUKAN
	mov r2, #0x0
	lsl r3, r3, #0x1
	bl ReadFromNarcMemberByIdPair
	add r0, sp, #0x4
	ldrh r0, [r0, #0x0]
	add sp, #0x8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02069B60
FUN_02069B60: ; 0x02069B60
	push {r3, lr}
	sub sp, #0x8
	add r3, r0, #0x0
	mov r2, #0x0
	add r0, sp, #0x4
	strh r2, [r0, #0x0]
	cmp r3, #0x97
	bhi _02069B7E
	mov r0, #0x2
	str r0, [sp, #0x0]
	add r0, sp, #0x4
	mov r1, #0x91 ; NARC_POKETOOL_SHINZUKAN
	lsl r3, r3, #0x1
	bl ReadFromNarcMemberByIdPair
_02069B7E:
	add r0, sp, #0x4
	ldrh r0, [r0, #0x0]
	add sp, #0x8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02069B88
FUN_02069B88: ; 0x02069B88
	push {r3-r4}
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r2, #0x1d
_02069B90:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02069B90
	ldr r0, [r4, #0x0]
	str r0, [r3, #0x0]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02069BA0
FUN_02069BA0: ; 0x02069BA0
	push {r3-r4}
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r2, #0x11
_02069BA8:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02069BA8
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02069BB4
FUN_02069BB4: ; 0x02069BB4
	push {r3-r4}
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r2, #0x11
_02069BBC:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02069BBC
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02069BC8
FUN_02069BC8: ; 0x02069BC8
	ldr r3, _02069BCC ; =FUN_02069BD0
	bx r3
	.balign 4
_02069BCC: .word FUN_02069BD0

	thumb_func_start FUN_02069BD0
FUN_02069BD0: ; 0x02069BD0
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x0
	add r2, r1, #0x0
	bl FUN_020672BC
	add r1, r4, #0x0
	bl FUN_02069BE4
	pop {r4, pc}

	thumb_func_start FUN_02069BE4
FUN_02069BE4: ; 0x02069BE4
	push {r4, lr}
	add r4, r1, #0x0
	bl GetNatureFromPersonality
	lsl r1, r0, #0x2
	add r1, r0, r1
	ldr r0, _02069BF8 ; =UNK_020F7F16
	add r0, r0, r1
	ldrsb r0, [r4, r0]
	pop {r4, pc}
	.balign 4
_02069BF8: .word UNK_020F7F16

	thumb_func_start FUN_02069BFC
FUN_02069BFC: ; 0x02069BFC
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r7, r1, #0x0
	mov r0, #0x0
	mov r1, #0x2c
	add r5, r2, #0x0
	bl AllocFromHeap
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_02069F9C
	ldrh r1, [r6, #0x0]
	ldr r0, _02069C44 ; =0x0000FFFF
	mov r4, #0x0
	cmp r1, r0
	beq _02069C3A
	ldr r1, _02069C48 ; =0x000001FF
	ldr r2, _02069C44 ; =0x0000FFFF
	add r0, r6, #0x0
_02069C28:
	ldrh r3, [r0, #0x0]
	add r0, r0, #0x2
	add r4, r4, #0x1
	and r3, r1
	strh r3, [r5, #0x0]
	ldrh r3, [r0, #0x0]
	add r5, r5, #0x2
	cmp r3, r2
	bne _02069C28
_02069C3A:
	add r0, r6, #0x0
	bl FreeToHeap
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4
_02069C44: .word 0x0000FFFF
_02069C48: .word 0x000001FF

	thumb_func_start FUN_02069C4C
FUN_02069C4C: ; 0x02069C4C
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_0206B9AC
	add r6, r0, #0x0
	bl rand_LC
	mov r1, #0x1
	lsl r1, r1, #0xe
	cmp r0, r1
	beq _02069C70
	lsl r1, r1, #0x1
	cmp r0, r1
	beq _02069C70
	mov r1, #0x3
	lsl r1, r1, #0xe
	cmp r0, r1
	bne _02069CF2
_02069C70:
	bl rand_LC
	add r1, r6, #0x0
	bl _s32_div_f
	add r0, r5, #0x0
	add r7, r1, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02069C70
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _02069C70
	add r0, r7, #0x0
	bl MaskOfFlagNo
	add r1, r0, #0x0
	lsl r1, r1, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_02069CF4
	cmp r0, #0x0
	bne _02069CF2
	add r5, sp, #0x0
	mov r6, #0x7
_02069CB8:
	bl rand_LC
	strb r0, [r5, #0x0]
	ldrb r2, [r5, #0x0]
	add r1, r2, #0x0
	and r1, r6
	beq _02069CB8
	mov r0, #0xf0
	tst r0, r2
	beq _02069CD0
	add r0, sp, #0x0
	strb r1, [r0, #0x0]
_02069CD0:
	add r1, sp, #0x0
	ldrb r2, [r1, #0x0]
	lsl r0, r2, #0x4
	orr r0, r2
	strb r0, [r1, #0x0]
	ldrb r2, [r1, #0x0]
	mov r0, #0xf3
	and r0, r2
	strb r0, [r1, #0x0]
	ldrb r0, [r1, #0x0]
	add r2, sp, #0x0
	add r0, r0, #0x1
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	mov r1, #0x99
	bl FUN_02067830
_02069CF2:
	pop {r3-r7, pc}

	thumb_func_start FUN_02069CF4
FUN_02069CF4: ; 0x02069CF4
	push {r3-r7, lr}
	mov r6, #0x0
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	mov r4, #0x1
	add r7, r6, #0x0
	cmp r5, #0x0
	beq _02069D32
_02069D04:
	mov r0, #0x1
	tst r0, r5
	beq _02069D26
	ldr r0, [sp, #0x0]
	add r1, r6, #0x0
	bl FUN_0206B9B0
	mov r1, #0x99
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02069D26
	add r0, r7, #0x0
	orr r0, r4
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
_02069D26:
	lsl r0, r5, #0x17
	add r6, r6, #0x1
	lsl r4, r4, #0x1
	lsr r5, r0, #0x18
	bne _02069D04
	b _02069D4A
_02069D32:
	add r1, r6, #0x0
	bl FUN_0206B9B0
	mov r1, #0x99
	add r2, r6, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02069D4A
	add r0, r7, #0x1
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
_02069D4A:
	add r0, r7, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02069D50
FUN_02069D50: ; 0x02069D50
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	add r5, r1, #0x0
	bl FUN_0206B9AC
	mov r6, #0x0
	str r0, [sp, #0x4]
	cmp r0, #0x0
	ble _02069DC2
	add r4, sp, #0x8
_02069D66:
	ldr r0, [sp, #0x0]
	add r1, r6, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	add r7, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02069DBA
	add r0, r7, #0x0
	mov r1, #0x99
	mov r2, #0x0
	bl FUN_020671BC
	strb r0, [r4, #0x0]
	ldrb r1, [r4, #0x0]
	mov r0, #0xf
	and r0, r1
	beq _02069DBA
	cmp r0, r5
	blt _02069D98
	cmp r5, #0x4
	ble _02069DA2
_02069D98:
	ldrb r1, [r4, #0x0]
	mov r0, #0xf0
	and r0, r1
	strb r0, [r4, #0x0]
	b _02069DA6
_02069DA2:
	sub r0, r1, r5
	strb r0, [r4, #0x0]
_02069DA6:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02069DB0
	mov r0, #0x10
	strb r0, [r4, #0x0]
_02069DB0:
	add r0, r7, #0x0
	mov r1, #0x99
	add r2, sp, #0x8
	bl FUN_02067830
_02069DBA:
	ldr r0, [sp, #0x4]
	add r6, r6, #0x1
	cmp r6, r0
	blt _02069D66
_02069DC2:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02069DC8
FUN_02069DC8: ; 0x02069DC8
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl FUN_0206B9AC
	add r7, r0, #0x0
	bl rand_LC
	mov r1, #0x3
	bl _s32_div_f
	cmp r1, #0x0
	bne _02069E70
	mov r4, #0x0
	cmp r7, #0x0
	ble _02069E70
	sub r0, r7, #0x1
	str r0, [sp, #0x0]
_02069DEC:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	add r6, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02069E6A
	add r0, r6, #0x0
	mov r1, #0x99
	mov r2, #0x0
	bl FUN_020671BC
	add r1, sp, #0x4
	strb r0, [r1, #0x0]
	add r0, r1, #0x0
	ldrb r1, [r0, #0x0]
	mov r0, #0xf
	tst r0, r1
	beq _02069E6A
	cmp r4, #0x0
	beq _02069E40
	add r0, r5, #0x0
	sub r1, r4, #0x1
	bl FUN_0206B9B0
	mov r1, #0x99
	mov r2, #0x0
	add r6, r0, #0x0
	bl FUN_020671BC
	mov r1, #0xf0
	tst r0, r1
	bne _02069E40
	add r0, r6, #0x0
	mov r1, #0x99
	add r2, sp, #0x4
	bl FUN_02067830
_02069E40:
	ldr r0, [sp, #0x0]
	cmp r4, r0
	bge _02069E6A
	add r0, r5, #0x0
	add r1, r4, #0x1
	bl FUN_0206B9B0
	mov r1, #0x99
	mov r2, #0x0
	add r6, r0, #0x0
	bl FUN_020671BC
	mov r1, #0xf0
	tst r0, r1
	bne _02069E6A
	add r0, r6, #0x0
	mov r1, #0x99
	add r2, sp, #0x4
	bl FUN_02067830
	add r4, r4, #0x1
_02069E6A:
	add r4, r4, #0x1
	cmp r4, r7
	blt _02069DEC
_02069E70:
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02069E74
FUN_02069E74: ; 0x02069E74
	ldr r3, _02069E78 ; =FUN_02069E7C
	bx r3
	.balign 4
_02069E78: .word FUN_02069E7C

	thumb_func_start FUN_02069E7C
FUN_02069E7C: ; 0x02069E7C
	push {r3, lr}
	mov r1, #0x99
	mov r2, #0x0
	bl FUN_020672BC
	mov r1, #0xf
	tst r0, r1
	beq _02069E90
	mov r0, #0x1
	pop {r3, pc}
_02069E90:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02069E94
FUN_02069E94: ; 0x02069E94
	ldr r3, _02069E98 ; =FUN_02069E9C
	bx r3
	.balign 4
_02069E98: .word FUN_02069E9C

	thumb_func_start FUN_02069E9C
FUN_02069E9C: ; 0x02069E9C
	push {r3, lr}
	mov r1, #0x99
	mov r2, #0x0
	bl FUN_020672BC
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r0, #0xf
	tst r0, r1
	beq _02069EB4
	mov r0, #0x0
	pop {r3, pc}
_02069EB4:
	mov r0, #0xf0
	tst r0, r1
	beq _02069EBE
	mov r0, #0x1
	pop {r3, pc}
_02069EBE:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02069EC4
FUN_02069EC4: ; 0x02069EC4
	ldr r3, _02069EC8 ; =FUN_02069ECC
	bx r3
	.balign 4
_02069EC8: .word FUN_02069ECC

	thumb_func_start FUN_02069ECC
FUN_02069ECC: ; 0x02069ECC
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020672BC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xa
	mov r2, #0x0
	bl FUN_020672BC
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x6
	mov r2, #0x0
	bl FUN_020672BC
	ldr r1, _02069F20 ; =0x000001ED
	cmp r4, r1
	bne _02069F1C
	cmp r6, #0x79
	bne _02069F1C
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_0206E7B8
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl GetArceusTypeByPlate
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r1, #0x70
	add r2, sp, #0x0
	bl FUN_02067960
_02069F1C:
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_02069F20: .word 0x000001ED

	thumb_func_start GetArceusTypeByPlate
GetArceusTypeByPlate: ; 0x02069F24
	sub r0, #0x7d
	cmp r0, #0xf
	bhi _02069F96
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02069F36: ; jump table (using 16-bit offset)
	.short _02069F56 - _02069F36 - 2; case 0
	.short _02069F5A - _02069F36 - 2; case 1
	.short _02069F5E - _02069F36 - 2; case 2
	.short _02069F62 - _02069F36 - 2; case 3
	.short _02069F66 - _02069F36 - 2; case 4
	.short _02069F6A - _02069F36 - 2; case 5
	.short _02069F6E - _02069F36 - 2; case 6
	.short _02069F72 - _02069F36 - 2; case 7
	.short _02069F76 - _02069F36 - 2; case 8
	.short _02069F7A - _02069F36 - 2; case 9
	.short _02069F7E - _02069F36 - 2; case 10
	.short _02069F82 - _02069F36 - 2; case 11
	.short _02069F86 - _02069F36 - 2; case 12
	.short _02069F8A - _02069F36 - 2; case 13
	.short _02069F8E - _02069F36 - 2; case 14
	.short _02069F92 - _02069F36 - 2; case 15
_02069F56:
	mov r0, #0xa
	bx lr
_02069F5A:
	mov r0, #0xb
	bx lr
_02069F5E:
	mov r0, #0xd
	bx lr
_02069F62:
	mov r0, #0xc
	bx lr
_02069F66:
	mov r0, #0xf
	bx lr
_02069F6A:
	mov r0, #0x1
	bx lr
_02069F6E:
	mov r0, #0x3
	bx lr
_02069F72:
	mov r0, #0x4
	bx lr
_02069F76:
	mov r0, #0x2
	bx lr
_02069F7A:
	mov r0, #0xe
	bx lr
_02069F7E:
	mov r0, #0x6
	bx lr
_02069F82:
	mov r0, #0x5
	bx lr
_02069F86:
	mov r0, #0x7
	bx lr
_02069F8A:
	mov r0, #0x10
	bx lr
_02069F8E:
	mov r0, #0x11
	bx lr
_02069F92:
	mov r0, #0x8
	bx lr
_02069F96:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02069F9C
FUN_02069F9C: ; 0x02069F9C
	push {r4, lr}
	add r4, r2, #0x0
	bl ConvertUnownOrArceusSpecies
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x21 ; NARC_POKETOOL_PERSONAL_WOTBL
	bl ReadWholeNarcMemberByIdPair
	pop {r4, pc}

	thumb_func_start FUN_02069FB0
FUN_02069FB0: ; 0x02069FB0
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, _0206A010 ; =0x000001B9
	add r4, r2, #0x0
	add r5, r1, #0x0
	add r6, r3, #0x0
	cmp r4, r0
	bne _02069FFC
	add r0, r5, #0x0
	bl FUN_02005F14
	cmp r0, #0x0
	bne _02069FE2
	mov r0, #0x1
	bl FUN_02005E80
	ldr r0, [sp, #0x20]
	ldr r3, [sp, #0x18]
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020056AC
	pop {r3-r7, pc}
_02069FE2:
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	beq _02069FEE
	mov r0, #0x1
	bl FUN_02005E80
_02069FEE:
	ldr r2, [sp, #0x18]
	add r0, r7, #0x0
	mov r1, #0x0
	add r3, r6, #0x0
	bl FUN_02005E90
	pop {r3-r7, pc}
_02069FFC:
	ldr r0, [sp, #0x20]
	ldr r3, [sp, #0x18]
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020056AC
	pop {r3-r7, pc}
	nop
_0206A010: .word 0x000001B9

	thumb_func_start FUN_0206A014
FUN_0206A014: ; 0x0206A014
	push {r3-r6, lr}
	sub sp, #0xc
	ldr r6, [sp, #0x20]
	add r5, r0, #0x0
	str r6, [sp, #0x0]
	ldr r6, [sp, #0x24]
	add r4, r2, #0x0
	str r6, [sp, #0x4]
	bl FUN_0206A054
	cmp r4, #0xe
	bne _0206A050
	add r0, r5, #0x0
	mov r1, #0xa3
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0xa2
	add r2, sp, #0x8
	bl FUN_02067830
	mov r0, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x9f
	add r2, sp, #0x8
	bl FUN_02067830
_0206A050:
	add sp, #0xc
	pop {r3-r6, pc}

	thumb_func_start FUN_0206A054
FUN_0206A054: ; 0x0206A054
	push {r0-r3}
	push {r3-r4, lr}
	sub sp, #0x4
	ldr r2, [sp, #0x24]
	add r4, r0, #0x0
	str r2, [sp, #0x0]
	mov r2, #0x0
	bl FUN_020808AC
	ldr r2, _0206A090 ; =gGameVersion
	add r0, r4, #0x0
	mov r1, #0x79
	bl FUN_02067960
	add r0, r4, #0x0
	mov r1, #0x9a
	add r2, sp, #0x18
	bl FUN_02067960
	add r0, r4, #0x0
	mov r1, #0x9d
	add r2, sp, #0x20
	bl FUN_02067960
	add sp, #0x4
	pop {r3-r4}
	pop {r3}
	add sp, #0x10
	bx r3
	nop
_0206A090: .word gGameVersion

	thumb_func_start FUN_0206A094
FUN_0206A094: ; 0x0206A094
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	mov r0, #0x81
	add r7, r2, #0x0
	tst r0, r1
	bne _0206A12E
	bl rand_LC
	mov r1, #0x64
	bl _s32_div_f
	add r4, r1, #0x0
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r0, r5, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	mov r2, #0x10
	bl FUN_02068654
	add r1, sp, #0x4
	strh r0, [r1, #0x2]
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	mov r2, #0x11
	bl FUN_02068654
	add r1, sp, #0x4
	strh r0, [r1, #0x0]
	ldrh r2, [r1, #0x2]
	ldrh r0, [r1, #0x0]
	cmp r2, r0
	bne _0206A104
	cmp r2, #0x0
	beq _0206A104
	add r2, sp, #0x4
	add r0, r5, #0x0
	mov r1, #0x6
	add r2, #0x2
	bl FUN_02067830
	add sp, #0x8
	pop {r3-r7, pc}
_0206A104:
	ldr r0, _0206A134 ; =UNK_020F7ECC
	lsl r1, r7, #0x2
	ldrh r0, [r0, r1]
	cmp r4, r0
	blo _0206A12E
	ldr r0, _0206A138 ; =UNK_020F7ECC + 2
	ldrh r0, [r0, r1]
	cmp r4, r0
	add r2, sp, #0x4
	bhs _0206A126
	add r0, r5, #0x0
	mov r1, #0x6
	add r2, #0x2
	bl FUN_02067830
	add sp, #0x8
	pop {r3-r7, pc}
_0206A126:
	add r0, r5, #0x0
	mov r1, #0x6
	bl FUN_02067830
_0206A12E:
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0206A134: .word UNK_020F7ECC
_0206A138: .word UNK_020F7ECC + 2

	thumb_func_start FUN_0206A13C
FUN_0206A13C: ; 0x0206A13C
	ldr r3, _0206A140 ; =FUN_0206A144
	bx r3
	.balign 4
_0206A140: .word FUN_0206A144

	thumb_func_start FUN_0206A144
FUN_0206A144: ; 0x0206A144
	push {r4-r6, lr}
	add r6, r1, #0x0
	mov r1, #0xad
	mov r2, #0x0
	add r5, r0, #0x0
	bl FUN_020672BC
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r5, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020672BC
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0206A16C
	pop {r4-r6, pc}

	thumb_func_start FUN_0206A16C
FUN_0206A16C: ; 0x0206A16C
	push {r4, lr}
	ldr r3, _0206A1C0 ; =0x000001EE
	cmp r0, r3
	bne _0206A178
	mov r0, #0x0
	pop {r4, pc}
_0206A178:
	cmp r2, #0x20
	bhs _0206A186
	mov r3, #0x1
	add r4, r3, #0x0
	lsl r4, r2
	mov r2, #0x1d
	b _0206A1B0
_0206A186:
	cmp r2, #0x40
	bhs _0206A196
	mov r3, #0x1
	sub r2, #0x20
	add r4, r3, #0x0
	lsl r4, r2
	mov r2, #0x1e
	b _0206A1B0
_0206A196:
	cmp r2, #0x60
	bhs _0206A1A6
	mov r3, #0x1
	sub r2, #0x40
	add r4, r3, #0x0
	lsl r4, r2
	mov r2, #0x1f
	b _0206A1B0
_0206A1A6:
	mov r3, #0x1
	sub r2, #0x60
	add r4, r3, #0x0
	lsl r4, r2
	mov r2, #0x20
_0206A1B0:
	bl FUN_02068654
	tst r0, r4
	beq _0206A1BC
	mov r0, #0x1
	pop {r4, pc}
_0206A1BC:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_0206A1C0: .word 0x000001EE

	thumb_func_start FUN_0206A1C4
FUN_0206A1C4: ; 0x0206A1C4
	ldr r3, _0206A1C8 ; =FUN_0206A1CC
	bx r3
	.balign 4
_0206A1C8: .word FUN_0206A1CC

	thumb_func_start FUN_0206A1CC
FUN_0206A1CC: ; 0x0206A1CC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl FUN_02066A6C
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020672BC
	mov r1, #0x0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_020672BC
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x18
	bl FUN_02068678
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0x19
	bl FUN_02068678
	str r0, [sp, #0x0]
	cmp r0, #0x0
	beq _0206A226
	mov r0, #0x1
	tst r0, r6
	beq _0206A21A
	add r0, r5, #0x0
	mov r1, #0xa
	add r2, sp, #0x0
	bl FUN_02067960
	b _0206A230
_0206A21A:
	add r0, r5, #0x0
	mov r1, #0xa
	add r2, sp, #0x4
	bl FUN_02067960
	b _0206A230
_0206A226:
	add r0, r5, #0x0
	mov r1, #0xa
	add r2, sp, #0x4
	bl FUN_02067960
_0206A230:
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02066A94
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_0206A23C
FUN_0206A23C: ; 0x0206A23C
	push {r4-r7, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	mov r0, #0x0
	str r1, [sp, #0x0]
	bl FUN_020669C0
	str r0, [sp, #0x4]
	ldr r1, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02069B88
	ldr r0, [sp, #0x4]
	ldr r1, [r5, #0x0]
	mov r2, #0x0
	bl GetSubstruct
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	ldr r1, [r5, #0x0]
	mov r2, #0x1
	bl GetSubstruct
	add r6, r0, #0x0
	ldr r0, [sp, #0x4]
	ldr r1, [r5, #0x0]
	mov r2, #0x2
	bl GetSubstruct
	add r7, r0, #0x0
	ldr r0, [sp, #0x4]
	ldr r1, [r5, #0x0]
	mov r2, #0x3
	bl GetSubstruct
	str r0, [sp, #0x8]
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	mov r2, #0x0
	bl GetSubstruct
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	mov r2, #0x1
	bl GetSubstruct
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	mov r2, #0x2
	bl GetSubstruct
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	mov r2, #0x3
	bl GetSubstruct
	ldr r2, [sp, #0x4]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x4]
	ldrh r2, [r2, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3D0
	add r0, r5, #0x0
	ldr r2, [r5, #0x0]
	add r0, #0x88
	mov r1, #0x64
	bl FUN_0206A3D0
	add r0, r5, #0x0
	ldrh r2, [r5, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3D0
	ldr r0, [sp, #0x0]
	str r0, [r5, #0x0]
	ldr r2, [sp, #0xc]
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0xc]
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0xc]
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0xc]
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0xc]
	ldr r2, [sp, #0x10]
	ldmia r6!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0x10]
	ldmia r6!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0x10]
	ldmia r6!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0x10]
	ldmia r6!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0x10]
	ldr r2, [sp, #0x14]
	ldmia r7!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0x14]
	ldmia r7!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0x14]
	ldmia r7!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0x14]
	ldmia r7!, {r0-r1}
	stmia r2!, {r0-r1}
	str r2, [sp, #0x14]
	mov r0, #0x10
_0206A32E:
	ldr r1, [sp, #0x8]
	ldrh r2, [r1, #0x0]
	add r1, r1, #0x2
	str r1, [sp, #0x8]
	ldr r1, [sp, #0x18]
	strh r2, [r1, #0x0]
	add r1, r1, #0x2
	str r1, [sp, #0x18]
	sub r0, r0, #0x1
	bne _0206A32E
	add r0, r5, #0x0
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3F8
	strh r0, [r5, #0x6]
	add r0, r5, #0x0
	ldrh r2, [r5, #0x6]
	add r0, #0x8
	mov r1, #0x80
	bl FUN_0206A3A4
	add r0, r5, #0x0
	ldr r2, [r5, #0x0]
	add r0, #0x88
	mov r1, #0x64
	bl FUN_0206A3A4
	ldr r0, [sp, #0x4]
	bl FreeToHeap
	add sp, #0x1c
	pop {r4-r7, pc}

	thumb_func_start FUN_0206A370
FUN_0206A370: ; 0x0206A370
	ldr r3, _0206A37C ; =ReadWholeNarcMemberByIdPair
	add r2, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x2 ; NARC_POKETOOL_PERSONAL_PERSONAL
	bx r3
	nop
_0206A37C: .word ReadWholeNarcMemberByIdPair

	thumb_func_start FUN_0206A380
FUN_0206A380: ; 0x0206A380
	push {r4, lr}
	add r4, r2, #0x0
	bl ConvertUnownOrArceusSpecies
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x2 ; NARC_POKETOOL_PERSONAL_PERSONAL
	bl ReadWholeNarcMemberByIdPair
	pop {r4, pc}

	thumb_func_start FUN_0206A394
FUN_0206A394: ; 0x0206A394
	ldr r3, _0206A3A0 ; =ReadWholeNarcMemberByIdPair
	add r2, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x22 ; NARC_POKETOOL_PERSONAL_EVO
	bx r3
	nop
_0206A3A0: .word ReadWholeNarcMemberByIdPair

	thumb_func_start FUN_0206A3A4
FUN_0206A3A4: ; 0x0206A3A4
	push {r0-r3}
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r4, #0x0
	lsr r6, r1, #0x1
	beq _0206A3C6
	add r7, sp, #0x20
_0206A3B2:
	add r0, r7, #0x0
	bl FUN_0206A3D8
	ldrh r1, [r5, #0x0]
	add r4, r4, #0x1
	eor r0, r1
	strh r0, [r5, #0x0]
	add r5, r5, #0x2
	cmp r4, r6
	blo _0206A3B2
_0206A3C6:
	pop {r3-r7}
	pop {r3}
	add sp, #0x10
	bx r3
	.balign 4

	thumb_func_start FUN_0206A3D0
FUN_0206A3D0: ; 0x0206A3D0
	ldr r3, _0206A3D4 ; =FUN_0206A3A4
	bx r3
	.balign 4
_0206A3D4: .word FUN_0206A3A4

	thumb_func_start FUN_0206A3D8
FUN_0206A3D8: ; 0x0206A3D8
	ldr r2, [r0, #0x0]
	ldr r1, _0206A3F0 ; =0x41C64E6D
	add r3, r2, #0x0
	mul r3, r1
	ldr r1, _0206A3F4 ; =0x00006073
	add r1, r3, r1
	str r1, [r0, #0x0]
	lsr r0, r1, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr
	nop
_0206A3F0: .word 0x41C64E6D
_0206A3F4: .word 0x00006073

	thumb_func_start FUN_0206A3F8
FUN_0206A3F8: ; 0x0206A3F8
	push {r3-r4}
	mov r3, #0x0
	add r2, r3, #0x0
	lsr r4, r1, #0x1
	beq _0206A412
_0206A402:
	ldrh r1, [r0, #0x0]
	add r2, r2, #0x1
	add r0, r0, #0x2
	add r1, r3, r1
	lsl r1, r1, #0x10
	lsr r3, r1, #0x10
	cmp r2, r4
	blo _0206A402
_0206A412:
	add r0, r3, #0x0
	pop {r3-r4}
	bx lr

	thumb_func_start GetSubstruct
GetSubstruct: ; 0x0206A418
	push {r3, lr}
	mov r3, #0x3e
	lsl r3, r3, #0xc
	and r3, r1
	lsr r3, r3, #0xd
	cmp r3, #0x1f
	bhi _0206A478
	add r3, r3, r3
	add r3, pc
	ldrh r3, [r3, #0x6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_0206A432: ; jump table (using 16-bit offset)
	.short _0206A472 - _0206A432 - 2; case 0
	.short _0206A4A4 - _0206A432 - 2; case 1
	.short _0206A4D4 - _0206A432 - 2; case 2
	.short _0206A504 - _0206A432 - 2; case 3
	.short _0206A534 - _0206A432 - 2; case 4
	.short _0206A564 - _0206A432 - 2; case 5
	.short _0206A594 - _0206A432 - 2; case 6
	.short _0206A5C6 - _0206A432 - 2; case 7
	.short _0206A5F6 - _0206A432 - 2; case 8
	.short _0206A626 - _0206A432 - 2; case 9
	.short _0206A656 - _0206A432 - 2; case 10
	.short _0206A686 - _0206A432 - 2; case 11
	.short _0206A6B6 - _0206A432 - 2; case 12
	.short _0206A6E8 - _0206A432 - 2; case 13
	.short _0206A718 - _0206A432 - 2; case 14
	.short _0206A748 - _0206A432 - 2; case 15
	.short _0206A778 - _0206A432 - 2; case 16
	.short _0206A7A8 - _0206A432 - 2; case 17
	.short _0206A7D8 - _0206A432 - 2; case 18
	.short _0206A80A - _0206A432 - 2; case 19
	.short _0206A83A - _0206A432 - 2; case 20
	.short _0206A86A - _0206A432 - 2; case 21
	.short _0206A89A - _0206A432 - 2; case 22
	.short _0206A8CA - _0206A432 - 2; case 23
	.short _0206A472 - _0206A432 - 2; case 24
	.short _0206A4A4 - _0206A432 - 2; case 25
	.short _0206A4D4 - _0206A432 - 2; case 26
	.short _0206A504 - _0206A432 - 2; case 27
	.short _0206A534 - _0206A432 - 2; case 28
	.short _0206A564 - _0206A432 - 2; case 29
	.short _0206A594 - _0206A432 - 2; case 30
	.short _0206A5C6 - _0206A432 - 2; case 31
_0206A472:
	add r0, #0x8
	cmp r2, #0x3
	bls _0206A47A
_0206A478:
	b _0206A8F8
_0206A47A:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A486: ; jump table (using 16-bit offset)
	.short _0206A48E - _0206A486 - 2; case 0
	.short _0206A492 - _0206A486 - 2; case 1
	.short _0206A498 - _0206A486 - 2; case 2
	.short _0206A49E - _0206A486 - 2; case 3
_0206A48E:
	add r1, r0, #0x0
	b _0206A8F8
_0206A492:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A498:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A49E:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A4A4:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A59A
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A4B6: ; jump table (using 16-bit offset)
	.short _0206A4BE - _0206A4B6 - 2; case 0
	.short _0206A4C2 - _0206A4B6 - 2; case 1
	.short _0206A4C8 - _0206A4B6 - 2; case 2
	.short _0206A4CE - _0206A4B6 - 2; case 3
_0206A4BE:
	add r1, r0, #0x0
	b _0206A8F8
_0206A4C2:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A4C8:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A4CE:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A4D4:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A59A
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A4E6: ; jump table (using 16-bit offset)
	.short _0206A4EE - _0206A4E6 - 2; case 0
	.short _0206A4F2 - _0206A4E6 - 2; case 1
	.short _0206A4F8 - _0206A4E6 - 2; case 2
	.short _0206A4FE - _0206A4E6 - 2; case 3
_0206A4EE:
	add r1, r0, #0x0
	b _0206A8F8
_0206A4F2:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A4F8:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A4FE:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A504:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A59A
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A516: ; jump table (using 16-bit offset)
	.short _0206A51E - _0206A516 - 2; case 0
	.short _0206A522 - _0206A516 - 2; case 1
	.short _0206A528 - _0206A516 - 2; case 2
	.short _0206A52E - _0206A516 - 2; case 3
_0206A51E:
	add r1, r0, #0x0
	b _0206A8F8
_0206A522:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A528:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A52E:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A534:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A59A
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A546: ; jump table (using 16-bit offset)
	.short _0206A54E - _0206A546 - 2; case 0
	.short _0206A552 - _0206A546 - 2; case 1
	.short _0206A558 - _0206A546 - 2; case 2
	.short _0206A55E - _0206A546 - 2; case 3
_0206A54E:
	add r1, r0, #0x0
	b _0206A8F8
_0206A552:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A558:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A55E:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A564:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A59A
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A576: ; jump table (using 16-bit offset)
	.short _0206A57E - _0206A576 - 2; case 0
	.short _0206A582 - _0206A576 - 2; case 1
	.short _0206A588 - _0206A576 - 2; case 2
	.short _0206A58E - _0206A576 - 2; case 3
_0206A57E:
	add r1, r0, #0x0
	b _0206A8F8
_0206A582:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A588:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A58E:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A594:
	add r0, #0x8
	cmp r2, #0x3
	bls _0206A59C
_0206A59A:
	b _0206A8F8
_0206A59C:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A5A8: ; jump table (using 16-bit offset)
	.short _0206A5B0 - _0206A5A8 - 2; case 0
	.short _0206A5B6 - _0206A5A8 - 2; case 1
	.short _0206A5BA - _0206A5A8 - 2; case 2
	.short _0206A5C0 - _0206A5A8 - 2; case 3
_0206A5B0:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A5B6:
	add r1, r0, #0x0
	b _0206A8F8
_0206A5BA:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A5C0:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A5C6:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A6BC
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A5D8: ; jump table (using 16-bit offset)
	.short _0206A5E0 - _0206A5D8 - 2; case 0
	.short _0206A5E6 - _0206A5D8 - 2; case 1
	.short _0206A5EA - _0206A5D8 - 2; case 2
	.short _0206A5F0 - _0206A5D8 - 2; case 3
_0206A5E0:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A5E6:
	add r1, r0, #0x0
	b _0206A8F8
_0206A5EA:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A5F0:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A5F6:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A6BC
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A608: ; jump table (using 16-bit offset)
	.short _0206A610 - _0206A608 - 2; case 0
	.short _0206A616 - _0206A608 - 2; case 1
	.short _0206A61A - _0206A608 - 2; case 2
	.short _0206A620 - _0206A608 - 2; case 3
_0206A610:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A616:
	add r1, r0, #0x0
	b _0206A8F8
_0206A61A:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A620:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A626:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A6BC
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A638: ; jump table (using 16-bit offset)
	.short _0206A640 - _0206A638 - 2; case 0
	.short _0206A646 - _0206A638 - 2; case 1
	.short _0206A64A - _0206A638 - 2; case 2
	.short _0206A650 - _0206A638 - 2; case 3
_0206A640:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A646:
	add r1, r0, #0x0
	b _0206A8F8
_0206A64A:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A650:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A656:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A6BC
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A668: ; jump table (using 16-bit offset)
	.short _0206A670 - _0206A668 - 2; case 0
	.short _0206A676 - _0206A668 - 2; case 1
	.short _0206A67A - _0206A668 - 2; case 2
	.short _0206A680 - _0206A668 - 2; case 3
_0206A670:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A676:
	add r1, r0, #0x0
	b _0206A8F8
_0206A67A:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A680:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A686:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A6BC
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A698: ; jump table (using 16-bit offset)
	.short _0206A6A0 - _0206A698 - 2; case 0
	.short _0206A6A6 - _0206A698 - 2; case 1
	.short _0206A6AA - _0206A698 - 2; case 2
	.short _0206A6B0 - _0206A698 - 2; case 3
_0206A6A0:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A6A6:
	add r1, r0, #0x0
	b _0206A8F8
_0206A6AA:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A6B0:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A6B6:
	add r0, #0x8
	cmp r2, #0x3
	bls _0206A6BE
_0206A6BC:
	b _0206A8F8
_0206A6BE:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A6CA: ; jump table (using 16-bit offset)
	.short _0206A6D2 - _0206A6CA - 2; case 0
	.short _0206A6D8 - _0206A6CA - 2; case 1
	.short _0206A6DE - _0206A6CA - 2; case 2
	.short _0206A6E2 - _0206A6CA - 2; case 3
_0206A6D2:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A6D8:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A6DE:
	add r1, r0, #0x0
	b _0206A8F8
_0206A6E2:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A6E8:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A7DE
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A6FA: ; jump table (using 16-bit offset)
	.short _0206A702 - _0206A6FA - 2; case 0
	.short _0206A708 - _0206A6FA - 2; case 1
	.short _0206A70E - _0206A6FA - 2; case 2
	.short _0206A712 - _0206A6FA - 2; case 3
_0206A702:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A708:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A70E:
	add r1, r0, #0x0
	b _0206A8F8
_0206A712:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A718:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A7DE
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A72A: ; jump table (using 16-bit offset)
	.short _0206A732 - _0206A72A - 2; case 0
	.short _0206A738 - _0206A72A - 2; case 1
	.short _0206A73E - _0206A72A - 2; case 2
	.short _0206A742 - _0206A72A - 2; case 3
_0206A732:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A738:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A73E:
	add r1, r0, #0x0
	b _0206A8F8
_0206A742:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A748:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A7DE
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A75A: ; jump table (using 16-bit offset)
	.short _0206A762 - _0206A75A - 2; case 0
	.short _0206A768 - _0206A75A - 2; case 1
	.short _0206A76E - _0206A75A - 2; case 2
	.short _0206A772 - _0206A75A - 2; case 3
_0206A762:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A768:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A76E:
	add r1, r0, #0x0
	b _0206A8F8
_0206A772:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A778:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A7DE
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A78A: ; jump table (using 16-bit offset)
	.short _0206A792 - _0206A78A - 2; case 0
	.short _0206A798 - _0206A78A - 2; case 1
	.short _0206A79E - _0206A78A - 2; case 2
	.short _0206A7A2 - _0206A78A - 2; case 3
_0206A792:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A798:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A79E:
	add r1, r0, #0x0
	b _0206A8F8
_0206A7A2:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A7A8:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A7DE
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A7BA: ; jump table (using 16-bit offset)
	.short _0206A7C2 - _0206A7BA - 2; case 0
	.short _0206A7C8 - _0206A7BA - 2; case 1
	.short _0206A7CE - _0206A7BA - 2; case 2
	.short _0206A7D2 - _0206A7BA - 2; case 3
_0206A7C2:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A7C8:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A7CE:
	add r1, r0, #0x0
	b _0206A8F8
_0206A7D2:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A7D8:
	add r0, #0x8
	cmp r2, #0x3
	bls _0206A7E0
_0206A7DE:
	b _0206A8F8
_0206A7E0:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A7EC: ; jump table (using 16-bit offset)
	.short _0206A7F4 - _0206A7EC - 2; case 0
	.short _0206A7FA - _0206A7EC - 2; case 1
	.short _0206A800 - _0206A7EC - 2; case 2
	.short _0206A806 - _0206A7EC - 2; case 3
_0206A7F4:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A7FA:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A800:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A806:
	add r1, r0, #0x0
	b _0206A8F8
_0206A80A:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A8F8
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A81C: ; jump table (using 16-bit offset)
	.short _0206A824 - _0206A81C - 2; case 0
	.short _0206A82A - _0206A81C - 2; case 1
	.short _0206A830 - _0206A81C - 2; case 2
	.short _0206A836 - _0206A81C - 2; case 3
_0206A824:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A82A:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A830:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A836:
	add r1, r0, #0x0
	b _0206A8F8
_0206A83A:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A8F8
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A84C: ; jump table (using 16-bit offset)
	.short _0206A854 - _0206A84C - 2; case 0
	.short _0206A85A - _0206A84C - 2; case 1
	.short _0206A860 - _0206A84C - 2; case 2
	.short _0206A866 - _0206A84C - 2; case 3
_0206A854:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A85A:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A860:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A866:
	add r1, r0, #0x0
	b _0206A8F8
_0206A86A:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A8F8
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A87C: ; jump table (using 16-bit offset)
	.short _0206A884 - _0206A87C - 2; case 0
	.short _0206A88A - _0206A87C - 2; case 1
	.short _0206A890 - _0206A87C - 2; case 2
	.short _0206A896 - _0206A87C - 2; case 3
_0206A884:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A88A:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A890:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A896:
	add r1, r0, #0x0
	b _0206A8F8
_0206A89A:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A8F8
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A8AC: ; jump table (using 16-bit offset)
	.short _0206A8B4 - _0206A8AC - 2; case 0
	.short _0206A8BA - _0206A8AC - 2; case 1
	.short _0206A8C0 - _0206A8AC - 2; case 2
	.short _0206A8C6 - _0206A8AC - 2; case 3
_0206A8B4:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A8BA:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A8C0:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A8C6:
	add r1, r0, #0x0
	b _0206A8F8
_0206A8CA:
	add r0, #0x8
	cmp r2, #0x3
	bhi _0206A8F8
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206A8DC: ; jump table (using 16-bit offset)
	.short _0206A8E4 - _0206A8DC - 2; case 0
	.short _0206A8EA - _0206A8DC - 2; case 1
	.short _0206A8F0 - _0206A8DC - 2; case 2
	.short _0206A8F6 - _0206A8DC - 2; case 3
_0206A8E4:
	add r1, r0, #0x0
	add r1, #0x60
	b _0206A8F8
_0206A8EA:
	add r1, r0, #0x0
	add r1, #0x40
	b _0206A8F8
_0206A8F0:
	add r1, r0, #0x0
	add r1, #0x20
	b _0206A8F8
_0206A8F6:
	add r1, r0, #0x0
_0206A8F8:
	add r0, r1, #0x0
	pop {r3, pc}

	thumb_func_start ConvertUnownOrArceusSpecies
ConvertUnownOrArceusSpecies: ; 0x0206A8FC
	ldr r3, _0206A928 ; =0x00000182
	cmp r0, r3
	beq _0206A90C
	add r2, r3, #0x0
	add r2, #0x1b
	cmp r0, r2
	beq _0206A91A
	bx lr
_0206A90C:
	cmp r1, #0x0
	beq _0206A926
	cmp r1, #0x3
	bgt _0206A926
	add r3, #0x6d
	add r0, r1, r3
	bx lr
_0206A91A:
	cmp r1, #0x0
	beq _0206A926
	cmp r1, #0x2
	bgt _0206A926
	add r3, #0x70
	add r0, r1, r3
_0206A926:
	bx lr
	.balign 4
_0206A928: .word 0x00000182

	thumb_func_start MaskOfFlagNo
MaskOfFlagNo: ; 0x0206A92C
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r4, #0x1
	cmp r5, #0x20
	blt _0206A93A
	bl ErrorHandling
_0206A93A:
	mov r0, #0x0
	cmp r5, #0x0
	ble _0206A948
_0206A940:
	add r0, r0, #0x1
	lsl r4, r4, #0x1
	cmp r0, r5
	blt _0206A940
_0206A948:
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start LowestFlagNo
LowestFlagNo: ; 0x0206A94C
	mov r3, #0x1
	mov r2, #0x0
_0206A950:
	add r1, r0, #0x0
	tst r1, r3
	bne _0206A95E
	add r2, r2, #0x1
	lsl r3, r3, #0x1
	cmp r2, #0x20
	blt _0206A950
_0206A95E:
	add r0, r2, #0x0
	bx lr
	.balign 4

	thumb_func_start IsPokemonLegendaryOrMythical
IsPokemonLegendaryOrMythical: ; 0x0206A964
	ldr r3, _0206A980 ; =sLegendaryMonsList
	mov r2, #0x0
_0206A968:
	ldrh r1, [r3, #0x0]
	cmp r0, r1
	bne _0206A972
	mov r0, #0x1
	bx lr
_0206A972:
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, #0x12
	blo _0206A968
	mov r0, #0x0
	bx lr
	nop
_0206A980: .word sLegendaryMonsList

	thumb_func_start GetLegendaryMon
GetLegendaryMon: ; 0x0206A984
	cmp r0, #0x12
	blo _0206A98A
	mov r0, #0x0
_0206A98A:
	lsl r1, r0, #0x1
	ldr r0, _0206A994 ; =sLegendaryMonsList
	ldrh r0, [r0, r1]
	bx lr
	nop
_0206A994: .word sLegendaryMonsList

	thumb_func_start FUN_0206A998
FUN_0206A998: ; 0x0206A998
	push {r3, lr}
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl IsPokemonLegendaryOrMythical
	pop {r3, pc}

	thumb_func_start FUN_0206A9AC
FUN_0206A9AC: ; 0x0206A9AC
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r6, r2, #0x0
	bl FUN_020239BC
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl FUN_020672BC
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl FUN_020239CC
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x9c
	mov r2, #0x0
	bl FUN_020672BC
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_020239A0
	add r7, r0, #0x0
	mov r0, #0x8
	add r1, r6, #0x0
	bl FUN_020219F4
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x90
	add r2, r6, #0x0
	mov r4, #0x0
	bl FUN_020672BC
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x4]
	cmp r1, r0
	bne _0206AA1C
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	cmp r1, r0
	bne _0206AA1C
	add r0, r7, #0x0
	add r1, r6, #0x0
	bl FUN_02021CE0
	cmp r0, #0x0
	bne _0206AA1C
	mov r4, #0x1
_0206AA1C:
	add r0, r6, #0x0
	bl FUN_02021A20
	add r0, r7, #0x0
	bl FUN_02021A20
	add r0, r4, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0206AA30
FUN_0206AA30: ; 0x0206AA30
	push {r3, lr}
	cmp r0, #0x3f
	bgt _0206AA48
	bge _0206AA6C
	cmp r0, #0x1
	bgt _0206AA74
	cmp r0, #0x0
	blt _0206AA74
	beq _0206AA82
	cmp r0, #0x1
	beq _0206AA82
	b _0206AA74
_0206AA48:
	cmp r0, #0x5a
	bgt _0206AA50
	beq _0206AA70
	b _0206AA74
_0206AA50:
	add r1, r0, #0x0
	sub r1, #0x5b
	cmp r1, #0x3
	bhi _0206AA74
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0206AA64: ; jump table (using 16-bit offset)
	.short _0206AA70 - _0206AA64 - 2; case 0
	.short _0206AA70 - _0206AA64 - 2; case 1
	.short _0206AA70 - _0206AA64 - 2; case 2
	.short _0206AA70 - _0206AA64 - 2; case 3
_0206AA6C:
	mov r0, #0x2
	pop {r3, pc}
_0206AA70:
	sub r0, #0x57
	pop {r3, pc}
_0206AA74:
	bl FUN_0206AE00
	cmp r0, #0x1
	bne _0206AA80
	mov r0, #0x1
	pop {r3, pc}
_0206AA80:
	mov r0, #0x0
_0206AA82:
	pop {r3, pc}

	thumb_func_start FUN_0206AA84
FUN_0206AA84: ; 0x0206AA84
	push {r3-r4, lr}
	sub sp, #0x1c
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, sp, #0x0
	strb r0, [r1, #0x0]
	add r1, sp, #0x0
	add r1, #0x1
	mov r2, #0x18
	bl MIi_CpuClearFast
	add r0, r4, #0x0
	mov r1, #0xa1
	add r2, sp, #0x0
	bl FUN_02067830
	add r2, sp, #0x0
	add r0, r4, #0x0
	mov r1, #0xaa
	add r2, #0x1
	bl FUN_02067830
	add sp, #0x1c
	pop {r3-r4, pc}

	thumb_func_start FUN_0206AAB4
FUN_0206AAB4: ; 0x0206AAB4
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl FUN_02066A6C
	mov r4, #0x0
	str r0, [sp, #0x0]
	add r7, r4, #0x0
	add r6, sp, #0x4
_0206AAC6:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x36
	add r2, r7, #0x0
	bl FUN_020672BC
	cmp r0, #0x0
	beq _0206AAF0
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x42
	mov r2, #0x0
	bl FUN_020672BC
	add r1, r4, #0x0
	strb r0, [r6, #0x0]
	add r0, r5, #0x0
	add r1, #0x3a
	add r2, sp, #0x4
	bl FUN_02067960
_0206AAF0:
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _0206AAC6
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02066A94
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
