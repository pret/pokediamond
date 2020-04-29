    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_ReadMessage
OS_ReadMessage: ; 0x020CBBE0
	stmdb sp!, {r4-r8,lr}
	mov r6, r0
	mov r5, r1
	mov r7, r2
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x1c]
	mov r4, r0
	cmp r1, #0x0
	bne _020CBC3C
	and r8, r7, #0x1
	add r7, r6, #0x8
_020CBC0C:
	cmp r8, #0x0
	bne _020CBC28
	mov r0, r4
	bl OS_RestoreInterrupts
_020CBC1C:
	mov r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CBC28:
	mov r0, r7
	bl OS_SleepThread
	ldr r0, [r6, #0x1c]
	cmp r0, #0x0
	beq _020CBC0C
_020CBC3C:
	cmp r5, #0x0
	ldrne r1, [r6, #0x10]
	ldrne r0, [r6, #0x18]
	ldrne r0, [r1, r0, lsl #0x2]
	strne r0, [r5, #0x0]
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start OS_JamMessage
OS_JamMessage: ; 0x020CBC64
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r5, r1
	mov r7, r2
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x14]
	ldr r2, [r6, #0x1c]
	mov r4, r0
	cmp r1, r2
	bgt _020CBCCC
	and r7, r7, #0x1
_020CBC94:
	cmp r7, #0x0
	bne _020CBCB4
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020CBCB4:
	mov r0, r6
	bl OS_SleepThread
	ldr r1, [r6, #0x14]
	ldr r0, [r6, #0x1c]
	cmp r1, r0
	ble _020CBC94
_020CBCCC:
	ldr r0, [r6, #0x18]
	add r0, r0, r1
	sub r0, r0, #0x1
	bl _s32_div_f
	str r1, [r6, #0x18]
	ldr r2, [r6, #0x10]
	ldr r1, [r6, #0x18]
	add r0, r6, #0x8
	str r5, [r2, r1, lsl #0x2]
	ldr r1, [r6, #0x1c]
	add r1, r1, #0x1
	str r1, [r6, #0x1c]
	bl OS_WakeupThread
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start OS_ReceiveMessage
OS_ReceiveMessage: ; 0x020CBD18
	stmdb sp!, {r4-r8,lr}
	mov r6, r0
	mov r5, r1
	mov r7, r2
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x1c]
	mov r4, r0
	cmp r1, #0x0
	bne _020CBD74
	and r8, r7, #0x1
	add r7, r6, #0x8
_020CBD44:
	cmp r8, #0x0
	bne _020CBD60
	mov r0, r4
	bl OS_RestoreInterrupts
_020CBD54:
	mov r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CBD60:
	mov r0, r7
	bl OS_SleepThread
	ldr r0, [r6, #0x1c]
	cmp r0, #0x0
	beq _020CBD44
_020CBD74:
	cmp r5, #0x0
	ldrne r1, [r6, #0x10]
	ldrne r0, [r6, #0x18]
	ldrne r0, [r1, r0, lsl #0x2]
	strne r0, [r5, #0x0]
	ldr r0, [r6, #0x18]
	ldr r1, [r6, #0x14]
	add r0, r0, #0x1
	bl _s32_div_f
	str r1, [r6, #0x18]
	ldr r1, [r6, #0x1c]
	mov r0, r6
	sub r1, r1, #0x1
	str r1, [r6, #0x1c]
	bl OS_WakeupThread
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start OS_SendMessage
OS_SendMessage: ; 0x020CBDC4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r5, r1
	mov r7, r2
	bl OS_DisableInterrupts
	ldr r2, [r6, #0x1c]
	ldr r1, [r6, #0x14]
	mov r4, r0
	cmp r1, r2
	bgt _020CBE2C
	and r7, r7, #0x1
_020CBDF4:
	cmp r7, #0x0
	bne _020CBE14
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020CBE14:
	mov r0, r6
	bl OS_SleepThread
	ldr r2, [r6, #0x1c]
	ldr r1, [r6, #0x14]
	cmp r1, r2
	ble _020CBDF4
_020CBE2C:
	ldr r0, [r6, #0x18]
	add r0, r0, r2
	bl _s32_div_f
	ldr r2, [r6, #0x10]
	add r0, r6, #0x8
	str r5, [r2, r1, lsl #0x2]
	ldr r1, [r6, #0x1c]
	add r1, r1, #0x1
	str r1, [r6, #0x1c]
	bl OS_WakeupThread
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start OS_InitMessageQueue
OS_InitMessageQueue: ; 0x020CBE6C
	mov r12, #0x0
	str r12, [r0, #0x4]
	ldr r3, [r0, #0x4]
	str r3, [r0, #0x0]
	str r12, [r0, #0xc]
	ldr r3, [r0, #0xc]
	str r3, [r0, #0x8]
	str r1, [r0, #0x10]
	str r2, [r0, #0x14]
	str r12, [r0, #0x18]
	str r12, [r0, #0x1c]
	bx lr
