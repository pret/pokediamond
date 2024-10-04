	.include	"asm/macros.inc"
	.include	"global.inc"

    .extern WL_GetThreadStruct
    .extern WL_InitDriver
    .extern WMSP_IndicateThread
    .extern WMSP_RequestThread
    .extern WMSP_WL_ParamSetAll

	.section	.text
	.balign	4, 0

	arm_func_start WMSP_SetChildSize
WMSP_SetChildSize: ; 0x06000000
	ldr	r1, _0600002C	; =wmspW + 0x1000
	ldr	r2, [r1, #1360]	; 0x550
	strh	r0, [r2, #50]	; 0x32
	add	r1, r2, #256	; 0x100
	ldrh	r1, [r1, #136]	; 0x88
	cmp	r1, #0
	addeq	r0, r0, #2
	streqh	r0, [r2, #58]	; 0x3a
	addne	r0, r0, #2
	strneh	r0, [r2, #56]	; 0x38
	bx	lr
_0600002C:	.word	wmspW + 0x1000

	arm_func_start WMSP_SetParentSize
WMSP_SetParentSize: ; 0x06000030
	ldr	r1, _0600005C	; =wmspW + 0x1000
	ldr	r2, [r1, #1360]	; 0x550
	strh	r0, [r2, #48]	; 0x30
	add	r1, r2, #256	; 0x100
	ldrh	r1, [r1, #136]	; 0x88
	cmp	r1, #0
	addeq	r0, r0, #4
	streqh	r0, [r2, #56]	; 0x38
	addne	r0, r0, #4
	strneh	r0, [r2, #58]	; 0x3a
	bx	lr
_0600005C:	.word	wmspW + 0x1000

	arm_func_start WMSP_SetChildMaxSize
WMSP_SetChildMaxSize: ; 0x06000060
	ldr	r1, _060000AC	; =wmspW + 0x1000
	ldr	r2, [r1, #1360]	; 0x550
	strh	r0, [r2, #54]	; 0x36
	strh	r0, [r2, #50]	; 0x32
	add	r1, r2, #256	; 0x100
	ldrh	r1, [r1, #136]	; 0x88
	cmp	r1, #0
	addne	r0, r0, #2
	movne	r0, r0, lsl #16
	movne	r0, r0, lsr #16
	strneh	r0, [r2, #60]	; 0x3c
	strneh	r0, [r2, #56]	; 0x38
	bxne	lr
	add	r0, r0, #2
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	strh	r0, [r2, #62]	; 0x3e
	strh	r0, [r2, #58]	; 0x3a
	bx	lr
_060000AC:	.word	wmspW + 0x1000

	arm_func_start WMSP_SetParentMaxSize
WMSP_SetParentMaxSize: ; 0x060000B0
	ldr	r1, _060000FC	; =wmspW + 0x1000
	ldr	r2, [r1, #1360]	; 0x550
	strh	r0, [r2, #48]	; 0x30
	strh	r0, [r2, #52]	; 0x34
	add	r1, r2, #256	; 0x100
	ldrh	r1, [r1, #136]	; 0x88
	cmp	r1, #0
	addne	r0, r0, #4
	movne	r0, r0, lsl #16
	movne	r0, r0, lsr #16
	strneh	r0, [r2, #62]	; 0x3e
	strneh	r0, [r2, #58]	; 0x3a
	bxne	lr
	add	r0, r0, #4
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	strh	r0, [r2, #60]	; 0x3c
	strh	r0, [r2, #56]	; 0x38
	bx	lr
_060000FC:	.word	wmspW + 0x1000

	arm_func_start WMSP_ResetSizeVars
WMSP_ResetSizeVars: ; 0x06000100
	ldr	r0, _06000130	; =wmspW + 0x1000
	ldr	r1, [r0, #1360]	; 0x550
	mov	r0, #0
	strh	r0, [r1, #56]	; 0x38
	strh	r0, [r1, #58]	; 0x3a
	strh	r0, [r1, #48]	; 0x30
	strh	r0, [r1, #50]	; 0x32
	strh	r0, [r1, #60]	; 0x3c
	strh	r0, [r1, #62]	; 0x3e
	strh	r0, [r1, #52]	; 0x34
	strh	r0, [r1, #54]	; 0x36
	bx	lr
_06000130:	.word	wmspW + 0x1000

	arm_func_start WMSP_GetInternalRequestBuf
WMSP_GetInternalRequestBuf: ; 0x06000134
	stmdb	sp!, {r4, lr}
	mov	r4, #0
	bl	sub_060001A4
	ldr	r1, _060001A0	; =wmspW + 0x1000
	ldr	r2, [r1, #1356]	; 0x54c
	cmp	r2, #0
	beq	_06000190
	mov	ip, r4
	b	_06000188
_06000158:
	mov	r3, ip, lsl #4
	add	r1, r2, ip, lsl #4
	ldr	r1, [r1, #208]	; 0xd0
	ands	r1, r1, #32768	; 0x8000
	beq	_06000184
	add	r2, r2, #208	; 0xd0
	add	r4, r2, r3
	ldr	r1, [r2, r3]
	bic	r1, r1, #32768	; 0x8000
	str	r1, [r2, r3]
	b	_06000190
_06000184:
	add	ip, ip, #1
_06000188:
	cmp	ip, #32
	blt	_06000158
_06000190:
	bl	sub_060001AC
	mov	r0, r4
	ldmia	sp!, {r4, lr}
	bx	lr
_060001A0:	.word	wmspW + 0x1000

	arm_func_start sub_060001A4
sub_060001A4: ; 0x060001A4
	ldr	pc, _060001A8	; =OS_DisableInterrupts
_060001A8:	.word	OS_DisableInterrupts

	arm_func_start sub_060001AC
sub_060001AC: ; 0x060001AC
	ldr	pc, _060001B0	; =OS_RestoreInterrupts
_060001B0:	.word	OS_RestoreInterrupts

	arm_func_start sub_060001B4
sub_060001B4: ; 0x060001B4
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, r1
	mov	r4, r2
	bl	sub_060001E8
	strh	r6, [r0]
	mov	r1, #1
	strh	r1, [r0, #2]
	strh	r5, [r0, #4]
	strh	r4, [r0, #6]
	bl	sub_060001F0
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start sub_060001E8
sub_060001E8: ; 0x060001E8
	ldr	pc, _060001EC	; =WMSP_GetBuffer4Callback2Wm9
_060001EC:	.word	WMSP_GetBuffer4Callback2Wm9

	arm_func_start sub_060001F0
sub_060001F0: ; 0x060001F0
	ldr	pc, _060001F4	; =WMSP_ReturnResult2Wm9
_060001F4:	.word	WMSP_ReturnResult2Wm9

	arm_func_start WMSP_GetIndicateThread
WMSP_GetIndicateThread: ; 0x060001F8
	ldr	r0, _06000200	; =_0380B808
	bx	lr
_06000200:	.word	_0380B808

	arm_func_start WMSP_GetRequestThread
WMSP_GetRequestThread: ; 0x06000204
	ldr	r0, _0600020C	; =_0380B764
	bx	lr
_0600020C:	.word	_0380B764

	arm_func_start WMSP_SetThreadPriorityHigh
WMSP_SetThreadPriorityHigh: ; 0x06000210
	stmdb	sp!, {r4, lr}
	bl	sub_060001A4
	mov	r4, r0
	bl	sub_06000270
	ldr	r0, _06000264	; =_0380B808
	ldr	r1, _06000268	; =wmspW + 0x1000
	ldr	r1, [r1, #1400]	; 0x578
	bl	sub_06000278
	bl	WL_GetThreadStruct
	ldr	r1, _06000268	; =wmspW + 0x1000
	ldr	r1, [r1, #1404]	; 0x57c
	bl	sub_06000278
	ldr	r0, _0600026C	; =_0380B764
	ldr	r1, _06000268	; =wmspW + 0x1000
	ldr	r1, [r1, #1408]	; 0x580
	bl	sub_06000278
	bl	sub_06000280
	mov	r0, r4
	bl	sub_060001AC
	ldmia	sp!, {r4, lr}
	bx	lr
_06000264:	.word	_0380B808
_06000268:	.word	wmspW + 0x1000
_0600026C:	.word	_0380B764

	arm_func_start sub_06000270
sub_06000270: ; 0x06000270
	ldr	pc, _06000274	; =OS_DisableScheduler
_06000274:	.word	OS_DisableScheduler

	arm_func_start sub_06000278
sub_06000278: ; 0x06000278
	ldr	pc, _0600027C	; =OS_SetThreadPriority
_0600027C:	.word	OS_SetThreadPriority

	arm_func_start sub_06000280
sub_06000280: ; 0x06000280
	ldr	pc, _06000284	; =OS_EnableScheduler
_06000284:	.word	OS_EnableScheduler

	arm_func_start WMSP_SetThreadPriorityLow
WMSP_SetThreadPriorityLow: ; 0x06000288
	stmdb	sp!, {r4, lr}
	bl	sub_060001A4
	mov	r4, r0
	bl	sub_06000270
	ldr	r0, _060002DC	; =_0380B764
	ldr	r1, _060002E0	; =wmspW + 0x1000
	ldr	r1, [r1, #1420]	; 0x58c
	bl	sub_06000278
	bl	WL_GetThreadStruct
	ldr	r1, _060002E0	; =wmspW + 0x1000
	ldr	r1, [r1, #1416]	; 0x588
	bl	sub_06000278
	ldr	r0, _060002E4	; =_0380B808
	ldr	r1, _060002E0	; =wmspW + 0x1000
	ldr	r1, [r1, #1412]	; 0x584
	bl	sub_06000278
	bl	sub_06000280
	mov	r0, r4
	bl	sub_060001AC
	ldmia	sp!, {r4, lr}
	bx	lr
_060002DC:	.word	_0380B764
_060002E0:	.word	wmspW + 0x1000
_060002E4:	.word	_0380B808

	arm_func_start WMSP_GetLinkLevel
WMSP_GetLinkLevel: ; 0x060002E8
	ldr	r1, _0600034C	; =wmspW + 0x1000
	ldr	r1, [r1, #1356]	; 0x54c
	ldrb	r1, [r1, #83]	; 0x53
	cmp	r1, #8
	bne	_06000324
	cmp	r0, #22
	movcc	r0, #0
	bxcc	lr
	cmp	r0, #28
	movcc	r0, #1
	bxcc	lr
	cmp	r0, #34	; 0x22
	movcc	r0, #2
	movcs	r0, #3
	bx	lr
_06000324:
	cmp	r0, #8
	movcc	r0, #0
	bxcc	lr
	cmp	r0, #14
	movcc	r0, #1
	bxcc	lr
	cmp	r0, #20
	movcc	r0, #2
	movcs	r0, #3
	bx	lr
_0600034C:	.word	wmspW + 0x1000

	arm_func_start WMSP_GetAverageLinkLevel
WMSP_GetAverageLinkLevel: ; 0x06000350
	mov	r2, #0
	mov	r3, r2
	ldr	r1, _06000384	; =wmspW
_0600035C:
	add	r0, r1, r3
	add	r0, r0, #4096	; 0x1000
	ldrb	r0, [r0, #1364]	; 0x554
	add	r2, r2, r0
	add	r3, r3, #1
	cmp	r3, #32
	blt	_0600035C
	mov	r0, r2, lsr #5
	ldr	ip, _06000388	; =WMSP_GetLinkLevel
	bx	ip
_06000384:	.word	wmspW
_06000388:	.word	WMSP_GetLinkLevel

	arm_func_start WMSP_FillRssiIntoList
WMSP_FillRssiIntoList: ; 0x0600038C
	mov	r3, #0
	ldr	r2, _060003BC	; =wmspW
_06000394:
	add	r1, r2, r3
	add	r1, r1, #4096	; 0x1000
	strb	r0, [r1, #1364]	; 0x554
	add	r3, r3, #1
	cmp	r3, #32
	blt	_06000394
	mov	r1, #0
	ldr	r0, _060003C0	; =wmspW + 0x1000
	str	r1, [r0, #1396]	; 0x574
	bx	lr
_060003BC:	.word	wmspW
_060003C0:	.word	wmspW + 0x1000

	arm_func_start WMSP_AddRssiToList
WMSP_AddRssiToList: ; 0x060003C4
	ldr	r1, _060003FC	; =wmspW + 0x1000
	ldr	r3, [r1, #1396]	; 0x574
	ldr	r2, _06000400	; =wmspW + 0x1554
	strb	r0, [r2, r3]
	ldr	r2, [r1, #1396]	; 0x574
	add	r2, r2, #1
	and	r2, r2, #31
	str	r2, [r1, #1396]	; 0x574
	ldr	r2, _06000404	; =0x027FFF98
	ldrh	r1, [r2]
	eor	r0, r0, r1, lsl #1
	eor	r0, r0, r0, lsr #16
	strh	r0, [r2]
	bx	lr
_060003FC:	.word	wmspW + 0x1000
_06000400:	.word	wmspW + 0x1554
_06000404:	.word	0x027FFF98

	arm_func_start WMSP_SetAllParams
WMSP_SetAllParams: ; 0x06000408
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, r1
	ldr	r0, _0600054C	; =wmspW + 0x1000
	ldr	r4, [r0, #1360]	; 0x550
	add	r0, r4, #224	; 0xe0
	add	r1, r5, #16
	mov	r2, #6
	bl	sub_06000554
	mov	r0, #7
	strh	r0, [r5, #22]
	add	r0, r4, #256	; 0x100
	ldrh	r1, [r0, #244]	; 0xf4
	strh	r1, [r5, #24]
	ldrh	r1, [r0, #236]	; 0xec
	strh	r1, [r5, #30]
	ldrh	r1, [r4, #230]	; 0xe6
	strh	r1, [r5, #28]
	ldr	r1, [r4, #408]	; 0x198
	cmp	r1, #0
	bne	_06000480
	mov	r0, #0
	strh	r0, [r5, #32]
	strh	r0, [r5, #34]	; 0x22
	add	r1, r5, #36	; 0x24
	mov	r2, #80	; 0x50
	bl	sub_0600055C
	mov	r0, #0
	strh	r0, [r5, #158]	; 0x9e
	b	_060004A8
_06000480:
	ldrh	r0, [r0, #150]	; 0x96
	strh	r0, [r5, #32]
	ldrh	r0, [r4, #196]	; 0xc4
	strh	r0, [r5, #34]	; 0x22
	add	r0, r4, #412	; 0x19c
	add	r1, r5, #36	; 0x24
	mov	r2, #80	; 0x50
	bl	sub_06000554
	mov	r0, #1
	strh	r0, [r5, #158]	; 0x9e
_060004A8:
	mov	r0, #1
	strh	r0, [r5, #116]	; 0x74
	strh	r0, [r5, #118]	; 0x76
	ldrh	r0, [r4, #230]	; 0xe6
	cmp	r0, #1
	moveq	r0, #0
	streqh	r0, [r5, #120]	; 0x78
	movne	r0, #16
	strneh	r0, [r5, #120]	; 0x78
	mov	r0, #10
	strh	r0, [r5, #122]	; 0x7a
	cmp	r6, #38	; 0x26
	bne	_060004F0
	mov	r0, #0
	add	r1, r5, #124	; 0x7c
	mov	r2, #32
	bl	sub_0600055C
	b	_06000510
_060004F0:
	mov	r0, #0
	add	r1, r5, #124	; 0x7c
	mov	r2, #8
	bl	sub_0600055C
	ldr	r0, _06000550	; =0x0000FFFF
	add	r1, r5, #132	; 0x84
	mov	r2, #24
	bl	sub_0600055C
_06000510:
	add	r0, r4, #256	; 0x100
	ldrh	r0, [r0, #238]	; 0xee
	strh	r0, [r5, #156]	; 0x9c
	mov	r0, r5
	bl	WMSP_WL_ParamSetAll
	ldrh	r2, [r0, #4]
	cmp	r2, #0
	moveq	r0, #1
	beq	_06000544
	mov	r0, r6
	mov	r1, #512	; 0x200
	bl	sub_060001B4
	mov	r0, #0
_06000544:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr
_0600054C:	.word	wmspW + 0x1000
_06000550:	.word	0x0000FFFF

	arm_func_start sub_06000554
sub_06000554: ; 0x06000554
	ldr	pc, _06000558	; =MI_CpuCopy8
_06000558:	.word	MI_CpuCopy8

	arm_func_start sub_0600055C
sub_0600055C: ; 0x0600055C
	ldr	pc, _06000560	; =MIi_CpuClear16
_06000560:	.word	MIi_CpuClear16

	arm_func_start WMSP_CopyParentParam
WMSP_CopyParentParam: ; 0x06000564
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r2, r0
	ldr	r0, [r1, #8]
	str	r0, [r2, #4]
	ldrh	r0, [r1, #12]
	strh	r0, [r2, #8]
	ldrh	r0, [r1, #18]
	cmp	r0, #0
	movne	r3, #2
	moveq	r3, #0
	ldrh	r0, [r1, #14]
	cmp	r0, #0
	movne	ip, #1
	moveq	ip, #0
	ldrh	r0, [r1, #20]
	cmp	r0, #0
	movne	lr, #4
	moveq	lr, #0
	orr	r0, ip, r3
	orr	r0, lr, r0
	strb	r0, [r2, #11]
	ldrh	r0, [r1, #4]
	strb	r0, [r2, #10]
	mov	r0, #1
	strh	r0, [r2]
	strb	r0, [r2, #2]
	mov	r0, #0
	strb	r0, [r2, #3]
	ldrh	r0, [r1, #52]	; 0x34
	strh	r0, [r2, #12]
	ldrh	r0, [r1, #54]	; 0x36
	strh	r0, [r2, #14]
	ldrb	r3, [r2, #10]
	cmp	r3, #0
	beq	_06000608
	ldr	r0, [r1]
	add	r1, r2, #16
	add	r2, r3, #1
	bic	r2, r2, #1
	bl	sub_06000554
_06000608:
	add	sp, sp, #4
	ldmfd	sp!, {lr}
	bx	lr

	arm_func_start WMSP_CheckMacAddress
WMSP_CheckMacAddress: ; 0x06000614
	ldr	r1, _0600068C	; =wmspW + 0x1000
	ldr	r1, [r1, #1360]	; 0x550
	add	r3, r1, #224	; 0xe0
	ldrb	r2, [r0]
	ldrb	r1, [r1, #224]	; 0xe0
	cmp	r2, r1
	bne	_06000684
	ldrb	r2, [r0, #1]
	ldrb	r1, [r3, #1]
	cmp	r2, r1
	bne	_06000684
	ldrb	r2, [r0, #2]
	ldrb	r1, [r3, #2]
	cmp	r2, r1
	bne	_06000684
	ldrb	r2, [r0, #3]
	ldrb	r1, [r3, #3]
	cmp	r2, r1
	bne	_06000684
	ldrb	r2, [r0, #4]
	ldrb	r1, [r3, #4]
	cmp	r2, r1
	bne	_06000684
	ldrb	r1, [r0, #5]
	ldrb	r0, [r3, #5]
	cmp	r1, r0
	moveq	r0, #1
	bxeq	lr
_06000684:
	mov	r0, #0
	bx	lr
_0600068C:	.word	wmspW + 0x1000

	arm_func_start WmspPxiCallback
WmspPxiCallback: ; 0x06000690
	stmdb	sp!, {r4, lr}
	mov	r4, r1
	cmp	r2, #0
	bne	_060006E8
	ldr	r0, _060006F0	; =wmspW + 0x88
	mov	r2, #0
	bl	sub_060006F8
	cmp	r0, #0
	bne	_060006E8
	ldr	r0, _060006F4	; =wmspW + 0x1000
	ldr	r0, [r0, #1356]	; 0x54c
	cmp	r0, #0
	beq	_060006E8
	bl	sub_060001E8
	ldrh	r1, [r4]
	strh	r1, [r0]
	mov	r1, #8
	strh	r1, [r0, #2]
	mov	r1, #0
	strh	r1, [r0, #4]
	strh	r1, [r0, #6]
	bl	sub_060001F0
_060006E8:
	ldmia	sp!, {r4, lr}
	bx	lr
_060006F0:	.word	wmspW + 0x88
_060006F4:	.word	wmspW + 0x1000

	arm_func_start sub_060006F8
sub_060006F8: ; 0x060006F8
	ldr	pc, _060006FC	; =OS_SendMessage
_060006FC:	.word	OS_SendMessage

	arm_func_start WMSP_WlRequest
WMSP_WlRequest: ; 0x06000700
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r1, r0
	ldr	r0, _06000778	; =wmspW
	mov	r2, #1
	bl	sub_060006F8
	ldr	r0, _0600077C	; =wmspW + 0x58
	add	r1, sp, #0
	mov	r2, #1
	bl	sub_06000780
	ldr	r1, [sp]
	ldrh	r0, [r1, #14]
	add	r0, r1, r0, lsl #1
	ldrh	r0, [r0, #20]
	cmp	r0, #14
	bne	_06000768
	bl	sub_060001E8
	mov	r1, #128	; 0x80
	strh	r1, [r0]
	mov	r1, #19
	strh	r1, [r0, #2]
	mov	r1, #24
	strh	r1, [r0, #4]
	bl	sub_060001F0
	bl	sub_06000788
	bl	sub_06000790
_06000768:
	ldr	r0, [sp]
	add	sp, sp, #4
	ldmfd	sp!, {lr}
	bx	lr
_06000778:	.word	wmspW
_0600077C:	.word	wmspW + 0x58

	arm_func_start sub_06000780
sub_06000780: ; 0x06000780
	ldr	pc, _06000784	; =OS_ReceiveMessage
_06000784:	.word	OS_ReceiveMessage

	arm_func_start sub_06000788
sub_06000788: ; 0x06000788
	ldr	pc, _0600078C	; =SND_BeginSleep
_0600078C:	.word	SND_BeginSleep

	arm_func_start sub_06000790
sub_06000790: ; 0x06000790
	ldr	pc, _06000794	; =OS_Terminate
_06000794:	.word	OS_Terminate

	arm_func_start WMSP_Init
WMSP_Init: ; 0x06000798
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #12
	mov	r5, r0
	mov	r4, r1
	ldr	r1, [r4]
	ldr	r0, _06000924	; =wmspW + 0x1000
	str	r1, [r0, #1344]	; 0x540
	ldr	r1, [r5, #36]	; 0x24
	str	r1, [r0, #1348]	; 0x544
	ldr	r1, [r5, #40]	; 0x28
	str	r1, [r0, #1352]	; 0x548
	mov	r1, #0
	str	r1, [r0, #1356]	; 0x54c
	str	r1, [r0, #1360]	; 0x550
	ldr	r0, _06000928	; =wmspW
	ldr	r1, _0600092C	; =wmspW + 0x20
	mov	r2, #2
	bl	sub_06000964
	ldr	r0, _06000930	; =wmspW + 0x28
	ldr	r1, _06000934	; =wmspW + 0x48
	mov	r2, #4
	bl	sub_06000964
	ldr	r0, _06000938	; =wmspW + 0x58
	ldr	r1, _0600093C	; =wmspW + 0x78
	mov	r2, #4
	bl	sub_06000964
	ldr	r0, _06000940	; =wmspW + 0x88
	ldr	r1, _06000944	; =wmspW + 0xA8
	mov	r2, #32
	bl	sub_06000964
	ldr	r0, _06000928	; =wmspW
	str	r0, [r5, #16]
	ldr	r0, _06000930	; =wmspW + 0x28
	str	r0, [r5, #20]
	ldr	r1, [r4, #8]
	ldr	r0, _06000924	; =wmspW + 0x1000
	str	r1, [r0, #1400]	; 0x578
	ldr	r1, [r4, #24]
	str	r1, [r0, #1404]	; 0x57c
	ldr	r1, [r4, #16]
	str	r1, [r0, #1408]	; 0x580
	ldr	r1, [r4, #4]
	str	r1, [r0, #1412]	; 0x584
	ldr	r1, [r4, #20]
	str	r1, [r0, #1416]	; 0x588
	ldr	r1, [r4, #12]
	str	r1, [r0, #1420]	; 0x58c
	ldr	r0, _06000948	; =wmspW + 0x1528
	bl	sub_0600096C
	mov	r0, #1024	; 0x400
	str	r0, [sp]
	ldr	r0, [r4, #4]
	str	r0, [sp, #4]
	ldr	r0, _0600094C	; =_0380B808
	ldr	r1, _06000950	; =WMSP_IndicateThread
	mov	r2, #0
	ldr	r3, _06000948	; =wmspW + 0x1528
	bl	sub_06000974
	ldr	r0, _0600094C	; =_0380B808
	bl	sub_0600097C
	mov	r0, #4096	; 0x1000
	str	r0, [sp]
	ldr	r0, [r4, #12]
	str	r0, [sp, #4]
	ldr	r0, _06000954	; =_0380B764
	ldr	r1, _06000958	; =WMSP_RequestThread
	mov	r2, #0
	ldr	r3, _0600095C	; =wmspW + 0x1128
	bl	sub_06000974
	ldr	r0, _06000954	; =_0380B764
	bl	sub_0600097C
	mov	r3, #0
	mov	r2, r3
	ldr	r1, _06000928	; =wmspW
_060008C0:
	add	r0, r1, r3
	add	r0, r0, #4096	; 0x1000
	strb	r2, [r0, #1364]	; 0x554
	add	r3, r3, #1
	cmp	r3, #32
	blt	_060008C0
	ldr	r0, _06000924	; =wmspW + 0x1000
	str	r2, [r0, #1396]	; 0x574
	bl	sub_06000984
	cmp	r0, #0
	bne	_060008F0
	bl	sub_0600098C
_060008F0:
	bl	sub_06000994
	mov	r0, #10
	ldr	r1, _06000960	; =WmspPxiCallback
	bl	sub_0600099C
	mov	r0, #2
	str	r0, [r5, #24]
	ldr	r0, [r4, #20]
	str	r0, [r5, #12]
	mov	r0, r5
	bl	WL_InitDriver
	add	sp, sp, #12
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_06000924:	.word	wmspW + 0x1000
_06000928:	.word	wmspW
_0600092C:	.word	wmspW + 0x20
_06000930:	.word	wmspW + 0x28
_06000934:	.word	wmspW + 0x48
_06000938:	.word	wmspW + 0x58
_0600093C:	.word	wmspW + 0x78
_06000940:	.word	wmspW + 0x88
_06000944:	.word	wmspW + 0xA8
_06000948:	.word	wmspW + 0x1528
_0600094C:	.word	_0380B808
_06000950:	.word	WMSP_IndicateThread
_06000954:	.word	_0380B764
_06000958:	.word	WMSP_RequestThread
_0600095C:	.word	wmspW + 0x1128
_06000960:	.word	WmspPxiCallback

	arm_func_start sub_06000964
sub_06000964: ; 0x06000964
	ldr	pc, _06000968	; =OS_InitMessageQueue
_06000968:	.word	OS_InitMessageQueue

	arm_func_start sub_0600096C
sub_0600096C: ; 0x0600096C
	ldr	pc, _06000970	; =OS_InitMutex
_06000970:	.word	OS_InitMutex

	arm_func_start sub_06000974
sub_06000974: ; 0x06000974
	ldr	pc, _06000978	; =OS_CreateThread
_06000978:	.word	OS_CreateThread

	arm_func_start sub_0600097C
sub_0600097C: ; 0x0600097C
	ldr	pc, _06000980	; =OS_WakeupThreadDirect
_06000980:	.word	OS_WakeupThreadDirect

	arm_func_start sub_06000984
sub_06000984: ; 0x06000984
	ldr	pc, _06000988	; =OS_IsVAlarmAvailable
_06000988:	.word	OS_IsVAlarmAvailable

	arm_func_start sub_0600098C
sub_0600098C: ; 0x0600098C
	ldr	pc, _06000990	; =OS_InitVAlarm
_06000990:	.word	OS_InitVAlarm

	arm_func_start sub_06000994
sub_06000994: ; 0x06000994
	ldr	pc, _06000998	; =PXI_Init
_06000998:	.word	PXI_Init

	arm_func_start sub_0600099C
sub_0600099C: ; 0x0600099C
	ldr	pc, _060009A0	; =PXI_SetFifoRecvCallback
_060009A0:	.word	PXI_SetFifoRecvCallback

 	.section .bss
 	.balign 16, 0
 	.global wmspW
wmspW:
	.space 0x1590
