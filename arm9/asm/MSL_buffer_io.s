    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start __convert_from_newlines
__convert_from_newlines:
	bx lr
	arm_func_end __convert_from_newlines

	arm_func_start __convert_to_newlines
__convert_to_newlines:
	bx lr
	arm_func_end __convert_to_newlines

	arm_func_start __prep_buffer
__prep_buffer:
	ldr r1, [r0, #0x1c]
	str r1, [r0, #0x24]
	ldr r3, [r0, #0x20]
	str r3, [r0, #0x28]
	ldr r2, [r0, #0x18]
	ldr r1, [r0, #0x2c]
	and r1, r2, r1
	sub r1, r3, r1
	str r1, [r0, #0x28]
	ldr r1, [r0, #0x18]
	str r1, [r0, #0x34]
	bx lr
	arm_func_end __prep_buffer

	arm_func_start __load_buffer
__load_buffer:
	stmdb sp!, {r4-r6,lr}
	mov r5, r2
	mov r4, r0
	mov r6, r1
	bl __prep_buffer
	cmp r5, #0x1
	ldreq r0, [r4, #0x20]
	add r2, r4, #0x28
	streq r0, [r4, #0x28]
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x1c]
	ldr r3, [r4, #0x48]
	ldr r12, [r4, #0x3c]
	blx r12
	cmp r0, #0x2
	moveq r1, #0x0
	streq r1, [r4, #0x28]
	cmp r6, #0x0
	ldrne r1, [r4, #0x28]
	strne r1, [r6, #0x0]
	cmp r0, #0x0
	ldmneia sp!, {r4-r6,pc}
	ldr r1, [r4, #0x18]
	ldr r0, [r4, #0x28]
	add r0, r1, r0
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x4]
	mov r0, r0, lsl #0x13
	movs r0, r0, lsr #0x1f
	bne _020DE4F4
	ldr r0, [r4, #0x1c]
	add r1, r4, #0x28
	bl __convert_to_newlines
_020DE4F4:
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}
	arm_func_end __load_buffer

	arm_func_start __flush_buffer
__flush_buffer:
	stmdb sp!, {r3-r5,lr}
	mov r5, r0
	ldr r2, [r5, #0x24]
	ldr r0, [r5, #0x1c]
	mov r4, r1
	subs r0, r2, r0
	beq _020DE574
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x4]
	mov r0, r0, lsl #0x13
	movs r0, r0, lsr #0x1f
	bne _020DE538
	ldr r0, [r5, #0x1c]
	add r1, r5, #0x28
	bl __convert_from_newlines
_020DE538:
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0x1c]
	ldr r3, [r5, #0x48]
	ldr r12, [r5, #0x40]
	add r2, r5, #0x28
	blx r12
	cmp r4, #0x0
	ldrne r1, [r5, #0x28]
	strne r1, [r4, #0x0]
	cmp r0, #0x0
	ldmneia sp!, {r3-r5,pc}
	ldr r1, [r5, #0x18]
	ldr r0, [r5, #0x28]
	add r0, r1, r0
	str r0, [r5, #0x18]
_020DE574:
	mov r0, r5
	bl __prep_buffer
	mov r0, #0x0
	ldmia sp!, {r3-r5,pc}
	arm_func_end __flush_buffer

    .section .exceptix,4

	.word __load_buffer
	.short 141
	.word 0x00200700
	.word __flush_buffer
	.short 137
	.word 0x00200300
