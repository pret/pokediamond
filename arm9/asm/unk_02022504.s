	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02022504
FUN_02022504: ; 0x02022504
	ldr r3, _0202250C ; =FUN_02022610
	mov r1, #0x1b
	bx r3
	nop
_0202250C: .word FUN_02022610

	thumb_func_start FUN_02022510
FUN_02022510: ; 0x02022510
	ldr r3, _02022518 ; =FUN_02022610
	mov r1, #0x23
	bx r3
	nop
_02022518: .word FUN_02022610

	thumb_func_start FUN_0202251C
FUN_0202251C: ; 0x0202251C
	ldr r3, _02022524 ; =FUN_02022610
	mov r1, #0x1f
	bx r3
	nop
_02022524: .word FUN_02022610

	thumb_func_start FUN_02022528
FUN_02022528: ; 0x02022528
	ldr r3, _02022530 ; =FUN_02022610
	mov r1, #0x20
	bx r3
	nop
_02022530: .word FUN_02022610

	thumb_func_start FUN_02022534
FUN_02022534: ; 0x02022534
	push {r3, lr}
	add r3, r2, #0x0
	mov r2, #0x0
	bl FUN_02023408
	pop {r3, pc}

	thumb_func_start FUN_02022540
FUN_02022540: ; 0x02022540
	ldr r3, _02022548 ; =FUN_020232BC
	add r2, r1, #0x0
	mov r1, #0x0
	bx r3
	.balign 4
_02022548: .word FUN_020232BC
