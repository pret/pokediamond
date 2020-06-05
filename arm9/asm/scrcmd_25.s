    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start ScrCmd_DebugPrintWork
ScrCmd_DebugPrintWork: ; 0x02046010
	push {r3, lr}
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_DebugPrintFlag
ScrCmd_DebugPrintFlag: ; 0x0204601C
	push {r3, lr}
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_DebugPrintWorkStationed
ScrCmd_DebugPrintWorkStationed: ; 0x02046028
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_DebugPrintFlagStationed
ScrCmd_DebugPrintFlagStationed: ; 0x0204602C
	mov r0, #0x0
	bx lr
