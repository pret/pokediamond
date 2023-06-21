	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD35_02254854
MOD35_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x34
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD35_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD35_022548F0
	add r1, r4, #0
	mov r2, #1
	bl sub_0200CA44
	cmp r0, #0
	beq _0225488C
	str r4, [r5]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0225488C:
	add r0, r4, #0
	bl FreeToHeap
_02254892:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254898: .word MOD35_022548F0
	thumb_func_end MOD35_02254854

	thumb_func_start MOD35_0225489C
MOD35_0225489C: ; 0x0225489C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r6, r2, #0
	bl MOD20_02252C40
	bl Save_DayCare_Get
	str r0, [r5, #0x30]
	ldr r1, [r5, #0x30]
	add r0, r5, #4
	bl MOD35_02254A50
	add r0, r5, #0
	add r0, #0x28
	add r1, r5, #4
	add r2, r6, #0
	bl MOD35_02254ADC
	cmp r0, #0
	beq _022548D6
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	str r4, [r5, #0x2c]
	mov r0, #1
	pop {r4, r5, r6, pc}
_022548D6:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD35_0225489C

	thumb_func_start MOD35_022548DC
MOD35_022548DC: ; 0x022548DC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl MOD35_02254B38
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD35_022548DC

	thumb_func_start MOD35_022548F0
MOD35_022548F0: ; 0x022548F0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	cmp r1, #3
	bhs _0225491C
	lsl r2, r1, #2
	ldr r1, _02254920 ; =MOD35_022550B8
	add r0, r4, #0
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _0225491C
	add r0, r4, #0
	bl MOD35_022548DC
	add r0, r5, #0
	bl sub_0200CAB4
	ldr r0, [r4, #0x2c]
	bl MOD20_022529A0
_0225491C:
	pop {r3, r4, r5, pc}
	nop
_02254920: .word MOD35_022550B8
	thumb_func_end MOD35_022548F0

	thumb_func_start MOD35_02254924
MOD35_02254924: ; 0x02254924
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD35_02254924

	thumb_func_start MOD35_0225492C
MOD35_0225492C: ; 0x0225492C
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _02254934
	b _02254936
_02254934:
	mov r1, #2
_02254936:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD35_0225492C

	thumb_func_start MOD35_02254940
MOD35_02254940: ; 0x02254940
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254950
	cmp r0, #1
	beq _02254960
	b _0225497A
_02254950:
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl MOD35_02254C48
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _0225497A
_02254960:
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl MOD35_02254C6C
	cmp r0, #0
	beq _0225497A
	ldr r0, [r4, #0x2c]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD35_0225492C
_0225497A:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD35_02254940

	thumb_func_start MOD35_02254980
MOD35_02254980: ; 0x02254980
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _02254994
	mov r1, #2
	bl MOD35_0225492C
	mov r0, #0
	pop {r4, pc}
_02254994:
	ldrb r1, [r4, #1]
	cmp r1, #0
	beq _022549A0
	cmp r1, #1
	beq _022549C0
	b _022549D0
_022549A0:
	bl MOD35_02254A08
	cmp r0, #0
	beq _022549D0
	ldr r1, [r4, #0x30]
	add r0, r4, #4
	bl MOD35_02254A50
	ldr r0, [r4, #0x28]
	mov r1, #2
	bl MOD35_02254C48
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549D0
_022549C0:
	ldr r0, [r4, #0x28]
	mov r1, #2
	bl MOD35_02254C6C
	cmp r0, #0
	beq _022549D0
	mov r0, #0
	strb r0, [r4, #1]
_022549D0:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD35_02254980

	thumb_func_start MOD35_022549D4
MOD35_022549D4: ; 0x022549D4
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _022549E4
	cmp r0, #1
	beq _022549F4
	b _02254A02
_022549E4:
	ldr r0, [r4, #0x28]
	mov r1, #1
	bl MOD35_02254C48
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A02
_022549F4:
	ldr r0, [r4, #0x28]
	bl MOD35_02254C78
	cmp r0, #0
	beq _02254A02
	mov r0, #1
	pop {r4, pc}
_02254A02:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD35_022549D4

	thumb_func_start MOD35_02254A08
MOD35_02254A08: ; 0x02254A08
	push {r3, lr}
	sub sp, #8
	ldr r0, [r0, #0x2c]
	bl MOD20_02252C08
	cmp r0, #0
	bne _02254A48
	add r0, sp, #4
	add r1, sp, #0
	bl sub_02020ACC
	cmp r0, #0
	beq _02254A48
	ldr r0, [sp, #4]
	sub r0, #0x10
	cmp r0, #0xbf
	bhs _02254A2E
	mov r1, #1
	b _02254A30
_02254A2E:
	mov r1, #0
_02254A30:
	ldr r0, [sp]
	sub r0, #0x10
	cmp r0, #0x9f
	bhs _02254A3C
	mov r0, #1
	b _02254A3E
_02254A3C:
	mov r0, #0
_02254A3E:
	tst r0, r1
	beq _02254A48
	add sp, #8
	mov r0, #1
	pop {r3, pc}
_02254A48:
	mov r0, #0
	add sp, #8
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD35_02254A08

	thumb_func_start MOD35_02254A50
MOD35_02254A50: ; 0x02254A50
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp]
	add r0, r1, #0
	str r1, [sp, #4]
	bl MOD05_021EC464
	ldr r1, [sp]
	strb r0, [r1]
	ldr r0, [sp, #4]
	bl Save_DayCare_GetEggPID
	ldr r1, [sp]
	mov r7, #0
	strb r0, [r1, #1]
	add r0, r1, #0
	ldrb r0, [r0]
	cmp r0, #0
	ble _02254AD6
	add r5, r1, #0
	add r6, r1, #0
_02254A7A:
	ldr r0, [sp, #4]
	add r1, r7, #0
	bl Save_DayCare_GetMonX
	str r0, [sp, #8]
	bl DayCareMon_GetBoxMon
	add r4, r0, #0
	bl AcquireBoxMonLock
	str r0, [sp, #0xc]
	add r0, r4, #0
	bl sub_0206B688
	str r0, [r5, #4]
	add r0, r4, #0
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	strh r0, [r6, #0x1c]
	add r0, r4, #0
	mov r1, #0x70
	mov r2, #0
	bl GetBoxMonData
	strh r0, [r6, #0x20]
	ldr r0, [sp, #8]
	bl MOD05_021EC7B4
	str r0, [r5, #0xc]
	add r0, r4, #0
	bl GetBoxMonGender
	str r0, [r5, #0x14]
	ldr r1, [sp, #0xc]
	add r0, r4, #0
	bl ReleaseBoxMonLock
	ldr r0, [sp]
	add r7, r7, #1
	ldrb r0, [r0]
	add r5, r5, #4
	add r6, r6, #2
	cmp r7, r0
	blt _02254A7A
_02254AD6:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD35_02254A50

	thumb_func_start MOD35_02254ADC
MOD35_02254ADC: ; 0x02254ADC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #8
	mov r1, #0x90
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254B2E
	add r0, #8
	mov r1, #4
	bl MOD20_022536F4
	str r5, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	bl MOD20_02252D24
	str r0, [r4, #0x20]
	add r0, r4, #0
	mov r2, #0
	add r0, #0x88
	str r2, [r0]
	ldr r0, _02254B34 ; =MOD35_02254E60
	add r1, r4, #0
	bl sub_0200CA98
	add r1, r4, #0
	add r1, #0x8c
	str r0, [r1]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD35_02254B54
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _02254B2E
	str r4, [r6]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254B2E:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_02254B34: .word MOD35_02254E60
	thumb_func_end MOD35_02254ADC

	thumb_func_start MOD35_02254B38
MOD35_02254B38: ; 0x02254B38
	push {r4, lr}
	add r4, r0, #0
	beq _02254B52
	bl MOD35_02254C18
	add r0, r4, #0
	add r0, #0x8c
	ldr r0, [r0]
	bl sub_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
_02254B52:
	pop {r4, pc}
	thumb_func_end MOD35_02254B38

	thumb_func_start MOD35_02254B54
MOD35_02254B54: ; 0x02254B54
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r7, r0, #0
	mov r0, #1
	str r1, [sp, #0xc]
	bl MOD20_022539C4
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x54
	bl GfGfxLoader_LoadWholePalette
	mov r1, #0x14
	bl _u32_div_f
	ldr r1, [sp, #0xc]
	str r0, [sp, #0x14]
	str r0, [r7, #0x78]
	bl MOD35_02254E88
	mov r0, #8
	str r0, [sp]
	add r0, r7, #0
	add r0, #0x50
	mov r1, #0xc
	mov r2, #0x52
	mov r3, #0x53
	bl MOD20_02253FBC
	mov r0, #8
	str r0, [sp]
	add r0, r7, #0
	add r0, #0x64
	mov r1, #0xc
	mov r2, #5
	mov r3, #6
	bl MOD20_02253FBC
	add r0, r7, #0
	str r0, [sp, #0x1c]
	add r0, #0x50
	str r0, [sp, #0x1c]
	add r0, r7, #0
	mov r4, #0
	str r0, [sp, #0x18]
	add r0, #0x64
	ldr r6, _02254C14 ; =MOD35_02255110
	add r5, r7, #0
	str r4, [sp, #0x10]
	str r0, [sp, #0x18]
_02254BC2:
	cmp r4, #0
	blt _02254BE2
	cmp r4, #2
	bgt _02254BE2
	ldr r0, [r7, #0x20]
	ldr r2, [sp, #0x18]
	add r1, r6, #0
	bl MOD20_02253E74
	ldr r2, [sp, #0x14]
	ldr r1, [sp, #0x10]
	str r0, [r5, #0x24]
	add r1, r2, r1
	bl MOD20_02253FA4
	b _02254BEE
_02254BE2:
	ldr r0, [r7, #0x20]
	ldr r2, [sp, #0x1c]
	add r1, r6, #0
	bl MOD20_02253E74
	str r0, [r5, #0x24]
_02254BEE:
	ldr r0, [r5, #0x24]
	mov r1, #1
	bl MOD20_02253FAC
	ldr r0, [sp, #0x10]
	add r4, r4, #1
	add r0, #0x20
	add r6, #0x10
	add r5, r5, #4
	str r0, [sp, #0x10]
	cmp r4, #0xb
	blt _02254BC2
	ldr r1, [sp, #0xc]
	add r0, r7, #0
	bl MOD35_02254EC8
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254C14: .word MOD35_02255110
	thumb_func_end MOD35_02254B54

	thumb_func_start MOD35_02254C18
MOD35_02254C18: ; 0x02254C18
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_02254C20:
	ldr r1, [r5, #0x24]
	cmp r1, #0
	beq _02254C2C
	ldr r0, [r6, #0x20]
	bl MOD20_02253F14
_02254C2C:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xb
	blt _02254C20
	add r0, r6, #0
	add r0, #0x64
	bl MOD20_02254014
	add r6, #0x50
	add r0, r6, #0
	bl MOD20_02254014
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD35_02254C18

	thumb_func_start MOD35_02254C48
MOD35_02254C48: ; 0x02254C48
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254C68 ; =MOD35_022550E0
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254C68: .word MOD35_022550E0
	thumb_func_end MOD35_02254C48

	thumb_func_start MOD35_02254C6C
MOD35_02254C6C: ; 0x02254C6C
	ldr r3, _02254C74 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254C74: .word MOD20_02253794
	thumb_func_end MOD35_02254C6C

	thumb_func_start MOD35_02254C78
MOD35_02254C78: ; 0x02254C78
	ldr r3, _02254C80 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254C80: .word MOD20_022537B8
	thumb_func_end MOD35_02254C78

	thumb_func_start MOD35_02254C84
MOD35_02254C84: ; 0x02254C84
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD35_02254C84

	thumb_func_start MOD35_02254C98
MOD35_02254C98: ; 0x02254C98
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254D24 ; =MOD35_022550C4
	mov r1, #6
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x51
	mov r3, #6
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x50
	mov r3, #6
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	ldr r0, [r5, #4]
	mov r1, #6
	bl BgCommitTilemapBufferToVram
	ldr r1, _02254D28 ; =0x0400104C
	mov r0, #0
	strb r0, [r1]
	strb r0, [r1, #1]
	sub r1, #0x4c
	ldr r3, [r1]
	ldr r2, [r1]
	ldr r0, _02254D2C ; =0xFFFFE0FF
	str r3, [sp, #0x10]
	and r0, r2
	lsl r2, r3, #0x13
	lsr r3, r2, #0x1b
	mov r2, #4
	orr r2, r3
	lsl r2, r2, #8
	orr r0, r2
	str r0, [r1]
	add r0, r4, #0
	bl MOD35_02254C84
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_02254D24: .word MOD35_022550C4
_02254D28: .word 0x0400104C
_02254D2C: .word 0xFFFFE0FF
	thumb_func_end MOD35_02254C98

	thumb_func_start MOD35_02254D30
MOD35_02254D30: ; 0x02254D30
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538AC
	cmp r0, #0
	beq _02254D4C
	cmp r0, #1
	beq _02254D5A
	pop {r3, r4, r5, pc}
_02254D4C:
	mov r0, #1
	add r4, #0x84
	str r0, [r4]
	add r0, r5, #0
	bl MOD20_022538B0
	pop {r3, r4, r5, pc}
_02254D5A:
	add r0, r4, #0
	mov r1, #2
	bl MOD35_02254C6C
	cmp r0, #0
	beq _02254D7C
	ldr r0, _02254D80 ; =0x0400104C
	mov r1, #0
	strb r1, [r0]
	strb r1, [r0, #1]
	ldr r0, [r4, #4]
	mov r1, #6
	bl FreeBgTilemapBuffer
	add r0, r5, #0
	bl MOD35_02254C84
_02254D7C:
	pop {r3, r4, r5, pc}
	nop
_02254D80: .word 0x0400104C
	thumb_func_end MOD35_02254D30

	thumb_func_start MOD35_02254D84
MOD35_02254D84: ; 0x02254D84
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r6, r0, #0
	add r0, r5, #0
	bl MOD20_022538AC
	cmp r0, #3
	bhi _02254E50
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02254DAE: ; jump table
	.short _02254DB6 - _02254DAE - 2 ; case 0
	.short _02254DDC - _02254DAE - 2 ; case 1
	.short _02254DF4 - _02254DAE - 2 ; case 2
	.short _02254E4A - _02254DAE - 2 ; case 3
_02254DB6:
	add r0, r4, #0
	mov r1, #0
	add r0, #0x84
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	mov r0, #0xa
	str r0, [r4, #0x7c]
	add r0, r4, #0
	bl MOD35_02254E58
	ldr r0, _02254E54 ; =0x00000678
	bl MOD20_02252B28
	add r0, r5, #0
	bl MOD20_022538B0
	pop {r4, r5, r6, pc}
_02254DDC:
	ldr r0, [r4, #0x78]
	add r1, r6, #0
	bl MOD35_02254E88
	add r0, r4, #0
	add r1, r6, #0
	bl MOD35_02254EC8
	add r0, r5, #0
	bl MOD20_022538B0
	pop {r4, r5, r6, pc}
_02254DF4:
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	beq _02254E10
	mov r0, #0
	str r0, [r4, #0x7c]
	add r0, r4, #0
	bl MOD35_02254E58
	add r0, r5, #0
	bl MOD20_022538B0
	pop {r4, r5, r6, pc}
_02254E10:
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #4
	blo _02254E50
	add r0, r4, #0
	mov r1, #0
	add r0, #0x80
	str r1, [r0]
	ldr r0, [r4, #0x7c]
	sub r0, r0, #1
	str r0, [r4, #0x7c]
	add r0, r4, #0
	bl MOD35_02254E58
	ldr r0, [r4, #0x7c]
	cmp r0, #0
	bne _02254E50
	add r0, r5, #0
	bl MOD20_022538B0
	pop {r4, r5, r6, pc}
_02254E4A:
	add r0, r5, #0
	bl MOD35_02254C84
_02254E50:
	pop {r4, r5, r6, pc}
	nop
_02254E54: .word 0x00000678
	thumb_func_end MOD35_02254D84

	thumb_func_start MOD35_02254E58
MOD35_02254E58: ; 0x02254E58
	mov r1, #1
	add r0, #0x88
	str r1, [r0]
	bx lr
	thumb_func_end MOD35_02254E58

	thumb_func_start MOD35_02254E60
MOD35_02254E60: ; 0x02254E60
	add r0, r1, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #0
	beq _02254E82
	ldr r2, [r1, #0x7c]
	ldr r3, _02254E84 ; =0x0400104C
	lsl r0, r2, #4
	orr r0, r2
	strb r0, [r3]
	ldr r2, [r1, #0x7c]
	add r1, #0x88
	lsl r0, r2, #4
	orr r0, r2
	strb r0, [r3, #1]
	mov r0, #0
	str r0, [r1]
_02254E82:
	bx lr
	.align 2, 0
_02254E84: .word 0x0400104C
	thumb_func_end MOD35_02254E60

	thumb_func_start MOD35_02254E88
MOD35_02254E88: ; 0x02254E88
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #1
	add r4, r1, #0
	add r1, r0, #0
	mov r2, #0
	bl sub_0206B6D4
	ldrb r1, [r4]
	cmp r1, #0
	beq _02254EA4
	ldr r1, [r4, #4]
	b _02254EA6
_02254EA4:
	add r1, r0, #0
_02254EA6:
	str r1, [sp]
	ldrb r1, [r4]
	cmp r1, #1
	bls _02254EB2
	ldr r1, [r4, #8]
	b _02254EB4
_02254EB2:
	add r1, r0, #0
_02254EB4:
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, sp, #0
	mov r2, #3
	mov r3, #1
	bl MOD20_02253A04
	add sp, #0xc
	pop {r4, r5, pc}
	thumb_func_end MOD35_02254E88

	thumb_func_start MOD35_02254EC8
MOD35_02254EC8: ; 0x02254EC8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r0, #0
	add r6, r1, #0
	str r0, [sp]
	ldrb r0, [r6]
	cmp r0, #0
	ble _02254F00
	add r4, r6, #0
	add r5, r7, #0
_02254EDC:
	ldrh r0, [r4, #0x1c]
	ldrh r1, [r4, #0x20]
	mov r2, #0
	bl sub_0206B7BC
	add r1, r0, #0
	ldr r0, [r5, #0x24]
	add r1, r1, #1
	bl MOD20_02253F9C
	ldr r0, [sp]
	ldrb r1, [r6]
	add r0, r0, #1
	add r4, r4, #2
	add r5, r5, #4
	str r0, [sp]
	cmp r0, r1
	blt _02254EDC
_02254F00:
	mov r0, #1
	mov r1, #0
	add r2, r0, #0
	bl sub_0206B7BC
	add r1, r0, #0
	ldr r0, [r7, #0x2c]
	add r1, r1, #1
	bl MOD20_02253F9C
	ldrb r0, [r6]
	cmp r0, #0
	beq _02254F36
	ldrh r0, [r6, #0x1c]
	mov r1, #0x1c ; BASE_FLIP
	bl GetMonBaseStat
	cmp r0, #0
	ldr r0, [r7, #0x24]
	beq _02254F30
	mov r1, #6
	bl MOD20_02253F28
	b _02254F36
_02254F30:
	mov r1, #7
	bl MOD20_02253F28
_02254F36:
	add r0, r7, #0
	ldr r1, [r6, #0xc]
	add r0, #0x30
	bl MOD35_02254FD8
	add r0, r7, #0
	ldr r1, [r6, #0x10]
	add r0, #0x3c
	bl MOD35_02254FD8
	ldr r0, [r7, #0x48]
	ldr r1, [r6, #0x14]
	bl MOD35_02255094
	ldr r0, [r7, #0x4c]
	ldr r1, [r6, #0x18]
	bl MOD35_02255094
	ldrb r0, [r6]
	cmp r0, #0
	bne _02254F64
	mov r4, #1
	b _02254F66
_02254F64:
	mov r4, #0
_02254F66:
	ldr r0, [r7, #0x24]
	add r1, r4, #0
	bl MOD20_02253F78
	ldr r0, [r7, #0x30]
	add r1, r4, #0
	bl MOD20_02253F78
	ldr r0, [r7, #0x34]
	add r1, r4, #0
	bl MOD20_02253F78
	ldr r0, [r7, #0x38]
	add r1, r4, #0
	bl MOD20_02253F78
	ldr r0, [r7, #0x48]
	add r1, r4, #0
	bl MOD20_02253F78
	ldrb r0, [r6]
	cmp r0, #1
	bhi _02254F98
	mov r4, #1
	b _02254F9A
_02254F98:
	mov r4, #0
_02254F9A:
	ldr r0, [r7, #0x28]
	add r1, r4, #0
	bl MOD20_02253F78
	ldr r0, [r7, #0x3c]
	add r1, r4, #0
	bl MOD20_02253F78
	ldr r0, [r7, #0x40]
	add r1, r4, #0
	bl MOD20_02253F78
	ldr r0, [r7, #0x44]
	add r1, r4, #0
	bl MOD20_02253F78
	ldr r0, [r7, #0x4c]
	add r1, r4, #0
	bl MOD20_02253F78
	ldrb r0, [r6, #1]
	cmp r0, #0
	bne _02254FCC
	mov r1, #1
	b _02254FCE
_02254FCC:
	mov r1, #0
_02254FCE:
	ldr r0, [r7, #0x2c]
	bl MOD20_02253F78
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD35_02254EC8

	thumb_func_start MOD35_02254FD8
MOD35_02254FD8: ; 0x02254FD8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r1, #0
	str r0, [sp]
	cmp r7, #0x64
	bls _02254FE6
	mov r7, #0x64
_02254FE6:
	ldr r2, _02255088 ; =0x04000280
	mov r3, #0
	strh r3, [r2]
	add r0, r2, #0
	str r7, [r2, #0x10]
	mov r1, #0x64
	add r0, #0x18
	str r1, [r0]
	str r3, [r0, #4]
	lsr r0, r2, #0xb
_02254FFA:
	ldrh r1, [r2]
	tst r1, r0
	bne _02254FFA
	ldr r0, _0225508C ; =0x040002A0
	ldr r4, _02255088 ; =0x04000280
	ldr r0, [r0]
	str r0, [sp, #4]
	lsr r0, r4, #0xb
_0225500A:
	ldrh r1, [r4]
	tst r1, r0
	bne _0225500A
	ldr r3, _02255090 ; =0x040002A8
	mov r1, #0
	ldr r2, [r3]
	add r0, r3, #0
	strh r1, [r4]
	sub r0, #0x18
	str r2, [r0]
	mov r0, #0xa
	sub r3, #0x10
	str r0, [r3]
	ldr r2, _02255088 ; =0x04000280
	str r1, [r3, #4]
	lsr r0, r2, #0xb
_0225502A:
	ldrh r1, [r2]
	tst r1, r0
	bne _0225502A
	ldr r0, _0225508C ; =0x040002A0
	ldr r2, _02255088 ; =0x04000280
	ldr r0, [r0]
	str r0, [sp, #8]
	lsr r0, r2, #0xb
_0225503A:
	ldrh r1, [r2]
	tst r1, r0
	bne _0225503A
	ldr r0, _02255090 ; =0x040002A8
	ldr r5, [sp]
	ldr r0, [r0]
	mov r6, #0
	str r0, [sp, #0xc]
	add r4, sp, #4
_0225504C:
	ldr r0, [r5]
	ldr r1, [r4]
	bl MOD20_02253F28
	add r6, r6, #1
	add r4, r4, #4
	add r5, r5, #4
	cmp r6, #3
	blt _0225504C
	cmp r7, #0x64
	bhs _02255066
	mov r1, #1
	b _02255068
_02255066:
	mov r1, #0
_02255068:
	ldr r0, [sp]
	ldr r0, [r0]
	bl MOD20_02253F78
	cmp r7, #0xa
	bhs _02255078
	mov r1, #1
	b _0225507A
_02255078:
	mov r1, #0
_0225507A:
	ldr r0, [sp]
	ldr r0, [r0, #4]
	bl MOD20_02253F78
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02255088: .word 0x04000280
_0225508C: .word 0x040002A0
_02255090: .word 0x040002A8
	thumb_func_end MOD35_02254FD8

	thumb_func_start MOD35_02255094
MOD35_02255094: ; 0x02255094
	push {r3, lr}
	cmp r1, #0
	beq _022550A0
	cmp r1, #1
	beq _022550A8
	b _022550B0
_022550A0:
	mov r1, #0xa
	bl MOD20_02253F28
	pop {r3, pc}
_022550A8:
	mov r1, #0xb
	bl MOD20_02253F28
	pop {r3, pc}
_022550B0:
	mov r1, #0xc
	bl MOD20_02253F28
	pop {r3, pc}
	thumb_func_end MOD35_02255094

	.section .rodata

	.global MOD35_022550B8
MOD35_022550B8: ; 0x022550B8
	.word MOD35_02254940, MOD35_02254980, MOD35_022549D4

	.global MOD35_022550C4
MOD35_022550C4: ; 0x022550C4
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD35_022550E0
MOD35_022550E0: ; 0x022550E0
	.word 0x00, MOD35_02254C98, 0x00
	.word 0x01, MOD35_02254D30, 0x00
	.word 0x02, MOD35_02254D84, 0x00
	.word 0x00, 0x00000000, 0x00

	.global MOD35_02255110
MOD35_02255110: ; 0x02255110
	.byte 0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 0x08, 0x00
	.byte 0x07, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x0A, 0x00, 0x00, 0x00, 0x08, 0x00
	.byte 0x06, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x80, 0x08, 0x00
	.byte 0x04, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x80, 0x02, 0x00
	.byte 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x80, 0x02, 0x00
	.byte 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x80, 0x02, 0x00
	.byte 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x09, 0x00, 0x00, 0x80, 0x02, 0x00
	.byte 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0A, 0x00, 0x00, 0x80, 0x02, 0x00
	.byte 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0B, 0x00, 0x00, 0x80, 0x02, 0x00
	.byte 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x80, 0x02, 0x00
	.byte 0x0A, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0C, 0x00, 0x00, 0x80, 0x02, 0x00
	.byte 0x0A, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
