	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	; firstSRTransformedMtxIdx_
	.global UNK_02106570
UNK_02106570: ; 0x02106570
	.short -2

	.balign 4, 0
	; currenVramTransferHandle_
	.global UNK_02106574
UNK_02106574: ; 0x02106574
	.word -1

	; mtxI_
	.global UNK_02106578
UNK_02106578: ; 0x02106578
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.section .bss

	; currentMtxCachePos_
	.global UNK_021CDD60
UNK_021CDD60: ; 0x021CDD60
	.space 0x4

	; groupID_
	.global UNK_021CDD64
UNK_021CDD64: ; 0x021CDD64
	.space 0x4

	; bDonotUseSRTransform
	.global UNK_021CDD68
UNK_021CDD68: ; 0x021CDD68
	.space 0x4

	; pCurrentInstance_
	.global UNK_021CDD6C
UNK_021CDD6C: ; 0x021CDD6C
	.space 0x4

	; stackPos_
	.global UNK_021CDD70
UNK_021CDD70: ; 0x021CDD70
	.space 0x4

	; fxZStack_
	.global UNK_021CDD74
UNK_021CDD74: ; 0x021CDD74
	.space 0x80

	; mtxStateStack_
	.global UNK_021CDDF4
UNK_021CDDF4: ; 0x021CDDF4
	.space 0x4

	; mtxStateStack_ + 0x4
	.global UNK_021CDDF8
UNK_021CDDF8: ; 0x021CDDF8
	.space 0xfc

	; mtxStack_
	.global UNK_021CDEF4
UNK_021CDEF4: ; 0x021CDEF4
	.space 0x10

	; mtxStack_ + 0x10
	.global UNK_021CDF04
UNK_021CDF04: ; 0x021CDF04
	.space 0x4

	; mtxStack_ + 0x14
	.global UNK_021CDF08
UNK_021CDF08: ; 0x021CDF08
	.space 0x2ec

	; mtxStackFor2DHW_
	.global UNK_021CE1F4
UNK_021CE1F4: ; 0x021CE1F4
	.space 0x300

	; mtxCacheBuffer_
	.global UNK_021CE4F4
UNK_021CE4F4: ; 0x021CE4F4
	.space 0x400

	; mcRenderState_
	.global UNK_021CE8F4
UNK_021CE8F4: ; 0x021CE8F4
	.space 0x4

	; mcRenderState_ + 0x4
	.global UNK_021CE8F8
UNK_021CE8F8: ; 0x021CE8F8
	.space 0x404

	.section .text

	; NNS_G2dSetRendererImageProxy
	arm_func_start thunk_FUN_020b5040
thunk_FUN_020b5040: ; 0x020B2780
	ldr ip, _020B2788 ; =FUN_020B5040
	bx r12
	.balign 4
_020B2788: .word FUN_020B5040
	arm_func_end thunk_FUN_020b5040

	; _end
	arm_func_start FUN_020B278C
