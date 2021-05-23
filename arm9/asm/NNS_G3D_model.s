	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNS_G3dMdlSetMdlXLDepthUpdateAll
NNS_G3dMdlSetMdlXLDepthUpdateAll: ; 0x020BB8F4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BB910:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl NNS_G3dMdlSetMdlXLDepthUpdate
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BB910
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNS_G3dMdlSetMdlXLDepthUpdateAll

	arm_func_start NNS_G3dMdlSetMdlFarClipAll
NNS_G3dMdlSetMdlFarClipAll: ; 0x020BB934
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BB950:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl NNS_G3dMdlSetMdlFarClip
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BB950
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNS_G3dMdlSetMdlFarClipAll

	arm_func_start NNS_G3dMdlSetMdl1DotAll
NNS_G3dMdlSetMdl1DotAll: ; 0x020BB974
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BB990:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl NNS_G3dMdlSetMdl1Dot
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BB990
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNS_G3dMdlSetMdl1DotAll

	arm_func_start NNS_G3dMdlSetMdlDepthTestCondAll
NNS_G3dMdlSetMdlDepthTestCondAll: ; 0x020BB9B4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BB9D0:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl NNS_G3dMdlSetMdlDepthTestCond
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BB9D0
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNS_G3dMdlSetMdlDepthTestCondAll

	arm_func_start NNS_G3dMdlSetMdlFogEnableFlagAll
NNS_G3dMdlSetMdlFogEnableFlagAll: ; 0x020BB9F4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBA10:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl NNS_G3dMdlSetMdlFogEnableFlag
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBA10
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNS_G3dMdlSetMdlFogEnableFlagAll

	arm_func_start NNS_G3dMdlSetMdlAlphaAll
NNS_G3dMdlSetMdlAlphaAll: ; 0x020BBA34
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBA50:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl NNS_G3dMdlSetMdlAlpha
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBA50
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNS_G3dMdlSetMdlAlphaAll

	arm_func_start NNS_G3dMdlSetMdlPolygonIDAll
NNS_G3dMdlSetMdlPolygonIDAll: ; 0x020BBA74
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBA90:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl NNS_G3dMdlSetMdlPolygonID
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBA90
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNS_G3dMdlSetMdlPolygonIDAll

	arm_func_start NNS_G3dMdlSetMdlCullModeAll
NNS_G3dMdlSetMdlCullModeAll: ; 0x020BBAB4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBAD0:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl NNS_G3dMdlSetMdlCullMode
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBAD0
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNS_G3dMdlSetMdlCullModeAll

	arm_func_start NNS_G3dMdlSetMdlPolygonModeAll
NNS_G3dMdlSetMdlPolygonModeAll: ; 0x020BBAF4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBB10:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl NNS_G3dMdlSetMdlPolygonMode
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBB10
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNS_G3dMdlSetMdlPolygonModeAll

	arm_func_start NNS_G3dMdlSetMdlLightEnableFlagAll
NNS_G3dMdlSetMdlLightEnableFlagAll: ; 0x020BBB34
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBB50:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl NNS_G3dMdlSetMdlLightEnableFlag
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBB50
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNS_G3dMdlSetMdlLightEnableFlagAll

	arm_func_start NNS_G3dMdlSetMdlEmiAll
NNS_G3dMdlSetMdlEmiAll: ; 0x020BBB74
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBB90:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl NNS_G3dMdlSetMdlEmi
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBB90
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNS_G3dMdlSetMdlEmiAll

	arm_func_start NNS_G3dMdlSetMdlSpecAll
NNS_G3dMdlSetMdlSpecAll: ; 0x020BBBB4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBBD0:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl NNS_G3dMdlSetMdlSpec
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBBD0
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNS_G3dMdlSetMdlSpecAll

	arm_func_start NNS_G3dMdlSetMdlAmbAll
NNS_G3dMdlSetMdlAmbAll: ; 0x020BBBF4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBC10:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl NNS_G3dMdlSetMdlAmb
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBC10
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNS_G3dMdlSetMdlAmbAll

	arm_func_start NNS_G3dMdlSetMdlDiffAll
NNS_G3dMdlSetMdlDiffAll: ; 0x020BBC34
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBC50:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl NNS_G3dMdlSetMdlDiff
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBC50
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNS_G3dMdlSetMdlDiffAll

	arm_func_start NNS_G3dMdlSetMdlXLDepthUpdate
