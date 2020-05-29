    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0208A300
FUN_0208A300: ; 0x0208A300
	push {r3, lr}
	mov r1, #0x8
	bl AllocFromHeap
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	strb r1, [r0, #0x4]
	strb r1, [r0, #0x5]
	strb r1, [r0, #0x6]
	strb r1, [r0, #0x7]
	mov r1, #0x2
	str r1, [r0, #0x4]
	pop {r3, pc}

	thumb_func_start FUN_0208A320
FUN_0208A320: ; 0x0208A320
	ldr r3, _0208A324 ; =FreeToHeap
	bx r3
	.balign 4
_0208A324: .word FreeToHeap

	thumb_func_start FUN_0208A328
FUN_0208A328: ; 0x0208A328
	ldr r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0208A32C
FUN_0208A32C: ; 0x0208A32C
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0208A330
FUN_0208A330: ; 0x0208A330
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_0208A334
FUN_0208A334: ; 0x0208A334
	str r1, [r0, #0x4]
	bx lr
