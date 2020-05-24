    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_021D5360

	.section .bss

	.global UNK_021D3838
UNK_021D3838: ; 0x021D3838
	.space 0x4

	.global UNK_021D383C
UNK_021D383C: ; 0x021D383C
	.space 0x4

	.global UNK_021D3840
UNK_021D3840: ; 0x021D3840
	.space 0x4

	.global UNK_021D3844
UNK_021D3844: ; 0x021D3844
	.space 0x4

	.global UNK_021D3848
UNK_021D3848: ; 0x021D3848
	.space 0x4

	.global UNK_021D384C
UNK_021D384C: ; 0x021D384C
	.space 0x4

	.global UNK_021D3850
UNK_021D3850: ; 0x021D3850
	.space 0x4

	.global UNK_021D3854
UNK_021D3854: ; 0x021D3854
	.space 0x4

	.global UNK_021D3858
UNK_021D3858: ; 0x021D3858
	.space 0x4

	.global UNK_021D385C
UNK_021D385C: ; 0x021D385C
	.space 0x24

	.global UNK_021D3880
UNK_021D3880: ; 0x021D3880
	.space 0x280

	.global UNK_021D3B00
UNK_021D3B00: ; 0x021D3B00
	.space 0x1000

	.global UNK_021D4B00
UNK_021D4B00: ; 0x021D4B00
	.space 0x7e8

	.global UNK_021D52E8
UNK_021D52E8: ; 0x021D52E8
	.space 0x18

    .text

	arm_func_start IsCommandAvailable
IsCommandAvailable:
	stmdb sp!, {r4,lr}
	bl OS_IsRunOnEmulator
_020CEC94:
	cmp r0, #0x0
	moveq r0, #0x1
	ldmeqia sp!, {r4, lr}
	bxeq lr
	bl OS_DisableInterrupts
	ldr r1, _020CECD0
	mov r2, #0x10
	str r2, [r1]
	ldr r4, [r1]
	bl OS_RestoreInterrupts
	cmp r4, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	ldmia sp!, {r4, lr}
	bx lr
_020CECD0: .word 0x04FFF200

	arm_func_start AllocCommand
