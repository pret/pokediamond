	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global SOCLiCommandPackets
SOCLiCommandPackets: ; 0x021C8D04
	.space 0x4

	.global SOCLiCommandPacketQueue
SOCLiCommandPacketQueue: ; 0x021C8D08
	.space 0x20

	.text

	arm_func_start SOCLi_CommandPacketHandler
SOCLi_CommandPacketHandler: ; 0x02097878
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	add r6, sp, #0x0
	mov r4, #0x0
	mov r5, #0x1
_02097890:
	mov r0, r9
	mov r1, r6
	mov r2, r5
	bl OS_ReadMessage
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r1, [r0, #0x0]
	blx r1
	mov r7, r0
	bl OS_DisableInterrupts
	mov r8, r0
	bl OS_DisableScheduler
	mov r0, r9
	mov r1, r4
	mov r2, r4
	bl OS_ReceiveMessage
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	strne r7, [r0, #0x6c]
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _02097908
	mov r1, r7
	mov r2, r4
	bl OS_SendMessage
_02097908:
	ldr r0, [sp, #0x0]
	bl SOCLi_FreeCommandPacket
	bl OS_EnableScheduler
	mov r0, r8
	bl OS_RestoreInterrupts
	b _02097890
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start SOCLi_ExecCommandPacketInCtrlPipe
SOCLi_ExecCommandPacketInCtrlPipe: ; 0x0209792C
	stmdb sp!, {r4,lr}
	mov r4, r1
	bl SOCLi_GetCtrlPipe
	mov r1, r4
	bl SOCLi_ExecCommandPacket
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start SOCLi_ExecCommandPacketInSendPipe
SOCLi_ExecCommandPacketInSendPipe:
	ldr ip, _02097954 ; =SOCLi_ExecCommandPacket
	ldr r0, [r0, #0x68]
	bx r12
	.balign 4
_02097954: .word SOCLi_ExecCommandPacket

	arm_func_start SOCLi_ExecCommandPacketInRecvPipe
SOCLi_ExecCommandPacketInRecvPipe: ; 0x02097958
	ldr ip, _02097964 ; =SOCLi_ExecCommandPacket
	ldr r0, [r0, #0x64]
	bx r12
	.balign 4
_02097964: .word SOCLi_ExecCommandPacket

	arm_func_start SOCLi_ExecCommandPacket
SOCLi_ExecCommandPacket: ; 0x02097968
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x2c
	mov r4, r1
	ldrsb r2, [r4, #0xd]
	mov r5, r0
	cmp r2, #0x1
	bne _020979BC
	add r0, sp, #0x8
	add r1, sp, #0x4
	mov r2, #0x1
	bl OS_InitMessageQueue
	add r2, sp, #0x8
	mov r0, r5
	mov r1, r4
	str r2, [r4, #0x8]
	bl SOCLi_SendCommandPacket
	add r0, sp, #0x8
	add r1, sp, #0x0
	mov r2, #0x1
	bl OS_ReceiveMessage
	b _020979CC
_020979BC:
	mov r2, #0x0
	str r2, [r4, #0x8]
	bl SOCLi_SendCommandPacket
	str r0, [sp, #0x0]
_020979CC:
	ldr r0, [sp, #0x0]
	add sp, sp, #0x2c
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start SOCLi_SendCommandPacketToCtrlPipe
SOCLi_SendCommandPacketToCtrlPipe:
	stmdb sp!, {r4,lr}
	mov r4, r1
	bl SOCLi_GetCtrlPipe
	mov r1, r4
	bl SOCLi_SendCommandPacket
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start SOCLi_SendCommandPacket
SOCLi_SendCommandPacket:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r5, r1
	beq _02097A14
	ldrsb r1, [r5, #0xd]
	ands r1, r1, #0x1
	beq _02097A1C
_02097A14:
	mov r2, #0x1
	b _02097A20
_02097A1C:
	mov r2, #0x0
_02097A20:
	mov r1, r5
	bl OS_SendMessage
	movs r4, r0
	bne _02097A38
	mov r0, r5
	bl SOCLi_FreeCommandPacket
_02097A38:
	cmp r4, #0x0
	movne r0, #0x0
	mvneq r0, #0x29
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start SOCLi_GetCtrlPipe
SOCLi_GetCtrlPipe: ; 0x02097A50
	ldr r1, [r0, #0x64]
	cmp r1, #0x0
	ldreq r1, [r0, #0x68]
	mov r0, r1
	bx lr

	arm_func_start SOCLi_FreeCommandPacket
SOCLi_FreeCommandPacket:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	movs r1, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r0, _02097A94 ; =SOCLiCommandPacketQueue
	mov r2, #0x0
	bl OS_SendMessage
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02097A94: .word SOCLiCommandPacketQueue

	arm_func_start SOCLi_CreateCommandPacket
SOCLi_CreateCommandPacket: ; 0x02097A98
	stmdb sp!, {r4-r6,lr}
	mov r4, r2
	mov r6, r0
	mov r0, r4
	mov r5, r1
	bl SOCLi_AllocCommandPacket
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	str r6, [r0, #0x0]
	str r5, [r0, #0x4]
	mov r1, #0x0
	str r1, [r0, #0x8]
	ldrsb r1, [r5, #0x73]
	strb r1, [r0, #0xc]
	strb r4, [r0, #0xd]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start SOCLi_AllocCommandPacket
SOCLi_AllocCommandPacket:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r0
	ldr r0, _02097B10 ; =SOCLiCommandPacketQueue
	add r1, sp, #0x0
	bl OS_ReceiveMessage
	cmp r0, #0x0
	ldrne r0, [sp, #0x0]
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02097B10: .word SOCLiCommandPacketQueue

	arm_func_start SOCLi_CleanupCommandPacketQueue
SOCLi_CleanupCommandPacketQueue: ; 0x02097B14
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _02097B6C ; =SOCLiCommandPacketQueue
	ldr r1, [r0, #0x1c]
	ldr r0, [r0, #0x14]
	cmp r1, r0
	addlt sp, sp, #0x4
	mvnlt r0, #0x0
	ldmltia sp!, {lr}
	bxlt lr
	ldr r0, _02097B70 ; =SOCLiConfigPtr
	ldr r1, _02097B74 ; =SOCLiCommandPackets
	ldr r2, [r0, #0x0]
	ldr r0, [r1, #0x0]
	ldr r1, [r2, #0x1c]
	blx r1
	ldr r1, _02097B74 ; =SOCLiCommandPackets
	mov r0, #0x0
	str r0, [r1, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02097B6C: .word SOCLiCommandPacketQueue
_02097B70: .word SOCLiConfigPtr
_02097B74: .word SOCLiCommandPackets

	arm_func_start SOCLi_StartupCommandPacketQueue
SOCLi_StartupCommandPacketQueue: ; 0x02097B78
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	mov r0, #0x2c
	mul r1, r4, r0
	ldr r0, _02097C08 ; =SOCLiConfigPtr
	mov r2, r4, lsl #0x2
	add r2, r2, #0x3
	ldr r0, [r0, #0x0]
	add r1, r1, #0x3
	bic r5, r2, #0x3
	bic r2, r1, #0x3
	ldr r1, [r0, #0x18]
	add r0, r2, r5
	blx r1
	movs r6, r0
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, _02097C0C ; =SOCLiCommandPacketQueue
	mov r1, r6
	mov r2, r4
	bl OS_InitMessageQueue
	cmp r4, #0x0
	add r5, r6, r5
	ble _02097BF4
_02097BDC:
	mov r0, r5
	bl SOCLi_FreeCommandPacket
	sub r4, r4, #0x1
	cmp r4, #0x0
	add r5, r5, #0x2c
	bgt _02097BDC
_02097BF4:
	ldr r1, _02097C10 ; =SOCLiCommandPackets
	mov r0, #0x0
	str r6, [r1, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_02097C08: .word SOCLiConfigPtr
_02097C0C: .word SOCLiCommandPacketQueue
_02097C10: .word SOCLiCommandPackets
