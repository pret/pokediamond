	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global UNK_021D5E20
UNK_021D5E20: ; 0x021D5E20
	.space 0x4

	.global UNK_021D5E24
UNK_021D5E24: ; 0x021D5E24
	.space 0x4

	.text

	arm_func_start CARDi_SendtoPxi
CARDi_SendtoPxi: ; 0x020D7BCC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r1, r7
	mov r0, #0xe
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020D7BEC: ; 0x020D7BEC
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r5, #0xe
	mov r4, #0x0
_020D7C04:
	mov r0, r6
	bl SVC_WaitByLoop
	mov r0, r5
	mov r1, r7
	mov r2, r4
	bl PXI_SendWordByFifo
_020D7C1C: ; 0x020D7C1C
	cmp r0, #0x0
	bne _020D7C04
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start CARDi_CheckPulledOutCore
CARDi_CheckPulledOutCore:
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldr r1, _020D7C94 ; =0x027FFC10
	ldrh r1, [r1, #0x0]
	cmp r1, #0x0
	ldreq r1, _020D7C98 ; =0x027FF800
	ldrne r1, _020D7C9C ; =0x027FFC00
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x0]
	cmp r0, r1
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl OS_DisableInterrupts
	mov r4, r0
	mov r0, #0xe
	mov r1, #0x11
	mov r2, #0x0
	bl CARDi_PulledOutCallback
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D7C94: .word 0x027FFC10
_020D7C98: .word 0x027FF800
_020D7C9C: .word 0x027FFC00

	arm_func_start CARD_TerminateForPulledOut
CARD_TerminateForPulledOut: ; 0x020D7CA0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020D7D10 ; =0x027FFFA8
	mov r5, #0x1
	ldrh r0, [r0, #0x0]
	and r0, r0, #0x8000
	movs r0, r0, asr #0xf
	beq _020D7CEC
	bl PM_ForceToPowerOff
	cmp r0, #0x4
	bne _020D7CE4
	ldr r4, _020D7D14 ; =0x000A3A47
_020D7CD0:
	mov r0, r4
	bl OS_SpinWait
	bl PM_ForceToPowerOff
	cmp r0, #0x4
	beq _020D7CD0
_020D7CE4:
	cmp r0, #0x0
	moveq r5, #0x0
_020D7CEC:
	cmp r5, #0x0
	beq _020D7D00
	mov r0, #0x1
	mov r1, r0
	bl CARDi_SendtoPxi
_020D7D00:
	bl OS_Terminate
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D7D10: .word 0x027FFFA8
_020D7D14: .word 0x000A3A47

	arm_func_start CARD_IsPulledOut
CARD_IsPulledOut: ; 0x020D7D18
	ldr r0, _020D7D24 ; =UNK_021D5E20
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020D7D24: .word UNK_021D5E20

	arm_func_start CARDi_PulledOutCallback
CARDi_PulledOutCallback: ; 0x020D7D28
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	and r0, r1, #0x3f
	cmp r0, #0x11
	bne _020D7D90
	ldr r2, _020D7DA0 ; =UNK_021D5E20
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r1, _020D7DA4 ; =UNK_021D5E24
	mov r0, #0x1
	ldr r1, [r1, #0x0]
	str r0, [r2, #0x0]
	cmp r1, #0x0
	beq _020D7D70
	blx r1
_020D7D70:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	bl CARD_TerminateForPulledOut
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020D7D90:
	bl OS_Terminate
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D7DA0: .word UNK_021D5E20
_020D7DA4: .word UNK_021D5E24

	arm_func_start CARD_InitPulledOutCallback
CARD_InitPulledOutCallback: ; 0x020D7DA8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl PXI_Init
	ldr r1, _020D7DD8 ; =CARDi_PulledOutCallback
	mov r0, #0xe
	bl PXI_SetFifoRecvCallback
	ldr r0, _020D7DDC ; =UNK_021D5E24
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D7DD8: .word CARDi_PulledOutCallback
_020D7DDC: .word UNK_021D5E24
