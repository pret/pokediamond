	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; NNS_G3dDraw1Mat1Shp
	arm_func_start FUN_020BAFB8
FUN_020BAFB8: ; 0x020BAFB8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x6c
	mov r6, r0
	ldr r12, [r6, #0x1c]
	mov r4, r1
	mov r5, r2
	mov r7, r3
	cmp r12, #0x1000
	beq _020BAFF8
	add r1, sp, #0x54
	mov r0, #0x1b
	mov r2, #0x3
	str r12, [sp, #0x54]
	str r12, [sp, #0x58]
	str r12, [sp, #0x5c]
	bl FUN_020BB1C0
_020BAFF8:
	cmp r7, #0x0
	beq _020BB150
	ldr r0, [r6, #0x8]
	add r3, r6, r0
	ldrh r0, [r3, #0xa]
	add r2, r3, #0x4
	ldrh r1, [r2, r0]
	add r0, r2, r0
	mla r0, r1, r4, r0
	ldr r0, [r0, #0x4]
	add r4, r3, r0
	ldr r0, [r4, #0xc]
	ands r0, r0, #0x1f0000
	addeq sp, sp, #0x6c
	ldmeqia sp!, {r4-r7,pc}
	ldr r0, _020BB1B4 ; =0x00293130
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x4]
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x8]
	str r0, [sp, #0x8]
	ldr r1, [r4, #0xc]
	str r1, [sp, #0xc]
	ldrh r0, [r4, #0x1e]
	ands r0, r0, #0x20
	bicne r0, r1, #0x1f0000
	ldr r1, _020BB1B8 ; =0x00002B2A
	strne r0, [sp, #0xc]
	str r1, [sp, #0x10]
	ldr r2, [r4, #0x14]
	ldr r0, [sp, #0x0]
	str r2, [sp, #0x14]
	ldrh r3, [r4, #0x1c]
	add r1, sp, #0x4
	mov r2, #0x6
	str r3, [sp, #0x18]
	bl FUN_020BB1C0
	ldrh r0, [r4, #0x1e]
	ands r0, r0, #0x1
	beq _020BB150
	ldrb r12, [r6, #0x16]
	mov r3, #0x8
	ldr r1, _020BB1BC ; =UNK_02106620
	str r3, [sp, #0x1c]
	ldrh r2, [r4, #0x20]
	add r0, r4, #0x2c
	ldr r1, [r1, r12, lsl #0x2]
	strh r2, [sp, #0x48]
	ldrh r2, [r4, #0x22]
	strh r2, [sp, #0x4a]
	ldr r2, [r4, #0x24]
	str r2, [sp, #0x4c]
	ldr r2, [r4, #0x28]
	str r2, [sp, #0x50]
	ldrh r2, [r4, #0x1e]
	ands r2, r2, #0x2
	orrne r2, r3, #0x1
	strne r2, [sp, #0x1c]
	bne _020BB0F8
	ldr r2, [r0, #0x0]
	str r2, [sp, #0x34]
	ldr r2, [r0, #0x4]
	add r0, r0, #0x8
	str r2, [sp, #0x38]
_020BB0F8:
	ldrh r2, [r4, #0x1e]
	ands r2, r2, #0x4
	ldrne r2, [sp, #0x1c]
	orrne r2, r2, #0x2
	strne r2, [sp, #0x1c]
	bne _020BB124
	ldrsh r2, [r0, #0x0]
	strh r2, [sp, #0x3c]
	ldrsh r2, [r0, #0x2]
	add r0, r0, #0x4
	strh r2, [sp, #0x3e]
_020BB124:
	ldrh r2, [r4, #0x1e]
	ands r2, r2, #0x8
	ldreq r2, [r0, #0x0]
	streq r2, [sp, #0x40]
	ldreq r0, [r0, #0x4]
	streq r0, [sp, #0x44]
	ldrne r0, [sp, #0x1c]
	orrne r0, r0, #0x4
	strne r0, [sp, #0x1c]
	add r0, sp, #0x1c
	blx r1
_020BB150:
	ldr r0, [r6, #0xc]
	add r2, r6, r0
	ldrh r0, [r2, #0x6]
	ldrh r1, [r2, r0]
	add r0, r2, r0
	mla r0, r1, r5, r0
	ldr r0, [r0, #0x4]
	add r2, r2, r0
	ldr r0, [r2, #0x8]
	ldr r1, [r2, #0xc]
	add r0, r2, r0
	bl FUN_020BB2B0
	ldr r3, [r6, #0x20]
	cmp r3, #0x1000
	addeq sp, sp, #0x6c
	ldmeqia sp!, {r4-r7,pc}
	add r1, sp, #0x60
	mov r0, #0x1b
	mov r2, #0x3
	str r3, [sp, #0x60]
	str r3, [sp, #0x64]
	str r3, [sp, #0x68]
	bl FUN_020BB1C0
	add sp, sp, #0x6c
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020BB1B4: .word 0x00293130
_020BB1B8: .word 0x00002B2A
_020BB1BC: .word UNK_02106620
	arm_func_end FUN_020BAFB8

