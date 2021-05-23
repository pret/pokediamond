	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global NNS_G3dAnmFmtNum
NNS_G3dAnmFmtNum: ; 0x02106594
	.byte 0x05, 0x00, 0x00, 0x00

	.global NNS_G3dFuncAnmVisNsBvaDefault
NNS_G3dFuncAnmVisNsBvaDefault: ; 0x02106598
	.word NNSi_G3dAnmCalcNsBva

	.global NNS_G3dFuncAnmJntNsBcaDefault
NNS_G3dFuncAnmJntNsBcaDefault: ; 0x0210659C
	.word NNSi_G3dAnmCalcNsBca

	.global NNS_G3dFuncAnmMatNsBtaDefault
NNS_G3dFuncAnmMatNsBtaDefault: ; 0x021065A0
	.word NNSi_G3dAnmCalcNsBta

	.global NNS_G3dFuncAnmMatNsBtpDefault
NNS_G3dFuncAnmMatNsBtpDefault: ; 0x021065A4
	.word NNSi_G3dAnmCalcNsBtp

	.global NNS_G3dFuncAnmMatNsBmaDefault
NNS_G3dFuncAnmMatNsBmaDefault: ; 0x021065A8
	.word NNSi_G3dAnmCalcNsBma

	.global NNS_G3dFuncBlendVisDefault
NNS_G3dFuncBlendVisDefault: ; 0x021065AC
	.word NNSi_G3dAnmBlendVis

	.global NNS_G3dFuncBlendJntDefault
NNS_G3dFuncBlendJntDefault: ; 0x021065B0
	.word NNSi_G3dAnmBlendJnt

	.global NNS_G3dFuncBlendMatDefault
NNS_G3dFuncBlendMatDefault: ; 0x021065B4
	.word NNSi_G3dAnmBlendMat

	.global NNS_G3dAnmObjInitFuncArray
NNS_G3dAnmObjInitFuncArray: ; 0x021065B8
	.byte 0x4D, 0x00, 0x41, 0x4D
	.word NNSi_G3dAnmObjInitNsBma
	.byte 0x4D, 0x00, 0x50, 0x54
	.word NNSi_G3dAnmObjInitNsBtp
	.byte 0x4D, 0x00, 0x41, 0x54
	.word NNSi_G3dAnmObjInitNsBta
	.byte 0x56, 0x00, 0x41, 0x56
	.word NNSi_G3dAnmObjInitNsBva
	.byte 0x4A, 0x00, 0x41, 0x43
	.word NNSi_G3dAnmObjInitNsBca
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.section .text

	arm_func_start NNSi_G3dAnmBlendVis
