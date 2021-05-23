	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	; mgr_
	.global UNK_021CCD88
UNK_021CCD88: ; 0x021CCD88
	.space 0x4

	; mgr_ + 0x4
	.global UNK_021CCD8C
UNK_021CCD8C: ; 0x021CCD8C
	.space 0x10

	.section .text

	; NNS_GfdResetLnkPlttVramState
	arm_func_start FUN_020AFA30
FUN_020AFA30: ; 0x020AFA30
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020AFA78 ; =UNK_021CCD88
	ldr r1, [r0, #0x10]
	ldr r0, [r0, #0xc]
	mov r1, r1, lsr #0x4
	bl FUN_020AF64C
	ldr r1, _020AFA78 ; =UNK_021CCD88
	str r0, [r1, #0x4]
	mov r0, r1
	bl FUN_020AF698
	ldr r0, _020AFA78 ; =UNK_021CCD88
	ldr r1, _020AFA7C ; =UNK_021CCD8C
	ldr r3, [r0, #0x8]
	mov r2, #0x0
	bl FUN_020AF5E0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AFA78: .word UNK_021CCD88
_020AFA7C: .word UNK_021CCD8C
	arm_func_end FUN_020AFA30

	; NNS_GfdFreeLnkPlttVram
	arm_func_start FUN_020AFA80
FUN_020AFA80: ; 0x020AFA80
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r1, #0x10000
	rsb r2, r1, #0x0
	ldr r1, _020AFAC8 ; =0x0000FFFF
	and r2, r0, r2
	and r12, r0, r1
	mov r3, r2, lsr #0x10
	ldr r0, _020AFACC ; =UNK_021CCD88
	ldr r1, _020AFAD0 ; =UNK_021CCD8C
	mov r2, r12, lsl #0x3
	mov r3, r3, lsl #0x3
	bl FUN_020AF334
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AFAC8: .word 0x0000FFFF
_020AFACC: .word UNK_021CCD88
_020AFAD0: .word UNK_021CCD8C
	arm_func_end FUN_020AFA80

	; NNS_GfdAllocLnkPlttVram
	arm_func_start FUN_020AFAD4
FUN_020AFAD4: ; 0x020AFAD4
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
	ldr r0, _020AFB9C ; =UNK_021CCD88
	ldr r1, _020AFBA0 ; =UNK_021CCD8C
	add r2, sp, #0x4
	mov r3, r4
	str r12, [sp, #0x0]
	bl FUN_020AF488
	ldr r2, [sp, #0x4]
	add r1, r2, r4
	cmp r1, #0x10000
	bls _020AFB6C
	ldr r0, _020AFB9C ; =UNK_021CCD88
	ldr r1, _020AFBA0 ; =UNK_021CCD8C
	mov r3, r4
	bl FUN_020AF334
	add sp, sp, #0x8
	mov r0, #0x0
	ldmia sp!, {r4,pc}
_020AFB50:
	ldr r0, _020AFB9C ; =UNK_021CCD88
	mov r12, #0x10
	ldr r1, _020AFBA0 ; =UNK_021CCD8C
	add r2, sp, #0x4
	mov r3, r4
	str r12, [sp, #0x0]
	bl FUN_020AF488
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
_020AFB9C: .word UNK_021CCD88
_020AFBA0: .word UNK_021CCD8C
_020AFBA4: .word 0x0000FFFF
	arm_func_end FUN_020AFAD4

	; NNS_GfdInitLnkPlttVramManager
	arm_func_start FUN_020AFBA8
FUN_020AFBA8: ; 0x020AFBA8
	stmdb sp!, {r4,lr}
	ldr ip, _020AFBE8 ; =UNK_021CCD88
	mov r4, r3
	str r0, [r12, #0x8]
	str r1, [r12, #0xc]
	str r2, [r12, #0x10]
	bl FUN_020AFA30
	cmp r4, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r3, _020AFBEC ; =FUN_020AFAD4
	ldr r1, _020AFBF0 ; =UNK_021064C0
	ldr r2, _020AFBF4 ; =FUN_020AFA80
	ldr r0, _020AFBF8 ; =UNK_021064C4
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_020AFBE8: .word UNK_021CCD88
_020AFBEC: .word FUN_020AFAD4
_020AFBF0: .word UNK_021064C0
_020AFBF4: .word FUN_020AFA80
_020AFBF8: .word UNK_021064C4
	arm_func_end FUN_020AFBA8

	; _end
	arm_func_start FUN_020AFBFC
FUN_020AFBFC: ; 0x020AFBFC
	mov r0, r0, lsl #0x4
	bx lr
	arm_func_end FUN_020AFBFC

