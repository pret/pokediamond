	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov78_021D74E0
ov78_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	mov r2, #2
	add r5, r0, #0
	mov r0, #3
	mov r1, #0x48
	lsl r2, r2, #0x10
	bl CreateHeap
	add r0, r5, #0
	mov r1, #0xa0
	mov r2, #0x48
	bl OverlayManager_CreateAndGetData
	mov r1, #0
	mov r2, #0xa0
	add r4, r0, #0
	bl memset
	add r0, r5, #0
	bl OverlayManager_GetField18
	add r5, r0, #0
	add r0, r4, #0
	ldrb r1, [r5]
	add r0, #0x9c
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0x9d
	strb r1, [r0]
	mov r0, #0x48
	bl Camera_New
	str r0, [r4]
	bl ov78_021D7708
	add r0, r4, #0
	bl ov78_021D778C
	add r0, sp, #0xc
	mov r1, #0
	str r1, [r0]
	str r1, [r0, #4]
	str r1, [r0, #8]
	str r1, [sp]
	str r1, [sp, #4]
	ldr r1, [r4]
	ldr r2, _021D75C4 ; =0x021D789C
	str r1, [sp, #8]
	ldr r1, _021D75C8 ; =0x0029AEC1
	ldr r3, _021D75CC ; =0x000005C1
	bl Camera_Init_FromTargetDistanceAndAngle
	ldr r0, [r4]
	bl Camera_SetStaticPtr
	mov r4, #0
	mov r7, #2
	mov r6, #4
_021D7558:
	ldr r2, [r5, #4]
	mov r0, #6
	add r1, r4, #0
	mul r1, r0
	add r3, r2, r1
	ldrsh r1, [r2, r1]
	ldrsh r2, [r3, r7]
	ldrsh r3, [r3, r6]
	add r0, r4, #0
	bl NNS_G3dGlbLightVector
	ldr r2, [r5, #4]
	lsl r1, r4, #1
	add r1, r2, r1
	ldrh r1, [r1, #0x18]
	add r0, r4, #0
	bl NNS_G3dGlbLightColor
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021D7558
	ldr r2, [r5, #4]
	ldrh r0, [r2, #0x20]
	ldrh r1, [r2, #0x22]
	ldr r2, [r2, #0x28]
	bl NNS_G3dGlbMaterialColorDiffAmb
	ldr r2, [r5, #4]
	ldrh r0, [r2, #0x24]
	ldrh r1, [r2, #0x26]
	ldr r2, [r2, #0x2c]
	bl NNS_G3dGlbMaterialColorSpecEmi
	ldr r3, [r5, #4]
	ldr r0, [r3, #0x40]
	str r0, [sp]
	ldr r0, [r3, #0x44]
	str r0, [sp, #4]
	ldr r0, [r3, #0x30]
	ldr r1, [r3, #0x34]
	ldr r2, [r3, #0x38]
	ldr r3, [r3, #0x3c]
	bl NNS_G3dGlbPolygonAttr
	mov r0, #0
	mov r1, #0x48
	bl sub_02079A70
	mov r0, #1
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D75C4: .word ov78_021D789C
_021D75C8: .word 0x0029AEC1
_021D75CC: .word 0x000005C1
	thumb_func_end ov78_021D74E0

	thumb_func_start ov78_021D75D0
ov78_021D75D0: ; 0x021D75D0
	push {r3, r4, r5, r6, lr}
	sub sp, #0x3c
	ldr r6, _021D76AC ; =0x021D78AC
	add r2, r0, #0
	add r5, r1, #0
	add r4, sp, #0x18
	mov r3, #4
_021D75DE:
	ldmia r6!, {r0, r1}
	stmia r4!, {r0, r1}
	sub r3, r3, #1
	bne _021D75DE
	ldr r0, [r6]
	add r3, sp, #0xc
	str r0, [r4]
	ldr r4, _021D76B0 ; =0x021D787C
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	add r1, sp, #0
	str r0, [r3]
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	add r0, r2, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, [r5]
	cmp r0, #0
	beq _021D7614
	cmp r0, #1
	beq _021D7622
	b _021D7662
_021D7614:
	ldr r0, _021D76B4 ; =0x000006DC
	bl PlaySE
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D7662
_021D7622:
	add r0, r4, #0
	add r0, #0x9d
	ldrb r0, [r0]
	cmp r0, #0
	bne _021D7654
	add r0, r4, #0
	add r0, #0x80
	ldr r2, [r0]
	mov r0, #1
	ldr r1, [r2]
	lsl r0, r0, #0xc
	add r1, r1, r0
	ldr r0, [r2, #8]
	ldrh r0, [r0, #4]
	lsl r0, r0, #0xc
	cmp r1, r0
	bne _021D7662
	add r1, r4, #0
	mov r0, #1
	add r1, #0x9d
	strb r0, [r1]
	mov r1, #0x48
	bl sub_02079A70
	b _021D7662
_021D7654:
	bl IsPaletteFadeFinished
	cmp r0, #0
	beq _021D7662
	add sp, #0x3c
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D7662:
	mov r3, #1
	mov r2, #0
	lsl r3, r3, #0xc
_021D7668:
	lsl r0, r2, #2
	add r0, r4, r0
	add r0, #0x80
	ldr r1, [r0]
	ldr r5, [r1, #8]
	ldr r0, [r1]
	ldrh r5, [r5, #4]
	add r0, r0, r3
	lsl r5, r5, #0xc
	cmp r0, r5
	bge _021D7680
	str r0, [r1]
_021D7680:
	add r0, r2, #1
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	cmp r2, #4
	blo _021D7668
	bl sub_020222AC
	bl Camera_PushLookAtToNNSGlb
	add r0, r4, #4
	add r1, sp, #0
	add r2, sp, #0x18
	add r3, sp, #0xc
	bl sub_0201B26C
	mov r0, #1
	add r1, r0, #0
	bl sub_020222B4
	mov r0, #0
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021D76AC: .word ov78_021D78AC
_021D76B0: .word ov78_021D787C
_021D76B4: .word 0x000006DC
	thumb_func_end ov78_021D75D0

	thumb_func_start ov78_021D76B8
ov78_021D76B8: ; 0x021D76B8
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	bl OverlayManager_GetData
	add r6, r0, #0
	add r7, r6, #0
	mov r4, #0
	add r7, #0x70
_021D76C8:
	lsl r0, r4, #2
	add r5, r6, r0
	add r1, r5, #0
	add r1, #0x80
	ldr r1, [r1]
	add r0, r7, #0
	bl NNS_G3dFreeAnmObj
	ldr r0, [r5, #0x60]
	bl FreeToHeap
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021D76C8
	ldr r0, [r6, #0x5c]
	bl FreeToHeap
	ldr r0, [r6]
	bl Camera_Delete
	ldr r0, [sp]
	bl OverlayManager_FreeData
	bl sub_0201B398
	mov r0, #0x48
	bl DestroyHeap
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end ov78_021D76B8

	thumb_func_start ov78_021D7708
ov78_021D7708: ; 0x021D7708
	push {r3, lr}
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl sub_02015F1C
	bl GfGfx_DisableEngineAPlanes
	bl GfGfx_DisableEngineBPlanes
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D7758 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D775C ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	bl ov78_021D776C
	mov r0, #0x48
	bl sub_0201B2EC
	ldr r2, _021D7760 ; =0x04000060
	ldr r0, _021D7764 ; =0xFFFFCFFF
	ldrh r1, [r2]
	and r1, r0
	mov r0, #0x20
	orr r0, r1
	strh r0, [r2]
	ldr r0, _021D7768 ; =0x021D7888
	bl G3X_SetEdgeColorTable
	bl GfGfx_SwapDisplay
	pop {r3, pc}
	nop
_021D7758: .word 0xFFFFE0FF
_021D775C: .word 0x04001000
_021D7760: .word 0x04000060
_021D7764: .word 0xFFFFCFFF
_021D7768: .word ov78_021D7888
	thumb_func_end ov78_021D7708

	thumb_func_start ov78_021D776C
ov78_021D776C: ; 0x021D776C
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D7788 ; =0x021D78D0
	add r3, sp, #0
	mov r2, #5
_021D7776:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7776
	add r0, sp, #0
	bl GfGfx_SetBanks
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D7788: .word ov78_021D78D0
	thumb_func_end ov78_021D776C

	thumb_func_start ov78_021D778C
ov78_021D778C: ; 0x021D778C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0x78
	mov r1, #0x48
	bl NARC_New
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x70
	mov r1, #0x48
	mov r2, #4
	bl GF_ExpHeap_FndInitAllocator
	add r1, r5, #0
	add r1, #0x9c
	ldrb r2, [r1]
	mov r1, #0xa
	ldr r0, [sp]
	add r3, r2, #0
	mul r3, r1
	ldr r1, _021D7878 ; =0x021D7900
	mov r2, #0x48
	ldrh r1, [r1, r3]
	bl NARC_AllocAndReadWholeMember
	add r1, r5, #0
	add r2, r5, #0
	str r0, [r5, #0x5c]
	add r0, r5, #4
	add r1, #0x58
	add r2, #0x5c
	bl sub_0201B234
	ldr r0, [r5, #0x5c]
	bl NNS_G3dGetTex
	str r0, [sp, #4]
	ldr r0, [r5, #0x58]
	mov r1, #0
	mov r2, #0x40
	bl NNSi_G3dModifyMatFlag
	ldr r0, [r5, #0x58]
	mov r1, #0
	mov r2, #0x80
	bl NNSi_G3dModifyMatFlag
	mov r2, #2
	ldr r0, [r5, #0x58]
	mov r1, #0
	lsl r2, r2, #8
	bl NNSi_G3dModifyMatFlag
	mov r2, #1
	ldr r0, [r5, #0x58]
	mov r1, #0
	lsl r2, r2, #0xa
	bl NNSi_G3dModifyMatFlag
	add r0, r5, #0
	str r0, [sp, #8]
	add r0, #0x70
	mov r6, #0
	str r0, [sp, #8]
_021D780E:
	add r1, r5, #0
	add r1, #0x9c
	ldrb r3, [r1]
	lsl r0, r6, #2
	add r4, r5, r0
	add r2, r3, #0
	mov r1, #0xa
	mul r2, r1
	ldr r3, _021D7878 ; =0x021D7900
	lsl r1, r6, #1
	add r2, r3, r2
	add r1, r1, r2
	ldrh r1, [r1, #2]
	ldr r0, [sp]
	mov r2, #0x48
	bl NARC_AllocAndReadWholeMember
	str r0, [r4, #0x60]
	mov r1, #0
	bl NNS_G3dGetAnmByIdx
	add r7, r0, #0
	ldr r0, [sp, #8]
	ldr r2, [r5, #0x58]
	add r1, r7, #0
	bl NNS_G3dAllocAnmObj
	add r1, r4, #0
	add r1, #0x80
	str r0, [r1]
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	ldr r2, [r5, #0x58]
	ldr r3, [sp, #4]
	add r1, r7, #0
	bl NNS_G3dAnmObjInit
	add r4, #0x80
	ldr r1, [r4]
	add r0, r5, #4
	bl NNS_G3dRenderObjAddAnmObj
	add r0, r6, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #4
	blo _021D780E
	ldr r0, [sp]
	bl NARC_Delete
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D7878: .word ov78_021D7900
	thumb_func_end ov78_021D778C

	.rodata
	.global ov78_021D787C
ov78_021D787C: ; 0x021D787C
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global ov78_021D7888
ov78_021D7888: ; 0x021D7888
	.byte 0x00, 0x00, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10
	.byte 0xC1, 0xAE, 0x29, 0x00

	.global ov78_021D789C
ov78_021D789C: ; 0x021D789C
	.byte 0x02, 0xD6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x05, 0x00, 0x00, 0x00, 0x00

	.global ov78_021D78AC
ov78_021D78AC: ; 0x021D78AC
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.global ov78_021D78D0
ov78_021D78D0: ; 0x021D78D0
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.data
	.global ov78_021D7900
ov78_021D7900: ; 0x021D7900
	.byte 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x04, 0x00, 0x07, 0x00, 0x05, 0x00, 0x06, 0x00
	.byte 0x08, 0x00, 0x09, 0x00, 0x0C, 0x00, 0x0A, 0x00, 0x0B, 0x00, 0x0D, 0x00, 0x0E, 0x00, 0x11, 0x00
	.byte 0x0F, 0x00, 0x10, 0x00, 0x12, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.bss
