	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; NNS_G2dMakeCellToOams
	arm_func_start FUN_020B1AF8
FUN_020B1AF8: ; 0x020B1AF8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x34
	ldrh r5, [r2, #0x0]
	ldr r4, [sp, #0x60]
	ldr r10, [sp, #0x58]
	str r4, [sp, #0x60]
	cmp r1, r5
	movcs r1, r5
	mov r4, #0x0
	cmp r1, #0x0
	str r4, [sp, #0x0]
	bls _020B1E7C
	ldrh r4, [sp, #0x5c]
	mov r4, r4, lsl #0x19
	str r4, [sp, #0x4]
	ldr r4, [sp, #0x0]
	str r4, [sp, #0x14]
	mov r4, #0x100
	str r4, [sp, #0xc]
	mov r4, #0x300
	str r4, [sp, #0x8]
	mov r4, #0x1
	str r4, [sp, #0x10]
_020B1B54:
	ldr r5, [sp, #0x0]
	mov r6, #0x6
	mul r6, r5, r6
	ldr r8, [r2, #0x4]
	ldr r4, [sp, #0x0]
	add r7, r0, r5, lsl #0x3
	ldrh r5, [r8, r6]
	mov r4, r4, lsl #0x3
	add r9, r8, r6
	strh r5, [r0, r4]
	ldrh r4, [r9, #0x2]
	cmp r3, #0x0
	strh r4, [r7, #0x2]
	ldrh r4, [r9, #0x4]
	strh r4, [r7, #0x4]
	bne _020B1B9C
	cmp r10, #0x0
	beq _020B1E60
_020B1B9C:
	ldr r5, [r7, #0x0]
	ldr r4, _020B1E88 ; =0x01FF0000
	and r4, r5, r4
	mov r4, r4, lsr #0x10
	mov r4, r4, lsl #0x10
	mov r4, r4, asr #0x10
	cmp r4, #0xff
	orrgt r4, r4, #0xff00
	movgt r4, r4, lsl #0x10
	movgt r4, r4, asr #0x10
	mov r4, r4, lsl #0xc
	str r4, [sp, #0x20]
	ldr r4, [r7, #0x0]
	and r4, r4, #0xff
	mov r4, r4, lsl #0x10
	mov r4, r4, asr #0x10
	cmp r4, #0x7f
	orrgt r4, r4, #0xff00
	movgt r4, r4, lsl #0x10
	movgt r4, r4, asr #0x10
	mov r4, r4, lsl #0xc
	str r4, [sp, #0x24]
	cmp r3, #0x0
	beq _020B1E00
	ldr r5, [r7, #0x0]
	and r6, r5, #0x300
	cmp r6, #0x100
	beq _020B1C1C
	cmp r6, #0x300
	beq _020B1C1C
	and r4, r5, #0x30000000
	orr r6, r6, r4
_020B1C1C:
	cmp r6, #0x300
	bne _020B1C70
	ldr r4, _020B1E8C ; =0xC000C000
	ldr r8, _020B1E90 ; =UNK_020FF8AC
	and r5, r5, r4
	and r4, r5, #0xc000
	mov r6, r4, asr #0xe
	and r4, r5, #0xc0000000
	mov r4, r4, lsr #0x1e
	mov r4, r4, lsl #0x1
	add r8, r8, r6, lsl #0x3
	ldrh r9, [r4, r8]
	ldr r8, _020B1E94 ; =UNK_020FF894
	ldr r5, [sp, #0x20]
	add r6, r8, r6, lsl #0x3
	add r5, r5, r9, lsl #0xb
	str r5, [sp, #0x20]
	ldrh r4, [r4, r6]
	ldr r5, [sp, #0x24]
	add r4, r5, r4, lsl #0xb
	str r4, [sp, #0x24]
_020B1C70:
	ldr r4, [sp, #0x60]
	ldr r5, [r3, #0x8]
	cmp r4, #0x0
	ldrne r8, [sp, #0x8]
	add r4, sp, #0x20
	ldreq r8, [sp, #0xc]
	mov r6, r4
	cmp r8, #0x300
	ldreq r9, [sp, #0x10]
	mov r12, #0x1000
	ldrne r9, [sp, #0x14]
	cmp r4, r4
	ldr r4, [sp, #0x24]
	addeq r6, sp, #0x28
	smull r11, r4, r5, r4
	adds r5, r11, r12
	adc r11, r4, #0x0
	ldr r4, [r3, #0x0]
	ldr lr, [sp, #0x20]
	smlal r5, r11, r4, lr
	mov r4, r5, lsr #0xc
	orr r4, r4, r11, lsl #0x14
	str r4, [r6, #0x0]
	ldr r4, [r3, #0xc]
	ldr r5, [sp, #0x24]
	ldr lr, [r3, #0x4]
	smull r11, r5, r4, r5
	adds r11, r11, r12
	adc r4, r5, #0x0
	add r5, sp, #0x28
	cmp r6, r5
	ldr r5, [sp, #0x20]
	smlal r11, r4, lr, r5
	mov r5, r11, lsr #0xc
	orr r5, r5, r4, lsl #0x14
	str r5, [r6, #0x4]
	ldreq r5, [sp, #0x28]
	ldreq r4, [sp, #0x2c]
	streq r5, [sp, #0x20]
	streq r4, [sp, #0x24]
	cmp r8, #0x100
	beq _020B1D38
	cmp r8, #0x300
	beq _020B1D38
	ldr r5, [r7, #0x0]
	ldr r4, _020B1E98 ; =0xC1FFFCFF
	and r4, r5, r4
	orr r4, r4, r8
	str r4, [r7, #0x0]
	b _020B1D54
_020B1D38:
	ldr r5, [r7, #0x0]
	ldr r4, _020B1E98 ; =0xC1FFFCFF
	and r4, r5, r4
	orr r5, r4, r8
	ldr r4, [sp, #0x4]
	orr r4, r4, r5
	str r4, [r7, #0x0]
_020B1D54:
	ldr r6, [r7, #0x0]
	ldr r5, _020B1E8C ; =0xC000C000
	cmp r9, #0x0
	and r8, r6, r5
	and r5, r8, #0xc000
	mov r6, r5, asr #0xe
	and r5, r8, #0xc0000000
	ldr r8, _020B1E90 ; =UNK_020FF8AC
	mov r5, r5, lsr #0x1e
	mov r5, r5, lsl #0x1
	add r8, r8, r6, lsl #0x3
	ldrh r9, [r5, r8]
	ldr r8, _020B1E94 ; =UNK_020FF894
	ldr r4, [sp, #0x20]
	add r6, r8, r6, lsl #0x3
	mov r11, r9, asr #0x1
	ldrh r5, [r5, r6]
	mov r8, r11, lsl #0xc
	ldr r6, [r3, #0x0]
	rsb r12, r8, #0x0
	mov r9, r5, asr #0x1
	mla r12, r6, r11, r12
	ldr r5, [r3, #0x8]
	mla r6, r5, r9, r12
	add r6, r4, r6
	str r6, [sp, #0x20]
	ldr r12, [r3, #0x4]
	mov r5, r9, lsl #0xc
	str r12, [sp, #0x1c]
	ldr r12, [r3, #0xc]
	rsb lr, r5, #0x0
	str r12, [sp, #0x18]
	ldr r12, [sp, #0x1c]
	ldr r4, [sp, #0x24]
	mla r11, r12, r11, lr
	ldr r12, [sp, #0x18]
	subne r6, r6, r8
	mla r9, r12, r9, r11
	add r4, r4, r9
	str r4, [sp, #0x24]
	subne r4, r4, r5
	strne r6, [sp, #0x20]
	strne r4, [sp, #0x24]
_020B1E00:
	cmp r10, #0x0
	beq _020B1E28
	ldr r6, [sp, #0x20]
	ldr r4, [r10, #0x0]
	ldr r5, [sp, #0x24]
	add r4, r6, r4
	str r4, [sp, #0x20]
	ldr r4, [r10, #0x4]
	add r4, r5, r4
	str r4, [sp, #0x24]
_020B1E28:
	ldr r4, [sp, #0x20]
	ldr r6, [r7, #0x0]
	add r5, r4, #0x800
	ldr r4, _020B1E9C ; =0x000001FF
	and r4, r4, r5, asr #0xc
	ldr r5, _020B1EA0 ; =0xFE00FF00
	and r6, r6, r5
	ldr r5, [sp, #0x24]
	add r5, r5, #0x800
	mov r5, r5, asr #0xc
	and r5, r5, #0xff
	orr r5, r6, r5
	orr r4, r5, r4, lsl #0x10
	str r4, [r7, #0x0]
_020B1E60:
	ldr r4, [sp, #0x0]
	add r4, r4, #0x1
	mov r4, r4, lsl #0x10
	mov r4, r4, lsr #0x10
	str r4, [sp, #0x0]
	cmp r4, r1
	blo _020B1B54
_020B1E7C:
	mov r0, r1
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B1E88: .word 0x01FF0000
_020B1E8C: .word 0xC000C000
_020B1E90: .word UNK_020FF8AC
_020B1E94: .word UNK_020FF894
_020B1E98: .word 0xC1FFFCFF
_020B1E9C: .word 0x000001FF
_020B1EA0: .word 0xFE00FF00
	arm_func_end FUN_020B1AF8

	; _end
	arm_func_start FUN_020B1EA4
FUN_020B1EA4: ; 0x020B1EA4
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020B0518
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
	mov r0, r4
	bl FUN_020B1FC4
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020B1EA4

	; _end
	arm_func_start FUN_020B1EC4
FUN_020B1EC4: ; 0x020B1EC4
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020B0534
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
	mov r0, r4
	bl FUN_020B1FC4
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020B1EC4

	; _end
	arm_func_start FUN_020B1EE4
FUN_020B1EE4: ; 0x020B1EE4
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020B0438
	mov r0, r4
	bl FUN_020B1FC4
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020B1EE4

	; _end
	arm_func_start FUN_020B1EFC
FUN_020B1EFC: ; 0x020B1EFC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov r4, r2
	ldr r2, [r4, #0xc]
	mov r5, r1
	ldr r1, [r2, #0x0]
	ldr r2, [sp, #0x34]
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x38]
	str r2, [sp, #0x4]
	mov r6, r3
	mov r7, r0
	ldr r12, [sp, #0x3c]
	str r1, [sp, #0x8]
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x2c]
	ldr r3, [sp, #0x30]
	mov r0, r6
	str r12, [sp, #0xc]
	bl FUN_020B45F0
	str r6, [r7, #0x34]
	str r4, [r7, #0x30]
	add r0, r7, #0x38
	mov r1, #0x1
	str r6, [r7, #0x34]
	bl FUN_020B1A68
	mov r0, r7
	bl FUN_020B04C0
	mov r0, r7
	mov r1, r5
	bl FUN_020B1EE4
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,pc}
	arm_func_end FUN_020B1EFC

	; _end
	arm_func_start FUN_020B1F80
FUN_020B1F80: ; 0x020B1F80
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	str r2, [r5, #0x30]
	mvn r2, #0x0
	add r0, r5, #0x38
	mov r1, #0x1
	str r2, [r5, #0x34]
	bl FUN_020B1A68
	mov r0, r5
	bl FUN_020B04C0
	mov r0, r5
	mov r1, r4
	bl FUN_020B1EE4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	arm_func_end FUN_020B1F80

	; _end
	arm_func_start FUN_020B1FC4
FUN_020B1FC4: ; 0x020B1FC4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r1, [r5, #0x0]
	ldrh r1, [r1, #0x4]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
	bl FUN_020B06E0
	mov r4, r0
	ldr r7, [r5, #0x30]
	ldrh r1, [r4, #0x0]
	mov r0, r7
	bl FUN_020AFE8C
	str r0, [r5, #0x2c]
	ldr r1, [r5, #0x18]
	add r0, r5, #0x38
	ldr r2, [r1, #0x4]
	mov r1, #0x1
	and r6, r2, #0xff
	bl FUN_020B1A68
	cmp r6, #0x0
	beq _020B2068
	cmp r6, #0x2
	bne _020B203C
	ldrsh r1, [r4, #0x4]
	ldrsh r2, [r4, #0x6]
	add r0, r5, #0x38
	bl FUN_020B1AB4
	b _020B2068
_020B203C:
	ldr r1, [r4, #0x4]
	ldr r2, [r4, #0x8]
	add r0, r5, #0x38
	bl FUN_020B1A78
	ldrh r1, [r4, #0x2]
	add r0, r5, #0x38
	bl FUN_020B1A98
	ldrsh r1, [r4, #0xc]
	ldrsh r2, [r4, #0xe]
	add r0, r5, #0x38
	bl FUN_020B1AB4
_020B2068:
	ldr r2, [r7, #0xc]
	cmp r2, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
	ldr r1, [r5, #0x34]
	mvn r0, #0x0
	cmp r1, r0
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
	ldrh r1, [r4, #0x0]
	ldr r2, [r2, #0x4]
	ldr r0, [r5, #0x34]
	add r3, r2, r1, lsl #0x3
	ldr r1, [r2, r1, lsl #0x3]
	ldr r2, [r3, #0x4]
	bl FUN_020B4400
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	arm_func_end FUN_020B1FC4

