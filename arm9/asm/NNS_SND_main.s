	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	; sCurDriverInfo
	.global UNK_021D1C8C
UNK_021D1C8C: ; 0x021D1C8C
	.space 0x4

	; sDriverInfoFirstFlag
	.global UNK_021D1C90
UNK_021D1C90: ; 0x021D1C90
	.space 0x4

	; initialized$8127
	.global UNK_021D1C94
UNK_021D1C94: ; 0x021D1C94
	.space 0x4

	; sPreSleepCallback
	.global UNK_021D1C98
UNK_021D1C98: ; 0x021D1C98
	.space 0xc

	; sPostSleepCallback
	.global UNK_021D1CA4
UNK_021D1CA4: ; 0x021D1CA4
	.space 0xc

	.section .text

	; EndSleep
	arm_func_start FUN_020C0130
FUN_020C0130: ; 0x020C0130
	ldr ip, _020C0138 ; =FUN_020C187C
	bx r12
	.balign 4
_020C0138: .word FUN_020C187C

	; _end
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

	; _end
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

	; _end
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

	; NNS_SndInit
	arm_func_start SDAT_Init
SDAT_Init: ; 0x020C01D0
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

