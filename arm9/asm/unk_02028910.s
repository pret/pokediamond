	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02028910
FUN_02028910: ; 0x02028910
	mov r1, #0x0
	strh r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02028918
FUN_02028918: ; 0x02028918
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0202892C ; =0x0000C350
	add r4, r1, #0x0
	cmp r4, r0
	bls _02028928
	bl ErrorHandling
_02028928:
	strh r4, [r5, #0x0]
	pop {r3-r5, pc}
	.balign 4
_0202892C: .word 0x0000C350

	thumb_func_start FUN_02028930
FUN_02028930: ; 0x02028930
	ldrh r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02028934
FUN_02028934: ; 0x02028934
	ldrh r3, [r0, #0x0]
	ldr r2, _02028950 ; =0x0000C350
	cmp r3, r2
	blo _02028940
	mov r0, #0x0
	bx lr
_02028940:
	add r1, r3, r1
	strh r1, [r0, #0x0]
	ldrh r1, [r0, #0x0]
	cmp r1, r2
	bls _0202894C
	strh r2, [r0, #0x0]
_0202894C:
	mov r0, #0x1
	bx lr
	.balign 4
_02028950: .word 0x0000C350

	thumb_func_start FUN_02028954
FUN_02028954: ; 0x02028954
	ldrh r0, [r0, #0x0]
	add r1, r1, r0
	ldr r0, _02028968 ; =0x0000C350
	cmp r1, r0
	bhi _02028962
	mov r0, #0x1
	bx lr
_02028962:
	mov r0, #0x0
	bx lr
	nop
_02028968: .word 0x0000C350

	thumb_func_start FUN_0202896C
FUN_0202896C: ; 0x0202896C
	ldrh r2, [r0, #0x0]
	cmp r2, r1
	bhs _02028976
	mov r0, #0x0
	bx lr
_02028976:
	sub r1, r2, r1
	strh r1, [r0, #0x0]
	mov r0, #0x1
	bx lr
	.balign 4
