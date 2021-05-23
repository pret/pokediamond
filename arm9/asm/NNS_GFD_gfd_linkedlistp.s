	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

mgr_: ; 0x021CCD88
	.space 0x14

	.section .text

	arm_func_start NNS_GfdResetLnkPlttVramState
NNS_GfdResetLnkPlttVramState: ; 0x020AFA30
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020AFA78 ; =mgr_
	ldr r1, [r0, #0x10]
	ldr r0, [r0, #0xc]
	mov r1, r1, lsr #0x4
	bl NNSi_GfdInitLnkVramBlockPool
	ldr r1, _020AFA78 ; =mgr_
	str r0, [r1, #0x4]
	mov r0, r1
	bl NNSi_GfdInitLnkVramMan
	ldr r0, _020AFA78 ; =mgr_
	ldr r1, _020AFA7C ; =mgr_ + 0x4
	ldr r3, [r0, #0x8]
	mov r2, #0x0
	bl NNSi_GfdAddNewFreeBlock
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AFA78: .word mgr_
_020AFA7C: .word mgr_ + 0x4
	arm_func_end NNS_GfdResetLnkPlttVramState

	arm_func_start NNS_GfdFreeLnkPlttVram
NNS_GfdFreeLnkPlttVram: ; 0x020AFA80
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r1, #0x10000
	rsb r2, r1, #0x0
	ldr r1, _020AFAC8 ; =0x0000FFFF
	and r2, r0, r2
	and r12, r0, r1
	mov r3, r2, lsr #0x10
	ldr r0, _020AFACC ; =mgr_
	ldr r1, _020AFAD0 ; =mgr_ + 0x4
	mov r2, r12, lsl #0x3
	mov r3, r3, lsl #0x3
	bl NNSi_GfdFreeLnkVram
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AFAC8: .word 0x0000FFFF
_020AFACC: .word mgr_
_020AFAD0: .word mgr_ + 0x4
	arm_func_end NNS_GfdFreeLnkPlttVram

	arm_func_start NNS_GfdAllocLnkPlttVram
NNS_GfdAllocLnkPlttVram: ; 0x020AFAD4
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	cmp r0, #0x0
	moveq r4, #0x8
	addne r0, r0, #0x7
	bicne r4, r0, #0x7
	ldr r0, _020AFB98 ; =0x0007FFF8
	cmp r4, r0
	addcs sp, sp, #0x8
	movcs r0, #0x0
	ldmcsia sp!, {r4,pc}
	cmp r1, #0x0
	beq _020AFB50
	mov r12, #0x8
	ldr r0, _020AFB9C ; =mgr_
	ldr r1, _020AFBA0 ; =mgr_ + 0x4
	add r2, sp, #0x4
	mov r3, r4
	str r12, [sp, #0x0]
	bl NNSi_GfdAllocLnkVramAligned
	ldr r2, [sp, #0x4]
	add r1, r2, r4
	cmp r1, #0x10000
	bls _020AFB6C
	ldr r0, _020AFB9C ; =mgr_
	ldr r1, _020AFBA0 ; =mgr_ + 0x4
	mov r3, r4
	bl NNSi_GfdFreeLnkVram
	add sp, sp, #0x8
	mov r0, #0x0
	ldmia sp!, {r4,pc}
_020AFB50:
	ldr r0, _020AFB9C ; =mgr_
	mov r12, #0x10
	ldr r1, _020AFBA0 ; =mgr_ + 0x4
	add r2, sp, #0x4
	mov r3, r4
	str r12, [sp, #0x0]
	bl NNSi_GfdAllocLnkVramAligned
_020AFB6C:
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r1, [sp, #0x4]
	ldr r0, _020AFBA4 ; =0x0000FFFF
	mov r2, r4, lsr #0x3
	and r0, r0, r1, lsr #0x3
	orr r0, r0, r2, lsl #0x10
	add sp, sp, #0x8
	ldmia sp!, {r4,pc}
	.balign 4
_020AFB98: .word 0x0007FFF8
_020AFB9C: .word mgr_
_020AFBA0: .word mgr_ + 0x4
_020AFBA4: .word 0x0000FFFF
	arm_func_end NNS_GfdAllocLnkPlttVram

	arm_func_start NNS_GfdInitLnkPlttVramManager
NNS_GfdInitLnkPlttVramManager: ; 0x020AFBA8
	stmdb sp!, {r4,lr}
	ldr ip, _020AFBE8 ; =mgr_
	mov r4, r3
	str r0, [r12, #0x8]
	str r1, [r12, #0xc]
	str r2, [r12, #0x10]
	bl NNS_GfdResetLnkPlttVramState
	cmp r4, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r3, _020AFBEC ; =NNS_GfdAllocLnkPlttVram
	ldr r1, _020AFBF0 ; =NNS_GfdDefaultFuncAllocPlttVram
	ldr r2, _020AFBF4 ; =NNS_GfdFreeLnkPlttVram
	ldr r0, _020AFBF8 ; =NNS_GfdDefaultFuncFreePlttVram
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_020AFBE8: .word mgr_
_020AFBEC: .word NNS_GfdAllocLnkPlttVram
_020AFBF0: .word NNS_GfdDefaultFuncAllocPlttVram
_020AFBF4: .word NNS_GfdFreeLnkPlttVram
_020AFBF8: .word NNS_GfdDefaultFuncFreePlttVram
	arm_func_end NNS_GfdInitLnkPlttVramManager

	arm_func_start NNS_GfdGetLnkPlttVramManagerWorkSize
NNS_GfdGetLnkPlttVramManagerWorkSize: ; 0x020AFBFC
	mov r0, r0, lsl #0x4
	bx lr
	arm_func_end NNS_GfdGetLnkPlttVramManagerWorkSize
