    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02015CC0
FUN_02015CC0: ; 0x02015CC0
	ldr r3, _02015CDC ; =0x020ED72C
	mov r2, #0x0
_02015CC4:
	ldrh r1, [r3, #0x2]
	cmp r0, r1
	bhs _02015CCE
	add r0, r2, #0x0
	bx lr
_02015CCE:
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, #0x2
	blt _02015CC4
	add r0, r2, #0x0
	bx lr
	nop
_02015CDC: .word 0x020ED72C

	thumb_func_start FUN_02015CE0
FUN_02015CE0: ; 0x02015CE0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02015CC0
	lsl r1, r0, #0x1
	ldr r0, _02015CF4 ; =0x020ED72C
	ldrh r0, [r0, r1]
	sub r0, r4, r0
	pop {r4, pc}
	nop
_02015CF4: .word 0x020ED72C

	thumb_func_start FUN_02015CF8
FUN_02015CF8: ; 0x02015CF8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x3
	blt _02015D06
	bl ErrorHandling
_02015D06:
	ldr r0, _02015D10 ; =0x020ED72C
	lsl r1, r5, #0x1
	ldrh r0, [r0, r1]
	add r0, r4, r0
	pop {r3-r5, pc}
	.balign 4
_02015D10: .word 0x020ED72C
