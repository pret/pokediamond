	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global UNK_021C59BC
UNK_021C59BC: ; 0x021C59BC
	.space 0xc

	.text

	thumb_func_start FUN_02022294
FUN_02022294: ; 0x02022294
	ldr r0, _020222A4 ; =UNK_021C59BC
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	str r1, [r0, #0x8]
	ldr r0, _020222A8 ; =UNK_021C59BC
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020222A4: .word UNK_021C59BC
_020222A8: .word UNK_021C59BC

	thumb_func_start FUN_020222AC
FUN_020222AC: ; 0x020222AC
	ldr r3, _020222B0 ; =G3X_ResetMtxStack
	bx r3
	.balign 4
_020222B0: .word G3X_ResetMtxStack

	thumb_func_start FUN_020222B4
FUN_020222B4: ; 0x020222B4
	ldr r2, _020222C0 ; =UNK_021C59BC
	str r0, [r2, #0x4]
	str r1, [r2, #0x8]
	mov r0, #0x1
	str r0, [r2, #0x0]
	bx lr
	.balign 4
_020222C0: .word UNK_021C59BC

	thumb_func_start FUN_020222C4
FUN_020222C4: ; 0x020222C4
	ldr r0, _020222E0 ; =UNK_021C59BC
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _020222DC
	ldr r1, [r0, #0x8]
	ldr r2, [r0, #0x4]
	lsl r1, r1, #0x1
	orr r2, r1
	ldr r1, _020222E4 ; =0x04000540
	str r2, [r1, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
_020222DC:
	bx lr
	nop
_020222E0: .word UNK_021C59BC
_020222E4: .word 0x04000540
