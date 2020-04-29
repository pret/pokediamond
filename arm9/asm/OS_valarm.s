    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_InitVAlarm
OS_InitVAlarm: ; 0x020CD28C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020CD2EC ; =OSi_UseVAlarm
	ldrh r0, [r2, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r1, _020CD2F0 ; =OSi_VAlarmQueue
	mov r3, #0x0
	mov r12, #0x1
	mov r0, #0x4
	strh r12, [r2, #0x0]
	str r3, [r1, #0x0]
	str r3, [r1, #0x4]
	bl OS_DisableIrqMask
	ldr r1, _020CD2F4 ; =OSi_VFrameCount
	mov r2, #0x0
	ldr r0, _020CD2F8 ; =OSi_PreviousVCount
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CD2EC: .word OSi_UseVAlarm
_020CD2F0: .word OSi_VAlarmQueue
_020CD2F4: .word OSi_VFrameCount
_020CD2F8: .word OSi_PreviousVCount
