	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	; sIsThreadCreated
	.global UNK_021D27A4
UNK_021D27A4: ; 0x021D27A4
	.space 0x4

	; sCurEffectInfo
	.global UNK_021D27A8
UNK_021D27A8: ; 0x021D27A8
	.space 0x4

	; sMesgQ
	.global UNK_021D27AC
UNK_021D27AC: ; 0x021D27AC
	.space 0x20

	; sCapParam
	.global UNK_021D27CC
UNK_021D27CC: ; 0x021D27CC
	.space 0x54

	; sEffectInfoBuffer
	.global UNK_021D2820
UNK_021D2820: ; 0x021D2820
	.space 0xa0

	.section .text

	; AlarmCallback
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

	; NNSi_SndCaptureEndSleep
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

	; NNSi_SndCaptureBeginSleep
	arm_func_start FUN_020C18F8
FUN_020C18F8: ; 0x020C18F8
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

	; NNSi_SndCaptureStop
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

	; NNSi_SndCaptureStart
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

	; NNSi_SndCaptureMain
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

	; NNSi_SndCaptureInit
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

	; NNS_SndCaptureIsActive
	arm_func_start FUN_020C1E58
FUN_020C1E58: ; 0x020C1E58
	ldr r0, _020C1E64 ; =UNK_021D27CC
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020C1E64: .word UNK_021D27CC

	; NNS_SndCaptureStopEffect
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

	; NNS_SndCaptureStartEffect
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

	; NNS_SndCaptureStopReverb
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

	; NNS_SndCaptureSetReverbVolume
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

	; NNS_SndCaptureStartReverb
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

