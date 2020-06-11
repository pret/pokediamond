	.include "asm/macros.inc"
	.include "global.inc"

    .section .bss

	.global _03809764
_03809764: ;0x03809764
	.space 0x03809774 - 0x03809764

    .section .text

	arm_func_start CARDi_SetWriteProtectCore
CARDi_SetWriteProtectCore: ; 0x03800034
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	sub	sp, sp, #8
	mov	r4, r0
	bl	CARDi_WaitPrevCommand
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
	ldr	r5, _038000CC	; =CARDi_CommWriteCore
	mov	r4, #5
_03800078:
	bl	CARDi_WriteEnable
	mov	r0, r8
	bl	CARDi_CommandBegin
	mov	r0, r7
	mov	r1, r6
	mov	r2, r8
	mov	r3, r5
	bl	CARDi_CommArray
	mov	r0, r4
	mov	r1, r6
	bl	CARDi_CommandEnd
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
_038000CC:	.word	CARDi_CommWriteCore

	arm_func_start CARDi_EraseChipCore
CARDi_EraseChipCore: ; 0x038000D0
	stmdb	sp!, {r4, lr}
	bl	CARDi_WaitPrevCommand
	cmp	r0, #0
	beq	_03800114
	ldr	r0, _0380011C	; =cardi_common
	ldr	r4, [r0]
	bl	CARDi_WriteEnable
	mov	r0, #1
	bl	CARDi_CommandBegin
	ldr	r0, _03800120	; =_038072BC
	mov	r1, #0
	mov	r2, #1
	ldr	r3, _03800124	; =CARDi_CommWriteCore
	bl	CARDi_CommArray
	ldr	r0, [r4, #52]	; 0x34
	ldr	r1, [r4, #56]	; 0x38
	bl	CARDi_CommandEnd
_03800114:
	ldmia	sp!, {r4, lr}
	bx	lr
_0380011C:	.word	cardi_common
_03800120:	.word	_038072BC
_03800124:	.word	CARDi_CommWriteCore

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
	bl	CARDi_WaitPrevCommand
	cmp	r0, #0
	beq	_038001B0
	mov	r8, #216	; 0xd8
	b	_038001A8
_0380016C:
	bl	CARDi_WriteEnable
	ldr	r0, [r5, #36]	; 0x24
	add	r0, r0, #1
	bl	CARDi_CommandBegin
	mov	r0, r7
	mov	r1, r8
	bl	CARDi_SendSpiAddressingCommand
	ldr	r0, [r5, #60]	; 0x3c
	ldr	r1, [r5, #64]	; 0x40
	bl	CARDi_CommandEnd
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
	bl	CARDi_WaitPrevCommand
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
	bl	CARDi_CommandBegin
	mov	r0, r7
	mov	r1, #3
	bl	CARDi_SendSpiAddressingCommand
	mov	r0, r6
	mov	r1, #0
	mov	r2, r5
	ldr	r3, _03800260	; =CARDi_CommVerifyCore
	bl	CARDi_CommArray
	mov	r0, #0
	mov	r1, r0
	bl	CARDi_CommandEnd
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
_03800260:	.word	CARDi_CommVerifyCore

	arm_func_start CARDi_WriteBackupCore
CARDi_WriteBackupCore: ; 0x03800264
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	r9, r1
	mov	r8, r2
	bl	CARDi_WaitPrevCommand
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
	bl	CARDi_WriteEnable
	ldr	r0, [r7, #36]	; 0x24
	add	r0, r0, #1
	add	r0, r0, r5
	bl	CARDi_CommandBegin
	mov	r0, sl
	mov	r1, fp
	bl	CARDi_SendSpiAddressingCommand
	mov	r0, r9
	ldr	r1, [sp]
	mov	r2, r5
	ldr	r3, _03800324	; =CARDi_CommWriteCore
	bl	CARDi_CommArray
	ldr	r0, [r7, #44]	; 0x2c
	ldr	r1, [r7, #48]	; 0x30
	bl	CARDi_CommandEnd
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
_03800324:	.word	CARDi_CommWriteCore

	arm_func_start CARDi_ProgramBackupCore
CARDi_ProgramBackupCore: ; 0x03800328
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	r9, r1
	mov	r8, r2
	bl	CARDi_WaitPrevCommand
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
	bl	CARDi_WriteEnable
	ldr	r0, [r7, #36]	; 0x24
	add	r0, r0, #1
	add	r0, r0, r5
	bl	CARDi_CommandBegin
	mov	r0, sl
	ldr	r1, [sp]
	bl	CARDi_SendSpiAddressingCommand
	mov	r0, r9
	mov	r1, fp
	mov	r2, r5
	ldr	r3, _038003E8	; =CARDi_CommWriteCore
	bl	CARDi_CommArray
	ldr	r0, [r7, #40]	; 0x28
	mov	r1, fp
	bl	CARDi_CommandEnd
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
_038003E8:	.word	CARDi_CommWriteCore

	arm_func_start CARDi_ReadBackupCore
CARDi_ReadBackupCore: ; 0x038003EC
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, r1
	mov	r4, r2
	bl	CARDi_WaitPrevCommand
	cmp	r0, #0
	beq	_0380044C
	ldr	r0, _03800454	; =cardi_common
	ldr	r0, [r0]
	ldr	r0, [r0, #36]	; 0x24
	add	r0, r0, #1
	add	r0, r0, r4
	bl	CARDi_CommandBegin
	mov	r0, r6
	mov	r1, #3
	bl	CARDi_SendSpiAddressingCommand
	mov	r0, #0
	mov	r1, r5
	mov	r2, r4
	ldr	r3, _03800458	; =CARDi_CommReadCore
	bl	CARDi_CommArray
	mov	r0, #0
	mov	r1, r0
	bl	CARDi_CommandEnd
_0380044C:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr
_03800454:	.word	cardi_common
_03800458:	.word	CARDi_CommReadCore

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
	bl	CARDi_CommandBegin
	add	r0, sp, #0
	mov	r1, #0
	mov	r2, #1
	ldr	r3, _03800500	; =CARDi_CommWriteCore
	bl	CARDi_CommArray
	mov	r0, #0
	add	r1, sp, #1
	mov	r2, #1
	ldr	r3, _03800504	; =CARDi_CommReadCore
	bl	CARDi_CommArray
	mov	r0, #0
	mov	r1, r0
	bl	CARDi_CommandEnd
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
_03800500:	.word	CARDi_CommWriteCore
_03800504:	.word	CARDi_CommReadCore

	arm_func_start CARDi_SendSpiAddressingCommand
CARDi_SendSpiAddressingCommand: ; 0x03800508
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
	ldr	r3, _038005B0	; =CARDi_CommWriteCore
	bl	CARDi_CommArray
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_038005AC:	.word	cardi_common
_038005B0:	.word	CARDi_CommWriteCore

	arm_func_start CARDi_WriteEnable
CARDi_WriteEnable: ; 0x038005B4
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #1
	bl	CARDi_CommandBegin
	ldr	r0, _038005F0	; =_038072C0
	mov	r1, #0
	mov	r2, #1
	ldr	r3, _038005F4	; =CARDi_CommWriteCore
	bl	CARDi_CommArray
	mov	r0, #0
	mov	r1, r0
	bl	CARDi_CommandEnd
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_038005F0:	.word	_038072C0
_038005F4:	.word	CARDi_CommWriteCore

	arm_func_start CARDi_CommVerifyCore
CARDi_CommVerifyCore: ; 0x038005F8
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

	arm_func_start CARDi_CommWriteCore
CARDi_CommWriteCore: ; 0x03800660
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

	arm_func_start CARDi_CommReadCore
CARDi_CommReadCore: ; 0x038006AC
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

	arm_func_start CARDi_CommArray
CARDi_CommArray: ; 0x038006F0
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

	arm_func_start CARDi_WaitPrevCommand
CARDi_WaitPrevCommand: ; 0x03800780
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #0
	mov	r1, #50	; 0x32
	bl	CARDi_CommandEnd
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

	arm_func_start CARDi_CommandCheckBusy
CARDi_CommandCheckBusy: ; 0x038007C4
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #2
	bl	CARDi_CommandBegin
	ldr	r0, _03800824	; =_038072C4
	mov	r1, #0
	mov	r2, #1
	ldr	r3, _03800828	; =CARDi_CommWriteCore
	bl	CARDi_CommArray
	mov	r0, #0
	add	r1, sp, #0
	mov	r2, #1
	ldr	r3, _0380082C	; =CARDi_CommReadCore
	bl	CARDi_CommArray
	mov	r0, #0
	mov	r1, r0
	bl	CARDi_CommandEnd
	ldrb	r0, [sp]
	ands	r0, r0, #1
	moveq	r0, #1
	movne	r0, #0
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03800824:	.word	_038072C4
_03800828:	.word	CARDi_CommWriteCore
_0380082C:	.word	CARDi_CommReadCore

	arm_func_start CARDi_CommandEnd
CARDi_CommandEnd: ; 0x03800830
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
	bl	CARDi_CommandCheckBusy
	cmp	r0, #0
	bne	_03800890
	cmp	r6, #0
	bgt	_03800864
_03800890:
	bl	CARDi_CommandCheckBusy
	cmp	r0, #0
	moveq	r1, #4
	ldreq	r0, _038008B0	; =cardi_common
	ldreq	r0, [r0]
	streq	r1, [r0]
_038008A8:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr
_038008B0:	.word	cardi_common

	arm_func_start CARDi_CommandBegin
CARDi_CommandBegin: ; 0x038008B4
	ldr	r1, _038008C0	; =_03809764
	str	r0, [r1]
	bx	lr
_038008C0:	.word	_03809764
