	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global SOCLiSocketList
SOCLiSocketList: ; 0x021C8D30
	.space 0x4

	.global SOCLiSocketListTrash
SOCLiSocketListTrash: ; 0x021C8D34
	.space 0x4

	.text

	arm_func_start SOCL_SocketIsInTrash
SOCL_SocketIsInTrash:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r1, r0
	ldr r0, _02099FA4 ; =SOCLiSocketListTrash
	bl SOCLi_SocketGetNextPtr
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02099FA4: .word SOCLiSocketListTrash

	arm_func_start SOCL_SocketIsInvalid
SOCL_SocketIsInvalid:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r1, r0
	cmp r1, #0x0
	ble _02099FCC
	ldr r0, _02099FEC ; =SOCLiSocketList
	bl SOCLi_SocketGetNextPtr
	cmp r0, #0x0
	bne _02099FDC
_02099FCC:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {lr}
	bx lr
_02099FDC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_02099FEC: .word SOCLiSocketList

	arm_func_start SOCLi_SocketUnregisterTrash
SOCLi_SocketUnregisterTrash: ; 0x02099FF0
	ldr ip, _0209A000 ; =SOCLi_SocketUnregisterList
	mov r1, r0
	ldr r0, _0209A004 ; =SOCLiSocketListTrash
	bx r12
	.balign 4
_0209A000: .word SOCLi_SocketUnregisterList
_0209A004: .word SOCLiSocketListTrash

	arm_func_start SOCLi_SocketGetNextPtr
SOCLi_SocketGetNextPtr:
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _0209A02C
_0209A014:
	cmp r2, r1
	bxeq lr
	add r0, r2, #0x7c
	ldr r2, [r2, #0x7c]
	cmp r2, #0x0
	bne _0209A014
_0209A02C:
	mov r0, #0x0
	bx lr

	arm_func_start SOCLi_SocketUnregisterList
SOCLi_SocketUnregisterList: ; 0x0209A034
	stmdb sp!, {r4,lr}
	mov r4, r1
	bl SOCLi_SocketGetNextPtr
	cmp r0, #0x0
	ldrne r1, [r4, #0x7c]
	strne r1, [r0, #0x0]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start SOCLi_SocketUnregister
SOCLi_SocketUnregister: ; 0x0209A054
	ldr ip, _0209A064 ; =SOCLi_SocketUnregisterList
	mov r1, r0
	ldr r0, _0209A068 ; =SOCLiSocketList
	bx r12
	.balign 4
_0209A064: .word SOCLi_SocketUnregisterList
_0209A068: .word SOCLiSocketList

	arm_func_start SOCLi_SocketRegisterTrash
SOCLi_SocketRegisterTrash: ; 0x0209A06C
	ldr ip, _0209A07C ; =SOCLi_SocketRegisterList
	mov r1, r0
	ldr r0, _0209A080 ; =SOCLiSocketListTrash
	bx r12
	.balign 4
_0209A07C: .word SOCLi_SocketRegisterList
_0209A080: .word SOCLiSocketListTrash

	arm_func_start SOCLi_SocketRegisterList
SOCLi_SocketRegisterList: ; 0x0209A084
	ldr r2, [r0, #0x0]
	str r2, [r1, #0x7c]
	str r1, [r0, #0x0]
	bx lr

	arm_func_start SOCLi_SocketRegister
SOCLi_SocketRegister: ; 0x0209A094
	ldr ip, _0209A0A4 ; =SOCLi_SocketRegisterList
	mov r1, r0
	ldr r0, _0209A0A8 ; =SOCLiSocketList
	bx r12
	.balign 4
_0209A0A4: .word SOCLi_SocketRegisterList
_0209A0A8: .word SOCLiSocketList
