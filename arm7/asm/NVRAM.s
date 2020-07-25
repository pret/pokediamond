	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global _0380A018
_0380A018: ;0x0380A018
	.space 0x0380A038 - 0x0380A018

	.section .text

	arm_func_start FUN_0380428C
FUN_0380428C: ;@ 0x0380428C
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	add	r0, sp, #0
	bl	NVRAM_ReadStatusRegister
	ldrh	r1, [sp]
	ands	r0, r1, #1
	movne	r0, #0
	bne	_038042B8
	ands	r0, r1, #2
	movne	r0, #1
	moveq	r0, #0
_038042B8:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start FUN_038042C4
FUN_038042C4: ;@ 0x038042C4
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	add	r0, sp, #0
	bl	NVRAM_ReadStatusRegister
	ldrh	r0, [sp]
	ands	r0, r0, #1
	moveq	r0, #1
	movne	r0, #0
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start NVRAM_ExecuteProcess
NVRAM_ExecuteProcess: ;@ 0x038042F0
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r4, r0
	bl	OS_DisableInterrupts
	mov	r5, r0
	mov	r0, #1
	bl	SPIi_CheckException
	cmp	r0, #0
	bne	_03804334
	mov	r0, r5
	bl	OS_RestoreInterrupts
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #4
	bl	SPIi_ReturnResult
	b	_038045C0
