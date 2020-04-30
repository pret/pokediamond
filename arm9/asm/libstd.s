		.include "asm/macros.inc"
		.include "global.inc"

	.text

	arm_func_start STD_CompareNString
STD_CompareNString: ; 0x020DE03C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	beq _020DE080
	cmp r2, #0x0
	mov lr, #0x0
	ble _020DE080
_020DE058:
	ldrb r12, [r0, lr]
	ldrb r3, [r1, lr]
	cmp r12, r3
	addne sp, sp, #0x4
	subne r0, r12, r3
	ldmneia sp!, {lr}
	bxne lr
	add lr, lr, #0x1
	cmp lr, r2
	blt _020DE058
_020DE080:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start STD_CompareString
STD_CompareString: ; 0x020DE090
	b _020DE09C
_020DE094:
	add r0, r0, #0x1
	add r1, r1, #0x1
_020DE09C:
	ldrsb r2, [r1, #0x0]
	ldrsb r3, [r0, #0x0]
	cmp r3, r2
	bne _020DE0B4
	cmp r3, #0x0
	bne _020DE094
_020DE0B4:
	sub r0, r3, r2
	bx lr

	arm_func_start STD_GetStringLength
STD_GetStringLength: ; 0x020DE0BC
	ldrsb r1, [r0, #0x0]
	mov r2, #0x0
	cmp r1, #0x0
	beq _020DE0DC
_020DE0CC:
	add r2, r2, #0x1
	ldrsb r1, [r0, r2]
	cmp r1, #0x0
	bne _020DE0CC
_020DE0DC:
	mov r0, r2
	bx lr

	arm_func_start STD_CopyLString
STD_CopyLString: ; 0x020DE0E4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	sub r12, r2, #0x1
	cmp r12, #0x0
	mov lr, #0x0
	ble _020DE120
_020DE0FC:
	ldrsb r3, [r1, #0x0]
	strb r3, [r0, lr]
	ldrsb r3, [r1, #0x0]
	cmp r3, #0x0
	beq _020DE120
	add lr, lr, #0x1
	cmp lr, r12
	add r1, r1, #0x1
	blt _020DE0FC
_020DE120:
	sub r3, r2, #0x1
	cmp lr, r3
	blt _020DE138
	cmp r2, #0x0
	movne r2, #0x0
	strneb r2, [r0, lr]
_020DE138:
	mov r0, r1
	bl STD_GetStringLength
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
