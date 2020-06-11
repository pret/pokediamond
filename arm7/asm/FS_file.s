	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start FS_Init
FS_Init: ; 0x037FFF14
	ldr	ip, _037FFF1C	; =CARD_Init
	bx	ip
_037FFF1C:	.word	CARD_Init
