	.include "asm/macros.inc"
	.include "global.inc"
	.section .itcm

	; OS
	arm_func_start OS_IrqHandler
OS_IrqHandler: ; 0x01FF8000
	stmfd sp!, {lr}
	mov ip, #0x04000000
	add ip, ip, #0x210
	ldr r1, [ip, #-8]
	cmp r1, #0
	ldmeqfd sp!, {pc}
	ldmia ip, {r1, r2}
	ands r1, r1, r2
	ldmeqfd sp!, {pc}
	mov r3, #0x80000000
_01FF8028:
	clz r0, r1
	bics r1, r1, r3, lsr r0
	bne _01FF8028
	mov r1, r3, lsr r0
	str r1, [ip, #0x4]
	rsbs r0, r0, #0x1f
	ldr r1, _01FF8050 ; =0x027E0000
	ldr r0, [r1, r0, lsl #2]
	ldr lr, _01FF8054 ; =0x01FF70B8
	bx r0
_01FF8050: .word OS_IRQTable
_01FF8054: .word OS_IrqHandler_ThreadSwitch

	arm_func_start OS_IrqHandler_ThreadSwitch
OS_IrqHandler_ThreadSwitch: ; 01FF8058
	ldr ip, _01FF81A4
	mov r3, #0x0
	ldr ip, [ip]
	mov r2, #0x1
	cmp ip, #0x0
	beq _01FF80A8
_01FF8070:
	str r2, [ip, #0x64]
	str r3, [ip, #0x78]
	str r3, [ip, #0x7c]
	ldr r0, [ip, #0x80]
	str r3, [ip, #0x80]
	mov ip, r0
	cmp ip, #0x0
	bne _01FF8070
	ldr ip, _01FF81A4
	str r3, [ip]
	str r3, [ip, #0x4]
	ldr ip, _01FF81A8
	mov r1, #0x1
	strh r1, [ip]
_01FF80A8:
	ldr ip, _01FF81A8
	ldrh r1, [ip]
	cmp r1, #0x0
	ldreq pc, [sp], #0x4
	mov r1, #0x0
	strh r1, [ip]
	mov r3, #0xd2
	msr CPSR_c, r3
	add r2, ip, #0x8
	ldr r1, [r2]
_01FF80D0:
	cmp r1, #0x0
	ldrneh r0, [r1, #0x64]
	cmpne r0, #0x1
	ldrne r1, [r1, #0x68]
	bne _01FF80D0
	cmp r1, #0x0
	bne _01FF80F8
_01FF80EC:
	mov r3, #0x92
	msr CPSR_c, r3
	ldr pc, [sp], #0x4
_01FF80F8:
	ldr r0, [ip, #0x4]
	cmp r1, r0
	beq _01FF80EC
	ldr r3, [ip, #0xC]
	cmp r3, #0x0
	beq _01FF8120
	stmdb sp!, {r0, r1, ip}
	mov lr, pc
	bx r3
	ldmia sp!, {r0, r1, ip}
_01FF8120:
	str r1, [ip, #0x4]
	mrs r2, SPSR
	str r2, [r0, #0x0]!
	stmdb sp!, {r0, r1}
	add r0, r0, #0x0
	add r0, r0, #0x48
	ldr r1, _01FF81AC
	blx r1
	ldmia sp!, {r0, r1}
	ldmib sp!, {r2, r3}
	stmib r0!, {r2, r3}
	ldmib sp!, {r2, r3, ip, lr}
	stmib r0!, {r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
	stmib r0!, {lr}
	mov r3, #0xd3
	msr CPSR_c, r3
	stmib r0!, {sp}
	stmfd sp!, {r1}
	add r0, r1, #0x0
	add r0, r0, #0x48
	ldr r1, _01FF81B0
	blx r1
	ldmfd sp!, {r1}
	ldr sp, [r1, #0x44]
	mov r3, #0xd2
	msr CPSR_c, r3
	ldr r2, [r1, #0x0]!
	msr SPSR_fc, r2
	ldr lr, [r1, #0x40]
	ldmib r1!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
	nop
	stmda sp!, {r0, r1, r2, r3, ip, lr}
	ldmfd sp!, {pc}
_01FF81A4: .word OSi_IrqThreadQueue
_01FF81A8: .word OSi_ThreadInfo
_01FF81AC: .word CP_SaveContext
_01FF81B0: .word CP_RestoreContext

	.section .itcm
	arm_func_start OSi_DoBoot
OSi_DoBoot: ; 0x01FF81B4
	mov ip, #0x04000000
	str ip, [ip, #0x208]
	ldr r1, _01FF8260
	add r1, r1, #0x3fc0
	add r1, r1, #0x3c
	mov r0, #0x0
	str r0, [r1]
	ldr r1, _01FF8264
_01FF81D4:
	ldrh r0, [r1]
	and r0, r0, #0xf
	cmp r0, #0x1
	bne _01FF81D4
	mov r0, #0x100
	strh r0, [r1]
	mov r0, #0x0
	ldr r3, _01FF8268
	ldr r4, [r3]
	ldr r1, _01FF826C
	mov r2, #0x80
	bl OSi_CpuClear32
	str r4, [r3]
	ldr r1, _01FF8270
	mov r2, #0x18
	bl OSi_CpuClear32
	ldr r1, _01FF8274
	strh r0, [r1]
	ldr r1, _01FF8278
	mov r2, #0x64
	bl OSi_CpuClear32
	ldr r1, _01FF8264
_01FF822C:
	ldrh r0, [r1]
	and r0, r0, #0xf
	cmp r0, #0x1
	beq _01FF822C
	mov r0, #0x0
	strh r0, [r1]
	ldr r3, _01FF827C
	ldr ip, [r3, #0x24]
	mov lr, ip
	ldr fp, _01FF8270
	ldmia fp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl}
	mov fp, #0x0
	bx ip
_01FF8260: .word SDK_AUTOLOAD_DTCM_START
_01FF8264: .word 0x04000180
_01FF8268: .word 0x027FFD9C
_01FF826C: .word 0x027FFD80
_01FF8270: .word 0x027FFF80
_01FF8274: .word 0x027FFF98
_01FF8278: .word 0x027FFF9C
_01FF827C: .word 0x027FFE00

	arm_func_start OSi_CpuClear32
OSi_CpuClear32: ; 01FF8280
	add ip, r1, r2
_01FF8284:
	cmp r1, ip
	stmltia r1!, {r0}
	blt _01FF8284
	bx lr

	arm_func_start OSi_ReadCardRom32
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

	arm_func_start OSi_ReloadRomData
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

	arm_func_start OSi_DoResetSystem
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

	.incbin "baserom.nds", 0x10B5E0, 0xC0
