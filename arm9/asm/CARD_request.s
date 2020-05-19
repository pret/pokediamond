	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start CARDi_Request
CARDi_Request:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r6, r0
	ldr r0, [r6, #0x114]
	mov r5, r1
	mov r4, r2
	ands r0, r0, #0x2
	bne _020D7A44
	ldr r1, [r6, #0x114]
	mov r0, #0xb
	orr r2, r1, #0x2
	mov r1, #0x1
	str r2, [r6, #0x114]
	bl PXI_IsCallbackReady
_020D7A04: ; 0x020D7A04
	cmp r0, #0x0
	bne _020D7A34
	mov r9, #0x64
	mov r8, #0xb
	mov r7, #0x1
_020D7A18:
	mov r0, r9
	bl OS_SpinWait
	mov r0, r8
	mov r1, r7
	bl PXI_IsCallbackReady
_020D7A2C: ; 0x020D7A2C
	cmp r0, #0x0
	beq _020D7A18
_020D7A34:
	mov r0, r6
	mov r1, #0x0
	mov r2, #0x1
	bl CARDi_Request
_020D7A44:
	ldr r0, [r6, #0x0]
	mov r1, #0x60
	bl DC_FlushRange
	bl DC_WaitWriteBufferEmpty
	mov r9, #0xb
	mov r8, #0x1
	mov r7, #0x0
	mov r11, #0x60
_020D7A64:
	str r5, [r6, #0x4]
	ldr r0, [r6, #0x114]
	orr r0, r0, #0x20
	str r0, [r6, #0x114]
_020D7A74:
	mov r0, r9
	mov r1, r5
	mov r2, r8
	bl PXI_SendWordByFifo
_020D7A84: ; 0x020D7A84
	cmp r0, #0x0
	blt _020D7A74
	cmp r5, #0x0
	bne _020D7AB0
	ldr r10, [r6, #0x0]
_020D7A98:
	mov r0, r9
	mov r1, r10
	mov r2, r8
	bl PXI_SendWordByFifo
_020D7AA8: ; 0x020D7AA8
	cmp r0, #0x0
	blt _020D7A98
_020D7AB0:
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x114]
	mov r10, r0
	ands r0, r1, #0x20
	beq _020D7AD8
_020D7AC4:
	mov r0, r7
	bl OS_SleepThread
	ldr r0, [r6, #0x114]
	ands r0, r0, #0x20
	bne _020D7AC4
_020D7AD8:
	mov r0, r10
	bl OS_RestoreInterrupts
_020D7AE0: ; 0x020D7AE0
	ldr r0, [r6, #0x0]
	mov r1, r11
	bl DC_InvalidateRange
_020D7AEC: ; 0x020D7AEC
	ldr r0, [r6, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x4
	bne _020D7B08
	sub r4, r4, #0x1
	cmp r4, #0x0
	bgt _020D7A64
_020D7B08:
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start CARDi_TaskThread
CARDi_TaskThread: ; 0x020D7B20
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r5, _020D7B78 ; =0x021D55C0
	mov r6, #0x0
	add r7, r5, #0x44
_020D7B34:
	bl OS_DisableInterrupts
	ldr r1, [r5, #0x114]
	mov r4, r0
	ands r0, r1, #0x8
	bne _020D7B60
_020D7B48:
	mov r0, r6
	str r7, [r5, #0x104]
	bl OS_SleepThread
	ldr r0, [r5, #0x114]
	ands r0, r0, #0x8
	beq _020D7B48
_020D7B60:
	mov r0, r4
	bl OS_RestoreInterrupts
	ldr r1, [r5, #0x40]
	mov r0, r5
	blx r1
	b _020D7B34
	.balign 4
_020D7B78: .word 0x021D55C0

	arm_func_start CARDi_OnFifoRecv
CARDi_OnFifoRecv: ; 0x020D7B7C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0xb
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r1, _020D7BC8 ; =0x021D55C0
	ldr r0, [r1, #0x114]
	bic r0, r0, #0x20
	str r0, [r1, #0x114]
	ldr r0, [r1, #0x104]
	bl OS_WakeupThreadDirect
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D7BC8: .word 0x021D55C0
