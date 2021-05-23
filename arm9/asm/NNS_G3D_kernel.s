	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNS_G3dReleaseMdlSet
NNS_G3dReleaseMdlSet: ; 0x020B772C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	ldrb r0, [r6, #0x9]
	mov r5, #0x0
	cmp r0, #0x0
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r7,pc}
	add r4, r6, #0x8
_020B7750:
	ldrh r0, [r6, #0xe]
	ldrh r1, [r4, r0]
	add r0, r4, r0
	mla r0, r1, r5, r0
	ldr r0, [r0, #0x4]
	add r7, r6, r0
	mov r0, r7
	bl NNS_G3dReleaseMdlTex
	mov r0, r7
	bl NNS_G3dReleaseMdlPltt
	ldrb r0, [r6, #0x9]
	add r5, r5, #0x1
	cmp r5, r0
	blo _020B7750
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	arm_func_end NNS_G3dReleaseMdlSet

	arm_func_start NNS_G3dBindMdlSet
NNS_G3dBindMdlSet: ; 0x020B7790
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r8, r0
	ldrb r0, [r8, #0x9]
	mov r7, r1
	mov r5, #0x1
	cmp r0, #0x0
	mov r6, #0x0
	bls _020B7800
	add r4, r8, #0x8
_020B77B8:
	ldrh r0, [r8, #0xe]
	mov r1, r7
	ldrh r2, [r4, r0]
	add r0, r4, r0
	mla r0, r2, r6, r0
	ldr r0, [r0, #0x4]
	add r9, r8, r0
	mov r0, r9
	bl NNS_G3dBindMdlTex
	and r5, r5, r0
	mov r0, r9
	mov r1, r7
	bl NNS_G3dBindMdlPltt
	ldrb r1, [r8, #0x9]
	add r6, r6, #0x1
	and r5, r5, r0
	cmp r6, r1
	blo _020B77B8
_020B7800:
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	arm_func_end NNS_G3dBindMdlSet

	arm_func_start NNS_G3dReleaseMdlPltt
NNS_G3dReleaseMdlPltt: ; 0x020B780C
	ldr r2, [r0, #0x8]
	mov r1, #0x0
	add r2, r0, r2
	ldrh r0, [r2, #0x2]
	add r12, r2, r0
	ldrb r0, [r12, #0x1]
	cmp r0, #0x0
	bxls lr
_020B782C:
	ldrh r2, [r12, #0x6]
	ldrh r0, [r12, r2]
	add r2, r12, r2
	add r2, r2, #0x4
	mla r3, r0, r1, r2
	ldrb r0, [r3, #0x3]
	add r1, r1, #0x1
	ands r2, r0, #0x1
	bicne r0, r0, #0x1
	strneb r0, [r3, #0x3]
	ldrb r0, [r12, #0x1]
	cmp r1, r0
	blo _020B782C
	bx lr
	arm_func_end NNS_G3dReleaseMdlPltt

	arm_func_start NNS_G3dBindMdlPltt
NNS_G3dBindMdlPltt: ; 0x020B7864
	stmdb sp!, {r4-r10,lr}
	ldr r2, [r0, #0x8]
	mov r10, r1
	add r9, r0, r2
	ldrh r0, [r9, #0x2]
	mov r6, #0x1
	mov r7, #0x0
	add r8, r9, r0
	ldrb r0, [r8, #0x1]
	cmp r0, #0x0
	bls _020B7908
	mov r5, r7
	mov r4, r7
_020B7898:
	ldrh r1, [r8, #0x6]
	ldrh r0, [r10, #0x34]
	add r2, r8, r1
	ldrh r1, [r2, #0x2]
	add r0, r10, r0
	add r1, r2, r1
	add r1, r1, r5
	bl NNS_G3dGetResDataByName
	movs r3, r0
	beq _020B78F0
	ldrh r1, [r8, #0x6]
	ldrh r0, [r8, r1]
	add r1, r8, r1
	add r1, r1, #0x4
	mla r1, r0, r7, r1
	ldrb r0, [r1, #0x3]
	ands r0, r0, #0x1
	bne _020B78F4
	mov r0, r9
	mov r2, r10
	bl bindMdlPltt_Internal_
	b _020B78F4
_020B78F0:
	mov r6, r4
_020B78F4:
	ldrb r0, [r8, #0x1]
	add r7, r7, #0x1
	add r5, r5, #0x10
	cmp r7, r0
	blo _020B7898
_020B7908:
	mov r0, r6
	ldmia sp!, {r4-r10,pc}
	arm_func_end NNS_G3dBindMdlPltt

	arm_func_start bindMdlPltt_Internal_
bindMdlPltt_Internal_: ; 0x020B7910
	stmdb sp!, {r4-r6,lr}
	ldrh r5, [r1, #0x0]
	ldr r2, [r2, #0x2c]
	ldrh r4, [r3, #0x2]
	mov r2, r2, lsl #0x10
	add r12, r0, r5
	mov r5, r2, lsr #0x10
	ands r2, r4, #0x1
	ldrh r4, [r3, #0x0]
	moveq r3, r5, lsl #0xf
	moveq r5, r3, lsr #0x10
	moveq r2, r4, lsl #0xf
	moveq r4, r2, lsr #0x10
	ldrb r3, [r1, #0x2]
	mov r2, #0x0
	cmp r3, #0x0
	bls _020B7994
	add r3, r4, r5
	mov r3, r3, lsl #0x10
	add r6, r0, #0x4
	mov r4, r3, lsr #0x10
_020B7964:
	ldrh r5, [r0, #0xa]
	ldrb r3, [r12, r2]
	add r2, r2, #0x1
	ldrh lr, [r6, r5]
	add r5, r6, r5
	mla r3, lr, r3, r5
	ldr r3, [r3, #0x4]
	add r3, r0, r3
	strh r4, [r3, #0x1c]
	ldrb r3, [r1, #0x2]
	cmp r2, r3
	blo _020B7964
_020B7994:
	ldrb r0, [r1, #0x3]
	orr r0, r0, #0x1
	strb r0, [r1, #0x3]
	ldmia sp!, {r4-r6,pc}
	arm_func_end bindMdlPltt_Internal_

	arm_func_start NNS_G3dReleaseMdlTex
NNS_G3dReleaseMdlTex: ; 0x020B79A4
	stmdb sp!, {r4-r6,lr}
	ldr r2, [r0, #0x8]
	mov r4, #0x0
	ldrh r1, [r0, r2]
	add r6, r0, r2
	add r5, r6, r1
	ldrb r0, [r5, #0x1]
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020B79C8:
	ldrh r1, [r5, #0x6]
	ldrh r0, [r5, r1]
	add r1, r5, r1
	add r1, r1, #0x4
	mla r1, r0, r4, r1
	ldrb r0, [r1, #0x3]
	ands r0, r0, #0x1
	beq _020B79F0
	mov r0, r6
	bl releaseMdlTex_Internal_
_020B79F0:
	ldrb r0, [r5, #0x1]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020B79C8
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNS_G3dReleaseMdlTex

	arm_func_start NNS_G3dBindMdlTex
NNS_G3dBindMdlTex: ; 0x020B7A04
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x8]
	mov r10, r1
	ldrh r1, [r0, r2]
	add r9, r0, r2
	mov r11, #0x1
	add r8, r9, r1
	ldrb r0, [r8, #0x1]
	mov r7, #0x0
	cmp r0, #0x0
	bls _020B7AAC
	mov r6, r7
	mov r4, r7
	add r5, r10, #0x3c
_020B7A40:
	ldrh r1, [r8, #0x6]
	mov r0, r5
	add r2, r8, r1
	ldrh r1, [r2, #0x2]
	add r1, r2, r1
	add r1, r1, r6
	bl NNS_G3dGetResDataByName
	movs r3, r0
	beq _020B7A94
	ldrh r1, [r8, #0x6]
	ldrh r0, [r8, r1]
	add r1, r8, r1
	add r1, r1, #0x4
	mla r1, r0, r7, r1
	ldrb r0, [r1, #0x3]
	ands r0, r0, #0x1
	bne _020B7A98
	mov r0, r9
	mov r2, r10
	bl bindMdlTex_Internal_
	b _020B7A98
_020B7A94:
	mov r11, r4
_020B7A98:
	ldrb r0, [r8, #0x1]
	add r7, r7, #0x1
	add r6, r6, #0x10
	cmp r7, r0
	blo _020B7A40
_020B7AAC:
	mov r0, r11
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	arm_func_end NNS_G3dBindMdlTex

	arm_func_start releaseMdlTex_Internal_
releaseMdlTex_Internal_: ; 0x020B7AB8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldrh r4, [r1, #0x0]
	ldrb r2, [r1, #0x2]
	mov r3, #0x0
	add r12, r0, r4
	cmp r2, #0x0
	bls _020B7B28
	add r2, r0, #0x4
	mov r5, #0x1000
	ldr lr, _020B7B3C ; =0xC00F0000
_020B7AE4:
	ldrh r7, [r0, #0xa]
	ldrb r4, [r12, r3]
	add r3, r3, #0x1
	ldrh r6, [r2, r7]
	add r7, r2, r7
	mla r4, r6, r4, r7
	ldr r4, [r4, #0x4]
	add r6, r0, r4
	ldr r4, [r6, #0x14]
	and r4, r4, lr
	str r4, [r6, #0x14]
	str r5, [r6, #0x24]
	ldr r4, [r6, #0x24]
	str r4, [r6, #0x28]
	ldrb r4, [r1, #0x2]
	cmp r3, r4
	blo _020B7AE4
_020B7B28:
	ldrb r0, [r1, #0x3]
	bic r0, r0, #0x1
	strb r0, [r1, #0x3]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B7B3C: .word 0xC00F0000
	arm_func_end releaseMdlTex_Internal_

	arm_func_start bindMdlTex_Internal_
bindMdlTex_Internal_: ; 0x020B7B40
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r11, r1
	mov r9, r3
	ldr r1, [r9, #0x0]
	mov r10, r0
	and r0, r1, #0x1c000000
	cmp r0, #0x14000000
	ldrh r3, [r11, #0x0]
	ldrne r1, [r2, #0x8]
	mov r8, #0x0
	add r0, r10, r3
	str r0, [sp, #0x4]
	ldrne r0, _020B7C50 ; =0x0000FFFF
	andne r0, r1, r0
	strne r0, [sp, #0x0]
	ldreq r1, [r2, #0x18]
	ldreq r0, _020B7C50 ; =0x0000FFFF
	andeq r0, r1, r0
	streq r0, [sp, #0x0]
	ldrb r0, [r11, #0x2]
	cmp r0, #0x0
	bls _020B7C3C
	mov r4, #0x1000
	add r5, r10, #0x4
_020B7BA4:
	ldrh r6, [r10, #0xa]
	ldr r0, [sp, #0x4]
	ldr r1, [r9, #0x0]
	ldrb r2, [r0, r8]
	ldrh r3, [r5, r6]
	ldr r0, [sp, #0x0]
	add r6, r5, r6
	add r0, r1, r0
	mla r1, r3, r2, r6
	ldr r1, [r1, #0x4]
	add r6, r10, r1
	ldr r1, [r6, #0x14]
	orr r0, r1, r0
	str r0, [r6, #0x14]
	ldr r3, [r9, #0x4]
	ldr r0, _020B7C54 ; =0x000007FF
	ldrh r1, [r6, #0x20]
	and r2, r3, r0
	and r7, r0, r3, lsr #0xb
	cmp r2, r1
	moveq r0, r4
	beq _020B7C08
	mov r0, r2, lsl #0xc
	mov r1, r1, lsl #0xc
	bl FX_Div
_020B7C08:
	str r0, [r6, #0x24]
	ldrh r1, [r6, #0x22]
	cmp r7, r1
	moveq r0, r4
	beq _020B7C28
	mov r0, r7, lsl #0xc
	mov r1, r1, lsl #0xc
	bl FX_Div
_020B7C28:
	str r0, [r6, #0x28]
	ldrb r0, [r11, #0x2]
	add r8, r8, #0x1
	cmp r8, r0
	blo _020B7BA4
_020B7C3C:
	ldrb r0, [r11, #0x3]
	orr r0, r0, #0x1
	strb r0, [r11, #0x3]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B7C50: .word 0x0000FFFF
_020B7C54: .word 0x000007FF
	arm_func_end bindMdlTex_Internal_

	arm_func_start NNS_G3dPlttReleasePlttKey
NNS_G3dPlttReleasePlttKey: ; 0x020B7C58
	ldrh r2, [r0, #0x32]
	mov r1, #0x0
	bic r2, r2, #0x1
	strh r2, [r0, #0x32]
	ldr r2, [r0, #0x2c]
	str r1, [r0, #0x2c]
	mov r0, r2
	bx lr
	arm_func_end NNS_G3dPlttReleasePlttKey

	arm_func_start NNS_G3dPlttLoad
NNS_G3dPlttLoad: ; 0x020B7C78
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r4, r1
	mov r5, r0
	beq _020B7C90
	bl GX_BeginLoadTexPltt
_020B7C90:
	ldrh r2, [r5, #0x30]
	ldr r0, [r5, #0x38]
	ldr r3, [r5, #0x2c]
	ldr r1, _020B7CD8 ; =0x0000FFFF
	add r0, r5, r0
	and r1, r3, r1
	mov r1, r1, lsl #0x3
	mov r2, r2, lsl #0x3
	bl GX_LoadTexPltt
	ldrh r0, [r5, #0x32]
	cmp r4, #0x0
	addeq sp, sp, #0x4
	orr r0, r0, #0x1
	strh r0, [r5, #0x32]
	ldmeqia sp!, {r4-r5,pc}
	bl GX_EndLoadTexPltt
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B7CD8: .word 0x0000FFFF
	arm_func_end NNS_G3dPlttLoad

	arm_func_start NNS_G3dPlttSetPlttKey
NNS_G3dPlttSetPlttKey: ; 0x020B7CDC
	str r1, [r0, #0x2c]
	bx lr
	arm_func_end NNS_G3dPlttSetPlttKey

	arm_func_start NNS_G3dPlttGetRequiredSize
NNS_G3dPlttGetRequiredSize: ; 0x020B7CE4
	ldrh r0, [r0, #0x30]
	mov r0, r0, lsl #0x3
	bx lr
	arm_func_end NNS_G3dPlttGetRequiredSize

	arm_func_start NNS_G3dTexReleaseTexKey
NNS_G3dTexReleaseTexKey: ; 0x020B7CF0
	ldrh r12, [r0, #0x10]
	mov r3, #0x0
	bic r12, r12, #0x1
	strh r12, [r0, #0x10]
	ldrh r12, [r0, #0x20]
	bic r12, r12, #0x1
	strh r12, [r0, #0x20]
	ldr r12, [r0, #0x8]
	str r12, [r1, #0x0]
	str r3, [r0, #0x8]
	ldr r1, [r0, #0x18]
	str r1, [r2, #0x0]
	str r3, [r0, #0x18]
	bx lr
	arm_func_end NNS_G3dTexReleaseTexKey

	arm_func_start NNS_G3dTexLoad
NNS_G3dTexLoad: ; 0x020B7D28
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	movs r8, r1
	mov r9, r0
	beq _020B7D40
	bl GX_BeginLoadTex
_020B7D40:
	ldrh r0, [r9, #0xc]
	movs r2, r0, lsl #0x3
	beq _020B7D74
	ldr r1, [r9, #0x8]
	ldr r0, _020B7DF4 ; =0x0000FFFF
	ldr r3, [r9, #0x14]
	and r1, r1, r0
	add r0, r9, r3
	mov r1, r1, lsl #0x3
	bl GX_LoadTex
	ldrh r0, [r9, #0x10]
	orr r0, r0, #0x1
	strh r0, [r9, #0x10]
_020B7D74:
	ldrh r0, [r9, #0x1c]
	movs r7, r0, lsl #0x3
	beq _020B7DDC
	ldr r1, [r9, #0x18]
	ldr r0, _020B7DF4 ; =0x0000FFFF
	ldr r3, [r9, #0x24]
	and r4, r1, r0
	mov r5, r4, lsl #0x3
	ldr r6, [r9, #0x28]
	mov r1, r5
	mov r2, r7
	add r0, r9, r3
	add r6, r9, r6
	bl GX_LoadTex
	ldr r0, _020B7DF8 ; =0x0001FFFF
	and r1, r5, #0x40000
	and r0, r0, r4, lsl #0x3
	mov r0, r0, lsr #0x1
	add r2, r0, #0x20000
	mov r0, r6
	add r1, r2, r1, lsr #0x2
	mov r2, r7, lsr #0x1
	bl GX_LoadTex
	ldrh r0, [r9, #0x20]
	orr r0, r0, #0x1
	strh r0, [r9, #0x20]
_020B7DDC:
	cmp r8, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r9,pc}
	bl GX_EndLoadTex
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020B7DF4: .word 0x0000FFFF
_020B7DF8: .word 0x0001FFFF
	arm_func_end NNS_G3dTexLoad

	arm_func_start NNS_G3dTexSetTexKey
NNS_G3dTexSetTexKey: ; 0x020B7DFC
	cmp r1, #0x0
	strne r1, [r0, #0x8]
	cmp r2, #0x0
	strne r2, [r0, #0x18]
	bx lr
	arm_func_end NNS_G3dTexSetTexKey

	arm_func_start NNS_G3dTex4x4GetRequiredSize
NNS_G3dTex4x4GetRequiredSize: ; 0x020B7E10
	ldrh r0, [r0, #0x1c]
	mov r0, r0, lsl #0x3
	bx lr
	arm_func_end NNS_G3dTex4x4GetRequiredSize

	arm_func_start NNS_G3dTexGetRequiredSize
NNS_G3dTexGetRequiredSize: ; 0x020B7E1C
	ldrh r0, [r0, #0xc]
	mov r0, r0, lsl #0x3
	bx lr
	arm_func_end NNS_G3dTexGetRequiredSize

	arm_func_start NNS_G3dRenderObjRemoveAnmObj
NNS_G3dRenderObjRemoveAnmObj: ; 0x020B7E28
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	add r0, r5, #0x8
	mov r4, r1
	bl removeLink_
	cmp r0, #0x0
	bne _020B7E74
	mov r1, r4
	add r0, r5, #0x10
	bl removeLink_
	cmp r0, #0x0
	bne _020B7E74
	mov r1, r4
	add r0, r5, #0x18
	bl removeLink_
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
_020B7E74:
	ldr r0, [r5, #0x0]
	orr r0, r0, #0x10
	str r0, [r5, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	arm_func_end NNS_G3dRenderObjRemoveAnmObj

	arm_func_start removeLink_
removeLink_: ; 0x020B7E88
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r2, r1
	bne _020B7EB8
	ldr r3, [r2, #0x10]
	mov r2, #0x0
	str r3, [r0, #0x0]
	str r2, [r1, #0x10]
	mov r0, #0x1
	bx lr
_020B7EB8:
	ldr r3, [r2, #0x10]
	cmp r3, #0x0
	beq _020B7EF4
_020B7EC4:
	cmp r3, r1
	bne _020B7EE4
	ldr r1, [r3, #0x10]
	mov r0, #0x0
	str r1, [r2, #0x10]
	str r0, [r3, #0x10]
	mov r0, #0x1
	bx lr
_020B7EE4:
	mov r2, r3
	ldr r3, [r3, #0x10]
	cmp r3, #0x0
	bne _020B7EC4
_020B7EF4:
	mov r0, #0x0
	bx lr
	arm_func_end removeLink_

	arm_func_start NNS_G3dRenderObjAddAnmObj
NNS_G3dRenderObjAddAnmObj: ; 0x020B7EFC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	ldr r2, [r4, #0x8]
	mov r5, r0
	ldrb r0, [r2, #0x0]
	cmp r0, #0x4a
	beq _020B7F50
	cmp r0, #0x4d
	beq _020B7F34
	cmp r0, #0x56
	beq _020B7F6C
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
_020B7F34:
	add r0, r5, #0x3c
	bl updateHintVec_
	mov r1, r4
	add r0, r5, #0x8
	bl addLink_
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
_020B7F50:
	add r0, r5, #0x44
	bl updateHintVec_
	mov r1, r4
	add r0, r5, #0x10
	bl addLink_
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
_020B7F6C:
	add r0, r5, #0x4c
	bl updateHintVec_
	mov r1, r4
	add r0, r5, #0x18
	bl addLink_
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	arm_func_end NNS_G3dRenderObjAddAnmObj

	local_arm_func_start updateHintVec_
updateHintVec_: ; 0x020B7F88
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
	mov r3, #0x1
	mov r4, #0x0
_020B7FA4:
	ldrb r2, [r1, #0x19]
	mov r5, r4
	cmp r2, #0x0
	ble _020B7FE4
_020B7FB4:
	add r2, r1, r5, lsl #0x1
	ldrh r2, [r2, #0x1a]
	ands r2, r2, #0x100
	movne lr, r5, asr #0x5
	andne r2, r5, #0x1f
	ldrne r12, [r0, lr, lsl #0x2]
	add r5, r5, #0x1
	orrne r2, r12, r3, lsl r2
	strne r2, [r0, lr, lsl #0x2]
	ldrb r2, [r1, #0x19]
	cmp r5, r2
	blt _020B7FB4
_020B7FE4:
	ldr r1, [r1, #0x10]
	cmp r1, #0x0
	bne _020B7FA4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	arm_func_end updateHintVec_

	arm_func_start addLink_
addLink_: ; 0x020B7FF8
	ldr r12, [r0, #0x0]
	cmp r12, #0x0
	streq r1, [r0, #0x0]
	bxeq lr
	ldr r3, [r12, #0x10]
	cmp r3, #0x0
	bne _020B8058
	ldrb r3, [r12, #0x18]
	ldrb r2, [r1, #0x18]
	cmp r3, r2
	bls _020B8050
	ldr r2, [r1, #0x10]
	mov r3, r1
	cmp r2, #0x0
	beq _020B8044
_020B8034:
	ldr r3, [r3, #0x10]
	ldr r2, [r3, #0x10]
	cmp r2, #0x0
	bne _020B8034
_020B8044:
	str r12, [r3, #0x10]
	str r1, [r0, #0x0]
	bx lr
_020B8050:
	str r1, [r12, #0x10]
	bx lr
_020B8058:
	cmp r3, #0x0
	beq _020B80AC
	ldrb r2, [r1, #0x18]
_020B8064:
	ldrb r0, [r3, #0x18]
	cmp r0, r2
	blo _020B809C
	ldr r0, [r1, #0x10]
	mov r2, r1
	cmp r0, #0x0
	beq _020B8090
_020B8080:
	ldr r2, [r2, #0x10]
	ldr r0, [r2, #0x10]
	cmp r0, #0x0
	bne _020B8080
_020B8090:
	str r1, [r12, #0x10]
	str r3, [r2, #0x10]
	bx lr
_020B809C:
	mov r12, r3
	ldr r3, [r3, #0x10]
	cmp r3, #0x0
	bne _020B8064
_020B80AC:
	str r1, [r12, #0x10]
	bx lr
	arm_func_end addLink_

	arm_func_start NNS_G3dRenderObjInit
NNS_G3dRenderObjInit: ; 0x020B80B4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	mov r1, r5
	mov r0, #0x0
	mov r2, #0x54
	bl MIi_CpuClear32
	ldr r0, _020B8104 ; =NNS_G3dFuncBlendMatDefault
	ldr r1, _020B8108 ; =NNS_G3dFuncBlendJntDefault
	ldr r2, [r0, #0x0]
	ldr r0, _020B810C ; =NNS_G3dFuncBlendVisDefault
	str r2, [r5, #0xc]
	ldr r1, [r1, #0x0]
	str r1, [r5, #0x14]
	ldr r0, [r0, #0x0]
	str r0, [r5, #0x1c]
	str r4, [r5, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B8104: .word NNS_G3dFuncBlendMatDefault
_020B8108: .word NNS_G3dFuncBlendJntDefault
_020B810C: .word NNS_G3dFuncBlendVisDefault
	arm_func_end NNS_G3dRenderObjInit

	arm_func_start NNS_G3dAnmObjInit
NNS_G3dAnmObjInit: ; 0x020B8110
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r12, #0x0
	str r12, [r0, #0x0]
	str r1, [r0, #0x8]
	str r12, [r0, #0x10]
	mov r4, #0x7f
	strb r4, [r0, #0x18]
	mov r4, #0x1000
	str r4, [r0, #0x4]
	ldr lr, _020B81A4 ; =NNS_G3dAnmFmtNum
	str r3, [r0, #0x14]
	ldr r6, [lr, #0x0]
	cmp r6, #0x0
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r7,pc}
	ldrb r7, [r1, #0x0]
	ldr r4, _020B81A8 ; =NNS_G3dAnmObjInitFuncArray
_020B8158:
	ldrb r3, [r4, r12, lsl #0x3]
	mov r5, r12, lsl #0x3
	cmp r7, r3
	bne _020B8190
	add r3, r4, r5
	ldrh lr, [r1, #0x2]
	ldrh r3, [r3, #0x2]
	cmp lr, r3
	bne _020B8190
	ldr r3, _020B81AC ; =NNS_G3dAnmObjInitFuncArray + 0x4
	ldr r3, [r3, r5]
	blx r3
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
_020B8190:
	add r12, r12, #0x1
	cmp r12, r6
	blo _020B8158
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B81A4: .word NNS_G3dAnmFmtNum
_020B81A8: .word NNS_G3dAnmObjInitFuncArray
_020B81AC: .word NNS_G3dAnmObjInitFuncArray + 0x4
	arm_func_end NNS_G3dAnmObjInit

	arm_func_start NNS_G3dAnmObjCalcSizeRequired
NNS_G3dAnmObjCalcSizeRequired: ; 0x020B81B0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x4a
	beq _020B81E4
	cmp r0, #0x4d
	beq _020B81D0
	cmp r0, #0x56
	beq _020B81E4
	b _020B81F8
_020B81D0:
	ldrb r0, [r1, #0x18]
	mov r0, r0, lsl #0x1
	add r0, r0, #0x1c
	bic r0, r0, #0x3
	bx lr
_020B81E4:
	ldrb r0, [r1, #0x17]
	mov r0, r0, lsl #0x1
	add r0, r0, #0x1c
	bic r0, r0, #0x3
	bx lr
_020B81F8:
	mov r0, #0x0
	bx lr
	arm_func_end NNS_G3dAnmObjCalcSizeRequired
