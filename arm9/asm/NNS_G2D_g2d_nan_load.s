	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; _end
	arm_func_start FUN_020AFC04
FUN_020AFC04: ; 0x020AFC04
	ldrh r2, [r0, #0x0]
	cmp r2, r1
	ldrhi r0, [r0, #0x4]
	addhi r0, r0, r1, lsl #0x4
	movls r0, #0x0
	bx lr
	arm_func_end FUN_020AFC04

	; _end
	arm_func_start FUN_020AFC1C
FUN_020AFC1C: ; 0x020AFC1C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r1, [r0, #0x4]
	mov r6, #0x0
	add r1, r1, r0
	str r1, [r0, #0x4]
	ldr r1, [r0, #0x8]
	add r1, r1, r0
	str r1, [r0, #0x8]
	ldr r1, [r0, #0xc]
	add r1, r1, r0
	str r1, [r0, #0xc]
	ldrh r1, [r0, #0x0]
	ldr r4, [r0, #0x4]
	ldr lr, [r0, #0x8]
	cmp r1, #0x0
	ldr r12, [r0, #0xc]
	bls _020AFCCC
	mov r1, r6
_020AFC68:
	add r2, r4, r6, lsl #0x4
	ldr r5, [r2, #0xc]
	mov r3, r6, lsl #0x4
	add r5, lr, r5
	str r5, [r2, #0xc]
	ldrh r7, [r4, r3]
	mov r5, r1
	cmp r7, #0x0
	bls _020AFCB4
_020AFC8C:
	ldr r9, [r2, #0xc]
	add r7, r5, #0x1
	ldr r8, [r9, r5, lsl #0x3]
	mov r7, r7, lsl #0x10
	add r8, r12, r8
	str r8, [r9, r5, lsl #0x3]
	ldrh r8, [r4, r3]
	mov r5, r7, lsr #0x10
	cmp r5, r8
	blo _020AFC8C
_020AFCB4:
	add r2, r6, #0x1
	mov r2, r2, lsl #0x10
	ldrh r3, [r0, #0x0]
	mov r6, r2, lsr #0x10
	cmp r6, r3
	blo _020AFC68
_020AFCCC:
	ldr r1, [r0, #0x14]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r9,pc}
	add r1, r1, r0
	str r1, [r0, #0x14]
	ldr r1, [r0, #0x14]
	mov r12, #0x0
	add r2, r1, #0x8
	ldr r0, [r2, #0x4]
	add r0, r0, r2
	str r0, [r2, #0x4]
	ldrh r0, [r1, #0x8]
	cmp r0, #0x0
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r9,pc}
	mov r0, r12
	mov r6, r12
_020AFD14:
	ldr r5, [r2, #0x4]
	mov r3, r6
	add r1, r5, r0
	ldr r4, [r1, #0x4]
	add r4, r4, r2
	str r4, [r1, #0x4]
	ldr r4, [r1, #0x8]
	add r4, r4, r2
	str r4, [r1, #0x8]
	ldrh r4, [r5, r0]
	cmp r4, #0x0
	bls _020AFD6C
	mov r7, r6
_020AFD48:
	ldr r5, [r1, #0x8]
	add r3, r3, #0x1
	ldr r4, [r5, r7]
	add r4, r4, r2
	str r4, [r5, r7]
	ldrh r4, [r1, #0x0]
	add r7, r7, #0x4
	cmp r3, r4
	blo _020AFD48
_020AFD6C:
	ldrh r1, [r2, #0x0]
	add r12, r12, #0x1
	add r0, r0, #0xc
	cmp r12, r1
	blo _020AFD14
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	arm_func_end FUN_020AFC1C

	; NNS_G2dGetUnpackedMCAnimBank
	arm_func_start thunk_FUN_020afda0
thunk_FUN_020afda0: ; 0x020AFD88
	ldr ip, _020AFD90 ; =FUN_020AFDA0
	bx r12
	.balign 4
_020AFD90: .word FUN_020AFDA0
	arm_func_end thunk_FUN_020afda0

	; NNS_G2dGetUnpackedAnimBank
	arm_func_start thunk_FUN_020afda0_2
thunk_FUN_020afda0_2: ; 0x020AFD94
	ldr ip, _020AFD9C ; =FUN_020AFDA0
	bx r12
	.balign 4
_020AFD9C: .word FUN_020AFDA0
	arm_func_end thunk_FUN_020afda0_2

	; GetUnpackedAnimBankImpl_
	arm_func_start FUN_020AFDA0
FUN_020AFDA0: ; 0x020AFDA0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldr r1, _020AFDE4 ; =0x41424E4B
	bl FUN_020B01F8
	movs r4, r0
	moveq r0, #0x0
	addeq sp, sp, #0x4
	streq r0, [r5, #0x0]
	ldmeqia sp!, {r4-r5,pc}
	add r0, r4, #0x8
	bl FUN_020AFC1C
	add r0, r4, #0x8
	str r0, [r5, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AFDE4: .word 0x41424E4B
	arm_func_end FUN_020AFDA0

