	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start MI_HBlankDmaCopy16
MI_HBlankDmaCopy16: ; 0x020CDD90
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	mov r7, r0
	mov r4, r3
	mov r1, #0x10000000
	mov r5, r2
	bl MIi_CheckAnotherAutoDMA
	mov r0, r7
	mov r1, r6
	mov r2, r4
	mov r3, #0x0
	bl MIi_CheckDma0SourceAddress
_020CDDC4:
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7, lr}
	bxeq lr
	mov r0, r7
	bl MI_WaitDma
	ldr r3, _020CDE00
	mov r0, r7
	mov r1, r6
	mov r2, r5
	orr r3, r3, r4, lsr #0x1
	bl MIi_DmaSetParams
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020CDE00: .word 0x92600000

	arm_func_start MI_HBlankDmaCopy32
MI_HBlankDmaCopy32: ; 0x020CDE04
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	mov r7, r0
	mov r4, r3
	mov r1, #0x10000000
	mov r5, r2
	bl MIi_CheckAnotherAutoDMA
	mov r0, r7
	mov r1, r6
	mov r2, r4
	mov r3, #0x0
	bl MIi_CheckDma0SourceAddress
_020CDE38:
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r7
	bl MI_WaitDma
	ldr r3, _020CDE74
	mov r0, r7
	mov r1, r6
	mov r2, r5
	orr r3, r3, r4, lsr #0x2
	bl MIi_DmaSetParams
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020CDE74: .word 0x96600000
