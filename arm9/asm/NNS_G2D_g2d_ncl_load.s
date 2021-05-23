	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNS_G2dUnpackNCL
NNS_G2dUnpackNCL: ; 0x020B00D0
	ldr r1, [r0, #0xc]
	add r1, r1, r0
	str r1, [r0, #0xc]
	bx lr
	arm_func_end NNS_G2dUnpackNCL

	arm_func_start NNSi_G2dUnpackNCLCmpInfo
NNSi_G2dUnpackNCLCmpInfo: ; 0x020B00E0
	ldr r1, [r0, #0x4]
	add r1, r1, r0
	str r1, [r0, #0x4]
	bx lr
	arm_func_end NNSi_G2dUnpackNCLCmpInfo

	arm_func_start NNS_G2dGetUnpackedPaletteCompressInfo
NNS_G2dGetUnpackedPaletteCompressInfo: ; 0x020B00F0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldr r1, _020B0134 ; =0x50434D50
	bl NNS_G2dFindBinaryBlock
	movs r4, r0
	moveq r0, #0x0
	addeq sp, sp, #0x4
	streq r0, [r5, #0x0]
	ldmeqia sp!, {r4-r5,pc}
	add r0, r4, #0x8
	bl NNSi_G2dUnpackNCLCmpInfo
	add r0, r4, #0x8
	str r0, [r5, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B0134: .word 0x50434D50
	arm_func_end NNS_G2dGetUnpackedPaletteCompressInfo

	arm_func_start NNS_G2dGetUnpackedPaletteData
NNS_G2dGetUnpackedPaletteData: ; 0x020B0138
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldr r1, _020B017C ; =0x504C5454
	bl NNS_G2dFindBinaryBlock
	movs r4, r0
	moveq r0, #0x0
	addeq sp, sp, #0x4
	streq r0, [r5, #0x0]
	ldmeqia sp!, {r4-r5,pc}
	add r0, r4, #0x8
	bl NNS_G2dUnpackNCL
	add r0, r4, #0x8
	str r0, [r5, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B017C: .word 0x504C5454
	arm_func_end NNS_G2dGetUnpackedPaletteData
