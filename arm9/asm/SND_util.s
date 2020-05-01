	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start SND_CalcChannelVolume
SND_CalcChannelVolume: ; 0x020CF6F4
	ldr r1, _020CF75C ; =0xFFFFFD2D
	cmp r0, r1
	movlt r0, r1
	blt _020CF70C
	cmp r0, #0x0
	movgt r0, #0x0
_020CF70C:
	ldr r1, _020CF760 ; =0x000002D3
	ldr r2, _020CF764 ; =0x02103CAC
	add r3, r0, r1
	mvn r1, #0xef
	cmp r0, r1
	ldrb r2, [r2, r3]
	movlt r0, #0x3
	blt _020CF74C
	mvn r1, #0x77
	cmp r0, r1
	movlt r0, #0x2
	blt _020CF74C
	mvn r1, #0x3b
	cmp r0, r1
	movlt r0, #0x1
	movge r0, #0x0
_020CF74C:
	orr r0, r2, r0, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bx lr
	.balign 4
_020CF75C: .word 0xFFFFFD2D
_020CF760: .word 0x000002D3
_020CF764: .word 0x02103CAC
