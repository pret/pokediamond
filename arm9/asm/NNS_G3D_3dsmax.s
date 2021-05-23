	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	; calcTexMtx_
	.global UNK_021067D0
UNK_021067D0: ; 0x021067D0
	.word FUN_020BF988
	.word FUN_020BF894
	.word FUN_020BF810
	.word FUN_020BF7C8
	.word FUN_020BF6C8
	.word FUN_020BF5E8
	.word FUN_020BF598
	.word FUN_020BF574

	.section .text

	; NNSi_G3dSendTexSRT3dsMax
	arm_func_start FUN_020BF42C
FUN_020BF42C: ; 0x020BF42C
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x50
	mov r4, r0
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	ands r0, r0, #0x8
	ldrne r0, _020BF568 ; =0x00101610
	mov r3, #0x3
	strne r0, [sp, #0x0]
	ldreq r0, _020BF56C ; =0x00101810
	mov r2, #0x2
	streq r0, [sp, #0x0]
	mov r0, #0x1000
	str r0, [sp, #0x44]
	str r3, [sp, #0x4]
	str r2, [sp, #0x48]
	str r1, [sp, #0x40]
	str r1, [sp, #0x34]
	str r1, [sp, #0x30]
	str r1, [sp, #0x2c]
	str r1, [sp, #0x28]
	str r1, [sp, #0x24]
	str r1, [sp, #0x20]
	str r1, [sp, #0x14]
	str r1, [sp, #0x10]
	ldr r1, [r4, #0x0]
	ldr r0, _020BF570 ; =UNK_021067D0
	and r1, r1, #0x7
	ldr r2, [r0, r1, lsl #0x2]
	add r0, sp, #0x8
	mov r1, r4
	blx r2
	ldr r3, [r4, #0x30]
	cmp r3, #0x1000
	beq _020BF4FC
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	smull r2, r0, r3, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [sp, #0x8]
	ldr r2, [r4, #0x30]
	ldr r0, [sp, #0x38]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [sp, #0xc]
	ldr r1, [r4, #0x30]
	smull r2, r0, r1, r0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [sp, #0x38]
_020BF4FC:
	ldr r3, [r4, #0x34]
	cmp r3, #0x1000
	beq _020BF54C
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	smull r2, r0, r3, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [sp, #0x18]
	ldr r2, [r4, #0x34]
	ldr r0, [sp, #0x3c]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [sp, #0x1c]
	ldr r1, [r4, #0x34]
	smull r2, r0, r1, r0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [sp, #0x3c]
_020BF54C:
	add r1, sp, #0x0
	ldr r0, [sp, #0x0]
	add r1, r1, #0x4
	mov r2, #0x12
	bl FUN_020BB1C0
	add sp, sp, #0x50
	ldmia sp!, {r4,pc}
	.balign 4
_020BF568: .word 0x00101610
_020BF56C: .word 0x00101810
_020BF570: .word UNK_021067D0
	arm_func_end FUN_020BF42C

	; _end
	arm_func_start FUN_020BF574
FUN_020BF574: ; 0x020BF574
	mov r2, #0x1000
	str r2, [r0, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
	str r1, [r0, #0x10]
	str r2, [r0, #0x14]
	str r1, [r0, #0x30]
	str r1, [r0, #0x34]
	bx lr
	arm_func_end FUN_020BF574

	; _end
	arm_func_start FUN_020BF598
FUN_020BF598: ; 0x020BF598
	ldr r2, [r1, #0x18]
	mov r12, #0x0
	str r2, [r0, #0x0]
	ldr r2, [r1, #0x1c]
	str r2, [r0, #0x14]
	str r12, [r0, #0x4]
	ldr r3, [r1, #0x18]
	ldrh r2, [r1, #0x2c]
	rsb r3, r3, #0x1000
	mul r2, r3, r2
	mov r2, r2, lsl #0x3
	str r2, [r0, #0x30]
	ldr r2, [r1, #0x1c]
	ldrh r1, [r1, #0x2e]
	rsb r2, r2, #0x1000
	mul r1, r2, r1
	mov r1, r1, lsl #0x3
	str r1, [r0, #0x34]
	str r12, [r0, #0x10]
	bx lr
	arm_func_end FUN_020BF598

	; _end
	arm_func_start FUN_020BF5E8
FUN_020BF5E8: ; 0x020BF5E8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldrh r2, [r5, #0x2c]
	ldrh r1, [r5, #0x2e]
	mov r6, r0
	mov r4, r2, lsl #0xc
	mov r7, r1, lsl #0xc
	mov r0, r7
	mov r1, r4
	bl FX_DivAsync
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x0]
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x14]
	bl FX_GetDivResult
	ldrsh r2, [r5, #0x20]
	mov r1, r7
	mul r0, r2, r0
	mov r2, r0, asr #0xc
	mov r0, r4
	str r2, [r6, #0x4]
	bl FX_DivAsync
	ldrh r2, [r5, #0x2c]
	ldrh r1, [r5, #0x2e]
	ldrsh r4, [r5, #0x22]
	rsb r0, r2, #0x0
	rsb r1, r1, #0x0
	mov r0, r0, lsl #0xb
	ldrsh r3, [r5, #0x20]
	mov r1, r1, lsl #0xb
	smull r7, lr, r4, r0
	smull r12, r4, r3, r1
	subs r7, r7, r12
	sbc r3, lr, r4
	mov r4, r7, lsr #0x8
	orr r4, r4, r3, lsl #0x18
	add r2, r4, r2, lsl #0xf
	str r2, [r6, #0x30]
	ldrsh r2, [r5, #0x22]
	ldrsh r3, [r5, #0x20]
	ldrh r12, [r5, #0x2e]
	smull r4, r1, r2, r1
	smlal r4, r1, r3, r0
	mov r0, r4, lsr #0x8
	orr r0, r0, r1, lsl #0x18
	add r0, r0, r12, lsl #0xf
	str r0, [r6, #0x34]
	bl FX_GetDivResult
	ldrsh r1, [r5, #0x20]
	rsb r1, r1, #0x0
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r6, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	arm_func_end FUN_020BF5E8

	; _end
	arm_func_start FUN_020BF6C8
FUN_020BF6C8: ; 0x020BF6C8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r9, r1
	ldrh r2, [r9, #0x2c]
	ldrh r1, [r9, #0x2e]
	mov r10, r0
	mov r8, r2, lsl #0xc
	mov r11, r1, lsl #0xc
	mov r0, r11
	mov r1, r8
	bl FX_DivAsync
	ldrsh r0, [r9, #0x22]
	ldr r3, [r9, #0x18]
	ldrsh r5, [r9, #0x20]
	ldr r4, [r9, #0x1c]
	smull r2, r1, r3, r0
	mov r7, r2, lsr #0xc
	orr r7, r7, r1, lsl #0x14
	smull r2, r1, r3, r5
	mov r6, r2, lsr #0xc
	orr r6, r6, r1, lsl #0x14
	smull r3, r2, r4, r0
	smull r1, r0, r4, r5
	mov r5, r3, lsr #0xc
	orr r5, r5, r2, lsl #0x14
	mov r4, r1, lsr #0xc
	orr r4, r4, r0, lsl #0x14
	str r7, [r10, #0x0]
	str r5, [r10, #0x14]
	bl FX_GetDivResult
	mov r1, r11
	mul r0, r4, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x4]
	mov r0, r8
	bl FX_DivAsync
	ldrh r3, [r9, #0x2c]
	ldrh r1, [r9, #0x2e]
	rsb r0, r3, #0x0
	rsb r1, r1, #0x0
	mov r2, r1, lsl #0xb
	mov r11, r0, lsl #0xb
	smull r1, r0, r7, r11
	smull r8, r7, r5, r2
	smlal r8, r7, r4, r11
	mov r4, r8, lsr #0x8
	orr r4, r4, r7, lsl #0x18
	smull r5, r2, r6, r2
	subs r1, r1, r5
	sbc r0, r0, r2
	mov r1, r1, lsr #0x8
	orr r1, r1, r0, lsl #0x18
	add r0, r1, r3, lsl #0xf
	str r0, [r10, #0x30]
	ldrh r0, [r9, #0x2e]
	add r0, r4, r0, lsl #0xf
	str r0, [r10, #0x34]
	bl FX_GetDivResult
	rsb r1, r6, #0x0
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	arm_func_end FUN_020BF6C8

	; _end
	arm_func_start FUN_020BF7C8
FUN_020BF7C8: ; 0x020BF7C8
	mov r2, #0x1000
	str r2, [r0, #0x0]
	str r2, [r0, #0x14]
	mov r12, #0x0
	str r12, [r0, #0x4]
	ldr r3, [r1, #0x24]
	ldrh r2, [r1, #0x2c]
	rsb r3, r3, #0x0
	mul r2, r3, r2
	mov r2, r2, lsl #0x4
	str r2, [r0, #0x30]
	ldrh r2, [r1, #0x2e]
	ldr r1, [r1, #0x28]
	mul r2, r1, r2
	mov r1, r2, lsl #0x4
	str r1, [r0, #0x34]
	str r12, [r0, #0x10]
	bx lr
	arm_func_end FUN_020BF7C8

	; _end
	arm_func_start FUN_020BF810
FUN_020BF810: ; 0x020BF810
	stmdb sp!, {r4-r6,lr}
	ldr r2, [r1, #0x18]
	mov r3, #0x0
	str r2, [r0, #0x0]
	ldr r2, [r1, #0x1c]
	str r2, [r0, #0x14]
	str r3, [r0, #0x4]
	ldrh r5, [r1, #0x2c]
	ldr r12, [r1, #0x24]
	ldrh r2, [r1, #0x2e]
	mul lr, r12, r5
	rsb r12, r5, #0x0
	mov r12, r12, lsl #0xb
	ldr r4, [r1, #0x18]
	sub r12, r12, lr
	smull lr, r12, r4, r12
	ldr r6, [r1, #0x28]
	mov r4, lr, lsr #0x8
	orr r4, r4, r12, lsl #0x18
	add r4, r4, r5, lsl #0xf
	str r4, [r0, #0x30]
	mul r4, r6, r2
	rsb r5, r2, #0x0
	ldr r2, [r1, #0x1c]
	add r4, r4, r5, lsl #0xb
	smull lr, r12, r2, r4
	mov r2, lr, lsr #0x8
	ldrh r1, [r1, #0x2e]
	orr r2, r2, r12, lsl #0x18
	add r1, r2, r1, lsl #0xf
	str r1, [r0, #0x34]
	str r3, [r0, #0x10]
	ldmia sp!, {r4-r6,pc}
	arm_func_end FUN_020BF810

	; _end
	arm_func_start FUN_020BF894
FUN_020BF894: ; 0x020BF894
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldrh r2, [r5, #0x2c]
	ldrh r1, [r5, #0x2e]
	mov r6, r0
	mov r4, r2, lsl #0xc
	mov r7, r1, lsl #0xc
	mov r0, r7
	mov r1, r4
	bl FX_DivAsync
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x0]
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x14]
	bl FX_GetDivResult
	ldrsh r2, [r5, #0x20]
	mov r1, r7
	mul r0, r2, r0
	mov r2, r0, asr #0xc
	mov r0, r4
	str r2, [r6, #0x4]
	bl FX_DivAsync
	ldrh r2, [r5, #0x2c]
	ldrh r7, [r5, #0x2e]
	ldr r1, [r5, #0x28]
	ldr r0, [r5, #0x24]
	rsb r4, r2, #0x0
	mul r3, r1, r7
	rsb r1, r7, #0x0
	add r1, r3, r1, lsl #0xb
	ldrsh r3, [r5, #0x20]
	mov r7, r4, lsl #0xb
	mul r4, r0, r2
	sub r0, r7, r4
	ldrsh lr, [r5, #0x22]
	smull r12, r4, r3, r1
	smull r7, r3, lr, r0
	subs r7, r7, r12
	sbc r3, r3, r4
	mov r4, r7, lsr #0x8
	orr r4, r4, r3, lsl #0x18
	add r2, r4, r2, lsl #0xf
	str r2, [r6, #0x30]
	ldrsh r2, [r5, #0x22]
	ldrsh r3, [r5, #0x20]
	ldrh r12, [r5, #0x2e]
	smull r4, r1, r2, r1
	smlal r4, r1, r3, r0
	mov r0, r4, lsr #0x8
	orr r0, r0, r1, lsl #0x18
	add r0, r0, r12, lsl #0xf
	str r0, [r6, #0x34]
	bl FX_GetDivResult
	ldrsh r1, [r5, #0x20]
	rsb r1, r1, #0x0
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r6, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	arm_func_end FUN_020BF894

	; _end
	arm_func_start FUN_020BF988
FUN_020BF988: ; 0x020BF988
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r9, r1
	ldrh r2, [r9, #0x2c]
	ldrh r1, [r9, #0x2e]
	mov r10, r0
	mov r8, r2, lsl #0xc
	mov r11, r1, lsl #0xc
	mov r0, r11
	mov r1, r8
	bl FX_DivAsync
	ldrsh r0, [r9, #0x22]
	ldr r3, [r9, #0x18]
	ldrsh r5, [r9, #0x20]
	ldr r4, [r9, #0x1c]
	smull r2, r1, r3, r0
	mov r7, r2, lsr #0xc
	orr r7, r7, r1, lsl #0x14
	smull r2, r1, r3, r5
	mov r6, r2, lsr #0xc
	orr r6, r6, r1, lsl #0x14
	smull r3, r2, r4, r0
	smull r1, r0, r4, r5
	mov r5, r3, lsr #0xc
	orr r5, r5, r2, lsl #0x14
	mov r4, r1, lsr #0xc
	orr r4, r4, r0, lsl #0x14
	str r7, [r10, #0x0]
	str r5, [r10, #0x14]
	bl FX_GetDivResult
	mov r1, r11
	mul r0, r4, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x4]
	mov r0, r8
	bl FX_DivAsync
	ldrh r1, [r9, #0x2c]
	ldrh r8, [r9, #0x2e]
	ldr r2, [r9, #0x28]
	rsb r0, r1, #0x0
	mul r3, r2, r8
	rsb r2, r8, #0x0
	add r8, r3, r2, lsl #0xb
	mov r0, r0, lsl #0xb
	smull r3, r2, r5, r8
	smull r8, r5, r6, r8
	ldr r11, [r9, #0x24]
	mul r12, r11, r1
	sub r0, r0, r12
	smlal r3, r2, r4, r0
	smull r4, r0, r7, r0
	subs r4, r4, r8
	sbc r0, r0, r5
	mov r4, r4, lsr #0x8
	orr r4, r4, r0, lsl #0x18
	add r0, r4, r1, lsl #0xf
	str r0, [r10, #0x30]
	ldrh r1, [r9, #0x2e]
	mov r0, r3, lsr #0x8
	orr r0, r0, r2, lsl #0x18
	add r0, r0, r1, lsl #0xf
	str r0, [r10, #0x34]
	bl FX_GetDivResult
	rsb r1, r6, #0x0
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	arm_func_end FUN_020BF988

