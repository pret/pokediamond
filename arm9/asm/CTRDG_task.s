	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_021D6B54
	.extern UNK_021D6F78
	.extern UNK_021D6B50

	.text

	arm_func_start CTRDGi_SetTask
CTRDGi_SetTask: ; 0x020DD9FC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r3, _020DDAA8 ; =UNK_021D6B50
	mov r7, r0
	mov r4, r1
	mov r6, r2
	ldr r5, [r3, #0x0]
	bl CTRDGi_IsTaskAvailable
_020DDA1C: ; 0x020DDA1C
	cmp r0, #0x0
	bne _020DDA28
	bl OS_Terminate
_020DDA28:
	ldr r0, _020DDAAC ; =UNK_021D6B54
	ldrb r0, [r0, #0x22]
	cmp r0, #0x0
	beq _020DDA3C
	bl OS_Terminate
_020DDA3C:
	bl OS_DisableInterrupts
	mov r1, #0x1
	strb r1, [r7, #0x22]
	str r4, [r7, #0x0]
	add r1, r5, #0xc4
	cmp r7, r1
	mov r4, r0
	ldreq r0, _020DDAA8 ; =UNK_021D6B50
	str r6, [r7, #0x4]
	moveq r1, #0x0
	streq r1, [r0, #0x0]
	ldr ip, _020DDAAC ; =UNK_021D6B54
	ldmia r7!, {r0-r3}
	mov r6, r12
	stmia r12!, {r0-r3}
	ldmia r7!, {r0-r3}
	stmia r12!, {r0-r3}
	ldr r1, [r7, #0x0]
	mov r0, r5
	str r1, [r12, #0x0]
	str r6, [r5, #0xc0]
	bl OS_WakeupThreadDirect
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DDAA8: .word UNK_021D6B50
_020DDAAC: .word UNK_021D6B54

	arm_func_start CTRDGi_TaskThread
CTRDGi_TaskThread: ; 0x020DDAB0
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x28
	ldr r6, _020DDB94 ; =UNK_021D6B54
	ldr r5, _020DDB98 ; =UNK_021D6B50
	mov r4, r0
	add r9, sp, #0x0
	mov r8, #0x0
	mov r7, #0x24
_020DDAD0:
	mov r0, r9
	mov r1, r8
	mov r2, r7
	bl MI_CpuFill8
	bl OS_DisableInterrupts
	ldr r1, [r4, #0xc0]
	mov r10, r0
	cmp r1, #0x0
	bne _020DDB08
_020DDAF4:
	mov r0, r8
	bl OS_SleepThread
	ldr r0, [r4, #0xc0]
	cmp r0, #0x0
	beq _020DDAF4
_020DDB08:
	ldr lr, [r4, #0xc0]
	add r12, sp, #0x0
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldr r1, [lr, #0x0]
	mov r0, r10
	str r1, [r12, #0x0]
	bl OS_RestoreInterrupts
	ldr r1, [sp, #0x0]
	cmp r1, #0x0
	beq _020DDB48
	mov r0, r9
	blx r1
	str r0, [sp, #0x8]
_020DDB48:
	bl OS_DisableInterrupts
	ldr r1, [sp, #0x4]
	mov r10, r0
	strb r8, [r6, #0x22]
	cmp r1, #0x0
	beq _020DDB68
	mov r0, r9
	blx r1
_020DDB68:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _020DDB84
	mov r0, r10
	str r8, [r4, #0xc0]
	bl OS_RestoreInterrupts
	b _020DDAD0
_020DDB84:
	bl OS_ExitThread
	add sp, sp, #0x28
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_020DDB94: .word UNK_021D6B54
_020DDB98: .word UNK_021D6B50

	arm_func_start CTRDGi_InitTaskInfo
CTRDGi_InitTaskInfo:
	ldr ip, _020DDBAC ; =MI_CpuFill8
	mov r1, #0x0
	mov r2, #0x24
	bx r12
	.balign 4
_020DDBAC: .word MI_CpuFill8

	arm_func_start CTRDGi_IsTaskAvailable
CTRDGi_IsTaskAvailable:
	ldr r0, _020DDBC8 ; =UNK_021D6B50
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	bx lr
	.balign 4
_020DDBC8: .word UNK_021D6B50

	arm_func_start CTRDGi_InitTaskThread
CTRDGi_InitTaskThread: ; 0x020DDBCC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020DDC4C ; =UNK_021D6B50
	mov r4, r0
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	bne _020DDC38
	add r0, r5, #0xc4
	str r5, [r1, #0x0]
	bl CTRDGi_InitTaskInfo
	ldr r0, _020DDC50 ; =UNK_021D6B54
	bl CTRDGi_InitTaskInfo
_020DDC04: ; 0x020DDC04
	mov r0, #0x0
	str r0, [r5, #0xc0]
	mov r2, #0x400
	ldr r1, _020DDC54 ; =CTRDGi_TaskThread
	ldr r3, _020DDC58 ; =UNK_021D6F78
	mov r0, r5
	str r2, [sp, #0x0]
	mov r2, #0x14
	str r2, [sp, #0x4]
	mov r2, r5
	bl OS_CreateThread
	mov r0, r5
	bl OS_WakeupThreadDirect
_020DDC38:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DDC4C: .word UNK_021D6B50
_020DDC50: .word UNK_021D6B54
_020DDC54: .word CTRDGi_TaskThread
_020DDC58: .word UNK_021D6F78
