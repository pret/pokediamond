	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start fwide
fwide:
	cmp r0, #0x0
	beq _020E500C
	ldr r3, [r0, #0x4]
	mov r2, r3, lsl #0x16
	movs r2, r2, lsr #0x1d
	bne _020E5014
_020E500C:
	mov r0, #0x0
	bx lr
_020E5014:
	mov r2, r3, lsl #0x14
	movs r2, r2, lsr #0x1e
	beq _020E5034
	cmp r2, #0x1
	beq _020E505C
	cmp r2, #0x2
	moveq r1, #0x1
	b _020E5060
_020E5034:
	cmp r1, #0x0
	ble _020E504C
	bic r2, r3, #0xc00
	orr r2, r2, #0x800
	str r2, [r0, #0x4]
	b _020E5060
_020E504C:
	biclt r2, r3, #0xc00
	orrlt r2, r2, #0x400
	strlt r2, [r0, #0x4]
	b _020E5060
_020E505C:
	mvn r1, #0x0
_020E5060:
	mov r0, r1
	bx lr
	arm_func_end fwide
