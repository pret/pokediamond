	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start _dsqrt
_dsqrt: ; 0x020EA418
	stmdb sp!, {r4-r6,lr}
	ldr r2, _020EA5A8 ; =0x7FF00000
	cmp r1, r2
	bhs _020EA564
	movs r12, r1, lsr #0x14
	beq _020EA510
	bic r1, r1, r2
	orr r1, r1, #0x100000
_020EA438:
	movs r12, r12, asr #0x1
	bhs _020EA44C
	sub r12, r12, #0x1
	movs r0, r0, lsl #0x1
	adc r1, r1, r1
_020EA44C:
	movs r3, r0, lsl #0x1
	adc r1, r1, r1
	mov r2, #0x0
	mov r4, #0x0
	mov lr, #0x200000
_020EA460:
	add r6, r4, lr
	cmp r6, r1
	addle r4, r6, lr
	suble r1, r1, r6
	addle r2, r2, lr
	movs r3, r3, lsl #0x1
	adc r1, r1, r1
	movs lr, lr, lsr #0x1
	bne _020EA460
	mov r0, #0x0
	mov r5, #0x0
	cmp r1, r4
	cmpeq r3, #0x80000000
	blo _020EA4A8
	subs r3, r3, #0x80000000
	sbc r1, r1, r4
	add r4, r4, #0x1
	mov r0, #0x80000000
_020EA4A8:
	movs r3, r3, lsl #0x1
	adc r1, r1, r1
	mov lr, #0x40000000
_020EA4B4:
	add r6, r5, lr
	cmp r4, r1
	cmpeq r6, r3
	bhi _020EA4D4
	add r5, r6, lr
	subs r3, r3, r6
	sbc r1, r1, r4
	add r0, r0, lr
_020EA4D4:
	movs r3, r3, lsl #0x1
	adc r1, r1, r1
	movs lr, lr, lsr #0x1
	bne _020EA4B4
	orrs r1, r1, r3
	biceq r0, r0, #0x1
	movs r1, r2, lsr #0x1
	movs r0, r0, rrx
	adcs r0, r0, #0x0
	adc r1, r1, #0x0
	add r1, r1, #0x20000000
	sub r1, r1, #0x100000
	add r1, r1, r12, lsl #0x14
	ldmia sp!, {r4-r6,lr}
	bx lr
_020EA510:
	cmp r1, #0x0
	bne _020EA540
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mvn r12, #0x13
	clz r5, r0
	movs r0, r0, lsl r5
	sub r12, r12, r5
	mov r1, r0, lsr #0xb
	mov r0, r0, lsl #0x15
	b _020EA438
_020EA540:
	clz r2, r1
	movs r1, r1, lsl r2
	rsb r2, r2, #0x2b
	mov r1, r1, lsr #0xb
	orr r1, r1, r0, lsr r2
	rsb r2, r2, #0x20
	mov r0, r0, lsl r2
	rsb r12, r2, #0x1
	b _020EA438
_020EA564:
	tst r1, #0x80000000
	beq _020EA580
	bics r3, r1, #0x80000000
	cmpeq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	b _020EA58C
_020EA580:
	orrs r2, r0, r1, lsl #0xc
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
_020EA58C:
	ldr r2, _020EA5AC ; =0x7FF80000
	orr r1, r1, r2
	ldr r3, _020EA5B0 ; =errno
	mov r4, #0x21
	str r4, [r3, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020EA5A8: .word 0x7FF00000
_020EA5AC: .word 0x7FF80000
_020EA5B0: .word errno
	arm_func_end _dsqrt
