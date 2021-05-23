	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNSi_G3dSendTexSRTSi3d
NNSi_G3dSendTexSRTSi3d: ; 0x020BEF10
	stmdb sp!, {lr}
	sub sp, sp, #0x3c
	ldr r1, [r0, #0x0]
	mov r3, #0x0
	ands r1, r1, #0x8
	ldrne r1, _020BF0CC ; =0x00101710
	mov r2, #0x3
	strne r1, [sp, #0x0]
	ldreq r1, _020BF0D0 ; =0x00101910
	str r3, [sp, #0x34]
	streq r1, [sp, #0x0]
	mov r1, #0x2
	str r1, [sp, #0x38]
	str r3, [sp, #0x28]
	str r3, [sp, #0x24]
	str r3, [sp, #0x20]
	str r3, [sp, #0x1c]
	str r3, [sp, #0x14]
	str r3, [sp, #0x10]
	str r3, [sp, #0xc]
	str r2, [sp, #0x4]
	ldr r2, [r0, #0x0]
	ands r1, r2, #0x4
	beq _020BEFA0
	str r3, [sp, #0x2c]
	str r3, [sp, #0x30]
	ldr r1, [r0, #0x0]
	ands r1, r1, #0x1
	movne r1, #0x1000
	strne r1, [sp, #0x8]
	strne r1, [sp, #0x18]
	ldreq r1, [r0, #0x18]
	streq r1, [sp, #0x8]
	ldreq r1, [r0, #0x1c]
	streq r1, [sp, #0x18]
	b _020BF040
_020BEFA0:
	ands r1, r2, #0x1
	beq _020BEFE8
	ldr r2, [r0, #0x24]
	ldrh r1, [r0, #0x2c]
	mov r2, r2, lsl #0x4
	rsb r2, r2, #0x0
	mul r1, r2, r1
	str r1, [sp, #0x2c]
	ldr r2, [r0, #0x28]
	ldrh r1, [r0, #0x2e]
	mov r2, r2, lsl #0x4
	rsb r2, r2, #0x0
	mul r3, r2, r1
	mov r1, #0x1000
	str r3, [sp, #0x30]
	str r1, [sp, #0x8]
	str r1, [sp, #0x18]
	b _020BF040
_020BEFE8:
	ldr r2, [r0, #0x18]
	ldr r1, [r0, #0x24]
	ldrh r12, [r0, #0x2c]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0x8
	orr r2, r2, r1, lsl #0x18
	rsb r1, r2, #0x0
	mul r1, r12, r1
	str r1, [sp, #0x2c]
	ldr r2, [r0, #0x1c]
	ldr r1, [r0, #0x28]
	ldrh r12, [r0, #0x2e]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0x8
	orr r2, r2, r1, lsl #0x18
	rsb r1, r2, #0x0
	mul r1, r12, r1
	str r1, [sp, #0x30]
	ldr r1, [r0, #0x18]
	str r1, [sp, #0x8]
	ldr r1, [r0, #0x1c]
	str r1, [sp, #0x18]
_020BF040:
	ldr r12, [r0, #0x30]
	cmp r12, #0x1000
	beq _020BF078
	ldr r2, [sp, #0x8]
	ldr r1, [sp, #0x2c]
	smull r3, r2, r12, r2
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	str r3, [sp, #0x8]
	ldr r2, [r0, #0x30]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [sp, #0x2c]
_020BF078:
	ldr r12, [r0, #0x34]
	cmp r12, #0x1000
	beq _020BF0B0
	ldr r2, [sp, #0x18]
	ldr r1, [sp, #0x30]
	smull r3, r2, r12, r2
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	str r3, [sp, #0x18]
	ldr r0, [r0, #0x34]
	smull r2, r1, r0, r1
	mov r0, r2, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	str r0, [sp, #0x30]
_020BF0B0:
	add r1, sp, #0x0
	ldr r0, [sp, #0x0]
	add r1, r1, #0x4
	mov r2, #0xe
	bl NNS_G3dGeBufferOP_N
	add sp, sp, #0x3c
	ldmia sp!, {pc}
	.balign 4
_020BF0CC: .word 0x00101710
_020BF0D0: .word 0x00101910
	arm_func_end NNSi_G3dSendTexSRTSi3d

	arm_func_start NNSi_G3dGetJointScaleSi3d
NNSi_G3dGetJointScaleSi3d: ; 0x020BF0D4
	stmdb sp!, {r4-r8,lr}
	mov r5, r0
	ands r0, r3, #0x4
	ldrb r4, [r2, #0x1]
	ldrb r0, [r2, #0x2]
	beq _020BF174
	ldr r2, [r5, #0x0]
	ldr r1, _020BF2E0 ; =NNS_G3dRS
	orr r2, r2, #0x1
	str r2, [r5, #0x0]
	ldr r3, [r1, #0x0]
	mov r1, r0, lsr #0x5
	add r1, r3, r1, lsl #0x2
	and r2, r0, #0x1f
	mov r6, #0x1
	mov r2, r6, lsl r2
	ldr r1, [r1, #0xc4]
	ands r1, r2, r1
	beq _020BF148
	add r3, r3, #0xc4
	mov r2, r4, lsr #0x5
	ldr r1, [r3, r2, lsl #0x2]
	and r0, r4, #0x1f
	orr r0, r1, r6, lsl r0
	str r0, [r3, r2, lsl #0x2]
	ldr r0, [r5, #0x0]
	orr r0, r0, #0x18
	str r0, [r5, #0x0]
	ldmia sp!, {r4-r8,pc}
_020BF148:
	ldr r1, _020BF2E4 ; =NNS_G3dRSOnGlb + 0xE00
	mov r2, #0x18
	mla r6, r0, r2, r1
	mla r1, r4, r2, r1
	mov r0, r6
	bl MIi_CpuCopy32
	mov r0, r6
	add r1, r5, #0x10
	mov r2, #0x18
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r8,pc}
_020BF174:
	ldr r3, [r1, #0x0]
	ldr r2, _020BF2E0 ; =NNS_G3dRS
	str r3, [r5, #0x4]
	ldr r3, [r1, #0x4]
	mov r7, r0, lsr #0x5
	str r3, [r5, #0x8]
	ldr r3, [r1, #0x8]
	and r8, r0, #0x1f
	str r3, [r5, #0xc]
	ldr r6, [r2, #0x0]
	mov r3, #0x1
	add r2, r6, r7, lsl #0x2
	mov r7, r3, lsl r8
	ldr r2, [r2, #0xc4]
	ands r2, r7, r2
	beq _020BF200
	ldr r3, _020BF2E4 ; =NNS_G3dRSOnGlb + 0xE00
	mov r2, #0x18
	mov r0, r1
	mla r1, r4, r2, r3
	bl MIi_CpuCopy32
	ldr r0, _020BF2E0 ; =NNS_G3dRS
	mov r2, r4, lsr #0x5
	ldr r1, [r0, #0x0]
	and r0, r4, #0x1f
	add r3, r1, #0xc4
	mov r1, #0x1
	mvn r0, r1, lsl r0
	ldr r1, [r3, r2, lsl #0x2]
	and r0, r1, r0
	str r0, [r3, r2, lsl #0x2]
	ldr r0, [r5, #0x0]
	orr r0, r0, #0x18
	str r0, [r5, #0x0]
	ldmia sp!, {r4-r8,pc}
_020BF200:
	mov r2, #0x18
	mul r12, r0, r2
	and r7, r4, #0x1f
	ldr r0, _020BF2E4 ; =NNS_G3dRSOnGlb + 0xE00
	add r6, r6, #0xc4
	mov lr, r4, lsr #0x5
	mvn r7, r3, lsl r7
	ldr r8, [r6, lr, lsl #0x2]
	mul r3, r4, r2
	and r4, r8, r7
	str r4, [r6, lr, lsl #0x2]
	ldr r7, [r1, #0x0]
	ldr r4, [r0, r12]
	ldr r6, _020BF2E8 ; =NNS_G3dRSOnGlb + 0xE04
	smull r8, r4, r7, r4
	mov r7, r8, lsr #0xc
	orr r7, r7, r4, lsl #0x14
	str r7, [r0, r3]
	ldr r8, [r1, #0x4]
	ldr r4, [r6, r12]
	ldr r7, _020BF2EC ; =NNS_G3dRSOnGlb + 0xE08
	smull lr, r4, r8, r4
	mov r8, lr, lsr #0xc
	orr r8, r8, r4, lsl #0x14
	str r8, [r6, r3]
	ldr r8, [r1, #0x8]
	ldr r4, [r7, r12]
	ldr r6, _020BF2F0 ; =NNS_G3dRSOnGlb + 0xE0C
	smull lr, r4, r8, r4
	mov r8, lr, lsr #0xc
	orr r8, r8, r4, lsl #0x14
	str r8, [r7, r3]
	ldr r7, [r1, #0xc]
	ldr r4, [r6, r12]
	ldr lr, _020BF2F4 ; =NNS_G3dRSOnGlb + 0xE10
	smull r8, r4, r7, r4
	mov r7, r8, lsr #0xc
	orr r7, r7, r4, lsl #0x14
	str r7, [r6, r3]
	ldr r7, [r1, #0x10]
	ldr r4, [lr, r12]
	ldr r6, _020BF2F8 ; =NNS_G3dRSOnGlb + 0xE14
	smull r8, r4, r7, r4
	add r0, r0, r12
	mov r7, r8, lsr #0xc
	orr r7, r7, r4, lsl #0x14
	str r7, [lr, r3]
	ldr lr, [r1, #0x14]
	ldr r4, [r6, r12]
	add r1, r5, #0x10
	smull r5, r4, lr, r4
	mov r5, r5, lsr #0xc
	orr r5, r5, r4, lsl #0x14
	str r5, [r6, r3]
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020BF2E0: .word NNS_G3dRS
_020BF2E4: .word NNS_G3dRSOnGlb + 0xE00
_020BF2E8: .word NNS_G3dRSOnGlb + 0xE04
_020BF2EC: .word NNS_G3dRSOnGlb + 0xE08
_020BF2F0: .word NNS_G3dRSOnGlb + 0xE0C
_020BF2F4: .word NNS_G3dRSOnGlb + 0xE10
_020BF2F8: .word NNS_G3dRSOnGlb + 0xE14
	arm_func_end NNSi_G3dGetJointScaleSi3d

	arm_func_start NNSi_G3dSendJointSRTSi3d
NNSi_G3dSendJointSRTSi3d: ; 0x020BF2FC
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x10
	mov r6, r0
	ldr r0, [r6, #0x0]
	mov r5, #0x0
	ands r4, r0, #0x18
	bne _020BF328
	add r1, r6, #0x1c
	mov r0, #0x1b
	mov r2, #0x3
	bl NNS_G3dGeBufferOP_N
_020BF328:
	ldr r0, [r6, #0x0]
	ands r0, r0, #0x4
	bne _020BF398
	cmp r4, #0x0
	movne r5, #0x1
	bne _020BF398
	ldr r2, [r6, #0x4c]
	ldr r0, [r6, #0x10]
	add r1, sp, #0x0
	smull r3, r0, r2, r0
	mov r2, r3, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [sp, #0x0]
	ldr r3, [r6, #0x50]
	ldr r2, [r6, #0x14]
	mov r0, #0x1c
	smull r12, r2, r3, r2
	mov r3, r12, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	str r3, [sp, #0x4]
	ldr r12, [r6, #0x54]
	ldr r3, [r6, #0x18]
	mov r2, #0x3
	smull lr, r3, r12, r3
	mov r12, lr, lsr #0xc
	orr r12, r12, r3, lsl #0x14
	str r12, [sp, #0x8]
	bl NNS_G3dGeBufferOP_N
_020BF398:
	ldr r0, [r6, #0x0]
	ands r0, r0, #0x2
	bne _020BF3D4
	cmp r5, #0x0
	beq _020BF3C0
	add r1, r6, #0x28
	mov r0, #0x19
	mov r2, #0xc
	bl NNS_G3dGeBufferOP_N
	b _020BF3EC
_020BF3C0:
	add r1, r6, #0x28
	mov r0, #0x1a
	mov r2, #0x9
	bl NNS_G3dGeBufferOP_N
	b _020BF3EC
_020BF3D4:
	cmp r5, #0x0
	beq _020BF3EC
	add r1, r6, #0x4c
	mov r0, #0x1c
	mov r2, #0x3
	bl NNS_G3dGeBufferOP_N
_020BF3EC:
	cmp r4, #0x0
	bne _020BF404
	add r1, r6, #0x10
	mov r0, #0x1b
	mov r2, #0x3
	bl NNS_G3dGeBufferOP_N
_020BF404:
	ldr r0, [r6, #0x0]
	ands r0, r0, #0x1
	addne sp, sp, #0x10
	ldmneia sp!, {r4-r6,pc}
	add r1, r6, #0x4
	mov r0, #0x1b
	mov r2, #0x3
	bl NNS_G3dGeBufferOP_N
	add sp, sp, #0x10
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNSi_G3dSendJointSRTSi3d
