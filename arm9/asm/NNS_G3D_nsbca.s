	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global pivotUtil_
pivotUtil_: ; 0x020FFA14
	.byte 0x04, 0x05, 0x07, 0x08
	.byte 0x03, 0x05, 0x06, 0x08
	.byte 0x03, 0x04, 0x06, 0x07
	.byte 0x01, 0x02, 0x07, 0x08
	.byte 0x00, 0x02, 0x06, 0x08
	.byte 0x00, 0x01, 0x06, 0x07
	.byte 0x01, 0x02, 0x04, 0x05
	.byte 0x00, 0x02, 0x03, 0x05
	.byte 0x00, 0x01, 0x03, 0x04

	.section .text

	arm_func_start getRotDataByIdx_
getRotDataByIdx_: ; 0x020BC500
	stmdb sp!, {r4,lr}
	ands r4, r3, #0x8000
	beq _020BC5E0
	mov r2, #0x0
	str r2, [r0, #0x20]
	ldr r4, [r0, #0x20]
	ldr r2, _020BC684 ; =0x00007FFF
	str r4, [r0, #0x1c]
	ldr r4, [r0, #0x1c]
	and r3, r3, r2
	str r4, [r0, #0x18]
	ldr r4, [r0, #0x18]
	mov r2, #0x3
	str r4, [r0, #0x14]
	ldr r4, [r0, #0x14]
	mul r2, r3, r2
	str r4, [r0, #0x10]
	ldr r4, [r0, #0x10]
	mov r3, r2, lsl #0x1
	str r4, [r0, #0xc]
	ldr r4, [r0, #0xc]
	add r2, r1, r2, lsl #0x1
	str r4, [r0, #0x8]
	ldr r4, [r0, #0x8]
	str r4, [r0, #0x4]
	ldr r4, [r0, #0x4]
	str r4, [r0, #0x0]
	ldrsh r4, [r1, r3]
	ldrsh r12, [r2, #0x2]
	ldrsh r3, [r2, #0x4]
	and r1, r4, #0xf
	ands r4, r4, #0x10
	movne lr, #0x1000
	rsbne lr, lr, #0x0
	moveq lr, #0x1000
	str lr, [r0, r1, lsl #0x2]
	ldr r4, _020BC688 ; =pivotUtil_
	ldr lr, _020BC68C ; =pivotUtil_ + 1
	ldrb r4, [r4, r1, lsl #0x2]
	str r12, [r0, r4, lsl #0x2]
	ldrb lr, [lr, r1, lsl #0x2]
	str r3, [r0, lr, lsl #0x2]
	ldrsh lr, [r2, #0x0]
	ands lr, lr, #0x20
	ldr lr, _020BC690 ; =pivotUtil_ + 2
	rsbne r3, r3, #0x0
	ldrb lr, [lr, r1, lsl #0x2]
	str r3, [r0, lr, lsl #0x2]
	ldrsh r2, [r2, #0x0]
	ands r2, r2, #0x40
	ldr r2, _020BC694 ; =pivotUtil_ + 3
	rsbne r12, r12, #0x0
	ldrb r1, [r2, r1, lsl #0x2]
	str r12, [r0, r1, lsl #0x2]
	mov r0, #0x0
	ldmia sp!, {r4,pc}
_020BC5E0:
	ldr r1, _020BC684 ; =0x00007FFF
	mov r12, #0x5
	and r1, r3, r1
	mul r3, r1, r12
	add r1, r2, r3, lsl #0x1
	ldrsh lr, [r1, #0x8]
	mov r12, r3, lsl #0x1
	mov r3, lr, asr #0x3
	str r3, [r0, #0x10]
	ldrsh r12, [r2, r12]
	and r2, lr, #0x7
	mov r2, r2, lsl #0x10
	mov r3, r12, asr #0x3
	str r3, [r0, #0x0]
	ldrsh r3, [r1, #0x2]
	and r12, r12, #0x7
	orr lr, r12, r2, asr #0xd
	mov r2, r3, asr #0x3
	str r2, [r0, #0x4]
	ldrsh r12, [r1, #0x4]
	mov r2, lr, lsl #0x10
	and lr, r3, #0x7
	mov r3, r12, asr #0x3
	str r3, [r0, #0x8]
	ldrsh r3, [r1, #0x6]
	orr r1, lr, r2, asr #0xd
	mov r1, r1, lsl #0x10
	and r2, r12, #0x7
	orr r1, r2, r1, asr #0xd
	mov r1, r1, lsl #0x10
	and r2, r3, #0x7
	orr r1, r2, r1, asr #0xd
	mov r1, r1, lsl #0x10
	mov r1, r1, asr #0x10
	mov r2, r3, asr #0x3
	mov r1, r1, lsl #0x13
	str r2, [r0, #0xc]
	mov r1, r1, asr #0x13
	str r1, [r0, #0x14]
	mov r0, #0x1
	ldmia sp!, {r4,pc}
	.balign 4
_020BC684: .word 0x00007FFF
_020BC688: .word pivotUtil_
_020BC68C: .word pivotUtil_ + 1
_020BC690: .word pivotUtil_ + 2
_020BC694: .word pivotUtil_ + 3
	arm_func_end getRotDataByIdx_

	arm_func_start getRotDataEx_
getRotDataEx_: ; 0x020BC698
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x48
	ldrh r4, [r3, #0x4]
	ldr r5, [r3, #0xc]
	ldr r8, [r3, #0x10]
	ldr r7, [r2, #0x4]
	mov r12, r1, asr #0xc
	sub r4, r4, #0x1
	mov r6, r0
	cmp r12, r4
	add r5, r3, r5
	add r4, r3, r8
	add r8, r3, r7
	ldr r7, [r2, #0x0]
	bne _020BC780
	ands r0, r7, #0xc0000000
	beq _020BC6F0
	ands r0, r7, #0x40000000
	andne r0, r12, #0x1
	addne r12, r0, r12, lsr #0x1
	andeq r0, r12, #0x3
	addeq r12, r0, r12, lsr #0x2
_020BC6F0:
	ldr r0, [r3, #0x8]
	ands r0, r0, #0x2
	movne r7, #0x0
	bne _020BC7F4
	mov r0, r12, lsl #0x1
	ldrh r3, [r8, r0]
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl getRotDataByIdx_
	cmp r0, #0x0
	addeq sp, sp, #0x48
	ldmeqia sp!, {r4-r10,pc}
	ldr r9, [r6, #0x14]
	ldr r5, [r6, #0x4]
	ldr r4, [r6, #0x10]
	ldr r2, [r6, #0x8]
	mul r1, r5, r9
	mul r0, r2, r4
	sub r0, r1, r0
	ldr r7, [r6, #0xc]
	ldr r8, [r6, #0x0]
	mov r3, r0, asr #0xc
	mul r1, r2, r7
	mul r0, r8, r9
	sub r2, r1, r0
	mul r1, r8, r4
	mul r0, r5, r7
	sub r0, r1, r0
	str r3, [r6, #0x18]
	mov r1, r2, asr #0xc
	str r1, [r6, #0x1c]
	mov r0, r0, asr #0xc
	add sp, sp, #0x48
	str r0, [r6, #0x20]
	ldmia sp!, {r4-r10,pc}
_020BC780:
	ands r0, r7, #0xc0000000
	beq _020BC7F0
	ldr r0, _020BC9C4 ; =0x1FFF0000
	ands r2, r7, #0x40000000
	and r0, r7, r0
	mov r0, r0, lsr #0x10
	beq _020BC7C4
	cmp r12, r0
	movcs r12, r0, lsr #0x1
	addcs r7, r12, #0x1
	bhs _020BC7F4
	ldr r0, _020BC9C8 ; =0x00001FFF
	mov r12, r12, lsr #0x1
	add r7, r12, #0x1
	and r10, r1, r0
	mov r9, #0x2
	b _020BC800
_020BC7C4:
	cmp r12, r0
	andcs r0, r12, #0x3
	addcs r12, r0, r12, lsr #0x2
	addcs r7, r12, #0x1
	bhs _020BC7F4
	ldr r0, _020BC9CC ; =0x00003FFF
	mov r12, r12, lsr #0x2
	add r7, r12, #0x1
	and r10, r1, r0
	mov r9, #0x4
	b _020BC800
_020BC7F0:
	add r7, r12, #0x1
_020BC7F4:
	ldr r0, _020BC9D0 ; =0x00000FFF
	mov r9, #0x1
	and r10, r1, r0
_020BC800:
	mov r0, r12, lsl #0x1
	ldrh r3, [r8, r0]
	add r0, sp, #0x0
	mov r1, r5
	mov r2, r4
	bl getRotDataByIdx_
	mov r1, r7, lsl #0x1
	ldrh r3, [r8, r1]
	orr r7, r0, #0x0
	add r0, sp, #0x24
	mov r1, r5
	mov r2, r4
	bl getRotDataByIdx_
	ldr r3, [sp, #0x0]
	ldr r1, [sp, #0x24]
	mul r2, r3, r9
	sub r1, r1, r3
	mul r1, r10, r1
	add r1, r2, r1, asr #0xc
	str r1, [r6, #0x0]
	ldr r3, [sp, #0x4]
	ldr r1, [sp, #0x28]
	mul r2, r3, r9
	sub r1, r1, r3
	mul r1, r10, r1
	add r1, r2, r1, asr #0xc
	str r1, [r6, #0x4]
	ldr r3, [sp, #0x8]
	ldr r1, [sp, #0x2c]
	mul r2, r3, r9
	sub r1, r1, r3
	mul r1, r10, r1
	add r1, r2, r1, asr #0xc
	str r1, [r6, #0x8]
	ldr r3, [sp, #0xc]
	ldr r1, [sp, #0x30]
	mul r2, r3, r9
	sub r1, r1, r3
	mul r1, r10, r1
	add r1, r2, r1, asr #0xc
	str r1, [r6, #0xc]
	ldr r2, [sp, #0x10]
	ldr r1, [sp, #0x34]
	orr r7, r7, r0
	sub r0, r1, r2
	mul r1, r2, r9
	mul r0, r10, r0
	add r0, r1, r0, asr #0xc
	str r0, [r6, #0x10]
	ldr r2, [sp, #0x14]
	ldr r0, [sp, #0x38]
	mul r1, r2, r9
	sub r0, r0, r2
	mul r0, r10, r0
	add r2, r1, r0, asr #0xc
	mov r0, r6
	mov r1, r6
	str r2, [r6, #0x14]
	bl VEC_Normalize
	add r0, r6, #0xc
	mov r1, r0
	bl VEC_Normalize
	cmp r7, #0x0
	bne _020BC968
	ldr r3, [sp, #0x18]
	ldr r1, [sp, #0x3c]
	mul r2, r3, r9
	sub r1, r1, r3
	mul r1, r10, r1
	add r1, r2, r1, asr #0xc
	str r1, [r6, #0x18]
	ldr r3, [sp, #0x1c]
	ldr r1, [sp, #0x40]
	mul r2, r3, r9
	sub r1, r1, r3
	mul r1, r10, r1
	add r1, r2, r1, asr #0xc
	str r1, [r6, #0x1c]
	ldr r3, [sp, #0x20]
	ldr r1, [sp, #0x44]
	mul r2, r3, r9
	sub r1, r1, r3
	mul r1, r10, r1
	add r2, r2, r1, asr #0xc
	add r0, r6, #0x18
	mov r1, r0
	str r2, [r6, #0x20]
	bl VEC_Normalize
	add sp, sp, #0x48
	ldmia sp!, {r4-r10,pc}
_020BC968:
	ldr r9, [r6, #0x14]
	ldr r5, [r6, #0x4]
	ldr r8, [r6, #0x0]
	ldr r4, [r6, #0x10]
	ldr r2, [r6, #0x8]
	ldr r7, [r6, #0xc]
	mul r1, r5, r9
	mul r0, r2, r4
	sub r0, r1, r0
	mov r3, r0, asr #0xc
	mul r1, r2, r7
	mul r0, r8, r9
	sub r2, r1, r0
	mul r1, r8, r4
	mul r0, r5, r7
	sub r0, r1, r0
	str r3, [r6, #0x18]
	mov r1, r2, asr #0xc
	str r1, [r6, #0x1c]
	mov r0, r0, asr #0xc
	str r0, [r6, #0x20]
	add sp, sp, #0x48
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020BC9C4: .word 0x1FFF0000
_020BC9C8: .word 0x00001FFF
_020BC9CC: .word 0x00003FFF
_020BC9D0: .word 0x00000FFF
	arm_func_end getRotDataEx_

	arm_func_start getRotData_
getRotData_: ; 0x020BC9D4
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4c
	ldr r5, [r3, #0xc]
	ldr r4, [r3, #0x10]
	ldr r12, [r2, #0x0]
	ldr r2, [r2, #0x4]
	mov r6, r0
	mov r0, r1, asr #0xc
	add r5, r3, r5
	add r4, r3, r4
	add r8, r3, r2
	ands r1, r12, #0xc0000000
	beq _020BCD40
	ldr r1, _020BCDC0 ; =0x1FFF0000
	ands r2, r12, #0x40000000
	and r1, r12, r1
	mov r2, r1, lsr #0x10
	beq _020BCA44
	ands r1, r0, #0x1
	beq _020BCA3C
	cmp r0, r2
	movhi r0, r2, lsr #0x1
	addhi r0, r0, #0x1
	bhi _020BCD40
	mov r7, r0, lsr #0x1
	b _020BCBE8
_020BCA3C:
	mov r0, r0, lsr #0x1
	b _020BCD40
_020BCA44:
	ands r1, r0, #0x3
	beq _020BCBE0
	cmp r0, r2
	addhi r0, r1, r2, lsr #0x2
	bhi _020BCD40
	ands r1, r0, #0x1
	beq _020BCBD8
	ands r1, r0, #0x2
	movne r9, r0, lsr #0x2
	addne r0, r9, #0x1
	moveq r0, r0, lsr #0x2
	addeq r9, r0, #0x1
	mov r0, r0, lsl #0x1
	ldrh r3, [r8, r0]
	mov r0, r6
	mov r1, r5
	mov r2, r4
	mov r7, #0x0
	bl getRotDataByIdx_
	mov r1, r9, lsl #0x1
	ldrh r3, [r8, r1]
	orr r7, r7, r0
	add r0, sp, #0x0
	mov r1, r5
	mov r2, r4
	bl getRotDataByIdx_
	ldr r3, [sp, #0x0]
	ldr r1, [r6, #0x0]
	mov r2, #0x3
	mla r3, r1, r2, r3
	str r3, [r6, #0x0]
	ldr r3, [sp, #0x4]
	ldr r1, [r6, #0x4]
	orr r7, r7, r0
	mla r0, r1, r2, r3
	str r0, [r6, #0x4]
	ldr r3, [sp, #0x8]
	ldr r1, [r6, #0x8]
	mov r0, r6
	mla r3, r1, r2, r3
	str r3, [r6, #0x8]
	ldr r4, [sp, #0xc]
	ldr r3, [r6, #0xc]
	mov r1, r6
	mla r4, r3, r2, r4
	str r4, [r6, #0xc]
	ldr r4, [sp, #0x10]
	ldr r3, [r6, #0x10]
	mla r4, r3, r2, r4
	str r4, [r6, #0x10]
	ldr r4, [sp, #0x14]
	ldr r3, [r6, #0x14]
	mla r2, r3, r2, r4
	str r2, [r6, #0x14]
	bl VEC_Normalize
	add r0, r6, #0xc
	mov r1, r0
	bl VEC_Normalize
	cmp r7, #0x0
	bne _020BCB7C
	ldr r1, [sp, #0x18]
	ldr r0, [r6, #0x18]
	mov r2, #0x3
	mla r1, r0, r2, r1
	str r1, [r6, #0x18]
	ldr r3, [sp, #0x1c]
	ldr r1, [r6, #0x1c]
	add r0, r6, #0x18
	mla r3, r1, r2, r3
	str r3, [r6, #0x1c]
	ldr r4, [sp, #0x20]
	ldr r3, [r6, #0x20]
	mov r1, r0
	mla r2, r3, r2, r4
	str r2, [r6, #0x20]
	bl VEC_Normalize
	add sp, sp, #0x4c
	ldmia sp!, {r4-r9,pc}
_020BCB7C:
	ldr r12, [r6, #0x14]
	ldr r5, [r6, #0x4]
	ldr r4, [r6, #0x10]
	ldr r2, [r6, #0x8]
	mul r1, r5, r12
	mul r0, r2, r4
	sub r0, r1, r0
	ldr r7, [r6, #0xc]
	ldr r8, [r6, #0x0]
	mov r3, r0, asr #0xc
	mul r1, r2, r7
	mul r0, r8, r12
	sub r2, r1, r0
	mul r1, r8, r4
	mul r0, r5, r7
	sub r0, r1, r0
	str r3, [r6, #0x18]
	mov r1, r2, asr #0xc
	str r1, [r6, #0x1c]
	mov r0, r0, asr #0xc
	add sp, sp, #0x4c
	str r0, [r6, #0x20]
	ldmia sp!, {r4-r9,pc}
_020BCBD8:
	mov r7, r0, lsr #0x2
	b _020BCBE8
_020BCBE0:
	mov r0, r0, lsr #0x2
	b _020BCD40
_020BCBE8:
	mov r0, r7, lsl #0x1
	ldrh r3, [r8, r0]
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl getRotDataByIdx_
	add r1, r8, r7, lsl #0x1
	ldrh r3, [r1, #0x2]
	orr r7, r0, #0x0
	add r0, sp, #0x24
	mov r1, r5
	mov r2, r4
	bl getRotDataByIdx_
	ldr r2, [r6, #0x0]
	ldr r1, [sp, #0x24]
	orr r7, r7, r0
	add r0, r2, r1
	str r0, [r6, #0x0]
	ldr r2, [r6, #0x4]
	ldr r1, [sp, #0x28]
	mov r0, r6
	add r1, r2, r1
	str r1, [r6, #0x4]
	ldr r3, [r6, #0x8]
	ldr r2, [sp, #0x2c]
	mov r1, r6
	add r2, r3, r2
	str r2, [r6, #0x8]
	ldr r3, [r6, #0xc]
	ldr r2, [sp, #0x30]
	add r2, r3, r2
	str r2, [r6, #0xc]
	ldr r3, [r6, #0x10]
	ldr r2, [sp, #0x34]
	add r2, r3, r2
	str r2, [r6, #0x10]
	ldr r3, [r6, #0x14]
	ldr r2, [sp, #0x38]
	add r2, r3, r2
	str r2, [r6, #0x14]
	bl VEC_Normalize
	add r0, r6, #0xc
	mov r1, r0
	bl VEC_Normalize
	cmp r7, #0x0
	bne _020BCCE4
	ldr r2, [r6, #0x18]
	ldr r1, [sp, #0x3c]
	add r0, r6, #0x18
	add r1, r2, r1
	str r1, [r6, #0x18]
	ldr r3, [r6, #0x1c]
	ldr r2, [sp, #0x40]
	mov r1, r0
	add r2, r3, r2
	str r2, [r6, #0x1c]
	ldr r3, [r6, #0x20]
	ldr r2, [sp, #0x44]
	add r2, r3, r2
	str r2, [r6, #0x20]
	bl VEC_Normalize
	add sp, sp, #0x4c
	ldmia sp!, {r4-r9,pc}
_020BCCE4:
	ldr r12, [r6, #0x14]
	ldr r5, [r6, #0x4]
	ldr r4, [r6, #0x10]
	ldr r2, [r6, #0x8]
	mul r1, r5, r12
	mul r0, r2, r4
	sub r0, r1, r0
	ldr r7, [r6, #0xc]
	ldr r8, [r6, #0x0]
	mov r3, r0, asr #0xc
	mul r1, r2, r7
	mul r0, r8, r12
	sub r2, r1, r0
	mul r1, r8, r4
	mul r0, r5, r7
	sub r0, r1, r0
	str r3, [r6, #0x18]
	mov r1, r2, asr #0xc
	str r1, [r6, #0x1c]
	mov r0, r0, asr #0xc
	add sp, sp, #0x4c
	str r0, [r6, #0x20]
	ldmia sp!, {r4-r9,pc}
_020BCD40:
	mov r0, r0, lsl #0x1
	ldrh r3, [r8, r0]
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl getRotDataByIdx_
	cmp r0, #0x0
	addeq sp, sp, #0x4c
	ldmeqia sp!, {r4-r9,pc}
	ldr r12, [r6, #0x14]
	ldr r5, [r6, #0x4]
	ldr r8, [r6, #0x0]
	ldr r4, [r6, #0x10]
	ldr r2, [r6, #0x8]
	ldr r7, [r6, #0xc]
	mul r1, r5, r12
	mul r0, r2, r4
	sub r0, r1, r0
	mov r3, r0, asr #0xc
	mul r1, r2, r7
	mul r0, r8, r12
	sub r2, r1, r0
	mul r1, r8, r4
	mul r0, r5, r7
	sub r0, r1, r0
	str r3, [r6, #0x18]
	mov r1, r2, asr #0xc
	str r1, [r6, #0x1c]
	mov r0, r0, asr #0xc
	str r0, [r6, #0x20]
	add sp, sp, #0x4c
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020BCDC0: .word 0x1FFF0000
	arm_func_end getRotData_

	arm_func_start getScaleDataEx_
getScaleDataEx_: ; 0x020BCDC4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldrh r4, [r3, #0x4]
	ldr r6, [r2, #0x4]
	mov r5, r1, asr #0xc
	sub r4, r4, #0x1
	cmp r5, r4
	add r6, r3, r6
	ldr r2, [r2, #0x0]
	bne _020BCE58
	ands r4, r2, #0xc0000000
	beq _020BCE08
	ands r4, r2, #0x40000000
	andne r4, r5, #0x1
	addne r5, r4, r5, lsr #0x1
	andeq r4, r5, #0x3
	addeq r5, r4, r5, lsr #0x2
_020BCE08:
	ldr r3, [r3, #0x8]
	ands r3, r3, #0x2
	movne r4, #0x0
	bne _020BCED4
	ands r1, r2, #0x20000000
	ldreq r2, [r6, r5, lsl #0x3]
	addeq r1, r6, r5, lsl #0x3
	streq r2, [r0, #0x0]
	ldreq r1, [r1, #0x4]
	addeq sp, sp, #0x4
	streq r1, [r0, #0x4]
	ldmeqia sp!, {r4-r7,pc}
	mov r1, r5, lsl #0x2
	ldrsh r2, [r6, r1]
	add r1, r6, r5, lsl #0x2
	add sp, sp, #0x4
	str r2, [r0, #0x0]
	ldrsh r1, [r1, #0x2]
	str r1, [r0, #0x4]
	ldmia sp!, {r4-r7,pc}
_020BCE58:
	ands r3, r2, #0xc0000000
	beq _020BCED0
	ldr r3, _020BCF60 ; =0x1FFF0000
	ands r4, r2, #0x40000000
	and r3, r2, r3
	mov r3, r3, lsr #0x10
	beq _020BCEA0
	cmp r5, r3
	movcs r5, r3, lsr #0x1
	addcs r4, r5, #0x1
	bhs _020BCED4
	ldr r3, _020BCF64 ; =0x00001FFF
	mov r5, r5, lsr #0x1
	add r4, r5, #0x1
	and lr, r1, r3
	mov r12, #0x2
	mov r3, #0x1
	b _020BCEE4
_020BCEA0:
	cmp r5, r3
	andcs r3, r5, #0x3
	addcs r5, r3, r5, lsr #0x2
	addcs r4, r5, #0x1
	bhs _020BCED4
	ldr r3, _020BCF68 ; =0x00003FFF
	mov r5, r5, lsr #0x2
	add r4, r5, #0x1
	and lr, r1, r3
	mov r12, #0x4
	mov r3, #0x2
	b _020BCEE4
_020BCED0:
	add r4, r5, #0x1
_020BCED4:
	ldr r3, _020BCF6C ; =0x00000FFF
	mov r12, #0x1
	and lr, r1, r3
	mov r3, #0x0
_020BCEE4:
	ands r1, r2, #0x20000000
	beq _020BCF10
	mov r2, r5, lsl #0x2
	add r1, r6, r5, lsl #0x2
	mov r5, r4, lsl #0x2
	add r4, r6, r4, lsl #0x2
	ldrsh r2, [r6, r2]
	ldrsh r1, [r1, #0x2]
	ldrsh r5, [r6, r5]
	ldrsh r4, [r4, #0x2]
	b _020BCF28
_020BCF10:
	add r1, r6, r5, lsl #0x3
	add r7, r6, r4, lsl #0x3
	ldr r2, [r6, r5, lsl #0x3]
	ldr r1, [r1, #0x4]
	ldr r5, [r6, r4, lsl #0x3]
	ldr r4, [r7, #0x4]
_020BCF28:
	sub r5, r5, r2
	sub r4, r4, r1
	mul r6, r2, r12
	mul r2, lr, r5
	add r2, r6, r2, asr #0xc
	mov r5, r2, asr r3
	mul r2, r1, r12
	mul r1, lr, r4
	add r1, r2, r1, asr #0xc
	mov r1, r1, asr r3
	str r5, [r0, #0x0]
	str r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020BCF60: .word 0x1FFF0000
_020BCF64: .word 0x00001FFF
_020BCF68: .word 0x00003FFF
_020BCF6C: .word 0x00000FFF
	arm_func_end getScaleDataEx_

	arm_func_start getScaleData_
getScaleData_: ; 0x020BCF70
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r4, [r2, #0x4]
	ldr r12, [r2, #0x0]
	mov r1, r1, asr #0xc
	add r3, r3, r4
	ands r2, r12, #0xc0000000
	beq _020BD0D0
	ldr r2, _020BD184 ; =0x1FFF0000
	ands r4, r12, #0x40000000
	and r2, r12, r2
	mov r4, r2, lsr #0x10
	beq _020BCFCC
	ands r2, r1, #0x1
	beq _020BCFC4
	cmp r1, r4
	movhi r1, r4, lsr #0x1
	addhi r1, r1, #0x1
	bhi _020BD0D0
	mov r2, r1, lsr #0x1
	b _020BD110
_020BCFC4:
	mov r1, r1, lsr #0x1
	b _020BD0D0
_020BCFCC:
	ands r2, r1, #0x3
	beq _020BD0CC
	cmp r1, r4
	addhi r1, r2, r4, lsr #0x2
	bhi _020BD0D0
	ands r2, r1, #0x1
	beq _020BD0C4
	ands r2, r1, #0x2
	movne r1, r1, lsr #0x2
	addne r2, r1, #0x1
	moveq r2, r1, lsr #0x2
	addeq r1, r2, #0x1
	ands r4, r12, #0x20000000
	beq _020BD04C
	mov r5, r2, lsl #0x2
	mov r4, r1, lsl #0x2
	ldrsh r12, [r3, r5]
	ldrsh r5, [r3, r4]
	add r2, r3, r2, lsl #0x2
	add r4, r12, r12, lsl #0x1
	add r4, r5, r4
	mov r4, r4, asr #0x2
	str r4, [r0, #0x0]
	add r1, r3, r1, lsl #0x2
	ldrsh r3, [r2, #0x2]
	ldrsh r2, [r1, #0x2]
	add sp, sp, #0x4
	add r1, r3, r3, lsl #0x1
	add r1, r2, r1
	mov r1, r1, asr #0x2
	str r1, [r0, #0x4]
	ldmia sp!, {r4-r5,pc}
_020BD04C:
	ldr r5, [r3, r2, lsl #0x3]
	ldr r4, [r3, r1, lsl #0x3]
	mov r12, r5, asr #0x1f
	mov r12, r12, lsl #0x1
	mov lr, r5, lsl #0x1
	orr r12, r12, r5, lsr #0x1f
	adds lr, lr, r5
	adc r12, r12, r5, asr #0x1f
	adds lr, lr, r4
	adc r12, r12, r4, asr #0x1f
	mov lr, lr, lsr #0x2
	orr lr, lr, r12, lsl #0x1e
	str lr, [r0, #0x0]
	add r2, r3, r2, lsl #0x3
	ldr r12, [r2, #0x4]
	add r1, r3, r1, lsl #0x3
	mov r2, r12, asr #0x1f
	mov r2, r2, lsl #0x1
	mov r3, r12, lsl #0x1
	ldr r1, [r1, #0x4]
	orr r2, r2, r12, lsr #0x1f
	adds r3, r3, r12
	adc r2, r2, r12, asr #0x1f
	adds r3, r3, r1
	adc r1, r2, r1, asr #0x1f
	mov r2, r3, lsr #0x2
	orr r2, r2, r1, lsl #0x1e
	str r2, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
_020BD0C4:
	mov r2, r1, lsr #0x2
	b _020BD110
_020BD0CC:
	mov r1, r1, lsr #0x2
_020BD0D0:
	ands r2, r12, #0x20000000
	ldreq r2, [r3, r1, lsl #0x3]
	addeq r1, r3, r1, lsl #0x3
	streq r2, [r0, #0x0]
	ldreq r1, [r1, #0x4]
	addeq sp, sp, #0x4
	streq r1, [r0, #0x4]
	ldmeqia sp!, {r4-r5,pc}
	mov r2, r1, lsl #0x2
	ldrsh r2, [r3, r2]
	add r1, r3, r1, lsl #0x2
	add sp, sp, #0x4
	str r2, [r0, #0x0]
	ldrsh r1, [r1, #0x2]
	str r1, [r0, #0x4]
	ldmia sp!, {r4-r5,pc}
_020BD110:
	ands r1, r12, #0x20000000
	beq _020BD150
	mov r1, r2, lsl #0x2
	add r12, r3, r2, lsl #0x2
	ldrsh r2, [r3, r1]
	ldrsh r1, [r12, #0x4]
	add sp, sp, #0x4
	add r1, r2, r1
	mov r1, r1, asr #0x1
	str r1, [r0, #0x0]
	ldrsh r2, [r12, #0x2]
	ldrsh r1, [r12, #0x6]
	add r1, r2, r1
	mov r1, r1, asr #0x1
	str r1, [r0, #0x4]
	ldmia sp!, {r4-r5,pc}
_020BD150:
	add r12, r3, r2, lsl #0x3
	ldr r2, [r3, r2, lsl #0x3]
	ldr r1, [r12, #0x8]
	add r1, r2, r1
	mov r1, r1, asr #0x1
	str r1, [r0, #0x0]
	ldr r2, [r12, #0x4]
	ldr r1, [r12, #0xc]
	add r1, r2, r1
	mov r1, r1, asr #0x1
	str r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020BD184: .word 0x1FFF0000
	arm_func_end getScaleData_

	arm_func_start getTransDataEx_
getTransDataEx_: ; 0x020BD188
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldrh r4, [r3, #0x4]
	ldr lr, [r2, #0x4]
	mov r12, r1, asr #0xc
	sub r4, r4, #0x1
	cmp r12, r4
	add r4, r3, lr
	ldr lr, [r2, #0x0]
	bne _020BD230
	ands r2, lr, #0xc0000000
	beq _020BD1CC
	ands r2, lr, #0x40000000
	andne r2, r12, #0x1
	addne r12, r2, r12, lsr #0x1
	andeq r2, r12, #0x3
	addeq r12, r2, r12, lsr #0x2
_020BD1CC:
	ldr r2, [r3, #0x8]
	ands r2, r2, #0x2
	beq _020BD210
	ldr r2, _020BD2E8 ; =0x00000FFF
	ands r3, lr, #0x20000000
	and r3, r1, r2
	movne r1, r12, lsl #0x1
	ldrnesh r2, [r4, r1]
	ldrnesh r1, [r4, #0x0]
	add sp, sp, #0x4
	ldreq r2, [r4, r12, lsl #0x2]
	ldreq r1, [r4, #0x0]
	sub r1, r1, r2
	mul r1, r3, r1
	add r1, r2, r1, asr #0xc
	str r1, [r0, #0x0]
	ldmia sp!, {r4-r5,pc}
_020BD210:
	ands r1, lr, #0x20000000
	movne r1, r12, lsl #0x1
	ldrnesh r1, [r4, r1]
	add sp, sp, #0x4
	strne r1, [r0, #0x0]
	ldreq r1, [r4, r12, lsl #0x2]
	streq r1, [r0, #0x0]
	ldmia sp!, {r4-r5,pc}
_020BD230:
	ands r2, lr, #0xc0000000
	beq _020BD298
	ldr r2, _020BD2EC ; =0x1FFF0000
	ands r3, lr, #0x40000000
	and r2, lr, r2
	mov r2, r2, lsr #0x10
	beq _020BD270
	cmp r12, r2
	movcs r12, r2, lsr #0x1
	bhs _020BD298
	ldr r2, _020BD2F0 ; =0x00001FFF
	mov r12, r12, lsr #0x1
	and r5, r1, r2
	mov r2, #0x2
	mov r1, #0x1
	b _020BD2A8
_020BD270:
	cmp r12, r2
	andcs r2, r12, #0x3
	addcs r12, r2, r12, lsr #0x2
	bhs _020BD298
	ldr r2, _020BD2F4 ; =0x00003FFF
	mov r12, r12, lsr #0x2
	and r5, r1, r2
	mov r2, #0x4
	mov r1, #0x2
	b _020BD2A8
_020BD298:
	ldr r3, _020BD2E8 ; =0x00000FFF
	mov r2, #0x1
	and r5, r1, r3
	mov r1, #0x0
_020BD2A8:
	ands r3, lr, #0x20000000
	addne r3, r4, r12, lsl #0x1
	movne lr, r12, lsl #0x1
	ldrnesh r12, [r4, lr]
	ldrnesh r3, [r3, #0x2]
	addeq r3, r4, r12, lsl #0x2
	ldreq r12, [r4, r12, lsl #0x2]
	ldreq r3, [r3, #0x4]
	mul r4, r12, r2
	sub r3, r3, r12
	mul r2, r5, r3
	add r2, r4, r2, asr #0xc
	mov r1, r2, asr r1
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020BD2E8: .word 0x00000FFF
_020BD2EC: .word 0x1FFF0000
_020BD2F0: .word 0x00001FFF
_020BD2F4: .word 0x00003FFF
	arm_func_end getTransDataEx_

	arm_func_start getTransData_
getTransData_: ; 0x020BD2F8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r12, [r2, #0x4]
	ldr r2, [r2, #0x0]
	mov r1, r1, asr #0xc
	add r3, r3, r12
	ands r12, r2, #0xc0000000
	beq _020BD44C
	ldr ip, _020BD46C ; =0x1FFF0000
	ands lr, r2, #0x40000000
	and r12, r2, r12
	mov lr, r12, lsr #0x10
	beq _020BD354
	ands r12, r1, #0x1
	beq _020BD34C
	cmp r1, lr
	movhi r1, lr, lsr #0x1
	addhi r1, r1, #0x1
	bhi _020BD44C
	mov r12, r1, lsr #0x1
	b _020BD400
_020BD34C:
	mov r1, r1, lsr #0x1
	b _020BD44C
_020BD354:
	ands r12, r1, #0x3
	beq _020BD3F8
	cmp r1, lr
	addhi r1, r12, lr, lsr #0x2
	bhi _020BD44C
	ands r12, r1, #0x1
	beq _020BD3F0
	ands r12, r1, #0x2
	movne lr, r1, lsr #0x2
	addne r12, lr, #0x1
	moveq r12, r1, lsr #0x2
	addeq lr, r12, #0x1
	ands r1, r2, #0x20000000
	beq _020BD3B4
	mov r2, r12, lsl #0x1
	mov r1, lr, lsl #0x1
	ldrsh r12, [r3, r2]
	ldrsh r2, [r3, r1]
	mov r1, #0x3
	add sp, sp, #0x4
	smlabb r1, r12, r1, r2
	mov r1, r1, asr #0x2
	str r1, [r0, #0x0]
	ldmia sp!, {pc}
_020BD3B4:
	ldr r12, [r3, r12, lsl #0x2]
	ldr r1, [r3, lr, lsl #0x2]
	mov r2, r12, asr #0x1f
	mov r2, r2, lsl #0x1
	mov r3, r12, lsl #0x1
	orr r2, r2, r12, lsr #0x1f
	adds r3, r3, r12
	adc r2, r2, r12, asr #0x1f
	adds r3, r3, r1
	adc r1, r2, r1, asr #0x1f
	mov r2, r3, lsr #0x2
	orr r2, r2, r1, lsl #0x1e
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020BD3F0:
	mov r12, r1, lsr #0x2
	b _020BD400
_020BD3F8:
	mov r1, r1, lsr #0x2
	b _020BD44C
_020BD400:
	ands r1, r2, #0x20000000
	beq _020BD42C
	mov r2, r12, lsl #0x1
	add r1, r3, r12, lsl #0x1
	ldrsh r2, [r3, r2]
	ldrsh r1, [r1, #0x2]
	add sp, sp, #0x4
	add r1, r2, r1
	mov r1, r1, asr #0x1
	str r1, [r0, #0x0]
	ldmia sp!, {pc}
_020BD42C:
	add r1, r3, r12, lsl #0x2
	ldr r2, [r3, r12, lsl #0x2]
	ldr r1, [r1, #0x4]
	mov r2, r2, asr #0x1
	add r1, r2, r1, asr #0x1
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020BD44C:
	ands r2, r2, #0x20000000
	movne r1, r1, lsl #0x1
	ldrnesh r1, [r3, r1]
	strne r1, [r0, #0x0]
	ldreq r1, [r3, r1, lsl #0x2]
	streq r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020BD46C: .word 0x1FFF0000
	arm_func_end getTransData_

	arm_func_start getJntSRTAnmResult_
getJntSRTAnmResult_: ; 0x020BD470
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x34
	mov r9, r0
	add r0, r9, r1, lsl #0x1
	ldrh r0, [r0, #0x14]
	mov r7, r3
	mov r8, r2
	ldr r5, [r9, r0]
	add r1, r9, r0
	ands r0, r5, #0x1
	movne r0, #0x7
	strne r0, [r7, #0x0]
	bne _020BD814
	ldr r0, _020BD848 ; =0x00000FFF
	add r4, r1, #0x4
	ands r0, r8, r0
	beq _020BD4C4
	ldr r0, [r9, #0x8]
	ands r0, r0, #0x1
	movne r6, #0x1
	bne _020BD4C8
_020BD4C4:
	mov r6, #0x0
_020BD4C8:
	mov r0, #0x0
	str r0, [r7, #0x0]
	ands r0, r5, #0x6
	bne _020BD5C0
	ands r0, r5, #0x8
	bne _020BD51C
	cmp r6, #0x0
	beq _020BD500
	mov r1, r8
	mov r2, r4
	mov r3, r9
	add r0, r7, #0x4c
	bl getTransDataEx_
	b _020BD514
_020BD500:
	mov r1, r8
	mov r2, r4
	mov r3, r9
	add r0, r7, #0x4c
	bl getTransData_
_020BD514:
	add r4, r4, #0x8
	b _020BD524
_020BD51C:
	ldr r0, [r4], #0x4
	str r0, [r7, #0x4c]
_020BD524:
	ands r0, r5, #0x10
	bne _020BD568
	cmp r6, #0x0
	beq _020BD54C
	mov r1, r8
	mov r2, r4
	mov r3, r9
	add r0, r7, #0x50
	bl getTransDataEx_
	b _020BD560
_020BD54C:
	mov r1, r8
	mov r2, r4
	mov r3, r9
	add r0, r7, #0x50
	bl getTransData_
_020BD560:
	add r4, r4, #0x8
	b _020BD570
_020BD568:
	ldr r0, [r4], #0x4
	str r0, [r7, #0x50]
_020BD570:
	ands r0, r5, #0x20
	bne _020BD5B4
	cmp r6, #0x0
	beq _020BD598
	mov r1, r8
	mov r2, r4
	mov r3, r9
	add r0, r7, #0x54
	bl getTransDataEx_
	b _020BD5AC
_020BD598:
	mov r1, r8
	mov r2, r4
	mov r3, r9
	add r0, r7, #0x54
	bl getTransData_
_020BD5AC:
	add r4, r4, #0x8
	b _020BD5DC
_020BD5B4:
	ldr r0, [r4], #0x4
	str r0, [r7, #0x54]
	b _020BD5DC
_020BD5C0:
	ands r0, r5, #0x2
	ldrne r0, [r7, #0x0]
	orrne r0, r0, #0x4
	strne r0, [r7, #0x0]
	bne _020BD5DC
	mov r0, r7
	bl getMdlTrans_
_020BD5DC:
	ands r0, r5, #0xc0
	bne _020BD6A8
	ands r0, r5, #0x100
	bne _020BD628
	cmp r6, #0x0
	beq _020BD60C
	mov r1, r8
	mov r2, r4
	mov r3, r9
	add r0, r7, #0x28
	bl getRotDataEx_
	b _020BD620
_020BD60C:
	mov r1, r8
	mov r2, r4
	mov r3, r9
	add r0, r7, #0x28
	bl getRotData_
_020BD620:
	add r4, r4, #0x8
	b _020BD6C4
_020BD628:
	ldr r1, [r9, #0xc]
	ldr r2, [r9, #0x10]
	ldr r3, [r4, #0x0]
	add r0, r7, #0x28
	add r1, r9, r1
	add r2, r9, r2
	bl getRotDataByIdx_
	cmp r0, #0x0
	beq _020BD6A0
	ldr r12, [r7, #0x3c]
	ldr r0, [r7, #0x2c]
	ldr r3, [r7, #0x28]
	ldr r11, [r7, #0x38]
	ldr r1, [r7, #0x30]
	ldr r2, [r7, #0x34]
	mul r10, r0, r12
	mul lr, r1, r11
	sub r10, r10, lr
	mov r10, r10, asr #0xc
	mul lr, r1, r2
	mul r1, r3, r12
	sub r1, lr, r1
	mul r11, r3, r11
	mul r2, r0, r2
	sub r0, r11, r2
	str r10, [r7, #0x40]
	mov r1, r1, asr #0xc
	str r1, [r7, #0x44]
	mov r0, r0, asr #0xc
	str r0, [r7, #0x48]
_020BD6A0:
	add r4, r4, #0x4
	b _020BD6C4
_020BD6A8:
	ands r0, r5, #0x40
	ldrne r0, [r7, #0x0]
	orrne r0, r0, #0x2
	strne r0, [r7, #0x0]
	bne _020BD6C4
	mov r0, r7
	bl getMdlRot_
_020BD6C4:
	ands r0, r5, #0x600
	bne _020BD7F0
	ands r0, r5, #0x800
	bne _020BD71C
	cmp r6, #0x0
	beq _020BD6F4
	add r0, sp, #0x0
	mov r1, r8
	mov r2, r4
	mov r3, r9
	bl getScaleDataEx_
	b _020BD708
_020BD6F4:
	add r0, sp, #0x0
	mov r1, r8
	mov r2, r4
	mov r3, r9
	bl getScaleData_
_020BD708:
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x18]
	str r0, [sp, #0x24]
	b _020BD72C
_020BD71C:
	ldr r0, [r4, #0x0]
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x4]
	str r0, [sp, #0x24]
_020BD72C:
	ands r0, r5, #0x1000
	bne _020BD77C
	cmp r6, #0x0
	beq _020BD754
	add r0, sp, #0x8
	mov r1, r8
	mov r3, r9
	add r2, r4, #0x8
	bl getScaleDataEx_
	b _020BD768
_020BD754:
	add r0, sp, #0x8
	mov r1, r8
	mov r3, r9
	add r2, r4, #0x8
	bl getScaleData_
_020BD768:
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	str r1, [sp, #0x1c]
	str r0, [sp, #0x28]
	b _020BD78C
_020BD77C:
	ldr r0, [r4, #0x8]
	str r0, [sp, #0x1c]
	ldr r0, [r4, #0xc]
	str r0, [sp, #0x28]
_020BD78C:
	ands r0, r5, #0x2000
	bne _020BD7DC
	cmp r6, #0x0
	beq _020BD7B4
	add r0, sp, #0x10
	mov r1, r8
	mov r3, r9
	add r2, r4, #0x10
	bl getScaleDataEx_
	b _020BD7C8
_020BD7B4:
	add r0, sp, #0x10
	mov r1, r8
	mov r3, r9
	add r2, r4, #0x10
	bl getScaleData_
_020BD7C8:
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #0x14]
	str r1, [sp, #0x20]
	str r0, [sp, #0x2c]
	b _020BD814
_020BD7DC:
	ldr r0, [r4, #0x10]
	str r0, [sp, #0x20]
	ldr r0, [r4, #0x14]
	str r0, [sp, #0x2c]
	b _020BD814
_020BD7F0:
	ands r0, r5, #0x200
	ldrne r0, [r7, #0x0]
	orrne r0, r0, #0x1
	strne r0, [r7, #0x0]
	bne _020BD814
	mov r0, r7
	bl getMdlScale_
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,pc}
_020BD814:
	ldr r0, [r7, #0x0]
	add r1, sp, #0x18
	ands r0, r0, #0x1
	ldr r0, _020BD84C ; =NNS_G3dRS
	movne r3, #0x4
	ldr r4, [r0, #0x0]
	moveq r3, #0x0
	ldr r2, [r4, #0x0]
	ldr r4, [r4, #0xe8]
	mov r0, r7
	blx r4
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020BD848: .word 0x00000FFF
_020BD84C: .word NNS_G3dRS
	arm_func_end getJntSRTAnmResult_

	arm_func_start getMdlRot_
getMdlRot_: ; 0x020BD850
	stmdb sp!, {r4-r8,lr}
	ldr r1, _020BD990 ; =NNS_G3dRS
	mov r8, r0
	ldr r0, [r1, #0x0]
	ldr r3, [r0, #0xd4]
	ldr r0, [r0, #0x0]
	ldrh r2, [r3, #0x6]
	ldrb r0, [r0, #0x1]
	ldrh r1, [r3, r2]
	add r2, r3, r2
	mla r0, r1, r0, r2
	ldr r0, [r0, #0x4]
	ldrh r2, [r3, r0]
	add r4, r3, r0
	add r1, r4, #0x4
	ands r0, r2, #0x1
	addeq r1, r1, #0xc
	ands r0, r2, #0x2
	bne _020BD980
	ands r0, r2, #0x8
	beq _020BD934
	and r2, r2, #0xf0
	add r0, r8, #0x28
	mov r5, r2, asr #0x4
	ldrsh r7, [r1, #0x0]
	ldrsh r6, [r1, #0x2]
	bl MI_Zero36B
	ldrh r0, [r4, #0x0]
	add r1, r8, r5, lsl #0x2
	ands r0, r0, #0x100
	movne r0, #0x1000
	rsbne r2, r0, #0x0
	moveq r2, #0x1000
	ldr r0, _020BD994 ; =pivotUtil_
	str r2, [r1, #0x28]
	ldrb r1, [r0, r5, lsl #0x2]
	ldr r0, _020BD998 ; =pivotUtil_ + 1
	add r1, r8, r1, lsl #0x2
	str r7, [r1, #0x28]
	ldrb r0, [r0, r5, lsl #0x2]
	add r0, r8, r0, lsl #0x2
	str r6, [r0, #0x28]
	ldrh r0, [r4, #0x0]
	ands r0, r0, #0x200
	ldr r0, _020BD99C ; =pivotUtil_ + 2
	rsbne r6, r6, #0x0
	ldrb r0, [r0, r5, lsl #0x2]
	add r0, r8, r0, lsl #0x2
	str r6, [r0, #0x28]
	ldrh r0, [r4, #0x0]
	ands r0, r0, #0x400
	ldr r0, _020BD9A0 ; =pivotUtil_ + 3
	rsbne r7, r7, #0x0
	ldrb r0, [r0, r5, lsl #0x2]
	add r0, r8, r0, lsl #0x2
	str r7, [r0, #0x28]
	ldmia sp!, {r4-r8,pc}
_020BD934:
	ldrsh r0, [r4, #0x2]
	str r0, [r8, #0x28]
	ldrsh r0, [r1, #0x0]
	str r0, [r8, #0x2c]
	ldrsh r0, [r1, #0x2]
	str r0, [r8, #0x30]
	ldrsh r0, [r1, #0x4]
	str r0, [r8, #0x34]
	ldrsh r0, [r1, #0x6]
	str r0, [r8, #0x38]
	ldrsh r0, [r1, #0x8]
	str r0, [r8, #0x3c]
	ldrsh r0, [r1, #0xa]
	str r0, [r8, #0x40]
	ldrsh r0, [r1, #0xc]
	str r0, [r8, #0x44]
	ldrsh r0, [r1, #0xe]
	str r0, [r8, #0x48]
	ldmia sp!, {r4-r8,pc}
_020BD980:
	ldr r0, [r8, #0x0]
	orr r0, r0, #0x2
	str r0, [r8, #0x0]
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020BD990: .word NNS_G3dRS
_020BD994: .word pivotUtil_
_020BD998: .word pivotUtil_ + 1
_020BD99C: .word pivotUtil_ + 2
_020BD9A0: .word pivotUtil_ + 3
	arm_func_end getMdlRot_

	arm_func_start getMdlScale_
getMdlScale_: ; 0x020BD9A4
	stmdb sp!, {r4,lr}
	ldr r1, _020BDA04 ; =NNS_G3dRS
	ldr r12, [r1, #0x0]
	ldr r4, [r12, #0xd4]
	ldr r2, [r12, #0x0]
	ldrh lr, [r4, #0x6]
	ldrb r1, [r2, #0x1]
	ldrh r3, [r4, lr]
	add lr, r4, lr
	mla r1, r3, r1, lr
	ldr r1, [r1, #0x4]
	ldrh r3, [r4, r1]
	add r1, r4, r1
	add r1, r1, #0x4
	ands lr, r3, #0x1
	addeq r1, r1, #0xc
	ands lr, r3, #0x2
	bne _020BD9F8
	ands lr, r3, #0x8
	addne r1, r1, #0x4
	addeq r1, r1, #0x10
_020BD9F8:
	ldr r12, [r12, #0xe8]
	blx r12
	ldmia sp!, {r4,pc}
	.balign 4
_020BDA04: .word NNS_G3dRS
	arm_func_end getMdlScale_

	arm_func_start getMdlTrans_
getMdlTrans_: ; 0x020BDA08
	ldr r1, _020BDA6C ; =NNS_G3dRS
	ldr r1, [r1, #0x0]
	ldr r12, [r1, #0xd4]
	ldr r1, [r1, #0x0]
	ldrh r3, [r12, #0x6]
	ldrb r1, [r1, #0x1]
	ldrh r2, [r12, r3]
	add r3, r12, r3
	mla r1, r2, r1, r3
	ldr r2, [r1, #0x4]
	ldrh r1, [r12, r2]
	add r2, r12, r2
	ands r1, r1, #0x1
	ldrne r1, [r0, #0x0]
	orrne r1, r1, #0x4
	strne r1, [r0, #0x0]
	bxne lr
	ldr r1, [r2, #0x4]
	add r2, r2, #0x4
	str r1, [r0, #0x4c]
	ldr r1, [r2, #0x4]
	str r1, [r0, #0x50]
	ldr r1, [r2, #0x8]
	str r1, [r0, #0x54]
	bx lr
	.balign 4
_020BDA6C: .word NNS_G3dRS
	arm_func_end getMdlTrans_

	arm_func_start NNSi_G3dAnmCalcNsBca
NNSi_G3dAnmCalcNsBca: ; 0x020BDA70
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r3, r0
	ldr r0, [r1, #0x8]
	ldr r12, [r1, #0x0]
	ldrh r1, [r0, #0x4]
	mov r1, r1, lsl #0xc
	cmp r12, r1
	subge r12, r1, #0x1
	bge _020BDAA0
	cmp r12, #0x0
	movlt r12, #0x0
_020BDAA0:
	mov r1, r2
	mov r2, r12
	bl getJntSRTAnmResult_
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNSi_G3dAnmCalcNsBca

	arm_func_start NNSi_G3dAnmObjInitNsBca
NNSi_G3dAnmObjInitNsBca: ; 0x020BDAB4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	ldr r0, _020BDB3C ; =NNS_G3dFuncAnmJntNsBcaDefault
	str r4, [r5, #0x8]
	ldr r0, [r0, #0x0]
	add r1, r5, #0x1a
	str r0, [r5, #0xc]
	ldrb r2, [r2, #0x17]
	mov r0, #0x0
	strb r2, [r5, #0x19]
	ldrb r2, [r5, #0x19]
	mov r2, r2, lsl #0x1
	bl MIi_CpuClear16
	ldrh r0, [r4, #0x6]
	add r2, r4, #0x14
	mov r3, #0x0
	cmp r0, #0x0
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r5,pc}
_020BDB08:
	mov r0, r3, lsl #0x1
	ldrh r1, [r2, r0]
	add r0, r5, r3, lsl #0x1
	add r3, r3, #0x1
	ldr r1, [r4, r1]
	mov r1, r1, lsr #0x18
	orr r1, r1, #0x100
	strh r1, [r0, #0x1a]
	ldrh r0, [r4, #0x6]
	cmp r3, r0
	blo _020BDB08
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020BDB3C: .word NNS_G3dFuncAnmJntNsBcaDefault
	arm_func_end NNSi_G3dAnmObjInitNsBca
