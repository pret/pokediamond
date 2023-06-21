	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start ov04_021DD82C
ov04_021DD82C: ; 0x021DD82C
	ldr ip, _021DD840 ; =ov04_021DD904
	mov r1, r0
	mov r0, #5
	mov r2, #0
	bx ip
	.align 2, 0
_021DD840: .word ov04_021DD904
	arm_func_end ov04_021DD82C

	arm_func_start ov04_021DD844
ov04_021DD844: ; 0x021DD844
	ldr ip, _021DD85C ; =ov04_021DD8E8
	mov r2, r1
	mov r1, r0
	mov r3, r2
	mov r0, #5
	bx ip
	.align 2, 0
_021DD85C: .word ov04_021DD8E8
	arm_func_end ov04_021DD844

	arm_func_start ov04_021DD860
ov04_021DD860: ; 0x021DD860
	ldr ip, _021DD870 ; =ov04_021DD944
	mov r1, r0
	mov r0, #5
	bx ip
	.align 2, 0
_021DD870: .word ov04_021DD944
	arm_func_end ov04_021DD860

	arm_func_start ov04_021DD874
ov04_021DD874: ; 0x021DD874
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	ldr ip, _021DD8E0 ; =ov04_02210514
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
	ldr r1, _021DD8E4 ; =ov04_02210510
	mov r0, r8
	ldr r3, [r1]
	mov r1, r5
	mov r2, r4
	blx r3
_021DD8D8:
	mov r0, r6
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_021DD8E0: .word ov04_02210514
_021DD8E4: .word ov04_02210510
	arm_func_end ov04_021DD874

	arm_func_start ov04_021DD8E8
ov04_021DD8E8: ; 0x021DD8E8
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov ip, #0x20
	str ip, [sp]
	bl ov04_021DD874
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end ov04_021DD8E8

	arm_func_start ov04_021DD904
ov04_021DD904: ; 0x021DD904
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r3, _021DD920 ; =ov04_02210510
	ldr r3, [r3]
	blx r3
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DD920: .word ov04_02210510
	arm_func_end ov04_021DD904

	arm_func_start ov04_021DD924
ov04_021DD924: ; 0x021DD924
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r3, _021DD940 ; =ov04_02210514
	ldr r3, [r3]
	blx r3
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DD940: .word ov04_02210514
	arm_func_end ov04_021DD924

	arm_func_start ov04_021DD944
ov04_021DD944: ; 0x021DD944
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r3, _021DD964 ; =ov04_02210514
	mov r2, #0x20
	ldr r3, [r3]
	blx r3
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DD964: .word ov04_02210514
	arm_func_end ov04_021DD944

	arm_func_start ov04_021DD968
ov04_021DD968: ; 0x021DD968
	ldr r3, _021DD97C ; =ov04_02210514
	ldr r2, _021DD980 ; =ov04_02210510
	str r0, [r3]
	str r1, [r2]
	bx lr
	.align 2, 0
_021DD97C: .word ov04_02210514
_021DD980: .word ov04_02210510
	arm_func_end ov04_021DD968

	.section .bss

	.global ov04_02210510
ov04_02210510: ; 0x02210510
	.space 0x4

	.global ov04_02210514
ov04_02210514: ; 0x02210514
	.space 0x4
