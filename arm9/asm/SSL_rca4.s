	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start CPSi_rc4_crypt
CPSi_rc4_crypt: ; 0x020A49CC
	stmdb sp!, {r4-r6,lr}
	cmp r2, #0x0
	add r3, r0, #0x2
	ldrb lr, [r0, #0x0]
	ldrb r12, [r0, #0x1]
	mov r4, #0x0
	ble _020A4A2C
_020A49E8:
	add r5, lr, #0x1
	and lr, r5, #0xff
	ldrb r6, [r3, lr]
	add r5, r12, r6
	and r12, r5, #0xff
	ldrb r5, [r3, r12]
	strb r5, [r3, lr]
	add r5, r6, r5
	strb r6, [r3, r12]
	and r5, r5, #0xff
	ldrb r6, [r1, r4]
	ldrb r5, [r3, r5]
	eor r5, r6, r5
	strb r5, [r1, r4]
	add r4, r4, #0x1
	cmp r4, r2
	blt _020A49E8
_020A4A2C:
	strb lr, [r0, #0x0]
	strb r12, [r0, #0x1]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start CPSi_rc4_init
CPSi_rc4_init: ; 0x020A4A3C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r3, #0x0
	strb r3, [r0, #0x0]
	strb r3, [r0, #0x1]
	add r7, r0, #0x2
_020A4A54:
	strb r3, [r7, r3]
	add r3, r3, #0x1
	cmp r3, #0x100
	blt _020A4A54
	mov r5, #0x0
	mov r6, r5
	mov r4, r5
	mov r0, r5
_020A4A74:
	ldrb lr, [r7, r4]
	ldrb r12, [r1, r5]
	add r3, r5, #0x1
	and r5, r3, #0xff
	add r3, lr, r12
	add r3, r6, r3
	and r6, r3, #0xff
	ldrb r3, [r7, r6]
	cmp r5, r2
	movge r5, r0
	strb r3, [r7, r4]
	add r4, r4, #0x1
	strb lr, [r7, r6]
	cmp r4, #0x100
	blt _020A4A74
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
