    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start GX_InitGXState
GX_InitGXState: ; 0x020C5CAC
	ldr r0, _020C5D14 ; =0x021D33C4
	mov r3, #0x0
	ldr r2, _020C5D18 ; =0x04000240
	strh r3, [r0, #0x0]
	strh r3, [r0, #0x2]
	strh r3, [r0, #0x4]
	strh r3, [r0, #0x6]
	strh r3, [r0, #0x8]
	strh r3, [r0, #0xa]
	strh r3, [r0, #0xc]
	strh r3, [r0, #0xe]
	strh r3, [r0, #0x10]
	strh r3, [r0, #0x12]
	strh r3, [r0, #0x14]
	strh r3, [r0, #0x16]
	strh r3, [r0, #0x18]
	ldr r1, _020C5D1C ; =0x04000244
	str r3, [r2, #0x0]
	ldr r0, _020C5D20 ; =0x04000245
	strb r3, [r1, #0x0]
	ldr r1, _020C5D24 ; =0x04000246
	strb r3, [r0, #0x0]
	ldr r0, _020C5D28 ; =0x04000248
	strb r3, [r1, #0x0]
	strh r3, [r0, #0x0]
	bx lr
	.balign 4
_020C5D14: .word 0x021D33C4
_020C5D18: .word 0x04000240
_020C5D1C: .word 0x04000244
_020C5D20: .word 0x04000245
_020C5D24: .word 0x04000246
_020C5D28: .word 0x04000248
