	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021E5300
ov05_021E5300: ; 0x021E5300
	push {r3, r4, r5, lr}
	mov r1, #0xbe
	mov r2, #0
	lsl r1, r1, #4
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov05_021E532C
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021E531C
ov05_021E531C: ; 0x021E531C
	push {r4, lr}
	add r4, r0, #0
	bl ov05_021E5398
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov05_021E532C
ov05_021E532C: ; 0x021E532C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	ldr r1, _021E5390 ; =0x00000B5C
	str r0, [sp, #8]
	add r6, r0, r1
	sub r1, #0x84
	mov r4, #0
	add r5, r0, r1
	add r7, r0, #4
_021E533E:
	str r5, [sp]
	ldr r0, [sp, #8]
	str r6, [sp, #4]
	add r1, r4, #0
	ldr r0, [r0]
	add r1, #0x1a
	mov r2, #0
	add r3, r7, #0
	bl ov05_021E51EC
	add r4, r4, #1
	add r6, r6, #4
	add r5, r5, #4
	add r7, #0x54
	cmp r4, #0x20
	blt _021E533E
	ldr r2, _021E5394 ; =0x00000AD8
	ldr r1, [sp, #8]
	lsl r0, r4, #2
	add r1, r1, r2
	add r1, r1, r0
	str r1, [sp]
	ldr r1, [sp, #8]
	add r2, #0x84
	add r1, r1, r2
	add r0, r1, r0
	ldr r3, [sp, #8]
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	add r5, r3, #4
	mov r3, #0x54
	mul r3, r4
	ldr r0, [r0]
	mov r1, #0x19
	mov r2, #0
	add r3, r5, r3
	bl ov05_021E51EC
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_021E5390: .word 0x00000B5C
_021E5394: .word 0x00000AD8

	thumb_func_start ov05_021E5398
ov05_021E5398: ; 0x021E5398
	push {r4, r5, r6, lr}
	ldr r6, _021E53B0 ; =0x00000B5C
	add r5, r0, #0
	mov r4, #0
_021E53A0:
	ldr r0, [r5, r6]
	bl ov05_021E4C00
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x21
	blt _021E53A0
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021E53B0: .word 0x00000B5C

	thumb_func_start ov05_021E53B4
ov05_021E53B4: ; 0x021E53B4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r5, r0, #0
	ldr r0, [r5, #0x3c]
	add r4, r1, #0
	mov r1, #3
	add r6, r2, #0
	add r7, r3, #0
	str r0, [sp, #8]
	str r0, [sp, #0x24]
	bl ov05_021E4C08
	str r0, [sp, #0x28]
	mov r0, #9
	mov r3, #0
	lsl r1, r4, #0x10
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0xc]
	lsl r0, r6, #0x10
	str r0, [sp, #0x14]
	str r4, [sp, #0x18]
	str r6, [sp, #0x1c]
	str r5, [sp, #0x20]
	str r3, [sp, #0x10]
	add r0, sp, #0x18
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	ldr r1, _021E541C ; =ov05_021F757C
	add r2, sp, #0xc
	bl ov05_021E4DC4
	add r5, r0, #0
	beq _021E5416
	bl sub_02064738
	add r4, r0, #0
	ldr r0, [sp, #0x40]
	str r0, [r4, #0x54]
	add r0, r7, #0
	bl _fflt
	str r0, [r4, #0x58]
	add r0, r7, #0
	bl _fflt
	str r0, [r4, #0x5c]
_021E5416:
	add r0, r5, #0
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021E541C: .word ov05_021F757C

	thumb_func_start ov05_021E5420
ov05_021E5420: ; 0x021E5420
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	ldr r4, [sp, #0x18]
	add r5, r3, #0
	str r4, [sp]
	bl ov05_021E53B4
	add r6, r0, #0
	beq _021E5444
	bl sub_02064738
	add r4, r0, #0
	mov r0, #0
	str r0, [r4, #0x58]
	add r0, r5, #0
	bl _fflt
	str r0, [r4, #0x5c]
_021E5444:
	add r0, r6, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021E544C
ov05_021E544C: ; 0x021E544C
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	bl sub_0206475C
	add r3, r0, #0
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	add r2, #0x6c
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #0x6c]
	lsl r1, r0, #0x10
	mov r0, #9
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp]
	ldr r0, [r4, #0x70]
	add r1, sp, #0
	lsl r0, r0, #0x10
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #4]
	add r0, r5, #0
	bl sub_0206476C
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021E5490
ov05_021E5490: ; 0x021E5490
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021E5494
ov05_021E5494: ; 0x021E5494
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x5c]
	bl _fls
	bhs _021E54B6
	ldr r0, [r4, #0x58]
	bl _f2d
	ldr r2, _021E54B8 ; =0x9999999A
	ldr r3, _021E54BC ; =0x3FC99999
	bl _dadd
	bl _d2f
	str r0, [r4, #0x58]
_021E54B6:
	pop {r4, pc}
	.balign 4, 0
_021E54B8: .word 0x9999999A
_021E54BC: .word 0x3FC99999

	thumb_func_start ov05_021E54C0
ov05_021E54C0: ; 0x021E54C0
	push {r3, r4, r5, r6, lr}
	sub sp, #0x3c
	ldr r5, _021E555C ; =ov05_021F7570
	add r2, r0, #0
	add r4, r1, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0x24
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	ldr r6, _021E5560 ; =ov05_021F7590
	str r0, [r3]
	add r5, sp, #0
	mov r3, #4
_021E54DA:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r3, r3, #1
	bne _021E54DA
	ldr r0, [r6]
	add r1, sp, #0x30
	str r0, [r5]
	add r0, r2, #0
	bl sub_0206477C
	ldr r0, [sp, #0x24]
	bl _fflt
	ldr r1, [r4, #0x58]
	bl _fmul
	bl _ffix
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x28]
	bl _fflt
	ldr r1, [r4, #0x58]
	bl _fmul
	bl _ffix
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x2c]
	bl _fflt
	ldr r1, [r4, #0x58]
	bl _fmul
	bl _ffix
	str r0, [sp, #0x2c]
	mov r0, #2
	ldr r1, [sp, #0x30]
	lsl r0, r0, #0xa
	sub r1, r1, r0
	str r1, [sp, #0x30]
	ldr r1, [sp, #0x34]
	lsl r0, r0, #1
	sub r0, r1, r0
	str r0, [sp, #0x34]
	mov r0, #5
	ldr r1, [sp, #0x38]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x38]
	ldr r0, [r4, #0x7c]
	ldr r1, [r4, #0x54]
	add r2, r0, #4
	mov r0, #0x54
	mul r0, r1
	add r0, r2, r0
	add r1, sp, #0x30
	add r2, sp, #0
	add r3, sp, #0x24
	bl sub_0201B26C
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
	nop
_021E555C: .word ov05_021F7570
_021E5560: .word ov05_021F7590

	.section .rodata

	.global ov05_021F7570
ov05_021F7570: ; 0x021F7570
	.word 0x00001000, 0x00001000, 0x00001000

	.global ov05_021F757C
ov05_021F757C: ; 0x021F757C
	.word 0x00000080, ov05_021E544C, ov05_021E5490, ov05_021E5494
	.word ov05_021E54C0

	.global ov05_021F7590
ov05_021F7590: ; 0x021F7590
	.word 0x00001000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00001000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00001000
