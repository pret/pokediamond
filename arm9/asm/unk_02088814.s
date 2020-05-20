    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02088814
FUN_02088814: ; 0x02088814
	mov r0, #0x3
	bx lr

	thumb_func_start FUN_02088818
FUN_02088818: ; 0x02088818
	bx lr
	.balign 4

	thumb_func_start FUN_0208881C
FUN_0208881C: ; 0x0208881C
	ldr r3, _02088828 ; =FUN_0202D8D0
	add r2, r0, #0x0
	ldr r0, _0208882C ; =0x020FD1C4
	mov r1, #0x6c
	bx r3
	nop
_02088828: .word FUN_0202D8D0
_0208882C: .word 0x020FD1C4

	thumb_func_start FUN_02088830
FUN_02088830: ; 0x02088830
	ldr r0, _02088834 ; =0x0000066C
	bx lr
	.balign 4
_02088834: .word 0x0000066C

	thumb_func_start FUN_02088838
FUN_02088838: ; 0x02088838
	mov r0, #0x2f
	lsl r0, r0, #0x6
	bx lr
	.balign 4

	thumb_func_start FUN_02088840
FUN_02088840: ; 0x02088840
	mov r0, #0x3f
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_02088848
FUN_02088848: ; 0x02088848
	mov r0, #0xa
	bx lr

	thumb_func_start FUN_0208884C
FUN_0208884C: ; 0x0208884C
	mov r0, #0x32
	bx lr

	thumb_func_start FUN_02088850
FUN_02088850: ; 0x02088850
	mov r0, #0x4
	bx lr

	thumb_func_start FUN_02088854
FUN_02088854: ; 0x02088854
	mov r0, #0x4
	bx lr
