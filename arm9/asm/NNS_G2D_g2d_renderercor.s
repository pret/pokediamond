	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	; mtxIdentity_
	.global UNK_020FF958
UNK_020FF958: ; 0x020FF958
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	; static const in function
	.section .bss

	; pTheInstance_
	.global UNK_021CED14
UNK_021CED14: ; 0x021CED14
	.space 0x4

	.section .text

	; NNS_G2dRndCoreDrawCellVramTransfer
	arm_func_start FUN_020B4BF4
FUN_020B4BF4: ; 0x020B4BF4
	stmdb sp!, {r4-r6,lr}
	ldr r2, _020B4CD8 ; =UNK_021CED14
	mov r6, r0
	ldr r3, [r2, #0x0]
	mov r4, r1
	ldr r5, [r3, #0x0]
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	mov r0, #0x1
	str r0, [r3, #0x30]
	ldr r3, [r5, #0x18]
	cmp r3, #0x0
	beq _020B4C38
	ldr r0, [r2, #0x0]
	mov r1, r6
	blx r3
_020B4C38:
	ldr r0, _020B4CD8 ; =UNK_021CED14
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x30]
	cmp r0, #0x0
	beq _020B4CB8
	mvn r0, #0x0
	cmp r4, r0
	beq _020B4C7C
	mov r0, r4
	ldr r4, [r5, #0x14]
	bl FUN_020B469C
	mov r3, #0x1
	mvn r1, r3, lsl r4
	ldr r2, [r0, #0x20]
	and r1, r2, r1
	orr r1, r1, r3, lsl r4
	str r1, [r0, #0x20]
_020B4C7C:
	ldr r0, [r5, #0x14]
	cmp r0, #0x3
	addls pc, pc, r0, lsl #0x2
	b _020B4CB8
	; Jump table
	b _020B4C9C ; case 0
	b _020B4CAC ; case 1
	b _020B4CAC ; case 2
	b _020B4CB8 ; case 3
_020B4C9C:
	mov r0, r5
	mov r1, r6
	bl FUN_020B5090
	b _020B4CB8
_020B4CAC:
	mov r0, r5
	mov r1, r6
	bl FUN_020B53B4
_020B4CB8:
	ldr r2, [r5, #0x1c]
	cmp r2, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r0, _020B4CD8 ; =UNK_021CED14
	mov r1, r6
	ldr r0, [r0, #0x0]
	blx r2
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B4CD8: .word UNK_021CED14
	arm_func_end FUN_020B4BF4

	; NNS_G2dRndCoreDrawCell
	arm_func_start FUN_020B4CDC
FUN_020B4CDC: ; 0x020B4CDC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _020B4D9C ; =UNK_021CED14
	mov r5, r0
	ldr r2, [r1, #0x0]
	ldr r4, [r2, #0x0]
	ldr r0, [r4, #0x10]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
	mov r0, #0x1
	str r0, [r2, #0x30]
	ldr r2, [r4, #0x18]
	cmp r2, #0x0
	beq _020B4D24
	ldr r0, [r1, #0x0]
	mov r1, r5
	blx r2
_020B4D24:
	ldr r0, _020B4D9C ; =UNK_021CED14
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x30]
	cmp r0, #0x0
	beq _020B4D74
	ldr r0, [r4, #0x14]
	cmp r0, #0x3
	addls pc, pc, r0, lsl #0x2
	b _020B4D74
	; Jump table
	b _020B4D58 ; case 0
	b _020B4D68 ; case 1
	b _020B4D68 ; case 2
	b _020B4D74 ; case 3
_020B4D58:
	mov r0, r4
	mov r1, r5
	bl FUN_020B5090
	b _020B4D74
_020B4D68:
	mov r0, r4
	mov r1, r5
	bl FUN_020B53B4
_020B4D74:
	ldr r2, [r4, #0x1c]
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
	ldr r0, _020B4D9C ; =UNK_021CED14
	mov r1, r5
	ldr r0, [r0, #0x0]
	blx r2
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B4D9C: .word UNK_021CED14
	arm_func_end FUN_020B4CDC

	; NNS_G2dRndCoreEndRendering
	arm_func_start FUN_020B4DA0
FUN_020B4DA0: ; 0x020B4DA0
	ldr r0, _020B4E00 ; =UNK_021CED14
	ldr r3, [r0, #0x0]
	ldr r1, [r3, #0x0]
	ldr r1, [r1, #0x14]
	cmp r1, #0x0
	bne _020B4DD8
	ldr r2, _020B4E04 ; =0x04000440
	mov r1, #0x0
	ldr r0, _020B4E08 ; =0x04000448
	str r1, [r2, #0x0]
	mov r1, #0x1
	str r1, [r0, #0x0]
	str r1, [r2, #0x0]
	b _020B4DF0
_020B4DD8:
	mov r2, #0x0
	str r2, [r3, #0x10]
	ldr r1, [r0, #0x0]
	str r2, [r1, #0x2c]
	ldr r0, [r0, #0x0]
	str r2, [r0, #0x28]
_020B4DF0:
	ldr r0, _020B4E00 ; =UNK_021CED14
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020B4E00: .word UNK_021CED14
_020B4E04: .word 0x04000440
_020B4E08: .word 0x04000448
	arm_func_end FUN_020B4DA0

	; NNS_G2dRndCoreBeginRendering
	arm_func_start FUN_020B4E0C
FUN_020B4E0C: ; 0x020B4E0C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r2, _020B4F28 ; =UNK_021CED14
	mov r4, r0
	str r4, [r2, #0x0]
	ldr r0, [r4, #0x0]
	ldr r5, [r0, #0x14]
	cmp r5, #0x0
	bne _020B4ED8
	ldr lr, _020B4F2C ; =0x04000440
	mov r1, #0x0
	ldr r0, _020B4F30 ; =0x04000444
	str r1, [lr, #0x0]
	str r1, [r0, #0x0]
	ldr r12, [r4, #0x0]
	ldr r0, _020B4F34 ; =0x04000470
	ldr r3, [r12, #0x0]
	ldr r12, [r12, #0x4]
	rsb r3, r3, #0x0
	str r3, [r0, #0x0]
	rsb r3, r12, #0x0
	str r3, [r0, #0x0]
	str r1, [r0, #0x0]
	mov r0, #0x1
	str r0, [lr, #0x0]
	ldr r0, [r2, #0x0]
	ldr r5, [r0, #0x8]
	mov r0, r5
	bl FUN_020B19FC
	cmp r0, #0x0
	moveq r0, #0x0
	beq _020B4E98
	mov r0, r5
	mov r1, #0x0
	bl FUN_020B1A14
_020B4E98:
	ldr r1, _020B4F28 ; =UNK_021CED14
	str r0, [r4, #0x14]
	ldr r0, [r1, #0x0]
	mov r1, #0x0
	ldr r5, [r0, #0xc]
	mov r0, r5
	bl FUN_020B19A8
	cmp r0, #0x0
	moveq r0, #0x0
	beq _020B4ECC
	mov r0, r5
	mov r1, #0x0
	bl FUN_020B19C4
_020B4ECC:
	add sp, sp, #0x4
	str r0, [r4, #0x18]
	ldmia sp!, {r4-r5,pc}
_020B4ED8:
	ldr r4, [r4, #0x8]
	mov r1, r5
	mov r0, r4
	bl FUN_020B19FC
	cmp r0, #0x0
	moveq r1, #0x0
	beq _020B4F14
	mov r0, r4
	mov r1, r5
	bl FUN_020B1A14
	ldr r1, [r4, #0x20]
	and r1, r1, #0x700000
	mov r1, r1, asr #0x14
	add r1, r1, #0x5
	mov r1, r0, lsr r1
_020B4F14:
	ldr r0, _020B4F28 ; =UNK_021CED14
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B4F28: .word UNK_021CED14
_020B4F2C: .word 0x04000440
_020B4F30: .word 0x04000444
_020B4F34: .word 0x04000470
	arm_func_end FUN_020B4E0C

	; _end
	arm_func_start FUN_020B4F38
FUN_020B4F38: ; 0x020B4F38
	cmp r1, #0x0
	ldrne r1, [r0, #0x24]
	orrne r1, r1, #0x1
	strne r1, [r0, #0x24]
	ldreq r1, [r0, #0x24]
	biceq r1, r1, #0x1
	streq r1, [r0, #0x24]
	cmp r2, #0x0
	ldrne r1, [r0, #0x24]
	orrne r1, r1, #0x2
	strne r1, [r0, #0x24]
	ldreq r1, [r0, #0x24]
	biceq r1, r1, #0x2
	streq r1, [r0, #0x24]
	bx lr
	arm_func_end FUN_020B4F38

	; _end
	arm_func_start FUN_020B4F74
FUN_020B4F74: ; 0x020B4F74
	ldr r0, [r0, #0x24]
	ands r0, r0, #0x2
	movne r0, #0x1
	moveq r0, #0x0
	bx lr
	arm_func_end FUN_020B4F74

	; _end
	arm_func_start FUN_020B4F88
FUN_020B4F88: ; 0x020B4F88
	ldr r0, [r0, #0x24]
	ands r0, r0, #0x1
	movne r0, #0x1
	moveq r0, #0x0
	bx lr
	arm_func_end FUN_020B4F88

	; _end
	arm_func_start FUN_020B4F9C
FUN_020B4F9C: ; 0x020B4F9C
	str r1, [r0, #0x0]
	bx lr
	arm_func_end FUN_020B4F9C

	; _end
	arm_func_start FUN_020B4FA4
FUN_020B4FA4: ; 0x020B4FA4
	str r1, [r0, #0x34]
	bx lr
	arm_func_end FUN_020B4FA4

	; NNS_G2dSetRndCoreCurrentMtx2D
	arm_func_start FUN_020B4FAC
FUN_020B4FAC: ; 0x020B4FAC
	ldr r2, _020B4FC0 ; =UNK_021CED14
	ldr r2, [r2, #0x0]
	str r0, [r2, #0x2c]
	str r1, [r2, #0x28]
	bx lr
	.balign 4
_020B4FC0: .word UNK_021CED14
	arm_func_end FUN_020B4FAC

	; NNS_G2dSetRndCoreCurrentMtx3D
	arm_func_start FUN_020B4FC4
FUN_020B4FC4: ; 0x020B4FC4
	ldr r1, _020B5028 ; =UNK_021CED14
	mov r3, #0x0
	ldr r12, [r1, #0x0]
	mov r1, #0x1000
	str r0, [r12, #0x2c]
	ldr r2, [r0, #0x0]
	str r2, [r12, #0x40]
	ldr r2, [r0, #0x4]
	str r2, [r12, #0x44]
	str r3, [r12, #0x48]
	ldr r2, [r0, #0x8]
	str r2, [r12, #0x4c]
	ldr r2, [r0, #0xc]
	str r2, [r12, #0x50]
	str r3, [r12, #0x54]
	str r3, [r12, #0x58]
	str r3, [r12, #0x5c]
	str r1, [r12, #0x60]
	ldr r1, [r0, #0x10]
	str r1, [r12, #0x64]
	ldr r0, [r0, #0x14]
	str r0, [r12, #0x68]
	ldr r0, [r12, #0x34]
	str r0, [r12, #0x6c]
	bx lr
	.balign 4
_020B5028: .word UNK_021CED14
	arm_func_end FUN_020B4FC4

	; _end
	arm_func_start FUN_020B502C
FUN_020B502C: ; 0x020B502C
	str r1, [r0, #0x4]
	bx lr
	arm_func_end FUN_020B502C

	; _end
	arm_func_start FUN_020B5034
FUN_020B5034: ; 0x020B5034
	str r1, [r0, #0x1c]
	str r2, [r0, #0x20]
	bx lr
	arm_func_end FUN_020B5034

	; _end
	arm_func_start FUN_020B5040
FUN_020B5040: ; 0x020B5040
	str r1, [r0, #0x8]
	str r2, [r0, #0xc]
	bx lr
	arm_func_end FUN_020B5040

	; _end
	arm_func_start FUN_020B504C
FUN_020B504C: ; 0x020B504C
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r1, r4
	mov r0, #0x0
	mov r2, #0x70
	bl MIi_CpuClear16
	mov r1, #0x0
	str r1, [r4, #0x0]
	mov r0, #0x2
	str r0, [r4, #0x4]
	str r1, [r4, #0x8]
	str r1, [r4, #0xc]
	str r1, [r4, #0x24]
	mov r0, #0x1
	str r0, [r4, #0x30]
	str r1, [r4, #0x28]
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020B504C

	; DrawCellToSurface3D_
	arm_func_start FUN_020B5090
FUN_020B5090: ; 0x020B5090
	stmdb sp!, {r4-r10,lr}
	ldr r5, _020B5158 ; =UNK_021CED14
	mov r9, r1
	ldrh r1, [r9, #0x0]
	ldr r2, [r5, #0x0]
	mov r10, r0
	add r7, r2, #0x38
	mov r8, #0x0
	cmp r1, #0x0
	ldmlsia sp!, {r4-r10,pc}
	mov r6, #0x1
	mov r4, #0x6
_020B50C0:
	mul r1, r8, r4
	ldr r0, [r5, #0x0]
	str r6, [r0, #0x30]
	ldr r2, [r9, #0x4]
	ldrh r0, [r2, r1]
	add r1, r2, r1
	strh r0, [r7, #0x0]
	ldrh r0, [r1, #0x2]
	strh r0, [r7, #0x2]
	ldrh r0, [r1, #0x4]
	strh r0, [r7, #0x4]
	ldr r3, [r10, #0x20]
	cmp r3, #0x0
	beq _020B5108
	ldr r0, [r5, #0x0]
	mov r1, r9
	mov r2, r8
	blx r3
_020B5108:
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x30]
	cmp r0, #0x0
	beq _020B5120
	mov r0, r7
	bl FUN_020B515C
_020B5120:
	ldr r3, [r10, #0x24]
	cmp r3, #0x0
	beq _020B513C
	ldr r0, [r5, #0x0]
	mov r1, r9
	mov r2, r8
	blx r3
_020B513C:
	add r0, r8, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r9, #0x0]
	mov r8, r0, lsr #0x10
	cmp r8, r1
	blo _020B50C0
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020B5158: .word UNK_021CED14
	arm_func_end FUN_020B5090

	; DrawOamToSurface3D_
	arm_func_start FUN_020B515C
FUN_020B515C: ; 0x020B515C
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	ldr r1, _020B53A4 ; =UNK_021CED14
	mov r7, r0
	ldr r0, [r1, #0x0]
	add r0, r0, #0x40
	bl G3_LoadMtx43
	ldr r0, _020B53A4 ; =UNK_021CED14
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x24]
	cmp r1, #0x0
	beq _020B533C
	ldr r2, [r7, #0x0]
	ldr r1, _020B53A8 ; =0xC000C000
	and r4, r2, r1
	bl FUN_020B4F88
	cmp r0, #0x0
	beq _020B51F4
	ldr r0, [r7, #0x0]
	and r2, r4, #0xc000
	mov r0, r0, lsl #0x7
	mov r3, r0, lsr #0x17
	and r1, r4, #0xc0000000
	mov r1, r1, lsr #0x1e
	ldr r0, _020B53AC ; =UNK_020FF8AC
	mov r2, r2, asr #0xe
	mov r1, r1, lsl #0x1
	add r0, r0, r2, lsl #0x3
	cmp r3, #0xff
	ldrh r1, [r1, r0]
	orrgt r0, r3, #0xff00
	movgt r0, r0, lsl #0x10
	movgt r3, r0, asr #0x10
	add r0, r3, r1
	rsb r0, r0, #0x0
	mov r0, r0, lsl #0x10
	mov r1, r0, lsr #0x10
	b _020B5218
_020B51F4:
	ldr r0, [r7, #0x0]
	mov r0, r0, lsl #0x7
	mov r0, r0, lsr #0x17
	cmp r0, #0xff
	orrgt r0, r0, #0xff00
	movgt r0, r0, lsl #0x10
	movgt r0, r0, asr #0x10
	mov r0, r0, lsl #0x10
	mov r1, r0, lsr #0x10
_020B5218:
	ldr r0, _020B53A4 ; =UNK_021CED14
	mov r1, r1, lsl #0x10
	ldr r0, [r0, #0x0]
	mov r6, r1, asr #0x10
	bl FUN_020B4F74
	cmp r0, #0x0
	beq _020B527C
	and r1, r4, #0xc000
	and r0, r4, #0xc0000000
	ldrb r4, [r7, #0x0]
	ldr r2, _020B53B0 ; =UNK_020FF894
	mov r0, r0, lsr #0x1e
	mov r3, r1, asr #0xe
	mov r1, r0, lsl #0x1
	add r0, r2, r3, lsl #0x3
	cmp r4, #0x7f
	ldrh r1, [r1, r0]
	orrgt r0, r4, #0xff00
	movgt r0, r0, lsl #0x10
	movgt r4, r0, asr #0x10
	add r0, r4, r1
	rsb r0, r0, #0x0
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0x10
	b _020B5298
_020B527C:
	ldrb r0, [r7, #0x0]
	cmp r0, #0x7f
	orrgt r0, r0, #0xff00
	movgt r0, r0, lsl #0x10
	movgt r0, r0, asr #0x10
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0x10
_020B5298:
	ldr r0, _020B53A4 ; =UNK_021CED14
	ldr r1, [r7, #0x0]
	ldr r0, [r0, #0x0]
	mov r5, r1, lsl #0x3
	bl FUN_020B4F88
	ldr r2, [r7, #0x0]
	ldr r1, _020B53A4 ; =UNK_021CED14
	eor r5, r0, r5, lsr #0x1f
	ldr r0, [r1, #0x0]
	mov r8, r2, lsl #0x2
	bl FUN_020B4F74
	ldr r2, [r7, #0x0]
	eor r1, r0, r8, lsr #0x1f
	bic r0, r2, #0x10000000
	str r0, [r7, #0x0]
	ldr r2, [r7, #0x0]
	ldr r3, _020B53A4 ; =UNK_021CED14
	orr r2, r2, r5, lsl #0x1c
	str r2, [r7, #0x0]
	ldr r2, [r7, #0x0]
	mov r0, r6
	bic r2, r2, #0x20000000
	str r2, [r7, #0x0]
	ldr r5, [r7, #0x0]
	mov r2, r4, lsl #0x10
	orr r1, r5, r1, lsl #0x1d
	str r1, [r7, #0x0]
	ldr r5, [r3, #0x0]
	mov r1, r2, asr #0x10
	ldr r4, [r5, #0x8]
	mov r3, r7
	add r2, r4, #0xc
	str r2, [sp, #0x0]
	ldr r4, [r5, #0x14]
	mvn r2, #0x0
	str r4, [sp, #0x4]
	ldr r4, [r5, #0x18]
	str r4, [sp, #0x8]
	bl FUN_020B46B4
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}
_020B533C:
	ldr r2, _020B53A4 ; =UNK_021CED14
	ldr r0, [r7, #0x0]
	ldr r5, [r2, #0x0]
	mov r0, r0, lsl #0x7
	ldr r4, [r5, #0x8]
	mov r0, r0, lsr #0x17
	cmp r0, #0xff
	orrgt r0, r0, #0xff00
	movgt r0, r0, lsl #0x10
	ldrb r1, [r7, #0x0]
	add r4, r4, #0xc
	movgt r0, r0, asr #0x10
	str r4, [sp, #0x0]
	ldr r4, [r5, #0x14]
	cmp r1, #0x7f
	orrgt r1, r1, #0xff00
	movgt r1, r1, lsl #0x10
	str r4, [sp, #0x4]
	ldr r4, [r5, #0x18]
	movgt r1, r1, asr #0x10
	mov r3, r7
	mvn r2, #0x0
	str r4, [sp, #0x8]
	bl FUN_020B46B4
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020B53A4: .word UNK_021CED14
_020B53A8: .word 0xC000C000
_020B53AC: .word UNK_020FF8AC
_020B53B0: .word UNK_020FF894
	arm_func_end FUN_020B515C

	; DrawCellToSurface2D_
	arm_func_start FUN_020B53B4
FUN_020B53B4: ; 0x020B53B4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x44
	ldr r2, _020B57B0 ; =UNK_021CED14
	mov r10, r0
	ldr r0, [r2, #0x0]
	mov r11, r1
	ldr r9, [r0, #0x2c]
	ldr r1, _020B57B0 ; =UNK_021CED14
	cmp r9, #0x0
	ldreq sb, _020B57B4 ; =UNK_020FF958
	ldr r3, [r1, #0x0]
	ldr r4, [r9, #0x10]
	str r4, [sp, #0x18]
	ldr r2, [r9, #0x14]
	str r2, [sp, #0x1c]
	ldr r1, [r10, #0x0]
	sub r1, r4, r1
	str r1, [sp, #0x18]
	ldr r1, [r10, #0x4]
	sub r1, r2, r1
	str r1, [sp, #0x1c]
	ldr r2, [r3, #0x24]
	ldr r1, [r3, #0x10]
	cmp r2, #0x0
	str r1, [sp, #0x4]
	bne _020B5430
	ldr r1, [r3, #0x28]
	cmp r1, #0x0
	movne r1, #0x1
	strne r1, [sp, #0x0]
	bne _020B5438
_020B5430:
	mov r1, #0x0
	str r1, [sp, #0x0]
_020B5438:
	ldrh r1, [r11, #0x0]
	add r7, r0, #0x38
	mov r8, #0x0
	cmp r1, #0x0
	addls sp, sp, #0x44
	ldmlsia sp!, {r4-r11,pc}
	mov r0, #0x1
	ldr r4, _020B57B0 ; =UNK_021CED14
	str r8, [sp, #0x14]
	str r0, [sp, #0xc]
_020B5460:
	ldr r2, [r4, #0x0]
	ldr r0, [sp, #0xc]
	mov r1, #0x6
	str r0, [r2, #0x30]
	mul r0, r8, r1
	ldr r1, [r11, #0x4]
	add r2, r1, r0
	ldrh r0, [r1, r0]
	strh r0, [r7, #0x0]
	ldrh r0, [r2, #0x2]
	strh r0, [r7, #0x2]
	ldrh r0, [r2, #0x4]
	strh r0, [r7, #0x4]
	ldr r3, [r10, #0x20]
	cmp r3, #0x0
	beq _020B54B0
	ldr r0, [r4, #0x0]
	mov r1, r11
	mov r2, r8
	blx r3
_020B54B0:
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x30]
	cmp r0, #0x0
	beq _020B5790
	ldr r0, [sp, #0x0]
	ldr r1, [r7, #0x4]
	cmp r0, #0x0
	mov r0, #0x400
	rsb r0, r0, #0x0
	and r2, r1, r0
	ldr r0, [sp, #0x4]
	mov r1, r1, lsl #0x16
	add r1, r0, r1, lsr #0x16
	ldr r0, _020B57B8 ; =0x000003FF
	and r0, r1, r0
	orr r0, r2, r0
	str r0, [r7, #0x4]
	beq _020B5600
	ldr r0, [r10, #0x14]
	ldr lr, [r4, #0x0]
	sub r1, r0, #0x1
	ldr r0, [r7, #0x0]
	ldr r6, [lr, #0x28]
	mov r2, r0, lsl #0x2
	mov r2, r2, lsr #0x1f
	mov r2, r2, lsl #0x1
	mov r0, r0, lsl #0x3
	orr r5, r2, r0, lsr #0x1f
	add r0, r6, r5, lsl #0x2
	add r0, r0, r1, lsl #0x1
	ldrh r1, [r0, #0x10]
	ldr r0, _020B57BC ; =0x0000FFFF
	str r1, [sp, #0x8]
	cmp r1, r0
	bne _020B55CC
	cmp r5, #0x0
	bne _020B5558
	ldr r1, [lr, #0x20]
	mov r0, r6
	blx r1
	str r0, [sp, #0x8]
	b _020B55B4
_020B5558:
	ands r0, r5, #0x1
	add r12, sp, #0x30
	ldmia r6, {r0-r3}
	stmia r12, {r0-r3}
	beq _020B5584
	ldr r1, [sp, #0x30]
	ldr r0, [sp, #0x34]
	rsb r1, r1, #0x0
	str r1, [sp, #0x30]
	rsb r0, r0, #0x0
	str r0, [sp, #0x34]
_020B5584:
	ands r0, r5, #0x2
	beq _020B55A4
	ldr r1, [sp, #0x38]
	ldr r0, [sp, #0x3c]
	rsb r1, r1, #0x0
	str r1, [sp, #0x38]
	rsb r0, r0, #0x0
	str r0, [sp, #0x3c]
_020B55A4:
	ldr r1, [lr, #0x20]
	add r0, sp, #0x30
	blx r1
	str r0, [sp, #0x8]
_020B55B4:
	ldr r1, [r10, #0x14]
	add r0, r6, r5, lsl #0x2
	sub r1, r1, #0x1
	add r1, r0, r1, lsl #0x1
	ldr r0, [sp, #0x8]
	strh r0, [r1, #0x10]
_020B55CC:
	ldr r1, [r9, #0x0]
	add r0, sp, #0x20
	str r1, [sp, #0x20]
	ldr r2, [r9, #0x4]
	mov r1, r7
	str r2, [sp, #0x24]
	ldr r3, [r9, #0x8]
	add r2, sp, #0x18
	str r3, [sp, #0x28]
	ldr r3, [r9, #0xc]
	str r3, [sp, #0x2c]
	bl FUN_020B57D8
	b _020B5750
_020B5600:
	ldr r0, _020B57C0 ; =0x0000FFFE
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x0]
	ldr r1, [r0, #0x24]
	cmp r1, #0x0
	beq _020B5714
	ldr r2, [r7, #0x0]
	ldr r1, _020B57C4 ; =0xC000C000
	mov r6, r2, lsl #0x3
	and r5, r2, r1
	bl FUN_020B4F88
	ldr r1, [r7, #0x0]
	eor r6, r0, r6, lsr #0x1f
	mov r1, r1, lsl #0x2
	ldr r0, [r4, #0x0]
	str r1, [sp, #0x10]
	bl FUN_020B4F74
	ldr r1, [sp, #0x10]
	eor r0, r0, r1, lsr #0x1f
	ldr r1, [r7, #0x0]
	bic r1, r1, #0x10000000
	str r1, [r7, #0x0]
	ldr r1, [r7, #0x0]
	orr r1, r1, r6, lsl #0x1c
	str r1, [r7, #0x0]
	ldr r1, [r7, #0x0]
	bic r1, r1, #0x20000000
	str r1, [r7, #0x0]
	ldr r1, [r7, #0x0]
	orr r0, r1, r0, lsl #0x1d
	str r0, [r7, #0x0]
	ldr r0, [r4, #0x0]
	bl FUN_020B4F88
	cmp r0, #0x0
	beq _020B56D4
	and r1, r5, #0xc000
	mov r2, r1, asr #0xe
	ldr r1, _020B57C8 ; =UNK_020FF8AC
	and r3, r5, #0xc0000000
	mov r3, r3, lsr #0x1e
	add r2, r1, r2, lsl #0x3
	mov r3, r3, lsl #0x1
	ldr r0, [r7, #0x0]
	ldr r1, _020B57CC ; =0xFE00FFFF
	ldrh r2, [r3, r2]
	and r1, r0, r1
	mov r0, r0, lsl #0x7
	add r0, r2, r0, lsr #0x17
	rsb r2, r0, #0x0
	ldr r0, _020B57D0 ; =0x000001FF
	and r0, r2, r0
	orr r0, r1, r0, lsl #0x10
	str r0, [r7, #0x0]
_020B56D4:
	ldr r0, [r4, #0x0]
	bl FUN_020B4F74
	cmp r0, #0x0
	beq _020B5714
	and r1, r5, #0xc000
	mov r3, r1, asr #0xe
	and r1, r5, #0xc0000000
	mov r1, r1, lsr #0x1e
	mov r2, r1, lsl #0x1
	ldr r1, _020B57D4 ; =UNK_020FF894
	ldrb r0, [r7, #0x0]
	add r1, r1, r3, lsl #0x3
	ldrh r1, [r2, r1]
	add r0, r0, r1
	rsb r0, r0, #0x0
	strb r0, [r7, #0x0]
_020B5714:
	ldr r2, [r7, #0x0]
	ldr r0, _020B57CC ; =0xFE00FFFF
	ldr r1, [sp, #0x18]
	and r0, r2, r0
	mov r2, r2, lsl #0x7
	mov r2, r2, lsr #0x17
	add r2, r2, r1, asr #0xc
	ldr r1, _020B57D0 ; =0x000001FF
	and r1, r2, r1
	orr r0, r0, r1, lsl #0x10
	str r0, [r7, #0x0]
	ldrb r1, [r7, #0x0]
	ldr r0, [sp, #0x1c]
	add r0, r1, r0, asr #0xc
	strb r0, [r7, #0x0]
_020B5750:
	ldr r3, [r4, #0x0]
	ldr r1, [sp, #0x8]
	ldr r2, [sp, #0x14]
	ldr r3, [r3, #0x1c]
	mov r0, r7
	blx r3
	cmp r0, #0x1
	addne sp, sp, #0x44
	ldmneia sp!, {r4-r11,pc}
	ldr r3, [r10, #0x24]
	cmp r3, #0x0
	beq _020B5790
	ldr r0, [r4, #0x0]
	mov r1, r11
	mov r2, r8
	blx r3
_020B5790:
	add r0, r8, #0x1
	mov r0, r0, lsl #0x10
	mov r8, r0, lsr #0x10
	ldrh r0, [r11, #0x0]
	cmp r8, r0
	blo _020B5460
	add sp, sp, #0x44
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B57B0: .word UNK_021CED14
_020B57B4: .word UNK_020FF958
_020B57B8: .word 0x000003FF
_020B57BC: .word 0x0000FFFF
_020B57C0: .word 0x0000FFFE
_020B57C4: .word 0xC000C000
_020B57C8: .word UNK_020FF8AC
_020B57CC: .word 0xFE00FFFF
_020B57D0: .word 0x000001FF
_020B57D4: .word UNK_020FF894
	arm_func_end FUN_020B53B4

	; DoAffineTransforme_
	arm_func_start FUN_020B57D8
FUN_020B57D8: ; 0x020B57D8
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	ldr r4, [r1, #0x0]
	ldr r3, _020B5A9C ; =0x01FF0000
	and r3, r4, r3
	mov r3, r3, lsr #0x10
	mov r3, r3, lsl #0x10
	mov r3, r3, asr #0x10
	cmp r3, #0xff
	orrgt r3, r3, #0xff00
	movgt r3, r3, lsl #0x10
	movgt r3, r3, asr #0x10
	mov r3, r3, lsl #0xc
	str r3, [sp, #0x0]
	ldr r3, [r1, #0x0]
	and r3, r3, #0xff
	mov r3, r3, lsl #0x10
	mov r3, r3, asr #0x10
	cmp r3, #0x7f
	orrgt r3, r3, #0xff00
	movgt r3, r3, lsl #0x10
	movgt r3, r3, asr #0x10
	mov r3, r3, lsl #0xc
	str r3, [sp, #0x4]
	ldr r5, [r1, #0x0]
	and r4, r5, #0x300
	cmp r4, #0x100
	beq _020B5858
	cmp r4, #0x300
	beq _020B5858
	and r3, r5, #0x30000000
	orr r4, r4, r3
_020B5858:
	cmp r4, #0x300
	bne _020B58AC
	ldr r3, _020B5AA0 ; =0xC000C000
	ldr r4, _020B5AA4 ; =UNK_020FF8AC
	and r3, r5, r3
	and r5, r3, #0xc0000000
	and r3, r3, #0xc000
	mov r6, r5, lsr #0x1e
	mov r5, r3, asr #0xe
	ldr r3, _020B5AA8 ; =UNK_020FF894
	mov r6, r6, lsl #0x1
	add r4, r4, r5, lsl #0x3
	add r3, r3, r5, lsl #0x3
	ldrh r5, [r6, r4]
	ldr r7, [sp, #0x0]
	ldrh r3, [r6, r3]
	ldr r4, [sp, #0x4]
	add r5, r7, r5, lsl #0xb
	add r3, r4, r3, lsl #0xb
	str r5, [sp, #0x0]
	str r3, [sp, #0x4]
_020B58AC:
	ldr r5, [r0, #0x8]
	ldr r4, [sp, #0x4]
	add r3, sp, #0x0
	smull r8, r7, r5, r4
	cmp r3, r3
	ldr r6, [r0, #0x0]
	mov r4, #0x1000
	addeq r3, sp, #0x8
	adds r8, r8, r4
	ldr r5, [sp, #0x0]
	adc r7, r7, #0x0
	smlal r8, r7, r6, r5
	mov r5, r8, lsr #0xc
	orr r5, r5, r7, lsl #0x14
	str r5, [r3, #0x0]
	ldr r7, [r0, #0xc]
	ldr r6, [sp, #0x4]
	ldr r5, [r0, #0x4]
	smull r8, r6, r7, r6
	adds r7, r8, r4
	ldr r4, [sp, #0x0]
	adc r6, r6, #0x0
	smlal r7, r6, r5, r4
	mov r5, r7, lsr #0xc
	add r4, sp, #0x8
	orr r5, r5, r6, lsl #0x14
	str r5, [r3, #0x4]
	cmp r3, r4
	ldreq r3, [sp, #0xc]
	ldreq r4, [sp, #0x8]
	streq r3, [sp, #0x4]
	ldr r3, _020B5AAC ; =UNK_021CED14
	streq r4, [sp, #0x0]
	ldr r3, [r3, #0x0]
	ldr r3, [r3, #0x4]
	cmp r3, #0x0
	beq _020B597C
	cmp r3, #0x2
	moveq r5, #0x300
	movne r5, #0x100
	cmp r5, #0x100
	ldreq r4, [r1, #0x0]
	ldreq r3, _020B5AB0 ; =0xC1FFFCFF
	andeq r3, r4, r3
	orreq r3, r3, r5
	streq r3, [r1, #0x0]
	beq _020B597C
	ldr r4, [r1, #0x0]
	ldr r3, _020B5AB0 ; =0xC1FFFCFF
	and r3, r4, r3
	orr r3, r3, r5
	str r3, [r1, #0x0]
_020B597C:
	ldr r6, [r1, #0x0]
	and r5, r6, #0x300
	cmp r5, #0x100
	beq _020B599C
	cmp r5, #0x300
	beq _020B599C
	and r3, r6, #0x30000000
	orr r5, r5, r3
_020B599C:
	ldr r3, _020B5AA0 ; =0xC000C000
	ldr r4, _020B5AA4 ; =UNK_020FF8AC
	and r3, r6, r3
	and r6, r3, #0xc0000000
	and r3, r3, #0xc000
	mov lr, r3, asr #0xe
	mov r6, r6, lsr #0x1e
	mov r3, r6, lsl #0x1
	add r4, r4, lr, lsl #0x3
	ldrh r4, [r3, r4]
	ldr r6, [r0, #0x0]
	ldr r8, _020B5AA8 ; =UNK_020FF894
	mov r12, r4, asr #0x1
	mov r4, r12, lsl #0xc
	rsb r7, r4, #0x0
	mla r7, r6, r12, r7
	add lr, r8, lr, lsl #0x3
	ldrh r3, [r3, lr]
	ldr r6, [r0, #0x8]
	ldr lr, [sp, #0x0]
	mov r3, r3, asr #0x1
	mla r7, r6, r3, r7
	add r6, lr, r7
	str r6, [sp, #0x0]
	mov lr, r3, lsl #0xc
	ldr r6, [r0, #0x4]
	rsb r7, lr, #0x0
	mla r7, r6, r12, r7
	ldr r0, [r0, #0xc]
	ldr r6, [sp, #0x4]
	mla r3, r0, r3, r7
	add r0, r6, r3
	str r0, [sp, #0x4]
	cmp r5, #0x300
	moveq r0, #0x1
	movne r0, #0x0
	cmp r0, #0x0
	beq _020B5A4C
	ldr r3, [sp, #0x0]
	ldr r0, [sp, #0x4]
	sub r3, r3, r4
	sub r0, r0, lr
	str r3, [sp, #0x0]
	str r0, [sp, #0x4]
_020B5A4C:
	ldr r4, [sp, #0x0]
	ldr r0, [r2, #0x0]
	ldr r3, [sp, #0x4]
	add r5, r4, r0
	str r5, [sp, #0x0]
	ldr r2, [r2, #0x4]
	ldr r0, _020B5AB4 ; =0x000001FF
	add r2, r3, r2
	str r2, [sp, #0x4]
	mov r3, r2, asr #0xc
	ldr r4, [r1, #0x0]
	ldr r2, _020B5AB8 ; =0xFE00FF00
	and r3, r3, #0xff
	and r2, r4, r2
	and r4, r0, r5, asr #0xc
	orr r0, r2, r3
	orr r0, r0, r4, lsl #0x10
	str r0, [r1, #0x0]
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020B5A9C: .word 0x01FF0000
_020B5AA0: .word 0xC000C000
_020B5AA4: .word UNK_020FF8AC
_020B5AA8: .word UNK_020FF894
_020B5AAC: .word UNK_021CED14
_020B5AB0: .word 0xC1FFFCFF
_020B5AB4: .word 0x000001FF
_020B5AB8: .word 0xFE00FF00
	arm_func_end FUN_020B57D8

