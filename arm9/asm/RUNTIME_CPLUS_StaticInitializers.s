	.include "asm/macros.inc"
	.include "global.inc"

	.bss

	.global __global_destructor_chain
__global_destructor_chain: ; 0x021D74C8
	.space 0x18

	.text

	.extern __sinit__
	arm_func_start __call_static_initializers
__call_static_initializers: ; 0x020EC694
	stmdb sp!, {r4,lr}
	ldr r4, _020EC6BC ; =__sinit__
	b _020EC6A8
_020EC6A0:
	blx r0
	add r4, r4, #0x4
_020EC6A8:
	cmp r4, #0x0
	ldrne r0, [r4, #0x0]
	cmpne r0, #0x0
	bne _020EC6A0
	ldmia sp!, {r4,pc}
	.balign 4
_020EC6BC: .word __sinit__

	arm_func_start __destroy_global_chain
__destroy_global_chain: ; 0x020EC6C0
	stmdb sp!, {r3-r5,lr}
	ldr r4, _020EC700 ; =__global_destructor_chain
	ldr r2, [r4, #0x0]
	cmp r2, #0x0
	ldmeqia sp!, {r3-r5,pc}
_020EC6D4: ; 0x020EC6D4
	mvn r5, #0x0
_020EC6D8:
	ldr r0, [r2, #0x0]
	mov r1, r5
	str r0, [r4, #0x0]
	ldr r0, [r2, #0x8]
	ldr r2, [r2, #0x4]
	blx r2
	ldr r2, [r4, #0x0]
	cmp r2, #0x0
	bne _020EC6D8
	ldmia sp!, {r3-r5,pc}
	.balign 4
_020EC700: .word __global_destructor_chain

	.section .exceptix,4

	.word __call_static_initializers
	.short 45
	.word 0x00100100
	.word __destroy_global_chain
	.short 69
	.word 0x00200300
