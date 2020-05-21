    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020FB788
	.extern UNK_020FB78E
	.extern UNK_020FB792
	.extern UNK_020FB78C
	.extern UNK_020FB790

	.text

	thumb_func_start FUN_0207FC5C
FUN_0207FC5C: ; 0x0207FC5C
	cmp r1, #0x4
	bhi _0207FCA8
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0207FC6C: ; jump table (using 16-bit offset)
	.short _0207FC76 - _0207FC6C - 2; case 0
	.short _0207FC80 - _0207FC6C - 2; case 1
	.short _0207FC8A - _0207FC6C - 2; case 2
	.short _0207FC94 - _0207FC6C - 2; case 3
	.short _0207FC9E - _0207FC6C - 2; case 4
_0207FC76:
	mov r1, #0xc
	mul r1, r0
	ldr r0, _0207FCAC ; =UNK_020FB788
	ldr r0, [r0, r1]
	bx lr
_0207FC80:
	mov r1, #0xc
	mul r1, r0
	ldr r0, _0207FCB0 ; =UNK_020FB78C
	ldrh r0, [r0, r1]
	bx lr
_0207FC8A:
	mov r1, #0xc
	mul r1, r0
	ldr r0, _0207FCB4 ; =UNK_020FB78E
	ldrh r0, [r0, r1]
	bx lr
_0207FC94:
	mov r1, #0xc
	mul r1, r0
	ldr r0, _0207FCB8 ; =UNK_020FB790
	ldrh r0, [r0, r1]
	bx lr
_0207FC9E:
	mov r1, #0xc
	mul r1, r0
	ldr r0, _0207FCBC ; =UNK_020FB792
	ldrh r0, [r0, r1]
	bx lr
_0207FCA8:
	mov r0, #0x0
	bx lr
	.balign 4
_0207FCAC: .word UNK_020FB788
_0207FCB0: .word UNK_020FB78C
_0207FCB4: .word UNK_020FB78E
_0207FCB8: .word UNK_020FB790
_0207FCBC: .word UNK_020FB792

	thumb_func_start FUN_0207FCC0
FUN_0207FCC0: ; 0x0207FCC0
	mov r2, #0xc
	mul r2, r1
	ldr r1, _0207FCDC ; =UNK_020FB792
	ldrh r2, [r1, r2]
	mov r1, #0x2
	lsl r1, r1, #0xe
	tst r1, r2
	beq _0207FCD8
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	ldrb r2, [r0, r1]
	add r2, #0x92
_0207FCD8:
	add r0, r2, #0x0
	bx lr
	.balign 4
_0207FCDC: .word UNK_020FB792

	thumb_func_start FUN_0207FCE0
FUN_0207FCE0: ; 0x0207FCE0
	mov r1, #0xc
	mul r1, r0
	ldr r0, _0207FCFC ; =UNK_020FB792
	ldrh r1, [r0, r1]
	mov r0, #0x2
	lsl r0, r0, #0xe
	tst r0, r1
	beq _0207FCF6
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	bx lr
_0207FCF6:
	mov r0, #0xff
	bx lr
	nop
_0207FCFC: .word UNK_020FB792
