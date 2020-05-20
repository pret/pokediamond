    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0204CA80
FUN_0204CA80: ; 0x0204CA80
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CA8C ; =0x020F48CC
	ldrb r0, [r0, r1]
	bx lr
	nop
_0204CA8C: .word 0x020F48CC

	thumb_func_start FUN_0204CA90
FUN_0204CA90: ; 0x0204CA90
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CA9C ; =0x020F48CD
	ldrb r0, [r0, r1]
	bx lr
	nop
_0204CA9C: .word 0x020F48CD

	thumb_func_start FUN_0204CAA0
FUN_0204CAA0: ; 0x0204CAA0
	mov r1, #0x1c
	ldr r2, _0204CAAC ; =0x020F48CC
	mul r1, r0
	add r0, r2, r1
	add r0, r0, #0x2
	bx lr
	.balign 4
_0204CAAC: .word 0x020F48CC

	thumb_func_start FUN_0204CAB0
FUN_0204CAB0: ; 0x0204CAB0
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CABC ; =0x020F48D7
	ldrb r0, [r0, r1]
	bx lr
	nop
_0204CABC: .word 0x020F48D7

	thumb_func_start FUN_0204CAC0
FUN_0204CAC0: ; 0x0204CAC0
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CACC ; =0x020F48D8
	ldrb r0, [r0, r1]
	bx lr
	nop
_0204CACC: .word 0x020F48D8

	thumb_func_start FUN_0204CAD0
FUN_0204CAD0: ; 0x0204CAD0
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CADC ; =0x020F48D9
	ldrb r0, [r0, r1]
	bx lr
	nop
_0204CADC: .word 0x020F48D9

	thumb_func_start FUN_0204CAE0
FUN_0204CAE0: ; 0x0204CAE0
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CAEC ; =0x020F48DC
	ldr r0, [r0, r1]
	bx lr
	nop
_0204CAEC: .word 0x020F48DC

	thumb_func_start FUN_0204CAF0
FUN_0204CAF0: ; 0x0204CAF0
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CAFC ; =0x020F48E0
	ldr r0, [r0, r1]
	bx lr
	nop
_0204CAFC: .word 0x020F48E0

	thumb_func_start FUN_0204CB00
FUN_0204CB00: ; 0x0204CB00
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CB0C ; =0x020F48E4
	ldrb r0, [r0, r1]
	bx lr
	nop
_0204CB0C: .word 0x020F48E4

	thumb_func_start FUN_0204CB10
FUN_0204CB10: ; 0x0204CB10
	mov r1, #0x1c
	mul r1, r0
	ldr r0, _0204CB1C ; =0x020F48E5
	ldrb r0, [r0, r1]
	bx lr
	nop
_0204CB1C: .word 0x020F48E5
