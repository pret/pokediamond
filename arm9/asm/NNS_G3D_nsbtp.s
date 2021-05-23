	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNSi_G3dAnmCalcNsBtp
NNSi_G3dAnmCalcNsBtp: ; 0x020BE334
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	ldr r3, [r6, #0x0]
	ldr r5, [r6, #0x8]
	mov r1, r2, lsl #0x10
	mov r2, r3, lsl #0x4
	mov r7, r0
	mov r0, r5
	mov r1, r1, lsr #0x10
	mov r2, r2, lsr #0x10
	bl NNSi_G3dGetTexPatAnmFV
	mov r4, r0
	ldrb r1, [r4, #0x2]
	mov r0, r5
	bl NNSi_G3dGetTexPatAnmTexNameByIdx
	mov r1, r0
	ldr r0, [r6, #0x14]
	mov r2, r7
	bl SetTexParamaters_
	ldrb r1, [r4, #0x3]
	cmp r1, #0xff
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
	mov r0, r5
	bl NNSi_G3dGetTexPatAnmPlttNameByIdx
	mov r1, r0
	ldr r0, [r6, #0x14]
	mov r2, r7
	bl SetPlttParamaters_
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	arm_func_end NNSi_G3dAnmCalcNsBtp

	arm_func_start SetPlttParamaters_
SetPlttParamaters_: ; 0x020BE3B4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrh r0, [r5, #0x34]
	mov r4, r2
	add r0, r5, r0
	bl NNS_G3dGetResDataByName
	ldr r1, [r5, #0x2c]
	ldrh r2, [r0, #0x2]
	mov r1, r1, lsl #0x10
	mov r3, r1, lsr #0x10
	ands r1, r2, #0x1
	ldrh r0, [r0, #0x0]
	moveq r1, r3, lsl #0xf
	moveq r3, r1, lsr #0x10
	moveq r0, r0, lsl #0xf
	moveq r0, r0, lsr #0x10
	add r0, r0, r3
	str r0, [r4, #0x14]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	arm_func_end SetPlttParamaters_

	arm_func_start SetTexParamaters_
SetTexParamaters_: ; 0x020BE408
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	add r0, r5, #0x3c
	mov r4, r2
	bl NNS_G3dGetResDataByName
	ldr r1, [r0, #0x0]
	ldr r3, [r4, #0x10]
	and r1, r1, #0x1c000000
	cmp r1, #0x14000000
	ldrne r2, [r5, #0x8]
	ldrne r1, _020BE4E0 ; =0x0000FFFF
	andne r5, r2, r1
	ldreq r2, [r5, #0x18]
	ldreq r1, _020BE4E0 ; =0x0000FFFF
	andeq r5, r2, r1
	ldr r1, _020BE4E4 ; =0xC00F0000
	ldr r2, _020BE4E8 ; =0x000007FF
	and r1, r3, r1
	str r1, [r4, #0x10]
	ldr r1, [r0, #0x0]
	ldr r3, [r4, #0x10]
	add r1, r1, r5
	orr r1, r3, r1
	str r1, [r4, #0x10]
	ldr r3, [r0, #0x4]
	ldr r1, _020BE4EC ; =0x003FF800
	and r3, r3, r2
	strh r3, [r4, #0x2c]
	ldr r3, [r0, #0x4]
	and r1, r3, r1
	mov r1, r1, lsr #0xb
	strh r1, [r4, #0x2e]
	ldr r3, [r0, #0x4]
	ldrh r1, [r4, #0x2c]
	and r0, r3, r2
	and r5, r2, r3, lsr #0xb
	cmp r0, r1
	moveq r0, #0x1000
	beq _020BE4B4
	mov r0, r0, lsl #0xc
	mov r1, r1, lsl #0xc
	bl FX_Div
_020BE4B4:
	str r0, [r4, #0x30]
	ldrh r1, [r4, #0x2e]
	cmp r5, r1
	moveq r0, #0x1000
	beq _020BE4D4
	mov r0, r5, lsl #0xc
	mov r1, r1, lsl #0xc
	bl FX_Div
_020BE4D4:
	str r0, [r4, #0x34]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020BE4E0: .word 0x0000FFFF
_020BE4E4: .word 0xC00F0000
_020BE4E8: .word 0x000007FF
_020BE4EC: .word 0x003FF800
	arm_func_end SetTexParamaters_

	arm_func_start NNSi_G3dAnmObjInitNsBtp
NNSi_G3dAnmObjInitNsBtp: ; 0x020BE4F0
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r3, _020BE59C ; =NNS_G3dFuncAnmMatNsBtpDefault
	ldr r4, [r2, #0x8]
	ldr r3, [r3, #0x0]
	mov r9, r0
	str r3, [r9, #0xc]
	ldrb r0, [r2, #0x18]
	mov r8, r1
	add r4, r2, r4
	strb r0, [r9, #0x19]
	str r8, [r9, #0x8]
	ldrb r2, [r9, #0x19]
	add r1, r9, #0x1a
	mov r0, #0x0
	mov r2, r2, lsl #0x1
	bl MIi_CpuClear16
	ldrb r0, [r8, #0xd]
	mov r7, #0x0
	cmp r0, #0x0
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r9,pc}
	mov r6, r7
	add r5, r8, #0xc
	add r4, r4, #0x4
_020BE554:
	ldrh r1, [r8, #0x12]
	mov r0, r4
	add r2, r5, r1
	ldrh r1, [r2, #0x2]
	add r1, r2, r1
	add r1, r1, r6
	bl NNS_G3dGetResDictIdxByName
	cmp r0, #0x0
	orrge r1, r7, #0x100
	addge r0, r9, r0, lsl #0x1
	strgeh r1, [r0, #0x1a]
	ldrb r0, [r8, #0xd]
	add r7, r7, #0x1
	add r6, r6, #0x10
	cmp r7, r0
	blo _020BE554
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020BE59C: .word NNS_G3dFuncAnmMatNsBtpDefault
	arm_func_end NNSi_G3dAnmObjInitNsBtp
