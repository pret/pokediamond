	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start ErrorHandling
ErrorHandling: ; 0x02020C2C
	push {r3, lr}
	bl FUN_02031810
	cmp r0, #0x0
	beq _02020C42
	bl OS_GetProcMode
	cmp r0, #0x12
	beq _02020C42
	bl PrintErrorMessageAndReset
_02020C42:
	pop {r3, pc}
