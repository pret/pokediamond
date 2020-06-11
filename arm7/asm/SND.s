#todo split further

	.include "asm/macros.inc"
	.include "global.inc"

    .section .data

	.global sMasterPan
sMasterPan:
	.word	0xFFFFFFFF

    .section .bss

	.global sSurroundDecay
sSurroundDecay: ;0x03807A0C
	.space 0x03807A10 - 0x03807A0C

	.global sOrgPan
sOrgPan: ;0x03807A10
	.space 0x03807A20 - 0x03807A10

	.global sOrgVolume
sOrgVolume: ;0x03807A20
	.space 0x03807A30 - 0x03807A20

    .section .text

	arm_func_start SND_SetOutputSelector
SND_SetOutputSelector: ; 0x037FBA0C
	ldr	ip, _037FBA40	; =0x04000501
	ldrb	ip, [ip]
	ands	ip, ip, #128	; 0x80
	movne	ip, #1
	moveq	ip, #0
	mov	ip, ip, lsl #7
	orr	r3, ip, r3, lsl #5
	orr	r2, r3, r2, lsl #4
	orr	r1, r2, r1, lsl #2
	orr	r1, r0, r1
	ldr	r0, _037FBA40	; =0x04000501
	strb	r1, [r0]
	bx	lr
_037FBA40:	.word	0x04000501

	arm_func_start SND_SetMasterVolume
SND_SetMasterVolume: ; 0x037FBA44
	ldr	r1, _037FBA50	; =0x04000500
	strb	r0, [r1]
	bx	lr
_037FBA50:	.word	0x04000500

	arm_func_start SND_EndSleep
SND_EndSleep: ; 0x037FBA54
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _037FBA94	; =0x04000304
	ldrh	r0, [r1]
	orr	r0, r0, #1
	strh	r0, [r1]
	mov	r0, #1
	bl	PMi_SetControl
	mov	r0, #256	; 0x100
	bl	FUN_037FBA9C
	ldr	r0, _037FBA98	; =0x0007AB80
	bl	OS_SpinWait
	bl	SND_Enable
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FBA94:	.word	0x04000304
_037FBA98:	.word	0x0007AB80

	arm_func_start FUN_037FBA9C
FUN_037FBA9C: ; 0x037FBA9C
	ldr	ip, _037FBAA4	; =SVC_SoundBiasSet
	bx	ip
_037FBAA4:	.word	SVC_SoundBiasSet

	arm_func_start SND_BeginSleep
SND_BeginSleep: ; 0x037FBAA8
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	bl	SND_Disable
	mov	r0, #128	; 0x80
	bl	FUN_037FBAEC
	mov	r0, #262144	; 0x40000
	bl	OS_SpinWait
	mov	r0, #1
	bl	PMi_ResetControl
	ldr	r1, _037FBAE8	; =0x04000304
	ldrh	r0, [r1]
	bic	r0, r0, #1
	strh	r0, [r1]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FBAE8:	.word	0x04000304

	arm_func_start FUN_037FBAEC
FUN_037FBAEC: ; 0x037FBAEC
	ldr	ip, _037FBAF4	; =SVC_SoundBiasReset
	bx	ip
_037FBAF4:	.word	SVC_SoundBiasReset

	arm_func_start SND_Shutdown
SND_Shutdown: ; 0x037FBAF8
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	bl	SND_Disable
	mov	r5, #0
	mov	r4, #1
_037FBB0C:
	mov	r0, r5
	mov	r1, r4
	bl	SND_StopChannel
	add	r5, r5, #1
	cmp	r5, #16
	blt	_037FBB0C
	mov	r1, #0
	ldr	r0, _037FBB44	; =0x04000508
	strb	r1, [r0]
	ldr	r0, _037FBB48	; =0x04000509
	strb	r1, [r0]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FBB44:	.word	0x04000508
_037FBB48:	.word	0x04000509

	arm_func_start SND_Disable
SND_Disable: ; 0x037FBB4C
	ldr	r1, _037FBB60	; =0x04000501
	ldrb	r0, [r1]
	bic	r0, r0, #128	; 0x80
	strb	r0, [r1]
	bx	lr
_037FBB60:	.word	0x04000501

	arm_func_start SND_Enable
SND_Enable: ; 0x037FBB64
	ldr	r1, _037FBB78	; =0x04000501
	ldrb	r0, [r1]
	orr	r0, r0, #128	; 0x80
	strb	r0, [r1]
	bx	lr
