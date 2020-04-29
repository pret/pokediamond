    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OSi_AlarmHandler
OSi_AlarmHandler: ; 0x020CCE00
	stmdb sp!, {r0,lr}
	bl OSi_ArrangeTimer
	ldmia sp!, {r0,lr}
	bx lr

	arm_func_start OSi_ArrangeTimer
OSi_ArrangeTimer: ; 0x020CCE10
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _020CCF1C ; =0x04000106
	mov r2, #0x0
	mov r0, #0x10
	strh r2, [r1, #0x0]
	bl OS_DisableIrqMask
	ldr r0, _020CCF20 ; =0x027E0000
	add r0, r0, #0x3000
	ldr r1, [r0, #0xff8]
	orr r1, r1, #0x10
	str r1, [r0, #0xff8]
	bl OS_GetTick
	ldr r2, _020CCF24 ; =OSi_AlarmQueue
	ldr r4, [r2, #0x0]
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r3, [r4, #0x10]
	ldr r12, [r4, #0xc]
	cmp r1, r3
	cmpeq r0, r12
	bhs _020CCE84
	mov r0, r4
	bl OSi_SetTimer
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020CCE84:
	ldr r1, [r4, #0x18]
	cmp r1, #0x0
	moveq r0, #0x0
	streq r0, [r2, #0x4]
	str r1, [r2, #0x0]
	movne r0, #0x0
	strne r0, [r1, #0x14]
	ldr r2, [r4, #0x1c]
	ldr r1, [r4, #0x20]
	mov r0, #0x0
	cmp r1, r0
	ldr r5, [r4, #0x0]
	cmpeq r2, r0
	streq r0, [r4, #0x0]
	cmp r5, #0x0
	beq _020CCECC
	ldr r0, [r4, #0x4]
	blx r5
_020CCECC:
	ldr r2, [r4, #0x1c]
	ldr r0, [r4, #0x20]
	mov r1, #0x0
	cmp r0, r1
	cmpeq r2, r1
	beq _020CCEF4
	mov r0, r4
	mov r2, r1
	str r5, [r4, #0x0]
	bl OSi_InsertAlarm
_020CCEF4:
	ldr r0, _020CCF24 ; =OSi_AlarmQueue
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	bl OSi_SetTimer
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CCF1C: .word 0x04000106
_020CCF20: .word 0x027E0000
_020CCF24: .word OSi_AlarmQueue

	arm_func_start OS_CancelAlarm
OS_CancelAlarm: ; 0x020CCF28
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, [r5, #0x0]
	mov r4, r0
	cmp r1, #0x0
	bne _020CCF58
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020CCF58:
	ldr r0, [r5, #0x18]
	cmp r0, #0x0
	ldreq r2, [r5, #0x14]
	ldreq r1, _020CCFBC ; =OSi_AlarmQueue
	streq r2, [r1, #0x4]
	ldrne r1, [r5, #0x14]
	strne r1, [r0, #0x14]
	ldr r1, [r5, #0x14]
	cmp r1, #0x0
	strne r0, [r1, #0x18]
	bne _020CCF98
	ldr r1, _020CCFBC ; =OSi_AlarmQueue
	cmp r0, #0x0
	str r0, [r1, #0x0]
	beq _020CCF98
	bl OSi_SetTimer
_020CCF98:
	mov r1, #0x0
	str r1, [r5, #0x0]
	str r1, [r5, #0x1c]
	mov r0, r4
	str r1, [r5, #0x20]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CCFBC: .word OSi_AlarmQueue

	arm_func_start OS_SetAlarm
OS_SetAlarm: ; 0x020CCFC0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	movs r6, r0
	mov r5, r1
	mov r4, r2
	mov r7, r3
	beq _020CCFE8
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	beq _020CCFEC
_020CCFE8:
	bl OS_Terminate
_020CCFEC:
	bl OS_DisableInterrupts
	mov r1, #0x0
	str r1, [r6, #0x1c]
	str r1, [r6, #0x20]
	str r7, [r6, #0x0]
	ldr r1, [sp, #0x18]
	mov r7, r0
	str r1, [r6, #0x4]
	bl OS_GetTick
	adds r3, r5, r0
	adc r2, r4, r1
	mov r0, r6
	mov r1, r3
	bl OSi_InsertAlarm
	mov r0, r7
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start OSi_InsertAlarm
OSi_InsertAlarm: ; 0x020CD038
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	ldr r4, [r8, #0x1c]
	ldr r3, [r8, #0x20]
	mov r0, #0x0
	cmp r3, r0
	mov r7, r1
	mov r6, r2
	cmpeq r4, r0
	beq _020CD0B4
	bl OS_GetTick
	ldr r6, [r8, #0x28]
	ldr r7, [r8, #0x24]
	cmp r6, r1
	cmpeq r7, r0
	bhs _020CD0B4
	ldr r5, [r8, #0x1c]
	ldr r4, [r8, #0x20]
	subs r0, r0, r7
	mov r2, r5
	mov r3, r4
	sbc r1, r1, r6
	bl _ll_udiv
	mov r2, #0x1
	adds r2, r0, r2
	adc r0, r1, #0x0
	umull r3, r1, r5, r2
	mla r1, r5, r0, r1
	mla r1, r4, r2, r1
	adds r7, r7, r3
	adc r6, r6, r1
_020CD0B4:
	str r7, [r8, #0xc]
	ldr r0, _020CD174 ; =OSi_AlarmQueue
	str r6, [r8, #0x10]
	ldr r4, [r0, #0x0]
	cmp r4, #0x0
	beq _020CD134
	mov r1, #0x0
_020CD0D0:
	ldr r2, [r4, #0xc]
	ldr r0, [r4, #0x10]
	subs r3, r7, r2
	sbc r2, r6, r0
	subs r0, r3, r1
	sbcs r0, r2, r1
	bge _020CD128
	ldr r0, [r4, #0x14]
	str r0, [r8, #0x14]
	str r8, [r4, #0x14]
	str r4, [r8, #0x18]
	ldr r0, [r8, #0x14]
	cmp r0, #0x0
	strne r8, [r0, #0x18]
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldr r1, _020CD174 ; =OSi_AlarmQueue
	mov r0, r8
	str r8, [r1, #0x0]
	bl OSi_SetTimer
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CD128:
	ldr r4, [r4, #0x18]
	cmp r4, #0x0
	bne _020CD0D0
_020CD134:
	ldr r1, _020CD174 ; =OSi_AlarmQueue
	mov r0, #0x0
	str r0, [r8, #0x18]
	ldr r0, [r1, #0x4]
	str r8, [r1, #0x4]
	str r0, [r8, #0x14]
	cmp r0, #0x0
	strne r8, [r0, #0x18]
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	mov r0, r8
	str r8, [r1, #0x4]
	str r8, [r1, #0x0]
	bl OSi_SetTimer
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020CD174: .word OSi_AlarmQueue

	arm_func_start OS_CreateAlarm
OS_CreateAlarm: ; 0x020CD178
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x8]
	bx lr

	arm_func_start OS_IsAlarmAvailable
OS_IsAlarmAvailable: ; 0x020CD188
	ldr r0, _020CD194 ; =OSi_UseAlarm
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4
_020CD194: .word OSi_UseAlarm

	arm_func_start OS_InitAlarm
OS_InitAlarm: ; 0x020CD198
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020CD1E8 ; =OSi_UseAlarm
	ldrh r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	mov r0, #0x1
	strh r0, [r1, #0x0]
	bl OSi_SetTimerReserved
	ldr r1, _020CD1EC ; =OSi_AlarmQueue
	mov r2, #0x0
	mov r0, #0x10
	str r2, [r1, #0x0]
	str r2, [r1, #0x4]
	bl OS_DisableIrqMask
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CD1E8: .word OSi_UseAlarm
_020CD1EC: .word OSi_AlarmQueue

	arm_func_start OSi_SetTimer
OSi_SetTimer: ; 0x020CD1F0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	bl OS_GetTick
	ldr r3, _020CD27C ; =0x04000106
	mov r2, #0x0
	strh r2, [r3, #0x0]
	ldr r12, [r4, #0xc]
	ldr r3, [r4, #0x10]
	subs r5, r12, r0
	sbc r4, r3, r1
	ldr r1, _020CD280 ; =OSi_AlarmHandler
	mov r0, #0x1
	bl OSi_EnterTimerCallback
	mov r2, #0x0
	subs r0, r5, r2
	sbcs r0, r4, r2
	ldrlt r2, _020CD284 ; =0x0000FFFE
	blt _020CD254
	mov r0, #0x10000
	subs r0, r5, r0
	sbcs r0, r4, r2
	mvnlt r0, r5
	movlt r0, r0, lsl #0x10
	movlt r2, r0, lsr #0x10
_020CD254:
	ldr r0, _020CD288 ; =0x04000104
	ldr r1, _020CD27C ; =0x04000106
	strh r2, [r0, #0x0]
	mov r2, #0xc1
	mov r0, #0x10
	strh r2, [r1, #0x0]
	bl OS_EnableIrqMask
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CD27C: .word 0x04000106
_020CD280: .word OSi_AlarmHandler
_020CD284: .word 0x0000FFFE
_020CD288: .word 0x04000104
