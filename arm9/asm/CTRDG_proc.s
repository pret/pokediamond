	.include "asm/macros.inc"
	.include "global.inc"

	.extern CTRDGi_Work

	.section .bss

	.global UNK_021D6948
UNK_021D6948: ; 0x021D6948
	.space 0x4

	.global UNK_021D694C
UNK_021D694C: ; 0x021D694C
	.space 0x4

	.global UNK_021D6950
UNK_021D6950: ; 0x021D6950
	.space 0x4

	.global UNK_021D6954
UNK_021D6954: ; 0x021D6954
	.space 0x4

	.global UNK_021D6958
UNK_021D6958: ; 0x021D6958
	.space 0x8

	.global UNK_021D6960
UNK_021D6960: ; 0x021D6960
	.space 0x4

	.global UNK_021D6964
UNK_021D6964: ; 0x021D6964
	.space 0xbc

	.global UNK_021D6A20
UNK_021D6A20: ; 0x021D6A20
	.space 0xe8

	.text

	arm_func_start CTRDGi_CallbackForSetPhi
CTRDGi_CallbackForSetPhi: ; 0x020DB978
	ldr r0, _020DB988 ; =UNK_021D694C
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020DB988: .word UNK_021D694C

	arm_func_start CTRDG_TerminateForPulledOut
CTRDG_TerminateForPulledOut: ; 0x020DB98C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, #0x2
	bl CTRDGi_SendtoPxi
	bl OS_Terminate
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_PulledOutCallback
CTRDGi_PulledOutCallback: ; 0x020DB9AC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	and r0, r1, #0x3f
	cmp r0, #0x11
	bne _020DBA14
	ldr r0, _020DBA24 ; =UNK_021D6954
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r1, _020DBA28 ; =UNK_021D6958
	mov r0, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020DB9F0
	blx r1
_020DB9F0:
	cmp r0, #0x0
	beq _020DB9FC
	bl CTRDG_TerminateForPulledOut
_020DB9FC:
	ldr r0, _020DBA24 ; =UNK_021D6954
	mov r1, #0x1
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020DBA14:
	bl OS_Terminate
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DBA24: .word UNK_021D6954
_020DBA28: .word UNK_021D6958

	arm_func_start CTRDGi_CallbackForInitModuleInfo
