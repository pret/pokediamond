	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start PXI_Init
PXI_Init: ; 0x037FB5B0
	ldr	ip, _037FB5B8	; =PXI_InitFifo
	bx	ip
_037FB5B8:	.word	PXI_InitFifo
