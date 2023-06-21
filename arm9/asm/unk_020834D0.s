	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata
	.global UNK_020FBED8
UNK_020FBED8: ; 0x020FBED8
	.word 0x00000000, sub_0202DA80, 0x00000000
	.word sub_0208350C, sub_0202DA80, 0x00000000
	.word sub_02083510, sub_0202DA78, sub_020834E4
	.word sub_020835A0, sub_02083504, 0x00000000
	.word sub_020835B0, sub_0202DA78, 0x00000000
	.word sub_02083694, sub_0202DA78, 0x00000000
	.word sub_020836FC, sub_0202DA78, sub_020834E4
	.word sub_0208378C, sub_0202DA78, 0x00000000
	.word sub_020837F4, sub_0202DA78, 0x00000000
	.word sub_02083888, sub_0202DA78, 0x00000000
	.word sub_02083904, sub_0202DA78, 0x00000000
	.word sub_02083970, sub_0202DA78, sub_020834E4
	.word sub_02083A1C, sub_02083508, 0x00000000
	.word sub_02083A6C, sub_02083508, 0x00000000
	.word sub_02083AA8, sub_0202DA78, sub_020834E4
	.word sub_02083B10, sub_0202DA78, 0x00000000

	.text

	thumb_func_start sub_020834D0
sub_020834D0: ; 0x020834D0
	ldr r3, _020834DC ; =sub_0202D8D0
	add r2, r0, #0x0
	ldr r0, _020834E0 ; =UNK_020FBED8
	mov r1, #0x10
	bx r3
	nop
_020834DC: .word sub_0202D8D0
_020834E0: .word UNK_020FBED8

	thumb_func_start sub_020834E4
sub_020834E4: ; 0x020834E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x1
	lsl r0, r0, #0xa
	add r4, r1, #0x0
	cmp r2, r0
	blt _020834F6
	bl GF_AssertFail
_020834F6:
	ldr r0, _02083500 ; =0x00000985
	add r1, r4, r0
	lsl r0, r5, #0xa
	add r0, r1, r0
	pop {r3-r5, pc}
	.balign 4
_02083500: .word 0x00000985

	thumb_func_start sub_02083504
sub_02083504: ; 0x02083504
	mov r0, #0xa
	bx lr

	thumb_func_start sub_02083508
sub_02083508: ; 0x02083508
	mov r0, #0x8
	bx lr

	thumb_func_start sub_0208350C
sub_0208350C: ; 0x0208350C
	bx lr
	.balign 4

	thumb_func_start sub_02083510
