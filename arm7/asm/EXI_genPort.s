	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start EXIi_SelectRcnt
EXIi_SelectRcnt: ; 0x037FB8F0
	mov	r1, r0
	mov	r0, #49152	; 0xc000
	mov	r1, r1, lsl #16
	mov	r1, r1, lsr #16
	ldr	ip, _037FB908	; =EXIi_SetBitRcnt0L
	bx	ip
_037FB908:	.word	EXIi_SetBitRcnt0L

	arm_func_start EXIi_SetBitRcnt0L
EXIi_SetBitRcnt0L: ; 0x037FB90C
	mvn	r3, r0
	ldr	r2, _037FB928	; =0x04000134
	ldrh	r0, [r2]
	and	r0, r3, r0
	orr	r0, r1, r0
	strh	r0, [r2]
	bx	lr
_037FB928:	.word	0x04000134
