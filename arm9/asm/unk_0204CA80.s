    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020F48E5
	.extern UNK_020F48D8
	.extern UNK_020F48D9
	.extern UNK_020F48CC
	.extern UNK_020F48D7
	.extern UNK_020F48DC
	.extern UNK_020F48E4
	.extern UNK_020F48E0
	.extern UNK_020F48CD

	.text

	thumb_func_start FUN_0204CA80
FUN_0204CA80: ; 0x0204CA80
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CA8C ; =UNK_020F48CC
	ldrb r0, [r0, r1]
	bx lr
	nop
_0204CA8C: .word UNK_020F48CC

	thumb_func_start FUN_0204CA90
FUN_0204CA90: ; 0x0204CA90
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CA9C ; =UNK_020F48CD
	ldrb r0, [r0, r1]
	bx lr
	nop
_0204CA9C: .word UNK_020F48CD

	thumb_func_start FUN_0204CAA0
FUN_0204CAA0: ; 0x0204CAA0
	mov r1, #0x1c
	ldr r2, _0204CAAC ; =UNK_020F48CC
	mul r1, r0
	add r0, r2, r1
	add r0, r0, #0x2
	bx lr
	.balign 4
_0204CAAC: .word UNK_020F48CC

	thumb_func_start FUN_0204CAB0
FUN_0204CAB0: ; 0x0204CAB0
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CABC ; =UNK_020F48D7
	ldrb r0, [r0, r1]
	bx lr
	nop
_0204CABC: .word UNK_020F48D7

	thumb_func_start FUN_0204CAC0
FUN_0204CAC0: ; 0x0204CAC0
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CACC ; =UNK_020F48D8
	ldrb r0, [r0, r1]
	bx lr
	nop
_0204CACC: .word UNK_020F48D8

	thumb_func_start FUN_0204CAD0
FUN_0204CAD0: ; 0x0204CAD0
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CADC ; =UNK_020F48D9
	ldrb r0, [r0, r1]
	bx lr
	nop
_0204CADC: .word UNK_020F48D9

	thumb_func_start FUN_0204CAE0
FUN_0204CAE0: ; 0x0204CAE0
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CAEC ; =UNK_020F48DC
	ldr r0, [r0, r1]
	bx lr
	nop
_0204CAEC: .word UNK_020F48DC

	thumb_func_start FUN_0204CAF0
FUN_0204CAF0: ; 0x0204CAF0
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CAFC ; =UNK_020F48E0
	ldr r0, [r0, r1]
	bx lr
	nop
_0204CAFC: .word UNK_020F48E0

	thumb_func_start FUN_0204CB00
FUN_0204CB00: ; 0x0204CB00
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CB0C ; =UNK_020F48E4
	ldrb r0, [r0, r1]
	bx lr
	nop
_0204CB0C: .word UNK_020F48E4

	thumb_func_start FUN_0204CB10
FUN_0204CB10: ; 0x0204CB10
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CB1C ; =UNK_020F48E5
	ldrb r0, [r0, r1]
	bx lr
	nop
_0204CB1C: .word UNK_020F48E5
