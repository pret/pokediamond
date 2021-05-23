	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global NNS_G3dGlb
NNS_G3dGlb: ; 0x021CED18
	.space 0x264

	.section .text

	arm_func_start NNS_G3dGlbGetViewPort
NNS_G3dGlbGetViewPort: ; 0x020B8200
	cmp r0, #0x0
	ldrne ip, _020B8260 ; =NNS_G3dGlb
	ldrne r12, [r12, #0xa0]
	andne r12, r12, #0xff
	strne r12, [r0, #0x0]
	cmp r1, #0x0
	ldrne r0, _020B8260 ; =NNS_G3dGlb
	ldrne r0, [r0, #0xa0]
	movne r0, r0, lsr #0x8
	andne r0, r0, #0xff
	strne r0, [r1, #0x0]
	cmp r2, #0x0
	ldrne r0, _020B8260 ; =NNS_G3dGlb
	ldrne r0, [r0, #0xa0]
	movne r0, r0, lsr #0x10
	andne r0, r0, #0xff
	strne r0, [r2, #0x0]
	cmp r3, #0x0
	ldrne r0, _020B8260 ; =NNS_G3dGlb
	ldrne r0, [r0, #0xa0]
	movne r0, r0, lsr #0x18
	andne r0, r0, #0xff
	strne r0, [r3, #0x0]
	bx lr
	.balign 4
_020B8260: .word NNS_G3dGlb
	arm_func_end NNS_G3dGlbGetViewPort

	arm_func_start NNS_G3dGlbGetInvWV
NNS_G3dGlbGetInvWV: ; 0x020B8264
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020B829C ; =NNS_G3dGlb
	ldr r0, [r0, #0xfc]
	ands r0, r0, #0x80
	bne _020B8290
	bl calcSrtCameraMtx_
	ldr r0, _020B829C ; =NNS_G3dGlb
	ldr r1, [r0, #0xfc]
	orr r1, r1, #0x80
	str r1, [r0, #0xfc]
_020B8290:
	ldr r0, _020B82A0 ; =NNS_G3dGlb + 0x160
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B829C: .word NNS_G3dGlb
_020B82A0: .word NNS_G3dGlb + 0x160
	arm_func_end NNS_G3dGlbGetInvWV

	arm_func_start NNS_G3dGlbGetWV
NNS_G3dGlbGetWV: ; 0x020B82A4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020B82DC ; =NNS_G3dGlb
	ldr r0, [r0, #0xfc]
	ands r0, r0, #0x80
	bne _020B82D0
	bl calcSrtCameraMtx_
	ldr r0, _020B82DC ; =NNS_G3dGlb
	ldr r1, [r0, #0xfc]
	orr r1, r1, #0x80
	str r1, [r0, #0xfc]
_020B82D0:
	ldr r0, _020B82E0 ; =NNS_G3dGlb + 0x130
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B82DC: .word NNS_G3dGlb
_020B82E0: .word NNS_G3dGlb + 0x130
	arm_func_end NNS_G3dGlbGetWV

	arm_func_start calcSrtCameraMtx_
calcSrtCameraMtx_: ; 0x020B82E4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020B8330 ; =NNS_G3dGlb + 0xBC
	ldr r1, _020B8334 ; =NNS_G3dGlb + 0x4C
	ldr r2, _020B8338 ; =NNS_G3dGlb + 0x130
	bl MTX_Concat43
	ldr r3, _020B833C ; =NNS_G3dGlb
	ldr r0, _020B8338 ; =NNS_G3dGlb + 0x130
	ldr r2, [r3, #0xf4]
	mov r1, r0
	str r2, [sp, #0x0]
	ldr r2, [r3, #0xec]
	ldr r3, [r3, #0xf0]
	bl MTX_ScaleApply43
	ldr r0, _020B8338 ; =NNS_G3dGlb + 0x130
	ldr r1, _020B8340 ; =NNS_G3dGlb + 0x160
	bl MTX_Inverse43
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B8330: .word NNS_G3dGlb + 0xBC
_020B8334: .word NNS_G3dGlb + 0x4C
_020B8338: .word NNS_G3dGlb + 0x130
_020B833C: .word NNS_G3dGlb
_020B8340: .word NNS_G3dGlb + 0x160
	arm_func_end calcSrtCameraMtx_

	arm_func_start NNS_G3dGlbGetInvV
NNS_G3dGlbGetInvV: ; 0x020B8344
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020B8384 ; =NNS_G3dGlb
	ldr r0, [r0, #0xfc]
	ands r0, r0, #0x8
	bne _020B8378
	ldr r0, _020B8388 ; =NNS_G3dGlb + 0x4C
	ldr r1, _020B838C ; =NNS_G3dGlb + 0x100
	bl MTX_Inverse43
	ldr r0, _020B8384 ; =NNS_G3dGlb
	ldr r1, [r0, #0xfc]
	orr r1, r1, #0x8
	str r1, [r0, #0xfc]
_020B8378:
	ldr r0, _020B838C ; =NNS_G3dGlb + 0x100
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B8384: .word NNS_G3dGlb
_020B8388: .word NNS_G3dGlb + 0x4C
_020B838C: .word NNS_G3dGlb + 0x100
	arm_func_end NNS_G3dGlbGetInvV

	arm_func_start NNS_G3dGlbPolygonAttr
NNS_G3dGlbPolygonAttr: ; 0x020B8390
	orr r0, r0, r1, lsl #0x4
	ldr r1, [sp, #0x4]
	orr r0, r0, r2, lsl #0x6
	orr r0, r1, r0
	ldr r2, [sp, #0x0]
	orr r1, r0, r3, lsl #0x18
	ldr r0, _020B83B8 ; =NNS_G3dGlb
	orr r1, r1, r2, lsl #0x10
	str r1, [r0, #0x9c]
	bx lr
	.balign 4
_020B83B8: .word NNS_G3dGlb
	arm_func_end NNS_G3dGlbPolygonAttr

	arm_func_start NNS_G3dGlbMaterialColorSpecEmi
NNS_G3dGlbMaterialColorSpecEmi: ; 0x020B83BC
	cmp r2, #0x0
	movne r2, #0x1
	orr r1, r0, r1, lsl #0x10
	moveq r2, #0x0
	ldr r0, _020B83DC ; =NNS_G3dGlb
	orr r1, r1, r2, lsl #0xf
	str r1, [r0, #0x98]
	bx lr
	.balign 4
_020B83DC: .word NNS_G3dGlb
	arm_func_end NNS_G3dGlbMaterialColorSpecEmi

	arm_func_start NNS_G3dGlbMaterialColorDiffAmb
NNS_G3dGlbMaterialColorDiffAmb: ; 0x020B83E0
	cmp r2, #0x0
	movne r2, #0x1
	orr r1, r0, r1, lsl #0x10
	moveq r2, #0x0
	ldr r0, _020B8400 ; =NNS_G3dGlb
	orr r1, r1, r2, lsl #0xf
	str r1, [r0, #0x94]
	bx lr
	.balign 4
_020B8400: .word NNS_G3dGlb
	arm_func_end NNS_G3dGlbMaterialColorDiffAmb

	arm_func_start NNS_G3dGlbLightColor
NNS_G3dGlbLightColor: ; 0x020B8404
	ldr r2, _020B8414 ; =NNS_G3dGlb + 0xA8
	orr r1, r1, r0, lsl #0x1e
	str r1, [r2, r0, lsl #0x2]
	bx lr
	.balign 4
_020B8414: .word NNS_G3dGlb + 0xA8
	arm_func_end NNS_G3dGlbLightColor

	arm_func_start NNS_G3dGlbLightVector
NNS_G3dGlbLightVector: ; 0x020B8418
	stmdb sp!, {r4,lr}
	ldr ip, _020B8444 ; =0x000003FF
	ldr lr, _020B8448 ; =NNS_G3dGlb + 0x80
	and r4, r12, r1, asr #0x3
	and r1, r12, r2, asr #0x3
	and r2, r12, r3, asr #0x3
	orr r1, r4, r1, lsl #0xa
	orr r1, r1, r2, lsl #0x14
	orr r1, r1, r0, lsl #0x1e
	str r1, [lr, r0, lsl #0x2]
	ldmia sp!, {r4,pc}
	.balign 4
_020B8444: .word 0x000003FF
_020B8448: .word NNS_G3dGlb + 0x80
	arm_func_end NNS_G3dGlbLightVector

	arm_func_start NNS_G3dGlbSetBaseScale
NNS_G3dGlbSetBaseScale: ; 0x020B844C
	ldr r3, _020B846C ; =NNS_G3dGlb + 0xEC
	ldmia r0, {r0-r2}
	stmia r3, {r0-r2}
	ldr r0, _020B8470 ; =NNS_G3dGlb
	ldr r1, [r0, #0xfc]
	bic r1, r1, #0xa4
	str r1, [r0, #0xfc]
	bx lr
	.balign 4
_020B846C: .word NNS_G3dGlb + 0xEC
_020B8470: .word NNS_G3dGlb
	arm_func_end NNS_G3dGlbSetBaseScale

	arm_func_start NNS_G3dGlbSetBaseTrans
NNS_G3dGlbSetBaseTrans: ; 0x020B8474
	ldr r3, _020B8494 ; =NNS_G3dGlb + 0xE0
	ldmia r0, {r0-r2}
	stmia r3, {r0-r2}
	ldr r0, _020B8498 ; =NNS_G3dGlb
	ldr r1, [r0, #0xfc]
	bic r1, r1, #0xa4
	str r1, [r0, #0xfc]
	bx lr
	.balign 4
_020B8494: .word NNS_G3dGlb + 0xE0
_020B8498: .word NNS_G3dGlb
	arm_func_end NNS_G3dGlbSetBaseTrans

	arm_func_start NNS_G3dGlbFlushP
NNS_G3dGlbFlushP: ; 0x020B849C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020B84D4 ; =NNS_G3dGlb
	mov r2, #0x3e
	ldr r0, [r1], #0x4
	bl NNS_G3dGeBufferOP_N
	ldr r0, _020B84D4 ; =NNS_G3dGlb
	ldr r1, [r0, #0xfc]
	bic r1, r1, #0x1
	str r1, [r0, #0xfc]
	bic r1, r1, #0x2
	str r1, [r0, #0xfc]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B84D4: .word NNS_G3dGlb
	arm_func_end NNS_G3dGlbFlushP

	arm_func_start NNS_G3dGlbInit
NNS_G3dGlbInit: ; 0x020B84D8
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r8, _020B85F4 ; =0x17101610
	ldr r1, _020B85F8 ; =NNS_G3dGlb
	ldr r5, _020B85FC ; =0x32323232
	ldr r4, _020B8600 ; =0x60293130
	ldr r3, _020B8604 ; =0x33333333
	ldr r2, _020B8608 ; =0x002A1B19
	mov r7, #0x0
	mov r6, #0x2
	ldr r0, _020B860C ; =NNS_G3dGlb + 0x4C
	str r8, [r1, #0x0]
	str r7, [r1, #0x4]
	str r6, [r1, #0x48]
	str r5, [r1, #0x7c]
	str r4, [r1, #0x90]
	str r3, [r1, #0xa4]
	str r2, [r1, #0xb8]
	bl MTX_Identity43_
	ldr r0, _020B8610 ; =NNS_G3dGlb + 0x8
	bl MTX_Identity44_
	mov r2, r7
	ldr r1, _020B85F8 ; =NNS_G3dGlb
	ldr r7, _020B8614 ; =0x4210C210
	ldr r0, _020B8618 ; =0x40000200
	ldr lr, _020B861C ; =0x2D8B62D8
	ldr sb, _020B8620 ; =0x800001FF
	ldr r8, _020B8624 ; =0xC0080000
	ldr r6, _020B8628 ; =0x001F008F
	ldr r5, _020B862C ; =0xBFFF0000
	ldr r4, _020B8630 ; =0x00007FFF
	ldr ip, _020B8634 ; =0x800003E0
	ldr r3, _020B8638 ; =0xC0007C00
	str r0, [r1, #0x84]
	str lr, [r1, #0x80]
	mov lr, #0x4000001f
	ldr r0, _020B863C ; =NNS_G3dGlb + 0xBC
	str r9, [r1, #0x88]
	str r8, [r1, #0x8c]
	str r7, [r1, #0x94]
	str r7, [r1, #0x98]
	str r6, [r1, #0x9c]
	str r5, [r1, #0xa0]
	str r4, [r1, #0xa8]
	str lr, [r1, #0xac]
	str r12, [r1, #0xb0]
	str r3, [r1, #0xb4]
	str r2, [r1, #0xe0]
	str r2, [r1, #0xe4]
	str r2, [r1, #0xe8]
	bl MTX_Identity33_
	mov r3, #0x1000
	ldr r0, _020B85F8 ; =NNS_G3dGlb
	mov r2, #0x0
	rsb r1, r3, #0x0
	str r3, [r0, #0xec]
	str r3, [r0, #0xf0]
	str r3, [r0, #0xf4]
	str r2, [r0, #0xf8]
	str r2, [r0, #0xfc]
	str r2, [r0, #0x248]
	str r2, [r0, #0x244]
	str r2, [r0, #0x240]
	str r2, [r0, #0x254]
	str r2, [r0, #0x24c]
	str r3, [r0, #0x250]
	str r2, [r0, #0x25c]
	str r2, [r0, #0x258]
	str r1, [r0, #0x260]
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020B85F4: .word 0x17101610
_020B85F8: .word NNS_G3dGlb
_020B85FC: .word 0x32323232
_020B8600: .word 0x60293130
_020B8604: .word 0x33333333
_020B8608: .word 0x002A1B19
_020B860C: .word NNS_G3dGlb + 0x4C
_020B8610: .word NNS_G3dGlb + 0x8
_020B8614: .word 0x4210C210
_020B8618: .word 0x40000200
_020B861C: .word 0x2D8B62D8
_020B8620: .word 0x800001FF
_020B8624: .word 0xC0080000
_020B8628: .word 0x001F008F
_020B862C: .word 0xBFFF0000
_020B8630: .word 0x00007FFF
_020B8634: .word 0x800003E0
_020B8638: .word 0xC0007C00
_020B863C: .word NNS_G3dGlb + 0xBC
	arm_func_end NNS_G3dGlbInit
