	.include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020F2BB0
	.extern UNK_020F2B9C

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
