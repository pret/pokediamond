	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global sRootListInitialized
sRootListInitialized: ; 0x021CCD38
	.space 0x4

	.global sRootList
sRootList: ; 0x021CCD3C
	.space 0xc
	.text

	arm_func_start NNSi_FndFinalizeHeap
NNSi_FndFinalizeHeap: ; 0x020ADC8C
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FindListContainHeap
	mov r1, r4
	bl NNS_FndRemoveListObject
	ldmia sp!, {r4,pc}
	arm_func_end NNSi_FndFinalizeHeap

	arm_func_start NNSi_FndInitHeapHead
NNSi_FndInitHeapHead:
	stmdb sp!, {r4,lr}
	mov r4, r0
	str r1, [r4, #0x0]
	str r2, [r4, #0x18]
	str r3, [r4, #0x1c]
	mov r0, #0x0
	str r0, [r4, #0x20]
	ldr r1, [r4, #0x20]
	ldrh r0, [sp, #0x8]
	bic r1, r1, #0xff
	str r1, [r4, #0x20]
	ldr r1, [r4, #0x20]
	and r0, r0, #0xff
	orr r2, r1, r0
	add r0, r4, #0xc
	mov r1, #0x4
	str r2, [r4, #0x20]
	bl NNS_FndInitList
	ldr r0, _020ADD28 ; =sRootListInitialized
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020ADD14
	ldr r0, _020ADD2C ; =sRootList
	mov r1, #0x4
	bl NNS_FndInitList
	ldr r0, _020ADD28 ; =sRootListInitialized
	mov r1, #0x1
	str r1, [r0, #0x0]
_020ADD14:
	mov r0, r4
	bl FindListContainHeap
	mov r1, r4
	bl NNS_FndAppendListObject
	ldmia sp!, {r4,pc}
	.balign 4
_020ADD28: .word sRootListInitialized
_020ADD2C: .word sRootList
	arm_func_end NNSi_FndInitHeapHead

	arm_func_start FindListContainHeap
FindListContainHeap: ; 0x020ADD30
	stmdb sp!, {r4,lr}
	ldr r4, _020ADD54 ; =sRootList
	mov r1, r0
	mov r0, r4
	bl FindContainHeap
	cmp r0, #0x0
	addne r4, r0, #0xc
	mov r0, r4
	ldmia sp!, {r4,pc}
	.balign 4
_020ADD54: .word sRootList
	arm_func_end FindListContainHeap

	arm_func_start FindContainHeap
FindContainHeap:
	stmdb sp!, {r4-r6,lr}
	mov r5, r1
	mov r1, #0x0
	mov r6, r0
	bl NNS_FndGetNextListObject
	movs r4, r0
	beq _020ADDB8
_020ADD74:
	ldr r0, [r4, #0x18]
	cmp r0, r5
	bhi _020ADDA4
	ldr r0, [r4, #0x1c]
	cmp r5, r0
	bhs _020ADDA4
	mov r1, r5
	add r0, r4, #0xc
	bl FindContainHeap
	cmp r0, #0x0
	moveq r0, r4
	ldmia sp!, {r4-r6,pc}
_020ADDA4:
	mov r0, r6
	mov r1, r4
	bl NNS_FndGetNextListObject
	movs r4, r0
	bne _020ADD74
_020ADDB8:
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}
	arm_func_end FindContainHeap
