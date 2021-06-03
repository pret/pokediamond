	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start FUN_020222E8
FUN_020222E8: ; 0x020222E8
	mov r0, #0x5
	lsl r0, r0, #0x18
	bx lr
	.balign 4

	thumb_func_start FUN_020222F0
FUN_020222F0: ; 0x020222F0
	mov r0, #0x2
	lsl r0, r0, #0x8
	bx lr
	.balign 4

	thumb_func_start FUN_020222F8
FUN_020222F8: ; 0x020222F8
	ldr r0, _020222FC ; =0x05000400
	bx lr
	.balign 4
_020222FC: .word 0x05000400

	thumb_func_start FUN_02022300
FUN_02022300: ; 0x02022300
	mov r0, #0x2
	lsl r0, r0, #0x8
	bx lr
	.balign 4

	thumb_func_start FUN_02022308
FUN_02022308: ; 0x02022308
	ldr r0, _0202230C ; =0x05000200
	bx lr
	.balign 4
_0202230C: .word 0x05000200

	thumb_func_start FUN_02022310
FUN_02022310: ; 0x02022310
	ldr r0, _02022314 ; =0x05000600
	bx lr
	.balign 4
_02022314: .word 0x05000600
