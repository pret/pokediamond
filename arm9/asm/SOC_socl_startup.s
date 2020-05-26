	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global SOCLiConfigPtr
SOCLiConfigPtr: ; 0x021C8CC0
	.space 0x4

	.global SOCLiYieldWait
SOCLiYieldWait: ; 0x021C8CC4
	.space 0x4

	.global SOCLiRequestedIP
SOCLiRequestedIP: ; 0x021C8CC8
	.space 0x4

	.global SOCLiDhcpState
SOCLiDhcpState: ; 0x021C8CCC
	.space 0x4

	.global SOCLiUDPSendSocket
SOCLiUDPSendSocket: ; 0x021C8CD0
	.space 0x4

	.global SOCLiCPSConfig
SOCLiCPSConfig: ; 0x021C8CD4
	.space 0x30

	.text

	arm_func_start SOCL_LinkIsOn
SOCL_LinkIsOn: ; 0x020975B4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl WCM_GetApMacAddress
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SOCLi_DhcpTimeout
SOCLi_DhcpTimeout: ; 0x020975D8
	ldr r0, _020975EC ; =SOCLiDhcpState
	ldr r1, [r0, #0x0]
	orr r1, r1, #0x2
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020975EC: .word SOCLiDhcpState

	arm_func_start SOCLi_SetMyIP
SOCLi_SetMyIP: ; 0x020975F0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _02097654 ; =SOCLiConfigPtr
	ldr r0, _02097658 ; =SOCLiDhcpState
	ldr lr, [r1, #0x0]
	ldr r3, [r0, #0x0]
	ldr r12, [lr, #0x4]
	ldr r2, _0209765C ; =CPSMyIp
	ldr r1, _02097660 ; =CPSNetMask
	str r12, [r2, #0x0]
	ldr r12, [lr, #0x8]
	ldr r2, _02097664 ; =CPSGatewayIp
	str r12, [r1, #0x0]
	ldr r12, [lr, #0xc]
	ldr r1, _02097668 ; =CPSDnsIp
	str r12, [r2, #0x0]
	ldr r12, [lr, #0x10]
	orr r2, r3, #0x2
	str r12, [r1, #0x0]
	ldr r3, [lr, #0x14]
	str r3, [r1, #0x4]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02097654: .word SOCLiConfigPtr
_02097658: .word SOCLiDhcpState
_0209765C: .word CPSMyIp
_02097660: .word CPSNetMask
_02097664: .word CPSGatewayIp
_02097668: .word CPSDnsIp

	arm_func_start SOCLi_StartupCPS
SOCLi_StartupCPS: ; 0x0209766C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020977C0 ; =SOCLiConfigPtr
	ldr r5, _020977C4 ; =SOCLiCPSConfig
	ldr r4, [r0, #0x0]
	mov r0, r5
	mov r1, #0x0
	mov r2, #0x30
	bl MI_CpuFill8
	ldr r0, _020977C8 ; =SOCLiYieldWait
	ldr r2, [r4, #0x18]
	mov r1, r5
	str r2, [r1, #0x4]
	ldr r12, [r4, #0x1c]
	mov r2, #0x0
	ldr r3, _020977CC ; =SOCL_LinkIsOn
	ldr r0, [r0, #0x0]
	str r12, [r1, #0x8]
	str r3, [r1, #0x10]
	str r2, [r1, #0x14]
	str r2, [r1, #0x18]
	str r0, [r1, #0x2c]
	ldr r0, [r4, #0x24]
	cmp r0, #0x0
	strne r0, [r5, #0x20]
	moveq r0, #0x4000
	streq r0, [r5, #0x20]
	ldr r0, [r4, #0x28]
	cmp r0, #0x0
	strne r0, [r5, #0x1c]
	bne _02097700
	ldr r1, _020977C0 ; =SOCLiConfigPtr
	ldr r0, [r5, #0x20]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x18]
	blx r1
	str r0, [r5, #0x1c]
_02097700:
	ldr r0, [r4, #0x30]
	ldr r12, [r4, #0x34]
	cmp r0, #0x0
	moveq r0, #0x240
	cmp r12, #0x0
	sub r2, r0, #0x28
	moveq r12, #0x10c0
	add r0, r12, r12, lsr #0x1f
	str r2, [r5, #0x24]
	ldr r1, _020977D0 ; =SOCLSocketParamTCP
	mov r3, r0, asr #0x1
	ldr r0, _020977D4 ; =CPSMyIp
	mov r2, #0x0
	strh r12, [r1, #0x2]
	strh r3, [r1, #0x4]
	str r2, [r0, #0x0]
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02097774
	ldr r0, _020977D8 ; =SOCLiDhcpState
	mov r1, #0x1
	str r1, [r0, #0x0]
	ldr r1, _020977DC ; =SOCLi_DhcpTimeout
	str r2, [r5, #0x0]
	ldr r0, _020977E0 ; =SOCLiRequestedIP
	str r1, [r5, #0xc]
	ldr r0, [r0, #0x0]
	str r0, [r5, #0x28]
	b _0209778C
_02097774:
	ldr r0, _020977D8 ; =SOCLiDhcpState
	mov r1, #0x1
	str r2, [r0, #0x0]
	ldr r0, _020977E4 ; =SOCLi_SetMyIP
	str r1, [r5, #0x0]
	str r0, [r5, #0xc]
_0209778C:
	ldr r0, [r4, #0x2c]
	cmp r0, #0x0
	moveq r0, #0xb
	bl CPS_SetThreadPriority
	ldr r0, _020977E8 ; =CPSi_RecvCallbackFunc
	bl WCM_SetRecvDCFCallback
	ldr r0, _020977EC ; =SOCLi_TrashSocket
	bl CPS_SetScavengerCallback
	mov r0, r5
	bl CPS_Startup
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020977C0: .word SOCLiConfigPtr
_020977C4: .word SOCLiCPSConfig
_020977C8: .word SOCLiYieldWait
_020977CC: .word SOCL_LinkIsOn
_020977D0: .word SOCLSocketParamTCP
_020977D4: .word CPSMyIp
_020977D8: .word SOCLiDhcpState
_020977DC: .word SOCLi_DhcpTimeout
_020977E0: .word SOCLiRequestedIP
_020977E4: .word SOCLi_SetMyIP
_020977E8: .word CPSi_RecvCallbackFunc
_020977EC: .word SOCLi_TrashSocket

	arm_func_start SOCLi_StartupSOCL
SOCLi_StartupSOCL: ; 0x020977F0
	stmdb sp!, {r4,lr}
	ldr r0, _02097828 ; =SOCLiConfigPtr
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x20]
	bl SOCLi_StartupCommandPacketQueue
	movs r4, r0
	bmi _0209781C
	ldr r0, _0209782C ; =SOCLSocketParamUDPSend
	bl SOCL_CreateSocket
	ldr r1, _02097830 ; =SOCLiUDPSendSocket
	str r0, [r1, #0x0]
_0209781C:
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02097828: .word SOCLiConfigPtr
_0209782C: .word SOCLSocketParamUDPSend
_02097830: .word SOCLiUDPSendSocket

	.extern _SDK_NintendoWiFi

	arm_func_start SOCL_Startup
SOCL_Startup: ; 0x02097834
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, _02097870 ; =_SDK_NintendoWiFi
	bl OSi_ReferSymbol
	ldr r0, _02097874 ; =SOCLiConfigPtr
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	str r4, [r0, #0x0]
	bl SOCLi_StartupCPS
	bl SOCLi_StartupSOCL
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02097870: .word _SDK_NintendoWiFi
_02097874: .word SOCLiConfigPtr
