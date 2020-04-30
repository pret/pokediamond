    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start FX_Atan2
FX_Atan2: ; 0x020C5668
	stmdb sp!, {r4,lr}
	cmp r0, #0x0
	ble _020C5704
	cmp r1, #0x0
	ble _020C56B4
	cmp r1, r0
	movgt r3, r0
	movgt r4, #0x0
	movgt r0, #0x1
	bgt _020C57C8
	cmp r1, r0
	movlt r3, r1
	movlt r1, r0
	movlt r4, #0x4000
	movlt r0, #0x0
	blt _020C57C8
	mov r0, #0x2000
	ldmia sp!, {r4,lr}
	bx lr
_020C56B4:
	cmp r1, #0x0
	bge _020C56F8
	rsb r1, r1, #0x0
	cmp r1, r0
	movlt r3, r1
	movlt r1, r0
	movlt r4, #0x4000
	movlt r0, #0x1
	blt _020C57C8
	cmp r1, r0
	movgt r3, r0
	movgt r4, #0x8000
	movgt r0, #0x0
	bgt _020C57C8
	mov r0, #0x6000
	ldmia sp!, {r4,lr}
	bx lr
_020C56F8:
	mov r0, #0x4000
	ldmia sp!, {r4,lr}
	bx lr
_020C5704:
	cmp r0, #0x0
	bge _020C57B4
	cmp r1, #0x0
	rsb r2, r0, #0x0
	bge _020C5760
	rsb r1, r1, #0x0
	cmp r1, r2
	movgt r0, #0x8000
	rsbgt r4, r0, #0x0
	movgt r3, r2
	movgt r0, #0x1
	bgt _020C57C8
	cmp r1, r2
	bge _020C5754
	mov r0, #0x4000
	mov r3, r1
	mov r1, r2
	rsb r4, r0, #0x0
	mov r0, #0x0
	b _020C57C8
_020C5754:
	mov r0, #0xa000
	ldmia sp!, {r4,lr}
	bx lr
_020C5760:
	cmp r1, #0x0
	ble _020C57A8
	cmp r1, r2
	bge _020C5788
	mov r0, #0x4000
	mov r3, r1
	mov r1, r2
	rsb r4, r0, #0x0
	mov r0, #0x1
	b _020C57C8
_020C5788:
	cmp r1, r2
	movgt r4, #0x0
	movgt r3, r2
	movgt r0, r4
	bgt _020C57C8
	mov r0, #0xe000
	ldmia sp!, {r4,lr}
	bx lr
_020C57A8:
	mov r0, #0xc000
	ldmia sp!, {r4,lr}
	bx lr
_020C57B4:
	cmp r1, #0x0
	movge r0, #0x0
	movlt r0, #0x8000
	ldmia sp!, {r4,lr}
	bx lr
_020C57C8:
	cmp r1, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	cmp r0, #0x0
	beq _020C580C
	mov r0, r3
	bl FX_Div
	mov r1, r0, asr #0x5
	ldr r0, _020C5838 ; =FX_AtanTable_
	mov r1, r1, lsl #0x1
	ldrsh r0, [r0, r1]
	add r0, r4, r0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {r4,lr}
	bx lr
_020C580C:
	mov r0, r3
	bl FX_Div
	mov r1, r0, asr #0x5
	ldr r0, _020C5838 ; =FX_AtanTable_
	mov r1, r1, lsl #0x1
	ldrsh r0, [r0, r1]
	sub r0, r4, r0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C5838: .word FX_AtanTable_

	arm_func_start FX_Atan
FX_Atan: ; 0x020C583C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	blt _020C58A4
	cmp r0, #0x1000
	ble _020C5880
	bl FX_Inv
	mov r1, r0, asr #0x5
	ldr r0, _020C5924 ; =FX_AtanTable_
	mov r1, r1, lsl #0x1
	ldrsh r0, [r0, r1]
	add sp, sp, #0x4
	rsb r0, r0, #0x4000
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {lr}
	bx lr
_020C5880:
	cmp r0, #0x1000
	movlt r1, r0, asr #0x5
	ldrlt r0, _020C5924 ; =FX_AtanTable_
	movlt r1, r1, lsl #0x1
	ldrlth r0, [r0, r1]
	add sp, sp, #0x4
	movge r0, #0x2000
	ldmia sp!, {lr}
	bx lr
_020C58A4:
	mov r1, #0x1000
	rsb r1, r1, #0x0
	cmp r0, r1
	bge _020C58E4
	rsb r0, r0, #0x0
	bl FX_Inv
	mov r1, r0, asr #0x5
	ldr r0, _020C5924 ; =FX_AtanTable_
	mov r1, r1, lsl #0x1
	ldrsh r0, [r0, r1]
	add sp, sp, #0x4
	sub r0, r0, #0x4000
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {lr}
	bx lr
_020C58E4:
	cmp r0, r1
	addle sp, sp, #0x4
	movle r0, #0xe000
	ldmleia sp!, {lr}
	bxle lr
	rsb r0, r0, #0x0
	mov r1, r0, asr #0x5
	ldr r0, _020C5924 ; =FX_AtanTable_
	mov r1, r1, lsl #0x1
	ldrsh r0, [r0, r1]
	rsb r0, r0, #0x0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C5924: .word FX_AtanTable_
