	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start sub_0201B4E8
sub_0201B4E8: ; 0x0201B4E8
	str r0, [r1, #0x0]
	add r0, r0, #0x4
	str r0, [r1, #0x8]
	str r0, [r1, #0x4]
	mov r0, #0x0
	str r0, [r1, #0xc]
	str r0, [r1, #0x10]
	str r0, [r1, #0x14]
	bx lr
	.balign 4

	thumb_func_start sub_0201B4FC
sub_0201B4FC: ; 0x0201B4FC
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldrh r0, [r5, #0x0]
	mov r7, #0x0
	cmp r0, #0x0
	ble _0201B52A
	add r4, r7, #0x0
	add r6, r7, #0x0
_0201B50C:
	ldr r1, [r5, #0x24]
	add r0, r5, #0x0
	add r1, r1, r4
	bl sub_0201B4E8
	ldr r0, [r5, #0x24]
	add r7, r7, #0x1
	add r1, r0, r4
	ldr r0, [r5, #0x20]
	add r4, #0x1c
	str r1, [r0, r6]
	ldrh r0, [r5, #0x0]
	add r6, r6, #0x4
	cmp r7, r0
	blt _0201B50C
_0201B52A:
	mov r0, #0x0
	strh r0, [r5, #0x2]
	pop {r3-r7, pc}

	thumb_func_start sub_0201B530
sub_0201B530: ; 0x0201B530
	ldrh r3, [r0, #0x2]
	ldrh r1, [r0, #0x0]
	cmp r3, r1
	bne _0201B53C
	mov r0, #0x0
	bx lr
_0201B53C:
	ldr r2, [r0, #0x20]
	lsl r1, r3, #0x2
	ldr r2, [r2, r1]
	add r1, r3, #0x1
	strh r1, [r0, #0x2]
	add r0, r2, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_0201B54C
sub_0201B54C: ; 0x0201B54C
	ldrh r2, [r0, #0x2]
	cmp r2, #0x0
	bne _0201B556
	mov r0, #0x0
	bx lr
_0201B556:
	str r0, [r1, #0x0]
	add r2, r0, #0x4
	str r2, [r1, #0x8]
	str r2, [r1, #0x4]
	mov r2, #0x0
	str r2, [r1, #0xc]
	str r2, [r1, #0x10]
	str r2, [r1, #0x14]
	ldrh r2, [r0, #0x2]
	sub r2, r2, #0x1
	strh r2, [r0, #0x2]
	ldr r2, [r0, #0x20]
	ldrh r0, [r0, #0x2]
	lsl r0, r0, #0x2
	str r1, [r2, r0]
	mov r0, #0x1
	bx lr

	thumb_func_start sub_0201B578
sub_0201B578: ; 0x0201B578
	lsl r0, r0, #0x5
	add r0, #0x34
	bx lr
	.balign 4

	thumb_func_start sub_0201B580
sub_0201B580: ; 0x0201B580
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bne _0201B58C
	bl GF_AssertFail
_0201B58C:
	add r1, r4, #0x0
	add r1, #0x34
	lsl r0, r5, #0x2
	str r1, [r4, #0x20]
	add r0, r1, r0
	str r0, [r4, #0x24]
	strh r5, [r4, #0x0]
	mov r0, #0x0
	strh r0, [r4, #0x2]
	str r0, [r4, #0x28]
	add r0, r4, #0x0
	bl sub_0201B5AC
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0201B5AC
sub_0201B5AC: ; 0x0201B5AC
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_0201B4FC
	str r4, [r4, #0x4]
	add r0, r4, #0x4
	str r0, [r4, #0xc]
	str r0, [r4, #0x8]
	mov r0, #0x0
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	ldr r0, [r4, #0xc]
	str r0, [r4, #0x2c]
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0201B5CC
sub_0201B5CC: ; 0x0201B5CC
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x28]
	cmp r0, #0x0
	bne _0201B608
	ldr r1, [r5, #0xc]
	add r4, r5, #0x4
	str r1, [r5, #0x2c]
	cmp r1, r4
	beq _0201B604
	mov r6, #0x0
_0201B5E2:
	ldr r0, [r1, #0x8]
	str r0, [r5, #0x30]
	ldr r0, [r5, #0x2c]
	ldr r1, [r0, #0x18]
	cmp r1, #0x0
	bne _0201B5FA
	ldr r2, [r0, #0x14]
	cmp r2, #0x0
	beq _0201B5FC
	ldr r1, [r0, #0x10]
	blx r2
	b _0201B5FC
_0201B5FA:
	str r6, [r0, #0x18]
_0201B5FC:
	ldr r1, [r5, #0x30]
	str r1, [r5, #0x2c]
	cmp r1, r4
	bne _0201B5E2
_0201B604:
	mov r0, #0x0
	str r0, [r1, #0x14]
_0201B608:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_0201B60C
sub_0201B60C: ; 0x0201B60C
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r5, #0x1
	str r5, [r4, #0x28]
	bl sub_0201B620
	mov r1, #0x0
	str r1, [r4, #0x28]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0201B620
sub_0201B620: ; 0x0201B620
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	add r4, r3, #0x0
	bl sub_0201B530
	cmp r0, #0x0
	bne _0201B636
	mov r0, #0x0
	pop {r3-r7, pc}
_0201B636:
	str r4, [r0, #0xc]
	str r7, [r0, #0x10]
	str r6, [r0, #0x14]
	ldr r2, [r5, #0x2c]
	ldr r1, [r2, #0x14]
	cmp r1, #0x0
	beq _0201B656
	ldr r1, [r2, #0xc]
	cmp r1, r4
	bhi _0201B650
	mov r1, #0x1
	str r1, [r0, #0x18]
	b _0201B65A
_0201B650:
	mov r1, #0x0
	str r1, [r0, #0x18]
	b _0201B65A
_0201B656:
	mov r1, #0x0
	str r1, [r0, #0x18]
_0201B65A:
	ldr r3, [r5, #0xc]
	add r2, r5, #0x4
	cmp r3, r2
	beq _0201B686
	ldr r4, [r0, #0xc]
_0201B664:
	ldr r1, [r3, #0xc]
	cmp r1, r4
	bls _0201B680
	ldr r1, [r3, #0x4]
	str r1, [r0, #0x4]
	str r3, [r0, #0x8]
	ldr r1, [r3, #0x4]
	str r0, [r1, #0x8]
	str r0, [r3, #0x4]
	ldr r1, [r5, #0x30]
	cmp r3, r1
	bne _0201B69E
	str r0, [r5, #0x30]
	pop {r3-r7, pc}
_0201B680:
	ldr r3, [r3, #0x8]
	cmp r3, r2
	bne _0201B664
_0201B686:
	ldr r2, [r5, #0x30]
	add r1, r5, #0x4
	cmp r2, r1
	bne _0201B690
	str r0, [r5, #0x30]
_0201B690:
	ldr r1, [r5, #0x8]
	str r1, [r0, #0x4]
	add r1, r5, #0x4
	str r1, [r0, #0x8]
	ldr r1, [r5, #0x8]
	str r0, [r1, #0x8]
	str r0, [r5, #0x8]
_0201B69E:
	pop {r3-r7, pc}

	thumb_func_start sub_0201B6A0
sub_0201B6A0: ; 0x0201B6A0
	add r1, r0, #0x0
	ldr r2, [r1, #0x0]
	ldr r0, [r2, #0x30]
	cmp r0, r1
	bne _0201B6AE
	ldr r0, [r1, #0x8]
	str r0, [r2, #0x30]
_0201B6AE:
	ldr r2, [r1, #0x8]
	ldr r0, [r1, #0x4]
	ldr r3, _0201B6C0 ; =0x0201B54D
	str r2, [r0, #0x8]
	ldr r2, [r1, #0x4]
	ldr r0, [r1, #0x8]
	str r2, [r0, #0x4]
	ldr r0, [r1, #0x0]
	bx r3
	.balign 4
_0201B6C0: .word sub_0201B54C

	thumb_func_start sub_0201B6C4
sub_0201B6C4: ; 0x0201B6C4
	str r1, [r0, #0x14]
	bx lr

	thumb_func_start sub_0201B6C8
sub_0201B6C8: ; 0x0201B6C8
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start sub_0201B6CC
sub_0201B6CC: ; 0x0201B6CC
	ldr r0, [r0, #0xc]
	bx lr