_037FBB78:	.word	0x04000501

	arm_func_start CalcSurroundDecay
CalcSurroundDecay: ; 0x037FBB7C
	cmp	r1, #24
	bge	_037FBBAC
	ldr	r2, _037FBBE0	; =sSurroundDecay
	ldr	r3, [r2]
	ldr	r2, _037FBBE4	; =0x00007FFF
	sub	r2, r2, r3
	add	r1, r1, #40	; 0x28
	mul	r1, r3, r1
	add	r1, r1, r2, lsl #6
	mul	r1, r0, r1
	mov	r0, r1, asr #21
	bx	lr
_037FBBAC:
	cmp	r1, #104	; 0x68
	bxle	lr
	ldr	r2, _037FBBE0	; =sSurroundDecay
	ldr	ip, [r2]
	ldr	r2, _037FBBE4	; =0x00007FFF
	add	r3, ip, r2
	rsb	r2, ip, #0
	sub	r1, r1, #40	; 0x28
	mul	r1, r2, r1
	add	r1, r1, r3, lsl #6
	mul	r1, r0, r1
	mov	r0, r1, asr #21
	bx	lr
_037FBBE0:	.word	sSurroundDecay
_037FBBE4:	.word	0x00007FFF

	arm_func_start SNDi_SetSurroundDecay
SNDi_SetSurroundDecay: ; 0x037FBBE8
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	ldr	r1, _037FBC40	; =sSurroundDecay
	str	r0, [r1]
	mov	r4, #0
	ldr	r6, _037FBC44	; =sOrgVolume
	mov	r7, #1
	ldr	r5, _037FBC48	; =0x0000FFF5
