	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start _ll_mod
_ll_mod: ; 0x020EBA28
	stmdb sp!, {r4-r7,r11-r12,lr}
	mov r4, r1
	orr r4, r4, #0x1
	b _020EBA48

	arm_func_start _ll_sdiv
_ll_sdiv: ; 0x020EBA38
	stmdb sp!, {r4-r7,r11-r12,lr}
	eor r4, r1, r3
	mov r4, r4, asr #0x1
	mov r4, r4, lsl #0x1
_020EBA48:
	orrs r5, r3, r2
	bne _020EBA58
	ldmia sp!, {r4-r7,r11-r12,lr}
	bx lr
_020EBA58:
	mov r5, r0, lsr #0x1f
	add r5, r5, r1
	mov r6, r2, lsr #0x1f
	add r6, r6, r3
	orrs r6, r5, r6
	bne _020EBA8C
	mov r1, r2
	bl _s32_div_f
	ands r4, r4, #0x1
	movne r0, r1
	mov r1, r0, asr #0x1f
	ldmia sp!, {r4-r7,r11-r12,lr}
	bx lr
_020EBA8C:
	cmp r1, #0x0
	bge _020EBA9C
	rsbs r0, r0, #0x0
	rsc r1, r1, #0x0
_020EBA9C:
	cmp r3, #0x0
	bge _020EBAAC
	rsbs r2, r2, #0x0
	rsc r3, r3, #0x0
_020EBAAC:
	orrs r5, r1, r0
	beq _020EBBD0
	mov r5, #0x0
	mov r6, #0x1
	cmp r3, #0x0
	bmi _020EBAD8
_020EBAC4:
	add r5, r5, #0x1
	adds r2, r2, r2
	adcs r3, r3, r3
	bpl _020EBAC4
	add r6, r6, r5
_020EBAD8:
	cmp r1, #0x0
	blt _020EBAF8
_020EBAE0:
	cmp r6, #0x1
	beq _020EBAF8
	sub r6, r6, #0x1
	adds r0, r0, r0
	adcs r1, r1, r1
	bpl _020EBAE0
_020EBAF8:
	mov r7, #0x0
	mov r12, #0x0
	mov r11, #0x0
	b _020EBB20
_020EBB08:
	orr r12, r12, #0x1
	subs r6, r6, #0x1
	beq _020EBB78
	adds r0, r0, r0
	adcs r1, r1, r1
	adcs r7, r7, r7
_020EBB20:
	subs r0, r0, r2
	sbcs r1, r1, r3
	sbcs r7, r7, #0x0
	adds r12, r12, r12
	adc r11, r11, r11
	cmp r7, #0x0
	bge _020EBB08
_020EBB3C:
	subs r6, r6, #0x1
	beq _020EBB70
	adds r0, r0, r0
	adcs r1, r1, r1
	adc r7, r7, r7
	adds r0, r0, r2
	adcs r1, r1, r3
	adc r7, r7, #0x0
	adds r12, r12, r12
	adc r11, r11, r11
	cmp r7, #0x0
	bge _020EBB08
	b _020EBB3C
_020EBB70:
	adds r0, r0, r2
	adc r1, r1, r3
_020EBB78:
	ands r7, r4, #0x1
	moveq r0, r12
	moveq r1, r11
	beq _020EBBB0
	subs r7, r5, #0x20
	movge r0, r1, lsr r7
	bge _020EBBD4
	rsb r7, r5, #0x20
	mov r0, r0, lsr r5
	orr r0, r0, r1, lsl r7
	mov r1, r1, lsr r5
	b _020EBBB0
_020EBBA8: ; 0x020EBBA8
	mov r0, r1, lsr r7
	mov r1, #0x0
_020EBBB0:
	cmp r4, #0x0
	blt _020EBBC0
	ldmia sp!, {r4-r7,r11-r12,lr}
	bx lr
_020EBBC0:
	rsbs r0, r0, #0x0
	rsc r1, r1, #0x0
	ldmia sp!, {r4-r7,r11-r12,lr}
	bx lr
_020EBBD0:
	mov r0, #0x0
_020EBBD4:
	mov r1, #0x0
	cmp r4, #0x0
	blt _020EBBC0
	ldmia sp!, {r4-r7,r11-r12,lr}
	bx lr

	arm_func_start _ll_udiv
_ll_udiv: ; 0x020EBBE8
	stmdb sp!, {r4-r7,r11-r12,lr}
	mov r4, #0x0
	b _020EBBFC

	arm_func_start _ull_mod
_ull_mod: ; 0x020EBBF4
	stmdb sp!, {r4-r7,r11-r12,lr}
	mov r4, #0x1
_020EBBFC:
	orrs r5, r3, r2
	bne _020EBC0C
	ldmia sp!, {r4-r7,r11-r12,lr}
	bx lr
_020EBC0C:
	orrs r5, r1, r3
	bne _020EBAAC
	mov r1, r2
	bl _u32_div_not_0_f
	cmp r4, #0x0
	movne r0, r1
	mov r1, #0x0
	ldmia sp!, {r4-r7,r11-r12,lr}
	bx lr