FUN_020B278C: ; 0x020B278C
	ldr r0, [r0, #0x78]
	bx lr
	arm_func_end FUN_020B278C

	; NNS_G2dRotZ
	arm_func_start FUN_020B2794
FUN_020B2794: ; 0x020B2794
	stmdb sp!, {lr}
	sub sp, sp, #0x1c
	ldr r2, _020B2894 ; =UNK_021CDD70
	mov lr, #0x0
	ldr r12, [r2, #0x0]
	ldr r3, _020B2898 ; =UNK_021CDEF4
	mov r2, #0x18
	str r1, [sp, #0x0]
	str r1, [sp, #0xc]
	mla r1, r12, r2, r3
	rsb r3, r0, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0x0
	mov r2, r1
	str r3, [sp, #0x8]
	str lr, [sp, #0x10]
	str lr, [sp, #0x14]
	bl FUN_020B423C
	ldr r0, _020B2894 ; =UNK_021CDD70
	ldr r1, _020B289C ; =UNK_021CE1F4
	ldr r2, [r0, #0x0]
	mov r0, #0x18
	mla r1, r2, r0, r1
	add r0, sp, #0x0
	mov r2, r1
	bl FUN_020B423C
	ldr r0, _020B28A0 ; =UNK_021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020B2824
	ldr r1, _020B28A4 ; =UNK_02106570
	ldr r0, _020B28A8 ; =0x0000FFFE
	ldrh r1, [r1, #0x0]
	cmp r1, r0
	movne r0, #0x1
	bne _020B2828
_020B2824:
	mov r0, #0x0
_020B2828:
	cmp r0, #0x0
	ldreq r1, _020B2894 ; =UNK_021CDD70
	ldreq r0, _020B28A4 ; =UNK_02106570
	ldreq r1, [r1, #0x0]
	streqh r1, [r0, #0x0]
	ldr r0, _020B2894 ; =UNK_021CDD70
	ldr r1, _020B28AC ; =UNK_021CDDF4
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x10
	add r12, r1, r0, lsr #0xd
	ldrh r0, [r12, #0x4]
	cmp r0, #0x3
	addls pc, pc, r0, lsl #0x2
	b _020B288C
	; Jump table
	b _020B2870 ; case 0
	b _020B288C ; case 1
	b _020B2870 ; case 2
	b _020B2870 ; case 3
_020B2870:
	ldr r0, _020B28B0 ; =UNK_021CDD64
	mov r1, #0x1
	ldrh r3, [r0, #0x0]
	add r2, r3, #0x1
	strh r2, [r0, #0x0]
	strh r3, [r12, #0x2]
	strh r1, [r12, #0x4]
_020B288C:
	add sp, sp, #0x1c
	ldmia sp!, {pc}
	.balign 4
_020B2894: .word UNK_021CDD70
_020B2898: .word UNK_021CDEF4
_020B289C: .word UNK_021CE1F4
_020B28A0: .word UNK_021CDD68
_020B28A4: .word UNK_02106570
_020B28A8: .word 0x0000FFFE
_020B28AC: .word UNK_021CDDF4
_020B28B0: .word UNK_021CDD64
	arm_func_end FUN_020B2794

	; NNS_G2dScale
	arm_func_start FUN_020B28B4
FUN_020B28B4: ; 0x020B28B4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x1c
	ldr r2, _020B29E8 ; =UNK_021CDD70
	mov r12, #0x0
	ldr r3, [r2, #0x0]
	mov r4, r1
	ldr r2, _020B29EC ; =UNK_021CDEF4
	mov r1, #0x18
	mla r1, r3, r1, r2
	mov r5, r0
	add r0, sp, #0x0
	mov r2, r1
	str r5, [sp, #0x0]
	str r12, [sp, #0x4]
	str r12, [sp, #0x8]
	str r4, [sp, #0xc]
	str r12, [sp, #0x10]
	str r12, [sp, #0x14]
	bl FUN_020B423C
	mov r0, r5
	bl FX_Inv
	mov r1, #0x0
	str r0, [sp, #0x0]
	mov r0, r4
	str r1, [sp, #0x4]
	str r1, [sp, #0x8]
	bl FX_Inv
	mov r3, #0x0
	ldr r1, _020B29E8 ; =UNK_021CDD70
	str r0, [sp, #0xc]
	ldr r2, [r1, #0x0]
	ldr r1, _020B29F0 ; =UNK_021CE1F4
	mov r0, #0x18
	mla r1, r2, r0, r1
	add r0, sp, #0x0
	mov r2, r1
	str r3, [sp, #0x10]
	str r3, [sp, #0x14]
	bl FUN_020B423C
	ldr r0, _020B29F4 ; =UNK_021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020B2978
	ldr r1, _020B29F8 ; =UNK_02106570
	ldr r0, _020B29FC ; =0x0000FFFE
	ldrh r1, [r1, #0x0]
	cmp r1, r0
	movne r0, #0x1
	bne _020B297C
_020B2978:
	mov r0, #0x0
_020B297C:
	cmp r0, #0x0
	ldreq r1, _020B29E8 ; =UNK_021CDD70
	ldreq r0, _020B29F8 ; =UNK_02106570
	ldreq r1, [r1, #0x0]
	streqh r1, [r0, #0x0]
	ldr r0, _020B29E8 ; =UNK_021CDD70
	ldr r1, _020B2A00 ; =UNK_021CDDF4
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x10
	add r12, r1, r0, lsr #0xd
	ldrh r0, [r12, #0x4]
	cmp r0, #0x3
	addls pc, pc, r0, lsl #0x2
	b _020B29E0
	; Jump table
	b _020B29C4 ; case 0
	b _020B29E0 ; case 1
	b _020B29C4 ; case 2
	b _020B29C4 ; case 3
_020B29C4:
	ldr r0, _020B2A04 ; =UNK_021CDD64
	mov r1, #0x1
	ldrh r3, [r0, #0x0]
	add r2, r3, #0x1
	strh r2, [r0, #0x0]
	strh r3, [r12, #0x2]
	strh r1, [r12, #0x4]
_020B29E0:
	add sp, sp, #0x1c
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B29E8: .word UNK_021CDD70
_020B29EC: .word UNK_021CDEF4
_020B29F0: .word UNK_021CE1F4
_020B29F4: .word UNK_021CDD68
_020B29F8: .word UNK_02106570
_020B29FC: .word 0x0000FFFE
_020B2A00: .word UNK_021CDDF4
_020B2A04: .word UNK_021CDD64
	arm_func_end FUN_020B28B4

	; NNS_G2dTranslate
	arm_func_start FUN_020B2A08
FUN_020B2A08: ; 0x020B2A08
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x1c
	ldr r3, _020B2AEC ; =UNK_021CDD68
	mov r4, r2
	ldr r2, [r3, #0x0]
	cmp r2, #0x0
	beq _020B2A6C
	ldr r2, _020B2AF0 ; =UNK_021CDD70
	mov r3, #0x18
	ldr r2, [r2, #0x0]
	ldr lr, _020B2AF4 ; =UNK_021CDF04
	mul r5, r2, r3
	ldr r3, [lr, r5]
	ldr ip, _020B2AF8 ; =UNK_021CDF08
	add r0, r3, r0
	str r0, [lr, r5]
	ldr r0, [r12, r5]
	ldr r3, _020B2AFC ; =UNK_021CDD74
	add r0, r0, r1
	str r0, [r12, r5]
	ldr r0, [r3, r2, lsl #0x2]
	add sp, sp, #0x1c
	add r0, r0, r4
	str r0, [r3, r2, lsl #0x2]
	ldmia sp!, {r4-r5,pc}
_020B2A6C:
	ldr r2, _020B2AF0 ; =UNK_021CDD70
	mov lr, #0x1000
	ldr r12, [r2, #0x0]
	ldr r3, _020B2B00 ; =UNK_021CDEF4
	mov r2, #0x18
	str r1, [sp, #0x14]
	mla r1, r12, r2, r3
	mov r3, #0x0
	str r0, [sp, #0x10]
	add r0, sp, #0x0
	mov r2, r1
	str lr, [sp, #0x0]
	str r3, [sp, #0x4]
	str r3, [sp, #0x8]
	str lr, [sp, #0xc]
	bl FUN_020B423C
	ldr r0, _020B2AF0 ; =UNK_021CDD70
	ldr r1, _020B2B04 ; =UNK_021CE1F4
	ldr r2, [r0, #0x0]
	mov r0, #0x18
	mla r1, r2, r0, r1
	add r0, sp, #0x0
	mov r2, r1
	bl FUN_020B423C
	ldr r0, _020B2AF0 ; =UNK_021CDD70
	ldr r2, _020B2AFC ; =UNK_021CDD74
	ldr r1, [r0, #0x0]
	ldr r0, [r2, r1, lsl #0x2]
	add r0, r0, r4
	str r0, [r2, r1, lsl #0x2]
	add sp, sp, #0x1c
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B2AEC: .word UNK_021CDD68
_020B2AF0: .word UNK_021CDD70
_020B2AF4: .word UNK_021CDF04
_020B2AF8: .word UNK_021CDF08
_020B2AFC: .word UNK_021CDD74
_020B2B00: .word UNK_021CDEF4
_020B2B04: .word UNK_021CE1F4
	arm_func_end FUN_020B2A08

	; NNS_G2dPopMtx
	arm_func_start FUN_020B2B08
FUN_020B2B08: ; 0x020B2B08
	ldr r0, _020B2B4C ; =UNK_021CDD70
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	movle r0, #0x1
	movgt r0, #0x0
	cmp r0, #0x0
	bxne lr
	ldr r1, _020B2B4C ; =UNK_021CDD70
	ldr r0, _020B2B50 ; =UNK_02106570
	ldr r3, [r1, #0x0]
	ldrh r2, [r0, #0x0]
	sub r3, r3, #0x1
	str r3, [r1, #0x0]
	cmp r2, r3
	ldrgt r1, _020B2B54 ; =0x0000FFFE
	strgth r1, [r0, #0x0]
	bx lr
	.balign 4
_020B2B4C: .word UNK_021CDD70
_020B2B50: .word UNK_02106570
_020B2B54: .word 0x0000FFFE
	arm_func_end FUN_020B2B08

	; NNS_G2dPushMtx
	arm_func_start FUN_020B2B58
FUN_020B2B58: ; 0x020B2B58
	stmdb sp!, {r4-r10,lr}
	ldr r0, _020B2D74 ; =UNK_021CDD6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x7c]
	ands r0, r0, #0x1
	bne _020B2CA4
	ldr r0, _020B2D78 ; =UNK_021CDD70
	ldr r1, [r0, #0x0]
	mov r0, r1, lsl #0x10
	add r5, r1, #0x1
	cmp r5, #0x20
	mov r4, r0, lsr #0x10
	movlt r0, #0x1
	movge r0, #0x0
	cmp r0, #0x0
	beq _020B2C44
	ldr r0, _020B2D7C ; =UNK_021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020B2BE4
	ldr r1, _020B2D78 ; =UNK_021CDD70
	mov r0, #0x18
	ldr r3, [r1, #0x0]
	ldr r1, _020B2D80 ; =UNK_021CDD74
	mul r8, r3, r0
	ldr r6, _020B2D84 ; =UNK_021CDF04
	mul r7, r5, r0
	ldr r2, [r6, r8]
	ldr r0, [r1, r3, lsl #0x2]
	ldr r3, _020B2D88 ; =UNK_021CDF08
	str r2, [r6, r7]
	ldr r2, [r3, r8]
	str r0, [r1, r5, lsl #0x2]
	str r2, [r3, r7]
	b _020B2C3C
_020B2BE4:
	ldr r1, _020B2D78 ; =UNK_021CDD70
	mov r0, #0x18
	ldr r2, [r1, #0x0]
	ldr r7, _020B2D80 ; =UNK_021CDD74
	mul lr, r2, r0
	ldr r1, _020B2D8C ; =UNK_021CDEF4
	mul r12, r5, r0
	ldr r8, _020B2D90 ; =UNK_021CE1F4
	add r10, r1, lr
	ldr r6, [r7, r2, lsl #0x2]
	add r9, r1, r12
	ldmia r10!, {r0-r3}
	stmia r9!, {r0-r3}
	ldmia r10, {r0-r1}
	str r6, [r7, r5, lsl #0x2]
	add r7, r8, lr
	stmia r9, {r0-r1}
	add r6, r8, r12
	ldmia r7!, {r0-r3}
	stmia r6!, {r0-r3}
	ldmia r7, {r0-r1}
	stmia r6, {r0-r1}
_020B2C3C:
	ldr r0, _020B2D78 ; =UNK_021CDD70
	str r5, [r0, #0x0]
_020B2C44:
	ldr r0, _020B2D78 ; =UNK_021CDD70
	ldr r2, _020B2D94 ; =UNK_021CDDF4
	ldr r0, [r0, #0x0]
	mov r5, r4, lsl #0x3
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	add r4, r2, r4, lsl #0x3
	mov r6, r3, lsl #0x3
	ldrh r1, [r2, r5]
	ldrh r0, [r4, #0x2]
	add r3, r2, r3, lsl #0x3
	strh r1, [r2, r6]
	strh r0, [r3, #0x2]
	ldrh r2, [r4, #0x4]
	ldrh r0, [r4, #0x6]
	ldr r1, _020B2D98 ; =UNK_021CDDF8
	strh r2, [r3, #0x4]
	strh r0, [r3, #0x6]
	ldrh r0, [r1, r5]
	cmp r0, #0x1
	moveq r0, #0x2
	streqh r0, [r1, r6]
	strneh r0, [r1, r6]
	ldmia sp!, {r4-r10,pc}
_020B2CA4:
	ldr r0, _020B2D78 ; =UNK_021CDD70
	ldr r0, [r0, #0x0]
	add r4, r0, #0x1
	cmp r4, #0x20
	movlt r0, #0x1
	movge r0, #0x0
	cmp r0, #0x0
	ldmeqia sp!, {r4-r10,pc}
	ldr r0, _020B2D7C ; =UNK_021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020B2D10
	ldr r1, _020B2D78 ; =UNK_021CDD70
	mov r0, #0x18
	ldr r3, [r1, #0x0]
	ldr r1, _020B2D80 ; =UNK_021CDD74
	mul r7, r3, r0
	ldr r5, _020B2D84 ; =UNK_021CDF04
	mul r6, r4, r0
	ldr r2, [r5, r7]
	ldr r0, [r1, r3, lsl #0x2]
	ldr r3, _020B2D88 ; =UNK_021CDF08
	str r2, [r5, r6]
	ldr r2, [r3, r7]
	str r0, [r1, r4, lsl #0x2]
	str r2, [r3, r6]
	b _020B2D68
_020B2D10:
	ldr r1, _020B2D78 ; =UNK_021CDD70
	mov r0, #0x18
	ldr r2, [r1, #0x0]
	ldr ip, _020B2D80 ; =UNK_021CDD74
	mul r9, r2, r0
	ldr r1, _020B2D8C ; =UNK_021CDEF4
	mul r8, r4, r0
	ldr lr, _020B2D90 ; =UNK_021CE1F4
	add r6, r1, r9
	ldr r5, [r12, r2, lsl #0x2]
	add r7, r1, r8
	ldmia r6!, {r0-r3}
	stmia r7!, {r0-r3}
	ldmia r6, {r0-r1}
	add r6, lr, r9
	stmia r7, {r0-r1}
	add lr, lr, r8
	ldmia r6!, {r0-r3}
	stmia lr!, {r0-r3}
	ldmia r6, {r0-r1}
	stmia lr, {r0-r1}
	str r5, [r12, r4, lsl #0x2]
_020B2D68:
	ldr r0, _020B2D78 ; =UNK_021CDD70
	str r4, [r0, #0x0]
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020B2D74: .word UNK_021CDD6C
_020B2D78: .word UNK_021CDD70
_020B2D7C: .word UNK_021CDD68
_020B2D80: .word UNK_021CDD74
_020B2D84: .word UNK_021CDF04
_020B2D88: .word UNK_021CDF08
_020B2D8C: .word UNK_021CDEF4
_020B2D90: .word UNK_021CE1F4
_020B2D94: .word UNK_021CDDF4
_020B2D98: .word UNK_021CDDF8
	arm_func_end FUN_020B2B58

	; NNS_G2dDrawMultiCellAnimation
	arm_func_start FUN_020B2D9C
FUN_020B2D9C: ; 0x020B2D9C
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	ldrh r0, [r4, #0x56]
	cmp r0, #0x0
	bne _020B2DBC
	add r0, r4, #0x30
	bl FUN_020B2E78
	ldmia sp!, {r4-r6,pc}
_020B2DBC:
	bl FUN_020B2B58
	ldrh r0, [r4, #0x56]
	ands r0, r0, #0x8
	beq _020B2E0C
	ldr r0, _020B2E70 ; =UNK_021CDD6C
	ldrsh r6, [r4, #0x52]
	ldr r0, [r0, #0x0]
	ldrsh r5, [r4, #0x50]
	bl FUN_020B4F88
	cmp r0, #0x0
	ldr r0, _020B2E70 ; =UNK_021CDD6C
	rsbne r5, r5, #0x0
	ldr r0, [r0, #0x0]
	bl FUN_020B4F74
	cmp r0, #0x0
	rsbne r6, r6, #0x0
	mov r0, r5, lsl #0xc
	mov r1, r6, lsl #0xc
	mov r2, #0x0
	bl FUN_020B2A08
_020B2E0C:
	ldrh r0, [r4, #0x56]
	ands r0, r0, #0x4
	beq _020B2E40
	ldrh r0, [r4, #0x54]
	ldr r2, _020B2E74 ; =FX_SinCosTable_
	mov r0, r0, asr #0x4
	mov r1, r0, lsl #0x1
	add r0, r1, #0x1
	mov r3, r1, lsl #0x1
	mov r1, r0, lsl #0x1
	ldrsh r0, [r2, r3]
	ldrsh r1, [r2, r1]
	bl FUN_020B2794
_020B2E40:
	ldrh r0, [r4, #0x56]
	ands r0, r0, #0x2
	beq _020B2E5C
	ldr r0, [r4, #0x48]
	ldr r1, [r4, #0x4c]
	mov r2, #0x1000
	bl FUN_020B28B4
_020B2E5C:
	add r0, r4, #0x30
	bl FUN_020B2E78
	mov r0, #0x1
	bl FUN_020B2B08
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B2E70: .word UNK_021CDD6C
_020B2E74: .word FX_SinCosTable_
	arm_func_end FUN_020B2D9C

	; NNS_G2dDrawMultiCell
	arm_func_start FUN_020B2E78
FUN_020B2E78: ; 0x020B2E78
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r5, r0
	ldr r0, [r5, #0x8]
	cmp r0, #0x1
	bne _020B309C
	ldr r0, [r5, #0x0]
	mov r2, #0x0
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	bls _020B2ED0
	ldr r3, _020B3174 ; =UNK_021CE8F4
	mov r4, r2
_020B2EAC:
	add r0, r3, r2, lsl #0x2
	str r4, [r0, #0x4]
	ldr r0, [r5, #0x0]
	add r2, r2, #0x1
	ldrh r1, [r0, #0x2]
	mov r0, r2, lsl #0x10
	mov r2, r0, lsr #0x10
	cmp r2, r1
	blo _020B2EAC
_020B2ED0:
	ldr r0, _020B3178 ; =UNK_021CDD6C
	mov r6, #0x1
	ldr r1, [r0, #0x0]
	ldr r0, _020B3174 ; =UNK_021CE8F4
	str r6, [r0, #0x404]
	ldr r0, [r1, #0x80]
	cmp r0, #0x0
	beq _020B2FD8
	bl FUN_020B4948
	str r0, [sp, #0x0]
	mov r0, r6
	bl FUN_020B497C
	ldr r0, _020B3178 ; =UNK_021CDD6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x80]
	bl FUN_020B4958
	ldr r2, [r5, #0x0]
	mov r7, #0x0
	ldrh r0, [r2, #0x0]
	cmp r0, #0x0
	bls _020B2FC0
	mov r11, r7
_020B2F28:
	ldr r0, [r2, #0x4]
	ldr r9, [r5, #0xc]
	add r10, r0, r7, lsl #0x3
	ldrh r0, [r10, #0x6]
	and r0, r0, #0xff00
	mov r0, r0, lsl #0x8
	mov r8, r0, lsr #0x10
	ldr r0, _020B3174 ; =UNK_021CE8F4
	strh r8, [r0, #0x0]
	bl FUN_020B2B58
	ldr r0, _020B3178 ; =UNK_021CDD6C
	ldrsh r4, [r10, #0x4]
	ldr r0, [r0, #0x0]
	ldrsh r10, [r10, #0x2]
	bl FUN_020B4F88
	cmp r0, #0x0
	ldr r0, _020B3178 ; =UNK_021CDD6C
	rsbne r10, r10, #0x0
	ldr r0, [r0, #0x0]
	bl FUN_020B4F74
	cmp r0, #0x0
	rsbne r4, r4, #0x0
	mov r2, r11
	mov r0, r10, lsl #0xc
	mov r1, r4, lsl #0xc
	bl FUN_020B2A08
	mov r0, #0x58
	mla r0, r8, r0, r9
	bl FUN_020B3554
	mov r0, r6
	bl FUN_020B2B08
	ldr r2, [r5, #0x0]
	add r0, r7, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r2, #0x0]
	mov r7, r0, lsr #0x10
	cmp r7, r1
	blo _020B2F28
_020B2FC0:
	mov r0, #0x0
	bl FUN_020B497C
	ldr r0, [sp, #0x0]
	bl FUN_020B4958
	bl FUN_020B4968
	b _020B3088
_020B2FD8:
	ldr r2, [r5, #0x0]
	mov r7, #0x0
	ldrh r0, [r2, #0x0]
	cmp r0, #0x0
	bls _020B3088
	str r7, [sp, #0x4]
	mov r11, #0x58
_020B2FF4:
	ldr r0, [r2, #0x4]
	ldr r9, [r5, #0xc]
	add r10, r0, r7, lsl #0x3
	ldrh r0, [r10, #0x6]
	and r0, r0, #0xff00
	mov r0, r0, lsl #0x8
	mov r8, r0, lsr #0x10
	ldr r0, _020B3174 ; =UNK_021CE8F4
	strh r8, [r0, #0x0]
	bl FUN_020B2B58
	ldr r0, _020B3178 ; =UNK_021CDD6C
	ldrsh r4, [r10, #0x4]
	ldr r0, [r0, #0x0]
	ldrsh r10, [r10, #0x2]
	bl FUN_020B4F88
	cmp r0, #0x0
	ldr r0, _020B3178 ; =UNK_021CDD6C
	rsbne r10, r10, #0x0
	ldr r0, [r0, #0x0]
	bl FUN_020B4F74
	cmp r0, #0x0
	rsbne r4, r4, #0x0
	ldr r2, [sp, #0x4]
	mov r0, r10, lsl #0xc
	mov r1, r4, lsl #0xc
	bl FUN_020B2A08
	mla r0, r8, r11, r9
	bl FUN_020B3554
	mov r0, r6
	bl FUN_020B2B08
	ldr r2, [r5, #0x0]
	add r0, r7, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r2, #0x0]
	mov r7, r0, lsr #0x10
	cmp r7, r1
	blo _020B2FF4
_020B3088:
	ldr r0, _020B3174 ; =UNK_021CE8F4
	mov r1, #0x0
	str r1, [r0, #0x404]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
_020B309C:
	ldr r0, _020B3178 ; =UNK_021CDD6C
	ldr r7, [r5, #0xc]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x80]
	cmp r0, #0x0
	beq _020B312C
	bl FUN_020B4948
	mov r6, r0
	mov r0, #0x1
	bl FUN_020B497C
	ldr r0, _020B3178 ; =UNK_021CDD6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x80]
	bl FUN_020B4958
	ldr r0, [r5, #0x0]
	mov r4, #0x0
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	bls _020B3110
	mov r8, #0x28
_020B30EC:
	mla r0, r4, r8, r7
	bl FUN_020B3474
	ldr r1, [r5, #0x0]
	add r0, r4, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r1, #0x0]
	mov r4, r0, lsr #0x10
	cmp r4, r1
	blo _020B30EC
_020B3110:
	mov r0, #0x0
	bl FUN_020B497C
	mov r0, r6
	bl FUN_020B4958
	bl FUN_020B4968
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
_020B312C:
	ldr r0, [r5, #0x0]
	mov r4, #0x0
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	addls sp, sp, #0xc
	ldmlsia sp!, {r4-r11,pc}
	mov r6, #0x28
_020B3148:
	mla r0, r4, r6, r7
	bl FUN_020B3474
	ldr r1, [r5, #0x0]
	add r0, r4, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r1, #0x0]
	mov r4, r0, lsr #0x10
	cmp r4, r1
	blo _020B3148
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B3174: .word UNK_021CE8F4
_020B3178: .word UNK_021CDD6C
	arm_func_end FUN_020B2E78

	; NNS_G2dDrawCellAnimation
	arm_func_start FUN_020B317C
FUN_020B317C: ; 0x020B317C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _020B31EC ; =UNK_021CDD6C
	mov r5, r0
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x80]
	cmp r1, #0x0
	beq _020B31E0
	bl FUN_020B4948
	mov r4, r0
	mov r0, #0x1
	bl FUN_020B497C
	ldr r0, _020B31EC ; =UNK_021CDD6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x80]
	bl FUN_020B4958
	mov r0, r5
	bl FUN_020B3554
	mov r0, #0x0
	bl FUN_020B497C
	mov r0, r4
	bl FUN_020B4958
	bl FUN_020B4968
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
_020B31E0:
	bl FUN_020B3554
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B31EC: .word UNK_021CDD6C
	arm_func_end FUN_020B317C

	; NNS_G2dEndRendering
	arm_func_start FUN_020B31F0
FUN_020B31F0: ; 0x020B31F0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020B3260 ; =0x04000448
	mov r2, #0x1
	ldr r0, _020B3264 ; =UNK_021CDD6C
	str r2, [r1, #0x0]
	ldr r2, [r0, #0x0]
	ldr r3, [r2, #0x7c]
	cmp r3, #0x0
	beq _020B324C
	ands r0, r3, #0x1
	ldrne r0, _020B3268 ; =UNK_021CDD68
	movne r1, #0x0
	strne r1, [r0, #0x0]
	ands r0, r3, #0x2
	beq _020B323C
	mov r0, #0x0
	str r0, [r2, #0x74]
	bl FUN_020B4DA0
_020B323C:
	ldr r0, _020B3264 ; =UNK_021CDD6C
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x7c]
_020B324C:
	ldr r0, _020B3264 ; =UNK_021CDD6C
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B3260: .word 0x04000448
_020B3264: .word UNK_021CDD6C
_020B3268: .word UNK_021CDD68
	arm_func_end FUN_020B31F0

	; NNS_G2dBeginRendering
	arm_func_start FUN_020B326C
FUN_020B326C: ; 0x020B326C
	stmdb sp!, {r4-r8,lr}
	ldr r5, _020B330C ; =UNK_021CDD60
	ldr r3, _020B3310 ; =UNK_021CDD6C
	ldrh r6, [r5, #0x0]
	ldr r2, _020B3314 ; =UNK_021CDD70
	mov r4, #0x0
	ldr r7, _020B3318 ; =0x0000FFFE
	ldr r1, _020B331C ; =UNK_02106570
	str r0, [r3, #0x0]
	str r4, [r2, #0x0]
	strh r7, [r1, #0x0]
	cmp r6, #0x0
	ble _020B32D0
	ldr r8, _020B3320 ; =UNK_021CE4F4
	mvn r7, #0x0
	mov r6, #0x10
_020B32AC:
	mov r0, r7
	mov r2, r6
	add r1, r8, #0x10
	bl MIi_CpuClearFast
	ldrh r0, [r5, #0x0]
	add r4, r4, #0x1
	add r8, r8, #0x20
	cmp r4, r0
	blt _020B32AC
_020B32D0:
	ldr r4, _020B330C ; =UNK_021CDD60
	mov r0, #0x0
	ldr r3, _020B3324 ; =UNK_021CDD64
	ldr r1, _020B3328 ; =UNK_021CDDF4
	mov r2, #0x100
	strh r0, [r4, #0x0]
	strh r0, [r3, #0x0]
	bl MIi_CpuClearFast
	ldr r1, _020B332C ; =0x04000444
	mov r2, #0x0
	ldr r0, _020B3330 ; =0x04000454
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	bl FUN_020B4178
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020B330C: .word UNK_021CDD60
_020B3310: .word UNK_021CDD6C
_020B3314: .word UNK_021CDD70
_020B3318: .word 0x0000FFFE
_020B331C: .word UNK_02106570
_020B3320: .word UNK_021CE4F4
_020B3324: .word UNK_021CDD64
_020B3328: .word UNK_021CDDF4
_020B332C: .word 0x04000444
_020B3330: .word 0x04000454
	arm_func_end FUN_020B326C

	; NNS_G2dInitRenderSurface
	arm_func_start FUN_020B3334
FUN_020B3334: ; 0x020B3334
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r1, r4
	mov r0, #0x0
	mov r2, #0x48
	bl MIi_CpuClear16
	mov r0, #0x1
	str r0, [r4, #0x10]
	mov r0, #0x3
	ldr r1, _020B3380 ; =FUN_020B3EE0
	str r0, [r4, #0x14]
	ldr r0, _020B3384 ; =FUN_020B3E48
	str r1, [r4, #0x18]
	ldr r1, _020B3388 ; =FUN_020B3C40
	str r0, [r4, #0x1c]
	ldr r0, _020B338C ; =FUN_020B3B90
	str r1, [r4, #0x20]
	str r0, [r4, #0x24]
	ldmia sp!, {r4,pc}
	.balign 4
_020B3380: .word FUN_020B3EE0
_020B3384: .word FUN_020B3E48
_020B3388: .word FUN_020B3C40
_020B338C: .word FUN_020B3B90
	arm_func_end FUN_020B3334

	; _end
	arm_func_start FUN_020B3390
FUN_020B3390: ; 0x020B3390
	ldr r2, [r0, #0x70]
	str r2, [r1, #0x30]
	str r1, [r0, #0x70]
	bx lr
	arm_func_end FUN_020B3390

	; NNS_G2dInitRenderer
	arm_func_start FUN_020B33A0
FUN_020B33A0: ; 0x020B33A0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r0
	bl FUN_020B504C
	mov r7, #0x0
	str r7, [r4, #0x70]
	str r7, [r4, #0x74]
	str r7, [r4, #0x78]
	str r7, [r4, #0x7c]
	str r7, [r4, #0x80]
	str r7, [r4, #0x84]
	strh r7, [r4, #0x88]
	strh r7, [r4, #0x8a]
	str r7, [r4, #0x8c]
	str r7, [r4, #0x90]
	ldr r1, _020B3454 ; =UNK_021CDD70
	strh r7, [r4, #0x94]
	ldr r2, _020B3458 ; =0x0000FFFE
	ldr r0, _020B345C ; =UNK_02106570
	ldr r6, _020B3460 ; =UNK_021CE4F4
	str r7, [r1, #0x0]
	strh r2, [r0, #0x0]
	mvn r5, #0x0
	mov r4, #0x10
_020B3400:
	mov r0, r5
	mov r2, r4
	add r1, r6, #0x10
	bl MIi_CpuClearFast
	add r7, r7, #0x1
	cmp r7, #0x20
	add r6, r6, #0x20
	blt _020B3400
	ldr ip, _020B3464 ; =UNK_021CDD60
	mov r0, #0x0
	ldr r3, _020B3468 ; =UNK_021CDD64
	ldr r1, _020B346C ; =UNK_021CDDF4
	mov r2, #0x100
	strh r0, [r12, #0x0]
	strh r0, [r3, #0x0]
	bl MIi_CpuClearFast
	ldr r0, _020B3470 ; =UNK_021CDD68
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B3454: .word UNK_021CDD70
_020B3458: .word 0x0000FFFE
_020B345C: .word UNK_02106570
_020B3460: .word UNK_021CE4F4
_020B3464: .word UNK_021CDD60
_020B3468: .word UNK_021CDD64
_020B346C: .word UNK_021CDDF4
_020B3470: .word UNK_021CDD68
	arm_func_end FUN_020B33A0

	; DrawNode_
	arm_func_start FUN_020B3474
FUN_020B3474: ; 0x020B3474
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
	ldr r4, [r5, #0x0]
	bl FUN_020B2B58
	ldrh r0, [r5, #0x1e]
	ands r0, r0, #0x8
	beq _020B34E4
	ldr r0, _020B354C ; =UNK_021CDD6C
	ldrsh r7, [r5, #0x1a]
	ldr r0, [r0, #0x0]
	ldrsh r6, [r5, #0x18]
	bl FUN_020B4F88
	cmp r0, #0x0
	ldr r0, _020B354C ; =UNK_021CDD6C
	rsbne r6, r6, #0x0
	ldr r0, [r0, #0x0]
	bl FUN_020B4F74
	cmp r0, #0x0
	rsbne r7, r7, #0x0
	mov r0, r6, lsl #0xc
	mov r1, r7, lsl #0xc
	mov r2, #0x0
	bl FUN_020B2A08
_020B34E4:
	ldrh r0, [r5, #0x1e]
	ands r0, r0, #0x4
	beq _020B3518
	ldrh r0, [r5, #0x1c]
	ldr r2, _020B3550 ; =FX_SinCosTable_
	mov r0, r0, asr #0x4
	mov r1, r0, lsl #0x1
	add r0, r1, #0x1
	mov r3, r1, lsl #0x1
	mov r1, r0, lsl #0x1
	ldrsh r0, [r2, r3]
	ldrsh r1, [r2, r1]
	bl FUN_020B2794
_020B3518:
	ldrh r0, [r5, #0x1e]
	ands r0, r0, #0x2
	beq _020B3534
	ldr r0, [r5, #0x10]
	ldr r1, [r5, #0x14]
	mov r2, #0x1000
	bl FUN_020B28B4
_020B3534:
	mov r0, r4
	bl FUN_020B3554
	mov r0, #0x1
	bl FUN_020B2B08
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B354C: .word UNK_021CDD6C
_020B3550: .word FX_SinCosTable_
	arm_func_end FUN_020B3474

	; DrawCellAnimationImpl_
	arm_func_start FUN_020B3554
FUN_020B3554: ; 0x020B3554
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrh r0, [r5, #0x4a]
	ldr r4, [r5, #0x2c]
	cmp r0, #0x0
	bne _020B35C0
	ldr r2, [r5, #0x34]
	mvn r0, #0x0
	cmp r2, r0
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020B35B0
	ldr r1, _020B36B4 ; =UNK_02106574
	mov r0, r4
	str r2, [r1, #0x0]
	bl FUN_020B36C0
	ldr r0, _020B36B4 ; =UNK_02106574
	mvn r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
_020B35B0:
	mov r0, r4
	bl FUN_020B36C0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
_020B35C0:
	bl FUN_020B2B58
	ldrh r0, [r5, #0x4a]
	ands r0, r0, #0x8
	beq _020B3610
	ldr r0, _020B36B8 ; =UNK_021CDD6C
	ldrsh r7, [r5, #0x46]
	ldr r0, [r0, #0x0]
	ldrsh r6, [r5, #0x44]
	bl FUN_020B4F88
	cmp r0, #0x0
	ldr r0, _020B36B8 ; =UNK_021CDD6C
	rsbne r6, r6, #0x0
	ldr r0, [r0, #0x0]
	bl FUN_020B4F74
	cmp r0, #0x0
	rsbne r7, r7, #0x0
	mov r0, r6, lsl #0xc
	mov r1, r7, lsl #0xc
	mov r2, #0x0
	bl FUN_020B2A08
_020B3610:
	ldrh r0, [r5, #0x4a]
	ands r0, r0, #0x4
	beq _020B3644
	ldrh r0, [r5, #0x48]
	ldr r2, _020B36BC ; =FX_SinCosTable_
	mov r0, r0, asr #0x4
	mov r1, r0, lsl #0x1
	add r0, r1, #0x1
	mov r3, r1, lsl #0x1
	mov r1, r0, lsl #0x1
	ldrsh r0, [r2, r3]
	ldrsh r1, [r2, r1]
	bl FUN_020B2794
_020B3644:
	ldrh r0, [r5, #0x4a]
	ands r0, r0, #0x2
	beq _020B3660
	ldr r0, [r5, #0x3c]
	ldr r1, [r5, #0x40]
	mov r2, #0x1000
	bl FUN_020B28B4
_020B3660:
	ldr r2, [r5, #0x34]
	mvn r0, #0x0
	cmp r2, r0
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020B369C
	ldr r1, _020B36B4 ; =UNK_02106574
	mov r0, r4
	str r2, [r1, #0x0]
	bl FUN_020B36C0
	ldr r0, _020B36B4 ; =UNK_02106574
	mvn r1, #0x0
	str r1, [r0, #0x0]
	b _020B36A4
_020B369C:
	mov r0, r4
	bl FUN_020B36C0
_020B36A4:
	mov r0, #0x1
	bl FUN_020B2B08
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B36B4: .word UNK_02106574
_020B36B8: .word UNK_021CDD6C
_020B36BC: .word FX_SinCosTable_
	arm_func_end FUN_020B3554

	; DrawCellImpl_
	arm_func_start FUN_020B36C0
FUN_020B36C0: ; 0x020B36C0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r5, _020B3B54 ; =UNK_021CDD6C
	mov r10, r0
	ldr r0, [r5, #0x0]
	ldr r1, [r0, #0x7c]
	str r0, [sp, #0x0]
	ldr r9, [r0, #0x70]
	ands r0, r1, #0x2
	beq _020B38EC
	ldr r0, [r9, #0x14]
	cmp r0, #0x0
	beq _020B3840
	ldr r0, _020B3B58 ; =UNK_021CDD68
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020B3720
	ldr r2, _020B3B5C ; =UNK_02106570
	ldr r0, _020B3B60 ; =0x0000FFFE
	ldrh r2, [r2, #0x0]
	cmp r2, r0
	movne r0, #0x1
	bne _020B3724
_020B3720:
	mov r0, #0x0
_020B3724:
	cmp r0, #0x0
	beq _020B37AC
	ldr r0, _020B3B64 ; =UNK_021CE8F4
	ldr r1, [r0, #0x404]
	cmp r1, #0x0
	beq _020B3788
	ldrh r1, [r0, #0x0]
	ldr r0, _020B3B68 ; =UNK_021CE8F8
	ldr r1, [r0, r1, lsl #0x2]
	cmp r1, #0x0
	bne _020B37AC
	bl FUN_020B4010
	ldr r0, _020B3B6C ; =UNK_021CDD70
	ldr r2, _020B3B70 ; =UNK_021CDDF4
	ldr r0, [r0, #0x0]
	ldr r1, _020B3B64 ; =UNK_021CE8F4
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0xd
	ldrh r3, [r2, r0]
	ldr r4, _020B3B74 ; =UNK_021CE4F4
	ldrh r2, [r1, #0x0]
	ldr r0, _020B3B68 ; =UNK_021CE8F8
	add r1, r4, r3, lsl #0x5
	str r1, [r0, r2, lsl #0x2]
	b _020B37AC
_020B3788:
	bl FUN_020B4010
	ldr r0, _020B3B6C ; =UNK_021CDD70
	ldr r1, _020B3B70 ; =UNK_021CDDF4
	ldr r0, [r0, #0x0]
	ldr r2, _020B3B74 ; =UNK_021CE4F4
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0xd
	ldrh r0, [r1, r0]
	add r1, r2, r0, lsl #0x5
_020B37AC:
	ldr r0, _020B3B58 ; =UNK_021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldreq r0, _020B3B6C ; =UNK_021CDD70
	ldreq r3, _020B3B78 ; =UNK_021CDEF4
	ldreq r2, [r0, #0x0]
	moveq r0, #0x18
	mlaeq r0, r2, r0, r3
	beq _020B37FC
	ldr r2, _020B3B6C ; =UNK_021CDD70
	mov r0, #0x18
	ldr r2, [r2, #0x0]
	ldr r3, _020B3B7C ; =UNK_021CDF04
	mul r4, r2, r0
	ldr r2, _020B3B80 ; =UNK_021CDF08
	ldr r3, [r3, r4]
	ldr r0, _020B3B84 ; =UNK_02106578
	ldr r2, [r2, r4]
	str r3, [r0, #0x10]
	str r2, [r0, #0x14]
_020B37FC:
	bl FUN_020B4FAC
	ldr r1, _020B3B88 ; =UNK_02106574
	mvn r0, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, r0
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020B3830
	mov r0, r10
	bl FUN_020B4BF4
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
_020B3830:
	mov r0, r10
	bl FUN_020B4CDC
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
_020B3840:
	ldr r0, _020B3B6C ; =UNK_021CDD70
	ldr r1, _020B3B8C ; =UNK_021CDD74
	ldr r2, [r0, #0x0]
	ldr r0, [sp, #0x0]
	ldr r1, [r1, r2, lsl #0x2]
	bl FUN_020B4FA4
	ldr r0, _020B3B58 ; =UNK_021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldreq r0, _020B3B6C ; =UNK_021CDD70
	ldreq r2, _020B3B78 ; =UNK_021CDEF4
	ldreq r1, [r0, #0x0]
	moveq r0, #0x18
	mlaeq r0, r1, r0, r2
	beq _020B38A8
	ldr r1, _020B3B6C ; =UNK_021CDD70
	mov r0, #0x18
	ldr r1, [r1, #0x0]
	ldr r2, _020B3B7C ; =UNK_021CDF04
	mul r3, r1, r0
	ldr r1, _020B3B80 ; =UNK_021CDF08
	ldr r2, [r2, r3]
	ldr r0, _020B3B84 ; =UNK_02106578
	ldr r1, [r1, r3]
	str r2, [r0, #0x10]
	str r1, [r0, #0x14]
_020B38A8:
	bl FUN_020B4FC4
	ldr r1, _020B3B88 ; =UNK_02106574
	mvn r0, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, r0
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020B38DC
	mov r0, r10
	bl FUN_020B4BF4
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
_020B38DC:
	mov r0, r10
	bl FUN_020B4CDC
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
_020B38EC:
	cmp r9, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r11,pc}
	ldr r4, _020B3B6C ; =UNK_021CDD70
	ldr fp, _020B3B78 ; =UNK_021CDEF4
	mov r7, #0x0
	mov r6, #0x1
_020B3908:
	ldr r0, [r9, #0x10]
	cmp r0, #0x0
	beq _020B3B40
	ldr r0, [r9, #0x14]
	cmp r0, #0x0
	beq _020B3A8C
	ldr r8, [r5, #0x0]
	mov r1, r9
	str r9, [r8, #0x74]
	mov r0, r8
	bl FUN_020B4F9C
	ldr r1, [r9, #0x28]
	ldr r2, [r9, #0x2c]
	mov r0, r8
	bl FUN_020B5034
	mov r0, r8
	bl FUN_020B4E0C
	ldr r0, _020B3B58 ; =UNK_021CDD68
	mov r1, r7
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020B3978
	ldr r0, _020B3B5C ; =UNK_02106570
	ldrh r2, [r0, #0x0]
	ldr r0, _020B3B60 ; =0x0000FFFE
	cmp r2, r0
	movne r0, r6
	bne _020B397C
_020B3978:
	mov r0, r7
_020B397C:
	cmp r0, #0x0
	beq _020B3A04
	ldr r0, _020B3B64 ; =UNK_021CE8F4
	ldr r0, [r0, #0x404]
	cmp r0, #0x0
	beq _020B39E4
	ldr r0, _020B3B64 ; =UNK_021CE8F4
	ldrh r1, [r0, #0x0]
	add r0, r0, r1, lsl #0x2
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	bne _020B3A04
	bl FUN_020B4010
	ldr r0, _020B3B64 ; =UNK_021CE8F4
	ldr r2, [r4, #0x0]
	ldrh r1, [r0, #0x0]
	mov r0, r2, lsl #0x10
	mov r2, r0, lsr #0xd
	ldr r0, _020B3B70 ; =UNK_021CDDF4
	ldrh r3, [r0, r2]
	ldr r0, _020B3B64 ; =UNK_021CE8F4
	add r2, r0, r1, lsl #0x2
	ldr r0, _020B3B74 ; =UNK_021CE4F4
	add r1, r0, r3, lsl #0x5
	str r1, [r2, #0x4]
	b _020B3A04
_020B39E4:
	bl FUN_020B4010
	ldr r0, [r4, #0x0]
	mov r0, r0, lsl #0x10
	mov r1, r0, lsr #0xd
	ldr r0, _020B3B70 ; =UNK_021CDDF4
	ldrh r1, [r0, r1]
	ldr r0, _020B3B74 ; =UNK_021CE4F4
	add r1, r0, r1, lsl #0x5
_020B3A04:
	ldr r0, _020B3B58 ; =UNK_021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldreq r2, [r4, #0x0]
	moveq r0, #0x18
	mlaeq r0, r2, r0, r11
	beq _020B3A44
	ldr r2, [r4, #0x0]
	mov r0, #0x18
	mla r8, r2, r0, r11
	ldr r0, _020B3B84 ; =UNK_02106578
	ldr r3, [r8, #0x10]
	mov r2, r0
	str r3, [r2, #0x10]
	ldr r3, [r8, #0x14]
	str r3, [r2, #0x14]
_020B3A44:
	bl FUN_020B4FAC
	ldr r0, _020B3B88 ; =UNK_02106574
	ldr r1, [r0, #0x0]
	mvn r0, #0x0
	cmp r1, r0
	movne r0, r6
	moveq r0, r7
	cmp r0, #0x0
	beq _020B3A74
	mov r0, r10
	bl FUN_020B4BF4
	b _020B3A7C
_020B3A74:
	mov r0, r10
	bl FUN_020B4CDC
_020B3A7C:
	ldr r0, [r5, #0x0]
	str r7, [r0, #0x74]
	bl FUN_020B4DA0
	b _020B3B40
_020B3A8C:
	ldr r8, [r5, #0x0]
	mov r1, r9
	mov r0, r8
	str r9, [r8, #0x74]
	bl FUN_020B4F9C
	mov r0, r8
	bl FUN_020B4E0C
	ldr r2, [r4, #0x0]
	ldr r1, _020B3B8C ; =UNK_021CDD74
	ldr r0, [sp, #0x0]
	ldr r1, [r1, r2, lsl #0x2]
	bl FUN_020B4FA4
	ldr r0, _020B3B58 ; =UNK_021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldreq r1, [r4, #0x0]
	moveq r0, #0x18
	mlaeq r0, r1, r0, r11
	beq _020B3AFC
	ldr r1, [r4, #0x0]
	mov r0, #0x18
	mla r3, r1, r0, r11
	ldr r0, _020B3B84 ; =UNK_02106578
	ldr r2, [r3, #0x10]
	mov r1, r0
	str r2, [r1, #0x10]
	ldr r2, [r3, #0x14]
	str r2, [r1, #0x14]
_020B3AFC:
	bl FUN_020B4FC4
	ldr r0, _020B3B88 ; =UNK_02106574
	ldr r1, [r0, #0x0]
	mvn r0, #0x0
	cmp r1, r0
	movne r0, r6
	moveq r0, r7
	cmp r0, #0x0
	beq _020B3B2C
	mov r0, r10
	bl FUN_020B4BF4
	b _020B3B34
_020B3B2C:
	mov r0, r10
	bl FUN_020B4CDC
_020B3B34:
	ldr r0, [r5, #0x0]
	str r7, [r0, #0x74]
	bl FUN_020B4DA0
_020B3B40:
	ldr r9, [r9, #0x30]
	cmp r9, #0x0
	bne _020B3908
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B3B54: .word UNK_021CDD6C
_020B3B58: .word UNK_021CDD68
_020B3B5C: .word UNK_02106570
_020B3B60: .word 0x0000FFFE
_020B3B64: .word UNK_021CE8F4
_020B3B68: .word UNK_021CE8F8
_020B3B6C: .word UNK_021CDD70
_020B3B70: .word UNK_021CDDF4
_020B3B74: .word UNK_021CE4F4
_020B3B78: .word UNK_021CDEF4
_020B3B7C: .word UNK_021CDF04
_020B3B80: .word UNK_021CDF08
_020B3B84: .word UNK_02106578
_020B3B88: .word UNK_02106574
_020B3B8C: .word UNK_021CDD74
	arm_func_end FUN_020B36C0

	; RndCoreCBFuncAfterOBJ_
	arm_func_start FUN_020B3B90
FUN_020B3B90: ; 0x020B3B90
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	ldr r0, _020B3C24 ; =UNK_021CDD6C
	mov r12, r1
	ldr r0, [r0, #0x0]
	mov r3, r2
	ldr r1, [r0, #0x74]
	ldr r2, [r1, #0x44]
	cmp r2, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r6,pc}
	ldr r2, _020B3C28 ; =UNK_021CDD68
	ldr r2, [r2, #0x0]
	cmp r2, #0x0
	ldreq r2, _020B3C2C ; =UNK_021CDD70
	ldreq r4, _020B3C30 ; =UNK_021CDEF4
	ldreq lr, [r2, #0x0]
	moveq r2, #0x18
	mlaeq r6, lr, r2, r4
	beq _020B3C0C
	ldr lr, _020B3C2C ; =UNK_021CDD70
	mov r2, #0x18
	ldr lr, [lr, #0x0]
	ldr r4, _020B3C34 ; =UNK_021CDF04
	mul r5, lr, r2
	ldr r2, _020B3C38 ; =UNK_021CDF08
	ldr r4, [r4, r5]
	ldr r6, _020B3C3C ; =UNK_02106578
	ldr r2, [r2, r5]
	str r4, [r6, #0x10]
	str r2, [r6, #0x14]
_020B3C0C:
	str r6, [sp, #0x0]
	ldr lr, [r1, #0x44]
	mov r2, r12
	blx lr
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B3C24: .word UNK_021CDD6C
_020B3C28: .word UNK_021CDD68
_020B3C2C: .word UNK_021CDD70
_020B3C30: .word UNK_021CDEF4
_020B3C34: .word UNK_021CDF04
_020B3C38: .word UNK_021CDF08
_020B3C3C: .word UNK_02106578
	arm_func_end FUN_020B3B90

	; RndCoreCBFuncBeforeOBJ_
	arm_func_start FUN_020B3C40
FUN_020B3C40: ; 0x020B3C40
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	ldr r3, _020B3E2C ; =UNK_021CDD6C
	add r4, r0, #0x38
	ldr r0, [r3, #0x0]
	mov r6, r1
	mov r5, r2
	bl FUN_020B278C
	cmp r0, #0x0
	beq _020B3C90
	ldrh r1, [r4, #0x4]
	and r1, r1, #0xf000
	mov r1, r1, lsl #0x4
	mov r1, r1, lsr #0x10
	bl FUN_020B10B0
	ldr r1, [r4, #0x4]
	and r0, r0, #0xf
	bic r1, r1, #0xf000
	orr r0, r1, r0, lsl #0xc
	str r0, [r4, #0x4]
_020B3C90:
	ldr r0, _020B3E2C ; =UNK_021CDD6C
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x84]
	cmp r0, #0x0
	beq _020B3DA4
	ldr r0, [r1, #0x84]
	ands r0, r0, #0x1
	beq _020B3CC8
	ldrh r0, [r1, #0x88]
	ldr r1, [r4, #0x4]
	bic r1, r1, #0xc00
	and r0, r0, #0x3
	orr r0, r1, r0, lsl #0xa
	str r0, [r4, #0x4]
_020B3CC8:
	ldr r0, _020B3E2C ; =UNK_021CDD6C
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x84]
	ands r0, r0, #0x2
	beq _020B3CF4
	ldrh r0, [r1, #0x8a]
	ldr r1, [r4, #0x4]
	bic r1, r1, #0xf000
	and r0, r0, #0xf
	orr r0, r1, r0, lsl #0xc
	str r0, [r4, #0x4]
_020B3CF4:
	ldr r0, _020B3E2C ; =UNK_021CDD6C
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x84]
	ands r0, r0, #0x10
	beq _020B3D2C
	ldr r2, [r4, #0x4]
	ldrh r0, [r1, #0x94]
	mov r1, r2, lsl #0x10
	bic r2, r2, #0xf000
	add r0, r0, r1, lsr #0x1c
	and r0, r0, #0xf
	and r0, r0, #0xf
	orr r0, r2, r0, lsl #0xc
	str r0, [r4, #0x4]
_020B3D2C:
	ldr r0, _020B3E2C ; =UNK_021CDD6C
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x84]
	ands r0, r0, #0x4
	beq _020B3D60
	ldr r0, [r1, #0x90]
	cmp r0, #0x0
	ldrne r0, [r4, #0x0]
	orrne r0, r0, #0x1000
	strne r0, [r4, #0x0]
	ldreq r0, [r4, #0x0]
	biceq r0, r0, #0x1000
	streq r0, [r4, #0x0]
_020B3D60:
	ldr r0, _020B3E2C ; =UNK_021CDD6C
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x84]
	ands r0, r0, #0x8
	beq _020B3DA4
	ldr r0, [r4, #0x0]
	ldrh r2, [r4, #0x4]
	ldr r1, [r1, #0x8c]
	bic r0, r0, #0xc00
	orr r0, r0, r1, lsl #0xa
	str r0, [r4, #0x0]
	ldrh r0, [r4, #0x4]
	and r1, r2, #0xf000
	mov r1, r1, asr #0xc
	bic r0, r0, #0xf000
	orr r0, r0, r1, lsl #0xc
	strh r0, [r4, #0x4]
_020B3DA4:
	ldr r0, _020B3E2C ; =UNK_021CDD6C
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x74]
	ldr r2, [r1, #0x40]
	cmp r2, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r6,pc}
	ldr r2, _020B3E30 ; =UNK_021CDD68
	ldr r2, [r2, #0x0]
	cmp r2, #0x0
	ldreq r2, _020B3E34 ; =UNK_021CDD70
	ldreq r4, _020B3E38 ; =UNK_021CDEF4
	ldreq r3, [r2, #0x0]
	moveq r2, #0x18
	mlaeq r4, r3, r2, r4
	beq _020B3E10
	ldr r3, _020B3E34 ; =UNK_021CDD70
	mov r2, #0x18
	ldr r4, [r3, #0x0]
	ldr r3, _020B3E3C ; =UNK_021CDF04
	mul r12, r4, r2
	ldr r2, _020B3E40 ; =UNK_021CDF08
	ldr r3, [r3, r12]
	ldr r4, _020B3E44 ; =UNK_02106578
	ldr r2, [r2, r12]
	str r3, [r4, #0x10]
	str r2, [r4, #0x14]
_020B3E10:
	str r4, [sp, #0x0]
	ldr r4, [r1, #0x40]
	mov r2, r6
	mov r3, r5
	blx r4
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B3E2C: .word UNK_021CDD6C
_020B3E30: .word UNK_021CDD68
_020B3E34: .word UNK_021CDD70
_020B3E38: .word UNK_021CDEF4
_020B3E3C: .word UNK_021CDF04
_020B3E40: .word UNK_021CDF08
_020B3E44: .word UNK_02106578
	arm_func_end FUN_020B3C40

	; RndCoreCBFuncAfterCell_
	arm_func_start FUN_020B3E48
FUN_020B3E48: ; 0x020B3E48
	stmdb sp!, {r4,lr}
	ldr r0, _020B3EC4 ; =UNK_021CDD6C
	mov r2, r1
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x74]
	ldr r3, [r1, #0x3c]
	cmp r3, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r3, _020B3EC8 ; =UNK_021CDD68
	ldr r3, [r3, #0x0]
	cmp r3, #0x0
	ldreq r3, _020B3ECC ; =UNK_021CDD70
	ldreq lr, _020B3ED0 ; =UNK_021CDEF4
	ldreq r12, [r3, #0x0]
	moveq r3, #0x18
	mlaeq r3, r12, r3, lr
	beq _020B3EB8
	ldr ip, _020B3ECC ; =UNK_021CDD70
	mov r3, #0x18
	ldr r12, [r12, #0x0]
	ldr lr, _020B3ED4 ; =UNK_021CDF04
	mul r4, r12, r3
	ldr ip, _020B3ED8 ; =UNK_021CDF08
	ldr lr, [lr, r4]
	ldr r3, _020B3EDC ; =UNK_02106578
	ldr r12, [r12, r4]
	str lr, [r3, #0x10]
	str r12, [r3, #0x14]
_020B3EB8:
	ldr r12, [r1, #0x3c]
	blx r12
	ldmia sp!, {r4,pc}
	.balign 4
_020B3EC4: .word UNK_021CDD6C
_020B3EC8: .word UNK_021CDD68
_020B3ECC: .word UNK_021CDD70
_020B3ED0: .word UNK_021CDEF4
_020B3ED4: .word UNK_021CDF04
_020B3ED8: .word UNK_021CDF08
_020B3EDC: .word UNK_02106578
	arm_func_end FUN_020B3E48

	; RndCoreCBFuncBeforeCell_
	arm_func_start FUN_020B3EE0
FUN_020B3EE0: ; 0x020B3EE0
	stmdb sp!, {r4-r6,lr}
	ldr r2, _020B3FF4 ; =UNK_021CDD6C
	mov r6, r0
	ldr r0, [r2, #0x0]
	mov r5, r1
	ldr r4, [r0, #0x74]
	ldr r0, [r4, #0x34]
	cmp r0, #0x0
	beq _020B3F7C
	ldr r0, _020B3FF8 ; =UNK_021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldreq r0, _020B3FFC ; =UNK_021CDD70
	ldreq r1, _020B4000 ; =UNK_021CDEF4
	ldreq r2, [r0, #0x0]
	moveq r0, #0x18
	mlaeq r1, r2, r0, r1
	beq _020B3F54
	ldr r1, _020B3FFC ; =UNK_021CDD70
	mov r0, #0x18
	ldr r2, [r1, #0x0]
	ldr r1, _020B4004 ; =UNK_021CDF04
	mul r3, r2, r0
	ldr r0, _020B4008 ; =UNK_021CDF08
	ldr r2, [r1, r3]
	ldr r1, _020B400C ; =UNK_02106578
	ldr r0, [r0, r3]
	str r2, [r1, #0x10]
	str r0, [r1, #0x14]
_020B3F54:
	ldr r3, [r4, #0x34]
	mov r0, r5
	mov r2, r4
	blx r3
	cmp r0, #0x0
	moveq r0, #0x0
	streq r0, [r6, #0x30]
	ldmeqia sp!, {r4-r6,pc}
	mov r0, #0x1
	str r0, [r6, #0x30]
_020B3F7C:
	ldr r0, [r4, #0x38]
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r0, _020B3FF8 ; =UNK_021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldreq r0, _020B3FFC ; =UNK_021CDD70
	ldreq r2, _020B4000 ; =UNK_021CDEF4
	ldreq r1, [r0, #0x0]
	moveq r0, #0x18
	mlaeq r3, r1, r0, r2
	beq _020B3FD8
	ldr r1, _020B3FFC ; =UNK_021CDD70
	mov r0, #0x18
	ldr r2, [r1, #0x0]
	ldr r1, _020B4004 ; =UNK_021CDF04
	mul r6, r2, r0
	ldr r0, _020B4008 ; =UNK_021CDF08
	ldr r1, [r1, r6]
	ldr r3, _020B400C ; =UNK_02106578
	ldr r0, [r0, r6]
	str r1, [r3, #0x10]
	str r0, [r3, #0x14]
_020B3FD8:
	ldr r0, _020B3FF4 ; =UNK_021CDD6C
	ldr r6, [r4, #0x38]
	ldr r0, [r0, #0x0]
	mov r1, r4
	mov r2, r5
	blx r6
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B3FF4: .word UNK_021CDD6C
_020B3FF8: .word UNK_021CDD68
_020B3FFC: .word UNK_021CDD70
_020B4000: .word UNK_021CDEF4
_020B4004: .word UNK_021CDF04
_020B4008: .word UNK_021CDF08
_020B400C: .word UNK_02106578
	arm_func_end FUN_020B3EE0

	; NNSi_G2dMCMStoreCurrentMtxToMtxCache
	arm_func_start FUN_020B4010
FUN_020B4010: ; 0x020B4010
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020B4154 ; =UNK_021CDD70
	ldr r1, _020B4158 ; =UNK_021CDDF4
	ldr r0, [r0, #0x0]
	mov r2, #0x1
	mov r0, r0, lsl #0x10
	add r3, r1, r0, lsr #0xd
	ldrh r0, [r3, #0x4]
	cmp r0, #0x1
	beq _020B4044
	cmp r0, #0x2
	movne r2, #0x0
_020B4044:
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
	ldr r0, _020B415C ; =UNK_021CDD60
	mov r2, #0x10
	ldrh r4, [r0, #0x0]
	cmp r4, #0x1f
	addcc r1, r4, #0x1
	strcch r1, [r0, #0x0]
	ldr r0, _020B4160 ; =UNK_021CE4F4
	ldrh r5, [r3, #0x2]
	add r0, r0, r4, lsl #0x5
	add r1, r0, #0x10
	mvn r0, #0x0
	strh r4, [r3, #0x0]
	bl MIi_CpuClearFast
	ldr r0, _020B4154 ; =UNK_021CDD70
	ldr r1, _020B4164 ; =UNK_021CDD68
	ldr r0, [r0, #0x0]
	ldr r2, [r1, #0x0]
	mov r1, r0, lsl #0x10
	cmp r2, #0x0
	ldr r3, _020B4158 ; =UNK_021CDDF4
	mov r1, r1, lsr #0xd
	ldrh r1, [r3, r1]
	ldr r3, _020B4160 ; =UNK_021CE4F4
	moveq r2, #0x18
	add r1, r3, r1, lsl #0x5
	ldreq r3, _020B4168 ; =UNK_021CE1F4
	mlaeq r12, r0, r2, r3
	beq _020B40E4
	mov r2, #0x18
	mul r3, r0, r2
	ldr r2, _020B416C ; =UNK_021CDF04
	ldr r0, _020B4170 ; =UNK_021CDF08
	ldr r2, [r2, r3]
	ldr ip, _020B4174 ; =UNK_02106578
	ldr r0, [r0, r3]
	str r2, [r12, #0x10]
	str r0, [r12, #0x14]
_020B40E4:
	ldr r2, [r12, #0x0]
	ldr r0, _020B4154 ; =UNK_021CDD70
	str r2, [r1, #0x0]
	ldr r2, [r12, #0x4]
	str r2, [r1, #0x4]
	ldr r2, [r12, #0x8]
	str r2, [r1, #0x8]
	ldr r2, [r12, #0xc]
	str r2, [r1, #0xc]
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x10
	movs lr, r0, lsr #0x10
	addmi sp, sp, #0x4
	ldmmiia sp!, {r4-r5,pc}
	ldr r3, _020B4158 ; =UNK_021CDDF4
	mov r0, #0x3
_020B4124:
	add r2, r3, lr, lsl #0x3
	ldrh r1, [r2, #0x2]
	mov r12, lr, lsl #0x3
	cmp r5, r1
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,pc}
	strh r0, [r2, #0x4]
	strh r4, [r3, r12]
	subs lr, lr, #0x1
	bpl _020B4124
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B4154: .word UNK_021CDD70
_020B4158: .word UNK_021CDDF4
_020B415C: .word UNK_021CDD60
_020B4160: .word UNK_021CE4F4
_020B4164: .word UNK_021CDD68
_020B4168: .word UNK_021CE1F4
_020B416C: .word UNK_021CDF04
_020B4170: .word UNK_021CDF08
_020B4174: .word UNK_02106578
	arm_func_end FUN_020B4010

	; NNSi_G2dIdentity
	arm_func_start FUN_020B4178
FUN_020B4178: ; 0x020B4178
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020B4220 ; =UNK_021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020B41B8
	ldr r1, _020B4224 ; =UNK_021CDD70
	mov r0, #0x18
	ldr r12, [r1, #0x0]
	ldr r1, _020B4228 ; =UNK_021CDF04
	mul r3, r12, r0
	mov r2, #0x0
	ldr r0, _020B422C ; =UNK_021CDF08
	str r2, [r1, r3]
	str r2, [r0, r3]
	b _020B420C
_020B41B8:
	ldr r0, _020B4224 ; =UNK_021CDD70
	mov lr, #0x18
	ldr r1, [r0, #0x0]
	ldr r4, _020B4230 ; =UNK_021CDEF4
	mul r3, r1, lr
	mov r2, #0x1000
	str r2, [r4, r3]
	add r5, r4, r3
	mov r1, #0x0
	str r1, [r5, #0x4]
	str r1, [r5, #0x8]
	str r2, [r5, #0xc]
	str r1, [r5, #0x10]
	str r1, [r5, #0x14]
	ldr r12, [r0, #0x0]
	ldr r4, _020B4234 ; =UNK_021CE1F4
	ldmia r5!, {r0-r3}
	mla lr, r12, lr, r4
	stmia lr!, {r0-r3}
	ldmia r5, {r0-r1}
	stmia lr, {r0-r1}
_020B420C:
	ldr r0, _020B4238 ; =UNK_021CDD74
	mov r1, #0x0
	str r1, [r0, r12, lsl #0x2]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B4220: .word UNK_021CDD68
_020B4224: .word UNK_021CDD70
_020B4228: .word UNK_021CDF04
_020B422C: .word UNK_021CDF08
_020B4230: .word UNK_021CDEF4
_020B4234: .word UNK_021CE1F4
_020B4238: .word UNK_021CDD74
	arm_func_end FUN_020B4178

