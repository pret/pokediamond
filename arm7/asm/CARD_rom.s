	.include "asm/macros.inc"
	.include "global.inc"

    .section .data

	.global cardi_rom_header_addr
cardi_rom_header_addr:
	.word	0x027FFE00

    .section .bss

	.global cardi_rom_base
cardi_rom_base: ;0x03809774
	.space 0x03809780 - 0x03809774

	.global rom_stat
rom_stat: ;0x03809780
	.space 0x038099A0 - 0x03809780

    .section .text

	arm_func_start CARDi_GetRomAccessor
CARDi_GetRomAccessor: ; 0x038008C4
	ldr	r0, _038008CC	; =_03800A7C
	bx	lr
_038008CC:	.word	_03800A7C

	arm_func_start CARD_Init
CARD_Init: ; 0x038008D0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r2, _03800940	; =cardi_common
	ldr	r0, [r2, #252]	; 0xfc
	cmp	r0, #0
	bne	_03800934
	mov	r0, #1
	str	r0, [r2, #252]	; 0xfc
	mov	r1, #0
	str	r1, [r2, #40]	; 0x28
	ldr	r0, [r2, #40]	; 0x28
	str	r0, [r2, #36]	; 0x24
	ldr	r0, [r2, #36]	; 0x24
	str	r0, [r2, #32]
	mvn	r0, #0
	str	r0, [r2, #44]	; 0x2c
	str	r1, [r2, #60]	; 0x3c
	str	r1, [r2, #64]	; 0x40
	ldr	r0, _03800944	; =cardi_rom_base
	str	r1, [r0]
	bl	CARDi_InitCommon
	bl	CARDi_GetRomAccessor
	ldr	r1, _03800948	; =rom_stat
	str	r0, [r1]
	bl	CARD_InitPulledOutCallback
_03800934:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03800940:	.word	cardi_common
_03800944:	.word	cardi_rom_base
_03800948:	.word	rom_stat

	arm_func_start CARDi_ReadRomID
CARDi_ReadRomID: ; 0x0380094C
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	ldr	r5, _03800A10	; =cardi_common
	bl	OS_DisableInterrupts
	mov	r4, r0
	add	r6, r5, #244	; 0xf4
	b	_0380096C
_03800964:
	mov	r0, r6
	bl	OS_SleepThread
_0380096C:
	ldr	r0, [r5, #252]	; 0xfc
	ands	r0, r0, #4
	bne	_03800964
	ldr	r0, [r5, #252]	; 0xfc
	orr	r0, r0, #4
	str	r0, [r5, #252]	; 0xfc
	mov	r0, #0
	str	r0, [r5, #60]	; 0x3c
	str	r0, [r5, #64]	; 0x40
	mov	r0, r4
	bl	OS_RestoreInterrupts
	bl	CARDi_ReadRomIDCore
	mov	r8, r0
	ldr	r7, _03800A10	; =cardi_common
	mov	r1, #0
	ldr	r0, [r7]
	str	r1, [r0]
	ldr	r6, [r7, #60]	; 0x3c
	ldr	r5, [r7, #64]	; 0x40
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r0, [r7, #252]	; 0xfc
	bic	r0, r0, #76	; 0x4c
	str	r0, [r7, #252]	; 0xfc
	add	r0, r7, #244	; 0xf4
	bl	OS_WakeupThread
	ldr	r0, [r7, #252]	; 0xfc
	ands	r0, r0, #16
	beq	_038009E8
	add	r0, r7, #72	; 0x48
	bl	OS_WakeupThreadDirect
_038009E8:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	cmp	r6, #0
	beq	_03800A04
	mov	r0, r5
	mov	lr, pc
	bx	r6
_03800A04:
	mov	r0, r8
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_03800A10:	.word	cardi_common

	arm_func_start CARDi_ReadRomIDCore
CARDi_ReadRomIDCore: ; 0x03800A14
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #-1207959552	; 0xb8000000
	mov	r1, #0
	bl	CARDi_SetRomOp
	ldr	r0, _03800A70	; =cardi_rom_header_addr
	ldr	r0, [r0]
	ldr	r0, [r0, #96]	; 0x60
	bic	r0, r0, #117440512	; 0x7000000
	orr	r1, r0, #-1493172224	; 0xa7000000
	mov	r0, #8192	; 0x2000
	rsb	r0, r0, #0
	and	r0, r1, r0
	ldr	r1, _03800A74	; =0x040001A4
	str	r0, [r1]
_03800A50:
	ldr	r0, [r1]
	ands	r0, r0, #8388608	; 0x800000
	beq	_03800A50
	ldr	r0, _03800A78	; =0x04100010
	ldr	r0, [r0]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03800A70:	.word	cardi_rom_header_addr
_03800A74:	.word	0x040001A4
_03800A78:	.word	0x04100010
_03800A7C:
	bx	lr

	arm_func_start CARDi_SetRomOp
CARDi_SetRomOp: ; 0x03800A80
	ldr	r3, _03800AF8	; =0x040001A4
_03800A84:
	ldr	r2, [r3]
	ands	r2, r2, #-2147483648	; 0x80000000
	bne	_03800A84
	mov	r3, #192	; 0xc0
	ldr	r2, _03800AFC	; =0x040001A1
	strb	r3, [r2]
	mov	r3, r0, lsr #24
	ldr	r2, _03800B00	; =0x040001A8
	strb	r3, [r2]
	mov	r3, r0, lsr #16
	ldr	r2, _03800B04	; =0x040001A9
	strb	r3, [r2]
	mov	r3, r0, lsr #8
	ldr	r2, _03800B08	; =0x040001AA
	strb	r3, [r2]
	ldr	r2, _03800B0C	; =0x040001AB
	strb	r0, [r2]
	mov	r2, r1, lsr #24
	ldr	r0, _03800B10	; =0x040001AC
	strb	r2, [r0]
	mov	r2, r1, lsr #16
	ldr	r0, _03800B14	; =0x040001AD
	strb	r2, [r0]
	mov	r2, r1, lsr #8
	ldr	r0, _03800B18	; =0x040001AE
	strb	r2, [r0]
	ldr	r0, _03800B1C	; =0x040001AF
	strb	r1, [r0]
	bx	lr
_03800AF8:	.word	0x040001A4
_03800AFC:	.word	0x040001A1
_03800B00:	.word	0x040001A8
_03800B04:	.word	0x040001A9
_03800B08:	.word	0x040001AA
_03800B0C:	.word	0x040001AB
_03800B10:	.word	0x040001AC
_03800B14:	.word	0x040001AD
_03800B18:	.word	0x040001AE
_03800B1C:	.word	0x040001AF
