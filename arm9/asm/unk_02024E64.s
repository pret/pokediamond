	.include "asm/macros.inc"
    .include "global.inc"

	.text




	thumb_func_start FUN_02024EE8
FUN_02024EE8: ; 0x02024EE8
	ldr r1, _02024EF0 ; =0x00000724
	add r0, r0, r1
	bx lr
	nop
_02024EF0: .word 0x00000724

	thumb_func_start FUN_02024EF4
FUN_02024EF4: ; 0x02024EF4
	add r2, r0, #0x0
	add r0, r1, #0x0
	ldr r1, _02024F04 ; =0x00000724
	ldr r3, _02024F08 ; =CopyStringToU16Array
	add r1, r2, r1
	mov r2, #0x8
	bx r3
	nop
_02024F04: .word 0x00000724
_02024F08: .word CopyStringToU16Array

	thumb_func_start FUN_02024F0C
FUN_02024F0C: ; 0x02024F0C
	ldr r1, _02024F14 ; =0x00000734
	add r0, r0, r1
	bx lr
	nop
_02024F14: .word 0x00000734

	thumb_func_start FUN_02024F18
FUN_02024F18: ; 0x02024F18
	add r2, r0, #0x0
	add r0, r1, #0x0
	ldr r1, _02024F28 ; =0x00000734
	ldr r3, _02024F2C ; =CopyStringToU16Array
	add r1, r2, r1
	mov r2, #0xb
	bx r3
	nop
_02024F28: .word 0x00000734
_02024F2C: .word CopyStringToU16Array
