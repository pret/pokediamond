	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNS_G3dFreeAnmObj
NNS_G3dFreeAnmObj: ; 0x020BB8C4
	ldr ip, _020BB8CC ; =NNS_FndFreeToAllocator
	bx r12
	.balign 4
_020BB8CC: .word NNS_FndFreeToAllocator
	arm_func_end NNS_G3dFreeAnmObj

	arm_func_start NNS_G3dAllocAnmObj
NNS_G3dAllocAnmObj: ; 0x020BB8D0
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, r1
	mov r1, r2
	bl NNS_G3dAnmObjCalcSizeRequired
	mov r1, r0
	mov r0, r4
	bl NNS_FndAllocFromAllocator
	ldmia sp!, {r4,pc}
	arm_func_end NNS_G3dAllocAnmObj