_03804334:
	mov	r0, #1
	bl	SPIi_GetException
	mov	r0, r5
	bl	OS_RestoreInterrupts
	ldr	r0, [r4, #4]
	sub	r0, r0, #32
	cmp	r0, #13
	addls	pc, pc, r0, lsl #2
	b	_03804584
	b	_03804390
	b	_03804398
	b	_038043A0
	b	_038043AC
	b	_038043EC
	b	_0380442C
	b	_03804474
	b	_038044BC
	b	_038044F4
	b	_0380452C
	b	_03804534
	b	_0380453C
	b	_03804570
	b	_0380457C
_03804390:
	bl	NVRAM_WriteEnable
	b	_038045A4
_03804398:
	bl	NVRAM_WriteDisable
	b	_038045A4
_038043A0:
	ldr	r0, [r4, #16]
	bl	NVRAM_ReadStatusRegister
	b	_038045A4
_038043AC:
	bl	FUN_038042C4
	cmp	r0, #0
	bne	_038043D8
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
	mov	r0, #1
	bl	SPIi_ReleaseException
	b	_038045C0
_038043D8:
	ldr	r0, [r4, #8]
	ldr	r1, [r4, #12]
	ldr	r2, [r4, #16]
	bl	NVRAM_ReadDataBytes
	b	_038045A4
_038043EC:
	bl	FUN_038042C4
	cmp	r0, #0
	bne	_03804418
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
	mov	r0, #1
	bl	SPIi_ReleaseException
	b	_038045C0
_03804418:
	ldr	r0, [r4, #8]
	ldr	r1, [r4, #12]
	ldr	r2, [r4, #16]
	bl	NVRAM_ReadDataBytesAtHigherSpeed
	b	_038045A4
_0380442C:
	bl	FUN_0380428C
	cmp	r0, #0
	bne	_03804458
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
	mov	r0, #1
	bl	SPIi_ReleaseException
	b	_038045C0
_03804458:
	ldr	r0, [r4, #8]
	ldr	r1, [r4, #12]
	mov	r1, r1, lsl #16
	mov	r1, r1, lsr #16
	ldr	r2, [r4, #16]
	bl	NVRAM_PageWrite
	b	_038045A4
_03804474:
	bl	FUN_0380428C
	cmp	r0, #0
	bne	_038044A0
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
	mov	r0, #1
	bl	SPIi_ReleaseException
	b	_038045C0
_038044A0:
	ldr	r0, [r4, #8]
	ldr	r1, [r4, #12]
	mov	r1, r1, lsl #16
	mov	r1, r1, lsr #16
	ldr	r2, [r4, #16]
	bl	NVRAM_PageProgram
	b	_038045A4
_038044BC:
	bl	FUN_0380428C
	cmp	r0, #0
	bne	_038044E8
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
	mov	r0, #1
	bl	SPIi_ReleaseException
	b	_038045C0
_038044E8:
	ldr	r0, [r4, #8]
	bl	NVRAM_PageErase
	b	_038045A4
_038044F4:
	bl	FUN_0380428C
	cmp	r0, #0
	bne	_03804520
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
	mov	r0, #1
	bl	SPIi_ReleaseException
	b	_038045C0
_03804520:
	ldr	r0, [r4, #8]
	bl	NVRAM_SectorErase
	b	_038045A4
_0380452C:
	bl	NVRAM_DeepPowerDown
	b	_038045A4
_03804534:
	bl	NVRAM_ReleaseFromDeepPowerDown
	b	_038045A4
_0380453C:
	bl	FUN_0380428C
	cmp	r0, #0
	bne	_03804568
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #3
	bl	SPIi_ReturnResult
	mov	r0, #1
	bl	SPIi_ReleaseException
	b	_038045C0
_03804568:
	bl	NVRAM_ChipErase
	b	_038045A4
_03804570:
	ldr	r0, [r4, #16]
	bl	NVRAM_ReadSiliconId
	b	_038045A4
_0380457C:
	bl	NVRAM_SoftwareReset
	b	_038045A4
_03804584:
	mov	r0, #1
	bl	SPIi_ReleaseException
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #1
	bl	SPIi_ReturnResult
	b	_038045C0
_038045A4:
	ldr	r0, [r4, #4]
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	mov	r1, #0
	bl	SPIi_ReturnResult
	mov	r0, #1
	bl	SPIi_ReleaseException
_038045C0:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start NVRAM_AnalyzeCommand
NVRAM_AnalyzeCommand: ;@ 0x038045CC
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #12
	ands	r1, r0, #33554432	;@ 0x2000000
	beq	_038045FC
	mov	r5, #0
	mov	lr, r5
	ldr	r1, _0380476C	;@ =_0380A018
_038045E8:
	mov	r4, r5, lsl #1
	strh	lr, [r1, r4]
	add	r5, r5, #1
	cmp	r5, #16
	blt	_038045E8
_038045FC:
	and	r1, r0, #983040	;@ 0xf0000
	mov	r1, r1, lsr #16
	mov	r4, r1, lsl #1
	ldr	r1, _0380476C	;@ =_0380A018
	strh	r0, [r1, r4]
	ands	r0, r0, #16777216	;@ 0x1000000
	beq	_03804760
	ldrh	r0, [r1]
	and	r4, r0, #65280	;@ 0xff00
	mov	r4, r4, lsl #8
	mov	r4, r4, lsr #16
	sub	lr, r4, #34	;@ 0x22
	cmp	lr, #10
	addls	pc, pc, lr, lsl #2
	b	_03804734
	b	_03804664
	b	_038046A0
	b	_038046A0
	b	_038046E8
	b	_038046E8
	b	_03804728
	b	_03804728
	b	_03804734
	b	_03804734
	b	_03804734
	b	_03804664
_03804664:
	ldrh	ip, [r1, #4]
	and	lr, ip, #65280	;@ 0xff00
	and	r0, r0, #255	;@ 0xff
	mov	ip, r0, lsl #24
	ldrh	r0, [r1, #2]
	orr	r0, ip, r0, lsl #8
	orr	ip, r0, lr, lsr #8
	cmp	ip, #33554432	;@ 0x2000000
	bcc	_03804690
	cmp	ip, #41943040	;@ 0x2800000
	bcc	_03804734
_03804690:
	mov	r0, r4
	mov	r1, #2
	bl	SPIi_ReturnResult
	b	_03804760
_038046A0:
	ldrh	r3, [r1, #8]
	ldrh	r2, [r1, #10]
	orr	ip, r2, r3, lsl #16
	cmp	ip, #33554432	;@ 0x2000000
	bcc	_038046BC
	cmp	ip, #41943040	;@ 0x2800000
	bcc	_038046CC
_038046BC:
	mov	r0, r4
	mov	r1, #2
	bl	SPIi_ReturnResult
	b	_03804760
_038046CC:
	and	r2, r0, #255	;@ 0xff
	ldrh	r0, [r1, #2]
	orr	r3, r0, r2, lsl #16
	ldrh	r2, [r1, #4]
	ldrh	r0, [r1, #6]
	orr	r2, r0, r2, lsl #16
	b	_03804734
_038046E8:
	ldrh	r3, [r1, #6]
	ldrh	r2, [r1, #8]
	orr	ip, r2, r3, lsl #16
	cmp	ip, #33554432	;@ 0x2000000
	bcc	_03804704
	cmp	ip, #41943040	;@ 0x2800000
	bcc	_03804714
_03804704:
	mov	r0, r4
	mov	r1, #2
	bl	SPIi_ReturnResult
	b	_03804760
_03804714:
	and	r2, r0, #255	;@ 0xff
	ldrh	r0, [r1, #2]
	orr	r3, r0, r2, lsl #16
	ldrh	r2, [r1, #4]
	b	_03804734
_03804728:
	and	r3, r0, #255	;@ 0xff
	ldrh	r0, [r1, #2]
	orr	r3, r0, r3, lsl #16
_03804734:
	str	r2, [sp]
	str	ip, [sp, #4]
	mov	r0, #1
	mov	r1, r4
	mov	r2, #3
	bl	SPIi_SetEntry
	cmp	r0, #0
	bne	_03804760
	mov	r0, r4
	mov	r1, #4
	bl	SPIi_ReturnResult
_03804760:
	add	sp, sp, #12
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_0380476C:	.word	_0380A018

	arm_func_start NVRAM_Init
NVRAM_Init: ;@ 0x03804770
	mov	r3, #0
	mov	r2, r3
	ldr	r0, _03804794	;@ =_0380A018
_0380477C:
	mov	r1, r3, lsl #1
	strh	r2, [r0, r1]
	add	r3, r3, #1
	cmp	r3, #16
	blt	_0380477C
	bx	lr
_03804794:	.word	_0380A018

	arm_func_start NVRAM_SoftwareReset
NVRAM_SoftwareReset: ;@ 0x03804798
	ldr	r1, _038047D0	;@ =0x040001C0
_0380479C:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_0380479C
	mov	r0, #33024	;@ 0x8100
	strh	r0, [r1]
	mov	r1, #255	;@ 0xff
	ldr	r0, _038047D4	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _038047D0	;@ =0x040001C0
_038047C0:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038047C0
	bx	lr
_038047D0:	.word	0x040001C0
_038047D4:	.word	0x040001C2

	arm_func_start NVRAM_ReadSiliconId
NVRAM_ReadSiliconId: ;@ 0x038047D8
	ldr	r2, _0380486C	;@ =0x040001C0
_038047DC:
	ldrh	r1, [r2]
	ands	r1, r1, #128	;@ 0x80
	bne	_038047DC
	mov	r1, #35072	;@ 0x8900
	strh	r1, [r2]
	mov	r2, #159	;@ 0x9f
	ldr	r1, _03804870	;@ =0x040001C2
	strh	r2, [r1]
	ldr	r2, _0380486C	;@ =0x040001C0
_03804800:
	ldrh	r1, [r2]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804800
	mov	r2, #0
	ldr	r1, _03804870	;@ =0x040001C2
	strh	r2, [r1]
	ldr	r3, _0380486C	;@ =0x040001C0
_0380481C:
	ldrh	r1, [r3]
	ands	r1, r1, #128	;@ 0x80
	bne	_0380481C
	ldr	r2, _03804870	;@ =0x040001C2
	ldrh	r1, [r2]
	and	r1, r1, #255	;@ 0xff
	strb	r1, [r0]
	mov	r1, #33024	;@ 0x8100
	strh	r1, [r3]
	mov	r1, #0
	strh	r1, [r2]
	ldr	r2, _0380486C	;@ =0x040001C0
_0380484C:
	ldrh	r1, [r2]
	ands	r1, r1, #128	;@ 0x80
	bne	_0380484C
	ldr	r1, _03804870	;@ =0x040001C2
	ldrh	r1, [r1]
	and	r1, r1, #255	;@ 0xff
	strb	r1, [r0, #1]
	bx	lr
_0380486C:	.word	0x040001C0
_03804870:	.word	0x040001C2

	arm_func_start NVRAM_ChipErase
NVRAM_ChipErase: ;@ 0x03804874
	ldr	r1, _038048AC	;@ =0x040001C0
_03804878:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804878
	mov	r0, #33024	;@ 0x8100
	strh	r0, [r1]
	mov	r1, #199	;@ 0xc7
	ldr	r0, _038048B0	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _038048AC	;@ =0x040001C0
_0380489C:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_0380489C
	bx	lr
_038048AC:	.word	0x040001C0
_038048B0:	.word	0x040001C2

	arm_func_start NVRAM_ReleaseFromDeepPowerDown
NVRAM_ReleaseFromDeepPowerDown: ;@ 0x038048B4
	ldr	r1, _038048EC	;@ =0x040001C0
_038048B8:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038048B8
	mov	r0, #33024	;@ 0x8100
	strh	r0, [r1]
	mov	r1, #171	;@ 0xab
	ldr	r0, _038048F0	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _038048EC	;@ =0x040001C0
_038048DC:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038048DC
	bx	lr
_038048EC:	.word	0x040001C0
_038048F0:	.word	0x040001C2

	arm_func_start NVRAM_DeepPowerDown
NVRAM_DeepPowerDown: ;@ 0x038048F4
	ldr	r1, _0380492C	;@ =0x040001C0
_038048F8:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038048F8
	mov	r0, #33024	;@ 0x8100
	strh	r0, [r1]
	mov	r1, #185	;@ 0xb9
	ldr	r0, _03804930	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _0380492C	;@ =0x040001C0
_0380491C:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_0380491C
	bx	lr
_0380492C:	.word	0x040001C0
_03804930:	.word	0x040001C2

	arm_func_start NVRAM_SectorErase
NVRAM_SectorErase: ;@ 0x03804934
	and	r1, r0, #16711680	;@ 0xff0000
	mov	r1, r1, lsr #16
	mov	r1, r1, lsl #16
	mov	r2, r1, lsr #16
	and	r1, r0, #65280	;@ 0xff00
	mov	r1, r1, lsl #8
	mov	r1, r1, lsr #16
	and	r0, r0, #255	;@ 0xff
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	ldr	ip, _038049F0	;@ =0x040001C0
_03804960:
	ldrh	r3, [ip]
	ands	r3, r3, #128	;@ 0x80
	bne	_03804960
	mov	r3, #35072	;@ 0x8900
	strh	r3, [ip]
	mov	ip, #216	;@ 0xd8
	ldr	r3, _038049F4	;@ =0x040001C2
	strh	ip, [r3]
	ldr	ip, _038049F0	;@ =0x040001C0
_03804984:
	ldrh	r3, [ip]
	ands	r3, r3, #128	;@ 0x80
	bne	_03804984
	and	r3, r2, #255	;@ 0xff
	ldr	r2, _038049F4	;@ =0x040001C2
	strh	r3, [r2]
	ldr	r3, _038049F0	;@ =0x040001C0
_038049A0:
	ldrh	r2, [r3]
	ands	r2, r2, #128	;@ 0x80
	bne	_038049A0
	and	r2, r1, #255	;@ 0xff
	ldr	r1, _038049F4	;@ =0x040001C2
	strh	r2, [r1]
	ldr	r2, _038049F0	;@ =0x040001C0
_038049BC:
	ldrh	r1, [r2]
	ands	r1, r1, #128	;@ 0x80
	bne	_038049BC
	mov	r1, #33024	;@ 0x8100
	strh	r1, [r2]
	and	r1, r0, #255	;@ 0xff
	ldr	r0, _038049F4	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _038049F0	;@ =0x040001C0
_038049E0:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_038049E0
	bx	lr
_038049F0:	.word	0x040001C0
_038049F4:	.word	0x040001C2

	arm_func_start NVRAM_PageErase
NVRAM_PageErase: ;@ 0x038049F8
	and	r1, r0, #16711680	;@ 0xff0000
	mov	r1, r1, lsr #16
	mov	r1, r1, lsl #16
	mov	r2, r1, lsr #16
	and	r1, r0, #65280	;@ 0xff00
	mov	r1, r1, lsl #8
	mov	r1, r1, lsr #16
	and	r0, r0, #255	;@ 0xff
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	ldr	ip, _03804AB4	;@ =0x040001C0
_03804A24:
	ldrh	r3, [ip]
	ands	r3, r3, #128	;@ 0x80
	bne	_03804A24
	mov	r3, #35072	;@ 0x8900
	strh	r3, [ip]
	mov	ip, #219	;@ 0xdb
	ldr	r3, _03804AB8	;@ =0x040001C2
	strh	ip, [r3]
	ldr	ip, _03804AB4	;@ =0x040001C0
_03804A48:
	ldrh	r3, [ip]
	ands	r3, r3, #128	;@ 0x80
	bne	_03804A48
	and	r3, r2, #255	;@ 0xff
	ldr	r2, _03804AB8	;@ =0x040001C2
	strh	r3, [r2]
	ldr	r3, _03804AB4	;@ =0x040001C0
_03804A64:
	ldrh	r2, [r3]
	ands	r2, r2, #128	;@ 0x80
	bne	_03804A64
	and	r2, r1, #255	;@ 0xff
	ldr	r1, _03804AB8	;@ =0x040001C2
	strh	r2, [r1]
	ldr	r2, _03804AB4	;@ =0x040001C0
_03804A80:
	ldrh	r1, [r2]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804A80
	mov	r1, #33024	;@ 0x8100
	strh	r1, [r2]
	and	r1, r0, #255	;@ 0xff
	ldr	r0, _03804AB8	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _03804AB4	;@ =0x040001C0
_03804AA4:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804AA4
	bx	lr
_03804AB4:	.word	0x040001C0
_03804AB8:	.word	0x040001C2

	arm_func_start NVRAM_PageProgram
NVRAM_PageProgram: ;@ 0x03804ABC
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	cmp	r1, #1
	bcc	_03804BD4
	add	r3, r0, r1
	sub	r3, r3, #1
	mov	r3, r3, lsr #8
	cmp	r3, r0, lsr #8
	andhi	r1, r0, #255	;@ 0xff
	rsbhi	r1, r1, #256	;@ 0x100
	movhi	r1, r1, lsl #16
	movhi	r1, r1, lsr #16
	and	r3, r0, #16711680	;@ 0xff0000
	mov	r3, r3, lsr #16
	strh	r3, [sp]
	and	r3, r0, #65280	;@ 0xff00
	mov	r3, r3, lsr #8
	strh	r3, [sp, #2]
	and	r0, r0, #255	;@ 0xff
	strh	r0, [sp, #4]
	ldr	r3, _03804BE0	;@ =0x040001C0
_03804B10:
	ldrh	r0, [r3]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804B10
	mov	r0, #35072	;@ 0x8900
	strh	r0, [r3]
	mov	r0, #2
	ldr	lr, _03804BE4	;@ =0x040001C2
	strh	r0, [lr]
	mov	r4, #0
	add	r3, sp, #0
	ldr	ip, _03804BE0	;@ =0x040001C0
_03804B3C:
	ldrh	r0, [ip]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804B3C
	mov	r0, r4, lsl #1
	ldrh	r0, [r3, r0]
	and	r0, r0, #255	;@ 0xff
	strh	r0, [lr]
	add	r4, r4, #1
	cmp	r4, #3
	blt	_03804B3C
	mov	ip, #0
	sub	lr, r1, #1
	ldr	r3, _03804BE0	;@ =0x040001C0
	ldr	r0, _03804BE4	;@ =0x040001C2
	b	_03804B94
_03804B78:
	ldrh	r1, [r3]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804B78
	ldrb	r1, [r2, ip]
	and	r1, r1, #255	;@ 0xff
	strh	r1, [r0]
	add	ip, ip, #1
_03804B94:
	cmp	ip, lr
	blt	_03804B78
	ldr	r1, _03804BE0	;@ =0x040001C0
_03804BA0:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804BA0
	mov	r0, #33024	;@ 0x8100
	strh	r0, [r1]
	ldrb	r0, [r2, ip]
	and	r1, r0, #255	;@ 0xff
	ldr	r0, _03804BE4	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _03804BE0	;@ =0x040001C0
_03804BC8:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804BC8
_03804BD4:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_03804BE0:	.word	0x040001C0
_03804BE4:	.word	0x040001C2

	arm_func_start NVRAM_PageWrite
NVRAM_PageWrite: ;@ 0x03804BE8
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	cmp	r1, #1
	bcc	_03804D00
	add	r3, r0, r1
	sub	r3, r3, #1
	mov	r3, r3, lsr #8
	cmp	r3, r0, lsr #8
	andhi	r1, r0, #255	;@ 0xff
	rsbhi	r1, r1, #256	;@ 0x100
	movhi	r1, r1, lsl #16
	movhi	r1, r1, lsr #16
	and	r3, r0, #16711680	;@ 0xff0000
	mov	r3, r3, lsr #16
	strh	r3, [sp]
	and	r3, r0, #65280	;@ 0xff00
	mov	r3, r3, lsr #8
	strh	r3, [sp, #2]
	and	r0, r0, #255	;@ 0xff
	strh	r0, [sp, #4]
	ldr	r3, _03804D0C	;@ =0x040001C0
_03804C3C:
	ldrh	r0, [r3]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804C3C
	mov	r0, #35072	;@ 0x8900
	strh	r0, [r3]
	mov	r0, #10
	ldr	lr, _03804D10	;@ =0x040001C2
	strh	r0, [lr]
	mov	r4, #0
	add	r3, sp, #0
	ldr	ip, _03804D0C	;@ =0x040001C0
_03804C68:
	ldrh	r0, [ip]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804C68
	mov	r0, r4, lsl #1
	ldrh	r0, [r3, r0]
	and	r0, r0, #255	;@ 0xff
	strh	r0, [lr]
	add	r4, r4, #1
	cmp	r4, #3
	blt	_03804C68
	mov	ip, #0
	sub	lr, r1, #1
	ldr	r3, _03804D0C	;@ =0x040001C0
	ldr	r0, _03804D10	;@ =0x040001C2
	b	_03804CC0
_03804CA4:
	ldrh	r1, [r3]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804CA4
	ldrb	r1, [r2, ip]
	and	r1, r1, #255	;@ 0xff
	strh	r1, [r0]
	add	ip, ip, #1
_03804CC0:
	cmp	ip, lr
	blt	_03804CA4
	ldr	r1, _03804D0C	;@ =0x040001C0
_03804CCC:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804CCC
	mov	r0, #33024	;@ 0x8100
	strh	r0, [r1]
	ldrb	r0, [r2, ip]
	and	r1, r0, #255	;@ 0xff
	ldr	r0, _03804D10	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _03804D0C	;@ =0x040001C0
_03804CF4:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804CF4
_03804D00:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_03804D0C:	.word	0x040001C0
_03804D10:	.word	0x040001C2

	arm_func_start NVRAM_ReadDataBytesAtHigherSpeed
NVRAM_ReadDataBytesAtHigherSpeed: ;@ 0x03804D14
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	cmp	r1, #1
	bcc	_03804E3C
	and	r3, r0, #16711680	;@ 0xff0000
	mov	r3, r3, lsr #16
	strh	r3, [sp]
	and	r3, r0, #65280	;@ 0xff00
	mov	r3, r3, lsr #8
	strh	r3, [sp, #2]
	and	r0, r0, #255	;@ 0xff
	strh	r0, [sp, #4]
	ldr	r3, _03804E48	;@ =0x040001C0
_03804D48:
	ldrh	r0, [r3]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804D48
	mov	r0, #35072	;@ 0x8900
	strh	r0, [r3]
	mov	r0, #11
	ldr	ip, _03804E4C	;@ =0x040001C2
	strh	r0, [ip]
	mov	lr, #0
	add	r3, sp, #0
	ldr	r4, _03804E48	;@ =0x040001C0
_03804D74:
	ldrh	r0, [r4]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804D74
	mov	r0, lr, lsl #1
	ldrh	r0, [r3, r0]
	and	r0, r0, #255	;@ 0xff
	strh	r0, [ip]
	add	lr, lr, #1
	cmp	lr, #3
	blt	_03804D74
	ldr	r3, _03804E48	;@ =0x040001C0
_03804DA0:
	ldrh	r0, [r3]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804DA0
	mov	r3, #0
	ldr	r0, _03804E4C	;@ =0x040001C2
	strh	r3, [r0]
	ldr	r3, _03804E48	;@ =0x040001C0
_03804DBC:
	ldrh	r0, [r3]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804DBC
	mov	r0, #0
	ldr	ip, _03804E48	;@ =0x040001C0
	mov	r4, r0
	ldr	lr, _03804E4C	;@ =0x040001C2
	sub	r1, r1, #1
	b	_03804E00
_03804DE0:
	strh	r4, [lr]
_03804DE4:
	ldrh	r3, [ip]
	ands	r3, r3, #128	;@ 0x80
	bne	_03804DE4
	ldrh	r3, [lr]
	and	r3, r3, #255	;@ 0xff
	strb	r3, [r2, r0]
	add	r0, r0, #1
_03804E00:
	cmp	r0, r1
	bcc	_03804DE0
	mov	r1, #33024	;@ 0x8100
	ldr	ip, _03804E48	;@ =0x040001C0
	strh	r1, [ip]
	mov	r3, #0
	ldr	r1, _03804E4C	;@ =0x040001C2
	strh	r3, [r1]
_03804E20:
	ldrh	r1, [ip]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804E20
	ldr	r1, _03804E4C	;@ =0x040001C2
	ldrh	r1, [r1]
	and	r1, r1, #255	;@ 0xff
	strb	r1, [r2, r0]
_03804E3C:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_03804E48:	.word	0x040001C0
_03804E4C:	.word	0x040001C2

	arm_func_start NVRAM_ReadDataBytes
NVRAM_ReadDataBytes: ;@ 0x03804E50
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	cmp	r1, #1
	bcc	_03804F5C
	and	r3, r0, #16711680	;@ 0xff0000
	mov	r3, r3, lsr #16
	strh	r3, [sp]
	and	r3, r0, #65280	;@ 0xff00
	mov	r3, r3, lsr #8
	strh	r3, [sp, #2]
	and	r0, r0, #255	;@ 0xff
	strh	r0, [sp, #4]
	ldr	r3, _03804F68	;@ =0x040001C0
_03804E84:
	ldrh	r0, [r3]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804E84
	mov	r0, #35072	;@ 0x8900
	strh	r0, [r3]
	mov	r0, #3
	ldr	ip, _03804F6C	;@ =0x040001C2
	strh	r0, [ip]
	mov	lr, #0
	add	r3, sp, #0
	ldr	r4, _03804F68	;@ =0x040001C0
_03804EB0:
	ldrh	r0, [r4]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804EB0
	mov	r0, lr, lsl #1
	ldrh	r0, [r3, r0]
	and	r0, r0, #255	;@ 0xff
	strh	r0, [ip]
	add	lr, lr, #1
	cmp	lr, #3
	blt	_03804EB0
	ldr	r3, _03804F68	;@ =0x040001C0
_03804EDC:
	ldrh	r0, [r3]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804EDC
	mov	r0, #0
	ldr	ip, _03804F68	;@ =0x040001C0
	mov	r4, r0
	ldr	lr, _03804F6C	;@ =0x040001C2
	sub	r1, r1, #1
	b	_03804F20
_03804F00:
	strh	r4, [lr]
_03804F04:
	ldrh	r3, [ip]
	ands	r3, r3, #128	;@ 0x80
	bne	_03804F04
	ldrh	r3, [lr]
	and	r3, r3, #255	;@ 0xff
	strb	r3, [r2, r0]
	add	r0, r0, #1
_03804F20:
	cmp	r0, r1
	bcc	_03804F00
	mov	r1, #33024	;@ 0x8100
	ldr	ip, _03804F68	;@ =0x040001C0
	strh	r1, [ip]
	mov	r3, #0
	ldr	r1, _03804F6C	;@ =0x040001C2
	strh	r3, [r1]
_03804F40:
	ldrh	r1, [ip]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804F40
	ldr	r1, _03804F6C	;@ =0x040001C2
	ldrh	r1, [r1]
	and	r1, r1, #255	;@ 0xff
	strb	r1, [r2, r0]
_03804F5C:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_03804F68:	.word	0x040001C0
_03804F6C:	.word	0x040001C2

	arm_func_start NVRAM_ReadStatusRegister
NVRAM_ReadStatusRegister: ;@ 0x03804F70
	ldr	r2, _03804FDC	;@ =0x040001C0
_03804F74:
	ldrh	r1, [r2]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804F74
	mov	r1, #35072	;@ 0x8900
	strh	r1, [r2]
	mov	r2, #5
	ldr	r1, _03804FE0	;@ =0x040001C2
	strh	r2, [r1]
	ldr	r2, _03804FDC	;@ =0x040001C0
_03804F98:
	ldrh	r1, [r2]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804F98
	mov	r1, #33024	;@ 0x8100
	strh	r1, [r2]
	mov	r2, #0
	ldr	r1, _03804FE0	;@ =0x040001C2
	strh	r2, [r1]
	ldr	r2, _03804FDC	;@ =0x040001C0
_03804FBC:
	ldrh	r1, [r2]
	ands	r1, r1, #128	;@ 0x80
	bne	_03804FBC
	ldr	r1, _03804FE0	;@ =0x040001C2
	ldrh	r1, [r1]
	and	r1, r1, #255	;@ 0xff
	strb	r1, [r0]
	bx	lr
_03804FDC:	.word	0x040001C0
_03804FE0:	.word	0x040001C2

	arm_func_start NVRAM_WriteDisable
NVRAM_WriteDisable: ;@ 0x03804FE4
	ldr	r1, _0380501C	;@ =0x040001C0
_03804FE8:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03804FE8
	mov	r0, #33024	;@ 0x8100
	strh	r0, [r1]
	mov	r1, #4
	ldr	r0, _03805020	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _0380501C	;@ =0x040001C0
_0380500C:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_0380500C
	bx	lr
_0380501C:	.word	0x040001C0
_03805020:	.word	0x040001C2

	arm_func_start NVRAM_WriteEnable
NVRAM_WriteEnable: ;@ 0x03805024
	ldr	r1, _0380505C	;@ =0x040001C0
_03805028:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_03805028
	mov	r0, #33024	;@ 0x8100
	strh	r0, [r1]
	mov	r1, #6
	ldr	r0, _03805060	;@ =0x040001C2
	strh	r1, [r0]
	ldr	r1, _0380505C	;@ =0x040001C0
_0380504C:
	ldrh	r0, [r1]
	ands	r0, r0, #128	;@ 0x80
	bne	_0380504C
	bx	lr
_0380505C:	.word	0x040001C0
_03805060:	.word	0x040001C2
