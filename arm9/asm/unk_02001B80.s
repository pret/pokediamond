	.include "asm/macros.inc"
	.include "global.inc"

	.extern gMain

	.section .rodata

	.balign 4, 0
	.global UNK_020ECAC8
UNK_020ECAC8: ; 0x020ECAC8
	.incbin "graphics/unk_020ECAC8.4bpp"

	.text

	thumb_func_start FUN_02001B8C
FUN_02001B8C: ; 0x02001B8C
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	str r3, [sp, #0x0]
	add r0, sp, #0x10
	ldrb r0, [r0, #0x10]
	add r6, r1, #0x0
	mov r1, #0x20
	add r7, r2, #0x0
	str r0, [sp, #0x4]
	bl AllocFromHeap
	add r4, r0, #0x0
	add r3, r5, #0x0
	ldmia r3!, {r0-r1}
	add r2, r4, #0x0
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldr r0, [sp, #0x4]
	bl ListMenuCursorNew
	str r0, [r4, #0xc]
	ldr r0, [sp, #0x24]
	str r0, [r4, #0x10]
	ldr r0, [sp, #0x0]
	strb r0, [r4, #0x15]
	add r0, r4, #0x0
	bl FUN_02001FB4
	strb r0, [r4, #0x16]
	add r0, sp, #0x10
	ldrb r0, [r0, #0x10]
	mov r1, #0x0
	strb r0, [r4, #0x1c]
	strb r6, [r4, #0x17]
	strb r7, [r4, #0x18]
	ldrb r0, [r5, #0x8]
	bl GetFontAttribute
	add r6, r0, #0x0
	ldrb r0, [r5, #0x8]
	mov r1, #0x2
	bl GetFontAttribute
	add r0, r6, r0
	strb r0, [r4, #0x19]
	ldrb r0, [r5, #0x8]
	mov r1, #0x1
	bl GetFontAttribute
	add r6, r0, #0x0
	ldrb r0, [r5, #0x8]
	mov r1, #0x3
	bl GetFontAttribute
	add r0, r6, r0
	strb r0, [r4, #0x1a]
	add r0, r4, #0x0
	bl FUN_02001FF4
	add r0, r4, #0x0
	bl FUN_02002080
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02001C14
FUN_02001C14: ; 0x02001C14
	push {r4, lr}
	sub sp, #0x8
	add r4, sp, #0x0
	ldrb r4, [r4, #0x10]
	str r4, [sp, #0x0]
	ldr r4, [sp, #0x14]
	str r4, [sp, #0x4]
	bl FUN_02001B8C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	bl CopyWindowToVram
	add r0, r4, #0x0
	add sp, #0x8
	pop {r4, pc}

	thumb_func_start FUN_02001C34
FUN_02001C34: ; 0x02001C34
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldrb r0, [r5, #0x8]
	add r6, r1, #0x0
	add r4, r2, #0x0
	mov r1, #0x0
	bl GetFontAttribute
	add r1, r0, #0x0
	str r4, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r2, #0x0
	add r3, r6, #0x0
	bl FUN_02001C14
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_02001C5C
FUN_02001C5C: ; 0x02001C5C
	push {r4, lr}
	add r4, r0, #0x0
	cmp r1, #0x0
	beq _02001C68
	ldrb r0, [r4, #0x15]
	strb r0, [r1, #0x0]
_02001C68:
	ldr r0, [r4, #0xc]
	bl DestroyListMenuCursorObj
	ldrb r0, [r4, #0x1c]
	add r1, r4, #0x0
	bl FreeToHeapExplicit
	pop {r4, pc}

	thumb_func_start FUN_02001C78
FUN_02001C78: ; 0x02001C78
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	ldr r2, _02001D24 ; =gMain
	strb r1, [r4, #0x1b]
	ldr r2, [r2, #0x48]
	mov r5, #0x1
	add r3, r2, #0x0
	tst r3, r5
	beq _02001C9E
	ldr r0, _02001D28 ; =0x000005DC
	bl FUN_020054C8
	ldrb r0, [r4, #0x15]
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x3
	add r0, r1, r0
	ldr r0, [r0, #0x4]
	pop {r3-r5, pc}
_02001C9E:
	ldr r3, [r4, #0x10]
	tst r3, r2
	beq _02001CAE
	ldr r0, _02001D28 ; =0x000005DC
	bl FUN_020054C8
	sub r0, r5, #0x3
	pop {r3-r5, pc}
_02001CAE:
	mov r3, #0x40
	tst r3, r2
	beq _02001CC8
	ldr r2, _02001D28 ; =0x000005DC
	bl FUN_02001E64
	cmp r0, #0x1
	bne _02001CC2
	add r0, r5, #0x0
	strb r0, [r4, #0x1b]
_02001CC2:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_02001CC8:
	mov r1, #0x80
	tst r1, r2
	beq _02001CE4
	ldr r2, _02001D28 ; =0x000005DC
	add r1, r5, #0x0
	bl FUN_02001E64
	cmp r0, #0x1
	bne _02001CDE
	mov r0, #0x2
	strb r0, [r4, #0x1b]
_02001CDE:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_02001CE4:
	mov r1, #0x20
	tst r1, r2
	beq _02001D00
	ldr r2, _02001D28 ; =0x000005DC
	mov r1, #0x2
	bl FUN_02001E64
	cmp r0, #0x1
	bne _02001CFA
	mov r0, #0x3
	strb r0, [r4, #0x1b]
_02001CFA:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_02001D00:
	mov r1, #0x10
	tst r2, r1
	beq _02001D1C
	ldr r2, _02001D28 ; =0x000005DC
	mov r1, #0x3
	bl FUN_02001E64
	cmp r0, #0x1
	bne _02001D16
	mov r0, #0x4
	strb r0, [r4, #0x1b]
_02001D16:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_02001D1C:
	sub r1, #0x11
	add r0, r1, #0x0
	pop {r3-r5, pc}
	nop
_02001D24: .word gMain
_02001D28: .word 0x000005DC

	thumb_func_start FUN_02001D2C
FUN_02001D2C: ; 0x02001D2C
	push {r4-r6, lr}
	add r2, r1, #0x0
	add r4, r0, #0x0
	mov r1, #0x0
	ldr r3, _02001DD4 ; =gMain
	strb r1, [r4, #0x1b]
	ldr r5, [r3, #0x48]
	mov r3, #0x1
	add r6, r5, #0x0
	tst r6, r3
	beq _02001D54
	ldr r0, _02001DD8 ; =0x000005DC
	bl FUN_020054C8
	ldrb r0, [r4, #0x15]
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x3
	add r0, r1, r0
	ldr r0, [r0, #0x4]
	pop {r4-r6, pc}
_02001D54:
	ldr r6, [r4, #0x10]
	tst r6, r5
	beq _02001D66
	ldr r0, _02001DD8 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x1
	mvn r0, r0
	pop {r4-r6, pc}
_02001D66:
	mov r6, #0x40
	tst r6, r5
	beq _02001D7E
	bl FUN_02001E64
	cmp r0, #0x1
	bne _02001D78
	mov r0, #0x1
	strb r0, [r4, #0x1b]
_02001D78:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_02001D7E:
	mov r1, #0x80
	tst r1, r5
	beq _02001D98
	add r1, r3, #0x0
	bl FUN_02001E64
	cmp r0, #0x1
	bne _02001D92
	mov r0, #0x2
	strb r0, [r4, #0x1b]
_02001D92:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_02001D98:
	mov r1, #0x20
	tst r1, r5
	beq _02001DB2
	mov r1, #0x2
	bl FUN_02001E64
	cmp r0, #0x1
	bne _02001DAC
	mov r0, #0x3
	strb r0, [r4, #0x1b]
_02001DAC:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_02001DB2:
	mov r1, #0x10
	add r3, r5, #0x0
	tst r3, r1
	beq _02001DCE
	mov r1, #0x3
	bl FUN_02001E64
	cmp r0, #0x1
	bne _02001DC8
	mov r0, #0x4
	strb r0, [r4, #0x1b]
_02001DC8:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_02001DCE:
	sub r1, #0x11
	add r0, r1, #0x0
	pop {r4-r6, pc}
	.balign 4
_02001DD4: .word gMain
_02001DD8: .word 0x000005DC

	thumb_func_start FUN_02001DDC
FUN_02001DDC: ; 0x02001DDC
	push {r4, lr}
	add r4, r0, #0x0
	cmp r1, #0x5
	bhi _02001E52
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02001DF0: ; jump table (using 16-bit offset)
	.short _02001DFC - _02001DF0 - 2; case 0
	.short _02001E0E - _02001DF0 - 2; case 1
	.short _02001E1A - _02001DF0 - 2; case 2
	.short _02001E28 - _02001DF0 - 2; case 3
	.short _02001E36 - _02001DF0 - 2; case 4
	.short _02001E44 - _02001DF0 - 2; case 5
_02001DFC:
	ldr r0, _02001E58 ; =0x000005DC
	bl FUN_020054C8
	ldrb r0, [r4, #0x15]
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x3
	add r0, r1, r0
	ldr r0, [r0, #0x4]
	pop {r4, pc}
_02001E0E:
	ldr r0, _02001E58 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x1
	mvn r0, r0
	pop {r4, pc}
_02001E1A:
	ldr r2, _02001E58 ; =0x000005DC
	mov r1, #0x0
	bl FUN_02001E64
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}
_02001E28:
	ldr r2, _02001E58 ; =0x000005DC
	mov r1, #0x1
	bl FUN_02001E64
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}
_02001E36:
	ldr r2, _02001E58 ; =0x000005DC
	mov r1, #0x2
	bl FUN_02001E64
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}
_02001E44:
	ldr r2, _02001E58 ; =0x000005DC
	mov r1, #0x3
	bl FUN_02001E64
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}
_02001E52:
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}
	.balign 4
_02001E58: .word 0x000005DC

	thumb_func_start FUN_02001E5C
FUN_02001E5C: ; 0x02001E5C
	ldrb r0, [r0, #0x15]
	bx lr

	thumb_func_start FUN_02001E60
FUN_02001E60: ; 0x02001E60
	ldrb r0, [r0, #0x1b]
	bx lr

	thumb_func_start FUN_02001E64
FUN_02001E64: ; 0x02001E64
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r6, r2, #0x0
	ldrb r4, [r5, #0x15]
	bl FUN_02001EBC
	cmp r0, #0x0
	bne _02001E7C
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_02001E7C:
	ldrb r0, [r5, #0x8]
	mov r1, #0x6
	bl GetFontAttribute
	add r1, sp, #0x8
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, #0x1
	add r2, sp, #0x8
	add r3, r4, #0x0
	bl FUN_020020B0
	mov r0, #0x8
	str r0, [sp, #0x0]
	ldrb r0, [r5, #0x1a]
	add r3, sp, #0x8
	add r1, r7, #0x0
	str r0, [sp, #0x4]
	ldrb r2, [r3, #0x1]
	ldrb r3, [r3, #0x0]
	ldr r0, [r5, #0x4]
	bl FillWindowPixelRect
	add r0, r5, #0x0
	bl FUN_02002080
	add r0, r6, #0x0
	bl FUN_020054C8
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_02001EBC
FUN_02001EBC: ; 0x02001EBC
	push {r4-r6, lr}
	add r5, r0, #0x0
	cmp r1, #0x0
	bne _02001EFA
	ldrb r6, [r5, #0xa]
	cmp r6, #0x1
	bhi _02001ECE
	mov r0, #0x0
	pop {r4-r6, pc}
_02001ECE:
	ldrb r4, [r5, #0x15]
	add r1, r6, #0x0
	add r0, r4, #0x0
	bl _s32_div_f
	cmp r1, #0x0
	bne _02001EF2
	ldrb r0, [r5, #0xb]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1e
	bne _02001EE8
	mov r0, #0x0
	pop {r4-r6, pc}
_02001EE8:
	sub r0, r6, #0x1
	add r0, r4, r0
	lsl r0, r0, #0x18
	asr r2, r0, #0x18
	b _02001F9A
_02001EF2:
	sub r0, r4, #0x1
	lsl r0, r0, #0x18
	asr r2, r0, #0x18
	b _02001F9A
_02001EFA:
	cmp r1, #0x1
	bne _02001F32
	ldrb r1, [r5, #0xa]
	cmp r1, #0x1
	bhi _02001F08
	mov r0, #0x0
	pop {r4-r6, pc}
_02001F08:
	ldrb r6, [r5, #0x15]
	sub r4, r1, #0x1
	add r0, r6, #0x0
	bl _s32_div_f
	cmp r4, r1
	bne _02001F2A
	ldrb r0, [r5, #0xb]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1e
	bne _02001F22
	mov r0, #0x0
	pop {r4-r6, pc}
_02001F22:
	sub r0, r6, r4
	lsl r0, r0, #0x18
	asr r2, r0, #0x18
	b _02001F9A
_02001F2A:
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	asr r2, r0, #0x18
	b _02001F9A
_02001F32:
	cmp r1, #0x2
	bne _02001F68
	ldrb r3, [r5, #0x9]
	cmp r3, #0x1
	bhi _02001F40
	mov r0, #0x0
	pop {r4-r6, pc}
_02001F40:
	ldrb r2, [r5, #0xa]
	ldrb r1, [r5, #0x15]
	cmp r1, r2
	bhs _02001F60
	ldrb r0, [r5, #0xb]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1e
	bne _02001F54
	mov r0, #0x0
	pop {r4-r6, pc}
_02001F54:
	sub r0, r3, #0x1
	mul r0, r2
	add r0, r1, r0
	lsl r0, r0, #0x18
	asr r2, r0, #0x18
	b _02001F9A
_02001F60:
	sub r0, r1, r2
	lsl r0, r0, #0x18
	asr r2, r0, #0x18
	b _02001F9A
_02001F68:
	ldrb r2, [r5, #0x9]
	cmp r2, #0x1
	bhi _02001F72
	mov r0, #0x0
	pop {r4-r6, pc}
_02001F72:
	ldrb r1, [r5, #0xa]
	ldrb r0, [r5, #0x15]
	sub r2, r2, #0x1
	mul r2, r1
	cmp r0, r2
	blt _02001F94
	ldrb r2, [r5, #0xb]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x1e
	bne _02001F8A
	mov r0, #0x0
	pop {r4-r6, pc}
_02001F8A:
	bl _s32_div_f
	lsl r0, r1, #0x18
	asr r2, r0, #0x18
	b _02001F9A
_02001F94:
	add r0, r0, r1
	lsl r0, r0, #0x18
	asr r2, r0, #0x18
_02001F9A:
	ldr r1, [r5, #0x0]
	lsl r0, r2, #0x3
	add r0, r1, r0
	ldr r1, [r0, #0x4]
	mov r0, #0x2
	mvn r0, r0
	cmp r1, r0
	bne _02001FAE
	mov r0, #0x0
	pop {r4-r6, pc}
_02001FAE:
	strb r2, [r5, #0x15]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_02001FB4
FUN_02001FB4: ; 0x02001FB4
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldrb r1, [r5, #0x9]
	ldrb r0, [r5, #0xa]
	mov r6, #0x0
	add r4, r6, #0x0
	mul r0, r1
	cmp r0, #0x0
	ble _02001FF0
	add r7, r6, #0x0
_02001FC8:
	ldr r2, [r5, #0x0]
	lsl r1, r4, #0x3
	ldr r1, [r2, r1]
	ldrb r0, [r5, #0x8]
	add r2, r7, #0x0
	bl FUN_02002E14
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r6, r0
	bhs _02001FE0
	add r6, r0, #0x0
_02001FE0:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldrb r1, [r5, #0x9]
	ldrb r0, [r5, #0xa]
	mul r0, r1
	cmp r4, r0
	blt _02001FC8
_02001FF0:
	add r0, r6, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02001FF4
FUN_02001FF4: ; 0x02001FF4
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldrb r0, [r5, #0x8]
	mov r1, #0x6
	bl GetFontAttribute
	add r1, r0, #0x0
	ldr r0, [r5, #0x4]
	bl FillWindowPixelBuffer
	ldrb r0, [r5, #0x19]
	ldrb r1, [r5, #0x16]
	ldrb r7, [r5, #0x17]
	lsl r0, r0, #0x1
	add r0, r1, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	ldrb r0, [r5, #0x9]
	mov r6, #0x0
	cmp r0, #0x0
	bls _0200207C
_02002022:
	ldrb r2, [r5, #0xa]
	mov r4, #0x0
	cmp r2, #0x0
	bls _02002068
_0200202A:
	ldrb r3, [r5, #0xb]
	mul r2, r6
	ldrb r0, [r5, #0x1a]
	lsl r3, r3, #0x1c
	lsr r3, r3, #0x1c
	add r0, r0, r3
	ldrb r1, [r5, #0x18]
	mul r0, r4
	add r2, r4, r2
	add r0, r1, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	ldr r3, [r5, #0x0]
	lsl r2, r2, #0x3
	ldr r2, [r3, r2]
	ldrb r1, [r5, #0x8]
	ldr r0, [r5, #0x4]
	add r3, r7, #0x0
	bl AddTextPrinterParameterized
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	ldrb r2, [r5, #0xa]
	lsr r4, r0, #0x18
	cmp r4, r2
	blo _0200202A
_02002068:
	ldr r0, [sp, #0xc]
	add r0, r7, r0
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldrb r0, [r5, #0x9]
	cmp r6, r0
	blo _02002022
_0200207C:
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start FUN_02002080
FUN_02002080: ; 0x02002080
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	ldrb r1, [r4, #0xb]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1e
	cmp r1, #0x1
	beq _020020AA
	ldrb r3, [r4, #0x15]
	add r1, sp, #0x0
	add r1, #0x1
	add r2, sp, #0x0
	bl FUN_020020B0
	add r3, sp, #0x0
	ldrb r2, [r3, #0x1]
	ldrb r3, [r3, #0x0]
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x4]
	bl ListMenuUpdateCursorObj
_020020AA:
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_020020B0
FUN_020020B0: ; 0x020020B0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r7, r3, #0x0
	ldrb r1, [r5, #0xa]
	add r0, r7, #0x0
	add r6, r2, #0x0
	bl _s32_div_f
	ldrb r2, [r5, #0x19]
	ldrb r1, [r5, #0x16]
	lsl r2, r2, #0x1
	add r1, r1, r2
	mul r1, r0
	strb r1, [r4, #0x0]
	ldrb r1, [r5, #0xa]
	add r0, r7, #0x0
	bl _s32_div_f
	ldrb r2, [r5, #0xb]
	ldrb r3, [r5, #0x1a]
	ldrb r0, [r5, #0x18]
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x1c
	add r2, r3, r2
	mul r2, r1
	add r0, r0, r2
	strb r0, [r6, #0x0]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start CreateYesNoMenu
CreateYesNoMenu: ; 0x020020EC
	push {r3-r7, lr}
	sub sp, #0x20
	ldr r5, [sp, #0x3c]
	str r2, [sp, #0xc]
	add r7, r0, #0x0
	str r1, [sp, #0x8]
	str r3, [sp, #0x10]
	ldr r2, _02002194 ; =0x00000141
	mov r0, #0x1
	mov r1, #0x1a
	add r3, r5, #0x0
	bl NewMsgDataFromNarc
	add r4, r0, #0x0
	mov r0, #0x2
	add r1, r5, #0x0
	bl ListMenuItems_ctor
	add r1, r4, #0x0
	mov r2, #0x29
	mov r3, #0x0
	add r6, r0, #0x0
	bl ListMenuItems_AppendFromMsgData ; YES
	mov r3, #0x2a
	add r2, r3, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	sub r3, #0x2c
	bl ListMenuItems_AppendFromMsgData ; NO
	add r0, r4, #0x0
	bl DestroyMsgData
	add r0, r5, #0x0
	mov r1, #0x1
	str r6, [sp, #0x14]
	bl AllocWindows
	add r1, r0, #0x0
	str r1, [sp, #0x18]
	mov r0, #0x0
	add r3, sp, #0x14
	strb r0, [r3, #0x8]
	mov r0, #0x1
	strb r0, [r3, #0x9]
	mov r0, #0x2
	strb r0, [r3, #0xa]
	ldrb r0, [r3, #0xb]
	mov r2, #0xf
	bic r0, r2
	strb r0, [r3, #0xb]
	ldrb r4, [r3, #0xb]
	mov r0, #0x30
	bic r4, r0
	strb r4, [r3, #0xb]
	ldrb r0, [r3, #0xb]
	bic r0, r2
	strb r0, [r3, #0xb]
	ldr r2, [sp, #0x8]
	add r0, r7, #0x0
	bl FUN_02019150
	ldr r0, [sp, #0x18]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	mov r1, #0x1
	bl FUN_0200CCA4
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	add r3, sp, #0x28
	ldrb r3, [r3, #0x10]
	add r0, sp, #0x14
	mov r1, #0x8
	mov r2, #0x0
	bl FUN_02001C14
	add sp, #0x20
	pop {r3-r7, pc}
	nop
_02002194: .word 0x00000141

	thumb_func_start Std_CreateYesNoMenu
Std_CreateYesNoMenu: ; 0x02002198
	push {r4, lr}
	sub sp, #0x8
	mov r4, #0x0
	str r4, [sp, #0x0]
	ldr r4, [sp, #0x10]
	str r4, [sp, #0x4]
	bl CreateYesNoMenu
	add sp, #0x8
	pop {r4, pc}

	thumb_func_start FUN_020021AC
FUN_020021AC: ; 0x020021AC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02001C78
	add r6, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r6, r0
	beq _020021C8
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020021EC
_020021C8:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020021CC
FUN_020021CC: ; 0x020021CC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02001DDC
	add r6, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r6, r0
	beq _020021E8
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020021EC
_020021E8:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020021EC
FUN_020021EC: ; 0x020021EC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x4]
	add r4, r1, #0x0
	mov r1, #0x0
	bl FUN_0200CCF8
	ldr r0, [r5, #0x4]
	bl FUN_02019178
	ldr r1, [r5, #0x4]
	add r0, r4, #0x0
	bl FreeToHeapExplicit
	ldr r0, [r5, #0x0]
	bl ListMenuItems_dtor
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02001C5C
	pop {r3-r5, pc}

	thumb_func_start FUN_02002218
FUN_02002218: ; 0x02002218
	push {r4, lr}
	sub sp, #0x18
	mov r4, #0x8
	lsl r1, r1, #0x10
	str r4, [sp, #0x0]
	mov r3, #0x10
	str r3, [sp, #0x4]
	lsr r1, r1, #0x10
	str r1, [sp, #0x8]
	lsl r1, r2, #0x10
	lsr r1, r1, #0x10
	str r1, [sp, #0xc]
	str r4, [sp, #0x10]
	ldr r1, _02002244 ; =UNK_020ECAC8
	mov r2, #0x0
	str r3, [sp, #0x14]
	add r3, r2, #0x0
	bl BlitBitmapRectToWindow
	add sp, #0x18
	pop {r4, pc}
	nop
_02002244: .word UNK_020ECAC8
