	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov11_02232264
ov11_02232264: ; 0x02232264
	push {r3, lr}
	add r2, r1, #0
	add r2, #0xb4
	ldr r2, [r2]
	lsl r2, r2, #2
	add r3, r1, r2
	mov r2, #0x27
	lsl r2, r2, #8
	ldr r2, [r3, r2]
	lsl r3, r2, #2
	ldr r2, _02232280 ; =ov11_0225DDE4
	ldr r2, [r2, r3]
	blx r2
	pop {r3, pc}
	.align 2, 0
_02232280: .word ov11_0225DDE4

	thumb_func_start ov11_02232284
ov11_02232284: ; 0x02232284
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	mov r1, #0
	bl ov11_022548F0
	mov r0, #0
	pop {r4, pc}

	thumb_func_start ov11_0223229C
ov11_0223229C: ; 0x0223229C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r4, r0, #0
	bl ov11_0222FF84
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	cmp r0, #0
	beq _022322C2
	cmp r0, #3
	beq _0223230E
	cmp r0, #4
	beq _022322E0
_022322C2:
	mov r5, #0
	cmp r6, #0
	ble _0223230E
_022322C8:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02254908
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_022315C0
	add r5, r5, #1
	cmp r5, r6
	blt _022322C8
	b _0223230E
_022322E0:
	mov r5, #0
	cmp r6, #0
	ble _0223230E
	mov r7, #1
_022322E8:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _02232314 ; =0x00000195
	ldrb r0, [r0, r1]
	tst r0, r7
	beq _02232308
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02254908
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_022315C0
_02232308:
	add r5, r5, #1
	cmp r5, r6
	blt _022322E8
_0223230E:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02232314: .word 0x00000195

	thumb_func_start ov11_02232318
ov11_02232318: ; 0x02232318
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r4, r0, #0
	bl ov11_0222FF84
	add r7, r0, #0
	add r0, r6, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r6, #0
	bl ov11_0223A404
	cmp r0, #6
	bhi _02232350
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02232342: ; jump table
	.short _02232350 - _02232342 - 2 ; case 0
	.short _022323F4 - _02232342 - 2 ; case 1
	.short _0223243E - _02232342 - 2 ; case 2
	.short _0223236E - _02232342 - 2 ; case 3
	.short _022323B2 - _02232342 - 2 ; case 4
	.short _02232350 - _02232342 - 2 ; case 5
	.short _02232488 - _02232342 - 2 ; case 6
_02232350:
	mov r5, #0
	cmp r7, #0
	ble _0223236C
_02232356:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02254A0C
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_022315C0
	add r5, r5, #1
	cmp r5, r7
	blt _02232356
_0223236C:
	b _022324D0
_0223236E:
	mov r5, #0
	cmp r7, #0
	ble _0223239C
_02232374:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _022324D4 ; =0x00000195
	ldrb r1, [r0, r1]
	mov r0, #1
	tst r0, r1
	bne _02232396
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02254A0C
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_022315C0
_02232396:
	add r5, r5, #1
	cmp r5, r7
	blt _02232374
_0223239C:
	add r0, r4, #0
	add r1, r6, #0
	mov r2, #1
	bl ov11_022448CC
	add r0, r4, #0
	add r1, r6, #0
	mov r2, #3
	bl ov11_022448CC
	b _022324D0
_022323B2:
	mov r5, #0
	cmp r7, #0
	ble _022323F2
_022323B8:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _022324D4 ; =0x00000195
	ldrb r1, [r0, r1]
	mov r0, #1
	tst r0, r1
	beq _022323EC
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_022448BC
	add r0, r4, #0
	add r1, r6, #0
	add r2, r5, #0
	bl ov11_022448CC
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02254A0C
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_022315C0
_022323EC:
	add r5, r5, #1
	cmp r5, r7
	blt _022323B8
_022323F2:
	b _022324D0
_022323F4:
	ldr r1, [r6, #0x64]
	add r0, r4, #0
	bl ov11_0222FF7C
	ldr r1, _022324D4 ; =0x00000195
	mov r2, #1
	ldrb r0, [r0, r1]
	tst r0, r2
	bne _0223241A
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_022448CC
	add r0, r4, #0
	add r1, r6, #0
	mov r2, #3
	bl ov11_022448CC
	b _0223242C
_0223241A:
	ldr r1, [r6, #0x64]
	add r0, r6, #0
	bl ov11_022448BC
	ldr r2, [r6, #0x64]
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_022448CC
_0223242C:
	ldr r1, [r6, #0x64]
	add r0, r4, #0
	bl ov11_022315C0
	ldr r1, [r6, #0x64]
	add r0, r4, #0
	bl ov11_02254A0C
	b _022324D0
_0223243E:
	ldr r1, [r6, #0x6c]
	add r0, r4, #0
	bl ov11_0222FF7C
	ldr r1, _022324D4 ; =0x00000195
	mov r2, #1
	ldrb r0, [r0, r1]
	tst r0, r2
	bne _02232464
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_022448CC
	add r0, r4, #0
	add r1, r6, #0
	mov r2, #3
	bl ov11_022448CC
	b _02232476
_02232464:
	ldr r1, [r6, #0x6c]
	add r0, r6, #0
	bl ov11_022448BC
	ldr r2, [r6, #0x6c]
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_022448CC
_02232476:
	ldr r1, [r6, #0x6c]
	add r0, r4, #0
	bl ov11_022315C0
	ldr r1, [r6, #0x6c]
	add r0, r4, #0
	bl ov11_02254A0C
	b _022324D0
_02232488:
	ldr r1, [r6, #0x78]
	add r0, r4, #0
	bl ov11_0222FF7C
	ldr r1, _022324D4 ; =0x00000195
	mov r2, #1
	ldrb r0, [r0, r1]
	tst r0, r2
	bne _022324AE
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_022448CC
	add r0, r4, #0
	add r1, r6, #0
	mov r2, #3
	bl ov11_022448CC
	b _022324C0
_022324AE:
	ldr r1, [r6, #0x78]
	add r0, r6, #0
	bl ov11_022448BC
	ldr r2, [r6, #0x78]
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_022448CC
_022324C0:
	ldr r1, [r6, #0x78]
	add r0, r4, #0
	bl ov11_022315C0
	ldr r1, [r6, #0x78]
	add r0, r4, #0
	bl ov11_02254A0C
_022324D0:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022324D4: .word 0x00000195

	thumb_func_start ov11_022324D8
ov11_022324D8: ; 0x022324D8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r4, r0, #0
	bl ov11_0222FF84
	add r7, r0, #0
	add r0, r6, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r6, #0
	bl ov11_0223A404
	cmp r0, #6
	bhi _02232510
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02232502: ; jump table
	.short _02232510 - _02232502 - 2 ; case 0
	.short _022325C2 - _02232502 - 2 ; case 1
	.short _02232610 - _02232502 - 2 ; case 2
	.short _02232534 - _02232502 - 2 ; case 3
	.short _0223257C - _02232502 - 2 ; case 4
	.short _02232510 - _02232502 - 2 ; case 5
	.short _0223265E - _02232502 - 2 ; case 6
_02232510:
	mov r5, #0
	cmp r7, #0
	ble _02232532
	add r6, r5, #0
_02232518:
	add r0, r4, #0
	add r1, r5, #0
	add r2, r6, #0
	add r3, r6, #0
	bl ov11_02254B40
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_022315C0
	add r5, r5, #1
	cmp r5, r7
	blt _02232518
_02232532:
	b _022326AA
_02232534:
	mov r5, #0
	cmp r7, #0
	ble _02232566
_0223253A:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _022326B0 ; =0x00000195
	ldrb r1, [r0, r1]
	mov r0, #1
	tst r0, r1
	bne _02232560
	mov r2, #0
	add r0, r4, #0
	add r1, r5, #0
	add r3, r2, #0
	bl ov11_02254B40
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_022315C0
_02232560:
	add r5, r5, #1
	cmp r5, r7
	blt _0223253A
_02232566:
	add r0, r4, #0
	add r1, r6, #0
	mov r2, #1
	bl ov11_022448CC
	add r0, r4, #0
	add r1, r6, #0
	mov r2, #3
	bl ov11_022448CC
	b _022326AA
_0223257C:
	mov r5, #0
	cmp r7, #0
	ble _022325C0
_02232582:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _022326B0 ; =0x00000195
	ldrb r1, [r0, r1]
	mov r0, #1
	tst r0, r1
	beq _022325BA
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_022448BC
	add r0, r4, #0
	add r1, r6, #0
	add r2, r5, #0
	bl ov11_022448CC
	mov r2, #0
	add r0, r4, #0
	add r1, r5, #0
	add r3, r2, #0
	bl ov11_02254B40
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_022315C0
_022325BA:
	add r5, r5, #1
	cmp r5, r7
	blt _02232582
_022325C0:
	b _022326AA
_022325C2:
	ldr r1, [r6, #0x64]
	add r0, r4, #0
	bl ov11_0222FF7C
	ldr r1, _022326B0 ; =0x00000195
	mov r2, #1
	ldrb r0, [r0, r1]
	tst r0, r2
	bne _022325E8
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_022448CC
	add r0, r4, #0
	add r1, r6, #0
	mov r2, #3
	bl ov11_022448CC
	b _022325FA
_022325E8:
	ldr r1, [r6, #0x64]
	add r0, r6, #0
	bl ov11_022448BC
	ldr r2, [r6, #0x64]
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_022448CC
_022325FA:
	ldr r1, [r6, #0x64]
	add r0, r4, #0
	bl ov11_022315C0
	mov r2, #0
	ldr r1, [r6, #0x64]
	add r0, r4, #0
	add r3, r2, #0
	bl ov11_02254B40
	b _022326AA
_02232610:
	ldr r1, [r6, #0x6c]
	add r0, r4, #0
	bl ov11_0222FF7C
	ldr r1, _022326B0 ; =0x00000195
	mov r2, #1
	ldrb r0, [r0, r1]
	tst r0, r2
	bne _02232636
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_022448CC
	add r0, r4, #0
	add r1, r6, #0
	mov r2, #3
	bl ov11_022448CC
	b _02232648
_02232636:
	ldr r1, [r6, #0x6c]
	add r0, r6, #0
	bl ov11_022448BC
	ldr r2, [r6, #0x6c]
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_022448CC
_02232648:
	ldr r1, [r6, #0x6c]
	add r0, r4, #0
	bl ov11_022315C0
	mov r2, #0
	ldr r1, [r6, #0x6c]
	add r0, r4, #0
	add r3, r2, #0
	bl ov11_02254B40
	b _022326AA
_0223265E:
	ldr r1, [r6, #0x78]
	add r0, r4, #0
	bl ov11_0222FF7C
	ldr r1, _022326B0 ; =0x00000195
	mov r2, #1
	ldrb r0, [r0, r1]
	tst r0, r2
	bne _02232684
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_022448CC
	add r0, r4, #0
	add r1, r6, #0
	mov r2, #3
	bl ov11_022448CC
	b _02232696
_02232684:
	ldr r1, [r6, #0x78]
	add r0, r6, #0
	bl ov11_022448BC
	ldr r2, [r6, #0x78]
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_022448CC
_02232696:
	ldr r1, [r6, #0x78]
	add r0, r4, #0
	bl ov11_022315C0
	mov r2, #0
	ldr r1, [r6, #0x78]
	add r0, r4, #0
	add r3, r2, #0
	bl ov11_02254B40
_022326AA:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022326B0: .word 0x00000195

	thumb_func_start ov11_022326B4
ov11_022326B4: ; 0x022326B4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r5, r0, #0
	bl ov11_0222FF84
	add r7, r0, #0
	add r0, r6, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r6, #0
	bl ov11_0223A404
	add r2, r0, #0
	beq _022326DC
	cmp r2, #3
	beq _022326F4
	cmp r2, #4
	beq _0223271E
	b _02232756
_022326DC:
	mov r4, #0
	cmp r7, #0
	ble _02232768
_022326E2:
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl ov11_02254D50
	add r4, r4, #1
	cmp r4, r7
	blt _022326E2
	b _02232768
_022326F4:
	mov r4, #0
	cmp r7, #0
	ble _02232768
_022326FA:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0222FF7C
	ldr r1, _0223276C ; =0x00000195
	ldrb r1, [r0, r1]
	mov r0, #1
	tst r0, r1
	bne _02232716
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl ov11_02254D50
_02232716:
	add r4, r4, #1
	cmp r4, r7
	blt _022326FA
	b _02232768
_0223271E:
	mov r4, #0
	cmp r7, #0
	ble _02232768
_02232724:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0222FF7C
	ldr r1, _0223276C ; =0x00000195
	ldrb r1, [r0, r1]
	mov r0, #1
	tst r0, r1
	beq _0223274E
	add r0, r4, #0
	bl MaskOfFlagNo
	ldr r1, _02232770 ; =0x00003108
	ldrb r1, [r6, r1]
	tst r0, r1
	bne _0223274E
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl ov11_02254D50
_0223274E:
	add r4, r4, #1
	cmp r4, r7
	blt _02232724
	b _02232768
_02232756:
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_0223C230
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_02254D50
_02232768:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223276C: .word 0x00000195
_02232770: .word 0x00003108

	thumb_func_start ov11_02232774
ov11_02232774: ; 0x02232774
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r5, #0
	bl ov11_02254F60
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_022327A0
ov11_022327A0: ; 0x022327A0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r4, r0, #0
	bl ov11_0222FF84
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	cmp r0, #0
	beq _022327C6
	cmp r0, #3
	beq _0223282A
	cmp r0, #4
	beq _0223286A
_022327C6:
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #0x10
	tst r0, r1
	beq _022327F8
	mov r5, #0
	cmp r6, #0
	ble _022328B4
	ldr r7, _022328B8 ; =0x00000195
_022327DA:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldrb r0, [r0, r7]
	cmp r0, #4
	beq _022327F0
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02254F7C
_022327F0:
	add r5, r5, #1
	cmp r5, r6
	blt _022327DA
	b _022328B4
_022327F8:
	mov r5, #0
	cmp r6, #0
	ble _022328B4
	mov r7, #8
_02232800:
	add r0, r4, #0
	bl ov11_0222FF74
	tst r0, r7
	bne _0223281A
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _0223281A
	cmp r5, #1
	bgt _022328B4
_0223281A:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02254F7C
	add r5, r5, #1
	cmp r5, r6
	blt _02232800
	b _022328B4
_0223282A:
	mov r5, #0
	cmp r6, #0
	ble _022328B4
	mov r7, #1
_02232832:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _022328B8 ; =0x00000195
	ldrb r0, [r0, r1]
	tst r0, r7
	bne _02232862
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02254F7C
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #8
	tst r0, r1
	bne _02232862
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	bne _022328B4
_02232862:
	add r5, r5, #1
	cmp r5, r6
	blt _02232832
	b _022328B4
_0223286A:
	mov r5, #0
	cmp r6, #0
	ble _022328B4
	mov r7, #1
_02232872:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _022328B8 ; =0x00000195
	ldrb r0, [r0, r1]
	tst r0, r7
	beq _022328AE
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02254F7C
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #8
	tst r0, r1
	bne _022328AE
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #0x10
	tst r0, r1
	bne _022328AE
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	bne _022328B4
_022328AE:
	add r5, r5, #1
	cmp r5, r6
	blt _02232872
_022328B4:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022328B8: .word 0x00000195

	thumb_func_start ov11_022328BC
ov11_022328BC: ; 0x022328BC
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r4, r0, #0
	bl ov11_0222FF84
	add r6, r0, #0
	add r0, r7, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r7, #0
	bl ov11_0223A404
	add r5, r0, #0
	add r0, r7, #0
	bl ov11_0223A404
	add r7, r0, #0
	cmp r5, #0
	beq _022328EC
	cmp r5, #3
	beq _02232920
	cmp r5, #4
	beq _02232962
_022328EC:
	mov r5, #0
	cmp r6, #0
	ble _022329AE
_022328F2:
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #8
	tst r0, r1
	bne _0223290E
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _0223290E
	cmp r5, #1
	bgt _022329AE
_0223290E:
	add r0, r4, #0
	add r1, r5, #0
	add r2, r7, #0
	bl ov11_02254FAC
	add r5, r5, #1
	cmp r5, r6
	blt _022328F2
	b _022329AE
_02232920:
	mov r5, #0
	cmp r6, #0
	ble _022329AE
_02232926:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _022329B4 ; =0x00000195
	ldrb r1, [r0, r1]
	mov r0, #1
	tst r0, r1
	bne _0223295A
	add r0, r4, #0
	add r1, r5, #0
	add r2, r7, #0
	bl ov11_02254FAC
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #8
	tst r0, r1
	bne _0223295A
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	bne _022329AE
_0223295A:
	add r5, r5, #1
	cmp r5, r6
	blt _02232926
	b _022329AE
_02232962:
	mov r5, #0
	cmp r6, #0
	ble _022329AE
_02232968:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _022329B4 ; =0x00000195
	ldrb r1, [r0, r1]
	mov r0, #1
	tst r0, r1
	beq _022329A8
	add r0, r4, #0
	add r1, r5, #0
	add r2, r7, #0
	bl ov11_02254FAC
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #8
	tst r0, r1
	bne _022329A8
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #0x10
	tst r0, r1
	bne _022329A8
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	bne _022329AE
_022329A8:
	add r5, r5, #1
	cmp r5, r6
	blt _02232968
_022329AE:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022329B4: .word 0x00000195

	thumb_func_start ov11_022329B8
ov11_022329B8: ; 0x022329B8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r4, r0, #0
	bl ov11_0222FF84
	add r5, r0, #0
	add r0, r6, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r6, #0
	bl ov11_0223A404
	cmp r0, #0xc
	bhi _022329FC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022329E2: ; jump table
	.short _022329FC - _022329E2 - 2 ; case 0
	.short _022329FC - _022329E2 - 2 ; case 1
	.short _022329FC - _022329E2 - 2 ; case 2
	.short _02232A2E - _022329E2 - 2 ; case 3
	.short _02232A6E - _022329E2 - 2 ; case 4
	.short _022329FC - _022329E2 - 2 ; case 5
	.short _022329FC - _022329E2 - 2 ; case 6
	.short _022329FC - _022329E2 - 2 ; case 7
	.short _022329FC - _022329E2 - 2 ; case 8
	.short _02232ABA - _022329E2 - 2 ; case 9
	.short _02232AE6 - _022329E2 - 2 ; case 10
	.short _02232B12 - _022329E2 - 2 ; case 11
	.short _02232B3A - _022329E2 - 2 ; case 12
_022329FC:
	mov r6, #0
	cmp r5, #0
	ble _02232A2C
	mov r7, #8
_02232A04:
	add r0, r4, #0
	bl ov11_0222FF74
	tst r0, r7
	bne _02232A1E
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _02232A1E
	cmp r6, #1
	bgt _02232A2C
_02232A1E:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_02254FE4
	add r6, r6, #1
	cmp r6, r5
	blt _02232A04
_02232A2C:
	b _02232B60
_02232A2E:
	mov r6, #0
	cmp r5, #0
	ble _02232A6C
	mov r7, #1
_02232A36:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0222FF7C
	ldr r1, _02232B64 ; =0x00000195
	ldrb r0, [r0, r1]
	tst r0, r7
	bne _02232A66
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_02254FE4
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #8
	tst r0, r1
	bne _02232A66
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	bne _02232B60
_02232A66:
	add r6, r6, #1
	cmp r6, r5
	blt _02232A36
_02232A6C:
	b _02232B60
_02232A6E:
	mov r6, #0
	cmp r5, #0
	ble _02232B60
	mov r7, #1
_02232A76:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0222FF7C
	ldr r1, _02232B64 ; =0x00000195
	ldrb r0, [r0, r1]
	tst r0, r7
	beq _02232AB2
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_02254FE4
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #8
	tst r0, r1
	bne _02232AB2
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #0x10
	tst r0, r1
	bne _02232AB2
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	bne _02232B60
_02232AB2:
	add r6, r6, #1
	cmp r6, r5
	blt _02232A76
	b _02232B60
_02232ABA:
	mov r6, #0
	cmp r5, #0
	ble _02232B60
	ldr r7, _02232B64 ; =0x00000195
_02232AC2:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0222FF7C
	ldrb r0, [r0, r7]
	cmp r0, #0
	beq _02232AD4
	cmp r0, #2
	bne _02232ADE
_02232AD4:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_02254FE4
	b _02232B60
_02232ADE:
	add r6, r6, #1
	cmp r6, r5
	blt _02232AC2
	b _02232B60
_02232AE6:
	mov r6, #0
	cmp r5, #0
	ble _02232B60
	ldr r7, _02232B64 ; =0x00000195
_02232AEE:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0222FF7C
	ldrb r0, [r0, r7]
	cmp r0, #1
	beq _02232B00
	cmp r0, #3
	bne _02232B0A
_02232B00:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_02254FE4
	b _02232B60
_02232B0A:
	add r6, r6, #1
	cmp r6, r5
	blt _02232AEE
	b _02232B60
_02232B12:
	mov r6, #0
	cmp r5, #0
	ble _02232B60
	ldr r7, _02232B64 ; =0x00000195
_02232B1A:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0222FF7C
	ldrb r0, [r0, r7]
	cmp r0, #4
	bne _02232B32
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_02254FE4
	b _02232B60
_02232B32:
	add r6, r6, #1
	cmp r6, r5
	blt _02232B1A
	b _02232B60
_02232B3A:
	mov r6, #0
	cmp r5, #0
	ble _02232B60
	ldr r7, _02232B64 ; =0x00000195
_02232B42:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0222FF7C
	ldrb r0, [r0, r7]
	cmp r0, #5
	bne _02232B5A
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_02254FE4
	b _02232B60
_02232B5A:
	add r6, r6, #1
	cmp r6, r5
	blt _02232B42
_02232B60:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02232B64: .word 0x00000195

	thumb_func_start ov11_02232B68
ov11_02232B68: ; 0x02232B68
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r4, r0, #0
	bl ov11_0222FF84
	add r5, r0, #0
	add r0, r7, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r7, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r7, #0
	bl ov11_0223A404
	add r7, r0, #0
	cmp r6, #0xc
	bhi _02232BB6
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02232B9C: ; jump table
	.short _02232BB6 - _02232B9C - 2 ; case 0
	.short _02232BB6 - _02232B9C - 2 ; case 1
	.short _02232BB6 - _02232B9C - 2 ; case 2
	.short _02232BDE - _02232B9C - 2 ; case 3
	.short _02232C14 - _02232B9C - 2 ; case 4
	.short _02232BB6 - _02232B9C - 2 ; case 5
	.short _02232BB6 - _02232B9C - 2 ; case 6
	.short _02232BB6 - _02232B9C - 2 ; case 7
	.short _02232BB6 - _02232B9C - 2 ; case 8
	.short _02232C4A - _02232B9C - 2 ; case 9
	.short _02232C78 - _02232B9C - 2 ; case 10
	.short _02232CA6 - _02232B9C - 2 ; case 11
	.short _02232CD0 - _02232B9C - 2 ; case 12
_02232BB6:
	mov r6, #0
	cmp r5, #0
	ble _02232BDC
_02232BBC:
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _02232BCC
	cmp r6, #1
	bgt _02232BDC
_02232BCC:
	add r0, r4, #0
	add r1, r6, #0
	add r2, r7, #0
	bl ov11_02255000
	add r6, r6, #1
	cmp r6, r5
	blt _02232BBC
_02232BDC:
	b _02232CF8
_02232BDE:
	mov r6, #0
	cmp r5, #0
	ble _02232C12
_02232BE4:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0222FF7C
	ldr r1, _02232CFC ; =0x00000195
	ldrb r1, [r0, r1]
	mov r0, #1
	tst r0, r1
	bne _02232C0C
	add r0, r4, #0
	add r1, r6, #0
	add r2, r7, #0
	bl ov11_02255000
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	bne _02232CF8
_02232C0C:
	add r6, r6, #1
	cmp r6, r5
	blt _02232BE4
_02232C12:
	b _02232CF8
_02232C14:
	mov r6, #0
	cmp r5, #0
	ble _02232CF8
_02232C1A:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0222FF7C
	ldr r1, _02232CFC ; =0x00000195
	ldrb r1, [r0, r1]
	mov r0, #1
	tst r0, r1
	beq _02232C42
	add r0, r4, #0
	add r1, r6, #0
	add r2, r7, #0
	bl ov11_02255000
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	bne _02232CF8
_02232C42:
	add r6, r6, #1
	cmp r6, r5
	blt _02232C1A
	b _02232CF8
_02232C4A:
	mov r6, #0
	cmp r5, #0
	ble _02232CF8
_02232C50:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0222FF7C
	ldr r1, _02232CFC ; =0x00000195
	ldrb r0, [r0, r1]
	cmp r0, #0
	beq _02232C64
	cmp r0, #2
	bne _02232C70
_02232C64:
	add r0, r4, #0
	add r1, r6, #0
	add r2, r7, #0
	bl ov11_02255000
	b _02232CF8
_02232C70:
	add r6, r6, #1
	cmp r6, r5
	blt _02232C50
	b _02232CF8
_02232C78:
	mov r6, #0
	cmp r5, #0
	ble _02232CF8
_02232C7E:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0222FF7C
	ldr r1, _02232CFC ; =0x00000195
	ldrb r0, [r0, r1]
	cmp r0, #1
	beq _02232C92
	cmp r0, #3
	bne _02232C9E
_02232C92:
	add r0, r4, #0
	add r1, r6, #0
	add r2, r7, #0
	bl ov11_02255000
	b _02232CF8
_02232C9E:
	add r6, r6, #1
	cmp r6, r5
	blt _02232C7E
	b _02232CF8
_02232CA6:
	mov r6, #0
	cmp r5, #0
	ble _02232CF8
_02232CAC:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0222FF7C
	ldr r1, _02232CFC ; =0x00000195
	ldrb r0, [r0, r1]
	cmp r0, #4
	bne _02232CC8
	add r0, r4, #0
	add r1, r6, #0
	add r2, r7, #0
	bl ov11_02255000
	b _02232CF8
_02232CC8:
	add r6, r6, #1
	cmp r6, r5
	blt _02232CAC
	b _02232CF8
_02232CD0:
	mov r6, #0
	cmp r5, #0
	ble _02232CF8
_02232CD6:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0222FF7C
	ldr r1, _02232CFC ; =0x00000195
	ldrb r0, [r0, r1]
	cmp r0, #5
	bne _02232CF2
	add r0, r4, #0
	add r1, r6, #0
	add r2, r7, #0
	bl ov11_02255000
	b _02232CF8
_02232CF2:
	add r6, r6, #1
	cmp r6, r5
	blt _02232CD6
_02232CF8:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02232CFC: .word 0x00000195

	thumb_func_start ov11_02232D00
ov11_02232D00: ; 0x02232D00
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r0, #0
	bl ov11_0222FF84
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	mov r4, #0
	cmp r5, #0
	ble _02232D28
_02232D1A:
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0225624C
	add r4, r4, #1
	cmp r4, r5
	blt _02232D1A
_02232D28:
	mov r0, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov11_02232D2C
ov11_02232D2C: ; 0x02232D2C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r4, r0, #0
	bl ov11_0222FF84
	add r6, r0, #0
	add r0, r7, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r7, #0
	bl ov11_0223A404
	add r2, r0, #0
	beq _02232D54
	cmp r2, #3
	beq _02232D6E
	cmp r2, #4
	beq _02232D9A
	b _02232DC6
_02232D54:
	mov r5, #0
	cmp r6, #0
	ble _02232DDA
_02232D5A:
	add r0, r4, #0
	add r1, r7, #0
	add r2, r5, #0
	mov r3, #0
	bl ov11_02255034
	add r5, r5, #1
	cmp r5, r6
	blt _02232D5A
	b _02232DDA
_02232D6E:
	mov r5, #0
	cmp r6, #0
	ble _02232DDA
_02232D74:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _02232DE0 ; =0x00000195
	ldrb r1, [r0, r1]
	mov r0, #1
	tst r0, r1
	bne _02232D92
	add r0, r4, #0
	add r1, r7, #0
	add r2, r5, #0
	mov r3, #0
	bl ov11_02255034
_02232D92:
	add r5, r5, #1
	cmp r5, r6
	blt _02232D74
	b _02232DDA
_02232D9A:
	mov r5, #0
	cmp r6, #0
	ble _02232DDA
_02232DA0:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _02232DE0 ; =0x00000195
	ldrb r1, [r0, r1]
	mov r0, #1
	tst r0, r1
	beq _02232DBE
	add r0, r4, #0
	add r1, r7, #0
	add r2, r5, #0
	mov r3, #0
	bl ov11_02255034
_02232DBE:
	add r5, r5, #1
	cmp r5, r6
	blt _02232DA0
	b _02232DDA
_02232DC6:
	add r0, r4, #0
	add r1, r7, #0
	bl ov11_0223C230
	add r2, r0, #0
	add r0, r4, #0
	add r1, r7, #0
	mov r3, #0
	bl ov11_02255034
_02232DDA:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02232DE0: .word 0x00000195

	thumb_func_start ov11_02232DE4
ov11_02232DE4: ; 0x02232DE4
	push {r3, r4, r5, r6, r7, lr}
	str r1, [sp]
	add r5, r0, #0
	bl ov11_0222FF84
	add r7, r0, #0
	ldr r0, [sp]
	mov r1, #1
	bl ov11_0223A424
	ldr r0, [sp]
	bl ov11_0223A404
	add r2, r0, #0
	ldr r4, _02232EA4 ; =0x00000000
	beq _02232E0E
	cmp r2, #3
	beq _02232E28
	cmp r2, #4
	beq _02232E5A
	b _02232E8C
_02232E0E:
	cmp r7, #0
	ble _02232EA0
	add r6, r4, #0
_02232E14:
	ldr r1, [sp]
	add r0, r5, #0
	add r2, r4, #0
	add r3, r6, #0
	bl ov11_02255034
	add r4, r4, #1
	cmp r4, r7
	blt _02232E14
	b _02232EA0
_02232E28:
	add r6, r4, #0
	cmp r7, #0
	ble _02232EA0
_02232E2E:
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_0222FF7C
	ldr r1, _02232EA8 ; =0x00000195
	ldrb r1, [r0, r1]
	mov r0, #1
	tst r0, r1
	bne _02232E52
	ldr r1, [sp]
	add r0, r5, #0
	add r2, r6, #0
	add r3, r4, #0
	bl ov11_02255034
	add r0, r4, #4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02232E52:
	add r6, r6, #1
	cmp r6, r7
	blt _02232E2E
	b _02232EA0
_02232E5A:
	add r6, r4, #0
	cmp r7, #0
	ble _02232EA0
_02232E60:
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_0222FF7C
	ldr r1, _02232EA8 ; =0x00000195
	ldrb r1, [r0, r1]
	mov r0, #1
	tst r0, r1
	beq _02232E84
	ldr r1, [sp]
	add r0, r5, #0
	add r2, r6, #0
	add r3, r4, #0
	bl ov11_02255034
	add r0, r4, #4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02232E84:
	add r6, r6, #1
	cmp r6, r7
	blt _02232E60
	b _02232EA0
_02232E8C:
	ldr r1, [sp]
	add r0, r5, #0
	bl ov11_0223C230
	add r2, r0, #0
	ldr r1, [sp]
	add r0, r5, #0
	add r3, r4, #0
	bl ov11_02255034
_02232EA0:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02232EA4: .word 0x00000000
_02232EA8: .word 0x00000195

	thumb_func_start ov11_02232EAC
ov11_02232EAC: ; 0x02232EAC
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r4, r0, #0
	bl ov11_0222FF84
	add r6, r0, #0
	add r0, r7, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r7, #0
	bl ov11_0223A404
	add r2, r0, #0
	beq _02232ED4
	cmp r2, #3
	beq _02232EEA
	cmp r2, #4
	beq _02232F20
	b _02232F48
_02232ED4:
	mov r5, #0
	cmp r6, #0
	ble _02232F58
_02232EDA:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0225516C
	add r5, r5, #1
	cmp r5, r6
	blt _02232EDA
	b _02232F58
_02232EEA:
	mov r5, #0
	cmp r6, #0
	ble _02232F58
_02232EF0:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _02232F5C ; =0x00000195
	ldrb r1, [r0, r1]
	mov r0, #1
	tst r0, r1
	bne _02232F18
	add r0, r5, #0
	bl MaskOfFlagNo
	ldr r1, _02232F60 ; =0x00003108
	ldrb r1, [r7, r1]
	tst r0, r1
	bne _02232F18
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0225516C
_02232F18:
	add r5, r5, #1
	cmp r5, r6
	blt _02232EF0
	b _02232F58
_02232F20:
	mov r5, #0
	cmp r6, #0
	ble _02232F58
	mov r7, #1
_02232F28:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _02232F5C ; =0x00000195
	ldrb r0, [r0, r1]
	tst r0, r7
	beq _02232F40
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0225516C
_02232F40:
	add r5, r5, #1
	cmp r5, r6
	blt _02232F28
	b _02232F58
_02232F48:
	add r0, r4, #0
	add r1, r7, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r4, #0
	bl ov11_0225516C
_02232F58:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02232F5C: .word 0x00000195
_02232F60: .word 0x00003108

	thumb_func_start ov11_02232F64
ov11_02232F64: ; 0x02232F64
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl ov11_02243388
	cmp r0, #0
	beq _02232F7C
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	b _02232F82
_02232F7C:
	add r0, r4, #0
	bl ov11_022433DC
_02232F82:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_02232F88
ov11_02232F88: ; 0x02232F88
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r1, #0
	ldr r1, [r5, #0x64]
	add r7, r0, #0
	add r0, r5, #0
	bl ov11_02246D1C
	cmp r0, #0x60
	bne _02232FA0
	mov r4, #0
	b _02232FB4
_02232FA0:
	ldr r0, _022330D4 ; =0x00002160
	ldr r4, [r5, r0]
	cmp r4, #0
	bne _02232FB4
	ldr r0, _022330D8 ; =0x00003044
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _022330DC ; =0x000003E2
	ldrb r4, [r1, r0]
_02232FB4:
	ldr r0, [r5, #0x6c]
	str r0, [sp, #0x18]
	ldr r1, [sp, #0x18]
	add r0, r7, #0
	bl ov11_02230270
	mov r3, #6
	lsl r3, r3, #6
	add r6, r0, #0
	ldr r0, [r5, r3]
	ldr r1, _022330E0 ; =0x00002154
	str r0, [sp]
	ldr r0, [r5, r1]
	ldr r2, _022330D8 ; =0x00003044
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	ldr r0, [r5, #0x64]
	lsl r4, r6, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x18]
	add r4, r5, r4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x10]
	sub r0, r1, #4
	ldr r0, [r5, r0]
	add r3, #0x3c
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x14]
	ldr r2, [r5, r2]
	ldr r3, [r4, r3]
	add r0, r7, #0
	add r1, r5, #0
	bl ov11_0224B310
	ldr r1, _022330E4 ; =0x00002144
	str r0, [r5, r1]
	add r0, r1, #0
	add r0, #0xc
	ldr r2, [r5, r1]
	ldr r0, [r5, r0]
	mul r0, r2
	str r0, [r5, r1]
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl ov11_02249D90
	cmp r0, #0x61
	bne _02233040
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	mov r2, #0
	bl ov11_02249DA4
	ldr r1, _022330E4 ; =0x00002144
	add r0, #0x64
	ldr r1, [r5, r1]
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	ldr r1, _022330E4 ; =0x00002144
	str r0, [r5, r1]
_02233040:
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl ov11_02249D90
	cmp r0, #0x68
	bne _0223306E
	ldr r0, _022330E4 ; =0x00002144
	ldr r2, [r5, #0x64]
	ldr r1, [r5, r0]
	mov r0, #0xc0
	mul r0, r2
	add r2, r5, r0
	ldr r0, _022330E8 ; =0x00002DCC
	ldr r0, [r2, r0]
	lsl r0, r0, #5
	lsr r0, r0, #0x1c
	add r0, #0xa
	mul r0, r1
	mov r1, #0xa
	bl _u32_div_f
	ldr r1, _022330E4 ; =0x00002144
	str r0, [r5, r1]
_0223306E:
	ldr r2, [r5, #0x64]
	mov r1, #0xc0
	add r0, r2, #0
	mul r0, r1
	ldr r2, _022330E8 ; =0x00002DCC
	add r3, r5, r0
	ldr r3, [r3, r2]
	lsl r3, r3, #1
	lsr r3, r3, #0x1f
	beq _022330CE
	add r2, #0x10
	add r3, r5, r2
	add r1, #0xb4
	ldr r2, [r5, r1]
	ldr r1, [r3, r0]
	cmp r2, r1
	bne _02233094
	sub r1, r1, #1
	str r1, [r3, r0]
_02233094:
	ldr r2, [r5, #0x64]
	mov r1, #0xc0
	add r0, r2, #0
	mul r0, r1
	add r1, #0xb4
	ldr r3, [r5, r1]
	ldr r1, _022330EC ; =0x00002DDC
	add r2, r5, r0
	ldr r2, [r2, r1]
	sub r2, r3, r2
	cmp r2, #2
	bge _022330C2
	ldr r0, _022330E4 ; =0x00002144
	ldr r1, [r5, r0]
	mov r0, #0xf
	mul r0, r1
	mov r1, #0xa
	bl _s32_div_f
	ldr r1, _022330E4 ; =0x00002144
	add sp, #0x1c
	str r0, [r5, r1]
	pop {r4, r5, r6, r7, pc}
_022330C2:
	sub r1, #0x10
	add r3, r5, r1
	ldr r2, [r3, r0]
	ldr r1, _022330F0 ; =0xBFFFFFFF
	and r1, r2
	str r1, [r3, r0]
_022330CE:
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_022330D4: .word 0x00002160
_022330D8: .word 0x00003044
_022330DC: .word 0x000003E2
_022330E0: .word 0x00002154
_022330E4: .word 0x00002144
_022330E8: .word 0x00002DCC
_022330EC: .word 0x00002DDC
_022330F0: .word 0xBFFFFFFF

	thumb_func_start ov11_022330F4
ov11_022330F4: ; 0x022330F4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02232F88
	ldr r1, _02233128 ; =0x00002144
	add r0, r4, #0
	ldr r1, [r4, r1]
	bl ov11_0224BF10
	ldr r1, _02233128 ; =0x00002144
	str r0, [r4, r1]
	mov r0, #0
	ldr r2, [r4, r1]
	mvn r0, r0
	mul r0, r2
	str r0, [r4, r1]
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02233128: .word 0x00002144

	thumb_func_start ov11_0223312C
ov11_0223312C: ; 0x0223312C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02232F88
	ldr r1, _02233154 ; =0x00002144
	mov r0, #0
	ldr r2, [r4, r1]
	mvn r0, r0
	mul r0, r2
	str r0, [r4, r1]
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02233154: .word 0x00002144

	thumb_func_start ov11_02233158
ov11_02233158: ; 0x02233158
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r0, _02233194 ; =0x0000213C
	ldr r1, [r4, r0]
	mov r0, #1
	tst r0, r1
	bne _02233178
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_022559BC
_02233178:
	ldr r1, _02233194 ; =0x0000213C
	mov r0, #1
	ldr r2, [r4, r1]
	orr r0, r2
	str r0, [r4, r1]
	add r0, r1, #4
	ldr r2, [r4, r0]
	mov r0, #4
	orr r2, r0
	add r0, r1, #4
	str r2, [r4, r0]
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02233194: .word 0x0000213C

	thumb_func_start ov11_02233198
ov11_02233198: ; 0x02233198
	push {r4, r5, lr}
	sub sp, #0x44
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	add r1, sp, #0x24
	bl ov11_0223C490
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #0x24
	add r3, sp, #0
	bl ov11_0223C55C
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #0
	bl ov11_022559F4
	mov r0, #0
	add sp, #0x44
	pop {r4, r5, pc}

	thumb_func_start ov11_022331CC
ov11_022331CC: ; 0x022331CC
	push {r4, r5, lr}
	sub sp, #0x44
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	add r1, sp, #0x24
	bl ov11_0223C490
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #0x24
	add r3, sp, #0
	bl ov11_0223C55C
	add r1, sp, #0
	ldrb r2, [r1, #1]
	mov r0, #0x80
	orr r0, r2
	strb r0, [r1, #1]
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #0
	bl ov11_022559F4
	mov r0, #0
	add sp, #0x44
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_0223320C
ov11_0223320C: ; 0x0223320C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r1, r4, #0
	add r4, #0xf4
	add r0, r5, #0
	add r2, r4, #0
	bl ov11_022559F4
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_0223322C
ov11_0223322C: ; 0x0223322C
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	add r1, sp, #0
	bl ov11_0223C490
	add r1, r4, #0
	add r4, #0xf4
	add r0, r5, #0
	add r2, sp, #0
	add r3, r4, #0
	bl ov11_0223C55C
	mov r0, #0
	add sp, #0x20
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_02233258
ov11_02233258: ; 0x02233258
	push {r3, r4, r5, r6, lr}
	sub sp, #0x44
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	add r1, sp, #0x24
	bl ov11_0223C490
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #0x24
	add r3, sp, #0
	bl ov11_0223C55C
	add r1, sp, #0
	ldrb r2, [r1, #1]
	mov r0, #0x40
	orr r0, r2
	strb r0, [r1, #1]
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0223C230
	str r0, [sp, #0x20]
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #0
	bl ov11_022559F4
	mov r0, #0
	add sp, #0x44
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_022332AC
ov11_022332AC: ; 0x022332AC
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	cmp r0, #0xff
	bne _022332CA
	mov r0, #0x49
	lsl r0, r0, #2
	b _022332CC
_022332CA:
	ldr r0, _0223331C ; =0x00003044
_022332CC:
	ldr r0, [r5, r0]
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, _02233320 ; =0x0000213C
	ldr r1, [r5, r0]
	mov r0, #1
	lsl r0, r0, #0xe
	tst r0, r1
	bne _022332E8
	add r0, r6, #0
	bl ov11_02230E20
	cmp r0, #1
	beq _022332EC
_022332E8:
	cmp r4, #0x90
	bne _02233302
_022332EC:
	ldr r1, _02233320 ; =0x0000213C
	mov r0, #1
	ldr r2, [r5, r1]
	lsl r0, r0, #0xe
	orr r0, r2
	str r0, [r5, r1]
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl ov11_02255A10
_02233302:
	add r0, r6, #0
	bl ov11_02230E20
	cmp r0, #0
	bne _02233316
	ldr r2, _02233324 ; =0x00000123
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A43C
_02233316:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_0223331C: .word 0x00003044
_02233320: .word 0x0000213C
_02233324: .word 0x00000123

	thumb_func_start ov11_02233328
ov11_02233328: ; 0x02233328
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp, #8]
	cmp r6, #0xff
	bne _0223335A
	mov r0, #0x49
	lsl r0, r0, #2
	b _0223335C
_0223335A:
	ldr r0, _022333C8 ; =0x00003044
_0223335C:
	ldr r0, [r4, r0]
	add r1, r4, #0
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r0, r5, #0
	add r2, r7, #0
	bl ov11_0223C230
	str r0, [sp, #4]
	ldr r2, [sp, #8]
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r7, r0, #0
	ldr r0, _022333CC ; =0x0000213C
	ldr r1, [r4, r0]
	mov r0, #1
	lsl r0, r0, #0xe
	tst r0, r1
	bne _02233390
	add r0, r5, #0
	bl ov11_02230E20
	cmp r0, #1
	beq _02233394
_02233390:
	cmp r6, #0x90
	bne _022333AE
_02233394:
	ldr r1, _022333CC ; =0x0000213C
	mov r0, #1
	ldr r2, [r4, r1]
	lsl r0, r0, #0xe
	orr r0, r2
	str r0, [r4, r1]
	ldr r3, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	str r7, [sp]
	bl ov11_02255A40
_022333AE:
	add r0, r5, #0
	bl ov11_02230E20
	cmp r0, #0
	bne _022333C2
	ldr r2, _022333D0 ; =0x00000123
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A43C
_022333C2:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022333C8: .word 0x00003044
_022333CC: .word 0x0000213C
_022333D0: .word 0x00000123

	thumb_func_start ov11_022333D4
ov11_022333D4: ; 0x022333D4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	ldr r2, _02233404 ; =0x0000216C
	add r1, r0, #0
	ldr r2, [r4, r2]
	add r0, r5, #0
	bl ov11_02255A70
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02233404: .word 0x0000216C

	thumb_func_start ov11_02233408
ov11_02233408: ; 0x02233408
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	ldr r0, [sp]
	add r1, r4, #0
	bl ov11_0223C230
	add r2, r0, #0
	ldr r0, _0223349C ; =0x00002D8C
	add r7, r2, #0
	add r5, r4, r0
	mov r0, #0xc0
	mul r7, r0
	ldr r0, _022334A0 ; =0x0000215C
	ldr r6, [r5, r7]
	ldr r3, [r4, r0]
	add r1, r3, r6
	cmp r1, #0
	bgt _02233446
	neg r1, r6
	sub r0, #0x14
	str r1, [r4, r0]
	b _0223344A
_02233446:
	sub r0, #0x14
	str r3, [r4, r0]
_0223344A:
	ldr r0, _022334A4 ; =0x00002148
	ldr r6, [r4, r0]
	cmp r6, #0
	bge _02233460
	mov r0, #0x59
	lsl r0, r0, #2
	add r3, r4, r0
	lsl r1, r2, #2
	ldr r0, [r3, r1]
	sub r0, r0, r6
	str r0, [r3, r1]
_02233460:
	mov r0, #0xc0
	add r3, r2, #0
	mul r3, r0
	ldr r0, _0223349C ; =0x00002D8C
	ldr r6, _022334A0 ; =0x0000215C
	add r1, r4, r0
	ldr r0, [r1, r3]
	ldr r6, [r4, r6]
	add r0, r0, r6
	str r0, [r1, r3]
	ldr r1, [r1, r3]
	cmp r1, #0
	bge _02233480
	mov r0, #0
	str r0, [r5, r7]
	b _0223348E
_02233480:
	add r0, r4, r3
	ldr r3, _0223349C ; =0x00002D8C
	add r3, r3, #4
	ldr r0, [r0, r3]
	cmp r1, r0
	bls _0223348E
	str r0, [r5, r7]
_0223348E:
	ldr r0, [sp]
	add r1, r4, #0
	bl ov11_02245190
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223349C: .word 0x00002D8C
_022334A0: .word 0x0000215C
_022334A4: .word 0x00002148

	thumb_func_start ov11_022334A8
ov11_022334A8: ; 0x022334A8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02255A8C
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_022334D4
ov11_022334D4: ; 0x022334D4
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_0223C230
	add r4, r0, #0
	mov r1, #0xc0
	mul r1, r4
	add r2, r5, r1
	ldr r1, _02233530 ; =0x00002D8C
	ldr r1, [r2, r1]
	cmp r1, #0
	bne _0223352A
	str r4, [r5, #0x74]
	bl MaskOfFlagNo
	ldr r1, _02233534 ; =0x0000213C
	lsl r0, r0, #0x18
	ldr r2, [r5, r1]
	orr r0, r2
	str r0, [r5, r1]
	mov r0, #0x55
	lsl r0, r0, #2
	add r2, r5, r0
	lsl r1, r4, #2
	ldr r0, [r2, r1]
	add r0, r0, #1
	str r0, [r2, r1]
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl ov11_0223D0EC
_0223352A:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_02233530: .word 0x00002D8C
_02233534: .word 0x0000213C

	thumb_func_start ov11_02233538
ov11_02233538: ; 0x02233538
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r2, [r4, #0x74]
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02255BEC
	ldr r0, [r4, #0x74]
	bl MaskOfFlagNo
	ldr r2, _02233594 ; =0x0000213C
	lsl r3, r0, #0x18
	mov r0, #0
	mvn r0, r0
	ldr r1, [r4, r2]
	eor r0, r3
	and r0, r1
	str r0, [r4, r2]
	ldr r0, [r4, #0x74]
	bl MaskOfFlagNo
	mov r1, #0x85
	lsl r1, r1, #6
	ldr r2, [r4, r1]
	lsl r0, r0, #0x1c
	orr r0, r2
	str r0, [r4, r1]
	ldr r0, [r4, #0x74]
	mov r2, #0x27
	lsl r0, r0, #4
	add r0, r4, r0
	add r1, #0x68
	str r2, [r0, r1]
	ldr r2, [r4, #0x74]
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02245A10
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02233594: .word 0x0000213C

	thumb_func_start ov11_02233598
ov11_02233598: ; 0x02233598
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r6, #0
	bl ov11_0222FF74
	mov r1, #4
	tst r0, r1
	bne _022335D2
	ldr r0, _022335FC ; =gSystem
	ldr r1, [r0, #0x48]
	ldr r0, _02233600 ; =0x00000C03
	tst r0, r1
	bne _022335CC
	bl sub_02020AA4
	cmp r0, #0
	beq _022335D2
_022335CC:
	add r0, r5, #0
	add r0, #0xf0
	str r4, [r0]
_022335D2:
	add r0, r5, #0
	add r0, #0xf0
	ldr r0, [r0]
	cmp r4, r0
	beq _022335F0
	mov r1, #1
	add r0, r5, #0
	mvn r1, r1
	bl ov11_0223A424
	add r0, r5, #0
	add r0, #0xf0
	ldr r0, [r0]
	add r0, r0, #1
	b _022335F2
_022335F0:
	mov r0, #0
_022335F2:
	add r5, #0xf0
	str r0, [r5]
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_022335FC: .word gSystem
_02233600: .word 0x00000C03

	thumb_func_start ov11_02233604
ov11_02233604: ; 0x02233604
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0223C230
	add r3, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r7, #0
	bl ov11_02255D00
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_0223363C
ov11_0223363C: ; 0x0223363C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	str r0, [sp]
	add r0, r6, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r6, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r6, #0
	bl ov11_0223A404
	str r0, [sp, #4]
	add r0, r6, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r6, #0
	bl ov11_0223A404
	add r5, r0, #0
	ldr r0, [sp]
	ldr r2, [sp, #4]
	add r1, r6, #0
	bl ov11_0223A444
	cmp r7, #6
	bhi _022336DA
	add r1, r7, r7
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02233686: ; jump table
	.short _02233694 - _02233686 - 2 ; case 0
	.short _0223369E - _02233686 - 2 ; case 1
	.short _022336A8 - _02233686 - 2 ; case 2
	.short _022336B2 - _02233686 - 2 ; case 3
	.short _022336BC - _02233686 - 2 ; case 4
	.short _022336C6 - _02233686 - 2 ; case 5
	.short _022336D0 - _02233686 - 2 ; case 6
_02233694:
	ldr r0, [r0]
	cmp r0, r4
	beq _022336DA
	mov r5, #0
	b _022336DA
_0223369E:
	ldr r0, [r0]
	cmp r0, r4
	bne _022336DA
	mov r5, #0
	b _022336DA
_022336A8:
	ldr r0, [r0]
	cmp r0, r4
	bgt _022336DA
	mov r5, #0
	b _022336DA
_022336B2:
	ldr r0, [r0]
	cmp r0, r4
	ble _022336DA
	mov r5, #0
	b _022336DA
_022336BC:
	ldr r0, [r0]
	tst r0, r4
	bne _022336DA
	mov r5, #0
	b _022336DA
_022336C6:
	ldr r0, [r0]
	tst r0, r4
	beq _022336DA
	mov r5, #0
	b _022336DA
_022336D0:
	ldr r0, [r0]
	and r0, r4
	cmp r4, r0
	beq _022336DA
	mov r5, #0
_022336DA:
	cmp r5, #0
	beq _022336E6
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_0223A424
_022336E6:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_022336EC
ov11_022336EC: ; 0x022336EC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r1, #0
	str r0, [sp]
	add r0, r6, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r6, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r6, #0
	bl ov11_0223A404
	str r0, [sp, #4]
	add r0, r6, #0
	bl ov11_0223A404
	str r0, [sp, #8]
	add r0, r6, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r6, #0
	bl ov11_0223A404
	add r5, r0, #0
	ldr r0, [sp]
	ldr r2, [sp, #4]
	add r1, r6, #0
	bl ov11_0223C230
	add r1, r0, #0
	ldr r2, [sp, #8]
	add r0, r6, #0
	mov r3, #0
	bl ov11_02243420
	cmp r7, #6
	bhi _02233790
	add r1, r7, r7
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223374A: ; jump table
	.short _02233758 - _0223374A - 2 ; case 0
	.short _02233760 - _0223374A - 2 ; case 1
	.short _02233768 - _0223374A - 2 ; case 2
	.short _02233770 - _0223374A - 2 ; case 3
	.short _02233778 - _0223374A - 2 ; case 4
	.short _02233780 - _0223374A - 2 ; case 5
	.short _02233788 - _0223374A - 2 ; case 6
_02233758:
	cmp r0, r4
	beq _02233790
	mov r5, #0
	b _02233790
_02233760:
	cmp r0, r4
	bne _02233790
	mov r5, #0
	b _02233790
_02233768:
	cmp r0, r4
	bgt _02233790
	mov r5, #0
	b _02233790
_02233770:
	cmp r0, r4
	ble _02233790
	mov r5, #0
	b _02233790
_02233778:
	tst r0, r4
	bne _02233790
	mov r5, #0
	b _02233790
_02233780:
	tst r0, r4
	beq _02233790
	mov r5, #0
	b _02233790
_02233788:
	and r0, r4
	cmp r4, r0
	beq _02233790
	mov r5, #0
_02233790:
	cmp r5, #0
	beq _0223379C
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_0223A424
_0223379C:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_022337A4
ov11_022337A4: ; 0x022337A4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02255D20
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_022337C0
ov11_022337C0: ; 0x022337C0
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A434
	mov r0, #0
	pop {r4, pc}

	thumb_func_start ov11_022337E0
ov11_022337E0: ; 0x022337E0
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r2, _02233804 ; =0x00003044
	add r0, r4, #0
	ldr r2, [r4, r2]
	mov r1, #0x1e
	lsl r2, r2, #4
	add r3, r4, r2
	ldr r2, _02233808 ; =0x000003DE
	ldrh r2, [r3, r2]
	bl ov11_0223A434
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_02233804: .word 0x00003044
_02233808: .word 0x000003DE

	thumb_func_start ov11_0223380C
ov11_0223380C: ; 0x0223380C
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	ldr r2, _02233890 ; =0x0000213C
	mov r1, #1
	ldr r3, [r4, r2]
	bic r3, r1
	str r3, [r4, r2]
	ldr r3, [r4, r2]
	ldr r1, _02233894 ; =0xFFFFBFFF
	and r1, r3
	mov r3, #0x49
	lsl r3, r3, #2
	str r1, [r4, r2]
	ldr r2, [r4, r3]
	ldr r1, _02233898 ; =0x00003044
	cmp r0, #0
	str r2, [r4, r1]
	bne _02233866
	mov r0, #1
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r3, [r4, r3]
	ldr r2, [r4, #0x64]
	lsl r3, r3, #0x10
	add r0, r5, #0
	add r1, r4, #0
	lsr r3, r3, #0x10
	bl ov11_02244C28
	str r0, [r4, #0x6c]
	ldr r1, [r4, #0x64]
	lsl r1, r1, #4
	add r2, r4, r1
	ldr r1, _0223389C ; =0x000021AC
	str r0, [r2, r1]
_02233866:
	ldr r0, [r4, #0x6c]
	cmp r0, #0xff
	bne _0223387C
	mov r2, #0x26
	str r2, [r4, #0xc]
	add r0, r4, #0
	mov r1, #1
	add r2, #0xf3
	bl ov11_0223A434
	b _02233888
_0223387C:
	ldr r2, _02233898 ; =0x00003044
	add r0, r4, #0
	ldr r2, [r4, r2]
	mov r1, #0
	bl ov11_0223A434
_02233888:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_02233890: .word 0x0000213C
_02233894: .word 0xFFFFBFFF
_02233898: .word 0x00003044
_0223389C: .word 0x000021AC

	thumb_func_start ov11_022338A0
ov11_022338A0: ; 0x022338A0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0222FF74
	mov r1, #1
	lsl r1, r1, #0xa
	tst r0, r1
	bne _022338C8
	add r0, r5, #0
	bl ov11_02230C50
	mov r1, #1
	tst r0, r1
	beq _022338D0
_022338C8:
	ldr r0, _022338F4 ; =0x00002150
	mov r1, #1
	str r1, [r4, r0]
	b _022338F0
_022338D0:
	ldr r3, [r4, #0x6c]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0
	bl ov11_0224C474
	str r0, [sp]
	ldr r3, _022338F8 ; =0x0000214C
	ldr r1, [r4, #0x64]
	ldr r2, [r4, #0x6c]
	ldr r3, [r4, r3]
	add r0, r4, #0
	bl ov11_0224BF3C
	ldr r1, _022338F4 ; =0x00002150
	str r0, [r4, r1]
_022338F0:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_022338F4: .word 0x00002150
_022338F8: .word 0x0000214C

	thumb_func_start CalcExperienceGain
CalcExperienceGain: ; 0x022338FC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	add r7, r0, #0
	bl ov11_0222FF74
	add r4, r0, #0
	ldr r1, [r5, #0x74]
	add r0, r7, #0
	bl ov11_0222FF7C
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r1, r0, #0
	ldr r0, _02233A70 ; =0x00000195
	ldrb r2, [r6, r0]
	mov r0, #1
	tst r0, r2
	beq _02233936
	mov r0, #0xa9
	lsl r0, r0, #2
	tst r0, r4
	beq _02233938
_02233936:
	b _02233A64
_02233938:
	mov r0, #0
	str r0, [sp, #4]
	ldr r1, [sp, #4]
	str r0, [sp]
	add r4, r0, #0
	add r0, r7, #0
	bl ov11_0222FF88
	bl GetPartyCount
	cmp r0, #0
	ble _022339C6
_02233950:
	add r0, r7, #0
	mov r1, #0
	add r2, r4, #0
	bl ov11_02230014
	mov r1, #5
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _022339B4
	add r0, r6, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _022339B4
	add r0, r4, #0
	bl MaskOfFlagNo
	ldr r1, [r5, #0x74]
	asr r1, r1, #1
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1d
	add r1, r5, r1
	add r1, #0xa4
	ldr r1, [r1]
	tst r0, r1
	beq _02233994
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
_02233994:
	add r0, r6, #0
	mov r1, #6
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	add r0, r5, #0
	mov r2, #1
	bl ov11_0224C12C
	cmp r0, #0x32
	bne _022339B4
	ldr r0, [sp]
	add r0, r0, #1
	str r0, [sp]
_022339B4:
	add r0, r7, #0
	mov r1, #0
	add r4, r4, #1
	bl ov11_0222FF88
	bl GetPartyCount
	cmp r4, r0
	blt _02233950
_022339C6:
	ldr r1, [r5, #0x74]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	mov r0, #0xb5
	lsl r0, r0, #6
	ldrh r0, [r1, r0]
	mov r1, #9 ; BASE_EXP_YIELD
	bl GetMonBaseStat
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r2, [r5, #0x74]
	mov r0, #0xc0
	mul r0, r2
	add r2, r5, r0
	ldr r0, _02233A74 ; =0x00002D74
	ldrb r0, [r2, r0]
	mul r0, r1
	mov r1, #7
	bl _s32_div_f
	lsl r0, r0, #0x10
	ldr r1, [sp]
	lsr r0, r0, #0x10
	cmp r1, #0
	beq _02233A3E
	lsr r4, r0, #1
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl _s32_div_f
	add r1, r5, #0
	add r1, #0x9c
	str r0, [r1]
	add r0, r5, #0
	add r0, #0x9c
	ldr r0, [r0]
	cmp r0, #0
	bne _02233A1E
	add r0, r5, #0
	mov r1, #1
	add r0, #0x9c
	str r1, [r0]
_02233A1E:
	ldr r1, [sp]
	add r0, r4, #0
	bl _s32_div_f
	add r1, r5, #0
	add r1, #0xa0
	str r0, [r1]
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	cmp r0, #0
	bne _02233A6A
	mov r0, #1
	add r5, #0xa0
	str r0, [r5]
	b _02233A6A
_02233A3E:
	ldr r1, [sp, #4]
	bl _s32_div_f
	add r1, r5, #0
	add r1, #0x9c
	str r0, [r1]
	add r0, r5, #0
	add r0, #0x9c
	ldr r0, [r0]
	cmp r0, #0
	bne _02233A5C
	add r0, r5, #0
	mov r1, #1
	add r0, #0x9c
	str r1, [r0]
_02233A5C:
	mov r0, #0
	add r5, #0xa0
	str r0, [r5]
	b _02233A6A
_02233A64:
	add r0, r5, #0
	bl ov11_0223A424
_02233A6A:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02233A70: .word 0x00000195
_02233A74: .word 0x00002D74

	thumb_func_start ov11_02233A78
ov11_02233A78: ; 0x02233A78
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	mov r0, #5
	mov r1, #0x58
	bl AllocFromHeap
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r2, #0
	str r5, [r0]
	ldr r0, [r4, r1]
	str r4, [r0, #4]
	ldr r0, [r4, r1]
	str r2, [r0, #0x28]
	ldr r0, [r4, r1]
	str r2, [r0, #0x48]
	ldr r0, _02233AB4 ; =ov11_0223A79C
	ldr r1, [r4, r1]
	bl sub_0200CA44
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02233AB4: .word ov11_0223A79C

	thumb_func_start ov11_02233AB8
ov11_02233AB8: ; 0x02233AB8
	push {r3, lr}
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _02233ACC
	add r0, r1, #0
	mov r1, #1
	bl ov11_0223A424
_02233ACC:
	mov r0, #0
	pop {r3, pc}

	thumb_func_start ov11_02233AD0
ov11_02233AD0: ; 0x02233AD0
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_02233AE8
ov11_02233AE8: ; 0x02233AE8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r1, [sp, #8]
	add r6, r0, #0
	bl ov11_0222FF84
	add r7, r0, #0
	ldr r0, [sp, #8]
	mov r1, #1
	bl ov11_0223A424
	mov r4, #0
	add r5, r4, #0
	cmp r7, #0
	ble _02233B40
	ldr r0, [sp, #8]
	str r0, [sp, #0xc]
_02233B0A:
	mov r0, #0x4f
	ldr r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r1, [r1, r0]
	mov r0, #1
	tst r0, r1
	beq _02233B34
	add r0, r5, #0
	bl MaskOfFlagNo
	orr r4, r0
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	ldr r1, [sp, #8]
	add r0, r6, #0
	add r2, r5, #0
	mov r3, #1
	bl ov11_022558E0
_02233B34:
	ldr r0, [sp, #0xc]
	add r5, r5, #1
	add r0, r0, #4
	str r0, [sp, #0xc]
	cmp r5, r7
	blt _02233B0A
_02233B40:
	mov r5, #0
	cmp r7, #0
	ble _02233B98
_02233B46:
	add r0, r6, #0
	bl ov11_0222FF74
	cmp r0, #7
	bne _02233B80
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_022302BC
	str r0, [sp, #0x10]
	add r0, r5, #0
	bl MaskOfFlagNo
	tst r0, r4
	bne _02233B92
	ldr r0, [sp, #0x10]
	bl MaskOfFlagNo
	tst r0, r4
	bne _02233B92
	add r0, r5, #0
	bl MaskOfFlagNo
	orr r4, r0
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_022564CC
	b _02233B92
_02233B80:
	add r0, r5, #0
	bl MaskOfFlagNo
	tst r0, r4
	bne _02233B92
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_022564CC
_02233B92:
	add r5, r5, #1
	cmp r5, r7
	blt _02233B46
_02233B98:
	mov r0, #0
	cmp r7, #0
	ble _02233BBA
	mov r1, #0x4f
	ldr r4, [sp, #8]
	lsl r1, r1, #2
	mov r2, #1
_02233BA6:
	ldr r3, [r4, r1]
	tst r3, r2
	beq _02233BB2
	ldr r1, [sp, #8]
	str r0, [r1, #0x78]
	b _02233BBA
_02233BB2:
	add r0, r0, #1
	add r4, r4, #4
	cmp r0, r7
	blt _02233BA6
_02233BBA:
	mov r0, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov11_02233BC0
ov11_02233BC0: ; 0x02233BC0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r0, [sp]
	add r5, r1, #0
	bl ov11_0222FF84
	str r0, [sp, #8]
	mov r6, #0
	ldr r1, [sp, #8]
	add r0, r6, #0
	cmp r1, #0
	ble _02233BF2
	mov r3, #0x4f
	add r1, r5, #0
	lsl r3, r3, #2
	mov r4, #1
_02233BE0:
	ldr r2, [r1, r3]
	tst r2, r4
	beq _02233BE8
	add r6, r6, #1
_02233BE8:
	ldr r2, [sp, #8]
	add r0, r0, #1
	add r1, r1, #4
	cmp r0, r2
	blt _02233BE0
_02233BF2:
	ldr r0, [sp, #8]
	mov r4, #0
	cmp r0, #0
	ble _02233C6C
	str r5, [sp, #4]
	add r7, r5, #0
_02233BFE:
	mov r0, #0x4f
	ldr r1, [sp, #4]
	lsl r0, r0, #2
	ldr r1, [r1, r0]
	mov r0, #1
	tst r0, r1
	beq _02233C58
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0224AD90
	cmp r0, #0
	beq _02233C58
	mov r0, #0x23
	lsl r0, r0, #8
	ldrb r0, [r7, r0]
	add r1, r5, r4
	sub r6, r6, #1
	sub r2, r0, #1
	ldr r0, _02233C8C ; =0x000021A0
	strb r2, [r1, r0]
	add r0, r4, #0
	bl MaskOfFlagNo
	mov r1, #0x85
	lsl r1, r1, #6
	ldr r1, [r5, r1]
	lsl r0, r0, #0x18
	tst r0, r1
	bne _02233C58
	add r0, r4, #0
	bl MaskOfFlagNo
	mov r1, #0x85
	lsl r1, r1, #6
	ldr r1, [r5, r1]
	lsl r0, r0, #0x18
	orr r1, r0
	mov r0, #0x85
	lsl r0, r0, #6
	str r1, [r5, r0]
	ldr r0, [sp]
	add r1, r4, #0
	bl ov11_022564CC
_02233C58:
	ldr r0, [sp, #4]
	add r4, r4, #1
	add r0, r0, #4
	str r0, [sp, #4]
	mov r0, #1
	lsl r0, r0, #8
	add r7, r7, r0
	ldr r0, [sp, #8]
	cmp r4, r0
	blt _02233BFE
_02233C6C:
	cmp r6, #0
	bne _02233C84
	mov r1, #0x85
	lsl r1, r1, #6
	ldr r2, [r5, r1]
	ldr r0, _02233C90 ; =0xF0FFFFFF
	and r0, r2
	str r0, [r5, r1]
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
_02233C84:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02233C8C: .word 0x000021A0
_02233C90: .word 0xF0FFFFFF

	thumb_func_start ov11_02233C94
ov11_02233C94: ; 0x02233C94
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	cmp r0, #1
	beq _02233CB6
	cmp r0, #6
	beq _02233CBA
	cmp r0, #0x12
	beq _02233CBE
	b _02233CC0
_02233CB6:
	ldr r4, [r5, #0x64]
	b _02233CC0
_02233CBA:
	ldr r4, [r5, #0x78]
	b _02233CC0
_02233CBE:
	ldr r4, [r5, #0x6c]
_02233CC0:
	mov r0, #0x4f
	lsl r0, r0, #2
	add r3, r5, r0
	lsl r2, r4, #2
	ldr r1, [r3, r2]
	mov r0, #1
	bic r1, r0
	add r0, r4, #0
	str r1, [r3, r2]
	bl MaskOfFlagNo
	ldr r3, _02233D24 ; =0x00003108
	mov r2, #0
	mvn r2, r2
	eor r0, r2
	ldrb r1, [r5, r3]
	add r2, r4, #0
	and r0, r1
	ldr r1, _02233D28 ; =0x000021A0
	strb r0, [r5, r3]
	add r0, r5, r1
	sub r1, r1, #4
	add r6, r5, r1
	ldrb r1, [r0, r4]
	strb r1, [r6, r4]
	mov r1, #6
	strb r1, [r0, r4]
	ldrb r3, [r6, r4]
	add r0, r7, #0
	add r1, r5, #0
	bl ov11_02242B78
	ldrb r3, [r6, r4]
	add r0, r7, #0
	add r1, r5, #0
	add r2, r4, #0
	bl ov11_0224B290
	ldr r0, _02233D2C ; =0x00002E4C
	add r2, r4, #0
	ldr r1, [r5, r0]
	ldr r0, _02233D30 ; =0x00003122
	strh r1, [r5, r0]
	add r0, r7, #0
	add r1, r5, #0
	bl ov11_02245608
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02233D24: .word 0x00003108
_02233D28: .word 0x000021A0
_02233D2C: .word 0x00002E4C
_02233D30: .word 0x00003122

	thumb_func_start ov11_02233D34
ov11_02233D34: ; 0x02233D34
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	bl ov11_0222FF84
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r7, r0, #0
	mov r0, #0
	cmp r4, #0
	ble _02233D76
	mov r2, #0x4f
	add r1, r5, #0
	lsl r2, r2, #2
	mov r3, #1
_02233D5C:
	ldr r6, [r1, r2]
	tst r6, r3
	beq _02233D6E
	str r0, [r5, #0x78]
	add r0, r5, #0
	add r1, r7, #0
	bl ov11_0223A424
	b _02233D76
_02233D6E:
	add r0, r0, #1
	add r1, r1, #4
	cmp r0, r4
	blt _02233D5C
_02233D76:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_02233D7C
ov11_02233D7C: ; 0x02233D7C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	mov r0, #5
	mov r1, #0x58
	bl AllocFromHeap
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r2, #0
	str r5, [r0]
	ldr r0, [r4, r1]
	str r4, [r0, #4]
	ldr r0, [r4, r1]
	str r2, [r0, #0x28]
	ldr r0, [r4, r1]
	str r6, [r0, #0x24]
	add r0, r1, #0
	sub r0, #0x50
	ldr r3, [r4, r0]
	ldr r0, [r4, r1]
	str r3, [r0, #0x2c]
	ldr r0, _02233DC8 ; =ov11_0223B49C
	ldr r1, [r4, r1]
	bl sub_0200CA44
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_02233DC8: .word ov11_0223B49C

	thumb_func_start ov11_02233DCC
ov11_02233DCC: ; 0x02233DCC
	push {r3, lr}
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _02233DE0
	add r0, r1, #0
	mov r1, #1
	bl ov11_0223A424
_02233DE0:
	mov r0, #0
	pop {r3, pc}

	thumb_func_start ov11_02233DE4
ov11_02233DE4: ; 0x02233DE4
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	add r6, r0, #0
	ldr r0, _02233E4C ; =0x0000217D
	ldrb r0, [r5, r0]
	cmp r0, #0
	bne _02233E46
	cmp r4, #0
	bne _02233E36
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl ov11_02246D1C
	cmp r0, #0x5c
	bne _02233E1C
	mov r4, #5
	b _02233E36
_02233E1C:
	bl LCRandom
	mov r1, #3
	and r0, r1
	cmp r0, #2
	bge _02233E2C
	add r4, r0, #2
	b _02233E36
_02233E2C:
	bl LCRandom
	mov r1, #3
	and r0, r1
	add r4, r0, #2
_02233E36:
	lsl r0, r4, #0x18
	ldr r1, _02233E50 ; =0x0000217C
	lsr r2, r0, #0x18
	strb r2, [r5, r1]
	add r0, r1, #1
	strb r2, [r5, r0]
	add r1, #0xc
	str r6, [r5, r1]
_02233E46:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_02233E4C: .word 0x0000217D
_02233E50: .word 0x0000217C

	thumb_func_start ov11_02233E54
ov11_02233E54: ; 0x02233E54
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r7, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp]
	add r0, r4, #0
	bl ov11_0223A404
	add r5, r0, #0
	ldr r2, [sp]
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_0223A444
	add r4, r0, #0
	cmp r6, #0x14
	bhi _02233F3E
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02233E96: ; jump table
	.short _02233F3E - _02233E96 - 2 ; case 0
	.short _02233F3E - _02233E96 - 2 ; case 1
	.short _02233F3E - _02233E96 - 2 ; case 2
	.short _02233F3E - _02233E96 - 2 ; case 3
	.short _02233F3E - _02233E96 - 2 ; case 4
	.short _02233F3E - _02233E96 - 2 ; case 5
	.short _02233F3E - _02233E96 - 2 ; case 6
	.short _02233EC0 - _02233E96 - 2 ; case 7
	.short _02233EC4 - _02233E96 - 2 ; case 8
	.short _02233ECC - _02233E96 - 2 ; case 9
	.short _02233ED4 - _02233E96 - 2 ; case 10
	.short _02233EDC - _02233E96 - 2 ; case 11
	.short _02233EEA - _02233E96 - 2 ; case 12
	.short _02233EF4 - _02233E96 - 2 ; case 13
	.short _02233F00 - _02233E96 - 2 ; case 14
	.short _02233F08 - _02233E96 - 2 ; case 15
	.short _02233F10 - _02233E96 - 2 ; case 16
	.short _02233F1A - _02233E96 - 2 ; case 17
	.short _02233F20 - _02233E96 - 2 ; case 18
	.short _02233F2E - _02233E96 - 2 ; case 19
	.short _02233F36 - _02233E96 - 2 ; case 20
_02233EC0:
	str r5, [r4]
	b _02233F42
_02233EC4:
	ldr r0, [r4]
	add r0, r0, r5
	str r0, [r4]
	b _02233F42
_02233ECC:
	ldr r0, [r4]
	sub r0, r0, r5
	str r0, [r4]
	b _02233F42
_02233ED4:
	ldr r0, [r4]
	orr r0, r5
	str r0, [r4]
	b _02233F42
_02233EDC:
	mov r0, #0
	mvn r0, r0
	ldr r1, [r4]
	eor r0, r5
	and r0, r1
	str r0, [r4]
	b _02233F42
_02233EEA:
	ldr r0, [r4]
	add r1, r0, #0
	mul r1, r5
	str r1, [r4]
	b _02233F42
_02233EF4:
	ldr r0, [r4]
	add r1, r5, #0
	bl _s32_div_f
	str r0, [r4]
	b _02233F42
_02233F00:
	ldr r0, [r4]
	lsl r0, r5
	str r0, [r4]
	b _02233F42
_02233F08:
	ldr r0, [r4]
	asr r0, r5
	str r0, [r4]
	b _02233F42
_02233F10:
	add r0, r5, #0
	bl MaskOfFlagNo
	str r0, [r4]
	b _02233F42
_02233F1A:
	bl GF_AssertFail
	b _02233F42
_02233F20:
	ldr r0, [r4]
	sub r0, r0, r5
	str r0, [r4]
	bpl _02233F42
	mov r0, #0
	str r0, [r4]
	b _02233F42
_02233F2E:
	ldr r0, [r4]
	eor r0, r5
	str r0, [r4]
	b _02233F42
_02233F36:
	ldr r0, [r4]
	and r0, r5
	str r0, [r4]
	b _02233F42
_02233F3E:
	bl GF_AssertFail
_02233F42:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_02233F48
ov11_02233F48: ; 0x02233F48
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r0, [sp]
	mov r0, #0xb5
	add r5, r1, #0
	lsl r0, r0, #6
	add r2, r5, r0
	add r0, r5, #0
	add r0, #0x94
	ldr r1, [r0]
	mov r0, #0xc0
	mul r0, r1
	add r6, r2, r0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	str r0, [sp, #0x14]
	add r0, r5, #0
	bl ov11_0223A404
	str r0, [sp, #0x10]
	add r0, r5, #0
	bl ov11_0223A404
	ldr r1, _022342D0 ; =0x0000213C
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #8]
	ldr r2, [r5, r1]
	ldr r0, _022342D4 ; =0xFFFDFFFF
	and r2, r0
	str r2, [r5, r1]
	add r1, r5, #0
	add r1, #0x8c
	ldr r4, [r1]
	cmp r4, #0x2e
	blt _02233FA8
	asr r7, r0, #0x11
	mov r0, #0x4e
	mov r1, #0xd
	lsl r0, r0, #2
	sub r4, #0x2e
	str r1, [r5, r0]
	b _02233FD8
_02233FA8:
	cmp r4, #0x27
	blt _02233FBA
	mov r0, #0x4e
	mov r1, #0xc
	lsl r0, r0, #2
	sub r4, #0x27
	mov r7, #2
	str r1, [r5, r0]
	b _02233FD8
_02233FBA:
	cmp r4, #0x16
	blt _02233FCC
	asr r7, r0, #0x12
	mov r0, #0x4e
	mov r1, #0xd
	lsl r0, r0, #2
	sub r4, #0x16
	str r1, [r5, r0]
	b _02233FD8
_02233FCC:
	mov r0, #0x4e
	mov r1, #0xc
	lsl r0, r0, #2
	sub r4, #0xf
	mov r7, #1
	str r1, [r5, r0]
_02233FD8:
	cmp r7, #0
	bgt _02233FDE
	b _02234116
_02233FDE:
	add r1, r4, #1
	add r6, #0x18
	add r0, r6, r1
	str r0, [sp, #4]
	ldrsb r0, [r6, r1]
	cmp r0, #0xc
	bne _02234042
	ldr r1, _022342D0 ; =0x0000213C
	mov r0, #2
	ldr r2, [r5, r1]
	lsl r0, r0, #0x10
	orr r0, r2
	str r0, [r5, r1]
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	sub r0, r0, #2
	cmp r0, #1
	bhi _0223400E
	ldr r1, [sp, #0x10]
	add r0, r5, #0
	bl ov11_0223A424
	b _02234538
_0223400E:
	add r0, r5, #0
	mov r1, #0x8e
	add r0, #0xf6
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #0xc
	add r0, #0xf5
	strb r1, [r0]
	add r1, r5, #0
	add r1, #0x94
	ldr r1, [r1]
	add r0, r5, #0
	bl ov11_0224682C
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	add r0, r5, #0
	add r1, r4, #1
	add r0, #0xfc
	str r1, [r0]
	ldr r1, [sp, #0x14]
	add r0, r5, #0
	bl ov11_0223A424
	b _02234538
_02234042:
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #3
	bne _0223408E
	add r0, r5, #0
	ldr r1, _022342D8 ; =0x0000026E
	add r0, #0xf6
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #0x27
	add r0, #0xf5
	strb r1, [r0]
	add r1, r5, #0
	add r1, #0x94
	ldr r1, [r1]
	add r0, r5, #0
	bl ov11_0224682C
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	add r0, r5, #0
	add r0, #0x94
	ldr r0, [r0]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	ldr r0, _022342DC ; =0x00002D67
	add r2, r5, r2
	ldrb r2, [r2, r0]
	add r0, r5, #0
	add r0, #0xfc
	str r2, [r0]
	add r0, r4, #1
	add r1, #0x40
	str r0, [r5, r1]
	b _022340FA
_0223408E:
	cmp r0, #5
	bne _022340CA
	mov r1, #0xbd
	add r0, r5, #0
	lsl r1, r1, #2
	add r0, #0xf6
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #0x2d
	add r0, #0xf5
	strb r1, [r0]
	add r1, r5, #0
	add r1, #0x94
	ldr r1, [r1]
	add r0, r5, #0
	bl ov11_0224682C
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	mov r1, #0x4a
	lsl r1, r1, #2
	ldr r2, [r5, r1]
	add r0, r5, #0
	add r0, #0xfc
	str r2, [r0]
	add r0, r4, #1
	sub r1, #0x28
	str r0, [r5, r1]
	b _022340FA
_022340CA:
	cmp r7, #1
	bne _022340D2
	ldr r1, _022342E0 ; =0x000002EE
	b _022340D4
_022340D2:
	ldr r1, _022342E4 ; =0x000002F1
_022340D4:
	add r0, r5, #0
	add r0, #0xf6
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #0xc
	add r0, #0xf5
	strb r1, [r0]
	add r1, r5, #0
	add r1, #0x94
	ldr r1, [r1]
	add r0, r5, #0
	bl ov11_0224682C
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	add r0, r4, #1
	add r5, #0xfc
	str r0, [r5]
_022340FA:
	ldr r0, [sp, #4]
	mov r1, #0
	ldrsb r0, [r0, r1]
	add r2, r0, r7
	ldr r0, [sp, #4]
	strb r2, [r0]
	ldrsb r0, [r0, r1]
	cmp r0, #0xc
	bgt _0223410E
	b _02234538
_0223410E:
	ldr r0, [sp, #4]
	mov r1, #0xc
	strb r1, [r0]
	b _02234538
_02234116:
	add r0, r5, #0
	add r0, #0x90
	ldr r1, [r0]
	mov r0, #2
	lsl r0, r0, #0x1a
	tst r1, r0
	beq _02234126
	b _0223449C
_02234126:
	add r1, r5, #0
	add r1, #0x94
	ldr r1, [r1]
	ldr r2, [r5, #0x64]
	cmp r2, r1
	bne _02234134
	b _022343E4
_02234134:
	ldr r0, [sp]
	bl ov11_02230270
	lsl r0, r0, #3
	mov r1, #0x71
	add r0, r5, r0
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1d
	beq _02234172
	add r0, r5, #0
	sub r1, #0xb3
	add r0, #0xf6
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #2
	add r0, #0xf5
	strb r1, [r0]
	add r1, r5, #0
	add r1, #0x94
	ldr r1, [r1]
	add r0, r5, #0
	bl ov11_0224682C
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	mov r0, #1
	str r0, [sp, #8]
	b _0223444C
_02234172:
	add r2, r5, #0
	add r2, #0x94
	ldr r1, [r5, #0x64]
	ldr r2, [r2]
	add r0, r5, #0
	mov r3, #0x1d
	bl ov11_02246D84
	cmp r0, #1
	beq _0223419A
	add r2, r5, #0
	add r2, #0x94
	ldr r1, [r5, #0x64]
	ldr r2, [r2]
	add r0, r5, #0
	mov r3, #0x49
	bl ov11_02246D84
	cmp r0, #1
	bne _0223423C
_0223419A:
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #3
	bne _022341FE
	add r0, r5, #0
	ldr r1, _022342E8 ; =0x000002D7
	add r0, #0xf6
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #0x35
	add r0, #0xf5
	strb r1, [r0]
	add r1, r5, #0
	add r1, #0x94
	ldr r1, [r1]
	add r0, r5, #0
	bl ov11_0224682C
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	add r0, r5, #0
	add r0, #0x94
	ldr r1, [r0]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _022342DC ; =0x00002D67
	ldrb r1, [r1, r0]
	add r0, r5, #0
	add r0, #0xfc
	str r1, [r0]
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl ov11_0224682C
	mov r1, #1
	lsl r1, r1, #8
	str r0, [r5, r1]
	ldr r0, [r5, #0x64]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	ldr r0, _022342DC ; =0x00002D67
	add r2, r5, r2
	ldrb r0, [r2, r0]
	add r1, #0x44
	str r0, [r5, r1]
	b _02234236
_022341FE:
	add r0, r5, #0
	ldr r1, _022342EC ; =0x0000029D
	add r0, #0xf6
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #0xb
	add r0, #0xf5
	strb r1, [r0]
	add r1, r5, #0
	add r1, #0x94
	ldr r1, [r1]
	add r0, r5, #0
	bl ov11_0224682C
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	add r0, r5, #0
	add r0, #0x94
	ldr r1, [r0]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _022342DC ; =0x00002D67
	ldrb r1, [r1, r0]
	add r0, r5, #0
	add r0, #0xfc
	str r1, [r0]
_02234236:
	mov r0, #1
	str r0, [sp, #8]
	b _0223444C
_0223423C:
	add r2, r5, #0
	add r2, #0x94
	ldr r1, [r5, #0x64]
	ldr r2, [r2]
	add r0, r5, #0
	mov r3, #0x33
	bl ov11_02246D84
	cmp r0, #1
	bne _02234256
	add r0, r4, #1
	cmp r0, #6
	beq _0223426E
_02234256:
	add r2, r5, #0
	add r2, #0x94
	ldr r1, [r5, #0x64]
	ldr r2, [r2]
	add r0, r5, #0
	mov r3, #0x34
	bl ov11_02246D84
	cmp r0, #1
	bne _02234338
	cmp r4, #0
	bne _02234338
_0223426E:
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #3
	bne _022342F0
	add r0, r5, #0
	ldr r1, _022342E8 ; =0x000002D7
	add r0, #0xf6
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #0x35
	add r0, #0xf5
	strb r1, [r0]
	add r1, r5, #0
	add r1, #0x94
	ldr r1, [r1]
	add r0, r5, #0
	bl ov11_0224682C
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	add r0, r5, #0
	add r0, #0x94
	ldr r1, [r0]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _022342DC ; =0x00002D67
	ldrb r1, [r1, r0]
	add r0, r5, #0
	add r0, #0xfc
	str r1, [r0]
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl ov11_0224682C
	mov r1, #1
	lsl r1, r1, #8
	str r0, [r5, r1]
	ldr r0, [r5, #0x64]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	ldr r0, _022342DC ; =0x00002D67
	add r2, r5, r2
	ldrb r0, [r2, r0]
	add r1, #0x44
	b _02234330
	.align 2, 0
_022342D0: .word 0x0000213C
_022342D4: .word 0xFFFDFFFF
_022342D8: .word 0x0000026E
_022342DC: .word 0x00002D67
_022342E0: .word 0x000002EE
_022342E4: .word 0x000002F1
_022342E8: .word 0x000002D7
_022342EC: .word 0x0000029D
_022342F0:
	mov r1, #0xb
	add r0, r5, #0
	lsl r1, r1, #6
	add r0, #0xf6
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #0x27
	add r0, #0xf5
	strb r1, [r0]
	add r1, r5, #0
	add r1, #0x94
	ldr r1, [r1]
	add r0, r5, #0
	bl ov11_0224682C
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	add r0, r5, #0
	add r0, #0x94
	ldr r0, [r0]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	ldr r0, _02234540 ; =0x00002D67
	add r2, r5, r2
	ldrb r2, [r2, r0]
	add r0, r5, #0
	add r0, #0xfc
	str r2, [r0]
	add r0, r4, #1
	add r1, #0x40
_02234330:
	str r0, [r5, r1]
	mov r0, #1
	str r0, [sp, #8]
	b _0223444C
_02234338:
	add r0, r4, #1
	add r1, r6, r0
	mov r0, #0x18
	ldrsb r0, [r1, r0]
	cmp r0, #0
	bne _022343A2
	ldr r1, _02234544 ; =0x0000213C
	mov r0, #2
	ldr r2, [r5, r1]
	lsl r0, r0, #0x10
	orr r0, r2
	str r0, [r5, r1]
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	sub r0, r0, #2
	cmp r0, #1
	bhi _0223436A
	ldr r1, [sp, #0x10]
	add r0, r5, #0
	bl ov11_0223A424
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223436A:
	add r0, r5, #0
	mov r1, #0x91
	add r0, #0xf6
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #0xc
	add r0, #0xf5
	strb r1, [r0]
	add r1, r5, #0
	add r1, #0x94
	ldr r1, [r1]
	add r0, r5, #0
	bl ov11_0224682C
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	add r0, r5, #0
	add r1, r4, #1
	add r0, #0xfc
	str r1, [r0]
	ldr r1, [sp, #0x14]
	add r0, r5, #0
	bl ov11_0223A424
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_022343A2:
	add r2, r5, #0
	add r2, #0x94
	ldr r1, [r5, #0x64]
	ldr r2, [r2]
	add r0, r5, #0
	mov r3, #0x13
	bl ov11_02246D84
	cmp r0, #1
	bne _022343C6
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #2
	bne _022343C6
	mov r0, #1
	str r0, [sp, #8]
	b _0223444C
_022343C6:
	add r0, r5, #0
	add r0, #0x94
	ldr r1, [r0]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _02234548 ; =0x00002DB0
	ldr r1, [r1, r0]
	mov r0, #1
	lsl r0, r0, #0x18
	tst r0, r1
	beq _0223444C
	mov r0, #2
	str r0, [sp, #8]
	b _0223444C
_022343E4:
	add r1, r4, #1
	add r2, r6, r1
	mov r1, #0x18
	ldrsb r1, [r2, r1]
	cmp r1, #0
	bne _0223444C
	ldr r1, _02234544 ; =0x0000213C
	lsr r0, r0, #0xa
	ldr r2, [r5, r1]
	orr r0, r2
	str r0, [r5, r1]
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	sub r0, r0, #2
	cmp r0, #1
	bhi _02234414
	ldr r1, [sp, #0x10]
	add r0, r5, #0
	bl ov11_0223A424
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02234414:
	add r0, r5, #0
	mov r1, #0x91
	add r0, #0xf6
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #0xc
	add r0, #0xf5
	strb r1, [r0]
	add r1, r5, #0
	add r1, #0x94
	ldr r1, [r1]
	add r0, r5, #0
	bl ov11_0224682C
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	add r0, r5, #0
	add r1, r4, #1
	add r0, #0xfc
	str r1, [r0]
	ldr r1, [sp, #0x14]
	add r0, r5, #0
	bl ov11_0223A424
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223444C:
	ldr r0, [sp, #8]
	cmp r0, #2
	bne _0223446A
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #1
	bne _0223446A
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	bl ov11_0223A424
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223446A:
	ldr r0, [sp, #8]
	cmp r0, #0
	beq _02234488
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #2
	bne _02234488
	ldr r1, [sp, #0x10]
	add r0, r5, #0
	bl ov11_0223A424
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02234488:
	ldr r0, [sp, #8]
	cmp r0, #0
	beq _0223449C
	ldr r1, [sp, #0x14]
	add r0, r5, #0
	bl ov11_0223A424
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223449C:
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #3
	bne _022344F0
	add r0, r5, #0
	ldr r1, _0223454C ; =0x00000296
	add r0, #0xf6
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #0x36
	add r0, #0xf5
	strb r1, [r0]
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl ov11_0224682C
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _02234540 ; =0x00002D67
	ldrb r1, [r1, r0]
	add r0, r5, #0
	add r0, #0xfc
	str r1, [r0]
	add r1, r5, #0
	add r1, #0x94
	ldr r1, [r1]
	add r0, r5, #0
	bl ov11_0224682C
	mov r1, #1
	lsl r1, r1, #8
	str r0, [r5, r1]
	add r2, r4, #1
	add r0, r1, #4
	str r2, [r5, r0]
	b _02234524
_022344F0:
	mov r0, #0
	mvn r0, r0
	cmp r7, r0
	bne _022344FC
	ldr r1, _02234550 ; =0x000002FA
	b _022344FE
_022344FC:
	ldr r1, _02234554 ; =0x000002FD
_022344FE:
	add r0, r5, #0
	add r0, #0xf6
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #0xc
	add r0, #0xf5
	strb r1, [r0]
	add r1, r5, #0
	add r1, #0x94
	ldr r1, [r1]
	add r0, r5, #0
	bl ov11_0224682C
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	add r0, r4, #1
	add r5, #0xfc
	str r0, [r5]
_02234524:
	add r6, #0x18
	add r1, r4, #1
	ldrsb r0, [r6, r1]
	add r0, r0, r7
	strb r0, [r6, r1]
	ldrsb r0, [r6, r1]
	cmp r0, #0
	bge _02234538
	mov r0, #0
	strb r0, [r6, r1]
_02234538:
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02234540: .word 0x00002D67
_02234544: .word 0x0000213C
_02234548: .word 0x00002DB0
_0223454C: .word 0x00000296
_02234550: .word 0x000002FA
_02234554: .word 0x000002FD

	thumb_func_start ov11_02234558
ov11_02234558: ; 0x02234558
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	str r0, [sp, #8]
	add r0, r5, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	ldr r0, [sp]
	ldr r2, [sp, #8]
	add r1, r5, #0
	bl ov11_0223C230
	str r0, [sp, #4]
	ldr r1, [sp, #4]
	add r0, r5, #0
	add r2, r6, #0
	mov r3, #0
	bl ov11_02243420
	str r0, [sp, #0xc]
	cmp r7, #0x14
	bhi _02234644
	add r1, r7, r7
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022345B2: ; jump table
	.short _02234644 - _022345B2 - 2 ; case 0
	.short _02234644 - _022345B2 - 2 ; case 1
	.short _02234644 - _022345B2 - 2 ; case 2
	.short _02234644 - _022345B2 - 2 ; case 3
	.short _02234644 - _022345B2 - 2 ; case 4
	.short _02234644 - _022345B2 - 2 ; case 5
	.short _02234644 - _022345B2 - 2 ; case 6
	.short _022345DC - _022345B2 - 2 ; case 7
	.short _022345E0 - _022345B2 - 2 ; case 8
	.short _022345E6 - _022345B2 - 2 ; case 9
	.short _022345EC - _022345B2 - 2 ; case 10
	.short _022345F2 - _022345B2 - 2 ; case 11
	.short _022345FE - _022345B2 - 2 ; case 12
	.short _02234606 - _022345B2 - 2 ; case 13
	.short _02234610 - _022345B2 - 2 ; case 14
	.short _02234616 - _022345B2 - 2 ; case 15
	.short _0223461C - _022345B2 - 2 ; case 16
	.short _02234626 - _022345B2 - 2 ; case 17
	.short _0223462C - _022345B2 - 2 ; case 18
	.short _02234638 - _022345B2 - 2 ; case 19
	.short _0223463E - _022345B2 - 2 ; case 20
_022345DC:
	str r4, [sp, #0xc]
	b _02234648
_022345E0:
	add r0, r0, r4
	str r0, [sp, #0xc]
	b _02234648
_022345E6:
	sub r0, r0, r4
	str r0, [sp, #0xc]
	b _02234648
_022345EC:
	orr r0, r4
	str r0, [sp, #0xc]
	b _02234648
_022345F2:
	mov r1, #0
	mvn r1, r1
	eor r1, r4
	and r0, r1
	str r0, [sp, #0xc]
	b _02234648
_022345FE:
	add r1, r0, #0
	mul r1, r4
	str r1, [sp, #0xc]
	b _02234648
_02234606:
	add r1, r4, #0
	bl _s32_div_f
	str r0, [sp, #0xc]
	b _02234648
_02234610:
	lsl r0, r4
	str r0, [sp, #0xc]
	b _02234648
_02234616:
	asr r0, r4
	str r0, [sp, #0xc]
	b _02234648
_0223461C:
	add r0, r4, #0
	bl MaskOfFlagNo
	str r0, [sp, #0xc]
	b _02234648
_02234626:
	bl GF_AssertFail
	b _02234648
_0223462C:
	sub r0, r0, r4
	str r0, [sp, #0xc]
	bpl _02234648
	mov r0, #0
	str r0, [sp, #0xc]
	b _02234648
_02234638:
	eor r0, r4
	str r0, [sp, #0xc]
	b _02234648
_0223463E:
	and r0, r4
	str r0, [sp, #0xc]
	b _02234648
_02234644:
	bl GF_AssertFail
_02234648:
	cmp r6, #0x1a
	bne _0223465E
	ldr r1, [sp, #4]
	ldr r2, [sp, #0xc]
	lsl r1, r1, #0x18
	lsl r2, r2, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl ov11_0223D1C4
_0223465E:
	ldr r1, [sp, #4]
	add r0, r5, #0
	add r2, r6, #0
	add r3, sp, #0xc
	bl ov11_0224379C
	ldr r0, [sp]
	ldr r2, [sp, #4]
	add r1, r5, #0
	bl ov11_02245190
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_0223467C
ov11_0223467C: ; 0x0223467C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r6, #0
	add r1, r5, #0
	add r2, r7, #0
	bl ov11_0223C230
	ldr r1, _022346B4 ; =0x0000218C
	add r2, r5, r1
	lsl r1, r0, #2
	ldr r0, [r2, r1]
	orr r0, r4
	str r0, [r2, r1]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022346B4: .word 0x0000218C

	thumb_func_start ov11_022346B8
ov11_022346B8: ; 0x022346B8
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r5, #0
	add r2, r7, #0
	bl ov11_02255D3C
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_022346F0
ov11_022346F0: ; 0x022346F0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	str r0, [sp, #8]
	cmp r4, #0
	bne _02234766
	ldr r0, [sp]
	bl ov11_0222FF84
	mov r4, #0
	str r0, [sp, #4]
	cmp r0, #0
	ble _022347A8
_02234732:
	cmp r7, #0
	bne _02234750
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02246D1C
	cmp r6, r0
	bne _0223475C
	ldr r1, [sp, #8]
	add r0, r5, #0
	bl ov11_0223A424
	add r5, #0x80
	str r4, [r5]
	b _022347A8
_02234750:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02246D1C
	cmp r6, r0
	beq _022347A8
_0223475C:
	ldr r0, [sp, #4]
	add r4, r4, #1
	cmp r4, r0
	blt _02234732
	b _022347A8
_02234766:
	ldr r0, [sp]
	add r1, r5, #0
	add r2, r4, #0
	bl ov11_0223C230
	add r4, r0, #0
	cmp r7, #0
	bne _02234790
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02246D1C
	cmp r6, r0
	bne _022347A8
	ldr r1, [sp, #8]
	add r0, r5, #0
	bl ov11_0223A424
	add r5, #0x80
	str r4, [r5]
	b _022347A8
_02234790:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02246D1C
	cmp r6, r0
	beq _022347A8
	ldr r1, [sp, #8]
	add r0, r5, #0
	bl ov11_0223A424
	add r5, #0x80
	str r4, [r5]
_022347A8:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_022347B0
ov11_022347B0: ; 0x022347B0
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	add r6, r0, #0
	bl LCRandom
	add r1, r4, #1
	bl _s32_div_f
	mov r0, #0x4d
	add r1, r6, r1
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_022347E4
ov11_022347E4: ; 0x022347E4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	str r0, [sp]
	add r0, r7, #0
	add r1, r5, #0
	add r2, r4, #0
	bl ov11_0223A444
	add r4, r0, #0
	ldr r2, [sp]
	add r0, r7, #0
	add r1, r5, #0
	bl ov11_0223A444
	add r1, r0, #0
	cmp r6, #0x14
	bhi _022348F2
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02234832: ; jump table
	.short _022348F2 - _02234832 - 2 ; case 0
	.short _022348F2 - _02234832 - 2 ; case 1
	.short _022348F2 - _02234832 - 2 ; case 2
	.short _022348F2 - _02234832 - 2 ; case 3
	.short _022348F2 - _02234832 - 2 ; case 4
	.short _022348F2 - _02234832 - 2 ; case 5
	.short _022348F2 - _02234832 - 2 ; case 6
	.short _0223485C - _02234832 - 2 ; case 7
	.short _02234862 - _02234832 - 2 ; case 8
	.short _0223486C - _02234832 - 2 ; case 9
	.short _02234876 - _02234832 - 2 ; case 10
	.short _02234880 - _02234832 - 2 ; case 11
	.short _02234890 - _02234832 - 2 ; case 12
	.short _0223489A - _02234832 - 2 ; case 13
	.short _022348A6 - _02234832 - 2 ; case 14
	.short _022348B2 - _02234832 - 2 ; case 15
	.short _022348BE - _02234832 - 2 ; case 16
	.short _022348C8 - _02234832 - 2 ; case 17
	.short _022348CE - _02234832 - 2 ; case 18
	.short _022348DE - _02234832 - 2 ; case 19
	.short _022348E8 - _02234832 - 2 ; case 20
_0223485C:
	ldr r0, [r1]
	str r0, [r4]
	b _022348F6
_02234862:
	ldr r2, [r4]
	ldr r0, [r1]
	add r0, r2, r0
	str r0, [r4]
	b _022348F6
_0223486C:
	ldr r2, [r4]
	ldr r0, [r1]
	sub r0, r2, r0
	str r0, [r4]
	b _022348F6
_02234876:
	ldr r2, [r4]
	ldr r0, [r1]
	orr r0, r2
	str r0, [r4]
	b _022348F6
_02234880:
	mov r0, #0
	ldr r1, [r1]
	mvn r0, r0
	ldr r2, [r4]
	eor r0, r1
	and r0, r2
	str r0, [r4]
	b _022348F6
_02234890:
	ldr r2, [r4]
	ldr r0, [r1]
	mul r0, r2
	str r0, [r4]
	b _022348F6
_0223489A:
	ldr r0, [r4]
	ldr r1, [r1]
	bl _s32_div_f
	str r0, [r4]
	b _022348F6
_022348A6:
	ldr r2, [r4]
	ldr r0, [r1]
	add r1, r2, #0
	lsl r1, r0
	str r1, [r4]
	b _022348F6
_022348B2:
	ldr r2, [r4]
	ldr r0, [r1]
	add r1, r2, #0
	asr r1, r0
	str r1, [r4]
	b _022348F6
_022348BE:
	ldr r0, [r1]
	bl MaskOfFlagNo
	str r0, [r4]
	b _022348F6
_022348C8:
	ldr r0, [r4]
	str r0, [r1]
	b _022348F6
_022348CE:
	ldr r2, [r4]
	ldr r0, [r1]
	sub r0, r2, r0
	str r0, [r4]
	bpl _022348F6
	mov r0, #0
	str r0, [r4]
	b _022348F6
_022348DE:
	ldr r2, [r4]
	ldr r0, [r1]
	eor r0, r2
	str r0, [r4]
	b _022348F6
_022348E8:
	ldr r2, [r4]
	ldr r0, [r1]
	and r0, r2
	str r0, [r4]
	b _022348F6
_022348F2:
	bl GF_AssertFail
_022348F6:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_022348FC
ov11_022348FC: ; 0x022348FC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r7, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r5, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp, #4]
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp, #8]
	ldr r2, [sp, #4]
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_0223C230
	str r0, [sp]
	ldr r1, [sp]
	add r0, r4, #0
	add r2, r6, #0
	mov r3, #0
	bl ov11_02243420
	str r0, [sp, #0xc]
	ldr r2, [sp, #8]
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_0223A444
	add r1, r0, #0
	cmp r5, #0x14
	bhi _02234A22
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02234962: ; jump table
	.short _02234A22 - _02234962 - 2 ; case 0
	.short _02234A22 - _02234962 - 2 ; case 1
	.short _02234A22 - _02234962 - 2 ; case 2
	.short _02234A22 - _02234962 - 2 ; case 3
	.short _02234A22 - _02234962 - 2 ; case 4
	.short _02234A22 - _02234962 - 2 ; case 5
	.short _02234A22 - _02234962 - 2 ; case 6
	.short _0223498C - _02234962 - 2 ; case 7
	.short _02234992 - _02234962 - 2 ; case 8
	.short _0223499C - _02234962 - 2 ; case 9
	.short _022349A6 - _02234962 - 2 ; case 10
	.short _022349B0 - _02234962 - 2 ; case 11
	.short _022349C0 - _02234962 - 2 ; case 12
	.short _022349CA - _02234962 - 2 ; case 13
	.short _022349D6 - _02234962 - 2 ; case 14
	.short _022349E2 - _02234962 - 2 ; case 15
	.short _022349EE - _02234962 - 2 ; case 16
	.short _022349F8 - _02234962 - 2 ; case 17
	.short _022349FE - _02234962 - 2 ; case 18
	.short _02234A0E - _02234962 - 2 ; case 19
	.short _02234A18 - _02234962 - 2 ; case 20
_0223498C:
	ldr r0, [r1]
	str r0, [sp, #0xc]
	b _02234A26
_02234992:
	ldr r2, [sp, #0xc]
	ldr r0, [r1]
	add r0, r2, r0
	str r0, [sp, #0xc]
	b _02234A26
_0223499C:
	ldr r2, [sp, #0xc]
	ldr r0, [r1]
	sub r0, r2, r0
	str r0, [sp, #0xc]
	b _02234A26
_022349A6:
	ldr r2, [sp, #0xc]
	ldr r0, [r1]
	orr r0, r2
	str r0, [sp, #0xc]
	b _02234A26
_022349B0:
	ldr r2, [r1]
	mov r1, #0
	mvn r1, r1
	ldr r0, [sp, #0xc]
	eor r1, r2
	and r0, r1
	str r0, [sp, #0xc]
	b _02234A26
_022349C0:
	ldr r2, [sp, #0xc]
	ldr r0, [r1]
	mul r0, r2
	str r0, [sp, #0xc]
	b _02234A26
_022349CA:
	ldr r0, [sp, #0xc]
	ldr r1, [r1]
	bl _s32_div_f
	str r0, [sp, #0xc]
	b _02234A26
_022349D6:
	ldr r2, [sp, #0xc]
	ldr r0, [r1]
	add r1, r2, #0
	lsl r1, r0
	str r1, [sp, #0xc]
	b _02234A26
_022349E2:
	ldr r2, [sp, #0xc]
	ldr r0, [r1]
	add r1, r2, #0
	asr r1, r0
	str r1, [sp, #0xc]
	b _02234A26
_022349EE:
	ldr r0, [r1]
	bl MaskOfFlagNo
	str r0, [sp, #0xc]
	b _02234A26
_022349F8:
	ldr r0, [sp, #0xc]
	str r0, [r1]
	b _02234A26
_022349FE:
	ldr r2, [sp, #0xc]
	ldr r0, [r1]
	sub r0, r2, r0
	str r0, [sp, #0xc]
	bpl _02234A26
	mov r0, #0
	str r0, [sp, #0xc]
	b _02234A26
_02234A0E:
	ldr r2, [sp, #0xc]
	ldr r0, [r1]
	eor r0, r2
	str r0, [sp, #0xc]
	b _02234A26
_02234A18:
	ldr r2, [sp, #0xc]
	ldr r0, [r1]
	and r0, r2
	str r0, [sp, #0xc]
	b _02234A26
_02234A22:
	bl GF_AssertFail
_02234A26:
	cmp r5, #0x11
	beq _02234A56
	cmp r6, #0x1a
	bne _02234A40
	ldr r1, [sp]
	ldr r2, [sp, #0xc]
	lsl r1, r1, #0x18
	lsl r2, r2, #0x18
	add r0, r4, #0
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl ov11_0223D1C4
_02234A40:
	ldr r1, [sp]
	add r0, r4, #0
	add r2, r6, #0
	add r3, sp, #0xc
	bl ov11_0224379C
	ldr r2, [sp]
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_02245190
_02234A56:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_02234A5C
ov11_02234A5C: ; 0x02234A5C
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r1, r0, #0
	add r0, r4, #0
	bl ov11_0223A424
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_02234A7C
ov11_02234A7C: ; 0x02234A7C
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A43C
	mov r0, #0
	pop {r4, pc}

	thumb_func_start ov11_02234A9C
ov11_02234A9C: ; 0x02234A9C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223A444
	add r2, r0, #0
	ldr r2, [r2]
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A43C
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02234ACC
ov11_02234ACC: ; 0x02234ACC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	str r0, [sp, #8]
	mov r4, #0
	bl ov11_0222FF74
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r1, [r5, #0x64]
	lsl r0, r1, #1
	add r2, r5, r0
	ldr r0, _02234BCC ; =0x00003084
	ldrh r2, [r2, r0]
	cmp r2, #0
	beq _02234AF6
	add r4, r2, #0
	b _02234B40
_02234AF6:
	mov r2, #2
	tst r2, r6
	beq _02234B40
	lsl r1, r1, #3
	add r3, r5, r1
	add r1, r0, #0
	add r1, #0xe
	add r4, r0, #0
	ldrh r2, [r3, r1]
	add r1, r0, #0
	add r4, #8
	add r0, #0xa
	add r1, #0xc
	ldrh r4, [r3, r4]
	ldrh r0, [r3, r0]
	ldrh r1, [r3, r1]
	add r0, r4, r0
	add r0, r1, r0
	add r4, r2, r0
	beq _02234B40
	ldr r6, _02234BD0 ; =0x0000308C
	mov r7, #0x1e
_02234B22:
	bl LCRandom
	lsr r2, r0, #0x1f
	lsl r0, r0, #0x1e
	ldr r1, [r5, #0x64]
	sub r0, r0, r2
	ror r0, r7
	add r0, r2, r0
	lsl r1, r1, #3
	lsl r2, r0, #1
	add r0, r5, r1
	add r0, r2, r0
	ldrh r4, [r0, r6]
	cmp r4, #0
	beq _02234B22
_02234B40:
	cmp r4, #0
	beq _02234BAA
	lsl r1, r4, #0x10
	add r0, r5, #0
	lsr r1, r1, #0x10
	bl ov11_0224C0B4
	cmp r0, #1
	bne _02234BAA
	ldr r1, _02234BD4 ; =0x0000213C
	lsl r3, r4, #0x10
	ldr r2, [r5, r1]
	mov r0, #1
	bic r2, r0
	str r2, [r5, r1]
	ldr r2, [r5, r1]
	ldr r0, _02234BD8 ; =0xFFFFBFFF
	lsr r3, r3, #0x10
	and r0, r2
	str r0, [r5, r1]
	ldr r0, _02234BDC ; =0x00003044
	add r1, r5, #0
	str r4, [r5, r0]
	mov r0, #1
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	ldr r2, [r5, #0x64]
	bl ov11_02244C28
	str r0, [r5, #0x6c]
	cmp r0, #0xff
	bne _02234B94
	mov r2, #0x26
	str r2, [r5, #0xc]
	add r0, r5, #0
	mov r1, #1
	add r2, #0xf3
	bl ov11_0223A434
	b _02234BC4
_02234B94:
	ldr r1, [r5, #0x64]
	lsl r1, r1, #4
	add r2, r5, r1
	ldr r1, _02234BE0 ; =0x000021AC
	str r0, [r2, r1]
	add r0, r5, #0
	mov r1, #0
	add r2, r4, #0
	bl ov11_0223A434
	b _02234BC4
_02234BAA:
	ldr r2, [r5, #0x64]
	mov r0, #0xb5
	lsl r0, r0, #2
	mov r1, #0x1c
	add r3, r2, #0
	mul r3, r1
	add r0, r5, r0
	ldr r2, [r0, r3]
	mov r1, #1
	bic r2, r1
	mov r1, #1
	orr r1, r2
	str r1, [r0, r3]
_02234BC4:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02234BCC: .word 0x00003084
_02234BD0: .word 0x0000308C
_02234BD4: .word 0x0000213C
_02234BD8: .word 0xFFFFBFFF
_02234BDC: .word 0x00003044
_02234BE0: .word 0x000021AC

	thumb_func_start ov11_02234BE4
ov11_02234BE4: ; 0x02234BE4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0222FF84
	mov r2, #0
	cmp r0, #0
	ble _02234C24
	ldr r6, _02234C28 ; =0x00002D58
	mov r1, #6
	add r5, r6, #0
	add r5, #0x58
_02234C06:
	mov r7, #0
_02234C08:
	add r3, r4, r7
	add r7, r7, #1
	strb r1, [r3, r6]
	cmp r7, #8
	blt _02234C08
	ldr r3, _02234C2C ; =0x00002DB0
	add r2, r2, #1
	ldr r7, [r4, r3]
	ldr r3, _02234C30 ; =0xFFEFFFFF
	and r3, r7
	str r3, [r4, r5]
	add r4, #0xc0
	cmp r2, r0
	blt _02234C06
_02234C24:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02234C28: .word 0x00002D58
_02234C2C: .word 0x00002DB0
_02234C30: .word 0xFFEFFFFF

	thumb_func_start ov11_02234C34
ov11_02234C34: ; 0x02234C34
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_022451C0
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_02234C60
ov11_02234C60: ; 0x02234C60
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_022451F0
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_02234C8C
ov11_02234C8C: ; 0x02234C8C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r5, #0
	add r2, r7, #0
	bl ov11_02255E0C
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_02234CC4
ov11_02234CC4: ; 0x02234CC4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r5, #0
	add r2, r7, #0
	bl ov11_02255E2C
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_02234CFC
ov11_02234CFC: ; 0x02234CFC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	add r7, r0, #0
	add r5, r1, #0
	str r2, [sp]
	mov r0, #5
	mov r1, #0x60
	bl AllocFromHeap
	add r4, r0, #0
	ldr r0, [sp]
	add r6, r7, #0
	lsl r0, r0, #1
	add r6, #0xa0
	str r0, [sp, #4]
	ldrh r0, [r6, r0]
	add r1, sp, #8
	bl TrainerData_ReadTrData
	ldr r0, [sp, #4]
	add r1, r4, #0
	ldrh r0, [r6, r0]
	bl TrainerData_ReadTrPoke
	add r0, sp, #8
	ldrb r1, [r0]
	cmp r1, #3
	bhi _02234D48
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02234D40: ; jump table
	.short _02234D48 - _02234D40 - 2 ; case 0
	.short _02234D5C - _02234D40 - 2 ; case 1
	.short _02234D6E - _02234D40 - 2 ; case 2
	.short _02234D7E - _02234D40 - 2 ; case 3
_02234D48:
	add r0, sp, #8
	ldrb r0, [r0, #3]
	sub r1, r0, #1
	mov r0, #6
	mul r0, r1
	add r0, r4, r0
	ldrh r0, [r0, #2]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	b _02234D8C
_02234D5C:
	ldrb r0, [r0, #3]
	sub r1, r0, #1
	mov r0, #0xe
	mul r0, r1
	add r0, r4, r0
	ldrh r0, [r0, #2]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	b _02234D8C
_02234D6E:
	ldrb r0, [r0, #3]
	sub r0, r0, #1
	lsl r0, r0, #3
	add r0, r4, r0
	ldrh r0, [r0, #2]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	b _02234D8C
_02234D7E:
	ldrb r0, [r0, #3]
	sub r0, r0, #1
	lsl r0, r0, #4
	add r0, r4, r0
	ldrh r0, [r0, #2]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
_02234D8C:
	ldr r2, [r7, #0x2c]
	mov r0, #0x10
	tst r0, r2
	bne _02234D98
	cmp r2, #0x4b
	bne _02234DAE
_02234D98:
	add r0, sp, #8
	ldrb r2, [r0, #1]
	ldr r0, _02234DEC ; =ov11_0225FF20
	lsl r1, r1, #2
	ldrb r0, [r0, r2]
	ldr r2, _02234DF0 ; =0x00002168
	ldr r2, [r5, r2]
	add r5, r0, #0
	mul r1, r2
	mul r5, r1
	b _02234DDE
_02234DAE:
	mov r0, #2
	tst r0, r2
	add r0, sp, #8
	beq _02234DCC
	ldrb r2, [r0, #1]
	ldr r0, _02234DEC ; =ov11_0225FF20
	lsl r1, r1, #2
	ldrb r0, [r0, r2]
	ldr r2, _02234DF0 ; =0x00002168
	ldr r2, [r5, r2]
	add r5, r0, #0
	mul r1, r2
	lsl r1, r1, #1
	mul r5, r1
	b _02234DDE
_02234DCC:
	ldrb r2, [r0, #1]
	ldr r0, _02234DEC ; =ov11_0225FF20
	lsl r1, r1, #2
	ldrb r0, [r0, r2]
	ldr r2, _02234DF0 ; =0x00002168
	ldr r2, [r5, r2]
	add r5, r0, #0
	mul r1, r2
	mul r5, r1
_02234DDE:
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	nop
_02234DEC: .word ov11_0225FF20
_02234DF0: .word 0x00002168

	thumb_func_start ov11_02234DF4
ov11_02234DF4: ; 0x02234DF4
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r0, _02234E70 ; =0x0000241C
	ldrb r0, [r5, r0]
	cmp r0, #1
	bne _02234E3E
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #1
	bl ov11_02234CFC
	add r4, r0, #0
	ldr r1, [r5, #0x2c]
	mov r0, #0x10
	tst r0, r1
	bne _02234E22
	cmp r1, #0x4b
	bne _02234E2E
_02234E22:
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #3
	bl ov11_02234CFC
	add r4, r4, r0
_02234E2E:
	add r0, r5, #0
	mov r1, #0
	bl ov11_022301D4
	add r1, r4, #0
	bl PlayerProfile_AddMoney
	b _02234E56
_02234E3E:
	ldr r0, [r5, #0x68]
	ldr r1, [r5, #0x48]
	bl ov11_0223158C
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #0
	bl ov11_022301D4
	add r1, r4, #0
	bl PlayerProfile_SubMoney
_02234E56:
	cmp r4, #0
	beq _02234E62
	mov r0, #0x13
	lsl r0, r0, #4
	str r4, [r6, r0]
	b _02234E6A
_02234E62:
	mov r0, #0x13
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r6, r0]
_02234E6A:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_02234E70: .word 0x0000241C

	thumb_func_start ov11_02234E74
ov11_02234E74: ; 0x02234E74
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r6, #0
	bl ov11_02230E20
	cmp r0, #1
	beq _02234EAC
	cmp r4, #0xf
	beq _02234EAC
	cmp r4, #0x10
	beq _02234EAC
	add r0, r4, #0
	sub r0, #0x19
	cmp r0, #1
	bhi _02234ED2
_02234EAC:
	add r0, r6, #0
	add r1, r5, #0
	add r2, r7, #0
	bl ov11_0223C230
	add r7, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	bl ov11_0224C20C
	cmp r0, #1
	bne _02234ED2
	add r0, r6, #0
	add r1, r5, #0
	add r2, r7, #0
	add r3, r4, #0
	bl ov11_02255E4C
_02234ED2:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_02234ED8
ov11_02234ED8: ; 0x02234ED8
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	str r0, [sp, #4]
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r6, #0
	bl ov11_02230E20
	cmp r0, #1
	beq _02234F1A
	cmp r4, #0xf
	beq _02234F1A
	cmp r4, #0x10
	beq _02234F1A
	add r0, r4, #0
	sub r0, #0x19
	cmp r0, #1
	bhi _02234F5C
_02234F1A:
	add r0, r6, #0
	add r1, r5, #0
	add r2, r7, #0
	bl ov11_0223C230
	add r7, r0, #0
	ldr r2, [sp, #4]
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_0223C230
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	bl ov11_0224C20C
	cmp r0, #1
	bne _02234F5C
	ldr r1, [sp, #8]
	add r0, r5, #0
	add r2, r4, #0
	bl ov11_0224C20C
	cmp r0, #1
	bne _02234F5C
	ldr r3, [sp, #8]
	add r0, r6, #0
	add r1, r5, #0
	add r2, r7, #0
	str r4, [sp]
	bl ov11_02255E7C
_02234F5C:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_02234F64
ov11_02234F64: ; 0x02234F64
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r7, #0
	add r1, r5, #0
	add r2, r4, #0
	bl ov11_0223C230
	str r0, [sp]
	add r0, r7, #0
	add r1, r5, #0
	add r2, r6, #0
	bl ov11_0223A444
	add r4, r0, #0
	add r0, r7, #0
	bl ov11_02230E20
	cmp r0, #1
	beq _02234FB4
	cmp r6, #0xf
	beq _02234FB4
	cmp r6, #0x10
	beq _02234FB4
	ldr r0, [r4]
	sub r0, #0x19
	cmp r0, #1
	bhi _02234FCE
_02234FB4:
	ldr r1, [sp]
	ldr r2, [r4]
	add r0, r5, #0
	bl ov11_0224C20C
	cmp r0, #1
	bne _02234FCE
	ldr r2, [sp]
	ldr r3, [r4]
	add r0, r7, #0
	add r1, r5, #0
	bl ov11_02255E4C
_02234FCE:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_02234FD4
ov11_02234FD4: ; 0x02234FD4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r2, r0, #0
	add r1, r4, #0
	ldr r3, _02235008 ; =0x0000219C
	add r4, r4, r2
	ldrb r3, [r4, r3]
	add r0, r5, #0
	bl ov11_02255EAC
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02235008: .word 0x0000219C

	thumb_func_start ov11_0223500C
ov11_0223500C: ; 0x0223500C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r2, r0, #0
	add r1, r4, #0
	ldr r3, _02235040 ; =0x0000219C
	add r4, r4, r2
	ldrb r3, [r4, r3]
	add r0, r5, #0
	bl ov11_02255EF0
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02235040: .word 0x0000219C

	thumb_func_start ov11_02235044
ov11_02235044: ; 0x02235044
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02255F3C
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_02235070
ov11_02235070: ; 0x02235070
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02255F54
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_0223509C
ov11_0223509C: ; 0x0223509C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	mov r2, #0x13
	lsl r2, r2, #4
	add r1, r0, #0
	ldr r2, [r4, r2]
	add r0, r5, #0
	bl ov11_02255E2C
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_022350CC
ov11_022350CC: ; 0x022350CC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp]
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x79
	bne _022350FC
	ldr r1, [sp]
	add r0, r4, #0
	bl ov11_0223A424
	add sp, #8
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_022350FC:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r4, r0
	ldr r0, _02235238 ; =0x00002D4C
	mov r6, #0
_02235108:
	ldrh r1, [r2, r0]
	cmp r1, #0
	beq _02235116
	add r6, r6, #1
	add r2, r2, #2
	cmp r6, #4
	blt _02235108
_02235116:
	mov r0, #0
	str r0, [sp, #4]
	cmp r6, #0
	ble _0223518E
	add r7, r0, #0
_02235120:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r0, r4, r0
	add r2, r7, r0
	ldr r0, _02235238 ; =0x00002D4C
	ldrh r0, [r2, r0]
	cmp r0, #0xa0
	beq _02235182
	lsl r0, r0, #4
	add r2, r4, r0
	ldr r0, _0223523C ; =0x000003E2
	ldrb r5, [r2, r0]
	cmp r5, #9
	bne _02235162
	add r0, r4, #0
	mov r2, #0x1b
	mov r3, #0
	bl ov11_02243420
	cmp r0, #7
	beq _0223515C
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	mov r2, #0x1c
	mov r3, #0
	bl ov11_02243420
	cmp r0, #7
	bne _02235160
_0223515C:
	mov r5, #7
	b _02235162
_02235160:
	mov r5, #0
_02235162:
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	mov r2, #0x1b
	mov r3, #0
	bl ov11_02243420
	cmp r5, r0
	beq _02235182
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	mov r2, #0x1c
	mov r3, #0
	bl ov11_02243420
	cmp r5, r0
	bne _0223518E
_02235182:
	ldr r0, [sp, #4]
	add r7, r7, #2
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, r6
	blt _02235120
_0223518E:
	ldr r0, [sp, #4]
	cmp r0, r6
	bne _0223519E
	ldr r1, [sp]
	add r0, r4, #0
	bl ov11_0223A424
	b _02235230
_0223519E:
	ldr r7, _02235238 ; =0x00002D4C
_022351A0:
	bl LCRandom
	add r1, r6, #0
	bl _s32_div_f
	ldr r2, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r2
	lsl r1, r1, #1
	add r0, r4, r0
	add r0, r1, r0
	ldrh r0, [r0, r7]
	cmp r0, #0xa0
	beq _022351A0
	lsl r0, r0, #4
	add r1, r4, r0
	ldr r0, _0223523C ; =0x000003E2
	ldrb r5, [r1, r0]
	cmp r5, #9
	bne _022351EE
	add r1, r2, #0
	add r0, r4, #0
	mov r2, #0x1b
	mov r3, #0
	bl ov11_02243420
	cmp r0, #7
	beq _022351E8
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	mov r2, #0x1c
	mov r3, #0
	bl ov11_02243420
	cmp r0, #7
	bne _022351EC
_022351E8:
	mov r5, #7
	b _022351EE
_022351EC:
	mov r5, #0
_022351EE:
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	mov r2, #0x1b
	mov r3, #0
	bl ov11_02243420
	cmp r5, r0
	beq _022351A0
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	mov r2, #0x1c
	mov r3, #0
	bl ov11_02243420
	cmp r5, r0
	beq _022351A0
	ldr r1, [r4, #0x64]
	lsl r0, r5, #0x18
	add r3, r1, #0
	mov r2, #0xc0
	mul r3, r2
	ldr r1, _02235240 ; =0x00002D64
	lsr r0, r0, #0x18
	add r3, r4, r3
	strb r0, [r3, r1]
	ldr r3, [r4, #0x64]
	add r1, r1, #1
	add r6, r3, #0
	mul r6, r2
	add r3, r4, r6
	strb r0, [r3, r1]
	add r2, #0x70
	str r5, [r4, r2]
_02235230:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02235238: .word 0x00002D4C
_0223523C: .word 0x000003E2
_02235240: .word 0x00002D64

	thumb_func_start ov11_02235244
ov11_02235244: ; 0x02235244
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	str r0, [sp]
	add r0, r6, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r6, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r6, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r6, #0
	bl ov11_0223A404
	str r0, [sp, #4]
	add r0, r6, #0
	bl ov11_0223A404
	add r5, r0, #0
	ldr r0, [sp]
	add r1, r6, #0
	add r2, r4, #0
	bl ov11_0223A444
	add r4, r0, #0
	ldr r0, [sp]
	ldr r2, [sp, #4]
	add r1, r6, #0
	bl ov11_0223A444
	cmp r7, #6
	bhi _022352FC
	add r1, r7, r7
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223529A: ; jump table
	.short _022352A8 - _0223529A - 2 ; case 0
	.short _022352B4 - _0223529A - 2 ; case 1
	.short _022352C0 - _0223529A - 2 ; case 2
	.short _022352CC - _0223529A - 2 ; case 3
	.short _022352D8 - _0223529A - 2 ; case 4
	.short _022352E4 - _0223529A - 2 ; case 5
	.short _022352F0 - _0223529A - 2 ; case 6
_022352A8:
	ldr r1, [r4]
	ldr r0, [r0]
	cmp r1, r0
	beq _022352FC
	mov r5, #0
	b _022352FC
_022352B4:
	ldr r1, [r4]
	ldr r0, [r0]
	cmp r1, r0
	bne _022352FC
	mov r5, #0
	b _022352FC
_022352C0:
	ldr r1, [r4]
	ldr r0, [r0]
	cmp r1, r0
	bhi _022352FC
	mov r5, #0
	b _022352FC
_022352CC:
	ldr r1, [r4]
	ldr r0, [r0]
	cmp r1, r0
	bls _022352FC
	mov r5, #0
	b _022352FC
_022352D8:
	ldr r1, [r4]
	ldr r0, [r0]
	tst r0, r1
	bne _022352FC
	mov r5, #0
	b _022352FC
_022352E4:
	ldr r1, [r4]
	ldr r0, [r0]
	tst r0, r1
	beq _022352FC
	mov r5, #0
	b _022352FC
_022352F0:
	ldr r1, [r0]
	ldr r0, [r4]
	and r0, r1
	cmp r1, r0
	beq _022352FC
	mov r5, #0
_022352FC:
	cmp r5, #0
	beq _02235308
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_0223A424
_02235308:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_02235310
ov11_02235310: ; 0x02235310
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r1, #0
	str r0, [sp]
	add r0, r6, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r6, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r6, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r6, #0
	bl ov11_0223A404
	str r0, [sp, #4]
	add r0, r6, #0
	bl ov11_0223A404
	str r0, [sp, #8]
	add r0, r6, #0
	bl ov11_0223A404
	add r5, r0, #0
	ldr r0, [sp]
	add r1, r6, #0
	add r2, r4, #0
	bl ov11_0223C230
	add r1, r0, #0
	ldr r2, [sp, #4]
	add r0, r6, #0
	mov r3, #0
	bl ov11_02243420
	add r4, r0, #0
	ldr r0, [sp]
	ldr r2, [sp, #8]
	add r1, r6, #0
	bl ov11_0223A444
	cmp r7, #6
	bhi _022353D0
	add r1, r7, r7
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223537A: ; jump table
	.short _02235388 - _0223537A - 2 ; case 0
	.short _02235392 - _0223537A - 2 ; case 1
	.short _0223539C - _0223537A - 2 ; case 2
	.short _022353A6 - _0223537A - 2 ; case 3
	.short _022353B0 - _0223537A - 2 ; case 4
	.short _022353BA - _0223537A - 2 ; case 5
	.short _022353C4 - _0223537A - 2 ; case 6
_02235388:
	ldr r0, [r0]
	cmp r4, r0
	beq _022353D0
	mov r5, #0
	b _022353D0
_02235392:
	ldr r0, [r0]
	cmp r4, r0
	bne _022353D0
	mov r5, #0
	b _022353D0
_0223539C:
	ldr r0, [r0]
	cmp r4, r0
	bhi _022353D0
	mov r5, #0
	b _022353D0
_022353A6:
	ldr r0, [r0]
	cmp r4, r0
	bls _022353D0
	mov r5, #0
	b _022353D0
_022353B0:
	ldr r0, [r0]
	tst r0, r4
	bne _022353D0
	mov r5, #0
	b _022353D0
_022353BA:
	ldr r0, [r0]
	tst r0, r4
	beq _022353D0
	mov r5, #0
	b _022353D0
_022353C4:
	ldr r1, [r0]
	add r0, r1, #0
	and r0, r4
	cmp r1, r0
	beq _022353D0
	mov r5, #0
_022353D0:
	cmp r5, #0
	beq _022353DC
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_0223A424
_022353DC:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_022353E4
ov11_022353E4: ; 0x022353E4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r1, _0223542C ; =0x00002168
	ldr r2, [r4, r0]
	ldr r1, [r4, r1]
	add r3, r2, #0
	mul r3, r1
	add r1, r0, #0
	sub r1, #0x1c
	str r3, [r4, r1]
	add r1, r0, #0
	sub r1, #0x1c
	ldr r2, [r4, r1]
	ldr r1, _02235430 ; =0x0000FFFF
	cmp r2, r1
	ble _02235416
	sub r0, #0x1c
	str r1, [r4, r0]
_02235416:
	add r0, r5, #0
	mov r1, #0
	bl ov11_022301D4
	mov r1, #0x13
	lsl r1, r1, #4
	ldr r1, [r4, r1]
	bl PlayerProfile_AddMoney
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223542C: .word 0x00002168
_02235430: .word 0x0000FFFF

	thumb_func_start ov11_02235434
ov11_02235434: ; 0x02235434
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	str r0, [sp]
	ldr r1, [r5, #0x64]
	add r0, r7, #0
	bl ov11_02230270
	add r6, r0, #0
	mov r0, #0x6f
	lsl r0, r0, #2
	add r3, r5, r0
	lsl r2, r6, #2
	ldr r1, [r3, r2]
	mov r4, #2
	tst r4, r1
	beq _02235478
	ldr r1, [sp]
	add r0, r5, #0
	bl ov11_0223A424
	ldr r1, _02235508 ; =0x0000216C
	mov r0, #0x40
	ldr r2, [r5, r1]
	orr r0, r2
	str r0, [r5, r1]
	b _02235504
_02235478:
	mov r4, #2
	orr r1, r4
	str r1, [r3, r2]
	add r1, r0, #0
	add r1, #8
	add r4, r5, r1
	lsl r6, r6, #3
	ldr r2, [r4, r6]
	ldr r1, _0223550C ; =0xFFFFFC7F
	add r0, #0xc4
	and r1, r2
	orr r0, r1
	str r0, [r4, r6]
	ldr r0, [r4, r6]
	mov r1, #0x60
	bic r0, r1
	ldr r1, [r5, #0x64]
	lsl r1, r1, #0x1e
	lsr r1, r1, #0x19
	orr r0, r1
	str r0, [r4, r6]
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl ov11_02249D90
	cmp r0, #0x60
	bne _022354CC
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	mov r2, #0
	bl ov11_02249DA4
	ldr r1, [r4, r6]
	ldr r2, _0223550C ; =0xFFFFFC7F
	and r2, r1
	lsl r1, r1, #0x16
	lsr r1, r1, #0x1d
	add r0, r1, r0
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x16
	orr r0, r2
	str r0, [r4, r6]
_022354CC:
	add r0, r5, #0
	mov r1, #0x14
	add r0, #0xf5
	strb r1, [r0]
	ldr r0, _02235510 ; =0x00003044
	mov r2, #1
	ldr r1, [r5, r0]
	add r0, r5, #0
	add r0, #0xf8
	str r1, [r0]
	add r0, r5, #0
	ldr r1, [r5, #0x64]
	add r0, #0xfc
	str r1, [r0]
	ldr r3, [r5, #0x64]
	add r0, r7, #0
	add r1, r5, #0
	bl ov11_022467AC
	cmp r0, #2
	bne _022354FE
	mov r0, #0xc0
	add r5, #0xf6
	strh r0, [r5]
	b _02235504
_022354FE:
	mov r0, #0xbe
	add r5, #0xf6
	strh r0, [r5]
_02235504:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02235508: .word 0x0000216C
_0223550C: .word 0xFFFFFC7F
_02235510: .word 0x00003044

	thumb_func_start ov11_02235514
ov11_02235514: ; 0x02235514
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	str r0, [sp]
	ldr r1, [r5, #0x64]
	add r0, r7, #0
	bl ov11_02230270
	add r6, r0, #0
	mov r0, #0x6f
	lsl r0, r0, #2
	add r3, r5, r0
	lsl r2, r6, #2
	ldr r1, [r3, r2]
	mov r4, #1
	tst r4, r1
	beq _02235558
	ldr r1, [sp]
	add r0, r5, #0
	bl ov11_0223A424
	ldr r1, _022355EC ; =0x0000216C
	mov r0, #0x40
	ldr r2, [r5, r1]
	orr r0, r2
	str r0, [r5, r1]
	b _022355E6
_02235558:
	mov r4, #1
	orr r1, r4
	add r0, #8
	add r4, r5, r0
	lsl r6, r6, #3
	str r1, [r3, r2]
	ldr r1, [r4, r6]
	mov r0, #0x1c
	bic r1, r0
	mov r0, #0x14
	orr r0, r1
	str r0, [r4, r6]
	ldr r0, [r4, r6]
	mov r1, #3
	bic r0, r1
	ldr r2, [r5, #0x64]
	mov r1, #3
	and r1, r2
	orr r0, r1
	str r0, [r4, r6]
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl ov11_02249D90
	cmp r0, #0x60
	bne _022355AE
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	mov r2, #0
	bl ov11_02249DA4
	ldr r1, [r4, r6]
	add r3, r0, #0
	mov r0, #0x1c
	add r2, r1, #0
	bic r2, r0
	lsl r0, r1, #0x1b
	lsr r0, r0, #0x1d
	add r0, r0, r3
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1b
	orr r0, r2
	str r0, [r4, r6]
_022355AE:
	add r0, r5, #0
	mov r1, #0x14
	add r0, #0xf5
	strb r1, [r0]
	ldr r0, _022355F0 ; =0x00003044
	mov r2, #1
	ldr r1, [r5, r0]
	add r0, r5, #0
	add r0, #0xf8
	str r1, [r0]
	add r0, r5, #0
	ldr r1, [r5, #0x64]
	add r0, #0xfc
	str r1, [r0]
	ldr r3, [r5, #0x64]
	add r0, r7, #0
	add r1, r5, #0
	bl ov11_022467AC
	cmp r0, #2
	bne _022355E0
	mov r0, #0xc4
	add r5, #0xf6
	strh r0, [r5]
	b _022355E6
_022355E0:
	mov r0, #0xc2
	add r5, #0xf6
	strh r0, [r5]
_022355E6:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022355EC: .word 0x0000216C
_022355F0: .word 0x00003044

	thumb_func_start ov11_022355F4
ov11_022355F4: ; 0x022355F4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	ldr r1, [r4, #0x64]
	add r0, r5, #0
	bl ov11_02230270
	mov r5, #0x6f
	add r2, r0, #0
	lsl r5, r5, #2
	add r1, r4, r5
	lsl r0, r2, #2
	ldr r6, [r1, r0]
	mov r3, #0x40
	tst r3, r6
	beq _02235638
	add r0, r4, #0
	add r1, r7, #0
	bl ov11_0223A424
	ldr r1, _02235668 ; =0x0000216C
	mov r0, #0x40
	ldr r2, [r4, r1]
	orr r0, r2
	str r0, [r4, r1]
	b _02235662
_02235638:
	mov r3, #0x40
	orr r3, r6
	str r3, [r1, r0]
	add r5, #8
	lsl r0, r2, #3
	add r1, r4, r5
	ldr r3, [r1, r0]
	ldr r2, _0223566C ; =0xFFFF8FFF
	and r3, r2
	mov r2, #5
	lsl r2, r2, #0xc
	orr r2, r3
	str r2, [r1, r0]
	ldr r3, [r1, r0]
	ldr r2, _02235670 ; =0xFFFFF3FF
	and r3, r2
	ldr r2, [r4, #0x64]
	lsl r2, r2, #0x1e
	lsr r2, r2, #0x14
	orr r2, r3
	str r2, [r1, r0]
_02235662:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02235668: .word 0x0000216C
_0223566C: .word 0xFFFF8FFF
_02235670: .word 0xFFFFF3FF

	thumb_func_start ov11_02235674
ov11_02235674: ; 0x02235674
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r1, _02235844 ; =0x0000213C
	mov r0, #1
	ldr r2, [r4, r1]
	lsl r0, r0, #0xa
	orr r0, r2
	str r0, [r4, r1]
	ldr r1, [r4, #0x64]
	ldr r2, [r4, #0x6c]
	add r0, r4, #0
	mov r3, #5
	bl ov11_02246D84
	cmp r0, #1
	bne _022356AA
	ldr r1, _02235848 ; =0x0000216C
	mov r0, #2
	ldr r2, [r4, r1]
	lsl r0, r0, #0x12
	orr r0, r2
	str r0, [r4, r1]
	b _0223583E
_022356AA:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	mov r0, #0xb7
	lsl r0, r0, #6
	ldr r1, [r1, r0]
	mov r0, #0x18
	tst r0, r1
	bne _02235730
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x63
	beq _02235730
	ldr r1, [r4, #0x6c]
	add r0, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x63
	beq _02235730
	ldr r0, _0223584C ; =0x00003044
	mov r2, #0xc0
	ldr r0, [r4, r0]
	ldr r5, [r4, #0x6c]
	lsl r0, r0, #4
	add r1, r4, r0
	ldr r0, _02235850 ; =0x000003E3
	ldrb r1, [r1, r0]
	ldr r0, [r4, #0x64]
	add r3, r0, #0
	mul r3, r2
	add r0, r4, r3
	ldr r3, _02235854 ; =0x00002D74
	mul r2, r5
	add r2, r4, r2
	ldrb r0, [r0, r3]
	ldrb r2, [r2, r3]
	sub r0, r0, r2
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	bl LCRandom
	mov r1, #0x64
	bl _s32_div_f
	cmp r1, r5
	bge _0223572C
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	add r2, r1, #0
	mul r2, r0
	ldr r1, _02235854 ; =0x00002D74
	add r2, r4, r2
	ldrb r3, [r2, r1]
	ldr r2, [r4, #0x6c]
	mul r0, r2
	add r0, r4, r0
	ldrb r0, [r0, r1]
	cmp r3, r0
	blo _0223572C
	mov r3, #1
	b _022357E8
_0223572C:
	mov r3, #0
	b _022357E8
_02235730:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r3, r4, r0
	ldr r0, _02235858 ; =0x00002DCC
	ldr r1, [r4, #0x64]
	ldr r2, [r3, r0]
	lsl r2, r2, #0x1e
	lsr r2, r2, #0x1e
	cmp r1, r2
	bne _02235750
	sub r0, #0xc
	ldr r2, [r3, r0]
	mov r0, #0x18
	tst r0, r2
	bne _02235766
_02235750:
	add r0, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x63
	beq _02235766
	ldr r1, [r4, #0x6c]
	add r0, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x63
	bne _02235784
_02235766:
	ldr r0, [r4, #0x64]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	ldr r3, [r4, #0x6c]
	add r0, r4, r2
	ldr r2, _02235854 ; =0x00002D74
	mul r1, r3
	add r1, r4, r1
	ldrb r0, [r0, r2]
	ldrb r1, [r1, r2]
	cmp r0, r1
	blo _02235784
	mov r3, #1
	b _022357DC
_02235784:
	ldr r0, _0223584C ; =0x00003044
	mov r2, #0xc0
	ldr r0, [r4, r0]
	ldr r5, [r4, #0x6c]
	lsl r0, r0, #4
	add r1, r4, r0
	ldr r0, _02235850 ; =0x000003E3
	ldrb r1, [r1, r0]
	ldr r0, [r4, #0x64]
	add r3, r0, #0
	mul r3, r2
	add r0, r4, r3
	ldr r3, _02235854 ; =0x00002D74
	mul r2, r5
	add r2, r4, r2
	ldrb r0, [r0, r3]
	ldrb r2, [r2, r3]
	sub r0, r0, r2
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	bl LCRandom
	mov r1, #0x64
	bl _s32_div_f
	cmp r1, r5
	bge _022357DA
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	add r2, r1, #0
	mul r2, r0
	ldr r1, _02235854 ; =0x00002D74
	add r2, r4, r2
	ldrb r3, [r2, r1]
	ldr r2, [r4, #0x6c]
	mul r0, r2
	add r0, r4, r0
	ldrb r0, [r0, r1]
	cmp r3, r0
	blo _022357DA
	mov r3, #1
	b _022357DC
_022357DA:
	mov r3, #0
_022357DC:
	ldr r1, _02235848 ; =0x0000216C
	mov r0, #1
	ldr r2, [r4, r1]
	lsl r0, r0, #0xa
	orr r0, r2
	str r0, [r4, r1]
_022357E8:
	cmp r3, #0
	beq _0223580E
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0223585C ; =0x00002D8C
	ldr r0, [r1, r0]
	ldr r1, _02235860 ; =0x00002144
	neg r0, r0
	str r0, [r4, r1]
	add r0, r1, #0
	add r0, #0x28
	ldr r2, [r4, r0]
	mov r0, #0x20
	orr r0, r2
	add r1, #0x28
	str r0, [r4, r1]
	b _0223583E
_0223580E:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	add r2, r1, #0
	mul r2, r0
	ldr r1, _02235854 ; =0x00002D74
	add r2, r4, r2
	ldrb r3, [r2, r1]
	ldr r2, [r4, #0x6c]
	mul r0, r2
	add r0, r4, r0
	ldrb r0, [r0, r1]
	cmp r3, r0
	ldr r1, _02235848 ; =0x0000216C
	blo _02235834
	ldr r2, [r4, r1]
	mov r0, #1
	orr r0, r2
	str r0, [r4, r1]
	b _0223583E
_02235834:
	mov r0, #1
	ldr r2, [r4, r1]
	lsl r0, r0, #0xc
	orr r0, r2
	str r0, [r4, r1]
_0223583E:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02235844: .word 0x0000213C
_02235848: .word 0x0000216C
_0223584C: .word 0x00003044
_02235850: .word 0x000003E3
_02235854: .word 0x00002D74
_02235858: .word 0x00002DCC
_0223585C: .word 0x00002D8C
_02235860: .word 0x00002144

	thumb_func_start ov11_02235864
ov11_02235864: ; 0x02235864
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0223A444
	add r4, r0, #0
	ldr r0, [r4]
	add r1, r7, #0
	bl ov11_022476C0
	str r0, [r4]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_0223589C
ov11_0223589C: ; 0x0223589C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl ov11_0223A444
	add r4, r0, #0
	add r0, r6, #0
	add r1, r5, #0
	add r2, r7, #0
	bl ov11_0223A444
	add r1, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	bge _022358DE
	mov r5, #0
	mvn r5, r5
	b _022358E0
_022358DE:
	mov r5, #1
_022358E0:
	ldr r0, [r4]
	ldr r1, [r1]
	bl _s32_div_f
	str r0, [r4]
	cmp r0, #0
	bne _022358F0
	str r5, [r4]
_022358F0:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_022358F4
ov11_022358F4: ; 0x022358F4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r0, r6, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r6, #0
	bl ov11_0223A404
	str r0, [sp]
	ldr r0, [r6, #0x6c]
	lsl r0, r0, #1
	add r1, r6, r0
	ldr r0, _02235A18 ; =0x0000307C
	ldrh r0, [r1, r0]
	bl ov11_0224C044
	cmp r0, #0
	beq _0223594E
	ldr r0, [r6, #0x64]
	mov r2, #2
	mov r3, #0xc0
	add r1, r0, #0
	mul r1, r3
	add r0, r6, r1
	ldr r1, _02235A1C ; =0x00002DB0
	mov ip, r0
	ldr r0, [r0, r1]
	lsl r2, r2, #0x14
	tst r0, r2
	bne _0223594E
	ldr r0, [r6, #0x6c]
	add r4, r0, #0
	mul r4, r3
	add r4, r6, r4
	ldr r4, [r4, r1]
	lsl r1, r2, #3
	tst r1, r4
	bne _0223594E
	lsl r0, r0, #1
	add r1, r6, r0
	ldr r0, _02235A18 ; =0x0000307C
	ldrh r7, [r1, r0]
	cmp r7, #0
	bne _02235958
_0223594E:
	ldr r1, [sp]
	add r0, r6, #0
	bl ov11_0223A424
	b _02235A14
_02235958:
	mov r2, #0
	sub r3, #0xc1
	mov r4, ip
	add r5, r2, #0
_02235960:
	ldr r0, _02235A20 ; =0x00002D4C
	ldrh r0, [r4, r0]
	cmp r7, r0
	beq _02235988
	mov r0, ip
	add r1, r0, r5
	ldr r0, _02235A20 ; =0x00002D4C
	ldrh r0, [r1, r0]
	cmp r0, #0x66
	bne _0223597E
	mov r0, #0
	mvn r0, r0
	cmp r3, r0
	bne _0223597E
	add r3, r2, #0
_0223597E:
	add r2, r2, #1
	add r4, r4, #2
	add r5, r5, #2
	cmp r2, #4
	blt _02235960
_02235988:
	cmp r2, #4
	bne _02235A0C
	mov r4, #0x49
	lsl r4, r4, #2
	str r7, [r6, r4]
	ldr r2, [r6, #0x64]
	mov r1, #0xc0
	add r5, r2, #0
	mul r5, r1
	add r5, r6, r5
	lsl r2, r3, #1
	add r5, r5, r2
	ldr r0, [r6, r4]
	ldr r2, _02235A20 ; =0x00002D4C
	strh r0, [r5, r2]
	ldr r0, [r6, r4]
	lsl r0, r0, #4
	add r4, r6, r0
	mov r0, #0xf9
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	cmp r0, #5
	bhs _022359B8
	b _022359BA
_022359B8:
	mov r0, #5
_022359BA:
	ldr r4, [r6, #0x64]
	add r2, #0x20
	mul r1, r4
	add r1, r6, r1
	add r1, r1, r3
	strb r0, [r1, r2]
	add r0, r3, #0
	bl MaskOfFlagNo
	ldr r1, _02235A24 ; =0x00002DCC
	mov r4, #0xc0
	add r3, r6, r1
	ldr r1, [r6, #0x64]
	mov r5, #0x3c
	add r2, r1, #0
	mul r2, r4
	ldr r7, [r3, r2]
	add r1, r7, #0
	bic r1, r5
	lsl r5, r7, #0x1a
	lsr r5, r5, #0x1c
	orr r0, r5
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1a
	orr r0, r1
	str r0, [r3, r2]
	add r0, r4, #0
	add r0, #0x64
	ldr r1, [r6, r0]
	add r0, r4, #0
	add r0, #0xc3
	cmp r1, r0
	bne _02235A14
	ldr r0, [r6, #0x64]
	add r2, r0, #0
	mul r2, r4
	ldr r1, [r3, r2]
	ldr r0, _02235A28 ; =0xFFFFE3FF
	and r0, r1
	str r0, [r3, r2]
	b _02235A14
_02235A0C:
	ldr r1, [sp]
	add r0, r6, #0
	bl ov11_0223A424
_02235A14:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02235A18: .word 0x0000307C
_02235A1C: .word 0x00002DB0
_02235A20: .word 0x00002D4C
_02235A24: .word 0x00002DCC
_02235A28: .word 0xFFFFE3FF

	thumb_func_start ov11_02235A2C
ov11_02235A2C: ; 0x02235A2C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r0, r6, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r4, _02235A7C ; =0x00002D4C
	mov r7, #0xc0
_02235A3C:
	bl LCRandom
	ldr r1, _02235A80 ; =0x000001D3
	bl _s32_div_f
	add r0, r1, #1
	ldr r1, [r6, #0x64]
	lsl r0, r0, #0x10
	add r2, r1, #0
	mul r2, r7
	lsr r5, r0, #0x10
	mov r0, #0
	add r2, r6, r2
_02235A56:
	ldrh r1, [r2, r4]
	cmp r5, r1
	beq _02235A64
	add r0, r0, #1
	add r2, r2, #2
	cmp r0, #4
	blt _02235A56
_02235A64:
	cmp r0, #4
	bne _02235A3C
	add r0, r5, #0
	bl ov11_0224C07C
	cmp r0, #0
	beq _02235A3C
	mov r0, #0x49
	lsl r0, r0, #2
	str r5, [r6, r0]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02235A7C: .word 0x00002D4C
_02235A80: .word 0x000001D3

	thumb_func_start ov11_02235A84
ov11_02235A84: ; 0x02235A84
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	mov r0, #0xb5
	lsl r0, r0, #6
	add r2, r5, r0
	ldr r1, [r5, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	lsl r1, r1, #1
	add r0, r2, r0
	add r2, r5, r1
	ldr r1, _02235B34 ; =0x0000307C
	ldrh r1, [r2, r1]
	bl ov11_022461AC
	ldr r3, [r5, #0x6c]
	add r6, r0, #0
	mov r7, #0xc0
	add r0, r3, #0
	mul r0, r7
	add r2, r5, r0
	ldr r0, _02235B38 ; =0x00002DE8
	ldrh r1, [r2, r0]
	cmp r1, #0
	bne _02235B26
	cmp r6, #4
	beq _02235B26
	add r1, r0, #0
	add r2, r2, r6
	sub r1, #0x7c
	ldrb r1, [r2, r1]
	cmp r1, #0
	beq _02235B26
	lsl r1, r3, #1
	add r2, r5, r1
	ldr r1, _02235B34 ; =0x0000307C
	ldrh r2, [r2, r1]
	cmp r2, #0
	beq _02235B26
	add r1, r7, #0
	add r1, #0x64
	str r2, [r5, r1]
	add r1, r7, #0
	add r1, #0x64
	ldr r3, [r5, r1]
	ldr r1, [r5, #0x6c]
	add r2, r1, #0
	mul r2, r7
	add r1, r5, r2
	strh r3, [r1, r0]
	bl LCRandom
	ldr r1, _02235B3C ; =0x00002DC8
	ldr r4, [r5, #0x6c]
	add r3, r5, r1
	add r2, r4, #0
	add r1, r7, #0
	mul r2, r1
	ldr r1, [r3, r2]
	mov r4, #7
	bic r1, r4
	lsr r5, r0, #0x1f
	lsl r4, r0, #0x1e
	sub r4, r4, r5
	mov r0, #0x1e
	ror r4, r0
	add r0, r5, r4
	add r4, r0, #3
	mov r0, #7
	and r0, r4
	orr r0, r1
	str r0, [r3, r2]
	b _02235B2E
_02235B26:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223A424
_02235B2E:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02235B34: .word 0x0000307C
_02235B38: .word 0x00002DE8
_02235B3C: .word 0x00002DC8

	thumb_func_start ov11_02235B40
ov11_02235B40: ; 0x02235B40
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r1, [r5, #0x64]
	lsl r0, r1, #6
	add r2, r5, r0
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r4, [r2, r0]
	ldr r0, [sp]
	bl ov11_02230270
	str r0, [sp, #4]
	ldr r0, [sp]
	add r1, r4, #0
	bl ov11_02230270
	ldr r6, [r5, #0x64]
	add r3, r0, #0
	lsl r0, r6, #6
	add r1, r5, r0
	lsl r0, r4, #2
	add r0, r1, r0
	mov r1, #0x76
	lsl r1, r1, #2
	ldr r7, [r0, r1]
	cmp r7, #0
	beq _02235C06
	ldr r0, [sp, #4]
	cmp r0, r3
	beq _02235C06
	mov r0, #0xc0
	mul r0, r4
	add r2, r5, r0
	ldr r0, _02235C30 ; =0x00002D8C
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _02235C06
	ldr r0, _02235C34 ; =0x00002144
	lsl r2, r7, #1
	sub r1, #0x14
	str r2, [r5, r0]
	add r1, r5, r1
	lsl r0, r3, #3
	ldr r0, [r1, r0]
	lsl r1, r0, #0xb
	lsr r1, r1, #0x1f
	beq _02235BC0
	lsl r0, r0, #9
	lsr r0, r0, #0x1e
	mov r1, #0xc0
	mul r1, r0
	add r2, r5, r1
	ldr r1, _02235C30 ; =0x00002D8C
	ldr r1, [r2, r1]
	cmp r1, #0
	beq _02235BC0
	str r0, [r5, #0x6c]
	b _02235BC2
_02235BC0:
	str r4, [r5, #0x6c]
_02235BC2:
	ldr r1, [r5, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _02235C30 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _02235BFA
	ldr r0, [sp]
	ldr r2, [r5, #0x64]
	add r1, r5, #0
	bl ov11_022482A4
	mov r1, #0xc0
	mul r1, r0
	str r0, [r5, #0x6c]
	ldr r0, _02235C30 ; =0x00002D8C
	add r1, r5, r1
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _02235BFA
	mov r2, #0x26
	str r2, [r5, #0xc]
	add r0, r5, #0
	mov r1, #1
	add r2, #0xf3
	bl ov11_0223A434
_02235BFA:
	ldr r1, [r5, #0x64]
	ldr r2, [r5, #0x6c]
	add r0, r5, #0
	bl ov11_0224C438
	b _02235C28
_02235C06:
	mov r0, #0xb5
	lsl r0, r0, #2
	mov r1, #0x1c
	add r3, r6, #0
	mul r3, r1
	add r0, r5, r0
	ldr r2, [r0, r3]
	mov r1, #1
	bic r2, r1
	mov r1, #1
	orr r1, r2
	str r1, [r0, r3]
	ldr r1, _02235C38 ; =0x0000216C
	mov r0, #0x40
	ldr r2, [r5, r1]
	orr r0, r2
	str r0, [r5, r1]
_02235C28:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02235C30: .word 0x00002D8C
_02235C34: .word 0x00002144
_02235C38: .word 0x0000216C

	thumb_func_start ov11_02235C3C
ov11_02235C3C: ; 0x02235C3C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r1, [r5, #0x64]
	lsl r0, r1, #6
	add r2, r5, r0
	mov r0, #2
	lsl r0, r0, #8
	ldr r4, [r2, r0]
	ldr r0, [sp]
	bl ov11_02230270
	str r0, [sp, #4]
	ldr r0, [sp]
	add r1, r4, #0
	bl ov11_02230270
	ldr r6, [r5, #0x64]
	add r3, r0, #0
	lsl r0, r6, #6
	add r1, r5, r0
	lsl r0, r4, #2
	add r0, r1, r0
	mov r1, #0x1f
	lsl r1, r1, #4
	ldr r7, [r0, r1]
	cmp r7, #0
	beq _02235D02
	ldr r0, [sp, #4]
	cmp r0, r3
	beq _02235D02
	mov r0, #0xc0
	mul r0, r4
	add r2, r5, r0
	ldr r0, _02235D2C ; =0x00002D8C
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _02235D02
	ldr r0, _02235D30 ; =0x00002144
	lsl r2, r7, #1
	sub r1, #0x2c
	str r2, [r5, r0]
	add r1, r5, r1
	lsl r0, r3, #3
	ldr r0, [r1, r0]
	lsl r1, r0, #0xb
	lsr r1, r1, #0x1f
	beq _02235CBC
	lsl r0, r0, #9
	lsr r0, r0, #0x1e
	mov r1, #0xc0
	mul r1, r0
	add r2, r5, r1
	ldr r1, _02235D2C ; =0x00002D8C
	ldr r1, [r2, r1]
	cmp r1, #0
	beq _02235CBC
	str r0, [r5, #0x6c]
	b _02235CBE
_02235CBC:
	str r4, [r5, #0x6c]
_02235CBE:
	ldr r1, [r5, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _02235D2C ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _02235CF6
	ldr r0, [sp]
	ldr r2, [r5, #0x64]
	add r1, r5, #0
	bl ov11_022482A4
	mov r1, #0xc0
	mul r1, r0
	str r0, [r5, #0x6c]
	ldr r0, _02235D2C ; =0x00002D8C
	add r1, r5, r1
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _02235CF6
	mov r2, #0x26
	str r2, [r5, #0xc]
	add r0, r5, #0
	mov r1, #1
	add r2, #0xf3
	bl ov11_0223A434
_02235CF6:
	ldr r1, [r5, #0x64]
	ldr r2, [r5, #0x6c]
	add r0, r5, #0
	bl ov11_0224C438
	b _02235D24
_02235D02:
	mov r0, #0xb5
	lsl r0, r0, #2
	mov r1, #0x1c
	add r3, r6, #0
	mul r3, r1
	add r0, r5, r0
	ldr r2, [r0, r3]
	mov r1, #1
	bic r2, r1
	mov r1, #1
	orr r1, r2
	str r1, [r0, r3]
	ldr r1, _02235D34 ; =0x0000216C
	mov r0, #0x40
	ldr r2, [r5, r1]
	orr r0, r2
	str r0, [r5, r1]
_02235D24:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02235D2C: .word 0x00002D8C
_02235D30: .word 0x00002144
_02235D34: .word 0x0000216C

	thumb_func_start ov11_02235D38
ov11_02235D38: ; 0x02235D38
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r7, r0, #0
	mov r0, #0xb5
	lsl r0, r0, #6
	add r2, r5, r0
	ldr r1, [r5, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	lsl r1, r1, #1
	add r0, r2, r0
	add r2, r5, r1
	ldr r1, _02235E0C ; =0x0000307C
	ldrh r1, [r2, r1]
	bl ov11_022461AC
	ldr r1, [r5, #0x6c]
	add r4, r0, #0
	lsl r1, r1, #1
	add r2, r5, r1
	ldr r1, _02235E0C ; =0x0000307C
	add r0, r5, #0
	ldrh r1, [r2, r1]
	bl ov11_0224C0B4
	cmp r0, #0
	bne _02235D7E
	mov r4, #4
_02235D7E:
	ldr r0, [r5, #0x6c]
	mov r2, #0xc0
	add r1, r0, #0
	mul r1, r2
	ldr r3, _02235E10 ; =0x00002DEC
	add r6, r5, r1
	ldrh r1, [r6, r3]
	cmp r1, #0
	bne _02235DF6
	cmp r4, #4
	beq _02235DF6
	add r1, r3, #0
	add r6, r6, r4
	sub r1, #0x80
	ldrb r1, [r6, r1]
	cmp r1, #0
	beq _02235DF6
	lsl r0, r0, #1
	add r1, r5, r0
	ldr r0, _02235E0C ; =0x0000307C
	ldrh r1, [r1, r0]
	cmp r1, #0
	beq _02235DF6
	add r0, r2, #0
	add r0, #0x64
	str r1, [r5, r0]
	ldr r1, [r5, #0x6c]
	add r0, r2, #0
	add r0, #0x64
	add r6, r1, #0
	mul r6, r2
	ldr r0, [r5, r0]
	add r1, r5, r6
	strh r0, [r1, r3]
	ldr r0, [r5, #0x6c]
	add r1, r0, #0
	mul r1, r2
	add r1, r5, r1
	add r0, r3, #2
	strh r4, [r1, r0]
	bl LCRandom
	ldr r1, _02235E14 ; =0x00002DC8
	ldr r2, [r5, #0x6c]
	add r4, r5, r1
	mov r1, #0xc0
	add r5, r2, #0
	mul r5, r1
	mov r1, #5
	bl _s32_div_f
	ldr r2, [r4, r5]
	mov r0, #0x38
	bic r2, r0
	add r0, r1, #3
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1a
	orr r0, r2
	str r0, [r4, r5]
	b _02235E08
_02235DF6:
	ldr r1, _02235E18 ; =0x0000216C
	mov r0, #0x40
	ldr r2, [r5, r1]
	orr r0, r2
	str r0, [r5, r1]
	add r0, r5, #0
	add r1, r7, #0
	bl ov11_0223A424
_02235E08:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02235E0C: .word 0x0000307C
_02235E10: .word 0x00002DEC
_02235E14: .word 0x00002DC8
_02235E18: .word 0x0000216C

	thumb_func_start ov11_02235E1C
ov11_02235E1C: ; 0x02235E1C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp]
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x79
	bne _02235E4C
	ldr r1, [sp]
	add r0, r4, #0
	bl ov11_0223A424
	add sp, #8
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02235E4C:
	ldr r0, [r4, #0x64]
	lsl r0, r0, #1
	add r2, r4, r0
	ldr r0, _02235FB4 ; =0x000030C4
	ldrh r1, [r2, r0]
	cmp r1, #0
	beq _02235E62
	add r0, #8
	ldrh r0, [r2, r0]
	cmp r0, #0xff
	bne _02235E64
_02235E62:
	b _02235FA6
_02235E64:
	add r0, r4, #0
	bl ov11_02246AF8
	cmp r0, #0
	beq _02235E98
	ldr r0, [r4, #0x64]
	lsl r0, r0, #1
	add r1, r4, r0
	ldr r0, _02235FB8 ; =0x000030CC
	ldrh r1, [r1, r0]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _02235FBC ; =0x00002DB0
	ldr r1, [r1, r0]
	mov r0, #1
	lsl r0, r0, #0xc
	tst r0, r1
	beq _02235E98
	ldr r1, [sp]
	add r0, r4, #0
	bl ov11_0223A424
	add sp, #8
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02235E98:
	ldr r0, [r4, #0x64]
	mov r7, #0
	lsl r0, r0, #1
	add r1, r4, r0
	ldr r0, _02235FC0 ; =0x000030D4
	ldrh r6, [r1, r0]
_02235EA4:
	add r1, sp, #4
	add r2, sp, #4
	ldr r0, _02235FC4 ; =0x0000FFFF
	add r1, #2
	add r2, #1
	add r3, sp, #4
	bl ov11_02246B58
	add r0, sp, #4
	ldrb r0, [r0, #2]
	cmp r0, r6
	bne _02235F12
	add r0, sp, #4
	ldrb r0, [r0]
	cmp r0, #5
	bhi _02235F12
	add r0, sp, #4
	ldrb r5, [r0, #1]
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	mov r2, #0x1b
	mov r3, #0
	bl ov11_02243420
	cmp r5, r0
	beq _02235F12
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	mov r2, #0x1c
	mov r3, #0
	bl ov11_02243420
	cmp r5, r0
	beq _02235F12
	ldr r0, [r4, #0x64]
	add r3, sp, #4
	mov r2, #0xc0
	add r1, r0, #0
	mul r1, r2
	add r0, r4, r1
	ldr r1, _02235FC8 ; =0x00002D64
	add sp, #8
	strb r5, [r0, r1]
	ldr r5, [r4, #0x64]
	ldrb r0, [r3, #1]
	add r6, r5, #0
	mul r6, r2
	add r5, r4, r6
	add r1, r1, #1
	strb r0, [r5, r1]
	ldrb r0, [r3, #1]
	add r2, #0x70
	str r0, [r4, r2]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02235F12:
	mov r0, #0xfa
	add r7, r7, #1
	lsl r0, r0, #2
	cmp r7, r0
	blt _02235EA4
	mov r7, #0
	add r1, sp, #4
	add r2, sp, #4
	add r0, r7, #0
	add r1, #2
	add r2, #1
	add r3, sp, #4
	bl ov11_02246B58
	cmp r0, #1
	bne _02235FA6
_02235F32:
	add r0, sp, #4
	ldrb r0, [r0, #2]
	cmp r0, r6
	bne _02235F90
	add r0, sp, #4
	ldrb r0, [r0]
	cmp r0, #5
	bhi _02235F90
	add r0, sp, #4
	ldrb r5, [r0, #1]
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	mov r2, #0x1b
	mov r3, #0
	bl ov11_02243420
	cmp r5, r0
	beq _02235F90
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	mov r2, #0x1c
	mov r3, #0
	bl ov11_02243420
	cmp r5, r0
	beq _02235F90
	ldr r0, [r4, #0x64]
	add r3, sp, #4
	mov r2, #0xc0
	add r1, r0, #0
	mul r1, r2
	add r0, r4, r1
	ldr r1, _02235FC8 ; =0x00002D64
	add sp, #8
	strb r5, [r0, r1]
	ldr r5, [r4, #0x64]
	ldrb r0, [r3, #1]
	add r6, r5, #0
	mul r6, r2
	add r5, r4, r6
	add r1, r1, #1
	strb r0, [r5, r1]
	ldrb r0, [r3, #1]
	add r2, #0x70
	str r0, [r4, r2]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02235F90:
	add r7, r7, #1
	add r1, sp, #4
	add r2, sp, #4
	add r0, r7, #0
	add r1, #2
	add r2, #1
	add r3, sp, #4
	bl ov11_02246B58
	cmp r0, #1
	beq _02235F32
_02235FA6:
	ldr r1, [sp]
	add r0, r4, #0
	bl ov11_0223A424
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02235FB4: .word 0x000030C4
_02235FB8: .word 0x000030CC
_02235FBC: .word 0x00002DB0
_02235FC0: .word 0x000030D4
_02235FC4: .word 0x0000FFFF
_02235FC8: .word 0x00002D64

	thumb_func_start ov11_02235FCC
ov11_02235FCC: ; 0x02235FCC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r0, [sp]
	mov r0, #0
	add r6, r1, #0
	mvn r0, r0
	str r0, [sp, #8]
	add r0, r6, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r6, #0
	bl ov11_0223A404
	mov ip, r0
	ldr r1, [r6, #0x64]
	mov r0, #0xc0
	mul r0, r1
	str r0, [sp, #4]
	add r3, r6, r0
	ldr r0, _022360DC ; =0x00002DB0
	ldr r1, [r3, r0]
	mov r0, #2
	lsl r0, r0, #0x14
	tst r0, r1
	bne _0223601E
	ldr r0, [r6, #0x6c]
	lsl r0, r0, #1
	add r1, r6, r0
	ldr r0, _022360E0 ; =0x000030AC
	ldrh r7, [r1, r0]
	cmp r7, #0xa5
	beq _0223601E
	cmp r7, #0xa6
	beq _0223601E
	mov r0, #7
	lsl r0, r0, #6
	cmp r7, r0
	beq _0223601E
	cmp r7, #0
	bne _02236028
_0223601E:
	add r0, r6, #0
	mov r1, ip
	bl ov11_0223A424
	b _022360D6
_02236028:
	mov r0, #0
	add r1, r3, #0
	add r2, r0, #0
_0223602E:
	ldr r4, _022360E4 ; =0x00002D4C
	ldrh r4, [r1, r4]
	cmp r4, #0xa6
	beq _02236040
	ldr r4, _022360E4 ; =0x00002D4C
	add r5, r3, r2
	ldrh r4, [r5, r4]
	cmp r7, r4
	beq _02236060
_02236040:
	ldr r4, _022360E4 ; =0x00002D4C
	add r5, r3, r2
	ldrh r4, [r5, r4]
	cmp r4, #0xa6
	bne _02236056
	mov r5, #0
	ldr r4, [sp, #8]
	mvn r5, r5
	cmp r4, r5
	bne _02236056
	str r0, [sp, #8]
_02236056:
	add r0, r0, #1
	add r1, r1, #2
	add r2, r2, #2
	cmp r0, #4
	blt _0223602E
_02236060:
	cmp r0, #4
	bne _022360CE
	ldr r0, [sp, #4]
	add r1, r6, r0
	ldr r0, [sp, #8]
	lsl r0, r0, #1
	add r1, r1, r0
	ldr r0, _022360E4 ; =0x00002D4C
	strh r7, [r1, r0]
	ldr r1, [r6, #0x6c]
	ldr r3, [r6, #0x64]
	lsl r1, r1, #1
	add r2, r6, r1
	ldr r1, _022360E0 ; =0x000030AC
	add r0, #0x20
	ldrh r1, [r2, r1]
	lsl r1, r1, #4
	add r2, r6, r1
	mov r1, #0xf9
	lsl r1, r1, #2
	ldrb r1, [r2, r1]
	mov r2, #0xc0
	mul r2, r3
	add r3, r6, r2
	ldr r2, [sp, #8]
	add r2, r3, r2
	strb r1, [r2, r0]
	ldr r0, [sp]
	ldr r2, [r6, #0x64]
	add r1, r6, #0
	bl ov11_02256150
	ldr r0, [r6, #0x6c]
	lsl r0, r0, #1
	add r1, r6, r0
	ldr r0, _022360E0 ; =0x000030AC
	ldrh r1, [r1, r0]
	mov r0, #0x49
	lsl r0, r0, #2
	str r1, [r6, r0]
	ldr r1, [r6, r0]
	add r0, #0x5f
	cmp r1, r0
	bne _022360D6
	ldr r0, _022360E8 ; =0x00002DCC
	ldr r1, [r6, #0x64]
	add r3, r6, r0
	mov r0, #0xc0
	add r2, r1, #0
	mul r2, r0
	ldr r1, [r3, r2]
	ldr r0, _022360EC ; =0xFFFFE3FF
	and r0, r1
	str r0, [r3, r2]
	b _022360D6
_022360CE:
	add r0, r6, #0
	mov r1, ip
	bl ov11_0223A424
_022360D6:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022360DC: .word 0x00002DB0
_022360E0: .word 0x000030AC
_022360E4: .word 0x00002D4C
_022360E8: .word 0x00002DCC
_022360EC: .word 0xFFFFE3FF

	thumb_func_start ov11_022360F0
ov11_022360F0: ; 0x022360F0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	mov r7, #0
	str r0, [sp, #8]
	add r6, r7, #0
	add r4, r7, #0
_0223610E:
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r0, r5, r0
	add r1, r4, r0
	ldr r0, _022361B8 ; =0x00002D4C
	ldrh r0, [r1, r0]
	bl ov11_02246BE8
	cmp r0, #0
	bne _0223614E
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r0, r5, r0
	add r1, r4, r0
	ldr r0, _022361B8 ; =0x00002D4C
	ldrh r1, [r1, r0]
	mov r0, #0x42
	lsl r0, r0, #2
	cmp r1, r0
	beq _0223614E
	cmp r1, #0xfd
	beq _0223614E
	add r0, #0xb8
	cmp r1, r0
	beq _0223614E
	add r0, r5, #0
	bl ov11_02246AF8
	cmp r0, #0
	beq _02236156
_0223614E:
	add r0, r6, #0
	bl MaskOfFlagNo
	orr r7, r0
_02236156:
	add r6, r6, #1
	add r4, r4, #2
	cmp r6, #4
	blt _0223610E
	mov r0, #2
	mvn r0, r0
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r2, [r5, #0x64]
	add r1, r5, #0
	add r3, r7, #0
	bl ov11_02245D38
	add r4, r0, #0
	cmp r4, #0xf
	bne _02236180
	ldr r1, [sp, #8]
	add r0, r5, #0
	bl ov11_0223A424
	b _022361B0
_02236180:
	mov r7, #0x1e
_02236182:
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r0, r0, #0x1e
	sub r0, r0, r1
	ror r0, r7
	add r6, r1, r0
	add r0, r6, #0
	bl MaskOfFlagNo
	tst r0, r4
	bne _02236182
	ldr r0, [r5, #0x64]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	add r2, r5, r2
	lsl r0, r6, #1
	add r2, r2, r0
	ldr r0, _022361B8 ; =0x00002D4C
	add r1, #0x64
	ldrh r0, [r2, r0]
	str r0, [r5, r1]
_022361B0:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_022361B8: .word 0x00002D4C

	thumb_func_start ov11_022361BC
ov11_022361BC: ; 0x022361BC
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	ldr r1, _02236200 ; =0x00002D8C
	add r2, r4, r0
	ldr r0, [r2, r1]
	add r1, r1, #4
	ldr r1, [r2, r1]
	mov r2, #0x40
	bl sub_02079A0C
	ldr r3, _02236204 ; =ov11_0225DC3C
	mov r2, #0
_022361E2:
	ldrb r1, [r3]
	cmp r0, r1
	ble _022361F0
	add r2, r2, #1
	add r3, r3, #2
	cmp r2, #6
	blo _022361E2
_022361F0:
	ldr r0, _02236208 ; =ov11_0225DC3D
	lsl r1, r2, #1
	ldrb r1, [r0, r1]
	ldr r0, _0223620C ; =0x00002154
	str r1, [r4, r0]
	mov r0, #0
	pop {r4, pc}
	nop
_02236200: .word 0x00002D8C
_02236204: .word ov11_0225DC3C
_02236208: .word ov11_0225DC3D
_0223620C: .word 0x00002154

	thumb_func_start ov11_02236210
ov11_02236210: ; 0x02236210
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	ldr r2, [r5, #0x6c]
	add r4, r0, #0
	lsl r0, r2, #1
	add r1, r5, r0
	ldr r0, _022362AC ; =0x0000307C
	ldrh r1, [r1, r0]
	cmp r1, #0
	beq _0223629E
	mov r0, #0xb5
	lsl r0, r0, #6
	mov r3, #0xc0
	add r0, r5, r0
	mul r3, r2
	add r0, r0, r3
	bl ov11_022461AC
	add r2, r0, #0
	cmp r2, #4
	beq _0223625C
	ldr r0, [r5, #0x6c]
	mov r1, #0xc0
	mul r1, r0
	add r1, r5, r1
	add r3, r1, r2
	ldr r1, _022362B0 ; =0x00002D6C
	ldrb r3, [r3, r1]
	cmp r3, #0
	bne _02236266
_0223625C:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223A424
	b _022362A6
_02236266:
	mov r1, #4
	cmp r3, #4
	bge _0223626E
	add r1, r3, #0
_0223626E:
	lsl r0, r0, #1
	add r3, r5, r0
	ldr r0, _022362AC ; =0x0000307C
	ldrh r3, [r3, r0]
	mov r0, #0x49
	lsl r0, r0, #2
	str r3, [r5, r0]
	add r0, #0xc
	str r1, [r5, r0]
	ldr r0, _022362B0 ; =0x00002D6C
	ldr r4, [r5, #0x6c]
	mov r3, #0xc0
	add r0, r5, r0
	mul r3, r4
	add r3, r0, r3
	ldrb r0, [r3, r2]
	sub r0, r0, r1
	strb r0, [r3, r2]
	ldr r2, [r5, #0x6c]
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_02245190
	b _022362A6
_0223629E:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223A424
_022362A6:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_022362AC: .word 0x0000307C
_022362B0: .word 0x00002D6C

	thumb_func_start ov11_022362B4
ov11_022362B4: ; 0x022362B4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	bl ov11_0222FF74
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	mov r1, #0x4d
	mov r0, #0
	lsl r1, r1, #2
	ldr r2, _022363F4 ; =0x00003044
	str r0, [r5, r1]
	ldr r2, [r5, r2]
	cmp r2, #0xd7
	bne _02236382
	sub r1, #0x10
	str r2, [r5, r1]
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl ov11_02246D1C
	cmp r0, #0x2b
	beq _0223630A
	ldr r2, [r5, #0x64]
	mov r0, #0xc0
	add r3, r2, #0
	mul r3, r0
	ldr r2, _022363F8 ; =0x00002DAC
	mov r1, #0
	add r3, r5, r3
	str r1, [r3, r2]
	add r1, r2, #4
	ldr r2, [r5, #0x64]
	add r1, r5, r1
	mul r0, r2
	ldr r3, [r1, r0]
	ldr r2, _022363FC ; =0xF7FFFFFF
	and r2, r3
	str r2, [r1, r0]
	b _02236316
_0223630A:
	mov r1, #0x4d
	lsl r1, r1, #2
	ldr r2, [r5, r1]
	mov r0, #5
	orr r0, r2
	str r0, [r5, r1]
_02236316:
	mov r0, #2
	tst r0, r4
	beq _02236374
	add r0, r7, #0
	add r1, r5, #0
	mov r2, #0x10
	bl ov11_0223C230
	add r4, r0, #0
	bl MaskOfFlagNo
	ldr r1, _02236400 ; =0x00003108
	ldrb r1, [r5, r1]
	tst r0, r1
	bne _022363E2
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	add r2, r4, #0
	mov r3, #0x2b
	bl ov11_02246D84
	cmp r0, #0
	bne _0223635E
	mov r0, #0xc0
	mul r0, r4
	ldr r1, _022363F8 ; =0x00002DAC
	mov r3, #0
	add r2, r5, r0
	str r3, [r2, r1]
	add r1, r1, #4
	add r3, r5, r1
	ldr r2, [r3, r0]
	ldr r1, _022363FC ; =0xF7FFFFFF
	and r1, r2
	str r1, [r3, r0]
	b _022363E2
_0223635E:
	mov r1, #0x46
	lsl r1, r1, #2
	add r0, r1, #0
	str r4, [r5, r1]
	add r0, #0x1c
	ldr r2, [r5, r0]
	mov r0, #0xa
	orr r0, r2
	add r1, #0x1c
	str r0, [r5, r1]
	b _022363E2
_02236374:
	mov r1, #0x4d
	lsl r1, r1, #2
	ldr r2, [r5, r1]
	mov r0, #8
	orr r0, r2
	str r0, [r5, r1]
	b _022363E2
_02236382:
	ldr r3, [r5, #0x64]
	mov r2, #0xc0
	mul r2, r3
	add r3, r5, r2
	ldr r2, _022363F8 ; =0x00002DAC
	str r0, [r3, r2]
	add r0, r2, #4
	add r6, r5, r0
	ldr r0, [r5, #0x64]
	mov r2, #0xc0
	add r3, r0, #0
	mul r3, r2
	ldr r2, [r6, r3]
	ldr r0, _022363FC ; =0xF7FFFFFF
	and r0, r2
	str r0, [r6, r3]
	mov r0, #2
	tst r0, r4
	beq _022363DA
	add r0, r7, #0
	add r1, r5, #0
	mov r2, #0x10
	bl ov11_0223C230
	add r4, r0, #0
	bl MaskOfFlagNo
	ldr r1, _02236400 ; =0x00003108
	ldrb r1, [r5, r1]
	tst r0, r1
	bne _022363E2
	mov r0, #0xc0
	mul r0, r4
	ldr r1, _022363F8 ; =0x00002DAC
	mov r3, #0
	add r2, r5, r0
	str r3, [r2, r1]
	add r1, r1, #4
	add r3, r5, r1
	ldr r2, [r3, r0]
	ldr r1, _022363FC ; =0xF7FFFFFF
	and r1, r2
	str r1, [r3, r0]
	b _022363E2
_022363DA:
	ldr r2, [r5, r1]
	mov r0, #8
	orr r0, r2
	str r0, [r5, r1]
_022363E2:
	ldr r3, _022363F4 ; =0x00003044
	ldr r2, [r5, #0x64]
	ldr r3, [r5, r3]
	add r0, r7, #0
	add r1, r5, #0
	bl ov11_02256284
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022363F4: .word 0x00003044
_022363F8: .word 0x00002DAC
_022363FC: .word 0xF7FFFFFF
_02236400: .word 0x00003108

	thumb_func_start ov11_02236404
ov11_02236404: ; 0x02236404
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp]
	add r0, r5, #0
	bl ov11_0222FF74
	str r0, [sp, #4]
	ldr r1, [r4, #0x64]
	add r0, r5, #0
	bl ov11_02230270
	add r7, r0, #0
	ldr r1, [r4, #0x64]
	add r0, r5, #0
	bl ov11_02230270
	cmp r0, #0
	beq _02236454
	ldr r0, [sp, #4]
	mov r1, #0x84
	tst r0, r1
	bne _02236454
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
	b _022364EC
_02236454:
	ldr r0, [r4, #0x64]
	add r1, r4, r0
	ldr r0, _022364F4 ; =0x0000219C
	ldrb r0, [r1, r0]
	bl MaskOfFlagNo
	lsl r1, r7, #3
	add r2, r4, r1
	mov r1, #0x71
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	lsl r1, r1, #3
	lsr r1, r1, #0x1a
	tst r0, r1
	beq _0223647C
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
	b _022364EC
_0223647C:
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x79
	beq _02236494
	ldr r1, [r4, #0x6c]
	add r0, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x79
	bne _0223649E
_02236494:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
	b _022364EC
_0223649E:
	ldr r2, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r2
	add r1, r4, r0
	ldr r0, _022364F8 ; =0x00002DB8
	ldrh r0, [r1, r0]
	cmp r0, #0
	beq _022364C6
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	mov r3, #0x3c
	bl ov11_02246D84
	cmp r0, #1
	bne _022364C6
	ldr r1, [sp]
	add r0, r4, #0
	bl ov11_0223A424
	b _022364EC
_022364C6:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _022364F8 ; =0x00002DB8
	ldrh r0, [r1, r0]
	cmp r0, #0
	bne _022364E4
	ldr r2, [r4, #0x6c]
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02246C50
	cmp r0, #0
	bne _022364EC
_022364E4:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
_022364EC:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022364F4: .word 0x0000219C
_022364F8: .word 0x00002DB8

	thumb_func_start ov11_022364FC
ov11_022364FC: ; 0x022364FC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r1, #0
	str r0, [sp]
	add r0, r6, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r6, #0
	bl ov11_0223A404
	ldr r1, [r6, #0x64]
	str r0, [sp, #8]
	lsl r0, r1, #1
	add r2, r6, r0
	ldr r0, _02236640 ; =0x0000305C
	ldrh r0, [r2, r0]
	cmp r0, #0xb6
	beq _0223653C
	cmp r0, #0xc5
	beq _0223653C
	cmp r0, #0xcb
	beq _0223653C
	ldr r0, _02236644 ; =0x00002DC8
	add r3, r1, #0
	mov r2, #0xc0
	add r0, r6, r0
	mul r3, r2
	ldr r2, [r0, r3]
	ldr r1, _02236648 ; =0xFFFFE7FF
	and r1, r2
	str r1, [r0, r3]
_0223653C:
	ldr r0, [sp]
	mov r7, #0
	add r4, r7, #0
	bl ov11_0222FF84
	cmp r0, #0
	ble _02236564
	add r5, r6, #0
_0223654C:
	ldr r0, _0223664C ; =0x000021A8
	ldr r0, [r5, r0]
	cmp r0, #0x27
	beq _02236556
	add r7, r7, #1
_02236556:
	ldr r0, [sp]
	add r5, #0x10
	add r4, r4, #1
	bl ov11_0222FF84
	cmp r4, r0
	blt _0223654C
_02236564:
	cmp r7, #1
	beq _0223656E
	mov r0, #1
	str r0, [sp, #4]
	b _02236572
_0223656E:
	mov r0, #0
	str r0, [sp, #4]
_02236572:
	ldr r7, [r6, #0x64]
	ldr r0, _02236644 ; =0x00002DC8
	add r5, r7, #0
	add r4, r6, r0
	mov r0, #0xc0
	mul r5, r0
	bl LCRandom
	ldr r1, [r4, r5]
	lsl r1, r1, #0x13
	lsr r1, r1, #0x1e
	lsl r2, r1, #1
	ldr r1, _02236650 ; =ov11_0225DC34
	ldrh r1, [r1, r2]
	cmp r1, r0
	blo _02236628
	ldr r0, [sp, #4]
	cmp r0, #0
	beq _02236628
	ldr r0, _02236654 ; =0x00003044
	ldr r0, [r6, r0]
	lsl r0, r0, #4
	add r1, r6, r0
	ldr r0, _02236658 ; =0x000003DE
	ldrh r0, [r1, r0]
	cmp r0, #0x6f
	bne _022365C0
	mov r2, #0x75
	lsl r2, r2, #2
	add r0, r6, r2
	lsl r4, r7, #6
	ldr r3, [r0, r4]
	mov r1, #4
	orr r1, r3
	str r1, [r0, r4]
	add r0, r6, #0
	sub r2, #0xba
	add r0, #0xf6
	strh r2, [r0]
_022365C0:
	ldr r0, _02236654 ; =0x00003044
	ldr r0, [r6, r0]
	lsl r0, r0, #4
	add r1, r6, r0
	ldr r0, _02236658 ; =0x000003DE
	ldrh r0, [r1, r0]
	cmp r0, #0x74
	bne _022365EC
	mov r2, #0x75
	ldr r1, [r6, #0x64]
	lsl r2, r2, #2
	lsl r4, r1, #6
	add r0, r6, r2
	add r1, r2, #0
	ldr r3, [r0, r4]
	add r1, #0x2c
	orr r1, r3
	str r1, [r0, r4]
	add r0, r6, #0
	sub r2, #0x1a
	add r0, #0xf6
	strh r2, [r0]
_022365EC:
	add r0, r6, #0
	mov r1, #2
	add r0, #0xf5
	strb r1, [r0]
	ldr r1, [r6, #0x64]
	add r0, r6, #0
	bl ov11_0224682C
	add r1, r6, #0
	add r1, #0xf8
	str r0, [r1]
	ldr r2, [r6, #0x64]
	mov r0, #0xc0
	add r1, r2, #0
	mul r1, r0
	ldr r0, _02236644 ; =0x00002DC8
	add r0, r6, r0
	ldr r3, [r0, r1]
	lsl r2, r3, #0x13
	lsr r4, r2, #0x1e
	cmp r4, #3
	bhs _02236638
	ldr r2, _02236648 ; =0xFFFFE7FF
	and r3, r2
	add r2, r4, #1
	lsl r2, r2, #0x1e
	lsr r2, r2, #0x13
	orr r2, r3
	str r2, [r0, r1]
	b _02236638
_02236628:
	ldr r1, [r4, r5]
	ldr r0, _02236648 ; =0xFFFFE7FF
	and r0, r1
	str r0, [r4, r5]
	ldr r1, [sp, #8]
	add r0, r6, #0
	bl ov11_0223A424
_02236638:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02236640: .word 0x0000305C
_02236644: .word 0x00002DC8
_02236648: .word 0xFFFFE7FF
_0223664C: .word 0x000021A8
_02236650: .word ov11_0225DC34
_02236654: .word 0x00003044
_02236658: .word 0x000003DE

	thumb_func_start ov11_0223665C
ov11_0223665C: ; 0x0223665C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _022366C8 ; =0x00002D90
	ldr r0, [r1, r0]
	mov r1, #4
	bl ov11_022476C0
	ldr r1, [r5, #0x64]
	mov r2, #0xc0
	add r3, r1, #0
	mul r3, r2
	add r1, r5, r3
	ldr r3, _022366CC ; =0x00002D8C
	ldr r1, [r1, r3]
	cmp r1, r0
	bgt _0223669E
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223A424
	b _022366C2
_0223669E:
	ldr r1, _022366D0 ; =0x0000215C
	neg r4, r0
	str r4, [r5, r1]
	ldr r1, [r5, #0x64]
	add r4, r1, #0
	add r1, r3, #0
	mul r4, r2
	add r3, #0x24
	add r4, r5, r4
	add r1, #0x54
	str r0, [r4, r1]
	ldr r0, [r5, #0x64]
	add r3, r5, r3
	mul r2, r0
	ldr r1, [r3, r2]
	ldr r0, _022366D4 ; =0xFFFF1FFF
	and r0, r1
	str r0, [r3, r2]
_022366C2:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_022366C8: .word 0x00002D90
_022366CC: .word 0x00002D8C
_022366D0: .word 0x0000215C
_022366D4: .word 0xFFFF1FFF

	thumb_func_start ov11_022366D8
ov11_022366D8: ; 0x022366D8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	str r1, [sp]
	add r0, r1, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r0, [sp]
	bl ov11_0223A404
	str r0, [sp, #0x18]
	add r0, r5, #0
	bl ov11_0222FF74
	add r4, r0, #0
	mov r0, #1
	tst r0, r4
	bne _02236700
	b _0223684E
_02236700:
	ldr r1, [sp]
	add r0, r5, #0
	ldr r1, [r1, #0x6c]
	mov r7, #0
	bl ov11_0222FF88
	ldr r1, [sp]
	str r0, [sp, #0x14]
	ldr r1, [r1, #0x6c]
	add r0, r5, #0
	bl ov11_0222FFC8
	add r6, r0, #0
	mov r0, #8
	tst r0, r4
	bne _02236734
	mov r0, #0x10
	tst r0, r4
	beq _0223674C
	ldr r1, [sp]
	add r0, r5, #0
	ldr r1, [r1, #0x6c]
	bl ov11_02230270
	cmp r0, #0
	beq _0223674C
_02236734:
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, [sp]
	ldr r1, [r0, #0x6c]
	add r1, r0, r1
	ldr r0, _02236868 ; =0x0000219C
	ldrb r0, [r1, r0]
	str r0, [sp, #8]
	str r0, [sp, #4]
	b _0223678C
_0223674C:
	mov r0, #2
	str r0, [sp, #0x10]
	tst r0, r4
	beq _02236776
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp]
	ldr r1, [r0, #0x6c]
	add r2, r0, r1
	ldr r0, _02236868 ; =0x0000219C
	ldrb r0, [r2, r0]
	str r0, [sp, #8]
	add r0, r5, #0
	bl ov11_022302BC
	ldr r1, [sp]
	add r1, r1, r0
	ldr r0, _02236868 ; =0x0000219C
	ldrb r0, [r1, r0]
	str r0, [sp, #4]
	b _0223678C
_02236776:
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, [sp]
	ldr r1, [r0, #0x6c]
	add r1, r0, r1
	ldr r0, _02236868 ; =0x0000219C
	ldrb r0, [r1, r0]
	str r0, [sp, #8]
	str r0, [sp, #4]
_0223678C:
	ldr r5, [sp, #0xc]
	add r0, r5, #0
	cmp r0, r6
	bge _022367CE
_02236794:
	ldr r0, [sp, #0x14]
	add r1, r5, #0
	bl Party_GetMonByIndex
	mov r1, #5
	mov r2, #0
	add r4, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _022367C8
	add r0, r4, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _022367C8
	add r0, r4, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _022367C8
	add r7, r7, #1
_022367C8:
	add r5, r5, #1
	cmp r5, r6
	blt _02236794
_022367CE:
	ldr r0, [sp, #0x10]
	cmp r7, r0
	bgt _022367DE
	ldr r0, [sp]
	ldr r1, [sp, #0x18]
	bl ov11_0223A424
	b _02236860
_022367DE:
	ldr r0, [sp]
	bl ov11_02246CCC
	cmp r0, #0
	beq _02236844
	mov r7, #5
_022367EA:
	bl LCRandom
	add r1, r6, #0
	bl _s32_div_f
	ldr r0, [sp, #0xc]
	add r5, r1, #0
	add r5, r5, r0
	ldr r0, [sp, #8]
	cmp r5, r0
	beq _022367EA
	ldr r0, [sp, #4]
	cmp r5, r0
	beq _022367EA
	ldr r0, [sp, #0x14]
	add r1, r5, #0
	bl Party_GetMonByIndex
	add r1, r7, #0
	mov r2, #0
	add r4, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _022367EA
	add r0, r4, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #1
	beq _022367EA
	add r0, r4, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _022367EA
	ldr r0, [sp]
	ldr r1, [r0, #0x6c]
	add r1, r0, r1
	ldr r0, _0223686C ; =0x000021A0
	strb r5, [r1, r0]
	b _02236860
_02236844:
	ldr r0, [sp]
	ldr r1, [sp, #0x18]
	bl ov11_0223A424
	b _02236860
_0223684E:
	ldr r0, [sp]
	bl ov11_02246CCC
	cmp r0, #0
	bne _02236860
	ldr r0, [sp]
	ldr r1, [sp, #0x18]
	bl ov11_0223A424
_02236860:
	mov r0, #0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_02236868: .word 0x0000219C
_0223686C: .word 0x000021A0

	thumb_func_start ov11_02236870
ov11_02236870: ; 0x02236870
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r5, [r4, #0x64]
	ldr r1, _02236A40 ; =0x00002DB0
	add r0, r5, #0
	mov r2, #0xc0
	mov r5, #2
	add r3, r4, r1
	mul r0, r2
	ldr r6, [r3, r0]
	lsl r5, r5, #0x14
	orr r5, r6
	str r5, [r3, r0]
	ldr r3, [r4, #0x64]
	mov r0, #0
	add r5, r3, #0
	mul r5, r2
	add r3, r1, #0
	add r5, r4, r5
	add r3, #0x38
	strh r0, [r5, r3]
	add r3, r1, #0
	add r3, #0x18
	ldr r6, [r4, #0x64]
	add r5, r4, r3
	add r3, r6, #0
	mul r3, r2
	ldr r7, [r5, r3]
	mov r6, #7
	bic r7, r6
	str r7, [r5, r3]
	ldr r3, [r4, #0x6c]
	add r5, r3, #0
	mul r5, r2
	add r3, r1, #0
	add r5, r4, r5
	sub r3, #8
	ldr r3, [r5, r3]
	ldr r5, [r4, #0x64]
	add r6, r5, #0
	mul r6, r2
	add r5, r1, #0
	add r6, r4, r6
	add r5, #0x34
	str r3, [r6, r5]
	ldr r3, [r4, #0x6c]
	add r5, r3, #0
	mul r5, r2
	add r3, r1, #0
	add r5, r4, r5
	add r3, #0xe
	ldrb r3, [r5, r3]
	ldr r5, [r4, #0x64]
	add r6, r5, #0
	lsl r3, r3, #0x1c
	mul r6, r2
	add r5, r1, #0
	lsr r3, r3, #0x1c
	add r6, r4, r6
	add r5, #0x4a
	strh r3, [r6, r5]
	add r3, r1, #0
	add r3, #0x1c
	ldr r6, [r4, #0x64]
	add r5, r4, r3
	add r3, r6, #0
	mul r3, r2
	ldr r7, [r5, r3]
	mov r6, #0x3c
	bic r7, r6
	str r7, [r5, r3]
	ldr r6, [r4, #0x64]
	sub r1, #0x70
	add r3, r6, #0
	mul r3, r2
	ldr r7, [r5, r3]
	ldr r6, _02236A44 ; =0xFFFFE3FF
	and r6, r7
	str r6, [r5, r3]
	add r5, r4, r1
	ldr r1, [r4, #0x64]
	add r3, r1, #0
	mul r3, r2
	ldr r1, [r4, #0x6c]
	add r3, r5, r3
	mul r2, r1
	add r2, r5, r2
_02236926:
	ldrb r1, [r2, r0]
	strb r1, [r3, r0]
	add r0, r0, #1
	cmp r0, #0x28
	blo _02236926
	ldr r3, [r4, #0x64]
	ldr r1, _02236A48 ; =0x00002D68
	add r6, r3, #0
	mov r2, #0xc0
	add r0, r4, r1
	mul r6, r2
	ldr r5, [r0, r6]
	mov r3, #1
	bic r5, r3
	str r5, [r0, r6]
	ldr r3, [r4, #0x64]
	add r6, r3, #0
	mul r6, r2
	ldr r5, [r0, r6]
	mov r3, #2
	bic r5, r3
	str r5, [r0, r6]
	ldr r3, [r4, #0x64]
	add r6, r3, #0
	mul r6, r2
	ldr r5, [r0, r6]
	mov r3, #4
	bic r5, r3
	str r5, [r0, r6]
	ldr r3, [r4, #0x64]
	add r6, r3, #0
	mul r6, r2
	ldr r5, [r0, r6]
	mov r3, #8
	bic r5, r3
	str r5, [r0, r6]
	ldr r3, [r4, #0x64]
	add r6, r3, #0
	mul r6, r2
	ldr r5, [r0, r6]
	mov r3, #0x10
	bic r5, r3
	str r5, [r0, r6]
	ldr r3, [r4, #0x64]
	add r6, r3, #0
	mul r6, r2
	ldr r5, [r0, r6]
	mov r3, #0x20
	bic r5, r3
	str r5, [r0, r6]
	ldr r5, [r4, #0x64]
	add r3, r5, #0
	mul r3, r2
	ldr r6, [r0, r3]
	ldr r5, _02236A4C ; =0xFFFFFEFF
	and r5, r6
	str r5, [r0, r3]
	ldr r5, [r4, #0x64]
	add r3, r5, #0
	mul r3, r2
	ldr r6, [r0, r3]
	ldr r5, _02236A50 ; =0xFFFFFDFF
	and r5, r6
	str r5, [r0, r3]
	ldr r5, [r4, #0x64]
	add r3, r5, #0
	mul r3, r2
	ldr r6, [r0, r3]
	ldr r5, _02236A54 ; =0xFFFFFBFF
	and r5, r6
	str r5, [r0, r3]
	add r3, r1, #0
	add r3, #0x60
	add r6, r4, r3
	ldr r3, [r4, #0x64]
	add r1, #0x70
	add r5, r3, #0
	mul r5, r2
	ldr r7, [r6, r5]
	ldr r3, _02236A58 ; =0xBFFFFFFF
	and r3, r7
	add r7, r2, #0
	add r7, #0x90
	ldr r7, [r4, r7]
	lsl r7, r7, #0x1f
	lsr r7, r7, #1
	orr r3, r7
	str r3, [r6, r5]
	add r3, r2, #0
	add r3, #0x90
	ldr r3, [r4, r3]
	add r6, r3, #1
	ldr r3, [r4, #0x64]
	add r5, r3, #0
	mul r5, r2
	add r3, r4, r5
	str r6, [r3, r1]
	ldr r1, [r4, #0x64]
	add r5, r1, #0
	mul r5, r2
	ldr r3, [r0, r5]
	mov r1, #0x40
	bic r3, r1
	str r3, [r0, r5]
	ldr r1, [r4, #0x64]
	mov r6, #0
	add r3, r1, #0
	mul r3, r2
	ldr r2, [r0, r3]
	mov r1, #0x80
	bic r2, r1
	str r2, [r0, r3]
	mov r0, #0xf9
	add r5, r6, #0
	mov r1, #5
	lsl r0, r0, #2
_02236A0E:
	ldr r3, [r4, #0x64]
	mov r2, #0xc0
	mul r2, r3
	add r3, r4, r2
	ldr r2, _02236A5C ; =0x00002D4C
	add r7, r3, r5
	ldrh r2, [r7, r2]
	lsl r2, r2, #4
	add r2, r4, r2
	ldrb r2, [r2, r0]
	cmp r2, #5
	bhs _02236A2E
	add r7, r3, r6
	ldr r3, _02236A60 ; =0x00002D6C
	strb r2, [r7, r3]
	b _02236A34
_02236A2E:
	ldr r2, _02236A60 ; =0x00002D6C
	add r3, r3, r6
	strb r1, [r3, r2]
_02236A34:
	add r6, r6, #1
	add r5, r5, #2
	cmp r6, #4
	blt _02236A0E
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02236A40: .word 0x00002DB0
_02236A44: .word 0xFFFFE3FF
_02236A48: .word 0x00002D68
_02236A4C: .word 0xFFFFFEFF
_02236A50: .word 0xFFFFFDFF
_02236A54: .word 0xFFFFFBFF
_02236A58: .word 0xBFFFFFFF
_02236A5C: .word 0x00002D4C
_02236A60: .word 0x00002D6C

	thumb_func_start ov11_02236A64
ov11_02236A64: ; 0x02236A64
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	ldr r1, [r4, #0x64]
	add r0, r5, #0
	bl ov11_02230270
	mov r2, #0x72
	mov r1, #1
	add r3, r0, #0
	eor r3, r1
	lsl r0, r3, #3
	add r5, r4, r0
	lsl r2, r2, #2
	ldr r5, [r5, r2]
	lsl r5, r5, #0x1e
	lsr r5, r5, #0x1e
	cmp r5, #3
	bne _02236ABA
	mov r0, #0xb5
	lsl r0, r0, #2
	add r2, r4, r0
	ldr r3, [r4, #0x64]
	mov r0, #0x1c
	mul r0, r3
	ldr r5, [r2, r0]
	mov r3, #1
	bic r5, r3
	orr r1, r5
	str r1, [r2, r0]
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
	b _02236AE2
_02236ABA:
	add r1, r2, #0
	sub r1, #0xc
	lsl r6, r3, #2
	add r1, r4, r1
	ldr r5, [r1, r6]
	mov r3, #4
	orr r3, r5
	str r3, [r1, r6]
	add r2, r4, r2
	ldr r4, [r2, r0]
	mov r3, #3
	add r1, r4, #0
	bic r1, r3
	lsl r3, r4, #0x1e
	lsr r3, r3, #0x1e
	add r4, r3, #1
	mov r3, #3
	and r3, r4
	orr r1, r3
	str r1, [r2, r0]
_02236AE2:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_02236AE8
ov11_02236AE8: ; 0x02236AE8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl ov11_0223C230
	add r4, r0, #0
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_02230270
	lsl r0, r0, #3
	add r1, r5, r0
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1e
	lsr r1, r0, #0x1e
	beq _02236B56
	mov r0, #0xc0
	mul r0, r4
	ldr r4, _02236B64 ; =0x00002D8C
	add r0, r5, r0
	ldr r2, [r0, r4]
	cmp r2, #0
	beq _02236B56
	mov r2, #5
	sub r1, r2, r1
	ldr r3, _02236B68 ; =0x0000215C
	lsl r1, r1, #1
	str r1, [r5, r3]
	add r1, r4, #4
	ldr r1, [r0, r1]
	sub r0, r2, #6
	mul r0, r1
	ldr r1, [r5, r3]
	bl ov11_022476C0
	ldr r1, _02236B68 ; =0x0000215C
	str r0, [r5, r1]
	b _02236B5E
_02236B56:
	add r0, r5, #0
	add r1, r7, #0
	bl ov11_0223A424
_02236B5E:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02236B64: .word 0x00002D8C
_02236B68: .word 0x0000215C

	thumb_func_start ov11_02236B6C
ov11_02236B6C: ; 0x02236B6C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	str r1, [sp]
	add r0, r1, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r0, [sp]
	bl ov11_0223A404
	str r0, [sp, #8]
	add r0, r4, #0
	bl ov11_0222FF84
	mov r2, #0x4d
	mov r7, #0
	str r0, [sp, #4]
	add r1, r0, #0
	ldr r0, [sp]
	lsl r2, r2, #2
	str r1, [r0, r2]
	ldr r0, [sp, #4]
	add r6, r7, #0
	cmp r0, #0
	ble _02236BFC
	ldr r4, [sp]
	ldr r1, _02236C10 ; =0x00002DC8
	add r0, r4, #0
	add r5, r0, r1
_02236BA8:
	mov r0, #0xb7
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r0, #0x20
	tst r0, r1
	bne _02236BCE
	ldr r0, _02236C14 ; =0x00002D8C
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02236BCE
	ldr r0, [sp]
	add r2, r6, #0
	add r1, r0, #0
	ldr r1, [r1, #0x64]
	mov r3, #0x2b
	bl ov11_02246D84
	cmp r0, #1
	bne _02236BD2
_02236BCE:
	add r7, r7, #1
	b _02236BF0
_02236BD2:
	mov r0, #0xb7
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r0, #0x20
	orr r1, r0
	mov r0, #0xb7
	lsl r0, r0, #6
	str r1, [r4, r0]
	ldr r1, [r5]
	ldr r0, _02236C18 ; =0xFFFF9FFF
	and r1, r0
	mov r0, #6
	lsl r0, r0, #0xc
	orr r0, r1
	str r0, [r5]
_02236BF0:
	ldr r0, [sp, #4]
	add r6, r6, #1
	add r4, #0xc0
	add r5, #0xc0
	cmp r6, r0
	blt _02236BA8
_02236BFC:
	ldr r0, [sp, #4]
	cmp r7, r0
	bne _02236C0A
	ldr r0, [sp]
	ldr r1, [sp, #8]
	bl ov11_0223A424
_02236C0A:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02236C10: .word 0x00002DC8
_02236C14: .word 0x00002D8C
_02236C18: .word 0xFFFF9FFF

	thumb_func_start ov11_02236C1C
ov11_02236C1C: ; 0x02236C1C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223A444
	ldr r1, _02236C4C ; =0x00003104
	ldr r1, [r4, r1]
	add r2, r4, r1
	ldr r1, _02236C50 ; =0x000021EC
	ldrb r1, [r2, r1]
	str r1, [r0]
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02236C4C: .word 0x00003104
_02236C50: .word 0x000021EC

	thumb_func_start ov11_02236C54
ov11_02236C54: ; 0x02236C54
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0223A444
	add r6, r0, #0
	add r0, r5, #0
	bl ov11_0222FF84
	ldr r1, [r6]
	cmp r1, r0
	bhs _02236C92
	add r0, r4, #0
	add r1, r7, #0
	bl ov11_0223A424
_02236C92:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_02236C98
ov11_02236C98: ; 0x02236C98
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_0223C230
	add r4, r0, #0
	mov r0, #0x4e
	mov r3, #0
	lsl r0, r0, #2
	str r3, [r5, r0]
	ldr r0, _02236F40 ; =0x0000215C
	add r1, r4, #0
	str r3, [r5, r0]
	add r0, r5, #0
	mov r2, #0x1b
	bl ov11_02243420
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x1c
	mov r3, #0
	bl ov11_02243420
	add r7, r0, #0
	mov r0, #0xd
	str r0, [sp]
	add r0, r6, #0
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl ov11_02246870
	cmp r0, #0
	bne _02236D08
	mov r0, #0x4c
	str r0, [sp]
	add r0, r6, #0
	add r1, r5, #0
	mov r2, #8
	mov r3, #0
	bl ov11_02246870
	cmp r0, #0
	beq _02236D0A
_02236D08:
	b _02236F38
_02236D0A:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #0xc
	tst r0, r1
	beq _02236D74
	ldr r0, [sp, #4]
	cmp r0, #5
	beq _02236D74
	cmp r7, #5
	beq _02236D74
	cmp r0, #8
	beq _02236D74
	cmp r7, #8
	beq _02236D74
	cmp r0, #4
	beq _02236D74
	cmp r7, #4
	beq _02236D74
	mov r0, #0xc0
	add r6, r4, #0
	mul r6, r0
	ldr r0, _02236F44 ; =0x00002D8C
	add r1, r5, r6
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02236D74
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02246D1C
	cmp r0, #8
	beq _02236D74
	mov r3, #0xb7
	add r1, r5, r6
	lsl r3, r3, #6
	ldr r2, [r1, r3]
	ldr r0, _02236F48 ; =0x00040080
	tst r0, r2
	bne _02236D74
	mov r0, #0xc9
	add r2, r0, #0
	add r2, #0x5b
	str r0, [r5, r2]
	sub r3, #0x30
	ldr r1, [r1, r3]
	sub r0, #0xca
	mul r0, r1
	mov r1, #0x10
	bl ov11_022476C0
	ldr r1, _02236F40 ; =0x0000215C
	str r0, [r5, r1]
_02236D74:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #0x30
	tst r0, r1
	beq _02236DDC
	mov r0, #0xc0
	add r6, r4, #0
	mul r6, r0
	ldr r0, _02236F44 ; =0x00002D8C
	add r2, r5, r6
	ldr r1, [r2, r0]
	cmp r1, #0
	beq _02236DDC
	add r0, #0x34
	ldr r1, [r2, r0]
	ldr r0, _02236F48 ; =0x00040080
	tst r0, r1
	bne _02236DDC
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x57
	beq _02236DB2
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x5e
	bne _02236DC8
_02236DB2:
	ldr r0, _02236F4C ; =0x00002D90
	add r1, r5, r6
	ldr r1, [r1, r0]
	mov r0, #0
	mvn r0, r0
	mul r0, r1
	mov r1, #8
	bl ov11_022476C0
	ldr r1, _02236F40 ; =0x0000215C
	str r0, [r5, r1]
_02236DC8:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x5e
	bne _02236DDC
	mov r0, #0x4e
	mov r1, #2
	lsl r0, r0, #2
	str r1, [r5, r0]
_02236DDC:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #0xc0
	tst r1, r0
	beq _02236E5E
	ldr r1, _02236F44 ; =0x00002D8C
	add r6, r4, #0
	mul r6, r0
	add r0, r5, r1
	str r0, [sp, #8]
	ldr r0, [r0, r6]
	cmp r0, #0
	beq _02236E5E
	add r0, r5, r6
	add r1, #0x34
	ldr r1, [r0, r1]
	ldr r0, _02236F48 ; =0x00040080
	tst r0, r1
	bne _02236E5E
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x73
	bne _02236E2A
	ldr r0, _02236F4C ; =0x00002D90
	add r1, r5, r6
	ldr r0, [r1, r0]
	ldr r1, [sp, #8]
	ldr r1, [r1, r6]
	cmp r1, r0
	bhs _02236E5E
	mov r1, #0x10
	bl ov11_022476C0
	ldr r1, _02236F40 ; =0x0000215C
	str r0, [r5, r1]
	b _02236E5E
_02236E2A:
	ldr r0, [sp, #4]
	cmp r0, #0xf
	beq _02236E5E
	cmp r7, #0xf
	beq _02236E5E
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x51
	beq _02236E5E
	ldr r1, _02236F50 ; =0x00000102
	add r0, r1, #0
	add r0, #0x22
	str r1, [r5, r0]
	ldr r0, _02236F4C ; =0x00002D90
	add r1, r5, r6
	ldr r1, [r1, r0]
	mov r0, #0
	mvn r0, r0
	mul r0, r1
	mov r1, #0x10
	bl ov11_022476C0
	ldr r1, _02236F40 ; =0x0000215C
	str r0, [r5, r1]
_02236E5E:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r5, r0]
	mov r0, #3
	tst r0, r1
	beq _02236F38
	ldr r1, _02236F44 ; =0x00002D8C
	mov r0, #0xc0
	add r6, r4, #0
	mul r6, r0
	add r7, r5, r1
	ldr r0, [r7, r6]
	cmp r0, #0
	beq _02236EA0
	add r1, r1, #4
	add r1, r5, r1
	str r1, [sp, #0xc]
	ldr r1, [r1, r6]
	cmp r0, r1
	bhs _02236EA0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x2c
	bne _02236EA0
	ldr r0, [sp, #0xc]
	mov r1, #0x10
	ldr r0, [r0, r6]
	bl ov11_022476C0
	ldr r1, _02236F40 ; =0x0000215C
	str r0, [r5, r1]
_02236EA0:
	ldr r0, [r7, r6]
	cmp r0, #0
	beq _02236ECC
	ldr r1, _02236F4C ; =0x00002D90
	add r1, r5, r1
	str r1, [sp, #0x10]
	ldr r1, [r1, r6]
	cmp r0, r1
	bhs _02236ECC
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x57
	bne _02236ECC
	ldr r0, [sp, #0x10]
	mov r1, #8
	ldr r0, [r0, r6]
	bl ov11_022476C0
	ldr r1, _02236F40 ; =0x0000215C
	str r0, [r5, r1]
_02236ECC:
	ldr r0, [r7, r6]
	cmp r0, #0
	beq _02236F38
	ldr r0, _02236F54 ; =0x00002DAC
	add r7, r5, r0
	ldr r0, [r7, r6]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	beq _02236F38
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02246D1C
	cmp r0, #0x5d
	bne _02236F38
	ldr r0, [r7, r6]
	mov r1, #7
	tst r1, r0
	beq _02236EFC
	mov r0, #0x13
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02236F30
_02236EFC:
	ldr r1, _02236F58 ; =0x00000F88
	tst r1, r0
	beq _02236F0C
	mov r0, #0x13
	mov r1, #1
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02236F30
_02236F0C:
	mov r1, #0x10
	tst r1, r0
	beq _02236F1C
	mov r0, #0x13
	mov r1, #2
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _02236F30
_02236F1C:
	mov r1, #0x40
	tst r0, r1
	beq _02236F2A
	mov r0, #3
	add r1, #0xf0
	str r0, [r5, r1]
	b _02236F30
_02236F2A:
	mov r0, #4
	add r1, #0xf0
	str r0, [r5, r1]
_02236F30:
	mov r0, #0x4e
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r5, r0]
_02236F38:
	mov r0, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_02236F40: .word 0x0000215C
_02236F44: .word 0x00002D8C
_02236F48: .word 0x00040080
_02236F4C: .word 0x00002D90
_02236F50: .word 0x00000102
_02236F54: .word 0x00002DAC
_02236F58: .word 0x00000F88

	thumb_func_start ov11_02236F5C
ov11_02236F5C: ; 0x02236F5C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r6, [r4, #0x64]
	mov r0, #0xb5
	lsl r0, r0, #2
	add r2, r4, r0
	mov r0, #0x1c
	add r1, r6, #0
	mul r1, r0
	ldr r3, [r2, r1]
	ldr r0, _0223705C ; =0xFFFFFE3F
	mov r7, #0xc0
	and r0, r3
	add r3, r6, #0
	mul r3, r7
	add r6, r4, r3
	ldr r3, _02237060 ; =0x00002DC8
	ldr r6, [r6, r3]
	sub r3, #0x18
	lsl r6, r6, #0xe
	lsr r6, r6, #0x1d
	lsl r6, r6, #0x1d
	lsr r6, r6, #0x17
	orr r0, r6
	str r0, [r2, r1]
	ldr r2, [r4, #0x64]
	add r0, r2, #0
	mul r0, r7
	add r0, r4, r0
	ldr r1, [r0, r3]
	mov r0, #1
	lsl r0, r0, #0xc
	tst r0, r1
	bne _02236FCA
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_022451C0
	ldr r0, _02237060 ; =0x00002DC8
	ldr r2, [r4, #0x64]
	add r1, r4, r0
	add r0, r7, #0
	mul r0, r2
	ldr r3, [r1, r0]
	ldr r2, _02237064 ; =0xFFFC7FFF
	and r3, r2
	mov r2, #0xa
	lsl r2, r2, #0xe
	orr r2, r3
	str r2, [r1, r0]
_02236FCA:
	ldr r1, [r4, #0x64]
	ldr r0, _02237060 ; =0x00002DC8
	mov r7, #0xc0
	add r3, r1, #0
	add r6, r4, r0
	mul r3, r7
	ldr r1, [r6, r3]
	ldr r2, _02237064 ; =0xFFFC7FFF
	and r2, r1
	lsl r1, r1, #0xe
	lsr r1, r1, #0x1d
	sub r1, r1, #1
	lsl r1, r1, #0x1d
	lsr r1, r1, #0xe
	orr r1, r2
	str r1, [r6, r3]
	ldr r2, [r4, #0x64]
	add r1, r2, #0
	mul r1, r7
	add r1, r4, r1
	ldr r0, [r1, r0]
	lsl r0, r0, #0xe
	lsr r0, r0, #0x1d
	bne _02237002
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_022451F0
_02237002:
	ldr r0, _02237068 ; =0x00003044
	mov r2, #1
	ldr r0, [r4, r0]
	lsl r0, r0, #4
	add r1, r4, r0
	ldr r0, _0223706C ; =0x000003E1
	ldrb r1, [r1, r0]
	ldr r0, _02237070 ; =0x00002154
	str r1, [r4, r0]
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _02237060 ; =0x00002DC8
	ldr r0, [r1, r0]
	lsl r0, r0, #0xe
	lsr r1, r0, #0x1d
	mov r0, #5
	sub r3, r0, r1
	cmp r3, #1
	ble _0223703A
	ldr r0, _02237070 ; =0x00002154
_0223702E:
	ldr r1, [r4, r0]
	add r2, r2, #1
	lsl r1, r1, #1
	str r1, [r4, r0]
	cmp r2, r3
	blt _0223702E
_0223703A:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _02237074 ; =0x00002DB0
	ldr r1, [r1, r0]
	mov r0, #1
	lsl r0, r0, #0x1e
	tst r0, r1
	beq _02237056
	ldr r0, _02237070 ; =0x00002154
	ldr r1, [r4, r0]
	lsl r1, r1, #1
	str r1, [r4, r0]
_02237056:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223705C: .word 0xFFFFFE3F
_02237060: .word 0x00002DC8
_02237064: .word 0xFFFC7FFF
_02237068: .word 0x00003044
_0223706C: .word 0x000003E1
_02237070: .word 0x00002154
_02237074: .word 0x00002DB0

	thumb_func_start ov11_02237078
ov11_02237078: ; 0x02237078
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r2, [r4, #0x64]
	mov r0, #0xc0
	add r1, r2, #0
	mul r1, r0
	ldr r0, _022370F4 ; =0x00002DC8
	add r0, r4, r0
	ldr r3, [r0, r1]
	lsl r2, r3, #0xb
	lsr r5, r2, #0x1d
	cmp r5, #5
	bhs _022370A8
	ldr r2, _022370F8 ; =0xFFE3FFFF
	and r3, r2
	add r2, r5, #1
	lsl r2, r2, #0x1d
	lsr r2, r2, #0xb
	orr r2, r3
	str r2, [r0, r1]
_022370A8:
	ldr r0, _022370FC ; =0x00003044
	ldr r0, [r4, r0]
	lsl r0, r0, #4
	add r1, r4, r0
	ldr r0, _02237100 ; =0x000003E1
	ldrb r1, [r1, r0]
	ldr r0, _02237104 ; =0x00002154
	str r1, [r4, r0]
	ldr r2, [r4, #0x64]
	mov r1, #0xc0
	mul r1, r2
	add r2, r4, r1
	ldr r1, _022370F4 ; =0x00002DC8
	mov r0, #1
	ldr r1, [r2, r1]
	lsl r1, r1, #0xb
	lsr r1, r1, #0x1d
	cmp r1, #1
	bls _022370EE
	ldr r3, _02237104 ; =0x00002154
	ldr r2, _022370F4 ; =0x00002DC8
	mov r1, #0xc0
_022370D4:
	ldr r5, [r4, r3]
	add r0, r0, #1
	lsl r5, r5, #1
	str r5, [r4, r3]
	ldr r5, [r4, #0x64]
	add r6, r5, #0
	mul r6, r1
	add r5, r4, r6
	ldr r5, [r5, r2]
	lsl r5, r5, #0xb
	lsr r5, r5, #0x1d
	cmp r0, r5
	blo _022370D4
_022370EE:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_022370F4: .word 0x00002DC8
_022370F8: .word 0xFFE3FFFF
_022370FC: .word 0x00003044
_02237100: .word 0x000003E1
_02237104: .word 0x00002154

	thumb_func_start ov11_02237108
ov11_02237108: ; 0x02237108
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r3, r0, #0
	add r0, r4, #0
	add r0, #0x94
	ldr r0, [r0]
	mov r5, #0xc0
	add r1, r0, #0
	mul r1, r5
	ldr r6, _02237184 ; =0x00002DBE
	add r1, r4, r1
	ldrb r0, [r1, r6]
	lsl r0, r0, #0x1c
	lsr r2, r0, #0x1c
	add r0, r5, #0
	add r0, #0x58
	ldr r0, [r4, r0]
	mul r5, r0
	add r5, r4, r5
	ldrb r5, [r5, r6]
	lsl r5, r5, #0x1c
	lsr r5, r5, #0x1c
	cmp r5, r2
	beq _0223715A
	sub r6, #0xe
	ldr r6, [r1, r6]
	mov r1, #0xf
	lsl r1, r1, #0x10
	tst r1, r6
	bne _0223715A
	cmp r5, #2
	beq _0223715A
	cmp r2, #2
	bne _02237164
_0223715A:
	add r0, r4, #0
	add r1, r3, #0
	bl ov11_0223A424
	b _0223717E
_02237164:
	bl MaskOfFlagNo
	ldr r1, _02237188 ; =0x00002DB0
	mov r2, #0xc0
	add r1, r4, r1
	add r4, #0x94
	ldr r3, [r4]
	lsl r0, r0, #0x10
	add r4, r3, #0
	mul r4, r2
	ldr r2, [r1, r4]
	orr r0, r2
	str r0, [r1, r4]
_0223717E:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_02237184: .word 0x00002DBE
_02237188: .word 0x00002DB0

	thumb_func_start ov11_0223718C
ov11_0223718C: ; 0x0223718C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	ldr r1, [r4, #0x64]
	add r0, r5, #0
	bl ov11_02230270
	mov r5, #0x6f
	add r2, r0, #0
	lsl r5, r5, #2
	add r1, r4, r5
	lsl r0, r2, #2
	ldr r6, [r1, r0]
	mov r3, #8
	tst r3, r6
	beq _022371D0
	add r0, r4, #0
	add r1, r7, #0
	bl ov11_0223A424
	ldr r1, _02237214 ; =0x0000216C
	mov r0, #0x40
	ldr r2, [r4, r1]
	orr r0, r2
	str r0, [r4, r1]
	b _02237210
_022371D0:
	mov r3, #8
	orr r3, r6
	str r3, [r1, r0]
	add r5, #8
	lsl r0, r2, #3
	add r1, r4, r5
	ldr r3, [r1, r0]
	ldr r2, _02237218 ; =0xFFF1FFFF
	and r3, r2
	mov r2, #0xa
	lsl r2, r2, #0x10
	orr r2, r3
	str r2, [r1, r0]
	ldr r3, [r1, r0]
	ldr r2, _0223721C ; =0xFFFE7FFF
	and r3, r2
	ldr r2, [r4, #0x64]
	lsl r2, r2, #0x1e
	lsr r2, r2, #0xf
	orr r2, r3
	str r2, [r1, r0]
	add r0, r4, #0
	mov r1, #1
	add r0, #0xf5
	strb r1, [r0]
	add r0, r4, #0
	ldr r1, [r4, #0x64]
	add r0, #0xf8
	str r1, [r0]
	mov r0, #0xc6
	add r4, #0xf6
	strh r0, [r4]
_02237210:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02237214: .word 0x0000216C
_02237218: .word 0xFFF1FFFF
_0223721C: .word 0xFFFE7FFF

	thumb_func_start ov11_02237220
ov11_02237220: ; 0x02237220
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	bl LCRandom
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x66
	bge _02237248
	ldr r0, _02237284 ; =0x00002154
	mov r1, #0x28
	str r1, [r5, r0]
	b _0223727E
_02237248:
	cmp r0, #0xb2
	bge _02237254
	ldr r0, _02237284 ; =0x00002154
	mov r1, #0x50
	str r1, [r5, r0]
	b _0223727E
_02237254:
	cmp r0, #0xcc
	bge _02237260
	ldr r0, _02237284 ; =0x00002154
	mov r1, #0x78
	str r1, [r5, r0]
	b _0223727E
_02237260:
	ldr r1, [r5, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _02237288 ; =0x00002D90
	ldr r0, [r1, r0]
	mov r1, #4
	bl ov11_022476C0
	ldr r1, _0223728C ; =0x0000215C
	str r0, [r5, r1]
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223A424
_0223727E:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02237284: .word 0x00002154
_02237288: .word 0x00002D90
_0223728C: .word 0x0000215C

	thumb_func_start ov11_02237290
ov11_02237290: ; 0x02237290
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r0, _0223732C ; =0x00003120
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _0223731C
	bl LCRandom
	mov r1, #0x64
	bl _s32_div_f
	ldr r0, _0223732C ; =0x00003120
	strb r1, [r4, r0]
	ldrb r1, [r4, r0]
	cmp r1, #5
	bhs _022372C4
	ldr r1, _02237330 ; =0x00002154
	mov r2, #0xa
	str r2, [r4, r1]
	mov r1, #4
	strb r1, [r4, r0]
	b _0223731C
_022372C4:
	cmp r1, #0xf
	bhs _022372D4
	ldr r1, _02237330 ; =0x00002154
	mov r2, #0x1e
	str r2, [r4, r1]
	mov r1, #5
	strb r1, [r4, r0]
	b _0223731C
_022372D4:
	cmp r1, #0x23
	bhs _022372E4
	ldr r1, _02237330 ; =0x00002154
	mov r2, #0x32
	str r2, [r4, r1]
	mov r1, #6
	strb r1, [r4, r0]
	b _0223731C
_022372E4:
	cmp r1, #0x41
	bhs _022372F4
	ldr r1, _02237330 ; =0x00002154
	mov r2, #0x46
	str r2, [r4, r1]
	mov r1, #7
	strb r1, [r4, r0]
	b _0223731C
_022372F4:
	cmp r1, #0x55
	bhs _02237304
	ldr r1, _02237330 ; =0x00002154
	mov r2, #0x5a
	str r2, [r4, r1]
	mov r1, #8
	strb r1, [r4, r0]
	b _0223731C
_02237304:
	cmp r1, #0x5f
	ldr r1, _02237330 ; =0x00002154
	bhs _02237314
	mov r2, #0x6e
	str r2, [r4, r1]
	mov r1, #9
	strb r1, [r4, r0]
	b _0223731C
_02237314:
	mov r2, #0x96
	str r2, [r4, r1]
	mov r1, #0xa
	strb r1, [r4, r0]
_0223731C:
	ldr r0, _0223732C ; =0x00003120
	ldrb r1, [r4, r0]
	mov r0, #0x13
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #0
	pop {r4, pc}
	nop
_0223732C: .word 0x00003120
_02237330: .word 0x00002154

	thumb_func_start ov11_02237334
ov11_02237334: ; 0x02237334
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	str r0, [sp]
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl ov11_0223C230
	add r4, r0, #0
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl ov11_02246DE0
	cmp r0, #0
	bne _0223737E
	ldr r1, [sp]
	add r0, r5, #0
	bl ov11_0223A424
	b _02237392
_0223737E:
	cmp r7, #1
	bne _02237392
	mov r0, #0x4f
	lsl r0, r0, #2
	add r3, r5, r0
	lsl r2, r4, #2
	ldr r1, [r3, r2]
	mov r0, #1
	orr r0, r1
	str r0, [r3, r2]
_02237392:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_02237398
ov11_02237398: ; 0x02237398
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	ldr r1, [r4, #0x64]
	bl ov11_02230270
	ldr r1, [r4, #0x64]
	mov r6, #0xe
	ldr r5, _022374D4 ; =0x00002DB0
	add r2, r1, #0
	mov r3, #0xc0
	mul r2, r3
	add r1, r4, r5
	ldr r7, [r1, r2]
	lsl r6, r6, #0xc
	tst r6, r7
	beq _022373F4
	ldr r0, _022374D8 ; =0xFFFF1FFF
	and r0, r7
	str r0, [r1, r2]
	ldr r0, [r4, #0x64]
	mov r2, #0x74
	add r1, r0, #0
	add r0, r5, #0
	mul r1, r3
	add r1, r4, r1
	add r0, #0x1c
	ldr r0, [r1, r0]
	add r5, #0x3a
	lsl r0, r0, #0x18
	lsr r1, r0, #0x1e
	add r0, r3, #0
	add r0, #0x58
	str r1, [r4, r0]
	ldr r0, [r4, #0x64]
	add r1, r0, #0
	mul r1, r3
	add r0, r4, r1
	ldrh r0, [r0, r5]
	add r3, #0x64
	mov r1, #1
	str r0, [r4, r3]
	add r0, r4, #0
	bl ov11_0223A43C
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_022373F4:
	add r5, #0x10
	add r5, r4, r5
	ldr r1, [r5, r2]
	mov r6, #4
	tst r6, r1
	beq _0223742A
	mov r0, #4
	bic r1, r0
	str r1, [r5, r2]
	ldr r0, [r4, #0x64]
	add r2, r0, #0
	mul r2, r3
	ldr r1, [r5, r2]
	mov r0, #3
	bic r1, r0
	str r1, [r5, r2]
	mov r1, #0x49
	add r0, r1, #0
	add r0, #0xdb
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x75
	bl ov11_0223A43C
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223742A:
	mov r1, #0x72
	lsl r1, r1, #2
	add r6, r4, r1
	lsl r5, r0, #3
	ldr r2, [r6, r5]
	lsl r3, r2, #0x1e
	lsr r3, r3, #0x1e
	beq _02237466
	sub r1, #0xc
	lsl r3, r0, #2
	add r1, r4, r1
	ldr r2, [r1, r3]
	mov r0, #4
	bic r2, r0
	str r2, [r1, r3]
	ldr r1, [r6, r5]
	mov r0, #3
	bic r1, r0
	str r1, [r6, r5]
	mov r1, #0xbf
	add r0, r1, #0
	add r0, #0x65
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x75
	bl ov11_0223A43C
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02237466:
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x1e
	beq _0223749A
	add r2, r1, #0
	sub r2, #0xc
	lsl r7, r0, #2
	add r3, r4, r2
	ldr r2, [r3, r7]
	ldr r0, _022374DC ; =0xFFFFFBFF
	and r0, r2
	str r0, [r3, r7]
	ldr r2, [r6, r5]
	mov r0, #0xc
	bic r2, r0
	add r0, r1, #0
	str r2, [r6, r5]
	sub r0, #0x42
	sub r1, #0xa4
	str r0, [r4, r1]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x75
	bl ov11_0223A43C
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223749A:
	add r2, r1, #0
	sub r2, #0xc
	add r2, r4, r2
	lsl r0, r0, #2
	ldr r6, [r2, r0]
	mov r5, #0x80
	add r3, r6, #0
	tst r3, r5
	beq _022374C6
	mov r3, #0x80
	bic r6, r3
	str r6, [r2, r0]
	sub r1, #0xa
	add r5, #0xa4
	str r1, [r4, r5]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x75
	bl ov11_0223A43C
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_022374C6:
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022374D4: .word 0x00002DB0
_022374D8: .word 0xFFFF1FFF
_022374DC: .word 0xFFFFFBFF

	thumb_func_start ov11_022374E0
ov11_022374E0: ; 0x022374E0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	ldr r0, _02237578 ; =0x000080FF
	tst r0, r1
	beq _02237522
	mov r0, #0xd
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #8
	mov r3, #0
	bl ov11_02246870
	cmp r0, #0
	bne _02237522
	mov r0, #0x4c
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #8
	mov r3, #0
	bl ov11_02246870
	cmp r0, #0
	beq _02237536
_02237522:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0223757C ; =0x00002D90
	ldr r0, [r1, r0]
	lsr r1, r0, #1
	ldr r0, _02237580 ; =0x0000215C
	str r1, [r4, r0]
	b _02237572
_02237536:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r0, #0x30
	tst r0, r1
	ldr r1, [r4, #0x64]
	beq _0223755E
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0223757C ; =0x00002D90
	ldr r1, [r1, r0]
	mov r0, #0x14
	mul r0, r1
	mov r1, #0x1e
	bl ov11_022476C0
	ldr r1, _02237580 ; =0x0000215C
	str r0, [r4, r1]
	b _02237572
_0223755E:
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0223757C ; =0x00002D90
	ldr r0, [r1, r0]
	mov r1, #4
	bl ov11_022476C0
	ldr r1, _02237580 ; =0x0000215C
	str r0, [r4, r1]
_02237572:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02237578: .word 0x000080FF
_0223757C: .word 0x00002D90
_02237580: .word 0x0000215C

	thumb_func_start ov11_02237584
ov11_02237584: ; 0x02237584
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r0, _02237664 ; =0x00002D54
	ldr r1, [r4, #0x64]
	add r3, r4, r0
	mov r0, #0xc0
	mul r0, r1
	ldr r1, [r3, r0]
	mov r5, #2
	lsl r0, r1, #2
	lsr r0, r0, #0x1b
	and r0, r5
	lsl r2, r0, #4
	lsl r0, r1, #7
	lsr r0, r0, #0x1b
	and r0, r5
	lsl r7, r0, #3
	lsl r0, r1, #0xc
	lsr r0, r0, #0x1b
	and r0, r5
	lsl r0, r0, #2
	mov ip, r0
	lsl r0, r1, #0x11
	lsr r0, r0, #0x1b
	and r0, r5
	lsl r6, r0, #1
	lsl r0, r1, #0x1b
	lsr r0, r0, #0x1b
	lsl r1, r1, #0x16
	and r0, r5
	lsr r1, r1, #0x1b
	lsr r0, r0, #1
	and r1, r5
	orr r0, r1
	add r1, r6, #0
	orr r1, r0
	mov r0, ip
	orr r0, r1
	orr r0, r7
	add r1, r2, #0
	orr r1, r0
	ldr r0, _02237668 ; =0x00002154
	str r1, [r4, r0]
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	ldr r5, [r3, r0]
	lsl r0, r5, #2
	lsr r0, r0, #0x1b
	lsl r0, r0, #0x1f
	lsr r6, r0, #0x1a
	lsl r0, r5, #7
	lsr r0, r0, #0x1b
	lsl r0, r0, #0x1f
	lsr r3, r0, #0x1b
	lsl r0, r5, #0xc
	lsr r0, r0, #0x1b
	lsl r0, r0, #0x1f
	lsr r2, r0, #0x1c
	lsl r0, r5, #0x11
	lsr r0, r0, #0x1b
	lsl r0, r0, #0x1f
	lsr r7, r0, #0x1d
	lsl r0, r5, #0x1b
	lsr r1, r0, #0x1b
	mov r0, #1
	and r0, r1
	lsl r1, r5, #0x16
	lsr r1, r1, #0x1b
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1e
	orr r0, r1
	orr r0, r7
	orr r0, r2
	orr r0, r3
	add r1, r6, #0
	orr r1, r0
	ldr r0, _02237668 ; =0x00002154
	add r0, #0xc
	str r1, [r4, r0]
	ldr r0, _02237668 ; =0x00002154
	ldr r1, [r4, r0]
	mov r0, #0x28
	mul r0, r1
	mov r1, #0x3f
	bl _s32_div_f
	ldr r1, _02237668 ; =0x00002154
	add r0, #0x1e
	str r0, [r4, r1]
	add r1, #0xc
	ldr r1, [r4, r1]
	mov r0, #0xf
	mul r0, r1
	mov r1, #0x3f
	bl _s32_div_f
	add r1, r0, #1
	ldr r0, _0223766C ; =0x00002160
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #9
	blt _0223765E
	add r1, r1, #1
	str r1, [r4, r0]
_0223765E:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02237664: .word 0x00002D54
_02237668: .word 0x00002154
_0223766C: .word 0x00002160

	thumb_func_start ov11_02237670
ov11_02237670: ; 0x02237670
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r2, _022376C8 ; =0x00002D58
	mov r1, #0
	mov r3, #0xc0
	add r5, r2, #0
_02237684:
	ldr r6, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r6
	ldr r6, [r4, #0x64]
	add r0, r4, r0
	add r0, r1, r0
	add r7, r6, #0
	mul r7, r3
	add r6, r4, r7
	add r6, r1, r6
	ldrsb r0, [r0, r2]
	add r1, r1, #1
	cmp r1, #8
	strb r0, [r6, r5]
	blt _02237684
	ldr r0, [r4, #0x64]
	ldr r6, [r4, #0x6c]
	mov r3, #0xc0
	add r1, r0, #0
	ldr r5, _022376CC ; =0x00002DB0
	mul r1, r3
	mul r3, r6
	add r2, r4, r5
	add r3, r4, r3
	ldr r4, [r3, r5]
	mov r3, #1
	lsl r3, r3, #0x14
	ldr r0, [r2, r1]
	and r3, r4
	orr r0, r3
	str r0, [r2, r1]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022376C8: .word 0x00002D58
_022376CC: .word 0x00002DB0

	thumb_func_start ov11_022376D0
ov11_022376D0: ; 0x022376D0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	ldr r1, [r4, #0x6c]
	add r2, r0, #0
	mov r0, #0x62
	add r3, r4, r1
	lsl r0, r0, #2
	ldrb r0, [r3, r0]
	cmp r0, #0
	bne _022377A4
	add r0, r5, #0
	bl ov11_02230270
	mov r1, #0x6f
	lsl r1, r1, #2
	lsl r3, r0, #2
	add r6, r4, r1
	add r7, r1, #0
	ldr r2, [r6, r3]
	mov r0, #0x10
	orr r0, r2
	str r0, [r6, r3]
	ldr r0, [r4, #0x6c]
	sub r7, #0x34
	add r2, r4, r0
	mov r0, #3
	strb r0, [r2, r7]
	add r7, r1, #0
	ldr r0, _022377B4 ; =0x00003044
	sub r7, #0x2c
	ldr r2, [r4, r0]
	ldr r0, [r4, #0x6c]
	sub r1, #0x24
	lsl r0, r0, #1
	add r0, r4, r0
	strh r2, [r0, r7]
	ldr r2, [r4, #0x6c]
	ldr r0, [r4, #0x64]
	lsl r2, r2, #2
	add r2, r4, r2
	str r0, [r2, r1]
	mov r0, #3
	lsl r0, r0, #7
	ldr r0, [r4, r0]
	ldr r2, _022377B4 ; =0x00003044
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4, #0x64]
	add r1, r4, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x6c]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	ldr r2, [r4, r2]
	ldr r3, [r6, r3]
	add r0, r5, #0
	bl ov11_0224B310
	mov r1, #0
	mvn r1, r1
	mul r1, r0
	add r0, r4, #0
	bl ov11_0224BF10
	ldr r1, [r4, #0x6c]
	lsl r1, r1, #2
	add r2, r4, r1
	mov r1, #0x6a
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4, #0x64]
	lsl r0, r0, #6
	add r2, r4, r0
	add r0, r1, #0
	add r0, #0x2c
	ldr r0, [r2, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	beq _022377AC
	ldr r0, [r4, #0x6c]
	add r5, r4, r1
	lsl r4, r0, #2
	ldr r1, [r5, r4]
	mov r0, #0xf
	mul r0, r1
	mov r1, #0xa
	bl _s32_div_f
	str r0, [r5, r4]
	b _022377AC
_022377A4:
	add r0, r4, #0
	add r1, r2, #0
	bl ov11_0223A424
_022377AC:
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022377B4: .word 0x00003044

	thumb_func_start ov11_022377B8
ov11_022377B8: ; 0x022377B8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp, #4]
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0223C230
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r1, r4, #0
	add r2, r7, #0
	bl ov11_0223C230
	add r6, r0, #0
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl ov11_0223CC8C
	str r0, [sp]
	ldr r2, [sp, #0xc]
	add r0, r5, #0
	add r1, r4, #0
	add r3, r6, #0
	bl ov11_0223D29C
	ldr r0, _02237830 ; =0x0000216C
	ldr r1, [r4, r0]
	ldr r0, _02237834 ; =0x001FD849
	tst r0, r1
	beq _02237828
	ldr r1, [sp, #8]
	add r0, r4, #0
	bl ov11_0223A424
_02237828:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02237830: .word 0x0000216C
_02237834: .word 0x001FD849

	thumb_func_start ov11_02237838
ov11_02237838: ; 0x02237838
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	ldr r2, [r4, #0x64]
	add r0, r5, #0
	add r1, r4, #0
	mov r3, #0
	bl ov11_02246ED0
	cmp r0, #0
	beq _02237866
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
_02237866:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_0223786C
ov11_0223786C: ; 0x0223786C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r1, [r5, #0x64]
	add r0, r7, #0
	bl ov11_0222FFC8
	ldr r1, _02237AA0 ; =0x0000217D
	str r0, [sp]
	ldrb r0, [r5, r1]
	cmp r0, #0
	bne _02237900
	mov r0, #2
	strb r0, [r5, r1]
	add r0, r1, #0
	mov r2, #0xfd
	add r0, #0xb
	str r2, [r5, r0]
	mov r2, #0
	add r0, r1, #2
	strb r2, [r5, r0]
	add r6, r1, #2
_022378A2:
	ldr r2, _02237AA4 ; =0x0000217F
	ldr r1, [r5, #0x64]
	ldrb r2, [r5, r2]
	add r0, r7, #0
	bl ov11_02230014
	ldr r1, _02237AA4 ; =0x0000217F
	add r4, r0, #0
	ldrb r3, [r5, r1]
	ldr r1, [r5, #0x64]
	add r2, r5, r1
	ldr r1, _02237AA8 ; =0x0000219C
	ldrb r1, [r2, r1]
	cmp r3, r1
	beq _02237900
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _022378F8
	add r0, r4, #0
	mov r1, #0xad
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _022378F8
	add r0, r4, #0
	mov r1, #0xad
	mov r2, #0
	bl GetMonData
	ldr r1, _02237AAC ; =0x000001EE
	cmp r0, r1
	beq _022378F8
	add r0, r4, #0
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _02237900
_022378F8:
	ldrb r0, [r5, r6]
	add r0, r0, #1
	strb r0, [r5, r6]
	b _022378A2
_02237900:
	ldr r2, _02237AA4 ; =0x0000217F
	ldr r1, [r5, #0x64]
	ldrb r2, [r5, r2]
	add r0, r7, #0
	bl ov11_02230014
	add r4, r0, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0x70
	mov r2, #0
	bl GetMonData
	add r6, r0, #0
	add r0, r4, #0
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	add r4, r0, #0
	ldr r0, [sp, #4]
	add r1, r6, #0
	mov r2, #1 ; BASE_ATK
	bl GetMonBaseStat_HandleFormConversion
	ldr r1, _02237AB0 ; =0x00002144
	ldr r2, _02237AB4 ; =0x00003044
	str r0, [r5, r1]
	ldr r2, [r5, r2]
	ldr r0, [r5, r1]
	lsl r2, r2, #4
	add r3, r5, r2
	ldr r2, _02237AB8 ; =0x000003E1
	ldrb r2, [r3, r2]
	mul r2, r0
	str r2, [r5, r1]
	lsl r0, r4, #1
	mov r1, #5
	bl _s32_div_f
	ldr r1, _02237AB0 ; =0x00002144
	add r0, r0, #2
	ldr r2, [r5, r1]
	mul r0, r2
	str r0, [r5, r1]
	ldr r1, [r5, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	mov r1, #0xb5
	add r2, r5, r0
	lsl r1, r1, #6
	ldrh r0, [r2, r1]
	add r1, #0x26
	ldrb r1, [r2, r1]
	mov r2, #2 ; BASE_DEF
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x1b
	bl GetMonBaseStat_HandleFormConversion
	add r1, r0, #0
	ldr r0, _02237AB0 ; =0x00002144
	ldr r0, [r5, r0]
	bl _u32_div_f
	ldr r1, _02237AB0 ; =0x00002144
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	mov r1, #0x32
	bl _s32_div_f
	ldr r1, _02237AB0 ; =0x00002144
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	add r0, r0, #2
	str r0, [r5, r1]
	add r0, r1, #0
	add r0, #0xc
	ldr r2, [r5, r1]
	ldr r0, [r5, r0]
	mul r0, r2
	str r0, [r5, r1]
	ldr r0, [r5, #0x64]
	lsl r0, r0, #6
	add r2, r5, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r2, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	beq _022379CC
	ldr r1, [r5, r1]
	mov r0, #0xf
	mul r0, r1
	mov r1, #0xa
	bl _s32_div_f
	ldr r1, _02237AB0 ; =0x00002144
	str r0, [r5, r1]
_022379CC:
	ldr r1, _02237AB0 ; =0x00002144
	add r0, r5, #0
	ldr r1, [r5, r1]
	bl ov11_0224BF10
	ldr r1, _02237AB0 ; =0x00002144
	str r0, [r5, r1]
	mov r0, #0
	ldr r2, [r5, r1]
	mvn r0, r0
	mul r0, r2
	str r0, [r5, r1]
	add r0, r5, #0
	add r3, r1, #0
	ldr r2, _02237ABC ; =0x000001E1
	add r0, #0xf6
	strh r2, [r0]
	add r0, r5, #0
	mov r2, #2
	add r0, #0xf5
	strb r2, [r0]
	add r3, #0x3b
	ldrb r3, [r5, r3]
	ldr r0, [r5, #0x64]
	add r6, r1, #0
	lsl r3, r3, #8
	orr r3, r0
	add r0, r5, #0
	add r0, #0xf8
	str r3, [r0]
	add r0, r1, #0
	add r0, #0x3b
	ldrb r0, [r5, r0]
	add r6, #0x3b
	add r3, r0, #1
	add r0, r1, #0
	add r0, #0x3b
	strb r3, [r5, r0]
	add r0, r1, #0
	add r0, #0x38
	strb r2, [r5, r0]
	add r0, r1, #0
	add r0, #0x3b
	ldrb r2, [r5, r0]
	ldr r0, [sp]
	cmp r2, r0
	bge _02237A94
_02237A2A:
	ldr r1, [r5, #0x64]
	add r0, r7, #0
	bl ov11_02230014
	ldr r1, _02237AA4 ; =0x0000217F
	add r4, r0, #0
	ldrb r3, [r5, r1]
	ldr r1, [r5, #0x64]
	add r2, r5, r1
	ldr r1, _02237AA8 ; =0x0000219C
	ldrb r1, [r2, r1]
	cmp r3, r1
	beq _02237A9A
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _02237A7C
	add r0, r4, #0
	mov r1, #0xad
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _02237A7C
	add r0, r4, #0
	mov r1, #0xad
	mov r2, #0
	bl GetMonData
	ldr r1, _02237AAC ; =0x000001EE
	cmp r0, r1
	beq _02237A7C
	add r0, r4, #0
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _02237A9A
_02237A7C:
	ldrb r0, [r5, r6]
	add r0, r0, #1
	strb r0, [r5, r6]
	ldr r0, _02237AA4 ; =0x0000217F
	ldrb r2, [r5, r0]
	ldr r0, [sp]
	cmp r2, r0
	blt _02237A2A
	ldr r0, _02237AC0 ; =0x0000217C
	mov r1, #1
	strb r1, [r5, r0]
	b _02237A9A
_02237A94:
	mov r0, #1
	add r1, #0x38
	strb r0, [r5, r1]
_02237A9A:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02237AA0: .word 0x0000217D
_02237AA4: .word 0x0000217F
_02237AA8: .word 0x0000219C
_02237AAC: .word 0x000001EE
_02237AB0: .word 0x00002144
_02237AB4: .word 0x00003044
_02237AB8: .word 0x000003E1
_02237ABC: .word 0x000001E1
_02237AC0: .word 0x0000217C

	thumb_func_start ov11_02237AC4
ov11_02237AC4: ; 0x02237AC4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r1, [r4, #0x64]
	add r0, r5, #0
	bl ov11_02230270
	mov r1, #0x71
	lsl r1, r1, #2
	mov r2, #1
	add r1, r4, r1
	lsl r0, r0, #3
	ldr r3, [r1, r0]
	lsl r2, r2, #0x14
	orr r2, r3
	str r2, [r1, r0]
	ldr r3, [r1, r0]
	ldr r2, _02237B00 ; =0xFF9FFFFF
	and r3, r2
	ldr r2, [r4, #0x64]
	lsl r2, r2, #0x1e
	lsr r2, r2, #9
	orr r2, r3
	str r2, [r1, r0]
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02237B00: .word 0xFF9FFFFF

	thumb_func_start ov11_02237B04
ov11_02237B04: ; 0x02237B04
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _02237B82
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #0x10
	bl ov11_0223C230
	add r4, r0, #0
	bl MaskOfFlagNo
	ldr r1, _02237B90 ; =0x00003108
	ldrb r1, [r5, r1]
	tst r0, r1
	bne _02237B78
	mov r0, #0xc0
	mul r0, r4
	add r1, r5, r0
	ldr r0, _02237B94 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02237B78
	ldr r0, [r5, #0x64]
	mov r2, #0x75
	lsl r0, r0, #6
	add r0, r5, r0
	lsl r2, r2, #2
	ldr r0, [r0, r2]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	bne _02237B78
	add r1, r5, r2
	lsl r0, r4, #6
	ldr r3, [r1, r0]
	lsl r3, r3, #0x1c
	lsr r3, r3, #0x1f
	bne _02237B78
	sub r2, #0xbc
	str r4, [r5, r2]
	ldr r3, [r1, r0]
	mov r2, #8
	orr r2, r3
	str r2, [r1, r0]
	b _02237B8A
_02237B78:
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_0223A424
	b _02237B8A
_02237B82:
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_0223A424
_02237B8A:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_02237B90: .word 0x00003108
_02237B94: .word 0x00002D8C

	thumb_func_start ov11_02237B98
ov11_02237B98: ; 0x02237B98
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp, #4]
	add r0, r5, #0
	bl ov11_0222FF74
	str r0, [sp, #8]
	ldr r1, [r4, #0x64]
	add r0, r5, #0
	bl ov11_02230270
	str r0, [sp]
	ldr r1, [r4, #0x6c]
	add r0, r5, #0
	bl ov11_02230270
	add r7, r0, #0
	ldr r1, [r4, #0x64]
	add r0, r5, #0
	bl ov11_02230270
	cmp r0, #0
	beq _02237BF2
	ldr r0, [sp, #8]
	mov r1, #0x84
	tst r0, r1
	bne _02237BF2
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
	b _02237C90
_02237BF2:
	ldr r0, [r4, #0x64]
	add r1, r4, r0
	ldr r0, _02237C98 ; =0x0000219C
	ldrb r0, [r1, r0]
	bl MaskOfFlagNo
	ldr r1, [sp]
	lsl r1, r1, #3
	add r2, r4, r1
	mov r1, #0x71
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	lsl r1, r1, #3
	lsr r1, r1, #0x1a
	tst r0, r1
	bne _02237C30
	ldr r0, [r4, #0x6c]
	add r1, r4, r0
	ldr r0, _02237C98 ; =0x0000219C
	ldrb r0, [r1, r0]
	bl MaskOfFlagNo
	lsl r1, r7, #3
	add r2, r4, r1
	mov r1, #0x71
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	lsl r1, r1, #3
	lsr r1, r1, #0x1a
	tst r0, r1
	beq _02237C3A
_02237C30:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
	b _02237C90
_02237C3A:
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	add r2, r1, #0
	mul r2, r0
	add r3, r4, r2
	ldr r2, _02237C9C ; =0x00002DB8
	ldrh r3, [r3, r2]
	cmp r3, #0
	bne _02237C58
	ldr r3, [r4, #0x6c]
	mul r0, r3
	add r0, r4, r0
	ldrh r0, [r0, r2]
	cmp r0, #0
	beq _02237C6E
_02237C58:
	add r0, r4, #0
	bl ov11_02246CAC
	cmp r0, #0
	beq _02237C6E
	ldr r1, [r4, #0x6c]
	add r0, r4, #0
	bl ov11_02246CAC
	cmp r0, #0
	bne _02237C78
_02237C6E:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
	b _02237C90
_02237C78:
	ldr r1, [r4, #0x64]
	ldr r2, [r4, #0x6c]
	add r0, r4, #0
	mov r3, #0x3c
	bl ov11_02246D84
	cmp r0, #1
	bne _02237C90
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl ov11_0223A424
_02237C90:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02237C98: .word 0x0000219C
_02237C9C: .word 0x00002DB8

	thumb_func_start ov11_02237CA0
ov11_02237CA0: ; 0x02237CA0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	mov r2, #0x63
	lsl r2, r2, #2
	ldr r3, [r4, #0x64]
	add r5, r4, r2
	add r1, r0, #0
	ldrb r0, [r5, r3]
	cmp r0, #0
	beq _02237CCA
	add r0, r4, #0
	bl ov11_0223A424
	b _02237CDA
_02237CCA:
	mov r0, #2
	strb r0, [r5, r3]
	ldr r0, [r4, #0x64]
	add r2, #0x2c
	add r1, r4, r0
	ldr r0, _02237CE0 ; =0x0000219C
	ldrb r0, [r1, r0]
	strb r0, [r1, r2]
_02237CDA:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02237CE0: .word 0x0000219C

	thumb_func_start ov11_02237CE4
ov11_02237CE4: ; 0x02237CE4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x48
	str r0, [sp]
	str r1, [sp, #4]
	add r0, r1, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r0, [sp, #4]
	bl ov11_0223A404
	ldr r1, [sp, #4]
	str r0, [sp, #0x14]
	ldr r0, [sp]
	ldr r1, [r1, #0x64]
	mov r7, #0
	bl ov11_0222FFC8
	str r0, [sp, #0xc]
	add r0, r7, #0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xc]
	cmp r0, #0
	ble _02237D8A
	add r5, sp, #0x18
_02237D16:
	ldr r0, [sp, #4]
	ldr r1, [r0, #0x64]
	add r2, r0, r1
	ldr r0, _02237DB8 ; =0x0000219C
	ldrb r2, [r2, r0]
	ldr r0, [sp, #0x10]
	cmp r0, r2
	beq _02237D7E
	ldr r0, [sp]
	ldr r2, [sp, #0x10]
	bl ov11_02230014
	mov r1, #0xad
	mov r2, #0
	str r0, [sp, #8]
	bl GetMonData
	cmp r0, #0
	beq _02237D7E
	ldr r0, [sp, #8]
	mov r1, #0xad
	mov r2, #0
	bl GetMonData
	ldr r1, _02237DBC ; =0x000001EE
	cmp r0, r1
	beq _02237D7E
	mov r4, #0
_02237D4E:
	add r1, r4, #0
	ldr r0, [sp, #8]
	add r1, #0x36
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r0, r6, #0
	bl ov11_02246BE8
	cmp r0, #0
	bne _02237D78
	add r0, r6, #0
	bl ov11_0224C07C
	cmp r0, #1
	bne _02237D78
	strh r6, [r5]
	add r5, r5, #2
	add r7, r7, #1
_02237D78:
	add r4, r4, #1
	cmp r4, #4
	blt _02237D4E
_02237D7E:
	ldr r0, [sp, #0x10]
	add r1, r0, #1
	ldr r0, [sp, #0xc]
	str r1, [sp, #0x10]
	cmp r1, r0
	blt _02237D16
_02237D8A:
	cmp r7, #0
	beq _02237DA8
	bl LCRandom
	add r1, r7, #0
	bl _s32_div_f
	lsl r1, r1, #1
	add r0, sp, #0x18
	ldrh r2, [r0, r1]
	mov r1, #0x49
	ldr r0, [sp, #4]
	lsl r1, r1, #2
	str r2, [r0, r1]
	b _02237DB0
_02237DA8:
	ldr r0, [sp, #4]
	ldr r1, [sp, #0x14]
	bl ov11_0223A424
_02237DB0:
	mov r0, #0
	add sp, #0x48
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02237DB8: .word 0x0000219C
_02237DBC: .word 0x000001EE

	thumb_func_start ov11_02237DC0
ov11_02237DC0: ; 0x02237DC0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r0, #0
	str r1, [sp]
	add r0, r1, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r0, [sp]
	bl ov11_0223A404
	str r0, [sp, #4]
	mov r6, #0
	add r0, r7, #0
	add r4, r6, #0
	bl ov11_0222FF84
	cmp r0, #0
	ble _02237E00
	ldr r5, [sp]
_02237DE8:
	ldr r0, _02237E30 ; =0x00002D8C
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _02237DF2
	add r6, r6, #1
_02237DF2:
	add r0, r7, #0
	add r5, #0xc0
	add r4, r4, #1
	bl ov11_0222FF84
	cmp r4, r0
	blt _02237DE8
_02237E00:
	ldr r0, [sp]
	add r0, #0xec
	ldr r1, [r0]
	sub r0, r6, #1
	cmp r1, r0
	bne _02237E16
	ldr r0, [sp]
	ldr r1, [sp, #4]
	bl ov11_0223A424
	b _02237E2A
_02237E16:
	mov r1, #0x75
	ldr r0, [sp]
	lsl r1, r1, #2
	add r3, r0, r1
	ldr r0, [r0, #0x64]
	lsl r2, r0, #6
	ldr r1, [r3, r2]
	mov r0, #0x10
	orr r0, r1
	str r0, [r3, r2]
_02237E2A:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02237E30: .word 0x00002D8C

	thumb_func_start ov11_02237E34
ov11_02237E34: ; 0x02237E34
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r1, [r5, #0x64]
	add r0, r6, #0
	bl ov11_02230270
	add r1, r5, #0
	ldr r4, [r5, #0x64]
	add r1, #0x84
	str r4, [r1]
	ldr r1, [r5, #0x6c]
	lsl r0, r0, #3
	str r1, [r5, #0x64]
	mov r1, #0x71
	lsl r1, r1, #2
	add r1, r5, r1
	ldr r0, [r1, r0]
	lsl r1, r0, #0xb
	lsr r1, r1, #0x1f
	beq _02237E7E
	lsl r0, r0, #9
	lsr r0, r0, #0x1e
	mov r1, #0xc0
	mul r1, r0
	add r2, r5, r1
	ldr r1, _02237EDC ; =0x00002D8C
	ldr r1, [r2, r1]
	cmp r1, #0
	beq _02237E7E
	str r0, [r5, #0x6c]
	b _02237ECA
_02237E7E:
	ldr r0, _02237EE0 ; =0x00003044
	ldr r3, [r5, r0]
	lsl r0, r3, #4
	add r1, r5, r0
	ldr r0, _02237EE4 ; =0x000003E6
	ldrh r0, [r1, r0]
	cmp r0, #4
	beq _02237E92
	cmp r0, #8
	bne _02237E96
_02237E92:
	str r4, [r5, #0x6c]
	b _02237ECA
_02237E96:
	mov r0, #1
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	lsl r3, r3, #0x10
	ldr r2, [r5, #0x64]
	add r0, r6, #0
	add r1, r5, #0
	lsr r3, r3, #0x10
	bl ov11_02244C28
	mov r1, #0xb5
	lsl r1, r1, #2
	add r2, r5, r1
	mov r1, #0x1c
	mul r1, r0
	ldr r1, [r2, r1]
	lsl r2, r1, #0x1e
	lsr r2, r2, #0x1f
	bne _02237EC4
	lsl r1, r1, #0x1d
	lsr r1, r1, #0x1f
	beq _02237EC8
_02237EC4:
	str r0, [r5, #0x6c]
	b _02237ECA
_02237EC8:
	str r4, [r5, #0x6c]
_02237ECA:
	mov r1, #0x85
	lsl r1, r1, #6
	ldr r2, [r5, r1]
	mov r0, #8
	orr r0, r2
	str r0, [r5, r1]
	mov r0, #0
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_02237EDC: .word 0x00002D8C
_02237EE0: .word 0x00003044
_02237EE4: .word 0x000003E6

	thumb_func_start ov11_02237EE8
ov11_02237EE8: ; 0x02237EE8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r1, [r5, #0x64]
	ldr r0, [r5, #0x6c]
	lsl r4, r1, #6
	add r2, r5, r4
	lsl r1, r0, #2
	add r2, r2, r1
	mov r1, #0x76
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	cmp r1, #0
	beq _02237F1A
	bl MaskOfFlagNo
	mov r1, #0x7b
	add r2, r5, r4
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	tst r0, r1
	bne _02237F40
_02237F1A:
	ldr r0, [r5, #0x6c]
	add r2, r5, r4
	lsl r1, r0, #2
	add r2, r2, r1
	mov r1, #0x1f
	lsl r1, r1, #4
	ldr r1, [r2, r1]
	cmp r1, #0
	beq _02237F48
	bl MaskOfFlagNo
	ldr r1, [r5, #0x64]
	lsl r1, r1, #6
	add r2, r5, r1
	mov r1, #0x81
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	tst r0, r1
	beq _02237F48
_02237F40:
	ldr r0, _02237F54 ; =0x00002158
	mov r1, #0x14
	str r1, [r5, r0]
	b _02237F4E
_02237F48:
	ldr r0, _02237F54 ; =0x00002158
	mov r1, #0xa
	str r1, [r5, r0]
_02237F4E:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02237F54: .word 0x00002158

	thumb_func_start ov11_02237F58
ov11_02237F58: ; 0x02237F58
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	ldr r1, [r4, #0x6c]
	add r0, r5, #0
	bl ov11_02230270
	lsl r1, r0, #2
	add r2, r4, r1
	mov r1, #0x6f
	lsl r1, r1, #2
	ldr r2, [r2, r1]
	mov r1, #1
	tst r1, r2
	bne _02237F8C
	mov r1, #2
	tst r1, r2
	beq _02237FBC
_02237F8C:
	mov r5, #0x6f
	lsl r5, r5, #2
	add r2, r4, r5
	lsl r1, r0, #2
	ldr r6, [r2, r1]
	mov r3, #1
	bic r6, r3
	str r6, [r2, r1]
	ldr r6, [r2, r1]
	mov r3, #2
	bic r6, r3
	add r5, #8
	str r6, [r2, r1]
	lsl r2, r0, #3
	add r3, r4, r5
	ldr r1, [r3, r2]
	mov r0, #0x1c
	bic r1, r0
	str r1, [r3, r2]
	ldr r1, [r3, r2]
	ldr r0, _02237FC8 ; =0xFFFFFC7F
	and r0, r1
	str r0, [r3, r2]
	b _02237FC4
_02237FBC:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
_02237FC4:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_02237FC8: .word 0xFFFFFC7F

	thumb_func_start ov11_02237FCC
ov11_02237FCC: ; 0x02237FCC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r1, r0, #0
	mov r0, #0xb7
	lsl r0, r0, #6
	add r3, r4, r0
	ldr r0, [r4, #0x6c]
	mov r5, #0xc0
	add r2, r0, #0
	mul r2, r5
	ldr r0, [r3, r2]
	lsl r5, r5, #5
	tst r5, r0
	beq _02237FFE
	add r0, r4, #0
	bl ov11_0223A424
	b _02238006
_02237FFE:
	mov r1, #1
	lsl r1, r1, #0xc
	orr r0, r1
	str r0, [r3, r2]
_02238006:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_0223800C
ov11_0223800C: ; 0x0223800C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r6, r0, #0
	ldr r1, [r5, #0x6c]
	add r0, r4, #0
	bl ov11_02230270
	add r4, r0, #0
	ldr r2, [r5, #0x6c]
	mov r0, #0xc0
	mul r0, r2
	add r1, r5, r0
	ldr r0, _02238118 ; =0x00002DB8
	ldrh r0, [r1, r0]
	cmp r0, #0
	beq _02238086
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	mov r3, #0x3c
	bl ov11_02246D84
	cmp r0, #1
	bne _02238086
	add r0, r5, #0
	ldr r1, _0223811C ; =0x000002CA
	add r0, #0xf6
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #0x25
	add r0, #0xf5
	strb r1, [r0]
	ldr r1, [r5, #0x6c]
	add r0, r5, #0
	bl ov11_0224682C
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	ldr r0, [r5, #0x6c]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	ldr r0, _02238120 ; =0x00002D67
	add r2, r5, r2
	ldrb r2, [r2, r0]
	add r0, r5, #0
	add r0, #0xfc
	str r2, [r0]
	ldr r0, _02238124 ; =0x00003044
	add r1, #0x40
	ldr r0, [r5, r0]
	str r0, [r5, r1]
	b _02238114
_02238086:
	ldr r1, [r5, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _02238118 ; =0x00002DB8
	ldrh r0, [r1, r0]
	cmp r0, #0
	beq _0223810C
	mov r1, #0x8a
	add r0, r5, #0
	lsl r1, r1, #2
	add r0, #0xf6
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #0x21
	add r0, #0xf5
	strb r1, [r0]
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl ov11_0224682C
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	ldr r1, [r5, #0x6c]
	add r0, r5, #0
	bl ov11_0224682C
	add r1, r5, #0
	add r1, #0xfc
	str r0, [r1]
	ldr r0, [r5, #0x6c]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	add r0, r5, r2
	ldr r2, _02238118 ; =0x00002DB8
	ldrh r3, [r0, r2]
	add r0, r1, #0
	add r0, #0x40
	str r3, [r5, r0]
	ldr r3, [r5, #0x6c]
	mov r0, #0
	mul r1, r3
	add r1, r5, r1
	strh r0, [r1, r2]
	ldr r0, [r5, #0x6c]
	add r1, r5, r0
	ldr r0, _02238128 ; =0x0000219C
	ldrb r0, [r1, r0]
	bl MaskOfFlagNo
	mov r1, #0x71
	lsl r1, r1, #2
	add r3, r5, r1
	lsl r2, r4, #3
	ldr r4, [r3, r2]
	ldr r1, _0223812C ; =0xE07FFFFF
	and r1, r4
	lsl r4, r4, #3
	lsr r4, r4, #0x1a
	orr r0, r4
	lsl r0, r0, #0x1a
	lsr r0, r0, #3
	orr r0, r1
	str r0, [r3, r2]
	b _02238114
_0223810C:
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_0223A424
_02238114:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_02238118: .word 0x00002DB8
_0223811C: .word 0x000002CA
_02238120: .word 0x00002D67
_02238124: .word 0x00003044
_02238128: .word 0x0000219C
_0223812C: .word 0xE07FFFFF

	thumb_func_start ov11_02238130
ov11_02238130: ; 0x02238130
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r0, _02238178 ; =0x00002154
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _02238174
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	ldr r1, _0223817C ; =0x00003044
	ldr r1, [r4, r1]
	lsl r1, r1, #4
	add r2, r4, r1
	ldr r1, _02238180 ; =0x000003E1
	ldrb r3, [r2, r1]
	ldr r1, _02238184 ; =0x00002D8C
	add r2, r4, r0
	ldr r0, [r2, r1]
	add r1, r1, #4
	ldr r1, [r2, r1]
	mul r0, r3
	bl _u32_div_f
	ldr r1, _02238178 ; =0x00002154
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _02238174
	mov r0, #1
	str r0, [r4, r1]
_02238174:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_02238178: .word 0x00002154
_0223817C: .word 0x00003044
_02238180: .word 0x000003E1
_02238184: .word 0x00002D8C

	thumb_func_start ov11_02238188
ov11_02238188: ; 0x02238188
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r7, r1, #0
	str r0, [sp]
	add r0, r7, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r7, #0
	bl ov11_0223A404
	str r0, [sp, #0x14]
	ldr r0, [sp]
	ldr r1, [r7, #0x64]
	mov r2, #0
	bl ov11_02230308
	add r4, r0, #0
	ldr r0, [sp]
	ldr r1, [r7, #0x64]
	mov r2, #2
	bl ov11_02230308
	mov r6, #0xb7
	add r3, r0, #0
	lsl r6, r6, #6
	add r1, r4, #0
	mov r0, #0xc0
	mov r4, #1
	add r2, r7, r6
	mul r1, r0
	ldr r5, [r2, r1]
	lsl r4, r4, #0x1e
	orr r5, r4
	str r5, [r2, r1]
	add r1, r3, #0
	mul r1, r0
	ldr r3, [r2, r1]
	orr r3, r4
	str r3, [r2, r1]
	ldr r1, [r7, #0x64]
	mul r0, r1
	add r0, r7, r0
	ldr r2, [r0, r6]
	lsr r0, r4, #0x11
	tst r0, r2
	beq _022381F0
	ldr r1, [sp, #0x14]
	add r0, r7, #0
	bl ov11_0223A424
	b _02238294
_022381F0:
	ldr r0, [sp]
	bl ov11_02230270
	str r0, [sp, #0x10]
	ldr r0, [sp]
	bl ov11_0222FF84
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #8]
	cmp r0, #0
	ble _0223826A
	str r7, [sp, #4]
_0223820C:
	ldr r0, [sp]
	ldr r1, [sp, #0xc]
	bl ov11_02230270
	ldr r1, [sp, #0x10]
	cmp r1, r0
	beq _02238258
	mov r2, #0
	ldr r0, _0223829C ; =0x00002D4C
	add r4, r2, #0
_02238220:
	ldr r1, [r7, #0x64]
	mov r6, #0xc0
	mul r6, r1
	add r1, r7, r6
	add r6, r1, r4
	ldr r1, _0223829C ; =0x00002D4C
	ldr r5, [sp, #4]
	ldrh r6, [r6, r1]
	mov r3, #0
_02238232:
	ldrh r1, [r5, r0]
	cmp r6, r1
	bne _02238240
	cmp r6, #0
	beq _02238240
	cmp r1, #0
	bne _02238248
_02238240:
	add r3, r3, #1
	add r5, r5, #2
	cmp r3, #4
	blt _02238232
_02238248:
	cmp r3, #4
	bne _02238254
	add r2, r2, #1
	add r4, r4, #2
	cmp r2, #4
	blt _02238220
_02238254:
	cmp r3, #4
	bne _0223826A
_02238258:
	ldr r0, [sp, #4]
	add r0, #0xc0
	str r0, [sp, #4]
	ldr r0, [sp, #0xc]
	add r1, r0, #1
	ldr r0, [sp, #8]
	str r1, [sp, #0xc]
	cmp r1, r0
	blt _0223820C
_0223826A:
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #8]
	cmp r1, r0
	bne _0223827C
	ldr r1, [sp, #0x14]
	add r0, r7, #0
	bl ov11_0223A424
	b _02238294
_0223827C:
	mov r0, #0xb7
	ldr r1, [r7, #0x64]
	lsl r0, r0, #6
	add r3, r7, r0
	mov r0, #0xc0
	add r2, r1, #0
	mul r2, r0
	mov r0, #2
	ldr r1, [r3, r2]
	lsl r0, r0, #0xc
	orr r0, r1
	str r0, [r3, r2]
_02238294:
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223829C: .word 0x00002D4C

	thumb_func_start ov11_022382A0
ov11_022382A0: ; 0x022382A0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp]
	ldr r1, [r4, #0x6c]
	add r0, r5, #0
	bl ov11_02230270
	ldr r6, [r4, #0x74]
	mov r0, #0xc0
	mul r0, r6
	add r1, r4, r0
	mov r0, #0xb7
	lsl r0, r0, #6
	ldr r1, [r1, r0]
	mov r0, #1
	lsl r0, r0, #0xe
	tst r0, r1
	beq _0223833C
	ldr r1, [r4, #0x64]
	add r0, r5, #0
	bl ov11_02230270
	add r7, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_02230270
	cmp r7, r0
	beq _0223833C
	ldr r0, [r4, #0x64]
	mov r2, #0xc0
	add r1, r0, #0
	mul r1, r2
	ldr r3, _02238348 ; =0x00002D8C
	add r0, r4, r1
	ldr r0, [r0, r3]
	cmp r0, #0
	beq _0223833C
	mov r1, #0xc1
	lsl r1, r1, #6
	ldr r6, [r4, r1]
	cmp r6, #0xa5
	beq _0223833C
	add r0, r2, #0
	add r0, #0x64
	str r6, [r4, r0]
	ldr r0, [r4, #0x64]
	ldr r1, [r4, r1]
	sub r3, #0x4c
	lsl r1, r1, #0x10
	add r3, r4, r3
	mul r2, r0
	add r0, r3, r2
	lsr r1, r1, #0x10
	bl ov11_022461AC
	ldr r3, [r4, #0x64]
	mov r2, #0xc0
	mul r2, r3
	add r2, r4, r2
	add r2, r2, r0
	ldr r0, _0223834C ; =0x00002D6C
	mov r1, #0
	strb r1, [r2, r0]
	ldr r2, [r4, #0x64]
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02245190
	b _02238344
_0223833C:
	ldr r1, [sp]
	add r0, r4, #0
	bl ov11_0223A424
_02238344:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02238348: .word 0x00002D8C
_0223834C: .word 0x00002D6C

	thumb_func_start ov11_02238350
ov11_02238350: ; 0x02238350
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r0, #0
	str r1, [sp]
	add r0, r1, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r0, [sp]
	bl ov11_0223A404
	str r0, [sp, #4]
	mov r6, #0
	add r0, r7, #0
	add r4, r6, #0
	bl ov11_0222FF84
	cmp r0, #0
	ble _02238390
	ldr r5, [sp]
_02238378:
	ldr r0, _022383C0 ; =0x00002D8C
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _02238382
	add r6, r6, #1
_02238382:
	add r0, r7, #0
	add r5, #0xc0
	add r4, r4, #1
	bl ov11_0222FF84
	cmp r4, r0
	blt _02238378
_02238390:
	ldr r0, [sp]
	add r0, #0xec
	ldr r1, [r0]
	sub r0, r6, #1
	cmp r1, r0
	bne _022383A6
	ldr r0, [sp]
	ldr r1, [sp, #4]
	bl ov11_0223A424
	b _022383BA
_022383A6:
	mov r1, #0x75
	ldr r0, [sp]
	lsl r1, r1, #2
	add r3, r0, r1
	ldr r0, [r0, #0x64]
	lsl r2, r0, #6
	ldr r1, [r3, r2]
	mov r0, #0x20
	orr r0, r1
	str r0, [r3, r2]
_022383BA:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022383C0: .word 0x00002D8C

	thumb_func_start ov11_022383C4
ov11_022383C4: ; 0x022383C4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r2, [r4, #0x6c]
	mov r1, #0xc0
	mul r1, r2
	add r2, r4, r1
	ldr r1, _02238410 ; =0x00002D60
	ldr r5, _02238414 ; =ov11_0225DCA8
	ldr r3, [r2, r1]
	ldr r1, _02238418 ; =0x0000FFFF
	mov r0, #0
_022383E2:
	ldrh r2, [r5]
	cmp r2, r3
	bge _022383F2
	add r5, r5, #4
	ldrh r2, [r5]
	add r0, r0, #1
	cmp r2, r1
	bne _022383E2
_022383F2:
	lsl r2, r0, #2
	ldr r0, _02238414 ; =ov11_0225DCA8
	ldrh r1, [r0, r2]
	ldr r0, _02238418 ; =0x0000FFFF
	cmp r1, r0
	beq _02238404
	ldr r0, _0223841C ; =ov11_0225DCAA
	ldrh r1, [r0, r2]
	b _02238406
_02238404:
	mov r1, #0x78
_02238406:
	ldr r0, _02238420 ; =0x00002154
	str r1, [r4, r0]
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02238410: .word 0x00002D60
_02238414: .word ov11_0225DCA8
_02238418: .word 0x0000FFFF
_0223841C: .word ov11_0225DCAA
_02238420: .word 0x00002154

	thumb_func_start ov11_02238424
ov11_02238424: ; 0x02238424
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	mov r0, #0xd
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #8
	mov r3, #0
	bl ov11_02246870
	cmp r0, #0
	bne _022384CC
	mov r0, #0x4c
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #8
	mov r3, #0
	bl ov11_02246870
	cmp r0, #0
	bne _022384CC
	mov r1, #6
	lsl r1, r1, #6
	ldr r2, [r4, r1]
	ldr r0, _022384D0 ; =0x000080FF
	tst r0, r2
	ldr r0, _022384D4 ; =0x00003044
	beq _022384BE
	ldr r0, [r4, r0]
	lsl r0, r0, #4
	add r2, r4, r0
	ldr r0, _022384D8 ; =0x000003E1
	ldrb r0, [r2, r0]
	lsl r2, r0, #1
	ldr r0, _022384DC ; =0x00002154
	str r2, [r4, r0]
	ldr r2, [r4, r1]
	mov r1, #3
	tst r1, r2
	beq _02238486
	mov r1, #0xb
	add r0, #0xc
	str r1, [r4, r0]
_02238486:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r0, #0xc
	tst r0, r1
	beq _02238498
	ldr r0, _022384E0 ; =0x00002160
	mov r1, #5
	str r1, [r4, r0]
_02238498:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r0, #0x30
	tst r0, r1
	beq _022384AA
	ldr r0, _022384E0 ; =0x00002160
	mov r1, #0xa
	str r1, [r4, r0]
_022384AA:
	mov r0, #6
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	mov r0, #0xc0
	tst r0, r1
	beq _022384CC
	ldr r0, _022384E0 ; =0x00002160
	mov r1, #0xf
	str r1, [r4, r0]
	b _022384CC
_022384BE:
	ldr r0, [r4, r0]
	lsl r0, r0, #4
	add r1, r4, r0
	ldr r0, _022384D8 ; =0x000003E1
	ldrb r1, [r1, r0]
	ldr r0, _022384DC ; =0x00002154
	str r1, [r4, r0]
_022384CC:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_022384D0: .word 0x000080FF
_022384D4: .word 0x00003044
_022384D8: .word 0x000003E1
_022384DC: .word 0x00002154
_022384E0: .word 0x00002160

	thumb_func_start ov11_022384E4
ov11_022384E4: ; 0x022384E4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r6, r1, #0
	str r0, [sp]
	add r0, r6, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r6, #0
	bl ov11_0223A404
	str r0, [sp, #0x10]
	ldr r0, [sp]
	bl ov11_0222FF84
	mov r7, #0
	str r0, [sp, #0xc]
	cmp r0, #0
	bgt _0223850C
	b _02238612
_0223850C:
	mov r0, #0xb5
	lsl r0, r0, #6
	add r0, r6, r0
	str r6, [sp, #8]
	add r5, r6, #0
	str r0, [sp, #4]
_02238518:
	ldr r1, [sp, #8]
	ldr r0, _02238654 ; =0x000021A8
	ldr r0, [r1, r0]
	cmp r0, #0x27
	beq _022385FC
	ldr r0, _02238658 ; =0x00002D8C
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _022385FC
	ldr r0, _0223865C ; =0x00002DAC
	ldr r1, [r5, r0]
	mov r0, #0x27
	tst r0, r1
	bne _022385FC
	add r0, r6, #0
	add r1, r7, #0
	bl ov11_02247190
	cmp r0, #0
	bne _022385FC
	ldr r0, [sp]
	add r1, r7, #0
	bl ov11_02230270
	str r0, [sp, #0x14]
	ldr r0, [sp]
	ldr r1, [r6, #0x78]
	bl ov11_02230270
	ldr r1, [sp, #0x14]
	cmp r1, r0
	beq _022385FC
	ldr r0, _02238660 ; =0x00002DEC
	ldrh r4, [r5, r0]
	cmp r4, #0
	beq _02238570
	add r0, r0, #2
	ldrh r0, [r5, r0]
	lsl r0, r0, #1
	add r1, r5, r0
	ldr r0, _02238664 ; =0x00002D4C
	ldrh r0, [r1, r0]
	cmp r4, r0
	beq _0223857A
_02238570:
	add r0, r6, #0
	add r1, r7, #0
	bl ov11_0224683C
	add r4, r0, #0
_0223857A:
	cmp r4, #0
	beq _022385FC
	lsl r1, r4, #0x10
	ldr r0, [sp, #4]
	lsr r1, r1, #0x10
	bl ov11_022461AC
	str r0, [sp, #0x18]
	lsl r0, r4, #4
	add r1, r6, r0
	ldr r0, _02238668 ; =0x000003DE
	ldrh r0, [r1, r0]
	cmp r0, #0x80
	bne _022385FC
	ldr r0, [sp, #0x18]
	add r1, r5, r0
	ldr r0, _0223866C ; =0x00002D6C
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _022385FC
	ldr r0, _0223866C ; =0x00002D6C
	add r1, r6, r0
	mov r0, #0xc0
	mul r0, r7
	add r5, r1, r0
	ldr r0, [sp, #0x18]
	ldrb r0, [r5, r0]
	sub r1, r0, #1
	ldr r0, [sp, #0x18]
	strb r1, [r5, r0]
	ldr r1, [r6, #0x78]
	add r0, r6, #0
	bl ov11_02246D1C
	cmp r0, #0x2e
	bne _022385D0
	ldr r0, [sp, #0x18]
	ldrb r0, [r5, r0]
	cmp r0, #0
	beq _022385D0
	sub r1, r0, #1
	ldr r0, [sp, #0x18]
	strb r1, [r5, r0]
_022385D0:
	ldr r0, [sp]
	add r1, r6, #0
	bl ov11_02247264
	str r7, [r6, #0x64]
	ldr r0, [r6, #0x78]
	lsl r2, r7, #1
	str r0, [r6, #0x6c]
	ldr r1, _02238670 ; =0x00002158
	mov r0, #0x14
	str r0, [r6, r1]
	ldr r0, _02238674 ; =0x00003044
	add r2, r6, r2
	str r4, [r6, r0]
	add r0, #0x38
	strh r4, [r2, r0]
	lsl r0, r7, #4
	mov r2, #0x27
	add r0, r6, r0
	add r1, #0x50
	str r2, [r0, r1]
	b _02238612
_022385FC:
	ldr r0, [sp, #8]
	add r7, r7, #1
	add r0, #0x10
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	add r5, #0xc0
	add r0, #0xc0
	str r0, [sp, #4]
	ldr r0, [sp, #0xc]
	cmp r7, r0
	blt _02238518
_02238612:
	ldr r0, [sp, #0xc]
	cmp r7, r0
	bne _02238622
	ldr r1, [sp, #0x10]
	add r0, r6, #0
	bl ov11_0223A424
	b _0223864E
_02238622:
	ldr r1, [r6, #0x64]
	add r0, r6, #0
	bl ov11_02249D90
	add r5, r0, #0
	ldr r1, [r6, #0x64]
	add r0, r6, #0
	mov r2, #0
	bl ov11_02249DA4
	cmp r5, #0x36
	beq _02238642
	cmp r5, #0x72
	beq _02238642
	cmp r5, #0x7c
	bne _0223864E
_02238642:
	ldr r1, [r6, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r1, r6, r0
	ldr r0, _02238678 ; =0x00002DF8
	strh r4, [r1, r0]
_0223864E:
	mov r0, #0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02238654: .word 0x000021A8
_02238658: .word 0x00002D8C
_0223865C: .word 0x00002DAC
_02238660: .word 0x00002DEC
_02238664: .word 0x00002D4C
_02238668: .word 0x000003DE
_0223866C: .word 0x00002D6C
_02238670: .word 0x00002158
_02238674: .word 0x00003044
_02238678: .word 0x00002DF8

	thumb_func_start ov11_0223867C
ov11_0223867C: ; 0x0223867C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r0, [r4, #0x64]
	ldr r3, _022386BC ; =0x00002144
	str r0, [sp]
	ldr r0, [r4, #0x6c]
	ldr r2, _022386C0 ; =0x00003044
	str r0, [sp, #4]
	ldr r0, [r4, r3]
	add r1, r4, #0
	str r0, [sp, #8]
	add r0, r3, #0
	add r0, #0x28
	add r0, r4, r0
	str r0, [sp, #0xc]
	add r3, #0x1c
	ldr r2, [r4, r2]
	ldr r3, [r4, r3]
	add r0, r5, #0
	bl ov11_02246274
	ldr r1, _022386BC ; =0x00002144
	str r0, [r4, r1]
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_022386BC: .word 0x00002144
_022386C0: .word 0x00003044

	thumb_func_start ov11_022386C4
ov11_022386C4: ; 0x022386C4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r1, #0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #1
	mov r6, #0
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp, #8]
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r5, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp, #4]
	ldr r0, [sp]
	ldr r2, [sp, #8]
	add r1, r4, #0
	bl ov11_0223C230
	cmp r7, #6
	bhi _022387B6
	add r1, r7, r7
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02238710: ; jump table
	.short _0223871E - _02238710 - 2 ; case 0
	.short _02238734 - _02238710 - 2 ; case 1
	.short _0223874A - _02238710 - 2 ; case 2
	.short _02238760 - _02238710 - 2 ; case 3
	.short _02238776 - _02238710 - 2 ; case 4
	.short _0223878C - _02238710 - 2 ; case 5
	.short _022387A2 - _02238710 - 2 ; case 6
_0223871E:
	lsl r0, r0, #6
	add r1, r4, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	cmp r5, r0
	bne _022387B6
	mov r6, #1
	b _022387B6
_02238734:
	lsl r0, r0, #6
	add r1, r4, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	cmp r5, r0
	bne _022387B6
	mov r6, #1
	b _022387B6
_0223874A:
	lsl r0, r0, #6
	add r1, r4, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	cmp r5, r0
	bne _022387B6
	mov r6, #1
	b _022387B6
_02238760:
	lsl r0, r0, #6
	add r1, r4, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	cmp r5, r0
	bne _022387B6
	mov r6, #1
	b _022387B6
_02238776:
	lsl r0, r0, #6
	add r1, r4, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	cmp r5, r0
	bne _022387B6
	mov r6, #1
	b _022387B6
_0223878C:
	lsl r0, r0, #6
	add r1, r4, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1f
	cmp r5, r0
	bne _022387B6
	mov r6, #1
	b _022387B6
_022387A2:
	lsl r0, r0, #6
	add r1, r4, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	cmp r5, r0
	bne _022387B6
	mov r6, #1
_022387B6:
	cmp r6, #0
	beq _022387C2
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl ov11_0223A424
_022387C2:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov11_022387C8
ov11_022387C8: ; 0x022387C8
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r7, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp]
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r5, r0, #0
	ldr r2, [sp]
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_0223C230
	cmp r6, #6
	bhi _022388BC
	add r1, r6, r6
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02238808: ; jump table
	.short _02238816 - _02238808 - 2 ; case 0
	.short _0223882E - _02238808 - 2 ; case 1
	.short _02238846 - _02238808 - 2 ; case 2
	.short _0223885E - _02238808 - 2 ; case 3
	.short _02238876 - _02238808 - 2 ; case 4
	.short _0223888E - _02238808 - 2 ; case 5
	.short _022388A6 - _02238808 - 2 ; case 6
_02238816:
	mov r1, #0x75
	lsl r1, r1, #2
	lsl r3, r0, #6
	add r1, r4, r1
	ldr r2, [r1, r3]
	mov r0, #1
	bic r2, r0
	mov r0, #1
	and r0, r5
	orr r0, r2
	str r0, [r1, r3]
	b _022388BC
_0223882E:
	mov r1, #0x75
	lsl r1, r1, #2
	lsl r3, r0, #6
	add r1, r4, r1
	ldr r2, [r1, r3]
	mov r0, #2
	bic r2, r0
	lsl r0, r5, #0x1f
	lsr r0, r0, #0x1e
	orr r0, r2
	str r0, [r1, r3]
	b _022388BC
_02238846:
	mov r1, #0x75
	lsl r1, r1, #2
	lsl r3, r0, #6
	add r1, r4, r1
	ldr r2, [r1, r3]
	mov r0, #4
	bic r2, r0
	lsl r0, r5, #0x1f
	lsr r0, r0, #0x1d
	orr r0, r2
	str r0, [r1, r3]
	b _022388BC
_0223885E:
	mov r1, #0x75
	lsl r1, r1, #2
	lsl r3, r0, #6
	add r1, r4, r1
	ldr r2, [r1, r3]
	mov r0, #8
	bic r2, r0
	lsl r0, r5, #0x1f
	lsr r0, r0, #0x1c
	orr r0, r2
	str r0, [r1, r3]
	b _022388BC
_02238876:
	mov r1, #0x75
	lsl r1, r1, #2
	lsl r3, r0, #6
	add r1, r4, r1
	ldr r2, [r1, r3]
	mov r0, #0x10
	bic r2, r0
	lsl r0, r5, #0x1f
	lsr r0, r0, #0x1b
	orr r0, r2
	str r0, [r1, r3]
	b _022388BC
_0223888E:
	mov r1, #0x75
	lsl r1, r1, #2
	lsl r3, r0, #6
	add r1, r4, r1
	ldr r2, [r1, r3]
	mov r0, #0x20
	bic r2, r0
	lsl r0, r5, #0x1f
	lsr r0, r0, #0x1a
	orr r0, r2
	str r0, [r1, r3]
	b _022388BC
_022388A6:
	mov r1, #0x75
	lsl r1, r1, #2
	lsl r3, r0, #6
	add r1, r4, r1
	ldr r2, [r1, r3]
	mov r0, #0x40
	bic r2, r0
	lsl r0, r5, #0x1f
	lsr r0, r0, #0x19
	orr r0, r2
	str r0, [r1, r3]
_022388BC:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_022388C0
ov11_022388C0: ; 0x022388C0
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r0, [r4, #0x6c]
	ldr r1, _022388FC ; =0x000021F0
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r2, [r0, r1]
	mov r0, #0x19
	mul r0, r2
	ldr r2, [r4, #0x64]
	lsl r2, r2, #2
	add r2, r4, r2
	ldr r1, [r2, r1]
	bl _u32_div_f
	add r1, r0, #1
	ldr r0, _02238900 ; =0x00002154
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0x96
	ble _022388F6
	mov r1, #0x96
	str r1, [r4, r0]
_022388F6:
	mov r0, #0
	pop {r4, pc}
	nop
_022388FC: .word 0x000021F0
_02238900: .word 0x00002154

	thumb_func_start ov11_02238904
ov11_02238904: ; 0x02238904
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	str r0, [sp]
	ldr r1, [r5, #0x64]
	add r0, r6, #0
	bl ov11_02230270
	ldr r1, [r5, #0x64]
	add r7, r0, #0
	lsl r1, r1, #6
	add r2, r5, r1
	mov r1, #0x83
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	add r0, r6, #0
	bl ov11_02230270
	add r4, r0, #0
	ldr r0, [r5, #0x64]
	mov r2, #0x82
	lsl r0, r0, #6
	add r0, r5, r0
	lsl r2, r2, #2
	ldr r1, [r0, r2]
	cmp r1, #0
	beq _022389E4
	cmp r7, r4
	beq _022389E4
	add r2, r2, #4
	ldr r2, [r0, r2]
	mov r0, #0xc0
	mul r0, r2
	add r2, r5, r0
	ldr r0, _022389F0 ; =0x00002D8C
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _022389E4
	mov r0, #0xf
	mul r0, r1
	mov r1, #0xa
	bl _s32_div_f
	ldr r1, _022389F4 ; =0x00002144
	str r0, [r5, r1]
	mov r0, #0x71
	lsl r0, r0, #2
	add r1, r5, r0
	lsl r0, r4, #3
	ldr r0, [r1, r0]
	lsl r1, r0, #0xb
	lsr r1, r1, #0x1f
	beq _02238992
	lsl r0, r0, #9
	lsr r0, r0, #0x1e
	mov r1, #0xc0
	mul r1, r0
	add r2, r5, r1
	ldr r1, _022389F0 ; =0x00002D8C
	ldr r1, [r2, r1]
	cmp r1, #0
	beq _02238992
	str r0, [r5, #0x6c]
	b _022389A0
_02238992:
	ldr r0, [r5, #0x64]
	lsl r0, r0, #6
	add r1, r5, r0
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	str r0, [r5, #0x6c]
_022389A0:
	ldr r1, [r5, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _022389F0 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _022389D8
	ldr r2, [r5, #0x64]
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_022482A4
	mov r1, #0xc0
	mul r1, r0
	str r0, [r5, #0x6c]
	ldr r0, _022389F0 ; =0x00002D8C
	add r1, r5, r1
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _022389D8
	mov r2, #0x26
	str r2, [r5, #0xc]
	add r0, r5, #0
	mov r1, #1
	add r2, #0xf3
	bl ov11_0223A434
_022389D8:
	ldr r1, [r5, #0x64]
	ldr r2, [r5, #0x6c]
	add r0, r5, #0
	bl ov11_0224C438
	b _022389EC
_022389E4:
	ldr r1, [sp]
	add r0, r5, #0
	bl ov11_0223A424
_022389EC:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022389F0: .word 0x00002D8C
_022389F4: .word 0x00002144

	thumb_func_start ov11_022389F8
ov11_022389F8: ; 0x022389F8
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r0, [r4, #0x6c]
	ldr r1, _02238A34 ; =0x000021A8
	lsl r0, r0, #4
	add r0, r4, r0
	ldr r0, [r0, r1]
	cmp r0, #0x27
	ldr r0, _02238A38 ; =0x00003044
	bne _02238A22
	ldr r0, [r4, r0]
	lsl r0, r0, #4
	add r2, r4, r0
	ldr r0, _02238A3C ; =0x000003E1
	ldrb r0, [r2, r0]
	lsl r0, r0, #1
	b _02238A2C
_02238A22:
	ldr r0, [r4, r0]
	lsl r0, r0, #4
	add r2, r4, r0
	ldr r0, _02238A3C ; =0x000003E1
	ldrb r0, [r2, r0]
_02238A2C:
	sub r1, #0x54
	str r0, [r4, r1]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_02238A34: .word 0x000021A8
_02238A38: .word 0x00003044
_02238A3C: .word 0x000003E1

	thumb_func_start ov11_02238A40
ov11_02238A40: ; 0x02238A40
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r1, [r4, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r2, r4, r0
	lsl r0, r1, #1
	add r1, r4, r0
	ldr r0, _02238A74 ; =0x000030BC
	ldrh r0, [r1, r0]
	add r1, r2, r0
	ldr r0, _02238A78 ; =0x00002D6C
	ldrb r1, [r1, r0]
	cmp r1, #4
	bls _02238A68
	mov r1, #4
_02238A68:
	ldr r0, _02238A7C ; =ov11_0225DC2C
	ldrb r1, [r0, r1]
	ldr r0, _02238A80 ; =0x00002154
	str r1, [r4, r0]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_02238A74: .word 0x000030BC
_02238A78: .word 0x00002D6C
_02238A7C: .word ov11_0225DC2C
_02238A80: .word 0x00002154

	thumb_func_start ov11_02238A84
ov11_02238A84: ; 0x02238A84
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r3, r4, r0
	ldr r1, _02238AB4 ; =0x00002D8C
	mov r0, #0x78
	ldr r2, [r3, r1]
	add r1, r1, #4
	ldr r1, [r3, r1]
	mul r0, r2
	bl _u32_div_f
	add r1, r0, #1
	ldr r0, _02238AB8 ; =0x00002154
	str r1, [r4, r0]
	mov r0, #0
	pop {r4, pc}
	nop
_02238AB4: .word 0x00002D8C
_02238AB8: .word 0x00002154

	thumb_func_start ov11_02238ABC
ov11_02238ABC: ; 0x02238ABC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r6, r0, #0
	ldr r1, [r5, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	ldr r3, _02238B68 ; =0x00002DEC
	add r0, r5, r0
	ldrh r4, [r0, r3]
	cmp r4, #0
	beq _02238AF0
	add r2, r3, #2
	ldrh r2, [r0, r2]
	sub r3, #0xa0
	lsl r2, r2, #1
	add r0, r0, r2
	ldrh r0, [r0, r3]
	cmp r4, r0
	beq _02238AF8
_02238AF0:
	add r0, r5, #0
	bl ov11_0224683C
	add r4, r0, #0
_02238AF8:
	ldr r0, [r5, #0x6c]
	lsl r1, r0, #4
	add r2, r5, r1
	ldr r1, _02238B6C ; =0x000021A8
	ldr r1, [r2, r1]
	cmp r1, #0x27
	beq _02238B5C
	lsl r0, r0, #6
	add r1, r5, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bne _02238B5C
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0224C0F0
	cmp r0, #1
	bne _02238B5C
	lsl r0, r4, #4
	add r1, r5, r0
	ldr r0, _02238B70 ; =0x000003E1
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _02238B5C
	ldr r2, [r5, #0x64]
	ldr r3, _02238B74 ; =0x00002DCC
	add r0, r2, #0
	mov r6, #0xc0
	add r1, r5, r3
	mul r0, r6
	mov r2, #1
	ldr r7, [r1, r0]
	lsl r2, r2, #0x1e
	orr r2, r7
	str r2, [r1, r0]
	add r0, r6, #0
	add r0, #0xb4
	ldr r2, [r5, r0]
	ldr r0, [r5, #0x64]
	add r3, #0x10
	add r1, r0, #0
	mul r1, r6
	add r0, r5, r1
	str r2, [r0, r3]
	add r6, #0x64
	str r4, [r5, r6]
	b _02238B64
_02238B5C:
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_0223A424
_02238B64:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02238B68: .word 0x00002DEC
_02238B6C: .word 0x000021A8
_02238B70: .word 0x000003E1
_02238B74: .word 0x00002DCC

	thumb_func_start ov11_02238B78
ov11_02238B78: ; 0x02238B78
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	ldr r0, _02238BC8 ; =0x00003048
	ldr r0, [r5, r0]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl ov11_02246BE8
	cmp r0, #0
	bne _02238BBC
	ldr r0, _02238BC8 ; =0x00003048
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _02238BBC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl ov11_0224C07C
	cmp r0, #1
	bne _02238BBC
	ldr r0, _02238BC8 ; =0x00003048
	ldr r1, [r5, r0]
	mov r0, #0x49
	lsl r0, r0, #2
	str r1, [r5, r0]
	b _02238BC4
_02238BBC:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223A424
_02238BC4:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02238BC8: .word 0x00003048

	thumb_func_start ov11_02238BCC
ov11_02238BCC: ; 0x02238BCC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	ldr r5, _02238C1C ; =0x00002D58
	mov r1, #0
	ldr r3, [r4, #0x6c]
	mov r2, #0xc0
	mul r2, r3
	add r3, r4, r2
	add r0, r1, #0
	add r2, r3, #0
	add r6, r5, #0
_02238BEA:
	ldrsb r7, [r2, r6]
	cmp r7, #6
	ble _02238BF8
	add r7, r3, r0
	ldrsb r7, [r7, r5]
	sub r7, r7, #6
	add r1, r1, r7
_02238BF8:
	add r0, r0, #1
	add r2, r2, #1
	cmp r0, #8
	blt _02238BEA
	mov r0, #0x14
	add r2, r1, #0
	mul r2, r0
	ldr r0, _02238C20 ; =0x00002154
	add r2, #0x3c
	str r2, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0xc8
	ble _02238C16
	mov r1, #0xc8
	str r1, [r4, r0]
_02238C16:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02238C1C: .word 0x00002D58
_02238C20: .word 0x00002154

	thumb_func_start ov11_02238C24
ov11_02238C24: ; 0x02238C24
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	ldr r1, [r5, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	ldr r6, _02238C94 ; =0x00002DEC
	add r2, r5, r0
	ldrh r0, [r2, r6]
	cmp r0, #0
	beq _02238C58
	add r3, r6, #2
	ldrh r3, [r2, r3]
	sub r6, #0xa0
	lsl r3, r3, #1
	add r2, r2, r3
	ldrh r2, [r2, r6]
	cmp r0, r2
	beq _02238C5E
_02238C58:
	add r0, r5, #0
	bl ov11_0224683C
_02238C5E:
	ldr r1, [r5, #0x6c]
	lsl r2, r1, #4
	add r3, r5, r2
	ldr r2, _02238C98 ; =0x000021A8
	ldr r2, [r3, r2]
	cmp r2, #0x27
	beq _02238C88
	lsl r0, r0, #4
	add r2, r5, r0
	ldr r0, _02238C9C ; =0x000003E1
	ldrb r0, [r2, r0]
	cmp r0, #0
	bne _02238C90
	lsl r0, r1, #6
	add r1, r5, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bne _02238C90
_02238C88:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223A424
_02238C90:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_02238C94: .word 0x00002DEC
_02238C98: .word 0x000021A8
_02238C9C: .word 0x000003E1

	thumb_func_start ov11_02238CA0
ov11_02238CA0: ; 0x02238CA0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r7, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp, #8]
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp, #4]
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp]
	ldr r2, [sp, #8]
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r7, #0
	bl ov11_02230270
	ldr r1, [sp, #4]
	cmp r1, #0
	beq _02238CF2
	cmp r1, #1
	beq _02238CF2
	cmp r1, #2
	beq _02238D70
	b _02238E4A
_02238CF2:
	cmp r6, #5
	bls _02238CF8
	b _02238E4A
_02238CF8:
	add r1, r6, r6
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02238D04: ; jump table
	.short _02238D10 - _02238D04 - 2 ; case 0
	.short _02238D20 - _02238D04 - 2 ; case 1
	.short _02238D30 - _02238D04 - 2 ; case 2
	.short _02238D40 - _02238D04 - 2 ; case 3
	.short _02238D50 - _02238D04 - 2 ; case 4
	.short _02238D60 - _02238D04 - 2 ; case 5
_02238D10:
	lsl r0, r0, #3
	add r1, r4, r0
	mov r0, #0x71
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1b
	lsr r5, r0, #0x1d
	b _02238E4A
_02238D20:
	lsl r0, r0, #3
	add r1, r4, r0
	mov r0, #0x71
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x16
	lsr r5, r0, #0x1d
	b _02238E4A
_02238D30:
	lsl r0, r0, #3
	add r1, r4, r0
	mov r0, #0x71
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x11
	lsr r5, r0, #0x1d
	b _02238E4A
_02238D40:
	lsl r0, r0, #3
	add r1, r4, r0
	mov r0, #0x71
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0xc
	lsr r5, r0, #0x1d
	b _02238E4A
_02238D50:
	lsl r0, r0, #3
	add r1, r4, r0
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1e
	lsr r5, r0, #0x1e
	b _02238E4A
_02238D60:
	lsl r0, r0, #3
	add r1, r4, r0
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r0, r0, #0x1c
	lsr r5, r0, #0x1e
	b _02238E4A
_02238D70:
	cmp r6, #5
	bhi _02238E4A
	add r1, r6, r6
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02238D80: ; jump table
	.short _02238D8C - _02238D80 - 2 ; case 0
	.short _02238DAC - _02238D80 - 2 ; case 1
	.short _02238DCC - _02238D80 - 2 ; case 2
	.short _02238DEC - _02238D80 - 2 ; case 3
	.short _02238E0C - _02238D80 - 2 ; case 4
	.short _02238E2C - _02238D80 - 2 ; case 5
_02238D8C:
	mov r2, #0x71
	lsl r2, r2, #2
	add r6, r4, r2
	lsl r3, r0, #3
	ldr r7, [r6, r3]
	mov r1, #0x1c
	bic r7, r1
	sub r2, #8
	str r7, [r6, r3]
	add r3, r4, r2
	lsl r2, r0, #2
	ldr r1, [r3, r2]
	mov r0, #1
	bic r1, r0
	str r1, [r3, r2]
	b _02238E4A
_02238DAC:
	mov r2, #0x71
	lsl r2, r2, #2
	add r6, r4, r2
	lsl r7, r0, #3
	ldr r3, [r6, r7]
	ldr r1, _02238E74 ; =0xFFFFFC7F
	sub r2, #8
	and r1, r3
	add r3, r4, r2
	lsl r2, r0, #2
	str r1, [r6, r7]
	ldr r1, [r3, r2]
	mov r0, #2
	bic r1, r0
	str r1, [r3, r2]
	b _02238E4A
_02238DCC:
	mov r2, #0x71
	lsl r2, r2, #2
	add r6, r4, r2
	lsl r7, r0, #3
	ldr r3, [r6, r7]
	ldr r1, _02238E78 ; =0xFFFF8FFF
	sub r2, #8
	and r1, r3
	add r3, r4, r2
	lsl r2, r0, #2
	str r1, [r6, r7]
	ldr r1, [r3, r2]
	mov r0, #0x40
	bic r1, r0
	str r1, [r3, r2]
	b _02238E4A
_02238DEC:
	mov r2, #0x71
	lsl r2, r2, #2
	add r6, r4, r2
	lsl r7, r0, #3
	ldr r3, [r6, r7]
	ldr r1, _02238E7C ; =0xFFF1FFFF
	sub r2, #8
	and r1, r3
	add r3, r4, r2
	lsl r2, r0, #2
	str r1, [r6, r7]
	ldr r1, [r3, r2]
	mov r0, #8
	bic r1, r0
	str r1, [r3, r2]
	b _02238E4A
_02238E0C:
	mov r2, #0x72
	lsl r2, r2, #2
	add r6, r4, r2
	lsl r3, r0, #3
	ldr r7, [r6, r3]
	mov r1, #3
	bic r7, r1
	sub r2, #0xc
	str r7, [r6, r3]
	add r3, r4, r2
	lsl r2, r0, #2
	ldr r1, [r3, r2]
	mov r0, #4
	bic r1, r0
	str r1, [r3, r2]
	b _02238E4A
_02238E2C:
	mov r2, #0x72
	lsl r2, r2, #2
	add r6, r4, r2
	lsl r3, r0, #3
	ldr r7, [r6, r3]
	mov r1, #0xc
	bic r7, r1
	sub r2, #0xc
	str r7, [r6, r3]
	lsl r3, r0, #2
	add r1, r4, r2
	ldr r2, [r1, r3]
	ldr r0, _02238E80 ; =0xFFFFFBFF
	and r0, r2
	str r0, [r1, r3]
_02238E4A:
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _02238E5C
	cmp r5, #0
	bne _02238E5C
	ldr r1, [sp]
	add r0, r4, #0
	bl ov11_0223A424
_02238E5C:
	ldr r0, [sp, #4]
	cmp r0, #1
	bne _02238E6E
	cmp r5, #0
	beq _02238E6E
	ldr r1, [sp]
	add r0, r4, #0
	bl ov11_0223A424
_02238E6E:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02238E74: .word 0xFFFFFC7F
_02238E78: .word 0xFFFF8FFF
_02238E7C: .word 0xFFF1FFFF
_02238E80: .word 0xFFFFFBFF

	thumb_func_start ov11_02238E84
ov11_02238E84: ; 0x02238E84
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r1, r0, #0
	ldr r0, [r4, #0x6c]
	lsl r0, r0, #6
	add r2, r4, r0
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r0, [r2, r0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	bne _02238EB0
	add r0, r4, #0
	bl ov11_0223A424
_02238EB0:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start ov11_02238EB4
ov11_02238EB4: ; 0x02238EB4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r1, r0, #0
	ldr r0, [r4, #0x6c]
	mov r2, #0xc0
	add r3, r0, #0
	mul r3, r2
	add r5, r4, r3
	ldr r3, _02238EFC ; =0x00002DAC
	ldr r0, [r5, r3]
	cmp r0, #0
	bne _02238EF2
	add r0, r3, #4
	ldr r5, [r5, r0]
	mov r0, #1
	lsl r0, r0, #0x18
	tst r0, r5
	bne _02238EF2
	ldr r0, [r4, #0x64]
	mul r2, r0
	add r0, r4, r2
	ldr r0, [r0, r3]
	cmp r0, #0
	bne _02238EF8
_02238EF2:
	add r0, r4, #0
	bl ov11_0223A424
_02238EF8:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02238EFC: .word 0x00002DAC

	thumb_func_start ov11_02238F00
ov11_02238F00: ; 0x02238F00
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	ldr r2, [r4, #0x64]
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_022473F8
	ldr r2, [r4, #0x64]
	mov r1, #0xc0
	mul r1, r2
	add r2, r4, r1
	ldr r1, _02238F48 ; =0x00002DCC
	ldr r1, [r2, r1]
	lsl r1, r1, #0x13
	lsr r2, r1, #0x1d
	sub r1, r0, #1
	cmp r2, r1
	blo _02238F3A
	cmp r0, #2
	bge _02238F42
_02238F3A:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
_02238F42:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_02238F48: .word 0x00002DCC

	thumb_func_start ov11_02238F4C
ov11_02238F4C: ; 0x02238F4C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	ldr r1, [r4, #0x64]
	add r0, r5, #0
	bl ov11_02230270
	mov r2, #0x72
	mov r1, #1
	add r3, r0, #0
	eor r3, r1
	lsl r0, r3, #3
	add r5, r4, r0
	lsl r2, r2, #2
	ldr r5, [r5, r2]
	lsl r5, r5, #0x1c
	lsr r5, r5, #0x1e
	cmp r5, #2
	bne _02238FA2
	mov r0, #0xb5
	lsl r0, r0, #2
	add r2, r4, r0
	ldr r3, [r4, #0x64]
	mov r0, #0x1c
	mul r0, r3
	ldr r5, [r2, r0]
	mov r3, #1
	bic r5, r3
	orr r1, r5
	str r1, [r2, r0]
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
	b _02238FCA
_02238FA2:
	add r5, r2, #0
	sub r5, #0xc
	add r5, r4, r5
	lsl r3, r3, #2
	ldr r6, [r5, r3]
	lsl r1, r1, #0xa
	orr r1, r6
	str r1, [r5, r3]
	add r2, r4, r2
	ldr r4, [r2, r0]
	mov r3, #0xc
	add r1, r4, #0
	bic r1, r3
	lsl r3, r4, #0x1c
	lsr r3, r3, #0x1e
	add r3, r3, #1
	lsl r3, r3, #0x1e
	lsr r3, r3, #0x1c
	orr r1, r3
	str r1, [r2, r0]
_02238FCA:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_02238FD0
ov11_02238FD0: ; 0x02238FD0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r5, #0
	add r2, r6, #0
	bl ov11_0223C230
	add r7, r0, #0
	add r0, r4, #0
	add r1, r7, #0
	bl ov11_02230270
	mov r1, #0x72
	lsl r1, r1, #2
	add r4, r5, r1
	lsl r6, r0, #3
	str r0, [sp]
	ldr r0, [r4, r6]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1e
	beq _0223906A
	sub r1, #0x94
	str r0, [r5, r1]
	add r0, r5, #0
	mov r1, #6
	add r0, #0x88
	str r1, [r0]
	add r0, r5, #0
	add r0, #0x94
	str r7, [r0]
	ldr r1, [r5, #0x78]
	add r0, r5, #0
	mov r2, #0x1b
	mov r3, #0
	bl ov11_02243420
	cmp r0, #3
	beq _02239048
	ldr r1, [r5, #0x78]
	add r0, r5, #0
	mov r2, #0x1c
	mov r3, #0
	bl ov11_02243420
	cmp r0, #3
	bne _02239072
_02239048:
	mov r0, #0x6f
	ldr r1, [sp]
	lsl r0, r0, #2
	add r2, r5, r0
	lsl r1, r1, #2
	ldr r7, [r2, r1]
	ldr r3, _02239078 ; =0xFFFFFBFF
	sub r0, #0x88
	and r3, r7
	str r3, [r2, r1]
	ldr r2, [r4, r6]
	mov r1, #0xc
	bic r2, r1
	str r2, [r4, r6]
	mov r1, #0
	str r1, [r5, r0]
	b _02239072
_0223906A:
	ldr r1, [sp, #4]
	add r0, r5, #0
	bl ov11_0223A424
_02239072:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02239078: .word 0xFFFFFBFF

	thumb_func_start ov11_0223907C
ov11_0223907C: ; 0x0223907C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	str r0, [sp, #8]
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	str r0, [sp, #4]
	cmp r4, #0
	bne _0223912C
	add r0, r6, #0
	bl ov11_0222FF84
	mov r6, #0
	str r0, [sp]
	cmp r0, #0
	ble _02239194
_022390BE:
	ldr r0, _0223919C ; =0x000021EC
	add r1, r5, r6
	ldrb r4, [r1, r0]
	ldr r0, [sp, #8]
	cmp r0, #0
	bne _022390F6
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	add r2, r4, #0
	add r3, r7, #0
	bl ov11_02246D84
	cmp r0, #1
	bne _02239122
	mov r0, #0xc0
	mul r0, r4
	add r1, r5, r0
	ldr r0, _022391A0 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02239122
	ldr r1, [sp, #4]
	add r0, r5, #0
	bl ov11_0223A424
	add r5, #0x80
	str r4, [r5]
	b _02239194
_022390F6:
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	add r2, r4, #0
	add r3, r7, #0
	bl ov11_02246D84
	cmp r0, #0
	beq _02239114
	mov r0, #0xc0
	mul r0, r4
	add r1, r5, r0
	ldr r0, _022391A0 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _02239122
_02239114:
	ldr r1, [sp, #4]
	add r0, r5, #0
	bl ov11_0223A424
	add r5, #0x80
	str r4, [r5]
	b _02239194
_02239122:
	ldr r0, [sp]
	add r6, r6, #1
	cmp r6, r0
	blt _022390BE
	b _02239194
_0223912C:
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl ov11_0223C230
	add r4, r0, #0
	ldr r0, [sp, #8]
	cmp r0, #0
	bne _0223916A
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	add r2, r4, #0
	add r3, r7, #0
	bl ov11_02246D84
	cmp r0, #1
	bne _02239194
	mov r0, #0xc0
	mul r0, r4
	add r1, r5, r0
	ldr r0, _022391A0 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02239194
	ldr r1, [sp, #4]
	add r0, r5, #0
	bl ov11_0223A424
	add r5, #0x80
	str r4, [r5]
	b _02239194
_0223916A:
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	add r2, r4, #0
	add r3, r7, #0
	bl ov11_02246D84
	cmp r0, #0
	beq _02239188
	mov r0, #0xc0
	mul r0, r4
	add r1, r5, r0
	ldr r0, _022391A0 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _02239194
_02239188:
	ldr r1, [sp, #4]
	add r0, r5, #0
	bl ov11_0223A424
	add r5, #0x80
	str r4, [r5]
_02239194:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_0223919C: .word 0x000021EC
_022391A0: .word 0x00002D8C

	thumb_func_start ov11_022391A4
ov11_022391A4: ; 0x022391A4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0223C230
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r7, #0
	bl ov11_0223C230
	add r7, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_02230270
	add r6, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	bl ov11_02230270
	cmp r6, r0
	bne _02239200
	ldr r1, [sp]
	add r0, r4, #0
	bl ov11_0223A424
_02239200:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_02239204
ov11_02239204: ; 0x02239204
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp]
	add r0, r1, #0
	mov r1, #1
	bl ov11_0223A424
	mov r7, #0
	ldr r0, [sp]
	add r1, r7, #0
	bl ov11_0222FFC8
	cmp r0, #0
	bgt _02239222
	b _02239360
_02239222:
	ldr r0, [sp]
	mov r1, #0
	add r2, r7, #0
	bl ov11_02230014
	mov r1, #0xad
	mov r2, #0
	add r4, r0, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r0, r4, #0
	mov r1, #6
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0xa
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	cmp r0, #0x35
	bne _022392EC
	cmp r6, #0
	beq _022392EC
	ldr r0, _02239368 ; =0x000001EE
	cmp r6, r0
	beq _022392EC
	ldr r0, [sp, #8]
	cmp r0, #0
	bne _022392EC
	bl LCRandom
	mov r1, #0xa
	bl _s32_div_f
	cmp r1, #0
	bne _022392EC
	bl LCRandom
	mov r1, #0x64
	bl _s32_div_f
	add r5, r1, #0
	add r0, r4, #0
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	sub r0, r0, #1
	mov r1, #0xa
	bl _u32_div_f
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	cmp r2, #0xa
	blo _022392A4
	mov r2, #9
_022392A4:
	mov r1, #0
	ldr r3, _0223936C ; =ov11_0225DE150
	str r1, [sp, #0xc]
_022392AA:
	ldrb r0, [r3]
	cmp r0, r5
	ble _022392C4
	ldr r3, [sp, #0xc]
	ldr r5, _02239370 ; =ov11_0225DD24
	add r2, r2, r3
	lsl r2, r2, #1
	add r0, r4, #0
	mov r1, #6
	add r2, r5, r2
	bl SetMonData
	b _022392EC
_022392C4:
	cmp r5, #0x62
	blt _022392E2
	cmp r5, #0x63
	bgt _022392E2
	mov r3, #0x63
	sub r3, r3, r5
	add r2, r2, r3
	lsl r3, r2, #1
	ldr r2, _02239374 ; =ov11_0225DC48
	add r0, r4, #0
	mov r1, #6
	add r2, r2, r3
	bl SetMonData
	b _022392EC
_022392E2:
	add r1, r1, #1
	add r3, r3, #1
	str r1, [sp, #0xc]
	cmp r1, #9
	blt _022392AA
_022392EC:
	ldr r0, [sp, #4]
	cmp r0, #0x76
	bne _02239350
	cmp r6, #0
	beq _02239350
	ldr r0, _02239368 ; =0x000001EE
	cmp r6, r0
	beq _02239350
	ldr r0, [sp, #8]
	cmp r0, #0
	bne _02239350
	mov r2, #0
	add r0, r4, #0
	mov r1, #0xa0
	str r2, [sp, #0xc]
	mov r5, #0xa
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	cmp r1, #0xa
	ble _02239324
	ldr r0, [sp, #0xc]
_0223931A:
	add r5, #0xa
	add r0, r0, #1
	cmp r5, r1
	blt _0223931A
	str r0, [sp, #0xc]
_02239324:
	ldr r0, [sp, #0xc]
	cmp r0, #0xa
	blt _0223932E
	bl GF_AssertFail
_0223932E:
	bl LCRandom
	mov r1, #0x64
	bl _s32_div_f
	ldr r2, [sp, #0xc]
	ldr r0, _02239378 ; =ov11_0225DE15C
	ldrb r0, [r0, r2]
	cmp r1, r0
	bge _02239350
	mov r0, #0x5e
	str r0, [sp, #0xc]
	add r0, r4, #0
	mov r1, #6
	add r2, sp, #0xc
	bl SetMonData
_02239350:
	ldr r0, [sp]
	mov r1, #0
	add r7, r7, #1
	bl ov11_0222FFC8
	cmp r7, r0
	bge _02239360
	b _02239222
_02239360:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02239368: .word 0x000001EE
_0223936C: .word ov11_0225DE150
_02239370: .word ov11_0225DD24
_02239374: .word ov11_0225DC48
_02239378: .word ov11_0225E15C

	thumb_func_start ov11_0223937C
ov11_0223937C: ; 0x0223937C
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	mov r0, #0xb5
	ldr r1, [r4, #0x64]
	lsl r0, r0, #2
	add r3, r4, r0
	mov r0, #0x1c
	add r2, r1, #0
	mul r2, r0
	ldr r1, [r3, r2]
	mov r0, #0x10
	orr r0, r1
	str r0, [r3, r2]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_022393A4
ov11_022393A4: ; 0x022393A4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r4, #0
	bl ov11_02249B7C
	cmp r0, #1
	bne _022393E0
	add r0, r4, #0
	add r1, r7, #0
	bl ov11_0223A424
_022393E0:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_022393E4
ov11_022393E4: ; 0x022393E4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	str r0, [sp, #4]
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	add r7, r0, #0
	ldr r0, [sp]
	ldr r2, [sp, #4]
	add r1, r5, #0
	bl ov11_0223C230
	add r1, r0, #0
	cmp r6, #0
	bne _02239438
	add r0, r5, #0
	bl ov11_02249D90
	cmp r4, r0
	bne _0223944A
	add r0, r5, #0
	add r1, r7, #0
	bl ov11_0223A424
	b _0223944A
_02239438:
	add r0, r5, #0
	bl ov11_02249D90
	cmp r4, r0
	beq _0223944A
	add r0, r5, #0
	add r1, r7, #0
	bl ov11_0223A424
_0223944A:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_02239450
ov11_02239450: ; 0x02239450
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223A444
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r7, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r4, #0
	bl ov11_02249B4C
	add r1, r0, #0
	add r0, r4, #0
	mov r2, #1
	bl ov11_0224C12C
	str r0, [r6]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_0223949C
ov11_0223949C: ; 0x0223949C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223A444
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r7, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r4, #0
	bl ov11_02249B4C
	add r1, r0, #0
	add r0, r4, #0
	mov r2, #2
	bl ov11_0224C12C
	str r0, [r6]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_022394E8
ov11_022394E8: ; 0x022394E8
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r6, r0, #0
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl ov11_02246D1C
	cmp r0, #0x79
	bne _02239516
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_0223A424
	mov r0, #0
	pop {r4, r5, r6, pc}
_02239516:
	add r0, r4, #0
	bl ov11_02230294
	ldr r1, _02239570 ; =ov11_0225E168
	mov r2, #0x1b
	ldrb r4, [r1, r0]
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	mov r3, #0
	bl ov11_02243420
	cmp r4, r0
	beq _02239564
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	mov r2, #0x1c
	mov r3, #0
	bl ov11_02243420
	cmp r4, r0
	beq _02239564
	ldr r1, [r5, #0x64]
	lsl r0, r4, #0x18
	add r3, r1, #0
	mov r2, #0xc0
	mul r3, r2
	ldr r1, _02239574 ; =0x00002D64
	lsr r0, r0, #0x18
	add r3, r5, r3
	strb r0, [r3, r1]
	ldr r3, [r5, #0x64]
	add r1, r1, #1
	add r6, r3, #0
	mul r6, r2
	add r3, r5, r6
	strb r0, [r3, r1]
	add r2, #0x70
	str r4, [r5, r2]
	b _0223956C
_02239564:
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_0223A424
_0223956C:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_02239570: .word ov11_0225E168
_02239574: .word 0x00002D64

	thumb_func_start ov11_02239578
ov11_02239578: ; 0x02239578
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_02230294
	lsl r1, r0, #1
	ldr r0, _0223959C ; =ov11_0225DD0A
	ldrh r1, [r0, r1]
	mov r0, #0x49
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223959C: .word ov11_0225DD0A

	thumb_func_start ov11_022395A0
ov11_022395A0: ; 0x022395A0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_02230294
	lsl r1, r0, #2
	ldr r0, _022395C4 ; =ov11_0225DD48
	ldr r1, [r0, r1]
	ldr r0, _022395C8 ; =0x00002174
	str r1, [r4, r0]
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_022395C4: .word ov11_0225DD48
_022395C8: .word 0x00002174

	thumb_func_start ov11_022395CC
ov11_022395CC: ; 0x022395CC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r5, r0, #0
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl ov11_02249DF0
	cmp r0, #0
	beq _022395FE
	ldr r1, _0223960C ; =0x00002154
	str r0, [r4, r1]
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	bl ov11_02249E04
	ldr r1, _02239610 ; =0x00002160
	str r0, [r4, r1]
	b _02239606
_022395FE:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0223A424
_02239606:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_0223960C: .word 0x00002154
_02239610: .word 0x00002160

	thumb_func_start ov11_02239614
ov11_02239614: ; 0x02239614
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	ldr r2, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r2
	add r1, r4, r0
	ldr r0, _02239674 ; =0x00002DB8
	ldrh r0, [r1, r0]
	cmp r0, #0
	beq _0223965A
	ldr r1, [r4, #0x64]
	add r0, r4, #0
	mov r3, #0x3c
	bl ov11_02246D84
	cmp r0, #1
	bne _0223965A
	add r0, r4, #0
	add r1, r7, #0
	bl ov11_0223A424
	b _02239670
_0223965A:
	ldr r2, [r4, #0x6c]
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02249F8C
	cmp r0, #1
	beq _02239670
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
_02239670:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02239674: .word 0x00002DB8

	thumb_func_start ov11_02239678
ov11_02239678: ; 0x02239678
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	ldr r2, [r4, #0x64]
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0224A4E0
	cmp r0, #1
	beq _022396A4
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
_022396A4:
	mov r0, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov11_022396A8
ov11_022396A8: ; 0x022396A8
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp]
	mov r2, #0
	str r2, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	add r3, r2, #0
	str r2, [sp, #8]
	bl ov11_02255980
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_022396D8
ov11_022396D8: ; 0x022396D8
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r0, r5, #0
	mov r1, #0
	bl ov11_0224AD90
	add r4, r0, #0
	beq _02239714
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	add r1, r0, #0
	cmp r4, #0xff
	bne _0223970C
	add r0, r5, #0
	bl ov11_0223A424
	b _02239714
_0223970C:
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_0223A424
_02239714:
	mov r0, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov11_02239718
ov11_02239718: ; 0x02239718
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	bl ov11_0222FF84
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	mov r2, #0
	str r2, [sp]
	mov r0, #6
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	add r3, r2, #0
	bl ov11_022558E0
	mov r0, #0
	str r0, [r4, #0x78]
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02239748
ov11_02239748: ; 0x02239748
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #0
	bl ov11_0224AD90
	add r5, r0, #0
	beq _0223977A
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r1, r0, #0
	cmp r5, #0xff
	bne _02239774
	add r0, r4, #0
	bl ov11_0223A424
	b _0223977A
_02239774:
	ldr r0, _02239780 ; =0x000021A0
	sub r1, r5, #1
	strb r1, [r4, r0]
_0223977A:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02239780: .word 0x000021A0

	thumb_func_start ov11_02239784
ov11_02239784: ; 0x02239784
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0222FF74
	mov r1, #4
	tst r0, r1
	beq _022397A2
	add r0, r4, #0
	bl ov11_02256774
_022397A2:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_022397A8
ov11_022397A8: ; 0x022397A8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	str r0, [sp]
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl ov11_0223C230
	add r4, r0, #0
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_02230270
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x1b
	mov r3, #0
	bl ov11_02243420
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x1c
	mov r3, #0
	bl ov11_02243420
	add r2, r0, #0
	lsl r0, r6, #2
	add r1, r5, r0
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r1, [r1, r0]
	mov r0, #0x80
	tst r0, r1
	beq _0223989C
	mov r0, #0xc0
	add r6, r4, #0
	mul r6, r0
	ldr r0, _022398A8 ; =0x00002D8C
	add r1, r5, r6
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223989C
	lsl r1, r7, #0x18
	lsl r2, r2, #0x18
	mov r0, #5
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl ov11_02246B9C
	cmp r0, #0x14
	bgt _0223983A
	bge _02239862
	cmp r0, #0
	bgt _02239834
	beq _02239872
	b _0223987E
_02239834:
	cmp r0, #0xa
	beq _0223986A
	b _0223987E
_0223983A:
	cmp r0, #0x50
	bgt _02239846
	bge _02239852
	cmp r0, #0x28
	beq _0223985A
	b _0223987E
_02239846:
	cmp r0, #0xa0
	bne _0223987E
	ldr r0, _022398AC ; =0x0000215C
	mov r1, #2
	str r1, [r5, r0]
	b _02239882
_02239852:
	ldr r0, _022398AC ; =0x0000215C
	mov r1, #4
	str r1, [r5, r0]
	b _02239882
_0223985A:
	ldr r0, _022398AC ; =0x0000215C
	mov r1, #8
	str r1, [r5, r0]
	b _02239882
_02239862:
	ldr r0, _022398AC ; =0x0000215C
	mov r1, #0x10
	str r1, [r5, r0]
	b _02239882
_0223986A:
	ldr r0, _022398AC ; =0x0000215C
	mov r1, #0x20
	str r1, [r5, r0]
	b _02239882
_02239872:
	ldr r1, [sp]
	add r0, r5, #0
	bl ov11_0223A424
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223987E:
	bl GF_AssertFail
_02239882:
	ldr r0, _022398B0 ; =0x00002D90
	add r1, r5, r6
	ldr r1, [r1, r0]
	mov r0, #0
	mvn r0, r0
	mul r0, r1
	ldr r1, _022398AC ; =0x0000215C
	ldr r1, [r5, r1]
	bl ov11_022476C0
	ldr r1, _022398AC ; =0x0000215C
	str r0, [r5, r1]
	b _022398A4
_0223989C:
	ldr r1, [sp]
	add r0, r5, #0
	bl ov11_0223A424
_022398A4:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022398A8: .word 0x00002D8C
_022398AC: .word 0x0000215C
_022398B0: .word 0x00002D90

	thumb_func_start ov11_022398B4
ov11_022398B4: ; 0x022398B4
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r6, r0, #0
	ldr r1, [r5, #0x64]
	add r0, r5, #0
	bl ov11_02246D1C
	cmp r0, #0x20
	ldr r0, _0223992C ; =0x00003044
	bne _022398E6
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _02239930 ; =0x000003E5
	ldrb r0, [r1, r0]
	lsl r0, r0, #0x11
	lsr r4, r0, #0x10
	b _022398F0
_022398E6:
	ldr r0, [r5, r0]
	lsl r0, r0, #4
	add r1, r5, r0
	ldr r0, _02239930 ; =0x000003E5
	ldrb r4, [r1, r0]
_022398F0:
	cmp r4, #0
	bne _022398F8
	bl GF_AssertFail
_022398F8:
	bl LCRandom
	mov r1, #0x64
	bl _s32_div_f
	cmp r1, r4
	bge _0223991E
	add r0, r5, #0
	add r0, #0x94
	ldr r1, [r0]
	mov r0, #0xc0
	mul r0, r1
	add r1, r5, r0
	ldr r0, _02239934 ; =0x00002D8C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223991E
	mov r0, #0
	pop {r4, r5, r6, pc}
_0223991E:
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_0223A424
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_0223992C: .word 0x00003044
_02239930: .word 0x000003E5
_02239934: .word 0x00002D8C

	thumb_func_start ov11_02239938
ov11_02239938: ; 0x02239938
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r6, r0, #0
	mov r3, #0xb5
	mov r2, #0xc0
	ldr r1, [r5, #0x64]
	mov r0, #0xc0
	mul r0, r1
	add r0, r5, r0
	lsl r3, r3, #6
	ldrh r4, [r0, r3]
	add r2, #0xf9
	cmp r4, r2
	bne _022399BA
	ldr r4, [r5, #0x6c]
	mov r2, #0xc0
	mul r2, r4
	add r4, r5, r2
	add r2, r3, #0
	add r2, #0x4c
	ldr r2, [r4, r2]
	cmp r2, #0
	beq _022399BA
	add r3, #0x70
	ldr r2, [r0, r3]
	mov r0, #2
	lsl r0, r0, #0x14
	tst r0, r2
	bne _022399BA
	add r0, r7, #0
	bl ov11_02230E88
	bl sub_02005EE0
	cmp r0, #0
	beq _02239998
	cmp r0, #1
	beq _0223999C
	cmp r0, #2
	beq _022399A0
_02239998:
	mov r4, #0
	b _022399A2
_0223999C:
	mov r4, #0xa
	b _022399A2
_022399A0:
	mov r4, #0x1e
_022399A2:
	bl LCRandom
	mov r1, #0x64
	bl _s32_div_f
	cmp r1, r4
	ble _022399C2
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_0223A424
	b _022399C2
_022399BA:
	add r0, r5, #0
	add r1, r6, #0
	bl ov11_0223A424
_022399C2:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_022399C8
ov11_022399C8: ; 0x022399C8
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r1, r0, #0
	ldr r0, _022399F8 ; =0x000003DE
	add r2, r4, r0
	ldr r0, _022399FC ; =0x00003044
	ldr r0, [r4, r0]
	lsl r0, r0, #4
	add r0, r2, r0
	bl GetAttrFromWazaTbl
	mov r1, #0x4d
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0
	pop {r4, pc}
	nop
_022399F8: .word 0x000003DE
_022399FC: .word 0x00003044

	thumb_func_start ov11_02239A00
ov11_02239A00: ; 0x02239A00
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0223C230
	add r1, r0, #0
	ldr r3, [sp]
	add r0, r5, #0
	add r2, r7, #0
	bl ov11_022562E4
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_02239A40
ov11_02239A40: ; 0x02239A40
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r5, #0
	bl ov11_02256308
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02239A6C
ov11_02239A6C: ; 0x02239A6C
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	mov r1, #0
	bl ov11_02256398
	mov r0, #0
	pop {r4, pc}

	thumb_func_start ov11_02239A84
ov11_02239A84: ; 0x02239A84
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r1, r0, #0
	mov r0, #0x4a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r2, _02239AC0 ; =0x0000219C
	str r0, [sp]
	add r3, r4, r1
	ldrb r2, [r3, r2]
	add r0, r5, #0
	mov r3, #0
	bl ov11_02230370
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02239AC0: .word 0x0000219C

	thumb_func_start ov11_02239AC4
ov11_02239AC4: ; 0x02239AC4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0223C230
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_022470B8
	cmp r0, #0
	beq _02239B02
	add r0, r4, #0
	add r1, r7, #0
	bl ov11_0223A424
_02239B02:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_02239B08
ov11_02239B08: ; 0x02239B08
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r5, #0
	bl ov11_022563D0
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02239B34
ov11_02239B34: ; 0x02239B34
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r5, #0
	bl ov11_022563F8
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02239B60
ov11_02239B60: ; 0x02239B60
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r5, #0
	bl ov11_02256420
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02239B8C
ov11_02239B8C: ; 0x02239B8C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r5, #0
	bl ov11_02256448
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02239BB8
ov11_02239BB8: ; 0x02239BB8
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_02256470
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_02239BD0
ov11_02239BD0: ; 0x02239BD0
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0225648C
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_02239BE8
ov11_02239BE8: ; 0x02239BE8
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0223C230
	add r1, r0, #0
	ldr r3, [sp]
	add r0, r5, #0
	add r2, r7, #0
	bl ov11_022564A8
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_02239C28
ov11_02239C28: ; 0x02239C28
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_022564F4
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_02239C54
ov11_02239C54: ; 0x02239C54
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	mov r2, #0x4e
	lsl r2, r2, #2
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r4, r2
	bl ov11_02248308
	cmp r0, #0
	bne _02239C84
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
_02239C84:
	mov r0, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov11_02239C88
ov11_02239C88: ; 0x02239C88
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r4, r0, #0
	bl ov11_0222FF84
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r2, r0, #0
	cmp r2, #3
	beq _02239CAE
	cmp r2, #4
	beq _02239CD6
	b _02239CFE
_02239CAE:
	mov r5, #0
	cmp r6, #0
	ble _02239D0E
	mov r7, #1
_02239CB6:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _02239D14 ; =0x00000195
	ldrb r0, [r0, r1]
	tst r0, r7
	bne _02239CCE
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_022565A0
_02239CCE:
	add r5, r5, #1
	cmp r5, r6
	blt _02239CB6
	b _02239D0E
_02239CD6:
	mov r5, #0
	cmp r6, #0
	ble _02239D0E
	mov r7, #1
_02239CDE:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _02239D14 ; =0x00000195
	ldrb r0, [r0, r1]
	tst r0, r7
	beq _02239CF6
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_022565A0
_02239CF6:
	add r5, r5, #1
	cmp r5, r6
	blt _02239CDE
	b _02239D0E
_02239CFE:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r4, #0
	bl ov11_022565A0
_02239D0E:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02239D14: .word 0x00000195

	thumb_func_start ov11_02239D18
ov11_02239D18: ; 0x02239D18
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r4, r0, #0
	bl ov11_0222FF84
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r2, r0, #0
	cmp r2, #3
	beq _02239D3E
	cmp r2, #4
	beq _02239D66
	b _02239D8E
_02239D3E:
	mov r5, #0
	cmp r6, #0
	ble _02239D9E
	mov r7, #1
_02239D46:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _02239DA4 ; =0x00000195
	ldrb r0, [r0, r1]
	tst r0, r7
	bne _02239D5E
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_022565BC
_02239D5E:
	add r5, r5, #1
	cmp r5, r6
	blt _02239D46
	b _02239D9E
_02239D66:
	mov r5, #0
	cmp r6, #0
	ble _02239D9E
	mov r7, #1
_02239D6E:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _02239DA4 ; =0x00000195
	ldrb r0, [r0, r1]
	tst r0, r7
	beq _02239D86
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_022565BC
_02239D86:
	add r5, r5, #1
	cmp r5, r6
	blt _02239D6E
	b _02239D9E
_02239D8E:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r4, #0
	bl ov11_022565BC
_02239D9E:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02239DA4: .word 0x00000195

	thumb_func_start ov11_02239DA8
ov11_02239DA8: ; 0x02239DA8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r0, [sp]
	str r1, [sp, #4]
	add r0, r1, #0
	mov r1, #1
	mov r5, #0
	bl ov11_0223A424
	ldr r0, [sp, #4]
	bl ov11_0223A404
	add r4, r0, #0
	ldr r0, [sp, #4]
	bl ov11_0223A404
	str r0, [sp, #0x14]
	ldr r0, [sp]
	bl ov11_0222FF74
	str r0, [sp, #0xc]
	ldr r0, [sp]
	ldr r1, [sp, #4]
	add r2, r4, #0
	bl ov11_0223C230
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xc]
	mov r1, #8
	tst r0, r1
	bne _02239DFA
	ldr r0, [sp, #0xc]
	mov r1, #0x10
	tst r0, r1
	beq _02239EDA
	ldr r0, [sp]
	ldr r1, [sp, #0x10]
	bl ov11_02230270
	cmp r0, #0
	beq _02239EDA
_02239DFA:
	ldr r0, [sp]
	ldr r1, [sp, #0x10]
	bl ov11_0222FF88
	add r7, r0, #0
	ldr r0, [sp]
	ldr r1, [sp, #0x10]
	bl ov11_022302BC
	add r1, r0, #0
	ldr r0, [sp]
	bl ov11_0222FF88
	str r0, [sp, #8]
	ldr r0, [sp]
	ldr r1, [sp, #0x10]
	bl ov11_0222FF7C
	add r0, r7, #0
	mov r4, #0
	bl GetPartyCount
	cmp r0, #0
	ble _02239E68
_02239E2A:
	add r0, r7, #0
	add r1, r4, #0
	bl Party_GetMonByIndex
	mov r1, #0xad
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _02239E5C
	add r0, r6, #0
	mov r1, #0xad
	mov r2, #0
	bl GetMonData
	ldr r1, _02239F48 ; =0x000001EE
	cmp r0, r1
	beq _02239E5C
	add r0, r6, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	add r5, r5, r0
_02239E5C:
	add r0, r7, #0
	add r4, r4, #1
	bl GetPartyCount
	cmp r4, r0
	blt _02239E2A
_02239E68:
	ldr r0, [sp, #0xc]
	cmp r0, #0x4b
	beq _02239E76
	cmp r0, #0xcb
	beq _02239E76
	cmp r0, #0x4a
	bne _02239E82
_02239E76:
	ldr r0, [sp]
	ldr r1, [sp, #0x10]
	bl ov11_02230270
	cmp r0, #0
	beq _02239ECC
_02239E82:
	ldr r0, [sp, #8]
	mov r4, #0
	bl GetPartyCount
	cmp r0, #0
	ble _02239ECC
	ldr r7, _02239F48 ; =0x000001EE
_02239E90:
	ldr r0, [sp, #8]
	add r1, r4, #0
	bl Party_GetMonByIndex
	mov r1, #0xad
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _02239EC0
	add r0, r6, #0
	mov r1, #0xad
	mov r2, #0
	bl GetMonData
	cmp r0, r7
	beq _02239EC0
	add r0, r6, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	add r5, r5, r0
_02239EC0:
	ldr r0, [sp, #8]
	add r4, r4, #1
	bl GetPartyCount
	cmp r4, r0
	blt _02239E90
_02239ECC:
	cmp r5, #0
	bne _02239F42
	ldr r0, [sp, #4]
	ldr r1, [sp, #0x14]
	bl ov11_0223A424
	b _02239F42
_02239EDA:
	ldr r0, [sp]
	ldr r1, [sp, #0x10]
	bl ov11_0222FF88
	add r7, r0, #0
	ldr r0, [sp]
	ldr r1, [sp, #0x10]
	bl ov11_0222FF7C
	add r0, r7, #0
	mov r4, #0
	bl GetPartyCount
	cmp r0, #0
	ble _02239F36
_02239EF8:
	add r0, r7, #0
	add r1, r4, #0
	bl Party_GetMonByIndex
	mov r1, #0xad
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _02239F2A
	add r0, r6, #0
	mov r1, #0xad
	mov r2, #0
	bl GetMonData
	ldr r1, _02239F48 ; =0x000001EE
	cmp r0, r1
	beq _02239F2A
	add r0, r6, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	add r5, r5, r0
_02239F2A:
	add r0, r7, #0
	add r4, r4, #1
	bl GetPartyCount
	cmp r4, r0
	blt _02239EF8
_02239F36:
	cmp r5, #0
	bne _02239F42
	ldr r0, [sp, #4]
	ldr r1, [sp, #0x14]
	bl ov11_0223A424
_02239F42:
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02239F48: .word 0x000001EE

	thumb_func_start ov11_02239F4C
ov11_02239F4C: ; 0x02239F4C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r6, r1, #0
	add r0, r6, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r6, #0
	bl ov11_0223A404
	mov ip, r0
	ldr r1, [r6, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r0, r6, r0
	add r5, r0, #1
	ldr r7, _02239FC0 ; =0x00002D58
	mov r4, #0
	mov r3, #1
	add r0, sp, #0
_02239F74:
	ldrsb r1, [r5, r7]
	cmp r1, #0xc
	bge _02239F82
	lsl r1, r4, #2
	sub r2, r3, #1
	add r4, r4, #1
	str r2, [r0, r1]
_02239F82:
	add r3, r3, #1
	add r5, r5, #1
	cmp r3, #8
	blt _02239F74
	cmp r4, #0
	beq _02239FB0
	bl LCRandom
	add r1, r4, #0
	bl _s32_div_f
	lsl r1, r1, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	ldr r1, _02239FC4 ; =0x00002170
	add r0, #0x27
	str r0, [r6, r1]
	mov r0, #2
	ldr r2, [r6, r1]
	lsl r0, r0, #0x1e
	orr r0, r2
	str r0, [r6, r1]
	b _02239FB8
_02239FB0:
	add r0, r6, #0
	mov r1, ip
	bl ov11_0223A424
_02239FB8:
	mov r0, #0
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02239FC0: .word 0x00002D58
_02239FC4: .word 0x00002170

	thumb_func_start ov11_02239FC8
ov11_02239FC8: ; 0x02239FC8
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r7, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r2, r0, #0
	ldr r0, _0223A00C ; =0x00002DB8
	add r5, r2, #0
	add r6, r4, r0
	mov r0, #0xc0
	mul r5, r0
	lsl r0, r2, #1
	add r1, r4, r0
	ldrh r3, [r6, r5]
	ldr r0, _0223A010 ; =0x00003124
	strh r3, [r1, r0]
	mov r0, #0
	strh r0, [r6, r5]
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_02245190
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223A00C: .word 0x00002DB8
_0223A010: .word 0x00003124

	thumb_func_start ov11_0223A014
ov11_0223A014: ; 0x0223A014
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r1, r0, #0
	ldr r0, [r4, #0x64]
	ldr r2, _0223A054 ; =0x00003124
	lsl r0, r0, #1
	add r0, r4, r0
	ldrh r3, [r0, r2]
	cmp r3, #0
	beq _0223A048
	mov r0, #0x4a
	lsl r0, r0, #2
	str r3, [r4, r0]
	ldr r0, [r4, #0x64]
	mov r1, #0
	lsl r0, r0, #1
	add r0, r4, r0
	strh r1, [r0, r2]
	b _0223A04E
_0223A048:
	add r0, r4, #0
	bl ov11_0223A424
_0223A04E:
	mov r0, #0
	pop {r4, pc}
	nop
_0223A054: .word 0x00003124

	thumb_func_start ov11_0223A058
ov11_0223A058: ; 0x0223A058
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	mov r2, #0x4e
	lsl r2, r2, #2
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r4, r2
	bl ov11_02249B94
	cmp r0, #0
	bne _0223A088
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
_0223A088:
	mov r0, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov11_0223A08C
ov11_0223A08C: ; 0x0223A08C
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_022565D8
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_0223A0A4
ov11_0223A0A4: ; 0x0223A0A4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_022565F4
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_0223A0C0
ov11_0223A0C0: ; 0x0223A0C0
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0225664C
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_0223A0D8
ov11_0223A0D8: ; 0x0223A0D8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	mov r4, #0
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_0223C230
	add r7, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	bl ov11_02249D90
	add r6, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	bl ov11_02249DA4
	str r0, [sp]
	cmp r6, #0x40
	bne _0223A126
	bl LCRandom
	mov r1, #0x64
	bl _s32_div_f
	ldr r0, [sp]
	cmp r1, r0
	bge _0223A126
	mov r4, #1
_0223A126:
	cmp r6, #0x66
	bne _0223A13E
	mov r0, #0xc0
	mul r0, r7
	add r2, r5, r0
	ldr r0, _0223A170 ; =0x00002D8C
	ldr r1, [r2, r0]
	add r0, r0, #4
	ldr r0, [r2, r0]
	cmp r1, r0
	bne _0223A13E
	mov r4, #1
_0223A13E:
	cmp r4, #0
	beq _0223A16C
	mov r1, #0xc0
	add r0, r7, #0
	mul r0, r1
	add r2, r5, r0
	ldr r0, _0223A170 ; =0x00002D8C
	ldr r3, [r2, r0]
	ldr r2, _0223A174 ; =0x0000215C
	ldr r0, [r5, r2]
	add r0, r0, r3
	cmp r0, #0
	bgt _0223A16C
	sub r0, r3, #1
	neg r0, r0
	str r0, [r5, r2]
	add r0, r2, #0
	add r0, #0x10
	ldr r0, [r5, r0]
	add r1, #0x40
	orr r0, r1
	add r2, #0x10
	str r0, [r5, r2]
_0223A16C:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223A170: .word 0x00002D8C
_0223A174: .word 0x0000215C

	thumb_func_start ov11_0223A178
ov11_0223A178: ; 0x0223A178
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r5, #0
	bl ov11_0223A404
	add r4, r0, #0
	add r0, r5, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl ov11_0223C230
	add r1, r0, #0
	mov r0, #0xc0
	add r4, r1, #0
	mul r4, r0
	ldr r0, _0223A208 ; =0x00002D8C
	add r2, r5, r4
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _0223A1FA
	ldr r0, _0223A20C ; =0x0000219C
	add r2, r5, r1
	ldrb r2, [r2, r0]
	cmp r2, #6
	beq _0223A1FA
	add r0, r6, #0
	bl ov11_02230014
	add r6, r0, #0
	mov r1, #0xa
	mov r2, #0
	bl GetMonData
	str r0, [sp]
	add r0, r6, #0
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	add r2, r0, #0
	ldr r0, _0223A210 ; =0x00002D67
	add r1, r5, r4
	ldrb r0, [r1, r0]
	cmp r0, #0x1e
	beq _0223A202
	ldr r1, [sp]
	add r0, r5, #0
	bl ov11_02248A14
	cmp r0, #0
	bne _0223A202
	add r0, r5, #0
	add r1, r7, #0
	bl ov11_0223A424
	b _0223A202
_0223A1FA:
	add r0, r5, #0
	add r1, r7, #0
	bl ov11_0223A424
_0223A202:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223A208: .word 0x00002D8C
_0223A20C: .word 0x0000219C
_0223A210: .word 0x00002D67

	thumb_func_start ov11_0223A214
ov11_0223A214: ; 0x0223A214
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r7, #0
	bl ov11_0223C230
	mov r1, #0xc0
	mul r1, r0
	add r2, r4, r1
	ldr r1, _0223A26C ; =0x00002DB0
	ldr r2, [r2, r1]
	mov r1, #1
	lsl r1, r1, #0x18
	tst r1, r2
	bne _0223A260
	mov r1, #0x1c
	mul r1, r0
	mov r0, #0xba
	add r1, r4, r1
	lsl r0, r0, #2
	ldr r1, [r1, r0]
	mov r0, #8
	tst r0, r1
	beq _0223A268
_0223A260:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
_0223A268:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223A26C: .word 0x00002DB0

	thumb_func_start ov11_0223A270
ov11_0223A270: ; 0x0223A270
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	mov r0, #0xd
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #8
	mov r3, #0
	bl ov11_02246870
	cmp r0, #0
	bne _0223A2B0
	mov r0, #0x4c
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #8
	mov r3, #0
	bl ov11_02246870
	cmp r0, #0
	beq _0223A2B8
_0223A2B0:
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
_0223A2B8:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_0223A2C0
ov11_0223A2C0: ; 0x0223A2C0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_022482A4
	str r0, [r4, #0x6c]
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_0223A2F0
ov11_0223A2F0: ; 0x0223A2F0
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	mov r2, #0x4e
	lsl r2, r2, #2
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r4, r2
	bl ov11_0224C258
	cmp r0, #0
	bne _0223A320
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
_0223A320:
	mov r0, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov11_0223A324
ov11_0223A324: ; 0x0223A324
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02256668
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_0223A350
ov11_0223A350: ; 0x0223A350
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0223C230
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02256714
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_0223A37C
ov11_0223A37C: ; 0x0223A37C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r4, #0
	bl ov11_0223A404
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0223C230
	add r1, r0, #0
	add r0, r5, #0
	add r2, r7, #0
	bl ov11_02256754
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_0223A3B4
ov11_0223A3B4: ; 0x0223A3B4
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl ov11_0223A424
	add r0, r4, #0
	bl ov11_0223A404
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #0
	bl ov11_0222FFC8
	cmp r0, #6
	bne _0223A3E0
	ldr r0, [r5, #0x64]
	bl PCStorage_FindFirstBoxWithEmptySlot
	cmp r0, #0x12
	beq _0223A3F0
_0223A3E0:
	ldr r0, _0223A3F4 ; =0x00002410
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _0223A3F0
	add r0, r4, #0
	add r1, r6, #0
	bl ov11_0223A424
_0223A3F0:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223A3F4: .word 0x00002410

	thumb_func_start ov11_0223A3F8
ov11_0223A3F8: ; 0x0223A3F8
	ldr r3, _0223A400 ; =ov11_022432B4
	add r0, r1, #0
	bx r3
	nop
_0223A400: .word ov11_022432B4

	thumb_func_start ov11_0223A404
ov11_0223A404: ; 0x0223A404
	add r1, r0, #0
	add r1, #0xb4
	ldr r1, [r1]
	lsl r1, r1, #2
	add r2, r0, r1
	mov r1, #0x27
	lsl r1, r1, #8
	ldr r2, [r2, r1]
	add r1, r0, #0
	add r1, #0xb4
	ldr r1, [r1]
	add r0, #0xb4
	add r1, r1, #1
	str r1, [r0]
	add r0, r2, #0
	bx lr

	thumb_func_start ov11_0223A424
ov11_0223A424: ; 0x0223A424
	add r2, r0, #0
	add r2, #0xb4
	ldr r2, [r2]
	add r0, #0xb4
	add r1, r2, r1
	str r1, [r0]
	bx lr
	.align 2, 0

	thumb_func_start ov11_0223A434
ov11_0223A434: ; 0x0223A434
	ldr r3, _0223A438 ; =ov11_022431DC
	bx r3
	.align 2, 0
_0223A438: .word ov11_022431DC

	thumb_func_start ov11_0223A43C
ov11_0223A43C: ; 0x0223A43C
	ldr r3, _0223A440 ; =ov11_0224321C
	bx r3
	.align 2, 0
_0223A440: .word ov11_0224321C

	thumb_func_start ov11_0223A444
ov11_0223A444: ; 0x0223A444
	push {r4, lr}
	add r4, r1, #0
	cmp r2, #0x44
	bls _0223A44E
	b _0223A738
_0223A44E:
	add r1, r2, r2
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223A45A: ; jump table
	.short _0223A4E4 - _0223A45A - 2 ; case 0
	.short _0223A4E8 - _0223A45A - 2 ; case 1
	.short _0223A4EE - _0223A45A - 2 ; case 2
	.short _0223A4F4 - _0223A45A - 2 ; case 3
	.short _0223A4FA - _0223A45A - 2 ; case 4
	.short _0223A500 - _0223A45A - 2 ; case 5
	.short _0223A506 - _0223A45A - 2 ; case 6
	.short _0223A50C - _0223A45A - 2 ; case 7
	.short _0223A514 - _0223A45A - 2 ; case 8
	.short _0223A51A - _0223A45A - 2 ; case 9
	.short _0223A522 - _0223A45A - 2 ; case 10
	.short _0223A528 - _0223A45A - 2 ; case 11
	.short _0223A53A - _0223A45A - 2 ; case 12
	.short _0223A54C - _0223A45A - 2 ; case 13
	.short _0223A562 - _0223A45A - 2 ; case 14
	.short _0223A568 - _0223A45A - 2 ; case 15
	.short _0223A56E - _0223A45A - 2 ; case 16
	.short _0223A574 - _0223A45A - 2 ; case 17
	.short _0223A57A - _0223A45A - 2 ; case 18
	.short _0223A580 - _0223A45A - 2 ; case 19
	.short _0223A586 - _0223A45A - 2 ; case 20
	.short _0223A58E - _0223A45A - 2 ; case 21
	.short _0223A59A - _0223A45A - 2 ; case 22
	.short _0223A5A2 - _0223A45A - 2 ; case 23
	.short _0223A5AA - _0223A45A - 2 ; case 24
	.short _0223A5B0 - _0223A45A - 2 ; case 25
	.short _0223A5B8 - _0223A45A - 2 ; case 26
	.short _0223A5C0 - _0223A45A - 2 ; case 27
	.short _0223A5C8 - _0223A45A - 2 ; case 28
	.short _0223A5D0 - _0223A45A - 2 ; case 29
	.short _0223A5D6 - _0223A45A - 2 ; case 30
	.short _0223A5DC - _0223A45A - 2 ; case 31
	.short _0223A5E2 - _0223A45A - 2 ; case 32
	.short _0223A5E8 - _0223A45A - 2 ; case 33
	.short _0223A5EE - _0223A45A - 2 ; case 34
	.short _0223A5F4 - _0223A45A - 2 ; case 35
	.short _0223A5FC - _0223A45A - 2 ; case 36
	.short _0223A604 - _0223A45A - 2 ; case 37
	.short _0223A60C - _0223A45A - 2 ; case 38
	.short _0223A614 - _0223A45A - 2 ; case 39
	.short _0223A61A - _0223A45A - 2 ; case 40
	.short _0223A622 - _0223A45A - 2 ; case 41
	.short _0223A630 - _0223A45A - 2 ; case 42
	.short _0223A63E - _0223A45A - 2 ; case 43
	.short _0223A646 - _0223A45A - 2 ; case 44
	.short _0223A64C - _0223A45A - 2 ; case 45
	.short _0223A65A - _0223A45A - 2 ; case 46
	.short _0223A668 - _0223A45A - 2 ; case 47
	.short _0223A678 - _0223A45A - 2 ; case 48
	.short _0223A688 - _0223A45A - 2 ; case 49
	.short _0223A69A - _0223A45A - 2 ; case 50
	.short _0223A6A0 - _0223A45A - 2 ; case 51
	.short _0223A6A6 - _0223A45A - 2 ; case 52
	.short _0223A6AC - _0223A45A - 2 ; case 53
	.short _0223A6B8 - _0223A45A - 2 ; case 54
	.short _0223A6BE - _0223A45A - 2 ; case 55
	.short _0223A6C4 - _0223A45A - 2 ; case 56
	.short _0223A6CA - _0223A45A - 2 ; case 57
	.short _0223A6D0 - _0223A45A - 2 ; case 58
	.short _0223A6D6 - _0223A45A - 2 ; case 59
	.short _0223A6DC - _0223A45A - 2 ; case 60
	.short _0223A6E4 - _0223A45A - 2 ; case 61
	.short _0223A6EA - _0223A45A - 2 ; case 62
	.short _0223A6EE - _0223A45A - 2 ; case 63
	.short _0223A6F4 - _0223A45A - 2 ; case 64
	.short _0223A6FA - _0223A45A - 2 ; case 65
	.short _0223A70A - _0223A45A - 2 ; case 66
	.short _0223A71A - _0223A45A - 2 ; case 67
	.short _0223A728 - _0223A45A - 2 ; case 68
_0223A4E4:
	add r0, #0x2c
	pop {r4, pc}
_0223A4E8:
	ldr r0, _0223A73C ; =0x0000214C
	add r0, r4, r0
	pop {r4, pc}
_0223A4EE:
	ldr r0, _0223A740 ; =0x00002170
	add r0, r4, r0
	pop {r4, pc}
_0223A4F4:
	ldr r0, _0223A744 ; =0x00002174
	add r0, r4, r0
	pop {r4, pc}
_0223A4FA:
	ldr r0, _0223A748 ; =0x00002178
	add r0, r4, r0
	pop {r4, pc}
_0223A500:
	add r4, #0x88
	add r0, r4, #0
	pop {r4, pc}
_0223A506:
	ldr r0, _0223A74C ; =0x0000213C
	add r0, r4, r0
	pop {r4, pc}
_0223A50C:
	mov r0, #6
	lsl r0, r0, #6
	add r0, r4, r0
	pop {r4, pc}
_0223A514:
	ldr r0, _0223A750 ; =0x00002158
	add r0, r4, r0
	pop {r4, pc}
_0223A51A:
	mov r0, #0x4d
	lsl r0, r0, #2
	add r0, r4, r0
	pop {r4, pc}
_0223A522:
	ldr r0, _0223A754 ; =0x0000216C
	add r0, r4, r0
	pop {r4, pc}
_0223A528:
	ldr r1, [r4, #0x64]
	bl ov11_02230270
	mov r1, #0x6f
	lsl r1, r1, #2
	add r1, r4, r1
	lsl r0, r0, #2
	add r0, r1, r0
	pop {r4, pc}
_0223A53A:
	ldr r1, [r4, #0x6c]
	bl ov11_02230270
	mov r1, #0x6f
	lsl r1, r1, #2
	add r1, r4, r1
	lsl r0, r0, #2
	add r0, r1, r0
	pop {r4, pc}
_0223A54C:
	add r1, r4, #0
	add r1, #0x94
	ldr r1, [r1]
	bl ov11_02230270
	mov r1, #0x6f
	lsl r1, r1, #2
	add r1, r4, r1
	lsl r0, r0, #2
	add r0, r1, r0
	pop {r4, pc}
_0223A562:
	ldr r0, _0223A758 ; =0x00002144
	add r0, r4, r0
	pop {r4, pc}
_0223A568:
	add r4, #0x64
	add r0, r4, #0
	pop {r4, pc}
_0223A56E:
	add r4, #0x6c
	add r0, r4, #0
	pop {r4, pc}
_0223A574:
	add r4, #0x94
	add r0, r4, #0
	pop {r4, pc}
_0223A57A:
	add r4, #0x74
	add r0, r4, #0
	pop {r4, pc}
_0223A580:
	add r4, #0x78
	add r0, r4, #0
	pop {r4, pc}
_0223A586:
	mov r0, #0x46
	lsl r0, r0, #2
	add r0, r4, r0
	pop {r4, pc}
_0223A58E:
	ldr r0, _0223A75C ; =0x000030E4
	add r1, r4, r0
	ldr r0, [r4, #0x64]
	lsl r0, r0, #2
	add r0, r1, r0
	pop {r4, pc}
_0223A59A:
	mov r0, #0x13
	lsl r0, r0, #4
	add r0, r4, r0
	pop {r4, pc}
_0223A5A2:
	mov r0, #0x53
	lsl r0, r0, #2
	add r0, r4, r0
	pop {r4, pc}
_0223A5AA:
	ldr r0, _0223A760 ; =0x00003044
	add r0, r4, r0
	pop {r4, pc}
_0223A5B0:
	mov r0, #0x15
	lsl r0, r0, #4
	add r0, r4, r0
	pop {r4, pc}
_0223A5B8:
	mov r0, #0x47
	lsl r0, r0, #2
	add r0, r4, r0
	pop {r4, pc}
_0223A5C0:
	mov r0, #0x12
	lsl r0, r0, #4
	add r0, r4, r0
	pop {r4, pc}
_0223A5C8:
	mov r0, #0xc1
	lsl r0, r0, #6
	add r0, r4, r0
	pop {r4, pc}
_0223A5D0:
	add r4, #0x98
	add r0, r4, #0
	pop {r4, pc}
_0223A5D6:
	ldr r0, _0223A764 ; =0x00002154
	add r0, r4, r0
	pop {r4, pc}
_0223A5DC:
	add r4, #0x38
	add r0, r4, #0
	pop {r4, pc}
_0223A5E2:
	ldr r0, _0223A768 ; =0x0000215C
	add r0, r4, r0
	pop {r4, pc}
_0223A5E8:
	ldr r1, _0223A76C ; =0x0000241C
	add r0, r0, r1
	pop {r4, pc}
_0223A5EE:
	add r4, #0x8c
	add r0, r4, #0
	pop {r4, pc}
_0223A5F4:
	mov r0, #0x49
	lsl r0, r0, #2
	add r0, r4, r0
	pop {r4, pc}
_0223A5FC:
	mov r0, #0x4a
	lsl r0, r0, #2
	add r0, r4, r0
	pop {r4, pc}
_0223A604:
	mov r0, #0x4b
	lsl r0, r0, #2
	add r0, r4, r0
	pop {r4, pc}
_0223A60C:
	mov r0, #0x61
	lsl r0, r0, #2
	add r0, r4, r0
	pop {r4, pc}
_0223A614:
	ldr r0, _0223A770 ; =0x00003104
	add r0, r4, r0
	pop {r4, pc}
_0223A61A:
	mov r0, #0x86
	lsl r0, r0, #6
	add r0, r4, r0
	pop {r4, pc}
_0223A622:
	mov r0, #0x7b
	lsl r0, r0, #2
	add r1, r4, r0
	ldr r0, [r4, #0x64]
	lsl r0, r0, #6
	add r0, r1, r0
	pop {r4, pc}
_0223A630:
	mov r0, #0x81
	lsl r0, r0, #2
	add r1, r4, r0
	ldr r0, [r4, #0x64]
	lsl r0, r0, #6
	add r0, r1, r0
	pop {r4, pc}
_0223A63E:
	mov r0, #0x4e
	lsl r0, r0, #2
	add r0, r4, r0
	pop {r4, pc}
_0223A646:
	ldr r0, _0223A774 ; =0x00002150
	add r0, r4, r0
	pop {r4, pc}
_0223A64C:
	mov r0, #0x82
	lsl r0, r0, #2
	add r1, r4, r0
	ldr r0, [r4, #0x64]
	lsl r0, r0, #6
	add r0, r1, r0
	pop {r4, pc}
_0223A65A:
	mov r0, #0x82
	lsl r0, r0, #2
	add r1, r4, r0
	ldr r0, [r4, #0x6c]
	lsl r0, r0, #6
	add r0, r1, r0
	pop {r4, pc}
_0223A668:
	mov r0, #0xba
	lsl r0, r0, #2
	add r2, r4, r0
	ldr r1, [r4, #0x64]
	mov r0, #0x1c
	mul r0, r1
	add r0, r2, r0
	pop {r4, pc}
_0223A678:
	mov r0, #0xba
	lsl r0, r0, #2
	add r2, r4, r0
	ldr r1, [r4, #0x6c]
	mov r0, #0x1c
	mul r0, r1
	add r0, r2, r0
	pop {r4, pc}
_0223A688:
	mov r0, #0xba
	lsl r0, r0, #2
	add r2, r4, r0
	add r4, #0x94
	ldr r1, [r4]
	mov r0, #0x1c
	mul r0, r1
	add r0, r2, r0
	pop {r4, pc}
_0223A69A:
	ldr r0, _0223A778 ; =0x00003114
	add r0, r4, r0
	pop {r4, pc}
_0223A6A0:
	ldr r0, _0223A77C ; =0x00003118
	add r0, r4, r0
	pop {r4, pc}
_0223A6A6:
	ldr r1, _0223A780 ; =0x00002408
	add r0, r0, r1
	pop {r4, pc}
_0223A6AC:
	ldr r0, _0223A784 ; =0x0000304C
	add r1, r4, r0
	ldr r0, [r4, #0x64]
	lsl r0, r0, #2
	add r0, r1, r0
	pop {r4, pc}
_0223A6B8:
	ldr r0, _0223A788 ; =0x00002148
	add r0, r4, r0
	pop {r4, pc}
_0223A6BE:
	ldr r1, _0223A78C ; =0x00002410
	add r0, r0, r1
	pop {r4, pc}
_0223A6C4:
	add r4, #0x7c
	add r0, r4, #0
	pop {r4, pc}
_0223A6CA:
	ldr r0, _0223A790 ; =0x00002160
	add r0, r4, r0
	pop {r4, pc}
_0223A6D0:
	ldr r0, _0223A794 ; =0x00002164
	add r0, r4, r0
	pop {r4, pc}
_0223A6D6:
	ldr r1, _0223A798 ; =0x00002418
	add r0, r0, r1
	pop {r4, pc}
_0223A6DC:
	mov r0, #0x85
	lsl r0, r0, #6
	add r0, r4, r0
	pop {r4, pc}
_0223A6E4:
	add r4, #0xec
	add r0, r4, #0
	pop {r4, pc}
_0223A6EA:
	add r0, #0x44
	pop {r4, pc}
_0223A6EE:
	add r4, #0x68
	add r0, r4, #0
	pop {r4, pc}
_0223A6F4:
	add r4, #0x70
	add r0, r4, #0
	pop {r4, pc}
_0223A6FA:
	mov r0, #0xb6
	lsl r0, r0, #2
	add r2, r4, r0
	ldr r1, [r4, #0x6c]
	mov r0, #0x1c
	mul r0, r1
	add r0, r2, r0
	pop {r4, pc}
_0223A70A:
	mov r0, #0x21
	lsl r0, r0, #4
	add r1, r4, r0
	sub r0, #0xf8
	ldr r0, [r4, r0]
	lsl r0, r0, #6
	add r0, r1, r0
	pop {r4, pc}
_0223A71A:
	mov r0, #0x21
	lsl r0, r0, #4
	add r1, r4, r0
	ldr r0, [r4, #0x6c]
	lsl r0, r0, #6
	add r0, r1, r0
	pop {r4, pc}
_0223A728:
	mov r0, #0xbb
	lsl r0, r0, #2
	add r2, r4, r0
	ldr r1, [r4, #0x64]
	mov r0, #0x1c
	mul r0, r1
	add r0, r2, r0
	pop {r4, pc}
_0223A738:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_0223A73C: .word 0x0000214C
_0223A740: .word 0x00002170
_0223A744: .word 0x00002174
_0223A748: .word 0x00002178
_0223A74C: .word 0x0000213C
_0223A750: .word 0x00002158
_0223A754: .word 0x0000216C
_0223A758: .word 0x00002144
_0223A75C: .word 0x000030E4
_0223A760: .word 0x00003044
_0223A764: .word 0x00002154
_0223A768: .word 0x0000215C
_0223A76C: .word 0x0000241C
_0223A770: .word 0x00003104
_0223A774: .word 0x00002150
_0223A778: .word 0x00003114
_0223A77C: .word 0x00003118
_0223A780: .word 0x00002408
_0223A784: .word 0x0000304C
_0223A788: .word 0x00002148
_0223A78C: .word 0x00002410
_0223A790: .word 0x00002160
_0223A794: .word 0x00002164
_0223A798: .word 0x00002418

	thumb_func_start ov11_0223A79C
ov11_0223A79C: ; 0x0223A79C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xd4
	add r4, r1, #0
	str r0, [sp, #0x14]
	ldr r0, [r4]
	bl ov11_022300C4
	str r0, [sp, #0x3c]
	ldr r0, [r4]
	bl ov11_0222FF74
	str r0, [sp, #0x38]
	ldr r0, [r4, #4]
	mov r7, #0
	ldr r0, [r0, #0x74]
	ldr r5, [r4, #0x48]
	asr r1, r0, #1
	mov r0, #1
	and r0, r1
	str r0, [sp, #0x40]
	ldr r0, [r4]
	add r1, r7, #0
	bl ov11_0222FFC8
	cmp r5, r0
	bge _0223A81E
	ldr r0, [sp, #0x40]
	lsl r0, r0, #2
	str r0, [sp, #0x24]
_0223A7D6:
	ldr r0, [r4]
	mov r1, #0
	add r2, r5, #0
	bl ov11_02230014
	mov r1, #6
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #1
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0x32
	beq _0223A81E
	add r0, r5, #0
	bl MaskOfFlagNo
	add r2, r0, #0
	ldr r1, [r4, #4]
	ldr r0, [sp, #0x24]
	add r0, r0, r1
	add r0, #0xa4
	ldr r0, [r0]
	tst r0, r2
	bne _0223A81E
	ldr r0, [r4]
	mov r1, #0
	add r5, r5, #1
	bl ov11_0222FFC8
	cmp r5, r0
	blt _0223A7D6
_0223A81E:
	ldr r0, [r4]
	mov r1, #0
	bl ov11_0222FFC8
	cmp r5, r0
	bne _0223A830
	mov r0, #0x26
	str r0, [r4, #0x28]
	b _0223A84C
_0223A830:
	ldr r0, [sp, #0x38]
	mov r2, #2
	tst r0, r2
	beq _0223A84C
	ldr r0, [sp, #0x38]
	mov r1, #0x40
	tst r0, r1
	bne _0223A84C
	ldr r1, [r4, #4]
	ldr r0, _0223AB98 ; =0x0000219E
	ldrb r0, [r1, r0]
	cmp r0, r5
	bne _0223A84C
	add r7, r2, #0
_0223A84C:
	ldr r0, [r4, #0x28]
	cmp r0, #0x26
	bls _0223A856
	bl _0223B2AE
_0223A856:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223A862: ; jump table
	.short _0223A8B0 - _0223A862 - 2 ; case 0
	.short _0223AA74 - _0223A862 - 2 ; case 1
	.short _0223AA8C - _0223A862 - 2 ; case 2
	.short _0223AA9E - _0223A862 - 2 ; case 3
	.short _0223AACA - _0223A862 - 2 ; case 4
	.short _0223AADE - _0223A862 - 2 ; case 5
	.short _0223AB16 - _0223A862 - 2 ; case 6
	.short _0223AC16 - _0223A862 - 2 ; case 7
	.short _0223AC32 - _0223A862 - 2 ; case 8
	.short _0223AC50 - _0223A862 - 2 ; case 9
	.short _0223ACF8 - _0223A862 - 2 ; case 10
	.short _0223AE3C - _0223A862 - 2 ; case 11
	.short _0223ADBA - _0223A862 - 2 ; case 12
	.short _0223AE3C - _0223A862 - 2 ; case 13
	.short _0223AE5E - _0223A862 - 2 ; case 14
	.short _0223AEC0 - _0223A862 - 2 ; case 15
	.short _0223AF42 - _0223A862 - 2 ; case 16
	.short _0223AFDA - _0223A862 - 2 ; case 17
	.short _0223AFAC - _0223A862 - 2 ; case 18
	.short _0223AFDA - _0223A862 - 2 ; case 19
	.short _0223AFF2 - _0223A862 - 2 ; case 20
	.short _0223B012 - _0223A862 - 2 ; case 21
	.short _0223B05A - _0223A862 - 2 ; case 22
	.short _0223B07E - _0223A862 - 2 ; case 23
	.short _0223B16A - _0223A862 - 2 ; case 24
	.short _0223AFDA - _0223A862 - 2 ; case 25
	.short _0223B192 - _0223A862 - 2 ; case 26
	.short _0223AFDA - _0223A862 - 2 ; case 27
	.short _0223B1CE - _0223A862 - 2 ; case 28
	.short _0223AFDA - _0223A862 - 2 ; case 29
	.short _0223B1F6 - _0223A862 - 2 ; case 30
	.short _0223B0B6 - _0223A862 - 2 ; case 31
	.short _0223AFDA - _0223A862 - 2 ; case 32
	.short _0223B0E0 - _0223A862 - 2 ; case 33
	.short _0223B102 - _0223A862 - 2 ; case 34
	.short _0223B152 - _0223A862 - 2 ; case 35
	.short _0223B25C - _0223A862 - 2 ; case 36
	.short _0223B272 - _0223A862 - 2 ; case 37
	.short _0223B298 - _0223A862 - 2 ; case 38
_0223A8B0:
	add r0, r6, #0
	mov r1, #6
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #1
	mov r2, #5
	bl GetItemAttr
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x38]
	mov r1, #1
	and r0, r1
	str r0, [sp, #0x1c]
	bne _0223A90E
	ldr r1, [r4, #4]
	ldr r0, _0223AB9C ; =0x00002E4C
	ldr r2, _0223ABA0 ; =0x00002FCC
	ldr r0, [r1, r0]
	ldr r1, [r1, r2]
	add r0, r0, r1
	bne _0223A90E
	add r0, r6, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _0223A90E
	ldr r1, [r4, #4]
	ldr r0, _0223ABA4 ; =0x00003144
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _0223A90E
	ldr r0, _0223ABA8 ; =0x00000467
	bl sub_0200521C
	ldr r1, [r4, #4]
	ldr r0, _0223ABA4 ; =0x00003144
	mov r2, #1
	str r2, [r1, r0]
	ldr r0, [r4]
	mov r1, #2
	bl ov11_02231484
_0223A90E:
	mov r0, #0
	str r0, [sp, #0x34]
	mov r1, #1
	add r0, sp, #0xb0
	strh r1, [r0, #2]
	ldr r2, [sp, #0x34]
	add r0, r6, #0
	mov r1, #0xa2
	bl GetMonData
	cmp r0, #0
	bne _0223A928
	b _0223AA34
_0223A928:
	add r0, r6, #0
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	cmp r0, #0x64
	beq _0223AA34
	ldr r0, [r4, #4]
	str r0, [sp, #0x20]
	add r0, r5, #0
	bl MaskOfFlagNo
	ldr r1, [sp, #0x40]
	lsl r2, r1, #2
	ldr r1, [sp, #0x20]
	add r1, r1, r2
	add r1, #0xa4
	ldr r1, [r1]
	tst r0, r1
	beq _0223A958
	ldr r0, [sp, #0x20]
	add r0, #0x9c
	ldr r0, [r0]
	str r0, [sp, #0x34]
_0223A958:
	ldr r0, [sp, #0x18]
	cmp r0, #0x32
	bne _0223A96C
	ldr r0, [sp, #0x20]
	add r0, #0xa0
	str r0, [sp, #0x20]
	ldr r1, [r0]
	ldr r0, [sp, #0x34]
	add r0, r0, r1
	str r0, [sp, #0x34]
_0223A96C:
	ldr r0, [sp, #0x18]
	cmp r0, #0x41
	bne _0223A980
	ldr r1, [sp, #0x34]
	mov r0, #0x96
	mul r0, r1
	mov r1, #0x64
	bl _u32_div_f
	str r0, [sp, #0x34]
_0223A980:
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	beq _0223A994
	ldr r1, [sp, #0x34]
	mov r0, #0x96
	mul r0, r1
	mov r1, #0x64
	bl _u32_div_f
	str r0, [sp, #0x34]
_0223A994:
	ldr r0, [r4]
	add r1, r6, #0
	bl ov11_0224AE14
	cmp r0, #0
	bne _0223A9D6
	add r0, r6, #0
	mov r1, #0xc
	mov r2, #0
	bl GetMonData
	ldr r1, _0223ABAC ; =gGameLanguage
	ldrb r1, [r1]
	cmp r1, r0
	beq _0223A9C2
	ldr r1, [sp, #0x34]
	mov r0, #0xaa
	mul r0, r1
	mov r1, #0x64
	bl _u32_div_f
	str r0, [sp, #0x34]
	b _0223A9D0
_0223A9C2:
	ldr r1, [sp, #0x34]
	mov r0, #0x96
	mul r0, r1
	mov r1, #0x64
	bl _u32_div_f
	str r0, [sp, #0x34]
_0223A9D0:
	mov r1, #2
	add r0, sp, #0xb0
	strh r1, [r0, #2]
_0223A9D6:
	add r0, r6, #0
	mov r1, #8
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0x48]
	add r0, r6, #0
	bl GetMonBaseExperienceAtCurrentLevel
	ldr r1, [sp, #0x48]
	sub r0, r1, r0
	str r0, [r4, #0x3c]
	ldr r1, [sp, #0x48]
	ldr r0, [sp, #0x34]
	add r2, r1, r0
	str r2, [sp, #0x48]
	ldr r3, [r4, #4]
	ldr r0, _0223ABB0 ; =0x0000219C
	add r1, r3, r7
	ldrb r0, [r1, r0]
	cmp r5, r0
	bne _0223AA0C
	mov r0, #0xc0
	mul r0, r7
	add r1, r3, r0
	ldr r0, _0223ABB4 ; =0x00002DA4
	str r2, [r1, r0]
_0223AA0C:
	add r0, r6, #0
	mov r1, #8
	add r2, sp, #0x48
	bl SetMonData
	ldr r6, [r4, #4]
	ldr r0, [r4]
	add r1, r7, #0
	bl ov11_0222FF88
	ldr r3, [r6, #0x74]
	mov r2, #0xc0
	mul r2, r3
	add r3, r6, r2
	mov r2, #0xb5
	lsl r2, r2, #6
	ldrh r2, [r3, r2]
	add r1, r5, #0
	bl ov11_0223B2DC
_0223AA34:
	ldr r0, [sp, #0x34]
	cmp r0, #0
	beq _0223AA6C
	mov r1, #0x11
	add r0, sp, #0xb0
	strb r1, [r0, #1]
	lsl r0, r5, #8
	orr r0, r7
	str r0, [sp, #0xb4]
	ldr r0, [sp, #0x34]
	str r0, [sp, #0xb8]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x3c]
	add r2, sp, #0xb0
	bl ov11_0223178C
	str r0, [r4, #0x30]
	mov r0, #0x14
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x28]
	add sp, #0xd4
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AA6C:
	mov r0, #0x25
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AA74:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_0201BD70
	cmp r0, #0
	bne _0223AB20
	ldr r0, [r4, #0x28]
	add sp, #0xd4
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AA8C:
	ldr r0, [r4, #0x34]
	sub r0, r0, #1
	str r0, [r4, #0x34]
	bne _0223AB20
	ldr r0, [r4, #0x28]
	add sp, #0xd4
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AA9E:
	ldr r1, [r4, #4]
	ldr r0, _0223ABB0 ; =0x0000219C
	add r2, r1, r7
	ldrb r0, [r2, r0]
	cmp r5, r0
	bne _0223AAC2
	ldr r0, [r4]
	ldr r3, [r4, #0x3c]
	add r2, r7, #0
	bl ov11_02255B68
	mov r0, #0
	str r0, [r4, #0x3c]
	ldr r0, [r4, #0x28]
	add sp, #0xd4
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AAC2:
	mov r0, #5
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AACA:
	ldr r0, [r4, #4]
	bl ov11_02243388
	cmp r0, #0
	beq _0223AB20
	ldr r0, [r4, #0x28]
	add sp, #0xd4
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AADE:
	add r0, r6, #0
	bl sub_020690E8
	cmp r0, #0
	beq _0223AB0E
	ldr r1, [r4, #4]
	ldr r0, _0223ABB0 ; =0x0000219C
	add r2, r1, r7
	ldrb r0, [r2, r0]
	cmp r5, r0
	bne _0223AB06
	ldr r0, [r4]
	add r2, r7, #0
	mov r3, #8
	bl ov11_02255E4C
	ldr r0, [r4]
	add r1, r7, #0
	bl ov11_02255FA0
_0223AB06:
	mov r0, #6
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AB0E:
	mov r0, #0x25
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AB16:
	ldr r0, [r4, #4]
	bl ov11_02243388
	cmp r0, #0
	bne _0223AB22
_0223AB20:
	b _0223B2AE
_0223AB22:
	ldr r3, _0223ABB8 ; =ov11_0225DCC0
	add r2, sp, #0x98
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r6, #0
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0x30]
	mov r0, #5
	mov r1, #0x18
	bl AllocFromHeap
	mov r1, #0x5f
	ldr r2, [r4, #4]
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4, #4]
	ldr r0, [r0, r1]
	mov r1, #0
	str r0, [sp, #0x2c]
	str r1, [sp, #0x4c]
_0223AB58:
	lsl r2, r1, #2
	add r1, sp, #0x98
	ldr r1, [r1, r2]
	add r0, r6, #0
	mov r2, #0
	bl GetMonData
	ldr r1, [sp, #0x4c]
	lsl r2, r1, #2
	ldr r1, [sp, #0x2c]
	str r0, [r1, r2]
	ldr r0, [sp, #0x4c]
	add r1, r0, #1
	str r1, [sp, #0x4c]
	cmp r1, #6
	blt _0223AB58
	ldr r0, [r4]
	bl ov11_022302B0
	add r2, r0, #0
	lsl r2, r2, #0x10
	add r0, r6, #0
	mov r1, #0
	lsr r2, r2, #0x10
	bl MonApplyFriendshipMod
	add r0, r6, #0
	bl CalcMonStats
	ldr r1, [r4, #4]
	ldr r0, _0223ABB0 ; =0x0000219C
	b _0223ABBC
	.align 2, 0
_0223AB98: .word 0x0000219E
_0223AB9C: .word 0x00002E4C
_0223ABA0: .word 0x00002FCC
_0223ABA4: .word 0x00003144
_0223ABA8: .word 0x00000467
_0223ABAC: .word gGameLanguage
_0223ABB0: .word 0x0000219C
_0223ABB4: .word 0x00002DA4
_0223ABB8: .word ov11_0225DCC0
_0223ABBC:
	add r2, r1, r7
	ldrb r3, [r2, r0]
	cmp r5, r3
	bne _0223ABCC
	ldr r0, [r4]
	add r2, r7, #0
	bl ov11_02243054
_0223ABCC:
	add r0, r5, #0
	bl MaskOfFlagNo
	ldr r1, [r4, #4]
	ldr r2, _0223AF48 ; =0x00003109
	ldrb r3, [r1, r2]
	orr r0, r3
	strb r0, [r1, r2]
	ldr r0, [r4]
	ldr r1, [r4, #4]
	add r2, r7, #0
	bl ov11_02256020
	mov r1, #3
	add r0, sp, #0xb0
	strh r1, [r0, #2]
	mov r1, #0x11
	strb r1, [r0, #1]
	lsl r0, r5, #8
	orr r0, r7
	str r0, [sp, #0xb4]
	ldr r0, [sp, #0x30]
	str r0, [sp, #0xb8]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x3c]
	add r2, sp, #0xb0
	bl ov11_0223178C
	str r0, [r4, #0x30]
	mov r0, #7
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AC16:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_0201BD70
	cmp r0, #0
	beq _0223AC26
	b _0223B2AE
_0223AC26:
	mov r0, #8
	str r0, [r4, #0x28]
	mov r0, #0
	add sp, #0xd4
	str r0, [r4, #0x38]
	pop {r4, r5, r6, r7, pc}
_0223AC32:
	ldr r0, [r4, #4]
	add r1, r0, r7
	ldr r0, _0223AF4C ; =0x0000219C
	ldrb r0, [r1, r0]
	cmp r5, r0
	beq _0223AC48
	ldr r0, [r4]
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0223CDC4
_0223AC48:
	mov r0, #9
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AC50:
	ldr r0, [r4]
	bl ov11_0222FF68
	add r6, r0, #0
	ldr r0, [r4]
	mov r1, #1
	bl ov11_0222FF6C
	add r5, r0, #0
	ldr r0, [r4]
	bl ov11_022300CC
	add r7, r0, #0
	ldr r0, _0223AF50 ; =0x04000008
	mov r2, #3
	ldrh r1, [r0]
	bic r1, r2
	mov r2, #2
	orr r1, r2
	strh r1, [r0]
	mov r0, #1
	add r1, r0, #0
	bl SetBgPriority
	mov r0, #2
	mov r1, #0
	bl SetBgPriority
	ldr r0, [r4]
	mov r1, #2
	bl ov11_02231564
	mov r0, #5
	str r0, [sp]
	add r0, r6, #0
	mov r1, #2
	mov r2, #1
	mov r3, #0
	bl sub_0200CABC
	bl sub_0200CAFC
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x80
	str r0, [sp, #8]
	add r0, r7, #0
	mov r1, #0x26
	mov r3, #5
	bl PaletteData_LoadNarc
	mov r0, #7
	str r0, [sp]
	mov r0, #0xe
	str r0, [sp, #4]
	mov r0, #0xc
	str r0, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	mov r0, #0xa
	str r0, [sp, #0x10]
	add r0, r6, #0
	add r1, r5, #0
	mov r2, #2
	mov r3, #0x11
	bl AddWindowParameterized
	add r0, r5, #0
	mov r1, #0xff
	bl FillWindowPixelBuffer
	add r0, r5, #0
	mov r1, #0
	mov r2, #1
	mov r3, #8
	bl DrawFrameAndWindow1
	mov r0, #0xa
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223ACF8:
	ldr r3, _0223AF54 ; =ov11_0225DCD8
	add r2, sp, #0x80
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r3, _0223AF58 ; =ov11_0225DC60
	add r2, sp, #0x68
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r4]
	mov r1, #1
	bl ov11_0222FF6C
	add r7, r0, #0
	mov r0, #0x5f
	ldr r1, [r4, #4]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	str r0, [sp, #0x28]
	mov r0, #0
	str r0, [sp, #0x4c]
_0223AD30:
	ldr r2, _0223AF5C ; =0x000003B3
	add r1, sp, #0xb0
	strh r2, [r1, #2]
	mov r2, #4
	strb r2, [r1, #1]
	lsl r2, r0, #2
	add r1, sp, #0x80
	ldr r1, [r1, r2]
	lsl r0, r0, #4
	str r1, [sp, #0xb4]
	mov r1, #0
	str r1, [sp]
	str r0, [sp, #4]
	add r0, r1, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r4]
	ldr r2, [sp, #0x3c]
	add r1, r7, #0
	add r3, sp, #0xb0
	bl ov11_022317E0
	mov r1, #0xed
	ldr r5, [sp, #0x4c]
	lsl r1, r1, #2
	add r0, sp, #0xb0
	strh r1, [r0, #2]
	mov r1, #7
	strb r1, [r0, #1]
	lsl r2, r5, #2
	add r1, sp, #0x68
	ldr r1, [r1, r2]
	add r0, r6, #0
	mov r2, #0
	bl GetMonData
	ldr r1, [sp, #0x28]
	lsl r2, r5, #2
	ldr r1, [r1, r2]
	ldr r2, [sp, #0x3c]
	sub r0, r0, r1
	str r0, [sp, #0xb4]
	mov r0, #2
	str r0, [sp, #0xcc]
	mov r0, #0x50
	str r0, [sp]
	lsl r0, r5, #4
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0x1c
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r1, r7, #0
	add r3, sp, #0xb0
	bl ov11_022317E0
	ldr r0, [sp, #0x4c]
	add r0, r0, #1
	str r0, [sp, #0x4c]
	cmp r0, #6
	blt _0223AD30
	mov r0, #0xb
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223ADBA:
	ldr r3, _0223AF60 ; =ov11_0225DC90
	add r2, sp, #0x50
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r4]
	mov r1, #1
	bl ov11_0222FF6C
	mov r1, #0x24
	str r1, [sp]
	mov r1, #0x60
	str r1, [sp, #4]
	mov r1, #0xf
	mov r2, #0x50
	mov r3, #0
	add r7, r0, #0
	bl FillWindowPixelRect
	mov r1, #0
	str r1, [sp, #0x4c]
	add r5, sp, #0xb0
_0223ADEC:
	ldr r0, _0223AF64 ; =0x000003B5
	lsl r2, r1, #2
	add r1, sp, #0x50
	strh r0, [r5, #2]
	mov r0, #7
	ldr r1, [r1, r2]
	strb r0, [r5, #1]
	add r0, r6, #0
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0xb4]
	mov r0, #3
	str r0, [sp, #0xcc]
	mov r0, #0x48
	str r0, [sp]
	ldr r0, [sp, #0x4c]
	ldr r2, [sp, #0x3c]
	lsl r0, r0, #4
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0x24
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r1, r7, #0
	add r3, r5, #0
	bl ov11_022317E0
	ldr r0, [sp, #0x4c]
	add r1, r0, #1
	str r1, [sp, #0x4c]
	cmp r1, #6
	blt _0223ADEC
	mov r0, #0xd
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AE3C:
	ldr r0, _0223AF68 ; =gSystem
	ldr r1, [r0, #0x48]
	ldr r0, _0223AF6C ; =0x00000C03
	tst r0, r1
	bne _0223AE4E
	bl sub_02020AA4
	cmp r0, #0
	beq _0223AEDC
_0223AE4E:
	ldr r0, _0223AF70 ; =0x000005DC
	bl PlaySE
	ldr r0, [r4, #0x28]
	add sp, #0xd4
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AE5E:
	ldr r0, [r4]
	mov r1, #1
	bl ov11_0222FF6C
	add r6, r0, #0
	mov r1, #0
	bl ClearFrameAndWindow1
	add r0, r6, #0
	bl RemoveWindow
	ldr r1, _0223AF50 ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #1
	orr r2, r0
	strh r2, [r1]
	mov r1, #0
	bl SetBgPriority
	mov r0, #2
	mov r1, #1
	bl SetBgPriority
	ldr r0, [r4]
	mov r1, #0
	bl ov11_02231564
	ldr r0, [r4, #4]
	add r1, r0, r7
	ldr r0, _0223AF4C ; =0x0000219C
	ldrb r0, [r1, r0]
	cmp r5, r0
	beq _0223AEAC
	ldr r0, [r4]
	add r1, r4, #0
	bl ov11_0223D068
_0223AEAC:
	mov r0, #0x5f
	ldr r1, [r4, #4]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FreeToHeap
	mov r0, #0xf
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AEC0:
	ldr r0, [r4]
	bl ov11_0222FF68
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x38
	add r2, sp, #0x44
	bl sub_02069818
	cmp r0, #0
	beq _0223AEE6
	ldr r1, _0223AF74 ; =0x0000FFFE
	cmp r0, r1
	bne _0223AEDE
_0223AEDC:
	b _0223B2AE
_0223AEDE:
	add r1, r1, #1
	cmp r0, r1
	beq _0223AEEE
	b _0223AEFC
_0223AEE6:
	mov r0, #3
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AEEE:
	add r0, sp, #0x44
	ldrh r0, [r0]
	add sp, #0xd4
	str r0, [r4, #0x40]
	mov r0, #0x10
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AEFC:
	ldr r1, [r4, #4]
	ldr r0, _0223AF4C ; =0x0000219C
	add r2, r1, r7
	ldrb r3, [r2, r0]
	cmp r5, r3
	bne _0223AF10
	ldr r0, [r4]
	add r2, r7, #0
	bl ov11_02243054
_0223AF10:
	mov r1, #4
	add r0, sp, #0xb0
	strh r1, [r0, #2]
	mov r1, #0xa
	strb r1, [r0, #1]
	lsl r0, r5, #8
	orr r0, r7
	str r0, [sp, #0xb4]
	add r0, sp, #0x44
	ldrh r0, [r0]
	str r0, [sp, #0xb8]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x3c]
	add r2, sp, #0xb0
	bl ov11_0223178C
	str r0, [r4, #0x30]
	mov r0, #0x24
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AF42:
	ldr r1, _0223AF78 ; =0x0000049A
	b _0223AF7C
	nop
_0223AF48: .word 0x00003109
_0223AF4C: .word 0x0000219C
_0223AF50: .word 0x04000008
_0223AF54: .word ov11_0225DCD8
_0223AF58: .word ov11_0225DC60
_0223AF5C: .word 0x000003B3
_0223AF60: .word ov11_0225DC90
_0223AF64: .word 0x000003B5
_0223AF68: .word gSystem
_0223AF6C: .word 0x00000C03
_0223AF70: .word 0x000005DC
_0223AF74: .word 0x0000FFFE
_0223AF78: .word 0x0000049A
_0223AF7C:
	add r0, sp, #0xb0
	strh r1, [r0, #2]
	mov r1, #0xa
	strb r1, [r0, #1]
	lsl r0, r5, #8
	orr r0, r7
	str r0, [sp, #0xb4]
	ldr r0, [r4, #0x40]
	str r0, [sp, #0xb8]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x3c]
	add r2, sp, #0xb0
	bl ov11_0223178C
	str r0, [r4, #0x30]
	ldr r0, [r4, #0x28]
	add sp, #0xd4
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AFAC:
	ldr r1, _0223B2B4 ; =0x0000049B
	add r0, sp, #0xb0
	strh r1, [r0, #2]
	mov r1, #2
	strb r1, [r0, #1]
	lsl r0, r5, #8
	orr r0, r7
	str r0, [sp, #0xb4]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x3c]
	add r2, sp, #0xb0
	bl ov11_0223178C
	str r0, [r4, #0x30]
	ldr r0, [r4, #0x28]
	add sp, #0xd4
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AFDA:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_0201BD70
	cmp r0, #0
	bne _0223B01E
	ldr r0, [r4, #0x28]
	add sp, #0xd4
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223AFF2:
	mov r0, #1
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r3, _0223B2B8 ; =0x0000049C
	add r2, r7, #0
	bl ov11_02255980
	ldr r0, [r4, #0x28]
	add sp, #0xd4
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B012:
	ldr r0, [r4, #4]
	add r1, r7, #0
	bl ov11_0224AD90
	cmp r0, #0
	bne _0223B020
_0223B01E:
	b _0223B2AE
_0223B020:
	ldr r0, [r4, #4]
	add r1, r7, #0
	bl ov11_0224AD90
	cmp r0, #0xff
	bne _0223B034
	mov r0, #0x1f
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B034:
	ldr r1, _0223B2BC ; =0x0000049F
	add r0, sp, #0xb0
	strh r1, [r0, #2]
	mov r1, #0
	strb r1, [r0, #1]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x3c]
	add r2, sp, #0xb0
	bl ov11_0223178C
	str r0, [r4, #0x30]
	mov r0, #0x16
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B05A:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_0201BD70
	cmp r0, #0
	bne _0223B160
	ldr r0, [r4]
	ldr r2, [r4, #0x40]
	add r1, r7, #0
	add r3, r5, #0
	bl ov11_022562B0
	ldr r0, [r4, #0x28]
	add sp, #0xd4
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B07E:
	ldr r0, [r4, #4]
	add r1, r7, #0
	bl ov11_0224AD90
	cmp r0, #0xff
	bne _0223B092
	mov r0, #0x1f
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B092:
	ldr r0, [r4, #4]
	add r1, r7, #0
	bl ov11_0224AD90
	cmp r0, #0
	beq _0223B160
	ldr r1, [r4, #4]
	lsl r0, r7, #8
	add r1, r1, r0
	mov r0, #0x23
	lsl r0, r0, #8
	ldrb r0, [r1, r0]
	add sp, #0xd4
	sub r0, r0, #1
	str r0, [r4, #0x44]
	mov r0, #0x18
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B0B6:
	mov r1, #0x4a
	lsl r1, r1, #4
	add r0, sp, #0xb0
	strh r1, [r0, #2]
	mov r1, #0
	strb r1, [r0, #1]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x3c]
	add r2, sp, #0xb0
	bl ov11_0223178C
	str r0, [r4, #0x30]
	ldr r0, [r4, #0x28]
	add sp, #0xd4
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B0E0:
	mov r0, #2
	str r0, [sp]
	ldr r0, [r4, #0x40]
	ldr r3, _0223B2C0 ; =0x000004A1
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [r4]
	ldr r1, [r4, #4]
	add r2, r7, #0
	bl ov11_02255980
	ldr r0, [r4, #0x28]
	add sp, #0xd4
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B102:
	ldr r0, [r4, #4]
	add r1, r7, #0
	bl ov11_0224AD90
	cmp r0, #0
	beq _0223B160
	ldr r0, [r4, #4]
	add r1, r7, #0
	bl ov11_0224AD90
	cmp r0, #0xff
	bne _0223B122
	mov r0, #0x10
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B122:
	ldr r1, _0223B2C4 ; =0x000004A4
	add r0, sp, #0xb0
	strh r1, [r0, #2]
	mov r1, #0xa
	strb r1, [r0, #1]
	lsl r0, r5, #8
	orr r0, r7
	str r0, [sp, #0xb4]
	ldr r0, [r4, #0x40]
	str r0, [sp, #0xb8]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x3c]
	add r2, sp, #0xb0
	bl ov11_0223178C
	str r0, [r4, #0x30]
	mov r0, #0x23
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B152:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_0201BD70
	cmp r0, #0
	beq _0223B162
_0223B160:
	b _0223B2AE
_0223B162:
	mov r0, #0xf
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B16A:
	ldr r1, _0223B2C8 ; =0x000004A5
	add r0, sp, #0xb0
	strh r1, [r0, #2]
	mov r1, #0
	strb r1, [r0, #1]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x3c]
	add r2, sp, #0xb0
	bl ov11_0223178C
	str r0, [r4, #0x30]
	ldr r0, [r4, #0x28]
	add sp, #0xd4
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B192:
	ldr r1, _0223B2CC ; =0x000004A6
	add r0, sp, #0xb0
	strh r1, [r0, #2]
	mov r1, #0xa
	strb r1, [r0, #1]
	lsl r0, r5, #8
	orr r0, r7
	str r0, [sp, #0xb4]
	ldr r1, [r4, #0x44]
	add r0, r6, #0
	add r1, #0x36
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0xb8]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x3c]
	add r2, sp, #0xb0
	bl ov11_0223178C
	str r0, [r4, #0x30]
	ldr r0, [r4, #0x28]
	add sp, #0xd4
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B1CE:
	ldr r1, _0223B2D0 ; =0x000004A7
	add r0, sp, #0xb0
	strh r1, [r0, #2]
	mov r1, #0
	strb r1, [r0, #1]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x3c]
	add r2, sp, #0xb0
	bl ov11_0223178C
	str r0, [r4, #0x30]
	ldr r0, [r4, #0x28]
	add sp, #0xd4
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B1F6:
	ldr r1, _0223B2D4 ; =0x000004A8
	add r0, sp, #0xb0
	strh r1, [r0, #2]
	mov r1, #0xa
	strb r1, [r0, #1]
	lsl r0, r5, #8
	orr r0, r7
	str r0, [sp, #0xb4]
	ldr r0, [r4, #0x40]
	str r0, [sp, #0xb8]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x3c]
	add r2, sp, #0xb0
	bl ov11_0223178C
	str r0, [r4, #0x30]
	mov r0, #0
	str r0, [sp, #0x4c]
	ldr r1, [r4, #0x44]
	add r0, r6, #0
	add r1, #0x3e
	add r2, sp, #0x4c
	bl SetMonData
	ldr r1, [r4, #0x40]
	ldr r2, [r4, #0x44]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x18
	add r0, r6, #0
	lsr r1, r1, #0x10
	lsr r2, r2, #0x18
	bl MonSetMoveInSlot
	ldr r1, [r4, #4]
	ldr r0, _0223B2D8 ; =0x0000219C
	add r2, r1, r7
	ldrb r3, [r2, r0]
	cmp r5, r3
	bne _0223B254
	ldr r0, [r4]
	add r2, r7, #0
	bl ov11_02243054
_0223B254:
	mov r0, #0x24
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B25C:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_0201BD70
	cmp r0, #0
	bne _0223B2AE
	mov r0, #0xf
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B272:
	add r0, r5, #0
	bl MaskOfFlagNo
	ldr r1, [sp, #0x40]
	ldr r2, [r4, #4]
	mov r3, #0
	mvn r3, r3
	add r2, #0xa4
	lsl r1, r1, #2
	ldr r6, [r2, r1]
	eor r0, r3
	and r0, r6
	str r0, [r2, r1]
	add r0, r5, #1
	str r0, [r4, #0x48]
	mov r0, #0
	add sp, #0xd4
	str r0, [r4, #0x28]
	pop {r4, r5, r6, r7, pc}
_0223B298:
	mov r0, #0x5e
	ldr r1, [r4, #4]
	mov r2, #0
	lsl r0, r0, #2
	str r2, [r1, r0]
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [sp, #0x14]
	bl sub_0200CAB4
_0223B2AE:
	add sp, #0xd4
	pop {r4, r5, r6, r7, pc}
	nop
_0223B2B4: .word 0x0000049B
_0223B2B8: .word 0x0000049C
_0223B2BC: .word 0x0000049F
_0223B2C0: .word 0x000004A1
_0223B2C4: .word 0x000004A4
_0223B2C8: .word 0x000004A5
_0223B2CC: .word 0x000004A6
_0223B2D0: .word 0x000004A7
_0223B2D4: .word 0x000004A8
_0223B2D8: .word 0x0000219C

	thumb_func_start ov11_0223B2DC
ov11_0223B2DC: ; 0x0223B2DC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	str r0, [sp]
	str r1, [sp, #4]
	add r0, r2, #0
	mov r1, #5
	mov r4, #0
	bl AllocAndLoadMonPersonal
	add r7, r0, #0
	ldr r0, [sp]
	ldr r1, [sp, #4]
	bl Party_GetMonByIndex
	mov r1, #6
	add r2, r4, #0
	str r0, [sp, #0x14]
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r0, r6, #0
	mov r1, #1
	mov r2, #5
	bl GetItemAttr
	add r5, r0, #0
	add r0, r6, #0
	mov r1, #2
	mov r2, #5
	bl GetItemAttr
	add r6, r0, #0
	add r0, r4, #0
	str r0, [sp, #0x18]
	str r0, [sp, #0x1c]
	add r0, sp, #0x20
	str r0, [sp, #0xc]
_0223B328:
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x14]
	add r1, #0xd
	mov r2, #0
	bl GetMonData
	ldr r1, [sp, #0xc]
	strb r0, [r1]
	add r0, r1, #0
	ldrb r1, [r0]
	ldr r0, [sp, #0x18]
	add r0, r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x18]
	ldr r0, [sp, #0xc]
	add r0, r0, #1
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x1c]
	add r0, r0, #1
	str r0, [sp, #0x1c]
	cmp r0, #6
	blt _0223B328
	mov r0, #0
	str r0, [sp, #8]
	add r0, sp, #0x20
	str r0, [sp, #0x10]
_0223B35E:
	ldr r1, [sp, #0x18]
	ldr r0, _0223B498 ; =0x000001FE
	cmp r1, r0
	blo _0223B368
	b _0223B48C
_0223B368:
	ldr r0, [sp, #8]
	cmp r0, #5
	bhi _0223B414
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223B37A: ; jump table
	.short _0223B386 - _0223B37A - 2 ; case 0
	.short _0223B39E - _0223B37A - 2 ; case 1
	.short _0223B3B6 - _0223B37A - 2 ; case 2
	.short _0223B3CE - _0223B37A - 2 ; case 3
	.short _0223B3E6 - _0223B37A - 2 ; case 4
	.short _0223B3FE - _0223B37A - 2 ; case 5
_0223B386:
	add r0, r7, #0
	mov r1, #0xa
	bl GetPersonalAttr
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	cmp r5, #0x79
	bne _0223B414
	add r0, r4, r6
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	b _0223B414
_0223B39E:
	add r0, r7, #0
	mov r1, #0xb
	bl GetPersonalAttr
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	cmp r5, #0x74
	bne _0223B414
	add r0, r4, r6
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	b _0223B414
_0223B3B6:
	add r0, r7, #0
	mov r1, #0xc
	bl GetPersonalAttr
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	cmp r5, #0x75
	bne _0223B414
	add r0, r4, r6
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	b _0223B414
_0223B3CE:
	add r0, r7, #0
	mov r1, #0xd
	bl GetPersonalAttr
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	cmp r5, #0x78
	bne _0223B414
	add r0, r4, r6
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	b _0223B414
_0223B3E6:
	add r0, r7, #0
	mov r1, #0xe
	bl GetPersonalAttr
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	cmp r5, #0x76
	bne _0223B414
	add r0, r4, r6
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	b _0223B414
_0223B3FE:
	add r0, r7, #0
	mov r1, #0xf
	bl GetPersonalAttr
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	cmp r5, #0x77
	bne _0223B414
	add r0, r4, r6
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
_0223B414:
	ldr r0, [sp, #4]
	bl MaskOfFlagNo
	add r1, r0, #0
	lsl r1, r1, #0x18
	ldr r0, [sp]
	lsr r1, r1, #0x18
	bl Party_MaskMonsWithPokerus
	cmp r0, #0
	beq _0223B42E
	lsl r0, r4, #0x11
	asr r4, r0, #0x10
_0223B42E:
	cmp r5, #0x31
	bne _0223B436
	lsl r0, r4, #0x11
	asr r4, r0, #0x10
_0223B436:
	ldr r0, [sp, #0x18]
	ldr r1, _0223B498 ; =0x000001FE
	add r0, r0, r4
	cmp r0, r1
	ble _0223B448
	sub r0, r0, r1
	sub r0, r4, r0
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
_0223B448:
	ldr r0, [sp, #0x10]
	ldrb r0, [r0]
	add r0, r0, r4
	cmp r0, #0xff
	ble _0223B45A
	sub r0, #0xff
	sub r0, r4, r0
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
_0223B45A:
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x10]
	ldrb r0, [r0]
	add r1, r0, r4
	ldr r0, [sp, #0x10]
	strb r1, [r0]
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #8]
	add r0, r0, r4
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	add r1, #0xd
	bl SetMonData
	ldr r0, [sp, #0x10]
	add r0, r0, #1
	str r0, [sp, #0x10]
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
	cmp r0, #6
	bge _0223B48C
	b _0223B35E
_0223B48C:
	add r0, r7, #0
	bl FreeMonPersonal
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223B498: .word 0x000001FE

	thumb_func_start ov11_0223B49C
ov11_0223B49C: ; 0x0223B49C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x158
	add r4, r1, #0
	str r0, [sp, #0x10]
	ldr r0, [r4]
	bl ov11_022300C4
	str r0, [sp, #0x20]
	ldr r0, [r4]
	bl ov11_022300CC
	add r5, r0, #0
	ldr r0, [r4]
	bl ov11_02230068
	mov r7, #1
	str r0, [sp, #0x24]
	add r0, r7, #0
	ldr r6, [r4, #4]
	bl MaskOfFlagNo
	ldr r1, _0223B7F0 ; =0x00003108
	ldrb r1, [r6, r1]
	tst r0, r1
	beq _0223B4D0
	mov r7, #3
_0223B4D0:
	ldr r0, [r4, #0x28]
	cmp r0, #0x20
	bls _0223B4DA
	bl _0223BFD0
_0223B4DA:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223B4E6: ; jump table
	.short _0223B528 - _0223B4E6 - 2 ; case 0
	.short _0223B5E8 - _0223B4E6 - 2 ; case 1
	.short _0223B634 - _0223B4E6 - 2 ; case 2
	.short _0223B662 - _0223B4E6 - 2 ; case 3
	.short _0223B68C - _0223B4E6 - 2 ; case 4
	.short _0223B6A0 - _0223B4E6 - 2 ; case 5
	.short _0223B6D4 - _0223B4E6 - 2 ; case 6
	.short _0223B6F6 - _0223B4E6 - 2 ; case 7
	.short _0223B716 - _0223B4E6 - 2 ; case 8
	.short _0223B75C - _0223B4E6 - 2 ; case 9
	.short _0223B77A - _0223B4E6 - 2 ; case 10
	.short _0223B8BC - _0223B4E6 - 2 ; case 11
	.short _0223B90A - _0223B4E6 - 2 ; case 12
	.short _0223B990 - _0223B4E6 - 2 ; case 13
	.short _0223B9E4 - _0223B4E6 - 2 ; case 14
	.short _0223BA12 - _0223B4E6 - 2 ; case 15
	.short _0223BA42 - _0223B4E6 - 2 ; case 16
	.short _0223BAC4 - _0223B4E6 - 2 ; case 17
	.short _0223BAEA - _0223B4E6 - 2 ; case 18
	.short _0223BB12 - _0223B4E6 - 2 ; case 19
	.short _0223BB6A - _0223B4E6 - 2 ; case 20
	.short _0223BC38 - _0223B4E6 - 2 ; case 21
	.short _0223BC7E - _0223B4E6 - 2 ; case 22
	.short _0223BC7E - _0223B4E6 - 2 ; case 23
	.short _0223BDD8 - _0223B4E6 - 2 ; case 24
	.short _0223BE26 - _0223B4E6 - 2 ; case 25
	.short _0223BE62 - _0223B4E6 - 2 ; case 26
	.short _0223BEA6 - _0223B4E6 - 2 ; case 27
	.short _0223BED8 - _0223B4E6 - 2 ; case 28
	.short _0223BEF0 - _0223B4E6 - 2 ; case 29
	.short _0223BF06 - _0223B4E6 - 2 ; case 30
	.short _0223BF5E - _0223B4E6 - 2 ; case 31
	.short _0223BF8E - _0223B4E6 - 2 ; case 32
_0223B528:
	ldr r0, [r4, #0x24]
	cmp r0, #0
	bne _0223B5A4
	mov r0, #3
	str r0, [sp, #0x138]
	mov r0, #5
	str r0, [sp, #0x134]
	ldr r0, _0223B7F4 ; =0x00004E20
	add r0, r7, r0
	str r0, [sp, #0x13c]
	ldr r0, [r4, #0x2c]
	str r0, [sp, #0x140]
	ldr r0, [r4]
	bl ov11_02230078
	str r0, [sp, #0x14c]
	ldr r0, [r4]
	bl ov11_022300CC
	str r0, [sp, #0x150]
	mov r0, #1
	str r0, [sp, #0x144]
	mov r0, #0
	str r0, [sp, #0x148]
	ldr r0, [r4]
	str r0, [sp, #0x154]
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _0223B578
	cmp r7, #1
	bne _0223B572
	mov r0, #0x10
	str r0, [sp, #0x130]
	b _0223B57C
_0223B572:
	mov r0, #0x11
	str r0, [sp, #0x130]
	b _0223B57C
_0223B578:
	mov r0, #0xf
	str r0, [sp, #0x130]
_0223B57C:
	add r0, sp, #0x130
	bl ov08_02229918
	str r0, [r4, #8]
	mov r0, #1
	str r0, [r4, #0x28]
	ldr r0, _0223B7F8 ; =0x0000070A
	bl PlaySE
	ldr r2, [r4]
	ldr r0, _0223B7FC ; =0x0000241E
	ldrh r1, [r2, r0]
	add r1, r1, #1
	strh r1, [r2, r0]
	ldr r0, [r4, #8]
	mov r1, #0
	bl ov08_02228AB8
	add sp, #0x158
	pop {r3, r4, r5, r6, r7, pc}
_0223B5A4:
	ldr r0, [r4]
	mov r1, #0
	bl ov11_0222FF7C
	add r5, r0, #0
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_02229A80
	cmp r0, #4
	beq _0223B678
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	add r5, #0x88
	str r0, [r4, #8]
	mov r0, #0
	str r0, [r5]
	mov r0, #1
	str r0, [r4, #0x28]
	ldr r0, _0223B7F8 ; =0x0000070A
	bl PlaySE
	ldr r2, [r4]
	ldr r0, _0223B7FC ; =0x0000241E
	ldrh r1, [r2, r0]
	add r1, r1, #1
	strh r1, [r2, r0]
	ldr r0, [r4, #8]
	mov r1, #0
	bl ov08_02228AB8
	add sp, #0x158
	pop {r3, r4, r5, r6, r7, pc}
_0223B5E8:
	ldr r0, [r4, #8]
	mov r1, #0
	bl ov08_02228AC0
	cmp r0, #0
	bne _0223B678
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #1
	tst r0, r1
	beq _0223B618
	ldr r0, _0223B800 ; =0x000005E6
	mov r1, #0x75
	bl sub_020054A8
	ldr r0, [r4, #8]
	mov r1, #2
	bl ov08_02228AB8
	mov r0, #0x19
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223B618:
	ldr r0, _0223B804 ; =0x00000708
	mov r1, #0x75
	bl sub_020054A8
	ldr r0, [r4, #8]
	mov r1, #1
	bl ov08_02228AB8
	mov r0, #2
	str r0, [r4, #0x28]
	mov r0, #0x17
	add sp, #0x158
	str r0, [r4, #0x34]
	pop {r3, r4, r5, r6, r7, pc}
_0223B634:
	ldr r0, [r4, #0x34]
	sub r0, r0, #1
	str r0, [r4, #0x34]
	bne _0223B678
	ldr r0, [r4]
	ldr r2, [r4, #0x2c]
	add r1, r7, #0
	bl ov11_02254EA8
	ldr r0, [r4]
	ldr r1, [r4, #4]
	bl CalcBallShakesOnMonCatch
	str r0, [r4, #0x38]
	cmp r0, #4
	bge _0223B656
	b _0223B658
_0223B656:
	mov r0, #3
_0223B658:
	str r0, [r4, #0x3c]
	mov r0, #3
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223B662:
	ldr r0, [r4, #8]
	mov r1, #1
	bl ov08_02228AC0
	cmp r0, #0
	bne _0223B678
	ldr r0, [r4, #4]
	bl ov11_02243388
	cmp r0, #0
	bne _0223B67C
_0223B678:
	bl _0223BFD0
_0223B67C:
	ldr r0, [r4, #8]
	mov r1, #3
	bl ov08_02228AB8
	mov r0, #4
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223B68C:
	ldr r0, [r4, #8]
	mov r1, #3
	bl ov08_02228AC0
	cmp r0, #0
	bne _0223B78E
	mov r0, #5
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223B6A0:
	ldr r0, [r4, #0x3c]
	cmp r0, #0
	bne _0223B6C0
	ldr r0, [r4, #0x38]
	cmp r0, #4
	bne _0223B6B8
	mov r0, #7
	str r0, [r4, #0x28]
	mov r0, #0xc
	add sp, #0x158
	str r0, [r4, #0x34]
	pop {r3, r4, r5, r6, r7, pc}
_0223B6B8:
	mov r0, #0x1c
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223B6C0:
	ldr r0, [r4, #8]
	mov r1, #4
	bl ov08_02228AB8
	mov r0, #6
	str r0, [r4, #0x28]
	mov r0, #0xc
	add sp, #0x158
	str r0, [r4, #0x34]
	pop {r3, r4, r5, r6, r7, pc}
_0223B6D4:
	ldr r0, [r4, #8]
	mov r1, #4
	bl ov08_02228AC0
	cmp r0, #0
	bne _0223B78E
	ldr r0, [r4, #0x34]
	sub r0, r0, #1
	str r0, [r4, #0x34]
	bne _0223B78E
	ldr r0, [r4, #0x3c]
	add sp, #0x158
	sub r0, r0, #1
	str r0, [r4, #0x3c]
	mov r0, #5
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223B6F6:
	ldr r0, [r4, #0x34]
	sub r0, r0, #1
	str r0, [r4, #0x34]
	bne _0223B78E
	ldr r0, [r4, #8]
	mov r1, #6
	bl ov08_02228AB8
	ldr r0, _0223B808 ; =0x00000709
	mov r1, #0x75
	bl sub_020054A8
	mov r0, #8
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223B716:
	ldr r0, [r4, #8]
	mov r1, #6
	bl ov08_02228AC0
	cmp r0, #0
	bne _0223B78E
	ldr r1, _0223B80C ; =0x00000363
	add r0, sp, #0x10c
	strh r1, [r0, #2]
	mov r1, #0x82
	strb r1, [r0, #1]
	str r7, [sp, #0x110]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x20]
	add r2, sp, #0x10c
	bl ov11_0223178C
	str r0, [r4, #0x30]
	mov r0, #0x14
	str r0, [r4, #0x34]
	mov r0, #9
	str r0, [r4, #0x28]
	ldr r0, _0223B810 ; =0x00000467
	bl sub_0200521C
	ldr r0, [r4]
	mov r1, #2
	bl ov11_02231484
	add sp, #0x158
	pop {r3, r4, r5, r6, r7, pc}
_0223B75C:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_0201BD70
	cmp r0, #0
	bne _0223B78E
	mov r0, #0xa
	str r0, [r4, #0x28]
	ldr r0, [r4, #8]
	mov r1, #7
	bl ov08_02228AB8
	add sp, #0x158
	pop {r3, r4, r5, r6, r7, pc}
_0223B77A:
	ldr r0, [r4, #8]
	mov r1, #7
	bl ov08_02228AC0
	cmp r0, #0
	bne _0223B78E
	ldr r0, [r4, #0x34]
	sub r0, r0, #1
	str r0, [r4, #0x34]
	beq _0223B792
_0223B78E:
	bl _0223BFD0
_0223B792:
	ldr r0, [r4]
	add r1, r7, #0
	bl ov11_022314D4
	ldr r2, [r4, #4]
	ldr r0, [r4]
	add r3, r2, r7
	ldr r2, _0223B814 ; =0x0000219C
	add r1, r7, #0
	ldrb r2, [r3, r2]
	bl ov11_02230014
	add r6, r0, #0
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #6
	lsl r1, r1, #8
	tst r0, r1
	beq _0223B83C
	ldr r2, [r4, #4]
	ldr r0, [r4]
	add r3, r2, r7
	ldr r2, _0223B814 ; =0x0000219C
	add r1, r7, #0
	ldrb r2, [r3, r2]
	bl ov11_02230014
	add r2, r0, #0
	ldr r0, [r4]
	ldr r1, [r4, #4]
	bl ov11_0224AD38
	ldr r0, [r4]
	bl ov11_02230288
	mov r1, #1
	bl sub_020143A8
	mov r1, #0
	str r1, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	str r1, [sp, #8]
	ldr r2, _0223B818 ; =0x0000FFFF
	b _0223B81C
	nop
_0223B7F0: .word 0x00003108
_0223B7F4: .word 0x00004E20
_0223B7F8: .word 0x0000070A
_0223B7FC: .word 0x0000241E
_0223B800: .word 0x000005E6
_0223B804: .word 0x00000708
_0223B808: .word 0x00000709
_0223B80C: .word 0x00000363
_0223B810: .word 0x00000467
_0223B814: .word 0x0000219C
_0223B818: .word 0x0000FFFF
_0223B81C:
	add r0, r5, #0
	mov r1, #0xf
	mov r3, #1
	bl sub_02003210
	mov r1, #0
	ldr r0, [sp, #0x24]
	mov r2, #0x10
	add r3, r1, #0
	str r1, [sp]
	bl sub_02007E98
	mov r0, #0x20
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223B83C:
	add r0, r6, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	add r1, r0, #0
	ldr r0, [r4]
	bl ov11_02231668
	cmp r0, #0
	beq _0223B88A
	ldr r0, [r4]
	bl ov11_02230288
	mov r1, #1
	bl sub_020143A8
	mov r1, #0
	str r1, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	str r1, [sp, #8]
	ldr r2, _0223BBD4 ; =0x0000FFFF
	add r0, r5, #0
	mov r1, #5
	mov r3, #1
	bl sub_02003210
	mov r1, #0
	ldr r0, [sp, #0x24]
	mov r2, #0x10
	add r3, r1, #0
	str r1, [sp]
	bl sub_02007E98
	mov r0, #0x10
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223B88A:
	ldr r1, _0223BBD8 ; =0x00000367
	add r0, sp, #0xe8
	strh r1, [r0, #2]
	mov r1, #0x82
	strb r1, [r0, #1]
	str r7, [sp, #0xec]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x20]
	add r2, sp, #0xe8
	bl ov11_0223178C
	str r0, [r4, #0x30]
	mov r0, #0x14
	str r0, [r4, #0x34]
	mov r0, #0xb
	str r0, [r4, #0x28]
	ldr r0, [r4]
	bl ov11_0223129C
	add sp, #0x158
	pop {r3, r4, r5, r6, r7, pc}
_0223B8BC:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_0201BD70
	cmp r0, #0
	bne _0223B914
	ldr r0, [r4, #0x34]
	sub r0, r0, #1
	str r0, [r4, #0x34]
	bne _0223B914
	mov r0, #0xc
	str r0, [r4, #0x28]
	mov r1, #0
	str r1, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	str r1, [sp, #8]
	ldr r2, _0223BBD4 ; =0x0000FFFF
	add r0, r5, #0
	mov r1, #5
	mov r3, #1
	bl sub_02003210
	mov r1, #0
	ldr r0, [sp, #0x24]
	str r1, [sp]
	mov r2, #0x10
	add r3, r1, #0
	bl sub_02007E98
	ldr r0, [r4]
	bl ov11_02230288
	mov r1, #1
	bl sub_020143A8
	add sp, #0x158
	pop {r3, r4, r5, r6, r7, pc}
_0223B90A:
	add r0, r5, #0
	bl sub_020038E4
	cmp r0, #0
	beq _0223B916
_0223B914:
	b _0223BFD0
_0223B916:
	ldr r0, [r4, #8]
	bl ov08_02229A2C
	ldr r0, [sp, #0x24]
	bl sub_02007540
	ldr r0, [r4]
	bl ov11_0222D944
	ldr r0, [r4]
	mov r1, #0
	bl ov11_02230088
	mov r1, #0
	bl ov11_022583C8
	ldr r0, [r4]
	mov r1, #1
	bl ov11_02230088
	mov r1, #0
	bl ov11_022583C8
	ldr r0, [r4]
	bl ov11_0222FF68
	str r0, [sp, #0xd0]
	ldr r0, [r4]
	bl ov11_022300CC
	str r0, [sp, #0xd4]
	ldr r0, [sp, #0x24]
	add r1, r7, #0
	str r0, [sp, #0xd8]
	mov r0, #5
	str r0, [sp, #0xdc]
	ldr r2, [r4, #4]
	ldr r0, [r4]
	add r3, r2, r7
	ldr r2, _0223BBDC ; =0x0000219C
	ldrb r2, [r3, r2]
	bl ov11_02230014
	str r0, [sp, #0xe0]
	ldr r0, [r4]
	bl ov11_022300D0
	bl Pokedex_IsNatDexEnabled
	str r0, [sp, #0xe4]
	bl sub_0201D658
	str r0, [r4, #0x54]
	add r0, sp, #0xd0
	bl ov16_021EEF0C
	str r0, [r4, #0x50]
	mov r0, #0xd
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223B990:
	ldr r0, [r4, #0x50]
	bl ov16_021EEF84
	cmp r0, #0
	beq _0223BA4C
	ldr r0, _0223BBE0 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _0223B9AA
	mov r0, #0xe
	str r0, [r4, #0x28]
	b _0223B9BC
_0223B9AA:
	bl sub_02020AA4
	cmp r0, #0
	beq _0223B9BC
	ldr r0, _0223BBE4 ; =0x000005DC
	bl PlaySE
	mov r0, #0xe
	str r0, [r4, #0x28]
_0223B9BC:
	ldr r0, [r4, #0x28]
	cmp r0, #0xe
	bne _0223BA4C
	mov r1, #0
	str r1, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	str r1, [sp, #8]
	ldr r2, _0223BBD4 ; =0x0000FFFF
	add r0, r5, #0
	mov r1, #5
	mov r3, #1
	bl sub_02003210
	ldr r0, [r4, #0x50]
	mov r1, #0
	bl ov05_021EEF9C
	add sp, #0x158
	pop {r3, r4, r5, r6, r7, pc}
_0223B9E4:
	ldr r0, [r4, #0x50]
	bl ov16_021EEF98
	add r5, r0, #0
	mov r1, #0
	mov r2, #4
	bl sub_020079E0
	add r0, r5, #0
	mov r1, #0
	bl sub_0200782C
	cmp r0, #0x80
	blt _0223BA4C
	add r0, r5, #0
	mov r1, #0
	mov r2, #0x80
	bl sub_02007558
	mov r0, #0xf
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223BA12:
	ldr r0, [r4, #0x50]
	bl ov05_021EEF68
	ldr r0, [r4, #0x54]
	bl sub_0201D674
	ldr r0, [r4]
	bl ov11_0222D980
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r2, _0223BBD4 ; =0x0000FFFF
	add r0, r5, #0
	mov r1, #5
	mov r3, #1
	bl sub_02003210
	mov r0, #0x11
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223BA42:
	add r0, r5, #0
	bl sub_020038E4
	cmp r0, #0
	beq _0223BA4E
_0223BA4C:
	b _0223BFD0
_0223BA4E:
	ldr r2, [r4, #4]
	ldr r0, [r4]
	add r3, r2, r7
	ldr r2, _0223BBDC ; =0x0000219C
	add r1, r7, #0
	ldrb r2, [r3, r2]
	bl ov11_02230014
	add r6, r0, #0
	ldr r0, [r4, #8]
	bl ov08_02229A2C
	ldr r0, [sp, #0x24]
	bl sub_02007540
	ldr r0, [r4]
	bl ov11_0222D944
	ldr r0, [r4]
	bl ov11_0222D980
	add r0, sp, #0xc0
	add r1, r6, #0
	mov r2, #2
	bl sub_02068B68
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x24]
	add r1, sp, #0xc0
	mov r2, #0x80
	mov r3, #0x48
	bl sub_020073A0
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r2, _0223BBD4 ; =0x0000FFFF
	add r0, r5, #0
	mov r1, #5
	mov r3, #1
	bl sub_02003210
	mov r2, #0
	ldr r0, [sp, #0x24]
	mov r1, #0x10
	add r3, r2, #0
	str r2, [sp]
	bl sub_02007E98
	mov r0, #0x11
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223BAC4:
	add r0, r5, #0
	bl sub_020038E4
	cmp r0, #0
	bne _0223BB74
	mov r0, #0x12
	str r0, [r4, #0x28]
	ldr r0, [r4]
	bl ov11_02230288
	mov r1, #0
	bl sub_020143A8
	add r0, r5, #0
	mov r1, #1
	bl sub_020038F0
	add sp, #0x158
	pop {r3, r4, r5, r6, r7, pc}
_0223BAEA:
	ldr r1, [r4, #4]
	mov r0, #5
	str r0, [sp]
	mov r2, #0
	ldr r0, _0223BBDC ; =0x0000219C
	str r2, [sp, #4]
	add r3, r1, r7
	ldrb r0, [r3, r0]
	mov r3, #0xd9
	lsl r3, r3, #2
	orr r0, r7
	str r0, [sp, #8]
	ldr r0, [r4]
	bl ov11_02255980
	ldr r0, [r4, #0x28]
	add sp, #0x158
	add r0, r0, #1
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223BB12:
	add r0, r6, #0
	mov r1, #0
	bl ov11_0224AD90
	cmp r0, #0
	beq _0223BB74
	ldr r0, [r4, #4]
	mov r1, #0
	bl ov11_0224AD90
	cmp r0, #0xff
	bne _0223BB32
	mov r0, #0x16
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223BB32:
	ldr r0, [r4]
	bl ov11_02230288
	mov r1, #1
	bl sub_020143A8
	mov r1, #0
	str r1, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	str r1, [sp, #8]
	ldr r2, _0223BBD4 ; =0x0000FFFF
	add r0, r5, #0
	mov r1, #0xf
	mov r3, #1
	bl sub_02003210
	mov r1, #0
	ldr r0, [sp, #0x24]
	mov r2, #0x10
	add r3, r1, #0
	str r1, [sp]
	bl sub_02007E98
	mov r0, #0x14
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223BB6A:
	add r0, r5, #0
	bl sub_020038E4
	cmp r0, #0
	beq _0223BB76
_0223BB74:
	b _0223BFD0
_0223BB76:
	mov r0, #0
	add r1, r0, #0
	bl sub_0200E3A0
	mov r0, #1
	mov r1, #0
	bl sub_0200E3A0
	ldr r2, [r4, #4]
	ldr r0, [r4]
	add r3, r2, r7
	ldr r2, _0223BBDC ; =0x0000219C
	add r1, r7, #0
	ldrb r2, [r3, r2]
	bl ov11_02230014
	mov r1, #5
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	add r5, r0, #0
	ldr r0, [r4]
	bl ov11_02230E18
	str r0, [sp]
	mov r0, #5
	mov r1, #1
	add r2, r5, #0
	mov r3, #0xa
	bl sub_02077A84
	add r5, r0, #0
	str r5, [r4, #0x54]
	ldr r0, [r4]
	mov r1, #0
	bl ov11_0222FFC8
	cmp r0, #6
	bge _0223BBCA
	mov r0, #0
	b _0223BBEE
_0223BBCA:
	ldr r0, [r4]
	bl ov11_02231280
	ldr r1, _0223BBE8 ; =0x00000496
	b _0223BBEC
	.align 2, 0
_0223BBD4: .word 0x0000FFFF
_0223BBD8: .word 0x00000367
_0223BBDC: .word 0x0000219C
_0223BBE0: .word gSystem
_0223BBE4: .word 0x000005DC
_0223BBE8: .word 0x00000496
_0223BBEC:
	add r0, r0, r1
_0223BBEE:
	str r0, [r5, #0x44]
	add r0, r6, #0
	mov r1, #0x70
	mov r2, #0
	bl GetMonData
	str r0, [r5, #8]
	ldr r0, [r4]
	bl ov11_02230290
	str r0, [r5, #0x48]
	add r0, r6, #0
	mov r1, #0x6f
	mov r2, #0
	bl GetMonData
	str r0, [r5, #0x10]
	ldr r0, _0223BF18 ; =UNK_020FA5FC
	add r1, r5, #0
	mov r2, #5
	bl OverlayManager_New
	str r0, [r4, #0x50]
	mov r0, #0x15
	str r0, [r4, #0x28]
	ldr r0, [r4]
	bl ov11_02231438
	ldr r0, [r4]
	bl ov11_0222D840
	ldr r0, [r4]
	mov r1, #1
	bl ov11_02231338
	add sp, #0x158
	pop {r3, r4, r5, r6, r7, pc}
_0223BC38:
	ldr r0, [r4, #0x50]
	bl OverlayManager_Run
	cmp r0, #0
	beq _0223BC88
	ldr r2, [r4, #4]
	ldr r5, [r4, #0x54]
	add r3, r2, r7
	ldr r2, _0223BF1C ; =0x0000219C
	ldr r0, [r4]
	ldrb r2, [r3, r2]
	add r1, r7, #0
	bl ov11_02230014
	ldr r1, [r5, #0x14]
	cmp r1, #0
	bne _0223BC62
	ldr r2, [r5, #0x18]
	mov r1, #0x77
	bl SetMonData
_0223BC62:
	add r0, r5, #0
	bl sub_02077AC4
	ldr r0, [r4, #0x50]
	bl OverlayManager_Delete
	ldr r0, [r4]
	mov r1, #2
	bl ov11_02231338
	mov r0, #0x17
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223BC7E:
	add r0, r5, #0
	bl sub_020038E4
	cmp r0, #0
	beq _0223BC8A
_0223BC88:
	b _0223BFD0
_0223BC8A:
	ldr r0, [r4]
	mov r1, #0
	bl ov11_0222FF88
	ldr r2, [r4, #4]
	str r0, [sp, #0x28]
	add r3, r2, r7
	ldr r2, _0223BF1C ; =0x0000219C
	ldr r0, [r4]
	ldrb r2, [r3, r2]
	add r1, r7, #0
	bl ov11_02230014
	add r6, r0, #0
	ldr r0, [r4]
	add r1, r7, #0
	bl ov11_02231628
	ldr r0, [r4]
	ldr r1, [r4, #4]
	add r2, r6, #0
	bl ov11_0224AD38
	ldr r0, [r4]
	add r1, r6, #0
	bl ov11_02230F88
	ldr r0, [r4]
	add r1, r6, #0
	bl ov11_02230FA8
	mov r1, #0
	ldr r0, [r4]
	add r2, r1, #0
	mov r3, #9
	bl ov11_022564A8
	ldr r0, [sp, #0x28]
	add r1, r6, #0
	bl Party_AddMon
	cmp r0, #1
	bne _0223BD1E
	ldr r0, [r4, #0x28]
	cmp r0, #0x16
	bne _0223BD16
	ldr r0, [r4]
	bl ov11_02230288
	mov r1, #1
	bl sub_020143A8
	mov r1, #0
	str r1, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	str r1, [sp, #8]
	ldr r2, _0223BF20 ; =0x0000FFFF
	add r0, r5, #0
	mov r1, #0xf
	mov r3, #1
	bl sub_02003210
	mov r1, #0
	ldr r0, [sp, #0x24]
	mov r2, #0x10
	add r3, r1, #0
	str r1, [sp]
	bl sub_02007E98
_0223BD16:
	mov r0, #0x20
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223BD1E:
	ldr r0, [r4]
	bl ov11_02230290
	str r0, [sp, #0x1c]
	bl PCStorage_GetActiveBox
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	bl PCStorage_FindFirstBoxWithEmptySlot
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x14]
	bl PCStorage_SetActiveBox
	mov r5, #0
_0223BD3E:
	add r1, r5, #0
	add r0, r6, #0
	add r1, #0x42
	mov r2, #0
	bl GetMonData
	add r1, r5, #0
	str r0, [sp, #0x2c]
	add r0, r6, #0
	add r1, #0x3a
	add r2, sp, #0x2c
	bl SetMonData
	add r5, r5, #1
	cmp r5, #4
	blt _0223BD3E
	add r0, r6, #0
	bl sub_020690E4
	add r2, r0, #0
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x14]
	bl PCStorage_PlaceMonInBoxFirstEmptySlot
	ldr r0, [r4, #0x28]
	cmp r0, #0x16
	bne _0223BDD0
	ldr r1, [sp, #0x18]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	ldr r0, [r4]
	bne _0223BD96
	bl ov11_02231280
	ldr r1, _0223BF24 ; =0x00000496
	add r1, r0, r1
	add r0, sp, #0x9c
	strh r1, [r0, #2]
	mov r1, #0x93
	strb r1, [r0, #1]
	ldr r0, [sp, #0x18]
	str r7, [sp, #0xa0]
	str r0, [sp, #0xa4]
	b _0223BDB0
_0223BD96:
	bl ov11_02231280
	ldr r1, _0223BF28 ; =0x00000498
	add r1, r0, r1
	add r0, sp, #0x9c
	strh r1, [r0, #2]
	mov r1, #0xaf
	strb r1, [r0, #1]
	ldr r0, [sp, #0x18]
	str r7, [sp, #0xa0]
	str r0, [sp, #0xa4]
	ldr r0, [sp, #0x14]
	str r0, [sp, #0xa8]
_0223BDB0:
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x20]
	add r2, sp, #0x9c
	bl ov11_0223178C
	str r0, [r4, #0x30]
	mov r0, #0x14
	str r0, [r4, #0x34]
	mov r0, #0x18
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223BDD0:
	mov r0, #0x20
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223BDD8:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_0201BD70
	cmp r0, #0
	bne _0223BEBC
	ldr r0, [r4, #0x34]
	sub r0, r0, #1
	str r0, [r4, #0x34]
	bne _0223BEBC
	ldr r0, [r4]
	bl ov11_02230288
	mov r1, #1
	bl sub_020143A8
	mov r1, #0
	str r1, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	str r1, [sp, #8]
	ldr r2, _0223BF20 ; =0x0000FFFF
	add r0, r5, #0
	mov r1, #0xf
	mov r3, #1
	bl sub_02003210
	mov r1, #0
	ldr r0, [sp, #0x24]
	mov r2, #0x10
	add r3, r1, #0
	str r1, [sp]
	bl sub_02007E98
	mov r0, #0x20
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223BE26:
	ldr r0, [r4, #8]
	mov r1, #2
	bl ov08_02228AC0
	cmp r0, #0
	bne _0223BEBC
	ldr r0, [r4, #8]
	bl ov08_02229A2C
	ldr r1, _0223BF2C ; =0x0000035B
	add r0, sp, #0x78
	strh r1, [r0, #2]
	mov r1, #0
	strb r1, [r0, #1]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x20]
	add r2, sp, #0x78
	bl ov11_0223178C
	str r0, [r4, #0x30]
	mov r0, #0x14
	str r0, [r4, #0x34]
	mov r0, #0x1a
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223BE62:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_0201BD70
	cmp r0, #0
	bne _0223BEBC
	ldr r0, [r4, #0x34]
	sub r0, r0, #1
	str r0, [r4, #0x34]
	bne _0223BEBC
	mov r1, #0xd7
	lsl r1, r1, #2
	add r0, sp, #0x2c
	strh r1, [r0, #0x2a]
	mov r1, #0
	add r0, sp, #0x54
	strb r1, [r0, #1]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x20]
	add r2, sp, #0x54
	bl ov11_0223178C
	str r0, [r4, #0x30]
	mov r0, #0x14
	str r0, [r4, #0x34]
	mov r0, #0x1b
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223BEA6:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_0201BD70
	cmp r0, #0
	bne _0223BEBC
	ldr r0, [r4, #0x34]
	sub r0, r0, #1
	str r0, [r4, #0x34]
	beq _0223BEBE
_0223BEBC:
	b _0223BFD0
_0223BEBE:
	mov r0, #0x5e
	ldr r1, [r4, #4]
	mov r2, #0
	lsl r0, r0, #2
	str r2, [r1, r0]
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [sp, #0x10]
	bl sub_0200CAB4
	add sp, #0x158
	pop {r3, r4, r5, r6, r7, pc}
_0223BED8:
	ldr r0, [r4]
	ldr r2, [r4, #0x2c]
	add r1, r7, #0
	mov r3, #1
	bl ov11_02254B40
	mov r0, #0x1d
	str r0, [r4, #0x28]
	mov r0, #2
	add sp, #0x158
	str r0, [r4, #0x34]
	pop {r3, r4, r5, r6, r7, pc}
_0223BEF0:
	ldr r0, [r4, #0x34]
	sub r0, r0, #1
	str r0, [r4, #0x34]
	bne _0223BFD0
	ldr r0, [r4, #8]
	bl ov08_02229A2C
	mov r0, #0x1e
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223BF06:
	add r0, r6, #0
	bl ov11_02243388
	cmp r0, #0
	beq _0223BFD0
	ldr r1, [r4, #0x38]
	ldr r0, _0223BF30 ; =0x0000035F
	b _0223BF34
	nop
_0223BF18: .word UNK_020FA5FC
_0223BF1C: .word 0x0000219C
_0223BF20: .word 0x0000FFFF
_0223BF24: .word 0x00000496
_0223BF28: .word 0x00000498
_0223BF2C: .word 0x0000035B
_0223BF30: .word 0x0000035F
_0223BF34:
	add r1, r1, r0
	add r0, sp, #0x2c
	strh r1, [r0, #6]
	mov r1, #0
	strb r1, [r0, #5]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	ldr r1, [sp, #0x20]
	add r2, sp, #0x30
	bl ov11_0223178C
	str r0, [r4, #0x30]
	mov r0, #0x14
	str r0, [r4, #0x34]
	mov r0, #0x1f
	add sp, #0x158
	str r0, [r4, #0x28]
	pop {r3, r4, r5, r6, r7, pc}
_0223BF5E:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_0201BD70
	cmp r0, #0
	bne _0223BFD0
	ldr r0, [r4, #0x34]
	sub r0, r0, #1
	str r0, [r4, #0x34]
	bne _0223BFD0
	mov r0, #0x5e
	ldr r1, [r4, #4]
	mov r2, #0
	lsl r0, r0, #2
	str r2, [r1, r0]
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [sp, #0x10]
	bl sub_0200CAB4
	add sp, #0x158
	pop {r3, r4, r5, r6, r7, pc}
_0223BF8E:
	add r0, r5, #0
	bl sub_020038E4
	cmp r0, #0
	bne _0223BFD0
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #6
	lsl r1, r1, #8
	tst r0, r1
	beq _0223BFB2
	ldr r0, [r4, #8]
	bl ov08_02229A2C
	ldr r0, [sp, #0x24]
	bl sub_02007540
_0223BFB2:
	ldr r1, [r4]
	ldr r0, _0223BFD4 ; =0x0000241C
	mov r2, #4
	strb r2, [r1, r0]
	mov r0, #0x5e
	ldr r1, [r4, #4]
	mov r2, #0
	lsl r0, r0, #2
	str r2, [r1, r0]
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [sp, #0x10]
	bl sub_0200CAB4
_0223BFD0:
	add sp, #0x158
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223BFD4: .word 0x0000241C

	thumb_func_start CalcBallShakesOnMonCatch
CalcBallShakesOnMonCatch: ; 0x0223BFD8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r4, r1, #0
	bl ov11_0222FF74
	mov r1, #6
	lsl r1, r1, #8
	tst r0, r1
	beq _0223BFEE
	mov r0, #4
	pop {r3, r4, r5, r6, r7, pc}
_0223BFEE:
	mov r0, #0x4a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r1, [r4, #0x6c]
	cmp r0, #5
	bne _0223C026
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	mov r0, #0xb5
	lsl r0, r0, #6
	ldrh r0, [r1, r0]
	mov r1, #8 ; BASE_CATCH_RATE
	bl GetMonBaseStat
	ldr r1, _0223C200 ; =0x0000311C
	ldr r2, _0223C204 ; =ov11_0225DCF0
	ldrb r1, [r4, r1]
	lsl r1, r1, #1
	ldrb r2, [r2, r1]
	mul r2, r0
	add r0, r2, #0
	ldr r2, _0223C208 ; =ov11_0225DCF0 + 1
	ldrb r1, [r2, r1]
	bl _u32_div_f
	str r0, [sp]
	b _0223C03A
_0223C026:
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	mov r0, #0xb5
	lsl r0, r0, #6
	ldrh r0, [r1, r0]
	mov r1, #8 ; BASE_CATCH_RATE
	bl GetMonBaseStat
	str r0, [sp]
_0223C03A:
	ldr r1, [r4, #0x6c]
	add r0, r4, #0
	mov r2, #0x1b
	mov r3, #0
	mov r5, #0xa
	bl ov11_02243420
	add r7, r0, #0
	ldr r1, [r4, #0x6c]
	add r0, r4, #0
	mov r2, #0x1c
	mov r3, #0
	bl ov11_02243420
	add r1, r0, #0
	mov r0, #0x4a
	lsl r0, r0, #2
	ldr r2, [r4, r0]
	cmp r2, #5
	ble _0223C128
	cmp r2, #0xf
	bhi _0223C12E
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0223C072: ; jump table
	.short _0223C12E - _0223C072 - 2 ; case 0
	.short _0223C12E - _0223C072 - 2 ; case 1
	.short _0223C12E - _0223C072 - 2 ; case 2
	.short _0223C12E - _0223C072 - 2 ; case 3
	.short _0223C12E - _0223C072 - 2 ; case 4
	.short _0223C12E - _0223C072 - 2 ; case 5
	.short _0223C092 - _0223C072 - 2 ; case 6
	.short _0223C0A6 - _0223C072 - 2 ; case 7
	.short _0223C0B4 - _0223C072 - 2 ; case 8
	.short _0223C0D0 - _0223C072 - 2 ; case 9
	.short _0223C0EC - _0223C072 - 2 ; case 10
	.short _0223C12E - _0223C072 - 2 ; case 11
	.short _0223C12E - _0223C072 - 2 ; case 12
	.short _0223C0FA - _0223C072 - 2 ; case 13
	.short _0223C12E - _0223C072 - 2 ; case 14
	.short _0223C11C - _0223C072 - 2 ; case 15
_0223C092:
	cmp r7, #0xb
	beq _0223C0A2
	cmp r1, #0xb
	beq _0223C0A2
	cmp r7, #6
	beq _0223C0A2
	cmp r1, #6
	bne _0223C12E
_0223C0A2:
	mov r5, #0x1e
	b _0223C12E
_0223C0A6:
	add r0, r6, #0
	bl ov11_02230294
	cmp r0, #7
	bne _0223C12E
	mov r5, #0x23
	b _0223C12E
_0223C0B4:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0223C20C ; =0x00002D74
	ldrb r1, [r1, r0]
	cmp r1, #0x28
	bhs _0223C12E
	mov r0, #0x28
	sub r5, r0, r1
	cmp r5, #0xa
	bhs _0223C12E
	mov r5, #0xa
	b _0223C12E
_0223C0D0:
	ldr r2, [r4, #0x6c]
	mov r1, #0xc0
	mul r1, r2
	add r2, r4, r1
	mov r1, #0xb5
	lsl r1, r1, #6
	ldrh r1, [r2, r1]
	add r0, r6, #0
	bl ov11_02231668
	cmp r0, #1
	bne _0223C12E
	mov r5, #0x1e
	b _0223C12E
_0223C0EC:
	add r0, #0x28
	ldr r5, [r4, r0]
	add r5, #0xa
	cmp r5, #0x28
	bls _0223C12E
	mov r5, #0x28
	b _0223C12E
_0223C0FA:
	add r0, r6, #0
	bl ov11_02230C5C
	cmp r0, #3
	beq _0223C118
	add r0, r6, #0
	bl ov11_02230C5C
	cmp r0, #4
	beq _0223C118
	add r0, r6, #0
	bl ov11_02230294
	cmp r0, #5
	bne _0223C12E
_0223C118:
	mov r5, #0x23
	b _0223C12E
_0223C11C:
	add r0, #0x28
	ldr r0, [r4, r0]
	cmp r0, #1
	bge _0223C12E
	mov r5, #0x28
	b _0223C12E
_0223C128:
	ldr r0, _0223C210 ; =ov11_0225DC28
	sub r1, r2, #2
	ldrb r5, [r0, r1]
_0223C12E:
	ldr r1, [r4, #0x6c]
	mov r0, #0xc0
	add r6, r1, #0
	mul r6, r0
	ldr r0, _0223C214 ; =0x00002D90
	add r1, r4, r6
	ldr r1, [r1, r0]
	lsl r0, r1, #1
	add r7, r1, r0
	ldr r1, [sp]
	add r0, r1, #0
	mul r0, r5
	mov r1, #0xa
	bl _u32_div_f
	ldr r1, _0223C218 ; =0x00002D8C
	add r2, r4, r6
	ldr r1, [r2, r1]
	lsl r1, r1, #1
	sub r1, r7, r1
	mul r1, r0
	add r0, r1, #0
	add r1, r7, #0
	bl _u32_div_f
	add r1, r0, #0
	ldr r0, _0223C21C ; =0x00002DAC
	add r2, r4, r6
	ldr r2, [r2, r0]
	mov r0, #0x27
	tst r0, r2
	beq _0223C170
	lsl r1, r1, #1
_0223C170:
	mov r0, #0xd8
	tst r0, r2
	beq _0223C182
	mov r0, #0xf
	mul r0, r1
	mov r1, #0xa
	bl _u32_div_f
	add r1, r0, #0
_0223C182:
	cmp r1, #0xff
	blo _0223C18A
	mov r5, #4
	b _0223C1FA
_0223C18A:
	ldr r0, _0223C220 ; =0x040002B0
	mov r2, #0
	strh r2, [r0]
	mov r0, #0xff
	lsl r0, r0, #0x10
	bl _u32_div_f
	ldr r1, _0223C224 ; =0x040002B8
	add r2, r1, #0
	str r0, [r1]
	sub r2, #8
	lsr r0, r1, #0xb
_0223C1A2:
	ldrh r1, [r2]
	tst r1, r0
	bne _0223C1A2
	ldr r3, _0223C220 ; =0x040002B0
	lsr r0, r3, #0xb
_0223C1AC:
	ldrh r1, [r3]
	tst r1, r0
	bne _0223C1AC
	ldr r2, _0223C228 ; =0x040002B4
	mov r0, #0
	ldr r1, [r2]
	strh r0, [r3]
	mov r0, #2
	str r1, [r2, #4]
	sub r2, r2, #4
	lsl r0, r0, #0xe
_0223C1C2:
	ldrh r1, [r2]
	tst r1, r0
	bne _0223C1C2
	ldr r2, _0223C220 ; =0x040002B0
	lsr r0, r2, #0xb
_0223C1CC:
	ldrh r1, [r2]
	tst r1, r0
	bne _0223C1CC
	ldr r1, _0223C228 ; =0x040002B4
	ldr r0, _0223C22C ; =0x000FFFF0
	ldr r1, [r1]
	bl _u32_div_f
	add r6, r0, #0
	mov r5, #0
_0223C1E0:
	bl LCRandom
	cmp r0, r6
	bhs _0223C1EE
	add r5, r5, #1
	cmp r5, #4
	blt _0223C1E0
_0223C1EE:
	mov r0, #0x4a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _0223C1FA
	mov r5, #4
_0223C1FA:
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223C200: .word 0x0000311C
_0223C204: .word ov11_0225DCF0
_0223C208: .word ov11_0225DCF0 + 1
_0223C20C: .word 0x00002D74
_0223C210: .word ov11_0225DC28
_0223C214: .word 0x00002D90
_0223C218: .word 0x00002D8C
_0223C21C: .word 0x00002DAC
_0223C220: .word 0x040002B0
_0223C224: .word 0x040002B8
_0223C228: .word 0x040002B4
_0223C22C: .word 0x000FFFF0

	thumb_func_start ov11_0223C230
ov11_0223C230: ; 0x0223C230
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r0, #0
	add r6, r1, #0
	cmp r2, #0x16
	bgt _0223C27A
	cmp r2, #0
	blt _0223C280
	add r1, r2, r2
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223C24C: ; jump table
	.short _0223C280 - _0223C24C - 2 ; case 0
	.short _0223C280 - _0223C24C - 2 ; case 1
	.short _0223C284 - _0223C24C - 2 ; case 2
	.short _0223C320 - _0223C24C - 2 ; case 3
	.short _0223C29C - _0223C24C - 2 ; case 4
	.short _0223C288 - _0223C24C - 2 ; case 5
	.short _0223C28C - _0223C24C - 2 ; case 6
	.short _0223C290 - _0223C24C - 2 ; case 7
	.short _0223C296 - _0223C24C - 2 ; case 8
	.short _0223C346 - _0223C24C - 2 ; case 9
	.short _0223C2C2 - _0223C24C - 2 ; case 10
	.short _0223C36E - _0223C24C - 2 ; case 11
	.short _0223C2EA - _0223C24C - 2 ; case 12
	.short _0223C280 - _0223C24C - 2 ; case 13
	.short _0223C3A4 - _0223C24C - 2 ; case 14
	.short _0223C3AC - _0223C24C - 2 ; case 15
	.short _0223C3B4 - _0223C24C - 2 ; case 16
	.short _0223C3F0 - _0223C24C - 2 ; case 17
	.short _0223C280 - _0223C24C - 2 ; case 18
	.short _0223C42C - _0223C24C - 2 ; case 19
	.short _0223C456 - _0223C24C - 2 ; case 20
	.short _0223C480 - _0223C24C - 2 ; case 21
	.short _0223C28C - _0223C24C - 2 ; case 22
_0223C27A:
	cmp r2, #0xff
	bne _0223C280
	b _0223C480
_0223C280:
	ldr r5, [r6, #0x64]
	b _0223C486
_0223C284:
	ldr r5, [r6, #0x6c]
	b _0223C486
_0223C288:
	ldr r5, [r6, #0x74]
	b _0223C486
_0223C28C:
	ldr r5, [r6, #0x78]
	b _0223C486
_0223C290:
	add r6, #0x94
	ldr r5, [r6]
	b _0223C486
_0223C296:
	add r6, #0x80
	ldr r5, [r6]
	b _0223C486
_0223C29C:
	bl ov11_0222FF84
	add r6, r0, #0
	mov r5, #0
	cmp r6, #0
	ble _0223C2C0
	mov r7, #1
_0223C2AA:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _0223C48C ; =0x00000195
	ldrb r0, [r0, r1]
	tst r0, r7
	bne _0223C2C0
	add r5, r5, #1
	cmp r5, r6
	blt _0223C2AA
_0223C2C0:
	b _0223C486
_0223C2C2:
	bl ov11_0222FF84
	add r6, r0, #0
	mov r5, #0
	cmp r6, #0
	ble _0223C2E8
	ldr r7, _0223C48C ; =0x00000195
_0223C2D0:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldrb r0, [r0, r7]
	cmp r0, #3
	beq _0223C2E8
	cmp r0, #1
	beq _0223C2E8
	add r5, r5, #1
	cmp r5, r6
	blt _0223C2D0
_0223C2E8:
	b _0223C486
_0223C2EA:
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _0223C2F8
	mov r6, #5
	b _0223C2FA
_0223C2F8:
	mov r6, #1
_0223C2FA:
	add r0, r4, #0
	bl ov11_0222FF84
	add r7, r0, #0
	mov r5, #0
	cmp r7, #0
	ble _0223C31E
_0223C308:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _0223C48C ; =0x00000195
	ldrb r0, [r0, r1]
	cmp r0, r6
	beq _0223C31E
	add r5, r5, #1
	cmp r5, r7
	blt _0223C308
_0223C31E:
	b _0223C486
_0223C320:
	bl ov11_0222FF84
	add r6, r0, #0
	mov r5, #0
	cmp r6, #0
	ble _0223C344
	mov r7, #1
_0223C32E:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _0223C48C ; =0x00000195
	ldrb r0, [r0, r1]
	tst r0, r7
	beq _0223C344
	add r5, r5, #1
	cmp r5, r6
	blt _0223C32E
_0223C344:
	b _0223C486
_0223C346:
	bl ov11_0222FF84
	add r6, r0, #0
	mov r5, #0
	cmp r6, #0
	ble _0223C36C
	ldr r7, _0223C48C ; =0x00000195
_0223C354:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldrb r0, [r0, r7]
	cmp r0, #2
	beq _0223C36C
	cmp r0, #0
	beq _0223C36C
	add r5, r5, #1
	cmp r5, r6
	blt _0223C354
_0223C36C:
	b _0223C486
_0223C36E:
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _0223C37C
	mov r6, #4
	b _0223C37E
_0223C37C:
	mov r6, #0
_0223C37E:
	add r0, r4, #0
	bl ov11_0222FF84
	add r7, r0, #0
	mov r5, #0
	cmp r7, #0
	ble _0223C486
_0223C38C:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_0222FF7C
	ldr r1, _0223C48C ; =0x00000195
	ldrb r0, [r0, r1]
	cmp r0, r6
	beq _0223C486
	add r5, r5, #1
	cmp r5, r7
	blt _0223C38C
	b _0223C486
_0223C3A4:
	mov r0, #0x47
	lsl r0, r0, #2
	ldr r5, [r6, r0]
	b _0223C486
_0223C3AC:
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r5, [r6, r0]
	b _0223C486
_0223C3B4:
	bl ov11_0222FF84
	mov r5, #0
	str r0, [sp, #4]
	cmp r0, #0
	ble _0223C3E6
_0223C3C0:
	ldr r7, [r6, #0x64]
	cmp r5, r7
	beq _0223C3DE
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02230270
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, r7, #0
	bl ov11_02230270
	ldr r1, [sp, #8]
	cmp r1, r0
	beq _0223C3E6
_0223C3DE:
	ldr r0, [sp, #4]
	add r5, r5, #1
	cmp r5, r0
	blt _0223C3C0
_0223C3E6:
	ldr r0, [sp, #4]
	cmp r5, r0
	bne _0223C486
	mov r5, #0
	b _0223C486
_0223C3F0:
	bl ov11_0222FF84
	mov r5, #0
	str r0, [sp]
	cmp r0, #0
	ble _0223C422
_0223C3FC:
	ldr r7, [r6, #0x6c]
	cmp r5, r7
	beq _0223C41A
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02230270
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r1, r7, #0
	bl ov11_02230270
	ldr r1, [sp, #0xc]
	cmp r1, r0
	beq _0223C422
_0223C41A:
	ldr r0, [sp]
	add r5, r5, #1
	cmp r5, r0
	blt _0223C3FC
_0223C422:
	ldr r0, [sp]
	cmp r5, r0
	bne _0223C486
	mov r5, #0
	b _0223C486
_0223C42C:
	bl ov11_0222FF84
	add r7, r0, #0
	ldr r1, [r6, #0x64]
	add r0, r4, #0
	bl ov11_02230270
	add r6, r0, #0
	mov r5, #0
	cmp r7, #0
	ble _0223C486
_0223C442:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02230270
	cmp r6, r0
	bne _0223C486
	add r5, r5, #1
	cmp r5, r7
	blt _0223C442
	b _0223C486
_0223C456:
	bl ov11_0222FF84
	add r7, r0, #0
	ldr r1, [r6, #0x6c]
	add r0, r4, #0
	bl ov11_02230270
	add r6, r0, #0
	mov r5, #0
	cmp r7, #0
	ble _0223C486
_0223C46C:
	add r0, r4, #0
	add r1, r5, #0
	bl ov11_02230270
	cmp r6, r0
	bne _0223C486
	add r5, r5, #1
	cmp r5, r7
	blt _0223C46C
	b _0223C486
_0223C480:
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r5, [r6, r0]
_0223C486:
	add r0, r5, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223C48C: .word 0x00000195

	thumb_func_start ov11_0223C490
ov11_0223C490: ; 0x0223C490
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r4, r1, #0
	mov r6, #0
	bl ov11_0223A404
	str r0, [r4]
	add r0, r7, #0
	bl ov11_0223A404
	str r0, [r4, #4]
	cmp r0, #0x3c
	bhi _0223C544
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223C4B6: ; jump table
	.short _0223C530 - _0223C4B6 - 2 ; case 0
	.short _0223C532 - _0223C4B6 - 2 ; case 1
	.short _0223C532 - _0223C4B6 - 2 ; case 2
	.short _0223C532 - _0223C4B6 - 2 ; case 3
	.short _0223C532 - _0223C4B6 - 2 ; case 4
	.short _0223C532 - _0223C4B6 - 2 ; case 5
	.short _0223C532 - _0223C4B6 - 2 ; case 6
	.short _0223C532 - _0223C4B6 - 2 ; case 7
	.short _0223C532 - _0223C4B6 - 2 ; case 8
	.short _0223C536 - _0223C4B6 - 2 ; case 9
	.short _0223C536 - _0223C4B6 - 2 ; case 10
	.short _0223C536 - _0223C4B6 - 2 ; case 11
	.short _0223C536 - _0223C4B6 - 2 ; case 12
	.short _0223C536 - _0223C4B6 - 2 ; case 13
	.short _0223C536 - _0223C4B6 - 2 ; case 14
	.short _0223C536 - _0223C4B6 - 2 ; case 15
	.short _0223C536 - _0223C4B6 - 2 ; case 16
	.short _0223C536 - _0223C4B6 - 2 ; case 17
	.short _0223C536 - _0223C4B6 - 2 ; case 18
	.short _0223C536 - _0223C4B6 - 2 ; case 19
	.short _0223C536 - _0223C4B6 - 2 ; case 20
	.short _0223C536 - _0223C4B6 - 2 ; case 21
	.short _0223C536 - _0223C4B6 - 2 ; case 22
	.short _0223C536 - _0223C4B6 - 2 ; case 23
	.short _0223C536 - _0223C4B6 - 2 ; case 24
	.short _0223C536 - _0223C4B6 - 2 ; case 25
	.short _0223C536 - _0223C4B6 - 2 ; case 26
	.short _0223C536 - _0223C4B6 - 2 ; case 27
	.short _0223C536 - _0223C4B6 - 2 ; case 28
	.short _0223C536 - _0223C4B6 - 2 ; case 29
	.short _0223C536 - _0223C4B6 - 2 ; case 30
	.short _0223C53A - _0223C4B6 - 2 ; case 31
	.short _0223C53A - _0223C4B6 - 2 ; case 32
	.short _0223C53A - _0223C4B6 - 2 ; case 33
	.short _0223C53A - _0223C4B6 - 2 ; case 34
	.short _0223C53A - _0223C4B6 - 2 ; case 35
	.short _0223C53A - _0223C4B6 - 2 ; case 36
	.short _0223C53A - _0223C4B6 - 2 ; case 37
	.short _0223C53A - _0223C4B6 - 2 ; case 38
	.short _0223C53A - _0223C4B6 - 2 ; case 39
	.short _0223C53A - _0223C4B6 - 2 ; case 40
	.short _0223C53A - _0223C4B6 - 2 ; case 41
	.short _0223C53A - _0223C4B6 - 2 ; case 42
	.short _0223C53A - _0223C4B6 - 2 ; case 43
	.short _0223C53A - _0223C4B6 - 2 ; case 44
	.short _0223C53A - _0223C4B6 - 2 ; case 45
	.short _0223C53A - _0223C4B6 - 2 ; case 46
	.short _0223C53A - _0223C4B6 - 2 ; case 47
	.short _0223C53A - _0223C4B6 - 2 ; case 48
	.short _0223C53A - _0223C4B6 - 2 ; case 49
	.short _0223C53A - _0223C4B6 - 2 ; case 50
	.short _0223C53A - _0223C4B6 - 2 ; case 51
	.short _0223C53E - _0223C4B6 - 2 ; case 52
	.short _0223C53E - _0223C4B6 - 2 ; case 53
	.short _0223C53E - _0223C4B6 - 2 ; case 54
	.short _0223C53E - _0223C4B6 - 2 ; case 55
	.short _0223C53E - _0223C4B6 - 2 ; case 56
	.short _0223C53E - _0223C4B6 - 2 ; case 57
	.short _0223C53E - _0223C4B6 - 2 ; case 58
	.short _0223C53E - _0223C4B6 - 2 ; case 59
	.short _0223C542 - _0223C4B6 - 2 ; case 60
_0223C530:
	b _0223C544
_0223C532:
	mov r6, #1
	b _0223C544
_0223C536:
	mov r6, #2
	b _0223C544
_0223C53A:
	mov r6, #3
	b _0223C544
_0223C53E:
	mov r6, #4
	b _0223C544
_0223C542:
	mov r6, #6
_0223C544:
	mov r5, #0
	cmp r6, #0
	ble _0223C55A
_0223C54A:
	add r0, r7, #0
	bl ov11_0223A404
	str r0, [r4, #8]
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, r6
	blt _0223C54A
_0223C55A:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_0223C55C
ov11_0223C55C: ; 0x0223C55C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r2, #0
	ldr r2, [r4]
	add r5, r3, #0
	strh r2, [r5, #2]
	ldr r2, [r4, #4]
	add r7, r0, #0
	strb r2, [r5, #1]
	ldrb r2, [r5, #1]
	add r6, r1, #0
	cmp r2, #0x3c
	bls _0223C576
	b _0223CC58
_0223C576:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0223C582: ; jump table
	.short _0223CC58 - _0223C582 - 2 ; case 0
	.short _0223C5FC - _0223C582 - 2 ; case 1
	.short _0223C606 - _0223C582 - 2 ; case 2
	.short _0223C610 - _0223C582 - 2 ; case 3
	.short _0223C61C - _0223C582 - 2 ; case 4
	.short _0223C628 - _0223C582 - 2 ; case 5
	.short _0223C634 - _0223C582 - 2 ; case 6
	.short _0223C634 - _0223C582 - 2 ; case 7
	.short _0223C640 - _0223C582 - 2 ; case 8
	.short _0223C64A - _0223C582 - 2 ; case 9
	.short _0223C660 - _0223C582 - 2 ; case 10
	.short _0223C674 - _0223C582 - 2 ; case 11
	.short _0223C68A - _0223C582 - 2 ; case 12
	.short _0223C69E - _0223C582 - 2 ; case 13
	.short _0223C6B2 - _0223C582 - 2 ; case 14
	.short _0223C6C8 - _0223C582 - 2 ; case 15
	.short _0223C6DC - _0223C582 - 2 ; case 16
	.short _0223C6F0 - _0223C582 - 2 ; case 17
	.short _0223C704 - _0223C582 - 2 ; case 18
	.short _0223C71A - _0223C582 - 2 ; case 19
	.short _0223C728 - _0223C582 - 2 ; case 20
	.short _0223C740 - _0223C582 - 2 ; case 21
	.short _0223C758 - _0223C582 - 2 ; case 22
	.short _0223C76E - _0223C582 - 2 ; case 23
	.short _0223C784 - _0223C582 - 2 ; case 24
	.short _0223C79A - _0223C582 - 2 ; case 25
	.short _0223C7B0 - _0223C582 - 2 ; case 26
	.short _0223C7C6 - _0223C582 - 2 ; case 27
	.short _0223C7DC - _0223C582 - 2 ; case 28
	.short _0223C7F0 - _0223C582 - 2 ; case 29
	.short _0223C804 - _0223C582 - 2 ; case 30
	.short _0223C81A - _0223C582 - 2 ; case 31
	.short _0223C83A - _0223C582 - 2 ; case 32
	.short _0223C85C - _0223C582 - 2 ; case 33
	.short _0223C87C - _0223C582 - 2 ; case 34
	.short _0223C89A - _0223C582 - 2 ; case 35
	.short _0223C8B8 - _0223C582 - 2 ; case 36
	.short _0223C8DA - _0223C582 - 2 ; case 37
	.short _0223C8FA - _0223C582 - 2 ; case 38
	.short _0223C91A - _0223C582 - 2 ; case 39
	.short _0223C93A - _0223C582 - 2 ; case 40
	.short _0223C95A - _0223C582 - 2 ; case 41
	.short _0223C97A - _0223C582 - 2 ; case 42
	.short _0223C99A - _0223C582 - 2 ; case 43
	.short _0223C9BA - _0223C582 - 2 ; case 44
	.short _0223C9D8 - _0223C582 - 2 ; case 45
	.short _0223C9F6 - _0223C582 - 2 ; case 46
	.short _0223CA14 - _0223C582 - 2 ; case 47
	.short _0223CA26 - _0223C582 - 2 ; case 48
	.short _0223CA48 - _0223C582 - 2 ; case 49
	.short _0223CA6A - _0223C582 - 2 ; case 50
	.short _0223CA8C - _0223C582 - 2 ; case 51
	.short _0223CAAC - _0223C582 - 2 ; case 52
	.short _0223CAD8 - _0223C582 - 2 ; case 53
	.short _0223CB06 - _0223C582 - 2 ; case 54
	.short _0223CB32 - _0223C582 - 2 ; case 55
	.short _0223CB5C - _0223C582 - 2 ; case 56
	.short _0223CB8A - _0223C582 - 2 ; case 57
	.short _0223CBB8 - _0223C582 - 2 ; case 58
	.short _0223CBE6 - _0223C582 - 2 ; case 59
	.short _0223CC14 - _0223C582 - 2 ; case 60
_0223C5FC:
	ldr r2, [r4, #8]
	bl ov11_0223C230
	str r0, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
_0223C606:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
_0223C610:
	ldr r1, [r4, #8]
	add r0, r6, #0
	bl ov11_0223CC8C
	str r0, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
_0223C61C:
	ldr r1, [r4, #8]
	add r0, r6, #0
	bl ov11_0223CD6C
	str r0, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
_0223C628:
	ldr r1, [r4, #8]
	add r0, r6, #0
	bl ov11_0223CCA8
	str r0, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
_0223C634:
	ldr r1, [r4, #8]
	add r0, r6, #0
	bl ov11_0223CD20
	str r0, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
_0223C640:
	ldr r2, [r4, #8]
	bl ov11_0223CDBC
	str r0, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
_0223C64A:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C660:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CC8C
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C674:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CD38
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C68A:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CD6C
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C69E:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CD2C
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C6B2:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CD84
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C6C8:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CCA8
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C6DC:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CD9C
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C6F0:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CD20
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C704:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CDBC
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C71A:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r0, [r4, #0xc]
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C728:
	ldr r1, [r4, #8]
	add r0, r6, #0
	bl ov11_0223CC8C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223C230
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C740:
	ldr r1, [r4, #8]
	add r0, r6, #0
	bl ov11_0223CC8C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C758:
	ldr r1, [r4, #8]
	add r0, r6, #0
	bl ov11_0223CC8C
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CC8C
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C76E:
	ldr r2, [r4, #8]
	bl ov11_0223CD38
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C784:
	ldr r1, [r4, #8]
	add r0, r6, #0
	bl ov11_0223CCA8
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CC8C
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C79A:
	ldr r1, [r4, #8]
	add r0, r6, #0
	bl ov11_0223CD20
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CD20
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C7B0:
	ldr r2, [r4, #8]
	bl ov11_0223CDBC
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CDBC
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C7C6:
	ldr r2, [r4, #8]
	bl ov11_0223CDBC
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C7DC:
	ldr r2, [r4, #8]
	bl ov11_0223CDBC
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CCA8
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C7F0:
	ldr r2, [r4, #8]
	bl ov11_0223CDBC
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CD20
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C804:
	ldr r2, [r4, #8]
	bl ov11_0223CDB4
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CDBC
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_0223C81A:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #8]
	ldr r1, [r4, #0x10]
	add r0, r6, #0
	bl ov11_0223CC8C
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223C83A:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #8]
	ldr r2, [r4, #0x10]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CD38
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223C85C:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #8]
	ldr r1, [r4, #0x10]
	add r0, r6, #0
	bl ov11_0223CCA8
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223C87C:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CC8C
	str r0, [r5, #8]
	ldr r1, [r4, #0x10]
	add r0, r6, #0
	bl ov11_0223CC8C
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223C89A:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CC8C
	str r0, [r5, #8]
	ldr r1, [r4, #0x10]
	add r0, r6, #0
	bl ov11_0223CD20
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223C8B8:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CD38
	str r0, [r5, #8]
	ldr r2, [r4, #0x10]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223C8DA:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CD38
	str r0, [r5, #8]
	ldr r1, [r4, #0x10]
	add r0, r6, #0
	bl ov11_0223CC8C
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223C8FA:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CD38
	str r0, [r5, #8]
	ldr r1, [r4, #0x10]
	add r0, r6, #0
	bl ov11_0223CCA8
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223C91A:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CD38
	str r0, [r5, #8]
	ldr r1, [r4, #0x10]
	add r0, r6, #0
	bl ov11_0223CD6C
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223C93A:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CD38
	str r0, [r5, #8]
	ldr r1, [r4, #0x10]
	add r0, r6, #0
	bl ov11_0223CD2C
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223C95A:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CD38
	str r0, [r5, #8]
	ldr r1, [r4, #0x10]
	add r0, r6, #0
	bl ov11_0223CD78
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223C97A:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CD38
	str r0, [r5, #8]
	ldr r1, [r4, #0x10]
	add r0, r6, #0
	bl ov11_0223CD20
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223C99A:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CCA8
	str r0, [r5, #8]
	ldr r2, [r4, #0x10]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223C9BA:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CCA8
	str r0, [r5, #8]
	ldr r1, [r4, #0x10]
	add r0, r6, #0
	bl ov11_0223CC8C
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223C9D8:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CCA8
	str r0, [r5, #8]
	ldr r1, [r4, #0x10]
	add r0, r6, #0
	bl ov11_0223CD6C
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223C9F6:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CCA8
	str r0, [r5, #8]
	ldr r1, [r4, #0x10]
	add r0, r6, #0
	bl ov11_0223CD78
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223CA14:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r0, [r4, #0xc]
	str r0, [r5, #8]
	ldr r0, [r4, #0x10]
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223CA26:
	ldr r1, [r4, #8]
	add r0, r6, #0
	bl ov11_0223CCA8
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #8]
	ldr r1, [r4, #0x10]
	add r0, r6, #0
	bl ov11_0223CDA8
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223CA48:
	ldr r2, [r4, #8]
	bl ov11_0223CDBC
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #8]
	ldr r2, [r4, #0x10]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223CA6A:
	ldr r2, [r4, #8]
	bl ov11_0223CDB4
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CDBC
	str r0, [r5, #8]
	ldr r2, [r4, #0x10]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223CA8C:
	ldr r2, [r4, #8]
	bl ov11_0223CDB4
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CDBC
	str r0, [r5, #8]
	ldr r1, [r4, #0x10]
	add r0, r6, #0
	bl ov11_0223CCA8
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223CAAC:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CD38
	str r0, [r5, #8]
	ldr r2, [r4, #0x10]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #0xc]
	ldr r1, [r4, #0x14]
	add r0, r6, #0
	bl ov11_0223CC8C
	str r0, [r5, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0223CAD8:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CD38
	str r0, [r5, #8]
	ldr r2, [r4, #0x10]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #0xc]
	ldr r2, [r4, #0x14]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CD38
	str r0, [r5, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0223CB06:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CD38
	str r0, [r5, #8]
	ldr r2, [r4, #0x10]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #0xc]
	ldr r1, [r4, #0x14]
	add r0, r6, #0
	bl ov11_0223CD6C
	str r0, [r5, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0223CB32:
	ldr r2, [r4, #8]
	bl ov11_0223CC5C
	str r0, [r5, #4]
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	bl ov11_0223CCA8
	str r0, [r5, #8]
	ldr r2, [r4, #0x10]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #0xc]
	ldr r1, [r4, #0x14]
	add r0, r6, #0
	bl ov11_0223CCA8
	str r0, [r5, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0223CB5C:
	ldr r2, [r4, #8]
	bl ov11_0223CDBC
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #8]
	ldr r2, [r4, #0x10]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CDBC
	str r0, [r5, #0xc]
	ldr r2, [r4, #0x14]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0223CB8A:
	ldr r2, [r4, #8]
	bl ov11_0223CDB4
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CDBC
	str r0, [r5, #8]
	ldr r2, [r4, #0x10]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #0xc]
	ldr r2, [r4, #0x14]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0223CBB8:
	ldr r2, [r4, #8]
	bl ov11_0223CDB4
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CDBC
	str r0, [r5, #8]
	ldr r2, [r4, #0x10]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #0xc]
	ldr r2, [r4, #0x14]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CDBC
	str r0, [r5, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0223CBE6:
	ldr r2, [r4, #8]
	bl ov11_0223CDB4
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CDBC
	str r0, [r5, #8]
	ldr r2, [r4, #0x10]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CDB4
	str r0, [r5, #0xc]
	ldr r2, [r4, #0x14]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CDBC
	str r0, [r5, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0223CC14:
	ldr r2, [r4, #8]
	bl ov11_0223CDB4
	str r0, [r5, #4]
	ldr r2, [r4, #0xc]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CDBC
	str r0, [r5, #8]
	ldr r2, [r4, #0x10]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #0xc]
	ldr r2, [r4, #0x14]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CDB4
	str r0, [r5, #0x10]
	ldr r2, [r4, #0x18]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CDBC
	str r0, [r5, #0x14]
	ldr r2, [r4, #0x1c]
	add r0, r7, #0
	add r1, r6, #0
	bl ov11_0223CC5C
	str r0, [r5, #0x18]
_0223CC58:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_0223CC5C
ov11_0223CC5C: ; 0x0223CC5C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r2, #0
	bl ov11_0223C230
	cmp r4, #0x16
	bne _0223CC76
	ldr r1, _0223CC84 ; =0x000021A0
	add r2, r5, r0
	ldrb r1, [r2, r1]
	lsl r1, r1, #8
	orr r0, r1
	pop {r3, r4, r5, pc}
_0223CC76:
	ldr r1, _0223CC88 ; =0x0000219C
	add r2, r5, r0
	ldrb r1, [r2, r1]
	lsl r1, r1, #8
	orr r0, r1
	pop {r3, r4, r5, pc}
	nop
_0223CC84: .word 0x000021A0
_0223CC88: .word 0x0000219C

	thumb_func_start ov11_0223CC8C
ov11_0223CC8C: ; 0x0223CC8C
	cmp r1, #1
	beq _0223CC96
	cmp r1, #0xff
	beq _0223CC9C
	bx lr
_0223CC96:
	ldr r1, _0223CCA4 ; =0x00003044
	ldr r0, [r0, r1]
	bx lr
_0223CC9C:
	mov r1, #0x49
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr
	.align 2, 0
_0223CCA4: .word 0x00003044

	thumb_func_start ov11_0223CCA8
ov11_0223CCA8: ; 0x0223CCA8
	push {r4, lr}
	cmp r1, #0x15
	bgt _0223CCC0
	bge _0223CCF6
	cmp r1, #2
	bgt _0223CD18
	cmp r1, #1
	blt _0223CD18
	beq _0223CCC6
	cmp r1, #2
	beq _0223CCDE
	b _0223CD18
_0223CCC0:
	cmp r1, #0xff
	beq _0223CD12
	b _0223CD18
_0223CCC6:
	ldr r3, [r0, #0x64]
	mov r1, #0xc0
	mul r1, r3
	add r2, r0, r1
	ldr r1, _0223CD1C ; =0x00002DB8
	ldrh r4, [r2, r1]
	lsl r1, r3, #0x18
	lsr r1, r1, #0x18
	add r2, r4, #0
	bl ov11_0223D1D0
	b _0223CD18
_0223CCDE:
	ldr r3, [r0, #0x6c]
	mov r1, #0xc0
	mul r1, r3
	add r2, r0, r1
	ldr r1, _0223CD1C ; =0x00002DB8
	ldrh r4, [r2, r1]
	lsl r1, r3, #0x18
	lsr r1, r1, #0x18
	add r2, r4, #0
	bl ov11_0223D1D0
	b _0223CD18
_0223CCF6:
	mov r1, #0x46
	lsl r1, r1, #2
	ldr r3, [r0, r1]
	mov r1, #0xc0
	mul r1, r3
	add r2, r0, r1
	ldr r1, _0223CD1C ; =0x00002DB8
	ldrh r4, [r2, r1]
	lsl r1, r3, #0x18
	lsr r1, r1, #0x18
	add r2, r4, #0
	bl ov11_0223D1D0
	b _0223CD18
_0223CD12:
	mov r1, #0x4a
	lsl r1, r1, #2
	ldr r4, [r0, r1]
_0223CD18:
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0
_0223CD1C: .word 0x00002DB8

	thumb_func_start ov11_0223CD20
ov11_0223CD20: ; 0x0223CD20
	cmp r1, #0xff
	bne _0223CD2A
	mov r1, #0x13
	lsl r1, r1, #4
	ldr r0, [r0, r1]
_0223CD2A:
	bx lr

	thumb_func_start ov11_0223CD2C
ov11_0223CD2C: ; 0x0223CD2C
	cmp r1, #0xff
	bne _0223CD36
	mov r1, #0x13
	lsl r1, r1, #4
	ldr r0, [r0, r1]
_0223CD36:
	bx lr

	thumb_func_start ov11_0223CD38
ov11_0223CD38: ; 0x0223CD38
	push {r3, r4, r5, lr}
	add r5, r1, #0
	cmp r2, #0xff
	bne _0223CD48
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r4, [r5, r0]
	b _0223CD64
_0223CD48:
	bl ov11_0223C230
	add r1, r0, #0
	mov r0, #0xc0
	mul r0, r1
	add r2, r5, r0
	ldr r0, _0223CD68 ; =0x00002D67
	lsl r1, r1, #0x18
	ldrb r4, [r2, r0]
	add r0, r5, #0
	lsr r1, r1, #0x18
	add r2, r4, #0
	bl ov11_0223D1C4
_0223CD64:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223CD68: .word 0x00002D67

	thumb_func_start ov11_0223CD6C
ov11_0223CD6C: ; 0x0223CD6C
	cmp r1, #0xff
	bne _0223CD76
	mov r1, #0x13
	lsl r1, r1, #4
	ldr r0, [r0, r1]
_0223CD76:
	bx lr

	thumb_func_start ov11_0223CD78
ov11_0223CD78: ; 0x0223CD78
	cmp r1, #0xff
	bne _0223CD82
	mov r1, #0x13
	lsl r1, r1, #4
	ldr r0, [r0, r1]
_0223CD82:
	bx lr

	thumb_func_start ov11_0223CD84
ov11_0223CD84: ; 0x0223CD84
	push {r4, lr}
	add r4, r1, #0
	bl ov11_0223C230
	ldr r1, _0223CD98 ; =0x0000219C
	add r2, r4, r0
	ldrb r1, [r2, r1]
	lsl r1, r1, #8
	orr r0, r1
	pop {r4, pc}
	.align 2, 0
_0223CD98: .word 0x0000219C

	thumb_func_start ov11_0223CD9C
ov11_0223CD9C: ; 0x0223CD9C
	cmp r1, #0xff
	bne _0223CDA6
	mov r1, #0x13
	lsl r1, r1, #4
	ldr r0, [r0, r1]
_0223CDA6:
	bx lr

	thumb_func_start ov11_0223CDA8
ov11_0223CDA8: ; 0x0223CDA8
	cmp r1, #0xff
	bne _0223CDB2
	mov r1, #0x13
	lsl r1, r1, #4
	ldr r0, [r0, r1]
_0223CDB2:
	bx lr

	thumb_func_start ov11_0223CDB4
ov11_0223CDB4: ; 0x0223CDB4
	ldr r3, _0223CDB8 ; =ov11_0223C230
	bx r3
	.align 2, 0
_0223CDB8: .word ov11_0223C230

	thumb_func_start ov11_0223CDBC
ov11_0223CDBC: ; 0x0223CDBC
	ldr r3, _0223CDC0 ; =ov11_0223C230
	bx r3
	.align 2, 0
_0223CDC0: .word ov11_0223C230

	thumb_func_start ov11_0223CDC4
ov11_0223CDC4: ; 0x0223CDC4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x78
	add r7, r0, #0
	add r5, r1, #0
	str r2, [sp, #0x18]
	bl ov11_022300C4
	str r0, [sp, #0x28]
	add r0, r7, #0
	bl ov11_0223013C
	str r0, [sp, #0x20]
	add r0, r7, #0
	bl ov11_02230138
	str r0, [sp, #0x24]
	add r0, r7, #0
	bl ov11_0222FF68
	str r0, [sp, #0x1c]
	add r0, r7, #0
	bl ov11_02230078
	add r6, r0, #0
	add r0, r7, #0
	bl ov11_02230080
	add r4, r0, #0
	add r0, r7, #0
	bl ov11_022300CC
	add r7, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0223D03C ; =0x00004E31
	add r1, r4, #0
	str r0, [sp, #8]
	add r0, r6, #0
	mov r2, #0x1b
	mov r3, #0xc0
	bl sub_0200C00C
	mov r0, #0x1b
	str r0, [sp]
	mov r0, #0x2e
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r1, #2
	str r1, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, _0223D040 ; =0x00004E2C
	add r2, r6, #0
	str r0, [sp, #0x14]
	add r0, r7, #0
	add r3, r4, #0
	bl sub_0200C0DC
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223D044 ; =0x00004E29
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r6, #0
	mov r2, #0x1b
	mov r3, #0xc1
	bl sub_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223D044 ; =0x00004E29
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r6, #0
	mov r2, #0x1b
	mov r3, #0xc2
	bl sub_0200C13C
	ldr r2, _0223D048 ; =ov11_0225DD7C
	add r0, r6, #0
	add r1, r4, #0
	bl sub_0200C154
	str r0, [r5, #0xc]
	bl sub_0200C5A8
	ldr r0, [sp, #0x18]
	bl sub_0206B6C8
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _0223D04C ; =0x00004E32
	add r1, r4, #0
	str r0, [sp, #8]
	add r0, r6, #0
	mov r2, #0x13
	bl sub_0200C978
	bl sub_0206B888
	mov r1, #0x13
	str r1, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, _0223D050 ; =0x00004E2D
	mov r1, #2
	str r0, [sp, #0x14]
	add r0, r7, #0
	add r2, r6, #0
	add r3, r4, #0
	bl sub_0200C0DC
	bl sub_0206B894
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _0223D054 ; =0x00004E2A
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r6, #0
	mov r2, #0x13
	bl sub_0200C124
	bl sub_0206B8A0
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _0223D054 ; =0x00004E2A
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r6, #0
	mov r2, #0x13
	bl sub_0200C13C
	ldr r2, _0223D058 ; =ov11_0225DDB0
	add r0, r6, #0
	add r1, r4, #0
	bl sub_0200C154
	str r0, [r5, #0x10]
	ldr r0, [sp, #0x18]
	bl sub_0206B87C
	add r1, r0, #0
	ldr r0, [r5, #0x10]
	ldr r0, [r0]
	bl sub_020202DC
	ldr r0, [r5, #0x10]
	bl sub_0200C5A8
	mov r0, #1
	mov r1, #5
	bl sub_02011744
	str r0, [r5, #0x50]
	ldr r0, [sp, #0x18]
	mov r1, #0xaf
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0223CF26
	mov r0, #2
	b _0223CF30
_0223CF26:
	ldr r0, [sp, #0x18]
	mov r1, #0x6f
	mov r2, #0
	bl GetMonData
_0223CF30:
	cmp r0, #0
	bne _0223CF42
	mov r1, #0x3b
	ldr r0, [sp, #0x28]
	lsl r1, r1, #4
	bl NewString_ReadMsgData
	add r6, r0, #0
	b _0223CF5C
_0223CF42:
	cmp r0, #1
	bne _0223CF52
	ldr r0, [sp, #0x28]
	ldr r1, _0223D05C ; =0x000003B1
	bl NewString_ReadMsgData
	add r6, r0, #0
	b _0223CF5C
_0223CF52:
	ldr r0, [sp, #0x28]
	ldr r1, _0223D060 ; =0x000003B2
	bl NewString_ReadMsgData
	add r6, r0, #0
_0223CF5C:
	ldr r0, [sp, #0x18]
	bl sub_020690E4
	add r2, r0, #0
	ldr r0, [sp, #0x24]
	mov r1, #0
	bl BufferBoxMonNickname
	ldr r0, [sp, #0x18]
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r1, #1
	ldr r0, [sp, #0x24]
	mov r3, #3
	str r1, [sp, #4]
	bl BufferIntegerAsString
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0x20]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_Delete
	add r0, sp, #0x68
	bl InitWindow
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [sp, #0x1c]
	add r1, sp, #0x68
	mov r2, #0xc
	mov r3, #4
	bl AddTextWindowTopLeftCorner
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0223D064 ; =0x00010200
	ldr r2, [sp, #0x20]
	str r0, [sp, #8]
	add r0, sp, #0x68
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, sp, #0x68
	mov r1, #1
	mov r2, #5
	bl sub_02011898
	mov r1, #1
	add r2, r1, #0
	add r3, sp, #0x5c
	bl sub_0201D568
	ldr r0, [r5, #0x50]
	str r0, [sp, #0x2c]
	add r0, sp, #0x68
	str r0, [sp, #0x30]
	add r0, r4, #0
	bl sub_0200CA40
	str r0, [sp, #0x34]
	ldr r1, _0223D040 ; =0x00004E2C
	add r0, r4, #0
	bl sub_0200C334
	mov r1, #0
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x60]
	str r1, [sp, #0x3c]
	str r0, [sp, #0x40]
	mov r0, #0xb0
	str r0, [sp, #0x44]
	mov r0, #8
	str r0, [sp, #0x48]
	mov r0, #0x64
	str r0, [sp, #0x50]
	mov r0, #1
	str r0, [sp, #0x54]
	mov r0, #5
	str r0, [sp, #0x58]
	add r0, sp, #0x2c
	str r1, [sp, #0x4c]
	bl sub_020117E8
	add r2, r5, #0
	add r3, sp, #0x5c
	str r0, [r5, #0x14]
	ldmia r3!, {r0, r1}
	add r2, #0x18
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, #1
	str r0, [r2]
	ldr r0, [r5, #0x14]
	bl sub_02011AC0
	add r0, sp, #0x68
	bl RemoveWindow
	add sp, #0x78
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223D03C: .word 0x00004E31
_0223D040: .word 0x00004E2C
_0223D044: .word 0x00004E29
_0223D048: .word ov11_0225DD7C
_0223D04C: .word 0x00004E32
_0223D050: .word 0x00004E2D
_0223D054: .word 0x00004E2A
_0223D058: .word ov11_0225DDB0
_0223D05C: .word 0x000003B1
_0223D060: .word 0x000003B2
_0223D064: .word 0x00010200

	thumb_func_start ov11_0223D068
ov11_0223D068: ; 0x0223D068
	push {r3, r4, r5, lr}
	add r5, r1, #0
	bl ov11_02230080
	add r4, r0, #0
	ldr r0, [r5, #0xc]
	bl sub_0200C3DC
	ldr r0, [r5, #0x10]
	bl sub_0200C3DC
	ldr r0, [r5, #0x14]
	bl sub_02011870
	add r0, r5, #0
	add r0, #0x18
	bl sub_0201D5E8
	ldr r1, _0223D0D4 ; =0x00004E31
	add r0, r4, #0
	bl sub_0200C358
	ldr r1, _0223D0D8 ; =0x00004E2C
	add r0, r4, #0
	bl sub_0200C368
	ldr r1, _0223D0DC ; =0x00004E29
	add r0, r4, #0
	bl sub_0200C378
	ldr r1, _0223D0DC ; =0x00004E29
	add r0, r4, #0
	bl sub_0200C388
	ldr r1, _0223D0E0 ; =0x00004E32
	add r0, r4, #0
	bl sub_0200C358
	ldr r1, _0223D0E4 ; =0x00004E2D
	add r0, r4, #0
	bl sub_0200C368
	ldr r1, _0223D0E8 ; =0x00004E2A
	add r0, r4, #0
	bl sub_0200C378
	ldr r1, _0223D0E8 ; =0x00004E2A
	add r0, r4, #0
	bl sub_0200C388
	ldr r0, [r5, #0x50]
	bl sub_020117BC
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223D0D4: .word 0x00004E31
_0223D0D8: .word 0x00004E2C
_0223D0DC: .word 0x00004E29
_0223D0E0: .word 0x00004E32
_0223D0E4: .word 0x00004E2D
_0223D0E8: .word 0x00004E2A

	thumb_func_start ov11_0223D0EC
ov11_0223D0EC: ; 0x0223D0EC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r1, r2, #0
	add r5, r0, #0
	str r2, [sp]
	bl ov11_02230270
	cmp r0, #0
	bne _0223D1B8
	add r0, r5, #0
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _0223D13C
	add r0, r5, #0
	mov r1, #3
	bl ov11_0223022C
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	add r0, r5, #0
	mov r1, #5
	bl ov11_0223022C
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r2, #0xc0
	add r0, r1, #0
	mul r0, r2
	mul r2, r6
	ldr r3, _0223D1BC ; =0x00002D74
	add r0, r4, r0
	add r2, r4, r2
	ldrb r0, [r0, r3]
	ldrb r2, [r2, r3]
	cmp r0, r2
	bls _0223D148
	add r6, r1, #0
	b _0223D148
_0223D13C:
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223022C
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
_0223D148:
	ldr r1, [sp]
	add r0, r5, #0
	add r2, r1, #0
	add r3, r4, r2
	ldr r2, _0223D1C0 ; =0x0000219C
	ldrb r2, [r3, r2]
	bl ov11_02230014
	add r7, r0, #0
	ldr r0, [sp]
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	add r0, r4, r2
	ldr r2, _0223D1BC ; =0x00002D74
	mul r1, r6
	add r1, r4, r1
	ldrb r0, [r0, r2]
	ldrb r1, [r1, r2]
	cmp r1, r0
	bls _0223D1A4
	sub r0, r1, r0
	cmp r0, #0x1e
	blt _0223D18E
	add r0, r5, #0
	bl ov11_022302B0
	add r2, r0, #0
	lsl r2, r2, #0x10
	add r0, r7, #0
	mov r1, #8
	lsr r2, r2, #0x10
	bl MonApplyFriendshipMod
	pop {r3, r4, r5, r6, r7, pc}
_0223D18E:
	add r0, r5, #0
	bl ov11_022302B0
	add r2, r0, #0
	lsl r2, r2, #0x10
	add r0, r7, #0
	mov r1, #6
	lsr r2, r2, #0x10
	bl MonApplyFriendshipMod
	pop {r3, r4, r5, r6, r7, pc}
_0223D1A4:
	add r0, r5, #0
	bl ov11_022302B0
	add r2, r0, #0
	lsl r2, r2, #0x10
	add r0, r7, #0
	mov r1, #6
	lsr r2, r2, #0x10
	bl MonApplyFriendshipMod
_0223D1B8:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223D1BC: .word 0x00002D74
_0223D1C0: .word 0x0000219C

	thumb_func_start ov11_0223D1C4
ov11_0223D1C4: ; 0x0223D1C4
	add r1, r0, r1
	mov r0, #0x39
	lsl r0, r0, #4
	strb r2, [r1, r0]
	bx lr
	.align 2, 0

	thumb_func_start ov11_0223D1D0
ov11_0223D1D0: ; 0x0223D1D0
	lsl r1, r1, #1
	add r1, r0, r1
	mov r0, #0xe5
	lsl r0, r0, #2
	strh r2, [r1, r0]
	bx lr

	.section .rodata

	.global ov11_0225DC28
ov11_0225DC28: ; 0x0225DC28
	.byte 0x14, 0x0F, 0x0A, 0x0F

	.global ov11_0225DC2C
ov11_0225DC2C: ; 0x0225DC2C
	.byte 0xC8, 0x50, 0x3C, 0x32, 0x28, 0x00, 0x00, 0x00

	.global ov11_0225DC34
ov11_0225DC34: ; 0x0225DC34
	.byte 0xFF, 0xFF, 0xFF, 0x7F
	.byte 0xFF, 0x3F, 0xFF, 0x1F

	.global ov11_0225DC3C
ov11_0225DC3C: ; 0x0225DC3C
	.byte 0x01

	.global ov11_0225DC3D
ov11_0225DC3D: ; 0x0225DC3D
	.byte 0xC8, 0x05, 0x96
	.byte 0x0C, 0x64, 0x15, 0x50, 0x2A, 0x28, 0x40, 0x14

	.global ov11_0225DC48
ov11_0225DC48: ; 0x0225DC48
	.byte 0x19, 0x00, 0x5C, 0x00, 0xDD, 0x00, 0x17, 0x00, 0x26, 0x00, 0xD6, 0x00, 0x73, 0x01, 0x28, 0x00
	.byte 0x48, 0x01, 0xEA, 0x00, 0x61, 0x01, 0x00, 0x00

	.global ov11_0225DC60
ov11_0225DC60: ; 0x0225DC60
	.byte 0xA3, 0x00, 0x00, 0x00, 0xA4, 0x00, 0x00, 0x00
	.byte 0xA5, 0x00, 0x00, 0x00, 0xA7, 0x00, 0x00, 0x00, 0xA8, 0x00, 0x00, 0x00, 0xA6, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00

	.global ov11_0225DC90
ov11_0225DC90: ; 0x0225DC90
	.byte 0xA3, 0x00, 0x00, 0x00, 0xA4, 0x00, 0x00, 0x00
	.byte 0xA5, 0x00, 0x00, 0x00, 0xA7, 0x00, 0x00, 0x00, 0xA8, 0x00, 0x00, 0x00, 0xA6, 0x00, 0x00, 0x00

	.global ov11_0225DCA8
ov11_0225DCA8: ; 0x0225DCA8
	.byte 0x64, 0x00

	.global ov11_0225DCAA
ov11_0225DCAA: ; 0x0225DCAA
	.byte 0x14, 0x00, 0xFA, 0x00, 0x28, 0x00, 0xF4, 0x01, 0x3C, 0x00, 0xE8, 0x03, 0x50, 0x00
	.byte 0xD0, 0x07, 0x64, 0x00, 0xFF, 0xFF, 0xFF, 0xFF

	.global ov11_0225DCC0
ov11_0225DCC0: ; 0x0225DCC0
	.byte 0xA3, 0x00, 0x00, 0x00, 0xA4, 0x00, 0x00, 0x00
	.byte 0xA5, 0x00, 0x00, 0x00, 0xA7, 0x00, 0x00, 0x00, 0xA8, 0x00, 0x00, 0x00, 0xA6, 0x00, 0x00, 0x00

	.global ov11_0225DCD8
ov11_0225DCD8: ; 0x0225DCD8
	.byte 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00

	.global ov11_0225DCF0
ov11_0225DCF0: ; 0x0225DCF0
	.byte 10, 40
	.byte 10, 35
	.byte 10, 30
	.byte 10, 25
	.byte 10, 20
	.byte 10, 15
	.byte 10, 10
	.byte 15, 10
	.byte 20, 10
	.byte 25, 10
	.byte 30, 10
	.byte 35, 10
	.byte 40, 10

	.global ov11_0225DD0A
ov11_0225DD0A: ; 0x0225DD0A
	.byte 0x59, 0x00, 0x59, 0x00, 0x92, 0x01, 0x92, 0x01, 0x9D, 0x00, 0x9D, 0x00, 0x3B, 0x00
	.byte 0x38, 0x00, 0x3A, 0x00, 0xA1, 0x00, 0xAA, 0x01, 0x93, 0x01, 0xA1, 0x00

	.global ov11_0225DD24
ov11_0225DD24: ; 0x0225DD24
	.byte 0x11, 0x00, 0x12, 0x00
	.byte 0x1A, 0x00, 0x03, 0x00, 0x4F, 0x00, 0x4E, 0x00, 0x1B, 0x00, 0x19, 0x00, 0x02, 0x00, 0x1C, 0x00
	.byte 0x32, 0x00, 0x6C, 0x00, 0x6B, 0x00, 0x6D, 0x00, 0x17, 0x00, 0x1D, 0x00, 0x33, 0x00, 0x29, 0x00

	.global ov11_0225DD48
ov11_0225DD48: ; 0x0225DD48
	.byte 0x1B, 0x00, 0x00, 0x80, 0x1B, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80
	.byte 0x08, 0x00, 0x00, 0x80, 0x08, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x80, 0x16, 0x00, 0x00, 0x80
	.byte 0x04, 0x00, 0x00, 0x80, 0x05, 0x00, 0x00, 0x80, 0x18, 0x00, 0x00, 0x80, 0x1C, 0x00, 0x00, 0x80
	.byte 0x05, 0x00, 0x00, 0x80

	.global ov11_0225DD7C
ov11_0225DD7C: ; 0x0225DD7C
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x31, 0x4E, 0x00, 0x00, 0x2C, 0x4E, 0x00, 0x00
	.byte 0x29, 0x4E, 0x00, 0x00, 0x29, 0x4E, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov11_0225DDB0
ov11_0225DDB0: ; 0x0225DDB0
	.byte 0x98, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x32, 0x4E, 0x00, 0x00
	.byte 0x2D, 0x4E, 0x00, 0x00, 0x2A, 0x4E, 0x00, 0x00, 0x2A, 0x4E, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov11_0225DDE4
ov11_0225DDE4: ; 0x0225DDE4
	.word ov11_02232284
	.word ov11_0223229C, ov11_02232318, ov11_022324D8, ov11_022326B4
	.word ov11_02232774, ov11_022327A0, ov11_022328BC, ov11_022329B8
	.word ov11_02232B68, ov11_02232D00, ov11_02232D2C, ov11_02232DE4
	.word ov11_02232EAC, ov11_02232F64, ov11_022330F4, ov11_0223312C
	.word ov11_02233158, ov11_02233198, ov11_022331CC, ov11_0223320C
	.word ov11_0223322C, ov11_02233258, ov11_022332AC, ov11_02233328
	.word ov11_022333D4, ov11_02233408, ov11_022334A8, ov11_022334D4
	.word ov11_02233538, ov11_02233598, ov11_02233604, ov11_0223363C
	.word ov11_022336EC, ov11_022337A4, ov11_022337C0, ov11_022337E0
	.word ov11_0223380C, ov11_022338A0, CalcExperienceGain, ov11_02233A78
	.word ov11_02233AB8, ov11_02233AD0, ov11_02233AE8, ov11_02233BC0
	.word ov11_02233C94, ov11_02233D34, ov11_02233D7C, ov11_02233DCC
	.word ov11_02233DE4, ov11_02233E54, ov11_02233F48, ov11_02234558
	.word ov11_0223467C, ov11_022346B8, ov11_022346F0, ov11_022347B0
	.word ov11_022347E4, ov11_022348FC, ov11_02234A5C, ov11_02234A7C
	.word ov11_02234A9C, ov11_02234ACC, ov11_02234BE4, ov11_02234C34
	.word ov11_02234C60, ov11_02234C8C, ov11_02234CC4, ov11_02234DF4
	.word ov11_02234E74, ov11_02234ED8, ov11_02234F64, ov11_02234FD4
	.word ov11_0223500C, ov11_02235044, ov11_02235070, ov11_0223509C
	.word ov11_022350CC, ov11_02235244, ov11_02235310, ov11_022353E4
	.word ov11_02235434, ov11_02235514, ov11_022355F4, ov11_02235674
	.word ov11_02235864, ov11_0223589C, ov11_022358F4, ov11_02235A2C
	.word ov11_02235A84, ov11_02235B40, ov11_02235C3C, ov11_02235D38
	.word ov11_02235E1C, ov11_02235FCC, ov11_022360F0, ov11_022361BC
	.word ov11_02236210, ov11_022362B4, ov11_02236404, ov11_022364FC
	.word ov11_0223665C, ov11_022366D8, ov11_02236870, ov11_02236A64
	.word ov11_02236AE8, ov11_02236B6C, ov11_02236C1C, ov11_02236C54
	.word ov11_02236C98, ov11_02236F5C, ov11_02237078, ov11_02237108
	.word ov11_0223718C, ov11_02237220, ov11_02237290, ov11_02237334
	.word ov11_02237398, ov11_022374E0, ov11_02237584, ov11_02237670
	.word ov11_022376D0, ov11_022377B8, ov11_02237838, ov11_0223786C
	.word ov11_02237AC4, ov11_02237B04, ov11_02237B98, ov11_02237CA0
	.word ov11_02237CE4, ov11_02237DC0, ov11_02237E34, ov11_02237EE8
	.word ov11_02237F58, ov11_02237FCC, ov11_0223800C, ov11_02238130
	.word ov11_02238188, ov11_022382A0, ov11_02238350, ov11_022383C4
	.word ov11_02238424, ov11_022384E4, ov11_0223867C, ov11_022386C4
	.word ov11_022387C8, ov11_022388C0, ov11_02238904, ov11_022389F8
	.word ov11_02238A40, ov11_02238A84, ov11_02238ABC, ov11_02238B78
	.word ov11_02238BCC, ov11_02238C24, ov11_02238CA0, ov11_02238E84
	.word ov11_02238EB4, ov11_02238F00, ov11_02238F4C, ov11_02238FD0
	.word ov11_0223907C, ov11_022391A4, ov11_02239204, ov11_0223937C
	.word ov11_022393A4, ov11_022393E4, ov11_02239450, ov11_0223949C
	.word ov11_022394E8, ov11_02239578, ov11_022395A0, ov11_022395CC
	.word ov11_02239614, ov11_02239678, ov11_022396A8, ov11_022396D8
	.word ov11_02239718, ov11_02239748, ov11_02239784, ov11_022397A8
	.word ov11_022398B4, ov11_02239938, ov11_022399C8, ov11_02239A00
	.word ov11_02239A40, ov11_02239A6C, ov11_02239A84, ov11_02239AC4
	.word ov11_02239B08, ov11_02239B34, ov11_02239B60, ov11_02239B8C
	.word ov11_02239BB8, ov11_02239BD0, ov11_02239BE8, ov11_02239C28
	.word ov11_02239C54, ov11_02239C88, ov11_02239D18, ov11_02239DA8
	.word ov11_02239F4C, ov11_02239FC8, ov11_0223A014, ov11_0223A058
	.word ov11_0223A08C, ov11_0223A0A4, ov11_0223A0C0, ov11_0223A0D8
	.word ov11_0223A178, ov11_0223A214, ov11_0223A270, ov11_0223A2C0
	.word ov11_0223A2F0, ov11_0223A324, ov11_0223A350, ov11_0223A37C
	.word ov11_0223A3B4, ov11_0223A3F8

	.global ov11_0225DE150
ov11_0225DE150: ; 0x0225E150
	.byte 0x1E, 0x28, 0x32, 0x3C, 0x46, 0x50, 0x5A, 0x5E
	.byte 0x62, 0x00, 0x00, 0x00

	.global ov11_0225E15C
ov11_0225E15C: ; 0x0225E15C
	.byte 0x05, 0x0A, 0x0F, 0x14, 0x19, 0x1E, 0x23, 0x28, 0x2D, 0x32, 0x00, 0x00

	.global ov11_0225E168
ov11_0225E168: ; 0x0225E168
	.byte 0x04, 0x04, 0x0C, 0x0C, 0x05, 0x05, 0x0F, 0x0B, 0x0F, 0x00, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00

	.section .data

	.global ov11_0225FF20
ov11_0225FF20: ; 0x0225FF20
	.byte 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0x04, 0x08, 0x04, 0x08, 0x08, 0x08, 0x06, 0x0C
	.byte 0x0C, 0x0C, 0x04, 0x08, 0x10, 0x10, 0x02, 0x10, 0x0F, 0x0F, 0x08, 0x14, 0x02, 0x08, 0x08, 0x1E
	.byte 0x28, 0x28, 0x32, 0x32, 0x0E, 0x10, 0x0A, 0x0F, 0x0F, 0x0C, 0x04, 0x04, 0x01, 0x01, 0x08, 0x05
	.byte 0x0C, 0x08, 0x08, 0x1E, 0x06, 0x0F, 0x0F, 0x08, 0x08, 0x06, 0x06, 0x0A, 0x05, 0x05, 0x1E, 0x19
	.byte 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x32, 0x0E, 0x0A, 0x14, 0x0A, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E
	.byte 0x08, 0x08, 0x12, 0x08, 0x0A, 0x12, 0x2D, 0x14, 0x14, 0x0A, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x19
	.byte 0x19, 0x00, 0x00, 0x00
