	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start FUN_02029A84
FUN_02029A84: ; 0x02029A84
	mov r0, #0x62
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_02029A8C
FUN_02029A8C: ; 0x02029A8C
	push {r4-r6, lr}
	mov r2, #0x62
	add r4, r0, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x4
	bl memset
	add r0, r4, #0x0
	bl FUN_02029ACC
	add r5, r0, #0x0
	mov r4, #0x0
	mov r6, #0x8c
_02029AA6:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02029AD8
	add r4, r4, #0x1
	cmp r4, #0x8
	blt _02029AA6
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02029ABC
FUN_02029ABC: ; 0x02029ABC
	ldr r3, _02029AC4 ; =SavArray_get
	mov r1, #0x13
	bx r3
	nop
_02029AC4: .word SavArray_get

	thumb_func_start FUN_02029AC8
FUN_02029AC8: ; 0x02029AC8
	add r0, #0x20
	bx lr

	thumb_func_start FUN_02029ACC
FUN_02029ACC: ; 0x02029ACC
	bx lr
	.balign 4

	thumb_func_start FUN_02029AD0
FUN_02029AD0: ; 0x02029AD0
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02029AD8
FUN_02029AD8: ; 0x02029AD8
	lsl r0, r0, #0x2
	str r1, [r2, r0]
	bx lr
	.balign 4
