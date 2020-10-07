	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0202ABBC
FUN_0202ABBC: ; 0x0202ABBC
	ldr r3, _0202ABC4 ; =SavArray_get
	mov r1, #0x1a
	bx r3
	nop
_0202ABC4: .word SavArray_get

	thumb_func_start FUN_0202ABC8
FUN_0202ABC8: ; 0x0202ABC8
	mov r0, #0xf4
	bx lr

	thumb_func_start FUN_0202ABCC
FUN_0202ABCC: ; 0x0202ABCC
	ldr r3, _0202ABD8 ; =MIi_CpuClearFast
	add r1, r0, #0x0
	mov r0, #0x0
	mov r2, #0xf4
	bx r3
	nop
_0202ABD8: .word MIi_CpuClearFast

	thumb_func_start FUN_0202ABDC
FUN_0202ABDC: ; 0x0202ABDC
	add r0, #0xec
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0202ABE4
FUN_0202ABE4: ; 0x0202ABE4
	add r0, #0xec
	strh r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0202ABEC
FUN_0202ABEC: ; 0x0202ABEC
	ldr r3, _0202ABF4 ; =MIi_CpuCopyFast
	mov r2, #0xec
	bx r3
	nop
_0202ABF4: .word MIi_CpuCopyFast

	thumb_func_start FUN_0202ABF8
FUN_0202ABF8: ; 0x0202ABF8
	ldr r3, _0202AC04 ; =MIi_CpuCopyFast
	add r2, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	mov r2, #0xec
	bx r3
	.balign 4
_0202AC04: .word MIi_CpuCopyFast

	thumb_func_start FUN_0202AC08
FUN_0202AC08: ; 0x0202AC08
	add r0, #0xf0
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0202AC10
FUN_0202AC10: ; 0x0202AC10
	add r0, #0xf0
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0202AC18
FUN_0202AC18: ; 0x0202AC18
	add r0, #0xee
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4
