	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start wmemcpy
wmemcpy: ; 0x020E5068
	ldr ip, _020E5074 ; =memcpy
	mov r2, r2, lsl #0x1
	bx r12
	.balign 4
_020E5074: .word memcpy
    arm_func_end wmemcpy

	arm_func_start wmemchr
wmemchr:
	cmp r2, #0x0
	beq _020E5098
_020E5080:
	ldrh r3, [r0, #0x0]
	cmp r3, r1
	bxeq lr
	add r0, r0, #0x2
	subs r2, r2, #0x1
	bne _020E5080
_020E5098:
	mov r0, #0x0
	bx lr
    arm_func_end wmemchr
