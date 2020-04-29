    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start G2S_GetBG3CharPtr
G2S_GetBG3CharPtr: ; 0x020C6F60
	ldr r1, _020C6FA8 ; =0x04001000
	ldr r0, _020C6FAC ; =0x0400100E
	ldr r1, [r1, #0x0]
	ldrh r2, [r0, #0x0]
	and r0, r1, #0x7
	cmp r0, #0x3
	blt _020C6F8C
	cmp r0, #0x6
	bge _020C6FA0
	ands r0, r2, #0x80
	bne _020C6FA0
_020C6F8C:
	and r0, r2, #0x3c
	mov r0, r0, lsr #0x2
	mov r0, r0, lsl #0xe
	add r0, r0, #0x6200000
	bx lr
_020C6FA0:
	mov r0, #0x0
	bx lr
	.balign 4
_020C6FA8: .word 0x04001000
_020C6FAC: .word 0x0400100E

	arm_func_start G2_GetBG3CharPtr
G2_GetBG3CharPtr: ; 0x020C6FB0
	mov r0, #0x4000000
	ldr r1, [r0, #0x0]
	ldr r0, _020C700C ; =0x0400000E
	and r1, r1, #0x7
	cmp r1, #0x3
	ldrh r2, [r0, #0x0]
	blt _020C6FDC
	cmp r1, #0x6
	bge _020C7004
	ands r0, r2, #0x80
	bne _020C7004
_020C6FDC:
	mov r0, #0x4000000
	ldr r1, [r0, #0x0]
	and r0, r2, #0x3c
	and r1, r1, #0x7000000
	mov r1, r1, lsr #0x18
	mov r1, r1, lsl #0x10
	add r1, r1, #0x6000000
	mov r0, r0, lsr #0x2
	add r0, r1, r0, lsl #0xe
	bx lr
_020C7004:
	mov r0, #0x0
	bx lr
	.balign 4
_020C700C: .word 0x0400000E

	arm_func_start G2S_GetBG2CharPtr
G2S_GetBG2CharPtr: ; 0x020C7010
	ldr r1, _020C7050 ; =0x04001000
	ldr r0, _020C7054 ; =0x0400100C
	ldr r1, [r1, #0x0]
	ldrh r2, [r0, #0x0]
	and r0, r1, #0x7
	cmp r0, #0x5
	blt _020C7034
	ands r0, r2, #0x80
	bne _020C7048
_020C7034:
	and r0, r2, #0x3c
	mov r0, r0, lsr #0x2
	mov r0, r0, lsl #0xe
	add r0, r0, #0x6200000
	bx lr
_020C7048:
	mov r0, #0x0
	bx lr
	.balign 4
_020C7050: .word 0x04001000
_020C7054: .word 0x0400100C

	arm_func_start G2_GetBG2CharPtr
G2_GetBG2CharPtr: ; 0x020C7058
	mov r0, #0x4000000
	ldr r1, [r0, #0x0]
	ldr r0, _020C70AC ; =0x0400000C
	and r1, r1, #0x7
	cmp r1, #0x5
	ldrh r2, [r0, #0x0]
	blt _020C707C
	ands r0, r2, #0x80
	bne _020C70A4
_020C707C:
	mov r0, #0x4000000
	ldr r1, [r0, #0x0]
	and r0, r2, #0x3c
	and r1, r1, #0x7000000
	mov r1, r1, lsr #0x18
	mov r1, r1, lsl #0x10
	add r1, r1, #0x6000000
	mov r0, r0, lsr #0x2
	add r0, r1, r0, lsl #0xe
	bx lr
_020C70A4:
	mov r0, #0x0
	bx lr
	.balign 4
_020C70AC: .word 0x0400000C

	arm_func_start G2S_GetBG1CharPtr
G2S_GetBG1CharPtr: ; 0x020C70B0
	ldr r0, _020C70CC ; =0x0400100A
	ldrh r0, [r0, #0x0]
	and r0, r0, #0x3c
	mov r0, r0, asr #0x2
	mov r0, r0, lsl #0xe
	add r0, r0, #0x6200000
	bx lr
	.balign 4
_020C70CC: .word 0x0400100A

	arm_func_start G2_GetBG1CharPtr
G2_GetBG1CharPtr: ; 0x020C70D0
	ldr r1, _020C7100 ; =0x0400000A
	mov r0, #0x4000000
	ldrh r1, [r1, #0x0]
	ldr r0, [r0, #0x0]
	and r0, r0, #0x7000000
	mov r0, r0, lsr #0x18
	and r1, r1, #0x3c
	mov r0, r0, lsl #0x10
	mov r1, r1, asr #0x2
	add r0, r0, #0x6000000
	add r0, r0, r1, lsl #0xe
	bx lr
	.balign 4
_020C7100: .word 0x0400000A

	arm_func_start G2S_GetBG0CharPtr
G2S_GetBG0CharPtr: ; 0x020C7104
	ldr r0, _020C7120 ; =0x04001008
	ldrh r0, [r0, #0x0]
	and r0, r0, #0x3c
	mov r0, r0, asr #0x2
	mov r0, r0, lsl #0xe
	add r0, r0, #0x6200000
	bx lr
	.balign 4
_020C7120: .word 0x04001008

	arm_func_start G2_GetBG0CharPtr
G2_GetBG0CharPtr: ; 0x020C7124
	ldr r1, _020C7154 ; =0x04000008
	mov r0, #0x4000000
	ldrh r1, [r1, #0x0]
	ldr r0, [r0, #0x0]
	and r0, r0, #0x7000000
	mov r0, r0, lsr #0x18
	and r1, r1, #0x3c
	mov r0, r0, lsl #0x10
	mov r1, r1, asr #0x2
	add r0, r0, #0x6000000
	add r0, r0, r1, lsl #0xe
	bx lr
	.balign 4
_020C7154: .word 0x04000008

	arm_func_start G2S_GetBG3ScrPtr
G2S_GetBG3ScrPtr: ; 0x020C7158
	ldr r1, _020C71D0 ; =0x04001000
	ldr r0, _020C71D4 ; =0x0400100E
	ldr r1, [r1, #0x0]
	ldrh r2, [r0, #0x0]
	and r3, r1, #0x7
	cmp r3, #0x6
	and r0, r2, #0x1f00
	mov r1, r0, lsr #0x8
	addls pc, pc, r3, lsl #0x2
	b _020C71C8
_020C7180: ; 0x020C7180
	b _020C719C
_020C7184: ; 0x020C7184
	b _020C719C
_020C7188: ; 0x020C7188
	b _020C719C
_020C718C: ; 0x020C718C
	b _020C71A8
_020C7190: ; 0x020C7190
	b _020C71A8
_020C7194: ; 0x020C7194
	b _020C71A8
_020C7198: ; 0x020C7198
	b _020C71C0
_020C719C:
	mov r0, r1, lsl #0xb
	add r0, r0, #0x6200000
	bx lr
_020C71A8:
	ands r0, r2, #0x80
	movne r0, r1, lsl #0xe
	addne r0, r0, #0x6200000
	moveq r0, r1, lsl #0xb
	addeq r0, r0, #0x6200000
	bx lr
_020C71C0:
	mov r0, #0x0
	bx lr
_020C71C8:
	mov r0, #0x0
	bx lr
	.balign 4
_020C71D0: .word 0x04001000
_020C71D4: .word 0x0400100E

	arm_func_start G2_GetBG3ScrPtr
G2_GetBG3ScrPtr: ; 0x020C71D8
	ldr r0, _020C7260 ; =0x0400000E
	mov r2, #0x4000000
	ldr r1, [r2, #0x0]
	ldrh r3, [r0, #0x0]
	ldr r0, [r2, #0x0]
	and r12, r1, #0x7
	and r0, r0, #0x38000000
	mov r1, r0, lsr #0x1b
	and r0, r3, #0x1f00
	mov r2, r1, lsl #0x10
	cmp r12, #0x6
	mov r1, r0, lsr #0x8
	addls pc, pc, r12, lsl #0x2
	b _020C7258
_020C7210:
	b _020C722C
_020C7214:
	b _020C722C
_020C7218:
	b _020C722C
_020C721C:
	b _020C7238
_020C7220:
	b _020C7238
_020C7224:
	b _020C7238
_020C7228:
	b _020C7250
_020C722C:
	add r0, r2, #0x6000000
	add r0, r0, r1, lsl #0xb
	bx lr
_020C7238:
	ands r0, r3, #0x80
	movne r0, r1, lsl #0xe
	addne r0, r0, #0x6000000
	addeq r0, r2, #0x6000000
	addeq r0, r0, r1, lsl #0xb
	bx lr
_020C7250:
	mov r0, #0x0
	bx lr
_020C7258:
	mov r0, #0x0
	bx lr
	.balign 4
_020C7260: .word 0x0400000E

	arm_func_start G2S_GetBG2ScrPtr
G2S_GetBG2ScrPtr: ; 0x020C7264
	ldr r1, _020C72DC ; =0x04001000
	ldr r0, _020C72E0 ; =0x0400100C
	ldr r1, [r1, #0x0]
	ldrh r2, [r0, #0x0]
	and r3, r1, #0x7
	cmp r3, #0x6
	and r0, r2, #0x1f00
	mov r1, r0, lsr #0x8
	addls pc, pc, r3, lsl #0x2
	b _020C72D4
_020C728C: ; 0x020C728C
	b _020C72A8
_020C7290: ; 0x020C7290
	b _020C72A8
_020C7294: ; 0x020C7294
	b _020C72A8
_020C7298: ; 0x020C7298
	b _020C72A8
_020C729C: ; 0x020C729C
	b _020C72A8
_020C72A0: ; 0x020C72A0
	b _020C72B4
_020C72A4: ; 0x020C72A4
	b _020C72CC
_020C72A8:
	mov r0, r1, lsl #0xb
	add r0, r0, #0x6200000
	bx lr
_020C72B4:
	ands r0, r2, #0x80
	movne r0, r1, lsl #0xe
	addne r0, r0, #0x6200000
	moveq r0, r1, lsl #0xb
	addeq r0, r0, #0x6200000
	bx lr
_020C72CC:
	mov r0, #0x0
	bx lr
_020C72D4:
	mov r0, #0x0
	bx lr
	.balign 4
_020C72DC: .word 0x04001000
_020C72E0: .word 0x0400100C

	arm_func_start G2_GetBG2ScrPtr
G2_GetBG2ScrPtr: ; 0x020C72E4
	ldr r0, _020C736C ; =0x0400000C
	mov r2, #0x4000000
	ldr r1, [r2, #0x0]
	ldrh r3, [r0, #0x0]
	ldr r0, [r2, #0x0]
	and r12, r1, #0x7
	and r0, r0, #0x38000000
	mov r1, r0, lsr #0x1b
	and r0, r3, #0x1f00
	mov r2, r1, lsl #0x10
	cmp r12, #0x6
	mov r1, r0, lsr #0x8
	addls pc, pc, r12, lsl #0x2
	b _020C7364
_020C731C:
	b _020C7338
_020C7320:
	b _020C7338
_020C7324:
	b _020C7338
_020C7328:
	b _020C7338
_020C732C:
	b _020C7338
_020C7330:
	b _020C7344
_020C7334:
	b _020C735C
_020C7338:
	add r0, r2, #0x6000000
	add r0, r0, r1, lsl #0xb
	bx lr
_020C7344:
	ands r0, r3, #0x80
	movne r0, r1, lsl #0xe
	addne r0, r0, #0x6000000
	addeq r0, r2, #0x6000000
	addeq r0, r0, r1, lsl #0xb
	bx lr
_020C735C:
	mov r0, #0x6000000
	bx lr
_020C7364:
	mov r0, #0x0
	bx lr
	.balign 4
_020C736C: .word 0x0400000C

	arm_func_start G2S_GetBG1ScrPtr
G2S_GetBG1ScrPtr: ; 0x020C7370
	ldr r0, _020C738C ; =0x0400100A
	ldrh r0, [r0, #0x0]
	and r0, r0, #0x1f00
	mov r0, r0, asr #0x8
	mov r0, r0, lsl #0xb
	add r0, r0, #0x6200000
	bx lr
	.balign 4
_020C738C: .word 0x0400100A

	arm_func_start G2_GetBG1ScrPtr
G2_GetBG1ScrPtr: ; 0x020C7390
	ldr r1, _020C73C0 ; =0x0400000A
	mov r0, #0x4000000
	ldrh r1, [r1, #0x0]
	ldr r0, [r0, #0x0]
	and r0, r0, #0x38000000
	mov r0, r0, lsr #0x1b
	and r1, r1, #0x1f00
	mov r0, r0, lsl #0x10
	mov r1, r1, asr #0x8
	add r0, r0, #0x6000000
	add r0, r0, r1, lsl #0xb
	bx lr
	.balign 4
_020C73C0: .word 0x0400000A

	arm_func_start G2S_GetBG0ScrPtr
G2S_GetBG0ScrPtr: ; 0x020C73C4
	ldr r0, _020C73E0 ; =0x04001008
	ldrh r0, [r0, #0x0]
	and r0, r0, #0x1f00
	mov r0, r0, asr #0x8
	mov r0, r0, lsl #0xb
	add r0, r0, #0x6200000
	bx lr
	.balign 4
_020C73E0: .word 0x04001008

	arm_func_start G2_GetBG0ScrPtr
G2_GetBG0ScrPtr: ; 0x020C73E4
	ldr r1, _020C7414 ; =0x04000008
	mov r0, #0x4000000
	ldrh r1, [r1, #0x0]
	ldr r0, [r0, #0x0]
	and r0, r0, #0x38000000
	mov r0, r0, lsr #0x1b
	and r1, r1, #0x1f00
	mov r0, r0, lsl #0x10
	mov r1, r1, asr #0x8
	add r0, r0, #0x6000000
	add r0, r0, r1, lsl #0xb
	bx lr
	.balign 4
_020C7414: .word 0x04000008
