    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020F7460
UNK_020F7460: ; 0x020F7460
	.word 0x00000156, 0x00000157, 0x00000158, 0x00000159
	.word 0x0000015A, 0x0000015B, 0x0000015D, 0x0000015E
	.word 0x00000161, 0x00000162, 0x00000164, 0x0000016A
	.word 0x0000016B, 0x0000016D, 0x0000016E, 0x0000016F
	.word 0x00000173, 0x00000175, 0x0000017C, 0x0000017E
	.word 0x0000017F, 0x00000181, 0x00000184, 0x00000187
	.word 0x000001D3, 0x00000188, 0x0000018B, 0x000000C8
	.word 0x000000CC

	.global UNK_020F74D4
UNK_020F74D4: ; 0x020F74D4
	.short 2, 0x0001, 0x0017, 0xFFFF, 0xFFFF, 0xFFFF
	.short 5, 0x0000, 0x0002, 0x0003, 0x0016, 0x0017
	.short 4, 0x0001, 0x0003, 0x0008, 0x0016, 0xFFFF
	.short 4, 0x0001, 0x0002, 0x0004, 0x0016, 0xFFFF
	.short 2, 0x0003, 0x0005, 0xFFFF, 0xFFFF, 0xFFFF
	.short 4, 0x0004, 0x0006, 0x001B, 0x001C, 0xFFFF
	.short 3, 0x0005, 0x0007, 0x0009, 0xFFFF, 0xFFFF
	.short 3, 0x0006, 0x0008, 0x000D, 0xFFFF, 0xFFFF
	.short 3, 0x0002, 0x0007, 0x0009, 0xFFFF, 0xFFFF
	.short 3, 0x0008, 0x000A, 0x000F, 0xFFFF, 0xFFFF
	.short 3, 0x0009, 0x000B, 0x000F, 0xFFFF, 0xFFFF
	.short 3, 0x000A, 0x000C, 0x0013, 0xFFFF, 0xFFFF
	.short 2, 0x000B, 0x000E, 0xFFFF, 0xFFFF, 0xFFFF
	.short 4, 0x0006, 0x0007, 0x000E, 0x0014, 0xFFFF
	.short 3, 0x000C, 0x000D, 0x0014, 0xFFFF, 0x0000
	.short 3, 0x0009, 0x000A, 0x0010, 0xFFFF, 0xFFFF
	.short 2, 0x000F, 0x0011, 0xFFFF, 0xFFFF, 0xFFFF
	.short 3, 0x0010, 0x0012, 0x001A, 0xFFFF, 0xFFFF
	.short 3, 0x0011, 0x0013, 0x001A, 0xFFFF, 0xFFFF
	.short 2, 0x000B, 0x0012, 0xFFFF, 0xFFFF, 0xFFFF
	.short 3, 0x000D, 0x000E, 0x0015, 0xFFFF, 0xFFFF
	.short 1, 0x0014, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
	.short 3, 0x0001, 0x0002, 0x0003, 0xFFFF, 0xFFFF
	.short 3, 0x0000, 0x0001, 0x0018, 0xFFFF, 0xFFFF
	.short 2, 0x0017, 0x0019, 0xFFFF, 0xFFFF, 0xFFFF
	.short 1, 0x0018, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
	.short 2, 0x0011, 0x0012, 0xFFFF, 0xFFFF, 0xFFFF
	.short 1, 0x0005, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
	.short 1, 0x0005, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF

	.text

	thumb_func_start FUN_020603B0
FUN_020603B0: ; 0x020603B0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0202AA38
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02060588
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020603C8
FUN_020603C8: ; 0x020603C8
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r5, #0x0
_020603CE:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_0202AA74
	cmp r0, #0x0
	beq _020603E2
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_020603B0
_020603E2:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x3
	blo _020603CE
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020603F0
FUN_020603F0: ; 0x020603F0
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r4, #0x0
_020603F6:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202AA74
	cmp r0, #0x0
	beq _02060430
	bl LCRandom
	lsl r0, r0, #0x4
	lsr r6, r0, #0x10
	cmp r6, #0x10
	blo _02060412
	bl ErrorHandling
_02060412:
	cmp r6, #0x0
	bne _02060420
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020603B0
	b _02060430
_02060420:
	add r0, r5, #0x0
	bl FUN_0202AA38
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020605D8
_02060430:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x3
	blo _020603F6
	pop {r4-r6, pc}

	thumb_func_start FUN_0206043C
FUN_0206043C: ; 0x0206043C
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x1d
	blo _02060448
	bl ErrorHandling
_02060448:
	ldr r0, _02060450 ; =UNK_020F7460
	lsl r1, r4, #0x2
	ldr r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_02060450: .word UNK_020F7460

	thumb_func_start FUN_02060454
FUN_02060454: ; 0x02060454
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r5, #0x0
_0206045A:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_0202AA74
	cmp r0, #0x0
	beq _0206046A
	mov r0, #0x1
	pop {r3-r5, pc}
_0206046A:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x3
	blo _0206045A
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02060478
FUN_02060478: ; 0x02060478
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02060454
	cmp r0, #0x0
	beq _0206048E
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202AA20
_0206048E:
	pop {r3-r5, pc}

	thumb_func_start FUN_02060490
