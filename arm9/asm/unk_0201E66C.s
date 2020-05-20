	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0201E66C
FUN_0201E66C: ; 0x0201E66C
	push {r4, lr}
	add r4, r0, #0x0
	bl GX_ResetBankForBG
	bl GX_ResetBankForBGExtPltt
	bl GX_ResetBankForSubBG
	bl FUN_020C6034
	bl GX_ResetBankForOBJ
	bl GX_ResetBankForOBJExtPltt
	bl FUN_020C605C
	bl GX_ResetBankForSubOBJ
	bl GX_ResetBankForTex
	bl GX_ResetBankForTexPltt
	ldr r0, [r4, #0x0]
	bl GX_SetBankForBG
	ldr r0, [r4, #0x4]
	bl GX_SetBankForBGExtPltt
	ldr r0, [r4, #0x8]
	bl GX_SetBankForSubBG
	ldr r0, [r4, #0xc]
	bl GX_SetBankForSubBGExtPltt
	ldr r0, [r4, #0x10]
	bl GX_SetBankForOBJ
	ldr r0, [r4, #0x14]
	bl GX_SetBankForOBJExtPltt
	ldr r0, [r4, #0x18]
	bl GX_SetBankForSubOBJ
	ldr r0, [r4, #0x1c]
	bl GX_SetBankForSubOBJExtPltt
	ldr r0, [r4, #0x20]
	bl GX_SetBankForTex
	ldr r0, [r4, #0x24]
	bl GX_SetBankForTexPltt
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201E6D8
FUN_0201E6D8: ; 0x0201E6D8
	ldr r0, _0201E6E0 ; =0x021C599C
	mov r1, #0x0
	str r1, [r0, #0x4]
	bx lr
	.balign 4
_0201E6E0: .word 0x021C599C

	thumb_func_start FUN_0201E6E4
FUN_0201E6E4: ; 0x0201E6E4
	cmp r1, #0x1
	bne _0201E6F2
	ldr r1, _0201E718 ; =0x021C599C
	ldr r1, [r1, #0x4]
	tst r1, r0
	beq _0201E6FA
	bx lr
_0201E6F2:
	ldr r1, _0201E718 ; =0x021C599C
	ldr r1, [r1, #0x4]
	tst r1, r0
	beq _0201E714
_0201E6FA:
	ldr r1, _0201E718 ; =0x021C599C
	ldr r2, [r1, #0x4]
	add r3, r2, #0x0
	eor r3, r0
	mov r2, #0x1
	lsl r2, r2, #0x1a
	str r3, [r1, #0x4]
	ldr r1, [r2, #0x0]
	ldr r0, _0201E71C ; =0xFFFFE0FF
	and r1, r0
	lsl r0, r3, #0x8
	orr r0, r1
	str r0, [r2, #0x0]
_0201E714:
	bx lr
	nop
_0201E718: .word 0x021C599C
_0201E71C: .word 0xFFFFE0FF

	thumb_func_start FUN_0201E720
FUN_0201E720: ; 0x0201E720
	ldr r1, _0201E738 ; =0x021C599C
	mov r3, #0x1
	str r0, [r1, #0x4]
	lsl r3, r3, #0x1a
	ldr r2, [r3, #0x0]
	ldr r1, _0201E73C ; =0xFFFFE0FF
	lsl r0, r0, #0x8
	and r1, r2
	orr r0, r1
	str r0, [r3, #0x0]
	bx lr
	nop
_0201E738: .word 0x021C599C
_0201E73C: .word 0xFFFFE0FF

	thumb_func_start FUN_0201E740
FUN_0201E740: ; 0x0201E740
	ldr r0, _0201E748 ; =0x021C599C
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_0201E748: .word 0x021C599C

	thumb_func_start FUN_0201E74C
FUN_0201E74C: ; 0x0201E74C
	cmp r1, #0x1
	bne _0201E75A
	ldr r1, _0201E77C ; =0x021C599C
	ldr r1, [r1, #0x0]
	tst r1, r0
	beq _0201E762
	bx lr
_0201E75A:
	ldr r1, _0201E77C ; =0x021C599C
	ldr r1, [r1, #0x0]
	tst r1, r0
	beq _0201E77A
_0201E762:
	ldr r1, _0201E77C ; =0x021C599C
	ldr r2, [r1, #0x0]
	add r3, r2, #0x0
	eor r3, r0
	ldr r2, _0201E780 ; =0x04001000
	str r3, [r1, #0x0]
	ldr r1, [r2, #0x0]
	ldr r0, _0201E784 ; =0xFFFFE0FF
	and r1, r0
	lsl r0, r3, #0x8
	orr r0, r1
	str r0, [r2, #0x0]
_0201E77A:
	bx lr
	.balign 4
_0201E77C: .word 0x021C599C
_0201E780: .word 0x04001000
_0201E784: .word 0xFFFFE0FF

	thumb_func_start FUN_0201E788
FUN_0201E788: ; 0x0201E788
	push {r3, lr}
	bl GX_DispOn
	ldr r2, _0201E79C ; =0x04001000
	mov r0, #0x1
	ldr r1, [r2, #0x0]
	lsl r0, r0, #0x10
	orr r0, r1
	str r0, [r2, #0x0]
	pop {r3, pc}
	.balign 4
_0201E79C: .word 0x04001000

	thumb_func_start FUN_0201E7A0
FUN_0201E7A0: ; 0x0201E7A0
	ldr r0, _0201E7C0 ; =0x021C4918
	ldr r2, _0201E7C4 ; =0x04000304
	ldrb r0, [r0, #0x5]
	cmp r0, #0x0
	bne _0201E7B4
	ldrh r1, [r2, #0x0]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2, #0x0]
	bx lr
_0201E7B4:
	ldrh r1, [r2, #0x0]
	ldr r0, _0201E7C8 ; =0xFFFF7FFF
	and r0, r1
	strh r0, [r2, #0x0]
	bx lr
	nop
_0201E7C0: .word 0x021C4918
_0201E7C4: .word 0x04000304
_0201E7C8: .word 0xFFFF7FFF

	thumb_func_start FUN_0201E7CC
FUN_0201E7CC: ; 0x0201E7CC
	ldr r0, _0201E7D4 ; =0x021C599C
	ldr r0, [r0, #0x4]
	bx lr
	nop
_0201E7D4: .word 0x021C599C