AllocCommand: ; 0x020CECD4
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020CED24 ; =UNK_021D3838
	ldr r4, [r1, #0x0]
	cmp r4, #0x0
	bne _020CECFC
	bl OS_RestoreInterrupts
_020CECF0:
	mov r0, #0x0
	ldmia sp!, {r4, lr}
	bx lr
_020CECFC:
	ldr r2, [r4, #0x0]
	str r2, [r1, #0x0]
	cmp r2, #0x0
	ldreq r1, _020CED28 ; =UNK_021D3848
	moveq r2, #0x0
	streq r2, [r1, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CED24: .word UNK_021D3838
_020CED28: .word UNK_021D3848

	arm_func_start RequestCommandProc
RequestCommandProc: ; 0x020CED2C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, #0x7
	mov r4, #0x0
_020CED3C:
	mov r0, r5
	mov r1, r4
	mov r2, r4
	bl PXI_SendWordByFifo
_020CED4C:
	cmp r0, #0
	blt _020CED3C
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start InitPXI
InitPXI: ; 0x020CED60
	stmdb sp!, {r4-r6,lr}
	ldr r1, _020CEDC8 ; =PxiFifoCallback
	mov r0, #0x7
	bl PXI_SetFifoRecvCallback
	bl IsCommandAvailable
_020CED74:
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6, lr}
	bxeq lr
	mov r0, #0x7
	mov r1, #0x1
	bl PXI_IsCallbackReady
	cmp r0, #0x0
	ldmneia sp!, {r4-r6, lr}
	bxne lr
	mov r6, #0x64
	mov r5, #0x7
	mov r4, #0x1
_020CEDA4:
	mov r0, r6
	bl OS_SpinWait
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
	cmp r0, #0x0
	beq _020CEDA4
	ldmia sp!, {r4-r6, lr}
	bx lr
_020CEDC8: .word PxiFifoCallback

	arm_func_start PxiFifoCallback
PxiFifoCallback: ; 0x020CEDCC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	bl OS_DisableInterrupts
	mov r4, r0
	mov r0, r5
	bl SNDi_CallAlarmHandler
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start SND_CountWaitingCommand
SND_CountWaitingCommand: ; 0x020CEDFC
	stmdb sp!, {r4,lr}
	bl SND_CountFreeCommand
	mov r4, r0
	bl SND_CountReservedCommand
	rsb r1, r4, #0x100
	sub r0, r1, r0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start SND_CountReservedCommand
SND_CountReservedCommand: ; 0x020CEE1C
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020CEE58 ; =UNK_021D3840
	mov r4, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020CEE48
_020CEE38:
	ldr r1, [r1, #0x0]
	add r4, r4, #0x1
	cmp r1, #0x0
	bne _020CEE38
_020CEE48:
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CEE58: .word UNK_021D3840

	arm_func_start SND_CountFreeCommand
SND_CountFreeCommand: ; 0x020CEE5C
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020CEE98 ; =UNK_021D3838
	mov r4, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020CEE88
_020CEE78:
	ldr r1, [r1, #0x0]
	add r4, r4, #0x1
	cmp r1, #0x0
	bne _020CEE78
_020CEE88:
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CEE98: .word UNK_021D3838

	arm_func_start SND_IsFinishedCommandTag
SND_IsFinishedCommandTag:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _020CEEEC ; =UNK_021D383C
	ldr r1, [r1, #0x0]
	cmp r4, r1
	bls _020CEECC
	sub r1, r4, r1
	cmp r1, #0x80000000
	movcc r4, #0x0
	movcs r4, #0x1
	b _020CEEDC
_020CEECC:
	sub r1, r1, r4
	cmp r1, #0x80000000
	movcc r4, #0x1
	movcs r4, #0x0
_020CEEDC:
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CEEEC: .word UNK_021D383C

	arm_func_start SND_GetCurrentCommandTag
SND_GetCurrentCommandTag: ; 0x020CEEF0
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020CEF24 ; =UNK_021D3840
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	ldreq r1, _020CEF28 ; =UNK_021D383C
	ldreq r4, [r1, #0x0]
	ldrne r1, _020CEF2C ; =UNK_021D3858
	ldrne r4, [r1, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CEF24: .word UNK_021D3840
_020CEF28: .word UNK_021D383C
_020CEF2C: .word UNK_021D3858

	arm_func_start SND_WaitForCommandProc
SND_WaitForCommandProc: ; 0x020CEF30
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl SND_IsFinishedCommandTag
_020CEF40:
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5, lr}
	bxne lr
	mov r4, #0x0
_020CEF54:
	mov r0, r4
	bl SND_RecvCommandReply
	cmp r0, #0x0
	bne _020CEF54
	mov r0, r5
	bl SND_IsFinishedCommandTag
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5, lr}
	bxne lr
	bl RequestCommandProc
	mov r0, r5
	bl SND_IsFinishedCommandTag
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5, lr}
	bxne lr
	mov r4, #0x1
_020CEF9C:
	mov r0, r4
	bl SND_RecvCommandReply
	mov r0, r5
	bl SND_IsFinishedCommandTag
	cmp r0, #0x0
	beq _020CEF9C
	add sp, sp, #0x4
	ldmia sp!, {r4-r5, lr}
	bx lr

	arm_func_start SND_FlushCommand
SND_FlushCommand: ; 0x020CEFC0
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020CF164 ; =UNK_021D3840
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020CEFF8
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r9,lr}
	bx lr
_020CEFF8:
	ldr r1, _020CF168 ; =UNK_021D3854
	ldr r1, [r1, #0x0]
	cmp r1, #0x8
	blt _020CF03C
	ands r1, r5, #0x1
	bne _020CF024
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r9,lr}
	bx lr
_020CF024:
	mov r0, #0x1
	bl SND_RecvCommandReply
	ldr r0, _020CF168 ; =UNK_021D3854
	ldr r0, [r0, #0x0]
	cmp r0, #0x8
	bge _020CF024
_020CF03C:
	ldr r0, _020CF16C ; =UNK_021D3B00
	mov r1, #0x1800
	bl DC_FlushRange
	ldr r1, _020CF164 ; =UNK_021D3840
	mov r0, #0x7
	ldr r1, [r1, #0x0]
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020CF05C:
	cmp r0, #0x0
	bge _020CF0E0
	ands r0, r5, #0x1
	bne _020CF084
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r9, lr}
	bx lr
_020CF084:
	ldr r1, _020CF164
	mov r0, #0x7
	ldr r1, [r1]
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	bge _020CF0E0
	ldr r6, _020CF164
	mov r9, #0x64
	mov r8, #0x7
	mov r7, #0x0
_020CF0B0:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r9
	bl OS_SpinWait
	bl OS_DisableInterrupts
	mov r4, r0
	mov r0, r8
	ldr r1, [r6]
	mov r2, r7
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	blt _020CF0B0
_020CF0E0:
	ands r0, r5, #0x2
	beq _020CF0EC
	bl RequestCommandProc
_020CF0EC:
	ldr r0, _020CF170
	ldr r1, _020CF164
	ldr r3, [r0]
	ldr r5, [r1]
	add r1, r3, #0x1
	ldr r2, _020CF174
	str r1, [r0]
	str r5, [r2, r3, lsl #2]
	cmp r1, #0x8
	movgt r1, #0x0
	ldr r2, _020CF168
	strgt r1, [r0]
	ldr r1, _020CF178
	ldr r3, [r2]
	ldr r0, [r1]
	add ip, r3, #0x1
	add r6, r0, #0x1
	ldr r5, _020CF164
	mov lr, #0x0
	ldr r3, _020CF17C
	mov r0, r4
	str lr, [r5]
	str lr, [r3]
	str ip, [r2]
	str r6, [r1]
	bl OS_RestoreInterrupts
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r9, lr}
	bx lr
_020CF164: .word UNK_021D3840
_020CF168: .word UNK_021D3854
_020CF16C: .word UNK_021D3B00
_020CF170: .word UNK_021D3850
_020CF174: .word UNK_021D385C
_020CF178: .word UNK_021D3858
_020CF17C: .word UNK_021D3844

	arm_func_start SND_PushCommand
SND_PushCommand: ; 0x020CF180
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r2, _020CF1C0 ; =UNK_021D3844
	ldr r1, [r2, #0x0]
	cmp r1, #0x0
	ldreq r1, _020CF1C4 ; =UNK_021D3840
	streq r4, [r2, #0x0]
	streq r4, [r1, #0x0]
	strne r4, [r1, #0x0]
	strne r4, [r2, #0x0]
	mov r1, #0x0
	str r1, [r4, #0x0]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CF1C0: .word UNK_021D3844
_020CF1C4: .word UNK_021D3840

	arm_func_start SND_AllocCommand
SND_AllocCommand:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl IsCommandAvailable
_020CF1D4:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl AllocCommand
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	ands r0, r4, #0x1
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl SND_CountWaitingCommand
	cmp r0, #0x0
	ble _020CF238
	mov r4, #0x0
_020CF214:
	mov r0, r4
	bl SND_RecvCommandReply
	cmp r0, #0x0
	bne _020CF214
	bl AllocCommand
	cmp r0, #0x0
	beq _020CF240
	ldmia sp!, {r4,lr}
	bx lr
_020CF238:
	mov r0, #0x1
	bl SND_FlushCommand
_020CF240:
	bl RequestCommandProc
	mov r4, #0x1
_020CF248:
	mov r0, r4
	bl SND_RecvCommandReply
	bl AllocCommand
	cmp r0, #0x0
	beq _020CF248
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start SND_RecvCommandReply
SND_RecvCommandReply: ; 0x020CF264
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	mov r5, r0
	ands r0, r4, #0x1
	beq _020CF2C0
	bl SNDi_GetFinishedCommandTag
	ldr r4, _020CF380 ; =UNK_021D383C
	ldr r1, [r4, #0x0]
	cmp r1, r0
	bne _020CF2E8
	mov r6, #0x64
_020CF294:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r6
	bl OS_SpinWait
	bl OS_DisableInterrupts
	mov r5, r0
	bl SNDi_GetFinishedCommandTag
	ldr r1, [r4, #0x0]
	cmp r1, r0
	beq _020CF294
	b _020CF2E8
_020CF2C0:
	bl SNDi_GetFinishedCommandTag
	ldr r1, _020CF380 ; =UNK_021D383C
	ldr r1, [r1, #0x0]
	cmp r1, r0
	bne _020CF2E8
	mov r0, r5
	bl OS_RestoreInterrupts
_020CF2DC:
	mov r0, #0x0
	ldmia sp!, {r4-r6, lr}
	bx lr
_020CF2E8:
	ldr r0, _020CF384 ; =UNK_021D384C
	ldr r2, _020CF388 ; =UNK_021D385C
	ldr r3, [r0, #0x0]
	add r1, r3, #0x1
	ldr r4, [r2, r3, lsl #0x2]
	str r1, [r0, #0x0]
	cmp r1, #0x8
	movgt r1, #0x0
	strgt r1, [r0, #0x0]
	ldr r0, [r4, #0x0]
	mov r1, r4
	cmp r0, #0x0
	beq _020CF32C
_020CF31C:
	ldr r1, [r1, #0x0]
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	bne _020CF31C
_020CF32C:
	ldr r0, _020CF38C ; =UNK_021D3848
	ldr r3, _020CF390 ; =UNK_021D3854
	ldr r0, [r0, #0x0]
	ldr r2, _020CF380 ; =UNK_021D383C
	cmp r0, #0x0
	strne r4, [r0, #0x0]
	ldreq r0, _020CF394 ; =UNK_021D3838
	ldr lr, [r3, #0x0]
	streq r4, [r0, #0x0]
	ldr ip, _020CF38C ; =UNK_021D3848
	sub r6, lr, #0x1
	ldr r0, [r2, #0x0]
	str r1, [r12, #0x0]
	add lr, r0, #0x1
	mov r0, r5
	str r6, [r3, #0x0]
	str lr, [r2, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020CF380: .word UNK_021D383C
_020CF384: .word UNK_021D384C
_020CF388: .word UNK_021D385C
_020CF38C: .word UNK_021D3848
_020CF390: .word UNK_021D3854
_020CF394: .word UNK_021D3838

	arm_func_start SND_CommandInit
SND_CommandInit: ; 0x020CF398
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	bl InitPXI
	ldr r3, _020CF478 ; =UNK_021D3B00
	ldr r0, _020CF47C ; =UNK_021D3838
	mov r4, #0x0
	str r3, [r0, #0x0]
	mov r1, r3
	mov r0, #0x18
_020CF3BC:
	add r4, r4, #0x1
	mla r2, r4, r0, r1
	cmp r4, #0xff
	str r2, [r3], #0x18
	blt _020CF3BC
	ldr r7, _020CF480 ; =UNK_021D4B00
	mov r10, #0x0
	ldr r5, _020CF484 ; =UNK_021D3840
	ldr r4, _020CF488 ; =UNK_021D3844
	ldr lr, _020CF48C ; =UNK_021D3854
	ldr ip, _020CF490 ; =UNK_021D384C
	ldr r3, _020CF494 ; =UNK_021D3850
	ldr r1, _020CF498 ; =UNK_021D383C
	ldr sb, _020CF49C ; =UNK_021D52E8
	ldr r6, _020CF4A0 ; =UNK_021D3848
	ldr r2, _020CF4A4 ; =UNK_021D3858
	mov r8, #0x1
	ldr r0, _020CF4A8 ; =UNK_021D3880
	ldr fp, _020CF4AC ; =UNK_021D5360
	str r9, [r6, #0x0]
	str r10, [r7, #0x7e8]
	str r10, [r5, #0x0]
	str r10, [r4, #0x0]
	str r10, [lr, #0x0]
	str r10, [r12, #0x0]
	str r10, [r3, #0x0]
	str r8, [r2, #0x0]
	str r10, [r1, #0x0]
	str r0, [r11, #0x0]
	bl SNDi_InitSharedWork
	mov r0, r8
	bl SND_AllocCommand
_020CF43C:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r11, lr}
	bxeq lr
	mov r2, #0x1D
	mov r1, fp
	str r2, [r0, #0x4]
	ldr r1, [r1]
	str r1, [r0, #0x8]
	bl SND_PushCommand
	mov r0, r8
	bl SND_FlushCommand
	add sp, sp, #0x4
	ldmia sp!, {r4-r11, lr}
	bx lr
_020CF478: .word UNK_021D3B00
_020CF47C: .word UNK_021D3838
_020CF480: .word UNK_021D4B00
_020CF484: .word UNK_021D3840
_020CF488: .word UNK_021D3844
_020CF48C: .word UNK_021D3854
_020CF490: .word UNK_021D384C
_020CF494: .word UNK_021D3850
_020CF498: .word UNK_021D383C
_020CF49C: .word UNK_021D52E8
_020CF4A0: .word UNK_021D3848
_020CF4A4: .word UNK_021D3858
_020CF4A8: .word UNK_021D3880
_020CF4AC: .word UNK_021D5360
