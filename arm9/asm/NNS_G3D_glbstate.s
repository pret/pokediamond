	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	; NNS_G3dGlb
	.global UNK_021CED18
UNK_021CED18: ; 0x021CED18
	.space 0x8

	; NNS_G3dGlb + 0x8
	.global UNK_021CED20
UNK_021CED20: ; 0x021CED20
	.space 0x44

	; NNS_G3dGlb + 0x4C
	.global UNK_021CED64
UNK_021CED64: ; 0x021CED64
	.space 0x34

	; NNS_G3dGlb + 0x80
	.global UNK_021CED98
UNK_021CED98: ; 0x021CED98
	.space 0x28

	; NNS_G3dGlb + 0xA8
	.global UNK_021CEDC0
UNK_021CEDC0: ; 0x021CEDC0
	.space 0x14

	; NNS_G3dGlb + 0xBC
	.global UNK_021CEDD4
UNK_021CEDD4: ; 0x021CEDD4
	.space 0x24

	; NNS_G3dGlb + 0xE0
	.global UNK_021CEDF8
UNK_021CEDF8: ; 0x021CEDF8
	.space 0xc

	; NNS_G3dGlb + 0xEC
	.global UNK_021CEE04
UNK_021CEE04: ; 0x021CEE04
	.space 0x14

	; NNS_G3dGlb + 0x100
	.global UNK_021CEE18
UNK_021CEE18: ; 0x021CEE18
	.space 0x30

	; NNS_G3dGlb + 0x130
	.global UNK_021CEE48
UNK_021CEE48: ; 0x021CEE48
	.space 0x30

	; NNS_G3dGlb + 0x160
	.global UNK_021CEE78
UNK_021CEE78: ; 0x021CEE78
	.space 0xe0

	; NNS_G3dGlb + 0x240
	.global UNK_021CEF58
UNK_021CEF58: ; 0x021CEF58
	.space 0xc

	; NNS_G3dGlb + 0x24C
	.global UNK_021CEF64
UNK_021CEF64: ; 0x021CEF64
	.space 0xc

	; NNS_G3dGlb + 0x258
	.global UNK_021CEF70
UNK_021CEF70: ; 0x021CEF70
	.space 0xc

	.section .text

	; NNS_G3dGlbGetViewPort
	arm_func_start FUN_020B8200
