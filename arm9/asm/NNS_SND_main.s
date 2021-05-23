	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global sCurDriverInfo
sCurDriverInfo: ; 0x021D1C8C
	.space 0x4

	.global sDriverInfoFirstFlag
sDriverInfoFirstFlag: ; 0x021D1C90
	.space 0x4

	.global initialized$8127
initialized$8127: ; 0x021D1C94
	.space 0x4

	.global sPreSleepCallback
sPreSleepCallback: ; 0x021D1C98
	.space 0xc

	.global sPostSleepCallback
sPostSleepCallback: ; 0x021D1CA4
	.space 0xc

	.section .text

	local_arm_func_start EndSleep
EndSleep: ; 0x020C0130
	ldr ip, _020C0138 ; =NNSi_SndCaptureEndSleep
	bx r12
	.balign 4
_020C0138: .word NNSi_SndCaptureEndSleep

	local_arm_func_start BeginSleep
BeginSleep: ; 0x020C013C
	stmdb sp!, {r4,lr}
	bl NNSi_SndCaptureBeginSleep
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

	arm_func_start NNS_SndSetMonoFlag
NNS_SndSetMonoFlag: ; 0x020C0174
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

	arm_func_start NNS_SndMain
NNS_SndMain: ; 0x020C01A0
	stmdb sp!, {r4,lr}
	mov r4, #0x0
_020C01A8:
	mov r0, r4
	bl SND_RecvCommandReply
	cmp r0, #0x0
	bne _020C01A8
	bl NNSi_SndPlayerMain
	bl NNSi_SndCaptureMain
	bl NNSi_SndArcStrmMain
	mov r0, #0x0
	bl SND_FlushCommand
	ldmia sp!, {r4,pc}

	arm_func_start NNS_SndInit
NNS_SndInit: ; 0x020C01D0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C0254 ; =initialized$8127
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {pc}
	mov r1, #0x1
	str r1, [r0, #0x0]
	bl SND_Init
	ldr ip, _020C0258 ; =BeginSleep
	ldr r0, _020C025C ; =sPreSleepCallback
	mov r3, #0x0
	ldr r1, _020C0260 ; =sPostSleepCallback
	ldr r2, _020C0264 ; =EndSleep
	str r12, [r0, #0x0]
	str r3, [r0, #0x4]
	str r2, [r1, #0x0]
	str r3, [r1, #0x4]
	bl PM_PrependPreSleepCallback
	ldr r0, _020C0260 ; =sPostSleepCallback
	bl PM_AppendPostSleepCallback
	bl NNSi_SndInitResourceMgr
	bl NNSi_SndCaptureInit
	bl NNSi_SndPlayerInit
	ldr r1, _020C0268 ; =sCurDriverInfo
	mvn r3, #0x0
	ldr r0, _020C026C ; =sDriverInfoFirstFlag
	mov r2, #0x1
	strb r3, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020C0254: .word initialized$8127
_020C0258: .word BeginSleep
_020C025C: .word sPreSleepCallback
_020C0260: .word sPostSleepCallback
_020C0264: .word EndSleep
_020C0268: .word sCurDriverInfo
_020C026C: .word sDriverInfoFirstFlag
