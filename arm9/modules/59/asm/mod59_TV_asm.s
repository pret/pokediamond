	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD59_021D9C48
MOD59_021D9C48: ; 0x021D9C48
	push {r4, lr}
	add r4, r0, #0
	ldr r2, _021D9C64 ; =0x00000225
	ldr r3, [r4]
	mov r0, #1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	str r0, [r4, #8]
	bl FUN_0201BD5C
	mov r0, #0
	str r0, [r4, #0xc]
	pop {r4, pc}
	.align 2, 0
_021D9C64: .word 0x00000225
	thumb_func_end MOD59_021D9C48

	thumb_func_start MOD59_021D9C68
MOD59_021D9C68: ; 0x021D9C68
	ldr r3, _021D9C70 ; =DestroyMsgData
	ldr r0, [r0, #8]
	bx r3
	nop
_021D9C70: .word DestroyMsgData
	thumb_func_end MOD59_021D9C68

	thumb_func_start MOD59_021D9C74
MOD59_021D9C74: ; 0x021D9C74
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	str r1, [sp, #0x10]
	add r7, r3, #0
	mov r5, #0
	cmp r0, #3
	bhi _021D9D66
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D9C92: ; jump table
	.short _021D9C9A - _021D9C92 - 2 ; case 0
	.short _021D9D24 - _021D9C92 - 2 ; case 1
	.short _021D9D36 - _021D9C92 - 2 ; case 2
	.short _021D9D50 - _021D9C92 - 2 ; case 3
_021D9C9A:
	mov r0, #2
	add r1, r5, #0
	bl ToggleBgLayer
	mov r0, #1
	ldr r1, [r4]
	lsl r0, r0, #0xa
	bl String_ctor
	add r6, r0, #0
	ldr r0, [r4, #8]
	ldr r1, [sp, #0x10]
	add r2, r6, #0
	bl ReadMsgDataIntoString
	add r1, r4, #0
	ldr r0, [r4, #4]
	ldr r2, _021D9D6C ; =0x021DA04C
	add r1, #0x10
	bl AddWindow
	add r1, r5, #0
	mov r0, #1
	lsl r0, r0, #8
	str r0, [sp]
	mov r0, #0xc0
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x10
	add r2, r1, #0
	add r3, r1, #0
	bl FillWindowPixelRect
	add r0, r5, #0
	add r1, r6, #0
	add r2, r0, #0
	bl FUN_02002F08
	mov r1, #1
	lsl r1, r1, #8
	sub r0, r1, r0
	lsr r3, r0, #1
	str r7, [sp]
	add r1, r5, #0
	ldr r0, _021D9D70 ; =0x000F0200
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x10
	add r2, r6, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	add r0, r4, #0
	add r0, #0x10
	bl CopyWindowToVram
	mov r0, #2
	mov r1, #1
	bl ToggleBgLayer
	mov r0, #0xf0
	str r0, [r4, #0x24]
	mov r0, #1
	str r0, [r4, #0xc]
	b _021D9D66
_021D9D24:
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _021D9D30
	sub r0, r0, #1
	str r0, [r4, #0x24]
	b _021D9D66
_021D9D30:
	mov r0, #2
	str r0, [r4, #0xc]
	b _021D9D66
_021D9D36:
	ldr r0, _021D9D74 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	and r0, r1
	cmp r0, #1
	beq _021D9D4A
	mov r0, #2
	and r0, r1
	cmp r0, #2
	bne _021D9D66
_021D9D4A:
	mov r0, #3
	str r0, [r4, #0xc]
	b _021D9D66
_021D9D50:
	add r0, r4, #0
	add r0, #0x10
	bl RemoveWindow
	ldr r0, [r4, #4]
	mov r1, #2
	bl BgClearTilemapBufferAndCommit
	add r0, r5, #0
	str r0, [r4, #0xc]
	mov r5, #1
_021D9D66:
	add r0, r5, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D9D6C: .word MOD59_021DA04C
_021D9D70: .word 0x000F0200
_021D9D74: .word gMain
	thumb_func_end MOD59_021D9C74

	thumb_func_start MOD59_021D9D78
MOD59_021D9D78: ; 0x021D9D78
	push {r3, lr}
	ldr r1, [r0, #0x20]
	mov r2, #3
	add r3, r1, #4
	str r3, [r0, #0x20]
	ldr r0, [r0, #4]
	mov r1, #1
	asr r3, r3, #4
	bl BgSetPosTextAndCommit
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD59_021D9D78

	.rodata

	.global MOD59_021DA04C
MOD59_021DA04C: ; 0x021DA04C
	.byte 0x02, 0x00, 0x00, 0x20, 0x18, 0x01, 0x01, 0x00

	.global MOD59_021DA054
MOD59_021DA054: ; 0x021DA054
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD59_021DA064
MOD59_021DA064: ; 0x021DA064
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x02, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD59_021DA080
MOD59_021DA080: ; 0x021DA080
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD59_021DA09C
MOD59_021DA09C: ; 0x021DA09C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x01, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD59_021DA0B8
MOD59_021DA0B8: ; 0x021DA0B8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x03, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD59_021DA0D4
MOD59_021DA0D4: ; 0x021DA0D4
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