NNSi_G3dAnmBlendVis: ; 0x020B8640
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r7, r0
	mov r0, #0x0
	mov r6, r1
	str r0, [r7, #0x0]
	add r4, sp, #0x0
	mov r5, r2, lsl #0x1
	mov r8, #0x1
_020B8664:
	add r1, r5, r6
	ldrh r2, [r1, #0x1a]
	ands r1, r2, #0x100
	beq _020B869C
	ldr r3, [r6, #0xc]
	mov r0, r4
	mov r1, r6
	and r2, r2, #0xff
	blx r3
	ldr r2, [r7, #0x0]
	ldr r1, [sp, #0x0]
	mov r0, r8
	orr r1, r2, r1
	str r1, [r7, #0x0]
_020B869C:
	ldr r6, [r6, #0x10]
	cmp r6, #0x0
	bne _020B8664
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,pc}
	arm_func_end NNSi_G3dAnmBlendVis

	arm_func_start NNSi_G3dAnmBlendJnt
NNSi_G3dAnmBlendJnt: ; 0x020B86B0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x5c
	mov r9, r1
	ldr r3, [r9, #0x10]
	mov r10, r0
	mov r8, r2
	cmp r3, #0x0
	bne _020B8704
	add r2, r9, r8, lsl #0x1
	ldrh r4, [r2, #0x1a]
	and r2, r4, #0x300
	cmp r2, #0x100
	addne sp, sp, #0x5c
	movne r0, #0x0
	ldmneia sp!, {r4-r11,pc}
	ldr r3, [r9, #0xc]
	and r2, r4, #0xff
	blx r3
	add sp, sp, #0x5c
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_020B8704:
	mov r7, #0x0
	mov r3, r7
	mov r4, r9
	mov r2, r8, lsl #0x1
_020B8714:
	add r0, r2, r4
	ldrh r0, [r0, #0x1a]
	and r0, r0, #0x300
	cmp r0, #0x100
	ldreq r0, [r4, #0x4]
	moveq r1, r4
	ldr r4, [r4, #0x10]
	addeq r7, r7, r0
	addeq r3, r3, #0x1
	cmp r4, #0x0
	bne _020B8714
	cmp r7, #0x0
	addeq sp, sp, #0x5c
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,pc}
	cmp r3, #0x1
	bne _020B877C
	add r0, r1, r8, lsl #0x1
	ldrh r2, [r0, #0x1a]
	ldr r3, [r1, #0xc]
	mov r0, r10
	and r2, r2, #0xff
	blx r3
	add sp, sp, #0x5c
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_020B877C:
	mov r1, r10
	mov r0, #0x0
	mov r2, #0x58
	bl MIi_CpuClearFast
	mvn r0, #0x0
	str r0, [r10, #0x0]
	add r5, sp, #0x0
	add r4, sp, #0x4
	add r11, sp, #0x10
_020B87A0:
	add r0, r9, r8, lsl #0x1
	ldrh r2, [r0, #0x1a]
	and r0, r2, #0x300
	cmp r0, #0x100
	bne _020B8948
	ldr r0, [r9, #0x4]
	cmp r0, #0x0
	ble _020B8948
	ldr r3, [r9, #0xc]
	mov r0, r5
	mov r1, r9
	and r2, r2, #0xff
	blx r3
	cmp r7, #0x1000
	ldreq r6, [r9, #0x4]
	beq _020B87F0
	ldr r0, [r9, #0x4]
	mov r1, r7
	bl FX_Div
	mov r6, r0
_020B87F0:
	ldr r3, [sp, #0x0]
	mov r1, r4
	mov r2, r6
	add r0, r10, #0x4
	and r3, r3, #0x1
	bl blendScaleVec_
	ldr r1, [sp, #0x0]
	add r0, r10, #0x10
	and r3, r1, #0x8
	mov r1, r11
	mov r2, r6
	bl blendScaleVec_
	ldr r3, [sp, #0x0]
	add r0, r10, #0x1c
	add r1, sp, #0x1c
	mov r2, r6
	and r3, r3, #0x10
	bl blendScaleVec_
	ldr r0, [sp, #0x0]
	ands r0, r0, #0x4
	bne _020B8898
	ldr r0, [sp, #0x4c]
	ldr r2, [r10, #0x4c]
	smull r1, r0, r6, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	add r0, r2, r1
	str r0, [r10, #0x4c]
	ldr r0, [sp, #0x50]
	ldr r2, [r10, #0x50]
	smull r1, r0, r6, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	add r0, r2, r1
	str r0, [r10, #0x50]
	ldr r0, [sp, #0x54]
	ldr r2, [r10, #0x54]
	smull r1, r0, r6, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	add r0, r2, r1
	str r0, [r10, #0x54]
_020B8898:
	ldr r0, [sp, #0x0]
	ands r0, r0, #0x2
	bne _020B8920
	ldr r0, [sp, #0x28]
	ldr r1, [r10, #0x28]
	mul r0, r6, r0
	add r0, r1, r0, asr #0xc
	str r0, [r10, #0x28]
	ldr r0, [sp, #0x2c]
	ldr r1, [r10, #0x2c]
	mul r0, r6, r0
	add r0, r1, r0, asr #0xc
	str r0, [r10, #0x2c]
	ldr r0, [sp, #0x30]
	ldr r1, [r10, #0x30]
	mul r0, r6, r0
	add r0, r1, r0, asr #0xc
	str r0, [r10, #0x30]
	ldr r0, [sp, #0x34]
	ldr r1, [r10, #0x34]
	mul r0, r6, r0
	add r0, r1, r0, asr #0xc
	str r0, [r10, #0x34]
	ldr r0, [sp, #0x38]
	ldr r1, [r10, #0x38]
	mul r0, r6, r0
	add r0, r1, r0, asr #0xc
	str r0, [r10, #0x38]
	ldr r0, [sp, #0x3c]
	ldr r1, [r10, #0x3c]
	mul r0, r6, r0
	add r0, r1, r0, asr #0xc
	str r0, [r10, #0x3c]
	b _020B8938
_020B8920:
	ldr r0, [r10, #0x28]
	add r0, r0, r6
	str r0, [r10, #0x28]
	ldr r0, [r10, #0x38]
	add r0, r0, r6
	str r0, [r10, #0x38]
_020B8938:
	ldr r1, [r10, #0x0]
	ldr r0, [sp, #0x0]
	and r0, r1, r0
	str r0, [r10, #0x0]
_020B8948:
	ldr r9, [r9, #0x10]
	cmp r9, #0x0
	bne _020B87A0
	add r0, r10, #0x28
	add r1, r10, #0x34
	add r2, r10, #0x40
	bl VEC_CrossProduct
	add r0, r10, #0x28
	mov r1, r0
	bl VEC_Normalize
	add r0, r10, #0x40
	mov r1, r0
	bl VEC_Normalize
	add r0, r10, #0x40
	add r1, r10, #0x28
	add r2, r10, #0x34
	bl VEC_CrossProduct
	mov r0, #0x1
	add sp, sp, #0x5c
	ldmia sp!, {r4-r11,pc}
	arm_func_end NNSi_G3dAnmBlendJnt

	arm_func_start blendScaleVec_
blendScaleVec_: ; 0x020B8998
	cmp r3, #0x0
	beq _020B89C8
	ldr r1, [r0, #0x0]
	add r1, r1, r2
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, r2
	str r1, [r0, #0x4]
	ldr r1, [r0, #0x8]
	add r1, r1, r2
	str r1, [r0, #0x8]
	bx lr
_020B89C8:
	ldr r3, [r1, #0x0]
	ldr r12, [r0, #0x0]
	mul r3, r2, r3
	add r3, r12, r3, asr #0xc
	str r3, [r0, #0x0]
	ldr r3, [r1, #0x4]
	ldr r12, [r0, #0x4]
	mul r3, r2, r3
	add r3, r12, r3, asr #0xc
	str r3, [r0, #0x4]
	ldr r1, [r1, #0x8]
	ldr r3, [r0, #0x8]
	mul r1, r2, r1
	add r1, r3, r1, asr #0xc
	str r1, [r0, #0x8]
	bx lr
	arm_func_end blendScaleVec_

	arm_func_start NNSi_G3dAnmBlendMat
NNSi_G3dAnmBlendMat: ; 0x020B8A08
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r5, r1
	mov r0, #0x0
	mov r4, r2, lsl #0x1
	mov r7, #0x1
_020B8A24:
	add r1, r4, r5
	ldrh r2, [r1, #0x1a]
	ands r1, r2, #0x100
	beq _020B8A4C
	ldr r3, [r5, #0xc]
	mov r0, r6
	mov r1, r5
	and r2, r2, #0xff
	blx r3
	mov r0, r7
_020B8A4C:
	ldr r5, [r5, #0x10]
	cmp r5, #0x0
	bne _020B8A24
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	arm_func_end NNSi_G3dAnmBlendMat
