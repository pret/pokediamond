	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start SOCLi_TrashSocket
SOCLi_TrashSocket: ; 0x020996C0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r4, _02099704 ; =SOCLiSocketListTrash
	mov r5, r0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020996F0
_020996E0:
	bl SOCLi_CleanupSocket
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _020996E0
_020996F0:
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_02099704: .word SOCLiSocketListTrash

	arm_func_start SOCLi_FreeCommandPipe
SOCLi_FreeCommandPipe: ; 0x02099708
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	movs r8, r0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	add r0, r8, #0x20
	bl OS_JoinThread
	bl OS_DisableInterrupts
	mov r7, r0
	bl OS_DisableScheduler
	add r1, sp, #0x0
	mov r0, r8
	mov r2, #0x0
	bl OS_ReceiveMessage
	cmp r0, #0x0
	beq _0209979C
	add r4, sp, #0x0
	mvn r6, #0xa
	mov r5, #0x0
_02099758:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _02099784
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0209977C
	mov r1, r6
	mov r2, r5
	bl OS_SendMessage
_0209977C:
	ldr r0, [sp, #0x0]
	bl SOCLi_FreeCommandPacket
_02099784:
	mov r0, r8
	mov r1, r4
	mov r2, r5
	bl OS_ReceiveMessage
	cmp r0, #0x0
	bne _02099758
_0209979C:
	bl OS_EnableScheduler
	bl OS_RescheduleThread
	mov r0, r7
	bl OS_RestoreInterrupts
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start SOCLi_CleanupSocket
SOCLi_CleanupSocket:
	stmdb sp!, {r4-r6,lr}
	movs r4, r0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r0, #0x0
	strh r0, [r4, #0x70]
	ldrsb r1, [r4, #0x73]
	mov r2, #0x1
	cmp r1, #0x0
	beq _020997E8
	cmp r1, #0x4
	movne r2, r0
_020997E8:
	cmp r2, #0x0
	beq _02099804
	ldr r0, [r4, #0x68]
	bl SOCLi_FreeCommandPipe
	ldr r0, [r4, #0x64]
	bl SOCLi_FreeCommandPipe
	b _02099884
_02099804:
	cmp r1, #0x1
	bne _02099874
	ldr r0, [r4, #0x64]
	ldr r0, [r0, #0x104]
	cmp r0, #0x0
	beq _0209983C
	ldr r5, _020998C0 ; =SOCLiConfigPtr
_02099820:
	ldr r1, [r5, #0x0]
	ldr r6, [r0, #0x0]
	ldr r1, [r1, #0x1c]
	blx r1
	mov r0, r6
	cmp r6, #0x0
	bne _02099820
_0209983C:
	ldr r0, [r4, #0x64]
	mov r1, #0x0
	add r0, r0, #0x100
	strh r1, [r0, #0x8]
	ldr r0, [r4, #0x64]
	str r1, [r0, #0x100]
	ldr r0, [r4, #0x64]
	str r1, [r0, #0x104]
	ldr r0, [r4, #0x64]
	add r0, r0, #0x10c
	bl OS_WakeupThread
	ldr r0, [r4, #0x64]
	bl SOCLi_FreeCommandPipe
	b _02099884
_02099874:
	cmp r1, #0x2
	bne _02099884
	ldr r0, [r4, #0x68]
	bl SOCLi_FreeCommandPipe
_02099884:
	bl OS_DisableInterrupts
	mov r5, r0
	mov r0, r4
	bl SOCLi_SocketUnregister
	mov r0, r4
	bl SOCLi_SocketUnregisterTrash
	ldr r1, _020998C0 ; =SOCLiConfigPtr
	mov r0, r4
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x1c]
	blx r1
	mov r0, r5
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020998C0: .word SOCLiConfigPtr

	arm_func_start SOCLi_CloseCallBack
SOCLi_CloseCallBack: ; 0x020998C4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r4, [r0, #0x4]
	mov r1, #0x1
	ldrsb r0, [r4, #0x73]
	cmp r0, #0x0
	beq _020998E8
	cmp r0, #0x4
	movne r1, #0x0
_020998E8:
	cmp r1, #0x0
	beq _02099908
	ldr r0, [r4, #0x68]
	add r0, r0, #0x20
	bl OS_JoinThread
	bl CPS_TcpShutdown
	bl CPS_TcpClose
	bl CPS_SocRelease
_02099908:
	bl CPS_SocUnRegister
	ldrsh r0, [r4, #0x70]
	mov r1, #0x0
	bic r0, r0, #0x6
	strh r0, [r4, #0x70]
	ldrsb r0, [r4, #0x73]
	cmp r0, #0x2
	ldreq r0, [r4, #0x68]
	ldrne r0, [r4, #0x64]
	bl SOCLi_SendCommandPacket
	bl OS_DisableInterrupts
	mov r5, r0
	mov r0, r4
	bl SOCLi_SocketUnregister
	mov r0, r4
	bl SOCLi_SocketRegisterTrash
	mov r0, r5
	bl OS_RestoreInterrupts
	ldrsh r1, [r4, #0x70]
	mov r0, #0x0
	orr r1, r1, #0x20
	strh r1, [r4, #0x70]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start SOCL_Close
SOCL_Close: ; 0x0209996C
	stmdb sp!, {r4,lr}
	mov r4, r0
	cmp r4, #0x0
	mvnle r0, #0x1b
	ldmleia sp!, {r4,lr}
	bxle lr
	bl SOCL_SocketIsInTrash
	cmp r0, #0x0
	mvnne r0, #0x19
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r0, r4
	bl SOCL_SocketIsInvalid
	cmp r0, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	cmp r4, #0x0
	mov r1, #0x0
	beq _020999C8
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_020999C8:
	cmp r1, #0x0
	mvneq r0, #0x26
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x10
	mvnne r0, #0x19
	ldmneia sp!, {r4,lr}
	bxne lr
	ldrsh r0, [r4, #0x70]
	mov r1, #0x1
	orr r0, r0, #0x18
	strh r0, [r4, #0x70]
	ldrsb r0, [r4, #0x73]
	cmp r0, #0x0
	beq _02099A10
	cmp r0, #0x4
	movne r1, #0x0
_02099A10:
	cmp r1, #0x0
	beq _02099A24
	ldr r0, [r4, #0x68]
	mov r1, #0x0
	bl SOCLi_SendCommandPacket
_02099A24:
	ldr r0, _02099A54 ; =SOCLi_CloseCallBack
	mov r1, r4
	mov r2, #0x1
	bl SOCLi_CreateCommandPacket
	mov r1, r0
	mov r2, #0x0
	mov r0, r4
	str r2, [r1, #0x8]
	bl SOCLi_SendCommandPacketToCtrlPipe
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02099A54: .word SOCLi_CloseCallBack

	arm_func_start SOCL_IsClosed
SOCL_IsClosed:
	stmdb sp!, {r4,lr}
	movs r4, r0
	bmi _02099A88
	bl SOCL_SocketIsInvalid
	cmp r0, #0x0
	beq _02099A88
	mov r0, r4
	bl SOCL_SocketIsInTrash
	cmp r0, #0x0
	moveq r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
_02099A88:
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