sub_02083510: ; 0x02083510
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x17
	lsl r0, r0, #0x4
	add r6, r1, #0x0
	ldrb r1, [r3, r0]
	str r2, [sp, #0x0]
	cmp r1, #0x0
	bne _0208352C
	sub r0, r0, #0x4
	ldr r1, [r3, r0]
	ldr r0, _02083590 ; =0x000004FC
	add r4, r1, r0
	b _0208355E
_0208352C:
	cmp r1, #0x1
	bne _0208353A
	sub r0, r0, #0x4
	ldr r1, [r3, r0]
	ldr r0, _02083594 ; =0x00001158
	add r4, r1, r0
	b _0208355E
_0208353A:
	cmp r1, #0x2
	bne _0208354A
	sub r0, r0, #0x4
	ldr r1, [r3, r0]
	mov r0, #0xc3
	lsl r0, r0, #0x4
	add r4, r1, r0
	b _0208355E
_0208354A:
	cmp r1, #0x3
	bne _02083558
	sub r0, r0, #0x4
	ldr r1, [r3, r0]
	ldr r0, _02083598 ; =0x0000085C
	add r4, r1, r0
	b _0208355E
_02083558:
	bl GF_AssertFail
	pop {r3-r7, pc}
_0208355E:
	mov r0, #0x2
	lsl r0, r0, #0x8
	cmp r6, r0
	ble _0208356A
	bl GF_AssertFail
_0208356A:
	ldr r0, _0208359C ; =0x00000A11
	add r7, r4, r0
	ldrb r0, [r7, r5]
	cmp r0, #0x0
	beq _02083578
	bl GF_AssertFail
_02083578:
	mov r1, #0x21
	lsl r1, r1, #0x4
	add r2, r4, r1
	lsl r1, r5, #0x9
	add r1, r2, r1
	ldr r0, [sp, #0x0]
	add r2, r6, #0x0
	bl MI_CpuCopy8
	mov r0, #0x1
	strb r0, [r7, r5]
	pop {r3-r7, pc}
	.balign 4
_02083590: .word 0x000004FC
_02083594: .word 0x00001158
_02083598: .word 0x0000085C
_0208359C: .word 0x00000A11

	thumb_func_start sub_020835A0
sub_020835A0: ; 0x020835A0
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r3, r0]
	ldr r3, _020835AC ; =MOD12_0223D1CC
	add r1, r2, #0x0
	bx r3
	.balign 4
_020835AC: .word MOD12_0223D1CC

	thumb_func_start sub_020835B0
sub_020835B0: ; 0x020835B0
	push {r3-r6, lr}
	sub sp, #0x14
	add r5, r1, #0x0
	mov r1, #0x61
	add r6, r0, #0x0
	add r4, r3, #0x0
	lsl r1, r1, #0x2
	add r0, r2, #0x0
	add r2, r4, r1
	lsl r1, r6, #0x8
	add r1, r2, r1
	add r2, r5, #0x0
	bl MI_CpuCopy8
	ldr r2, _02083628 ; =0x00000584
	ldrb r0, [r4, r2]
	add r0, r0, #0x1
	strb r0, [r4, r2]
	ldr r0, _0208362C ; =0x00000127
	ldrb r2, [r4, r2]
	ldrb r1, [r4, r0]
	cmp r2, r1
	blo _02083622
	mov r3, #0x0
	cmp r1, #0x0
	ble _020835FE
	add r0, #0x5d
	add r5, r4, r0
	mov r0, #0x1
	lsl r0, r0, #0x8
	add r2, r0, #0x0
	add r6, sp, #0x4
	add r2, #0x27
_020835F2:
	stmia r6!, {r5}
	ldrb r1, [r4, r2]
	add r3, r3, #0x1
	add r5, r5, r0
	cmp r3, r1
	blt _020835F2
_020835FE:
	add r0, sp, #0x4
	add r2, sp, #0x0
	bl sub_02083660
	mov r1, #0x47
	lsl r1, r1, #0x2
	strb r0, [r4, r1]
	add r0, sp, #0x0
	ldrb r2, [r0, #0x0]
	add r0, r1, #0x1
	strb r2, [r4, r0]
	ldrb r0, [r4, r1]
	lsl r2, r0, #0x2
	add r0, sp, #0x4
	ldr r0, [r0, r2]
	ldrb r2, [r0, #0x2]
	add r0, r1, #0x6
	strb r2, [r4, r0]
_02083622:
	add sp, #0x14
	pop {r3-r6, pc}
	nop
_02083628: .word 0x00000584
_0208362C: .word 0x00000127

	thumb_func_start sub_02083630
sub_02083630: ; 0x02083630
	push {r3, lr}
	ldr r1, _0208365C ; =0x00000125
	add r3, sp, #0x0
	ldrb r2, [r0, r1]
	strb r2, [r3, #0x0]
	sub r2, r1, #0x2
	ldrb r2, [r0, r2]
	sub r1, r1, #0x3
	strb r2, [r3, #0x1]
	ldrb r0, [r0, r1]
	add r1, sp, #0x0
	mov r2, #0x4
	strb r0, [r3, #0x2]
	mov r0, #0x1a
	bl sub_02030ADC
	cmp r0, #0x1
	bne _02083658
	mov r0, #0x1
	pop {r3, pc}
_02083658:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_0208365C: .word 0x00000125

	thumb_func_start sub_02083660
sub_02083660: ; 0x02083660
	push {r4-r7}
	mov r5, #0x0
	add r4, r5, #0x0
	cmp r1, #0x0
	ble _02083684
	add r6, r0, #0x0
_0208366C:
	lsl r3, r5, #0x2
	ldr r3, [r0, r3]
	ldr r7, [r6, #0x0]
	ldrb r3, [r3, #0x0]
	ldrb r7, [r7, #0x0]
	cmp r3, r7
	bhs _0208367C
	add r5, r4, #0x0
_0208367C:
	add r4, r4, #0x1
	add r6, r6, #0x4
	cmp r4, r1
	blt _0208366C
_02083684:
	lsl r1, r5, #0x2
	ldr r0, [r0, r1]
	ldrb r0, [r0, #0x0]
	strb r0, [r2, #0x0]
	add r0, r5, #0x0
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start sub_02083694
sub_02083694: ; 0x02083694
	push {r3-r5, lr}
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl SizeOfStructPokemon
	add r2, r0, #0x0
	ldrb r1, [r5, r2]
	add r0, r5, #0x0
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	bl MI_CpuCopy8
	ldr r0, _020836B8 ; =0x00000584
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r5, pc}
	nop
_020836B8: .word 0x00000584

	thumb_func_start sub_020836BC
sub_020836BC: ; 0x020836BC
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl SizeOfStructPokemon
	add r4, r0, #0x0
	mov r0, #0x14
	add r1, r4, #0x1
	bl AllocFromHeap
	add r5, r0, #0x0
	add r0, r7, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl MI_CpuCopy8
	mov r0, #0x1b
	add r1, r5, #0x0
	add r2, r4, #0x1
	strb r6, [r5, r4]
	bl sub_02030ADC
	cmp r0, #0x1
	bne _020836F0
	mov r4, #0x1
	b _020836F2
_020836F0:
	mov r4, #0x0
_020836F2:
	add r0, r5, #0x0
	bl FreeToHeap
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start sub_020836FC
sub_020836FC: ; 0x020836FC
	push {r3-r7, lr}
	sub sp, #0x8
	str r2, [sp, #0x0]
	str r3, [sp, #0x4]
	bl SizeOfStructPokemon
	mov r7, #0x0
	ldr r4, [sp, #0x4]
	add r6, r0, #0x0
	add r5, r7, #0x0
_02083710:
	ldr r0, [sp, #0x0]
	ldr r1, [r4, #0x0]
	add r0, r0, r5
	add r2, r6, #0x0
	bl MI_CpuCopy8
	add r7, r7, #0x1
	add r4, r4, #0x4
	add r5, r5, r6
	cmp r7, #0x4
	blt _02083710
	ldr r1, _02083738 ; =0x00000584
	ldr r0, [sp, #0x4]
	ldrb r0, [r0, r1]
	add r2, r0, #0x1
	ldr r0, [sp, #0x4]
	strb r2, [r0, r1]
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02083738: .word 0x00000584

	thumb_func_start sub_0208373C
sub_0208373C: ; 0x0208373C
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r5, r1, #0x0
	bl SizeOfStructPokemon
	add r6, r0, #0x0
	lsl r0, r6, #0x2
	str r0, [sp, #0x0]
	ldr r0, _02083788 ; =0x00000585
	mov r7, #0x0
	add r0, r4, r0
	str r0, [sp, #0x4]
	add r4, r7, #0x0
_02083758:
	ldr r1, [sp, #0x4]
	ldr r0, [r5, #0x0]
	add r1, r1, r4
	add r2, r6, #0x0
	bl MI_CpuCopy8
	add r7, r7, #0x1
	add r4, r4, r6
	add r5, r5, #0x4
	cmp r7, #0x4
	blt _02083758
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	mov r0, #0x1c
	bl sub_02030A78
	cmp r0, #0x1
	bne _02083782
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_02083782:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02083788: .word 0x00000585

	thumb_func_start sub_0208378C
sub_0208378C: ; 0x0208378C
	push {r3-r5, lr}
	add r0, r2, #0x0
	add r2, #0x30
	ldrb r1, [r2, #0x0]
	add r4, r3, #0x0
	add r5, r4, #0x0
	mov r2, #0x30
	add r3, r1, #0x0
	add r5, #0x10
	mul r3, r2
	add r1, r5, r3
	bl MI_CpuCopy8
	ldr r0, _020837B0 ; =0x00000584
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r5, pc}
	.balign 4
_020837B0: .word 0x00000584

	thumb_func_start sub_020837B4
sub_020837B4: ; 0x020837B4
	push {r4-r6, lr}
	add r5, r1, #0x0
	mov r0, #0x14
	mov r1, #0x31
	add r6, r2, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	mov r2, #0x30
	bl MI_CpuCopy8
	add r0, r4, #0x0
	add r0, #0x30
	strb r5, [r0, #0x0]
	mov r0, #0x1d
	add r1, r4, #0x0
	mov r2, #0x31
	bl sub_02030ADC
	cmp r0, #0x1
	bne _020837E6
	mov r5, #0x1
	b _020837E8
_020837E6:
	mov r5, #0x0
_020837E8:
	add r0, r4, #0x0
	bl FreeToHeap
	add r0, r5, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_020837F4
sub_020837F4: ; 0x020837F4
	push {r3-r7, lr}
	add r5, r3, #0x0
	add r6, r2, #0x0
	str r3, [sp, #0x0]
	mov r4, #0x0
	add r5, #0xd0
	mov r7, #0x8
_02083802:
	lsl r0, r4, #0x3
	add r0, r6, r0
	add r1, r5, #0x0
	add r2, r7, #0x0
	bl MI_CpuCopy8
	add r4, r4, #0x1
	add r5, #0x8
	cmp r4, #0x3
	blt _02083802
	ldrb r2, [r6, #0x18]
	ldr r1, _0208382C ; =0x0000011E
	ldr r0, [sp, #0x0]
	strb r2, [r0, r1]
	ldr r1, _02083830 ; =0x00000584
	ldrb r0, [r0, r1]
	add r2, r0, #0x1
	ldr r0, [sp, #0x0]
	strb r2, [r0, r1]
	pop {r3-r7, pc}
	nop
_0208382C: .word 0x0000011E
_02083830: .word 0x00000584

	thumb_func_start sub_02083834
sub_02083834: ; 0x02083834
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	mov r0, #0x14
	mov r1, #0x19
	add r5, r2, #0x0
	bl AllocFromHeap
	add r6, r0, #0x0
	mov r4, #0x0
	mov r7, #0x8
_02083848:
	lsl r1, r4, #0x3
	add r0, r5, #0x0
	add r1, r6, r1
	add r2, r7, #0x0
	bl MI_CpuCopy8
	add r4, r4, #0x1
	add r5, #0x8
	cmp r4, #0x3
	blt _02083848
	ldr r1, _02083884 ; =0x0000011E
	ldr r0, [sp, #0x0]
	mov r2, #0x19
	ldrb r0, [r0, r1]
	add r1, r6, #0x0
	strb r0, [r6, #0x18]
	mov r0, #0x1e
	bl sub_02030ADC
	cmp r0, #0x1
	bne _02083876
	mov r4, #0x1
	b _02083878
_02083876:
	mov r4, #0x0
_02083878:
	add r0, r6, #0x0
	bl FreeToHeap
	add r0, r4, #0x0
	pop {r3-r7, pc}
	nop
_02083884: .word 0x0000011E

	thumb_func_start sub_02083888
sub_02083888: ; 0x02083888
	push {r3-r7, lr}
	add r5, r2, #0x0
	ldrb r0, [r5, #0x0]
	add r6, r3, #0x0
	add r4, r6, #0x0
	add r4, #0xe8
	lsl r7, r0, #0x2
	ldr r0, [r4, r7]
	bl StringSetEmpty
	ldr r0, [r4, r7]
	add r1, r5, #0x4
	bl CopyU16ArrayToString
	ldr r0, _020838B0 ; =0x00000584
	ldrb r1, [r6, r0]
	add r1, r1, #0x1
	strb r1, [r6, r0]
	pop {r3-r7, pc}
	nop
_020838B0: .word 0x00000584

	thumb_func_start sub_020838B4
sub_020838B4: ; 0x020838B4
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r1, #0x0
	add r0, r2, #0x0
	add r1, sp, #0x0
	mov r2, #0x8
	bl CopyStringToU16Array
	mov r0, #0x14
	add r1, r0, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, sp, #0x0
	add r1, r4, #0x4
	mov r2, #0x10
	bl MI_CpuCopy8
	strb r5, [r4, #0x0]
	mov r0, #0x10
	strb r0, [r4, #0x1]
	mov r0, #0x0
	strb r0, [r4, #0x2]
	strb r0, [r4, #0x3]
	mov r0, #0x1f
	add r1, r4, #0x0
	mov r2, #0x14
	bl sub_02030ADC
	cmp r0, #0x1
	bne _020838F6
	mov r5, #0x1
	b _020838F8
_020838F6:
	mov r5, #0x0
_020838F8:
	add r0, r4, #0x0
	bl FreeToHeap
	add r0, r5, #0x0
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start sub_02083904
sub_02083904: ; 0x02083904
	push {r3-r5, lr}
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl sub_02026FE4
	add r2, r0, #0x0
	ldrb r1, [r5, r2]
	add r0, r5, #0x0
	lsl r1, r1, #0x2
	add r1, r4, r1
	add r1, #0xf8
	ldr r1, [r1, #0x0]
	bl MI_CpuCopy8
	ldr r0, _0208392C ; =0x00000584
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r5, pc}
	nop
_0208392C: .word 0x00000584

	thumb_func_start sub_02083930
sub_02083930: ; 0x02083930
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl sub_02026FE4
	add r4, r0, #0x0
	mov r0, #0x14
	add r1, r4, #0x1
	bl AllocFromHeap
	add r5, r0, #0x0
	add r0, r7, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl MI_CpuCopy8
	mov r0, #0x20
	add r1, r5, #0x0
	add r2, r4, #0x1
	strb r6, [r5, r4]
	bl sub_02030ADC
	cmp r0, #0x1
	bne _02083964
	mov r4, #0x1
	b _02083966
_02083964:
	mov r4, #0x0
_02083966:
	add r0, r5, #0x0
	bl FreeToHeap
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start sub_02083970
sub_02083970: ; 0x02083970
	push {r3-r7, lr}
	sub sp, #0x8
	str r2, [sp, #0x0]
	str r3, [sp, #0x4]
	bl sub_02026FE4
	add r6, r0, #0x0
	mov r0, #0x1
	lsl r1, r6, #0x2
	lsl r0, r0, #0xa
	cmp r1, r0
	blt _0208398C
	bl GF_AssertFail
_0208398C:
	mov r7, #0x0
	ldr r4, [sp, #0x4]
	add r5, r7, #0x0
_02083992:
	add r1, r4, #0x0
	ldr r0, [sp, #0x0]
	add r1, #0xf8
	ldr r1, [r1, #0x0]
	add r0, r0, r5
	add r2, r6, #0x0
	bl MI_CpuCopy8
	add r7, r7, #0x1
	add r4, r4, #0x4
	add r5, r5, r6
	cmp r7, #0x4
	blt _02083992
	ldr r1, _020839BC ; =0x00000584
	ldr r0, [sp, #0x4]
	ldrb r0, [r0, r1]
	add r2, r0, #0x1
	ldr r0, [sp, #0x4]
	strb r2, [r0, r1]
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_020839BC: .word 0x00000584

	thumb_func_start sub_020839C0
sub_020839C0: ; 0x020839C0
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r5, r1, #0x0
	bl sub_02026FE4
	add r6, r0, #0x0
	mov r1, #0x1
	lsl r0, r6, #0x2
	lsl r1, r1, #0xa
	str r0, [sp, #0x0]
	cmp r0, r1
	blt _020839DE
	bl GF_AssertFail
_020839DE:
	ldr r0, _02083A18 ; =0x00000585
	mov r7, #0x0
	add r0, r4, r0
	str r0, [sp, #0x4]
	add r4, r7, #0x0
_020839E8:
	ldr r1, [sp, #0x4]
	ldr r0, [r5, #0x0]
	add r1, r1, r4
	add r2, r6, #0x0
	bl MI_CpuCopy8
	add r7, r7, #0x1
	add r4, r4, r6
	add r5, r5, #0x4
	cmp r7, #0x4
	blt _020839E8
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	mov r0, #0x21
	bl sub_02030A78
	cmp r0, #0x1
	bne _02083A12
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_02083A12:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02083A18: .word 0x00000585

	thumb_func_start sub_02083A1C
sub_02083A1C: ; 0x02083A1C
	push {r4, lr}
	add r4, r1, #0x0
	ldr r1, _02083A30 ; =0x000019A0
	add r0, r2, #0x0
	add r1, r3, r1
	add r2, r4, #0x0
	bl MI_CpuCopy8
	pop {r4, pc}
	nop
_02083A30: .word 0x000019A0

	thumb_func_start sub_02083A34
sub_02083A34: ; 0x02083A34
	push {r3, lr}
	add r3, r0, #0x0
	ldrb r0, [r3, #0x16]
	cmp r0, #0x0
	bne _02083A44
	str r1, [r3, #0x0]
	mov r0, #0x1
	pop {r3, pc}
_02083A44:
	ldrb r2, [r3, #0x14]
	ldrb r0, [r3, #0x15]
	cmp r2, r0
	beq _02083A50
	mov r0, #0x0
	pop {r3, pc}
_02083A50:
	str r1, [r3, #0x8]
	add r3, #0x8
	mov r0, #0x22
	add r1, r3, #0x0
	mov r2, #0x8
	bl sub_02030ADC
	cmp r0, #0x1
	bne _02083A66
	mov r0, #0x1
	pop {r3, pc}
_02083A66:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02083A6C
sub_02083A6C: ; 0x02083A6C
	ldrb r2, [r2, #0x4]
	add r1, r3, r0
	ldr r0, _02083A78 ; =0x000019B0
	strb r2, [r1, r0]
	bx lr
	nop
_02083A78: .word 0x000019B0

	thumb_func_start sub_02083A7C
sub_02083A7C: ; 0x02083A7C
	push {r3, lr}
	add r2, r0, #0x0
	ldrb r0, [r2, #0x16]
	cmp r0, #0x0
	bne _02083A8C
	strb r1, [r2, #0x10]
	mov r0, #0x1
	pop {r3, pc}
_02083A8C:
	strb r1, [r2, #0xc]
	add r2, #0x8
	add r1, r2, #0x0
	mov r0, #0x23
	mov r2, #0x8
	bl sub_02030ADC
	cmp r0, #0x1
	bne _02083AA2
	mov r0, #0x1
	pop {r3, pc}
_02083AA2:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02083AA8
sub_02083AA8: ; 0x02083AA8
	push {r3-r5, lr}
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl Save_Chatot_sizeof
	add r2, r0, #0x0
	ldrb r1, [r5, r2]
	add r0, r5, #0x0
	lsl r1, r1, #0x2
	add r3, r4, r1
	mov r1, #0x57
	lsl r1, r1, #0x2
	ldr r1, [r3, r1]
	bl MI_CpuCopy8
	ldr r0, _02083AD0 ; =0x00000584
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r5, pc}
	.balign 4
_02083AD0: .word 0x00000584

	thumb_func_start sub_02083AD4
sub_02083AD4: ; 0x02083AD4
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r7, r1, #0x0
	add r6, r2, #0x0
	bl Save_Chatot_sizeof
	add r5, r0, #0x0
	ldr r0, _02083B0C ; =0x00000585
	add r4, r4, r0
	cmp r6, #0x0
	beq _02083AF4
	add r0, r6, #0x0
	add r1, r4, #0x0
	add r2, r5, #0x0
	bl MI_CpuCopy8
_02083AF4:
	mov r0, #0x24
	add r1, r4, #0x0
	add r2, r5, #0x1
	strb r7, [r4, r5]
	bl sub_02030A78
	cmp r0, #0x1
	bne _02083B08
	mov r0, #0x1
	pop {r3-r7, pc}
_02083B08:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02083B0C: .word 0x00000585

	thumb_func_start sub_02083B10
sub_02083B10: ; 0x02083B10
	push {r3-r6}
	ldrb r1, [r2, #0x6]
	ldrb r4, [r2, #0x0]
	mov r5, #0x42
	add r0, r3, r1
	lsl r5, r5, #0x2
	strb r4, [r0, r5]
	ldrb r6, [r2, #0x1]
	add r4, r5, #0x4
	strb r6, [r0, r4]
	add r4, r5, #0x0
	ldrb r6, [r2, #0x2]
	add r4, #0x8
	add r5, #0xc
	strb r6, [r0, r4]
	lsl r0, r1, #0x1
	ldrh r2, [r2, #0x4]
	add r0, r3, r0
	strh r2, [r0, r5]
	ldr r0, _02083B44 ; =0x00000584
	ldrb r1, [r3, r0]
	add r1, r1, #0x1
	strb r1, [r3, r0]
	pop {r3-r6}
	bx lr
	nop
_02083B44: .word 0x00000584

	thumb_func_start sub_02083B48
sub_02083B48: ; 0x02083B48
	push {r4-r6, lr}
	add r5, r1, #0x0
	mov r0, #0x14
	mov r1, #0x7
	add r6, r2, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	mov r2, #0x6
	bl MI_CpuCopy8
	mov r0, #0x25
	add r1, r4, #0x0
	mov r2, #0x7
	strb r5, [r4, #0x6]
	bl sub_02030ADC
	cmp r0, #0x1
	bne _02083B76
	mov r5, #0x1
	b _02083B78
_02083B76:
	mov r5, #0x0
_02083B78:
	add r0, r4, #0x0
	bl FreeToHeap
	add r0, r5, #0x0
	pop {r4-r6, pc}
	.balign 4
