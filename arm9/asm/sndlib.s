	; Compiled with MWCCARM 1.2 sp3

	.include "asm/macros.inc"
	.include "global.inc"

	.extern SNDi_DecibelTable

	.bss

	.global UNK_021D1C8C
UNK_021D1C8C: ; 0x021D1C8C
	.space 0x4

	.global UNK_021D1C90
UNK_021D1C90: ; 0x021D1C90
	.space 0x4

	.global UNK_021D1C94
UNK_021D1C94: ; 0x021D1C94
	.space 0x4

	.global UNK_021D1C98
UNK_021D1C98: ; 0x021D1C98
	.space 0xc

	.global UNK_021D1CA4
UNK_021D1CA4: ; 0x021D1CA4
	.space 0xc

	.global UNK_021D1CB0
UNK_021D1CB0: ; 0x021D1CB0
	.space 0x4

	.global UNK_021D1CB4
UNK_021D1CB4: ; 0x021D1CB4
	.space 0x4

	.global UNK_021D1CB8
UNK_021D1CB8: ; 0x021D1CB8
	.space 0x4

	.global UNK_021D1CBC
UNK_021D1CBC: ; 0x021D1CBC
	.space 0x140

	.global UNK_021D1DFC
UNK_021D1DFC: ; 0x021D1DFC
	.space 0xc

	.global UNK_021D1E08
UNK_021D1E08: ; 0x021D1E08
	.space 0xc

	.global UNK_021D1E14
UNK_021D1E14: ; 0x021D1E14
	.space 0x440

	.global UNK_021D2254
UNK_021D2254: ; 0x021D2254
	.space 0x8

	.global UNK_021D225C
UNK_021D225C: ; 0x021D225C
	.space 0x10

	.global UNK_021D226C
UNK_021D226C: ; 0x021D226C
	.space 0x4

	.global UNK_021D2270
UNK_021D2270: ; 0x021D2270
	.space 0x4

	.global UNK_021D2274
UNK_021D2274: ; 0x021D2274
	.space 0x460

	.global UNK_021D26D4
UNK_021D26D4: ; 0x021D26D4
	.space 0x4

	.global UNK_021D26D8
UNK_021D26D8: ; 0x021D26D8
	.space 0xc

	.global UNK_021D26E4
UNK_021D26E4: ; 0x021D26E4
	.space 0x40

	.global UNK_021D2724
UNK_021D2724: ; 0x021D2724
	.space 0x80

	.global UNK_021D27A4
UNK_021D27A4: ; 0x021D27A4
	.space 0x4

	.global UNK_021D27A8
UNK_021D27A8: ; 0x021D27A8
	.space 0x4

	.global UNK_021D27AC
UNK_021D27AC: ; 0x021D27AC
	.space 0x20

	.global UNK_021D27CC
UNK_021D27CC: ; 0x021D27CC
	.space 0x54

	.global UNK_021D2820
UNK_021D2820: ; 0x021D2820
	.space 0xa0

	.global UNK_021D28C0
UNK_021D28C0: ; 0x021D28C0
	.space 0x4

	.global UNK_021D28C4
UNK_021D28C4: ; 0x021D28C4
	.space 0x3c

	.global UNK_021D2900
UNK_021D2900: ; 0x021D2900
	.space 0x4

	.global UNK_021D2904
UNK_021D2904: ; 0x021D2904
	.space 0x4d4

	.global UNK_021D2DD8
UNK_021D2DD8: ; 0x021D2DD8
	.space 0x18

	.global UNK_021D2DF0
UNK_021D2DF0: ; 0x021D2DF0
	.space 0xc

	.global UNK_021D2DFC
UNK_021D2DFC: ; 0x021D2DFC
	.space 0x5c0

	.text

	arm_func_start FUN_020C0130
FUN_020C0130: ; 0x020C0130
	ldr ip, _020C0138 ; =FUN_020C187C
	bx r12
	.balign 4
_020C0138: .word FUN_020C187C

	arm_func_start FUN_020C013C
FUN_020C013C: ; 0x020C013C
	stmdb sp!, {r4,lr}
	bl FUN_020C18F8
	mov r0, #0x0
	mov r1, r0
	mov r2, r0
	mov r3, r0
	bl SND_StopTimer
	bl SND_GetCurrentCommandTag
	mov r4, r0
	mov r0, #0x1
	bl SND_FlushCommand
	mov r0, r4
	bl SND_WaitForCommandProc
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C0174
FUN_020C0174: ; 0x020C0174
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	beq _020C0194
	mov r0, #0x40
	bl SND_SetMasterPan
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020C0194:
	bl SND_ResetMasterPan
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C01A0
FUN_020C01A0: ; 0x020C01A0
	stmdb sp!, {r4,lr}
	mov r4, #0x0
