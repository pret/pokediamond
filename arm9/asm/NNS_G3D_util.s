	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; NNS_G3dWorldPosToScrPos
	arm_func_start FUN_020BB408
FUN_020BB408: ; 0x020BB408
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x1c
	mov r5, r1
	mov r4, r2
	ldr r6, _020BB594 ; =UNK_021CED20
	ldr r1, _020BB598 ; =UNK_021CED64
	add r2, sp, #0x10
	bl MTX_MultVec43
	ldr r1, [sp, #0x14]
	ldr r0, [r6, #0x1c]
	ldr r2, [sp, #0x10]
	smull r8, r7, r1, r0
	ldr r0, [r6, #0xc]
	ldr r3, [sp, #0x18]
	smlal r8, r7, r2, r0
	ldr r1, [r6, #0x2c]
	ldr r0, [r6, #0x3c]
	smlal r8, r7, r3, r1
	mov r1, r8, lsr #0xc
	orr r1, r1, r7, lsl #0x14
	add r0, r1, r0
	bl FX_InvAsync
	ldr r2, [sp, #0x14]
	ldr r1, [r6, #0x10]
	ldr r0, [r6, #0x14]
	smull lr, r8, r2, r1
	smull r12, r9, r2, r0
	ldr r1, [sp, #0x10]
	ldr r3, [r6, #0x0]
	ldr r0, [sp, #0x18]
	smlal lr, r8, r1, r3
	ldr r7, [r6, #0x20]
	ldr r2, [r6, #0x30]
	smlal lr, r8, r0, r7
	mov r3, lr, lsr #0xc
	orr r3, r3, r8, lsl #0x14
	add r7, r3, r2
	ldr r3, [r6, #0x4]
	ldr r8, [r6, #0x24]
	smlal r12, r9, r1, r3
	smlal r12, r9, r0, r8
	mov r0, r12, lsr #0xc
	ldr r2, [r6, #0x34]
	orr r0, r0, r9, lsl #0x14
	add r6, r0, r2
	bl FX_GetDivResultFx64c
	mov r2, r7, asr #0x1f
	umull r9, lr, r0, r7
	mla lr, r0, r2, lr
	mov r3, #0x80000000
	mla lr, r1, r7, lr
	adds r9, r9, r3
	adc r2, lr, #0x0
	add r2, r2, #0x1000
	add r2, r2, r2, lsr #0x1f
	mov r7, r2, asr #0x1
	umull lr, r2, r0, r6
	mov r12, r6, asr #0x1f
	mla r2, r0, r12, r2
	mla r2, r1, r6, r2
	adds r3, lr, r3
	adc r0, r2, #0x0
	add r0, r0, #0x1000
	add r0, r0, r0, lsr #0x1f
	mov r8, #0x0
	mov r6, r0, asr #0x1
	cmp r7, #0x0
	blt _020BB530
	cmp r6, #0x0
	blt _020BB530
	cmp r7, #0x1000
	bgt _020BB530
	cmp r6, #0x1000
	ble _020BB534
_020BB530:
	mvn r8, #0x0
_020BB534:
	add r0, sp, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x8
	add r3, sp, #0xc
	bl FUN_020B8200
	ldr r2, [sp, #0x0]
	ldr r0, [sp, #0x8]
	ldr r12, [sp, #0xc]
	sub r0, r0, r2
	mul r0, r7, r0
	add r1, r0, #0x800
	ldr r3, [sp, #0x4]
	add r1, r2, r1, asr #0xc
	sub r0, r12, r3
	mul r0, r6, r0
	str r1, [r5, #0x0]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x800
	rsb r1, r1, #0xbf
	sub r1, r1, r0, asr #0xc
	mov r0, r8
	str r1, [r4, #0x0]
	add sp, sp, #0x1c
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020BB594: .word UNK_021CED20
_020BB598: .word UNK_021CED64
	arm_func_end FUN_020BB408

	; NNS_G3dResDefaultSetup
	arm_func_start FUN_020BB59C
FUN_020BB59C: ; 0x020BB59C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r1, [r5, #0x0]
	ldr r0, _020BB7C8 ; =0x30415642
	cmp r1, r0
	bhi _020BB5F4
	cmp r1, r0
	bhs _020BB7B0
	ldr r0, _020BB7CC ; =0x30414D42
	cmp r1, r0
	bhi _020BB5E4
	cmp r1, r0
	bhs _020BB7B0
	ldr r0, _020BB7D0 ; =0x30414342
	cmp r1, r0
	beq _020BB7B0
	b _020BB7BC
_020BB5E4:
	ldr r0, _020BB7D4 ; =0x30415442
	cmp r1, r0
	beq _020BB7B0
	b _020BB7BC
_020BB5F4:
	ldr r0, _020BB7D8 ; =0x30505442
	cmp r1, r0
	bhi _020BB618
	cmp r1, r0
	bhs _020BB7B0
	ldr r0, _020BB7DC ; =0x30444D42
	cmp r1, r0
	beq _020BB624
	b _020BB7BC
_020BB618:
	ldr r0, _020BB7E0 ; =0x30585442
	cmp r1, r0
	bne _020BB7BC
_020BB624:
	mov r11, #0x1
	mov r0, r5
	mov r9, r11
	mov r8, r11
	bl FUN_020BC0FC
	movs r4, r0
	beq _020BB77C
	bl FUN_020B7E1C
	mov r7, r0
	mov r0, r4
	bl FUN_020B7E10
	mov r6, r0
	mov r0, r4
	bl FUN_020B7CE4
	mov r10, r0
	cmp r7, #0x0
	beq _020BB68C
	ldr r0, _020BB7E4 ; =UNK_021064B8
	mov r1, #0x0
	ldr r3, [r0, #0x0]
	mov r0, r7
	mov r2, r1
	blx r3
	movs r7, r0
	moveq r11, #0x0
	b _020BB690
_020BB68C:
	mov r7, #0x0
_020BB690:
	cmp r6, #0x0
	beq _020BB6BC
	ldr r1, _020BB7E4 ; =UNK_021064B8
	mov r0, r6
	ldr r3, [r1, #0x0]
	mov r1, #0x1
	mov r2, #0x0
	blx r3
	movs r6, r0
	moveq r9, #0x0
	b _020BB6C0
_020BB6BC:
	mov r6, #0x0
_020BB6C0:
	cmp r10, #0x0
	beq _020BB6F0
	ldr r1, _020BB7E8 ; =UNK_021064C0
	ldrh r2, [r4, #0x20]
	ldr r3, [r1, #0x0]
	mov r0, r10
	and r1, r2, #0x8000
	mov r2, #0x0
	blx r3
	movs r10, r0
	moveq r8, #0x0
	b _020BB6F4
_020BB6F0:
	mov r10, #0x0
_020BB6F4:
	cmp r11, #0x0
	beq _020BB70C
	cmp r9, #0x0
	beq _020BB70C
	cmp r8, #0x0
	bne _020BB748
_020BB70C:
	ldr r1, _020BB7EC ; =UNK_021064C4
	mov r0, r10
	ldr r1, [r1, #0x0]
	blx r1
	ldr r1, _020BB7F0 ; =UNK_021064BC
	mov r0, r6
	ldr r1, [r1, #0x0]
	blx r1
	ldr r1, _020BB7F0 ; =UNK_021064BC
	mov r0, r7
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_020BB748:
	mov r0, r4
	mov r1, r7
	mov r2, r6
	bl FUN_020B7DFC
	mov r0, r4
	mov r1, r10
	bl FUN_020B7CDC
	mov r0, r4
	mov r1, #0x1
	bl FUN_020B7D28
	mov r0, r4
	mov r1, #0x1
	bl FUN_020B7C78
_020BB77C:
	ldr r1, [r5, #0x0]
	ldr r0, _020BB7DC ; =0x30444D42
	cmp r1, r0
	bne _020BB7A4
	mov r0, r5
	bl FUN_020BC13C
	cmp r4, #0x0
	beq _020BB7A4
	mov r1, r4
	bl FUN_020B7790
_020BB7A4:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_020BB7B0:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_020BB7BC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020BB7C8: .word 0x30415642
_020BB7CC: .word 0x30414D42
_020BB7D0: .word 0x30414342
_020BB7D4: .word 0x30415442
_020BB7D8: .word 0x30505442
_020BB7DC: .word 0x30444D42
_020BB7E0: .word 0x30585442
_020BB7E4: .word UNK_021064B8
_020BB7E8: .word UNK_021064C0
_020BB7EC: .word UNK_021064C4
_020BB7F0: .word UNK_021064BC
	arm_func_end FUN_020BB59C

	; NNS_G3dInit
	arm_func_start FUN_020BB7F4
FUN_020BB7F4: ; 0x020BB7F4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl G3X_Init
	bl FUN_020B84D8
	ldr r1, _020BB820 ; =0x04000600
	ldr r0, [r1, #0x0]
	bic r0, r0, #0xc0000000
	orr r0, r0, #0x80000000
	str r0, [r1, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020BB820: .word 0x04000600
	arm_func_end FUN_020BB7F4

	; NNS_G3dGetCurrentMtx
	arm_func_start FUN_020BB824
FUN_020BB824: ; 0x020BB824
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x40
	mov r6, r0
	mov r5, r1
	bl FUN_020BB394
	ldr r0, _020BB8B4 ; =0x04000440
	mov r2, #0x0
	ldr r1, _020BB8B8 ; =0x04000444
	str r2, [r0, #0x0]
	ldr r0, _020BB8BC ; =0x04000454
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	cmp r6, #0x0
	beq _020BB87C
	add r4, sp, #0x0
_020BB860:
	mov r0, r4
	bl G3X_GetClipMtx
	cmp r0, #0x0
	bne _020BB860
	add r0, sp, #0x0
	mov r1, r6
	bl MTX_Copy44To43_
_020BB87C:
	cmp r5, #0x0
	beq _020BB894
_020BB884:
	mov r0, r5
	bl G3X_GetVectorMtx
	cmp r0, #0x0
	bne _020BB884
_020BB894:
	ldr r1, _020BB8C0 ; =0x04000448
	mov r2, #0x1
	ldr r0, _020BB8B4 ; =0x04000440
	str r2, [r1, #0x0]
	mov r1, #0x2
	str r1, [r0, #0x0]
	add sp, sp, #0x40
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020BB8B4: .word 0x04000440
_020BB8B8: .word 0x04000444
_020BB8BC: .word 0x04000454
_020BB8C0: .word 0x04000448
	arm_func_end FUN_020BB824

