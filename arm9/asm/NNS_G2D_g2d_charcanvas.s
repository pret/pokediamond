	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	; objs$8221
	.global UNK_020FF970
UNK_020FF970: ; 0x020FF970
	.byte 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x01, 0x01, 0x01, 0x02, 0x01, 0x02, 0x01
	.byte 0x00, 0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x00, 0x02, 0x01, 0x02, 0x02, 0x03, 0x03, 0x03

	; static const in function
	; shape$8277
	.global UNK_020FF990
UNK_020FF990: ; 0x020FF990
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x80, 0x00, 0x40, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x40, 0x00, 0xC0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0xC0, 0x00, 0x00, 0x00, 0xC0

	; static const in function
	.section .text

	; NNS_G2dArrangeOBJ1D
	arm_func_start FUN_020B5E50
FUN_020B5E50: ; 0x020B5E50
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x3c
	mov r7, r0
	mov r0, r1
	cmp r0, #0x8
	ldr r0, [sp, #0x60]
	str r1, [sp, #0x10]
	str r0, [sp, #0x60]
	ldr r0, [sp, #0x6c]
	str r2, [sp, #0x14]
	str r0, [sp, #0x6c]
	ldrlt r0, [sp, #0x10]
	mov r11, r3
	ldr r6, [sp, #0x64]
	ldr r5, [sp, #0x68]
	movge r2, #0x3
	clzlt r0, r0
	rsblt r2, r0, #0x1f
	ldr r0, [sp, #0x14]
	cmp r0, #0x8
	ldrlt r0, [sp, #0x14]
	movge r1, #0x3
	clzlt r0, r0
	rsblt r1, r0, #0x1f
	ldr r0, _020B6170 ; =UNK_020FF970
	mvn r3, #0x0
	add r1, r0, r1, lsl #0x3
	add r0, r1, r2, lsl #0x1
	ldrb r4, [r1, r2, lsl #0x1]
	ldrb r1, [r0, #0x1]
	ldr r2, [sp, #0x14]
	cmp r6, #0x0
	str r1, [sp, #0x18]
	ldr r1, [sp, #0x10]
	and r1, r1, r3, lsl r4
	str r1, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	and r1, r2, r3, lsl r1
	str r1, [sp, #0x20]
	moveq r1, #0x1
	streq r1, [sp, #0x24]
	movne r1, #0x2
	strne r1, [sp, #0x24]
	mov r1, #0x0
	str r1, [sp, #0x28]
	bl FUN_020B704C
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0x14]
	mov r10, r1, asr r4
	ldr r1, [sp, #0x18]
	mov r1, r2, asr r1
	str r1, [sp, #0x2c]
	ldr r1, [sp, #0x24]
	mov r2, r1, lsl r4
	ldr r1, [sp, #0x18]
	mov r2, r2, lsl r1
	ldr r1, [sp, #0x6c]
	mov r9, r2, asr r1
	mov r1, #0x0
	str r1, [sp, #0x30]
	str r1, [sp, #0x34]
	b _020B5FE8
_020B5F48:
	ldr r2, [sp, #0x30]
	ldr r1, [sp, #0x18]
	ldr r8, [sp, #0x34]
	mov r2, r2, lsl r1
	ldr r1, [sp, #0x60]
	add lr, r1, r2, lsl #0x3
	b _020B5FD4
_020B5F64:
	mov r1, r8, lsl r4
	add r2, r11, r1, lsl #0x3
	ldr r1, _020B6174 ; =0x000001FF
	ldr r3, [r7, #0x0]
	and r12, r2, r1
	ldr r1, _020B6178 ; =0xFE00FF00
	and r2, lr, #0xff
	and r1, r3, r1
	orr r1, r1, r2
	orr r1, r1, r12, lsl #0x10
	str r1, [r7, #0x0]
	ldr r3, [r7, #0x0]
	ldr r1, _020B617C ; =0x3FFF3FFF
	mov r2, #0x400
	and r1, r3, r1
	orr r1, r1, r0
	str r1, [r7, #0x0]
	rsb r1, r2, #0x0
	ldrh r2, [r7, #0x4]
	add r8, r8, #0x1
	and r1, r2, r1
	orr r1, r1, r5
	strh r1, [r7, #0x4]
	ldr r1, [r7, #0x0]
	add r5, r5, r9
	bic r1, r1, #0x2000
	orr r1, r1, r6, lsl #0xd
	str r1, [r7], #0x8
_020B5FD4:
	cmp r8, r10
	blt _020B5F64
	ldr r1, [sp, #0x30]
	add r1, r1, #0x1
	str r1, [sp, #0x30]
_020B5FE8:
	ldr r2, [sp, #0x30]
	ldr r1, [sp, #0x2c]
	cmp r2, r1
	blt _020B5F48
	ldr r0, [sp, #0x28]
	mla r0, r10, r1, r0
	str r0, [sp, #0x28]
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x10]
	cmp r1, r0
	bhs _020B6078
	ldr r0, [sp, #0x60]
	ldr r1, [sp, #0x10]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x1c]
	str r6, [sp, #0x4]
	sub r4, r1, r0
	ldr r1, [sp, #0x6c]
	str r5, [sp, #0x8]
	str r1, [sp, #0xc]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x20]
	add r3, r11, r1, lsl #0x3
	mov r0, r7
	mov r1, r4
	bl FUN_020B5E50
	ldr r1, [sp, #0x24]
	add r7, r7, r0, lsl #0x3
	mul r2, r1, r4
	ldr r1, [sp, #0x20]
	mul r2, r1, r2
	ldr r1, [sp, #0x6c]
	add r5, r5, r2, lsr r1
	ldr r1, [sp, #0x28]
	add r0, r1, r0
	str r0, [sp, #0x28]
_020B6078:
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bhs _020B60F0
	ldr r1, [sp, #0x60]
	ldr r0, [sp, #0x20]
	mov r3, r11
	add r0, r1, r0, lsl #0x3
	str r0, [sp, #0x0]
	str r6, [sp, #0x4]
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x20]
	str r5, [sp, #0x8]
	sub r4, r1, r0
	ldr r1, [sp, #0x6c]
	mov r0, r7
	str r1, [sp, #0xc]
	ldr r1, [sp, #0x1c]
	mov r2, r4
	bl FUN_020B5E50
	ldr r2, [sp, #0x24]
	ldr r1, [sp, #0x1c]
	add r7, r7, r0, lsl #0x3
	mul r1, r2, r1
	mul r2, r4, r1
	ldr r1, [sp, #0x6c]
	add r5, r5, r2, lsr r1
	ldr r1, [sp, #0x28]
	add r0, r1, r0
	str r0, [sp, #0x28]
_020B60F0:
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x10]
	cmp r1, r0
	bhs _020B6164
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bhs _020B6164
	ldr r1, [sp, #0x60]
	ldr r0, [sp, #0x20]
	ldr r2, [sp, #0x10]
	add r0, r1, r0, lsl #0x3
	ldr r1, [sp, #0x1c]
	ldr r3, [sp, #0x14]
	str r0, [sp, #0x0]
	sub r1, r2, r1
	ldr r2, [sp, #0x20]
	str r6, [sp, #0x4]
	sub r2, r3, r2
	ldr r3, [sp, #0x1c]
	ldr r4, [sp, #0x6c]
	str r5, [sp, #0x8]
	mov r0, r7
	add r3, r11, r3, lsl #0x3
	str r4, [sp, #0xc]
	bl FUN_020B5E50
	ldr r1, [sp, #0x28]
	add r0, r1, r0
	str r0, [sp, #0x28]
_020B6164:
	ldr r0, [sp, #0x28]
	add sp, sp, #0x3c
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B6170: .word UNK_020FF970
_020B6174: .word 0x000001FF
_020B6178: .word 0xFE00FF00
_020B617C: .word 0x3FFF3FFF
	arm_func_end FUN_020B5E50

	; _end
	arm_func_start FUN_020B6180
FUN_020B6180: ; 0x020B6180
	stmdb sp!, {r4-r6,lr}
	mov r3, r0, lsr #0x3
	mov r6, r1, lsr #0x3
	mul r12, r3, r6
	and r2, r0, #0x4
	and lr, r0, #0x2
	and r0, r0, #0x1
	add r4, r0, lr, lsr #0x1
	mov r5, r2, lsr #0x2
	and r0, r1, #0x4
	add lr, r12, #0x0
	add r12, r5, r4, lsl #0x1
	mla r12, r6, r12, lr
	and lr, r1, #0x2
	and r1, r1, #0x1
	add lr, r1, lr, lsr #0x1
	mov r1, r0, lsr #0x2
	add r1, r1, lr, lsl #0x1
	mla r12, r3, r1, r12
	add r1, r4, r2, lsr #0x2
	add r0, lr, r0, lsr #0x2
	mla r0, r1, r0, r12
	ldmia sp!, {r4-r6,pc}
	arm_func_end FUN_020B6180

	; _end
	arm_func_start FUN_020B61DC
FUN_020B61DC: ; 0x020B61DC
	stmdb sp!, {r4-r8,lr}
	ldr r12, [sp, #0x1c]
	ldr r8, [sp, #0x18]
	mov r12, r12, lsl #0x1c
	mov r4, r12, lsr #0x10
	mov r6, #0x0
	cmp r2, #0x0
	ldmleia sp!, {r4-r8,pc}
	mov lr, r3, lsl #0x1
	mov r12, r6
_020B6204:
	mov r5, r0
	mov r7, r12
	cmp r1, #0x0
	ble _020B622C
_020B6214:
	orr r3, r4, r8
	add r7, r7, #0x1
	cmp r7, r1
	add r8, r8, #0x1
	strh r3, [r5], #0x2
	blt _020B6214
_020B622C:
	add r6, r6, #0x1
	cmp r6, r2
	add r0, r0, lr
	blt _020B6204
	ldmia sp!, {r4-r8,pc}
	arm_func_end FUN_020B61DC

	; _end
	arm_func_start FUN_020B6240
FUN_020B6240: ; 0x020B6240
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	ldr r5, [sp, #0x24]
	ldr lr, [sp, #0x20]
	cmp r5, #0x20
	ldr r12, [sp, #0x28]
	bgt _020B6280
	mla r4, r5, lr, r3
	ldr lr, [sp, #0x2c]
	str r12, [sp, #0x0]
	mov r3, r5
	add r0, r0, r4, lsl #0x1
	str lr, [sp, #0x4]
	bl FUN_020B61DC
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,pc}
_020B6280:
	ldr r4, [sp, #0x2c]
	add r7, lr, r2
	mov r2, r4, lsl #0x1c
	cmp lr, r7
	add r8, r3, r1
	mov r4, r2, lsr #0x10
	addge sp, sp, #0x8
	ldmgeia sp!, {r4-r8,pc}
_020B62A0:
	cmp lr, #0x20
	movlt r1, lr
	addge r1, lr, #0x20
	mov r6, r3
	cmp r3, r8
	add r5, r0, r1, lsl #0x6
	bge _020B62E4
_020B62BC:
	cmp r6, #0x20
	movlt r1, r6
	addge r1, r6, #0x3e0
	orr r2, r4, r12
	mov r1, r1, lsl #0x1
	add r6, r6, #0x1
	strh r2, [r5, r1]
	cmp r6, r8
	add r12, r12, #0x1
	blt _020B62BC
_020B62E4:
	add lr, lr, #0x1
	cmp lr, r7
	blt _020B62A0
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,pc}
	arm_func_end FUN_020B6240

	; NNS_G2dCharCanvasInitForOBJ1D
	arm_func_start FUN_020B62F8
FUN_020B62F8: ; 0x020B62F8
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x18
	cmp r2, #0x8
	movlt r4, r2
	movge r12, #0x3
	clzlt r4, r4
	rsblt r12, r4, #0x1f
	cmp r3, #0x8
	movlt r4, r3
	movge r6, #0x3
	clzlt r4, r4
	rsblt r6, r4, #0x1f
	ldr r4, _020B6378 ; =UNK_020FF970
	ldr r5, [sp, #0x28]
	add r4, r4, r6, lsl #0x3
	ldrb r6, [r4, r12, lsl #0x1]
	add r12, r4, r12, lsl #0x1
	ldr r4, _020B637C ; =FUN_020B6908
	strb r6, [sp, #0x14]
	ldrb r6, [r12, #0x1]
	ldr lr, _020B6380 ; =FUN_020B68AC
	ldr ip, _020B6384 ; =FUN_020B64C0
	strb r6, [sp, #0x15]
	str r5, [sp, #0x0]
	str r4, [sp, #0x4]
	str lr, [sp, #0x8]
	str r12, [sp, #0xc]
	ldr r12, [sp, #0x14]
	str r12, [sp, #0x10]
	bl FUN_020B6488
	add sp, sp, #0x18
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B6378: .word UNK_020FF970
_020B637C: .word FUN_020B6908
_020B6380: .word FUN_020B68AC
_020B6384: .word FUN_020B64C0
	arm_func_end FUN_020B62F8

	; NNS_G2dCharCanvasInitForBG
	arm_func_start FUN_020B6388
FUN_020B6388: ; 0x020B6388
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	ldr lr, [sp, #0x18]
	ldr ip, _020B63C0 ; =FUN_020B6B10
	str lr, [sp, #0x0]
	ldr lr, _020B63C4 ; =FUN_020B68AC
	str r12, [sp, #0x4]
	ldr ip, _020B63C8 ; =FUN_020B66D4
	str lr, [sp, #0x8]
	str r12, [sp, #0xc]
	str r2, [sp, #0x10]
	bl FUN_020B6488
	add sp, sp, #0x14
	ldmia sp!, {pc}
	.balign 4
_020B63C0: .word FUN_020B6B10
_020B63C4: .word FUN_020B68AC
_020B63C8: .word FUN_020B66D4
	arm_func_end FUN_020B6388

	; NNS_G2dCharCanvasDrawChar
	arm_func_start FUN_020B63CC
FUN_020B63CC: ; 0x020B63CC
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	mov r7, r1
	ldrh r1, [sp, #0x2c]
	mov r8, r0
	mov r0, r7
	mov r6, r2
	mov r5, r3
	bl FUN_020B5CE4
	ldr r1, _020B6484 ; =0x0000FFFF
	mov r4, r0
	cmp r4, r1
	ldreq r0, [r7, #0x0]
	ldreqh r4, [r0, #0x2]
	mov r0, r7
	mov r1, r4
	bl FUN_020B5C88
	str r0, [sp, #0x8]
	ldr r0, [r7, #0x0]
	ldr r2, [sp, #0x28]
	ldr r0, [r0, #0x8]
	add r1, sp, #0x8
	ldrh r3, [r0, #0x2]
	add r12, r0, #0x8
	mov r0, r8
	mla r3, r4, r3, r12
	str r3, [sp, #0xc]
	str r2, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x8]
	ldr r4, [r8, #0x14]
	ldrsb r2, [r1, #0x0]
	mov r1, r7
	mov r3, r5
	add r2, r6, r2
	blx r4
	ldrh r0, [r7, #0x8]
	cmp r0, #0x0
	ldrne r0, [sp, #0x8]
	ldrnesb r1, [r0, #0x0]
	ldrneb r0, [r0, #0x1]
	addne r0, r1, r0
	ldreq r0, [sp, #0x8]
	ldreqsb r0, [r0, #0x2]
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020B6484: .word 0x0000FFFF
	arm_func_end FUN_020B63CC

	; _end
	arm_func_start FUN_020B6488
FUN_020B6488: ; 0x020B6488
	str r2, [r0, #0x4]
	ldr r2, [sp, #0x0]
	str r3, [r0, #0x8]
	strb r2, [r0, #0xc]
	ldr r2, [sp, #0x4]
	str r1, [r0, #0x0]
	ldr r1, [sp, #0x8]
	str r2, [r0, #0x14]
	ldr r2, [sp, #0xc]
	str r1, [r0, #0x18]
	ldr r1, [sp, #0x10]
	str r2, [r0, #0x1c]
	str r1, [r0, #0x10]
	bx lr
	arm_func_end FUN_020B6488

	; _end
	arm_func_start FUN_020B64C0
FUN_020B64C0: ; 0x020B64C0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x54
	ldrb r4, [r0, #0xc]
	mov r10, r2
	str r1, [sp, #0xc]
	str r4, [sp, #0x44]
	ldr r1, [sp, #0x44]
	ldr r4, [sp, #0x78]
	cmp r1, #0x4
	add r1, r10, r4
	str r1, [sp, #0x1c]
	ldr r2, [sp, #0x7c]
	mov r1, r3
	add r1, r1, r2
	str r1, [sp, #0x20]
	ldrne r1, [sp, #0xc]
	str r3, [sp, #0x10]
	orrne r1, r1, r1, lsl #0x8
	orrne r1, r1, r1, lsl #0x10
	strne r1, [sp, #0xc]
	bne _020B6528
	ldr r1, [sp, #0xc]
	orr r1, r1, r1, lsl #0x4
	orr r1, r1, r1, lsl #0x8
	orr r1, r1, r1, lsl #0x10
	str r1, [sp, #0xc]
_020B6528:
	bic r1, r10, #0x7
	str r1, [sp, #0x30]
	ldr r1, [sp, #0x10]
	ldr r2, [r0, #0x10]
	bic r1, r1, #0x7
	str r1, [sp, #0x14]
	ldr r1, [sp, #0x44]
	str r2, [sp, #0x4c]
	mov r3, r1, lsl #0x6
	mov r2, r3, asr #0x2
	ldr r1, [sp, #0x20]
	add r3, r3, r2, lsr #0x1d
	ldr r2, [sp, #0x1c]
	add r6, r1, #0x7
	add r2, r2, #0x7
	bic r5, r2, #0x7
	bic r2, r6, #0x7
	ldr r1, [sp, #0x30]
	str r2, [sp, #0x24]
	mov r2, r3, asr #0x3
	str r2, [sp, #0x48]
	mov r4, r1, asr #0x2
	ldr r2, [sp, #0x30]
	ldr r1, [sp, #0x14]
	add r2, r2, r4, lsr #0x1d
	mov r2, r2, asr #0x3
	str r2, [sp, #0x2c]
	ldr r2, [sp, #0x14]
	mov r1, r1, asr #0x2
	add r1, r2, r1, lsr #0x1d
	mov r6, r1, asr #0x3
	ldr r1, [sp, #0x24]
	cmp r2, r1
	ldr r1, [r0, #0x4]
	str r1, [sp, #0x40]
	ldr r1, [r0, #0x8]
	ldr r0, [r0, #0x0]
	str r1, [sp, #0x3c]
	str r0, [sp, #0x28]
	ldrb r0, [sp, #0x4c]
	str r0, [sp, #0x38]
	ldrb r0, [sp, #0x4d]
	str r0, [sp, #0x34]
	addge sp, sp, #0x54
	ldmgeia sp!, {r4-r11,pc}
	mov r4, #0x0
	mov r11, #0x8
_020B65E4:
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x10]
	ldr r7, [sp, #0x2c]
	cmp r1, r0
	movlt r1, r0
	ldrlt r0, [sp, #0x14]
	sublt r9, r1, r0
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #0x14]
	movge r9, r4
	sub r0, r1, r0
	cmp r0, #0x8
	movgt r0, r11
	sub r0, r0, r9
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x30]
	cmp r0, r5
	mov r8, r0
	bge _020B66B0
_020B6630:
	ldr r0, [sp, #0x38]
	ldr r2, [sp, #0x40]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x34]
	ldr r3, [sp, #0x3c]
	str r0, [sp, #0x4]
	mov r0, r7
	mov r1, r6
	bl FUN_020B7068
	ldr r2, [sp, #0x1c]
	cmp r8, r10
	sublt r1, r10, r8
	sub r2, r2, r8
	movge r1, r4
	cmp r2, #0x8
	movgt r2, r11
	sub r3, r2, r1
	ldr r2, [sp, #0x18]
	ldr r12, [sp, #0x48]
	str r2, [sp, #0x0]
	ldr r2, [sp, #0xc]
	str r2, [sp, #0x4]
	ldr r2, [sp, #0x44]
	str r2, [sp, #0x8]
	ldr r2, [sp, #0x28]
	mla r0, r12, r0, r2
	mov r2, r9
	bl FUN_020B6F18
	add r8, r8, #0x8
	add r7, r7, #0x1
	cmp r8, r5
	blt _020B6630
_020B66B0:
	ldr r0, [sp, #0x14]
	add r6, r6, #0x1
	add r1, r0, #0x8
	ldr r0, [sp, #0x24]
	str r1, [sp, #0x14]
	cmp r1, r0
	blt _020B65E4
	add sp, sp, #0x54
	ldmia sp!, {r4-r11,pc}
	arm_func_end FUN_020B64C0

	; _end
	arm_func_start FUN_020B66D4
FUN_020B66D4: ; 0x020B66D4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x3c
	ldrb r4, [r0, #0xc]
	mov r10, r2
	str r1, [sp, #0xc]
	str r4, [sp, #0x2c]
	ldr r1, [sp, #0x2c]
	ldr r4, [sp, #0x60]
	cmp r1, #0x4
	add r1, r10, r4
	str r1, [sp, #0x18]
	ldr r2, [sp, #0x64]
	mov r1, r3
	add r1, r1, r2
	str r1, [sp, #0x1c]
	ldrne r1, [sp, #0xc]
	str r3, [sp, #0x10]
	orrne r1, r1, r1, lsl #0x8
	orrne r1, r1, r1, lsl #0x10
	strne r1, [sp, #0xc]
	bne _020B673C
	ldr r1, [sp, #0xc]
	orr r1, r1, r1, lsl #0x4
	orr r1, r1, r1, lsl #0x8
	orr r1, r1, r1, lsl #0x10
	str r1, [sp, #0xc]
_020B673C:
	ldr r1, [sp, #0x10]
	bic r1, r1, #0x7
	mov r2, r1, asr #0x2
	str r1, [sp, #0x14]
	add r1, r1, r2, lsr #0x1d
	ldr r2, [r0, #0x10]
	mov r3, r1, asr #0x3
	mul r1, r3, r2
	bic r3, r10, #0x7
	str r3, [sp, #0x28]
	ldr r3, [sp, #0x2c]
	mov r6, r3, lsl #0x6
	ldr r3, [sp, #0x28]
	mov r4, r6, asr #0x2
	mov r5, r3, asr #0x2
	add r5, r3, r5, lsr #0x1d
	add r4, r6, r4, lsr #0x1d
	mov r3, r4, asr #0x3
	str r3, [sp, #0x30]
	ldr r3, [sp, #0x1c]
	add r1, r1, r5, asr #0x3
	add r4, r3, #0x7
	ldr r3, [r0, #0x0]
	ldr r0, [sp, #0x18]
	add r5, r0, #0x7
	ldr r0, [sp, #0x30]
	bic r7, r5, #0x7
	mla r1, r0, r1, r3
	bic r0, r4, #0x7
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x30]
	str r1, [sp, #0x24]
	mul r0, r2, r0
	str r0, [sp, #0x34]
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x20]
	cmp r1, r0
	addge sp, sp, #0x3c
	ldmgeia sp!, {r4-r11,pc}
	mov r5, #0x0
	mov r4, #0x8
_020B67E0:
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x10]
	ldr r6, [sp, #0x24]
	cmp r1, r0
	movlt r1, r0
	ldrlt r0, [sp, #0x14]
	sublt r9, r1, r0
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x14]
	movge r9, r5
	sub r0, r1, r0
	cmp r0, #0x8
	movgt r0, r4
	sub r11, r0, r9
	ldr r0, [sp, #0x28]
	cmp r0, r7
	mov r8, r0
	bge _020B687C
_020B6828:
	ldr r0, [sp, #0x18]
	cmp r8, r10
	sublt r1, r10, r8
	sub r0, r0, r8
	movge r1, r5
	cmp r0, #0x8
	movgt r0, r4
	sub r3, r0, r1
	ldr r0, [sp, #0xc]
	str r11, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x2c]
	mov r2, r9
	str r0, [sp, #0x8]
	mov r0, r6
	bl FUN_020B6F18
	ldr r0, [sp, #0x30]
	add r8, r8, #0x8
	add r6, r6, r0
	cmp r8, r7
	blt _020B6828
_020B687C:
	ldr r1, [sp, #0x24]
	ldr r0, [sp, #0x34]
	add r0, r1, r0
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x14]
	add r1, r0, #0x8
	ldr r0, [sp, #0x20]
	str r1, [sp, #0x14]
	cmp r1, r0
	blt _020B67E0
	add sp, sp, #0x3c
	ldmia sp!, {r4-r11,pc}
	arm_func_end FUN_020B66D4

	; _end
	arm_func_start FUN_020B68AC
FUN_020B68AC: ; 0x020B68AC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r3, r0
	ldrb r2, [r3, #0xc]
	ldr r12, [r3, #0x4]
	cmp r2, #0x4
	orreq r0, r1, r1, lsl #0x4
	orreq r0, r0, r0, lsl #0x8
	orreq r1, r0, r0, lsl #0x10
	orrne r0, r1, r1, lsl #0x8
	orrne r1, r0, r0, lsl #0x10
	ldr r0, [r3, #0x8]
	mov r2, r2, lsl #0x6
	mul lr, r12, r0
	mov r0, r2, asr #0x2
	add r0, r2, r0, lsr #0x1d
	mov r2, r0, asr #0x3
	mov r0, r1
	mul r2, lr, r2
	ldr r1, [r3, #0x0]
	bl MIi_CpuClearFast
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end FUN_020B68AC

	; _end
	arm_func_start FUN_020B6908
FUN_020B6908: ; 0x020B6908
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4c
	ldr r7, [sp, #0x74]
	ldrb r5, [r0, #0xc]
	ldr r6, [r1, #0x0]
	ldr r4, [r7, #0x0]
	ldr r9, [r6, #0x8]
	mov r8, r5, lsl #0x6
	ldrb r4, [r4, #0x1]
	mov r5, r8, asr #0x2
	add r5, r8, r5, lsr #0x1d
	ldrb r9, [r9, #0x1]
	ldr r8, [r0, #0x4]
	ldr r6, [r0, #0x8]
	str r2, [sp, #0x8]
	str r3, [sp, #0xc]
	cmp r4, #0x0
	mov r5, r5, asr #0x3
	addeq sp, sp, #0x4c
	ldmeqia sp!, {r4-r11,pc}
	adds r3, r2, r4
	addmi sp, sp, #0x4c
	ldmmiia sp!, {r4-r11,pc}
	ldr r2, [sp, #0xc]
	adds r2, r2, r9
	addmi sp, sp, #0x4c
	ldmmiia sp!, {r4-r11,pc}
	ldr r10, [sp, #0x8]
	add r3, r3, #0x7
	cmp r10, #0x0
	movle r10, #0x0
	strle r10, [sp, #0x10]
	movgt r10, r10, lsr #0x3
	strgt r10, [sp, #0x10]
	ldr r10, [sp, #0xc]
	add r2, r2, #0x7
	cmp r10, #0x0
	movle r10, #0x0
	mov r11, r2, lsr #0x3
	mov r3, r3, lsr #0x3
	movgt r10, r10, lsr #0x3
	cmp r3, r8
	movcs r3, r8
	cmp r11, r6
	ldr r2, [sp, #0x10]
	movcs r11, r6
	subs r8, r3, r2
	addmi sp, sp, #0x4c
	sub r3, r11, r10
	ldmmiia sp!, {r4-r11,pc}
	cmp r3, #0x0
	addlt sp, sp, #0x4c
	ldmltia sp!, {r4-r11,pc}
	ldr r2, [sp, #0x8]
	ldr r6, [r0, #0x0]
	cmp r2, #0x0
	andge r2, r2, #0x7
	strge r2, [sp, #0x8]
	ldr r2, [sp, #0xc]
	ldr r11, [sp, #0x8]
	cmp r2, #0x0
	andge r2, r2, #0x7
	strge r2, [sp, #0xc]
	sub r8, r11, r8, lsl #0x3
	ldr r11, [sp, #0xc]
	ldr r2, [sp, #0x70]
	sub r3, r11, r3, lsl #0x3
	str r3, [sp, #0x14]
	ldr r3, [r7, #0x4]
	sub r2, r2, #0x1
	str r3, [sp, #0x28]
	str r2, [sp, #0x48]
	str r9, [sp, #0x38]
	str r4, [sp, #0x34]
	ldr r4, [r1, #0x0]
	ldr r2, [sp, #0x14]
	mov r3, r11
	cmp r3, r2
	ldr r2, [r4, #0x8]
	ldrb r3, [r2, #0x6]
	str r3, [sp, #0x40]
	ldrb r2, [r0, #0xc]
	str r2, [sp, #0x44]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x8]
	ldrb r1, [r1, #0x0]
	mul r1, r3, r1
	str r1, [sp, #0x3c]
	ldr r1, [r0, #0x10]
	str r1, [sp, #0x20]
	ldr r1, [r0, #0x4]
	ldr r0, [r0, #0x8]
	ldrb r11, [sp, #0x20]
	ldrb r4, [sp, #0x21]
	str r1, [sp, #0x1c]
	str r0, [sp, #0x18]
	addle sp, sp, #0x4c
	ldmleia sp!, {r4-r11,pc}
_020B6A90:
	ldr r0, [sp, #0xc]
	ldr r7, [sp, #0x10]
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x8]
	cmp r0, r8
	mov r9, r0
	ble _020B6AEC
_020B6AAC:
	ldr r2, [sp, #0x1c]
	str r11, [sp, #0x0]
	ldr r3, [sp, #0x18]
	mov r0, r7
	mov r1, r10
	str r4, [sp, #0x4]
	bl FUN_020B7068
	mla r1, r0, r5, r6
	add r0, sp, #0x24
	str r9, [sp, #0x2c]
	str r1, [sp, #0x24]
	bl FUN_020B6CAC
	sub r9, r9, #0x8
	add r7, r7, #0x1
	cmp r9, r8
	bgt _020B6AAC
_020B6AEC:
	ldr r0, [sp, #0xc]
	add r10, r10, #0x1
	sub r1, r0, #0x8
	ldr r0, [sp, #0x14]
	str r1, [sp, #0xc]
	cmp r1, r0
	bgt _020B6A90
	add sp, sp, #0x4c
	ldmia sp!, {r4-r11,pc}
	arm_func_end FUN_020B6908

	; _end
	arm_func_start FUN_020B6B10
FUN_020B6B10: ; 0x020B6B10
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x2c
	ldr r4, [sp, #0x54]
	ldrb r5, [r0, #0xc]
	str r4, [sp, #0x54]
	ldr r4, [r4, #0x0]
	ldr r6, [r1, #0x0]
	mov r7, r5, lsl #0x6
	ldrb r4, [r4, #0x1]
	mov r5, r7, asr #0x2
	add r5, r7, r5, lsr #0x1d
	cmp r4, #0x0
	ldr r6, [r6, #0x8]
	mov r9, r3
	ldr r8, [r0, #0x4]
	ldr r7, [r0, #0x8]
	mov r10, r2
	mov r5, r5, asr #0x3
	addeq sp, sp, #0x2c
	ldr lr, [r0, #0x0]
	ldrb r3, [r6, #0x1]
	ldmeqia sp!, {r4-r11,pc}
	adds r6, r10, r4
	addmi sp, sp, #0x2c
	ldmmiia sp!, {r4-r11,pc}
	adds r2, r9, r3
	addmi sp, sp, #0x2c
	ldmmiia sp!, {r4-r11,pc}
	cmp r10, #0x0
	movle r11, #0x0
	add r6, r6, #0x7
	movgt r11, r10, lsr #0x3
	cmp r9, #0x0
	movle r12, #0x0
	add r2, r2, #0x7
	mov r6, r6, lsr #0x3
	movgt r12, r9, lsr #0x3
	cmp r6, r8
	movcs r6, r8
	mov r2, r2, lsr #0x3
	cmp r2, r7
	movcs r2, r7
	subs r7, r6, r11
	addmi sp, sp, #0x2c
	sub r2, r2, r12
	ldmmiia sp!, {r4-r11,pc}
	cmp r2, #0x0
	addlt sp, sp, #0x2c
	ldmltia sp!, {r4-r11,pc}
	ldr r6, [r0, #0x10]
	cmp r10, #0x0
	sub r8, r6, r7
	mul r8, r5, r8
	mla r11, r6, r12, r11
	andge r10, r10, #0x7
	str r8, [sp, #0x0]
	ldr r8, [sp, #0x54]
	mla r6, r5, r11, lr
	ldr r12, [r8, #0x4]
	ldr r11, [sp, #0x50]
	cmp r9, #0x0
	sub r8, r11, #0x1
	andge r9, r9, #0x7
	sub r11, r9, r2, lsl #0x3
	str r12, [sp, #0x8]
	str r4, [sp, #0x14]
	str r8, [sp, #0x28]
	str r3, [sp, #0x18]
	ldr r3, [r1, #0x0]
	cmp r9, r11
	ldr r2, [r3, #0x8]
	sub r7, r10, r7, lsl #0x3
	ldrb r2, [r2, #0x6]
	str r2, [sp, #0x20]
	ldrb r0, [r0, #0xc]
	str r0, [sp, #0x24]
	ldr r0, [r1, #0x0]
	ldr r0, [r0, #0x8]
	ldrb r0, [r0, #0x0]
	mul r0, r2, r0
	str r0, [sp, #0x1c]
	addle sp, sp, #0x2c
	ldmleia sp!, {r4-r11,pc}
	add r4, sp, #0x4
_020B6C60:
	mov r8, r10
	str r9, [sp, #0x10]
	cmp r10, r7
	ble _020B6C90
_020B6C70:
	mov r0, r4
	str r6, [sp, #0x4]
	str r8, [sp, #0xc]
	bl FUN_020B6CAC
	sub r8, r8, #0x8
	cmp r8, r7
	add r6, r6, r5
	bgt _020B6C70
_020B6C90:
	ldr r0, [sp, #0x0]
	sub r9, r9, #0x8
	cmp r9, r11
	add r6, r6, r0
	bgt _020B6C60
	add sp, sp, #0x2c
	ldmia sp!, {r4-r11,pc}
	arm_func_end FUN_020B6B10

	; _end
	arm_func_start FUN_020B6CAC
FUN_020B6CAC: ; 0x020B6CAC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x34
	ldr r5, [r0, #0x8]
	ldr r4, [r0, #0xc]
	cmp r5, #0x0
	strge r5, [sp, #0x0]
	movlt r1, #0x0
	strlt r1, [sp, #0x0]
	ldr r1, [r0, #0x10]
	cmp r4, #0x0
	add r10, r5, r1
	ldr r1, [r0, #0x14]
	movge r2, r4
	movlt r2, #0x0
	cmp r10, #0x8
	add r3, r4, r1
	movge r10, #0x8
	cmp r3, #0x8
	movge r3, #0x8
	cmp r4, #0x0
	movgt r4, #0x0
	cmp r5, #0x0
	ldr r8, [r0, #0x20]
	movgt r5, #0x0
	rsb r1, r4, #0x0
	mul r7, r10, r8
	ldr r6, [r0, #0x1c]
	rsb r4, r5, #0x0
	mul r9, r6, r4
	ldr r4, [r0, #0x18]
	mov r10, r7
	str r4, [sp, #0x8]
	ldr r4, [sp, #0x0]
	cmp r8, #0x4
	mul r5, r4, r8
	ldr r4, [sp, #0x8]
	str r5, [sp, #0x0]
	mla r11, r1, r4, r9
	ldr r1, [r0, #0x4]
	str r1, [sp, #0x4]
	bne _020B6E24
	ldr r1, [r0, #0x0]
	ldr r7, [r0, #0x24]
	add r0, r1, r2, lsl #0x2
	str r0, [sp, #0xc]
	add r0, r1, r3, lsl #0x2
	ldr r1, [sp, #0xc]
	str r0, [sp, #0x10]
	cmp r1, r0
	addcs sp, sp, #0x34
	ldmcsia sp!, {r4-r11,pc}
	mov r0, #0x0
	add r9, sp, #0x24
	mov r4, #0xf
	str r0, [sp, #0x1c]
_020B6D88:
	ldr r0, [sp, #0xc]
	mov r1, r11, lsr #0x1f
	ldr r5, [r0, #0x0]
	ldr r0, [sp, #0x4]
	rsb r2, r1, r11, lsl #0x1d
	add r0, r0, r11, lsr #0x3
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x1c]
	add r1, r1, r2, ror #0x1d
	strb r0, [sp, #0x28]
	strb r0, [sp, #0x29]
	mov r0, r9
	bl FUN_020B76B0
	ldr r8, [sp, #0x0]
	mov r0, r8
	cmp r0, r10
	bhs _020B6DF8
_020B6DCC:
	mov r0, r9
	mov r1, r6
	bl FUN_020B76B0
	cmp r0, #0x0
	mvnne r1, r4, lsl r8
	addne r0, r7, r0
	andne r1, r5, r1
	orrne r5, r1, r0, lsl r8
	add r8, r8, #0x4
	cmp r8, r10
	blo _020B6DCC
_020B6DF8:
	ldr r0, [sp, #0xc]
	add r1, r0, #0x4
	str r5, [r0, #0x0]
	ldr r0, [sp, #0x10]
	str r1, [sp, #0xc]
	cmp r1, r0
	ldr r0, [sp, #0x8]
	add r11, r11, r0
	blo _020B6D88
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,pc}
_020B6E24:
	ldr r1, [r0, #0x0]
	ldr r9, [r0, #0x24]
	add r0, r1, r2, lsl #0x3
	str r0, [sp, #0x14]
	add r0, r1, r3, lsl #0x3
	ldr r1, [sp, #0x14]
	str r0, [sp, #0x18]
	cmp r1, r0
	addcs sp, sp, #0x34
	ldmcsia sp!, {r4-r11,pc}
	mov r0, #0x0
	mov r4, #0xff
	str r0, [sp, #0x20]
_020B6E58:
	mov r1, r11, lsr #0x1f
	rsb r0, r1, r11, lsl #0x1d
	add r1, r1, r0, ror #0x1d
	ldr r0, [sp, #0x14]
	ldr r8, [r0, #0x0]
	ldr r7, [r0, #0x4]
	ldr r0, [sp, #0x4]
	add r0, r0, r11, lsr #0x3
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x20]
	strb r0, [sp, #0x30]
	strb r0, [sp, #0x31]
	add r0, sp, #0x2c
	bl FUN_020B76B0
	ldr r0, [sp, #0x0]
	cmp r0, r10
	mov r5, r0
	bhs _020B6EE8
_020B6EA0:
	add r0, sp, #0x2c
	mov r1, r6
	bl FUN_020B76B0
	cmp r0, #0x0
	beq _020B6EDC
	cmp r5, #0x20
	mvncc r1, r4, lsl r5
	addcc r0, r9, r0
	andcc r1, r8, r1
	orrcc r8, r1, r0, lsl r5
	subcs r2, r5, #0x20
	mvncs r1, r4, lsl r2
	addcs r0, r9, r0
	andcs r1, r7, r1
	orrcs r7, r1, r0, lsl r2
_020B6EDC:
	add r5, r5, #0x8
	cmp r5, r10
	blo _020B6EA0
_020B6EE8:
	ldr r0, [sp, #0x14]
	str r8, [r0, #0x0]
	add r1, r0, #0x8
	str r7, [r0, #0x4]
	ldr r0, [sp, #0x18]
	str r1, [sp, #0x14]
	cmp r1, r0
	ldr r0, [sp, #0x8]
	add r11, r11, r0
	blo _020B6E58
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,pc}
	arm_func_end FUN_020B6CAC

	; _end
	arm_func_start FUN_020B6F18
FUN_020B6F18: ; 0x020B6F18
	stmdb sp!, {r4-r6,lr}
	mov lr, r0
	cmp r3, #0x8
	ldr r0, [sp, #0x14]
	bne _020B6F4C
	ldr r4, [sp, #0x10]
	cmp r4, #0x8
	bne _020B6F4C
	ldr r2, [sp, #0x18]
	mov r1, lr
	mov r2, r2, lsl #0x3
	bl MIi_CpuClearFast
	ldmia sp!, {r4-r6,pc}
_020B6F4C:
	ldr r4, [sp, #0x18]
	cmp r4, #0x4
	bne _020B6FAC
	mov r5, r1, lsl #0x2
	add r4, r5, r3, lsl #0x2
	mvn r3, #0x0
	rsb r4, r4, #0x20
	mov r3, r3, lsr r5
	add r1, r4, r1, lsl #0x2
	mov r3, r3, lsl r1
	ldr r1, [sp, #0x10]
	add r5, lr, r2, lsl #0x2
	add r2, r5, r1, lsl #0x2
	and r6, r0, r3, lsr r4
	cmp r5, r2
	mvn r1, r3, lsr r4
	ldmcsia sp!, {r4-r6,pc}
_020B6F90:
	ldr r0, [r5, #0x0]
	and r0, r0, r1
	orr r0, r6, r0
	str r0, [r5], #0x4
	cmp r5, r2
	blo _020B6F90
	ldmia sp!, {r4-r6,pc}
_020B6FAC:
	mov r12, r1, lsl #0x3
	add r1, r12, r3, lsl #0x3
	rsb r1, r1, #0x40
	mvn r3, #0x0
	cmp r1, #0x20
	mov r5, r3, lsr r12
	subcs r4, r1, #0x20
	addcs r3, r12, r4
	movcs r3, r5, lsl r3
	movcs r3, r3, lsr r4
	movcc r3, r5, lsl r12
	mvn r4, #0x0
	add r5, lr, r2, lsl #0x3
	cmp r12, #0x20
	mov r4, r4, lsl r1
	subcs r12, r12, #0x20
	addcs r1, r12, r1
	movcs r1, r4, lsr r1
	movcs r6, r1, lsl r12
	movcc r6, r4, lsr r1
	ldr r1, [sp, #0x10]
	and lr, r0, r3
	add r4, r5, r1, lsl #0x3
	cmp r5, r4
	and r12, r0, r6
	mvn r2, r3
	mvn r1, r6
	ldmcsia sp!, {r4-r6,pc}
_020B701C:
	ldr r0, [r5, #0x0]
	and r0, r0, r2
	orr r0, lr, r0
	str r0, [r5, #0x0]
	ldr r0, [r5, #0x4]
	and r0, r0, r1
	orr r0, r12, r0
	str r0, [r5, #0x4]
	add r5, r5, #0x8
	cmp r5, r4
	blo _020B701C
	ldmia sp!, {r4-r6,pc}
	arm_func_end FUN_020B6F18

	; OBJSizeToShape
	arm_func_start FUN_020B704C
FUN_020B704C: ; 0x020B704C
	ldrb r3, [r0, #0x1]
	ldr r2, _020B7064 ; =UNK_020FF990
	ldrb r1, [r0, #0x0]
	add r0, r2, r3, lsl #0x4
	ldr r0, [r0, r1, lsl #0x2]
	bx lr
	.balign 4
_020B7064: .word UNK_020FF990
	arm_func_end FUN_020B704C

	; GetCharIndex1D
	arm_func_start FUN_020B7068
FUN_020B7068: ; 0x020B7068
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr fp, _020B7164 ; =UNK_020FF970
	mov r9, #0x0
	mov r10, #0x3
	mvn r7, #0x0
_020B7080:
	ldr r4, [sp, #0x2c]
	ldr r6, [sp, #0x28]
	and r12, r3, r7, lsl r4
	cmp r12, r1
	mov r8, r7, lsl r6
	mov r5, r7, lsl r4
	and lr, r2, r7, lsl r6
	bhi _020B70D0
	mla r9, r2, r12, r9
	cmp lr, r0
	movhi r2, lr
	subhi r1, r1, r12
	subhi r3, r3, r12
	bhi _020B7118
	sub r3, r3, r12
	mla r9, lr, r3, r9
	sub r0, r0, lr
	sub r1, r1, r12
	sub r2, r2, lr
	b _020B7118
_020B70D0:
	cmp lr, r0
	mlals r9, lr, r12, r9
	mvn r3, r5
	movls r3, r12
	subls r0, r0, lr
	subls r2, r2, lr
	bls _020B7118
	and r2, r1, r5
	mla r5, lr, r2, r9
	and r2, r0, r8
	and r1, r1, r3
	add r2, r5, r2, lsl r4
	mvn r3, r8
	add r1, r2, r1, lsl r6
	and r0, r0, r3
	add sp, sp, #0x4
	add r0, r1, r0
	ldmia sp!, {r4-r11,pc}
_020B7118:
	cmp r2, #0x8
	movlt r4, r2
	movge r5, r10
	clzlt r4, r4
	rsblt r5, r4, #0x1f
	cmp r3, #0x8
	movge r4, r10
	movlt r4, r3
	clzlt r4, r4
	rsblt r4, r4, #0x1f
	add r4, r11, r4, lsl #0x3
	add r6, r4, r5, lsl #0x1
	ldrb r5, [r4, r5, lsl #0x1]
	ldrb r4, [r6, #0x1]
	str r5, [sp, #0x28]
	str r4, [sp, #0x2c]
	b _020B7080
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B7164: .word UNK_020FF970
	arm_func_end FUN_020B7068

