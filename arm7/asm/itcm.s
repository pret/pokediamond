/* arm7_rom.s TODO: Disassemble */
	.include "asm/macros.inc"
	.include "global.inc"

	.section .text
	arm_func_start FUN_027E0000
FUN_027E0000: ; 0x027E0000 load at 0x023801B0
	stmdb	sp!, {r4, r5, r6, lr}
	ldr	r6, [pc, #180]	; 0x270
	ldr	r3, [pc, #180]	; 0x274
	ldr	r0, [pc, #180]	; 0x278
	b	_027E00B0
_027E0014:
	mov	r2, r3
	ldr	r5, [r3, #4]
	add	r1, r3, #8
	add	r3, r3, #12
	ldr	r4, [r1]
	ldr	r1, [r2]
	cmp	r1, #100663296	; 0x6000000
	bne	_027E00AC
	ldr	r3, [pc, #144]	; 0x27c
	ldr	r0, [pc, #144]	; 0x280
	str	r3, [r0]
	add	r2, r5, r4
	ldr	r0, [pc, #136]	; 0x284
	str	r2, [r0]
	ldr	r1, [pc, #132]	; 0x288
	add	r0, r3, r2
	cmp	r1, r0
	beq	_027E0060
	bl	FUN_037FB1F0
_027E0060:
	ldr	r0, [pc, #104]	; 0x280
	ldr	r3, [r0]
	mov	r2, #0
	mov	r1, r5, lsr #2
	b	_027E0080
_027E0074:
	ldr	r0, [r6], #4
	str	r0, [r3], #4
	add	r2, r2, #1
_027E0080:
	cmp	r2, r1
	bcc	_027E0074
	mov	r1, #0
	mov	r2, r4, lsr #2
	mov	r0, r1
	b	_027E00A0
_027E0098:
	str	r0, [r3], #4
	add	r1, r1, #1
_027E00A0:
	cmp	r1, r2
	bcc	_027E0098
	b	_027E00B8
_027E00AC:
	add	r6, r6, r5
_027E00B0:
	cmp	r3, r0
	bne	_027E0014
_027E00B8:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr
_027E00C0: .word 0x023801B0
_027E00C4: .word 0x023A92F8
_027E00C8: .word 0x023A931C
_027E00CC: .word 0x027E00DC
_027E00D0: .word 0x0380A3F4
_027E00D4: .word 0x0380A3FC
_027E00D8: .word 0x027FAFCC
