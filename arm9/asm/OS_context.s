    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_InitContext
OS_InitContext: ; 0x020CBAC4
	add r1, r1, #0x4
	str r1, [r0, #0x40]
	str r2, [r0, #0x44]
	sub r2, r2, #0x40
	tst r2, #0x4
	subne r2, r2, #0x4
	str r2, [r0, #0x38]
	ands r1, r1, #0x1
	movne r1, #0x3f
	moveq r1, #0x1f
	str r1, [r0, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
	str r1, [r0, #0x8]
	str r1, [r0, #0xc]
	str r1, [r0, #0x10]
	str r1, [r0, #0x14]
	str r1, [r0, #0x18]
	str r1, [r0, #0x1c]
	str r1, [r0, #0x20]
	str r1, [r0, #0x24]
	str r1, [r0, #0x28]
	str r1, [r0, #0x2c]
	str r1, [r0, #0x30]
	str r1, [r0, #0x34]
	str r1, [r0, #0x3c]
	bx lr

	arm_func_start OS_SaveContext
OS_SaveContext:
	stmdb sp!, {r0,lr}
	add r0, r0, #0x48
	ldr r1, _020CBB78 ; =CP_SaveContext
	blx r1
	ldmia sp!, {r0,lr}
	add r1, r0, #0x0
	mrs r2, cpsr
	str r2, [r1], #0x4
	mov r0, #0xd3
	msr cpsr_c, r0
	str sp, [r1, #0x40]
	msr cpsr_c, r2
	mov r0, #0x1
	stmia r1, {r0-lr}
	add r0, pc, #0x8 ; =_020CBB78
	str r0, [r1, #0x3c]
	mov r0, #0x0
	bx lr
	.balign 4
_020CBB78: .word CP_SaveContext

	arm_func_start OS_LoadContext
OS_LoadContext: ; 0x020CBB7C
	stmdb sp!, {r0,lr}
	add r0, r0, #0x48
	ldr r1, _020CBBBC ; =CP_RestoreContext
	blx r1
	ldmia sp!, {r0,lr}
	mrs r1, cpsr
	bic r1, r1, #0x1f
	orr r1, r1, #0xd3
	msr cpsr_c, r1
	ldr r1, [r0], #0x4
	msr spsr_fsxc, r1
	ldr sp, [r0, #0x40]
	ldr lr, [r0, #0x3c]
	ldmia r0, {r0-lr}^
	mov r0, r0
	subs pc, lr, #0x4
	.balign 4
_020CBBBC: .word CP_RestoreContext
