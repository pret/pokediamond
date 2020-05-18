	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0201CBEC
FUN_0201CBEC: ; 0x0201CBEC
	push {r3, lr}
	sub r0, r0, r2
	sub r2, r1, r3
	add r1, r0, #0x0
	mul r1, r0
	add r0, r2, #0x0
	mul r0, r2
	add r0, r1, r0
	lsl r0, r0, #0xc
	bl FX_Sqrt
	asr r0, r0, #0xc
	pop {r3, pc}
	.balign 4
