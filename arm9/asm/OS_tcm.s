    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_GetDTCMAddress
OS_GetDTCMAddress: ; 0x020CC9A4
	mrc p15, 0x0, r0, c9, c1, 0x0
	ldr r1, _020CC9B4 ; =0xFFFFF000
	and r0, r0, r1
	bx lr
	.balign 4
_020CC9B4: .word 0xFFFFF000
