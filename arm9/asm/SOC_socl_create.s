	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start SOCLi_InitCommandPipe
SOCLi_InitCommandPipe: ; 0x02097C14
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r5, r2
	mov r7, r0
	mov r0, r5
	mov r6, r1
	bl SOCLi_GetSizeCommandPipe
	add r4, r7, r0
	ldrb r2, [r5, #0x3]
	mov r0, r6
	mov r1, r7
	bl OS_InitMessageQueue
	add r0, r6, #0xe0
	bl OS_InitMutex
	ldrh r2, [r5, #0x0]
	add r0, r6, #0x20
	ldr r1, _02097C88 ; =SOCLi_CommandPacketHandler
	str r2, [sp, #0x0]
	ldrb r12, [r5, #0x2]
	mov r2, r6
	mov r3, r4
	str r12, [sp, #0x4]
	bl OS_CreateThread
	add r0, r6, #0x20
	bl OS_WakeupThreadDirect
	mov r0, r4
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02097C88: .word SOCLi_CommandPacketHandler

	arm_func_start SOCLi_InitSocketBuffer
SOCLi_InitSocketBuffer: ; 0x02097C8C
	stmdb sp!, {r4,lr}
	mov r4, r0
	cmp r2, #0x0
	moveq r0, #0x0
	str r0, [r1, #0x4]
	mov r0, r2
	str r2, [r1, #0x0]
	bl SOCLi_RoundUp4
	add r0, r4, r0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start SOCLi_InitSocket
SOCLi_InitSocket: ; 0x02097CB8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	ldrsb r1, [r6, #0x0]
	mov r7, r0
	add r4, r7, #0x80
	strb r1, [r7, #0x73]
	ldrsb r0, [r6, #0x1]
	strb r0, [r7, #0x72]
	ldrh r0, [r6, #0x2]
	cmp r0, #0x0
	beq _02097D40
	str r4, [r7, #0x64]
	ldrh r2, [r6, #0x4]
	mov r1, r4
	add r0, r4, #0x114
	strh r2, [r4, #0xfc]
	add r2, r6, #0x10
	mov r5, r4
	bl SOCLi_InitCommandPipe
	ldrh r2, [r6, #0x2]
	add r1, r7, #0x3c
	bl SOCLi_InitSocketBuffer
	ldrh r2, [r6, #0x8]
	add r1, r7, #0x50
	bl SOCLi_InitSocketBuffer
	ldrh r3, [r6, #0xe]
	add r1, r5, #0x100
	mov r2, #0x0
	strh r3, [r1, #0xa]
	str r2, [r5, #0x110]
	ldr r1, [r5, #0x110]
	mov r4, r0
	str r1, [r5, #0x10c]
_02097D40:
	ldrh r0, [r6, #0x6]
	cmp r0, #0x0
	ldreq r0, _02097DC0 ; =SOCLiUDPSendSocket
	ldreq r0, [r0, #0x0]
	ldreq r0, [r0, #0x68]
	streq r0, [r7, #0x68]
	beq _02097DB0
	str r4, [r7, #0x68]
	mov r1, r4
	str r7, [r4, #0x10c]
	add r0, r4, #0x110
	add r2, r6, #0x14
	mov r5, r4
	bl SOCLi_InitCommandPipe
	ldrh r2, [r6, #0x6]
	add r1, r7, #0x48
	bl SOCLi_InitSocketBuffer
	ldrh r2, [r6, #0xa]
	add r1, r7, #0x58
	bl SOCLi_InitSocketBuffer
	ldrh r2, [r6, #0xc]
	add r1, r4, #0xf8
	bl SOCLi_InitSocketBuffer
	mov r1, #0x0
	str r1, [r5, #0x108]
	ldr r1, [r5, #0x108]
	mov r4, r0
	str r1, [r5, #0x104]
_02097DB0:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02097DC0: .word SOCLiUDPSendSocket

	arm_func_start SOCLi_GetSizeCommandPipe
SOCLi_GetSizeCommandPipe: ; 0x02097DC4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrb r0, [r5, #0x3]
	mov r0, r0, lsl #0x2
	bl SOCLi_RoundUp4
	mov r4, r0
	ldrh r0, [r5, #0x0]
	bl SOCLi_RoundUp4
	add r0, r4, r0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start SOCLi_GetSizeSocket
SOCLi_GetSizeSocket: ; 0x02097DF8
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrh r0, [r5, #0x2]
	mov r4, #0x80
	cmp r0, #0x0
	beq _02097E38
	add r4, r4, #0x114
	bl SOCLi_RoundUp4
	add r4, r4, r0
	ldrh r0, [r5, #0x8]
	bl SOCLi_RoundUp4
	add r4, r4, r0
	add r0, r5, #0x10
	bl SOCLi_GetSizeCommandPipe
	add r4, r4, r0
_02097E38:
	ldrh r0, [r5, #0x6]
	cmp r0, #0x0
	beq _02097E74
	add r4, r4, #0x110
	bl SOCLi_RoundUp4
	add r4, r4, r0
	ldrh r0, [r5, #0xa]
	bl SOCLi_RoundUp4
	add r4, r4, r0
	ldrh r0, [r5, #0xc]
	bl SOCLi_RoundUp4
	add r4, r4, r0
	add r0, r5, #0x14
	bl SOCLi_GetSizeCommandPipe
	add r4, r4, r0
_02097E74:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start SOCLi_StartupSocket
SOCLi_StartupSocket: ; 0x02097E84
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	bl SOCLi_GetSizeSocket
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _02097EF4 ; =SOCLiConfigPtr
	mov r5, r0
	ldr r1, [r1, #0x0]
	mov r0, r4
	ldr r1, [r1, #0x18]
	blx r1
	movs r6, r0
	beq _02097EDC
	mov r2, r4
	mov r1, #0x0
	bl MI_CpuFill8
	mov r0, r6
	mov r1, r7
	bl SOCLi_InitSocket
	mov r0, r6
	bl SOCLi_SocketRegister
_02097EDC:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02097EF4: .word SOCLiConfigPtr

	arm_func_start SOCLi_CreateSocketCallBack
SOCLi_CreateSocketCallBack: ; 0x02097EF8
	stmdb sp!, {r4,lr}
	ldr r4, [r0, #0x4]
	mov r0, r4
	bl CPS_SocRegister
	ldrsb r0, [r4, #0x73]
	ldr r1, [r4, #0x68]
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _02097F58
_02097F1C: ; jump table
	b _02097F30 ; case 0
	b _02097F40 ; case 1
	b _02097F54 ; case 2
	b _02097F58 ; case 3
	b _02097F30 ; case 4
_02097F30:
	add r0, r1, #0x20
	bl CPS_SocDup
	bl CPS_SocUse
	b _02097F58
_02097F40:
	bl CPS_SocUse
	bl CPS_SocDatagramMode
	ldr r0, _02097F6C ; =SOCLi_UdpRecvCallback
	bl CPS_SetUdpCallback
	b _02097F58
_02097F54:
	bl CPS_SocDatagramMode
_02097F58:
	mov r0, #0x1
	strh r0, [r4, #0x70]
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02097F6C: .word SOCLi_UdpRecvCallback

	arm_func_start SOCL_CreateSocket
SOCL_CreateSocket: ; 0x02097F70
	stmdb sp!, {r4,lr}
	bl SOCLi_StartupSocket
	movs r4, r0
	mvneq r0, #0x30
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, _02097FB0 ; =SOCLi_CreateSocketCallBack
	mov r1, r4
	mov r2, #0x1
	bl SOCLi_CreateCommandPacket
	mov r1, r0
	mov r0, r4
	bl SOCLi_ExecCommandPacketInCtrlPipe
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02097FB0: .word SOCLi_CreateSocketCallBack

	arm_func_start SOCLi_ListenAcceptCallBack
SOCLi_ListenAcceptCallBack: ; 0x02097FB4
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r6, r0
	ldr r4, [r6, #0x4]
	ldr r5, [r4, #0x64]
	add r0, r5, #0xe0
	bl OS_LockMutex
	mov r1, #0x0
	ldrh r0, [r6, #0x10]
	mov r2, r1
	bl CPS_SocPingMode
	bl CPS_TcpListen
	mov r2, #0x0
	add r0, sp, #0x0
	add r1, sp, #0x4
	str r2, [r5, #0xf8]
	bl CPS_SocWho
	ldrh r2, [sp, #0x0]
	ldr r1, [r6, #0x14]
	strh r2, [r1, #0x0]
	ldr r1, [r6, #0x18]
	str r0, [r1, #0x0]
	ldrsh r1, [r4, #0x70]
	add r0, r5, #0xe0
	orr r1, r1, #0x4
	strh r1, [r4, #0x70]
	bl OS_UnlockMutex
	mov r0, #0x0
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start SOCL_ListenAccept
SOCL_ListenAccept:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl SOCL_SocketIsInvalid
	cmp r0, #0x0
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	cmp r6, #0x0
	mov r1, #0x0
	beq _0209806C
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_0209806C:
	cmp r1, #0x0
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x2
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldrsb r0, [r6, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _020980A8
	cmp r0, #0x4
	movne r1, #0x0
_020980A8:
	cmp r1, #0x0
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrsb r2, [r6, #0x72]
	cmp r2, #0x1
	mvnne r0, #0x5
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldrh r0, [r6, #0x74]
	cmp r0, #0x0
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, _0209811C ; =SOCLi_ListenAcceptCallBack
	mov r1, r6
	bl SOCLi_CreateCommandPacket
	mov r1, r0
	ldrh r2, [r6, #0x74]
	mov r0, r6
	strh r2, [r1, #0x10]
	str r5, [r1, #0x14]
	str r4, [r1, #0x18]
	ldrsh r2, [r6, #0x70]
	orr r2, r2, #0x2
	strh r2, [r6, #0x70]
	bl SOCLi_ExecCommandPacketInRecvPipe
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209811C: .word SOCLi_ListenAcceptCallBack

	arm_func_start SOCL_Accept
SOCL_Accept:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl SOCL_SocketIsInvalid
	cmp r0, #0x0
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	cmp r6, #0x0
	mov r1, #0x0
	beq _02098164
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_02098164:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x2
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrsb r0, [r6, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _020981A8
	cmp r0, #0x4
	movne r1, #0x0
_020981A8:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrsb r0, [r6, #0x72]
	cmp r0, #0x1
	addne sp, sp, #0x4
	mvnne r0, #0x5
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldr r0, _02098228 ; =SOCLSocketParamTCP
	bl SOCL_CreateSocket
	movs r7, r0
	addmi sp, sp, #0x4
	ldmmiia sp!, {r4-r7,lr}
	bxmi lr
	ldrh r1, [r6, #0x74]
	bl SOCL_Bind
	cmp r0, #0x0
	addlt sp, sp, #0x4
	ldmltia sp!, {r4-r7,lr}
	bxlt lr
	mov r0, r7
	mov r1, r5
	mov r2, r4
	bl SOCL_ListenAccept
	cmp r0, #0x0
	movge r0, r7
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02098228: .word SOCLSocketParamTCP

	arm_func_start SOCL_Listen
SOCL_Listen: ; 0x0209822C
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl SOCL_SocketIsInvalid
	cmp r0, #0x0
	mvnne r0, #0x1b
	ldmneia sp!, {r4,lr}
	bxne lr
	cmp r4, #0x0
	mov r1, #0x0
	beq _02098260
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_02098260:
	cmp r1, #0x0
	mvneq r0, #0x26
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x2
	mvnne r0, #0x1b
	ldmneia sp!, {r4,lr}
	bxne lr
	ldrsb r0, [r4, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _0209829C
	cmp r0, #0x4
	movne r1, #0x0
_0209829C:
	cmp r1, #0x0
	mvneq r0, #0x1b
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrsb r0, [r4, #0x72]
	cmp r0, #0x1
	moveq r0, #0x0
	mvnne r0, #0x5
	ldmia sp!, {r4,lr}
	bx lr
