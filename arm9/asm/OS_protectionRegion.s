    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_SetDPermissionsForProtectionRegion
OS_SetDPermissionsForProtectionRegion: ; 0x020CC9D8
	mrc p15, 0x0, r2, c5, c0, 0x2
	bic r2, r2, r0
	orr r2, r2, r1
	mcr p15, 0x0, r2, c5, c0, 0x2
	bx lr

	arm_func_start OS_SetProtectionRegion1
OS_SetProtectionRegion1: ; 0x020CC9EC
	mcr p15, 0x0, r0, c6, c1, 0x0
	bx lr

	arm_func_start OS_SetProtectionRegion2
OS_SetProtectionRegion2: ; 0x020CC9F4
	mcr p15, 0x0, r0, c6, c2, 0x0
	bx lr
