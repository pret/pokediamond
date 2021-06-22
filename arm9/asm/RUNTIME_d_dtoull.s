	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start _ll_ufrom_d
_ll_ufrom_d: ; 0x020E9FAC
	tst r1, #0x80000000
	bne _020EA010
	ldr r2, _020EA034 ; =0x0000043E
	subs r2, r2, r1, lsr #0x14
	blt _020EA028
	cmp r2, #0x40
	bge _020EA004
	mov r12, r1, lsl #0xb
	orr r12, r12, #0x80000000
	orr r12, r12, r0, lsr #0x15
	cmp r2, #0x20
	ble _020E9FEC
	sub r2, r2, #0x20
	mov r1, #0x0
	mov r0, r12, lsr r2
	bx lr
_020E9FEC:
	mov r3, r0, lsl #0xb
	mov r1, r12, lsr r2
	mov r0, r3, lsr r2
	rsb r2, r2, #0x20
	orr r0, r0, r12, lsl r2
	bx lr
_020EA004:
	mov r1, #0x0
	mov r0, #0x0
	bx lr
_020EA010:
	cmn r1, #0x100000
	cmpeq r0, #0x0
	bhi _020EA028
	mov r1, #0x0
	mov r0, #0x0
	bx lr
_020EA028:
	mvn r1, #0x0
	mvn r0, #0x0
	bx lr
	.balign 4
_020EA034: .word 0x0000043E
	arm_func_end _ll_ufrom_d
