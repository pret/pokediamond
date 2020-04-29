	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start OS_EnableProtectionUnit
OS_EnableProtectionUnit: ; 0x020CC9B8
	mrc p15, 0x0, r0, c1, c0, 0x0
	orr r0, r0, #0x1
	mcr p15, 0x0, r0, c1, c0, 0x0
	bx lr

	arm_func_start OS_DisableProtectionUnit
OS_DisableProtectionUnit: ; 0x020CC9C8
	mrc p15, 0x0, r0, c1, c0, 0x0
	bic r0, r0, #0x1
	mcr p15, 0x0, r0, c1, c0, 0x0
	bx lr
