    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02088320
FUN_02088320: ; 0x02088320
	push {r3-r7, lr}
	add r5, r1, #0x0
	mov r1, #0x59
	lsl r1, r1, #0x2
	add r6, r0, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x0]
	bl FUN_02016998
	mov r2, #0x59
	mov r1, #0x0
	lsl r2, r2, #0x2
	add r4, r0, #0x0
	bl MI_CpuFill8
	str r6, [r4, #0x0]
	cmp r5, #0x10
	bls _0208834A
	mov r0, #0x10
	strh r0, [r4, #0xa]
	b _0208834C
_0208834A:
	strh r7, [r4, #0xa]
_0208834C:
	strh r5, [r4, #0xc]
	ldr r0, [sp, #0x0]
	strh r0, [r4, #0xe]
	ldr r0, [sp, #0x18]
	str r0, [r4, #0x4]
	add r0, r4, #0x0
	bl FUN_0208837C
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02088360
FUN_02088360: ; 0x02088360
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0208843C
	mov r2, #0x59
	add r0, r4, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x2
	bl MI_CpuFill8
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}

	thumb_func_start FUN_0208837C
FUN_0208837C: ; 0x0208837C
	push {r4-r7, lr}
	sub sp, #0xc
	ldr r1, _02088438 ; =0x020FD1C0
	str r0, [sp, #0x0]
	ldrb r2, [r1, #0x0]
	add r0, sp, #0x8
	strb r2, [r0, #0x0]
	ldrb r2, [r1, #0x1]
	strb r2, [r0, #0x1]
	ldrb r2, [r1, #0x2]
	ldrb r1, [r1, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldr r0, [sp, #0x0]
	ldr r2, [sp, #0x0]
	ldr r1, [sp, #0x0]
	ldrh r0, [r0, #0xc]
	ldr r2, [r2, #0x0]
	add r1, #0x14
	bl FUN_02008C9C
	ldr r1, [sp, #0x0]
	mov r6, #0x15
	str r0, [r1, #0x10]
	add r0, r1, #0x0
	ldrh r1, [r0, #0xa]
	add r0, sp, #0x8
	ldr r5, [sp, #0x0]
	strb r1, [r0, #0x1]
	mov r0, #0x0
	str r0, [sp, #0x4]
	add r7, sp, #0x8
	add r4, r0, #0x0
	lsl r6, r6, #0x4
_020883C0:
	ldr r2, [sp, #0x0]
	ldrb r0, [r7, #0x0]
	ldr r1, [sp, #0x4]
	ldr r2, [r2, #0x0]
	bl FUN_02008DEC
	mov r1, #0x5
	lsl r1, r1, #0x6
	str r0, [r5, r1]
	ldr r1, [sp, #0x0]
	ldrb r0, [r7, #0x0]
	ldr r1, [r1, #0x0]
	bl FUN_02009424
	mov r1, #0x15
	lsl r1, r1, #0x4
	str r0, [r5, r1]
	mov r0, #0x15
	lsl r0, r0, #0x4
	ldr r3, [r5, r0]
	mov r1, #0x0
	ldr r0, [r3, #0x4]
	cmp r0, #0x0
	bls _02088402
	add r2, r1, #0x0
_020883F2:
	ldr r0, [r3, #0x0]
	add r1, r1, #0x1
	str r4, [r0, r2]
	ldr r3, [r5, r6]
	add r2, r2, #0x4
	ldr r0, [r3, #0x4]
	cmp r1, r0
	blo _020883F2
_02088402:
	ldr r0, [sp, #0x4]
	add r7, r7, #0x1
	add r0, r0, #0x1
	add r5, r5, #0x4
	str r0, [sp, #0x4]
	cmp r0, #0x4
	blo _020883C0
	ldr r0, [sp, #0x0]
	bl FUN_020886CC
	ldr r0, [sp, #0x0]
	mov r1, #0x4
	ldr r0, [r0, #0x0]
	bl FUN_02016998
	mov r2, #0x16
	ldr r1, [sp, #0x0]
	lsl r2, r2, #0x4
	str r0, [r1, r2]
	add r0, r1, #0x0
	ldr r0, [r0, r2]
	mov r1, #0x0
	mov r2, #0x4
	bl MI_CpuFill8
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02088438: .word 0x020FD1C0

	thumb_func_start FUN_0208843C
FUN_0208843C: ; 0x0208843C
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x16
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	bl FUN_02016A18
	ldr r0, [r5, #0x10]
	bl FUN_0201FD58
	mov r0, #0x15
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	bl FUN_02009C30
	mov r0, #0x55
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl FUN_02009E28
	mov r7, #0x15
	lsl r7, r7, #0x4
	add r6, r7, #0x0
	mov r4, #0x0
	sub r6, #0x10
_0208846E:
	ldr r0, [r5, r7]
	bl FUN_02009448
	ldr r0, [r5, r6]
	bl FUN_02008E2C
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x4
	blo _0208846E
	pop {r3-r7, pc}

	thumb_func_start FUN_02088484
FUN_02088484: ; 0x02088484
	ldr r3, _0208848C ; =FUN_0201FDEC
	ldr r0, [r0, #0x10]
	bx r3
	nop
_0208848C: .word FUN_0201FDEC

	thumb_func_start FUN_02088490
FUN_02088490: ; 0x02088490
	push {r3-r7, lr}
	sub sp, #0x70
	str r1, [sp, #0x2c]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r5, r0, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x30]
	bl FUN_020887CC
	str r0, [sp, #0x3c]
	cmp r0, #0x0
	bge _020884B4
	bl ErrorHandling
	add sp, #0x70
	mov r0, #0x0
	pop {r3-r7, pc}
_020884B4:
	ldr r0, [r5, #0x0]
	mov r1, #0x8
	bl FUN_02016998
	str r0, [sp, #0x38]
	mov r1, #0x0
	mov r2, #0x8
	bl MI_CpuFill8
	ldr r1, [sp, #0x3c]
	ldr r0, [sp, #0x38]
	strh r1, [r0, #0x0]
	ldr r0, [sp, #0x94]
	cmp r0, #0x0
	bne _020884D6
	mov r6, #0x1
	b _020884D8
_020884D6:
	mov r6, #0x2
_020884D8:
	ldr r0, [sp, #0x3c]
	mov r1, #0x55
	lsl r1, r1, #0x2
	lsl r4, r0, #0x2
	ldr r0, [r5, r1]
	ldr r3, [sp, #0x2c]
	ldr r0, [r0, #0x0]
	sub r1, #0x10
	ldr r0, [r0, r4]
	mov r2, #0x58
	str r0, [sp, #0x34]
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x0]
	add r3, r3, #0x3
	str r0, [sp, #0x4]
	ldr r0, [r5, r1]
	ldr r1, [sp, #0x34]
	bl FUN_02009168
	mov r0, #0x55
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, r4]
	bl FUN_02009DE0
	ldr r0, [r5, #0x0]
	mov r1, #0x10
	bl FUN_02016998
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x8
	bl FUN_02016998
	str r0, [r4, #0x8]
	ldr r0, [r5, #0x0]
	mov r1, #0x24
	bl FUN_02016998
	ldr r1, [r4, #0x8]
	mov r3, #0xe
	str r0, [r1, #0x0]
	ldr r0, [r4, #0x8]
	lsl r3, r3, #0xc
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	str r0, [r4, #0x4]
	mov r0, #0x0
	str r3, [sp, #0x0]
	mvn r0, r0
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	add r0, sp, #0x78
	ldrb r0, [r0, #0x14]
	str r0, [sp, #0x10]
	mov r0, #0x5
	lsl r0, r0, #0x6
	ldr r2, [r5, r0]
	str r2, [sp, #0x14]
	add r2, r0, #0x4
	ldr r2, [r5, r2]
	str r2, [sp, #0x18]
	add r2, r0, #0x0
	add r2, #0x8
	ldr r2, [r5, r2]
	add r0, #0xc
	str r2, [sp, #0x1c]
	ldr r0, [r5, r0]
	str r0, [sp, #0x20]
	str r1, [sp, #0x24]
	str r1, [sp, #0x28]
	ldr r2, [sp, #0x3c]
	ldr r0, [r4, #0x4]
	add r1, r3, #0x0
	add r2, r2, r3
	bl FUN_02008AA4
	ldr r0, [r5, #0x10]
	cmp r7, #0x0
	str r0, [sp, #0x40]
	ldr r0, [r4, #0x4]
	str r0, [sp, #0x44]
	beq _02088596
	lsl r0, r7, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _020885A4
_02088596:
	lsl r0, r7, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_020885A4:
	bl _ffix
	str r0, [sp, #0x48]
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	beq _020885C2
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _020885D0
_020885C2:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_020885D0:
	bl _ffix
	str r0, [sp, #0x4c]
	add r0, sp, #0x78
	ldrh r0, [r0, #0x10]
	cmp r0, #0x0
	beq _020885F0
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _020885FE
_020885F0:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_020885FE:
	bl _ffix
	str r0, [sp, #0x50]
	cmp r6, #0x2
	bne _02088612
	mov r0, #0x3
	ldr r1, [sp, #0x4c]
	lsl r0, r0, #0x12
	add r0, r1, r0
	str r0, [sp, #0x4c]
_02088612:
	mov r0, #0x1
	lsl r0, r0, #0xc
	str r0, [sp, #0x54]
	str r0, [sp, #0x58]
	str r0, [sp, #0x5c]
	mov r1, #0x0
	add r0, sp, #0x40
	strh r1, [r0, #0x20]
	add r0, sp, #0x78
	ldrb r0, [r0, #0x18]
	str r6, [sp, #0x68]
	str r0, [sp, #0x64]
	ldr r0, [r5, #0x0]
	str r0, [sp, #0x6c]
	add r0, sp, #0x40
	bl FUN_0201FE94
	str r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02088652
	mov r1, #0x0
	bl FUN_02020130
	ldr r0, [sp, #0x34]
	add r1, r6, #0x0
	bl FUN_02009E88
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02020248
	b _02088656
_02088652:
	bl ErrorHandling
_02088656:
	ldr r0, [sp, #0x38]
	str r4, [r0, #0x4]
	add sp, #0x70
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02088660
FUN_02088660: ; 0x02088660
	push {r4, lr}
	sub sp, #0x8
	add r3, r2, #0x0
	mov r2, #0x55
	lsl r2, r2, #0x2
	ldr r4, [r0, r2]
	ldrh r1, [r1, #0x0]
	ldr r4, [r4, #0x0]
	sub r2, #0x10
	lsl r1, r1, #0x2
	ldr r4, [r4, r1]
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r1, [r0, #0x0]
	add r3, r3, #0x3
	str r1, [sp, #0x4]
	ldr r0, [r0, r2]
	add r1, r4, #0x0
	mov r2, #0x58
	bl FUN_02009168
	add r0, r4, #0x0
	bl FUN_02009DE0
	add sp, #0x8
	pop {r4, pc}

	thumb_func_start FUN_02088694
FUN_02088694: ; 0x02088694
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x4]
	bl FUN_0200C3DC
	mov r1, #0x16
	ldrh r2, [r4, #0x0]
	lsl r1, r1, #0x4
	ldr r3, [r5, r1]
	mov r0, #0x0
	lsl r2, r2, #0x2
	strb r0, [r3, r2]
	ldrh r2, [r4, #0x0]
	ldr r3, [r5, r1]
	lsl r2, r2, #0x2
	add r2, r3, r2
	strh r0, [r2, #0x2]
	ldr r2, [r5, r1]
	ldrh r1, [r4, #0x0]
	lsl r1, r1, #0x2
	add r1, r2, r1
	strb r0, [r1, #0x1]
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020886CC
FUN_020886CC: ; 0x020886CC
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	mov r0, #0x15
	lsl r0, r0, #0x4
	ldr r4, [r5, r0]
	mov r1, #0xe
	lsl r1, r1, #0xc
	str r1, [sp, #0x0]
	ldrh r1, [r5, #0xe]
	mov r2, #0x0
	sub r0, #0x10
	str r1, [sp, #0x4]
	ldr r1, [r5, #0x0]
	add r3, r2, #0x0
	str r1, [sp, #0x8]
	ldr r0, [r5, r0]
	mov r1, #0x58
	bl FUN_02008F34
	ldr r1, [r4, #0x0]
	str r0, [r1, #0x0]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02088704
	bl ErrorHandling
_02088704:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	beq _02088728
	cmp r0, #0x1
	beq _02088714
	cmp r0, #0x2
	beq _0208871E
	b _02088728
_02088714:
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_02009B04
	b _02088730
_0208871E:
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_02009B78
	b _02088730
_02088728:
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_02009A50
_02088730:
	mov r4, #0x0
	add r6, r5, #0x0
_02088734:
	mov r0, #0x56
	lsl r0, r0, #0x2
	ldr r7, [r6, r0]
	mov r0, #0xe
	lsl r0, r0, #0xc
	str r0, [sp, #0x0]
	add r0, r4, #0x2
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	mov r1, #0x58
	str r0, [sp, #0x8]
	mov r0, #0x52
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	add r2, r4, #0x1
	mov r3, #0x0
	bl FUN_020090AC
	ldr r1, [r7, #0x0]
	str r0, [r1, #0x0]
	ldr r0, [r7, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02088768
	bl ErrorHandling
_02088768:
	add r4, r4, #0x1
	add r6, r6, #0x4
	cmp r4, #0x2
	blt _02088734
	mov r0, #0x55
	lsl r0, r0, #0x2
	ldr r6, [r5, r0]
	ldrh r0, [r5, #0xa]
	mov r7, #0x0
	cmp r0, #0x0
	ble _020887C6
	add r4, r7, #0x0
_02088780:
	mov r0, #0xe
	lsl r0, r0, #0xc
	add r0, r7, r0
	str r0, [sp, #0x0]
	ldrh r0, [r5, #0xe]
	mov r1, #0x58
	mov r2, #0x4
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x0]
	mov r3, #0x0
	str r0, [sp, #0xc]
	mov r0, #0x51
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl FUN_02008FEC
	ldr r1, [r6, #0x0]
	str r0, [r1, r4]
	ldr r0, [r6, #0x0]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	bne _020887B4
	bl ErrorHandling
_020887B4:
	ldr r0, [r6, #0x0]
	ldr r0, [r0, r4]
	bl FUN_02009CF0
	ldrh r0, [r5, #0xa]
	add r7, r7, #0x1
	add r4, r4, #0x4
	cmp r7, r0
	blt _02088780
_020887C6:
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020887CC
FUN_020887CC: ; 0x020887CC
	push {r3-r6}
	ldrh r5, [r0, #0xa]
	mov r3, #0x0
	cmp r5, #0x0
	bls _0208880A
	mov r2, #0x16
	lsl r2, r2, #0x4
	ldr r4, [r0, r2]
_020887DC:
	lsl r2, r3, #0x2
	ldrb r6, [r4, r2]
	cmp r6, #0x0
	bne _02088800
	add r4, r4, r2
	strh r3, [r4, #0x2]
	mov r4, #0x16
	lsl r4, r4, #0x4
	ldr r5, [r0, r4]
	add r5, r5, r2
	strb r1, [r5, #0x1]
	ldr r0, [r0, r4]
	mov r1, #0x1
	strb r1, [r0, r2]
	lsl r0, r3, #0x10
	asr r0, r0, #0x10
	pop {r3-r6}
	bx lr
_02088800:
	add r2, r3, #0x1
	lsl r2, r2, #0x10
	lsr r3, r2, #0x10
	cmp r3, r5
	blo _020887DC
_0208880A:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r6}
	bx lr
	.balign 4