_020C01A8:
	mov r0, r4
	bl SND_RecvCommandReply
	cmp r0, #0x0
	bne _020C01A8
	bl FUN_020C0BA0
	bl FUN_020C1D9C
	bl FUN_020C3C88
	mov r0, #0x0
	bl SND_FlushCommand
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C01D0
FUN_020C01D0: ; 0x020C01D0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C0254 ; =UNK_021D1C94
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {pc}
	mov r1, #0x1
	str r1, [r0, #0x0]
	bl SND_Init
	ldr ip, _020C0258 ; =FUN_020C013C
	ldr r0, _020C025C ; =UNK_021D1C98
	mov r3, #0x0
	ldr r1, _020C0260 ; =UNK_021D1CA4
	ldr r2, _020C0264 ; =FUN_020C0130
	str r12, [r0, #0x0]
	str r3, [r0, #0x4]
	str r2, [r1, #0x0]
	str r3, [r1, #0x4]
	bl PM_PrependPreSleepCallback
	ldr r0, _020C0260 ; =UNK_021D1CA4
	bl PM_AppendPostSleepCallback
	bl FUN_020C0270
	bl FUN_020C1E38
	bl FUN_020C0D20
	ldr r1, _020C0268 ; =UNK_021D1C8C
	mvn r3, #0x0
	ldr r0, _020C026C ; =UNK_021D1C90
	mov r2, #0x1
	strb r3, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020C0254: .word UNK_021D1C94
_020C0258: .word FUN_020C013C
_020C025C: .word UNK_021D1C98
_020C0260: .word UNK_021D1CA4
_020C0264: .word FUN_020C0130
_020C0268: .word UNK_021D1C8C
_020C026C: .word UNK_021D1C90

	arm_func_start FUN_020C0270
FUN_020C0270: ; 0x020C0270
	ldr r2, _020C0290 ; =UNK_021D1CB8
	mov r3, #0x0
	ldr r1, _020C0294 ; =UNK_021D1CB0
	ldr r0, _020C0298 ; =UNK_021D1CB4
	str r3, [r2, #0x0]
	str r3, [r1, #0x0]
	str r3, [r0, #0x0]
	bx lr
	.balign 4
_020C0290: .word UNK_021D1CB8
_020C0294: .word UNK_021D1CB0
_020C0298: .word UNK_021D1CB4

	arm_func_start FUN_020C029C
FUN_020C029C: ; 0x020C029C
	ldr r1, _020C02B8 ; =UNK_021D1CB4
	mov r2, #0x1
	mvn r0, r2, lsl r0
	ldr r2, [r1, #0x0]
	and r0, r2, r0
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020C02B8: .word UNK_021D1CB4

	arm_func_start FUN_020C02BC
FUN_020C02BC: ; 0x020C02BC
	ldr r0, _020C02FC ; =UNK_021D1CB4
	mov r3, #0x1
	ldr r2, [r0, #0x0]
	mov r0, #0x0
_020C02CC:
	ands r1, r2, r3
	ldreq r1, _020C02FC ; =UNK_021D1CB4
	ldreq r2, [r1, #0x0]
	orreq r2, r2, r3
	streq r2, [r1, #0x0]
	bxeq lr
	add r0, r0, #0x1
	cmp r0, #0x8
	mov r3, r3, lsl #0x1
	blt _020C02CC
	mvn r0, #0x0
	bx lr
	.balign 4
_020C02FC: .word UNK_021D1CB4

	arm_func_start FUN_020C0300
FUN_020C0300: ; 0x020C0300
	ldr r1, _020C0318 ; =UNK_021D1CB0
	mvn r0, r0
	ldr r2, [r1, #0x0]
	and r0, r2, r0
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020C0318: .word UNK_021D1CB0

	arm_func_start FUN_020C031C
FUN_020C031C:
	ldr r1, _020C033C ; =UNK_021D1CB0
	ldr r2, [r1, #0x0]
	ands r3, r0, r2
	movne r0, #0x0
	orreq r0, r2, r0
	streq r0, [r1, #0x0]
	moveq r0, #0x1
	bx lr
	.balign 4
_020C033C: .word UNK_021D1CB0

	arm_func_start FUN_020C0340
FUN_020C0340:
	stmdb sp!, {r4,lr}
	movs r4, r0
	ldmeqia sp!, {r4,pc}
	mov r1, #0x0
	bl SND_UnlockChannel
	ldr r0, _020C036C ; =UNK_021D1CB8
	mvn r1, r4
	ldr r2, [r0, #0x0]
	and r1, r2, r1
	str r1, [r0, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_020C036C: .word UNK_021D1CB8

	arm_func_start FUN_020C0370
FUN_020C0370:
	stmdb sp!, {r4,lr}
	movs r4, r0
	moveq r0, #0x1
	ldmeqia sp!, {r4,pc}
	ldr r1, _020C03B4 ; =UNK_021D1CB8
	ldr r1, [r1, #0x0]
	ands r1, r4, r1
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
	mov r1, #0x0
	bl SND_LockChannel
	ldr r1, _020C03B4 ; =UNK_021D1CB8
	mov r0, #0x1
	ldr r2, [r1, #0x0]
	orr r2, r2, r4
	str r2, [r1, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_020C03B4: .word UNK_021D1CB8

	arm_func_start FUN_020C03B8
FUN_020C03B8: ; 0x020C03B8
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r0, [r4, #0xc]
	cmp r0, #0x0
	bne _020C03F8
	ldr r0, [r4, #0x10]
	bl SND_IsFinishedCommandTag
	cmp r0, #0x0
	moveq r0, #0x1
	ldmeqia sp!, {r4,pc}
	mov r0, #0x1
	str r0, [r4, #0xc]
_020C03F8:
	bl SND_GetChannelStatus
	ldr r1, [r4, #0x0]
	mov r2, #0x1
	mov r1, r2, lsl r1
	ands r0, r1, r0
	movne r0, r2
	moveq r0, #0x0
	streq r0, [r4, #0x8]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C041C
FUN_020C041C: ; 0x020C041C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x8]
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r0, [r0, #0x0]
	mov r2, #0x1
	mov r0, r2, lsl r0
	bl SND_SetChannelPan
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C044C
FUN_020C044C: ; 0x020C044C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, [r5, #0x8]
	mov r4, r1
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
	ldr r2, [r5, #0x4]
	ldr r0, _020C04D4 ; =0xD87F8000
	mov r3, r2, asr #0x1f
	mov r1, #0x7f
	bl _ll_udiv
	mov r2, r4
	mov r3, r4, asr #0x1f
	bl _ll_udiv
	mov r2, #0x0
	mov r3, r0
	mov r0, #0x10
	cmp r1, r2
	cmpeq r3, r0
	movcc r3, r0
	blo _020C04B8
	ldr r0, _020C04D8 ; =0x0000FFFF
	cmp r1, r2
	cmpeq r3, r0
	movhi r3, r0
_020C04B8:
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	mov r0, r1, lsl r0
	mov r1, r3
	bl SND_SetChannelTimer
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C04D4: .word 0xD87F8000
_020C04D8: .word 0x0000FFFF

	arm_func_start FUN_020C04DC
FUN_020C04DC: ; 0x020C04DC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x8]
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r0, [r0, #0x0]
	mov r2, #0x1
	mov r0, r2, lsl r0
	mov r2, #0x0
	bl SND_SetChannelVolume
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C0510
FUN_020C0510: ; 0x020C0510
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r0, [r4, #0x0]
	mov r2, #0x1
	mov r1, #0x0
	mov r0, r2, lsl r0
	mov r2, r1
	mov r3, r1
	bl SND_StopTimer
	mov r0, #0x0
	str r0, [r4, #0x8]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C054C
FUN_020C054C: ; 0x020C054C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x1c
	movs r8, r1
	mov r9, r0
	mov r7, r2
	mov r6, r3
	beq _020C0584
	cmp r8, #0x1
	ldreq r0, [sp, #0x3c]
	ldreq r1, [sp, #0x38]
	moveq r0, r0, asr #0x1
	moveq r5, r1, asr #0x1
	subeq r4, r0, r1, asr #0x1
	b _020C0598
_020C0584:
	ldr r0, [sp, #0x3c]
	ldr r1, [sp, #0x38]
	mov r0, r0, asr #0x2
	mov r5, r1, asr #0x2
	sub r4, r0, r1, asr #0x2
_020C0598:
	ldr r2, [sp, #0x40]
	ldr r0, _020C0668 ; =0xD87F8000
	mov r3, r2, asr #0x1f
	mov r1, #0x7f
	bl _ll_udiv
	ldr r2, [sp, #0x48]
	mov r3, r2, asr #0x1f
	bl _ll_udiv
	mov r3, #0x0
	mov r2, #0x10
	cmp r1, r3
	cmpeq r0, r2
	movcc r0, r2
	blo _020C05E0
	ldr r2, _020C066C ; =0x0000FFFF
	cmp r1, r3
	cmpeq r0, r2
	movhi r0, r2
_020C05E0:
	str r5, [sp, #0x0]
	ldr r1, [sp, #0x44]
	str r4, [sp, #0x4]
	str r1, [sp, #0x8]
	mov r1, #0x0
	str r1, [sp, #0xc]
	cmp r6, #0x0
	movne r3, #0x1
	ldr r1, [sp, #0x4c]
	str r0, [sp, #0x10]
	str r1, [sp, #0x14]
	ldr r0, [r9, #0x0]
	moveq r3, #0x2
	mov r1, r8
	mov r2, r7
	bl SND_SetupChannelPcm
	mov r1, #0x0
	ldr r0, [r9, #0x0]
	mov r2, #0x1
	mov r0, r2, lsl r0
	mov r2, r1
	mov r3, r1
	bl SND_StartTimer
	mov r0, #0x1
	str r0, [r9, #0x8]
	mov r0, #0x0
	str r0, [r9, #0xc]
	bl SND_GetCurrentCommandTag
	str r0, [r9, #0x10]
	ldr r1, [sp, #0x40]
	mov r0, #0x1
	str r1, [r9, #0x4]
	add sp, sp, #0x1c
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020C0668: .word 0xD87F8000
_020C066C: .word 0x0000FFFF

	arm_func_start FUN_020C0670
FUN_020C0670: ; 0x020C0670
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	ldr ip, _020C0684 ; =FUN_020C0340
	mov r0, r1, lsl r0
	bx r12
	.balign 4
_020C0684: .word FUN_020C0340

	arm_func_start FUN_020C0688
FUN_020C0688: ; 0x020C0688
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x1
	mov r0, r0, lsl r4
	bl FUN_020C0370
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	mov r0, #0x14
	mul r0, r4, r0
	ldr r2, _020C06C8 ; =UNK_021D1CBC
	mov r1, #0x0
	str r4, [r2, r0]
	add r0, r2, r0
	str r1, [r0, #0x8]
	ldmia sp!, {r4,pc}
	.balign 4
_020C06C8: .word UNK_021D1CBC

	arm_func_start FUN_020C06CC
FUN_020C06CC: ; 0x020C06CC
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldr r4, [r6, #0x4]
	mov r5, r1
	cmp r4, #0x0
	beq _020C06F8
	mov r0, r4
	mov r1, r6
	bl FUN_020ADAB0
	mov r0, #0x0
	str r0, [r6, #0x4]
_020C06F8:
	ldr r0, _020C0728 ; =UNK_021D1E08
	mov r1, r6
	bl FUN_020ADAB0
	strb r5, [r6, #0x3d]
	cmp r4, #0x0
	beq _020C071C
	mov r0, r4
	mov r1, r6
	bl FUN_020C0910
_020C071C:
	mov r0, r6
	bl FUN_020C08B4
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C0728: .word UNK_021D1E08

	arm_func_start FUN_020C072C
FUN_020C072C: ; 0x020C072C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
	bl FUN_020C2A7C
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x8]
	ldmneia sp!, {r4,pc}
	ldr r1, [r4, #0x10]
	ldr r2, _020C0778 ; =UNK_021D2254
	mov r0, #0x24
	mla r0, r1, r0, r2
	mov r1, r4
	add r0, r0, #0xc
	bl FUN_020ADAB0
	ldmia sp!, {r4,pc}
	.balign 4
_020C0778: .word UNK_021D2254

	arm_func_start FUN_020C077C
FUN_020C077C: ; 0x020C077C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x0]
	strne r0, [r4, #0x0]
	ldr r5, [r4, #0x4]
	mov r1, r4
	mov r0, r5
	bl FUN_020ADAB0
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	cmp r1, #0x0
	beq _020C07D8
	add r0, r5, #0xc
	bl FUN_020ADBE8
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	str r1, [r0, #0xc]
	str r1, [r4, #0x8]
_020C07D8:
	ldr r0, _020C0800 ; =UNK_021D1E08
	mov r1, r4
	bl FUN_020ADAB0
	ldr r0, _020C0804 ; =UNK_021D1DFC
	mov r1, r4
	bl FUN_020ADBE8
	mov r0, #0x0
	strb r0, [r4, #0x2c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C0800: .word UNK_021D1E08
_020C0804: .word UNK_021D1DFC

	arm_func_start FUN_020C0808
FUN_020C0808: ; 0x020C0808
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, _020C0874 ; =UNK_021D1DFC
	mov r1, #0x0
	bl FUN_020ADA98
	movs r4, r0
	bne _020C0850
	ldr r0, _020C0878 ; =UNK_021D1E08
	mov r1, #0x0
	bl FUN_020ADA98
	mov r4, r0
	ldrb r1, [r4, #0x3d]
	cmp r5, r1
	addlt sp, sp, #0x4
	movlt r0, #0x0
	ldmltia sp!, {r4-r5,pc}
	bl FUN_020C087C
_020C0850:
	ldr r0, _020C0874 ; =UNK_021D1DFC
	mov r1, r4
	bl FUN_020ADAB0
	mov r0, r4
	strb r5, [r4, #0x3d]
	bl FUN_020C08B4
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C0874: .word UNK_021D1DFC
_020C0878: .word UNK_021D1E08

	arm_func_start FUN_020C087C
FUN_020C087C: ; 0x020C087C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldrb r0, [r4, #0x2c]
	cmp r0, #0x2
	bne _020C089C
	ldrb r0, [r4, #0x3c]
	ldr r1, _020C08B0 ; =0xFFFFFD2D
	bl SND_SetPlayerVolume
_020C089C:
	ldrb r0, [r4, #0x3c]
	bl SND_StopSeq
	mov r0, r4
	bl FUN_020C077C
	ldmia sp!, {r4,pc}
	.balign 4
_020C08B0: .word 0xFFFFFD2D

	arm_func_start FUN_020C08B4
FUN_020C08B4: ; 0x020C08B4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, _020C090C ; =UNK_021D1E08
	mov r1, #0x0
	bl FUN_020ADA98
	movs r1, r0
	beq _020C08F8
	ldr r4, _020C090C ; =UNK_021D1E08
_020C08D8:
	ldrb r2, [r5, #0x3d]
	ldrb r0, [r1, #0x3d]
	cmp r2, r0
	blo _020C08F8
	mov r0, r4
	bl FUN_020ADA98
	movs r1, r0
	bne _020C08D8
_020C08F8:
	ldr r0, _020C090C ; =UNK_021D1E08
	mov r2, r5
	bl FUN_020ADB18
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C090C: .word UNK_021D1E08

	arm_func_start FUN_020C0910
FUN_020C0910: ; 0x020C0910
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r1, #0x0
	mov r5, r0
	bl FUN_020ADA98
	movs r1, r0
	beq _020C0950
_020C0930:
	ldrb r2, [r4, #0x3d]
	ldrb r0, [r1, #0x3d]
	cmp r2, r0
	blo _020C0950
	mov r0, r5
	bl FUN_020ADA98
	movs r1, r0
	bne _020C0930
_020C0950:
	mov r0, r5
	mov r2, r4
	bl FUN_020ADB18
	str r5, [r4, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C0968
FUN_020C0968: ; 0x020C0968
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x0
	strb r0, [r4, #0x2e]
	strb r0, [r4, #0x2d]
	strb r0, [r4, #0x2f]
	strh r0, [r4, #0x34]
	strh r0, [r4, #0x3e]
	mov r1, #0x7f
	strb r1, [r4, #0x40]
	add r0, r4, #0x1c
	strb r1, [r4, #0x41]
	bl FUN_020C3E6C
	add r0, r4, #0x1c
	mov r1, #0x7f00
	mov r2, #0x1
	bl FUN_020C3E40
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C09B0
FUN_020C09B0: ; 0x020C09B0
	stmdb sp!, {r4-r6,lr}
	ldr r3, _020C0A00 ; =UNK_021D2254
	mov r2, #0x24
	mla r5, r0, r2, r3
	mov r6, r1
	add r0, r5, #0xc
	mov r1, #0x0
	bl FUN_020ADA98
	movs r4, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	mov r1, r4
	add r0, r5, #0xc
	bl FUN_020ADAB0
	str r6, [r4, #0xc]
	str r4, [r6, #0x8]
	ldr r0, [r4, #0x8]
	bl FUN_020C29C0
	ldr r0, [r4, #0x8]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C0A00: .word UNK_021D2254

	arm_func_start FUN_020C0A04
FUN_020C0A04: ; 0x020C0A04
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r5, r0
	mov r4, r1
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
	ldrb r0, [r5, #0x2e]
	cmp r4, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
	ldrb r0, [r5, #0x3c]
	bl SND_PauseSeq
	strb r4, [r5, #0x2e]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C0A40
FUN_020C0A40: ; 0x020C0A40
	stmdb sp!, {r4,lr}
	movs r4, r0
	mov r2, r1
	ldmeqia sp!, {r4,pc}
	ldrb r1, [r4, #0x2c]
	cmp r1, #0x0
	ldmeqia sp!, {r4,pc}
	cmp r2, #0x0
	bne _020C0A6C
	bl FUN_020C087C
	ldmia sp!, {r4,pc}
_020C0A6C:
	add r0, r4, #0x1c
	mov r1, #0x0
	bl FUN_020C3E40
	mov r0, r4
	mov r1, #0x0
	bl FUN_020C06CC
	mov r0, #0x2
	strb r0, [r4, #0x2c]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C0A90
FUN_020C0A90: ; 0x020C0A90
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrb r0, [r5, #0x3c]
	ldr r4, [r5, #0x4]
	bl SND_PrepareSeq
	ldr r2, [r4, #0x1c]
	cmp r2, #0x0
	beq _020C0AC0
	ldrb r0, [r5, #0x3c]
	ldr r1, _020C0AE4 ; =0x0000FFFF
	bl SND_SetTrackAllocatableChannel
_020C0AC0:
	mov r0, r5
	bl FUN_020C0968
	bl SND_GetCurrentCommandTag
	str r0, [r5, #0x30]
	mov r0, #0x1
	strb r0, [r5, #0x2f]
	strb r0, [r5, #0x2c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C0AE4: .word 0x0000FFFF

	arm_func_start thunk_FUN_020c077c
thunk_FUN_020c077c: ; 0x020C0AE8
	ldr ip, _020C0AF0 ; =FUN_020C077C
	bx r12
	.balign 4
_020C0AF0: .word FUN_020C077C

	arm_func_start FUN_020C0AF4
FUN_020C0AF4: ; 0x020C0AF4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr ip, _020C0B9C ; =UNK_021D2254
	mov r3, #0x24
	mov r4, r0
	ldr r5, [r4, #0x0]
	mla r6, r1, r3, r12
	mov r7, r2
	cmp r5, #0x0
	beq _020C0B20
	bl FUN_020C0F68
_020C0B20:
	ldrh r1, [r6, #0x8]
	ldr r0, [r6, #0x18]
	cmp r1, r0
	blo _020C0B64
	mov r0, r6
	mov r1, #0x0
	bl FUN_020ADA98
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	ldrb r1, [r0, #0x3d]
	cmp r7, r1
	addlt sp, sp, #0x4
	movlt r0, #0x0
	ldmltia sp!, {r4-r7,pc}
	bl FUN_020C087C
_020C0B64:
	mov r0, r7
	bl FUN_020C0808
	movs r5, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	mov r0, r6
	mov r1, r5
	bl FUN_020C0910
	str r4, [r5, #0x0]
	mov r0, r5
	str r5, [r4, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C0B9C: .word UNK_021D2254

	arm_func_start FUN_020C0BA0
FUN_020C0BA0: ; 0x020C0BA0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	bl SND_GetPlayerStatus
	str r0, [sp, #0x0]
	ldr r0, _020C0D14 ; =UNK_021D1E08
	mov r1, #0x0
	bl FUN_020ADA98
	movs r10, r0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r11,pc}
	mov r0, #0x8000
	rsb r0, r0, #0x0
	ldr r4, _020C0D18 ; =SNDi_DecibelTable
	str r0, [sp, #0x4]
	mov r5, #0x1
	mov r11, #0x0
_020C0BE0:
	ldr r0, _020C0D14 ; =UNK_021D1E08
	mov r1, r10
	bl FUN_020ADA98
	ldrb r1, [r10, #0x2d]
	mov r9, r0
	cmp r1, #0x0
	bne _020C0C0C
	ldr r0, [r10, #0x30]
	bl SND_IsFinishedCommandTag
	cmp r0, #0x0
	strneb r5, [r10, #0x2d]
_020C0C0C:
	ldrb r0, [r10, #0x2d]
	cmp r0, #0x0
	beq _020C0C38
	ldrb r0, [r10, #0x3c]
	mov r1, r5, lsl r0
	ldr r0, [sp, #0x0]
	ands r0, r0, r1
	bne _020C0C38
	mov r0, r10
	bl FUN_020C077C
	b _020C0D00
_020C0C38:
	add r0, r10, #0x1c
	bl FUN_020C3DF4
	ldr r0, [r10, #0x4]
	ldrb r2, [r10, #0x41]
	ldrb r1, [r10, #0x40]
	ldrb r0, [r0, #0x20]
	mov r3, r2, lsl #0x1
	mov r2, r1, lsl #0x1
	mov r1, r0, lsl #0x1
	add r0, r10, #0x1c
	ldrsh r8, [r4, r3]
	ldrsh r7, [r4, r2]
	ldrsh r6, [r4, r1]
	bl FUN_020C3E0C
	mov r0, r0, asr #0x8
	mov r2, r0, lsl #0x1
	add r1, r7, r8
	mov r0, #0x8000
	ldrsh r2, [r4, r2]
	add r1, r6, r1
	rsb r0, r0, #0x0
	add r6, r2, r1
	cmp r6, r0
	ldrlt r6, [sp, #0x4]
	blt _020C0CA8
	ldr r0, _020C0D1C ; =0x00007FFF
	cmp r6, r0
	movgt r6, r0
_020C0CA8:
	ldrsh r0, [r10, #0x3e]
	cmp r6, r0
	beq _020C0CC4
	ldrb r0, [r10, #0x3c]
	mov r1, r6
	bl SND_SetPlayerVolume
	strh r6, [r10, #0x3e]
_020C0CC4:
	ldrb r0, [r10, #0x2c]
	cmp r0, #0x2
	bne _020C0CE8
	add r0, r10, #0x1c
	bl FUN_020C3DDC
	cmp r0, #0x0
	beq _020C0CE8
	mov r0, r10
	bl FUN_020C087C
_020C0CE8:
	ldrb r0, [r10, #0x2f]
	cmp r0, #0x0
	beq _020C0D00
	ldrb r0, [r10, #0x3c]
	bl SND_StartPreparedSeq
	strb r11, [r10, #0x2f]
_020C0D00:
	mov r10, r9
	cmp r9, #0x0
	bne _020C0BE0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020C0D14: .word UNK_021D1E08
_020C0D18: .word SNDi_DecibelTable
_020C0D1C: .word 0x00007FFF

	arm_func_start FUN_020C0D20
FUN_020C0D20: ; 0x020C0D20
	stmdb sp!, {r4-r10,lr}
	ldr r0, _020C0DC4 ; =UNK_021D1E08
	mov r1, #0x14
	bl FUN_020ADC74
	ldr r0, _020C0DC8 ; =UNK_021D1DFC
	mov r1, #0x14
	bl FUN_020ADC74
	ldr r6, _020C0DCC ; =UNK_021D1E14
	mov r7, #0x0
	ldr r4, _020C0DC8 ; =UNK_021D1DFC
	mov r5, r7
_020C0D4C:
	strb r5, [r6, #0x2c]
	mov r0, r4
	mov r1, r6
	strb r7, [r6, #0x3c]
	bl FUN_020ADBE8
	add r7, r7, #0x1
	cmp r7, #0x10
	add r6, r6, #0x44
	blt _020C0D4C
	ldr sl, _020C0DD0 ; =UNK_021D2254
	mov r9, #0x0
	mov r7, r9
	mov r4, r9
	mov r8, #0xc
	mov r6, #0x7f
	mov r5, #0x1
_020C0D8C:
	mov r0, r10
	mov r1, r8
	bl FUN_020ADC74
	mov r1, r7
	add r0, r10, #0xc
	bl FUN_020ADC74
	strb r6, [r10, #0x20]
	str r5, [r10, #0x18]
	add r9, r9, #0x1
	str r4, [r10, #0x1c]
	cmp r9, #0x20
	add r10, r10, #0x24
	blt _020C0D8C
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020C0DC4: .word UNK_021D1E08
_020C0DC8: .word UNK_021D1DFC
_020C0DCC: .word UNK_021D1E14
_020C0DD0: .word UNK_021D2254

	arm_func_start FUN_020C0DD4
FUN_020C0DD4: ; 0x020C0DD4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {pc}
	ldrb r0, [r1, #0x2d]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {pc}
	ldrb r0, [r1, #0x3c]
	bl SND_GetPlayerTickCounter
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C0E14
FUN_020C0E14: ; 0x020C0E14
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	mvneq r0, #0x0
	bxeq lr
	ldrh r0, [r1, #0x34]
	cmp r0, #0x1
	mvnne r0, #0x0
	ldreqh r0, [r1, #0x38]
	bx lr

	arm_func_start FUN_020C0E38
FUN_020C0E38: ; 0x020C0E38
	ldr r12, [r0, #0x0]
	cmp r12, #0x0
	bxeq lr
	mov r3, #0x2
	strh r3, [r12, #0x34]
	ldr r3, [r0, #0x0]
	strh r1, [r3, #0x38]
	ldr r0, [r0, #0x0]
	strh r2, [r0, #0x3a]
	bx lr

	arm_func_start FUN_020C0E60
FUN_020C0E60: ; 0x020C0E60
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	movne r2, #0x1
	strneh r2, [r3, #0x34]
	ldrne r0, [r0, #0x0]
	strneh r1, [r0, #0x38]
	bx lr

	arm_func_start FUN_020C0E7C
FUN_020C0E7C: ; 0x020C0E7C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldrb r0, [r0, #0x3c]
	bl SND_SetTrackPan
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C0EA4
FUN_020C0EA4: ; 0x020C0EA4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldrb r0, [r0, #0x3c]
	bl SND_SetTrackPitch
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C0ECC
FUN_020C0ECC: ; 0x020C0ECC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldrb r0, [r0, #0x3c]
	bl SND_SetPlayerChannelPriority
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C0EF4
FUN_020C0EF4: ; 0x020C0EF4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldrb r0, [r3, #0x2c]
	cmp r0, #0x2
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	add r0, r3, #0x1c
	mov r1, r1, lsl #0x8
	bl FUN_020C3E40
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C0F30
FUN_020C0F30: ; 0x020C0F30
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	strneb r1, [r0, #0x40]
	bx lr

	arm_func_start FUN_020C0F40
FUN_020C0F40: ; 0x020C0F40
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	strneb r1, [r0, #0x41]
	bx lr

	arm_func_start FUN_020C0F50
FUN_020C0F50: ; 0x020C0F50
	mov r1, #0x24
	mul r1, r0, r1
	ldr r0, _020C0F64 ; =UNK_021D225C
	ldrh r0, [r0, r1]
	bx lr
	.balign 4
_020C0F64: .word UNK_021D225C

	arm_func_start FUN_020C0F68
FUN_020C0F68: ; 0x020C0F68
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	movne r1, #0x0
	strne r1, [r2, #0x0]
	strne r1, [r0, #0x0]
	bx lr

	arm_func_start FUN_020C0F80
FUN_020C0F80: ; 0x020C0F80
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr

	arm_func_start FUN_020C0F8C
FUN_020C0F8C: ; 0x020C0F8C
	ldr ip, _020C0F98 ; =FUN_020C0A04
	ldr r0, [r0, #0x0]
	bx r12
	.balign 4
_020C0F98: .word FUN_020C0A04

	arm_func_start FUN_020C0F9C
FUN_020C0F9C: ; 0x020C0F9C
	stmdb sp!, {r4-r6,lr}
	ldr r4, _020C0FD8 ; =UNK_021D1E14
	mov r6, r0
	mov r5, #0x0
_020C0FAC:
	ldrb r0, [r4, #0x2c]
	cmp r0, #0x0
	beq _020C0FC4
	mov r0, r4
	mov r1, r6
	bl FUN_020C0A40
_020C0FC4:
	add r5, r5, #0x1
	cmp r5, #0x10
	add r4, r4, #0x44
	blt _020C0FAC
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C0FD8: .word UNK_021D1E14

	arm_func_start FUN_020C0FDC
FUN_020C0FDC: ; 0x020C0FDC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r4, _020C103C ; =UNK_021D1E14
	mov r7, r0
	mov r6, r1
	mov r5, #0x0
_020C0FF4:
	ldrb r0, [r4, #0x2c]
	cmp r0, #0x0
	beq _020C1024
	ldrh r0, [r4, #0x34]
	cmp r0, #0x1
	bne _020C1024
	ldrh r0, [r4, #0x38]
	cmp r0, r7
	bne _020C1024
	mov r0, r4
	mov r1, r6
	bl FUN_020C0A40
_020C1024:
	add r5, r5, #0x1
	cmp r5, #0x10
	add r4, r4, #0x44
	blt _020C0FF4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C103C: .word UNK_021D1E14

	arm_func_start FUN_020C1040
FUN_020C1040: ; 0x020C1040
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r3, _020C109C ; =UNK_021D2254
	mov r2, #0x24
	mla r4, r0, r2, r3
	ldr r5, _020C10A0 ; =UNK_021D1E14
	mov r7, r1
	mov r6, #0x0
_020C1060:
	ldrb r0, [r5, #0x2c]
	cmp r0, #0x0
	beq _020C1084
	ldr r0, [r5, #0x4]
	cmp r0, r4
	bne _020C1084
	mov r0, r5
	mov r1, r7
	bl FUN_020C0A40
_020C1084:
	add r6, r6, #0x1
	cmp r6, #0x10
	add r5, r5, #0x44
	blt _020C1060
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C109C: .word UNK_021D2254
_020C10A0: .word UNK_021D1E14

	arm_func_start FUN_020C10A4
FUN_020C10A4: ; 0x020C10A4
	ldr ip, _020C10B0 ; =FUN_020C0A40
	ldr r0, [r0, #0x0]
	bx r12
	.balign 4
_020C10B0: .word FUN_020C0A40

	arm_func_start FUN_020C10B4
FUN_020C10B4:
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r5, r2
	mov r6, r0
	mov r0, r1
	mov r3, #0x0
	ldr r2, _020C1140 ; =FUN_020C072C
	add r1, r5, #0x14
	str r3, [sp, #0x0]
	bl FUN_020C2958
	movs r4, r0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	mov r2, #0x0
	str r2, [r4, #0xc]
	str r6, [r4, #0x10]
	mov r1, r5
	add r0, r4, #0x14
	str r2, [r4, #0x8]
	bl FUN_020C2A94
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r2, _020C1144 ; =UNK_021D2254
	mov r1, #0x24
	mla r2, r6, r1, r2
	str r0, [r4, #0x8]
	mov r1, r4
	add r0, r2, #0xc
	bl FUN_020ADBE8
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C1140: .word FUN_020C072C
_020C1144: .word UNK_021D2254

	arm_func_start FUN_020C1148
FUN_020C1148: ; 0x020C1148
	mov r2, #0x24
	mul r2, r0, r2
	ldr r0, _020C115C ; =UNK_021D2270
	str r1, [r0, r2]
	bx lr
	.balign 4
_020C115C: .word UNK_021D2270

	arm_func_start FUN_020C1160
FUN_020C1160: ; 0x020C1160
	mov r2, #0x24
	mul r2, r0, r2
	mov r0, r1, lsl #0x10
	ldr r1, _020C117C ; =UNK_021D226C
	mov r0, r0, lsr #0x10
	str r0, [r1, r2]
	bx lr
	.balign 4
_020C117C: .word UNK_021D226C

	arm_func_start FUN_020C1180
FUN_020C1180: ; 0x020C1180
	mov r2, #0x24
	mul r2, r0, r2
	ldr r0, _020C1194 ; =UNK_021D2274
	strb r1, [r0, r2]
	bx lr
	.balign 4
_020C1194: .word UNK_021D2274

	arm_func_start FUN_020C1198
FUN_020C1198: ; 0x020C1198
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	ldr r0, [r4, #0x24]
	mov r0, r0, lsl #0x1e
	movs r0, r0, asr #0x1f
	ldmeqia sp!, {r4-r6,pc}
	ldr r0, [r4, #0x38]
	cmp r0, #0x0
	beq _020C11E8
	mov r5, #0x1
_020C11C0:
	bl OS_DisableInterrupts
	mov r6, r0
	mov r0, r4
	mov r1, r5
	bl FUN_020C1254
	mov r0, r6
	bl OS_RestoreInterrupts
	ldr r0, [r4, #0x38]
	cmp r0, #0x0
	bne _020C11C0
_020C11E8:
	ldr r0, [r4, #0x40]
	mov r2, #0x1
	mov r1, #0x0
	mov r2, r2, lsl r0
	ldr r0, [r4, #0x44]
	mov r3, r1
	bl SND_StartTimer
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020C1208
FUN_020C1208: ; 0x020C1208
	stmdb sp!, {r4,lr}
	ldr r1, [r0, #0x24]
	mov r1, r1, lsl #0x1e
	movs r1, r1, asr #0x1f
	ldmeqia sp!, {r4,pc}
	ldr r2, [r0, #0x40]
	mov r3, #0x1
	mov r1, #0x0
	mov r2, r3, lsl r2
	ldr r0, [r0, #0x44]
	mov r3, r1
	bl SND_StopTimer
	bl SND_GetCurrentCommandTag
	mov r4, r0
	mov r0, #0x1
	bl SND_FlushCommand
	mov r0, r4
	bl SND_WaitForCommandProc
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C1254
FUN_020C1254: ; 0x020C1254
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r5, r0
	mov r4, r1
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	bl _u32_div_f
	ldr r1, [r5, #0x48]
	ldr r2, [r5, #0x38]
	mov r3, r0
	mul lr, r3, r2
	cmp r1, #0x0
	mov r12, #0x0
	ble _020C12B8
	ldr r2, _020C1300 ; =UNK_021D2724
	ldr r0, _020C1304 ; =UNK_021D26E4
_020C1294:
	add r1, r5, r12
	ldrb r1, [r1, #0x4c]
	ldr r1, [r2, r1, lsl #0x3]
	add r1, r1, lr
	str r1, [r0, r12, lsl #0x2]
	ldr r1, [r5, #0x48]
	add r12, r12, #0x1
	cmp r12, r1
	blt _020C1294
_020C12B8:
	ldr r0, [r5, #0x20]
	ldr r2, _020C1304 ; =UNK_021D26E4
	str r0, [sp, #0x0]
	ldr r12, [r5, #0x34]
	mov r0, r4
	str r12, [sp, #0x4]
	ldr r4, [r5, #0x30]
	blx r4
	ldr r0, [r5, #0x38]
	add r0, r0, #0x1
	str r0, [r5, #0x38]
	ldr r1, [r5, #0x38]
	ldr r0, [r5, #0x2c]
	cmp r1, r0
	movge r0, #0x0
	strge r0, [r5, #0x38]
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C1300: .word UNK_021D2724
_020C1304: .word UNK_021D26E4

	arm_func_start FUN_020C1308
FUN_020C1308: ; 0x020C1308
	ldr ip, _020C1314 ; =FUN_020C1254
	mov r1, #0x1
	bx r12
	.balign 4
_020C1314: .word FUN_020C1254

	arm_func_start FUN_020C1318
FUN_020C1318: ; 0x020C1318
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x40]
	bl FUN_020C029C
	ldr r0, _020C1344 ; =UNK_021D26D8
	mov r1, r4
	bl FUN_020ADAB0
	ldr r0, [r4, #0x24]
	bic r0, r0, #0x1
	str r0, [r4, #0x24]
	ldmia sp!, {r4,pc}
	.balign 4
_020C1344: .word UNK_021D26D8

	arm_func_start FUN_020C1348
FUN_020C1348: ; 0x020C1348
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldr r0, [r4, #0x24]
	mov r0, r0, lsl #0x1e
	movs r0, r0, asr #0x1f
	beq _020C13B4
	ldr r0, [r4, #0x40]
	mov r2, #0x1
	mov r1, #0x0
	mov r2, r2, lsl r0
	ldr r0, [r4, #0x44]
	mov r3, r1
	bl SND_StopTimer
	add r0, r4, #0x8
	bl PM_DeletePreSleepCallback
	add r0, r4, #0x14
	bl PM_DeletePostSleepCallback
	ldr r0, [r4, #0x24]
	bic r0, r0, #0x2
	str r0, [r4, #0x24]
	bl SND_GetCurrentCommandTag
	mov r5, r0
	mov r0, #0x1
	bl SND_FlushCommand
	mov r0, r5
	bl SND_WaitForCommandProc
_020C13B4:
	mov r0, r4
	bl FUN_020C1318
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C13C4
FUN_020C13C4: ; 0x020C13C4
	stmdb sp!, {r4-r8,lr}
	mov r7, r0
	str r1, [r7, #0x3c]
	ldr r0, [r7, #0x48]
	mov r5, #0x0
	cmp r0, #0x0
	ldmleia sp!, {r4-r8,pc}
	ldr r4, _020C142C ; =UNK_021D2724
	mov r8, #0x1
_020C13E8:
	add r0, r7, r5
	ldrb r6, [r0, #0x4c]
	ldr r1, [r7, #0x3c]
	add r0, r4, r6, lsl #0x3
	ldr r0, [r0, #0x4]
	add r0, r1, r0
	bl SND_CalcChannelVolume
	mov r2, r0
	mov r0, r8, lsl r6
	and r1, r2, #0xff
	mov r2, r2, asr #0x8
	bl SND_SetChannelVolume
	ldr r0, [r7, #0x48]
	add r5, r5, #0x1
	cmp r5, r0
	blt _020C13E8
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020C142C: .word UNK_021D2724

	arm_func_start FUN_020C1430
FUN_020C1430: ; 0x020C1430
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, [r0, #0x24]
	mov r1, r1, lsl #0x1f
	movs r1, r1, asr #0x1f
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	bl FUN_020C1348
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C1458
FUN_020C1458: ; 0x020C1458
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x40]
	mov r2, #0x1
	mov r1, #0x0
	mov r2, r2, lsl r0
	ldr r0, [r4, #0x44]
	mov r3, r1
	bl SND_StartTimer
	ldr r0, [r4, #0x24]
	mov r0, r0, lsl #0x1e
	movs r0, r0, asr #0x1f
	ldmneia sp!, {r4,pc}
	add r0, r4, #0x8
	bl PM_PrependPreSleepCallback
	add r0, r4, #0x14
	bl PM_AppendPostSleepCallback
	ldr r0, [r4, #0x24]
	orr r0, r0, #0x2
	str r0, [r4, #0x24]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C14AC
FUN_020C14AC: ; 0x020C14AC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x24
	mov r10, r0
	ldr r4, [r10, #0x24]
	mov r9, r1
	mov r1, r4, lsl #0x1f
	movs r1, r1, asr #0x1f
	ldr r1, [sp, #0x4c]
	str r2, [sp, #0x18]
	mov r4, r3
	str r1, [sp, #0x4c]
	beq _020C14E0
	bl FUN_020C1430
_020C14E0:
	ldr r0, [sp, #0x4c]
	ldr r2, [r10, #0x48]
	mov r0, r0, lsl #0x5
	mul r1, r2, r0
	mov r0, r4
	bl _u32_div_f
	ldr r1, [sp, #0x4c]
	ldr r2, [sp, #0x48]
	mul r1, r0, r1
	mov r0, r1, lsl #0x5
	str r0, [r10, #0x28]
	ldr r0, [r10, #0x28]
	cmp r9, #0x1
	moveq r0, r0, lsr #0x1
	mul r0, r2, r0
	ldr r1, [sp, #0x4c]
	bl _u32_div_f
	str r0, [sp, #0x1c]
	bl FUN_020C02BC
	str r0, [r10, #0x40]
	ldr r0, [r10, #0x40]
	cmp r0, #0x0
	addlt sp, sp, #0x24
	movlt r0, #0x0
	ldmltia sp!, {r4-r11,pc}
	ldr r0, [r10, #0x48]
	mov r8, #0x0
	cmp r0, #0x0
	ble _020C15D4
	ldr r0, [sp, #0x48]
	mov r7, r0, lsl #0x5
	ldr r6, _020C1668 ; =UNK_021D2724
	mov r5, r8
	mov r4, #0x7f
	mov r11, #0x40
	mov r0, #0x1
	str r0, [sp, #0x20]
_020C1574:
	ldr r2, [r10, #0x28]
	ldr r1, [sp, #0x18]
	add r0, r10, r8
	mla r1, r2, r8, r1
	ldrb r0, [r0, #0x4c]
	ldr r3, [sp, #0x20]
	str r1, [r6, r0, lsl #0x3]
	add r1, r6, r0, lsl #0x3
	str r5, [r1, #0x4]
	str r5, [sp, #0x0]
	ldr r2, [r10, #0x28]
	mov r1, r9
	mov r2, r2, lsr #0x2
	str r2, [sp, #0x4]
	str r4, [sp, #0x8]
	str r5, [sp, #0xc]
	str r7, [sp, #0x10]
	str r11, [sp, #0x14]
	ldr r2, [r6, r0, lsl #0x3]
	bl SND_SetupChannelPcm
	ldr r0, [r10, #0x48]
	add r8, r8, #0x1
	cmp r8, r0
	blt _020C1574
_020C15D4:
	str r10, [sp, #0x0]
	ldr r1, [sp, #0x1c]
	ldr r0, [r10, #0x40]
	ldr r3, _020C166C ; =FUN_020C1308
	mov r2, r1
	bl SND_SetupAlarm
	ldr r0, _020C1670 ; =UNK_021D26D8
	mov r1, r10
	bl FUN_020ADBE8
	ldr r0, [sp, #0x4c]
	str r9, [r10, #0x20]
	str r0, [r10, #0x2c]
	ldr r1, [sp, #0x50]
	ldr r0, [sp, #0x54]
	str r1, [r10, #0x30]
	str r0, [r10, #0x34]
	mov r0, #0x0
	str r0, [r10, #0x38]
	str r0, [r10, #0x3c]
	ldr r0, [r10, #0x24]
	bic r0, r0, #0x1
	orr r0, r0, #0x1
	str r0, [r10, #0x24]
	bl OS_DisableInterrupts
	mov r4, r0
	mov r2, #0x1
	mov r0, r10
	mov r1, #0x0
	str r2, [r10, #0x2c]
	bl FUN_020C1254
	ldr r1, [sp, #0x4c]
	mov r0, r4
	str r1, [r10, #0x2c]
	bl OS_RestoreInterrupts
	mov r0, #0x1
	add sp, sp, #0x24
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020C1668: .word UNK_021D2724
_020C166C: .word FUN_020C1308
_020C1670: .word UNK_021D26D8

	arm_func_start FUN_020C1674
FUN_020C1674: ; 0x020C1674
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x44]
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
	bl FUN_020C0340
	mov r0, #0x0
	str r0, [r4, #0x44]
	str r0, [r4, #0x48]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C169C
FUN_020C169C: ; 0x020C169C
	stmdb sp!, {r4-r6,lr}
	mov r5, r1
	mov r4, #0x0
	mov r6, r0
	mov r12, r4
	cmp r5, #0x0
	ble _020C16DC
	mov r1, #0x1
_020C16BC:
	ldrb r3, [r2, r12]
	add r0, r6, r12
	strb r3, [r0, #0x4c]
	ldrb r0, [r2, r12]
	add r12, r12, #0x1
	cmp r12, r5
	orr r4, r4, r1, lsl r0
	blt _020C16BC
_020C16DC:
	mov r0, r4
	bl FUN_020C0370
	cmp r0, #0x0
	moveq r0, #0x0
	strne r5, [r6, #0x48]
	strne r4, [r6, #0x44]
	movne r0, #0x1
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020C16FC
FUN_020C16FC: ; 0x020C16FC
	stmdb sp!, {r4,lr}
	ldr r1, _020C176C ; =UNK_021D26D4
	mov r4, r0
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	bne _020C172C
	ldr r0, _020C1770 ; =UNK_021D26D8
	mov r1, #0x0
	bl FUN_020ADC74
	ldr r0, _020C176C ; =UNK_021D26D4
	mov r1, #0x1
	str r1, [r0, #0x0]
_020C172C:
	ldr r1, _020C1774 ; =FUN_020C1208
	ldr r0, _020C1778 ; =FUN_020C1198
	str r1, [r4, #0x8]
	str r4, [r4, #0xc]
	str r0, [r4, #0x14]
	str r4, [r4, #0x18]
	mov r0, #0x0
	str r0, [r4, #0x44]
	str r0, [r4, #0x48]
	ldr r0, [r4, #0x24]
	bic r0, r0, #0x1
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x24]
	bic r0, r0, #0x2
	str r0, [r4, #0x24]
	ldmia sp!, {r4,pc}
	.balign 4
_020C176C: .word UNK_021D26D4
_020C1770: .word UNK_021D26D8
_020C1774: .word FUN_020C1208
_020C1778: .word FUN_020C1198

	arm_func_start FUN_020C177C
FUN_020C177C: ; 0x020C177C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldr r4, [r7, #0x18]
	ldr r0, [r7, #0x1c]
	ldr r1, _020C186C ; =UNK_021D27A4
	mul r0, r4, r0
	ldr r3, [r7, #0xc]
	ldr r2, [r7, #0x10]
	ldr r1, [r1, #0x0]
	add r6, r3, r0
	cmp r1, #0x0
	add r5, r2, r0
	beq _020C180C
	ldr r2, _020C1870 ; =UNK_021D27A8
	mov r1, #0x14
	ldr r2, [r2, #0x0]
	ldr r3, _020C1874 ; =UNK_021D2820
	mul r1, r2, r1
	str r7, [r3, r1]
	add r1, r3, r1
	str r4, [r1, #0x4]
	str r0, [r1, #0x8]
	str r6, [r1, #0xc]
	ldr r0, _020C1878 ; =UNK_021D27AC
	mov r2, #0x0
	str r5, [r1, #0x10]
	bl OS_SendMessage
	ldr r0, _020C1870 ; =UNK_021D27A8
	ldr r1, [r0, #0x0]
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	cmp r1, #0x8
	movge r1, #0x0
	strge r1, [r0, #0x0]
	b _020C1844
_020C180C:
	mov r0, r6
	mov r1, r4
	bl DC_InvalidateRange
	mov r0, r5
	mov r1, r4
	bl DC_InvalidateRange
	ldr r1, [r7, #0x38]
	mov r0, r6
	str r1, [sp, #0x0]
	ldr r3, [r7, #0x8]
	ldr r6, [r7, #0x34]
	mov r1, r5
	mov r2, r4
	blx r6
_020C1844:
	ldr r0, [r7, #0x1c]
	add r0, r0, #0x1
	str r0, [r7, #0x1c]
	ldr r1, [r7, #0x1c]
	ldr r0, [r7, #0x30]
	cmp r1, r0
	movge r0, #0x0
	strge r0, [r7, #0x1c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C186C: .word UNK_021D27A4
_020C1870: .word UNK_021D27A8
_020C1874: .word UNK_021D2820
_020C1878: .word UNK_021D27AC

	arm_func_start FUN_020C187C
FUN_020C187C: ; 0x020C187C
	stmdb sp!, {r4,lr}
	ldr r4, _020C18F4 ; =UNK_021D27CC
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
	mov r0, #0x0
	str r0, [r4, #0x1c]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x14]
	bl MIi_CpuClear32
	ldr r1, [r4, #0x10]
	ldr r2, [r4, #0x14]
	mov r0, #0x0
	bl MIi_CpuClear32
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x14]
	bl DC_FlushRange
	ldr r0, [r4, #0x10]
	ldr r1, [r4, #0x14]
	bl DC_FlushRange
	ldr r1, [r4, #0x2c]
	mov r3, #0x0
	cmp r1, #0x0
	movge r0, #0x1
	movge r2, r0, lsl r1
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x28]
	movlt r2, #0x0
	bl SND_StartTimer
	ldmia sp!, {r4,pc}
	.balign 4
_020C18F4: .word UNK_021D27CC

	arm_func_start FUN_020C18F8
FUN_020C18F8:
	stmdb sp!, {r4,lr}
	ldr r3, _020C194C ; =UNK_021D27CC
	ldr r0, [r3, #0x0]
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r1, [r3, #0x2c]
	cmp r1, #0x0
	movge r0, #0x1
	movge r2, r0, lsl r1
	ldr r0, [r3, #0x24]
	ldr r1, [r3, #0x28]
	movlt r2, #0x0
	mov r3, #0x0
	bl SND_StopTimer
	bl SND_GetCurrentCommandTag
	mov r4, r0
	mov r0, #0x1
	bl SND_FlushCommand
	mov r0, r4
	bl SND_WaitForCommandProc
	ldmia sp!, {r4,pc}
	.balign 4
_020C194C: .word UNK_021D27CC

	arm_func_start FUN_020C1950
FUN_020C1950: ; 0x020C1950
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r4, _020C1A3C ; =UNK_021D27CC
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
	ldr r1, [r4, #0x2c]
	mov r3, #0x0
	cmp r1, #0x0
	movge r7, #0x1
	movlt r7, #0x0
	cmp r7, #0x0
	movne r0, #0x1
	movne r2, r0, lsl r1
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x28]
	moveq r2, #0x0
	bl SND_StopTimer
	cmp r7, #0x0
	beq _020C19DC
	bl SND_GetCurrentCommandTag
	mov r5, r0
	mov r0, #0x1
	bl SND_FlushCommand
	mov r0, r5
	bl SND_WaitForCommandProc
	ldr r6, _020C1A40 ; =UNK_021D27AC
	mov r5, #0x0
_020C19C4:
	mov r0, r6
	mov r1, r5
	mov r2, r5
	bl OS_ReceiveMessage
	cmp r0, #0x0
	bne _020C19C4
_020C19DC:
	ldr r0, [r4, #0x28]
	cmp r0, #0x0
	beq _020C19EC
	bl FUN_020C0300
_020C19EC:
	ldr r0, [r4, #0x20]
	cmp r0, #0x0
	beq _020C19FC
	bl FUN_020C0340
_020C19FC:
	cmp r7, #0x0
	beq _020C1A0C
	ldr r0, [r4, #0x2c]
	bl FUN_020C029C
_020C1A0C:
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	bne _020C1A2C
	mov r0, #0x0
	mov r1, r0
	mov r2, r0
	mov r3, r0
	bl SND_SetOutputSelector
_020C1A2C:
	mov r0, #0x0
	str r0, [r4, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C1A3C: .word UNK_021D27CC
_020C1A40: .word UNK_021D27AC

	arm_func_start FUN_020C1A44
FUN_020C1A44: ; 0x020C1A44
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x3c
	mov r10, r3
	str r0, [sp, #0x18]
	str r2, [sp, #0x20]
	mov r2, #0x0
	str r1, [sp, #0x1c]
	mov r0, r1
	mov r1, r10
	ldr r9, [sp, #0x6c]
	ldr r8, [sp, #0x74]
	str r2, [sp, #0x2c]
	mvn r6, #0x0
	ldr r4, _020C1D90 ; =UNK_021D27CC
	bl DC_FlushRange
	ldr r0, [sp, #0x20]
	mov r1, r10
	bl DC_FlushRange
	ldr r0, [sp, #0x60]
	ldr r1, [sp, #0x70]
	cmp r0, #0x1
	moveq r7, #0x1
	ldr r0, _020C1D94 ; =0x00FFB0FF
	movne r7, #0x0
	bl _s32_div_f
	ldr r1, [sp, #0x84]
	mov r11, r0
	cmp r1, #0x0
	beq _020C1B00
	add r1, r11, #0x10
	bic r11, r1, #0x1f
	mov r2, r11, asr #0x5
	mov r0, r10
	cmp r7, #0x0
	ldr r1, [sp, #0x80]
	moveq r0, r10, lsr #0x1
	str r2, [sp, #0x34]
	bl _u32_div_f
	ldr r1, [sp, #0x34]
	mov r5, #0x20
	mul r0, r1, r0
	str r0, [sp, #0x30]
	cmp r7, #0x0
	ldr r0, [sp, #0x34]
	moveq r5, r5, lsr #0x1
	mul r0, r5, r0
	mov r5, r0
_020C1B00:
	cmp r7, #0x0
	movne r0, #0x0
	strne r0, [sp, #0x28]
	moveq r0, #0x1
	streq r0, [sp, #0x28]
	cmp r7, #0x0
	movne r0, #0x1
	strne r0, [sp, #0x24]
	moveq r0, #0x0
	streq r0, [sp, #0x24]
	ldr r0, [sp, #0x18]
	cmp r0, #0x2
	movne r0, #0xa
	strne r0, [sp, #0x2c]
	ldr r0, [sp, #0x84]
	cmp r0, #0x0
	beq _020C1B58
	bl FUN_020C02BC
	movs r6, r0
	addmi sp, sp, #0x3c
	movmi r0, #0x0
	ldmmiia sp!, {r4-r11,pc}
_020C1B58:
	mov r0, #0x3
	bl FUN_020C031C
	cmp r0, #0x0
	bne _020C1B84
	cmp r6, #0x0
	blt _020C1B78
	mov r0, r6
	bl FUN_020C029C
_020C1B78:
	add sp, sp, #0x3c
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_020C1B84:
	mov r0, #0xa
	bl FUN_020C0370
	cmp r0, #0x0
	bne _020C1BB8
	cmp r6, #0x0
	blt _020C1BA4
	mov r0, r6
	bl FUN_020C029C
_020C1BA4:
	mov r0, #0x3
	bl FUN_020C0300
	add sp, sp, #0x3c
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_020C1BB8:
	mov r0, #0x0
	mov r7, r10, lsr #0x2
	str r0, [sp, #0x0]
	str r7, [sp, #0x4]
	str r8, [sp, #0x8]
	str r0, [sp, #0xc]
	cmp r9, #0x0
	movne r3, #0x1
	ldr r1, [sp, #0x78]
	str r11, [sp, #0x10]
	str r1, [sp, #0x14]
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x1c]
	moveq r3, #0x2
	mov r0, #0x1
	bl SND_SetupChannelPcm
	ldr r1, [sp, #0x64]
	str r9, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r0, [sp, #0x68]
	ldr r1, [sp, #0x24]
	str r0, [sp, #0x8]
	ldr r2, [sp, #0x1c]
	mov r0, #0x0
	mov r3, r7
	bl SND_SetupCapture
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r7, [sp, #0x4]
	str r8, [sp, #0x8]
	str r0, [sp, #0xc]
	cmp r9, #0x0
	movne r3, #0x1
	ldr r2, [sp, #0x7c]
	str r11, [sp, #0x10]
	str r2, [sp, #0x14]
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x20]
	moveq r3, #0x2
	mov r0, #0x3
	bl SND_SetupChannelPcm
	ldr r2, [sp, #0x64]
	str r9, [sp, #0x0]
	str r2, [sp, #0x4]
	ldr r0, [sp, #0x68]
	ldr r1, [sp, #0x24]
	str r0, [sp, #0x8]
	ldr r2, [sp, #0x20]
	mov r3, r7
	mov r0, #0x1
	bl SND_SetupCapture
	cmp r6, #0x0
	blt _020C1CA8
	ldr r2, [sp, #0x30]
	ldr r3, _020C1D98 ; =FUN_020C177C
	mov r1, r2
	mov r0, r6
	add r1, r1, r5
	str r4, [sp, #0x0]
	bl SND_SetupAlarm
_020C1CA8:
	ldr r0, [sp, #0x18]
	cmp r0, #0x1
	bne _020C1CC8
	mov r0, #0x1
	mov r2, r0
	mov r3, r0
	mov r1, #0x2
	bl SND_SetOutputSelector
_020C1CC8:
	cmp r6, #0x0
	movge r0, #0x1
	movge r2, r0, lsl r6
	ldr r0, [sp, #0x2c]
	movlt r2, #0x0
	mov r1, #0x3
	mov r3, #0x0
	bl SND_StartTimer
	mov r0, #0x1
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x80]
	str r0, [r4, #0x4]
	mov r0, #0xa
	str r0, [r4, #0x20]
	ldr r0, [sp, #0x2c]
	str r0, [r4, #0x24]
	mov r0, #0x3
	str r0, [r4, #0x28]
	ldr r0, [sp, #0x60]
	str r6, [r4, #0x2c]
	str r0, [r4, #0x8]
	ldr r0, [sp, #0x1c]
	str r0, [r4, #0xc]
	ldr r0, [sp, #0x20]
	str r0, [r4, #0x10]
	mov r0, r10
	str r10, [r4, #0x14]
	bl _u32_div_f
	str r0, [r4, #0x18]
	mov r1, #0x0
	str r1, [r4, #0x1c]
	ldr r0, [sp, #0x80]
	ldr r1, [sp, #0x84]
	str r0, [r4, #0x30]
	ldr r0, [sp, #0x88]
	str r1, [r4, #0x34]
	str r0, [r4, #0x38]
	add r0, r4, #0x3c
	str r8, [r4, #0x50]
	bl FUN_020C3E6C
	add r0, r4, #0x3c
	mov r1, r8, lsl #0x8
	mov r2, #0x1
	bl FUN_020C3E40
	mov r0, #0x0
	str r0, [r4, #0x4c]
	mov r0, #0x1
	add sp, sp, #0x3c
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020C1D90: .word UNK_021D27CC
_020C1D94: .word 0x00FFB0FF
_020C1D98: .word FUN_020C177C

	arm_func_start FUN_020C1D9C
FUN_020C1D9C: ; 0x020C1D9C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r5, _020C1E34 ; =UNK_021D27CC
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,pc}
	add r4, r5, #0x3c
	mov r0, r4
	bl FUN_020C3DF4
	ldr r0, [r5, #0x4c]
	cmp r0, #0x0
	beq _020C1DFC
	mov r0, r4
	bl FUN_020C3DDC
	cmp r0, #0x0
	beq _020C1DFC
	bl FUN_020C1950
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
_020C1DFC:
	mov r0, r4
	bl FUN_020C3E0C
	ldr r1, [r5, #0x50]
	mov r4, r0, asr #0x8
	cmp r4, r1
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
	ldr r0, [r5, #0x24]
	mov r1, r4
	mov r2, #0x0
	bl SND_SetChannelVolume
	str r4, [r5, #0x50]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C1E34: .word UNK_021D27CC

	arm_func_start FUN_020C1E38
FUN_020C1E38: ; 0x020C1E38
	ldr r1, _020C1E50 ; =UNK_021D27A4
	mov r2, #0x0
	ldr r0, _020C1E54 ; =UNK_021D27CC
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	bx lr
	.balign 4
_020C1E50: .word UNK_021D27A4
_020C1E54: .word UNK_021D27CC

	arm_func_start FUN_020C1E58
FUN_020C1E58: ; 0x020C1E58
	ldr r0, _020C1E64 ; =UNK_021D27CC
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020C1E64: .word UNK_021D27CC

	arm_func_start FUN_020C1E68
FUN_020C1E68: ; 0x020C1E68
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C1EA0 ; =UNK_021D27CC
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r0, [r0, #0x4]
	cmp r0, #0x1
	addne sp, sp, #0x4
	ldmneia sp!, {pc}
	bl FUN_020C1950
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020C1EA0: .word UNK_021D27CC

	arm_func_start FUN_020C1EA4
FUN_020C1EA4: ; 0x020C1EA4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x2c
	mov r5, r0
	mov r4, r1
	mov r7, r2
	mov r6, r3
	bl FUN_020C1E68
	ldr r0, _020C1F50 ; =UNK_021D27CC
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x2c
	movne r0, #0x0
	ldmneia sp!, {r4-r7,pc}
	mov r1, r5
	mov r2, r4
	mov r0, #0x0
	bl MIi_CpuClear32
	mov r0, r5
	mov r1, r4
	bl DC_FlushRange
	str r7, [sp, #0x0]
	mov r2, #0x0
	str r2, [sp, #0x4]
	str r2, [sp, #0x8]
	mov r0, #0x1
	str r0, [sp, #0xc]
	str r6, [sp, #0x10]
	mov r1, #0x7f
	str r1, [sp, #0x14]
	str r2, [sp, #0x18]
	ldr r2, [sp, #0x40]
	str r1, [sp, #0x1c]
	ldr r1, [sp, #0x44]
	str r2, [sp, #0x20]
	ldr r12, [sp, #0x48]
	str r1, [sp, #0x24]
	mov r1, r5
	mov r3, r4, lsr #0x1
	add r2, r5, r4, lsr #0x1
	str r12, [sp, #0x28]
	bl FUN_020C1A44
	add sp, sp, #0x2c
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C1F50: .word UNK_021D27CC

	arm_func_start FUN_020C1F54
FUN_020C1F54: ; 0x020C1F54
	stmdb sp!, {r4,lr}
	ldr r4, _020C1FA0 ; =UNK_021D27CC
	mov r2, r0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	ldmneia sp!, {r4,pc}
	cmp r2, #0x0
	bne _020C1F88
	bl FUN_020C1950
	ldmia sp!, {r4,pc}
_020C1F88:
	add r0, r4, #0x3c
	mov r1, #0x0
	bl FUN_020C3E40
	mov r0, #0x1
	str r0, [r4, #0x4c]
	ldmia sp!, {r4,pc}
	.balign 4
_020C1FA0: .word UNK_021D27CC

	arm_func_start FUN_020C1FA4
FUN_020C1FA4: ; 0x020C1FA4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, _020C1FEC ; =UNK_021D27CC
	mov r12, r0
	ldr r0, [r3, #0x0]
	mov r2, r1
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r0, [r3, #0x4]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {pc}
	add r0, r3, #0x3c
	mov r1, r12, lsl #0x8
	bl FUN_020C3E40
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020C1FEC: .word UNK_021D27CC

	arm_func_start FUN_020C1FF0
FUN_020C1FF0: ; 0x020C1FF0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x2c
	mov r5, r0
	mov r0, #0x0
	mov r4, r1
	mov r7, r2
	mov r6, r3
	bl FUN_020C1F54
	ldr r0, _020C2098 ; =UNK_021D27CC
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x2c
	movne r0, #0x0
	ldmneia sp!, {r4-r7,pc}
	mov r1, r5
	mov r2, r4
	mov r0, #0x0
	bl MIi_CpuClear32
	mov r0, r5
	mov r1, r4
	bl DC_FlushRange
	str r7, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r1, #0x1
	str r1, [sp, #0xc]
	ldr r1, [sp, #0x40]
	str r6, [sp, #0x10]
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	mov r1, #0x7f
	str r1, [sp, #0x1c]
	str r0, [sp, #0x20]
	str r0, [sp, #0x24]
	mov r1, r5
	mov r3, r4, lsr #0x1
	add r2, r5, r4, lsr #0x1
	str r0, [sp, #0x28]
	bl FUN_020C1A44
	add sp, sp, #0x2c
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C2098: .word UNK_021D27CC

	arm_func_start FUN_020C209C
FUN_020C209C: ; 0x020C209C
	mov r0, #0x0
	str r0, [r2, #0x88]
	bx lr

	arm_func_start FUN_020C20A8
FUN_020C20A8: ; 0x020C20A8
	mov r0, #0x0
	str r0, [r2, #0x84]
	bx lr

	arm_func_start FUN_020C20B4
FUN_020C20B4: ; 0x020C20B4
	mov r0, #0x0
	str r0, [r2, #0x8c]
	bx lr

	arm_func_start FUN_020C20C0
FUN_020C20C0: ; 0x020C20C0
	ldr r2, _020C20D8 ; =UNK_021D28C0
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x84]
	add r0, r2, r0, lsl #0x4
	str r1, [r0, #0x14]
	bx lr
	.balign 4
_020C20D8: .word UNK_021D28C0

	arm_func_start FUN_020C20DC
FUN_020C20DC:
	ldr r1, _020C2100 ; =UNK_021D28C0
	ldr r1, [r1, #0x0]
	ldr r2, [r1, #0x84]
	ldr r1, [r2, #0x8]
	cmp r0, r1
	movcs r0, #0x0
	addcc r0, r2, r0, lsl #0x4
	ldrcc r0, [r0, #0x14]
	bx lr
	.balign 4
_020C2100: .word UNK_021D28C0

	arm_func_start FUN_020C2104
FUN_020C2104:
	stmdb sp!, {r4-r6,lr}
	ldr r4, _020C2178 ; =UNK_021D28C0
	mov r5, r2
	ldr r4, [r4, #0x0]
	mov r6, r1
	ldr r2, [r4, #0x84]
	ldr r1, [r2, #0x8]
	cmp r0, r1
	mvncs r0, #0x0
	ldmcsia sp!, {r4-r6,pc}
	add r1, r2, #0xc
	add r1, r1, r0, lsl #0x4
	ldr r0, [r1, #0x4]
	ldr r1, [r1, #0x0]
	sub r0, r0, r3
	cmp r5, r0
	movhi r5, r0
	add r0, r4, #0x34
	add r1, r1, r3
	mov r2, #0x0
	bl FS_SeekFile
	cmp r0, #0x0
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	mov r1, r6
	mov r2, r5
	add r0, r4, #0x34
	bl FS_ReadFile
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C2178: .word UNK_021D28C0

	arm_func_start FUN_020C217C
FUN_020C217C: ; 0x020C217C
	ldr r1, _020C21A0 ; =UNK_021D28C0
	ldr r1, [r1, #0x0]
	ldr r2, [r1, #0x84]
	ldr r1, [r2, #0x8]
	cmp r0, r1
	movcs r0, #0x0
	addcc r0, r2, r0, lsl #0x4
	ldrcc r0, [r0, #0x10]
	bx lr
	.balign 4
_020C21A0: .word UNK_021D28C0

	arm_func_start FUN_020C21A4
FUN_020C21A4: ; 0x020C21A4
	ldr r1, _020C2204 ; =UNK_021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0x1c]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C2204: .word UNK_021D28C0

	arm_func_start FUN_020C2208
FUN_020C2208: ; 0x020C2208
	ldr r1, _020C2268 ; =UNK_021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0x18]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C2268: .word UNK_021D28C0

	arm_func_start FUN_020C226C
FUN_020C226C:
	ldr r1, _020C22CC ; =UNK_021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0x14]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C22CC: .word UNK_021D28C0

	arm_func_start FUN_020C22D0
FUN_020C22D0: ; 0x020C22D0
	ldr r1, _020C2330 ; =UNK_021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0x10]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C2330: .word UNK_021D28C0

	arm_func_start FUN_020C2334
FUN_020C2334:
	ldr r1, _020C2394 ; =UNK_021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0xc]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C2394: .word UNK_021D28C0

	arm_func_start FUN_020C2398
FUN_020C2398:
	ldr r1, _020C23F8 ; =UNK_021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0x8]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C23F8: .word UNK_021D28C0

	arm_func_start FUN_020C23FC
FUN_020C23FC: ; 0x020C23FC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020C2398
	cmp r0, #0x0
	moveq r0, #0x0
	addne r0, r0, #0x4
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C241C
FUN_020C241C: ; 0x020C241C
	ldr r0, _020C2428 ; =UNK_021D28C0
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020C2428: .word UNK_021D28C0

	arm_func_start FUN_020C242C
FUN_020C242C: ; 0x020C242C
	ldr r1, _020C2440 ; =UNK_021D28C0
	ldr r2, [r1, #0x0]
	str r0, [r1, #0x0]
	mov r0, r2
	bx lr
	.balign 4
_020C2440: .word UNK_021D28C0

	arm_func_start FUN_020C2444
FUN_020C2444: ; 0x020C2444
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	mov r0, r4
	mov r1, r5
	mov r2, #0x30
	bl MIi_CpuCopy32
	ldr r0, [r5, #0x18]
	mov r12, #0x0
	cmp r0, #0x0
	moveq r0, #0x0
	addne r0, r4, r0
	str r0, [r5, #0x8c]
	ldr r0, [r5, #0x20]
	cmp r0, #0x0
	moveq r0, #0x0
	addne r0, r4, r0
	str r0, [r5, #0x84]
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	moveq r0, #0x0
	addne r0, r4, r0
	str r0, [r5, #0x88]
	ldr r2, [r5, #0x84]
	ldr r0, [r2, #0x8]
	cmp r0, #0x0
	bls _020C24F0
	mov r3, r12
	mov r1, r12
_020C24BC:
	add r2, r2, #0xc
	ldr r0, [r2, r3]
	add r2, r2, r3
	cmp r0, #0x0
	moveq r0, r1
	addne r0, r4, r0
	str r0, [r2, #0x8]
	ldr r2, [r5, #0x84]
	add r12, r12, #0x1
	ldr r0, [r2, #0x8]
	add r3, r3, #0x10
	cmp r12, r0
	blo _020C24BC
_020C24F0:
	mov r1, #0x0
	ldr r0, _020C2508 ; =UNK_021D28C0
	str r1, [r5, #0x30]
	str r5, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C2508: .word UNK_021D28C0

	arm_func_start FUN_020C250C
FUN_020C250C:
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r6, r0
	mov r5, r1
	mov r1, #0x0
	mov r4, r2
	mov r2, r1
	add r0, r6, #0x34
	bl FS_SeekFile
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	mov r1, r6
	add r0, r6, #0x34
	mov r2, #0x30
	bl FS_ReadFile
	cmp r0, #0x30
	addne sp, sp, #0x8
	movne r0, #0x0
	ldmneia sp!, {r4-r6,pc}
	cmp r5, #0x0
	beq _020C26E0
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r1, [r6, #0x1c]
	ldr r2, _020C26EC ; =FUN_020C20B4
	mov r0, r5
	mov r3, r6
	bl FUN_020C2958
	str r0, [r6, #0x8c]
	ldr r0, [r6, #0x8c]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r1, [r6, #0x18]
	add r0, r6, #0x34
	mov r2, #0x0
	bl FS_SeekFile
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r1, [r6, #0x8c]
	ldr r2, [r6, #0x1c]
	add r0, r6, #0x34
	bl FS_ReadFile
	ldr r1, [r6, #0x1c]
	cmp r0, r1
	addne sp, sp, #0x8
	movne r0, #0x0
	ldmneia sp!, {r4-r6,pc}
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r1, [r6, #0x24]
	ldr r2, _020C26F0 ; =FUN_020C20A8
	mov r0, r5
	mov r3, r6
	bl FUN_020C2958
	str r0, [r6, #0x84]
	ldr r0, [r6, #0x84]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r1, [r6, #0x20]
	add r0, r6, #0x34
	mov r2, #0x0
	bl FS_SeekFile
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r1, [r6, #0x84]
	ldr r2, [r6, #0x24]
	add r0, r6, #0x34
	bl FS_ReadFile
	ldr r1, [r6, #0x24]
	cmp r0, r1
	addne sp, sp, #0x8
	movne r0, #0x0
	ldmneia sp!, {r4-r6,pc}
	cmp r4, #0x0
	beq _020C26E0
	ldr r1, [r6, #0x14]
	cmp r1, #0x0
	beq _020C26E0
	mov r4, #0x0
	ldr r2, _020C26F4 ; =FUN_020C209C
	mov r0, r5
	mov r3, r6
	str r4, [sp, #0x0]
	bl FUN_020C2958
	str r0, [r6, #0x88]
	ldr r0, [r6, #0x88]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, r4
	ldmeqia sp!, {r4-r6,pc}
	ldr r1, [r6, #0x10]
	add r0, r6, #0x34
	mov r2, r4
	bl FS_SeekFile
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, r4
	ldmeqia sp!, {r4-r6,pc}
	ldr r1, [r6, #0x88]
	ldr r2, [r6, #0x14]
	add r0, r6, #0x34
	bl FS_ReadFile
	ldr r1, [r6, #0x14]
	cmp r0, r1
	addne sp, sp, #0x8
	movne r0, r4
	ldmneia sp!, {r4-r6,pc}
_020C26E0:
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C26EC: .word FUN_020C20B4
_020C26F0: .word FUN_020C20A8
_020C26F4: .word FUN_020C209C

	arm_func_start FUN_020C26F8
FUN_020C26F8: ; 0x020C26F8
	; r0: &sSoundDataBuffer
	; r1: char* filename
	; r2: (&sSoundDataBuffer)->unk_0090
	; r3: 0
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r12, #0x0
	str r12, [r6, #0x8c]
	str r12, [r6, #0x84]
	add r0, r6, #0x7c
	mov r5, r2
	mov r4, r3
	str r12, [r6, #0x88]
	bl FS_ConvertPathToFileID
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	add r0, r6, #0x34
	bl FS_InitFile
	add r1, r6, #0x7c
	add r0, r6, #0x34
	ldmia r1, {r1-r2}
	bl FS_OpenFileFast
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	mov r3, #0x1
	mov r0, r6
	mov r1, r5
	mov r2, r4
	str r3, [r6, #0x30]
	bl FUN_020C250C
	cmp r0, #0x0
	ldrne r0, _020C2770 ; =UNK_021D28C0
	strne r6, [r0, #0x0]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C2770: .word UNK_021D28C0

	arm_func_start FUN_020C2774
FUN_020C2774: ; 0x020C2774
	stmdb sp!, {r4,lr}
	bl SND_GetCurrentCommandTag
	mov r4, r0
	mov r0, #0x1
	bl SND_FlushCommand
	mov r0, r4
	bl SND_WaitForCommandProc
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C2794
FUN_020C2794:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, [r5, #0x0]
	mov r1, #0x14
	mov r2, #0x4
	bl FUN_020AE638
	movs r4, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
	bl FUN_020C2818
	mov r1, r4
	add r0, r5, #0x4
	bl FUN_020ADBE8
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C27DC
FUN_020C27DC:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	add r0, r5, #0x4
	mov r1, #0xc
	bl FUN_020ADC74
	mov r0, r5
	str r4, [r5, #0x0]
	bl FUN_020C2794
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C2818
FUN_020C2818: ; 0x020C2818
	ldr ip, _020C2824 ; =FUN_020ADC74
	mov r1, #0x0
	bx r12
	.balign 4
_020C2824: .word FUN_020ADC74

	arm_func_start FUN_020C2828
FUN_020C2828: ; 0x020C2828
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r7, #0x0
	movs r9, r1
	mov r10, r0
	mov r6, r7
	bne _020C2850
	bl FUN_020C29C0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
_020C2850:
	ldrh r0, [r10, #0xc]
	cmp r9, r0
	bge _020C28D8
	mov r11, r7
	add r5, r10, #0x4
	mov r4, #0x1
_020C2868:
	mov r0, r5
	mov r1, r11
	bl FUN_020ADA84
	mov r1, r7
	mov r8, r0
	bl FUN_020ADA84
	movs r7, r0
	beq _020C28C0
_020C2888:
	ldr r12, [r7, #0xc]
	cmp r12, #0x0
	beq _020C28AC
	ldr r1, [r7, #0x8]
	ldr r2, [r7, #0x10]
	ldr r3, [r7, #0x14]
	add r0, r7, #0x20
	blx r12
	mov r6, r4
_020C28AC:
	mov r0, r8
	mov r1, r7
	bl FUN_020ADA84
	movs r7, r0
	bne _020C2888
_020C28C0:
	mov r0, r5
	mov r1, r8
	bl FUN_020ADAB0
	ldrh r0, [r10, #0xc]
	cmp r9, r0
	blt _020C2868
_020C28D8:
	ldr r0, [r10, #0x0]
	mov r1, r9
	bl FUN_020AE554
	cmp r6, #0x0
	beq _020C28F0
	bl FUN_020C2774
_020C28F0:
	ldrh r1, [r10, #0xc]
	ldr r0, [r10, #0x0]
	bl FUN_020AE5B0
	mov r0, r10
	bl FUN_020C2794
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020C290C
FUN_020C290C: ; 0x020C290C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldrh r1, [r4, #0xc]
	ldr r0, [r4, #0x0]
	bl FUN_020AE5B0
	cmp r0, #0x0
	mvneq r0, #0x0
	ldmeqia sp!, {r4,pc}
	mov r0, r4
	bl FUN_020C2794
	cmp r0, #0x0
	ldrneh r0, [r4, #0xc]
	subne r0, r0, #0x1
	ldmneia sp!, {r4,pc}
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl FUN_020AE554
	mvn r0, #0x0
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C2958
FUN_020C2958: ; 0x020C2958
	stmdb sp!, {r4-r8,lr}
	mov r7, r1
	mov r8, r0
	add r0, r7, #0x1f
	bic r1, r0, #0x1f
	mov r6, r2
	ldr r0, [r8, #0x0]
	add r1, r1, #0x20
	mov r2, #0x20
	mov r5, r3
	bl FUN_020AE638
	movs r4, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	add r0, r8, #0x4
	mov r1, #0x0
	bl FUN_020ADA84
	str r7, [r4, #0x8]
	str r6, [r4, #0xc]
	ldr r2, [sp, #0x18]
	str r5, [r4, #0x10]
	mov r1, r4
	str r2, [r4, #0x14]
	bl FUN_020ADBE8
	add r0, r4, #0x20
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020C29C0
FUN_020C29C0:
	stmdb sp!, {r4-r10,lr}
	mov r8, r0
	mov r5, #0x0
	mov r1, r5
	add r0, r8, #0x4
	bl FUN_020ADA84
	movs r7, r0
	beq _020C2A58
	add r9, r8, #0x4
	mov r10, #0x1
	mov r4, r5
_020C29EC:
	mov r0, r7
	mov r1, r4
	bl FUN_020ADA84
	movs r6, r0
	beq _020C2A38
_020C2A00:
	ldr r12, [r6, #0xc]
	cmp r12, #0x0
	beq _020C2A24
	ldr r1, [r6, #0x8]
	ldr r2, [r6, #0x10]
	ldr r3, [r6, #0x14]
	add r0, r6, #0x20
	blx r12
	mov r5, r10
_020C2A24:
	mov r0, r7
	mov r1, r6
	bl FUN_020ADA84
	movs r6, r0
	bne _020C2A00
_020C2A38:
	mov r0, r9
	mov r1, r7
	bl FUN_020ADAB0
	mov r0, r9
	mov r1, r4
	bl FUN_020ADA84
	movs r7, r0
	bne _020C29EC
_020C2A58:
	ldr r0, [r8, #0x0]
	mov r1, #0x3
	bl FUN_020AE600
	cmp r5, #0x0
	beq _020C2A70
	bl FUN_020C2774
_020C2A70:
	mov r0, r8
	bl FUN_020C2794
	ldmia sp!, {r4-r10,pc}

	arm_func_start FUN_020C2A7C
FUN_020C2A7C: ; 0x020C2A7C
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020C29C0
	ldr r0, [r4, #0x0]
	bl thunk_FUN_020adc8c_2
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C2A94
FUN_020C2A94:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	add r2, r0, #0x3
	add r0, r0, r1
	bic r5, r2, #0x3
	cmp r5, r0
	addhi sp, sp, #0x4
	movhi r0, #0x0
	ldmhiia sp!, {r4-r5,pc}
	sub r1, r0, r5
	cmp r1, #0x10
	addcc sp, sp, #0x4
	movcc r0, #0x0
	ldmccia sp!, {r4-r5,pc}
	add r0, r5, #0x10
	sub r1, r1, #0x10
	mov r2, #0x0
	bl FUN_020AE684
	movs r4, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
	mov r0, r5
	mov r1, r4
	bl FUN_020C27DC
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, r5
	ldmneia sp!, {r4-r5,pc}
	mov r0, r4
	bl thunk_FUN_020adc8c_2
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C2B1C
FUN_020C2B1C:
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x20
	mov r8, r0
	add r0, sp, #0x8
	mov r7, r1
	mov r6, r2
	mov r5, r3
	ldr r4, [sp, #0x40]
	bl SND_GetFirstInstDataPos
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	cmp r7, #0x0
	add r2, sp, #0x0
	addeq sp, sp, #0x20
	moveq r0, #0x0
	ldmeqia sp!, {r4-r10,pc}
	add r1, sp, #0x10
	mov r0, r7
	bl SND_GetNextInstData
	cmp r0, #0x0
	beq _020C2BD4
	add r10, sp, #0x10
	add r9, sp, #0x0
_020C2B80:
	ldrb r0, [sp, #0x10]
	cmp r0, #0x1
	bne _020C2BBC
	ldrh r0, [sp, #0x14]
	cmp r6, r0
	bne _020C2BBC
	ldrh r1, [sp, #0x12]
	mov r0, r8
	mov r2, r5
	mov r3, r4
	bl FUN_020C2BE0
	cmp r0, #0x0
	addeq sp, sp, #0x20
	moveq r0, #0x0
	ldmeqia sp!, {r4-r10,pc}
_020C2BBC:
	mov r0, r7
	mov r1, r10
	mov r2, r9
	bl SND_GetNextInstData
	cmp r0, #0x0
	bne _020C2B80
_020C2BD4:
	mov r0, #0x1
	add sp, sp, #0x20
	ldmia sp!, {r4-r10,pc}

	arm_func_start FUN_020C2BE0
FUN_020C2BE0:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl SND_GetWaveDataAddress
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, #0x1
	ldmneia sp!, {r4-r9,pc}
	mov r0, r7
	bl SND_GetWaveDataCount
	ldr r1, [r7, #0x38]
	sub r0, r0, #0x1
	add r1, r1, r6
	add r1, r7, r1, lsl #0x2
	cmp r6, r0
	ldrcc r0, [r1, #0x40]
	ldr r8, [r1, #0x3c]
	ldrcs r0, [r7, #0x8]
	cmp r4, #0x0
	sub r9, r0, r8
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,pc}
	ldr r2, _020C2CBC ; =FUN_020C2CC0
	mov r0, r4
	mov r3, r7
	add r1, r9, #0x20
	str r6, [sp, #0x0]
	bl FUN_020C2958
	movs r4, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,pc}
	mov r0, r5
	mov r1, r4
	mov r2, r9
	mov r3, r8
	bl FUN_020C2104
	cmp r9, r0
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r9,pc}
	mov r0, r4
	mov r1, r9
	bl DC_StoreRange
	mov r0, r7
	mov r1, r6
	mov r2, r4
	bl SND_SetWaveDataAddress
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020C2CBC: .word FUN_020C2CC0

	arm_func_start FUN_020C2CC0
FUN_020C2CC0: ; 0x020C2CC0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r2
	mov r7, r0
	mov r4, r3
	mov r6, r1
	mov r0, r5
	mov r1, r4
	bl SND_GetWaveDataAddress
	cmp r7, r0
	bne _020C2CFC
	mov r0, r5
	mov r1, r4
	mov r2, #0x0
	bl SND_SetWaveDataAddress
_020C2CFC:
	mov r0, r7
	add r1, r7, r6
	bl SND_InvalidateWaveData
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020C2D10
FUN_020C2D10: ; 0x020C2D10
	stmdb sp!, {r4,lr}
	mov r1, r2
	mov r4, r0
	mov r2, r3
	bl FUN_020C2DD0
	mov r0, r4
	bl SND_DestroyWaveArc
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C2D30
FUN_020C2D30: ; 0x020C2D30
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r1, r2
	mov r5, r0
	mov r2, r3
	bl FUN_020C2DD0
	mov r0, r5
	add r1, r5, r4
	bl SND_InvalidateWaveData
	mov r0, r5
	bl SND_DestroyWaveArc
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C2D68
FUN_020C2D68: ; 0x020C2D68
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r1, r2
	mov r5, r0
	mov r2, r3
	bl FUN_020C2DD0
	mov r0, r5
	add r1, r5, r4
	bl SND_InvalidateBankData
	mov r0, r5
	bl SND_DestroyBank
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C2DA0
FUN_020C2DA0: ; 0x020C2DA0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r1, r2
	mov r5, r0
	mov r2, r3
	bl FUN_020C2DD0
	mov r0, r5
	add r1, r5, r4
	bl SND_InvalidateSeqData
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C2DD0
FUN_020C2DD0: ; 0x020C2DD0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	movs r5, r1
	mov r7, r0
	mov r6, r2
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
	bl OS_DisableInterrupts
	mov r4, r0
	mov r0, r5
	bl FUN_020C242C
	mov r5, r0
	mov r0, r6
	bl FUN_020C20DC
	cmp r7, r0
	bne _020C2E1C
	mov r0, r6
	mov r1, #0x0
	bl FUN_020C20C0
_020C2E1C:
	mov r0, r5
	bl FUN_020C242C
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020C2E34
FUN_020C2E34: ; 0x020C2E34
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	mov r8, r1
	mov r7, r2
	bl FUN_020C20DC
	movs r6, r0
	bne _020C2F40
	ldr r1, _020C2F4C ; =UNK_021D28C4
	mov r0, r9
	mov r2, #0x3c
	mov r3, #0x0
	bl FUN_020C2104
	cmp r0, #0x3c
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r9,pc}
	ldr r0, _020C2F4C ; =UNK_021D28C4
	cmp r8, #0x0
	ldr r0, [r0, #0x38]
	addeq sp, sp, #0x4
	mov r4, r0, lsl #0x2
	mov r0, r4, lsl #0x1
	add r5, r0, #0x3c
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,pc}
	cmp r7, #0x0
	moveq r3, #0x0
	beq _020C2EB0
	bl FUN_020C241C
	mov r3, r0
_020C2EB0:
	ldr r2, _020C2F50 ; =FUN_020C2D10
	mov r0, r8
	add r1, r5, #0x20
	str r9, [sp, #0x0]
	bl FUN_020C2958
	movs r6, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,pc}
	mov r0, r9
	mov r1, r6
	add r2, r4, #0x3c
	mov r3, #0x0
	bl FUN_020C2104
	add r1, r4, #0x3c
	cmp r0, r1
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r9,pc}
	ldr r1, [r6, #0x38]
	add r0, r6, #0x3c
	mov r2, r4
	add r1, r0, r1, lsl #0x2
	bl MI_CpuCopy8
	mov r2, r4
	add r0, r6, #0x3c
	mov r1, #0x0
	bl MI_CpuFill8
	mov r0, r6
	mov r1, r5
	bl DC_StoreRange
	cmp r7, #0x0
	beq _020C2F40
	mov r0, r9
	mov r1, r6
	bl FUN_020C20C0
_020C2F40:
	mov r0, r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020C2F4C: .word UNK_021D28C4
_020C2F50: .word FUN_020C2D10

	arm_func_start FUN_020C2F54
FUN_020C2F54:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl FUN_020C20DC
	movs r4, r0
	bne _020C2FBC
	cmp r5, #0x0
	moveq r2, #0x0
	beq _020C2F88
	bl FUN_020C241C
	mov r2, r0
_020C2F88:
	ldr r1, _020C2FC8 ; =FUN_020C2D30
	mov r0, r7
	mov r3, r7
	str r6, [sp, #0x0]
	bl FUN_020C3134
	mov r4, r0
	cmp r5, #0x0
	beq _020C2FBC
	cmp r4, #0x0
	beq _020C2FBC
	mov r0, r7
	mov r1, r4
	bl FUN_020C20C0
_020C2FBC:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C2FC8: .word FUN_020C2D30

	arm_func_start FUN_020C2FCC
FUN_020C2FCC: ; 0x020C2FCC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl FUN_020C20DC
	movs r4, r0
	bne _020C3034
	cmp r5, #0x0
	moveq r2, #0x0
	beq _020C3000
	bl FUN_020C241C
	mov r2, r0
_020C3000:
	ldr r1, _020C3040 ; =FUN_020C2D68
	mov r0, r7
	mov r3, r7
	str r6, [sp, #0x0]
	bl FUN_020C3134
	mov r4, r0
	cmp r5, #0x0
	beq _020C3034
	cmp r4, #0x0
	beq _020C3034
	mov r0, r7
	mov r1, r4
	bl FUN_020C20C0
_020C3034:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C3040: .word FUN_020C2D68

	arm_func_start FUN_020C3044
FUN_020C3044:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl FUN_020C20DC
	movs r4, r0
	bne _020C30AC
	cmp r5, #0x0
	moveq r2, #0x0
	beq _020C3078
	bl FUN_020C241C
	mov r2, r0
_020C3078:
	ldr r1, _020C30B8 ; =FUN_020C2DA0
	mov r0, r7
	mov r3, r7
	str r6, [sp, #0x0]
	bl FUN_020C3134
	mov r4, r0
	cmp r5, #0x0
	beq _020C30AC
	cmp r4, #0x0
	beq _020C30AC
	mov r0, r7
	mov r1, r4
	bl FUN_020C20C0
_020C30AC:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C30B8: .word FUN_020C2DA0

	arm_func_start FUN_020C30BC
FUN_020C30BC:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl FUN_020C20DC
	movs r4, r0
	bne _020C3124
	cmp r5, #0x0
	moveq r2, #0x0
	beq _020C30F0
	bl FUN_020C241C
	mov r2, r0
_020C30F0:
	ldr r1, _020C3130 ; =FUN_020C2DA0
	mov r0, r7
	mov r3, r7
	str r6, [sp, #0x0]
	bl FUN_020C3134
	mov r4, r0
	cmp r5, #0x0
	beq _020C3124
	cmp r4, #0x0
	beq _020C3124
	mov r0, r7
	mov r1, r4
	bl FUN_020C20C0
_020C3124:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C3130: .word FUN_020C2DA0

	arm_func_start FUN_020C3134
FUN_020C3134: ; 0x020C3134
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r4, r3
	bl FUN_020C217C
	movs r5, r0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	mov r2, r7
	mov r3, r6
	add r1, r5, #0x20
	str r4, [sp, #0x0]
	bl FUN_020C2958
	movs r4, r0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	mov r0, r8
	mov r1, r4
	mov r2, r5
	mov r3, #0x0
	bl FUN_020C2104
	cmp r5, r0
	addne sp, sp, #0x8
	movne r0, #0x0
	ldmneia sp!, {r4-r8,pc}
	mov r0, r4
	mov r1, r5
	bl DC_StoreRange
	mov r0, r4
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020C31D4
FUN_020C31D4:
	stmdb sp!, {r4-r6,lr}
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl FUN_020C226C
	cmp r0, #0x0
	moveq r0, #0x5
	ldmeqia sp!, {r4-r6,pc}
	ands r1, r6, #0x4
	beq _020C324C
	ldrb r1, [r0, #0x3]
	ands r1, r1, #0x1
	beq _020C3224
	ldr r0, [r0, #0x0]
	mov r1, r5
	mov r0, r0, lsl #0x8
	mov r2, r4
	mov r0, r0, lsr #0x8
	bl FUN_020C2E34
	b _020C323C
_020C3224:
	ldr r0, [r0, #0x0]
	mov r1, r5
	mov r0, r0, lsl #0x8
	mov r2, r4
	mov r0, r0, lsr #0x8
	bl FUN_020C2F54
_020C323C:
	cmp r0, #0x0
	bne _020C325C
	mov r0, #0x9
	ldmia sp!, {r4-r6,pc}
_020C324C:
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x8
	mov r0, r0, lsr #0x8
	bl FUN_020C20DC
_020C325C:
	ldr r1, [sp, #0x10]
	cmp r1, #0x0
	strne r0, [r1, #0x0]
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020C3270
FUN_020C3270:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r10, r1
	mov r9, r2
	mov r11, r3
	bl FUN_020C22D0
	movs r8, r0
	addeq sp, sp, #0xc
	moveq r0, #0x4
	ldmeqia sp!, {r4-r11,pc}
	ands r0, r10, #0x2
	beq _020C32C4
	ldr r0, [r8, #0x0]
	mov r1, r9
	mov r2, r11
	bl FUN_020C2FCC
	movs r7, r0
	bne _020C32D0
	add sp, sp, #0xc
	mov r0, #0x8
	ldmia sp!, {r4-r11,pc}
_020C32C4:
	ldr r0, [r8, #0x0]
	bl FUN_020C20DC
	mov r7, r0
_020C32D0:
	and r5, r10, #0x4
	mov r6, #0x0
_020C32D8:
	add r0, r8, r6, lsl #0x1
	ldrh r0, [r0, #0x4]
	ldr r1, _020C33B4 ; =0x0000FFFF
	cmp r0, r1
	beq _020C3390
	bl FUN_020C226C
	movs r4, r0
	addeq sp, sp, #0xc
	moveq r0, #0x5
	ldmeqia sp!, {r4-r11,pc}
	add r0, sp, #0x4
	str r0, [sp, #0x0]
	add r0, r8, r6, lsl #0x1
	ldrh r0, [r0, #0x4]
	mov r1, r10
	mov r2, r9
	mov r3, r11
	bl FUN_020C31D4
	cmp r0, #0x0
	addne sp, sp, #0xc
	ldmneia sp!, {r4-r11,pc}
	ldrb r0, [r4, #0x3]
	ands r0, r0, #0x1
	beq _020C3370
	cmp r5, #0x0
	beq _020C3370
	str r9, [sp, #0x0]
	ldr r1, [r4, #0x0]
	ldr r0, [sp, #0x4]
	mov r3, r1, lsl #0x8
	mov r1, r7
	mov r2, r6
	mov r3, r3, lsr #0x8
	bl FUN_020C2B1C
	cmp r0, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x9
	ldmeqia sp!, {r4-r11,pc}
_020C3370:
	cmp r7, #0x0
	beq _020C3390
	ldr r2, [sp, #0x4]
	cmp r2, #0x0
	beq _020C3390
	mov r0, r7
	mov r1, r6
	bl SND_AssignWaveArc
_020C3390:
	add r6, r6, #0x1
	cmp r6, #0x4
	blt _020C32D8
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	strne r7, [r0, #0x0]
	mov r0, #0x0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020C33B4: .word 0x0000FFFF

	arm_func_start FUN_020C33B8
FUN_020C33B8:
	stmdb sp!, {r4-r6,lr}
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl FUN_020C2334
	cmp r0, #0x0
	moveq r0, #0x3
	ldmeqia sp!, {r4-r6,pc}
	ands r1, r6, #0x8
	beq _020C3400
	ldr r0, [r0, #0x0]
	mov r1, r5
	mov r2, r4
	bl FUN_020C3044
	cmp r0, #0x0
	bne _020C3408
	mov r0, #0x7
	ldmia sp!, {r4-r6,pc}
_020C3400:
	ldr r0, [r0, #0x0]
	bl FUN_020C20DC
_020C3408:
	ldr r1, [sp, #0x10]
	cmp r1, #0x0
	strne r0, [r1, #0x0]
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020C341C
FUN_020C341C:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r1
	mov r6, r2
	mov r5, r3
	bl FUN_020C2398
	movs r4, r0
	addeq sp, sp, #0x4
	moveq r0, #0x2
	ldmeqia sp!, {r4-r7,pc}
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldrh r0, [r4, #0x4]
	mov r1, r7
	mov r2, r6
	mov r3, r5
	bl FUN_020C3270
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,pc}
	ands r0, r7, #0x1
	beq _020C3498
	ldr r0, [r4, #0x0]
	mov r1, r6
	mov r2, r5
	bl FUN_020C30BC
	cmp r0, #0x0
	bne _020C34A0
	add sp, sp, #0x4
	mov r0, #0x6
	ldmia sp!, {r4-r7,pc}
_020C3498:
	ldr r0, [r4, #0x0]
	bl FUN_020C20DC
_020C34A0:
	ldr r1, [sp, #0x18]
	cmp r1, #0x0
	strne r0, [r1, #0x0]
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020C34B8
FUN_020C34B8:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r9, r1
	bl FUN_020C21A4
	movs r8, r0
	addeq sp, sp, #0xc
	moveq r0, #0x1
	ldmeqia sp!, {r4-r11,pc}
	ldr r0, [r8, #0x0]
	mov r7, #0x0
	cmp r0, #0x0
	bls _020C35D4
	add r6, r8, #0x4
	str r7, [sp, #0x4]
	mov r11, r7
	mov r10, r7
	mov r5, r7
	mov r4, #0x1
_020C3500:
	ldrb r0, [r6, #0x0]
	cmp r0, #0x3
	addls pc, pc, r0, lsl #0x2
	b _020C35C0
	; Jump table
	b _020C3520 ; case 0
	b _020C3570 ; case 1
	b _020C3598 ; case 2
	b _020C3548 ; case 3
_020C3520:
	str r5, [sp, #0x0]
	ldrb r1, [r6, #0x1]
	ldr r0, [r6, #0x4]
	mov r2, r9
	mov r3, r4
	bl FUN_020C341C
	cmp r0, #0x0
	beq _020C35C0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
_020C3548:
	str r10, [sp, #0x0]
	ldrb r1, [r6, #0x1]
	ldr r0, [r6, #0x4]
	mov r2, r9
	mov r3, r4
	bl FUN_020C33B8
	cmp r0, #0x0
	beq _020C35C0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
_020C3570:
	str r11, [sp, #0x0]
	ldrb r1, [r6, #0x1]
	ldr r0, [r6, #0x4]
	mov r2, r9
	mov r3, r4
	bl FUN_020C3270
	cmp r0, #0x0
	beq _020C35C0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
_020C3598:
	ldr r0, [sp, #0x4]
	mov r2, r9
	str r0, [sp, #0x0]
	ldrb r1, [r6, #0x1]
	ldr r0, [r6, #0x4]
	mov r3, r4
	bl FUN_020C31D4
	cmp r0, #0x0
	addne sp, sp, #0xc
	ldmneia sp!, {r4-r11,pc}
_020C35C0:
	ldr r0, [r8, #0x0]
	add r7, r7, #0x1
	cmp r7, r0
	add r6, r6, #0x8
	blo _020C3500
_020C35D4:
	mov r0, #0x0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020C35E0
FUN_020C35E0: ; 0x020C35E0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r12, #0x0
	mov r3, #0x1
	str r12, [sp, #0x0]
	bl FUN_020C341C
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C360C
FUN_020C360C: ; 0x020C360C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r12, #0x0
	mov r1, #0xff
	mov r3, #0x1
	str r12, [sp, #0x0]
	bl FUN_020C31D4
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C3640
FUN_020C3640: ; 0x020C3640
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r12, #0x0
	mov r1, #0xff
	mov r3, #0x1
	str r12, [sp, #0x0]
	bl FUN_020C3270
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C3674
FUN_020C3674: ; 0x020C3674
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r12, #0x0
	mov r1, #0xff
	mov r3, #0x1
	str r12, [sp, #0x0]
	bl FUN_020C341C
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C36A8
FUN_020C36A8: ; 0x020C36A8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020C34B8
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C36C8
FUN_020C36C8: ; 0x020C36C8
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r7, r2
	mov r2, r3
	ldr r6, [sp, #0x20]
	mov r4, r0
	mov r8, r1
	bl FUN_020C0AF4
	movs r5, r0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	mov r0, r8
	mov r1, r5
	bl FUN_020C09B0
	add r12, sp, #0x4
	mov r2, r0
	mov r0, r7
	mov r1, #0x6
	mov r3, #0x0
	str r12, [sp, #0x0]
	bl FUN_020C3270
	cmp r0, #0x0
	beq _020C373C
	mov r0, r5
	bl thunk_FUN_020c077c
	add sp, sp, #0x8
	mov r0, #0x0
	ldmia sp!, {r4-r8,pc}
_020C373C:
	ldr r12, [sp, #0x24]
	ldr r2, [r6, #0x0]
	ldr r1, [r12, #0x18]
	ldr r3, [sp, #0x4]
	mov r0, r5
	add r1, r12, r1
	bl FUN_020C0A90
	ldrb r1, [r6, #0x6]
	mov r0, r4
	bl FUN_020C0F30
	ldrb r1, [r6, #0x7]
	mov r0, r4
	bl FUN_020C0ECC
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x2c]
	mov r0, r4
	bl FUN_020C0E38
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020C378C
FUN_020C378C: ; 0x020C378C
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	mov r8, r2
	mov r2, r3
	ldr r5, [sp, #0x28]
	mov r6, r0
	mov r7, r1
	bl FUN_020C0AF4
	movs r4, r0
	addeq sp, sp, #0x10
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	mov r0, r7
	mov r1, r4
	bl FUN_020C09B0
	mov r7, r0
	add r12, sp, #0x8
	mov r0, r8
	mov r2, r7
	mov r1, #0x6
	mov r3, #0x0
	str r12, [sp, #0x0]
	bl FUN_020C3270
	cmp r0, #0x0
	beq _020C3804
	mov r0, r4
	bl thunk_FUN_020c077c
	add sp, sp, #0x10
	mov r0, #0x0
	ldmia sp!, {r4-r8,pc}
_020C3804:
	ldr r0, [sp, #0x2c]
	add r12, sp, #0x4
	mov r2, r7
	mov r1, #0x1
	mov r3, #0x0
	str r12, [sp, #0x0]
	bl FUN_020C341C
	cmp r0, #0x0
	beq _020C383C
	mov r0, r4
	bl thunk_FUN_020c077c
	add sp, sp, #0x10
	mov r0, #0x0
	ldmia sp!, {r4-r8,pc}
_020C383C:
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x8]
	ldr r1, [r2, #0x18]
	mov r0, r4
	add r1, r2, r1
	mov r2, #0x0
	bl FUN_020C0A90
	ldrb r1, [r5, #0x6]
	mov r0, r6
	bl FUN_020C0F30
	ldrb r1, [r5, #0x7]
	mov r0, r6
	bl FUN_020C0ECC
	ldr r1, [sp, #0x2c]
	mov r0, r6
	bl FUN_020C0E60
	mov r0, #0x1
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020C3888
FUN_020C3888: ; 0x020C3888
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov r6, r1
	mov r7, r0
	mov r0, r6
	mov r5, r2
	bl FUN_020C2334
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	ldr r0, [r0, #0x0]
	bl FUN_020C20DC
	movs r4, r0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	mov r1, r5
	bl FUN_020C3D9C
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	str r6, [sp, #0x8]
	str r5, [sp, #0xc]
	ldrb r1, [r0, #0x9]
	ldrh r2, [r0, #0x4]
	ldrb r3, [r0, #0x8]
	mov r0, r7
	bl FUN_020C36C8
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020C3910
FUN_020C3910: ; 0x020C3910
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r7, r0
	ldr r0, [sp, #0x20]
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl FUN_020C2398
	cmp r0, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	cmp r4, #0x0
	ldrltb r4, [r0, #0x8]
	cmp r5, #0x0
	ldrlth r5, [r0, #0x4]
	cmp r6, #0x0
	ldrltb r6, [r0, #0x9]
	ldr r12, [sp, #0x20]
	mov r2, r5
	str r0, [sp, #0x0]
	mov r0, r7
	mov r1, r6
	mov r3, r4
	str r12, [sp, #0x4]
	bl FUN_020C378C
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020C3980
FUN_020C3980: ; 0x020C3980
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r4, r1
	mov r5, r0
	mov r0, r4
	bl FUN_020C2398
	cmp r0, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	ldrb r1, [r0, #0x9]
	ldrh r2, [r0, #0x4]
	ldrb r3, [r0, #0x8]
	mov r0, r5
	bl FUN_020C378C
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C39CC
FUN_020C39CC: ; 0x020C39CC
	stmdb sp!, {r4-r8,lr}
	mov r6, r0
	bl FUN_020C241C
	mov r5, #0x0
	mov r7, r5
_020C39E0:
	mov r0, r5
	bl FUN_020C2208
	movs r4, r0
	beq _020C3A58
	ldrb r1, [r4, #0x0]
	mov r0, r5
	bl FUN_020C1160
	ldrh r1, [r4, #0x2]
	mov r0, r5
	bl FUN_020C1148
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _020C3A58
	cmp r6, #0x0
	beq _020C3A58
	ldrb r0, [r4, #0x0]
	mov r8, r7
	cmp r0, #0x0
	ble _020C3A58
_020C3A2C:
	ldr r2, [r4, #0x4]
	mov r0, r5
	mov r1, r6
	bl FUN_020C10B4
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	ldrb r0, [r4, #0x0]
	add r8, r8, #0x1
	cmp r8, r0
	blt _020C3A2C
_020C3A58:
	add r5, r5, #0x1
	cmp r5, #0x20
	blt _020C39E0
	mov r0, #0x1
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020C3A6C
FUN_020C3A6C: ; 0x020C3A6C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	mov r4, r0
	ldr r0, _020C3A9C ; =UNK_021D2904
	mov r1, r5
	bl FUN_020ADBE8
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C3A9C: .word UNK_021D2904

	arm_func_start FUN_020C3AA0
FUN_020C3AA0: ; 0x020C3AA0
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	bl OS_DisableInterrupts
	mov r6, r0
	mov r0, r8
	mov r1, #0x0
	bl FUN_020ADA98
	movs r5, r0
	beq _020C3B04
_020C3AC8:
	mov r0, r8
	mov r1, r5
	bl FUN_020ADA98
	ldr r1, [r5, #0x8]
	mov r4, r0
	cmp r1, r7
	bne _020C3AF8
	mov r0, r8
	mov r1, r5
	bl FUN_020ADAB0
	mov r0, r5
	bl FUN_020C3A6C
_020C3AF8:
	mov r5, r4
	cmp r4, #0x0
	bne _020C3AC8
_020C3B04:
	mov r0, r6
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020C3B10
FUN_020C3B10: ; 0x020C3B10
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, [r0, #0x120]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	sub r1, r1, #0x1
	str r1, [r0, #0x120]
	ldr r1, [r0, #0x120]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {pc}
	bl FUN_020C1674
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C3B4C
FUN_020C3B4C: ; 0x020C3B4C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r1, [r4, #0x110]
	mov r1, r1, lsl #0x1f
	movs r1, r1, asr #0x1f
	ldmeqia sp!, {r4,pc}
	bl FUN_020C3B10
	ldr r1, [r4, #0x164]
	mov r0, r4
	blx r1
	ldr r0, _020C3BA8 ; =UNK_021D2DF0
	mov r1, r4
	bl FUN_020C3AA0
	ldr r0, _020C3BAC ; =UNK_021D2900
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020C3B9C
	mov r1, r4
	add r0, r0, #0x4e0
	bl FUN_020C3AA0
_020C3B9C:
	mov r0, r4
	bl FUN_020C3C4C
	ldmia sp!, {r4,pc}
	.balign 4
_020C3BA8: .word UNK_021D2DF0
_020C3BAC: .word UNK_021D2900

	arm_func_start FUN_020C3BB0
FUN_020C3BB0: ; 0x020C3BB0
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, _020C3C40 ; =UNK_021D2DD8
	bl OS_LockMutex
	ldr r0, _020C3C44 ; =UNK_021D2900
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _020C3BDC
	ldr r0, _020C3C48 ; =0x000004C8
	add r0, r1, r0
	bl OS_LockMutex
_020C3BDC:
	ldr r0, [r4, #0x110]
	mov r0, r0, lsl #0x1e
	movs r0, r0, asr #0x1f
	beq _020C3BF4
	mov r0, r4
	bl FUN_020C1430
_020C3BF4:
	ldr r0, [r4, #0x110]
	mov r0, r0, lsl #0x1f
	movs r0, r0, asr #0x1f
	beq _020C3C10
	ldr r1, [r4, #0x16c]
	mov r0, r4
	blx r1
_020C3C10:
	mov r0, r4
	bl FUN_020C3B4C
	ldr r0, _020C3C40 ; =UNK_021D2DD8
	bl OS_UnlockMutex
	ldr r0, _020C3C44 ; =UNK_021D2900
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r0, _020C3C48 ; =0x000004C8
	add r0, r1, r0
	bl OS_UnlockMutex
	ldmia sp!, {r4,pc}
	.balign 4
_020C3C40: .word UNK_021D2DD8
_020C3C44: .word UNK_021D2900
_020C3C48: .word 0x000004C8

	arm_func_start FUN_020C3C4C
FUN_020C3C4C: ; 0x020C3C4C
	ldr r2, [r0, #0x14c]
	cmp r2, #0x0
	movne r1, #0x0
	strne r1, [r2, #0x0]
	strne r1, [r0, #0x14c]
	ldr r1, [r0, #0x110]
	bic r1, r1, #0x1
	str r1, [r0, #0x110]
	ldr r1, [r0, #0x110]
	bic r1, r1, #0x4
	str r1, [r0, #0x110]
	ldr r1, [r0, #0x110]
	bic r1, r1, #0x2
	str r1, [r0, #0x110]
	bx lr

	arm_func_start FUN_020C3C88
FUN_020C3C88:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r5, _020C3D94 ; =UNK_021D2DFC
	mov r7, #0x0
	ldr r4, _020C3D98 ; =SNDi_DecibelTable
_020C3C9C:
	ldr r1, [r5, #0x110]
	mov r0, r1, lsl #0x1f
	movs r0, r0, asr #0x1f
	beq _020C3D7C
	ldr r0, [r5, #0x114]
	cmp r0, #0x0
	bne _020C3CC4
	mov r0, r5
	bl FUN_020C3BB0
	b _020C3D7C
_020C3CC4:
	mov r0, r1, lsl #0x1d
	movs r0, r0, asr #0x1f
	beq _020C3CFC
	ldr r0, [r5, #0x118]
	cmp r0, #0x0
	beq _020C3CFC
	mov r0, r5
	bl FUN_020C1458
	ldr r0, [r5, #0x110]
	orr r0, r0, #0x2
	str r0, [r5, #0x110]
	ldr r0, [r5, #0x110]
	bic r0, r0, #0x4
	str r0, [r5, #0x110]
_020C3CFC:
	ldr r0, [r5, #0x110]
	mov r0, r0, lsl #0x1e
	movs r0, r0, asr #0x1f
	beq _020C3D7C
	add r0, r5, #0xe8
	bl FUN_020C3DF4
	ldr r1, [r5, #0x154]
	add r0, r5, #0xe8
	mov r1, r1, lsl #0x1
	ldrsh r6, [r4, r1]
	bl FUN_020C3E0C
	mov r0, r0, asr #0x8
	mov r0, r0, lsl #0x1
	ldrsh r1, [r4, r0]
	ldr r0, [r5, #0x158]
	add r6, r1, r6
	cmp r6, r0
	beq _020C3D54
	mov r0, r5
	mov r1, r6
	bl FUN_020C13C4
	str r6, [r5, #0x158]
_020C3D54:
	ldr r0, [r5, #0x110]
	mov r0, r0, lsl #0x1c
	movs r0, r0, asr #0x1f
	beq _020C3D7C
	add r0, r5, #0xe8
	bl FUN_020C3DDC
	cmp r0, #0x0
	beq _020C3D7C
	mov r0, r5
	bl FUN_020C3BB0
_020C3D7C:
	add r7, r7, #0x1
	cmp r7, #0x4
	add r5, r5, #0x170
	blt _020C3C9C
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C3D94: .word UNK_021D2DFC
_020C3D98: .word SNDi_DecibelTable

	arm_func_start FUN_020C3D9C
FUN_020C3D9C:
	cmp r1, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r2, [r0, #0x1c]
	cmp r1, r2
	movcs r0, #0x0
	bxcs lr
	mov r2, #0xc
	mul r2, r1, r2
	add r3, r0, #0x20
	ldr r1, [r3, r2]
	mvn r0, #0x0
	cmp r1, r0
	add r0, r3, r2
	moveq r0, #0x0
	bx lr

	arm_func_start FUN_020C3DDC
FUN_020C3DDC:
	ldr r1, [r0, #0x8]
	ldr r0, [r0, #0xc]
	cmp r1, r0
	movge r0, #0x1
	movlt r0, #0x0
	bx lr

	arm_func_start FUN_020C3DF4
FUN_020C3DF4: ; 0x020C3DF4
	ldr r2, [r0, #0x8]
	ldr r1, [r0, #0xc]
	cmp r2, r1
	addlt r1, r2, #0x1
	strlt r1, [r0, #0x8]
	bx lr

	arm_func_start FUN_020C3E0C
FUN_020C3E0C:
	stmdb sp!, {r4,lr}
	ldr r1, [r0, #0xc]
	ldr r2, [r0, #0x8]
	cmp r2, r1
	ldrge r0, [r0, #0x4]
	ldmgeia sp!, {r4,pc}
	ldr r4, [r0, #0x0]
	ldr r0, [r0, #0x4]
	sub r0, r0, r4
	mul r0, r2, r0
	bl _s32_div_f
	add r0, r4, r0
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C3E40
FUN_020C3E40:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl FUN_020C3E0C
	str r0, [r6, #0x0]
	str r5, [r6, #0x4]
	str r4, [r6, #0xc]
	mov r0, #0x0
	str r0, [r6, #0x8]
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020C3E6C
FUN_020C3E6C: ; 0x020C3E6C
	mov r2, #0x0
	str r2, [r0, #0x4]
	ldr r1, [r0, #0x4]
	str r1, [r0, #0x0]
	str r2, [r0, #0xc]
	ldr r1, [r0, #0xc]
	str r1, [r0, #0x8]
	bx lr
