	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global __LOCAL_LABEL__$7929
__LOCAL_LABEL__$7929: ; 0x020FF864
	.byte 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.section .bss

mgr_: ; 0x021CCD6C
	.space 0x1C

	.section .text

	arm_func_start NNS_GfdResetLnkTexVramState
NNS_GfdResetLnkTexVramState: ; 0x020AF6A4
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x30
	ldr r6, _020AF884 ; =__LOCAL_LABEL__$7929
	add r5, sp, #0x0
	ldmia r6!, {r0-r3}
	mov r12, r5
	stmia r5!, {r0-r3}
	ldmia r6!, {r0-r3}
	stmia r5!, {r0-r3}
	ldr r4, _020AF888 ; =mgr_
	ldmia r6, {r0-r3}
	stmia r5, {r0-r3}
	ldr lr, [r4, #0x10]
	ldr r1, [r4, #0xc]
	add r0, lr, lr, lsr #0x1
	mov r4, lr, lsr #0x1
	sub r0, r1, r0
	mov r3, #0x0
_020AF6EC:
	cmp r3, #0x0
	beq _020AF6FC
	cmp r3, #0x2
	bne _020AF734
_020AF6FC:
	ldr r2, [r12, #0x0]
	cmp r2, #0x0
	beq _020AF734
	cmp lr, #0x0
	beq _020AF734
	ldr r1, [r12, #0x8]
	cmp r2, lr
	movhi r2, lr
	add r1, r1, r2
	str r1, [r12, #0x8]
	ldr r1, [r12, #0x0]
	sub lr, lr, r2
	sub r1, r1, r2
	str r1, [r12, #0x0]
_020AF734:
	add r3, r3, #0x1
	cmp r3, #0x4
	add r12, r12, #0xc
	blo _020AF6EC
	ldr r1, [sp, #0xc]
	add r5, sp, #0x0
	sub r1, r1, r4
	str r1, [sp, #0xc]
	mov r3, #0x0
_020AF758:
	ldr r2, [r5, #0x0]
	cmp r2, #0x0
	beq _020AF790
	cmp r0, #0x0
	beq _020AF790
	ldr r1, [r5, #0x4]
	cmp r2, r0
	movhi r2, r0
	add r1, r1, r2
	str r1, [r5, #0x4]
	ldr r1, [r5, #0x0]
	sub r0, r0, r2
	sub r1, r1, r2
	str r1, [r5, #0x0]
_020AF790:
	add r3, r3, #0x1
	cmp r3, #0x4
	add r5, r5, #0xc
	blo _020AF758
	ldr r0, _020AF888 ; =mgr_
	bl NNSi_GfdInitLnkVramMan
	ldr r0, _020AF88C ; =mgr_ + 0x4
	bl NNSi_GfdInitLnkVramMan
	ldr r0, _020AF888 ; =mgr_
	ldr r1, [r0, #0x18]
	ldr r0, [r0, #0x14]
	mov r1, r1, lsr #0x4
	bl NNSi_GfdInitLnkVramBlockPool
	ldr r3, [sp, #0x8]
	ldr r1, _020AF888 ; =mgr_
	cmp r3, #0x0
	str r0, [r1, #0x8]
	beq _020AF7E8
	ldr r0, _020AF88C ; =mgr_ + 0x4
	ldr r1, _020AF890 ; =mgr_ + 0x8
	mov r2, #0x0
	bl NNSi_GfdAddNewFreeBlock
_020AF7E8:
	ldr r3, [sp, #0x4]
	ldr r2, [sp, #0x8]
	cmp r3, #0x0
	beq _020AF804
	ldr r0, _020AF888 ; =mgr_
	ldr r1, _020AF890 ; =mgr_ + 0x8
	bl NNSi_GfdAddNewFreeBlock
_020AF804:
	ldr r3, [sp, #0x20]
	cmp r3, #0x0
	beq _020AF820
	ldr r0, _020AF88C ; =mgr_ + 0x4
	ldr r1, _020AF890 ; =mgr_ + 0x8
	mov r2, #0x40000
	bl NNSi_GfdAddNewFreeBlock
_020AF820:
	ldr r3, [sp, #0x1c]
	ldr r0, [sp, #0x20]
	cmp r3, #0x0
	add r2, r0, #0x40000
	beq _020AF840
	ldr r0, _020AF888 ; =mgr_
	ldr r1, _020AF890 ; =mgr_ + 0x8
	bl NNSi_GfdAddNewFreeBlock
_020AF840:
	ldr r3, [sp, #0x28]
	cmp r3, #0x0
	beq _020AF85C
	ldr r0, _020AF888 ; =mgr_
	ldr r1, _020AF890 ; =mgr_ + 0x8
	mov r2, #0x60000
	bl NNSi_GfdAddNewFreeBlock
_020AF85C:
	ldr r3, [sp, #0x10]
	cmp r3, #0x0
	addeq sp, sp, #0x30
	ldmeqia sp!, {r4-r6,pc}
	ldr r0, _020AF888 ; =mgr_
	ldr r1, _020AF890 ; =mgr_ + 0x8
	add r2, r4, #0x20000
	bl NNSi_GfdAddNewFreeBlock
	add sp, sp, #0x30
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020AF884: .word __LOCAL_LABEL__$7929
_020AF888: .word mgr_
_020AF88C: .word mgr_ + 0x4
_020AF890: .word mgr_ + 0x8
	arm_func_end NNS_GfdResetLnkTexVramState

	arm_func_start NNS_GfdFreeLnkTexVram
NNS_GfdFreeLnkTexVram: ; 0x020AF894
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020AF908 ; =0x7FFF0000
	ldr r1, _020AF90C ; =0x0000FFFF
	and r2, r0, r2
	and r3, r0, r1
	mov r1, r2, lsr #0x10
	and r0, r0, #0x80000000
	mov r2, r3, lsl #0x3
	movs r3, r1, lsl #0x4
	mov r0, r0, lsr #0x1f
	beq _020AF8FC
	cmp r0, #0x0
	beq _020AF8DC
	ldr r0, _020AF910 ; =mgr_ + 0x4
	ldr r1, _020AF914 ; =mgr_ + 0x8
	bl NNSi_GfdFreeLnkVram
	b _020AF8E8
_020AF8DC:
	ldr r0, _020AF918 ; =mgr_
	ldr r1, _020AF914 ; =mgr_ + 0x8
	bl NNSi_GfdFreeLnkVram
_020AF8E8:
	cmp r0, #0x0
	movne r0, #0x0
	add sp, sp, #0x4
	moveq r0, #0x1
	ldmia sp!, {pc}
_020AF8FC:
	mov r0, #0x2
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AF908: .word 0x7FFF0000
_020AF90C: .word 0x0000FFFF
_020AF910: .word mgr_ + 0x4
_020AF914: .word mgr_ + 0x8
_020AF918: .word mgr_
	arm_func_end NNS_GfdFreeLnkTexVram

	arm_func_start NNS_GfdAllocLnkTexVram
NNS_GfdAllocLnkTexVram: ; 0x020AF91C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	moveq r5, #0x10
	addne r0, r0, #0xf
	bicne r5, r0, #0xf
	ldr r0, _020AF9B0 ; =0x0007FFF0
	mov r4, r1
	cmp r5, r0
	addcs sp, sp, #0x4
	movcs r0, #0x0
	ldmcsia sp!, {r4-r5,pc}
	cmp r4, #0x0
	beq _020AF96C
	ldr r0, _020AF9B4 ; =mgr_ + 0x4
	ldr r1, _020AF9B8 ; =mgr_ + 0x8
	add r2, sp, #0x0
	mov r3, r5
	bl NNSi_GfdAllocLnkVram
	b _020AF980
_020AF96C:
	ldr r0, _020AF9BC ; =mgr_
	ldr r1, _020AF9B8 ; =mgr_ + 0x8
	add r2, sp, #0x0
	mov r3, r5
	bl NNSi_GfdAllocLnkVram
_020AF980:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
	ldr r1, [sp, #0x0]
	ldr r0, _020AF9C0 ; =0x0000FFFF
	mov r2, r5, lsr #0x4
	and r0, r0, r1, lsr #0x3
	orr r0, r0, r2, lsl #0x10
	orr r0, r0, r4, lsl #0x1f
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AF9B0: .word 0x0007FFF0
_020AF9B4: .word mgr_ + 0x4
_020AF9B8: .word mgr_ + 0x8
_020AF9BC: .word mgr_
_020AF9C0: .word 0x0000FFFF
	arm_func_end NNS_GfdAllocLnkTexVram

	arm_func_start NNS_GfdInitLnkTexVramManager
NNS_GfdInitLnkTexVramManager: ; 0x020AF9C4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr ip, _020AFA14 ; =mgr_
	str r0, [r12, #0xc]
	str r1, [r12, #0x10]
	str r2, [r12, #0x14]
	str r3, [r12, #0x18]
	bl NNS_GfdResetLnkTexVramState
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r3, _020AFA18 ; =NNS_GfdAllocLnkTexVram
	ldr r1, _020AFA1C ; =NNS_GfdDefaultFuncAllocTexVram
	ldr r2, _020AFA20 ; =NNS_GfdFreeLnkTexVram
	ldr r0, _020AFA24 ; =NNS_GfdDefaultFuncFreeTexVram
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AFA14: .word mgr_
_020AFA18: .word NNS_GfdAllocLnkTexVram
_020AFA1C: .word NNS_GfdDefaultFuncAllocTexVram
_020AFA20: .word NNS_GfdFreeLnkTexVram
_020AFA24: .word NNS_GfdDefaultFuncFreeTexVram
	arm_func_end NNS_GfdInitLnkTexVramManager

	arm_func_start NNS_GfdGetLnkTexVramManagerWorkSize
NNS_GfdGetLnkTexVramManagerWorkSize: ; 0x020AFA28
	mov r0, r0, lsl #0x4
	bx lr
	arm_func_end NNS_GfdGetLnkTexVramManagerWorkSize