NNS_G3dMdlSetMdlXLDepthUpdate: ; 0x020BBC74
	ldr r3, [r0, #0x8]
	cmp r2, #0x0
	add r12, r0, r3
	ldrh r0, [r12, #0xa]
	add r3, r12, #0x4
	ldrh r2, [r3, r0]
	add r0, r3, r0
	mla r0, r2, r1, r0
	ldr r0, [r0, #0x4]
	add r1, r12, r0
	ldrne r0, [r1, #0xc]
	orrne r0, r0, #0x800
	strne r0, [r1, #0xc]
	ldreq r0, [r1, #0xc]
	biceq r0, r0, #0x800
	streq r0, [r1, #0xc]
	bx lr
	arm_func_end NNS_G3dMdlSetMdlXLDepthUpdate

	arm_func_start NNS_G3dMdlSetMdlFarClip
NNS_G3dMdlSetMdlFarClip: ; 0x020BBCB8
	ldr r3, [r0, #0x8]
	cmp r2, #0x0
	add r12, r0, r3
	ldrh r0, [r12, #0xa]
	add r3, r12, #0x4
	ldrh r2, [r3, r0]
	add r0, r3, r0
	mla r0, r2, r1, r0
	ldr r0, [r0, #0x4]
	add r1, r12, r0
	ldrne r0, [r1, #0xc]
	orrne r0, r0, #0x1000
	strne r0, [r1, #0xc]
	ldreq r0, [r1, #0xc]
	biceq r0, r0, #0x1000
	streq r0, [r1, #0xc]
	bx lr
	arm_func_end NNS_G3dMdlSetMdlFarClip

	arm_func_start NNS_G3dMdlSetMdl1Dot
NNS_G3dMdlSetMdl1Dot: ; 0x020BBCFC
	ldr r3, [r0, #0x8]
	cmp r2, #0x0
	add r12, r0, r3
	ldrh r0, [r12, #0xa]
	add r3, r12, #0x4
	ldrh r2, [r3, r0]
	add r0, r3, r0
	mla r0, r2, r1, r0
	ldr r0, [r0, #0x4]
	add r1, r12, r0
	ldrne r0, [r1, #0xc]
	orrne r0, r0, #0x2000
	strne r0, [r1, #0xc]
	ldreq r0, [r1, #0xc]
	biceq r0, r0, #0x2000
	streq r0, [r1, #0xc]
	bx lr
	arm_func_end NNS_G3dMdlSetMdl1Dot

	arm_func_start NNS_G3dMdlSetMdlDepthTestCond
NNS_G3dMdlSetMdlDepthTestCond: ; 0x020BBD40
	ldr r3, [r0, #0x8]
	cmp r2, #0x0
	add r12, r0, r3
	ldrh r0, [r12, #0xa]
	add r3, r12, #0x4
	ldrh r2, [r3, r0]
	add r0, r3, r0
	mla r0, r2, r1, r0
	ldr r0, [r0, #0x4]
	add r1, r12, r0
	ldrne r0, [r1, #0xc]
	orrne r0, r0, #0x4000
	strne r0, [r1, #0xc]
	ldreq r0, [r1, #0xc]
	biceq r0, r0, #0x4000
	streq r0, [r1, #0xc]
	bx lr
	arm_func_end NNS_G3dMdlSetMdlDepthTestCond

	arm_func_start NNS_G3dMdlSetMdlFogEnableFlag
NNS_G3dMdlSetMdlFogEnableFlag: ; 0x020BBD84
	ldr r3, [r0, #0x8]
	cmp r2, #0x0
	add r12, r0, r3
	ldrh r0, [r12, #0xa]
	add r3, r12, #0x4
	ldrh r2, [r3, r0]
	add r0, r3, r0
	mla r0, r2, r1, r0
	ldr r0, [r0, #0x4]
	add r1, r12, r0
	ldrne r0, [r1, #0xc]
	orrne r0, r0, #0x8000
	strne r0, [r1, #0xc]
	ldreq r0, [r1, #0xc]
	biceq r0, r0, #0x8000
	streq r0, [r1, #0xc]
	bx lr
	arm_func_end NNS_G3dMdlSetMdlFogEnableFlag

	arm_func_start NNS_G3dMdlSetMdlAlpha
NNS_G3dMdlSetMdlAlpha: ; 0x020BBDC8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [r0, #0x8]
	add lr, r0, r3
	ldrh r0, [lr, #0xa]
	add r12, lr, #0x4
	ldrh r3, [r12, r0]
	add r0, r12, r0
	mla r0, r3, r1, r0
	ldr r0, [r0, #0x4]
	add r1, lr, r0
	ldr r0, [r1, #0xc]
	bic r0, r0, #0x1f0000
	orr r0, r0, r2, lsl #0x10
	str r0, [r1, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNS_G3dMdlSetMdlAlpha

	arm_func_start NNS_G3dMdlSetMdlPolygonID
NNS_G3dMdlSetMdlPolygonID: ; 0x020BBE0C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [r0, #0x8]
	add lr, r0, r3
	ldrh r0, [lr, #0xa]
	add r12, lr, #0x4
	ldrh r3, [r12, r0]
	add r0, r12, r0
	mla r0, r3, r1, r0
	ldr r0, [r0, #0x4]
	add r1, lr, r0
	ldr r0, [r1, #0xc]
	bic r0, r0, #0x3f000000
	orr r0, r0, r2, lsl #0x18
	str r0, [r1, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNS_G3dMdlSetMdlPolygonID

	arm_func_start NNS_G3dMdlSetMdlCullMode
NNS_G3dMdlSetMdlCullMode: ; 0x020BBE50
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [r0, #0x8]
	add lr, r0, r3
	ldrh r0, [lr, #0xa]
	add r12, lr, #0x4
	ldrh r3, [r12, r0]
	add r0, r12, r0
	mla r0, r3, r1, r0
	ldr r0, [r0, #0x4]
	add r1, lr, r0
	ldr r0, [r1, #0xc]
	bic r0, r0, #0xc0
	orr r0, r0, r2, lsl #0x6
	str r0, [r1, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNS_G3dMdlSetMdlCullMode

	arm_func_start NNS_G3dMdlSetMdlPolygonMode
NNS_G3dMdlSetMdlPolygonMode: ; 0x020BBE94
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [r0, #0x8]
	add lr, r0, r3
	ldrh r0, [lr, #0xa]
	add r12, lr, #0x4
	ldrh r3, [r12, r0]
	add r0, r12, r0
	mla r0, r3, r1, r0
	ldr r0, [r0, #0x4]
	add r1, lr, r0
	ldr r0, [r1, #0xc]
	bic r0, r0, #0x30
	orr r0, r0, r2, lsl #0x4
	str r0, [r1, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNS_G3dMdlSetMdlPolygonMode

	arm_func_start NNS_G3dMdlSetMdlLightEnableFlag
NNS_G3dMdlSetMdlLightEnableFlag: ; 0x020BBED8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [r0, #0x8]
	add lr, r0, r3
	ldrh r0, [lr, #0xa]
	add r12, lr, #0x4
	ldrh r3, [r12, r0]
	add r0, r12, r0
	mla r0, r3, r1, r0
	ldr r0, [r0, #0x4]
	add r1, lr, r0
	ldr r0, [r1, #0xc]
	bic r0, r0, #0xf
	orr r0, r0, r2
	str r0, [r1, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNS_G3dMdlSetMdlLightEnableFlag

	arm_func_start NNS_G3dMdlSetMdlEmi
NNS_G3dMdlSetMdlEmi: ; 0x020BBF1C
	stmdb sp!, {r4,lr}
	ldr r12, [r0, #0x8]
	ldr r3, _020BBF5C ; =0x8000FFFF
	add r4, r0, r12
	ldrh r0, [r4, #0xa]
	add lr, r4, #0x4
	ldrh r12, [lr, r0]
	add r0, lr, r0
	mla r0, r12, r1, r0
	ldr r0, [r0, #0x4]
	add r1, r4, r0
	ldr r0, [r1, #0x8]
	and r0, r0, r3
	orr r0, r0, r2, lsl #0x10
	str r0, [r1, #0x8]
	ldmia sp!, {r4,pc}
	.balign 4
_020BBF5C: .word 0x8000FFFF
	arm_func_end NNS_G3dMdlSetMdlEmi

	arm_func_start NNS_G3dMdlSetMdlSpec
NNS_G3dMdlSetMdlSpec: ; 0x020BBF60
	stmdb sp!, {r4,lr}
	ldr r12, [r0, #0x8]
	mov r3, #0x8000
	add r4, r0, r12
	ldrh r12, [r4, #0xa]
	add lr, r4, #0x4
	rsb r0, r3, #0x0
	ldrh r3, [lr, r12]
	add r12, lr, r12
	mla r1, r3, r1, r12
	ldr r1, [r1, #0x4]
	add r3, r4, r1
	ldr r1, [r3, #0x8]
	and r0, r1, r0
	orr r0, r0, r2
	str r0, [r3, #0x8]
	ldmia sp!, {r4,pc}
	arm_func_end NNS_G3dMdlSetMdlSpec

	arm_func_start NNS_G3dMdlSetMdlAmb
NNS_G3dMdlSetMdlAmb: ; 0x020BBFA4
	stmdb sp!, {r4,lr}
	ldr r12, [r0, #0x8]
	ldr r3, _020BBFE4 ; =0x8000FFFF
	add r4, r0, r12
	ldrh r0, [r4, #0xa]
	add lr, r4, #0x4
	ldrh r12, [lr, r0]
	add r0, lr, r0
	mla r0, r12, r1, r0
	ldr r0, [r0, #0x4]
	add r1, r4, r0
	ldr r0, [r1, #0x4]
	and r0, r0, r3
	orr r0, r0, r2, lsl #0x10
	str r0, [r1, #0x4]
	ldmia sp!, {r4,pc}
	.balign 4
_020BBFE4: .word 0x8000FFFF
	arm_func_end NNS_G3dMdlSetMdlAmb

	arm_func_start NNS_G3dMdlSetMdlDiff
NNS_G3dMdlSetMdlDiff: ; 0x020BBFE8
	stmdb sp!, {r4,lr}
	ldr r12, [r0, #0x8]
	mov r3, #0x8000
	add r4, r0, r12
	ldrh r12, [r4, #0xa]
	add lr, r4, #0x4
	rsb r0, r3, #0x0
	ldrh r3, [lr, r12]
	add r12, lr, r12
	mla r1, r3, r1, r12
	ldr r1, [r1, #0x4]
	add r3, r4, r1
	ldr r1, [r3, #0x4]
	and r0, r1, r0
	orr r0, r0, r2
	str r0, [r3, #0x4]
	ldmia sp!, {r4,pc}
	arm_func_end NNS_G3dMdlSetMdlDiff

	arm_func_start NNSi_G3dModifyPolygonAttrMask
NNSi_G3dModifyPolygonAttrMask: ; 0x020BC02C
	stmdb sp!, {r4-r6,lr}
	ldrb r4, [r0, #0x18]
	ldr r3, [r0, #0x8]
	mov lr, #0x0
	cmp r4, #0x0
	add r12, r0, r3
	ldmlsia sp!, {r4-r6,pc}
	mvn r3, r2
	add r0, r12, #0x4
_020BC050:
	ldrh r5, [r12, #0xa]
	cmp r1, #0x0
	ldrh r6, [r0, r5]
	add r5, r0, r5
	mla r5, r6, lr, r5
	ldr r5, [r5, #0x4]
	add lr, lr, #0x1
	add r6, r12, r5
	ldrne r5, [r6, #0x10]
	orrne r5, r5, r2
	strne r5, [r6, #0x10]
	ldreq r5, [r6, #0x10]
	andeq r5, r5, r3
	streq r5, [r6, #0x10]
	cmp lr, r4
	blo _020BC050
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNSi_G3dModifyPolygonAttrMask

	arm_func_start NNSi_G3dModifyMatFlag
NNSi_G3dModifyMatFlag: ; 0x020BC094
	stmdb sp!, {r4-r6,lr}
	ldrb r4, [r0, #0x18]
	ldr r3, [r0, #0x8]
	mov lr, #0x0
	cmp r4, #0x0
	add r12, r0, r3
	ldmlsia sp!, {r4-r6,pc}
	mvn r3, r2
	add r0, r12, #0x4
_020BC0B8:
	ldrh r5, [r12, #0xa]
	cmp r1, #0x0
	ldrh r6, [r0, r5]
	add r5, r0, r5
	mla r5, r6, lr, r5
	ldr r5, [r5, #0x4]
	add lr, lr, #0x1
	add r6, r12, r5
	ldrneh r5, [r6, #0x1e]
	orrne r5, r5, r2
	strneh r5, [r6, #0x1e]
	ldreqh r5, [r6, #0x1e]
	andeq r5, r5, r3
	streqh r5, [r6, #0x1e]
	cmp lr, r4
	blo _020BC0B8
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNSi_G3dModifyMatFlag
