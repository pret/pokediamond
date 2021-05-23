	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	; sCaptureLock
	.global UNK_021D1CB0
UNK_021D1CB0: ; 0x021D1CB0
	.space 0x4

	; sAlarmLock
	.global UNK_021D1CB4
UNK_021D1CB4: ; 0x021D1CB4
	.space 0x4

	; sChannelLock
	.global UNK_021D1CB8
UNK_021D1CB8: ; 0x021D1CB8
	.space 0x4

	.section .text

	; NNSi_SndInitResourceMgr
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

	; NNS_SndFreeAlarm
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

	; NNS_SndAllocAlarm
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

	; NNS_SndUnlockCapture
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

	; NNS_SndLockCapture
	arm_func_start FUN_020C031C
FUN_020C031C: ; 0x020C031C
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

	; NNS_SndUnlockChannel
	arm_func_start FUN_020C0340
FUN_020C0340: ; 0x020C0340
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

	; NNS_SndLockChannel
	arm_func_start FUN_020C0370
FUN_020C0370: ; 0x020C0370
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

