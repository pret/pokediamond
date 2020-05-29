	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

	; OS
	arm_func_start OSi_ReadCardRom32  ;OS_reset.c
OSi_ReadCardRom32: ; 01FF8294
	stmdb sp!,	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	ldr	r4, _01FF8390
	ldr	r3, _01FF8394
	ldr	r4, [r4]
	and	r3, r0, r3
	bic	r4, r4, #117440512	; 0x7000000
	orr	sl, r4, #-1593835520	; 0xa1000000
	rsb	r9, r3, #0
	ldr	r4, _01FF8398
_01FF82BC:
	ldr	r3, [r4]
	ands	r3, r3, #-2147483648	; 0x80000000
	bne	_01FF82BC
	ldr	r3, _01FF839C
	mov	r4, #128	; 0x80
	cmp	r9, r2
	addge	sp, sp, #4
	strb	r4, [r3]
	add	r0, r0, r9
	ldmgeia sp!,	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bxge	lr
	ldr	r3, _01FF83A0
	ldr	ip, _01FF8398
	ldr	r5, _01FF83A4
	ldr	r4, _01FF83A8
	mov	r7, r0, lsr #8
	mov	r6, #183	; 0xb7
	mov	lr, #0
_01FF8304:
	strb	r6, [r5]
	mov	r8, r0, lsr #24
	strb	r8, [r4]
	ldr	r8, _01FF83AC
	mov	fp, r0, lsr #16
	strb	fp, [r8]
	ldr	r8, _01FF83B0
	strb	r7, [r8]
	ldr	r8, _01FF83B4
	strb	r0, [r8]
	ldr	r8, _01FF83B8
	strb	lr, [r8]
	ldr	r8, _01FF83BC
	strb	lr, [r8]
	ldr	r8, _01FF83C0
	strb	lr, [r8]
	str	sl, [ip]
_01FF8348:
	ldr	r8, [ip]
	ands	fp, r8, #8388608	; 0x800000
	beq	_01FF836C
	cmp	r9, #0
	ldr	fp, [r3]
	blt	_01FF8368
	cmp	r9, r2
	strlt	fp, [r1, r9]
_01FF8368:
	add	r9, r9, #4
_01FF836C:
	ands	r8, r8, #-2147483648	; 0x80000000
	bne	_01FF8348
	cmp	r9, r2
	add	r7, r7, #2
	add	r0, r0, #512	; 0x200
	blt	_01FF8304
	add	sp, sp, #4
	ldmia sp!,	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_01FF8390:	.word 0x027FFE60
_01FF8394:	.word 0x000001FF
_01FF8398:	.word 0x040001A4
_01FF839C:	.word 0x040001A1
_01FF83A0:	.word 0x04100010
_01FF83A4:	.word 0x040001A8
_01FF83A8:	.word 0x040001A9
_01FF83AC:	.word 0x040001AA
_01FF83B0:	.word 0x040001AB
_01FF83B4:	.word 0x040001AC
_01FF83B8:	.word 0x040001AD
_01FF83BC:	.word 0x040001AE
_01FF83C0:	.word 0x040001AF

	arm_func_start OSi_ReloadRomData  ;OS_reset.c
OSi_ReloadRomData: ; 0x01FF83C4
	stmdb sp!,	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	ldr	r0, _01FF8484
	ldr	sl, [r0]
	cmp	sl, #32768	; 0x8000
	bcc	_01FF83EC
	ldr	r1, _01FF8488
	mov	r0, sl
	mov	r2, #352	; 0x160
	bl	OSi_ReadCardRom32
_01FF83EC:
	ldr	r5, _01FF848C
	ldr	r4, _01FF8490
	ldr	r3, _01FF8494
	ldr	r2, _01FF8498
	ldr	r1, _01FF849C
	ldr	r9, [r5]
	ldr	r0, _01FF84A0
	ldr	r8, [r4]
	ldr	r7, [r3]
	ldr	r6, [r2]
	ldr	r5, [r1]
	ldr	r4, [r0]
	bl	OS_DisableInterrupts ; 0x1e02b0
	mov	fp, r0
	bl	DC_StoreAll ; 0x1df064
	bl	DC_InvalidateAll ; 0x1df058
	mov	r0, fp
	bl	OS_RestoreInterrupts ; 0x1e02c4
	bl	IC_InvalidateAll ; 0x1df12c
	bl	DC_WaitWriteBufferEmpty ; 0x1df120
	add	r9, r9, sl
	cmp	r9, #32768	; 0x8000
	rsbcc	r0, r9, #32768	; 0x8000
	addcc	r8, r8, r0
	subcc	r7, r7, r0
	movcc	r9, #32768	; 0x8000
	add	r6, r6, sl
	mov	r0, r9
	mov	r1, r8
	mov	r2, r7
	bl	OSi_ReadCardRom32 ; 0x10b234
	mov	r0, r6
	mov	r1, r5
	mov	r2, r4
	bl	OSi_ReadCardRom32
	add	sp, sp, #4
	ldmia sp!,	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_01FF8484:	.word 0x027FFC2C
_01FF8488:	.word 0x027FFE00
_01FF848C:	.word 0x027FFE20
_01FF8490:	.word 0x027FFE28
_01FF8494:	.word 0x027FFE2C
_01FF8498:	.word 0x027FFE30
_01FF849C:	.word 0x027FFE38
_01FF84A0:	.word 0x027FFE3C

	arm_func_start OSi_DoResetSystem  ;OS_reset.c
