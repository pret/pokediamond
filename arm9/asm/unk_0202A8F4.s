	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0202A8F4
FUN_0202A8F4: ; 0x0202A8F4
	mov r0, #0xe
	bx lr

	thumb_func_start FUN_0202A8F8
FUN_0202A8F8: ; 0x0202A8F8
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	strb r1, [r0, #0x4]
	strb r1, [r0, #0x5]
	strb r1, [r0, #0x6]
	strb r1, [r0, #0x7]
	strb r1, [r0, #0x8]
	strb r1, [r0, #0x9]
	strb r1, [r0, #0xa]
	strb r1, [r0, #0xb]
	strb r1, [r0, #0xc]
	strb r1, [r0, #0xd]
	bx lr

	thumb_func_start FUN_0202A918
FUN_0202A918: ; 0x0202A918
	ldr r3, _0202A920 ; =SavArray_get
	mov r1, #0x18
	bx r3
	nop
_0202A920: .word SavArray_get
