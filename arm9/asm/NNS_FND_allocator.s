	.include "asm/macros.inc"
	.include "global.inc"
	.rodata
	; static const in function

	.global sAllocatorFunc$7864
sAllocatorFunc$7864: ; 0x020FF7CC
	.word AllocatorAllocForExpHeap
	.word AllocatorFreeForExpHeap
	.text

	arm_func_start NNS_FndInitAllocatorForExpHeap
NNS_FndInitAllocatorForExpHeap: ; 0x020AE82C
	ldr ip, _020AE848 ; =sAllocatorFunc$7864
	mov r3, #0x0
	str r12, [r0, #0x0]
	str r1, [r0, #0x4]
	str r2, [r0, #0x8]
	str r3, [r0, #0xc]
	bx lr
	.balign 4
_020AE848: .word sAllocatorFunc$7864
	arm_func_end NNS_FndInitAllocatorForExpHeap

	arm_func_start NNS_FndFreeToAllocator
NNS_FndFreeToAllocator: ; 0x020AE84C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x0]
	ldr r2, [r2, #0x4]
	blx r2
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNS_FndFreeToAllocator

	arm_func_start NNS_FndAllocFromAllocator
NNS_FndAllocFromAllocator: ; 0x020AE868
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x0]
	ldr r2, [r2, #0x0]
	blx r2
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNS_FndAllocFromAllocator

	arm_func_start AllocatorFreeForExpHeap
AllocatorFreeForExpHeap: ; 0x020AE884
	ldr ip, _020AE890 ; =NNS_FndFreeToExpHeap
	ldr r0, [r0, #0x4]
	bx r12
	.balign 4
_020AE890: .word NNS_FndFreeToExpHeap
	arm_func_end AllocatorFreeForExpHeap

	arm_func_start AllocatorAllocForExpHeap
AllocatorAllocForExpHeap: ; 0x020AE894
	ldr ip, _020AE8A8 ; =NNS_FndAllocFromExpHeapEx
	mov r2, r0
	ldr r0, [r2, #0x4]
	ldr r2, [r2, #0x8]
	bx r12
	.balign 4
_020AE8A8: .word NNS_FndAllocFromExpHeapEx
	arm_func_end AllocatorAllocForExpHeap
