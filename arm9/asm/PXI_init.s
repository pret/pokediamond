	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start PXI_Init
PXI_Init: ; 0x020CFBB0
	ldr ip, _020CFBB8 ; =PXI_InitFifo
	bx r12
	.balign 4
_020CFBB8: .word PXI_InitFifo