CTRDGi_CallbackForInitModuleInfo: ; 0x020DBA2C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	and r0, r1, #0x3f
	cmp r0, #0x1
	ldreq r0, _020DBA64 ; =CTRDGi_Work
	moveq r1, #0x1
	streqh r1, [r0, #0x0]
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	bl OS_Terminate
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DBA64: .word CTRDGi_Work

	arm_func_start CTRDGi_InitModuleInfo
CTRDGi_InitModuleInfo: ; 0x020DBA68
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	ldr r0, _020DBC50 ; =UNK_021D6948
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	addne sp, sp, #0x14
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldr r1, _020DBC54 ; =0x04000300
	mov r2, #0x1
	str r2, [r0, #0x0]
	ldrh r0, [r1, #0x0]
	ands r0, r0, #0x1
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, #0x40000
	bl OS_SetIrqMask
	ldr r3, _020DBC58 ; =0x04000208
	mov r2, #0x1
	ldrh r4, [r3, #0x0]
	ldr r1, _020DBC5C ; =CTRDGi_Work
	mov r6, r0
	strh r2, [r3, #0x0]
	ldrh r0, [r1, #0x2]
	add r1, sp, #0x0
	bl CTRDGi_LockByProcessor
	ldr r1, _020DBC60 ; =0x04000204
	add r0, sp, #0x8
	ldrh r1, [r1, #0x0]
	and r1, r1, #0x8000
	mov r5, r1, asr #0xf
	bl CTRDGi_ChangeLatestAccessCycle
	ldr r3, _020DBC60 ; =0x04000204
	ldr r0, _020DBC64 ; =UNK_021D6960
	ldrh r2, [r3, #0x0]
	add r0, r0, #0x80
	mov r1, #0x40
	bic r2, r2, #0x8000
	strh r2, [r3, #0x0]
	bl DC_InvalidateRange
	ldr r2, _020DBC64 ; =UNK_021D6960
	ldr r1, _020DBC68 ; =0x08000080
	mov r0, #0x1
	mov r3, #0x40
	add r2, r2, #0x80
	bl MI_DmaCopy16
	ldr r2, _020DBC60 ; =0x04000204
	add r0, sp, #0x8
	ldrh r1, [r2, #0x0]
	bic r1, r1, #0x8000
	orr r1, r1, r5, lsl #0xf
	strh r1, [r2, #0x0]
	bl CTRDGi_RestoreAccessCycle
	ldr r0, _020DBC5C ; =CTRDGi_Work
	add r1, sp, #0x0
	ldrh r0, [r0, #0x2]
	bl CTRDGi_UnlockByProcessor
	ldr r0, _020DBC6C ; =0x027FFF9B
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020DBB70
	ldr r0, _020DBC70 ; =0x027FFF9A
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020DBBDC
_020DBB70:
	ldr r2, _020DBC64 ; =UNK_021D6960
	ldr r0, _020DBC74 ; =0x027FFC30
	ldrh r1, [r2, #0xbe]
	mov r3, #0x0
	strh r1, [r0, #0x0]
_020DBB84:
	add r0, r2, r3
	ldrb r1, [r0, #0xb5]
	add r0, r3, #0x2700000
	add r0, r0, #0xff000
	add r3, r3, #0x1
	strb r1, [r0, #0xC32]
	cmp r3, #0x3
	blt _020DBB84
	ldrh r0, [r2, #0xb0]
	ldr r1, _020DBC74 ; =0x027FFC30
	strh r0, [r1, #0x6]
	ldr r0, [r2, #0xac]
	str r0, [r1, #0x8]
	bl CTRDG_IsExisting
_020DBBBC: ; 0x020DBBBC
	cmp r0, #0x0
	movne r2, #0x1
	ldr r1, _020DBC6C ; =0x027FFF9B
	moveq r2, #0x0
	strb r2, [r1, #0x0]
	ldr r0, _020DBC70 ; =0x027FFF9A
	mov r1, #0x1
	strb r1, [r0, #0x0]
_020DBBDC:
	ldr r0, _020DBC78 ; =0xFFFF0020
	ldr r1, _020DBC7C ; =UNK_021D6964
	mov r2, #0x9c
	bl MIi_CpuCopy32
	bl DC_FlushAll
	ldr r0, _020DBC64 ; =UNK_021D6960
	add r0, r0, #0xfe000000
	mov r0, r0, lsr #0x5
	mov r0, r0, lsl #0x6
	orr r0, r0, #0x1
	bl CTRDGi_SendtoPxi
	ldr r5, _020DBC5C ; =CTRDGi_Work
	ldrh r0, [r5, #0x0]
	cmp r0, #0x1
	beq _020DBC30
	mov r7, #0x1
_020DBC1C:
	mov r0, r7
	bl SVC_WaitByLoop
	ldrh r0, [r5, #0x0]
	cmp r0, #0x1
	bne _020DBC1C
_020DBC30:
	ldr r2, _020DBC58 ; =0x04000208
	mov r0, r6
	ldrh r1, [r2, #0x0]
	strh r4, [r2, #0x0]
	bl OS_SetIrqMask
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DBC50: .word UNK_021D6948
_020DBC54: .word 0x04000300
_020DBC58: .word 0x04000208
_020DBC5C: .word CTRDGi_Work
_020DBC60: .word 0x04000204
_020DBC64: .word UNK_021D6960
_020DBC68: .word 0x08000080
_020DBC6C: .word 0x027FFF9B
_020DBC70: .word 0x027FFF9A
_020DBC74: .word 0x027FFC30
_020DBC78: .word 0xFFFF0020
_020DBC7C: .word UNK_021D6964

	arm_func_start CTRDG_Init
CTRDG_Init: ; 0x020DBC80
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020DBD34 ; =UNK_021D6950
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r1, #0x1
	str r1, [r0, #0x0]
	bl CTRDGi_InitCommon
	ldr r0, _020DBD38 ; =UNK_021D6954
	mov r1, #0x0
	str r1, [r0, #0x0]
	bl PXI_Init
	mov r5, #0xd
	mov r4, #0x1
_020DBCC4:
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
_020DBCD0: ; 0x020DBCD0
	cmp r0, #0x0
	beq _020DBCC4
	ldr r1, _020DBD3C ; =CTRDGi_CallbackForInitModuleInfo
	mov r0, #0xd
	bl PXI_SetFifoRecvCallback
	bl CTRDGi_InitModuleInfo
	mov r0, #0xd
	mov r1, #0x0
	bl PXI_SetFifoRecvCallback
	ldr r1, _020DBD40 ; =CTRDGi_PulledOutCallback
	mov r0, #0xd
	bl PXI_SetFifoRecvCallback
	ldr r1, _020DBD44 ; =UNK_021D6958
	mov r2, #0x0
	ldr r0, _020DBD48 ; =UNK_021D6A20
	str r2, [r1, #0x0]
	bl CTRDGi_InitTaskThread
	ldr r1, _020DBD4C ; =CTRDGi_CallbackForSetPhi
	mov r0, #0x11
	bl PXI_SetFifoRecvCallback
_020DBD20: ; 0x020DBD20
	mov r0, #0x0
	bl CTRDG_Enable
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DBD34: .word UNK_021D6950
_020DBD38: .word UNK_021D6954
_020DBD3C: .word CTRDGi_CallbackForInitModuleInfo
_020DBD40: .word CTRDGi_PulledOutCallback
_020DBD44: .word UNK_021D6958
_020DBD48: .word UNK_021D6A20
_020DBD4C: .word CTRDGi_CallbackForSetPhi
