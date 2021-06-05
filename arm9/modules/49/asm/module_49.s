	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD49_02254854
MOD49_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x7c
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD49_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD49_02254938
	add r1, r4, #0
	mov r2, #1
	bl FUN_0200CA44
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
_02254898: .word MOD49_02254938
	thumb_func_end MOD49_02254854

	thumb_func_start MOD49_0225489C
MOD49_0225489C: ; 0x0225489C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r0, #0
	add r0, r1, #0
	str r1, [sp, #4]
	str r2, [sp, #8]
	bl MOD20_02252C3C
	str r0, [sp, #0xc]
	bl Sav2_Poketch_PokemonHistoryGetFirstEmptySlot
	mov r6, #0
	str r0, [r7, #0x64]
	cmp r0, #0
	bls _022548D8
	add r4, r7, #0
	add r4, #8
	add r5, r7, #4
_022548C0:
	ldr r0, [sp, #0xc]
	add r1, r6, #0
	add r2, r5, #0
	add r3, r4, #0
	bl Sav2_Poketch_PokemonHistoryGetSlotN
	ldr r0, [r7, #0x64]
	add r6, r6, #1
	add r4, #8
	add r5, #8
	cmp r6, r0
	blo _022548C0
_022548D8:
	add r0, r7, #0
	ldr r2, [sp, #8]
	add r0, #0x68
	add r1, r7, #4
	bl MOD49_02254A44
	cmp r0, #0
	beq _02254912
	mov r0, #0
	strb r0, [r7]
	strb r0, [r7, #1]
	strb r0, [r7, #2]
	mov r0, #8
	str r0, [sp]
	ldr r0, _02254918 ; =MOD49_02254CF0
	ldr r2, _0225491C ; =MOD49_0225497C
	mov r1, #0xc
	add r3, r7, #0
	bl MOD20_02254130
	str r0, [r7, #0x70]
	mov r0, #0
	str r0, [r7, #0x74]
	str r0, [r7, #0x78]
	ldr r0, [sp, #4]
	add sp, #0x10
	str r0, [r7, #0x6c]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02254912:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254918: .word MOD49_02254CF0
_0225491C: .word MOD49_0225497C
	thumb_func_end MOD49_0225489C

	thumb_func_start MOD49_02254920
MOD49_02254920: ; 0x02254920
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x70]
	bl MOD20_02254198
	ldr r0, [r4, #0x68]
	bl MOD49_02254A78
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD49_02254920

	thumb_func_start MOD49_02254938
MOD49_02254938: ; 0x02254938
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bhs _0225496E
	ldr r0, [r4, #0x6c]
	ldr r1, [r4, #0x70]
	bl MOD20_02252C14
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _02254970 ; =MOD49_02254CE4
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _0225496E
	add r0, r4, #0
	bl MOD49_02254920
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x6c]
	bl MOD20_022529A0
_0225496E:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254970: .word MOD49_02254CE4
	thumb_func_end MOD49_02254938

	thumb_func_start MOD49_02254974
MOD49_02254974: ; 0x02254974
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD49_02254974

	thumb_func_start MOD49_0225497C
MOD49_0225497C: ; 0x0225497C
	str r0, [r3, #0x78]
	str r1, [r3, #0x74]
	bx lr
	.align 2, 0
	thumb_func_end MOD49_0225497C

	thumb_func_start MOD49_02254984
MOD49_02254984: ; 0x02254984
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _0225498C
	b _0225498E
_0225498C:
	mov r1, #2
_0225498E:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD49_02254984

	thumb_func_start MOD49_02254998
MOD49_02254998: ; 0x02254998
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _022549A8
	cmp r0, #1
	beq _022549B8
	b _022549D2
_022549A8:
	ldr r0, [r4, #0x68]
	mov r1, #0
	bl MOD49_02254A84
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549D2
_022549B8:
	ldr r0, [r4, #0x68]
	mov r1, #0
	bl MOD49_02254AA8
	cmp r0, #0
	beq _022549D2
	ldr r0, [r4, #0x6c]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD49_02254984
_022549D2:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD49_02254998

	thumb_func_start MOD49_022549D8
MOD49_022549D8: ; 0x022549D8
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _022549EC
	mov r1, #2
	bl MOD49_02254984
	mov r0, #0
	pop {r4, pc}
_022549EC:
	ldr r0, [r4, #0x74]
	cmp r0, #1
	bne _02254A0C
	ldr r1, [r4, #0x78]
	mov r0, #0xb
	sub r1, r0, r1
	ldr r0, [r4, #0x64]
	cmp r1, r0
	bhs _02254A08
	lsl r0, r1, #3
	add r0, r4, r0
	ldr r0, [r0, #4]
	bl MOD20_02252B48
_02254A08:
	mov r0, #0
	str r0, [r4, #0x74]
_02254A0C:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD49_022549D8

	thumb_func_start MOD49_02254A10
MOD49_02254A10: ; 0x02254A10
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A20
	cmp r0, #1
	beq _02254A30
	b _02254A3E
_02254A20:
	ldr r0, [r4, #0x68]
	mov r1, #1
	bl MOD49_02254A84
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A3E
_02254A30:
	ldr r0, [r4, #0x68]
	bl MOD49_02254AB4
	cmp r0, #0
	beq _02254A3E
	mov r0, #1
	pop {r4, pc}
_02254A3E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD49_02254A10

	thumb_func_start MOD49_02254A44
MOD49_02254A44: ; 0x02254A44
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x98
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254A72
	add r0, #8
	mov r1, #4
	bl MOD20_022536F4
	str r6, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	bl MOD20_02252D24
	str r0, [r4, #0x20]
	str r4, [r5]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254A72:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD49_02254A44

	thumb_func_start MOD49_02254A78
MOD49_02254A78: ; 0x02254A78
	push {r3, lr}
	cmp r0, #0
	beq _02254A82
	bl FreeToHeap
_02254A82:
	pop {r3, pc}
	thumb_func_end MOD49_02254A78

	thumb_func_start MOD49_02254A84
MOD49_02254A84: ; 0x02254A84
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254AA4 ; =MOD49_02254D3C
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254AA4: .word MOD49_02254D3C
	thumb_func_end MOD49_02254A84

	thumb_func_start MOD49_02254AA8
MOD49_02254AA8: ; 0x02254AA8
	ldr r3, _02254AB0 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254AB0: .word MOD20_02253794
	thumb_func_end MOD49_02254AA8

	thumb_func_start MOD49_02254AB4
MOD49_02254AB4: ; 0x02254AB4
	ldr r3, _02254ABC ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254ABC: .word MOD20_022537B8
	thumb_func_end MOD49_02254AB4

	thumb_func_start MOD49_02254AC0
MOD49_02254AC0: ; 0x02254AC0
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD49_02254AC0

	thumb_func_start MOD49_02254AD4
MOD49_02254AD4: ; 0x02254AD4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r7, r1, #0
	add r0, r7, #0
	bl MOD20_022538A0
	add r5, r0, #0
	add r0, r7, #0
	bl MOD20_022538A4
	str r0, [sp, #0x14]
	ldr r0, [r5, #4]
	ldr r2, _02254BD0 ; =MOD49_02254D20
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	str r0, [sp]
	ldr r0, [r5, #4]
	mov r1, #6
	mov r2, #4
	mov r3, #1
	bl BG_FillCharDataRange
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	ldr r0, [r5, #4]
	mov r1, #6
	add r3, r2, #0
	bl FUN_02018540
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	mov r3, #2
	str r3, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, [r5, #4]
	add r1, sp, #0x1c
	mov r2, #6
	bl AddWindowParameterized
	add r0, sp, #0x1c
	mov r1, #4
	bl FillWindowPixelBuffer
	add r0, sp, #0x1c
	bl PutWindowTilemap
	ldr r1, _02254BD4 ; =0x00000197
	mov r0, #0x1a
	mov r2, #0
	mov r3, #8
	bl ReadMsgData_NewNarc_NewString
	add r4, r0, #0
	beq _02254B94
	mov r0, #0
	add r1, r4, #0
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0
	add r6, r0, #0
	mov r3, #0xc0
	sub r3, r3, r6
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02254BD8 ; =0x00010104
	add r2, r4, #0
	str r0, [sp, #8]
	add r0, sp, #0x1c
	lsr r3, r3, #1
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, sp, #0x1c
	bl FUN_02019548
	add r0, r4, #0
	bl String_dtor
_02254B94:
	add r0, sp, #0x1c
	bl RemoveWindow
	ldr r0, [r5, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r1, [sp, #0x14]
	add r0, r5, #0
	bl MOD49_02254C04
	ldr r1, _02254BDC ; =0x04001000
	ldr r0, _02254BE0 ; =0xFFFFE0FF
	ldr r3, [r1]
	ldr r2, [r1]
	str r3, [sp, #0x18]
	and r0, r2
	lsl r2, r3, #0x13
	lsr r3, r2, #0x1b
	mov r2, #4
	orr r2, r3
	lsl r2, r2, #8
	orr r0, r2
	str r0, [r1]
	add r0, r7, #0
	bl MOD49_02254AC0
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_02254BD0: .word MOD49_02254D20
_02254BD4: .word 0x00000197
_02254BD8: .word 0x00010104
_02254BDC: .word 0x04001000
_02254BE0: .word 0xFFFFE0FF
	thumb_func_end MOD49_02254AD4

	thumb_func_start MOD49_02254BE4
MOD49_02254BE4: ; 0x02254BE4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	bl MOD49_02254CB8
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r5, #0
	bl MOD49_02254AC0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD49_02254BE4

	thumb_func_start MOD49_02254C04
MOD49_02254C04: ; 0x02254C04
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r0, [sp, #4]
	mov r0, #0
	str r1, [sp, #8]
	bl MOD20_022539C4
	mov r0, #8
	str r0, [sp]
	ldr r0, [sp, #4]
	mov r1, #0xc
	add r0, #0x54
	mov r2, #5
	mov r3, #6
	bl MOD20_02253FBC
	ldr r0, [sp, #8]
	mov r4, #0
	ldr r0, [r0, #0x60]
	cmp r0, #0
	bls _02254C86
	ldr r5, [sp, #4]
	ldr r6, [sp, #8]
	add r0, r5, #0
	str r0, [sp, #0x10]
	add r0, #0x54
	ldr r7, _02254CB4 ; =MOD49_02254D60
	str r4, [sp, #0xc]
	str r0, [sp, #0x10]
_02254C3E:
	ldr r0, [r6]
	ldr r2, [r6, #4]
	mov r1, #0
	bl FUN_0206B6D4
	str r0, [r5, #0x68]
	ldr r0, [sp, #4]
	ldr r2, [sp, #0x10]
	ldr r0, [r0, #0x20]
	add r1, r7, #0
	bl MOD20_02253E74
	ldr r1, [sp, #0xc]
	str r0, [r5, #0x24]
	bl MOD20_02253FA4
	ldr r0, [r6]
	ldr r1, [r6, #4]
	mov r2, #0
	bl FUN_0206B7BC
	add r1, r0, #0
	ldr r0, [r5, #0x24]
	bl MOD20_02253F9C
	ldr r0, [sp, #0xc]
	add r4, r4, #1
	add r0, #0x10
	str r0, [sp, #0xc]
	ldr r0, [sp, #8]
	add r6, #8
	ldr r0, [r0, #0x60]
	add r5, r5, #4
	add r7, #0x10
	cmp r4, r0
	blo _02254C3E
_02254C86:
	cmp r4, #0xc
	bge _02254C9C
	ldr r0, [sp, #4]
	lsl r1, r4, #2
	add r1, r0, r1
	mov r0, #0
_02254C92:
	add r4, r4, #1
	str r0, [r1, #0x24]
	add r1, r1, #4
	cmp r4, #0xc
	blt _02254C92
_02254C9C:
	ldr r2, [sp, #8]
	ldr r1, [sp, #4]
	mov r0, #0
	add r1, #0x68
	ldr r2, [r2, #0x60]
	add r3, r0, #0
	str r1, [sp, #4]
	bl MOD20_02253A04
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_02254CB4: .word MOD49_02254D60
	thumb_func_end MOD49_02254C04

	thumb_func_start MOD49_02254CB8
MOD49_02254CB8: ; 0x02254CB8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
	add r7, r4, #0
_02254CC2:
	ldr r1, [r5, #0x24]
	cmp r1, #0
	beq _02254CD0
	ldr r0, [r6, #0x20]
	bl MOD20_02253F14
	str r7, [r5, #0x24]
_02254CD0:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xc
	blt _02254CC2
	add r6, #0x54
	add r0, r6, #0
	bl MOD20_02254014
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD49_02254CB8

	.section .rodata

	.global MOD49_02254CE4
MOD49_02254CE4: ; 0x02254CE4
	.word MOD49_02254998, MOD49_022549D8, MOD49_02254A10

	.global MOD49_02254CF0
MOD49_02254CF0: ; 0x02254CF0
	.byte 0x7E, 0xA2, 0x90, 0xC0
	.byte 0x7E, 0xA2, 0x68, 0x98, 0x7E, 0xA2, 0x40, 0x70, 0x7E, 0xA2, 0x18, 0x48, 0x4E, 0x72, 0x90, 0xC0
	.byte 0x4E, 0x72, 0x68, 0x98, 0x4E, 0x72, 0x40, 0x70, 0x4E, 0x72, 0x18, 0x48, 0x1E, 0x42, 0x90, 0xC0
	.byte 0x1E, 0x42, 0x68, 0x98, 0x1E, 0x42, 0x40, 0x70, 0x1E, 0x42, 0x18, 0x48

	.global MOD49_02254D20
MOD49_02254D20: ; 0x02254D20
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD49_02254D3C
MOD49_02254D3C: ; 0x02254D3C
	.word 0x00, MOD49_02254AD4, 0x00
	.word 0x01, MOD49_02254BE4, 0x00
	.word 0x00, 0x00000000, 0x00

	.global MOD49_02254D60
MOD49_02254D60: ; 0x02254D60
	.byte 0x00, 0x00, 0x03, 0x00
	.byte 0x00, 0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x02, 0x0C, 0x01, 0x00, 0x00, 0x00, 0x80, 0x05, 0x00
	.byte 0x00, 0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x02, 0x0B, 0x01, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00
	.byte 0x00, 0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x02, 0x0A, 0x01, 0x00, 0x00, 0x00, 0x80, 0x0A, 0x00
	.byte 0x00, 0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x02, 0x09, 0x01, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00
	.byte 0x00, 0x00, 0x06, 0x00, 0x04, 0x00, 0x00, 0x02, 0x08, 0x01, 0x00, 0x00, 0x00, 0x80, 0x05, 0x00
	.byte 0x00, 0x00, 0x06, 0x00, 0x04, 0x00, 0x00, 0x02, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00
	.byte 0x00, 0x00, 0x06, 0x00, 0x04, 0x00, 0x00, 0x02, 0x06, 0x01, 0x00, 0x00, 0x00, 0x80, 0x0A, 0x00
	.byte 0x00, 0x00, 0x06, 0x00, 0x04, 0x00, 0x00, 0x02, 0x05, 0x01, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00
	.byte 0x00, 0x00, 0x09, 0x00, 0x04, 0x00, 0x00, 0x02, 0x04, 0x01, 0x00, 0x00, 0x00, 0x80, 0x05, 0x00
	.byte 0x00, 0x00, 0x09, 0x00, 0x04, 0x00, 0x00, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00
	.byte 0x00, 0x00, 0x09, 0x00, 0x04, 0x00, 0x00, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x80, 0x0A, 0x00
	.byte 0x00, 0x00, 0x09, 0x00, 0x04, 0x00, 0x00, 0x02, 0x01, 0x01, 0x00, 0x00
