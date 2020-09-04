    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start ScrCmd_unk_575
ScrCmd_unk_575: ; 0x02046010
	push {r3, lr}
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_576
ScrCmd_unk_576: ; 0x0204601C
	push {r3, lr}
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_577
ScrCmd_unk_577: ; 0x02046028
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_unk_578
ScrCmd_unk_578: ; 0x0204602C
	mov r0, #0x0
	bx lr
