	.include "asm/macros.inc"
    .include "global.inc"

	.extern gMain

	.section .bss


	.section .data



	.text

	thumb_func_start FUN_02030674
FUN_02030674: ; 0x02030674
	push {r3-r7, lr}
	ldr r7, _02030798 ; =UNK_021C59F4
	mov r6, #0x0
	ldr r5, [r7, #0x4]
	ldr r2, _0203079C ; =0x0000062C
	add r4, r6, #0x0
	ldrb r0, [r5, r2]
	cmp r0, #0x0
	beq _02030690
	sub r1, r2, #0x4
	ldrh r1, [r5, r1]
	mov r3, #0xf0
	tst r3, r1
	bne _02030692
_02030690:
	b _02030794
_02030692:
	cmp r0, #0x2
	bne _020306D0
	mov r0, #0x20
	tst r0, r1
	beq _020306A4
	mov r0, #0x10
	orr r0, r6
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_020306A4:
	mov r0, #0x10
	tst r0, r1
	beq _020306B2
	mov r0, #0x20
	orr r0, r4
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_020306B2:
	mov r0, #0x40
	tst r0, r1
	beq _020306C0
	mov r0, #0x80
	orr r0, r4
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_020306C0:
	mov r0, #0x80
	tst r0, r1
	beq _0203077E
	mov r0, #0x40
	orr r0, r4
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	b _0203077E
_020306D0:
	add r0, r2, #0x2
	ldrh r0, [r5, r0]
	cmp r0, #0x0
	beq _020306F2
	add r4, r0, #0x0
	add r0, r2, #0x1
	ldrsb r0, [r5, r0]
	sub r1, r0, #0x1
	add r0, r2, #0x1
	strb r1, [r5, r0]
	ldr r1, [r7, #0x4]
	ldrsb r0, [r1, r0]
	cmp r0, #0x0
	bge _0203077E
	add r0, r2, #0x2
	strh r6, [r1, r0]
	b _0203077E
_020306F2:
	add r0, r2, #0x0
	sub r0, #0x34
	add r6, r5, r0
	sub r2, #0x34
	ldr r0, [r6, #0x8]
	ldr r1, [r6, #0xc]
	ldr r2, [r5, r2]
	ldr r3, [r6, #0x4]
	bl _ll_mul
	add r3, r0, #0x0
	add r2, r1, #0x0
	ldr r0, [r6, #0x10]
	ldr r1, [r6, #0x14]
	add r0, r0, r3
	adc r1, r2
	ldr r2, _020307A0 ; =0x000005F8
	str r0, [r5, r2]
	mov r2, #0x0
	str r1, [r6, #0x4]
	lsr r0, r1, #0x1e
	lsl r1, r2, #0x2
	orr r1, r0
	cmp r1, #0x3
	bhi _02030746
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02030730: ; jump table (using 16-bit offset)
	.short _02030738 - _02030730 - 2; case 0
	.short _0203073C - _02030730 - 2; case 1
	.short _02030740 - _02030730 - 2; case 2
	.short _02030744 - _02030730 - 2; case 3
_02030738:
	mov r4, #0x20
	b _02030746
_0203073C:
	mov r4, #0x10
	b _02030746
_02030740:
	mov r4, #0x40
	b _02030746
_02030744:
	mov r4, #0x80
_02030746:
	ldr r0, _02030798 ; =UNK_021C59F4
	ldr r5, [r0, #0x4]
	ldr r0, _020307A0 ; =0x000005F8
	add r6, r5, r0
	ldr r0, [r6, #0x8]
	ldr r1, [r6, #0xc]
	ldr r2, [r6, #0x0]
	ldr r3, [r6, #0x4]
	bl _ll_mul
	ldr r3, [r6, #0x10]
	ldr r2, [r6, #0x14]
	add r0, r3, r0
	adc r2, r1
	ldr r1, _020307A0 ; =0x000005F8
	mov r3, #0x0
	str r0, [r5, r1]
	str r2, [r6, #0x4]
	lsr r0, r2, #0x1c
	lsl r2, r3, #0x4
	orr r2, r0
	add r0, r1, #0x0
	add r0, #0x35
	strb r2, [r5, r0]
	ldr r0, _02030798 ; =UNK_021C59F4
	add r1, #0x36
	ldr r0, [r0, #0x4]
	strh r4, [r0, r1]
_0203077E:
	ldr r2, _02030798 ; =UNK_021C59F4
	ldr r1, _020307A4 ; =0x00000628
	ldr r5, [r2, #0x4]
	mov r0, #0xf0
	ldrh r3, [r5, r1]
	bic r3, r0
	strh r3, [r5, r1]
	ldr r2, [r2, #0x4]
	ldrh r0, [r2, r1]
	add r0, r0, r4
	strh r0, [r2, r1]
_02030794:
	pop {r3-r7, pc}
	nop
_02030798: .word UNK_021C59F4
_0203079C: .word 0x0000062C
_020307A0: .word 0x000005F8
_020307A4: .word 0x00000628

	thumb_func_start FUN_020307A8
FUN_020307A8: ; 0x020307A8
	ldr r0, _020307B4 ; =UNK_021C59F4
	mov r2, #0x1
	ldr r1, [r0, #0x4]
	ldr r0, _020307B8 ; =0x0000062C
	strb r2, [r1, r0]
	bx lr
	.balign 4
_020307B4: .word UNK_021C59F4
_020307B8: .word 0x0000062C

	thumb_func_start FUN_020307BC
FUN_020307BC: ; 0x020307BC
	ldr r0, _020307C8 ; =UNK_021C59F4
	mov r2, #0x2
	ldr r1, [r0, #0x4]
	ldr r0, _020307CC ; =0x0000062C
	strb r2, [r1, r0]
	bx lr
	.balign 4
_020307C8: .word UNK_021C59F4
_020307CC: .word 0x0000062C

	thumb_func_start FUN_020307D0
FUN_020307D0: ; 0x020307D0
	ldr r0, _020307DC ; =UNK_021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _020307E0 ; =0x0000062C
	strb r2, [r1, r0]
	bx lr
	.balign 4
_020307DC: .word UNK_021C59F4
_020307E0: .word 0x0000062C

	thumb_func_start FUN_020307E4
FUN_020307E4: ; 0x020307E4
	push {r4-r7}
	ldr r4, _02030868 ; =UNK_021C59F4
	lsl r6, r1, #0x1
	ldr r2, [r4, #0x4]
	mov r5, #0x0
	add r3, r2, r6
	mov r2, #0x61
	lsl r2, r2, #0x4
	strh r5, [r3, r2]
	ldrb r5, [r0, #0x0]
	mov r3, #0x10
	add r7, r5, #0x0
	and r7, r3
	cmp r7, #0x10
	bne _02030860
	mov r7, #0xc
	and r5, r7
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	bne _0203081A
	ldr r3, [r4, #0x4]
	add r4, r3, r2
	ldrh r3, [r4, r6]
	mov r2, #0x40
	orr r2, r3
	strh r2, [r4, r6]
	b _0203084C
_0203081A:
	cmp r5, #0x4
	bne _0203082C
	ldr r3, [r4, #0x4]
	add r4, r3, r2
	ldrh r3, [r4, r6]
	mov r2, #0x80
	orr r2, r3
	strh r2, [r4, r6]
	b _0203084C
_0203082C:
	cmp r5, #0x8
	bne _0203083E
	ldr r3, [r4, #0x4]
	add r4, r3, r2
	ldrh r3, [r4, r6]
	mov r2, #0x20
	orr r2, r3
	strh r2, [r4, r6]
	b _0203084C
_0203083E:
	cmp r5, #0xc
	bne _0203084C
	ldr r4, [r4, #0x4]
	add r4, r4, r2
	ldrh r2, [r4, r6]
	orr r2, r3
	strh r2, [r4, r6]
_0203084C:
	ldrb r0, [r0, #0x0]
	asr r2, r0, #0x5
	mov r0, #0x7
	and r2, r0
	ldr r0, _02030868 ; =UNK_021C59F4
	ldr r0, [r0, #0x4]
	add r1, r0, r1
	mov r0, #0x62
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
_02030860:
	mov r0, #0x1
	pop {r4-r7}
	bx lr
	nop
_02030868: .word UNK_021C59F4

	thumb_func_start FUN_0203086C
FUN_0203086C: ; 0x0203086C
	bx lr
	.balign 4

	thumb_func_start FUN_02030870
FUN_02030870: ; 0x02030870
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0203091C ; =UNK_021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _02030920 ; =0x0000062A
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _02030884
	mov r0, #0x0
	pop {r4, pc}
_02030884:
	bl FUN_02030FE0
	cmp r0, #0x0
	bne _02030890
	mov r0, #0x0
	pop {r4, pc}
_02030890:
	ldr r0, _0203091C ; =UNK_021C59F4
	ldr r2, [r0, #0x4]
	ldr r0, _02030924 ; =0x00000681
	ldrb r1, [r2, r0]
	cmp r1, #0x0
	beq _020308A0
	sub r1, r1, #0x1
	strb r1, [r2, r0]
_020308A0:
	ldr r1, _0203091C ; =UNK_021C59F4
	ldr r0, _02030928 ; =0x00000628
	ldr r2, [r1, #0x4]
	mov r3, #0x40
	ldrh r2, [r2, r0]
	tst r3, r2
	beq _020308C0
	ldrb r3, [r4, #0x0]
	mov r2, #0x10
	add r0, #0x59
	orr r2, r3
	strb r2, [r4, #0x0]
	ldr r1, [r1, #0x4]
	mov r2, #0x8
	strb r2, [r1, r0]
	b _02030906
_020308C0:
	mov r3, #0x80
	tst r3, r2
	beq _020308D8
	ldrb r3, [r4, #0x0]
	mov r2, #0x14
	add r0, #0x59
	orr r2, r3
	strb r2, [r4, #0x0]
	ldr r1, [r1, #0x4]
	mov r2, #0x8
	strb r2, [r1, r0]
	b _02030906
_020308D8:
	mov r3, #0x20
	tst r3, r2
	beq _020308F0
	ldrb r3, [r4, #0x0]
	mov r2, #0x18
	add r0, #0x59
	orr r2, r3
	strb r2, [r4, #0x0]
	ldr r1, [r1, #0x4]
	mov r2, #0x8
	strb r2, [r1, r0]
	b _02030906
_020308F0:
	mov r3, #0x10
	tst r2, r3
	beq _02030906
	ldrb r3, [r4, #0x0]
	mov r2, #0x1c
	add r0, #0x59
	orr r2, r3
	strb r2, [r4, #0x0]
	ldr r1, [r1, #0x4]
	mov r2, #0x8
	strb r2, [r1, r0]
_02030906:
	ldr r0, _0203091C ; =UNK_021C59F4
	ldrb r2, [r4, #0x0]
	ldr r1, [r0, #0x4]
	ldr r0, _0203092C ; =0x0000062B
	ldrb r0, [r1, r0]
	lsl r0, r0, #0x5
	orr r0, r2
	strb r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4, pc}
	nop
_0203091C: .word UNK_021C59F4
_02030920: .word 0x0000062A
_02030924: .word 0x00000681
_02030928: .word 0x00000628
_0203092C: .word 0x0000062B

	thumb_func_start FUN_02030930
FUN_02030930: ; 0x02030930
	push {r3-r5, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02031228
	add r5, r0, #0x0
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D858
	ldr r0, _020309F0 ; =UNK_021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _020309F4 ; =0x00000684
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _02030960
	mov r0, #0x0
	b _02030962
_02030960:
	mov r0, #0x1
_02030962:
	strb r0, [r4, #0x0]
	bl FUN_0202FA28
	cmp r0, #0x0
	bne _02030972
	add r0, r4, #0x0
	bl FUN_02030870
_02030972:
	ldr r1, _020309F0 ; =UNK_021C59F4
	ldr r0, _020309F4 ; =0x00000684
	ldr r2, [r1, #0x4]
	mov r3, #0x0
	strb r3, [r2, r0]
	ldr r1, [r1, #0x4]
	ldr r0, _020309F8 ; =0x0000054C
	add r0, r1, r0
	bl FUN_0202D4E4
	cmp r0, #0x0
	beq _0203099E
	ldrb r1, [r4, #0x0]
	mov r0, #0x2
	orr r0, r1
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x0]
	cmp r0, #0x2
	bne _020309E8
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r5, pc}
_0203099E:
	sub r0, r5, #0x1
	str r0, [sp, #0x4]
	add r0, r4, #0x1
	str r0, [sp, #0x0]
	ldr r0, _020309F0 ; =UNK_021C59F4
	mov r2, #0x1
	ldr r1, [r0, #0x4]
	ldr r0, _020309F8 ; =0x0000054C
	add r0, r1, r0
	add r1, sp, #0x0
	bl FUN_0202D760
	cmp r0, #0x0
	bne _020309C4
	ldr r0, _020309F0 ; =UNK_021C59F4
	mov r2, #0x1
	ldr r1, [r0, #0x4]
	ldr r0, _020309F4 ; =0x00000684
	strb r2, [r1, r0]
_020309C4:
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _020309E8
	ldr r2, _020309F0 ; =UNK_021C59F4
	ldr r1, _020309FC ; =0x0000065E
	ldr r3, [r2, #0x4]
	ldrb r0, [r3, r1]
	add r0, r0, #0x1
	strb r0, [r3, r1]
	ldr r2, [r2, #0x4]
	ldrb r0, [r4, #0x0]
	ldrb r1, [r2, r1]
	lsl r2, r1, #0x4
	mov r1, #0xf0
	and r1, r2
	orr r0, r1
	strb r0, [r4, #0x0]
_020309E8:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r5, pc}
	nop
_020309F0: .word UNK_021C59F4
_020309F4: .word 0x00000684
_020309F8: .word 0x0000054C
_020309FC: .word 0x0000065E

	thumb_func_start FUN_02030A00
FUN_02030A00: ; 0x02030A00
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	mov r0, #0xb
	strb r0, [r4, #0x0]
	ldr r0, _02030A6C ; =UNK_021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _02030A70 ; =0x00000685
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _02030A1A
	mov r0, #0x0
	b _02030A1C
_02030A1A:
	mov r0, #0x1
_02030A1C:
	strb r0, [r4, #0x1]
	bl FUN_0202CB8C
	asr r1, r0, #0x8
	strb r1, [r4, #0x2]
	strb r0, [r4, #0x3]
	mov r0, #0xbb
	str r0, [sp, #0x4]
	add r0, r4, #0x5
	str r0, [sp, #0x0]
	ldr r0, _02030A6C ; =UNK_021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02030A74 ; =0x0000056C
	add r0, r1, r0
	add r1, sp, #0x0
	bl FUN_0202D760
	cmp r0, #0x0
	beq _02030A5A
	ldr r0, _02030A6C ; =UNK_021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02030A70 ; =0x00000685
	strb r2, [r1, r0]
	ldr r1, [sp, #0x4]
	mov r0, #0xbb
	sub r0, r0, r1
	add sp, #0x8
	strb r0, [r4, #0x4]
	pop {r4, pc}
_02030A5A:
	ldr r0, _02030A6C ; =UNK_021C59F4
	mov r2, #0x1
	ldr r1, [r0, #0x4]
	ldr r0, _02030A70 ; =0x00000685
	strb r2, [r1, r0]
	mov r0, #0xbb
	strb r0, [r4, #0x4]
	add sp, #0x8
	pop {r4, pc}
	.balign 4
_02030A6C: .word UNK_021C59F4
_02030A70: .word 0x00000685
_02030A74: .word 0x0000056C

	thumb_func_start FUN_02030A78
FUN_02030A78: ; 0x02030A78
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _02030A9C
	bl FUN_02031280
	cmp r0, #0x0
	bne _02030A9C
	add sp, #0x8
	mov r0, #0x0
	pop {r4-r6, pc}
_02030A9C:
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldr r0, _02030AD4 ; =UNK_021C59F4
	add r2, r4, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02030AD8 ; =0x0000054C
	add r3, r6, #0x0
	add r0, r1, r0
	add r1, r5, #0x0
	bl FUN_0202D684
	cmp r0, #0x0
	beq _02030AC0
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_02030AC0:
	bl FUN_02033534
	cmp r0, #0xa
	bne _02030ACC
	bl FUN_02031454
_02030ACC:
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_02030AD4: .word UNK_021C59F4
_02030AD8: .word 0x0000054C

	thumb_func_start FUN_02030ADC
FUN_02030ADC: ; 0x02030ADC
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _02030B00
	bl FUN_02031280
	cmp r0, #0x0
	bne _02030B00
	add sp, #0x8
	mov r0, #0x0
	pop {r4-r6, pc}
_02030B00:
	mov r0, #0x1
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, _02030B34 ; =UNK_021C59F4
	add r2, r4, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02030B38 ; =0x0000054C
	add r3, r6, #0x0
	add r0, r1, r0
	add r1, r5, #0x0
	bl FUN_0202D684
	cmp r0, #0x0
	beq _02030B22
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_02030B22:
	bl FUN_02033534
	cmp r0, #0xa
	bne _02030B2E
	bl FUN_02031454
_02030B2E:
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_02030B34: .word UNK_021C59F4
_02030B38: .word 0x0000054C

	thumb_func_start FUN_02030B3C
FUN_02030B3C: ; 0x02030B3C
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	beq _02030B58
	bl ErrorHandling
	add sp, #0x8
	mov r0, #0x0
	pop {r4-r6, pc}
_02030B58:
	mov r0, #0x0
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _02030B70
	bl FUN_02031280
	cmp r0, #0x0
	bne _02030B70
	add sp, #0x8
	mov r0, #0x0
	pop {r4-r6, pc}
_02030B70:
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _02030B86
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02030A78
	add sp, #0x8
	pop {r4-r6, pc}
_02030B86:
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldr r0, _02030BBC ; =UNK_021C59F4
	add r2, r4, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02030BC0 ; =0x0000056C
	add r3, r6, #0x0
	add r0, r1, r0
	add r1, r5, #0x0
	bl FUN_0202D684
	cmp r0, #0x0
	beq _02030BAA
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_02030BAA:
	bl FUN_02033534
	cmp r0, #0xa
	bne _02030BB6
	bl FUN_02031454
_02030BB6:
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_02030BBC: .word UNK_021C59F4
_02030BC0: .word 0x0000056C

	thumb_func_start FUN_02030BC4
FUN_02030BC4: ; 0x02030BC4
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	beq _02030BE0
	bl FUN_02031454
	add sp, #0x8
	mov r0, #0x0
	pop {r4-r6, pc}
_02030BE0:
	mov r0, #0x0
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _02030BF8
	bl FUN_02031280
	cmp r0, #0x0
	bne _02030BF8
	add sp, #0x8
	mov r0, #0x0
	pop {r4-r6, pc}
_02030BF8:
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _02030C0E
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02030ADC
	add sp, #0x8
	pop {r4-r6, pc}
_02030C0E:
	mov r0, #0x1
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, _02030C44 ; =UNK_021C59F4
	add r2, r4, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02030C48 ; =0x0000056C
	add r3, r6, #0x0
	add r0, r1, r0
	add r1, r5, #0x0
	bl FUN_0202D684
	cmp r0, #0x0
	beq _02030C30
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_02030C30:
	bl FUN_02033534
	cmp r0, #0xa
	bne _02030C3C
	bl FUN_02031454
_02030C3C:
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_02030C44: .word UNK_021C59F4
_02030C48: .word 0x0000056C

	thumb_func_start FUN_02030C4C
FUN_02030C4C: ; 0x02030C4C
	ldr r3, _02030C54 ; =FUN_02030BC4
	mov r2, #0x0
	bx r3
	nop
_02030C54: .word FUN_02030BC4

	thumb_func_start FUN_02030C58
FUN_02030C58: ; 0x02030C58
	ldr r0, _02030C64 ; =UNK_021C59F4
	ldr r3, _02030C68 ; =FUN_0202D498
	ldr r1, [r0, #0x4]
	ldr r0, _02030C6C ; =0x00000464
	add r0, r1, r0
	bx r3
	.balign 4
_02030C64: .word UNK_021C59F4
_02030C68: .word FUN_0202D498
_02030C6C: .word 0x00000464

	thumb_func_start FUN_02030C70
FUN_02030C70: ; 0x02030C70
	push {r4, lr}
	ldr r4, [sp, #0x8]
	bl FUN_0202D934
	mov r0, #0xee
	strb r0, [r4, #0xa]
	ldr r0, _02030C88 ; =0x0000FFFF
	strh r0, [r4, #0x8]
	mov r0, #0x0
	str r0, [r4, #0x4]
	str r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4
_02030C88: .word 0x0000FFFF

	thumb_func_start FUN_02030C8C
FUN_02030C8C: ; 0x02030C8C
	push {r4-r7, lr}
	sub sp, #0x14
	add r6, r0, #0x0
	str r1, [sp, #0x4]
	str r2, [sp, #0x8]
	ldr r5, [sp, #0x28]
	bl FUN_0202D478
	cmp r0, #0x0
	beq _02030D94
_02030CA0:
	ldrb r7, [r5, #0xa]
	cmp r7, #0xee
	bne _02030CB2
	add r0, r6, #0x0
	bl FUN_0202D41C
	add r7, r0, #0x0
	cmp r7, #0xee
	beq _02030D8A
_02030CB2:
	mov r0, #0x4
	ldrsh r0, [r6, r0]
	strb r7, [r5, #0xa]
	ldrh r4, [r5, #0x8]
	str r0, [sp, #0x10]
	ldr r0, _02030D98 ; =0x0000FFFF
	cmp r4, r0
	bne _02030D06
	add r0, r7, #0x0
	bl FUN_0202D9A0
	add r4, r0, #0x0
	ldr r0, _02030D9C ; =UNK_021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _02030DA0 ; =0x00000689
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _02030D94
	ldr r0, _02030D98 ; =0x0000FFFF
	cmp r4, r0
	bne _02030D04
	add r0, r6, #0x0
	bl FUN_0202D478
	cmp r0, #0x1
	bge _02030CEE
	ldr r0, [sp, #0x10]
	add sp, #0x14
	strh r0, [r6, #0x4]
	pop {r4-r7, pc}
_02030CEE:
	add r0, r6, #0x0
	bl FUN_0202D41C
	lsl r4, r0, #0x8
	add r0, r6, #0x0
	bl FUN_0202D41C
	add r4, r4, r0
	mov r0, #0x4
	ldrsh r0, [r6, r0]
	str r0, [sp, #0x10]
_02030D04:
	strh r4, [r5, #0x8]
_02030D06:
	add r0, r7, #0x0
	bl FUN_0202DA04
	cmp r0, #0x0
	beq _02030D5E
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	bne _02030D22
	ldrh r2, [r5, #0x8]
	ldr r1, [sp, #0x4]
	add r0, r7, #0x0
	bl FUN_0202DA40
	str r0, [r5, #0x4]
_02030D22:
	ldr r2, [r5, #0x0]
	ldr r1, [sp, #0x8]
	add r0, r6, #0x0
	sub r2, r4, r2
	bl FUN_0202D400
	ldr r2, [r5, #0x4]
	str r0, [sp, #0xc]
	cmp r2, #0x0
	beq _02030D42
	ldr r1, [r5, #0x0]
	ldr r0, [sp, #0x8]
	add r1, r2, r1
	ldr r2, [sp, #0xc]
	bl MI_CpuCopy8
_02030D42:
	ldr r1, [r5, #0x0]
	ldr r0, [sp, #0xc]
	add r0, r1, r0
	str r0, [r5, #0x0]
	cmp r0, r4
	blt _02030D8A
	str r5, [sp, #0x0]
	ldr r0, [sp, #0x4]
	ldr r3, [r5, #0x4]
	add r1, r7, #0x0
	add r2, r4, #0x0
	bl FUN_02030C70
	b _02030D8A
_02030D5E:
	add r0, r6, #0x0
	bl FUN_0202D478
	cmp r0, r4
	blt _02030D82
	ldr r1, [sp, #0x8]
	add r0, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0202D400
	ldr r0, [sp, #0x4]
	ldr r3, [sp, #0x8]
	add r1, r7, #0x0
	add r2, r4, #0x0
	str r5, [sp, #0x0]
	bl FUN_02030C70
	b _02030D8A
_02030D82:
	ldr r0, [sp, #0x10]
	add sp, #0x14
	strh r0, [r6, #0x4]
	pop {r4-r7, pc}
_02030D8A:
	add r0, r6, #0x0
	bl FUN_0202D478
	cmp r0, #0x0
	bne _02030CA0
_02030D94:
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02030D98: .word 0x0000FFFF
_02030D9C: .word UNK_021C59F4
_02030DA0: .word 0x00000689

	thumb_func_start FUN_02030DA4
FUN_02030DA4: ; 0x02030DA4
	push {r3, lr}
	ldr r0, _02030DF0 ; =UNK_021C59F4
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _02030DEE
	ldr r0, _02030DF4 ; =0x0000068B
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _02030DEE
	mov r0, #0x47
	lsl r0, r0, #0x4
	add r0, r1, r0
	bl FUN_0202D4BC
	ldr r0, _02030DF0 ; =UNK_021C59F4
	ldr r1, [r0, #0x4]
	mov r0, #0x47
	lsl r0, r0, #0x4
	add r0, r1, r0
	bl FUN_0202D478
	cmp r0, #0x0
	ble _02030DEE
	ldr r0, _02030DF0 ; =UNK_021C59F4
	mov r2, #0x47
	ldr r3, [r0, #0x4]
	ldr r0, _02030DF8 ; =0x000005EC
	lsl r2, r2, #0x4
	add r0, r3, r0
	str r0, [sp, #0x0]
	add r0, r3, r2
	sub r2, #0x10
	ldr r2, [r3, r2]
	mov r1, #0x0
	mov r3, #0x1
	bl FUN_02030C8C
_02030DEE:
	pop {r3, pc}
	.balign 4
_02030DF0: .word UNK_021C59F4
_02030DF4: .word 0x0000068B
_02030DF8: .word 0x000005EC

	thumb_func_start FUN_02030DFC
FUN_02030DFC: ; 0x02030DFC
	push {r3-r7, lr}
	ldr r0, _02030E6C ; =UNK_021C59F4
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _02030E68
	ldr r0, _02030E70 ; =0x0000068B
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _02030E68
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D858
	add r7, r0, #0x1
	mov r4, #0x0
	cmp r7, #0x0
	ble _02030E68
	ldr r6, _02030E6C ; =UNK_021C59F4
	add r5, r4, #0x0
_02030E26:
	ldr r1, [r6, #0x4]
	ldr r0, _02030E74 ; =0x000004E8
	add r0, r1, r0
	add r0, r0, r5
	bl FUN_0202D4BC
	ldr r1, [r6, #0x4]
	ldr r0, _02030E74 ; =0x000004E8
	add r0, r1, r0
	add r0, r0, r5
	bl FUN_0202D478
	cmp r0, #0x0
	ble _02030E60
	ldr r3, [r6, #0x4]
	ldr r0, _02030E78 ; =0x0000058C
	mov r2, #0x46
	add r0, r3, r0
	add r0, r0, r5
	str r0, [sp, #0x0]
	ldr r0, _02030E74 ; =0x000004E8
	lsl r2, r2, #0x4
	add r0, r3, r0
	ldr r2, [r3, r2]
	add r0, r0, r5
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_02030C8C
_02030E60:
	add r4, r4, #0x1
	add r5, #0xc
	cmp r4, r7
	blt _02030E26
_02030E68:
	pop {r3-r7, pc}
	nop
_02030E6C: .word UNK_021C59F4
_02030E70: .word 0x0000068B
_02030E74: .word 0x000004E8
_02030E78: .word 0x0000058C

	thumb_func_start FUN_02030E7C
FUN_02030E7C: ; 0x02030E7C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02030F14 ; =UNK_021C59F4
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	bne _02030E8C
	mov r0, #0x0
	pop {r4, pc}
_02030E8C:
	bl FUN_02033534
	cmp r0, #0x13
	blt _02030EC0
	ldr r0, _02030F14 ; =UNK_021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _02030F18 ; =0x00000687
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _02030EBC
	bl MOD04_021D8018
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _02030EBC
	cmp r4, #0x0
	bne _02030EB4
	mov r0, #0x1
	pop {r4, pc}
_02030EB4:
	cmp r4, #0x1
	bne _02030EBC
	mov r0, #0x1
	pop {r4, pc}
_02030EBC:
	mov r0, #0x0
	pop {r4, pc}
_02030EC0:
	bl FUN_02030F40
	cmp r0, #0x0
	bne _02030ECC
	mov r0, #0x0
	pop {r4, pc}
_02030ECC:
	bl FUN_0202CBD4
	cmp r0, #0x4
	beq _02030ED8
	mov r0, #0x0
	pop {r4, pc}
_02030ED8:
	bl FUN_02031190
	cmp r4, r0
	bne _02030EE4
	mov r0, #0x1
	pop {r4, pc}
_02030EE4:
	bl FUN_02031190
	cmp r0, #0x0
	bne _02030EFE
	bl FUN_0202CB8C
	mov r1, #0x1
	add r2, r1, #0x0
	lsl r2, r4
	tst r0, r2
	beq _02030F10
	add r0, r1, #0x0
	pop {r4, pc}
_02030EFE:
	ldr r0, _02030F14 ; =UNK_021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _02030F1C ; =0x0000065C
	ldrh r2, [r1, r0]
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r1, r4
	tst r1, r2
	bne _02030F12
_02030F10:
	mov r0, #0x0
_02030F12:
	pop {r4, pc}
	.balign 4
_02030F14: .word UNK_021C59F4
_02030F18: .word 0x00000687
_02030F1C: .word 0x0000065C

	thumb_func_start FUN_02030F20
FUN_02030F20: ; 0x02030F20
	push {r3-r5, lr}
	mov r4, #0x0
	add r5, r4, #0x0
_02030F26:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _02030F34
	add r4, r4, #0x1
_02030F34:
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _02030F26
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02030F40
FUN_02030F40: ; 0x02030F40
	push {r3, lr}
	ldr r0, _02030F5C ; =UNK_021C59F4
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _02030F56
	bl FUN_02033534
	cmp r0, #0x13
	blt _02030F56
	mov r0, #0x1
	pop {r3, pc}
_02030F56:
	bl FUN_0202EDF8
	pop {r3, pc}
	.balign 4
_02030F5C: .word UNK_021C59F4

	thumb_func_start FUN_02030F60
FUN_02030F60: ; 0x02030F60
	ldr r1, _02030F6C ; =UNK_021C59F4
	ldr r2, [r1, #0x4]
	ldr r1, _02030F70 ; =0x0000062B
	strb r0, [r2, r1]
	bx lr
	nop
_02030F6C: .word UNK_021C59F4
_02030F70: .word 0x0000062B

	thumb_func_start FUN_02030F74
FUN_02030F74: ; 0x02030F74
	ldr r1, _02030F84 ; =UNK_021C59F4
	ldr r1, [r1, #0x4]
	add r1, r1, r0
	mov r0, #0x62
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	bx lr
	nop
_02030F84: .word UNK_021C59F4

	thumb_func_start FUN_02030F88
FUN_02030F88: ; 0x02030F88
	ldr r1, _02030FA4 ; =UNK_021C59F4
	ldr r2, [r1, #0x4]
	cmp r2, #0x0
	bne _02030F94
	mov r0, #0x0
	bx lr
_02030F94:
	mov r1, #0x61
	lsl r1, r1, #0x4
	add r3, r2, r1
	lsl r2, r0, #0x1
	ldrh r0, [r3, r2]
	mov r1, #0x0
	strh r1, [r3, r2]
	bx lr
	.balign 4
_02030FA4: .word UNK_021C59F4

	thumb_func_start FUN_02030FA8
FUN_02030FA8: ; 0x02030FA8
	ldr r0, _02030FC0 ; =UNK_021C59F4
	ldr r3, [r0, #0x4]
	cmp r3, #0x0
	beq _02030FBC
	ldr r1, _02030FC4 ; =0x00000628
	mov r0, #0x2
	ldrh r2, [r3, r1]
	lsl r0, r0, #0xe
	orr r0, r2
	strh r0, [r3, r1]
_02030FBC:
	bx lr
	nop
_02030FC0: .word UNK_021C59F4
_02030FC4: .word 0x00000628

	thumb_func_start FUN_02030FC8
FUN_02030FC8: ; 0x02030FC8
	ldr r0, _02030FD8 ; =UNK_021C59F4
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	beq _02030FD6
	ldr r0, _02030FDC ; =0x00000628
	mov r1, #0x0
	strh r1, [r2, r0]
_02030FD6:
	bx lr
	.balign 4
_02030FD8: .word UNK_021C59F4
_02030FDC: .word 0x00000628

	thumb_func_start FUN_02030FE0
FUN_02030FE0: ; 0x02030FE0
	ldr r0, _02030FF8 ; =UNK_021C59F4
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _02030FF4
	ldr r0, _02030FFC ; =0x00000628
	ldrh r1, [r1, r0]
	mov r0, #0x2
	lsl r0, r0, #0xe
	and r0, r1
	bx lr
_02030FF4:
	mov r0, #0x1
	bx lr
	.balign 4
_02030FF8: .word UNK_021C59F4
_02030FFC: .word 0x00000628

	thumb_func_start FUN_02031000
FUN_02031000: ; 0x02031000
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _02031030
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldr r0, _02031050 ; =UNK_021C59F4
	add r2, r4, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02031054 ; =0x0000054C
	add r3, r6, #0x0
	add r0, r1, r0
	add r1, r5, #0x0
	bl FUN_0202D684
	add sp, #0x8
	pop {r4-r6, pc}
_02031030:
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldr r0, _02031050 ; =UNK_021C59F4
	add r2, r4, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02031058 ; =0x0000056C
	add r3, r6, #0x0
	add r0, r1, r0
	add r1, r5, #0x0
	bl FUN_0202D684
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_02031050: .word UNK_021C59F4
_02031054: .word 0x0000054C
_02031058: .word 0x0000056C

	thumb_func_start FUN_0203105C
FUN_0203105C: ; 0x0203105C
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, _02031080 ; =UNK_021C59F4
	add r4, r1, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02031084 ; =0x0000054C
	add r3, r2, #0x0
	add r0, r1, r0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0202D684
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_02031080: .word UNK_021C59F4
_02031084: .word 0x0000054C

	thumb_func_start FUN_02031088
FUN_02031088: ; 0x02031088
	push {r3, lr}
	ldr r0, _02031100 ; =UNK_021C59F4
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	beq _020310FC
	ldr r1, _02031104 ; =0x0000067B
	ldrb r0, [r2, r1]
	cmp r0, #0x1
	beq _020310A0
	cmp r0, #0x3
	beq _020310D8
	pop {r3, pc}
_020310A0:
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _020310B8
	ldr r1, _02031100 ; =UNK_021C59F4
	mov r0, #0xb
	ldr r2, [r1, #0x4]
	ldr r1, _02031108 ; =0x0000067C
	add r1, r2, r1
	bl FUN_020311D0
	b _020310C8
_020310B8:
	ldr r1, _02031100 ; =UNK_021C59F4
	mov r0, #0xb
	ldr r2, [r1, #0x4]
	ldr r1, _02031108 ; =0x0000067C
	add r1, r2, r1
	mov r2, #0x1
	bl FUN_02030BC4
_020310C8:
	cmp r0, #0x0
	beq _020310FC
	ldr r0, _02031100 ; =UNK_021C59F4
	mov r2, #0x2
	ldr r1, [r0, #0x4]
	ldr r0, _02031104 ; =0x0000067B
	strb r2, [r1, r0]
	pop {r3, pc}
_020310D8:
	add r1, r1, #0x1
	mov r0, #0xc
	add r1, r2, r1
	bl FUN_020311D0
	cmp r0, #0x0
	beq _020310FC
	ldr r0, _02031100 ; =UNK_021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _02031108 ; =0x0000067C
	ldrb r0, [r1, r0]
	bl FUN_0202F9E0
	ldr r0, _02031100 ; =UNK_021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02031104 ; =0x0000067B
	strb r2, [r1, r0]
_020310FC:
	pop {r3, pc}
	nop
_02031100: .word UNK_021C59F4
_02031104: .word 0x0000067B
_02031108: .word 0x0000067C

	thumb_func_start FUN_0203110C
FUN_0203110C: ; 0x0203110C
	push {r4, lr}
	add r4, r2, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	bne _0203112A
	ldr r1, _0203112C ; =UNK_021C59F4
	ldr r0, _02031130 ; =0x0000067B
	ldr r2, [r1, #0x4]
	mov r3, #0x1
	strb r3, [r2, r0]
	ldrb r2, [r4, #0x0]
	ldr r1, [r1, #0x4]
	add r0, r0, #0x1
	strb r2, [r1, r0]
_0203112A:
	pop {r4, pc}
	.balign 4
_0203112C: .word UNK_021C59F4
_02031130: .word 0x0000067B

	thumb_func_start FUN_02031134
FUN_02031134: ; 0x02031134
	push {r4, lr}
	add r4, r2, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	beq _02031152
	ldr r1, _02031154 ; =UNK_021C59F4
	ldrb r3, [r4, #0x0]
	ldr r2, [r1, #0x4]
	ldr r0, _02031158 ; =0x0000067C
	strb r3, [r2, r0]
	ldr r1, [r1, #0x4]
	mov r2, #0x3
	sub r0, r0, #0x1
	strb r2, [r1, r0]
_02031152:
	pop {r4, pc}
	.balign 4
_02031154: .word UNK_021C59F4
_02031158: .word 0x0000067C

	thumb_func_start FUN_0203115C
FUN_0203115C: ; 0x0203115C
	push {r4, lr}
	add r4, r2, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	bne _02031184
	ldr r0, _02031188 ; =UNK_021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _0203118C ; =0x0000067B
	ldrb r0, [r1, r0]
	cmp r0, #0x2
	bne _02031184
	ldrb r0, [r4, #0x0]
	bl FUN_0202F9E0
	ldr r0, _02031188 ; =UNK_021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _0203118C ; =0x0000067B
	strb r2, [r1, r0]
_02031184:
	pop {r4, pc}
	nop
_02031188: .word UNK_021C59F4
_0203118C: .word 0x0000067B

	thumb_func_start FUN_02031190
FUN_02031190: ; 0x02031190
	push {r3, lr}
	ldr r0, _020311CC ; =UNK_021C59F4
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _020311C6
	bl FUN_02033534
	cmp r0, #0x13
	blt _020311B4
	bl MOD04_021D8018
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _020311C6
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r3, pc}
_020311B4:
	bl FUN_02031280
	cmp r0, #0x0
	beq _020311C0
	mov r0, #0x0
	pop {r3, pc}
_020311C0:
	bl FUN_0202D19C
	pop {r3, pc}
_020311C6:
	mov r0, #0x0
	pop {r3, pc}
	nop
_020311CC: .word UNK_021C59F4

	thumb_func_start FUN_020311D0
FUN_020311D0: ; 0x020311D0
	ldr r3, _020311D8 ; =FUN_02030ADC
	mov r2, #0x0
	bx r3
	nop
_020311D8: .word FUN_02030ADC

	thumb_func_start FUN_020311DC
FUN_020311DC: ; 0x020311DC
	ldr r3, _020311E4 ; =FUN_02030ADC
	mov r1, #0x0
	add r2, r1, #0x0
	bx r3
	.balign 4
_020311E4: .word FUN_02030ADC

	thumb_func_start FUN_020311E8
FUN_020311E8: ; 0x020311E8
	ldr r3, _020311EC ; =FUN_0202EE24
	bx r3
	.balign 4
_020311EC: .word FUN_0202EE24

	thumb_func_start FUN_020311F0
FUN_020311F0: ; 0x020311F0
	push {r3, lr}
	bl FUN_02031280
	cmp r0, #0x0
	beq _020311FE
	mov r0, #0x0
	pop {r3, pc}
_020311FE:
	ldr r0, _02031220 ; =UNK_021C59F4
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _0203121A
	ldr r0, _02031224 ; =0x00000689
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0203121A
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_020334E8
	mov r0, #0x1
	pop {r3, pc}
_0203121A:
	bl FUN_0202EE60
	pop {r3, pc}
	.balign 4
_02031220: .word UNK_021C59F4
_02031224: .word 0x00000689

	thumb_func_start FUN_02031228
FUN_02031228: ; 0x02031228
	push {r3, lr}
	bl FUN_0202D858
	cmp r0, #0x5
	blo _02031236
	mov r0, #0xc
	pop {r3, pc}
_02031236:
	bl FUN_0202FA28
	cmp r0, #0x0
	bne _02031242
	mov r0, #0xc
	pop {r3, pc}
_02031242:
	mov r0, #0x26
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02031248
FUN_02031248: ; 0x02031248
	push {r3, lr}
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D858
	add r0, r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02031258
FUN_02031258: ; 0x02031258
	push {r3, lr}
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D884
	add r0, r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02031268
FUN_02031268: ; 0x02031268
	ldr r1, _02031278 ; =UNK_021C59F4
	ldr r2, [r1, #0x4]
	cmp r2, #0x0
	beq _02031274
	ldr r1, _0203127C ; =0x00000686
	strb r0, [r2, r1]
_02031274:
	bx lr
	nop
_02031278: .word UNK_021C59F4
_0203127C: .word 0x00000686

	thumb_func_start FUN_02031280
FUN_02031280: ; 0x02031280
	ldr r0, _02031294 ; =UNK_021C59F4
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _0203128E
	ldr r0, _02031298 ; =0x00000686
	ldrb r0, [r1, r0]
	bx lr
_0203128E:
	mov r0, #0x0
	bx lr
	nop
_02031294: .word UNK_021C59F4
_02031298: .word 0x00000686

	thumb_func_start FUN_0203129C
FUN_0203129C: ; 0x0203129C
	push {r3, lr}
	bl FUN_0202F03C
	cmp r0, #0x0
	bne _020312B6
	bl FUN_02031190
	cmp r0, #0x0
	bne _020312B6
	mov r0, #0x2
	add r1, sp, #0x0
	bl FUN_02030C4C
_020312B6:
	bl FUN_0202F05C
	pop {r3, pc}

	thumb_func_start FUN_020312BC
FUN_020312BC: ; 0x020312BC
	push {r3-r7, lr}
	sub sp, #0x20
	add r4, r0, #0x0
	add r0, sp, #0x10
	add r1, sp, #0x4
	bl GF_RTC_CopyDateTime
	ldr r0, _02031340 ; =gMain
	ldr r6, [sp, #0x10]
	mov r5, #0x0
	lsr r7, r6, #0x1c
	lsl r5, r5, #0x4
	ldr r1, [sp, #0xc]
	ldr r0, [r0, #0x2c]
	lsl r6, r6, #0x4
	add r3, r1, r0
	ldr r0, [sp, #0x18]
	orr r5, r7
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x4]
	add r6, r0, r6
	ldr r0, _02031344 ; =0x00000000
	ldr r2, [sp, #0x8]
	adc r0, r5
	lsr r5, r6, #0x1b
	lsl r0, r0, #0x5
	orr r0, r5
	ldr r5, [sp, #0x0]
	lsl r6, r6, #0x5
	add r6, r5, r6
	ldr r5, _02031344 ; =0x00000000
	adc r5, r0
	lsr r0, r6, #0x1b
	lsl r5, r5, #0x5
	orr r5, r0
	lsl r0, r6, #0x5
	add r6, r1, r0
	ldr r1, _02031344 ; =0x00000000
	adc r1, r5
	lsr r0, r6, #0x1a
	lsl r1, r1, #0x6
	orr r1, r0
	lsl r0, r6, #0x6
	add r5, r2, r0
	ldr r2, _02031344 ; =0x00000000
	adc r2, r1
	lsr r0, r5, #0x1a
	lsl r1, r2, #0x6
	orr r1, r0
	lsl r0, r5, #0x6
	add r2, r3, r0
	ldr r0, _02031344 ; =0x00000000
	str r2, [r4, #0x0]
	adc r0, r1
	str r0, [r4, #0x4]
	ldr r1, _02031348 ; =0x6C078965
	ldr r0, _0203134C ; =0x5D588B65
	str r1, [r4, #0x8]
	str r0, [r4, #0xc]
	ldr r0, _02031350 ; =0x00269EC3
	str r0, [r4, #0x10]
	mov r0, #0x0
	str r0, [r4, #0x14]
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4
_02031340: .word gMain
_02031344: .word 0x00000000
_02031348: .word 0x6C078965
_0203134C: .word 0x5D588B65
_02031350: .word 0x00269EC3

	thumb_func_start FUN_02031354
FUN_02031354: ; 0x02031354
	add r1, r0, #0x0
	ldr r0, _02031364 ; =UNK_021C59F4
	ldr r3, _02031368 ; =FUN_0202D830
	ldr r2, [r0, #0x4]
	ldr r0, _0203136C ; =0x0000056C
	add r0, r2, r0
	bx r3
	nop
_02031364: .word UNK_021C59F4
_02031368: .word FUN_0202D830
_0203136C: .word 0x0000056C

	thumb_func_start FUN_02031370
FUN_02031370: ; 0x02031370
	ldr r0, _0203137C ; =UNK_021C59F4
	ldr r3, _02031380 ; =FUN_0202D4E4
	ldr r1, [r0, #0x4]
	ldr r0, _02031384 ; =0x0000056C
	add r0, r1, r0
	bx r3
	.balign 4
_0203137C: .word UNK_021C59F4
_02031380: .word FUN_0202D4E4
_02031384: .word 0x0000056C

	thumb_func_start FUN_02031388
FUN_02031388: ; 0x02031388
	ldr r0, _02031394 ; =UNK_021C59F4
	ldr r3, _02031398 ; =FUN_0202D4E4
	ldr r1, [r0, #0x4]
	ldr r0, _0203139C ; =0x0000054C
	add r0, r1, r0
	bx r3
	.balign 4
_02031394: .word UNK_021C59F4
_02031398: .word FUN_0202D4E4
_0203139C: .word 0x0000054C

	thumb_func_start FUN_020313A0
FUN_020313A0: ; 0x020313A0
	ldr r1, _020313AC ; =UNK_021C59F4
	ldr r2, [r1, #0x4]
	ldr r1, _020313B0 ; =0x00000687
	strb r0, [r2, r1]
	bx lr
	nop
_020313AC: .word UNK_021C59F4
_020313B0: .word 0x00000687

	thumb_func_start FUN_020313B4
FUN_020313B4: ; 0x020313B4
	ldr r2, _020313C4 ; =UNK_021C59F4
	ldr r2, [r2, #0x4]
	cmp r2, #0x0
	beq _020313C2
	add r2, r2, r1
	ldr r1, _020313C8 ; =0x00000677
	strb r0, [r2, r1]
_020313C2:
	bx lr
	.balign 4
_020313C4: .word UNK_021C59F4
_020313C8: .word 0x00000677

	thumb_func_start FUN_020313CC
FUN_020313CC: ; 0x020313CC
	ldr r1, _020313E4 ; =UNK_021C59F4
	ldr r1, [r1, #0x4]
	cmp r1, #0x0
	beq _020313E0
	add r2, r1, r0
	ldr r1, _020313E8 ; =0x00000677
	ldrb r1, [r2, r1]
	cmp r1, #0xff
	beq _020313E0
	add r0, r1, #0x0
_020313E0:
	bx lr
	nop
_020313E4: .word UNK_021C59F4
_020313E8: .word 0x00000677

	thumb_func_start FUN_020313EC
FUN_020313EC: ; 0x020313EC
	push {r3, lr}
	bl FUN_02033534
	cmp r0, #0x13
	bge _020313FA
	mov r0, #0x0
	pop {r3, pc}
_020313FA:
	bl MOD04_021D8624
	pop {r3, pc}

	thumb_func_start FUN_02031400
FUN_02031400: ; 0x02031400
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02033534
	cmp r0, #0x13
	blt _02031430
	ldr r2, _02031434 ; =UNK_021C59F4
	mov r1, #0x63
	ldr r0, [r2, #0x4]
	lsl r1, r1, #0x4
	str r4, [r0, r1]
	cmp r4, #0x0
	beq _02031430
	ldr r3, [r2, #0x4]
	mov r4, #0x0
	add r0, r1, #0x4
	str r4, [r3, r0]
	add r0, r1, #0x0
	ldr r3, [r2, #0x4]
	add r0, #0x8
	str r4, [r3, r0]
	ldr r0, [r2, #0x4]
	add r1, #0xc
	str r4, [r0, r1]
_02031430:
	pop {r4, pc}
	nop
_02031434: .word UNK_021C59F4

	thumb_func_start FUN_02031438
FUN_02031438: ; 0x02031438
	ldr r0, _0203144C ; =UNK_021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _02031450 ; =0x00000681
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _02031448
	mov r0, #0x1
	bx lr
_02031448:
	mov r0, #0x0
	bx lr
	.balign 4
_0203144C: .word UNK_021C59F4
_02031450: .word 0x00000681

	thumb_func_start FUN_02031454
FUN_02031454: ; 0x02031454
	ldr r0, _02031460 ; =UNK_021C59F4
	mov r2, #0x1
	ldr r1, [r0, #0x4]
	ldr r0, _02031464 ; =0x00000689
	strb r2, [r1, r0]
	bx lr
	.balign 4
_02031460: .word UNK_021C59F4
_02031464: .word 0x00000689

	thumb_func_start FUN_02031468
FUN_02031468: ; 0x02031468
	ldr r0, _02031478 ; =UNK_021C59F4
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	beq _02031476
	ldr r0, _0203147C ; =0x0000068A
	mov r1, #0x1
	strb r1, [r2, r0]
_02031476:
	bx lr
	.balign 4
_02031478: .word UNK_021C59F4
_0203147C: .word 0x0000068A