OSi_DoResetSystem: ; 0x01FF84A4
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _01FF84DC
_01FF84B0:
	ldrh	r1, [r0]
	cmp	r1, #0
	beq	_01FF84B0
	ldr	r0, _01FF84E0
	mov	r1, #0
	strh	r1, [r0]
	bl	OSi_ReloadRomData
	bl	OSi_DoBoot
	add	sp, sp, #4
	ldmfd	sp!, {lr}
	bx	lr
_01FF84DC:	.word OSi_IsResetOccurred
_01FF84E0:	.word 0x04000208

	; MI
	arm_func_start MIi_DmaSetParams_wait_noInt
MIi_DmaSetParams_wait_noInt: ; 0x01FF84E4
	stmdb sp!,	{r4, lr}
	mov	ip, #12
	mul	r4, r0, ip
	add	ip, r4, #67108864	; 0x4000000
	ldr	lr, [pc, #64]	; 0x10b4dc
	str	r1, [ip, #176]	; 0xb0
	add	r4, r4, lr
	str	r2, [r4, #4]
	str	r3, [r4, #8]
	ldr	r1, [lr]
	cmp	r0, #0
	ldr	r0, [lr]
	moveq	r1, #0
	streq	r1, [r4]
	streq	r1, [r4, #4]
	ldreq	r0, _01FF8540
	ldr	r1, _01FF853C
	streq	r0, [r4, #8]
	ldr	r0, [r1]
	ldr	r0, [r1]
	ldmia sp!,	{r4, lr}
	bx	lr
_01FF853C:	.word 0x040000B0
_01FF8540:	.word 0x81400001

	arm_func_start MIi_DmaSetParams_noInt
MIi_DmaSetParams_noInt: ; 01FF8544
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	ip, #12
	mul	lr, r0, ip
	ldr	r0, _01FF8578
	add	ip, lr, #67108864	; 0x4000000
	str	r1, [ip, #176]	; 0xb0
	add	r0, lr, r0
	str	r2, [r0, #4]
	str	r3, [r0, #8]
	add	sp, sp, #4
	ldmfd	sp!, {lr}
	bx	lr
_01FF8578:	.word 0x040000B0

	arm_func_start MIi_DmaSetParams_wait
MIi_DmaSetParams_wait: ; 01FF857C
	stmdb sp!,	{r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r5, r2
	mov	r4, r3
	bl	OS_DisableInterrupts
	mov	r1, #12
	mul	r3, r7, r1
	add	r1, r3, #67108864	; 0x4000000
	ldr	r2, _01FF85E8
	str	r6, [r1, #176]	; 0xb0
	add	r3, r3, r2
	str	r5, [r3, #4]
	str	r4, [r3, #8]
	ldr	r1, [r2]
	cmp	r7, #0
	ldr	r1, [r2]
	moveq	r2, #0
	streq	r2, [r3]
	ldreq	r1, _01FF85EC
	streq	r2, [r3, #4]
	streq	r1, [r3, #8]
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia sp!,	{r4, r5, r6, r7, lr}
	bx	lr
_01FF85E8:	.word 0x040000B0
_01FF85EC:	.word 0x81400001

	arm_func_start MIi_DmaSetParams
MIi_DmaSetParams: ; 01FF85F0
	stmdb sp!,	{r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r5, r2
	mov	r4, r3
	bl	OS_DisableInterrupts
	mov	r1, #12
	mul	r3, r7, r1
	ldr	r1, _01FF863C
	add	r2, r3, #67108864	; 0x4000000
	str	r6, [r2, #176]	; 0xb0
	add	r1, r3, r1
	str	r5, [r1, #4]
	str	r4, [r1, #8]
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia sp!,	{r4, r5, r6, r7, lr}
	bx	lr
_01FF863C:	.word 0x040000B0

	arm_func_start MI_SendGXCommand
MI_SendGXCommand: ; 0x01FF8640
	stmdb sp!,	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	movs	r8, r2
	mov	sl, r0
	mov	r9, r1
	addeq	sp, sp, #4
	ldmeqia sp!,	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bxeq	lr
	mov	r3, #0
	bl	MIi_CheckDma0SourceAddress
	mov	r0, #3
	mul	r1, sl, r0
	ldr	r0, [pc, #104]	; 0x10b680
	add	r1, r1, #2
	add	r7, r0, r1, lsl #2
_01FF867C:
	ldr	r0, [r7]
	ands	r0, r0, #-2147483648	; 0x80000000
	bne	_01FF867C
	cmp	r8, #0
	beq	_01FF86C8
	ldr	fp, [pc, #76]	; 0x10b684
	mov	r5, #472	; 0x1d8
	ldr	r4, [pc, #72]	; 0x10b688
_01FF869C:
	cmp	r8, #472	; 0x1d8
	movhi	r6, r5
	movls	r6, r8
	mov	r0, sl
	mov	r1, r9
	mov	r2, fp
	orr	r3, r4, r6, lsr #2
	bl	MIi_DmaSetParams
	subs	r8, r8, r6
	add	r9, r9, r6
	bne	_01FF869C
_01FF86C8:
	ldr	r0, [r7]
	ands	r0, r0, #-2147483648	; 0x80000000
	bne	_01FF86C8
	add	sp, sp, #4
	ldmia sp!,	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_01FF86E0:	.word 0x040000B0
_01FF86E4:	.word 0x04000400
_01FF86E8:	.word 0x84400000
