	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	; calcTexMtx_
	.global UNK_021067B0
UNK_021067B0: ; 0x021067B0
	.word FUN_020BEBD8
	.word FUN_020BEB00
	.word FUN_020BEA84
	.word FUN_020BEA3C
	.word FUN_020BE954
	.word FUN_020BE894
	.word FUN_020BE850
	.word FUN_020BE82C

	.section .text

	; NNSi_G3dSendTexSRTMaya
	arm_func_start FUN_020BE6E4
FUN_020BE6E4: ; 0x020BE6E4
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x50
	mov r4, r0
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	ands r0, r0, #0x8
	ldrne r0, _020BE820 ; =0x00101610
	mov r3, #0x3
	strne r0, [sp, #0x0]
	ldreq r0, _020BE824 ; =0x00101810
	mov r2, #0x2
	streq r0, [sp, #0x0]
	mov r0, #0x1000
	str r0, [sp, #0x44]
	str r3, [sp, #0x4]
	str r2, [sp, #0x48]
	str r1, [sp, #0x40]
	str r1, [sp, #0x34]
	str r1, [sp, #0x30]
	str r1, [sp, #0x2c]
	str r1, [sp, #0x28]
	str r1, [sp, #0x24]
	str r1, [sp, #0x20]
	str r1, [sp, #0x14]
	str r1, [sp, #0x10]
	ldr r1, [r4, #0x0]
	ldr r0, _020BE828 ; =UNK_021067B0
	and r1, r1, #0x7
	ldr r2, [r0, r1, lsl #0x2]
	add r0, sp, #0x8
	mov r1, r4
	blx r2
	ldr r3, [r4, #0x30]
	cmp r3, #0x1000
	beq _020BE7B4
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	smull r2, r0, r3, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [sp, #0x8]
	ldr r2, [r4, #0x30]
	ldr r0, [sp, #0x38]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [sp, #0xc]
	ldr r1, [r4, #0x30]
	smull r2, r0, r1, r0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [sp, #0x38]
_020BE7B4:
	ldr r3, [r4, #0x34]
	cmp r3, #0x1000
	beq _020BE804
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	smull r2, r0, r3, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [sp, #0x18]
	ldr r2, [r4, #0x34]
	ldr r0, [sp, #0x3c]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [sp, #0x1c]
	ldr r1, [r4, #0x34]
	smull r2, r0, r1, r0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [sp, #0x3c]
_020BE804:
	add r1, sp, #0x0
	ldr r0, [sp, #0x0]
	add r1, r1, #0x4
	mov r2, #0x12
	bl FUN_020BB1C0
	add sp, sp, #0x50
	ldmia sp!, {r4,pc}
	.balign 4
_020BE820: .word 0x00101610
_020BE824: .word 0x00101810
_020BE828: .word UNK_021067B0
	arm_func_end FUN_020BE6E4

	; _end
	arm_func_start FUN_020BE82C
FUN_020BE82C: ; 0x020BE82C
	mov r2, #0x1000
	str r2, [r0, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
	str r1, [r0, #0x10]
	str r2, [r0, #0x14]
	str r1, [r0, #0x30]
	str r1, [r0, #0x34]
	bx lr
	arm_func_end FUN_020BE82C

	; _end
	arm_func_start FUN_020BE850
FUN_020BE850: ; 0x020BE850
	ldr r2, [r1, #0x18]
	mov r12, #0x0
	str r2, [r0, #0x0]
	ldr r2, [r1, #0x1c]
	str r2, [r0, #0x14]
	str r12, [r0, #0x4]
	str r12, [r0, #0x30]
	ldr r2, [r1, #0x1c]
	ldrh r3, [r1, #0x2e]
	mov r1, r2, lsl #0x1
	rsb r1, r1, #0x0
	add r1, r1, #0x2000
	mul r1, r3, r1
	mov r1, r1, lsl #0x3
	str r1, [r0, #0x34]
	str r12, [r0, #0x10]
	bx lr
	arm_func_end FUN_020BE850

	; _end
	arm_func_start FUN_020BE894
FUN_020BE894: ; 0x020BE894
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldrh r2, [r5, #0x2c]
	ldrh r1, [r5, #0x2e]
	mov r6, r0
	mov r4, r2, lsl #0xc
	mov r7, r1, lsl #0xc
	mov r0, r7
	mov r1, r4
	bl FX_DivAsync
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x0]
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x14]
	bl FX_GetDivResult
	ldrsh r2, [r5, #0x20]
	mov r1, r7
	rsb r2, r2, #0x0
	mul r0, r2, r0
	mov r2, r0, asr #0xc
	mov r0, r4
	str r2, [r6, #0x4]
	bl FX_DivAsync
	ldrsh r1, [r5, #0x20]
	ldrsh r0, [r5, #0x22]
	ldrh r2, [r5, #0x2c]
	add r0, r1, r0
	rsb r0, r0, #0x0
	add r0, r0, #0x1000
	mul r0, r2, r0
	mov r0, r0, lsl #0x3
	str r0, [r6, #0x30]
	ldrsh r1, [r5, #0x20]
	ldrsh r0, [r5, #0x22]
	ldrh r2, [r5, #0x2e]
	sub r0, r1, r0
	add r0, r0, #0x1000
	mul r0, r2, r0
	mov r0, r0, lsl #0x3
	str r0, [r6, #0x34]
	bl FX_GetDivResult
	ldrsh r1, [r5, #0x20]
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r6, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	arm_func_end FUN_020BE894

	; _end
	arm_func_start FUN_020BE954
FUN_020BE954: ; 0x020BE954
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r9, r1
	ldrh r2, [r9, #0x2c]
	ldrh r1, [r9, #0x2e]
	mov r10, r0
	mov r8, r2, lsl #0xc
	mov r11, r1, lsl #0xc
	mov r0, r11
	mov r1, r8
	bl FX_DivAsync
	ldrsh r5, [r9, #0x22]
	ldr r3, [r9, #0x18]
	ldrsh r0, [r9, #0x20]
	ldr r4, [r9, #0x1c]
	smull r2, r1, r3, r5
	mov r6, r2, lsr #0xc
	orr r6, r6, r1, lsl #0x14
	smull r2, r1, r3, r0
	mov r7, r2, lsr #0xc
	orr r7, r7, r1, lsl #0x14
	smull r3, r2, r4, r0
	smull r1, r0, r4, r5
	mov r5, r3, lsr #0xc
	orr r5, r5, r2, lsl #0x14
	mov r4, r1, lsr #0xc
	orr r4, r4, r0, lsl #0x14
	str r6, [r10, #0x0]
	str r4, [r10, #0x14]
	bl FX_GetDivResult
	mov r1, r11
	rsb r2, r5, #0x0
	mul r0, r2, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x4]
	mov r0, r8
	bl FX_DivAsync
	sub r1, r5, r4
	add r0, r7, r6
	ldrh r3, [r9, #0x2c]
	ldr r2, [r9, #0x18]
	sub r0, r2, r0
	mul r0, r3, r0
	mov r0, r0, lsl #0x3
	str r0, [r10, #0x30]
	ldrh r2, [r9, #0x2e]
	ldr r0, [r9, #0x1c]
	sub r0, r1, r0
	add r0, r0, #0x2000
	mul r0, r2, r0
	mov r0, r0, lsl #0x3
	str r0, [r10, #0x34]
	bl FX_GetDivResult
	mul r0, r7, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	arm_func_end FUN_020BE954

	; _end
	arm_func_start FUN_020BEA3C
FUN_020BEA3C: ; 0x020BEA3C
	mov r2, #0x1000
	str r2, [r0, #0x0]
	str r2, [r0, #0x14]
	mov r12, #0x0
	str r12, [r0, #0x4]
	ldrh r2, [r1, #0x2c]
	ldr r3, [r1, #0x24]
	mul r2, r3, r2
	rsb r2, r2, #0x0
	mov r2, r2, lsl #0x4
	str r2, [r0, #0x30]
	ldrh r2, [r1, #0x2e]
	ldr r1, [r1, #0x28]
	mul r2, r1, r2
	mov r1, r2, lsl #0x4
	str r1, [r0, #0x34]
	str r12, [r0, #0x10]
	bx lr
	arm_func_end FUN_020BEA3C

	; _end
	arm_func_start FUN_020BEA84
FUN_020BEA84: ; 0x020BEA84
	stmdb sp!, {r4,lr}
	ldr r3, [r1, #0x18]
	mov r2, #0x0
	str r3, [r0, #0x0]
	ldr r3, [r1, #0x1c]
	str r3, [r0, #0x14]
	str r2, [r0, #0x4]
	ldr r4, [r1, #0x18]
	ldr r3, [r1, #0x24]
	ldrh lr, [r1, #0x2c]
	smull r12, r3, r4, r3
	mov r4, r12, lsr #0x8
	orr r4, r4, r3, lsl #0x18
	rsb r3, r4, #0x0
	mul r3, lr, r3
	str r3, [r0, #0x30]
	ldr r4, [r1, #0x1c]
	ldr r12, [r1, #0x28]
	mov r3, r4, lsl #0x1
	smull lr, r12, r4, r12
	rsb r4, r3, #0x0
	mov r3, lr, lsr #0x8
	ldrh lr, [r1, #0x2e]
	add r1, r4, #0x2000
	orr r3, r3, r12, lsl #0x18
	mul r4, lr, r1
	mul r1, lr, r3
	add r1, r1, r4, lsl #0x3
	str r1, [r0, #0x34]
	str r2, [r0, #0x10]
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020BEA84

	; _end
	arm_func_start FUN_020BEB00
FUN_020BEB00: ; 0x020BEB00
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldrh r2, [r5, #0x2c]
	ldrh r1, [r5, #0x2e]
	mov r6, r0
	mov r4, r2, lsl #0xc
	mov r7, r1, lsl #0xc
	mov r0, r7
	mov r1, r4
	bl FX_DivAsync
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x0]
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x14]
	bl FX_GetDivResult
	ldrsh r2, [r5, #0x20]
	mov r1, r7
	rsb r2, r2, #0x0
	mul r0, r2, r0
	mov r2, r0, asr #0xc
	mov r0, r4
	str r2, [r6, #0x4]
	bl FX_DivAsync
	ldrsh r2, [r5, #0x20]
	ldrsh r1, [r5, #0x22]
	ldrh r3, [r5, #0x2c]
	ldr r0, [r5, #0x24]
	add r1, r2, r1
	rsb r1, r1, #0x0
	add r1, r1, #0x1000
	mul r2, r3, r1
	mul r1, r0, r3
	mov r0, r2, lsl #0x3
	sub r0, r0, r1, lsl #0x4
	str r0, [r6, #0x30]
	ldrsh r2, [r5, #0x20]
	ldrsh r1, [r5, #0x22]
	ldrh r3, [r5, #0x2e]
	ldr r0, [r5, #0x28]
	sub r1, r2, r1
	add r1, r1, #0x1000
	mul r2, r3, r1
	mul r1, r0, r3
	mov r0, r2, lsl #0x3
	add r0, r0, r1, lsl #0x4
	str r0, [r6, #0x34]
	bl FX_GetDivResult
	ldrsh r1, [r5, #0x20]
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r6, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	arm_func_end FUN_020BEB00

	; _end
	arm_func_start FUN_020BEBD8
FUN_020BEBD8: ; 0x020BEBD8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r9, r1
	ldrh r2, [r9, #0x2c]
	ldrh r1, [r9, #0x2e]
	mov r10, r0
	mov r8, r2, lsl #0xc
	mov r11, r1, lsl #0xc
	mov r0, r11
	mov r1, r8
	bl FX_DivAsync
	ldrsh r5, [r9, #0x22]
	ldr r3, [r9, #0x18]
	ldrsh r0, [r9, #0x20]
	ldr r4, [r9, #0x1c]
	smull r2, r1, r3, r5
	mov r6, r2, lsr #0xc
	orr r6, r6, r1, lsl #0x14
	smull r2, r1, r3, r0
	mov r7, r2, lsr #0xc
	orr r7, r7, r1, lsl #0x14
	smull r3, r2, r4, r0
	smull r1, r0, r4, r5
	mov r5, r3, lsr #0xc
	orr r5, r5, r2, lsl #0x14
	mov r4, r1, lsr #0xc
	orr r4, r4, r0, lsl #0x14
	str r6, [r10, #0x0]
	str r4, [r10, #0x14]
	bl FX_GetDivResult
	mov r1, r11
	rsb r2, r5, #0x0
	mul r0, r2, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x4]
	mov r0, r8
	bl FX_DivAsync
	sub r1, r5, r4
	add r2, r7, r6
	ldr r5, [r9, #0x18]
	ldrh r0, [r9, #0x2c]
	sub r3, r5, r2
	ldr r2, [r9, #0x24]
	mul r4, r0, r3
	smull r3, r2, r5, r2
	mov r4, r4, lsl #0x3
	mov r3, r3, lsr #0x8
	orr r3, r3, r2, lsl #0x18
	mul r2, r0, r3
	sub r0, r4, r2
	str r0, [r10, #0x30]
	ldr r4, [r9, #0x1c]
	ldrh r3, [r9, #0x2e]
	sub r0, r1, r4
	add r0, r0, #0x2000
	mul r2, r3, r0
	ldr r0, [r9, #0x28]
	smull r1, r0, r4, r0
	mov r1, r1, lsr #0x8
	orr r1, r1, r0, lsl #0x18
	mul r0, r3, r1
	add r0, r0, r2, lsl #0x3
	str r0, [r10, #0x34]
	bl FX_GetDivResult
	mul r0, r7, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	arm_func_end FUN_020BEBD8

	; NNSi_G3dGetJointScaleMaya
	arm_func_start FUN_020BECEC
FUN_020BECEC: ; 0x020BECEC
	stmdb sp!, {r4-r8,lr}
	mov r12, r0
	ands r0, r3, #0x4
	ldrb r3, [r2, #0x3]
	beq _020BED40
	ldr r1, [r12, #0x0]
	ands r0, r3, #0x2
	orr r0, r1, #0x1
	str r0, [r12, #0x0]
	beq _020BEDB8
	ldr r0, _020BEE2C ; =UNK_021CEF7C
	ldrb r7, [r2, #0x1]
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	add r6, r0, #0xc4
	mov r5, r7, lsr #0x5
	ldr r4, [r6, r5, lsl #0x2]
	and r0, r7, #0x1f
	orr r0, r4, r1, lsl r0
	str r0, [r6, r5, lsl #0x2]
	b _020BEDB8
_020BED40:
	ldr r4, [r1, #0x0]
	ands r0, r3, #0x2
	str r4, [r12, #0x4]
	ldr r0, [r1, #0x4]
	str r0, [r12, #0x8]
	ldr r0, [r1, #0x8]
	str r0, [r12, #0xc]
	beq _020BEDB8
	ldr lr, _020BEE2C ; =UNK_021CEF7C
	ldrb r0, [r2, #0x1]
	ldr r4, [lr, #0x0]
	mov lr, #0x18
	add r8, r4, #0xc4
	mov r7, r0, lsr #0x5
	and r4, r0, #0x1f
	mov r5, #0x1
	mvn r4, r5, lsl r4
	ldr r6, [r8, r7, lsl #0x2]
	mul r5, r0, lr
	and r0, r6, r4
	str r0, [r8, r7, lsl #0x2]
	ldr r4, [r1, #0xc]
	ldr r0, _020BEE30 ; =UNK_021CFD8C
	ldr lr, _020BEE34 ; =UNK_021CFD90
	str r4, [r0, r5]
	ldr r4, [r1, #0x10]
	ldr r0, _020BEE38 ; =UNK_021CFD94
	str r4, [lr, r5]
	ldr r1, [r1, #0x14]
	str r1, [r0, r5]
_020BEDB8:
	ands r0, r3, #0x1
	beq _020BEE1C
	ldrb r0, [r2, #0x2]
	ldr r2, [r12, #0x0]
	ldr r1, _020BEE2C ; =UNK_021CEF7C
	orr r2, r2, #0x20
	str r2, [r12, #0x0]
	ldr r2, [r1, #0x0]
	mov r1, r0, lsr #0x5
	add r1, r2, r1, lsl #0x2
	and r2, r0, #0x1f
	mov r3, #0x1
	mov r2, r3, lsl r2
	ldr r1, [r1, #0xc4]
	ands r1, r2, r1
	ldrne r0, [r12, #0x0]
	orrne r0, r0, #0x8
	strne r0, [r12, #0x0]
	bne _020BEE1C
	ldr r2, _020BEE30 ; =UNK_021CFD8C
	mov r1, #0x18
	mla r1, r0, r1, r2
	add r3, r12, #0x10
	ldmia r1, {r0-r2}
	stmia r3, {r0-r2}
_020BEE1C:
	ldr r0, [r12, #0x0]
	orr r0, r0, #0x10
	str r0, [r12, #0x0]
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020BEE2C: .word UNK_021CEF7C
_020BEE30: .word UNK_021CFD8C
_020BEE34: .word UNK_021CFD90
_020BEE38: .word UNK_021CFD94
	arm_func_end FUN_020BECEC

	; _end
	arm_func_start FUN_020BEE3C
FUN_020BEE3C: ; 0x020BEE3C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r1, [r5, #0x0]
	mov r4, #0x0
	ands r0, r1, #0x4
	moveq r4, #0x1
	ands r0, r1, #0x20
	beq _020BEE94
	ands r0, r1, #0x8
	bne _020BEE94
	cmp r4, #0x0
	beq _020BEE84
	add r1, r5, #0x4c
	mov r0, #0x1c
	mov r2, #0x3
	bl FUN_020BB1C0
	mov r4, #0x0
_020BEE84:
	add r1, r5, #0x10
	mov r0, #0x1b
	mov r2, #0x3
	bl FUN_020BB1C0
_020BEE94:
	ldr r0, [r5, #0x0]
	ands r0, r0, #0x2
	bne _020BEED0
	cmp r4, #0x0
	beq _020BEEBC
	add r1, r5, #0x28
	mov r0, #0x19
	mov r2, #0xc
	bl FUN_020BB1C0
	b _020BEEE8
_020BEEBC:
	add r1, r5, #0x28
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
	b _020BEEE8
_020BEED0:
	cmp r4, #0x0
	beq _020BEEE8
	add r1, r5, #0x4c
	mov r0, #0x1c
	mov r2, #0x3
	bl FUN_020BB1C0
_020BEEE8:
	ldr r0, [r5, #0x0]
	ands r0, r0, #0x1
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,pc}
	add r1, r5, #0x4
	mov r0, #0x1b
	mov r2, #0x3
	bl FUN_020BB1C0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	arm_func_end FUN_020BEE3C

