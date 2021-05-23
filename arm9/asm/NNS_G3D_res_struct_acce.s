	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNS_G3dGetTex
NNS_G3dGetTex: ; 0x020BC0FC
	ldrh r2, [r0, #0xc]
	ldrh r1, [r0, #0xe]
	add r3, r0, r2
	cmp r1, #0x1
	bne _020BC12C
	ldr r2, [r0, #0x0]
	ldr r1, _020BC138 ; =0x30585442
	cmp r2, r1
	ldreq r1, [r3, #0x0]
	addeq r0, r0, r1
	movne r0, #0x0
	bx lr
_020BC12C:
	ldr r1, [r3, #0x4]
	add r0, r0, r1
	bx lr
	.balign 4
_020BC138: .word 0x30585442
	arm_func_end NNS_G3dGetTex

	arm_func_start NNS_G3dGetMdlSet
NNS_G3dGetMdlSet: ; 0x020BC13C
	ldrh r1, [r0, #0xc]
	ldr r1, [r0, r1]
	add r0, r0, r1
	bx lr
	arm_func_end NNS_G3dGetMdlSet

	arm_func_start NNS_G3dGetResDictIdxByName
NNS_G3dGetResDictIdxByName: ; 0x020BC14C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldrb r2, [r0, #0x1]
	cmp r2, #0x10
	bhs _020BC1E4
	cmp r2, #0x0
	ldr lr, [r1, #0x0]
	ldr r12, [r1, #0x4]
	ldr r3, [r1, #0x8]
	ldr r2, [r1, #0xc]
	mov r4, #0x0
	bls _020BC294
	ldrh r5, [r0, #0x6]
	mov r1, r4
	add r6, r0, r5
	ldrh r5, [r6, #0x2]
	add r6, r6, r5
_020BC190:
	ldr r5, [r6, r1]
	add r7, r6, r1
	cmp r5, lr
	bne _020BC1CC
	ldr r5, [r7, #0x4]
	cmp r5, r12
	bne _020BC1CC
	ldr r5, [r7, #0x8]
	cmp r5, r3
	bne _020BC1CC
	ldr r5, [r7, #0xc]
	cmp r5, r2
	addeq sp, sp, #0x4
	moveq r0, r4
	ldmeqia sp!, {r4-r7,pc}
_020BC1CC:
	ldrb r5, [r0, #0x1]
	add r4, r4, #0x1
	add r1, r1, #0x10
	cmp r4, r5
	blo _020BC190
	b _020BC294
_020BC1E4:
	add r3, r0, #0x8
	ldrb r2, [r3, #0x1]
	cmp r2, #0x0
	beq _020BC294
	ldrb r5, [r3, r2, lsl #0x2]
	ldrb r4, [r3, #0x0]
	add r2, r3, r2, lsl #0x2
	cmp r4, r5
	bls _020BC238
_020BC208:
	mov r4, r5, asr #0x5
	ldr r12, [r1, r4, lsl #0x2]
	and r4, r5, #0x1f
	mov r4, r12, lsr r4
	and r4, r4, #0x1
	add r4, r2, r4
	ldrb r12, [r4, #0x1]
	ldrb r4, [r2, #0x0]
	ldrb r5, [r3, r12, lsl #0x2]
	add r2, r3, r12, lsl #0x2
	cmp r4, r5
	bhi _020BC208
_020BC238:
	ldrh r4, [r0, #0x6]
	ldr r3, [r1, #0x0]
	add r12, r0, r4
	ldrh r4, [r12, #0x2]
	ldrb r0, [r2, #0x3]
	add r4, r12, r4
	ldr r2, [r4, r0, lsl #0x4]
	add r4, r4, r0, lsl #0x4
	cmp r2, r3
	bne _020BC294
	ldr r3, [r4, #0x4]
	ldr r2, [r1, #0x4]
	cmp r3, r2
	bne _020BC294
	ldr r3, [r4, #0x8]
	ldr r2, [r1, #0x8]
	cmp r3, r2
	bne _020BC294
	ldr r2, [r4, #0xc]
	ldr r1, [r1, #0xc]
	cmp r2, r1
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
_020BC294:
	mvn r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	arm_func_end NNS_G3dGetResDictIdxByName

	arm_func_start NNS_G3dGetResDataByName
NNS_G3dGetResDataByName: ; 0x020BC2A0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldrb r2, [r0, #0x1]
	cmp r2, #0x10
	bhs _020BC34C
	cmp r2, #0x0
	ldr lr, [r1, #0x0]
	ldr r12, [r1, #0x4]
	ldr r3, [r1, #0x8]
	ldr r2, [r1, #0xc]
	mov r4, #0x0
	bls _020BC404
	ldrh r5, [r0, #0x6]
	mov r1, r4
	add r6, r0, r5
	ldrh r5, [r6, #0x2]
	add r6, r6, r5
_020BC2E4:
	ldr r5, [r6, r1]
	add r7, r6, r1
	cmp r5, lr
	bne _020BC334
	ldr r5, [r7, #0x4]
	cmp r5, r12
	bne _020BC334
	ldr r5, [r7, #0x8]
	cmp r5, r3
	bne _020BC334
	ldr r5, [r7, #0xc]
	cmp r5, r2
	bne _020BC334
	ldrh r2, [r0, #0x6]
	add sp, sp, #0x4
	ldrh r1, [r0, r2]
	add r0, r0, r2
	add r0, r0, #0x4
	mla r0, r1, r4, r0
	ldmia sp!, {r4-r7,pc}
_020BC334:
	ldrb r5, [r0, #0x1]
	add r4, r4, #0x1
	add r1, r1, #0x10
	cmp r4, r5
	blo _020BC2E4
	b _020BC404
_020BC34C:
	add r3, r0, #0x8
	ldrb r2, [r3, #0x1]
	cmp r2, #0x0
	beq _020BC404
	ldrb r5, [r3, r2, lsl #0x2]
	ldrb r4, [r3, #0x0]
	add r2, r3, r2, lsl #0x2
	cmp r4, r5
	bls _020BC3A0
_020BC370:
	mov r4, r5, asr #0x5
	ldr r12, [r1, r4, lsl #0x2]
	and r4, r5, #0x1f
	mov r4, r12, lsr r4
	and r4, r4, #0x1
	add r4, r2, r4
	ldrb r12, [r4, #0x1]
	ldrb r4, [r2, #0x0]
	ldrb r5, [r3, r12, lsl #0x2]
	add r2, r3, r12, lsl #0x2
	cmp r4, r5
	bhi _020BC370
_020BC3A0:
	ldrh r4, [r0, #0x6]
	ldrb r2, [r2, #0x3]
	ldr r3, [r1, #0x0]
	add r0, r0, r4
	ldrh r4, [r0, #0x2]
	add r12, r0, r4
	ldr r4, [r12, r2, lsl #0x4]
	add r12, r12, r2, lsl #0x4
	cmp r4, r3
	bne _020BC404
	ldr r4, [r12, #0x4]
	ldr r3, [r1, #0x4]
	cmp r4, r3
	bne _020BC404
	ldr r4, [r12, #0x8]
	ldr r3, [r1, #0x8]
	cmp r4, r3
	bne _020BC404
	ldr r3, [r12, #0xc]
	ldr r1, [r1, #0xc]
	cmp r3, r1
	ldreqh r1, [r0], #0x4
	addeq sp, sp, #0x4
	mlaeq r0, r1, r2, r0
	ldmeqia sp!, {r4-r7,pc}
_020BC404:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	arm_func_end NNS_G3dGetResDataByName

	arm_func_start NNSi_G3dGetTexPatAnmDataByIdx
NNSi_G3dGetTexPatAnmDataByIdx: ; 0x020BC410
	ldrh r3, [r0, #0x12]
	add r0, r0, #0xc
	ldrh r2, [r0, r3]
	add r0, r0, r3
	add r0, r0, #0x4
	mla r0, r2, r1, r0
	bx lr
	arm_func_end NNSi_G3dGetTexPatAnmDataByIdx

	arm_func_start NNSi_G3dGetTexPatAnmFV
NNSi_G3dGetTexPatAnmFV: ; 0x020BC42C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r2
	bl NNSi_G3dGetTexPatAnmDataByIdx
	ldrsh r1, [r0, #0x4]
	ldrh r3, [r0, #0x6]
	mul r2, r1, r4
	add r3, r5, r3
	mov r2, r2, lsr #0xc
	b _020BC45C
_020BC458:
	sub r2, r2, #0x1
_020BC45C:
	cmp r2, #0x0
	beq _020BC474
	mov r1, r2, lsl #0x2
	ldrh r1, [r3, r1]
	cmp r1, r4
	bhs _020BC458
_020BC474:
	ldrh r1, [r0, #0x0]
	b _020BC480
_020BC47C:
	add r2, r2, #0x1
_020BC480:
	add r0, r2, #0x1
	cmp r0, r1
	bhs _020BC49C
	add r0, r3, r2, lsl #0x2
	ldrh r0, [r0, #0x4]
	cmp r0, r4
	bls _020BC47C
_020BC49C:
	add r0, r3, r2, lsl #0x2
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	arm_func_end NNSi_G3dGetTexPatAnmFV

	arm_func_start NNSi_G3dGetTexPatAnmPlttNameByIdx
NNSi_G3dGetTexPatAnmPlttNameByIdx: ; 0x020BC4A8
	ldrh r2, [r0, #0xa]
	add r0, r0, r2
	add r0, r0, r1, lsl #0x4
	bx lr
	arm_func_end NNSi_G3dGetTexPatAnmPlttNameByIdx

	arm_func_start NNSi_G3dGetTexPatAnmTexNameByIdx
NNSi_G3dGetTexPatAnmTexNameByIdx: ; 0x020BC4B8
	ldrh r2, [r0, #0x8]
	add r0, r0, r2
	add r0, r0, r1, lsl #0x4
	bx lr
	arm_func_end NNSi_G3dGetTexPatAnmTexNameByIdx

	arm_func_start NNS_G3dGetAnmByIdx
NNS_G3dGetAnmByIdx: ; 0x020BC4C8
	ldrh r2, [r0, #0xc]
	ldr r2, [r0, r2]
	add r12, r0, r2
	ldrh r2, [r12, #0xe]
	add r3, r12, #0x8
	ldrh r0, [r3, r2]
	add r2, r3, r2
	add r2, r2, #0x4
	mul r1, r0, r1
	adds r0, r2, r1
	ldrne r0, [r0, #0x0]
	addne r0, r12, r0
	moveq r0, #0x0
	bx lr
	arm_func_end NNS_G3dGetAnmByIdx
