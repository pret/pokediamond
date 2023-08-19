	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov11_0223D1DC
ov11_0223D1DC: ; 0x0223D1DC
	push {r3, r4, r5, lr}
	ldr r1, _0223D22C ; =0x0000314C
	add r5, r0, #0
	mov r0, #5
	bl AllocFromHeap
	add r4, r0, #0
	ldr r2, _0223D22C ; =0x0000314C
	mov r0, #0
	add r1, r4, #0
	bl MIi_CpuClearFast
	add r0, r4, #0
	bl ov11_02245494
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02245588
	bl sub_02033590
	cmp r0, #0
	bne _0223D216
	mov r2, #0
	add r0, r5, #0
	add r1, r4, #0
	add r3, r2, #0
	bl ov16_021EFBF4
_0223D216:
	ldr r0, _0223D230 ; =0x000003DE
	add r0, r4, r0
	bl LoadAllWazaTbl
	mov r0, #5
	bl LoadAllItemData
	ldr r1, _0223D234 ; =0x00002120
	str r0, [r4, r1]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223D22C: .word 0x0000314C
_0223D230: .word 0x000003DE
_0223D234: .word 0x00002120

	thumb_func_start ov11_0223D238
ov11_0223D238: ; 0x0223D238
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, _0223D27C ; =0x0000311F
	add r5, r0, #0
	ldrb r1, [r4, r1]
	cmp r1, #0
	bne _0223D25E
	bl ov11_0223145C
	cmp r0, #0
	beq _0223D25E
	add r0, r5, #0
	bl ov11_0223145C
	mov r1, #0x40
	tst r0, r1
	bne _0223D25E
	mov r0, #0x29
	str r0, [r4, #8]
_0223D25E:
	ldr r2, [r4, #8]
	add r0, r5, #0
	lsl r3, r2, #2
	ldr r2, _0223D280 ; =ov11_0225E194
	add r1, r4, #0
	ldr r2, [r2, r3]
	blx r2
	ldr r0, [r4, #8]
	cmp r0, #0x2b
	bne _0223D276
	mov r0, #1
	pop {r3, r4, r5, pc}
_0223D276:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_0223D27C: .word 0x0000311F
_0223D280: .word ov11_0225E194

	thumb_func_start ov11_0223D284
ov11_0223D284: ; 0x0223D284
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0223D298 ; =0x00002120
	ldr r0, [r4, r0]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
_0223D298: .word 0x00002120

	thumb_func_start ov11_0223D29C
ov11_0223D29C: ; 0x0223D29C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	ldr r6, [sp, #0x20]
	add r5, r0, #0
	add r4, r1, #0
	add r7, r2, #0
	str r3, [sp, #4]
	str r6, [sp]
	bl ov11_0224053C
	ldr r0, [sp, #0x20]
	ldr r3, [sp, #4]
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	add r2, r7, #0
	bl ov11_02240890
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_0223D2C4
ov11_0223D2C4: ; 0x0223D2C4
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	add r5, r1, #0
	bl ov11_0222FF84
	add r7, r0, #0
	mov r4, #0
	cmp r7, #0
	ble _0223D2EC
_0223D2D6:
	ldr r3, _0223D2FC ; =0x0000219C
	add r6, r5, r4
	ldrb r3, [r6, r3]
	ldr r0, [sp]
	add r1, r5, #0
	add r2, r4, #0
	bl ov11_02242B78
	add r4, r4, #1
	cmp r4, r7
	blt _0223D2D6
_0223D2EC:
	ldr r0, _0223D300 ; =0x00002E4C
	ldr r1, [r5, r0]
	ldr r0, _0223D304 ; =0x00003122
	strh r1, [r5, r0]
	mov r0, #1
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223D2FC: .word 0x0000219C
_0223D300: .word 0x00002E4C
_0223D304: .word 0x00003122

	thumb_func_start ov11_0223D308
ov11_0223D308: ; 0x0223D308
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #2
	str r0, [r4, #0xc]
	pop {r4, pc}

	thumb_func_start ov11_0223D320
ov11_0223D320: ; 0x0223D320
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov11_0224529C
	cmp r0, #0
	beq _0223D342
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x29
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #3
	str r0, [r4, #0xc]
	b _0223D346
_0223D342:
	mov r0, #3
	str r0, [r4, #8]
_0223D346:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0224728C
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_0223D350
ov11_0223D350: ; 0x0223D350
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov11_022476DC
	add r2, r0, #0
	beq _0223D370
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
_0223D370:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0224728C
	mov r0, #4
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_0223D380
ov11_0223D380: ; 0x0223D380
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	add r4, r1, #0
	bl ov11_0222FF84
	add r5, r0, #0
	mov r3, #0
	cmp r5, #0
	ble _0223D3AA
	mov r7, #0xb7
	lsl r7, r7, #6
	add r6, r4, #0
	add r2, r3, #0
	add r0, r7, #4
_0223D39C:
	strb r2, [r4, r3]
	ldr r1, [r6, r7]
	add r3, r3, #1
	str r1, [r6, r0]
	add r6, #0xc0
	cmp r3, r5
	blt _0223D39C
_0223D3AA:
	ldr r0, [sp]
	mov r1, #0
	bl ov11_022312AC
	mov r0, #5
	str r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_0223D3B8
ov11_0223D3B8: ; 0x0223D3B8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0xb8
	add r7, r0, #0
	add r6, r1, #0
	bl ov11_0222FF84
	str r0, [sp, #0x64]
	add r0, r7, #0
	bl ov11_0222FF74
	str r0, [sp, #0x24]
	mov r4, #0
	ldr r0, [sp, #0x64]
	str r4, [sp, #0x60]
	cmp r0, #0
	bgt _0223D3DA
	b _0223DB58
_0223D3DA:
	mov r0, #0x75
	lsl r0, r0, #2
	add r0, r6, r0
	str r0, [sp, #0x50]
	ldr r0, _0223D710 ; =0x000021AC
	mov r1, #2
	add r0, r6, r0
	str r0, [sp, #0x40]
	mov r0, #0x23
	lsl r0, r0, #8
	add r0, r6, r0
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x24]
	str r6, [sp, #0x54]
	and r0, r1
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x24]
	mov r1, #8
	and r0, r1
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x24]
	lsl r1, r1, #6
	and r0, r1
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x24]
	mov r1, #0x20
	and r0, r1
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x24]
	mov r1, #4
	and r0, r1
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x24]
	mov r1, #0x80
	and r0, r1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x24]
	mov r1, #1
	and r0, r1
	str r6, [sp, #0x4c]
	str r6, [sp, #0x48]
	str r6, [sp, #0x44]
	str r0, [sp, #0x1c]
_0223D430:
	ldrb r0, [r6, r4]
	add r5, r6, r4
	cmp r0, #0x10
	bhi _0223D50A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223D444: ; jump table
	.short _0223D466 - _0223D444 - 2 ; case 0
	.short _0223D4DA - _0223D444 - 2 ; case 1
	.short _0223D6EE - _0223D444 - 2 ; case 2
	.short _0223D6FC - _0223D444 - 2 ; case 3
	.short _0223D7DA - _0223D444 - 2 ; case 4
	.short _0223D814 - _0223D444 - 2 ; case 5
	.short _0223D848 - _0223D444 - 2 ; case 6
	.short _0223D856 - _0223D444 - 2 ; case 7
	.short _0223D884 - _0223D444 - 2 ; case 8
	.short _0223D8FC - _0223D444 - 2 ; case 9
	.short _0223D93C - _0223D444 - 2 ; case 10
	.short _0223D9F8 - _0223D444 - 2 ; case 11
	.short _0223DA46 - _0223D444 - 2 ; case 12
	.short _0223DA94 - _0223D444 - 2 ; case 13
	.short _0223DA9C - _0223D444 - 2 ; case 14
	.short _0223DAB6 - _0223D444 - 2 ; case 15
	.short _0223DB14 - _0223D444 - 2 ; case 16
_0223D466:
	ldr r0, [sp, #0x38]
	cmp r0, #0
	beq _0223D486
	ldr r0, [sp, #0x34]
	cmp r0, #0
	bne _0223D486
	cmp r4, #2
	bne _0223D47C
	ldrb r0, [r6]
	cmp r0, #0xd
	bne _0223D50A
_0223D47C:
	cmp r4, #3
	bne _0223D486
	ldrb r0, [r6, #1]
	cmp r0, #0xd
	bne _0223D50A
_0223D486:
	add r0, r4, #0
	bl MaskOfFlagNo
	ldr r1, _0223D714 ; =0x00003108
	ldrb r1, [r6, r1]
	tst r0, r1
	beq _0223D4A2
	mov r0, #0xc
	strb r0, [r5]
	ldr r1, _0223D718 ; =0x000021A8
	ldr r0, [sp, #0x54]
	mov r2, #0x27
	str r2, [r0, r1]
	b _0223DB20
_0223D4A2:
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224AD04
	cmp r0, #0
	bne _0223D4C8
	ldr r0, [sp, #0x50]
	mov r2, #0xd
	ldr r1, [r0]
	mov r0, #2
	orr r1, r0
	ldr r0, [sp, #0x50]
	str r1, [r0]
	mov r0, #0xc
	strb r0, [r5]
	ldr r1, _0223D718 ; =0x000021A8
	ldr r0, [sp, #0x54]
	str r2, [r0, r1]
	b _0223DB20
_0223D4C8:
	ldr r3, _0223D71C ; =0x0000219C
	add r0, r7, #0
	ldrb r3, [r5, r3]
	add r1, r6, #0
	add r2, r4, #0
	bl ov11_02255188
	mov r0, #1
	strb r0, [r5]
_0223D4DA:
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224AD90
	cmp r0, #0
	beq _0223D50A
	mov r1, #0x23
	ldr r0, [sp, #0x4c]
	lsl r1, r1, #8
	ldrb r2, [r0, r1]
	ldr r1, _0223D720 ; =0x000021B4
	ldr r0, [sp, #0x54]
	str r2, [r0, r1]
	ldr r0, [sp, #0x30]
	cmp r0, #0
	beq _0223D52E
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224AD90
	cmp r0, #1
	beq _0223D50C
	cmp r0, #4
	beq _0223D51E
_0223D50A:
	b _0223DB20
_0223D50C:
	mov r0, #0x10
	strb r0, [r5]
	mov r0, #0xc
	strb r0, [r5, #4]
	ldr r1, _0223D718 ; =0x000021A8
	ldr r0, [sp, #0x54]
	mov r2, #0x11
	str r2, [r0, r1]
	b _0223DB20
_0223D51E:
	mov r0, #0x10
	strb r0, [r5]
	mov r1, #0xc
	strb r1, [r5, #4]
	ldr r2, _0223D718 ; =0x000021A8
	ldr r1, [sp, #0x54]
	str r0, [r1, r2]
	b _0223DB20
_0223D52E:
	ldr r0, [sp, #0x2c]
	cmp r0, #0
	beq _0223D5B0
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224AD90
	cmp r0, #5
	bhi _0223D5DA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223D54C: ; jump table
	.short _0223DB20 - _0223D54C - 2 ; case 0
	.short _0223D558 - _0223D54C - 2 ; case 1
	.short _0223D56A - _0223D54C - 2 ; case 2
	.short _0223D57C - _0223D54C - 2 ; case 3
	.short _0223D58E - _0223D54C - 2 ; case 4
	.short _0223D59E - _0223D54C - 2 ; case 5
_0223D558:
	mov r0, #0x10
	strb r0, [r5]
	mov r0, #0xc
	strb r0, [r5, #4]
	ldr r1, _0223D718 ; =0x000021A8
	ldr r0, [sp, #0x54]
	mov r2, #0x11
	str r2, [r0, r1]
	b _0223DB20
_0223D56A:
	mov r0, #0x10
	strb r0, [r5]
	mov r0, #0xc
	strb r0, [r5, #4]
	ldr r1, _0223D718 ; =0x000021A8
	ldr r0, [sp, #0x54]
	mov r2, #0x12
	str r2, [r0, r1]
	b _0223DB20
_0223D57C:
	mov r0, #0x10
	strb r0, [r5]
	mov r0, #0xc
	strb r0, [r5, #4]
	ldr r1, _0223D718 ; =0x000021A8
	ldr r0, [sp, #0x54]
	mov r2, #0x13
	str r2, [r0, r1]
	b _0223DB20
_0223D58E:
	mov r0, #0x10
	strb r0, [r5]
	mov r1, #0xc
	strb r1, [r5, #4]
	ldr r2, _0223D718 ; =0x000021A8
	ldr r1, [sp, #0x54]
	str r0, [r1, r2]
	b _0223DB20
_0223D59E:
	mov r0, #0x10
	strb r0, [r5]
	mov r0, #0xc
	strb r0, [r5]
	ldr r1, _0223D718 ; =0x000021A8
	ldr r0, [sp, #0x54]
	mov r2, #0x14
	str r2, [r0, r1]
	b _0223DB20
_0223D5B0:
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224AD90
	cmp r0, #4
	bgt _0223D5D6
	cmp r0, #0
	blt _0223D5DA
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223D5CC: ; jump table
	.short _0223DB20 - _0223D5CC - 2 ; case 0
	.short _0223D5DC - _0223D5CC - 2 ; case 1
	.short _0223D63C - _0223D5CC - 2 ; case 2
	.short _0223D698 - _0223D5CC - 2 ; case 3
	.short _0223D6A6 - _0223D5CC - 2 ; case 4
_0223D5D6:
	cmp r0, #0xff
	beq _0223D6B4
_0223D5DA:
	b _0223DB20
_0223D5DC:
	mov r0, #0
	mvn r0, r0
	str r0, [sp]
	add r0, r7, #0
	add r1, r6, #0
	add r2, r4, #0
	mov r3, #0
	bl ov11_02245D38
	cmp r0, #0xf
	bne _0223D5FC
	mov r0, #0x10
	strb r0, [r5]
	mov r0, #0xf
	strb r0, [r5, #4]
	b _0223D632
_0223D5FC:
	ldr r3, _0223D724 ; =0x00002DEC
	ldr r0, [sp, #0x48]
	ldrh r0, [r0, r3]
	cmp r0, #0
	beq _0223D62E
	ldr r0, [sp, #0x48]
	add r1, r3, #2
	ldrh r1, [r0, r1]
	ldr r2, _0223D728 ; =0x000030BC
	ldr r0, [sp, #0x44]
	strh r1, [r0, r2]
	ldr r0, [sp, #0x48]
	sub r2, #8
	ldrh r1, [r0, r3]
	ldr r0, [sp, #0x44]
	strh r1, [r0, r2]
	ldr r1, _0223D72C ; =0x000021B0
	ldr r0, [sp, #0x54]
	mov r2, #0
	str r2, [r0, r1]
	mov r0, #0x10
	strb r0, [r5]
	mov r0, #0xc
	strb r0, [r5, #4]
	b _0223D632
_0223D62E:
	mov r0, #2
	strb r0, [r5]
_0223D632:
	ldr r1, _0223D718 ; =0x000021A8
	ldr r0, [sp, #0x54]
	mov r2, #0xd
	str r2, [r0, r1]
	b _0223DB20
_0223D63C:
	add r0, r7, #0
	bl ov11_0222FF74
	mov r1, #0x84
	tst r0, r1
	beq _0223D68A
	ldr r1, _0223D730 ; =0x00000251
	add r0, sp, #0x90
	strh r1, [r0, #6]
	mov r1, #0
	strb r1, [r0, #5]
	mov r0, sp
	str r0, [sp, #0x68]
	sub r0, #8
	str r0, [sp, #0x68]
	add r3, r0, #0
	mov r0, #4
	add r2, sp, #0x94
	str r0, [sp, #0x6c]
_0223D662:
	ldmia r2!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [sp, #0x6c]
	sub r0, r0, #1
	str r0, [sp, #0x6c]
	bne _0223D662
	ldr r0, [r2]
	add r1, r4, #0
	str r0, [r3]
	ldr r0, [sp, #0x68]
	ldmia r0!, {r2, r3}
	str r0, [sp, #0x68]
	add r0, r7, #0
	bl ov11_02255FBC
	mov r0, #0xe
	strb r0, [r5]
	mov r0, #0
	strb r0, [r5, #4]
	b _0223DB20
_0223D68A:
	ldr r1, _0223D718 ; =0x000021A8
	ldr r0, [sp, #0x54]
	mov r2, #0xe
	str r2, [r0, r1]
	mov r0, #6
	strb r0, [r5]
	b _0223DB20
_0223D698:
	ldr r1, _0223D718 ; =0x000021A8
	ldr r0, [sp, #0x54]
	mov r2, #0xf
	str r2, [r0, r1]
	mov r0, #8
	strb r0, [r5]
	b _0223DB20
_0223D6A6:
	ldr r1, _0223D718 ; =0x000021A8
	ldr r0, [sp, #0x54]
	mov r2, #0x10
	str r2, [r0, r1]
	mov r0, #0xa
	strb r0, [r5]
	b _0223DB20
_0223D6B4:
	ldr r0, [sp, #0x28]
	cmp r0, #0
	beq _0223D6D4
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_02256268
	mov r0, #0
	strb r0, [r5]
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_022302BC
	mov r1, #0
	strb r1, [r6, r0]
	b _0223DB20
_0223D6D4:
	ldr r0, [sp, #0x38]
	cmp r0, #0
	beq _0223D740
	cmp r4, #2
	bne _0223D740
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_02256268
	mov r0, #0
	strb r0, [r6]
	strb r0, [r6, #2]
	b _0223DB20
_0223D6EE:
	add r0, r7, #0
	add r1, r6, #0
	add r2, r4, #0
	bl ov11_02255544
	mov r0, #3
	strb r0, [r5]
_0223D6FC:
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224AD90
	cmp r0, #0xff
	bne _0223D734
	mov r0, #0
	strb r0, [r5]
	b _0223DB20
	nop
_0223D710: .word 0x000021AC
_0223D714: .word 0x00003108
_0223D718: .word 0x000021A8
_0223D71C: .word 0x0000219C
_0223D720: .word 0x000021B4
_0223D724: .word 0x00002DEC
_0223D728: .word 0x000030BC
_0223D72C: .word 0x000021B0
_0223D730: .word 0x00000251
_0223D734:
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224AD90
	cmp r0, #0
	bne _0223D742
_0223D740:
	b _0223DB20
_0223D742:
	mov r1, #0x23
	ldr r0, [sp, #0x4c]
	lsl r1, r1, #8
	ldrb r0, [r0, r1]
	sub r3, r0, #1
	cmp r3, #4
	bne _0223D75E
	ldr r1, _0223DA6C ; =0x000021A8
	ldr r0, [sp, #0x54]
	mov r2, #0x10
	str r2, [r0, r1]
	mov r0, #0xa
	strb r0, [r5]
	b _0223DB20
_0223D75E:
	add r0, sp, #0x94
	str r0, [sp]
	add r0, r7, #0
	add r1, r6, #0
	add r2, r4, #0
	bl ov11_02245F74
	cmp r0, #0
	bne _0223D7A8
	mov r0, sp
	str r0, [sp, #0x70]
	sub r0, #8
	str r0, [sp, #0x70]
	add r3, r0, #0
	mov r0, #4
	add r2, sp, #0x94
	str r0, [sp, #0x74]
_0223D780:
	ldmia r2!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [sp, #0x74]
	sub r0, r0, #1
	str r0, [sp, #0x74]
	bne _0223D780
	ldr r0, [r2]
	add r1, r4, #0
	str r0, [r3]
	ldr r0, [sp, #0x70]
	ldmia r0!, {r2, r3}
	str r0, [sp, #0x70]
	add r0, r7, #0
	bl ov11_02255FBC
	mov r0, #0xe
	strb r0, [r5]
	mov r0, #2
	strb r0, [r5, #4]
	b _0223DB20
_0223D7A8:
	mov r3, #0x23
	ldr r0, [sp, #0x4c]
	lsl r3, r3, #8
	ldrb r2, [r0, r3]
	ldr r1, _0223DA70 ; =0x000021B0
	ldr r0, [sp, #0x54]
	str r2, [r0, r1]
	ldr r0, [sp, #0x4c]
	ldr r2, _0223DA74 ; =0x000030BC
	ldrb r0, [r0, r3]
	sub r1, r0, #1
	ldr r0, [sp, #0x44]
	strh r1, [r0, r2]
	ldrh r0, [r0, r2]
	sub r2, #8
	lsl r1, r0, #1
	ldr r0, [sp, #0x48]
	add r1, r0, r1
	ldr r0, _0223DA78 ; =0x00002D4C
	ldrh r1, [r1, r0]
	ldr r0, [sp, #0x44]
	strh r1, [r0, r2]
	mov r0, #4
	strb r0, [r5]
	b _0223DB20
_0223D7DA:
	add r0, sp, #0x90
	str r0, [sp]
	ldr r1, _0223DA74 ; =0x000030BC
	ldr r0, [sp, #0x44]
	lsl r2, r4, #0x18
	ldrh r0, [r0, r1]
	ldr r3, [sp, #0x24]
	add r1, r6, #0
	str r0, [sp, #4]
	ldr r0, [sp, #0x40]
	lsr r2, r2, #0x18
	str r0, [sp, #8]
	add r0, r7, #0
	bl ov11_0224235C
	cmp r0, #0
	beq _0223D80E
	ldr r2, [sp, #0x90]
	add r0, r7, #0
	add r1, r6, #0
	add r3, r4, #0
	bl ov11_02255600
	mov r0, #5
	strb r0, [r5]
	b _0223DB20
_0223D80E:
	mov r0, #0xc
	strb r0, [r5]
	b _0223DB20
_0223D814:
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224AD90
	cmp r0, #0xff
	bne _0223D826
	mov r0, #2
	strb r0, [r5]
	b _0223DB20
_0223D826:
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224AD90
	cmp r0, #0
	beq _0223D91A
	mov r1, #0x23
	ldr r0, [sp, #0x4c]
	lsl r1, r1, #8
	ldrb r0, [r0, r1]
	ldr r1, _0223DA7C ; =0x000021AC
	sub r2, r0, #1
	ldr r0, [sp, #0x54]
	str r2, [r0, r1]
	mov r0, #0xc
	strb r0, [r5]
	b _0223DB20
_0223D848:
	add r0, r7, #0
	add r1, r6, #0
	add r2, r4, #0
	bl ov11_0225573C
	mov r0, #7
	strb r0, [r5]
_0223D856:
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224AD90
	cmp r0, #0xff
	bne _0223D868
	mov r0, #0
	strb r0, [r5]
	b _0223DB20
_0223D868:
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224AD90
	cmp r0, #0
	beq _0223D91A
	ldr r0, [sp, #0x3c]
	ldr r1, _0223DA70 ; =0x000021B0
	ldr r2, [r0]
	ldr r0, [sp, #0x54]
	str r2, [r0, r1]
	mov r0, #0xc
	strb r0, [r5]
	b _0223DB20
_0223D884:
	mov r0, #6
	str r0, [sp, #0x58]
	add r0, r7, #0
	add r1, r6, #0
	add r2, r4, #0
	bl ov11_02249E80
	str r0, [sp, #0x5c]
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_02230260
	cmp r0, #4
	beq _0223D8AC
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_02230260
	cmp r0, #5
	bne _0223D8E4
_0223D8AC:
	ldr r0, [sp, #0x24]
	cmp r0, #3
	beq _0223D8CA
	cmp r0, #7
	beq _0223D8CA
	cmp r0, #0x83
	beq _0223D8CA
	cmp r0, #0x13
	bne _0223D8E4
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_02230260
	cmp r0, #4
	bne _0223D8E4
_0223D8CA:
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_022302BC
	lsl r0, r0, #4
	add r2, r6, r0
	ldr r0, _0223DA6C ; =0x000021A8
	ldr r1, [r2, r0]
	cmp r1, #0xf
	bne _0223D8E4
	add r0, #8
	ldr r0, [r2, r0]
	str r0, [sp, #0x58]
_0223D8E4:
	ldr r0, [sp, #0x5c]
	add r1, r6, #0
	str r0, [sp]
	ldr r0, [sp, #0x58]
	add r2, r4, #0
	str r0, [sp, #4]
	add r0, r7, #0
	mov r3, #0
	bl ov11_022558E0
	mov r0, #9
	strb r0, [r5]
_0223D8FC:
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224AD90
	cmp r0, #0xff
	bne _0223D90E
	mov r0, #0
	strb r0, [r5]
	b _0223DB20
_0223D90E:
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224AD90
	cmp r0, #0
	bne _0223D91C
_0223D91A:
	b _0223DB20
_0223D91C:
	mov r3, #0x23
	ldr r0, [sp, #0x4c]
	lsl r3, r3, #8
	ldrb r0, [r0, r3]
	ldr r2, _0223DA70 ; =0x000021B0
	sub r1, r0, #1
	ldr r0, [sp, #0x54]
	str r1, [r0, r2]
	ldr r0, [sp, #0x4c]
	sub r2, #0x10
	ldrb r0, [r0, r3]
	sub r0, r0, #1
	strb r0, [r5, r2]
	mov r0, #0xc
	strb r0, [r5]
	b _0223DB20
_0223D93C:
	ldr r0, [sp, #0x20]
	cmp r0, #0
	beq _0223D95C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r3, _0223DA80 ; =0x000003BB
	add r0, r7, #0
	add r1, r6, #0
	add r2, r4, #0
	bl ov11_02255980
	mov r0, #0xb
	strb r0, [r5]
	b _0223DB20
_0223D95C:
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	beq _0223D9AA
	ldr r0, [sp, #0x28]
	cmp r0, #0
	bne _0223D9AA
	mov r1, #0
	add r0, sp, #0x90
	strb r1, [r0, #5]
	ldr r1, _0223DA84 ; =0x00000319
	add r2, sp, #0x94
	strh r1, [r0, #6]
	mov r0, sp
	str r0, [sp, #0x78]
	sub r0, #8
	str r0, [sp, #0x78]
	add r3, r0, #0
	mov r0, #4
	str r0, [sp, #0x7c]
_0223D982:
	ldmia r2!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [sp, #0x7c]
	sub r0, r0, #1
	str r0, [sp, #0x7c]
	bne _0223D982
	ldr r0, [r2]
	add r1, r4, #0
	str r0, [r3]
	ldr r0, [sp, #0x78]
	ldmia r0!, {r2, r3}
	str r0, [sp, #0x78]
	add r0, r7, #0
	bl ov11_02255FBC
	mov r0, #0xe
	strb r0, [r5]
	mov r0, #0
	strb r0, [r5, #4]
	b _0223DB20
_0223D9AA:
	add r0, r7, #0
	add r1, r6, #0
	add r2, r4, #0
	add r3, sp, #0x94
	bl ov11_02246ED0
	cmp r0, #0
	beq _0223D9F2
	mov r0, sp
	str r0, [sp, #0x80]
	sub r0, #8
	str r0, [sp, #0x80]
	add r3, r0, #0
	mov r0, #4
	add r2, sp, #0x94
	str r0, [sp, #0x84]
_0223D9CA:
	ldmia r2!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [sp, #0x84]
	sub r0, r0, #1
	str r0, [sp, #0x84]
	bne _0223D9CA
	ldr r0, [r2]
	add r1, r4, #0
	str r0, [r3]
	ldr r0, [sp, #0x80]
	ldmia r0!, {r2, r3}
	str r0, [sp, #0x80]
	add r0, r7, #0
	bl ov11_02255FBC
	mov r0, #0xe
	strb r0, [r5]
	mov r0, #0
	strb r0, [r5, #4]
	b _0223DB20
_0223D9F2:
	mov r0, #0xb
	strb r0, [r5]
	b _0223DB20
_0223D9F8:
	ldr r0, [sp, #0x20]
	cmp r0, #0
	beq _0223DA22
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224AD90
	cmp r0, #0
	beq _0223DA26
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224AD90
	cmp r0, #0xff
	bne _0223DA1C
	mov r0, #0
	strb r0, [r5]
	b _0223DA26
_0223DA1C:
	mov r0, #0xc
	strb r0, [r5]
	b _0223DA26
_0223DA22:
	mov r0, #0xc
	strb r0, [r5]
_0223DA26:
	ldr r0, [sp, #0x38]
	cmp r0, #0
	beq _0223DB20
	ldr r0, [sp, #0x34]
	cmp r0, #0
	bne _0223DB20
	ldrb r0, [r5]
	cmp r0, #0xc
	bne _0223DB20
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_022302BC
	mov r1, #0xc
	strb r1, [r6, r0]
	b _0223DB20
_0223DA46:
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_02256268
	ldr r0, [sp, #0x24]
	cmp r0, #7
	bne _0223DA88
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_022302BC
	ldrb r0, [r6, r0]
	cmp r0, #0xd
	bne _0223DA90
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_022564CC
	b _0223DA90
	.align 2, 0
_0223DA6C: .word 0x000021A8
_0223DA70: .word 0x000021B0
_0223DA74: .word 0x000030BC
_0223DA78: .word 0x00002D4C
_0223DA7C: .word 0x000021AC
_0223DA80: .word 0x000003BB
_0223DA84: .word 0x00000319
_0223DA88:
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_022564CC
_0223DA90:
	mov r0, #0xd
	strb r0, [r5]
_0223DA94:
	ldr r0, [sp, #0x60]
	add r0, r0, #1
	str r0, [sp, #0x60]
	b _0223DB20
_0223DA9C:
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224AD90
	cmp r0, #0
	beq _0223DB20
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_02243400
	ldrb r0, [r5, #4]
	strb r0, [r5]
	b _0223DB20
_0223DAB6:
	mov r1, #2
	add r0, sp, #0x90
	strb r1, [r0, #5]
	mov r1, #0x26
	lsl r1, r1, #4
	strh r1, [r0, #6]
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0224682C
	str r0, [sp, #0x98]
	mov r0, sp
	str r0, [sp, #0x88]
	sub r0, #8
	str r0, [sp, #0x88]
	add r3, r0, #0
	mov r0, #4
	add r2, sp, #0x94
	mov ip, r0
_0223DADC:
	ldmia r2!, {r0, r1}
	stmia r3!, {r0, r1}
	mov r0, ip
	sub r0, r0, #1
	mov ip, r0
	bne _0223DADC
	ldr r0, [r2]
	add r1, r4, #0
	str r0, [r3]
	ldr r0, [sp, #0x88]
	ldmia r0!, {r2, r3}
	str r0, [sp, #0x88]
	add r0, r7, #0
	bl ov11_02255FBC
	ldr r0, [sp, #0x50]
	mov r1, #1
	ldr r0, [r0]
	bic r0, r1
	mov r1, #1
	orr r1, r0
	ldr r0, [sp, #0x50]
	str r1, [r0]
	mov r0, #0xe
	strb r0, [r5]
	mov r0, #0xc
	strb r0, [r5, #4]
	b _0223DB20
_0223DB14:
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_022563B4
	ldrb r0, [r5, #4]
	strb r0, [r5]
_0223DB20:
	ldr r0, [sp, #0x54]
	ldr r1, [sp, #0x4c]
	add r0, #0x10
	str r0, [sp, #0x54]
	ldr r0, [sp, #0x50]
	add r4, r4, #1
	add r0, #0x40
	str r0, [sp, #0x50]
	mov r0, #1
	lsl r0, r0, #8
	add r1, r1, r0
	str r1, [sp, #0x4c]
	ldr r1, [sp, #0x48]
	add r1, #0xc0
	str r1, [sp, #0x48]
	ldr r1, [sp, #0x44]
	add r1, r1, #2
	str r1, [sp, #0x44]
	ldr r1, [sp, #0x40]
	add r1, #0x10
	str r1, [sp, #0x40]
	ldr r1, [sp, #0x3c]
	add r0, r1, r0
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x64]
	cmp r4, r0
	bge _0223DB58
	b _0223D430
_0223DB58:
	ldr r1, [sp, #0x60]
	ldr r0, [sp, #0x64]
	cmp r1, r0
	bne _0223DB96
	mov r0, #6
	str r0, [r6, #8]
	ldr r0, [sp, #0x64]
	mov r5, #0
	cmp r0, #0
	ble _0223DB96
	str r6, [sp, #0x8c]
_0223DB6E:
	ldr r1, _0223DB9C ; =0x000021A8
	ldr r0, [sp, #0x8c]
	ldr r0, [r0, r1]
	cmp r0, #0xf
	bne _0223DB88
	ldr r3, _0223DBA0 ; =0x000021A0
	add r4, r6, r5
	ldrb r3, [r4, r3]
	add r0, r7, #0
	add r1, r6, #0
	add r2, r5, #0
	bl ov11_0224B290
_0223DB88:
	ldr r0, [sp, #0x8c]
	add r5, r5, #1
	add r0, #0x10
	str r0, [sp, #0x8c]
	ldr r0, [sp, #0x64]
	cmp r5, r0
	blt _0223DB6E
_0223DB96:
	add sp, #0xb8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223DB9C: .word 0x000021A8
_0223DBA0: .word 0x000021A0

	thumb_func_start ov11_0223DBA4
ov11_0223DBA4: ; 0x0223DBA4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	str r0, [sp, #4]
	add r5, r1, #0
	bl ov11_0222FF84
	str r0, [sp, #0x14]
	ldr r0, [sp, #4]
	bl ov11_0222FF74
	mov r2, #0x22
	lsl r2, r2, #4
	mov r1, #0
	tst r2, r0
	beq _0223DBDA
	ldr r0, [sp, #0x14]
	add r4, r1, #0
	cmp r0, #0
	ble _0223DBD8
	ldr r1, _0223DD14 ; =0x000021E8
_0223DBCC:
	add r0, r5, r4
	strb r4, [r0, r1]
	ldr r0, [sp, #0x14]
	add r4, r4, #1
	cmp r4, r0
	blt _0223DBCC
_0223DBD8:
	b _0223DD0C
_0223DBDA:
	mov r2, #4
	tst r0, r2
	beq _0223DC02
	ldr r0, [sp, #0x14]
	add r4, r1, #0
	cmp r0, #0
	ble _0223DC1A
	ldr r2, _0223DD18 ; =0x000021B4
	add r3, r5, #0
_0223DBEC:
	ldr r0, [r3, r2]
	cmp r0, #4
	bne _0223DBF6
	mov r1, #5
	b _0223DC1A
_0223DBF6:
	ldr r0, [sp, #0x14]
	add r4, r4, #1
	add r3, #0x10
	cmp r4, r0
	blt _0223DBEC
	b _0223DC1A
_0223DC02:
	ldr r0, _0223DD18 ; =0x000021B4
	ldr r0, [r5, r0]
	cmp r0, #4
	bne _0223DC0E
	add r4, r1, #0
	mov r1, #5
_0223DC0E:
	ldr r0, _0223DD1C ; =0x000021D4
	ldr r0, [r5, r0]
	cmp r0, #4
	bne _0223DC1A
	mov r4, #2
	mov r1, #5
_0223DC1A:
	cmp r1, #5
	bne _0223DC42
	ldr r0, _0223DD14 ; =0x000021E8
	ldr r2, [sp, #0x14]
	strb r4, [r5, r0]
	mov r1, #1
	mov r0, #0
	cmp r2, #0
	ble _0223DD0C
	ldr r3, _0223DD14 ; =0x000021E8
_0223DC2E:
	cmp r0, r4
	beq _0223DC38
	add r2, r5, r1
	strb r0, [r2, r3]
	add r1, r1, #1
_0223DC38:
	ldr r2, [sp, #0x14]
	add r0, r0, #1
	cmp r0, r2
	blt _0223DC2E
	b _0223DD0C
_0223DC42:
	ldr r0, [sp, #0x14]
	mov r2, #0
	cmp r0, #0
	ble _0223DC6A
	ldr r4, _0223DD14 ; =0x000021E8
	add r0, r5, #0
	add r6, r4, #0
	sub r6, #0x34
_0223DC52:
	ldr r3, [r0, r6]
	sub r3, r3, #2
	cmp r3, #1
	bhi _0223DC60
	add r3, r5, r1
	strb r2, [r3, r4]
	add r1, r1, #1
_0223DC60:
	ldr r3, [sp, #0x14]
	add r2, r2, #1
	add r0, #0x10
	cmp r2, r3
	blt _0223DC52
_0223DC6A:
	ldr r0, [sp, #0x14]
	mov r2, #0
	cmp r0, #0
	ble _0223DC94
	ldr r4, _0223DD14 ; =0x000021E8
	add r0, r5, #0
	add r6, r4, #0
	sub r6, #0x34
_0223DC7A:
	ldr r3, [r0, r6]
	cmp r3, #2
	beq _0223DC8A
	cmp r3, #3
	beq _0223DC8A
	add r3, r5, r1
	strb r2, [r3, r4]
	add r1, r1, #1
_0223DC8A:
	ldr r3, [sp, #0x14]
	add r2, r2, #1
	add r0, #0x10
	cmp r2, r3
	blt _0223DC7A
_0223DC94:
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x14]
	sub r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, #0
	ble _0223DD0C
_0223DCA2:
	ldr r0, [sp, #8]
	add r7, r0, #1
	ldr r0, [sp, #0x14]
	cmp r7, r0
	bge _0223DD00
	ldr r0, [sp, #8]
	add r0, r5, r0
	str r0, [sp, #0x10]
_0223DCB2:
	ldr r1, [sp, #0x10]
	ldr r0, _0223DD14 ; =0x000021E8
	ldrb r6, [r1, r0]
	add r1, r5, r7
	ldrb r4, [r1, r0]
	lsl r0, r6, #4
	str r1, [sp, #0xc]
	add r1, r5, r0
	ldr r0, _0223DD18 ; =0x000021B4
	ldr r0, [r1, r0]
	lsl r1, r4, #4
	add r2, r5, r1
	ldr r1, _0223DD18 ; =0x000021B4
	ldr r1, [r2, r1]
	cmp r0, r1
	bne _0223DCF8
	cmp r0, #1
	beq _0223DCDA
	mov r0, #1
	b _0223DCDC
_0223DCDA:
	mov r0, #0
_0223DCDC:
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	add r2, r6, #0
	add r3, r4, #0
	bl ov11_02244248
	cmp r0, #0
	beq _0223DCF8
	ldr r1, [sp, #0x10]
	ldr r0, _0223DD14 ; =0x000021E8
	strb r4, [r1, r0]
	ldr r1, [sp, #0xc]
	strb r6, [r1, r0]
_0223DCF8:
	ldr r0, [sp, #0x14]
	add r7, r7, #1
	cmp r7, r0
	blt _0223DCB2
_0223DD00:
	ldr r0, [sp, #8]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [sp, #8]
	cmp r1, r0
	blt _0223DCA2
_0223DD0C:
	mov r0, #7
	str r0, [r5, #8]
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223DD14: .word 0x000021E8
_0223DD18: .word 0x000021B4
_0223DD1C: .word 0x000021D4

	thumb_func_start ov11_0223DD20
ov11_0223DD20: ; 0x0223DD20
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	mov r1, #0
	str r0, [sp]
	str r1, [sp, #4]
	bl ov11_0222FF84
	add r7, r0, #0
_0223DD32:
	ldr r0, [r4, #0x28]
	cmp r0, #3
	bls _0223DD3A
	b _0223DE4A
_0223DD3A:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223DD46: ; jump table
	.short _0223DD4E - _0223DD46 - 2 ; case 0
	.short _0223DDE8 - _0223DD46 - 2 ; case 1
	.short _0223DE26 - _0223DD46 - 2 ; case 2
	.short _0223DE42 - _0223DD46 - 2 ; case 3
_0223DD4E:
	ldr r0, [r4, #0x2c]
	cmp r0, r7
	bge _0223DDDC
	add r6, r4, #0
	add r6, #0x2c
_0223DD58:
	add r1, r4, r0
	ldr r0, _0223DE60 ; =0x000021E8
	ldrb r5, [r1, r0]
	add r0, r5, #0
	bl MaskOfFlagNo
	ldr r1, _0223DE64 ; =0x00003108
	ldrb r1, [r4, r1]
	tst r0, r1
	ldr r0, [r6]
	beq _0223DD74
	add r0, r0, #1
	str r0, [r6]
	b _0223DDD6
_0223DD74:
	add r0, r0, #1
	str r0, [r6]
	mov r0, #0xc0
	mul r0, r5
	add r1, r4, r0
	ldr r0, _0223DE68 ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #7
	tst r0, r1
	bne _0223DDD6
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0224683C
	mov r1, #0x42
	lsl r1, r1, #2
	cmp r0, r1
	bne _0223DDD6
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02247190
	cmp r0, #0
	bne _0223DDD6
	lsl r0, r5, #6
	add r1, r4, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bne _0223DDD6
	ldr r0, [sp]
	bl ov11_0225679C
	mov r0, #0x46
	lsl r0, r0, #2
	str r5, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xe8
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add sp, #8
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223DDD6:
	ldr r0, [r4, #0x2c]
	cmp r0, r7
	blt _0223DD58
_0223DDDC:
	mov r0, #0
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x28]
	add r0, r0, #1
	str r0, [r4, #0x28]
	b _0223DE4A
_0223DDE8:
	mov r6, #0
	cmp r7, #0
	ble _0223DE1E
	add r5, r4, #0
_0223DDF0:
	ldr r0, _0223DE6C ; =0x00002DB0
	ldr r1, [r5, r0]
	mov r0, #2
	lsl r0, r0, #0x16
	tst r0, r1
	beq _0223DE16
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0224683C
	cmp r0, #0x63
	beq _0223DE16
	ldr r0, _0223DE6C ; =0x00002DB0
	ldr r1, [r5, r0]
	mov r0, #2
	lsl r0, r0, #0x16
	and r1, r0
	ldr r0, _0223DE6C ; =0x00002DB0
	str r1, [r5, r0]
_0223DE16:
	add r6, r6, #1
	add r5, #0xc0
	cmp r6, r7
	blt _0223DDF0
_0223DE1E:
	ldr r0, [r4, #0x28]
	add r0, r0, #1
	str r0, [r4, #0x28]
	b _0223DE4A
_0223DE26:
	mov r6, #0
	add r5, r4, #0
_0223DE2A:
	bl LCRandom
	ldr r1, _0223DE70 ; =0x0000310C
	add r6, r6, #1
	strh r0, [r5, r1]
	add r5, r5, #2
	cmp r6, #4
	blt _0223DE2A
	ldr r0, [r4, #0x28]
	add r0, r0, #1
	str r0, [r4, #0x28]
	b _0223DE4A
_0223DE42:
	mov r0, #0
	str r0, [r4, #0x28]
	mov r0, #2
	str r0, [sp, #4]
_0223DE4A:
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _0223DE52
	b _0223DD32
_0223DE52:
	cmp r0, #2
	bne _0223DE5A
	mov r0, #8
	str r0, [r4, #8]
_0223DE5A:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223DE60: .word 0x000021E8
_0223DE64: .word 0x00003108
_0223DE68: .word 0x00002DAC
_0223DE6C: .word 0x00002DB0
_0223DE70: .word 0x0000310C

	thumb_func_start ov11_0223DE74
ov11_0223DE74: ; 0x0223DE74
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	bl ov11_0222FF84
	add r4, r0, #0
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_0224728C
	add r0, r5, #0
	add r0, #0xec
	ldr r0, [r0]
	cmp r0, r4
	bne _0223DEA0
	add r0, r5, #0
	mov r1, #0
	add r0, #0xec
	str r1, [r0]
	mov r0, #9
	str r0, [r5, #8]
	pop {r4, r5, r6, pc}
_0223DEA0:
	add r1, r5, r0
	ldr r0, _0223DEB4 ; =0x000021E8
	ldrb r1, [r1, r0]
	sub r0, #0x40
	lsl r1, r1, #4
	add r1, r5, r1
	ldr r0, [r1, r0]
	str r0, [r5, #8]
	pop {r4, r5, r6, pc}
	nop
_0223DEB4: .word 0x000021E8

	thumb_func_start ov11_0223DEB8
ov11_0223DEB8: ; 0x0223DEB8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	str r0, [sp]
	add r4, r1, #0
	mov r5, #0
	bl ov11_0222FF84
	str r0, [sp, #4]
_0223DEC8:
	ldr r1, [r4, #8]
	add r0, r4, #0
	add r2, r1, #0
	mov r3, #1
	bl ov11_0224246C
	cmp r0, #1
	beq _0223DEF2
	ldr r1, [r4, #8]
	add r0, r4, #0
	add r2, r1, #0
	bl ov11_02242510
	cmp r0, #1
	beq _0223DEF2
	ldr r0, [sp]
	add r1, r4, #0
	bl ov11_02241FD8
	cmp r0, #1
	bne _0223DEF4
_0223DEF2:
	b _0223E684
_0223DEF4:
	ldr r0, [r4, #0x10]
	cmp r0, #0xd
	bhi _0223DFCE
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223DF06: ; jump table
	.short _0223DF22 - _0223DF06 - 2 ; case 0
	.short _0223DFDC - _0223DF06 - 2 ; case 1
	.short _0223E086 - _0223DF06 - 2 ; case 2
	.short _0223E132 - _0223DF06 - 2 ; case 3
	.short _0223E1E0 - _0223DF06 - 2 ; case 4
	.short _0223E25C - _0223DF06 - 2 ; case 5
	.short _0223E2D8 - _0223DF06 - 2 ; case 6
	.short _0223E3A0 - _0223DF06 - 2 ; case 7
	.short _0223E430 - _0223DF06 - 2 ; case 8
	.short _0223E4C0 - _0223DF06 - 2 ; case 9
	.short _0223E554 - _0223DF06 - 2 ; case 10
	.short _0223E5EA - _0223DF06 - 2 ; case 11
	.short _0223E62C - _0223DF06 - 2 ; case 12
	.short _0223E666 - _0223DF06 - 2 ; case 13
_0223DF22:
	ldr r6, [r4, #0x14]
	cmp r6, #2
	bge _0223DFCA
	mov r0, #0x71
	lsl r0, r0, #2
	add r0, r4, r0
	str r0, [sp, #0x38]
	add r0, r4, #0
	str r0, [sp, #8]
	add r0, #0x14
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0x1c]
	mov r0, #0x1c
	str r0, [sp, #0x18]
_0223DF40:
	lsl r0, r6, #2
	mov r1, #0x6f
	add r0, r4, r0
	lsl r1, r1, #2
	ldr r2, [r0, r1]
	mov r1, #1
	tst r1, r2
	beq _0223DFB6
	ldr r1, [sp, #0x38]
	lsl r3, r6, #3
	ldr r7, [r1, r3]
	ldr r2, [sp, #0x18]
	add r1, r7, #0
	str r7, [sp, #0x2c]
	bic r1, r2
	str r1, [sp, #0x2c]
	lsl r1, r7, #0x1b
	lsr r1, r1, #0x1d
	sub r1, r1, #1
	lsl r1, r1, #0x1d
	lsr r2, r1, #0x1b
	ldr r1, [sp, #0x2c]
	orr r2, r1
	ldr r1, [sp, #0x38]
	str r2, [r1, r3]
	ldr r1, [r1, r3]
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x1d
	bne _0223DFB6
	mov r1, #0x6f
	lsl r1, r1, #2
	ldr r2, [r0, r1]
	ldr r1, [sp, #0x1c]
	bic r2, r1
	mov r1, #0x6f
	lsl r1, r1, #2
	str r2, [r0, r1]
	mov r1, #0x73
	add r0, r1, #0
	add r0, #0xb1
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x32
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add r1, r4, #0
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	ldr r0, [sp]
	add r2, r6, #0
	bl ov11_0224C150
	mov r1, #0x46
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r5, #1
_0223DFB6:
	ldr r0, [sp, #8]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #8]
	cmp r5, #0
	str r1, [r0]
	bne _0223DFCA
	ldr r6, [r4, #0x14]
	cmp r6, #2
	blt _0223DF40
_0223DFCA:
	cmp r5, #0
	beq _0223DFD0
_0223DFCE:
	b _0223E668
_0223DFD0:
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	mov r0, #0
	str r0, [r4, #0x14]
	b _0223E668
_0223DFDC:
	ldr r6, [r4, #0x14]
	cmp r6, #2
	bge _0223E076
	mov r0, #0x71
	lsl r0, r0, #2
	add r7, r4, r0
	add r0, r4, #0
	str r0, [sp, #0xc]
	add r0, #0x14
	str r0, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x20]
_0223DFF4:
	lsl r0, r6, #2
	add r3, r4, r0
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r1, [r3, r0]
	mov r0, #2
	tst r0, r1
	beq _0223E062
	lsl r2, r6, #3
	ldr r1, [r7, r2]
	ldr r0, _0223E340 ; =0xFFFFFC7F
	and r0, r1
	str r0, [sp, #0x30]
	lsl r0, r1, #0x16
	lsr r0, r0, #0x1d
	sub r0, r0, #1
	lsl r0, r0, #0x1d
	lsr r1, r0, #0x16
	ldr r0, [sp, #0x30]
	orr r0, r1
	str r0, [r7, r2]
	ldr r0, [r7, r2]
	lsl r0, r0, #0x16
	lsr r0, r0, #0x1d
	bne _0223E062
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r0, [r3, r0]
	ldr r1, [sp, #0x20]
	mov r2, #0x32
	bic r0, r1
	mov r1, #0x6f
	lsl r1, r1, #2
	str r0, [r3, r1]
	mov r1, #0x71
	add r0, r1, #0
	add r0, #0xb3
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add r1, r4, #0
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	ldr r0, [sp]
	add r2, r6, #0
	bl ov11_0224C150
	mov r1, #0x46
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r5, #1
_0223E062:
	ldr r0, [sp, #0xc]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0xc]
	cmp r5, #0
	str r1, [r0]
	bne _0223E076
	ldr r6, [r4, #0x14]
	cmp r6, #2
	blt _0223DFF4
_0223E076:
	cmp r5, #0
	bne _0223E124
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	mov r0, #0
	str r0, [r4, #0x14]
	b _0223E668
_0223E086:
	ldr r6, [r4, #0x14]
	cmp r6, #2
	bge _0223E120
	mov r0, #0x71
	lsl r0, r0, #2
	add r7, r4, r0
	add r0, r4, #0
	str r0, [sp, #0x10]
	add r0, #0x14
	str r0, [sp, #0x10]
	mov r0, #0x40
	str r0, [sp, #0x24]
_0223E09E:
	lsl r0, r6, #2
	add r3, r4, r0
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r1, [r3, r0]
	mov r0, #0x40
	tst r0, r1
	beq _0223E10C
	lsl r2, r6, #3
	ldr r1, [r7, r2]
	ldr r0, _0223E344 ; =0xFFFF8FFF
	and r0, r1
	str r0, [sp, #0x34]
	lsl r0, r1, #0x11
	lsr r0, r0, #0x1d
	sub r0, r0, #1
	lsl r0, r0, #0x1d
	lsr r1, r0, #0x11
	ldr r0, [sp, #0x34]
	orr r0, r1
	str r0, [r7, r2]
	ldr r0, [r7, r2]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1d
	bne _0223E10C
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r0, [r3, r0]
	ldr r1, [sp, #0x24]
	mov r2, #0x32
	bic r0, r1
	mov r1, #0x6f
	lsl r1, r1, #2
	str r0, [r3, r1]
	mov r1, #0x36
	add r0, r1, #0
	add r0, #0xee
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add r1, r4, #0
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	ldr r0, [sp]
	add r2, r6, #0
	bl ov11_0224C150
	mov r1, #0x46
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r5, #1
_0223E10C:
	ldr r0, [sp, #0x10]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x10]
	cmp r5, #0
	str r1, [r0]
	bne _0223E120
	ldr r6, [r4, #0x14]
	cmp r6, #2
	blt _0223E09E
_0223E120:
	cmp r5, #0
	beq _0223E126
_0223E124:
	b _0223E668
_0223E126:
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	mov r0, #0
	str r0, [r4, #0x14]
	b _0223E668
_0223E132:
	ldr r7, [r4, #0x14]
	cmp r7, #2
	bge _0223E1D0
	mov r0, #0x71
	lsl r0, r0, #2
	add r6, r4, r0
	add r0, r4, #0
	str r0, [sp, #0x14]
	add r0, #0x14
	str r0, [sp, #0x14]
	mov r0, #8
	str r0, [sp, #0x28]
_0223E14A:
	lsl r0, r7, #2
	add r3, r4, r0
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r1, [r3, r0]
	mov r0, #8
	tst r0, r1
	beq _0223E1BC
	lsl r0, r7, #3
	ldr r2, [r6, r0]
	ldr r1, _0223E348 ; =0xFFF1FFFF
	and r1, r2
	mov ip, r1
	lsl r1, r2, #0xc
	lsr r1, r1, #0x1d
	sub r1, r1, #1
	lsl r1, r1, #0x1d
	lsr r2, r1, #0xc
	mov r1, ip
	orr r1, r2
	str r1, [r6, r0]
	ldr r1, [r6, r0]
	lsl r1, r1, #0xc
	lsr r1, r1, #0x1d
	bne _0223E1BC
	mov r1, #0x6f
	lsl r1, r1, #2
	ldr r1, [r3, r1]
	ldr r2, [sp, #0x28]
	bic r1, r2
	mov r2, #0x6f
	lsl r2, r2, #2
	str r1, [r3, r2]
	ldr r0, [r6, r0]
	lsl r0, r0, #0xf
	lsr r1, r0, #0x1e
	add r0, r2, #0
	sub r0, #0xa4
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x6e
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add r1, r4, #0
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	ldr r0, [sp]
	add r2, r7, #0
	bl ov11_0224C150
	mov r1, #0x46
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r5, #1
_0223E1BC:
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	cmp r5, #0
	str r1, [r0]
	bne _0223E1D0
	ldr r7, [r4, #0x14]
	cmp r7, #2
	blt _0223E14A
_0223E1D0:
	cmp r5, #0
	bne _0223E24E
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	mov r0, #0
	str r0, [r4, #0x14]
	b _0223E668
_0223E1E0:
	ldr r6, [r4, #0x14]
	cmp r6, #2
	bge _0223E24A
	add r7, r4, #0
	add r7, #0x14
_0223E1EA:
	lsl r0, r6, #2
	mov r1, #0x6f
	add r0, r4, r0
	lsl r1, r1, #2
	ldr r2, [r0, r1]
	mov r1, #3
	lsl r1, r1, #8
	tst r1, r2
	beq _0223E23A
	mov r1, #0x6f
	lsl r1, r1, #2
	ldr r2, [r0, r1]
	sub r1, #0xbc
	sub r2, r2, r1
	mov r1, #0x6f
	lsl r1, r1, #2
	str r2, [r0, r1]
	ldr r1, [r0, r1]
	mov r0, #3
	lsl r0, r0, #8
	tst r0, r1
	bne _0223E23A
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xe9
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add r1, r4, #0
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	ldr r0, [sp]
	add r2, r6, #0
	bl ov11_0224C150
	mov r1, #0x46
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r5, #1
_0223E23A:
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	cmp r5, #0
	bne _0223E24A
	ldr r6, [r4, #0x14]
	cmp r6, #2
	blt _0223E1EA
_0223E24A:
	cmp r5, #0
	beq _0223E250
_0223E24E:
	b _0223E668
_0223E250:
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	mov r0, #0
	str r0, [r4, #0x14]
	b _0223E668
_0223E25C:
	ldr r6, [r4, #0x14]
	cmp r6, #2
	bge _0223E2C8
	add r7, r4, #0
	add r7, #0x14
_0223E266:
	lsl r0, r6, #2
	mov r1, #0x6f
	add r0, r4, r0
	lsl r1, r1, #2
	ldr r2, [r0, r1]
	mov r1, #7
	lsl r1, r1, #0xc
	tst r1, r2
	beq _0223E2B8
	mov r1, #0x6f
	lsl r1, r1, #2
	ldr r2, [r0, r1]
	mov r1, #1
	lsl r1, r1, #0xc
	sub r2, r2, r1
	mov r1, #0x6f
	lsl r1, r1, #2
	str r2, [r0, r1]
	ldr r1, [r0, r1]
	mov r0, #7
	lsl r0, r0, #0xc
	tst r0, r1
	bne _0223E2B8
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xfa
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add r1, r4, #0
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	ldr r0, [sp]
	add r2, r6, #0
	bl ov11_0224C150
	mov r1, #0x46
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r5, #1
_0223E2B8:
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	cmp r5, #0
	bne _0223E2C8
	ldr r6, [r4, #0x14]
	cmp r6, #2
	blt _0223E266
_0223E2C8:
	cmp r5, #0
	bne _0223E392
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	mov r0, #0
	str r0, [r4, #0x14]
	b _0223E668
_0223E2D8:
	ldr r0, [r4, #0x14]
	ldr r1, [sp, #4]
	cmp r0, r1
	bge _0223E38E
	add r6, r4, #0
	mov r7, #2
	add r6, #0x14
_0223E2E6:
	add r1, r4, r0
	ldr r0, _0223E34C ; =0x000021EC
	ldrb r2, [r1, r0]
	mov r0, #0x63
	lsl r0, r0, #2
	add r1, r4, r2
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _0223E37C
	mov r0, #0x63
	lsl r0, r0, #2
	ldrb r0, [r1, r0]
	sub r3, r0, #1
	mov r0, #0x63
	lsl r0, r0, #2
	strb r3, [r1, r0]
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _0223E37C
	mov r0, #0xc0
	mul r0, r2
	ldr r3, _0223E350 ; =0x00002D8C
	add r0, r4, r0
	ldr r3, [r0, r3]
	cmp r3, #0
	beq _0223E37C
	mov r3, #0x46
	lsl r3, r3, #2
	str r2, [r4, r3]
	add r3, r4, #0
	add r3, #0xf5
	strb r7, [r3]
	add r5, r4, #0
	ldr r3, _0223E354 ; =0x00000215
	add r5, #0xf6
	strh r3, [r5]
	sub r3, #0x5d
	ldrb r1, [r1, r3]
	lsl r1, r1, #8
	orr r2, r1
	add r1, r4, #0
	add r1, #0xf8
	str r2, [r1]
	ldr r1, _0223E358 ; =0x00002D90
	b _0223E35C
	.align 2, 0
_0223E340: .word 0xFFFFFC7F
_0223E344: .word 0xFFFF8FFF
_0223E348: .word 0xFFF1FFFF
_0223E34C: .word 0x000021EC
_0223E350: .word 0x00002D8C
_0223E354: .word 0x00000215
_0223E358: .word 0x00002D90
_0223E35C:
	ldr r0, [r0, r1]
	add r1, r7, #0
	bl ov11_022476C0
	ldr r1, _0223E688 ; =0x0000215C
	mov r2, #0x88
	str r0, [r4, r1]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	mov r5, #1
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
_0223E37C:
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	cmp r5, #0
	bne _0223E38E
	ldr r0, [r4, #0x14]
	ldr r1, [sp, #4]
	cmp r0, r1
	blt _0223E2E6
_0223E38E:
	cmp r5, #0
	beq _0223E394
_0223E392:
	b _0223E668
_0223E394:
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	mov r0, #0
	str r0, [r4, #0x14]
	b _0223E668
_0223E3A0:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r2, #3
	tst r2, r1
	beq _0223E428
	mov r2, #2
	tst r1, r2
	beq _0223E3D6
	add r0, r4, #0
	ldr r1, _0223E68C ; =0x00000321
	add r0, #0xf6
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xf5
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x68
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	b _0223E41E
_0223E3D6:
	add r1, r0, #4
	ldr r1, [r4, r1]
	sub r2, r1, #1
	add r1, r0, #4
	str r2, [r4, r1]
	add r0, r0, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0223E3FC
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xea
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	b _0223E41E
_0223E3FC:
	add r0, r4, #0
	ldr r1, _0223E68C ; =0x00000321
	add r0, #0xf6
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xf5
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x68
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
_0223E41E:
	mov r0, #0x4e
	mov r1, #0x13
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r5, #1
_0223E428:
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	b _0223E668
_0223E430:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r2, #0xc
	tst r2, r1
	beq _0223E4B8
	mov r2, #8
	tst r1, r2
	beq _0223E466
	add r0, r4, #0
	ldr r1, _0223E690 ; =0x00000325
	add r0, #0xf6
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xf5
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x68
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	b _0223E4AE
_0223E466:
	add r1, r0, #4
	ldr r1, [r4, r1]
	sub r2, r1, #1
	add r1, r0, #4
	str r2, [r4, r1]
	add r0, r0, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0223E48C
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xeb
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	b _0223E4AE
_0223E48C:
	add r0, r4, #0
	ldr r1, _0223E690 ; =0x00000325
	add r0, #0xf6
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xf5
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x68
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
_0223E4AE:
	mov r0, #0x4e
	mov r1, #0x15
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r5, #1
_0223E4B8:
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	b _0223E668
_0223E4C0:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r2, #0x30
	tst r2, r1
	beq _0223E54C
	mov r2, #0x20
	tst r1, r2
	beq _0223E4F8
	mov r1, #0xca
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0xf6
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xf5
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x68
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	b _0223E542
_0223E4F8:
	add r1, r0, #4
	ldr r1, [r4, r1]
	sub r2, r1, #1
	add r1, r0, #4
	str r2, [r4, r1]
	add r0, r0, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0223E51E
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xec
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	b _0223E542
_0223E51E:
	mov r1, #0xca
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0xf6
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xf5
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x68
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
_0223E542:
	mov r0, #0x4e
	mov r1, #0x16
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r5, #1
_0223E54C:
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	b _0223E668
_0223E554:
	mov r0, #6
	lsl r0, r0, #6
	ldr r2, [r4, r0]
	mov r1, #0xc0
	add r0, r2, #0
	tst r0, r1
	beq _0223E5E2
	mov r0, #0x80
	tst r0, r2
	beq _0223E58C
	add r0, r4, #0
	ldr r1, _0223E694 ; =0x0000032B
	add r0, #0xf6
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xf5
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x68
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	b _0223E5D8
_0223E58C:
	add r0, r1, #0
	add r0, #0xc4
	ldr r0, [r4, r0]
	sub r2, r0, #1
	add r0, r1, #0
	add r0, #0xc4
	add r1, #0xc4
	str r2, [r4, r0]
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _0223E5B6
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xed
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	b _0223E5D8
_0223E5B6:
	add r0, r4, #0
	ldr r1, _0223E694 ; =0x0000032B
	add r0, #0xf6
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xf5
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x68
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
_0223E5D8:
	mov r0, #0x4e
	mov r1, #0x14
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r5, #1
_0223E5E2:
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	b _0223E668
_0223E5EA:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r0, #2
	lsl r0, r0, #0xe
	tst r0, r1
	beq _0223E624
	add r0, r4, #0
	ldr r1, _0223E698 ; =0x0000032D
	add r0, #0xf6
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xf5
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x68
	bl ov11_022431DC
	ldr r0, [r4, #8]
	mov r1, #0x12
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x4e
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r5, #1
_0223E624:
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	b _0223E668
_0223E62C:
	mov r1, #6
	lsl r1, r1, #6
	ldr r3, [r4, r1]
	mov r2, #7
	lsl r2, r2, #0xc
	add r0, r3, #0
	tst r0, r2
	beq _0223E65E
	mov r0, #1
	lsl r0, r0, #0xc
	sub r0, r3, r0
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	tst r0, r2
	bne _0223E65E
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xee
	bl ov11_022431DC
	ldr r0, [r4, #8]
	mov r5, #1
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
_0223E65E:
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	b _0223E668
_0223E666:
	mov r5, #2
_0223E668:
	cmp r5, #0
	bne _0223E66E
	b _0223DEC8
_0223E66E:
	cmp r5, #1
	bne _0223E678
	ldr r0, [sp]
	bl ov11_0225679C
_0223E678:
	cmp r5, #2
	bne _0223E684
	mov r0, #0
	str r0, [r4, #0x10]
	mov r0, #0xa
	str r0, [r4, #8]
_0223E684:
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223E688: .word 0x0000215C
_0223E68C: .word 0x00000321
_0223E690: .word 0x00000325
_0223E694: .word 0x0000032B
_0223E698: .word 0x0000032D

	thumb_func_start ov11_0223E69C
ov11_0223E69C: ; 0x0223E69C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r4, r1, #0
	mov r1, #0
	str r1, [sp, #0x10]
	str r0, [sp, #4]
	bl ov11_0222FF84
	ldr r1, [r4, #8]
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r2, r1, #0
	mov r3, #1
	bl ov11_0224246C
	cmp r0, #1
	beq _0223E6D8
	ldr r1, [r4, #8]
	add r0, r4, #0
	add r2, r1, #0
	bl ov11_02242510
	cmp r0, #1
	beq _0223E6D8
	ldr r0, [sp, #4]
	add r1, r4, #0
	bl ov11_02241FD8
	cmp r0, #1
	bne _0223E6DC
_0223E6D8:
	bl _0223F0B2
_0223E6DC:
	ldr r1, [r4, #0x1c]
	ldr r0, [sp, #0xc]
	cmp r1, r0
	blt _0223E6E8
	bl _0223F0A8
_0223E6E8:
	ldr r0, _0223EA14 ; =0x000021EC
	add r1, r4, r1
	ldrb r5, [r1, r0]
	add r0, r5, #0
	bl MaskOfFlagNo
	ldr r1, _0223EA18 ; =0x00003108
	ldrb r1, [r4, r1]
	tst r0, r1
	beq _0223E706
	ldr r0, [r4, #0x1c]
	add r0, r0, #1
	str r0, [r4, #0x1c]
	bl _0223F09C
_0223E706:
	ldr r0, [r4, #0x18]
	cmp r0, #0x1a
	bls _0223E710
	bl _0223F08C
_0223E710:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223E71C: ; jump table
	.short _0223E752 - _0223E71C - 2 ; case 0
	.short _0223E7BA - _0223E71C - 2 ; case 1
	.short _0223E83C - _0223E71C - 2 ; case 2
	.short _0223E856 - _0223E71C - 2 ; case 3
	.short _0223E872 - _0223E71C - 2 ; case 4
	.short _0223E88C - _0223E71C - 2 ; case 5
	.short _0223E8F6 - _0223E71C - 2 ; case 6
	.short _0223E948 - _0223E71C - 2 ; case 7
	.short _0223E9C8 - _0223E71C - 2 ; case 8
	.short _0223EA04 - _0223E71C - 2 ; case 9
	.short _0223EA72 - _0223E71C - 2 ; case 10
	.short _0223EAB0 - _0223E71C - 2 ; case 11
	.short _0223EB2A - _0223E71C - 2 ; case 12
	.short _0223EBAE - _0223E71C - 2 ; case 13
	.short _0223ECA6 - _0223E71C - 2 ; case 14
	.short _0223ED0E - _0223E71C - 2 ; case 15
	.short _0223ED90 - _0223E71C - 2 ; case 16
	.short _0223EE56 - _0223E71C - 2 ; case 17
	.short _0223EE74 - _0223E71C - 2 ; case 18
	.short _0223EEBA - _0223E71C - 2 ; case 19
	.short _0223EF06 - _0223E71C - 2 ; case 20
	.short _0223EF50 - _0223E71C - 2 ; case 21
	.short _0223EF9A - _0223E71C - 2 ; case 22
	.short _0223EFE4 - _0223E71C - 2 ; case 23
	.short _0223F034 - _0223E71C - 2 ; case 24
	.short _0223F068 - _0223E71C - 2 ; case 25
	.short _0223F082 - _0223E71C - 2 ; case 26
_0223E752:
	mov r6, #0xc0
	add r0, r5, #0
	mul r0, r6
	add r3, r4, r0
	mov r0, #0xb7
	lsl r0, r0, #6
	mov r1, #1
	ldr r2, [r3, r0]
	lsl r1, r1, #0xa
	tst r1, r2
	beq _0223E7B0
	add r1, r0, #0
	sub r1, #0x34
	ldr r2, [r3, r1]
	add r1, r0, #0
	sub r1, #0x30
	ldr r1, [r3, r1]
	cmp r2, r1
	beq _0223E7B0
	cmp r2, #0
	beq _0223E7B0
	add r0, #0xc
	ldr r0, [r3, r0]
	lsl r0, r0, #0xd
	lsr r0, r0, #0x1d
	beq _0223E796
	add r6, #0x58
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xef
	str r5, [r4, r6]
	bl ov11_022431DC
	b _0223E7A4
_0223E796:
	add r6, #0x58
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x89
	str r5, [r4, r6]
	bl ov11_022431DC
_0223E7A4:
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223E7B0:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	bl _0223F08C
_0223E7BA:
	mov r0, #0xc0
	add r1, r5, #0
	mul r1, r0
	add r6, r4, r1
	mov r1, #0xb7
	lsl r1, r1, #6
	mov r2, #1
	ldr r3, [r6, r1]
	lsl r2, r2, #0x18
	tst r2, r3
	beq _0223E832
	add r2, r1, #0
	sub r2, #0x34
	ldr r3, [r6, r2]
	add r2, r1, #0
	sub r2, #0x30
	ldr r2, [r6, r2]
	cmp r3, r2
	beq _0223E832
	cmp r3, #0
	beq _0223E832
	add r2, r1, #0
	add r2, #0xc
	ldr r2, [r6, r2]
	lsl r2, r2, #0xd
	lsr r2, r2, #0x1d
	beq _0223E800
	add r0, #0x58
	str r5, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xef
	bl ov11_022431DC
	b _0223E826
_0223E800:
	add r2, r0, #0
	add r2, #0x58
	str r5, [r4, r2]
	add r2, r0, #0
	add r2, #0xc8
	add r0, #0x64
	sub r1, #0x30
	str r2, [r4, r0]
	ldr r0, [r6, r1]
	mov r1, #0x10
	bl ov11_022476C0
	ldr r1, _0223EA1C ; =0x0000215C
	mov r2, #0xa9
	str r0, [r4, r1]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
_0223E826:
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223E832:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	bl _0223F08C
_0223E83C:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_022475B8
	cmp r0, #1
	bne _0223E84C
	mov r0, #1
	str r0, [sp, #0x10]
_0223E84C:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	bl _0223F08C
_0223E856:
	ldr r0, [sp, #4]
	add r1, r4, #0
	add r2, r5, #0
	bl ov11_02248C0C
	cmp r0, #1
	bne _0223E868
	mov r0, #1
	str r0, [sp, #0x10]
_0223E868:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	bl _0223F08C
_0223E872:
	ldr r0, [sp, #4]
	add r1, r4, #0
	add r2, r5, #0
	bl ov11_022492A4
	cmp r0, #1
	bne _0223E884
	mov r0, #1
	str r0, [sp, #0x10]
_0223E884:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223E88C:
	mov r3, #0xc0
	add r0, r5, #0
	mul r0, r3
	mov r2, #0xb7
	add r6, r4, r0
	lsl r2, r2, #6
	ldr r0, [r6, r2]
	mov r1, #4
	tst r1, r0
	beq _0223E8EE
	mov r1, #3
	and r0, r1
	add r1, r0, #0
	mul r1, r3
	add r0, r4, r1
	sub r2, #0x34
	ldr r0, [r0, r2]
	cmp r0, #0
	beq _0223E8EE
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02246D1C
	cmp r0, #0x62
	beq _0223E8EE
	ldr r0, _0223EA20 ; =0x00002D8C
	ldr r1, [r6, r0]
	cmp r1, #0
	beq _0223E8EE
	add r0, #0x34
	ldr r1, [r6, r0]
	mov r0, #3
	and r1, r0
	mov r0, #0x47
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r0, #4
	str r5, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x45
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223E8EE:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223E8F6:
	mov r2, #0xc0
	add r0, r5, #0
	mul r0, r2
	ldr r3, _0223EA24 ; =0x00002DAC
	add r0, r4, r0
	ldr r1, [r0, r3]
	mov r6, #8
	tst r1, r6
	beq _0223E940
	add r1, r3, #0
	sub r1, #0x20
	ldr r1, [r0, r1]
	cmp r1, #0
	beq _0223E940
	add r2, #0x58
	str r5, [r4, r2]
	sub r3, #0x1c
	ldr r1, [r0, r3]
	add r0, r6, #0
	sub r0, #9
	mul r0, r1
	add r1, r6, #0
	bl ov11_022476C0
	ldr r1, _0223EA1C ; =0x0000215C
	mov r2, #0x17
	str r0, [r4, r1]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223E940:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223E948:
	mov r0, #0xc0
	mul r0, r5
	ldr r1, _0223EA24 ; =0x00002DAC
	add r6, r4, r0
	ldr r0, [r6, r1]
	mov r2, #0x80
	tst r0, r2
	beq _0223E9C0
	add r0, r1, #0
	sub r0, #0x20
	ldr r0, [r6, r0]
	cmp r0, #0
	beq _0223E9C0
	add r2, #0x98
	str r5, [r4, r2]
	sub r1, #0x1c
	ldr r0, [r6, r1]
	mov r1, #0x10
	bl ov11_022476C0
	ldr r1, _0223EA1C ; =0x0000215C
	str r0, [r4, r1]
	ldr r1, _0223EA24 ; =0x00002DAC
	mov r0, #0xf
	ldr r2, [r6, r1]
	lsl r0, r0, #8
	add r3, r2, #0
	and r3, r0
	cmp r3, r0
	beq _0223E98C
	mov r0, #1
	lsl r0, r0, #8
	add r0, r2, r0
	str r0, [r6, r1]
_0223E98C:
	ldr r2, _0223EA24 ; =0x00002DAC
	ldr r0, _0223EA1C ; =0x0000215C
	ldr r3, [r6, r2]
	mov r2, #0xf
	lsl r2, r2, #8
	and r2, r3
	ldr r1, [r4, r0]
	lsr r2, r2, #8
	mul r2, r1
	str r2, [r4, r0]
	mov r1, #0
	ldr r2, [r4, r0]
	mvn r1, r1
	mul r1, r2
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x17
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223E9C0:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223E9C8:
	mov r0, #0xc0
	add r1, r5, #0
	mul r1, r0
	add r6, r4, r1
	ldr r1, _0223EA24 ; =0x00002DAC
	mov r2, #0x10
	ldr r3, [r6, r1]
	tst r2, r3
	beq _0223E9FC
	sub r1, #0x20
	ldr r1, [r6, r1]
	cmp r1, #0
	beq _0223E9FC
	add r0, #0x58
	str r5, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x1a
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223E9FC:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223EA04:
	mov r6, #0xc0
	add r0, r5, #0
	mul r0, r6
	add r3, r4, r0
	ldr r7, _0223EA28 ; =0x00002DB0
	ldr r0, _0223EA18 ; =0x00003108
	b _0223EA2C
	nop
_0223EA14: .word 0x000021EC
_0223EA18: .word 0x00003108
_0223EA1C: .word 0x0000215C
_0223EA20: .word 0x00002D8C
_0223EA24: .word 0x00002DAC
_0223EA28: .word 0x00002DB0
_0223EA2C:
	ldr r2, [r3, r7]
	lsl r0, r0, #0x18
	tst r0, r2
	beq _0223EA6A
	add r0, r7, #0
	sub r0, #0x24
	ldr r0, [r3, r0]
	cmp r0, #0
	beq _0223EA6A
	sub r0, r7, #4
	ldr r1, [r3, r0]
	mov r0, #7
	tst r0, r1
	beq _0223EA64
	add r6, #0x58
	str r5, [r4, r6]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x5e
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
	b _0223EA6A
_0223EA64:
	ldr r0, _0223ED9C ; =0xF7FFFFFF
	and r0, r2
	str r0, [r3, r7]
_0223EA6A:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223EA72:
	mov r0, #0xc0
	add r1, r5, #0
	mul r1, r0
	add r6, r4, r1
	ldr r1, _0223EDA0 ; =0x00002DB0
	mov r2, #1
	ldr r3, [r6, r1]
	lsl r2, r2, #0x1c
	tst r2, r3
	beq _0223EAA8
	sub r1, #0x24
	ldr r1, [r6, r1]
	cmp r1, #0
	beq _0223EAA8
	add r0, #0x58
	str r5, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x62
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223EAA8:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223EAB0:
	mov r1, #0xc0
	add r0, r5, #0
	mul r0, r1
	ldr r2, _0223EDA0 ; =0x00002DB0
	add r6, r4, r0
	ldr r3, [r6, r2]
	mov r7, #0xe
	lsl r7, r7, #0xc
	add r0, r3, #0
	tst r0, r7
	beq _0223EB22
	add r0, r2, #0
	sub r0, #0x24
	ldr r0, [r6, r0]
	cmp r0, #0
	beq _0223EB22
	mov r0, #2
	lsl r0, r0, #0xc
	sub r0, r3, r0
	str r0, [r6, r2]
	ldr r0, [r6, r2]
	tst r0, r7
	beq _0223EAFE
	sub r2, #0x20
	ldr r2, [r6, r2]
	sub r1, #0xc1
	add r0, r2, #0
	mul r0, r1
	mov r1, #0x10
	bl ov11_022476C0
	ldr r1, _0223EDA4 ; =0x0000215C
	mov r2, #0x3b
	str r0, [r4, r1]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	b _0223EB08
_0223EAFE:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x3c
	bl ov11_022431DC
_0223EB08:
	ldr r0, _0223EDA8 ; =0x00002DEA
	ldrh r1, [r6, r0]
	mov r0, #0x49
	lsl r0, r0, #2
	str r1, [r4, r0]
	sub r0, #0xc
	str r5, [r4, r0]
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223EB22:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223EB2A:
	mov r0, #0x7b
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r4, #0
	mov r2, #4
	add r3, r5, #0
	bl ov11_02246870
	mov r1, #0x4e
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0xc0
	mul r0, r5
	add r6, r4, r0
	ldr r0, _0223EDAC ; =0x00002DAC
	ldr r1, [r6, r0]
	mov r0, #7
	tst r0, r1
	beq _0223EBA6
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02246D1C
	cmp r0, #0x62
	beq _0223EBA6
	ldr r1, _0223EDB0 ; =0x00002D8C
	ldr r0, [r6, r1]
	cmp r0, #0
	beq _0223EBA6
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0223EBA6
	add r0, r1, #4
	ldr r1, [r6, r0]
	mov r0, #0
	mvn r0, r0
	mul r0, r1
	mov r1, #8
	bl ov11_022476C0
	ldr r1, _0223EDA4 ; =0x0000215C
	ldr r2, _0223EDB4 ; =0x00000107
	str r0, [r4, r1]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, _0223EDB8 ; =0x0000213C
	mov r1, #0x40
	ldr r2, [r4, r0]
	orr r2, r1
	str r2, [r4, r0]
	add r1, #0xd8
	str r5, [r4, r1]
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223EBA6:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223EBAE:
	mov r0, #0xc0
	mul r0, r5
	add r7, r4, r0
	ldr r0, _0223EDA0 ; =0x00002DB0
	ldr r1, [r7, r0]
	mov r0, #0x70
	tst r0, r1
	beq _0223EC96
	ldr r0, [sp, #0xc]
	mov r6, #0
	cmp r0, #0
	ble _0223EC08
_0223EBC6:
	mov r0, #0xc0
	mul r0, r6
	add r1, r4, r0
	ldr r0, _0223EDAC ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #7
	tst r0, r1
	beq _0223EBFC
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_02246D1C
	cmp r0, #0x2b
	beq _0223EBFC
	mov r0, #0x46
	lsl r0, r0, #2
	str r6, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x13
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	b _0223EC08
_0223EBFC:
	add r0, r6, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldr r0, [sp, #0xc]
	cmp r6, r0
	blt _0223EBC6
_0223EC08:
	ldr r0, [sp, #0xc]
	cmp r6, r0
	beq _0223EC14
	mov r0, #2
	str r0, [sp, #0x10]
	b _0223F08C
_0223EC14:
	ldr r0, _0223EDA0 ; =0x00002DB0
	ldr r1, [r7, r0]
	sub r1, #0x10
	str r1, [r7, r0]
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02246764
	cmp r0, #0
	ldr r2, _0223EDA0 ; =0x00002DB0
	beq _0223EC4E
	ldr r1, [r7, r2]
	mov r0, #0x70
	bic r1, r0
	mov r6, #0xf1
	add r0, r5, #0
	str r1, [r7, r2]
	bl MaskOfFlagNo
	add r3, r6, #0
	add r3, #0x8f
	lsl r2, r0, #8
	add r0, r6, #0
	sub r0, #0xf2
	ldr r1, [r4, r3]
	eor r0, r2
	and r0, r1
	str r0, [r4, r3]
	b _0223EC7A
_0223EC4E:
	ldr r1, [r7, r2]
	mov r0, #0x70
	tst r0, r1
	beq _0223EC5A
	mov r6, #0xf0
	b _0223EC7A
_0223EC5A:
	mov r0, #0x70
	bic r1, r0
	mov r6, #0xf1
	add r0, r5, #0
	str r1, [r7, r2]
	bl MaskOfFlagNo
	add r3, r6, #0
	add r3, #0x8f
	lsl r2, r0, #8
	add r0, r6, #0
	sub r0, #0xf2
	ldr r1, [r4, r3]
	eor r0, r2
	and r0, r1
	str r0, [r4, r3]
_0223EC7A:
	mov r0, #0x46
	lsl r0, r0, #2
	str r5, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	add r2, r6, #0
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223EC96:
	ldr r0, [sp, #0x10]
	cmp r0, #2
	bne _0223EC9E
	b _0223F08C
_0223EC9E:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223ECA6:
	mov r2, #0xc0
	add r0, r5, #0
	mul r0, r2
	add r6, r4, r0
	ldr r0, _0223EDA0 ; =0x00002DB0
	lsl r2, r2, #4
	ldr r1, [r6, r0]
	tst r2, r1
	beq _0223ED06
	mov r2, #1
	lsl r2, r2, #0xa
	sub r1, r1, r2
	str r1, [r6, r0]
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02246764
	cmp r0, #0
	beq _0223ECD8
	ldr r1, _0223EDA0 ; =0x00002DB0
	ldr r0, _0223EDBC ; =0xFFFFF3FF
	ldr r2, [r6, r1]
	and r0, r2
	str r0, [r6, r1]
	b _0223ED06
_0223ECD8:
	ldr r0, _0223EDA0 ; =0x00002DB0
	ldr r1, [r6, r0]
	mov r0, #3
	lsl r0, r0, #0xa
	tst r0, r1
	bne _0223ED06
	mov r0, #7
	tst r0, r1
	bne _0223ED06
	add r0, r4, #0
	add r0, #0x94
	str r5, [r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x33
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223ED06:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223ED0E:
	mov r0, #0xc0
	add r6, r5, #0
	mul r6, r0
	add r0, r4, r6
	ldr r1, _0223EDC0 ; =0x00002DE8
	mov ip, r0
	ldrh r3, [r0, r1]
	cmp r3, #0
	beq _0223ED88
	ldr r7, _0223EDC4 ; =0x00002D4C
	mov r2, #0
	mov r1, ip
_0223ED26:
	ldrh r0, [r1, r7]
	cmp r3, r0
	beq _0223ED34
	add r2, r2, #1
	add r1, r1, #2
	cmp r2, #4
	blt _0223ED26
_0223ED34:
	cmp r2, #4
	bne _0223ED44
	ldr r0, _0223EDC8 ; =0x00002DC8
	add r1, r4, r0
	ldr r2, [r1, r6]
	mov r0, #7
	bic r2, r0
	str r2, [r1, r6]
_0223ED44:
	ldr r1, _0223EDC8 ; =0x00002DC8
	add r0, r4, r6
	ldr r0, [r0, r1]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1d
	beq _0223ED64
	add r2, r4, r1
	ldr r1, [r2, r6]
	mov r3, #7
	bic r1, r3
	sub r3, r0, #1
	mov r0, #7
	and r0, r3
	orr r0, r1
	str r0, [r2, r6]
	b _0223ED88
_0223ED64:
	mov r2, #0
	add r1, #0x20
	mov r0, ip
	strh r2, [r0, r1]
	mov r0, #0x46
	lsl r0, r0, #2
	str r5, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x48
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223ED88:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223ED90:
	mov r0, #0xc0
	add r6, r5, #0
	mul r6, r0
	add r0, r4, r6
	ldr r1, _0223EDCC ; =0x00002DEC
	b _0223EDD0
	.align 2, 0
_0223ED9C: .word 0xF7FFFFFF
_0223EDA0: .word 0x00002DB0
_0223EDA4: .word 0x0000215C
_0223EDA8: .word 0x00002DEA
_0223EDAC: .word 0x00002DAC
_0223EDB0: .word 0x00002D8C
_0223EDB4: .word 0x00000107
_0223EDB8: .word 0x0000213C
_0223EDBC: .word 0xFFFFF3FF
_0223EDC0: .word 0x00002DE8
_0223EDC4: .word 0x00002D4C
_0223EDC8: .word 0x00002DC8
_0223EDCC: .word 0x00002DEC
_0223EDD0:
	str r0, [sp, #8]
	ldrh r2, [r0, r1]
	cmp r2, #0
	beq _0223EE4E
	ldr r7, _0223F0B8 ; =0x00002D4C
	mov r3, #0
	add r1, r0, #0
_0223EDDE:
	ldrh r0, [r1, r7]
	cmp r2, r0
	beq _0223EDEC
	add r3, r3, #1
	add r1, r1, #2
	cmp r3, #4
	blt _0223EDDE
_0223EDEC:
	cmp r3, #4
	beq _0223EDFE
	beq _0223EE0A
	ldr r0, [sp, #8]
	add r1, r0, r3
	ldr r0, _0223F0BC ; =0x00002D6C
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _0223EE0A
_0223EDFE:
	ldr r0, _0223F0C0 ; =0x00002DC8
	add r2, r4, r0
	ldr r1, [r2, r6]
	mov r0, #0x38
	bic r1, r0
	str r1, [r2, r6]
_0223EE0A:
	ldr r1, _0223F0C0 ; =0x00002DC8
	add r0, r4, r6
	ldr r0, [r0, r1]
	lsl r0, r0, #0x1a
	lsr r2, r0, #0x1d
	beq _0223EE2A
	add r1, r4, r1
	sub r2, r2, #1
	lsl r2, r2, #0x1d
	ldr r0, [r1, r6]
	mov r3, #0x38
	bic r0, r3
	lsr r2, r2, #0x1a
	orr r0, r2
	str r0, [r1, r6]
	b _0223EE4E
_0223EE2A:
	ldr r0, [sp, #8]
	mov r2, #0
	add r1, #0x24
	strh r2, [r0, r1]
	mov r0, #0x46
	lsl r0, r0, #2
	str r5, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x4a
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223EE4E:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223EE56:
	mov r0, #0xc0
	mul r0, r5
	add r3, r4, r0
	mov r0, #0xb7
	lsl r0, r0, #6
	ldr r2, [r3, r0]
	mov r1, #0x18
	tst r1, r2
	beq _0223EE6C
	sub r2, #8
	str r2, [r3, r0]
_0223EE6C:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223EE74:
	mov r0, #0xc0
	mul r0, r5
	ldr r2, _0223F0C0 ; =0x00002DC8
	add r5, r4, r0
	ldr r1, [r5, r2]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1e
	beq _0223EEB2
	add r3, r4, r2
	ldr r6, [r3, r0]
	mov r1, #0xc0
	add r7, r6, #0
	bic r7, r1
	lsl r1, r6, #0x18
	lsr r1, r1, #0x1e
	sub r1, r1, #1
	lsl r1, r1, #0x1e
	lsr r1, r1, #0x18
	orr r1, r7
	str r1, [r3, r0]
	ldr r0, [r3, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1e
	bne _0223EEB2
	add r0, r2, #0
	sub r0, #8
	ldr r1, [r5, r0]
	ldr r0, _0223F0C4 ; =0xFFFFFDFF
	sub r2, #8
	and r0, r1
	str r0, [r5, r2]
_0223EEB2:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223EEBA:
	ldr r0, _0223F0C0 ; =0x00002DC8
	mov r2, #0xc0
	add r3, r5, #0
	mul r3, r2
	add r1, r4, r0
	ldr r7, [r1, r3]
	lsl r0, r7, #0x15
	lsr r6, r0, #0x1d
	beq _0223EEFE
	ldr r0, _0223F0C8 ; =0xFFFFF8FF
	and r7, r0
	sub r0, r6, #1
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x15
	orr r0, r7
	str r0, [r1, r3]
	ldr r0, [r1, r3]
	lsl r0, r0, #0x15
	lsr r0, r0, #0x1d
	bne _0223EEFE
	add r0, r2, #0
	add r0, #0x58
	str r5, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	add r2, #0x60
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223EEFE:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223EF06:
	ldr r0, _0223F0CC ; =0x00002DCC
	mov r1, #0xc0
	add r3, r5, #0
	mul r3, r1
	add r2, r4, r0
	ldr r7, [r2, r3]
	lsl r0, r7, #0x10
	lsr r6, r0, #0x1d
	beq _0223EF48
	ldr r0, _0223F0D0 ; =0xFFFF1FFF
	and r7, r0
	sub r0, r6, #1
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x10
	orr r0, r7
	str r0, [r2, r3]
	ldr r0, [r2, r3]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x1d
	bne _0223EF48
	add r1, #0x58
	str r5, [r4, r1]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xf2
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223EF48:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223EF50:
	ldr r0, _0223F0CC ; =0x00002DCC
	mov r1, #0xc0
	add r3, r5, #0
	mul r3, r1
	add r2, r4, r0
	ldr r7, [r2, r3]
	lsl r0, r7, #0xd
	lsr r6, r0, #0x1d
	beq _0223EF92
	ldr r0, _0223F0D4 ; =0xFFF8FFFF
	and r7, r0
	sub r0, r6, #1
	lsl r0, r0, #0x1d
	lsr r0, r0, #0xd
	orr r0, r7
	str r0, [r2, r3]
	ldr r0, [r2, r3]
	lsl r0, r0, #0xd
	lsr r0, r0, #0x1d
	bne _0223EF92
	add r1, #0x58
	str r5, [r4, r1]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xf3
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223EF92:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223EF9A:
	ldr r0, _0223F0CC ; =0x00002DCC
	mov r1, #0xc0
	add r3, r5, #0
	mul r3, r1
	add r2, r4, r0
	ldr r7, [r2, r3]
	lsl r0, r7, #0xa
	lsr r6, r0, #0x1d
	beq _0223EFDC
	ldr r0, _0223F0D8 ; =0xFFC7FFFF
	and r7, r0
	sub r0, r6, #1
	lsl r0, r0, #0x1d
	lsr r0, r0, #0xa
	orr r0, r7
	str r0, [r2, r3]
	ldr r0, [r2, r3]
	lsl r0, r0, #0xa
	lsr r0, r0, #0x1d
	bne _0223EFDC
	add r1, #0x58
	str r5, [r4, r1]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xf4
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223EFDC:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223EFE4:
	mov r6, #0xc0
	add r0, r5, #0
	mul r0, r6
	mov r3, #0xb7
	add r1, r4, r0
	lsl r3, r3, #6
	ldr r0, [r1, r3]
	lsl r2, r6, #5
	tst r2, r0
	beq _0223F02C
	mov r2, #2
	lsl r2, r2, #0xa
	sub r0, r0, r2
	str r0, [r1, r3]
	ldr r1, [r1, r3]
	lsl r0, r6, #5
	tst r0, r1
	bne _0223F02C
	add r0, r4, #0
	add r0, #0x94
	str r5, [r0]
	add r0, r4, #0
	mov r1, #4
	add r0, #0x88
	str r1, [r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x12
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223F02C:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223F034:
	ldr r0, [sp, #4]
	add r1, r4, #0
	add r2, r5, #0
	add r3, sp, #0x14
	bl ov11_022493A0
	cmp r0, #1
	bne _0223F060
	mov r0, #0x46
	lsl r0, r0, #2
	str r5, [r4, r0]
	ldr r2, [sp, #0x14]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #0x10]
_0223F060:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223F068:
	ldr r0, [sp, #4]
	add r1, r4, #0
	add r2, r5, #0
	bl ov11_02249A7C
	cmp r0, #1
	bne _0223F07A
	mov r0, #1
	str r0, [sp, #0x10]
_0223F07A:
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	b _0223F08C
_0223F082:
	mov r0, #0
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x1c]
	add r0, r0, #1
	str r0, [r4, #0x1c]
_0223F08C:
	ldr r0, [sp, #0x10]
	cmp r0, #0
	beq _0223F09C
	ldr r0, [sp, #4]
	bl ov11_0225679C
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0223F09C:
	ldr r1, [r4, #0x1c]
	ldr r0, [sp, #0xc]
	cmp r1, r0
	bge _0223F0A8
	bl _0223E6E8
_0223F0A8:
	mov r0, #0
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	mov r0, #0xb
	str r0, [r4, #8]
_0223F0B2:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223F0B8: .word 0x00002D4C
_0223F0BC: .word 0x00002D6C
_0223F0C0: .word 0x00002DC8
_0223F0C4: .word 0xFFFFFDFF
_0223F0C8: .word 0xFFFFF8FF
_0223F0CC: .word 0x00002DCC
_0223F0D0: .word 0xFFFF1FFF
_0223F0D4: .word 0xFFF8FFFF
_0223F0D8: .word 0xFFC7FFFF

	thumb_func_start ov11_0223F0DC
ov11_0223F0DC: ; 0x0223F0DC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	str r0, [sp]
	bl ov11_0222FF84
	ldr r1, [r4, #8]
	add r7, r0, #0
	add r0, r4, #0
	add r2, r1, #0
	mov r3, #1
	bl ov11_0224246C
	cmp r0, #1
	bne _0223F0FC
	b _0223F30C
_0223F0FC:
	ldr r0, [sp]
	bl ov11_0225679C
	ldr r0, [r4, #0x20]
	cmp r0, #0
	beq _0223F114
	cmp r0, #1
	beq _0223F1FE
	cmp r0, #2
	bne _0223F112
	b _0223F2C4
_0223F112:
	b _0223F302
_0223F114:
	ldr r0, [r4, #0x24]
	cmp r0, r7
	bge _0223F1F4
	add r5, r4, #0
	add r5, #0x24
_0223F11E:
	add r1, r4, r0
	ldr r0, _0223F310 ; =0x000021EC
	ldrb r6, [r1, r0]
	add r0, r6, #0
	bl MaskOfFlagNo
	ldr r1, _0223F314 ; =0x00003108
	ldrb r1, [r4, r1]
	tst r0, r1
	ldr r0, [r5]
	beq _0223F13A
	add r0, r0, #1
	str r0, [r5]
	b _0223F1EE
_0223F13A:
	add r0, r0, #1
	mov r1, #0x62
	str r0, [r5]
	add r0, r4, r6
	lsl r1, r1, #2
	ldrb r1, [r0, r1]
	cmp r1, #0
	beq _0223F1EE
	mov r1, #0x62
	lsl r1, r1, #2
	ldrb r1, [r0, r1]
	sub r2, r1, #1
	mov r1, #0x62
	lsl r1, r1, #2
	strb r2, [r0, r1]
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _0223F1EE
	mov r0, #0xc0
	mul r0, r6
	add r1, r4, r0
	ldr r0, _0223F318 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223F1EE
	ldr r0, [sp]
	add r1, r6, #0
	bl ov11_02230270
	mov r2, #0x6f
	lsl r2, r2, #2
	add r1, r4, r2
	lsl r5, r0, #2
	ldr r3, [r1, r5]
	mov r0, #0x10
	bic r3, r0
	add r0, r4, #0
	str r3, [r1, r5]
	add r2, #0x1f
	add r0, #0xf6
	strh r2, [r0]
	add r0, r4, #0
	mov r1, #0xa
	add r0, #0xf5
	strb r1, [r0]
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0224682C
	add r1, r4, #0
	add r1, #0xf8
	str r0, [r1]
	mov r0, #0x19
	lsl r0, r0, #4
	add r1, r4, #0
	add r3, r4, r0
	lsl r2, r6, #1
	ldrh r5, [r3, r2]
	add r1, #0xfc
	str r5, [r1]
	add r1, r0, #0
	sub r1, #0x78
	str r6, [r4, r1]
	lsl r1, r6, #2
	add r5, r0, #0
	add r1, r4, r1
	add r5, #8
	ldr r6, [r1, r5]
	add r5, r0, #0
	sub r5, #0x74
	str r6, [r4, r5]
	ldrh r3, [r3, r2]
	add r2, r0, #0
	sub r2, #0x6c
	str r3, [r4, r2]
	add r0, #0x18
	ldr r1, [r1, r0]
	ldr r0, _0223F31C ; =0x0000215C
	mov r2, #0x79
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add sp, #8
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223F1EE:
	ldr r0, [r4, #0x24]
	cmp r0, r7
	blt _0223F11E
_0223F1F4:
	ldr r0, [r4, #0x20]
	add r0, r0, #1
	str r0, [r4, #0x20]
	mov r0, #0
	str r0, [r4, #0x24]
_0223F1FE:
	ldr r0, [r4, #0x24]
	cmp r0, r7
	bge _0223F2BA
	add r5, r4, #0
	add r5, #0x24
_0223F208:
	add r1, r4, r0
	ldr r0, _0223F310 ; =0x000021EC
	ldrb r6, [r1, r0]
	add r0, r6, #0
	bl MaskOfFlagNo
	ldr r1, _0223F314 ; =0x00003108
	ldrb r1, [r4, r1]
	tst r0, r1
	ldr r0, [r5]
	beq _0223F224
	add r0, r0, #1
	str r0, [r5]
	b _0223F2B4
_0223F224:
	add r0, r0, #1
	str r0, [r5]
	mov r0, #0xc0
	mul r0, r6
	mov r1, #0xb7
	add r3, r4, r0
	lsl r1, r1, #6
	ldr r2, [r3, r1]
	mov r1, #0x20
	tst r1, r2
	beq _0223F2B4
	ldr r7, _0223F320 ; =0x00002DC8
	add r2, r4, r7
	ldr r1, [r2, r0]
	lsl r1, r1, #0x11
	lsr r1, r1, #0x1e
	bne _0223F27E
	add r1, r7, #0
	sub r1, #8
	add r1, r4, r1
	str r1, [sp, #4]
	ldr r1, [r1, r0]
	mov r5, #0x20
	bic r1, r5
	ldr r5, [sp, #4]
	sub r7, #0x3c
	str r1, [r5, r0]
	ldr r0, [r2, r0]
	lsl r0, r0, #0x11
	lsr r1, r0, #0x1e
	mov r0, #0x13
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r0, [r3, r7]
	ldr r1, _0223F31C ; =0x0000215C
	neg r0, r0
	str r0, [r4, r1]
	add r0, r1, #0
	sub r0, #0x20
	ldr r2, [r4, r0]
	mov r0, #0x40
	orr r0, r2
	sub r1, #0x20
	str r0, [r4, r1]
	b _0223F298
_0223F27E:
	mov r3, #0x13
	lsl r3, r3, #4
	str r1, [r4, r3]
	ldr r3, [r2, r0]
	ldr r1, _0223F324 ; =0xFFFF9FFF
	and r1, r3
	lsl r3, r3, #0x11
	lsr r3, r3, #0x1e
	sub r3, r3, #1
	lsl r3, r3, #0x1e
	lsr r3, r3, #0x11
	orr r1, r3
	str r1, [r2, r0]
_0223F298:
	mov r0, #0x46
	lsl r0, r0, #2
	str r6, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x66
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add sp, #8
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223F2B4:
	ldr r0, [r4, #0x24]
	cmp r0, r7
	blt _0223F208
_0223F2BA:
	ldr r0, [r4, #0x20]
	add r0, r0, #1
	str r0, [r4, #0x20]
	mov r0, #0
	str r0, [r4, #0x24]
_0223F2C4:
	mov r1, #6
	lsl r1, r1, #6
	ldr r3, [r4, r1]
	mov r2, #7
	lsl r2, r2, #0x10
	add r0, r3, #0
	tst r0, r2
	beq _0223F2F8
	mov r0, #1
	lsl r0, r0, #0x10
	sub r0, r3, r0
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	tst r0, r2
	bne _0223F2F8
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xfb
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add sp, #8
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223F2F8:
	ldr r0, [r4, #0x20]
	add r0, r0, #1
	str r0, [r4, #0x20]
	mov r0, #0
	str r0, [r4, #0x24]
_0223F302:
	mov r0, #0
	str r0, [r4, #0x20]
	str r0, [r4, #0x24]
	mov r0, #0xc
	str r0, [r4, #8]
_0223F30C:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223F310: .word 0x000021EC
_0223F314: .word 0x00003108
_0223F318: .word 0x00002D8C
_0223F31C: .word 0x0000215C
_0223F320: .word 0x00002DC8
_0223F324: .word 0xFFFF9FFF

	thumb_func_start ov11_0223F328
ov11_0223F328: ; 0x0223F328
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4, #8]
	add r5, r0, #0
	add r0, r4, #0
	add r2, r1, #0
	bl ov11_02242510
	cmp r0, #1
	beq _0223F37C
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02241FD8
	cmp r0, #1
	beq _0223F37C
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02241D2C
	cmp r0, #1
	beq _0223F37C
	mov r1, #0x15
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	add r0, r0, #1
	str r0, [r4, r1]
	add r0, r1, #0
	add r0, #0x24
	ldr r0, [r4, r0]
	add r1, #0x24
	add r0, r0, #1
	str r0, [r4, r1]
	add r0, r4, #0
	bl ov11_02245494
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02245C5C
	mov r0, #2
	str r0, [r4, #8]
_0223F37C:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_0223F380
ov11_0223F380: ; 0x0223F380
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xec
	ldr r0, [r0]
	mov r4, #0
	add r1, r5, r0
	ldr r0, _0223F4A8 ; =0x000021E8
	ldrb r2, [r1, r0]
	lsl r0, r2, #6
	add r1, r5, r0
	mov r0, #0x75
	str r2, [r5, #0x64]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _0223F3B4
	mov r0, #0xc1
	mov r1, #0xa5
	lsl r0, r0, #6
	str r1, [r5, r0]
	mov r4, #1
	b _0223F478
_0223F3B4:
	mov r0, #0xc0
	mul r0, r2
	ldr r6, _0223F4AC ; =0x00002DEC
	add r0, r5, r0
	ldrh r1, [r0, r6]
	cmp r1, #0
	beq _0223F3DC
	add r3, r6, #2
	ldrh r3, [r0, r3]
	sub r6, #0xa0
	lsl r3, r3, #1
	add r0, r0, r3
	ldrh r0, [r0, r6]
	cmp r1, r0
	bne _0223F3DC
	mov r0, #0xc1
	lsl r0, r0, #6
	str r1, [r5, r0]
	mov r4, #1
	b _0223F478
_0223F3DC:
	cmp r1, #0
	beq _0223F42E
	mov r7, #0xc0
	add r0, r2, #0
	mul r0, r7
	ldr r3, _0223F4B0 ; =0x00002DEE
	add r0, r5, r0
	ldrh r6, [r0, r3]
	lsl r6, r6, #1
	add r0, r0, r6
	add r6, r3, #0
	sub r6, #0xa2
	ldrh r0, [r0, r6]
	cmp r1, r0
	beq _0223F42E
	mov r1, #0xc1
	lsl r1, r1, #6
	str r0, [r5, r1]
	ldr r1, [r5, #0x64]
	mov r0, #0
	add r2, r1, #0
	mul r2, r7
	add r2, r5, r2
	sub r1, r3, #2
	strh r0, [r2, r1]
	ldr r1, [r5, #0x64]
	mov r4, #1
	add r2, r1, #0
	mul r2, r7
	add r1, r5, r2
	strh r0, [r1, r3]
	ldr r0, [r5, #0x64]
	sub r3, #0x26
	add r2, r0, #0
	add r3, r5, r3
	mul r2, r7
	ldr r1, [r3, r2]
	mov r0, #0x38
	bic r1, r0
	str r1, [r3, r2]
	b _0223F478
_0223F42E:
	add r0, r5, #0
	add r1, r2, #0
	bl ov11_0224AD04
	cmp r0, #0
	bne _0223F44A
	ldr r0, [r5, #0x64]
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, _0223F4B4 ; =0x0000304C
	ldr r1, [r1, r0]
	sub r0, #0xc
	str r1, [r5, r0]
	b _0223F478
_0223F44A:
	ldr r2, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r2
	lsl r1, r2, #1
	add r3, r5, r0
	add r0, r5, r1
	ldr r1, _0223F4B8 ; =0x000030BC
	ldrh r2, [r0, r1]
	lsl r2, r2, #1
	add r3, r3, r2
	ldr r2, _0223F4BC ; =0x00002D4C
	ldrh r3, [r3, r2]
	add r2, r1, #0
	sub r2, #8
	ldrh r0, [r0, r2]
	cmp r0, r3
	beq _0223F474
	sub r1, #0x7c
	str r3, [r5, r1]
	mov r4, #1
	b _0223F478
_0223F474:
	sub r1, #0x7c
	str r3, [r5, r1]
_0223F478:
	mov r3, #0xc1
	lsl r3, r3, #6
	ldr r1, [r5, r3]
	add r0, r3, #4
	str r1, [r5, r0]
	mov r0, #0x16
	str r0, [r5, #8]
	str r4, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r3, [r5, r3]
	ldr r0, [sp, #8]
	lsl r3, r3, #0x10
	ldr r2, [r5, #0x64]
	add r1, r5, #0
	lsr r3, r3, #0x10
	bl ov11_02244C28
	str r0, [r5, #0x6c]
	ldr r0, [sp, #8]
	bl ov11_0225679C
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223F4A8: .word 0x000021E8
_0223F4AC: .word 0x00002DEC
_0223F4B0: .word 0x00002DEE
_0223F4B4: .word 0x0000304C
_0223F4B8: .word 0x000030BC
_0223F4BC: .word 0x00002D4C

	thumb_func_start ov11_0223F4C0
ov11_0223F4C0: ; 0x0223F4C0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0xec
	ldr r2, [r2]
	add r7, r0, #0
	add r3, r4, r2
	ldr r2, _0223F5FC ; =0x000021E8
	ldrb r2, [r3, r2]
	str r2, [r4, #0x64]
	bl ov11_022482A4
	str r0, [r4, #0x6c]
	ldr r0, _0223F600 ; =0x000021B0
	ldr r1, [r4, #0x64]
	add r2, r4, r0
	lsl r0, r1, #4
	add r6, r2, r0
	add r0, r7, #0
	bl ov11_02230270
	cmp r0, #0
	beq _0223F568
	ldr r0, [r4, #0x64]
	asr r0, r0, #1
	add r1, r4, r0
	ldr r0, _0223F604 ; =0x000003D1
	ldrb r2, [r1, r0]
	cmp r2, #4
	bhi _0223F554
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0223F508: ; jump table
	.short _0223F512 - _0223F508 - 2 ; case 0
	.short _0223F516 - _0223F508 - 2 ; case 1
	.short _0223F51A - _0223F508 - 2 ; case 2
	.short _0223F544 - _0223F508 - 2 ; case 3
	.short _0223F552 - _0223F508 - 2 ; case 4
_0223F512:
	ldr r5, _0223F608 ; =0x00000121
	b _0223F554
_0223F516:
	ldr r5, _0223F60C ; =0x0000010B
	b _0223F554
_0223F51A:
	add r0, r0, #2
	ldrb r0, [r1, r0]
	mov r1, #1
	tst r1, r0
	beq _0223F534
	mov r1, #0x3e
	add r2, r0, #0
	tst r2, r1
	beq _0223F534
	mov r0, #6
	add r1, #0xf2
	str r0, [r4, r1]
	b _0223F53E
_0223F534:
	bl LowestFlagNo
	mov r1, #0x13
	lsl r1, r1, #4
	str r0, [r4, r1]
_0223F53E:
	mov r5, #0x43
	lsl r5, r5, #2
	b _0223F554
_0223F544:
	add r0, r0, #2
	ldrb r0, [r1, r0]
	mov r5, #0x13
	lsl r5, r5, #4
	str r0, [r4, r5]
	sub r5, #0x23
	b _0223F554
_0223F552:
	ldr r5, _0223F610 ; =0x0000010E
_0223F554:
	ldr r1, [r4, #0x64]
	mov r0, #1
	bic r1, r0
	ldr r0, _0223F614 ; =0x000003D6
	add r1, r4, r1
	ldrh r1, [r1, r0]
	mov r0, #0x4a
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _0223F5DA
_0223F568:
	ldrb r0, [r6, #2]
	cmp r0, #3
	bhi _0223F5D2
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223F57A: ; jump table
	.short _0223F582 - _0223F57A - 2 ; case 0
	.short _0223F582 - _0223F57A - 2 ; case 1
	.short _0223F598 - _0223F57A - 2 ; case 2
	.short _0223F582 - _0223F57A - 2 ; case 3
_0223F582:
	ldrh r1, [r6]
	ldr r0, _0223F618 ; =0x0000FFC1
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #1
	bhi _0223F594
	mov r5, #0xde
	b _0223F5D2
_0223F594:
	mov r5, #0xdf
	b _0223F5D2
_0223F598:
	add r0, r7, #0
	mov r5, #0xb
	bl ov11_0222FF74
	mov r1, #1
	tst r0, r1
	bne _0223F5D2
	add r0, r7, #0
	bl ov11_0222FF74
	mov r1, #1
	lsl r1, r1, #0xa
	tst r0, r1
	bne _0223F5D2
	add r0, r7, #0
	bl ov11_02230214
	ldrh r1, [r6]
	mov r2, #1
	mov r3, #5
	bl Bag_TakeItem
	add r0, r7, #0
	bl ov11_02230218
	ldrh r1, [r6]
	ldrb r2, [r6, #2]
	bl BagCursor_Battle_SetLastUsedItem
_0223F5D2:
	ldrh r1, [r6]
	mov r0, #0x4a
	lsl r0, r0, #2
	str r1, [r4, r0]
_0223F5DA:
	add r0, r4, #0
	mov r1, #1
	add r2, r5, #0
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x27
	str r0, [r4, #0xc]
	ldr r1, _0223F61C ; =0x0000216C
	mov r0, #2
	ldr r2, [r4, r1]
	lsl r0, r0, #0x1e
	orr r0, r2
	str r0, [r4, r1]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223F5FC: .word 0x000021E8
_0223F600: .word 0x000021B0
_0223F604: .word 0x000003D1
_0223F608: .word 0x00000121
_0223F60C: .word 0x0000010B
_0223F610: .word 0x0000010E
_0223F614: .word 0x000003D6
_0223F618: .word 0x0000FFC1
_0223F61C: .word 0x0000216C

	thumb_func_start ov11_0223F620
ov11_0223F620: ; 0x0223F620
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	mov r2, #9
	bl ov11_022431DC
	add r0, r4, #0
	add r0, #0xec
	ldr r0, [r0]
	ldr r1, _0223F660 ; =0x000021E8
	add r0, r4, r0
	ldrb r0, [r0, r1]
	mov r2, #0
	str r0, [r4, #0x64]
	str r0, [r4, #0x78]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x28
	str r0, [r4, #0xc]
	mov r0, #0x4e
	lsl r0, r0, #2
	str r2, [r4, r0]
	add r0, r1, #0
	sub r0, #0x7c
	ldr r2, [r4, r0]
	mov r0, #2
	lsl r0, r0, #0x1e
	orr r0, r2
	sub r1, #0x7c
	str r0, [r4, r1]
	pop {r4, pc}
	.align 2, 0
_0223F660: .word 0x000021E8

	thumb_func_start ov11_0223F664
ov11_0223F664: ; 0x0223F664
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r1, #0xec
	ldr r1, [r1]
	add r5, r0, #0
	add r2, r4, r1
	ldr r1, _0223F71C ; =0x000021E8
	ldrb r1, [r2, r1]
	str r1, [r4, #0x64]
	bl ov11_02230270
	cmp r0, #0
	beq _0223F6D6
	add r0, r5, #0
	bl ov11_0222FF74
	mov r1, #4
	tst r0, r1
	bne _0223F6D6
	ldr r0, [r4, #0x64]
	mov r2, #0xc0
	add r1, r0, #0
	mul r1, r2
	ldr r0, _0223F720 ; =0x00002DB0
	add r1, r4, r1
	ldr r1, [r1, r0]
	ldr r0, _0223F724 ; =0x0400E000
	tst r0, r1
	beq _0223F6BA
	add r0, r4, #0
	mov r1, #1
	add r2, #0x5e
	bl ov11_022431DC
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x27
	str r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223F6BA:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xe6
	bl ov11_022431DC
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x2a
	str r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223F6D6:
	ldr r2, [r4, #0x64]
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_022470B8
	cmp r0, #0
	beq _0223F700
	add r0, r4, #0
	mov r1, #1
	mov r2, #3
	bl ov11_022431DC
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x2a
	str r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223F700:
	add r0, r4, #0
	mov r1, #1
	mov r2, #8
	bl ov11_022431DC
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x27
	str r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223F71C: .word 0x000021E8
_0223F720: .word 0x00002DB0
_0223F724: .word 0x0400E000

	thumb_func_start ov11_0223F728
ov11_0223F728: ; 0x0223F728
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r2, _0223F76C ; =0x00000113
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	mov r0, #0
	str r0, [r4, #0x64]
	mov r0, #1
	str r0, [r4, #0x6c]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x27
	str r0, [r4, #0xc]
	mov r0, #0x4a
	mov r1, #5
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r5, #0
	bl ov11_02230E00
	sub r1, r0, #1
	add r0, r5, #0
	bl ov11_02230E0C
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0
	bl ov11_02256020
	pop {r3, r4, r5, pc}
	nop
_0223F76C: .word 0x00000113

	thumb_func_start ov11_0223F770
ov11_0223F770: ; 0x0223F770
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xe3
	bl ov11_022431DC
	mov r0, #0
	str r0, [r4, #0x64]
	mov r0, #1
	str r0, [r4, #0x6c]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x27
	str r0, [r4, #0xc]
	bl LCRandom
	mov r1, #0xa
	bl _s32_div_f
	mov r0, #0x4e
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, _0223F7C4 ; =0x0000311C
	ldrb r1, [r4, r0]
	cmp r1, #0xc
	bhs _0223F7AA
	add r1, r1, #1
	strb r1, [r4, r0]
_0223F7AA:
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0223F7C0
	ldr r0, _0223F7C8 ; =0x0000311D
	ldrb r1, [r4, r0]
	cmp r1, #0xc
	bhs _0223F7C0
	add r1, r1, #1
	strb r1, [r4, r0]
_0223F7C0:
	pop {r4, pc}
	nop
_0223F7C4: .word 0x0000311C
_0223F7C8: .word 0x0000311D

	thumb_func_start ov11_0223F7CC
ov11_0223F7CC: ; 0x0223F7CC
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xe4
	bl ov11_022431DC
	mov r0, #0
	str r0, [r4, #0x64]
	mov r0, #1
	str r0, [r4, #0x6c]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x27
	str r0, [r4, #0xc]
	bl LCRandom
	mov r1, #0xa
	bl _s32_div_f
	mov r0, #0x4e
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, _0223F824 ; =0x0000311D
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _0223F806
	sub r1, r1, #1
	strb r1, [r4, r0]
_0223F806:
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _0223F822
	mov r1, #1
	sub r0, #8
	str r1, [r4, r0]
	ldr r0, _0223F828 ; =0x0000311C
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _0223F822
	sub r1, r1, #1
	strb r1, [r4, r0]
_0223F822:
	pop {r4, pc}
	.align 2, 0
_0223F824: .word 0x0000311D
_0223F828: .word 0x0000311C

	thumb_func_start ov11_0223F82C
ov11_0223F82C: ; 0x0223F82C
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xe5
	bl ov11_022431DC
	mov r0, #0
	str r0, [r4, #0x64]
	mov r0, #1
	str r0, [r4, #0x6c]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x27
	str r0, [r4, #0xc]
	pop {r4, pc}

	thumb_func_start ov11_0223F84C
ov11_0223F84C: ; 0x0223F84C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r0, [sp, #0x18]
	add r4, r1, #0
	add r6, r2, #0
	bl ov11_0222FF74
	add r5, r0, #0
	ldr r0, [sp, #0x18]
	mov r1, #0
	bl ov11_022301D4
	add r7, r0, #0
	mov r0, #0x84
	tst r0, r5
	beq _0223F872
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223F872:
	ldr r0, [sp, #0x18]
	ldr r1, [r4, #0x64]
	bl ov11_02230270
	cmp r0, #0
	beq _0223F884
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223F884:
	mov r0, #0x40
	tst r0, r5
	beq _0223F89C
	ldr r0, [sp, #0x18]
	ldr r1, [r4, #0x64]
	bl ov11_02230260
	cmp r0, #4
	bne _0223F89C
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223F89C:
	ldr r0, [sp, #0x18]
	add r1, r4, #0
	bl ov11_0224ADB8
	cmp r0, #1
	bne _0223F8AE
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223F8AE:
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl ov11_0224AD04
	cmp r0, #0
	bne _0223F8C0
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223F8C0:
	add r0, r7, #0
	bl PlayerProfile_CountBadges
	cmp r0, #8
	blt _0223F8D0
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223F8D0:
	add r0, r7, #0
	mov r5, #0xa
	bl PlayerProfile_CountBadges
	cmp r0, #2
	blt _0223F8DE
	mov r5, #0x1e
_0223F8DE:
	add r0, r7, #0
	bl PlayerProfile_CountBadges
	cmp r0, #4
	blt _0223F8EA
	mov r5, #0x32
_0223F8EA:
	add r0, r7, #0
	bl PlayerProfile_CountBadges
	cmp r0, #6
	blt _0223F8F6
	mov r5, #0x46
_0223F8F6:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	add r7, r1, #0
	mul r7, r0
	ldr r0, _0223FAEC ; =0x00002D74
	add r1, r4, r7
	ldrb r0, [r1, r0]
	cmp r0, r5
	bhi _0223F90E
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223F90E:
	bl LCRandom
	lsl r0, r0, #0x18
	ldr r1, _0223FAEC ; =0x00002D74
	add r2, r4, r7
	ldrb r2, [r2, r1]
	lsr r0, r0, #0x18
	add r2, r5, r2
	mul r0, r2
	asr r0, r0, #8
	cmp r0, r5
	bge _0223F92C
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223F92C:
	ldr r0, _0223FAF0 ; =0x00003044
	ldr r0, [r4, r0]
	cmp r0, #0x63
	bne _0223F940
	add r1, #0x3c
	add r0, r4, r1
	ldr r2, [r0, r7]
	ldr r1, _0223FAF4 ; =0xFF7FFFFF
	and r1, r2
	str r1, [r0, r7]
_0223F940:
	ldr r7, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r7
	add r1, r4, r0
	ldr r0, _0223FAF8 ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #7
	tst r0, r1
	beq _0223F968
	ldr r0, _0223FAF0 ; =0x00003044
	ldr r0, [r4, r0]
	cmp r0, #0xad
	beq _0223F95E
	cmp r0, #0xd6
	bne _0223F968
_0223F95E:
	mov r0, #0xfe
	str r0, [r6]
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223F968:
	mov r0, #0xc0
	mul r0, r7
	add r1, r4, r0
	ldr r0, _0223FAEC ; =0x00002D74
	ldrb r0, [r1, r0]
	str r0, [sp, #0x1c]
	bl LCRandom
	ldr r1, [sp, #0x1c]
	lsl r0, r0, #0x18
	add r1, r5, r1
	lsr r0, r0, #0x18
	mul r0, r1
	asr r0, r0, #8
	cmp r0, r5
	bge _0223FA2E
	lsl r0, r7, #1
	add r1, r4, r0
	ldr r0, _0223FAFC ; =0x000030BC
	ldrh r0, [r1, r0]
	bl MaskOfFlagNo
	add r3, r0, #0
	mov r0, #0
	mvn r0, r0
	str r0, [sp]
	ldr r0, [sp, #0x18]
	ldr r2, [r4, #0x64]
	add r1, r4, #0
	bl ov11_02245D38
	add r5, r0, #0
	cmp r5, #0xf
	bne _0223F9B6
	mov r0, #0xff
	str r0, [r6]
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223F9B6:
	bl LCRandom
	mov r1, #3
	add r7, r0, #0
	and r7, r1
	add r0, r7, #0
	bl MaskOfFlagNo
	tst r0, r5
	bne _0223F9B6
	ldr r0, [r4, #0x64]
	ldr r3, _0223FAFC ; =0x000030BC
	lsl r0, r0, #1
	add r0, r4, r0
	strh r7, [r0, r3]
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	lsl r1, r1, #1
	add r1, r4, r1
	ldrh r1, [r1, r3]
	add r0, r4, r0
	lsl r1, r1, #1
	add r1, r0, r1
	ldr r0, _0223FB00 ; =0x00002D4C
	ldrh r1, [r1, r0]
	add r0, r3, #0
	sub r0, #0x7c
	str r1, [r4, r0]
	add r0, r3, #0
	sub r0, #0x7c
	ldr r1, [r4, r0]
	add r0, r3, #0
	sub r0, #0x78
	str r1, [r4, r0]
	mov r0, #1
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	sub r3, #0x7c
	ldr r3, [r4, r3]
	ldr r0, [sp, #0x18]
	lsl r3, r3, #0x10
	ldr r2, [r4, #0x64]
	add r1, r4, #0
	lsr r3, r3, #0x10
	bl ov11_02244C28
	str r0, [r4, #0x6c]
	mov r0, #1
	lsl r0, r0, #8
	str r0, [r6]
	ldr r1, _0223FB04 ; =0x00002184
	mov r0, #1
	ldr r2, [r4, r1]
	add sp, #0x20
	orr r0, r2
	str r0, [r4, r1]
	mov r0, #2
	pop {r3, r4, r5, r6, r7, pc}
_0223FA2E:
	ldr r0, [sp, #0x1c]
	sub r0, r0, r5
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	bl LCRandom
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	cmp r7, r5
	bge _0223FA8E
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r4, r0
	ldr r0, _0223FAF8 ; =0x00002DAC
	ldr r0, [r2, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bne _0223FA8E
	add r0, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x48
	beq _0223FA8E
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl ov11_02246D1C
	cmp r0, #0xf
	beq _0223FA8E
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x66
	beq _0223FA8E
	mov r1, #6
	lsl r1, r1, #6
	mov r0, #0xf
	ldr r2, [r4, r1]
	lsl r0, r0, #8
	tst r0, r2
	bne _0223FA8E
	sub r1, #0x7f
	add sp, #0x20
	str r1, [r6]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223FA8E:
	sub r0, r7, r5
	cmp r0, r5
	bge _0223FAE2
	ldr r1, [r4, #0x64]
	mov r0, #0x46
	str r1, [r4, #0x6c]
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r1, [r4, #0x64]
	mov r3, #0
	str r3, [sp]
	mov r0, #0x28
	str r0, [sp, #4]
	lsl r0, r1, #0x18
	str r3, [sp, #8]
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r2, #1
	ldr r0, [sp, #0x18]
	add r1, r4, #0
	str r2, [sp, #0x14]
	bl ov11_0224B310
	ldr r1, _0223FB08 ; =0x0000215C
	str r0, [r4, r1]
	ldr r1, [r4, r1]
	add r0, r4, #0
	bl ov11_0224BF10
	ldr r1, _0223FB08 ; =0x0000215C
	add sp, #0x20
	str r0, [r4, r1]
	mov r0, #0
	ldr r2, [r4, r1]
	mvn r0, r0
	mul r0, r2
	str r0, [r4, r1]
	ldr r0, _0223FB0C ; =0x00000102
	str r0, [r6]
	mov r0, #3
	pop {r3, r4, r5, r6, r7, pc}
_0223FAE2:
	mov r0, #0xff
	str r0, [r6]
	mov r0, #1
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223FAEC: .word 0x00002D74
_0223FAF0: .word 0x00003044
_0223FAF4: .word 0xFF7FFFFF
_0223FAF8: .word 0x00002DAC
_0223FAFC: .word 0x000030BC
_0223FB00: .word 0x00002D4C
_0223FB04: .word 0x00002184
_0223FB08: .word 0x0000215C
_0223FB0C: .word 0x00000102

	thumb_func_start ov11_0223FB10
ov11_0223FB10: ; 0x0223FB10
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	ldr r3, [r5, #0x64]
	mov r2, #0x1c
	mul r2, r3
	add r6, r5, r2
	mov r2, #0xb5
	lsl r2, r2, #2
	ldr r2, [r6, r2]
	str r0, [sp, #4]
	lsl r2, r2, #0x1f
	mov r4, #1
	lsr r2, r2, #0x1f
	bne _0223FBCA
	ldr r6, [r5, #0x6c]
	cmp r6, #0xff
	beq _0223FBCA
	mov r2, #0xc1
	lsl r2, r2, #6
	ldr r7, [r5, r2]
	ldr r2, _0223FC98 ; =0x0000011E
	cmp r7, r2
	bne _0223FB4E
	mov r2, #0x2e
	str r2, [sp]
	mov r2, #3
	bl ov11_02246870
	add r4, r4, r0
	b _0223FBCA
_0223FB4E:
	lsl r0, r7, #4
	add r1, r5, r0
	ldr r0, _0223FC9C ; =0x000003E6
	ldrh r1, [r1, r0]
	cmp r1, #0x40
	bgt _0223FB78
	bge _0223FB94
	cmp r1, #0x10
	bgt _0223FB72
	bge _0223FBCA
	cmp r1, #8
	bgt _0223FBB8
	cmp r1, #4
	blt _0223FBB8
	beq _0223FBA6
	cmp r1, #8
	beq _0223FB94
	b _0223FBB8
_0223FB72:
	cmp r1, #0x20
	beq _0223FBCA
	b _0223FBB8
_0223FB78:
	add r0, r2, #0
	sub r0, #0x1e
	cmp r1, r0
	bgt _0223FB8C
	sub r2, #0x1e
	cmp r1, r2
	bge _0223FBCA
	cmp r1, #0x80
	beq _0223FBA6
	b _0223FBB8
_0223FB8C:
	add r2, #0xe2
	cmp r1, r2
	beq _0223FBCA
	b _0223FBB8
_0223FB94:
	mov r0, #0x2e
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #9
	bl ov11_02246870
	add r4, r4, r0
	b _0223FBCA
_0223FBA6:
	mov r0, #0x2e
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #3
	bl ov11_02246870
	add r4, r4, r0
	b _0223FBCA
_0223FBB8:
	cmp r3, r6
	beq _0223FBCA
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_02246D1C
	cmp r0, #0x2e
	bne _0223FBCA
	add r4, r4, #1
_0223FBCA:
	mov r0, #0xb5
	lsl r0, r0, #6
	add r2, r5, r0
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	mov r1, #0xc1
	lsl r1, r1, #6
	ldr r1, [r5, r1]
	add r0, r2, r0
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl ov11_022461AC
	add r6, r0, #0
	ldr r1, [r5, #0x64]
	mov r0, #0x75
	lsl r0, r0, #2
	add r0, r5, r0
	lsl r7, r1, #6
	ldr r3, [r0, r7]
	lsl r2, r3, #0x1e
	lsr r2, r2, #0x1f
	bne _0223FC42
	lsl r2, r3, #0x1f
	lsr r2, r2, #0x1f
	bne _0223FC42
	mov r1, #2
	orr r1, r3
	str r1, [r0, r7]
	ldr r0, _0223FCA0 ; =0x00002D6C
	ldr r1, [r5, #0x64]
	add r2, r5, r0
	mov r0, #0xc0
	mul r0, r1
	add r1, r2, r0
	ldrb r0, [r1, r6]
	cmp r0, #0
	beq _0223FC34
	cmp r6, #4
	bge _0223FC34
	cmp r0, r4
	ble _0223FC24
	sub r0, r0, r4
	b _0223FC26
_0223FC24:
	mov r0, #0
_0223FC26:
	strb r0, [r1, r6]
	ldr r0, [sp, #4]
	ldr r2, [r5, #0x64]
	add r1, r5, #0
	bl ov11_02245190
	b _0223FC90
_0223FC34:
	ldr r1, _0223FCA4 ; =0x0000216C
	mov r0, #2
	ldr r2, [r5, r1]
	lsl r0, r0, #8
	orr r0, r2
	str r0, [r5, r1]
	b _0223FC90
_0223FC42:
	mov r2, #0xc0
	add r0, r1, #0
	mul r0, r2
	add r0, r5, r0
	ldr r3, _0223FCA0 ; =0x00002D6C
	add r4, r0, r6
	ldrb r4, [r4, r3]
	cmp r4, #0
	bne _0223FC90
	ldr r4, _0223FCA8 ; =0x0000213C
	mov r7, #2
	ldr r4, [r5, r4]
	lsl r7, r7, #8
	tst r4, r7
	bne _0223FC90
	add r3, #0x44
	ldr r0, [r0, r3]
	lsl r3, r7, #3
	tst r3, r0
	bne _0223FC90
	lsl r2, r2, #4
	tst r0, r2
	bne _0223FC90
	add r0, r1, #0
	bl MaskOfFlagNo
	add r1, r7, #0
	sub r1, #0x80
	ldr r2, [r5, r1]
	lsl r0, r0, #8
	tst r0, r2
	bne _0223FC90
	cmp r6, #4
	bge _0223FC90
	ldr r0, _0223FCA4 ; =0x0000216C
	add r1, #0x80
	ldr r2, [r5, r0]
	orr r1, r2
	str r1, [r5, r0]
_0223FC90:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223FC98: .word 0x0000011E
_0223FC9C: .word 0x000003E6
_0223FCA0: .word 0x00002D6C
_0223FCA4: .word 0x0000216C
_0223FCA8: .word 0x0000213C

	thumb_func_start ov11_0223FCAC
ov11_0223FCAC: ; 0x0223FCAC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x6c]
	mov r4, #0
	cmp r0, #0xff
	bne _0223FCC6
	ldr r1, _0223FD10 ; =0x00003044
	add r0, r5, #0
	ldr r1, [r5, r1]
	bl ov11_02246AF8
	cmp r0, #0
	beq _0223FCF8
_0223FCC6:
	ldr r0, [r5, #0x6c]
	cmp r0, #0xff
	bne _0223FD0C
	ldr r1, _0223FD10 ; =0x00003044
	add r0, r5, #0
	ldr r1, [r5, r1]
	bl ov11_02246AF8
	cmp r0, #1
	bne _0223FD0C
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _0223FD14 ; =0x00002DB0
	ldr r0, [r1, r0]
	mov r1, #1
	lsl r1, r1, #0xc
	tst r0, r1
	bne _0223FCF8
	ldr r0, _0223FD18 ; =0x0000213C
	ldr r2, [r5, r0]
	lsr r0, r1, #3
	tst r0, r2
	beq _0223FD0C
_0223FCF8:
	ldr r2, _0223FD1C ; =0x00000119
	add r0, r5, #0
	mov r1, #1
	bl ov11_022431DC
	mov r0, #0x26
	str r0, [r5, #0xc]
	mov r0, #0x15
	str r0, [r5, #8]
	mov r4, #1
_0223FD0C:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223FD10: .word 0x00003044
_0223FD14: .word 0x00002DB0
_0223FD18: .word 0x0000213C
_0223FD1C: .word 0x00000119

	thumb_func_start ov11_0223FD20
ov11_0223FD20: ; 0x0223FD20
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r1, #0
	ldr r1, _0223FDA0 ; =0x00003044
	ldr r2, [r4, r1]
	lsl r1, r2, #4
	add r5, r4, r1
	ldr r1, _0223FDA4 ; =0x000003E6
	ldrh r3, [r5, r1]
	cmp r3, #0x10
	beq _0223FD54
	cmp r3, #0x20
	beq _0223FD54
	sub r1, r1, #5
	ldrb r1, [r5, r1]
	cmp r1, #0
	beq _0223FD54
	ldr r1, _0223FDA8 ; =0x0000213C
	ldr r3, [r4, r1]
	mov r1, #2
	lsl r1, r1, #0xe
	tst r1, r3
	bne _0223FD54
	mov r1, #0x20
	tst r1, r3
	beq _0223FD58
_0223FD54:
	cmp r2, #0x56
	bne _0223FD98
_0223FD58:
	ldr r1, [r4, #0x64]
	ldr r3, _0223FDAC ; =0x00002144
	str r1, [sp]
	ldr r1, [r4, #0x6c]
	str r1, [sp, #4]
	ldr r1, [r4, r3]
	str r1, [sp, #8]
	add r1, r3, #0
	add r1, #0x28
	add r1, r4, r1
	str r1, [sp, #0xc]
	add r3, #0x1c
	ldr r3, [r4, r3]
	add r1, r4, #0
	bl ov11_02246274
	ldr r1, _0223FDAC ; =0x00002144
	str r0, [r4, r1]
	add r1, #0x28
	ldr r1, [r4, r1]
	mov r0, #8
	tst r0, r1
	beq _0223FD98
	mov r0, #0xd1
	lsl r0, r0, #2
	add r3, r4, r0
	ldr r0, [r4, #0x64]
	lsl r2, r0, #2
	ldr r1, [r3, r2]
	mov r0, #2
	orr r0, r1
	str r0, [r3, r2]
_0223FD98:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_0223FDA0: .word 0x00003044
_0223FDA4: .word 0x000003E6
_0223FDA8: .word 0x0000213C
_0223FDAC: .word 0x00002144

	thumb_func_start ov11_0223FDB0
ov11_0223FDB0: ; 0x0223FDB0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	str r0, [sp, #0x18]
	add r4, r1, #0
	ldr r0, _022400D8 ; =0x00003044
	add r5, r4, #0
	ldr r0, [r4, r0]
	mov r7, #0
	lsl r0, r0, #4
	add r1, r4, r0
	ldr r0, _022400DC ; =0x000003DE
	add r5, #0x50
	ldrh r0, [r1, r0]
	str r0, [sp, #0x1c]
	mov r0, #0xd1
	lsl r0, r0, #2
	add r6, r4, r0
	mov r0, #7
	str r0, [sp, #0x20]
	mov r0, #8
	str r0, [sp, #0x24]
	mov r0, #1
	str r0, [sp, #0x28]
_0223FDDE:
	ldr r0, [r4, #0x50]
	cmp r0, #0x10
	bls _0223FDE6
	b _0224043C
_0223FDE6:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223FDF2: ; jump table
	.short _0223FE14 - _0223FDF2 - 2 ; case 0
	.short _0223FE48 - _0223FDF2 - 2 ; case 1
	.short _0223FF42 - _0223FDF2 - 2 ; case 2
	.short _0223FFA6 - _0223FDF2 - 2 ; case 3
	.short _0223FFCE - _0223FDF2 - 2 ; case 4
	.short _0224000A - _0223FDF2 - 2 ; case 5
	.short _02240050 - _0223FDF2 - 2 ; case 6
	.short _0224008C - _0223FDF2 - 2 ; case 7
	.short _022400D4 - _0223FDF2 - 2 ; case 8
	.short _02240138 - _0223FDF2 - 2 ; case 9
	.short _02240174 - _0223FDF2 - 2 ; case 10
	.short _022401B0 - _0223FDF2 - 2 ; case 11
	.short _0224028C - _0223FDF2 - 2 ; case 12
	.short _022402E8 - _0223FDF2 - 2 ; case 13
	.short _0224034E - _0223FDF2 - 2 ; case 14
	.short _022403FE - _0223FDF2 - 2 ; case 15
	.short _02240436 - _0223FDF2 - 2 ; case 16
_0223FE14:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r4, r0
	ldr r0, _022400E0 ; =0x00002DB0
	ldr r1, [r2, r0]
	ldr r0, _022400E4 ; =0xFDFFFFFF
	and r1, r0
	ldr r0, _022400E0 ; =0x00002DB0
	str r1, [r2, r0]
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r4, r0
	mov r0, #0xb7
	lsl r0, r0, #6
	ldr r1, [r2, r0]
	ldr r0, _022400E8 ; =0xFFFFBFFF
	and r1, r0
	mov r0, #0xb7
	lsl r0, r0, #6
	str r1, [r2, r0]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0224043C
_0223FE48:
	ldr r2, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r2
	add r1, r4, r0
	ldr r0, _022400EC ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #7
	tst r0, r1
	beq _0223FF3A
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r0, #0xf
	lsl r0, r0, #8
	tst r0, r1
	beq _0223FE92
	add r0, r4, #0
	add r1, r2, #0
	bl ov11_02246D1C
	cmp r0, #0x2b
	beq _0223FE92
	mov r0, #0x46
	ldr r1, [r4, #0x64]
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x13
	bl ov11_022431DC
	ldr r0, [r4, #8]
	mov r7, #2
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	b _0223FF3A
_0223FE92:
	ldr r0, _022400D8 ; =0x00003044
	ldr r0, [r4, r0]
	cmp r0, #0xd6
	beq _0223FEA8
	mov r0, #0xc1
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	cmp r0, #0xd6
	bne _0223FEA8
	mov r0, #1
	b _0223FEAA
_0223FEA8:
	mov r0, #0
_0223FEAA:
	cmp r0, #0
	bne _0223FF3A
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x30
	bne _0223FEBE
	mov r3, #2
	b _0223FEC0
_0223FEBE:
	mov r3, #1
_0223FEC0:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r4, r0
	ldr r0, _022400EC ; =0x00002DAC
	ldr r1, [r2, r0]
	mov r0, #7
	and r0, r1
	cmp r0, r3
	ldr r0, _022400EC ; =0x00002DAC
	bhs _0223FEDE
	ldr r1, [r2, r0]
	ldr r0, [sp, #0x20]
	bic r1, r0
	b _0223FEE2
_0223FEDE:
	ldr r0, [r2, r0]
	sub r1, r0, r3
_0223FEE2:
	ldr r0, _022400EC ; =0x00002DAC
	str r1, [r2, r0]
	ldr r2, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r2
	add r1, r4, r0
	ldr r0, _022400EC ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #7
	tst r0, r1
	beq _0223FF20
	ldr r0, _022400D8 ; =0x00003044
	ldr r0, [r4, r0]
	cmp r0, #0xad
	beq _0223FF3A
	mov r0, #0xc1
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	cmp r0, #0xd6
	beq _0223FF3A
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x14
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x26
	str r0, [r4, #0xc]
	mov r7, #2
	b _0223FF3A
_0223FF20:
	mov r0, #0x46
	lsl r0, r0, #2
	str r2, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x13
	bl ov11_022431DC
	ldr r0, [r4, #8]
	mov r7, #2
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
_0223FF3A:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0224043C
_0223FF42:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _022400EC ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #0x20
	tst r0, r1
	beq _0223FF9E
	bl LCRandom
	mov r1, #5
	bl _s32_div_f
	cmp r1, #0
	beq _0223FF82
	ldr r0, [sp, #0x1c]
	cmp r0, #0x7d
	beq _0223FF9E
	cmp r0, #0xfd
	beq _0223FF9E
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x1c
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x26
	str r0, [r4, #0xc]
	mov r7, #1
	b _0223FF9E
_0223FF82:
	mov r0, #0x46
	ldr r1, [r4, #0x64]
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x1d
	bl ov11_022431DC
	ldr r0, [r4, #8]
	mov r7, #2
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
_0223FF9E:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0224043C
_0223FFA6:
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl ov11_02247190
	cmp r0, #1
	bne _0223FFC6
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xbf
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x26
	str r0, [r4, #0xc]
	mov r7, #1
_0223FFC6:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0224043C
_0223FFCE:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r4, r0
	ldr r0, _022400E0 ; =0x00002DB0
	ldr r1, [r2, r0]
	mov r0, #1
	lsl r0, r0, #0x16
	tst r0, r1
	beq _02240002
	ldr r0, _022400E0 ; =0x00002DB0
	ldr r1, [r2, r0]
	ldr r0, _022400F0 ; =0xFFBFFFFF
	and r1, r0
	ldr r0, _022400E0 ; =0x00002DB0
	str r1, [r2, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x41
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x26
	str r0, [r4, #0xc]
	mov r7, #1
_02240002:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0224043C
_0224000A:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r4, r0
	ldr r0, _022400E0 ; =0x00002DB0
	ldr r1, [r2, r0]
	mov r0, #8
	tst r0, r1
	beq _02240048
	ldr r0, _022400E0 ; =0x00002DB0
	ldr r1, [sp, #0x24]
	ldr r0, [r2, r0]
	bic r0, r1
	ldr r1, _022400E0 ; =0x00002DB0
	str r0, [r2, r1]
	ldr r0, [r4, #0x64]
	mov r1, #0x40
	lsl r0, r0, #2
	ldr r2, [r6, r0]
	orr r1, r2
	str r1, [r6, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xf
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x26
	str r0, [r4, #0xc]
	mov r7, #1
_02240048:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0224043C
_02240050:
	mov r0, #0xc1
	lsl r0, r0, #6
	ldr r3, [r4, r0]
	ldr r2, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r2
	add r1, r4, r0
	ldr r0, _022400F4 ; =0x00002DE8
	ldrh r0, [r1, r0]
	cmp r3, r0
	bne _02240084
	lsl r0, r2, #2
	ldr r2, [r6, r0]
	mov r1, #0x10
	orr r1, r2
	str r1, [r6, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x47
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x26
	str r0, [r4, #0xc]
	mov r7, #1
_02240084:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0224043C
_0224008C:
	ldr r2, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r2
	add r1, r4, r0
	ldr r0, _022400F8 ; =0x00002DC8
	ldr r0, [r1, r0]
	lsl r0, r0, #0x15
	lsr r0, r0, #0x1d
	beq _022400CC
	ldr r0, _022400D8 ; =0x00003044
	ldr r0, [r4, r0]
	lsl r0, r0, #4
	add r1, r4, r0
	ldr r0, _022400FC ; =0x000003E1
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _022400CC
	lsl r0, r2, #2
	ldr r2, [r6, r0]
	mov r1, #0x20
	orr r1, r2
	str r1, [r6, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x85
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x26
	str r0, [r4, #0xc]
	mov r7, #1
_022400CC:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0224043C
_022400D4:
	ldr r3, _022400D8 ; =0x00003044
	b _02240100
	.align 2, 0
_022400D8: .word 0x00003044
_022400DC: .word 0x000003DE
_022400E0: .word 0x00002DB0
_022400E4: .word 0xFDFFFFFF
_022400E8: .word 0xFFFFBFFF
_022400EC: .word 0x00002DAC
_022400F0: .word 0xFFBFFFFF
_022400F4: .word 0x00002DE8
_022400F8: .word 0x00002DC8
_022400FC: .word 0x000003E1
_02240100:
	ldr r0, [sp, #0x18]
	ldr r2, [r4, #0x64]
	ldr r3, [r4, r3]
	add r1, r4, #0
	bl ov11_022471C4
	cmp r0, #0
	beq _02240130
	ldr r0, [r4, #0x64]
	mov r1, #4
	lsl r0, r0, #2
	ldr r2, [r6, r0]
	orr r1, r2
	str r1, [r6, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x90
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x26
	str r0, [r4, #0xc]
	mov r7, #1
_02240130:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0224043C
_02240138:
	ldr r3, _0224047C ; =0x00003044
	ldr r0, [sp, #0x18]
	ldr r2, [r4, #0x64]
	ldr r3, [r4, r3]
	add r1, r4, #0
	bl ov11_02247314
	cmp r0, #0
	beq _0224016C
	ldr r0, [r4, #0x64]
	mov r1, #1
	lsl r0, r0, #2
	ldr r2, [r6, r0]
	lsl r1, r1, #8
	orr r1, r2
	str r1, [r6, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x9d
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x26
	str r0, [r4, #0xc]
	mov r7, #1
_0224016C:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0224043C
_02240174:
	ldr r3, _0224047C ; =0x00003044
	ldr r0, [sp, #0x18]
	ldr r2, [r4, #0x64]
	ldr r3, [r4, r3]
	add r1, r4, #0
	bl ov11_02247348
	cmp r0, #0
	beq _022401A8
	ldr r0, [r4, #0x64]
	mov r1, #2
	lsl r0, r0, #2
	ldr r2, [r6, r0]
	lsl r1, r1, #8
	orr r1, r2
	str r1, [r6, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xae
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x26
	str r0, [r4, #0xc]
	mov r7, #1
_022401A8:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0224043C
_022401B0:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r4, r0
	ldr r0, _02240480 ; =0x00002DB0
	ldr r1, [r2, r0]
	mov r0, #7
	tst r0, r1
	bne _022401CA
	b _0224043C
_022401CA:
	ldr r0, _02240480 ; =0x00002DB0
	ldr r0, [r2, r0]
	sub r1, r0, #1
	ldr r0, _02240480 ; =0x00002DB0
	str r1, [r2, r0]
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _02240480 ; =0x00002DB0
	ldr r1, [r1, r0]
	mov r0, #7
	tst r0, r1
	beq _02240276
	bl LCRandom
	mov r1, #1
	tst r0, r1
	beq _02240204
	add r0, r4, #0
	mov r2, #0x26
	bl ov11_022431DC
	ldr r0, [r4, #8]
	mov r7, #2
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	b _0224043C
_02240204:
	ldr r0, [r4, #0x64]
	mov r1, #0x80
	lsl r0, r0, #2
	ldr r2, [r6, r0]
	mov r3, #0
	orr r1, r2
	str r1, [r6, r0]
	ldr r1, [r4, #0x64]
	mov r0, #0x46
	str r1, [r4, #0x6c]
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, [r4, #0x64]
	mov r1, #0
	str r1, [sp]
	mov r1, #0x28
	str r1, [sp, #4]
	mov r1, #0
	lsl r0, r0, #0x18
	str r1, [sp, #8]
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x18]
	add r1, r4, #0
	mov r2, #0xa5
	bl ov11_0224B310
	ldr r1, _02240484 ; =0x0000215C
	str r0, [r4, r1]
	ldr r1, [r4, r1]
	add r0, r4, #0
	bl ov11_0224BF10
	ldr r1, _02240484 ; =0x0000215C
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r1, [r4, r0]
	mov r0, #0
	add r2, r1, #0
	mvn r0, r0
	mul r2, r0
	ldr r0, _02240484 ; =0x0000215C
	mov r1, #1
	str r2, [r4, r0]
	add r0, r4, #0
	mov r2, #0x27
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x21
	str r0, [r4, #0xc]
	mov r7, #1
	b _0224043C
_02240276:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x28
	bl ov11_022431DC
	ldr r0, [r4, #8]
	mov r7, #2
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	b _0224043C
_0224028C:
	ldr r2, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r2
	add r1, r4, r0
	ldr r0, _02240488 ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #0x40
	tst r0, r1
	beq _022402E0
	add r0, r4, #0
	add r1, r2, #0
	bl ov11_02246D1C
	cmp r0, #0x62
	beq _022402E0
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r2, r0, #0x1e
	sub r2, r2, r1
	mov r0, #0x1e
	ror r2, r0
	add r0, r1, r2
	bne _022402E0
	ldr r0, [r4, #0x64]
	ldr r2, [sp, #0x28]
	lsl r1, r0, #2
	ldr r0, [r6, r1]
	bic r0, r2
	mov r2, #1
	orr r0, r2
	str r0, [r6, r1]
	add r1, r2, #0
	add r0, r4, #0
	mov r2, #0x20
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x26
	str r0, [r4, #0xc]
	mov r7, #1
_022402E0:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0224043C
_022402E8:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _02240480 ; =0x00002DB0
	ldr r1, [r1, r0]
	mov r0, #0xf
	lsl r0, r0, #0x10
	and r0, r1
	beq _02240346
	lsr r0, r0, #0x10
	bl LowestFlagNo
	mov r1, #0x46
	lsl r1, r1, #2
	str r0, [r4, r1]
	bl LCRandom
	mov r1, #1
	tst r0, r1
	beq _02240326
	add r0, r4, #0
	mov r2, #0x6b
	bl ov11_022431DC
	ldr r0, [r4, #8]
	mov r7, #2
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	b _02240346
_02240326:
	ldr r0, [r4, #0x64]
	mov r1, #8
	lsl r0, r0, #2
	ldr r2, [r6, r0]
	orr r1, r2
	str r1, [r6, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x6c
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x26
	str r0, [r4, #0xc]
	mov r7, #1
_02240346:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0224043C
_0224034E:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r4, r0
	ldr r0, _02240480 ; =0x00002DB0
	ldr r1, [r2, r0]
	mov r0, #3
	lsl r0, r0, #8
	tst r0, r1
	beq _0224043C
	ldr r0, _02240480 ; =0x00002DB0
	ldr r1, [r2, r0]
	mov r0, #1
	lsl r0, r0, #8
	sub r1, r1, r0
	ldr r0, _02240480 ; =0x00002DB0
	str r1, [r2, r0]
	ldr r0, [r4, #0x64]
	mov r1, #0xc0
	mul r1, r0
	add r2, r4, r1
	ldr r1, _02240480 ; =0x00002DB0
	ldr r2, [r2, r1]
	mov r1, #3
	lsl r1, r1, #8
	tst r1, r2
	bne _022403E8
	lsl r0, r0, #2
	add r1, r4, r0
	ldr r0, _0224048C ; =0x000030E4
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _022403E8
	lsl r1, r0, #1
	ldr r0, _02240490 ; =0x00002144
	str r1, [r4, r0]
	ldr r3, [r4, #0x64]
	lsl r0, r3, #2
	add r1, r4, r0
	ldr r0, _02240494 ; =0x000030F4
	ldr r2, [r1, r0]
	mov r0, #0xc0
	mul r0, r2
	add r1, r4, r0
	ldr r0, _02240498 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _022403B8
	str r2, [r4, #0x6c]
	b _022403E8
_022403B8:
	ldr r0, [sp, #0x18]
	add r1, r4, #0
	add r2, r3, #0
	bl ov11_022482A4
	mov r1, #0xc0
	mul r1, r0
	str r0, [r4, #0x6c]
	ldr r0, _02240498 ; =0x00002D8C
	add r1, r4, r1
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _022403E8
	ldr r2, _0224049C ; =0x0000011A
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	mov r0, #0x26
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r7, #2
	b _0224043C
_022403E8:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x24
	bl ov11_022431DC
	ldr r0, [r4, #8]
	mov r7, #2
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	b _0224043C
_022403FE:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _02240488 ; =0x00002DAC
	ldr r1, [r1, r0]
	mov r0, #0x20
	tst r0, r1
	beq _0224042E
	ldr r0, [sp, #0x1c]
	cmp r0, #0x7d
	beq _0224041A
	cmp r0, #0xfd
	bne _0224042E
_0224041A:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x1e
	bl ov11_022431DC
	ldr r0, [r4, #8]
	mov r7, #2
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
_0224042E:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0224043C
_02240436:
	mov r0, #0
	str r0, [r4, #0x50]
	mov r7, #3
_0224043C:
	cmp r7, #0
	bne _02240442
	b _0223FDDE
_02240442:
	ldr r0, [sp, #0x18]
	ldr r2, [r4, #0x64]
	add r1, r4, #0
	bl ov11_02245190
	cmp r7, #1
	bne _0224046A
	ldr r1, _022404A0 ; =0x0000213C
	mov r0, #2
	ldr r2, [r4, r1]
	orr r0, r2
	str r0, [r4, r1]
	add r0, r1, #0
	add r0, #0x30
	ldr r2, [r4, r0]
	mov r0, #2
	lsl r0, r0, #0x1e
	orr r0, r2
	add r1, #0x30
	str r0, [r4, r1]
_0224046A:
	cmp r7, #3
	beq _02240474
	add sp, #0x2c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02240474:
	mov r0, #0
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_0224047C: .word 0x00003044
_02240480: .word 0x00002DB0
_02240484: .word 0x0000215C
_02240488: .word 0x00002DAC
_0224048C: .word 0x000030E4
_02240490: .word 0x00002144
_02240494: .word 0x000030F4
_02240498: .word 0x00002D8C
_0224049C: .word 0x0000011A
_022404A0: .word 0x0000213C

	thumb_func_start ov11_022404A4
ov11_022404A4: ; 0x022404A4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r6, r5, #0
	ldr r7, _02240514 ; =0x0000216C
	mov r4, #0
	add r6, #0x54
_022404B0:
	ldr r0, [r5, #0x54]
	cmp r0, #0
	beq _022404BC
	cmp r0, #1
	beq _022404FC
	b _02240502
_022404BC:
	ldr r1, [r5, #0x64]
	ldr r2, [r5, #0x6c]
	add r0, r5, #0
	bl ov11_02247418
	add r2, r0, #0
	beq _022404D4
	ldr r0, _02240514 ; =0x0000216C
	ldr r1, [r5, r0]
	ldr r0, _02240518 ; =0x001FD849
	tst r0, r1
	beq _022404D8
_022404D4:
	cmp r2, #0xb5
	bne _022404F4
_022404D8:
	add r0, r5, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r5, #8]
	mov r4, #1
	str r0, [r5, #0xc]
	mov r0, #0x15
	str r0, [r5, #8]
	mov r0, #2
	ldr r1, [r5, r7]
	lsl r0, r0, #0x1e
	orr r0, r1
	str r0, [r5, r7]
_022404F4:
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _02240502
_022404FC:
	mov r0, #0
	str r0, [r5, #0x54]
	mov r4, #2
_02240502:
	cmp r4, #0
	beq _022404B0
	cmp r4, #2
	beq _0224050E
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0224050E:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02240514: .word 0x0000216C
_02240518: .word 0x001FD849

	thumb_func_start ov11_0224051C
ov11_0224051C: ; 0x0224051C
	push {r4, lr}
	add r4, r1, #0
	ldr r2, _02240538 ; =0x00000116
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	pop {r4, pc}
	nop
_02240538: .word 0x00000116

	thumb_func_start ov11_0224053C
ov11_0224053C: ; 0x0224053C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r0, [sp, #4]
	add r5, r1, #0
	add r6, r2, #0
	str r3, [sp, #8]
	bl ov11_0222FF74
	mov r1, #1
	lsl r1, r1, #0xa
	tst r0, r1
	beq _0224055A
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0224055A:
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_02246D1C
	ldr r0, [sp, #0x38]
	ldr r2, _02240868 ; =0x00002D5E
	lsl r0, r0, #4
	str r0, [sp, #0x10]
	add r1, r5, r0
	mov r0, #0x3e
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	add r1, r6, #0
	str r0, [sp, #0x18]
	mov r0, #0xc0
	mul r1, r0
	str r1, [sp, #0xc]
	add r1, r5, r1
	ldrsb r1, [r1, r2]
	sub r1, r1, #6
	lsl r1, r1, #0x18
	asr r7, r1, #0x18
	ldr r1, [sp, #8]
	mul r0, r1
	str r0, [sp, #0x14]
	add r1, r5, r0
	add r0, r2, #1
	ldrsb r1, [r1, r0]
	mov r0, #6
	sub r0, r0, r1
	lsl r0, r0, #0x18
	asr r4, r0, #0x18
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_02246D1C
	cmp r0, #0x56
	bne _022405AA
	lsl r0, r7, #0x19
	asr r7, r0, #0x18
_022405AA:
	ldr r2, [sp, #8]
	add r0, r5, #0
	add r1, r6, #0
	mov r3, #0x56
	bl ov11_02246D84
	cmp r0, #1
	bne _022405BE
	lsl r0, r4, #0x19
	asr r4, r0, #0x18
_022405BE:
	ldr r2, [sp, #8]
	add r0, r5, #0
	add r1, r6, #0
	mov r3, #0x6d
	bl ov11_02246D84
	cmp r0, #1
	bne _022405D0
	mov r7, #0
_022405D0:
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_02246D1C
	cmp r0, #0x6d
	bne _022405DE
	mov r4, #0
_022405DE:
	ldr r0, _0224086C ; =0x00002DB0
	ldr r1, [sp, #0x14]
	add r2, r5, r0
	str r2, [sp, #0x1c]
	ldr r1, [r2, r1]
	mov r2, #2
	lsl r2, r2, #0x1c
	tst r1, r2
	bne _022405FE
	ldr r1, [sp, #0x14]
	add r0, #0x10
	add r1, r5, r1
	ldr r1, [r1, r0]
	lsr r0, r2, #7
	tst r0, r1
	beq _02240604
_022405FE:
	cmp r4, #0
	bge _02240604
	mov r4, #0
_02240604:
	add r0, r4, #6
	add r0, r0, r7
	lsl r0, r0, #0x18
	asr r7, r0, #0x18
	bpl _02240610
	mov r7, #0
_02240610:
	cmp r7, #0xc
	ble _02240616
	mov r7, #0xc
_02240616:
	ldr r0, _02240870 ; =0x000003E3
	add r1, r5, r0
	ldr r0, [sp, #0x10]
	ldrb r4, [r1, r0]
	cmp r4, #0
	bne _02240628
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02240628:
	ldr r0, _02240874 ; =0x0000213C
	mov r1, #0x20
	ldr r0, [r5, r0]
	add r2, r0, #0
	tst r2, r1
	beq _0224063A
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0224063A:
	lsl r1, r1, #5
	tst r0, r1
	beq _02240646
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02240646:
	mov r0, #0xd
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl ov11_02246870
	cmp r0, #0
	bne _02240688
	mov r0, #0x4c
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl ov11_02246870
	cmp r0, #0
	bne _02240688
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #0x30
	tst r0, r1
	beq _02240688
	ldr r0, [sp, #0x10]
	add r1, r5, r0
	ldr r0, _02240878 ; =0x000003DE
	ldrh r0, [r1, r0]
	cmp r0, #0x98
	bne _02240688
	mov r4, #0x32
_02240688:
	ldr r0, _0224087C ; =ov11_0225E178
	lsl r1, r7, #1
	ldrb r0, [r0, r1]
	ldr r2, _02240880 ; =ov11_0225E179
	ldrb r1, [r2, r1]
	mul r0, r4
	bl _u32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_02246D1C
	cmp r0, #0xe
	bne _022406B6
	mov r0, #0x82
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_022406B6:
	mov r0, #0xd
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl ov11_02246870
	cmp r0, #0
	bne _0224074E
	mov r0, #0x4c
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl ov11_02246870
	cmp r0, #0
	bne _0224074E
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #0xc
	tst r0, r1
	beq _02240708
	ldr r2, [sp, #8]
	add r0, r5, #0
	add r1, r6, #0
	mov r3, #8
	bl ov11_02246D84
	cmp r0, #1
	bne _02240708
	mov r0, #0x50
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_02240708:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #0xc0
	tst r0, r1
	beq _02240732
	ldr r2, [sp, #8]
	add r0, r5, #0
	add r1, r6, #0
	mov r3, #0x51
	bl ov11_02246D84
	cmp r0, #1
	bne _02240732
	mov r0, #0x50
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_02240732:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #2
	lsl r0, r0, #0xe
	tst r0, r1
	beq _0224074E
	mov r0, #6
	mul r0, r4
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0224074E:
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_02246D1C
	cmp r0, #0x37
	bne _0224076E
	ldr r0, [sp, #0x18]
	cmp r0, #0
	bne _0224076E
	mov r0, #0x50
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0224076E:
	ldr r2, [sp, #8]
	add r0, r5, #0
	add r1, r6, #0
	mov r3, #0x4d
	bl ov11_02246D84
	cmp r0, #1
	bne _02240798
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x14]
	ldr r1, [r1, r0]
	mov r0, #7
	tst r0, r1
	beq _02240798
	mov r0, #0x32
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_02240798:
	ldr r1, [sp, #8]
	add r0, r5, #0
	bl ov11_02249D90
	add r7, r0, #0
	ldr r1, [sp, #8]
	add r0, r5, #0
	mov r2, #0
	bl ov11_02249DA4
	cmp r7, #0x2f
	bne _022407BE
	mov r1, #0x64
	sub r0, r1, r0
	mul r0, r4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_022407BE:
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_02249D90
	add r7, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0
	bl ov11_02249DA4
	add r6, r0, #0
	cmp r7, #0x5c
	bne _022407E6
	add r0, #0x64
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_022407E6:
	cmp r7, #0x67
	bne _02240806
	ldr r1, [sp, #8]
	add r0, r5, #0
	bl ov11_02249B7C
	cmp r0, #1
	bne _02240806
	add r6, #0x64
	add r0, r4, #0
	mul r0, r6
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_02240806:
	ldr r0, _02240884 ; =0x00002DCC
	ldr r1, [sp, #0xc]
	add r0, r5, r0
	ldr r2, [r0, r1]
	lsl r1, r2, #4
	lsr r1, r1, #0x1f
	beq _0224082A
	ldr r1, _02240888 ; =0xF7FFFFFF
	and r2, r1
	ldr r1, [sp, #0xc]
	str r2, [r0, r1]
	mov r0, #0x78
	mul r0, r4
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_0224082A:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #7
	lsl r0, r0, #0xc
	tst r0, r1
	beq _02240846
	mov r0, #0xa
	mul r0, r4
	mov r1, #6
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_02240846:
	bl LCRandom
	mov r1, #0x64
	bl _s32_div_f
	add r0, r1, #1
	cmp r0, r4
	ble _02240860
	ldr r1, _0224088C ; =0x0000216C
	mov r0, #1
	ldr r2, [r5, r1]
	orr r0, r2
	str r0, [r5, r1]
_02240860:
	mov r0, #0
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02240868: .word 0x00002D5E
_0224086C: .word 0x00002DB0
_02240870: .word 0x000003E3
_02240874: .word 0x0000213C
_02240878: .word 0x000003DE
_0224087C: .word ov11_0225E178
_02240880: .word ov11_0225E179
_02240884: .word 0x00002DCC
_02240888: .word 0xF7FFFFFF
_0224088C: .word 0x0000216C

	thumb_func_start ov11_02240890
ov11_02240890: ; 0x02240890
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp, #4]
	add r5, r1, #0
	ldr r0, _02240A54 ; =0x0000213C
	add r6, r3, #0
	ldr r3, [r5, r0]
	mov r1, #0x20
	add r7, r2, #0
	ldr r4, [sp, #0x20]
	tst r1, r3
	beq _022408AE
	add sp, #8
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_022408AE:
	lsl r1, r6, #6
	add r3, r5, r1
	mov r1, #0x75
	lsl r1, r1, #2
	ldr r1, [r3, r1]
	lsl r1, r1, #0x1d
	lsr r1, r1, #0x1f
	beq _0224091C
	lsl r1, r4, #4
	add r3, r5, r1
	ldr r1, _02240A58 ; =0x000003E9
	ldrb r3, [r3, r1]
	mov r1, #2
	tst r1, r3
	beq _0224091C
	add r0, #0x30
	ldr r1, [r5, r0]
	ldr r0, _02240A5C ; =0x801FDA49
	tst r0, r1
	bne _0224091C
	cmp r4, #0xae
	bne _022408E8
	lsl r1, r4, #0x10
	add r0, r5, #0
	lsr r1, r1, #0x10
	bl ov11_02246C20
	cmp r0, #1
	bne _0224091C
_022408E8:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02246AF8
	cmp r0, #0
	beq _02240900
	ldr r0, _02240A54 ; =0x0000213C
	ldr r1, [r5, r0]
	mov r0, #2
	lsl r0, r0, #8
	tst r0, r1
	beq _0224091C
_02240900:
	ldr r0, [sp, #4]
	add r1, r5, #0
	add r2, r7, #0
	bl ov11_022451F0
	ldr r1, _02240A60 ; =0x0000216C
	mov r0, #2
	ldr r2, [r5, r1]
	lsl r0, r0, #0xe
	orr r0, r2
	str r0, [r5, r1]
	add sp, #8
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0224091C:
	ldr r0, _02240A54 ; =0x0000213C
	ldr r1, [r5, r0]
	mov r0, #1
	lsl r0, r0, #0xa
	tst r0, r1
	bne _0224096E
	mov r0, #0xc0
	mul r0, r6
	add r3, r5, r0
	mov r0, #0xb7
	lsl r0, r0, #6
	ldr r2, [r3, r0]
	mov r1, #0x18
	tst r1, r2
	beq _02240946
	add r0, #0xc
	ldr r0, [r3, r0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1e
	cmp r7, r0
	beq _0224095E
_02240946:
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl ov11_02246D1C
	cmp r0, #0x63
	beq _0224095E
	ldr r1, [r5, #0x6c]
	add r0, r5, #0
	bl ov11_02246D1C
	cmp r0, #0x63
	bne _0224096E
_0224095E:
	ldr r1, _02240A60 ; =0x0000216C
	mov r0, #1
	ldr r2, [r5, r1]
	add sp, #8
	bic r2, r0
	str r2, [r5, r1]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0224096E:
	mov r0, #0xd
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl ov11_02246870
	cmp r0, #0
	bne _022409DC
	mov r0, #0x4c
	str r0, [sp]
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl ov11_02246870
	cmp r0, #0
	bne _022409DC
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #3
	tst r0, r1
	beq _022409B8
	lsl r0, r4, #4
	add r1, r5, r0
	ldr r0, _02240A64 ; =0x000003DE
	ldrh r0, [r1, r0]
	cmp r0, #0x98
	bne _022409B8
	ldr r1, _02240A60 ; =0x0000216C
	mov r0, #1
	ldr r2, [r5, r1]
	bic r2, r0
	str r2, [r5, r1]
_022409B8:
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #0xc0
	tst r0, r1
	beq _022409DC
	lsl r0, r4, #4
	add r2, r5, r0
	ldr r0, _02240A64 ; =0x000003DE
	add r1, #0x44
	ldrh r0, [r2, r0]
	cmp r0, r1
	bne _022409DC
	ldr r1, _02240A60 ; =0x0000216C
	mov r0, #1
	ldr r2, [r5, r1]
	bic r2, r0
	str r2, [r5, r1]
_022409DC:
	ldr r1, _02240A60 ; =0x0000216C
	mov r2, #1
	ldr r0, [r5, r1]
	lsl r2, r2, #0xa
	tst r0, r2
	bne _02240A4C
	ldr r0, _02240A68 ; =0x00003044
	sub r2, #0x1a
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r0, r5, r0
	ldrh r0, [r0, r2]
	cmp r0, #0x80
	beq _02240A4C
	sub r1, #0x30
	ldr r0, [r5, r1]
	mov r1, #4
	tst r1, r0
	bne _02240A14
	mov r1, #0xc0
	mul r1, r6
	add r2, r5, r1
	mov r1, #0xb7
	lsl r1, r1, #6
	ldr r2, [r2, r1]
	mov r1, #0x40
	tst r1, r2
	bne _02240A40
_02240A14:
	mov r1, #0xc0
	mul r1, r6
	add r2, r5, r1
	mov r1, #0xb7
	lsl r1, r1, #6
	ldr r1, [r2, r1]
	mov r2, #2
	lsl r2, r2, #0x1c
	tst r2, r1
	bne _02240A40
	mov r2, #8
	tst r2, r0
	bne _02240A34
	mov r2, #0x80
	tst r2, r1
	bne _02240A40
_02240A34:
	mov r2, #0x10
	tst r0, r2
	bne _02240A4C
	lsl r0, r2, #0xe
	tst r0, r1
	beq _02240A4C
_02240A40:
	ldr r1, _02240A60 ; =0x0000216C
	mov r0, #1
	ldr r2, [r5, r1]
	lsl r0, r0, #0x10
	orr r0, r2
	str r0, [r5, r1]
_02240A4C:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02240A54: .word 0x0000213C
_02240A58: .word 0x000003E9
_02240A5C: .word 0x801FDA49
_02240A60: .word 0x0000216C
_02240A64: .word 0x000003DE
_02240A68: .word 0x00003044

	thumb_func_start ov11_02240A6C
ov11_02240A6C: ; 0x02240A6C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	bl ov11_0222FF84
	add r2, r0, #0
	ldr r0, [r4, #0x6c]
	cmp r0, #0xff
	bne _02240A80
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02240A80:
	ldr r6, _02240BBC ; =0x0000216C
	ldr r1, _02240BC0 ; =0x801FDA49
	ldr r3, [r4, r6]
	add r7, r3, #0
	and r7, r1
	bne _02240B12
	mov r1, #0x75
	lsl r1, r1, #2
	lsl r0, r0, #6
	add r5, r4, r1
	ldr r3, [r5, r0]
	mov ip, r0
	lsl r0, r3, #0x1b
	lsr r0, r0, #0x1f
	beq _02240B12
	ldr r0, _02240BC4 ; =0x00003044
	ldr r0, [r4, r0]
	lsl r0, r0, #4
	add r1, r4, r0
	ldr r0, _02240BC8 ; =0x000003E9
	ldrb r0, [r1, r0]
	mov r1, #4
	tst r0, r1
	beq _02240B12
	mov r0, #0x10
	bic r3, r0
	mov r0, ip
	str r3, [r5, r0]
	ldr r2, [r4, #0x64]
	mov r0, #0
	lsl r2, r2, #1
	add r3, r4, r2
	ldr r2, _02240BC4 ; =0x00003044
	add r2, #0x18
	strh r0, [r3, r2]
	ldr r2, [r4, #0x64]
	ldr r0, _02240BC4 ; =0x00003044
	lsl r2, r2, #1
	sub r0, r0, #4
	add r3, r4, r2
	ldr r2, _02240BC4 ; =0x00003044
	ldr r0, [r4, r0]
	add r2, #0x38
	strh r0, [r3, r2]
	ldr r0, _02240BC4 ; =0x00003044
	sub r0, r0, #4
	ldr r2, [r4, r0]
	ldr r0, _02240BC4 ; =0x00003044
	add r0, r0, #4
	str r2, [r4, r0]
	add r0, r6, #0
	sub r0, #0x30
	ldr r2, [r4, r0]
	lsl r0, r1, #0x12
	orr r0, r2
	sub r6, #0x30
	str r0, [r4, r6]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x8b
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	ldr r1, [r4, #0x6c]
	ldr r2, [r4, #0x64]
	add r0, r4, #0
	bl ov11_0224C438
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02240B12:
	mov r1, #0
	cmp r2, #0
	ble _02240BB8
	mov r0, #0x75
	lsl r0, r0, #2
	add r0, r4, r0
_02240B1E:
	ldr r3, _02240BCC ; =0x000021EC
	add r5, r4, r1
	ldrb r5, [r5, r3]
	cmp r7, #0
	bne _02240BB2
	lsl r3, r5, #6
	str r3, [sp]
	ldr r3, [r0, r3]
	lsl r3, r3, #0x1a
	lsr r3, r3, #0x1f
	beq _02240BB2
	ldr r3, _02240BC4 ; =0x00003044
	ldr r3, [r4, r3]
	lsl r3, r3, #4
	add r6, r4, r3
	ldr r3, _02240BC8 ; =0x000003E9
	ldrb r6, [r6, r3]
	mov r3, #8
	tst r3, r6
	beq _02240BB2
	mov r1, #0x46
	lsl r1, r1, #2
	str r5, [r4, r1]
	ldr r1, [sp]
	mov r7, #1
	ldr r2, [r0, r1]
	mov r1, #0x20
	bic r2, r1
	ldr r1, [sp]
	lsl r7, r7, #0x14
	str r2, [r0, r1]
	ldr r2, _02240BD0 ; =0x0000213C
	ldr r0, [r4, r2]
	tst r0, r7
	bne _02240B92
	ldr r1, [r4, #0x64]
	mov r0, #0
	lsl r1, r1, #1
	add r3, r4, r1
	ldr r1, _02240BD4 ; =0x0000305C
	strh r0, [r3, r1]
	add r0, r1, #0
	sub r0, #0x1c
	ldr r6, [r4, r0]
	ldr r0, [r4, #0x64]
	lsl r0, r0, #1
	add r3, r4, r0
	add r0, r1, #0
	add r0, #0x20
	strh r6, [r3, r0]
	add r0, r1, #0
	sub r0, #0x1c
	ldr r0, [r4, r0]
	sub r1, #0x14
	str r0, [r4, r1]
	ldr r0, [r4, r2]
	orr r0, r7
	str r0, [r4, r2]
_02240B92:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x92
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add r1, r5, #0
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	ldr r2, [r4, #0x64]
	add r0, r4, #0
	bl ov11_0224C438
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02240BB2:
	add r1, r1, #1
	cmp r1, r2
	blt _02240B1E
_02240BB8:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02240BBC: .word 0x0000216C
_02240BC0: .word 0x801FDA49
_02240BC4: .word 0x00003044
_02240BC8: .word 0x000003E9
_02240BCC: .word 0x000021EC
_02240BD0: .word 0x0000213C
_02240BD4: .word 0x0000305C

	thumb_func_start ov11_02240BD8
ov11_02240BD8: ; 0x02240BD8
	push {r4, lr}
	add r4, r1, #0
	bl ov11_02232264
	cmp r0, #1
	bne _02240BF0
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
	ldr r0, [r4, #0xc]
	str r0, [r4, #8]
_02240BF0:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_02240BF4
ov11_02240BF4: ; 0x02240BF4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r2, [r4, #0x48]
	add r5, r0, #0
	cmp r2, #6
	bhi _02240CEA
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02240C0C: ; jump table
	.short _02240C1A - _02240C0C - 2 ; case 0
	.short _02240C26 - _02240C0C - 2 ; case 1
	.short _02240C3E - _02240C0C - 2 ; case 2
	.short _02240C8A - _02240C0C - 2 ; case 3
	.short _02240CA6 - _02240C0C - 2 ; case 4
	.short _02240CB8 - _02240C0C - 2 ; case 5
	.short _02240CD4 - _02240C0C - 2 ; case 6
_02240C1A:
	bl ov11_0224051C
	ldr r0, [r4, #0x48]
	add r0, r0, #1
	str r0, [r4, #0x48]
	pop {r3, r4, r5, pc}
_02240C26:
	ldr r2, _02240D30 ; =0x00002184
	ldr r3, [r4, r2]
	mov r2, #4
	tst r2, r3
	bne _02240C38
	bl ov11_0223FDB0
	cmp r0, #1
	beq _02240D2C
_02240C38:
	ldr r0, [r4, #0x48]
	add r0, r0, #1
	str r0, [r4, #0x48]
_02240C3E:
	ldr r0, _02240D30 ; =0x00002184
	ldr r1, [r4, r0]
	mov r0, #1
	tst r0, r1
	bne _02240C84
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #0
	bl ov11_0223F84C
	cmp r0, #0
	beq _02240C84
	cmp r0, #1
	beq _02240C64
	cmp r0, #2
	beq _02240C6A
	cmp r0, #3
	beq _02240C70
	b _02240C74
_02240C64:
	mov r0, #0x26
	str r0, [r4, #0xc]
	b _02240C74
_02240C6A:
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	b _02240C74
_02240C70:
	mov r0, #0x21
	str r0, [r4, #0xc]
_02240C74:
	mov r0, #0x15
	str r0, [r4, #8]
	ldr r2, [sp]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	pop {r3, r4, r5, pc}
_02240C84:
	ldr r0, [r4, #0x48]
	add r0, r0, #1
	str r0, [r4, #0x48]
_02240C8A:
	ldr r0, _02240D30 ; =0x00002184
	ldr r1, [r4, r0]
	mov r0, #8
	tst r0, r1
	bne _02240CA0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223FB10
	cmp r0, #1
	beq _02240D2C
_02240CA0:
	ldr r0, [r4, #0x48]
	add r0, r0, #1
	str r0, [r4, #0x48]
_02240CA6:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223FCAC
	cmp r0, #1
	beq _02240D2C
	ldr r0, [r4, #0x48]
	add r0, r0, #1
	str r0, [r4, #0x48]
_02240CB8:
	ldr r0, _02240D30 ; =0x00002184
	ldr r1, [r4, r0]
	mov r0, #0x80
	tst r0, r1
	bne _02240CCE
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02240A6C
	cmp r0, #1
	beq _02240D2C
_02240CCE:
	ldr r0, [r4, #0x48]
	add r0, r0, #1
	str r0, [r4, #0x48]
_02240CD4:
	ldr r3, _02240D34 ; =0x00003044
	ldr r2, [r4, #0x64]
	ldr r3, [r4, r3]
	add r0, r5, #0
	lsl r3, r3, #0x10
	add r1, r4, #0
	lsr r3, r3, #0x10
	bl ov11_02244F68
	mov r0, #0
	str r0, [r4, #0x48]
_02240CEA:
	ldr r1, _02240D38 ; =0x0000216C
	ldr r0, _02240D3C ; =0x801FDA49
	ldr r2, [r4, r1]
	tst r0, r2
	beq _02240CFA
	mov r0, #0x19
	str r0, [r4, #8]
	b _02240D24
_02240CFA:
	add r0, r1, #0
	sub r0, #0x2c
	ldr r2, [r4, r0]
	mov r0, #0x40
	orr r0, r2
	sub r1, #0x2c
	str r0, [r4, r1]
	ldr r2, _02240D34 ; =0x00003044
	add r0, r4, #0
	ldr r2, [r4, r2]
	mov r1, #0
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x17
	str r0, [r4, #0xc]
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02247380
_02240D24:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0224AB44
_02240D2C:
	pop {r3, r4, r5, pc}
	nop
_02240D30: .word 0x00002184
_02240D34: .word 0x00003044
_02240D38: .word 0x0000216C
_02240D3C: .word 0x801FDA49

	thumb_func_start ov11_02240D40
ov11_02240D40: ; 0x02240D40
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r2, [r4, #0x4c]
	add r5, r0, #0
	cmp r2, #6
	bhi _02240E20
	add r3, r2, r2
	add r3, pc
	ldrh r3, [r3, #6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_02240D58: ; jump table
	.short _02240D66 - _02240D58 - 2 ; case 0
	.short _02240D72 - _02240D58 - 2 ; case 1
	.short _02240D84 - _02240D58 - 2 ; case 2
	.short _02240DAE - _02240D58 - 2 ; case 3
	.short _02240DD8 - _02240D58 - 2 ; case 4
	.short _02240DFA - _02240D58 - 2 ; case 5
	.short _02240E1C - _02240D58 - 2 ; case 6
_02240D66:
	add r2, r2, #1
	str r2, [r4, #0x4c]
	bl ov11_0223FCAC
	cmp r0, #1
	beq _02240E24
_02240D72:
	ldr r0, [r4, #0x4c]
	add r1, r4, #0
	add r0, r0, #1
	str r0, [r4, #0x4c]
	add r0, r5, #0
	bl ov11_0224510C
	cmp r0, #1
	beq _02240E24
_02240D84:
	ldr r0, _02240E28 ; =0x00002184
	ldr r1, [r4, r0]
	mov r0, #0x20
	tst r0, r1
	bne _02240DA8
	ldr r3, [r4, #0x6c]
	cmp r3, #0xff
	beq _02240DA8
	ldr r0, _02240E2C ; =0x00003044
	add r1, r4, #0
	ldr r0, [r4, r0]
	str r0, [sp]
	ldr r2, [r4, #0x64]
	add r0, r5, #0
	bl ov11_0224053C
	cmp r0, #1
	beq _02240E24
_02240DA8:
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
_02240DAE:
	ldr r0, _02240E28 ; =0x00002184
	ldr r1, [r4, r0]
	mov r0, #0x40
	tst r0, r1
	bne _02240DD2
	ldr r3, [r4, #0x6c]
	cmp r3, #0xff
	beq _02240DD2
	ldr r0, _02240E2C ; =0x00003044
	add r1, r4, #0
	ldr r0, [r4, r0]
	str r0, [sp]
	ldr r2, [r4, #0x64]
	add r0, r5, #0
	bl ov11_02240890
	cmp r0, #1
	beq _02240E24
_02240DD2:
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
_02240DD8:
	ldr r0, _02240E28 ; =0x00002184
	ldr r1, [r4, r0]
	mov r0, #2
	tst r0, r1
	bne _02240DF4
	ldr r0, [r4, #0x6c]
	cmp r0, #0xff
	beq _02240DF4
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223FD20
	cmp r0, #1
	beq _02240E24
_02240DF4:
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
_02240DFA:
	ldr r0, _02240E28 ; =0x00002184
	ldr r1, [r4, r0]
	mov r0, #0x10
	tst r0, r1
	bne _02240E16
	ldr r0, [r4, #0x6c]
	cmp r0, #0xff
	beq _02240E16
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_022404A4
	cmp r0, #1
	beq _02240E24
_02240E16:
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
_02240E1C:
	mov r0, #0
	str r0, [r4, #0x4c]
_02240E20:
	mov r0, #0x18
	str r0, [r4, #8]
_02240E24:
	pop {r3, r4, r5, pc}
	nop
_02240E28: .word 0x00002184
_02240E2C: .word 0x00003044

	thumb_func_start ov11_02240E30
ov11_02240E30: ; 0x02240E30
	push {r3, r4, lr}
	sub sp, #4
	add r2, sp, #0
	add r4, r1, #0
	bl ov11_02244948
	cmp r0, #1
	bne _02240E56
	ldr r2, [sp]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x19
	add sp, #4
	str r0, [r4, #0xc]
	pop {r3, r4, pc}
_02240E56:
	mov r0, #0x19
	str r0, [r4, #8]
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start ov11_02240E60
ov11_02240E60: ; 0x02240E60
	push {r4, lr}
	ldr r0, _02240ED8 ; =0x0000216C
	add r4, r1, #0
	ldr r1, [r4, r0]
	mov r2, #2
	lsl r2, r2, #0x1e
	add r3, r1, #0
	tst r3, r2
	beq _02240E78
	mov r0, #0x22
	str r0, [r4, #8]
	pop {r4, pc}
_02240E78:
	lsr r2, r2, #0x16
	tst r2, r1
	beq _02240E92
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x2a
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x26
	str r0, [r4, #0xc]
	pop {r4, pc}
_02240E92:
	add r2, r0, #0
	add r2, #0x14
	ldr r2, [r4, r2]
	cmp r2, #0
	beq _02240EB8
	mov r3, #1
	add r2, r1, #0
	tst r2, r3
	beq _02240EB8
	mov r2, #1
	bic r1, r2
	str r1, [r4, r0]
	ldr r2, [r4, r0]
	lsl r1, r3, #0xe
	orr r1, r2
	str r1, [r4, r0]
	mov r0, #0x1c
	str r0, [r4, #8]
	pop {r4, pc}
_02240EB8:
	ldr r0, _02240EDC ; =0x001FD849
	tst r0, r1
	beq _02240ED2
	add r0, r4, #0
	mov r1, #1
	mov r2, #7
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x21
	str r0, [r4, #0xc]
	pop {r4, pc}
_02240ED2:
	mov r0, #0x1a
	str r0, [r4, #8]
	pop {r4, pc}
	.align 2, 0
_02240ED8: .word 0x0000216C
_02240EDC: .word 0x001FD849

	thumb_func_start ov11_02240EE0
ov11_02240EE0: ; 0x02240EE0
	push {r4, lr}
	add r4, r1, #0
	mov r1, #1
	add r0, r4, #0
	add r2, r1, #0
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x1b
	str r0, [r4, #0xc]
	pop {r4, pc}

	thumb_func_start ov11_02240EF8
ov11_02240EF8: ; 0x02240EF8
	push {r3, r4, r5, r6, r7, lr}
	ldr r2, _02241260 ; =0x0000216C
	add r4, r1, #0
	ldr r1, [r4, r2]
	add r5, r0, #0
	mov r0, #0x20
	tst r0, r1
	beq _02240F1E
	ldr r0, [r4, #0x6c]
	mov r1, #0xc0
	add r3, r0, #0
	mul r3, r1
	ldr r0, _02241264 ; =0x00002D90
	add r3, r4, r3
	ldr r0, [r3, r0]
	sub r1, #0xc1
	mul r1, r0
	sub r2, #0x28
	str r1, [r4, r2]
_02240F1E:
	ldr r0, _02241268 ; =0x00002144
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _02240F28
	b _022412E8
_02240F28:
	ldr r1, [r4, #0x6c]
	add r0, r4, #0
	bl ov11_02249D90
	add r7, r0, #0
	ldr r1, [r4, #0x6c]
	add r0, r4, #0
	mov r2, #0
	bl ov11_02249DA4
	str r0, [sp]
	ldr r0, _02241268 ; =0x00002144
	ldr r0, [r4, r0]
	cmp r0, #0
	blt _02240F4A
	bl GF_AssertFail
_02240F4A:
	ldr r1, [r4, #0x64]
	add r0, r5, #0
	bl ov11_02230270
	add r6, r0, #0
	ldr r1, [r4, #0x6c]
	add r0, r5, #0
	bl ov11_02230270
	cmp r6, r0
	bne _02240F6C
	ldr r1, [r4, #0x64]
	add r0, r5, #0
	mov r2, #0
	mov r3, #0x46
	bl ov11_022564A8
_02240F6C:
	ldr r0, [r4, #0x6c]
	ldr r2, [r4, #0x64]
	lsl r0, r0, #2
	add r1, r4, r0
	ldr r0, _0224126C ; =0x000030F4
	str r2, [r1, r0]
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	add r6, r1, #0
	mul r6, r0
	mov r2, #1
	ldr r1, _02241270 ; =0x00002DB0
	add r5, r4, r6
	ldr r3, [r5, r1]
	lsl r2, r2, #0x18
	tst r2, r3
	beq _02241044
	ldr r2, _02241268 ; =0x00002144
	ldr r2, [r4, r2]
	cmp r2, #0
	bge _02241044
	add r3, r1, #0
	add r3, #0x30
	ldr r3, [r5, r3]
	add r5, r2, r3
	cmp r5, #0
	bgt _02240FE8
	mov r2, #0xbb
	lsl r2, r2, #2
	add r6, r4, r2
	ldr r2, [r4, #0x64]
	mov r5, #0x1c
	mul r5, r2
	ldr r2, [r6, r5]
	sub r2, r2, r3
	str r2, [r6, r5]
	ldr r5, [r4, #0x6c]
	add r3, r4, r1
	add r2, r5, #0
	mul r2, r0
	ldr r6, [r3, r2]
	ldr r5, _02241274 ; =0xFEFFFFFF
	and r5, r6
	str r5, [r3, r2]
	ldr r2, [r4, #0x6c]
	add r3, r2, #0
	add r2, r1, #0
	mul r3, r0
	add r3, r4, r3
	add r2, #0x30
	ldr r2, [r3, r2]
	add r1, #0x30
	neg r3, r2
	ldr r2, _02241268 ; =0x00002144
	add r2, r2, #4
	str r3, [r4, r2]
	ldr r2, [r4, #0x6c]
	mov r3, #0
	mul r0, r2
	add r0, r4, r0
	str r3, [r0, r1]
	b _02241014
_02240FE8:
	mov r3, #0xbb
	lsl r3, r3, #2
	add r6, r4, r3
	ldr r3, [r4, #0x64]
	mov r5, #0x1c
	mul r5, r3
	ldr r3, [r6, r5]
	add r1, #0x30
	add r2, r3, r2
	str r2, [r6, r5]
	ldr r2, [r4, #0x6c]
	add r1, r4, r1
	mul r0, r2
	ldr r2, _02241268 ; =0x00002144
	ldr r3, [r1, r0]
	ldr r2, [r4, r2]
	add r2, r3, r2
	str r2, [r1, r0]
	ldr r0, _02241268 ; =0x00002144
	ldr r1, [r4, r0]
	add r0, r0, #4
	str r1, [r4, r0]
_02241014:
	mov r0, #0xba
	lsl r0, r0, #2
	ldr r2, [r4, #0x6c]
	add r1, r4, r0
	add r0, r2, #0
	mov r3, #0x1c
	mul r0, r3
	ldr r5, [r1, r0]
	mov r2, #8
	orr r2, r5
	str r2, [r1, r0]
	ldr r0, [r4, #0x6c]
	add r3, #0xfc
	str r0, [r4, r3]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x5a
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x1c
	str r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02241044:
	ldr r0, _02241278 ; =0x00003044
	ldr r0, [r4, r0]
	lsl r0, r0, #4
	add r1, r4, r0
	ldr r0, _0224127C ; =0x000003DE
	ldrh r0, [r1, r0]
	cmp r0, #0x65
	bne _0224106A
	ldr r0, _02241280 ; =0x00002D8C
	add r1, r4, r6
	ldr r2, [r1, r0]
	ldr r0, _02241268 ; =0x00002144
	ldr r1, [r4, r0]
	add r1, r1, r2
	cmp r1, #0
	bgt _0224106A
	sub r1, r2, #1
	neg r1, r1
	str r1, [r4, r0]
_0224106A:
	ldr r0, [r4, #0x6c]
	lsl r0, r0, #6
	add r1, r4, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x16
	lsr r0, r0, #0x1f
	bne _022410D0
	cmp r7, #0x40
	bne _022410A4
	bl LCRandom
	mov r1, #0x64
	bl _s32_div_f
	ldr r0, [sp]
	cmp r1, r0
	bge _022410A4
	mov r0, #0xb5
	lsl r0, r0, #2
	add r1, r4, r0
	ldr r2, [r4, #0x6c]
	mov r0, #0x1c
	mul r0, r2
	ldr r3, [r1, r0]
	mov r2, #0x20
	orr r2, r3
	str r2, [r1, r0]
_022410A4:
	cmp r7, #0x66
	bne _022410D0
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r3, r4, r0
	ldr r0, _02241280 ; =0x00002D8C
	ldr r2, [r3, r0]
	add r0, r0, #4
	ldr r0, [r3, r0]
	cmp r2, r0
	bne _022410D0
	mov r0, #0xb5
	lsl r0, r0, #2
	add r3, r1, #0
	mov r2, #0x1c
	add r0, r4, r0
	mul r3, r2
	ldr r2, [r0, r3]
	mov r1, #0x20
	orr r1, r2
	str r1, [r0, r3]
_022410D0:
	ldr r0, [r4, #0x6c]
	lsl r1, r0, #6
	add r2, r4, r1
	mov r1, #0x75
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	lsl r1, r1, #0x16
	lsr r1, r1, #0x1f
	bne _022410F4
	mov r1, #0x1c
	mul r1, r0
	add r2, r4, r1
	mov r1, #0xb5
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1f
	beq _0224113E
_022410F4:
	mov r1, #0xc0
	mul r1, r0
	ldr r0, _02241280 ; =0x00002D8C
	add r1, r4, r1
	ldr r2, _02241268 ; =0x00002144
	ldr r1, [r1, r0]
	ldr r0, [r4, r2]
	add r0, r0, r1
	cmp r0, #0
	bgt _0224113E
	sub r0, r1, #1
	neg r0, r0
	str r0, [r4, r2]
	ldr r0, [r4, #0x6c]
	mov r1, #0x75
	lsl r0, r0, #6
	add r0, r4, r0
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	lsl r0, r0, #0x16
	lsr r0, r0, #0x1f
	beq _02241130
	add r0, r2, #0
	add r0, #0x28
	ldr r1, [r4, r0]
	mov r0, #0x80
	orr r0, r1
	add r2, #0x28
	str r0, [r4, r2]
	b _0224113E
_02241130:
	add r0, r2, #0
	add r0, #0x28
	ldr r0, [r4, r0]
	sub r1, #0xd4
	orr r0, r1
	add r2, #0x28
	str r0, [r4, r2]
_0224113E:
	ldr r1, [r4, #0x6c]
	ldr r0, _02241284 ; =0x000030E4
	lsl r3, r1, #2
	ldr r1, _02241268 ; =0x00002144
	add r0, r4, r0
	ldr r2, [r0, r3]
	ldr r1, [r4, r1]
	add r1, r2, r1
	str r1, [r0, r3]
	ldr r0, _02241288 ; =0x00002DBC
	ldr r1, [r4, #0x6c]
	add r3, r4, r0
	mov r0, #0xc0
	add r2, r1, #0
	mul r2, r0
	ldrb r0, [r3, r2]
	cmp r0, #0xff
	bhs _02241166
	add r0, r0, #1
	strb r0, [r3, r2]
_02241166:
	ldr r0, _02241278 ; =0x00003044
	mov r1, #0x3e
	ldr r0, [r4, r0]
	lsl r1, r1, #4
	lsl r0, r0, #4
	add r0, r4, r0
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _022411D4
	ldr r1, [r4, #0x6c]
	ldr r0, _02241268 ; =0x00002144
	lsl r1, r1, #6
	add r2, r4, r1
	ldr r1, [r4, #0x64]
	ldr r0, [r4, r0]
	lsl r1, r1, #2
	add r2, r2, r1
	mov r1, #0x76
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4, #0x6c]
	ldr r2, [r4, #0x64]
	lsl r0, r0, #6
	add r0, r4, r0
	add r1, #0x10
	str r2, [r0, r1]
	ldr r0, [r4, #0x64]
	bl MaskOfFlagNo
	mov r1, #0x7b
	ldr r3, [r4, #0x6c]
	lsl r1, r1, #2
	add r2, r4, r1
	lsl r5, r3, #6
	ldr r3, [r2, r5]
	orr r0, r3
	str r0, [r2, r5]
	ldr r2, [r4, #0x6c]
	ldr r0, _02241268 ; =0x00002144
	add r5, r2, #0
	add r2, r1, #0
	mov r3, #0x1c
	mul r5, r3
	ldr r0, [r4, r0]
	add r5, r4, r5
	add r2, #0xec
	str r0, [r5, r2]
	ldr r0, [r4, #0x6c]
	ldr r5, [r4, #0x64]
	add r2, r0, #0
	mul r2, r3
	add r0, r4, r2
	add r1, #0xf0
	str r5, [r0, r1]
	b _02241232
_022411D4:
	cmp r0, #1
	bne _02241232
	ldr r2, [r4, #0x6c]
	ldr r0, _02241268 ; =0x00002144
	lsl r2, r2, #6
	add r3, r4, r2
	ldr r2, [r4, #0x64]
	ldr r0, [r4, r0]
	lsl r2, r2, #2
	add r2, r3, r2
	lsr r1, r1, #1
	str r0, [r2, r1]
	ldr r0, [r4, #0x6c]
	ldr r2, [r4, #0x64]
	lsl r0, r0, #6
	add r1, r4, r0
	mov r0, #2
	lsl r0, r0, #8
	str r2, [r1, r0]
	ldr r0, [r4, #0x64]
	bl MaskOfFlagNo
	mov r1, #0x81
	ldr r3, [r4, #0x6c]
	lsl r1, r1, #2
	add r2, r4, r1
	lsl r5, r3, #6
	ldr r3, [r2, r5]
	orr r0, r3
	str r0, [r2, r5]
	ldr r2, [r4, #0x6c]
	ldr r0, _02241268 ; =0x00002144
	add r5, r2, #0
	add r2, r1, #0
	mov r3, #0x1c
	mul r5, r3
	ldr r0, [r4, r0]
	add r5, r4, r5
	add r2, #0xdc
	str r0, [r5, r2]
	ldr r0, [r4, #0x6c]
	ldr r5, [r4, #0x64]
	add r2, r0, #0
	mul r2, r3
	add r0, r4, r2
	add r1, #0xe0
	str r5, [r0, r1]
_02241232:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _02241280 ; =0x00002D8C
	ldr r2, [r1, r0]
	ldr r0, _02241268 ; =0x00002144
	ldr r1, [r4, r0]
	add r0, r1, r2
	cmp r0, #0
	bgt _0224128C
	mov r0, #0xbb
	lsl r0, r0, #2
	add r1, r4, r0
	ldr r3, [r4, #0x64]
	mov r0, #0x1c
	mul r0, r3
	ldr r3, [r1, r0]
	neg r2, r2
	add r2, r3, r2
	str r2, [r1, r0]
	b _022412A0
	nop
_02241260: .word 0x0000216C
_02241264: .word 0x00002D90
_02241268: .word 0x00002144
_0224126C: .word 0x000030F4
_02241270: .word 0x00002DB0
_02241274: .word 0xFEFFFFFF
_02241278: .word 0x00003044
_0224127C: .word 0x000003DE
_02241280: .word 0x00002D8C
_02241284: .word 0x000030E4
_02241288: .word 0x00002DBC
_0224128C:
	ldr r3, [r4, #0x64]
	mov r0, #0xbb
	lsl r0, r0, #2
	mov r2, #0x1c
	add r5, r3, #0
	add r0, r4, r0
	mul r5, r2
	ldr r2, [r0, r5]
	add r1, r2, r1
	str r1, [r0, r5]
_022412A0:
	ldr r3, _022412F0 ; =0x00002144
	ldr r0, [r4, #0x6c]
	mov r2, #0x82
	lsl r0, r0, #6
	ldr r1, [r4, r3]
	add r0, r4, r0
	lsl r2, r2, #2
	str r1, [r0, r2]
	ldr r1, [r4, #0x6c]
	ldr r0, [r4, #0x64]
	lsl r1, r1, #6
	add r5, r4, r1
	add r1, r2, #4
	str r0, [r5, r1]
	ldr r0, [r4, #0x6c]
	sub r2, #0xf0
	str r0, [r4, r2]
	ldr r0, [r4, r3]
	add r3, #0x18
	str r0, [r4, r3]
	add r0, r4, #0
	mov r1, #1
	mov r2, #2
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x1c
	str r0, [r4, #0xc]
	ldr r1, _022412F4 ; =0x0000213C
	mov r0, #2
	ldr r2, [r4, r1]
	lsl r0, r0, #0xc
	orr r0, r2
	str r0, [r4, r1]
	pop {r3, r4, r5, r6, r7, pc}
_022412E8:
	mov r0, #0x1c
	str r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022412F0: .word 0x00002144
_022412F4: .word 0x0000213C

	thumb_func_start ov11_022412F8
ov11_022412F8: ; 0x022412F8
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r1, #0
	ldr r2, [r4, #0x38]
	add r5, r0, #0
	cmp r2, #0
	beq _0224130C
	cmp r2, #1
	beq _022413D2
	b _02241490
_0224130C:
	ldr r2, [r4, #0x3c]
	cmp r2, #5
	bls _02241314
	b _02241490
_02241314:
	add r3, r2, r2
	add r3, pc
	ldrh r3, [r3, #6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_02241320: ; jump table
	.short _0224132C - _02241320 - 2 ; case 0
	.short _02241338 - _02241320 - 2 ; case 1
	.short _0224134A - _02241320 - 2 ; case 2
	.short _0224137E - _02241320 - 2 ; case 3
	.short _02241392 - _02241320 - 2 ; case 4
	.short _022413BC - _02241320 - 2 ; case 5
_0224132C:
	add r2, r2, #1
	str r2, [r4, #0x3c]
	bl ov11_02242774
	cmp r0, #1
	beq _02241390
_02241338:
	ldr r0, [r4, #0x3c]
	add r1, r4, #0
	add r0, r0, #1
	str r0, [r4, #0x3c]
	add r0, r5, #0
	bl ov11_02242790
	cmp r0, #1
	beq _02241390
_0224134A:
	ldr r0, [r4, #0x3c]
	add r1, r4, #0
	add r0, r0, #1
	str r0, [r4, #0x3c]
	add r0, r5, #0
	add r2, sp, #0xc
	bl ov11_022449EC
	cmp r0, #1
	bne _0224137E
	ldr r0, _0224149C ; =0x0000216C
	ldr r1, [r4, r0]
	ldr r0, _022414A0 ; =0x001FD849
	tst r0, r1
	bne _0224137E
	ldr r2, [sp, #0xc]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add sp, #0x10
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
_0224137E:
	ldr r0, [r4, #0x3c]
	add r1, r4, #0
	add r0, r0, #1
	str r0, [r4, #0x3c]
	add r0, r5, #0
	bl ov11_022427E4
	cmp r0, #1
	bne _02241392
_02241390:
	b _02241498
_02241392:
	ldr r0, [r4, #0x3c]
	add r1, r4, #0
	add r0, r0, #1
	str r0, [r4, #0x3c]
	add r0, r5, #0
	add r2, sp, #8
	bl ov11_02248308
	cmp r0, #1
	bne _022413BC
	ldr r2, [sp, #8]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add sp, #0x10
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
_022413BC:
	ldr r0, [r4, #0x3c]
	add r1, r4, #0
	add r0, r0, #1
	str r0, [r4, #0x3c]
	add r0, r5, #0
	bl ov11_02242870
	cmp r0, #1
	bne _02241490
	add sp, #0x10
	pop {r3, r4, r5, pc}
_022413D2:
	ldr r2, [r4, #0x3c]
	cmp r2, #5
	bhi _02241490
	add r3, r2, r2
	add r3, pc
	ldrh r3, [r3, #6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_022413E4: ; jump table
	.short _022413F0 - _022413E4 - 2 ; case 0
	.short _022413FC - _022413E4 - 2 ; case 1
	.short _02241430 - _022413E4 - 2 ; case 2
	.short _02241442 - _022413E4 - 2 ; case 3
	.short _0224146C - _022413E4 - 2 ; case 4
	.short _0224147E - _022413E4 - 2 ; case 5
_022413F0:
	add r2, r2, #1
	str r2, [r4, #0x3c]
	bl ov11_02242774
	cmp r0, #1
	beq _02241498
_022413FC:
	ldr r0, [r4, #0x3c]
	add r1, r4, #0
	add r0, r0, #1
	str r0, [r4, #0x3c]
	add r0, r5, #0
	add r2, sp, #4
	bl ov11_022449EC
	cmp r0, #1
	bne _02241430
	ldr r0, _0224149C ; =0x0000216C
	ldr r1, [r4, r0]
	ldr r0, _022414A0 ; =0x001FD849
	tst r0, r1
	bne _02241430
	ldr r2, [sp, #4]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add sp, #0x10
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
_02241430:
	ldr r0, [r4, #0x3c]
	add r1, r4, #0
	add r0, r0, #1
	str r0, [r4, #0x3c]
	add r0, r5, #0
	bl ov11_022427E4
	cmp r0, #1
	beq _02241498
_02241442:
	ldr r0, [r4, #0x3c]
	add r1, r4, #0
	add r0, r0, #1
	str r0, [r4, #0x3c]
	add r0, r5, #0
	add r2, sp, #0
	bl ov11_02248308
	cmp r0, #1
	bne _0224146C
	ldr r2, [sp]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add sp, #0x10
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
_0224146C:
	ldr r0, [r4, #0x3c]
	add r1, r4, #0
	add r0, r0, #1
	str r0, [r4, #0x3c]
	add r0, r5, #0
	bl ov11_02242790
	cmp r0, #1
	beq _02241498
_0224147E:
	ldr r0, [r4, #0x3c]
	add r1, r4, #0
	add r0, r0, #1
	str r0, [r4, #0x3c]
	add r0, r5, #0
	bl ov11_02242870
	cmp r0, #1
	beq _02241498
_02241490:
	mov r0, #0
	str r0, [r4, #0x3c]
	mov r0, #0x1e
	str r0, [r4, #8]
_02241498:
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224149C: .word 0x0000216C
_022414A0: .word 0x001FD849

	thumb_func_start ov11_022414A4
ov11_022414A4: ; 0x022414A4
	bx lr
	.align 2, 0

	thumb_func_start ov11_022414A8
ov11_022414A8: ; 0x022414A8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	ldr r1, [r4, #0x40]
	add r7, r0, #0
	cmp r1, #7
	bls _022414B8
	b _022416F2
_022414B8:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022414C4: ; jump table
	.short _022414D4 - _022414C4 - 2 ; case 0
	.short _0224154E - _022414C4 - 2 ; case 1
	.short _02241562 - _022414C4 - 2 ; case 2
	.short _02241588 - _022414C4 - 2 ; case 3
	.short _0224159C - _022414C4 - 2 ; case 4
	.short _022415B6 - _022414C4 - 2 ; case 5
	.short _022415E0 - _022414C4 - 2 ; case 6
	.short _02241674 - _022414C4 - 2 ; case 7
_022414D4:
	mov r1, #0
	ldr r5, [r4, #0x44]
	str r1, [sp, #4]
	bl ov11_0222FF84
	cmp r5, r0
	bge _02241544
	add r6, r4, #0
	add r6, #0x44
_022414E6:
	mov r0, #0xc0
	mul r0, r5
	mov r1, #0xb7
	add r0, r4, r0
	lsl r1, r1, #6
	ldr r2, [r0, r1]
	ldr r1, _02241700 ; =0x200400C0
	tst r1, r2
	bne _0224152C
	ldr r1, _02241704 ; =0x00002DC4
	ldr r2, [r0, r1]
	ldr r1, _02241700 ; =0x200400C0
	tst r1, r2
	beq _0224152C
	ldr r1, _02241704 ; =0x00002DC4
	ldr r2, [r0, r1]
	ldr r1, _02241708 ; =0xDFFBFF3F
	and r2, r1
	ldr r1, _02241704 ; =0x00002DC4
	str r2, [r0, r1]
	ldr r2, _0224170C ; =0x0000011F
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	mov r0, #0x46
	ldr r1, [r4, #0x44]
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp, #4]
_0224152C:
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _022415B4
	ldr r5, [r4, #0x44]
	add r0, r7, #0
	bl ov11_0222FF84
	cmp r5, r0
	blt _022414E6
_02241544:
	ldr r0, [r4, #0x40]
	add r0, r0, #1
	str r0, [r4, #0x40]
	mov r0, #0
	str r0, [r4, #0x44]
_0224154E:
	ldr r0, [r4, #0x40]
	add r1, r4, #0
	add r0, r0, #1
	str r0, [r4, #0x40]
	ldr r2, [r4, #8]
	add r0, r7, #0
	bl ov11_02248A78
	cmp r0, #1
	beq _022415B4
_02241562:
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_022476DC
	add r2, r0, #0
	beq _02241582
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add sp, #0x10
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_02241582:
	ldr r0, [r4, #0x40]
	add r0, r0, #1
	str r0, [r4, #0x40]
_02241588:
	ldr r0, [r4, #0x40]
	add r1, r4, #0
	add r0, r0, #1
	str r0, [r4, #0x40]
	ldr r2, [r4, #0x64]
	add r0, r7, #0
	bl ov11_02248C0C
	cmp r0, #1
	beq _022415B4
_0224159C:
	ldr r0, [r4, #0x40]
	add r0, r0, #1
	str r0, [r4, #0x40]
	ldr r2, [r4, #0x6c]
	cmp r2, #0xff
	beq _022415B6
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_02248C0C
	cmp r0, #1
	bne _022415B6
_022415B4:
	b _022416FC
_022415B6:
	ldr r0, [r4, #0x40]
	add r1, r4, #0
	add r0, r0, #1
	str r0, [r4, #0x40]
	add r0, r7, #0
	add r2, sp, #0xc
	bl ov11_02249B94
	cmp r0, #1
	bne _022415E0
	ldr r2, [sp, #0xc]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add sp, #0x10
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_022415E0:
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x60
	bne _022415F0
	mov r2, #0
	b _02241604
_022415F0:
	ldr r0, _02241710 ; =0x00002160
	ldr r2, [r4, r0]
	cmp r2, #0
	bne _02241604
	ldr r0, _02241714 ; =0x00003044
	ldr r0, [r4, r0]
	lsl r0, r0, #4
	add r1, r4, r0
	ldr r0, _02241718 ; =0x000003E2
	ldrb r2, [r1, r0]
_02241604:
	ldr r0, [r4, #0x40]
	add r0, r0, #1
	str r0, [r4, #0x40]
	ldr r3, [r4, #0x6c]
	cmp r3, #0xff
	beq _02241674
	mov r0, #0xc0
	add r5, r3, #0
	mul r5, r0
	ldr r0, _0224171C ; =0x00002DAC
	add r1, r4, r5
	ldr r1, [r1, r0]
	mov r0, #0x20
	tst r1, r0
	beq _02241674
	ldr r1, _02241720 ; =0x0000216C
	lsl r0, r0, #9
	ldr r1, [r4, r1]
	tst r0, r1
	bne _02241674
	ldr r0, [r4, #0x64]
	cmp r3, r0
	beq _02241674
	mov r0, #0x1c
	mul r0, r3
	add r6, r4, r0
	mov r0, #0xb6
	lsl r0, r0, #2
	ldr r1, [r6, r0]
	cmp r1, #0
	bne _0224164A
	add r0, #8
	ldr r0, [r6, r0]
	cmp r0, #0
	beq _02241674
_0224164A:
	ldr r0, _02241724 ; =0x00002D8C
	add r1, r4, r5
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02241674
	cmp r2, #0xa
	bne _02241674
	mov r0, #0x46
	lsl r0, r0, #2
	str r3, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x1d
	bl ov11_022431DC
	ldr r0, [r4, #8]
	add sp, #0x10
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_02241674:
	mov r0, #0
	str r0, [sp]
	ldr r6, [r4, #0x44]
	add r0, r7, #0
	bl ov11_0222FF84
	cmp r6, r0
	bge _022416E2
	add r5, r4, #0
	add r5, #0x44
_02241688:
	ldr r0, _02241728 ; =0x000021EC
	add r1, r4, r6
	ldrb r6, [r1, r0]
	add r0, r6, #0
	bl MaskOfFlagNo
	ldr r1, _0224172C ; =0x00003108
	ldrb r1, [r4, r1]
	tst r0, r1
	ldr r0, [r5]
	beq _022416A4
	add r0, r0, #1
	str r0, [r5]
	b _022416D6
_022416A4:
	add r0, r0, #1
	str r0, [r5]
	add r0, r7, #0
	add r1, r4, #0
	add r2, r6, #0
	add r3, sp, #8
	bl ov11_022493A0
	cmp r0, #1
	bne _022416D6
	mov r0, #0x46
	lsl r0, r0, #2
	str r6, [r4, r0]
	ldr r2, [sp, #8]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	str r0, [sp]
	b _022416E2
_022416D6:
	ldr r6, [r4, #0x44]
	add r0, r7, #0
	bl ov11_0222FF84
	cmp r6, r0
	blt _02241688
_022416E2:
	ldr r0, [sp]
	cmp r0, #0
	bne _022416F2
	ldr r0, [r4, #0x40]
	add r0, r0, #1
	str r0, [r4, #0x40]
	mov r0, #0
	str r0, [r4, #0x44]
_022416F2:
	mov r0, #0
	str r0, [r4, #0x40]
	str r0, [r4, #0x44]
	mov r0, #0x1f
	str r0, [r4, #8]
_022416FC:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02241700: .word 0x200400C0
_02241704: .word 0x00002DC4
_02241708: .word 0xDFFBFF3F
_0224170C: .word 0x0000011F
_02241710: .word 0x00002160
_02241714: .word 0x00003044
_02241718: .word 0x000003E2
_0224171C: .word 0x00002DAC
_02241720: .word 0x0000216C
_02241724: .word 0x00002D8C
_02241728: .word 0x000021EC
_0224172C: .word 0x00003108

	thumb_func_start ov11_02241730
ov11_02241730: ; 0x02241730
	bx lr
	.align 2, 0

	thumb_func_start ov11_02241734
ov11_02241734: ; 0x02241734
	push {r3, r4, r5, r6, r7, lr}
	ldr r6, _02241820 ; =0x0000217D
	add r4, r1, #0
	ldrb r2, [r4, r6]
	str r0, [sp]
	cmp r2, #0
	beq _0224181A
	ldr r3, [r4, #0x74]
	mov ip, r3
	cmp r3, #0xff
	bne _022417CC
	ldr r3, [r4, #0x64]
	mov r7, #0xc0
	add r5, r3, #0
	mul r5, r7
	ldr r3, _02241824 ; =0x00002DAC
	add r5, r4, r5
	ldr r5, [r5, r3]
	mov r3, #7
	tst r3, r5
	bne _022417CC
	add r3, r6, #0
	sub r3, #0x11
	ldr r5, [r4, r3]
	mov r3, #1
	lsl r3, r3, #0xe
	tst r3, r5
	bne _022417CC
	sub r2, r6, #1
	ldrb r2, [r4, r2]
	sub r3, r2, #1
	sub r2, r6, #1
	strb r3, [r4, r2]
	ldrb r2, [r4, r2]
	cmp r2, #0
	beq _022417B2
	mov r3, #1
	add r2, r6, #3
	str r3, [r4, r2]
	bl ov11_02247264
	add r1, r6, #0
	sub r1, #0x41
	ldr r2, [r4, r1]
	ldr r0, _02241828 ; =0xFFFFBFFF
	and r0, r2
	str r0, [r4, r1]
	add r0, r1, #0
	add r0, #0x4c
	ldr r0, [r4, r0]
	add r1, #0x48
	str r0, [r4, r1]
	ldr r2, _0224182C ; =0x00003044
	add r0, r4, #0
	ldr r2, [r4, r2]
	mov r1, #0
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x17
	str r0, [r4, #0xc]
	b _02241812
_022417B2:
	ldrb r0, [r4, r6]
	add r7, #0x70
	mov r1, #1
	str r0, [r4, r7]
	add r0, r4, #0
	mov r2, #0x11
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x21
	str r0, [r4, #0xc]
	b _02241812
_022417CC:
	mov r0, ip
	cmp r0, #0xff
	bne _022417E6
	ldr r0, [r4, #0x64]
	mov r1, #0xc0
	add r3, r0, #0
	mul r3, r1
	ldr r0, _02241824 ; =0x00002DAC
	add r3, r4, r3
	ldr r3, [r3, r0]
	mov r0, #7
	tst r0, r3
	beq _022417F6
_022417E6:
	ldr r0, _02241830 ; =0x0000217C
	ldrb r0, [r4, r0]
	sub r0, r2, r0
	add r1, r0, #1
	mov r0, #0x13
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _02241800
_022417F6:
	ldr r0, _02241830 ; =0x0000217C
	add r1, #0x70
	ldrb r0, [r4, r0]
	sub r0, r2, r0
	str r0, [r4, r1]
_02241800:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x11
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x21
	str r0, [r4, #0xc]
_02241812:
	ldr r0, [sp]
	bl ov11_0225679C
	pop {r3, r4, r5, r6, r7, pc}
_0224181A:
	mov r0, #0x21
	str r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02241820: .word 0x0000217D
_02241824: .word 0x00002DAC
_02241828: .word 0xFFFFBFFF
_0224182C: .word 0x00003044
_02241830: .word 0x0000217C

	thumb_func_start ov11_02241834
ov11_02241834: ; 0x02241834
	push {r3, lr}
	ldr r0, _02241858 ; =0x0000213C
	ldr r2, [r1, r0]
	mov r0, #0xf
	lsl r0, r0, #0x18
	tst r0, r2
	beq _02241850
	add r0, r1, #0
	mov r1, #0x21
	add r2, r1, #0
	mov r3, #0
	bl ov11_0224246C
	pop {r3, pc}
_02241850:
	mov r0, #0x22
	str r0, [r1, #8]
	pop {r3, pc}
	nop
_02241858: .word 0x0000213C

	thumb_func_start ov11_0224185C
ov11_0224185C: ; 0x0224185C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	mov r1, #0x85
	lsl r1, r1, #6
	add r5, r0, #0
	ldr r2, [r4, r1]
	mov r0, #8
	tst r0, r2
	beq _02241880
	mov r0, #8
	bic r2, r0
	str r2, [r4, r1]
	ldr r0, [r4, #0x64]
	str r0, [r4, #0x6c]
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	str r0, [r4, #0x64]
_02241880:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0224256C
	ldr r0, _022419E0 ; =0x00003044
	ldr r0, [r4, r0]
	lsl r0, r0, #4
	add r1, r4, r0
	ldr r0, _022419E4 ; =0x000003E6
	ldrh r0, [r1, r0]
	cmp r0, #4
	bne _0224194C
	ldr r0, _022419E8 ; =0x0000213C
	ldr r1, [r4, r0]
	mov r0, #2
	tst r0, r1
	bne _0224194C
	add r0, r5, #0
	bl ov11_0222FF84
	ldr r1, _022419EC ; =0x0000217E
	ldrb r2, [r4, r1]
	cmp r2, r0
	bge _0224194C
	mov r2, #0xd
	add r0, r1, #6
	str r2, [r4, r0]
	add r0, r5, #0
	bl ov11_0222FF84
	ldr r1, [r4, #0x64]
	add r0, r5, #0
	bl ov11_0222FF7C
	bl ov11_02253A4C
	mov r1, #1
	add r7, r0, #0
	and r7, r1
_022418CE:
	ldr r1, _022419EC ; =0x0000217E
	ldr r0, _022419EC ; =0x0000217E
	ldrb r1, [r4, r1]
	ldrb r0, [r4, r0]
	add r2, r1, #1
	ldr r1, _022419EC ; =0x0000217E
	strb r2, [r4, r1]
	add r1, r4, r0
	ldr r0, _022419F0 ; =0x000021EC
	ldrb r6, [r1, r0]
	add r0, r6, #0
	bl MaskOfFlagNo
	ldr r1, _022419F4 ; =0x00003108
	ldrb r1, [r4, r1]
	tst r0, r1
	bne _02241936
	mov r0, #0xc0
	mul r0, r6
	add r1, r4, r0
	ldr r0, _022419F8 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02241936
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_0222FF7C
	str r0, [sp]
	cmp r7, #0
	beq _02241916
	bl ov11_02253A4C
	mov r1, #1
	tst r0, r1
	beq _02241926
_02241916:
	cmp r7, #0
	bne _02241936
	ldr r0, [sp]
	bl ov11_02253A4C
	mov r1, #1
	tst r0, r1
	beq _02241936
_02241926:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02247264
	str r6, [r4, #0x6c]
	mov r0, #0x16
	str r0, [r4, #8]
	b _02241944
_02241936:
	add r0, r5, #0
	bl ov11_0222FF84
	ldr r1, _022419EC ; =0x0000217E
	ldrb r1, [r4, r1]
	cmp r1, r0
	blt _022418CE
_02241944:
	add r0, r5, #0
	bl ov11_0225679C
	pop {r3, r4, r5, r6, r7, pc}
_0224194C:
	ldr r0, _022419E0 ; =0x00003044
	ldr r0, [r4, r0]
	lsl r0, r0, #4
	add r1, r4, r0
	ldr r0, _022419E4 ; =0x000003E6
	ldrh r0, [r1, r0]
	cmp r0, #8
	bne _022419DA
	ldr r0, _022419E8 ; =0x0000213C
	ldr r1, [r4, r0]
	mov r0, #2
	tst r0, r1
	bne _022419DA
	add r0, r5, #0
	bl ov11_0222FF84
	ldr r1, _022419EC ; =0x0000217E
	ldrb r2, [r4, r1]
	cmp r2, r0
	bge _022419DA
	mov r2, #0xd
	add r0, r1, #6
	str r2, [r4, r0]
	add r0, r5, #0
	bl ov11_0222FF84
	ldr r7, _022419EC ; =0x0000217E
_02241982:
	ldr r0, _022419EC ; =0x0000217E
	ldrb r1, [r4, r0]
	ldrb r0, [r4, r7]
	add r1, r4, r1
	add r0, r0, #1
	strb r0, [r4, r7]
	ldr r0, _022419F0 ; =0x000021EC
	ldrb r6, [r1, r0]
	add r0, r6, #0
	bl MaskOfFlagNo
	ldr r1, _022419F4 ; =0x00003108
	ldrb r1, [r4, r1]
	tst r0, r1
	bne _022419C4
	mov r0, #0xc0
	mul r0, r6
	add r1, r4, r0
	ldr r0, _022419F8 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _022419C4
	ldr r0, [r4, #0x64]
	cmp r6, r0
	beq _022419C4
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02247264
	str r6, [r4, #0x6c]
	mov r0, #0x16
	str r0, [r4, #8]
	b _022419D2
_022419C4:
	add r0, r5, #0
	bl ov11_0222FF84
	ldr r1, _022419EC ; =0x0000217E
	ldrb r1, [r4, r1]
	cmp r1, r0
	blt _02241982
_022419D2:
	add r0, r5, #0
	bl ov11_0225679C
	pop {r3, r4, r5, r6, r7, pc}
_022419DA:
	mov r0, #0x23
	str r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022419E0: .word 0x00003044
_022419E4: .word 0x000003E6
_022419E8: .word 0x0000213C
_022419EC: .word 0x0000217E
_022419F0: .word 0x000021EC
_022419F4: .word 0x00003108
_022419F8: .word 0x00002D8C

	thumb_func_start ov11_022419FC
ov11_022419FC: ; 0x022419FC
	push {r4, lr}
	ldr r0, _02241A38 ; =0x0000213C
	add r4, r1, #0
	ldr r1, [r4, r0]
	mov r0, #0xf
	lsl r0, r0, #0x1c
	and r0, r1
	beq _02241A32
	lsr r0, r0, #0x1c
	bl LowestFlagNo
	str r0, [r4, #0x74]
	ldr r1, _02241A38 ; =0x0000213C
	ldr r0, _02241A3C ; =0x0FFFFFFF
	ldr r2, [r4, r1]
	and r0, r2
	str r0, [r4, r1]
	ldr r2, _02241A40 ; =0x00000115
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x24
	str r0, [r4, #0xc]
	pop {r4, pc}
_02241A32:
	mov r0, #0x24
	str r0, [r4, #8]
	pop {r4, pc}
	.align 2, 0
_02241A38: .word 0x0000213C
_02241A3C: .word 0x0FFFFFFF
_02241A40: .word 0x00000115

	thumb_func_start ov11_02241A44
ov11_02241A44: ; 0x02241A44
	push {r4, lr}
	add r4, r1, #0
	bl ov11_022429B0
	cmp r0, #1
	beq _02241A54
	mov r0, #0x26
	str r0, [r4, #8]
_02241A54:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_02241A58
ov11_02241A58: ; 0x02241A58
	bx lr
	.align 2, 0

	thumb_func_start ov11_02241A5C
ov11_02241A5C: ; 0x02241A5C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4, #0x64]
	add r5, r0, #0
	add r0, r4, #0
	bl ov11_02249D90
	ldr r1, _02241B60 ; =0x0000213C
	lsl r0, r0, #0x18
	ldr r3, [r4, r1]
	mov r2, #0x20
	lsr r0, r0, #0x18
	tst r2, r3
	bne _02241A82
	add r1, r1, #4
	ldr r2, [r4, r1]
	mov r1, #4
	tst r1, r2
	beq _02241AC4
_02241A82:
	cmp r0, #0x36
	beq _02241A8E
	cmp r0, #0x72
	beq _02241A8E
	cmp r0, #0x7c
	bne _02241AB6
_02241A8E:
	mov r0, #0xc1
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	cmp r0, #0xa5
	beq _02241AC4
	cmp r0, #0xe2
	bne _02241AA8
	mov r1, #0x85
	lsl r1, r1, #6
	ldr r2, [r4, r1]
	mov r1, #0x40
	tst r1, r2
	bne _02241AC4
_02241AA8:
	ldr r2, [r4, #0x64]
	mov r1, #0xc0
	mul r1, r2
	add r2, r4, r1
	ldr r1, _02241B64 ; =0x00002DF8
	strh r0, [r2, r1]
	b _02241AC4
_02241AB6:
	ldr r2, [r4, #0x64]
	mov r1, #0xc0
	mul r1, r2
	add r2, r4, r1
	ldr r1, _02241B64 ; =0x00002DF8
	mov r0, #0
	strh r0, [r2, r1]
_02241AC4:
	ldr r0, _02241B60 ; =0x0000213C
	mov r1, #1
	ldr r2, [r4, r0]
	lsl r1, r1, #0x14
	tst r1, r2
	bne _02241B2C
	add r0, r0, #4
	ldr r1, [r4, r0]
	mov r0, #4
	tst r0, r1
	beq _02241AF2
	ldr r2, [r4, #0x64]
	ldr r1, _02241B68 ; =0x00003044
	lsl r2, r2, #1
	add r3, r4, r2
	add r2, r1, #0
	ldr r0, [r4, r1]
	add r2, #0x18
	strh r0, [r3, r2]
	sub r0, r1, #4
	ldr r2, [r4, r0]
	add r0, r1, #4
	b _02241B00
_02241AF2:
	ldr r0, [r4, #0x64]
	mov r2, #0
	lsl r0, r0, #1
	add r1, r4, r0
	ldr r0, _02241B6C ; =0x0000305C
	strh r2, [r1, r0]
	sub r0, #0x14
_02241B00:
	str r2, [r4, r0]
	mov r0, #0x85
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r0, #0x40
	tst r0, r1
	beq _02241B20
	mov r0, #0xc1
	ldr r1, [r4, #0x64]
	lsl r0, r0, #6
	ldr r2, [r4, r0]
	lsl r1, r1, #1
	add r1, r4, r1
	add r0, #0x3c
	strh r2, [r1, r0]
	b _02241B2C
_02241B20:
	ldr r0, [r4, #0x64]
	mov r2, #0
	lsl r0, r0, #1
	add r1, r4, r0
	ldr r0, _02241B70 ; =0x0000307C
	strh r2, [r1, r0]
_02241B2C:
	mov r0, #0x85
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r0, #4
	tst r0, r1
	beq _02241B48
	mov r0, #0xc1
	ldr r1, [r4, #0x64]
	lsl r0, r0, #6
	ldr r2, [r4, r0]
	lsl r1, r1, #1
	add r1, r4, r1
	add r0, #0x6c
	strh r2, [r1, r0]
_02241B48:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0224256C
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0224ABF8
	mov r0, #0x27
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
	nop
_02241B60: .word 0x0000213C
_02241B64: .word 0x00002DF8
_02241B68: .word 0x00003044
_02241B6C: .word 0x0000305C
_02241B70: .word 0x0000307C

	thumb_func_start ov11_02241B74
ov11_02241B74: ; 0x02241B74
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov11_0222FF74
	mov r1, #0x22
	lsl r1, r1, #4
	tst r0, r1
	bne _02241BF6
	ldr r2, [r4, #0x64]
	add r0, r5, #0
	add r1, r4, #0
	mov r3, #0
	bl ov11_02248898
	cmp r0, #1
	beq _02241C4C
	ldr r2, [r4, #0x6c]
	cmp r2, #0xff
	beq _02241BAA
	add r0, r5, #0
	add r1, r4, #0
	mov r3, #0
	bl ov11_02248898
	cmp r0, #1
	beq _02241C4C
_02241BAA:
	ldr r1, [r4, #8]
	add r0, r4, #0
	add r2, r1, #0
	bl ov11_02242510
	cmp r0, #1
	beq _02241C4C
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02241FD8
	cmp r0, #1
	beq _02241C4C
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_022476DC
	add r2, r0, #0
	beq _02241BE2
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
_02241BE2:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02242924
	cmp r0, #1
	beq _02241C4C
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02242404
_02241BF6:
	add r1, r4, #0
	add r1, #0xec
	ldr r1, [r1]
	mov r0, #0x27
	add r2, r4, r1
	ldr r1, _02241C50 ; =0x000021E8
	ldrb r2, [r2, r1]
	sub r1, #0x40
	lsl r2, r2, #4
	add r2, r4, r2
	str r0, [r2, r1]
	ldr r1, [r4, #0x64]
	mov r0, #0x1c
	mul r0, r1
	add r1, r4, r0
	mov r0, #0xb5
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	beq _02241C34
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0224C178
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0224728C
	mov r1, #0
	b _02241C3C
_02241C34:
	add r0, r4, #0
	add r0, #0xec
	ldr r0, [r0]
	add r1, r0, #1
_02241C3C:
	add r0, r4, #0
	add r0, #0xec
	str r1, [r0]
	add r0, r4, #0
	bl ov11_02245494
	mov r0, #8
	str r0, [r4, #8]
_02241C4C:
	pop {r3, r4, r5, pc}
	nop
_02241C50: .word 0x000021E8

	thumb_func_start ov11_02241C54
ov11_02241C54: ; 0x02241C54
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4, #8]
	add r0, r4, #0
	add r2, r1, #0
	mov r3, #1
	bl ov11_0224246C
	cmp r0, #1
	beq _02241C6C
	mov r0, #0x27
	str r0, [r4, #8]
_02241C6C:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_02241C70
ov11_02241C70: ; 0x02241C70
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov11_0223145C
	mov r1, #0x80
	tst r0, r1
	beq _02241C86
	mov r0, #0x2a
	str r0, [r4, #8]
	b _02241CE4
_02241C86:
	add r0, r5, #0
	bl ov11_0223145C
	cmp r0, #2
	beq _02241C9A
	add r0, r5, #0
	bl ov11_0223145C
	cmp r0, #3
	bne _02241CAE
_02241C9A:
	add r0, r4, #0
	mov r1, #1
	mov r2, #5
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x2a
	str r0, [r4, #0xc]
	b _02241CE4
_02241CAE:
	add r0, r5, #0
	bl ov11_0223145C
	cmp r0, #1
	bne _02241CCC
	add r0, r4, #0
	mov r1, #1
	mov r2, #4
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #0x2a
	str r0, [r4, #0xc]
	b _02241CE4
_02241CCC:
	add r0, r5, #0
	bl ov11_0223145C
	cmp r0, #4
	beq _02241CE0
	add r0, r5, #0
	bl ov11_0223145C
	cmp r0, #5
	bne _02241CE4
_02241CE0:
	mov r0, #0x2a
	str r0, [r4, #8]
_02241CE4:
	ldr r0, _02241CEC ; =0x0000311F
	mov r1, #1
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
	.align 2, 0
_02241CEC: .word 0x0000311F

	thumb_func_start ov11_02241CF0
ov11_02241CF0: ; 0x02241CF0
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	bl ov11_0222FF74
	mov r1, #4
	add r4, r0, #0
	and r4, r1
	bne _02241D16
	add r0, r6, #0
	mov r1, #0
	bl ov11_0222FF88
	add r6, r0, #0
	bl Party_GivePokerusAtRandom
	add r0, r6, #0
	bl Party_SpreadPokerus
_02241D16:
	cmp r4, #0
	beq _02241D20
	mov r0, #0x16
	bl sub_020311DC
_02241D20:
	mov r0, #0x2b
	str r0, [r5, #8]
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_02241D28
ov11_02241D28: ; 0x02241D28
	bx lr
	.align 2, 0

	thumb_func_start ov11_02241D2C
ov11_02241D2C: ; 0x02241D2C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	str r1, [sp, #4]
	mov r1, #0
	str r0, [sp]
	str r1, [sp, #0x30]
	bl ov11_0222FF84
	str r0, [sp, #0x28]
	ldr r0, [sp]
	bl ov11_0222FF74
	str r0, [sp, #0x24]
	ldr r0, [sp, #4]
	ldr r0, [r0, #8]
	str r0, [sp, #0x20]
	mov r0, #0
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x28]
	cmp r0, #0
	bgt _02241D58
	b _02241F4A
_02241D58:
	ldr r0, [sp, #4]
	mov r1, #2
	str r0, [sp, #0x1c]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x24]
	and r0, r1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x24]
	mov r1, #0x18
	and r0, r1
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x24]
	mov r1, #0x10
	and r0, r1
	str r0, [sp, #0xc]
_02241D76:
	mov r1, #0x4f
	ldr r0, [sp, #0x1c]
	lsl r1, r1, #2
	ldr r2, [r0, r1]
	mov r0, #1
	bic r2, r0
	ldr r0, [sp, #0x1c]
	str r2, [r0, r1]
	ldr r0, [sp, #0x14]
	cmp r0, #0
	beq _02241D92
	ldr r0, [sp, #0x10]
	cmp r0, #0
	beq _02241DA4
_02241D92:
	ldr r0, [sp, #0xc]
	cmp r0, #0
	beq _02241E8A
	ldr r0, [sp]
	ldr r1, [sp, #0x2c]
	bl ov11_02230270
	cmp r0, #0
	bne _02241E8A
_02241DA4:
	ldr r3, _02241FC8 ; =0x00002D8C
	ldr r0, [sp, #0x18]
	ldr r0, [r0, r3]
	cmp r0, #0
	bne _02241DCC
	ldr r1, [sp, #0x2c]
	mov r2, #2
	add r4, r1, #0
	eor r4, r2
	mov r1, #0xc0
	add r5, r4, #0
	mul r5, r1
	ldr r1, [sp, #4]
	add r1, r1, r5
	ldr r1, [r1, r3]
	cmp r1, #0
	bne _02241DCC
	ldr r1, [sp, #0x2c]
	tst r1, r2
	bne _02241DD0
_02241DCC:
	cmp r0, #0
	beq _02241DD2
_02241DD0:
	b _02241F30
_02241DD2:
	ldr r0, [sp]
	ldr r1, [sp, #0x2c]
	mov r7, #0
	bl ov11_0222FF88
	add r6, r0, #0
	ldr r0, [sp]
	ldr r1, [sp, #0x2c]
	bl ov11_0222FF7C
	add r0, r6, #0
	add r5, r7, #0
	bl GetPartyCount
	cmp r0, #0
	ble _02241E4A
	ldr r0, [sp, #0x2c]
	mov r1, #2
	eor r1, r0
	ldr r0, [sp, #4]
	add r0, r0, r1
	str r0, [sp, #8]
_02241DFE:
	add r0, r6, #0
	add r1, r5, #0
	bl Party_GetMonByIndex
	mov r1, #0xad
	mov r2, #0
	add r4, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _02241E3E
	add r0, r4, #0
	mov r1, #0xad
	mov r2, #0
	bl GetMonData
	ldr r1, _02241FCC ; =0x000001EE
	cmp r0, r1
	beq _02241E3E
	add r0, r4, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _02241E3E
	ldr r2, [sp, #8]
	ldr r1, _02241FD0 ; =0x0000219C
	ldrb r1, [r2, r1]
	cmp r5, r1
	beq _02241E3E
	add r7, r7, r0
_02241E3E:
	add r0, r6, #0
	add r5, r5, #1
	bl GetPartyCount
	cmp r5, r0
	blt _02241DFE
_02241E4A:
	cmp r7, #0
	bne _02241E6E
	ldr r0, [sp, #0x2c]
	bl MaskOfFlagNo
	ldr r2, _02241FD4 ; =0x00003108
	ldr r1, [sp, #4]
	ldrb r1, [r1, r2]
	orr r1, r0
	ldr r0, [sp, #4]
	strb r1, [r0, r2]
	add r1, r0, #0
	ldr r0, [sp, #0x2c]
	mov r2, #6
	add r1, r1, r0
	ldr r0, _02241FD0 ; =0x0000219C
	strb r2, [r1, r0]
	b _02241F30
_02241E6E:
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #4]
	str r1, [r0, #0xc]
	mov r1, #0x15
	str r1, [r0, #8]
	mov r1, #0x4f
	ldr r0, [sp, #0x1c]
	lsl r1, r1, #2
	ldr r2, [r0, r1]
	mov r0, #1
	orr r2, r0
	ldr r0, [sp, #0x1c]
	str r2, [r0, r1]
	b _02241F30
_02241E8A:
	ldr r1, _02241FC8 ; =0x00002D8C
	ldr r0, [sp, #0x18]
	ldr r0, [r0, r1]
	cmp r0, #0
	bne _02241F30
	ldr r0, [sp]
	ldr r1, [sp, #0x2c]
	mov r7, #0
	bl ov11_0222FF88
	add r6, r0, #0
	ldr r0, [sp]
	ldr r1, [sp, #0x2c]
	bl ov11_0222FF7C
	add r0, r6, #0
	add r5, r7, #0
	bl GetPartyCount
	cmp r0, #0
	ble _02241EF2
_02241EB4:
	add r0, r6, #0
	add r1, r5, #0
	bl Party_GetMonByIndex
	mov r1, #0xad
	mov r2, #0
	add r4, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _02241EE6
	add r0, r4, #0
	mov r1, #0xad
	mov r2, #0
	bl GetMonData
	ldr r1, _02241FCC ; =0x000001EE
	cmp r0, r1
	beq _02241EE6
	add r0, r4, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	add r7, r7, r0
_02241EE6:
	add r0, r6, #0
	add r5, r5, #1
	bl GetPartyCount
	cmp r5, r0
	blt _02241EB4
_02241EF2:
	cmp r7, #0
	bne _02241F16
	ldr r0, [sp, #0x2c]
	bl MaskOfFlagNo
	ldr r2, _02241FD4 ; =0x00003108
	ldr r1, [sp, #4]
	ldrb r1, [r1, r2]
	orr r1, r0
	ldr r0, [sp, #4]
	strb r1, [r0, r2]
	add r1, r0, #0
	ldr r0, [sp, #0x2c]
	mov r2, #6
	add r1, r1, r0
	ldr r0, _02241FD0 ; =0x0000219C
	strb r2, [r1, r0]
	b _02241F30
_02241F16:
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #4]
	str r1, [r0, #0xc]
	mov r1, #0x15
	str r1, [r0, #8]
	mov r1, #0x4f
	ldr r0, [sp, #0x1c]
	lsl r1, r1, #2
	ldr r2, [r0, r1]
	mov r0, #1
	orr r2, r0
	ldr r0, [sp, #0x1c]
	str r2, [r0, r1]
_02241F30:
	ldr r0, [sp, #0x1c]
	add r0, r0, #4
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r0, #0xc0
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x2c]
	add r1, r0, #1
	ldr r0, [sp, #0x28]
	str r1, [sp, #0x2c]
	cmp r1, r0
	bge _02241F4A
	b _02241D76
_02241F4A:
	ldr r0, [sp, #4]
	ldr r0, [r0, #8]
	cmp r0, #0x15
	bne _02241FC0
	ldr r0, [sp, #0x24]
	mov r1, #0x86
	tst r0, r1
	bne _02241FB2
	ldr r0, [sp]
	bl ov11_02230E70
	cmp r0, #0
	bne _02241FB2
	mov r1, #0x4f
	ldr r0, [sp, #4]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r2, #1
	tst r0, r2
	beq _02241F7C
	ldr r0, [sp, #4]
	add r1, r1, #4
	ldr r0, [r0, r1]
	tst r0, r2
	bne _02241FB2
_02241F7C:
	ldr r0, [sp]
	ldr r1, [sp, #4]
	mov r2, #0
	bl ov11_02246DE0
	cmp r0, #0
	beq _02241FB2
	mov r1, #0x4f
	ldr r0, [sp, #4]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r2, #1
	tst r0, r2
	beq _02241FA0
	mov r2, #0
	sub r1, r1, #4
	ldr r0, [sp, #4]
	b _02241FA4
_02241FA0:
	ldr r0, [sp, #4]
	sub r1, r1, #4
_02241FA4:
	str r2, [r0, r1]
	ldr r0, [sp, #4]
	mov r1, #1
	mov r2, #0xe7
	bl ov11_022431DC
	b _02241FBC
_02241FB2:
	ldr r0, [sp, #4]
	mov r1, #1
	mov r2, #0xa
	bl ov11_022431DC
_02241FBC:
	mov r0, #1
	str r0, [sp, #0x30]
_02241FC0:
	ldr r0, [sp, #0x30]
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	nop
_02241FC8: .word 0x00002D8C
_02241FCC: .word 0x000001EE
_02241FD0: .word 0x0000219C
_02241FD4: .word 0x00003108

	thumb_func_start ov11_02241FD8
ov11_02241FD8: ; 0x02241FD8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	str r0, [sp]
	str r1, [sp, #4]
	bl ov11_0222FF84
	str r0, [sp, #0x24]
	ldr r0, [sp]
	bl ov11_0222FF74
	str r0, [sp, #0x20]
	mov r0, #0
	str r0, [sp, #0x1c]
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x24]
	cmp r0, #0
	bgt _02241FFC
	b _02242256
_02241FFC:
	ldr r0, [sp, #0x20]
	mov r1, #8
	and r0, r1
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x20]
	mov r1, #0x10
	and r0, r1
	str r0, [sp, #8]
_0224200C:
	ldr r0, [sp, #0x20]
	sub r0, #0x4a
	cmp r0, #1
	bhi _022420A6
	ldr r0, [sp]
	ldr r1, [sp, #0x28]
	bl ov11_02230270
	cmp r0, #0
	bne _022420A6
	ldr r0, [sp]
	ldr r1, [sp, #0x28]
	bl ov11_02230260
	cmp r0, #2
	bne _022420C8
	ldr r1, _0224233C ; =0x00002D8C
	ldr r0, [sp, #4]
	ldr r0, [r0, r1]
	cmp r0, #0
	bne _022420C8
	ldr r0, [sp]
	ldr r1, [sp, #0x28]
	mov r7, #0
	bl ov11_0222FF88
	add r6, r0, #0
	ldr r0, [sp]
	ldr r1, [sp, #0x28]
	bl ov11_0222FF7C
	add r0, r6, #0
	add r4, r7, #0
	bl GetPartyCount
	cmp r0, #0
	ble _02242094
_02242056:
	add r0, r6, #0
	add r1, r4, #0
	bl Party_GetMonByIndex
	mov r1, #0xad
	mov r2, #0
	add r5, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _02242088
	add r0, r5, #0
	mov r1, #0xad
	mov r2, #0
	bl GetMonData
	ldr r1, _02242340 ; =0x000001EE
	cmp r0, r1
	beq _02242088
	add r0, r5, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	add r7, r7, r0
_02242088:
	add r0, r6, #0
	add r4, r4, #1
	bl GetPartyCount
	cmp r4, r0
	blt _02242056
_02242094:
	cmp r7, #0
	bne _022420C8
	ldr r0, [sp, #0x1c]
	mov r1, #2
	orr r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x1c]
	b _02242242
_022420A6:
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bne _022420BE
	ldr r0, [sp, #8]
	cmp r0, #0
	beq _022421B0
	ldr r0, [sp]
	ldr r1, [sp, #0x28]
	bl ov11_02230270
	cmp r0, #0
	beq _022421B0
_022420BE:
	ldr r1, _0224233C ; =0x00002D8C
	ldr r0, [sp, #4]
	ldr r0, [r0, r1]
	cmp r0, #0
	beq _022420CA
_022420C8:
	b _02242242
_022420CA:
	ldr r0, [sp]
	ldr r1, [sp, #0x28]
	mov r5, #0
	bl ov11_0222FF88
	add r7, r0, #0
	ldr r0, [sp]
	ldr r1, [sp, #0x28]
	bl ov11_022302BC
	add r1, r0, #0
	ldr r0, [sp]
	bl ov11_0222FF88
	str r0, [sp, #0x18]
	ldr r0, [sp]
	ldr r1, [sp, #0x28]
	bl ov11_0222FF7C
	str r0, [sp, #0x14]
	add r0, r7, #0
	add r4, r5, #0
	bl GetPartyCount
	cmp r0, #0
	ble _0224213C
_022420FE:
	add r0, r7, #0
	add r1, r4, #0
	bl Party_GetMonByIndex
	mov r1, #0xad
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _02242130
	add r0, r6, #0
	mov r1, #0xad
	mov r2, #0
	bl GetMonData
	ldr r1, _02242340 ; =0x000001EE
	cmp r0, r1
	beq _02242130
	add r0, r6, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	add r5, r5, r0
_02242130:
	add r0, r7, #0
	add r4, r4, #1
	bl GetPartyCount
	cmp r4, r0
	blt _022420FE
_0224213C:
	ldr r0, [sp, #0x18]
	mov r4, #0
	bl GetPartyCount
	cmp r0, #0
	ble _02242186
	ldr r7, _02242340 ; =0x000001EE
_0224214A:
	ldr r0, [sp, #0x18]
	add r1, r4, #0
	bl Party_GetMonByIndex
	mov r1, #0xad
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _0224217A
	add r0, r6, #0
	mov r1, #0xad
	mov r2, #0
	bl GetMonData
	cmp r0, r7
	beq _0224217A
	add r0, r6, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	add r5, r5, r0
_0224217A:
	ldr r0, [sp, #0x18]
	add r4, r4, #1
	bl GetPartyCount
	cmp r4, r0
	blt _0224214A
_02242186:
	cmp r5, #0
	bne _02242242
	ldr r0, [sp, #0x14]
	bl ov11_02253A4C
	mov r1, #1
	tst r0, r1
	beq _022421A2
	ldr r0, [sp, #0x1c]
	orr r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x1c]
	b _02242242
_022421A2:
	ldr r0, [sp, #0x1c]
	mov r1, #2
	orr r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x1c]
	b _02242242
_022421B0:
	ldr r1, _0224233C ; =0x00002D8C
	ldr r0, [sp, #4]
	ldr r0, [r0, r1]
	cmp r0, #0
	bne _02242242
	ldr r0, [sp]
	ldr r1, [sp, #0x28]
	mov r7, #0
	bl ov11_0222FF88
	add r6, r0, #0
	ldr r0, [sp]
	ldr r1, [sp, #0x28]
	bl ov11_0222FF7C
	str r0, [sp, #0x10]
	add r0, r6, #0
	add r4, r7, #0
	bl GetPartyCount
	cmp r0, #0
	ble _0224221A
_022421DC:
	add r0, r6, #0
	add r1, r4, #0
	bl Party_GetMonByIndex
	mov r1, #0xad
	mov r2, #0
	add r5, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _0224220E
	add r0, r5, #0
	mov r1, #0xad
	mov r2, #0
	bl GetMonData
	ldr r1, _02242340 ; =0x000001EE
	cmp r0, r1
	beq _0224220E
	add r0, r5, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	add r7, r7, r0
_0224220E:
	add r0, r6, #0
	add r4, r4, #1
	bl GetPartyCount
	cmp r4, r0
	blt _022421DC
_0224221A:
	cmp r7, #0
	bne _02242242
	ldr r0, [sp, #0x10]
	bl ov11_02253A4C
	mov r1, #1
	tst r0, r1
	beq _02242236
	ldr r0, [sp, #0x1c]
	orr r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x1c]
	b _02242242
_02242236:
	ldr r0, [sp, #0x1c]
	mov r1, #2
	orr r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x1c]
_02242242:
	ldr r0, [sp, #4]
	add r0, #0xc0
	str r0, [sp, #4]
	ldr r0, [sp, #0x28]
	add r1, r0, #1
	ldr r0, [sp, #0x24]
	str r1, [sp, #0x28]
	cmp r1, r0
	bge _02242256
	b _0224200C
_02242256:
	ldr r0, [sp, #0x1c]
	cmp r0, #1
	bne _0224226C
	ldr r0, [sp, #0x20]
	mov r1, #1
	tst r0, r1
	beq _0224226C
	ldr r0, [sp, #0x20]
	mov r1, #4
	tst r0, r1
	beq _02242282
_0224226C:
	ldr r0, [sp, #0x1c]
	cmp r0, #1
	bne _0224231C
	ldr r0, [sp, #0x20]
	mov r1, #0x80
	tst r0, r1
	beq _0224231C
	ldr r0, [sp, #0x20]
	mov r1, #4
	tst r0, r1
	bne _0224231C
_02242282:
	ldr r0, [sp]
	mov r1, #1
	bl ov11_02230188
	ldrb r0, [r0, #1]
	sub r0, #0x3e
	cmp r0, #0x23
	bhi _0224230E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224229E: ; jump table
	.short _022422E6 - _0224229E - 2 ; case 0
	.short _0224230E - _0224229E - 2 ; case 1
	.short _022422E6 - _0224229E - 2 ; case 2
	.short _02242306 - _0224229E - 2 ; case 3
	.short _02242306 - _0224229E - 2 ; case 4
	.short _02242306 - _0224229E - 2 ; case 5
	.short _02242306 - _0224229E - 2 ; case 6
	.short _022422EE - _0224229E - 2 ; case 7
	.short _0224230E - _0224229E - 2 ; case 8
	.short _0224230E - _0224229E - 2 ; case 9
	.short _022422F6 - _0224229E - 2 ; case 10
	.short _022422F6 - _0224229E - 2 ; case 11
	.short _022422E6 - _0224229E - 2 ; case 12
	.short _022422E6 - _0224229E - 2 ; case 13
	.short _022422E6 - _0224229E - 2 ; case 14
	.short _022422E6 - _0224229E - 2 ; case 15
	.short _022422E6 - _0224229E - 2 ; case 16
	.short _022422E6 - _0224229E - 2 ; case 17
	.short _0224230E - _0224229E - 2 ; case 18
	.short _0224230E - _0224229E - 2 ; case 19
	.short _0224230E - _0224229E - 2 ; case 20
	.short _0224230E - _0224229E - 2 ; case 21
	.short _0224230E - _0224229E - 2 ; case 22
	.short _0224230E - _0224229E - 2 ; case 23
	.short _022422FE - _0224229E - 2 ; case 24
	.short _022422F6 - _0224229E - 2 ; case 25
	.short _022422F6 - _0224229E - 2 ; case 26
	.short _022422F6 - _0224229E - 2 ; case 27
	.short _0224230E - _0224229E - 2 ; case 28
	.short _0224230E - _0224229E - 2 ; case 29
	.short _0224230E - _0224229E - 2 ; case 30
	.short _0224230E - _0224229E - 2 ; case 31
	.short _0224230E - _0224229E - 2 ; case 32
	.short _0224230E - _0224229E - 2 ; case 33
	.short _0224230E - _0224229E - 2 ; case 34
	.short _022422E6 - _0224229E - 2 ; case 35
_022422E6:
	ldr r0, _02242344 ; =0x00000469
	bl sub_0200521C
	b _02242314
_022422EE:
	ldr r0, _02242348 ; =0x0000046A
	bl sub_0200521C
	b _02242314
_022422F6:
	ldr r0, _0224234C ; =0x0000046B
	bl sub_0200521C
	b _02242314
_022422FE:
	ldr r0, _02242350 ; =0x0000046C
	bl sub_0200521C
	b _02242314
_02242306:
	ldr r0, _02242354 ; =0x0000046D
	bl sub_0200521C
	b _02242314
_0224230E:
	ldr r0, _02242358 ; =0x00000468
	bl sub_0200521C
_02242314:
	ldr r0, [sp]
	mov r1, #2
	bl ov11_02231484
_0224231C:
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	beq _0224232A
	ldr r0, [sp]
	ldr r1, [sp, #0x1c]
	bl ov11_02231468
_0224232A:
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	beq _02242336
	add sp, #0x2c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02242336:
	mov r0, #0
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224233C: .word 0x00002D8C
_02242340: .word 0x000001EE
_02242344: .word 0x00000469
_02242348: .word 0x0000046A
_0224234C: .word 0x0000046B
_02242350: .word 0x0000046C
_02242354: .word 0x0000046D
_02242358: .word 0x00000468

	thumb_func_start ov11_0224235C
ov11_0224235C: ; 0x0224235C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp]
	add r5, r1, #0
	ldr r0, _022423F4 ; =0x00002D4C
	add r6, r2, #0
	mov r1, #0xc0
	add r0, r5, r0
	mul r1, r6
	add r0, r0, r1
	str r0, [sp, #8]
	ldr r0, [sp, #0x2c]
	ldr r1, [sp, #8]
	lsl r0, r0, #1
	ldrh r1, [r1, r0]
	str r3, [sp, #4]
	ldr r4, [sp, #0x28]
	ldr r7, [sp, #0x30]
	str r0, [sp, #0xc]
	cmp r1, #0xae
	bne _02242396
	add r0, r5, #0
	bl ov11_02246C20
	cmp r0, #0
	bne _02242396
	mov r0, #0x10
	str r0, [r4]
	b _022423A6
_02242396:
	ldr r1, [sp, #8]
	ldr r0, [sp, #0xc]
	ldrh r0, [r1, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _022423F8 ; =0x000003E6
	ldrh r0, [r1, r0]
	str r0, [r4]
_022423A6:
	ldr r0, [sp, #4]
	mov r1, #2
	tst r0, r1
	beq _022423DC
	ldr r0, [r4]
	add r1, #0xfe
	cmp r0, r1
	bne _022423D6
	ldr r0, [sp]
	add r1, r6, #0
	bl ov11_022302BC
	bl MaskOfFlagNo
	ldr r1, _022423FC ; =0x00003108
	ldrb r1, [r5, r1]
	tst r0, r1
	bne _022423D0
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_022423D0:
	add sp, #0x10
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_022423D6:
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_022423DC:
	ldr r1, [r4]
	ldr r0, _02242400 ; =0x00000251
	tst r0, r1
	beq _022423E8
	str r6, [r7]
	b _022423EE
_022423E8:
	mov r0, #1
	eor r0, r6
	str r0, [r7]
_022423EE:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022423F4: .word 0x00002D4C
_022423F8: .word 0x000003E6
_022423FC: .word 0x00003108
_02242400: .word 0x00000251

	thumb_func_start ov11_02242404
ov11_02242404: ; 0x02242404
	push {r3, r4, r5, r6, r7, lr}
	str r1, [sp]
	bl ov11_0222FF84
	add r4, r0, #0
	mov r3, #0
	cmp r4, #0
	ble _0224243E
	ldr r5, [sp]
	add r7, r3, #0
	add r6, r5, #0
_0224241A:
	ldr r0, _02242460 ; =0x00002DB0
	add r3, r3, #1
	ldr r2, [r6, r0]
	ldr r0, _02242464 ; =0x0000218C
	ldr r1, [r5, r0]
	mov r0, #0
	mvn r0, r0
	eor r0, r1
	add r1, r2, #0
	and r1, r0
	ldr r0, _02242460 ; =0x00002DB0
	str r1, [r6, r0]
	ldr r0, _02242464 ; =0x0000218C
	add r6, #0xc0
	str r7, [r5, r0]
	add r5, r5, #4
	cmp r3, r4
	blt _0224241A
_0224243E:
	ldr r1, [sp]
	mov r0, #0
	ldr r1, [r1, #0x64]
	lsl r2, r1, #1
	ldr r1, [sp]
	add r1, r1, r2
	ldr r2, _02242468 ; =0x00003064
	strh r0, [r1, r2]
	ldr r1, [sp]
	add r2, #0x60
	ldr r1, [r1, #0x64]
	lsl r3, r1, #1
	ldr r1, [sp]
	add r1, r1, r3
	strh r0, [r1, r2]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02242460: .word 0x00002DB0
_02242464: .word 0x0000218C
_02242468: .word 0x00003064

	thumb_func_start ov11_0224246C
ov11_0224246C: ; 0x0224246C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, _02242504 ; =0x000021EC
	str r1, [sp]
	ldrb r0, [r5, r0]
	add r6, r2, #0
	str r3, [sp, #4]
	mov r4, #0
	bl MaskOfFlagNo
	ldr r1, _02242508 ; =0x0000213C
	lsl r0, r0, #0x18
	ldr r2, [r5, r1]
	mov r1, #0xf
	lsl r1, r1, #0x18
	tst r1, r2
	beq _022424FA
	add r1, r2, #0
	tst r1, r0
	bne _022424AE
	ldr r7, _02242504 ; =0x000021EC
	add r6, r7, #0
	sub r6, #0xb0
_0224249C:
	add r4, r4, #1
	add r0, r5, r4
	ldrb r0, [r0, r7]
	bl MaskOfFlagNo
	ldr r1, [r5, r6]
	lsl r0, r0, #0x18
	tst r1, r0
	beq _0224249C
_022424AE:
	ldr r2, _02242508 ; =0x0000213C
	mov r1, #0
	mvn r1, r1
	eor r1, r0
	ldr r3, [r5, r2]
	asr r0, r0, #0x18
	and r1, r3
	str r1, [r5, r2]
	bl LowestFlagNo
	str r0, [r5, #0x74]
	ldr r0, [sp, #4]
	cmp r0, #1
	bne _022424D6
	add r0, r5, #0
	mov r1, #1
	mov r2, #6
	bl ov11_022431DC
	b _022424E0
_022424D6:
	add r0, r5, #0
	mov r1, #1
	mov r2, #0x53
	bl ov11_022431DC
_022424E0:
	mov r0, #0x15
	str r0, [r5, #8]
	ldr r0, [sp]
	mov r2, #0x27
	str r0, [r5, #0xc]
	ldr r0, [r5, #0x74]
	add sp, #8
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _0224250C ; =0x000021A8
	str r2, [r1, r0]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_022424FA:
	str r6, [r5, #8]
	add r0, r4, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02242504: .word 0x000021EC
_02242508: .word 0x0000213C
_0224250C: .word 0x000021A8

	thumb_func_start ov11_02242510
ov11_02242510: ; 0x02242510
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x85
	lsl r0, r0, #6
	add r4, r1, #0
	ldr r1, [r5, r0]
	mov r0, #0xf
	lsl r0, r0, #0x1c
	tst r0, r1
	beq _02242564
	mov r0, #1
	lsl r0, r0, #0x1c
	add r2, r1, #0
	tst r2, r0
	bne _02242536
_0224252E:
	lsl r0, r0, #1
	add r2, r1, #0
	tst r2, r0
	beq _0224252E
_02242536:
	mov r2, #0x85
	lsl r2, r2, #6
	mov r1, #0
	mvn r1, r1
	eor r1, r0
	ldr r3, [r5, r2]
	asr r0, r0, #0x1c
	and r1, r3
	str r1, [r5, r2]
	bl LowestFlagNo
	mov r2, #0x45
	str r0, [r5, #0x74]
	add r0, r5, #0
	mov r1, #1
	lsl r2, r2, #2
	bl ov11_022431DC
	mov r0, #0x15
	str r0, [r5, #8]
	str r4, [r5, #0xc]
	mov r0, #1
	pop {r3, r4, r5, pc}
_02242564:
	str r2, [r5, #8]
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_0224256C
ov11_0224256C: ; 0x0224256C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl ov11_02246D1C
	cmp r0, #0x60
	bne _02242580
	mov r4, #0
	b _02242594
_02242580:
	ldr r0, _0224274C ; =0x00002160
	ldr r4, [r5, r0]
	cmp r4, #0
	bne _02242594
	ldr r0, _02242750 ; =0x00003044
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _02242754 ; =0x000003E2
	ldrb r4, [r1, r0]
_02242594:
	mov r0, #0xc1
	lsl r0, r0, #6
	ldr r2, [r5, r0]
	mov r6, #0x10
	lsl r1, r2, #4
	add r3, r5, r1
	ldr r1, _02242758 ; =0x000003E9
	ldrb r1, [r3, r1]
	tst r1, r6
	beq _022425DE
	ldr r3, _0224275C ; =0x0000213C
	lsl r6, r6, #0x10
	ldr r1, [r5, r3]
	tst r1, r6
	bne _022425DE
	ldr r1, [r5, #0x6c]
	cmp r1, #0xff
	beq _022425DE
	add r3, r3, #4
	ldr r6, [r5, r3]
	mov r3, #4
	tst r3, r6
	beq _022425DE
	lsl r1, r1, #1
	add r3, r5, r1
	add r1, r0, #0
	add r1, #0x44
	strh r2, [r3, r1]
	ldr r2, [r5, #0x6c]
	ldr r1, [r5, r0]
	lsl r2, r2, #3
	add r3, r5, r2
	ldr r2, [r5, #0x64]
	add r0, #0x4c
	lsl r2, r2, #1
	add r2, r3, r2
	strh r1, [r2, r0]
_022425DE:
	ldr r1, [r5, #0x6c]
	cmp r1, #0xff
	beq _02242628
	add r0, r5, #0
	bl ov11_02249D90
	ldr r1, _0224275C ; =0x0000213C
	lsl r0, r0, #0x18
	ldr r3, [r5, r1]
	mov r2, #0x20
	lsr r0, r0, #0x18
	tst r2, r3
	bne _02242602
	add r1, r1, #4
	ldr r2, [r5, r1]
	mov r1, #4
	tst r1, r2
	beq _0224261C
_02242602:
	cmp r0, #0x36
	beq _0224261C
	cmp r0, #0x72
	beq _0224261C
	cmp r0, #0x7c
	beq _0224261C
	ldr r1, [r5, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _02242760 ; =0x00002DF8
	mov r2, #0
	strh r2, [r1, r0]
_0224261C:
	ldr r0, _0224275C ; =0x0000213C
	mov r1, #1
	ldr r2, [r5, r0]
	lsl r1, r1, #0x14
	tst r1, r2
	beq _0224262A
_02242628:
	b _0224274A
_0224262A:
	add r0, r0, #4
	ldr r1, [r5, r0]
	mov r0, #4
	tst r0, r1
	beq _02242668
	ldr r1, [r5, #0x6c]
	ldr r0, _02242750 ; =0x00003044
	lsl r1, r1, #1
	add r2, r5, r1
	add r1, r0, #0
	ldr r3, [r5, r0]
	add r1, #0x20
	strh r3, [r2, r1]
	ldr r1, [r5, #0x6c]
	ldr r3, [r5, #0x64]
	lsl r1, r1, #1
	add r2, r5, r1
	add r1, r0, #0
	add r1, #0x28
	strh r3, [r2, r1]
	ldr r1, [r5, #0x6c]
	lsl r1, r1, #1
	add r2, r5, r1
	add r1, r0, #0
	add r1, #0x30
	strh r4, [r2, r1]
	sub r1, r0, #4
	ldr r1, [r5, r1]
	add r0, r0, #4
	str r1, [r5, r0]
	b _02242692
_02242668:
	ldr r0, [r5, #0x6c]
	ldr r3, _02242764 ; =0x00003064
	lsl r0, r0, #1
	mov r1, #0
	add r0, r5, r0
	strh r1, [r0, r3]
	ldr r2, [r5, #0x6c]
	mov r0, #0xff
	lsl r2, r2, #1
	add r6, r5, r2
	add r2, r3, #0
	add r2, #8
	strh r0, [r6, r2]
	ldr r0, [r5, #0x6c]
	lsl r0, r0, #1
	add r2, r5, r0
	add r0, r3, #0
	add r0, #0x10
	strh r1, [r2, r0]
	sub r3, #0x1c
	str r1, [r5, r3]
_02242692:
	mov r0, #0x85
	lsl r0, r0, #6
	ldr r2, [r5, r0]
	mov r1, #0x40
	tst r1, r2
	beq _02242726
	add r0, #0x2c
	ldr r0, [r5, r0]
	ldr r2, _02242768 ; =0x801FDA49
	tst r0, r2
	bne _02242726
	ldr r0, _02242750 ; =0x00003044
	ldr r0, [r5, r0]
	lsl r1, r0, #4
	add r3, r5, r1
	ldr r1, _0224276C ; =0x000003E6
	ldrh r3, [r3, r1]
	cmp r3, #0x40
	bgt _022426C8
	bge _022426DC
	cmp r3, #0x10
	bgt _022426C2
	beq _022426DC
	b _02242702
_022426C2:
	cmp r3, #0x20
	beq _022426DC
	b _02242702
_022426C8:
	lsr r1, r2, #0x17
	cmp r3, r1
	bgt _022426D6
	bge _022426DC
	cmp r3, #0x80
	beq _022426DC
	b _02242702
_022426D6:
	lsr r1, r2, #0x16
	cmp r3, r1
	bne _02242702
_022426DC:
	ldr r1, [r5, #0x6c]
	ldr r2, _02242770 ; =0x000030C4
	lsl r1, r1, #1
	mov r0, #0
	add r1, r5, r1
	strh r0, [r1, r2]
	ldr r1, [r5, #0x6c]
	mov r4, #0xff
	lsl r1, r1, #1
	add r3, r5, r1
	add r1, r2, #0
	add r1, #8
	strh r4, [r3, r1]
	ldr r1, [r5, #0x6c]
	add r2, #0x10
	lsl r1, r1, #1
	add r1, r5, r1
	strh r0, [r1, r2]
	pop {r4, r5, r6, pc}
_02242702:
	ldr r1, [r5, #0x6c]
	lsl r1, r1, #1
	add r2, r5, r1
	ldr r1, _02242770 ; =0x000030C4
	strh r0, [r2, r1]
	ldr r0, [r5, #0x6c]
	ldr r3, [r5, #0x64]
	lsl r0, r0, #1
	add r2, r5, r0
	add r0, r1, #0
	add r0, #8
	strh r3, [r2, r0]
	ldr r0, [r5, #0x6c]
	add r1, #0x10
	lsl r0, r0, #1
	add r0, r5, r0
	strh r4, [r0, r1]
	pop {r4, r5, r6, pc}
_02242726:
	ldr r1, [r5, #0x6c]
	ldr r2, _02242770 ; =0x000030C4
	lsl r1, r1, #1
	mov r0, #0
	add r1, r5, r1
	strh r0, [r1, r2]
	ldr r1, [r5, #0x6c]
	mov r4, #0xff
	lsl r1, r1, #1
	add r3, r5, r1
	add r1, r2, #0
	add r1, #8
	strh r4, [r3, r1]
	ldr r1, [r5, #0x6c]
	add r2, #0x10
	lsl r1, r1, #1
	add r1, r5, r1
	strh r0, [r1, r2]
_0224274A:
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224274C: .word 0x00002160
_02242750: .word 0x00003044
_02242754: .word 0x000003E2
_02242758: .word 0x000003E9
_0224275C: .word 0x0000213C
_02242760: .word 0x00002DF8
_02242764: .word 0x00003064
_02242768: .word 0x801FDA49
_0224276C: .word 0x000003E6
_02242770: .word 0x000030C4

	thumb_func_start ov11_02242774
ov11_02242774: ; 0x02242774
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x10
	bl ov11_022431DC
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_02242790
ov11_02242790: ; 0x02242790
	push {r3, r4, r5, lr}
	ldr r2, _022427E0 ; =0x0000216C
	add r5, r1, #0
	ldr r0, [r5, r2]
	mov r4, #0
	cmp r0, #0
	beq _022427C4
	add r1, r2, #0
	add r1, #0x11
	ldrb r1, [r5, r1]
	cmp r1, #0
	beq _022427C2
	ldr r1, [r5, #0x74]
	cmp r1, #0xff
	bne _022427BE
	add r2, #0x10
	ldrb r1, [r5, r2]
	cmp r1, #1
	beq _022427BE
	mov r1, #1
	lsl r1, r1, #0xe
	tst r0, r1
	beq _022427C4
_022427BE:
	mov r4, #1
	b _022427C4
_022427C2:
	mov r4, #1
_022427C4:
	cmp r4, #1
	bne _022427DA
	add r0, r5, #0
	mov r1, #1
	mov r2, #0x15
	bl ov11_022431DC
	ldr r0, [r5, #8]
	str r0, [r5, #0xc]
	mov r0, #0x15
	str r0, [r5, #8]
_022427DA:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_022427E0: .word 0x0000216C

	thumb_func_start ov11_022427E4
ov11_022427E4: ; 0x022427E4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	ldr r2, [r4, #0x6c]
	mov r3, #0
	cmp r2, #0xff
	bne _022427F4
	add r0, r3, #0
	pop {r3, r4, r5, r6, r7, pc}
_022427F4:
	mov r0, #0xc0
	add r5, r2, #0
	mul r5, r0
	mov r1, #2
	ldr r0, _02242864 ; =0x00002DB0
	add r7, r4, r5
	ldr r6, [r7, r0]
	lsl r1, r1, #0x16
	tst r1, r6
	beq _0224285E
	ldr r1, _02242868 ; =0x0000216C
	mov r6, #2
	lsl r6, r6, #0x16
	ldr r1, [r4, r1]
	lsr r6, r6, #9
	tst r1, r6
	bne _0224285E
	ldr r1, [r4, #0x64]
	cmp r2, r1
	beq _0224285E
	sub r0, #0x24
	ldr r0, [r7, r0]
	cmp r0, #0
	beq _0224285E
	mov r0, #0x1c
	mul r0, r2
	add r2, r4, r0
	mov r0, #0xb6
	lsl r0, r0, #2
	ldr r1, [r2, r0]
	cmp r1, #0
	bne _0224283C
	add r0, #8
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _0224285E
_0224283C:
	ldr r0, _0224286C ; =0x00002D59
	add r1, r4, r0
	ldrsb r0, [r1, r5]
	cmp r0, #0xc
	bge _0224285E
	add r0, r0, #1
	strb r0, [r1, r5]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xf5
	bl ov11_022431DC
	ldr r0, [r4, #8]
	mov r3, #1
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
_0224285E:
	add r0, r3, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02242864: .word 0x00002DB0
_02242868: .word 0x0000216C
_0224286C: .word 0x00002D59

	thumb_func_start ov11_02242870
ov11_02242870: ; 0x02242870
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	mov r4, #0
	bl ov11_02249D90
	add r7, r0, #0
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	add r2, r4, #0
	bl ov11_02249DA4
	add r6, r0, #0
	ldr r0, [r5, #0x6c]
	cmp r0, #0xff
	beq _0224290A
	cmp r7, #0x37
	bne _0224290A
	ldr r1, _02242910 ; =0x0000216C
	ldr r2, [r5, r1]
	ldr r1, _02242914 ; =0x801FDA49
	tst r1, r2
	bne _0224290A
	mov r1, #0x1c
	mul r1, r0
	mov r0, #0xb6
	add r2, r5, r1
	lsl r0, r0, #2
	ldr r1, [r2, r0]
	cmp r1, #0
	bne _022428B8
	add r0, #8
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _0224290A
_022428B8:
	bl LCRandom
	mov r1, #0x64
	bl _s32_div_f
	cmp r1, r6
	bge _0224290A
	ldr r0, _02242918 ; =0x00003044
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _0224291C ; =0x000003E9
	ldrb r1, [r1, r0]
	mov r0, #0x20
	tst r0, r1
	beq _0224290A
	ldr r0, [r5, #0x6c]
	mov r1, #0xc0
	mul r1, r0
	add r2, r5, r1
	ldr r1, _02242920 ; =0x00002D8C
	ldr r1, [r2, r1]
	cmp r1, #0
	beq _0224290A
	add r1, r5, #0
	add r1, #0x94
	str r0, [r1]
	add r0, r5, #0
	mov r1, #2
	add r0, #0x88
	str r1, [r0]
	add r0, r5, #0
	mov r1, #1
	mov r2, #0xe
	bl ov11_022431DC
	ldr r0, [r5, #8]
	mov r4, #1
	str r0, [r5, #0xc]
	mov r0, #0x15
	str r0, [r5, #8]
_0224290A:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02242910: .word 0x0000216C
_02242914: .word 0x801FDA49
_02242918: .word 0x00003044
_0224291C: .word 0x000003E9
_02242920: .word 0x00002D8C

	thumb_func_start ov11_02242924
ov11_02242924: ; 0x02242924
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldr r4, [r5, #0x5c]
	str r0, [sp]
	mov r7, #0
	bl ov11_0222FF84
	cmp r4, r0
	bge _02242994
	add r6, r5, #0
	add r6, #0x5c
_0224293A:
	mov r0, #0xc0
	mul r0, r4
	mov r1, #0xb7
	add r0, r5, r0
	lsl r1, r1, #6
	ldr r2, [r0, r1]
	ldr r1, _022429A0 ; =0x200400C0
	tst r1, r2
	bne _0224297E
	ldr r1, _022429A4 ; =0x00002DC4
	ldr r2, [r0, r1]
	ldr r1, _022429A0 ; =0x200400C0
	tst r1, r2
	beq _0224297E
	ldr r1, _022429A4 ; =0x00002DC4
	ldr r2, [r0, r1]
	ldr r1, _022429A8 ; =0xDFFBFF3F
	and r2, r1
	ldr r1, _022429A4 ; =0x00002DC4
	str r2, [r0, r1]
	ldr r2, _022429AC ; =0x0000011F
	add r0, r5, #0
	mov r1, #1
	bl ov11_022431DC
	mov r0, #0x46
	ldr r1, [r5, #0x5c]
	lsl r0, r0, #2
	str r1, [r5, r0]
	ldr r0, [r5, #8]
	mov r7, #1
	str r0, [r5, #0xc]
	mov r0, #0x15
	str r0, [r5, #8]
_0224297E:
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	cmp r7, #1
	beq _02242994
	ldr r0, [sp]
	ldr r4, [r5, #0x5c]
	bl ov11_0222FF84
	cmp r4, r0
	blt _0224293A
_02242994:
	cmp r7, #0
	bne _0224299C
	mov r0, #0
	str r0, [r5, #0x5c]
_0224299C:
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022429A0: .word 0x200400C0
_022429A4: .word 0x00002DC4
_022429A8: .word 0xDFFBFF3F
_022429AC: .word 0x0000011F

	thumb_func_start ov11_022429B0
ov11_022429B0: ; 0x022429B0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	mov r6, #0
	bl ov11_0222FF84
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl ov11_02249D90
	str r0, [sp, #4]
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	add r2, r6, #0
	bl ov11_02249DA4
	ldr r1, [r4, #8]
	str r0, [sp]
	add r0, r4, #0
	add r2, r1, #0
	mov r3, #1
	bl ov11_0224246C
	cmp r0, #1
	bne _022429E8
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_022429E8:
	add r5, r4, #0
	add r5, #0x30
_022429EC:
	ldr r0, [r4, #0x30]
	cmp r0, #3
	bls _022429F4
	b _02242B44
_022429F4:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02242A00: ; jump table
	.short _02242A08 - _02242A00 - 2 ; case 0
	.short _02242A38 - _02242A00 - 2 ; case 1
	.short _02242AB8 - _02242A00 - 2 ; case 2
	.short _02242B3C - _02242A00 - 2 ; case 3
_02242A08:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	ldr r1, _02242B5C ; =0x00002DB0
	add r0, r4, r0
	ldr r2, [r0, r1]
	mov r1, #2
	lsl r1, r1, #0x16
	tst r1, r2
	beq _02242A30
	ldr r1, _02242B60 ; =0x00003044
	ldr r1, [r4, r1]
	cmp r1, #0x63
	beq _02242A30
	ldr r1, _02242B5C ; =0x00002DB0
	ldr r2, [r0, r1]
	ldr r1, _02242B64 ; =0xFF7FFFFF
	and r2, r1
	ldr r1, _02242B5C ; =0x00002DB0
	str r2, [r0, r1]
_02242A30:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _02242B44
_02242A38:
	ldr r3, [r4, #0x6c]
	cmp r3, #0xff
	beq _02242AB0
	ldr r0, [sp, #4]
	cmp r0, #0x57
	bne _02242AB0
	mov r0, #0x85
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r0, #0x10
	tst r0, r1
	bne _02242AB0
	ldr r0, _02242B68 ; =0x0000213C
	ldr r1, [r4, r0]
	mov r0, #2
	lsl r0, r0, #0xc
	tst r0, r1
	beq _02242AB0
	ldr r2, [r4, #0x64]
	mov r0, #0x1c
	mul r0, r2
	add r1, r4, r0
	mov r0, #0xbb
	lsl r0, r0, #2
	ldr r7, [r1, r0]
	cmp r7, #0
	beq _02242AB0
	cmp r2, r3
	beq _02242AB0
	mov r0, #0xc0
	mul r0, r2
	add r2, r4, r0
	ldr r0, _02242B6C ; =0x00002D8C
	ldr r1, [r2, r0]
	add r0, r0, #4
	ldr r0, [r2, r0]
	cmp r1, r0
	bhs _02242AB0
	cmp r1, #0
	beq _02242AB0
	ldr r1, [sp]
	neg r0, r7
	bl ov11_022476C0
	ldr r1, _02242B70 ; =0x0000215C
	mov r2, #0xd5
	str r0, [r4, r1]
	mov r0, #0x46
	ldr r1, [r4, #0x64]
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	mov r6, #1
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
_02242AB0:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _02242B44
_02242AB8:
	ldr r0, [sp, #4]
	cmp r0, #0x61
	bne _02242B34
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x62
	beq _02242B34
	mov r0, #0x85
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r0, #0x10
	tst r0, r1
	bne _02242B34
	ldr r0, _02242B68 ; =0x0000213C
	ldr r1, [r4, r0]
	mov r0, #2
	lsl r0, r0, #0xc
	tst r0, r1
	beq _02242B34
	ldr r0, _02242B60 ; =0x00003044
	ldr r0, [r4, r0]
	lsl r0, r0, #4
	add r1, r4, r0
	mov r0, #0x3e
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	cmp r0, #2
	beq _02242B34
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	ldr r1, _02242B6C ; =0x00002D8C
	add r0, r4, r0
	ldr r1, [r0, r1]
	cmp r1, #0
	beq _02242B34
	ldr r1, _02242B74 ; =0x00002D90
	ldr r1, [r0, r1]
	mov r0, #0
	mvn r0, r0
	mul r0, r1
	mov r1, #0xa
	bl ov11_022476C0
	ldr r1, _02242B70 ; =0x0000215C
	mov r2, #0xd6
	str r0, [r4, r1]
	mov r0, #0x46
	ldr r1, [r4, #0x64]
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	bl ov11_022431DC
	ldr r0, [r4, #8]
	mov r6, #1
	str r0, [r4, #0xc]
	mov r0, #0x15
	str r0, [r4, #8]
_02242B34:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _02242B44
_02242B3C:
	mov r0, #0
	str r0, [r4, #0x30]
	str r0, [r4, #0x34]
	mov r6, #2
_02242B44:
	cmp r6, #0
	bne _02242B4A
	b _022429EC
_02242B4A:
	cmp r6, #1
	bne _02242B54
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02242B54:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02242B5C: .word 0x00002DB0
_02242B60: .word 0x00003044
_02242B64: .word 0xFF7FFFFF
_02242B68: .word 0x0000213C
_02242B6C: .word 0x00002D8C
_02242B70: .word 0x0000215C
_02242B74: .word 0x00002D90

	.section .rodata

	.global ov11_0225E178
ov11_0225E178: ; 0x0225E178
	.byte 0x21

	.global ov11_0225E179
ov11_0225E179: ; 0x0225E179
	.byte 0x64, 0x24, 0x64
	.byte 0x2B, 0x64, 0x32, 0x64, 0x3C, 0x64, 0x4B, 0x64, 0x01, 0x01, 0x85, 0x64
	.byte 0xA6, 0x64, 0x02, 0x01, 0xE9, 0x64, 0x85, 0x32, 0x03, 0x01, 0x00, 0x00

	.global ov11_0225E194
ov11_0225E194: ; 0x0225E194
	.word ov11_0223D2C4
	.word ov11_0223D308, ov11_0223D320, ov11_0223D350, ov11_0223D380
	.word ov11_0223D3B8, ov11_0223DBA4, ov11_0223DD20, ov11_0223DE74
	.word ov11_0223DEB8, ov11_0223E69C, ov11_0223F0DC, ov11_0223F328
	.word ov11_0223F380, ov11_0223F4C0, ov11_0223F620, ov11_0223F664
	.word ov11_0223F728, ov11_0223F770, ov11_0223F7CC, ov11_0223F82C
	.word ov11_02240BD8, ov11_02240BF4, ov11_02240D40, ov11_02240E30
	.word ov11_02240E60, ov11_02240EE0, ov11_02240EF8, ov11_022412F8
	.word ov11_022414A4, ov11_022414A8, ov11_02241734, ov11_02241730
	.word ov11_02241834, ov11_0224185C, ov11_022419FC, ov11_02241A44
	.word ov11_02241A58, ov11_02241A5C, ov11_02241B74, ov11_02241C54
	.word ov11_02241C70, ov11_02241CF0, ov11_02241D28
