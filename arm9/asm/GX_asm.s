	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start GX_SendFifo48B
GX_SendFifo48B: ; 0x020C9BE8
	ldmia r0!, {r2-r3,r12}
	stmia r1, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1, {r2-r3,r12}
	bx lr
