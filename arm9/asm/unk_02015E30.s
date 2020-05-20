    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02015E30
FUN_02015E30: ; 0x02015E30
	ldr r0, _02015E38 ; =0x021C4898
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_02015E38: .word 0x021C4898

	thumb_func_start FUN_02015E3C
FUN_02015E3C: ; 0x02015E3C
	push {r3, lr}
	ldr r1, _02015E5C ; =0x021C4898
	mov r2, #0x1
	str r2, [r1, #0x0]
	mov r2, #0x0
	str r2, [r1, #0x10]
	str r2, [r1, #0x14]
	str r2, [r1, #0x8]
	str r2, [r1, #0xc]
	str r0, [r1, #0x4]
	bl FUN_02020BF4
	ldr r2, _02015E5C ; =0x021C4898
	str r0, [r2, #0x18]
	str r1, [r2, #0x1c]
	pop {r3, pc}
	.balign 4
_02015E5C: .word 0x021C4898

	thumb_func_start FUN_02015E60
FUN_02015E60: ; 0x02015E60
	push {r3-r5, lr}
	ldr r0, _02015E9C ; =0x021C4898
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02015E9A
	bl FUN_02020BF4
	ldr r2, _02015E9C ; =0x021C4898
	ldr r3, [r2, #0x18]
	ldr r2, [r2, #0x1c]
	sub r0, r0, r3
	sbc r1, r2
	bl FUN_02020C14
	add r5, r1, #0x0
	ldr r1, _02015E9C ; =0x021C4898
	add r4, r0, #0x0
	ldr r3, [r1, #0x8]
	ldr r2, [r1, #0xc]
	sub r0, r3, r4
	sbc r2, r5
	bhs _02015E9A
	ldr r0, [r1, #0x4]
	sub r1, r4, r3
	bl FUN_02029E54
	ldr r0, _02015E9C ; =0x021C4898
	str r4, [r0, #0x8]
	str r5, [r0, #0xc]
_02015E9A:
	pop {r3-r5, pc}
	.balign 4
_02015E9C: .word 0x021C4898
