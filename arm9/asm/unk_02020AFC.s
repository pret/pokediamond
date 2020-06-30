	.include "asm/macros.inc"
    .include "global.inc"

	.section .bss

	.global UNK_021C59B0
UNK_021C59B0: ; 0x021C59B0
	.space 0xc

	.text

	thumb_func_start FUN_02020AFC
FUN_02020AFC: ; 0x02020AFC
	push {r3, lr}
	ldr r0, _02020B24 ; =UNK_021C59B0
	mov r2, #0x0
	str r2, [r0, #0x4]
	str r2, [r0, #0x8]
	ldr r1, _02020B28 ; =0x0400010E
	str r2, [r0, #0x0]
	strh r2, [r1, #0x0]
	sub r0, r1, #0x2
	strh r2, [r0, #0x0]
	mov r0, #0xc1
	strh r0, [r1, #0x0]
	ldr r1, _02020B2C ; =FUN_02020B30
	mov r0, #0x40
	bl OS_SetIrqFunction
	mov r0, #0x40
	bl OS_EnableIrqMask
	pop {r3, pc}
	.balign 4
_02020B24: .word UNK_021C59B0
_02020B28: .word 0x0400010E
_02020B2C: .word FUN_02020B30

	thumb_func_start FUN_02020B30
FUN_02020B30: ; 0x02020B30
	ldr r0, _02020B68 ; =UNK_021C59B0
	mov r3, #0x0
	ldr r1, [r0, #0x4]
	ldr r2, [r0, #0x8]
	add r1, r1, #0x1
	adc r2, r3
	str r1, [r0, #0x4]
	str r2, [r0, #0x8]
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02020B54
	ldr r2, _02020B6C ; =0x0400010E
	strh r3, [r2, #0x0]
	sub r1, r2, #0x2
	strh r3, [r1, #0x0]
	mov r1, #0xc1
	strh r1, [r2, #0x0]
	str r3, [r0, #0x0]
_02020B54:
	ldr r3, _02020B70 ; =OS_IRQTable
	ldr r1, _02020B74 ; =0x00003FF8
	mov r0, #0x40
	ldr r2, [r3, r1]
	orr r2, r0
	str r2, [r3, r1]
	ldr r3, _02020B78 ; =OS_SetIrqFunction
	ldr r1, _02020B7C ; =FUN_02020B30
	bx r3
	nop
_02020B68: .word UNK_021C59B0
_02020B6C: .word 0x0400010E
_02020B70: .word OS_IRQTable
_02020B74: .word 0x00003FF8
_02020B78: .word OS_SetIrqFunction
_02020B7C: .word FUN_02020B30

	thumb_func_start FUN_02020B80
FUN_02020B80: ; 0x02020B80
	push {r4-r5, lr}
	sub sp, #0xc
	bl OS_DisableInterrupts
	ldr r1, _02020BE4 ; =0x0400010C
	add r3, sp, #0x0
	ldrh r1, [r1, #0x0]
	ldr r2, _02020BE8 ; =0x0000FFFF
	strh r1, [r3, #0x0]
	ldr r1, _02020BEC ; =UNK_021C59B0
	ldr r5, [r1, #0x4]
	ldr r4, [r1, #0x8]
	mov r1, #0x0
	mvn r1, r1
	and r1, r5
	str r1, [sp, #0x4]
	and r2, r4
	ldr r1, _02020BF0 ; =0x04000214
	str r2, [sp, #0x8]
	ldr r2, [r1, #0x0]
	mov r1, #0x40
	tst r2, r1
	beq _02020BC4
	ldrh r2, [r3, #0x0]
	lsl r1, r1, #0x9
	tst r1, r2
	bne _02020BC4
	ldr r2, [sp, #0x4]
	mov r1, #0x0
	ldr r3, [sp, #0x8]
	add r2, r2, #0x1
	adc r3, r1
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
_02020BC4:
	bl OS_RestoreInterrupts
	ldr r2, [sp, #0x4]
	ldr r1, [sp, #0x8]
	lsr r0, r2, #0x10
	lsl r1, r1, #0x10
	orr r1, r0
	add r0, sp, #0x0
	lsl r3, r2, #0x10
	ldrh r2, [r0, #0x0]
	asr r0, r2, #0x1f
	orr r1, r0
	add r0, r3, #0x0
	orr r0, r2
	add sp, #0xc
	pop {r4-r5, pc}
	.balign 4
_02020BE4: .word 0x0400010C
_02020BE8: .word 0x0000FFFF
_02020BEC: .word UNK_021C59B0
_02020BF0: .word 0x04000214

	thumb_func_start FUN_02020BF4
FUN_02020BF4: ; 0x02020BF4
	ldr r3, _02020BF8 ; =FUN_02020B80
	bx r3
	.balign 4
_02020BF8: .word FUN_02020B80

	thumb_func_start FUN_02020BFC
FUN_02020BFC: ; 0x02020BFC
	push {r3, lr}
	lsr r2, r0, #0x1a
	lsl r1, r1, #0x6
	orr r1, r2
	ldr r2, _02020C10 ; =0x000082EA
	lsl r0, r0, #0x6
	mov r3, #0x0
	bl _ll_udiv
	pop {r3, pc}
	.balign 4
_02020C10: .word 0x000082EA

	thumb_func_start FUN_02020C14
FUN_02020C14: ; 0x02020C14
	push {r3, lr}
	lsr r2, r0, #0x1a
	lsl r1, r1, #0x6
	orr r1, r2
	ldr r2, _02020C28 ; =0x01FF6210
	lsl r0, r0, #0x6
	mov r3, #0x0
	bl _ll_udiv
	pop {r3, pc}
	.balign 4
_02020C28: .word 0x01FF6210