FUN_020B8200: ; 0x020B8200
	cmp r0, #0x0
	ldrne ip, _020B8260 ; =UNK_021CED18
	ldrne r12, [r12, #0xa0]
	andne r12, r12, #0xff
	strne r12, [r0, #0x0]
	cmp r1, #0x0
	ldrne r0, _020B8260 ; =UNK_021CED18
	ldrne r0, [r0, #0xa0]
	movne r0, r0, lsr #0x8
	andne r0, r0, #0xff
	strne r0, [r1, #0x0]
	cmp r2, #0x0
	ldrne r0, _020B8260 ; =UNK_021CED18
	ldrne r0, [r0, #0xa0]
	movne r0, r0, lsr #0x10
	andne r0, r0, #0xff
	strne r0, [r2, #0x0]
	cmp r3, #0x0
	ldrne r0, _020B8260 ; =UNK_021CED18
	ldrne r0, [r0, #0xa0]
	movne r0, r0, lsr #0x18
	andne r0, r0, #0xff
	strne r0, [r3, #0x0]
	bx lr
	.balign 4
_020B8260: .word UNK_021CED18
	arm_func_end FUN_020B8200

	; NNS_G3dGlbGetInvWV
	arm_func_start FUN_020B8264
FUN_020B8264: ; 0x020B8264
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020B829C ; =UNK_021CED18
	ldr r0, [r0, #0xfc]
	ands r0, r0, #0x80
	bne _020B8290
	bl FUN_020B82E4
	ldr r0, _020B829C ; =UNK_021CED18
	ldr r1, [r0, #0xfc]
	orr r1, r1, #0x80
	str r1, [r0, #0xfc]
_020B8290:
	ldr r0, _020B82A0 ; =UNK_021CEE78
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B829C: .word UNK_021CED18
_020B82A0: .word UNK_021CEE78
	arm_func_end FUN_020B8264

	; NNS_G3dGlbGetWV
	arm_func_start FUN_020B82A4
FUN_020B82A4: ; 0x020B82A4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020B82DC ; =UNK_021CED18
	ldr r0, [r0, #0xfc]
	ands r0, r0, #0x80
	bne _020B82D0
	bl FUN_020B82E4
	ldr r0, _020B82DC ; =UNK_021CED18
	ldr r1, [r0, #0xfc]
	orr r1, r1, #0x80
	str r1, [r0, #0xfc]
_020B82D0:
	ldr r0, _020B82E0 ; =UNK_021CEE48
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B82DC: .word UNK_021CED18
_020B82E0: .word UNK_021CEE48
	arm_func_end FUN_020B82A4

	; calcSrtCameraMtx_
	arm_func_start FUN_020B82E4
FUN_020B82E4: ; 0x020B82E4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020B8330 ; =UNK_021CEDD4
	ldr r1, _020B8334 ; =UNK_021CED64
	ldr r2, _020B8338 ; =UNK_021CEE48
	bl MTX_Concat43
	ldr r3, _020B833C ; =UNK_021CED18
	ldr r0, _020B8338 ; =UNK_021CEE48
	ldr r2, [r3, #0xf4]
	mov r1, r0
	str r2, [sp, #0x0]
	ldr r2, [r3, #0xec]
	ldr r3, [r3, #0xf0]
	bl MTX_ScaleApply43
	ldr r0, _020B8338 ; =UNK_021CEE48
	ldr r1, _020B8340 ; =UNK_021CEE78
	bl MTX_Inverse43
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B8330: .word UNK_021CEDD4
_020B8334: .word UNK_021CED64
_020B8338: .word UNK_021CEE48
_020B833C: .word UNK_021CED18
_020B8340: .word UNK_021CEE78
	arm_func_end FUN_020B82E4

	; NNS_G3dGlbGetInvV
	arm_func_start FUN_020B8344
FUN_020B8344: ; 0x020B8344
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020B8384 ; =UNK_021CED18
	ldr r0, [r0, #0xfc]
	ands r0, r0, #0x8
	bne _020B8378
	ldr r0, _020B8388 ; =UNK_021CED64
	ldr r1, _020B838C ; =UNK_021CEE18
	bl MTX_Inverse43
	ldr r0, _020B8384 ; =UNK_021CED18
	ldr r1, [r0, #0xfc]
	orr r1, r1, #0x8
	str r1, [r0, #0xfc]
_020B8378:
	ldr r0, _020B838C ; =UNK_021CEE18
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B8384: .word UNK_021CED18
_020B8388: .word UNK_021CED64
_020B838C: .word UNK_021CEE18
	arm_func_end FUN_020B8344

	; NNS_G3dGlbPolygonAttr
	arm_func_start FUN_020B8390
FUN_020B8390: ; 0x020B8390
	orr r0, r0, r1, lsl #0x4
	ldr r1, [sp, #0x4]
	orr r0, r0, r2, lsl #0x6
	orr r0, r1, r0
	ldr r2, [sp, #0x0]
	orr r1, r0, r3, lsl #0x18
	ldr r0, _020B83B8 ; =UNK_021CED18
	orr r1, r1, r2, lsl #0x10
	str r1, [r0, #0x9c]
	bx lr
	.balign 4
_020B83B8: .word UNK_021CED18
	arm_func_end FUN_020B8390

	; NNS_G3dGlbMaterialColorSpecEmi
	arm_func_start FUN_020B83BC
FUN_020B83BC: ; 0x020B83BC
	cmp r2, #0x0
	movne r2, #0x1
	orr r1, r0, r1, lsl #0x10
	moveq r2, #0x0
	ldr r0, _020B83DC ; =UNK_021CED18
	orr r1, r1, r2, lsl #0xf
	str r1, [r0, #0x98]
	bx lr
	.balign 4
_020B83DC: .word UNK_021CED18
	arm_func_end FUN_020B83BC

	; NNS_G3dGlbMaterialColorDiffAmb
	arm_func_start FUN_020B83E0
FUN_020B83E0: ; 0x020B83E0
	cmp r2, #0x0
	movne r2, #0x1
	orr r1, r0, r1, lsl #0x10
	moveq r2, #0x0
	ldr r0, _020B8400 ; =UNK_021CED18
	orr r1, r1, r2, lsl #0xf
	str r1, [r0, #0x94]
	bx lr
	.balign 4
_020B8400: .word UNK_021CED18
	arm_func_end FUN_020B83E0

	; NNS_G3dGlbLightColor
	arm_func_start FUN_020B8404
FUN_020B8404: ; 0x020B8404
	ldr r2, _020B8414 ; =UNK_021CEDC0
	orr r1, r1, r0, lsl #0x1e
	str r1, [r2, r0, lsl #0x2]
	bx lr
	.balign 4
_020B8414: .word UNK_021CEDC0
	arm_func_end FUN_020B8404

	; NNS_G3dGlbLightVector
	arm_func_start FUN_020B8418
FUN_020B8418: ; 0x020B8418
	stmdb sp!, {r4,lr}
	ldr ip, _020B8444 ; =0x000003FF
	ldr lr, _020B8448 ; =UNK_021CED98
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
_020B8448: .word UNK_021CED98
	arm_func_end FUN_020B8418

	; NNS_G3dGlbSetBaseScale
	arm_func_start FUN_020B844C
FUN_020B844C: ; 0x020B844C
	ldr r3, _020B846C ; =UNK_021CEE04
	ldmia r0, {r0-r2}
	stmia r3, {r0-r2}
	ldr r0, _020B8470 ; =UNK_021CED18
	ldr r1, [r0, #0xfc]
	bic r1, r1, #0xa4
	str r1, [r0, #0xfc]
	bx lr
	.balign 4
_020B846C: .word UNK_021CEE04
_020B8470: .word UNK_021CED18
	arm_func_end FUN_020B844C

	; NNS_G3dGlbSetBaseTrans
	arm_func_start FUN_020B8474
FUN_020B8474: ; 0x020B8474
	ldr r3, _020B8494 ; =UNK_021CEDF8
	ldmia r0, {r0-r2}
	stmia r3, {r0-r2}
	ldr r0, _020B8498 ; =UNK_021CED18
	ldr r1, [r0, #0xfc]
	bic r1, r1, #0xa4
	str r1, [r0, #0xfc]
	bx lr
	.balign 4
_020B8494: .word UNK_021CEDF8
_020B8498: .word UNK_021CED18
	arm_func_end FUN_020B8474

	; NNS_G3dGlbFlushP
	arm_func_start FUN_020B849C
FUN_020B849C: ; 0x020B849C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020B84D4 ; =UNK_021CED18
	mov r2, #0x3e
	ldr r0, [r1], #0x4
	bl FUN_020BB1C0
	ldr r0, _020B84D4 ; =UNK_021CED18
	ldr r1, [r0, #0xfc]
	bic r1, r1, #0x1
	str r1, [r0, #0xfc]
	bic r1, r1, #0x2
	str r1, [r0, #0xfc]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B84D4: .word UNK_021CED18
	arm_func_end FUN_020B849C

	; NNS_G3dGlbInit
	arm_func_start FUN_020B84D8
FUN_020B84D8: ; 0x020B84D8
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r8, _020B85F4 ; =0x17101610
	ldr r1, _020B85F8 ; =UNK_021CED18
	ldr r5, _020B85FC ; =0x32323232
	ldr r4, _020B8600 ; =0x60293130
	ldr r3, _020B8604 ; =0x33333333
	ldr r2, _020B8608 ; =0x002A1B19
	mov r7, #0x0
	mov r6, #0x2
	ldr r0, _020B860C ; =UNK_021CED64
	str r8, [r1, #0x0]
	str r7, [r1, #0x4]
	str r6, [r1, #0x48]
	str r5, [r1, #0x7c]
	str r4, [r1, #0x90]
	str r3, [r1, #0xa4]
	str r2, [r1, #0xb8]
	bl MTX_Identity43_
	ldr r0, _020B8610 ; =UNK_021CED20
	bl MTX_Identity44_
	mov r2, r7
	ldr r1, _020B85F8 ; =UNK_021CED18
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
	ldr r0, _020B863C ; =UNK_021CEDD4
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
	ldr r0, _020B85F8 ; =UNK_021CED18
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
_020B85F8: .word UNK_021CED18
_020B85FC: .word 0x32323232
_020B8600: .word 0x60293130
_020B8604: .word 0x33333333
_020B8608: .word 0x002A1B19
_020B860C: .word UNK_021CED64
_020B8610: .word UNK_021CED20
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
_020B863C: .word UNK_021CEDD4
	arm_func_end FUN_020B84D8

