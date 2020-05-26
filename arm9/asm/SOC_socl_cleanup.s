	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start SOCL_CalmDown
SOCL_CalmDown: ; 0x02099A94
	stmdb sp!, {r4,lr}
	ldr r0, _02099B10 ; =SOCLiUDPSendSocket
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02099AE8
	bl SOCL_CloseAll
	movs r4, r0
	bne _02099AE0
	ldr r0, _02099B10 ; =SOCLiUDPSendSocket
	ldr r0, [r0, #0x0]
	bl SOCL_Close
	ldr r0, _02099B10 ; =SOCLiUDPSendSocket
	ldr r0, [r0, #0x0]
	bl SOCL_IsClosed
	cmp r0, #0x0
	ldrne r0, _02099B10 ; =SOCLiUDPSendSocket
	movne r1, #0x0
	strne r1, [r0, #0x0]
	mvn r4, #0x19
_02099AE0:
	bl SOCLi_TrashSocket
	b _02099B04
_02099AE8:
	bl CPS_CalmDown
	cmp r0, #0x0
	mvneq r4, #0x19
	beq _02099B04
	mov r0, #0x0
	bl WCM_SetRecvDCFCallback
	mov r4, #0x0
_02099B04:
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02099B10: .word SOCLiUDPSendSocket

	arm_func_start SOCL_CloseAll
SOCL_CloseAll: ; 0x02099B14
	stmdb sp!, {r4-r6,lr}
	ldr r4, _02099BBC ; =SOCLiUDPSendSocket
	ldr r5, _02099BC0 ; =SOCLiSocketList
_02099B20:
	bl OS_DisableInterrupts
	ldr r6, [r5, #0x0]
	cmp r6, #0x0
	beq _02099B54
	ldr r2, [r4, #0x0]
_02099B34:
	cmp r6, r2
	beq _02099B48
	ldrsh r1, [r6, #0x70]
	ands r1, r1, #0x10
	beq _02099B54
_02099B48:
	ldr r6, [r6, #0x7c]
	cmp r6, #0x0
	bne _02099B34
_02099B54:
	bl OS_RestoreInterrupts
	cmp r6, #0x0
	beq _02099B6C
	mov r0, r6
	bl SOCL_Close
	b _02099B20
_02099B6C:
	ldr r0, _02099BC0 ; =SOCLiSocketList
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02099B98
	ldr r0, _02099BBC ; =SOCLiUDPSendSocket
	ldr r0, [r0, #0x0]
	cmp r1, r0
	bne _02099BB0
	ldr r0, [r1, #0x7c]
	cmp r0, #0x0
	bne _02099BB0
_02099B98:
	ldr r0, _02099BC4 ; =SOCLiSocketListTrash
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
_02099BB0:
	mvn r0, #0x19
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_02099BBC: .word SOCLiUDPSendSocket
_02099BC0: .word SOCLiSocketList
_02099BC4: .word SOCLiSocketListTrash

	arm_func_start SOCL_Cleanup
SOCL_Cleanup: ; 0x02099BC8
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _02099C68 ; =SOCLiRequestedIP
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	ldreq r0, _02099C6C ; =CPSMyIp
	ldreq r0, [r0, #0x0]
	streq r0, [r1, #0x0]
	bl SOCL_CalmDown
	mvn r4, #0x19
	cmp r0, r4
	bne _02099C10
	mov r5, #0x64
_02099BFC:
	mov r0, r5
	bl OS_Sleep
	bl SOCL_CalmDown
	cmp r0, r4
	beq _02099BFC
_02099C10:
	bl SOCLi_CleanupCommandPacketQueue
	movs r4, r0
	bmi _02099C58
	bl CPS_Cleanup
	mov r0, #0x0
	bl CPS_SetScavengerCallback
	ldr r0, _02099C70 ; =SOCLiConfigPtr
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x28]
	cmp r0, #0x0
	bne _02099C4C
	ldr r0, _02099C74 ; =SOCLiCPSConfig
	ldr r1, [r1, #0x1c]
	ldr r0, [r0, #0x1c]
	blx r1
_02099C4C:
	ldr r0, _02099C70 ; =SOCLiConfigPtr
	mov r1, #0x0
	str r1, [r0, #0x0]
_02099C58:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_02099C68: .word SOCLiRequestedIP
_02099C6C: .word CPSMyIp
_02099C70: .word SOCLiConfigPtr
_02099C74: .word SOCLiCPSConfig

	arm_func_start SOCL_GetHostID
SOCL_GetHostID: ; 02099C78
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _02099CE0 ; =CPSMyIp
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	bne _02099CBC
	ldr r0, _02099CE4 ; =SOCLiDhcpState
	ldr r0, [r0, #0x0]
	and r0, r0, #0x3
	cmp r0, #0x1
	bne _02099CCC
	bl OS_GetProcMode
	cmp r0, #0x12
	beq _02099CCC
	mov r0, #0xa
	bl OS_Sleep
	b _02099CCC
_02099CBC:
	ldr r0, _02099CE8 ; =SOCLiRequestedIP
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	streq r2, [r0, #0x0]
_02099CCC:
	ldr r0, _02099CE0 ; =CPSMyIp
	ldr r0, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02099CE0: .word CPSMyIp
_02099CE4: .word SOCLiDhcpState
_02099CE8: .word SOCLiRequestedIP

	arm_func_start SOCL_SetResolver
SOCL_SetResolver: ; 0x02099CEC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl SOCL_GetHostID
	cmp r0, #0x0
	ldrne r1, _02099D24 ; =CPSDnsIp
	mvneq r0, #0x26
	movne r0, #0x0
	strne r5, [r1, #0x0]
	strne r4, [r1, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_02099D24: .word CPSDnsIp

	arm_func_start SOCL_InetAtoH
SOCL_InetAtoH: ; 0x022099D28
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _02099D84 ; =CPSDnsIp
	mov r5, r0
	ldr r7, [r1, #0x0]
	mov r2, #0x0
	ldr r6, [r1, #0x4]
	mov r0, r4
	str r2, [r1, #0x0]
	str r2, [r1, #0x4]
	bl CPS_Resolve
	ldr r1, _02099D84 ; =CPSDnsIp
	mov r4, r0
	mov r0, r5
	str r7, [r1, #0x0]
	str r6, [r1, #0x4]
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02099D84: .word CPSDnsIp

	arm_func_start SOCL_Resolve
SOCL_Resolve: ; 0x02099D88
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x64
	movs r4, r0
	addeq sp, sp, #0x64
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r1, _02099E34 ; =SOCLiConfigPtr
	mov r0, #0xfd0
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x18]
	blx r1
	movs r5, r0
	addeq sp, sp, #0x64
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	add r0, sp, #0x0
	mov r1, #0x0
	mov r2, #0x64
	bl MI_CpuFill8
	ldr r3, _02099E38 ; =0x00000B68
	ldr r1, _02099E3C ; =0x00000466
	add r2, r5, r3
	add r0, sp, #0x0
	str r5, [sp, #0x40]
	str r3, [sp, #0x3c]
	str r2, [sp, #0x4c]
	str r1, [sp, #0x48]
	bl CPS_SocRegister
	mov r0, r4
	bl CPS_Resolve
	mov r4, r0
	bl CPS_SocUnRegister
	ldr r1, _02099E34 ; =SOCLiConfigPtr
	mov r0, r5
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x1c]
	blx r1
	mov r0, r4
	add sp, sp, #0x64
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_02099E34: .word SOCLiConfigPtr
_02099E38: .word 0x00000B68
_02099E3C: .word 0x00000466
