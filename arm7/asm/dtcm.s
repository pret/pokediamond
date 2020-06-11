	.include "asm/macros.inc"
	.include "global.inc"

	.section .text
	arm_func_start FS_Init
FS_Init: ; 0x037FFF14
	ldr	ip, _037FFF1C	; =CARD_Init
	bx	ip
_037FFF1C:	.word	CARD_Init

	arm_func_start CARD_GetRomHeader
CARD_GetRomHeader: ; 0x037FFF20
	ldr	r0, _037FFF28	; =0x027FFA80
	bx	lr
_037FFF28:	.word	0x027FFA80

	arm_func_start CARD_SetThreadPriority
CARD_SetThreadPriority: ; 0x037FFF2C
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	ldr	r6, _037FFF70	; =cardi_common
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r5, [r6, #240]	; 0xf0
	str	r7, [r6, #240]	; 0xf0
	add	r0, r6, #72	; 0x48
	ldr	r1, [r6, #240]	; 0xf0
	bl	OS_SetThreadPriority
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, r5
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FFF70:	.word	cardi_common

	arm_func_start CARD_Enable
CARD_Enable: ; 0x037FFF74
	ldr	r1, _037FFF80	; =_0380912C
	str	r0, [r1]
	bx	lr
_037FFF80:	.word	_0380912C

	arm_func_start CARDi_InitCommon
CARDi_InitCommon: ; 0x037FFF84
	stmfd	sp!, {lr}
	sub	sp, sp, #12
	mvn	r1, #2
	ldr	r0, _0380001C	; =cardi_common
	str	r1, [r0, #12]
	mov	r2, #0
	str	r2, [r0, #16]
	str	r2, [r0, #28]
	str	r2, [r0]
	str	r2, [r0, #8]
	str	r2, [r0, #24]
	str	r2, [r0, #20]
	str	r2, [r0, #248]	; 0xf8
	str	r2, [r0, #244]	; 0xf4
	mov	r1, #4
	str	r1, [r0, #240]	; 0xf0
	mov	r1, #1024	; 0x400
	str	r1, [sp]
	ldr	r0, [r0, #240]	; 0xf0
	str	r0, [sp, #4]
	ldr	r0, _03800020	; =_03809188
	ldr	r1, _03800024	; =CARDi_TaskThread
	ldr	r3, _03800028	; =_03809760
	bl	OS_CreateThread
	ldr	r0, _03800020	; =_03809188
	bl	OS_WakeupThreadDirect
	mov	r0, #11
	ldr	r1, _0380002C	; =CARDi_OnFifoRecv
	bl	PXI_SetFifoRecvCallback
	ldr	r0, _03800030	; =0x027FFC40
	ldrh	r0, [r0]
_03800000:
	cmp	r0, #2
	beq	_03800010
	mov	r0, #1
	bl	CARD_Enable
_03800010:
	add	sp, sp, #12
	ldmia	sp!, {lr}
	bx	lr
_0380001C:	.word	cardi_common
_03800020:	.word	_03809188
_03800024:	.word	CARDi_TaskThread
_03800028:	.word	_03809760
_0380002C:	.word	CARDi_OnFifoRecv
_03800030:	.word	0x027FFC40

	arm_func_start CARDi_SetWriteProtectCore
CARDi_SetWriteProtectCore: ; 0x03800034
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	sub	sp, sp, #8
	mov	r4, r0
	bl	FUN_03800780
	cmp	r0, #0
	beq	_038000BC
	ldr	r0, _038000C8	; =cardi_common
	ldr	sl, [r0]
	mov	r9, #10
	mov	r0, #1
	strb	r0, [sp]
	strb	r4, [sp, #1]
	mov	r8, #2
	add	r7, sp, #0
	mov	r6, #0
	ldr	r5, _038000CC	; =_03800660
	mov	r4, #5
_03800078:
	bl	FUN_038005B4
	mov	r0, r8
	bl	FUN_038008B4
	mov	r0, r7
	mov	r1, r6
	mov	r2, r8
	mov	r3, r5
	bl	FUN_038006F0
	mov	r0, r4
	mov	r1, r6
	bl	FUN_03800830
	ldr	r0, [sl]
	cmp	r0, #4
	bne	_038000BC
	sub	r9, r9, #1
	cmp	r9, #0
	bgt	_03800078
_038000BC:
	add	sp, sp, #8
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	bx	lr
_038000C8:	.word	cardi_common
_038000CC:	.word	_03800660

	arm_func_start CARDi_EraseChipCore
CARDi_EraseChipCore: ; 0x038000D0
	stmdb	sp!, {r4, lr}
	bl	FUN_03800780
	cmp	r0, #0
	beq	_03800114
	ldr	r0, _0380011C	; =cardi_common
	ldr	r4, [r0]
	bl	FUN_038005B4
	mov	r0, #1
	bl	FUN_038008B4
	ldr	r0, _03800120	; =_038072BC
	mov	r1, #0
	mov	r2, #1
	ldr	r3, _03800124	; =_03800660
	bl	FUN_038006F0
	ldr	r0, [r4, #52]	; 0x34
	ldr	r1, [r4, #56]	; 0x38
	bl	FUN_03800830
_03800114:
	ldmia	sp!, {r4, lr}
	bx	lr
_0380011C:	.word	cardi_common
_03800120:	.word	_038072BC
_03800124:	.word	_03800660

	arm_func_start CARDi_EraseBackupSectorCore
CARDi_EraseBackupSectorCore: ; 0x03800128
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r7, r0
	mov	r6, r1
	ldr	r0, _038001B8	; =cardi_common
	ldr	r5, [r0]
	ldr	r4, [r5, #28]
	sub	r1, r4, #1
	orr	r0, r7, r6
	ands	r0, r1, r0
	movne	r0, #2
	strne	r0, [r5]
	bne	_038001B0
	bl	FUN_03800780
	cmp	r0, #0
	beq	_038001B0
	mov	r8, #216	; 0xd8
	b	_038001A8
_0380016C:
	bl	FUN_038005B4
	ldr	r0, [r5, #36]	; 0x24
	add	r0, r0, #1
	bl	FUN_038008B4
	mov	r0, r7
	mov	r1, r8
	bl	FUN_03800508
	ldr	r0, [r5, #60]	; 0x3c
	ldr	r1, [r5, #64]	; 0x40
	bl	FUN_03800830
	ldr	r0, [r5]
	cmp	r0, #0
	bne	_038001B0
	add	r7, r7, r4
	sub	r6, r6, r4
_038001A8:
	cmp	r6, #0
	bne	_0380016C
_038001B0:
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_038001B8:	.word	cardi_common

	arm_func_start CARDi_VerifyBackupCore
CARDi_VerifyBackupCore: ; 0x038001BC
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r5, r2
	bl	FUN_03800780
	cmp	r0, #0
	beq	_0380024C
	ldr	r0, _03800258	; =cardi_common
	ldr	r4, [r0]
	mov	r1, #1
	ldr	r0, _0380025C	; =_03809764
	str	r1, [r0, #12]
	ldr	r0, [r4, #36]	; 0x24
	add	r0, r0, #1
	add	r0, r0, r5
	bl	FUN_038008B4
	mov	r0, r7
	mov	r1, #3
	bl	FUN_03800508
	mov	r0, r6
	mov	r1, #0
	mov	r2, r5
	ldr	r3, _03800260	; =_038005F8
	bl	FUN_038006F0
	mov	r0, #0
	mov	r1, r0
	bl	FUN_03800830
	ldr	r0, [r4]
	cmp	r0, #0
	bne	_0380024C
	ldr	r0, _0380025C	; =_03809764
	ldr	r0, [r0, #12]
	cmp	r0, #0
	moveq	r0, #1
	streq	r0, [r4]
_0380024C:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_03800258:	.word	cardi_common
_0380025C:	.word	_03809764
_03800260:	.word	_038005F8

	arm_func_start CARDi_WriteBackupCore
CARDi_WriteBackupCore: ; 0x03800264
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	r9, r1
	mov	r8, r2
	bl	FUN_03800780
	cmp	r0, #0
	beq	_03800314
	ldr	r0, _03800320	; =cardi_common
	ldr	r7, [r0]
	ldr	r6, [r7, #32]
	sub	r4, r6, #1
	mov	fp, #10
	mov	r0, #0
	str	r0, [sp]
	b	_0380030C
_038002A4:
	and	r0, sl, r4
	sub	r5, r6, r0
	cmp	r5, r8
	movhi	r5, r8
	bl	FUN_038005B4
	ldr	r0, [r7, #36]	; 0x24
	add	r0, r0, #1
	add	r0, r0, r5
	bl	FUN_038008B4
	mov	r0, sl
	mov	r1, fp
	bl	FUN_03800508
	mov	r0, r9
	ldr	r1, [sp]
	mov	r2, r5
	ldr	r3, _03800324	; =_03800660
	bl	FUN_038006F0
	ldr	r0, [r7, #44]	; 0x2c
	ldr	r1, [r7, #48]	; 0x30
	bl	FUN_03800830
	ldr	r0, [r7]
	cmp	r0, #0
	bne	_03800314
	add	r9, r9, r5
	add	sl, sl, r5
	sub	r8, r8, r5
_0380030C:
	cmp	r8, #0
	bne	_038002A4
_03800314:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_03800320:	.word	cardi_common
_03800324:	.word	_03800660

	arm_func_start CARDi_ProgramBackupCore
CARDi_ProgramBackupCore: ; 0x03800328
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	r9, r1
	mov	r8, r2
	bl	FUN_03800780
	cmp	r0, #0
	beq	_038003D8
	ldr	r0, _038003E4	; =cardi_common
	ldr	r7, [r0]
	ldr	r6, [r7, #32]
	sub	r4, r6, #1
	mov	r0, #2
	str	r0, [sp]
	mov	fp, #0
	b	_038003D0
_03800368:
	and	r0, sl, r4
	sub	r5, r6, r0
	cmp	r5, r8
	movhi	r5, r8
	bl	FUN_038005B4
	ldr	r0, [r7, #36]	; 0x24
	add	r0, r0, #1
	add	r0, r0, r5
	bl	FUN_038008B4
	mov	r0, sl
	ldr	r1, [sp]
	bl	FUN_03800508
	mov	r0, r9
	mov	r1, fp
	mov	r2, r5
	ldr	r3, _038003E8	; =_03800660
	bl	FUN_038006F0
	ldr	r0, [r7, #40]	; 0x28
	mov	r1, fp
	bl	FUN_03800830
	ldr	r0, [r7]
	cmp	r0, #0
	bne	_038003D8
	add	r9, r9, r5
	add	sl, sl, r5
	sub	r8, r8, r5
_038003D0:
	cmp	r8, #0
	bne	_03800368
_038003D8:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_038003E4:	.word	cardi_common
_038003E8:	.word	_03800660

	arm_func_start CARDi_ReadBackupCore
CARDi_ReadBackupCore: ; 0x038003EC
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, r1
	mov	r4, r2
	bl	FUN_03800780
	cmp	r0, #0
	beq	_0380044C
	ldr	r0, _03800454	; =cardi_common
	ldr	r0, [r0]
	ldr	r0, [r0, #36]	; 0x24
	add	r0, r0, #1
	add	r0, r0, r4
	bl	FUN_038008B4
	mov	r0, r6
	mov	r1, #3
	bl	FUN_03800508
	mov	r0, #0
	mov	r1, r5
	mov	r2, r4
	ldr	r3, _03800458	; =_038006AC
	bl	FUN_038006F0
	mov	r0, #0
	mov	r1, r0
	bl	FUN_03800830
_0380044C:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr
_03800454:	.word	cardi_common
_03800458:	.word	_038006AC

	arm_func_start CARDi_InitStatusRegister
CARDi_InitStatusRegister: ; 0x0380045C
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	ldr	r0, _038004F8	; =cardi_common
	ldr	r0, [r0]
	ldrb	r4, [r0, #72]	; 0x48
	cmp	r4, #255	; 0xff
	beq	_038004EC
	ldr	r0, _038004FC	; =_03809760
	ldr	r0, [r0]
	cmp	r0, #0
	bne	_038004EC
	mov	r0, #5
	strb	r0, [sp]
	mov	r0, #2
	bl	FUN_038008B4
	add	r0, sp, #0
	mov	r1, #0
	mov	r2, #1
	ldr	r3, _03800500	; =_03800660
	bl	FUN_038006F0
	mov	r0, #0
	add	r1, sp, #1
	mov	r2, #1
	ldr	r3, _03800504	; =_038006AC
	bl	FUN_038006F0
	mov	r0, #0
	mov	r1, r0
	bl	FUN_03800830
	ldrb	r0, [sp, #1]
	cmp	r0, r4
	beq	_038004E0
	mov	r0, r4
	bl	CARDi_SetWriteProtectCore
_038004E0:
	mov	r1, #1
	ldr	r0, _038004FC	; =_03809760
	str	r1, [r0]
_038004EC:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_038004F8:	.word	cardi_common
_038004FC:	.word	_03809760
_03800500:	.word	_03800660
_03800504:	.word	_038006AC

	arm_func_start FUN_03800508
FUN_03800508: ; 0x03800508
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r2, _038005AC	; =cardi_common
	ldr	r2, [r2]
	ldr	r2, [r2, #36]	; 0x24
	cmp	r2, #1
	beq	_03800538
	cmp	r2, #2
	beq	_03800554
	cmp	r2, #3
	beq	_0380056C
	b	_0380058C
_03800538:
	and	r3, r0, #255	; 0xff
	mov	r0, r0, lsr #5
	and	r0, r0, #8
	orr	r0, r1, r0
	orr	r0, r0, r3, lsl #8
	str	r0, [sp]
	b	_0380058C
_03800554:
	and	r3, r0, #255	; 0xff
	and	r0, r0, #65280	; 0xff00
	orr	r0, r1, r0
	orr	r0, r0, r3, lsl #16
	str	r0, [sp]
	b	_0380058C
_0380056C:
	and	ip, r0, #255	; 0xff
	and	r3, r0, #65280	; 0xff00
	mov	r0, r0, lsr #8
	and	r0, r0, #65280	; 0xff00
	orr	r0, r1, r0
	orr	r0, r0, r3, lsl #8
	orr	r0, r0, ip, lsl #24
	str	r0, [sp]
_0380058C:
	add	r0, sp, #0
	mov	r1, #0
	add	r2, r2, #1
	ldr	r3, _038005B0	; =_03800660
	bl	FUN_038006F0
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_038005AC:	.word	cardi_common
_038005B0:	.word	_03800660

	arm_func_start FUN_038005B4
FUN_038005B4: ; 0x038005B4
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #1
	bl	FUN_038008B4
	ldr	r0, _038005F0	; =_038072C0
	mov	r1, #0
	mov	r2, #1
	ldr	r3, _038005F4	; =_03800660
	bl	FUN_038006F0
	mov	r0, #0
	mov	r1, r0
	bl	FUN_03800830
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_038005F0:	.word	_038072C0
_038005F4:	.word	_03800660
_038005F8:
	mov	r2, #0
	ldr	r1, _03800658	; =0x040001A2
	strh	r2, [r1]
	ldr	r2, _0380065C	; =0x040001A0
_03800608:
	ldrh	r1, [r2]
	ands	r1, r1, #128	; 0x80
	bne	_03800608
	ldr	r1, _03800658	; =0x040001A2
	ldrh	r1, [r1]
	and	r2, r1, #255	; 0xff
	ldr	r1, [r0, #4]
	ldrb	r1, [r1]
	cmp	r2, r1
	beq	_03800648
	mov	r1, #0
	str	r1, [r0, #12]
	ldr	r1, [r0]
	cmp	r1, #1
	movhi	r1, #1
	strhi	r1, [r0]
_03800648:
	ldr	r1, [r0, #4]
	add	r1, r1, #1
	str	r1, [r0, #4]
	bx	lr
_03800658:	.word	0x040001A2
_0380065C:	.word	0x040001A0
_03800660:
	sub	sp, sp, #8
	ldr	r1, [r0, #4]
	ldrb	r2, [r1]
	ldr	r1, _038006A4	; =0x040001A2
	strh	r2, [r1]
	ldr	r1, [r0, #4]
	add	r1, r1, #1
	str	r1, [r0, #4]
	ldr	r1, _038006A8	; =0x040001A0
_03800684:
	ldrh	r0, [r1]
	ands	r0, r0, #128	; 0x80
	bne	_03800684
	ldr	r0, _038006A4	; =0x040001A2
	ldrh	r0, [r0]
	strh	r0, [sp]
	add	sp, sp, #8
	bx	lr
_038006A4:	.word	0x040001A2
_038006A8:	.word	0x040001A0
_038006AC:
	mov	r2, #0
	ldr	r1, _038006E8	; =0x040001A2
	strh	r2, [r1]
	ldr	r2, _038006EC	; =0x040001A0
_038006BC:
	ldrh	r1, [r2]
	ands	r1, r1, #128	; 0x80
	bne	_038006BC
	ldr	r1, _038006E8	; =0x040001A2
	ldrh	r2, [r1]
	ldr	r1, [r0, #8]
	strb	r2, [r1]
	ldr	r1, [r0, #8]
	add	r1, r1, #1
	str	r1, [r0, #8]
	bx	lr
_038006E8:	.word	0x040001A2
_038006EC:	.word	0x040001A0

	arm_func_start FUN_038006F0
FUN_038006F0: ; 0x038006F0
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r7, r2
	mov	r6, r3
	ldr	r5, _03800774	; =_03809764
	str	r0, [r5, #4]
	str	r1, [r5, #8]
	ldr	r0, _03800778	; =0x0000A040
	ldr	r4, _0380077C	; =0x040001A0
	strh	r0, [r4]
	mov	r8, #40960	; 0xa000
	b	_03800750
_0380071C:
	ldr	r0, [r5]
	sub	r0, r0, #1
	str	r0, [r5]
	ldr	r0, [r5]
	cmp	r0, #0
	streqh	r8, [r4]
_03800734:
	ldrh	r0, [r4]
	ands	r0, r0, #128	; 0x80
	bne	_03800734
	mov	r0, r5
	mov	lr, pc
	bx	r6
	sub	r7, r7, #1
_03800750:
	cmp	r7, #0
	bne	_0380071C
	ldr	r0, [r5]
	cmp	r0, #0
	moveq	r1, #0
	ldreq	r0, _0380077C	; =0x040001A0
	streqh	r1, [r0]
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_03800774:	.word	_03809764
_03800778:	.word	0x0000A040
_0380077C:	.word	0x040001A0

	arm_func_start FUN_03800780
FUN_03800780: ; 0x03800780
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #0
	mov	r1, #50	; 0x32
	bl	FUN_03800830
	ldr	r0, _038007C0	; =cardi_common
	ldr	r1, [r0]
	ldr	r0, [r1]
	cmp	r0, #4
	moveq	r0, #6
	streq	r0, [r1]
	moveq	r0, #0
	movne	r0, #1
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_038007C0:	.word	cardi_common

	arm_func_start FUN_038007C4
FUN_038007C4: ; 0x038007C4
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #2
	bl	FUN_038008B4
	ldr	r0, _03800824	; =_038072C4
	mov	r1, #0
	mov	r2, #1
	ldr	r3, _03800828	; =_03800660
	bl	FUN_038006F0
	mov	r0, #0
	add	r1, sp, #0
	mov	r2, #1
	ldr	r3, _0380082C	; =_038006AC
	bl	FUN_038006F0
	mov	r0, #0
	mov	r1, r0
	bl	FUN_03800830
	ldrb	r0, [sp]
	ands	r0, r0, #1
	moveq	r0, #1
	movne	r0, #0
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03800824:	.word	_038072C4
_03800828:	.word	_03800660
_0380082C:	.word	_038006AC

	arm_func_start FUN_03800830
FUN_03800830: ; 0x03800830
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r5, r0
	mov	r4, r1
	adds	r1, r5, r4
	beq	_038008A8
	cmp	r5, #0
	beq	_03800850
	bl	OS_Sleep
_03800850:
	cmp	r4, #0
	beq	_03800890
	sub	r6, r4, r5
	mov	r4, #5
	b	_0380087C
_03800864:
	cmp	r6, #5
	movlt	r5, r6
	movge	r5, r4
	mov	r0, r5
	bl	OS_Sleep
	sub	r6, r6, r5
_0380087C:
	bl	FUN_038007C4
	cmp	r0, #0
	bne	_03800890
	cmp	r6, #0
	bgt	_03800864
_03800890:
	bl	FUN_038007C4
	cmp	r0, #0
	moveq	r1, #4
	ldreq	r0, _038008B0	; =cardi_common
	ldreq	r0, [r0]
	streq	r1, [r0]
_038008A8:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr
_038008B0:	.word	cardi_common

	arm_func_start FUN_038008B4
FUN_038008B4: ; 0x038008B4
	ldr	r1, _038008C0	; =_03809764
	str	r0, [r1]
	bx	lr
_038008C0:	.word	_03809764

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
	bl	FUN_03800A80
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

	arm_func_start FUN_03800A80
FUN_03800A80: ; 0x03800A80
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

	arm_func_start CARDi_TaskThread
CARDi_TaskThread: ; 0x03800B20
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	ldr	r9, _03800D28	; =cardi_common
	add	r5, r9, #72	; 0x48
	mov	r8, #0
	add	r7, r9, #252	; 0xfc
	mov	r6, #1
	mov	r4, #3
	mov	fp, #11
_03800B44:
	mov	sl, r8
	bl	OS_DisableInterrupts
	str	r0, [sp]
_03800B50:
	ldr	r0, [r9, #252]	; 0xfc
	ands	r0, r0, #4
	bne	_03800B88
	ldr	r0, [r9, #252]	; 0xfc
	ands	r0, r0, #16
	beq	_03800B94
	ldr	r0, [r7]
	orr	r0, r0, #4
	str	r0, [r7]
	ldr	r0, [r7]
	bic	r0, r0, #16
	str	r0, [r7]
	mov	sl, r6
	b	_03800BA4
_03800B88:
	ldr	r0, [r9, #252]	; 0xfc
	ands	r0, r0, #8
	bne	_03800BA4
_03800B94:
	str	r5, [r9, #236]	; 0xec
	mov	r0, r8
	bl	OS_SleepThread
	b	_03800B50
_03800BA4:
	ldr	r0, [sp]
	bl	OS_RestoreInterrupts
	cmp	sl, #0
	beq	_03800D14
	ldr	r0, [r9]
	str	r8, [r0]
	ldr	r2, [r9]
	ldr	r1, [r2, #76]	; 0x4c
	ldr	r0, [r9, #4]
	mov	r0, r6, lsl r0
	ands	r0, r1, r0
	streq	r4, [r2]
	ldr	r0, [r9, #4]
	cmp	r0, #12
	addls	pc, pc, r0, lsl #2
	b	_03800CB8
	b	_03800CC0
	b	_03800CC0
	b	_03800C18
	b	_03800C20
	b	_03800C30
	b	_03800CB8
	b	_03800C3C
	b	_03800C54
	b	_03800C6C
	b	_03800C84
	b	_03800CB8
	b	_03800C9C
	b	_03800CB0
_03800C18:
	bl	CARDi_InitStatusRegister
	b	_03800CC0
_03800C20:
	bl	CARDi_ReadRomIDCore
	ldr	r1, [r9]
	str	r0, [r1, #8]
	b	_03800CC0
_03800C30:
	ldr	r0, [r9]
	str	r4, [r0]
	b	_03800CC0
_03800C3C:
	ldr	r2, [r9]
	ldr	r0, [r2, #12]
	ldr	r1, [r2, #16]
	ldr	r2, [r2, #20]
	bl	CARDi_ReadBackupCore
	b	_03800CC0
_03800C54:
	ldr	r2, [r9]
	ldr	r0, [r2, #16]
	ldr	r1, [r2, #12]
	ldr	r2, [r2, #20]
	bl	CARDi_WriteBackupCore
	b	_03800CC0
_03800C6C:
	ldr	r2, [r9]
	ldr	r0, [r2, #16]
	ldr	r1, [r2, #12]
	ldr	r2, [r2, #20]
	bl	CARDi_ProgramBackupCore
	b	_03800CC0
_03800C84:
	ldr	r2, [r9]
	ldr	r0, [r2, #16]
	ldr	r1, [r2, #12]
	ldr	r2, [r2, #20]
	bl	CARDi_VerifyBackupCore
	b	_03800CC0
_03800C9C:
	ldr	r1, [r9]
	ldr	r0, [r1, #16]
	ldr	r1, [r1, #20]
	bl	CARDi_EraseBackupSectorCore
	b	_03800CC0
_03800CB0:
	bl	CARDi_EraseChipCore
	b	_03800CC0
_03800CB8:
	ldr	r0, [r9]
	str	r4, [r0]
_03800CC0:
	mov	r0, fp
	mov	r1, r6
	mov	r2, r6
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	blt	_03800CC0
	bl	OS_DisableInterrupts
	mov	sl, r0
	ldr	r0, [r9, #252]	; 0xfc
	bic	r0, r0, #76	; 0x4c
	str	r0, [r9, #252]	; 0xfc
	add	r0, r9, #244	; 0xf4
	bl	OS_WakeupThread
	ldr	r0, [r9, #252]	; 0xfc
	ands	r0, r0, #16
	beq	_03800D08
	mov	r0, r5
	bl	OS_WakeupThreadDirect
_03800D08:
	mov	r0, sl
	bl	OS_RestoreInterrupts
	b	_03800B44
_03800D14:
	mov	r0, r9
	ldr	r1, [r9, #68]	; 0x44
	mov	lr, pc
	bx	r1
	b	_03800B44
_03800D28:	.word	cardi_common

	arm_func_start CARDi_OnFifoRecv
CARDi_OnFifoRecv: ; 0x03800D2C
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	cmp	r0, #11
	bne	_03800DFC
	cmp	r2, #0
	beq	_03800DFC
	ldr	r0, _03800E08	; =cardi_common
	ldr	r2, [r0, #8]
	cmp	r2, #0
	streq	r1, [r0, #4]
	ldr	r2, [r0, #4]
	cmp	r2, #12
	addls	pc, pc, r2, lsl #2
	b	_03800DC8
	b	_03800D98
	b	_03800DC8
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
_03800D98:
	ldr	r2, [r0, #8]
	cmp	r2, #0
	beq	_03800DC8
	cmp	r2, #1
	streq	r1, [r0]
	ldreq	r1, [r0, #252]	; 0xfc
	orreq	r1, r1, #16
	streq	r1, [r0, #252]	; 0xfc
	b	_03800DC8
_03800DBC:
	ldr	r1, [r0, #252]	; 0xfc
	orr	r1, r1, #16
	str	r1, [r0, #252]	; 0xfc
_03800DC8:
	ldr	r1, [r0, #252]	; 0xfc
	ands	r1, r1, #16
	ldreq	r1, [r0, #8]
	addeq	r1, r1, #1
	streq	r1, [r0, #8]
	beq	_03800DFC
	mov	r1, #0
	str	r1, [r0, #8]
	ldr	r1, [r0, #252]	; 0xfc
	ands	r1, r1, #4
	ldrne	r0, [r0, #236]	; 0xec
	addeq	r0, r0, #72	; 0x48
	bl	OS_WakeupThreadDirect
_03800DFC:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03800E08:	.word	cardi_common

	arm_func_start FUN_03800E0C
FUN_03800E0C: ; 0x03800E0C
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r5, #14
	mov	r4, #0
	b	_03800E30
_03800E28:
	mov	r0, r6
	bl	FUN_037F8CB4
_03800E30:
	mov	r0, r5
	mov	r1, r7
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	bne	_03800E28
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr

	arm_func_start FUN_03800E54
FUN_03800E54: ; 0x03800E54
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #0
	bl	CTRDG_VibPulseEdgeUpdate
	bl	SND_BeginSleep
	bl	WVR_Shutdown
	bl	OS_Terminate
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start CARD_CheckPullOut_Polling
CARD_CheckPullOut_Polling: ; 0x03800E7C
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _03800F50	; =_038099A0
	ldr	r0, [r0]
	cmp	r0, #0
	bne	_03800F44
	ldr	r0, _03800F54	; =0x027FFC40
	ldrh	r0, [r0]
	cmp	r0, #2
	beq	_03800F44
	ldr	r1, _03800F58	; =_03807668
	ldr	r3, [r1]
	mvn	r0, #0
	cmp	r3, r0
	ldreq	r0, _03800F5C	; =0x027FFC3C
	ldreq	r0, [r0]
	addeq	r0, r0, #10
	streq	r0, [r1]
	beq	_03800F44
	ldr	r2, _03800F5C	; =0x027FFC3C
	ldr	r0, [r2]
	cmp	r0, r3
	bcc	_03800F44
	ldr	r0, [r2]
	add	r0, r0, #10
	str	r0, [r1]
	bl	CARD_IsPulledOut
	cmp	r0, #0
	beq	_03800F1C
	mov	r1, #1
	ldr	r0, _03800F50	; =_038099A0
	str	r1, [r0]
	bl	CARD_GetRomHeader
	ldr	r0, [r0, #12]
	cmp	r0, #0
	bne	_03800F1C
	ldr	r0, _03800F60	; =_0380766C
	ldr	r0, [r0]
	cmp	r0, #0
	bne	_03800F44
_03800F1C:
	mov	r1, #0
	ldr	r0, _03800F60	; =_0380766C
	str	r1, [r0]
	ldr	r0, _03800F50	; =_038099A0
	ldr	r0, [r0]
	cmp	r0, #0
	beq	_03800F44
	mov	r0, #17
	mov	r1, #100	; 0x64
	bl	FUN_03800E0C
_03800F44:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03800F50:	.word	_038099A0
_03800F54:	.word	0x027FFC40
_03800F58:	.word	_03807668
_03800F5C:	.word	0x027FFC3C
_03800F60:	.word	_0380766C

	arm_func_start CARD_IsCardIreqLo
CARD_IsCardIreqLo: ; 0x03800F64
	mov	r2, #1
	mov	r0, r2
	ldr	r1, _03800F88	; =0x04000214
	ldr	r1, [r1]
	ands	r1, r1, #1048576	; 0x100000
	movne	r0, #0
	ldrne	r1, _03800F8C	; =_038099A8
	strne	r2, [r1]
	bx	lr
_03800F88:	.word	0x04000214
_03800F8C:	.word	_038099A8

	arm_func_start CARD_CompareCardID
CARD_CompareCardID: ; 0x03800F90
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _03800FE8	; =0x027FFC10
	ldrh	r0, [r0]
	cmp	r0, #0
	ldreq	r0, _03800FEC	; =0x027FF800
	ldrne	r0, _03800FF0	; =0x027FFC00
	ldr	r0, [r0]
	str	r0, [sp]
	bl	CARDi_ReadRomID
	ldr	r1, [sp]
	cmp	r0, r1
	moveq	r0, #1
	movne	r0, #0
	cmp	r0, #0
	moveq	r2, #1
	movne	r2, #0
	ldr	r1, _03800FF4	; =_038099A8
	str	r2, [r1]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03800FE8:	.word	0x027FFC10
_03800FEC:	.word	0x027FF800
_03800FF0:	.word	0x027FFC00
_03800FF4:	.word	_038099A8

	arm_func_start CARD_IsPulledOut
CARD_IsPulledOut: ; 0x03800FF8
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _03801040	; =_038099A8
	ldr	r0, [r0]
	cmp	r0, #0
	bne	_0380102C
	ldr	r0, _03801044	; =0x027FFC1F
	ldrb	r0, [r0]
	ands	r0, r0, #1
	beq	_03801028
	bl	CARD_CompareCardID
	b	_0380102C
_03801028:
	bl	CARD_IsCardIreqLo
_0380102C:
	ldr	r0, _03801040	; =_038099A8
	ldr	r0, [r0]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03801040:	.word	_038099A8
_03801044:	.word	0x027FFC1F

	arm_func_start FUN_03801048
FUN_03801048: ; 0x03801048
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	and	r0, r1, #63	; 0x3f
	cmp	r0, #1
	bne	_03801064
	bl	FUN_03800E54
	b	_03801068
_03801064:
	bl	OS_Terminate
_03801068:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start CARD_InitPulledOutCallback
CARD_InitPulledOutCallback: ; 0x03801074
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	ldr	r0, _038010CC	; =_038099A4
	ldr	r1, [r0]
	cmp	r1, #0
	bne	_038010C0
	mov	r1, #1
	str	r1, [r0]
	bl	PXI_Init
	mov	r5, #14
	mov	r4, #0
_038010A0:
	mov	r0, r5
	mov	r1, r4
	bl	PXI_IsCallbackReady
	cmp	r0, #0
	beq	_038010A0
	mov	r0, #14
	ldr	r1, _038010D0	; =FUN_03801048
	bl	PXI_SetFifoRecvCallback
_038010C0:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_038010CC:	.word	_038099A4
_038010D0:	.word	FUN_03801048
	.balign 2, 0 ; Don't pad with nop