_037FBC04:
	mov	r0, r7, lsl r4
	ands	r0, r0, r5
	beq	_037FBC2C
	mov	r8, r4, lsl #4
	add	r0, r8, #67108864	; 0x4000000
	ldrb	r1, [r0, #1026]	; 0x402
	ldrb	r0, [r6, r4]
	bl	CalcSurroundDecay
	add	r1, r8, #67108864	; 0x4000000
	strb	r0, [r1, #1024]	; 0x400
_037FBC2C:
	add	r4, r4, #1
	cmp	r4, #16
	blt	_037FBC04
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FBC40:	.word	sSurroundDecay
_037FBC44:	.word	sOrgVolume
_037FBC48:	.word	0x0000FFF5

	arm_func_start SND_GetChannelControl
SND_GetChannelControl: ; 0x037FBC4C
	mov	r0, r0, lsl #4
	add	r0, r0, #67108864	; 0x4000000
	ldr	r0, [r0, #1024]	; 0x400
	bx	lr

	arm_func_start SND_SetMasterPan
SND_SetMasterPan: ; 0x037FBC5C
	ldr	r1, _037FBCB8	; =sMasterPan
	str	r0, [r1]
	cmp	r0, #0
	blt	_037FBC90
	mov	r2, #0
	and	r1, r0, #255	; 0xff
_037FBC74:
	mov	r0, r2, lsl #4
	add	r0, r0, #67108864	; 0x4000000
	strb	r1, [r0, #1026]	; 0x402
	add	r2, r2, #1
	cmp	r2, #16
	blt	_037FBC74
	bx	lr
_037FBC90:
	mov	r3, #0
	ldr	r2, _037FBCBC	; =sOrgPan
_037FBC98:
	ldrb	r1, [r2, r3]
	mov	r0, r3, lsl #4
	add	r0, r0, #67108864	; 0x4000000
	strb	r1, [r0, #1026]	; 0x402
	add	r3, r3, #1
	cmp	r3, #16
	blt	_037FBC98
	bx	lr
_037FBCB8:	.word	sMasterPan
_037FBCBC:	.word	sOrgPan

	arm_func_start SND_IsChannelActive
SND_IsChannelActive: ; 0x037FBCC0
	mov	r0, r0, lsl #4
	add	r0, r0, #67108864	; 0x4000000
	ldrb	r0, [r0, #1027]	; 0x403
	ands	r0, r0, #128	; 0x80
	movne	r0, #1
	moveq	r0, #0
	bx	lr

	arm_func_start SND_SetChannelPan
SND_SetChannelPan: ; 0x037FBCDC
	stmdb	sp!, {r4, lr}
	ldr	r2, _037FBD44	; =sOrgPan
	strb	r1, [r2, r0]
	ldr	r2, _037FBD48	; =sMasterPan
	ldr	r2, [r2]
	cmp	r2, #0
	movge	r1, r2
	mov	r4, r0, lsl #4
	add	r2, r4, #67108864	; 0x4000000
	strb	r1, [r2, #1026]	; 0x402
	ldr	r2, _037FBD4C	; =sSurroundDecay
	ldr	r2, [r2]
	cmp	r2, #0
	ble	_037FBD3C
	mov	r2, #1
	mov	r3, r2, lsl r0
	ldr	r2, _037FBD50	; =0x0000FFF5
	ands	r2, r3, r2
	beq	_037FBD3C
	ldr	r2, _037FBD54	; =sOrgVolume
	ldrb	r0, [r2, r0]
	bl	CalcSurroundDecay
	add	r1, r4, #67108864	; 0x4000000
	strb	r0, [r1, #1024]	; 0x400
_037FBD3C:
	ldmia	sp!, {r4, lr}
	bx	lr
_037FBD44:	.word	sOrgPan
_037FBD48:	.word	sMasterPan
_037FBD4C:	.word	sSurroundDecay
_037FBD50:	.word	0x0000FFF5
_037FBD54:	.word	sOrgVolume

	arm_func_start SND_SetChannelTimer
SND_SetChannelTimer: ; 0x037FBD58
	rsb	r1, r1, #65536	; 0x10000
	mov	r0, r0, lsl #4
	add	r0, r0, #67108864	; 0x4000000
	add	r0, r0, #1024	; 0x400
	strh	r1, [r0, #8]
	bx	lr

	arm_func_start SND_SetChannelVolume
SND_SetChannelVolume: ; 0x037FBD70
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, r2
	ldr	r0, _037FBDE8	; =sOrgVolume
	strb	r1, [r0, r5]
	ldr	r0, _037FBDEC	; =sSurroundDecay
	ldr	r0, [r0]
	cmp	r0, #0
	ble	_037FBDC8
	mov	r0, #1
	mov	r2, r0, lsl r5
	ldr	r0, _037FBDF0	; =0x0000FFF5
	ands	r0, r2, r0
	beq	_037FBDC8
	mov	r0, r5, lsl #4
	add	r0, r0, #67108864	; 0x4000000
	ldrb	r2, [r0, #1026]	; 0x402
	mov	r0, r1
	mov	r1, r2
	bl	CalcSurroundDecay
	mov	r1, r0
_037FBDC8:
	orr	r1, r1, r4, lsl #8
	mov	r0, r5, lsl #4
	add	r0, r0, #67108864	; 0x4000000
	add	r0, r0, #1024	; 0x400
	strh	r1, [r0]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FBDE8:	.word	sOrgVolume
_037FBDEC:	.word	sSurroundDecay
_037FBDF0:	.word	0x0000FFF5

	arm_func_start SND_StopChannel
SND_StopChannel: ; 0x037FBDF4
	mov	r3, r0, lsl #4
	ldr	r2, _037FBE1C	; =0x04000400
	add	ip, r2, r0, lsl #4
	add	r0, r3, #67108864	; 0x4000000
	ldr	r0, [r0, #1024]	; 0x400
	bic	r2, r0, #-2147483648	; 0x80000000
	ands	r0, r1, #1
	orrne	r2, r2, #32768	; 0x8000
	str	r2, [ip]
	bx	lr
_037FBE1C:	.word	0x04000400

	arm_func_start SND_SetupChannelNoise
SND_SetupChannelNoise: ; 0x037FBE20
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r2
	mov	r6, r3
	ldr	r5, [sp, #24]
	mov	r4, r0, lsl #4
	ldr	r2, _037FBEBC	; =sOrgPan
	strb	r5, [r2, r0]
	ldr	r2, _037FBEC0	; =sMasterPan
	ldr	r2, [r2]
	cmp	r2, #0
	movge	r5, r2
	ldr	r2, _037FBEC4	; =sOrgVolume
	strb	r1, [r2, r0]
	ldr	r2, _037FBEC8	; =sSurroundDecay
	ldr	r2, [r2]
	cmp	r2, #0
	ble	_037FBE8C
	mov	r2, #1
	mov	r2, r2, lsl r0
	ldr	r0, _037FBECC	; =0x0000FFF5
	ands	r0, r2, r0
	beq	_037FBE8C
	mov	r0, r1
	mov	r1, r5
	bl	CalcSurroundDecay
	mov	r1, r0
_037FBE8C:
	mov	r0, r5, lsl #16
	orr	r0, r0, #1610612736	; 0x60000000
	orr	r0, r0, r7, lsl #8
	orr	r1, r1, r0
	add	r0, r4, #67108864	; 0x4000000
	str	r1, [r0, #1024]	; 0x400
	rsb	r1, r6, #65536	; 0x10000
	add	r0, r0, #1024	; 0x400
	strh	r1, [r0, #8]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FBEBC:	.word	sOrgPan
_037FBEC0:	.word	sMasterPan
_037FBEC4:	.word	sOrgVolume
_037FBEC8:	.word	sSurroundDecay
_037FBECC:	.word	0x0000FFF5

	arm_func_start SND_SetupChannelPsg
SND_SetupChannelPsg: ; 0x037FBED0
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r1
	mov	r6, r3
	ldr	r5, [sp, #28]
	mov	r4, r0, lsl #4
	ldr	r1, _037FBF74	; =sOrgPan
	strb	r5, [r1, r0]
	ldr	r1, _037FBF78	; =sMasterPan
	ldr	r1, [r1]
	cmp	r1, #0
	movge	r5, r1
	ldr	r1, _037FBF7C	; =sOrgVolume
	strb	r2, [r1, r0]
	ldr	r1, _037FBF80	; =sSurroundDecay
	ldr	r1, [r1]
	cmp	r1, #0
	ble	_037FBF3C
	mov	r1, #1
	mov	r1, r1, lsl r0
	ldr	r0, _037FBF84	; =0x0000FFF5
	ands	r0, r1, r0
	beq	_037FBF3C
	mov	r0, r2
	mov	r1, r5
	bl	CalcSurroundDecay
	mov	r2, r0
_037FBF3C:
	mov	r0, r7, lsl #24
	orr	r0, r0, #1610612736	; 0x60000000
	orr	r0, r0, r5, lsl #16
	orr	r0, r0, r6, lsl #8
	orr	r1, r2, r0
	add	r0, r4, #67108864	; 0x4000000
	str	r1, [r0, #1024]	; 0x400
	ldr	r1, [sp, #24]
	rsb	r1, r1, #65536	; 0x10000
	add	r0, r0, #1024	; 0x400
	strh	r1, [r0, #8]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FBF74:	.word	sOrgPan
_037FBF78:	.word	sMasterPan
_037FBF7C:	.word	sOrgVolume
_037FBF80:	.word	sSurroundDecay
_037FBF84:	.word	0x0000FFF5

	arm_func_start SND_SetupChannelPcm
SND_SetupChannelPcm: ; 0x037FBF88
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r8, r1
	mov	r7, r2
	mov	r6, r3
	ldr	r1, [sp, #32]
	ldr	r5, [sp, #44]	; 0x2c
	mov	r4, r0, lsl #4
	ldr	r2, _037FC044	; =sOrgPan
	strb	r5, [r2, r0]
	ldr	r2, _037FC048	; =sMasterPan
	ldr	r2, [r2]
	cmp	r2, #0
	movge	r5, r2
	ldr	r2, _037FC04C	; =sOrgVolume
	strb	r1, [r2, r0]
	ldr	r2, _037FC050	; =sSurroundDecay
	ldr	r2, [r2]
	cmp	r2, #0
	ble	_037FBFF8
	mov	r2, #1
	mov	r2, r2, lsl r0
	ldr	r0, _037FC054	; =0x0000FFF5
	ands	r0, r2, r0
	beq	_037FBFF8
	mov	r0, r1
	mov	r1, r5
	bl	CalcSurroundDecay
	mov	r1, r0
_037FBFF8:
	ldr	r2, [sp, #36]	; 0x24
	mov	r0, r7, lsl #29
	orr	r0, r0, r6, lsl #27
	orr	r0, r0, r5, lsl #16
	orr	r0, r0, r2, lsl #8
	orr	r0, r1, r0
	add	r1, r4, #67108864	; 0x4000000
	str	r0, [r1, #1024]	; 0x400
	ldr	r0, [sp, #40]	; 0x28
	rsb	r2, r0, #65536	; 0x10000
	add	r0, r1, #1024	; 0x400
	strh	r2, [r0, #8]
	ldr	r2, [sp, #24]
	strh	r2, [r0, #10]
	ldr	r0, [sp, #28]
	str	r0, [r1, #1036]	; 0x40c
	str	r8, [r1, #1028]	; 0x404
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FC044:	.word	sOrgPan
_037FC048:	.word	sMasterPan
_037FC04C:	.word	sOrgVolume
_037FC050:	.word	sSurroundDecay
_037FC054:	.word	0x0000FFF5
