	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start copysign
copysign: ; 0x020E8214
	stmdb sp!, {r0-r3}
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0xc]
	bic r1, r1, #0x80000000
	and r0, r0, #0x80000000
	orr r1, r1, r0
	ldr r0, [sp, #0x0]
	str r1, [sp, #0x4]
	add sp, sp, #0x10
	bx lr
	arm_func_end copysign