FUN_02060490: ; 0x02060490
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r1, #0x0
	str r0, [sp, #0x10]
	bl FUN_0202A9B0
	add r1, r5, #0x0
	str r0, [sp, #0x14]
	bl FUN_0202AAA0
	add r4, r0, #0x0
	cmp r5, #0x0
	beq _020604B4
	cmp r5, #0x1
	beq _020604BA
	cmp r5, #0x2
	beq _020604C2
	b _020604C8
_020604B4:
	ldr r7, _02060580 ; =0x000001E1
	mov r6, #0x32
	b _020604D0
_020604BA:
	mov r7, #0x7a
	lsl r7, r7, #0x2
	mov r6, #0x32
	b _020604D0
_020604C2:
	ldr r7, _02060584 ; =0x000001EB
	mov r6, #0x28
	b _020604D0
_020604C8:
	bl ErrorHandling
	add sp, #0x20
	pop {r3-r7, pc}
_020604D0:
	add r0, r4, #0x0
	mov r1, #0x4
	add r2, r7, #0x0
	bl FUN_0202AAFC
	add r0, r4, #0x0
	mov r1, #0x6
	add r2, r6, #0x0
	bl FUN_0202AAFC
	ldr r0, [sp, #0x10]
	bl FUN_020238F4
	str r0, [sp, #0x18]
	mov r0, #0x4
	bl AllocMonZeroed
	str r0, [sp, #0x1c]
	bl ZeroMonData
	ldr r0, [sp, #0x18]
	bl FUN_020239C0
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	mov r1, #0x1
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x1c]
	add r1, r7, #0x0
	add r2, r6, #0x0
	mov r3, #0x20
	bl CreateMon
	add r0, r4, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl FUN_0202AAFC
	add r0, r4, #0x0
	mov r1, #0x8
	mov r2, #0x1
	bl FUN_0202AAFC
	ldr r0, [sp, #0x1c]
	mov r1, #0xae
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_0202AAFC
	mov r1, #0x0
	ldr r0, [sp, #0x1c]
	add r2, r1, #0x0
	bl GetMonData
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_0202AAFC
	ldr r0, [sp, #0x1c]
	mov r1, #0xa3
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x5
	bl FUN_0202AAFC
	ldr r0, [sp, #0x1c]
	bl FreeToHeap
	ldr r0, [sp, #0x14]
	bl FUN_0202AA38
	add r2, r0, #0x0
	ldr r0, [sp, #0x14]
	add r1, r5, #0x0
	bl FUN_02060588
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4
_02060580: .word 0x000001E1
_02060584: .word 0x000001EB

	thumb_func_start FUN_02060588
FUN_02060588: ; 0x02060588
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	add r6, r2, #0x0
	bl FUN_0202AA40
	ldr r7, _020605D0 ; =UNK_020F7460
	lsl r0, r0, #0x2
	ldr r4, [r7, r0]
_0206059C:
	bl LCRandom
	ldr r1, _020605D4 ; =0x000008D4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x1d
	blo _020605B2
	bl ErrorHandling
_020605B2:
	lsl r0, r5, #0x18
	lsr r2, r0, #0x18
	lsl r0, r2, #0x2
	ldr r3, [r7, r0]
	cmp r3, r6
	beq _0206059C
	cmp r3, r4
	beq _0206059C
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	bl FUN_02060688
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_020605D0: .word UNK_020F7460
_020605D4: .word 0x000008D4

	thumb_func_start FUN_020605D8
FUN_020605D8: ; 0x020605D8
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	add r7, r2, #0x0
	bl FUN_0202AA40
	mov r1, #0xc
	ldr r2, _0206067C ; =UNK_020F74D4
	mul r1, r0
	ldrh r0, [r2, r1]
	add r4, r2, r1
	cmp r0, #0x1
	bne _0206061E
	ldrh r0, [r4, #0x2]
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	ldr r0, _02060680 ; =UNK_020F7460
	lsl r1, r2, #0x2
	ldr r3, [r0, r1]
	cmp r3, r7
	bne _02060612
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r2, r7, #0x0
	bl FUN_02060588
	add sp, #0x8
	pop {r3-r7, pc}
_02060612:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	bl FUN_02060688
	add sp, #0x8
	pop {r3-r7, pc}
_0206061E:
	ldrh r5, [r4, #0x0]
	cmp r5, #0x0
	bne _02060628
	bl ErrorHandling
_02060628:
	cmp r5, #0x1
	bhi _02060630
	mov r6, #0x0
	b _02060658
_02060630:
	bl LCRandom
	add r6, r0, #0x0
	ldr r0, _02060684 ; =0x0000FFFF
	add r1, r5, #0x0
	bl _s32_div_f
	add r1, r0, #0x0
	add r1, r1, #0x1
	lsl r1, r1, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r6, r5
	blo _02060658
	bl ErrorHandling
_02060658:
	lsl r0, r6, #0x18
	lsr r0, r0, #0x17
	add r0, r4, r0
	ldrh r0, [r0, #0x2]
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	ldr r0, _02060680 ; =UNK_020F7460
	lsl r1, r2, #0x2
	ldr r3, [r0, r1]
	cmp r3, r7
	beq _0206061E
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	bl FUN_02060688
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0206067C: .word UNK_020F74D4
_02060680: .word UNK_020F7460
_02060684: .word 0x0000FFFF

	thumb_func_start FUN_02060688
FUN_02060688: ; 0x02060688
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_0202AAA0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0202AA58
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	add r2, r7, #0x0
	bl FUN_0202AAFC
	pop {r3-r7, pc}
	.balign 4
