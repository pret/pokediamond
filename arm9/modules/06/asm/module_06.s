	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD06_022396A0
MOD06_022396A0: ; 0x022396A0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, r5, #4
	add r4, r2, #0
	add r6, r3, #0
	str r1, [r5]
	bl FUN_0223972C
	mov r0, #0
	str r0, [r5, #0x38]
	str r4, [r5, #0x30]
	str r6, [r5, #0x34]
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start FUN_022396BC
FUN_022396BC: ; 0x022396BC
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x38]
	cmp r1, #5
	bhi _02239712
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022396D2: ; jump table
	.short _022396DE - _022396D2 - 2 ; case 0
	.short _022396EA - _022396D2 - 2 ; case 1
	.short _02239712 - _022396D2 - 2 ; case 2
	.short _022396FC - _022396D2 - 2 ; case 3
	.short _02239708 - _022396D2 - 2 ; case 4
	.short _02239712 - _022396D2 - 2 ; case 5
_022396DE:
	bl FUN_022397F4
	ldr r0, [r4, #0x38]
	add r0, r0, #1
	str r0, [r4, #0x38]
	pop {r4, pc}
_022396EA:
	ldr r0, [r4, #0x30]
	ldr r1, [r4, #0x34]
	bl FUN_0223987C
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x38]
	add r0, r0, #1
	str r0, [r4, #0x38]
	pop {r4, pc}
_022396FC:
	bl FUN_022398A8
	ldr r0, [r4, #0x38]
	add r0, r0, #1
	str r0, [r4, #0x38]
	pop {r4, pc}
_02239708:
	bl FUN_02239808
	ldr r0, [r4, #0x38]
	add r0, r0, #1
	str r0, [r4, #0x38]
_02239712:
	pop {r4, pc}

	thumb_func_start FUN_02239714
FUN_02239714: ; 0x02239714
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x38]
	cmp r0, #2
	beq _02239722
	bl ErrorHandling
_02239722:
	mov r0, #3
	str r0, [r4, #0x38]
	pop {r4, pc}

	thumb_func_start FUN_02239728
FUN_02239728: ; 0x02239728
	ldr r0, [r0, #0x38]
	bx lr

	thumb_func_start FUN_0223972C
FUN_0223972C: ; 0x0223972C
	push {r4, lr}
	add r4, r0, #0
	bl GX_GetBankForBGExtPltt_2
	str r0, [r4]
	bl GX_GetBankForBGExtPltt
	str r0, [r4, #4]
	bl GX_GetBankForSubBGExtPltt_2
	str r0, [r4, #8]
	bl GX_GetBankForSubBGExtPltt
	str r0, [r4, #0xc]
	bl GX_GetBankForOBJ
	str r0, [r4, #0x10]
	bl GX_GetBankForOBJExtPltt
	str r0, [r4, #0x14]
	bl GX_GetBankForSubOBJ
	str r0, [r4, #0x18]
	bl GX_GetBankForSubOBJExtPltt
	str r0, [r4, #0x1c]
	bl FUN_020C5D8C
	str r0, [r4, #0x20]
	bl GX_GetBankForTexPltt
	str r0, [r4, #0x24]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start FUN_02239770
FUN_02239770: ; 0x02239770
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _0223978C ; =0x0224F1F4
	add r3, sp, #0
	mov r2, #5
_0223977A:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0223977A
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_0223978C: .word 0x0224F1F4

	thumb_func_start FUN_02239790
FUN_02239790: ; 0x02239790
	push {r4, r5, lr}
	sub sp, #0x2c
	ldr r5, _022397EC ; =0x0224F180
	add r3, sp, #0x1c
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	ldr r5, _022397F0 ; =0x0224F1D8
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #3
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #3
	mov r1, #0x20
	mov r2, #0
	mov r3, #4
	bl FUN_02017F18
	add r0, r4, #0
	mov r1, #3
	bl FUN_02018744
	add sp, #0x2c
	pop {r4, r5, pc}
	nop
_022397EC: .word 0x0224F180
_022397F0: .word 0x0224F1D8

	thumb_func_start FUN_022397F4
FUN_022397F4: ; 0x022397F4
	ldr r3, _02239800 ; =FUN_0200CA98
	mov r2, #1
	add r1, r0, #0
	ldr r0, _02239804 ; =FUN_0223981C
	lsl r2, r2, #0xa
	bx r3
	.align 2, 0
_02239800: .word FUN_0200CA98
_02239804: .word FUN_0223981C

	thumb_func_start FUN_02239808
FUN_02239808: ; 0x02239808
	ldr r3, _02239814 ; =FUN_0200CA98
	mov r2, #1
	add r1, r0, #0
	ldr r0, _02239818 ; =FUN_02239840
	lsl r2, r2, #0xa
	bx r3
	.align 2, 0
_02239814: .word FUN_0200CA98
_02239818: .word FUN_02239840

	thumb_func_start FUN_0223981C
FUN_0223981C: ; 0x0223981C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	bl FUN_02239770
	ldr r0, [r4]
	ldr r0, [r0, #8]
	bl FUN_02239864
	ldr r0, [r4]
	ldr r0, [r0, #8]
	bl FUN_02239790
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start FUN_02239840
FUN_02239840: ; 0x02239840
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #4
	bl FUN_0201E66C
	ldr r0, [r4]
	ldr r0, [r0, #8]
	bl FUN_02239864
	ldr r0, [r4]
	ldr r0, [r0, #8]
	bl FUN_0223986C
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}

	thumb_func_start FUN_02239864
FUN_02239864: ; 0x02239864
	ldr r3, _02239868 ; =FUN_021D7A28
	bx r3
	.align 2, 0
_02239868: .word FUN_021D7A28 + 1 ; TODO: disassemble the module that defines this

	thumb_func_start FUN_0223986C
FUN_0223986C: ; 0x0223986C
	push {r3, lr}
	bl FUN_021D7A20
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	pop {r3, pc}

	thumb_func_start FUN_0223987C
FUN_0223987C: ; 0x0223987C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x2c
	ldr r6, _022398A4 ; =0x0224F21C
	add r3, r0, #0
	add r2, r1, #0
	add r5, sp, #0
	mov r4, #5
_0223988A:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r4, r4, #1
	bne _0223988A
	ldr r0, [r6]
	str r0, [r5]
	add r0, sp, #0
	str r3, [sp, #0x20]
	str r2, [sp, #0x24]
	bl FUN_021E8648
	add sp, #0x2c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_022398A4: .word 0x0224F21C

	thumb_func_start FUN_022398A8
FUN_022398A8: ; 0x022398A8
	ldr r3, _022398B4 ; =FUN_0200CA98
	mov r2, #1
	add r1, r0, #0
	ldr r0, _022398B8 ; =0x022398BD
	lsl r2, r2, #0xa
	bx r3
	.align 2, 0
_022398B4: .word FUN_0200CA98
_022398B8: .word 0x022398BD

	.section .data
	; 0x022398BC
	.incbin "baserom.nds", 0x16b81c, 0x18b64

	.section .bss
	; 0x02252420
	.space 0x20
