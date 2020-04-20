.include "asm/macros.inc"

/* rom2.s TODO: Disassemble */

.section .text

.incbin "baserom.nds", 0xD9150, 0x16D3C

; required to make the linker happy :

	arm_func_start _u32_div_f
_u32_div_f: ; 0x020EBE8C
	cmp r1, #0x0
	bxeq lr
	cmp r0, r1
	movcc r1, r0
	movcc r0, #0x0
	bxcc lr
	mov r2, #0x1c
	mov r3, r0, lsr #0x4
	cmp r1, r3, lsr #0xc
	suble r2, r2, #0x10
	movle r3, r3, lsr #0x10
	cmp r1, r3, lsr #0x4
	suble r2, r2, #0x8
	movle r3, r3, lsr #0x8
	cmp r1, r3
	suble r2, r2, #0x4
	movle r3, r3, lsr #0x4
	mov r0, r0, lsl r2
	rsb r1, r1, #0x0
	adds r0, r0, r0
	add r2, r2, r2, lsl #0x1
	add pc, pc, r2, lsl #0x2
	mov r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	adcs r3, r1, r3, lsl #0x1
	subcc r3, r3, r1
	adcs r0, r0, r0
	mov r1, r3
	bx lr

.incbin "baserom.nds", 0xF0070, 0x55C

	.global FUN_020EC5CC
FUN_020EC5CC:
.incbin "baserom.nds", 0xF05CC, 0xC8

	.global FUN_020EC694
FUN_020EC694:
.incbin "baserom.nds", 0xF0694, 0x1b090
