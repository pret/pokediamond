	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; _end
	arm_func_start FUN_020BDF38
FUN_020BDF38: ; 0x020BDF38
	stmdb sp!, {r4,lr}
	ldr r12, [r1, #0x0]
	mov r4, r0
	mov r2, r2, lsl #0x10
	ldr r0, [r1, #0x8]
	mov r1, r2, lsr #0x10
	mov r3, r4
	mov r2, r12, asr #0xc
	bl FUN_020BE030
	ldr r0, [r4, #0x10]
	bic r0, r0, #0xc0000000
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x10]
	orr r0, r0, #0x40000000
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x0]
	orr r0, r0, #0x8
	str r0, [r4, #0x0]
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020BDF38

	; NNSi_G3dAnmObjInitNsBta
	arm_func_start FUN_020BDF84
FUN_020BDF84: ; 0x020BDF84
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r3, _020BE02C ; =UNK_021065A0
	ldr r4, [r2, #0x8]
	ldr r3, [r3, #0x0]
	mov r9, r0
	str r3, [r9, #0xc]
	ldrb r0, [r2, #0x18]
	mov r8, r1
	add r4, r2, r4
	strb r0, [r9, #0x19]
	ldrb r2, [r9, #0x19]
	add r1, r9, #0x1a
	mov r0, #0x0
	mov r2, r2, lsl #0x1
	bl MIi_CpuClear16
	ldrb r0, [r8, #0x9]
	mov r7, #0x0
	cmp r0, #0x0
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r9,pc}
	mov r6, r7
	add r5, r8, #0x8
	add r4, r4, #0x4
_020BDFE4:
	ldrh r1, [r8, #0xe]
	mov r0, r4
	add r2, r5, r1
	ldrh r1, [r2, #0x2]
	add r1, r2, r1
	add r1, r1, r6
	bl FUN_020BC14C
	cmp r0, #0x0
	orrge r1, r7, #0x100
	addge r0, r9, r0, lsl #0x1
	strgeh r1, [r0, #0x1a]
	ldrb r0, [r8, #0x9]
	add r7, r7, #0x1
	add r6, r6, #0x10
	cmp r7, r0
	blo _020BDFE4
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020BE02C: .word UNK_021065A0
	arm_func_end FUN_020BDF84

	; _end
	arm_func_start FUN_020BE030
FUN_020BE030: ; 0x020BE030
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r8, r0
	ldrh r4, [r8, #0xe]
	add r5, r8, #0x8
	mov r6, r3
	ldrh r3, [r5, r4]
	add r4, r5, r4
	add r4, r4, #0x4
	mla r5, r3, r1, r4
	mov r7, r2
	ldr r1, [r5, #0x18]
	ldr r2, [r5, #0x1c]
	mov r3, r7
	ldr r4, [r6, #0x0]
	bl FUN_020BE238
	mov r9, r0
	ldr r1, [r5, #0x20]
	mov r0, r8
	ldr r2, [r5, #0x24]
	mov r3, r7
	bl FUN_020BE238
	cmp r9, #0x0
	bne _020BE09C
	cmp r0, #0x0
	orreq r4, r4, #0x4
	beq _020BE0A8
_020BE09C:
	str r9, [r6, #0x24]
	str r0, [r6, #0x28]
	bic r4, r4, #0x4
_020BE0A8:
	ldr r1, [r5, #0x10]
	ldr r2, [r5, #0x14]
	mov r0, r8
	mov r3, r7
	bl FUN_020BE12C
	cmp r0, #0x10000000
	strneh r0, [r6, #0x20]
	movne r0, r0, lsr #0x10
	strneh r0, [r6, #0x22]
	orreq r4, r4, #0x2
	ldr r1, [r5, #0x0]
	ldr r2, [r5, #0x4]
	mov r0, r8
	mov r3, r7
	bicne r4, r4, #0x2
	bl FUN_020BE238
	mov r9, r0
	ldr r1, [r5, #0x8]
	ldr r2, [r5, #0xc]
	mov r0, r8
	mov r3, r7
	bl FUN_020BE238
	cmp r9, #0x1000
	bne _020BE114
	cmp r0, #0x1000
	orreq r4, r4, #0x1
	beq _020BE120
_020BE114:
	str r9, [r6, #0x18]
	str r0, [r6, #0x1c]
	bic r4, r4, #0x1
_020BE120:
	str r4, [r6, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	arm_func_end FUN_020BE030

	; GetTexSRTAnmSinCosVal_
	arm_func_start FUN_020BE12C
FUN_020BE12C: ; 0x020BE12C
	ands r12, r1, #0x20000000
	movne r0, r2
	bxne lr
	add r0, r0, r2
	ands r2, r1, #0xc0000000
	beq _020BE1F8
	ldr r2, _020BE234 ; =0x0000FFFF
	ands r12, r1, #0x40000000
	and r2, r1, r2
	beq _020BE17C
	ands r1, r3, #0x1
	beq _020BE174
	cmp r3, r2
	movhi r1, r2, lsr #0x1
	addhi r3, r1, #0x1
	bhi _020BE1F8
	mov r2, r3, lsr #0x1
	b _020BE200
_020BE174:
	mov r3, r3, lsr #0x1
	b _020BE1F8
_020BE17C:
	ands r1, r3, #0x3
	beq _020BE1F4
	cmp r3, r2
	addhi r3, r1, r2, lsr #0x2
	bhi _020BE1F8
	ands r1, r3, #0x1
	beq _020BE1EC
	ands r1, r3, #0x2
	movne r1, r3, lsr #0x2
	addne r2, r1, #0x1
	moveq r2, r3, lsr #0x2
	addeq r1, r2, #0x1
	mov r12, r2, lsl #0x2
	add r3, r0, r2, lsl #0x2
	mov r2, r1, lsl #0x2
	add r1, r0, r1, lsl #0x2
	ldrsh r12, [r0, r12]
	ldrsh r2, [r0, r2]
	mov r0, #0x3
	ldrsh r3, [r3, #0x2]
	ldrsh r1, [r1, #0x2]
	mla r2, r12, r0, r2
	mla r1, r3, r0, r1
	ldr r0, _020BE234 ; =0x0000FFFF
	mov r1, r1, asr #0x2
	and r0, r0, r2, asr #0x2
	orr r0, r0, r1, lsl #0x10
	bx lr
_020BE1EC:
	mov r2, r3, lsr #0x2
	b _020BE200
_020BE1F4:
	mov r3, r3, lsr #0x2
_020BE1F8:
	ldr r0, [r0, r3, lsl #0x2]
	bx lr
_020BE200:
	add r1, r0, r2, lsl #0x2
	mov r2, r2, lsl #0x2
	ldrsh r12, [r0, r2]
	ldrsh r3, [r1, #0x4]
	ldrsh r2, [r1, #0x2]
	ldrsh r1, [r1, #0x6]
	ldr r0, _020BE234 ; =0x0000FFFF
	add r3, r12, r3
	add r1, r2, r1
	and r2, r0, r3, asr #0x1
	mov r0, r1, asr #0x1
	orr r0, r2, r0, lsl #0x10
	bx lr
	.balign 4
_020BE234: .word 0x0000FFFF
	arm_func_end FUN_020BE12C

	; GetTexSRTAnmVectorVal_
	arm_func_start FUN_020BE238
FUN_020BE238: ; 0x020BE238
	ands r12, r1, #0x20000000
	movne r0, r2
	bxne lr
	add r0, r0, r2
	ands r2, r1, #0xc0000000
	beq _020BE2F0
	ldr r2, _020BE330 ; =0x0000FFFF
	ands r12, r1, #0x40000000
	and r12, r1, r2
	beq _020BE288
	ands r2, r3, #0x1
	beq _020BE280
	cmp r3, r12
	movhi r2, r12, lsr #0x1
	addhi r3, r2, #0x1
	bhi _020BE2F0
	mov r3, r3, lsr #0x1
	b _020BE304
_020BE280:
	mov r3, r3, lsr #0x1
	b _020BE2F0
_020BE288:
	ands r2, r3, #0x3
	beq _020BE2EC
	cmp r3, r12
	addhi r3, r2, r12, lsr #0x2
	bhi _020BE2F0
	ands r2, r3, #0x1
	beq _020BE2E4
	ands r2, r3, #0x2
	movne r3, r3, lsr #0x2
	addne r2, r3, #0x1
	moveq r2, r3, lsr #0x2
	addeq r3, r2, #0x1
	ands r1, r1, #0x10000000
	movne r2, r2, lsl #0x1
	movne r1, r3, lsl #0x1
	ldrnesh r2, [r0, r2]
	ldrnesh r1, [r0, r1]
	ldreq r2, [r0, r2, lsl #0x2]
	ldreq r1, [r0, r3, lsl #0x2]
	mov r0, #0x3
	mla r0, r2, r0, r1
	mov r0, r0, asr #0x2
	bx lr
_020BE2E4:
	mov r3, r3, lsr #0x2
	b _020BE304
_020BE2EC:
	mov r3, r3, lsr #0x2
_020BE2F0:
	ands r1, r1, #0x10000000
	movne r1, r3, lsl #0x1
	ldrnesh r0, [r0, r1]
	ldreq r0, [r0, r3, lsl #0x2]
	bx lr
_020BE304:
	ands r1, r1, #0x10000000
	movne r2, r3, lsl #0x1
	addne r1, r0, r3, lsl #0x1
	ldrnesh r2, [r0, r2]
	ldrnesh r0, [r1, #0x2]
	addeq r1, r0, r3, lsl #0x2
	ldreq r2, [r0, r3, lsl #0x2]
	ldreq r0, [r1, #0x4]
	add r0, r2, r0
	mov r0, r0, asr #0x1
	bx lr
	.balign 4
_020BE330: .word 0x0000FFFF
	arm_func_end FUN_020BE238

