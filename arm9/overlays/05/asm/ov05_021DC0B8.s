	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021DC0B8
ov05_021DC0B8: ; 0x021DC0B8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #4
	mov r1, #0x18
	bl AllocFromHeap
	add r4, r0, #0
	add r2, r4, #0
	mov r1, #0x18
	mov r0, #0
_021DC0CC:
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _021DC0CC
	add r0, r5, #0
	bl ov05_021DC554
	str r0, [r4]
	mov r1, #0
	str r1, [r4, #4]
	str r1, [r4, #8]
	mov r0, #6
	str r0, [r4, #0xc]
	str r1, [r4, #0x14]
	mov r0, #0x17
	str r0, [r4, #0x10]
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021DC0F8
ov05_021DC0F8: ; 0x021DC0F8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021DC106
	bl sub_0200CAB4
_021DC106:
	add r0, r4, #0
	bl ov05_021DC594
	add r2, r4, #0
	mov r1, #0x18
	mov r0, #0
_021DC112:
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _021DC112
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021DC124
ov05_021DC124: ; 0x021DC124
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	add r4, r1, #0
	cmp r0, #6
	beq _021DC134
	bl GF_AssertFail
_021DC134:
	ldr r2, [r5, #4]
	cmp r2, r4
	beq _021DC170
	ldr r0, [r5]
	mov r1, #8
	bl ov05_021DC608
	cmp r0, #0
	bne _021DC14A
	bl GF_AssertFail
_021DC14A:
	ldr r0, [r5]
	mov r1, #0
	add r2, r4, #0
	bl ov05_021DC608
	cmp r0, #0
	bne _021DC15C
	bl GF_AssertFail
_021DC15C:
	ldr r0, [r5]
	mov r1, #3
	add r2, r4, #0
	bl ov05_021DC608
	cmp r0, #0
	bne _021DC16E
	bl GF_AssertFail
_021DC16E:
	str r4, [r5, #4]
_021DC170:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021DC174
ov05_021DC174: ; 0x021DC174
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	add r4, r1, #0
	cmp r0, #6
	beq _021DC186
	str r4, [r5, #0x10]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DC186:
	ldr r0, [r5, #4]
	cmp r0, r4
	bne _021DC190
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DC190:
	ldr r0, [r5, #0x14]
	cmp r0, #0
	beq _021DC19A
	bl GF_AssertFail
_021DC19A:
	str r4, [r5, #8]
	ldr r0, [r5, #4]
	add r1, r4, #0
	bl ov05_021DC368
	cmp r0, #0
	bne _021DC1B6
	ldr r0, _021DC1C8 ; =ov05_021DC1D4
	mov r2, #0
	add r1, r5, #0
	str r2, [r5, #0xc]
	bl sub_0200CA44
	b _021DC1C2
_021DC1B6:
	ldr r0, _021DC1CC ; =ov05_021DC2A4
	mov r2, #0
	add r1, r5, #0
	str r2, [r5, #0xc]
	bl sub_0200CA44
_021DC1C2:
	str r0, [r5, #0x14]
	mov r0, #1
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021DC1C8: .word ov05_021DC1D4
_021DC1CC: .word ov05_021DC2A4

	thumb_func_start ov05_021DC1D0
ov05_021DC1D0: ; 0x021DC1D0
	ldr r0, [r0, #4]
	bx lr

	thumb_func_start ov05_021DC1D4
ov05_021DC1D4: ; 0x021DC1D4
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4, #0xc]
	cmp r1, #5
	bhi _021DC2A2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021DC1EA: ; jump table
	.short _021DC1F6 - _021DC1EA - 2 ; case 0
	.short _021DC210 - _021DC1EA - 2 ; case 1
	.short _021DC236 - _021DC1EA - 2 ; case 2
	.short _021DC250 - _021DC1EA - 2 ; case 3
	.short _021DC264 - _021DC1EA - 2 ; case 4
	.short _021DC286 - _021DC1EA - 2 ; case 5
_021DC1F6:
	ldr r0, [r4]
	ldr r2, [r4, #4]
	mov r1, #5
	bl ov05_021DC608
	cmp r0, #0
	bne _021DC208
	bl GF_AssertFail
_021DC208:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r4, pc}
_021DC210:
	ldr r0, [r4]
	ldr r1, [r4, #4]
	bl ov05_021DC6C0
	cmp r0, #3
	beq _021DC2A2
	ldr r0, [r4]
	ldr r2, [r4, #4]
	mov r1, #8
	bl ov05_021DC608
	cmp r0, #0
	bne _021DC22E
	bl GF_AssertFail
_021DC22E:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r4, pc}
_021DC236:
	ldr r0, [r4]
	ldr r2, [r4, #8]
	mov r1, #1
	bl ov05_021DC608
	cmp r0, #0
	bne _021DC248
	bl GF_AssertFail
_021DC248:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r4, pc}
_021DC250:
	ldr r0, [r4]
	ldr r1, [r4, #8]
	bl ov05_021DC6C0
	cmp r0, #1
	beq _021DC2A2
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r4, pc}
_021DC264:
	ldr r0, [r4]
	ldr r2, [r4, #8]
	mov r1, #2
	bl ov05_021DC608
	cmp r0, #0
	bne _021DC276
	bl GF_AssertFail
_021DC276:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4, #8]
	str r0, [r4, #4]
	mov r0, #0
	str r0, [r4, #8]
	pop {r4, pc}
_021DC286:
	mov r1, #6
	str r1, [r4, #0xc]
	mov r1, #0
	str r1, [r4, #0x14]
	bl sub_0200CAB4
	ldr r1, [r4, #0x10]
	cmp r1, #0x17
	beq _021DC2A2
	add r0, r4, #0
	bl ov05_021DC174
	mov r0, #0x17
	str r0, [r4, #0x10]
_021DC2A2:
	pop {r4, pc}

	thumb_func_start ov05_021DC2A4
ov05_021DC2A4: ; 0x021DC2A4
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4, #0xc]
	cmp r1, #4
	bhi _021DC366
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021DC2BA: ; jump table
	.short _021DC2C4 - _021DC2BA - 2 ; case 0
	.short _021DC2DE - _021DC2BA - 2 ; case 1
	.short _021DC2F2 - _021DC2BA - 2 ; case 2
	.short _021DC31E - _021DC2BA - 2 ; case 3
	.short _021DC344 - _021DC2BA - 2 ; case 4
_021DC2C4:
	ldr r0, [r4]
	ldr r2, [r4, #8]
	mov r1, #1
	bl ov05_021DC608
	cmp r0, #0
	bne _021DC2D6
	bl GF_AssertFail
_021DC2D6:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r4, pc}
_021DC2DE:
	ldr r0, [r4]
	ldr r1, [r4, #8]
	bl ov05_021DC6C0
	cmp r0, #1
	beq _021DC366
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r4, pc}
_021DC2F2:
	ldr r0, [r4]
	ldr r2, [r4, #4]
	mov r1, #7
	bl ov05_021DC608
	cmp r0, #0
	bne _021DC304
	bl GF_AssertFail
_021DC304:
	ldr r0, [r4]
	ldr r2, [r4, #8]
	mov r1, #4
	bl ov05_021DC608
	cmp r0, #0
	bne _021DC316
	bl GF_AssertFail
_021DC316:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r4, pc}
_021DC31E:
	ldr r0, [r4]
	ldr r1, [r4, #4]
	bl ov05_021DC6C0
	cmp r0, #3
	beq _021DC366
	ldr r0, [r4]
	ldr r2, [r4, #4]
	mov r1, #8
	bl ov05_021DC608
	cmp r0, #0
	bne _021DC33C
	bl GF_AssertFail
_021DC33C:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	pop {r4, pc}
_021DC344:
	ldr r1, [r4, #8]
	mov r2, #0
	str r1, [r4, #4]
	str r2, [r4, #8]
	mov r1, #6
	str r1, [r4, #0xc]
	str r2, [r4, #0x14]
	bl sub_0200CAB4
	ldr r1, [r4, #0x10]
	cmp r1, #0x17
	beq _021DC366
	add r0, r4, #0
	bl ov05_021DC174
	mov r0, #0x17
	str r0, [r4, #0x10]
_021DC366:
	pop {r4, pc}

	thumb_func_start ov05_021DC368
ov05_021DC368: ; 0x021DC368
	mov r2, #0
	cmp r0, #7
	bgt _021DC37E
	cmp r0, #5
	blt _021DC3BC
	beq _021DC384
	cmp r0, #6
	beq _021DC394
	cmp r0, #7
	beq _021DC3AE
	b _021DC3BC
_021DC37E:
	cmp r0, #0x15
	beq _021DC3A4
	b _021DC3BC
_021DC384:
	cmp r1, #6
	beq _021DC390
	cmp r1, #0x15
	beq _021DC390
	cmp r1, #7
	bne _021DC3BC
_021DC390:
	mov r2, #1
	b _021DC3BC
_021DC394:
	cmp r1, #5
	beq _021DC3A0
	cmp r1, #0x15
	beq _021DC3A0
	cmp r1, #7
	bne _021DC3BC
_021DC3A0:
	mov r2, #1
	b _021DC3BC
_021DC3A4:
	sub r0, r1, #5
	cmp r0, #2
	bhi _021DC3BC
	mov r2, #1
	b _021DC3BC
_021DC3AE:
	cmp r1, #5
	beq _021DC3BA
	cmp r1, #0x15
	beq _021DC3BA
	cmp r1, #6
	bne _021DC3BC
_021DC3BA:
	mov r2, #1
_021DC3BC:
	add r0, r2, #0
	bx lr

	thumb_func_start ov05_021DC3C0
ov05_021DC3C0: ; 0x021DC3C0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	ldr r1, _021DC46C ; =0xFFFFF000
	add r6, r0, #0
	add r0, #0x14
	bl sub_0202134C
	mov r0, #0
	add r3, r6, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #0xff
	lsl r0, r0, #0xc
	str r0, [sp, #0x14]
	mov r0, #3
	lsl r0, r0, #0x12
	str r0, [sp, #0x18]
	add r0, r6, #0
	add r0, #0xac
	add r1, sp, #0xc
	mov r2, #1
	add r3, #0x14
	bl sub_02009FD8
	mov r4, #0
	add r5, r6, #0
	mov r7, #0x17
_021DC3F6:
	add r0, r7, #0
	add r1, r4, #0
	mov r2, #4
	bl sub_02008DEC
	add r4, r4, #1
	stmia r5!, {r0}
	cmp r4, #4
	blt _021DC3F6
	bl sub_0200965C
	add r1, r0, #0
	mov r0, #4
	lsl r1, r1, #2
	bl AllocFromHeap
	str r0, [r6, #0x10]
	mov r1, #0
	mov r2, #0x39
	bl ov05_021DC480
	ldr r0, [r6, #0x10]
	mov r1, #1
	mov r2, #0x3a
	bl ov05_021DC480
	ldr r0, [r6, #0x10]
	mov r1, #2
	mov r2, #0x37
	bl ov05_021DC480
	ldr r0, [r6, #0x10]
	mov r1, #3
	mov r2, #0x38
	bl ov05_021DC480
	mov r0, #0x40
	str r0, [sp]
	add r0, r6, #0
	add r0, #0x14
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	add r0, sp, #0
	bl sub_0201FCB0
	add r1, r6, #0
	add r1, #0xf4
	str r0, [r1]
	ldr r0, _021DC470 ; =ov05_021DC474
	add r1, r6, #0
	mov r2, #0xa
	bl sub_0200CA44
	add r6, #0xf8
	str r0, [r6]
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021DC46C: .word 0xFFFFF000
_021DC470: .word ov05_021DC474

	thumb_func_start ov05_021DC474
ov05_021DC474: ; 0x021DC474
	ldr r3, _021DC47C ; =sub_0201FDEC
	add r1, #0xf4
	ldr r0, [r1]
	bx r3
	.balign 4, 0
_021DC47C: .word sub_0201FDEC

	thumb_func_start ov05_021DC480
ov05_021DC480: ; 0x021DC480
	push {r3, r4, r5, lr}
	add r5, r2, #0
	bl sub_02009660
	add r4, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r0, #0x41
	add r1, r5, #0
	mov r2, #0
	mov r3, #4
	bl GfGfxLoader_LoadFromNarc
	add r5, r0, #0
	add r1, r4, #0
	mov r2, #4
	bl sub_02009668
	add r0, r5, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021DC4AC
ov05_021DC4AC: ; 0x021DC4AC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_021DC4B4:
	ldr r0, [r6, #0x10]
	add r1, r4, #0
	bl sub_02009660
	bl sub_020096B4
	ldr r0, [r5]
	bl sub_02008E2C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021DC4B4
	ldr r0, [r6, #0x10]
	bl FreeToHeap
	mov r0, #0
	str r0, [r6, #0x10]
	add r0, r6, #0
	add r0, #0xf4
	ldr r0, [r0]
	bl sub_0201FD58
	add r0, r6, #0
	mov r1, #0
	add r0, #0xf4
	str r1, [r0]
	add r0, r6, #0
	add r0, #0xf8
	ldr r0, [r0]
	bl sub_0200CAB4
	mov r0, #0
	add r6, #0xf8
	str r0, [r6]
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021DC4FC
ov05_021DC4FC: ; 0x021DC4FC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	ldr r1, _021DC54C ; =0x0013F000
	cmp r0, r1
	ble _021DC512
	bl _s32_div_f
	str r1, [r4]
	b _021DC51C
_021DC512:
	ldr r2, _021DC550 ; =0xFFFC0000
	cmp r0, r2
	bge _021DC51C
	add r0, r0, r1
	str r0, [r4]
_021DC51C:
	mov r1, #1
	ldr r3, [r4, #4]
	lsl r1, r1, #0x14
	cmp r3, r1
	ble _021DC536
	lsr r2, r3, #0x1f
	lsl r1, r3, #0xc
	sub r1, r1, r2
	mov r0, #0xc
	ror r1, r0
	add r0, r2, r1
	str r0, [r4, #4]
	b _021DC540
_021DC536:
	ldr r0, _021DC550 ; =0xFFFC0000
	cmp r3, r0
	bge _021DC540
	add r0, r3, r1
	str r0, [r4, #4]
_021DC540:
	add r0, r5, #0
	add r1, r4, #0
	bl sub_02020044
	pop {r3, r4, r5, pc}
	nop
_021DC54C: .word 0x0013F000
_021DC550: .word 0xFFFC0000

	thumb_func_start ov05_021DC554
ov05_021DC554: ; 0x021DC554
	push {r3, r4, r5, lr}
	mov r1, #0x43
	add r5, r0, #0
	mov r0, #4
	lsl r1, r1, #2
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0x41
	lsl r0, r0, #2
	str r5, [r4, r0]
	add r0, r4, #0
	add r0, #8
	bl ov05_021DC3C0
	ldr r0, _021DC58C ; =ov05_021FD2D4
	mov r1, #4
	str r0, [r4]
	ldr r0, _021DC590 ; =ov05_021F689C
	str r0, [r4, #4]
	mov r0, #0x41
	bl NARC_New
	mov r1, #0x42
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021DC58C: .word ov05_021FD2D4
_021DC590: .word ov05_021F689C

	thumb_func_start ov05_021DC594
ov05_021DC594: ; 0x021DC594
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021DC5FE
	mov r5, #0
_021DC5A2:
	ldr r0, [r4]
	add r1, r5, #0
	bl ov05_021DCA94
	add r5, r5, #1
	cmp r5, #0x17
	blt _021DC5A2
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	mov r0, #0x41
	ldr r1, [r4]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	ldr r0, [r0, #0x44]
	add r3, r2, #0
	bl ov05_021DBA40
	ldr r1, _021DC604 ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #1
	orr r0, r2
	strh r0, [r1]
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, [r4]
	add r0, #8
	bl ov05_021DC4AC
	mov r0, #0x42
	ldr r1, [r4]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl NARC_Delete
	ldr r1, [r4]
	mov r0, #4
	bl FreeToHeapExplicit
	mov r0, #0
	str r0, [r4]
_021DC5FE:
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_021DC604: .word 0x04000008

	thumb_func_start ov05_021DC608
ov05_021DC608: ; 0x021DC608
	push {r4, r5, r6, lr}
	add r4, r2, #0
	add r6, r0, #0
	mov r5, #1
	cmp r4, #0x17
	ble _021DC618
	mov r0, #0
	pop {r4, r5, r6, pc}
_021DC618:
	cmp r1, #8
	bhi _021DC6BC
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021DC628: ; jump table
	.short _021DC63A - _021DC628 - 2 ; case 0
	.short _021DC644 - _021DC628 - 2 ; case 1
	.short _021DC64E - _021DC628 - 2 ; case 2
	.short _021DC65C - _021DC628 - 2 ; case 3
	.short _021DC66A - _021DC628 - 2 ; case 4
	.short _021DC69A - _021DC628 - 2 ; case 5
	.short _021DC6A4 - _021DC628 - 2 ; case 6
	.short _021DC6AC - _021DC628 - 2 ; case 7
	.short _021DC6B6 - _021DC628 - 2 ; case 8
_021DC63A:
	add r1, r4, #0
	bl ov05_021DC8BC
	add r5, r0, #0
	b _021DC6BC
_021DC644:
	add r1, r4, #0
	bl ov05_021DC90C
	add r5, r0, #0
	b _021DC6BC
_021DC64E:
	add r1, r4, #0
	mov r2, #0
	add r3, r5, #0
	bl ov05_021DC948
	add r5, r0, #0
	b _021DC6BC
_021DC65C:
	add r1, r4, #0
	mov r2, #2
	add r3, r5, #0
	bl ov05_021DC948
	add r5, r0, #0
	b _021DC6BC
_021DC66A:
	mov r0, #0x41
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	ldr r0, [r0, #0x44]
	bl ov05_021DBA30
	cmp r0, #1
	bne _021DC68A
	add r0, r6, #0
	add r1, r4, #0
	mov r2, #0
	mov r3, #2
	bl ov05_021DC948
	add r5, r0, #0
	b _021DC6BC
_021DC68A:
	add r0, r6, #0
	add r1, r4, #0
	mov r2, #0
	add r3, r5, #0
	bl ov05_021DC948
	add r5, r0, #0
	b _021DC6BC
_021DC69A:
	add r1, r4, #0
	add r2, r5, #0
	bl ov05_021DCA44
	b _021DC6BC
_021DC6A4:
	add r1, r4, #0
	bl ov05_021DCA6C
	b _021DC6BC
_021DC6AC:
	add r1, r4, #0
	mov r2, #0
	bl ov05_021DCA44
	b _021DC6BC
_021DC6B6:
	add r1, r4, #0
	bl ov05_021DCA94
_021DC6BC:
	add r0, r5, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021DC6C0
ov05_021DC6C0: ; 0x021DC6C0
	cmp r1, #0x17
	blt _021DC6C8
	mov r0, #0
	bx lr
_021DC6C8:
	ldr r2, [r0]
	mov r0, #0x24
	mul r0, r1
	add r0, r2, r0
	ldr r0, [r0, #0x14]
	bx lr

	thumb_func_start ov05_021DC6D4
ov05_021DC6D4: ; 0x021DC6D4
	push {r3, lr}
	add r3, r0, #0
	str r1, [sp]
	ldr r0, _021DC6E8 ; =0x04000050
	mov r1, #4
	mov r2, #0x21
	bl G2x_SetBlendAlpha_
	pop {r3, pc}
	nop
_021DC6E8: .word 0x04000050

	thumb_func_start ov05_021DC6EC
ov05_021DC6EC: ; 0x021DC6EC
	str r1, [r0]
	str r1, [r0, #4]
	sub r1, r2, r1
	str r1, [r0, #8]
	str r3, [r0, #0x10]
	mov r1, #0
	str r1, [r0, #0xc]
	bx lr

	thumb_func_start ov05_021DC6FC
ov05_021DC6FC: ; 0x021DC6FC
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #8]
	ldr r0, [r4, #0xc]
	mul r0, r1
	ldr r1, [r4, #0x10]
	bl _s32_div_f
	ldr r1, [r4, #4]
	add r0, r0, r1
	str r0, [r4]
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	add r0, r0, #1
	cmp r0, r1
	bgt _021DC722
	str r0, [r4, #0xc]
	mov r0, #0
	pop {r4, pc}
_021DC722:
	str r1, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}

	thumb_func_start ov05_021DC728
ov05_021DC728: ; 0x021DC728
	str r1, [r0]
	str r1, [r0, #4]
	sub r1, r2, r1
	str r1, [r0, #8]
	strh r3, [r0, #0xe]
	mov r1, #0
	strh r1, [r0, #0xc]
	bx lr

	thumb_func_start ov05_021DC738
ov05_021DC738: ; 0x021DC738
	push {r4, lr}
	add r4, r0, #0
	mov r2, #0xc
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #8]
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r0, r0, r2
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	mov r1, #0xe
	ldrsh r1, [r4, r1]
	bl FX_Div
	ldr r1, [r4, #4]
	add r0, r0, r1
	str r0, [r4]
	mov r0, #0xe
	ldrsh r1, [r4, r0]
	mov r0, #0xc
	ldrsh r0, [r4, r0]
	add r0, r0, #1
	cmp r0, r1
	bgt _021DC77C
	strh r0, [r4, #0xc]
	mov r0, #0
	pop {r4, pc}
_021DC77C:
	strh r1, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021DC784
ov05_021DC784: ; 0x021DC784
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	bl ov05_021DCDA0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov05_021DCDD0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov05_021DCE00
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov05_021DCE3C
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021DC7B0
ov05_021DC7B0: ; 0x021DC7B0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r4, r2, #0
	add r6, r1, #0
	add r7, r3, #0
	ldr r5, [sp, #0x40]
	bl sub_02009660
	str r0, [sp, #0x18]
	add r1, r4, #0
	bl sub_02009710
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r1, r4, #0
	bl sub_0200973C
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x18]
	add r1, r4, #0
	bl sub_02009768
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x18]
	add r1, r4, #0
	bl sub_0200979C
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x18]
	add r1, r4, #0
	bl sub_020096DC
	cmp r6, #3
	bhi _021DC87A
	add r1, r6, r6
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021DC800: ; jump table
	.short _021DC808 - _021DC800 - 2 ; case 0
	.short _021DC826 - _021DC800 - 2 ; case 1
	.short _021DC848 - _021DC800 - 2 ; case 2
	.short _021DC862 - _021DC800 - 2 ; case 3
_021DC808:
	str r0, [sp]
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x1c]
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r0, [sp, #0x44]
	ldr r3, [sp, #0x20]
	str r0, [sp, #0xc]
	add r0, r7, #0
	add r1, r5, #0
	bl sub_0200923C
	str r0, [sp, #0x14]
	b _021DC87A
_021DC826:
	str r0, [sp]
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x1c]
	str r0, [sp, #4]
	ldr r0, [sp, #0x28]
	ldr r3, [sp, #0x20]
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x44]
	add r1, r5, #0
	str r0, [sp, #0x10]
	add r0, r7, #0
	bl sub_020092F8
	str r0, [sp, #0x14]
	b _021DC87A
_021DC848:
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r2, [sp, #0x1c]
	ldr r3, [sp, #0x20]
	add r0, r7, #0
	add r1, r5, #0
	bl sub_02009358
	str r0, [sp, #0x14]
	b _021DC87A
_021DC862:
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r2, [sp, #0x1c]
	ldr r3, [sp, #0x20]
	add r0, r7, #0
	add r1, r5, #0
	bl sub_02009358
	str r0, [sp, #0x14]
_021DC87A:
	ldr r0, [sp, #0x14]
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov05_021DC880
ov05_021DC880: ; 0x021DC880
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0
	mvn r0, r0
	add r4, r2, #0
	cmp r1, r0
	beq _021DC8BA
	ldr r0, [r4]
	cmp r0, #0
	beq _021DC898
	bl sub_02009C0C
_021DC898:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021DC8A2
	bl sub_02009E04
_021DC8A2:
	mov r6, #0
_021DC8A4:
	ldr r1, [r4]
	cmp r1, #0
	beq _021DC8B0
	ldr r0, [r5, #8]
	bl sub_02009490
_021DC8B0:
	add r6, r6, #1
	add r4, r4, #4
	add r5, r5, #4
	cmp r6, #4
	blt _021DC8A4
_021DC8BA:
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021DC8BC
ov05_021DC8BC: ; 0x021DC8BC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r2, #0x24
	ldr r3, [r5]
	mul r2, r1
	add r4, r3, r2
	ldr r1, [r4, #0xc]
	cmp r1, #0
	bne _021DC906
	add r1, r4, #0
	bl ov05_021DCD04
	cmp r0, #0
	bne _021DC8DC
	mov r0, #0
	pop {r3, r4, r5, pc}
_021DC8DC:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021DCBFC
	cmp r0, #0
	bne _021DC8F4
	ldr r0, [r4, #0xc]
	bl FreeToHeap
	mov r0, #0
	str r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_021DC8F4:
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0xc]
	str r1, [r0, #8]
	ldr r1, [r4, #4]
	add r0, r5, #0
	bl ov05_021DCBE0
	mov r0, #2
	str r0, [r4, #0x14]
_021DC906:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021DC90C
ov05_021DC90C: ; 0x021DC90C
	push {r4, lr}
	mov r2, #0x24
	ldr r3, [r0]
	mul r2, r1
	add r4, r3, r2
	ldr r1, [r4, #0xc]
	cmp r1, #0
	beq _021DC920
	mov r0, #1
	pop {r4, pc}
_021DC920:
	add r1, r4, #0
	bl ov05_021DCD04
	cmp r0, #0
	bne _021DC92E
	mov r0, #0
	pop {r4, pc}
_021DC92E:
	ldr r0, _021DC944 ; =ov05_021DCC38
	add r1, r4, #0
	mov r2, #1
	bl sub_0200CA44
	str r0, [r4, #0x1c]
	mov r0, #1
	str r0, [r4, #0x14]
	mov r1, #0
	str r1, [r4, #0x18]
	pop {r4, pc}
	.balign 4, 0
_021DC944: .word ov05_021DCC38

	thumb_func_start ov05_021DC948
ov05_021DC948: ; 0x021DC948
	push {r4, r5, r6, lr}
	add r5, r2, #0
	add r6, r3, #0
	ldr r3, [r0]
	mov r0, #0x24
	add r2, r1, #0
	mul r2, r0
	ldr r1, [r3, r2]
	sub r0, #0x25
	add r4, r3, r2
	cmp r1, r0
	beq _021DC96A
	ldr r0, [r4, #0x10]
	cmp r0, #0
	bne _021DC96A
	mov r0, #0
	pop {r4, r5, r6, pc}
_021DC96A:
	ldr r1, [r4, #0xc]
	cmp r1, #0
	bne _021DC974
	mov r0, #0
	pop {r4, r5, r6, pc}
_021DC974:
	ldr r0, [r4, #0x14]
	cmp r0, #2
	beq _021DC97E
	mov r0, #0
	pop {r4, r5, r6, pc}
_021DC97E:
	ldr r0, [r4, #0x20]
	mov r2, #4
	bl sub_0200CA44
	ldr r1, [r4, #0xc]
	ldr r3, _021DCA34 ; =0x00000F48
	str r0, [r1, r3]
	ldr r0, [r4, #0xc]
	ldr r0, [r0, r3]
	cmp r0, #0
	bne _021DC998
	mov r0, #0
	pop {r4, r5, r6, pc}
_021DC998:
	mov r0, #3
	str r0, [r4, #0x14]
	add r0, r3, #0
	ldr r1, [r4, #0xc]
	add r0, #0x1a
	strh r5, [r1, r0]
	add r0, r3, #0
	ldr r1, [r4, #0xc]
	mov r2, #0
	add r0, #0x1e
	strh r2, [r1, r0]
	ldr r1, [r4, #0xc]
	add r0, r1, #0
	add r0, #0xc
	str r0, [r1, #0x40]
	ldr r1, [r4, #0xc]
	add r0, r1, #0
	add r0, #0xc
	str r0, [r1, #0x44]
	add r0, r3, #0
	ldr r1, [r4, #0xc]
	add r0, #0x1c
	strh r6, [r1, r0]
	add r0, r3, #0
	ldr r1, [r4, #0xc]
	add r0, #0x14
	str r2, [r1, r0]
	ldr r1, [r4, #0xc]
	add r0, r3, #4
	ldr r6, _021DCA38 ; =NNS_G3dGlb + 0x258
	add r5, r1, r0
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	str r0, [r5]
	ldr r1, [r4, #8]
	cmp r1, #0
	ble _021DC9FE
	mov r0, #4
	bl AllocFromHeap
	ldr r2, [r4, #0xc]
	ldr r1, _021DCA3C ; =0x00000F58
	str r0, [r2, r1]
	ldr r0, [r4, #0xc]
	ldr r2, [r4, #8]
	ldr r0, [r0, r1]
	mov r1, #0
	bl memset
	b _021DCA04
_021DC9FE:
	ldr r0, [r4, #0xc]
	add r3, #0x10
	str r2, [r0, r3]
_021DCA04:
	mov r0, #0
	ldr r1, [r4, #4]
	mvn r0, r0
	cmp r1, r0
	beq _021DCA30
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r2, _021DCA40 ; =0x0400000C
	mov r1, #3
	ldrh r3, [r2]
	mov r0, #1
	bic r3, r1
	orr r0, r3
	strh r0, [r2]
	sub r2, r2, #4
	ldrh r3, [r2]
	mov r0, #2
	bic r3, r1
	orr r0, r3
	strh r0, [r2]
_021DCA30:
	mov r0, #1
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021DCA34: .word 0x00000F48
_021DCA38: .word NNS_G3dGlb + 0x258
_021DCA3C: .word 0x00000F58
_021DCA40: .word 0x0400000C

	thumb_func_start ov05_021DCA44
ov05_021DCA44: ; 0x021DCA44
	push {r3, r4}
	ldr r3, [r0]
	mov r0, #0x24
	mul r0, r1
	add r4, r3, r0
	ldr r0, [r4, #0x14]
	cmp r0, #3
	bne _021DCA62
	ldr r1, [r4, #0xc]
	ldr r0, _021DCA68 ; =0x00000F66
	mov r3, #5
	strh r3, [r1, r0]
	ldr r1, [r4, #0xc]
	sub r0, r0, #2
	strh r2, [r1, r0]
_021DCA62:
	pop {r3, r4}
	bx lr
	nop
_021DCA68: .word 0x00000F66

	thumb_func_start ov05_021DCA6C
ov05_021DCA6C: ; 0x021DCA6C
	push {r4, lr}
	mov r2, #0x24
	ldr r3, [r0]
	mul r2, r1
	add r4, r3, r2
	bl ov05_021DC6C0
	cmp r0, #3
	bne _021DCA8E
	ldr r1, [r4, #0xc]
	ldr r0, _021DCA90 ; =0x00000F62
	mov r2, #5
	strh r2, [r1, r0]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x20]
	mov r0, #0
	blx r2
_021DCA8E:
	pop {r4, pc}
	.balign 4, 0
_021DCA90: .word 0x00000F62

	thumb_func_start ov05_021DCA94
ov05_021DCA94: ; 0x021DCA94
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r3, [r5]
	mov r0, #0x24
	add r2, r1, #0
	mul r2, r0
	add r4, r3, r2
	ldr r1, [r4, #4]
	sub r0, #0x25
	cmp r1, r0
	beq _021DCAD2
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, _021DCB5C ; =0x0400000C
	mov r2, #3
	ldrh r3, [r0]
	mov r1, #3
	bic r3, r2
	orr r1, r3
	strh r1, [r0]
	sub r3, r0, #4
	ldrh r6, [r3]
	mov r1, #1
	add r0, #0x44
	bic r6, r2
	orr r1, r6
	strh r1, [r3]
	mov r1, #0
	strh r1, [r0]
_021DCAD2:
	ldr r2, [r4, #0x10]
	cmp r2, #0
	beq _021DCAFA
	ldr r1, [r4]
	add r0, r5, #0
	bl ov05_021DC880
	ldr r1, [r4, #0x10]
	mov r0, #4
	bl FreeToHeapExplicit
	mov r0, #0
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _021DCAFA
	bl sub_0200CAB4
	mov r0, #0
	str r0, [r4, #0x1c]
_021DCAFA:
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021DCB58
	add r0, #0xc
	bl ov05_021DD130
	ldr r0, [r4, #0xc]
	ldr r1, _021DCB60 ; =0x00000F5C
	ldr r1, [r0, r1]
	cmp r1, #1
	bne _021DCB14
	bl ov05_021E0FD0
_021DCB14:
	ldr r1, [r4, #0xc]
	ldr r0, _021DCB64 ; =0x00000F58
	ldr r1, [r1, r0]
	cmp r1, #0
	beq _021DCB2C
	mov r0, #4
	bl FreeToHeapExplicit
	ldr r1, [r4, #0xc]
	ldr r0, _021DCB64 ; =0x00000F58
	mov r2, #0
	str r2, [r1, r0]
_021DCB2C:
	ldr r0, [r4, #0x14]
	cmp r0, #1
	bne _021DCB3E
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _021DCB4C
	bl sub_0200CAB4
	b _021DCB4C
_021DCB3E:
	cmp r0, #3
	bne _021DCB4C
	ldr r1, [r4, #0xc]
	ldr r0, _021DCB68 ; =0x00000F48
	ldr r0, [r1, r0]
	bl sub_0200CAB4
_021DCB4C:
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	mov r0, #0
	str r0, [r4, #0xc]
_021DCB58:
	pop {r4, r5, r6, pc}
	nop
_021DCB5C: .word 0x0400000C
_021DCB60: .word 0x00000F5C
_021DCB64: .word 0x00000F58
_021DCB68: .word 0x00000F48

	thumb_func_start ov05_021DCB6C
ov05_021DCB6C: ; 0x021DCB6C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	mov r0, #0
	ldr r1, [r4, #4]
	mvn r0, r0
	cmp r1, r0
	beq _021DCBA2
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, _021DCBD4 ; =0x0400000C
	mov r2, #3
	ldrh r3, [r0]
	mov r1, #3
	bic r3, r2
	orr r1, r3
	strh r1, [r0]
	sub r3, r0, #4
	ldrh r5, [r3]
	mov r1, #1
	add r0, #0x44
	bic r5, r2
	orr r1, r5
	strh r1, [r3]
	mov r1, #0
	strh r1, [r0]
_021DCBA2:
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021DCBD0
	add r0, #0xc
	bl ov05_021DD130
	ldr r0, [r4, #0xc]
	ldr r1, _021DCBD8 ; =0x00000F5C
	ldr r1, [r0, r1]
	cmp r1, #1
	bne _021DCBBC
	bl ov05_021E0FD0
_021DCBBC:
	ldr r0, [r4, #0x14]
	cmp r0, #3
	bne _021DCBD0
	ldr r1, [r4, #0xc]
	ldr r0, _021DCBDC ; =0x00000F48
	ldr r0, [r1, r0]
	bl sub_0200CAB4
	mov r0, #2
	str r0, [r4, #0x14]
_021DCBD0:
	pop {r3, r4, r5, pc}
	nop
_021DCBD4: .word 0x0400000C
_021DCBD8: .word 0x00000F5C
_021DCBDC: .word 0x00000F48

	thumb_func_start ov05_021DCBE0
ov05_021DCBE0: ; 0x021DCBE0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021DCECC
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021DCF14
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021DCF68
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021DCBFC
ov05_021DCBFC: ; 0x021DCBFC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	mov r0, #0
	ldr r1, [r4]
	mvn r0, r0
	cmp r1, r0
	beq _021DCC32
	ldr r0, [r4, #0x10]
	cmp r0, #0
	bne _021DCC32
	add r0, r4, #0
	bl ov05_021DCD68
	cmp r0, #0
	bne _021DCC20
	mov r0, #0
	pop {r3, r4, r5, pc}
_021DCC20:
	ldr r1, [r4]
	ldr r2, [r4, #0x10]
	add r0, r5, #0
	bl ov05_021DC784
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021DCE74
_021DCC32:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021DCC38
ov05_021DCC38: ; 0x021DCC38
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	ldr r2, [r4, #0x18]
	ldr r0, [r0]
	cmp r2, #8
	bhi _021DCD00
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021DCC54: ; jump table
	.short _021DCC66 - _021DCC54 - 2 ; case 0
	.short _021DCC7C - _021DCC54 - 2 ; case 1
	.short _021DCC8C - _021DCC54 - 2 ; case 2
	.short _021DCC9A - _021DCC54 - 2 ; case 3
	.short _021DCCAA - _021DCC54 - 2 ; case 4
	.short _021DCCB8 - _021DCC54 - 2 ; case 5
	.short _021DCCC8 - _021DCC54 - 2 ; case 6
	.short _021DCCD6 - _021DCC54 - 2 ; case 7
	.short _021DCCE6 - _021DCC54 - 2 ; case 8
_021DCC66:
	add r0, r4, #0
	bl ov05_021DCD68
	cmp r0, #0
	bne _021DCC74
	bl GF_AssertFail
_021DCC74:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	pop {r3, r4, r5, pc}
_021DCC7C:
	ldr r1, [r4]
	ldr r2, [r4, #0x10]
	bl ov05_021DCDA0
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	pop {r3, r4, r5, pc}
_021DCC8C:
	ldr r1, [r4, #4]
	bl ov05_021DCECC
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	pop {r3, r4, r5, pc}
_021DCC9A:
	ldr r1, [r4]
	ldr r2, [r4, #0x10]
	bl ov05_021DCDD0
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	pop {r3, r4, r5, pc}
_021DCCAA:
	ldr r1, [r4, #4]
	bl ov05_021DCF14
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	pop {r3, r4, r5, pc}
_021DCCB8:
	ldr r1, [r4]
	ldr r2, [r4, #0x10]
	bl ov05_021DCE00
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	pop {r3, r4, r5, pc}
_021DCCC8:
	ldr r1, [r4, #4]
	bl ov05_021DCF68
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	pop {r3, r4, r5, pc}
_021DCCD6:
	ldr r1, [r4]
	ldr r2, [r4, #0x10]
	bl ov05_021DCE3C
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	pop {r3, r4, r5, pc}
_021DCCE6:
	bl ov05_021DCE74
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0xc]
	str r1, [r0, #8]
	mov r0, #2
	str r0, [r4, #0x14]
	mov r0, #0
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	add r0, r5, #0
	bl sub_0200CAB4
_021DCD00:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021DCD04
ov05_021DCD04: ; 0x021DCD04
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021DCD14
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DCD14:
	ldr r1, _021DCD60 ; =0x00000F68
	mov r0, #4
	bl AllocFromHeap
	str r0, [r4, #0xc]
	cmp r0, #0
	bne _021DCD26
	mov r0, #0
	pop {r3, r4, r5, pc}
_021DCD26:
	ldr r2, _021DCD60 ; =0x00000F68
	mov r1, #0
	bl memset
	ldr r0, [r4, #0xc]
	ldr r2, _021DCD64 ; =0x00000F62
	str r5, [r0]
	ldr r1, [r4, #0xc]
	mov r0, #0
	strh r0, [r1, r2]
	add r1, r2, #4
	ldr r3, [r4, #0xc]
	sub r2, #0xa
	strh r0, [r3, r1]
	ldr r3, [r4, #0xc]
	add r1, r3, #0
	add r1, #0xc
	str r1, [r3, #0x40]
	ldr r3, [r4, #0xc]
	add r1, r3, #0
	add r1, #0xc
	str r1, [r3, #0x44]
	ldr r1, [r4, #0xc]
	str r0, [r1, r2]
	ldr r0, [r4, #0xc]
	str r4, [r0, #4]
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_021DCD60: .word 0x00000F68
_021DCD64: .word 0x00000F62

	thumb_func_start ov05_021DCD68
ov05_021DCD68: ; 0x021DCD68
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	ldr r1, [r4]
	mvn r0, r0
	cmp r1, r0
	beq _021DCD9A
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _021DCD80
	mov r0, #1
	pop {r4, pc}
_021DCD80:
	mov r0, #4
	mov r1, #0x64
	bl AllocFromHeap
	str r0, [r4, #0x10]
	cmp r0, #0
	bne _021DCD92
	mov r0, #0
	pop {r4, pc}
_021DCD92:
	mov r1, #0
	mov r2, #0x64
	bl memset
_021DCD9A:
	mov r0, #1
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021DCDA0
ov05_021DCDA0: ; 0x021DCDA0
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0
	add r3, r1, #0
	mvn r0, r0
	add r4, r2, #0
	cmp r3, r0
	beq _021DCDCC
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r2, r3, #0
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, [r5, #0x18]
	ldr r3, [r5, #0x10]
	mov r1, #2
	bl ov05_021DC7B0
	str r0, [r4, #8]
_021DCDCC:
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021DCDD0
ov05_021DCDD0: ; 0x021DCDD0
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0
	add r3, r1, #0
	mvn r0, r0
	add r4, r2, #0
	cmp r3, r0
	beq _021DCDFC
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r2, r3, #0
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, [r5, #0x18]
	ldr r3, [r5, #0x14]
	mov r1, #3
	bl ov05_021DC7B0
	str r0, [r4, #0xc]
_021DCDFC:
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021DCE00
ov05_021DCE00: ; 0x021DCE00
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0
	add r3, r1, #0
	mvn r0, r0
	add r4, r2, #0
	cmp r3, r0
	beq _021DCE36
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r2, r3, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5, #0x18]
	ldr r3, [r5, #8]
	mov r1, #0
	bl ov05_021DC7B0
	str r0, [r4]
	bl sub_02009B04
	ldr r0, [r4]
	bl sub_02009474
_021DCE36:
	add sp, #8
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021DCE3C
ov05_021DCE3C: ; 0x021DCE3C
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0
	add r3, r1, #0
	mvn r0, r0
	add r4, r2, #0
	cmp r3, r0
	beq _021DCE70
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	add r2, r3, #0
	ldr r0, [r5, #0x18]
	ldr r3, [r5, #0xc]
	bl ov05_021DC7B0
	str r0, [r4, #4]
	bl sub_02009D68
	ldr r0, [r4, #4]
	bl sub_02009474
_021DCE70:
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021DCE74
ov05_021DCE74: ; 0x021DCE74
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	mov r0, #0
	ldr r1, [r4]
	mvn r0, r0
	cmp r1, r0
	beq _021DCEC8
	ldr r2, [r4, #0x10]
	mov r0, #1
	str r0, [sp]
	add r0, r2, #0
	add r0, #0x40
	add r1, r5, #0
	mov r3, #0
	bl ov05_021DD0A4
	ldr r0, [r4, #0x10]
	mov r1, #0
	add r0, #0x10
	mov r2, #0x30
	bl memset
	add r5, #0xfc
	ldr r1, [r5]
	ldr r0, [r4, #0x10]
	str r1, [r0, #0x10]
	ldr r1, [r4, #0x10]
	add r0, r1, #0
	add r0, #0x40
	str r0, [r1, #0x14]
	mov r1, #1
	ldr r0, [r4, #0x10]
	lsl r1, r1, #0xc
	str r1, [r0, #0x24]
	ldr r0, [r4, #0x10]
	str r1, [r0, #0x28]
	ldr r0, [r4, #0x10]
	str r1, [r0, #0x2c]
	ldr r0, [r4, #0x10]
	mov r1, #1
	str r1, [r0, #0x38]
_021DCEC8:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021DCECC
ov05_021DCECC: ; 0x021DCECC
	push {r3, lr}
	sub sp, #0x18
	add r2, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	beq _021DCF0E
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r0, [r2, r0]
	ldr r3, [r2, #4]
	mov r2, #0xc
	mul r2, r1
	ldr r1, [r3, r2]
	mov r2, #4
	bl NARC_AllocAndReadWholeMember
	add r1, sp, #0x14
	str r0, [sp]
	bl NNS_G2dGetUnpackedPaletteData
	ldr r1, [sp, #0x14]
	mov r0, #2
	ldr r1, [r1, #0xc]
	mov r2, #0x20
	mov r3, #0xc0
	bl BG_LoadPlttData
	ldr r0, [sp]
	bl FreeToHeap
	mov r0, #0
	str r0, [sp]
_021DCF0E:
	add sp, #0x18
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021DCF14
ov05_021DCF14: ; 0x021DCF14
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	beq _021DCF62
	mov r2, #0xc
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r3, [r4, #4]
	mul r2, r1
	add r1, r3, r2
	ldr r0, [r4, r0]
	ldr r1, [r1, #4]
	mov r2, #4
	bl NARC_AllocAndReadWholeMember
	add r1, sp, #0x14
	str r0, [sp, #8]
	bl NNS_G2dGetUnpackedCharacterData
	ldr r3, [sp, #0x14]
	mov r0, #0
	str r0, [sp]
	mov r0, #0x41
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r2, [r3, #0x14]
	ldr r0, [r0, #8]
	ldr r3, [r3, #0x10]
	mov r1, #2
	bl BG_LoadCharTilesData
	ldr r0, [sp, #8]
	bl FreeToHeap
	mov r0, #0
	str r0, [sp, #8]
_021DCF62:
	add sp, #0x1c
	pop {r3, r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021DCF68
ov05_021DCF68: ; 0x021DCF68
	push {r4, r5, lr}
	sub sp, #0x24
	add r4, r0, #0
	mov r0, #0
	add r5, r1, #0
	mvn r0, r0
	cmp r5, r0
	beq _021DD00A
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r1, #0xc
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r2, [r4, #4]
	mul r1, r5
	add r1, r2, r1
	ldr r0, [r4, r0]
	ldr r1, [r1, #8]
	mov r2, #4
	bl NARC_AllocAndReadWholeMember
	str r0, [sp, #0x14]
	cmp r0, #0
	bne _021DCFA0
	bl GF_AssertFail
_021DCFA0:
	ldr r0, [sp, #0x14]
	add r1, sp, #0x18
	bl NNS_G2dGetUnpackedScreenData
	ldr r3, [sp, #0x18]
	mov r0, #0
	str r0, [sp]
	add r2, r3, #0
	mov r0, #0x41
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r3, [r3, #8]
	ldr r0, [r0, #8]
	mov r1, #2
	add r2, #0xc
	bl BgCopyOrUncompressTilemapBufferRangeToVram
	mov r0, #0x41
	lsl r0, r0, #2
	ldr r3, [sp, #0x18]
	ldr r0, [r4, r0]
	add r2, r3, #0
	ldr r0, [r0, #8]
	ldr r3, [r3, #8]
	mov r1, #2
	add r2, #0xc
	bl BG_LoadScreenTilemapData
	mov r0, #0x20
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	add r0, #0xfe
	ldr r0, [r4, r0]
	mov r2, #0
	ldr r0, [r0, #8]
	mov r1, #2
	add r3, r2, #0
	bl BgTilemapRectChangePalette
	mov r0, #0x41
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	ldr r0, [r0, #8]
	bl BgCommitTilemapBufferToVram
	ldr r0, [sp, #0x14]
	bl FreeToHeap
	mov r0, #0
	str r0, [sp, #0x14]
_021DD00A:
	add sp, #0x24
	pop {r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021DD010
ov05_021DD010: ; 0x021DD010
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #8]
	add r4, r1, #0
	cmp r0, #0
	beq _021DD020
	bl GF_AssertFail
_021DD020:
	cmp r4, #0
	bgt _021DD028
	bl GF_AssertFail
_021DD028:
	cmp r4, #0x28
	bls _021DD030
	bl GF_AssertFail
_021DD030:
	add r0, r5, #0
	add r0, #0xc
	str r0, [r5, #8]
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021DD038
ov05_021DD038: ; 0x021DD038
	ldr r3, _021DD044 ; =memset
	mov r1, #0
	str r1, [r0, #8]
	add r0, #0xc
	mov r2, #0x28
	bx r3
	.balign 4, 0
_021DD044: .word memset

	thumb_func_start ov05_021DD048
ov05_021DD048: ; 0x021DD048
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	ldr r6, [r5]
	bl ov05_021DD6FC
	add r4, r0, #0
	bne _021DD05C
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021DD05C:
	add r0, r5, #0
	str r6, [r4]
	add r0, #0xc
	str r0, [r4, #0x34]
	ldr r0, [r5, #0x44]
	str r0, [r4, #0x38]
	ldr r0, [r5, #0x44]
	str r4, [r0, #0x34]
	str r4, [r5, #0x44]
	ldr r0, [r5, #8]
	add r0, #0x10
	bl sub_0201FE94
	str r0, [r4, #4]
	cmp r0, #0
	bne _021DD086
	add r0, r4, #0
	bl ov05_021DD100
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021DD086:
	add r0, r4, #0
	add r1, r7, #0
	bl ov05_021DD010
	ldr r0, [r4, #8]
	cmp r0, #0
	bne _021DD09E
	add r0, r4, #0
	bl ov05_021DD100
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021DD09E:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021DD0A4
ov05_021DD0A4: ; 0x021DD0A4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	str r0, [sp, #0x2c]
	add r7, r1, #0
	add r5, r2, #0
	str r3, [sp, #0x30]
	mov r6, #0
	add r4, sp, #0x34
_021DD0B4:
	ldr r0, [r5]
	bl sub_02009530
	add r6, r6, #1
	add r5, r5, #4
	stmia r4!, {r0}
	cmp r6, #4
	blt _021DD0B4
	ldr r0, [sp, #0x40]
	str r0, [sp]
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [sp, #0x30]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x58]
	str r0, [sp, #0x10]
	ldr r0, [r7, #8]
	str r0, [sp, #0x14]
	ldr r0, [r7, #0xc]
	str r0, [sp, #0x18]
	ldr r0, [r7, #0x10]
	str r0, [sp, #0x1c]
	ldr r0, [r7, #0x14]
	str r0, [sp, #0x20]
	mov r0, #0
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x2c]
	ldr r1, [sp, #0x34]
	ldr r2, [sp, #0x38]
	ldr r3, [sp, #0x3c]
	bl sub_02008AA4
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021DD100
ov05_021DD100: ; 0x021DD100
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x34]
	ldr r0, [r4, #0x38]
	str r1, [r0, #0x34]
	ldr r1, [r4, #0x38]
	ldr r0, [r4, #0x34]
	str r1, [r0, #0x38]
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021DD11E
	bl sub_0201FFC8
	mov r0, #0
	str r0, [r4, #4]
_021DD11E:
	add r0, r4, #0
	bl ov05_021DD038
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x3c
	bl memset
	pop {r4, pc}

	thumb_func_start ov05_021DD130
ov05_021DD130: ; 0x021DD130
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x34]
	cmp r0, r5
	beq _021DD146
_021DD13A:
	ldr r4, [r0, #0x34]
	bl ov05_021DD100
	add r0, r4, #0
	cmp r4, r5
	bne _021DD13A
_021DD146:
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021DD148
ov05_021DD148: ; 0x021DD148
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x34]
	add r6, r1, #0
	ldr r4, [r0, #0x34]
	cmp r0, r5
	beq _021DD160
_021DD156:
	blx r6
	add r0, r4, #0
	ldr r4, [r4, #0x34]
	cmp r0, r5
	bne _021DD156
_021DD160:
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021DD164
ov05_021DD164: ; 0x021DD164
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021DD168
ov05_021DD168: ; 0x021DD168
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1, #4]
	bl sub_0202011C
	add r2, r0, #0
	ldmia r2!, {r0, r1}
	stmia r4!, {r0, r1}
	ldr r0, [r2]
	str r0, [r4]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021DD180
ov05_021DD180: ; 0x021DD180
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #1
	mov r1, #3
	add r5, r2, #0
	lsl r0, r0, #0xe
	lsl r1, r1, #0xc
	bl FX_Div
	add r4, r0, #0
	mov r0, #0x41
	ldr r1, [r5]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r0, [r0, #0x20]
	bl Camera_GetPerspectiveAngle
	add r6, r0, #0
	mov r0, #0x41
	ldr r1, [r5]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r0, [r0, #0x20]
	bl Camera_GetDistance
	add r1, r0, #0
	add r0, sp, #0xc
	str r0, [sp]
	add r0, r6, #0
	add r2, r4, #0
	add r3, sp, #0x10
	bl sub_0201CB7C
	mov r1, #1
	ldr r0, [sp, #0x10]
	lsl r1, r1, #0x14
	bl FX_Div
	str r0, [sp, #0x10]
	mov r1, #3
	ldr r0, [sp, #0xc]
	lsl r1, r1, #0x12
	bl FX_Div
	ldr r3, _021DD2B0 ; =NNS_G3dGlb + 0x258
	str r0, [sp, #0xc]
	ldmia r3!, {r0, r1}
	add r2, sp, #0x14
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r4, _021DD2B4 ; =0x00000F4C
	str r0, [r2]
	ldr r1, [sp, #0x14]
	ldr r0, [r5, r4]
	ldr r2, [sp, #0x1c]
	sub r0, r1, r0
	add r1, r4, #0
	add r1, #8
	ldr r1, [r5, r1]
	add r4, #0xb4
	sub r7, r2, r1
	cmp r0, #0
	bge _021DD21E
	ldr r4, _021DD2B8 ; =0xFFFFF000
	asr r1, r0, #0x1f
	asr r3, r4, #0xc
	add r2, r4, #0
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r0, r0, r2
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
_021DD21E:
	ldr r1, [sp, #0x10]
	bl FX_Div
	add r6, r0, #0
	cmp r4, #0
	bge _021DD244
	asr r1, r6, #0x1f
	asr r3, r4, #0x1f
	add r2, r4, #0
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r6, r2, #0xc
	orr r6, r0
_021DD244:
	mov r4, #1
	lsl r4, r4, #0xc
	cmp r7, #0
	bge _021DD26A
	ldr r4, _021DD2B8 ; =0xFFFFF000
	asr r1, r7, #0x1f
	add r0, r7, #0
	asr r3, r4, #0xc
	add r2, r4, #0
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r7, r2, #0xc
	orr r7, r0
_021DD26A:
	ldr r1, [sp, #0xc]
	add r0, r7, #0
	bl FX_Div
	add r3, r0, #0
	cmp r4, #0
	bge _021DD292
	asr r1, r3, #0x1f
	asr r3, r4, #0x1f
	add r2, r4, #0
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r3, r2, #0xc
	orr r3, r0
_021DD292:
	add r0, r6, r3
	beq _021DD2A4
	ldr r0, _021DD2B4 ; =0x00000F4C
	add r2, sp, #0x14
	add r4, r5, r0
	ldmia r2!, {r0, r1}
	stmia r4!, {r0, r1}
	ldr r0, [r2]
	str r0, [r4]
_021DD2A4:
	ldr r0, [sp, #4]
	str r6, [r0]
	ldr r0, [sp, #8]
	str r3, [r0]
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021DD2B0: .word NNS_G3dGlb + 0x258
_021DD2B4: .word 0x00000F4C
_021DD2B8: .word 0xFFFFF000

	thumb_func_start ov05_021DD2BC
ov05_021DD2BC: ; 0x021DD2BC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r7, r1, #0
	str r2, [sp]
	add r0, sp, #8
	add r1, sp, #4
	add r2, r5, #0
	bl ov05_021DD180
	ldr r4, [r5, #0x40]
	add r5, #0xc
	cmp r4, r5
	beq _021DD300
	add r6, sp, #0xc
_021DD2DA:
	add r0, r6, #0
	add r1, r4, #0
	bl ov05_021DD168
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #8]
	sub r0, r1, r0
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #4]
	sub r0, r1, r0
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r6, #0
	bl ov05_021DC4FC
	ldr r4, [r4, #0x34]
	cmp r4, r5
	bne _021DD2DA
_021DD300:
	cmp r7, #0
	beq _021DD310
	ldr r0, [sp, #8]
	asr r0, r0, #0xc
	str r0, [r7]
	bpl _021DD310
	add r0, r0, #1
	str r0, [r7]
_021DD310:
	ldr r0, [sp]
	cmp r0, #0
	beq _021DD324
	ldr r0, [sp, #4]
	asr r1, r0, #0xc
	ldr r0, [sp]
	str r1, [r0]
	bpl _021DD324
	add r1, r1, #1
	str r1, [r0]
_021DD324:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021DD328
ov05_021DD328: ; 0x021DD328
	str r1, [r0]
	strh r2, [r0, #4]
	mov r1, #0
	strh r1, [r0, #6]
	strh r3, [r0, #8]
	strh r1, [r0, #0xa]
	ldr r1, [sp]
	strh r1, [r0, #0xc]
	ldr r1, [sp, #4]
	strh r1, [r0, #0xe]
	ldr r1, [sp, #8]
	strh r1, [r0, #0x10]
	ldr r1, [sp, #0xc]
	strh r1, [r0, #0x12]
	ldr r1, [sp, #0x10]
	str r1, [r0, #0x14]
	ldr r1, [sp, #0x14]
	str r1, [r0, #0x18]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021DD350
ov05_021DD350: ; 0x021DD350
	strh r1, [r0, #0xc]
	strh r2, [r0, #0xe]
	ldr r1, [sp]
	strh r3, [r0, #0x10]
	str r1, [r0, #0x14]
	bx lr

	thumb_func_start ov05_021DD35C
ov05_021DD35C: ; 0x021DD35C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x10
	ldrsh r0, [r5, r0]
	mov r4, #0
	cmp r0, #0
	bne _021DD370
	mov r0, #1
	orr r4, r0
	b _021DD396
_021DD370:
	bgt _021DD376
	mov r2, #1
	b _021DD378
_021DD376:
	add r2, r4, #0
_021DD378:
	mov r0, #0xe
	ldrsh r1, [r5, r0]
	mov r0, #8
	ldrsh r0, [r5, r0]
	cmp r0, r1
	blt _021DD388
	cmp r2, #0
	beq _021DD390
_021DD388:
	cmp r0, r1
	bgt _021DD396
	cmp r2, #1
	bne _021DD396
_021DD390:
	mov r0, #1
	orr r4, r0
	strh r1, [r5, #8]
_021DD396:
	ldr r0, [r5, #0x14]
	cmp r0, #0
	bne _021DD3A2
	mov r0, #2
	orr r4, r0
	b _021DD3C8
_021DD3A2:
	bgt _021DD3A8
	mov r2, #1
	b _021DD3AA
_021DD3A8:
	mov r2, #0
_021DD3AA:
	mov r0, #0xc
	ldrsh r1, [r5, r0]
	mov r0, #4
	ldrsh r0, [r5, r0]
	cmp r0, r1
	blt _021DD3BA
	cmp r2, #0
	beq _021DD3C2
_021DD3BA:
	cmp r0, r1
	bgt _021DD3C8
	cmp r2, #1
	bne _021DD3C8
_021DD3C2:
	mov r0, #2
	orr r4, r0
	strh r1, [r5, #4]
_021DD3C8:
	mov r0, #6
	ldrsh r1, [r5, r0]
	sub r1, r1, #1
	strh r1, [r5, #6]
	ldrsh r0, [r5, r0]
	cmp r0, #0
	bgt _021DD41C
	mov r1, #4
	ldrsh r1, [r5, r1]
	ldr r0, [r5]
	ldr r2, [r5, #0x18]
	blx r2
	mov r0, #8
	ldrsh r1, [r5, r0]
	strh r1, [r5, #6]
	mov r1, #1
	tst r1, r4
	bne _021DD3F6
	ldrsh r1, [r5, r0]
	mov r0, #0x10
	ldrsh r0, [r5, r0]
	add r0, r1, r0
	strh r0, [r5, #8]
_021DD3F6:
	mov r0, #2
	tst r0, r4
	bne _021DD41C
	mov r0, #0xa
	ldrsh r1, [r5, r0]
	add r1, r1, #1
	strh r1, [r5, #0xa]
	ldrsh r1, [r5, r0]
	mov r0, #0x12
	ldrsh r0, [r5, r0]
	cmp r1, r0
	blt _021DD41C
	mov r0, #0
	strh r0, [r5, #0xa]
	mov r0, #4
	ldrsh r1, [r5, r0]
	ldr r0, [r5, #0x14]
	add r0, r1, r0
	strh r0, [r5, #4]
_021DD41C:
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021DD420
ov05_021DD420: ; 0x021DD420
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	ldr r1, [sp, #0x1c]
	str r2, [r4]
	cmp r1, #0
	beq _021DD470
	cmp r1, #1
	bne _021DD454
	add r1, r3, #0
	add r3, sp, #0
	add r0, r2, #0
	ldrh r3, [r3, #0x14]
	ldr r2, [sp, #0x10]
	bl ov05_021DD49C
	add r0, r4, #0
	bl ov05_021DD598
	ldr r1, [sp, #0x18]
	add r0, r4, #0
	mov r2, #1
	bl ov05_021DD5B4
	add sp, #8
	pop {r4, pc}
_021DD454:
	cmp r1, #2
	bne _021DD470
	add r1, sp, #0
	ldrh r1, [r1, #0x14]
	ldr r4, [sp, #0x18]
	str r1, [sp]
	mov r1, #0x7f
	mul r1, r4
	str r1, [sp, #4]
	add r1, r2, #0
	add r2, r3, #0
	ldr r3, [sp, #0x10]
	bl ov05_021DD4C8
_021DD470:
	add sp, #8
	pop {r4, pc}

	thumb_func_start ov05_021DD474
ov05_021DD474: ; 0x021DD474
	push {r4, lr}
	mov r4, #1
	cmp r2, #0
	beq _021DD498
	cmp r2, #1
	bne _021DD48A
	add r0, r1, #0
	bl ov05_021DD5D0
	add r4, r0, #0
	b _021DD498
_021DD48A:
	cmp r2, #2
	bne _021DD498
	bl ov05_021DD54C
	cmp r0, #0
	bne _021DD498
	mov r4, #0
_021DD498:
	add r0, r4, #0
	pop {r4, pc}

	thumb_func_start ov05_021DD49C
ov05_021DD49C: ; 0x021DD49C
	push {r3, r4, r5, lr}
	sub sp, #8
	str r1, [sp]
	mov r1, #0
	add r4, r3, #0
	str r2, [sp, #4]
	mvn r1, r1
	mov r2, #1
	mov r3, #0
	add r5, r0, #0
	bl ov05_021DBA40
	mov r1, #0
	add r0, r5, #0
	mvn r1, r1
	add r2, r4, #0
	mov r3, #0x1f
	bl ov05_021DBA78
	add sp, #8
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021DD4C8
ov05_021DD4C8: ; 0x021DD4C8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	str r2, [sp]
	str r3, [sp, #4]
	ldr r6, [sp, #0x2c]
	bl ov05_021DBA34
	str r0, [sp, #8]
	add r0, r4, #0
	bl ov05_021DBA38
	str r0, [sp, #0xc]
	add r0, r4, #0
	bl ov05_021DBA3C
	add r7, r0, #0
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #4]
	add r0, r5, #4
	add r3, r6, #0
	str r4, [r5]
	bl ov05_021DC6EC
	add r0, sp, #0x18
	ldrh r4, [r0, #0x10]
	add r0, r5, #0
	mov r2, #0x1f
	add r1, r7, #0
	and r1, r2
	add r0, #0x18
	and r2, r4
	add r3, r6, #0
	bl ov05_021DC6EC
	add r0, r5, #0
	asr r1, r7, #5
	mov r3, #0x1f
	asr r2, r4, #5
	add r0, #0x2c
	and r1, r3
	and r2, r3
	add r3, r6, #0
	bl ov05_021DC6EC
	add r0, r5, #0
	asr r1, r7, #0xa
	mov r2, #0x1f
	asr r3, r4, #0xa
	and r1, r2
	and r2, r3
	add r0, #0x40
	add r3, r6, #0
	bl ov05_021DC6EC
	add r5, #0x54
	ldr r1, [sp, #8]
	ldr r2, [sp]
	add r0, r5, #0
	add r3, r6, #0
	bl ov05_021DC6EC
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021DD54C
ov05_021DD54C: ; 0x021DD54C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, r5, #4
	bl ov05_021DC6FC
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0x18
	bl ov05_021DC6FC
	add r0, r5, #0
	add r0, #0x2c
	bl ov05_021DC6FC
	add r0, r5, #0
	add r0, #0x40
	bl ov05_021DC6FC
	add r0, r5, #0
	add r0, #0x54
	bl ov05_021DC6FC
	ldr r3, [r5, #0x40]
	ldr r0, [r5]
	lsl r6, r3, #0xa
	ldr r1, [r5, #0x54]
	ldr r2, [r5, #4]
	ldr r3, [r5, #0x18]
	ldr r5, [r5, #0x2c]
	lsl r5, r5, #5
	orr r3, r5
	orr r3, r6
	lsl r3, r3, #0x10
	lsr r3, r3, #0x10
	bl ov05_021DD49C
	add r0, r4, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021DD598
ov05_021DD598: ; 0x021DD598
	mov r2, #0
	add r3, r0, #0
	add r1, r2, #0
_021DD59E:
	add r0, r3, r2
	add r2, r2, #1
	strb r1, [r0, #4]
	cmp r2, #0x20
	blt _021DD59E
	ldr r0, [r3]
	add r1, r3, #4
	ldr r3, _021DD5B0 ; =ov05_021DBAA0
	bx r3
	.balign 4, 0
_021DD5B0: .word ov05_021DBAA0

	thumb_func_start ov05_021DD5B4
ov05_021DD5B4: ; 0x021DD5B4
	mov r3, #0x7f
	str r3, [r0, #0x24]
	mov r3, #0
	str r3, [r0, #0x28]
	strh r1, [r0, #0x2c]
	cmp r2, #1
	bne _021DD5C8
	mov r1, #1
	strh r1, [r0, #0x2e]
	bx lr
_021DD5C8:
	sub r1, r3, #1
	strh r1, [r0, #0x2e]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021DD5D0
ov05_021DD5D0: ; 0x021DD5D0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl ov05_021DD60C
	add r4, r0, #0
	ldr r0, [r5, #0x28]
	cmp r0, #0
	bne _021DD5E8
	ldr r0, [r5]
	add r1, r5, #4
	bl ov05_021DBAA0
_021DD5E8:
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021DD5EC
ov05_021DD5EC: ; 0x021DD5EC
	push {r4, lr}
	add r4, r0, #0
	mov r2, #1
	str r2, [r4, #0x24]
	mov r1, #0
	str r1, [r4, #0x28]
	strh r1, [r4, #0x2c]
	strh r2, [r4, #0x2e]
	bl ov05_021DD64C
	ldr r0, [r4]
	add r1, r4, #4
	bl ov05_021DBAA0
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021DD60C
ov05_021DD60C: ; 0x021DD60C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r1, #0x2e
	ldrsh r1, [r5, r1]
	mov r4, #0
	cmp r1, #0
	bne _021DD61E
	mov r4, #1
	b _021DD648
_021DD61E:
	ldr r1, [r5, #0x24]
	cmp r1, #0
	bgt _021DD628
	mov r4, #1
	b _021DD648
_021DD628:
	ldr r1, [r5, #0x28]
	add r2, r1, #1
	str r2, [r5, #0x28]
	mov r1, #0x2c
	ldrsh r1, [r5, r1]
	cmp r2, r1
	blt _021DD648
	str r4, [r5, #0x28]
	bl ov05_021DD64C
	ldr r0, [r5, #0x24]
	sub r0, r0, #1
	str r0, [r5, #0x24]
	cmp r0, #0
	bgt _021DD648
	mov r4, #1
_021DD648:
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021DD64C
ov05_021DD64C: ; 0x021DD64C
	push {r3, r4}
	mov r1, #0x2e
	ldrsh r1, [r0, r1]
	ldr r2, [r0, #0x24]
	cmp r1, #0
	bge _021DD65E
	mov r1, #0x7f
	sub r2, r1, r2
	b _021DD65E
_021DD65E:
	asr r1, r2, #1
	lsr r1, r1, #0x1e
	add r1, r2, r1
	asr r4, r1, #2
	mov r3, #0x1f
	cmp r4, #0x1f
	bge _021DD67A
_021DD66C:
	sub r1, r3, r4
	lsl r2, r1, #2
	add r1, r0, r3
	sub r3, r3, #1
	strb r2, [r1, #4]
	cmp r3, r4
	bgt _021DD66C
_021DD67A:
	pop {r3, r4}
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021DD680
ov05_021DD680: ; 0x021DD680
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r1, #0
	ldr r1, [sp, #0x28]
	str r0, [sp]
	str r1, [sp, #0x28]
	add r1, r2, #0
	str r2, [sp, #4]
	str r3, [sp, #8]
	ldr r7, [sp, #0x2c]
	blx r4
	ldr r0, [sp]
	mov r6, #0
	ldr r5, [r0, #0x40]
	str r6, [sp, #0x10]
	ldr r0, [r5, #0x34]
	str r0, [sp, #0xc]
	ldr r0, [sp, #4]
	cmp r0, #0
	ble _021DD6F6
	ldr r0, [sp]
	add r0, #0xc
	str r0, [sp]
_021DD6AE:
	ldr r0, [sp]
	cmp r5, r0
	beq _021DD6F6
	mov r4, #0
	cmp r6, #0
	ble _021DD6CA
_021DD6BA:
	add r0, r5, #0
	blx r7
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _021DD6CA
	add r4, r4, #1
	cmp r4, r6
	blt _021DD6BA
_021DD6CA:
	ldr r5, [sp, #0xc]
	ldr r1, [sp, #0x10]
	add r0, r5, #0
	ldr r0, [r0, #0x34]
	str r0, [sp, #0xc]
	ldr r0, [sp, #8]
	cmp r1, r0
	blt _021DD6EA
	add r0, r1, #0
	ldr r1, [sp, #8]
	bl _s32_div_f
	cmp r1, #0
	bne _021DD6EA
	ldr r0, [sp, #0x28]
	add r6, r6, r0
_021DD6EA:
	ldr r0, [sp, #0x10]
	add r1, r0, #1
	ldr r0, [sp, #4]
	str r1, [sp, #0x10]
	cmp r1, r0
	blt _021DD6AE
_021DD6F6:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021DD6FC
ov05_021DD6FC: ; 0x021DD6FC
	mov r2, #0
	add r3, r0, #0
_021DD700:
	ldr r1, [r3, #0x48]
	cmp r1, #0
	bne _021DD710
	mov r1, #0x3c
	add r0, #0x48
	mul r1, r2
	add r0, r0, r1
	bx lr
_021DD710:
	add r2, r2, #1
	add r3, #0x3c
	cmp r2, #0x40
	blt _021DD700
	mov r0, #0
	bx lr

	thumb_func_start ov05_021DD71C
ov05_021DD71C: ; 0x021DD71C
	push {r3, lr}
	ldr r0, _021DD76C ; =0x00000F62
	ldrh r2, [r1, r0]
	cmp r2, #5
	bhi _021DD76A
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021DD732: ; jump table
	.short _021DD73E - _021DD732 - 2 ; case 0
	.short _021DD744 - _021DD732 - 2 ; case 1
	.short _021DD74A - _021DD732 - 2 ; case 2
	.short _021DD750 - _021DD732 - 2 ; case 3
	.short _021DD75E - _021DD732 - 2 ; case 4
	.short _021DD764 - _021DD732 - 2 ; case 5
_021DD73E:
	mov r2, #1
	strh r2, [r1, r0]
	pop {r3, pc}
_021DD744:
	mov r2, #3
	strh r2, [r1, r0]
	pop {r3, pc}
_021DD74A:
	mov r2, #3
	strh r2, [r1, r0]
	pop {r3, pc}
_021DD750:
	add r2, r0, #4
	ldrh r2, [r1, r2]
	cmp r2, #5
	bne _021DD76A
	mov r2, #4
	strh r2, [r1, r0]
	pop {r3, pc}
_021DD75E:
	mov r2, #5
	strh r2, [r1, r0]
	pop {r3, pc}
_021DD764:
	ldr r0, [r1, #4]
	bl ov05_021DCB6C
_021DD76A:
	pop {r3, pc}
	.balign 4, 0
_021DD76C: .word 0x00000F62

	thumb_func_start ov05_021DD770
ov05_021DD770: ; 0x021DD770
	push {r4, r5, r6, lr}
	sub sp, #0x18
	ldr r0, _021DD998 ; =0x00000F58
	add r5, r1, #0
	add r2, r0, #0
	add r2, #0xa
	ldrh r2, [r5, r2]
	ldr r4, [r5, r0]
	cmp r2, #5
	bhi _021DD832
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021DD790: ; jump table
	.short _021DD79C - _021DD790 - 2 ; case 0
	.short _021DD7FA - _021DD790 - 2 ; case 1
	.short _021DD83C - _021DD790 - 2 ; case 2
	.short _021DD8A2 - _021DD790 - 2 ; case 3
	.short _021DD900 - _021DD790 - 2 ; case 4
	.short _021DD94E - _021DD790 - 2 ; case 5
_021DD79C:
	mov r0, #0x14
	str r0, [sp]
	mov r2, #1
	str r2, [sp, #4]
	sub r0, r2, #2
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, _021DD99C ; =ov05_021DD9BC
	mov r3, #8
	str r0, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021DD328
	ldr r0, _021DD9A0 ; =0x0000726F
	mov r2, #0x41
	str r0, [sp]
	ldr r0, _021DD9A4 ; =0x00006B5A
	lsl r2, r2, #2
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, _021DD9A8 ; =0x00000F64
	add r1, r4, #0
	ldrh r0, [r5, r0]
	add r1, #0x1c
	str r0, [sp, #0xc]
	ldr r3, [r5]
	add r0, r4, #0
	ldr r2, [r3, r2]
	add r0, #0x4c
	ldr r2, [r2, #0x44]
	mov r3, #3
	bl ov05_021DD420
	mov r0, #0
	add r4, #0xb4
	str r0, [r4]
	ldr r1, _021DD9AC ; =0x00000639
	add r0, r5, #0
	bl ov05_021E0FA4
	ldr r0, _021DD9B0 ; =0x00000F62
	mov r1, #1
	strh r1, [r5, r0]
	b _021DD96C
_021DD7FA:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DD81A
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r4, #0xb4
	sub r0, r0, #1
	str r0, [r4]
	b _021DD96C
_021DD81A:
	ldr r2, _021DD9A8 ; =0x00000F64
	add r0, r4, #0
	ldrh r2, [r5, r2]
	add r4, #0x1c
	add r0, #0x4c
	add r1, r4, #0
	bl ov05_021DD474
	cmp r0, #1
	bne _021DD832
	cmp r6, #3
	beq _021DD834
_021DD832:
	b _021DD96C
_021DD834:
	ldr r0, _021DD9B0 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	b _021DD96C
_021DD83C:
	mov r2, #0x14
	mov r3, #1
	str r2, [sp]
	str r3, [sp, #4]
	sub r0, r3, #2
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, _021DD99C ; =ov05_021DD9BC
	str r0, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021DD328
	ldr r0, _021DD9A8 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DD87E
	mov r0, #0x41
	ldr r1, [r5]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r2, _021DD9A0 ; =0x0000726F
	ldr r0, [r0, #0x44]
	ldr r3, _021DD9A4 ; =0x00006B5A
	mov r1, #3
	str r0, [r4, #0x1c]
	bl ov05_021DD49C
	add r4, #0x1c
	add r0, r4, #0
	bl ov05_021DD5EC
_021DD87E:
	mov r0, #1
	str r0, [sp]
	ldr r0, _021DD9B4 ; =ov05_021DDA7C
	ldr r1, _021DD99C ; =ov05_021DD9BC
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x14
	mov r3, #0xa
	bl ov05_021DD680
	ldr r1, _021DD9AC ; =0x00000639
	add r0, r5, #0
	bl ov05_021E0FA4
	ldr r0, _021DD9B0 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	b _021DD96C
_021DD8A2:
	mov r0, #6
	ldrsh r1, [r4, r0]
	sub r0, r1, #1
	strh r0, [r4, #6]
	cmp r1, #0
	bgt _021DD8BE
	mov r1, #4
	ldrsh r1, [r4, r1]
	add r0, r5, #0
	bl ov05_021DD9BC
	mov r0, #8
	ldrsh r0, [r4, r0]
	strh r0, [r4, #6]
_021DD8BE:
	ldr r0, _021DD9B8 ; =0x00000F66
	ldrh r0, [r5, r0]
	cmp r0, #5
	bne _021DD96C
	mov r0, #1
	mvn r0, r0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0
	mov r2, #8
	mov r3, #1
	bl ov05_021DD350
	ldr r0, _021DD9A8 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DD8EC
	add r0, r4, #0
	add r0, #0x1c
	mov r1, #1
	mov r2, #0
	bl ov05_021DD5B4
_021DD8EC:
	mov r0, #0
	add r4, #0xb4
	str r0, [r4]
	ldr r0, _021DD9B0 ; =0x00000F62
	mov r1, #4
	strh r1, [r5, r0]
	add r0, r5, #0
	bl ov05_021E0FD0
	b _021DD96C
_021DD900:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DD920
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r4, #0xb4
	sub r0, r0, #1
	str r0, [r4]
	b _021DD96C
_021DD920:
	ldr r0, _021DD9A8 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DD932
	add r4, #0x1c
	add r0, r4, #0
	bl ov05_021DD5D0
	b _021DD934
_021DD932:
	mov r0, #1
_021DD934:
	cmp r0, #1
	bne _021DD96C
	cmp r6, #3
	bne _021DD96C
	add r0, r5, #0
	ldr r1, [r5, #0x40]
	add r0, #0xc
	cmp r1, r0
	bne _021DD96C
	ldr r0, _021DD9B0 ; =0x00000F62
	mov r1, #5
	strh r1, [r5, r0]
	b _021DD96C
_021DD94E:
	add r0, #0xc
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DD966
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r0, [r4, #0x1c]
	mov r1, #1
	add r3, r2, #0
	bl ov05_021DBA40
_021DD966:
	ldr r0, [r5, #4]
	bl ov05_021DCB6C
_021DD96C:
	ldr r0, _021DD9B0 ; =0x00000F62
	ldrh r0, [r5, r0]
	cmp r0, #5
	beq _021DD992
	cmp r0, #0
	beq _021DD992
	add r0, r5, #0
	ldr r1, _021DD9B4 ; =ov05_021DDA7C
	add r0, #0xc
	bl ov05_021DD148
	mov r1, #0
	add r0, r5, #0
	add r2, r1, #0
	bl ov05_021DD2BC
	add r0, r5, #0
	bl ov05_021DD164
_021DD992:
	add sp, #0x18
	pop {r4, r5, r6, pc}
	nop
_021DD998: .word 0x00000F58
_021DD99C: .word ov05_021DD9BC
_021DD9A0: .word 0x0000726F
_021DD9A4: .word 0x00006B5A
_021DD9A8: .word 0x00000F64
_021DD9AC: .word 0x00000639
_021DD9B0: .word 0x00000F62
_021DD9B4: .word ov05_021DDA7C
_021DD9B8: .word 0x00000F66

	thumb_func_start ov05_021DD9BC
ov05_021DD9BC: ; 0x021DD9BC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r0, [sp]
	add r0, r1, #0
	mov r7, #0
	str r1, [sp, #4]
	cmp r0, #0
	ble _021DDA70
_021DD9CC:
	ldr r0, [sp]
	mov r1, #0x20
	bl ov05_021DD048
	add r6, r0, #0
	beq _021DDA70
	ldr r4, [r6, #8]
	mov r0, #0
	str r0, [r4]
	bl MTRandom
	mov r1, #3
	bl _u32_div_f
	add r5, r1, #0
	lsl r1, r5, #0x10
	ldr r0, [r6, #4]
	lsr r1, r1, #0x10
	bl sub_02020208
	bl MTRandom
	mov r1, #0x14
	bl _u32_div_f
	add r2, r5, #1
	mov r0, #0xa
	mul r0, r2
	add r0, r1, r0
	str r0, [r4, #8]
	cmp r5, #2
	bne _021DDA12
	ldr r0, [r4, #8]
	add r0, #0xa
	str r0, [r4, #8]
_021DDA12:
	add r0, r1, #0
	mov r1, #4
	mvn r1, r1
	bl _s32_div_f
	mov r1, #4
	add r2, r5, #1
	mvn r1, r1
	mul r1, r2
	add r0, r0, r1
	str r0, [r4, #0x10]
	cmp r5, #2
	bne _021DDA32
	ldr r0, [r4, #0x10]
	sub r0, r0, #5
	str r0, [r4, #0x10]
_021DDA32:
	mov r0, #0
	str r0, [r4, #0xc]
	bl MTRandom
	mov r1, #3
	bl _u32_div_f
	add r0, r1, #1
	str r0, [r4, #4]
	bl MTRandom
	ldr r1, _021DDA74 ; =0x0000010E
	bl _u32_div_f
	mov r0, #0xf
	mul r0, r5
	add r0, r0, r1
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r0, _021DDA78 ; =0xFFFA0000
	add r1, sp, #8
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [r6, #4]
	bl ov05_021DC4FC
	ldr r0, [sp, #4]
	add r7, r7, #1
	cmp r7, r0
	blt _021DD9CC
_021DDA70:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021DDA74: .word 0x0000010E
_021DDA78: .word 0xFFFA0000

	thumb_func_start ov05_021DDA7C
ov05_021DDA7C: ; 0x021DDA7C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r0, #0
	ldr r5, [r6, #8]
	add r0, sp, #0
	add r1, r6, #0
	bl ov05_021DD168
	ldr r0, [r5, #0xc]
	cmp r0, #0
	beq _021DDA9E
	cmp r0, #1
	beq _021DDAF6
	cmp r0, #2
	beq _021DDB08
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_021DDA9E:
	mov r4, #0
	mov r7, #2
_021DDAA2:
	ldr r0, [r5, #0x10]
	ldr r1, [sp]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp]
	ldr r0, [r5, #8]
	ldr r1, [sp, #4]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #4]
	ldr r1, [r5]
	add r0, r1, #1
	str r0, [r5]
	ldr r0, [r5, #4]
	cmp r1, r0
	ble _021DDAE4
	bl MTRandom
	mov r1, #0xa
	bl _u32_div_f
	cmp r1, #7
	bhs _021DDAD4
	str r7, [r5, #0xc]
	b _021DDAE4
_021DDAD4:
	mov r0, #1
	str r0, [r5, #0xc]
	mov r0, #4
	str r0, [r5]
	ldr r0, [r6, #4]
	mov r1, #3
	bl sub_02020208
_021DDAE4:
	add r4, r4, #1
	cmp r4, #2
	blt _021DDAA2
	ldr r0, [r6, #4]
	add r1, sp, #0
	bl ov05_021DC4FC
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_021DDAF6:
	ldr r1, [r5]
	sub r0, r1, #1
	str r0, [r5]
	cmp r1, #0
	bgt _021DDB0E
	mov r0, #2
	add sp, #0xc
	str r0, [r5, #0xc]
	pop {r4, r5, r6, r7, pc}
_021DDB08:
	add r0, r6, #0
	bl ov05_021DD100
_021DDB0E:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021DDB14
ov05_021DDB14: ; 0x021DDB14
	push {r4, r5, r6, lr}
	sub sp, #0x18
	ldr r0, _021DDD44 ; =0x00000F58
	add r5, r1, #0
	add r2, r0, #0
	add r2, #0xa
	ldrh r2, [r5, r2]
	ldr r4, [r5, r0]
	cmp r2, #5
	bhi _021DDBD6
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021DDB34: ; jump table
	.short _021DDB40 - _021DDB34 - 2 ; case 0
	.short _021DDB9E - _021DDB34 - 2 ; case 1
	.short _021DDBE0 - _021DDB34 - 2 ; case 2
	.short _021DDC4E - _021DDB34 - 2 ; case 3
	.short _021DDCA6 - _021DDB34 - 2 ; case 4
	.short _021DDCFA - _021DDB34 - 2 ; case 5
_021DDB40:
	mov r2, #1
	str r2, [sp]
	mov r0, #8
	str r0, [sp, #4]
	sub r0, #0xd
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, _021DDD48 ; =ov05_021DDD64
	mov r3, #0x14
	str r0, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021DD328
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb8
	str r1, [r0]
	ldr r0, _021DDD4C ; =0x0000726F
	mov r2, #0x41
	str r0, [sp]
	ldr r0, _021DDD50 ; =0x00006B5A
	add r1, r4, #0
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, _021DDD54 ; =0x00000F64
	lsl r2, r2, #2
	ldrh r0, [r5, r0]
	add r1, #0x1c
	str r0, [sp, #0xc]
	ldr r3, [r5]
	add r0, r4, #0
	ldr r2, [r3, r2]
	add r0, #0x4c
	ldr r2, [r2, #0x44]
	mov r3, #3
	bl ov05_021DD420
	mov r0, #0x10
	add r4, #0xb4
	str r0, [r4]
	ldr r0, _021DDD58 ; =0x00000F62
	mov r1, #1
	strh r1, [r5, r0]
	b _021DDD18
_021DDB9E:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DDBBE
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r4, #0xb4
	sub r0, r0, #1
	str r0, [r4]
	b _021DDD18
_021DDBBE:
	ldr r2, _021DDD54 ; =0x00000F64
	add r0, r4, #0
	ldrh r2, [r5, r2]
	add r4, #0x1c
	add r0, #0x4c
	add r1, r4, #0
	bl ov05_021DD474
	cmp r0, #1
	bne _021DDBD6
	cmp r6, #3
	beq _021DDBD8
_021DDBD6:
	b _021DDD18
_021DDBD8:
	ldr r0, _021DDD58 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	b _021DDD18
_021DDBE0:
	mov r2, #1
	mov r3, #8
	str r2, [sp]
	add r0, r3, #0
	str r3, [sp, #4]
	sub r0, #0xd
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, _021DDD48 ; =ov05_021DDD64
	str r0, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021DD328
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb8
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xbc
	str r1, [r0]
	ldr r0, _021DDD54 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DDC32
	mov r0, #0x41
	ldr r1, [r5]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r2, _021DDD4C ; =0x0000726F
	ldr r0, [r0, #0x44]
	ldr r3, _021DDD50 ; =0x00006B5A
	mov r1, #3
	str r0, [r4, #0x1c]
	bl ov05_021DD49C
	add r4, #0x1c
	add r0, r4, #0
	bl ov05_021DD5EC
_021DDC32:
	mov r0, #0x18
	str r0, [sp]
	ldr r0, _021DDD5C ; =ov05_021DDF44
	ldr r1, _021DDD48 ; =ov05_021DDD64
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x14
	mov r3, #2
	bl ov05_021DD680
	ldr r0, _021DDD58 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	b _021DDD18
_021DDC4E:
	mov r0, #6
	ldrsh r1, [r4, r0]
	sub r0, r1, #1
	strh r0, [r4, #6]
	cmp r1, #0
	bgt _021DDC6A
	mov r1, #4
	ldrsh r1, [r4, r1]
	add r0, r5, #0
	bl ov05_021DDD64
	mov r0, #8
	ldrsh r0, [r4, r0]
	strh r0, [r4, #6]
_021DDC6A:
	ldr r0, _021DDD60 ; =0x00000F66
	ldrh r0, [r5, r0]
	cmp r0, #5
	bne _021DDD18
	mov r0, #0
	mvn r0, r0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x14
	mov r3, #5
	bl ov05_021DD350
	ldr r0, _021DDD54 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DDC98
	add r0, r4, #0
	add r0, #0x1c
	mov r1, #2
	mov r2, #0
	bl ov05_021DD5B4
_021DDC98:
	mov r0, #0x20
	add r4, #0xb4
	str r0, [r4]
	ldr r0, _021DDD58 ; =0x00000F62
	mov r1, #4
	strh r1, [r5, r0]
	b _021DDD18
_021DDCA6:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DDCC6
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r4, #0xb4
	sub r0, r0, #1
	str r0, [r4]
	b _021DDD18
_021DDCC6:
	ldr r0, _021DDD54 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DDCD8
	add r0, r4, #0
	add r0, #0x1c
	bl ov05_021DD5D0
	b _021DDCDA
_021DDCD8:
	mov r0, #1
_021DDCDA:
	cmp r0, #1
	bne _021DDD18
	cmp r6, #3
	bne _021DDD18
	mov r0, #1
	add r4, #0xbc
	str r0, [r4]
	add r0, r5, #0
	ldr r1, [r5, #0x40]
	add r0, #0xc
	cmp r1, r0
	bne _021DDD18
	ldr r0, _021DDD58 ; =0x00000F62
	mov r1, #5
	strh r1, [r5, r0]
	b _021DDD18
_021DDCFA:
	add r0, #0xc
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DDD12
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r0, [r4, #0x1c]
	mov r1, #1
	add r3, r2, #0
	bl ov05_021DBA40
_021DDD12:
	ldr r0, [r5, #4]
	bl ov05_021DCB6C
_021DDD18:
	ldr r0, _021DDD58 ; =0x00000F62
	ldrh r0, [r5, r0]
	cmp r0, #5
	beq _021DDD3E
	cmp r0, #0
	beq _021DDD3E
	add r0, r5, #0
	ldr r1, _021DDD5C ; =ov05_021DDF44
	add r0, #0xc
	bl ov05_021DD148
	mov r1, #0
	add r0, r5, #0
	add r2, r1, #0
	bl ov05_021DD2BC
	add r0, r5, #0
	bl ov05_021DD164
_021DDD3E:
	add sp, #0x18
	pop {r4, r5, r6, pc}
	nop
_021DDD44: .word 0x00000F58
_021DDD48: .word ov05_021DDD64
_021DDD4C: .word 0x0000726F
_021DDD50: .word 0x00006B5A
_021DDD54: .word 0x00000F64
_021DDD58: .word 0x00000F62
_021DDD5C: .word ov05_021DDF44
_021DDD60: .word 0x00000F66

	thumb_func_start ov05_021DDD64
ov05_021DDD64: ; 0x021DDD64
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r7, r1, #0
	ldr r1, _021DDE70 ; =0x00000F58
	str r0, [sp]
	ldr r0, [r0, r1]
	str r0, [sp, #0x10]
	add r0, #0xb8
	ldr r0, [r0]
	cmp r0, #1
	bne _021DDD7C
	lsl r7, r7, #1
_021DDD7C:
	mov r6, #0
	cmp r7, #0
	ble _021DDE6A
	ldr r0, [sp, #0x10]
	str r0, [sp, #0xc]
	add r0, #0xb8
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	str r0, [sp, #8]
	add r0, #0xbc
	str r0, [sp, #8]
	lsr r0, r7, #0x1f
	add r0, r7, r0
	asr r0, r0, #1
	str r0, [sp, #4]
_021DDD9A:
	ldr r0, [sp]
	mov r1, #0x28
	bl ov05_021DD048
	add r4, r0, #0
	beq _021DDE6A
	ldr r5, [r4, #8]
	bl MTRandom
	mov r1, #3
	and r1, r0
	lsl r1, r1, #0x10
	ldr r0, [r4, #4]
	lsr r1, r1, #0x10
	bl sub_02020208
	mov r0, #0xa
	str r0, [r5, #0x10]
	mov r0, #0
	str r0, [r5, #0x14]
	str r0, [r5, #0x18]
	str r0, [r5, #0x20]
	bl MTRandom
	mov r1, #0x3c
	str r0, [sp, #0x14]
	bl _s32_div_f
	add r0, r1, #4
	str r0, [r5, #0x24]
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x14]
	lsr r0, r0, #0x1f
	lsl r2, r1, #0x1f
	sub r2, r2, r0
	mov r1, #0x1f
	ror r2, r1
	add r0, r0, r2
	bne _021DDDEC
	mov r0, #1
	b _021DDDF0
_021DDDEC:
	add r0, r1, #0
	sub r0, #0x20
_021DDDF0:
	str r0, [r5, #4]
	bl MTRandom
	mov r1, #1
	and r0, r1
	add r0, r0, #4
	str r0, [r5, #8]
	bl MTRandom
	mov r1, #1
	and r0, r1
	add r0, r0, #1
	str r0, [r5, #0xc]
	ldr r0, [sp, #0xc]
	str r0, [r5]
	ldr r0, [sp, #8]
	str r0, [r5, #0x1c]
	bl MTRandom
	ldr r1, _021DDE74 ; =0x0000019E
	bl _u32_div_f
	sub r1, #0x20
	lsl r0, r1, #0xc
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x10]
	add r0, #0xb8
	ldr r0, [r0]
	cmp r0, #1
	bne _021DDE48
	ldr r0, [sp, #4]
	cmp r6, r0
	blt _021DDE48
	bl MTRandom
	mov r1, #0x14
	bl _u32_div_f
	mov r0, #0x27
	mvn r0, r0
	sub r0, r0, r1
	lsl r0, r0, #0xc
	str r0, [sp, #0x1c]
	b _021DDE5C
_021DDE48:
	bl MTRandom
	mov r1, #0x14
	bl _u32_div_f
	mov r0, #7
	mvn r0, r0
	sub r0, r0, r1
	lsl r0, r0, #0xc
	str r0, [sp, #0x1c]
_021DDE5C:
	ldr r0, [r4, #4]
	add r1, sp, #0x18
	bl ov05_021DC4FC
	add r6, r6, #1
	cmp r6, r7
	blt _021DDD9A
_021DDE6A:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_021DDE70: .word 0x00000F58
_021DDE74: .word 0x0000019E

	thumb_func_start ov05_021DDE78
ov05_021DDE78: ; 0x021DDE78
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	add r0, sp, #0
	add r1, r5, #0
	bl ov05_021DD168
	ldr r0, [r4, #0x14]
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, [r4, #8]
	cmp r1, r0
	blt _021DDECE
	ldr r0, [r4, #4]
	ldr r1, [sp]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp]
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	ldr r1, [r4, #0x14]
	ldr r0, _021DDF3C ; =0xFFFF0000
	and r0, r1
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x10]
	cmp r0, #0xa
	ldr r0, [r4, #8]
	bge _021DDEB8
	sub r0, r0, #1
	b _021DDEBA
_021DDEB8:
	add r0, r0, #1
_021DDEBA:
	str r0, [r4, #8]
	ldr r0, [r4, #0x10]
	cmp r0, #0x14
	blt _021DDECE
	mov r0, #0
	str r0, [r4, #0x10]
	ldr r1, [r4, #4]
	sub r0, r0, #1
	mul r0, r1
	str r0, [r4, #4]
_021DDECE:
	ldr r0, [r4, #0x14]
	asr r1, r0, #0x10
	ldr r0, [r4, #0xc]
	cmp r1, r0
	blt _021DDEEA
	mov r0, #1
	ldr r1, [sp, #4]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #4]
	ldr r0, [r4, #0x14]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [r4, #0x14]
_021DDEEA:
	ldr r0, [r5, #4]
	add r1, sp, #0
	bl ov05_021DC4FC
	ldr r0, [sp]
	mov r1, #0x64
	asr r0, r0, #0xc
	str r0, [sp]
	ldr r0, [sp, #4]
	asr r0, r0, #0xc
	str r0, [sp, #4]
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	bl _s32_div_f
	str r1, [r4, #0x18]
	ldr r0, [r4, #0x14]
	add r1, r0, #1
	mov r0, #1
	lsl r0, r0, #0x10
	add r0, r1, r0
	str r0, [r4, #0x14]
	ldr r1, [sp, #4]
	ldr r0, _021DDF40 ; =0xFFFFFEE4
	cmp r1, r0
	bge _021DDF24
	sub r0, #0xc
	cmp r1, r0
	bgt _021DDF2C
_021DDF24:
	cmp r1, #0xd4
	ble _021DDF38
	cmp r1, #0xe8
	bge _021DDF38
_021DDF2C:
	ldr r0, [r4]
	mov r1, #1
	str r1, [r0]
	add r0, r5, #0
	bl ov05_021DD100
_021DDF38:
	add sp, #0xc
	pop {r4, r5, pc}
	.balign 4, 0
_021DDF3C: .word 0xFFFF0000
_021DDF40: .word 0xFFFFFEE4

	thumb_func_start ov05_021DDF44
ov05_021DDF44: ; 0x021DDF44
	push {r3, lr}
	ldr r1, [r0, #8]
	ldr r3, [r1, #0x20]
	ldr r2, [r1, #0x1c]
	cmp r3, #0
	beq _021DDF56
	cmp r3, #1
	beq _021DDF62
	b _021DDF70
_021DDF56:
	ldr r2, [r2]
	cmp r2, #1
	bne _021DDF70
	add r2, r3, #1
	str r2, [r1, #0x20]
	b _021DDF70
_021DDF62:
	ldr r2, [r1, #0x24]
	sub r2, r2, #1
	str r2, [r1, #0x24]
	bpl _021DDF70
	bl ov05_021DD100
	pop {r3, pc}
_021DDF70:
	bl ov05_021DDE78
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021DDF78
ov05_021DDF78: ; 0x021DDF78
	push {r4, r5, r6, lr}
	sub sp, #0x18
	ldr r0, _021DE19C ; =0x00000F58
	add r5, r1, #0
	add r2, r0, #0
	add r2, #0xa
	ldrh r2, [r5, r2]
	ldr r4, [r5, r0]
	cmp r2, #5
	bhi _021DE03C
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021DDF98: ; jump table
	.short _021DDFA4 - _021DDF98 - 2 ; case 0
	.short _021DE004 - _021DDF98 - 2 ; case 1
	.short _021DE046 - _021DDF98 - 2 ; case 2
	.short _021DE0AE - _021DDF98 - 2 ; case 3
	.short _021DE106 - _021DDF98 - 2 ; case 4
	.short _021DE154 - _021DDF98 - 2 ; case 5
_021DDFA4:
	mov r0, #6
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	sub r0, #8
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	mov r2, #1
	ldr r0, _021DE1A0 ; =ov05_021DE1BC
	str r2, [sp, #0x10]
	str r0, [sp, #0x14]
	add r0, r4, #0
	mov r3, #0x1e
	bl ov05_021DD328
	ldr r0, _021DE1A4 ; =0x00006D6F
	mov r2, #0x41
	str r0, [sp]
	ldr r0, _021DE1A8 ; =0x00006318
	add r1, r4, #0
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	ldr r0, _021DE1AC ; =0x00000F64
	lsl r2, r2, #2
	ldrh r0, [r5, r0]
	add r1, #0x1c
	str r0, [sp, #0xc]
	ldr r3, [r5]
	add r0, r4, #0
	ldr r2, [r3, r2]
	add r0, #0x4c
	ldr r2, [r2, #0x44]
	mov r3, #3
	bl ov05_021DD420
	add r0, r4, #0
	mov r1, #8
	add r0, #0xb4
	str r1, [r0]
	mov r0, #0
	add r4, #0xb8
	str r0, [r4]
	ldr r0, _021DE1B0 ; =0x00000F62
	mov r1, #1
	strh r1, [r5, r0]
	b _021DE172
_021DE004:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DE024
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r4, #0xb4
	sub r0, r0, #1
	str r0, [r4]
	b _021DE172
_021DE024:
	ldr r2, _021DE1AC ; =0x00000F64
	add r0, r4, #0
	ldrh r2, [r5, r2]
	add r4, #0x1c
	add r0, #0x4c
	add r1, r4, #0
	bl ov05_021DD474
	cmp r0, #1
	bne _021DE03C
	cmp r6, #3
	beq _021DE03E
_021DE03C:
	b _021DE172
_021DE03E:
	ldr r0, _021DE1B0 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	b _021DE172
_021DE046:
	mov r2, #6
	mov r3, #3
	str r2, [sp]
	add r0, r3, #0
	str r3, [sp, #4]
	sub r0, #8
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, _021DE1A0 ; =ov05_021DE1BC
	str r0, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021DD328
	ldr r0, _021DE1AC ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DE08C
	mov r0, #0x41
	ldr r1, [r5]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r2, _021DE1A4 ; =0x00006D6F
	ldr r0, [r0, #0x44]
	ldr r3, _021DE1A8 ; =0x00006318
	mov r1, #3
	str r0, [r4, #0x1c]
	bl ov05_021DD49C
	add r0, r4, #0
	add r0, #0x1c
	bl ov05_021DD5EC
_021DE08C:
	mov r0, #0
	add r4, #0xb8
	str r0, [r4]
	mov r0, #3
	str r0, [sp]
	ldr r0, _021DE1B4 ; =ov05_021DE2E0
	ldr r1, _021DE1A0 ; =ov05_021DE1BC
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x14
	mov r3, #2
	bl ov05_021DD680
	ldr r0, _021DE1B0 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	b _021DE172
_021DE0AE:
	mov r0, #6
	ldrsh r1, [r4, r0]
	sub r0, r1, #1
	strh r0, [r4, #6]
	cmp r1, #0
	bgt _021DE0CA
	mov r1, #4
	ldrsh r1, [r4, r1]
	add r0, r5, #0
	bl ov05_021DE1BC
	mov r0, #8
	ldrsh r0, [r4, r0]
	strh r0, [r4, #6]
_021DE0CA:
	ldr r0, _021DE1B8 ; =0x00000F66
	ldrh r0, [r5, r0]
	cmp r0, #5
	bne _021DE172
	mov r0, #2
	mvn r0, r0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x1e
	mov r3, #5
	bl ov05_021DD350
	ldr r0, _021DE1AC ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DE0F8
	add r0, r4, #0
	add r0, #0x1c
	mov r1, #1
	mov r2, #0
	bl ov05_021DD5B4
_021DE0F8:
	mov r0, #0
	add r4, #0xb4
	str r0, [r4]
	ldr r0, _021DE1B0 ; =0x00000F62
	mov r1, #4
	strh r1, [r5, r0]
	b _021DE172
_021DE106:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DE126
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r4, #0xb4
	sub r0, r0, #1
	str r0, [r4]
	b _021DE172
_021DE126:
	ldr r0, _021DE1AC ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DE138
	add r4, #0x1c
	add r0, r4, #0
	bl ov05_021DD5D0
	b _021DE13A
_021DE138:
	mov r0, #1
_021DE13A:
	cmp r0, #1
	bne _021DE172
	cmp r6, #3
	bne _021DE172
	add r0, r5, #0
	ldr r1, [r5, #0x40]
	add r0, #0xc
	cmp r1, r0
	bne _021DE172
	ldr r0, _021DE1B0 ; =0x00000F62
	mov r1, #5
	strh r1, [r5, r0]
	b _021DE172
_021DE154:
	add r0, #0xc
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DE16C
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r0, [r4, #0x1c]
	mov r1, #1
	add r3, r2, #0
	bl ov05_021DBA40
_021DE16C:
	ldr r0, [r5, #4]
	bl ov05_021DCB6C
_021DE172:
	ldr r0, _021DE1B0 ; =0x00000F62
	ldrh r0, [r5, r0]
	cmp r0, #5
	beq _021DE198
	cmp r0, #0
	beq _021DE198
	add r0, r5, #0
	ldr r1, _021DE1B4 ; =ov05_021DE2E0
	add r0, #0xc
	bl ov05_021DD148
	mov r1, #0
	add r0, r5, #0
	add r2, r1, #0
	bl ov05_021DD2BC
	add r0, r5, #0
	bl ov05_021DD164
_021DE198:
	add sp, #0x18
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021DE19C: .word 0x00000F58
_021DE1A0: .word ov05_021DE1BC
_021DE1A4: .word 0x00006D6F
_021DE1A8: .word 0x00006318
_021DE1AC: .word 0x00000F64
_021DE1B0: .word 0x00000F62
_021DE1B4: .word ov05_021DE2E0
_021DE1B8: .word 0x00000F66

	thumb_func_start ov05_021DE1BC
ov05_021DE1BC: ; 0x021DE1BC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x58
	ldr r3, _021DE2D4 ; =ov05_021F67D8
	add r2, sp, #0x48
	str r0, [sp]
	str r1, [sp, #4]
	ldmia r3!, {r0, r1}
	str r2, [sp, #0x10]
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r3, _021DE2D8 ; =ov05_021F67C8
	add r2, sp, #0x38
	str r2, [sp, #0x14]
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r1, _021DE2DC ; =0x00000F58
	ldr r0, [sp]
	ldr r6, [r0, r1]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #4]
	cmp r0, #0
	ble _021DE2D0
	add r0, r6, #0
	str r0, [sp, #0x18]
	add r0, #0xb8
	str r0, [sp, #0x18]
	mov r0, #7
	mvn r0, r0
	lsl r0, r0, #0xc
	str r0, [sp, #0x1c]
_021DE200:
	ldr r0, [sp]
	mov r1, #0x20
	bl ov05_021DD048
	add r4, r0, #0
	beq _021DE2D0
	ldr r0, [sp, #0x18]
	ldr r5, [r4, #8]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [r0]
	add r0, r6, #0
	add r0, #0xb8
	ldr r1, [r0]
	mov r0, #0x32
	lsl r0, r0, #4
	cmp r1, r0
	blt _021DE22E
	add r1, r6, #0
	add r1, #0xb8
	mov r0, #0
	str r0, [r1]
_021DE22E:
	add r0, r6, #0
	add r0, #0xb8
	ldr r0, [r0]
	mov r1, #0xc8
	bl _s32_div_f
	lsl r0, r0, #2
	ldr r1, [sp, #0x10]
	str r0, [sp, #8]
	ldr r0, [r1, r0]
	str r0, [r5, #0x14]
	mov r0, #0
	str r0, [r5]
	bl MTRandom
	mov r1, #0x2a
	bl _u32_div_f
	add r0, r1, #4
	str r0, [r5, #4]
	sub r0, r0, #4
	mov r1, #0xf
	bl _s32_div_f
	add r7, r0, #0
	lsl r1, r7, #0x10
	ldr r0, [r4, #4]
	lsr r1, r1, #0x10
	bl sub_02020208
	add r0, r7, #1
	neg r1, r0
	str r1, [r5, #0x10]
	ldr r2, [sp, #0x14]
	ldr r1, [sp, #8]
	ldr r1, [r2, r1]
	mul r1, r0
	str r1, [r5, #8]
	mov r0, #0
	str r0, [r5, #0xc]
	add r0, sp, #0x20
	add r1, r4, #0
	bl ov05_021DD168
	add r3, sp, #0x20
	ldmia r3!, {r0, r1}
	add r2, sp, #0x2c
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	bl MTRandom
	mov r1, #0x69
	lsl r1, r1, #2
	bl _u32_div_f
	mov r0, #1
	sub r2, r0, r7
	sub r0, #0x15
	mul r0, r2
	add r1, r0, r1
	mov r0, #7
	mvn r0, r0
	str r0, [sp, #0x30]
	mov r0, #0
	str r0, [sp, #0x34]
	str r1, [sp, #0x2c]
	lsl r0, r1, #0xc
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x1c]
	add r1, sp, #0x2c
	str r0, [sp, #0x30]
	ldr r0, [r4, #4]
	bl ov05_021DC4FC
	ldr r0, [sp, #0xc]
	add r1, r0, #1
	ldr r0, [sp, #4]
	str r1, [sp, #0xc]
	cmp r1, r0
	blt _021DE200
_021DE2D0:
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021DE2D4: .word ov05_021F67D8
_021DE2D8: .word ov05_021F67C8
_021DE2DC: .word 0x00000F58

	thumb_func_start ov05_021DE2E0
ov05_021DE2E0: ; 0x021DE2E0
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r0, sp, #0
	add r1, r5, #0
	ldr r4, [r5, #8]
	bl ov05_021DD168
	add r3, sp, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021DE30A
	cmp r0, #1
	beq _021DE356
	add sp, #0x18
	pop {r3, r4, r5, pc}
_021DE30A:
	ldr r0, [r4, #0x10]
	ldr r1, [sp, #0xc]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0xc]
	ldr r0, [r4, #8]
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x10]
	ldr r1, [r4]
	add r0, r1, #1
	str r0, [r4]
	ldr r0, [r4, #4]
	cmp r1, r0
	ble _021DE32E
	mov r0, #1
	str r0, [r4, #0xc]
_021DE32E:
	ldr r0, [r4]
	ldr r1, [r4, #0x14]
	bl _s32_div_f
	cmp r1, #0
	bne _021DE34A
	ldr r0, [r4, #0x10]
	sub r0, r0, #1
	str r0, [r4, #0x10]
	ldr r0, [r4, #8]
	cmp r0, #1
	ble _021DE34A
	sub r0, r0, #1
	str r0, [r4, #8]
_021DE34A:
	ldr r0, [r5, #4]
	add r1, sp, #0xc
	bl ov05_021DC4FC
	add sp, #0x18
	pop {r3, r4, r5, pc}
_021DE356:
	add r0, r5, #0
	bl ov05_021DD100
	add sp, #0x18
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021DE360
ov05_021DE360: ; 0x021DE360
	push {r4, r5, r6, lr}
	sub sp, #0x18
	ldr r0, _021DE5D0 ; =0x00000F58
	add r5, r1, #0
	add r2, r0, #0
	add r2, #0xa
	ldrh r2, [r5, r2]
	ldr r4, [r5, r0]
	cmp r2, #5
	bhi _021DE42E
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021DE380: ; jump table
	.short _021DE38C - _021DE380 - 2 ; case 0
	.short _021DE3F4 - _021DE380 - 2 ; case 1
	.short _021DE438 - _021DE380 - 2 ; case 2
	.short _021DE4A8 - _021DE380 - 2 ; case 3
	.short _021DE502 - _021DE380 - 2 ; case 4
	.short _021DE552 - _021DE380 - 2 ; case 5
_021DE38C:
	mov r0, #6
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	sub r0, #8
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	mov r2, #1
	ldr r0, _021DE5D4 ; =ov05_021DE1BC
	str r2, [sp, #0x10]
	str r0, [sp, #0x14]
	add r0, r4, #0
	mov r3, #0x1e
	bl ov05_021DD328
	ldr r0, _021DE5D8 ; =0x00006F6F
	mov r2, #0x41
	str r0, [sp]
	ldr r0, _021DE5DC ; =0x00006318
	add r1, r4, #0
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	ldr r0, _021DE5E0 ; =0x00000F64
	lsl r2, r2, #2
	ldrh r0, [r5, r0]
	add r1, #0x1c
	str r0, [sp, #0xc]
	ldr r3, [r5]
	add r0, r4, #0
	ldr r2, [r3, r2]
	add r0, #0x4c
	ldr r2, [r2, #0x44]
	mov r3, #3
	bl ov05_021DD420
	add r0, r4, #0
	mov r1, #8
	add r0, #0xb4
	str r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb8
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xbc
	str r1, [r0]
	ldr r0, _021DE5E4 ; =0x00000F62
	mov r1, #1
	strh r1, [r5, r0]
	b _021DE570
_021DE3F4:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DE416
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xb4
	str r1, [r0]
	b _021DE570
_021DE416:
	ldr r2, _021DE5E0 ; =0x00000F64
	add r0, r4, #0
	ldrh r2, [r5, r2]
	add r1, r4, #0
	add r0, #0x4c
	add r1, #0x1c
	bl ov05_021DD474
	cmp r0, #1
	bne _021DE42E
	cmp r6, #3
	beq _021DE430
_021DE42E:
	b _021DE570
_021DE430:
	ldr r0, _021DE5E4 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	b _021DE570
_021DE438:
	mov r2, #6
	mov r3, #3
	str r2, [sp]
	add r0, r3, #0
	str r3, [sp, #4]
	sub r0, #8
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, _021DE5D4 ; =ov05_021DE1BC
	str r0, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021DD328
	ldr r0, _021DE5E0 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DE47E
	mov r0, #0x41
	ldr r1, [r5]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r2, _021DE5D8 ; =0x00006F6F
	ldr r0, [r0, #0x44]
	ldr r3, _021DE5DC ; =0x00006318
	mov r1, #3
	str r0, [r4, #0x1c]
	bl ov05_021DD49C
	add r0, r4, #0
	add r0, #0x1c
	bl ov05_021DD5EC
_021DE47E:
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb8
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xbc
	str r1, [r0]
	mov r0, #3
	str r0, [sp]
	ldr r0, _021DE5E8 ; =ov05_021DE2E0
	ldr r1, _021DE5D4 ; =ov05_021DE1BC
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x14
	mov r3, #2
	bl ov05_021DD680
	ldr r0, _021DE5E4 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	b _021DE570
_021DE4A8:
	mov r0, #6
	ldrsh r1, [r4, r0]
	sub r0, r1, #1
	strh r0, [r4, #6]
	cmp r1, #0
	bgt _021DE4C4
	mov r1, #4
	ldrsh r1, [r4, r1]
	add r0, r5, #0
	bl ov05_021DE1BC
	mov r0, #8
	ldrsh r0, [r4, r0]
	strh r0, [r4, #6]
_021DE4C4:
	ldr r0, _021DE5EC ; =0x00000F66
	ldrh r0, [r5, r0]
	cmp r0, #5
	bne _021DE570
	mov r0, #2
	mvn r0, r0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x1e
	mov r3, #5
	bl ov05_021DD350
	ldr r0, _021DE5E0 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DE4F2
	add r0, r4, #0
	add r0, #0x1c
	mov r1, #1
	mov r2, #0
	bl ov05_021DD5B4
_021DE4F2:
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
	ldr r0, _021DE5E4 ; =0x00000F62
	mov r1, #4
	strh r1, [r5, r0]
	b _021DE570
_021DE502:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DE524
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xb4
	str r1, [r0]
	b _021DE570
_021DE524:
	ldr r0, _021DE5E0 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DE536
	add r0, r4, #0
	add r0, #0x1c
	bl ov05_021DD5D0
	b _021DE538
_021DE536:
	mov r0, #1
_021DE538:
	cmp r0, #1
	bne _021DE570
	cmp r6, #3
	bne _021DE570
	add r0, r5, #0
	ldr r1, [r5, #0x40]
	add r0, #0xc
	cmp r1, r0
	bne _021DE570
	ldr r0, _021DE5E4 ; =0x00000F62
	mov r1, #5
	strh r1, [r5, r0]
	b _021DE570
_021DE552:
	add r0, #0xc
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DE56A
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r0, [r4, #0x1c]
	mov r1, #1
	add r3, r2, #0
	bl ov05_021DBA40
_021DE56A:
	ldr r0, [r5, #4]
	bl ov05_021DCB6C
_021DE570:
	ldr r0, _021DE5E4 ; =0x00000F62
	ldrh r0, [r5, r0]
	cmp r0, #5
	beq _021DE5CA
	cmp r0, #0
	beq _021DE5CA
	add r0, r5, #0
	ldr r1, _021DE5E8 ; =ov05_021DE2E0
	add r0, #0xc
	bl ov05_021DD148
	mov r1, #0
	add r0, r5, #0
	add r2, r1, #0
	bl ov05_021DD2BC
	add r0, r5, #0
	bl ov05_021DD164
	add r0, r4, #0
	add r0, #0xbc
	ldr r0, [r0]
	add r0, r0, #6
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x18
	sub r1, r1, r2
	mov r0, #0x18
	ror r1, r0
	add r0, r4, #0
	add r1, r2, r1
	add r0, #0xbc
	str r1, [r0]
	add r4, #0xbc
	ldr r1, [r4]
	ldr r0, _021DE5F0 ; =0x000001FF
	add r2, r1, #0
	neg r1, r1
	and r2, r0
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	and r0, r1
	add r1, r2, #0
	orr r1, r0
	ldr r0, _021DE5F4 ; =0x04000018
	str r1, [r0]
_021DE5CA:
	add sp, #0x18
	pop {r4, r5, r6, pc}
	nop
_021DE5D0: .word 0x00000F58
_021DE5D4: .word ov05_021DE1BC
_021DE5D8: .word 0x00006F6F
_021DE5DC: .word 0x00006318
_021DE5E0: .word 0x00000F64
_021DE5E4: .word 0x00000F62
_021DE5E8: .word ov05_021DE2E0
_021DE5EC: .word 0x00000F66
_021DE5F0: .word 0x000001FF
_021DE5F4: .word 0x04000018

	thumb_func_start ov05_021DE5F8
ov05_021DE5F8: ; 0x021DE5F8
	push {r3, r4, r5, lr}
	sub sp, #0x10
	ldr r2, _021DE74C ; =0x00000F58
	add r4, r1, #0
	add r0, r2, #0
	add r0, #0xa
	ldrh r0, [r4, r0]
	ldr r5, [r4, r2]
	cmp r0, #5
	bls _021DE60E
	b _021DE746
_021DE60E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DE61A: ; jump table
	.short _021DE626 - _021DE61A - 2 ; case 0
	.short _021DE65E - _021DE61A - 2 ; case 1
	.short _021DE694 - _021DE61A - 2 ; case 2
	.short _021DE6C2 - _021DE61A - 2 ; case 3
	.short _021DE6EE - _021DE61A - 2 ; case 4
	.short _021DE728 - _021DE61A - 2 ; case 5
_021DE626:
	ldr r0, _021DE750 ; =0x0000716F
	add r2, #0xc
	str r0, [sp]
	ldr r0, _021DE754 ; =0x00006B5A
	add r1, r5, #0
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	ldrh r0, [r4, r2]
	mov r2, #0x41
	lsl r2, r2, #2
	str r0, [sp, #0xc]
	ldr r3, [r4]
	add r0, r5, #0
	ldr r2, [r3, r2]
	add r0, #0x30
	ldr r2, [r2, #0x44]
	mov r3, #3
	bl ov05_021DD420
	mov r0, #0x10
	add r5, #0x98
	str r0, [r5]
	ldr r0, _021DE758 ; =0x00000F62
	mov r1, #1
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021DE65E:
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	cmp r0, #0
	ble _021DE678
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	add r5, #0x98
	sub r0, r0, #1
	add sp, #0x10
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DE678:
	add r2, #0xc
	ldrh r2, [r4, r2]
	add r0, r5, #0
	add r0, #0x30
	add r1, r5, #0
	bl ov05_021DD474
	cmp r0, #1
	bne _021DE746
	ldr r0, _021DE758 ; =0x00000F62
	mov r1, #3
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021DE694:
	add r2, #0xc
	ldrh r0, [r4, r2]
	cmp r0, #0
	beq _021DE6B8
	mov r0, #0x41
	ldr r1, [r4]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r2, _021DE750 ; =0x0000716F
	ldr r0, [r0, #0x44]
	ldr r3, _021DE754 ; =0x00006B5A
	mov r1, #3
	str r0, [r5]
	bl ov05_021DD49C
	add r0, r5, #0
	bl ov05_021DD5EC
_021DE6B8:
	ldr r0, _021DE758 ; =0x00000F62
	mov r1, #3
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021DE6C2:
	add r0, r2, #0
	add r0, #0xe
	ldrh r0, [r4, r0]
	cmp r0, #5
	bne _021DE746
	add r2, #0xc
	ldrh r0, [r4, r2]
	cmp r0, #0
	beq _021DE6DE
	add r0, r5, #0
	mov r1, #2
	mov r2, #0
	bl ov05_021DD5B4
_021DE6DE:
	mov r0, #0x10
	add r5, #0x98
	str r0, [r5]
	ldr r0, _021DE758 ; =0x00000F62
	mov r1, #4
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021DE6EE:
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	cmp r0, #0
	ble _021DE708
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	add r5, #0x98
	sub r0, r0, #1
	add sp, #0x10
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DE708:
	add r2, #0xc
	ldrh r0, [r4, r2]
	cmp r0, #0
	beq _021DE718
	add r0, r5, #0
	bl ov05_021DD5D0
	b _021DE71A
_021DE718:
	mov r0, #1
_021DE71A:
	cmp r0, #1
	bne _021DE746
	ldr r0, _021DE758 ; =0x00000F62
	mov r1, #5
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021DE728:
	add r2, #0xc
	ldrh r0, [r4, r2]
	cmp r0, #0
	beq _021DE740
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r0, [r5]
	mov r1, #1
	add r3, r2, #0
	bl ov05_021DBA40
_021DE740:
	ldr r0, [r4, #4]
	bl ov05_021DCB6C
_021DE746:
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021DE74C: .word 0x00000F58
_021DE750: .word 0x0000716F
_021DE754: .word 0x00006B5A
_021DE758: .word 0x00000F62

	thumb_func_start ov05_021DE75C
ov05_021DE75C: ; 0x021DE75C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	ldr r2, _021DE8B0 ; =0x00000F58
	add r4, r1, #0
	add r0, r2, #0
	add r0, #0xa
	ldrh r0, [r4, r0]
	ldr r5, [r4, r2]
	cmp r0, #5
	bls _021DE772
	b _021DE8AA
_021DE772:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DE77E: ; jump table
	.short _021DE78A - _021DE77E - 2 ; case 0
	.short _021DE7C2 - _021DE77E - 2 ; case 1
	.short _021DE7F8 - _021DE77E - 2 ; case 2
	.short _021DE826 - _021DE77E - 2 ; case 3
	.short _021DE852 - _021DE77E - 2 ; case 4
	.short _021DE88C - _021DE77E - 2 ; case 5
_021DE78A:
	ldr r0, _021DE8B4 ; =0x0000658F
	add r2, #0xc
	str r0, [sp]
	ldr r0, _021DE8B8 ; =0x00006B5A
	add r1, r5, #0
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	ldrh r0, [r4, r2]
	mov r2, #0x41
	lsl r2, r2, #2
	str r0, [sp, #0xc]
	ldr r3, [r4]
	add r0, r5, #0
	ldr r2, [r3, r2]
	add r0, #0x30
	ldr r2, [r2, #0x44]
	mov r3, #3
	bl ov05_021DD420
	mov r0, #0x10
	add r5, #0x98
	str r0, [r5]
	ldr r0, _021DE8BC ; =0x00000F62
	mov r1, #1
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021DE7C2:
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	cmp r0, #0
	ble _021DE7DC
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	add r5, #0x98
	sub r0, r0, #1
	add sp, #0x10
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DE7DC:
	add r2, #0xc
	ldrh r2, [r4, r2]
	add r0, r5, #0
	add r0, #0x30
	add r1, r5, #0
	bl ov05_021DD474
	cmp r0, #1
	bne _021DE8AA
	ldr r0, _021DE8BC ; =0x00000F62
	mov r1, #3
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021DE7F8:
	add r2, #0xc
	ldrh r0, [r4, r2]
	cmp r0, #0
	beq _021DE81C
	mov r0, #0x41
	ldr r1, [r4]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r2, _021DE8B4 ; =0x0000658F
	ldr r0, [r0, #0x44]
	ldr r3, _021DE8B8 ; =0x00006B5A
	mov r1, #3
	str r0, [r5]
	bl ov05_021DD49C
	add r0, r5, #0
	bl ov05_021DD5EC
_021DE81C:
	ldr r0, _021DE8BC ; =0x00000F62
	mov r1, #3
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021DE826:
	add r0, r2, #0
	add r0, #0xe
	ldrh r0, [r4, r0]
	cmp r0, #5
	bne _021DE8AA
	add r2, #0xc
	ldrh r0, [r4, r2]
	cmp r0, #0
	beq _021DE842
	add r0, r5, #0
	mov r1, #2
	mov r2, #0
	bl ov05_021DD5B4
_021DE842:
	mov r0, #0x10
	add r5, #0x98
	str r0, [r5]
	ldr r0, _021DE8BC ; =0x00000F62
	mov r1, #4
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021DE852:
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	cmp r0, #0
	ble _021DE86C
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	add r5, #0x98
	sub r0, r0, #1
	add sp, #0x10
	str r0, [r5]
	pop {r3, r4, r5, pc}
_021DE86C:
	add r2, #0xc
	ldrh r0, [r4, r2]
	cmp r0, #0
	beq _021DE87C
	add r0, r5, #0
	bl ov05_021DD5D0
	b _021DE87E
_021DE87C:
	mov r0, #1
_021DE87E:
	cmp r0, #1
	bne _021DE8AA
	ldr r0, _021DE8BC ; =0x00000F62
	mov r1, #5
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021DE88C:
	add r2, #0xc
	ldrh r0, [r4, r2]
	cmp r0, #0
	beq _021DE8A4
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r0, [r5]
	mov r1, #1
	add r3, r2, #0
	bl ov05_021DBA40
_021DE8A4:
	ldr r0, [r4, #4]
	bl ov05_021DCB6C
_021DE8AA:
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021DE8B0: .word 0x00000F58
_021DE8B4: .word 0x0000658F
_021DE8B8: .word 0x00006B5A
_021DE8BC: .word 0x00000F62

	thumb_func_start ov05_021DE8C0
ov05_021DE8C0: ; 0x021DE8C0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	ldr r0, _021DEA58 ; =0x00000F58
	add r4, r1, #0
	add r1, r0, #0
	add r1, #0xa
	ldrh r1, [r4, r1]
	ldr r5, [r4, r0]
	cmp r1, #5
	bls _021DE8D6
	b _021DEA54
_021DE8D6:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021DE8E2: ; jump table
	.short _021DE8EE - _021DE8E2 - 2 ; case 0
	.short _021DE94C - _021DE8E2 - 2 ; case 1
	.short _021DE97A - _021DE8E2 - 2 ; case 2
	.short _021DE9C8 - _021DE8E2 - 2 ; case 3
	.short _021DE9FC - _021DE8E2 - 2 ; case 4
	.short _021DEA36 - _021DE8E2 - 2 ; case 5
_021DE8EE:
	ldr r1, _021DEA5C ; =0x00007A0F
	mov r2, #0x41
	str r1, [sp]
	ldr r1, _021DEA60 ; =0x00007FFF
	add r0, #0xc
	str r1, [sp, #4]
	mov r1, #2
	str r1, [sp, #8]
	ldrh r0, [r4, r0]
	add r1, r5, #0
	lsl r2, r2, #2
	str r0, [sp, #0xc]
	ldr r3, [r4]
	add r0, r5, #0
	ldr r2, [r3, r2]
	add r0, #0x44
	ldr r2, [r2, #0x44]
	add r1, #0x14
	mov r3, #5
	bl ov05_021DD420
	add r0, r5, #0
	mov r1, #0
	mov r2, #0x10
	mov r3, #0x1e
	bl ov05_021DC6EC
	mov r0, #0
	mov r1, #0x10
	bl ov05_021DC6D4
	ldr r1, _021DEA64 ; =0x0400000C
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #3
	orr r0, r2
	strh r0, [r1]
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, _021DEA68 ; =0x00000F62
	mov r1, #1
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021DE94C:
	add r0, r5, #0
	add r0, #0x14
	bl ov05_021DD5D0
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021DC6FC
	add r7, r0, #0
	ldr r0, [r5]
	mov r1, #0x10
	sub r1, r1, r0
	bl ov05_021DC6D4
	cmp r6, #1
	bne _021DEA54
	cmp r7, #1
	bne _021DEA54
	ldr r0, _021DEA68 ; =0x00000F62
	mov r1, #3
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021DE97A:
	add r0, #0xc
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _021DE9A0
	mov r0, #0x41
	ldr r1, [r4]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r2, _021DEA5C ; =0x00007A0F
	ldr r0, [r0, #0x44]
	ldr r3, _021DEA60 ; =0x00007FFF
	mov r1, #5
	str r0, [r5, #0x14]
	bl ov05_021DD49C
	add r5, #0x14
	add r0, r5, #0
	bl ov05_021DD5EC
_021DE9A0:
	mov r0, #0x10
	mov r1, #0
	bl ov05_021DC6D4
	ldr r1, _021DEA64 ; =0x0400000C
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #3
	orr r0, r2
	strh r0, [r1]
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, _021DEA68 ; =0x00000F62
	mov r1, #3
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021DE9C8:
	add r1, r0, #0
	add r1, #0xe
	ldrh r1, [r4, r1]
	cmp r1, #5
	bne _021DEA54
	add r0, #0xc
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _021DE9E6
	add r0, r5, #0
	add r0, #0x14
	mov r1, #1
	mov r2, #0
	bl ov05_021DD5B4
_021DE9E6:
	add r0, r5, #0
	mov r1, #0x10
	mov r2, #0
	mov r3, #0x1e
	bl ov05_021DC6EC
	ldr r0, _021DEA68 ; =0x00000F62
	mov r1, #4
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021DE9FC:
	add r0, #0xc
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _021DEA10
	add r0, r5, #0
	add r0, #0x14
	bl ov05_021DD5D0
	add r6, r0, #0
	b _021DEA12
_021DEA10:
	mov r6, #1
_021DEA12:
	add r0, r5, #0
	bl ov05_021DC6FC
	add r7, r0, #0
	ldr r0, [r5]
	mov r1, #0x10
	sub r1, r1, r0
	bl ov05_021DC6D4
	cmp r6, #1
	bne _021DEA54
	cmp r7, #1
	bne _021DEA54
	ldr r0, _021DEA68 ; =0x00000F62
	mov r1, #5
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021DEA36:
	add r0, #0xc
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _021DEA4E
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r0, [r5, #0x14]
	mov r1, #1
	add r3, r2, #0
	bl ov05_021DBA40
_021DEA4E:
	ldr r0, [r4, #4]
	bl ov05_021DCB6C
_021DEA54:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021DEA58: .word 0x00000F58
_021DEA5C: .word 0x00007A0F
_021DEA60: .word 0x00007FFF
_021DEA64: .word 0x0400000C
_021DEA68: .word 0x00000F62

	thumb_func_start ov05_021DEA6C
ov05_021DEA6C: ; 0x021DEA6C
	push {r4, r5, r6, lr}
	sub sp, #0x18
	ldr r0, _021DEC8C ; =0x00000F58
	add r5, r1, #0
	add r2, r0, #0
	add r2, #0xa
	ldrh r2, [r5, r2]
	ldr r4, [r5, r0]
	cmp r2, #5
	bhi _021DEB2E
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021DEA8C: ; jump table
	.short _021DEA98 - _021DEA8C - 2 ; case 0
	.short _021DEAF6 - _021DEA8C - 2 ; case 1
	.short _021DEB38 - _021DEA8C - 2 ; case 2
	.short _021DEB9C - _021DEA8C - 2 ; case 3
	.short _021DEBF4 - _021DEA8C - 2 ; case 4
	.short _021DEC42 - _021DEA8C - 2 ; case 5
_021DEA98:
	mov r0, #8
	str r0, [sp]
	mov r2, #1
	str r2, [sp, #4]
	sub r0, r2, #3
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, _021DEC90 ; =ov05_021DECAC
	mov r3, #0xf
	str r0, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021DD328
	ldr r0, _021DEC94 ; =0x00006EEF
	mov r2, #0x41
	str r0, [sp]
	ldr r0, _021DEC98 ; =0x0000169A
	lsl r2, r2, #2
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, _021DEC9C ; =0x00000F64
	add r1, r4, #0
	ldrh r0, [r5, r0]
	add r1, #0x1c
	str r0, [sp, #0xc]
	ldr r3, [r5]
	add r0, r4, #0
	ldr r2, [r3, r2]
	add r0, #0x4c
	ldr r2, [r2, #0x44]
	mov r3, #3
	bl ov05_021DD420
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
	add r4, #0xb8
	str r1, [r4]
	ldr r0, _021DECA0 ; =0x00000F62
	mov r1, #1
	strh r1, [r5, r0]
	b _021DEC60
_021DEAF6:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DEB16
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r4, #0xb4
	sub r0, r0, #1
	str r0, [r4]
	b _021DEC60
_021DEB16:
	ldr r2, _021DEC9C ; =0x00000F64
	add r0, r4, #0
	ldrh r2, [r5, r2]
	add r4, #0x1c
	add r0, #0x4c
	add r1, r4, #0
	bl ov05_021DD474
	cmp r0, #1
	bne _021DEB2E
	cmp r6, #3
	beq _021DEB30
_021DEB2E:
	b _021DEC60
_021DEB30:
	ldr r0, _021DECA0 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	b _021DEC60
_021DEB38:
	mov r2, #8
	mov r3, #1
	str r2, [sp]
	str r3, [sp, #4]
	sub r0, r3, #3
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, _021DEC90 ; =ov05_021DECAC
	str r0, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021DD328
	ldr r0, _021DEC9C ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DEB7C
	mov r0, #0x41
	ldr r1, [r5]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r2, _021DEC94 ; =0x00006EEF
	ldr r0, [r0, #0x44]
	ldr r3, _021DEC98 ; =0x0000169A
	mov r1, #3
	str r0, [r4, #0x1c]
	bl ov05_021DD49C
	add r0, r4, #0
	add r0, #0x1c
	bl ov05_021DD5EC
_021DEB7C:
	mov r0, #0
	add r4, #0xb8
	str r0, [r4]
	mov r3, #2
	ldr r0, _021DECA4 ; =ov05_021DEDB4
	str r3, [sp]
	str r0, [sp, #4]
	ldr r1, _021DEC90 ; =ov05_021DECAC
	add r0, r5, #0
	mov r2, #0x18
	bl ov05_021DD680
	ldr r0, _021DECA0 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	b _021DEC60
_021DEB9C:
	mov r0, #6
	ldrsh r1, [r4, r0]
	sub r0, r1, #1
	strh r0, [r4, #6]
	cmp r1, #0
	bgt _021DEBB8
	mov r1, #4
	ldrsh r1, [r4, r1]
	add r0, r5, #0
	bl ov05_021DECAC
	mov r0, #8
	ldrsh r0, [r4, r0]
	strh r0, [r4, #6]
_021DEBB8:
	ldr r0, _021DECA8 ; =0x00000F66
	ldrh r0, [r5, r0]
	cmp r0, #5
	bne _021DEC60
	mov r0, #2
	mvn r0, r0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0
	mov r2, #0xf
	mov r3, #2
	bl ov05_021DD350
	ldr r0, _021DEC9C ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DEBE6
	add r0, r4, #0
	add r0, #0x1c
	mov r1, #1
	mov r2, #0
	bl ov05_021DD5B4
_021DEBE6:
	mov r0, #0x1f
	add r4, #0xb4
	str r0, [r4]
	ldr r0, _021DECA0 ; =0x00000F62
	mov r1, #4
	strh r1, [r5, r0]
	b _021DEC60
_021DEBF4:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DEC14
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r4, #0xb4
	sub r0, r0, #1
	str r0, [r4]
	b _021DEC60
_021DEC14:
	ldr r0, _021DEC9C ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DEC26
	add r4, #0x1c
	add r0, r4, #0
	bl ov05_021DD5D0
	b _021DEC28
_021DEC26:
	mov r0, #1
_021DEC28:
	cmp r0, #1
	bne _021DEC60
	cmp r6, #3
	bne _021DEC60
	add r0, r5, #0
	ldr r1, [r5, #0x40]
	add r0, #0xc
	cmp r1, r0
	bne _021DEC60
	ldr r0, _021DECA0 ; =0x00000F62
	mov r1, #5
	strh r1, [r5, r0]
	b _021DEC60
_021DEC42:
	add r0, #0xc
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DEC5A
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r0, [r4, #0x1c]
	mov r1, #1
	add r3, r2, #0
	bl ov05_021DBA40
_021DEC5A:
	ldr r0, [r5, #4]
	bl ov05_021DCB6C
_021DEC60:
	ldr r0, _021DECA0 ; =0x00000F62
	ldrh r0, [r5, r0]
	cmp r0, #5
	beq _021DEC86
	cmp r0, #0
	beq _021DEC86
	add r0, r5, #0
	ldr r1, _021DECA4 ; =ov05_021DEDB4
	add r0, #0xc
	bl ov05_021DD148
	mov r1, #0
	add r0, r5, #0
	add r2, r1, #0
	bl ov05_021DD2BC
	add r0, r5, #0
	bl ov05_021DD164
_021DEC86:
	add sp, #0x18
	pop {r4, r5, r6, pc}
	nop
_021DEC8C: .word 0x00000F58
_021DEC90: .word ov05_021DECAC
_021DEC94: .word 0x00006EEF
_021DEC98: .word 0x0000169A
_021DEC9C: .word 0x00000F64
_021DECA0: .word 0x00000F62
_021DECA4: .word ov05_021DEDB4
_021DECA8: .word 0x00000F66

	thumb_func_start ov05_021DECAC
ov05_021DECAC: ; 0x021DECAC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r1, [sp, #4]
	ldr r1, _021DEDA0 ; =0x00000F58
	str r0, [sp]
	ldr r4, [r0, r1]
	mov r1, #5
	add r0, r4, #0
	add r0, #0xb8
	ldr r0, [r0]
	lsl r1, r1, #6
	add r0, r0, #1
	bl _s32_div_f
	add r0, r4, #0
	add r0, #0xb8
	str r1, [r0]
	add r4, #0xb8
	ldr r0, [r4]
	mov r1, #0x28
	bl _s32_div_f
	mov r1, #0
	str r1, [sp, #8]
	ldr r1, [sp, #4]
	cmp r1, #0
	ble _021DED9A
	lsl r6, r0, #2
_021DECE4:
	ldr r0, [sp]
	mov r1, #0x20
	bl ov05_021DD048
	add r4, r0, #0
	beq _021DED9A
	ldr r5, [r4, #8]
	mov r0, #0
	str r0, [r5]
	bl MTRandom
	mov r1, #0x14
	bl _u32_div_f
	add r1, #0xf
	str r1, [r5, #4]
	sub r1, #0xf
	add r0, r1, #0
	mov r1, #6
	bl _s32_div_f
	mov r1, #3
	sub r7, r1, r0
	ldr r1, _021DEDA4 ; =ov05_021F687C
	add r0, r7, #1
	ldr r1, [r1, r6]
	mul r1, r0
	str r1, [r5, #8]
	ldr r1, _021DEDA8 ; =ov05_021F683C
	ldr r1, [r1, r6]
	mul r1, r0
	str r1, [r5, #0x10]
	mov r0, #0
	str r0, [r5, #0xc]
	ldr r0, _021DEDA8 ; =ov05_021F683C
	ldr r0, [r0, r6]
	str r0, [r5, #0x14]
	bl MTRandom
	mov r1, #0xfa
	lsl r1, r1, #2
	bl _u32_div_f
	ldr r0, _021DEDAC ; =0x00000309
	cmp r1, r0
	bne _021DED4E
	ldr r1, [r5, #8]
	mov r7, #4
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	add r0, r1, r0
	str r0, [r5, #8]
_021DED4E:
	lsl r1, r7, #0x10
	ldr r0, [r4, #4]
	lsr r1, r1, #0x10
	bl sub_02020208
	add r0, sp, #0xc
	add r1, r4, #0
	bl ov05_021DD168
	bl MTRandom
	mov r1, #0x18
	bl _u32_div_f
	ldr r0, _021DEDB0 ; =0x00000106
	add r0, r1, r0
	str r0, [sp, #0xc]
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	bl MTRandom
	mov r1, #0xc0
	bl _u32_div_f
	sub r1, #0x40
	str r1, [sp, #0x10]
	lsl r0, r1, #0xc
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, sp, #0xc
	bl ov05_021DC4FC
	ldr r0, [sp, #8]
	add r1, r0, #1
	ldr r0, [sp, #4]
	str r1, [sp, #8]
	cmp r1, r0
	blt _021DECE4
_021DED9A:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DEDA0: .word 0x00000F58
_021DEDA4: .word ov05_021F687C
_021DEDA8: .word ov05_021F683C
_021DEDAC: .word 0x00000309
_021DEDB0: .word 0x00000106

	thumb_func_start ov05_021DEDB4
ov05_021DEDB4: ; 0x021DEDB4
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r0, sp, #0
	add r1, r5, #0
	ldr r4, [r5, #8]
	bl ov05_021DD168
	add r3, sp, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021DEDDE
	cmp r0, #1
	beq _021DEE22
	add sp, #0x18
	pop {r3, r4, r5, pc}
_021DEDDE:
	ldr r0, [r4, #0x10]
	ldr r1, [sp, #0xc]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0xc]
	ldr r0, [r4, #8]
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x10]
	ldr r0, [r4]
	mov r1, #5
	bl _s32_div_f
	cmp r1, #0
	bne _021DEE06
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x14]
	add r0, r1, r0
	str r0, [r4, #0x10]
_021DEE06:
	ldr r1, [r4]
	add r0, r1, #1
	str r0, [r4]
	ldr r0, [r4, #4]
	cmp r1, r0
	ble _021DEE16
	mov r0, #1
	str r0, [r4, #0xc]
_021DEE16:
	ldr r0, [r5, #4]
	add r1, sp, #0xc
	bl ov05_021DC4FC
	add sp, #0x18
	pop {r3, r4, r5, pc}
_021DEE22:
	add r0, r5, #0
	bl ov05_021DD100
	add sp, #0x18
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021DEE2C
ov05_021DEE2C: ; 0x021DEE2C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	ldr r0, _021DF0F0 ; =0x00000F58
	add r5, r1, #0
	add r2, r0, #0
	add r2, #0xa
	ldrh r2, [r5, r2]
	ldr r4, [r5, r0]
	cmp r2, #5
	bhi _021DEEFE
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021DEE4C: ; jump table
	.short _021DEE58 - _021DEE4C - 2 ; case 0
	.short _021DEEC4 - _021DEE4C - 2 ; case 1
	.short _021DEF10 - _021DEE4C - 2 ; case 2
	.short _021DEF8A - _021DEE4C - 2 ; case 3
	.short _021DF01E - _021DEE4C - 2 ; case 4
	.short _021DF06C - _021DEE4C - 2 ; case 5
_021DEE58:
	mov r0, #8
	str r0, [sp]
	mov r2, #1
	str r2, [sp, #4]
	sub r0, r2, #3
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, _021DF0F4 ; =ov05_021DECAC
	mov r3, #0xf
	str r0, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021DD328
	ldr r0, _021DF0F8 ; =0x00006EEF
	mov r2, #0x41
	str r0, [sp]
	ldr r0, _021DF0FC ; =0x0000169A
	lsl r2, r2, #2
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, _021DF100 ; =0x00000F64
	add r1, r4, #0
	ldrh r0, [r5, r0]
	add r1, #0x1c
	str r0, [sp, #0xc]
	ldr r3, [r5]
	add r0, r4, #0
	ldr r2, [r3, r2]
	add r0, #0x4c
	ldr r2, [r2, #0x44]
	mov r3, #3
	bl ov05_021DD420
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xb8
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xbc
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc0
	str r1, [r0]
	ldr r0, _021DF104 ; =0x00000F62
	mov r1, #1
	strh r1, [r5, r0]
	b _021DF08A
_021DEEC4:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DEEE6
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xb4
	str r1, [r0]
	b _021DF08A
_021DEEE6:
	ldr r2, _021DF100 ; =0x00000F64
	add r0, r4, #0
	ldrh r2, [r5, r2]
	add r1, r4, #0
	add r0, #0x4c
	add r1, #0x1c
	bl ov05_021DD474
	cmp r0, #1
	bne _021DEEFE
	cmp r6, #3
	beq _021DEF00
_021DEEFE:
	b _021DF08A
_021DEF00:
	ldr r0, _021DF104 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	b _021DF08A
_021DEF10:
	mov r2, #8
	mov r3, #1
	str r2, [sp]
	str r3, [sp, #4]
	sub r0, r3, #3
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, _021DF0F4 ; =ov05_021DECAC
	str r0, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021DD328
	ldr r0, _021DF100 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DEF54
	mov r0, #0x41
	ldr r1, [r5]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r2, _021DF0F8 ; =0x00006EEF
	ldr r0, [r0, #0x44]
	ldr r3, _021DF0FC ; =0x0000169A
	mov r1, #3
	str r0, [r4, #0x1c]
	bl ov05_021DD49C
	add r0, r4, #0
	add r0, #0x1c
	bl ov05_021DD5EC
_021DEF54:
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb8
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xbc
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc0
	str r1, [r0]
	mov r3, #2
	ldr r0, _021DF108 ; =ov05_021DEDB4
	str r3, [sp]
	str r0, [sp, #4]
	ldr r1, _021DF0F4 ; =ov05_021DECAC
	add r0, r5, #0
	mov r2, #0x18
	bl ov05_021DD680
	ldr r0, _021DF104 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	b _021DF08A
_021DEF8A:
	mov r0, #6
	ldrsh r1, [r4, r0]
	sub r0, r1, #1
	strh r0, [r4, #6]
	cmp r1, #0
	bgt _021DEFDA
	add r0, r4, #0
	add r0, #0xb8
	ldr r0, [r0]
	mov r1, #0x28
	bl _s32_div_f
	lsl r1, r0, #2
	ldr r0, _021DF10C ; =ov05_021F681C
	ldr r1, [r0, r1]
	add r0, r4, #0
	add r0, #0xc0
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc0
	ldr r1, [r0]
	mov r0, #5
	mvn r0, r0
	cmp r1, r0
	bgt _021DEFCA
	mov r1, #4
	ldrsh r1, [r4, r1]
	add r0, r5, #0
	lsl r1, r1, #1
	bl ov05_021DECAC
	b _021DEFD4
_021DEFCA:
	mov r1, #4
	ldrsh r1, [r4, r1]
	add r0, r5, #0
	bl ov05_021DECAC
_021DEFD4:
	mov r0, #8
	ldrsh r0, [r4, r0]
	strh r0, [r4, #6]
_021DEFDA:
	ldr r0, _021DF110 ; =0x00000F66
	ldrh r0, [r5, r0]
	cmp r0, #5
	bne _021DF08A
	mov r0, #2
	mvn r0, r0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0
	mov r2, #0xf
	mov r3, #2
	bl ov05_021DD350
	ldr r0, _021DF100 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DF008
	add r0, r4, #0
	add r0, #0x1c
	mov r1, #1
	mov r2, #0
	bl ov05_021DD5B4
_021DF008:
	add r0, r4, #0
	mov r1, #0x1f
	add r0, #0xb4
	str r1, [r0]
	ldr r1, _021DF104 ; =0x00000F62
	mov r0, #4
	strh r0, [r5, r1]
	mov r1, #0
	bl GX_EngineAToggleLayers
	b _021DF08A
_021DF01E:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DF040
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xb4
	str r1, [r0]
	b _021DF08A
_021DF040:
	ldr r0, _021DF100 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DF052
	add r0, r4, #0
	add r0, #0x1c
	bl ov05_021DD5D0
	add r7, r0, #0
_021DF052:
	cmp r7, #1
	bne _021DF08A
	cmp r6, #3
	bne _021DF08A
	add r0, r5, #0
	ldr r1, [r5, #0x40]
	add r0, #0xc
	cmp r1, r0
	bne _021DF08A
	ldr r0, _021DF104 ; =0x00000F62
	mov r1, #5
	strh r1, [r5, r0]
	b _021DF08A
_021DF06C:
	add r0, #0xc
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DF084
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r0, [r4, #0x1c]
	mov r1, #1
	add r3, r2, #0
	bl ov05_021DBA40
_021DF084:
	ldr r0, [r5, #4]
	bl ov05_021DCB6C
_021DF08A:
	ldr r0, _021DF104 ; =0x00000F62
	ldrh r0, [r5, r0]
	cmp r0, #5
	beq _021DF0EC
	cmp r0, #0
	beq _021DF0EC
	add r0, r5, #0
	ldr r1, _021DF108 ; =ov05_021DEDB4
	add r0, #0xc
	bl ov05_021DD148
	add r0, r5, #0
	add r1, sp, #0x1c
	add r2, sp, #0x18
	bl ov05_021DD2BC
	add r0, r5, #0
	bl ov05_021DD164
	add r0, r4, #0
	add r0, #0xbc
	ldr r0, [r0]
	add r0, r0, #6
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x18
	sub r1, r1, r2
	mov r0, #0x18
	ror r1, r0
	add r0, r4, #0
	add r1, r2, r1
	add r0, #0xbc
	str r1, [r0]
	add r4, #0xbc
	ldr r3, [r4]
	ldr r0, [sp, #0x1c]
	lsl r1, r3, #1
	sub r1, r1, r0
	add r2, r1, #0
	ldr r1, [sp, #0x18]
	ldr r0, _021DF114 ; =0x000001FF
	sub r1, r1, r3
	and r2, r0
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	and r0, r1
	add r1, r2, #0
	orr r1, r0
	ldr r0, _021DF118 ; =0x04000018
	str r1, [r0]
_021DF0EC:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021DF0F0: .word 0x00000F58
_021DF0F4: .word ov05_021DECAC
_021DF0F8: .word 0x00006EEF
_021DF0FC: .word 0x0000169A
_021DF100: .word 0x00000F64
_021DF104: .word 0x00000F62
_021DF108: .word ov05_021DEDB4
_021DF10C: .word ov05_021F681C
_021DF110: .word 0x00000F66
_021DF114: .word 0x000001FF
_021DF118: .word 0x04000018

	thumb_func_start ov05_021DF11C
ov05_021DF11C: ; 0x021DF11C
	push {r4, r5, r6, lr}
	sub sp, #0x18
	ldr r0, _021DF3BC ; =0x00000F58
	add r5, r1, #0
	add r2, r0, #0
	add r2, #0xa
	ldrh r2, [r5, r2]
	ldr r4, [r5, r0]
	cmp r2, #5
	bhi _021DF1EA
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021DF13C: ; jump table
	.short _021DF148 - _021DF13C - 2 ; case 0
	.short _021DF1B0 - _021DF13C - 2 ; case 1
	.short _021DF1FC - _021DF13C - 2 ; case 2
	.short _021DF270 - _021DF13C - 2 ; case 3
	.short _021DF2F8 - _021DF13C - 2 ; case 4
	.short _021DF348 - _021DF13C - 2 ; case 5
_021DF148:
	mov r0, #0xa
	str r0, [sp]
	mov r2, #1
	str r2, [sp, #4]
	sub r0, r2, #5
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	mov r0, #3
	str r0, [sp, #0x10]
	ldr r0, _021DF3C0 ; =ov05_021DF3E8
	mov r3, #0x1e
	str r0, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021DD328
	ldr r0, _021DF3C4 ; =0x00006B6F
	mov r2, #0x41
	str r0, [sp]
	ldr r0, _021DF3C8 ; =0x00006318
	lsl r2, r2, #2
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, _021DF3CC ; =0x00000F64
	add r1, r4, #0
	ldrh r0, [r5, r0]
	add r1, #0x1c
	str r0, [sp, #0xc]
	ldr r3, [r5]
	add r0, r4, #0
	ldr r2, [r3, r2]
	add r0, #0x4c
	ldr r2, [r2, #0x44]
	mov r3, #3
	bl ov05_021DD420
	add r0, r4, #0
	mov r1, #0x10
	add r0, #0xb4
	str r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb8
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xbc
	str r1, [r0]
	ldr r0, _021DF3D0 ; =0x00000F62
	mov r1, #1
	strh r1, [r5, r0]
	b _021DF366
_021DF1B0:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DF1D2
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xb4
	str r1, [r0]
	b _021DF366
_021DF1D2:
	ldr r2, _021DF3CC ; =0x00000F64
	add r0, r4, #0
	ldrh r2, [r5, r2]
	add r1, r4, #0
	add r0, #0x4c
	add r1, #0x1c
	bl ov05_021DD474
	cmp r0, #1
	bne _021DF1EA
	cmp r6, #3
	beq _021DF1EC
_021DF1EA:
	b _021DF366
_021DF1EC:
	ldr r0, _021DF3D0 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	b _021DF366
_021DF1FC:
	mov r2, #0xa
	mov r3, #1
	str r2, [sp]
	str r3, [sp, #4]
	sub r0, r3, #5
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	mov r0, #3
	str r0, [sp, #0x10]
	ldr r0, _021DF3C0 ; =ov05_021DF3E8
	str r0, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021DD328
	ldr r0, _021DF3CC ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DF240
	mov r0, #0x41
	ldr r1, [r5]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r2, _021DF3C4 ; =0x00006B6F
	ldr r0, [r0, #0x44]
	ldr r3, _021DF3C8 ; =0x00006318
	mov r1, #3
	str r0, [r4, #0x1c]
	bl ov05_021DD49C
	add r0, r4, #0
	add r0, #0x1c
	bl ov05_021DD5EC
_021DF240:
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb8
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xbc
	str r1, [r0]
	mov r3, #2
	ldr r0, _021DF3D4 ; =ov05_021DF500
	str r3, [sp]
	str r0, [sp, #4]
	ldr r1, _021DF3C0 ; =ov05_021DF3E8
	add r0, r5, #0
	mov r2, #0x14
	bl ov05_021DD680
	ldr r0, _021DF3D0 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	b _021DF366
_021DF270:
	mov r1, #6
	ldrsh r2, [r4, r1]
	sub r0, r2, #1
	strh r0, [r4, #6]
	cmp r2, #0
	bgt _021DF2B4
	add r0, r4, #0
	add r0, #0xb8
	ldr r2, [r0]
	sub r1, #0xe
	asr r0, r2, #8
	lsr r0, r0, #0x17
	add r0, r2, r0
	asr r0, r0, #9
	lsl r2, r0, #2
	ldr r0, _021DF3D8 ; =ov05_021F67F8
	ldr r0, [r0, r2]
	cmp r0, r1
	bgt _021DF2A4
	mov r1, #4
	ldrsh r1, [r4, r1]
	add r0, r5, #0
	lsl r1, r1, #1
	bl ov05_021DF3E8
	b _021DF2AE
_021DF2A4:
	mov r1, #4
	ldrsh r1, [r4, r1]
	add r0, r5, #0
	bl ov05_021DF3E8
_021DF2AE:
	mov r0, #8
	ldrsh r0, [r4, r0]
	strh r0, [r4, #6]
_021DF2B4:
	ldr r0, _021DF3DC ; =0x00000F66
	ldrh r0, [r5, r0]
	cmp r0, #5
	bne _021DF366
	mov r0, #3
	mvn r0, r0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0
	mov r2, #0xc
	mov r3, #4
	bl ov05_021DD350
	ldr r0, _021DF3CC ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DF2E2
	add r0, r4, #0
	add r0, #0x1c
	mov r1, #1
	mov r2, #0
	bl ov05_021DD5B4
_021DF2E2:
	add r0, r4, #0
	mov r1, #0x14
	add r0, #0xb4
	str r1, [r0]
	ldr r1, _021DF3D0 ; =0x00000F62
	mov r0, #4
	strh r0, [r5, r1]
	mov r1, #0
	bl GX_EngineAToggleLayers
	b _021DF366
_021DF2F8:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DF31A
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xb4
	str r1, [r0]
	b _021DF366
_021DF31A:
	ldr r0, _021DF3CC ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DF32C
	add r0, r4, #0
	add r0, #0x1c
	bl ov05_021DD5D0
	b _021DF32E
_021DF32C:
	mov r0, #1
_021DF32E:
	cmp r0, #1
	bne _021DF366
	cmp r6, #3
	bne _021DF366
	add r0, r5, #0
	ldr r1, [r5, #0x40]
	add r0, #0xc
	cmp r1, r0
	bne _021DF366
	ldr r0, _021DF3D0 ; =0x00000F62
	mov r1, #5
	strh r1, [r5, r0]
	b _021DF366
_021DF348:
	add r0, #0xc
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DF360
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r0, [r4, #0x1c]
	mov r1, #1
	add r3, r2, #0
	bl ov05_021DBA40
_021DF360:
	ldr r0, [r5, #4]
	bl ov05_021DCB6C
_021DF366:
	ldr r0, _021DF3D0 ; =0x00000F62
	ldrh r0, [r5, r0]
	cmp r0, #5
	beq _021DF3B8
	cmp r0, #0
	beq _021DF3B8
	add r0, r5, #0
	ldr r1, _021DF3D4 ; =ov05_021DF500
	add r0, #0xc
	bl ov05_021DD148
	add r0, r5, #0
	bl ov05_021DD164
	add r0, r4, #0
	add r0, #0xbc
	ldr r0, [r0]
	add r0, #0xc
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x18
	sub r1, r1, r2
	mov r0, #0x18
	ror r1, r0
	add r0, r4, #0
	add r1, r2, r1
	add r0, #0xbc
	str r1, [r0]
	add r4, #0xbc
	ldr r3, [r4]
	ldr r0, _021DF3E0 ; =0x000001FF
	lsl r1, r3, #1
	add r2, r1, #0
	neg r1, r3
	and r2, r0
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	and r0, r1
	add r1, r2, #0
	orr r1, r0
	ldr r0, _021DF3E4 ; =0x04000018
	str r1, [r0]
_021DF3B8:
	add sp, #0x18
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021DF3BC: .word 0x00000F58
_021DF3C0: .word ov05_021DF3E8
_021DF3C4: .word 0x00006B6F
_021DF3C8: .word 0x00006318
_021DF3CC: .word 0x00000F64
_021DF3D0: .word 0x00000F62
_021DF3D4: .word ov05_021DF500
_021DF3D8: .word ov05_021F67F8
_021DF3DC: .word 0x00000F66
_021DF3E0: .word 0x000001FF
_021DF3E4: .word 0x04000018

	thumb_func_start ov05_021DF3E8
ov05_021DF3E8: ; 0x021DF3E8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	ldr r2, _021DF4F4 ; =0x00000F58
	str r0, [sp]
	ldr r0, [r0, r2]
	add r2, r0, #0
	add r2, #0xb8
	ldr r2, [r2]
	add r3, r2, #1
	add r2, r0, #0
	add r2, #0xb8
	str r3, [r2]
	add r2, r0, #0
	add r2, #0xb8
	ldr r3, [r2]
	mov r2, #2
	lsl r2, r2, #0xa
	cmp r3, r2
	blt _021DF416
	add r2, r0, #0
	mov r3, #0
	add r2, #0xb8
	str r3, [r2]
_021DF416:
	add r0, #0xb8
	ldr r2, [r0]
	asr r0, r2, #8
	lsr r0, r0, #0x17
	add r0, r2, r0
	asr r2, r0, #9
	mov r0, #0
	str r0, [sp, #8]
	lsl r0, r1, #2
	str r0, [sp, #4]
	cmp r0, #0
	ble _021DF4EE
	lsl r4, r2, #2
_021DF430:
	ldr r0, [sp]
	mov r1, #0x20
	bl ov05_021DD048
	add r6, r0, #0
	beq _021DF4EE
	ldr r5, [r6, #8]
	mov r0, #0
	str r0, [r5]
	bl MTRandom
	mov r1, #6
	bl _u32_div_f
	add r1, #0x12
	str r1, [r5, #4]
	bl MTRandom
	add r7, r0, #0
	mov r1, #3
	and r7, r1
	lsl r1, r7, #0x10
	ldr r0, [r6, #4]
	lsr r1, r1, #0x10
	bl sub_02020208
	ldr r1, _021DF4F8 ; =ov05_021F67F8
	add r0, r7, #1
	ldr r1, [r1, r4]
	mul r1, r0
	str r1, [r5, #0x10]
	ldr r1, _021DF4FC ; =ov05_021F67E8
	ldr r1, [r1, r4]
	mul r1, r0
	mov r0, #0
	str r1, [r5, #8]
	str r0, [r5, #0xc]
	cmp r7, #3
	bne _021DF492
	ldr r0, _021DF4F8 ; =ov05_021F67F8
	ldr r1, [r5, #0x10]
	ldr r0, [r0, r4]
	add r0, r1, r0
	str r0, [r5, #0x10]
	ldr r0, _021DF4FC ; =ov05_021F67E8
	ldr r1, [r5, #8]
	ldr r0, [r0, r4]
	add r0, r1, r0
	str r0, [r5, #8]
_021DF492:
	ldr r0, _021DF4F8 ; =ov05_021F67F8
	add r1, r6, #0
	ldr r0, [r0, r4]
	str r0, [r5, #0x14]
	add r0, sp, #0xc
	bl ov05_021DD168
	add r3, sp, #0xc
	ldmia r3!, {r0, r1}
	add r2, sp, #0x18
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	bl MTRandom
	mov r1, #0x18
	bl _u32_div_f
	mov r0, #1
	lsl r0, r0, #8
	add r0, r1, r0
	str r0, [sp, #0x18]
	bl MTRandom
	mov r1, #0xa8
	bl _u32_div_f
	ldr r0, [sp, #0x18]
	sub r1, #0x20
	lsl r0, r0, #0xc
	str r0, [sp, #0x18]
	str r1, [sp, #0x1c]
	lsl r0, r1, #0xc
	str r0, [sp, #0x1c]
	mov r0, #0
	str r0, [sp, #0x20]
	ldr r0, [r6, #4]
	add r1, sp, #0x18
	bl ov05_021DC4FC
	ldr r0, [sp, #8]
	add r1, r0, #1
	ldr r0, [sp, #4]
	str r1, [sp, #8]
	cmp r1, r0
	blt _021DF430
_021DF4EE:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_021DF4F4: .word 0x00000F58
_021DF4F8: .word ov05_021F67F8
_021DF4FC: .word ov05_021F67E8

	thumb_func_start ov05_021DF500
ov05_021DF500: ; 0x021DF500
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r0, sp, #0
	add r1, r5, #0
	ldr r4, [r5, #8]
	bl ov05_021DD168
	add r3, sp, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021DF52A
	cmp r0, #1
	beq _021DF57C
	add sp, #0x18
	pop {r3, r4, r5, pc}
_021DF52A:
	ldr r0, [r4, #0x10]
	ldr r1, [sp, #0xc]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0xc]
	ldr r0, [r4, #8]
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x10]
	ldr r1, [r4]
	add r0, r1, #1
	str r0, [r4]
	ldr r0, [r4, #4]
	cmp r1, r0
	ble _021DF54E
	mov r0, #1
	str r0, [r4, #0xc]
_021DF54E:
	ldr r0, [r4]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	bne _021DF570
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x14]
	add r0, r1, r0
	str r0, [r4, #0x10]
	ldr r0, [r4, #8]
	cmp r0, #1
	ble _021DF570
	sub r0, r0, #1
	str r0, [r4, #8]
_021DF570:
	ldr r0, [r5, #4]
	add r1, sp, #0xc
	bl ov05_021DC4FC
	add sp, #0x18
	pop {r3, r4, r5, pc}
_021DF57C:
	add r0, r5, #0
	bl ov05_021DD100
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021DF588
ov05_021DF588: ; 0x021DF588
	push {r4, r5, r6, lr}
	sub sp, #0x18
	ldr r0, _021DF794 ; =0x00000F58
	add r5, r1, #0
	add r2, r0, #0
	add r2, #0xa
	ldrh r2, [r5, r2]
	ldr r4, [r5, r0]
	cmp r2, #5
	bhi _021DF642
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021DF5A8: ; jump table
	.short _021DF5B4 - _021DF5A8 - 2 ; case 0
	.short _021DF60A - _021DF5A8 - 2 ; case 1
	.short _021DF64C - _021DF5A8 - 2 ; case 2
	.short _021DF6AA - _021DF5A8 - 2 ; case 3
	.short _021DF702 - _021DF5A8 - 2 ; case 4
	.short _021DF74C - _021DF5A8 - 2 ; case 5
_021DF5B4:
	mov r0, #0x14
	str r0, [sp]
	mov r2, #2
	str r2, [sp, #4]
	sub r0, r2, #4
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	ldr r0, _021DF798 ; =ov05_021DF7B4
	str r2, [sp, #0x10]
	str r0, [sp, #0x14]
	add r0, r4, #0
	mov r3, #0x10
	bl ov05_021DD328
	ldr r0, _021DF79C ; =0x0000716F
	mov r2, #0x41
	str r0, [sp]
	ldr r0, _021DF7A0 ; =0x00006B5A
	lsl r2, r2, #2
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, _021DF7A4 ; =0x00000F64
	add r1, r4, #0
	ldrh r0, [r5, r0]
	add r1, #0x1c
	str r0, [sp, #0xc]
	ldr r3, [r5]
	add r0, r4, #0
	ldr r2, [r3, r2]
	add r0, #0x4c
	ldr r2, [r2, #0x44]
	mov r3, #3
	bl ov05_021DD420
	mov r0, #0
	add r4, #0xb4
	str r0, [r4]
	ldr r0, _021DF7A8 ; =0x00000F62
	mov r1, #1
	strh r1, [r5, r0]
	b _021DF76A
_021DF60A:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DF62A
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r4, #0xb4
	sub r0, r0, #1
	str r0, [r4]
	b _021DF76A
_021DF62A:
	ldr r2, _021DF7A4 ; =0x00000F64
	add r0, r4, #0
	ldrh r2, [r5, r2]
	add r4, #0x1c
	add r0, #0x4c
	add r1, r4, #0
	bl ov05_021DD474
	cmp r0, #1
	bne _021DF642
	cmp r6, #3
	beq _021DF644
_021DF642:
	b _021DF76A
_021DF644:
	ldr r0, _021DF7A8 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	b _021DF76A
_021DF64C:
	mov r2, #0x14
	mov r3, #2
	str r2, [sp]
	str r3, [sp, #4]
	sub r0, r3, #4
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	ldr r0, _021DF798 ; =ov05_021DF7B4
	str r3, [sp, #0x10]
	str r0, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021DD328
	ldr r0, _021DF7A4 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DF68E
	mov r0, #0x41
	ldr r1, [r5]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r2, _021DF79C ; =0x0000716F
	ldr r0, [r0, #0x44]
	ldr r3, _021DF7A0 ; =0x00006B5A
	mov r1, #3
	str r0, [r4, #0x1c]
	bl ov05_021DD49C
	add r4, #0x1c
	add r0, r4, #0
	bl ov05_021DD5EC
_021DF68E:
	mov r0, #1
	str r0, [sp]
	ldr r0, _021DF7AC ; =ov05_021DF8E4
	ldr r1, _021DF798 ; =ov05_021DF7B4
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x14
	mov r3, #0xa
	bl ov05_021DD680
	ldr r0, _021DF7A8 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	b _021DF76A
_021DF6AA:
	mov r0, #6
	ldrsh r1, [r4, r0]
	sub r0, r1, #1
	strh r0, [r4, #6]
	cmp r1, #0
	bgt _021DF6C6
	mov r1, #4
	ldrsh r1, [r4, r1]
	add r0, r5, #0
	bl ov05_021DF7B4
	mov r0, #8
	ldrsh r0, [r4, r0]
	strh r0, [r4, #6]
_021DF6C6:
	ldr r0, _021DF7B0 ; =0x00000F66
	ldrh r0, [r5, r0]
	cmp r0, #5
	bne _021DF76A
	mov r0, #9
	mvn r0, r0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x10
	mov r3, #6
	bl ov05_021DD350
	ldr r0, _021DF7A4 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DF6F4
	add r0, r4, #0
	add r0, #0x1c
	mov r1, #1
	mov r2, #0
	bl ov05_021DD5B4
_021DF6F4:
	mov r0, #0x14
	add r4, #0xb4
	str r0, [r4]
	ldr r0, _021DF7A8 ; =0x00000F62
	mov r1, #4
	strh r1, [r5, r0]
	b _021DF76A
_021DF702:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DF722
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r4, #0xb4
	sub r0, r0, #1
	str r0, [r4]
	b _021DF76A
_021DF722:
	ldr r2, _021DF7A4 ; =0x00000F64
	add r0, r4, #0
	ldrh r2, [r5, r2]
	add r4, #0x1c
	add r0, #0x4c
	add r1, r4, #0
	bl ov05_021DD474
	cmp r0, #1
	bne _021DF76A
	cmp r6, #3
	bne _021DF76A
	add r0, r5, #0
	ldr r1, [r5, #0x40]
	add r0, #0xc
	cmp r1, r0
	bne _021DF76A
	ldr r0, _021DF7A8 ; =0x00000F62
	mov r1, #5
	strh r1, [r5, r0]
	b _021DF76A
_021DF74C:
	add r0, #0xc
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DF764
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r0, [r4, #0x1c]
	mov r1, #1
	add r3, r2, #0
	bl ov05_021DBA40
_021DF764:
	ldr r0, [r5, #4]
	bl ov05_021DCB6C
_021DF76A:
	ldr r0, _021DF7A8 ; =0x00000F62
	ldrh r0, [r5, r0]
	cmp r0, #5
	beq _021DF790
	cmp r0, #0
	beq _021DF790
	add r0, r5, #0
	ldr r1, _021DF7AC ; =ov05_021DF8E4
	add r0, #0xc
	bl ov05_021DD148
	mov r1, #0
	add r0, r5, #0
	add r2, r1, #0
	bl ov05_021DD2BC
	add r0, r5, #0
	bl ov05_021DD164
_021DF790:
	add sp, #0x18
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021DF794: .word 0x00000F58
_021DF798: .word ov05_021DF7B4
_021DF79C: .word 0x0000716F
_021DF7A0: .word 0x00006B5A
_021DF7A4: .word 0x00000F64
_021DF7A8: .word 0x00000F62
_021DF7AC: .word ov05_021DF8E4
_021DF7B0: .word 0x00000F66

	thumb_func_start ov05_021DF7B4
ov05_021DF7B4: ; 0x021DF7B4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, r1, #0
	str r1, [sp, #4]
	cmp r0, #0
	bgt _021DF7C8
	b _021DF8E0
_021DF7C8:
	ldr r0, [sp]
	mov r1, #0x20
	bl ov05_021DD048
	add r4, r0, #0
	bne _021DF7D6
	b _021DF8E0
_021DF7D6:
	ldr r5, [r4, #8]
	mov r0, #0
	str r0, [r5]
	bl MTRandom
	mov r1, #5
	bl _u32_div_f
	add r0, r1, #7
	str r0, [r5, #4]
	bl MTRandom
	mov r1, #0xfa
	lsl r1, r1, #2
	bl _u32_div_f
	lsr r2, r1, #0x1f
	lsl r1, r1, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	bne _021DF808
	mov r0, #1
	b _021DF80C
_021DF808:
	mov r0, #0
	mvn r0, r0
_021DF80C:
	str r0, [r5, #8]
	mov r0, #1
	str r0, [r5, #0xc]
	bl MTRandom
	mov r1, #6
	bl _u32_div_f
	add r0, r1, #3
	str r0, [r5, #0x10]
	bl MTRandom
	mov r1, #5
	bl _u32_div_f
	add r0, r1, #4
	str r0, [r5, #0x14]
	bl MTRandom
	mov r1, #0x14
	bl _u32_div_f
	str r1, [sp, #8]
	add r0, sp, #0x10
	add r1, r4, #0
	bl ov05_021DD168
	bl MTRandom
	mov r1, #6
	lsl r1, r1, #6
	bl _u32_div_f
	sub r1, #0x40
	str r1, [sp, #0x10]
	bl MTRandom
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldr r0, [sp, #0x10]
	sub r1, #8
	lsl r0, r0, #0xc
	str r0, [sp, #0x10]
	str r1, [sp, #0x14]
	lsl r0, r1, #0xc
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	ldr r0, [r4, #4]
	add r1, sp, #0x10
	bl ov05_021DC4FC
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x10]
	asr r1, r1, #0xc
	asr r0, r0, #0xc
	str r1, [sp, #0x14]
	mov r1, #3
	str r0, [sp, #0x10]
	bl _s32_div_f
	mov r1, #0x32
	sub r6, r1, r0
	mov r1, #0xce
	sub r7, r1, r0
	bpl _021DF89E
	bl MTRandom
	neg r1, r7
	bl _u32_div_f
	sub r1, r6, r1
	b _021DF8AA
_021DF89E:
	bl MTRandom
	add r1, r7, #0
	bl _u32_div_f
	add r1, r6, r1
_021DF8AA:
	ldr r0, [sp, #0x14]
	cmp r6, r0
	bgt _021DF8BC
	cmp r1, r0
	blt _021DF8BC
	ldr r0, [r5, #4]
	lsl r0, r0, #1
	str r0, [r5, #4]
	b _021DF8C6
_021DF8BC:
	bl MTRandom
	mov r1, #3
	and r0, r1
	str r0, [sp, #8]
_021DF8C6:
	ldr r1, [sp, #8]
	ldr r0, [r4, #4]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl sub_02020208
	ldr r0, [sp, #0xc]
	add r1, r0, #1
	ldr r0, [sp, #4]
	str r1, [sp, #0xc]
	cmp r1, r0
	bge _021DF8E0
	b _021DF7C8
_021DF8E0:
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov05_021DF8E4
ov05_021DF8E4: ; 0x021DF8E4
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r4, [r5, #8]
	add r0, sp, #0
	add r1, r5, #0
	bl ov05_021DD168
	ldr r0, [r4]
	add r1, r0, #1
	str r1, [r4]
	ldr r0, [r4, #4]
	cmp r1, r0
	blt _021DF906
	add r0, r5, #0
	bl ov05_021DD100
_021DF906:
	add sp, #0xc
	pop {r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021DF90C
ov05_021DF90C: ; 0x021DF90C
	push {r3, r4, r5, lr}
	ldr r0, _021DFA98 ; =0x00000F58
	add r5, r1, #0
	ldr r4, [r5, r0]
	add r0, #0xa
	ldrh r0, [r5, r0]
	cmp r0, #5
	bhi _021DF978
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DF928: ; jump table
	.short _021DF934 - _021DF928 - 2 ; case 0
	.short _021DF958 - _021DF928 - 2 ; case 1
	.short _021DF9A2 - _021DF928 - 2 ; case 2
	.short _021DF9E2 - _021DF928 - 2 ; case 3
	.short _021DFA68 - _021DF928 - 2 ; case 4
	.short _021DFA90 - _021DF928 - 2 ; case 5
_021DF934:
	mov r0, #0
	str r0, [r4]
	mov r1, #0x10
	str r0, [r4, #4]
	bl ov05_021DC6D4
	mov r1, #2
	ldr r0, _021DFA9C ; =0x04000018
	lsl r1, r1, #0x14
	str r1, [r0]
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, _021DFAA0 ; =0x00000F62
	mov r1, #1
	strh r1, [r5, r0]
	pop {r3, r4, r5, pc}
_021DF958:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	cmp r0, #0xa
	blt _021DF978
	mov r0, #0
	str r0, [r4]
	ldr r0, [r4, #4]
	mov r1, #0x10
	add r0, r0, #1
	str r0, [r4, #4]
	bl ov05_021DC6D4
	ldr r0, [r4, #4]
	cmp r0, #0xa
	bge _021DF97A
_021DF978:
	b _021DFA96
_021DF97A:
	bl MTRandom
	mov r1, #0x14
	bl _u32_div_f
	add r1, #0xa
	str r1, [r4, #8]
	bl MTRandom
	mov r1, #3
	bl _u32_div_f
	add r0, r1, #5
	str r0, [r4, #0xc]
	mov r0, #1
	str r0, [r4, #0x10]
	ldr r0, _021DFAA0 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	pop {r3, r4, r5, pc}
_021DF9A2:
	mov r0, #0
	str r0, [r4]
	mov r0, #0xa
	str r0, [r4, #4]
	mov r1, #2
	ldr r0, _021DFA9C ; =0x04000018
	lsl r1, r1, #0x14
	str r1, [r0]
	ldr r0, [r4, #4]
	mov r1, #0x10
	bl ov05_021DC6D4
	bl MTRandom
	mov r1, #0x14
	bl _u32_div_f
	add r1, #0xa
	str r1, [r4, #8]
	bl MTRandom
	mov r1, #3
	bl _u32_div_f
	add r0, r1, #5
	str r0, [r4, #0xc]
	mov r0, #1
	str r0, [r4, #0x10]
	ldr r0, _021DFAA0 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	pop {r3, r4, r5, pc}
_021DF9E2:
	ldr r0, [r4]
	add r1, r0, #1
	str r1, [r4]
	ldr r0, [r4, #8]
	cmp r1, r0
	blt _021DFA50
	mov r0, #0
	str r0, [r4]
	ldr r0, [r4, #0x10]
	cmp r0, #1
	ldr r0, [r4, #4]
	bne _021DFA26
	sub r1, r0, #1
	str r1, [r4, #4]
	ldr r0, [r4, #0xc]
	cmp r1, r0
	bgt _021DFA50
	bl MTRandom
	mov r1, #0xf
	bl _u32_div_f
	add r1, #0xa
	str r1, [r4, #8]
	bl MTRandom
	mov r1, #3
	bl _u32_div_f
	add r0, r1, #7
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4, #0x10]
	b _021DFA50
_021DFA26:
	add r1, r0, #1
	str r1, [r4, #4]
	ldr r0, [r4, #0xc]
	cmp r1, r0
	blt _021DFA50
	bl MTRandom
	mov r1, #0x14
	bl _u32_div_f
	add r1, #0xa
	str r1, [r4, #8]
	bl MTRandom
	mov r1, #3
	bl _u32_div_f
	add r0, r1, #5
	str r0, [r4, #0xc]
	mov r0, #1
	str r0, [r4, #0x10]
_021DFA50:
	ldr r0, [r4, #4]
	mov r1, #0x10
	bl ov05_021DC6D4
	ldr r0, _021DFAA4 ; =0x00000F66
	ldrh r1, [r5, r0]
	cmp r1, #5
	bne _021DFA96
	mov r1, #4
	sub r0, r0, #4
	strh r1, [r5, r0]
	pop {r3, r4, r5, pc}
_021DFA68:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	cmp r0, #0xa
	blt _021DFA96
	mov r0, #0
	str r0, [r4]
	ldr r0, [r4, #4]
	mov r1, #0x10
	sub r0, r0, #1
	str r0, [r4, #4]
	bl ov05_021DC6D4
	ldr r0, [r4, #4]
	cmp r0, #0
	bgt _021DFA96
	ldr r0, _021DFAA0 ; =0x00000F62
	mov r1, #5
	strh r1, [r5, r0]
	pop {r3, r4, r5, pc}
_021DFA90:
	ldr r0, [r5, #4]
	bl ov05_021DCB6C
_021DFA96:
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021DFA98: .word 0x00000F58
_021DFA9C: .word 0x04000018
_021DFAA0: .word 0x00000F62
_021DFAA4: .word 0x00000F66

	thumb_func_start ov05_021DFAA8
ov05_021DFAA8: ; 0x021DFAA8
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	mov r0, #0x18
	str r0, [sp]
	mov r2, #1
	str r2, [sp, #4]
	sub r0, r2, #4
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	mov r0, #4
	str r0, [sp, #0x10]
	ldr r0, _021DFB1C ; =ov05_021DFEE0
	add r4, r1, #0
	str r0, [sp, #0x14]
	add r0, r4, #0
	add r1, r5, #0
	mov r3, #0xf
	bl ov05_021DD328
	ldr r0, _021DFB20 ; =0x00006F6F
	mov r2, #0x41
	str r0, [sp]
	ldr r0, _021DFB24 ; =0x00006B5A
	add r1, r4, #0
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, _021DFB28 ; =0x00000F64
	lsl r2, r2, #2
	ldrh r0, [r5, r0]
	add r1, #0x1c
	str r0, [sp, #0xc]
	ldr r3, [r5]
	add r0, r4, #0
	ldr r2, [r3, r2]
	add r0, #0x4c
	ldr r2, [r2, #0x44]
	mov r3, #3
	bl ov05_021DD420
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xb8
	str r1, [r0]
	add r4, #0xbc
	str r1, [r4]
	ldr r1, _021DFB2C ; =0x0000063B
	add r0, r5, #0
	bl ov05_021E0FA4
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_021DFB1C: .word ov05_021DFEE0
_021DFB20: .word 0x00006F6F
_021DFB24: .word 0x00006B5A
_021DFB28: .word 0x00000F64
_021DFB2C: .word 0x0000063B

	thumb_func_start ov05_021DFB30
ov05_021DFB30: ; 0x021DFB30
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DFB56
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r4, #0xb4
	sub r0, r0, #1
	str r0, [r4]
	b _021DFB72
_021DFB56:
	ldr r2, _021DFB78 ; =0x00000F64
	add r0, r4, #0
	ldrh r2, [r5, r2]
	add r4, #0x1c
	add r0, #0x4c
	add r1, r4, #0
	bl ov05_021DD474
	cmp r0, #1
	bne _021DFB72
	cmp r6, #3
	bne _021DFB72
	mov r0, #1
	pop {r4, r5, r6, pc}
_021DFB72:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_021DFB78: .word 0x00000F64

	thumb_func_start ov05_021DFB7C
ov05_021DFB7C: ; 0x021DFB7C
	push {r3, r4, r5, lr}
	sub sp, #0x18
	mov r2, #0x18
	str r2, [sp]
	mov r3, #1
	add r5, r0, #0
	str r3, [sp, #4]
	sub r0, r3, #4
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	mov r0, #4
	str r0, [sp, #0x10]
	ldr r0, _021DFBF8 ; =ov05_021DFEE0
	add r4, r1, #0
	str r0, [sp, #0x14]
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DD328
	ldr r0, _021DFBFC ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DFBCA
	mov r0, #0x41
	ldr r1, [r5]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r2, _021DFC00 ; =0x00006F6F
	ldr r0, [r0, #0x44]
	ldr r3, _021DFC04 ; =0x00006B5A
	mov r1, #3
	str r0, [r4, #0x1c]
	bl ov05_021DD49C
	add r0, r4, #0
	add r0, #0x1c
	bl ov05_021DD5EC
_021DFBCA:
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb8
	str r1, [r0]
	add r4, #0xbc
	str r1, [r4]
	mov r0, #1
	str r0, [sp]
	ldr r0, _021DFC08 ; =ov05_021E0000
	ldr r1, _021DFBF8 ; =ov05_021DFEE0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x14
	mov r3, #5
	bl ov05_021DD680
	ldr r1, _021DFC0C ; =0x0000063B
	add r0, r5, #0
	bl ov05_021E0FA4
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_021DFBF8: .word ov05_021DFEE0
_021DFBFC: .word 0x00000F64
_021DFC00: .word 0x00006F6F
_021DFC04: .word 0x00006B5A
_021DFC08: .word ov05_021E0000
_021DFC0C: .word 0x0000063B

	thumb_func_start ov05_021DFC10
ov05_021DFC10: ; 0x021DFC10
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0xbc
	ldr r0, [r0]
	mov r1, #0x4b
	add r0, r0, #1
	lsl r1, r1, #2
	bl _s32_div_f
	add r0, r4, #0
	add r0, #0xbc
	str r1, [r0]
	mov r0, #6
	ldrsh r1, [r4, r0]
	sub r0, r1, #1
	strh r0, [r4, #6]
	cmp r1, #0
	bgt _021DFC48
	mov r1, #4
	ldrsh r1, [r4, r1]
	add r0, r5, #0
	bl ov05_021DFEE0
	mov r0, #8
	ldrsh r0, [r4, r0]
	strh r0, [r4, #6]
_021DFC48:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021DFC4C
ov05_021DFC4C: ; 0x021DFC4C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #9
	add r4, r1, #0
	mvn r0, r0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0
	mov r2, #0xf
	mov r3, #3
	bl ov05_021DD350
	ldr r0, _021DFC88 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DFC78
	add r0, r4, #0
	add r0, #0x1c
	mov r1, #1
	mov r2, #0
	bl ov05_021DD5B4
_021DFC78:
	mov r0, #0
	add r4, #0xb4
	str r0, [r4]
	add r0, r5, #0
	bl ov05_021E0FD0
	pop {r3, r4, r5, pc}
	nop
_021DFC88: .word 0x00000F64

	thumb_func_start ov05_021DFC8C
ov05_021DFC8C: ; 0x021DFC8C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021DFCB2
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r4, #0xb4
	sub r0, r0, #1
	str r0, [r4]
	b _021DFCDA
_021DFCB2:
	ldr r0, _021DFCE0 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021DFCC4
	add r4, #0x1c
	add r0, r4, #0
	bl ov05_021DD5D0
	b _021DFCC6
_021DFCC4:
	mov r0, #1
_021DFCC6:
	cmp r0, #1
	bne _021DFCDA
	cmp r6, #3
	bne _021DFCDA
	ldr r0, [r5, #0x40]
	add r5, #0xc
	cmp r0, r5
	bne _021DFCDA
	mov r0, #1
	pop {r4, r5, r6, pc}
_021DFCDA:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_021DFCE0: .word 0x00000F64

	thumb_func_start ov05_021DFCE4
ov05_021DFCE4: ; 0x021DFCE4
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, _021DFD0C ; =0x00000F64
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _021DFD02
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r0, [r1, #0x1c]
	mov r1, #1
	add r3, r2, #0
	bl ov05_021DBA40
_021DFD02:
	ldr r0, [r4, #4]
	bl ov05_021DCB6C
	add sp, #8
	pop {r4, pc}
	.balign 4, 0
_021DFD0C: .word 0x00000F64

	thumb_func_start ov05_021DFD10
ov05_021DFD10: ; 0x021DFD10
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021DFD3C ; =0x00000F62
	ldrh r0, [r4, r0]
	cmp r0, #5
	beq _021DFD3A
	cmp r0, #0
	beq _021DFD3A
	add r0, r4, #0
	ldr r1, _021DFD40 ; =ov05_021E0000
	add r0, #0xc
	bl ov05_021DD148
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl ov05_021DD2BC
	add r0, r4, #0
	bl ov05_021DD164
_021DFD3A:
	pop {r4, pc}
	.balign 4, 0
_021DFD3C: .word 0x00000F62
_021DFD40: .word ov05_021E0000

	thumb_func_start ov05_021DFD44
ov05_021DFD44: ; 0x021DFD44
	push {r3, r4, r5, lr}
	ldr r0, _021DFE24 ; =0x00000F58
	add r4, r1, #0
	ldr r5, [r4, r0]
	add r0, #0xa
	ldrh r0, [r4, r0]
	cmp r0, #5
	bhi _021DFE18
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DFD60: ; jump table
	.short _021DFD6C - _021DFD60 - 2 ; case 0
	.short _021DFD90 - _021DFD60 - 2 ; case 1
	.short _021DFDA4 - _021DFD60 - 2 ; case 2
	.short _021DFDC8 - _021DFD60 - 2 ; case 3
	.short _021DFDF2 - _021DFD60 - 2 ; case 4
	.short _021DFE06 - _021DFD60 - 2 ; case 5
_021DFD6C:
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DFAA8
	ldr r0, [r4]
	mov r1, #0
	mov r2, #0x11
	bl ov05_021DC608
	ldr r0, [r4]
	mov r1, #3
	mov r2, #0x11
	bl ov05_021DC608
	ldr r0, _021DFE28 ; =0x00000F62
	mov r1, #1
	strh r1, [r4, r0]
	b _021DFE18
_021DFD90:
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DFB30
	cmp r0, #0
	beq _021DFE18
	ldr r0, _021DFE28 ; =0x00000F62
	mov r1, #3
	strh r1, [r4, r0]
	b _021DFE18
_021DFDA4:
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DFB7C
	ldr r0, [r4]
	mov r1, #0
	mov r2, #0x11
	bl ov05_021DC608
	ldr r0, [r4]
	mov r1, #3
	mov r2, #0x11
	bl ov05_021DC608
	ldr r0, _021DFE28 ; =0x00000F62
	mov r1, #3
	strh r1, [r4, r0]
	b _021DFE18
_021DFDC8:
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DFC10
	ldr r0, _021DFE2C ; =0x00000F66
	ldrh r0, [r4, r0]
	cmp r0, #5
	bne _021DFE18
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DFC4C
	ldr r0, [r4]
	mov r1, #5
	mov r2, #0x11
	bl ov05_021DC608
	ldr r0, _021DFE28 ; =0x00000F62
	mov r1, #4
	strh r1, [r4, r0]
	b _021DFE18
_021DFDF2:
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DFC8C
	cmp r0, #0
	beq _021DFE18
	ldr r0, _021DFE28 ; =0x00000F62
	mov r1, #5
	strh r1, [r4, r0]
	b _021DFE18
_021DFE06:
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DFCE4
	ldr r0, [r4]
	mov r1, #8
	mov r2, #0x11
	bl ov05_021DC608
_021DFE18:
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DFD10
	pop {r3, r4, r5, pc}
	nop
_021DFE24: .word 0x00000F58
_021DFE28: .word 0x00000F62
_021DFE2C: .word 0x00000F66

	thumb_func_start ov05_021DFE30
ov05_021DFE30: ; 0x021DFE30
	push {r3, r4, r5, lr}
	ldr r0, _021DFED4 ; =0x00000F58
	add r4, r1, #0
	ldr r5, [r4, r0]
	add r0, #0xa
	ldrh r0, [r4, r0]
	cmp r0, #5
	bhi _021DFEC8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DFE4C: ; jump table
	.short _021DFE58 - _021DFE4C - 2 ; case 0
	.short _021DFE68 - _021DFE4C - 2 ; case 1
	.short _021DFE7C - _021DFE4C - 2 ; case 2
	.short _021DFE8C - _021DFE4C - 2 ; case 3
	.short _021DFEAC - _021DFE4C - 2 ; case 4
	.short _021DFEC0 - _021DFE4C - 2 ; case 5
_021DFE58:
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DFAA8
	ldr r0, _021DFED8 ; =0x00000F62
	mov r1, #1
	strh r1, [r4, r0]
	b _021DFEC8
_021DFE68:
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DFB30
	cmp r0, #0
	beq _021DFEC8
	ldr r0, _021DFED8 ; =0x00000F62
	mov r1, #3
	strh r1, [r4, r0]
	b _021DFEC8
_021DFE7C:
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DFB7C
	ldr r0, _021DFED8 ; =0x00000F62
	mov r1, #3
	strh r1, [r4, r0]
	b _021DFEC8
_021DFE8C:
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DFC10
	ldr r0, _021DFEDC ; =0x00000F66
	ldrh r0, [r4, r0]
	cmp r0, #5
	bne _021DFEC8
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DFC4C
	ldr r0, _021DFED8 ; =0x00000F62
	mov r1, #4
	strh r1, [r4, r0]
	b _021DFEC8
_021DFEAC:
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DFC8C
	cmp r0, #0
	beq _021DFEC8
	ldr r0, _021DFED8 ; =0x00000F62
	mov r1, #5
	strh r1, [r4, r0]
	b _021DFEC8
_021DFEC0:
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DFCE4
_021DFEC8:
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021DFD10
	pop {r3, r4, r5, pc}
	nop
_021DFED4: .word 0x00000F58
_021DFED8: .word 0x00000F62
_021DFEDC: .word 0x00000F66

	thumb_func_start ov05_021DFEE0
ov05_021DFEE0: ; 0x021DFEE0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	str r1, [sp, #4]
	ldr r1, _021DFFF4 ; =0x00000F58
	str r0, [sp]
	ldr r6, [r0, r1]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	cmp r0, #0
	ble _021DFFEE
_021DFEF6:
	ldr r0, [sp]
	mov r1, #0x20
	bl ov05_021DD048
	add r4, r0, #0
	beq _021DFFEE
	ldr r5, [r4, #8]
	mov r0, #0
	str r0, [r5]
	bl MTRandom
	mov r1, #3
	bl _u32_div_f
	add r7, r1, #0
	lsl r1, r7, #0x10
	ldr r0, [r4, #4]
	lsr r1, r1, #0x10
	bl sub_02020208
	mov r0, #0x17
	add r1, r7, #1
	mvn r0, r0
	mul r0, r1
	str r0, [r5, #0x10]
	mov r0, #0x18
	mul r0, r1
	str r0, [r5, #8]
	add r0, r6, #0
	add r0, #0xbc
	ldr r0, [r0]
	mov r1, #0x3c
	bl _s32_div_f
	lsl r2, r0, #2
	ldr r0, _021DFFF8 ; =ov05_021F6808
	ldr r1, [r5, #0x10]
	ldr r0, [r0, r2]
	mul r0, r1
	str r0, [r5, #0x10]
	add r0, r6, #0
	add r0, #0xbc
	ldr r0, [r0]
	mov r1, #0x3c
	bl _s32_div_f
	lsl r2, r0, #2
	ldr r0, _021DFFF8 ; =ov05_021F6808
	ldr r1, [r5, #8]
	ldr r0, [r0, r2]
	mul r0, r1
	str r0, [r5, #8]
	ldr r0, [r5, #0x10]
	mov r1, #0x64
	bl _s32_div_f
	str r0, [r5, #0x10]
	ldr r0, [r5, #8]
	mov r1, #0x64
	bl _s32_div_f
	str r0, [r5, #8]
	mov r0, #0
	str r0, [r5, #0xc]
	bl MTRandom
	mov r1, #3
	and r1, r0
	mov r0, #0x64
	mul r0, r1
	str r0, [r5, #4]
	add r0, r6, #0
	add r0, #0xbc
	ldr r0, [r0]
	mov r1, #0x3c
	bl _s32_div_f
	add r1, r0, #0
	lsl r2, r1, #2
	ldr r1, _021DFFF8 ; =ov05_021F6808
	ldr r0, [r5, #4]
	ldr r1, [r1, r2]
	bl _s32_div_f
	str r0, [r5, #4]
	add r0, sp, #0xc
	add r1, r4, #0
	bl ov05_021DD168
	add r3, sp, #0xc
	ldmia r3!, {r0, r1}
	add r2, sp, #0x18
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	bl MTRandom
	ldr r1, _021DFFFC ; =0x000001FF
	and r0, r1
	str r0, [sp, #0x18]
	bl MTRandom
	mov r1, #0x30
	bl _u32_div_f
	mov r0, #0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x18]
	sub r1, #0x50
	lsl r0, r0, #0xc
	str r0, [sp, #0x18]
	str r1, [sp, #0x1c]
	lsl r0, r1, #0xc
	str r0, [sp, #0x1c]
	ldr r0, [r4, #4]
	add r1, sp, #0x18
	bl ov05_021DC4FC
	ldr r0, [sp, #8]
	add r1, r0, #1
	ldr r0, [sp, #4]
	str r1, [sp, #8]
	cmp r1, r0
	blt _021DFEF6
_021DFFEE:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_021DFFF4: .word 0x00000F58
_021DFFF8: .word ov05_021F6808
_021DFFFC: .word 0x000001FF

	thumb_func_start ov05_021E0000
ov05_021E0000: ; 0x021E0000
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r0, sp, #0
	add r1, r5, #0
	ldr r4, [r5, #8]
	bl ov05_021DD168
	add r3, sp, #0
	add r2, sp, #0xc
	ldmia r3!, {r0, r1}
	add r7, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021E0030
	cmp r0, #1
	beq _021E0088
	cmp r0, #2
	beq _021E009A
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_021E0030:
	mov r6, #0
_021E0032:
	ldr r0, [r4, #0x10]
	ldr r1, [sp, #0xc]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0xc]
	ldr r0, [r4, #8]
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x10]
	ldr r1, [r4]
	add r0, r1, #1
	str r0, [r4]
	ldr r0, [r4, #4]
	cmp r1, r0
	ble _021E0076
	bl MTRandom
	mov r1, #0xa
	bl _u32_div_f
	cmp r1, #5
	bhs _021E0066
	mov r0, #2
	str r0, [r4, #0xc]
	b _021E0076
_021E0066:
	mov r0, #1
	str r0, [r4, #0xc]
	mov r0, #4
	str r0, [r4]
	ldr r0, [r5, #4]
	mov r1, #3
	bl sub_02020208
_021E0076:
	ldr r0, [r5, #4]
	add r1, r7, #0
	bl ov05_021DC4FC
	add r6, r6, #1
	cmp r6, #2
	blt _021E0032
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_021E0088:
	ldr r1, [r4]
	sub r0, r1, #1
	str r0, [r4]
	cmp r1, #0
	bgt _021E00A0
	mov r0, #2
	add sp, #0x18
	str r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_021E009A:
	add r0, r5, #0
	bl ov05_021DD100
_021E00A0:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021E00A4
ov05_021E00A4: ; 0x021E00A4
	push {r4, r5, r6, lr}
	sub sp, #0x20
	ldr r0, _021E03D8 ; =0x00000F58
	add r5, r1, #0
	add r2, r0, #0
	add r2, #0xa
	ldrh r2, [r5, r2]
	ldr r4, [r5, r0]
	cmp r2, #5
	bhi _021E017E
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021E00C4: ; jump table
	.short _021E00D0 - _021E00C4 - 2 ; case 0
	.short _021E0144 - _021E00C4 - 2 ; case 1
	.short _021E0190 - _021E00C4 - 2 ; case 2
	.short _021E0212 - _021E00C4 - 2 ; case 3
	.short _021E027A - _021E00C4 - 2 ; case 4
	.short _021E02CA - _021E00C4 - 2 ; case 5
_021E00D0:
	mov r2, #1
	str r2, [sp]
	mov r0, #6
	str r0, [sp, #4]
	sub r0, r0, #7
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, _021E03DC ; =ov05_021E0400
	mov r3, #0xc
	str r0, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021DD328
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb8
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xbc
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc8
	str r1, [r0]
	ldr r0, _021E03E0 ; =0x00006F2F
	mov r2, #0x41
	str r0, [sp]
	ldr r0, _021E03E4 ; =0x00003A94
	add r1, r4, #0
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, _021E03E8 ; =0x00000F64
	lsl r2, r2, #2
	ldrh r0, [r5, r0]
	add r1, #0x1c
	str r0, [sp, #0xc]
	ldr r3, [r5]
	add r0, r4, #0
	ldr r2, [r3, r2]
	add r0, #0x4c
	ldr r2, [r2, #0x44]
	mov r3, #3
	bl ov05_021DD420
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
	ldr r0, _021E03EC ; =0x00000F62
	mov r1, #1
	strh r1, [r5, r0]
	b _021E02E8
_021E0144:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021E0166
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xb4
	str r1, [r0]
	b _021E02E8
_021E0166:
	ldr r2, _021E03E8 ; =0x00000F64
	add r0, r4, #0
	ldrh r2, [r5, r2]
	add r1, r4, #0
	add r0, #0x4c
	add r1, #0x1c
	bl ov05_021DD474
	cmp r0, #1
	bne _021E017E
	cmp r6, #3
	beq _021E0180
_021E017E:
	b _021E02E8
_021E0180:
	ldr r0, _021E03EC ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	b _021E02E8
_021E0190:
	mov r2, #1
	mov r3, #6
	str r2, [sp]
	str r3, [sp, #4]
	sub r0, r3, #7
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, _021E03DC ; =ov05_021E0400
	str r0, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021DD328
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb8
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xbc
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc8
	str r1, [r0]
	ldr r0, _021E03E8 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021E01EE
	mov r0, #0x41
	ldr r1, [r5]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r2, _021E03E0 ; =0x00006F2F
	ldr r0, [r0, #0x44]
	ldr r3, _021E03E4 ; =0x00003A94
	mov r1, #3
	str r0, [r4, #0x1c]
	bl ov05_021DD49C
	add r0, r4, #0
	add r0, #0x1c
	bl ov05_021DD5EC
_021E01EE:
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _021E03F0 ; =ov05_021E051C
	ldr r1, _021E03DC ; =ov05_021E0400
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x14
	mov r3, #2
	bl ov05_021DD680
	ldr r0, _021E03EC ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	b _021E02E8
_021E0212:
	mov r0, #6
	ldrsh r1, [r4, r0]
	sub r0, r1, #1
	strh r0, [r4, #6]
	cmp r1, #0
	bgt _021E022E
	mov r1, #4
	ldrsh r1, [r4, r1]
	add r0, r5, #0
	bl ov05_021E0400
	mov r0, #8
	ldrsh r0, [r4, r0]
	strh r0, [r4, #6]
_021E022E:
	ldr r0, _021E03F4 ; =0x00000F66
	ldrh r0, [r5, r0]
	cmp r0, #5
	bne _021E02E8
	mov r0, #0
	mvn r0, r0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0
	mov r2, #0xc
	mov r3, #1
	bl ov05_021DD350
	ldr r0, _021E03E8 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021E025C
	add r0, r4, #0
	add r0, #0x1c
	mov r1, #1
	mov r2, #0
	bl ov05_021DD5B4
_021E025C:
	add r0, r4, #0
	mov r1, #9
	add r0, #0xb4
	str r1, [r0]
	ldr r1, _021E03EC ; =0x00000F62
	mov r0, #4
	strh r0, [r5, r1]
	add r1, r4, #0
	mov r2, #1
	add r1, #0xc8
	str r2, [r1]
	mov r1, #0
	bl GX_EngineAToggleLayers
	b _021E02E8
_021E027A:
	add r0, r4, #0
	bl ov05_021DD35C
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _021E029C
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xb4
	str r1, [r0]
	b _021E02E8
_021E029C:
	ldr r0, _021E03E8 ; =0x00000F64
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021E02AE
	add r0, r4, #0
	add r0, #0x1c
	bl ov05_021DD5D0
	b _021E02B0
_021E02AE:
	mov r0, #1
_021E02B0:
	cmp r0, #1
	bne _021E02E8
	cmp r6, #3
	bne _021E02E8
	add r0, r5, #0
	ldr r1, [r5, #0x40]
	add r0, #0xc
	cmp r1, r0
	bne _021E02E8
	ldr r0, _021E03EC ; =0x00000F62
	mov r1, #5
	strh r1, [r5, r0]
	b _021E02E8
_021E02CA:
	add r0, #0xc
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _021E02E2
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r0, [r4, #0x1c]
	mov r1, #1
	add r3, r2, #0
	bl ov05_021DBA40
_021E02E2:
	ldr r0, [r5, #4]
	bl ov05_021DCB6C
_021E02E8:
	ldr r0, _021E03EC ; =0x00000F62
	ldrh r0, [r5, r0]
	cmp r0, #5
	beq _021E03D4
	cmp r0, #0
	beq _021E03D4
	add r0, r5, #0
	ldr r1, _021E03F0 ; =ov05_021E051C
	add r0, #0xc
	bl ov05_021DD148
	add r0, r5, #0
	add r1, sp, #0x1c
	add r2, sp, #0x18
	bl ov05_021DD2BC
	add r0, r5, #0
	bl ov05_021DD164
	add r0, r4, #0
	add r0, #0xbc
	ldr r1, [r0]
	asr r0, r1, #0x10
	lsl r0, r0, #0x10
	asr r2, r0, #0x10
	lsl r0, r1, #0x10
	ldr r1, [sp, #0x1c]
	asr r0, r0, #0x10
	add r1, r2, r1
	lsl r1, r1, #0x10
	ldr r2, [sp, #0x18]
	asr r5, r1, #0x10
	lsl r1, r2, #2
	add r1, r2, r1
	sub r0, r0, r1
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	cmp r5, #0
	bge _021E0342
	mov r1, #1
	lsl r1, r1, #8
	add r1, r5, r1
	lsl r1, r1, #0x10
	asr r5, r1, #0x10
	b _021E0350
_021E0342:
	mov r1, #1
	lsl r1, r1, #8
	cmp r5, r1
	blt _021E0350
	sub r1, r5, r1
	lsl r1, r1, #0x10
	asr r5, r1, #0x10
_021E0350:
	cmp r0, #0
	bge _021E035E
	mov r1, #2
	lsl r1, r1, #0xa
	add r0, r0, r1
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
_021E035E:
	add r1, r4, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r2, r1, #2
	add r1, r4, #0
	add r1, #0xc4
	str r2, [r1]
	add r1, r4, #0
	add r1, #0xc4
	ldr r1, [r1]
	cmp r1, #0x3c
	ble _021E0390
	add r1, r4, #0
	add r5, #0x20
	mov r2, #0
	add r1, #0xc4
	str r2, [r1]
	lsr r3, r5, #0x1f
	lsl r2, r5, #0x18
	sub r2, r2, r3
	mov r1, #0x18
	ror r2, r1
	add r1, r3, r2
	lsl r1, r1, #0x10
	asr r5, r1, #0x10
_021E0390:
	add r0, r0, #2
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x15
	sub r1, r1, r2
	mov r0, #0x15
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	neg r0, r6
	mov r1, #5
	bl _s32_div_f
	ldr r2, _021E03F8 ; =0x000001FF
	add r1, r5, #0
	lsl r3, r0, #0x10
	lsl r0, r2, #0x10
	and r1, r2
	and r0, r3
	orr r1, r0
	ldr r0, _021E03FC ; =0x04000018
	str r1, [r0]
	add r0, r4, #0
	lsl r1, r5, #0x10
	add r0, #0xbc
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xbc
	ldr r1, [r0]
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	orr r0, r1
	add r4, #0xbc
	str r0, [r4]
_021E03D4:
	add sp, #0x20
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021E03D8: .word 0x00000F58
_021E03DC: .word ov05_021E0400
_021E03E0: .word 0x00006F2F
_021E03E4: .word 0x00003A94
_021E03E8: .word 0x00000F64
_021E03EC: .word 0x00000F62
_021E03F0: .word ov05_021E051C
_021E03F4: .word 0x00000F66
_021E03F8: .word 0x000001FF
_021E03FC: .word 0x04000018

	thumb_func_start ov05_021E0400
ov05_021E0400: ; 0x021E0400
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r7, r1, #0
	ldr r1, _021E0514 ; =0x00000F58
	str r0, [sp]
	ldr r0, [r0, r1]
	str r0, [sp, #0x10]
	add r0, #0xb8
	ldr r0, [r0]
	cmp r0, #1
	bne _021E0418
	lsl r7, r7, #1
_021E0418:
	mov r6, #0
	cmp r7, #0
	ble _021E050E
	ldr r0, [sp, #0x10]
	str r0, [sp, #0xc]
	add r0, #0xb8
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	str r0, [sp, #8]
	add r0, #0xc8
	str r0, [sp, #8]
	lsr r0, r7, #0x1f
	add r0, r7, r0
	asr r0, r0, #1
	str r0, [sp, #4]
_021E0436:
	ldr r0, [sp]
	mov r1, #0x20
	bl ov05_021DD048
	add r4, r0, #0
	beq _021E050E
	ldr r5, [r4, #8]
	bl MTRandom
	mov r1, #3
	and r1, r0
	lsl r1, r1, #0x10
	ldr r0, [r4, #4]
	lsr r1, r1, #0x10
	bl sub_02020208
	mov r0, #0xa
	str r0, [r5, #0x10]
	mov r0, #0
	str r0, [r5, #0x14]
	bl MTRandom
	lsr r1, r0, #0x1f
	lsl r2, r0, #0x1f
	sub r2, r2, r1
	mov r0, #0x1f
	ror r2, r0
	add r0, r1, r2
	bne _021E0474
	mov r0, #1
	b _021E0478
_021E0474:
	mov r0, #0
	mvn r0, r0
_021E0478:
	str r0, [r5, #4]
	bl MTRandom
	mov r0, #1
	str r0, [r5, #0xc]
	ldr r0, [sp, #0xc]
	str r0, [r5]
	ldr r0, [sp, #8]
	str r0, [r5, #0x18]
	bl MTRandom
	mov r1, #0x14
	bl _u32_div_f
	add r1, #0xa
	str r1, [r5, #0x1c]
	add r0, sp, #0x14
	add r1, r4, #0
	bl ov05_021DD168
	add r3, sp, #0x14
	ldmia r3!, {r0, r1}
	add r2, sp, #0x20
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	bl MTRandom
	ldr r1, _021E0518 ; =0x0000019E
	bl _u32_div_f
	ldr r0, [sp, #0x10]
	sub r1, #0x20
	str r1, [sp, #0x20]
	add r0, #0xb8
	ldr r0, [r0]
	cmp r0, #1
	bne _021E04DE
	ldr r0, [sp, #4]
	cmp r6, r0
	blt _021E04DE
	bl MTRandom
	mov r1, #0x14
	bl _u32_div_f
	mov r0, #0x27
	mvn r0, r0
	sub r0, r0, r1
	str r0, [sp, #0x24]
	b _021E04F0
_021E04DE:
	bl MTRandom
	mov r1, #0x14
	bl _u32_div_f
	mov r0, #7
	mvn r0, r0
	sub r0, r0, r1
	str r0, [sp, #0x24]
_021E04F0:
	ldr r0, [sp, #0x20]
	add r1, sp, #0x20
	lsl r0, r0, #0xc
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x24]
	lsl r0, r0, #0xc
	str r0, [sp, #0x24]
	mov r0, #0
	str r0, [sp, #0x28]
	ldr r0, [r4, #4]
	bl ov05_021DC4FC
	add r6, r6, #1
	cmp r6, r7
	blt _021E0436
_021E050E:
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_021E0514: .word 0x00000F58
_021E0518: .word 0x0000019E

	thumb_func_start ov05_021E051C
ov05_021E051C: ; 0x021E051C
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r6, r0, #0
	add r0, sp, #0
	add r1, r6, #0
	ldr r4, [r6, #8]
	bl ov05_021DD168
	add r5, sp, #0
	add r3, sp, #0xc
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r5, #0
	str r0, [r3]
	ldr r1, [r4, #0x14]
	ldr r0, [r4, #0xc]
	cmp r1, r0
	blt _021E0558
	mov r0, #1
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x10]
	str r5, [r4, #0x14]
	ldr r0, [r6, #4]
	add r1, r2, #0
	bl ov05_021DC4FC
_021E0558:
	ldr r0, [r4, #0x14]
	add r0, r0, #1
	str r0, [r4, #0x14]
	ldr r0, [sp, #0x10]
	asr r0, r0, #0xc
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x18]
	ldr r0, [r0]
	cmp r0, #1
	bne _021E0578
	ldr r0, [r4, #0x1c]
	sub r0, r0, #1
	str r0, [r4, #0x1c]
	cmp r0, #0
	bgt _021E0578
	mov r5, #1
_021E0578:
	ldr r1, [sp, #0x10]
	ldr r0, _021E05A4 ; =0xFFFFFEE4
	cmp r1, r0
	bge _021E0586
	sub r0, #0xc
	cmp r1, r0
	bgt _021E058E
_021E0586:
	cmp r1, #0xd4
	ble _021E0590
	cmp r1, #0xe8
	bge _021E0590
_021E058E:
	mov r5, #1
_021E0590:
	cmp r5, #1
	bne _021E05A0
	ldr r0, [r4]
	mov r1, #1
	str r1, [r0]
	add r0, r6, #0
	bl ov05_021DD100
_021E05A0:
	add sp, #0x18
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021E05A4: .word 0xFFFFFEE4

	thumb_func_start ov05_021E05A8
ov05_021E05A8: ; 0x021E05A8
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, _021E06EC ; =0x00000F58
	add r5, r1, #0
	add r1, r0, #0
	add r1, #0xa
	ldrh r1, [r5, r1]
	ldr r4, [r5, r0]
	cmp r1, #5
	bls _021E05BC
	b _021E06EA
_021E05BC:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E05C8: ; jump table
	.short _021E05D4 - _021E05C8 - 2 ; case 0
	.short _021E05D4 - _021E05C8 - 2 ; case 1
	.short _021E05D4 - _021E05C8 - 2 ; case 2
	.short _021E05F2 - _021E05C8 - 2 ; case 3
	.short _021E06DC - _021E05C8 - 2 ; case 4
	.short _021E06E4 - _021E05C8 - 2 ; case 5
_021E05D4:
	mov r0, #0
	str r0, [r4]
	str r0, [r4, #0x10]
	mov r1, #0x1f
	str r0, [r4, #4]
	bl ov05_021DC6D4
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, _021E06F0 ; =0x00000F62
	mov r1, #3
	strh r1, [r5, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021E05F2:
	ldr r0, [r4, #0x10]
	cmp r0, #0
	blt _021E05FE
	sub r0, r0, #1
	str r0, [r4, #0x10]
	b _021E06CC
_021E05FE:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021E060E
	cmp r0, #1
	beq _021E0650
	cmp r0, #2
	beq _021E0678
	b _021E06CC
_021E060E:
	mov r0, #1
	str r0, [r4, #4]
	mov r0, #0
	str r0, [r4, #0x14]
	bl MTRandom
	mov r1, #0x1e
	lsl r1, r1, #4
	bl _u32_div_f
	add r1, #0xc8
	str r1, [r4, #0x18]
	mov r0, #0
	str r0, [r4, #0x1c]
	bl MTRandom
	mov r1, #3
	bl _u32_div_f
	cmp r1, #0
	beq _021E0644
	mov r0, #0x24
	str r0, [r4, #8]
	ldr r0, _021E06F4 ; =0x0000063D
	bl PlaySE
	b _021E06CC
_021E0644:
	mov r0, #0xc8
	str r0, [r4, #8]
	ldr r0, _021E06F8 ; =0x0000063C
	bl PlaySE
	b _021E06CC
_021E0650:
	ldr r0, [r4, #0x14]
	add r0, r0, #1
	str r0, [r4, #0x14]
	ldr r1, [r4, #0x1c]
	ldr r0, [r4, #0x18]
	add r0, r1, r0
	str r0, [r4, #0x1c]
	ldr r0, [r4, #0x14]
	cmp r0, #2
	blt _021E0668
	mov r0, #2
	str r0, [r4, #4]
_021E0668:
	ldr r0, [r4, #0x1c]
	mov r1, #0x64
	bl _s32_div_f
	mov r1, #0x1f
	bl ov05_021DC6D4
	b _021E06CC
_021E0678:
	ldr r1, [r4, #0x1c]
	ldr r0, [r4, #8]
	sub r0, r1, r0
	str r0, [r4, #0x1c]
	cmp r0, #0
	bgt _021E06BE
	mov r0, #0
	str r0, [r4, #4]
	str r0, [r4, #0x1c]
	ldr r0, [r4, #8]
	cmp r0, #0xc8
	bne _021E069E
	bl MTRandom
	mov r1, #0xf
	bl _u32_div_f
	str r1, [r4, #0x10]
	b _021E06BE
_021E069E:
	bl MTRandom
	add r7, r0, #0
	ldr r1, [r4, #0x18]
	mov r0, #0x32
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	add r6, r0, #0
	add r0, r7, #0
	mov r1, #0x78
	bl _u32_div_f
	add r0, r6, r1
	str r0, [r4, #0x10]
_021E06BE:
	ldr r0, [r4, #0x1c]
	mov r1, #0x64
	bl _s32_div_f
	mov r1, #0x1f
	bl ov05_021DC6D4
_021E06CC:
	ldr r0, _021E06FC ; =0x00000F66
	ldrh r1, [r5, r0]
	cmp r1, #5
	bne _021E06EA
	mov r1, #4
	sub r0, r0, #4
	strh r1, [r5, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021E06DC:
	mov r1, #5
	add r0, #0xa
	strh r1, [r5, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021E06E4:
	ldr r0, [r5, #4]
	bl ov05_021DCB6C
_021E06EA:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E06EC: .word 0x00000F58
_021E06F0: .word 0x00000F62
_021E06F4: .word 0x0000063D
_021E06F8: .word 0x0000063C
_021E06FC: .word 0x00000F66

	thumb_func_start ov05_021E0700
ov05_021E0700: ; 0x021E0700
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r0, _021E0828 ; =0x00000F58
	add r4, r1, #0
	ldr r5, [r4, r0]
	add r0, #0xa
	ldrh r0, [r4, r0]
	cmp r0, #5
	bhi _021E07FE
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E071E: ; jump table
	.short _021E072A - _021E071E - 2 ; case 0
	.short _021E0752 - _021E071E - 2 ; case 1
	.short _021E0764 - _021E071E - 2 ; case 2
	.short _021E079E - _021E071E - 2 ; case 3
	.short _021E07DC - _021E071E - 2 ; case 4
	.short _021E07F8 - _021E071E - 2 ; case 5
_021E072A:
	mov r0, #4
	str r0, [sp]
	mov r0, #0xf
	str r0, [sp, #4]
	sub r0, #0x11
	str r0, [sp, #8]
	mov r0, #5
	str r0, [sp, #0xc]
	mov r2, #1
	ldr r0, _021E082C ; =ov05_021E083C
	str r2, [sp, #0x10]
	str r0, [sp, #0x14]
	add r0, r5, #0
	mov r3, #0x23
	bl ov05_021DD328
	ldr r0, _021E0830 ; =0x00000F62
	mov r1, #1
	strh r1, [r4, r0]
	b _021E07FE
_021E0752:
	add r0, r5, #0
	bl ov05_021DD35C
	cmp r0, #3
	bne _021E07FE
	ldr r0, _021E0830 ; =0x00000F62
	mov r1, #3
	strh r1, [r4, r0]
	b _021E07FE
_021E0764:
	mov r0, #0xf
	str r0, [sp]
	str r0, [sp, #4]
	sub r0, #0x11
	str r0, [sp, #8]
	mov r0, #5
	str r0, [sp, #0xc]
	mov r2, #1
	ldr r0, _021E082C ; =ov05_021E083C
	str r2, [sp, #0x10]
	str r0, [sp, #0x14]
	add r0, r5, #0
	mov r3, #4
	bl ov05_021DD328
	mov r0, #1
	str r0, [sp]
	ldr r0, _021E0834 ; =ov05_021E093C
	ldr r1, _021E082C ; =ov05_021E083C
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x10
	mov r3, #2
	bl ov05_021DD680
	ldr r0, _021E0830 ; =0x00000F62
	mov r1, #3
	strh r1, [r4, r0]
	b _021E07FE
_021E079E:
	mov r0, #6
	ldrsh r1, [r5, r0]
	sub r0, r1, #1
	strh r0, [r5, #6]
	cmp r1, #0
	bgt _021E07BA
	mov r1, #4
	ldrsh r1, [r5, r1]
	add r0, r4, #0
	bl ov05_021E083C
	mov r0, #8
	ldrsh r0, [r5, r0]
	strh r0, [r5, #6]
_021E07BA:
	ldr r0, _021E0838 ; =0x00000F66
	ldrh r0, [r4, r0]
	cmp r0, #5
	bne _021E07FE
	mov r0, #2
	mvn r0, r0
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0
	mov r2, #0x23
	mov r3, #2
	bl ov05_021DD350
	ldr r0, _021E0830 ; =0x00000F62
	mov r1, #4
	strh r1, [r4, r0]
	b _021E07FE
_021E07DC:
	add r0, r5, #0
	bl ov05_021DD35C
	cmp r0, #3
	bne _021E07FE
	add r0, r4, #0
	ldr r1, [r4, #0x40]
	add r0, #0xc
	cmp r1, r0
	bne _021E07FE
	ldr r0, _021E0830 ; =0x00000F62
	mov r1, #5
	strh r1, [r4, r0]
	b _021E07FE
_021E07F8:
	ldr r0, [r4, #4]
	bl ov05_021DCB6C
_021E07FE:
	ldr r0, _021E0830 ; =0x00000F62
	ldrh r0, [r4, r0]
	cmp r0, #5
	beq _021E0824
	cmp r0, #0
	beq _021E0824
	add r0, r4, #0
	ldr r1, _021E0834 ; =ov05_021E093C
	add r0, #0xc
	bl ov05_021DD148
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl ov05_021DD2BC
	add r0, r4, #0
	bl ov05_021DD164
_021E0824:
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021E0828: .word 0x00000F58
_021E082C: .word ov05_021E083C
_021E0830: .word 0x00000F62
_021E0834: .word ov05_021E093C
_021E0838: .word 0x00000F66

	thumb_func_start ov05_021E083C
ov05_021E083C: ; 0x021E083C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r0, [sp]
	add r0, r1, #0
	mov r7, #0
	str r1, [sp, #4]
	cmp r0, #0
	ble _021E0932
_021E084C:
	ldr r0, [sp]
	mov r1, #0x20
	bl ov05_021DD048
	add r5, r0, #0
	beq _021E0932
	ldr r4, [r5, #8]
	bl MTRandom
	mov r1, #0xe
	bl _u32_div_f
	add r6, r1, #0
	lsl r1, r6, #0x10
	ldr r0, [r5, #4]
	lsr r1, r1, #0x10
	bl sub_02020208
	asr r0, r6, #1
	lsr r0, r0, #0x1e
	add r0, r6, r0
	asr r6, r0, #2
	bl MTRandom
	mov r1, #0x19
	bl _u32_div_f
	add r2, r1, #0
	add r2, #8
	add r1, r6, #1
	add r0, r2, #0
	mul r0, r1
	str r0, [r4]
	mov r0, #0x10
	bl _s32_div_f
	str r0, [r4, #4]
	mov r0, #0
	str r0, [r4, #8]
	bl MTRandom
	mov r1, #1
	and r0, r1
	str r0, [r4, #0xc]
	add r0, r1, #0
	str r0, [r4, #0x10]
	add r0, r6, #1
	cmp r0, #4
	bhi _021E0912
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E08BA: ; jump table
	.short _021E0912 - _021E08BA - 2 ; case 0
	.short _021E08C4 - _021E08BA - 2 ; case 1
	.short _021E08C4 - _021E08BA - 2 ; case 2
	.short _021E08E0 - _021E08BA - 2 ; case 3
	.short _021E08FA - _021E08BA - 2 ; case 4
_021E08C4:
	bl MTRandom
	ldr r1, _021E0938 ; =0x000001FF
	and r0, r1
	sub r0, #0x80
	str r0, [sp, #8]
	bl MTRandom
	mov r1, #0xc0
	bl _u32_div_f
	add r1, #8
	str r1, [sp, #0xc]
	b _021E0912
_021E08E0:
	bl MTRandom
	ldr r1, _021E0938 ; =0x000001FF
	and r0, r1
	sub r0, #0x80
	str r0, [sp, #8]
	bl MTRandom
	mov r1, #0x7f
	and r0, r1
	add r0, #0x40
	str r0, [sp, #0xc]
	b _021E0912
_021E08FA:
	bl MTRandom
	ldr r1, _021E0938 ; =0x000001FF
	and r0, r1
	sub r0, #0x80
	str r0, [sp, #8]
	bl MTRandom
	mov r1, #0x1f
	and r0, r1
	add r0, #0xa0
	str r0, [sp, #0xc]
_021E0912:
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [sp, #8]
	add r1, sp, #8
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, [r5, #4]
	bl ov05_021DC4FC
	ldr r0, [sp, #4]
	add r7, r7, #1
	cmp r7, r0
	blt _021E084C
_021E0932:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021E0938: .word 0x000001FF

	thumb_func_start ov05_021E093C
ov05_021E093C: ; 0x021E093C
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r0, sp, #0
	add r1, r5, #0
	ldr r4, [r5, #8]
	bl ov05_021DD168
	add r3, sp, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r1, [r4, #8]
	ldr r0, [r4, #4]
	add r0, r1, r0
	str r0, [r4, #8]
	ldr r0, [r4]
	cmp r0, #0
	ble _021E097C
	sub r0, r0, #1
	str r0, [r4]
	ldr r0, [r4, #8]
	mov r1, #0x64
	bl _s32_div_f
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0xc
	sub r0, r1, r0
	str r0, [sp, #0x10]
	b _021E098C
_021E097C:
	ldr r0, [r4, #8]
	mov r1, #0x32
	bl _s32_div_f
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0xc
	sub r0, r1, r0
	str r0, [sp, #0x10]
_021E098C:
	ldr r0, [r4, #0x10]
	sub r0, r0, #1
	str r0, [r4, #0x10]
	cmp r0, #0
	bgt _021E09B8
	mov r0, #1
	str r0, [r4, #0x10]
	ldr r1, [r4, #0xc]
	cmp r1, #0
	bne _021E09AC
	ldr r2, [sp, #0xc]
	lsl r1, r0, #0xd
	add r1, r2, r1
	str r1, [sp, #0xc]
	str r0, [r4, #0xc]
	b _021E09B8
_021E09AC:
	ldr r1, [sp, #0xc]
	lsl r0, r0, #0xd
	sub r0, r1, r0
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [r4, #0xc]
_021E09B8:
	ldr r0, [r5, #4]
	add r1, sp, #0xc
	bl ov05_021DC4FC
	ldr r0, [sp, #0x10]
	asr r1, r0, #0xc
	mov r0, #0xf
	mvn r0, r0
	cmp r1, r0
	bgt _021E09D2
	add r0, r5, #0
	bl ov05_021DD100
_021E09D2:
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021E09D8
ov05_021E09D8: ; 0x021E09D8
	push {r4, r5, r6, lr}
	ldr r0, _021E0ABC ; =0x00000F58
	add r4, r1, #0
	add r1, r0, #0
	add r1, #0xa
	ldrh r1, [r4, r1]
	ldr r5, [r4, r0]
	cmp r1, #5
	bhi _021E0AB8
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E09F6: ; jump table
	.short _021E0A02 - _021E09F6 - 2 ; case 0
	.short _021E0A34 - _021E09F6 - 2 ; case 1
	.short _021E0A52 - _021E09F6 - 2 ; case 2
	.short _021E0A78 - _021E09F6 - 2 ; case 3
	.short _021E0A94 - _021E09F6 - 2 ; case 4
	.short _021E0AB2 - _021E09F6 - 2 ; case 5
_021E0A02:
	add r0, r5, #0
	mov r1, #0
	mov r2, #0x10
	mov r3, #8
	bl ov05_021DC6EC
	mov r0, #0
	mov r1, #0x10
	bl ov05_021DC6D4
	ldr r1, _021E0AC0 ; =0x0400000C
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #3
	orr r0, r2
	strh r0, [r1]
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, _021E0AC4 ; =0x00000F62
	mov r1, #1
	strh r1, [r4, r0]
	pop {r4, r5, r6, pc}
_021E0A34:
	add r0, r5, #0
	bl ov05_021DC6FC
	add r6, r0, #0
	ldr r0, [r5]
	mov r1, #0x10
	sub r1, r1, r0
	bl ov05_021DC6D4
	cmp r6, #1
	bne _021E0AB8
	ldr r0, _021E0AC4 ; =0x00000F62
	mov r1, #3
	strh r1, [r4, r0]
	pop {r4, r5, r6, pc}
_021E0A52:
	mov r0, #0x10
	mov r1, #0
	bl ov05_021DC6D4
	ldr r1, _021E0AC0 ; =0x0400000C
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #3
	orr r0, r2
	strh r0, [r1]
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, _021E0AC4 ; =0x00000F62
	mov r1, #3
	strh r1, [r4, r0]
	pop {r4, r5, r6, pc}
_021E0A78:
	add r0, #0xe
	ldrh r0, [r4, r0]
	cmp r0, #5
	bne _021E0AB8
	add r0, r5, #0
	mov r1, #0x10
	mov r2, #0
	mov r3, #8
	bl ov05_021DC6EC
	ldr r0, _021E0AC4 ; =0x00000F62
	mov r1, #4
	strh r1, [r4, r0]
	pop {r4, r5, r6, pc}
_021E0A94:
	add r0, r5, #0
	bl ov05_021DC6FC
	add r6, r0, #0
	ldr r0, [r5]
	mov r1, #0x10
	sub r1, r1, r0
	bl ov05_021DC6D4
	cmp r6, #1
	bne _021E0AB8
	ldr r0, _021E0AC4 ; =0x00000F62
	mov r1, #5
	strh r1, [r4, r0]
	pop {r4, r5, r6, pc}
_021E0AB2:
	ldr r0, [r4, #4]
	bl ov05_021DCB6C
_021E0AB8:
	pop {r4, r5, r6, pc}
	nop
_021E0ABC: .word 0x00000F58
_021E0AC0: .word 0x0400000C
_021E0AC4: .word 0x00000F62

	thumb_func_start ov05_021E0AC8
ov05_021E0AC8: ; 0x021E0AC8
	push {r4, r5, r6, lr}
	ldr r0, _021E0B90 ; =0x00000F58
	add r4, r1, #0
	add r1, r0, #0
	add r1, #0xa
	ldrh r1, [r4, r1]
	ldr r5, [r4, r0]
	cmp r1, #5
	bhi _021E0B8C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E0AE6: ; jump table
	.short _021E0AF2 - _021E0AE6 - 2 ; case 0
	.short _021E0B16 - _021E0AE6 - 2 ; case 1
	.short _021E0B34 - _021E0AE6 - 2 ; case 2
	.short _021E0B4C - _021E0AE6 - 2 ; case 3
	.short _021E0B68 - _021E0AE6 - 2 ; case 4
	.short _021E0B86 - _021E0AE6 - 2 ; case 5
_021E0AF2:
	add r0, r5, #0
	mov r1, #0
	mov r2, #4
	mov r3, #8
	bl ov05_021DC6EC
	mov r0, #0
	mov r1, #0x10
	bl ov05_021DC6D4
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, _021E0B94 ; =0x00000F62
	mov r1, #1
	strh r1, [r4, r0]
	pop {r4, r5, r6, pc}
_021E0B16:
	add r0, r5, #0
	bl ov05_021DC6FC
	add r6, r0, #0
	ldr r0, [r5]
	mov r1, #0x10
	sub r1, r1, r0
	bl ov05_021DC6D4
	cmp r6, #0
	beq _021E0B8C
	ldr r0, _021E0B94 ; =0x00000F62
	mov r1, #3
	strh r1, [r4, r0]
	pop {r4, r5, r6, pc}
_021E0B34:
	mov r0, #4
	mov r1, #0xc
	bl ov05_021DC6D4
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, _021E0B94 ; =0x00000F62
	mov r1, #3
	strh r1, [r4, r0]
	pop {r4, r5, r6, pc}
_021E0B4C:
	add r0, #0xe
	ldrh r0, [r4, r0]
	cmp r0, #5
	bne _021E0B8C
	add r0, r5, #0
	mov r1, #4
	mov r2, #0
	mov r3, #8
	bl ov05_021DC6EC
	ldr r0, _021E0B94 ; =0x00000F62
	mov r1, #4
	strh r1, [r4, r0]
	pop {r4, r5, r6, pc}
_021E0B68:
	add r0, r5, #0
	bl ov05_021DC6FC
	add r6, r0, #0
	ldr r0, [r5]
	mov r1, #0x10
	sub r1, r1, r0
	bl ov05_021DC6D4
	cmp r6, #0
	beq _021E0B8C
	ldr r0, _021E0B94 ; =0x00000F62
	mov r1, #5
	strh r1, [r4, r0]
	pop {r4, r5, r6, pc}
_021E0B86:
	ldr r0, [r4, #4]
	bl ov05_021DCB6C
_021E0B8C:
	pop {r4, r5, r6, pc}
	nop
_021E0B90: .word 0x00000F58
_021E0B94: .word 0x00000F62

	thumb_func_start ov05_021E0B98
ov05_021E0B98: ; 0x021E0B98
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	ldr r0, _021E0D14 ; =0x00000F58
	add r4, r1, #0
	add r1, r0, #0
	add r1, #0xa
	ldrh r1, [r4, r1]
	ldr r5, [r4, r0]
	cmp r1, #5
	bls _021E0BAE
	b _021E0D10
_021E0BAE:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E0BBA: ; jump table
	.short _021E0BC6 - _021E0BBA - 2 ; case 0
	.short _021E0C16 - _021E0BBA - 2 ; case 1
	.short _021E0C44 - _021E0BBA - 2 ; case 2
	.short _021E0C84 - _021E0BBA - 2 ; case 3
	.short _021E0CB8 - _021E0BBA - 2 ; case 4
	.short _021E0CF2 - _021E0BBA - 2 ; case 5
_021E0BC6:
	ldr r1, _021E0D18 ; =0x0000764F
	mov r2, #0x41
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	add r0, #0xc
	ldrh r0, [r4, r0]
	add r1, r5, #0
	lsl r2, r2, #2
	str r0, [sp, #0xc]
	ldr r3, [r4]
	add r0, r5, #0
	ldr r2, [r3, r2]
	add r0, #0x44
	ldr r2, [r2, #0x44]
	add r1, #0x14
	mov r3, #7
	bl ov05_021DD420
	add r0, r5, #0
	mov r1, #0
	mov r2, #9
	mov r3, #0x1e
	bl ov05_021DC6EC
	mov r0, #0
	mov r1, #0x10
	bl ov05_021DC6D4
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, _021E0D1C ; =0x00000F62
	mov r1, #1
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021E0C16:
	add r0, r5, #0
	add r0, #0x14
	bl ov05_021DD5D0
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021DC6FC
	add r7, r0, #0
	ldr r0, [r5]
	mov r1, #0x10
	sub r1, r1, r0
	bl ov05_021DC6D4
	cmp r6, #1
	bne _021E0D10
	cmp r7, #1
	bne _021E0D10
	ldr r0, _021E0D1C ; =0x00000F62
	mov r1, #3
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021E0C44:
	add r0, #0xc
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _021E0C6A
	mov r0, #0x41
	ldr r1, [r4]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r2, _021E0D18 ; =0x0000764F
	ldr r0, [r0, #0x44]
	mov r1, #7
	mov r3, #0
	str r0, [r5, #0x14]
	bl ov05_021DD49C
	add r5, #0x14
	add r0, r5, #0
	bl ov05_021DD5EC
_021E0C6A:
	mov r0, #9
	mov r1, #7
	bl ov05_021DC6D4
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, _021E0D1C ; =0x00000F62
	mov r1, #3
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021E0C84:
	add r1, r0, #0
	add r1, #0xe
	ldrh r1, [r4, r1]
	cmp r1, #5
	bne _021E0D10
	add r0, #0xc
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _021E0CA2
	add r0, r5, #0
	add r0, #0x14
	mov r1, #1
	mov r2, #0
	bl ov05_021DD5B4
_021E0CA2:
	add r0, r5, #0
	mov r1, #9
	mov r2, #0
	mov r3, #0x1e
	bl ov05_021DC6EC
	ldr r0, _021E0D1C ; =0x00000F62
	mov r1, #4
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021E0CB8:
	add r0, #0xc
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _021E0CCC
	add r0, r5, #0
	add r0, #0x14
	bl ov05_021DD5D0
	add r6, r0, #0
	b _021E0CCE
_021E0CCC:
	mov r6, #1
_021E0CCE:
	add r0, r5, #0
	bl ov05_021DC6FC
	add r7, r0, #0
	ldr r0, [r5]
	mov r1, #0x10
	sub r1, r1, r0
	bl ov05_021DC6D4
	cmp r6, #1
	bne _021E0D10
	cmp r7, #1
	bne _021E0D10
	ldr r0, _021E0D1C ; =0x00000F62
	mov r1, #5
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021E0CF2:
	add r0, #0xc
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _021E0D0A
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r0, [r5, #0x14]
	mov r1, #1
	add r3, r2, #0
	bl ov05_021DBA40
_021E0D0A:
	ldr r0, [r4, #4]
	bl ov05_021DCB6C
_021E0D10:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E0D14: .word 0x00000F58
_021E0D18: .word 0x0000764F
_021E0D1C: .word 0x00000F62

	thumb_func_start ov05_021E0D20
ov05_021E0D20: ; 0x021E0D20
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	ldr r0, _021E0E9C ; =0x00000F58
	add r4, r1, #0
	add r1, r0, #0
	add r1, #0xa
	ldrh r1, [r4, r1]
	ldr r5, [r4, r0]
	cmp r1, #5
	bls _021E0D36
	b _021E0E98
_021E0D36:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E0D42: ; jump table
	.short _021E0D4E - _021E0D42 - 2 ; case 0
	.short _021E0D9E - _021E0D42 - 2 ; case 1
	.short _021E0DCC - _021E0D42 - 2 ; case 2
	.short _021E0E0C - _021E0D42 - 2 ; case 3
	.short _021E0E40 - _021E0D42 - 2 ; case 4
	.short _021E0E7A - _021E0D42 - 2 ; case 5
_021E0D4E:
	ldr r1, _021E0EA0 ; =0x00007555
	mov r2, #0x41
	str r1, [sp]
	ldr r1, _021E0EA4 ; =0x00007FFF
	add r0, #0xc
	str r1, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	ldrh r0, [r4, r0]
	add r1, r5, #0
	lsl r2, r2, #2
	str r0, [sp, #0xc]
	ldr r3, [r4]
	add r0, r5, #0
	ldr r2, [r3, r2]
	add r0, #0x44
	ldr r2, [r2, #0x44]
	add r1, #0x14
	mov r3, #6
	bl ov05_021DD420
	add r0, r5, #0
	mov r1, #0
	mov r2, #9
	mov r3, #0x1e
	bl ov05_021DC6EC
	mov r0, #0
	mov r1, #0x10
	bl ov05_021DC6D4
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, _021E0EA8 ; =0x00000F62
	mov r1, #1
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021E0D9E:
	add r0, r5, #0
	add r0, #0x14
	bl ov05_021DD5D0
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021DC6FC
	add r7, r0, #0
	ldr r0, [r5]
	mov r1, #0x10
	sub r1, r1, r0
	bl ov05_021DC6D4
	cmp r6, #1
	bne _021E0E98
	cmp r7, #1
	bne _021E0E98
	ldr r0, _021E0EA8 ; =0x00000F62
	mov r1, #3
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021E0DCC:
	add r0, #0xc
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _021E0DF2
	mov r0, #0x41
	ldr r1, [r4]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r2, _021E0EA0 ; =0x00007555
	ldr r0, [r0, #0x44]
	ldr r3, _021E0EA4 ; =0x00007FFF
	mov r1, #6
	str r0, [r5, #0x14]
	bl ov05_021DD49C
	add r5, #0x14
	add r0, r5, #0
	bl ov05_021DD5EC
_021E0DF2:
	mov r0, #9
	mov r1, #7
	bl ov05_021DC6D4
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, _021E0EA8 ; =0x00000F62
	mov r1, #3
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021E0E0C:
	add r1, r0, #0
	add r1, #0xe
	ldrh r1, [r4, r1]
	cmp r1, #5
	bne _021E0E98
	add r0, #0xc
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _021E0E2A
	add r0, r5, #0
	add r0, #0x14
	mov r1, #1
	mov r2, #0
	bl ov05_021DD5B4
_021E0E2A:
	add r0, r5, #0
	mov r1, #9
	mov r2, #0
	mov r3, #0x1e
	bl ov05_021DC6EC
	ldr r0, _021E0EA8 ; =0x00000F62
	mov r1, #4
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021E0E40:
	add r0, #0xc
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _021E0E54
	add r0, r5, #0
	add r0, #0x14
	bl ov05_021DD5D0
	add r6, r0, #0
	b _021E0E56
_021E0E54:
	mov r6, #1
_021E0E56:
	add r0, r5, #0
	bl ov05_021DC6FC
	add r7, r0, #0
	ldr r0, [r5]
	mov r1, #0x10
	sub r1, r1, r0
	bl ov05_021DC6D4
	cmp r6, #1
	bne _021E0E98
	cmp r7, #1
	bne _021E0E98
	ldr r0, _021E0EA8 ; =0x00000F62
	mov r1, #5
	add sp, #0x10
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021E0E7A:
	add r0, #0xc
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _021E0E92
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r0, [r5, #0x14]
	mov r1, #1
	add r3, r2, #0
	bl ov05_021DBA40
_021E0E92:
	ldr r0, [r4, #4]
	bl ov05_021DCB6C
_021E0E98:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E0E9C: .word 0x00000F58
_021E0EA0: .word 0x00007555
_021E0EA4: .word 0x00007FFF
_021E0EA8: .word 0x00000F62

	thumb_func_start ov05_021E0EAC
ov05_021E0EAC: ; 0x021E0EAC
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	mov r0, #0x41
	ldr r1, [r4]
	lsl r0, r0, #2
	ldr r1, [r1, r0]
	ldr r0, _021E0F9C ; =0x00000F58
	add r2, r0, #0
	add r2, #0xa
	ldrh r2, [r4, r2]
	ldr r5, [r4, r0]
	cmp r2, #5
	bhi _021E0F98
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021E0ED4: ; jump table
	.short _021E0EE0 - _021E0ED4 - 2 ; case 0
	.short _021E0F0A - _021E0ED4 - 2 ; case 1
	.short _021E0F2C - _021E0ED4 - 2 ; case 2
	.short _021E0F3E - _021E0ED4 - 2 ; case 3
	.short _021E0F70 - _021E0ED4 - 2 ; case 4
	.short _021E0F8C - _021E0ED4 - 2 ; case 5
_021E0EE0:
	ldr r1, [r1, #4]
	add r0, r5, #0
	ldr r1, [r1, #0x1c]
	bl ov05_021E1100
	mov r0, #0x54
	mov r1, #1
	str r0, [sp]
	mov r0, #0x1e
	lsl r1, r1, #0x14
	str r0, [sp, #4]
	add r0, r5, #0
	lsr r2, r1, #3
	mov r3, #0x80
	bl ov05_021E11CC
	ldr r0, _021E0FA0 ; =0x00000F62
	mov r1, #1
	add sp, #8
	strh r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021E0F0A:
	add r0, r5, #0
	bl ov05_021E11EC
	cmp r0, #1
	bne _021E0F98
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	add r0, r5, #0
	bl ov05_021E1290
	ldr r0, _021E0FA0 ; =0x00000F62
	mov r1, #3
	add sp, #8
	strh r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021E0F2C:
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, _021E0FA0 ; =0x00000F62
	mov r1, #3
	add sp, #8
	strh r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021E0F3E:
	add r0, #0xe
	ldrh r0, [r4, r0]
	cmp r0, #5
	bne _021E0F98
	ldr r1, [r1, #4]
	add r0, r5, #0
	ldr r1, [r1, #0x1c]
	bl ov05_021E1100
	mov r0, #0x54
	mov r1, #2
	str r0, [sp]
	mov r0, #0x1e
	lsl r1, r1, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	lsl r2, r1, #3
	mov r3, #0x80
	bl ov05_021E11CC
	ldr r0, _021E0FA0 ; =0x00000F62
	mov r1, #4
	add sp, #8
	strh r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021E0F70:
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	add r0, r5, #0
	bl ov05_021E11EC
	cmp r0, #1
	bne _021E0F98
	ldr r0, _021E0FA0 ; =0x00000F62
	mov r1, #5
	add sp, #8
	strh r1, [r4, r0]
	pop {r3, r4, r5, pc}
_021E0F8C:
	add r0, r5, #0
	bl ov05_021E117C
	ldr r0, [r4, #4]
	bl ov05_021DCB6C
_021E0F98:
	add sp, #8
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021E0F9C: .word 0x00000F58
_021E0FA0: .word 0x00000F62

	thumb_func_start ov05_021E0FA4
ov05_021E0FA4: ; 0x021E0FA4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021E0FCC ; =0x00000F5C
	add r4, r1, #0
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021E0FB6
	bl GF_AssertFail
_021E0FB6:
	ldr r1, _021E0FCC ; =0x00000F5C
	mov r0, #1
	str r0, [r5, r1]
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	add r1, r1, #4
	strh r0, [r5, r1]
	bl PlaySE
	pop {r3, r4, r5, pc}
	nop
_021E0FCC: .word 0x00000F5C

	thumb_func_start ov05_021E0FD0
ov05_021E0FD0: ; 0x021E0FD0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xf6
	lsl r0, r0, #4
	ldrh r0, [r4, r0]
	mov r1, #0
	bl sub_020054F0
	ldr r0, _021E0FE8 ; =0x00000F5C
	mov r1, #0
	str r1, [r4, r0]
	pop {r4, pc}
	.balign 4, 0
_021E0FE8: .word 0x00000F5C

	thumb_func_start ov05_021E0FEC
ov05_021E0FEC: ; 0x021E0FEC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r0, [r5, #0x1c]
	bl sub_02012988
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x20]
	bl sub_02012988
	ldr r7, [sp, #0xc]
	str r0, [sp, #8]
	mov r4, #0
	add r6, r0, #0
_021E1008:
	mov r0, #2
	ldrsh r2, [r5, r0]
	cmp r4, r2
	bgt _021E1026
	add r0, sp, #0x14
	str r0, [sp]
	add r0, sp, #0x10
	str r0, [sp, #4]
	mov r1, #0
	ldrsh r1, [r5, r1]
	ldr r0, [r5, #4]
	add r3, r4, #0
	bl ov05_021E1074
	b _021E105C
_021E1026:
	lsl r0, r2, #1
	cmp r4, r0
	bgt _021E1048
	sub r0, r0, r4
	lsl r1, r0, #1
	ldr r0, [sp, #0xc]
	ldrh r0, [r0, r1]
	str r0, [sp, #0x14]
	mov r0, #2
	ldrsh r0, [r5, r0]
	lsl r0, r0, #1
	sub r0, r0, r4
	lsl r1, r0, #1
	ldr r0, [sp, #8]
	ldrh r0, [r0, r1]
	str r0, [sp, #0x10]
	b _021E105C
_021E1048:
	add r0, sp, #0x14
	str r0, [sp]
	add r0, sp, #0x10
	str r0, [sp, #4]
	mov r1, #0
	ldrsh r1, [r5, r1]
	ldr r0, [r5, #4]
	add r3, r4, #0
	bl ov05_021E1074
_021E105C:
	ldr r0, [sp, #0x14]
	add r4, r4, #1
	strh r0, [r7]
	ldr r0, [sp, #0x10]
	add r7, r7, #2
	strh r0, [r6]
	add r6, r6, #2
	cmp r4, #0xc0
	blt _021E1008
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021E1074
ov05_021E1074: ; 0x021E1074
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r1, [sp]
	ldr r5, [sp, #0x20]
	ldr r4, [sp, #0x24]
	sub r1, r3, r2
	bpl _021E1084
	neg r1, r1
_021E1084:
	cmp r1, r0
	blt _021E1092
	mov r0, #0
	str r0, [r5]
	add sp, #0xc
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_021E1092:
	lsl r1, r1, #0xc
	str r1, [sp, #4]
	asr r7, r1, #0x1f
	asr r1, r0, #0x1f
	add r2, r0, #0
	add r3, r1, #0
	bl _ll_mul
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	add r6, r1, #0
	add r1, r7, #0
	add r2, r0, #0
	add r3, r7, #0
	bl _ll_mul
	add r2, r0, #0
	add r3, r1, #0
	mov r0, #2
	ldr r1, [sp, #8]
	mov r7, #0
	lsl r0, r0, #0xa
	add r0, r1, r0
	adc r6, r7
	lsl r1, r6, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	mov r1, #2
	lsl r1, r1, #0xa
	add r2, r2, r1
	adc r3, r7
	lsl r1, r3, #0x14
	lsr r2, r2, #0xc
	orr r2, r1
	sub r0, r0, r2
	bl FX_Sqrt
	asr r2, r0, #0xc
	ldr r0, [sp]
	sub r0, r0, r2
	str r0, [r5]
	bpl _021E10EA
	add r0, r7, #0
	str r0, [r5]
_021E10EA:
	ldr r1, [r5]
	lsl r0, r2, #1
	add r0, r1, r0
	str r0, [r4]
	cmp r0, #0xff
	ble _021E10FA
	mov r0, #0xff
	str r0, [r4]
_021E10FA:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021E1100
ov05_021E1100: ; 0x021E1100
	push {r4, r5, r6, lr}
	ldr r2, _021E116C ; =0x0000062C
	add r4, r1, #0
	mov r1, #0
	add r5, r0, #0
	bl memset
	mov r2, #0x6b
	add r1, r5, #0
	lsl r2, r2, #2
	mov r0, #4
	add r1, #0x2c
	add r2, r5, r2
	bl sub_02012944
	mov r1, #0xcb
	ldr r2, _021E1170 ; =0x000004AC
	lsl r1, r1, #2
	str r0, [r5, #0x1c]
	mov r0, #4
	add r1, r5, r1
	add r2, r5, r2
	bl sub_02012944
	str r0, [r5, #0x20]
	mov r0, #0xcb
	ldr r1, _021E1170 ; =0x000004AC
	mov r3, #0
	add r6, r5, #0
	mov r2, #0xff
	lsl r0, r0, #2
_021E113E:
	strh r2, [r6, r0]
	strh r2, [r6, r1]
	add r3, r3, #1
	add r6, r6, #2
	cmp r3, #0xc0
	blt _021E113E
	ldr r0, _021E1174 ; =ov05_021E12E4
	add r1, r5, #0
	mov r2, #0x78
	str r4, [r5, #0x14]
	bl sub_0200CA98
	mov r2, #1
	ldr r0, _021E1178 ; =ov05_021E1278
	add r1, r5, #0
	lsl r2, r2, #0xa
	bl sub_0200CA98
	str r0, [r5, #0x24]
	mov r0, #0
	str r0, [r5, #0x28]
	pop {r4, r5, r6, pc}
	nop
_021E116C: .word 0x0000062C
_021E1170: .word 0x000004AC
_021E1174: .word ov05_021E12E4
_021E1178: .word ov05_021E1278

	thumb_func_start ov05_021E117C
ov05_021E117C: ; 0x021E117C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	lsl r0, r0, #0x1a
	mov r1, #0xe
	ldr r2, [r0]
	lsl r1, r1, #0xc
	and r1, r2
	lsr r3, r1, #0xd
	ldr r2, [r0]
	ldr r1, _021E11C4 ; =0xFFFF1FFF
	and r2, r1
	mov r1, #2
	bic r3, r1
	lsl r1, r3, #0xd
	orr r1, r2
	str r1, [r0]
	ldr r0, [r4, #0x18]
	bl ov05_021F4648
	ldr r0, [r4, #0x24]
	bl sub_0200CAB4
	ldr r0, [r4, #0x1c]
	bl sub_02012974
	ldr r0, [r4, #0x20]
	bl sub_02012974
	ldr r2, _021E11C8 ; =0x0000062C
	add r0, r4, #0
	mov r1, #0
	bl memset
	pop {r4, pc}
	nop
_021E11C4: .word 0xFFFF1FFF
_021E11C8: .word 0x0000062C

	thumb_func_start ov05_021E11CC
ov05_021E11CC: ; 0x021E11CC
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r5, r3, #0
	ldr r3, [sp, #0x14]
	add r0, r4, #4
	bl ov05_021DC728
	ldr r0, [sp, #0x10]
	strh r5, [r4]
	strh r0, [r4, #2]
	mov r0, #1
	str r0, [r4, #0x28]
	add r0, r4, #0
	bl ov05_021E0FEC
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021E11EC
ov05_021E11EC: ; 0x021E11EC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r1, [r5, #0x28]
	cmp r1, #0
	bne _021E11FE
	bl ov05_021E12B8
	mov r0, #1
	pop {r3, r4, r5, pc}
_021E11FE:
	add r0, r5, #4
	bl ov05_021DC738
	add r4, r0, #0
	add r0, r5, #0
	bl ov05_021E0FEC
	cmp r4, #1
	bne _021E1214
	mov r0, #0
	str r0, [r5, #0x28]
_021E1214:
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021E1218
ov05_021E1218: ; 0x021E1218
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	ldr r0, _021E1270 ; =0x04000006
	add r5, r1, #0
	ldrh r7, [r0]
	mov r6, #0
	add r4, sp, #0
_021E1226:
	ldr r0, [r5, #0x1c]
	bl sub_0201299C
	add r6, r6, #1
	add r5, r5, #4
	stmia r4!, {r0}
	cmp r6, #2
	blt _021E1226
	cmp r7, #0xc0
	bge _021E126C
	add r7, r7, #1
	cmp r7, #0xc0
	blt _021E1242
	sub r7, #0xc0
_021E1242:
	ldr r1, _021E1274 ; =0x04000004
	mov r0, #2
	ldrh r2, [r1]
	tst r0, r2
	beq _021E126C
	ldr r2, [sp]
	lsl r0, r7, #1
	ldrh r2, [r2, r0]
	lsl r3, r2, #8
	mov r2, #0xff
	lsl r2, r2, #8
	and r3, r2
	ldr r2, [sp, #4]
	ldrh r0, [r2, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	orr r0, r3
	strh r0, [r1, #0x3e]
	mov r0, #0xc0
	add r1, #0x42
	strh r0, [r1]
_021E126C:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E1270: .word 0x04000006
_021E1274: .word 0x04000004

	thumb_func_start ov05_021E1278
ov05_021E1278: ; 0x021E1278
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r4, #0
_021E127E:
	ldr r0, [r5, #0x1c]
	bl sub_020129B4
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #2
	blt _021E127E
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021E1290
ov05_021E1290: ; 0x021E1290
	ldr r3, _021E129C ; =sub_0200CA98
	add r1, r0, #0
	ldr r0, _021E12A0 ; =ov05_021E12A4
	mov r2, #0x80
	bx r3
	nop
_021E129C: .word sub_0200CA98
_021E12A0: .word ov05_021E12A4

	thumb_func_start ov05_021E12A4
ov05_021E12A4: ; 0x021E12A4
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	bl ov05_021E117C
	add r0, r4, #0
	bl sub_0200CAB4
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021E12B8
ov05_021E12B8: ; 0x021E12B8
	push {r3, r4, r5, r6, r7, lr}
	mov r7, #6
	add r5, r0, #0
	mov r4, #0
	lsl r7, r7, #6
_021E12C2:
	ldr r0, [r5, #0x1c]
	bl sub_0201299C
	add r6, r0, #0
	ldr r0, [r5, #0x1c]
	bl sub_02012988
	add r1, r6, #0
	add r2, r7, #0
	bl memcpy
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #2
	blt _021E12C2
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021E12E4
ov05_021E12E4: ; 0x021E12E4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	ldr r1, _021E1364 ; =0x0400004A
	add r5, r0, #0
	ldrb r0, [r1]
	add r7, sp, #0
	ldr r3, _021E1368 ; =0xFFFFC0FF
	strb r0, [r7]
	add r0, r1, #0
	sub r0, #0x4a
	ldr r2, [r0]
	mov r0, #0xe
	lsl r0, r0, #0xc
	and r0, r2
	lsr r2, r0, #0xd
	sub r0, r1, #2
	ldrh r6, [r0]
	and r6, r3
	mov r3, #0x3f
	lsl r3, r3, #8
	orr r6, r3
	lsr r3, r1, #0xd
	orr r3, r6
	strh r3, [r0]
	ldrh r1, [r1]
	mov r0, #0x3f
	bic r1, r0
	mov r0, #0x3e
	orr r0, r1
	ldrb r1, [r7]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1f
	beq _021E132A
	mov r1, #0x20
	orr r0, r1
_021E132A:
	ldr r1, _021E1364 ; =0x0400004A
	mov r3, #0xff
	strh r0, [r1]
	add r0, r1, #0
	sub r0, #8
	strh r3, [r0]
	sub r0, r1, #4
	mov r3, #0xc0
	strh r3, [r0]
	sub r1, #0x4a
	ldr r3, [r1]
	ldr r0, _021E136C ; =0xFFFF1FFF
	and r0, r3
	mov r3, #2
	orr r2, r3
	lsl r2, r2, #0xd
	orr r0, r2
	str r0, [r1]
	ldr r0, [r4, #0x14]
	ldr r1, _021E1370 ; =ov05_021E1218
	add r2, r4, #0
	bl ov05_021F4624
	str r0, [r4, #0x18]
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E1364: .word 0x0400004A
_021E1368: .word 0xFFFFC0FF
_021E136C: .word 0xFFFF1FFF
_021E1370: .word ov05_021E1218

	.section .rodata

	.global ov05_021F67C8
ov05_021F67C8: ; 0x021F67C8
	.word 0x00000002, 0x00000002, 0x00000002, 0x00000002

	.global ov05_021F67D8
ov05_021F67D8: ; 0x021F67D8
	.word 0x00000010, 0x00000020, 0x00000010, 0x0000000A

	.global ov05_021F67E8
ov05_021F67E8: ; 0x021F67E8
	.word 0x00000002, 0x00000004, 0x00000002, 0x00000004

	.global ov05_021F67F8
ov05_021F67F8: ; 0x021F67F8
	.word -4, -6, -8, -10

	.global ov05_021F6808
ov05_021F6808: ; 0x021F6808
	.word 0x00000064, 0x00000064, 0x000000C8, 0x00000064
	.word 0x0000012C

	.global ov05_021F681C
ov05_021F681C: ; 0x021F681C
	.word -3, -5, -5, -3
	.word -5, -6, -10, -6

	.global ov05_021F683C
ov05_021F683C: ; 0x021F683C
	.word -3, -5, -5, -4
	.word -5, -6, -10, -6
	.word 0x00000002, 0x00000002, 0x00000002, 0x00000004
	.word 0x00000004, 0x00000002, 0x00000002, 0x00000002

	.global ov05_021F687C
ov05_021F687C: ; 0x021F687C
	.word 0x00000002, 0x00000002, 0x00000002, 0x000000004
	.word 0x00000004, 0x00000002, 0x00000002, 0x000000002

	.global ov05_021F689C
ov05_021F689C: ; 0x021F689C
	.word 0x00000015, 0x00000024, 0x00000026, 0x00000025
	.word 0x00000024, 0x00000026, 0x00000009, 0x00000008
	.word 0x0000000A, 0x0000002A, 0x0000002C, 0x0000002B
	.word 0x0000001E, 0x0000001D, 0x0000001F, 0x0000002E
	.word 0x0000002D, 0x0000002F, 0x00000033, 0x0000002D
	.word 0x0000002F, 0x00000034, 0x00000035, 0x00000036
	.word 0x00000031, 0x00000030, 0x00000032

	.section .data

	.global ov05_021FD2D4
ov05_021FD2D4: ; 0x021FD2D4
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x04, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00
	.word ov05_021DD71C
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x05, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021E0AC8
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021DD770
	.byte 0x05, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021DFE30
	.byte 0x05, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xDC, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00
	.word ov05_021DFD44
	.byte 0x03, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021DDB14
	.byte 0x01, 0x00, 0x00, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021DDF78
	.byte 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021DF11C
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x06, 0x00, 0x00, 0x00, 0xAC, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00
	.word ov05_021DE8C0
	.byte 0x06, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021E00A4
	.byte 0x02, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021DEE2C
	.byte 0x04, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021DF588
	.byte 0x07, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x44, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00
	.word ov05_021E0700
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x00, 0x00, 0x00
	.byte 0xAC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021E09D8
	.byte 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x06, 0x00, 0x00, 0x00, 0xAC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021E0D20
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x06, 0x00, 0x00, 0x00, 0xAC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021E0B98
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x2C, 0x06, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00
	.word ov05_021E0EAC
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x04, 0x00, 0x00, 0x00
	.byte 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021E05A8
	.byte 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021DE5F8
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021DE75C
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x02, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00
	.word ov05_021DF90C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021DE360
	.byte 0x02, 0x00, 0x00, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word ov05_021DEA6C
