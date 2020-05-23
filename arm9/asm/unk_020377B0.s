	.include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020F2B9C
UNK_020F2B9C: ; 0x020F2B9C
	.byte 0x9F, 0x01, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x04, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020F2BB0
UNK_020F2BB0: ; 0x020F2BB0
	.byte 0x9B, 0x01, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x74, 0x00, 0x00, 0x00, 0x76, 0x03, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_020377B0
FUN_020377B0: ; 0x020377B0
	ldr r2, _020377C4 ; =UNK_020F2B9C
	add r3, r0, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr
	nop
_020377C4: .word UNK_020F2B9C

	thumb_func_start FUN_020377C8
FUN_020377C8: ; 0x020377C8
	ldr r2, _020377DC ; =UNK_020F2BB0
	add r3, r0, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr
	nop
_020377DC: .word UNK_020F2BB0

	thumb_func_start FUN_020377E0
FUN_020377E0: ; 0x020377E0
	push {r3, lr}
	bl FUN_02034E30
	bl FUN_02034DC0
	bl FUN_020377B0
	pop {r3, pc}
