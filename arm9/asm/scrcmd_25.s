    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02046010
FUN_02046010: ; 0x02046010
	push {r3, lr}
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0204601C
FUN_0204601C: ; 0x0204601C
	push {r3, lr}
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02046028
FUN_02046028: ; 0x02046028
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0204602C
FUN_0204602C: ; 0x0204602C
	mov r0, #0x0
	bx lr
