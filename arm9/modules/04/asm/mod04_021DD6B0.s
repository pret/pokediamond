	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MOD04_021DD6B0
MOD04_021DD6B0: ; 0x021DD6B0
	ldr r3, _021DD6CC ; =UNK04_02210508
	ldr r2, [r3]
	cmp r2, #9
	ldrne r2, _021DD6D0 ; =UNK04_0221050C
	strne r0, [r3]
	strne r1, [r2]
	bx lr
	.align 2, 0
_021DD6CC: .word UNK04_02210508
_021DD6D0: .word UNK04_0221050C
	arm_func_end MOD04_021DD6B0

	arm_func_start MOD04_021DD6D4
MOD04_021DD6D4: ; 0x021DD6D4
	ldr r0, _021DD6EC ; =UNK04_02210508
	ldr r0, [r0]
	cmp r0, #0
	movne r0, #1
	moveq r0, #0
	bx lr
	.align 2, 0
_021DD6EC: .word UNK04_02210508
	arm_func_end MOD04_021DD6D4

	arm_func_start MOD04_021DD6F0
MOD04_021DD6F0: ; 0x021DD6F0
	ldr r1, _021DD710 ; =UNK04_02210508
	ldr r0, [r1]
	cmp r0, #9
	movne r2, #0
	ldrne r0, _021DD714 ; =UNK04_0221050C
	strne r2, [r1]
	strne r2, [r0]
	bx lr
	.align 2, 0
_021DD710: .word UNK04_02210508
_021DD714: .word UNK04_0221050C
	arm_func_end MOD04_021DD6F0

	arm_func_start MOD04_021DD718
MOD04_021DD718: ; 0x021DD718
	cmp r0, #0
	ldrne r2, _021DD800 ; =UNK04_0221050C
	ldrne r2, [r2]
	strne r2, [r0]
	cmp r1, #0
	beq _021DD7F4
	ldr r0, _021DD804 ; =UNK04_02210508
	ldr r0, [r0]
	cmp r0, #0x11
	addls pc, pc, r0, lsl #2
	b _021DD7EC
_021DD744: ; jump table
	b _021DD7EC ; case 0
	b _021DD7BC ; case 1
	b _021DD78C ; case 2
	b _021DD78C ; case 3
	b _021DD78C ; case 4
	b _021DD78C ; case 5
	b _021DD798 ; case 6
	b _021DD7A4 ; case 7
	b _021DD78C ; case 8
	b _021DD7BC ; case 9
	b _021DD7B0 ; case 10
	b _021DD7B0 ; case 11
	b _021DD7B0 ; case 12
	b _021DD7B0 ; case 13
	b _021DD7C8 ; case 14
	b _021DD7D4 ; case 15
	b _021DD7E0 ; case 16
	b _021DD7D4 ; case 17
_021DD78C:
	mov r0, #6
	str r0, [r1]
	b _021DD7F4
_021DD798:
	mov r0, #3
	str r0, [r1]
	b _021DD7F4
_021DD7A4:
	mov r0, #4
	str r0, [r1]
	b _021DD7F4
_021DD7B0:
	mov r0, #1
	str r0, [r1]
	b _021DD7F4
_021DD7BC:
	mov r0, #7
	str r0, [r1]
	b _021DD7F4
_021DD7C8:
	mov r0, #5
	str r0, [r1]
	b _021DD7F4
_021DD7D4:
	mov r0, #6
	str r0, [r1]
	b _021DD7F4
_021DD7E0:
	mov r0, #2
	str r0, [r1]
	b _021DD7F4
_021DD7EC:
	mov r0, #0
	str r0, [r1]
_021DD7F4:
	ldr r0, _021DD804 ; =UNK04_02210508
	ldr r0, [r0]
	bx lr
	.align 2, 0
_021DD800: .word UNK04_0221050C
_021DD804: .word UNK04_02210508
	arm_func_end MOD04_021DD718

	arm_func_start MOD04_021DD808
MOD04_021DD808: ; 0x021DD808
	cmp r0, #0
	ldrne r1, _021DD824 ; =UNK04_0221050C
	ldrne r1, [r1]
	strne r1, [r0]
	ldr r0, _021DD828 ; =UNK04_02210508
	ldr r0, [r0]
	bx lr
	.align 2, 0
_021DD824: .word UNK04_0221050C
_021DD828: .word UNK04_02210508
	arm_func_end MOD04_021DD808

	.section .bss

	.global UNK04_02210508
UNK04_02210508: ; 0x02210508
	.space 0x4

	.global UNK04_0221050C
UNK04_0221050C: ; 0x0221050C
	.space 0x4