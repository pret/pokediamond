    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start ScrCmd_BgmPlayCheck
ScrCmd_BgmPlayCheck: ; 0x020413C0
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02005410
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_BgmPlay
ScrCmd_BgmPlay: ; 0x020413E8
	push {r3, lr}
	bl ScriptReadHalfword
	bl FUN_0200521C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_BgmStop
ScrCmd_BgmStop: ; 0x020413F8
	push {r3, lr}
	bl ScriptReadHalfword
	bl FUN_02004124
	mov r1, #0x0
	bl FUN_02005350
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_BgmNowMapPlay
ScrCmd_BgmNowMapPlay: ; 0x0204140C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x1c]
	ldr r1, [r1, #0x0]
	bl FUN_0204ABA8
	bl FUN_0200521C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_BgmSpecialSet
ScrCmd_BgmSpecialSet: ; 0x02041424
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0204AB20
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_BgmFadeOut
ScrCmd_BgmFadeOut: ; 0x0204143C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020053CC
	ldr r1, _02041460 ; =FUN_02041464
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_02041460: .word FUN_02041464

	thumb_func_start FUN_02041464
FUN_02041464: ; 0x02041464
	push {r3, lr}
	bl FUN_02005404
	cmp r0, #0x0
	bne _02041472
	mov r0, #0x1
	pop {r3, pc}
_02041472:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_BgmFadeIn
ScrCmd_BgmFadeIn: ; 0x02041478
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	mov r0, #0x7f
	mov r2, #0x0
	bl FUN_0200538C
	ldr r1, _02041498 ; =FUN_02041464
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_02041498: .word FUN_02041464

	thumb_func_start ScrCmd_BgmPlayerPause
ScrCmd_BgmPlayerPause: ; 0x0204149C
	push {r3, lr}
	ldr r1, [r0, #0x8]
	add r3, r1, #0x1
	str r3, [r0, #0x8]
	ldrb r2, [r1, #0x0]
	add r1, r3, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r3, #0x0]
	add r0, r2, #0x0
	bl FUN_020047C8
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_PlayerFieldDemoBgmPlay
ScrCmd_PlayerFieldDemoBgmPlay: ; 0x020414B8
	push {r3, lr}
	bl ScriptReadHalfword
	add r1, r0, #0x0
	mov r0, #0x4
	bl FUN_02005308
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_CtrlBgmFlagSet
ScrCmd_CtrlBgmFlagSet: ; 0x020414CC
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r0, [r2, #0x0]
	bl FUN_020040F4
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_SePlay
ScrCmd_SePlay: ; 0x020414E0
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	bl FUN_020054C8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_SeStop
ScrCmd_SeStop: ; 0x020414FC
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	mov r1, #0x0
	bl FUN_020054F0
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_SeWait
ScrCmd_SeWait: ; 0x02041518
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [r4, #0x64]
	ldr r1, _0204153C ; =FUN_02041540
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0204153C: .word FUN_02041540

	thumb_func_start FUN_02041540
FUN_02041540: ; 0x02041540
	push {r3, lr}
	ldr r0, [r0, #0x64]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02005508
	cmp r0, #0x0
	bne _02041554
	mov r0, #0x1
	pop {r3, pc}
_02041554:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_VoicePlay
ScrCmd_VoicePlay: ; 0x02041558
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r0, r5, #0x0
	bl FUN_02005578
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_VoicePlayWait
ScrCmd_VoicePlayWait: ; 0x02041588
	push {r3, lr}
	ldr r1, _02041594 ; =FUN_02041598
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_02041594: .word FUN_02041598

	thumb_func_start FUN_02041598
FUN_02041598: ; 0x02041598
	push {r3, lr}
	bl FUN_02005670
	cmp r0, #0x0
	bne _020415A6
	mov r0, #0x1
	pop {r3, pc}
_020415A6:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_MePlay
ScrCmd_MePlay: ; 0x020415AC
	push {r3, lr}
	bl ScriptReadHalfword
	bl FUN_02005C28
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_MeWait
ScrCmd_MeWait: ; 0x020415BC
	push {r3, lr}
	ldr r1, _020415C8 ; =FUN_020415CC
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_020415C8: .word FUN_020415CC

	thumb_func_start FUN_020415CC
FUN_020415CC: ; 0x020415CC
	push {r3, lr}
	bl FUN_02005CBC
	cmp r0, #0x0
	bne _020415DA
	mov r0, #0x1
	pop {r3, pc}
_020415DA:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_PerapDataCheck
ScrCmd_PerapDataCheck: ; 0x020415E0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029EF8
	bl FUN_02005D20
	cmp r0, #0x1
	bne _02041610
	mov r0, #0x1
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
_02041610:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_PerapRecStart
ScrCmd_PerapRecStart: ; 0x02041618
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	bl FUN_02005E28
	cmp r0, #0x0
	bne _0204163C
	mov r0, #0x1
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4, pc}
_0204163C:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_PerapRecStop
ScrCmd_PerapRecStop: ; 0x02041644
	push {r3, lr}
	bl FUN_02005E64
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_PerapSave
ScrCmd_PerapSave: ; 0x02041650
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029EF8
	bl FUN_02005E6C
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_SndClimaxDataLoad
ScrCmd_SndClimaxDataLoad: ; 0x02041664
	push {r3, lr}
	mov r1, #0x0
	mov r0, #0x3f
	add r2, r1, #0x0
	bl FUN_0200433C
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_SndInitialVolSet
ScrCmd_SndInitialVolSet: ; 0x02041674
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0200488C
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
