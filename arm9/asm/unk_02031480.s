	.include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_021C59FC

	.text

	thumb_func_start FUN_02031480
FUN_02031480: ; 0x02031480
	push {r4, lr}
	ldr r1, _020314C8 ; =UNK_021C59FC
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _0203149C
	ldr r1, _020314CC ; =0x00000253
	bl FUN_02016998
	ldr r1, _020314C8 ; =UNK_021C59FC
	ldr r2, _020314CC ; =0x00000253
	str r0, [r1, #0x0]
	mov r1, #0x0
	bl MI_CpuFill8
_0203149C:
	ldr r1, _020314C8 ; =UNK_021C59FC
	mov r3, #0x0
	mov r0, #0xff
_020314A2:
	ldr r2, [r1, #0x0]
	add r2, r2, r3
	add r3, r3, #0x1
	strb r0, [r2, #0x10]
	cmp r3, #0x8
	blt _020314A2
	ldr r3, _020314C8 ; =UNK_021C59FC
	mov r1, #0x25
	ldr r2, [r3, #0x0]
	lsl r1, r1, #0x4
	strb r0, [r2, r1]
	ldr r4, [r3, #0x0]
	add r2, r1, #0x1
	strb r0, [r4, r2]
	ldr r2, [r3, #0x0]
	mov r4, #0x0
	add r0, r1, #0x2
	strb r4, [r2, r0]
	pop {r4, pc}
	.balign 4
_020314C8: .word UNK_021C59FC
_020314CC: .word 0x00000253

	thumb_func_start FUN_020314D0
FUN_020314D0: ; 0x020314D0
	push {r3, lr}
	ldr r0, _020314E4 ; =UNK_021C59FC
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, _020314E4 ; =UNK_021C59FC
	mov r1, #0x0
	str r1, [r0, #0x0]
	pop {r3, pc}
	nop
_020314E4: .word UNK_021C59FC

	thumb_func_start FUN_020314E8
FUN_020314E8: ; 0x020314E8
	ldr r0, _020314F8 ; =UNK_021C59FC
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020314F4
	mov r0, #0x1
	bx lr
_020314F4:
	mov r0, #0x0
	bx lr
	.balign 4
_020314F8: .word UNK_021C59FC

	thumb_func_start FUN_020314FC
FUN_020314FC: ; 0x020314FC
	push {r3-r6, lr}
	sub sp, #0x4
	ldrb r1, [r2, #0x0]
	add r5, r0, #0x0
	add r0, sp, #0x0
	strb r1, [r0, #0x0]
	bl FUN_02031190
	cmp r0, #0x0
	bne _02031556
	add r0, sp, #0x0
	strb r5, [r0, #0x1]
	ldrb r1, [r0, #0x0]
	strb r1, [r0, #0x2]
	add r1, sp, #0x0
	mov r0, #0x12
	add r1, #0x1
	bl FUN_02030C4C
	ldr r6, _0203155C ; =UNK_021C59FC
	add r4, sp, #0x0
	ldr r0, [r6, #0x0]
	ldrb r1, [r4, #0x0]
	add r0, r0, r5
	mov r5, #0x0
	strb r1, [r0, #0x10]
_02031530:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _02031548
	ldr r0, [r6, #0x0]
	ldrb r1, [r4, #0x0]
	add r0, r0, r5
	ldrb r0, [r0, #0x10]
	cmp r1, r0
	bne _02031556
_02031548:
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _02031530
	mov r0, #0x11
	add r1, sp, #0x0
	bl FUN_02030C4C
_02031556:
	add sp, #0x4
	pop {r3-r6, pc}
	nop
_0203155C: .word UNK_021C59FC

	thumb_func_start FUN_02031560
FUN_02031560: ; 0x02031560
	ldr r0, _02031570 ; =UNK_021C59FC
	ldrb r3, [r2, #0x1]
	ldr r1, [r0, #0x0]
	ldrb r0, [r2, #0x0]
	add r0, r1, r0
	strb r3, [r0, #0x10]
	bx lr
	nop
_02031570: .word UNK_021C59FC

	thumb_func_start FUN_02031574
FUN_02031574: ; 0x02031574
	ldr r0, _02031584 ; =UNK_021C59FC
	ldrb r2, [r2, #0x0]
	ldr r1, [r0, #0x0]
	mov r0, #0x25
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
	bx lr
	nop
_02031584: .word UNK_021C59FC

	thumb_func_start FUN_02031588
FUN_02031588: ; 0x02031588
	ldr r2, _0203159C ; =UNK_021C59FC
	ldr r1, _020315A0 ; =0x00000251
	ldr r3, [r2, #0x0]
	strb r0, [r3, r1]
	ldr r2, [r2, #0x0]
	mov r3, #0x1
	add r0, r1, #0x1
	strb r3, [r2, r0]
	bx lr
	nop
_0203159C: .word UNK_021C59FC
_020315A0: .word 0x00000251

	thumb_func_start FUN_020315A4
FUN_020315A4: ; 0x020315A4
	push {r3, lr}
	ldr r0, _020315D0 ; =UNK_021C59FC
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _020315CE
	ldr r1, _020315D4 ; =0x00000252
	ldrb r0, [r2, r1]
	cmp r0, #0x0
	beq _020315CE
	sub r1, r1, #0x1
	mov r0, #0x10
	add r1, r2, r1
	bl FUN_020311D0
	cmp r0, #0x0
	beq _020315CE
	ldr r0, _020315D0 ; =UNK_021C59FC
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	ldr r0, _020315D4 ; =0x00000252
	strb r2, [r1, r0]
_020315CE:
	pop {r3, pc}
	.balign 4
_020315D0: .word UNK_021C59FC
_020315D4: .word 0x00000252

	thumb_func_start FUN_020315D8
FUN_020315D8: ; 0x020315D8
	ldr r1, _020315F8 ; =UNK_021C59FC
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	bne _020315E4
	mov r0, #0x1
	bx lr
_020315E4:
	mov r1, #0x25
	lsl r1, r1, #0x4
	ldrb r1, [r2, r1]
	cmp r1, r0
	bne _020315F2
	mov r0, #0x1
	bx lr
_020315F2:
	mov r0, #0x0
	bx lr
	nop
_020315F8: .word UNK_021C59FC

	thumb_func_start FUN_020315FC
FUN_020315FC: ; 0x020315FC
	ldr r1, _02031608 ; =UNK_021C59FC
	ldr r1, [r1, #0x0]
	add r0, r1, r0
	ldrb r0, [r0, #0x10]
	bx lr
	nop
_02031608: .word UNK_021C59FC

	thumb_func_start FUN_0203160C
FUN_0203160C: ; 0x0203160C
	push {r3-r4}
	lsl r4, r0, #0x1
	ldr r0, _02031624 ; =UNK_021C59FC
	ldrb r3, [r2, #0x0]
	ldr r1, [r0, #0x0]
	strb r3, [r1, r4]
	ldr r0, [r0, #0x0]
	ldrb r1, [r2, #0x1]
	add r0, r0, r4
	strb r1, [r0, #0x1]
	pop {r3-r4}
	bx lr
	.balign 4
_02031624: .word UNK_021C59FC

	thumb_func_start FUN_02031628
FUN_02031628: ; 0x02031628
	mov r0, #0x2
	bx lr

	thumb_func_start FUN_0203162C
FUN_0203162C: ; 0x0203162C
	push {r3, lr}
	add r2, sp, #0x0
	strb r0, [r2, #0x0]
	strb r1, [r2, #0x1]
	mov r0, #0x13
	add r1, sp, #0x0
	bl FUN_020311D0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02031640
FUN_02031640: ; 0x02031640
	ldr r2, _02031664 ; =UNK_021C59FC
	ldr r3, [r2, #0x0]
	cmp r3, #0x0
	bne _0203164E
	mov r0, #0x0
	mvn r0, r0
	bx lr
_0203164E:
	lsl r2, r0, #0x1
	ldrb r0, [r3, r2]
	cmp r1, r0
	bne _0203165C
	add r0, r3, r2
	ldrb r0, [r0, #0x1]
	bx lr
_0203165C:
	mov r0, #0x0
	mvn r0, r0
	bx lr
	nop
_02031664: .word UNK_021C59FC

	thumb_func_start FUN_02031668
FUN_02031668: ; 0x02031668
	push {r3-r7, lr}
	mov r4, #0x0
	ldr r6, _02031688 ; =UNK_021C59FC
	add r5, r4, #0x0
	add r7, r4, #0x0
_02031672:
	ldr r0, [r6, #0x0]
	add r1, r7, #0x0
	add r0, r0, r5
	mov r2, #0x2
	bl MI_CpuFill8
	add r4, r4, #0x1
	add r5, r5, #0x2
	cmp r4, #0x8
	blt _02031672
	pop {r3-r7, pc}
	.balign 4
_02031688: .word UNK_021C59FC

	thumb_func_start FUN_0203168C
FUN_0203168C: ; 0x0203168C
	push {r3-r4}
	mov r4, #0x0
	mov r0, #0x92
	ldr r1, _020316A8 ; =UNK_021C59FC
	add r3, r4, #0x0
	lsl r0, r0, #0x2
_02031698:
	ldr r2, [r1, #0x0]
	add r2, r2, r4
	add r4, r4, #0x1
	strb r3, [r2, r0]
	cmp r4, #0x8
	blt _02031698
	pop {r3-r4}
	bx lr
	.balign 4
_020316A8: .word UNK_021C59FC

	thumb_func_start FUN_020316AC
FUN_020316AC: ; 0x020316AC
	push {r4, lr}
	ldr r2, _020316DC ; =UNK_021C59FC
	ldr r3, [r2, #0x0]
	cmp r3, #0x0
	beq _020316D8
	add r4, r0, #0x0
	mov r2, #0x46
	mul r4, r2
	add r3, #0x18
	add r0, r1, #0x0
	add r1, r3, r4
	bl MI_CpuCopy8
	ldr r1, _020316DC ; =UNK_021C59FC
	mov r0, #0x14
	ldr r1, [r1, #0x0]
	add r1, #0x18
	add r1, r1, r4
	bl FUN_020311D0
	mov r0, #0x1
	pop {r4, pc}
_020316D8:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_020316DC: .word UNK_021C59FC

	thumb_func_start FUN_020316E0
FUN_020316E0: ; 0x020316E0
	ldr r1, _02031700 ; =UNK_021C59FC
	ldr r3, [r1, #0x0]
	mov r1, #0x92
	add r2, r3, r0
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _020316FA
	mov r1, #0x46
	add r3, #0x18
	mul r1, r0
	add r0, r3, r1
	bx lr
_020316FA:
	mov r0, #0x0
	bx lr
	nop
_02031700: .word UNK_021C59FC

	thumb_func_start FUN_02031704
FUN_02031704: ; 0x02031704
	push {r3-r5, lr}
	ldr r3, _0203172C ; =UNK_021C59FC
	add r1, r0, #0x0
	ldr r0, [r3, #0x0]
	mov r5, #0x1
	add r4, r0, r1
	mov r0, #0x92
	lsl r0, r0, #0x2
	strb r5, [r4, r0]
	ldr r4, [r3, #0x0]
	add r0, r2, #0x0
	mov r2, #0x46
	add r3, r1, #0x0
	add r4, #0x18
	mul r3, r2
	add r1, r4, r3
	bl MI_CpuCopy8
	pop {r3-r5, pc}
	nop
_0203172C: .word UNK_021C59FC

	thumb_func_start FUN_02031730
FUN_02031730: ; 0x02031730
	mov r0, #0x46
	bx lr
