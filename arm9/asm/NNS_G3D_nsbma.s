	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; _end
	arm_func_start FUN_020BDB40
FUN_020BDB40: ; 0x020BDB40
	stmdb sp!, {r4-r8,lr}
	ldr r7, [r1, #0x8]
	mov r2, r2, lsl #0x10
	ldrh r4, [r7, #0xe]
	add r5, r7, #0x8
	ldr r6, [r1, #0x0]
	ldrh r3, [r5, r4]
	mov r1, r2, lsr #0x10
	add r2, r5, r4
	mul r4, r3, r1
	add r3, r2, #0x4
	mov r6, r6, asr #0xc
	mov r8, r0
	ldr r1, [r3, r4]
	mov r0, r7
	mov r2, r6
	add r5, r3, r4
	bl FUN_020BDDAC
	mov r4, r0
	ldr r1, [r5, #0x4]
	mov r0, r7
	mov r2, r6
	bl FUN_020BDDAC
	ldr r1, [r8, #0x4]
	mov r2, r6
	and r1, r1, #0x8000
	orr r1, r1, r4
	orr r0, r1, r0, lsl #0x10
	str r0, [r8, #0x4]
	mov r0, r7
	ldr r1, [r5, #0xc]
	bl FUN_020BDDAC
	mov r4, r0
	mov r0, r7
	ldr r1, [r5, #0x8]
	mov r2, r6
	bl FUN_020BDDAC
	mov r2, r6
	ldr r1, [r8, #0x8]
	and r1, r1, #0x8000
	orr r0, r1, r0
	orr r0, r0, r4, lsl #0x10
	str r0, [r8, #0x8]
	mov r0, r7
	ldr r1, [r5, #0x10]
	bl FUN_020BDCB8
	ldr r1, [r8, #0xc]
	bic r1, r1, #0x1f0000
	orr r0, r1, r0, lsl #0x10
	str r0, [r8, #0xc]
	ldmia sp!, {r4-r8,pc}
	arm_func_end FUN_020BDB40

	; NNSi_G3dAnmObjInitNsBma
	arm_func_start FUN_020BDC0C
FUN_020BDC0C: ; 0x020BDC0C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r3, _020BDCB4 ; =UNK_021065A8
	ldr r4, [r2, #0x8]
	ldr r3, [r3, #0x0]
	mov r9, r0
	str r3, [r9, #0xc]
	ldrb r0, [r2, #0x18]
	mov r8, r1
	add r4, r2, r4
	strb r0, [r9, #0x19]
	ldrb r2, [r9, #0x19]
	add r1, r9, #0x1a
	mov r0, #0x0
	mov r2, r2, lsl #0x1
	bl MIi_CpuClear16
	ldrb r0, [r8, #0x9]
	mov r7, #0x0
	cmp r0, #0x0
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r9,pc}
	mov r6, r7
	add r5, r8, #0x8
	add r4, r4, #0x4
_020BDC6C:
	ldrh r1, [r8, #0xe]
	mov r0, r4
	add r2, r5, r1
	ldrh r1, [r2, #0x2]
	add r1, r2, r1
	add r1, r1, r6
	bl FUN_020BC14C
	cmp r0, #0x0
	orrge r1, r7, #0x100
	addge r0, r9, r0, lsl #0x1
	strgeh r1, [r0, #0x1a]
	ldrb r0, [r8, #0x9]
	add r7, r7, #0x1
	add r6, r6, #0x10
	cmp r7, r0
	blo _020BDC6C
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020BDCB4: .word UNK_021065A8
	arm_func_end FUN_020BDC0C

	; GetMatColAnmuAlphaValue_
	arm_func_start FUN_020BDCB8
FUN_020BDCB8: ; 0x020BDCB8
	ands r3, r1, #0x20000000
	movne r0, r1, lsl #0x10
	movne r0, r0, lsr #0x10
	bxne lr
	ldr r3, _020BDDA4 ; =0x0000FFFF
	ands r12, r1, #0xc0000000
	and r3, r1, r3
	add r0, r0, r3
	ldreqb r0, [r0, r2]
	bxeq lr
	ldr r3, _020BDDA8 ; =0x1FFF0000
	ands r12, r1, #0x40000000
	and r1, r1, r3
	mov r3, r1, lsr #0x10
	beq _020BDD30
	ands r1, r2, #0x1
	beq _020BDD28
	cmp r2, r3
	addhi r0, r0, r3, lsr #0x1
	ldrhib r0, [r0, #0x1]
	bxhi lr
	add r1, r0, r2, lsr #0x1
	ldrb r2, [r0, r2, lsr #0x1]
	ldrb r0, [r1, #0x1]
	add r0, r2, r0
	mov r0, r0, lsl #0xf
	mov r0, r0, lsr #0x10
	bx lr
_020BDD28:
	ldrb r0, [r0, r2, lsr #0x1]
	bx lr
_020BDD30:
	ands r1, r2, #0x3
	beq _020BDD9C
	cmp r2, r3
	addhi r0, r0, r3, lsr #0x2
	ldrhib r0, [r1, r0]
	bxhi lr
	ands r1, r2, #0x1
	beq _020BDD80
	ands r1, r2, #0x2
	movne r1, r2, lsr #0x2
	addne r2, r1, #0x1
	moveq r2, r2, lsr #0x2
	addeq r1, r2, #0x1
	ldrb r2, [r0, r2]
	ldrb r1, [r0, r1]
	mov r0, #0x3
	mla r0, r2, r0, r1
	mov r0, r0, lsl #0xe
	mov r0, r0, lsr #0x10
	bx lr
_020BDD80:
	add r1, r0, r2, lsr #0x2
	ldrb r2, [r0, r2, lsr #0x2]
	ldrb r0, [r1, #0x1]
	add r0, r2, r0
	mov r0, r0, lsl #0xf
	mov r0, r0, lsr #0x10
	bx lr
_020BDD9C:
	ldrb r0, [r0, r2, lsr #0x2]
	bx lr
	.balign 4
_020BDDA4: .word 0x0000FFFF
_020BDDA8: .word 0x1FFF0000
	arm_func_end FUN_020BDCB8

	; GetMatColAnmValue_
	arm_func_start FUN_020BDDAC
FUN_020BDDAC: ; 0x020BDDAC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ands r3, r1, #0x20000000
	movne r0, r1, lsl #0x10
	addne sp, sp, #0x4
	movne r0, r0, lsr #0x10
	ldmneia sp!, {pc}
	ldr r3, _020BDF2C ; =0x0000FFFF
	ands r12, r1, #0xc0000000
	and r3, r1, r3
	add r0, r0, r3
	moveq r1, r2, lsl #0x1
	addeq sp, sp, #0x4
	ldreqh r0, [r0, r1]
	ldmeqia sp!, {pc}
	ldr r3, _020BDF30 ; =0x1FFF0000
	ands r12, r1, #0x40000000
	and r1, r1, r3
	mov r3, r1, lsr #0x10
	beq _020BDE34
	ands r1, r2, #0x1
	beq _020BDE24
	cmp r2, r3
	bichi r1, r3, #0x1
	addhi r0, r0, r1
	addhi sp, sp, #0x4
	ldrhih r0, [r0, #0x2]
	ldmhiia sp!, {pc}
	mov r1, r2, lsr #0x1
	b _020BDEE0
_020BDE24:
	bic r1, r2, #0x1
	add sp, sp, #0x4
	ldrh r0, [r0, r1]
	ldmia sp!, {pc}
_020BDE34:
	ands r1, r2, #0x3
	beq _020BDECC
	cmp r2, r3
	movhi r2, r3, lsr #0x2
	movhi r1, r1, lsl #0x1
	addhi r0, r0, r2, lsl #0x1
	addhi sp, sp, #0x4
	ldrhih r0, [r1, r0]
	ldmhiia sp!, {pc}
	ands r1, r2, #0x1
	beq _020BDEC4
	ands r1, r2, #0x2
	movne r1, r2, lsr #0x2
	addne r2, r1, #0x1
	moveq r2, r2, lsr #0x2
	addeq r1, r2, #0x1
	mov r2, r2, lsl #0x1
	mov r1, r1, lsl #0x1
	ldrh r12, [r0, r2]
	ldrh lr, [r0, r1]
	ldr r0, _020BDF34 ; =0x00007C1F
	and r3, r12, #0x3e0
	and r2, lr, #0x3e0
	mov r1, #0x3
	mla r2, r3, r1, r2
	and r12, r12, r0
	and r3, lr, r0
	mla r1, r12, r1, r3
	mov r2, r2, lsr #0x2
	and r1, r0, r1, lsr #0x2
	and r0, r2, #0x3e0
	orr r0, r1, r0
	mov r0, r0, lsl #0x10
	add sp, sp, #0x4
	mov r0, r0, lsr #0x10
	ldmia sp!, {pc}
_020BDEC4:
	mov r1, r2, lsr #0x2
	b _020BDEE0
_020BDECC:
	mov r1, r2, lsr #0x2
	mov r1, r1, lsl #0x1
	add sp, sp, #0x4
	ldrh r0, [r0, r1]
	ldmia sp!, {pc}
_020BDEE0:
	mov r2, r1, lsl #0x1
	add r1, r0, r1, lsl #0x1
	ldrh r3, [r0, r2]
	ldrh r12, [r1, #0x2]
	ldr r0, _020BDF34 ; =0x00007C1F
	and r2, r3, #0x3e0
	and r1, r12, #0x3e0
	add r1, r2, r1
	mov r1, r1, lsr #0x1
	and r3, r3, r0
	and r2, r12, r0
	add r2, r3, r2
	and r2, r0, r2, lsr #0x1
	and r0, r1, #0x3e0
	orr r0, r2, r0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020BDF2C: .word 0x0000FFFF
_020BDF30: .word 0x1FFF0000
_020BDF34: .word 0x00007C1F
	arm_func_end FUN_020BDDAC

