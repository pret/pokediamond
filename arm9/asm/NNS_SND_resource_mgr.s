	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global sCaptureLock
sCaptureLock: ; 0x021D1CB0
	.space 0x4

	.global sAlarmLock
sAlarmLock: ; 0x021D1CB4
	.space 0x4

	.global sChannelLock
sChannelLock: ; 0x021D1CB8
	.space 0x4

	.section .text

	arm_func_start NNSi_SndInitResourceMgr
NNSi_SndInitResourceMgr: ; 0x020C0270
	ldr r2, _020C0290 ; =sChannelLock
	mov r3, #0x0
	ldr r1, _020C0294 ; =sCaptureLock
	ldr r0, _020C0298 ; =sAlarmLock
	str r3, [r2, #0x0]
	str r3, [r1, #0x0]
	str r3, [r0, #0x0]
	bx lr
	.balign 4
_020C0290: .word sChannelLock
_020C0294: .word sCaptureLock
_020C0298: .word sAlarmLock

	arm_func_start NNS_SndFreeAlarm
NNS_SndFreeAlarm: ; 0x020C029C
	ldr r1, _020C02B8 ; =sAlarmLock
	mov r2, #0x1
	mvn r0, r2, lsl r0
	ldr r2, [r1, #0x0]
	and r0, r2, r0
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020C02B8: .word sAlarmLock

	arm_func_start NNS_SndAllocAlarm
NNS_SndAllocAlarm: ; 0x020C02BC
	ldr r0, _020C02FC ; =sAlarmLock
	mov r3, #0x1
	ldr r2, [r0, #0x0]
	mov r0, #0x0
_020C02CC:
	ands r1, r2, r3
	ldreq r1, _020C02FC ; =sAlarmLock
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
_020C02FC: .word sAlarmLock

	arm_func_start NNS_SndUnlockCapture
NNS_SndUnlockCapture: ; 0x020C0300
	ldr r1, _020C0318 ; =sCaptureLock
	mvn r0, r0
	ldr r2, [r1, #0x0]
	and r0, r2, r0
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020C0318: .word sCaptureLock

	arm_func_start NNS_SndLockCapture
NNS_SndLockCapture: ; 0x020C031C
	ldr r1, _020C033C ; =sCaptureLock
	ldr r2, [r1, #0x0]
	ands r3, r0, r2
	movne r0, #0x0
	orreq r0, r2, r0
	streq r0, [r1, #0x0]
	moveq r0, #0x1
	bx lr
	.balign 4
_020C033C: .word sCaptureLock

	arm_func_start NNS_SndUnlockChannel
NNS_SndUnlockChannel: ; 0x020C0340
	stmdb sp!, {r4,lr}
	movs r4, r0
	ldmeqia sp!, {r4,pc}
	mov r1, #0x0
	bl SND_UnlockChannel
	ldr r0, _020C036C ; =sChannelLock
	mvn r1, r4
	ldr r2, [r0, #0x0]
	and r1, r2, r1
	str r1, [r0, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_020C036C: .word sChannelLock

	arm_func_start NNS_SndLockChannel
NNS_SndLockChannel: ; 0x020C0370
	stmdb sp!, {r4,lr}
	movs r4, r0
	moveq r0, #0x1
	ldmeqia sp!, {r4,pc}
	ldr r1, _020C03B4 ; =sChannelLock
	ldr r1, [r1, #0x0]
	ands r1, r4, r1
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
	mov r1, #0x0
	bl SND_LockChannel
	ldr r1, _020C03B4 ; =sChannelLock
	mov r0, #0x1
	ldr r2, [r1, #0x0]
	orr r2, r2, r4
	str r2, [r1, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_020C03B4: .word sChannelLock
