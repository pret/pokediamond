    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020F4528
	.extern UNK_020F452A

	.text

	thumb_func_start FUN_020453A0
FUN_020453A0: ; 0x020453A0
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	ldr r1, _020453EC ; =UNK_020F4528
	lsl r2, r4, #0x2
	ldrh r1, [r1, r2]
	strh r1, [r6, #0x0]
	ldr r1, _020453F0 ; =UNK_020F452A
	ldrh r1, [r1, r2]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_020453EC: .word UNK_020F4528
_020453F0: .word UNK_020F452A
