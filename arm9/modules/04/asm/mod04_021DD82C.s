	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MOD04_021DD82C
MOD04_021DD82C: ; 0x021DD82C
	ldr ip, _021DD840 ; =MOD04_021DD904
	mov r1, r0
	mov r0, #5
	mov r2, #0
	bx ip
	.align 2, 0
_021DD840: .word MOD04_021DD904
	arm_func_end MOD04_021DD82C

	arm_func_start MOD04_021DD844
MOD04_021DD844: ; 0x021DD844
	ldr ip, _021DD85C ; =MOD04_021DD8E8
	mov r2, r1
	mov r1, r0
	mov r3, r2
	mov r0, #5
	bx ip
	.align 2, 0
_021DD85C: .word MOD04_021DD8E8
	arm_func_end MOD04_021DD844

	arm_func_start MOD04_021DD860
MOD04_021DD860: ; 0x021DD860
	ldr ip, _021DD870 ; =MOD04_021DD944
	mov r1, r0
	mov r0, #5
	bx ip
	.align 2, 0
_021DD870: .word MOD04_021DD944
	arm_func_end MOD04_021DD860

	arm_func_start MOD04_021DD874
MOD04_021DD874: ; 0x021DD874
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	ldr ip, _021DD8E0 ; =UNK04_02210514
	mov r4, r2
	mov r7, r3
	mov r5, r1
	ldr r2, [sp, #0x18]
	ldr r3, [ip]
	mov r1, r7
	mov r8, r0
	blx r3
	movs r6, r0
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
	cmp r5, #0
	beq _021DD8D8
	mov r0, r5
	mov r1, r6
	mov r2, r7
	bl MI_CpuCopy8
	ldr r1, _021DD8E4 ; =UNK04_02210510
	mov r0, r8
	ldr r3, [r1]
	mov r1, r5
	mov r2, r4
	blx r3
_021DD8D8:
	mov r0, r6
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_021DD8E0: .word UNK04_02210514
_021DD8E4: .word UNK04_02210510
	arm_func_end MOD04_021DD874

	arm_func_start MOD04_021DD8E8
MOD04_021DD8E8: ; 0x021DD8E8
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov ip, #0x20
	str ip, [sp]
	bl MOD04_021DD874
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end MOD04_021DD8E8

	arm_func_start MOD04_021DD904
MOD04_021DD904: ; 0x021DD904
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r3, _021DD920 ; =UNK04_02210510
	ldr r3, [r3]
	blx r3
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DD920: .word UNK04_02210510
	arm_func_end MOD04_021DD904

	arm_func_start MOD04_021DD924
MOD04_021DD924: ; 0x021DD924
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r3, _021DD940 ; =UNK04_02210514
	ldr r3, [r3]
	blx r3
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DD940: .word UNK04_02210514
	arm_func_end MOD04_021DD924

	arm_func_start MOD04_021DD944
MOD04_021DD944: ; 0x021DD944
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r3, _021DD964 ; =UNK04_02210514
	mov r2, #0x20
	ldr r3, [r3]
	blx r3
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DD964: .word UNK04_02210514
	arm_func_end MOD04_021DD944

	arm_func_start MOD04_021DD968
MOD04_021DD968: ; 0x021DD968
	ldr r3, _021DD97C ; =UNK04_02210514
	ldr r2, _021DD980 ; =UNK04_02210510
	str r0, [r3]
	str r1, [r2]
	bx lr
	.align 2, 0
_021DD97C: .word UNK04_02210514
_021DD980: .word UNK04_02210510
	arm_func_end MOD04_021DD968

	.section .bss

	.global UNK04_02210510
UNK04_02210510: ; 0x02210510
	.space 0x4

	.global UNK04_02210514
UNK04_02210514: ; 0x02210514
	.space 0x4
